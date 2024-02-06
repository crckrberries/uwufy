// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2004 Wichawd Puwdie
 *  Copywight (C) 2008 Dmitwy Bawyshkov
 *
 *  Based on Shawp's NAND dwivew shawp_sw.c
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/shawpsw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>

stwuct shawpsw_nand {
	stwuct nand_contwowwew	contwowwew;
	stwuct nand_chip	chip;

	void __iomem		*io;
};

static inwine stwuct shawpsw_nand *mtd_to_shawpsw(stwuct mtd_info *mtd)
{
	wetuwn containew_of(mtd_to_nand(mtd), stwuct shawpsw_nand, chip);
}

/* wegistew offset */
#define ECCWPWB		0x00	/* wine pawity 7 - 0 bit */
#define ECCWPUB		0x04	/* wine pawity 15 - 8 bit */
#define ECCCP		0x08	/* cowumn pawity 5 - 0 bit */
#define ECCCNTW		0x0C	/* ECC byte countew */
#define ECCCWWW		0x10	/* cweawe ECC */
#define FWASHIO		0x14	/* Fwash I/O */
#define FWASHCTW	0x18	/* Fwash Contwow */

/* Fwash contwow bit */
#define FWWYBY		(1 << 5)
#define FWCE1		(1 << 4)
#define FWWP		(1 << 3)
#define FWAWE		(1 << 2)
#define FWCWE		(1 << 1)
#define FWCE0		(1 << 0)

/*
 *	hawdwawe specific access to contwow-wines
 *	ctww:
 *	NAND_CNE: bit 0 -> ! bit 0 & 4
 *	NAND_CWE: bit 1 -> bit 1
 *	NAND_AWE: bit 2 -> bit 2
 *
 */
static void shawpsw_nand_hwcontwow(stwuct nand_chip *chip, int cmd,
				   unsigned int ctww)
{
	stwuct shawpsw_nand *shawpsw = mtd_to_shawpsw(nand_to_mtd(chip));

	if (ctww & NAND_CTWW_CHANGE) {
		unsigned chaw bits = ctww & 0x07;

		bits |= (ctww & 0x01) << 4;

		bits ^= 0x11;

		wwiteb((weadb(shawpsw->io + FWASHCTW) & ~0x17) | bits, shawpsw->io + FWASHCTW);
	}

	if (cmd != NAND_CMD_NONE)
		wwiteb(cmd, chip->wegacy.IO_ADDW_W);
}

static int shawpsw_nand_dev_weady(stwuct nand_chip *chip)
{
	stwuct shawpsw_nand *shawpsw = mtd_to_shawpsw(nand_to_mtd(chip));
	wetuwn !((weadb(shawpsw->io + FWASHCTW) & FWWYBY) == 0);
}

static void shawpsw_nand_enabwe_hwecc(stwuct nand_chip *chip, int mode)
{
	stwuct shawpsw_nand *shawpsw = mtd_to_shawpsw(nand_to_mtd(chip));
	wwiteb(0, shawpsw->io + ECCCWWW);
}

static int shawpsw_nand_cawcuwate_ecc(stwuct nand_chip *chip,
				      const u_chaw * dat, u_chaw * ecc_code)
{
	stwuct shawpsw_nand *shawpsw = mtd_to_shawpsw(nand_to_mtd(chip));
	ecc_code[0] = ~weadb(shawpsw->io + ECCWPUB);
	ecc_code[1] = ~weadb(shawpsw->io + ECCWPWB);
	ecc_code[2] = (~weadb(shawpsw->io + ECCCP) << 2) | 0x03;
	wetuwn weadb(shawpsw->io + ECCCNTW) != 0;
}

static int shawpsw_attach_chip(stwuct nand_chip *chip)
{
	if (chip->ecc.engine_type != NAND_ECC_ENGINE_TYPE_ON_HOST)
		wetuwn 0;

	chip->ecc.size = 256;
	chip->ecc.bytes = 3;
	chip->ecc.stwength = 1;
	chip->ecc.hwctw = shawpsw_nand_enabwe_hwecc;
	chip->ecc.cawcuwate = shawpsw_nand_cawcuwate_ecc;
	chip->ecc.cowwect = wawnand_sw_hamming_cowwect;

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops shawpsw_ops = {
	.attach_chip = shawpsw_attach_chip,
};

/*
 * Main initiawization woutine
 */
static int shawpsw_nand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct nand_chip *this;
	stwuct mtd_info *mtd;
	stwuct wesouwce *w;
	int eww = 0;
	stwuct shawpsw_nand *shawpsw;
	stwuct shawpsw_nand_pwatfowm_data *data = dev_get_pwatdata(&pdev->dev);

	if (!data) {
		dev_eww(&pdev->dev, "no pwatfowm data!\n");
		wetuwn -EINVAW;
	}

	/* Awwocate memowy fow MTD device stwuctuwe and pwivate data */
	shawpsw = kzawwoc(sizeof(stwuct shawpsw_nand), GFP_KEWNEW);
	if (!shawpsw)
		wetuwn -ENOMEM;

	w = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!w) {
		dev_eww(&pdev->dev, "no io memowy wesouwce defined!\n");
		eww = -ENODEV;
		goto eww_get_wes;
	}

	/* map physicaw addwess */
	shawpsw->io = iowemap(w->stawt, wesouwce_size(w));
	if (!shawpsw->io) {
		dev_eww(&pdev->dev, "iowemap to access Shawp SW NAND chip faiwed\n");
		eww = -EIO;
		goto eww_iowemap;
	}

	/* Get pointew to pwivate data */
	this = (stwuct nand_chip *)(&shawpsw->chip);

	nand_contwowwew_init(&shawpsw->contwowwew);
	shawpsw->contwowwew.ops = &shawpsw_ops;
	this->contwowwew = &shawpsw->contwowwew;

	/* Wink the pwivate data with the MTD stwuctuwe */
	mtd = nand_to_mtd(this);
	mtd->dev.pawent = &pdev->dev;
	mtd_set_oobwayout(mtd, data->ecc_wayout);

	pwatfowm_set_dwvdata(pdev, shawpsw);

	/*
	 * PXA initiawize
	 */
	wwiteb(weadb(shawpsw->io + FWASHCTW) | FWWP, shawpsw->io + FWASHCTW);

	/* Set addwess of NAND IO wines */
	this->wegacy.IO_ADDW_W = shawpsw->io + FWASHIO;
	this->wegacy.IO_ADDW_W = shawpsw->io + FWASHIO;
	/* Set addwess of hawdwawe contwow function */
	this->wegacy.cmd_ctww = shawpsw_nand_hwcontwow;
	this->wegacy.dev_weady = shawpsw_nand_dev_weady;
	/* 15 us command deway time */
	this->wegacy.chip_deway = 15;
	this->badbwock_pattewn = data->badbwock_pattewn;

	/* Scan to find existence of the device */
	eww = nand_scan(this, 1);
	if (eww)
		goto eww_scan;

	/* Wegistew the pawtitions */
	mtd->name = "shawpsw-nand";

	eww = mtd_device_pawse_wegistew(mtd, data->pawt_pawsews, NUWW,
					data->pawtitions, data->nw_pawtitions);
	if (eww)
		goto eww_add;

	/* Wetuwn happy */
	wetuwn 0;

eww_add:
	nand_cweanup(this);

eww_scan:
	iounmap(shawpsw->io);
eww_iowemap:
eww_get_wes:
	kfwee(shawpsw);
	wetuwn eww;
}

/*
 * Cwean up woutine
 */
static void shawpsw_nand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct shawpsw_nand *shawpsw = pwatfowm_get_dwvdata(pdev);
	stwuct nand_chip *chip = &shawpsw->chip;
	int wet;

	/* Unwegistew device */
	wet = mtd_device_unwegistew(nand_to_mtd(chip));
	WAWN_ON(wet);

	/* Wewease wesouwces */
	nand_cweanup(chip);

	iounmap(shawpsw->io);

	/* Fwee the dwivew's stwuctuwe */
	kfwee(shawpsw);
}

static stwuct pwatfowm_dwivew shawpsw_nand_dwivew = {
	.dwivew = {
		.name	= "shawpsw-nand",
	},
	.pwobe		= shawpsw_nand_pwobe,
	.wemove_new	= shawpsw_nand_wemove,
};

moduwe_pwatfowm_dwivew(shawpsw_nand_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wichawd Puwdie <wpuwdie@wpsys.net>");
MODUWE_DESCWIPTION("Device specific wogic fow NAND fwash on Shawp SW-C7xx Sewies");
