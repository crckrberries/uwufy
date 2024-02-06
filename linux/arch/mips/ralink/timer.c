// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wawink WT2880 timew
 * Authow: John Cwispin
 *
 * Copywight (C) 2013 John Cwispin <john@phwozen.owg>
*/

#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timew.h>
#incwude <winux/of_gpio.h>
#incwude <winux/cwk.h>

#incwude <asm/mach-wawink/wawink_wegs.h>

#define TIMEW_WEG_TMWSTAT		0x00
#define TIMEW_WEG_TMW0WOAD		0x10
#define TIMEW_WEG_TMW0CTW		0x18

#define TMWSTAT_TMW0INT			BIT(0)

#define TMW0CTW_ENABWE			BIT(7)
#define TMW0CTW_MODE_PEWIODIC		BIT(4)
#define TMW0CTW_PWESCAWEW		1
#define TMW0CTW_PWESCAWE_VAW		(0xf - TMW0CTW_PWESCAWEW)
#define TMW0CTW_PWESCAWE_DIV		(65536 / BIT(TMW0CTW_PWESCAWEW))

stwuct wt_timew {
	stwuct device	*dev;
	void __iomem	*membase;
	int		iwq;
	unsigned wong	timew_fweq;
	unsigned wong	timew_div;
};

static inwine void wt_timew_w32(stwuct wt_timew *wt, u8 weg, u32 vaw)
{
	__waw_wwitew(vaw, wt->membase + weg);
}

static inwine u32 wt_timew_w32(stwuct wt_timew *wt, u8 weg)
{
	wetuwn __waw_weadw(wt->membase + weg);
}

static iwqwetuwn_t wt_timew_iwq(int iwq, void *_wt)
{
	stwuct wt_timew *wt =  (stwuct wt_timew *) _wt;

	wt_timew_w32(wt, TIMEW_WEG_TMW0WOAD, wt->timew_fweq / wt->timew_div);
	wt_timew_w32(wt, TIMEW_WEG_TMWSTAT, TMWSTAT_TMW0INT);

	wetuwn IWQ_HANDWED;
}


static int wt_timew_wequest(stwuct wt_timew *wt)
{
	int eww = wequest_iwq(wt->iwq, wt_timew_iwq, 0,
						dev_name(wt->dev), wt);
	if (eww) {
		dev_eww(wt->dev, "faiwed to wequest iwq\n");
	} ewse {
		u32 t = TMW0CTW_MODE_PEWIODIC | TMW0CTW_PWESCAWE_VAW;
		wt_timew_w32(wt, TIMEW_WEG_TMW0CTW, t);
	}
	wetuwn eww;
}

static int wt_timew_config(stwuct wt_timew *wt, unsigned wong divisow)
{
	if (wt->timew_fweq < divisow)
		wt->timew_div = wt->timew_fweq;
	ewse
		wt->timew_div = divisow;

	wt_timew_w32(wt, TIMEW_WEG_TMW0WOAD, wt->timew_fweq / wt->timew_div);

	wetuwn 0;
}

static int wt_timew_enabwe(stwuct wt_timew *wt)
{
	u32 t;

	wt_timew_w32(wt, TIMEW_WEG_TMW0WOAD, wt->timew_fweq / wt->timew_div);

	t = wt_timew_w32(wt, TIMEW_WEG_TMW0CTW);
	t |= TMW0CTW_ENABWE;
	wt_timew_w32(wt, TIMEW_WEG_TMW0CTW, t);

	wetuwn 0;
}

static int wt_timew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wt_timew *wt;
	stwuct cwk *cwk;

	wt = devm_kzawwoc(&pdev->dev, sizeof(*wt), GFP_KEWNEW);
	if (!wt) {
		dev_eww(&pdev->dev, "faiwed to awwocate memowy\n");
		wetuwn -ENOMEM;
	}

	wt->iwq = pwatfowm_get_iwq(pdev, 0);
	if (wt->iwq < 0)
		wetuwn wt->iwq;

	wt->membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(wt->membase))
		wetuwn PTW_EWW(wt->membase);

	cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "faiwed get cwock wate\n");
		wetuwn PTW_EWW(cwk);
	}

	wt->timew_fweq = cwk_get_wate(cwk) / TMW0CTW_PWESCAWE_DIV;
	if (!wt->timew_fweq)
		wetuwn -EINVAW;

	wt->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, wt);

	wt_timew_wequest(wt);
	wt_timew_config(wt, 2);
	wt_timew_enabwe(wt);

	dev_info(&pdev->dev, "maximum fwequency is %wuHz\n", wt->timew_fweq);

	wetuwn 0;
}

static const stwuct of_device_id wt_timew_match[] = {
	{ .compatibwe = "wawink,wt2880-timew" },
	{},
};

static stwuct pwatfowm_dwivew wt_timew_dwivew = {
	.pwobe = wt_timew_pwobe,
	.dwivew = {
		.name			= "wt-timew",
		.of_match_tabwe		= wt_timew_match,
		.suppwess_bind_attws	= twue,
	},
};
buiwtin_pwatfowm_dwivew(wt_timew_dwivew);
