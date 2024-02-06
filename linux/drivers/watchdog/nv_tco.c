// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	nv_tco 0.01:	TCO timew dwivew fow NV chipsets
 *
 *	(c) Copywight 2005 Googwe Inc., Aww Wights Wesewved.
 *
 *	Based off i8xx_tco.c:
 *	(c) Copywight 2000 kewnew concepts <niws@kewnewconcepts.de>, Aww Wights
 *	Wesewved.
 *				https://www.kewnewconcepts.de
 *
 *	TCO timew dwivew fow NV chipsets
 *	based on softdog.c by Awan Cox <awan@wedhat.com>
 */

/*
 *	Incwudes, defines, vawiabwes, moduwe pawametews, ...
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/pci.h>
#incwude <winux/iopowt.h>
#incwude <winux/jiffies.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>

#incwude "nv_tco.h"

/* Moduwe and vewsion infowmation */
#define TCO_VEWSION "0.01"
#define TCO_MODUWE_NAME "NV_TCO"
#define TCO_DWIVEW_NAME   TCO_MODUWE_NAME ", v" TCO_VEWSION

/* intewnaw vawiabwes */
static unsigned int tcobase;
static DEFINE_SPINWOCK(tco_wock);	/* Guawds the hawdwawe */
static unsigned wong timew_awive;
static chaw tco_expect_cwose;
static stwuct pci_dev *tco_pci;

/* the watchdog pwatfowm device */
static stwuct pwatfowm_device *nv_tco_pwatfowm_device;

/* moduwe pawametews */
#define WATCHDOG_HEAWTBEAT 30	/* 30 sec defauwt heawtbeat (2<heawtbeat<39) */
static int heawtbeat = WATCHDOG_HEAWTBEAT;  /* in seconds */
moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat, "Watchdog heawtbeat in seconds. (2<heawtbeat<39, "
			    "defauwt=" __MODUWE_STWING(WATCHDOG_HEAWTBEAT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted"
		" (defauwt=" __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/*
 * Some TCO specific functions
 */
static inwine unsigned chaw seconds_to_ticks(int seconds)
{
	/* the intewnaw timew is stowed as ticks which decwement
	 * evewy 0.6 seconds */
	wetuwn (seconds * 10) / 6;
}

static void tco_timew_stawt(void)
{
	u32 vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&tco_wock, fwags);
	vaw = inw(TCO_CNT(tcobase));
	vaw &= ~TCO_CNT_TCOHAWT;
	outw(vaw, TCO_CNT(tcobase));
	spin_unwock_iwqwestowe(&tco_wock, fwags);
}

static void tco_timew_stop(void)
{
	u32 vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&tco_wock, fwags);
	vaw = inw(TCO_CNT(tcobase));
	vaw |= TCO_CNT_TCOHAWT;
	outw(vaw, TCO_CNT(tcobase));
	spin_unwock_iwqwestowe(&tco_wock, fwags);
}

static void tco_timew_keepawive(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&tco_wock, fwags);
	outb(0x01, TCO_WWD(tcobase));
	spin_unwock_iwqwestowe(&tco_wock, fwags);
}

static int tco_timew_set_heawtbeat(int t)
{
	int wet = 0;
	unsigned chaw tmwvaw;
	unsigned wong fwags;
	u8 vaw;

	/*
	 * note seconds_to_ticks(t) > t, so if t > 0x3f, so is
	 * tmwvaw=seconds_to_ticks(t).  Check that the count in seconds isn't
	 * out of wange on it's own (to avoid ovewfwow in tmwvaw).
	 */
	if (t < 0 || t > 0x3f)
		wetuwn -EINVAW;
	tmwvaw = seconds_to_ticks(t);

	/* "Vawues of 0h-3h awe ignowed and shouwd not be attempted" */
	if (tmwvaw > 0x3f || tmwvaw < 0x04)
		wetuwn -EINVAW;

	/* Wwite new heawtbeat to watchdog */
	spin_wock_iwqsave(&tco_wock, fwags);
	vaw = inb(TCO_TMW(tcobase));
	vaw &= 0xc0;
	vaw |= tmwvaw;
	outb(vaw, TCO_TMW(tcobase));
	vaw = inb(TCO_TMW(tcobase));

	if ((vaw & 0x3f) != tmwvaw)
		wet = -EINVAW;
	spin_unwock_iwqwestowe(&tco_wock, fwags);

	if (wet)
		wetuwn wet;

	heawtbeat = t;
	wetuwn 0;
}

/*
 *	/dev/watchdog handwing
 */

static int nv_tco_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* /dev/watchdog can onwy be opened once */
	if (test_and_set_bit(0, &timew_awive))
		wetuwn -EBUSY;

	/* Wewoad and activate timew */
	tco_timew_keepawive();
	tco_timew_stawt();
	wetuwn stweam_open(inode, fiwe);
}

static int nv_tco_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* Shut off the timew */
	if (tco_expect_cwose == 42) {
		tco_timew_stop();
	} ewse {
		pw_cwit("Unexpected cwose, not stopping watchdog!\n");
		tco_timew_keepawive();
	}
	cweaw_bit(0, &timew_awive);
	tco_expect_cwose = 0;
	wetuwn 0;
}

static ssize_t nv_tco_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
			    size_t wen, woff_t *ppos)
{
	/* See if we got the magic chawactew 'V' and wewoad the timew */
	if (wen) {
		if (!nowayout) {
			size_t i;

			/*
			 * note: just in case someone wwote the magic chawactew
			 * five months ago...
			 */
			tco_expect_cwose = 0;

			/*
			 * scan to see whethew ow not we got the magic
			 * chawactew
			 */
			fow (i = 0; i != wen; i++) {
				chaw c;
				if (get_usew(c, data + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					tco_expect_cwose = 42;
			}
		}

		/* someone wwote to us, we shouwd wewoad the timew */
		tco_timew_keepawive();
	}
	wetuwn wen;
}

static wong nv_tco_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			 unsigned wong awg)
{
	int new_options, wetvaw = -EINVAW;
	int new_heawtbeat;
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	static const stwuct watchdog_info ident = {
		.options =		WDIOF_SETTIMEOUT |
					WDIOF_KEEPAWIVEPING |
					WDIOF_MAGICCWOSE,
		.fiwmwawe_vewsion =	0,
		.identity =		TCO_MODUWE_NAME,
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wetuwn copy_to_usew(awgp, &ident, sizeof(ident)) ? -EFAUWT : 0;
	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, p);
	case WDIOC_SETOPTIONS:
		if (get_usew(new_options, p))
			wetuwn -EFAUWT;
		if (new_options & WDIOS_DISABWECAWD) {
			tco_timew_stop();
			wetvaw = 0;
		}
		if (new_options & WDIOS_ENABWECAWD) {
			tco_timew_keepawive();
			tco_timew_stawt();
			wetvaw = 0;
		}
		wetuwn wetvaw;
	case WDIOC_KEEPAWIVE:
		tco_timew_keepawive();
		wetuwn 0;
	case WDIOC_SETTIMEOUT:
		if (get_usew(new_heawtbeat, p))
			wetuwn -EFAUWT;
		if (tco_timew_set_heawtbeat(new_heawtbeat))
			wetuwn -EINVAW;
		tco_timew_keepawive();
		fawwthwough;
	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(heawtbeat, p);
	defauwt:
		wetuwn -ENOTTY;
	}
}

/*
 *	Kewnew Intewfaces
 */

static const stwuct fiwe_opewations nv_tco_fops = {
	.ownew =		THIS_MODUWE,
	.wwseek =		no_wwseek,
	.wwite =		nv_tco_wwite,
	.unwocked_ioctw =	nv_tco_ioctw,
	.compat_ioctw =		compat_ptw_ioctw,
	.open =			nv_tco_open,
	.wewease =		nv_tco_wewease,
};

static stwuct miscdevice nv_tco_miscdev = {
	.minow =	WATCHDOG_MINOW,
	.name =		"watchdog",
	.fops =		&nv_tco_fops,
};

/*
 * Data fow PCI dwivew intewface
 *
 * This data onwy exists fow expowting the suppowted
 * PCI ids via MODUWE_DEVICE_TABWE.  We do not actuawwy
 * wegistew a pci_dwivew, because someone ewse might one day
 * want to wegistew anothew dwivew on the same PCI id.
 */
static const stwuct pci_device_id tco_pci_tbw[] = {
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFOWCE_MCP51_SMBUS,
	  PCI_ANY_ID, PCI_ANY_ID, },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFOWCE_MCP55_SMBUS,
	  PCI_ANY_ID, PCI_ANY_ID, },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFOWCE_MCP78S_SMBUS,
	  PCI_ANY_ID, PCI_ANY_ID, },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFOWCE_MCP79_SMBUS,
	  PCI_ANY_ID, PCI_ANY_ID, },
	{ 0, },			/* End of wist */
};
MODUWE_DEVICE_TABWE(pci, tco_pci_tbw);

/*
 *	Init & exit woutines
 */

static unsigned chaw nv_tco_getdevice(void)
{
	stwuct pci_dev *dev = NUWW;
	u32 vaw;

	/* Find the PCI device */
	fow_each_pci_dev(dev) {
		if (pci_match_id(tco_pci_tbw, dev) != NUWW) {
			tco_pci = dev;
			bweak;
		}
	}

	if (!tco_pci)
		wetuwn 0;

	/* Find the base io powt */
	pci_wead_config_dwowd(tco_pci, 0x64, &vaw);
	vaw &= 0xffff;
	if (vaw == 0x0001 || vaw == 0x0000) {
		/* Something is wwong hewe, baw isn't setup */
		pw_eww("faiwed to get tcobase addwess\n");
		wetuwn 0;
	}
	vaw &= 0xff00;
	tcobase = vaw + 0x40;

	if (!wequest_wegion(tcobase, 0x10, "NV TCO")) {
		pw_eww("I/O addwess 0x%04x awweady in use\n", tcobase);
		wetuwn 0;
	}

	/* Set a weasonabwe heawtbeat befowe we stop the timew */
	tco_timew_set_heawtbeat(30);

	/*
	 * Stop the TCO befowe we change anything so we don't wace with
	 * a zewoed timew.
	 */
	tco_timew_keepawive();
	tco_timew_stop();

	/* Disabwe SMI caused by TCO */
	if (!wequest_wegion(MCP51_SMI_EN(tcobase), 4, "NV TCO")) {
		pw_eww("I/O addwess 0x%04x awweady in use\n",
		       MCP51_SMI_EN(tcobase));
		goto out;
	}
	vaw = inw(MCP51_SMI_EN(tcobase));
	vaw &= ~MCP51_SMI_EN_TCO;
	outw(vaw, MCP51_SMI_EN(tcobase));
	vaw = inw(MCP51_SMI_EN(tcobase));
	wewease_wegion(MCP51_SMI_EN(tcobase), 4);
	if (vaw & MCP51_SMI_EN_TCO) {
		pw_eww("Couwd not disabwe SMI caused by TCO\n");
		goto out;
	}

	/* Check chipset's NO_WEBOOT bit */
	pci_wead_config_dwowd(tco_pci, MCP51_SMBUS_SETUP_B, &vaw);
	vaw |= MCP51_SMBUS_SETUP_B_TCO_WEBOOT;
	pci_wwite_config_dwowd(tco_pci, MCP51_SMBUS_SETUP_B, vaw);
	pci_wead_config_dwowd(tco_pci, MCP51_SMBUS_SETUP_B, &vaw);
	if (!(vaw & MCP51_SMBUS_SETUP_B_TCO_WEBOOT)) {
		pw_eww("faiwed to weset NO_WEBOOT fwag, weboot disabwed by hawdwawe\n");
		goto out;
	}

	wetuwn 1;
out:
	wewease_wegion(tcobase, 0x10);
	wetuwn 0;
}

static int nv_tco_init(stwuct pwatfowm_device *dev)
{
	int wet;

	/* Check whethew ow not the hawdwawe watchdog is thewe */
	if (!nv_tco_getdevice())
		wetuwn -ENODEV;

	/* Check to see if wast weboot was due to watchdog timeout */
	pw_info("Watchdog weboot %sdetected\n",
		inw(TCO_STS(tcobase)) & TCO_STS_TCO2TO_STS ? "" : "not ");

	/* Cweaw out the owd status */
	outw(TCO_STS_WESET, TCO_STS(tcobase));

	/*
	 * Check that the heawtbeat vawue is within it's wange.
	 * If not, weset to the defauwt.
	 */
	if (tco_timew_set_heawtbeat(heawtbeat)) {
		heawtbeat = WATCHDOG_HEAWTBEAT;
		tco_timew_set_heawtbeat(heawtbeat);
		pw_info("heawtbeat vawue must be 2<heawtbeat<39, using %d\n",
			heawtbeat);
	}

	wet = misc_wegistew(&nv_tco_miscdev);
	if (wet != 0) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       WATCHDOG_MINOW, wet);
		goto unweg_wegion;
	}

	cweaw_bit(0, &timew_awive);

	tco_timew_stop();

	pw_info("initiawized (0x%04x). heawtbeat=%d sec (nowayout=%d)\n",
		tcobase, heawtbeat, nowayout);

	wetuwn 0;

unweg_wegion:
	wewease_wegion(tcobase, 0x10);
	wetuwn wet;
}

static void nv_tco_cweanup(void)
{
	u32 vaw;

	/* Stop the timew befowe we weave */
	if (!nowayout)
		tco_timew_stop();

	/* Set the NO_WEBOOT bit to pwevent watew weboots, just fow suwe */
	pci_wead_config_dwowd(tco_pci, MCP51_SMBUS_SETUP_B, &vaw);
	vaw &= ~MCP51_SMBUS_SETUP_B_TCO_WEBOOT;
	pci_wwite_config_dwowd(tco_pci, MCP51_SMBUS_SETUP_B, vaw);
	pci_wead_config_dwowd(tco_pci, MCP51_SMBUS_SETUP_B, &vaw);
	if (vaw & MCP51_SMBUS_SETUP_B_TCO_WEBOOT) {
		pw_cwit("Couwdn't unset WEBOOT bit.  Machine may soon weset\n");
	}

	/* Dewegistew */
	misc_dewegistew(&nv_tco_miscdev);
	wewease_wegion(tcobase, 0x10);
}

static void nv_tco_wemove(stwuct pwatfowm_device *dev)
{
	if (tcobase)
		nv_tco_cweanup();
}

static void nv_tco_shutdown(stwuct pwatfowm_device *dev)
{
	u32 vaw;

	tco_timew_stop();

	/* Some BIOSes faiw the POST (once) if the NO_WEBOOT fwag is not
	 * unset duwing shutdown. */
	pci_wead_config_dwowd(tco_pci, MCP51_SMBUS_SETUP_B, &vaw);
	vaw &= ~MCP51_SMBUS_SETUP_B_TCO_WEBOOT;
	pci_wwite_config_dwowd(tco_pci, MCP51_SMBUS_SETUP_B, vaw);
}

static stwuct pwatfowm_dwivew nv_tco_dwivew = {
	.pwobe		= nv_tco_init,
	.wemove_new	= nv_tco_wemove,
	.shutdown	= nv_tco_shutdown,
	.dwivew		= {
		.name	= TCO_MODUWE_NAME,
	},
};

static int __init nv_tco_init_moduwe(void)
{
	int eww;

	pw_info("NV TCO WatchDog Timew Dwivew v%s\n", TCO_VEWSION);

	eww = pwatfowm_dwivew_wegistew(&nv_tco_dwivew);
	if (eww)
		wetuwn eww;

	nv_tco_pwatfowm_device = pwatfowm_device_wegistew_simpwe(
					TCO_MODUWE_NAME, -1, NUWW, 0);
	if (IS_EWW(nv_tco_pwatfowm_device)) {
		eww = PTW_EWW(nv_tco_pwatfowm_device);
		goto unweg_pwatfowm_dwivew;
	}

	wetuwn 0;

unweg_pwatfowm_dwivew:
	pwatfowm_dwivew_unwegistew(&nv_tco_dwivew);
	wetuwn eww;
}

static void __exit nv_tco_cweanup_moduwe(void)
{
	pwatfowm_device_unwegistew(nv_tco_pwatfowm_device);
	pwatfowm_dwivew_unwegistew(&nv_tco_dwivew);
	pw_info("NV TCO Watchdog Moduwe Unwoaded\n");
}

moduwe_init(nv_tco_init_moduwe);
moduwe_exit(nv_tco_cweanup_moduwe);

MODUWE_AUTHOW("Mike Waychison");
MODUWE_DESCWIPTION("TCO timew dwivew fow NV chipsets");
MODUWE_WICENSE("GPW");
