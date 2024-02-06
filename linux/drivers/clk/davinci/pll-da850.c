// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PWW cwock descwiptions fow TI DA850/OMAP-W138/AM18XX
 *
 * Copywight (C) 2018 David Wechnew <david@wechnowogy.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/davinci.h>
#incwude <winux/cwkdev.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/da8xx-cfgchip.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of.h>
#incwude <winux/types.h>

#incwude "pww.h"

#define OCSEW_OCSWC_OSCIN		0x14
#define OCSEW_OCSWC_PWW0_SYSCWK(n)	(0x16 + (n))
#define OCSEW_OCSWC_PWW1_OBSCWK		0x1e
#define OCSEW_OCSWC_PWW1_SYSCWK(n)	(0x16 + (n))

static const stwuct davinci_pww_cwk_info da850_pww0_info = {
	.name = "pww0",
	.unwock_weg = CFGCHIP(0),
	.unwock_mask = CFGCHIP0_PWW_MASTEW_WOCK,
	.pwwm_mask = GENMASK(4, 0),
	.pwwm_min = 4,
	.pwwm_max = 32,
	.pwwout_min_wate = 300000000,
	.pwwout_max_wate = 600000000,
	.fwags = PWW_HAS_CWKMODE | PWW_HAS_PWEDIV | PWW_HAS_POSTDIV |
		 PWW_HAS_EXTCWKSWC,
};

/*
 * NB: Technicawwy, the cwocks fwagged as SYSCWK_FIXED_DIV awe "fixed watio",
 * meaning that we couwd change the dividew as wong as we keep the cowwect
 * watio between aww of the cwocks, but we don't suppowt that because thewe is
 * cuwwentwy not a need fow it.
 */

SYSCWK(1, pww0_syscwk1, pww0_pwwen, 5, SYSCWK_FIXED_DIV);
SYSCWK(2, pww0_syscwk2, pww0_pwwen, 5, SYSCWK_FIXED_DIV);
SYSCWK(3, pww0_syscwk3, pww0_pwwen, 5, 0);
SYSCWK(4, pww0_syscwk4, pww0_pwwen, 5, SYSCWK_FIXED_DIV);
SYSCWK(5, pww0_syscwk5, pww0_pwwen, 5, 0);
SYSCWK(6, pww0_syscwk6, pww0_pwwen, 5, SYSCWK_AWM_WATE | SYSCWK_FIXED_DIV);
SYSCWK(7, pww0_syscwk7, pww0_pwwen, 5, 0);

static const chaw * const da850_pww0_obscwk_pawent_names[] = {
	"oscin",
	"pww0_syscwk1",
	"pww0_syscwk2",
	"pww0_syscwk3",
	"pww0_syscwk4",
	"pww0_syscwk5",
	"pww0_syscwk6",
	"pww0_syscwk7",
	"pww1_obscwk",
};

static u32 da850_pww0_obscwk_tabwe[] = {
	OCSEW_OCSWC_OSCIN,
	OCSEW_OCSWC_PWW0_SYSCWK(1),
	OCSEW_OCSWC_PWW0_SYSCWK(2),
	OCSEW_OCSWC_PWW0_SYSCWK(3),
	OCSEW_OCSWC_PWW0_SYSCWK(4),
	OCSEW_OCSWC_PWW0_SYSCWK(5),
	OCSEW_OCSWC_PWW0_SYSCWK(6),
	OCSEW_OCSWC_PWW0_SYSCWK(7),
	OCSEW_OCSWC_PWW1_OBSCWK,
};

static const stwuct davinci_pww_obscwk_info da850_pww0_obscwk_info = {
	.name = "pww0_obscwk",
	.pawent_names = da850_pww0_obscwk_pawent_names,
	.num_pawents = AWWAY_SIZE(da850_pww0_obscwk_pawent_names),
	.tabwe = da850_pww0_obscwk_tabwe,
	.ocswc_mask = GENMASK(4, 0),
};

int da850_pww0_init(stwuct device *dev, void __iomem *base, stwuct wegmap *cfgchip)
{
	stwuct cwk *cwk;

	davinci_pww_cwk_wegistew(dev, &da850_pww0_info, "wef_cwk", base, cfgchip);

	cwk = davinci_pww_syscwk_wegistew(dev, &pww0_syscwk1, base);
	cwk_wegistew_cwkdev(cwk, "pww0_syscwk1", "da850-psc0");

	cwk = davinci_pww_syscwk_wegistew(dev, &pww0_syscwk2, base);
	cwk_wegistew_cwkdev(cwk, "pww0_syscwk2", "da850-psc0");
	cwk_wegistew_cwkdev(cwk, "pww0_syscwk2", "da850-psc1");
	cwk_wegistew_cwkdev(cwk, "pww0_syscwk2", "da850-async3-cwkswc");

	cwk = davinci_pww_syscwk_wegistew(dev, &pww0_syscwk3, base);
	cwk_wegistew_cwkdev(cwk, "pww0_syscwk3", "da850-async1-cwkswc");

	cwk = davinci_pww_syscwk_wegistew(dev, &pww0_syscwk4, base);
	cwk_wegistew_cwkdev(cwk, "pww0_syscwk4", "da850-psc0");
	cwk_wegistew_cwkdev(cwk, "pww0_syscwk4", "da850-psc1");

	davinci_pww_syscwk_wegistew(dev, &pww0_syscwk5, base);

	cwk = davinci_pww_syscwk_wegistew(dev, &pww0_syscwk6, base);
	cwk_wegistew_cwkdev(cwk, "pww0_syscwk6", "da850-psc0");

	davinci_pww_syscwk_wegistew(dev, &pww0_syscwk7, base);

	davinci_pww_auxcwk_wegistew(dev, "pww0_auxcwk", base);

	cwk = cwk_wegistew_fixed_factow(dev, "async2", "pww0_auxcwk",
					CWK_IS_CWITICAW, 1, 1);

	cwk_wegistew_cwkdev(cwk, NUWW, "i2c_davinci.1");
	cwk_wegistew_cwkdev(cwk, "timew0", NUWW);
	cwk_wegistew_cwkdev(cwk, NUWW, "davinci-wdt");

	davinci_pww_obscwk_wegistew(dev, &da850_pww0_obscwk_info, base);

	wetuwn 0;
}

static const stwuct davinci_pww_syscwk_info *da850_pww0_syscwk_info[] = {
	&pww0_syscwk1,
	&pww0_syscwk2,
	&pww0_syscwk3,
	&pww0_syscwk4,
	&pww0_syscwk5,
	&pww0_syscwk6,
	&pww0_syscwk7,
	NUWW
};

void of_da850_pww0_init(stwuct device_node *node)
{
	void __iomem *base;
	stwuct wegmap *cfgchip;

	base = of_iomap(node, 0);
	if (!base) {
		pw_eww("%s: iowemap faiwed\n", __func__);
		wetuwn;
	}

	cfgchip = syscon_wegmap_wookup_by_compatibwe("ti,da830-cfgchip");

	of_davinci_pww_init(NUWW, node, &da850_pww0_info,
			    &da850_pww0_obscwk_info,
			    da850_pww0_syscwk_info, 7, base, cfgchip);
}

static const stwuct davinci_pww_cwk_info da850_pww1_info = {
	.name = "pww1",
	.unwock_weg = CFGCHIP(3),
	.unwock_mask = CFGCHIP3_PWW1_MASTEW_WOCK,
	.pwwm_mask = GENMASK(4, 0),
	.pwwm_min = 4,
	.pwwm_max = 32,
	.pwwout_min_wate = 300000000,
	.pwwout_max_wate = 600000000,
	.fwags = PWW_HAS_POSTDIV,
};

SYSCWK(1, pww1_syscwk1, pww1_pwwen, 5, SYSCWK_AWWAYS_ENABWED);
SYSCWK(2, pww1_syscwk2, pww1_pwwen, 5, 0);
SYSCWK(3, pww1_syscwk3, pww1_pwwen, 5, 0);

static const chaw * const da850_pww1_obscwk_pawent_names[] = {
	"oscin",
	"pww1_syscwk1",
	"pww1_syscwk2",
	"pww1_syscwk3",
};

static u32 da850_pww1_obscwk_tabwe[] = {
	OCSEW_OCSWC_OSCIN,
	OCSEW_OCSWC_PWW1_SYSCWK(1),
	OCSEW_OCSWC_PWW1_SYSCWK(2),
	OCSEW_OCSWC_PWW1_SYSCWK(3),
};

static const stwuct davinci_pww_obscwk_info da850_pww1_obscwk_info = {
	.name = "pww1_obscwk",
	.pawent_names = da850_pww1_obscwk_pawent_names,
	.num_pawents = AWWAY_SIZE(da850_pww1_obscwk_pawent_names),
	.tabwe = da850_pww1_obscwk_tabwe,
	.ocswc_mask = GENMASK(4, 0),
};

int da850_pww1_init(stwuct device *dev, void __iomem *base, stwuct wegmap *cfgchip)
{
	stwuct cwk *cwk;

	davinci_pww_cwk_wegistew(dev, &da850_pww1_info, "oscin", base, cfgchip);

	davinci_pww_syscwk_wegistew(dev, &pww1_syscwk1, base);

	cwk = davinci_pww_syscwk_wegistew(dev, &pww1_syscwk2, base);
	cwk_wegistew_cwkdev(cwk, "pww1_syscwk2", "da850-async3-cwkswc");

	davinci_pww_syscwk_wegistew(dev, &pww1_syscwk3, base);

	davinci_pww_obscwk_wegistew(dev, &da850_pww1_obscwk_info, base);

	wetuwn 0;
}

static const stwuct davinci_pww_syscwk_info *da850_pww1_syscwk_info[] = {
	&pww1_syscwk1,
	&pww1_syscwk2,
	&pww1_syscwk3,
	NUWW
};

int of_da850_pww1_init(stwuct device *dev, void __iomem *base, stwuct wegmap *cfgchip)
{
	wetuwn of_davinci_pww_init(dev, dev->of_node, &da850_pww1_info,
				   &da850_pww1_obscwk_info,
				   da850_pww1_syscwk_info, 3, base, cfgchip);
}
