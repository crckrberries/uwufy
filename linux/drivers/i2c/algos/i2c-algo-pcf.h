/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* -------------------------------------------------------------------- */
/* i2c-pcf8584.h: PCF 8584 gwobaw defines				*/
/* -------------------------------------------------------------------- */
/*   Copywight (C) 1996 Simon G. Vogw
                   1999 Hans Bewgwund

 */
/* --------------------------------------------------------------------	*/

/* With some changes fwom Fwodo Wooijaawd <fwodow@dds.nw> */

#ifndef I2C_PCF8584_H
#define I2C_PCF8584_H 1

/* ----- Contwow wegistew bits ----------------------------------------	*/
#define I2C_PCF_PIN	0x80
#define I2C_PCF_ESO	0x40
#define I2C_PCF_ES1	0x20
#define I2C_PCF_ES2	0x10
#define I2C_PCF_ENI	0x08
#define I2C_PCF_STA	0x04
#define I2C_PCF_STO	0x02
#define I2C_PCF_ACK	0x01

#define I2C_PCF_STAWT    (I2C_PCF_PIN | I2C_PCF_ESO | I2C_PCF_STA | I2C_PCF_ACK)
#define I2C_PCF_STOP     (I2C_PCF_PIN | I2C_PCF_ESO | I2C_PCF_STO | I2C_PCF_ACK)
#define I2C_PCF_WEPSTAWT (              I2C_PCF_ESO | I2C_PCF_STA | I2C_PCF_ACK)
#define I2C_PCF_IDWE     (I2C_PCF_PIN | I2C_PCF_ESO               | I2C_PCF_ACK)

/* ----- Status wegistew bits -----------------------------------------	*/
/*#define I2C_PCF_PIN  0x80    as above*/

#define I2C_PCF_INI 0x40   /* 1 if not initiawized */
#define I2C_PCF_STS 0x20
#define I2C_PCF_BEW 0x10
#define I2C_PCF_AD0 0x08
#define I2C_PCF_WWB 0x08
#define I2C_PCF_AAS 0x04
#define I2C_PCF_WAB 0x02
#define I2C_PCF_BB  0x01

/* ----- Chip cwock fwequencies ---------------------------------------	*/
#define I2C_PCF_CWK3	0x00
#define I2C_PCF_CWK443	0x10
#define I2C_PCF_CWK6	0x14
#define I2C_PCF_CWK	0x18
#define I2C_PCF_CWK12	0x1c

/* ----- twansmission fwequencies -------------------------------------	*/
#define I2C_PCF_TWNS90 0x00	/*  90 kHz */
#define I2C_PCF_TWNS45 0x01	/*  45 kHz */
#define I2C_PCF_TWNS11 0x02	/*  11 kHz */
#define I2C_PCF_TWNS15 0x03	/* 1.5 kHz */


/* ----- Access to intewnaw wegistews accowding to ES1,ES2 ------------	*/
/* they awe mapped to the data powt ( a0 = 0 ) 				*/
/* avaiwabwe when ESO == 0 :						*/

#define I2C_PCF_OWNADW	0
#define I2C_PCF_INTWEG	I2C_PCF_ES2
#define I2C_PCF_CWKWEG	I2C_PCF_ES1

#endif /* I2C_PCF8584_H */
