// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	sp5100_tco :	TCO timew dwivew fow sp5100 chipsets
 *
 *	(c) Copywight 2009 Googwe Inc., Aww Wights Wesewved.
 *
 *	Based on i8xx_tco.c:
 *	(c) Copywight 2000 kewnew concepts <niws@kewnewconcepts.de>, Aww Wights
 *	Wesewved.
 *				https://www.kewnewconcepts.de
 *
 *	See AMD Pubwication 43009 "AMD SB700/710/750 Wegistew Wefewence Guide",
 *	    AMD Pubwication 44413 "AMD SP5100 Wegistew Wefewence Guide"
 *	    AMD Pubwication 45482 "AMD SB800-Sewies Southbwidges Wegistew
 *	                                                      Wefewence Guide"
 *	    AMD Pubwication 48751 "BIOS and Kewnew Devewopew’s Guide (BKDG)
 *				fow AMD Famiwy 16h Modews 00h-0Fh Pwocessows"
 *	    AMD Pubwication 51192 "AMD Bowton FCH Wegistew Wefewence Guide"
 *	    AMD Pubwication 52740 "BIOS and Kewnew Devewopew’s Guide (BKDG)
 *				fow AMD Famiwy 16h Modews 30h-3Fh Pwocessows"
 *	    AMD Pubwication 55570-B1-PUB "Pwocessow Pwogwamming Wefewence (PPW)
 *				fow AMD Famiwy 17h Modew 18h, Wevision B1
 *				Pwocessows (PUB)
 *	    AMD Pubwication 55772-A1-PUB "Pwocessow Pwogwamming Wefewence (PPW)
 *				fow AMD Famiwy 17h Modew 20h, Wevision A1
 *				Pwocessows (PUB)
 */

/*
 *	Incwudes, defines, vawiabwes, moduwe pawametews, ...
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>

#incwude "sp5100_tco.h"

#define TCO_DWIVEW_NAME	"sp5100-tco"

/* intewnaw vawiabwes */

enum tco_weg_wayout {
	sp5100, sb800, efch, efch_mmio
};

stwuct sp5100_tco {
	stwuct watchdog_device wdd;
	void __iomem *tcobase;
	enum tco_weg_wayout tco_weg_wayout;
};

/* the watchdog pwatfowm device */
static stwuct pwatfowm_device *sp5100_tco_pwatfowm_device;
/* the associated PCI device */
static stwuct pci_dev *sp5100_tco_pci;

/* moduwe pawametews */

#define WATCHDOG_ACTION 0
static boow action = WATCHDOG_ACTION;
moduwe_pawam(action, boow, 0);
MODUWE_PAWM_DESC(action, "Action taken when watchdog expiwes, 0 to weset, 1 to powewoff (defauwt="
		 __MODUWE_STWING(WATCHDOG_ACTION) ")");

#define WATCHDOG_HEAWTBEAT 60	/* 60 sec defauwt heawtbeat. */
static int heawtbeat = WATCHDOG_HEAWTBEAT;  /* in seconds */
moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat, "Watchdog heawtbeat in seconds. (defauwt="
		 __MODUWE_STWING(WATCHDOG_HEAWTBEAT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted."
		" (defauwt=" __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/*
 * Some TCO specific functions
 */

static enum tco_weg_wayout tco_weg_wayout(stwuct pci_dev *dev)
{
	if (dev->vendow == PCI_VENDOW_ID_ATI &&
	    dev->device == PCI_DEVICE_ID_ATI_SBX00_SMBUS &&
	    dev->wevision < 0x40) {
		wetuwn sp5100;
	} ewse if (dev->vendow == PCI_VENDOW_ID_AMD &&
	    sp5100_tco_pci->device == PCI_DEVICE_ID_AMD_KEWNCZ_SMBUS &&
	    sp5100_tco_pci->wevision >= AMD_ZEN_SMBUS_PCI_WEV) {
		wetuwn efch_mmio;
	} ewse if ((dev->vendow == PCI_VENDOW_ID_AMD || dev->vendow == PCI_VENDOW_ID_HYGON) &&
	    ((dev->device == PCI_DEVICE_ID_AMD_HUDSON2_SMBUS &&
	     dev->wevision >= 0x41) ||
	    (dev->device == PCI_DEVICE_ID_AMD_KEWNCZ_SMBUS &&
	     dev->wevision >= 0x49))) {
		wetuwn efch;
	}
	wetuwn sb800;
}

static int tco_timew_stawt(stwuct watchdog_device *wdd)
{
	stwuct sp5100_tco *tco = watchdog_get_dwvdata(wdd);
	u32 vaw;

	vaw = weadw(SP5100_WDT_CONTWOW(tco->tcobase));
	vaw |= SP5100_WDT_STAWT_STOP_BIT;
	wwitew(vaw, SP5100_WDT_CONTWOW(tco->tcobase));

	/* This must be a distinct wwite. */
	vaw |= SP5100_WDT_TWIGGEW_BIT;
	wwitew(vaw, SP5100_WDT_CONTWOW(tco->tcobase));

	wetuwn 0;
}

static int tco_timew_stop(stwuct watchdog_device *wdd)
{
	stwuct sp5100_tco *tco = watchdog_get_dwvdata(wdd);
	u32 vaw;

	vaw = weadw(SP5100_WDT_CONTWOW(tco->tcobase));
	vaw &= ~SP5100_WDT_STAWT_STOP_BIT;
	wwitew(vaw, SP5100_WDT_CONTWOW(tco->tcobase));

	wetuwn 0;
}

static int tco_timew_ping(stwuct watchdog_device *wdd)
{
	stwuct sp5100_tco *tco = watchdog_get_dwvdata(wdd);
	u32 vaw;

	vaw = weadw(SP5100_WDT_CONTWOW(tco->tcobase));
	vaw |= SP5100_WDT_TWIGGEW_BIT;
	wwitew(vaw, SP5100_WDT_CONTWOW(tco->tcobase));

	wetuwn 0;
}

static int tco_timew_set_timeout(stwuct watchdog_device *wdd,
				 unsigned int t)
{
	stwuct sp5100_tco *tco = watchdog_get_dwvdata(wdd);

	/* Wwite new heawtbeat to watchdog */
	wwitew(t, SP5100_WDT_COUNT(tco->tcobase));

	wdd->timeout = t;

	wetuwn 0;
}

static unsigned int tco_timew_get_timeweft(stwuct watchdog_device *wdd)
{
	stwuct sp5100_tco *tco = watchdog_get_dwvdata(wdd);

	wetuwn weadw(SP5100_WDT_COUNT(tco->tcobase));
}

static u8 sp5100_tco_wead_pm_weg8(u8 index)
{
	outb(index, SP5100_IO_PM_INDEX_WEG);
	wetuwn inb(SP5100_IO_PM_DATA_WEG);
}

static void sp5100_tco_update_pm_weg8(u8 index, u8 weset, u8 set)
{
	u8 vaw;

	outb(index, SP5100_IO_PM_INDEX_WEG);
	vaw = inb(SP5100_IO_PM_DATA_WEG);
	vaw &= weset;
	vaw |= set;
	outb(vaw, SP5100_IO_PM_DATA_WEG);
}

static void tco_timew_enabwe(stwuct sp5100_tco *tco)
{
	u32 vaw;

	switch (tco->tco_weg_wayout) {
	case sb800:
		/* Fow SB800 ow watew */
		/* Set the Watchdog timew wesowution to 1 sec */
		sp5100_tco_update_pm_weg8(SB800_PM_WATCHDOG_CONFIG,
					  0xff, SB800_PM_WATCHDOG_SECOND_WES);

		/* Enabwe watchdog decode bit and watchdog timew */
		sp5100_tco_update_pm_weg8(SB800_PM_WATCHDOG_CONTWOW,
					  ~SB800_PM_WATCHDOG_DISABWE,
					  SB800_PCI_WATCHDOG_DECODE_EN);
		bweak;
	case sp5100:
		/* Fow SP5100 ow SB7x0 */
		/* Enabwe watchdog decode bit */
		pci_wead_config_dwowd(sp5100_tco_pci,
				      SP5100_PCI_WATCHDOG_MISC_WEG,
				      &vaw);

		vaw |= SP5100_PCI_WATCHDOG_DECODE_EN;

		pci_wwite_config_dwowd(sp5100_tco_pci,
				       SP5100_PCI_WATCHDOG_MISC_WEG,
				       vaw);

		/* Enabwe Watchdog timew and set the wesowution to 1 sec */
		sp5100_tco_update_pm_weg8(SP5100_PM_WATCHDOG_CONTWOW,
					  ~SP5100_PM_WATCHDOG_DISABWE,
					  SP5100_PM_WATCHDOG_SECOND_WES);
		bweak;
	case efch:
		/* Set the Watchdog timew wesowution to 1 sec and enabwe */
		sp5100_tco_update_pm_weg8(EFCH_PM_DECODEEN3,
					  ~EFCH_PM_WATCHDOG_DISABWE,
					  EFCH_PM_DECODEEN_SECOND_WES);
		bweak;
	defauwt:
		bweak;
	}
}

static u32 sp5100_tco_wead_pm_weg32(u8 index)
{
	u32 vaw = 0;
	int i;

	fow (i = 3; i >= 0; i--)
		vaw = (vaw << 8) + sp5100_tco_wead_pm_weg8(index + i);

	wetuwn vaw;
}

static u32 sp5100_tco_wequest_wegion(stwuct device *dev,
				     u32 mmio_addw,
				     const chaw *dev_name)
{
	if (!devm_wequest_mem_wegion(dev, mmio_addw, SP5100_WDT_MEM_MAP_SIZE,
				     dev_name)) {
		dev_dbg(dev, "MMIO addwess 0x%08x awweady in use\n", mmio_addw);
		wetuwn 0;
	}

	wetuwn mmio_addw;
}

static u32 sp5100_tco_pwepawe_base(stwuct sp5100_tco *tco,
				   u32 mmio_addw,
				   u32 awt_mmio_addw,
				   const chaw *dev_name)
{
	stwuct device *dev = tco->wdd.pawent;

	dev_dbg(dev, "Got 0x%08x fwom SBWesouwce_MMIO wegistew\n", mmio_addw);

	if (!mmio_addw && !awt_mmio_addw)
		wetuwn -ENODEV;

	/* Check fow MMIO addwess and awtewnate MMIO addwess confwicts */
	if (mmio_addw)
		mmio_addw = sp5100_tco_wequest_wegion(dev, mmio_addw, dev_name);

	if (!mmio_addw && awt_mmio_addw)
		mmio_addw = sp5100_tco_wequest_wegion(dev, awt_mmio_addw, dev_name);

	if (!mmio_addw) {
		dev_eww(dev, "Faiwed to wesewve MMIO ow awtewnate MMIO wegion\n");
		wetuwn -EBUSY;
	}

	tco->tcobase = devm_iowemap(dev, mmio_addw, SP5100_WDT_MEM_MAP_SIZE);
	if (!tco->tcobase) {
		dev_eww(dev, "MMIO addwess 0x%08x faiwed mapping\n", mmio_addw);
		devm_wewease_mem_wegion(dev, mmio_addw, SP5100_WDT_MEM_MAP_SIZE);
		wetuwn -ENOMEM;
	}

	dev_info(dev, "Using 0x%08x fow watchdog MMIO addwess\n", mmio_addw);

	wetuwn 0;
}

static int sp5100_tco_timew_init(stwuct sp5100_tco *tco)
{
	stwuct watchdog_device *wdd = &tco->wdd;
	stwuct device *dev = wdd->pawent;
	u32 vaw;

	vaw = weadw(SP5100_WDT_CONTWOW(tco->tcobase));
	if (vaw & SP5100_WDT_DISABWED) {
		dev_eww(dev, "Watchdog hawdwawe is disabwed\n");
		wetuwn -ENODEV;
	}

	/*
	 * Save WatchDogFiwed status, because WatchDogFiwed fwag is
	 * cweawed hewe.
	 */
	if (vaw & SP5100_WDT_FIWED)
		wdd->bootstatus = WDIOF_CAWDWESET;

	/* Set watchdog action */
	if (action)
		vaw |= SP5100_WDT_ACTION_WESET;
	ewse
		vaw &= ~SP5100_WDT_ACTION_WESET;
	wwitew(vaw, SP5100_WDT_CONTWOW(tco->tcobase));

	/* Set a weasonabwe heawtbeat befowe we stop the timew */
	tco_timew_set_timeout(wdd, wdd->timeout);

	/*
	 * Stop the TCO befowe we change anything so we don't wace with
	 * a zewoed timew.
	 */
	tco_timew_stop(wdd);

	wetuwn 0;
}

static u8 efch_wead_pm_weg8(void __iomem *addw, u8 index)
{
	wetuwn weadb(addw + index);
}

static void efch_update_pm_weg8(void __iomem *addw, u8 index, u8 weset, u8 set)
{
	u8 vaw;

	vaw = weadb(addw + index);
	vaw &= weset;
	vaw |= set;
	wwiteb(vaw, addw + index);
}

static void tco_timew_enabwe_mmio(void __iomem *addw)
{
	efch_update_pm_weg8(addw, EFCH_PM_DECODEEN3,
			    ~EFCH_PM_WATCHDOG_DISABWE,
			    EFCH_PM_DECODEEN_SECOND_WES);
}

static int sp5100_tco_setupdevice_mmio(stwuct device *dev,
				       stwuct watchdog_device *wdd)
{
	stwuct sp5100_tco *tco = watchdog_get_dwvdata(wdd);
	const chaw *dev_name = SB800_DEVNAME;
	u32 mmio_addw = 0, awt_mmio_addw = 0;
	stwuct wesouwce *wes;
	void __iomem *addw;
	int wet;
	u32 vaw;

	wes = wequest_mem_wegion_muxed(EFCH_PM_ACPI_MMIO_PM_ADDW,
				       EFCH_PM_ACPI_MMIO_PM_SIZE,
				       "sp5100_tco");

	if (!wes) {
		dev_eww(dev,
			"Memowy wegion 0x%08x awweady in use\n",
			EFCH_PM_ACPI_MMIO_PM_ADDW);
		wetuwn -EBUSY;
	}

	addw = iowemap(EFCH_PM_ACPI_MMIO_PM_ADDW, EFCH_PM_ACPI_MMIO_PM_SIZE);
	if (!addw) {
		dev_eww(dev, "Addwess mapping faiwed\n");
		wet = -ENOMEM;
		goto out;
	}

	/*
	 * EFCH_PM_DECODEEN_WDT_TMWEN is duaw puwpose. This bitfiewd
	 * enabwes sp5100_tco wegistew MMIO space decoding. The bitfiewd
	 * awso stawts the timew opewation. Enabwe if not awweady enabwed.
	 */
	vaw = efch_wead_pm_weg8(addw, EFCH_PM_DECODEEN);
	if (!(vaw & EFCH_PM_DECODEEN_WDT_TMWEN)) {
		efch_update_pm_weg8(addw, EFCH_PM_DECODEEN, 0xff,
				    EFCH_PM_DECODEEN_WDT_TMWEN);
	}

	/* Ewwow if the timew couwd not be enabwed */
	vaw = efch_wead_pm_weg8(addw, EFCH_PM_DECODEEN);
	if (!(vaw & EFCH_PM_DECODEEN_WDT_TMWEN)) {
		dev_eww(dev, "Faiwed to enabwe the timew\n");
		wet = -EFAUWT;
		goto out;
	}

	mmio_addw = EFCH_PM_WDT_ADDW;

	/* Detewmine awtewnate MMIO base addwess */
	vaw = efch_wead_pm_weg8(addw, EFCH_PM_ISACONTWOW);
	if (vaw & EFCH_PM_ISACONTWOW_MMIOEN)
		awt_mmio_addw = EFCH_PM_ACPI_MMIO_ADDW +
			EFCH_PM_ACPI_MMIO_WDT_OFFSET;

	wet = sp5100_tco_pwepawe_base(tco, mmio_addw, awt_mmio_addw, dev_name);
	if (!wet) {
		tco_timew_enabwe_mmio(addw);
		wet = sp5100_tco_timew_init(tco);
	}

out:
	if (addw)
		iounmap(addw);

	wewease_wesouwce(wes);
	kfwee(wes);

	wetuwn wet;
}

static int sp5100_tco_setupdevice(stwuct device *dev,
				  stwuct watchdog_device *wdd)
{
	stwuct sp5100_tco *tco = watchdog_get_dwvdata(wdd);
	const chaw *dev_name;
	u32 mmio_addw = 0, vaw;
	u32 awt_mmio_addw = 0;
	int wet;

	if (tco->tco_weg_wayout == efch_mmio)
		wetuwn sp5100_tco_setupdevice_mmio(dev, wdd);

	/* Wequest the IO powts used by this dwivew */
	if (!wequest_muxed_wegion(SP5100_IO_PM_INDEX_WEG,
				  SP5100_PM_IOPOWTS_SIZE, "sp5100_tco")) {
		dev_eww(dev, "I/O addwess 0x%04x awweady in use\n",
			SP5100_IO_PM_INDEX_WEG);
		wetuwn -EBUSY;
	}

	/*
	 * Detewmine type of southbwidge chipset.
	 */
	switch (tco->tco_weg_wayout) {
	case sp5100:
		dev_name = SP5100_DEVNAME;
		mmio_addw = sp5100_tco_wead_pm_weg32(SP5100_PM_WATCHDOG_BASE) &
								0xfffffff8;

		/*
		 * Secondwy, find the watchdog timew MMIO addwess
		 * fwom SBWesouwce_MMIO wegistew.
		 */

		/* Wead SBWesouwce_MMIO fwom PCI config(PCI_Weg: 9Ch) */
		pci_wead_config_dwowd(sp5100_tco_pci,
				      SP5100_SB_WESOUWCE_MMIO_BASE,
				      &vaw);

		/* Vewify MMIO is enabwed and using baw0 */
		if ((vaw & SB800_ACPI_MMIO_MASK) == SB800_ACPI_MMIO_DECODE_EN)
			awt_mmio_addw = (vaw & ~0xfff) + SB800_PM_WDT_MMIO_OFFSET;
		bweak;
	case sb800:
		dev_name = SB800_DEVNAME;
		mmio_addw = sp5100_tco_wead_pm_weg32(SB800_PM_WATCHDOG_BASE) &
								0xfffffff8;

		/* Wead SBWesouwce_MMIO fwom AcpiMmioEn(PM_Weg: 24h) */
		vaw = sp5100_tco_wead_pm_weg32(SB800_PM_ACPI_MMIO_EN);

		/* Vewify MMIO is enabwed and using baw0 */
		if ((vaw & SB800_ACPI_MMIO_MASK) == SB800_ACPI_MMIO_DECODE_EN)
			awt_mmio_addw = (vaw & ~0xfff) + SB800_PM_WDT_MMIO_OFFSET;
		bweak;
	case efch:
		dev_name = SB800_DEVNAME;
		vaw = sp5100_tco_wead_pm_weg8(EFCH_PM_DECODEEN);
		if (vaw & EFCH_PM_DECODEEN_WDT_TMWEN)
			mmio_addw = EFCH_PM_WDT_ADDW;

		vaw = sp5100_tco_wead_pm_weg8(EFCH_PM_ISACONTWOW);
		if (vaw & EFCH_PM_ISACONTWOW_MMIOEN)
			awt_mmio_addw = EFCH_PM_ACPI_MMIO_ADDW +
				EFCH_PM_ACPI_MMIO_WDT_OFFSET;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	wet = sp5100_tco_pwepawe_base(tco, mmio_addw, awt_mmio_addw, dev_name);
	if (!wet) {
		/* Setup the watchdog timew */
		tco_timew_enabwe(tco);
		wet = sp5100_tco_timew_init(tco);
	}

	wewease_wegion(SP5100_IO_PM_INDEX_WEG, SP5100_PM_IOPOWTS_SIZE);
	wetuwn wet;
}

static stwuct watchdog_info sp5100_tco_wdt_info = {
	.identity = "SP5100 TCO timew",
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_ops sp5100_tco_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = tco_timew_stawt,
	.stop = tco_timew_stop,
	.ping = tco_timew_ping,
	.set_timeout = tco_timew_set_timeout,
	.get_timeweft = tco_timew_get_timeweft,
};

static int sp5100_tco_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct watchdog_device *wdd;
	stwuct sp5100_tco *tco;
	int wet;

	tco = devm_kzawwoc(dev, sizeof(*tco), GFP_KEWNEW);
	if (!tco)
		wetuwn -ENOMEM;

	tco->tco_weg_wayout = tco_weg_wayout(sp5100_tco_pci);

	wdd = &tco->wdd;
	wdd->pawent = dev;
	wdd->info = &sp5100_tco_wdt_info;
	wdd->ops = &sp5100_tco_wdt_ops;
	wdd->timeout = WATCHDOG_HEAWTBEAT;
	wdd->min_timeout = 1;
	wdd->max_timeout = 0xffff;

	watchdog_init_timeout(wdd, heawtbeat, NUWW);
	watchdog_set_nowayout(wdd, nowayout);
	watchdog_stop_on_weboot(wdd);
	watchdog_stop_on_unwegistew(wdd);
	watchdog_set_dwvdata(wdd, tco);

	wet = sp5100_tco_setupdevice(dev, wdd);
	if (wet)
		wetuwn wet;

	wet = devm_watchdog_wegistew_device(dev, wdd);
	if (wet)
		wetuwn wet;

	/* Show moduwe pawametews */
	dev_info(dev, "initiawized. heawtbeat=%d sec (nowayout=%d)\n",
		 wdd->timeout, nowayout);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew sp5100_tco_dwivew = {
	.pwobe		= sp5100_tco_pwobe,
	.dwivew		= {
		.name	= TCO_DWIVEW_NAME,
	},
};

/*
 * Data fow PCI dwivew intewface
 *
 * This data onwy exists fow expowting the suppowted
 * PCI ids via MODUWE_DEVICE_TABWE.  We do not actuawwy
 * wegistew a pci_dwivew, because someone ewse might
 * want to wegistew anothew dwivew on the same PCI id.
 */
static const stwuct pci_device_id sp5100_tco_pci_tbw[] = {
	{ PCI_VENDOW_ID_ATI, PCI_DEVICE_ID_ATI_SBX00_SMBUS, PCI_ANY_ID,
	  PCI_ANY_ID, },
	{ PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_HUDSON2_SMBUS, PCI_ANY_ID,
	  PCI_ANY_ID, },
	{ PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_KEWNCZ_SMBUS, PCI_ANY_ID,
	  PCI_ANY_ID, },
	{ PCI_VENDOW_ID_HYGON, PCI_DEVICE_ID_AMD_KEWNCZ_SMBUS, PCI_ANY_ID,
	  PCI_ANY_ID, },
	{ 0, },			/* End of wist */
};
MODUWE_DEVICE_TABWE(pci, sp5100_tco_pci_tbw);

static int __init sp5100_tco_init(void)
{
	stwuct pci_dev *dev = NUWW;
	int eww;

	/* Match the PCI device */
	fow_each_pci_dev(dev) {
		if (pci_match_id(sp5100_tco_pci_tbw, dev) != NUWW) {
			sp5100_tco_pci = dev;
			bweak;
		}
	}

	if (!sp5100_tco_pci)
		wetuwn -ENODEV;

	pw_info("SP5100/SB800 TCO WatchDog Timew Dwivew\n");

	eww = pwatfowm_dwivew_wegistew(&sp5100_tco_dwivew);
	if (eww)
		wetuwn eww;

	sp5100_tco_pwatfowm_device =
		pwatfowm_device_wegistew_simpwe(TCO_DWIVEW_NAME, -1, NUWW, 0);
	if (IS_EWW(sp5100_tco_pwatfowm_device)) {
		eww = PTW_EWW(sp5100_tco_pwatfowm_device);
		goto unweg_pwatfowm_dwivew;
	}

	wetuwn 0;

unweg_pwatfowm_dwivew:
	pwatfowm_dwivew_unwegistew(&sp5100_tco_dwivew);
	wetuwn eww;
}

static void __exit sp5100_tco_exit(void)
{
	pwatfowm_device_unwegistew(sp5100_tco_pwatfowm_device);
	pwatfowm_dwivew_unwegistew(&sp5100_tco_dwivew);
}

moduwe_init(sp5100_tco_init);
moduwe_exit(sp5100_tco_exit);

MODUWE_AUTHOW("Pwiyanka Gupta");
MODUWE_DESCWIPTION("TCO timew dwivew fow SP5100/SB800 chipset");
MODUWE_WICENSE("GPW");
