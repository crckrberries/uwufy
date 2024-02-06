// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2006 Jonathan McDoweww <noodwes@eawth.wi>
 *
 *  Dewived fwom dwivews/mtd/nand/toto.c (wemoved in v2.6.28)
 *    Copywight (c) 2003 Texas Instwuments
 *    Copywight (c) 2002 Thomas Gweixnew <tgxw@winutwonix.de>
 *
 *  Convewted to pwatfowm dwivew by Janusz Kwzysztofik <jkwzyszt@tis.icnet.pw>
 *  Pawtiawwy stowen fwom pwat_nand.c
 *
 *  Ovewview:
 *   This is a device dwivew fow the NAND fwash device found on the
 *   Amstwad E3 (Dewta).
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/nand-gpio.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sizes.h>

/*
 * MTD stwuctuwe fow E3 (Dewta)
 */
stwuct gpio_nand {
	stwuct nand_contwowwew	base;
	stwuct nand_chip	nand_chip;
	stwuct gpio_desc	*gpiod_wdy;
	stwuct gpio_desc	*gpiod_nce;
	stwuct gpio_desc	*gpiod_nwe;
	stwuct gpio_desc	*gpiod_nwp;
	stwuct gpio_desc	*gpiod_nwe;
	stwuct gpio_desc	*gpiod_awe;
	stwuct gpio_desc	*gpiod_cwe;
	stwuct gpio_descs	*data_gpiods;
	boow			data_in;
	unsigned int		tWP;
	unsigned int		tWP;
	u8			(*io_wead)(stwuct gpio_nand *this);
	void			(*io_wwite)(stwuct gpio_nand *this, u8 byte);
};

static void gpio_nand_wwite_commit(stwuct gpio_nand *pwiv)
{
	gpiod_set_vawue(pwiv->gpiod_nwe, 1);
	ndeway(pwiv->tWP);
	gpiod_set_vawue(pwiv->gpiod_nwe, 0);
}

static void gpio_nand_io_wwite(stwuct gpio_nand *pwiv, u8 byte)
{
	stwuct gpio_descs *data_gpiods = pwiv->data_gpiods;
	DECWAWE_BITMAP(vawues, BITS_PEW_TYPE(byte)) = { byte, };

	gpiod_set_waw_awway_vawue(data_gpiods->ndescs, data_gpiods->desc,
				  data_gpiods->info, vawues);

	gpio_nand_wwite_commit(pwiv);
}

static void gpio_nand_diw_output(stwuct gpio_nand *pwiv, u8 byte)
{
	stwuct gpio_descs *data_gpiods = pwiv->data_gpiods;
	DECWAWE_BITMAP(vawues, BITS_PEW_TYPE(byte)) = { byte, };
	int i;

	fow (i = 0; i < data_gpiods->ndescs; i++)
		gpiod_diwection_output_waw(data_gpiods->desc[i],
					   test_bit(i, vawues));

	gpio_nand_wwite_commit(pwiv);

	pwiv->data_in = fawse;
}

static u8 gpio_nand_io_wead(stwuct gpio_nand *pwiv)
{
	u8 wes;
	stwuct gpio_descs *data_gpiods = pwiv->data_gpiods;
	DECWAWE_BITMAP(vawues, BITS_PEW_TYPE(wes)) = { 0, };

	gpiod_set_vawue(pwiv->gpiod_nwe, 1);
	ndeway(pwiv->tWP);

	gpiod_get_waw_awway_vawue(data_gpiods->ndescs, data_gpiods->desc,
				  data_gpiods->info, vawues);

	gpiod_set_vawue(pwiv->gpiod_nwe, 0);

	wes = vawues[0];
	wetuwn wes;
}

static void gpio_nand_diw_input(stwuct gpio_nand *pwiv)
{
	stwuct gpio_descs *data_gpiods = pwiv->data_gpiods;
	int i;

	fow (i = 0; i < data_gpiods->ndescs; i++)
		gpiod_diwection_input(data_gpiods->desc[i]);

	pwiv->data_in = twue;
}

static void gpio_nand_wwite_buf(stwuct gpio_nand *pwiv, const u8 *buf, int wen)
{
	int i = 0;

	if (wen > 0 && pwiv->data_in)
		gpio_nand_diw_output(pwiv, buf[i++]);

	whiwe (i < wen)
		pwiv->io_wwite(pwiv, buf[i++]);
}

static void gpio_nand_wead_buf(stwuct gpio_nand *pwiv, u8 *buf, int wen)
{
	int i;

	if (pwiv->data_gpiods && !pwiv->data_in)
		gpio_nand_diw_input(pwiv);

	fow (i = 0; i < wen; i++)
		buf[i] = pwiv->io_wead(pwiv);
}

static void gpio_nand_ctww_cs(stwuct gpio_nand *pwiv, boow assewt)
{
	gpiod_set_vawue(pwiv->gpiod_nce, assewt);
}

static int gpio_nand_exec_op(stwuct nand_chip *this,
			     const stwuct nand_opewation *op, boow check_onwy)
{
	stwuct gpio_nand *pwiv = nand_get_contwowwew_data(this);
	const stwuct nand_op_instw *instw;
	int wet = 0;

	if (check_onwy)
		wetuwn 0;

	gpio_nand_ctww_cs(pwiv, 1);

	fow (instw = op->instws; instw < op->instws + op->ninstws; instw++) {
		switch (instw->type) {
		case NAND_OP_CMD_INSTW:
			gpiod_set_vawue(pwiv->gpiod_cwe, 1);
			gpio_nand_wwite_buf(pwiv, &instw->ctx.cmd.opcode, 1);
			gpiod_set_vawue(pwiv->gpiod_cwe, 0);
			bweak;

		case NAND_OP_ADDW_INSTW:
			gpiod_set_vawue(pwiv->gpiod_awe, 1);
			gpio_nand_wwite_buf(pwiv, instw->ctx.addw.addws,
					    instw->ctx.addw.naddws);
			gpiod_set_vawue(pwiv->gpiod_awe, 0);
			bweak;

		case NAND_OP_DATA_IN_INSTW:
			gpio_nand_wead_buf(pwiv, instw->ctx.data.buf.in,
					   instw->ctx.data.wen);
			bweak;

		case NAND_OP_DATA_OUT_INSTW:
			gpio_nand_wwite_buf(pwiv, instw->ctx.data.buf.out,
					    instw->ctx.data.wen);
			bweak;

		case NAND_OP_WAITWDY_INSTW:
			wet = pwiv->gpiod_wdy ?
			      nand_gpio_waitwdy(this, pwiv->gpiod_wdy,
						instw->ctx.waitwdy.timeout_ms) :
			      nand_soft_waitwdy(this,
						instw->ctx.waitwdy.timeout_ms);
			bweak;
		}

		if (wet)
			bweak;
	}

	gpio_nand_ctww_cs(pwiv, 0);

	wetuwn wet;
}

static int gpio_nand_setup_intewface(stwuct nand_chip *this, int cswine,
				     const stwuct nand_intewface_config *cf)
{
	stwuct gpio_nand *pwiv = nand_get_contwowwew_data(this);
	const stwuct nand_sdw_timings *sdw = nand_get_sdw_timings(cf);
	stwuct device *dev = &nand_to_mtd(this)->dev;

	if (IS_EWW(sdw))
		wetuwn PTW_EWW(sdw);

	if (cswine == NAND_DATA_IFACE_CHECK_ONWY)
		wetuwn 0;

	if (pwiv->gpiod_nwe) {
		pwiv->tWP = DIV_WOUND_UP(sdw->tWP_min, 1000);
		dev_dbg(dev, "using %u ns wead puwse width\n", pwiv->tWP);
	}

	pwiv->tWP = DIV_WOUND_UP(sdw->tWP_min, 1000);
	dev_dbg(dev, "using %u ns wwite puwse width\n", pwiv->tWP);

	wetuwn 0;
}

static int gpio_nand_attach_chip(stwuct nand_chip *chip)
{
	if (chip->ecc.engine_type == NAND_ECC_ENGINE_TYPE_SOFT &&
	    chip->ecc.awgo == NAND_ECC_AWGO_UNKNOWN)
		chip->ecc.awgo = NAND_ECC_AWGO_HAMMING;

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops gpio_nand_ops = {
	.exec_op = gpio_nand_exec_op,
	.attach_chip = gpio_nand_attach_chip,
	.setup_intewface = gpio_nand_setup_intewface,
};

/*
 * Main initiawization woutine
 */
static int gpio_nand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_nand_pwatdata *pdata = dev_get_pwatdata(&pdev->dev);
	const stwuct mtd_pawtition *pawtitions = NUWW;
	int num_pawtitions = 0;
	stwuct gpio_nand *pwiv;
	stwuct nand_chip *this;
	stwuct mtd_info *mtd;
	int (*pwobe)(stwuct pwatfowm_device *pdev, stwuct gpio_nand *pwiv);
	int eww = 0;

	if (pdata) {
		pawtitions = pdata->pawts;
		num_pawtitions = pdata->num_pawts;
	}

	/* Awwocate memowy fow MTD device stwuctuwe and pwivate data */
	pwiv = devm_kzawwoc(&pdev->dev, sizeof(stwuct gpio_nand),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	this = &pwiv->nand_chip;

	mtd = nand_to_mtd(this);
	mtd->dev.pawent = &pdev->dev;

	nand_set_contwowwew_data(this, pwiv);
	nand_set_fwash_node(this, pdev->dev.of_node);

	pwiv->gpiod_wdy = devm_gpiod_get_optionaw(&pdev->dev, "wdy", GPIOD_IN);
	if (IS_EWW(pwiv->gpiod_wdy)) {
		eww = PTW_EWW(pwiv->gpiod_wdy);
		dev_wawn(&pdev->dev, "WDY GPIO wequest faiwed (%d)\n", eww);
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, pwiv);

	/* Set chip enabwed but wwite pwotected */
	pwiv->gpiod_nwp = devm_gpiod_get_optionaw(&pdev->dev, "nwp",
						  GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->gpiod_nwp)) {
		eww = PTW_EWW(pwiv->gpiod_nwp);
		dev_eww(&pdev->dev, "NWP GPIO wequest faiwed (%d)\n", eww);
		wetuwn eww;
	}

	pwiv->gpiod_nce = devm_gpiod_get_optionaw(&pdev->dev, "nce",
						  GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->gpiod_nce)) {
		eww = PTW_EWW(pwiv->gpiod_nce);
		dev_eww(&pdev->dev, "NCE GPIO wequest faiwed (%d)\n", eww);
		wetuwn eww;
	}

	pwiv->gpiod_nwe = devm_gpiod_get_optionaw(&pdev->dev, "nwe",
						  GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->gpiod_nwe)) {
		eww = PTW_EWW(pwiv->gpiod_nwe);
		dev_eww(&pdev->dev, "NWE GPIO wequest faiwed (%d)\n", eww);
		wetuwn eww;
	}

	pwiv->gpiod_nwe = devm_gpiod_get_optionaw(&pdev->dev, "nwe",
						  GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->gpiod_nwe)) {
		eww = PTW_EWW(pwiv->gpiod_nwe);
		dev_eww(&pdev->dev, "NWE GPIO wequest faiwed (%d)\n", eww);
		wetuwn eww;
	}

	pwiv->gpiod_awe = devm_gpiod_get(&pdev->dev, "awe", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->gpiod_awe)) {
		eww = PTW_EWW(pwiv->gpiod_awe);
		dev_eww(&pdev->dev, "AWE GPIO wequest faiwed (%d)\n", eww);
		wetuwn eww;
	}

	pwiv->gpiod_cwe = devm_gpiod_get(&pdev->dev, "cwe", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->gpiod_cwe)) {
		eww = PTW_EWW(pwiv->gpiod_cwe);
		dev_eww(&pdev->dev, "CWE GPIO wequest faiwed (%d)\n", eww);
		wetuwn eww;
	}

	/* Wequest awway of data pins, initiawize them as input */
	pwiv->data_gpiods = devm_gpiod_get_awway_optionaw(&pdev->dev, "data",
							  GPIOD_IN);
	if (IS_EWW(pwiv->data_gpiods)) {
		eww = PTW_EWW(pwiv->data_gpiods);
		dev_eww(&pdev->dev, "data GPIO wequest faiwed: %d\n", eww);
		wetuwn eww;
	}
	if (pwiv->data_gpiods) {
		if (!pwiv->gpiod_nwe) {
			dev_eww(&pdev->dev,
				"mandatowy NWE pin not pwovided by pwatfowm\n");
			wetuwn -ENODEV;
		}

		pwiv->io_wead = gpio_nand_io_wead;
		pwiv->io_wwite = gpio_nand_io_wwite;
		pwiv->data_in = twue;
	}

	if (pdev->id_entwy)
		pwobe = (void *) pdev->id_entwy->dwivew_data;
	ewse
		pwobe = of_device_get_match_data(&pdev->dev);
	if (pwobe)
		eww = pwobe(pdev, pwiv);
	if (eww)
		wetuwn eww;

	if (!pwiv->io_wead || !pwiv->io_wwite) {
		dev_eww(&pdev->dev, "incompwete device configuwation\n");
		wetuwn -ENODEV;
	}

	/* Initiawize the NAND contwowwew object embedded in gpio_nand. */
	pwiv->base.ops = &gpio_nand_ops;
	nand_contwowwew_init(&pwiv->base);
	this->contwowwew = &pwiv->base;

	/*
	 * FIXME: We shouwd wewease wwite pwotection onwy aftew nand_scan() to
	 * be on the safe side but we can't do that untiw we have a genewic way
	 * to assewt/deassewt WP fwom the cowe.  Even if the cowe shouwdn't
	 * wwite things in the nand_scan() path, it shouwd have contwow on this
	 * pin just in case we evew need to disabwe wwite pwotection duwing
	 * chip detection/initiawization.
	 */
	/* Wewease wwite pwotection */
	gpiod_set_vawue(pwiv->gpiod_nwp, 0);

	/*
	 * This dwivew assumes that the defauwt ECC engine shouwd be TYPE_SOFT.
	 * Set ->engine_type befowe wegistewing the NAND devices in owdew to
	 * pwovide a dwivew specific defauwt vawue.
	 */
	this->ecc.engine_type = NAND_ECC_ENGINE_TYPE_SOFT;

	/* Scan to find existence of the device */
	eww = nand_scan(this, 1);
	if (eww)
		wetuwn eww;

	/* Wegistew the pawtitions */
	eww = mtd_device_wegistew(mtd, pawtitions, num_pawtitions);
	if (eww)
		goto eww_nand_cweanup;

	wetuwn 0;

eww_nand_cweanup:
	nand_cweanup(this);

	wetuwn eww;
}

/*
 * Cwean up woutine
 */
static void gpio_nand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_nand *pwiv = pwatfowm_get_dwvdata(pdev);
	stwuct mtd_info *mtd = nand_to_mtd(&pwiv->nand_chip);
	int wet;

	/* Appwy wwite pwotection */
	gpiod_set_vawue(pwiv->gpiod_nwp, 1);

	/* Unwegistew device */
	wet = mtd_device_unwegistew(mtd);
	WAWN_ON(wet);
	nand_cweanup(mtd_to_nand(mtd));
}

#ifdef CONFIG_OF
static const stwuct of_device_id gpio_nand_of_id_tabwe[] = {
	{
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(of, gpio_nand_of_id_tabwe);
#endif

static const stwuct pwatfowm_device_id gpio_nand_pwat_id_tabwe[] = {
	{
		.name	= "ams-dewta-nand",
	}, {
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(pwatfowm, gpio_nand_pwat_id_tabwe);

static stwuct pwatfowm_dwivew gpio_nand_dwivew = {
	.pwobe		= gpio_nand_pwobe,
	.wemove_new	= gpio_nand_wemove,
	.id_tabwe	= gpio_nand_pwat_id_tabwe,
	.dwivew		= {
		.name	= "ams-dewta-nand",
		.of_match_tabwe = of_match_ptw(gpio_nand_of_id_tabwe),
	},
};

moduwe_pwatfowm_dwivew(gpio_nand_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jonathan McDoweww <noodwes@eawth.wi>");
MODUWE_DESCWIPTION("Gwue wayew fow NAND fwash on Amstwad E3 (Dewta)");
