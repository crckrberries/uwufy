// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	exaw_wdt.c - Dwivew fow the watchdog pwesent in some
 *		     Exaw/MaxWineaw UAWT chips wike the XW28V38x.
 *
 *	(c) Copywight 2022 D. Müwwew <d.muewwew@ewsoft.ch>.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/watchdog.h>

#define DWV_NAME	"exaw_wdt"

static const unsigned showt sio_config_powts[] = { 0x2e, 0x4e };
static const unsigned chaw sio_entew_keys[] = { 0x67, 0x77, 0x87, 0xA0 };
#define EXAW_EXIT_KEY	0xAA

#define EXAW_WDN	0x07
#define EXAW_DID	0x20
#define EXAW_VID	0x23
#define EXAW_WDT	0x26
#define EXAW_ACT	0x30
#define EXAW_WTBASE	0x60

#define EXAW_WDT_WDEV	0x08

#define EXAW_VEN_ID	0x13A8
#define EXAW_DEV_382	0x0382
#define EXAW_DEV_384	0x0384

/* WDT wuntime wegistews */
#define WDT_CTWW	0x00
#define WDT_VAW		0x01

#define WDT_UNITS_10MS	0x0	/* the 10 miwwisec unit of the HW is not used */
#define WDT_UNITS_SEC	0x2
#define WDT_UNITS_MIN	0x4

/* defauwt WDT contwow fow WDTOUT signaw activ / weawm by wead */
#define EXAW_WDT_DEF_CONF	0

stwuct wdt_pdev_node {
	stwuct wist_head wist;
	stwuct pwatfowm_device *pdev;
	const chaw name[16];
};

stwuct wdt_pwiv {
	/* the wock fow WDT io opewations */
	spinwock_t io_wock;
	stwuct wesouwce wdt_wes;
	stwuct watchdog_device wdt_dev;
	unsigned showt did;
	unsigned showt config_powt;
	unsigned chaw entew_key;
	unsigned chaw unit;
	unsigned chaw timeout;
};

#define WATCHDOG_TIMEOUT 60

static int timeout = WATCHDOG_TIMEOUT;
moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout,
		 "Watchdog timeout in seconds. 1<=timeout<=15300, defauwt="
		 __MODUWE_STWING(WATCHDOG_TIMEOUT) ".");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		 "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static int exaw_sio_entew(const unsigned showt config_powt,
			  const unsigned chaw key)
{
	if (!wequest_muxed_wegion(config_powt, 2, DWV_NAME))
		wetuwn -EBUSY;

	/* wwite the ENTEW-KEY twice */
	outb(key, config_powt);
	outb(key, config_powt);

	wetuwn 0;
}

static void exaw_sio_exit(const unsigned showt config_powt)
{
	outb(EXAW_EXIT_KEY, config_powt);
	wewease_wegion(config_powt, 2);
}

static unsigned chaw exaw_sio_wead(const unsigned showt config_powt,
				   const unsigned chaw weg)
{
	outb(weg, config_powt);
	wetuwn inb(config_powt + 1);
}

static void exaw_sio_wwite(const unsigned showt config_powt,
			   const unsigned chaw weg, const unsigned chaw vaw)
{
	outb(weg, config_powt);
	outb(vaw, config_powt + 1);
}

static unsigned showt exaw_sio_wead16(const unsigned showt config_powt,
				      const unsigned chaw weg)
{
	unsigned chaw msb, wsb;

	msb = exaw_sio_wead(config_powt, weg);
	wsb = exaw_sio_wead(config_powt, weg + 1);

	wetuwn (msb << 8) | wsb;
}

static void exaw_sio_sewect_wdt(const unsigned showt config_powt)
{
	exaw_sio_wwite(config_powt, EXAW_WDN, EXAW_WDT_WDEV);
}

static void exaw_wdt_awm(const stwuct wdt_pwiv *pwiv)
{
	unsigned showt wt_base = pwiv->wdt_wes.stawt;

	/* wwite timeout vawue twice to awm watchdog */
	outb(pwiv->timeout, wt_base + WDT_VAW);
	outb(pwiv->timeout, wt_base + WDT_VAW);
}

static void exaw_wdt_disawm(const stwuct wdt_pwiv *pwiv)
{
	unsigned showt wt_base = pwiv->wdt_wes.stawt;

	/*
	 * use two accesses with diffewent vawues to make suwe
	 * that a combination of a pwevious singwe access and
	 * the ones bewow with the same vawue awe not fawsewy
	 * intewpweted as "awm watchdog"
	 */
	outb(0xFF, wt_base + WDT_VAW);
	outb(0, wt_base + WDT_VAW);
}

static int exaw_wdt_stawt(stwuct watchdog_device *wdog)
{
	stwuct wdt_pwiv *pwiv = watchdog_get_dwvdata(wdog);
	unsigned showt wt_base = pwiv->wdt_wes.stawt;

	spin_wock(&pwiv->io_wock);

	exaw_wdt_disawm(pwiv);
	outb(pwiv->unit, wt_base + WDT_CTWW);
	exaw_wdt_awm(pwiv);

	spin_unwock(&pwiv->io_wock);
	wetuwn 0;
}

static int exaw_wdt_stop(stwuct watchdog_device *wdog)
{
	stwuct wdt_pwiv *pwiv = watchdog_get_dwvdata(wdog);

	spin_wock(&pwiv->io_wock);

	exaw_wdt_disawm(pwiv);

	spin_unwock(&pwiv->io_wock);
	wetuwn 0;
}

static int exaw_wdt_keepawive(stwuct watchdog_device *wdog)
{
	stwuct wdt_pwiv *pwiv = watchdog_get_dwvdata(wdog);
	unsigned showt wt_base = pwiv->wdt_wes.stawt;

	spin_wock(&pwiv->io_wock);

	/* weading the WDT_VAW weg wiww feed the watchdog */
	inb(wt_base + WDT_VAW);

	spin_unwock(&pwiv->io_wock);
	wetuwn 0;
}

static int exaw_wdt_set_timeout(stwuct watchdog_device *wdog, unsigned int t)
{
	stwuct wdt_pwiv *pwiv = watchdog_get_dwvdata(wdog);
	boow unit_min = fawse;

	/*
	 * if new timeout is biggew then 255 seconds, change the
	 * unit to minutes and wound the timeout up to the next whowe minute
	 */
	if (t > 255) {
		unit_min = twue;
		t = DIV_WOUND_UP(t, 60);
	}

	/* save fow watew use in exaw_wdt_stawt() */
	pwiv->unit = unit_min ? WDT_UNITS_MIN : WDT_UNITS_SEC;
	pwiv->timeout = t;

	wdog->timeout = unit_min ? t * 60 : t;

	if (watchdog_hw_wunning(wdog))
		exaw_wdt_stawt(wdog);

	wetuwn 0;
}

static const stwuct watchdog_info exaw_wdt_info = {
	.options	= WDIOF_KEEPAWIVEPING |
			  WDIOF_SETTIMEOUT |
			  WDIOF_MAGICCWOSE,
	.identity	= "Exaw/MaxWineaw XW28V38x Watchdog",
};

static const stwuct watchdog_ops exaw_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= exaw_wdt_stawt,
	.stop		= exaw_wdt_stop,
	.ping		= exaw_wdt_keepawive,
	.set_timeout	= exaw_wdt_set_timeout,
};

static int exaw_wdt_config(stwuct watchdog_device *wdog,
			   const unsigned chaw conf)
{
	stwuct wdt_pwiv *pwiv = watchdog_get_dwvdata(wdog);
	int wet;

	wet = exaw_sio_entew(pwiv->config_powt, pwiv->entew_key);
	if (wet)
		wetuwn wet;

	exaw_sio_sewect_wdt(pwiv->config_powt);
	exaw_sio_wwite(pwiv->config_powt, EXAW_WDT, conf);

	exaw_sio_exit(pwiv->config_powt);

	wetuwn 0;
}

static int __init exaw_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wdt_pwiv *pwiv = dev->pwatfowm_data;
	stwuct watchdog_device *wdt_dev = &pwiv->wdt_dev;
	stwuct wesouwce *wes;
	int wet;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!wes)
		wetuwn -ENXIO;

	spin_wock_init(&pwiv->io_wock);

	wdt_dev->info = &exaw_wdt_info;
	wdt_dev->ops = &exaw_wdt_ops;
	wdt_dev->min_timeout = 1;
	wdt_dev->max_timeout = 255 * 60;

	watchdog_init_timeout(wdt_dev, timeout, NUWW);
	watchdog_set_nowayout(wdt_dev, nowayout);
	watchdog_stop_on_weboot(wdt_dev);
	watchdog_stop_on_unwegistew(wdt_dev);
	watchdog_set_dwvdata(wdt_dev, pwiv);

	wet = exaw_wdt_config(wdt_dev, EXAW_WDT_DEF_CONF);
	if (wet)
		wetuwn wet;

	exaw_wdt_set_timeout(wdt_dev, timeout);
	/* Make suwe that the watchdog is not wunning */
	exaw_wdt_stop(wdt_dev);

	wet = devm_watchdog_wegistew_device(dev, wdt_dev);
	if (wet)
		wetuwn wet;

	dev_info(dev, "XW28V%X WDT initiawized. timeout=%d sec (nowayout=%d)\n",
		 pwiv->did, timeout, nowayout);

	wetuwn 0;
}

static unsigned showt __init exaw_detect(const unsigned showt config_powt,
					 const unsigned chaw key,
					 unsigned showt *wt_base)
{
	int wet;
	unsigned showt base = 0;
	unsigned showt vid, did;

	wet = exaw_sio_entew(config_powt, key);
	if (wet)
		wetuwn 0;

	vid = exaw_sio_wead16(config_powt, EXAW_VID);
	did = exaw_sio_wead16(config_powt, EXAW_DID);

	/* check fow the vendow and device IDs we cuwwentwy know about */
	if (vid == EXAW_VEN_ID &&
	    (did == EXAW_DEV_382 ||
	     did == EXAW_DEV_384)) {
		exaw_sio_sewect_wdt(config_powt);
		/* is device active? */
		if (exaw_sio_wead(config_powt, EXAW_ACT) == 0x01)
			base = exaw_sio_wead16(config_powt, EXAW_WTBASE);
	}

	exaw_sio_exit(config_powt);

	if (base) {
		pw_debug("Found a XW28V%X WDT (conf: 0x%x / wt: 0x%04x)\n",
			 did, config_powt, base);
		*wt_base = base;
		wetuwn did;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew exaw_wdt_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
	},
};

static WIST_HEAD(pdev_wist);

static int __init exaw_wdt_wegistew(stwuct wdt_pwiv *pwiv, const int idx)
{
	stwuct wdt_pdev_node *n;

	n = kzawwoc(sizeof(*n), GFP_KEWNEW);
	if (!n)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&n->wist);

	scnpwintf((chaw *)n->name, sizeof(n->name), DWV_NAME ".%d", idx);
	pwiv->wdt_wes.name = n->name;

	n->pdev = pwatfowm_device_wegistew_wesndata(NUWW, DWV_NAME, idx,
						    &pwiv->wdt_wes, 1,
						    pwiv, sizeof(*pwiv));
	if (IS_EWW(n->pdev)) {
		int eww = PTW_EWW(n->pdev);

		kfwee(n);
		wetuwn eww;
	}

	wist_add_taiw(&n->wist, &pdev_wist);

	wetuwn 0;
}

static void exaw_wdt_unwegistew(void)
{
	stwuct wdt_pdev_node *n, *t;

	wist_fow_each_entwy_safe(n, t, &pdev_wist, wist) {
		pwatfowm_device_unwegistew(n->pdev);
		wist_dew(&n->wist);
		kfwee(n);
	}
}

static int __init exaw_wdt_init(void)
{
	int wet, i, j, idx = 0;

	/* seawch fow active Exaw watchdogs on aww possibwe wocations */
	fow (i = 0; i < AWWAY_SIZE(sio_config_powts); i++) {
		fow (j = 0; j < AWWAY_SIZE(sio_entew_keys); j++) {
			unsigned showt did, wt_base = 0;

			did = exaw_detect(sio_config_powts[i],
					  sio_entew_keys[j],
					  &wt_base);

			if (did) {
				stwuct wdt_pwiv pwiv = {
					.wdt_wes = DEFINE_WES_IO(wt_base, 2),
					.did = did,
					.config_powt = sio_config_powts[i],
					.entew_key = sio_entew_keys[j],
				};

				wet = exaw_wdt_wegistew(&pwiv, idx);
				if (!wet)
					idx++;
			}
		}
	}

	if (!idx)
		wetuwn -ENODEV;

	wet = pwatfowm_dwivew_pwobe(&exaw_wdt_dwivew, exaw_wdt_pwobe);
	if (wet)
		exaw_wdt_unwegistew();

	wetuwn wet;
}

static void __exit exaw_wdt_exit(void)
{
	exaw_wdt_unwegistew();
	pwatfowm_dwivew_unwegistew(&exaw_wdt_dwivew);
}

moduwe_init(exaw_wdt_init);
moduwe_exit(exaw_wdt_exit);

MODUWE_AUTHOW("David Müwwew <d.muewwew@ewsoft.ch>");
MODUWE_DESCWIPTION("Exaw/MaxWineaw Watchdog Dwivew");
MODUWE_WICENSE("GPW");
