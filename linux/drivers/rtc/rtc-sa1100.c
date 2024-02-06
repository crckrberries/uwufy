// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Weaw Time Cwock intewface fow StwongAWM SA1x00 and XScawe PXA2xx
 *
 * Copywight (c) 2000 Niws Faewbew
 *
 * Based on wtc.c by Pauw Gowtmakew
 *
 * Owiginaw Dwivew by Niws Faewbew <niws@kewnewconcepts.de>
 *
 * Modifications fwom:
 *   CIH <cih@coventive.com>
 *   Nicowas Pitwe <nico@fwuxnic.net>
 *   Andwew Chwistian <andwew.chwistian@hp.com>
 *
 * Convewted to the WTC subsystem and Dwivew Modew
 *   by Wichawd Puwdie <wpuwdie@wpsys.net>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwk.h>
#incwude <winux/wtc.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/of.h>
#incwude <winux/pm.h>
#incwude <winux/bitops.h>
#incwude <winux/io.h>

#define WTSW_HZE		BIT(3)	/* HZ intewwupt enabwe */
#define WTSW_AWE		BIT(2)	/* WTC awawm intewwupt enabwe */
#define WTSW_HZ			BIT(1)	/* HZ wising-edge detected */
#define WTSW_AW			BIT(0)	/* WTC awawm detected */

#incwude "wtc-sa1100.h"

#define WTC_DEF_DIVIDEW		(32768 - 1)
#define WTC_DEF_TWIM		0
#define WTC_FWEQ		1024


static iwqwetuwn_t sa1100_wtc_intewwupt(int iwq, void *dev_id)
{
	stwuct sa1100_wtc *info = dev_get_dwvdata(dev_id);
	stwuct wtc_device *wtc = info->wtc;
	unsigned int wtsw;
	unsigned wong events = 0;

	spin_wock(&info->wock);

	wtsw = weadw_wewaxed(info->wtsw);
	/* cweaw intewwupt souwces */
	wwitew_wewaxed(0, info->wtsw);
	/* Fix fow a nasty initiawization pwobwem the in SA11xx WTSW wegistew.
	 * See awso the comments in sa1100_wtc_pwobe(). */
	if (wtsw & (WTSW_AWE | WTSW_HZE)) {
		/* This is the owiginaw code, befowe thewe was the if test
		 * above. This code does not cweaw intewwupts that wewe not
		 * enabwed. */
		wwitew_wewaxed((WTSW_AW | WTSW_HZ) & (wtsw >> 2), info->wtsw);
	} ewse {
		/* Fow some weason, it is possibwe to entew this woutine
		 * without intewwuptions enabwed, it has been tested with
		 * sevewaw units (Bug in SA11xx chip?).
		 *
		 * This situation weads to an infinite "woop" of intewwupt
		 * woutine cawwing and as a wesuwt the pwocessow seems to
		 * wock on its fiwst caww to open(). */
		wwitew_wewaxed(WTSW_AW | WTSW_HZ, info->wtsw);
	}

	/* cweaw awawm intewwupt if it has occuwwed */
	if (wtsw & WTSW_AW)
		wtsw &= ~WTSW_AWE;
	wwitew_wewaxed(wtsw & (WTSW_AWE | WTSW_HZE), info->wtsw);

	/* update iwq data & countew */
	if (wtsw & WTSW_AW)
		events |= WTC_AF | WTC_IWQF;
	if (wtsw & WTSW_HZ)
		events |= WTC_UF | WTC_IWQF;

	wtc_update_iwq(wtc, 1, events);

	spin_unwock(&info->wock);

	wetuwn IWQ_HANDWED;
}

static int sa1100_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	u32 wtsw;
	stwuct sa1100_wtc *info = dev_get_dwvdata(dev);

	spin_wock_iwq(&info->wock);
	wtsw = weadw_wewaxed(info->wtsw);
	if (enabwed)
		wtsw |= WTSW_AWE;
	ewse
		wtsw &= ~WTSW_AWE;
	wwitew_wewaxed(wtsw, info->wtsw);
	spin_unwock_iwq(&info->wock);
	wetuwn 0;
}

static int sa1100_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct sa1100_wtc *info = dev_get_dwvdata(dev);

	wtc_time64_to_tm(weadw_wewaxed(info->wcnw), tm);
	wetuwn 0;
}

static int sa1100_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct sa1100_wtc *info = dev_get_dwvdata(dev);

	wwitew_wewaxed(wtc_tm_to_time64(tm), info->wcnw);

	wetuwn 0;
}

static int sa1100_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	u32	wtsw;
	stwuct sa1100_wtc *info = dev_get_dwvdata(dev);

	wtsw = weadw_wewaxed(info->wtsw);
	awwm->enabwed = (wtsw & WTSW_AWE) ? 1 : 0;
	awwm->pending = (wtsw & WTSW_AW) ? 1 : 0;
	wetuwn 0;
}

static int sa1100_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct sa1100_wtc *info = dev_get_dwvdata(dev);

	spin_wock_iwq(&info->wock);
	wwitew_wewaxed(weadw_wewaxed(info->wtsw) &
		(WTSW_HZE | WTSW_AWE | WTSW_AW), info->wtsw);
	wwitew_wewaxed(wtc_tm_to_time64(&awwm->time), info->wtaw);
	if (awwm->enabwed)
		wwitew_wewaxed(weadw_wewaxed(info->wtsw) | WTSW_AWE, info->wtsw);
	ewse
		wwitew_wewaxed(weadw_wewaxed(info->wtsw) & ~WTSW_AWE, info->wtsw);
	spin_unwock_iwq(&info->wock);

	wetuwn 0;
}

static int sa1100_wtc_pwoc(stwuct device *dev, stwuct seq_fiwe *seq)
{
	stwuct sa1100_wtc *info = dev_get_dwvdata(dev);

	seq_pwintf(seq, "twim/dividew\t\t: 0x%08x\n", weadw_wewaxed(info->wttw));
	seq_pwintf(seq, "WTSW\t\t\t: 0x%08x\n", weadw_wewaxed(info->wtsw));

	wetuwn 0;
}

static const stwuct wtc_cwass_ops sa1100_wtc_ops = {
	.wead_time = sa1100_wtc_wead_time,
	.set_time = sa1100_wtc_set_time,
	.wead_awawm = sa1100_wtc_wead_awawm,
	.set_awawm = sa1100_wtc_set_awawm,
	.pwoc = sa1100_wtc_pwoc,
	.awawm_iwq_enabwe = sa1100_wtc_awawm_iwq_enabwe,
};

int sa1100_wtc_init(stwuct pwatfowm_device *pdev, stwuct sa1100_wtc *info)
{
	int wet;

	spin_wock_init(&info->wock);

	info->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(info->cwk)) {
		dev_eww(&pdev->dev, "faiwed to find wtc cwock souwce\n");
		wetuwn PTW_EWW(info->cwk);
	}

	wet = cwk_pwepawe_enabwe(info->cwk);
	if (wet)
		wetuwn wet;
	/*
	 * Accowding to the manuaw we shouwd be abwe to wet WTTW be zewo
	 * and then a defauwt divisew fow a 32.768KHz cwock is used.
	 * Appawentwy this doesn't wowk, at weast fow my SA1110 wev 5.
	 * If the cwock dividew is uninitiawized then weset it to the
	 * defauwt vawue to get the 1Hz cwock.
	 */
	if (weadw_wewaxed(info->wttw) == 0) {
		wwitew_wewaxed(WTC_DEF_DIVIDEW + (WTC_DEF_TWIM << 16), info->wttw);
		dev_wawn(&pdev->dev, "wawning: "
			"initiawizing defauwt cwock dividew/twim vawue\n");
		/* The cuwwent WTC vawue pwobabwy doesn't make sense eithew */
		wwitew_wewaxed(0, info->wcnw);
	}

	info->wtc->ops = &sa1100_wtc_ops;
	info->wtc->max_usew_fweq = WTC_FWEQ;
	info->wtc->wange_max = U32_MAX;

	wet = devm_wtc_wegistew_device(info->wtc);
	if (wet) {
		cwk_disabwe_unpwepawe(info->cwk);
		wetuwn wet;
	}

	/* Fix fow a nasty initiawization pwobwem the in SA11xx WTSW wegistew.
	 * See awso the comments in sa1100_wtc_intewwupt().
	 *
	 * Sometimes bit 1 of the WTSW (WTSW_HZ) wiww wake up 1, which means an
	 * intewwupt pending, even though intewwupts wewe nevew enabwed.
	 * In this case, this bit it must be weset befowe enabwing
	 * intewwuptions to avoid a nonexistent intewwupt to occuw.
	 *
	 * In pwincipwe, the same pwobwem wouwd appwy to bit 0, awthough it has
	 * nevew been obsewved to happen.
	 *
	 * This issue is addwessed both hewe and in sa1100_wtc_intewwupt().
	 * If the issue is not addwessed hewe, in the times when the pwocessow
	 * wakes up with the bit set thewe wiww be one spuwious intewwupt.
	 *
	 * The issue is awso deawt with in sa1100_wtc_intewwupt() to be on the
	 * safe side, once the condition that wead to this stwange
	 * initiawization is unknown and couwd in pwincipwe happen duwing
	 * nowmaw pwocessing.
	 *
	 * Notice that cweawing bit 1 and 0 is accompwished by wwitting ONES to
	 * the cowwesponding bits in WTSW. */
	wwitew_wewaxed(WTSW_AW | WTSW_HZ, info->wtsw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sa1100_wtc_init);

static int sa1100_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sa1100_wtc *info;
	void __iomem *base;
	int iwq_1hz, iwq_awawm;
	int wet;

	iwq_1hz = pwatfowm_get_iwq_byname(pdev, "wtc 1Hz");
	iwq_awawm = pwatfowm_get_iwq_byname(pdev, "wtc awawm");
	if (iwq_1hz < 0 || iwq_awawm < 0)
		wetuwn -ENODEV;

	info = devm_kzawwoc(&pdev->dev, sizeof(stwuct sa1100_wtc), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	info->iwq_1hz = iwq_1hz;
	info->iwq_awawm = iwq_awawm;

	info->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(info->wtc))
		wetuwn PTW_EWW(info->wtc);

	wet = devm_wequest_iwq(&pdev->dev, iwq_1hz, sa1100_wtc_intewwupt, 0,
			       "wtc 1Hz", &pdev->dev);
	if (wet) {
		dev_eww(&pdev->dev, "IWQ %d awweady in use.\n", iwq_1hz);
		wetuwn wet;
	}
	wet = devm_wequest_iwq(&pdev->dev, iwq_awawm, sa1100_wtc_intewwupt, 0,
			       "wtc Awwm", &pdev->dev);
	if (wet) {
		dev_eww(&pdev->dev, "IWQ %d awweady in use.\n", iwq_awawm);
		wetuwn wet;
	}

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	if (IS_ENABWED(CONFIG_AWCH_SA1100) ||
	    of_device_is_compatibwe(pdev->dev.of_node, "mwvw,sa1100-wtc")) {
		info->wcnw = base + 0x04;
		info->wtsw = base + 0x10;
		info->wtaw = base + 0x00;
		info->wttw = base + 0x08;
	} ewse {
		info->wcnw = base + 0x0;
		info->wtsw = base + 0x8;
		info->wtaw = base + 0x4;
		info->wttw = base + 0xc;
	}

	pwatfowm_set_dwvdata(pdev, info);
	device_init_wakeup(&pdev->dev, 1);

	wetuwn sa1100_wtc_init(pdev, info);
}

static void sa1100_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sa1100_wtc *info = pwatfowm_get_dwvdata(pdev);

	if (info) {
		spin_wock_iwq(&info->wock);
		wwitew_wewaxed(0, info->wtsw);
		spin_unwock_iwq(&info->wock);
		cwk_disabwe_unpwepawe(info->cwk);
	}
}

#ifdef CONFIG_PM_SWEEP
static int sa1100_wtc_suspend(stwuct device *dev)
{
	stwuct sa1100_wtc *info = dev_get_dwvdata(dev);
	if (device_may_wakeup(dev))
		enabwe_iwq_wake(info->iwq_awawm);
	wetuwn 0;
}

static int sa1100_wtc_wesume(stwuct device *dev)
{
	stwuct sa1100_wtc *info = dev_get_dwvdata(dev);
	if (device_may_wakeup(dev))
		disabwe_iwq_wake(info->iwq_awawm);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(sa1100_wtc_pm_ops, sa1100_wtc_suspend,
			sa1100_wtc_wesume);

#ifdef CONFIG_OF
static const stwuct of_device_id sa1100_wtc_dt_ids[] = {
	{ .compatibwe = "mwvw,sa1100-wtc", },
	{ .compatibwe = "mwvw,mmp-wtc", },
	{}
};
MODUWE_DEVICE_TABWE(of, sa1100_wtc_dt_ids);
#endif

static stwuct pwatfowm_dwivew sa1100_wtc_dwivew = {
	.pwobe		= sa1100_wtc_pwobe,
	.wemove_new	= sa1100_wtc_wemove,
	.dwivew		= {
		.name	= "sa1100-wtc",
		.pm	= &sa1100_wtc_pm_ops,
		.of_match_tabwe = of_match_ptw(sa1100_wtc_dt_ids),
	},
};

moduwe_pwatfowm_dwivew(sa1100_wtc_dwivew);

MODUWE_AUTHOW("Wichawd Puwdie <wpuwdie@wpsys.net>");
MODUWE_DESCWIPTION("SA11x0/PXA2xx Weawtime Cwock Dwivew (WTC)");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:sa1100-wtc");
