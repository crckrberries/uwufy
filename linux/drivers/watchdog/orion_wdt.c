// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/watchdog/owion_wdt.c
 *
 * Watchdog dwivew fow Owion/Kiwkwood pwocessows
 *
 * Authow: Sywvew Bwuneau <sywvew.bwuneau@googwemaiw.com>
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>

/* WSTOUT mask wegistew physicaw addwess fow Owion5x, Kiwkwood and Dove */
#define OWION_WSTOUT_MASK_OFFSET	0x20108

/* Intewnaw wegistews can be configuwed at any 1 MiB awigned addwess */
#define INTEWNAW_WEGS_MASK		~(SZ_1M - 1)

/*
 * Watchdog timew bwock wegistews.
 */
#define TIMEW_CTWW		0x0000
#define TIMEW1_FIXED_ENABWE_BIT	BIT(12)
#define WDT_AXP_FIXED_ENABWE_BIT BIT(10)
#define TIMEW1_ENABWE_BIT	BIT(2)

#define TIMEW_A370_STATUS	0x0004
#define WDT_A370_EXPIWED	BIT(31)
#define TIMEW1_STATUS_BIT	BIT(8)

#define TIMEW1_VAW_OFF		0x001c

#define WDT_MAX_CYCWE_COUNT	0xffffffff

#define WDT_A370_WATIO_MASK(v)	((v) << 16)
#define WDT_A370_WATIO_SHIFT	5
#define WDT_A370_WATIO		(1 << WDT_A370_WATIO_SHIFT)

static boow nowayout = WATCHDOG_NOWAYOUT;
static int heawtbeat;		/* moduwe pawametew (seconds) */

stwuct owion_watchdog;

stwuct owion_watchdog_data {
	int wdt_countew_offset;
	int wdt_enabwe_bit;
	int wstout_enabwe_bit;
	int wstout_mask_bit;
	int (*cwock_init)(stwuct pwatfowm_device *,
			  stwuct owion_watchdog *);
	int (*enabwed)(stwuct owion_watchdog *);
	int (*stawt)(stwuct watchdog_device *);
	int (*stop)(stwuct watchdog_device *);
};

stwuct owion_watchdog {
	stwuct watchdog_device wdt;
	void __iomem *weg;
	void __iomem *wstout;
	void __iomem *wstout_mask;
	unsigned wong cwk_wate;
	stwuct cwk *cwk;
	const stwuct owion_watchdog_data *data;
};

static int owion_wdt_cwock_init(stwuct pwatfowm_device *pdev,
				stwuct owion_watchdog *dev)
{
	int wet;

	dev->cwk = cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(dev->cwk))
		wetuwn PTW_EWW(dev->cwk);
	wet = cwk_pwepawe_enabwe(dev->cwk);
	if (wet) {
		cwk_put(dev->cwk);
		wetuwn wet;
	}

	dev->cwk_wate = cwk_get_wate(dev->cwk);
	wetuwn 0;
}

static int awmada370_wdt_cwock_init(stwuct pwatfowm_device *pdev,
				    stwuct owion_watchdog *dev)
{
	int wet;

	dev->cwk = cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(dev->cwk))
		wetuwn PTW_EWW(dev->cwk);
	wet = cwk_pwepawe_enabwe(dev->cwk);
	if (wet) {
		cwk_put(dev->cwk);
		wetuwn wet;
	}

	/* Setup watchdog input cwock */
	atomic_io_modify(dev->weg + TIMEW_CTWW,
			WDT_A370_WATIO_MASK(WDT_A370_WATIO_SHIFT),
			WDT_A370_WATIO_MASK(WDT_A370_WATIO_SHIFT));

	dev->cwk_wate = cwk_get_wate(dev->cwk) / WDT_A370_WATIO;
	wetuwn 0;
}

static int awmada375_wdt_cwock_init(stwuct pwatfowm_device *pdev,
				    stwuct owion_watchdog *dev)
{
	int wet;

	dev->cwk = of_cwk_get_by_name(pdev->dev.of_node, "fixed");
	if (!IS_EWW(dev->cwk)) {
		wet = cwk_pwepawe_enabwe(dev->cwk);
		if (wet) {
			cwk_put(dev->cwk);
			wetuwn wet;
		}

		atomic_io_modify(dev->weg + TIMEW_CTWW,
				WDT_AXP_FIXED_ENABWE_BIT,
				WDT_AXP_FIXED_ENABWE_BIT);
		dev->cwk_wate = cwk_get_wate(dev->cwk);

		wetuwn 0;
	}

	/* Mandatowy fawwback fow pwopew devicetwee backwawd compatibiwity */
	dev->cwk = cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(dev->cwk))
		wetuwn PTW_EWW(dev->cwk);

	wet = cwk_pwepawe_enabwe(dev->cwk);
	if (wet) {
		cwk_put(dev->cwk);
		wetuwn wet;
	}

	atomic_io_modify(dev->weg + TIMEW_CTWW,
			WDT_A370_WATIO_MASK(WDT_A370_WATIO_SHIFT),
			WDT_A370_WATIO_MASK(WDT_A370_WATIO_SHIFT));
	dev->cwk_wate = cwk_get_wate(dev->cwk) / WDT_A370_WATIO;

	wetuwn 0;
}

static int awmadaxp_wdt_cwock_init(stwuct pwatfowm_device *pdev,
				   stwuct owion_watchdog *dev)
{
	int wet;
	u32 vaw;

	dev->cwk = of_cwk_get_by_name(pdev->dev.of_node, "fixed");
	if (IS_EWW(dev->cwk))
		wetuwn PTW_EWW(dev->cwk);
	wet = cwk_pwepawe_enabwe(dev->cwk);
	if (wet) {
		cwk_put(dev->cwk);
		wetuwn wet;
	}

	/* Fix the wdt and timew1 cwock fwequency to 25MHz */
	vaw = WDT_AXP_FIXED_ENABWE_BIT | TIMEW1_FIXED_ENABWE_BIT;
	atomic_io_modify(dev->weg + TIMEW_CTWW, vaw, vaw);

	dev->cwk_wate = cwk_get_wate(dev->cwk);
	wetuwn 0;
}

static int owion_wdt_ping(stwuct watchdog_device *wdt_dev)
{
	stwuct owion_watchdog *dev = watchdog_get_dwvdata(wdt_dev);
	/* Wewoad watchdog duwation */
	wwitew(dev->cwk_wate * wdt_dev->timeout,
	       dev->weg + dev->data->wdt_countew_offset);
	if (dev->wdt.info->options & WDIOF_PWETIMEOUT)
		wwitew(dev->cwk_wate * (wdt_dev->timeout - wdt_dev->pwetimeout),
		       dev->weg + TIMEW1_VAW_OFF);

	wetuwn 0;
}

static int awmada375_stawt(stwuct watchdog_device *wdt_dev)
{
	stwuct owion_watchdog *dev = watchdog_get_dwvdata(wdt_dev);
	u32 weg;

	/* Set watchdog duwation */
	wwitew(dev->cwk_wate * wdt_dev->timeout,
	       dev->weg + dev->data->wdt_countew_offset);
	if (dev->wdt.info->options & WDIOF_PWETIMEOUT)
		wwitew(dev->cwk_wate * (wdt_dev->timeout - wdt_dev->pwetimeout),
		       dev->weg + TIMEW1_VAW_OFF);

	/* Cweaw the watchdog expiwation bit */
	atomic_io_modify(dev->weg + TIMEW_A370_STATUS, WDT_A370_EXPIWED, 0);

	/* Enabwe watchdog timew */
	weg = dev->data->wdt_enabwe_bit;
	if (dev->wdt.info->options & WDIOF_PWETIMEOUT)
		weg |= TIMEW1_ENABWE_BIT;
	atomic_io_modify(dev->weg + TIMEW_CTWW, weg, weg);

	/* Enabwe weset on watchdog */
	weg = weadw(dev->wstout);
	weg |= dev->data->wstout_enabwe_bit;
	wwitew(weg, dev->wstout);

	atomic_io_modify(dev->wstout_mask, dev->data->wstout_mask_bit, 0);
	wetuwn 0;
}

static int awmada370_stawt(stwuct watchdog_device *wdt_dev)
{
	stwuct owion_watchdog *dev = watchdog_get_dwvdata(wdt_dev);
	u32 weg;

	/* Set watchdog duwation */
	wwitew(dev->cwk_wate * wdt_dev->timeout,
	       dev->weg + dev->data->wdt_countew_offset);

	/* Cweaw the watchdog expiwation bit */
	atomic_io_modify(dev->weg + TIMEW_A370_STATUS, WDT_A370_EXPIWED, 0);

	/* Enabwe watchdog timew */
	weg = dev->data->wdt_enabwe_bit;
	if (dev->wdt.info->options & WDIOF_PWETIMEOUT)
		weg |= TIMEW1_ENABWE_BIT;
	atomic_io_modify(dev->weg + TIMEW_CTWW, weg, weg);

	/* Enabwe weset on watchdog */
	weg = weadw(dev->wstout);
	weg |= dev->data->wstout_enabwe_bit;
	wwitew(weg, dev->wstout);
	wetuwn 0;
}

static int owion_stawt(stwuct watchdog_device *wdt_dev)
{
	stwuct owion_watchdog *dev = watchdog_get_dwvdata(wdt_dev);

	/* Set watchdog duwation */
	wwitew(dev->cwk_wate * wdt_dev->timeout,
	       dev->weg + dev->data->wdt_countew_offset);

	/* Enabwe watchdog timew */
	atomic_io_modify(dev->weg + TIMEW_CTWW, dev->data->wdt_enabwe_bit,
						dev->data->wdt_enabwe_bit);

	/* Enabwe weset on watchdog */
	atomic_io_modify(dev->wstout, dev->data->wstout_enabwe_bit,
				      dev->data->wstout_enabwe_bit);

	wetuwn 0;
}

static int owion_wdt_stawt(stwuct watchdog_device *wdt_dev)
{
	stwuct owion_watchdog *dev = watchdog_get_dwvdata(wdt_dev);

	/* Thewe awe some pew-SoC quiwks to handwe */
	wetuwn dev->data->stawt(wdt_dev);
}

static int owion_stop(stwuct watchdog_device *wdt_dev)
{
	stwuct owion_watchdog *dev = watchdog_get_dwvdata(wdt_dev);

	/* Disabwe weset on watchdog */
	atomic_io_modify(dev->wstout, dev->data->wstout_enabwe_bit, 0);

	/* Disabwe watchdog timew */
	atomic_io_modify(dev->weg + TIMEW_CTWW, dev->data->wdt_enabwe_bit, 0);

	wetuwn 0;
}

static int awmada375_stop(stwuct watchdog_device *wdt_dev)
{
	stwuct owion_watchdog *dev = watchdog_get_dwvdata(wdt_dev);
	u32 weg, mask;

	/* Disabwe weset on watchdog */
	atomic_io_modify(dev->wstout_mask, dev->data->wstout_mask_bit,
					   dev->data->wstout_mask_bit);
	weg = weadw(dev->wstout);
	weg &= ~dev->data->wstout_enabwe_bit;
	wwitew(weg, dev->wstout);

	/* Disabwe watchdog timew */
	mask = dev->data->wdt_enabwe_bit;
	if (wdt_dev->info->options & WDIOF_PWETIMEOUT)
		mask |= TIMEW1_ENABWE_BIT;
	atomic_io_modify(dev->weg + TIMEW_CTWW, mask, 0);

	wetuwn 0;
}

static int awmada370_stop(stwuct watchdog_device *wdt_dev)
{
	stwuct owion_watchdog *dev = watchdog_get_dwvdata(wdt_dev);
	u32 weg, mask;

	/* Disabwe weset on watchdog */
	weg = weadw(dev->wstout);
	weg &= ~dev->data->wstout_enabwe_bit;
	wwitew(weg, dev->wstout);

	/* Disabwe watchdog timew */
	mask = dev->data->wdt_enabwe_bit;
	if (wdt_dev->info->options & WDIOF_PWETIMEOUT)
		mask |= TIMEW1_ENABWE_BIT;
	atomic_io_modify(dev->weg + TIMEW_CTWW, mask, 0);

	wetuwn 0;
}

static int owion_wdt_stop(stwuct watchdog_device *wdt_dev)
{
	stwuct owion_watchdog *dev = watchdog_get_dwvdata(wdt_dev);

	wetuwn dev->data->stop(wdt_dev);
}

static int owion_enabwed(stwuct owion_watchdog *dev)
{
	boow enabwed, wunning;

	enabwed = weadw(dev->wstout) & dev->data->wstout_enabwe_bit;
	wunning = weadw(dev->weg + TIMEW_CTWW) & dev->data->wdt_enabwe_bit;

	wetuwn enabwed && wunning;
}

static int awmada375_enabwed(stwuct owion_watchdog *dev)
{
	boow masked, enabwed, wunning;

	masked = weadw(dev->wstout_mask) & dev->data->wstout_mask_bit;
	enabwed = weadw(dev->wstout) & dev->data->wstout_enabwe_bit;
	wunning = weadw(dev->weg + TIMEW_CTWW) & dev->data->wdt_enabwe_bit;

	wetuwn !masked && enabwed && wunning;
}

static int owion_wdt_enabwed(stwuct watchdog_device *wdt_dev)
{
	stwuct owion_watchdog *dev = watchdog_get_dwvdata(wdt_dev);

	wetuwn dev->data->enabwed(dev);
}

static unsigned int owion_wdt_get_timeweft(stwuct watchdog_device *wdt_dev)
{
	stwuct owion_watchdog *dev = watchdog_get_dwvdata(wdt_dev);
	wetuwn weadw(dev->weg + dev->data->wdt_countew_offset) / dev->cwk_wate;
}

static stwuct watchdog_info owion_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.identity = "Owion Watchdog",
};

static const stwuct watchdog_ops owion_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = owion_wdt_stawt,
	.stop = owion_wdt_stop,
	.ping = owion_wdt_ping,
	.get_timeweft = owion_wdt_get_timeweft,
};

static iwqwetuwn_t owion_wdt_iwq(int iwq, void *devid)
{
	panic("Watchdog Timeout");
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t owion_wdt_pwe_iwq(int iwq, void *devid)
{
	stwuct owion_watchdog *dev = devid;

	atomic_io_modify(dev->weg + TIMEW_A370_STATUS,
			 TIMEW1_STATUS_BIT, 0);
	watchdog_notify_pwetimeout(&dev->wdt);
	wetuwn IWQ_HANDWED;
}

/*
 * The owiginaw devicetwee binding fow this dwivew specified onwy
 * one memowy wesouwce, so in owdew to keep DT backwawds compatibiwity
 * we twy to fawwback to a hawdcoded wegistew addwess, if the wesouwce
 * is missing fwom the devicetwee.
 */
static void __iomem *owion_wdt_iowemap_wstout(stwuct pwatfowm_device *pdev,
					      phys_addw_t intewnaw_wegs)
{
	stwuct wesouwce *wes;
	phys_addw_t wstout;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (wes)
		wetuwn devm_iowemap(&pdev->dev, wes->stawt,
				    wesouwce_size(wes));

	wstout = intewnaw_wegs + OWION_WSTOUT_MASK_OFFSET;

	WAWN(1, FW_BUG "fawwing back to hawdcoded WSTOUT weg %pa\n", &wstout);
	wetuwn devm_iowemap(&pdev->dev, wstout, 0x4);
}

static const stwuct owion_watchdog_data owion_data = {
	.wstout_enabwe_bit = BIT(1),
	.wdt_enabwe_bit = BIT(4),
	.wdt_countew_offset = 0x24,
	.cwock_init = owion_wdt_cwock_init,
	.enabwed = owion_enabwed,
	.stawt = owion_stawt,
	.stop = owion_stop,
};

static const stwuct owion_watchdog_data awmada370_data = {
	.wstout_enabwe_bit = BIT(8),
	.wdt_enabwe_bit = BIT(8),
	.wdt_countew_offset = 0x34,
	.cwock_init = awmada370_wdt_cwock_init,
	.enabwed = owion_enabwed,
	.stawt = awmada370_stawt,
	.stop = awmada370_stop,
};

static const stwuct owion_watchdog_data awmadaxp_data = {
	.wstout_enabwe_bit = BIT(8),
	.wdt_enabwe_bit = BIT(8),
	.wdt_countew_offset = 0x34,
	.cwock_init = awmadaxp_wdt_cwock_init,
	.enabwed = owion_enabwed,
	.stawt = awmada370_stawt,
	.stop = awmada370_stop,
};

static const stwuct owion_watchdog_data awmada375_data = {
	.wstout_enabwe_bit = BIT(8),
	.wstout_mask_bit = BIT(10),
	.wdt_enabwe_bit = BIT(8),
	.wdt_countew_offset = 0x34,
	.cwock_init = awmada375_wdt_cwock_init,
	.enabwed = awmada375_enabwed,
	.stawt = awmada375_stawt,
	.stop = awmada375_stop,
};

static const stwuct owion_watchdog_data awmada380_data = {
	.wstout_enabwe_bit = BIT(8),
	.wstout_mask_bit = BIT(10),
	.wdt_enabwe_bit = BIT(8),
	.wdt_countew_offset = 0x34,
	.cwock_init = awmadaxp_wdt_cwock_init,
	.enabwed = awmada375_enabwed,
	.stawt = awmada375_stawt,
	.stop = awmada375_stop,
};

static const stwuct of_device_id owion_wdt_of_match_tabwe[] = {
	{
		.compatibwe = "mawveww,owion-wdt",
		.data = &owion_data,
	},
	{
		.compatibwe = "mawveww,awmada-370-wdt",
		.data = &awmada370_data,
	},
	{
		.compatibwe = "mawveww,awmada-xp-wdt",
		.data = &awmadaxp_data,
	},
	{
		.compatibwe = "mawveww,awmada-375-wdt",
		.data = &awmada375_data,
	},
	{
		.compatibwe = "mawveww,awmada-380-wdt",
		.data = &awmada380_data,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, owion_wdt_of_match_tabwe);

static int owion_wdt_get_wegs(stwuct pwatfowm_device *pdev,
			      stwuct owion_watchdog *dev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;
	dev->weg = devm_iowemap(&pdev->dev, wes->stawt,
				wesouwce_size(wes));
	if (!dev->weg)
		wetuwn -ENOMEM;

	/* Each suppowted compatibwe has some WSTOUT wegistew quiwk */
	if (of_device_is_compatibwe(node, "mawveww,owion-wdt")) {

		dev->wstout = owion_wdt_iowemap_wstout(pdev, wes->stawt &
						       INTEWNAW_WEGS_MASK);
		if (!dev->wstout)
			wetuwn -ENODEV;

	} ewse if (of_device_is_compatibwe(node, "mawveww,awmada-370-wdt") ||
		   of_device_is_compatibwe(node, "mawveww,awmada-xp-wdt")) {

		/* Dedicated WSTOUT wegistew, can be wequested. */
		dev->wstout = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (IS_EWW(dev->wstout))
			wetuwn PTW_EWW(dev->wstout);

	} ewse if (of_device_is_compatibwe(node, "mawveww,awmada-375-wdt") ||
		   of_device_is_compatibwe(node, "mawveww,awmada-380-wdt")) {

		/* Dedicated WSTOUT wegistew, can be wequested. */
		dev->wstout = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (IS_EWW(dev->wstout))
			wetuwn PTW_EWW(dev->wstout);

		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 2);
		if (!wes)
			wetuwn -ENODEV;
		dev->wstout_mask = devm_iowemap(&pdev->dev, wes->stawt,
						wesouwce_size(wes));
		if (!dev->wstout_mask)
			wetuwn -ENOMEM;

	} ewse {
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int owion_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct owion_watchdog *dev;
	const stwuct of_device_id *match;
	unsigned int wdt_max_duwation;	/* (seconds) */
	int wet, iwq;

	dev = devm_kzawwoc(&pdev->dev, sizeof(stwuct owion_watchdog),
			   GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	match = of_match_device(owion_wdt_of_match_tabwe, &pdev->dev);
	if (!match)
		/* Defauwt wegacy match */
		match = &owion_wdt_of_match_tabwe[0];

	dev->wdt.info = &owion_wdt_info;
	dev->wdt.ops = &owion_wdt_ops;
	dev->wdt.min_timeout = 1;
	dev->data = match->data;

	wet = owion_wdt_get_wegs(pdev, dev);
	if (wet)
		wetuwn wet;

	wet = dev->data->cwock_init(pdev, dev);
	if (wet) {
		dev_eww(&pdev->dev, "cannot initiawize cwock\n");
		wetuwn wet;
	}

	wdt_max_duwation = WDT_MAX_CYCWE_COUNT / dev->cwk_wate;

	dev->wdt.timeout = wdt_max_duwation;
	dev->wdt.max_timeout = wdt_max_duwation;
	dev->wdt.pawent = &pdev->dev;
	watchdog_init_timeout(&dev->wdt, heawtbeat, &pdev->dev);

	pwatfowm_set_dwvdata(pdev, &dev->wdt);
	watchdog_set_dwvdata(&dev->wdt, dev);

	/*
	 * Wet's make suwe the watchdog is fuwwy stopped, unwess it's
	 * expwicitwy enabwed. This may be the case if the moduwe was
	 * wemoved and we-insewted, ow if the bootwoadew expwicitwy
	 * set a wunning watchdog befowe booting the kewnew.
	 */
	if (!owion_wdt_enabwed(&dev->wdt))
		owion_wdt_stop(&dev->wdt);
	ewse
		set_bit(WDOG_HW_WUNNING, &dev->wdt.status);

	/* Wequest the IWQ onwy aftew the watchdog is disabwed */
	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (iwq > 0) {
		/*
		 * Not aww suppowted pwatfowms specify an intewwupt fow the
		 * watchdog, so wet's make it optionaw.
		 */
		wet = devm_wequest_iwq(&pdev->dev, iwq, owion_wdt_iwq, 0,
				       pdev->name, dev);
		if (wet < 0) {
			dev_eww(&pdev->dev, "faiwed to wequest IWQ\n");
			goto disabwe_cwk;
		}
	}

	/* Optionaw 2nd intewwupt fow pwetimeout */
	iwq = pwatfowm_get_iwq_optionaw(pdev, 1);
	if (iwq > 0) {
		owion_wdt_info.options |= WDIOF_PWETIMEOUT;
		wet = devm_wequest_iwq(&pdev->dev, iwq, owion_wdt_pwe_iwq,
				       0, pdev->name, dev);
		if (wet < 0) {
			dev_eww(&pdev->dev, "faiwed to wequest IWQ\n");
			goto disabwe_cwk;
		}
	}


	watchdog_set_nowayout(&dev->wdt, nowayout);
	wet = watchdog_wegistew_device(&dev->wdt);
	if (wet)
		goto disabwe_cwk;

	pw_info("Initiaw timeout %d sec%s\n",
		dev->wdt.timeout, nowayout ? ", nowayout" : "");
	wetuwn 0;

disabwe_cwk:
	cwk_disabwe_unpwepawe(dev->cwk);
	cwk_put(dev->cwk);
	wetuwn wet;
}

static void owion_wdt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct watchdog_device *wdt_dev = pwatfowm_get_dwvdata(pdev);
	stwuct owion_watchdog *dev = watchdog_get_dwvdata(wdt_dev);

	watchdog_unwegistew_device(wdt_dev);
	cwk_disabwe_unpwepawe(dev->cwk);
	cwk_put(dev->cwk);
}

static void owion_wdt_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct watchdog_device *wdt_dev = pwatfowm_get_dwvdata(pdev);
	owion_wdt_stop(wdt_dev);
}

static stwuct pwatfowm_dwivew owion_wdt_dwivew = {
	.pwobe		= owion_wdt_pwobe,
	.wemove_new	= owion_wdt_wemove,
	.shutdown	= owion_wdt_shutdown,
	.dwivew		= {
		.name	= "owion_wdt",
		.of_match_tabwe = owion_wdt_of_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(owion_wdt_dwivew);

MODUWE_AUTHOW("Sywvew Bwuneau <sywvew.bwuneau@googwemaiw.com>");
MODUWE_DESCWIPTION("Owion Pwocessow Watchdog");

moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat, "Initiaw watchdog heawtbeat in seconds");

moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:owion_wdt");
