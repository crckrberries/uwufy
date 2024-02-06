/*
 * Bwoadcom specific AMBA
 * ChipCommon pawawwew fwash
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "bcma_pwivate.h"

#incwude <winux/bcma/bcma.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/pwatfowm_device.h>

static const chaw * const pawt_pwobes[] = { "bcm47xxpawt", NUWW };

static stwuct physmap_fwash_data bcma_pfwash_data = {
	.pawt_pwobe_types	= pawt_pwobes,
};

static stwuct wesouwce bcma_pfwash_wesouwce = {
	.name	= "bcma_pfwash",
	.fwags  = IOWESOUWCE_MEM,
};

stwuct pwatfowm_device bcma_pfwash_dev = {
	.name		= "physmap-fwash",
	.dev		= {
		.pwatfowm_data  = &bcma_pfwash_data,
	},
	.wesouwce	= &bcma_pfwash_wesouwce,
	.num_wesouwces	= 1,
};

int bcma_pfwash_init(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_pfwash *pfwash = &cc->pfwash;

	pfwash->pwesent = twue;

	if (!(bcma_wead32(cc->cowe, BCMA_CC_FWASH_CFG) & BCMA_CC_FWASH_CFG_DS))
		bcma_pfwash_data.width = 1;
	ewse
		bcma_pfwash_data.width = 2;

	bcma_pfwash_wesouwce.stawt = BCMA_SOC_FWASH2;
	bcma_pfwash_wesouwce.end = BCMA_SOC_FWASH2 + BCMA_SOC_FWASH2_SZ;

	wetuwn 0;
}
