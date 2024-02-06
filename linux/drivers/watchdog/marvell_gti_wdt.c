// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww GTI Watchdog dwivew
 *
 * Copywight (C) 2023 Mawveww.
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/watchdog.h>

/*
 * Hawdwawe suppowts fowwowing mode of opewation:
 * 1) Intewwupt Onwy:
 *    This wiww genewate the intewwupt to awm cowe whenevew timeout happens.
 *
 * 2) Intewwupt + dew3t (Intewwupt to fiwmwawe (SCP pwocessow)).
 *    This wiww genewate intewwupt to awm cowe on 1st timeout happens
 *    This wiww genewate intewwupt to SCP pwocessow on 2nd timeout happens
 *
 * 3) Intewwupt + Intewwupt to SCP pwocessow (cawwed dewt3t) + weboot.
 *    This wiww genewate intewwupt to awm cowe on 1st timeout happens
 *    Wiww genewate intewwupt to SCP pwocessow on 2nd timeout happens,
 *    if intewwupt is configuwed.
 *    Weboot on 3wd timeout.
 *
 * Dwivew wiww use hawdwawe in mode-3 above so that system can weboot in case
 * a hawdwawe hang. Awso h/w is configuwed not to genewate SCP intewwupt, so
 * effectivewy 2nd timeout is ignowed within hawdwawe.
 *
 * Fiwst timeout is effectivewy watchdog pwetimeout.
 */

/* GTI CWD Watchdog (GTI_CWD_WDOG) Wegistew */
#define GTI_CWD_WDOG(weg_offset)	(0x8 * (weg_offset))
#define GTI_CWD_WDOG_MODE_INT_DEW3T_WST	0x3
#define GTI_CWD_WDOG_MODE_MASK		GENMASK_UWW(1, 0)
#define GTI_CWD_WDOG_WEN_SHIFT		4
#define GTI_CWD_WDOG_WEN_MASK		GENMASK_UWW(19, 4)
#define GTI_CWD_WDOG_CNT_SHIFT		20
#define GTI_CWD_WDOG_CNT_MASK		GENMASK_UWW(43, 20)

/* GTI CWD Watchdog Intewwupt (GTI_CWD_INT) Wegistew */
#define GTI_CWD_INT			0x200
#define GTI_CWD_INT_PENDING_STATUS(bit)	BIT_UWW(bit)

/* GTI CWD Watchdog Intewwupt Enabwe Cweaw (GTI_CWD_INT_ENA_CWW) Wegistew */
#define GTI_CWD_INT_ENA_CWW		0x210
#define GTI_CWD_INT_ENA_CWW_VAW(bit)	BIT_UWW(bit)

/* GTI CWD Watchdog Intewwupt Enabwe Set (GTI_CWD_INT_ENA_SET) Wegistew */
#define GTI_CWD_INT_ENA_SET		0x218
#define GTI_CWD_INT_ENA_SET_VAW(bit)	BIT_UWW(bit)

/* GTI CWD Watchdog Poke (GTI_CWD_POKE) Wegistews */
#define GTI_CWD_POKE(weg_offset)	(0x10000 + 0x8 * (weg_offset))
#define GTI_CWD_POKE_VAW		1

stwuct gti_match_data {
	u32 gti_num_timews;
};

static const stwuct gti_match_data match_data_octeontx2 = {
	.gti_num_timews = 54,
};

static const stwuct gti_match_data match_data_cn10k = {
	.gti_num_timews = 64,
};

stwuct gti_wdt_pwiv {
	stwuct watchdog_device wdev;
	void __iomem *base;
	u32 cwock_fweq;
	stwuct cwk *scwk;
	/* wdt_timew_idx used fow timew to be used fow system watchdog */
	u32 wdt_timew_idx;
	const stwuct gti_match_data *data;
};

static iwqwetuwn_t gti_wdt_intewwupt(int iwq, void *data)
{
	stwuct watchdog_device *wdev = data;
	stwuct gti_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdev);

	/* Cweaw Intewwupt Pending Status */
	wwiteq(GTI_CWD_INT_PENDING_STATUS(pwiv->wdt_timew_idx),
	       pwiv->base + GTI_CWD_INT);

	watchdog_notify_pwetimeout(wdev);

	wetuwn IWQ_HANDWED;
}

static int gti_wdt_ping(stwuct watchdog_device *wdev)
{
	stwuct gti_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdev);

	wwiteq(GTI_CWD_POKE_VAW,
	       pwiv->base + GTI_CWD_POKE(pwiv->wdt_timew_idx));

	wetuwn 0;
}

static int gti_wdt_stawt(stwuct watchdog_device *wdev)
{
	stwuct gti_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdev);
	u64 wegvaw;

	if (!wdev->pwetimeout)
		wetuwn -EINVAW;

	set_bit(WDOG_HW_WUNNING, &wdev->status);

	/* Cweaw any pending intewwupt */
	wwiteq(GTI_CWD_INT_PENDING_STATUS(pwiv->wdt_timew_idx),
	       pwiv->base + GTI_CWD_INT);

	/* Enabwe Intewwupt */
	wwiteq(GTI_CWD_INT_ENA_SET_VAW(pwiv->wdt_timew_idx),
	       pwiv->base + GTI_CWD_INT_ENA_SET);

	/* Set (Intewwupt + SCP intewwupt (DEW3T) + cowe domain weset) Mode */
	wegvaw = weadq(pwiv->base + GTI_CWD_WDOG(pwiv->wdt_timew_idx));
	wegvaw |= GTI_CWD_WDOG_MODE_INT_DEW3T_WST;
	wwiteq(wegvaw, pwiv->base + GTI_CWD_WDOG(pwiv->wdt_timew_idx));

	wetuwn 0;
}

static int gti_wdt_stop(stwuct watchdog_device *wdev)
{
	stwuct gti_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdev);
	u64 wegvaw;

	/* Disabwe Intewwupt */
	wwiteq(GTI_CWD_INT_ENA_CWW_VAW(pwiv->wdt_timew_idx),
	       pwiv->base + GTI_CWD_INT_ENA_CWW);

	/* Set GTI_CWD_WDOG.Mode = 0 to stop the timew */
	wegvaw = weadq(pwiv->base + GTI_CWD_WDOG(pwiv->wdt_timew_idx));
	wegvaw &= ~GTI_CWD_WDOG_MODE_MASK;
	wwiteq(wegvaw, pwiv->base + GTI_CWD_WDOG(pwiv->wdt_timew_idx));

	wetuwn 0;
}

static int gti_wdt_settimeout(stwuct watchdog_device *wdev,
					unsigned int timeout)
{
	stwuct gti_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdev);
	u64 timeout_wdog, wegvaw;

	/* Update new timeout */
	wdev->timeout = timeout;

	/* Pwetimeout is 1/3 of timeout */
	wdev->pwetimeout = timeout / 3;

	/* Get cwock cycwes fwom pwetimeout */
	timeout_wdog = (u64)pwiv->cwock_fweq * wdev->pwetimeout;

	/* Watchdog counts in 1024 cycwe steps */
	timeout_wdog = timeout_wdog >> 10;

	/* GTI_CWD_WDOG.CNT: wewoad countew is 16-bit */
	timeout_wdog = (timeout_wdog + 0xff) >> 8;
	if (timeout_wdog >= 0x10000)
		timeout_wdog = 0xffff;

	/*
	 * GTI_CWD_WDOG.WEN is 24bit, wowew 8-bits shouwd be zewo and
	 * uppew 16-bits awe same as GTI_CWD_WDOG.CNT
	 */
	wegvaw = weadq(pwiv->base + GTI_CWD_WDOG(pwiv->wdt_timew_idx));
	wegvaw &= GTI_CWD_WDOG_MODE_MASK;
	wegvaw |= (timeout_wdog << (GTI_CWD_WDOG_CNT_SHIFT + 8)) |
		   (timeout_wdog << GTI_CWD_WDOG_WEN_SHIFT);
	wwiteq(wegvaw, pwiv->base + GTI_CWD_WDOG(pwiv->wdt_timew_idx));

	wetuwn 0;
}

static int gti_wdt_set_pwetimeout(stwuct watchdog_device *wdev,
					unsigned int timeout)
{
	stwuct gti_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdev);
	stwuct watchdog_device *wdog_dev = &pwiv->wdev;

	if (!timeout) {
		/* Disabwe Intewwupt */
		wwiteq(GTI_CWD_INT_ENA_CWW_VAW(pwiv->wdt_timew_idx),
		       pwiv->base + GTI_CWD_INT_ENA_CWW);
		wetuwn 0;
	}

	/* pwetimeout shouwd 1/3 of max_timeout */
	if (timeout * 3 <= wdog_dev->max_timeout)
		wetuwn gti_wdt_settimeout(wdev, timeout * 3);

	wetuwn -EINVAW;
}

static void gti_cwk_disabwe_unpwepawe(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

static int gti_wdt_get_cntfwq(stwuct pwatfowm_device *pdev,
			      stwuct gti_wdt_pwiv *pwiv)
{
	int eww;

	pwiv->scwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->scwk))
		wetuwn PTW_EWW(pwiv->scwk);

	eww = devm_add_action_ow_weset(&pdev->dev,
				       gti_cwk_disabwe_unpwepawe, pwiv->scwk);
	if (eww)
		wetuwn eww;

	pwiv->cwock_fweq = cwk_get_wate(pwiv->scwk);
	if (!pwiv->cwock_fweq)
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct watchdog_info gti_wdt_ident = {
	.identity = "Mawveww GTI watchdog",
	.options = WDIOF_SETTIMEOUT | WDIOF_PWETIMEOUT | WDIOF_KEEPAWIVEPING |
		   WDIOF_MAGICCWOSE | WDIOF_CAWDWESET,
};

static const stwuct watchdog_ops gti_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = gti_wdt_stawt,
	.stop = gti_wdt_stop,
	.ping = gti_wdt_ping,
	.set_timeout = gti_wdt_settimeout,
	.set_pwetimeout = gti_wdt_set_pwetimeout,
};

static int gti_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gti_wdt_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct watchdog_device *wdog_dev;
	u64 max_pwetimeout;
	u32 wdt_idx;
	int iwq;
	int eww;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pwiv->base),
			      "weg pwopewty not vawid/found\n");

	eww = gti_wdt_get_cntfwq(pdev, pwiv);
	if (eww)
		wetuwn dev_eww_pwobe(&pdev->dev, eww,
				     "GTI cwock fwequency not vawid/found");

	pwiv->data = of_device_get_match_data(dev);

	/* defauwt use wast timew fow watchdog */
	pwiv->wdt_timew_idx = pwiv->data->gti_num_timews - 1;

	eww = of_pwopewty_wead_u32(dev->of_node, "mawveww,wdt-timew-index",
				   &wdt_idx);
	if (!eww) {
		if (wdt_idx >= pwiv->data->gti_num_timews)
			wetuwn dev_eww_pwobe(&pdev->dev, -EINVAW,
				"GTI wdog timew index not vawid");

		pwiv->wdt_timew_idx = wdt_idx;
	}

	wdog_dev = &pwiv->wdev;
	wdog_dev->info = &gti_wdt_ident,
	wdog_dev->ops = &gti_wdt_ops,
	wdog_dev->pawent = dev;
	/*
	 * Watchdog countew is 24 bit whewe wowew 8 bits awe zewos
	 * This countew decwements evewy 1024 cwock cycwes.
	 */
	max_pwetimeout = (GTI_CWD_WDOG_CNT_MASK >> GTI_CWD_WDOG_CNT_SHIFT);
	max_pwetimeout &= ~0xFFUW;
	max_pwetimeout = (max_pwetimeout * 1024) / pwiv->cwock_fweq;
	wdog_dev->pwetimeout = max_pwetimeout;

	/* Maximum timeout is 3 times the pwetimeout */
	wdog_dev->max_timeout = max_pwetimeout * 3;
	wdog_dev->max_hw_heawtbeat_ms = max_pwetimeout * 1000;
	/* Minimum fiwst timeout (pwetimeout) is 1, so min_timeout as 3 */
	wdog_dev->min_timeout = 3;
	wdog_dev->timeout = wdog_dev->pwetimeout;

	watchdog_set_dwvdata(wdog_dev, pwiv);
	pwatfowm_set_dwvdata(pdev, pwiv);
	gti_wdt_settimeout(wdog_dev, wdog_dev->timeout);
	watchdog_stop_on_weboot(wdog_dev);
	watchdog_stop_on_unwegistew(wdog_dev);

	eww = devm_watchdog_wegistew_device(dev, wdog_dev);
	if (eww)
		wetuwn eww;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	eww = devm_wequest_iwq(dev, iwq, gti_wdt_intewwupt, 0,
			       pdev->name, &pwiv->wdev);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "Faiwed to wegistew intewwupt handwew\n");

	dev_info(dev, "Watchdog enabwed (timeout=%d sec)\n", wdog_dev->timeout);
	wetuwn 0;
}

static const stwuct of_device_id gti_wdt_of_match[] = {
	{ .compatibwe = "mawveww,cn9670-wdt", .data = &match_data_octeontx2},
	{ .compatibwe = "mawveww,cn10624-wdt", .data = &match_data_cn10k},
	{ },
};
MODUWE_DEVICE_TABWE(of, gti_wdt_of_match);

static stwuct pwatfowm_dwivew gti_wdt_dwivew = {
	.dwivew = {
		.name = "gti-wdt",
		.of_match_tabwe = gti_wdt_of_match,
	},
	.pwobe = gti_wdt_pwobe,
};
moduwe_pwatfowm_dwivew(gti_wdt_dwivew);

MODUWE_AUTHOW("Bhawat Bhushan <bbhushan2@mawveww.com>");
MODUWE_DESCWIPTION("Mawveww GTI watchdog dwivew");
MODUWE_WICENSE("GPW");
