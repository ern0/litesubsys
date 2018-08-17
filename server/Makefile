# Makefile for LiteSubSys

SRC=src
BIN=bin
OBJ=/tmp/obj

CC=g++ -O3 -c
CL=g++ -pthread

INC= \
	${SRC} \
	${SRC}/core \
	${SRC}/modules/power \
	${SRC}/modules/power/events \
	${SRC}/modules/power/handlers \
	${SRC}/modules/lighting \
	${SRC}/modules/lighting/events \
	${SRC}/modules/lighting/handlers \

OBJLIST= \
	${OBJ}/event.o \
	${OBJ}/event_manager.o \
	${OBJ}/listener.o \
	${OBJ}/power.o \
	${OBJ}/main_power_on_handler.o \
	${OBJ}/main_power_off_handler.o \
	${OBJ}/lighting.o \
	${OBJ}/main_lighting_on_handler.o \
	${OBJ}/main_lighting_off_handler.o \


##### app #####

${BIN}/litesubsys: \
			${OBJLIST}
	${CL} \
		${OBJLIST} \
		-o ${BIN}/litesubsys

about:
	# makefile for litesubsys


##### misc ####

${BIN}:
	mkdir -p ${BIN}

${OBJ}:
	mkdir -p ${OBJ}

clean: ${OBJ}
	rm -rf ${OBJ}/*.o

all: clean ${BIN}/litesubsys


##### core ####

${OBJ}/event.o: \
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

${OBJ}/listener.o: \
			${SRC}/core/listener.cpp \
			${SRC}/core/listener.h
	${CC} \
		${SRC}/core/listener.cpp \
		-o ${OBJ}/listener.cpp


##### power module ####

${OBJ}/power.o: \
			${SRC}/modules/power/power.cpp \
			${SRC}/modules/power/power.h
	${CC} \
		${SRC}/modules/power/power.cpp \
		-o ${OBJ}/power.o

${OBJ}/main_power_on_handler.o: \
			${SRC}/modules/power/handlers/main_power_on_handler.cpp \
			${SRC}/modules/power/handlers/main_power_on_handler.h
	${CC} \
		${SRC}/modules/power/handlers/main_power_on_handler.cpp \
		-o ${OBJ}/main_power_on_handler.o

${OBJ}/main_power_off_handler.o: \
			${SRC}/modules/power/handlers/main_power_off_handler.cpp \
			${SRC}/modules/power/handlers/main_power_off_handler.h
	${CC} \
		${SRC}/modules/power/handlers/main_power_off_handler.cpp \
		-o ${OBJ}/main_power_off_handler.o


##### lighting module ####

${OBJ}/lighting.o: \
			${SRC}/modules/lighting/lighting.cpp \
			${SRC}/modules/lighting/lighting.h
	${CC} \
		${SRC}/modules/lighting/lighting.cpp \
		-o ${OBJ}/lighting.o

${OBJ}/main_lighting_on_handler.o: \
			${SRC}/modules/lighting/handlers/main_light_on_handler.cpp \
			${SRC}/modules/lighting/handlers/main_light_on_handler.h
	${CC} \
		${SRC}/modules/lighting/handlers/main_light_on_handler.cpp \
		-o ${OBJ}/main_lighting_on_handler.o

${OBJ}/main_lighting_off_handler.o: \
			${SRC}/modules/lighting/handlers/main_light_off_handler.cpp \
			${SRC}/modules/lighting/handlers/main_light_off_handler.h
	${CC} \
		${SRC}/modules/lighting/handlers/main_light_off_handler.cpp \
		-o ${OBJ}/main_light_off_handler.o
