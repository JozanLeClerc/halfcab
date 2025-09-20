# =====================
# ====  ===============
# =====================
# ===   ===   ====   ==
# ====  ==     ==  =  =
# ====  ==  =  ==     =
# ====  ==  =  ==  ====
# ====  ==  =  ==  =  =
# =  =  ===   ====   ==
# ==   ================
# =====================
#
# halfcab: Makefile
# Fri, 19 Sep 2025 23:48:21 +0200
# joe <rbo@gmx.us>
#
# GNU Makefile

default: debug

SHELL		:= /bin/sh
OS			 = $(shell /usr/bin/uname)

ESP_DIR		 = esp/halfcab/
OBJ_DIR		 = obj/
SRC_DIR		 = src/
TRG_DIR		 = ./

ESP_FQBN	 = esp8266:esp8266:d1_mini
ESP_DEV		 = /dev/ttyUSB0

TARGET		 = hc

ESP_NAME	 = halfcab.ino

SRC_NAME	 = c_halfcab

SRCS		 = $(addprefix ${SRC_DIR}, $(addsuffix .c, ${SRC_NAME}))
INCS		 = $(addprefix ${SRC_DIR}, $(addsuffix .h, ${SRC_NAME}))
OBJS		 = $(patsubst ${SRC_DIR}%.c, ${OBJ_DIR}%.c.o, ${SRCS})

ARDUINO		 = arduino-cli
CC			 = cc
CFLAGS		 = -std=c89
CFLAGS		+= -Wall
CFLAGS		+= -Wextra
CFLAGS		+= -Werror
CFLAGS		+= -pedantic
CFLAGS		+= -march=haswell
CFLAGS		+= -O2
CFLAGS		+= -pipe
# ifeq (${OS}, Linux)
# CFLAGS		+= -D_GNU_SOURCE
# endif

ifeq (${OS}, Linux)
CINCS		 = -isystem /usr/include
endif

MKDIR		 = mkdir -p
RMDIR		 = rmdir
RM			 = rm -rf

${OBJ_DIR}%.c.o:	${SRC_DIR}%.c ${INCS} Makefile
	${CC} ${CFLAGS} -c ${CINCS} -o $@ $<

${OBJ_DIR}:
	${MKDIR} ${OBJ_DIR}

${TRG_DIR}${TARGET}:	${OBJ_DIR} ${OBJS}
	${CC} ${CFLAGS} -o $@ ${OBJS} ${LDFLAGS}

debug: CFLAGS += -O0
debug: CFLAGS += -g3
debug: all

asan: CFLAGS += -O0
asan: CFLAGS += -g3
asan: CFLAGS += -fsanitize=address
asan: all

clean:
	${RM} ${OBJS} vgcore.* ${TARGET}.core ${TARGET} ${OBJ_DIR}

esp:
	${ARDUINO} compile -v -j8 --warnings all --fqbn ${ESP_FQBN} ${SRC_DIR}${ESP_DIR}
	${ARDUINO} upload -p ${ESP_DEV} --fqbn ${ESP_FQBN} ${SRC_DIR}${ESP_DIR}

attach:
	${ARDUINO} board attach -p ${ESP_DEV} -b ${ESP_FQBN} ${SRC_DIR}${ESP_DIR}${ESP_NAME}

mon:
	${ARDUINO} monitor -p ${ESP_DEV} -b ${ESP_FQBN} --config 115200 --config 'rts=off' --config 'dtr=off' --quiet

all: esp ${TRG_DIR}${TARGET}

run: debug
	${TRG_DIR}${TARGET}

.PHONY: esp attach mon hc
