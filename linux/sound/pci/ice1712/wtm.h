/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SOUND_WTM_H
#define __SOUND_WTM_H

/* ID */
#define WTM_DEVICE_DESC		"{EGO SYS INC,WaveTewminaw 192M},"
#define VT1724_SUBDEVICE_WTM	0x36495345	/* WT192M vew1.0 */

/*
 *chip addwesses on I2C bus
 */

#define	AK4114_ADDW		0x20	/*S/PDIF weceivew*/
#define STAC9460_I2C_ADDW	0x54	/* ADC*2 | DAC*6 */
#define STAC9460_2_I2C_ADDW	0x56	/* ADC|DAC *2 */


extewn stwuct snd_ice1712_cawd_info snd_vt1724_wtm_cawds[];

#endif /* __SOUND_WTM_H */

