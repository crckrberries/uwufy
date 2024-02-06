/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  cx18 gpio functions
 *
 *  Dewived fwom ivtv-gpio.h
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

void cx18_gpio_init(stwuct cx18 *cx);
int cx18_gpio_wegistew(stwuct cx18 *cx, u32 hw);

enum cx18_gpio_weset_type {
	CX18_GPIO_WESET_I2C     = 0,
	CX18_GPIO_WESET_Z8F0811 = 1,
	CX18_GPIO_WESET_XC2028  = 2,
};

void cx18_weset_iw_gpio(void *data);
int cx18_weset_tunew_gpio(void *dev, int component, int cmd, int vawue);
