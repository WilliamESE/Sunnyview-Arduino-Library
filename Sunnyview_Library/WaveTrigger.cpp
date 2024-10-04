/**************************************************************************************************
 * Project: Wave Trigger Library
 * Program: Source file for wave trigger library
 * Company: Crescent School
 * Author: William Veldhuis
 * Date: Novemeber 30 2023
 * Version: 1
**************************************************************************************************/

#include "WaveTrigger.h"

WaveTrigger::WaveTrigger(unsigned int baudRate) : m_baudRate(baudRate), m_rx(0), m_tx(1){
    
}

void WaveTrigger::begin(){
    //Set RX and TX pins as outputs
    pinMode(m_rx, OUTPUT);
    pinMode(m_tx, OUTPUT);

    //Run the connect process
    connected = (boolean)connect();
}


void WaveTrigger::runTrack(uint16_t trackNumber, boolean solo = true, boolean lock = false){
    //Process the paramters into individual bytes to be sent
    uint8_t trackMSB = (uint8_t)GET_MSB(trackNumber);
    uint8_t trackLSB = (uint8_t)GET_LSB(trackNumber);
    uint8_t playCode = ((solo) ? 0x00 : 0x01);
    uint8_t lockCode = ((lock) ? 0x00 : 0x01);

    //Construct data array
    uint8_t data[] = {playCode, trackLSB, trackMSB, lockCode};

    //Send command to the board
    sendCommand(CONTROL_TRACK, data);
}

void WaveTrigger::pauseTrack(uint16_t trackNumber, boolean lock = false){
    //Process the paramters into individual bytes to be sent
    uint8_t trackMSB = (uint8_t)GET_MSB(trackNumber);
    uint8_t trackLSB = (uint8_t)GET_LSB(trackNumber);
    uint8_t lockCode = ((lock) ? 0x00 : 0x01);

    uint8_t data[] = {0x02, trackLSB, trackMSB, lockCode};

    //Send command to the board
    sendCommand(CONTROL_TRACK, data);
}

void WaveTrigger::resumeTrack(uint16_t trackNumber, boolean lock = false){
    //Process the paramters into individual bytes to be sent
    uint8_t trackMSB = (uint8_t)GET_MSB(trackNumber);
    uint8_t trackLSB = (uint8_t)GET_LSB(trackNumber);
    uint8_t lockCode = ((lock) ? 0x00 : 0x01);

    uint8_t data[] = {0x03, trackLSB, trackMSB, lockCode};

    //Send command to the board
    sendCommand(CONTROL_TRACK, data);
}

void WaveTrigger::stopTrack(uint16_t trackNumber, boolean lock = false){
    //Process the paramters into individual bytes to be sent
    uint8_t trackMSB = (uint8_t)GET_MSB(trackNumber);
    uint8_t trackLSB = (uint8_t)GET_LSB(trackNumber);
    uint8_t lockCode = ((lock) ? 0x00 : 0x01);

    uint8_t data[] = {0x04, trackLSB, trackMSB, lockCode};

    //Send command to the board
    sendCommand(CONTROL_TRACK, data);
}

void WaveTrigger::loadTrack(uint16_t trackNumber, boolean lock = false){
    //Process the paramters into individual bytes to be sent
    uint8_t trackMSB = (uint8_t)GET_MSB(trackNumber);
    uint8_t trackLSB = (uint8_t)GET_LSB(trackNumber);
    uint8_t lockCode = ((lock) ? 0x00 : 0x01);

    uint8_t data[] = {0x07, trackLSB, trackMSB, lockCode};

    //Send command to the board
    sendCommand(CONTROL_TRACK, data);
}


void WaveTrigger::setLoop(uint16_t trackNumber, boolean state, boolean lock = false){
    //Process the paramters into individual bytes to be sent
    uint8_t trackMSB = (uint8_t)GET_MSB(trackNumber);
    uint8_t trackLSB = (uint8_t)GET_LSB(trackNumber);
    uint8_t loopCode = ((state) ? 0x05 : 0x06);
    uint8_t lockCode = ((lock) ? 0x00 : 0x01);

    uint8_t data[] = {loopCode, trackLSB, trackMSB, lockCode};

    //Send command to the board
    sendCommand(CONTROL_TRACK, data);
}


void WaveTrigger::stopAll(){
    sendCommand(STOP_ALL, NULL);
}

void WaveTrigger::resumeAll(){
    sendCommand(RESUME_ALL, NULL);
}


void WaveTrigger::setVolume(int16_t level){
    if(level > VOLUME_MAX)
        level = VOLUME_MAX;
    if(level < VOLUME_MIN)
        level = VOLUME_MIN;
    
    //Process the paramters into individual bytes to be sent
    uint8_t levelMSB = (uint8_t)GET_MSB(level);
    uint8_t levelLSB = (uint8_t)GET_LSB(level);
    uint8_t data[] = {levelLSB, levelMSB};

    //Send command to the board
    sendCommand(VOLUME, data);
}

void WaveTrigger::setTrackVolume(uint16_t trackNumber, int16_t level){
    if(level > VOLUME_MAX)
        level = VOLUME_MAX;
    if(level < VOLUME_MIN)
        level = VOLUME_MIN;

    //Process the paramters into individual bytes to be sent
    uint8_t trackMSB = (uint8_t)GET_MSB(trackNumber);
    uint8_t trackLSB = (uint8_t)GET_LSB(trackNumber);
    uint8_t levelMSB = (uint8_t)GET_MSB(level);
    uint8_t levelLSB = (uint8_t)GET_LSB(level);

    uint8_t data[] = {trackLSB, trackMSB, levelLSB, levelMSB};

    //Send command to the board
    sendCommand(VOLUME, data);
}

void WaveTrigger::setSampleRate(int16_t rate){
    //Process the paramters into individual bytes to be sent
    uint8_t rateMSB = (uint8_t)GET_MSB(rate);
    uint8_t rateLSB = (uint8_t)GET_LSB(rate);

    uint8_t data[] = {rateLSB, rateMSB};
    sendCommand(SAMPLE_RATE, data);
}


void WaveTrigger::trackFade(uint16_t trackNumber, int16_t targetLevel, uint16_t time, boolean stop){
    if(targetLevel > VOLUME_MAX)
        targetLevel = VOLUME_MAX;
    if(targetLevel < VOLUME_MIN)
        targetLevel = VOLUME_MIN;
    
    //Process the paramters into individual bytes to be sent
    uint8_t trackMSB = (uint8_t)GET_MSB(trackNumber);
    uint8_t trackLSB = (uint8_t)GET_LSB(trackNumber);
    uint8_t levelMSB = (uint8_t)GET_MSB(targetLevel);
    uint8_t levelLSB = (uint8_t)GET_LSB(targetLevel);
    uint8_t timeMSB = (uint8_t)GET_MSB(time);
    uint8_t timeLSB = (uint8_t)GET_LSB(time);
    uint8_t stopCode = ((stop) ? 0x00 : 0x01);

    uint8_t data[] = {trackLSB, trackMSB, levelLSB, levelMSB, timeLSB, timeMSB, stopCode};

    //Send command to the board
    sendCommand(TRACK_FADE, data);
}


//Get functions
WaveTrigger::System_Info WaveTrigger::getSystemInfo(){
    return systemInfo;
}

WaveTrigger::Status WaveTrigger::getSystemStatus(){
    sendRequest(STATUS);
    return systemStatus;
}

uint8_t WaveTrigger::getLastError(){
    return error;
}

boolean WaveTrigger::isConnected(){
    return connected;
}


//Private functions
uint8_t WaveTrigger::sendCommand(Commands cmd, uint8_t data[]){
    int cnt = 0;
    //Make sure we are connected properly before writing data
    if(!connected)
        return;
    
    //Message header array
    uint8_t send[] = {0xf0, 0xaa, commandLengths[cmd], commandCode[cmd]};

    //Send header
    for(cnt=0;cnt<4;cnt++){
        Serial1.write(send[cnt]);
    }

    //Send data
    if(data != NULL){
        for(cnt=0;cnt<(commandLengths[cmd]-5);cnt++){
            Serial1.write(data[cnt]);
        }
    }

    //Send tail
    Serial1.write(0x55);
}

uint8_t WaveTrigger::sendRequest(Commands cmd){
    int cnt = 0;
    error = 0;
    if(cmd >= 4) //Only the first 4 commands are requests for information
        return recordError(NOT_VALID_COMMAND);

    uint8_t send[] = {0xf0, 0xaa, commandLengths[cmd], commandCode[cmd], 0x55};

    for(cnt=0;cnt<(commandLengths[cmd]);cnt++)
        Serial1.write(send[cnt]);

    //Now listen for response
    delay(100);
    //read response
    uint8_t data[64];
    cnt = 0;
    while(Serial1.available() > 0){
        data[cnt] = Serial1.read();
        cnt++;
    }

    //Process response
    switch(cmd){
        case GET_VERSION:
            //Recieves a string of data like "WAV Trigger v1.34"
            //Verify that this is a WAV Trigger
            if((data[4] == 'W') && (data[8] == 'T')){
                //Store version as an integer in the varaibles - 
                //  Version number is "1.34" => (int)134 => systemInfo.version
                //  Converts the charater into a number, multiplies by the needed digit placement and adds them together.
                systemInfo.version = ((data[17] - 0x30) * 100) + ((data[19] - 0x30) * 10) + ((data[20] - 0x30));
                if(systemInfo.version != 134)
                    return recordError(UNKNOWN_VERSION);
            }
            else{
                return recordError(UNKNOWN_DEVICE);
            }
            break;
        case GET_SYS_INFO:
            //Gets the number of voices
            systemInfo.numVoices = data[4];
            //Gets the numer of tracks
            //  Has to take the MS and LS and combine them into one 16 bit value
            systemInfo.numTracks = B_TO_INT((uint16_t)data[5], (uint16_t)data[6]);
            break;
        case STATUS:{
            //Lists all the voices currently playing
            systemStatus.numTracks = (cnt - 5) / 2; //5 bytes is the header and tail data, each track has 2 bytes.
            for(cnt = 0;cnt<systemStatus.numTracks;cnt++)
                systemStatus.tracks[cnt] = B_TO_INT((uint16_t)data[(cnt*2)+4], (uint16_t)data[(cnt*2)+5]);
            break;
            }
    }
    return REQUEST_SUCCESSFUL;
}

uint8_t WaveTrigger::connect(){
    //Make sure we aren't already connected to the device.
    if(connected)
        return true;
    
    //Initialize the serial port
    Serial1.begin(9600);

    //Send the get version command to check the connection
    uint8_t result = sendRequest(GET_VERSION);
    //Return result
    if(result == REQUEST_SUCCESSFUL)
        return true;
    return false;
}

uint8_t WaveTrigger::recordError(uint8_t code){
    //Save the error for later retrevial
    error = code;
    return code;
}