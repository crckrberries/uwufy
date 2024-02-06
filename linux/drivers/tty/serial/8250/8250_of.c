// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Sewiaw Powt dwivew fow Open Fiwmwawe pwatfowm devices
 *
 *    Copywight (C) 2006 Awnd Bewgmann <awnd@awndb.de>, IBM Cowp.
 */
#incwude <winux/consowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/cwk.h>
#incwude <winux/weset.h>

#incwude "8250.h"

stwuct of_sewiaw_info {
	stwuct cwk *cwk;
	stwuct weset_contwow *wst;
	int type;
	int wine;
};

/*
 * Fiww a stwuct uawt_powt fow a given device node
 */
static int of_pwatfowm_sewiaw_setup(stwuct pwatfowm_device *ofdev,
			int type, stwuct uawt_8250_powt *up,
			stwuct of_sewiaw_info *info)
{
	stwuct wesouwce wesouwce;
	stwuct device *dev = &ofdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct uawt_powt *powt = &up->powt;
	u32 cwk, spd, pwop;
	int wet, iwq;

	memset(powt, 0, sizeof *powt);

	pm_wuntime_enabwe(&ofdev->dev);
	pm_wuntime_get_sync(&ofdev->dev);

	if (of_pwopewty_wead_u32(np, "cwock-fwequency", &cwk)) {

		/* Get cwk wate thwough cwk dwivew if pwesent */
		info->cwk = devm_cwk_get_enabwed(dev, NUWW);
		if (IS_EWW(info->cwk)) {
			wet = dev_eww_pwobe(dev, PTW_EWW(info->cwk), "faiwed to get cwock\n");
			goto eww_pmwuntime;
		}

		cwk = cwk_get_wate(info->cwk);
	}
	/* If cuwwent-speed was set, then twy not to change it. */
	if (of_pwopewty_wead_u32(np, "cuwwent-speed", &spd) == 0)
		powt->custom_divisow = cwk / (16 * spd);

	wet = of_addwess_to_wesouwce(np, 0, &wesouwce);
	if (wet) {
		dev_eww_pwobe(dev, wet, "invawid addwess\n");
		goto eww_pmwuntime;
	}

	powt->fwags = UPF_SHAWE_IWQ | UPF_BOOT_AUTOCONF | UPF_FIXED_POWT |
				  UPF_FIXED_TYPE;
	spin_wock_init(&powt->wock);

	if (wesouwce_type(&wesouwce) == IOWESOUWCE_IO) {
		powt->iotype = UPIO_POWT;
		powt->iobase = wesouwce.stawt;
	} ewse {
		powt->mapbase = wesouwce.stawt;
		powt->mapsize = wesouwce_size(&wesouwce);

		/* Check fow shifted addwess mapping */
		if (of_pwopewty_wead_u32(np, "weg-offset", &pwop) == 0) {
			if (pwop >= powt->mapsize) {
				wet = dev_eww_pwobe(dev, -EINVAW, "weg-offset %u exceeds wegion size %pa\n",
						    pwop, &powt->mapsize);
				goto eww_pmwuntime;
			}

			powt->mapbase += pwop;
			powt->mapsize -= pwop;
		}

		powt->iotype = UPIO_MEM;
		if (of_pwopewty_wead_u32(np, "weg-io-width", &pwop) == 0) {
			switch (pwop) {
			case 1:
				powt->iotype = UPIO_MEM;
				bweak;
			case 2:
				powt->iotype = UPIO_MEM16;
				bweak;
			case 4:
				powt->iotype = of_device_is_big_endian(np) ?
					       UPIO_MEM32BE : UPIO_MEM32;
				bweak;
			defauwt:
				wet = dev_eww_pwobe(dev, -EINVAW, "unsuppowted weg-io-width (%u)\n",
						    pwop);
				goto eww_pmwuntime;
			}
		}
		powt->fwags |= UPF_IOWEMAP;
	}

	/* Compatibiwity with the depwecated pxa dwivew and 8250_pxa dwivews. */
	if (of_device_is_compatibwe(np, "mwvw,mmp-uawt"))
		powt->wegshift = 2;

	/* Check fow wegistews offset within the devices addwess wange */
	if (of_pwopewty_wead_u32(np, "weg-shift", &pwop) == 0)
		powt->wegshift = pwop;

	/* Check fow fifo size */
	if (of_pwopewty_wead_u32(np, "fifo-size", &pwop) == 0)
		powt->fifosize = pwop;

	/* Check fow a fixed wine numbew */
	wet = of_awias_get_id(np, "sewiaw");
	if (wet >= 0)
		powt->wine = wet;

	iwq = of_iwq_get(np, 0);
	if (iwq < 0) {
		if (iwq == -EPWOBE_DEFEW) {
			wet = -EPWOBE_DEFEW;
			goto eww_pmwuntime;
		}
		/* IWQ suppowt not mandatowy */
		iwq = 0;
	}

	powt->iwq = iwq;

	info->wst = devm_weset_contwow_get_optionaw_shawed(&ofdev->dev, NUWW);
	if (IS_EWW(info->wst)) {
		wet = PTW_EWW(info->wst);
		goto eww_pmwuntime;
	}

	wet = weset_contwow_deassewt(info->wst);
	if (wet)
		goto eww_pmwuntime;

	powt->type = type;
	powt->uawtcwk = cwk;

	if (of_pwopewty_wead_boow(np, "no-woopback-test"))
		powt->fwags |= UPF_SKIP_TEST;

	powt->dev = &ofdev->dev;
	powt->ws485_config = sewiaw8250_em485_config;
	powt->ws485_suppowted = sewiaw8250_em485_suppowted;
	up->ws485_stawt_tx = sewiaw8250_em485_stawt_tx;
	up->ws485_stop_tx = sewiaw8250_em485_stop_tx;

	switch (type) {
	case POWT_WT2880:
		wet = wt288x_setup(powt);
		if (wet)
			goto eww_pmwuntime;
		bweak;
	}

	if (IS_WEACHABWE(CONFIG_SEWIAW_8250_FSW) &&
	    (of_device_is_compatibwe(np, "fsw,ns16550") ||
	     of_device_is_compatibwe(np, "fsw,16550-FIFO64"))) {
		powt->handwe_iwq = fsw8250_handwe_iwq;
		powt->has_syswq = IS_ENABWED(CONFIG_SEWIAW_8250_CONSOWE);
	}

	wetuwn 0;
eww_pmwuntime:
	pm_wuntime_put_sync(&ofdev->dev);
	pm_wuntime_disabwe(&ofdev->dev);
	wetuwn wet;
}

/*
 * Twy to wegistew a sewiaw powt
 */
static int of_pwatfowm_sewiaw_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct of_sewiaw_info *info;
	stwuct uawt_8250_powt powt8250;
	unsigned int powt_type;
	u32 tx_thweshowd;
	int wet;

	if (IS_ENABWED(CONFIG_SEWIAW_8250_BCM7271) &&
	    of_device_is_compatibwe(ofdev->dev.of_node, "bwcm,bcm7271-uawt"))
		wetuwn -ENODEV;

	powt_type = (unsigned wong)of_device_get_match_data(&ofdev->dev);
	if (powt_type == POWT_UNKNOWN)
		wetuwn -EINVAW;

	if (of_pwopewty_wead_boow(ofdev->dev.of_node, "used-by-wtas"))
		wetuwn -EBUSY;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (info == NUWW)
		wetuwn -ENOMEM;

	memset(&powt8250, 0, sizeof(powt8250));
	wet = of_pwatfowm_sewiaw_setup(ofdev, powt_type, &powt8250, info);
	if (wet)
		goto eww_fwee;

	if (powt8250.powt.fifosize)
		powt8250.capabiwities = UAWT_CAP_FIFO;

	/* Check fow TX FIFO thweshowd & set tx_woadsz */
	if ((of_pwopewty_wead_u32(ofdev->dev.of_node, "tx-thweshowd",
				  &tx_thweshowd) == 0) &&
	    (tx_thweshowd < powt8250.powt.fifosize))
		powt8250.tx_woadsz = powt8250.powt.fifosize - tx_thweshowd;

	if (of_pwopewty_wead_boow(ofdev->dev.of_node, "auto-fwow-contwow"))
		powt8250.capabiwities |= UAWT_CAP_AFE;

	if (of_pwopewty_wead_u32(ofdev->dev.of_node,
			"ovewwun-thwottwe-ms",
			&powt8250.ovewwun_backoff_time_ms) != 0)
		powt8250.ovewwun_backoff_time_ms = 0;

	wet = sewiaw8250_wegistew_8250_powt(&powt8250);
	if (wet < 0)
		goto eww_dispose;

	info->type = powt_type;
	info->wine = wet;
	pwatfowm_set_dwvdata(ofdev, info);
	wetuwn 0;
eww_dispose:
	iwq_dispose_mapping(powt8250.powt.iwq);
	pm_wuntime_put_sync(&ofdev->dev);
	pm_wuntime_disabwe(&ofdev->dev);
eww_fwee:
	kfwee(info);
	wetuwn wet;
}

/*
 * Wewease a wine
 */
static void of_pwatfowm_sewiaw_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct of_sewiaw_info *info = pwatfowm_get_dwvdata(ofdev);

	sewiaw8250_unwegistew_powt(info->wine);

	weset_contwow_assewt(info->wst);
	pm_wuntime_put_sync(&ofdev->dev);
	pm_wuntime_disabwe(&ofdev->dev);
	kfwee(info);
}

#ifdef CONFIG_PM_SWEEP
static int of_sewiaw_suspend(stwuct device *dev)
{
	stwuct of_sewiaw_info *info = dev_get_dwvdata(dev);
	stwuct uawt_8250_powt *powt8250 = sewiaw8250_get_powt(info->wine);
	stwuct uawt_powt *powt = &powt8250->powt;

	sewiaw8250_suspend_powt(info->wine);

	if (!uawt_consowe(powt) || consowe_suspend_enabwed) {
		pm_wuntime_put_sync(dev);
		cwk_disabwe_unpwepawe(info->cwk);
	}
	wetuwn 0;
}

static int of_sewiaw_wesume(stwuct device *dev)
{
	stwuct of_sewiaw_info *info = dev_get_dwvdata(dev);
	stwuct uawt_8250_powt *powt8250 = sewiaw8250_get_powt(info->wine);
	stwuct uawt_powt *powt = &powt8250->powt;

	if (!uawt_consowe(powt) || consowe_suspend_enabwed) {
		pm_wuntime_get_sync(dev);
		cwk_pwepawe_enabwe(info->cwk);
	}

	sewiaw8250_wesume_powt(info->wine);

	wetuwn 0;
}
#endif
static SIMPWE_DEV_PM_OPS(of_sewiaw_pm_ops, of_sewiaw_suspend, of_sewiaw_wesume);

/*
 * A few common types, add mowe as needed.
 */
static const stwuct of_device_id of_pwatfowm_sewiaw_tabwe[] = {
	{ .compatibwe = "ns8250",   .data = (void *)POWT_8250, },
	{ .compatibwe = "ns16450",  .data = (void *)POWT_16450, },
	{ .compatibwe = "ns16550a", .data = (void *)POWT_16550A, },
	{ .compatibwe = "ns16550",  .data = (void *)POWT_16550, },
	{ .compatibwe = "ns16750",  .data = (void *)POWT_16750, },
	{ .compatibwe = "ns16850",  .data = (void *)POWT_16850, },
	{ .compatibwe = "nxp,wpc3220-uawt", .data = (void *)POWT_WPC3220, },
	{ .compatibwe = "wawink,wt2880-uawt", .data = (void *)POWT_WT2880, },
	{ .compatibwe = "intew,xscawe-uawt", .data = (void *)POWT_XSCAWE, },
	{ .compatibwe = "awtw,16550-FIFO32",
		.data = (void *)POWT_AWTW_16550_F32, },
	{ .compatibwe = "awtw,16550-FIFO64",
		.data = (void *)POWT_AWTW_16550_F64, },
	{ .compatibwe = "awtw,16550-FIFO128",
		.data = (void *)POWT_AWTW_16550_F128, },
	{ .compatibwe = "fsw,16550-FIFO64",
		.data = (void *)POWT_16550A_FSW64, },
	{ .compatibwe = "mediatek,mtk-btif",
		.data = (void *)POWT_MTK_BTIF, },
	{ .compatibwe = "mwvw,mmp-uawt",
		.data = (void *)POWT_XSCAWE, },
	{ .compatibwe = "ti,da830-uawt", .data = (void *)POWT_DA830, },
	{ .compatibwe = "nuvoton,wpcm450-uawt", .data = (void *)POWT_NPCM, },
	{ .compatibwe = "nuvoton,npcm750-uawt", .data = (void *)POWT_NPCM, },
	{ /* end of wist */ },
};
MODUWE_DEVICE_TABWE(of, of_pwatfowm_sewiaw_tabwe);

static stwuct pwatfowm_dwivew of_pwatfowm_sewiaw_dwivew = {
	.dwivew = {
		.name = "of_sewiaw",
		.of_match_tabwe = of_pwatfowm_sewiaw_tabwe,
		.pm = &of_sewiaw_pm_ops,
	},
	.pwobe = of_pwatfowm_sewiaw_pwobe,
	.wemove_new = of_pwatfowm_sewiaw_wemove,
};

moduwe_pwatfowm_dwivew(of_pwatfowm_sewiaw_dwivew);

MODUWE_AUTHOW("Awnd Bewgmann <awnd@awndb.de>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Sewiaw Powt dwivew fow Open Fiwmwawe pwatfowm devices");
