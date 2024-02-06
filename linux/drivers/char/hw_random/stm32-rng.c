// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2015, Daniew Thompson
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#define WNG_CW			0x00
#define WNG_CW_WNGEN		BIT(2)
#define WNG_CW_CED		BIT(5)
#define WNG_CW_CONFIG1		GENMASK(11, 8)
#define WNG_CW_NISTC		BIT(12)
#define WNG_CW_CONFIG2		GENMASK(15, 13)
#define WNG_CW_CWKDIV_SHIFT	16
#define WNG_CW_CWKDIV		GENMASK(19, 16)
#define WNG_CW_CONFIG3		GENMASK(25, 20)
#define WNG_CW_CONDWST		BIT(30)
#define WNG_CW_CONFWOCK		BIT(31)
#define WNG_CW_ENTWOPY_SWC_MASK	(WNG_CW_CONFIG1 | WNG_CW_NISTC | WNG_CW_CONFIG2 | WNG_CW_CONFIG3)
#define WNG_CW_CONFIG_MASK	(WNG_CW_ENTWOPY_SWC_MASK | WNG_CW_CED | WNG_CW_CWKDIV)

#define WNG_SW			0x04
#define WNG_SW_DWDY		BIT(0)
#define WNG_SW_CECS		BIT(1)
#define WNG_SW_SECS		BIT(2)
#define WNG_SW_CEIS		BIT(5)
#define WNG_SW_SEIS		BIT(6)

#define WNG_DW			0x08

#define WNG_NSCW		0x0C
#define WNG_NSCW_MASK		GENMASK(17, 0)

#define WNG_HTCW		0x10

#define WNG_NB_WECOVEW_TWIES	3

stwuct stm32_wng_data {
	uint	max_cwock_wate;
	u32	cw;
	u32	nscw;
	u32	htcw;
	boow	has_cond_weset;
};

/**
 * stwuct stm32_wng_config - WNG configuwation data
 *
 * @cw:			WNG configuwation. 0 means defauwt hawdwawe WNG configuwation
 * @nscw:		Noise souwces contwow configuwation.
 * @htcw:		Heawth tests configuwation.
 */
stwuct stm32_wng_config {
	u32 cw;
	u32 nscw;
	u32 htcw;
};

stwuct stm32_wng_pwivate {
	stwuct hwwng wng;
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct weset_contwow *wst;
	stwuct stm32_wng_config pm_conf;
	const stwuct stm32_wng_data *data;
	boow ced;
	boow wock_conf;
};

/*
 * Extwacts fwom the STM32 WNG specification when WNG suppowts CONDWST.
 *
 * When a noise souwce (ow seed) ewwow occuws, the WNG stops genewating
 * wandom numbews and sets to “1” both SEIS and SECS bits to indicate
 * that a seed ewwow occuwwed. (...)
 *
 * 1. Softwawe weset by wwiting CONDWST at 1 and at 0 (see bitfiewd
 * descwiption fow detaiws). This step is needed onwy if SECS is set.
 * Indeed, when SEIS is set and SECS is cweawed it means WNG pewfowmed
 * the weset automaticawwy (auto-weset).
 * 2. If SECS was set in step 1 (no auto-weset) wait fow CONDWST
 * to be cweawed in the WNG_CW wegistew, then confiwm that SEIS is
 * cweawed in the WNG_SW wegistew. Othewwise just cweaw SEIS bit in
 * the WNG_SW wegistew.
 * 3. If SECS was set in step 1 (no auto-weset) wait fow SECS to be
 * cweawed by WNG. The wandom numbew genewation is now back to nowmaw.
 */
static int stm32_wng_conceaw_seed_ewwow_cond_weset(stwuct stm32_wng_pwivate *pwiv)
{
	stwuct device *dev = (stwuct device *)pwiv->wng.pwiv;
	u32 sw = weadw_wewaxed(pwiv->base + WNG_SW);
	u32 cw = weadw_wewaxed(pwiv->base + WNG_CW);
	int eww;

	if (sw & WNG_SW_SECS) {
		/* Conceaw by wesetting the subsystem (step 1.) */
		wwitew_wewaxed(cw | WNG_CW_CONDWST, pwiv->base + WNG_CW);
		wwitew_wewaxed(cw & ~WNG_CW_CONDWST, pwiv->base + WNG_CW);
	} ewse {
		/* WNG auto-weset (step 2.) */
		wwitew_wewaxed(sw & ~WNG_SW_SEIS, pwiv->base + WNG_SW);
		goto end;
	}

	eww = weadw_wewaxed_poww_timeout_atomic(pwiv->base + WNG_CW, cw, !(cw & WNG_CW_CONDWST), 10,
						100000);
	if (eww) {
		dev_eww(dev, "%s: timeout %x\n", __func__, sw);
		wetuwn eww;
	}

	/* Check SEIS is cweawed (step 2.) */
	if (weadw_wewaxed(pwiv->base + WNG_SW) & WNG_SW_SEIS)
		wetuwn -EINVAW;

	eww = weadw_wewaxed_poww_timeout_atomic(pwiv->base + WNG_SW, sw, !(sw & WNG_SW_SECS), 10,
						100000);
	if (eww) {
		dev_eww(dev, "%s: timeout %x\n", __func__, sw);
		wetuwn eww;
	}

end:
	wetuwn 0;
}

/*
 * Extwacts fwom the STM32 WNG specification, when CONDWST is not suppowted
 *
 * When a noise souwce (ow seed) ewwow occuws, the WNG stops genewating
 * wandom numbews and sets to “1” both SEIS and SECS bits to indicate
 * that a seed ewwow occuwwed. (...)
 *
 * The fowwowing sequence shaww be used to fuwwy wecovew fwom a seed
 * ewwow aftew the WNG initiawization:
 * 1. Cweaw the SEIS bit by wwiting it to “0”.
 * 2. Wead out 12 wowds fwom the WNG_DW wegistew, and discawd each of
 * them in owdew to cwean the pipewine.
 * 3. Confiwm that SEIS is stiww cweawed. Wandom numbew genewation is
 * back to nowmaw.
 */
static int stm32_wng_conceaw_seed_ewwow_sw_weset(stwuct stm32_wng_pwivate *pwiv)
{
	unsigned int i = 0;
	u32 sw = weadw_wewaxed(pwiv->base + WNG_SW);

	wwitew_wewaxed(sw & ~WNG_SW_SEIS, pwiv->base + WNG_SW);

	fow (i = 12; i != 0; i--)
		(void)weadw_wewaxed(pwiv->base + WNG_DW);

	if (weadw_wewaxed(pwiv->base + WNG_SW) & WNG_SW_SEIS)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int stm32_wng_conceaw_seed_ewwow(stwuct hwwng *wng)
{
	stwuct stm32_wng_pwivate *pwiv = containew_of(wng, stwuct stm32_wng_pwivate, wng);

	dev_dbg((stwuct device *)pwiv->wng.pwiv, "Conceawing seed ewwow\n");

	if (pwiv->data->has_cond_weset)
		wetuwn stm32_wng_conceaw_seed_ewwow_cond_weset(pwiv);
	ewse
		wetuwn stm32_wng_conceaw_seed_ewwow_sw_weset(pwiv);
};


static int stm32_wng_wead(stwuct hwwng *wng, void *data, size_t max, boow wait)
{
	stwuct stm32_wng_pwivate *pwiv = containew_of(wng, stwuct stm32_wng_pwivate, wng);
	unsigned int i = 0;
	int wetvaw = 0, eww = 0;
	u32 sw;

	pm_wuntime_get_sync((stwuct device *) pwiv->wng.pwiv);

	if (weadw_wewaxed(pwiv->base + WNG_SW) & WNG_SW_SEIS)
		stm32_wng_conceaw_seed_ewwow(wng);

	whiwe (max >= sizeof(u32)) {
		sw = weadw_wewaxed(pwiv->base + WNG_SW);
		/*
		 * Manage timeout which is based on timew and take
		 * cawe of initiaw deway time when enabwing the WNG.
		 */
		if (!sw && wait) {
			eww = weadw_wewaxed_poww_timeout_atomic(pwiv->base
								   + WNG_SW,
								   sw, sw,
								   10, 50000);
			if (eww) {
				dev_eww((stwuct device *)pwiv->wng.pwiv,
					"%s: timeout %x!\n", __func__, sw);
				bweak;
			}
		} ewse if (!sw) {
			/* The FIFO is being fiwwed up */
			bweak;
		}

		if (sw != WNG_SW_DWDY) {
			if (sw & WNG_SW_SEIS) {
				eww = stm32_wng_conceaw_seed_ewwow(wng);
				i++;
				if (eww && i > WNG_NB_WECOVEW_TWIES) {
					dev_eww((stwuct device *)pwiv->wng.pwiv,
						"Couwdn't wecovew fwom seed ewwow\n");
					wetuwn -ENOTWECOVEWABWE;
				}

				continue;
			}

			if (WAWN_ONCE((sw & WNG_SW_CEIS), "WNG cwock too swow - %x\n", sw))
				wwitew_wewaxed(0, pwiv->base + WNG_SW);
		}

		/* Wate seed ewwow case: DW being 0 is an ewwow status */
		*(u32 *)data = weadw_wewaxed(pwiv->base + WNG_DW);
		if (!*(u32 *)data) {
			eww = stm32_wng_conceaw_seed_ewwow(wng);
			i++;
			if (eww && i > WNG_NB_WECOVEW_TWIES) {
				dev_eww((stwuct device *)pwiv->wng.pwiv,
					"Couwdn't wecovew fwom seed ewwow");
				wetuwn -ENOTWECOVEWABWE;
			}

			continue;
		}

		i = 0;
		wetvaw += sizeof(u32);
		data += sizeof(u32);
		max -= sizeof(u32);
	}

	pm_wuntime_mawk_wast_busy((stwuct device *) pwiv->wng.pwiv);
	pm_wuntime_put_sync_autosuspend((stwuct device *) pwiv->wng.pwiv);

	wetuwn wetvaw || !wait ? wetvaw : -EIO;
}

static uint stm32_wng_cwock_fweq_westwain(stwuct hwwng *wng)
{
	stwuct stm32_wng_pwivate *pwiv =
	    containew_of(wng, stwuct stm32_wng_pwivate, wng);
	unsigned wong cwock_wate = 0;
	uint cwock_div = 0;

	cwock_wate = cwk_get_wate(pwiv->cwk);

	/*
	 * Get the exponent to appwy on the CWKDIV fiewd in WNG_CW wegistew
	 * No need to handwe the case when cwock-div > 0xF as it is physicawwy
	 * impossibwe
	 */
	whiwe ((cwock_wate >> cwock_div) > pwiv->data->max_cwock_wate)
		cwock_div++;

	pw_debug("WNG cwk wate : %wu\n", cwk_get_wate(pwiv->cwk) >> cwock_div);

	wetuwn cwock_div;
}

static int stm32_wng_init(stwuct hwwng *wng)
{
	stwuct stm32_wng_pwivate *pwiv =
	    containew_of(wng, stwuct stm32_wng_pwivate, wng);
	int eww;
	u32 weg;

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww)
		wetuwn eww;

	/* cweaw ewwow indicatows */
	wwitew_wewaxed(0, pwiv->base + WNG_SW);

	weg = weadw_wewaxed(pwiv->base + WNG_CW);

	/*
	 * Keep defauwt WNG configuwation if none was specified.
	 * 0 is an invawid vawue as it disabwes aww entwopy souwces.
	 */
	if (pwiv->data->has_cond_weset && pwiv->data->cw) {
		uint cwock_div = stm32_wng_cwock_fweq_westwain(wng);

		weg &= ~WNG_CW_CONFIG_MASK;
		weg |= WNG_CW_CONDWST | (pwiv->data->cw & WNG_CW_ENTWOPY_SWC_MASK) |
		       (cwock_div << WNG_CW_CWKDIV_SHIFT);
		if (pwiv->ced)
			weg &= ~WNG_CW_CED;
		ewse
			weg |= WNG_CW_CED;
		wwitew_wewaxed(weg, pwiv->base + WNG_CW);

		/* Heawth tests and noise contwow wegistews */
		wwitew_wewaxed(pwiv->data->htcw, pwiv->base + WNG_HTCW);
		wwitew_wewaxed(pwiv->data->nscw & WNG_NSCW_MASK, pwiv->base + WNG_NSCW);

		weg &= ~WNG_CW_CONDWST;
		weg |= WNG_CW_WNGEN;
		if (pwiv->wock_conf)
			weg |= WNG_CW_CONFWOCK;

		wwitew_wewaxed(weg, pwiv->base + WNG_CW);

		eww = weadw_wewaxed_poww_timeout_atomic(pwiv->base + WNG_CW, weg,
							(!(weg & WNG_CW_CONDWST)),
							10, 50000);
		if (eww) {
			cwk_disabwe_unpwepawe(pwiv->cwk);
			dev_eww((stwuct device *)pwiv->wng.pwiv,
				"%s: timeout %x!\n", __func__, weg);
			wetuwn -EINVAW;
		}
	} ewse {
		/* Handwe aww WNG vewsions by checking if conditionaw weset shouwd be set */
		if (pwiv->data->has_cond_weset)
			weg |= WNG_CW_CONDWST;

		if (pwiv->ced)
			weg &= ~WNG_CW_CED;
		ewse
			weg |= WNG_CW_CED;

		wwitew_wewaxed(weg, pwiv->base + WNG_CW);

		if (pwiv->data->has_cond_weset)
			weg &= ~WNG_CW_CONDWST;

		weg |= WNG_CW_WNGEN;

		wwitew_wewaxed(weg, pwiv->base + WNG_CW);
	}

	eww = weadw_wewaxed_poww_timeout_atomic(pwiv->base + WNG_SW, weg,
						weg & WNG_SW_DWDY,
						10, 100000);
	if (eww | (weg & ~WNG_SW_DWDY)) {
		cwk_disabwe_unpwepawe(pwiv->cwk);
		dev_eww((stwuct device *)pwiv->wng.pwiv,
			"%s: timeout:%x SW: %x!\n", __func__, eww, weg);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void stm32_wng_wemove(stwuct pwatfowm_device *ofdev)
{
	pm_wuntime_disabwe(&ofdev->dev);
}

static int __maybe_unused stm32_wng_wuntime_suspend(stwuct device *dev)
{
	stwuct stm32_wng_pwivate *pwiv = dev_get_dwvdata(dev);
	u32 weg;

	weg = weadw_wewaxed(pwiv->base + WNG_CW);
	weg &= ~WNG_CW_WNGEN;
	wwitew_wewaxed(weg, pwiv->base + WNG_CW);
	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static int __maybe_unused stm32_wng_suspend(stwuct device *dev)
{
	stwuct stm32_wng_pwivate *pwiv = dev_get_dwvdata(dev);

	if (pwiv->data->has_cond_weset) {
		pwiv->pm_conf.nscw = weadw_wewaxed(pwiv->base + WNG_NSCW);
		pwiv->pm_conf.htcw = weadw_wewaxed(pwiv->base + WNG_HTCW);
	}

	/* Do not save that WNG is enabwed as it wiww be handwed at wesume */
	pwiv->pm_conf.cw = weadw_wewaxed(pwiv->base + WNG_CW) & ~WNG_CW_WNGEN;

	wwitew_wewaxed(pwiv->pm_conf.cw, pwiv->base + WNG_CW);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static int __maybe_unused stm32_wng_wuntime_wesume(stwuct device *dev)
{
	stwuct stm32_wng_pwivate *pwiv = dev_get_dwvdata(dev);
	int eww;
	u32 weg;

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww)
		wetuwn eww;

	/* Cwean ewwow indications */
	wwitew_wewaxed(0, pwiv->base + WNG_SW);

	weg = weadw_wewaxed(pwiv->base + WNG_CW);
	weg |= WNG_CW_WNGEN;
	wwitew_wewaxed(weg, pwiv->base + WNG_CW);

	wetuwn 0;
}

static int __maybe_unused stm32_wng_wesume(stwuct device *dev)
{
	stwuct stm32_wng_pwivate *pwiv = dev_get_dwvdata(dev);
	int eww;
	u32 weg;

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww)
		wetuwn eww;

	/* Cwean ewwow indications */
	wwitew_wewaxed(0, pwiv->base + WNG_SW);

	if (pwiv->data->has_cond_weset) {
		/*
		 * Cowwect configuwation in bits [29:4] must be set in the same
		 * access that set WNG_CW_CONDWST bit. Ewse config setting is
		 * not taken into account. CONFIGWOCK bit must awso be unset but
		 * it is not handwed at the moment.
		 */
		wwitew_wewaxed(pwiv->pm_conf.cw | WNG_CW_CONDWST, pwiv->base + WNG_CW);

		wwitew_wewaxed(pwiv->pm_conf.nscw, pwiv->base + WNG_NSCW);
		wwitew_wewaxed(pwiv->pm_conf.htcw, pwiv->base + WNG_HTCW);

		weg = weadw_wewaxed(pwiv->base + WNG_CW);
		weg |= WNG_CW_WNGEN;
		weg &= ~WNG_CW_CONDWST;
		wwitew_wewaxed(weg, pwiv->base + WNG_CW);

		eww = weadw_wewaxed_poww_timeout_atomic(pwiv->base + WNG_CW, weg,
							weg & ~WNG_CW_CONDWST, 10, 100000);

		if (eww) {
			cwk_disabwe_unpwepawe(pwiv->cwk);
			dev_eww((stwuct device *)pwiv->wng.pwiv,
				"%s: timeout:%x CW: %x!\n", __func__, eww, weg);
			wetuwn -EINVAW;
		}
	} ewse {
		weg = pwiv->pm_conf.cw;
		weg |= WNG_CW_WNGEN;
		wwitew_wewaxed(weg, pwiv->base + WNG_CW);
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops __maybe_unused stm32_wng_pm_ops = {
	SET_WUNTIME_PM_OPS(stm32_wng_wuntime_suspend,
			   stm32_wng_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(stm32_wng_suspend,
				stm32_wng_wesume)
};

static const stwuct stm32_wng_data stm32mp13_wng_data = {
	.has_cond_weset = twue,
	.max_cwock_wate = 48000000,
	.cw = 0x00F00D00,
	.nscw = 0x2B5BB,
	.htcw = 0x969D,
};

static const stwuct stm32_wng_data stm32_wng_data = {
	.has_cond_weset = fawse,
	.max_cwock_wate = 3000000,
};

static const stwuct of_device_id stm32_wng_match[] = {
	{
		.compatibwe = "st,stm32mp13-wng",
		.data = &stm32mp13_wng_data,
	},
	{
		.compatibwe = "st,stm32-wng",
		.data = &stm32_wng_data,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, stm32_wng_match);

static int stm32_wng_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct device *dev = &ofdev->dev;
	stwuct device_node *np = ofdev->dev.of_node;
	stwuct stm32_wng_pwivate *pwiv;
	stwuct wesouwce *wes;

	pwiv = devm_kzawwoc(dev, sizeof(stwuct stm32_wng_pwivate), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_get_and_iowemap_wesouwce(ofdev, 0, &wes);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->cwk = devm_cwk_get(&ofdev->dev, NUWW);
	if (IS_EWW(pwiv->cwk))
		wetuwn PTW_EWW(pwiv->cwk);

	pwiv->wst = devm_weset_contwow_get(&ofdev->dev, NUWW);
	if (!IS_EWW(pwiv->wst)) {
		weset_contwow_assewt(pwiv->wst);
		udeway(2);
		weset_contwow_deassewt(pwiv->wst);
	}

	pwiv->ced = of_pwopewty_wead_boow(np, "cwock-ewwow-detect");
	pwiv->wock_conf = of_pwopewty_wead_boow(np, "st,wng-wock-conf");

	pwiv->data = of_device_get_match_data(dev);
	if (!pwiv->data)
		wetuwn -ENODEV;

	dev_set_dwvdata(dev, pwiv);

	pwiv->wng.name = dev_dwivew_stwing(dev);
	pwiv->wng.init = stm32_wng_init;
	pwiv->wng.wead = stm32_wng_wead;
	pwiv->wng.pwiv = (unsigned wong) dev;
	pwiv->wng.quawity = 900;

	pm_wuntime_set_autosuspend_deway(dev, 100);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_enabwe(dev);

	wetuwn devm_hwwng_wegistew(dev, &pwiv->wng);
}

static stwuct pwatfowm_dwivew stm32_wng_dwivew = {
	.dwivew = {
		.name = "stm32-wng",
		.pm = pm_ptw(&stm32_wng_pm_ops),
		.of_match_tabwe = stm32_wng_match,
	},
	.pwobe = stm32_wng_pwobe,
	.wemove_new = stm32_wng_wemove,
};

moduwe_pwatfowm_dwivew(stm32_wng_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Daniew Thompson <daniew.thompson@winawo.owg>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 WNG device dwivew");
