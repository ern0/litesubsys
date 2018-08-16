about:
	# makefile for litesubsys

PLATFORM=$(shell ../../util/platform.sh)

SRC=src
BIN=bin

CC=g++ -std=c++11 -O3
CL=g++ -pthread

INC=\
	${SRC} \
	${SRC}/core \
	${SRC}/modules/power \
	${SRC}/modules/power/events \
	${SRC}/modules/power/handlers \
	${SRC}/modules/lighting \
	${SRC}/modules/lighting/events \
	${SRC}/modules/lighting/handlers \

OBJLIST=\
	${OBJ}/event.o \
	${OBJ}/event_manager.o \
	${OBJ}/listener.o \


##### app #####

${BIN}/litesubsys: \
			${OBJLIST}
	${CL} \
		${OBJLIST} \
		-o ${BIN}/litesubsys


##### core ####

${OBJ}/event.o:
			${SRC}/core/event.cpp \
			${SRC}/core/event.h
	${CC} \
		${SRC}/core/event.cpp \
		-o ${OBJ}/event.cpp

${OBJ}/event_manager.o: \
			${SRC}/core/event_manager.cpp \
			${SRC}/core/event_manager.h
	${CC} \
		${SRC}/core/event_manager.cpp \
		-o ${OBJ}/event_manager.cpp

${OBJ}/listener.o:
			${SRC}/core/listener.cpp \
			${SRC}/core/listener.h
	${CC} \
		${SRC}/core/listener.cpp \
		-o ${OBJ}/listener.cpp


##### power module ####

${OBJ}/power.o:
			${SRC}/modules/power/power.cpp \
			${SRC}/modules/power/power.h
	${CC} \
		${SRC}/modules/power/power.cpp \
		-o ${OBJ}/power.o

${OBJ}/main_power_on_handler.o:
			${SRC}/modules/power/handlers/main_power_on_handler.cpp \
			${SRC}/modules/power/handlers/main_power_on_handler.h
	${CC} \
		${SRC}/modules/power/handlers/main_power_on_handler.cpp \
		-o ${OBJ}/main_power_on_handler.o

${OBJ}/main_power_off_handler.o:
			${SRC}/modules/power/handlers/main_power_off_handler.cpp \
			${SRC}/modules/power/handlers/main_power_off_handler.h
	${CC} \
		${SRC}/modules/power/handlers/main_power_off_handler.cpp \
		-o ${OBJ}/main_power_off_handler.o


##### lighting module ####

${OBJ}/lighting.o:
			${SRC}/modules/lighting/lighting.cpp \
			${SRC}/modules/lighting/lighting.h
	${CC} \
		${SRC}/modules/lighting/lighting.cpp \
		-o ${OBJ}/lighting.o

${OBJ}/main_lighting_on_handler.o:
			${SRC}/modules/lighting/handlers/main_light_on_handler.cpp \
			${SRC}/modules/lighting/handlers/main_light_on_handler.h
	${CC} \
		${SRC}/modules/lighting/handlers/main_light_on_handler.cpp \
		-o ${OBJ}/main_lighting_on_handler.o

${OBJ}/main_lighting_off_handler.o:
			${SRC}/modules/lighting/handlers/main_light_off_handler.cpp \
			${SRC}/modules/lighting/handlers/main_light_off_handler.h
	${CC} \
		${SRC}/modules/lighting/handlers/main_light_off_handler.cpp \
		-o ${OBJ}/main_light_off_handler.o



${OBJ}/modules/power/power.cpp
${OBJ}/modules/power/handlers/main_power_on_handler.cpp
${OBJ}/modules/power/handlers/main_power_off_handler.cpp

${OBJ}/modules/lighting/lighting.cpp
${OBJ}/modules/lighting/handlers/main_light_on_handler.cpp
${OBJ}/modules/lighting/handlers/main_light_off_handler.cpp


${BIN}/channelsniffer: \
		Makefile \
		${BIN} ${OBJ} ${OBJLIST} \
		${SRC}/channelsniffer.hpp ${SRC}/channelsniffer.cpp
	./about.sh > /tmp/snify/channelsniffer/about.cpp
	${CL} \
		${OBJLIST} \
		-o ${BIN}/channelsniffer \
		${SRC}/channelsniffer.cpp

${OBJ}/posixino.o: \
		Makefile \
		${PSRC}/posixino.hpp \
		${PSRC}/posixino.cpp
	${CC} \
		-o ${OBJ}/posixino.o \
		${PSRC}/posixino.cpp

${OBJ}/MacAddress.o: \
		Makefile \
		${SRC}/configuration.hpp \
		${SRC}/MacAddress.hpp \
		${SRC}/MacAddress.cpp
	${CC} \
		-DTEST \
		-o ${OBJ}/MacAddress.o \
		${SRC}/MacAddress.cpp

${OBJ}/Timer.o: \
		Makefile \
		${OBJ}/posixino.o \
 		${SRC}/Timer.hpp \
 		${SRC}/Timer.cpp
	${CC} \
		-o ${OBJ}/Timer.o \
		${SRC}/Timer.cpp

${OBJ}/PacketInspector.o: \
		Makefile \
		${SRC}/MacAddress.hpp \
		${SRC}/Timer.hpp \
		${SRC}/PacketInspector.hpp \
		${SRC}/PacketInspector.cpp \
		${SRC}/PacketInspector-debug.cpp
	${CC} \
		-o ${OBJ}/PacketInspector.o \
		${SRC}/PacketInspector.cpp

${OBJ}/Transmitter.o: \
		Makefile \
		${SRC}/MacAddress.hpp \
		${OBJ}/posixino.o \
		${SRC}/Transmitter.hpp \
		${SRC}/Transmitter.cpp
	${CC} \
		-o ${OBJ}/Transmitter.o \
		${SRC}/Transmitter.cpp

${OBJ}/Sniffer.o: \
		Makefile \
		${OBJ}/MacAddress.o \
		${OBJ}/Filter.o \
		${SRC}/Sniffer-posix.hpp \
		${SRC}/Sniffer-posix.cpp
	${CC} \
		-o ${OBJ}/Sniffer.o \
		${SRC}/Sniffer-posix.cpp

${OBJ}/ChannelSelect.o: \
		Makefile \
		${SRC}/ChannelSelect-posix.hpp \
		${SRC}/ChannelSelect-posix.cpp
	${CC} \
		-o ${OBJ}/ChannelSelect.o \
		${SRC}/ChannelSelect-posix.cpp


${OBJ}/Filter.o: \
		Makefile \
		${SRC}/configuration.hpp \
		${SRC}/MacAddress.hpp \
		${SRC}/Slot.hpp \
		${SRC}/PacketInspector.hpp \
		${SRC}/Filter.hpp \
		${SRC}/Filter.cpp
	${CC} \
		-o ${OBJ}/Filter.o \
		${SRC}/Filter.cpp

${OBJ}/Slot.o: \
		Makefile \
		${SRC}/Timer.hpp \
		${SRC}/PacketInspector.hpp \
		${SRC}/Slot.hpp \
		${SRC}/Slot.cpp
	${CC} \
		-o ${OBJ}/Slot.o \
		${SRC}/Slot.cpp

#############################################################################

test: Makefile ${BIN} ${OBJ} \
		${BIN}/test-timer \
		${BIN}/test-filter-none \
		${BIN}/test-filter-broadcast \
		${BIN}/test-filter-duplication \
		${BIN}/test-filter-overflow \
		${BIN}/test-filter-purge

${OBJ}/posixino-test.o: \
		Makefile \
		${PSRC}/posixino.hpp \
		${PSRC}/posixino.cpp
	${CC} \
		-D POSIXINO_CONFIG_MAIN \
		-o ${OBJ}/posixino-test.o \
		${PSRC}/posixino.cpp

${OBJ}/test-Filter.o: \
		Makefile \
		${SRC}/configuration.hpp \
		${SRC}/MacAddress.hpp \
		${OBJ}/Slot.o \
		${OBJ}/test-PacketInspector.o \
		${SRC}/Filter.hpp \
		${SRC}/Filter.cpp
	${CC} \
		-DTEST \
		-o ${OBJ}/test-Filter.o \
		${TST}/wrapper-Filter.cpp

${OBJ}/test-PacketInspector.o: \
		Makefile \
		${SRC}/MacAddress.hpp \
		${SRC}/Timer.hpp \
		${SRC}/PacketInspector.hpp \
		${SRC}/PacketInspector.cpp \
		${SRC}/PacketInspector-debug.cpp
	${CC} \
		-DTEST \
		-o ${OBJ}/test-PacketInspector.o \
		${SRC}/PacketInspector.cpp

${OBJ}/wrapper-Timer.o: \
		Makefile \
		${TST}/configuration.hpp \
		${OBJ}/posixino-test.o \
 		${SRC}/Timer.hpp \
 		${SRC}/Timer.cpp \
 		${TST}/wrapper-Timer.cpp
	${CC} \
		-o ${OBJ}/wrapper-Timer.o \
		${TST}/wrapper-Timer.cpp

${OBJ}/mock-Transmitter.o: \
		test/mock-Transmitter.hpp \
		test/mock-Transmitter.cpp
	${CC} \
		-o ${OBJ}/mock-Transmitter.o \
		${TST}/mock-Transmitter.cpp


${BIN}/test-timer: \
		Makefile \
		${TST}/test.hpp \
		${TST}/configuration.hpp \
 		${OBJ}/posixino-test.o \
		${OBJ}/wrapper-Timer.o
	${CL} \
		${OBJ}/posixino-test.o \
		${OBJ}/wrapper-Timer.o \
		-o ${BIN}/test-timer \
		${TST}/test-timer.cpp

${BIN}/test-filter-none: \
		Makefile \
		${TST}/test.hpp \
		${TST}/configuration.hpp \
		${OBJ}/MacAddress.o \
		${OBJ}/test-Filter.o \
		${OBJ}/Slot.o \
		${OBJ}/Timer.o \
		${OBJ}/mock-Transmitter.o \
		${TST}/configuration.hpp \
		${TST}/test-filter-none.cpp
	${CL} \
		${OBJ}/posixino-test.o \
		${OBJ}/Timer.o \
		${OBJ}/test-Filter.o \
		${OBJ}/MacAddress.o \
		${OBJ}/Slot.o \
		${OBJ}/mock-Transmitter.o \
		-o ${BIN}/test-filter-none \
		${TST}/test-filter-none.cpp

${BIN}/test-filter-broadcast: \
		Makefile \
		${TST}/test.hpp \
		${TST}/configuration.hpp \
		${OBJ}/MacAddress.o \
		${OBJ}/test-Filter.o \
		${OBJ}/Slot.o \
		${OBJ}/Timer.o \
		${OBJ}/mock-Transmitter.o \
		${TST}/configuration.hpp \
		${TST}/test-filter-broadcast.cpp
	${CL} \
		${OBJ}/posixino-test.o \
		${OBJ}/Timer.o \
		${OBJ}/MacAddress.o \
		${OBJ}/test-Filter.o \
		${OBJ}/Slot.o \
		${OBJ}/mock-Transmitter.o \
		-o ${BIN}/test-filter-broadcast \
		${TST}/test-filter-broadcast.cpp

${BIN}/test-filter-duplication: \
		Makefile \
		${TST}/test.hpp \
		${TST}/configuration.hpp \
		${OBJ}/posixino-test.o \
		${OBJ}/Timer.o \
		${OBJ}/MacAddress.o \
		${OBJ}/test-Filter.o \
		${OBJ}/Slot.o \
		${OBJ}/mock-Transmitter.o \
		${TST}/configuration.hpp \
		${TST}/test-filter-duplication.cpp
	${CL} \
		${OBJ}/posixino-test.o \
		${OBJ}/Timer.o \
		${OBJ}/MacAddress.o \
		${OBJ}/test-Filter.o \
		${OBJ}/Slot.o \
		${OBJ}/mock-Transmitter.o \
		-o ${BIN}/test-filter-duplication \
		${TST}/test-filter-duplication.cpp

${BIN}/test-filter-overflow: \
		Makefile \
		${TST}/test.hpp \
		${TST}/configuration.hpp \
		${OBJ}/Timer.o \
		${OBJ}/MacAddress.o \
		${OBJ}/posixino-test.o \
		${OBJ}/test-Filter.o \
		${OBJ}/Slot.o \
		${OBJ}/mock-Transmitter.o \
		${TST}/test-filter-overflow.cpp
	${CL} \
		${OBJ}/posixino-test.o \
		${OBJ}/Timer.o \
		${OBJ}/MacAddress.o \
		${OBJ}/test-Filter.o \
		${OBJ}/Slot.o \
		${OBJ}/mock-Transmitter.o \
		-o ${BIN}/test-filter-overflow \
		${TST}/test-filter-overflow.cpp

${BIN}/test-filter-purge: \
		Makefile \
		${TST}/test.hpp \
		${TST}/configuration.hpp \
		${OBJ}/posixino-test.o \
		${OBJ}/Timer.o \
		${OBJ}/MacAddress.o \
		${OBJ}/test-Filter.o \
		${OBJ}/Slot.o \
		${OBJ}/mock-Transmitter.o \
		${TST}/test-filter-purge.cpp
	${CL} \
		${OBJ}/posixino-test.o \
		${OBJ}/Timer.o \
		${OBJ}/MacAddress.o \
		${OBJ}/test-Filter.o \
		${OBJ}/Slot.o \
		${OBJ}/mock-Transmitter.o \
		-o ${BIN}/test-filter-purge \
		${TST}/test-filter-purge.cpp

#############################################################################

${BIN}:
	mkdir -p ${BIN}

${OBJ}:
	mkdir -p ${OBJ}

clean: ${OBJ}
	rm -rf ${OBJ}/*.o about.cpp

all: clean ${BIN}/channelsniffer
