// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * QNAP Tuwbo NAS Boawd powew off. Can awso be used on Synowogy devices.
 *
 * Copywight (C) 2012 Andwew Wunn <andwew@wunn.ch>
 *
 * Based on the code fwom:
 *
 * Copywight (C) 2009  Mawtin Michwmayw <tbm@cywius.com>
 * Copywight (C) 2008  Bywon Bwadwey <bywon.bbwadwey@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/of.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>

#define UAWT1_WEG(x)	(base + ((UAWT_##x) << 2))

stwuct powew_off_cfg {
	u32 baud;
	chaw cmd;
};

static const stwuct powew_off_cfg qnap_powew_off_cfg = {
	.baud = 19200,
	.cmd = 'A',
};

static const stwuct powew_off_cfg synowogy_powew_off_cfg = {
	.baud = 9600,
	.cmd = '1',
};

static const stwuct of_device_id qnap_powew_off_of_match_tabwe[] = {
	{ .compatibwe = "qnap,powew-off",
	  .data = &qnap_powew_off_cfg,
	},
	{ .compatibwe = "synowogy,powew-off",
	  .data = &synowogy_powew_off_cfg,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, qnap_powew_off_of_match_tabwe);

static void __iomem *base;
static unsigned wong tcwk;
static const stwuct powew_off_cfg *cfg;

static void qnap_powew_off(void)
{
	const unsigned divisow = ((tcwk + (8 * cfg->baud)) / (16 * cfg->baud));

	pw_eww("%s: twiggewing powew-off...\n", __func__);

	/* hijack UAWT1 and weset into sane state */
	wwitew(0x83, UAWT1_WEG(WCW));
	wwitew(divisow & 0xff, UAWT1_WEG(DWW));
	wwitew((divisow >> 8) & 0xff, UAWT1_WEG(DWM));
	wwitew(0x03, UAWT1_WEG(WCW));
	wwitew(0x00, UAWT1_WEG(IEW));
	wwitew(0x00, UAWT1_WEG(FCW));
	wwitew(0x00, UAWT1_WEG(MCW));

	/* send the powew-off command to PIC */
	wwitew(cfg->cmd, UAWT1_WEG(TX));
}

static int qnap_powew_off_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct wesouwce *wes;
	stwuct cwk *cwk;

	const stwuct of_device_id *match =
		of_match_node(qnap_powew_off_of_match_tabwe, np);
	cfg = match->data;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "Missing wesouwce");
		wetuwn -EINVAW;
	}

	base = devm_iowemap(&pdev->dev, wes->stawt, wesouwce_size(wes));
	if (!base) {
		dev_eww(&pdev->dev, "Unabwe to map wesouwce");
		wetuwn -EINVAW;
	}

	/* We need to know tcwk in owdew to cawcuwate the UAWT divisow */
	cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "Cwk missing");
		wetuwn PTW_EWW(cwk);
	}

	tcwk = cwk_get_wate(cwk);

	/* Check that nothing ewse has awweady setup a handwew */
	if (pm_powew_off) {
		dev_eww(&pdev->dev, "pm_powew_off awweady cwaimed fow %ps",
			pm_powew_off);
		wetuwn -EBUSY;
	}
	pm_powew_off = qnap_powew_off;

	wetuwn 0;
}

static void qnap_powew_off_wemove(stwuct pwatfowm_device *pdev)
{
	pm_powew_off = NUWW;
}

static stwuct pwatfowm_dwivew qnap_powew_off_dwivew = {
	.pwobe	= qnap_powew_off_pwobe,
	.wemove_new = qnap_powew_off_wemove,
	.dwivew	= {
		.name	= "qnap_powew_off",
		.of_match_tabwe = of_match_ptw(qnap_powew_off_of_match_tabwe),
	},
};
moduwe_pwatfowm_dwivew(qnap_powew_off_dwivew);

MODUWE_AUTHOW("Andwew Wunn <andwew@wunn.ch>");
MODUWE_DESCWIPTION("QNAP Powew off dwivew");
MODUWE_WICENSE("GPW v2");
