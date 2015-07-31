#ifndef __config__
#define __config__

#include "../base/container.hpp"

// -----* global *-----
typedef int                      int16_t;
typedef unsigned int             uint16_t;
typedef unsigned long int        uint32_t;
typedef unsigned char            Byte;
typedef unsigned int             size_t;
typedef float                    Factor;
// our primitive Vector.
// It store x,y,z value in v[0],v[1],v[2]
typedef base::container<float>   Vector;
// a measure value consist of three sensor
// it will store acc in m[0], gyro in m[1], and mag in [2]
typedef base::container<Vector>  MeasureValue;
typedef float                    Factor;

// frequency of microcontroller
#define F_CPU 16000000UL

// Pin and Port
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7
#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11
#define PIN_12 12
#define PIN_13 13
#define PIN_A0 14
#define PIN_A1 15
#define PIN_A2 16
#define PIN_A3 17
#define PIN_A4 27
#define PIN_A5 28

// -----* algorithm/PID *-----
#define SAMPLE_TIME 100 // sample time = 100ms
#define dt ((SAMPLE_TIME) / F_CPU)
#define OUTPUT_CLAMP true
#define P_CONTROL    true
#define I_CONTROL    true
#define D_CONTROL    true
// #define Kp 2.8
// #define Ki 3.6
// #define Kd 5.5

// -----* algorithm/motoMap *-----
#ifdef  __motorMap__
#define CROSS_MODE  0
#define DIRECT_MODE 1
#endif

// -----* base/IO  *-----
#define HIGH 1
#define LOW  0
#define OUTPUT 1
#define INPUT  0

// -----* base/SPI *-----
#define MASTER_MODE 0
#define SLAVE_MODE  1

// -----* base/USART *-----

// -----* base/PWM *-----
#define FAST_PWM          0
#define PHASE_CORRECT_PWM 1
// following is defined for Arduino Pro mini :
#define PWM_PIN3  0
#define PWM_PIN5  1
#define PWM_PIN6  2
#define PWM_PIN9  3
#define PWM_PIN10 4
#define PWM_PIN11 5

// output register alias
#define PWM_PORT_0 DDRD
#define PWM_PIN_0  PD3
#define PWM_PORT_1 DDRD
#define PWM_PIN_1  PD5
#define PWM_PORT_2 DDRD
#define PWM_PIN_2  PD6
#define PWM_PORT_3 DDRB
#define PWM_PIN_3  PB1
#define PWM_PORT_4 DDRB
#define PWM_PIN_4  PB2
#define PWM_PORT_5 DDRB
#define PWM_PIN_5  PB3

// -----* core/IMU *-----
#ifdef  __IMU__
// complementary filter ratio
#define Ka 1
#define Kb 1.5
#define NORMAL_ACC (Ka/(Ka+Kb))
#define NORMAL_GYR (Kb/(Ka+Kb))
#define ARC_PI 57.2975 // a shortcut of 180/pi
#define SAMPLE_TIME 100 // sample time = 100ms
#endif

#endif
