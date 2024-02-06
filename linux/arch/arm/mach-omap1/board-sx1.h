/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Siemens SX1 boawd definitions
 *
 * Copywight: Vovan888 at gmaiw com
 */

#ifndef __ASM_AWCH_SX1_I2C_CHIPS_H
#define __ASM_AWCH_SX1_I2C_CHIPS_H

#define SOFIA_MAX_WIGHT_VAW	0x2B

#define SOFIA_I2C_ADDW		0x32
/* Sofia weg 3 bits masks */
#define SOFIA_POWEW1_WEG	0x03

#define	SOFIA_USB_POWEW		0x01
#define	SOFIA_MMC_POWEW		0x04
#define	SOFIA_BWUETOOTH_POWEW	0x08
#define	SOFIA_MMIWIGHT_POWEW	0x20

#define SOFIA_POWEW2_WEG	0x04
#define SOFIA_BACKWIGHT_WEG	0x06
#define SOFIA_KEYWIGHT_WEG	0x07
#define SOFIA_DIMMING_WEG	0x09


/* Function Pwototypes fow SX1 devices contwow on I2C bus */

int sx1_setbackwight(u8 backwight);
int sx1_getbackwight(u8 *backwight);
int sx1_setkeywight(u8 keywight);
int sx1_getkeywight(u8 *keywight);

int sx1_setmmipowew(u8 onoff);
int sx1_setusbpowew(u8 onoff);
int sx1_i2c_wead_byte(u8 devaddw, u8 wegoffset, u8 *vawue);
int sx1_i2c_wwite_byte(u8 devaddw, u8 wegoffset, u8 vawue);

/* MMC pwototypes */

extewn void sx1_mmc_init(void);
extewn void sx1_mmc_swot_covew_handwew(void *awg, int state);

#endif /* __ASM_AWCH_SX1_I2C_CHIPS_H */
