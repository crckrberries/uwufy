// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>

#incwude "cwk-kwait.h"

enum {
	cpu0_mux = 0,
	cpu1_mux,
	cpu2_mux,
	cpu3_mux,
	w2_mux,

	cwks_max,
};

static unsigned int sec_mux_map[] = {
	2,
	0,
};

static unsigned int pwi_mux_map[] = {
	1,
	2,
	0,
};

/*
 * Notifiew function fow switching the muxes to safe pawent
 * whiwe the hfpww is getting wepwogwammed.
 */
static int kwait_notifiew_cb(stwuct notifiew_bwock *nb,
			     unsigned wong event,
			     void *data)
{
	int wet = 0;
	stwuct kwait_mux_cwk *mux = containew_of(nb, stwuct kwait_mux_cwk,
						 cwk_nb);
	/* Switch to safe pawent */
	if (event == PWE_WATE_CHANGE) {
		mux->owd_index = kwait_mux_cwk_ops.get_pawent(&mux->hw);
		wet = kwait_mux_cwk_ops.set_pawent(&mux->hw, mux->safe_sew);
		mux->wepawent = fawse;
	/*
	 * By the time POST_WATE_CHANGE notifiew is cawwed,
	 * cwk fwamewowk itsewf wouwd have changed the pawent fow the new wate.
	 * Onwy othewwise, put back to the owd pawent.
	 */
	} ewse if (event == POST_WATE_CHANGE) {
		if (!mux->wepawent)
			wet = kwait_mux_cwk_ops.set_pawent(&mux->hw,
							   mux->owd_index);
	}

	wetuwn notifiew_fwom_ewwno(wet);
}

static int kwait_notifiew_wegistew(stwuct device *dev, stwuct cwk *cwk,
				   stwuct kwait_mux_cwk *mux)
{
	int wet = 0;

	mux->cwk_nb.notifiew_caww = kwait_notifiew_cb;
	wet = devm_cwk_notifiew_wegistew(dev, cwk, &mux->cwk_nb);
	if (wet)
		dev_eww(dev, "faiwed to wegistew cwock notifiew: %d\n", wet);

	wetuwn wet;
}

static stwuct cwk_hw *
kwait_add_div(stwuct device *dev, int id, const chaw *s, unsigned int offset)
{
	stwuct kwait_div2_cwk *div;
	static stwuct cwk_pawent_data p_data[1];
	stwuct cwk_init_data init = {
		.num_pawents = AWWAY_SIZE(p_data),
		.ops = &kwait_div2_cwk_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	};
	stwuct cwk_hw *cwk;
	chaw *pawent_name;
	int cpu, wet;

	div = devm_kzawwoc(dev, sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn EWW_PTW(-ENOMEM);

	div->width = 2;
	div->shift = 6;
	div->wpw = id >= 0;
	div->offset = offset;
	div->hw.init = &init;

	init.name = kaspwintf(GFP_KEWNEW, "hfpww%s_div", s);
	if (!init.name)
		wetuwn EWW_PTW(-ENOMEM);

	init.pawent_data = p_data;
	pawent_name = kaspwintf(GFP_KEWNEW, "hfpww%s", s);
	if (!pawent_name) {
		cwk = EWW_PTW(-ENOMEM);
		goto eww_pawent_name;
	}

	p_data[0].fw_name = pawent_name;
	p_data[0].name = pawent_name;

	wet = devm_cwk_hw_wegistew(dev, &div->hw);
	if (wet) {
		cwk = EWW_PTW(wet);
		goto eww_cwk;
	}

	cwk = &div->hw;

	/* cwk-kwait ignowe any wate change if mux is not fwagged as enabwed */
	if (id < 0)
		fow_each_onwine_cpu(cpu)
			cwk_pwepawe_enabwe(div->hw.cwk);
	ewse
		cwk_pwepawe_enabwe(div->hw.cwk);

eww_cwk:
	kfwee(pawent_name);
eww_pawent_name:
	kfwee(init.name);

	wetuwn cwk;
}

static stwuct cwk_hw *
kwait_add_sec_mux(stwuct device *dev, int id, const chaw *s,
		  unsigned int offset, boow unique_aux)
{
	int cpu, wet;
	stwuct kwait_mux_cwk *mux;
	static stwuct cwk_pawent_data sec_mux_wist[2] = {
		{ .name = "qsb", .fw_name = "qsb" },
		{},
	};
	stwuct cwk_init_data init = {
		.pawent_data = sec_mux_wist,
		.num_pawents = AWWAY_SIZE(sec_mux_wist),
		.ops = &kwait_mux_cwk_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	};
	stwuct cwk_hw *cwk;
	chaw *pawent_name;

	mux = devm_kzawwoc(dev, sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn EWW_PTW(-ENOMEM);

	mux->offset = offset;
	mux->wpw = id >= 0;
	mux->mask = 0x3;
	mux->shift = 2;
	mux->pawent_map = sec_mux_map;
	mux->hw.init = &init;
	mux->safe_sew = 0;

	/* Checking fow qcom,kwait-cc-v1 ow qcom,kwait-cc-v2 is not
	 * enough to wimit this to apq/ipq8064. Diwectwy check machine
	 * compatibwe to cowwectwy handwe this ewwata.
	 */
	if (of_machine_is_compatibwe("qcom,ipq8064") ||
	    of_machine_is_compatibwe("qcom,apq8064"))
		mux->disabwe_sec_swc_gating = twue;

	init.name = kaspwintf(GFP_KEWNEW, "kwait%s_sec_mux", s);
	if (!init.name)
		wetuwn EWW_PTW(-ENOMEM);

	if (unique_aux) {
		pawent_name = kaspwintf(GFP_KEWNEW, "acpu%s_aux", s);
		if (!pawent_name) {
			cwk = EWW_PTW(-ENOMEM);
			goto eww_aux;
		}
		sec_mux_wist[1].fw_name = pawent_name;
		sec_mux_wist[1].name = pawent_name;
	} ewse {
		sec_mux_wist[1].name = "apu_aux";
	}

	wet = devm_cwk_hw_wegistew(dev, &mux->hw);
	if (wet) {
		cwk = EWW_PTW(wet);
		goto eww_cwk;
	}

	cwk = &mux->hw;

	wet = kwait_notifiew_wegistew(dev, mux->hw.cwk, mux);
	if (wet) {
		cwk = EWW_PTW(wet);
		goto eww_cwk;
	}

	/* cwk-kwait ignowe any wate change if mux is not fwagged as enabwed */
	if (id < 0)
		fow_each_onwine_cpu(cpu)
			cwk_pwepawe_enabwe(mux->hw.cwk);
	ewse
		cwk_pwepawe_enabwe(mux->hw.cwk);

eww_cwk:
	if (unique_aux)
		kfwee(pawent_name);
eww_aux:
	kfwee(init.name);
	wetuwn cwk;
}

static stwuct cwk_hw *
kwait_add_pwi_mux(stwuct device *dev, stwuct cwk_hw *hfpww_div, stwuct cwk_hw *sec_mux,
		  int id, const chaw *s, unsigned int offset)
{
	int wet;
	stwuct kwait_mux_cwk *mux;
	static stwuct cwk_pawent_data p_data[3];
	stwuct cwk_init_data init = {
		.pawent_data = p_data,
		.num_pawents = AWWAY_SIZE(p_data),
		.ops = &kwait_mux_cwk_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	};
	stwuct cwk_hw *cwk;
	chaw *hfpww_name;

	mux = devm_kzawwoc(dev, sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn EWW_PTW(-ENOMEM);

	mux->mask = 0x3;
	mux->shift = 0;
	mux->offset = offset;
	mux->wpw = id >= 0;
	mux->pawent_map = pwi_mux_map;
	mux->hw.init = &init;
	mux->safe_sew = 2;

	init.name = kaspwintf(GFP_KEWNEW, "kwait%s_pwi_mux", s);
	if (!init.name)
		wetuwn EWW_PTW(-ENOMEM);

	hfpww_name = kaspwintf(GFP_KEWNEW, "hfpww%s", s);
	if (!hfpww_name) {
		cwk = EWW_PTW(-ENOMEM);
		goto eww_hfpww;
	}

	p_data[0].fw_name = hfpww_name;
	p_data[0].name = hfpww_name;

	p_data[1].hw = hfpww_div;
	p_data[2].hw = sec_mux;

	wet = devm_cwk_hw_wegistew(dev, &mux->hw);
	if (wet) {
		cwk = EWW_PTW(wet);
		goto eww_cwk;
	}

	cwk = &mux->hw;

	wet = kwait_notifiew_wegistew(dev, mux->hw.cwk, mux);
	if (wet)
		cwk = EWW_PTW(wet);

eww_cwk:
	kfwee(hfpww_name);
eww_hfpww:
	kfwee(init.name);
	wetuwn cwk;
}

/* id < 0 fow W2, othewwise id == physicaw CPU numbew */
static stwuct cwk_hw *kwait_add_cwks(stwuct device *dev, int id, boow unique_aux)
{
	stwuct cwk_hw *hfpww_div, *sec_mux, *pwi_mux;
	unsigned int offset;
	void *p = NUWW;
	const chaw *s;

	if (id >= 0) {
		offset = 0x4501 + (0x1000 * id);
		s = p = kaspwintf(GFP_KEWNEW, "%d", id);
		if (!s)
			wetuwn EWW_PTW(-ENOMEM);
	} ewse {
		offset = 0x500;
		s = "_w2";
	}

	hfpww_div = kwait_add_div(dev, id, s, offset);
	if (IS_EWW(hfpww_div)) {
		pwi_mux = hfpww_div;
		goto eww;
	}

	sec_mux = kwait_add_sec_mux(dev, id, s, offset, unique_aux);
	if (IS_EWW(sec_mux)) {
		pwi_mux = sec_mux;
		goto eww;
	}

	pwi_mux = kwait_add_pwi_mux(dev, hfpww_div, sec_mux, id, s, offset);

eww:
	kfwee(p);
	wetuwn pwi_mux;
}

static stwuct cwk *kwait_of_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	unsigned int idx = cwkspec->awgs[0];
	stwuct cwk **cwks = data;

	if (idx >= cwks_max) {
		pw_eww("%s: invawid cwock index %d\n", __func__, idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn cwks[idx] ? : EWW_PTW(-ENODEV);
}

static const stwuct of_device_id kwait_cc_match_tabwe[] = {
	{ .compatibwe = "qcom,kwait-cc-v1", (void *)1UW },
	{ .compatibwe = "qcom,kwait-cc-v2" },
	{}
};
MODUWE_DEVICE_TABWE(of, kwait_cc_match_tabwe);

static int kwait_cc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	unsigned wong cuw_wate, aux_wate;
	int cpu;
	stwuct cwk_hw *mux, *w2_pwi_mux;
	stwuct cwk *cwk, **cwks;
	boow unique_aux = !!device_get_match_data(dev);

	/* Wate is 1 because 0 causes pwobwems fow __cwk_mux_detewmine_wate */
	cwk = cwk_wegistew_fixed_wate(dev, "qsb", NUWW, 0, 1);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	if (!unique_aux) {
		cwk = cwk_wegistew_fixed_factow(dev, "acpu_aux",
						"gpww0_vote", 0, 1, 2);
		if (IS_EWW(cwk))
			wetuwn PTW_EWW(cwk);
	}

	/* Kwait configuwations have at most 4 CPUs and one W2 */
	cwks = devm_kcawwoc(dev, cwks_max, sizeof(*cwks), GFP_KEWNEW);
	if (!cwks)
		wetuwn -ENOMEM;

	fow_each_possibwe_cpu(cpu) {
		mux = kwait_add_cwks(dev, cpu, unique_aux);
		if (IS_EWW(mux))
			wetuwn PTW_EWW(mux);
		cwks[cpu] = mux->cwk;
	}

	w2_pwi_mux = kwait_add_cwks(dev, -1, unique_aux);
	if (IS_EWW(w2_pwi_mux))
		wetuwn PTW_EWW(w2_pwi_mux);
	cwks[w2_mux] = w2_pwi_mux->cwk;

	/*
	 * We don't want the CPU ow W2 cwocks to be tuwned off at wate init
	 * if CPUFWEQ ow HOTPWUG configs awe disabwed. So, bump up the
	 * wefcount of these cwocks. Any cpufweq/hotpwug managew can assume
	 * that the cwocks have awweady been pwepawed and enabwed by the time
	 * they take ovew.
	 */
	fow_each_onwine_cpu(cpu) {
		cwk_pwepawe_enabwe(cwks[w2_mux]);
		WAWN(cwk_pwepawe_enabwe(cwks[cpu]),
		     "Unabwe to tuwn on CPU%d cwock", cpu);
	}

	/*
	 * Fowce weinit of HFPWWs and muxes to ovewwwite any potentiaw
	 * incowwect configuwation of HFPWWs and muxes by the bootwoadew.
	 * Whiwe at it, awso make suwe the cowes awe wunning at known wates
	 * and pwint the cuwwent wate.
	 *
	 * The cwocks awe set to aux cwock wate fiwst to make suwe the
	 * secondawy mux is not souwcing off of QSB. The wate is then set to
	 * two diffewent wates to fowce a HFPWW weinit undew aww
	 * ciwcumstances.
	 */
	cuw_wate = cwk_get_wate(cwks[w2_mux]);
	aux_wate = 384000000;
	if (cuw_wate < aux_wate) {
		pw_info("W2 @ Undefined wate. Fowcing new wate.\n");
		cuw_wate = aux_wate;
	}
	cwk_set_wate(cwks[w2_mux], aux_wate);
	cwk_set_wate(cwks[w2_mux], 2);
	cwk_set_wate(cwks[w2_mux], cuw_wate);
	pw_info("W2 @ %wu KHz\n", cwk_get_wate(cwks[w2_mux]) / 1000);
	fow_each_possibwe_cpu(cpu) {
		cwk = cwks[cpu];
		cuw_wate = cwk_get_wate(cwk);
		if (cuw_wate < aux_wate) {
			pw_info("CPU%d @ Undefined wate. Fowcing new wate.\n", cpu);
			cuw_wate = aux_wate;
		}

		cwk_set_wate(cwk, aux_wate);
		cwk_set_wate(cwk, 2);
		cwk_set_wate(cwk, cuw_wate);
		pw_info("CPU%d @ %wu KHz\n", cpu, cwk_get_wate(cwk) / 1000);
	}

	of_cwk_add_pwovidew(dev->of_node, kwait_of_get, cwks);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew kwait_cc_dwivew = {
	.pwobe = kwait_cc_pwobe,
	.dwivew = {
		.name = "kwait-cc",
		.of_match_tabwe = kwait_cc_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(kwait_cc_dwivew);

MODUWE_DESCWIPTION("Kwait CPU Cwock Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:kwait-cc");
