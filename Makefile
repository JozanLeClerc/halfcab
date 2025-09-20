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

default: esp

ESP_DIR		 = esp/halfcab/
OBJ_DIR		 = obj/
SRC_DIR		 = src/
TRGT_DIR	 = ./

ESP_FQBN	 = esp8266:esp8266:d1_mini
ESP_DEV		 = /dev/ttyUSB0

TRGT_NAME	 = hc

ESP_NAME	 = halfcab.ino

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

esp:
	${ARDUINO} compile -v -j8 --warnings all --fqbn ${ESP_FQBN} ${ESP_DIR}
	${ARDUINO} upload -p ${ESP_DEV} --fqbn ${ESP_FQBN} ${ESP_DIR}

attach:
	${ARDUINO} board attach -p ${ESP_DEV} -b ${ESP_FQBN} ${ESP_DIR}${ESP_NAME}

mon:
	${ARDUINO} monitor -p ${ESP_DEV} -b ${ESP_FQBN} --config 115200 --config 'rts=off' --config 'dtr=off' --quiet


.PHONY: esp attach mon
