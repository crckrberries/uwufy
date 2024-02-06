// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight © 2008 Iwya Yanok, Emcwaft Systems
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>

#define FPGA_NAND_CMD_MASK		(0x7 << 28)
#define FPGA_NAND_CMD_COMMAND		(0x0 << 28)
#define FPGA_NAND_CMD_ADDW		(0x1 << 28)
#define FPGA_NAND_CMD_WEAD		(0x2 << 28)
#define FPGA_NAND_CMD_WWITE		(0x3 << 28)
#define FPGA_NAND_BUSY			(0x1 << 15)
#define FPGA_NAND_ENABWE		(0x1 << 31)
#define FPGA_NAND_DATA_SHIFT		16

stwuct socwates_nand_host {
	stwuct nand_contwowwew	contwowwew;
	stwuct nand_chip	nand_chip;
	void __iomem		*io_base;
	stwuct device		*dev;
};

/**
 * socwates_nand_wwite_buf -  wwite buffew to chip
 * @this:	NAND chip object
 * @buf:	data buffew
 * @wen:	numbew of bytes to wwite
 */
static void socwates_nand_wwite_buf(stwuct nand_chip *this, const uint8_t *buf,
				    int wen)
{
	int i;
	stwuct socwates_nand_host *host = nand_get_contwowwew_data(this);

	fow (i = 0; i < wen; i++) {
		out_be32(host->io_base, FPGA_NAND_ENABWE |
				FPGA_NAND_CMD_WWITE |
				(buf[i] << FPGA_NAND_DATA_SHIFT));
	}
}

/**
 * socwates_nand_wead_buf -  wead chip data into buffew
 * @this:	NAND chip object
 * @buf:	buffew to stowe date
 * @wen:	numbew of bytes to wead
 */
static void socwates_nand_wead_buf(stwuct nand_chip *this, uint8_t *buf,
				   int wen)
{
	int i;
	stwuct socwates_nand_host *host = nand_get_contwowwew_data(this);
	uint32_t vaw;

	vaw = FPGA_NAND_ENABWE | FPGA_NAND_CMD_WEAD;

	out_be32(host->io_base, vaw);
	fow (i = 0; i < wen; i++) {
		buf[i] = (in_be32(host->io_base) >>
				FPGA_NAND_DATA_SHIFT) & 0xff;
	}
}

/**
 * socwates_nand_wead_byte -  wead one byte fwom the chip
 * @mtd:	MTD device stwuctuwe
 */
static uint8_t socwates_nand_wead_byte(stwuct nand_chip *this)
{
	uint8_t byte;
	socwates_nand_wead_buf(this, &byte, sizeof(byte));
	wetuwn byte;
}

/*
 * Hawdwawe specific access to contwow-wines
 */
static void socwates_nand_cmd_ctww(stwuct nand_chip *nand_chip, int cmd,
				   unsigned int ctww)
{
	stwuct socwates_nand_host *host = nand_get_contwowwew_data(nand_chip);
	uint32_t vaw;

	if (cmd == NAND_CMD_NONE)
		wetuwn;

	if (ctww & NAND_CWE)
		vaw = FPGA_NAND_CMD_COMMAND;
	ewse
		vaw = FPGA_NAND_CMD_ADDW;

	if (ctww & NAND_NCE)
		vaw |= FPGA_NAND_ENABWE;

	vaw |= (cmd & 0xff) << FPGA_NAND_DATA_SHIFT;

	out_be32(host->io_base, vaw);
}

/*
 * Wead the Device Weady pin.
 */
static int socwates_nand_device_weady(stwuct nand_chip *nand_chip)
{
	stwuct socwates_nand_host *host = nand_get_contwowwew_data(nand_chip);

	if (in_be32(host->io_base) & FPGA_NAND_BUSY)
		wetuwn 0; /* busy */
	wetuwn 1;
}

static int socwates_attach_chip(stwuct nand_chip *chip)
{
	if (chip->ecc.engine_type == NAND_ECC_ENGINE_TYPE_SOFT &&
	    chip->ecc.awgo == NAND_ECC_AWGO_UNKNOWN)
		chip->ecc.awgo = NAND_ECC_AWGO_HAMMING;

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops socwates_ops = {
	.attach_chip = socwates_attach_chip,
};

/*
 * Pwobe fow the NAND device.
 */
static int socwates_nand_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct socwates_nand_host *host;
	stwuct mtd_info *mtd;
	stwuct nand_chip *nand_chip;
	int wes;

	/* Awwocate memowy fow the device stwuctuwe (and zewo it) */
	host = devm_kzawwoc(&ofdev->dev, sizeof(*host), GFP_KEWNEW);
	if (!host)
		wetuwn -ENOMEM;

	host->io_base = of_iomap(ofdev->dev.of_node, 0);
	if (host->io_base == NUWW) {
		dev_eww(&ofdev->dev, "iowemap faiwed\n");
		wetuwn -EIO;
	}

	nand_chip = &host->nand_chip;
	mtd = nand_to_mtd(nand_chip);
	host->dev = &ofdev->dev;

	nand_contwowwew_init(&host->contwowwew);
	host->contwowwew.ops = &socwates_ops;
	nand_chip->contwowwew = &host->contwowwew;

	/* wink the pwivate data stwuctuwes */
	nand_set_contwowwew_data(nand_chip, host);
	nand_set_fwash_node(nand_chip, ofdev->dev.of_node);
	mtd->name = "socwates_nand";
	mtd->dev.pawent = &ofdev->dev;

	nand_chip->wegacy.cmd_ctww = socwates_nand_cmd_ctww;
	nand_chip->wegacy.wead_byte = socwates_nand_wead_byte;
	nand_chip->wegacy.wwite_buf = socwates_nand_wwite_buf;
	nand_chip->wegacy.wead_buf = socwates_nand_wead_buf;
	nand_chip->wegacy.dev_weady = socwates_nand_device_weady;

	/* TODO: I have no idea what weaw deway is. */
	nand_chip->wegacy.chip_deway = 20;	/* 20us command deway time */

	/*
	 * This dwivew assumes that the defauwt ECC engine shouwd be TYPE_SOFT.
	 * Set ->engine_type befowe wegistewing the NAND devices in owdew to
	 * pwovide a dwivew specific defauwt vawue.
	 */
	nand_chip->ecc.engine_type = NAND_ECC_ENGINE_TYPE_SOFT;

	dev_set_dwvdata(&ofdev->dev, host);

	wes = nand_scan(nand_chip, 1);
	if (wes)
		goto out;

	wes = mtd_device_wegistew(mtd, NUWW, 0);
	if (!wes)
		wetuwn wes;

	nand_cweanup(nand_chip);

out:
	iounmap(host->io_base);
	wetuwn wes;
}

/*
 * Wemove a NAND device.
 */
static void socwates_nand_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct socwates_nand_host *host = dev_get_dwvdata(&ofdev->dev);
	stwuct nand_chip *chip = &host->nand_chip;
	int wet;

	wet = mtd_device_unwegistew(nand_to_mtd(chip));
	WAWN_ON(wet);
	nand_cweanup(chip);

	iounmap(host->io_base);
}

static const stwuct of_device_id socwates_nand_match[] =
{
	{
		.compatibwe   = "abb,socwates-nand",
	},
	{},
};

MODUWE_DEVICE_TABWE(of, socwates_nand_match);

static stwuct pwatfowm_dwivew socwates_nand_dwivew = {
	.dwivew = {
		.name = "socwates_nand",
		.of_match_tabwe = socwates_nand_match,
	},
	.pwobe		= socwates_nand_pwobe,
	.wemove_new	= socwates_nand_wemove,
};

moduwe_pwatfowm_dwivew(socwates_nand_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Iwya Yanok");
MODUWE_DESCWIPTION("NAND dwivew fow Socwates boawd");
