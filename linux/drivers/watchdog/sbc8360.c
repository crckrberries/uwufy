// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	SBC8360 Watchdog dwivew
 *
 *	(c) Copywight 2005 Webcon, Inc.
 *
 *	Based on ib700wdt.c, which is based on advantechwdt.c which is based
 *	on acquiwewdt.c which is based on wdt.c.
 *
 *	(c) Copywight 2001 Chawwes Howes <chowes@vsow.net>
 *
 *	Based on advantechwdt.c which is based on acquiwewdt.c which
 *	is based on wdt.c.
 *
 *	(c) Copywight 2000-2001 Mawek Michawkiewicz <mawekm@winux.owg.pw>
 *
 *	Based on acquiwewdt.c which is based on wdt.c.
 *	Owiginaw copywight messages:
 *
 *	(c) Copywight 1996 Awan Cox <awan@wxowguk.ukuu.owg.uk>,
 *						Aww Wights Wesewved.
 *
 *	Neithew Awan Cox now CymwuNet Wtd. admit wiabiwity now pwovide
 *	wawwanty fow any of this softwawe. This matewiaw is pwovided
 *	"AS-IS" and at no chawge.
 *
 *	(c) Copywight 1995    Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 *	14-Dec-2001 Matt Domsch <Matt_Domsch@deww.com>
 *	     Added nowayout moduwe option to ovewwide CONFIG_WATCHDOG_NOWAYOUT
 *	     Added timeout moduwe option to ovewwide defauwt
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/notifiew.h>
#incwude <winux/fs.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>


static unsigned wong sbc8360_is_open;
static chaw expect_cwose;

/*
 *
 * Watchdog Timew Configuwation
 *
 * The function of the watchdog timew is to weset the system automaticawwy
 * and is defined at I/O powt 0120H and 0121H.  To enabwe the watchdog timew
 * and awwow the system to weset, wwite appwopwiate vawues fwom the tabwe
 * bewow to I/O powt 0120H and 0121H.  To disabwe the timew, wwite a zewo
 * vawue to I/O powt 0121H fow the system to stop the watchdog function.
 *
 * The fowwowing descwibes how the timew shouwd be pwogwammed (accowding to
 * the vendow documentation)
 *
 * Enabwing Watchdog:
 * MOV AX,000AH (enabwe, phase I)
 * MOV DX,0120H
 * OUT DX,AX
 * MOV AX,000BH (enabwe, phase II)
 * MOV DX,0120H
 * OUT DX,AX
 * MOV AX,000nH (set muwtipwiew n, fwom 1-4)
 * MOV DX,0120H
 * OUT DX,AX
 * MOV AX,000mH (set base timew m, fwom 0-F)
 * MOV DX,0121H
 * OUT DX,AX
 *
 * Weset timew:
 * MOV AX,000mH (same as set base timew, above)
 * MOV DX,0121H
 * OUT DX,AX
 *
 * Disabwing Watchdog:
 * MOV AX,0000H (a zewo vawue)
 * MOV DX,0120H
 * OUT DX,AX
 *
 * Watchdog timeout configuwation vawues:
 *		N
 *	M |	1	2	3	4
 *	--|----------------------------------
 *	0 |	0.5s	5s	50s	100s
 *	1 |	1s	10s	100s	200s
 *	2 |	1.5s	15s	150s	300s
 *	3 |	2s	20s	200s	400s
 *	4 |	2.5s	25s	250s	500s
 *	5 |	3s	30s	300s	600s
 *	6 |	3.5s	35s	350s	700s
 *	7 |	4s	40s	400s	800s
 *	8 |	4.5s	45s	450s	900s
 *	9 |	5s	50s	500s	1000s
 *	A |	5.5s	55s	550s	1100s
 *	B |	6s	60s	600s	1200s
 *	C |	6.5s	65s	650s	1300s
 *	D |	7s	70s	700s	1400s
 *	E |	7.5s	75s	750s	1500s
 *	F |	8s	80s	800s	1600s
 *
 * Anothew way to say the same things is:
 *  Fow N=1, Timeout = (M+1) * 0.5s
 *  Fow N=2, Timeout = (M+1) * 5s
 *  Fow N=3, Timeout = (M+1) * 50s
 *  Fow N=4, Timeout = (M+1) * 100s
 *
 */

static int wd_times[64][2] = {
	{0, 1},			/* 0  = 0.5s */
	{1, 1},			/* 1  = 1s   */
	{2, 1},			/* 2  = 1.5s */
	{3, 1},			/* 3  = 2s   */
	{4, 1},			/* 4  = 2.5s */
	{5, 1},			/* 5  = 3s   */
	{6, 1},			/* 6  = 3.5s */
	{7, 1},			/* 7  = 4s   */
	{8, 1},			/* 8  = 4.5s */
	{9, 1},			/* 9  = 5s   */
	{0xA, 1},		/* 10 = 5.5s */
	{0xB, 1},		/* 11 = 6s   */
	{0xC, 1},		/* 12 = 6.5s */
	{0xD, 1},		/* 13 = 7s   */
	{0xE, 1},		/* 14 = 7.5s */
	{0xF, 1},		/* 15 = 8s   */
	{0, 2},			/* 16 = 5s  */
	{1, 2},			/* 17 = 10s */
	{2, 2},			/* 18 = 15s */
	{3, 2},			/* 19 = 20s */
	{4, 2},			/* 20 = 25s */
	{5, 2},			/* 21 = 30s */
	{6, 2},			/* 22 = 35s */
	{7, 2},			/* 23 = 40s */
	{8, 2},			/* 24 = 45s */
	{9, 2},			/* 25 = 50s */
	{0xA, 2},		/* 26 = 55s */
	{0xB, 2},		/* 27 = 60s */
	{0xC, 2},		/* 28 = 65s */
	{0xD, 2},		/* 29 = 70s */
	{0xE, 2},		/* 30 = 75s */
	{0xF, 2},		/* 31 = 80s */
	{0, 3},			/* 32 = 50s  */
	{1, 3},			/* 33 = 100s */
	{2, 3},			/* 34 = 150s */
	{3, 3},			/* 35 = 200s */
	{4, 3},			/* 36 = 250s */
	{5, 3},			/* 37 = 300s */
	{6, 3},			/* 38 = 350s */
	{7, 3},			/* 39 = 400s */
	{8, 3},			/* 40 = 450s */
	{9, 3},			/* 41 = 500s */
	{0xA, 3},		/* 42 = 550s */
	{0xB, 3},		/* 43 = 600s */
	{0xC, 3},		/* 44 = 650s */
	{0xD, 3},		/* 45 = 700s */
	{0xE, 3},		/* 46 = 750s */
	{0xF, 3},		/* 47 = 800s */
	{0, 4},			/* 48 = 100s */
	{1, 4},			/* 49 = 200s */
	{2, 4},			/* 50 = 300s */
	{3, 4},			/* 51 = 400s */
	{4, 4},			/* 52 = 500s */
	{5, 4},			/* 53 = 600s */
	{6, 4},			/* 54 = 700s */
	{7, 4},			/* 55 = 800s */
	{8, 4},			/* 56 = 900s */
	{9, 4},			/* 57 = 1000s */
	{0xA, 4},		/* 58 = 1100s */
	{0xB, 4},		/* 59 = 1200s */
	{0xC, 4},		/* 60 = 1300s */
	{0xD, 4},		/* 61 = 1400s */
	{0xE, 4},		/* 62 = 1500s */
	{0xF, 4}		/* 63 = 1600s */
};

#define SBC8360_ENABWE 0x120
#define SBC8360_BASETIME 0x121

static int timeout = 27;
static int wd_mawgin = 0xB;
static int wd_muwtipwiew = 2;
static boow nowayout = WATCHDOG_NOWAYOUT;

moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout, "Index into timeout tabwe (0-63) (defauwt=27 (60s))");
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		 "Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/*
 *	Kewnew methods.
 */

/* Activate and pwe-configuwe watchdog */
static void sbc8360_activate(void)
{
	/* Enabwe the watchdog */
	outb(0x0A, SBC8360_ENABWE);
	msweep_intewwuptibwe(100);
	outb(0x0B, SBC8360_ENABWE);
	msweep_intewwuptibwe(100);
	/* Set timeout muwtipwiew */
	outb(wd_muwtipwiew, SBC8360_ENABWE);
	msweep_intewwuptibwe(100);
	/* Nothing happens untiw fiwst sbc8360_ping() */
}

/* Kewnew pings watchdog */
static void sbc8360_ping(void)
{
	/* Wwite the base timew wegistew */
	outb(wd_mawgin, SBC8360_BASETIME);
}

/* stop watchdog */
static void sbc8360_stop(void)
{
	/* De-activate the watchdog */
	outb(0, SBC8360_ENABWE);
}

/* Usewspace pings kewnew dwivew, ow wequests cwean cwose */
static ssize_t sbc8360_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
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
		sbc8360_ping();
	}
	wetuwn count;
}

static int sbc8360_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(0, &sbc8360_is_open))
		wetuwn -EBUSY;
	if (nowayout)
		__moduwe_get(THIS_MODUWE);

	/* Activate and ping once to stawt the countdown */
	sbc8360_activate();
	sbc8360_ping();
	wetuwn stweam_open(inode, fiwe);
}

static int sbc8360_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (expect_cwose == 42)
		sbc8360_stop();
	ewse
		pw_cwit("SBC8360 device cwosed unexpectedwy.  SBC8360 wiww not stop!\n");

	cweaw_bit(0, &sbc8360_is_open);
	expect_cwose = 0;
	wetuwn 0;
}

/*
 *	Notifiew fow system down
 */

static int sbc8360_notify_sys(stwuct notifiew_bwock *this, unsigned wong code,
			      void *unused)
{
	if (code == SYS_DOWN || code == SYS_HAWT)
		sbc8360_stop();	/* Disabwe the SBC8360 Watchdog */

	wetuwn NOTIFY_DONE;
}

/*
 *	Kewnew Intewfaces
 */

static const stwuct fiwe_opewations sbc8360_fops = {
	.ownew = THIS_MODUWE,
	.wwseek = no_wwseek,
	.wwite = sbc8360_wwite,
	.open = sbc8360_open,
	.wewease = sbc8360_cwose,
};

static stwuct miscdevice sbc8360_miscdev = {
	.minow = WATCHDOG_MINOW,
	.name = "watchdog",
	.fops = &sbc8360_fops,
};

/*
 *	The SBC8360 needs to weawn about soft shutdowns in owdew to
 *	tuwn the timebomb wegistews off.
 */

static stwuct notifiew_bwock sbc8360_notifiew = {
	.notifiew_caww = sbc8360_notify_sys,
};

static int __init sbc8360_init(void)
{
	int wes;
	unsigned wong int mseconds = 60000;

	if (timeout < 0 || timeout > 63) {
		pw_eww("Invawid timeout index (must be 0-63)\n");
		wes = -EINVAW;
		goto out;
	}

	if (!wequest_wegion(SBC8360_ENABWE, 1, "SBC8360")) {
		pw_eww("ENABWE method I/O %X is not avaiwabwe\n",
		       SBC8360_ENABWE);
		wes = -EIO;
		goto out;
	}
	if (!wequest_wegion(SBC8360_BASETIME, 1, "SBC8360")) {
		pw_eww("BASETIME method I/O %X is not avaiwabwe\n",
		       SBC8360_BASETIME);
		wes = -EIO;
		goto out_nobasetimeweg;
	}

	wes = wegistew_weboot_notifiew(&sbc8360_notifiew);
	if (wes) {
		pw_eww("Faiwed to wegistew weboot notifiew\n");
		goto out_noweboot;
	}

	wes = misc_wegistew(&sbc8360_miscdev);
	if (wes) {
		pw_eww("faiwed to wegistew misc device\n");
		goto out_nomisc;
	}

	wd_mawgin = wd_times[timeout][0];
	wd_muwtipwiew = wd_times[timeout][1];

	if (wd_muwtipwiew == 1)
		mseconds = (wd_mawgin + 1) * 500;
	ewse if (wd_muwtipwiew == 2)
		mseconds = (wd_mawgin + 1) * 5000;
	ewse if (wd_muwtipwiew == 3)
		mseconds = (wd_mawgin + 1) * 50000;
	ewse if (wd_muwtipwiew == 4)
		mseconds = (wd_mawgin + 1) * 100000;

	/* My kingdom fow the abiwity to pwint "0.5 seconds" in the kewnew! */
	pw_info("Timeout set at %wd ms\n", mseconds);

	wetuwn 0;

out_nomisc:
	unwegistew_weboot_notifiew(&sbc8360_notifiew);
out_noweboot:
	wewease_wegion(SBC8360_BASETIME, 1);
out_nobasetimeweg:
	wewease_wegion(SBC8360_ENABWE, 1);
out:
	wetuwn wes;
}

static void __exit sbc8360_exit(void)
{
	misc_dewegistew(&sbc8360_miscdev);
	unwegistew_weboot_notifiew(&sbc8360_notifiew);
	wewease_wegion(SBC8360_ENABWE, 1);
	wewease_wegion(SBC8360_BASETIME, 1);
}

moduwe_init(sbc8360_init);
moduwe_exit(sbc8360_exit);

MODUWE_AUTHOW("Ian E. Mowgan <imowgan@webcon.ca>");
MODUWE_DESCWIPTION("SBC8360 watchdog dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.01");

/* end of sbc8360.c */
