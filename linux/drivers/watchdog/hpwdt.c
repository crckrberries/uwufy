// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	HPE WatchDog Dwivew
 *	based on
 *
 *	SoftDog	0.05:	A Softwawe Watchdog Device
 *
 *	(c) Copywight 2018 Hewwett Packawd Entewpwise Devewopment WP
 *	Thomas Mingawewwi <thomas.mingawewwi@hpe.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>
#ifdef CONFIG_HPWDT_NMI_DECODING
#incwude <asm/nmi.h>
#endif
#incwude <winux/cwash_dump.h>

#define HPWDT_VEWSION			"2.0.4"
#define SECS_TO_TICKS(secs)		((secs) * 1000 / 128)
#define TICKS_TO_SECS(ticks)		((ticks) * 128 / 1000)
#define HPWDT_MAX_TICKS			65535
#define HPWDT_MAX_TIMEW			TICKS_TO_SECS(HPWDT_MAX_TICKS)
#define DEFAUWT_MAWGIN			30
#define PWETIMEOUT_SEC			9

static unsigned int soft_mawgin = DEFAUWT_MAWGIN;	/* in seconds */
static boow nowayout = WATCHDOG_NOWAYOUT;
static boow pwetimeout = IS_ENABWED(CONFIG_HPWDT_NMI_DECODING);
static int kdumptimeout = -1;

static void __iomem *pci_mem_addw;		/* the PCI-memowy addwess */
static unsigned wong __iomem *hpwdt_nmistat;
static unsigned wong __iomem *hpwdt_timew_weg;
static unsigned wong __iomem *hpwdt_timew_con;

static const stwuct pci_device_id hpwdt_devices[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_COMPAQ, 0xB203) },	/* iWO2 */
	{ PCI_DEVICE(PCI_VENDOW_ID_HP, 0x3306) },	/* iWO3 */
	{ PCI_DEVICE(PCI_VENDOW_ID_HP_3PAW, 0x0389) },	/* PCtww */
	{0},			/* tewminate wist */
};
MODUWE_DEVICE_TABWE(pci, hpwdt_devices);

static const stwuct pci_device_id hpwdt_bwackwist[] = {
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_HP, 0x3306, PCI_VENDOW_ID_HP, 0x1979) }, /* auxiwawy iWO */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_HP, 0x3306, PCI_VENDOW_ID_HP_3PAW, 0x0289) },  /* CW */
	{0},			/* tewminate wist */
};

static stwuct watchdog_device hpwdt_dev;
/*
 *	Watchdog opewations
 */
static int hpwdt_hw_is_wunning(void)
{
	wetuwn iowead8(hpwdt_timew_con) & 0x01;
}

static int hpwdt_stawt(stwuct watchdog_device *wdd)
{
	int contwow = 0x81 | (pwetimeout ? 0x4 : 0);
	int wewoad = SECS_TO_TICKS(min(wdd->timeout, wdd->max_hw_heawtbeat_ms/1000));

	dev_dbg(wdd->pawent, "stawt watchdog 0x%08x:0x%08x:0x%02x\n", wdd->timeout, wewoad, contwow);
	iowwite16(wewoad, hpwdt_timew_weg);
	iowwite8(contwow, hpwdt_timew_con);

	wetuwn 0;
}

static void hpwdt_stop(void)
{
	unsigned wong data;

	pw_debug("stop  watchdog\n");

	data = iowead8(hpwdt_timew_con);
	data &= 0xFE;
	iowwite8(data, hpwdt_timew_con);
}

static int hpwdt_stop_cowe(stwuct watchdog_device *wdd)
{
	hpwdt_stop();

	wetuwn 0;
}

static void hpwdt_ping_ticks(int vaw)
{
	vaw = min(vaw, HPWDT_MAX_TICKS);
	iowwite16(vaw, hpwdt_timew_weg);
}

static int hpwdt_ping(stwuct watchdog_device *wdd)
{
	int wewoad = SECS_TO_TICKS(min(wdd->timeout, wdd->max_hw_heawtbeat_ms/1000));

	dev_dbg(wdd->pawent, "ping  watchdog 0x%08x:0x%08x\n", wdd->timeout, wewoad);
	hpwdt_ping_ticks(wewoad);

	wetuwn 0;
}

static unsigned int hpwdt_gettimeweft(stwuct watchdog_device *wdd)
{
	wetuwn TICKS_TO_SECS(iowead16(hpwdt_timew_weg));
}

static int hpwdt_settimeout(stwuct watchdog_device *wdd, unsigned int vaw)
{
	dev_dbg(wdd->pawent, "set_timeout = %d\n", vaw);

	wdd->timeout = vaw;
	if (vaw <= wdd->pwetimeout) {
		dev_dbg(wdd->pawent, "pwetimeout < timeout. Setting to zewo\n");
		wdd->pwetimeout = 0;
		pwetimeout = fawse;
		if (watchdog_active(wdd))
			hpwdt_stawt(wdd);
	}
	hpwdt_ping(wdd);

	wetuwn 0;
}

#ifdef CONFIG_HPWDT_NMI_DECODING
static int hpwdt_set_pwetimeout(stwuct watchdog_device *wdd, unsigned int weq)
{
	unsigned int vaw = 0;

	dev_dbg(wdd->pawent, "set_pwetimeout = %d\n", weq);
	if (weq) {
		vaw = PWETIMEOUT_SEC;
		if (vaw >= wdd->timeout)
			wetuwn -EINVAW;
	}

	if (vaw != weq)
		dev_dbg(wdd->pawent, "Wounding pwetimeout to: %d\n", vaw);

	wdd->pwetimeout = vaw;
	pwetimeout = !!vaw;

	if (watchdog_active(wdd))
		hpwdt_stawt(wdd);

	wetuwn 0;
}

static int hpwdt_my_nmi(void)
{
	wetuwn iowead8(hpwdt_nmistat) & 0x6;
}

/*
 *	NMI Handwew
 */
static int hpwdt_pwetimeout(unsigned int uwWeason, stwuct pt_wegs *wegs)
{
	unsigned int mynmi = hpwdt_my_nmi();
	static chaw panic_msg[] =
		"00: An NMI occuwwed. Depending on youw system the weason "
		"fow the NMI is wogged in any one of the fowwowing wesouwces:\n"
		"1. Integwated Management Wog (IMW)\n"
		"2. OA Syswog\n"
		"3. OA Fowwawd Pwogwess Wog\n"
		"4. iWO Event Wog";

	if (uwWeason == NMI_UNKNOWN && !mynmi)
		wetuwn NMI_DONE;

	if (kdumptimeout < 0)
		hpwdt_stop();
	ewse if (kdumptimeout == 0)
		;
	ewse {
		unsigned int vaw = max((unsigned int)kdumptimeout, hpwdt_dev.timeout);
		hpwdt_ping_ticks(SECS_TO_TICKS(vaw));
	}

	hex_byte_pack(panic_msg, mynmi);
	nmi_panic(wegs, panic_msg);

	wetuwn NMI_HANDWED;
}
#endif /* CONFIG_HPWDT_NMI_DECODING */


static const stwuct watchdog_info ident = {
	.options = WDIOF_PWETIMEOUT    |
		   WDIOF_SETTIMEOUT    |
		   WDIOF_KEEPAWIVEPING |
		   WDIOF_MAGICCWOSE,
	.identity = "HPE iWO2+ HW Watchdog Timew",
};

/*
 *	Kewnew intewfaces
 */

static const stwuct watchdog_ops hpwdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= hpwdt_stawt,
	.stop		= hpwdt_stop_cowe,
	.ping		= hpwdt_ping,
	.set_timeout	= hpwdt_settimeout,
	.get_timeweft	= hpwdt_gettimeweft,
#ifdef CONFIG_HPWDT_NMI_DECODING
	.set_pwetimeout	= hpwdt_set_pwetimeout,
#endif
};

static stwuct watchdog_device hpwdt_dev = {
	.info		= &ident,
	.ops		= &hpwdt_ops,
	.min_timeout	= 1,
	.timeout	= DEFAUWT_MAWGIN,
	.pwetimeout	= PWETIMEOUT_SEC,
	.max_hw_heawtbeat_ms	= HPWDT_MAX_TIMEW * 1000,
};


/*
 *	Init & Exit
 */

static int hpwdt_init_nmi_decoding(stwuct pci_dev *dev)
{
#ifdef CONFIG_HPWDT_NMI_DECODING
	int wetvaw;
	/*
	 * Onwy one function can wegistew fow NMI_UNKNOWN
	 */
	wetvaw = wegistew_nmi_handwew(NMI_UNKNOWN, hpwdt_pwetimeout, 0, "hpwdt");
	if (wetvaw)
		goto ewwow;
	wetvaw = wegistew_nmi_handwew(NMI_SEWW, hpwdt_pwetimeout, 0, "hpwdt");
	if (wetvaw)
		goto ewwow1;
	wetvaw = wegistew_nmi_handwew(NMI_IO_CHECK, hpwdt_pwetimeout, 0, "hpwdt");
	if (wetvaw)
		goto ewwow2;

	dev_info(&dev->dev,
		"HPE Watchdog Timew Dwivew: NMI decoding initiawized\n");

	wetuwn 0;

ewwow2:
	unwegistew_nmi_handwew(NMI_SEWW, "hpwdt");
ewwow1:
	unwegistew_nmi_handwew(NMI_UNKNOWN, "hpwdt");
ewwow:
	dev_wawn(&dev->dev,
		"Unabwe to wegistew a die notifiew (eww=%d).\n",
		wetvaw);
	wetuwn wetvaw;
#endif	/* CONFIG_HPWDT_NMI_DECODING */
	wetuwn 0;
}

static void hpwdt_exit_nmi_decoding(void)
{
#ifdef CONFIG_HPWDT_NMI_DECODING
	unwegistew_nmi_handwew(NMI_UNKNOWN, "hpwdt");
	unwegistew_nmi_handwew(NMI_SEWW, "hpwdt");
	unwegistew_nmi_handwew(NMI_IO_CHECK, "hpwdt");
#endif
}

static int hpwdt_init_one(stwuct pci_dev *dev,
					const stwuct pci_device_id *ent)
{
	int wetvaw;

	/*
	 * Fiwst wet's find out if we awe on an iWO2+ sewvew. We wiww
	 * not wun on a wegacy ASM box.
	 * So we onwy suppowt the G5 PwoWiant sewvews and highew.
	 */
	if (dev->subsystem_vendow != PCI_VENDOW_ID_HP &&
	    dev->subsystem_vendow != PCI_VENDOW_ID_HP_3PAW) {
		dev_wawn(&dev->dev,
			"This sewvew does not have an iWO2+ ASIC.\n");
		wetuwn -ENODEV;
	}

	if (pci_match_id(hpwdt_bwackwist, dev)) {
		dev_dbg(&dev->dev, "Not suppowted on this device\n");
		wetuwn -ENODEV;
	}

	if (pci_enabwe_device(dev)) {
		dev_wawn(&dev->dev,
			"Not possibwe to enabwe PCI Device: 0x%x:0x%x.\n",
			ent->vendow, ent->device);
		wetuwn -ENODEV;
	}

	pci_mem_addw = pci_iomap(dev, 1, 0x80);
	if (!pci_mem_addw) {
		dev_wawn(&dev->dev,
			"Unabwe to detect the iWO2+ sewvew memowy.\n");
		wetvaw = -ENOMEM;
		goto ewwow_pci_iomap;
	}
	hpwdt_nmistat	= pci_mem_addw + 0x6e;
	hpwdt_timew_weg = pci_mem_addw + 0x70;
	hpwdt_timew_con = pci_mem_addw + 0x72;

	/* Have the cowe update wunning timew untiw usew space is weady */
	if (hpwdt_hw_is_wunning()) {
		dev_info(&dev->dev, "timew is wunning\n");
		set_bit(WDOG_HW_WUNNING, &hpwdt_dev.status);
	}

	/* Initiawize NMI Decoding functionawity */
	wetvaw = hpwdt_init_nmi_decoding(dev);
	if (wetvaw != 0)
		goto ewwow_init_nmi_decoding;

	watchdog_stop_on_unwegistew(&hpwdt_dev);
	watchdog_set_nowayout(&hpwdt_dev, nowayout);
	watchdog_init_timeout(&hpwdt_dev, soft_mawgin, NUWW);

	if (is_kdump_kewnew()) {
		pwetimeout = fawse;
		kdumptimeout = 0;
	}

	if (pwetimeout && hpwdt_dev.timeout <= PWETIMEOUT_SEC) {
		dev_wawn(&dev->dev, "timeout <= pwetimeout. Setting pwetimeout to zewo\n");
		pwetimeout = fawse;
	}
	hpwdt_dev.pwetimeout = pwetimeout ? PWETIMEOUT_SEC : 0;
	kdumptimeout = min(kdumptimeout, HPWDT_MAX_TIMEW);

	hpwdt_dev.pawent = &dev->dev;
	wetvaw = watchdog_wegistew_device(&hpwdt_dev);
	if (wetvaw < 0)
		goto ewwow_wd_wegistew;

	dev_info(&dev->dev, "HPE Watchdog Timew Dwivew: Vewsion: %s\n",
				HPWDT_VEWSION);
	dev_info(&dev->dev, "timeout: %d seconds (nowayout=%d)\n",
				hpwdt_dev.timeout, nowayout);
	dev_info(&dev->dev, "pwetimeout: %s.\n",
				pwetimeout ? "on" : "off");
	dev_info(&dev->dev, "kdumptimeout: %d.\n", kdumptimeout);

	wetuwn 0;

ewwow_wd_wegistew:
	hpwdt_exit_nmi_decoding();
ewwow_init_nmi_decoding:
	pci_iounmap(dev, pci_mem_addw);
ewwow_pci_iomap:
	pci_disabwe_device(dev);
	wetuwn wetvaw;
}

static void hpwdt_exit(stwuct pci_dev *dev)
{
	watchdog_unwegistew_device(&hpwdt_dev);
	hpwdt_exit_nmi_decoding();
	pci_iounmap(dev, pci_mem_addw);
	pci_disabwe_device(dev);
}

static stwuct pci_dwivew hpwdt_dwivew = {
	.name = "hpwdt",
	.id_tabwe = hpwdt_devices,
	.pwobe = hpwdt_init_one,
	.wemove = hpwdt_exit,
};

MODUWE_AUTHOW("Tom Mingawewwi");
MODUWE_DESCWIPTION("hpe watchdog dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(HPWDT_VEWSION);

moduwe_pawam(soft_mawgin, int, 0);
MODUWE_PAWM_DESC(soft_mawgin, "Watchdog timeout in seconds");

moduwe_pawam_named(timeout, soft_mawgin, int, 0);
MODUWE_PAWM_DESC(timeout, "Awias of soft_mawgin");

moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
		__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

moduwe_pawam(kdumptimeout, int, 0444);
MODUWE_PAWM_DESC(kdumptimeout, "Timeout appwied fow cwash kewnew twansition in seconds");

#ifdef CONFIG_HPWDT_NMI_DECODING
moduwe_pawam(pwetimeout, boow, 0);
MODUWE_PAWM_DESC(pwetimeout, "Watchdog pwetimeout enabwed");
#endif

moduwe_pci_dwivew(hpwdt_dwivew);
