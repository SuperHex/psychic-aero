export MCU=atmega8
export MAKE=/usr/local/CrossPack-AVR/bin/avr-gcc
export BUILD_PATH=build

all : I2C.o IMU.o container.o
	$(MAKE) build/I2C.o build/IMU.o build/container.o

clean :
	rm build/*.o
	rm build/*.a

I2C.o : base/I2C.cpp base/I2C.h
    $(MAKE) -Os -mmcu=$(MCU) -c base/I2C.cpp -o $(BUILD_PATH)/I2C.o

IMU.o : config/Registers.h core/IMU.h core/IMU.cpp base/container.hpp
	$(MAKE) -Os -mmcu=$(MCU) -c -std=c++11 core/IMU.cpp -o $(BUILD_PATH)/IMU.o

container.o : base/container.hpp
	$(MAKE) -Os -mmcu=$(MCU) -c -std=c++11 base/container.hpp -o $(BUILD_PATH)/container.o
