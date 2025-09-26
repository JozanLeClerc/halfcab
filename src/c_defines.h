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
 * halfcab: src/c_defines.h
 * Sat, 20 Sep 2025 17:24:52 +0200
 * joe <rbo@gmx.us>
 */

#ifndef __C_DEFINES_H__
#define __C_DEFINES_H__

#define PORT_NAME    "/dev/ttyUSB0"
#define SCREEN_W    2560
#define SCREEN_H    1440

#define DATA_PIN    D2
#define NUM_LEDS    60
#define BRIGHTNESS  254
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

#define BLACK CRGB(0, 0, 0)
#define RED   CRGB(255, 0, 0)
#define GREEN CRGB(0, 255, 0)
#define BLUE  CRGB(0, 0, 255)
#define GRUV  CRGB(255, 80, 0)

#define START_X 0
#define RANDOM_PX_COUNT 30

enum bool_e {
	FALSE,
	TRUE
};

#endif /* __C_DEFINES_H__ */
