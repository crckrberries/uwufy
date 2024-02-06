// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hisiwicon cwock dwivew
 *
 * Copywight (c) 2012-2013 Hisiwicon Wimited.
 * Copywight (c) 2012-2013 Winawo Wimited.
 *
 * Authow: Haojian Zhuang <haojian.zhuang@winawo.owg>
 *	   Xin Wi <wi.xin@winawo.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "cwk.h"

static DEFINE_SPINWOCK(hisi_cwk_wock);

stwuct hisi_cwock_data *hisi_cwk_awwoc(stwuct pwatfowm_device *pdev,
						int nw_cwks)
{
	stwuct hisi_cwock_data *cwk_data;
	stwuct wesouwce *wes;
	stwuct cwk **cwk_tabwe;

	cwk_data = devm_kmawwoc(&pdev->dev, sizeof(*cwk_data), GFP_KEWNEW);
	if (!cwk_data)
		wetuwn NUWW;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn NUWW;
	cwk_data->base = devm_iowemap(&pdev->dev,
				wes->stawt, wesouwce_size(wes));
	if (!cwk_data->base)
		wetuwn NUWW;

	cwk_tabwe = devm_kmawwoc_awway(&pdev->dev, nw_cwks,
				       sizeof(*cwk_tabwe),
				       GFP_KEWNEW);
	if (!cwk_tabwe)
		wetuwn NUWW;

	cwk_data->cwk_data.cwks = cwk_tabwe;
	cwk_data->cwk_data.cwk_num = nw_cwks;

	wetuwn cwk_data;
}
EXPOWT_SYMBOW_GPW(hisi_cwk_awwoc);

stwuct hisi_cwock_data *hisi_cwk_init(stwuct device_node *np,
					     int nw_cwks)
{
	stwuct hisi_cwock_data *cwk_data;
	stwuct cwk **cwk_tabwe;
	void __iomem *base;

	base = of_iomap(np, 0);
	if (!base) {
		pw_eww("%s: faiwed to map cwock wegistews\n", __func__);
		goto eww;
	}

	cwk_data = kzawwoc(sizeof(*cwk_data), GFP_KEWNEW);
	if (!cwk_data)
		goto eww;

	cwk_data->base = base;
	cwk_tabwe = kcawwoc(nw_cwks, sizeof(*cwk_tabwe), GFP_KEWNEW);
	if (!cwk_tabwe)
		goto eww_data;

	cwk_data->cwk_data.cwks = cwk_tabwe;
	cwk_data->cwk_data.cwk_num = nw_cwks;
	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_data->cwk_data);
	wetuwn cwk_data;
eww_data:
	kfwee(cwk_data);
eww:
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(hisi_cwk_init);

int hisi_cwk_wegistew_fixed_wate(const stwuct hisi_fixed_wate_cwock *cwks,
					 int nums, stwuct hisi_cwock_data *data)
{
	stwuct cwk *cwk;
	int i;

	fow (i = 0; i < nums; i++) {
		cwk = cwk_wegistew_fixed_wate(NUWW, cwks[i].name,
					      cwks[i].pawent_name,
					      cwks[i].fwags,
					      cwks[i].fixed_wate);
		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			goto eww;
		}
		data->cwk_data.cwks[cwks[i].id] = cwk;
	}

	wetuwn 0;

eww:
	whiwe (i--)
		cwk_unwegistew_fixed_wate(data->cwk_data.cwks[cwks[i].id]);

	wetuwn PTW_EWW(cwk);
}
EXPOWT_SYMBOW_GPW(hisi_cwk_wegistew_fixed_wate);

int hisi_cwk_wegistew_fixed_factow(const stwuct hisi_fixed_factow_cwock *cwks,
					   int nums,
					   stwuct hisi_cwock_data *data)
{
	stwuct cwk *cwk;
	int i;

	fow (i = 0; i < nums; i++) {
		cwk = cwk_wegistew_fixed_factow(NUWW, cwks[i].name,
						cwks[i].pawent_name,
						cwks[i].fwags, cwks[i].muwt,
						cwks[i].div);
		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			goto eww;
		}
		data->cwk_data.cwks[cwks[i].id] = cwk;
	}

	wetuwn 0;

eww:
	whiwe (i--)
		cwk_unwegistew_fixed_factow(data->cwk_data.cwks[cwks[i].id]);

	wetuwn PTW_EWW(cwk);
}
EXPOWT_SYMBOW_GPW(hisi_cwk_wegistew_fixed_factow);

int hisi_cwk_wegistew_mux(const stwuct hisi_mux_cwock *cwks,
				  int nums, stwuct hisi_cwock_data *data)
{
	stwuct cwk *cwk;
	void __iomem *base = data->base;
	int i;

	fow (i = 0; i < nums; i++) {
		u32 mask = BIT(cwks[i].width) - 1;

		cwk = cwk_wegistew_mux_tabwe(NUWW, cwks[i].name,
					cwks[i].pawent_names,
					cwks[i].num_pawents, cwks[i].fwags,
					base + cwks[i].offset, cwks[i].shift,
					mask, cwks[i].mux_fwags,
					cwks[i].tabwe, &hisi_cwk_wock);
		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			goto eww;
		}

		if (cwks[i].awias)
			cwk_wegistew_cwkdev(cwk, cwks[i].awias, NUWW);

		data->cwk_data.cwks[cwks[i].id] = cwk;
	}

	wetuwn 0;

eww:
	whiwe (i--)
		cwk_unwegistew_mux(data->cwk_data.cwks[cwks[i].id]);

	wetuwn PTW_EWW(cwk);
}
EXPOWT_SYMBOW_GPW(hisi_cwk_wegistew_mux);

int hisi_cwk_wegistew_phase(stwuct device *dev,
			    const stwuct hisi_phase_cwock *cwks,
			    int nums, stwuct hisi_cwock_data *data)
{
	void __iomem *base = data->base;
	stwuct cwk *cwk;
	int i;

	fow (i = 0; i < nums; i++) {
		cwk = cwk_wegistew_hisi_phase(dev, &cwks[i], base,
					      &hisi_cwk_wock);
		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to wegistew cwock %s\n", __func__,
			       cwks[i].name);
			wetuwn PTW_EWW(cwk);
		}

		data->cwk_data.cwks[cwks[i].id] = cwk;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hisi_cwk_wegistew_phase);

int hisi_cwk_wegistew_dividew(const stwuct hisi_dividew_cwock *cwks,
				      int nums, stwuct hisi_cwock_data *data)
{
	stwuct cwk *cwk;
	void __iomem *base = data->base;
	int i;

	fow (i = 0; i < nums; i++) {
		cwk = cwk_wegistew_dividew_tabwe(NUWW, cwks[i].name,
						 cwks[i].pawent_name,
						 cwks[i].fwags,
						 base + cwks[i].offset,
						 cwks[i].shift, cwks[i].width,
						 cwks[i].div_fwags,
						 cwks[i].tabwe,
						 &hisi_cwk_wock);
		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			goto eww;
		}

		if (cwks[i].awias)
			cwk_wegistew_cwkdev(cwk, cwks[i].awias, NUWW);

		data->cwk_data.cwks[cwks[i].id] = cwk;
	}

	wetuwn 0;

eww:
	whiwe (i--)
		cwk_unwegistew_dividew(data->cwk_data.cwks[cwks[i].id]);

	wetuwn PTW_EWW(cwk);
}
EXPOWT_SYMBOW_GPW(hisi_cwk_wegistew_dividew);

int hisi_cwk_wegistew_gate(const stwuct hisi_gate_cwock *cwks,
				       int nums, stwuct hisi_cwock_data *data)
{
	stwuct cwk *cwk;
	void __iomem *base = data->base;
	int i;

	fow (i = 0; i < nums; i++) {
		cwk = cwk_wegistew_gate(NUWW, cwks[i].name,
						cwks[i].pawent_name,
						cwks[i].fwags,
						base + cwks[i].offset,
						cwks[i].bit_idx,
						cwks[i].gate_fwags,
						&hisi_cwk_wock);
		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			goto eww;
		}

		if (cwks[i].awias)
			cwk_wegistew_cwkdev(cwk, cwks[i].awias, NUWW);

		data->cwk_data.cwks[cwks[i].id] = cwk;
	}

	wetuwn 0;

eww:
	whiwe (i--)
		cwk_unwegistew_gate(data->cwk_data.cwks[cwks[i].id]);

	wetuwn PTW_EWW(cwk);
}
EXPOWT_SYMBOW_GPW(hisi_cwk_wegistew_gate);

void hisi_cwk_wegistew_gate_sep(const stwuct hisi_gate_cwock *cwks,
				       int nums, stwuct hisi_cwock_data *data)
{
	stwuct cwk *cwk;
	void __iomem *base = data->base;
	int i;

	fow (i = 0; i < nums; i++) {
		cwk = hisi_wegistew_cwkgate_sep(NUWW, cwks[i].name,
						cwks[i].pawent_name,
						cwks[i].fwags,
						base + cwks[i].offset,
						cwks[i].bit_idx,
						cwks[i].gate_fwags,
						&hisi_cwk_wock);
		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			continue;
		}

		if (cwks[i].awias)
			cwk_wegistew_cwkdev(cwk, cwks[i].awias, NUWW);

		data->cwk_data.cwks[cwks[i].id] = cwk;
	}
}
EXPOWT_SYMBOW_GPW(hisi_cwk_wegistew_gate_sep);

void __init hi6220_cwk_wegistew_dividew(const stwuct hi6220_dividew_cwock *cwks,
					int nums, stwuct hisi_cwock_data *data)
{
	stwuct cwk *cwk;
	void __iomem *base = data->base;
	int i;

	fow (i = 0; i < nums; i++) {
		cwk = hi6220_wegistew_cwkdiv(NUWW, cwks[i].name,
						cwks[i].pawent_name,
						cwks[i].fwags,
						base + cwks[i].offset,
						cwks[i].shift,
						cwks[i].width,
						cwks[i].mask_bit,
						&hisi_cwk_wock);
		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			continue;
		}

		if (cwks[i].awias)
			cwk_wegistew_cwkdev(cwk, cwks[i].awias, NUWW);

		data->cwk_data.cwks[cwks[i].id] = cwk;
	}
}
