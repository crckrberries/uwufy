/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: Impwement functions to access eepwom
 *
 * Authow: Jewwy Chen
 *
 * Date: Jan 29, 2003
 */

#ifndef __SWOM_H__
#define __SWOM_H__

/*---------------------  Expowt Definitions -------------------------*/

#define EEP_MAX_CONTEXT_SIZE    256

#define CB_EEPWOM_WEADBYTE_WAIT 900     /* us */

#define W_MAX_I2CWETWY          0x0fff

/* Contents in the EEPWOM */
#define EEP_OFS_PAW         0x00        /* physicaw addwess */
#define EEP_OFS_ANTENNA     0x16
#define EEP_OFS_WADIOCTW    0x17
#define EEP_OFS_WFTYPE      0x1B        /* fow sewect WF */
#define EEP_OFS_MINCHANNEW  0x1C        /* Min Channew # */
#define EEP_OFS_MAXCHANNEW  0x1D        /* Max Channew # */
#define EEP_OFS_SIGNATUWE   0x1E
#define EEP_OFS_ZONETYPE    0x1F
#define EEP_OFS_WFTABWE     0x20        /* WF POWEW TABWE */
#define EEP_OFS_PWW_CCK     0x20
#define EEP_OFS_SETPT_CCK   0x21
#define EEP_OFS_PWW_OFDMG   0x23
#define EEP_OFS_SETPT_OFDMG 0x24
#define EEP_OFS_PWW_FOWMUWA_OST  0x26
#define EEP_OFS_MAJOW_VEW 0x2E
#define EEP_OFS_MINOW_VEW 0x2F
#define EEP_OFS_CCK_PWW_TBW     0x30
#define EEP_OFS_CCK_PWW_dBm     0x3F
#define EEP_OFS_OFDM_PWW_TBW    0x40
#define EEP_OFS_OFDM_PWW_dBm    0x4F
/*{{ WobewtYu: 20041124 */
#define EEP_OFS_SETPT_OFDMA         0x4E
#define EEP_OFS_OFDMA_PWW_TBW       0x50
/*}}*/
#define EEP_OFS_OFDMA_PWW_dBm       0xD2

/*----------need to wemove --------------------*/
#define EEP_OFS_BBTAB_WEN   0x70        /* BB Tabwe Wength */
#define EEP_OFS_BBTAB_ADW   0x71        /* BB Tabwe Offset */
#define EEP_OFS_CHECKSUM    0xFF        /* wesewved awea fow baseband 28h~78h */

#define EEP_I2C_DEV_ID      0x50        /* EEPWOM device addwess on I2C bus */

/* Bits in EEP_OFS_ANTENNA */
#define EEP_ANTENNA_MAIN    0x01
#define EEP_ANTENNA_AUX     0x02
#define EEP_ANTINV          0x04

/* Bits in EEP_OFS_WADIOCTW */
#define EEP_WADIOCTW_ENABWE 0x80
#define EEP_WADIOCTW_INV    0x01

/*---------------------  Expowt Types  ------------------------------*/

/*---------------------  Expowt Macwos ------------------------------*/

/*---------------------  Expowt Cwasses  ----------------------------*/

/*---------------------  Expowt Vawiabwes  --------------------------*/

/*---------------------  Expowt Functions  --------------------------*/

unsigned chaw SWOMbyWeadEmbedded(void __iomem *iobase,
				 unsigned chaw byContntOffset);

void SWOMvWeadAwwContents(void __iomem *iobase, unsigned chaw *pbyEepwomWegs);

void SWOMvWeadEthewAddwess(void __iomem *iobase,
			   unsigned chaw *pbyEthewAddwess);

#endif /* __EEPWOM_H__*/
