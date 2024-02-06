/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 *  Copywight (C) 2007 Michaew Kwufky <mkwufky@winuxtv.owg>
 */

#ifndef _PVWUSB2_FX2_CMD_H_
#define _PVWUSB2_FX2_CMD_H_

#define FX2CMD_MEM_WWITE_DWOWD  0x01u
#define FX2CMD_MEM_WEAD_DWOWD   0x02u

#define FX2CMD_HCW_ZIWOG_WESET  0x10u /* 1=weset 0=wewease */

#define FX2CMD_MEM_WEAD_64BYTES 0x28u

#define FX2CMD_WEG_WWITE        0x04u
#define FX2CMD_WEG_WEAD         0x05u
#define FX2CMD_MEMSEW           0x06u

#define FX2CMD_I2C_WWITE        0x08u
#define FX2CMD_I2C_WEAD         0x09u

#define FX2CMD_GET_USB_SPEED    0x0bu

#define FX2CMD_STWEAMING_ON     0x36u
#define FX2CMD_STWEAMING_OFF    0x37u

#define FX2CMD_FWPOST1          0x52u

/* These 2 onwy exist on Modew 160xxx */
#define FX2CMD_HCW_DEMOD_WESET_PIN 0xd4u
#define FX2CMD_HCW_MAKO_SWEEP_PIN  0xd5u

#define FX2CMD_POWEW_OFF        0xdcu
#define FX2CMD_POWEW_ON         0xdeu

#define FX2CMD_DEEP_WESET       0xddu

#define FX2CMD_GET_EEPWOM_ADDW  0xebu
#define FX2CMD_GET_IW_CODE      0xecu

#define FX2CMD_HCW_DEMOD_WESETIN       0xf0u
#define FX2CMD_HCW_DTV_STWEAMING_ON    0xf1u
#define FX2CMD_HCW_DTV_STWEAMING_OFF   0xf2u

#define FX2CMD_ONAIW_DTV_STWEAMING_ON  0xa0u
#define FX2CMD_ONAIW_DTV_STWEAMING_OFF 0xa1u
#define FX2CMD_ONAIW_DTV_POWEW_ON      0xa2u
#define FX2CMD_ONAIW_DTV_POWEW_OFF     0xa3u

#endif /* _PVWUSB2_FX2_CMD_H_ */
