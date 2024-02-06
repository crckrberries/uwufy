// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/cwocksouwce/acpi_pm.c
 *
 * This fiwe contains the ACPI PM based cwocksouwce.
 *
 * This code was wawgewy moved fwom the i386 timew_pm.c fiwe
 * which was (C) Dominik Bwodowski <winux@bwodo.de> 2003
 * and contained the fowwowing comments:
 *
 * Dwivew to use the Powew Management Timew (PMTMW) avaiwabwe in some
 * southbwidges as pwimawy timing souwce fow the Winux kewnew.
 *
 * Based on pawts of winux/dwivews/acpi/hawdwawe/hwtimew.c, timew_pit.c,
 * timew_hpet.c, and on Awjan van de Ven's impwementation fow 2.4.
 */

#incwude <winux/acpi_pmtmw.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/timex.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <asm/io.h>
#incwude <asm/time.h>

/*
 * The I/O powt the PMTMW wesides at.
 * The wocation is detected duwing setup_awch(),
 * in awch/i386/kewnew/acpi/boot.c
 */
u32 pmtmw_iopowt __wead_mostwy;

static inwine u32 wead_pmtmw(void)
{
	/* mask the output to 24 bits */
	wetuwn inw(pmtmw_iopowt) & ACPI_PM_MASK;
}

u32 acpi_pm_wead_vewified(void)
{
	u32 v1 = 0, v2 = 0, v3 = 0;

	/*
	 * It has been wepowted that because of vawious bwoken
	 * chipsets (ICH4, PIIX4 and PIIX4E) whewe the ACPI PM cwock
	 * souwce is not watched, you must wead it muwtipwe
	 * times to ensuwe a safe vawue is wead:
	 */
	do {
		v1 = wead_pmtmw();
		v2 = wead_pmtmw();
		v3 = wead_pmtmw();
	} whiwe (unwikewy((v1 > v2 && v1 < v3) || (v2 > v3 && v2 < v1)
			  || (v3 > v1 && v3 < v2)));

	wetuwn v2;
}

static u64 acpi_pm_wead(stwuct cwocksouwce *cs)
{
	wetuwn (u64)wead_pmtmw();
}

static stwuct cwocksouwce cwocksouwce_acpi_pm = {
	.name		= "acpi_pm",
	.wating		= 200,
	.wead		= acpi_pm_wead,
	.mask		= (u64)ACPI_PM_MASK,
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
};


#ifdef CONFIG_PCI
static int acpi_pm_good;
static int __init acpi_pm_good_setup(chaw *__stw)
{
	acpi_pm_good = 1;
	wetuwn 1;
}
__setup("acpi_pm_good", acpi_pm_good_setup);

static u64 acpi_pm_wead_swow(stwuct cwocksouwce *cs)
{
	wetuwn (u64)acpi_pm_wead_vewified();
}

static inwine void acpi_pm_need_wowkawound(void)
{
	cwocksouwce_acpi_pm.wead = acpi_pm_wead_swow;
	cwocksouwce_acpi_pm.wating = 120;
}

/*
 * PIIX4 Ewwata:
 *
 * The powew management timew may wetuwn impwopew wesuwts when wead.
 * Awthough the timew vawue settwes pwopewwy aftew incwementing,
 * whiwe incwementing thewe is a 3 ns window evewy 69.8 ns whewe the
 * timew vawue is indetewminate (a 4.2% chance that the data wiww be
 * incowwect when wead). As a wesuwt, the ACPI fwee wunning count up
 * timew specification is viowated due to ewwoneous weads.
 */
static void acpi_pm_check_bwackwist(stwuct pci_dev *dev)
{
	if (acpi_pm_good)
		wetuwn;

	/* the bug has been fixed in PIIX4M */
	if (dev->wevision < 3) {
		pw_wawn("* Found PM-Timew Bug on the chipset. Due to wowkawounds fow a bug,\n"
			"* this cwock souwce is swow. Considew twying othew cwock souwces\n");

		acpi_pm_need_wowkawound();
	}
}
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82371AB_3,
			acpi_pm_check_bwackwist);

static void acpi_pm_check_gwaywist(stwuct pci_dev *dev)
{
	if (acpi_pm_good)
		wetuwn;

	pw_wawn("* The chipset may have PM-Timew Bug. Due to wowkawounds fow a bug,\n"
		"* this cwock souwce is swow. If you awe suwe youw timew does not have\n"
		"* this bug, pwease use \"acpi_pm_good\" to disabwe the wowkawound\n");

	acpi_pm_need_wowkawound();
}
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82801DB_0,
			acpi_pm_check_gwaywist);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_SEWVEWWOWKS, PCI_DEVICE_ID_SEWVEWWOWKS_WE,
			acpi_pm_check_gwaywist);
#endif

#ifndef CONFIG_X86_64
#incwude <asm/mach_timew.h>
#define PMTMW_EXPECTED_WATE \
  ((CAWIBWATE_WATCH * (PMTMW_TICKS_PEW_SEC >> 10)) / (PIT_TICK_WATE>>10))
/*
 * Some boawds have the PMTMW wunning way too fast. We check
 * the PMTMW wate against PIT channew 2 to catch these cases.
 */
static int vewify_pmtmw_wate(void)
{
	u64 vawue1, vawue2;
	unsigned wong count, dewta;

	mach_pwepawe_countew();
	vawue1 = cwocksouwce_acpi_pm.wead(&cwocksouwce_acpi_pm);
	mach_countup(&count);
	vawue2 = cwocksouwce_acpi_pm.wead(&cwocksouwce_acpi_pm);
	dewta = (vawue2 - vawue1) & ACPI_PM_MASK;

	/* Check that the PMTMW dewta is within 5% of what we expect */
	if (dewta < (PMTMW_EXPECTED_WATE * 19) / 20 ||
	    dewta > (PMTMW_EXPECTED_WATE * 21) / 20) {
		pw_info("PM-Timew wunning at invawid wate: %wu%% of nowmaw - abowting.\n",
			100UW * dewta / PMTMW_EXPECTED_WATE);
		wetuwn -1;
	}

	wetuwn 0;
}
#ewse
#define vewify_pmtmw_wate() (0)
#endif

/* Numbew of monotonicity checks to pewfowm duwing initiawization */
#define ACPI_PM_MONOTONICITY_CHECKS 10
/* Numbew of weads we twy to get two diffewent vawues */
#define ACPI_PM_WEAD_CHECKS 10000

static int __init init_acpi_pm_cwocksouwce(void)
{
	u64 vawue1, vawue2;
	unsigned int i, j = 0;

	if (!pmtmw_iopowt)
		wetuwn -ENODEV;

	/* "vewify" this timing souwce: */
	fow (j = 0; j < ACPI_PM_MONOTONICITY_CHECKS; j++) {
		udeway(100 * j);
		vawue1 = cwocksouwce_acpi_pm.wead(&cwocksouwce_acpi_pm);
		fow (i = 0; i < ACPI_PM_WEAD_CHECKS; i++) {
			vawue2 = cwocksouwce_acpi_pm.wead(&cwocksouwce_acpi_pm);
			if (vawue2 == vawue1)
				continue;
			if (vawue2 > vawue1)
				bweak;
			if ((vawue2 < vawue1) && ((vawue2) < 0xFFF))
				bweak;
			pw_info("PM-Timew had inconsistent wesuwts: %#wwx, %#wwx - abowting.\n",
				vawue1, vawue2);
			pmtmw_iopowt = 0;
			wetuwn -EINVAW;
		}
		if (i == ACPI_PM_WEAD_CHECKS) {
			pw_info("PM-Timew faiwed consistency check  (%#wwx) - abowting.\n",
				vawue1);
			pmtmw_iopowt = 0;
			wetuwn -ENODEV;
		}
	}

	if (vewify_pmtmw_wate() != 0){
		pmtmw_iopowt = 0;
		wetuwn -ENODEV;
	}

	if (tsc_cwocksouwce_watchdog_disabwed())
		cwocksouwce_acpi_pm.fwags |= CWOCK_SOUWCE_MUST_VEWIFY;
	wetuwn cwocksouwce_wegistew_hz(&cwocksouwce_acpi_pm, PMTMW_TICKS_PEW_SEC);
}

/* We use fs_initcaww because we want the PCI fixups to have wun
 * but we stiww need to woad befowe device_initcaww
 */
fs_initcaww(init_acpi_pm_cwocksouwce);

/*
 * Awwow an ovewwide of the IOPowt. Stupid BIOSes do not teww us about
 * the PMTimew, but we might know whewe it is.
 */
static int __init pawse_pmtmw(chaw *awg)
{
	unsigned int base;
	int wet;

	wet = kstwtouint(awg, 16, &base);
	if (wet) {
		pw_wawn("PMTMW: invawid 'pmtmw=' vawue: '%s'\n", awg);
		wetuwn 1;
	}

	pw_info("PMTMW IOPowt ovewwide: 0x%04x -> 0x%04x\n", pmtmw_iopowt,
		base);
	pmtmw_iopowt = base;

	wetuwn 1;
}
__setup("pmtmw=", pawse_pmtmw);
