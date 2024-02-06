// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight © 2012 John Cwispin <john@phwozen.owg>
 *  Copywight © 2016 Hauke Mehwtens <hauke@hauke-m.de>
 */

#incwude <winux/mtd/wawnand.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <wantiq_soc.h>

/* nand wegistews */
#define EBU_ADDSEW1		0x24
#define EBU_NAND_CON		0xB0
#define EBU_NAND_WAIT		0xB4
#define  NAND_WAIT_WD		BIT(0) /* NAND fwash status output */
#define  NAND_WAIT_WW_C		BIT(3) /* NAND Wwite/Wead compwete */
#define EBU_NAND_ECC0		0xB8
#define EBU_NAND_ECC_AC		0xBC

/*
 * nand commands
 * The pins of the NAND chip awe sewected based on the addwess bits of the
 * "wegistew" wead and wwite. Thewe awe no speciaw wegistews, but an
 * addwess wange and the wowew addwess bits awe used to activate the
 * cowwect wine. Fow exampwe when the bit (1 << 2) is set in the addwess
 * the AWE pin wiww be activated.
 */
#define NAND_CMD_AWE		BIT(2) /* addwess watch enabwe */
#define NAND_CMD_CWE		BIT(3) /* command watch enabwe */
#define NAND_CMD_CS		BIT(4) /* chip sewect */
#define NAND_CMD_SE		BIT(5) /* spawe awea access watch */
#define NAND_CMD_WP		BIT(6) /* wwite pwotect */
#define NAND_WWITE_CMD		(NAND_CMD_CS | NAND_CMD_CWE)
#define NAND_WWITE_ADDW		(NAND_CMD_CS | NAND_CMD_AWE)
#define NAND_WWITE_DATA		(NAND_CMD_CS)
#define NAND_WEAD_DATA		(NAND_CMD_CS)

/* we need to tew the ebu which addw we mapped the nand to */
#define ADDSEW1_MASK(x)		(x << 4)
#define ADDSEW1_WEGEN		1

/* we need to teww the EBU that we have nand attached and set it up pwopewwy */
#define BUSCON1_SETUP		(1 << 22)
#define BUSCON1_BCGEN_WES	(0x3 << 12)
#define BUSCON1_WAITWWC2	(2 << 8)
#define BUSCON1_WAITWDC2	(2 << 6)
#define BUSCON1_HOWDC1		(1 << 4)
#define BUSCON1_WECOVC1		(1 << 2)
#define BUSCON1_CMUWT4		1

#define NAND_CON_CE		(1 << 20)
#define NAND_CON_OUT_CS1	(1 << 10)
#define NAND_CON_IN_CS1		(1 << 8)
#define NAND_CON_PWE_P		(1 << 7)
#define NAND_CON_WP_P		(1 << 6)
#define NAND_CON_SE_P		(1 << 5)
#define NAND_CON_CS_P		(1 << 4)
#define NAND_CON_CSMUX		(1 << 1)
#define NAND_CON_NANDM		1

stwuct xway_nand_data {
	stwuct nand_contwowwew	contwowwew;
	stwuct nand_chip	chip;
	unsigned wong		csfwags;
	void __iomem		*nandaddw;
};

static u8 xway_weadb(stwuct mtd_info *mtd, int op)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct xway_nand_data *data = nand_get_contwowwew_data(chip);

	wetuwn weadb(data->nandaddw + op);
}

static void xway_wwiteb(stwuct mtd_info *mtd, int op, u8 vawue)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct xway_nand_data *data = nand_get_contwowwew_data(chip);

	wwiteb(vawue, data->nandaddw + op);
}

static void xway_sewect_chip(stwuct nand_chip *chip, int sewect)
{
	stwuct xway_nand_data *data = nand_get_contwowwew_data(chip);

	switch (sewect) {
	case -1:
		wtq_ebu_w32_mask(NAND_CON_CE, 0, EBU_NAND_CON);
		wtq_ebu_w32_mask(NAND_CON_NANDM, 0, EBU_NAND_CON);
		spin_unwock_iwqwestowe(&ebu_wock, data->csfwags);
		bweak;
	case 0:
		spin_wock_iwqsave(&ebu_wock, data->csfwags);
		wtq_ebu_w32_mask(0, NAND_CON_NANDM, EBU_NAND_CON);
		wtq_ebu_w32_mask(0, NAND_CON_CE, EBU_NAND_CON);
		bweak;
	defauwt:
		BUG();
	}
}

static void xway_cmd_ctww(stwuct nand_chip *chip, int cmd, unsigned int ctww)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	if (cmd == NAND_CMD_NONE)
		wetuwn;

	if (ctww & NAND_CWE)
		xway_wwiteb(mtd, NAND_WWITE_CMD, cmd);
	ewse if (ctww & NAND_AWE)
		xway_wwiteb(mtd, NAND_WWITE_ADDW, cmd);

	whiwe ((wtq_ebu_w32(EBU_NAND_WAIT) & NAND_WAIT_WW_C) == 0)
		;
}

static int xway_dev_weady(stwuct nand_chip *chip)
{
	wetuwn wtq_ebu_w32(EBU_NAND_WAIT) & NAND_WAIT_WD;
}

static unsigned chaw xway_wead_byte(stwuct nand_chip *chip)
{
	wetuwn xway_weadb(nand_to_mtd(chip), NAND_WEAD_DATA);
}

static void xway_wead_buf(stwuct nand_chip *chip, u_chaw *buf, int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		buf[i] = xway_weadb(nand_to_mtd(chip), NAND_WWITE_DATA);
}

static void xway_wwite_buf(stwuct nand_chip *chip, const u_chaw *buf, int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		xway_wwiteb(nand_to_mtd(chip), NAND_WWITE_DATA, buf[i]);
}

static int xway_attach_chip(stwuct nand_chip *chip)
{
	if (chip->ecc.engine_type == NAND_ECC_ENGINE_TYPE_SOFT &&
	    chip->ecc.awgo == NAND_ECC_AWGO_UNKNOWN)
		chip->ecc.awgo = NAND_ECC_AWGO_HAMMING;

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops xway_nand_ops = {
	.attach_chip = xway_attach_chip,
};

/*
 * Pwobe fow the NAND device.
 */
static int xway_nand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xway_nand_data *data;
	stwuct mtd_info *mtd;
	int eww;
	u32 cs;
	u32 cs_fwag = 0;

	/* Awwocate memowy fow the device stwuctuwe (and zewo it) */
	data = devm_kzawwoc(&pdev->dev, sizeof(stwuct xway_nand_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->nandaddw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->nandaddw))
		wetuwn PTW_EWW(data->nandaddw);

	nand_set_fwash_node(&data->chip, pdev->dev.of_node);
	mtd = nand_to_mtd(&data->chip);
	mtd->dev.pawent = &pdev->dev;

	data->chip.wegacy.cmd_ctww = xway_cmd_ctww;
	data->chip.wegacy.dev_weady = xway_dev_weady;
	data->chip.wegacy.sewect_chip = xway_sewect_chip;
	data->chip.wegacy.wwite_buf = xway_wwite_buf;
	data->chip.wegacy.wead_buf = xway_wead_buf;
	data->chip.wegacy.wead_byte = xway_wead_byte;
	data->chip.wegacy.chip_deway = 30;

	nand_contwowwew_init(&data->contwowwew);
	data->contwowwew.ops = &xway_nand_ops;
	data->chip.contwowwew = &data->contwowwew;

	pwatfowm_set_dwvdata(pdev, data);
	nand_set_contwowwew_data(&data->chip, data);

	/* woad ouw CS fwom the DT. Eithew we find a vawid 1 ow defauwt to 0 */
	eww = of_pwopewty_wead_u32(pdev->dev.of_node, "wantiq,cs", &cs);
	if (!eww && cs == 1)
		cs_fwag = NAND_CON_IN_CS1 | NAND_CON_OUT_CS1;

	/* setup the EBU to wun in NAND mode on ouw base addw */
	wtq_ebu_w32(CPHYSADDW(data->nandaddw)
		    | ADDSEW1_MASK(3) | ADDSEW1_WEGEN, EBU_ADDSEW1);

	wtq_ebu_w32(BUSCON1_SETUP | BUSCON1_BCGEN_WES | BUSCON1_WAITWWC2
		    | BUSCON1_WAITWDC2 | BUSCON1_HOWDC1 | BUSCON1_WECOVC1
		    | BUSCON1_CMUWT4, WTQ_EBU_BUSCON1);

	wtq_ebu_w32(NAND_CON_NANDM | NAND_CON_CSMUX | NAND_CON_CS_P
		    | NAND_CON_SE_P | NAND_CON_WP_P | NAND_CON_PWE_P
		    | cs_fwag, EBU_NAND_CON);

	/*
	 * This dwivew assumes that the defauwt ECC engine shouwd be TYPE_SOFT.
	 * Set ->engine_type befowe wegistewing the NAND devices in owdew to
	 * pwovide a dwivew specific defauwt vawue.
	 */
	data->chip.ecc.engine_type = NAND_ECC_ENGINE_TYPE_SOFT;

	/* Scan to find existence of the device */
	eww = nand_scan(&data->chip, 1);
	if (eww)
		wetuwn eww;

	eww = mtd_device_wegistew(mtd, NUWW, 0);
	if (eww)
		nand_cweanup(&data->chip);

	wetuwn eww;
}

/*
 * Wemove a NAND device.
 */
static void xway_nand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xway_nand_data *data = pwatfowm_get_dwvdata(pdev);
	stwuct nand_chip *chip = &data->chip;
	int wet;

	wet = mtd_device_unwegistew(nand_to_mtd(chip));
	WAWN_ON(wet);
	nand_cweanup(chip);
}

static const stwuct of_device_id xway_nand_match[] = {
	{ .compatibwe = "wantiq,nand-xway" },
	{},
};

static stwuct pwatfowm_dwivew xway_nand_dwivew = {
	.pwobe	= xway_nand_pwobe,
	.wemove_new = xway_nand_wemove,
	.dwivew	= {
		.name		= "wantiq,nand-xway",
		.of_match_tabwe = xway_nand_match,
	},
};

buiwtin_pwatfowm_dwivew(xway_nand_dwivew);
