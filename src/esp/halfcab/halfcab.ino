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
 * halfcab: esp/halfcab/halfcab.ino
 * Sat, 20 Sep 2025 00:17:38 +0200
 * joe <rbo@gmx.us>
 *
 * this is going straight to the esp
 */

#include <FastLED.h>

#include "c_defines.h"

CRGB leds[NUM_LEDS];

byte
read_byte()
{
    while (Serial.available() <= 0) {
        /* empty */
    }
    return (Serial.read());
}

void
fill(CRGB color)
{
    uint8_t i;

    i = 0;
    while (i < NUM_LEDS) {
        leds[i] = color;
        i++;
    }
    FastLED.show();
}

void
blink(void)
{
    fill(RED);
    delay(60);
    fill(BLACK);
    delay(60);
    fill(RED);
    delay(60);
    fill(BLACK);
    delay(60);
    fill(RED);
    delay(60);
    fill(BLACK);
    delay(1000);
}

void
plain(void)
{
    CRGB color;

    color = BLACK;
    color.r = read_byte();
    color.g = read_byte();
    color.b = read_byte();
    fill(color);
}

void
dynamic(void)
{
    uint8_t i;

    i = 0;
    while (i < NUM_LEDS) {
        leds[i].r = read_byte();
        leds[i].g = read_byte();
        leds[i].b = read_byte();
        i++;
    }
    FastLED.show();
}

void
setup(void)
{
    Serial.begin(115200);

    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    fill(BLACK);
    blink();
}

void
loop(void)
{
    uint8_t com;

    com = 0;
    com = read_byte();
    if (com == 0xff) {
        dynamic();
    } else if (com == 0xfe) {
        plain();
    } else {
        fill(BLUE);
    }
}
