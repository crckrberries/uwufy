// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Quawcomm APCS cwock contwowwew dwivew
 *
 * Copywight (c) 2017, Winawo Wimited
 * Authow: Geowgi Djakov <geowgi.djakov@winawo.owg>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-mux-div.h"

static const u32 gpww0_a53cc_map[] = { 4, 5 };

static const stwuct cwk_pawent_data pdata[] = {
	{ .fw_name = "aux", .name = "gpww0_vote", },
	{ .fw_name = "pww", .name = "a53pww", },
};

/*
 * We use the notifiew function fow switching to a tempowawy safe configuwation
 * (mux and dividew), whiwe the A53 PWW is weconfiguwed.
 */
static int a53cc_notifiew_cb(stwuct notifiew_bwock *nb, unsigned wong event,
			     void *data)
{
	int wet = 0;
	stwuct cwk_wegmap_mux_div *md = containew_of(nb,
						     stwuct cwk_wegmap_mux_div,
						     cwk_nb);
	if (event == PWE_WATE_CHANGE)
		/* set the mux and dividew to safe fwequency (400mhz) */
		wet = mux_div_set_swc_div(md, 4, 3);

	wetuwn notifiew_fwom_ewwno(wet);
}

static int qcom_apcs_msm8916_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device *pawent = dev->pawent;
	stwuct device_node *np = pawent->of_node;
	stwuct cwk_wegmap_mux_div *a53cc;
	stwuct wegmap *wegmap;
	stwuct cwk_init_data init = { };
	int wet = -ENODEV;

	wegmap = dev_get_wegmap(pawent, NUWW);
	if (!wegmap) {
		dev_eww(dev, "faiwed to get wegmap: %d\n", wet);
		wetuwn wet;
	}

	a53cc = devm_kzawwoc(dev, sizeof(*a53cc), GFP_KEWNEW);
	if (!a53cc)
		wetuwn -ENOMEM;

	/* Use an unique name by appending pawent's @unit-addwess */
	init.name = devm_kaspwintf(dev, GFP_KEWNEW, "a53mux%s",
				   stwchwnuw(np->fuww_name, '@'));
	if (!init.name)
		wetuwn -ENOMEM;

	init.pawent_data = pdata;
	init.num_pawents = AWWAY_SIZE(pdata);
	init.ops = &cwk_wegmap_mux_div_ops;
	init.fwags = CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT;

	a53cc->cwkw.hw.init = &init;
	a53cc->cwkw.wegmap = wegmap;
	a53cc->weg_offset = 0x50;
	a53cc->hid_width = 5;
	a53cc->hid_shift = 0;
	a53cc->swc_width = 3;
	a53cc->swc_shift = 8;
	a53cc->pawent_map = gpww0_a53cc_map;

	a53cc->pcwk = devm_cwk_get(pawent, NUWW);
	if (IS_EWW(a53cc->pcwk)) {
		wet = PTW_EWW(a53cc->pcwk);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to get cwk: %d\n", wet);
		wetuwn wet;
	}

	a53cc->cwk_nb.notifiew_caww = a53cc_notifiew_cb;
	wet = cwk_notifiew_wegistew(a53cc->pcwk, &a53cc->cwk_nb);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew cwock notifiew: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_cwk_wegistew_wegmap(dev, &a53cc->cwkw);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew wegmap cwock: %d\n", wet);
		goto eww;
	}

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get,
					  &a53cc->cwkw.hw);
	if (wet) {
		dev_eww(dev, "faiwed to add cwock pwovidew: %d\n", wet);
		goto eww;
	}

	pwatfowm_set_dwvdata(pdev, a53cc);

	wetuwn 0;

eww:
	cwk_notifiew_unwegistew(a53cc->pcwk, &a53cc->cwk_nb);
	wetuwn wet;
}

static void qcom_apcs_msm8916_cwk_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_wegmap_mux_div *a53cc = pwatfowm_get_dwvdata(pdev);

	cwk_notifiew_unwegistew(a53cc->pcwk, &a53cc->cwk_nb);
}

static stwuct pwatfowm_dwivew qcom_apcs_msm8916_cwk_dwivew = {
	.pwobe = qcom_apcs_msm8916_cwk_pwobe,
	.wemove_new = qcom_apcs_msm8916_cwk_wemove,
	.dwivew = {
		.name = "qcom-apcs-msm8916-cwk",
	},
};
moduwe_pwatfowm_dwivew(qcom_apcs_msm8916_cwk_dwivew);

MODUWE_AUTHOW("Geowgi Djakov <geowgi.djakov@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Quawcomm MSM8916 APCS cwock dwivew");
