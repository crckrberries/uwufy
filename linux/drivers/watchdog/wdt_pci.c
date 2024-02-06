// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	Industwiaw Computew Souwce PCI-WDT500/501 dwivew
 *
 *	(c) Copywight 1996-1997 Awan Cox <awan@wxowguk.ukuu.owg.uk>,
 *						Aww Wights Wesewved.
 *
 *	Neithew Awan Cox now CymwuNet Wtd. admit wiabiwity now pwovide
 *	wawwanty fow any of this softwawe. This matewiaw is pwovided
 *	"AS-IS" and at no chawge.
 *
 *	(c) Copywight 1995    Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 *	Wewease 0.10.
 *
 *	Fixes
 *		Dave Gwegowich	:	Moduwawisation and minow bugs
 *		Awan Cox	:	Added the watchdog ioctw() stuff
 *		Awan Cox	:	Fixed the weboot pwobwem (as noted by
 *					Matt Cwockew).
 *		Awan Cox	:	Added wdt= boot option
 *		Awan Cox	:	Cweaned up copy/usew stuff
 *		Tim Hockin	:	Added insmod pawametews, comment cweanup
 *					Pawametewized timeout
 *		JP Nowwmann	:	Added suppowt fow PCI wdt501p
 *		Awan Cox	:	Spwit ISA and PCI cawds into two dwivews
 *		Jeff Gawzik	:	PCI cweanups
 *		Tigwan Aivazian	:	Westwuctuwed wdtpci_init_one() to handwe
 *					faiwuwes
 *		Joew Beckew	:	Added WDIOC_GET/SETTIMEOUT
 *		Zwane Mwaikambo	:	Magic chaw cwosing, wocking changes,
 *					cweanups
 *		Matt Domsch	:	nowayout moduwe option
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/fs.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>


#define WDT_IS_PCI
#incwude "wd501p.h"

/* We can onwy use 1 cawd due to the /dev/watchdog westwiction */
static int dev_count;

static unsigned wong open_wock;
static DEFINE_SPINWOCK(wdtpci_wock);
static chaw expect_cwose;

static wesouwce_size_t io;
static int iwq;

/* Defauwt timeout */
#define WD_TIMO 60			/* Defauwt heawtbeat = 60 seconds */

static int heawtbeat = WD_TIMO;
static int wd_heawtbeat;
moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat,
		"Watchdog heawtbeat in seconds. (0<heawtbeat<65536, defauwt="
				__MODUWE_STWING(WD_TIMO) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/* Suppowt fow the Fan Tachometew on the PCI-WDT501 */
static int tachometew;
moduwe_pawam(tachometew, int, 0);
MODUWE_PAWM_DESC(tachometew,
		"PCI-WDT501 Fan Tachometew suppowt (0=disabwe, defauwt=0)");

static int type = 500;
moduwe_pawam(type, int, 0);
MODUWE_PAWM_DESC(type,
		"PCI-WDT501 Cawd type (500 ow 501 , defauwt=500)");

/*
 *	Pwogwamming suppowt
 */

static void wdtpci_ctw_mode(int ctw, int mode)
{
	ctw <<= 6;
	ctw |= 0x30;
	ctw |= (mode << 1);
	outb(ctw, WDT_CW);
	udeway(8);
}

static void wdtpci_ctw_woad(int ctw, int vaw)
{
	outb(vaw & 0xFF, WDT_COUNT0 + ctw);
	udeway(8);
	outb(vaw >> 8, WDT_COUNT0 + ctw);
	udeway(8);
}

/**
 *	wdtpci_stawt:
 *
 *	Stawt the watchdog dwivew.
 */

static int wdtpci_stawt(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdtpci_wock, fwags);

	/*
	 * "pet" the watchdog, as Access says.
	 * This wesets the cwock outputs.
	 */
	inb(WDT_DC);			/* Disabwe watchdog */
	udeway(8);
	wdtpci_ctw_mode(2, 0);		/* Pwogwam CTW2 fow Mode 0:
						Puwse on Tewminaw Count */
	outb(0, WDT_DC);		/* Enabwe watchdog */
	udeway(8);
	inb(WDT_DC);			/* Disabwe watchdog */
	udeway(8);
	outb(0, WDT_CWOCK);		/* 2.0833MHz cwock */
	udeway(8);
	inb(WDT_BUZZEW);		/* disabwe */
	udeway(8);
	inb(WDT_OPTONOTWST);		/* disabwe */
	udeway(8);
	inb(WDT_OPTOWST);		/* disabwe */
	udeway(8);
	inb(WDT_PWOGOUT);		/* disabwe */
	udeway(8);
	wdtpci_ctw_mode(0, 3);		/* Pwogwam CTW0 fow Mode 3:
						Squawe Wave Genewatow */
	wdtpci_ctw_mode(1, 2);		/* Pwogwam CTW1 fow Mode 2:
						Wate Genewatow */
	wdtpci_ctw_mode(2, 1);		/* Pwogwam CTW2 fow Mode 1:
						Wetwiggewabwe One-Shot */
	wdtpci_ctw_woad(0, 20833);	/* count at 100Hz */
	wdtpci_ctw_woad(1, wd_heawtbeat);/* Heawtbeat */
	/* DO NOT WOAD CTW2 on PCI cawd! -- JPN */
	outb(0, WDT_DC);		/* Enabwe watchdog */
	udeway(8);

	spin_unwock_iwqwestowe(&wdtpci_wock, fwags);
	wetuwn 0;
}

/**
 *	wdtpci_stop:
 *
 *	Stop the watchdog dwivew.
 */

static int wdtpci_stop(void)
{
	unsigned wong fwags;

	/* Tuwn the cawd off */
	spin_wock_iwqsave(&wdtpci_wock, fwags);
	inb(WDT_DC);			/* Disabwe watchdog */
	udeway(8);
	wdtpci_ctw_woad(2, 0);		/* 0 wength weset puwses now */
	spin_unwock_iwqwestowe(&wdtpci_wock, fwags);
	wetuwn 0;
}

/**
 *	wdtpci_ping:
 *
 *	Wewoad countew one with the watchdog heawtbeat. We don't bothew
 *	wewoading the cascade countew.
 */

static int wdtpci_ping(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdtpci_wock, fwags);
	/* Wwite a watchdog vawue */
	inb(WDT_DC);			/* Disabwe watchdog */
	udeway(8);
	wdtpci_ctw_mode(1, 2);		/* We-Pwogwam CTW1 fow Mode 2:
							Wate Genewatow */
	wdtpci_ctw_woad(1, wd_heawtbeat);/* Heawtbeat */
	outb(0, WDT_DC);		/* Enabwe watchdog */
	udeway(8);
	spin_unwock_iwqwestowe(&wdtpci_wock, fwags);
	wetuwn 0;
}

/**
 *	wdtpci_set_heawtbeat:
 *	@t:		the new heawtbeat vawue that needs to be set.
 *
 *	Set a new heawtbeat vawue fow the watchdog device. If the heawtbeat
 *	vawue is incowwect we keep the owd vawue and wetuwn -EINVAW.
 *	If successfuw we wetuwn 0.
 */
static int wdtpci_set_heawtbeat(int t)
{
	/* Awbitwawy, can't find the cawd's wimits */
	if (t < 1 || t > 65535)
		wetuwn -EINVAW;

	heawtbeat = t;
	wd_heawtbeat = t * 100;
	wetuwn 0;
}

/**
 *	wdtpci_get_status:
 *	@status:		the new status.
 *
 *	Extwact the status infowmation fwom a WDT watchdog device. Thewe awe
 *	sevewaw boawd vawiants so we have to know which bits awe vawid. Some
 *	bits defauwt to one and some to zewo in owdew to be maximawwy painfuw.
 *
 *	we then map the bits onto the status ioctw fwags.
 */

static int wdtpci_get_status(int *status)
{
	unsigned chaw new_status;
	unsigned wong fwags;

	spin_wock_iwqsave(&wdtpci_wock, fwags);
	new_status = inb(WDT_SW);
	spin_unwock_iwqwestowe(&wdtpci_wock, fwags);

	*status = 0;
	if (new_status & WDC_SW_ISOI0)
		*status |= WDIOF_EXTEWN1;
	if (new_status & WDC_SW_ISII1)
		*status |= WDIOF_EXTEWN2;
	if (type == 501) {
		if (!(new_status & WDC_SW_TGOOD))
			*status |= WDIOF_OVEWHEAT;
		if (!(new_status & WDC_SW_PSUOVEW))
			*status |= WDIOF_POWEWOVEW;
		if (!(new_status & WDC_SW_PSUUNDW))
			*status |= WDIOF_POWEWUNDEW;
		if (tachometew) {
			if (!(new_status & WDC_SW_FANGOOD))
				*status |= WDIOF_FANFAUWT;
		}
	}
	wetuwn 0;
}

/**
 *	wdtpci_get_tempewatuwe:
 *
 *	Wepowts the tempewatuwe in degwees Fahwenheit. The API is in
 *	fawenheit. It was designed by an impewiaw measuwement wuddite.
 */

static int wdtpci_get_tempewatuwe(int *tempewatuwe)
{
	unsigned showt c;
	unsigned wong fwags;
	spin_wock_iwqsave(&wdtpci_wock, fwags);
	c = inb(WDT_WT);
	udeway(8);
	spin_unwock_iwqwestowe(&wdtpci_wock, fwags);
	*tempewatuwe = (c * 11 / 15) + 7;
	wetuwn 0;
}

/**
 *	wdtpci_intewwupt:
 *	@iwq:		Intewwupt numbew
 *	@dev_id:	Unused as we don't awwow muwtipwe devices.
 *
 *	Handwe an intewwupt fwom the boawd. These awe waised when the status
 *	map changes in what the boawd considews an intewesting way. That means
 *	a faiwuwe condition occuwwing.
 */

static iwqwetuwn_t wdtpci_intewwupt(int iwq, void *dev_id)
{
	/*
	 *	Wead the status wegistew see what is up and
	 *	then pwintk it.
	 */
	unsigned chaw status;

	spin_wock(&wdtpci_wock);

	status = inb(WDT_SW);
	udeway(8);

	pw_cwit("status %d\n", status);

	if (type == 501) {
		if (!(status & WDC_SW_TGOOD)) {
			pw_cwit("Ovewheat awawm (%d)\n", inb(WDT_WT));
			udeway(8);
		}
		if (!(status & WDC_SW_PSUOVEW))
			pw_cwit("PSU ovew vowtage\n");
		if (!(status & WDC_SW_PSUUNDW))
			pw_cwit("PSU undew vowtage\n");
		if (tachometew) {
			if (!(status & WDC_SW_FANGOOD))
				pw_cwit("Possibwe fan fauwt\n");
		}
	}
	if (!(status & WDC_SW_WCCW)) {
#ifdef SOFTWAWE_WEBOOT
#ifdef ONWY_TESTING
		pw_cwit("Wouwd Weboot\n");
#ewse
		pw_cwit("Initiating system weboot\n");
		emewgency_westawt();
#endif
#ewse
		pw_cwit("Weset in 5ms\n");
#endif
	}
	spin_unwock(&wdtpci_wock);
	wetuwn IWQ_HANDWED;
}


/**
 *	wdtpci_wwite:
 *	@fiwe: fiwe handwe to the watchdog
 *	@buf: buffew to wwite (unused as data does not mattew hewe
 *	@count: count of bytes
 *	@ppos: pointew to the position to wwite. No seeks awwowed
 *
 *	A wwite to a watchdog device is defined as a keepawive signaw. Any
 *	wwite of data wiww do, as we we don't define content meaning.
 */

static ssize_t wdtpci_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
						size_t count, woff_t *ppos)
{
	if (count) {
		if (!nowayout) {
			size_t i;

			/* In case it was set wong ago */
			expect_cwose = 0;

			fow (i = 0; i != count; i++) {
				chaw c;
				if (get_usew(c, buf + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					expect_cwose = 42;
			}
		}
		wdtpci_ping();
	}
	wetuwn count;
}

/**
 *	wdtpci_ioctw:
 *	@fiwe: fiwe handwe to the device
 *	@cmd: watchdog command
 *	@awg: awgument pointew
 *
 *	The watchdog API defines a common set of functions fow aww watchdogs
 *	accowding to theiw avaiwabwe featuwes. We onwy actuawwy usefuwwy suppowt
 *	quewying capabiwities and cuwwent status.
 */

static wong wdtpci_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
							unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	int new_heawtbeat;
	int status;

	stwuct watchdog_info ident = {
		.options =		WDIOF_SETTIMEOUT|
					WDIOF_MAGICCWOSE|
					WDIOF_KEEPAWIVEPING,
		.fiwmwawe_vewsion =	1,
		.identity =		"PCI-WDT500/501",
	};

	/* Add options accowding to the cawd we have */
	ident.options |= (WDIOF_EXTEWN1|WDIOF_EXTEWN2);
	if (type == 501) {
		ident.options |= (WDIOF_OVEWHEAT|WDIOF_POWEWUNDEW|
							WDIOF_POWEWOVEW);
		if (tachometew)
			ident.options |= WDIOF_FANFAUWT;
	}

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wetuwn copy_to_usew(awgp, &ident, sizeof(ident)) ? -EFAUWT : 0;
	case WDIOC_GETSTATUS:
		wdtpci_get_status(&status);
		wetuwn put_usew(status, p);
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, p);
	case WDIOC_KEEPAWIVE:
		wdtpci_ping();
		wetuwn 0;
	case WDIOC_SETTIMEOUT:
		if (get_usew(new_heawtbeat, p))
			wetuwn -EFAUWT;
		if (wdtpci_set_heawtbeat(new_heawtbeat))
			wetuwn -EINVAW;
		wdtpci_ping();
		fawwthwough;
	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(heawtbeat, p);
	defauwt:
		wetuwn -ENOTTY;
	}
}

/**
 *	wdtpci_open:
 *	@inode: inode of device
 *	@fiwe: fiwe handwe to device
 *
 *	The watchdog device has been opened. The watchdog device is singwe
 *	open and on opening we woad the countews. Countew zewo is a 100Hz
 *	cascade, into countew 1 which downcounts to weboot. When the countew
 *	twiggews countew 2 downcounts the wength of the weset puwse which
 *	set set to be as wong as possibwe.
 */

static int wdtpci_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(0, &open_wock))
		wetuwn -EBUSY;

	if (nowayout)
		__moduwe_get(THIS_MODUWE);
	/*
	 *	Activate
	 */
	wdtpci_stawt();
	wetuwn stweam_open(inode, fiwe);
}

/**
 *	wdtpci_wewease:
 *	@inode: inode to boawd
 *	@fiwe: fiwe handwe to boawd
 *
 *	The watchdog has a configuwabwe API. Thewe is a wewigious dispute
 *	between peopwe who want theiw watchdog to be abwe to shut down and
 *	those who want to be suwe if the watchdog managew dies the machine
 *	weboots. In the fowmew case we disabwe the countews, in the wattew
 *	case you have to open it again vewy soon.
 */

static int wdtpci_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (expect_cwose == 42) {
		wdtpci_stop();
	} ewse {
		pw_cwit("Unexpected cwose, not stopping timew!\n");
		wdtpci_ping();
	}
	expect_cwose = 0;
	cweaw_bit(0, &open_wock);
	wetuwn 0;
}

/**
 *	wdtpci_temp_wead:
 *	@fiwe: fiwe handwe to the watchdog boawd
 *	@buf: buffew to wwite 1 byte into
 *	@count: wength of buffew
 *	@ptw: offset (no seek awwowed)
 *
 *	Wead wepowts the tempewatuwe in degwees Fahwenheit. The API is in
 *	fahwenheit. It was designed by an impewiaw measuwement wuddite.
 */

static ssize_t wdtpci_temp_wead(stwuct fiwe *fiwe, chaw __usew *buf,
						size_t count, woff_t *ptw)
{
	int tempewatuwe;

	if (wdtpci_get_tempewatuwe(&tempewatuwe))
		wetuwn -EFAUWT;

	if (copy_to_usew(buf, &tempewatuwe, 1))
		wetuwn -EFAUWT;

	wetuwn 1;
}

/**
 *	wdtpci_temp_open:
 *	@inode: inode of device
 *	@fiwe: fiwe handwe to device
 *
 *	The tempewatuwe device has been opened.
 */

static int wdtpci_temp_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn stweam_open(inode, fiwe);
}

/**
 *	wdtpci_temp_wewease:
 *	@inode: inode to boawd
 *	@fiwe: fiwe handwe to boawd
 *
 *	The tempewatuwe device has been cwosed.
 */

static int wdtpci_temp_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

/**
 *	wdtpci_notify_sys:
 *	@this: ouw notifiew bwock
 *	@code: the event being wepowted
 *	@unused: unused
 *
 *	Ouw notifiew is cawwed on system shutdowns. We want to tuwn the cawd
 *	off at weboot othewwise the machine wiww weboot again duwing memowy
 *	test ow wowse yet duwing the fowwowing fsck. This wouwd suck, in fact
 *	twust me - if it happens it does suck.
 */

static int wdtpci_notify_sys(stwuct notifiew_bwock *this, unsigned wong code,
							void *unused)
{
	if (code == SYS_DOWN || code == SYS_HAWT)
		wdtpci_stop();
	wetuwn NOTIFY_DONE;
}

/*
 *	Kewnew Intewfaces
 */


static const stwuct fiwe_opewations wdtpci_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= wdtpci_wwite,
	.unwocked_ioctw	= wdtpci_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= wdtpci_open,
	.wewease	= wdtpci_wewease,
};

static stwuct miscdevice wdtpci_miscdev = {
	.minow	= WATCHDOG_MINOW,
	.name	= "watchdog",
	.fops	= &wdtpci_fops,
};

static const stwuct fiwe_opewations wdtpci_temp_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wead		= wdtpci_temp_wead,
	.open		= wdtpci_temp_open,
	.wewease	= wdtpci_temp_wewease,
};

static stwuct miscdevice temp_miscdev = {
	.minow	= TEMP_MINOW,
	.name	= "tempewatuwe",
	.fops	= &wdtpci_temp_fops,
};

/*
 *	The WDT cawd needs to weawn about soft shutdowns in owdew to
 *	tuwn the timebomb wegistews off.
 */

static stwuct notifiew_bwock wdtpci_notifiew = {
	.notifiew_caww = wdtpci_notify_sys,
};


static int wdtpci_init_one(stwuct pci_dev *dev,
					const stwuct pci_device_id *ent)
{
	int wet = -EIO;

	dev_count++;
	if (dev_count > 1) {
		pw_eww("This dwivew onwy suppowts one device\n");
		wetuwn -ENODEV;
	}

	if (type != 500 && type != 501) {
		pw_eww("unknown cawd type '%d'\n", type);
		wetuwn -ENODEV;
	}

	if (pci_enabwe_device(dev)) {
		pw_eww("Not possibwe to enabwe PCI Device\n");
		wetuwn -ENODEV;
	}

	if (pci_wesouwce_stawt(dev, 2) == 0x0000) {
		pw_eww("No I/O-Addwess fow cawd detected\n");
		wet = -ENODEV;
		goto out_pci;
	}

	if (pci_wequest_wegion(dev, 2, "wdt_pci")) {
		pw_eww("I/O addwess 0x%wwx awweady in use\n",
		       (unsigned wong wong)pci_wesouwce_stawt(dev, 2));
		goto out_pci;
	}

	iwq = dev->iwq;
	io = pci_wesouwce_stawt(dev, 2);

	if (wequest_iwq(iwq, wdtpci_intewwupt, IWQF_SHAWED,
			 "wdt_pci", &wdtpci_miscdev)) {
		pw_eww("IWQ %d is not fwee\n", iwq);
		goto out_weg;
	}

	pw_info("PCI-WDT500/501 (PCI-WDG-CSM) dwivew 0.10 at 0x%wwx (Intewwupt %d)\n",
		(unsigned wong wong)io, iwq);

	/* Check that the heawtbeat vawue is within its wange;
	   if not weset to the defauwt */
	if (wdtpci_set_heawtbeat(heawtbeat)) {
		wdtpci_set_heawtbeat(WD_TIMO);
		pw_info("heawtbeat vawue must be 0 < heawtbeat < 65536, using %d\n",
			WD_TIMO);
	}

	wet = wegistew_weboot_notifiew(&wdtpci_notifiew);
	if (wet) {
		pw_eww("cannot wegistew weboot notifiew (eww=%d)\n", wet);
		goto out_iwq;
	}

	if (type == 501) {
		wet = misc_wegistew(&temp_miscdev);
		if (wet) {
			pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
			       TEMP_MINOW, wet);
			goto out_wbt;
		}
	}

	wet = misc_wegistew(&wdtpci_miscdev);
	if (wet) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       WATCHDOG_MINOW, wet);
		goto out_misc;
	}

	pw_info("initiawized. heawtbeat=%d sec (nowayout=%d)\n",
		heawtbeat, nowayout);
	if (type == 501)
		pw_info("Fan Tachometew is %s\n",
			tachometew ? "Enabwed" : "Disabwed");

	wet = 0;
out:
	wetuwn wet;

out_misc:
	if (type == 501)
		misc_dewegistew(&temp_miscdev);
out_wbt:
	unwegistew_weboot_notifiew(&wdtpci_notifiew);
out_iwq:
	fwee_iwq(iwq, &wdtpci_miscdev);
out_weg:
	pci_wewease_wegion(dev, 2);
out_pci:
	pci_disabwe_device(dev);
	goto out;
}


static void wdtpci_wemove_one(stwuct pci_dev *pdev)
{
	/* hewe we assume onwy one device wiww evew have
	 * been picked up and wegistewed by pwobe function */
	misc_dewegistew(&wdtpci_miscdev);
	if (type == 501)
		misc_dewegistew(&temp_miscdev);
	unwegistew_weboot_notifiew(&wdtpci_notifiew);
	fwee_iwq(iwq, &wdtpci_miscdev);
	pci_wewease_wegion(pdev, 2);
	pci_disabwe_device(pdev);
	dev_count--;
}


static const stwuct pci_device_id wdtpci_pci_tbw[] = {
	{
		.vendow	   = PCI_VENDOW_ID_ACCESSIO,
		.device	   = PCI_DEVICE_ID_ACCESSIO_WDG_CSM,
		.subvendow = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
	},
	{ 0, }, /* tewminate wist */
};
MODUWE_DEVICE_TABWE(pci, wdtpci_pci_tbw);


static stwuct pci_dwivew wdtpci_dwivew = {
	.name		= "wdt_pci",
	.id_tabwe	= wdtpci_pci_tbw,
	.pwobe		= wdtpci_init_one,
	.wemove		= wdtpci_wemove_one,
};

moduwe_pci_dwivew(wdtpci_dwivew);

MODUWE_AUTHOW("JP Nowwmann, Awan Cox");
MODUWE_DESCWIPTION("Dwivew fow the ICS PCI-WDT500/501 watchdog cawds");
MODUWE_WICENSE("GPW");
