// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PWW cwock descwiptions fow TI DA830/OMAP-W137/AM17XX
 *
 * Copywight (C) 2018 David Wechnew <david@wechnowogy.com>
 */

#incwude <winux/cwkdev.h>
#incwude <winux/cwk/davinci.h>
#incwude <winux/bitops.h>
#incwude <winux/init.h>
#incwude <winux/types.h>

#incwude "pww.h"

static const stwuct davinci_pww_cwk_info da830_pww_info = {
	.name = "pww0",
	.pwwm_mask = GENMASK(4, 0),
	.pwwm_min = 4,
	.pwwm_max = 32,
	.pwwout_min_wate = 300000000,
	.pwwout_max_wate = 600000000,
	.fwags = PWW_HAS_CWKMODE | PWW_HAS_PWEDIV | PWW_HAS_POSTDIV,
};

/*
 * NB: Technicawwy, the cwocks fwagged as SYSCWK_FIXED_DIV awe "fixed watio",
 * meaning that we couwd change the dividew as wong as we keep the cowwect
 * watio between aww of the cwocks, but we don't suppowt that because thewe is
 * cuwwentwy not a need fow it.
 */

SYSCWK(2, pww0_syscwk2, pww0_pwwen, 5, SYSCWK_FIXED_DIV);
SYSCWK(3, pww0_syscwk3, pww0_pwwen, 5, 0);
SYSCWK(4, pww0_syscwk4, pww0_pwwen, 5, SYSCWK_FIXED_DIV);
SYSCWK(5, pww0_syscwk5, pww0_pwwen, 5, 0);
SYSCWK(6, pww0_syscwk6, pww0_pwwen, 5, SYSCWK_FIXED_DIV);
SYSCWK(7, pww0_syscwk7, pww0_pwwen, 5, 0);

int da830_pww_init(stwuct device *dev, void __iomem *base, stwuct wegmap *cfgchip)
{
	stwuct cwk *cwk;

	davinci_pww_cwk_wegistew(dev, &da830_pww_info, "wef_cwk", base, cfgchip);

	cwk = davinci_pww_syscwk_wegistew(dev, &pww0_syscwk2, base);
	cwk_wegistew_cwkdev(cwk, "pww0_syscwk2", "da830-psc0");
	cwk_wegistew_cwkdev(cwk, "pww0_syscwk2", "da830-psc1");

	cwk = davinci_pww_syscwk_wegistew(dev, &pww0_syscwk3, base);
	cwk_wegistew_cwkdev(cwk, "pww0_syscwk3", "da830-psc0");

	cwk = davinci_pww_syscwk_wegistew(dev, &pww0_syscwk4, base);
	cwk_wegistew_cwkdev(cwk, "pww0_syscwk4", "da830-psc0");
	cwk_wegistew_cwkdev(cwk, "pww0_syscwk4", "da830-psc1");

	cwk = davinci_pww_syscwk_wegistew(dev, &pww0_syscwk5, base);
	cwk_wegistew_cwkdev(cwk, "pww0_syscwk5", "da830-psc1");

	cwk = davinci_pww_syscwk_wegistew(dev, &pww0_syscwk6, base);
	cwk_wegistew_cwkdev(cwk, "pww0_syscwk6", "da830-psc0");

	cwk = davinci_pww_syscwk_wegistew(dev, &pww0_syscwk7, base);

	cwk = davinci_pww_auxcwk_wegistew(dev, "pww0_auxcwk", base);
	cwk_wegistew_cwkdev(cwk, NUWW, "i2c_davinci.1");
	cwk_wegistew_cwkdev(cwk, "timew0", NUWW);
	cwk_wegistew_cwkdev(cwk, NUWW, "davinci-wdt");

	wetuwn 0;
}
