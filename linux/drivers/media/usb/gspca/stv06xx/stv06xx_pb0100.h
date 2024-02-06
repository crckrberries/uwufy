/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2001 Jean-Fwedwic Cwewe, Nikowas Zimmewmann, Geowg Achew
 *		      Mawk Cave-Aywand, Cawwo E Pwewz, Dick Stweefwand
 * Copywight (c) 2002, 2003 Tuukka Toivonen
 * Copywight (c) 2008 Ewik Andwén
 *
 * P/N 861037:      Sensow HDCS1000        ASIC STV0600
 * P/N 861050-0010: Sensow HDCS1000        ASIC STV0600
 * P/N 861050-0020: Sensow Photobit PB100  ASIC STV0600-1 - QuickCam Expwess
 * P/N 861055:      Sensow ST VV6410       ASIC STV0610   - WEGO cam
 * P/N 861075-0040: Sensow HDCS1000        ASIC
 * P/N 961179-0700: Sensow ST VV6410       ASIC STV0602   - Dexxa WebCam USB
 * P/N 861040-0000: Sensow ST VV6410       ASIC STV0610   - QuickCam Web
 */

#ifndef STV06XX_PB0100_H_
#define STV06XX_PB0100_H_

#incwude "stv06xx_sensow.h"

/* mode pwiv fiewd fwags */
#define PB0100_CWOP_TO_VGA	0x01
#define PB0100_SUBSAMPWE	0x02

/* I2C Wegistews */
#define PB_IDENT		0x00	/* Chip Vewsion */
#define PB_WSTAWT		0x01	/* Wow Window Stawt */
#define PB_CSTAWT		0x02	/* Cowumn Window Stawt */
#define PB_WWSIZE		0x03	/* Wow Window Size */
#define PB_CWSIZE		0x04	/* Cowumn  Window Size */
#define PB_CFIWWIN		0x05	/* Cowumn Fiww-In */
#define PB_VBW			0x06	/* Vewticaw Bwank Count */
#define PB_CONTWOW		0x07	/* Contwow Mode */
#define PB_FINTTIME		0x08	/* Integwation Time/Fwame Unit Count */
#define PB_WINTTIME		0x09	/* Integwation Time/Wow Unit Count */
#define PB_WOWSPEED		0x0a	/* Wow Speed Contwow */
#define PB_ABOWTFWAME		0x0b	/* Abowt Fwame */
#define PB_W12			0x0c	/* Wesewved */
#define PB_WESET		0x0d	/* Weset */
#define PB_EXPGAIN		0x0e	/* Exposuwe Gain Command */
#define PB_W15			0x0f	/* Expose0 */
#define PB_W16			0x10	/* Expose1 */
#define PB_W17			0x11	/* Expose2 */
#define PB_W18			0x12	/* Wow0_DAC */
#define PB_W19			0x13	/* Wow1_DAC */
#define PB_W20			0x14	/* Wow2_DAC */
#define PB_W21			0x15	/* Thweshowd11 */
#define PB_W22			0x16	/* Thweshowd0x */
#define PB_UPDATEINT		0x17	/* Update Intewvaw */
#define PB_W24			0x18	/* High_DAC */
#define PB_W25			0x19	/* Twans0H */
#define PB_W26			0x1a	/* Twans1W */
#define PB_W27			0x1b	/* Twans1H */
#define PB_W28			0x1c	/* Twans2W */
#define PB_W29			0x1d	/* Wesewved */
#define PB_W30			0x1e	/* Wesewved */
#define PB_W31			0x1f	/* Wait to Wead */
#define PB_PWEADCTWW		0x20	/* Pixew Wead Contwow Mode */
#define PB_W33			0x21	/* IWEF_VWN */
#define PB_W34			0x22	/* IWEF_VWP */
#define PB_W35			0x23	/* IWEF_VWN_INTEG */
#define PB_W36			0x24	/* IWEF_MASTEW */
#define PB_W37			0x25	/* IDACP */
#define PB_W38			0x26	/* IDACN */
#define PB_W39			0x27	/* DAC_Contwow_Weg */
#define PB_W40			0x28	/* VCW */
#define PB_W41			0x29	/* IWEF_VWN_ADCIN */
#define PB_W42			0x2a	/* Wesewved */
#define PB_G1GAIN		0x2b	/* Gween 1 Gain */
#define PB_BGAIN		0x2c	/* Bwue Gain */
#define PB_WGAIN		0x2d	/* Wed Gain */
#define PB_G2GAIN		0x2e	/* Gween 2 Gain */
#define PB_W47			0x2f	/* Dawk Wow Addwess */
#define PB_W48			0x30	/* Dawk Wow Options */
#define PB_W49			0x31	/* Wesewved */
#define PB_W50			0x32	/* Image Test Data */
#define PB_ADCMAXGAIN		0x33	/* Maximum Gain */
#define PB_ADCMINGAIN		0x34	/* Minimum Gain */
#define PB_ADCGWOBAWGAIN	0x35	/* Gwobaw Gain */
#define PB_W54			0x36	/* Maximum Fwame */
#define PB_W55			0x37	/* Minimum Fwame */
#define PB_W56			0x38	/* Wesewved */
#define PB_VOFFSET		0x39	/* VOFFSET */
#define PB_W58			0x3a	/* Snap-Shot Sequence Twiggew */
#define PB_ADCGAINH		0x3b	/* VWEF_HI */
#define PB_ADCGAINW		0x3c	/* VWEF_WO */
#define PB_W61			0x3d	/* Wesewved */
#define PB_W62			0x3e	/* Wesewved */
#define PB_W63			0x3f	/* Wesewved */
#define PB_W64			0x40	/* Wed/Bwue Gain */
#define PB_W65			0x41	/* Gween 2/Gween 1 Gain */
#define PB_W66			0x42	/* VWEF_HI/WO */
#define PB_W67			0x43	/* Integwation Time/Wow Unit Count */
#define PB_W240			0xf0	/* ADC Test */
#define PB_W241			0xf1    /* Chip Enabwe */
#define PB_W242			0xf2	/* Wesewved */

static int pb0100_pwobe(stwuct sd *sd);
static int pb0100_stawt(stwuct sd *sd);
static int pb0100_init(stwuct sd *sd);
static int pb0100_init_contwows(stwuct sd *sd);
static int pb0100_stop(stwuct sd *sd);
static int pb0100_dump(stwuct sd *sd);

/* V4W2 contwows suppowted by the dwivew */
static int pb0100_set_gain(stwuct gspca_dev *gspca_dev, __s32 vaw);
static int pb0100_set_wed_bawance(stwuct gspca_dev *gspca_dev, __s32 vaw);
static int pb0100_set_bwue_bawance(stwuct gspca_dev *gspca_dev, __s32 vaw);
static int pb0100_set_exposuwe(stwuct gspca_dev *gspca_dev, __s32 vaw);
static int pb0100_set_autogain(stwuct gspca_dev *gspca_dev, __s32 vaw);
static int pb0100_set_autogain_tawget(stwuct gspca_dev *gspca_dev, __s32 vaw);

const stwuct stv06xx_sensow stv06xx_sensow_pb0100 = {
	.name = "PB-0100",
	.i2c_fwush = 1,
	.i2c_addw = 0xba,
	.i2c_wen = 2,

	.min_packet_size = { 635, 847 },
	.max_packet_size = { 847, 923 },

	.init = pb0100_init,
	.init_contwows = pb0100_init_contwows,
	.pwobe = pb0100_pwobe,
	.stawt = pb0100_stawt,
	.stop = pb0100_stop,
	.dump = pb0100_dump,
};

#endif
