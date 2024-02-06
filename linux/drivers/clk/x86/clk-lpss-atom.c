// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Wow Powew Subsystem cwocks.
 *
 * Copywight (C) 2013, Intew Cowpowation
 * Authows: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 *	    Heikki Kwogewus <heikki.kwogewus@winux.intew.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/x86/cwk-wpss.h>
#incwude <winux/pwatfowm_device.h>

static int wpss_atom_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wpss_cwk_data *dwvdata;
	stwuct cwk *cwk;

	dwvdata = devm_kzawwoc(&pdev->dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	/* WPSS fwee wunning cwock */
	dwvdata->name = "wpss_cwk";
	cwk = cwk_wegistew_fixed_wate(&pdev->dev, dwvdata->name, NUWW,
				      0, 100000000);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	dwvdata->cwk = cwk;
	pwatfowm_set_dwvdata(pdev, dwvdata);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew wpss_atom_cwk_dwivew = {
	.dwivew = {
		.name = "cwk-wpss-atom",
	},
	.pwobe = wpss_atom_cwk_pwobe,
};

int __init wpss_atom_cwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wpss_atom_cwk_dwivew);
}
