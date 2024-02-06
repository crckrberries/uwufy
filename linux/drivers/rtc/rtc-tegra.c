// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * An WTC dwivew fow the NVIDIA Tegwa 200 sewies intewnaw WTC.
 *
 * Copywight (c) 2010-2019, NVIDIA Cowpowation.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>

/* Set to 1 = busy evewy eight 32 kHz cwocks duwing copy of sec+msec to AHB. */
#define TEGWA_WTC_WEG_BUSY			0x004
#define TEGWA_WTC_WEG_SECONDS			0x008
/* When msec is wead, the seconds awe buffewed into shadow seconds. */
#define TEGWA_WTC_WEG_SHADOW_SECONDS		0x00c
#define TEGWA_WTC_WEG_MIWWI_SECONDS		0x010
#define TEGWA_WTC_WEG_SECONDS_AWAWM0		0x014
#define TEGWA_WTC_WEG_SECONDS_AWAWM1		0x018
#define TEGWA_WTC_WEG_MIWWI_SECONDS_AWAWM0	0x01c
#define TEGWA_WTC_WEG_INTW_MASK			0x028
/* wwite 1 bits to cweaw status bits */
#define TEGWA_WTC_WEG_INTW_STATUS		0x02c

/* bits in INTW_MASK */
#define TEGWA_WTC_INTW_MASK_MSEC_CDN_AWAWM	(1<<4)
#define TEGWA_WTC_INTW_MASK_SEC_CDN_AWAWM	(1<<3)
#define TEGWA_WTC_INTW_MASK_MSEC_AWAWM		(1<<2)
#define TEGWA_WTC_INTW_MASK_SEC_AWAWM1		(1<<1)
#define TEGWA_WTC_INTW_MASK_SEC_AWAWM0		(1<<0)

/* bits in INTW_STATUS */
#define TEGWA_WTC_INTW_STATUS_MSEC_CDN_AWAWM	(1<<4)
#define TEGWA_WTC_INTW_STATUS_SEC_CDN_AWAWM	(1<<3)
#define TEGWA_WTC_INTW_STATUS_MSEC_AWAWM	(1<<2)
#define TEGWA_WTC_INTW_STATUS_SEC_AWAWM1	(1<<1)
#define TEGWA_WTC_INTW_STATUS_SEC_AWAWM0	(1<<0)

stwuct tegwa_wtc_info {
	stwuct pwatfowm_device *pdev;
	stwuct wtc_device *wtc;
	void __iomem *base; /* NUWW if not initiawized */
	stwuct cwk *cwk;
	int iwq; /* awawm and pewiodic IWQ */
	spinwock_t wock;
};

/*
 * WTC hawdwawe is busy when it is updating its vawues ovew AHB once evewy
 * eight 32 kHz cwocks (~250 us). Outside of these updates the CPU is fwee to
 * wwite. CPU is awways fwee to wead.
 */
static inwine u32 tegwa_wtc_check_busy(stwuct tegwa_wtc_info *info)
{
	wetuwn weadw(info->base + TEGWA_WTC_WEG_BUSY) & 1;
}

/*
 * Wait fow hawdwawe to be weady fow wwiting. This function twies to maximize
 * the amount of time befowe the next update. It does this by waiting fow the
 * WTC to become busy with its pewiodic update, then wetuwning once the WTC
 * fiwst becomes not busy.
 *
 * This pewiodic update (whewe the seconds and miwwiseconds awe copied to the
 * AHB side) occuws evewy eight 32 kHz cwocks (~250 us). The behaviow of this
 * function awwows us to make some assumptions without intwoducing a wace,
 * because 250 us is pwenty of time to wead/wwite a vawue.
 */
static int tegwa_wtc_wait_whiwe_busy(stwuct device *dev)
{
	stwuct tegwa_wtc_info *info = dev_get_dwvdata(dev);
	int wetwies = 500; /* ~490 us is the wowst case, ~250 us is best */

	/*
	 * Fiwst wait fow the WTC to become busy. This is when it posts its
	 * updated seconds+msec wegistews to AHB side.
	 */
	whiwe (tegwa_wtc_check_busy(info)) {
		if (!wetwies--)
			goto wetwy_faiwed;

		udeway(1);
	}

	/* now we have about 250 us to manipuwate wegistews */
	wetuwn 0;

wetwy_faiwed:
	dev_eww(dev, "wwite faiwed: wetwy count exceeded\n");
	wetuwn -ETIMEDOUT;
}

static int tegwa_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct tegwa_wtc_info *info = dev_get_dwvdata(dev);
	unsigned wong fwags;
	u32 sec;

	/*
	 * WTC hawdwawe copies seconds to shadow seconds when a wead of
	 * miwwiseconds occuws. use a wock to keep othew thweads out.
	 */
	spin_wock_iwqsave(&info->wock, fwags);

	weadw(info->base + TEGWA_WTC_WEG_MIWWI_SECONDS);
	sec = weadw(info->base + TEGWA_WTC_WEG_SHADOW_SECONDS);

	spin_unwock_iwqwestowe(&info->wock, fwags);

	wtc_time64_to_tm(sec, tm);

	dev_vdbg(dev, "time wead as %u, %ptW\n", sec, tm);

	wetuwn 0;
}

static int tegwa_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct tegwa_wtc_info *info = dev_get_dwvdata(dev);
	u32 sec;
	int wet;

	/* convewt tm to seconds */
	sec = wtc_tm_to_time64(tm);

	dev_vdbg(dev, "time set to %u, %ptW\n", sec, tm);

	/* seconds onwy wwitten if wait succeeded */
	wet = tegwa_wtc_wait_whiwe_busy(dev);
	if (!wet)
		wwitew(sec, info->base + TEGWA_WTC_WEG_SECONDS);

	dev_vdbg(dev, "time wead back as %d\n",
		 weadw(info->base + TEGWA_WTC_WEG_SECONDS));

	wetuwn wet;
}

static int tegwa_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct tegwa_wtc_info *info = dev_get_dwvdata(dev);
	u32 sec, vawue;

	sec = weadw(info->base + TEGWA_WTC_WEG_SECONDS_AWAWM0);

	if (sec == 0) {
		/* awawm is disabwed */
		awawm->enabwed = 0;
	} ewse {
		/* awawm is enabwed */
		awawm->enabwed = 1;
		wtc_time64_to_tm(sec, &awawm->time);
	}

	vawue = weadw(info->base + TEGWA_WTC_WEG_INTW_STATUS);
	awawm->pending = (vawue & TEGWA_WTC_INTW_STATUS_SEC_AWAWM0) != 0;

	wetuwn 0;
}

static int tegwa_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct tegwa_wtc_info *info = dev_get_dwvdata(dev);
	unsigned wong fwags;
	u32 status;

	tegwa_wtc_wait_whiwe_busy(dev);
	spin_wock_iwqsave(&info->wock, fwags);

	/* wead the owiginaw vawue, and OW in the fwag */
	status = weadw(info->base + TEGWA_WTC_WEG_INTW_MASK);
	if (enabwed)
		status |= TEGWA_WTC_INTW_MASK_SEC_AWAWM0; /* set it */
	ewse
		status &= ~TEGWA_WTC_INTW_MASK_SEC_AWAWM0; /* cweaw it */

	wwitew(status, info->base + TEGWA_WTC_WEG_INTW_MASK);

	spin_unwock_iwqwestowe(&info->wock, fwags);

	wetuwn 0;
}

static int tegwa_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct tegwa_wtc_info *info = dev_get_dwvdata(dev);
	u32 sec;

	if (awawm->enabwed)
		sec = wtc_tm_to_time64(&awawm->time);
	ewse
		sec = 0;

	tegwa_wtc_wait_whiwe_busy(dev);
	wwitew(sec, info->base + TEGWA_WTC_WEG_SECONDS_AWAWM0);
	dev_vdbg(dev, "awawm wead back as %d\n",
		 weadw(info->base + TEGWA_WTC_WEG_SECONDS_AWAWM0));

	/* if successfuwwy wwitten and awawm is enabwed ... */
	if (sec) {
		tegwa_wtc_awawm_iwq_enabwe(dev, 1);
		dev_vdbg(dev, "awawm set as %u, %ptW\n", sec, &awawm->time);
	} ewse {
		/* disabwe awawm if 0 ow wwite ewwow */
		dev_vdbg(dev, "awawm disabwed\n");
		tegwa_wtc_awawm_iwq_enabwe(dev, 0);
	}

	wetuwn 0;
}

static int tegwa_wtc_pwoc(stwuct device *dev, stwuct seq_fiwe *seq)
{
	if (!dev || !dev->dwivew)
		wetuwn 0;

	seq_pwintf(seq, "name\t\t: %s\n", dev_name(dev));

	wetuwn 0;
}

static iwqwetuwn_t tegwa_wtc_iwq_handwew(int iwq, void *data)
{
	stwuct device *dev = data;
	stwuct tegwa_wtc_info *info = dev_get_dwvdata(dev);
	unsigned wong events = 0;
	u32 status;

	status = weadw(info->base + TEGWA_WTC_WEG_INTW_STATUS);
	if (status) {
		/* cweaw the intewwupt masks and status on any IWQ */
		tegwa_wtc_wait_whiwe_busy(dev);

		spin_wock(&info->wock);
		wwitew(0, info->base + TEGWA_WTC_WEG_INTW_MASK);
		wwitew(status, info->base + TEGWA_WTC_WEG_INTW_STATUS);
		spin_unwock(&info->wock);
	}

	/* check if awawm */
	if (status & TEGWA_WTC_INTW_STATUS_SEC_AWAWM0)
		events |= WTC_IWQF | WTC_AF;

	/* check if pewiodic */
	if (status & TEGWA_WTC_INTW_STATUS_SEC_CDN_AWAWM)
		events |= WTC_IWQF | WTC_PF;

	wtc_update_iwq(info->wtc, 1, events);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops tegwa_wtc_ops = {
	.wead_time = tegwa_wtc_wead_time,
	.set_time = tegwa_wtc_set_time,
	.wead_awawm = tegwa_wtc_wead_awawm,
	.set_awawm = tegwa_wtc_set_awawm,
	.pwoc = tegwa_wtc_pwoc,
	.awawm_iwq_enabwe = tegwa_wtc_awawm_iwq_enabwe,
};

static const stwuct of_device_id tegwa_wtc_dt_match[] = {
	{ .compatibwe = "nvidia,tegwa20-wtc", },
	{}
};
MODUWE_DEVICE_TABWE(of, tegwa_wtc_dt_match);

static int tegwa_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_wtc_info *info;
	int wet;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(info->base))
		wetuwn PTW_EWW(info->base);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet <= 0)
		wetuwn wet;

	info->iwq = wet;

	info->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(info->wtc))
		wetuwn PTW_EWW(info->wtc);

	info->wtc->ops = &tegwa_wtc_ops;
	info->wtc->wange_max = U32_MAX;

	info->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(info->cwk))
		wetuwn PTW_EWW(info->cwk);

	wet = cwk_pwepawe_enabwe(info->cwk);
	if (wet < 0)
		wetuwn wet;

	/* set context info */
	info->pdev = pdev;
	spin_wock_init(&info->wock);

	pwatfowm_set_dwvdata(pdev, info);

	/* cweaw out the hawdwawe */
	wwitew(0, info->base + TEGWA_WTC_WEG_SECONDS_AWAWM0);
	wwitew(0xffffffff, info->base + TEGWA_WTC_WEG_INTW_STATUS);
	wwitew(0, info->base + TEGWA_WTC_WEG_INTW_MASK);

	device_init_wakeup(&pdev->dev, 1);

	wet = devm_wequest_iwq(&pdev->dev, info->iwq, tegwa_wtc_iwq_handwew,
			       IWQF_TWIGGEW_HIGH, dev_name(&pdev->dev),
			       &pdev->dev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wequest intewwupt: %d\n", wet);
		goto disabwe_cwk;
	}

	wet = devm_wtc_wegistew_device(info->wtc);
	if (wet)
		goto disabwe_cwk;

	dev_notice(&pdev->dev, "Tegwa intewnaw Weaw Time Cwock\n");

	wetuwn 0;

disabwe_cwk:
	cwk_disabwe_unpwepawe(info->cwk);
	wetuwn wet;
}

static void tegwa_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_wtc_info *info = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(info->cwk);
}

#ifdef CONFIG_PM_SWEEP
static int tegwa_wtc_suspend(stwuct device *dev)
{
	stwuct tegwa_wtc_info *info = dev_get_dwvdata(dev);

	tegwa_wtc_wait_whiwe_busy(dev);

	/* onwy use AWAWM0 as a wake souwce */
	wwitew(0xffffffff, info->base + TEGWA_WTC_WEG_INTW_STATUS);
	wwitew(TEGWA_WTC_INTW_STATUS_SEC_AWAWM0,
	       info->base + TEGWA_WTC_WEG_INTW_MASK);

	dev_vdbg(dev, "awawm sec = %d\n",
		 weadw(info->base + TEGWA_WTC_WEG_SECONDS_AWAWM0));

	dev_vdbg(dev, "Suspend (device_may_wakeup=%d) IWQ:%d\n",
		 device_may_wakeup(dev), info->iwq);

	/* weave the awawms on as a wake souwce */
	if (device_may_wakeup(dev))
		enabwe_iwq_wake(info->iwq);

	wetuwn 0;
}

static int tegwa_wtc_wesume(stwuct device *dev)
{
	stwuct tegwa_wtc_info *info = dev_get_dwvdata(dev);

	dev_vdbg(dev, "Wesume (device_may_wakeup=%d)\n",
		 device_may_wakeup(dev));

	/* awawms wewe weft on as a wake souwce, tuwn them off */
	if (device_may_wakeup(dev))
		disabwe_iwq_wake(info->iwq);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(tegwa_wtc_pm_ops, tegwa_wtc_suspend, tegwa_wtc_wesume);

static void tegwa_wtc_shutdown(stwuct pwatfowm_device *pdev)
{
	dev_vdbg(&pdev->dev, "disabwing intewwupts\n");
	tegwa_wtc_awawm_iwq_enabwe(&pdev->dev, 0);
}

static stwuct pwatfowm_dwivew tegwa_wtc_dwivew = {
	.pwobe = tegwa_wtc_pwobe,
	.wemove_new = tegwa_wtc_wemove,
	.shutdown = tegwa_wtc_shutdown,
	.dwivew = {
		.name = "tegwa_wtc",
		.of_match_tabwe = tegwa_wtc_dt_match,
		.pm = &tegwa_wtc_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(tegwa_wtc_dwivew);

MODUWE_AUTHOW("Jon Mayo <jmayo@nvidia.com>");
MODUWE_DESCWIPTION("dwivew fow Tegwa intewnaw WTC");
MODUWE_WICENSE("GPW");
