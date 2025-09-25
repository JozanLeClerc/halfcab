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
 * halfcab: src/c_screen.c
 * Wed, 24 Sep 2025 20:29:26 +0200
 * joe <rbo@gmx.us>
 */

#include <stdlib.h>
#include <string.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "c_defines.h"
#include "c_screen.h"

static int
c_rand
(short min,
 short max)
{
	return min + (rand() % (max - min));
}

static void
c_fill_led
(unsigned char	leds[],
 const int	 i,
 Display*	 disp,
 XImage*	 img,
 const short x_min,
 const short x_max,
 const short y_min,
 const short y_max)
{
	XColor c;
	unsigned int total[3];
	short j;
	short x;
	short y;

	bzero(&total, 3 * sizeof(unsigned int));
	j = 0;
	while (j < RANDOM_PX_COUNT) {
		x = c_rand(x_min, x_max);
		y = c_rand(y_min, y_max);
		j++;
		c.pixel = XGetPixel(img, x, y);
		XQueryColor(disp, DefaultColormap(disp, DefaultScreen(disp)), &c);
		total[0] += c.red;
		total[1] += c.green;
		total[2] += c.blue;
	}
	j = 0;
	while (j < 3) {
		leds[i + j] = (total[j] / 256) / RANDOM_PX_COUNT;
		j++;
	}
}

void
c_get_screen_colors
(unsigned char	leds[],
 Display*		disp,
 unsigned int	t)
{
	XImage* img;
	static const short top_leds		   = NUM_LEDS / 2;
	static const short side_leds	   = NUM_LEDS / 4;
	static const short top_px_per_led  = SCREEN_W / top_leds;
	static const short side_px_per_led = SCREEN_H / side_leds;
	short i;
	short j;

	srand(t);
	img = XGetImage(
		disp, RootWindow(disp, DefaultScreen(disp)),
		1920, 0,
		SCREEN_W, SCREEN_H,
		AllPlanes, ZPixmap
		);
	if (img == NULL) {
		return;
	}
	i = 0;
	j = 0;
	while (j < side_leds) {
		i = side_leds - j - 1;
		c_fill_led(
			leds, i * 3,
			disp, img,
			0, side_px_per_led,
			j * side_px_per_led,
			(j + 1) * side_px_per_led
			);
		j++;
	}
	i = 0;
	while (i < top_leds) {
		c_fill_led(
			leds, (side_leds * 3) + (i * 3),
			disp, img,
			i * top_px_per_led,
			(i + 1) * top_px_per_led,
			0, top_px_per_led
			);
		i++;
	}
	i = 0;
	while (i < side_leds) {
		c_fill_led(
			leds, (side_leds + top_leds + i) * 3,
			disp, img,
			SCREEN_W - side_px_per_led, SCREEN_W - 1,
			i * side_px_per_led, (i + 1) * side_px_per_led
			);
		i++;
	}
	XDestroyImage(img);
}
