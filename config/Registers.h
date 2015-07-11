//
//  Registers.h
//  Utopia
//
//  Created by Soei Wong on 15/6/30.
//  Copyright (c) 2015年 Soei Wong. All rights reserved.
//

#ifndef Utopia_Registers_h
#define Utopia_Registers_h

// First we will define registers on MPU6050
// Here comes the accelerate
#define ACC_ADD 0x00
#define ACC_X_H 0x3B
#define ACC_X_L 0x3C
#define ACC_Y_H 0x3D
#define ACC_Y_L 0x3E
#define ACC_Z_H 0x3F
#define ACC_Z_L 0x40

// and the gyro..
#define GYRO_ADD 0x00
#define GYRO_X_H 0x43
#define GYRO_X_L 0x44
#define GYRO_Y_H 0x45
#define GYRO_Y_L 0x46
#define GYRO_Z_H 0x47
#define GYRO_Z_L 0x48

#endif
