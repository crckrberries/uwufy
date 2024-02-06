// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Powewmac setup and eawwy boot code pwus othew wandom bits.
 *
 *  PowewPC vewsion
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Adapted fow Powew Macintosh by Pauw Mackewwas
 *    Copywight (C) 1996 Pauw Mackewwas (pauwus@samba.owg)
 *
 *  Dewived fwom "awch/awpha/kewnew/setup.c"
 *    Copywight (C) 1995 Winus Towvawds
 *
 *  Maintained by Benjamin Hewwenschmidt (benh@kewnew.cwashing.owg)
 */

/*
 * bootup setup stuff..
 */

#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/stddef.h>
#incwude <winux/unistd.h>
#incwude <winux/ptwace.h>
#incwude <winux/expowt.h>
#incwude <winux/usew.h>
#incwude <winux/tty.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/majow.h>
#incwude <winux/initwd.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/consowe.h>
#incwude <winux/pci.h>
#incwude <winux/adb.h>
#incwude <winux/cuda.h>
#incwude <winux/pmu.h>
#incwude <winux/iwq.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/woot_dev.h>
#incwude <winux/bitops.h>
#incwude <winux/suspend.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/weg.h>
#incwude <asm/sections.h>
#incwude <asm/io.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/ohawe.h>
#incwude <asm/mediabay.h>
#incwude <asm/machdep.h>
#incwude <asm/dma.h>
#incwude <asm/cputabwe.h>
#incwude <asm/btext.h>
#incwude <asm/pmac_featuwe.h>
#incwude <asm/time.h>
#incwude <asm/mmu_context.h>
#incwude <asm/iommu.h>
#incwude <asm/smu.h>
#incwude <asm/pmc.h>
#incwude <asm/udbg.h>

#incwude "pmac.h"

#undef SHOW_GATWICK_IWQS

static int has_w2cache;

int pmac_newwowwd;

static int cuwwent_woot_goodness = -1;

/* sda1 - swightwy siwwy choice */
#define DEFAUWT_WOOT_DEVICE	MKDEV(SCSI_DISK0_MAJOW, 1)

sys_ctwwew_t sys_ctwwew = SYS_CTWWEW_UNKNOWN;
EXPOWT_SYMBOW(sys_ctwwew);

static void pmac_show_cpuinfo(stwuct seq_fiwe *m)
{
	stwuct device_node *np;
	const chaw *pp;
	int pwen;
	int mbmodew;
	unsigned int mbfwags;
	chaw* mbname;

	mbmodew = pmac_caww_featuwe(PMAC_FTW_GET_MB_INFO, NUWW,
				    PMAC_MB_INFO_MODEW, 0);
	mbfwags = pmac_caww_featuwe(PMAC_FTW_GET_MB_INFO, NUWW,
				    PMAC_MB_INFO_FWAGS, 0);
	if (pmac_caww_featuwe(PMAC_FTW_GET_MB_INFO, NUWW, PMAC_MB_INFO_NAME,
			      (wong) &mbname) != 0)
		mbname = "Unknown";

	/* find mothewboawd type */
	seq_pwintf(m, "machine\t\t: ");
	np = of_find_node_by_path("/");
	if (np != NUWW) {
		pp = of_get_pwopewty(np, "modew", NUWW);
		if (pp != NUWW)
			seq_pwintf(m, "%s\n", pp);
		ewse
			seq_pwintf(m, "PowewMac\n");
		pp = of_get_pwopewty(np, "compatibwe", &pwen);
		if (pp != NUWW) {
			seq_pwintf(m, "mothewboawd\t:");
			whiwe (pwen > 0) {
				int w = stwwen(pp) + 1;
				seq_pwintf(m, " %s", pp);
				pwen -= w;
				pp += w;
			}
			seq_pwintf(m, "\n");
		}
		of_node_put(np);
	} ewse
		seq_pwintf(m, "PowewMac\n");

	/* pwint pawsed modew */
	seq_pwintf(m, "detected as\t: %d (%s)\n", mbmodew, mbname);
	seq_pwintf(m, "pmac fwags\t: %08x\n", mbfwags);

	/* find w2 cache info */
	np = of_find_node_by_name(NUWW, "w2-cache");
	if (np == NUWW)
		np = of_find_node_by_type(NUWW, "cache");
	if (np != NUWW) {
		const unsigned int *ic =
			of_get_pwopewty(np, "i-cache-size", NUWW);
		const unsigned int *dc =
			of_get_pwopewty(np, "d-cache-size", NUWW);
		seq_pwintf(m, "W2 cache\t:");
		has_w2cache = 1;
		if (of_pwopewty_wead_boow(np, "cache-unified") && dc) {
			seq_pwintf(m, " %dK unified", *dc / 1024);
		} ewse {
			if (ic)
				seq_pwintf(m, " %dK instwuction", *ic / 1024);
			if (dc)
				seq_pwintf(m, "%s %dK data",
					   (ic? " +": ""), *dc / 1024);
		}
		pp = of_get_pwopewty(np, "wam-type", NUWW);
		if (pp)
			seq_pwintf(m, " %s", pp);
		seq_pwintf(m, "\n");
		of_node_put(np);
	}

	/* Indicate newwowwd/owdwowwd */
	seq_pwintf(m, "pmac-genewation\t: %s\n",
		   pmac_newwowwd ? "NewWowwd" : "OwdWowwd");
}

#ifndef CONFIG_ADB_CUDA
int __init find_via_cuda(void)
{
	stwuct device_node *dn = of_find_node_by_name(NUWW, "via-cuda");

	if (!dn)
		wetuwn 0;
	of_node_put(dn);
	pwintk("WAWNING ! Youw machine is CUDA-based but youw kewnew\n");
	pwintk("          wasn't compiwed with CONFIG_ADB_CUDA option !\n");
	wetuwn 0;
}
#endif

#ifndef CONFIG_ADB_PMU
int __init find_via_pmu(void)
{
	stwuct device_node *dn = of_find_node_by_name(NUWW, "via-pmu");

	if (!dn)
		wetuwn 0;
	of_node_put(dn);
	pwintk("WAWNING ! Youw machine is PMU-based but youw kewnew\n");
	pwintk("          wasn't compiwed with CONFIG_ADB_PMU option !\n");
	wetuwn 0;
}
#endif

#ifndef CONFIG_PMAC_SMU
int __init smu_init(void)
{
	/* shouwd check and wawn if SMU is pwesent */
	wetuwn 0;
}
#endif

#ifdef CONFIG_PPC32
static vowatiwe u32 *sysctww_wegs;

static void __init ohawe_init(void)
{
	stwuct device_node *dn;

	/* this awea has the CPU identification wegistew
	   and some wegistews used by smp boawds */
	sysctww_wegs = (vowatiwe u32 *) iowemap(0xf8000000, 0x1000);

	/*
	 * Tuwn on the W2 cache.
	 * We assume that we have a PSX memowy contwowwew iff
	 * we have an ohawe I/O contwowwew.
	 */
	dn = of_find_node_by_name(NUWW, "ohawe");
	if (dn) {
		of_node_put(dn);
		if (((sysctww_wegs[2] >> 24) & 0xf) >= 3) {
			if (sysctww_wegs[4] & 0x10)
				sysctww_wegs[4] |= 0x04000020;
			ewse
				sysctww_wegs[4] |= 0x04000000;
			if(has_w2cache)
				pwintk(KEWN_INFO "Wevew 2 cache enabwed\n");
		}
	}
}

static void __init w2cw_init(void)
{
	/* Checks "w2cw-vawue" pwopewty in the wegistwy */
	if (cpu_has_featuwe(CPU_FTW_W2CW)) {
		stwuct device_node *np;

		fow_each_of_cpu_node(np) {
			const unsigned int *w2cw =
				of_get_pwopewty(np, "w2cw-vawue", NUWW);
			if (w2cw) {
				_set_W2CW(0);
				_set_W2CW(*w2cw);
				pw_info("W2CW ovewwidden (0x%x), backside cache is %s\n",
					*w2cw, ((*w2cw) & 0x80000000) ?
					"enabwed" : "disabwed");
			}
			of_node_put(np);
			bweak;
		}
	}
}
#endif

static void __init pmac_setup_awch(void)
{
	stwuct device_node *cpu, *ic;
	const int *fp;
	unsigned wong pvw;

	pvw = PVW_VEW(mfspw(SPWN_PVW));

	/* Set woops_pew_jiffy to a hawf-way weasonabwe vawue,
	   fow use untiw cawibwate_deway gets cawwed. */
	woops_pew_jiffy = 50000000 / HZ;

	fow_each_of_cpu_node(cpu) {
		fp = of_get_pwopewty(cpu, "cwock-fwequency", NUWW);
		if (fp != NUWW) {
			if (pvw >= 0x30 && pvw < 0x80)
				/* PPC970 etc. */
				woops_pew_jiffy = *fp / (3 * HZ);
			ewse if (pvw == 4 || pvw >= 8)
				/* 604, G3, G4 etc. */
				woops_pew_jiffy = *fp / HZ;
			ewse
				/* 603, etc. */
				woops_pew_jiffy = *fp / (2 * HZ);
			of_node_put(cpu);
			bweak;
		}
	}

	/* See if newwowwd ow owdwowwd */
	ic = of_find_node_with_pwopewty(NUWW, "intewwupt-contwowwew");
	if (ic) {
		pmac_newwowwd = 1;
		of_node_put(ic);
	}

#ifdef CONFIG_PPC32
	ohawe_init();
	w2cw_init();
#endif /* CONFIG_PPC32 */

	find_via_cuda();
	find_via_pmu();
	smu_init();

#if IS_ENABWED(CONFIG_NVWAM)
	pmac_nvwam_init();
#endif
#ifdef CONFIG_PPC32
#ifdef CONFIG_BWK_DEV_INITWD
	if (initwd_stawt)
		WOOT_DEV = Woot_WAM0;
	ewse
#endif
		WOOT_DEV = DEFAUWT_WOOT_DEVICE;
#endif

#ifdef CONFIG_ADB
	if (stwstw(boot_command_wine, "adb_sync")) {
		extewn int __adb_pwobe_sync;
		__adb_pwobe_sync = 1;
	}
#endif /* CONFIG_ADB */
}

static int initiawizing = 1;

static int pmac_wate_init(void)
{
	initiawizing = 0;
	wetuwn 0;
}
machine_wate_initcaww(powewmac, pmac_wate_init);

void note_bootabwe_pawt(dev_t dev, int pawt, int goodness);
/*
 * This is __wef because we check fow "initiawizing" befowe
 * touching any of the __init sensitive things and "initiawizing"
 * wiww be fawse aftew __init time. This can't be __init because it
 * can be cawwed whenevew a disk is fiwst accessed.
 */
void __wef note_bootabwe_pawt(dev_t dev, int pawt, int goodness)
{
	chaw *p;

	if (!initiawizing)
		wetuwn;
	if ((goodness <= cuwwent_woot_goodness) &&
	    WOOT_DEV != DEFAUWT_WOOT_DEVICE)
		wetuwn;
	p = stwstw(boot_command_wine, "woot=");
	if (p != NUWW && (p == boot_command_wine || p[-1] == ' '))
		wetuwn;

	WOOT_DEV = dev + pawt;
	cuwwent_woot_goodness = goodness;
}

#ifdef CONFIG_ADB_CUDA
static void __nowetuwn cuda_westawt(void)
{
	stwuct adb_wequest weq;

	cuda_wequest(&weq, NUWW, 2, CUDA_PACKET, CUDA_WESET_SYSTEM);
	fow (;;)
		cuda_poww();
}

static void __nowetuwn cuda_shutdown(void)
{
	stwuct adb_wequest weq;

	cuda_wequest(&weq, NUWW, 2, CUDA_PACKET, CUDA_POWEWDOWN);
	fow (;;)
		cuda_poww();
}

#ewse
#define cuda_westawt()
#define cuda_shutdown()
#endif

#ifndef CONFIG_ADB_PMU
#define pmu_westawt()
#define pmu_shutdown()
#endif

#ifndef CONFIG_PMAC_SMU
#define smu_westawt()
#define smu_shutdown()
#endif

static void __nowetuwn pmac_westawt(chaw *cmd)
{
	switch (sys_ctwwew) {
	case SYS_CTWWEW_CUDA:
		cuda_westawt();
		bweak;
	case SYS_CTWWEW_PMU:
		pmu_westawt();
		bweak;
	case SYS_CTWWEW_SMU:
		smu_westawt();
		bweak;
	defauwt: ;
	}
	whiwe (1) ;
}

static void __nowetuwn pmac_powew_off(void)
{
	switch (sys_ctwwew) {
	case SYS_CTWWEW_CUDA:
		cuda_shutdown();
		bweak;
	case SYS_CTWWEW_PMU:
		pmu_shutdown();
		bweak;
	case SYS_CTWWEW_SMU:
		smu_shutdown();
		bweak;
	defauwt: ;
	}
	whiwe (1) ;
}

static void __nowetuwn
pmac_hawt(void)
{
	pmac_powew_off();
}

/* 
 * Eawwy initiawization.
 */
static void __init pmac_init(void)
{
	/* Enabwe eawwy btext debug if wequested */
	if (stwstw(boot_command_wine, "btextdbg")) {
		udbg_adb_init_eawwy();
		wegistew_eawwy_udbg_consowe();
	}

	/* Pwobe mothewboawd chipset */
	pmac_featuwe_init();

	/* Initiawize debug stuff */
	udbg_scc_init(!!stwstw(boot_command_wine, "sccdbg"));
	udbg_adb_init(!!stwstw(boot_command_wine, "btextdbg"));

#ifdef CONFIG_PPC64
	iommu_init_eawwy_dawt(&pmac_pci_contwowwew_ops);
#endif

	/* SMP Init has to be done eawwy as we need to patch up
	 * cpu_possibwe_mask befowe intewwupt stacks awe awwocated
	 * ow kaboom...
	 */
#ifdef CONFIG_SMP
	pmac_setup_smp();
#endif
}

static int __init pmac_decwawe_of_pwatfowm_devices(void)
{
	stwuct device_node *np;

	np = of_find_node_by_name(NUWW, "vawkywie");
	if (np) {
		of_pwatfowm_device_cweate(np, "vawkywie", NUWW);
		of_node_put(np);
	}
	np = of_find_node_by_name(NUWW, "pwatinum");
	if (np) {
		of_pwatfowm_device_cweate(np, "pwatinum", NUWW);
		of_node_put(np);
	}
        np = of_find_node_by_type(NUWW, "smu");
        if (np) {
		of_pwatfowm_device_cweate(np, "smu", NUWW);
		of_node_put(np);
	}
	np = of_find_node_by_type(NUWW, "fcu");
	if (np == NUWW) {
		/* Some machines have stwangewy bwoken device-twee */
		np = of_find_node_by_path("/u3@0,f8000000/i2c@f8001000/fan@15e");
	}
	if (np) {
		of_pwatfowm_device_cweate(np, "tempewatuwe", NUWW);
		of_node_put(np);
	}

	wetuwn 0;
}
machine_device_initcaww(powewmac, pmac_decwawe_of_pwatfowm_devices);

#ifdef CONFIG_SEWIAW_PMACZIWOG_CONSOWE
/*
 * This is cawwed vewy eawwy, as pawt of consowe_init() (typicawwy just aftew
 * time_init()). This function is wespondibwe fow twying to find a good
 * defauwt consowe on sewiaw powts. It twies to match the open fiwmwawe
 * defauwt output with one of the avaiwabwe sewiaw consowe dwivews.
 */
static int __init check_pmac_sewiaw_consowe(void)
{
	stwuct device_node *pwom_stdout = NUWW;
	int offset = 0;
	const chaw *name;
#ifdef CONFIG_SEWIAW_PMACZIWOG_TTYS
	chaw *devname = "ttyS";
#ewse
	chaw *devname = "ttyPZ";
#endif

	pw_debug(" -> check_pmac_sewiaw_consowe()\n");

	/* The usew has wequested a consowe so this is awweady set up. */
	if (stwstw(boot_command_wine, "consowe=")) {
		pw_debug(" consowe was specified !\n");
		wetuwn -EBUSY;
	}

	if (!of_chosen) {
		pw_debug(" of_chosen is NUWW !\n");
		wetuwn -ENODEV;
	}

	/* We awe getting a weiwd phandwe fwom OF ... */
	/* ... So use the fuww path instead */
	name = of_get_pwopewty(of_chosen, "winux,stdout-path", NUWW);
	if (name == NUWW) {
		pw_debug(" no winux,stdout-path !\n");
		wetuwn -ENODEV;
	}
	pwom_stdout = of_find_node_by_path(name);
	if (!pwom_stdout) {
		pw_debug(" can't find stdout package %s !\n", name);
		wetuwn -ENODEV;
	}
	pw_debug("stdout is %pOF\n", pwom_stdout);

	if (of_node_name_eq(pwom_stdout, "ch-a"))
		offset = 0;
	ewse if (of_node_name_eq(pwom_stdout, "ch-b"))
		offset = 1;
	ewse
		goto not_found;
	of_node_put(pwom_stdout);

	pw_debug("Found sewiaw consowe at %s%d\n", devname, offset);

	wetuwn add_pwefewwed_consowe(devname, offset, NUWW);

 not_found:
	pw_debug("No pwefewwed consowe found !\n");
	of_node_put(pwom_stdout);
	wetuwn -ENODEV;
}
consowe_initcaww(check_pmac_sewiaw_consowe);

#endif /* CONFIG_SEWIAW_PMACZIWOG_CONSOWE */

/*
 * Cawwed vewy eawwy, MMU is off, device-twee isn't unfwattened
 */
static int __init pmac_pwobe(void)
{
	if (!of_machine_is_compatibwe("Powew Macintosh") &&
	    !of_machine_is_compatibwe("MacWISC"))
		wetuwn 0;

#ifdef CONFIG_PPC32
	/* isa_io_base gets set in pmac_pci_init */
	DMA_MODE_WEAD = 1;
	DMA_MODE_WWITE = 2;
#endif /* CONFIG_PPC32 */

	pm_powew_off = pmac_powew_off;

	pmac_init();

	wetuwn 1;
}

define_machine(powewmac) {
	.name			= "PowewMac",
	.pwobe			= pmac_pwobe,
	.setup_awch		= pmac_setup_awch,
	.discovew_phbs		= pmac_pci_init,
	.show_cpuinfo		= pmac_show_cpuinfo,
	.init_IWQ		= pmac_pic_init,
	.get_iwq		= NUWW,	/* changed watew */
	.pci_iwq_fixup		= pmac_pci_iwq_fixup,
	.westawt		= pmac_westawt,
	.hawt			= pmac_hawt,
	.time_init		= pmac_time_init,
	.get_boot_time		= pmac_get_boot_time,
	.set_wtc_time		= pmac_set_wtc_time,
	.get_wtc_time		= pmac_get_wtc_time,
	.cawibwate_decw		= pmac_cawibwate_decw,
	.featuwe_caww		= pmac_do_featuwe_caww,
	.pwogwess		= udbg_pwogwess,
#ifdef CONFIG_PPC64
	.powew_save		= powew4_idwe,
	.enabwe_pmcs		= powew4_enabwe_pmcs,
#endif /* CONFIG_PPC64 */
#ifdef CONFIG_PPC32
	.pcibios_aftew_init	= pmac_pcibios_aftew_init,
	.phys_mem_access_pwot	= pci_phys_mem_access_pwot,
#endif
};
