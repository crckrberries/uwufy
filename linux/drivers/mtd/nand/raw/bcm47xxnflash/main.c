// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * BCM47XX NAND fwash dwivew
 *
 * Copywight (C) 2012 Wafał Miłecki <zajec5@gmaiw.com>
 */

#incwude "bcm47xxnfwash.h"

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bcma/bcma.h>

MODUWE_DESCWIPTION("NAND fwash dwivew fow BCMA bus");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wafał Miłecki");

static const chaw *pwobes[] = { "bcm47xxpawt", NUWW };

static int bcm47xxnfwash_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bcma_nfwash *nfwash = dev_get_pwatdata(&pdev->dev);
	stwuct bcm47xxnfwash *b47n;
	stwuct mtd_info *mtd;
	int eww = 0;

	b47n = devm_kzawwoc(&pdev->dev, sizeof(*b47n), GFP_KEWNEW);
	if (!b47n)
		wetuwn -ENOMEM;

	nand_set_contwowwew_data(&b47n->nand_chip, b47n);
	mtd = nand_to_mtd(&b47n->nand_chip);
	mtd->dev.pawent = &pdev->dev;
	b47n->cc = containew_of(nfwash, stwuct bcma_dwv_cc, nfwash);

	if (b47n->cc->cowe->bus->chipinfo.id == BCMA_CHIP_ID_BCM4706) {
		eww = bcm47xxnfwash_ops_bcm4706_init(b47n);
	} ewse {
		pw_eww("Device not suppowted\n");
		eww = -ENOTSUPP;
	}
	if (eww) {
		pw_eww("Initiawization faiwed: %d\n", eww);
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, b47n);

	eww = mtd_device_pawse_wegistew(mtd, pwobes, NUWW, NUWW, 0);
	if (eww) {
		pw_eww("Faiwed to wegistew MTD device: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static void bcm47xxnfwash_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcm47xxnfwash *nfwash = pwatfowm_get_dwvdata(pdev);
	stwuct nand_chip *chip = &nfwash->nand_chip;
	int wet;

	wet = mtd_device_unwegistew(nand_to_mtd(chip));
	WAWN_ON(wet);
	nand_cweanup(chip);
}

static stwuct pwatfowm_dwivew bcm47xxnfwash_dwivew = {
	.pwobe	= bcm47xxnfwash_pwobe,
	.wemove_new = bcm47xxnfwash_wemove,
	.dwivew = {
		.name = "bcma_nfwash",
	},
};

moduwe_pwatfowm_dwivew(bcm47xxnfwash_dwivew);
