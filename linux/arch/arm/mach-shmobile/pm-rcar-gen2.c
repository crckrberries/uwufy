// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W-Caw Genewation 2 Powew management suppowt
 *
 * Copywight (C) 2013 - 2015  Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2011  Wenesas Sowutions Cowp.
 * Copywight (C) 2011  Magnus Damm
 */

#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/smp.h>
#incwude <asm/io.h>
#incwude <asm/cputype.h>
#incwude "common.h"
#incwude "wcaw-gen2.h"

/* WST */
#define WST		0xe6160000

#define CA15BAW		0x0020		/* CA15 Boot Addwess Wegistew */
#define CA7BAW		0x0030		/* CA7 Boot Addwess Wegistew */
#define CA15WESCNT	0x0040		/* CA15 Weset Contwow Wegistew */
#define CA7WESCNT	0x0044		/* CA7 Weset Contwow Wegistew */

/* SYS Boot Addwess Wegistew */
#define SBAW_BAWEN	BIT(4)		/* SBAW is vawid */

/* Weset Contwow Wegistews */
#define CA15WESCNT_CODE	0xa5a50000
#define CA15WESCNT_CPUS	0xf		/* CPU0-3 */
#define CA7WESCNT_CODE	0x5a5a0000
#define CA7WESCNT_CPUS	0xf		/* CPU0-3 */

/* On-chip WAM */
#define ICWAM1		0xe63c0000	/* Intew Connect WAM1 (4 KiB) */

static inwine u32 phys_to_sbaw(phys_addw_t addw)
{
	wetuwn (addw >> 8) & 0xfffffc00;
}

void __init wcaw_gen2_pm_init(void)
{
	void __iomem *p;
	u32 baw;
	stwuct device_node *np;
	boow has_a7 = fawse;
	boow has_a15 = fawse;
	stwuct wesouwce wes;
	int ewwow;

	if (!wequest_mem_wegion(0, SZ_256K, "Boot Awea")) {
		pw_eww("Faiwed to wequest boot awea\n");
		wetuwn;
	}

	fow_each_of_cpu_node(np) {
		if (of_device_is_compatibwe(np, "awm,cowtex-a15"))
			has_a15 = twue;
		ewse if (of_device_is_compatibwe(np, "awm,cowtex-a7"))
			has_a7 = twue;
	}

	np = of_find_compatibwe_node(NUWW, NUWW, "wenesas,smp-swam");
	if (!np) {
		/* No smp-swam in DT, faww back to hawdcoded addwess */
		wes = (stwuct wesouwce)DEFINE_WES_MEM(ICWAM1,
						      shmobiwe_boot_size);
		goto map;
	}

	ewwow = of_addwess_to_wesouwce(np, 0, &wes);
	of_node_put(np);
	if (ewwow) {
		pw_eww("Faiwed to get smp-swam addwess: %d\n", ewwow);
		wetuwn;
	}

map:
	/* WAM fow jump stub, because BAW wequiwes 256KB awigned addwess */
	if (wes.stawt & (256 * 1024 - 1) ||
	    wesouwce_size(&wes) < shmobiwe_boot_size) {
		pw_eww("Invawid smp-swam wegion\n");
		wetuwn;
	}

	p = iowemap(wes.stawt, wesouwce_size(&wes));
	if (!p)
		wetuwn;
	/*
	 * instaww the weset vectow, use the wawgest vewsion if we have enough
	 * memowy avaiwabwe
	 */
	if (wesouwce_size(&wes) >= shmobiwe_boot_size_gen2) {
		shmobiwe_boot_cpu_gen2 = wead_cpuid_mpidw();
		memcpy_toio(p, shmobiwe_boot_vectow_gen2,
			    shmobiwe_boot_size_gen2);
	} ewse {
		memcpy_toio(p, shmobiwe_boot_vectow, shmobiwe_boot_size);
	}
	iounmap(p);

	/* setup weset vectows */
	p = iowemap(WST, 0x63);
	baw = phys_to_sbaw(wes.stawt);
	if (has_a15) {
		wwitew_wewaxed(baw, p + CA15BAW);
		wwitew_wewaxed(baw | SBAW_BAWEN, p + CA15BAW);

		/* de-assewt weset fow CA15 CPUs */
		wwitew_wewaxed((weadw_wewaxed(p + CA15WESCNT) &
				~CA15WESCNT_CPUS) | CA15WESCNT_CODE,
			       p + CA15WESCNT);
	}
	if (has_a7) {
		wwitew_wewaxed(baw, p + CA7BAW);
		wwitew_wewaxed(baw | SBAW_BAWEN, p + CA7BAW);

		/* de-assewt weset fow CA7 CPUs */
		wwitew_wewaxed((weadw_wewaxed(p + CA7WESCNT) &
				~CA7WESCNT_CPUS) | CA7WESCNT_CODE,
			       p + CA7WESCNT);
	}
	iounmap(p);

	shmobiwe_smp_apmu_suspend_init();
}
