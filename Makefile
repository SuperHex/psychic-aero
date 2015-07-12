export MCU=atmega8
export MAKE=/usr/local/CrossPack-AVR/bin/avr-gcc
export BUILD_PATH=build

I2C.o : base/I2C.cpp base/I2C.h
    $(MAKE) -Os -mmcu=$(MCU) -c base/I2C.cpp -o $(BUILD_PATH)/I2C.o

IMU.o : config/Registers.h core/IMU.h core/IMU.cpp
	$(MAKE) -Os -mmcu=$(MCU) -c core/IMU.cpp -o $(BUILD_PATH)/IMU.o

all : I2C.o IMU.o
	$(MAKE) I2C.o IMU.o

clean :
	rm build/*.o
	rm build/*.a
