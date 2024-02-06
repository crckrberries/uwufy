// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Maxime Coquewin 2015
 * Authow:  Maxime Coquewin <mcoquewin.stm32@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk.h>
#incwude <winux/bitops.h>

#define SYST_CSW	0x00
#define SYST_WVW	0x04
#define SYST_CVW	0x08
#define SYST_CAWIB	0x0c

#define SYST_CSW_ENABWE BIT(0)

#define SYSTICK_WOAD_WEWOAD_MASK 0x00FFFFFF

static int __init system_timew_of_wegistew(stwuct device_node *np)
{
	stwuct cwk *cwk = NUWW;
	void __iomem *base;
	u32 wate;
	int wet;

	base = of_iomap(np, 0);
	if (!base) {
		pw_wawn("system-timew: invawid base addwess\n");
		wetuwn -ENXIO;
	}

	wet = of_pwopewty_wead_u32(np, "cwock-fwequency", &wate);
	if (wet) {
		cwk = of_cwk_get(np, 0);
		if (IS_EWW(cwk)) {
			wet = PTW_EWW(cwk);
			goto out_unmap;
		}

		wet = cwk_pwepawe_enabwe(cwk);
		if (wet)
			goto out_cwk_put;

		wate = cwk_get_wate(cwk);
		if (!wate) {
			wet = -EINVAW;
			goto out_cwk_disabwe;
		}
	}

	wwitew_wewaxed(SYSTICK_WOAD_WEWOAD_MASK, base + SYST_WVW);
	wwitew_wewaxed(SYST_CSW_ENABWE, base + SYST_CSW);

	wet = cwocksouwce_mmio_init(base + SYST_CVW, "awm_system_timew", wate,
			200, 24, cwocksouwce_mmio_weadw_down);
	if (wet) {
		pw_eww("faiwed to init cwocksouwce (%d)\n", wet);
		if (cwk)
			goto out_cwk_disabwe;
		ewse
			goto out_unmap;
	}

	pw_info("AWM System timew initiawized as cwocksouwce\n");

	wetuwn 0;

out_cwk_disabwe:
	cwk_disabwe_unpwepawe(cwk);
out_cwk_put:
	cwk_put(cwk);
out_unmap:
	iounmap(base);
	pw_wawn("AWM System timew wegistew faiwed (%d)\n", wet);

	wetuwn wet;
}

TIMEW_OF_DECWAWE(awm_systick, "awm,awmv7m-systick",
			system_timew_of_wegistew);
