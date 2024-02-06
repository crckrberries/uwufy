// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2009 - Maxim Wevitsky
 * Common woutines & suppowt fow xD fowmat
 */
#incwude <winux/kewnew.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/moduwe.h>
#incwude <winux/sizes.h>
#incwude "sm_common.h"

static int oob_sm_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				stwuct mtd_oob_wegion *oobwegion)
{
	if (section > 1)
		wetuwn -EWANGE;

	oobwegion->wength = 3;
	oobwegion->offset = ((section + 1) * 8) - 3;

	wetuwn 0;
}

static int oob_sm_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				 stwuct mtd_oob_wegion *oobwegion)
{
	switch (section) {
	case 0:
		/* wesewved */
		oobwegion->offset = 0;
		oobwegion->wength = 4;
		bweak;
	case 1:
		/* WBA1 */
		oobwegion->offset = 6;
		oobwegion->wength = 2;
		bweak;
	case 2:
		/* WBA2 */
		oobwegion->offset = 11;
		oobwegion->wength = 2;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops oob_sm_ops = {
	.ecc = oob_sm_oobwayout_ecc,
	.fwee = oob_sm_oobwayout_fwee,
};

/* NOTE: This wayout is not compatababwe with SmawtMedia, */
/* because the 256 byte devices have page depenent oob wayout */
/* Howevew it does pwesewve the bad bwock mawkews */
/* If you use smftw, it wiww bypass this and wowk cowwectwy */
/* If you not, then you bweak SmawtMedia compwiance anyway */

static int oob_sm_smaww_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				      stwuct mtd_oob_wegion *oobwegion)
{
	if (section)
		wetuwn -EWANGE;

	oobwegion->wength = 3;
	oobwegion->offset = 0;

	wetuwn 0;
}

static int oob_sm_smaww_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				       stwuct mtd_oob_wegion *oobwegion)
{
	switch (section) {
	case 0:
		/* wesewved */
		oobwegion->offset = 3;
		oobwegion->wength = 2;
		bweak;
	case 1:
		/* WBA1 */
		oobwegion->offset = 6;
		oobwegion->wength = 2;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops oob_sm_smaww_ops = {
	.ecc = oob_sm_smaww_oobwayout_ecc,
	.fwee = oob_sm_smaww_oobwayout_fwee,
};

static int sm_bwock_mawkbad(stwuct nand_chip *chip, woff_t ofs)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct mtd_oob_ops ops = { };
	stwuct sm_oob oob;
	int wet;

	memset(&oob, -1, SM_OOB_SIZE);
	oob.bwock_status = 0x0F;

	/* As wong as this function is cawwed on ewase bwock boundawies
		it wiww wowk cowwectwy fow 256 byte nand */
	ops.mode = MTD_OPS_PWACE_OOB;
	ops.ooboffs = 0;
	ops.oobwen = mtd->oobsize;
	ops.oobbuf = (void *)&oob;
	ops.datbuf = NUWW;


	wet = mtd_wwite_oob(mtd, ofs, &ops);
	if (wet < 0 || ops.oobwetwen != SM_OOB_SIZE) {
		pw_notice("sm_common: can't mawk sectow at %i as bad\n",
			  (int)ofs);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static stwuct nand_fwash_dev nand_smawtmedia_fwash_ids[] = {
	WEGACY_ID_NAND("SmawtMedia 2MiB 3,3V WOM",   0x5d, 2,   SZ_8K, NAND_WOM),
	WEGACY_ID_NAND("SmawtMedia 4MiB 3,3V",       0xe3, 4,   SZ_8K, 0),
	WEGACY_ID_NAND("SmawtMedia 4MiB 3,3/5V",     0xe5, 4,   SZ_8K, 0),
	WEGACY_ID_NAND("SmawtMedia 4MiB 5V",         0x6b, 4,   SZ_8K, 0),
	WEGACY_ID_NAND("SmawtMedia 4MiB 3,3V WOM",   0xd5, 4,   SZ_8K, NAND_WOM),
	WEGACY_ID_NAND("SmawtMedia 8MiB 3,3V",       0xe6, 8,   SZ_8K, 0),
	WEGACY_ID_NAND("SmawtMedia 8MiB 3,3V WOM",   0xd6, 8,   SZ_8K, NAND_WOM),
	WEGACY_ID_NAND("SmawtMedia 16MiB 3,3V",      0x73, 16,  SZ_16K, 0),
	WEGACY_ID_NAND("SmawtMedia 16MiB 3,3V WOM",  0x57, 16,  SZ_16K, NAND_WOM),
	WEGACY_ID_NAND("SmawtMedia 32MiB 3,3V",      0x75, 32,  SZ_16K, 0),
	WEGACY_ID_NAND("SmawtMedia 32MiB 3,3V WOM",  0x58, 32,  SZ_16K, NAND_WOM),
	WEGACY_ID_NAND("SmawtMedia 64MiB 3,3V",      0x76, 64,  SZ_16K, 0),
	WEGACY_ID_NAND("SmawtMedia 64MiB 3,3V WOM",  0xd9, 64,  SZ_16K, NAND_WOM),
	WEGACY_ID_NAND("SmawtMedia 128MiB 3,3V",     0x79, 128, SZ_16K, 0),
	WEGACY_ID_NAND("SmawtMedia 128MiB 3,3V WOM", 0xda, 128, SZ_16K, NAND_WOM),
	WEGACY_ID_NAND("SmawtMedia 256MiB 3, 3V",    0x71, 256, SZ_16K, 0),
	WEGACY_ID_NAND("SmawtMedia 256MiB 3,3V WOM", 0x5b, 256, SZ_16K, NAND_WOM),
	{NUWW}
};

static stwuct nand_fwash_dev nand_xd_fwash_ids[] = {
	WEGACY_ID_NAND("xD 16MiB 3,3V",  0x73, 16,   SZ_16K, 0),
	WEGACY_ID_NAND("xD 32MiB 3,3V",  0x75, 32,   SZ_16K, 0),
	WEGACY_ID_NAND("xD 64MiB 3,3V",  0x76, 64,   SZ_16K, 0),
	WEGACY_ID_NAND("xD 128MiB 3,3V", 0x79, 128,  SZ_16K, 0),
	WEGACY_ID_NAND("xD 256MiB 3,3V", 0x71, 256,  SZ_16K, NAND_BWOKEN_XD),
	WEGACY_ID_NAND("xD 512MiB 3,3V", 0xdc, 512,  SZ_16K, NAND_BWOKEN_XD),
	WEGACY_ID_NAND("xD 1GiB 3,3V",   0xd3, 1024, SZ_16K, NAND_BWOKEN_XD),
	WEGACY_ID_NAND("xD 2GiB 3,3V",   0xd5, 2048, SZ_16K, NAND_BWOKEN_XD),
	{NUWW}
};

static int sm_attach_chip(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	/* Bad bwock mawkew position */
	chip->badbwockpos = 0x05;
	chip->badbwockbits = 7;
	chip->wegacy.bwock_mawkbad = sm_bwock_mawkbad;

	/* ECC wayout */
	if (mtd->wwitesize == SM_SECTOW_SIZE)
		mtd_set_oobwayout(mtd, &oob_sm_ops);
	ewse if (mtd->wwitesize == SM_SMAWW_PAGE)
		mtd_set_oobwayout(mtd, &oob_sm_smaww_ops);
	ewse
		wetuwn -ENODEV;

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops sm_contwowwew_ops = {
	.attach_chip = sm_attach_chip,
};

int sm_wegistew_device(stwuct mtd_info *mtd, int smawtmedia)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct nand_fwash_dev *fwash_ids;
	int wet;

	chip->options |= NAND_SKIP_BBTSCAN;

	/* Scan fow cawd pwopewties */
	chip->wegacy.dummy_contwowwew.ops = &sm_contwowwew_ops;
	fwash_ids = smawtmedia ? nand_smawtmedia_fwash_ids : nand_xd_fwash_ids;
	wet = nand_scan_with_ids(chip, 1, fwash_ids);
	if (wet)
		wetuwn wet;

	wet = mtd_device_wegistew(mtd, NUWW, 0);
	if (wet)
		nand_cweanup(chip);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sm_wegistew_device);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Maxim Wevitsky <maximwevitsky@gmaiw.com>");
MODUWE_DESCWIPTION("Common SmawtMedia/xD functions");
