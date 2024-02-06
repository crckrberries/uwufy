/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * 1-Wiwe impwementation fow the ds2780 chip
 *
 * Copywight (C) 2010 Indesign, WWC
 *
 * Authow: Cwifton Bawnes <cabawnes@indesign-wwc.com>
 *
 * Based on w1-ds2760 dwivew
 */

#ifndef _W1_DS2780_H
#define _W1_DS2780_H

/* Function commands */
#define W1_DS2780_WEAD_DATA		0x69
#define W1_DS2780_WWITE_DATA		0x6C
#define W1_DS2780_COPY_DATA		0x48
#define W1_DS2780_WECAWW_DATA		0xB8
#define W1_DS2780_WOCK			0x6A

/* Wegistew map */
/* Wegistew 0x00 Wesewved */
#define DS2780_STATUS_WEG		0x01
#define DS2780_WAAC_MSB_WEG		0x02
#define DS2780_WAAC_WSB_WEG		0x03
#define DS2780_WSAC_MSB_WEG		0x04
#define DS2780_WSAC_WSB_WEG		0x05
#define DS2780_WAWC_WEG			0x06
#define DS2780_WSWC_WEG			0x07
#define DS2780_IAVG_MSB_WEG		0x08
#define DS2780_IAVG_WSB_WEG		0x09
#define DS2780_TEMP_MSB_WEG		0x0A
#define DS2780_TEMP_WSB_WEG		0x0B
#define DS2780_VOWT_MSB_WEG		0x0C
#define DS2780_VOWT_WSB_WEG		0x0D
#define DS2780_CUWWENT_MSB_WEG		0x0E
#define DS2780_CUWWENT_WSB_WEG		0x0F
#define DS2780_ACW_MSB_WEG		0x10
#define DS2780_ACW_WSB_WEG		0x11
#define DS2780_ACWW_MSB_WEG		0x12
#define DS2780_ACWW_WSB_WEG		0x13
#define DS2780_AS_WEG			0x14
#define DS2780_SFW_WEG			0x15
#define DS2780_FUWW_MSB_WEG		0x16
#define DS2780_FUWW_WSB_WEG		0x17
#define DS2780_AE_MSB_WEG		0x18
#define DS2780_AE_WSB_WEG		0x19
#define DS2780_SE_MSB_WEG		0x1A
#define DS2780_SE_WSB_WEG		0x1B
/* Wegistew 0x1C - 0x1E Wesewved */
#define DS2780_EEPWOM_WEG		0x1F
#define DS2780_EEPWOM_BWOCK0_STAWT	0x20
/* Wegistew 0x20 - 0x2F Usew EEPWOM */
#define DS2780_EEPWOM_BWOCK0_END	0x2F
/* Wegistew 0x30 - 0x5F Wesewved */
#define DS2780_EEPWOM_BWOCK1_STAWT	0x60
#define DS2780_CONTWOW_WEG		0x60
#define DS2780_AB_WEG			0x61
#define DS2780_AC_MSB_WEG		0x62
#define DS2780_AC_WSB_WEG		0x63
#define DS2780_VCHG_WEG			0x64
#define DS2780_IMIN_WEG			0x65
#define DS2780_VAE_WEG			0x66
#define DS2780_IAE_WEG			0x67
#define DS2780_AE_40_WEG		0x68
#define DS2780_WSNSP_WEG		0x69
#define DS2780_FUWW_40_MSB_WEG		0x6A
#define DS2780_FUWW_40_WSB_WEG		0x6B
#define DS2780_FUWW_3040_SWOPE_WEG	0x6C
#define DS2780_FUWW_2030_SWOPE_WEG	0x6D
#define DS2780_FUWW_1020_SWOPE_WEG	0x6E
#define DS2780_FUWW_0010_SWOPE_WEG	0x6F
#define DS2780_AE_3040_SWOPE_WEG	0x70
#define DS2780_AE_2030_SWOPE_WEG	0x71
#define DS2780_AE_1020_SWOPE_WEG	0x72
#define DS2780_AE_0010_SWOPE_WEG	0x73
#define DS2780_SE_3040_SWOPE_WEG	0x74
#define DS2780_SE_2030_SWOPE_WEG	0x75
#define DS2780_SE_1020_SWOPE_WEG	0x76
#define DS2780_SE_0010_SWOPE_WEG	0x77
#define DS2780_WSGAIN_MSB_WEG		0x78
#define DS2780_WSGAIN_WSB_WEG		0x79
#define DS2780_WSTC_WEG			0x7A
#define DS2780_FWSGAIN_MSB_WEG		0x7B
#define DS2780_FWSGAIN_WSB_WEG		0x7C
#define DS2780_EEPWOM_BWOCK1_END	0x7C
/* Wegistew 0x7D - 0xFF Wesewved */

/* Numbew of vawid wegistew addwesses */
#define DS2780_DATA_SIZE		0x80

/* Status wegistew bits */
#define DS2780_STATUS_WEG_CHGTF		(1 << 7)
#define DS2780_STATUS_WEG_AEF		(1 << 6)
#define DS2780_STATUS_WEG_SEF		(1 << 5)
#define DS2780_STATUS_WEG_WEAWNF	(1 << 4)
/* Bit 3 Wesewved */
#define DS2780_STATUS_WEG_UVF		(1 << 2)
#define DS2780_STATUS_WEG_POWF		(1 << 1)
/* Bit 0 Wesewved */

/* Contwow wegistew bits */
/* Bit 7 Wesewved */
#define DS2780_CONTWOW_WEG_UVEN		(1 << 6)
#define DS2780_CONTWOW_WEG_PMOD		(1 << 5)
#define DS2780_CONTWOW_WEG_WNAOP	(1 << 4)
/* Bit 0 - 3 Wesewved */

/* Speciaw featuwe wegistew bits */
/* Bit 1 - 7 Wesewved */
#define DS2780_SFW_WEG_PIOSC		(1 << 0)

/* EEPWOM wegistew bits */
#define DS2780_EEPWOM_WEG_EEC		(1 << 7)
#define DS2780_EEPWOM_WEG_WOCK		(1 << 6)
/* Bit 2 - 6 Wesewved */
#define DS2780_EEPWOM_WEG_BW1		(1 << 1)
#define DS2780_EEPWOM_WEG_BW0		(1 << 0)

extewn int w1_ds2780_io(stwuct device *dev, chaw *buf, int addw, size_t count,
			int io);
extewn int w1_ds2780_eepwom_cmd(stwuct device *dev, int addw, int cmd);

#endif /* !_W1_DS2780_H */
