# Makefile for LiteSubSys

SRC=src
BIN=bin
OBJ=/tmp/obj

INC= \
	-I ${SRC} \
	-I ${SRC}/core \
	-I ${SRC}/modules/power \
	-I ${SRC}/modules/power/events \
	-I ${SRC}/modules/power/handlers \
	-I ${SRC}/modules/lighting \
	-I ${SRC}/modules/lighting/events \
	-I ${SRC}/modules/lighting/handlers \

OBJLIST= \
	${OBJ}/socket.o \
	${OBJ}/event.o \
	${OBJ}/event_factory.o \
	${OBJ}/event_manager.o \
	${OBJ}/listener.o \
	${OBJ}/power.o \
	${OBJ}/main_power_on_handler.o \
	${OBJ}/main_power_off_handler.o \
	${OBJ}/lighting.o \
	${OBJ}/main_light_on_handler.o \
	${OBJ}/main_light_off_handler.o \

CC=g++ -std=c++17 -O3 ${INC} -c
CL=g++


##### app #####

${BIN}/litesubsys: \
			${BIN} \
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

##### network ####

${OBJ}/socket.o: \
			${OBJ} \
			${SRC}/core/socket.cpp \
			${SRC}/core/socket.h
	${CC} \
		${SRC}/core/socket.cpp \
		-o ${OBJ}/socket.o

##### core ####

${OBJ}/event.o: \
			${OBJ} \
			${SRC}/core/event.cpp \
			${SRC}/core/event.h
	${CC} \
		${SRC}/core/event.cpp \
		-o ${OBJ}/event.o

${OBJ}/event_factory.o: \
			${OBJ} \
			${SRC}/core/event_factory.cpp \
			${SRC}/core/event_factory.h
	${CC} \
		${SRC}/core/event_factory.cpp \
		-o ${OBJ}/event_factory.o

${OBJ}/event_manager.o: \
			${OBJ} \
			${SRC}/core/event_manager.cpp \
			${SRC}/core/event_manager.h
	${CC} \
		${SRC}/core/event_manager.cpp \
		-o ${OBJ}/event_manager.o

${OBJ}/listener.o: \
			${OBJ} \
			${SRC}/core/listener.cpp \
			${SRC}/core/listener.h
	${CC} \
		${SRC}/core/listener.cpp \
		-o ${OBJ}/listener.o


##### power module ####

${OBJ}/power.o: \
			${OBJ} \
			${SRC}/modules/power/power.cpp \
			${SRC}/modules/power/power.h
	${CC} \
		${SRC}/modules/power/power.cpp \
		-o ${OBJ}/power.o

${OBJ}/main_power_on_handler.o: \
			${OBJ} \
			${SRC}/modules/power/handlers/main_power_on_handler.cpp \
			${SRC}/modules/power/handlers/main_power_on_handler.h
	${CC} \
		${SRC}/modules/power/handlers/main_power_on_handler.cpp \
		-o ${OBJ}/main_power_on_handler.o

${OBJ}/main_power_off_handler.o: \
			${OBJ} \
			${SRC}/modules/power/handlers/main_power_off_handler.cpp \
			${SRC}/modules/power/handlers/main_power_off_handler.h
	${CC} \
		${SRC}/modules/power/handlers/main_power_off_handler.cpp \
		-o ${OBJ}/main_power_off_handler.o


##### lighting module ####

${OBJ}/lighting.o: \
			${OBJ} \
			${SRC}/modules/lighting/lighting.cpp \
			${SRC}/modules/lighting/lighting.h
	${CC} \
		${SRC}/modules/lighting/lighting.cpp \
		-o ${OBJ}/lighting.o

${OBJ}/main_light_on_handler.o: \
			${OBJ} \
			${SRC}/modules/lighting/handlers/main_light_on_handler.cpp \
			${SRC}/modules/lighting/handlers/main_light_on_handler.h
	${CC} \
		${SRC}/modules/lighting/handlers/main_light_on_handler.cpp \
		-o ${OBJ}/main_light_on_handler.o

${OBJ}/main_light_off_handler.o: \
			${OBJ} \
			${SRC}/modules/lighting/handlers/main_light_off_handler.cpp \
			${SRC}/modules/lighting/handlers/main_light_off_handler.h
	${CC} \
		${SRC}/modules/lighting/handlers/main_light_off_handler.cpp \
		-o ${OBJ}/main_light_off_handler.o
