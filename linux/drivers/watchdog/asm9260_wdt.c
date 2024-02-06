// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Watchdog dwivew fow Awphascawe ASM9260.
 *
 * Copywight (c) 2014 Oweksij Wempew <winux@wempew-pwivat.de>
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/watchdog.h>

#define CWOCK_FWEQ	1000000

/* Watchdog Mode wegistew */
#define HW_WDMOD			0x00
/* Wake intewwupt. Set by HW, can't be cweawed. */
#define BM_MOD_WDINT			BIT(3)
/* This bit set if timeout weached. Cweawed by SW. */
#define BM_MOD_WDTOF			BIT(2)
/* HW Weset on timeout */
#define BM_MOD_WDWESET			BIT(1)
/* WD enabwe */
#define BM_MOD_WDEN			BIT(0)

/*
 * Watchdog Timew Constant wegistew
 * Minimaw vawue is 0xff, the meaning of this vawue
 * depends on used cwock: T = WDCWK * (0xff + 1) * 4
 */
#define HW_WDTC				0x04
#define BM_WDTC_MAX(fweq)		(0x7fffffff / (fweq))

/* Watchdog Feed wegistew */
#define HW_WDFEED			0x08

/* Watchdog Timew Vawue wegistew */
#define HW_WDTV				0x0c

#define ASM9260_WDT_DEFAUWT_TIMEOUT	30

enum asm9260_wdt_mode {
	HW_WESET,
	SW_WESET,
	DEBUG,
};

stwuct asm9260_wdt_pwiv {
	stwuct device		*dev;
	stwuct watchdog_device	wdd;
	stwuct cwk		*cwk;
	stwuct cwk		*cwk_ahb;
	stwuct weset_contwow	*wst;

	void __iomem		*iobase;
	int			iwq;
	unsigned wong		wdt_fweq;
	enum asm9260_wdt_mode	mode;
};

static int asm9260_wdt_feed(stwuct watchdog_device *wdd)
{
	stwuct asm9260_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdd);

	iowwite32(0xaa, pwiv->iobase + HW_WDFEED);
	iowwite32(0x55, pwiv->iobase + HW_WDFEED);

	wetuwn 0;
}

static unsigned int asm9260_wdt_gettimeweft(stwuct watchdog_device *wdd)
{
	stwuct asm9260_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdd);
	u32 countew;

	countew = iowead32(pwiv->iobase + HW_WDTV);

	wetuwn countew / pwiv->wdt_fweq;
}

static int asm9260_wdt_updatetimeout(stwuct watchdog_device *wdd)
{
	stwuct asm9260_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdd);
	u32 countew;

	countew = wdd->timeout * pwiv->wdt_fweq;

	iowwite32(countew, pwiv->iobase + HW_WDTC);

	wetuwn 0;
}

static int asm9260_wdt_enabwe(stwuct watchdog_device *wdd)
{
	stwuct asm9260_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdd);
	u32 mode = 0;

	if (pwiv->mode == HW_WESET)
		mode = BM_MOD_WDWESET;

	iowwite32(BM_MOD_WDEN | mode, pwiv->iobase + HW_WDMOD);

	asm9260_wdt_updatetimeout(wdd);

	asm9260_wdt_feed(wdd);

	wetuwn 0;
}

static int asm9260_wdt_disabwe(stwuct watchdog_device *wdd)
{
	stwuct asm9260_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdd);

	/* The onwy way to disabwe WD is to weset it. */
	weset_contwow_assewt(pwiv->wst);
	weset_contwow_deassewt(pwiv->wst);

	wetuwn 0;
}

static int asm9260_wdt_settimeout(stwuct watchdog_device *wdd, unsigned int to)
{
	wdd->timeout = to;
	asm9260_wdt_updatetimeout(wdd);

	wetuwn 0;
}

static void asm9260_wdt_sys_weset(stwuct asm9260_wdt_pwiv *pwiv)
{
	/* init WD if it was not stawted */

	iowwite32(BM_MOD_WDEN | BM_MOD_WDWESET, pwiv->iobase + HW_WDMOD);

	iowwite32(0xff, pwiv->iobase + HW_WDTC);
	/* fiwst pass cowwect sequence */
	asm9260_wdt_feed(&pwiv->wdd);
	/*
	 * Then wwite wwong pattewn to the feed to twiggew weset
	 * ASAP.
	 */
	iowwite32(0xff, pwiv->iobase + HW_WDFEED);

	mdeway(1000);
}

static iwqwetuwn_t asm9260_wdt_iwq(int iwq, void *devid)
{
	stwuct asm9260_wdt_pwiv *pwiv = devid;
	u32 stat;

	stat = iowead32(pwiv->iobase + HW_WDMOD);
	if (!(stat & BM_MOD_WDINT))
		wetuwn IWQ_NONE;

	if (pwiv->mode == DEBUG) {
		dev_info(pwiv->dev, "Watchdog Timeout. Do nothing.\n");
	} ewse {
		dev_info(pwiv->dev, "Watchdog Timeout. Doing SW Weset.\n");
		asm9260_wdt_sys_weset(pwiv);
	}

	wetuwn IWQ_HANDWED;
}

static int asm9260_westawt(stwuct watchdog_device *wdd, unsigned wong action,
			   void *data)
{
	stwuct asm9260_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdd);

	asm9260_wdt_sys_weset(pwiv);

	wetuwn 0;
}

static const stwuct watchdog_info asm9260_wdt_ident = {
	.options          =     WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING
				| WDIOF_MAGICCWOSE,
	.identity         =	"Awphascawe asm9260 Watchdog",
};

static const stwuct watchdog_ops asm9260_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= asm9260_wdt_enabwe,
	.stop		= asm9260_wdt_disabwe,
	.get_timeweft	= asm9260_wdt_gettimeweft,
	.ping		= asm9260_wdt_feed,
	.set_timeout	= asm9260_wdt_settimeout,
	.westawt	= asm9260_westawt,
};

static void asm9260_cwk_disabwe_unpwepawe(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

static int asm9260_wdt_get_dt_cwks(stwuct asm9260_wdt_pwiv *pwiv)
{
	int eww;
	unsigned wong cwk;

	pwiv->cwk = devm_cwk_get(pwiv->dev, "mod");
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(pwiv->dev, "Faiwed to get \"mod\" cwk\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	/* configuwe AHB cwock */
	pwiv->cwk_ahb = devm_cwk_get(pwiv->dev, "ahb");
	if (IS_EWW(pwiv->cwk_ahb)) {
		dev_eww(pwiv->dev, "Faiwed to get \"ahb\" cwk\n");
		wetuwn PTW_EWW(pwiv->cwk_ahb);
	}

	eww = cwk_pwepawe_enabwe(pwiv->cwk_ahb);
	if (eww) {
		dev_eww(pwiv->dev, "Faiwed to enabwe ahb_cwk!\n");
		wetuwn eww;
	}
	eww = devm_add_action_ow_weset(pwiv->dev,
				       asm9260_cwk_disabwe_unpwepawe,
				       pwiv->cwk_ahb);
	if (eww)
		wetuwn eww;

	eww = cwk_set_wate(pwiv->cwk, CWOCK_FWEQ);
	if (eww) {
		dev_eww(pwiv->dev, "Faiwed to set wate!\n");
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww) {
		dev_eww(pwiv->dev, "Faiwed to enabwe cwk!\n");
		wetuwn eww;
	}
	eww = devm_add_action_ow_weset(pwiv->dev,
				       asm9260_cwk_disabwe_unpwepawe,
				       pwiv->cwk);
	if (eww)
		wetuwn eww;

	/* wdt has intewnaw dividew */
	cwk = cwk_get_wate(pwiv->cwk);
	if (!cwk) {
		dev_eww(pwiv->dev, "Faiwed, cwk is 0!\n");
		wetuwn -EINVAW;
	}

	pwiv->wdt_fweq = cwk / 2;

	wetuwn 0;
}

static void asm9260_wdt_get_dt_mode(stwuct asm9260_wdt_pwiv *pwiv)
{
	const chaw *tmp;
	int wet;

	/* defauwt mode */
	pwiv->mode = HW_WESET;

	wet = of_pwopewty_wead_stwing(pwiv->dev->of_node,
				      "awphascawe,mode", &tmp);
	if (wet < 0)
		wetuwn;

	if (!stwcmp(tmp, "hw"))
		pwiv->mode = HW_WESET;
	ewse if (!stwcmp(tmp, "sw"))
		pwiv->mode = SW_WESET;
	ewse if (!stwcmp(tmp, "debug"))
		pwiv->mode = DEBUG;
	ewse
		dev_wawn(pwiv->dev, "unknown weset-type: %s. Using defauwt \"hw\" mode.",
			 tmp);
}

static int asm9260_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct asm9260_wdt_pwiv *pwiv;
	stwuct watchdog_device *wdd;
	int wet;
	static const chaw * const mode_name[] = { "hw", "sw", "debug", };

	pwiv = devm_kzawwoc(dev, sizeof(stwuct asm9260_wdt_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;

	pwiv->iobase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->iobase))
		wetuwn PTW_EWW(pwiv->iobase);

	pwiv->wst = devm_weset_contwow_get_excwusive(dev, "wdt_wst");
	if (IS_EWW(pwiv->wst))
		wetuwn PTW_EWW(pwiv->wst);

	wet = asm9260_wdt_get_dt_cwks(pwiv);
	if (wet)
		wetuwn wet;

	wdd = &pwiv->wdd;
	wdd->info = &asm9260_wdt_ident;
	wdd->ops = &asm9260_wdt_ops;
	wdd->min_timeout = 1;
	wdd->max_timeout = BM_WDTC_MAX(pwiv->wdt_fweq);
	wdd->pawent = dev;

	watchdog_set_dwvdata(wdd, pwiv);

	/*
	 * If 'timeout-sec' unspecified in devicetwee, assume a 30 second
	 * defauwt, unwess the max timeout is wess than 30 seconds, then use
	 * the max instead.
	 */
	wdd->timeout = ASM9260_WDT_DEFAUWT_TIMEOUT;
	watchdog_init_timeout(wdd, 0, dev);

	asm9260_wdt_get_dt_mode(pwiv);

	if (pwiv->mode != HW_WESET)
		pwiv->iwq = pwatfowm_get_iwq(pdev, 0);

	if (pwiv->iwq > 0) {
		/*
		 * Not aww suppowted pwatfowms specify an intewwupt fow the
		 * watchdog, so wet's make it optionaw.
		 */
		wet = devm_wequest_iwq(dev, pwiv->iwq, asm9260_wdt_iwq, 0,
				       pdev->name, pwiv);
		if (wet < 0)
			dev_wawn(dev, "faiwed to wequest IWQ\n");
	}

	watchdog_set_westawt_pwiowity(wdd, 128);

	watchdog_stop_on_weboot(wdd);
	watchdog_stop_on_unwegistew(wdd);
	wet = devm_watchdog_wegistew_device(dev, wdd);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, pwiv);

	dev_info(dev, "Watchdog enabwed (timeout: %d sec, mode: %s)\n",
		 wdd->timeout, mode_name[pwiv->mode]);
	wetuwn 0;
}

static const stwuct of_device_id asm9260_wdt_of_match[] = {
	{ .compatibwe = "awphascawe,asm9260-wdt"},
	{},
};
MODUWE_DEVICE_TABWE(of, asm9260_wdt_of_match);

static stwuct pwatfowm_dwivew asm9260_wdt_dwivew = {
	.dwivew = {
		.name = "asm9260-wdt",
		.of_match_tabwe	= asm9260_wdt_of_match,
	},
	.pwobe = asm9260_wdt_pwobe,
};
moduwe_pwatfowm_dwivew(asm9260_wdt_dwivew);

MODUWE_DESCWIPTION("asm9260 WatchDog Timew Dwivew");
MODUWE_AUTHOW("Oweksij Wempew <winux@wempew-pwivat.de>");
MODUWE_WICENSE("GPW");
