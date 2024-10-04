/**************************************************************************************************
 * Project: Wave Trigger Library
 * Program: Header file for wave trigger library
 * Company: Crescent School
 * Author: William Veldhuis
 * Date: Novemeber 30 2023
 * Version: 1
**************************************************************************************************/

#ifndef WAVETRIGGER
#define WAVETRIGGER

//Libraries
#include "Arduino.h"
#include <Stdint.h>

#define GET_MSB(x)              (((x) & 0xFF00) >> 8)
#define GET_LSB(x)              (((x) & 0xFF))
#define B_TO_INT(MS, LS)        (((MS) << 8) | (LS))

//Class
class WaveTrigger {
    public:
        //Public constants
        enum Commands{
            GET_VERSION,
            GET_SYS_INFO,
            SET_REPORTING,
            STATUS,
            CONTROL_TRACK,
            STOP_ALL,
            RESUME_ALL,
            VOLUME,
            SAMPLE_RATE,
            SET_TRIGGER_BANK,
            TRACK_VOLUME,
            AMP_POWER,
            TRACK_FADE
        };

        enum ErrorCodes{
            REQUEST_SUCCESSFUL,
            NOT_VALID_COMMAND,
            UNKNOWN_DEVICE,
            UNKNOWN_VERSION
        };
        
        typedef struct System_Info{
            uint16_t version;
            uint16_t numTracks;
            uint8_t numVoices;
        }tpInfo;

        typedef struct Status {
            uint8_t numTracks;
            uint16_t tracks[14];
        }tpStatus;

    private:
        //Defines the number of commands we are working with
        //  Must be static ( same for all Wave Triggers )
        static uint8_t const NUM_COMMANDS = 13;
        //Number of voices
        static uint8_t const NUM_VOICES = 14;
        //Number of tracks
        static uint8_t const NUM_TRACKS = 4096;
        //Volume definitions
        static int8_t const VOLUME_MAX = 10;
        static int8_t const VOLUME_MIN = -70;

        //Lookup arrays
        uint8_t commandCode[NUM_COMMANDS] = {0x01, 0x02, 0x0E, 0x07, 0x0D, 0x04, 0x0B, 0x05, 0x0C, 0x0F, 0x08, 0x09, 0x0A};
        uint8_t commandLengths[NUM_COMMANDS] = {5, 5, 6, 5, 9, 5, 5, 7, 7, 6, 9, 6, 12};
        //  For all tracks the data length is the total length - 4

        //Varaibles
        tpInfo systemInfo = {0,0,0};
        tpStatus systemStatus = {0, {0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
        boolean connected = false;
        unsigned int m_baudRate = 9600;
        uint8_t m_rx;
        uint8_t m_tx;

        //Response array
        uint8_t response[10] = {0,0,0,0,0,0,0,0,0,0};

        //Last Error
        uint8_t error = 0;
    
    //Functions
    public:
        /**
         *   \brief WaveTrigger - Initializes the object
         *   \param baudrate - Speed of the communications
        **/
        WaveTrigger(unsigned int baudRate);

        /**
         *   \brief begin - Loads the object and attempts to connect to the WAV Trigger
        **/
        void begin();

        /**
         *   \brief connect - Attempts to connect to the board if not already connected
         *   \return Returns 0 on failure, 1 on success
        **/
        uint8_t connect();

        //Controls

        /**
         *   \brief runTrack - Plays a track
         *   \param trackNumber - Which track to play, number from 1-4096
         *   \param solo - True = stop all other tracks and just play this one; False = play this with anything else currently playing
         *   \param lock - True = lock this so other tracks can't play; false = don't lock
        **/
        void runTrack(uint16_t trackNumber, boolean solo = true, boolean lock = false);

        /**
         *   \brief pauseTrack - Pause a track that is currently playing
         *   \param trackNumber - Which track to play, number from 1-4096
         *   \param lock - True = lock this so other tracks can't play; false = don't lock
        **/
        void pauseTrack(uint16_t trackNumber, boolean lock = false);

        /**
         *   \brief resumeTrack - Restarts a paused track, if the track is not loaded it will not play it!
         *   \param trackNumber - Which track to play, number from 1-4096 
         *   \param lock - True = lock this so other tracks can't play; false = don't lock
        **/
        void resumeTrack(uint16_t trackNumber, boolean lock = false);

        /**
         *   \brief stopTrack - Stops a track that is currently running
         *   \param trackNumber - Which track to play, number from 1-4096
         *   \param lock - True = lock this so other tracks can't play; false = don't lock
        **/
        void stopTrack(uint16_t trackNumber, boolean lock = false);

        /**
         *   \brief loadTrack - Loads a track, but does not play! The track is considered paused when loaded
         *   \param trackNumber - Which track to play, number from 1-4096
         *   \param lock - True = lock this so other tracks can't play; false = don't lock
        **/
        void loadTrack(uint16_t trackNumber, boolean lock = false);

        /**
         *   \brief setLoop - Set the loop on/off for a track
         *   \param trackNumber - Which track to play, number from 1-4096 
         *   \param state - True = on; False = off
         *   \param lock - True = lock this so other tracks can't play; false = don't lock
        **/
        void setLoop(uint16_t trackNumber, boolean state, boolean lock = false);

        /**
         *   \brief stopAll - Stops all tracks currently running
        **/
        void stopAll();

        /**
         *   \brief resumeAll - Resumes all paused tracks
        **/
        void resumeAll();

        /**
         *   \brief setVolume - Change the overall volume level
         *   \param level - Signed int from -70 to +10
        **/
        void setVolume(int16_t level);

        /**
         *   \brief setTrackVolume - Set the volume of a specific track
         *   \param trackNumber - Which track to play, number from 1-4096 
         *   \param level - Signed int from -70 to +10 
        **/
        void setTrackVolume(uint16_t trackNumber, int16_t level);

        /**
         *   \brief setSampleRate - Modifies the playback speed of all tracks
         *   \param rate - signed int value from -32767 to +32767
        **/
        void setSampleRate(int16_t rate);

        /**
         *   \brief trackFade - Set a track to fade in/out
         *   \param trackNumber - Which track to play, number from 1-4096 
         *   \param targetLevel - The target volume; Signed int from -70 to +10 
         *   \param time - Time in milliseconds for the fade to complete
         *   \param stop - Stop fade automatically when target volume is reached; true = on; false = false
        **/
        void trackFade(uint16_t trackNumber, int16_t targetLevel, uint16_t time, boolean stop);


        //Get functions

        /**
         *   \brief getSystemInfo - Gets the system information about the board, like the version number
         *   \return System_Info structure
        **/
        System_Info getSystemInfo();

        /**
         *   \brief getSystemStatus - Gets what tracks are currently being played by the board - up top 14
         *   \return Status structure
        **/
        Status getSystemStatus();

        /**
         *   \brief getLastError - If the connection fails this returns the error code
         *   \return 0 = REQUEST_SUCCESSFUL
                     1 = NOT_VALID_COMMAND,
                     2 = UNKNOWN_DEVICE,
                     3 = UNKNOWN_VERSION
        **/
        uint8_t getLastError();

        /**
         *   \brief isConnected - gets if the connection was successful
         *   \return true if connection was successful; false if not successful
        **/
        boolean isConnected();

    private:
        //Private functions
        uint8_t sendCommand(Commands cmd, uint8_t data[]);
        uint8_t sendRequest(Commands cmd);
        uint8_t recordError(uint8_t code);
};

#endif //WAVETRIGGER