/*
$Id:$

ST7565 LCD library!

Copyright (C) 2010 Limor Fried, Adafruit Industries

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

// some of this code was written by <cstone@pobox.com> originally; it is in the public domain.
*/

//#if ARDUINO >= 100
// #include "Arduino.h"
//#else
 #include "WProgram.h"
//#endif

#define swap(a, b) { uint8 t = a; a = b; b = t; }

#define _BV(a) ((uint8)(0x01<<(a)))

#define BLACK 1
#define WHITE 0

#define LCDWIDTH 128
#define LCDHEIGHT 64

#define CMD_DISPLAY_OFF   0xAE
#define CMD_DISPLAY_ON    0xAF

#define CMD_SET_DISP_START_LINE  0x40
#define CMD_SET_PAGE  0xB0

#define CMD_SET_COLUMN_UPPER  0x10
#define CMD_SET_COLUMN_LOWER  0x00

#define CMD_SET_ADC_NORMAL  0xA0
#define CMD_SET_ADC_REVERSE 0xA1

#define CMD_SET_DISP_NORMAL 0xA6
#define CMD_SET_DISP_REVERSE 0xA7

#define CMD_SET_ALLPTS_NORMAL 0xA4
#define CMD_SET_ALLPTS_ON  0xA5
#define CMD_SET_BIAS_9 0xA2 
#define CMD_SET_BIAS_7 0xA3

#define CMD_RMW  0xE0
#define CMD_RMW_CLEAR 0xEE
#define CMD_INTERNAL_RESET  0xE2
#define CMD_SET_COM_NORMAL  0xC0
#define CMD_SET_COM_REVERSE  0xC8
#define CMD_SET_POWER_CONTROL  0x28
#define CMD_SET_RESISTOR_RATIO  0x20
#define CMD_SET_VOLUME_FIRST  0x81
#define  CMD_SET_VOLUME_SECOND  0
#define CMD_SET_STATIC_OFF  0xAC
#define  CMD_SET_STATIC_ON  0xAD
#define CMD_SET_STATIC_REG  0x0
#define CMD_SET_BOOSTER_FIRST  0xF8
#define CMD_SET_BOOSTER_234  0
#define  CMD_SET_BOOSTER_5  1
#define  CMD_SET_BOOSTER_6  3
#define CMD_NOP  0xE3
#define CMD_TEST  0xF0

class ST7565 {
 public:
  ST7565(int8 SID, int8 SCLK, int8 A0, int8 RST, int8 CS) :sid(SID), sclk(SCLK), a0(A0), rst(RST), cs(CS) {}
  ST7565(int8 SID, int8 SCLK, int8 A0, int8 RST) :sid(SID), sclk(SCLK), a0(A0), rst(RST), cs(-1) {}


  void st7565_init(void);
  void begin(uint8 contrast);
  void st7565_command(uint8 c);
  void st7565_data(uint8 c);
  void st7565_set_brightness(uint8 val);
  void clear_display(void);
  void clear();
  void display();

  void setpixel(uint8 x, uint8 y, uint8 color);
  uint8 getpixel(uint8 x, uint8 y);
  void fillcircle(uint8 x0, uint8 y0, uint8 r, 
		  uint8 color);
  void drawcircle(uint8 x0, uint8 y0, uint8 r, 
		  uint8 color);
  void drawrect(uint8 x, uint8 y, uint8 w, uint8 h, 
		uint8 color);
  void fillrect(uint8 x, uint8 y, uint8 w, uint8 h, 
		uint8 color);
  void drawline(uint8 x0, uint8 y0, uint8 x1, uint8 y1, 
		uint8 color);

  int16 drawchar(int16 x, int8 line, char c, uint8 inverted = 0);
  int16 drawcharat(int16 x, int16 y, char c, uint8 inverted = 0);

  void drawstring(int8 column, int8 line, const char *c, uint8 inverted = 0);
  void drawstringw(int8 column, int8 line, const char *c, uint8 inverted = 0, uint8 smartwrap = 0, uint8 wraptocolumn = 0);
  void drawstringat(int16 x, int16 y, const char *c, uint8 inverted = 0);

  void drawbitmap(uint8 x, uint8 y, 
		  const uint8 *bitmap, uint8 w, uint8 h,
		  uint8 color);

 private:
  int8 sid, sclk, a0, rst, cs;
  void spiwrite(uint8 c);

  void my_setpixel(uint8 x, uint8 y, uint8 color);

  //uint8 buffer[128*64/8]; 
};
