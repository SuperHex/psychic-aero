#ifndef __config__
#define __config__

// ****************************
// frequency of microcontroller
#define F_CPU 20000000UL
// ****************************

// ****************************
// PID controller factor
#define SAMPLE_TIME 100 // sample time = 100ms
#define dt (SAMPLE_TIME) / F_CPU
#define OUTPUT_CLAMP true
#define P_CONTROL    true
#define I_CONTROL    true
#define D_CONTROL    true
// #define Kp 2.8
// #define Ki 3.6
// #define Kd 5.5
// ****************************

#endif
