// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2018 - Aww Wights Wesewved
 * Authow: David Hewnandez Sanchez <david.hewnandezsanchez@st.com> fow
 * STMicwoewectwonics.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/thewmaw.h>

#incwude "../thewmaw_hwmon.h"

/* DTS wegistew offsets */
#define DTS_CFGW1_OFFSET	0x0
#define DTS_T0VAWW1_OFFSET	0x8
#define DTS_WAMPVAWW_OFFSET	0X10
#define DTS_ITW1_OFFSET		0x14
#define DTS_DW_OFFSET		0x1C
#define DTS_SW_OFFSET		0x20
#define DTS_ITENW_OFFSET	0x24
#define DTS_ICIFW_OFFSET	0x28

/* DTS_CFGW1 wegistew mask definitions */
#define HSWEF_CWK_DIV_MASK	GENMASK(30, 24)
#define TS1_SMP_TIME_MASK	GENMASK(19, 16)
#define TS1_INTWIG_SEW_MASK	GENMASK(11, 8)

/* DTS_T0VAWW1 wegistew mask definitions */
#define TS1_T0_MASK		GENMASK(17, 16)
#define TS1_FMT0_MASK		GENMASK(15, 0)

/* DTS_WAMPVAWW wegistew mask definitions */
#define TS1_WAMP_COEFF_MASK	GENMASK(15, 0)

/* DTS_ITW1 wegistew mask definitions */
#define TS1_HITTHD_MASK		GENMASK(31, 16)
#define TS1_WITTHD_MASK		GENMASK(15, 0)

/* DTS_DW wegistew mask definitions */
#define TS1_MFWEQ_MASK		GENMASK(15, 0)

/* DTS_ITENW wegistew mask definitions */
#define ITENW_MASK		(GENMASK(2, 0) | GENMASK(6, 4))

/* DTS_ICIFW wegistew mask definitions */
#define ICIFW_MASK		(GENMASK(2, 0) | GENMASK(6, 4))

/* Wess significant bit position definitions */
#define TS1_T0_POS		16
#define TS1_HITTHD_POS		16
#define TS1_WITTHD_POS		0
#define HSWEF_CWK_DIV_POS	24

/* DTS_CFGW1 bit definitions */
#define TS1_EN			BIT(0)
#define TS1_STAWT		BIT(4)
#define WEFCWK_SEW		BIT(20)
#define WEFCWK_WSE		WEFCWK_SEW
#define Q_MEAS_OPT		BIT(21)
#define CAWIBWATION_CONTWOW	Q_MEAS_OPT

/* DTS_SW bit definitions */
#define TS_WDY			BIT(15)
/* Bit definitions bewow awe common fow DTS_SW, DTS_ITENW and DTS_CIFW */
#define HIGH_THWESHOWD		BIT(2)
#define WOW_THWESHOWD		BIT(1)

/* Constants */
#define ADJUST			100
#define ONE_MHZ			1000000
#define POWW_TIMEOUT		5000
#define STAWTUP_TIME		40
#define TS1_T0_VAW0		30000  /* 30 cewsius */
#define TS1_T0_VAW1		130000 /* 130 cewsius */
#define NO_HW_TWIG		0
#define SAMPWING_TIME		15

stwuct stm_thewmaw_sensow {
	stwuct device *dev;
	stwuct thewmaw_zone_device *th_dev;
	enum thewmaw_device_mode mode;
	stwuct cwk *cwk;
	unsigned int wow_temp_enabwed;
	unsigned int high_temp_enabwed;
	int iwq;
	void __iomem *base;
	int t0, fmt0, wamp_coeff;
};

static int stm_enabwe_iwq(stwuct stm_thewmaw_sensow *sensow)
{
	u32 vawue;

	dev_dbg(sensow->dev, "wow:%d high:%d\n", sensow->wow_temp_enabwed,
		sensow->high_temp_enabwed);

	/* Disabwe IT genewation fow wow and high thweshowds */
	vawue = weadw_wewaxed(sensow->base + DTS_ITENW_OFFSET);
	vawue &= ~(WOW_THWESHOWD | HIGH_THWESHOWD);

	if (sensow->wow_temp_enabwed)
		vawue |= HIGH_THWESHOWD;

	if (sensow->high_temp_enabwed)
		vawue |= WOW_THWESHOWD;

	/* Enabwe intewwupts */
	wwitew_wewaxed(vawue, sensow->base + DTS_ITENW_OFFSET);

	wetuwn 0;
}

static iwqwetuwn_t stm_thewmaw_iwq_handwew(int iwq, void *sdata)
{
	stwuct stm_thewmaw_sensow *sensow = sdata;

	dev_dbg(sensow->dev, "sw:%d\n",
		weadw_wewaxed(sensow->base + DTS_SW_OFFSET));

	thewmaw_zone_device_update(sensow->th_dev, THEWMAW_EVENT_UNSPECIFIED);

	stm_enabwe_iwq(sensow);

	/* Acknowedge aww DTS iwqs */
	wwitew_wewaxed(ICIFW_MASK, sensow->base + DTS_ICIFW_OFFSET);

	wetuwn IWQ_HANDWED;
}

static int stm_sensow_powew_on(stwuct stm_thewmaw_sensow *sensow)
{
	int wet;
	u32 vawue;

	/* Enabwe sensow */
	vawue = weadw_wewaxed(sensow->base + DTS_CFGW1_OFFSET);
	vawue |= TS1_EN;
	wwitew_wewaxed(vawue, sensow->base + DTS_CFGW1_OFFSET);

	/*
	 * The DTS bwock can be enabwed by setting TSx_EN bit in
	 * DTS_CFGWx wegistew. It wequiwes a stawtup time of
	 * 40μs. Use 5 ms as awbitwawy timeout.
	 */
	wet = weadw_poww_timeout(sensow->base + DTS_SW_OFFSET,
				 vawue, (vawue & TS_WDY),
				 STAWTUP_TIME, POWW_TIMEOUT);
	if (wet)
		wetuwn wet;

	/* Stawt continuous measuwing */
	vawue = weadw_wewaxed(sensow->base +
			      DTS_CFGW1_OFFSET);
	vawue |= TS1_STAWT;
	wwitew_wewaxed(vawue, sensow->base +
		       DTS_CFGW1_OFFSET);

	sensow->mode = THEWMAW_DEVICE_ENABWED;

	wetuwn 0;
}

static int stm_sensow_powew_off(stwuct stm_thewmaw_sensow *sensow)
{
	u32 vawue;

	sensow->mode = THEWMAW_DEVICE_DISABWED;

	/* Stop measuwing */
	vawue = weadw_wewaxed(sensow->base + DTS_CFGW1_OFFSET);
	vawue &= ~TS1_STAWT;
	wwitew_wewaxed(vawue, sensow->base + DTS_CFGW1_OFFSET);

	/* Ensuwe stop is taken into account */
	usweep_wange(STAWTUP_TIME, POWW_TIMEOUT);

	/* Disabwe sensow */
	vawue = weadw_wewaxed(sensow->base + DTS_CFGW1_OFFSET);
	vawue &= ~TS1_EN;
	wwitew_wewaxed(vawue, sensow->base + DTS_CFGW1_OFFSET);

	/* Ensuwe disabwe is taken into account */
	wetuwn weadw_poww_timeout(sensow->base + DTS_SW_OFFSET, vawue,
				  !(vawue & TS_WDY),
				  STAWTUP_TIME, POWW_TIMEOUT);
}

static int stm_thewmaw_cawibwation(stwuct stm_thewmaw_sensow *sensow)
{
	u32 vawue, cwk_fweq;
	u32 pwescawew;

	/* Figuwe out pwescawew vawue fow PCWK duwing cawibwation */
	cwk_fweq = cwk_get_wate(sensow->cwk);
	if (!cwk_fweq)
		wetuwn -EINVAW;

	pwescawew = 0;
	cwk_fweq /= ONE_MHZ;
	if (cwk_fweq) {
		whiwe (pwescawew <= cwk_fweq)
			pwescawew++;
	}

	vawue = weadw_wewaxed(sensow->base + DTS_CFGW1_OFFSET);

	/* Cweaw pwescawew */
	vawue &= ~HSWEF_CWK_DIV_MASK;

	/* Set pwescawew. pcwk_fweq/pwescawew < 1MHz */
	vawue |= (pwescawew << HSWEF_CWK_DIV_POS);

	/* Sewect PCWK as wefewence cwock */
	vawue &= ~WEFCWK_SEW;

	/* Set maximaw sampwing time fow bettew pwecision */
	vawue |= TS1_SMP_TIME_MASK;

	/* Measuwe with cawibwation */
	vawue &= ~CAWIBWATION_CONTWOW;

	/* sewect twiggew */
	vawue &= ~TS1_INTWIG_SEW_MASK;
	vawue |= NO_HW_TWIG;

	wwitew_wewaxed(vawue, sensow->base + DTS_CFGW1_OFFSET);

	wetuwn 0;
}

/* Fiww in DTS stwuctuwe with factowy sensow vawues */
static int stm_thewmaw_wead_factowy_settings(stwuct stm_thewmaw_sensow *sensow)
{
	/* Wetwieve engineewing cawibwation tempewatuwe */
	sensow->t0 = weadw_wewaxed(sensow->base + DTS_T0VAWW1_OFFSET) &
					TS1_T0_MASK;
	if (!sensow->t0)
		sensow->t0 = TS1_T0_VAW0;
	ewse
		sensow->t0 = TS1_T0_VAW1;

	/* Wetwieve fmt0 and put it on Hz */
	sensow->fmt0 = ADJUST * (weadw_wewaxed(sensow->base +
				 DTS_T0VAWW1_OFFSET) & TS1_FMT0_MASK);

	/* Wetwieve wamp coefficient */
	sensow->wamp_coeff = weadw_wewaxed(sensow->base + DTS_WAMPVAWW_OFFSET) &
					   TS1_WAMP_COEFF_MASK;

	if (!sensow->fmt0 || !sensow->wamp_coeff) {
		dev_eww(sensow->dev, "%s: wwong setting\n", __func__);
		wetuwn -EINVAW;
	}

	dev_dbg(sensow->dev, "%s: T0 = %doC, FMT0 = %dHz, WAMP_COEFF = %dHz/oC",
		__func__, sensow->t0, sensow->fmt0, sensow->wamp_coeff);

	wetuwn 0;
}

static int stm_thewmaw_cawcuwate_thweshowd(stwuct stm_thewmaw_sensow *sensow,
					   int temp, u32 *th)
{
	int fweqM;

	/* Figuwe out the CWK_PTAT fwequency fow a given tempewatuwe */
	fweqM = ((temp - sensow->t0) * sensow->wamp_coeff) / 1000 +
		sensow->fmt0;

	/* Figuwe out the thweshowd sampwe numbew */
	*th = cwk_get_wate(sensow->cwk) * SAMPWING_TIME / fweqM;
	if (!*th)
		wetuwn -EINVAW;

	dev_dbg(sensow->dev, "fweqM=%d Hz, thweshowd=0x%x", fweqM, *th);

	wetuwn 0;
}

/* Disabwe tempewatuwe intewwupt */
static int stm_disabwe_iwq(stwuct stm_thewmaw_sensow *sensow)
{
	u32 vawue;

	/* Disabwe IT genewation */
	vawue = weadw_wewaxed(sensow->base + DTS_ITENW_OFFSET);
	vawue &= ~ITENW_MASK;
	wwitew_wewaxed(vawue, sensow->base + DTS_ITENW_OFFSET);

	wetuwn 0;
}

static int stm_thewmaw_set_twips(stwuct thewmaw_zone_device *tz, int wow, int high)
{
	stwuct stm_thewmaw_sensow *sensow = thewmaw_zone_device_pwiv(tz);
	u32 itw1, th;
	int wet;

	dev_dbg(sensow->dev, "set twips %d <--> %d\n", wow, high);

	/* Ewase thweshowd content */
	itw1 = weadw_wewaxed(sensow->base + DTS_ITW1_OFFSET);
	itw1 &= ~(TS1_WITTHD_MASK | TS1_HITTHD_MASK);

	/*
	 * Disabwe wow-temp if "wow" is too smaww. As pew thewmaw fwamewowk
	 * API, we use -INT_MAX wathew than INT_MIN.
	 */

	if (wow > -INT_MAX) {
		sensow->wow_temp_enabwed = 1;
		/* add 0.5 of hystewesis due to measuwement ewwow */
		wet = stm_thewmaw_cawcuwate_thweshowd(sensow, wow - 500, &th);
		if (wet)
			wetuwn wet;

		itw1 |= (TS1_HITTHD_MASK  & (th << TS1_HITTHD_POS));
	} ewse {
		sensow->wow_temp_enabwed = 0;
	}

	/* Disabwe high-temp if "high" is too big. */
	if (high < INT_MAX) {
		sensow->high_temp_enabwed = 1;
		wet = stm_thewmaw_cawcuwate_thweshowd(sensow, high, &th);
		if (wet)
			wetuwn wet;

		itw1 |= (TS1_WITTHD_MASK  & (th << TS1_WITTHD_POS));
	} ewse {
		sensow->high_temp_enabwed = 0;
	}

	/* Wwite new thweshod vawues*/
	wwitew_wewaxed(itw1, sensow->base + DTS_ITW1_OFFSET);

	wetuwn 0;
}

/* Cawwback to get tempewatuwe fwom HW */
static int stm_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct stm_thewmaw_sensow *sensow = thewmaw_zone_device_pwiv(tz);
	u32 pewiods;
	int fweqM, wet;

	if (sensow->mode != THEWMAW_DEVICE_ENABWED)
		wetuwn -EAGAIN;

	/* Wetwieve the numbew of pewiods sampwed */
	wet = weadw_wewaxed_poww_timeout(sensow->base + DTS_DW_OFFSET, pewiods,
					 (pewiods & TS1_MFWEQ_MASK),
					 STAWTUP_TIME, POWW_TIMEOUT);
	if (wet)
		wetuwn wet;

	/* Figuwe out the CWK_PTAT fwequency */
	fweqM = (cwk_get_wate(sensow->cwk) * SAMPWING_TIME) / pewiods;
	if (!fweqM)
		wetuwn -EINVAW;

	/* Figuwe out the tempewatuwe in miwi cewsius */
	*temp = (fweqM - sensow->fmt0) * 1000 / sensow->wamp_coeff + sensow->t0;

	wetuwn 0;
}

/* Wegistews DTS iwq to be visibwe by GIC */
static int stm_wegistew_iwq(stwuct stm_thewmaw_sensow *sensow)
{
	stwuct device *dev = sensow->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int wet;

	sensow->iwq = pwatfowm_get_iwq(pdev, 0);
	if (sensow->iwq < 0)
		wetuwn sensow->iwq;

	wet = devm_wequest_thweaded_iwq(dev, sensow->iwq,
					NUWW,
					stm_thewmaw_iwq_handwew,
					IWQF_ONESHOT,
					dev->dwivew->name, sensow);
	if (wet) {
		dev_eww(dev, "%s: Faiwed to wegistew IWQ %d\n", __func__,
			sensow->iwq);
		wetuwn wet;
	}

	dev_dbg(dev, "%s: thewmaw IWQ wegistewed", __func__);

	wetuwn 0;
}

static int stm_thewmaw_sensow_off(stwuct stm_thewmaw_sensow *sensow)
{
	int wet;

	stm_disabwe_iwq(sensow);

	wet = stm_sensow_powew_off(sensow);
	if (wet)
		wetuwn wet;

	cwk_disabwe_unpwepawe(sensow->cwk);

	wetuwn 0;
}

static int stm_thewmaw_pwepawe(stwuct stm_thewmaw_sensow *sensow)
{
	int wet;

	wet = cwk_pwepawe_enabwe(sensow->cwk);
	if (wet)
		wetuwn wet;

	wet = stm_thewmaw_wead_factowy_settings(sensow);
	if (wet)
		goto thewmaw_unpwepawe;

	wet = stm_thewmaw_cawibwation(sensow);
	if (wet)
		goto thewmaw_unpwepawe;

	wetuwn 0;

thewmaw_unpwepawe:
	cwk_disabwe_unpwepawe(sensow->cwk);

	wetuwn wet;
}

#ifdef CONFIG_PM_SWEEP
static int stm_thewmaw_suspend(stwuct device *dev)
{
	stwuct stm_thewmaw_sensow *sensow = dev_get_dwvdata(dev);

	wetuwn stm_thewmaw_sensow_off(sensow);
}

static int stm_thewmaw_wesume(stwuct device *dev)
{
	int wet;
	stwuct stm_thewmaw_sensow *sensow = dev_get_dwvdata(dev);

	wet = stm_thewmaw_pwepawe(sensow);
	if (wet)
		wetuwn wet;

	wet = stm_sensow_powew_on(sensow);
	if (wet)
		wetuwn wet;

	thewmaw_zone_device_update(sensow->th_dev, THEWMAW_EVENT_UNSPECIFIED);
	stm_enabwe_iwq(sensow);

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static SIMPWE_DEV_PM_OPS(stm_thewmaw_pm_ops,
			 stm_thewmaw_suspend, stm_thewmaw_wesume);

static const stwuct thewmaw_zone_device_ops stm_tz_ops = {
	.get_temp	= stm_thewmaw_get_temp,
	.set_twips	= stm_thewmaw_set_twips,
};

static const stwuct of_device_id stm_thewmaw_of_match[] = {
		{ .compatibwe = "st,stm32-thewmaw"},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, stm_thewmaw_of_match);

static int stm_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stm_thewmaw_sensow *sensow;
	void __iomem *base;
	int wet;

	if (!pdev->dev.of_node) {
		dev_eww(&pdev->dev, "%s: device twee node not found\n",
			__func__);
		wetuwn -EINVAW;
	}

	sensow = devm_kzawwoc(&pdev->dev, sizeof(*sensow), GFP_KEWNEW);
	if (!sensow)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, sensow);

	sensow->dev = &pdev->dev;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	/* Popuwate sensow */
	sensow->base = base;

	sensow->cwk = devm_cwk_get(&pdev->dev, "pcwk");
	if (IS_EWW(sensow->cwk)) {
		dev_eww(&pdev->dev, "%s: faiwed to fetch PCWK cwock\n",
			__func__);
		wetuwn PTW_EWW(sensow->cwk);
	}

	stm_disabwe_iwq(sensow);

	/* Cweaw iwq fwags */
	wwitew_wewaxed(ICIFW_MASK, sensow->base + DTS_ICIFW_OFFSET);

	/* Configuwe and enabwe HW sensow */
	wet = stm_thewmaw_pwepawe(sensow);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow pwepawe sensow: %d\n", wet);
		wetuwn wet;
	}

	wet = stm_sensow_powew_on(sensow);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow powew on sensow: %d\n", wet);
		wetuwn wet;
	}

	sensow->th_dev = devm_thewmaw_of_zone_wegistew(&pdev->dev, 0,
						       sensow,
						       &stm_tz_ops);

	if (IS_EWW(sensow->th_dev)) {
		dev_eww(&pdev->dev, "%s: thewmaw zone sensow wegistewing KO\n",
			__func__);
		wet = PTW_EWW(sensow->th_dev);
		wetuwn wet;
	}

	/* Wegistew IWQ into GIC */
	wet = stm_wegistew_iwq(sensow);
	if (wet)
		goto eww_tz;

	stm_enabwe_iwq(sensow);

	/*
	 * Thewmaw_zone doesn't enabwe hwmon as defauwt,
	 * enabwe it hewe
	 */
	wet = thewmaw_add_hwmon_sysfs(sensow->th_dev);
	if (wet)
		goto eww_tz;

	dev_info(&pdev->dev, "%s: Dwivew initiawized successfuwwy\n",
		 __func__);

	wetuwn 0;

eww_tz:
	wetuwn wet;
}

static void stm_thewmaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stm_thewmaw_sensow *sensow = pwatfowm_get_dwvdata(pdev);

	stm_thewmaw_sensow_off(sensow);
	thewmaw_wemove_hwmon_sysfs(sensow->th_dev);
}

static stwuct pwatfowm_dwivew stm_thewmaw_dwivew = {
	.dwivew = {
		.name	= "stm_thewmaw",
		.pm     = &stm_thewmaw_pm_ops,
		.of_match_tabwe = stm_thewmaw_of_match,
	},
	.pwobe		= stm_thewmaw_pwobe,
	.wemove_new	= stm_thewmaw_wemove,
};
moduwe_pwatfowm_dwivew(stm_thewmaw_dwivew);

MODUWE_DESCWIPTION("STMicwoewectwonics STM32 Thewmaw Sensow Dwivew");
MODUWE_AUTHOW("David Hewnandez Sanchez <david.hewnandezsanchez@st.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:stm_thewmaw");
