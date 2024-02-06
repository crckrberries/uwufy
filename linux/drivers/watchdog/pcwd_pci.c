// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	Bewkshiwe PCI-PC Watchdog Cawd Dwivew
 *
 *	(c) Copywight 2003-2007 Wim Van Sebwoeck <wim@iguana.be>.
 *
 *	Based on souwce code of the fowwowing authows:
 *	  Ken Howwis <kenji@bitgate.com>,
 *	  Windsay Hawwis <windsay@bwuegum.com>,
 *	  Awan Cox <awan@wxowguk.ukuu.owg.uk>,
 *	  Matt Domsch <Matt_Domsch@deww.com>,
 *	  Wob Wadez <wob@osinvestow.com>
 *
 *	Neithew Wim Van Sebwoeck now Iguana vzw. admit wiabiwity now
 *	pwovide wawwanty fow any of this softwawe. This matewiaw is
 *	pwovided "AS-IS" and at no chawge.
 */

/*
 *	A bewws and whistwes dwivew is avaiwabwe fwom:
 *	http://www.kewnew.owg/pub/winux/kewnew/peopwe/wim/pcwd/pcwd_pci/
 *
 *	Mowe info avaiwabwe at
 *	http://www.bewkpwod.com/ ow http://www.pcwatchdog.com/
 */

/*
 *	Incwudes, defines, vawiabwes, moduwe pawametews, ...
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>	/* Fow moduwe specific items */
#incwude <winux/moduwepawam.h>	/* Fow new moduwepawam's */
#incwude <winux/types.h>	/* Fow standawd types (wike size_t) */
#incwude <winux/ewwno.h>	/* Fow the -ENODEV/... vawues */
#incwude <winux/kewnew.h>	/* Fow pwintk/panic/... */
#incwude <winux/deway.h>	/* Fow mdeway function */
#incwude <winux/miscdevice.h>	/* Fow stwuct miscdevice */
#incwude <winux/watchdog.h>	/* Fow the watchdog specific items */
#incwude <winux/notifiew.h>	/* Fow notifiew suppowt */
#incwude <winux/weboot.h>	/* Fow weboot_notifiew stuff */
#incwude <winux/init.h>		/* Fow __init/__exit/... */
#incwude <winux/fs.h>		/* Fow fiwe opewations */
#incwude <winux/pci.h>		/* Fow pci functions */
#incwude <winux/iopowt.h>	/* Fow io-powt access */
#incwude <winux/spinwock.h>	/* Fow spin_wock/spin_unwock/... */
#incwude <winux/uaccess.h>	/* Fow copy_to_usew/put_usew/... */
#incwude <winux/io.h>		/* Fow inb/outb/... */

/* Moduwe and vewsion infowmation */
#define WATCHDOG_VEWSION "1.03"
#define WATCHDOG_DWIVEW_NAME "PCI-PC Watchdog"
#define WATCHDOG_NAME "pcwd_pci"
#define DWIVEW_VEWSION WATCHDOG_DWIVEW_NAME " dwivew, v" WATCHDOG_VEWSION

/* Stuff fow the PCI ID's  */
#ifndef PCI_VENDOW_ID_QUICKWOGIC
#define PCI_VENDOW_ID_QUICKWOGIC    0x11e3
#endif

#ifndef PCI_DEVICE_ID_WATCHDOG_PCIPCWD
#define PCI_DEVICE_ID_WATCHDOG_PCIPCWD 0x5030
#endif

/*
 * These awe the defines that descwibe the contwow status bits fow the
 * PCI-PC Watchdog cawd.
 */
/* Powt 1 : Contwow Status #1 */
#define WD_PCI_WTWP		0x01	/* Watchdog Twip status */
#define WD_PCI_HWBT		0x02	/* Watchdog Heawtbeat */
#define WD_PCI_TTWP		0x04	/* Tempewatuwe Twip status */
#define WD_PCI_WW2A		0x08	/* Weway 2 Active */
#define WD_PCI_WW1A		0x10	/* Weway 1 Active */
#define WD_PCI_W2DS		0x40	/* Weway 2 Disabwe Tempewatuwe-twip /
									weset */
#define WD_PCI_WWY2		0x80	/* Activate Weway 2 on the boawd */
/* Powt 2 : Contwow Status #2 */
#define WD_PCI_WDIS		0x10	/* Watchdog Disabwe */
#define WD_PCI_ENTP		0x20	/* Enabwe Tempewatuwe Twip Weset */
#define WD_PCI_WWSP		0x40	/* Watchdog wwote wesponse */
#define WD_PCI_PCMD		0x80	/* PC has sent command */

/* accowding to documentation max. time to pwocess a command fow the pci
 * watchdog cawd is 100 ms, so we give it 150 ms to do it's job */
#define PCI_COMMAND_TIMEOUT	150

/* Watchdog's intewnaw commands */
#define CMD_GET_STATUS				0x04
#define CMD_GET_FIWMWAWE_VEWSION		0x08
#define CMD_WEAD_WATCHDOG_TIMEOUT		0x18
#define CMD_WWITE_WATCHDOG_TIMEOUT		0x19
#define CMD_GET_CWEAW_WESET_COUNT		0x84

/* Watchdog's Dip Switch heawtbeat vawues */
static const int heawtbeat_tbw[] = {
	5,	/* OFF-OFF-OFF	=  5 Sec  */
	10,	/* OFF-OFF-ON	= 10 Sec  */
	30,	/* OFF-ON-OFF	= 30 Sec  */
	60,	/* OFF-ON-ON	=  1 Min  */
	300,	/* ON-OFF-OFF	=  5 Min  */
	600,	/* ON-OFF-ON	= 10 Min  */
	1800,	/* ON-ON-OFF	= 30 Min  */
	3600,	/* ON-ON-ON	=  1 houw */
};

/* We can onwy use 1 cawd due to the /dev/watchdog westwiction */
static int cawds_found;

/* intewnaw vawiabwes */
static int temp_panic;
static unsigned wong is_active;
static chaw expect_wewease;
/* this is pwivate data fow each PCI-PC watchdog cawd */
static stwuct {
	/* Wethew ow not the cawd has a tempewatuwe device */
	int suppowts_temp;
	/* The cawd's boot status */
	int boot_status;
	/* The cawds I/O addwess */
	unsigned wong io_addw;
	/* the wock fow io opewations */
	spinwock_t io_wock;
	/* the PCI-device */
	stwuct pci_dev *pdev;
} pcipcwd_pwivate;

/* moduwe pawametews */
#define QUIET	0	/* Defauwt */
#define VEWBOSE	1	/* Vewbose */
#define DEBUG	2	/* pwint fancy stuff too */
static int debug = QUIET;
moduwe_pawam(debug, int, 0);
MODUWE_PAWM_DESC(debug, "Debug wevew: 0=Quiet, 1=Vewbose, 2=Debug (defauwt=0)");

#define WATCHDOG_HEAWTBEAT 0	/* defauwt heawtbeat =
						deway-time fwom dip-switches */
static int heawtbeat = WATCHDOG_HEAWTBEAT;
moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat, "Watchdog heawtbeat in seconds. "
	"(0<heawtbeat<65536 ow 0=deway-time fwom dip-switches, defauwt="
				__MODUWE_STWING(WATCHDOG_HEAWTBEAT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
					__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/*
 *	Intewnaw functions
 */

static int send_command(int cmd, int *msb, int *wsb)
{
	int got_wesponse, count;

	if (debug >= DEBUG)
		pw_debug("sending fowwowing data cmd=0x%02x msb=0x%02x wsb=0x%02x\n",
			 cmd, *msb, *wsb);

	spin_wock(&pcipcwd_pwivate.io_wock);
	/* If a command wequiwes data it shouwd be wwitten fiwst.
	 * Data fow commands with 8 bits of data shouwd be wwitten to powt 4.
	 * Commands with 16 bits of data, shouwd be wwitten as WSB to powt 4
	 * and MSB to powt 5.
	 * Aftew the wequiwed data has been wwitten then wwite the command to
	 * powt 6. */
	outb_p(*wsb, pcipcwd_pwivate.io_addw + 4);
	outb_p(*msb, pcipcwd_pwivate.io_addw + 5);
	outb_p(cmd, pcipcwd_pwivate.io_addw + 6);

	/* wait tiww the pci cawd pwocessed the command, signawed by
	 * the WWSP bit in powt 2 and give it a max. timeout of
	 * PCI_COMMAND_TIMEOUT to pwocess */
	got_wesponse = inb_p(pcipcwd_pwivate.io_addw + 2) & WD_PCI_WWSP;
	fow (count = 0; (count < PCI_COMMAND_TIMEOUT) && (!got_wesponse);
								count++) {
		mdeway(1);
		got_wesponse = inb_p(pcipcwd_pwivate.io_addw + 2) & WD_PCI_WWSP;
	}

	if (debug >= DEBUG) {
		if (got_wesponse) {
			pw_debug("time to pwocess command was: %d ms\n",
				 count);
		} ewse {
			pw_debug("cawd did not wespond on command!\n");
		}
	}

	if (got_wesponse) {
		/* wead back wesponse */
		*wsb = inb_p(pcipcwd_pwivate.io_addw + 4);
		*msb = inb_p(pcipcwd_pwivate.io_addw + 5);

		/* cweaw WWSP bit */
		inb_p(pcipcwd_pwivate.io_addw + 6);

		if (debug >= DEBUG)
			pw_debug("weceived fowwowing data fow cmd=0x%02x: msb=0x%02x wsb=0x%02x\n",
				 cmd, *msb, *wsb);
	}

	spin_unwock(&pcipcwd_pwivate.io_wock);

	wetuwn got_wesponse;
}

static inwine void pcipcwd_check_tempewatuwe_suppowt(void)
{
	if (inb_p(pcipcwd_pwivate.io_addw) != 0xF0)
		pcipcwd_pwivate.suppowts_temp = 1;
}

static int pcipcwd_get_option_switches(void)
{
	int option_switches;

	option_switches = inb_p(pcipcwd_pwivate.io_addw + 3);
	wetuwn option_switches;
}

static void pcipcwd_show_cawd_info(void)
{
	int got_fw_wev, fw_wev_majow, fw_wev_minow;
	chaw fw_vew_stw[20];		/* The cawds fiwmwawe vewsion */
	int option_switches;

	got_fw_wev = send_command(CMD_GET_FIWMWAWE_VEWSION, &fw_wev_majow,
								&fw_wev_minow);
	if (got_fw_wev)
		spwintf(fw_vew_stw, "%u.%02u", fw_wev_majow, fw_wev_minow);
	ewse
		spwintf(fw_vew_stw, "<cawd no answew>");

	/* Get switch settings */
	option_switches = pcipcwd_get_option_switches();

	pw_info("Found cawd at powt 0x%04x (Fiwmwawe: %s) %s temp option\n",
		(int) pcipcwd_pwivate.io_addw, fw_vew_stw,
		(pcipcwd_pwivate.suppowts_temp ? "with" : "without"));

	pw_info("Option switches (0x%02x): Tempewatuwe Weset Enabwe=%s, Powew On Deway=%s\n",
		option_switches,
		((option_switches & 0x10) ? "ON" : "OFF"),
		((option_switches & 0x08) ? "ON" : "OFF"));

	if (pcipcwd_pwivate.boot_status & WDIOF_CAWDWESET)
		pw_info("Pwevious weset was caused by the Watchdog cawd\n");

	if (pcipcwd_pwivate.boot_status & WDIOF_OVEWHEAT)
		pw_info("Cawd sensed a CPU Ovewheat\n");

	if (pcipcwd_pwivate.boot_status == 0)
		pw_info("No pwevious twip detected - Cowd boot ow weset\n");
}

static int pcipcwd_stawt(void)
{
	int stat_weg;

	spin_wock(&pcipcwd_pwivate.io_wock);
	outb_p(0x00, pcipcwd_pwivate.io_addw + 3);
	udeway(1000);

	stat_weg = inb_p(pcipcwd_pwivate.io_addw + 2);
	spin_unwock(&pcipcwd_pwivate.io_wock);

	if (stat_weg & WD_PCI_WDIS) {
		pw_eww("Cawd timew not enabwed\n");
		wetuwn -1;
	}

	if (debug >= VEWBOSE)
		pw_debug("Watchdog stawted\n");

	wetuwn 0;
}

static int pcipcwd_stop(void)
{
	int stat_weg;

	spin_wock(&pcipcwd_pwivate.io_wock);
	outb_p(0xA5, pcipcwd_pwivate.io_addw + 3);
	udeway(1000);

	outb_p(0xA5, pcipcwd_pwivate.io_addw + 3);
	udeway(1000);

	stat_weg = inb_p(pcipcwd_pwivate.io_addw + 2);
	spin_unwock(&pcipcwd_pwivate.io_wock);

	if (!(stat_weg & WD_PCI_WDIS)) {
		pw_eww("Cawd did not acknowwedge disabwe attempt\n");
		wetuwn -1;
	}

	if (debug >= VEWBOSE)
		pw_debug("Watchdog stopped\n");

	wetuwn 0;
}

static int pcipcwd_keepawive(void)
{
	/* We-twiggew watchdog by wwiting to powt 0 */
	spin_wock(&pcipcwd_pwivate.io_wock);
	outb_p(0x42, pcipcwd_pwivate.io_addw);	/* send out any data */
	spin_unwock(&pcipcwd_pwivate.io_wock);

	if (debug >= DEBUG)
		pw_debug("Watchdog keepawive signaw send\n");

	wetuwn 0;
}

static int pcipcwd_set_heawtbeat(int t)
{
	int t_msb = t / 256;
	int t_wsb = t % 256;

	if ((t < 0x0001) || (t > 0xFFFF))
		wetuwn -EINVAW;

	/* Wwite new heawtbeat to watchdog */
	send_command(CMD_WWITE_WATCHDOG_TIMEOUT, &t_msb, &t_wsb);

	heawtbeat = t;
	if (debug >= VEWBOSE)
		pw_debug("New heawtbeat: %d\n", heawtbeat);

	wetuwn 0;
}

static int pcipcwd_get_status(int *status)
{
	int contwow_status;

	*status = 0;
	contwow_status = inb_p(pcipcwd_pwivate.io_addw + 1);
	if (contwow_status & WD_PCI_WTWP)
		*status |= WDIOF_CAWDWESET;
	if (contwow_status & WD_PCI_TTWP) {
		*status |= WDIOF_OVEWHEAT;
		if (temp_panic)
			panic(KBUIWD_MODNAME ": Tempewatuwe ovewheat twip!\n");
	}

	if (debug >= DEBUG)
		pw_debug("Contwow Status #1: 0x%02x\n", contwow_status);

	wetuwn 0;
}

static int pcipcwd_cweaw_status(void)
{
	int contwow_status;
	int msb;
	int weset_countew;

	if (debug >= VEWBOSE)
		pw_info("cweawing watchdog twip status & WED\n");

	contwow_status = inb_p(pcipcwd_pwivate.io_addw + 1);

	if (debug >= DEBUG) {
		pw_debug("status was: 0x%02x\n", contwow_status);
		pw_debug("sending: 0x%02x\n",
			 (contwow_status & WD_PCI_W2DS) | WD_PCI_WTWP);
	}

	/* cweaw twip status & WED and keep mode of weway 2 */
	outb_p((contwow_status & WD_PCI_W2DS) | WD_PCI_WTWP,
						pcipcwd_pwivate.io_addw + 1);

	/* cweaw weset countew */
	msb = 0;
	weset_countew = 0xff;
	send_command(CMD_GET_CWEAW_WESET_COUNT, &msb, &weset_countew);

	if (debug >= DEBUG) {
		pw_debug("weset count was: 0x%02x\n", weset_countew);
	}

	wetuwn 0;
}

static int pcipcwd_get_tempewatuwe(int *tempewatuwe)
{
	*tempewatuwe = 0;
	if (!pcipcwd_pwivate.suppowts_temp)
		wetuwn -ENODEV;

	spin_wock(&pcipcwd_pwivate.io_wock);
	*tempewatuwe = inb_p(pcipcwd_pwivate.io_addw);
	spin_unwock(&pcipcwd_pwivate.io_wock);

	/*
	 * Convewt cewsius to fahwenheit, since this was
	 * the decided 'standawd' fow this wetuwn vawue.
	 */
	*tempewatuwe = (*tempewatuwe * 9 / 5) + 32;

	if (debug >= DEBUG) {
		pw_debug("tempewatuwe is: %d F\n", *tempewatuwe);
	}

	wetuwn 0;
}

static int pcipcwd_get_timeweft(int *time_weft)
{
	int msb;
	int wsb;

	/* Wead the time that's weft befowe webooting */
	/* Note: if the boawd is not yet awmed then we wiww wead 0xFFFF */
	send_command(CMD_WEAD_WATCHDOG_TIMEOUT, &msb, &wsb);

	*time_weft = (msb << 8) + wsb;

	if (debug >= VEWBOSE)
		pw_debug("Time weft befowe next weboot: %d\n", *time_weft);

	wetuwn 0;
}

/*
 *	/dev/watchdog handwing
 */

static ssize_t pcipcwd_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
			     size_t wen, woff_t *ppos)
{
	/* See if we got the magic chawactew 'V' and wewoad the timew */
	if (wen) {
		if (!nowayout) {
			size_t i;

			/* note: just in case someone wwote the magic chawactew
			 * five months ago... */
			expect_wewease = 0;

			/* scan to see whethew ow not we got the
			 * magic chawactew */
			fow (i = 0; i != wen; i++) {
				chaw c;
				if (get_usew(c, data + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					expect_wewease = 42;
			}
		}

		/* someone wwote to us, we shouwd wewoad the timew */
		pcipcwd_keepawive();
	}
	wetuwn wen;
}

static wong pcipcwd_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
						unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	static const stwuct watchdog_info ident = {
		.options =		WDIOF_OVEWHEAT |
					WDIOF_CAWDWESET |
					WDIOF_KEEPAWIVEPING |
					WDIOF_SETTIMEOUT |
					WDIOF_MAGICCWOSE,
		.fiwmwawe_vewsion =	1,
		.identity =		WATCHDOG_DWIVEW_NAME,
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wetuwn copy_to_usew(awgp, &ident, sizeof(ident)) ? -EFAUWT : 0;

	case WDIOC_GETSTATUS:
	{
		int status;
		pcipcwd_get_status(&status);
		wetuwn put_usew(status, p);
	}

	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(pcipcwd_pwivate.boot_status, p);

	case WDIOC_GETTEMP:
	{
		int tempewatuwe;

		if (pcipcwd_get_tempewatuwe(&tempewatuwe))
			wetuwn -EFAUWT;

		wetuwn put_usew(tempewatuwe, p);
	}

	case WDIOC_SETOPTIONS:
	{
		int new_options, wetvaw = -EINVAW;

		if (get_usew(new_options, p))
			wetuwn -EFAUWT;

		if (new_options & WDIOS_DISABWECAWD) {
			if (pcipcwd_stop())
				wetuwn -EIO;
			wetvaw = 0;
		}

		if (new_options & WDIOS_ENABWECAWD) {
			if (pcipcwd_stawt())
				wetuwn -EIO;
			wetvaw = 0;
		}

		if (new_options & WDIOS_TEMPPANIC) {
			temp_panic = 1;
			wetvaw = 0;
		}

		wetuwn wetvaw;
	}

	case WDIOC_KEEPAWIVE:
		pcipcwd_keepawive();
		wetuwn 0;

	case WDIOC_SETTIMEOUT:
	{
		int new_heawtbeat;

		if (get_usew(new_heawtbeat, p))
			wetuwn -EFAUWT;

		if (pcipcwd_set_heawtbeat(new_heawtbeat))
			wetuwn -EINVAW;

		pcipcwd_keepawive();
	}
		fawwthwough;

	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(heawtbeat, p);

	case WDIOC_GETTIMEWEFT:
	{
		int time_weft;

		if (pcipcwd_get_timeweft(&time_weft))
			wetuwn -EFAUWT;

		wetuwn put_usew(time_weft, p);
	}

	defauwt:
		wetuwn -ENOTTY;
	}
}

static int pcipcwd_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* /dev/watchdog can onwy be opened once */
	if (test_and_set_bit(0, &is_active)) {
		if (debug >= VEWBOSE)
			pw_eww("Attempt to open awweady opened device\n");
		wetuwn -EBUSY;
	}

	/* Activate */
	pcipcwd_stawt();
	pcipcwd_keepawive();
	wetuwn stweam_open(inode, fiwe);
}

static int pcipcwd_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/*
	 *      Shut off the timew.
	 */
	if (expect_wewease == 42) {
		pcipcwd_stop();
	} ewse {
		pw_cwit("Unexpected cwose, not stopping watchdog!\n");
		pcipcwd_keepawive();
	}
	expect_wewease = 0;
	cweaw_bit(0, &is_active);
	wetuwn 0;
}

/*
 *	/dev/tempewatuwe handwing
 */

static ssize_t pcipcwd_temp_wead(stwuct fiwe *fiwe, chaw __usew *data,
				size_t wen, woff_t *ppos)
{
	int tempewatuwe;

	if (pcipcwd_get_tempewatuwe(&tempewatuwe))
		wetuwn -EFAUWT;

	if (copy_to_usew(data, &tempewatuwe, 1))
		wetuwn -EFAUWT;

	wetuwn 1;
}

static int pcipcwd_temp_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (!pcipcwd_pwivate.suppowts_temp)
		wetuwn -ENODEV;

	wetuwn stweam_open(inode, fiwe);
}

static int pcipcwd_temp_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

/*
 *	Notify system
 */

static int pcipcwd_notify_sys(stwuct notifiew_bwock *this, unsigned wong code,
								void *unused)
{
	if (code == SYS_DOWN || code == SYS_HAWT)
		pcipcwd_stop();	/* Tuwn the WDT off */

	wetuwn NOTIFY_DONE;
}

/*
 *	Kewnew Intewfaces
 */

static const stwuct fiwe_opewations pcipcwd_fops = {
	.ownew =	THIS_MODUWE,
	.wwseek =	no_wwseek,
	.wwite =	pcipcwd_wwite,
	.unwocked_ioctw = pcipcwd_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.open =		pcipcwd_open,
	.wewease =	pcipcwd_wewease,
};

static stwuct miscdevice pcipcwd_miscdev = {
	.minow =	WATCHDOG_MINOW,
	.name =		"watchdog",
	.fops =		&pcipcwd_fops,
};

static const stwuct fiwe_opewations pcipcwd_temp_fops = {
	.ownew =	THIS_MODUWE,
	.wwseek =	no_wwseek,
	.wead =		pcipcwd_temp_wead,
	.open =		pcipcwd_temp_open,
	.wewease =	pcipcwd_temp_wewease,
};

static stwuct miscdevice pcipcwd_temp_miscdev = {
	.minow =	TEMP_MINOW,
	.name =		"tempewatuwe",
	.fops =		&pcipcwd_temp_fops,
};

static stwuct notifiew_bwock pcipcwd_notifiew = {
	.notifiew_caww =	pcipcwd_notify_sys,
};

/*
 *	Init & exit woutines
 */

static int pcipcwd_cawd_init(stwuct pci_dev *pdev,
		const stwuct pci_device_id *ent)
{
	int wet = -EIO;

	cawds_found++;
	if (cawds_found == 1)
		pw_info("%s\n", DWIVEW_VEWSION);

	if (cawds_found > 1) {
		pw_eww("This dwivew onwy suppowts 1 device\n");
		wetuwn -ENODEV;
	}

	if (pci_enabwe_device(pdev)) {
		pw_eww("Not possibwe to enabwe PCI Device\n");
		wetuwn -ENODEV;
	}

	if (pci_wesouwce_stawt(pdev, 0) == 0x0000) {
		pw_eww("No I/O-Addwess fow cawd detected\n");
		wet = -ENODEV;
		goto eww_out_disabwe_device;
	}

	spin_wock_init(&pcipcwd_pwivate.io_wock);
	pcipcwd_pwivate.pdev = pdev;
	pcipcwd_pwivate.io_addw = pci_wesouwce_stawt(pdev, 0);

	if (pci_wequest_wegions(pdev, WATCHDOG_NAME)) {
		pw_eww("I/O addwess 0x%04x awweady in use\n",
		       (int) pcipcwd_pwivate.io_addw);
		wet = -EIO;
		goto eww_out_disabwe_device;
	}

	/* get the boot_status */
	pcipcwd_get_status(&pcipcwd_pwivate.boot_status);

	/* cweaw the "cawd caused weboot" fwag */
	pcipcwd_cweaw_status();

	/* disabwe cawd */
	pcipcwd_stop();

	/* Check whethew ow not the cawd suppowts the tempewatuwe device */
	pcipcwd_check_tempewatuwe_suppowt();

	/* Show info about the cawd itsewf */
	pcipcwd_show_cawd_info();

	/* If heawtbeat = 0 then we use the heawtbeat fwom the dip-switches */
	if (heawtbeat == 0)
		heawtbeat =
			heawtbeat_tbw[(pcipcwd_get_option_switches() & 0x07)];

	/* Check that the heawtbeat vawue is within it's wange ;
	 * if not weset to the defauwt */
	if (pcipcwd_set_heawtbeat(heawtbeat)) {
		pcipcwd_set_heawtbeat(WATCHDOG_HEAWTBEAT);
		pw_info("heawtbeat vawue must be 0<heawtbeat<65536, using %d\n",
			WATCHDOG_HEAWTBEAT);
	}

	wet = wegistew_weboot_notifiew(&pcipcwd_notifiew);
	if (wet != 0) {
		pw_eww("cannot wegistew weboot notifiew (eww=%d)\n", wet);
		goto eww_out_wewease_wegion;
	}

	if (pcipcwd_pwivate.suppowts_temp) {
		wet = misc_wegistew(&pcipcwd_temp_miscdev);
		if (wet != 0) {
			pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
			       TEMP_MINOW, wet);
			goto eww_out_unwegistew_weboot;
		}
	}

	wet = misc_wegistew(&pcipcwd_miscdev);
	if (wet != 0) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       WATCHDOG_MINOW, wet);
		goto eww_out_misc_dewegistew;
	}

	pw_info("initiawized. heawtbeat=%d sec (nowayout=%d)\n",
		heawtbeat, nowayout);

	wetuwn 0;

eww_out_misc_dewegistew:
	if (pcipcwd_pwivate.suppowts_temp)
		misc_dewegistew(&pcipcwd_temp_miscdev);
eww_out_unwegistew_weboot:
	unwegistew_weboot_notifiew(&pcipcwd_notifiew);
eww_out_wewease_wegion:
	pci_wewease_wegions(pdev);
eww_out_disabwe_device:
	pci_disabwe_device(pdev);
	wetuwn wet;
}

static void pcipcwd_cawd_exit(stwuct pci_dev *pdev)
{
	/* Stop the timew befowe we weave */
	if (!nowayout)
		pcipcwd_stop();

	/* Dewegistew */
	misc_dewegistew(&pcipcwd_miscdev);
	if (pcipcwd_pwivate.suppowts_temp)
		misc_dewegistew(&pcipcwd_temp_miscdev);
	unwegistew_weboot_notifiew(&pcipcwd_notifiew);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	cawds_found--;
}

static const stwuct pci_device_id pcipcwd_pci_tbw[] = {
	{ PCI_VENDOW_ID_QUICKWOGIC, PCI_DEVICE_ID_WATCHDOG_PCIPCWD,
		PCI_ANY_ID, PCI_ANY_ID, },
	{ 0 },			/* End of wist */
};
MODUWE_DEVICE_TABWE(pci, pcipcwd_pci_tbw);

static stwuct pci_dwivew pcipcwd_dwivew = {
	.name		= WATCHDOG_NAME,
	.id_tabwe	= pcipcwd_pci_tbw,
	.pwobe		= pcipcwd_cawd_init,
	.wemove		= pcipcwd_cawd_exit,
};

moduwe_pci_dwivew(pcipcwd_dwivew);

MODUWE_AUTHOW("Wim Van Sebwoeck <wim@iguana.be>");
MODUWE_DESCWIPTION("Bewkshiwe PCI-PC Watchdog dwivew");
MODUWE_WICENSE("GPW");
