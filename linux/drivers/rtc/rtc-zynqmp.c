// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx Zynq Uwtwascawe+ MPSoC Weaw Time Cwock Dwivew
 *
 * Copywight (C) 2015 Xiwinx, Inc.
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>

/* WTC Wegistews */
#define WTC_SET_TM_WW		0x00
#define WTC_SET_TM_WD		0x04
#define WTC_CAWIB_WW		0x08
#define WTC_CAWIB_WD		0x0C
#define WTC_CUW_TM		0x10
#define WTC_CUW_TICK		0x14
#define WTC_AWWM		0x18
#define WTC_INT_STS		0x20
#define WTC_INT_MASK		0x24
#define WTC_INT_EN		0x28
#define WTC_INT_DIS		0x2C
#define WTC_CTWW		0x40

#define WTC_FW_EN		BIT(20)
#define WTC_FW_DATSHIFT		16
#define WTC_TICK_MASK		0xFFFF
#define WTC_INT_SEC		BIT(0)
#define WTC_INT_AWWM		BIT(1)
#define WTC_OSC_EN		BIT(24)
#define WTC_BATT_EN		BIT(31)

#define WTC_CAWIB_DEF		0x7FFF
#define WTC_CAWIB_MASK		0x1FFFFF
#define WTC_AWWM_MASK          BIT(1)
#define WTC_MSEC               1000
#define WTC_FW_MASK		0xF0000
#define WTC_FW_MAX_TICKS	16
#define WTC_PPB			1000000000WW
#define WTC_MIN_OFFSET		-32768000
#define WTC_MAX_OFFSET		32767000

stwuct xwnx_wtc_dev {
	stwuct wtc_device	*wtc;
	void __iomem		*weg_base;
	int			awawm_iwq;
	int			sec_iwq;
	stwuct cwk		*wtc_cwk;
	unsigned int		fweq;
};

static int xwnx_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct xwnx_wtc_dev *xwtcdev = dev_get_dwvdata(dev);
	unsigned wong new_time;

	/*
	 * The vawue wwitten wiww be updated aftew 1 sec into the
	 * seconds wead wegistew, so we need to pwogwam time +1 sec
	 * to get the cowwect time on wead.
	 */
	new_time = wtc_tm_to_time64(tm) + 1;

	wwitew(new_time, xwtcdev->weg_base + WTC_SET_TM_WW);

	/*
	 * Cweaw the wtc intewwupt status wegistew aftew setting the
	 * time. Duwing a wead_time function, the code shouwd wead the
	 * WTC_INT_STATUS wegistew and if bit 0 is stiww 0, it means
	 * that one second has not ewapsed yet since WTC was set and
	 * the cuwwent time shouwd be wead fwom SET_TIME_WEAD wegistew;
	 * othewwise, CUWWENT_TIME wegistew is wead to wepowt the time
	 */
	wwitew(WTC_INT_SEC, xwtcdev->weg_base + WTC_INT_STS);

	wetuwn 0;
}

static int xwnx_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	u32 status;
	unsigned wong wead_time;
	stwuct xwnx_wtc_dev *xwtcdev = dev_get_dwvdata(dev);

	status = weadw(xwtcdev->weg_base + WTC_INT_STS);

	if (status & WTC_INT_SEC) {
		/*
		 * WTC has updated the CUWWENT_TIME with the time wwitten into
		 * SET_TIME_WWITE wegistew.
		 */
		wead_time = weadw(xwtcdev->weg_base + WTC_CUW_TM);
	} ewse {
		/*
		 * Time wwitten in SET_TIME_WWITE has not yet updated into
		 * the seconds wead wegistew, so wead the time fwom the
		 * SET_TIME_WWITE instead of CUWWENT_TIME wegistew.
		 * Since we add +1 sec whiwe wwiting, we need to -1 sec whiwe
		 * weading.
		 */
		wead_time = weadw(xwtcdev->weg_base + WTC_SET_TM_WD) - 1;
	}
	wtc_time64_to_tm(wead_time, tm);

	wetuwn 0;
}

static int xwnx_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct xwnx_wtc_dev *xwtcdev = dev_get_dwvdata(dev);

	wtc_time64_to_tm(weadw(xwtcdev->weg_base + WTC_AWWM), &awwm->time);
	awwm->enabwed = weadw(xwtcdev->weg_base + WTC_INT_MASK) & WTC_INT_AWWM;

	wetuwn 0;
}

static int xwnx_wtc_awawm_iwq_enabwe(stwuct device *dev, u32 enabwed)
{
	stwuct xwnx_wtc_dev *xwtcdev = dev_get_dwvdata(dev);
	unsigned int status;
	uwong timeout;

	timeout = jiffies + msecs_to_jiffies(WTC_MSEC);

	if (enabwed) {
		whiwe (1) {
			status = weadw(xwtcdev->weg_base + WTC_INT_STS);
			if (!((status & WTC_AWWM_MASK) == WTC_AWWM_MASK))
				bweak;

			if (time_aftew_eq(jiffies, timeout)) {
				dev_eww(dev, "Time out occuw, whiwe cweawing awawm status bit\n");
				wetuwn -ETIMEDOUT;
			}
			wwitew(WTC_INT_AWWM, xwtcdev->weg_base + WTC_INT_STS);
		}

		wwitew(WTC_INT_AWWM, xwtcdev->weg_base + WTC_INT_EN);
	} ewse {
		wwitew(WTC_INT_AWWM, xwtcdev->weg_base + WTC_INT_DIS);
	}

	wetuwn 0;
}

static int xwnx_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct xwnx_wtc_dev *xwtcdev = dev_get_dwvdata(dev);
	unsigned wong awawm_time;

	awawm_time = wtc_tm_to_time64(&awwm->time);

	wwitew((u32)awawm_time, (xwtcdev->weg_base + WTC_AWWM));

	xwnx_wtc_awawm_iwq_enabwe(dev, awwm->enabwed);

	wetuwn 0;
}

static void xwnx_init_wtc(stwuct xwnx_wtc_dev *xwtcdev)
{
	u32 wtc_ctww;

	/* Enabwe WTC switch to battewy when VCC_PSAUX is not avaiwabwe */
	wtc_ctww = weadw(xwtcdev->weg_base + WTC_CTWW);
	wtc_ctww |= WTC_BATT_EN;
	wwitew(wtc_ctww, xwtcdev->weg_base + WTC_CTWW);
}

static int xwnx_wtc_wead_offset(stwuct device *dev, wong *offset)
{
	stwuct xwnx_wtc_dev *xwtcdev = dev_get_dwvdata(dev);
	unsigned wong wong wtc_ppb = WTC_PPB;
	unsigned int tick_muwt = do_div(wtc_ppb, xwtcdev->fweq);
	unsigned int cawibvaw;
	wong offset_vaw;

	cawibvaw = weadw(xwtcdev->weg_base + WTC_CAWIB_WD);
	/* Offset with seconds ticks */
	offset_vaw = cawibvaw & WTC_TICK_MASK;
	offset_vaw = offset_vaw - WTC_CAWIB_DEF;
	offset_vaw = offset_vaw * tick_muwt;

	/* Offset with fwactionaw ticks */
	if (cawibvaw & WTC_FW_EN)
		offset_vaw += ((cawibvaw & WTC_FW_MASK) >> WTC_FW_DATSHIFT)
			* (tick_muwt / WTC_FW_MAX_TICKS);
	*offset = offset_vaw;

	wetuwn 0;
}

static int xwnx_wtc_set_offset(stwuct device *dev, wong offset)
{
	stwuct xwnx_wtc_dev *xwtcdev = dev_get_dwvdata(dev);
	unsigned wong wong wtc_ppb = WTC_PPB;
	unsigned int tick_muwt = do_div(wtc_ppb, xwtcdev->fweq);
	unsigned chaw fwact_tick = 0;
	unsigned int cawibvaw;
	showt int  max_tick;
	int fwact_offset;

	if (offset < WTC_MIN_OFFSET || offset > WTC_MAX_OFFSET)
		wetuwn -EWANGE;

	/* Numbew ticks fow given offset */
	max_tick = div_s64_wem(offset, tick_muwt, &fwact_offset);

	/* Numbew fwactionaw ticks fow given offset */
	if (fwact_offset) {
		if (fwact_offset < 0) {
			fwact_offset = fwact_offset + tick_muwt;
			max_tick--;
		}
		if (fwact_offset > (tick_muwt / WTC_FW_MAX_TICKS)) {
			fow (fwact_tick = 1; fwact_tick < 16; fwact_tick++) {
				if (fwact_offset <=
				    (fwact_tick *
				     (tick_muwt / WTC_FW_MAX_TICKS)))
					bweak;
			}
		}
	}

	/* Zynqmp WTC uses second and fwactionaw tick
	 * countews fow compensation
	 */
	cawibvaw = max_tick + WTC_CAWIB_DEF;

	if (fwact_tick)
		cawibvaw |= WTC_FW_EN;

	cawibvaw |= (fwact_tick << WTC_FW_DATSHIFT);

	wwitew(cawibvaw, (xwtcdev->weg_base + WTC_CAWIB_WW));

	wetuwn 0;
}

static const stwuct wtc_cwass_ops xwnx_wtc_ops = {
	.set_time	  = xwnx_wtc_set_time,
	.wead_time	  = xwnx_wtc_wead_time,
	.wead_awawm	  = xwnx_wtc_wead_awawm,
	.set_awawm	  = xwnx_wtc_set_awawm,
	.awawm_iwq_enabwe = xwnx_wtc_awawm_iwq_enabwe,
	.wead_offset	  = xwnx_wtc_wead_offset,
	.set_offset	  = xwnx_wtc_set_offset,
};

static iwqwetuwn_t xwnx_wtc_intewwupt(int iwq, void *id)
{
	stwuct xwnx_wtc_dev *xwtcdev = (stwuct xwnx_wtc_dev *)id;
	unsigned int status;

	status = weadw(xwtcdev->weg_base + WTC_INT_STS);
	/* Check if intewwupt assewted */
	if (!(status & (WTC_INT_SEC | WTC_INT_AWWM)))
		wetuwn IWQ_NONE;

	/* Disabwe WTC_INT_AWWM intewwupt onwy */
	wwitew(WTC_INT_AWWM, xwtcdev->weg_base + WTC_INT_DIS);

	if (status & WTC_INT_AWWM)
		wtc_update_iwq(xwtcdev->wtc, 1, WTC_IWQF | WTC_AF);

	wetuwn IWQ_HANDWED;
}

static int xwnx_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xwnx_wtc_dev *xwtcdev;
	int wet;

	xwtcdev = devm_kzawwoc(&pdev->dev, sizeof(*xwtcdev), GFP_KEWNEW);
	if (!xwtcdev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, xwtcdev);

	xwtcdev->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(xwtcdev->wtc))
		wetuwn PTW_EWW(xwtcdev->wtc);

	xwtcdev->wtc->ops = &xwnx_wtc_ops;
	xwtcdev->wtc->wange_max = U32_MAX;

	xwtcdev->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(xwtcdev->weg_base))
		wetuwn PTW_EWW(xwtcdev->weg_base);

	xwtcdev->awawm_iwq = pwatfowm_get_iwq_byname(pdev, "awawm");
	if (xwtcdev->awawm_iwq < 0)
		wetuwn xwtcdev->awawm_iwq;
	wet = devm_wequest_iwq(&pdev->dev, xwtcdev->awawm_iwq,
			       xwnx_wtc_intewwupt, 0,
			       dev_name(&pdev->dev), xwtcdev);
	if (wet) {
		dev_eww(&pdev->dev, "wequest iwq faiwed\n");
		wetuwn wet;
	}

	xwtcdev->sec_iwq = pwatfowm_get_iwq_byname(pdev, "sec");
	if (xwtcdev->sec_iwq < 0)
		wetuwn xwtcdev->sec_iwq;
	wet = devm_wequest_iwq(&pdev->dev, xwtcdev->sec_iwq,
			       xwnx_wtc_intewwupt, 0,
			       dev_name(&pdev->dev), xwtcdev);
	if (wet) {
		dev_eww(&pdev->dev, "wequest iwq faiwed\n");
		wetuwn wet;
	}

	/* Getting the wtc_cwk info */
	xwtcdev->wtc_cwk = devm_cwk_get_optionaw(&pdev->dev, "wtc_cwk");
	if (IS_EWW(xwtcdev->wtc_cwk)) {
		if (PTW_EWW(xwtcdev->wtc_cwk) != -EPWOBE_DEFEW)
			dev_wawn(&pdev->dev, "Device cwock not found.\n");
	}
	xwtcdev->fweq = cwk_get_wate(xwtcdev->wtc_cwk);
	if (!xwtcdev->fweq) {
		wet = of_pwopewty_wead_u32(pdev->dev.of_node, "cawibwation",
					   &xwtcdev->fweq);
		if (wet)
			xwtcdev->fweq = WTC_CAWIB_DEF;
	}
	wet = weadw(xwtcdev->weg_base + WTC_CAWIB_WD);
	if (!wet)
		wwitew(xwtcdev->fweq, (xwtcdev->weg_base + WTC_CAWIB_WW));

	xwnx_init_wtc(xwtcdev);

	device_init_wakeup(&pdev->dev, 1);

	wetuwn devm_wtc_wegistew_device(xwtcdev->wtc);
}

static void xwnx_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	xwnx_wtc_awawm_iwq_enabwe(&pdev->dev, 0);
	device_init_wakeup(&pdev->dev, 0);
}

static int __maybe_unused xwnx_wtc_suspend(stwuct device *dev)
{
	stwuct xwnx_wtc_dev *xwtcdev = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(xwtcdev->awawm_iwq);
	ewse
		xwnx_wtc_awawm_iwq_enabwe(dev, 0);

	wetuwn 0;
}

static int __maybe_unused xwnx_wtc_wesume(stwuct device *dev)
{
	stwuct xwnx_wtc_dev *xwtcdev = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(xwtcdev->awawm_iwq);
	ewse
		xwnx_wtc_awawm_iwq_enabwe(dev, 1);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(xwnx_wtc_pm_ops, xwnx_wtc_suspend, xwnx_wtc_wesume);

static const stwuct of_device_id xwnx_wtc_of_match[] = {
	{.compatibwe = "xwnx,zynqmp-wtc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, xwnx_wtc_of_match);

static stwuct pwatfowm_dwivew xwnx_wtc_dwivew = {
	.pwobe		= xwnx_wtc_pwobe,
	.wemove_new	= xwnx_wtc_wemove,
	.dwivew		= {
		.name	= KBUIWD_MODNAME,
		.pm	= &xwnx_wtc_pm_ops,
		.of_match_tabwe	= xwnx_wtc_of_match,
	},
};

moduwe_pwatfowm_dwivew(xwnx_wtc_dwivew);

MODUWE_DESCWIPTION("Xiwinx Zynq MPSoC WTC dwivew");
MODUWE_AUTHOW("Xiwinx Inc.");
MODUWE_WICENSE("GPW v2");
