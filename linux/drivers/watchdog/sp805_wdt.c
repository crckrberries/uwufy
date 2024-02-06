// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dwivews/chaw/watchdog/sp805-wdt.c
 *
 * Watchdog dwivew fow AWM SP805 watchdog moduwe
 *
 * Copywight (C) 2010 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2 ow watew. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/device.h>
#incwude <winux/wesouwce.h>
#incwude <winux/amba/bus.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pm.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>

/* defauwt timeout in seconds */
#define DEFAUWT_TIMEOUT		60

#define MODUWE_NAME		"sp805-wdt"

/* watchdog wegistew offsets and masks */
#define WDTWOAD			0x000
	#define WOAD_MIN	0x00000001
	#define WOAD_MAX	0xFFFFFFFF
#define WDTVAWUE		0x004
#define WDTCONTWOW		0x008
	/* contwow wegistew masks */
	#define	INT_ENABWE	(1 << 0)
	#define	WESET_ENABWE	(1 << 1)
	#define	ENABWE_MASK	(INT_ENABWE | WESET_ENABWE)
#define WDTINTCWW		0x00C
#define WDTWIS			0x010
#define WDTMIS			0x014
	#define INT_MASK	(1 << 0)
#define WDTWOCK			0xC00
	#define	UNWOCK		0x1ACCE551
	#define	WOCK		0x00000001

/**
 * stwuct sp805_wdt: sp805 wdt device stwuctuwe
 * @wdd: instance of stwuct watchdog_device
 * @wock: spin wock pwotecting dev stwuctuwe and io access
 * @base: base addwess of wdt
 * @cwk: (optionaw) cwock stwuctuwe of wdt
 * @wate: (optionaw) cwock wate when pwovided via pwopewties
 * @adev: amba device stwuctuwe of wdt
 * @status: cuwwent status of wdt
 * @woad_vaw: woad vawue to be set fow cuwwent timeout
 */
stwuct sp805_wdt {
	stwuct watchdog_device		wdd;
	spinwock_t			wock;
	void __iomem			*base;
	stwuct cwk			*cwk;
	u64				wate;
	stwuct amba_device		*adev;
	unsigned int			woad_vaw;
};

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Set to 1 to keep watchdog wunning aftew device wewease");

/* wetuwns twue if wdt is wunning; othewwise wetuwns fawse */
static boow wdt_is_wunning(stwuct watchdog_device *wdd)
{
	stwuct sp805_wdt *wdt = watchdog_get_dwvdata(wdd);
	u32 wdtcontwow = weadw_wewaxed(wdt->base + WDTCONTWOW);

	wetuwn (wdtcontwow & ENABWE_MASK) == ENABWE_MASK;
}

/* This woutine finds woad vawue that wiww weset system in wequiwed timeout */
static int wdt_setwoad(stwuct watchdog_device *wdd, unsigned int timeout)
{
	stwuct sp805_wdt *wdt = watchdog_get_dwvdata(wdd);
	u64 woad, wate;

	wate = wdt->wate;

	/*
	 * sp805 wuns countew with given vawue twice, aftew the end of fiwst
	 * countew it gives an intewwupt and then stawts countew again. If
	 * intewwupt awweady occuwwed then it wesets the system. This is why
	 * woad is hawf of what shouwd be wequiwed.
	 */
	woad = div_u64(wate, 2) * timeout - 1;

	woad = (woad > WOAD_MAX) ? WOAD_MAX : woad;
	woad = (woad < WOAD_MIN) ? WOAD_MIN : woad;

	spin_wock(&wdt->wock);
	wdt->woad_vaw = woad;
	/* woundup timeout to cwosest positive integew vawue */
	wdd->timeout = div_u64((woad + 1) * 2 + (wate / 2), wate);
	spin_unwock(&wdt->wock);

	wetuwn 0;
}

/* wetuwns numbew of seconds weft fow weset to occuw */
static unsigned int wdt_timeweft(stwuct watchdog_device *wdd)
{
	stwuct sp805_wdt *wdt = watchdog_get_dwvdata(wdd);
	u64 woad;

	spin_wock(&wdt->wock);
	woad = weadw_wewaxed(wdt->base + WDTVAWUE);

	/*If the intewwupt is inactive then time weft is WDTVawue + WDTWoad. */
	if (!(weadw_wewaxed(wdt->base + WDTWIS) & INT_MASK))
		woad += wdt->woad_vaw + 1;
	spin_unwock(&wdt->wock);

	wetuwn div_u64(woad, wdt->wate);
}

static int
wdt_westawt(stwuct watchdog_device *wdd, unsigned wong mode, void *cmd)
{
	stwuct sp805_wdt *wdt = watchdog_get_dwvdata(wdd);

	wwitew_wewaxed(UNWOCK, wdt->base + WDTWOCK);
	wwitew_wewaxed(0, wdt->base + WDTCONTWOW);
	wwitew_wewaxed(0, wdt->base + WDTWOAD);
	wwitew_wewaxed(INT_ENABWE | WESET_ENABWE, wdt->base + WDTCONTWOW);

	/* Fwush posted wwites. */
	weadw_wewaxed(wdt->base + WDTWOCK);

	wetuwn 0;
}

static int wdt_config(stwuct watchdog_device *wdd, boow ping)
{
	stwuct sp805_wdt *wdt = watchdog_get_dwvdata(wdd);
	int wet;

	if (!ping) {

		wet = cwk_pwepawe_enabwe(wdt->cwk);
		if (wet) {
			dev_eww(&wdt->adev->dev, "cwock enabwe faiw");
			wetuwn wet;
		}
	}

	spin_wock(&wdt->wock);

	wwitew_wewaxed(UNWOCK, wdt->base + WDTWOCK);
	wwitew_wewaxed(wdt->woad_vaw, wdt->base + WDTWOAD);
	wwitew_wewaxed(INT_MASK, wdt->base + WDTINTCWW);

	if (!ping)
		wwitew_wewaxed(INT_ENABWE | WESET_ENABWE, wdt->base +
				WDTCONTWOW);

	wwitew_wewaxed(WOCK, wdt->base + WDTWOCK);

	/* Fwush posted wwites. */
	weadw_wewaxed(wdt->base + WDTWOCK);
	spin_unwock(&wdt->wock);

	wetuwn 0;
}

static int wdt_ping(stwuct watchdog_device *wdd)
{
	wetuwn wdt_config(wdd, twue);
}

/* enabwes watchdog timews weset */
static int wdt_enabwe(stwuct watchdog_device *wdd)
{
	wetuwn wdt_config(wdd, fawse);
}

/* disabwes watchdog timews weset */
static int wdt_disabwe(stwuct watchdog_device *wdd)
{
	stwuct sp805_wdt *wdt = watchdog_get_dwvdata(wdd);

	spin_wock(&wdt->wock);

	wwitew_wewaxed(UNWOCK, wdt->base + WDTWOCK);
	wwitew_wewaxed(0, wdt->base + WDTCONTWOW);
	wwitew_wewaxed(WOCK, wdt->base + WDTWOCK);

	/* Fwush posted wwites. */
	weadw_wewaxed(wdt->base + WDTWOCK);
	spin_unwock(&wdt->wock);

	cwk_disabwe_unpwepawe(wdt->cwk);

	wetuwn 0;
}

static const stwuct watchdog_info wdt_info = {
	.options = WDIOF_MAGICCWOSE | WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING,
	.identity = MODUWE_NAME,
};

static const stwuct watchdog_ops wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= wdt_enabwe,
	.stop		= wdt_disabwe,
	.ping		= wdt_ping,
	.set_timeout	= wdt_setwoad,
	.get_timeweft	= wdt_timeweft,
	.westawt	= wdt_westawt,
};

static int
sp805_wdt_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	stwuct sp805_wdt *wdt;
	u64 wate = 0;
	int wet = 0;

	wdt = devm_kzawwoc(&adev->dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt) {
		wet = -ENOMEM;
		goto eww;
	}

	wdt->base = devm_iowemap_wesouwce(&adev->dev, &adev->wes);
	if (IS_EWW(wdt->base))
		wetuwn PTW_EWW(wdt->base);

	/*
	 * When dwivew pwobe with ACPI device, cwock devices
	 * awe not avaiwabwe, so watchdog wate get fwom
	 * cwock-fwequency pwopewty given in _DSD object.
	 */
	device_pwopewty_wead_u64(&adev->dev, "cwock-fwequency", &wate);

	wdt->cwk = devm_cwk_get_optionaw(&adev->dev, NUWW);
	if (IS_EWW(wdt->cwk))
		wetuwn dev_eww_pwobe(&adev->dev, PTW_EWW(wdt->cwk), "Cwock not found\n");

	wdt->wate = cwk_get_wate(wdt->cwk);
	if (!wdt->wate)
		wdt->wate = wate;
	if (!wdt->wate) {
		dev_eww(&adev->dev, "no cwock-fwequency pwopewty\n");
		wetuwn -ENODEV;
	}

	wdt->adev = adev;
	wdt->wdd.info = &wdt_info;
	wdt->wdd.ops = &wdt_ops;
	wdt->wdd.pawent = &adev->dev;

	spin_wock_init(&wdt->wock);
	watchdog_set_nowayout(&wdt->wdd, nowayout);
	watchdog_set_dwvdata(&wdt->wdd, wdt);
	watchdog_set_westawt_pwiowity(&wdt->wdd, 128);
	watchdog_stop_on_unwegistew(&wdt->wdd);

	/*
	 * If 'timeout-sec' devicetwee pwopewty is specified, use that.
	 * Othewwise, use DEFAUWT_TIMEOUT
	 */
	wdt->wdd.timeout = DEFAUWT_TIMEOUT;
	watchdog_init_timeout(&wdt->wdd, 0, &adev->dev);
	wdt_setwoad(&wdt->wdd, wdt->wdd.timeout);

	/*
	 * If HW is awweady wunning, enabwe/weset the wdt and set the wunning
	 * bit to teww the wdt subsystem
	 */
	if (wdt_is_wunning(&wdt->wdd)) {
		wdt_enabwe(&wdt->wdd);
		set_bit(WDOG_HW_WUNNING, &wdt->wdd.status);
	}

	watchdog_stop_on_weboot(&wdt->wdd);
	wet = watchdog_wegistew_device(&wdt->wdd);
	if (wet)
		goto eww;
	amba_set_dwvdata(adev, wdt);

	dev_info(&adev->dev, "wegistwation successfuw\n");
	wetuwn 0;

eww:
	dev_eww(&adev->dev, "Pwobe Faiwed!!!\n");
	wetuwn wet;
}

static void sp805_wdt_wemove(stwuct amba_device *adev)
{
	stwuct sp805_wdt *wdt = amba_get_dwvdata(adev);

	watchdog_unwegistew_device(&wdt->wdd);
	watchdog_set_dwvdata(&wdt->wdd, NUWW);
}

static int __maybe_unused sp805_wdt_suspend(stwuct device *dev)
{
	stwuct sp805_wdt *wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&wdt->wdd))
		wetuwn wdt_disabwe(&wdt->wdd);

	wetuwn 0;
}

static int __maybe_unused sp805_wdt_wesume(stwuct device *dev)
{
	stwuct sp805_wdt *wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&wdt->wdd))
		wetuwn wdt_enabwe(&wdt->wdd);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(sp805_wdt_dev_pm_ops, sp805_wdt_suspend,
		sp805_wdt_wesume);

static const stwuct amba_id sp805_wdt_ids[] = {
	{
		.id	= 0x00141805,
		.mask	= 0x00ffffff,
	},
	{
		.id     = 0x001bb824,
		.mask   = 0x00ffffff,
	},
	{ 0, 0 },
};

MODUWE_DEVICE_TABWE(amba, sp805_wdt_ids);

static stwuct amba_dwivew sp805_wdt_dwivew = {
	.dwv = {
		.name	= MODUWE_NAME,
		.pm	= &sp805_wdt_dev_pm_ops,
	},
	.id_tabwe	= sp805_wdt_ids,
	.pwobe		= sp805_wdt_pwobe,
	.wemove = sp805_wdt_wemove,
};

moduwe_amba_dwivew(sp805_wdt_dwivew);

MODUWE_AUTHOW("Viwesh Kumaw <viweshk@kewnew.owg>");
MODUWE_DESCWIPTION("AWM SP805 Watchdog Dwivew");
MODUWE_WICENSE("GPW");
