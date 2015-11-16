export MCU=atmega328
export MAKE=/usr/local/CrossPack-AVR/bin/avr-gcc
export BUILD_PATH=build
export MAKE_FLAGS= -g -Os -std=c++11 -mmcu=$(MCU)
export COMPILE=$(MAKE) $(MAKE_FLAGS)

all : TWI.o IMU.o container.h PID.h PWM.o motorMap.o util.h SPI.h sonar.o IO.o Main.o USART.o
	cd $(BUILD_PATH) && \
	$(COMPILE) Main.o TWI.o IMU.o motorMap.o IO.o sonar.o -o psychic-aero.elf && \
	avr-objcopy -j .text -j .data -O ihex psychic-aero.elf psychic-aero.hex

clean :
	rm build/*

TWI.o : config/config.h base/TWI.cpp base/TWI.h
	$(MAKE) -Os -mmcu=$(MCU) -c -std=c++11 base/TWI.cpp -o $(BUILD_PATH)/TWI.o

IMU.o : config/Registers.h core/IMU.h core/IMU.cpp base/container.hpp
	$(MAKE) -Os -mmcu=$(MCU) -c -std=c++11 core/IMU.cpp -o $(BUILD_PATH)/IMU.o

container.h : base/container.hpp
	$(MAKE) -Os -mmcu=$(MCU) -std=c++11 base/container.hpp -o $(BUILD_PATH)/container.h.gch

PID.h : algorithm/PID.hpp
	$(MAKE) -Os -mmcu=$(MCU) -std=c++11 algorithm/PID.hpp -o $(BUILD_PATH)/PID.h.gch

PWM.o : config/config.h
	$(MAKE) -Os -mmcu=$(MCU) -c -std=c++11 base/PWM.cpp -o $(BUILD_PATH)/PWM.o

motorMap.o : algorithm/motorMap.h algorithm/motorMap.cpp
	$(MAKE) -Os -mmcu=$(MCU) -c -std=c++11 algorithm/motorMap.cpp -o $(BUILD_PATH)/motorMap.o

util.h : util/util.template.hpp
	$(MAKE) -Os -mmcu=$(MCU) -std=c++11 util/util.template.hpp -o $(BUILD_PATH)/util.h.gch

SPI.h : base/SPI.template.hpp
	$(MAKE) $(MAKE_FLAGS) base/SPI.template.hpp -o $(BUILD_PATH)/SPI.h.gch

USART.o : base/USART.h base/USART.cpp
	$(COMPILE) -c base/USART.cpp -o $(BUILD_PATH)/USART.o

IO.o : base/IO.h base/IO.cpp
	$(COMPILE) -c base/IO.cpp -o $(BUILD_PATH)/IO.o

sonar.o : module/sonar.h module/sonar.cpp IO.o
	$(COMPILE) -c module/sonar.cpp -o $(BUILD_PATH)/sonar.o

Motor.o : core/Motor.h core/Motor.cpp
	$(COMPILE) -c core/Motor.cpp -o $(BUILD_PATH)/Motor.o

Main.o : Main.cpp
	$(COMPILE) -c Main.cpp -o $(BUILD_PATH)/Main.o
