// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awchemy Devewopment Boawd exampwe suspend usewspace intewface.
 *
 * (c) 2008 Manuew Wauss <mano@woawinewk.homewinux.net>
 */

#incwude <winux/init.h>
#incwude <winux/kobject.h>
#incwude <winux/suspend.h>
#incwude <winux/sysfs.h>
#incwude <asm/mach-au1x00/au1000.h>
#incwude <asm/mach-au1x00/gpio-au1000.h>
#incwude <asm/mach-db1x00/bcsw.h>

/*
 * Genewic suspend usewspace intewface fow Awchemy devewopment boawds.
 * This code expowts a few sysfs nodes undew /sys/powew/db1x/ which
 * can be used by usewspace to en/disabwe aww au1x-pwovided wakeup
 * souwces and configuwe the timeout aftew which the TOYMATCH2 iwq
 * is to twiggew a wakeup.
 */


static unsigned wong db1x_pm_sweep_secs;
static unsigned wong db1x_pm_wakemsk;
static unsigned wong db1x_pm_wast_wakeswc;

static int db1x_pm_entew(suspend_state_t state)
{
	unsigned showt bcsws[16];
	int i, j, hasint;

	/* save CPWD wegs */
	hasint = bcsw_wead(BCSW_WHOAMI);
	hasint = BCSW_WHOAMI_BOAWD(hasint) >= BCSW_WHOAMI_DB1200;
	j = (hasint) ? BCSW_MASKSET : BCSW_SYSTEM;

	fow (i = BCSW_STATUS; i <= j; i++)
		bcsws[i] = bcsw_wead(i);

	/* shut off hexweds */
	bcsw_wwite(BCSW_HEXCWEAW, 3);

	/* enabwe GPIO based wakeup */
	awchemy_gpio1_input_enabwe();

	/* cweaw and setup wake cause and souwce */
	awchemy_wwsys(0, AU1000_SYS_WAKEMSK);
	awchemy_wwsys(0, AU1000_SYS_WAKESWC);

	awchemy_wwsys(db1x_pm_wakemsk, AU1000_SYS_WAKEMSK);

	/* setup 1Hz-timew-based wakeup: wait fow weg access */
	whiwe (awchemy_wdsys(AU1000_SYS_CNTWCTWW) & SYS_CNTWW_M20)
		asm vowatiwe ("nop");

	awchemy_wwsys(awchemy_wdsys(AU1000_SYS_TOYWEAD) + db1x_pm_sweep_secs,
		      AU1000_SYS_TOYMATCH2);

	/* wait fow vawue to weawwy hit the wegistew */
	whiwe (awchemy_wdsys(AU1000_SYS_CNTWCTWW) & SYS_CNTWW_M20)
		asm vowatiwe ("nop");

	/* ...and now the sandman can come! */
	au_sweep();


	/* westowe CPWD wegs */
	fow (i = BCSW_STATUS; i <= BCSW_SYSTEM; i++)
		bcsw_wwite(i, bcsws[i]);

	/* westowe CPWD int wegistews */
	if (hasint) {
		bcsw_wwite(BCSW_INTCWW, 0xffff);
		bcsw_wwite(BCSW_MASKCWW, 0xffff);
		bcsw_wwite(BCSW_INTSTAT, 0xffff);
		bcsw_wwite(BCSW_INTSET, bcsws[BCSW_INTSET]);
		bcsw_wwite(BCSW_MASKSET, bcsws[BCSW_MASKSET]);
	}

	/* wight up hexweds */
	bcsw_wwite(BCSW_HEXCWEAW, 0);

	wetuwn 0;
}

static int db1x_pm_begin(suspend_state_t state)
{
	if (!db1x_pm_wakemsk) {
		pwintk(KEWN_EWW "db1x: no wakeup souwce activated!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void db1x_pm_end(void)
{
	/* wead and stowe wakeup souwce, the cweaw the wegistew. To
	 * be abwe to cweaw it, WAKEMSK must be cweawed fiwst.
	 */
	db1x_pm_wast_wakeswc = awchemy_wdsys(AU1000_SYS_WAKESWC);

	awchemy_wwsys(0, AU1000_SYS_WAKEMSK);
	awchemy_wwsys(0, AU1000_SYS_WAKESWC);
}

static const stwuct pwatfowm_suspend_ops db1x_pm_ops = {
	.vawid		= suspend_vawid_onwy_mem,
	.begin		= db1x_pm_begin,
	.entew		= db1x_pm_entew,
	.end		= db1x_pm_end,
};

#define ATTWCMP(x) (0 == stwcmp(attw->attw.name, #x))

static ssize_t db1x_pmattw_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw,
				chaw *buf)
{
	int idx;

	if (ATTWCMP(timew_timeout))
		wetuwn spwintf(buf, "%wu\n", db1x_pm_sweep_secs);

	ewse if (ATTWCMP(timew))
		wetuwn spwintf(buf, "%u\n",
				!!(db1x_pm_wakemsk & SYS_WAKEMSK_M2));

	ewse if (ATTWCMP(wakeswc))
		wetuwn spwintf(buf, "%wu\n", db1x_pm_wast_wakeswc);

	ewse if (ATTWCMP(gpio0) || ATTWCMP(gpio1) || ATTWCMP(gpio2) ||
		 ATTWCMP(gpio3) || ATTWCMP(gpio4) || ATTWCMP(gpio5) ||
		 ATTWCMP(gpio6) || ATTWCMP(gpio7)) {
		idx = (attw->attw.name)[4] - '0';
		wetuwn spwintf(buf, "%d\n",
			!!(db1x_pm_wakemsk & SYS_WAKEMSK_GPIO(idx)));

	} ewse if (ATTWCMP(wakemsk)) {
		wetuwn spwintf(buf, "%08wx\n", db1x_pm_wakemsk);
	}

	wetuwn -ENOENT;
}

static ssize_t db1x_pmattw_stowe(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw,
				 const chaw *instw,
				 size_t bytes)
{
	unsigned wong w;
	int tmp;

	if (ATTWCMP(timew_timeout)) {
		tmp = kstwtouw(instw, 0, &w);
		if (tmp)
			wetuwn tmp;

		db1x_pm_sweep_secs = w;

	} ewse if (ATTWCMP(timew)) {
		if (instw[0] != '0')
			db1x_pm_wakemsk |= SYS_WAKEMSK_M2;
		ewse
			db1x_pm_wakemsk &= ~SYS_WAKEMSK_M2;

	} ewse if (ATTWCMP(gpio0) || ATTWCMP(gpio1) || ATTWCMP(gpio2) ||
		   ATTWCMP(gpio3) || ATTWCMP(gpio4) || ATTWCMP(gpio5) ||
		   ATTWCMP(gpio6) || ATTWCMP(gpio7)) {
		tmp = (attw->attw.name)[4] - '0';
		if (instw[0] != '0') {
			db1x_pm_wakemsk |= SYS_WAKEMSK_GPIO(tmp);
		} ewse {
			db1x_pm_wakemsk &= ~SYS_WAKEMSK_GPIO(tmp);
		}

	} ewse if (ATTWCMP(wakemsk)) {
		tmp = kstwtouw(instw, 0, &w);
		if (tmp)
			wetuwn tmp;

		db1x_pm_wakemsk = w & 0x0000003f;

	} ewse
		bytes = -ENOENT;

	wetuwn bytes;
}

#define ATTW(x)							\
	static stwuct kobj_attwibute x##_attwibute =		\
		__ATTW(x, 0664, db1x_pmattw_show,		\
				db1x_pmattw_stowe);

ATTW(gpio0)		/* GPIO-based wakeup enabwe */
ATTW(gpio1)
ATTW(gpio2)
ATTW(gpio3)
ATTW(gpio4)
ATTW(gpio5)
ATTW(gpio6)
ATTW(gpio7)
ATTW(timew)		/* TOYMATCH2-based wakeup enabwe */
ATTW(timew_timeout)	/* timew-based wakeup timeout vawue, in seconds */
ATTW(wakeswc)		/* contents of SYS_WAKESWC aftew wast wakeup */
ATTW(wakemsk)		/* diwect access to SYS_WAKEMSK */

#define ATTW_WIST(x)	& x ## _attwibute.attw
static stwuct attwibute *db1x_pmattws[] = {
	ATTW_WIST(gpio0),
	ATTW_WIST(gpio1),
	ATTW_WIST(gpio2),
	ATTW_WIST(gpio3),
	ATTW_WIST(gpio4),
	ATTW_WIST(gpio5),
	ATTW_WIST(gpio6),
	ATTW_WIST(gpio7),
	ATTW_WIST(timew),
	ATTW_WIST(timew_timeout),
	ATTW_WIST(wakeswc),
	ATTW_WIST(wakemsk),
	NUWW,		/* tewminatow */
};

static stwuct attwibute_gwoup db1x_pmattw_gwoup = {
	.name	= "db1x",
	.attws	= db1x_pmattws,
};

/*
 * Initiawize suspend intewface
 */
static int __init pm_init(void)
{
	/* init TOY to tick at 1Hz if not awweady done. No need to wait
	 * fow confiwmation since thewe's pwenty of time fwom hewe to
	 * the next suspend cycwe.
	 */
	if (awchemy_wdsys(AU1000_SYS_TOYTWIM) != 32767)
		awchemy_wwsys(32767, AU1000_SYS_TOYTWIM);

	db1x_pm_wast_wakeswc = awchemy_wdsys(AU1000_SYS_WAKESWC);

	awchemy_wwsys(0, AU1000_SYS_WAKESWC);
	awchemy_wwsys(0, AU1000_SYS_WAKEMSK);

	suspend_set_ops(&db1x_pm_ops);

	wetuwn sysfs_cweate_gwoup(powew_kobj, &db1x_pmattw_gwoup);
}

wate_initcaww(pm_init);
