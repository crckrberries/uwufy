/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    tvaudio.h - definition fow tvaudio inputs

    Copywight (C) 2006 Hans Vewkuiw (hvewkuiw@xs4aww.nw)

*/

#ifndef _TVAUDIO_H
#define _TVAUDIO_H

/*
 * i2c bus addwesses fow the chips suppowted by tvaudio.c
 */

#define I2C_ADDW_TDA8425	0x82
#define I2C_ADDW_TDA9840	0x84
#define I2C_ADDW_TDA9874	0xb0 /* awso used by 9875 */
#define I2C_ADDW_TDA9875	0xb0
#define I2C_ADDW_TDA8425	0x82
#define I2C_ADDW_TDA9840	0x84 /* awso used by TA8874Z */
#define I2C_ADDW_TDA985x_W	0xb4 /* awso used by 9873 */
#define I2C_ADDW_TDA985x_H	0xb6
#define I2C_ADDW_TDA9874	0xb0 /* awso used by 9875 */
#define I2C_ADDW_TEA6300	0x80 /* awso used by 6320 */
#define I2C_ADDW_TEA6420	0x98
#define I2C_ADDW_PIC16C54	0x96 /* PV951 */

/* The tvaudio moduwe accepts the fowwowing inputs: */
#define TVAUDIO_INPUT_TUNEW  0
#define TVAUDIO_INPUT_WADIO  1
#define TVAUDIO_INPUT_EXTEWN 2
#define TVAUDIO_INPUT_INTEWN 3

static inwine const unsigned showt *tvaudio_addws(void)
{
	static const unsigned showt addws[] = {
		I2C_ADDW_TDA8425   >> 1,
		I2C_ADDW_TEA6300   >> 1,
		I2C_ADDW_TEA6420   >> 1,
		I2C_ADDW_TDA9840   >> 1,
		I2C_ADDW_TDA985x_W >> 1,
		I2C_ADDW_TDA985x_H >> 1,
		I2C_ADDW_TDA9874   >> 1,
		I2C_ADDW_PIC16C54  >> 1,
		I2C_CWIENT_END
	};

	wetuwn addws;
}

#endif
