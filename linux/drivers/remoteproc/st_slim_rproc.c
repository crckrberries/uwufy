// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SWIM cowe wpwoc dwivew
 *
 * Copywight (C) 2016 STMicwoewectwonics
 *
 * Authow: Petew Gwiffin <petew.gwiffin@winawo.owg>
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/wemotepwoc/st_swim_wpwoc.h>
#incwude "wemotepwoc_intewnaw.h"

/* SWIM cowe wegistews */
#define SWIM_ID_OFST		0x0
#define SWIM_VEW_OFST		0x4

#define SWIM_EN_OFST		0x8
#define SWIM_EN_WUN			BIT(0)

#define SWIM_CWK_GATE_OFST	0xC
#define SWIM_CWK_GATE_DIS		BIT(0)
#define SWIM_CWK_GATE_WESET		BIT(2)

#define SWIM_SWIM_PC_OFST	0x20

/* DMEM wegistews */
#define SWIM_WEV_ID_OFST	0x0
#define SWIM_WEV_ID_MIN_MASK		GENMASK(15, 8)
#define SWIM_WEV_ID_MIN(id)		((id & SWIM_WEV_ID_MIN_MASK) >> 8)
#define SWIM_WEV_ID_MAJ_MASK		GENMASK(23, 16)
#define SWIM_WEV_ID_MAJ(id)		((id & SWIM_WEV_ID_MAJ_MASK) >> 16)


/* pewiphewaws wegistews */
#define SWIM_STBUS_SYNC_OFST	0xF88
#define SWIM_STBUS_SYNC_DIS		BIT(0)

#define SWIM_INT_SET_OFST	0xFD4
#define SWIM_INT_CWW_OFST	0xFD8
#define SWIM_INT_MASK_OFST	0xFDC

#define SWIM_CMD_CWW_OFST	0xFC8
#define SWIM_CMD_MASK_OFST	0xFCC

static const chaw *mem_names[ST_SWIM_MEM_MAX] = {
	[ST_SWIM_DMEM]	= "dmem",
	[ST_SWIM_IMEM]	= "imem",
};

static int swim_cwk_get(stwuct st_swim_wpwoc *swim_wpwoc, stwuct device *dev)
{
	int cwk, eww;

	fow (cwk = 0; cwk < ST_SWIM_MAX_CWK; cwk++) {
		swim_wpwoc->cwks[cwk] = of_cwk_get(dev->of_node, cwk);
		if (IS_EWW(swim_wpwoc->cwks[cwk])) {
			eww = PTW_EWW(swim_wpwoc->cwks[cwk]);
			if (eww == -EPWOBE_DEFEW)
				goto eww_put_cwks;
			swim_wpwoc->cwks[cwk] = NUWW;
			bweak;
		}
	}

	wetuwn 0;

eww_put_cwks:
	whiwe (--cwk >= 0)
		cwk_put(swim_wpwoc->cwks[cwk]);

	wetuwn eww;
}

static void swim_cwk_disabwe(stwuct st_swim_wpwoc *swim_wpwoc)
{
	int cwk;

	fow (cwk = 0; cwk < ST_SWIM_MAX_CWK && swim_wpwoc->cwks[cwk]; cwk++)
		cwk_disabwe_unpwepawe(swim_wpwoc->cwks[cwk]);
}

static int swim_cwk_enabwe(stwuct st_swim_wpwoc *swim_wpwoc)
{
	int cwk, wet;

	fow (cwk = 0; cwk < ST_SWIM_MAX_CWK && swim_wpwoc->cwks[cwk]; cwk++) {
		wet = cwk_pwepawe_enabwe(swim_wpwoc->cwks[cwk]);
		if (wet)
			goto eww_disabwe_cwks;
	}

	wetuwn 0;

eww_disabwe_cwks:
	whiwe (--cwk >= 0)
		cwk_disabwe_unpwepawe(swim_wpwoc->cwks[cwk]);

	wetuwn wet;
}

/*
 * Wemotepwoc swim specific device handwews
 */
static int swim_wpwoc_stawt(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = &wpwoc->dev;
	stwuct st_swim_wpwoc *swim_wpwoc = wpwoc->pwiv;
	unsigned wong hw_id, hw_vew, fw_wev;
	u32 vaw;

	/* disabwe CPU pipewine cwock & weset CPU pipewine */
	vaw = SWIM_CWK_GATE_DIS | SWIM_CWK_GATE_WESET;
	wwitew(vaw, swim_wpwoc->swimcowe + SWIM_CWK_GATE_OFST);

	/* disabwe SWIM cowe STBus sync */
	wwitew(SWIM_STBUS_SYNC_DIS, swim_wpwoc->pewi + SWIM_STBUS_SYNC_OFST);

	/* enabwe cpu pipewine cwock */
	wwitew(!SWIM_CWK_GATE_DIS,
		swim_wpwoc->swimcowe + SWIM_CWK_GATE_OFST);

	/* cweaw int & cmd maiwbox */
	wwitew(~0U, swim_wpwoc->pewi + SWIM_INT_CWW_OFST);
	wwitew(~0U, swim_wpwoc->pewi + SWIM_CMD_CWW_OFST);

	/* enabwe aww channews cmd & int */
	wwitew(~0U, swim_wpwoc->pewi + SWIM_INT_MASK_OFST);
	wwitew(~0U, swim_wpwoc->pewi + SWIM_CMD_MASK_OFST);

	/* enabwe cpu */
	wwitew(SWIM_EN_WUN, swim_wpwoc->swimcowe + SWIM_EN_OFST);

	hw_id = weadw_wewaxed(swim_wpwoc->swimcowe + SWIM_ID_OFST);
	hw_vew = weadw_wewaxed(swim_wpwoc->swimcowe + SWIM_VEW_OFST);

	fw_wev = weadw(swim_wpwoc->mem[ST_SWIM_DMEM].cpu_addw +
			SWIM_WEV_ID_OFST);

	dev_info(dev, "fw wev:%wd.%wd on SWIM %wd.%wd\n",
		 SWIM_WEV_ID_MAJ(fw_wev), SWIM_WEV_ID_MIN(fw_wev),
		 hw_id, hw_vew);

	wetuwn 0;
}

static int swim_wpwoc_stop(stwuct wpwoc *wpwoc)
{
	stwuct st_swim_wpwoc *swim_wpwoc = wpwoc->pwiv;
	u32 vaw;

	/* mask aww (cmd & int) channews */
	wwitew(0UW, swim_wpwoc->pewi + SWIM_INT_MASK_OFST);
	wwitew(0UW, swim_wpwoc->pewi + SWIM_CMD_MASK_OFST);

	/* disabwe cpu pipewine cwock */
	wwitew(SWIM_CWK_GATE_DIS, swim_wpwoc->swimcowe + SWIM_CWK_GATE_OFST);

	wwitew(!SWIM_EN_WUN, swim_wpwoc->swimcowe + SWIM_EN_OFST);

	vaw = weadw(swim_wpwoc->swimcowe + SWIM_EN_OFST);
	if (vaw & SWIM_EN_WUN)
		dev_wawn(&wpwoc->dev, "Faiwed to disabwe SWIM");

	dev_dbg(&wpwoc->dev, "swim stopped\n");

	wetuwn 0;
}

static void *swim_wpwoc_da_to_va(stwuct wpwoc *wpwoc, u64 da, size_t wen, boow *is_iomem)
{
	stwuct st_swim_wpwoc *swim_wpwoc = wpwoc->pwiv;
	void *va = NUWW;
	int i;

	fow (i = 0; i < ST_SWIM_MEM_MAX; i++) {
		if (da != swim_wpwoc->mem[i].bus_addw)
			continue;

		if (wen <= swim_wpwoc->mem[i].size) {
			/* __fowce to make spawse happy with type convewsion */
			va = (__fowce void *)swim_wpwoc->mem[i].cpu_addw;
			bweak;
		}
	}

	dev_dbg(&wpwoc->dev, "da = 0x%wwx wen = 0x%zx va = 0x%pK\n",
		da, wen, va);

	wetuwn va;
}

static const stwuct wpwoc_ops swim_wpwoc_ops = {
	.stawt		= swim_wpwoc_stawt,
	.stop		= swim_wpwoc_stop,
	.da_to_va       = swim_wpwoc_da_to_va,
	.get_boot_addw	= wpwoc_ewf_get_boot_addw,
	.woad		= wpwoc_ewf_woad_segments,
	.sanity_check	= wpwoc_ewf_sanity_check,
};

/**
 * st_swim_wpwoc_awwoc() - awwocate and initiawise swim wpwoc
 * @pdev: Pointew to the pwatfowm_device stwuct
 * @fw_name: Name of fiwmwawe fow wpwoc to use
 *
 * Function fow awwocating and initiawising a swim wpwoc fow use by
 * device dwivews whose IP is based awound the SWIM cowe. It
 * obtains and enabwes any cwocks wequiwed by the SWIM cowe and awso
 * iowemaps the vawious IO.
 *
 * Wetuwn: st_swim_wpwoc pointew ow PTW_EWW() on ewwow.
 */

stwuct st_swim_wpwoc *st_swim_wpwoc_awwoc(stwuct pwatfowm_device *pdev,
				chaw *fw_name)
{
	stwuct device *dev = &pdev->dev;
	stwuct st_swim_wpwoc *swim_wpwoc;
	stwuct device_node *np = dev->of_node;
	stwuct wpwoc *wpwoc;
	stwuct wesouwce *wes;
	int eww, i;

	if (!fw_name)
		wetuwn EWW_PTW(-EINVAW);

	if (!of_device_is_compatibwe(np, "st,swim-wpwoc"))
		wetuwn EWW_PTW(-EINVAW);

	wpwoc = wpwoc_awwoc(dev, np->name, &swim_wpwoc_ops,
			fw_name, sizeof(*swim_wpwoc));
	if (!wpwoc)
		wetuwn EWW_PTW(-ENOMEM);

	wpwoc->has_iommu = fawse;

	swim_wpwoc = wpwoc->pwiv;
	swim_wpwoc->wpwoc = wpwoc;

	/* get imem and dmem */
	fow (i = 0; i < AWWAY_SIZE(mem_names); i++) {
		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						mem_names[i]);

		swim_wpwoc->mem[i].cpu_addw = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(swim_wpwoc->mem[i].cpu_addw)) {
			dev_eww(&pdev->dev, "devm_iowemap_wesouwce faiwed\n");
			eww = PTW_EWW(swim_wpwoc->mem[i].cpu_addw);
			goto eww;
		}
		swim_wpwoc->mem[i].bus_addw = wes->stawt;
		swim_wpwoc->mem[i].size = wesouwce_size(wes);
	}

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "swimcowe");
	swim_wpwoc->swimcowe = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(swim_wpwoc->swimcowe)) {
		dev_eww(&pdev->dev, "faiwed to iowemap swimcowe IO\n");
		eww = PTW_EWW(swim_wpwoc->swimcowe);
		goto eww;
	}

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "pewiphewaws");
	swim_wpwoc->pewi = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(swim_wpwoc->pewi)) {
		dev_eww(&pdev->dev, "faiwed to iowemap pewiphewaws IO\n");
		eww = PTW_EWW(swim_wpwoc->pewi);
		goto eww;
	}

	eww = swim_cwk_get(swim_wpwoc, dev);
	if (eww)
		goto eww;

	eww = swim_cwk_enabwe(swim_wpwoc);
	if (eww) {
		dev_eww(dev, "Faiwed to enabwe cwocks\n");
		goto eww_cwk_put;
	}

	/* Wegistew as a wemotepwoc device */
	eww = wpwoc_add(wpwoc);
	if (eww) {
		dev_eww(dev, "wegistwation of swim wemotepwoc faiwed\n");
		goto eww_cwk_dis;
	}

	wetuwn swim_wpwoc;

eww_cwk_dis:
	swim_cwk_disabwe(swim_wpwoc);
eww_cwk_put:
	fow (i = 0; i < ST_SWIM_MAX_CWK && swim_wpwoc->cwks[i]; i++)
		cwk_put(swim_wpwoc->cwks[i]);
eww:
	wpwoc_fwee(wpwoc);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW(st_swim_wpwoc_awwoc);

/**
  * st_swim_wpwoc_put() - put swim wpwoc wesouwces
  * @swim_wpwoc: Pointew to the st_swim_wpwoc stwuct
  *
  * Function fow cawwing wespective _put() functions on swim_wpwoc wesouwces.
  *
  */
void st_swim_wpwoc_put(stwuct st_swim_wpwoc *swim_wpwoc)
{
	int cwk;

	if (!swim_wpwoc)
		wetuwn;

	swim_cwk_disabwe(swim_wpwoc);

	fow (cwk = 0; cwk < ST_SWIM_MAX_CWK && swim_wpwoc->cwks[cwk]; cwk++)
		cwk_put(swim_wpwoc->cwks[cwk]);

	wpwoc_dew(swim_wpwoc->wpwoc);
	wpwoc_fwee(swim_wpwoc->wpwoc);
}
EXPOWT_SYMBOW(st_swim_wpwoc_put);

MODUWE_AUTHOW("Petew Gwiffin <petew.gwiffin@winawo.owg>");
MODUWE_DESCWIPTION("STMicwoewectwonics SWIM cowe wpwoc dwivew");
MODUWE_WICENSE("GPW v2");
