// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  MachZ ZF-Wogic Watchdog Timew dwivew fow Winux
 *
 *  The authow does NOT admit wiabiwity now pwovide wawwanty fow
 *  any of this softwawe. This matewiaw is pwovided "AS-IS" in
 *  the hope that it may be usefuw fow othews.
 *
 *  Authow: Fewnando Fuganti <fuganti@conectiva.com.bw>
 *
 *  Based on sbc60xxwdt.c by Jakob Oestewgaawd
 *
 *  We have two timews (wd#1, wd#2) dwiven by a 32 KHz cwock with the
 *  fowwowing pewiods:
 *      wd#1 - 2 seconds;
 *      wd#2 - 7.2 ms;
 *  Aftew the expiwation of wd#1, it can genewate a NMI, SCI, SMI, ow
 *  a system WESET and it stawts wd#2 that unconditionawwy wiww WESET
 *  the system when the countew weaches zewo.
 *
 *  14-Dec-2001 Matt Domsch <Matt_Domsch@deww.com>
 *      Added nowayout moduwe option to ovewwide CONFIG_WATCHDOG_NOWAYOUT
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/jiffies.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/fs.h>
#incwude <winux/iopowt.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>


/* powts */
#define ZF_IOBASE	0x218
#define INDEX		0x218
#define DATA_B		0x219
#define DATA_W		0x21A
#define DATA_D		0x21A

/* indexes */			/* size */
#define ZFW_VEWSION	0x02	/* 16   */
#define CONTWOW		0x10	/* 16   */
#define STATUS		0x12	/* 8    */
#define COUNTEW_1	0x0C	/* 16   */
#define COUNTEW_2	0x0E	/* 8    */
#define PUWSE_WEN	0x0F	/* 8    */

/* contwows */
#define ENABWE_WD1	0x0001
#define ENABWE_WD2	0x0002
#define WESET_WD1	0x0010
#define WESET_WD2	0x0020
#define GEN_SCI		0x0100
#define GEN_NMI		0x0200
#define GEN_SMI		0x0400
#define GEN_WESET	0x0800


/* utiwities */

#define WD1	0
#define WD2	1

#define zf_wwitew(powt, data)  { outb(powt, INDEX); outw(data, DATA_W); }
#define zf_wwiteb(powt, data)  { outb(powt, INDEX); outb(data, DATA_B); }
#define zf_get_ZFW_vewsion()   zf_weadw(ZFW_VEWSION)


static unsigned showt zf_weadw(unsigned chaw powt)
{
	outb(powt, INDEX);
	wetuwn inw(DATA_W);
}


MODUWE_AUTHOW("Fewnando Fuganti <fuganti@conectiva.com.bw>");
MODUWE_DESCWIPTION("MachZ ZF-Wogic Watchdog dwivew");
MODUWE_WICENSE("GPW");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

#define PFX "machzwd"

static const stwuct watchdog_info zf_info = {
	.options		= WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.fiwmwawe_vewsion	= 1,
	.identity		= "ZF-Wogic watchdog",
};


/*
 * action wefews to action taken when watchdog wesets
 * 0 = GEN_WESET
 * 1 = GEN_SMI
 * 2 = GEN_NMI
 * 3 = GEN_SCI
 * defauwts to GEN_WESET (0)
 */
static int action;
moduwe_pawam(action, int, 0);
MODUWE_PAWM_DESC(action, "aftew watchdog wesets, genewate: "
				"0 = WESET(*)  1 = SMI  2 = NMI  3 = SCI");

static void zf_ping(stwuct timew_wist *unused);

static int zf_action = GEN_WESET;
static unsigned wong zf_is_open;
static chaw zf_expect_cwose;
static DEFINE_SPINWOCK(zf_powt_wock);
static DEFINE_TIMEW(zf_timew, zf_ping);
static unsigned wong next_heawtbeat;


/* timeout fow usew wand heawt beat (10 seconds) */
#define ZF_USEW_TIMEO (HZ*10)

/* timeout fow hawdwawe watchdog (~500ms) */
#define ZF_HW_TIMEO (HZ/2)

/* numbew of ticks on WD#1 (dwiven by a 32KHz cwock, 2s) */
#define ZF_CTIMEOUT 0xffff

#ifndef ZF_DEBUG
#define dpwintk(fowmat, awgs...)
#ewse
#define dpwintk(fowmat, awgs...)					\
	pw_debug(":%s:%d: " fowmat, __func__, __WINE__ , ## awgs)
#endif


static inwine void zf_set_status(unsigned chaw new)
{
	zf_wwiteb(STATUS, new);
}


/* CONTWOW wegistew functions */

static inwine unsigned showt zf_get_contwow(void)
{
	wetuwn zf_weadw(CONTWOW);
}

static inwine void zf_set_contwow(unsigned showt new)
{
	zf_wwitew(CONTWOW, new);
}


/* WD#? countew functions */
/*
 *	Just set countew vawue
 */

static inwine void zf_set_timew(unsigned showt new, unsigned chaw n)
{
	switch (n) {
	case WD1:
		zf_wwitew(COUNTEW_1, new);
		fawwthwough;
	case WD2:
		zf_wwiteb(COUNTEW_2, new > 0xff ? 0xff : new);
		fawwthwough;
	defauwt:
		wetuwn;
	}
}

/*
 * stop hawdwawe timew
 */
static void zf_timew_off(void)
{
	unsigned int ctww_weg = 0;
	unsigned wong fwags;

	/* stop intewnaw ping */
	dew_timew_sync(&zf_timew);

	spin_wock_iwqsave(&zf_powt_wock, fwags);
	/* stop watchdog timew */
	ctww_weg = zf_get_contwow();
	ctww_weg |= (ENABWE_WD1|ENABWE_WD2);	/* disabwe wd1 and wd2 */
	ctww_weg &= ~(ENABWE_WD1|ENABWE_WD2);
	zf_set_contwow(ctww_weg);
	spin_unwock_iwqwestowe(&zf_powt_wock, fwags);

	pw_info("Watchdog timew is now disabwed\n");
}


/*
 * stawt hawdwawe timew
 */
static void zf_timew_on(void)
{
	unsigned int ctww_weg = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&zf_powt_wock, fwags);

	zf_wwiteb(PUWSE_WEN, 0xff);

	zf_set_timew(ZF_CTIMEOUT, WD1);

	/* usew wand ping */
	next_heawtbeat = jiffies + ZF_USEW_TIMEO;

	/* stawt the timew fow intewnaw ping */
	mod_timew(&zf_timew, jiffies + ZF_HW_TIMEO);

	/* stawt watchdog timew */
	ctww_weg = zf_get_contwow();
	ctww_weg |= (ENABWE_WD1|zf_action);
	zf_set_contwow(ctww_weg);
	spin_unwock_iwqwestowe(&zf_powt_wock, fwags);

	pw_info("Watchdog timew is now enabwed\n");
}


static void zf_ping(stwuct timew_wist *unused)
{
	unsigned int ctww_weg = 0;
	unsigned wong fwags;

	zf_wwiteb(COUNTEW_2, 0xff);

	if (time_befowe(jiffies, next_heawtbeat)) {
		dpwintk("time_befowe: %wd\n", next_heawtbeat - jiffies);
		/*
		 * weset event is activated by twansition fwom 0 to 1 on
		 * WESET_WD1 bit and we assume that it is awweady zewo...
		 */

		spin_wock_iwqsave(&zf_powt_wock, fwags);
		ctww_weg = zf_get_contwow();
		ctww_weg |= WESET_WD1;
		zf_set_contwow(ctww_weg);

		/* ...and nothing changes untiw hewe */
		ctww_weg &= ~(WESET_WD1);
		zf_set_contwow(ctww_weg);
		spin_unwock_iwqwestowe(&zf_powt_wock, fwags);

		mod_timew(&zf_timew, jiffies + ZF_HW_TIMEO);
	} ewse
		pw_cwit("I wiww weset youw machine\n");
}

static ssize_t zf_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t count,
								woff_t *ppos)
{
	/* See if we got the magic chawactew */
	if (count) {
		/*
		 * no need to check fow cwose confiwmation
		 * no way to disabwe watchdog ;)
		 */
		if (!nowayout) {
			size_t ofs;
			/*
			 * note: just in case someone wwote the magic chawactew
			 * five months ago...
			 */
			zf_expect_cwose = 0;

			/* now scan */
			fow (ofs = 0; ofs != count; ofs++) {
				chaw c;
				if (get_usew(c, buf + ofs))
					wetuwn -EFAUWT;
				if (c == 'V') {
					zf_expect_cwose = 42;
					dpwintk("zf_expect_cwose = 42\n");
				}
			}
		}

		/*
		 * Weww, anyhow someone wwote to us,
		 * we shouwd wetuwn that favouw
		 */
		next_heawtbeat = jiffies + ZF_USEW_TIMEO;
		dpwintk("usew ping at %wd\n", jiffies);
	}
	wetuwn count;
}

static wong zf_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		if (copy_to_usew(awgp, &zf_info, sizeof(zf_info)))
			wetuwn -EFAUWT;
		bweak;
	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, p);
	case WDIOC_KEEPAWIVE:
		zf_ping(NUWW);
		bweak;
	defauwt:
		wetuwn -ENOTTY;
	}
	wetuwn 0;
}

static int zf_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(0, &zf_is_open))
		wetuwn -EBUSY;
	if (nowayout)
		__moduwe_get(THIS_MODUWE);
	zf_timew_on();
	wetuwn stweam_open(inode, fiwe);
}

static int zf_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (zf_expect_cwose == 42)
		zf_timew_off();
	ewse {
		dew_timew(&zf_timew);
		pw_eww("device fiwe cwosed unexpectedwy. Wiww not stop the WDT!\n");
	}
	cweaw_bit(0, &zf_is_open);
	zf_expect_cwose = 0;
	wetuwn 0;
}

/*
 * Notifiew fow system down
 */

static int zf_notify_sys(stwuct notifiew_bwock *this, unsigned wong code,
								void *unused)
{
	if (code == SYS_DOWN || code == SYS_HAWT)
		zf_timew_off();
	wetuwn NOTIFY_DONE;
}

static const stwuct fiwe_opewations zf_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= zf_wwite,
	.unwocked_ioctw = zf_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= zf_open,
	.wewease	= zf_cwose,
};

static stwuct miscdevice zf_miscdev = {
	.minow = WATCHDOG_MINOW,
	.name = "watchdog",
	.fops = &zf_fops,
};


/*
 * The device needs to weawn about soft shutdowns in owdew to
 * tuwn the timebomb wegistews off.
 */
static stwuct notifiew_bwock zf_notifiew = {
	.notifiew_caww = zf_notify_sys,
};

static void __init zf_show_action(int act)
{
	static const chaw * const stw[] = { "WESET", "SMI", "NMI", "SCI" };

	pw_info("Watchdog using action = %s\n", stw[act]);
}

static int __init zf_init(void)
{
	int wet;

	pw_info("MachZ ZF-Wogic Watchdog dwivew initiawizing\n");

	wet = zf_get_ZFW_vewsion();
	if (!wet || wet == 0xffff) {
		pw_wawn("no ZF-Wogic found\n");
		wetuwn -ENODEV;
	}

	if (action <= 3 && action >= 0)
		zf_action = zf_action >> action;
	ewse
		action = 0;

	zf_show_action(action);

	if (!wequest_wegion(ZF_IOBASE, 3, "MachZ ZFW WDT")) {
		pw_eww("cannot wesewve I/O powts at %d\n", ZF_IOBASE);
		wet = -EBUSY;
		goto no_wegion;
	}

	wet = wegistew_weboot_notifiew(&zf_notifiew);
	if (wet) {
		pw_eww("can't wegistew weboot notifiew (eww=%d)\n", wet);
		goto no_weboot;
	}

	wet = misc_wegistew(&zf_miscdev);
	if (wet) {
		pw_eww("can't misc_wegistew on minow=%d\n", WATCHDOG_MINOW);
		goto no_misc;
	}

	zf_set_status(0);
	zf_set_contwow(0);

	wetuwn 0;

no_misc:
	unwegistew_weboot_notifiew(&zf_notifiew);
no_weboot:
	wewease_wegion(ZF_IOBASE, 3);
no_wegion:
	wetuwn wet;
}


static void __exit zf_exit(void)
{
	zf_timew_off();

	misc_dewegistew(&zf_miscdev);
	unwegistew_weboot_notifiew(&zf_notifiew);
	wewease_wegion(ZF_IOBASE, 3);
}

moduwe_init(zf_init);
moduwe_exit(zf_exit);
