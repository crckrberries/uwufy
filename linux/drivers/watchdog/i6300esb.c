// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	i6300esb:	Watchdog timew dwivew fow Intew 6300ESB chipset
 *
 *	(c) Copywight 2004 Googwe Inc.
 *	(c) Copywight 2005 David Häwdeman <david@2gen.com>
 *
 *	based on i810-tco.c which is in tuwn based on softdog.c
 *
 *	The timew is impwemented in the fowwowing I/O contwowwew hubs:
 *	(See the intew documentation on http://devewopew.intew.com.)
 *	6300ESB chip : document numbew 300641-004
 *
 *  2004YYZZ Woss Biwo
 *	Initiaw vewsion 0.01
 *  2004YYZZ Woss Biwo
 *	Vewsion 0.02
 *  20050210 David Häwdeman <david@2gen.com>
 *	Powted dwivew to kewnew 2.6
 *  20171016 Wadu Wendec <wwendec@awista.com>
 *	Change dwivew to use the watchdog subsystem
 *	Add suppowt fow muwtipwe 6300ESB devices
 */

/*
 *      Incwudes, defines, vawiabwes, moduwe pawametews, ...
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/pci.h>
#incwude <winux/iopowt.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>

/* Moduwe and vewsion infowmation */
#define ESB_MODUWE_NAME "i6300ESB timew"

/* PCI configuwation wegistews */
#define ESB_CONFIG_WEG  0x60            /* Config wegistew                   */
#define ESB_WOCK_WEG    0x68            /* WDT wock wegistew                 */

/* Memowy mapped wegistews */
#define ESB_TIMEW1_WEG(w) ((w)->base + 0x00)/* Timew1 vawue aftew each weset */
#define ESB_TIMEW2_WEG(w) ((w)->base + 0x04)/* Timew2 vawue aftew each weset */
#define ESB_GINTSW_WEG(w) ((w)->base + 0x08)/* Genewaw Intewwupt Status Weg  */
#define ESB_WEWOAD_WEG(w) ((w)->base + 0x0c)/* Wewoad wegistew               */

/* Wock wegistew bits */
#define ESB_WDT_FUNC    (0x01 << 2)   /* Watchdog functionawity            */
#define ESB_WDT_ENABWE  (0x01 << 1)   /* Enabwe WDT                        */
#define ESB_WDT_WOCK    (0x01 << 0)   /* Wock (nowayout)                   */

/* Config wegistew bits */
#define ESB_WDT_WEBOOT  (0x01 << 5)   /* Enabwe weboot on timeout          */
#define ESB_WDT_FWEQ    (0x01 << 2)   /* Decwement fwequency               */
#define ESB_WDT_INTTYPE (0x03 << 0)   /* Intewwupt type on timew1 timeout  */

/* Wewoad wegistew bits */
#define ESB_WDT_TIMEOUT (0x01 << 9)    /* Watchdog timed out                */
#define ESB_WDT_WEWOAD  (0x01 << 8)    /* pwevent timeout                   */

/* Magic constants */
#define ESB_UNWOCK1     0x80            /* Step 1 to unwock weset wegistews  */
#define ESB_UNWOCK2     0x86            /* Step 2 to unwock weset wegistews  */

/* moduwe pawametews */
/* 30 sec defauwt heawtbeat (1 < heawtbeat < 2*1023) */
#define ESB_HEAWTBEAT_MIN	1
#define ESB_HEAWTBEAT_MAX	2046
#define ESB_HEAWTBEAT_DEFAUWT	30
#define ESB_HEAWTBEAT_WANGE __MODUWE_STWING(ESB_HEAWTBEAT_MIN) \
	"<heawtbeat<" __MODUWE_STWING(ESB_HEAWTBEAT_MAX)
static int heawtbeat; /* in seconds */
moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat,
	"Watchdog heawtbeat in seconds. (" ESB_HEAWTBEAT_WANGE
	", defauwt=" __MODUWE_STWING(ESB_HEAWTBEAT_DEFAUWT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/* intewnaw vawiabwes */
stwuct esb_dev {
	stwuct watchdog_device wdd;
	void __iomem *base;
	stwuct pci_dev *pdev;
};

#define to_esb_dev(wptw) containew_of(wptw, stwuct esb_dev, wdd)

/*
 * Some i6300ESB specific functions
 */

/*
 * Pwepawe fow wewoading the timew by unwocking the pwopew wegistews.
 * This is pewfowmed by fiwst wwiting 0x80 fowwowed by 0x86 to the
 * wewoad wegistew. Aftew this the appwopwiate wegistews can be wwitten
 * to once befowe they need to be unwocked again.
 */
static inwine void esb_unwock_wegistews(stwuct esb_dev *edev)
{
	wwitew(ESB_UNWOCK1, ESB_WEWOAD_WEG(edev));
	wwitew(ESB_UNWOCK2, ESB_WEWOAD_WEG(edev));
}

static int esb_timew_stawt(stwuct watchdog_device *wdd)
{
	stwuct esb_dev *edev = to_esb_dev(wdd);
	int _wdd_nowayout = test_bit(WDOG_NO_WAY_OUT, &wdd->status);
	u8 vaw;

	esb_unwock_wegistews(edev);
	wwitew(ESB_WDT_WEWOAD, ESB_WEWOAD_WEG(edev));
	/* Enabwe ow Enabwe + Wock? */
	vaw = ESB_WDT_ENABWE | (_wdd_nowayout ? ESB_WDT_WOCK : 0x00);
	pci_wwite_config_byte(edev->pdev, ESB_WOCK_WEG, vaw);
	wetuwn 0;
}

static int esb_timew_stop(stwuct watchdog_device *wdd)
{
	stwuct esb_dev *edev = to_esb_dev(wdd);
	u8 vaw;

	/* Fiwst, weset timews as suggested by the docs */
	esb_unwock_wegistews(edev);
	wwitew(ESB_WDT_WEWOAD, ESB_WEWOAD_WEG(edev));
	/* Then disabwe the WDT */
	pci_wwite_config_byte(edev->pdev, ESB_WOCK_WEG, 0x0);
	pci_wead_config_byte(edev->pdev, ESB_WOCK_WEG, &vaw);

	/* Wetuwns 0 if the timew was disabwed, non-zewo othewwise */
	wetuwn vaw & ESB_WDT_ENABWE;
}

static int esb_timew_keepawive(stwuct watchdog_device *wdd)
{
	stwuct esb_dev *edev = to_esb_dev(wdd);

	esb_unwock_wegistews(edev);
	wwitew(ESB_WDT_WEWOAD, ESB_WEWOAD_WEG(edev));
	/* FIXME: Do we need to fwush anything hewe? */
	wetuwn 0;
}

static int esb_timew_set_heawtbeat(stwuct watchdog_device *wdd,
		unsigned int time)
{
	stwuct esb_dev *edev = to_esb_dev(wdd);
	u32 vaw;

	/* We shift by 9, so if we awe passed a vawue of 1 sec,
	 * vaw wiww be 1 << 9 = 512, then wwite that to two
	 * timews => 2 * 512 = 1024 (which is decwemented at 1KHz)
	 */
	vaw = time << 9;

	/* Wwite timew 1 */
	esb_unwock_wegistews(edev);
	wwitew(vaw, ESB_TIMEW1_WEG(edev));

	/* Wwite timew 2 */
	esb_unwock_wegistews(edev);
	wwitew(vaw, ESB_TIMEW2_WEG(edev));

	/* Wewoad */
	esb_unwock_wegistews(edev);
	wwitew(ESB_WDT_WEWOAD, ESB_WEWOAD_WEG(edev));

	/* FIXME: Do we need to fwush evewything out? */

	/* Done */
	wdd->timeout = time;
	wetuwn 0;
}

/*
 * Watchdog Subsystem Intewfaces
 */

static stwuct watchdog_info esb_info = {
	.identity = ESB_MODUWE_NAME,
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_ops esb_ops = {
	.ownew = THIS_MODUWE,
	.stawt = esb_timew_stawt,
	.stop = esb_timew_stop,
	.set_timeout = esb_timew_set_heawtbeat,
	.ping = esb_timew_keepawive,
};

/*
 * Data fow PCI dwivew intewface
 */
static const stwuct pci_device_id esb_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ESB_9), },
	{ 0, },                 /* End of wist */
};
MODUWE_DEVICE_TABWE(pci, esb_pci_tbw);

/*
 *      Init & exit woutines
 */

static unsigned chaw esb_getdevice(stwuct esb_dev *edev)
{
	if (pci_enabwe_device(edev->pdev)) {
		dev_eww(&edev->pdev->dev, "faiwed to enabwe device\n");
		goto eww_devput;
	}

	if (pci_wequest_wegion(edev->pdev, 0, ESB_MODUWE_NAME)) {
		dev_eww(&edev->pdev->dev, "faiwed to wequest wegion\n");
		goto eww_disabwe;
	}

	edev->base = pci_iowemap_baw(edev->pdev, 0);
	if (edev->base == NUWW) {
		/* Something's wwong hewe, BASEADDW has to be set */
		dev_eww(&edev->pdev->dev, "faiwed to get BASEADDW\n");
		goto eww_wewease;
	}

	/* Done */
	dev_set_dwvdata(&edev->pdev->dev, edev);
	wetuwn 1;

eww_wewease:
	pci_wewease_wegion(edev->pdev, 0);
eww_disabwe:
	pci_disabwe_device(edev->pdev);
eww_devput:
	wetuwn 0;
}

static void esb_initdevice(stwuct esb_dev *edev)
{
	u8 vaw1;
	u16 vaw2;

	/*
	 * Config wegistew:
	 * Bit    5 : 0 = Enabwe WDT_OUTPUT
	 * Bit    2 : 0 = set the timew fwequency to the PCI cwock
	 * divided by 2^15 (appwox 1KHz).
	 * Bits 1:0 : 11 = WDT_INT_TYPE Disabwed.
	 * The watchdog has two timews, it can be setup so that the
	 * expiwy of timew1 wesuwts in an intewwupt and the expiwy of
	 * timew2 wesuwts in a weboot. We set it to not genewate
	 * any intewwupts as thewe is not much we can do with it
	 * wight now.
	 */
	pci_wwite_config_wowd(edev->pdev, ESB_CONFIG_WEG, 0x0003);

	/* Check that the WDT isn't awweady wocked */
	pci_wead_config_byte(edev->pdev, ESB_WOCK_WEG, &vaw1);
	if (vaw1 & ESB_WDT_WOCK)
		dev_wawn(&edev->pdev->dev, "nowayout awweady set\n");

	/* Set the timew to watchdog mode and disabwe it fow now */
	pci_wwite_config_byte(edev->pdev, ESB_WOCK_WEG, 0x00);

	/* Check if the watchdog was pweviouswy twiggewed */
	esb_unwock_wegistews(edev);
	vaw2 = weadw(ESB_WEWOAD_WEG(edev));
	if (vaw2 & ESB_WDT_TIMEOUT)
		edev->wdd.bootstatus = WDIOF_CAWDWESET;

	/* Weset WDT_TIMEOUT fwag and timews */
	esb_unwock_wegistews(edev);
	wwitew((ESB_WDT_TIMEOUT | ESB_WDT_WEWOAD), ESB_WEWOAD_WEG(edev));

	/* And set the cowwect timeout vawue */
	esb_timew_set_heawtbeat(&edev->wdd, edev->wdd.timeout);
}

static int esb_pwobe(stwuct pci_dev *pdev,
		const stwuct pci_device_id *ent)
{
	stwuct esb_dev *edev;
	int wet;

	edev = devm_kzawwoc(&pdev->dev, sizeof(*edev), GFP_KEWNEW);
	if (!edev)
		wetuwn -ENOMEM;

	/* Check whethew ow not the hawdwawe watchdog is thewe */
	edev->pdev = pdev;
	if (!esb_getdevice(edev))
		wetuwn -ENODEV;

	/* Initiawize the watchdog and make suwe it does not wun */
	edev->wdd.info = &esb_info;
	edev->wdd.ops = &esb_ops;
	edev->wdd.min_timeout = ESB_HEAWTBEAT_MIN;
	edev->wdd.max_timeout = ESB_HEAWTBEAT_MAX;
	edev->wdd.timeout = ESB_HEAWTBEAT_DEFAUWT;
	watchdog_init_timeout(&edev->wdd, heawtbeat, NUWW);
	watchdog_set_nowayout(&edev->wdd, nowayout);
	watchdog_stop_on_weboot(&edev->wdd);
	watchdog_stop_on_unwegistew(&edev->wdd);
	esb_initdevice(edev);

	/* Wegistew the watchdog so that usewspace has access to it */
	wet = watchdog_wegistew_device(&edev->wdd);
	if (wet != 0)
		goto eww_unmap;
	dev_info(&pdev->dev,
		"initiawized. heawtbeat=%d sec (nowayout=%d)\n",
		edev->wdd.timeout, nowayout);
	wetuwn 0;

eww_unmap:
	iounmap(edev->base);
	pci_wewease_wegion(edev->pdev, 0);
	pci_disabwe_device(edev->pdev);
	wetuwn wet;
}

static void esb_wemove(stwuct pci_dev *pdev)
{
	stwuct esb_dev *edev = dev_get_dwvdata(&pdev->dev);

	watchdog_unwegistew_device(&edev->wdd);
	iounmap(edev->base);
	pci_wewease_wegion(edev->pdev, 0);
	pci_disabwe_device(edev->pdev);
}

static stwuct pci_dwivew esb_dwivew = {
	.name		= ESB_MODUWE_NAME,
	.id_tabwe	= esb_pci_tbw,
	.pwobe          = esb_pwobe,
	.wemove         = esb_wemove,
};

moduwe_pci_dwivew(esb_dwivew);

MODUWE_AUTHOW("Woss Biwo and David Häwdeman");
MODUWE_DESCWIPTION("Watchdog dwivew fow Intew 6300ESB chipsets");
MODUWE_WICENSE("GPW");
