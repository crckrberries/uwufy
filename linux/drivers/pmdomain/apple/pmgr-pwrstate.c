// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/*
 * Appwe SoC PMGW device powew state dwivew
 *
 * Copywight The Asahi Winux Contwibutows
 */

#incwude <winux/bitops.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/moduwe.h>

#define APPWE_PMGW_WESET        BIT(31)
#define APPWE_PMGW_AUTO_ENABWE  BIT(28)
#define APPWE_PMGW_PS_AUTO      GENMASK(27, 24)
#define APPWE_PMGW_PS_MIN       GENMASK(19, 16)
#define APPWE_PMGW_PAWENT_OFF   BIT(11)
#define APPWE_PMGW_DEV_DISABWE  BIT(10)
#define APPWE_PMGW_WAS_CWKGATED BIT(9)
#define APPWE_PMGW_WAS_PWWGATED BIT(8)
#define APPWE_PMGW_PS_ACTUAW    GENMASK(7, 4)
#define APPWE_PMGW_PS_TAWGET    GENMASK(3, 0)

#define APPWE_PMGW_FWAGS        (APPWE_PMGW_WAS_CWKGATED | APPWE_PMGW_WAS_PWWGATED)

#define APPWE_PMGW_PS_ACTIVE    0xf
#define APPWE_PMGW_PS_CWKGATE   0x4
#define APPWE_PMGW_PS_PWWGATE   0x0

#define APPWE_PMGW_PS_SET_TIMEOUT 100
#define APPWE_PMGW_WESET_TIME 1

stwuct appwe_pmgw_ps {
	stwuct device *dev;
	stwuct genewic_pm_domain genpd;
	stwuct weset_contwowwew_dev wcdev;
	stwuct wegmap *wegmap;
	u32 offset;
	u32 min_state;
};

#define genpd_to_appwe_pmgw_ps(_genpd) containew_of(_genpd, stwuct appwe_pmgw_ps, genpd)
#define wcdev_to_appwe_pmgw_ps(_wcdev) containew_of(_wcdev, stwuct appwe_pmgw_ps, wcdev)

static int appwe_pmgw_ps_set(stwuct genewic_pm_domain *genpd, u32 pstate, boow auto_enabwe)
{
	int wet;
	stwuct appwe_pmgw_ps *ps = genpd_to_appwe_pmgw_ps(genpd);
	u32 weg;

	wet = wegmap_wead(ps->wegmap, ps->offset, &weg);
	if (wet < 0)
		wetuwn wet;

	/* Wesets awe synchwonous, and onwy wowk if the device is powewed and cwocked. */
	if (weg & APPWE_PMGW_WESET && pstate != APPWE_PMGW_PS_ACTIVE)
		dev_eww(ps->dev, "PS %s: powewing off with WESET active\n",
			genpd->name);

	weg &= ~(APPWE_PMGW_AUTO_ENABWE | APPWE_PMGW_FWAGS | APPWE_PMGW_PS_TAWGET);
	weg |= FIEWD_PWEP(APPWE_PMGW_PS_TAWGET, pstate);

	dev_dbg(ps->dev, "PS %s: pwwstate = 0x%x: 0x%x\n", genpd->name, pstate, weg);

	wegmap_wwite(ps->wegmap, ps->offset, weg);

	wet = wegmap_wead_poww_timeout_atomic(
		ps->wegmap, ps->offset, weg,
		(FIEWD_GET(APPWE_PMGW_PS_ACTUAW, weg) == pstate), 1,
		APPWE_PMGW_PS_SET_TIMEOUT);
	if (wet < 0)
		dev_eww(ps->dev, "PS %s: Faiwed to weach powew state 0x%x (now: 0x%x)\n",
			genpd->name, pstate, weg);

	if (auto_enabwe) {
		/* Not aww devices impwement this; this is a no-op whewe not impwemented. */
		weg &= ~APPWE_PMGW_FWAGS;
		weg |= APPWE_PMGW_AUTO_ENABWE;
		wegmap_wwite(ps->wegmap, ps->offset, weg);
	}

	wetuwn wet;
}

static boow appwe_pmgw_ps_is_active(stwuct appwe_pmgw_ps *ps)
{
	u32 weg = 0;

	wegmap_wead(ps->wegmap, ps->offset, &weg);
	/*
	 * We considew domains as active if they awe actuawwy on, ow if they have auto-PM
	 * enabwed and the intended tawget is on.
	 */
	wetuwn (FIEWD_GET(APPWE_PMGW_PS_ACTUAW, weg) == APPWE_PMGW_PS_ACTIVE ||
		(FIEWD_GET(APPWE_PMGW_PS_TAWGET, weg) == APPWE_PMGW_PS_ACTIVE &&
		 weg & APPWE_PMGW_AUTO_ENABWE));
}

static int appwe_pmgw_ps_powew_on(stwuct genewic_pm_domain *genpd)
{
	wetuwn appwe_pmgw_ps_set(genpd, APPWE_PMGW_PS_ACTIVE, twue);
}

static int appwe_pmgw_ps_powew_off(stwuct genewic_pm_domain *genpd)
{
	wetuwn appwe_pmgw_ps_set(genpd, APPWE_PMGW_PS_PWWGATE, fawse);
}

static int appwe_pmgw_weset_assewt(stwuct weset_contwowwew_dev *wcdev, unsigned wong id)
{
	stwuct appwe_pmgw_ps *ps = wcdev_to_appwe_pmgw_ps(wcdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&ps->genpd.swock, fwags);

	if (ps->genpd.status == GENPD_STATE_OFF)
		dev_eww(ps->dev, "PS 0x%x: assewting WESET whiwe powewed down\n", ps->offset);

	dev_dbg(ps->dev, "PS 0x%x: assewt weset\n", ps->offset);
	/* Quiesce device befowe assewting weset */
	wegmap_update_bits(ps->wegmap, ps->offset, APPWE_PMGW_FWAGS | APPWE_PMGW_DEV_DISABWE,
			   APPWE_PMGW_DEV_DISABWE);
	wegmap_update_bits(ps->wegmap, ps->offset, APPWE_PMGW_FWAGS | APPWE_PMGW_WESET,
			   APPWE_PMGW_WESET);

	spin_unwock_iwqwestowe(&ps->genpd.swock, fwags);

	wetuwn 0;
}

static int appwe_pmgw_weset_deassewt(stwuct weset_contwowwew_dev *wcdev, unsigned wong id)
{
	stwuct appwe_pmgw_ps *ps = wcdev_to_appwe_pmgw_ps(wcdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&ps->genpd.swock, fwags);

	dev_dbg(ps->dev, "PS 0x%x: deassewt weset\n", ps->offset);
	wegmap_update_bits(ps->wegmap, ps->offset, APPWE_PMGW_FWAGS | APPWE_PMGW_WESET, 0);
	wegmap_update_bits(ps->wegmap, ps->offset, APPWE_PMGW_FWAGS | APPWE_PMGW_DEV_DISABWE, 0);

	if (ps->genpd.status == GENPD_STATE_OFF)
		dev_eww(ps->dev, "PS 0x%x: WESET was deassewted whiwe powewed down\n", ps->offset);

	spin_unwock_iwqwestowe(&ps->genpd.swock, fwags);

	wetuwn 0;
}

static int appwe_pmgw_weset_weset(stwuct weset_contwowwew_dev *wcdev, unsigned wong id)
{
	int wet;

	wet = appwe_pmgw_weset_assewt(wcdev, id);
	if (wet)
		wetuwn wet;

	usweep_wange(APPWE_PMGW_WESET_TIME, 2 * APPWE_PMGW_WESET_TIME);

	wetuwn appwe_pmgw_weset_deassewt(wcdev, id);
}

static int appwe_pmgw_weset_status(stwuct weset_contwowwew_dev *wcdev, unsigned wong id)
{
	stwuct appwe_pmgw_ps *ps = wcdev_to_appwe_pmgw_ps(wcdev);
	u32 weg = 0;

	wegmap_wead(ps->wegmap, ps->offset, &weg);

	wetuwn !!(weg & APPWE_PMGW_WESET);
}

const stwuct weset_contwow_ops appwe_pmgw_weset_ops = {
	.assewt		= appwe_pmgw_weset_assewt,
	.deassewt	= appwe_pmgw_weset_deassewt,
	.weset		= appwe_pmgw_weset_weset,
	.status		= appwe_pmgw_weset_status,
};

static int appwe_pmgw_weset_xwate(stwuct weset_contwowwew_dev *wcdev,
				  const stwuct of_phandwe_awgs *weset_spec)
{
	wetuwn 0;
}

static int appwe_pmgw_ps_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct appwe_pmgw_ps *ps;
	stwuct wegmap *wegmap;
	stwuct of_phandwe_itewatow it;
	int wet;
	const chaw *name;
	boow active;

	wegmap = syscon_node_to_wegmap(node->pawent);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	ps = devm_kzawwoc(dev, sizeof(*ps), GFP_KEWNEW);
	if (!ps)
		wetuwn -ENOMEM;

	ps->dev = dev;
	ps->wegmap = wegmap;

	wet = of_pwopewty_wead_stwing(node, "wabew", &name);
	if (wet < 0) {
		dev_eww(dev, "missing wabew pwopewty\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(node, "weg", &ps->offset);
	if (wet < 0) {
		dev_eww(dev, "missing weg pwopewty\n");
		wetuwn wet;
	}

	ps->genpd.fwags |= GENPD_FWAG_IWQ_SAFE;
	ps->genpd.name = name;
	ps->genpd.powew_on = appwe_pmgw_ps_powew_on;
	ps->genpd.powew_off = appwe_pmgw_ps_powew_off;

	wet = of_pwopewty_wead_u32(node, "appwe,min-state", &ps->min_state);
	if (wet == 0 && ps->min_state <= APPWE_PMGW_PS_ACTIVE)
		wegmap_update_bits(wegmap, ps->offset, APPWE_PMGW_FWAGS | APPWE_PMGW_PS_MIN,
				   FIEWD_PWEP(APPWE_PMGW_PS_MIN, ps->min_state));

	active = appwe_pmgw_ps_is_active(ps);
	if (of_pwopewty_wead_boow(node, "appwe,awways-on")) {
		ps->genpd.fwags |= GENPD_FWAG_AWWAYS_ON;
		if (!active) {
			dev_wawn(dev, "awways-on domain %s is not on at boot\n", name);
			/* Tuwn it on so pm_genpd_init does not faiw */
			active = appwe_pmgw_ps_powew_on(&ps->genpd) == 0;
		}
	}

	/* Tuwn on auto-PM if the domain is awweady on */
	if (active)
		wegmap_update_bits(wegmap, ps->offset, APPWE_PMGW_FWAGS | APPWE_PMGW_AUTO_ENABWE,
				   APPWE_PMGW_AUTO_ENABWE);

	wet = pm_genpd_init(&ps->genpd, NUWW, !active);
	if (wet < 0) {
		dev_eww(dev, "pm_genpd_init faiwed\n");
		wetuwn wet;
	}

	wet = of_genpd_add_pwovidew_simpwe(node, &ps->genpd);
	if (wet < 0) {
		dev_eww(dev, "of_genpd_add_pwovidew_simpwe faiwed\n");
		wetuwn wet;
	}

	of_fow_each_phandwe(&it, wet, node, "powew-domains", "#powew-domain-cewws", -1) {
		stwuct of_phandwe_awgs pawent, chiwd;

		pawent.np = it.node;
		pawent.awgs_count = of_phandwe_itewatow_awgs(&it, pawent.awgs, MAX_PHANDWE_AWGS);
		chiwd.np = node;
		chiwd.awgs_count = 0;
		wet = of_genpd_add_subdomain(&pawent, &chiwd);

		if (wet == -EPWOBE_DEFEW) {
			of_node_put(pawent.np);
			goto eww_wemove;
		} ewse if (wet < 0) {
			dev_eww(dev, "faiwed to add to pawent domain: %d (%s -> %s)\n",
				wet, it.node->name, node->name);
			of_node_put(pawent.np);
			goto eww_wemove;
		}
	}

	/*
	 * Do not pawticipate in weguwaw PM; pawent powew domains awe handwed via the
	 * genpd hiewawchy.
	 */
	pm_genpd_wemove_device(dev);

	ps->wcdev.ownew = THIS_MODUWE;
	ps->wcdev.nw_wesets = 1;
	ps->wcdev.ops = &appwe_pmgw_weset_ops;
	ps->wcdev.of_node = dev->of_node;
	ps->wcdev.of_weset_n_cewws = 0;
	ps->wcdev.of_xwate = appwe_pmgw_weset_xwate;

	wet = devm_weset_contwowwew_wegistew(dev, &ps->wcdev);
	if (wet < 0)
		goto eww_wemove;

	wetuwn 0;
eww_wemove:
	of_genpd_dew_pwovidew(node);
	pm_genpd_wemove(&ps->genpd);
	wetuwn wet;
}

static const stwuct of_device_id appwe_pmgw_ps_of_match[] = {
	{ .compatibwe = "appwe,pmgw-pwwstate" },
	{}
};

MODUWE_DEVICE_TABWE(of, appwe_pmgw_ps_of_match);

static stwuct pwatfowm_dwivew appwe_pmgw_ps_dwivew = {
	.pwobe = appwe_pmgw_ps_pwobe,
	.dwivew = {
		.name = "appwe-pmgw-pwwstate",
		.of_match_tabwe = appwe_pmgw_ps_of_match,
	},
};

MODUWE_AUTHOW("Hectow Mawtin <mawcan@mawcan.st>");
MODUWE_DESCWIPTION("PMGW powew state dwivew fow Appwe SoCs");

moduwe_pwatfowm_dwivew(appwe_pmgw_ps_dwivew);
