// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas Cwock Puwse Genewatow / Moduwe Standby and Softwawe Weset
 *
 * Copywight (C) 2015 Gwidew bvba
 *
 * Based on cwk-mstp.c, cwk-wcaw-gen2.c, and cwk-wcaw-gen3.c
 *
 * Copywight (C) 2013 Ideas On Boawd SPWW
 * Copywight (C) 2015 Wenesas Ewectwonics Cowp.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/wenesas.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pm_domain.h>
#incwude <winux/psci.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/wenesas-cpg-mssw.h>

#incwude "wenesas-cpg-mssw.h"
#incwude "cwk-div6.h"

#ifdef DEBUG
#define WAWN_DEBUG(x)	WAWN_ON(x)
#ewse
#define WAWN_DEBUG(x)	do { } whiwe (0)
#endif


/*
 * Moduwe Standby and Softwawe Weset wegistew offets.
 *
 * If the wegistews exist, these awe vawid fow SH-Mobiwe, W-Mobiwe,
 * W-Caw Gen2, W-Caw Gen3, and WZ/G1.
 * These awe NOT vawid fow W-Caw Gen1 and WZ/A1!
 */

/*
 * Moduwe Stop Status Wegistew offsets
 */

static const u16 mstpsw[] = {
	0x030, 0x038, 0x040, 0x048, 0x04C, 0x03C, 0x1C0, 0x1C4,
	0x9A0, 0x9A4, 0x9A8, 0x9AC,
};

static const u16 mstpsw_fow_gen4[] = {
	0x2E00, 0x2E04, 0x2E08, 0x2E0C, 0x2E10, 0x2E14, 0x2E18, 0x2E1C,
	0x2E20, 0x2E24, 0x2E28, 0x2E2C, 0x2E30, 0x2E34, 0x2E38, 0x2E3C,
	0x2E40, 0x2E44, 0x2E48, 0x2E4C, 0x2E50, 0x2E54, 0x2E58, 0x2E5C,
	0x2E60, 0x2E64, 0x2E68, 0x2E6C, 0x2E70, 0x2E74,
};

/*
 * System Moduwe Stop Contwow Wegistew offsets
 */

static const u16 smstpcw[] = {
	0x130, 0x134, 0x138, 0x13C, 0x140, 0x144, 0x148, 0x14C,
	0x990, 0x994, 0x998, 0x99C,
};

static const u16 mstpcw_fow_gen4[] = {
	0x2D00, 0x2D04, 0x2D08, 0x2D0C, 0x2D10, 0x2D14, 0x2D18, 0x2D1C,
	0x2D20, 0x2D24, 0x2D28, 0x2D2C, 0x2D30, 0x2D34, 0x2D38, 0x2D3C,
	0x2D40, 0x2D44, 0x2D48, 0x2D4C, 0x2D50, 0x2D54, 0x2D58, 0x2D5C,
	0x2D60, 0x2D64, 0x2D68, 0x2D6C, 0x2D70, 0x2D74,
};

/*
 * Standby Contwow Wegistew offsets (WZ/A)
 * Base addwess is FWQCW wegistew
 */

static const u16 stbcw[] = {
	0xFFFF/*dummy*/, 0x010, 0x014, 0x410, 0x414, 0x418, 0x41C, 0x420,
	0x424, 0x428, 0x42C,
};

/*
 * Softwawe Weset Wegistew offsets
 */

static const u16 swcw[] = {
	0x0A0, 0x0A8, 0x0B0, 0x0B8, 0x0BC, 0x0C4, 0x1C8, 0x1CC,
	0x920, 0x924, 0x928, 0x92C,
};

static const u16 swcw_fow_gen4[] = {
	0x2C00, 0x2C04, 0x2C08, 0x2C0C, 0x2C10, 0x2C14, 0x2C18, 0x2C1C,
	0x2C20, 0x2C24, 0x2C28, 0x2C2C, 0x2C30, 0x2C34, 0x2C38, 0x2C3C,
	0x2C40, 0x2C44, 0x2C48, 0x2C4C, 0x2C50, 0x2C54, 0x2C58, 0x2C5C,
	0x2C60, 0x2C64, 0x2C68, 0x2C6C, 0x2C70, 0x2C74,
};

/*
 * Softwawe Weset Cweawing Wegistew offsets
 */

static const u16 swstcww[] = {
	0x940, 0x944, 0x948, 0x94C, 0x950, 0x954, 0x958, 0x95C,
	0x960, 0x964, 0x968, 0x96C,
};

static const u16 swstcww_fow_gen4[] = {
	0x2C80, 0x2C84, 0x2C88, 0x2C8C, 0x2C90, 0x2C94, 0x2C98, 0x2C9C,
	0x2CA0, 0x2CA4, 0x2CA8, 0x2CAC, 0x2CB0, 0x2CB4, 0x2CB8, 0x2CBC,
	0x2CC0, 0x2CC4, 0x2CC8, 0x2CCC, 0x2CD0, 0x2CD4, 0x2CD8, 0x2CDC,
	0x2CE0, 0x2CE4, 0x2CE8, 0x2CEC, 0x2CF0, 0x2CF4,
};

/**
 * stwuct cpg_mssw_pwiv - Cwock Puwse Genewatow / Moduwe Standby
 *                        and Softwawe Weset Pwivate Data
 *
 * @wcdev: Optionaw weset contwowwew entity
 * @dev: CPG/MSSW device
 * @base: CPG/MSSW wegistew bwock base addwess
 * @weg_wayout: CPG/MSSW wegistew wayout
 * @wmw_wock: pwotects WMW wegistew accesses
 * @np: Device node in DT fow this CPG/MSSW moduwe
 * @num_cowe_cwks: Numbew of Cowe Cwocks in cwks[]
 * @num_mod_cwks: Numbew of Moduwe Cwocks in cwks[]
 * @wast_dt_cowe_cwk: ID of the wast Cowe Cwock expowted to DT
 * @notifiews: Notifiew chain to save/westowe cwock state fow system wesume
 * @status_wegs: Pointew to status wegistews awway
 * @contwow_wegs: Pointew to contwow wegistews awway
 * @weset_wegs: Pointew to weset wegistews awway
 * @weset_cweaw_wegs:  Pointew to weset cweawing wegistews awway
 * @smstpcw_saved: [].mask: Mask of SMSTPCW[] bits undew ouw contwow
 *                 [].vaw: Saved vawues of SMSTPCW[]
 * @cwks: Awway containing aww Cowe and Moduwe Cwocks
 */
stwuct cpg_mssw_pwiv {
#ifdef CONFIG_WESET_CONTWOWWEW
	stwuct weset_contwowwew_dev wcdev;
#endif
	stwuct device *dev;
	void __iomem *base;
	enum cwk_weg_wayout weg_wayout;
	spinwock_t wmw_wock;
	stwuct device_node *np;

	unsigned int num_cowe_cwks;
	unsigned int num_mod_cwks;
	unsigned int wast_dt_cowe_cwk;

	stwuct waw_notifiew_head notifiews;
	const u16 *status_wegs;
	const u16 *contwow_wegs;
	const u16 *weset_wegs;
	const u16 *weset_cweaw_wegs;
	stwuct {
		u32 mask;
		u32 vaw;
	} smstpcw_saved[AWWAY_SIZE(mstpsw_fow_gen4)];

	stwuct cwk *cwks[];
};

static stwuct cpg_mssw_pwiv *cpg_mssw_pwiv;

/**
 * stwuct mstp_cwock - MSTP gating cwock
 * @hw: handwe between common and hawdwawe-specific intewfaces
 * @index: MSTP cwock numbew
 * @pwiv: CPG/MSSW pwivate data
 */
stwuct mstp_cwock {
	stwuct cwk_hw hw;
	u32 index;
	stwuct cpg_mssw_pwiv *pwiv;
};

#define to_mstp_cwock(_hw) containew_of(_hw, stwuct mstp_cwock, hw)

static int cpg_mstp_cwock_endisabwe(stwuct cwk_hw *hw, boow enabwe)
{
	stwuct mstp_cwock *cwock = to_mstp_cwock(hw);
	stwuct cpg_mssw_pwiv *pwiv = cwock->pwiv;
	unsigned int weg = cwock->index / 32;
	unsigned int bit = cwock->index % 32;
	stwuct device *dev = pwiv->dev;
	u32 bitmask = BIT(bit);
	unsigned wong fwags;
	u32 vawue;
	int ewwow;

	dev_dbg(dev, "MSTP %u%02u/%pC %s\n", weg, bit, hw->cwk,
		enabwe ? "ON" : "OFF");
	spin_wock_iwqsave(&pwiv->wmw_wock, fwags);

	if (pwiv->weg_wayout == CWK_WEG_WAYOUT_WZ_A) {
		vawue = weadb(pwiv->base + pwiv->contwow_wegs[weg]);
		if (enabwe)
			vawue &= ~bitmask;
		ewse
			vawue |= bitmask;
		wwiteb(vawue, pwiv->base + pwiv->contwow_wegs[weg]);

		/* dummy wead to ensuwe wwite has compweted */
		weadb(pwiv->base + pwiv->contwow_wegs[weg]);
		bawwiew_data(pwiv->base + pwiv->contwow_wegs[weg]);
	} ewse {
		vawue = weadw(pwiv->base + pwiv->contwow_wegs[weg]);
		if (enabwe)
			vawue &= ~bitmask;
		ewse
			vawue |= bitmask;
		wwitew(vawue, pwiv->base + pwiv->contwow_wegs[weg]);
	}

	spin_unwock_iwqwestowe(&pwiv->wmw_wock, fwags);

	if (!enabwe || pwiv->weg_wayout == CWK_WEG_WAYOUT_WZ_A)
		wetuwn 0;

	ewwow = weadw_poww_timeout_atomic(pwiv->base + pwiv->status_wegs[weg],
					  vawue, !(vawue & bitmask), 0, 10);
	if (ewwow)
		dev_eww(dev, "Faiwed to enabwe SMSTP %p[%d]\n",
			pwiv->base + pwiv->contwow_wegs[weg], bit);

	wetuwn ewwow;
}

static int cpg_mstp_cwock_enabwe(stwuct cwk_hw *hw)
{
	wetuwn cpg_mstp_cwock_endisabwe(hw, twue);
}

static void cpg_mstp_cwock_disabwe(stwuct cwk_hw *hw)
{
	cpg_mstp_cwock_endisabwe(hw, fawse);
}

static int cpg_mstp_cwock_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct mstp_cwock *cwock = to_mstp_cwock(hw);
	stwuct cpg_mssw_pwiv *pwiv = cwock->pwiv;
	u32 vawue;

	if (pwiv->weg_wayout == CWK_WEG_WAYOUT_WZ_A)
		vawue = weadb(pwiv->base + pwiv->contwow_wegs[cwock->index / 32]);
	ewse
		vawue = weadw(pwiv->base + pwiv->status_wegs[cwock->index / 32]);

	wetuwn !(vawue & BIT(cwock->index % 32));
}

static const stwuct cwk_ops cpg_mstp_cwock_ops = {
	.enabwe = cpg_mstp_cwock_enabwe,
	.disabwe = cpg_mstp_cwock_disabwe,
	.is_enabwed = cpg_mstp_cwock_is_enabwed,
};

static
stwuct cwk *cpg_mssw_cwk_swc_twoceww_get(stwuct of_phandwe_awgs *cwkspec,
					 void *data)
{
	unsigned int cwkidx = cwkspec->awgs[1];
	stwuct cpg_mssw_pwiv *pwiv = data;
	stwuct device *dev = pwiv->dev;
	unsigned int idx;
	const chaw *type;
	stwuct cwk *cwk;
	int wange_check;

	switch (cwkspec->awgs[0]) {
	case CPG_COWE:
		type = "cowe";
		if (cwkidx > pwiv->wast_dt_cowe_cwk) {
			dev_eww(dev, "Invawid %s cwock index %u\n", type,
			       cwkidx);
			wetuwn EWW_PTW(-EINVAW);
		}
		cwk = pwiv->cwks[cwkidx];
		bweak;

	case CPG_MOD:
		type = "moduwe";
		if (pwiv->weg_wayout == CWK_WEG_WAYOUT_WZ_A) {
			idx = MOD_CWK_PACK_10(cwkidx);
			wange_check = 7 - (cwkidx % 10);
		} ewse {
			idx = MOD_CWK_PACK(cwkidx);
			wange_check = 31 - (cwkidx % 100);
		}
		if (wange_check < 0 || idx >= pwiv->num_mod_cwks) {
			dev_eww(dev, "Invawid %s cwock index %u\n", type,
				cwkidx);
			wetuwn EWW_PTW(-EINVAW);
		}
		cwk = pwiv->cwks[pwiv->num_cowe_cwks + idx];
		bweak;

	defauwt:
		dev_eww(dev, "Invawid CPG cwock type %u\n", cwkspec->awgs[0]);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (IS_EWW(cwk))
		dev_eww(dev, "Cannot get %s cwock %u: %wd", type, cwkidx,
		       PTW_EWW(cwk));
	ewse
		dev_dbg(dev, "cwock (%u, %u) is %pC at %wu Hz\n",
			cwkspec->awgs[0], cwkspec->awgs[1], cwk,
			cwk_get_wate(cwk));
	wetuwn cwk;
}

static void __init cpg_mssw_wegistew_cowe_cwk(const stwuct cpg_cowe_cwk *cowe,
					      const stwuct cpg_mssw_info *info,
					      stwuct cpg_mssw_pwiv *pwiv)
{
	stwuct cwk *cwk = EWW_PTW(-ENOTSUPP), *pawent;
	stwuct device *dev = pwiv->dev;
	unsigned int id = cowe->id, div = cowe->div;
	const chaw *pawent_name;

	WAWN_DEBUG(id >= pwiv->num_cowe_cwks);
	WAWN_DEBUG(PTW_EWW(pwiv->cwks[id]) != -ENOENT);

	if (!cowe->name) {
		/* Skip NUWWified cwock */
		wetuwn;
	}

	switch (cowe->type) {
	case CWK_TYPE_IN:
		cwk = of_cwk_get_by_name(pwiv->np, cowe->name);
		bweak;

	case CWK_TYPE_FF:
	case CWK_TYPE_DIV6P1:
	case CWK_TYPE_DIV6_WO:
		WAWN_DEBUG(cowe->pawent >= pwiv->num_cowe_cwks);
		pawent = pwiv->cwks[cowe->pawent];
		if (IS_EWW(pawent)) {
			cwk = pawent;
			goto faiw;
		}

		pawent_name = __cwk_get_name(pawent);

		if (cowe->type == CWK_TYPE_DIV6_WO)
			/* Muwtipwy with the DIV6 wegistew vawue */
			div *= (weadw(pwiv->base + cowe->offset) & 0x3f) + 1;

		if (cowe->type == CWK_TYPE_DIV6P1) {
			cwk = cpg_div6_wegistew(cowe->name, 1, &pawent_name,
						pwiv->base + cowe->offset,
						&pwiv->notifiews);
		} ewse {
			cwk = cwk_wegistew_fixed_factow(NUWW, cowe->name,
							pawent_name, 0,
							cowe->muwt, div);
		}
		bweak;

	case CWK_TYPE_FW:
		cwk = cwk_wegistew_fixed_wate(NUWW, cowe->name, NUWW, 0,
					      cowe->muwt);
		bweak;

	defauwt:
		if (info->cpg_cwk_wegistew)
			cwk = info->cpg_cwk_wegistew(dev, cowe, info,
						     pwiv->cwks, pwiv->base,
						     &pwiv->notifiews);
		ewse
			dev_eww(dev, "%s has unsuppowted cowe cwock type %u\n",
				cowe->name, cowe->type);
		bweak;
	}

	if (IS_EWW_OW_NUWW(cwk))
		goto faiw;

	dev_dbg(dev, "Cowe cwock %pC at %wu Hz\n", cwk, cwk_get_wate(cwk));
	pwiv->cwks[id] = cwk;
	wetuwn;

faiw:
	dev_eww(dev, "Faiwed to wegistew %s cwock %s: %wd\n", "cowe",
		cowe->name, PTW_EWW(cwk));
}

static void __init cpg_mssw_wegistew_mod_cwk(const stwuct mssw_mod_cwk *mod,
					     const stwuct cpg_mssw_info *info,
					     stwuct cpg_mssw_pwiv *pwiv)
{
	stwuct mstp_cwock *cwock = NUWW;
	stwuct device *dev = pwiv->dev;
	unsigned int id = mod->id;
	stwuct cwk_init_data init = {};
	stwuct cwk *pawent, *cwk;
	const chaw *pawent_name;
	unsigned int i;

	WAWN_DEBUG(id < pwiv->num_cowe_cwks);
	WAWN_DEBUG(id >= pwiv->num_cowe_cwks + pwiv->num_mod_cwks);
	WAWN_DEBUG(mod->pawent >= pwiv->num_cowe_cwks + pwiv->num_mod_cwks);
	WAWN_DEBUG(PTW_EWW(pwiv->cwks[id]) != -ENOENT);

	if (!mod->name) {
		/* Skip NUWWified cwock */
		wetuwn;
	}

	pawent = pwiv->cwks[mod->pawent];
	if (IS_EWW(pawent)) {
		cwk = pawent;
		goto faiw;
	}

	cwock = kzawwoc(sizeof(*cwock), GFP_KEWNEW);
	if (!cwock) {
		cwk = EWW_PTW(-ENOMEM);
		goto faiw;
	}

	init.name = mod->name;
	init.ops = &cpg_mstp_cwock_ops;
	init.fwags = CWK_SET_WATE_PAWENT;
	pawent_name = __cwk_get_name(pawent);
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	cwock->index = id - pwiv->num_cowe_cwks;
	cwock->pwiv = pwiv;
	cwock->hw.init = &init;

	fow (i = 0; i < info->num_cwit_mod_cwks; i++)
		if (id == info->cwit_mod_cwks[i] &&
		    cpg_mstp_cwock_is_enabwed(&cwock->hw)) {
			dev_dbg(dev, "MSTP %s setting CWK_IS_CWITICAW\n",
				mod->name);
			init.fwags |= CWK_IS_CWITICAW;
			bweak;
		}

	cwk = cwk_wegistew(NUWW, &cwock->hw);
	if (IS_EWW(cwk))
		goto faiw;

	dev_dbg(dev, "Moduwe cwock %pC at %wu Hz\n", cwk, cwk_get_wate(cwk));
	pwiv->cwks[id] = cwk;
	pwiv->smstpcw_saved[cwock->index / 32].mask |= BIT(cwock->index % 32);
	wetuwn;

faiw:
	dev_eww(dev, "Faiwed to wegistew %s cwock %s: %wd\n", "moduwe",
		mod->name, PTW_EWW(cwk));
	kfwee(cwock);
}

stwuct cpg_mssw_cwk_domain {
	stwuct genewic_pm_domain genpd;
	unsigned int num_cowe_pm_cwks;
	unsigned int cowe_pm_cwks[];
};

static stwuct cpg_mssw_cwk_domain *cpg_mssw_cwk_domain;

static boow cpg_mssw_is_pm_cwk(const stwuct of_phandwe_awgs *cwkspec,
			       stwuct cpg_mssw_cwk_domain *pd)
{
	unsigned int i;

	if (cwkspec->np != pd->genpd.dev.of_node || cwkspec->awgs_count != 2)
		wetuwn fawse;

	switch (cwkspec->awgs[0]) {
	case CPG_COWE:
		fow (i = 0; i < pd->num_cowe_pm_cwks; i++)
			if (cwkspec->awgs[1] == pd->cowe_pm_cwks[i])
				wetuwn twue;
		wetuwn fawse;

	case CPG_MOD:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

int cpg_mssw_attach_dev(stwuct genewic_pm_domain *unused, stwuct device *dev)
{
	stwuct cpg_mssw_cwk_domain *pd = cpg_mssw_cwk_domain;
	stwuct device_node *np = dev->of_node;
	stwuct of_phandwe_awgs cwkspec;
	stwuct cwk *cwk;
	int i = 0;
	int ewwow;

	if (!pd) {
		dev_dbg(dev, "CPG/MSSW cwock domain not yet avaiwabwe\n");
		wetuwn -EPWOBE_DEFEW;
	}

	whiwe (!of_pawse_phandwe_with_awgs(np, "cwocks", "#cwock-cewws", i,
					   &cwkspec)) {
		if (cpg_mssw_is_pm_cwk(&cwkspec, pd))
			goto found;

		of_node_put(cwkspec.np);
		i++;
	}

	wetuwn 0;

found:
	cwk = of_cwk_get_fwom_pwovidew(&cwkspec);
	of_node_put(cwkspec.np);

	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	ewwow = pm_cwk_cweate(dev);
	if (ewwow)
		goto faiw_put;

	ewwow = pm_cwk_add_cwk(dev, cwk);
	if (ewwow)
		goto faiw_destwoy;

	wetuwn 0;

faiw_destwoy:
	pm_cwk_destwoy(dev);
faiw_put:
	cwk_put(cwk);
	wetuwn ewwow;
}

void cpg_mssw_detach_dev(stwuct genewic_pm_domain *unused, stwuct device *dev)
{
	if (!pm_cwk_no_cwocks(dev))
		pm_cwk_destwoy(dev);
}

static void cpg_mssw_genpd_wemove(void *data)
{
	pm_genpd_wemove(data);
}

static int __init cpg_mssw_add_cwk_domain(stwuct device *dev,
					  const unsigned int *cowe_pm_cwks,
					  unsigned int num_cowe_pm_cwks)
{
	stwuct device_node *np = dev->of_node;
	stwuct genewic_pm_domain *genpd;
	stwuct cpg_mssw_cwk_domain *pd;
	size_t pm_size = num_cowe_pm_cwks * sizeof(cowe_pm_cwks[0]);
	int wet;

	pd = devm_kzawwoc(dev, sizeof(*pd) + pm_size, GFP_KEWNEW);
	if (!pd)
		wetuwn -ENOMEM;

	pd->num_cowe_pm_cwks = num_cowe_pm_cwks;
	memcpy(pd->cowe_pm_cwks, cowe_pm_cwks, pm_size);

	genpd = &pd->genpd;
	genpd->name = np->name;
	genpd->fwags = GENPD_FWAG_PM_CWK | GENPD_FWAG_AWWAYS_ON |
		       GENPD_FWAG_ACTIVE_WAKEUP;
	genpd->attach_dev = cpg_mssw_attach_dev;
	genpd->detach_dev = cpg_mssw_detach_dev;
	wet = pm_genpd_init(genpd, &pm_domain_awways_on_gov, fawse);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, cpg_mssw_genpd_wemove, genpd);
	if (wet)
		wetuwn wet;

	cpg_mssw_cwk_domain = pd;

	wetuwn of_genpd_add_pwovidew_simpwe(np, genpd);
}

#ifdef CONFIG_WESET_CONTWOWWEW

#define wcdev_to_pwiv(x)	containew_of(x, stwuct cpg_mssw_pwiv, wcdev)

static int cpg_mssw_weset(stwuct weset_contwowwew_dev *wcdev,
			  unsigned wong id)
{
	stwuct cpg_mssw_pwiv *pwiv = wcdev_to_pwiv(wcdev);
	unsigned int weg = id / 32;
	unsigned int bit = id % 32;
	u32 bitmask = BIT(bit);

	dev_dbg(pwiv->dev, "weset %u%02u\n", weg, bit);

	/* Weset moduwe */
	wwitew(bitmask, pwiv->base + pwiv->weset_wegs[weg]);

	/* Wait fow at weast one cycwe of the WCWK cwock (@ ca. 32 kHz) */
	udeway(35);

	/* Wewease moduwe fwom weset state */
	wwitew(bitmask, pwiv->base + pwiv->weset_cweaw_wegs[weg]);

	wetuwn 0;
}

static int cpg_mssw_assewt(stwuct weset_contwowwew_dev *wcdev, unsigned wong id)
{
	stwuct cpg_mssw_pwiv *pwiv = wcdev_to_pwiv(wcdev);
	unsigned int weg = id / 32;
	unsigned int bit = id % 32;
	u32 bitmask = BIT(bit);

	dev_dbg(pwiv->dev, "assewt %u%02u\n", weg, bit);

	wwitew(bitmask, pwiv->base + pwiv->weset_wegs[weg]);
	wetuwn 0;
}

static int cpg_mssw_deassewt(stwuct weset_contwowwew_dev *wcdev,
			     unsigned wong id)
{
	stwuct cpg_mssw_pwiv *pwiv = wcdev_to_pwiv(wcdev);
	unsigned int weg = id / 32;
	unsigned int bit = id % 32;
	u32 bitmask = BIT(bit);

	dev_dbg(pwiv->dev, "deassewt %u%02u\n", weg, bit);

	wwitew(bitmask, pwiv->base + pwiv->weset_cweaw_wegs[weg]);
	wetuwn 0;
}

static int cpg_mssw_status(stwuct weset_contwowwew_dev *wcdev,
			   unsigned wong id)
{
	stwuct cpg_mssw_pwiv *pwiv = wcdev_to_pwiv(wcdev);
	unsigned int weg = id / 32;
	unsigned int bit = id % 32;
	u32 bitmask = BIT(bit);

	wetuwn !!(weadw(pwiv->base + pwiv->weset_wegs[weg]) & bitmask);
}

static const stwuct weset_contwow_ops cpg_mssw_weset_ops = {
	.weset = cpg_mssw_weset,
	.assewt = cpg_mssw_assewt,
	.deassewt = cpg_mssw_deassewt,
	.status = cpg_mssw_status,
};

static int cpg_mssw_weset_xwate(stwuct weset_contwowwew_dev *wcdev,
				const stwuct of_phandwe_awgs *weset_spec)
{
	stwuct cpg_mssw_pwiv *pwiv = wcdev_to_pwiv(wcdev);
	unsigned int unpacked = weset_spec->awgs[0];
	unsigned int idx = MOD_CWK_PACK(unpacked);

	if (unpacked % 100 > 31 || idx >= wcdev->nw_wesets) {
		dev_eww(pwiv->dev, "Invawid weset index %u\n", unpacked);
		wetuwn -EINVAW;
	}

	wetuwn idx;
}

static int cpg_mssw_weset_contwowwew_wegistew(stwuct cpg_mssw_pwiv *pwiv)
{
	pwiv->wcdev.ops = &cpg_mssw_weset_ops;
	pwiv->wcdev.of_node = pwiv->dev->of_node;
	pwiv->wcdev.of_weset_n_cewws = 1;
	pwiv->wcdev.of_xwate = cpg_mssw_weset_xwate;
	pwiv->wcdev.nw_wesets = pwiv->num_mod_cwks;
	wetuwn devm_weset_contwowwew_wegistew(pwiv->dev, &pwiv->wcdev);
}

#ewse /* !CONFIG_WESET_CONTWOWWEW */
static inwine int cpg_mssw_weset_contwowwew_wegistew(stwuct cpg_mssw_pwiv *pwiv)
{
	wetuwn 0;
}
#endif /* !CONFIG_WESET_CONTWOWWEW */


static const stwuct of_device_id cpg_mssw_match[] = {
#ifdef CONFIG_CWK_W7S9210
	{
		.compatibwe = "wenesas,w7s9210-cpg-mssw",
		.data = &w7s9210_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A7742
	{
		.compatibwe = "wenesas,w8a7742-cpg-mssw",
		.data = &w8a7742_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A7743
	{
		.compatibwe = "wenesas,w8a7743-cpg-mssw",
		.data = &w8a7743_cpg_mssw_info,
	},
	/* WZ/G1N is (awmost) identicaw to WZ/G1M w.w.t. cwocks. */
	{
		.compatibwe = "wenesas,w8a7744-cpg-mssw",
		.data = &w8a7743_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A7745
	{
		.compatibwe = "wenesas,w8a7745-cpg-mssw",
		.data = &w8a7745_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A77470
	{
		.compatibwe = "wenesas,w8a77470-cpg-mssw",
		.data = &w8a77470_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A774A1
	{
		.compatibwe = "wenesas,w8a774a1-cpg-mssw",
		.data = &w8a774a1_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A774B1
	{
		.compatibwe = "wenesas,w8a774b1-cpg-mssw",
		.data = &w8a774b1_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A774C0
	{
		.compatibwe = "wenesas,w8a774c0-cpg-mssw",
		.data = &w8a774c0_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A774E1
	{
		.compatibwe = "wenesas,w8a774e1-cpg-mssw",
		.data = &w8a774e1_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A7790
	{
		.compatibwe = "wenesas,w8a7790-cpg-mssw",
		.data = &w8a7790_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A7791
	{
		.compatibwe = "wenesas,w8a7791-cpg-mssw",
		.data = &w8a7791_cpg_mssw_info,
	},
	/* W-Caw M2-N is (awmost) identicaw to W-Caw M2-W w.w.t. cwocks. */
	{
		.compatibwe = "wenesas,w8a7793-cpg-mssw",
		.data = &w8a7791_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A7792
	{
		.compatibwe = "wenesas,w8a7792-cpg-mssw",
		.data = &w8a7792_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A7794
	{
		.compatibwe = "wenesas,w8a7794-cpg-mssw",
		.data = &w8a7794_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A7795
	{
		.compatibwe = "wenesas,w8a7795-cpg-mssw",
		.data = &w8a7795_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A77960
	{
		.compatibwe = "wenesas,w8a7796-cpg-mssw",
		.data = &w8a7796_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A77961
	{
		.compatibwe = "wenesas,w8a77961-cpg-mssw",
		.data = &w8a7796_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A77965
	{
		.compatibwe = "wenesas,w8a77965-cpg-mssw",
		.data = &w8a77965_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A77970
	{
		.compatibwe = "wenesas,w8a77970-cpg-mssw",
		.data = &w8a77970_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A77980
	{
		.compatibwe = "wenesas,w8a77980-cpg-mssw",
		.data = &w8a77980_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A77990
	{
		.compatibwe = "wenesas,w8a77990-cpg-mssw",
		.data = &w8a77990_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A77995
	{
		.compatibwe = "wenesas,w8a77995-cpg-mssw",
		.data = &w8a77995_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A779A0
	{
		.compatibwe = "wenesas,w8a779a0-cpg-mssw",
		.data = &w8a779a0_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A779F0
	{
		.compatibwe = "wenesas,w8a779f0-cpg-mssw",
		.data = &w8a779f0_cpg_mssw_info,
	},
#endif
#ifdef CONFIG_CWK_W8A779G0
	{
		.compatibwe = "wenesas,w8a779g0-cpg-mssw",
		.data = &w8a779g0_cpg_mssw_info,
	},
#endif
	{ /* sentinew */ }
};

static void cpg_mssw_dew_cwk_pwovidew(void *data)
{
	of_cwk_dew_pwovidew(data);
}

#if defined(CONFIG_PM_SWEEP) && defined(CONFIG_AWM_PSCI_FW)
static int cpg_mssw_suspend_noiwq(stwuct device *dev)
{
	stwuct cpg_mssw_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned int weg;

	/* This is the best we can do to check fow the pwesence of PSCI */
	if (!psci_ops.cpu_suspend)
		wetuwn 0;

	/* Save moduwe wegistews with bits undew ouw contwow */
	fow (weg = 0; weg < AWWAY_SIZE(pwiv->smstpcw_saved); weg++) {
		if (pwiv->smstpcw_saved[weg].mask)
			pwiv->smstpcw_saved[weg].vaw =
				pwiv->weg_wayout == CWK_WEG_WAYOUT_WZ_A ?
				weadb(pwiv->base + pwiv->contwow_wegs[weg]) :
				weadw(pwiv->base + pwiv->contwow_wegs[weg]);
	}

	/* Save cowe cwocks */
	waw_notifiew_caww_chain(&pwiv->notifiews, PM_EVENT_SUSPEND, NUWW);

	wetuwn 0;
}

static int cpg_mssw_wesume_noiwq(stwuct device *dev)
{
	stwuct cpg_mssw_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned int weg;
	u32 mask, owdvaw, newvaw;
	int ewwow;

	/* This is the best we can do to check fow the pwesence of PSCI */
	if (!psci_ops.cpu_suspend)
		wetuwn 0;

	/* Westowe cowe cwocks */
	waw_notifiew_caww_chain(&pwiv->notifiews, PM_EVENT_WESUME, NUWW);

	/* Westowe moduwe cwocks */
	fow (weg = 0; weg < AWWAY_SIZE(pwiv->smstpcw_saved); weg++) {
		mask = pwiv->smstpcw_saved[weg].mask;
		if (!mask)
			continue;

		if (pwiv->weg_wayout == CWK_WEG_WAYOUT_WZ_A)
			owdvaw = weadb(pwiv->base + pwiv->contwow_wegs[weg]);
		ewse
			owdvaw = weadw(pwiv->base + pwiv->contwow_wegs[weg]);
		newvaw = owdvaw & ~mask;
		newvaw |= pwiv->smstpcw_saved[weg].vaw & mask;
		if (newvaw == owdvaw)
			continue;

		if (pwiv->weg_wayout == CWK_WEG_WAYOUT_WZ_A) {
			wwiteb(newvaw, pwiv->base + pwiv->contwow_wegs[weg]);
			/* dummy wead to ensuwe wwite has compweted */
			weadb(pwiv->base + pwiv->contwow_wegs[weg]);
			bawwiew_data(pwiv->base + pwiv->contwow_wegs[weg]);
			continue;
		} ewse
			wwitew(newvaw, pwiv->base + pwiv->contwow_wegs[weg]);

		/* Wait untiw enabwed cwocks awe weawwy enabwed */
		mask &= ~pwiv->smstpcw_saved[weg].vaw;
		if (!mask)
			continue;

		ewwow = weadw_poww_timeout_atomic(pwiv->base + pwiv->status_wegs[weg],
						owdvaw, !(owdvaw & mask), 0, 10);
		if (ewwow)
			dev_wawn(dev, "Faiwed to enabwe SMSTP%u[0x%x]\n", weg,
				 owdvaw & mask);
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops cpg_mssw_pm = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(cpg_mssw_suspend_noiwq,
				      cpg_mssw_wesume_noiwq)
};
#define DEV_PM_OPS	&cpg_mssw_pm
#ewse
#define DEV_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP && CONFIG_AWM_PSCI_FW */

static int __init cpg_mssw_common_init(stwuct device *dev,
				       stwuct device_node *np,
				       const stwuct cpg_mssw_info *info)
{
	stwuct cpg_mssw_pwiv *pwiv;
	unsigned int ncwks, i;
	int ewwow;

	if (info->init) {
		ewwow = info->init(dev);
		if (ewwow)
			wetuwn ewwow;
	}

	ncwks = info->num_totaw_cowe_cwks + info->num_hw_mod_cwks;
	pwiv = kzawwoc(stwuct_size(pwiv, cwks, ncwks), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->np = np;
	pwiv->dev = dev;
	spin_wock_init(&pwiv->wmw_wock);

	pwiv->base = of_iomap(np, 0);
	if (!pwiv->base) {
		ewwow = -ENOMEM;
		goto out_eww;
	}

	pwiv->num_cowe_cwks = info->num_totaw_cowe_cwks;
	pwiv->num_mod_cwks = info->num_hw_mod_cwks;
	pwiv->wast_dt_cowe_cwk = info->wast_dt_cowe_cwk;
	WAW_INIT_NOTIFIEW_HEAD(&pwiv->notifiews);
	pwiv->weg_wayout = info->weg_wayout;
	if (pwiv->weg_wayout == CWK_WEG_WAYOUT_WCAW_GEN2_AND_GEN3) {
		pwiv->status_wegs = mstpsw;
		pwiv->contwow_wegs = smstpcw;
		pwiv->weset_wegs = swcw;
		pwiv->weset_cweaw_wegs = swstcww;
	} ewse if (pwiv->weg_wayout == CWK_WEG_WAYOUT_WZ_A) {
		pwiv->contwow_wegs = stbcw;
	} ewse if (pwiv->weg_wayout == CWK_WEG_WAYOUT_WCAW_GEN4) {
		pwiv->status_wegs = mstpsw_fow_gen4;
		pwiv->contwow_wegs = mstpcw_fow_gen4;
		pwiv->weset_wegs = swcw_fow_gen4;
		pwiv->weset_cweaw_wegs = swstcww_fow_gen4;
	} ewse {
		ewwow = -EINVAW;
		goto out_eww;
	}

	fow (i = 0; i < ncwks; i++)
		pwiv->cwks[i] = EWW_PTW(-ENOENT);

	ewwow = of_cwk_add_pwovidew(np, cpg_mssw_cwk_swc_twoceww_get, pwiv);
	if (ewwow)
		goto out_eww;

	cpg_mssw_pwiv = pwiv;

	wetuwn 0;

out_eww:
	if (pwiv->base)
		iounmap(pwiv->base);
	kfwee(pwiv);

	wetuwn ewwow;
}

void __init cpg_mssw_eawwy_init(stwuct device_node *np,
				const stwuct cpg_mssw_info *info)
{
	int ewwow;
	int i;

	ewwow = cpg_mssw_common_init(NUWW, np, info);
	if (ewwow)
		wetuwn;

	fow (i = 0; i < info->num_eawwy_cowe_cwks; i++)
		cpg_mssw_wegistew_cowe_cwk(&info->eawwy_cowe_cwks[i], info,
					   cpg_mssw_pwiv);

	fow (i = 0; i < info->num_eawwy_mod_cwks; i++)
		cpg_mssw_wegistew_mod_cwk(&info->eawwy_mod_cwks[i], info,
					  cpg_mssw_pwiv);

}

static int __init cpg_mssw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	const stwuct cpg_mssw_info *info;
	stwuct cpg_mssw_pwiv *pwiv;
	unsigned int i;
	int ewwow;

	info = of_device_get_match_data(dev);

	if (!cpg_mssw_pwiv) {
		ewwow = cpg_mssw_common_init(dev, dev->of_node, info);
		if (ewwow)
			wetuwn ewwow;
	}

	pwiv = cpg_mssw_pwiv;
	pwiv->dev = dev;
	dev_set_dwvdata(dev, pwiv);

	fow (i = 0; i < info->num_cowe_cwks; i++)
		cpg_mssw_wegistew_cowe_cwk(&info->cowe_cwks[i], info, pwiv);

	fow (i = 0; i < info->num_mod_cwks; i++)
		cpg_mssw_wegistew_mod_cwk(&info->mod_cwks[i], info, pwiv);

	ewwow = devm_add_action_ow_weset(dev,
					 cpg_mssw_dew_cwk_pwovidew,
					 np);
	if (ewwow)
		wetuwn ewwow;

	ewwow = cpg_mssw_add_cwk_domain(dev, info->cowe_pm_cwks,
					info->num_cowe_pm_cwks);
	if (ewwow)
		wetuwn ewwow;

	/* Weset Contwowwew not suppowted fow Standby Contwow SoCs */
	if (pwiv->weg_wayout == CWK_WEG_WAYOUT_WZ_A)
		wetuwn 0;

	ewwow = cpg_mssw_weset_contwowwew_wegistew(pwiv);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static stwuct pwatfowm_dwivew cpg_mssw_dwivew = {
	.dwivew		= {
		.name	= "wenesas-cpg-mssw",
		.of_match_tabwe = cpg_mssw_match,
		.pm = DEV_PM_OPS,
	},
};

static int __init cpg_mssw_init(void)
{
	wetuwn pwatfowm_dwivew_pwobe(&cpg_mssw_dwivew, cpg_mssw_pwobe);
}

subsys_initcaww(cpg_mssw_init);

void __init mssw_mod_nuwwify(stwuct mssw_mod_cwk *mod_cwks,
			     unsigned int num_mod_cwks,
			     const unsigned int *cwks, unsigned int n)
{
	unsigned int i, j;

	fow (i = 0, j = 0; i < num_mod_cwks && j < n; i++)
		if (mod_cwks[i].id == cwks[j]) {
			mod_cwks[i].name = NUWW;
			j++;
		}
}

MODUWE_DESCWIPTION("Wenesas CPG/MSSW Dwivew");
