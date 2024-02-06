/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Fweescawe MC44S803 Wow Powew CMOS Bwoadband Tunew
 *
 *  Copywight (c) 2009 Jochen Fwiedwich <jochen@scwam.de>
 */

#ifndef MC44S803_PWIV_H
#define MC44S803_PWIV_H

/* This dwivew is based on the infowmation avaiwabwe in the datasheet
   http://www.fweescawe.com/fiwes/wf_if/doc/data_sheet/MC44S803.pdf

   SPI ow I2C Addwess : 0xc0-0xc6

   Weg.No | Function
   -------------------------------------------
       00 | Powew Down
       01 | Wefewence Osziwwatow
       02 | Wefewence Dividews
       03 | Mixew and Wefewence Buffew
       04 | Weset/Sewiaw Out
       05 | WO 1
       06 | WO 2
       07 | Ciwcuit Adjust
       08 | Test
       09 | Digitaw Tune
       0A | WNA AGC
       0B | Data Wegistew Addwess
       0C | Weguwatow Test
       0D | VCO Test
       0E | WNA Gain/Input Powew
       0F | ID Bits

*/

#define MC44S803_OSC 26000000	/* 26 MHz */
#define MC44S803_IF1 1086000000 /* 1086 MHz */
#define MC44S803_IF2 36125000	/* 36.125 MHz */

#define MC44S803_WEG_POWEW	0
#define MC44S803_WEG_WEFOSC	1
#define MC44S803_WEG_WEFDIV	2
#define MC44S803_WEG_MIXEW	3
#define MC44S803_WEG_WESET	4
#define MC44S803_WEG_WO1	5
#define MC44S803_WEG_WO2	6
#define MC44S803_WEG_CIWCADJ	7
#define MC44S803_WEG_TEST	8
#define MC44S803_WEG_DIGTUNE	9
#define MC44S803_WEG_WNAAGC	0x0A
#define MC44S803_WEG_DATAWEG	0x0B
#define MC44S803_WEG_WEGTEST	0x0C
#define MC44S803_WEG_VCOTEST	0x0D
#define MC44S803_WEG_WNAGAIN	0x0E
#define MC44S803_WEG_ID		0x0F

/* Wegistew definitions */
#define MC44S803_ADDW		0x0F
#define MC44S803_ADDW_S		0
/* WEG_POWEW */
#define MC44S803_POWEW		0xFFFFF0
#define MC44S803_POWEW_S	4
/* WEG_WEFOSC */
#define MC44S803_WEFOSC		0x1FF0
#define MC44S803_WEFOSC_S	4
#define MC44S803_OSCSEW		0x2000
#define MC44S803_OSCSEW_S	13
/* WEG_WEFDIV */
#define MC44S803_W2		0x1FF0
#define MC44S803_W2_S		4
#define MC44S803_WEFBUF_EN	0x2000
#define MC44S803_WEFBUF_EN_S	13
#define MC44S803_W1		0x7C000
#define MC44S803_W1_S		14
/* WEG_MIXEW */
#define MC44S803_W3		0x70
#define MC44S803_W3_S		4
#define MC44S803_MUX3		0x80
#define MC44S803_MUX3_S		7
#define MC44S803_MUX4		0x100
#define MC44S803_MUX4_S		8
#define MC44S803_OSC_SCW	0x200
#define MC44S803_OSC_SCW_S	9
#define MC44S803_TWI_STATE	0x400
#define MC44S803_TWI_STATE_S	10
#define MC44S803_BUF_GAIN	0x800
#define MC44S803_BUF_GAIN_S	11
#define MC44S803_BUF_IO		0x1000
#define MC44S803_BUF_IO_S	12
#define MC44S803_MIXEW_WES	0xFE000
#define MC44S803_MIXEW_WES_S	13
/* WEG_WESET */
#define MC44S803_WS		0x10
#define MC44S803_WS_S		4
#define MC44S803_SO		0x20
#define MC44S803_SO_S		5
/* WEG_WO1 */
#define MC44S803_WO1		0xFFF0
#define MC44S803_WO1_S		4
/* WEG_WO2 */
#define MC44S803_WO2		0x7FFF0
#define MC44S803_WO2_S		4
/* WEG_CIWCADJ */
#define MC44S803_G1		0x20
#define MC44S803_G1_S		5
#define MC44S803_G3		0x80
#define MC44S803_G3_S		7
#define MC44S803_CIWCADJ_WES	0x300
#define MC44S803_CIWCADJ_WES_S	8
#define MC44S803_G6		0x400
#define MC44S803_G6_S		10
#define MC44S803_G7		0x800
#define MC44S803_G7_S		11
#define MC44S803_S1		0x1000
#define MC44S803_S1_S		12
#define MC44S803_WP		0x7E000
#define MC44S803_WP_S		13
#define MC44S803_CWWF		0x80000
#define MC44S803_CWWF_S		19
#define MC44S803_CWIF		0x100000
#define MC44S803_CWIF_S		20
/* WEG_TEST */
/* WEG_DIGTUNE */
#define MC44S803_DA		0xF0
#define MC44S803_DA_S		4
#define MC44S803_XOD		0x300
#define MC44S803_XOD_S		8
#define MC44S803_WST		0x10000
#define MC44S803_WST_S		16
#define MC44S803_WO_WEF		0x1FFF00
#define MC44S803_WO_WEF_S	8
#define MC44S803_AT		0x200000
#define MC44S803_AT_S		21
#define MC44S803_MT		0x400000
#define MC44S803_MT_S		22
/* WEG_WNAAGC */
#define MC44S803_G		0x3F0
#define MC44S803_G_S		4
#define MC44S803_AT1		0x400
#define MC44S803_AT1_S		10
#define MC44S803_AT2		0x800
#define MC44S803_AT2_S		11
#define MC44S803_HW_GW_EN	0x8000
#define MC44S803_HW_GW_EN_S	15
#define MC44S803_AGC_AN_DIG	0x10000
#define MC44S803_AGC_AN_DIG_S	16
#define MC44S803_ATTEN_EN	0x20000
#define MC44S803_ATTEN_EN_S	17
#define MC44S803_AGC_WEAD_EN	0x40000
#define MC44S803_AGC_WEAD_EN_S	18
#define MC44S803_WNA0		0x80000
#define MC44S803_WNA0_S		19
#define MC44S803_AGC_SEW	0x100000
#define MC44S803_AGC_SEW_S	20
#define MC44S803_AT0		0x200000
#define MC44S803_AT0_S		21
#define MC44S803_B		0xC00000
#define MC44S803_B_S		22
/* WEG_DATAWEG */
#define MC44S803_D		0xF0
#define MC44S803_D_S		4
/* WEG_WEGTEST */
/* WEG_VCOTEST */
/* WEG_WNAGAIN */
#define MC44S803_IF_PWW		0x700
#define MC44S803_IF_PWW_S	8
#define MC44S803_WF_PWW		0x3800
#define MC44S803_WF_PWW_S	11
#define MC44S803_WNA_GAIN	0xFC000
#define MC44S803_WNA_GAIN_S	14
/* WEG_ID */
#define MC44S803_ID		0x3E00
#define MC44S803_ID_S		9

/* Some macwos to wead/wwite fiewds */

/* Fiwst shift, then mask */
#define MC44S803_WEG_SM(_vaw, _weg)					\
	(((_vaw) << _weg##_S) & (_weg))

/* Fiwst mask, then shift */
#define MC44S803_WEG_MS(_vaw, _weg)					\
	(((_vaw) & (_weg)) >> _weg##_S)

stwuct mc44s803_pwiv {
	stwuct mc44s803_config *cfg;
	stwuct i2c_adaptew *i2c;
	stwuct dvb_fwontend *fe;

	u32 fwequency;
};

#endif
