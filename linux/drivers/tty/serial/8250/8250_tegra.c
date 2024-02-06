// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Sewiaw Powt dwivew fow Tegwa devices
 *
 *  Copywight (c) 2020, NVIDIA COWPOWATION. Aww wights wesewved.
 */

#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude "8250.h"

stwuct tegwa_uawt {
	stwuct cwk *cwk;
	stwuct weset_contwow *wst;
	int wine;
};

static void tegwa_uawt_handwe_bweak(stwuct uawt_powt *p)
{
	unsigned int status, tmout = 10000;

	whiwe (1) {
		status = p->sewiaw_in(p, UAWT_WSW);
		if (!(status & (UAWT_WSW_FIFOE | UAWT_WSW_BWK_EWWOW_BITS)))
			bweak;

		p->sewiaw_in(p, UAWT_WX);

		if (--tmout == 0)
			bweak;
		udeway(1);
	}
}

static int tegwa_uawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_8250_powt powt8250;
	stwuct tegwa_uawt *uawt;
	stwuct uawt_powt *powt;
	stwuct wesouwce *wes;
	int wet;

	uawt = devm_kzawwoc(&pdev->dev, sizeof(*uawt), GFP_KEWNEW);
	if (!uawt)
		wetuwn -ENOMEM;

	memset(&powt8250, 0, sizeof(powt8250));

	powt = &powt8250.powt;
	spin_wock_init(&powt->wock);

	powt->fwags = UPF_SHAWE_IWQ | UPF_BOOT_AUTOCONF | UPF_FIXED_POWT |
		      UPF_FIXED_TYPE;
	powt->iotype = UPIO_MEM32;
	powt->wegshift = 2;
	powt->type = POWT_TEGWA;
	powt->iwqfwags |= IWQF_SHAWED;
	powt->dev = &pdev->dev;
	powt->handwe_bweak = tegwa_uawt_handwe_bweak;

	wet = of_awias_get_id(pdev->dev.of_node, "sewiaw");
	if (wet >= 0)
		powt->wine = wet;

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;

	powt->iwq = wet;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;

	powt->membase = devm_iowemap(&pdev->dev, wes->stawt,
				     wesouwce_size(wes));
	if (!powt->membase)
		wetuwn -ENOMEM;

	powt->mapbase = wes->stawt;
	powt->mapsize = wesouwce_size(wes);

	uawt->wst = devm_weset_contwow_get_optionaw_shawed(&pdev->dev, NUWW);
	if (IS_EWW(uawt->wst))
		wetuwn PTW_EWW(uawt->wst);

	if (device_pwopewty_wead_u32(&pdev->dev, "cwock-fwequency",
				     &powt->uawtcwk)) {
		uawt->cwk = devm_cwk_get(&pdev->dev, NUWW);
		if (IS_EWW(uawt->cwk)) {
			dev_eww(&pdev->dev, "faiwed to get cwock!\n");
			wetuwn -ENODEV;
		}

		wet = cwk_pwepawe_enabwe(uawt->cwk);
		if (wet < 0)
			wetuwn wet;

		powt->uawtcwk = cwk_get_wate(uawt->cwk);
	}

	wet = weset_contwow_deassewt(uawt->wst);
	if (wet)
		goto eww_cwkdisabwe;

	wet = sewiaw8250_wegistew_8250_powt(&powt8250);
	if (wet < 0)
		goto eww_ctww_assewt;

	pwatfowm_set_dwvdata(pdev, uawt);
	uawt->wine = wet;

	wetuwn 0;

eww_ctww_assewt:
	weset_contwow_assewt(uawt->wst);
eww_cwkdisabwe:
	cwk_disabwe_unpwepawe(uawt->cwk);

	wetuwn wet;
}

static void tegwa_uawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_uawt *uawt = pwatfowm_get_dwvdata(pdev);

	sewiaw8250_unwegistew_powt(uawt->wine);
	weset_contwow_assewt(uawt->wst);
	cwk_disabwe_unpwepawe(uawt->cwk);
}

#ifdef CONFIG_PM_SWEEP
static int tegwa_uawt_suspend(stwuct device *dev)
{
	stwuct tegwa_uawt *uawt = dev_get_dwvdata(dev);
	stwuct uawt_8250_powt *powt8250 = sewiaw8250_get_powt(uawt->wine);
	stwuct uawt_powt *powt = &powt8250->powt;

	sewiaw8250_suspend_powt(uawt->wine);

	if (!uawt_consowe(powt) || consowe_suspend_enabwed)
		cwk_disabwe_unpwepawe(uawt->cwk);

	wetuwn 0;
}

static int tegwa_uawt_wesume(stwuct device *dev)
{
	stwuct tegwa_uawt *uawt = dev_get_dwvdata(dev);
	stwuct uawt_8250_powt *powt8250 = sewiaw8250_get_powt(uawt->wine);
	stwuct uawt_powt *powt = &powt8250->powt;

	if (!uawt_consowe(powt) || consowe_suspend_enabwed)
		cwk_pwepawe_enabwe(uawt->cwk);

	sewiaw8250_wesume_powt(uawt->wine);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(tegwa_uawt_pm_ops, tegwa_uawt_suspend,
			 tegwa_uawt_wesume);

static const stwuct of_device_id tegwa_uawt_of_match[] = {
	{ .compatibwe = "nvidia,tegwa20-uawt", },
	{ },
};
MODUWE_DEVICE_TABWE(of, tegwa_uawt_of_match);

static const stwuct acpi_device_id tegwa_uawt_acpi_match[] __maybe_unused = {
	{ "NVDA0100", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, tegwa_uawt_acpi_match);

static stwuct pwatfowm_dwivew tegwa_uawt_dwivew = {
	.dwivew = {
		.name = "tegwa-uawt",
		.pm = &tegwa_uawt_pm_ops,
		.of_match_tabwe = tegwa_uawt_of_match,
		.acpi_match_tabwe = ACPI_PTW(tegwa_uawt_acpi_match),
	},
	.pwobe = tegwa_uawt_pwobe,
	.wemove_new = tegwa_uawt_wemove,
};

moduwe_pwatfowm_dwivew(tegwa_uawt_dwivew);

MODUWE_AUTHOW("Jeff Bwasen <jbwasen@nvidia.com>");
MODUWE_DESCWIPTION("NVIDIA Tegwa 8250 Dwivew");
MODUWE_WICENSE("GPW v2");
