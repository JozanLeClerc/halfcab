/*
 * =====================
 * ====  ===============
 * =====================
 * ===   ===   ====   ==
 * ====  ==     ==  =  =
 * ====  ==  =  ==     =
 * ====  ==  =  ==  ====
 * ====  ==  =  ==  =  =
 * =  =  ===   ====   ==
 * ==   ================
 * =====================
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2025, joe
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the organization nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ''AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * halfcab: src/c_halfcab.c
 * Sat, 20 Sep 2025 16:24:57 +0200
 * joe <rbo@gmx.us>
 *
 * the main
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "c_defines.h"

static char
param_esp_com
(int fd,
 const char prog_name[])
{
	struct termios tty;

	bzero(&tty, sizeof(tty));
	if (tcgetattr(fd, &tty) != 0) {
		dprintf(
			STDERR_FILENO,
			"%s: %s: %s\n",
			prog_name,
			"tcgetattr error with esp",
			strerror(errno)
		);
		return (1);
	}
	cfsetospeed(&tty, B115200);
	cfsetispeed(&tty, B115200);
	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; /* 8-bit chars */
	tty.c_iflag &= ~IGNBRK;         /* disable break processing */
	tty.c_lflag = 0;                /* no signaling chars, no echo, */
	tty.c_oflag = 0;                /* no remapping, no delays */
	tty.c_cc[VMIN] = 1;             /* read doesn't block */
	tty.c_cc[VTIME] = 5;            /* 0.5 seconds read timeout */
	tty.c_iflag &= ~(IXON | IXOFF | IXANY); /* shut off xon/xoff ctrl */
	tty.c_cflag |= (CLOCAL | CREAD); /* ignore modem controls, enable reading */
	tty.c_cflag &= ~(PARENB | PARODD);      /* no parity */
	tty.c_cflag &= ~CSTOPB;         /* 1 stop bit */
	tty.c_cflag &= ~CRTSCTS;        /* no hardware flow control */
	if(tcsetattr(fd, TCSANOW, &tty) != 0) {
		dprintf(
			STDERR_FILENO,
			"%s: %s: %s\n",
			prog_name,
			"tcgetattr error with esp",
			strerror(errno)
		);
		return (1);
	}
	return (0);
}

static int
open_esp(const char prog_name[])
{
	int fd;

	fd = open(PORT_NAME, O_WRONLY | O_NOCTTY | O_SYNC);
	if (fd < 0) {
		dprintf(
			STDERR_FILENO,
			"%s: %s: %s\n",
			prog_name,
			"error opening esp",
			strerror(errno)
		);
		return (-1);
	}
	return (fd);
}

int
main
(int		 argc,
 const char* argv[])
{
	const char* prog_name = argv[0];
	int fd;
	int i;
	unsigned char com[4];
	unsigned char leds[NUM_LEDS * 3];

	fd = open_esp(prog_name);
	if (fd < 0) {
		return (EXIT_FAILURE);
	}
	if (param_esp_com(fd, prog_name) != 0) {
		close(fd);
		return (EXIT_FAILURE);
	}
	if (argc < 4) {
		com[0] = 0xfe;
		com[1] = 0x00;
		com[2] = 0xaa;
		com[3] = 0xaa;
		i = 0;
		while (i < NUM_LEDS * 3) {
			memcpy(leds + i, com + 1, 3 * sizeof(unsigned char));
			i += 3;
		}
		write(fd, &com, 1 * sizeof(unsigned char));
		write(fd, &leds, (NUM_LEDS * 3) * sizeof(unsigned char));
	} else {
		com[0] = 0xff;
		i = 1;
		while (i < 4) {
			com[i] = atoi(argv[i]);
			i++;
		}
		write(fd, &com, 4 * sizeof(unsigned char));
	}
	close(fd);
	return (EXIT_SUCCESS);
}
