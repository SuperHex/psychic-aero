export MCU=atmega8
export MAKE=/usr/local/CrossPack-AVR/bin/avr-gcc
export BUILD_PATH=build

all : I2C.o IMU.o container.h.gch PID.h.gch
	cd $(BUILD_PATH) && \
	$(MAKE) I2C.o IMU.o

clean :
	rm build/*.o
	rm build/*.out
	rm build/*.h.gch

I2C.o : config/config.h base/I2C.cpp base/I2C.h
	$(MAKE) -Os -mmcu=$(MCU) -c -std=c++11 base/I2C.cpp -o $(BUILD_PATH)/I2C.o

IMU.o : config/Registers.h core/IMU.h core/IMU.cpp base/container.hpp
	$(MAKE) -Os -mmcu=$(MCU) -c -std=c++11 core/IMU.cpp -o $(BUILD_PATH)/IMU.o

container.h.gch : base/container.hpp
	$(MAKE) -Os -mmcu=$(MCU) -std=c++11 base/container.hpp -o $(BUILD_PATH)/container.h.gch

PID.h.gch : algorithm/PID.hpp
	$(MAKE) -Os -mmcu=$(MCU) -std=c++11 algorithm/PID.hpp -o $(BUILD_PATH)/PID.h.gch
