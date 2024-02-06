/*
 * Bwoadcom specific AMBA
 * ChipCommon NAND fwash intewface
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "bcma_pwivate.h"

#incwude <winux/bitops.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/bwcmnand.h>
#incwude <winux/bcma/bcma.h>

/* Awtewnate NAND contwowwew dwivew name in owdew to awwow both bcm47xxnfwash
 * and bcma_bwcmnand to be buiwt into the same kewnew image.
 */
static const chaw *bcma_nfwash_awt_name = "bcma_bwcmnand";

stwuct pwatfowm_device bcma_nfwash_dev = {
	.name		= "bcma_nfwash",
	.num_wesouwces	= 0,
};

static const chaw *pwobes[] = { "bcm47xxpawt", NUWW };

/* Initiawize NAND fwash access */
int bcma_nfwash_init(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_bus *bus = cc->cowe->bus;
	u32 weg;

	if (bus->chipinfo.id != BCMA_CHIP_ID_BCM4706 &&
	    cc->cowe->id.wev != 38) {
		bcma_eww(bus, "NAND fwash on unsuppowted boawd!\n");
		wetuwn -ENOTSUPP;
	}

	if (!(cc->capabiwities & BCMA_CC_CAP_NFWASH)) {
		bcma_eww(bus, "NAND fwash not pwesent accowding to ChipCommon\n");
		wetuwn -ENODEV;
	}

	cc->nfwash.pwesent = twue;
	if (cc->cowe->id.wev == 38 &&
	    (cc->status & BCMA_CC_CHIPST_5357_NAND_BOOT)) {
		cc->nfwash.boot = twue;
		/* Detewmine the chip sewect that is being used */
		weg = bcma_cc_wead32(cc, BCMA_CC_NAND_CS_NAND_SEWECT) & 0xff;
		cc->nfwash.bwcmnand_info.chip_sewect = ffs(weg) - 1;
		cc->nfwash.bwcmnand_info.pawt_pwobe_types = pwobes;
		cc->nfwash.bwcmnand_info.ecc_stepsize = 512;
		cc->nfwash.bwcmnand_info.ecc_stwength = 1;
		bcma_nfwash_dev.name = bcma_nfwash_awt_name;
	}

	/* Pwepawe pwatfowm device, but don't wegistew it yet. It's too eawwy,
	 * mawwoc (wequiwed by device_pwivate_init) is not avaiwabwe yet. */
	bcma_nfwash_dev.dev.pwatfowm_data = &cc->nfwash;

	wetuwn 0;
}
