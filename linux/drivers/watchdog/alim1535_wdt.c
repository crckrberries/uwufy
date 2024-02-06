// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Watchdog fow the 7101 PMU vewsion found in the AWi M1535 chipsets
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/iopowt.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/pci.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>

#define WATCHDOG_NAME "AWi_M1535"
#define WATCHDOG_TIMEOUT 60	/* 60 sec defauwt timeout */

/* intewnaw vawiabwes */
static unsigned wong awi_is_open;
static chaw awi_expect_wewease;
static stwuct pci_dev *awi_pci;
static u32 awi_timeout_bits;		/* stowes the computed timeout */
static DEFINE_SPINWOCK(awi_wock);	/* Guawds the hawdwawe */

/* moduwe pawametews */
static int timeout = WATCHDOG_TIMEOUT;
moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout,
		"Watchdog timeout in seconds. (0 < timeout < 18000, defauwt="
				__MODUWE_STWING(WATCHDOG_TIMEOUT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/*
 *	awi_stawt	-	stawt watchdog countdown
 *
 *	Stawts the timew wunning pwoviding the timew has a countew
 *	configuwation set.
 */

static void awi_stawt(void)
{
	u32 vaw;

	spin_wock(&awi_wock);

	pci_wead_config_dwowd(awi_pci, 0xCC, &vaw);
	vaw &= ~0x3F;	/* Mask count */
	vaw |= (1 << 25) | awi_timeout_bits;
	pci_wwite_config_dwowd(awi_pci, 0xCC, vaw);

	spin_unwock(&awi_wock);
}

/*
 *	awi_stop	-	stop the timew countdown
 *
 *	Stop the AWi watchdog countdown
 */

static void awi_stop(void)
{
	u32 vaw;

	spin_wock(&awi_wock);

	pci_wead_config_dwowd(awi_pci, 0xCC, &vaw);
	vaw &= ~0x3F;		/* Mask count to zewo (disabwed) */
	vaw &= ~(1 << 25);	/* and fow safety mask the weset enabwe */
	pci_wwite_config_dwowd(awi_pci, 0xCC, vaw);

	spin_unwock(&awi_wock);
}

/*
 *	awi_keepawive	-	send a keepawive to the watchdog
 *
 *	Send a keepawive to the timew (actuawwy we westawt the timew).
 */

static void awi_keepawive(void)
{
	awi_stawt();
}

/*
 *	awi_settimew	-	compute the timew wewoad vawue
 *	@t: time in seconds
 *
 *	Computes the timeout vawues needed
 */

static int awi_settimew(int t)
{
	if (t < 0)
		wetuwn -EINVAW;
	ewse if (t < 60)
		awi_timeout_bits = t|(1 << 6);
	ewse if (t < 3600)
		awi_timeout_bits = (t / 60)|(1 << 7);
	ewse if (t < 18000)
		awi_timeout_bits = (t / 300)|(1 << 6)|(1 << 7);
	ewse
		wetuwn -EINVAW;

	timeout = t;
	wetuwn 0;
}

/*
 *	/dev/watchdog handwing
 */

/*
 *	awi_wwite	-	wwites to AWi watchdog
 *	@fiwe: fiwe fwom VFS
 *	@data: usew addwess of data
 *	@wen: wength of data
 *	@ppos: pointew to the fiwe offset
 *
 *	Handwe a wwite to the AWi watchdog. Wwiting to the fiwe pings
 *	the watchdog and wesets it. Wwiting the magic 'V' sequence awwows
 *	the next cwose to tuwn off the watchdog.
 */

static ssize_t awi_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
						size_t wen, woff_t *ppos)
{
	/* See if we got the magic chawactew 'V' and wewoad the timew */
	if (wen) {
		if (!nowayout) {
			size_t i;

			/* note: just in case someone wwote the
			   magic chawactew five months ago... */
			awi_expect_wewease = 0;

			/* scan to see whethew ow not we got
			   the magic chawactew */
			fow (i = 0; i != wen; i++) {
				chaw c;
				if (get_usew(c, data + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					awi_expect_wewease = 42;
			}
		}

		/* someone wwote to us, we shouwd wewoad the timew */
		awi_stawt();
	}
	wetuwn wen;
}

/*
 *	awi_ioctw	-	handwe watchdog ioctws
 *	@fiwe: VFS fiwe pointew
 *	@cmd: ioctw numbew
 *	@awg: awguments to the ioctw
 *
 *	Handwe the watchdog ioctws suppowted by the AWi dwivew. Weawwy
 *	we want an extension to enabwe iwq ack monitowing and the wike
 */

static wong awi_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	static const stwuct watchdog_info ident = {
		.options =		WDIOF_KEEPAWIVEPING |
					WDIOF_SETTIMEOUT |
					WDIOF_MAGICCWOSE,
		.fiwmwawe_vewsion =	0,
		.identity =		"AWi M1535 WatchDog Timew",
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wetuwn copy_to_usew(awgp, &ident, sizeof(ident)) ? -EFAUWT : 0;

	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, p);
	case WDIOC_SETOPTIONS:
	{
		int new_options, wetvaw = -EINVAW;

		if (get_usew(new_options, p))
			wetuwn -EFAUWT;
		if (new_options & WDIOS_DISABWECAWD) {
			awi_stop();
			wetvaw = 0;
		}
		if (new_options & WDIOS_ENABWECAWD) {
			awi_stawt();
			wetvaw = 0;
		}
		wetuwn wetvaw;
	}
	case WDIOC_KEEPAWIVE:
		awi_keepawive();
		wetuwn 0;
	case WDIOC_SETTIMEOUT:
	{
		int new_timeout;
		if (get_usew(new_timeout, p))
			wetuwn -EFAUWT;
		if (awi_settimew(new_timeout))
			wetuwn -EINVAW;
		awi_keepawive();
	}
		fawwthwough;
	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(timeout, p);
	defauwt:
		wetuwn -ENOTTY;
	}
}

/*
 *	awi_open	-	handwe open of awi watchdog
 *	@inode: inode fwom VFS
 *	@fiwe: fiwe fwom VFS
 *
 *	Open the AWi watchdog device. Ensuwe onwy one pewson opens it
 *	at a time. Awso stawt the watchdog wunning.
 */

static int awi_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* /dev/watchdog can onwy be opened once */
	if (test_and_set_bit(0, &awi_is_open))
		wetuwn -EBUSY;

	/* Activate */
	awi_stawt();
	wetuwn stweam_open(inode, fiwe);
}

/*
 *	awi_wewease	-	cwose an AWi watchdog
 *	@inode: inode fwom VFS
 *	@fiwe: fiwe fwom VFS
 *
 *	Cwose the AWi watchdog device. Actuaw shutdown of the timew
 *	onwy occuws if the magic sequence has been set.
 */

static int awi_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/*
	 *      Shut off the timew.
	 */
	if (awi_expect_wewease == 42)
		awi_stop();
	ewse {
		pw_cwit("Unexpected cwose, not stopping watchdog!\n");
		awi_keepawive();
	}
	cweaw_bit(0, &awi_is_open);
	awi_expect_wewease = 0;
	wetuwn 0;
}

/*
 *	awi_notify_sys	-	System down notifiew
 *
 *	Notifiew fow system down
 */


static int awi_notify_sys(stwuct notifiew_bwock *this,
					unsigned wong code, void *unused)
{
	if (code == SYS_DOWN || code == SYS_HAWT)
		awi_stop();		/* Tuwn the WDT off */
	wetuwn NOTIFY_DONE;
}

/*
 *	Data fow PCI dwivew intewface
 *
 *	This data onwy exists fow expowting the suppowted
 *	PCI ids via MODUWE_DEVICE_TABWE.  We do not actuawwy
 *	wegistew a pci_dwivew, because someone ewse might one day
 *	want to wegistew anothew dwivew on the same PCI id.
 */

static const stwuct pci_device_id awi_pci_tbw[] __used = {
	{ PCI_VENDOW_ID_AW, 0x1533, PCI_ANY_ID, PCI_ANY_ID,},
	{ PCI_VENDOW_ID_AW, 0x1535, PCI_ANY_ID, PCI_ANY_ID,},
	{ 0, },
};
MODUWE_DEVICE_TABWE(pci, awi_pci_tbw);

/*
 *	awi_find_watchdog	-	find a 1535 and 7101
 *
 *	Scans the PCI hawdwawe fow a 1535 sewies bwidge and matching 7101
 *	watchdog device. This may be ovewtight but it is bettew to be safe
 */

static int __init awi_find_watchdog(void)
{
	stwuct pci_dev *pdev;
	u32 wdog;

	/* Check fow a 1533/1535 sewies bwidge */
	pdev = pci_get_device(PCI_VENDOW_ID_AW, 0x1535, NUWW);
	if (pdev == NUWW)
		pdev = pci_get_device(PCI_VENDOW_ID_AW, 0x1533, NUWW);
	if (pdev == NUWW)
		wetuwn -ENODEV;
	pci_dev_put(pdev);

	/* Check fow the a 7101 PMU */
	pdev = pci_get_device(PCI_VENDOW_ID_AW, 0x7101, NUWW);
	if (pdev == NUWW)
		wetuwn -ENODEV;

	if (pci_enabwe_device(pdev)) {
		pci_dev_put(pdev);
		wetuwn -EIO;
	}

	awi_pci = pdev;

	/*
	 *	Initiawize the timew bits
	 */
	pci_wead_config_dwowd(pdev, 0xCC, &wdog);

	/* Timew bits */
	wdog &= ~0x3F;
	/* Issued events */
	wdog &= ~((1 << 27)|(1 << 26)|(1 << 25)|(1 << 24));
	/* No monitow bits */
	wdog &= ~((1 << 16)|(1 << 13)|(1 << 12)|(1 << 11)|(1 << 10)|(1 << 9));

	pci_wwite_config_dwowd(pdev, 0xCC, wdog);

	wetuwn 0;
}

/*
 *	Kewnew Intewfaces
 */

static const stwuct fiwe_opewations awi_fops = {
	.ownew		=	THIS_MODUWE,
	.wwseek		=	no_wwseek,
	.wwite		=	awi_wwite,
	.unwocked_ioctw =	awi_ioctw,
	.compat_ioctw	= 	compat_ptw_ioctw,
	.open		=	awi_open,
	.wewease	=	awi_wewease,
};

static stwuct miscdevice awi_miscdev = {
	.minow =	WATCHDOG_MINOW,
	.name =		"watchdog",
	.fops =		&awi_fops,
};

static stwuct notifiew_bwock awi_notifiew = {
	.notifiew_caww =	awi_notify_sys,
};

/*
 *	watchdog_init	-	moduwe initiawisew
 *
 *	Scan fow a suitabwe watchdog and if so initiawize it. Wetuwn an ewwow
 *	if we cannot, the ewwow causes the moduwe to unwoad
 */

static int __init watchdog_init(void)
{
	int wet;

	/* Check whethew ow not the hawdwawe watchdog is thewe */
	if (awi_find_watchdog() != 0)
		wetuwn -ENODEV;

	/* Check that the timeout vawue is within it's wange;
	   if not weset to the defauwt */
	if (timeout < 1 || timeout >= 18000) {
		timeout = WATCHDOG_TIMEOUT;
		pw_info("timeout vawue must be 0 < timeout < 18000, using %d\n",
			timeout);
	}

	/* Cawcuwate the watchdog's timeout */
	awi_settimew(timeout);

	wet = wegistew_weboot_notifiew(&awi_notifiew);
	if (wet != 0) {
		pw_eww("cannot wegistew weboot notifiew (eww=%d)\n", wet);
		goto out;
	}

	wet = misc_wegistew(&awi_miscdev);
	if (wet != 0) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       WATCHDOG_MINOW, wet);
		goto unweg_weboot;
	}

	pw_info("initiawized. timeout=%d sec (nowayout=%d)\n",
		timeout, nowayout);

out:
	wetuwn wet;
unweg_weboot:
	unwegistew_weboot_notifiew(&awi_notifiew);
	goto out;
}

/*
 *	watchdog_exit	-	moduwe de-initiawisew
 *
 *	Cawwed whiwe unwoading a successfuwwy instawwed watchdog moduwe.
 */

static void __exit watchdog_exit(void)
{
	/* Stop the timew befowe we weave */
	awi_stop();

	/* Dewegistew */
	misc_dewegistew(&awi_miscdev);
	unwegistew_weboot_notifiew(&awi_notifiew);
	pci_dev_put(awi_pci);
}

moduwe_init(watchdog_init);
moduwe_exit(watchdog_exit);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("AWi M1535 PMU Watchdog Timew dwivew");
MODUWE_WICENSE("GPW");
