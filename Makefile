PRG=./w
INC_DIR=./include
CFLAGS= -g -I${INC_DIR}
LIBS=
CFG=../config

OBJS= main.o bot.o server.o signal.o file.o parse.o list_add.o list_rem.o list_get.o str_tools.o \
u_misc.o help.o irc_proto.o
	
INC=${INC_DIR}/bot.h ${INC_DIR}/proto.h $(INC_DIR}/global.h ${INC_DIR}/structs.h

${PRG}: ${OBJS} 
	cc -o $@ ${OBJS} ${LIBS}

${OBJS}: ${INC_DIR}/bot.h
${OBJS}: ${INC_DIR}/proto.h
${OBJS}: ${INC_DIR}/globals.h
${OBJS}: ${INC_DIR}/structs.h

clean:
	rm -f ${OBJS} ${PRG} *.pid
