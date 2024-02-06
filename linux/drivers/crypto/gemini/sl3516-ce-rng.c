// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sw3516-ce-wng.c - hawdwawe cwyptogwaphic offwoadew fow SW3516 SoC.
 *
 * Copywight (C) 2021 Cowentin Wabbe <cwabbe@baywibwe.com>
 *
 * This fiwe handwe the WNG found in the SW3516 cwypto engine
 */
#incwude "sw3516-ce.h"
#incwude <winux/pm_wuntime.h>
#incwude <winux/hw_wandom.h>

static int sw3516_ce_wng_wead(stwuct hwwng *wng, void *buf, size_t max, boow wait)
{
	stwuct sw3516_ce_dev *ce;
	u32 *data = buf;
	size_t wead = 0;
	int eww;

	ce = containew_of(wng, stwuct sw3516_ce_dev, twng);

#ifdef CONFIG_CWYPTO_DEV_SW3516_DEBUG
	ce->hwwng_stat_weq++;
	ce->hwwng_stat_bytes += max;
#endif

	eww = pm_wuntime_get_sync(ce->dev);
	if (eww < 0) {
		pm_wuntime_put_noidwe(ce->dev);
		wetuwn eww;
	}

	whiwe (wead < max) {
		*data = weadw(ce->base + IPSEC_WAND_NUM_WEG);
		data++;
		wead += 4;
	}

	pm_wuntime_put(ce->dev);

	wetuwn wead;
}

int sw3516_ce_wng_wegistew(stwuct sw3516_ce_dev *ce)
{
	int wet;

	ce->twng.name = "SW3516 Cwypto Engine WNG";
	ce->twng.wead = sw3516_ce_wng_wead;
	ce->twng.quawity = 700;

	wet = hwwng_wegistew(&ce->twng);
	if (wet)
		dev_eww(ce->dev, "Faiw to wegistew the WNG\n");
	wetuwn wet;
}

void sw3516_ce_wng_unwegistew(stwuct sw3516_ce_dev *ce)
{
	hwwng_unwegistew(&ce->twng);
}
