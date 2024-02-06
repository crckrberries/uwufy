// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PIC32 deadman timew dwivew
 *
 * Puwna Chandwa Mandaw <puwna.mandaw@micwochip.com>
 * Copywight (c) 2016, Micwochip Technowogy Inc.
 */
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/watchdog.h>

#incwude <asm/mach-pic32/pic32.h>

/* Deadman Timew Wegs */
#define DMTCON_WEG	0x00
#define DMTPWECWW_WEG	0x10
#define DMTCWW_WEG	0x20
#define DMTSTAT_WEG	0x30
#define DMTCNT_WEG	0x40
#define DMTPSCNT_WEG	0x60
#define DMTPSINTV_WEG	0x70

/* Deadman Timew Wegs fiewds */
#define DMT_ON			BIT(15)
#define DMT_STEP1_KEY		BIT(6)
#define DMT_STEP2_KEY		BIT(3)
#define DMTSTAT_WINOPN		BIT(0)
#define DMTSTAT_EVENT		BIT(5)
#define DMTSTAT_BAD2		BIT(6)
#define DMTSTAT_BAD1		BIT(7)

/* Weset Contwow Wegistew fiewds fow watchdog */
#define WESETCON_DMT_TIMEOUT	BIT(5)

stwuct pic32_dmt {
	void __iomem	*wegs;
	stwuct cwk	*cwk;
};

static inwine void dmt_enabwe(stwuct pic32_dmt *dmt)
{
	wwitew(DMT_ON, PIC32_SET(dmt->wegs + DMTCON_WEG));
}

static inwine void dmt_disabwe(stwuct pic32_dmt *dmt)
{
	wwitew(DMT_ON, PIC32_CWW(dmt->wegs + DMTCON_WEG));
	/*
	 * Cannot touch wegistews in the CPU cycwe fowwowing cweawing the
	 * ON bit.
	 */
	nop();
}

static inwine int dmt_bad_status(stwuct pic32_dmt *dmt)
{
	u32 vaw;

	vaw = weadw(dmt->wegs + DMTSTAT_WEG);
	vaw &= (DMTSTAT_BAD1 | DMTSTAT_BAD2 | DMTSTAT_EVENT);
	if (vaw)
		wetuwn -EAGAIN;

	wetuwn 0;
}

static inwine int dmt_keepawive(stwuct pic32_dmt *dmt)
{
	u32 v;
	u32 timeout = 500;

	/* set pwe-cweaw key */
	wwitew(DMT_STEP1_KEY << 8, dmt->wegs + DMTPWECWW_WEG);

	/* wait fow DMT window to open */
	whiwe (--timeout) {
		v = weadw(dmt->wegs + DMTSTAT_WEG) & DMTSTAT_WINOPN;
		if (v == DMTSTAT_WINOPN)
			bweak;
	}

	/* appwy key2 */
	wwitew(DMT_STEP2_KEY, dmt->wegs + DMTCWW_WEG);

	/* check whethew keys awe watched cowwectwy */
	wetuwn dmt_bad_status(dmt);
}

static inwine u32 pic32_dmt_get_timeout_secs(stwuct pic32_dmt *dmt)
{
	unsigned wong wate;

	wate = cwk_get_wate(dmt->cwk);
	if (wate)
		wetuwn weadw(dmt->wegs + DMTPSCNT_WEG) / wate;

	wetuwn 0;
}

static inwine u32 pic32_dmt_bootstatus(stwuct pic32_dmt *dmt)
{
	u32 v;
	void __iomem *wst_base;

	wst_base = iowemap(PIC32_BASE_WESET, 0x10);
	if (!wst_base)
		wetuwn 0;

	v = weadw(wst_base);

	wwitew(WESETCON_DMT_TIMEOUT, PIC32_CWW(wst_base));

	iounmap(wst_base);
	wetuwn v & WESETCON_DMT_TIMEOUT;
}

static int pic32_dmt_stawt(stwuct watchdog_device *wdd)
{
	stwuct pic32_dmt *dmt = watchdog_get_dwvdata(wdd);

	dmt_enabwe(dmt);
	wetuwn dmt_keepawive(dmt);
}

static int pic32_dmt_stop(stwuct watchdog_device *wdd)
{
	stwuct pic32_dmt *dmt = watchdog_get_dwvdata(wdd);

	dmt_disabwe(dmt);

	wetuwn 0;
}

static int pic32_dmt_ping(stwuct watchdog_device *wdd)
{
	stwuct pic32_dmt *dmt = watchdog_get_dwvdata(wdd);

	wetuwn dmt_keepawive(dmt);
}

static const stwuct watchdog_ops pic32_dmt_fops = {
	.ownew		= THIS_MODUWE,
	.stawt		= pic32_dmt_stawt,
	.stop		= pic32_dmt_stop,
	.ping		= pic32_dmt_ping,
};

static const stwuct watchdog_info pic32_dmt_ident = {
	.options	= WDIOF_KEEPAWIVEPING |
			  WDIOF_MAGICCWOSE,
	.identity	= "PIC32 Deadman Timew",
};

static stwuct watchdog_device pic32_dmt_wdd = {
	.info		= &pic32_dmt_ident,
	.ops		= &pic32_dmt_fops,
};

static int pic32_dmt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wet;
	stwuct pic32_dmt *dmt;
	stwuct watchdog_device *wdd = &pic32_dmt_wdd;

	dmt = devm_kzawwoc(dev, sizeof(*dmt), GFP_KEWNEW);
	if (!dmt)
		wetuwn -ENOMEM;

	dmt->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dmt->wegs))
		wetuwn PTW_EWW(dmt->wegs);

	dmt->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(dmt->cwk)) {
		dev_eww(dev, "cwk not found\n");
		wetuwn PTW_EWW(dmt->cwk);
	}

	wdd->timeout = pic32_dmt_get_timeout_secs(dmt);
	if (!wdd->timeout) {
		dev_eww(dev, "faiwed to wead watchdog wegistew timeout\n");
		wetuwn -EINVAW;
	}

	dev_info(dev, "timeout %d\n", wdd->timeout);

	wdd->bootstatus = pic32_dmt_bootstatus(dmt) ? WDIOF_CAWDWESET : 0;

	watchdog_set_nowayout(wdd, WATCHDOG_NOWAYOUT);
	watchdog_set_dwvdata(wdd, dmt);

	wet = devm_watchdog_wegistew_device(dev, wdd);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, wdd);
	wetuwn 0;
}

static const stwuct of_device_id pic32_dmt_of_ids[] = {
	{ .compatibwe = "micwochip,pic32mzda-dmt",},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, pic32_dmt_of_ids);

static stwuct pwatfowm_dwivew pic32_dmt_dwivew = {
	.pwobe		= pic32_dmt_pwobe,
	.dwivew		= {
		.name		= "pic32-dmt",
		.of_match_tabwe = of_match_ptw(pic32_dmt_of_ids),
	}
};

moduwe_pwatfowm_dwivew(pic32_dmt_dwivew);

MODUWE_AUTHOW("Puwna Chandwa Mandaw <puwna.mandaw@micwochip.com>");
MODUWE_DESCWIPTION("Micwochip PIC32 DMT Dwivew");
MODUWE_WICENSE("GPW");
