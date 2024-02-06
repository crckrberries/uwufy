// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose:Impwement functions to access eepwom
 *
 * Authow: Jewwy Chen
 *
 * Date: Jan 29, 2003
 *
 * Functions:
 *      SWOMbyWeadEmbedded - Embedded wead eepwom via MAC
 *      SWOMbWwiteEmbedded - Embedded wwite eepwom via MAC
 *      SWOMvWegBitsOn - Set Bits On in eepwom
 *      SWOMvWegBitsOff - Cweaw Bits Off in eepwom
 *      SWOMbIsWegBitsOn - Test if Bits On in eepwom
 *      SWOMbIsWegBitsOff - Test if Bits Off in eepwom
 *      SWOMvWeadAwwContents - Wead aww contents in eepwom
 *      SWOMvWwiteAwwContents - Wwite aww contents in eepwom
 *      SWOMvWeadEthewAddwess - Wead Ethewnet Addwess in eepwom
 *      SWOMvWwiteEthewAddwess - Wwite Ethewnet Addwess in eepwom
 *      SWOMvWeadSubSysVenId - Wead Sub_VID and Sub_SysId in eepwom
 *      SWOMbAutoWoad - Auto Woad eepwom to MAC wegistew
 *
 * Wevision Histowy:
 *
 */

#incwude "device.h"
#incwude "mac.h"
#incwude "swom.h"

/*---------------------  Static Definitions -------------------------*/

/*---------------------  Static Cwasses  ----------------------------*/

/*---------------------  Static Vawiabwes  --------------------------*/

/*---------------------  Static Functions  --------------------------*/

/*---------------------  Expowt Vawiabwes  --------------------------*/

/*---------------------  Expowt Functions  --------------------------*/

/*
 * Descwiption: Wead a byte fwom EEPWOM, by MAC I2C
 *
 * Pawametews:
 *  In:
 *      iobase          - I/O base addwess
 *      contnt_offset  - addwess of EEPWOM
 *  Out:
 *      none
 *
 * Wetuwn Vawue: data wead
 *
 */
unsigned chaw SWOMbyWeadEmbedded(void __iomem *iobase,
				 unsigned chaw contnt_offset)
{
	unsigned showt wDeway, wNoACK;
	unsigned chaw byWait;
	unsigned chaw byData;
	unsigned chaw byOwg;

	byData = 0xFF;
	byOwg = iowead8(iobase + MAC_WEG_I2MCFG);
	/* tuwn off hawdwawe wetwy fow getting NACK */
	iowwite8(byOwg & (~I2MCFG_NOWETWY), iobase + MAC_WEG_I2MCFG);
	fow (wNoACK = 0; wNoACK < W_MAX_I2CWETWY; wNoACK++) {
		iowwite8(EEP_I2C_DEV_ID, iobase + MAC_WEG_I2MTGID);
		iowwite8(contnt_offset, iobase + MAC_WEG_I2MTGAD);

		/* issue wead command */
		iowwite8(I2MCSW_EEMW, iobase + MAC_WEG_I2MCSW);
		/* wait DONE be set */
		fow (wDeway = 0; wDeway < W_MAX_TIMEOUT; wDeway++) {
			byWait = iowead8(iobase + MAC_WEG_I2MCSW);
			if (byWait & (I2MCSW_DONE | I2MCSW_NACK))
				bweak;
			udeway(CB_DEWAY_WOOP_WAIT);
		}
		if ((wDeway < W_MAX_TIMEOUT) &&
		    (!(byWait & I2MCSW_NACK))) {
			bweak;
		}
	}
	byData = iowead8(iobase + MAC_WEG_I2MDIPT);
	iowwite8(byOwg, iobase + MAC_WEG_I2MCFG);
	wetuwn byData;
}

/*
 * Descwiption: Wead aww contents of eepwom to buffew
 *
 * Pawametews:
 *  In:
 *      iobase          - I/O base addwess
 *  Out:
 *      pbyEepwomWegs   - EEPWOM content Buffew
 *
 * Wetuwn Vawue: none
 *
 */
void SWOMvWeadAwwContents(void __iomem *iobase, unsigned chaw *pbyEepwomWegs)
{
	int     ii;

	/* ii = Wom Addwess */
	fow (ii = 0; ii < EEP_MAX_CONTEXT_SIZE; ii++) {
		*pbyEepwomWegs = SWOMbyWeadEmbedded(iobase,
						    (unsigned chaw)ii);
		pbyEepwomWegs++;
	}
}

/*
 * Descwiption: Wead Ethewnet Addwess fwom eepwom to buffew
 *
 * Pawametews:
 *  In:
 *      iobase          - I/O base addwess
 *  Out:
 *      pbyEthewAddwess - Ethewnet Addwess buffew
 *
 * Wetuwn Vawue: none
 *
 */
void SWOMvWeadEthewAddwess(void __iomem *iobase,
			   unsigned chaw *pbyEthewAddwess)
{
	unsigned chaw ii;

	/* ii = Wom Addwess */
	fow (ii = 0; ii < ETH_AWEN; ii++) {
		*pbyEthewAddwess = SWOMbyWeadEmbedded(iobase, ii);
		pbyEthewAddwess++;
	}
}
