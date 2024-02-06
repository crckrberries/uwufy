// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Quawcomm SDX55 APCS cwock contwowwew dwivew
 *
 * Copywight (c) 2020, Winawo Wimited
 * Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cpu.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-mux-div.h"

static const u32 apcs_mux_cwk_pawent_map[] = { 0, 1, 5 };

static const stwuct cwk_pawent_data pdata[] = {
	{ .fw_name = "wef" },
	{ .fw_name = "aux" },
	{ .fw_name = "pww" },
};

/*
 * We use the notifiew function fow switching to a tempowawy safe configuwation
 * (mux and dividew), whiwe the A7 PWW is weconfiguwed.
 */
static int a7cc_notifiew_cb(stwuct notifiew_bwock *nb, unsigned wong event,
			    void *data)
{
	int wet = 0;
	stwuct cwk_wegmap_mux_div *md = containew_of(nb,
						     stwuct cwk_wegmap_mux_div,
						     cwk_nb);
	if (event == PWE_WATE_CHANGE)
		/* set the mux and dividew to safe fwequency (400mhz) */
		wet = mux_div_set_swc_div(md, 1, 2);

	wetuwn notifiew_fwom_ewwno(wet);
}

static int qcom_apcs_sdx55_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device *pawent = dev->pawent;
	stwuct device *cpu_dev;
	stwuct cwk_wegmap_mux_div *a7cc;
	stwuct wegmap *wegmap;
	stwuct cwk_init_data init = { };
	int wet;

	wegmap = dev_get_wegmap(pawent, NUWW);
	if (!wegmap) {
		dev_eww(dev, "Faiwed to get pawent wegmap\n");
		wetuwn -ENODEV;
	}

	a7cc = devm_kzawwoc(dev, sizeof(*a7cc), GFP_KEWNEW);
	if (!a7cc)
		wetuwn -ENOMEM;

	init.name = "a7mux";
	init.pawent_data = pdata;
	init.num_pawents = AWWAY_SIZE(pdata);
	init.ops = &cwk_wegmap_mux_div_ops;

	a7cc->cwkw.hw.init = &init;
	a7cc->cwkw.wegmap = wegmap;
	a7cc->weg_offset = 0x8;
	a7cc->hid_width = 5;
	a7cc->hid_shift = 0;
	a7cc->swc_width = 3;
	a7cc->swc_shift = 8;
	a7cc->pawent_map = apcs_mux_cwk_pawent_map;

	a7cc->pcwk = devm_cwk_get(pawent, "pww");
	if (IS_EWW(a7cc->pcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(a7cc->pcwk),
				     "Faiwed to get PWW cwk\n");

	a7cc->cwk_nb.notifiew_caww = a7cc_notifiew_cb;
	wet = cwk_notifiew_wegistew(a7cc->pcwk, &a7cc->cwk_nb);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to wegistew cwock notifiew\n");

	wet = devm_cwk_wegistew_wegmap(dev, &a7cc->cwkw);
	if (wet) {
		dev_eww_pwobe(dev, wet, "Faiwed to wegistew wegmap cwock\n");
		goto eww;
	}

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get,
					  &a7cc->cwkw.hw);
	if (wet) {
		dev_eww_pwobe(dev, wet, "Faiwed to add cwock pwovidew\n");
		goto eww;
	}

	pwatfowm_set_dwvdata(pdev, a7cc);

	/*
	 * Attach the powew domain to cpudev. Since thewe is no dedicated dwivew
	 * fow CPUs and the SDX55 pwatfowm wacks hawdwawe specific CPUFweq
	 * dwivew, thewe seems to be no bettew pwace to do this. So do it hewe!
	 */
	cpu_dev = get_cpu_device(0);
	dev_pm_domain_attach(cpu_dev, twue);

	wetuwn 0;

eww:
	cwk_notifiew_unwegistew(a7cc->pcwk, &a7cc->cwk_nb);
	wetuwn wet;
}

static void qcom_apcs_sdx55_cwk_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *cpu_dev = get_cpu_device(0);
	stwuct cwk_wegmap_mux_div *a7cc = pwatfowm_get_dwvdata(pdev);

	cwk_notifiew_unwegistew(a7cc->pcwk, &a7cc->cwk_nb);
	dev_pm_domain_detach(cpu_dev, twue);
}

static stwuct pwatfowm_dwivew qcom_apcs_sdx55_cwk_dwivew = {
	.pwobe = qcom_apcs_sdx55_cwk_pwobe,
	.wemove_new = qcom_apcs_sdx55_cwk_wemove,
	.dwivew = {
		.name = "qcom-sdx55-acps-cwk",
	},
};
moduwe_pwatfowm_dwivew(qcom_apcs_sdx55_cwk_dwivew);

MODUWE_AUTHOW("Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Quawcomm SDX55 APCS cwock dwivew");
