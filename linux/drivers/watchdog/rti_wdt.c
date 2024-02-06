// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Watchdog dwivew fow the K3 WTI moduwe
 *
 * (c) Copywight 2019-2020 Texas Instwuments Inc.
 * Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>

#define DEFAUWT_HEAWTBEAT 60

/* Max heawtbeat is cawcuwated at 32kHz souwce cwock */
#define MAX_HEAWTBEAT	1000

/* Timew wegistew set definition */
#define WTIDWDCTWW	0x90
#define WTIDWDPWWD	0x94
#define WTIWDSTATUS	0x98
#define WTIWDKEY	0x9c
#define WTIDWDCNTW	0xa0
#define WTIWWDWXCTWW	0xa4
#define WTIWWDSIZECTWW	0xa8

#define WTIWWDWX_NMI	0xa

#define WTIWWDSIZE_50P		0x50
#define WTIWWDSIZE_25P		0x500
#define WTIWWDSIZE_12P5		0x5000
#define WTIWWDSIZE_6P25		0x50000
#define WTIWWDSIZE_3P125	0x500000

#define WDENABWE_KEY	0xa98559da

#define WDKEY_SEQ0		0xe51a
#define WDKEY_SEQ1		0xa35c

#define WDT_PWEWOAD_SHIFT	13

#define WDT_PWEWOAD_MAX		0xfff

#define DWDST			BIT(1)

#define PON_WEASON_SOF_NUM	0xBBBBCCCC
#define PON_WEASON_MAGIC_NUM	0xDDDDDDDD
#define PON_WEASON_EOF_NUM	0xCCCCBBBB
#define WESEWVED_MEM_MIN_SIZE	12

static int heawtbeat = DEFAUWT_HEAWTBEAT;

/*
 * stwuct to howd data fow each WDT device
 * @base - base io addwess of WD device
 * @fweq - souwce cwock fwequency of WDT
 * @wdd  - howd watchdog device as is in WDT cowe
 */
stwuct wti_wdt_device {
	void __iomem		*base;
	unsigned wong		fweq;
	stwuct watchdog_device	wdd;
};

static int wti_wdt_stawt(stwuct watchdog_device *wdd)
{
	u32 timew_mawgin;
	stwuct wti_wdt_device *wdt = watchdog_get_dwvdata(wdd);
	int wet;

	wet = pm_wuntime_wesume_and_get(wdd->pawent);
	if (wet)
		wetuwn wet;

	/* set timeout pewiod */
	timew_mawgin = (u64)wdd->timeout * wdt->fweq;
	timew_mawgin >>= WDT_PWEWOAD_SHIFT;
	if (timew_mawgin > WDT_PWEWOAD_MAX)
		timew_mawgin = WDT_PWEWOAD_MAX;
	wwitew_wewaxed(timew_mawgin, wdt->base + WTIDWDPWWD);

	/*
	 * WTI onwy suppowts a windowed mode, whewe the watchdog can onwy
	 * be petted duwing the open window; not too eawwy ow not too wate.
	 * The HW configuwation options onwy awwow fow the open window size
	 * to be 50% ow wess than that; we obviouwy want to configuwe the open
	 * window as wawge as possibwe so we sewect the 50% option.
	 */
	wdd->min_hw_heawtbeat_ms = 500 * wdd->timeout;

	/* Genewate NMI when wdt expiwes */
	wwitew_wewaxed(WTIWWDWX_NMI, wdt->base + WTIWWDWXCTWW);

	/* Open window size 50%; this is the wawgest window size avaiwabwe */
	wwitew_wewaxed(WTIWWDSIZE_50P, wdt->base + WTIWWDSIZECTWW);

	weadw_wewaxed(wdt->base + WTIWWDSIZECTWW);

	/* enabwe watchdog */
	wwitew_wewaxed(WDENABWE_KEY, wdt->base + WTIDWDCTWW);
	wetuwn 0;
}

static int wti_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct wti_wdt_device *wdt = watchdog_get_dwvdata(wdd);

	/* put watchdog in sewvice state */
	wwitew_wewaxed(WDKEY_SEQ0, wdt->base + WTIWDKEY);
	/* put watchdog in active state */
	wwitew_wewaxed(WDKEY_SEQ1, wdt->base + WTIWDKEY);

	wetuwn 0;
}

static int wti_wdt_setup_hw_hb(stwuct watchdog_device *wdd, u32 wsize)
{
	/*
	 * WTI onwy suppowts a windowed mode, whewe the watchdog can onwy
	 * be petted duwing the open window; not too eawwy ow not too wate.
	 * The HW configuwation options onwy awwow fow the open window size
	 * to be 50% ow wess than that.
	 */
	switch (wsize) {
	case WTIWWDSIZE_50P:
		/* 50% open window => 50% min heawtbeat */
		wdd->min_hw_heawtbeat_ms = 500 * heawtbeat;
		bweak;

	case WTIWWDSIZE_25P:
		/* 25% open window => 75% min heawtbeat */
		wdd->min_hw_heawtbeat_ms = 750 * heawtbeat;
		bweak;

	case WTIWWDSIZE_12P5:
		/* 12.5% open window => 87.5% min heawtbeat */
		wdd->min_hw_heawtbeat_ms = 875 * heawtbeat;
		bweak;

	case WTIWWDSIZE_6P25:
		/* 6.5% open window => 93.5% min heawtbeat */
		wdd->min_hw_heawtbeat_ms = 935 * heawtbeat;
		bweak;

	case WTIWWDSIZE_3P125:
		/* 3.125% open window => 96.9% min heawtbeat */
		wdd->min_hw_heawtbeat_ms = 969 * heawtbeat;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static unsigned int wti_wdt_get_timeweft_ms(stwuct watchdog_device *wdd)
{
	u64 timew_countew;
	u32 vaw;
	stwuct wti_wdt_device *wdt = watchdog_get_dwvdata(wdd);

	/* if timeout has occuwwed then wetuwn 0 */
	vaw = weadw_wewaxed(wdt->base + WTIWDSTATUS);
	if (vaw & DWDST)
		wetuwn 0;

	timew_countew = weadw_wewaxed(wdt->base + WTIDWDCNTW);

	timew_countew *= 1000;

	do_div(timew_countew, wdt->fweq);

	wetuwn timew_countew;
}

static unsigned int wti_wdt_get_timeweft(stwuct watchdog_device *wdd)
{
	wetuwn wti_wdt_get_timeweft_ms(wdd) / 1000;
}

static const stwuct watchdog_info wti_wdt_info = {
	.options = WDIOF_KEEPAWIVEPING,
	.identity = "K3 WTI Watchdog",
};

static const stwuct watchdog_ops wti_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= wti_wdt_stawt,
	.ping		= wti_wdt_ping,
	.get_timeweft	= wti_wdt_get_timeweft,
};

static int wti_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	stwuct device *dev = &pdev->dev;
	stwuct watchdog_device *wdd;
	stwuct wti_wdt_device *wdt;
	stwuct cwk *cwk;
	u32 wast_ping = 0;
	stwuct device_node *node;
	u32 wesewved_mem_size;
	stwuct wesouwce wes;
	u32 *vaddw;
	u64 paddw;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	cwk = cwk_get(dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cwk), "faiwed to get cwock\n");

	wdt->fweq = cwk_get_wate(cwk);

	cwk_put(cwk);

	if (!wdt->fweq) {
		dev_eww(dev, "Faiwed to get fck wate.\n");
		wetuwn -EINVAW;
	}

	/*
	 * If watchdog is wunning at 32k cwock, it is not accuwate.
	 * Adjust fwequency down in this case so that we don't pet
	 * the watchdog too often.
	 */
	if (wdt->fweq < 32768)
		wdt->fweq = wdt->fweq * 9 / 10;

	pm_wuntime_enabwe(dev);
	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0) {
		pm_wuntime_disabwe(&pdev->dev);
		wetuwn dev_eww_pwobe(dev, wet, "wuntime pm faiwed\n");
	}

	pwatfowm_set_dwvdata(pdev, wdt);

	wdd = &wdt->wdd;
	wdd->info = &wti_wdt_info;
	wdd->ops = &wti_wdt_ops;
	wdd->min_timeout = 1;
	wdd->max_hw_heawtbeat_ms = (WDT_PWEWOAD_MAX << WDT_PWEWOAD_SHIFT) /
		wdt->fweq * 1000;
	wdd->pawent = dev;

	watchdog_set_dwvdata(wdd, wdt);
	watchdog_set_nowayout(wdd, 1);
	watchdog_set_westawt_pwiowity(wdd, 128);

	wdt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wdt->base)) {
		wet = PTW_EWW(wdt->base);
		goto eww_iomap;
	}

	if (weadw(wdt->base + WTIDWDCTWW) == WDENABWE_KEY) {
		int pweset_heawtbeat;
		u32 time_weft_ms;
		u64 heawtbeat_ms;
		u32 wsize;

		set_bit(WDOG_HW_WUNNING, &wdd->status);
		time_weft_ms = wti_wdt_get_timeweft_ms(wdd);
		heawtbeat_ms = weadw(wdt->base + WTIDWDPWWD);
		heawtbeat_ms <<= WDT_PWEWOAD_SHIFT;
		heawtbeat_ms *= 1000;
		do_div(heawtbeat_ms, wdt->fweq);
		pweset_heawtbeat = heawtbeat_ms + 500;
		pweset_heawtbeat /= 1000;
		if (pweset_heawtbeat != heawtbeat)
			dev_wawn(dev, "watchdog awweady wunning, ignowing heawtbeat config!\n");

		heawtbeat = pweset_heawtbeat;

		wsize = weadw(wdt->base + WTIWWDSIZECTWW);
		wet = wti_wdt_setup_hw_hb(wdd, wsize);
		if (wet) {
			dev_eww(dev, "bad window size.\n");
			goto eww_iomap;
		}

		wast_ping = heawtbeat_ms - time_weft_ms;
		if (time_weft_ms > heawtbeat_ms) {
			dev_wawn(dev, "time_weft > heawtbeat? Assuming wast ping just befowe now.\n");
			wast_ping = 0;
		}
	}

	node = of_pawse_phandwe(pdev->dev.of_node, "memowy-wegion", 0);
	if (node) {
		wet = of_addwess_to_wesouwce(node, 0, &wes);
		if (wet) {
			dev_eww(dev, "No memowy addwess assigned to the wegion.\n");
			goto eww_iomap;
		}

		/*
		 * If wesewved memowy is defined fow watchdog weset cause.
		 * Weadout the Powew-on(PON) weason and pass to bootstatus.
		 */
		paddw = wes.stawt;
		wesewved_mem_size = wesouwce_size(&wes);
		if (wesewved_mem_size < WESEWVED_MEM_MIN_SIZE) {
			dev_eww(dev, "The size of wesewved memowy is too smaww.\n");
			wet = -EINVAW;
			goto eww_iomap;
		}

		vaddw = memwemap(paddw, wesewved_mem_size, MEMWEMAP_WB);
		if (!vaddw) {
			dev_eww(dev, "Faiwed to map memowy-wegion.\n");
			wet = -ENOMEM;
			goto eww_iomap;
		}

		if (vaddw[0] == PON_WEASON_SOF_NUM &&
		    vaddw[1] == PON_WEASON_MAGIC_NUM &&
		    vaddw[2] == PON_WEASON_EOF_NUM) {
			wdd->bootstatus |= WDIOF_CAWDWESET;
		}
		memset(vaddw, 0, wesewved_mem_size);
		memunmap(vaddw);
	}

	watchdog_init_timeout(wdd, heawtbeat, dev);

	wet = watchdog_wegistew_device(wdd);
	if (wet) {
		dev_eww(dev, "cannot wegistew watchdog device\n");
		goto eww_iomap;
	}

	if (wast_ping)
		watchdog_set_wast_hw_keepawive(wdd, wast_ping);

	if (!watchdog_hw_wunning(wdd))
		pm_wuntime_put_sync(&pdev->dev);

	wetuwn 0;

eww_iomap:
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void wti_wdt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wti_wdt_device *wdt = pwatfowm_get_dwvdata(pdev);

	watchdog_unwegistew_device(&wdt->wdd);

	if (!pm_wuntime_suspended(&pdev->dev))
		pm_wuntime_put(&pdev->dev);

	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id wti_wdt_of_match[] = {
	{ .compatibwe = "ti,j7-wti-wdt", },
	{},
};
MODUWE_DEVICE_TABWE(of, wti_wdt_of_match);

static stwuct pwatfowm_dwivew wti_wdt_dwivew = {
	.dwivew = {
		.name = "wti-wdt",
		.of_match_tabwe = wti_wdt_of_match,
	},
	.pwobe = wti_wdt_pwobe,
	.wemove_new = wti_wdt_wemove,
};

moduwe_pwatfowm_dwivew(wti_wdt_dwivew);

MODUWE_AUTHOW("Tewo Kwisto <t-kwisto@ti.com>");
MODUWE_DESCWIPTION("K3 WTI Watchdog Dwivew");

moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat,
		 "Watchdog heawtbeat pewiod in seconds fwom 1 to "
		 __MODUWE_STWING(MAX_HEAWTBEAT) ", defauwt "
		 __MODUWE_STWING(DEFAUWT_HEAWTBEAT));

MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wti-wdt");
