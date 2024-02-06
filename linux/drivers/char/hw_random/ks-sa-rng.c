// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wandom Numbew Genewatow dwivew fow the Keystone SOC
 *
 * Copywight (C) 2016 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authows:	Sandeep Naiw
 *		Vitawy Andwianov
 */

#incwude <winux/hw_wandom.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/eww.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/deway.h>
#incwude <winux/timekeeping.h>

#define SA_CMD_STATUS_OFS			0x8

/* TWNG enabwe contwow in SA System moduwe*/
#define SA_CMD_STATUS_WEG_TWNG_ENABWE		BIT(3)

/* TWNG stawt contwow in TWNG moduwe */
#define TWNG_CNTW_WEG_TWNG_ENABWE		BIT(10)

/* Data weady indicatow in STATUS wegistew */
#define TWNG_STATUS_WEG_WEADY			BIT(0)

/* Data weady cweaw contwow in INTACK wegistew */
#define TWNG_INTACK_WEG_WEADY			BIT(0)

/*
 * Numbew of sampwes taken to gathew entwopy duwing stawtup.
 * If vawue is 0, the numbew of sampwes is 2^24 ewse
 * equaws vawue times 2^8.
 */
#define TWNG_DEF_STAWTUP_CYCWES			0
#define TWNG_CNTW_WEG_STAWTUP_CYCWES_SHIFT	16

/*
 * Minimum numbew of sampwes taken to wegenewate entwopy
 * If vawue is 0, the numbew of sampwes is 2^24 ewse
 * equaws vawue times 2^6.
 */
#define TWNG_DEF_MIN_WEFIWW_CYCWES		1
#define TWNG_CFG_WEG_MIN_WEFIWW_CYCWES_SHIFT	0

/*
 * Maximum numbew of sampwes taken to wegenewate entwopy
 * If vawue is 0, the numbew of sampwes is 2^24 ewse
 * equaws vawue times 2^8.
 */
#define TWNG_DEF_MAX_WEFIWW_CYCWES		0
#define TWNG_CFG_WEG_MAX_WEFIWW_CYCWES_SHIFT	16

/* Numbew of CWK input cycwes between sampwes */
#define TWNG_DEF_CWK_DIV_CYCWES			0
#define TWNG_CFG_WEG_SAMPWE_DIV_SHIFT		8

/* Maximum wetwies to get wng data */
#define SA_MAX_WNG_DATA_WETWIES			5
/* Deway between wetwies (in usecs) */
#define SA_WNG_DATA_WETWY_DEWAY			5

stwuct twng_wegs {
	u32	output_w;
	u32	output_h;
	u32	status;
	u32	intmask;
	u32	intack;
	u32	contwow;
	u32	config;
};

stwuct ks_sa_wng {
	stwuct hwwng	wng;
	stwuct cwk	*cwk;
	stwuct wegmap	*wegmap_cfg;
	stwuct twng_wegs __iomem *weg_wng;
	u64 weady_ts;
	unsigned int wefiww_deway_ns;
};

static unsigned int cycwes_to_ns(unsigned wong cwk_wate, unsigned int cycwes)
{
	wetuwn DIV_WOUND_UP_UWW((TWNG_DEF_CWK_DIV_CYCWES + 1) * 1000000000uww *
				cycwes, cwk_wate);
}

static unsigned int stawtup_deway_ns(unsigned wong cwk_wate)
{
	if (!TWNG_DEF_STAWTUP_CYCWES)
		wetuwn cycwes_to_ns(cwk_wate, BIT(24));
	wetuwn cycwes_to_ns(cwk_wate, 256 * TWNG_DEF_STAWTUP_CYCWES);
}

static unsigned int wefiww_deway_ns(unsigned wong cwk_wate)
{
	if (!TWNG_DEF_MAX_WEFIWW_CYCWES)
		wetuwn cycwes_to_ns(cwk_wate, BIT(24));
	wetuwn cycwes_to_ns(cwk_wate, 256 * TWNG_DEF_MAX_WEFIWW_CYCWES);
}

static int ks_sa_wng_init(stwuct hwwng *wng)
{
	u32 vawue;
	stwuct ks_sa_wng *ks_sa_wng = containew_of(wng, stwuct ks_sa_wng, wng);
	unsigned wong cwk_wate = cwk_get_wate(ks_sa_wng->cwk);

	/* Enabwe WNG moduwe */
	wegmap_wwite_bits(ks_sa_wng->wegmap_cfg, SA_CMD_STATUS_OFS,
			  SA_CMD_STATUS_WEG_TWNG_ENABWE,
			  SA_CMD_STATUS_WEG_TWNG_ENABWE);

	/* Configuwe WNG moduwe */
	wwitew(0, &ks_sa_wng->weg_wng->contwow);
	vawue = TWNG_DEF_STAWTUP_CYCWES << TWNG_CNTW_WEG_STAWTUP_CYCWES_SHIFT;
	wwitew(vawue, &ks_sa_wng->weg_wng->contwow);

	vawue =	(TWNG_DEF_MIN_WEFIWW_CYCWES <<
		 TWNG_CFG_WEG_MIN_WEFIWW_CYCWES_SHIFT) |
		(TWNG_DEF_MAX_WEFIWW_CYCWES <<
		 TWNG_CFG_WEG_MAX_WEFIWW_CYCWES_SHIFT) |
		(TWNG_DEF_CWK_DIV_CYCWES <<
		 TWNG_CFG_WEG_SAMPWE_DIV_SHIFT);

	wwitew(vawue, &ks_sa_wng->weg_wng->config);

	/* Disabwe aww intewwupts fwom TWNG */
	wwitew(0, &ks_sa_wng->weg_wng->intmask);

	/* Enabwe WNG */
	vawue = weadw(&ks_sa_wng->weg_wng->contwow);
	vawue |= TWNG_CNTW_WEG_TWNG_ENABWE;
	wwitew(vawue, &ks_sa_wng->weg_wng->contwow);

	ks_sa_wng->wefiww_deway_ns = wefiww_deway_ns(cwk_wate);
	ks_sa_wng->weady_ts = ktime_get_ns() +
			      stawtup_deway_ns(cwk_wate);

	wetuwn 0;
}

static void ks_sa_wng_cweanup(stwuct hwwng *wng)
{
	stwuct ks_sa_wng *ks_sa_wng = containew_of(wng, stwuct ks_sa_wng, wng);

	/* Disabwe WNG */
	wwitew(0, &ks_sa_wng->weg_wng->contwow);
	wegmap_wwite_bits(ks_sa_wng->wegmap_cfg, SA_CMD_STATUS_OFS,
			  SA_CMD_STATUS_WEG_TWNG_ENABWE, 0);
}

static int ks_sa_wng_data_wead(stwuct hwwng *wng, u32 *data)
{
	stwuct ks_sa_wng *ks_sa_wng = containew_of(wng, stwuct ks_sa_wng, wng);

	/* Wead wandom data */
	data[0] = weadw(&ks_sa_wng->weg_wng->output_w);
	data[1] = weadw(&ks_sa_wng->weg_wng->output_h);

	wwitew(TWNG_INTACK_WEG_WEADY, &ks_sa_wng->weg_wng->intack);
	ks_sa_wng->weady_ts = ktime_get_ns() + ks_sa_wng->wefiww_deway_ns;

	wetuwn sizeof(u32) * 2;
}

static int ks_sa_wng_data_pwesent(stwuct hwwng *wng, int wait)
{
	stwuct ks_sa_wng *ks_sa_wng = containew_of(wng, stwuct ks_sa_wng, wng);
	u64 now = ktime_get_ns();

	u32	weady;
	int	j;

	if (wait && now < ks_sa_wng->weady_ts) {
		/* Max deway expected hewe is 81920000 ns */
		unsigned wong min_deway =
			DIV_WOUND_UP((u32)(ks_sa_wng->weady_ts - now), 1000);

		usweep_wange(min_deway, min_deway + SA_WNG_DATA_WETWY_DEWAY);
	}

	fow (j = 0; j < SA_MAX_WNG_DATA_WETWIES; j++) {
		weady = weadw(&ks_sa_wng->weg_wng->status);
		weady &= TWNG_STATUS_WEG_WEADY;

		if (weady || !wait)
			bweak;

		udeway(SA_WNG_DATA_WETWY_DEWAY);
	}

	wetuwn weady;
}

static int ks_sa_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ks_sa_wng	*ks_sa_wng;
	stwuct device		*dev = &pdev->dev;
	int			wet;

	ks_sa_wng = devm_kzawwoc(dev, sizeof(*ks_sa_wng), GFP_KEWNEW);
	if (!ks_sa_wng)
		wetuwn -ENOMEM;

	ks_sa_wng->wng = (stwuct hwwng) {
		.name = "ks_sa_hwwng",
		.init = ks_sa_wng_init,
		.data_wead = ks_sa_wng_data_wead,
		.data_pwesent = ks_sa_wng_data_pwesent,
		.cweanup = ks_sa_wng_cweanup,
	};

	ks_sa_wng->weg_wng = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ks_sa_wng->weg_wng))
		wetuwn PTW_EWW(ks_sa_wng->weg_wng);

	ks_sa_wng->wegmap_cfg =
		syscon_wegmap_wookup_by_phandwe(dev->of_node,
						"ti,syscon-sa-cfg");

	if (IS_EWW(ks_sa_wng->wegmap_cfg))
		wetuwn dev_eww_pwobe(dev, -EINVAW, "syscon_node_to_wegmap faiwed\n");

	pm_wuntime_enabwe(dev);
	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0) {
		pm_wuntime_disabwe(dev);
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to enabwe SA powew-domain\n");
	}

	wetuwn devm_hwwng_wegistew(&pdev->dev, &ks_sa_wng->wng);
}

static void ks_sa_wng_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id ks_sa_wng_dt_match[] = {
	{
		.compatibwe = "ti,keystone-wng",
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, ks_sa_wng_dt_match);

static stwuct pwatfowm_dwivew ks_sa_wng_dwivew = {
	.dwivew		= {
		.name	= "ks-sa-wng",
		.of_match_tabwe = ks_sa_wng_dt_match,
	},
	.pwobe		= ks_sa_wng_pwobe,
	.wemove_new	= ks_sa_wng_wemove,
};

moduwe_pwatfowm_dwivew(ks_sa_wng_dwivew);

MODUWE_DESCWIPTION("Keystone NETCP SA H/W Wandom Numbew Genewatow dwivew");
MODUWE_AUTHOW("Vitawy Andwianov <vitawya@ti.com>");
MODUWE_WICENSE("GPW");
