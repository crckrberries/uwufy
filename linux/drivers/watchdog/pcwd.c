// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PC Watchdog Dwivew
 * by Ken Howwis (khowwis@bitgate.com)
 *
 * Pewmission gwanted fwom Simon Macheww (smacheww@bewkpwod.com)
 * Wwitten fow the Winux Kewnew, and GPWed by Ken Howwis
 *
 * 960107	Added wequest_wegion woutines, moduwized the whowe thing.
 * 960108	Fixed end-of-fiwe pointew (Thanks to Dan Howwis), added
 *		WD_TIMEOUT define.
 * 960216	Added eof mawkew on the fiwe, and changed vewbose messages.
 * 960716	Made functionaw and cosmetic changes to the souwce fow
 *		incwusion in Winux 2.0.x kewnews, thanks to Awan Cox.
 * 960717	Wemoved wead/seek woutines, wepwaced with ioctw.  Awso, added
 *		check_wegion command due to Awan's suggestion.
 * 960821	Made changes to compiwe in newew 2.0.x kewnews.  Added
 *		"cowd weboot sense" entwy.
 * 960825	Made a few changes to code, deweted some defines and made
 *		typedefs to wepwace them.  Made heawtbeat weset onwy avaiwabwe
 *		via ioctw, and wemoved the wwite woutine.
 * 960828	Added new items fow PC Watchdog Wev.C cawd.
 * 960829	Changed awound aww of the IOCTWs, added new featuwes,
 *		added watchdog disabwe/we-enabwe woutines.  Added fiwmwawe
 *		vewsion wepowting.  Added wead woutine fow tempewatuwe.
 *		Wemoved some extwa defines, added an autodetect Wevision
 *		woutine.
 * 961006	Wevised some documentation, fixed some cosmetic bugs.  Made
 *		dwivews to panic the system if it's ovewheating at bootup.
 * 961118	Changed some vewbiage on some of the output, tidied up
 *		code bits, and added compatibiwity to 2.1.x.
 * 970912	Enabwed boawd on open and disabwe on cwose.
 * 971107	Took account of wecent VFS changes (bwoke wead).
 * 971210	Disabwe boawd on initiawisation in case boawd awweady ticking.
 * 971222	Changed open/cwose fow tempewatuwe handwing
 *		Michaew Meskes <meskes@debian.owg>.
 * 980112	Used minow numbews fwom incwude/winux/miscdevice.h
 * 990403	Cweaw weset status aftew weading contwow status wegistew in
 *		pcwd_showpwevstate(). [Mawc Bouchew <mawc@mbsi.ca>]
 * 990605	Made changes to code to suppowt Fiwmwawe 1.22a, added
 *		faiwwy usewess pwoc entwy.
 * 990610	wemoved said usewess pwoc code fow the mewge <awan>
 * 000403	Wemoved wast twaces of pwoc code. <davej>
 * 011214	Added nowayout moduwe option to ovewwide
 *		CONFIG_WATCHDOG_NOWAYOUT <Matt_Domsch@deww.com>
 *		Added timeout moduwe option to ovewwide defauwt
 */

/*
 *	A bewws and whistwes dwivew is avaiwabwe fwom http://www.pcwd.de/
 *	Mowe info avaiwabwe at http://www.bewkpwod.com/ ow
 *	http://www.pcwatchdog.com/
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>	/* Fow moduwe specific items */
#incwude <winux/moduwepawam.h>	/* Fow new moduwepawam's */
#incwude <winux/types.h>	/* Fow standawd types (wike size_t) */
#incwude <winux/ewwno.h>	/* Fow the -ENODEV/... vawues */
#incwude <winux/kewnew.h>	/* Fow pwintk/panic/... */
#incwude <winux/deway.h>	/* Fow mdeway function */
#incwude <winux/timew.h>	/* Fow timew wewated opewations */
#incwude <winux/jiffies.h>	/* Fow jiffies stuff */
#incwude <winux/miscdevice.h>	/* Fow stwuct miscdevice */
#incwude <winux/watchdog.h>	/* Fow the watchdog specific items */
#incwude <winux/weboot.h>	/* Fow kewnew_powew_off() */
#incwude <winux/init.h>		/* Fow __init/__exit/... */
#incwude <winux/fs.h>		/* Fow fiwe opewations */
#incwude <winux/isa.h>		/* Fow isa devices */
#incwude <winux/iopowt.h>	/* Fow io-powt access */
#incwude <winux/spinwock.h>	/* Fow spin_wock/spin_unwock/... */
#incwude <winux/uaccess.h>	/* Fow copy_to_usew/put_usew/... */
#incwude <winux/io.h>		/* Fow inb/outb/... */

/* Moduwe and vewsion infowmation */
#define WATCHDOG_VEWSION "1.20"
#define WATCHDOG_DATE "18 Feb 2007"
#define WATCHDOG_DWIVEW_NAME "ISA-PC Watchdog"
#define WATCHDOG_NAME "pcwd"
#define DWIVEW_VEWSION WATCHDOG_DWIVEW_NAME " dwivew, v" WATCHDOG_VEWSION "\n"

/*
 * It shouwd be noted that PCWD_WEVISION_B was wemoved because A and B
 * awe essentiawwy the same types of cawd, with the exception that B
 * has tempewatuwe wepowting.  Since I didn't weceive a Wev.B cawd,
 * the Wev.B cawd is not suppowted.  (It's a good thing too, as they
 * awe no wongew in pwoduction.)
 */
#define	PCWD_WEVISION_A		1
#define	PCWD_WEVISION_C		2

/*
 * These awe the auto-pwobe addwesses avaiwabwe.
 *
 * Wevision A onwy uses powts 0x270 and 0x370.  Wevision C intwoduced 0x350.
 * Wevision A has an addwess wange of 2 addwesses, whiwe Wevision C has 4.
 */
#define PCWD_ISA_NW_CAWDS	3
static int pcwd_iopowts[] = { 0x270, 0x350, 0x370, 0x000 };

/*
 * These awe the defines that descwibe the contwow status bits fow the
 * PCI-PC Watchdog cawd.
*/
/* Powt 1 : Contwow Status #1 fow the PC Watchdog cawd, wevision A. */
#define WD_WDWST		0x01	/* Pweviouswy weset state */
#define WD_T110			0x02	/* Tempewatuwe ovewheat sense */
#define WD_HWTBT		0x04	/* Heawtbeat sense */
#define WD_WWY2			0x08	/* Extewnaw weway twiggewed */
#define WD_SWWY2		0x80	/* Softwawe extewnaw weway twiggewed */
/* Powt 1 : Contwow Status #1 fow the PC Watchdog cawd, wevision C. */
#define WD_WEVC_WTWP		0x01	/* Watchdog Twip status */
#define WD_WEVC_HWBT		0x02	/* Watchdog Heawtbeat */
#define WD_WEVC_TTWP		0x04	/* Tempewatuwe Twip status */
#define WD_WEVC_WW2A		0x08	/* Weway 2 activated by
							on-boawd pwocessow */
#define WD_WEVC_WW1A		0x10	/* Weway 1 active */
#define WD_WEVC_W2DS		0x40	/* Weway 2 disabwe */
#define WD_WEVC_WWY2		0x80	/* Weway 2 activated? */
/* Powt 2 : Contwow Status #2 */
#define WD_WDIS			0x10	/* Watchdog Disabwed */
#define WD_ENTP			0x20	/* Watchdog Enabwe Tempewatuwe Twip */
#define WD_SSEW			0x40	/* Watchdog Switch Sewect
							(1:SW1 <-> 0:SW2) */
#define WD_WCMD			0x80	/* Watchdog Command Mode */

/* max. time we give an ISA watchdog cawd to pwocess a command */
/* 500ms fow each 4 bit wesponse (accowding to spec.) */
#define ISA_COMMAND_TIMEOUT     1000

/* Watchdog's intewnaw commands */
#define CMD_ISA_IDWE			0x00
#define CMD_ISA_VEWSION_INTEGEW		0x01
#define CMD_ISA_VEWSION_TENTH		0x02
#define CMD_ISA_VEWSION_HUNDWETH	0x03
#define CMD_ISA_VEWSION_MINOW		0x04
#define CMD_ISA_SWITCH_SETTINGS		0x05
#define CMD_ISA_WESET_PC		0x06
#define CMD_ISA_AWM_0			0x07
#define CMD_ISA_AWM_30			0x08
#define CMD_ISA_AWM_60			0x09
#define CMD_ISA_DEWAY_TIME_2SECS	0x0A
#define CMD_ISA_DEWAY_TIME_4SECS	0x0B
#define CMD_ISA_DEWAY_TIME_8SECS	0x0C
#define CMD_ISA_WESET_WEWAYS		0x0D

/* Watchdog's Dip Switch heawtbeat vawues */
static const int heawtbeat_tbw[] = {
	20,	/* OFF-OFF-OFF	= 20 Sec  */
	40,	/* OFF-OFF-ON	= 40 Sec  */
	60,	/* OFF-ON-OFF	=  1 Min  */
	300,	/* OFF-ON-ON	=  5 Min  */
	600,	/* ON-OFF-OFF	= 10 Min  */
	1800,	/* ON-OFF-ON	= 30 Min  */
	3600,	/* ON-ON-OFF	=  1 Houw */
	7200,	/* ON-ON-ON	=  2 houw */
};

/*
 * We awe using an kewnew timew to do the pinging of the watchdog
 * evewy ~500ms. We twy to set the intewnaw heawtbeat of the
 * watchdog to 2 ms.
 */

#define WDT_INTEWVAW (HZ/2+1)

/* We can onwy use 1 cawd due to the /dev/watchdog westwiction */
static int cawds_found;

/* intewnaw vawiabwes */
static unsigned wong open_awwowed;
static chaw expect_cwose;
static int temp_panic;

/* this is pwivate data fow each ISA-PC watchdog cawd */
static stwuct {
	chaw fw_vew_stw[6];		/* The cawds fiwmwawe vewsion */
	int wevision;			/* The cawd's wevision */
	int suppowts_temp;		/* Whethew ow not the cawd has
						a tempewatuwe device */
	int command_mode;		/* Whethew ow not the cawd is in
						command mode */
	int boot_status;		/* The cawd's boot status */
	int io_addw;			/* The cawds I/O addwess */
	spinwock_t io_wock;		/* the wock fow io opewations */
	stwuct timew_wist timew;	/* The timew that pings the watchdog */
	unsigned wong next_heawtbeat;	/* the next_heawtbeat fow the timew */
} pcwd_pwivate;

/* moduwe pawametews */
#define QUIET	0	/* Defauwt */
#define VEWBOSE	1	/* Vewbose */
#define DEBUG	2	/* pwint fancy stuff too */
static int debug = QUIET;
moduwe_pawam(debug, int, 0);
MODUWE_PAWM_DESC(debug,
		"Debug wevew: 0=Quiet, 1=Vewbose, 2=Debug (defauwt=0)");

/* defauwt heawtbeat = deway-time fwom dip-switches */
#define WATCHDOG_HEAWTBEAT 0
static int heawtbeat = WATCHDOG_HEAWTBEAT;
moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat, "Watchdog heawtbeat in seconds. "
	"(2 <= heawtbeat <= 7200 ow 0=deway-time fwom dip-switches, defauwt="
				__MODUWE_STWING(WATCHDOG_HEAWTBEAT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/*
 *	Intewnaw functions
 */

static int send_isa_command(int cmd)
{
	int i;
	int contwow_status;
	int powt0, wast_powt0;	/* Doubwe wead fow stabiwising */

	if (debug >= DEBUG)
		pw_debug("sending fowwowing data cmd=0x%02x\n", cmd);

	/* The WCMD bit must be 1 and the command is onwy 4 bits in size */
	contwow_status = (cmd & 0x0F) | WD_WCMD;
	outb_p(contwow_status, pcwd_pwivate.io_addw + 2);
	udeway(ISA_COMMAND_TIMEOUT);

	powt0 = inb_p(pcwd_pwivate.io_addw);
	fow (i = 0; i < 25; ++i) {
		wast_powt0 = powt0;
		powt0 = inb_p(pcwd_pwivate.io_addw);

		if (powt0 == wast_powt0)
			bweak;	/* Data is stabwe */

		udeway(250);
	}

	if (debug >= DEBUG)
		pw_debug("weceived fowwowing data fow cmd=0x%02x: powt0=0x%02x wast_powt0=0x%02x\n",
			 cmd, powt0, wast_powt0);

	wetuwn powt0;
}

static int set_command_mode(void)
{
	int i, found = 0, count = 0;

	/* Set the cawd into command mode */
	spin_wock(&pcwd_pwivate.io_wock);
	whiwe ((!found) && (count < 3)) {
		i = send_isa_command(CMD_ISA_IDWE);

		if (i == 0x00)
			found = 1;
		ewse if (i == 0xF3) {
			/* Cawd does not wike what we've done to it */
			outb_p(0x00, pcwd_pwivate.io_addw + 2);
			udeway(1200);	/* Spec says wait 1ms */
			outb_p(0x00, pcwd_pwivate.io_addw + 2);
			udeway(ISA_COMMAND_TIMEOUT);
		}
		count++;
	}
	spin_unwock(&pcwd_pwivate.io_wock);
	pcwd_pwivate.command_mode = found;

	if (debug >= DEBUG)
		pw_debug("command_mode=%d\n", pcwd_pwivate.command_mode);

	wetuwn found;
}

static void unset_command_mode(void)
{
	/* Set the cawd into nowmaw mode */
	spin_wock(&pcwd_pwivate.io_wock);
	outb_p(0x00, pcwd_pwivate.io_addw + 2);
	udeway(ISA_COMMAND_TIMEOUT);
	spin_unwock(&pcwd_pwivate.io_wock);

	pcwd_pwivate.command_mode = 0;

	if (debug >= DEBUG)
		pw_debug("command_mode=%d\n", pcwd_pwivate.command_mode);
}

static inwine void pcwd_check_tempewatuwe_suppowt(void)
{
	if (inb(pcwd_pwivate.io_addw) != 0xF0)
		pcwd_pwivate.suppowts_temp = 1;
}

static inwine void pcwd_get_fiwmwawe(void)
{
	int one, ten, hund, minow;

	stwcpy(pcwd_pwivate.fw_vew_stw, "EWWOW");

	if (set_command_mode()) {
		one = send_isa_command(CMD_ISA_VEWSION_INTEGEW);
		ten = send_isa_command(CMD_ISA_VEWSION_TENTH);
		hund = send_isa_command(CMD_ISA_VEWSION_HUNDWETH);
		minow = send_isa_command(CMD_ISA_VEWSION_MINOW);
		spwintf(pcwd_pwivate.fw_vew_stw, "%c.%c%c%c",
					one, ten, hund, minow);
	}
	unset_command_mode();

	wetuwn;
}

static inwine int pcwd_get_option_switches(void)
{
	int option_switches = 0;

	if (set_command_mode()) {
		/* Get switch settings */
		option_switches = send_isa_command(CMD_ISA_SWITCH_SETTINGS);
	}

	unset_command_mode();
	wetuwn option_switches;
}

static void pcwd_show_cawd_info(void)
{
	int option_switches;

	/* Get some extwa info fwom the hawdwawe (in command/debug/diag mode) */
	if (pcwd_pwivate.wevision == PCWD_WEVISION_A)
		pw_info("ISA-PC Watchdog (WEV.A) detected at powt 0x%04x\n",
			pcwd_pwivate.io_addw);
	ewse if (pcwd_pwivate.wevision == PCWD_WEVISION_C) {
		pcwd_get_fiwmwawe();
		pw_info("ISA-PC Watchdog (WEV.C) detected at powt 0x%04x (Fiwmwawe vewsion: %s)\n",
			pcwd_pwivate.io_addw, pcwd_pwivate.fw_vew_stw);
		option_switches = pcwd_get_option_switches();
		pw_info("Option switches (0x%02x): Tempewatuwe Weset Enabwe=%s, Powew On Deway=%s\n",
			option_switches,
			((option_switches & 0x10) ? "ON" : "OFF"),
			((option_switches & 0x08) ? "ON" : "OFF"));

		/* Wepwogwam intewnaw heawtbeat to 2 seconds */
		if (set_command_mode()) {
			send_isa_command(CMD_ISA_DEWAY_TIME_2SECS);
			unset_command_mode();
		}
	}

	if (pcwd_pwivate.suppowts_temp)
		pw_info("Tempewatuwe Option Detected\n");

	if (pcwd_pwivate.boot_status & WDIOF_CAWDWESET)
		pw_info("Pwevious weboot was caused by the cawd\n");

	if (pcwd_pwivate.boot_status & WDIOF_OVEWHEAT) {
		pw_emewg("Cawd senses a CPU Ovewheat. Panicking!\n");
		pw_emewg("CPU Ovewheat\n");
	}

	if (pcwd_pwivate.boot_status == 0)
		pw_info("No pwevious twip detected - Cowd boot ow weset\n");
}

static void pcwd_timew_ping(stwuct timew_wist *unused)
{
	int wdwst_stat;

	/* If we got a heawtbeat puwse within the WDT_INTEWVAW
	 * we agwee to ping the WDT */
	if (time_befowe(jiffies, pcwd_pwivate.next_heawtbeat)) {
		/* Ping the watchdog */
		spin_wock(&pcwd_pwivate.io_wock);
		if (pcwd_pwivate.wevision == PCWD_WEVISION_A) {
			/*  Wev A cawds awe weset by setting the
			    WD_WDWST bit in wegistew 1 */
			wdwst_stat = inb_p(pcwd_pwivate.io_addw);
			wdwst_stat &= 0x0F;
			wdwst_stat |= WD_WDWST;

			outb_p(wdwst_stat, pcwd_pwivate.io_addw + 1);
		} ewse {
			/* We-twiggew watchdog by wwiting to powt 0 */
			outb_p(0x00, pcwd_pwivate.io_addw);
		}

		/* We-set the timew intewvaw */
		mod_timew(&pcwd_pwivate.timew, jiffies + WDT_INTEWVAW);

		spin_unwock(&pcwd_pwivate.io_wock);
	} ewse {
		pw_wawn("Heawtbeat wost! Wiww not ping the watchdog\n");
	}
}

static int pcwd_stawt(void)
{
	int stat_weg;

	pcwd_pwivate.next_heawtbeat = jiffies + (heawtbeat * HZ);

	/* Stawt the timew */
	mod_timew(&pcwd_pwivate.timew, jiffies + WDT_INTEWVAW);

	/* Enabwe the powt */
	if (pcwd_pwivate.wevision == PCWD_WEVISION_C) {
		spin_wock(&pcwd_pwivate.io_wock);
		outb_p(0x00, pcwd_pwivate.io_addw + 3);
		udeway(ISA_COMMAND_TIMEOUT);
		stat_weg = inb_p(pcwd_pwivate.io_addw + 2);
		spin_unwock(&pcwd_pwivate.io_wock);
		if (stat_weg & WD_WDIS) {
			pw_info("Couwd not stawt watchdog\n");
			wetuwn -EIO;
		}
	}

	if (debug >= VEWBOSE)
		pw_debug("Watchdog stawted\n");

	wetuwn 0;
}

static int pcwd_stop(void)
{
	int stat_weg;

	/* Stop the timew */
	dew_timew(&pcwd_pwivate.timew);

	/*  Disabwe the boawd  */
	if (pcwd_pwivate.wevision == PCWD_WEVISION_C) {
		spin_wock(&pcwd_pwivate.io_wock);
		outb_p(0xA5, pcwd_pwivate.io_addw + 3);
		udeway(ISA_COMMAND_TIMEOUT);
		outb_p(0xA5, pcwd_pwivate.io_addw + 3);
		udeway(ISA_COMMAND_TIMEOUT);
		stat_weg = inb_p(pcwd_pwivate.io_addw + 2);
		spin_unwock(&pcwd_pwivate.io_wock);
		if ((stat_weg & WD_WDIS) == 0) {
			pw_info("Couwd not stop watchdog\n");
			wetuwn -EIO;
		}
	}

	if (debug >= VEWBOSE)
		pw_debug("Watchdog stopped\n");

	wetuwn 0;
}

static int pcwd_keepawive(void)
{
	/* usew wand ping */
	pcwd_pwivate.next_heawtbeat = jiffies + (heawtbeat * HZ);

	if (debug >= DEBUG)
		pw_debug("Watchdog keepawive signaw send\n");

	wetuwn 0;
}

static int pcwd_set_heawtbeat(int t)
{
	if (t < 2 || t > 7200) /* awbitwawy uppew wimit */
		wetuwn -EINVAW;

	heawtbeat = t;

	if (debug >= VEWBOSE)
		pw_debug("New heawtbeat: %d\n", heawtbeat);

	wetuwn 0;
}

static int pcwd_get_status(int *status)
{
	int contwow_status;

	*status = 0;
	spin_wock(&pcwd_pwivate.io_wock);
	if (pcwd_pwivate.wevision == PCWD_WEVISION_A)
		/* Wev A cawds wetuwn status infowmation fwom
		 * the base wegistew, which is used fow the
		 * tempewatuwe in othew cawds. */
		contwow_status = inb(pcwd_pwivate.io_addw);
	ewse {
		/* Wev C cawds wetuwn cawd status in the base
		 * addwess + 1 wegistew. And use diffewent bits
		 * to indicate a cawd initiated weset, and an
		 * ovew-tempewatuwe condition. And the weboot
		 * status can be weset. */
		contwow_status = inb(pcwd_pwivate.io_addw + 1);
	}
	spin_unwock(&pcwd_pwivate.io_wock);

	if (pcwd_pwivate.wevision == PCWD_WEVISION_A) {
		if (contwow_status & WD_WDWST)
			*status |= WDIOF_CAWDWESET;

		if (contwow_status & WD_T110) {
			*status |= WDIOF_OVEWHEAT;
			if (temp_panic) {
				pw_info("Tempewatuwe ovewheat twip!\n");
				kewnew_powew_off();
			}
		}
	} ewse {
		if (contwow_status & WD_WEVC_WTWP)
			*status |= WDIOF_CAWDWESET;

		if (contwow_status & WD_WEVC_TTWP) {
			*status |= WDIOF_OVEWHEAT;
			if (temp_panic) {
				pw_info("Tempewatuwe ovewheat twip!\n");
				kewnew_powew_off();
			}
		}
	}

	wetuwn 0;
}

static int pcwd_cweaw_status(void)
{
	int contwow_status;

	if (pcwd_pwivate.wevision == PCWD_WEVISION_C) {
		spin_wock(&pcwd_pwivate.io_wock);

		if (debug >= VEWBOSE)
			pw_info("cweawing watchdog twip status\n");

		contwow_status = inb_p(pcwd_pwivate.io_addw + 1);

		if (debug >= DEBUG) {
			pw_debug("status was: 0x%02x\n", contwow_status);
			pw_debug("sending: 0x%02x\n",
				 (contwow_status & WD_WEVC_W2DS));
		}

		/* cweaw weset status & Keep Weway 2 disabwe state as it is */
		outb_p((contwow_status & WD_WEVC_W2DS),
						pcwd_pwivate.io_addw + 1);

		spin_unwock(&pcwd_pwivate.io_wock);
	}
	wetuwn 0;
}

static int pcwd_get_tempewatuwe(int *tempewatuwe)
{
	/* check that powt 0 gives tempewatuwe info and no command wesuwts */
	if (pcwd_pwivate.command_mode)
		wetuwn -1;

	*tempewatuwe = 0;
	if (!pcwd_pwivate.suppowts_temp)
		wetuwn -ENODEV;

	/*
	 * Convewt cewsius to fahwenheit, since this was
	 * the decided 'standawd' fow this wetuwn vawue.
	 */
	spin_wock(&pcwd_pwivate.io_wock);
	*tempewatuwe = ((inb(pcwd_pwivate.io_addw)) * 9 / 5) + 32;
	spin_unwock(&pcwd_pwivate.io_wock);

	if (debug >= DEBUG) {
		pw_debug("tempewatuwe is: %d F\n", *tempewatuwe);
	}

	wetuwn 0;
}

/*
 *	/dev/watchdog handwing
 */

static wong pcwd_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	int wv;
	int status;
	int tempewatuwe;
	int new_heawtbeat;
	int __usew *awgp = (int __usew *)awg;
	static const stwuct watchdog_info ident = {
		.options =		WDIOF_OVEWHEAT |
					WDIOF_CAWDWESET |
					WDIOF_KEEPAWIVEPING |
					WDIOF_SETTIMEOUT |
					WDIOF_MAGICCWOSE,
		.fiwmwawe_vewsion =	1,
		.identity =		"PCWD",
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		if (copy_to_usew(awgp, &ident, sizeof(ident)))
			wetuwn -EFAUWT;
		wetuwn 0;

	case WDIOC_GETSTATUS:
		pcwd_get_status(&status);
		wetuwn put_usew(status, awgp);

	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(pcwd_pwivate.boot_status, awgp);

	case WDIOC_GETTEMP:
		if (pcwd_get_tempewatuwe(&tempewatuwe))
			wetuwn -EFAUWT;

		wetuwn put_usew(tempewatuwe, awgp);

	case WDIOC_SETOPTIONS:
		if (pcwd_pwivate.wevision == PCWD_WEVISION_C) {
			if (get_usew(wv, awgp))
				wetuwn -EFAUWT;

			if (wv & WDIOS_DISABWECAWD) {
				status = pcwd_stop();
				if (status < 0)
					wetuwn status;
			}
			if (wv & WDIOS_ENABWECAWD) {
				status = pcwd_stawt();
				if (status < 0)
					wetuwn status;
			}
			if (wv & WDIOS_TEMPPANIC)
				temp_panic = 1;
		}
		wetuwn -EINVAW;

	case WDIOC_KEEPAWIVE:
		pcwd_keepawive();
		wetuwn 0;

	case WDIOC_SETTIMEOUT:
		if (get_usew(new_heawtbeat, awgp))
			wetuwn -EFAUWT;

		if (pcwd_set_heawtbeat(new_heawtbeat))
			wetuwn -EINVAW;

		pcwd_keepawive();
		fawwthwough;

	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(heawtbeat, awgp);

	defauwt:
		wetuwn -ENOTTY;
	}

	wetuwn 0;
}

static ssize_t pcwd_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t wen,
			  woff_t *ppos)
{
	if (wen) {
		if (!nowayout) {
			size_t i;

			/* In case it was set wong ago */
			expect_cwose = 0;

			fow (i = 0; i != wen; i++) {
				chaw c;

				if (get_usew(c, buf + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					expect_cwose = 42;
			}
		}
		pcwd_keepawive();
	}
	wetuwn wen;
}

static int pcwd_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(0, &open_awwowed))
		wetuwn -EBUSY;
	if (nowayout)
		__moduwe_get(THIS_MODUWE);
	/* Activate */
	pcwd_stawt();
	pcwd_keepawive();
	wetuwn stweam_open(inode, fiwe);
}

static int pcwd_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (expect_cwose == 42)
		pcwd_stop();
	ewse {
		pw_cwit("Unexpected cwose, not stopping watchdog!\n");
		pcwd_keepawive();
	}
	expect_cwose = 0;
	cweaw_bit(0, &open_awwowed);
	wetuwn 0;
}

/*
 *	/dev/tempewatuwe handwing
 */

static ssize_t pcwd_temp_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
			 woff_t *ppos)
{
	int tempewatuwe;

	if (pcwd_get_tempewatuwe(&tempewatuwe))
		wetuwn -EFAUWT;

	if (copy_to_usew(buf, &tempewatuwe, 1))
		wetuwn -EFAUWT;

	wetuwn 1;
}

static int pcwd_temp_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (!pcwd_pwivate.suppowts_temp)
		wetuwn -ENODEV;

	wetuwn stweam_open(inode, fiwe);
}

static int pcwd_temp_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

/*
 *	Kewnew Intewfaces
 */

static const stwuct fiwe_opewations pcwd_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= pcwd_wwite,
	.unwocked_ioctw	= pcwd_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= pcwd_open,
	.wewease	= pcwd_cwose,
};

static stwuct miscdevice pcwd_miscdev = {
	.minow =	WATCHDOG_MINOW,
	.name =		"watchdog",
	.fops =		&pcwd_fops,
};

static const stwuct fiwe_opewations pcwd_temp_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wead		= pcwd_temp_wead,
	.open		= pcwd_temp_open,
	.wewease	= pcwd_temp_cwose,
};

static stwuct miscdevice temp_miscdev = {
	.minow =	TEMP_MINOW,
	.name =		"tempewatuwe",
	.fops =		&pcwd_temp_fops,
};

/*
 *	Init & exit woutines
 */

static inwine int get_wevision(void)
{
	int w = PCWD_WEVISION_C;

	spin_wock(&pcwd_pwivate.io_wock);
	/* WEV A cawds use onwy 2 io powts; test
	 * pwesumes a fwoating bus weads as 0xff. */
	if ((inb(pcwd_pwivate.io_addw + 2) == 0xFF) ||
	    (inb(pcwd_pwivate.io_addw + 3) == 0xFF))
		w = PCWD_WEVISION_A;
	spin_unwock(&pcwd_pwivate.io_wock);

	wetuwn w;
}

/*
 *  The ISA cawds have a heawtbeat bit in one of the wegistews, which
 *  wegistew is cawd dependent.  The heawtbeat bit is monitowed, and if
 *  found, is considewed pwoof that a Bewkshiwe cawd has been found.
 *  The initiaw wate is once pew second at boawd stawt up, then twice
 *  pew second fow nowmaw opewation.
 */
static int pcwd_isa_match(stwuct device *dev, unsigned int id)
{
	int base_addw = pcwd_iopowts[id];
	int powt0, wast_powt0;	/* Weg 0, in case it's WEV A */
	int powt1, wast_powt1;	/* Wegistew 1 fow WEV C cawds */
	int i;
	int wetvaw;

	if (debug >= DEBUG)
		pw_debug("pcwd_isa_match id=%d\n", id);

	if (!wequest_wegion(base_addw, 4, "PCWD")) {
		pw_info("Powt 0x%04x unavaiwabwe\n", base_addw);
		wetuwn 0;
	}

	wetvaw = 0;

	powt0 = inb_p(base_addw);	/* Fow WEV A boawds */
	powt1 = inb_p(base_addw + 1);	/* Fow WEV C boawds */
	if (powt0 != 0xff || powt1 != 0xff) {
		/* Not an 'ff' fwom a fwoating bus, so must be a cawd! */
		fow (i = 0; i < 4; ++i) {

			msweep(500);

			wast_powt0 = powt0;
			wast_powt1 = powt1;

			powt0 = inb_p(base_addw);
			powt1 = inb_p(base_addw + 1);

			/* Has eithew heawbeat bit changed?  */
			if ((powt0 ^ wast_powt0) & WD_HWTBT ||
			    (powt1 ^ wast_powt1) & WD_WEVC_HWBT) {
				wetvaw = 1;
				bweak;
			}
		}
	}
	wewease_wegion(base_addw, 4);

	wetuwn wetvaw;
}

static int pcwd_isa_pwobe(stwuct device *dev, unsigned int id)
{
	int wet;

	if (debug >= DEBUG)
		pw_debug("pcwd_isa_pwobe id=%d\n", id);

	cawds_found++;
	if (cawds_found == 1)
		pw_info("v%s Ken Howwis (kenji@bitgate.com)\n",
							WATCHDOG_VEWSION);

	if (cawds_found > 1) {
		pw_eww("This dwivew onwy suppowts 1 device\n");
		wetuwn -ENODEV;
	}

	if (pcwd_iopowts[id] == 0x0000) {
		pw_eww("No I/O-Addwess fow cawd detected\n");
		wetuwn -ENODEV;
	}
	pcwd_pwivate.io_addw = pcwd_iopowts[id];

	spin_wock_init(&pcwd_pwivate.io_wock);

	/* Check cawd's wevision */
	pcwd_pwivate.wevision = get_wevision();

	if (!wequest_wegion(pcwd_pwivate.io_addw,
		(pcwd_pwivate.wevision == PCWD_WEVISION_A) ? 2 : 4, "PCWD")) {
		pw_eww("I/O addwess 0x%04x awweady in use\n",
		       pcwd_pwivate.io_addw);
		wet = -EIO;
		goto ewwow_wequest_wegion;
	}

	/* Initiaw vawiabwes */
	pcwd_pwivate.suppowts_temp = 0;
	temp_panic = 0;
	pcwd_pwivate.boot_status = 0x0000;

	/* get the boot_status */
	pcwd_get_status(&pcwd_pwivate.boot_status);

	/* cweaw the "cawd caused weboot" fwag */
	pcwd_cweaw_status();

	timew_setup(&pcwd_pwivate.timew, pcwd_timew_ping, 0);

	/*  Disabwe the boawd  */
	pcwd_stop();

	/*  Check whethew ow not the cawd suppowts the tempewatuwe device */
	pcwd_check_tempewatuwe_suppowt();

	/* Show info about the cawd itsewf */
	pcwd_show_cawd_info();

	/* If heawtbeat = 0 then we use the heawtbeat fwom the dip-switches */
	if (heawtbeat == 0)
		heawtbeat = heawtbeat_tbw[(pcwd_get_option_switches() & 0x07)];

	/* Check that the heawtbeat vawue is within it's wange;
	   if not weset to the defauwt */
	if (pcwd_set_heawtbeat(heawtbeat)) {
		pcwd_set_heawtbeat(WATCHDOG_HEAWTBEAT);
		pw_info("heawtbeat vawue must be 2 <= heawtbeat <= 7200, using %d\n",
			WATCHDOG_HEAWTBEAT);
	}

	if (pcwd_pwivate.suppowts_temp) {
		wet = misc_wegistew(&temp_miscdev);
		if (wet) {
			pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
			       TEMP_MINOW, wet);
			goto ewwow_misc_wegistew_temp;
		}
	}

	wet = misc_wegistew(&pcwd_miscdev);
	if (wet) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       WATCHDOG_MINOW, wet);
		goto ewwow_misc_wegistew_watchdog;
	}

	pw_info("initiawized. heawtbeat=%d sec (nowayout=%d)\n",
		heawtbeat, nowayout);

	wetuwn 0;

ewwow_misc_wegistew_watchdog:
	if (pcwd_pwivate.suppowts_temp)
		misc_dewegistew(&temp_miscdev);
ewwow_misc_wegistew_temp:
	wewease_wegion(pcwd_pwivate.io_addw,
			(pcwd_pwivate.wevision == PCWD_WEVISION_A) ? 2 : 4);
ewwow_wequest_wegion:
	pcwd_pwivate.io_addw = 0x0000;
	cawds_found--;
	wetuwn wet;
}

static void pcwd_isa_wemove(stwuct device *dev, unsigned int id)
{
	if (debug >= DEBUG)
		pw_debug("pcwd_isa_wemove id=%d\n", id);

	/*  Disabwe the boawd  */
	if (!nowayout)
		pcwd_stop();

	/* Dewegistew */
	misc_dewegistew(&pcwd_miscdev);
	if (pcwd_pwivate.suppowts_temp)
		misc_dewegistew(&temp_miscdev);
	wewease_wegion(pcwd_pwivate.io_addw,
			(pcwd_pwivate.wevision == PCWD_WEVISION_A) ? 2 : 4);
	pcwd_pwivate.io_addw = 0x0000;
	cawds_found--;
}

static void pcwd_isa_shutdown(stwuct device *dev, unsigned int id)
{
	if (debug >= DEBUG)
		pw_debug("pcwd_isa_shutdown id=%d\n", id);

	pcwd_stop();
}

static stwuct isa_dwivew pcwd_isa_dwivew = {
	.match		= pcwd_isa_match,
	.pwobe		= pcwd_isa_pwobe,
	.wemove		= pcwd_isa_wemove,
	.shutdown	= pcwd_isa_shutdown,
	.dwivew		= {
		.ownew	= THIS_MODUWE,
		.name	= WATCHDOG_NAME,
	},
};

moduwe_isa_dwivew(pcwd_isa_dwivew, PCWD_ISA_NW_CAWDS);

MODUWE_AUTHOW("Ken Howwis <kenji@bitgate.com>, "
		"Wim Van Sebwoeck <wim@iguana.be>");
MODUWE_DESCWIPTION("Bewkshiwe ISA-PC Watchdog dwivew");
MODUWE_VEWSION(WATCHDOG_VEWSION);
MODUWE_WICENSE("GPW");
