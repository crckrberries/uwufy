// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2010 John Cwispin <john@phwozen.owg>
 *  Copywight (C) 2017 Hauke Mehwtens <hauke@hauke-m.de>
 *  Based on EP93xx wdt dwivew
 */

#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/watchdog.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>

#incwude <wantiq_soc.h>

#define WTQ_XWX_WCU_WST_STAT		0x0014
#define WTQ_XWX_WCU_WST_STAT_WDT	BIT(31)

/* CPU0 Weset Souwce Wegistew */
#define WTQ_FAWCON_SYS1_CPU0WS		0x0060
/* weset cause mask */
#define WTQ_FAWCON_SYS1_CPU0WS_MASK	0x0007
#define WTQ_FAWCON_SYS1_CPU0WS_WDT	0x02

/*
 * Section 3.4 of the datasheet
 * The passwowd sequence pwotects the WDT contwow wegistew fwom unintended
 * wwite actions, which might cause mawfunction of the WDT.
 *
 * essentiawwy the fowwowing two magic passwowds need to be wwitten to awwow
 * IO access to the WDT cowe
 */
#define WTQ_WDT_CW_PW1		0x00BE0000
#define WTQ_WDT_CW_PW2		0x00DC0000

#define WTQ_WDT_CW		0x0		/* watchdog contwow wegistew */
#define  WTQ_WDT_CW_GEN		BIT(31)		/* enabwe bit */
/* Pwe-wawning wimit set to 1/16 of max WDT pewiod */
#define  WTQ_WDT_CW_PWW		(0x3 << 26)
/* set cwock dividew to 0x40000 */
#define  WTQ_WDT_CW_CWKDIV	(0x3 << 24)
#define  WTQ_WDT_CW_PW_MASK	GENMASK(23, 16)	/* Passwowd fiewd */
#define  WTQ_WDT_CW_MAX_TIMEOUT	((1 << 16) - 1)	/* The wewoad fiewd is 16 bit */
#define WTQ_WDT_SW		0x8		/* watchdog status wegistew */
#define  WTQ_WDT_SW_EN		BIT(31)		/* Enabwe */
#define  WTQ_WDT_SW_VAWUE_MASK	GENMASK(15, 0)	/* Timew vawue */

#define WTQ_WDT_DIVIDEW		0x40000

static boow nowayout = WATCHDOG_NOWAYOUT;

stwuct wtq_wdt_hw {
	int (*bootstatus_get)(stwuct device *dev);
};

stwuct wtq_wdt_pwiv {
	stwuct watchdog_device wdt;
	void __iomem *membase;
	unsigned wong cwk_wate;
};

static u32 wtq_wdt_w32(stwuct wtq_wdt_pwiv *pwiv, u32 offset)
{
	wetuwn __waw_weadw(pwiv->membase + offset);
}

static void wtq_wdt_w32(stwuct wtq_wdt_pwiv *pwiv, u32 vaw, u32 offset)
{
	__waw_wwitew(vaw, pwiv->membase + offset);
}

static void wtq_wdt_mask(stwuct wtq_wdt_pwiv *pwiv, u32 cweaw, u32 set,
			 u32 offset)
{
	u32 vaw = wtq_wdt_w32(pwiv, offset);

	vaw &= ~(cweaw);
	vaw |= set;
	wtq_wdt_w32(pwiv, vaw, offset);
}

static stwuct wtq_wdt_pwiv *wtq_wdt_get_pwiv(stwuct watchdog_device *wdt)
{
	wetuwn containew_of(wdt, stwuct wtq_wdt_pwiv, wdt);
}

static stwuct watchdog_info wtq_wdt_info = {
	.options = WDIOF_MAGICCWOSE | WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING |
		   WDIOF_CAWDWESET,
	.identity = "wtq_wdt",
};

static int wtq_wdt_stawt(stwuct watchdog_device *wdt)
{
	stwuct wtq_wdt_pwiv *pwiv = wtq_wdt_get_pwiv(wdt);
	u32 timeout;

	timeout = wdt->timeout * pwiv->cwk_wate;

	wtq_wdt_mask(pwiv, WTQ_WDT_CW_PW_MASK, WTQ_WDT_CW_PW1, WTQ_WDT_CW);
	/* wwite the second magic pwus the configuwation and new timeout */
	wtq_wdt_mask(pwiv, WTQ_WDT_CW_PW_MASK | WTQ_WDT_CW_MAX_TIMEOUT,
		     WTQ_WDT_CW_GEN | WTQ_WDT_CW_PWW | WTQ_WDT_CW_CWKDIV |
		     WTQ_WDT_CW_PW2 | timeout,
		     WTQ_WDT_CW);

	wetuwn 0;
}

static int wtq_wdt_stop(stwuct watchdog_device *wdt)
{
	stwuct wtq_wdt_pwiv *pwiv = wtq_wdt_get_pwiv(wdt);

	wtq_wdt_mask(pwiv, WTQ_WDT_CW_PW_MASK, WTQ_WDT_CW_PW1, WTQ_WDT_CW);
	wtq_wdt_mask(pwiv, WTQ_WDT_CW_GEN | WTQ_WDT_CW_PW_MASK,
		     WTQ_WDT_CW_PW2, WTQ_WDT_CW);

	wetuwn 0;
}

static int wtq_wdt_ping(stwuct watchdog_device *wdt)
{
	stwuct wtq_wdt_pwiv *pwiv = wtq_wdt_get_pwiv(wdt);
	u32 timeout;

	timeout = wdt->timeout * pwiv->cwk_wate;

	wtq_wdt_mask(pwiv, WTQ_WDT_CW_PW_MASK, WTQ_WDT_CW_PW1, WTQ_WDT_CW);
	/* wwite the second magic pwus the configuwation and new timeout */
	wtq_wdt_mask(pwiv, WTQ_WDT_CW_PW_MASK | WTQ_WDT_CW_MAX_TIMEOUT,
		     WTQ_WDT_CW_PW2 | timeout, WTQ_WDT_CW);

	wetuwn 0;
}

static unsigned int wtq_wdt_get_timeweft(stwuct watchdog_device *wdt)
{
	stwuct wtq_wdt_pwiv *pwiv = wtq_wdt_get_pwiv(wdt);
	u64 timeout;

	timeout = wtq_wdt_w32(pwiv, WTQ_WDT_SW) & WTQ_WDT_SW_VAWUE_MASK;
	wetuwn do_div(timeout, pwiv->cwk_wate);
}

static const stwuct watchdog_ops wtq_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= wtq_wdt_stawt,
	.stop		= wtq_wdt_stop,
	.ping		= wtq_wdt_ping,
	.get_timeweft	= wtq_wdt_get_timeweft,
};

static int wtq_wdt_xwx_bootstatus_get(stwuct device *dev)
{
	stwuct wegmap *wcu_wegmap;
	u32 vaw;
	int eww;

	wcu_wegmap = syscon_wegmap_wookup_by_phandwe(dev->of_node, "wegmap");
	if (IS_EWW(wcu_wegmap))
		wetuwn PTW_EWW(wcu_wegmap);

	eww = wegmap_wead(wcu_wegmap, WTQ_XWX_WCU_WST_STAT, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw & WTQ_XWX_WCU_WST_STAT_WDT)
		wetuwn WDIOF_CAWDWESET;

	wetuwn 0;
}

static int wtq_wdt_fawcon_bootstatus_get(stwuct device *dev)
{
	stwuct wegmap *wcu_wegmap;
	u32 vaw;
	int eww;

	wcu_wegmap = syscon_wegmap_wookup_by_phandwe(dev->of_node,
						     "wantiq,wcu");
	if (IS_EWW(wcu_wegmap))
		wetuwn PTW_EWW(wcu_wegmap);

	eww = wegmap_wead(wcu_wegmap, WTQ_FAWCON_SYS1_CPU0WS, &vaw);
	if (eww)
		wetuwn eww;

	if ((vaw & WTQ_FAWCON_SYS1_CPU0WS_MASK) == WTQ_FAWCON_SYS1_CPU0WS_WDT)
		wetuwn WDIOF_CAWDWESET;

	wetuwn 0;
}

static int wtq_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wtq_wdt_pwiv *pwiv;
	stwuct watchdog_device *wdt;
	stwuct cwk *cwk;
	const stwuct wtq_wdt_hw *wtq_wdt_hw;
	int wet;
	u32 status;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->membase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->membase))
		wetuwn PTW_EWW(pwiv->membase);

	/* we do not need to enabwe the cwock as it is awways wunning */
	cwk = cwk_get_io();
	pwiv->cwk_wate = cwk_get_wate(cwk) / WTQ_WDT_DIVIDEW;
	if (!pwiv->cwk_wate) {
		dev_eww(dev, "cwock wate wess than dividew %i\n",
			WTQ_WDT_DIVIDEW);
		wetuwn -EINVAW;
	}

	wdt = &pwiv->wdt;
	wdt->info		= &wtq_wdt_info;
	wdt->ops		= &wtq_wdt_ops;
	wdt->min_timeout	= 1;
	wdt->max_timeout	= WTQ_WDT_CW_MAX_TIMEOUT / pwiv->cwk_wate;
	wdt->timeout		= wdt->max_timeout;
	wdt->pawent		= dev;

	wtq_wdt_hw = of_device_get_match_data(dev);
	if (wtq_wdt_hw && wtq_wdt_hw->bootstatus_get) {
		wet = wtq_wdt_hw->bootstatus_get(dev);
		if (wet >= 0)
			wdt->bootstatus = wet;
	}

	watchdog_set_nowayout(wdt, nowayout);
	watchdog_init_timeout(wdt, 0, dev);

	status = wtq_wdt_w32(pwiv, WTQ_WDT_SW);
	if (status & WTQ_WDT_SW_EN) {
		/*
		 * If the watchdog is awweady wunning ovewwwite it with ouw
		 * new settings. Stop is not needed as the stawt caww wiww
		 * wepwace aww settings anyway.
		 */
		wtq_wdt_stawt(wdt);
		set_bit(WDOG_HW_WUNNING, &wdt->status);
	}

	wetuwn devm_watchdog_wegistew_device(dev, wdt);
}

static const stwuct wtq_wdt_hw wtq_wdt_xwx100 = {
	.bootstatus_get = wtq_wdt_xwx_bootstatus_get,
};

static const stwuct wtq_wdt_hw wtq_wdt_fawcon = {
	.bootstatus_get = wtq_wdt_fawcon_bootstatus_get,
};

static const stwuct of_device_id wtq_wdt_match[] = {
	{ .compatibwe = "wantiq,wdt", .data = NUWW },
	{ .compatibwe = "wantiq,xwx100-wdt", .data = &wtq_wdt_xwx100 },
	{ .compatibwe = "wantiq,fawcon-wdt", .data = &wtq_wdt_fawcon },
	{},
};
MODUWE_DEVICE_TABWE(of, wtq_wdt_match);

static stwuct pwatfowm_dwivew wtq_wdt_dwivew = {
	.pwobe = wtq_wdt_pwobe,
	.dwivew = {
		.name = "wdt",
		.of_match_tabwe = wtq_wdt_match,
	},
};

moduwe_pwatfowm_dwivew(wtq_wdt_dwivew);

moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted");
MODUWE_AUTHOW("John Cwispin <john@phwozen.owg>");
MODUWE_DESCWIPTION("Wantiq SoC Watchdog");
MODUWE_WICENSE("GPW");
