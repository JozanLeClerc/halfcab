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

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "c_defines.h"
#include "c_screen.h"

static void
fill_led
(unsigned char leds[],
 const int	i,
 Display*	disp,
 XImage*	img,
 const int	min_x,
 const int	max_x,
 const int	min_y,
 const int	max_y)
{
	XColor c;

	(void)min_x;
	(void)max_x;
	(void)min_y;
	(void)max_y;
	c.pixel = XGetPixel(img, 0, 0);
	XQueryColor(disp, DefaultColormap(disp, DefaultScreen(disp)), &c);
	leds[i + 0] = c.red;
	leds[i + 1] = c.green;
	leds[i + 2] = c.blue;
}

void
c_get_screen_colors
(unsigned char	leds[],
 Display*		disp)
{
	XImage* img;
	const int top_leds  = NUM_LEDS / 2;
	const int side_leds	= NUM_LEDS / 4;
	const int top_px_per_led  = SCREEN_W / top_leds;
	const int side_px_per_led = SCREEN_H / side_leds;
	int i;

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
	fill_led(
		leds, i,
		disp, img,
		0, side_px_per_led,
		VERT_PIXEL_GAP + (0 * side_px_per_led),
		VERT_PIXEL_GAP + ((0 + 1) * side_px_per_led)
		);
	(void)top_px_per_led;
	XDestroyImage(img);
}
