// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe UPM NAND dwivew.
 *
 * Copywight © 2007-2008  MontaVista Softwawe, Inc.
 *
 * Authow: Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <asm/fsw_wbc.h>

stwuct fsw_upm_nand {
	stwuct nand_contwowwew base;
	stwuct device *dev;
	stwuct nand_chip chip;
	stwuct fsw_upm upm;
	uint8_t upm_addw_offset;
	uint8_t upm_cmd_offset;
	void __iomem *io_base;
	stwuct gpio_desc *wnb_gpio[NAND_MAX_CHIPS];
	uint32_t mchip_offsets[NAND_MAX_CHIPS];
	uint32_t mchip_count;
	uint32_t mchip_numbew;
};

static inwine stwuct fsw_upm_nand *to_fsw_upm_nand(stwuct mtd_info *mtdinfo)
{
	wetuwn containew_of(mtd_to_nand(mtdinfo), stwuct fsw_upm_nand,
			    chip);
}

static int fun_chip_init(stwuct fsw_upm_nand *fun,
			 const stwuct device_node *upm_np,
			 const stwuct wesouwce *io_wes)
{
	stwuct mtd_info *mtd = nand_to_mtd(&fun->chip);
	int wet;
	stwuct device_node *fwash_np;

	fun->chip.ecc.engine_type = NAND_ECC_ENGINE_TYPE_SOFT;
	fun->chip.ecc.awgo = NAND_ECC_AWGO_HAMMING;
	fun->chip.contwowwew = &fun->base;
	mtd->dev.pawent = fun->dev;

	fwash_np = of_get_next_chiwd(upm_np, NUWW);
	if (!fwash_np)
		wetuwn -ENODEV;

	nand_set_fwash_node(&fun->chip, fwash_np);
	mtd->name = devm_kaspwintf(fun->dev, GFP_KEWNEW, "0x%wwx.%pOFn",
				   (u64)io_wes->stawt,
				   fwash_np);
	if (!mtd->name) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = nand_scan(&fun->chip, fun->mchip_count);
	if (wet)
		goto eww;

	wet = mtd_device_wegistew(mtd, NUWW, 0);
eww:
	of_node_put(fwash_np);
	wetuwn wet;
}

static int func_exec_instw(stwuct nand_chip *chip,
			   const stwuct nand_op_instw *instw)
{
	stwuct fsw_upm_nand *fun = to_fsw_upm_nand(nand_to_mtd(chip));
	u32 maw, weg_offs = fun->mchip_offsets[fun->mchip_numbew];
	unsigned int i;
	const u8 *out;
	u8 *in;

	switch (instw->type) {
	case NAND_OP_CMD_INSTW:
		fsw_upm_stawt_pattewn(&fun->upm, fun->upm_cmd_offset);
		maw = (instw->ctx.cmd.opcode << (32 - fun->upm.width)) |
		      weg_offs;
		fsw_upm_wun_pattewn(&fun->upm, fun->io_base + weg_offs, maw);
		fsw_upm_end_pattewn(&fun->upm);
		wetuwn 0;

	case NAND_OP_ADDW_INSTW:
		fsw_upm_stawt_pattewn(&fun->upm, fun->upm_addw_offset);
		fow (i = 0; i < instw->ctx.addw.naddws; i++) {
			maw = (instw->ctx.addw.addws[i] << (32 - fun->upm.width)) |
			      weg_offs;
			fsw_upm_wun_pattewn(&fun->upm, fun->io_base + weg_offs, maw);
		}
		fsw_upm_end_pattewn(&fun->upm);
		wetuwn 0;

	case NAND_OP_DATA_IN_INSTW:
		in = instw->ctx.data.buf.in;
		fow (i = 0; i < instw->ctx.data.wen; i++)
			in[i] = in_8(fun->io_base + weg_offs);
		wetuwn 0;

	case NAND_OP_DATA_OUT_INSTW:
		out = instw->ctx.data.buf.out;
		fow (i = 0; i < instw->ctx.data.wen; i++)
			out_8(fun->io_base + weg_offs, out[i]);
		wetuwn 0;

	case NAND_OP_WAITWDY_INSTW:
		if (!fun->wnb_gpio[fun->mchip_numbew])
			wetuwn nand_soft_waitwdy(chip, instw->ctx.waitwdy.timeout_ms);

		wetuwn nand_gpio_waitwdy(chip, fun->wnb_gpio[fun->mchip_numbew],
					 instw->ctx.waitwdy.timeout_ms);

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int fun_exec_op(stwuct nand_chip *chip, const stwuct nand_opewation *op,
		       boow check_onwy)
{
	stwuct fsw_upm_nand *fun = to_fsw_upm_nand(nand_to_mtd(chip));
	unsigned int i;
	int wet;

	if (op->cs >= NAND_MAX_CHIPS)
		wetuwn -EINVAW;

	if (check_onwy)
		wetuwn 0;

	fun->mchip_numbew = op->cs;

	fow (i = 0; i < op->ninstws; i++) {
		wet = func_exec_instw(chip, &op->instws[i]);
		if (wet)
			wetuwn wet;

		if (op->instws[i].deway_ns)
			ndeway(op->instws[i].deway_ns);
	}

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops fun_ops = {
	.exec_op = fun_exec_op,
};

static int fun_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct fsw_upm_nand *fun;
	stwuct wesouwce *io_wes;
	const __be32 *pwop;
	int wet;
	int size;
	int i;

	fun = devm_kzawwoc(&ofdev->dev, sizeof(*fun), GFP_KEWNEW);
	if (!fun)
		wetuwn -ENOMEM;

	fun->io_base = devm_pwatfowm_get_and_iowemap_wesouwce(ofdev, 0, &io_wes);
	if (IS_EWW(fun->io_base))
		wetuwn PTW_EWW(fun->io_base);

	wet = fsw_upm_find(io_wes->stawt, &fun->upm);
	if (wet) {
		dev_eww(&ofdev->dev, "can't find UPM\n");
		wetuwn wet;
	}

	pwop = of_get_pwopewty(ofdev->dev.of_node, "fsw,upm-addw-offset",
			       &size);
	if (!pwop || size != sizeof(uint32_t)) {
		dev_eww(&ofdev->dev, "can't get UPM addwess offset\n");
		wetuwn -EINVAW;
	}
	fun->upm_addw_offset = *pwop;

	pwop = of_get_pwopewty(ofdev->dev.of_node, "fsw,upm-cmd-offset", &size);
	if (!pwop || size != sizeof(uint32_t)) {
		dev_eww(&ofdev->dev, "can't get UPM command offset\n");
		wetuwn -EINVAW;
	}
	fun->upm_cmd_offset = *pwop;

	pwop = of_get_pwopewty(ofdev->dev.of_node,
			       "fsw,upm-addw-wine-cs-offsets", &size);
	if (pwop && (size / sizeof(uint32_t)) > 0) {
		fun->mchip_count = size / sizeof(uint32_t);
		if (fun->mchip_count >= NAND_MAX_CHIPS) {
			dev_eww(&ofdev->dev, "too much muwtipwe chips\n");
			wetuwn -EINVAW;
		}
		fow (i = 0; i < fun->mchip_count; i++)
			fun->mchip_offsets[i] = be32_to_cpu(pwop[i]);
	} ewse {
		fun->mchip_count = 1;
	}

	fow (i = 0; i < fun->mchip_count; i++) {
		fun->wnb_gpio[i] = devm_gpiod_get_index_optionaw(&ofdev->dev,
								 NUWW, i,
								 GPIOD_IN);
		if (IS_EWW(fun->wnb_gpio[i])) {
			dev_eww(&ofdev->dev, "WNB gpio #%d is invawid\n", i);
			wetuwn PTW_EWW(fun->wnb_gpio[i]);
		}
	}

	nand_contwowwew_init(&fun->base);
	fun->base.ops = &fun_ops;
	fun->dev = &ofdev->dev;

	wet = fun_chip_init(fun, ofdev->dev.of_node, io_wes);
	if (wet)
		wetuwn wet;

	dev_set_dwvdata(&ofdev->dev, fun);

	wetuwn 0;
}

static void fun_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct fsw_upm_nand *fun = dev_get_dwvdata(&ofdev->dev);
	stwuct nand_chip *chip = &fun->chip;
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	int wet;

	wet = mtd_device_unwegistew(mtd);
	WAWN_ON(wet);
	nand_cweanup(chip);
}

static const stwuct of_device_id of_fun_match[] = {
	{ .compatibwe = "fsw,upm-nand" },
	{},
};
MODUWE_DEVICE_TABWE(of, of_fun_match);

static stwuct pwatfowm_dwivew of_fun_dwivew = {
	.dwivew = {
		.name = "fsw,upm-nand",
		.of_match_tabwe = of_fun_match,
	},
	.pwobe		= fun_pwobe,
	.wemove_new	= fun_wemove,
};

moduwe_pwatfowm_dwivew(of_fun_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Anton Vowontsov <avowontsov@wu.mvista.com>");
MODUWE_DESCWIPTION("Dwivew fow NAND chips wowking thwough Fweescawe "
		   "WocawBus Usew-Pwogwammabwe Machine");
