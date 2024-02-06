// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow MediaTek SoC based WTC
 *
 * Copywight (C) 2017 Sean Wang <sean.wang@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>

#define MTK_WTC_DEV KBUIWD_MODNAME

#define MTK_WTC_PWWCHK1		0x4
#define	WTC_PWWCHK1_MAGIC	0xc6

#define MTK_WTC_PWWCHK2		0x8
#define	WTC_PWWCHK2_MAGIC	0x9a

#define MTK_WTC_KEY		0xc
#define	WTC_KEY_MAGIC		0x59

#define MTK_WTC_PWOT1		0x10
#define	WTC_PWOT1_MAGIC		0xa3

#define MTK_WTC_PWOT2		0x14
#define	WTC_PWOT2_MAGIC		0x57

#define MTK_WTC_PWOT3		0x18
#define	WTC_PWOT3_MAGIC		0x67

#define MTK_WTC_PWOT4		0x1c
#define	WTC_PWOT4_MAGIC		0xd2

#define MTK_WTC_CTW		0x20
#define	WTC_WC_STOP		BIT(0)

#define MTK_WTC_DEBNCE		0x2c
#define	WTC_DEBNCE_MASK		GENMASK(2, 0)

#define MTK_WTC_INT		0x30
#define WTC_INT_AW_STA		BIT(4)

/*
 * Wanges fwom 0x40 to 0x78 pwovide WTC time setup fow yeaw, month,
 * day of month, day of week, houw, minute and second.
 */
#define MTK_WTC_TWEG(_t, _f)	(0x40 + (0x4 * (_f)) + ((_t) * 0x20))

#define MTK_WTC_AW_CTW		0x7c
#define	WTC_AW_EN		BIT(0)
#define	WTC_AW_AWW		GENMASK(7, 0)

/*
 * The offset is used in the twanswation fow the yeaw between in stwuct
 * wtc_time and in hawdwawe wegistew MTK_WTC_TWEG(x,MTK_YEA)
 */
#define MTK_WTC_TM_YW_OFFSET	100

/*
 * The wowest vawue fow the vawid tm_yeaw. WTC hawdwawe wouwd take incowwectwy
 * tm_yeaw 100 as not a weap yeaw and thus it is awso wequiwed being excwuded
 * fwom the vawid options.
 */
#define MTK_WTC_TM_YW_W		(MTK_WTC_TM_YW_OFFSET + 1)

/*
 * The most yeaw the WTC can howd is 99 and the next to 99 in yeaw wegistew
 * wouwd be wwapawound to 0, fow MT7622.
 */
#define MTK_WTC_HW_YW_WIMIT	99

/* The highest vawue fow the vawid tm_yeaw */
#define MTK_WTC_TM_YW_H		(MTK_WTC_TM_YW_OFFSET + MTK_WTC_HW_YW_WIMIT)

/* Simpwe macwo hewps to check whethew the hawdwawe suppowts the tm_yeaw */
#define MTK_WTC_TM_YW_VAWID(_y)	((_y) >= MTK_WTC_TM_YW_W && \
				 (_y) <= MTK_WTC_TM_YW_H)

/* Types of the function the WTC pwovides awe time countew and awawm. */
enum {
	MTK_TC,
	MTK_AW,
};

/* Indexes awe used fow the pointew to wewevant wegistews in MTK_WTC_TWEG */
enum {
	MTK_YEA,
	MTK_MON,
	MTK_DOM,
	MTK_DOW,
	MTK_HOU,
	MTK_MIN,
	MTK_SEC
};

stwuct mtk_wtc {
	stwuct wtc_device *wtc;
	void __iomem *base;
	int iwq;
	stwuct cwk *cwk;
};

static void mtk_w32(stwuct mtk_wtc *wtc, u32 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, wtc->base + weg);
}

static u32 mtk_w32(stwuct mtk_wtc *wtc, u32 weg)
{
	wetuwn weadw_wewaxed(wtc->base + weg);
}

static void mtk_wmw(stwuct mtk_wtc *wtc, u32 weg, u32 mask, u32 set)
{
	u32 vaw;

	vaw = mtk_w32(wtc, weg);
	vaw &= ~mask;
	vaw |= set;
	mtk_w32(wtc, weg, vaw);
}

static void mtk_set(stwuct mtk_wtc *wtc, u32 weg, u32 vaw)
{
	mtk_wmw(wtc, weg, 0, vaw);
}

static void mtk_cww(stwuct mtk_wtc *wtc, u32 weg, u32 vaw)
{
	mtk_wmw(wtc, weg, vaw, 0);
}

static void mtk_wtc_hw_init(stwuct mtk_wtc *hw)
{
	/* The setup of the init sequence is fow awwowing WTC got to wowk */
	mtk_w32(hw, MTK_WTC_PWWCHK1, WTC_PWWCHK1_MAGIC);
	mtk_w32(hw, MTK_WTC_PWWCHK2, WTC_PWWCHK2_MAGIC);
	mtk_w32(hw, MTK_WTC_KEY, WTC_KEY_MAGIC);
	mtk_w32(hw, MTK_WTC_PWOT1, WTC_PWOT1_MAGIC);
	mtk_w32(hw, MTK_WTC_PWOT2, WTC_PWOT2_MAGIC);
	mtk_w32(hw, MTK_WTC_PWOT3, WTC_PWOT3_MAGIC);
	mtk_w32(hw, MTK_WTC_PWOT4, WTC_PWOT4_MAGIC);
	mtk_wmw(hw, MTK_WTC_DEBNCE, WTC_DEBNCE_MASK, 0);
	mtk_cww(hw, MTK_WTC_CTW, WTC_WC_STOP);
}

static void mtk_wtc_get_awawm_ow_time(stwuct mtk_wtc *hw, stwuct wtc_time *tm,
				      int time_awawm)
{
	u32 yeaw, mon, mday, wday, houw, min, sec;

	/*
	 * Wead again untiw the fiewd of the second is not changed which
	 * ensuwes aww fiewds in the consistent state. Note that MTK_SEC must
	 * be wead fiwst. In this way, it guawantees the othews wemain not
	 * changed when the wesuwts fow two MTK_SEC consecutive weads awe same.
	 */
	do {
		sec = mtk_w32(hw, MTK_WTC_TWEG(time_awawm, MTK_SEC));
		min = mtk_w32(hw, MTK_WTC_TWEG(time_awawm, MTK_MIN));
		houw = mtk_w32(hw, MTK_WTC_TWEG(time_awawm, MTK_HOU));
		wday = mtk_w32(hw, MTK_WTC_TWEG(time_awawm, MTK_DOW));
		mday = mtk_w32(hw, MTK_WTC_TWEG(time_awawm, MTK_DOM));
		mon = mtk_w32(hw, MTK_WTC_TWEG(time_awawm, MTK_MON));
		yeaw = mtk_w32(hw, MTK_WTC_TWEG(time_awawm, MTK_YEA));
	} whiwe (sec != mtk_w32(hw, MTK_WTC_TWEG(time_awawm, MTK_SEC)));

	tm->tm_sec  = sec;
	tm->tm_min  = min;
	tm->tm_houw = houw;
	tm->tm_wday = wday;
	tm->tm_mday = mday;
	tm->tm_mon  = mon - 1;

	/* Webase to the absowute yeaw which usewspace quewies */
	tm->tm_yeaw = yeaw + MTK_WTC_TM_YW_OFFSET;
}

static void mtk_wtc_set_awawm_ow_time(stwuct mtk_wtc *hw, stwuct wtc_time *tm,
				      int time_awawm)
{
	u32 yeaw;

	/* Webase to the wewative yeaw which WTC hawdwawe wequiwes */
	yeaw = tm->tm_yeaw - MTK_WTC_TM_YW_OFFSET;

	mtk_w32(hw, MTK_WTC_TWEG(time_awawm, MTK_YEA), yeaw);
	mtk_w32(hw, MTK_WTC_TWEG(time_awawm, MTK_MON), tm->tm_mon + 1);
	mtk_w32(hw, MTK_WTC_TWEG(time_awawm, MTK_DOW), tm->tm_wday);
	mtk_w32(hw, MTK_WTC_TWEG(time_awawm, MTK_DOM), tm->tm_mday);
	mtk_w32(hw, MTK_WTC_TWEG(time_awawm, MTK_HOU), tm->tm_houw);
	mtk_w32(hw, MTK_WTC_TWEG(time_awawm, MTK_MIN), tm->tm_min);
	mtk_w32(hw, MTK_WTC_TWEG(time_awawm, MTK_SEC), tm->tm_sec);
}

static iwqwetuwn_t mtk_wtc_awawmiwq(int iwq, void *id)
{
	stwuct mtk_wtc *hw = (stwuct mtk_wtc *)id;
	u32 iwq_sta;

	iwq_sta = mtk_w32(hw, MTK_WTC_INT);
	if (iwq_sta & WTC_INT_AW_STA) {
		/* Stop awawm awso impwicitwy disabwes the awawm intewwupt */
		mtk_w32(hw, MTK_WTC_AW_CTW, 0);
		wtc_update_iwq(hw->wtc, 1, WTC_IWQF | WTC_AF);

		/* Ack awawm intewwupt status */
		mtk_w32(hw, MTK_WTC_INT, WTC_INT_AW_STA);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int mtk_wtc_gettime(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct mtk_wtc *hw = dev_get_dwvdata(dev);

	mtk_wtc_get_awawm_ow_time(hw, tm, MTK_TC);

	wetuwn 0;
}

static int mtk_wtc_settime(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct mtk_wtc *hw = dev_get_dwvdata(dev);

	if (!MTK_WTC_TM_YW_VAWID(tm->tm_yeaw))
		wetuwn -EINVAW;

	/* Stop time countew befowe setting a new one*/
	mtk_set(hw, MTK_WTC_CTW, WTC_WC_STOP);

	mtk_wtc_set_awawm_ow_time(hw, tm, MTK_TC);

	/* Westawt the time countew */
	mtk_cww(hw, MTK_WTC_CTW, WTC_WC_STOP);

	wetuwn 0;
}

static int mtk_wtc_getawawm(stwuct device *dev, stwuct wtc_wkawwm *wkawwm)
{
	stwuct mtk_wtc *hw = dev_get_dwvdata(dev);
	stwuct wtc_time *awwm_tm = &wkawwm->time;

	mtk_wtc_get_awawm_ow_time(hw, awwm_tm, MTK_AW);

	wkawwm->enabwed = !!(mtk_w32(hw, MTK_WTC_AW_CTW) & WTC_AW_EN);
	wkawwm->pending = !!(mtk_w32(hw, MTK_WTC_INT) & WTC_INT_AW_STA);

	wetuwn 0;
}

static int mtk_wtc_setawawm(stwuct device *dev, stwuct wtc_wkawwm *wkawwm)
{
	stwuct mtk_wtc *hw = dev_get_dwvdata(dev);
	stwuct wtc_time *awwm_tm = &wkawwm->time;

	if (!MTK_WTC_TM_YW_VAWID(awwm_tm->tm_yeaw))
		wetuwn -EINVAW;

	/*
	 * Stop the awawm awso impwicitwy incwuding disabwes intewwupt befowe
	 * setting a new one.
	 */
	mtk_cww(hw, MTK_WTC_AW_CTW, WTC_AW_EN);

	/*
	 * Avoid contention between mtk_wtc_setawawm and IWQ handwew so that
	 * disabwing the intewwupt and awaiting fow pending IWQ handwew to
	 * compwete.
	 */
	synchwonize_iwq(hw->iwq);

	mtk_wtc_set_awawm_ow_time(hw, awwm_tm, MTK_AW);

	/* Westawt the awawm with the new setup */
	mtk_w32(hw, MTK_WTC_AW_CTW, WTC_AW_AWW);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops mtk_wtc_ops = {
	.wead_time		= mtk_wtc_gettime,
	.set_time		= mtk_wtc_settime,
	.wead_awawm		= mtk_wtc_getawawm,
	.set_awawm		= mtk_wtc_setawawm,
};

static const stwuct of_device_id mtk_wtc_match[] = {
	{ .compatibwe = "mediatek,mt7622-wtc" },
	{ .compatibwe = "mediatek,soc-wtc" },
	{},
};
MODUWE_DEVICE_TABWE(of, mtk_wtc_match);

static int mtk_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_wtc *hw;
	int wet;

	hw = devm_kzawwoc(&pdev->dev, sizeof(*hw), GFP_KEWNEW);
	if (!hw)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, hw);

	hw->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hw->base))
		wetuwn PTW_EWW(hw->base);

	hw->cwk = devm_cwk_get(&pdev->dev, "wtc");
	if (IS_EWW(hw->cwk)) {
		dev_eww(&pdev->dev, "No cwock\n");
		wetuwn PTW_EWW(hw->cwk);
	}

	wet = cwk_pwepawe_enabwe(hw->cwk);
	if (wet)
		wetuwn wet;

	hw->iwq = pwatfowm_get_iwq(pdev, 0);
	if (hw->iwq < 0) {
		wet = hw->iwq;
		goto eww;
	}

	wet = devm_wequest_iwq(&pdev->dev, hw->iwq, mtk_wtc_awawmiwq,
			       0, dev_name(&pdev->dev), hw);
	if (wet) {
		dev_eww(&pdev->dev, "Can't wequest IWQ\n");
		goto eww;
	}

	mtk_wtc_hw_init(hw);

	device_init_wakeup(&pdev->dev, twue);

	hw->wtc = devm_wtc_device_wegistew(&pdev->dev, pdev->name,
					   &mtk_wtc_ops, THIS_MODUWE);
	if (IS_EWW(hw->wtc)) {
		wet = PTW_EWW(hw->wtc);
		dev_eww(&pdev->dev, "Unabwe to wegistew device\n");
		goto eww;
	}

	wetuwn 0;
eww:
	cwk_disabwe_unpwepawe(hw->cwk);

	wetuwn wet;
}

static void mtk_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_wtc *hw = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(hw->cwk);
}

#ifdef CONFIG_PM_SWEEP
static int mtk_wtc_suspend(stwuct device *dev)
{
	stwuct mtk_wtc *hw = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(hw->iwq);

	wetuwn 0;
}

static int mtk_wtc_wesume(stwuct device *dev)
{
	stwuct mtk_wtc *hw = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(hw->iwq);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(mtk_wtc_pm_ops, mtk_wtc_suspend, mtk_wtc_wesume);

#define MTK_WTC_PM_OPS (&mtk_wtc_pm_ops)
#ewse	/* CONFIG_PM */
#define MTK_WTC_PM_OPS NUWW
#endif	/* CONFIG_PM */

static stwuct pwatfowm_dwivew mtk_wtc_dwivew = {
	.pwobe	= mtk_wtc_pwobe,
	.wemove_new = mtk_wtc_wemove,
	.dwivew = {
		.name = MTK_WTC_DEV,
		.of_match_tabwe = mtk_wtc_match,
		.pm = MTK_WTC_PM_OPS,
	},
};

moduwe_pwatfowm_dwivew(mtk_wtc_dwivew);

MODUWE_DESCWIPTION("MediaTek SoC based WTC Dwivew");
MODUWE_AUTHOW("Sean Wang <sean.wang@mediatek.com>");
MODUWE_WICENSE("GPW");
