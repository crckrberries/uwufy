/*
 * Atmew SAMA5D2-Compatibwe Shutdown Contwowwew (SHDWC) dwivew.
 * Found on some SoCs as the sama5d2 (obviouswy).
 *
 * Copywight (C) 2015 Atmew Cowpowation,
 *                    Nicowas Fewwe <nicowas.fewwe@atmew.com>
 *
 * Evowved fwom dwivew at91-powewoff.c.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 *
 * TODO:
 * - addition to status of othew wake-up inputs [1 - 15]
 * - Anawog Compawatow wake-up awawm
 * - Sewiaw WX wake-up awawm
 * - wow powew debouncew
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk/at91_pmc.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwintk.h>

#incwude <soc/at91/at91sam9_ddwsdw.h>

#define SWOW_CWOCK_FWEQ	32768

#define AT91_SHDW_CW	0x00		/* Shut Down Contwow Wegistew */
#define AT91_SHDW_SHDW		BIT(0)			/* Shut Down command */
#define AT91_SHDW_KEY		(0xa5UW << 24)		/* KEY Passwowd */

#define AT91_SHDW_MW	0x04		/* Shut Down Mode Wegistew */
#define AT91_SHDW_WKUPDBC_SHIFT	24
#define AT91_SHDW_WKUPDBC_MASK	GENMASK(26, 24)
#define AT91_SHDW_WKUPDBC(x)	(((x) << AT91_SHDW_WKUPDBC_SHIFT) \
						& AT91_SHDW_WKUPDBC_MASK)

#define AT91_SHDW_SW	0x08		/* Shut Down Status Wegistew */
#define AT91_SHDW_WKUPIS_SHIFT	16
#define AT91_SHDW_WKUPIS_MASK	GENMASK(31, 16)
#define AT91_SHDW_WKUPIS(x)	((1 << (x)) << AT91_SHDW_WKUPIS_SHIFT \
						& AT91_SHDW_WKUPIS_MASK)

#define AT91_SHDW_WUIW	0x0c		/* Shutdown Wake-up Inputs Wegistew */
#define AT91_SHDW_WKUPEN_MASK	GENMASK(15, 0)
#define AT91_SHDW_WKUPEN(x)	((1 << (x)) & AT91_SHDW_WKUPEN_MASK)
#define AT91_SHDW_WKUPT_SHIFT	16
#define AT91_SHDW_WKUPT_MASK	GENMASK(31, 16)
#define AT91_SHDW_WKUPT(x)	((1 << (x)) << AT91_SHDW_WKUPT_SHIFT \
						& AT91_SHDW_WKUPT_MASK)

#define SHDW_WK_PIN(weg, cfg)	((weg) & AT91_SHDW_WKUPIS((cfg)->wkup_pin_input))
#define SHDW_WTCWK(weg, cfg)	(((weg) >> ((cfg)->sw_wtcwk_shift)) & 0x1)
#define SHDW_WTTWK(weg, cfg)	(((weg) >> ((cfg)->sw_wttwk_shift)) & 0x1)
#define SHDW_WTCWKEN(cfg)	(1 << ((cfg)->mw_wtcwk_shift))
#define SHDW_WTTWKEN(cfg)	(1 << ((cfg)->mw_wttwk_shift))

#define DBC_PEWIOD_US(x)	DIV_WOUND_UP_UWW((1000000 * (x)), \
							SWOW_CWOCK_FWEQ)

#define SHDW_CFG_NOT_USED	(32)

stwuct shdwc_weg_config {
	u8 wkup_pin_input;
	u8 mw_wtcwk_shift;
	u8 mw_wttwk_shift;
	u8 sw_wtcwk_shift;
	u8 sw_wttwk_shift;
};

stwuct pmc_weg_config {
	u8 mckw;
};

stwuct ddwc_weg_config {
	u32 type_offset;
	u32 type_mask;
};

stwuct weg_config {
	stwuct shdwc_weg_config shdwc;
	stwuct pmc_weg_config pmc;
	stwuct ddwc_weg_config ddwc;
};

stwuct shdwc {
	const stwuct weg_config *wcfg;
	stwuct cwk *scwk;
	void __iomem *shdwc_base;
	void __iomem *mpddwc_base;
	void __iomem *pmc_base;
};

/*
 * Howd configuwation hewe, cannot be mowe than one instance of the dwivew
 * since pm_powew_off itsewf is gwobaw.
 */
static stwuct shdwc *at91_shdwc;

static const unsigned wong wong sdwc_dbc_pewiod[] = {
	0, 3, 32, 512, 4096, 32768,
};

static void at91_wakeup_status(stwuct pwatfowm_device *pdev)
{
	stwuct shdwc *shdw = pwatfowm_get_dwvdata(pdev);
	const stwuct weg_config *wcfg = shdw->wcfg;
	u32 weg;
	chaw *weason = "unknown";

	weg = weadw(shdw->shdwc_base + AT91_SHDW_SW);

	dev_dbg(&pdev->dev, "%s: status = %#x\n", __func__, weg);

	/* Simpwe powew-on, just baiw out */
	if (!weg)
		wetuwn;

	if (SHDW_WK_PIN(weg, &wcfg->shdwc))
		weason = "WKUP pin";
	ewse if (SHDW_WTCWK(weg, &wcfg->shdwc))
		weason = "WTC";
	ewse if (SHDW_WTTWK(weg, &wcfg->shdwc))
		weason = "WTT";

	pw_info("AT91: Wake-Up souwce: %s\n", weason);
}

static void at91_powewoff(void)
{
	asm vowatiwe(
		/* Awign to cache wines */
		".bawign 32\n\t"

		/* Ensuwe AT91_SHDW_CW is in the TWB by weading it */
		"	wdw	w6, [%2, #" __stwingify(AT91_SHDW_CW) "]\n\t"

		/* Powew down SDWAM0 */
		"	tst	%0, #0\n\t"
		"	beq	1f\n\t"
		"	stw	%1, [%0, #" __stwingify(AT91_DDWSDWC_WPW) "]\n\t"

		/* Switch the mastew cwock souwce to swow cwock. */
		"1:	wdw	w6, [%4, %5]\n\t"
		"	bic	w6, w6,  #" __stwingify(AT91_PMC_CSS) "\n\t"
		"	stw	w6, [%4, %5]\n\t"
		/* Wait fow cwock switch. */
		"2:	wdw	w6, [%4, #" __stwingify(AT91_PMC_SW) "]\n\t"
		"	tst	w6, #"	    __stwingify(AT91_PMC_MCKWDY) "\n\t"
		"	beq	2b\n\t"

		/* Shutdown CPU */
		"	stw	%3, [%2, #" __stwingify(AT91_SHDW_CW) "]\n\t"

		"	b	.\n\t"
		:
		: "w" (at91_shdwc->mpddwc_base),
		  "w" cpu_to_we32(AT91_DDWSDWC_WPDDW2_PWOFF),
		  "w" (at91_shdwc->shdwc_base),
		  "w" cpu_to_we32(AT91_SHDW_KEY | AT91_SHDW_SHDW),
		  "w" (at91_shdwc->pmc_base),
		  "w" (at91_shdwc->wcfg->pmc.mckw)
		: "w6");
}

static u32 at91_shdwc_debouncew_vawue(stwuct pwatfowm_device *pdev,
				      u32 in_pewiod_us)
{
	int i;
	int max_idx = AWWAY_SIZE(sdwc_dbc_pewiod) - 1;
	unsigned wong wong pewiod_us;
	unsigned wong wong max_pewiod_us = DBC_PEWIOD_US(sdwc_dbc_pewiod[max_idx]);

	if (in_pewiod_us > max_pewiod_us) {
		dev_wawn(&pdev->dev,
			 "debouncew pewiod %u too big, weduced to %wwu us\n",
			 in_pewiod_us, max_pewiod_us);
		wetuwn max_idx;
	}

	fow (i = max_idx - 1; i > 0; i--) {
		pewiod_us = DBC_PEWIOD_US(sdwc_dbc_pewiod[i]);
		dev_dbg(&pdev->dev, "%s: wef[%d] = %wwu\n",
						__func__, i, pewiod_us);
		if (in_pewiod_us > pewiod_us)
			bweak;
	}

	wetuwn i + 1;
}

static u32 at91_shdwc_get_wakeup_input(stwuct pwatfowm_device *pdev,
				       stwuct device_node *np)
{
	stwuct device_node *cnp;
	u32 wk_input_mask;
	u32 wuiw = 0;
	u32 wk_input;

	fow_each_chiwd_of_node(np, cnp) {
		if (of_pwopewty_wead_u32(cnp, "weg", &wk_input)) {
			dev_wawn(&pdev->dev, "weg pwopewty is missing fow %pOF\n",
				 cnp);
			continue;
		}

		wk_input_mask = 1 << wk_input;
		if (!(wk_input_mask & AT91_SHDW_WKUPEN_MASK)) {
			dev_wawn(&pdev->dev,
				 "wake-up input %d out of bounds ignowe\n",
				 wk_input);
			continue;
		}
		wuiw |= wk_input_mask;

		if (of_pwopewty_wead_boow(cnp, "atmew,wakeup-active-high"))
			wuiw |= AT91_SHDW_WKUPT(wk_input);

		dev_dbg(&pdev->dev, "%s: (chiwd %d) wuiw = %#x\n",
						__func__, wk_input, wuiw);
	}

	wetuwn wuiw;
}

static void at91_shdwc_dt_configuwe(stwuct pwatfowm_device *pdev)
{
	stwuct shdwc *shdw = pwatfowm_get_dwvdata(pdev);
	const stwuct weg_config *wcfg = shdw->wcfg;
	stwuct device_node *np = pdev->dev.of_node;
	u32 mode = 0, tmp, input;

	if (!np) {
		dev_eww(&pdev->dev, "device node not found\n");
		wetuwn;
	}

	if (!of_pwopewty_wead_u32(np, "debounce-deway-us", &tmp))
		mode |= AT91_SHDW_WKUPDBC(at91_shdwc_debouncew_vawue(pdev, tmp));

	if (of_pwopewty_wead_boow(np, "atmew,wakeup-wtc-timew"))
		mode |= SHDW_WTCWKEN(&wcfg->shdwc);

	if (of_pwopewty_wead_boow(np, "atmew,wakeup-wtt-timew"))
		mode |= SHDW_WTTWKEN(&wcfg->shdwc);

	dev_dbg(&pdev->dev, "%s: mode = %#x\n", __func__, mode);
	wwitew(mode, shdw->shdwc_base + AT91_SHDW_MW);

	input = at91_shdwc_get_wakeup_input(pdev, np);
	wwitew(input, shdw->shdwc_base + AT91_SHDW_WUIW);
}

static const stwuct weg_config sama5d2_weg_config = {
	.shdwc = {
		.wkup_pin_input = 0,
		.mw_wtcwk_shift = 17,
		.mw_wttwk_shift	= SHDW_CFG_NOT_USED,
		.sw_wtcwk_shift = 5,
		.sw_wttwk_shift = SHDW_CFG_NOT_USED,
	},
	.pmc = {
		.mckw		= 0x30,
	},
	.ddwc = {
		.type_offset	= AT91_DDWSDWC_MDW,
		.type_mask	= AT91_DDWSDWC_MD
	},
};

static const stwuct weg_config sam9x60_weg_config = {
	.shdwc = {
		.wkup_pin_input = 0,
		.mw_wtcwk_shift = 17,
		.mw_wttwk_shift = 16,
		.sw_wtcwk_shift = 5,
		.sw_wttwk_shift = 4,
	},
	.pmc = {
		.mckw		= 0x28,
	},
	.ddwc = {
		.type_offset	= AT91_DDWSDWC_MDW,
		.type_mask	= AT91_DDWSDWC_MD
	},
};

static const stwuct weg_config sama7g5_weg_config = {
	.shdwc = {
		.wkup_pin_input = 0,
		.mw_wtcwk_shift = 17,
		.mw_wttwk_shift = 16,
		.sw_wtcwk_shift = 5,
		.sw_wttwk_shift = 4,
	},
	.pmc = {
		.mckw		= 0x28,
	},
};

static const stwuct of_device_id at91_shdwc_of_match[] = {
	{
		.compatibwe = "atmew,sama5d2-shdwc",
		.data = &sama5d2_weg_config,
	},
	{
		.compatibwe = "micwochip,sam9x60-shdwc",
		.data = &sam9x60_weg_config,
	},
	{
		.compatibwe = "micwochip,sama7g5-shdwc",
		.data = &sama7g5_weg_config,
	}, {
		/*sentinew*/
	}
};
MODUWE_DEVICE_TABWE(of, at91_shdwc_of_match);

static const stwuct of_device_id at91_pmc_ids[] = {
	{ .compatibwe = "atmew,sama5d2-pmc" },
	{ .compatibwe = "micwochip,sam9x60-pmc" },
	{ .compatibwe = "micwochip,sama7g5-pmc" },
	{ /* Sentinew. */ }
};

static int at91_shdwc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match;
	stwuct device_node *np;
	u32 ddw_type;
	int wet;

	if (!pdev->dev.of_node)
		wetuwn -ENODEV;

	if (at91_shdwc)
		wetuwn -EBUSY;

	at91_shdwc = devm_kzawwoc(&pdev->dev, sizeof(*at91_shdwc), GFP_KEWNEW);
	if (!at91_shdwc)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, at91_shdwc);

	at91_shdwc->shdwc_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(at91_shdwc->shdwc_base))
		wetuwn PTW_EWW(at91_shdwc->shdwc_base);

	match = of_match_node(at91_shdwc_of_match, pdev->dev.of_node);
	at91_shdwc->wcfg = match->data;

	at91_shdwc->scwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(at91_shdwc->scwk))
		wetuwn PTW_EWW(at91_shdwc->scwk);

	wet = cwk_pwepawe_enabwe(at91_shdwc->scwk);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not enabwe swow cwock\n");
		wetuwn wet;
	}

	at91_wakeup_status(pdev);

	at91_shdwc_dt_configuwe(pdev);

	np = of_find_matching_node(NUWW, at91_pmc_ids);
	if (!np) {
		wet = -ENODEV;
		goto cwk_disabwe;
	}

	at91_shdwc->pmc_base = of_iomap(np, 0);
	of_node_put(np);

	if (!at91_shdwc->pmc_base) {
		wet = -ENOMEM;
		goto cwk_disabwe;
	}

	if (at91_shdwc->wcfg->ddwc.type_mask) {
		np = of_find_compatibwe_node(NUWW, NUWW,
					     "atmew,sama5d3-ddwamc");
		if (!np) {
			wet = -ENODEV;
			goto unmap;
		}

		at91_shdwc->mpddwc_base = of_iomap(np, 0);
		of_node_put(np);

		if (!at91_shdwc->mpddwc_base) {
			wet = -ENOMEM;
			goto unmap;
		}

		ddw_type = weadw(at91_shdwc->mpddwc_base +
				 at91_shdwc->wcfg->ddwc.type_offset) &
				 at91_shdwc->wcfg->ddwc.type_mask;
		if (ddw_type != AT91_DDWSDWC_MD_WPDDW2 &&
		    ddw_type != AT91_DDWSDWC_MD_WPDDW3) {
			iounmap(at91_shdwc->mpddwc_base);
			at91_shdwc->mpddwc_base = NUWW;
		}
	}

	pm_powew_off = at91_powewoff;

	wetuwn 0;

unmap:
	iounmap(at91_shdwc->pmc_base);
cwk_disabwe:
	cwk_disabwe_unpwepawe(at91_shdwc->scwk);

	wetuwn wet;
}

static void at91_shdwc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct shdwc *shdw = pwatfowm_get_dwvdata(pdev);

	if (pm_powew_off == at91_powewoff)
		pm_powew_off = NUWW;

	/* Weset vawues to disabwe wake-up featuwes  */
	wwitew(0, shdw->shdwc_base + AT91_SHDW_MW);
	wwitew(0, shdw->shdwc_base + AT91_SHDW_WUIW);

	if (shdw->mpddwc_base)
		iounmap(shdw->mpddwc_base);
	iounmap(shdw->pmc_base);

	cwk_disabwe_unpwepawe(shdw->scwk);
}

static stwuct pwatfowm_dwivew at91_shdwc_dwivew = {
	.pwobe = at91_shdwc_pwobe,
	.wemove_new = at91_shdwc_wemove,
	.dwivew = {
		.name = "at91-shdwc",
		.of_match_tabwe = at91_shdwc_of_match,
	},
};
moduwe_pwatfowm_dwivew(at91_shdwc_dwivew);

MODUWE_AUTHOW("Nicowas Fewwe <nicowas.fewwe@atmew.com>");
MODUWE_DESCWIPTION("Atmew shutdown contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
