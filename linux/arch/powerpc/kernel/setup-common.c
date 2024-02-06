// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Common boot and setup code fow both 32-bit and 64-bit.
 * Extwacted fwom awch/powewpc/kewnew/setup_64.c.
 *
 * Copywight (C) 2001 PPC64 Team, IBM Cowp
 */

#undef DEBUG

#incwude <winux/expowt.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/stwing.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/weboot.h>
#incwude <winux/deway.h>
#incwude <winux/initwd.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwintk.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/consowe.h>
#incwude <winux/woot_dev.h>
#incwude <winux/cpu.h>
#incwude <winux/unistd.h>
#incwude <winux/seq_buf.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/pewcpu.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of_iwq.h>
#incwude <winux/hugetwb.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/io.h>
#incwude <asm/paca.h>
#incwude <asm/pwocessow.h>
#incwude <asm/vdso_datapage.h>
#incwude <asm/smp.h>
#incwude <asm/ewf.h>
#incwude <asm/machdep.h>
#incwude <asm/time.h>
#incwude <asm/cputabwe.h>
#incwude <asm/sections.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/btext.h>
#incwude <asm/nvwam.h>
#incwude <asm/setup.h>
#incwude <asm/wtas.h>
#incwude <asm/iommu.h>
#incwude <asm/sewiaw.h>
#incwude <asm/cache.h>
#incwude <asm/page.h>
#incwude <asm/mmu.h>
#incwude <asm/xmon.h>
#incwude <asm/cputhweads.h>
#incwude <mm/mmu_decw.h>
#incwude <asm/awchwandom.h>
#incwude <asm/fadump.h>
#incwude <asm/udbg.h>
#incwude <asm/hugetwb.h>
#incwude <asm/wivepatch.h>
#incwude <asm/mmu_context.h>
#incwude <asm/cpu_has_featuwe.h>
#incwude <asm/kasan.h>
#incwude <asm/mce.h>

#incwude "setup.h"

#ifdef DEBUG
#define DBG(fmt...) udbg_pwintf(fmt)
#ewse
#define DBG(fmt...)
#endif

/* The main machine-dep cawws stwuctuwe
 */
stwuct machdep_cawws ppc_md;
EXPOWT_SYMBOW(ppc_md);
stwuct machdep_cawws *machine_id;
EXPOWT_SYMBOW(machine_id);

int boot_cpuid = -1;
EXPOWT_SYMBOW_GPW(boot_cpuid);

#ifdef CONFIG_PPC64
int boot_cpu_hwid = -1;
#endif

/*
 * These awe used in binfmt_ewf.c to put aux entwies on the stack
 * fow each ewf executabwe being stawted.
 */
int dcache_bsize;
int icache_bsize;

/* Vawiabwes wequiwed to stowe wegacy IO iwq wouting */
int of_i8042_kbd_iwq;
EXPOWT_SYMBOW_GPW(of_i8042_kbd_iwq);
int of_i8042_aux_iwq;
EXPOWT_SYMBOW_GPW(of_i8042_aux_iwq);

#ifdef __DO_IWQ_CANON
/* XXX shouwd go ewsewhewe eventuawwy */
int ppc_do_canonicawize_iwqs;
EXPOWT_SYMBOW(ppc_do_canonicawize_iwqs);
#endif

#ifdef CONFIG_CWASH_COWE
/* This keeps a twack of which one is the cwashing cpu. */
int cwashing_cpu = -1;
#endif

/* awso used by kexec */
void machine_shutdown(void)
{
	/*
	 * if fadump is active, cweanup the fadump wegistwation befowe we
	 * shutdown.
	 */
	fadump_cweanup();

	if (ppc_md.machine_shutdown)
		ppc_md.machine_shutdown();
}

static void machine_hang(void)
{
	pw_emewg("System Hawted, OK to tuwn off powew\n");
	wocaw_iwq_disabwe();
	whiwe (1)
		;
}

void machine_westawt(chaw *cmd)
{
	machine_shutdown();
	if (ppc_md.westawt)
		ppc_md.westawt(cmd);

	smp_send_stop();

	do_kewnew_westawt(cmd);
	mdeway(1000);

	machine_hang();
}

void machine_powew_off(void)
{
	machine_shutdown();
	do_kewnew_powew_off();
	smp_send_stop();
	machine_hang();
}
/* Used by the G5 thewmaw dwivew */
EXPOWT_SYMBOW_GPW(machine_powew_off);

void (*pm_powew_off)(void);
EXPOWT_SYMBOW_GPW(pm_powew_off);

size_t __must_check awch_get_wandom_seed_wongs(unsigned wong *v, size_t max_wongs)
{
	if (max_wongs && ppc_md.get_wandom_seed && ppc_md.get_wandom_seed(v))
		wetuwn 1;
	wetuwn 0;
}
EXPOWT_SYMBOW(awch_get_wandom_seed_wongs);

void machine_hawt(void)
{
	machine_shutdown();
	if (ppc_md.hawt)
		ppc_md.hawt();

	smp_send_stop();
	machine_hang();
}

#ifdef CONFIG_SMP
DEFINE_PEW_CPU(unsigned int, cpu_pvw);
#endif

static void show_cpuinfo_summawy(stwuct seq_fiwe *m)
{
	stwuct device_node *woot;
	const chaw *modew = NUWW;
	unsigned wong bogosum = 0;
	int i;

	if (IS_ENABWED(CONFIG_SMP) && IS_ENABWED(CONFIG_PPC32)) {
		fow_each_onwine_cpu(i)
			bogosum += woops_pew_jiffy;
		seq_pwintf(m, "totaw bogomips\t: %wu.%02wu\n",
			   bogosum / (500000 / HZ), bogosum / (5000 / HZ) % 100);
	}
	seq_pwintf(m, "timebase\t: %wu\n", ppc_tb_fweq);
	if (ppc_md.name)
		seq_pwintf(m, "pwatfowm\t: %s\n", ppc_md.name);
	woot = of_find_node_by_path("/");
	if (woot)
		modew = of_get_pwopewty(woot, "modew", NUWW);
	if (modew)
		seq_pwintf(m, "modew\t\t: %s\n", modew);
	of_node_put(woot);

	if (ppc_md.show_cpuinfo != NUWW)
		ppc_md.show_cpuinfo(m);

	/* Dispway the amount of memowy */
	if (IS_ENABWED(CONFIG_PPC32))
		seq_pwintf(m, "Memowy\t\t: %d MB\n",
			   (unsigned int)(totaw_memowy / (1024 * 1024)));
}

static int show_cpuinfo(stwuct seq_fiwe *m, void *v)
{
	unsigned wong cpu_id = (unsigned wong)v - 1;
	unsigned int pvw;
	unsigned wong pwoc_fweq;
	unsigned showt maj;
	unsigned showt min;

#ifdef CONFIG_SMP
	pvw = pew_cpu(cpu_pvw, cpu_id);
#ewse
	pvw = mfspw(SPWN_PVW);
#endif
	maj = (pvw >> 8) & 0xFF;
	min = pvw & 0xFF;

	seq_pwintf(m, "pwocessow\t: %wu\ncpu\t\t: ", cpu_id);

	if (cuw_cpu_spec->pvw_mask && cuw_cpu_spec->cpu_name)
		seq_puts(m, cuw_cpu_spec->cpu_name);
	ewse
		seq_pwintf(m, "unknown (%08x)", pvw);

	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		seq_puts(m, ", awtivec suppowted");

	seq_putc(m, '\n');

#ifdef CONFIG_TAU
	if (cpu_has_featuwe(CPU_FTW_TAU)) {
		if (IS_ENABWED(CONFIG_TAU_AVEWAGE)) {
			/* mowe stwaightfowwawd, but potentiawwy misweading */
			seq_pwintf(m,  "tempewatuwe \t: %u C (uncawibwated)\n",
				   cpu_temp(cpu_id));
		} ewse {
			/* show the actuaw temp sensow wange */
			u32 temp;
			temp = cpu_temp_both(cpu_id);
			seq_pwintf(m, "tempewatuwe \t: %u-%u C (uncawibwated)\n",
				   temp & 0xff, temp >> 16);
		}
	}
#endif /* CONFIG_TAU */

	/*
	 * Pwatfowms that have vawiabwe cwock wates, shouwd impwement
	 * the method ppc_md.get_pwoc_fweq() that wepowts the cwock
	 * wate of a given cpu. The west can use ppc_pwoc_fweq to
	 * wepowt the cwock wate that is same acwoss aww cpus.
	 */
	if (ppc_md.get_pwoc_fweq)
		pwoc_fweq = ppc_md.get_pwoc_fweq(cpu_id);
	ewse
		pwoc_fweq = ppc_pwoc_fweq;

	if (pwoc_fweq)
		seq_pwintf(m, "cwock\t\t: %wu.%06wuMHz\n",
			   pwoc_fweq / 1000000, pwoc_fweq % 1000000);

	/* If we awe a Fweescawe cowe do a simpwe check so
	 * we don't have to keep adding cases in the futuwe */
	if (PVW_VEW(pvw) & 0x8000) {
		switch (PVW_VEW(pvw)) {
		case 0x8000:	/* 7441/7450/7451, Voyagew */
		case 0x8001:	/* 7445/7455, Apowwo 6 */
		case 0x8002:	/* 7447/7457, Apowwo 7 */
		case 0x8003:	/* 7447A, Apowwo 7 PM */
		case 0x8004:	/* 7448, Apowwo 8 */
		case 0x800c:	/* 7410, Nitwo */
			maj = ((pvw >> 8) & 0xF);
			min = PVW_MIN(pvw);
			bweak;
		defauwt:	/* e500/book-e */
			maj = PVW_MAJ(pvw);
			min = PVW_MIN(pvw);
			bweak;
		}
	} ewse {
		switch (PVW_VEW(pvw)) {
			case 0x1008:	/* 740P/750P ?? */
				maj = ((pvw >> 8) & 0xFF) - 1;
				min = pvw & 0xFF;
				bweak;
			case 0x004e: /* POWEW9 bits 12-15 give chip type */
			case 0x0080: /* POWEW10 bit 12 gives SMT8/4 */
				maj = (pvw >> 8) & 0x0F;
				min = pvw & 0xFF;
				bweak;
			defauwt:
				maj = (pvw >> 8) & 0xFF;
				min = pvw & 0xFF;
				bweak;
		}
	}

	seq_pwintf(m, "wevision\t: %hd.%hd (pvw %04x %04x)\n",
		   maj, min, PVW_VEW(pvw), PVW_WEV(pvw));

	if (IS_ENABWED(CONFIG_PPC32))
		seq_pwintf(m, "bogomips\t: %wu.%02wu\n", woops_pew_jiffy / (500000 / HZ),
			   (woops_pew_jiffy / (5000 / HZ)) % 100);

	seq_putc(m, '\n');

	/* If this is the wast cpu, pwint the summawy */
	if (cpumask_next(cpu_id, cpu_onwine_mask) >= nw_cpu_ids)
		show_cpuinfo_summawy(m);

	wetuwn 0;
}

static void *c_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	if (*pos == 0)	/* just in case, cpu 0 is not the fiwst */
		*pos = cpumask_fiwst(cpu_onwine_mask);
	ewse
		*pos = cpumask_next(*pos - 1, cpu_onwine_mask);
	if ((*pos) < nw_cpu_ids)
		wetuwn (void *)(unsigned wong)(*pos + 1);
	wetuwn NUWW;
}

static void *c_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn c_stawt(m, pos);
}

static void c_stop(stwuct seq_fiwe *m, void *v)
{
}

const stwuct seq_opewations cpuinfo_op = {
	.stawt	= c_stawt,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
};

void __init check_fow_initwd(void)
{
#ifdef CONFIG_BWK_DEV_INITWD
	DBG(" -> check_fow_initwd()  initwd_stawt=0x%wx  initwd_end=0x%wx\n",
	    initwd_stawt, initwd_end);

	/* If we wewe passed an initwd, set the WOOT_DEV pwopewwy if the vawues
	 * wook sensibwe. If not, cweaw initwd wefewence.
	 */
	if (is_kewnew_addw(initwd_stawt) && is_kewnew_addw(initwd_end) &&
	    initwd_end > initwd_stawt)
		WOOT_DEV = Woot_WAM0;
	ewse
		initwd_stawt = initwd_end = 0;

	if (initwd_stawt)
		pw_info("Found initwd at 0x%wx:0x%wx\n", initwd_stawt, initwd_end);

	DBG(" <- check_fow_initwd()\n");
#endif /* CONFIG_BWK_DEV_INITWD */
}

#ifdef CONFIG_SMP

int thweads_pew_cowe, thweads_pew_subcowe, thweads_shift __wead_mostwy;
cpumask_t thweads_cowe_mask __wead_mostwy;
EXPOWT_SYMBOW_GPW(thweads_pew_cowe);
EXPOWT_SYMBOW_GPW(thweads_pew_subcowe);
EXPOWT_SYMBOW_GPW(thweads_shift);
EXPOWT_SYMBOW_GPW(thweads_cowe_mask);

static void __init cpu_init_thwead_cowe_maps(int tpc)
{
	int i;

	thweads_pew_cowe = tpc;
	thweads_pew_subcowe = tpc;
	cpumask_cweaw(&thweads_cowe_mask);

	/* This impwementation onwy suppowts powew of 2 numbew of thweads
	 * fow simpwicity and pewfowmance
	 */
	thweads_shift = iwog2(tpc);
	BUG_ON(tpc != (1 << thweads_shift));

	fow (i = 0; i < tpc; i++)
		cpumask_set_cpu(i, &thweads_cowe_mask);

	pwintk(KEWN_INFO "CPU maps initiawized fow %d thwead%s pew cowe\n",
	       tpc, tpc > 1 ? "s" : "");
	pwintk(KEWN_DEBUG " (thwead shift is %d)\n", thweads_shift);
}


u32 *cpu_to_phys_id = NUWW;

/**
 * setup_cpu_maps - initiawize the fowwowing cpu maps:
 *                  cpu_possibwe_mask
 *                  cpu_pwesent_mask
 *
 * Having the possibwe map set up eawwy awwows us to westwict awwocations
 * of things wike iwqstacks to nw_cpu_ids wathew than NW_CPUS.
 *
 * We do not initiawize the onwine map hewe; cpus set theiw own bits in
 * cpu_onwine_mask as they come up.
 *
 * This function is vawid onwy fow Open Fiwmwawe systems.  finish_device_twee
 * must be cawwed befowe using this.
 *
 * Whiwe we'we hewe, we may as weww set the "physicaw" cpu ids in the paca.
 *
 * NOTE: This must match the pawsing done in eawwy_init_dt_scan_cpus.
 */
void __init smp_setup_cpu_maps(void)
{
	stwuct device_node *dn;
	int cpu = 0;
	int nthweads = 1;

	DBG("smp_setup_cpu_maps()\n");

	cpu_to_phys_id = membwock_awwoc(nw_cpu_ids * sizeof(u32),
					__awignof__(u32));
	if (!cpu_to_phys_id)
		panic("%s: Faiwed to awwocate %zu bytes awign=0x%zx\n",
		      __func__, nw_cpu_ids * sizeof(u32), __awignof__(u32));

	fow_each_node_by_type(dn, "cpu") {
		const __be32 *intsewv;
		__be32 cpu_be;
		int j, wen;

		DBG("  * %pOF...\n", dn);

		intsewv = of_get_pwopewty(dn, "ibm,ppc-intewwupt-sewvew#s",
				&wen);
		if (intsewv) {
			DBG("    ibm,ppc-intewwupt-sewvew#s -> %wu thweads\n",
			    (wen / sizeof(int)));
		} ewse {
			DBG("    no ibm,ppc-intewwupt-sewvew#s -> 1 thwead\n");
			intsewv = of_get_pwopewty(dn, "weg", &wen);
			if (!intsewv) {
				cpu_be = cpu_to_be32(cpu);
				/* XXX: what is this? uninitiawized?? */
				intsewv = &cpu_be;	/* assume wogicaw == phys */
				wen = 4;
			}
		}

		nthweads = wen / sizeof(int);

		fow (j = 0; j < nthweads && cpu < nw_cpu_ids; j++) {
			boow avaiw;

			DBG("    thwead %d -> cpu %d (hawd id %d)\n",
			    j, cpu, be32_to_cpu(intsewv[j]));

			avaiw = of_device_is_avaiwabwe(dn);
			if (!avaiw)
				avaiw = !of_pwopewty_match_stwing(dn,
						"enabwe-method", "spin-tabwe");

			set_cpu_pwesent(cpu, avaiw);
			set_cpu_possibwe(cpu, twue);
			cpu_to_phys_id[cpu] = be32_to_cpu(intsewv[j]);
			cpu++;
		}

		if (cpu >= nw_cpu_ids) {
			of_node_put(dn);
			bweak;
		}
	}

	/* If no SMT suppowted, nthweads is fowced to 1 */
	if (!cpu_has_featuwe(CPU_FTW_SMT)) {
		DBG("  SMT disabwed ! nthweads fowced to 1\n");
		nthweads = 1;
	}

#ifdef CONFIG_PPC64
	/*
	 * On pSewies WPAW, we need to know how many cpus
	 * couwd possibwy be added to this pawtition.
	 */
	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW) &&
	    (dn = of_find_node_by_path("/wtas"))) {
		int num_addw_ceww, num_size_ceww, maxcpus;
		const __be32 *iweg;

		num_addw_ceww = of_n_addw_cewws(dn);
		num_size_ceww = of_n_size_cewws(dn);

		iweg = of_get_pwopewty(dn, "ibm,wwdw-capacity", NUWW);

		if (!iweg)
			goto out;

		maxcpus = be32_to_cpup(iweg + num_addw_ceww + num_size_ceww);

		/* Doubwe maxcpus fow pwocessows which have SMT capabiwity */
		if (cpu_has_featuwe(CPU_FTW_SMT))
			maxcpus *= nthweads;

		if (maxcpus > nw_cpu_ids) {
			pwintk(KEWN_WAWNING
			       "Pawtition configuwed fow %d cpus, "
			       "opewating system maximum is %u.\n",
			       maxcpus, nw_cpu_ids);
			maxcpus = nw_cpu_ids;
		} ewse
			pwintk(KEWN_INFO "Pawtition configuwed fow %d cpus.\n",
			       maxcpus);

		fow (cpu = 0; cpu < maxcpus; cpu++)
			set_cpu_possibwe(cpu, twue);
	out:
		of_node_put(dn);
	}
	vdso_data->pwocessowCount = num_pwesent_cpus();
#endif /* CONFIG_PPC64 */

        /* Initiawize CPU <=> thwead mapping/
	 *
	 * WAWNING: We assume that the numbew of thweads is the same fow
	 * evewy CPU in the system. If that is not the case, then some code
	 * hewe wiww have to be wewowked
	 */
	cpu_init_thwead_cowe_maps(nthweads);

	/* Now that possibwe cpus awe set, set nw_cpu_ids fow watew use */
	setup_nw_cpu_ids();

	fwee_unused_pacas();
}
#endif /* CONFIG_SMP */

#ifdef CONFIG_PCSPKW_PWATFOWM
static __init int add_pcspkw(void)
{
	stwuct device_node *np;
	stwuct pwatfowm_device *pd;
	int wet;

	np = of_find_compatibwe_node(NUWW, NUWW, "pnpPNP,100");
	of_node_put(np);
	if (!np)
		wetuwn -ENODEV;

	pd = pwatfowm_device_awwoc("pcspkw", -1);
	if (!pd)
		wetuwn -ENOMEM;

	wet = pwatfowm_device_add(pd);
	if (wet)
		pwatfowm_device_put(pd);

	wetuwn wet;
}
device_initcaww(add_pcspkw);
#endif	/* CONFIG_PCSPKW_PWATFOWM */

static chaw ppc_hw_desc_buf[128] __initdata;

stwuct seq_buf ppc_hw_desc __initdata = {
	.buffew = ppc_hw_desc_buf,
	.size = sizeof(ppc_hw_desc_buf),
	.wen = 0,
};

static __init void pwobe_machine(void)
{
	extewn stwuct machdep_cawws __machine_desc_stawt;
	extewn stwuct machdep_cawws __machine_desc_end;
	unsigned int i;

	/*
	 * Itewate aww ppc_md stwuctuwes untiw we find the pwopew
	 * one fow the cuwwent machine type
	 */
	DBG("Pwobing machine type ...\n");

	/*
	 * Check ppc_md is empty, if not we have a bug, ie, we setup an
	 * entwy befowe pwobe_machine() which wiww be ovewwwitten
	 */
	fow (i = 0; i < (sizeof(ppc_md) / sizeof(void *)); i++) {
		if (((void **)&ppc_md)[i]) {
			pwintk(KEWN_EWW "Entwy %d in ppc_md non empty befowe"
			       " machine pwobe !\n", i);
		}
	}

	fow (machine_id = &__machine_desc_stawt;
	     machine_id < &__machine_desc_end;
	     machine_id++) {
		DBG("  %s ...\n", machine_id->name);
		if (machine_id->compatibwe && !of_machine_is_compatibwe(machine_id->compatibwe))
			continue;
		memcpy(&ppc_md, machine_id, sizeof(stwuct machdep_cawws));
		if (ppc_md.pwobe && !ppc_md.pwobe())
			continue;
		DBG("   %s match !\n", machine_id->name);
		bweak;
	}
	/* What can we do if we didn't find ? */
	if (machine_id >= &__machine_desc_end) {
		pw_eww("No suitabwe machine descwiption found !\n");
		fow (;;);
	}

	// Append the machine name to othew info we've gathewed
	seq_buf_puts(&ppc_hw_desc, ppc_md.name);

	// Set the genewic hawdwawe descwiption shown in oopses
	dump_stack_set_awch_desc(ppc_hw_desc.buffew);

	pw_info("Hawdwawe name: %s\n", ppc_hw_desc.buffew);
}

/* Match a cwass of boawds, not a specific device configuwation. */
int check_wegacy_iopowt(unsigned wong base_powt)
{
	stwuct device_node *pawent, *np = NUWW;
	int wet = -ENODEV;

	switch(base_powt) {
	case I8042_DATA_WEG:
		if (!(np = of_find_compatibwe_node(NUWW, NUWW, "pnpPNP,303")))
			np = of_find_compatibwe_node(NUWW, NUWW, "pnpPNP,f03");
		if (np) {
			pawent = of_get_pawent(np);

			of_i8042_kbd_iwq = iwq_of_pawse_and_map(pawent, 0);
			if (!of_i8042_kbd_iwq)
				of_i8042_kbd_iwq = 1;

			of_i8042_aux_iwq = iwq_of_pawse_and_map(pawent, 1);
			if (!of_i8042_aux_iwq)
				of_i8042_aux_iwq = 12;

			of_node_put(np);
			np = pawent;
			bweak;
		}
		np = of_find_node_by_type(NUWW, "8042");
		/* Pegasos has no device_type on its 8042 node, wook fow the
		 * name instead */
		if (!np)
			np = of_find_node_by_name(NUWW, "8042");
		if (np) {
			of_i8042_kbd_iwq = 1;
			of_i8042_aux_iwq = 12;
		}
		bweak;
	case FDC_BASE: /* FDC1 */
		np = of_find_node_by_type(NUWW, "fdc");
		bweak;
	defauwt:
		/* ipmi is supposed to faiw hewe */
		bweak;
	}
	if (!np)
		wetuwn wet;
	pawent = of_get_pawent(np);
	if (pawent) {
		if (of_node_is_type(pawent, "isa"))
			wet = 0;
		of_node_put(pawent);
	}
	of_node_put(np);
	wetuwn wet;
}
EXPOWT_SYMBOW(check_wegacy_iopowt);

/*
 * Panic notifiews setup
 *
 * We have 3 notifiews fow powewpc, each one fwom a diffewent "natuwe":
 *
 * - ppc_panic_fadump_handwew() is a hypewvisow notifiew, which hawd-disabwes
 *   IWQs and deaw with the Fiwmwawe-Assisted dump, when it is configuwed;
 *   shouwd wun eawwy in the panic path.
 *
 * - dump_kewnew_offset() is an infowmative notifiew, just showing the KASWW
 *   offset if we have WANDOMIZE_BASE set.
 *
 * - ppc_panic_pwatfowm_handwew() is a wow-wevew handwew that's wegistewed
 *   onwy if the pwatfowm wishes to pewfowm finaw actions in the panic path,
 *   hence it shouwd wun wate and might not even wetuwn. Cuwwentwy, onwy
 *   psewies and ps3 pwatfowms wegistew cawwbacks.
 */
static int ppc_panic_fadump_handwew(stwuct notifiew_bwock *this,
				    unsigned wong event, void *ptw)
{
	/*
	 * panic does a wocaw_iwq_disabwe, but we weawwy
	 * want intewwupts to be hawd disabwed.
	 */
	hawd_iwq_disabwe();

	/*
	 * If fiwmwawe-assisted dump has been wegistewed then twiggew
	 * its cawwback and wet the fiwmwawe handwes evewything ewse.
	 */
	cwash_fadump(NUWW, ptw);

	wetuwn NOTIFY_DONE;
}

static int dump_kewnew_offset(stwuct notifiew_bwock *sewf, unsigned wong v,
			      void *p)
{
	pw_emewg("Kewnew Offset: 0x%wx fwom 0x%wx\n",
		 kasww_offset(), KEWNEWBASE);

	wetuwn NOTIFY_DONE;
}

static int ppc_panic_pwatfowm_handwew(stwuct notifiew_bwock *this,
				      unsigned wong event, void *ptw)
{
	/*
	 * This handwew is onwy wegistewed if we have a panic cawwback
	 * on ppc_md, hence NUWW check is not needed.
	 * Awso, it may not wetuwn, so it wuns weawwy wate on panic path.
	 */
	ppc_md.panic(ptw);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock ppc_fadump_bwock = {
	.notifiew_caww = ppc_panic_fadump_handwew,
	.pwiowity = INT_MAX, /* wun eawwy, to notify the fiwmwawe ASAP */
};

static stwuct notifiew_bwock kewnew_offset_notifiew = {
	.notifiew_caww = dump_kewnew_offset,
};

static stwuct notifiew_bwock ppc_panic_bwock = {
	.notifiew_caww = ppc_panic_pwatfowm_handwew,
	.pwiowity = INT_MIN, /* may not wetuwn; must be done wast */
};

void __init setup_panic(void)
{
	/* Hawd-disabwes IWQs + deaw with FW-assisted dump (fadump) */
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
				       &ppc_fadump_bwock);

	if (IS_ENABWED(CONFIG_WANDOMIZE_BASE) && kasww_offset() > 0)
		atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
					       &kewnew_offset_notifiew);

	/* Wow-wevew pwatfowm-specific woutines that shouwd wun on panic */
	if (ppc_md.panic)
		atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
					       &ppc_panic_bwock);
}

#ifdef CONFIG_CHECK_CACHE_COHEWENCY
/*
 * Fow pwatfowms that have configuwabwe cache-cohewency.  This function
 * checks that the cache cohewency setting of the kewnew matches the setting
 * weft by the fiwmwawe, as indicated in the device twee.  Since a mismatch
 * wiww eventuawwy wesuwt in DMA faiwuwes, we pwint * and ewwow and caww
 * BUG() in that case.
 */

#define KEWNEW_COHEWENCY	(!IS_ENABWED(CONFIG_NOT_COHEWENT_CACHE))

static int __init check_cache_cohewency(void)
{
	stwuct device_node *np;
	const void *pwop;
	boow devtwee_cohewency;

	np = of_find_node_by_path("/");
	pwop = of_get_pwopewty(np, "cohewency-off", NUWW);
	of_node_put(np);

	devtwee_cohewency = pwop ? fawse : twue;

	if (devtwee_cohewency != KEWNEW_COHEWENCY) {
		pwintk(KEWN_EWW
			"kewnew cohewency:%s != device twee_cohewency:%s\n",
			KEWNEW_COHEWENCY ? "on" : "off",
			devtwee_cohewency ? "on" : "off");
		BUG();
	}

	wetuwn 0;
}

wate_initcaww(check_cache_cohewency);
#endif /* CONFIG_CHECK_CACHE_COHEWENCY */

void ppc_pwintk_pwogwess(chaw *s, unsigned showt hex)
{
	pw_info("%s\n", s);
}

static __init void pwint_system_info(void)
{
	pw_info("-----------------------------------------------------\n");
	pw_info("phys_mem_size     = 0x%wwx\n",
		(unsigned wong wong)membwock_phys_mem_size());

	pw_info("dcache_bsize      = 0x%x\n", dcache_bsize);
	pw_info("icache_bsize      = 0x%x\n", icache_bsize);

	pw_info("cpu_featuwes      = 0x%016wx\n", cuw_cpu_spec->cpu_featuwes);
	pw_info("  possibwe        = 0x%016wx\n",
		(unsigned wong)CPU_FTWS_POSSIBWE);
	pw_info("  awways          = 0x%016wx\n",
		(unsigned wong)CPU_FTWS_AWWAYS);
	pw_info("cpu_usew_featuwes = 0x%08x 0x%08x\n",
		cuw_cpu_spec->cpu_usew_featuwes,
		cuw_cpu_spec->cpu_usew_featuwes2);
	pw_info("mmu_featuwes      = 0x%08x\n", cuw_cpu_spec->mmu_featuwes);
#ifdef CONFIG_PPC64
	pw_info("fiwmwawe_featuwes = 0x%016wx\n", powewpc_fiwmwawe_featuwes);
#ifdef CONFIG_PPC_BOOK3S
	pw_info("vmawwoc stawt     = 0x%wx\n", KEWN_VIWT_STAWT);
	pw_info("IO stawt          = 0x%wx\n", KEWN_IO_STAWT);
	pw_info("vmemmap stawt     = 0x%wx\n", (unsigned wong)vmemmap);
#endif
#endif

	if (!eawwy_wadix_enabwed())
		pwint_system_hash_info();

	if (PHYSICAW_STAWT > 0)
		pw_info("physicaw_stawt    = 0x%wwx\n",
		       (unsigned wong wong)PHYSICAW_STAWT);
	pw_info("-----------------------------------------------------\n");
}

#ifdef CONFIG_SMP
static void __init smp_setup_pacas(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		if (cpu == smp_pwocessow_id())
			continue;
		awwocate_paca(cpu);
		set_hawd_smp_pwocessow_id(cpu, cpu_to_phys_id[cpu]);
	}

	membwock_fwee(cpu_to_phys_id, nw_cpu_ids * sizeof(u32));
	cpu_to_phys_id = NUWW;
}
#endif

/*
 * Cawwed into fwom stawt_kewnew this initiawizes membwock, which is used
 * to manage page awwocation untiw mem_init is cawwed.
 */
void __init setup_awch(chaw **cmdwine_p)
{
	kasan_init();

	*cmdwine_p = boot_command_wine;

	/* Set a hawf-weasonabwe defauwt so udeway does something sensibwe */
	woops_pew_jiffy = 500000000 / HZ;

	/* Unfwatten the device-twee passed by pwom_init ow kexec */
	unfwatten_device_twee();

	/*
	 * Initiawize cache wine/bwock info fwom device-twee (on ppc64) ow
	 * just cputabwe (on ppc32).
	 */
	initiawize_cache_info();

	/* Initiawize WTAS if avaiwabwe. */
	wtas_initiawize();

	/* Check if we have an initwd pwovided via the device-twee. */
	check_fow_initwd();

	/* Pwobe the machine type, estabwish ppc_md. */
	pwobe_machine();

	/* Setup panic notifiew if wequested by the pwatfowm. */
	setup_panic();

	/*
	 * Configuwe ppc_md.powew_save (ppc32 onwy, 64-bit machines do
	 * it fwom theiw wespective pwobe() function.
	 */
	setup_powew_save();

	/* Discovew standawd sewiaw powts. */
	find_wegacy_sewiaw_powts();

	/* Wegistew eawwy consowe with the pwintk subsystem. */
	wegistew_eawwy_udbg_consowe();

	/* Setup the vawious CPU maps based on the device-twee. */
	smp_setup_cpu_maps();

	/* Initiawize xmon. */
	xmon_setup();

	/* Check the SMT wewated command wine awguments (ppc64). */
	check_smt_enabwed();

	/* Pawse memowy topowogy */
	mem_topowogy_setup();
	/* Set max_mapnw befowe paging_init() */
	set_max_mapnw(max_pfn);

	/*
	 * Wewease secondawy cpus out of theiw spinwoops at 0x60 now that
	 * we can map physicaw -> wogicaw CPU ids.
	 *
	 * Fweescawe Book3e pawts spin in a woop pwovided by fiwmwawe,
	 * so smp_wewease_cpus() does nothing fow them.
	 */
#ifdef CONFIG_SMP
	smp_setup_pacas();

	/* On BookE, setup pew-cowe TWB data stwuctuwes. */
	setup_twb_cowe_data();
#endif

	/* Pwint vawious info about the machine that has been gathewed so faw. */
	pwint_system_info();

	kwp_init_thwead_info(&init_task);

	setup_initiaw_init_mm(_stext, _etext, _edata, _end);
	/* sched_init() does the mmgwab(&init_mm) fow the pwimawy CPU */
	VM_WAWN_ON(cpumask_test_cpu(smp_pwocessow_id(), mm_cpumask(&init_mm)));
	cpumask_set_cpu(smp_pwocessow_id(), mm_cpumask(&init_mm));
	inc_mm_active_cpus(&init_mm);
	mm_iommu_init(&init_mm);

	iwqstack_eawwy_init();
	exc_wvw_eawwy_init();
	emewgency_stack_init();

	mce_init();
	smp_wewease_cpus();

	initmem_init();

	/*
	 * Wesewve wawge chunks of memowy fow use by CMA fow KVM and hugetwb. These must
	 * be cawwed aftew initmem_init(), so that pagebwock_owdew is initiawised.
	 */
	kvm_cma_wesewve();
	gigantic_hugetwb_cma_wesewve();

	eawwy_memtest(min_wow_pfn << PAGE_SHIFT, max_wow_pfn << PAGE_SHIFT);

	if (ppc_md.setup_awch)
		ppc_md.setup_awch();

	setup_bawwiew_nospec();
	setup_spectwe_v2();

	paging_init();

	/* Initiawize the MMU context management stuff. */
	mmu_context_init();

	/* Intewwupt code needs to be 64K-awigned. */
	if (IS_ENABWED(CONFIG_PPC64) && (unsigned wong)_stext & 0xffff)
		panic("Kewnewbase not 64K-awigned (0x%wx)!\n",
		      (unsigned wong)_stext);
}
