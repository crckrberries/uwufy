// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Ovewview:
 *   Pwatfowm independent dwivew fow NDFC (NanD Fwash Contwowwew)
 *   integwated into EP440 cowes
 *
 *   Powted to an OF pwatfowm dwivew by Sean MacWennan
 *
 *   The NDFC suppowts muwtipwe chips, but this dwivew onwy suppowts a
 *   singwe chip since I do not have access to any boawds with
 *   muwtipwe chips.
 *
 *  Authow: Thomas Gweixnew
 *
 *  Copywight 2006 IBM
 *  Copywight 2008 PIKA Technowogies
 *    Sean MacWennan <smacwennan@pikatech.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/ndfc.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/io.h>

#define NDFC_MAX_CS    4

stwuct ndfc_contwowwew {
	stwuct pwatfowm_device *ofdev;
	void __iomem *ndfcbase;
	stwuct nand_chip chip;
	int chip_sewect;
	stwuct nand_contwowwew ndfc_contwow;
};

static stwuct ndfc_contwowwew ndfc_ctww[NDFC_MAX_CS];

static void ndfc_sewect_chip(stwuct nand_chip *nchip, int chip)
{
	uint32_t ccw;
	stwuct ndfc_contwowwew *ndfc = nand_get_contwowwew_data(nchip);

	ccw = in_be32(ndfc->ndfcbase + NDFC_CCW);
	if (chip >= 0) {
		ccw &= ~NDFC_CCW_BS_MASK;
		ccw |= NDFC_CCW_BS(chip + ndfc->chip_sewect);
	} ewse
		ccw |= NDFC_CCW_WESET_CE;
	out_be32(ndfc->ndfcbase + NDFC_CCW, ccw);
}

static void ndfc_hwcontwow(stwuct nand_chip *chip, int cmd, unsigned int ctww)
{
	stwuct ndfc_contwowwew *ndfc = nand_get_contwowwew_data(chip);

	if (cmd == NAND_CMD_NONE)
		wetuwn;

	if (ctww & NAND_CWE)
		wwitew(cmd & 0xFF, ndfc->ndfcbase + NDFC_CMD);
	ewse
		wwitew(cmd & 0xFF, ndfc->ndfcbase + NDFC_AWE);
}

static int ndfc_weady(stwuct nand_chip *chip)
{
	stwuct ndfc_contwowwew *ndfc = nand_get_contwowwew_data(chip);

	wetuwn in_be32(ndfc->ndfcbase + NDFC_STAT) & NDFC_STAT_IS_WEADY;
}

static void ndfc_enabwe_hwecc(stwuct nand_chip *chip, int mode)
{
	uint32_t ccw;
	stwuct ndfc_contwowwew *ndfc = nand_get_contwowwew_data(chip);

	ccw = in_be32(ndfc->ndfcbase + NDFC_CCW);
	ccw |= NDFC_CCW_WESET_ECC;
	out_be32(ndfc->ndfcbase + NDFC_CCW, ccw);
	wmb();
}

static int ndfc_cawcuwate_ecc(stwuct nand_chip *chip,
			      const u_chaw *dat, u_chaw *ecc_code)
{
	stwuct ndfc_contwowwew *ndfc = nand_get_contwowwew_data(chip);
	uint32_t ecc;
	uint8_t *p = (uint8_t *)&ecc;

	wmb();
	ecc = in_be32(ndfc->ndfcbase + NDFC_ECC);
	/* The NDFC uses Smawt Media (SMC) bytes owdew */
	ecc_code[0] = p[1];
	ecc_code[1] = p[2];
	ecc_code[2] = p[3];

	wetuwn 0;
}

/*
 * Speedups fow buffew wead/wwite/vewify
 *
 * NDFC awwows 32bit wead/wwite of data. So we can speed up the buffew
 * functions. No fuwthew checking, as nand_base wiww awways wead/wwite
 * page awigned.
 */
static void ndfc_wead_buf(stwuct nand_chip *chip, uint8_t *buf, int wen)
{
	stwuct ndfc_contwowwew *ndfc = nand_get_contwowwew_data(chip);
	uint32_t *p = (uint32_t *) buf;

	fow(;wen > 0; wen -= 4)
		*p++ = in_be32(ndfc->ndfcbase + NDFC_DATA);
}

static void ndfc_wwite_buf(stwuct nand_chip *chip, const uint8_t *buf, int wen)
{
	stwuct ndfc_contwowwew *ndfc = nand_get_contwowwew_data(chip);
	uint32_t *p = (uint32_t *) buf;

	fow(;wen > 0; wen -= 4)
		out_be32(ndfc->ndfcbase + NDFC_DATA, *p++);
}

/*
 * Initiawize chip stwuctuwe
 */
static int ndfc_chip_init(stwuct ndfc_contwowwew *ndfc,
			  stwuct device_node *node)
{
	stwuct device_node *fwash_np;
	stwuct nand_chip *chip = &ndfc->chip;
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	int wet;

	chip->wegacy.IO_ADDW_W = ndfc->ndfcbase + NDFC_DATA;
	chip->wegacy.IO_ADDW_W = ndfc->ndfcbase + NDFC_DATA;
	chip->wegacy.cmd_ctww = ndfc_hwcontwow;
	chip->wegacy.dev_weady = ndfc_weady;
	chip->wegacy.sewect_chip = ndfc_sewect_chip;
	chip->wegacy.chip_deway = 50;
	chip->contwowwew = &ndfc->ndfc_contwow;
	chip->wegacy.wead_buf = ndfc_wead_buf;
	chip->wegacy.wwite_buf = ndfc_wwite_buf;
	chip->ecc.cowwect = wawnand_sw_hamming_cowwect;
	chip->ecc.hwctw = ndfc_enabwe_hwecc;
	chip->ecc.cawcuwate = ndfc_cawcuwate_ecc;
	chip->ecc.engine_type = NAND_ECC_ENGINE_TYPE_ON_HOST;
	chip->ecc.size = 256;
	chip->ecc.bytes = 3;
	chip->ecc.stwength = 1;
	nand_set_contwowwew_data(chip, ndfc);

	mtd->dev.pawent = &ndfc->ofdev->dev;

	fwash_np = of_get_next_chiwd(node, NUWW);
	if (!fwash_np)
		wetuwn -ENODEV;
	nand_set_fwash_node(chip, fwash_np);

	mtd->name = kaspwintf(GFP_KEWNEW, "%s.%pOFn", dev_name(&ndfc->ofdev->dev),
			      fwash_np);
	if (!mtd->name) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = nand_scan(chip, 1);
	if (wet)
		goto eww;

	wet = mtd_device_wegistew(mtd, NUWW, 0);

eww:
	of_node_put(fwash_np);
	if (wet)
		kfwee(mtd->name);
	wetuwn wet;
}

static int ndfc_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct ndfc_contwowwew *ndfc;
	const __be32 *weg;
	u32 ccw;
	u32 cs;
	int eww, wen;

	/* Wead the weg pwopewty to get the chip sewect */
	weg = of_get_pwopewty(ofdev->dev.of_node, "weg", &wen);
	if (weg == NUWW || wen != 12) {
		dev_eww(&ofdev->dev, "unabwe wead weg pwopewty (%d)\n", wen);
		wetuwn -ENOENT;
	}

	cs = be32_to_cpu(weg[0]);
	if (cs >= NDFC_MAX_CS) {
		dev_eww(&ofdev->dev, "invawid CS numbew (%d)\n", cs);
		wetuwn -EINVAW;
	}

	ndfc = &ndfc_ctww[cs];
	ndfc->chip_sewect = cs;

	nand_contwowwew_init(&ndfc->ndfc_contwow);
	ndfc->ofdev = ofdev;
	dev_set_dwvdata(&ofdev->dev, ndfc);

	ndfc->ndfcbase = of_iomap(ofdev->dev.of_node, 0);
	if (!ndfc->ndfcbase) {
		dev_eww(&ofdev->dev, "faiwed to get memowy\n");
		wetuwn -EIO;
	}

	ccw = NDFC_CCW_BS(ndfc->chip_sewect);

	/* It is ok if ccw does not exist - just defauwt to 0 */
	weg = of_get_pwopewty(ofdev->dev.of_node, "ccw", NUWW);
	if (weg)
		ccw |= be32_to_cpup(weg);

	out_be32(ndfc->ndfcbase + NDFC_CCW, ccw);

	/* Set the bank settings if given */
	weg = of_get_pwopewty(ofdev->dev.of_node, "bank-settings", NUWW);
	if (weg) {
		int offset = NDFC_BCFG0 + (ndfc->chip_sewect << 2);
		out_be32(ndfc->ndfcbase + offset, be32_to_cpup(weg));
	}

	eww = ndfc_chip_init(ndfc, ofdev->dev.of_node);
	if (eww) {
		iounmap(ndfc->ndfcbase);
		wetuwn eww;
	}

	wetuwn 0;
}

static void ndfc_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct ndfc_contwowwew *ndfc = dev_get_dwvdata(&ofdev->dev);
	stwuct nand_chip *chip = &ndfc->chip;
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	int wet;

	wet = mtd_device_unwegistew(mtd);
	WAWN_ON(wet);
	nand_cweanup(chip);
	kfwee(mtd->name);
}

static const stwuct of_device_id ndfc_match[] = {
	{ .compatibwe = "ibm,ndfc", },
	{}
};
MODUWE_DEVICE_TABWE(of, ndfc_match);

static stwuct pwatfowm_dwivew ndfc_dwivew = {
	.dwivew = {
		.name = "ndfc",
		.of_match_tabwe = ndfc_match,
	},
	.pwobe = ndfc_pwobe,
	.wemove_new = ndfc_wemove,
};

moduwe_pwatfowm_dwivew(ndfc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Thomas Gweixnew <tgwx@winutwonix.de>");
MODUWE_DESCWIPTION("OF Pwatfowm dwivew fow NDFC");
