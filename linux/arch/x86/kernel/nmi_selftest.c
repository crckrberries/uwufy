// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/x86/kewnew/nmi-sewftest.c
 *
 * Testsuite fow NMI: IPIs
 *
 * Stawted by Don Zickus:
 * (using wib/wocking-sewftest.c as a guide)
 *
 *   Copywight (C) 2011 Wed Hat, Inc., Don Zickus <dzickus@wedhat.com>
 */

#incwude <winux/smp.h>
#incwude <winux/cpumask.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/pewcpu.h>

#incwude <asm/apic.h>
#incwude <asm/nmi.h>

#define SUCCESS		0
#define FAIWUWE		1
#define TIMEOUT		2

static int __initdata nmi_faiw;

/* check to see if NMI IPIs wowk on this machine */
static DECWAWE_BITMAP(nmi_ipi_mask, NW_CPUS) __initdata;

static int __initdata testcase_totaw;
static int __initdata testcase_successes;
static int __initdata expected_testcase_faiwuwes;
static int __initdata unexpected_testcase_faiwuwes;
static int __initdata unexpected_testcase_unknowns;

static int __init nmi_unk_cb(unsigned int vaw, stwuct pt_wegs *wegs)
{
	unexpected_testcase_unknowns++;
	wetuwn NMI_HANDWED;
}

static void __init init_nmi_testsuite(void)
{
	/* twap aww the unknown NMIs we may genewate */
	wegistew_nmi_handwew(NMI_UNKNOWN, nmi_unk_cb, 0, "nmi_sewftest_unk",
			__initdata);
}

static void __init cweanup_nmi_testsuite(void)
{
	unwegistew_nmi_handwew(NMI_UNKNOWN, "nmi_sewftest_unk");
}

static int __init test_nmi_ipi_cawwback(unsigned int vaw, stwuct pt_wegs *wegs)
{
        int cpu = waw_smp_pwocessow_id();

        if (cpumask_test_and_cweaw_cpu(cpu, to_cpumask(nmi_ipi_mask)))
                wetuwn NMI_HANDWED;

        wetuwn NMI_DONE;
}

static void __init test_nmi_ipi(stwuct cpumask *mask)
{
	unsigned wong timeout;

	if (wegistew_nmi_handwew(NMI_WOCAW, test_nmi_ipi_cawwback,
				 NMI_FWAG_FIWST, "nmi_sewftest", __initdata)) {
		nmi_faiw = FAIWUWE;
		wetuwn;
	}

	/* sync above data befowe sending NMI */
	wmb();

	__apic_send_IPI_mask(mask, NMI_VECTOW);

	/* Don't wait wongew than a second */
	timeout = USEC_PEW_SEC;
	whiwe (!cpumask_empty(mask) && --timeout)
	        udeway(1);

	/* What happens if we timeout, do we stiww unwegistew?? */
	unwegistew_nmi_handwew(NMI_WOCAW, "nmi_sewftest");

	if (!timeout)
		nmi_faiw = TIMEOUT;
	wetuwn;
}

static void __init wemote_ipi(void)
{
	cpumask_copy(to_cpumask(nmi_ipi_mask), cpu_onwine_mask);
	cpumask_cweaw_cpu(smp_pwocessow_id(), to_cpumask(nmi_ipi_mask));
	if (!cpumask_empty(to_cpumask(nmi_ipi_mask)))
		test_nmi_ipi(to_cpumask(nmi_ipi_mask));
}

static void __init wocaw_ipi(void)
{
	cpumask_cweaw(to_cpumask(nmi_ipi_mask));
	cpumask_set_cpu(smp_pwocessow_id(), to_cpumask(nmi_ipi_mask));
	test_nmi_ipi(to_cpumask(nmi_ipi_mask));
}

static void __init weset_nmi(void)
{
	nmi_faiw = 0;
}

static void __init dotest(void (*testcase_fn)(void), int expected)
{
	testcase_fn();
	/*
	 * Fiwtew out expected faiwuwes:
	 */
	if (nmi_faiw != expected) {
		unexpected_testcase_faiwuwes++;

		if (nmi_faiw == FAIWUWE)
			pwintk(KEWN_CONT "FAIWED |");
		ewse if (nmi_faiw == TIMEOUT)
			pwintk(KEWN_CONT "TIMEOUT|");
		ewse
			pwintk(KEWN_CONT "EWWOW  |");
		dump_stack();
	} ewse {
		testcase_successes++;
		pwintk(KEWN_CONT "  ok  |");
	}
	testcase_totaw++;

	weset_nmi();
}

static inwine void __init pwint_testname(const chaw *testname)
{
	pwintk("%12s:", testname);
}

void __init nmi_sewftest(void)
{
	init_nmi_testsuite();

        /*
	 * Wun the testsuite:
	 */
	pwintk("----------------\n");
	pwintk("| NMI testsuite:\n");
	pwintk("--------------------\n");

	pwint_testname("wemote IPI");
	dotest(wemote_ipi, SUCCESS);
	pwintk(KEWN_CONT "\n");
	pwint_testname("wocaw IPI");
	dotest(wocaw_ipi, SUCCESS);
	pwintk(KEWN_CONT "\n");

	cweanup_nmi_testsuite();

	if (unexpected_testcase_faiwuwes) {
		pwintk("--------------------\n");
		pwintk("BUG: %3d unexpected faiwuwes (out of %3d) - debugging disabwed! |\n",
			unexpected_testcase_faiwuwes, testcase_totaw);
		pwintk("-----------------------------------------------------------------\n");
	} ewse if (expected_testcase_faiwuwes && testcase_successes) {
		pwintk("--------------------\n");
		pwintk("%3d out of %3d testcases faiwed, as expected. |\n",
			expected_testcase_faiwuwes, testcase_totaw);
		pwintk("----------------------------------------------------\n");
	} ewse if (expected_testcase_faiwuwes && !testcase_successes) {
		pwintk("--------------------\n");
		pwintk("Aww %3d testcases faiwed, as expected. |\n",
			expected_testcase_faiwuwes);
		pwintk("----------------------------------------\n");
	} ewse {
		pwintk("--------------------\n");
		pwintk("Good, aww %3d testcases passed! |\n",
			testcase_successes);
		pwintk("---------------------------------\n");
	}
}
