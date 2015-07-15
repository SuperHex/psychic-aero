#ifndef __config__
#define __config__

#include "../base/container.hpp"

// -----* global *-----
typedef int int16_t;
typedef unsigned char Byte;
typedef float Factor;
// frequency of microcontroller
#define F_CPU 20000000UL


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
typedef base::container<float>       Vector;
typedef base::container<Vector>      MeasureValue;
typedef float                        Factor;

// complementary filter ratio
#define Ka 1
#define Kg 1.5
#endif
