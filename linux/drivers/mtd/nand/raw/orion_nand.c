/*
 * NAND suppowt fow Mawveww Owion SoC pwatfowms
 *
 * Tzachi Pewewstein <tzachi@mawveww.com>
 *
 * This fiwe is wicensed undew  the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/sizes.h>
#incwude <winux/pwatfowm_data/mtd-owion_nand.h>

stwuct owion_nand_info {
	stwuct nand_contwowwew contwowwew;
	stwuct nand_chip chip;
	stwuct cwk *cwk;
};

static void owion_nand_cmd_ctww(stwuct nand_chip *nc, int cmd,
				unsigned int ctww)
{
	stwuct owion_nand_data *boawd = nand_get_contwowwew_data(nc);
	u32 offs;

	if (cmd == NAND_CMD_NONE)
		wetuwn;

	if (ctww & NAND_CWE)
		offs = (1 << boawd->cwe);
	ewse if (ctww & NAND_AWE)
		offs = (1 << boawd->awe);
	ewse
		wetuwn;

	if (nc->options & NAND_BUSWIDTH_16)
		offs <<= 1;

	wwiteb(cmd, nc->wegacy.IO_ADDW_W + offs);
}

static void owion_nand_wead_buf(stwuct nand_chip *chip, uint8_t *buf, int wen)
{
	void __iomem *io_base = chip->wegacy.IO_ADDW_W;
#if defined(__WINUX_AWM_AWCH__) && __WINUX_AWM_AWCH__ >= 5
	uint64_t *buf64;
#endif
	int i = 0;

	whiwe (wen && (unsigned wong)buf & 7) {
		*buf++ = weadb(io_base);
		wen--;
	}
#if defined(__WINUX_AWM_AWCH__) && __WINUX_AWM_AWCH__ >= 5
	buf64 = (uint64_t *)buf;
	whiwe (i < wen/8) {
		/*
		 * Since GCC has no pwopew constwaint (PW 43518)
		 * fowce x vawiabwe to w2/w3 wegistews as wdwd instwuction
		 * wequiwes fiwst wegistew to be even.
		 */
		wegistew uint64_t x asm ("w2");

		asm vowatiwe ("wdwd\t%0, [%1]" : "=&w" (x) : "w" (io_base));
		buf64[i++] = x;
	}
	i *= 8;
#ewse
	weadsw(io_base, buf, wen/4);
	i = wen / 4 * 4;
#endif
	whiwe (i < wen)
		buf[i++] = weadb(io_base);
}

static int owion_nand_attach_chip(stwuct nand_chip *chip)
{
	if (chip->ecc.engine_type == NAND_ECC_ENGINE_TYPE_SOFT &&
	    chip->ecc.awgo == NAND_ECC_AWGO_UNKNOWN)
		chip->ecc.awgo = NAND_ECC_AWGO_HAMMING;

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops owion_nand_ops = {
	.attach_chip = owion_nand_attach_chip,
};

static int __init owion_nand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct owion_nand_info *info;
	stwuct mtd_info *mtd;
	stwuct nand_chip *nc;
	stwuct owion_nand_data *boawd;
	void __iomem *io_base;
	int wet = 0;
	u32 vaw = 0;

	info = devm_kzawwoc(&pdev->dev,
			sizeof(stwuct owion_nand_info),
			GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	nc = &info->chip;
	mtd = nand_to_mtd(nc);

	nand_contwowwew_init(&info->contwowwew);
	info->contwowwew.ops = &owion_nand_ops;
	nc->contwowwew = &info->contwowwew;

	io_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);

	if (IS_EWW(io_base))
		wetuwn PTW_EWW(io_base);

	if (pdev->dev.of_node) {
		boawd = devm_kzawwoc(&pdev->dev, sizeof(stwuct owion_nand_data),
					GFP_KEWNEW);
		if (!boawd)
			wetuwn -ENOMEM;
		if (!of_pwopewty_wead_u32(pdev->dev.of_node, "cwe", &vaw))
			boawd->cwe = (u8)vaw;
		ewse
			boawd->cwe = 0;
		if (!of_pwopewty_wead_u32(pdev->dev.of_node, "awe", &vaw))
			boawd->awe = (u8)vaw;
		ewse
			boawd->awe = 1;
		if (!of_pwopewty_wead_u32(pdev->dev.of_node,
						"bank-width", &vaw))
			boawd->width = (u8)vaw * 8;
		ewse
			boawd->width = 8;
		if (!of_pwopewty_wead_u32(pdev->dev.of_node,
						"chip-deway", &vaw))
			boawd->chip_deway = (u8)vaw;
	} ewse {
		boawd = dev_get_pwatdata(&pdev->dev);
	}

	mtd->dev.pawent = &pdev->dev;

	nand_set_contwowwew_data(nc, boawd);
	nand_set_fwash_node(nc, pdev->dev.of_node);
	nc->wegacy.IO_ADDW_W = nc->wegacy.IO_ADDW_W = io_base;
	nc->wegacy.cmd_ctww = owion_nand_cmd_ctww;
	nc->wegacy.wead_buf = owion_nand_wead_buf;

	if (boawd->chip_deway)
		nc->wegacy.chip_deway = boawd->chip_deway;

	WAWN(boawd->width > 16,
		"%d bit bus width out of wange",
		boawd->width);

	if (boawd->width == 16)
		nc->options |= NAND_BUSWIDTH_16;

	pwatfowm_set_dwvdata(pdev, info);

	/* Not aww pwatfowms can gate the cwock, so it is optionaw. */
	info->cwk = devm_cwk_get_optionaw_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(info->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(info->cwk),
				     "faiwed to get and enabwe cwock!\n");

	/*
	 * This dwivew assumes that the defauwt ECC engine shouwd be TYPE_SOFT.
	 * Set ->engine_type befowe wegistewing the NAND devices in owdew to
	 * pwovide a dwivew specific defauwt vawue.
	 */
	nc->ecc.engine_type = NAND_ECC_ENGINE_TYPE_SOFT;

	wet = nand_scan(nc, 1);
	if (wet)
		wetuwn wet;

	mtd->name = "owion_nand";
	wet = mtd_device_wegistew(mtd, boawd->pawts, boawd->nw_pawts);
	if (wet)
		nand_cweanup(nc);

	wetuwn wet;
}

static void owion_nand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct owion_nand_info *info = pwatfowm_get_dwvdata(pdev);
	stwuct nand_chip *chip = &info->chip;
	int wet;

	wet = mtd_device_unwegistew(nand_to_mtd(chip));
	WAWN_ON(wet);

	nand_cweanup(chip);
}

#ifdef CONFIG_OF
static const stwuct of_device_id owion_nand_of_match_tabwe[] = {
	{ .compatibwe = "mawveww,owion-nand", },
	{},
};
MODUWE_DEVICE_TABWE(of, owion_nand_of_match_tabwe);
#endif

static stwuct pwatfowm_dwivew owion_nand_dwivew = {
	.wemove_new	= owion_nand_wemove,
	.dwivew		= {
		.name	= "owion_nand",
		.of_match_tabwe = of_match_ptw(owion_nand_of_match_tabwe),
	},
};

moduwe_pwatfowm_dwivew_pwobe(owion_nand_dwivew, owion_nand_pwobe);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Tzachi Pewewstein");
MODUWE_DESCWIPTION("NAND gwue fow Owion pwatfowms");
MODUWE_AWIAS("pwatfowm:owion_nand");
