#ifndef __config__
#define __config__

#include "../base/container.hpp"

// -----* global *-----
typedef int int16_t;
typedef unsigned char Byte;
typedef float Factor;
// frequency of microcontroller
#define F_CPU 16000000UL

// -----* base/I2C *------
#define BAUD_RATE 96000
#define TWSR_VALUE 0x00
#define TWBR_VALUE ((F_CPU / BAUD_RATE) - 16) / (2 * TWSR_VALUE) + 1

// -----* algorithm/PID *-----
#define SAMPLE_TIME 100 // sample time = 100ms
#define dt (SAMPLE_TIME) / F_CPU
#define OUTPUT_CLAMP true
#define P_CONTROL    true
#define I_CONTROL    true
#define D_CONTROL    true
// #define Kp 2.8
// #define Ki 3.6
// #define Kd 5.5


// -----* core/IMU *-----
// our primitive Vector.
// It store x,y,z value in v[0],v[1],v[2]
typedef base::container<float>       Vector;
// a measure value consist of three sensor
// it will store acc in m[0], gyro in m[1], and mag in [2]
typedef base::container<Vector>      MeasureValue;
typedef float                        Factor;

// complementary filter ratio
#define Ka 1
#define Kb 1.5
#define NORMAL_ACC (Ka/(Ka+Kb))
#define NORMAL_GYR (Kb/(Ka+Kb))
#define ARC_PI 57.2975 // a shortcut of 180/pi
#endif
