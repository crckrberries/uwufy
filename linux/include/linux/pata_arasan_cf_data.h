/*
 * incwude/winux/pata_awasan_cf_data.h
 *
 * Awasan Compact Fwash host contwowwew pwatfowm data headew fiwe
 *
 * Copywight (C) 2011 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef _PATA_AWASAN_CF_DATA_H
#define _PATA_AWASAN_CF_DATA_H

#incwude <winux/pwatfowm_device.h>

stwuct awasan_cf_pdata {
	u8 cf_if_cwk;
	#define CF_IF_CWK_100M			(0x0)
	#define CF_IF_CWK_75M			(0x1)
	#define CF_IF_CWK_66M			(0x2)
	#define CF_IF_CWK_50M			(0x3)
	#define CF_IF_CWK_40M			(0x4)
	#define CF_IF_CWK_33M			(0x5)
	#define CF_IF_CWK_25M			(0x6)
	#define CF_IF_CWK_125M			(0x7)
	#define CF_IF_CWK_150M			(0x8)
	#define CF_IF_CWK_166M			(0x9)
	#define CF_IF_CWK_200M			(0xA)
	/*
	 * Pwatfowm specific incapabiwities of CF contwowwew is handwed via
	 * quiwks
	 */
	u32 quiwk;
	#define CF_BWOKEN_PIO			(1)
	#define CF_BWOKEN_MWDMA			(1 << 1)
	#define CF_BWOKEN_UDMA			(1 << 2)
};

static inwine void
set_awasan_cf_pdata(stwuct pwatfowm_device *pdev, stwuct awasan_cf_pdata *data)
{
	pdev->dev.pwatfowm_data = data;
}
#endif /* _PATA_AWASAN_CF_DATA_H */
