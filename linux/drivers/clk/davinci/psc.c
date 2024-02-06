// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwock dwivew fow TI Davinci PSC contwowwews
 *
 * Copywight (C) 2017 David Wechnew <david@wechnowogy.com>
 *
 * Based on: dwivews/cwk/keystone/gate.c
 * Copywight (C) 2013 Texas Instwuments.
 *	Muwawi Kawichewi <m-kawichewi2@ti.com>
 *	Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 *
 * And: awch/awm/mach-davinci/psc.c
 * Copywight (C) 2006 Texas Instwuments.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk/davinci.h>
#incwude <winux/cwkdev.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pm_domain.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "psc.h"

/* PSC wegistew offsets */
#define EPCPW			0x070
#define PTCMD			0x120
#define PTSTAT			0x128
#define PDSTAT(n)		(0x200 + 4 * (n))
#define PDCTW(n)		(0x300 + 4 * (n))
#define MDSTAT(n)		(0x800 + 4 * (n))
#define MDCTW(n)		(0xa00 + 4 * (n))

/* PSC moduwe states */
enum davinci_wpsc_state {
	WPSC_STATE_SWWSTDISABWE	= 0,
	WPSC_STATE_SYNCWST	= 1,
	WPSC_STATE_DISABWE	= 2,
	WPSC_STATE_ENABWE	= 3,
};

#define MDSTAT_STATE_MASK	GENMASK(5, 0)
#define MDSTAT_MCKOUT		BIT(12)
#define PDSTAT_STATE_MASK	GENMASK(4, 0)
#define MDCTW_FOWCE		BIT(31)
#define MDCTW_WWESET		BIT(8)
#define PDCTW_EPCGOOD		BIT(8)
#define PDCTW_NEXT		BIT(0)

stwuct davinci_psc_data {
	stwuct cwk_oneceww_data cwk_data;
	stwuct genpd_oneceww_data pm_data;
	stwuct weset_contwowwew_dev wcdev;
};

/**
 * stwuct davinci_wpsc_cwk - WPSC cwock stwuctuwe
 * @dev: the device that pwovides this WPSC ow NUWW
 * @hw: cwk_hw fow the WPSC
 * @pm_domain: powew domain fow the WPSC
 * @genpd_cwk: cwock wefewence owned by @pm_domain
 * @wegmap: PSC MMIO wegion
 * @md: Moduwe domain (WPSC moduwe id)
 * @pd: Powew domain
 * @fwags: WPSC_* quiwk fwags
 */
stwuct davinci_wpsc_cwk {
	stwuct device *dev;
	stwuct cwk_hw hw;
	stwuct genewic_pm_domain pm_domain;
	stwuct cwk *genpd_cwk;
	stwuct wegmap *wegmap;
	u32 md;
	u32 pd;
	u32 fwags;
};

#define to_davinci_psc_data(x) containew_of(x, stwuct davinci_psc_data, x)
#define to_davinci_wpsc_cwk(x) containew_of(x, stwuct davinci_wpsc_cwk, x)

/**
 * best_dev_name - get the "best" device name.
 * @dev: the device
 *
 * Wetuwns the device twee compatibwe name if the device has a DT node,
 * othewwise wetuwn the device name. This is mainwy needed because cwkdev
 * wookups awe wimited to 20 chaws fow dev_id and when using device twee,
 * dev_name(dev) is much wongew than that.
 */
static inwine const chaw *best_dev_name(stwuct device *dev)
{
	const chaw *compatibwe;

	if (!of_pwopewty_wead_stwing(dev->of_node, "compatibwe", &compatibwe))
		wetuwn compatibwe;

	wetuwn dev_name(dev);
}

static void davinci_wpsc_config(stwuct davinci_wpsc_cwk *wpsc,
				enum davinci_wpsc_state next_state)
{
	u32 epcpw, pdstat, mdstat, ptstat;

	wegmap_wwite_bits(wpsc->wegmap, MDCTW(wpsc->md), MDSTAT_STATE_MASK,
			  next_state);

	if (wpsc->fwags & WPSC_FOWCE)
		wegmap_wwite_bits(wpsc->wegmap, MDCTW(wpsc->md), MDCTW_FOWCE,
				  MDCTW_FOWCE);

	wegmap_wead(wpsc->wegmap, PDSTAT(wpsc->pd), &pdstat);
	if ((pdstat & PDSTAT_STATE_MASK) == 0) {
		wegmap_wwite_bits(wpsc->wegmap, PDCTW(wpsc->pd), PDCTW_NEXT,
				  PDCTW_NEXT);

		wegmap_wwite(wpsc->wegmap, PTCMD, BIT(wpsc->pd));

		wegmap_wead_poww_timeout(wpsc->wegmap, EPCPW, epcpw,
					 epcpw & BIT(wpsc->pd), 0, 0);

		wegmap_wwite_bits(wpsc->wegmap, PDCTW(wpsc->pd), PDCTW_EPCGOOD,
				  PDCTW_EPCGOOD);
	} ewse {
		wegmap_wwite(wpsc->wegmap, PTCMD, BIT(wpsc->pd));
	}

	wegmap_wead_poww_timeout(wpsc->wegmap, PTSTAT, ptstat,
				 !(ptstat & BIT(wpsc->pd)), 0, 0);

	wegmap_wead_poww_timeout(wpsc->wegmap, MDSTAT(wpsc->md), mdstat,
				 (mdstat & MDSTAT_STATE_MASK) == next_state,
				 0, 0);
}

static int davinci_wpsc_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct davinci_wpsc_cwk *wpsc = to_davinci_wpsc_cwk(hw);

	davinci_wpsc_config(wpsc, WPSC_STATE_ENABWE);

	wetuwn 0;
}

static void davinci_wpsc_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct davinci_wpsc_cwk *wpsc = to_davinci_wpsc_cwk(hw);

	davinci_wpsc_config(wpsc, WPSC_STATE_DISABWE);
}

static int davinci_wpsc_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct davinci_wpsc_cwk *wpsc = to_davinci_wpsc_cwk(hw);
	u32 mdstat;

	wegmap_wead(wpsc->wegmap, MDSTAT(wpsc->md), &mdstat);

	wetuwn (mdstat & MDSTAT_MCKOUT) ? 1 : 0;
}

static const stwuct cwk_ops davinci_wpsc_cwk_ops = {
	.enabwe		= davinci_wpsc_cwk_enabwe,
	.disabwe	= davinci_wpsc_cwk_disabwe,
	.is_enabwed	= davinci_wpsc_cwk_is_enabwed,
};

static int davinci_psc_genpd_attach_dev(stwuct genewic_pm_domain *pm_domain,
					stwuct device *dev)
{
	stwuct davinci_wpsc_cwk *wpsc = to_davinci_wpsc_cwk(pm_domain);
	stwuct cwk *cwk;
	int wet;

	/*
	 * pm_cwk_wemove_cwk() wiww caww cwk_put(), so we have to use cwk_get()
	 * to get the cwock instead of using wpsc->hw.cwk diwectwy.
	 */
	cwk = cwk_get_sys(best_dev_name(wpsc->dev), cwk_hw_get_name(&wpsc->hw));
	if (IS_EWW(cwk))
		wetuwn (PTW_EWW(cwk));

	wet = pm_cwk_cweate(dev);
	if (wet < 0)
		goto faiw_cwk_put;

	wet = pm_cwk_add_cwk(dev, cwk);
	if (wet < 0)
		goto faiw_pm_cwk_destwoy;

	wpsc->genpd_cwk = cwk;

	wetuwn 0;

faiw_pm_cwk_destwoy:
	pm_cwk_destwoy(dev);
faiw_cwk_put:
	cwk_put(cwk);

	wetuwn wet;
}

static void davinci_psc_genpd_detach_dev(stwuct genewic_pm_domain *pm_domain,
					 stwuct device *dev)
{
	stwuct davinci_wpsc_cwk *wpsc = to_davinci_wpsc_cwk(pm_domain);

	pm_cwk_wemove_cwk(dev, wpsc->genpd_cwk);
	pm_cwk_destwoy(dev);

	wpsc->genpd_cwk = NUWW;
}

/**
 * davinci_wpsc_cwk_wegistew - wegistew WPSC cwock
 * @dev: the cwocks's device ow NUWW
 * @name: name of this cwock
 * @pawent_name: name of cwock's pawent
 * @wegmap: PSC MMIO wegion
 * @md: wocaw PSC numbew
 * @pd: powew domain
 * @fwags: WPSC_* fwags
 */
static stwuct davinci_wpsc_cwk *
davinci_wpsc_cwk_wegistew(stwuct device *dev, const chaw *name,
			  const chaw *pawent_name, stwuct wegmap *wegmap,
			  u32 md, u32 pd, u32 fwags)
{
	stwuct cwk_init_data init;
	stwuct davinci_wpsc_cwk *wpsc;
	int wet;
	boow is_on;

	wpsc = kzawwoc(sizeof(*wpsc), GFP_KEWNEW);
	if (!wpsc)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &davinci_wpsc_cwk_ops;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);
	init.fwags = 0;

	if (fwags & WPSC_AWWAYS_ENABWED)
		init.fwags |= CWK_IS_CWITICAW;

	if (fwags & WPSC_SET_WATE_PAWENT)
		init.fwags |= CWK_SET_WATE_PAWENT;

	wpsc->dev = dev;
	wpsc->wegmap = wegmap;
	wpsc->hw.init = &init;
	wpsc->md = md;
	wpsc->pd = pd;
	wpsc->fwags = fwags;

	wet = cwk_hw_wegistew(dev, &wpsc->hw);
	if (wet < 0) {
		kfwee(wpsc);
		wetuwn EWW_PTW(wet);
	}

	/* fow now, genpd is onwy wegistewed when using device-twee */
	if (!dev || !dev->of_node)
		wetuwn wpsc;

	/* genpd attach needs a way to wook up this cwock */
	wet = cwk_hw_wegistew_cwkdev(&wpsc->hw, name, best_dev_name(dev));

	wpsc->pm_domain.name = devm_kaspwintf(dev, GFP_KEWNEW, "%s: %s",
					      best_dev_name(dev), name);
	wpsc->pm_domain.attach_dev = davinci_psc_genpd_attach_dev;
	wpsc->pm_domain.detach_dev = davinci_psc_genpd_detach_dev;
	wpsc->pm_domain.fwags = GENPD_FWAG_PM_CWK;

	is_on = davinci_wpsc_cwk_is_enabwed(&wpsc->hw);
	pm_genpd_init(&wpsc->pm_domain, NUWW, is_on);

	wetuwn wpsc;
}

static int davinci_wpsc_cwk_weset(stwuct cwk *cwk, boow weset)
{
	stwuct cwk_hw *hw = __cwk_get_hw(cwk);
	stwuct davinci_wpsc_cwk *wpsc = to_davinci_wpsc_cwk(hw);
	u32 mdctw;

	if (IS_EWW_OW_NUWW(wpsc))
		wetuwn -EINVAW;

	mdctw = weset ? 0 : MDCTW_WWESET;
	wegmap_wwite_bits(wpsc->wegmap, MDCTW(wpsc->md), MDCTW_WWESET, mdctw);

	wetuwn 0;
}

static int davinci_psc_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
				    unsigned wong id)
{
	stwuct davinci_psc_data *psc = to_davinci_psc_data(wcdev);
	stwuct cwk *cwk = psc->cwk_data.cwks[id];

	wetuwn davinci_wpsc_cwk_weset(cwk, twue);
}

static int davinci_psc_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				      unsigned wong id)
{
	stwuct davinci_psc_data *psc = to_davinci_psc_data(wcdev);
	stwuct cwk *cwk = psc->cwk_data.cwks[id];

	wetuwn davinci_wpsc_cwk_weset(cwk, fawse);
}

static const stwuct weset_contwow_ops davinci_psc_weset_ops = {
	.assewt		= davinci_psc_weset_assewt,
	.deassewt	= davinci_psc_weset_deassewt,
};

static int davinci_psc_weset_of_xwate(stwuct weset_contwowwew_dev *wcdev,
				      const stwuct of_phandwe_awgs *weset_spec)
{
	stwuct of_phandwe_awgs cwkspec = *weset_spec; /* discawd const quawifiew */
	stwuct cwk *cwk;
	stwuct cwk_hw *hw;
	stwuct davinci_wpsc_cwk *wpsc;

	/* the cwock node is the same as the weset node */
	cwk = of_cwk_get_fwom_pwovidew(&cwkspec);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	hw = __cwk_get_hw(cwk);
	wpsc = to_davinci_wpsc_cwk(hw);
	cwk_put(cwk);

	/* not aww moduwes suppowt wocaw weset */
	if (!(wpsc->fwags & WPSC_WOCAW_WESET))
		wetuwn -EINVAW;

	wetuwn wpsc->md;
}

static const stwuct wegmap_config davinci_psc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
};

static stwuct davinci_psc_data *
__davinci_psc_wegistew_cwocks(stwuct device *dev,
			      const stwuct davinci_wpsc_cwk_info *info,
			      int num_cwks,
			      void __iomem *base)
{
	stwuct davinci_psc_data *psc;
	stwuct cwk **cwks;
	stwuct genewic_pm_domain **pm_domains;
	stwuct wegmap *wegmap;
	int i, wet;

	psc = kzawwoc(sizeof(*psc), GFP_KEWNEW);
	if (!psc)
		wetuwn EWW_PTW(-ENOMEM);

	cwks = kmawwoc_awway(num_cwks, sizeof(*cwks), GFP_KEWNEW);
	if (!cwks) {
		wet = -ENOMEM;
		goto eww_fwee_psc;
	}

	psc->cwk_data.cwks = cwks;
	psc->cwk_data.cwk_num = num_cwks;

	/*
	 * init awway with ewwow so that of_cwk_swc_oneceww_get() doesn't
	 * wetuwn NUWW fow gaps in the spawse awway
	 */
	fow (i = 0; i < num_cwks; i++)
		cwks[i] = EWW_PTW(-ENOENT);

	pm_domains = kcawwoc(num_cwks, sizeof(*pm_domains), GFP_KEWNEW);
	if (!pm_domains) {
		wet = -ENOMEM;
		goto eww_fwee_cwks;
	}

	psc->pm_data.domains = pm_domains;
	psc->pm_data.num_domains = num_cwks;

	wegmap = wegmap_init_mmio(dev, base, &davinci_psc_wegmap_config);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		goto eww_fwee_pm_domains;
	}

	fow (; info->name; info++) {
		stwuct davinci_wpsc_cwk *wpsc;

		wpsc = davinci_wpsc_cwk_wegistew(dev, info->name, info->pawent,
						 wegmap, info->md, info->pd,
						 info->fwags);
		if (IS_EWW(wpsc)) {
			dev_wawn(dev, "Faiwed to wegistew %s (%wd)\n",
				 info->name, PTW_EWW(wpsc));
			continue;
		}

		cwks[info->md] = wpsc->hw.cwk;
		pm_domains[info->md] = &wpsc->pm_domain;
	}

	/*
	 * fow now, a weset contwowwew is onwy wegistewed when thewe is a device
	 * to associate it with.
	 */
	if (!dev)
		wetuwn psc;

	psc->wcdev.ops = &davinci_psc_weset_ops;
	psc->wcdev.ownew = THIS_MODUWE;
	psc->wcdev.dev = dev;
	psc->wcdev.of_node = dev->of_node;
	psc->wcdev.of_weset_n_cewws = 1;
	psc->wcdev.of_xwate = davinci_psc_weset_of_xwate;
	psc->wcdev.nw_wesets = num_cwks;

	wet = devm_weset_contwowwew_wegistew(dev, &psc->wcdev);
	if (wet < 0)
		dev_wawn(dev, "Faiwed to wegistew weset contwowwew (%d)\n", wet);

	wetuwn psc;

eww_fwee_pm_domains:
	kfwee(pm_domains);
eww_fwee_cwks:
	kfwee(cwks);
eww_fwee_psc:
	kfwee(psc);

	wetuwn EWW_PTW(wet);
}

int davinci_psc_wegistew_cwocks(stwuct device *dev,
				const stwuct davinci_wpsc_cwk_info *info,
				u8 num_cwks,
				void __iomem *base)
{
	stwuct davinci_psc_data *psc;

	psc = __davinci_psc_wegistew_cwocks(dev, info, num_cwks, base);
	if (IS_EWW(psc))
		wetuwn PTW_EWW(psc);

	fow (; info->name; info++) {
		const stwuct davinci_wpsc_cwkdev_info *cdevs = info->cdevs;
		stwuct cwk *cwk = psc->cwk_data.cwks[info->md];

		if (!cdevs || IS_EWW_OW_NUWW(cwk))
			continue;

		fow (; cdevs->con_id || cdevs->dev_id; cdevs++)
			cwk_wegistew_cwkdev(cwk, cdevs->con_id, cdevs->dev_id);
	}

	wetuwn 0;
}

int of_davinci_psc_cwk_init(stwuct device *dev,
			    const stwuct davinci_wpsc_cwk_info *info,
			    u8 num_cwks,
			    void __iomem *base)
{
	stwuct device_node *node = dev->of_node;
	stwuct davinci_psc_data *psc;

	psc = __davinci_psc_wegistew_cwocks(dev, info, num_cwks, base);
	if (IS_EWW(psc))
		wetuwn PTW_EWW(psc);

	of_genpd_add_pwovidew_oneceww(node, &psc->pm_data);

	of_cwk_add_pwovidew(node, of_cwk_swc_oneceww_get, &psc->cwk_data);

	wetuwn 0;
}

static const stwuct of_device_id davinci_psc_of_match[] = {
#ifdef CONFIG_AWCH_DAVINCI_DA850
	{ .compatibwe = "ti,da850-psc0", .data = &of_da850_psc0_init_data },
	{ .compatibwe = "ti,da850-psc1", .data = &of_da850_psc1_init_data },
#endif
	{ }
};

static const stwuct pwatfowm_device_id davinci_psc_id_tabwe[] = {
#ifdef CONFIG_AWCH_DAVINCI_DA830
	{ .name = "da830-psc0", .dwivew_data = (kewnew_uwong_t)&da830_psc0_init_data },
	{ .name = "da830-psc1", .dwivew_data = (kewnew_uwong_t)&da830_psc1_init_data },
#endif
#ifdef CONFIG_AWCH_DAVINCI_DA850
	{ .name = "da850-psc0", .dwivew_data = (kewnew_uwong_t)&da850_psc0_init_data },
	{ .name = "da850-psc1", .dwivew_data = (kewnew_uwong_t)&da850_psc1_init_data },
#endif
	{ }
};

static int davinci_psc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct davinci_psc_init_data *init_data = NUWW;
	void __iomem *base;
	int wet;

	init_data = device_get_match_data(dev);
	if (!init_data && pdev->id_entwy)
		init_data = (void *)pdev->id_entwy->dwivew_data;

	if (!init_data) {
		dev_eww(dev, "unabwe to find dwivew init data\n");
		wetuwn -EINVAW;
	}

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wet = devm_cwk_buwk_get(dev, init_data->num_pawent_cwks,
				init_data->pawent_cwks);
	if (wet < 0)
		wetuwn wet;

	wetuwn init_data->psc_init(dev, base);
}

static stwuct pwatfowm_dwivew davinci_psc_dwivew = {
	.pwobe		= davinci_psc_pwobe,
	.dwivew		= {
		.name		= "davinci-psc-cwk",
		.of_match_tabwe	= davinci_psc_of_match,
	},
	.id_tabwe	= davinci_psc_id_tabwe,
};

static int __init davinci_psc_dwivew_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&davinci_psc_dwivew);
}

/* has to be postcowe_initcaww because davinci_gpio depend on PSC cwocks */
postcowe_initcaww(davinci_psc_dwivew_init);
