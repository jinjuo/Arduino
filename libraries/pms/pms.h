
#ifndef _PMS_H_
#define _PMS_H_

#include <arduino.h>
#include <tri.h>
#include <pmsConfig.h>

// Important: Use 3.3V logic
// Pin 1: Vcc
// Pin 2: GND

// Using SoftSerial:
//   Pin 4: Digital pin 9 (there is no choice) 
//   Pin 5: Digital pin 8 (there is no choice)

class Pms5003 {
public:
    typedef uint16_t pmsData;
private:
    const uint8_t sig[ 2 ]{ 0x42, 0x4D };
    pmsData dataSize;
    tri passive;
    tri sleep;
    unsigned long timeout;
    static const decltype( timeout ) timeoutPassive = 65;  // transfer time of 32data + 1stop + 1start using 9600bps is 33 usec. timeoutPassive could be at least 34, Value of 65 is an arbitrary doubled
    static const decltype( timeout ) timeoutActive = 1100; // Probably could be at least 900 + 33
    static const decltype( timeout ) wakeupTime = 3000;    // Experimentally

#if defined PMS_ALTSOFTSERIAL
    AltSoftSerial pmsSerial;
#elif defined PMS_SOFTSERIAL
#error "Pms5003 serial library not defined"
#endif  

public:
    enum PmsStatus : uint8_t {
        OK = 0,
        noData,
        readError,
        frameLenMismatch,
        sumError,
        nValues_PmsStatus
    };

    static const char *errorMsg[ nValues_PmsStatus ];

    enum PmsCmd : uint32_t {
        cmdReadData = 0x0000e2L,
        cmdModePassive = 0x0000e1L,
        cmdModeActive = 0x0100e1L,
        cmdSleep = 0x0000e4L,
        cmdWakeup = 0x0100e4L
    };

    enum PmsDataNames : uint8_t {
        PM1dot0CF1 = 0,
        PM2dot5CF1,
        PM10CF1,
        PM1dot0,
        PM2dot5,
        PM10,
        Particles0dot3,
        Particles0dot5,
        Particles1dot0,
        Particles2dot5,
        Particles5dot0,
        Particles10,
        HCHO,
        temperature,
        humidity,
        Reserved,
        nValues_PmsDataNames
    };

    static const char *dataNames[ nValues_PmsDataNames ];
    static const char *metrics[ nValues_PmsDataNames ];

    void setTimeout( decltype( timeout ) timeout );
    decltype( timeout ) getTimeout( void );

    Pms5003();
    ~Pms5003();
    bool begin( void );
    void end( void );
    int available( void );
    PmsStatus read( pmsData *data, const size_t nData );
    pmsData getDataSize( void );
    bool write( PmsCmd cmd );
};

#endif
