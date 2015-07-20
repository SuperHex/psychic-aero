export MCU=atmega328
export MAKE=/usr/local/CrossPack-AVR/bin/avr-gcc
export BUILD_PATH=build
export MAKE_FLAGS= -Os -std=c++11 -mmcu=$(MCU)

all : I2C.o IMU.o container.h PID.h PWM.o motorMap.o util.h SPI.h
	cd $(BUILD_PATH) && \
	$(MAKE) I2C.o IMU.o motorMap.o

clean :
	rm build/*

I2C.o : config/config.h base/I2C.cpp base/I2C.h
	$(MAKE) -Os -mmcu=$(MCU) -c -std=c++11 base/I2C.cpp -o $(BUILD_PATH)/I2C.o

IMU.o : config/Registers.h core/IMU.h core/IMU.cpp base/container.hpp
	$(MAKE) -Os -mmcu=$(MCU) -c -std=c++11 core/IMU.cpp -o $(BUILD_PATH)/IMU.o

container.h : base/container.hpp
	$(MAKE) -Os -mmcu=$(MCU) -std=c++11 base/container.hpp -o $(BUILD_PATH)/container.h.gch

PID.h : algorithm/PID.hpp
	$(MAKE) -Os -mmcu=$(MCU) -std=c++11 algorithm/PID.hpp -o $(BUILD_PATH)/PID.h.gch

PWM.o : config/config.h
	$(MAKE) -Os -mmcu=$(MCU) -c -std=c++11 base/PWM.template.hpp -o $(BUILD_PATH)/PWM.h.gch

motorMap.o : algorithm/motorMap.h algorithm/motorMap.cpp
	$(MAKE) -Os -mmcu=$(MCU) -c -std=c++11 algorithm/motorMap.cpp -o $(BUILD_PATH)/motorMap.o

util.h : util/util.template.hpp
	$(MAKE) -Os -mmcu=$(MCU) -std=c++11 util/util.template.hpp -o $(BUILD_PATH)/util.h.gch

SPI.h : base/SPI.template.hpp
	$(MAKE) $(MAKE_FLAGS) base/SPI.template.hpp -o $(BUILD_PATH)/SPI.h.gch
