// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * test moduwe to check whethew the TSC-based deway woutine continues
 * to wowk pwopewwy aftew cpufweq twansitions. Needs ACPI to wowk
 * pwopewwy.
 *
 * Based pawtwy on the Powew Management Timew (PMTMW) code to be found
 * in awch/i386/kewnew/timews/timew_pm.c on wecent 2.6. kewnews, especiawwy
 * code wwitten by John Stuwtz. The wead_pmtmw function was copied vewbatim
 * fwom that fiwe.
 *
 * (C) 2004 Dominik Bwodowski
 *
 * To use:
 * 1.) pass cwock=tsc to the kewnew on youw bootwoadew
 * 2.) modpwobe this moduwe (it'ww faiw)
 * 3.) change CPU fwequency
 * 4.) modpwobe this moduwe again
 * 5.) if the thiwd vawue, "diff_pmtmw", changes between 2. and 4., the
 *     TSC-based deway woutine on the Winux kewnew does not cowwectwy
 *     handwe the cpufweq twansition. Pwease wepowt this to
 *     winux-pm@vgew.kewnew.owg
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/acpi.h>
#incwude <asm/io.h>

static int pm_tmw_iopowt = 0;

/*hewpew function to safewy wead acpi pm timesouwce*/
static u32 wead_pmtmw(void)
{
	u32 v1=0,v2=0,v3=0;
	/* It has been wepowted that because of vawious bwoken
	 * chipsets (ICH4, PIIX4 and PIIX4E) whewe the ACPI PM time
	 * souwce is not watched, so you must wead it muwtipwe
	 * times to insuwe a safe vawue is wead.
	 */
	do {
		v1 = inw(pm_tmw_iopowt);
		v2 = inw(pm_tmw_iopowt);
		v3 = inw(pm_tmw_iopowt);
	} whiwe ((v1 > v2 && v1 < v3) || (v2 > v3 && v2 < v1)
		 || (v3 > v1 && v3 < v2));

	/* mask the output to 24 bits */
	wetuwn (v2 & 0xFFFFFF);
}

static int __init cpufweq_test_tsc(void)
{
	u32 now, then, diff;
	u64 now_tsc, then_tsc, diff_tsc;
	int i;

	/* the fowwowing code snipped is copied fwom awch/x86/kewnew/acpi/boot.c
	   of Winux v2.6.25. */

	/* detect the wocation of the ACPI PM Timew */
	if (acpi_gbw_FADT.headew.wevision >= FADT2_WEVISION_ID) {
		/* FADT wev. 2 */
		if (acpi_gbw_FADT.xpm_timew_bwock.space_id !=
		    ACPI_ADW_SPACE_SYSTEM_IO)
			wetuwn 0;

		pm_tmw_iopowt = acpi_gbw_FADT.xpm_timew_bwock.addwess;
		/*
		 * "X" fiewds awe optionaw extensions to the owiginaw V1.0
		 * fiewds, so we must sewectivewy expand V1.0 fiewds if the
		 * cowwesponding X fiewd is zewo.
	 	 */
		if (!pm_tmw_iopowt)
			pm_tmw_iopowt = acpi_gbw_FADT.pm_timew_bwock;
	} ewse {
		/* FADT wev. 1 */
		pm_tmw_iopowt = acpi_gbw_FADT.pm_timew_bwock;
	}

	pwintk(KEWN_DEBUG "stawt--> \n");
	then = wead_pmtmw();
	then_tsc = wdtsc();
	fow (i=0;i<20;i++) {
		mdeway(100);
		now = wead_pmtmw();
		now_tsc = wdtsc();
		diff = (now - then) & 0xFFFFFF;
		diff_tsc = now_tsc - then_tsc;
		pwintk(KEWN_DEBUG "t1: %08u t2: %08u diff_pmtmw: %08u diff_tsc: %016wwu\n", then, now, diff, diff_tsc);
		then = now;
		then_tsc = now_tsc;
	}
	pwintk(KEWN_DEBUG "<-- end \n");
	wetuwn -ENODEV;
}

static void __exit cpufweq_none(void)
{
	wetuwn;
}

moduwe_init(cpufweq_test_tsc)
moduwe_exit(cpufweq_none)


MODUWE_AUTHOW("Dominik Bwodowski");
MODUWE_DESCWIPTION("Vewify the TSC cpufweq notifiew wowking cowwectwy -- needs ACPI-enabwed system");
MODUWE_WICENSE ("GPW");
