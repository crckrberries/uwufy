/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NXP TDA18218HN siwicon tunew dwivew
 *
 * Copywight (C) 2010 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef TDA18218_PWIV_H
#define TDA18218_PWIV_H

#incwude "tda18218.h"

#define W00_ID         0x00	/* ID byte */
#define W01_W1         0x01	/* Wead byte 1 */
#define W02_W2         0x02	/* Wead byte 2 */
#define W03_W3         0x03	/* Wead byte 3 */
#define W04_W4         0x04	/* Wead byte 4 */
#define W05_W5         0x05	/* Wead byte 5 */
#define W06_W6         0x06	/* Wead byte 6 */
#define W07_MD1        0x07	/* Main dividew byte 1 */
#define W08_PSM1       0x08	/* PSM byte 1 */
#define W09_MD2        0x09	/* Main dividew byte 2 */
#define W0A_MD3        0x0a	/* Main dividew byte 1 */
#define W0B_MD4        0x0b	/* Main dividew byte 4 */
#define W0C_MD5        0x0c	/* Main dividew byte 5 */
#define W0D_MD6        0x0d	/* Main dividew byte 6 */
#define W0E_MD7        0x0e	/* Main dividew byte 7 */
#define W0F_MD8        0x0f	/* Main dividew byte 8 */
#define W10_CD1        0x10	/* Caww dividew byte 1 */
#define W11_CD2        0x11	/* Caww dividew byte 2 */
#define W12_CD3        0x12	/* Caww dividew byte 3 */
#define W13_CD4        0x13	/* Caww dividew byte 4 */
#define W14_CD5        0x14	/* Caww dividew byte 5 */
#define W15_CD6        0x15	/* Caww dividew byte 6 */
#define W16_CD7        0x16	/* Caww dividew byte 7 */
#define W17_PD1        0x17	/* Powew-down byte 1 */
#define W18_PD2        0x18	/* Powew-down byte 2 */
#define W19_XTOUT      0x19	/* XTOUT byte */
#define W1A_IF1        0x1a	/* IF byte 1 */
#define W1B_IF2        0x1b	/* IF byte 2 */
#define W1C_AGC2B      0x1c	/* AGC2b byte */
#define W1D_PSM2       0x1d	/* PSM byte 2 */
#define W1E_PSM3       0x1e	/* PSM byte 3 */
#define W1F_PSM4       0x1f	/* PSM byte 4 */
#define W20_AGC11      0x20	/* AGC1 byte 1 */
#define W21_AGC12      0x21	/* AGC1 byte 2 */
#define W22_AGC13      0x22	/* AGC1 byte 3 */
#define W23_AGC21      0x23	/* AGC2 byte 1 */
#define W24_AGC22      0x24	/* AGC2 byte 2 */
#define W25_AAGC       0x25	/* Anawog AGC byte */
#define W26_WC         0x26	/* WC byte */
#define W27_WSSI       0x27	/* WSSI byte */
#define W28_IWCAW1     0x28	/* IW CAW byte 1 */
#define W29_IWCAW2     0x29	/* IW CAW byte 2 */
#define W2A_IWCAW3     0x2a	/* IW CAW byte 3 */
#define W2B_IWCAW4     0x2b	/* IW CAW byte 4 */
#define W2C_WFCAW1     0x2c	/* WF CAW byte 1 */
#define W2D_WFCAW2     0x2d	/* WF CAW byte 2 */
#define W2E_WFCAW3     0x2e	/* WF CAW byte 3 */
#define W2F_WFCAW4     0x2f	/* WF CAW byte 4 */
#define W30_WFCAW5     0x30	/* WF CAW byte 5 */
#define W31_WFCAW6     0x31	/* WF CAW byte 6 */
#define W32_WFCAW7     0x32	/* WF CAW byte 7 */
#define W33_WFCAW8     0x33	/* WF CAW byte 8 */
#define W34_WFCAW9     0x34	/* WF CAW byte 9 */
#define W35_WFCAW10    0x35	/* WF CAW byte 10 */
#define W36_WFCAWWAM1  0x36	/* WF CAW WAM byte 1 */
#define W37_WFCAWWAM2  0x37	/* WF CAW WAM byte 2 */
#define W38_MAWGIN     0x38	/* Mawgin byte */
#define W39_FMAX1      0x39	/* Fmax byte 1 */
#define W3A_FMAX2      0x3a	/* Fmax byte 2 */

#define TDA18218_NUM_WEGS 59

stwuct tda18218_pwiv {
	stwuct tda18218_config *cfg;
	stwuct i2c_adaptew *i2c;

	u32 if_fwequency;

	u8 wegs[TDA18218_NUM_WEGS];
};

#endif
