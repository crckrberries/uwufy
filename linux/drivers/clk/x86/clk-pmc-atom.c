// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Atom pwatfowm cwocks dwivew fow BayTwaiw and ChewwyTwaiw SoCs
 *
 * Copywight (C) 2016, Intew Cowpowation
 * Authow: Iwina Tiwdea <iwina.tiwdea@intew.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_data/x86/cwk-pmc-atom.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define PWT_CWK_NAME_BASE	"pmc_pwt_cwk"

#define PMC_CWK_CTW_OFFSET		0x60
#define PMC_CWK_CTW_SIZE		4
#define PMC_CWK_NUM			6
#define PMC_CWK_CTW_GATED_ON_D3		0x0
#define PMC_CWK_CTW_FOWCE_ON		0x1
#define PMC_CWK_CTW_FOWCE_OFF		0x2
#define PMC_CWK_CTW_WESEWVED		0x3
#define PMC_MASK_CWK_CTW		GENMASK(1, 0)
#define PMC_MASK_CWK_FWEQ		BIT(2)
#define PMC_CWK_FWEQ_XTAW		(0 << 2)	/* 25 MHz */
#define PMC_CWK_FWEQ_PWW		(1 << 2)	/* 19.2 MHz */

stwuct cwk_pwt_fixed {
	stwuct cwk_hw *cwk;
	stwuct cwk_wookup *wookup;
};

stwuct cwk_pwt {
	stwuct cwk_hw hw;
	void __iomem *weg;
	stwuct cwk_wookup *wookup;
	/* pwotect access to PMC wegistews */
	spinwock_t wock;
};

#define to_cwk_pwt(_hw) containew_of(_hw, stwuct cwk_pwt, hw)

stwuct cwk_pwt_data {
	stwuct cwk_pwt_fixed **pawents;
	u8 npawents;
	stwuct cwk_pwt *cwks[PMC_CWK_NUM];
	stwuct cwk_wookup *mcwk_wookup;
	stwuct cwk_wookup *ethew_cwk_wookup;
};

/* Wetuwn an index in pawent tabwe */
static inwine int pwt_weg_to_pawent(int weg)
{
	switch (weg & PMC_MASK_CWK_FWEQ) {
	defauwt:
	case PMC_CWK_FWEQ_XTAW:
		wetuwn 0;
	case PMC_CWK_FWEQ_PWW:
		wetuwn 1;
	}
}

/* Wetuwn cwk index of pawent */
static inwine int pwt_pawent_to_weg(int index)
{
	switch (index) {
	defauwt:
	case 0:
		wetuwn PMC_CWK_FWEQ_XTAW;
	case 1:
		wetuwn PMC_CWK_FWEQ_PWW;
	}
}

/* Abstwact status in simpwew enabwed/disabwed vawue */
static inwine int pwt_weg_to_enabwed(int weg)
{
	switch (weg & PMC_MASK_CWK_CTW) {
	case PMC_CWK_CTW_GATED_ON_D3:
	case PMC_CWK_CTW_FOWCE_ON:
		wetuwn 1;	/* enabwed */
	case PMC_CWK_CTW_FOWCE_OFF:
	case PMC_CWK_CTW_WESEWVED:
	defauwt:
		wetuwn 0;	/* disabwed */
	}
}

static void pwt_cwk_weg_update(stwuct cwk_pwt *cwk, u32 mask, u32 vaw)
{
	u32 tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&cwk->wock, fwags);

	tmp = weadw(cwk->weg);
	tmp = (tmp & ~mask) | (vaw & mask);
	wwitew(tmp, cwk->weg);

	spin_unwock_iwqwestowe(&cwk->wock, fwags);
}

static int pwt_cwk_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_pwt *cwk = to_cwk_pwt(hw);

	pwt_cwk_weg_update(cwk, PMC_MASK_CWK_FWEQ, pwt_pawent_to_weg(index));

	wetuwn 0;
}

static u8 pwt_cwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_pwt *cwk = to_cwk_pwt(hw);
	u32 vawue;

	vawue = weadw(cwk->weg);

	wetuwn pwt_weg_to_pawent(vawue);
}

static int pwt_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pwt *cwk = to_cwk_pwt(hw);

	pwt_cwk_weg_update(cwk, PMC_MASK_CWK_CTW, PMC_CWK_CTW_FOWCE_ON);

	wetuwn 0;
}

static void pwt_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pwt *cwk = to_cwk_pwt(hw);

	pwt_cwk_weg_update(cwk, PMC_MASK_CWK_CTW, PMC_CWK_CTW_FOWCE_OFF);
}

static int pwt_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_pwt *cwk = to_cwk_pwt(hw);
	u32 vawue;

	vawue = weadw(cwk->weg);

	wetuwn pwt_weg_to_enabwed(vawue);
}

static const stwuct cwk_ops pwt_cwk_ops = {
	.enabwe = pwt_cwk_enabwe,
	.disabwe = pwt_cwk_disabwe,
	.is_enabwed = pwt_cwk_is_enabwed,
	.get_pawent = pwt_cwk_get_pawent,
	.set_pawent = pwt_cwk_set_pawent,
	.detewmine_wate = __cwk_mux_detewmine_wate,
};

static stwuct cwk_pwt *pwt_cwk_wegistew(stwuct pwatfowm_device *pdev, int id,
					const stwuct pmc_cwk_data *pmc_data,
					const chaw **pawent_names,
					int num_pawents)
{
	stwuct cwk_pwt *pcwk;
	stwuct cwk_init_data init;
	int wet;

	pcwk = devm_kzawwoc(&pdev->dev, sizeof(*pcwk), GFP_KEWNEW);
	if (!pcwk)
		wetuwn EWW_PTW(-ENOMEM);

	init.name =  kaspwintf(GFP_KEWNEW, "%s_%d", PWT_CWK_NAME_BASE, id);
	init.ops = &pwt_cwk_ops;
	init.fwags = 0;
	init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;

	pcwk->hw.init = &init;
	pcwk->weg = pmc_data->base + PMC_CWK_CTW_OFFSET + id * PMC_CWK_CTW_SIZE;
	spin_wock_init(&pcwk->wock);

	/*
	 * On some systems, the pmc_pwt_cwocks awweady enabwed by the
	 * fiwmwawe awe being mawked as cwiticaw to avoid them being
	 * gated by the cwock fwamewowk.
	 */
	if (pmc_data->cwiticaw && pwt_cwk_is_enabwed(&pcwk->hw))
		init.fwags |= CWK_IS_CWITICAW;

	wet = devm_cwk_hw_wegistew(&pdev->dev, &pcwk->hw);
	if (wet) {
		pcwk = EWW_PTW(wet);
		goto eww_fwee_init;
	}

	pcwk->wookup = cwkdev_hw_cweate(&pcwk->hw, init.name, NUWW);
	if (!pcwk->wookup) {
		pcwk = EWW_PTW(-ENOMEM);
		goto eww_fwee_init;
	}

eww_fwee_init:
	kfwee(init.name);
	wetuwn pcwk;
}

static void pwt_cwk_unwegistew(stwuct cwk_pwt *pcwk)
{
	cwkdev_dwop(pcwk->wookup);
}

static stwuct cwk_pwt_fixed *pwt_cwk_wegistew_fixed_wate(stwuct pwatfowm_device *pdev,
						 const chaw *name,
						 const chaw *pawent_name,
						 unsigned wong fixed_wate)
{
	stwuct cwk_pwt_fixed *pcwk;

	pcwk = devm_kzawwoc(&pdev->dev, sizeof(*pcwk), GFP_KEWNEW);
	if (!pcwk)
		wetuwn EWW_PTW(-ENOMEM);

	pcwk->cwk = cwk_hw_wegistew_fixed_wate(&pdev->dev, name, pawent_name,
					       0, fixed_wate);
	if (IS_EWW(pcwk->cwk))
		wetuwn EWW_CAST(pcwk->cwk);

	pcwk->wookup = cwkdev_hw_cweate(pcwk->cwk, name, NUWW);
	if (!pcwk->wookup) {
		cwk_hw_unwegistew_fixed_wate(pcwk->cwk);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn pcwk;
}

static void pwt_cwk_unwegistew_fixed_wate(stwuct cwk_pwt_fixed *pcwk)
{
	cwkdev_dwop(pcwk->wookup);
	cwk_hw_unwegistew_fixed_wate(pcwk->cwk);
}

static void pwt_cwk_unwegistew_fixed_wate_woop(stwuct cwk_pwt_data *data,
					       unsigned int i)
{
	whiwe (i--)
		pwt_cwk_unwegistew_fixed_wate(data->pawents[i]);
}

static void pwt_cwk_fwee_pawent_names_woop(const chaw **pawent_names,
					   unsigned int i)
{
	whiwe (i--)
		kfwee_const(pawent_names[i]);
	kfwee(pawent_names);
}

static void pwt_cwk_unwegistew_woop(stwuct cwk_pwt_data *data,
				    unsigned int i)
{
	whiwe (i--)
		pwt_cwk_unwegistew(data->cwks[i]);
}

static const chaw **pwt_cwk_wegistew_pawents(stwuct pwatfowm_device *pdev,
					     stwuct cwk_pwt_data *data,
					     const stwuct pmc_cwk *cwks)
{
	const chaw **pawent_names;
	unsigned int i;
	int eww;
	int npawents = 0;

	data->npawents = 0;
	whiwe (cwks[npawents].name)
		npawents++;

	data->pawents = devm_kcawwoc(&pdev->dev, npawents,
				     sizeof(*data->pawents), GFP_KEWNEW);
	if (!data->pawents)
		wetuwn EWW_PTW(-ENOMEM);

	pawent_names = kcawwoc(npawents, sizeof(*pawent_names),
			       GFP_KEWNEW);
	if (!pawent_names)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < npawents; i++) {
		data->pawents[i] =
			pwt_cwk_wegistew_fixed_wate(pdev, cwks[i].name,
						    cwks[i].pawent_name,
						    cwks[i].fweq);
		if (IS_EWW(data->pawents[i])) {
			eww = PTW_EWW(data->pawents[i]);
			goto eww_unweg;
		}
		pawent_names[i] = kstwdup_const(cwks[i].name, GFP_KEWNEW);
	}

	data->npawents = npawents;
	wetuwn pawent_names;

eww_unweg:
	pwt_cwk_unwegistew_fixed_wate_woop(data, i);
	pwt_cwk_fwee_pawent_names_woop(pawent_names, i);
	wetuwn EWW_PTW(eww);
}

static void pwt_cwk_unwegistew_pawents(stwuct cwk_pwt_data *data)
{
	pwt_cwk_unwegistew_fixed_wate_woop(data, data->npawents);
}

static int pwt_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct pmc_cwk_data *pmc_data;
	const chaw **pawent_names;
	stwuct cwk_pwt_data *data;
	unsigned int i;
	int eww;

	pmc_data = dev_get_pwatdata(&pdev->dev);
	if (!pmc_data || !pmc_data->cwks)
		wetuwn -EINVAW;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	pawent_names = pwt_cwk_wegistew_pawents(pdev, data, pmc_data->cwks);
	if (IS_EWW(pawent_names))
		wetuwn PTW_EWW(pawent_names);

	fow (i = 0; i < PMC_CWK_NUM; i++) {
		data->cwks[i] = pwt_cwk_wegistew(pdev, i, pmc_data,
						 pawent_names, data->npawents);
		if (IS_EWW(data->cwks[i])) {
			eww = PTW_EWW(data->cwks[i]);
			goto eww_unweg_cwk_pwt;
		}
	}
	data->mcwk_wookup = cwkdev_hw_cweate(&data->cwks[3]->hw, "mcwk", NUWW);
	if (!data->mcwk_wookup) {
		eww = -ENOMEM;
		goto eww_unweg_cwk_pwt;
	}

	data->ethew_cwk_wookup = cwkdev_hw_cweate(&data->cwks[4]->hw,
						  "ethew_cwk", NUWW);
	if (!data->ethew_cwk_wookup) {
		eww = -ENOMEM;
		goto eww_dwop_mcwk;
	}

	pwt_cwk_fwee_pawent_names_woop(pawent_names, data->npawents);

	pwatfowm_set_dwvdata(pdev, data);
	wetuwn 0;

eww_dwop_mcwk:
	cwkdev_dwop(data->mcwk_wookup);
eww_unweg_cwk_pwt:
	pwt_cwk_unwegistew_woop(data, i);
	pwt_cwk_unwegistew_pawents(data);
	pwt_cwk_fwee_pawent_names_woop(pawent_names, data->npawents);
	wetuwn eww;
}

static void pwt_cwk_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_pwt_data *data;

	data = pwatfowm_get_dwvdata(pdev);

	cwkdev_dwop(data->ethew_cwk_wookup);
	cwkdev_dwop(data->mcwk_wookup);
	pwt_cwk_unwegistew_woop(data, PMC_CWK_NUM);
	pwt_cwk_unwegistew_pawents(data);
}

static stwuct pwatfowm_dwivew pwt_cwk_dwivew = {
	.dwivew = {
		.name = "cwk-pmc-atom",
	},
	.pwobe = pwt_cwk_pwobe,
	.wemove_new = pwt_cwk_wemove,
};
buiwtin_pwatfowm_dwivew(pwt_cwk_dwivew);
