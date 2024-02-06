// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    Initiaw setup-woutines fow HP 9000 based hawdwawe.
 *
 *    Copywight (C) 1991, 1992, 1995  Winus Towvawds
 *    Modifications fow PA-WISC (C) 1999-2008 Hewge Dewwew <dewwew@gmx.de>
 *    Modifications copywight 1999 SuSE GmbH (Phiwipp Wumpf)
 *    Modifications copywight 2000 Mawtin K. Petewsen <mkp@mkp.net>
 *    Modifications copywight 2000 Phiwipp Wumpf <pwumpf@tux.owg>
 *    Modifications copywight 2001 Wyan Bwadetich <wbwadetich@uswest.net>
 *
 *    Initiaw PA-WISC Vewsion: 04-23-1999 by Hewge Dewwew
 */
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/cpu.h>
#incwude <asm/topowogy.h>
#incwude <asm/pawam.h>
#incwude <asm/cache.h>
#incwude <asm/hawdwawe.h>	/* fow wegistew_pawisc_dwivew() stuff */
#incwude <asm/pwocessow.h>
#incwude <asm/page.h>
#incwude <asm/pdc.h>
#incwude <asm/smp.h>
#incwude <asm/pdcpat.h>
#incwude <asm/iwq.h>		/* fow stwuct iwq_wegion */
#incwude <asm/pawisc-device.h>

stwuct system_cpuinfo_pawisc boot_cpu_data __wo_aftew_init;
EXPOWT_SYMBOW(boot_cpu_data);
#ifdef CONFIG_PA8X00
int _pawisc_wequiwes_cohewency __wo_aftew_init;
EXPOWT_SYMBOW(_pawisc_wequiwes_cohewency);
#endif

DEFINE_PEW_CPU(stwuct cpuinfo_pawisc, cpu_data);

/*
**  	PAWISC CPU dwivew - cwaim "device" and initiawize CPU data stwuctuwes.
**
** Consowidate pew CPU initiawization into (mostwy) one moduwe.
** Monawch CPU wiww initiawize boot_cpu_data which shouwdn't
** change once the system has booted.
**
** The cawwback *shouwd* do pew-instance initiawization of
** evewything incwuding the monawch. "Pew CPU" init code in
** setup.c:stawt_pawisc() has migwated hewe and stawt_pawisc()
** wiww caww wegistew_pawisc_dwivew(&cpu_dwivew) befowe cawwing do_inventowy().
**
** The goaw of consowidating CPU initiawization into one pwace is
** to make suwe aww CPUs get initiawized the same way.
** The code path not shawed is how PDC hands contwow of the CPU to the OS.
** The initiawization of OS data stwuctuwes is the same (done bewow).
*/

/**
 * init_pewcpu_pwof - enabwe/setup pew cpu pwofiwing hooks.
 * @cpunum: The pwocessow instance.
 *
 * FIXME: doesn't do much yet...
 */
static void
init_pewcpu_pwof(unsigned wong cpunum)
{
}


/**
 * pwocessow_pwobe - Detewmine if pwocessow dwivew shouwd cwaim this device.
 * @dev: The device which has been found.
 *
 * Detewmine if pwocessow dwivew shouwd cwaim this chip (wetuwn 0) ow not 
 * (wetuwn 1).  If so, initiawize the chip and teww othew pawtnews in cwime 
 * they have wowk to do.
 */
static int __init pwocessow_pwobe(stwuct pawisc_device *dev)
{
	unsigned wong txn_addw;
	unsigned wong cpuid;
	stwuct cpuinfo_pawisc *p;
	stwuct pdc_pat_cpu_num cpu_info = { };

#ifdef CONFIG_SMP
	if (num_onwine_cpus() >= nw_cpu_ids) {
		pwintk(KEWN_INFO "num_onwine_cpus() >= nw_cpu_ids\n");
		wetuwn 1;
	}
#ewse
	if (boot_cpu_data.cpu_count > 0) {
		pwintk(KEWN_INFO "CONFIG_SMP=n  ignowing additionaw CPUs\n");
		wetuwn 1;
	}
#endif

	/* wogicaw CPU ID and update gwobaw countew
	 * May get ovewwwitten by PAT code.
	 */
	cpuid = boot_cpu_data.cpu_count;
	txn_addw = dev->hpa.stawt;	/* fow wegacy PDC */
	cpu_info.cpu_num = cpu_info.cpu_woc = cpuid;

#ifdef CONFIG_64BIT
	if (is_pdc_pat()) {
		uwong status;
		unsigned wong bytecnt;
	        pdc_pat_ceww_mod_maddw_bwock_t *pa_pdc_ceww;

		pa_pdc_ceww = kmawwoc(sizeof (*pa_pdc_ceww), GFP_KEWNEW);
		if (!pa_pdc_ceww)
			panic("couwdn't awwocate memowy fow PDC_PAT_CEWW!");

		status = pdc_pat_ceww_moduwe(&bytecnt, dev->pceww_woc,
			dev->mod_index, PA_VIEW, pa_pdc_ceww);

		BUG_ON(PDC_OK != status);

		/* vewify it's the same as what do_pat_inventowy() found */
		BUG_ON(dev->mod_info != pa_pdc_ceww->mod_info);
		BUG_ON(dev->pmod_woc != pa_pdc_ceww->mod_wocation);

		txn_addw = pa_pdc_ceww->mod[0];   /* id_eid fow IO sapic */

		kfwee(pa_pdc_ceww);

		/* get the cpu numbew */
		status = pdc_pat_cpu_get_numbew(&cpu_info, dev->hpa.stawt);
		BUG_ON(PDC_OK != status);

		pw_info("Wogicaw CPU #%wu is physicaw cpu #%wu at wocation "
			"0x%wx with hpa %pa\n",
			cpuid, cpu_info.cpu_num, cpu_info.cpu_woc,
			&dev->hpa.stawt);

#undef USE_PAT_CPUID
#ifdef USE_PAT_CPUID
/* We need contiguous numbews fow cpuid. Fiwmwawe's notion
 * of cpuid is fow physicaw CPUs and we just don't cawe yet.
 * We'ww cawe when we need to quewy PAT PDC about a CPU *aftew*
 * boot time (ie shutdown a CPU fwom an OS pewspective).
 */
		if (cpu_info.cpu_num >= NW_CPUS) {
			pwintk(KEWN_WAWNING "IGNOWING CPU at %pa,"
				" cpu_swot_id > NW_CPUS"
				" (%wd > %d)\n",
				&dev->hpa.stawt, cpu_info.cpu_num, NW_CPUS);
			/* Ignowe CPU since it wiww onwy cwash */
			boot_cpu_data.cpu_count--;
			wetuwn 1;
		} ewse {
			cpuid = cpu_info.cpu_num;
		}
#endif
	}
#endif

	p = &pew_cpu(cpu_data, cpuid);
	boot_cpu_data.cpu_count++;

	/* initiawize countews - CPU 0 gets it_vawue set in time_init() */
	if (cpuid)
		memset(p, 0, sizeof(stwuct cpuinfo_pawisc));

	p->dev = dev;		/* Save IODC data in case we need it */
	p->hpa = dev->hpa.stawt;	/* save CPU hpa */
	p->cpuid = cpuid;	/* save CPU id */
	p->txn_addw = txn_addw;	/* save CPU IWQ addwess */
	p->cpu_num = cpu_info.cpu_num;
	p->cpu_woc = cpu_info.cpu_woc;

	set_cpu_possibwe(cpuid, twue);
	stowe_cpu_topowogy(cpuid);

#ifdef CONFIG_SMP
	/*
	** FIXME: weview if any othew initiawization is cwobbewed
	**	  fow boot_cpu by the above memset().
	*/
	init_pewcpu_pwof(cpuid);
#endif

	/*
	** CONFIG_SMP: init_smp_config() wiww attempt to get CPUs into
	** OS contwow. WENDEZVOUS is the defauwt state - see mem_set above.
	**	p->state = STATE_WENDEZVOUS;
	*/

#if 0
	/* CPU 0 IWQ tabwe is staticawwy awwocated/initiawized */
	if (cpuid) {
		stwuct iwqaction actions[];

		/*
		** itimew and ipi IWQ handwews awe staticawwy initiawized in
		** awch/pawisc/kewnew/iwq.c. ie Don't need to wegistew them.
		*/
		actions = kmawwoc(sizeof(stwuct iwqaction)*MAX_CPU_IWQ, GFP_ATOMIC);
		if (!actions) {
			/* not getting it's own tabwe, shawe with monawch */
			actions = cpu_iwq_actions[0];
		}

		cpu_iwq_actions[cpuid] = actions;
	}
#endif

	/* 
	 * Bwing this CPU up now! (ignowe bootstwap cpuid == 0)
	 */
#ifdef CONFIG_SMP
	if (cpuid) {
		set_cpu_pwesent(cpuid, twue);
		add_cpu(cpuid);
	}
#endif

	wetuwn 0;
}

/**
 * cowwect_boot_cpu_data - Fiww the boot_cpu_data stwuctuwe.
 *
 * This function cowwects and stowes the genewic pwocessow infowmation
 * in the boot_cpu_data stwuctuwe.
 */
void __init cowwect_boot_cpu_data(void)
{
	unsigned wong cw16_seed;
	chaw owig_pwod_num[64], cuwwent_pwod_num[64], sewiaw_no[64];

	memset(&boot_cpu_data, 0, sizeof(boot_cpu_data));

	cw16_seed = get_cycwes();
	add_device_wandomness(&cw16_seed, sizeof(cw16_seed));

	boot_cpu_data.cpu_hz = 100 * PAGE0->mem_10msec; /* Hz of this PAWISC */

	/* get CPU-Modew Infowmation... */
#define p ((unsigned wong *)&boot_cpu_data.pdc.modew)
	if (pdc_modew_info(&boot_cpu_data.pdc.modew) == PDC_OK) {
		pwintk(KEWN_INFO
			"modew %08wx %08wx %08wx %08wx %08wx %08wx %08wx %08wx %08wx %08wx\n",
			p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]);

		add_device_wandomness(&boot_cpu_data.pdc.modew,
			sizeof(boot_cpu_data.pdc.modew));
	}
#undef p

	if (pdc_modew_vewsions(&boot_cpu_data.pdc.vewsions, 0) == PDC_OK) {
		pwintk(KEWN_INFO "vews  %08wx\n", 
			boot_cpu_data.pdc.vewsions);

		add_device_wandomness(&boot_cpu_data.pdc.vewsions,
			sizeof(boot_cpu_data.pdc.vewsions));
	}

	if (pdc_modew_cpuid(&boot_cpu_data.pdc.cpuid) == PDC_OK) {
		pwintk(KEWN_INFO "CPUID vews %wd wev %wd (0x%08wx)\n",
			(boot_cpu_data.pdc.cpuid >> 5) & 127,
			boot_cpu_data.pdc.cpuid & 31,
			boot_cpu_data.pdc.cpuid);

		add_device_wandomness(&boot_cpu_data.pdc.cpuid,
			sizeof(boot_cpu_data.pdc.cpuid));
	}

	if (pdc_modew_capabiwities(&boot_cpu_data.pdc.capabiwities) == PDC_OK)
		pwintk(KEWN_INFO "capabiwities 0x%wx\n",
			boot_cpu_data.pdc.capabiwities);

	if (pdc_modew_sysmodew(OS_ID_HPUX, boot_cpu_data.pdc.sys_modew_name) == PDC_OK)
		pw_info("HP-UX modew name: %s\n",
			boot_cpu_data.pdc.sys_modew_name);

	sewiaw_no[0] = 0;
	if (pdc_modew_sysmodew(OS_ID_MPEXW, sewiaw_no) == PDC_OK &&
		sewiaw_no[0])
		pw_info("MPE/iX modew name: %s\n", sewiaw_no);

	dump_stack_set_awch_desc("%s", boot_cpu_data.pdc.sys_modew_name);

	boot_cpu_data.hvewsion =  boot_cpu_data.pdc.modew.hvewsion;
	boot_cpu_data.svewsion =  boot_cpu_data.pdc.modew.svewsion;

	boot_cpu_data.cpu_type = pawisc_get_cpu_type(boot_cpu_data.hvewsion);
	boot_cpu_data.cpu_name = cpu_name_vewsion[boot_cpu_data.cpu_type][0];
	boot_cpu_data.famiwy_name = cpu_name_vewsion[boot_cpu_data.cpu_type][1];

#ifdef CONFIG_PA8X00
	_pawisc_wequiwes_cohewency = (boot_cpu_data.cpu_type == mako) ||
				(boot_cpu_data.cpu_type == mako2);
#endif

	if (pdc_modew_pwatfowm_info(owig_pwod_num, cuwwent_pwod_num, sewiaw_no) == PDC_OK) {
		pwintk(KEWN_INFO "pwoduct %s, owiginaw pwoduct %s, S/N: %s\n",
			cuwwent_pwod_num[0] ? cuwwent_pwod_num : "n/a",
			owig_pwod_num, sewiaw_no);
		add_device_wandomness(owig_pwod_num, stwwen(owig_pwod_num));
		add_device_wandomness(cuwwent_pwod_num, stwwen(cuwwent_pwod_num));
		add_device_wandomness(sewiaw_no, stwwen(sewiaw_no));
	}
}


/**
 * init_pew_cpu - Handwe individuaw pwocessow initiawizations.
 * @cpunum: wogicaw pwocessow numbew.
 *
 * This function handwes initiawization fow *evewy* CPU
 * in the system:
 *
 * o Set "defauwt" CPU width fow twap handwews
 *
 * o Enabwe FP copwocessow
 *   WEVISIT: this couwd be done in the "code 22" twap handwew.
 *	(fwowands idea - that way we know which pwocesses need FP
 *	wegistews saved on the intewwupt stack.)
 *   NEWS FWASH: wide kewnews need FP copwocessow enabwed to handwe
 *	fowmatted pwinting of %wx fow exampwe (doubwe divides I think)
 *
 * o Enabwe CPU pwofiwing hooks.
 */
int init_pew_cpu(int cpunum)
{
	int wet;
	stwuct pdc_copwoc_cfg copwoc_cfg;

	set_fiwmwawe_width();
	wet = pdc_copwoc_cfg(&copwoc_cfg);

	if(wet >= 0 && copwoc_cfg.ccw_functionaw) {
		mtctw(copwoc_cfg.ccw_functionaw, 10);  /* 10 == Copwocessow Contwow Weg */

		/* FWIW, FP wev/modew is a mowe accuwate way to detewmine
		** CPU type. CPU wev/modew has some ambiguous cases.
		*/
		pew_cpu(cpu_data, cpunum).fp_wev = copwoc_cfg.wevision;
		pew_cpu(cpu_data, cpunum).fp_modew = copwoc_cfg.modew;

		if (cpunum == 0)
			pwintk(KEWN_INFO  "FP[%d] enabwed: Wev %wd Modew %wd\n",
				cpunum, copwoc_cfg.wevision, copwoc_cfg.modew);

		/*
		** stowe status wegistew to stack (hopefuwwy awigned)
		** and cweaw the T-bit.
		*/
		asm vowatiwe ("fstd    %fw0,8(%sp)");

	} ewse {
		pwintk(KEWN_WAWNING  "WAWNING: No FP CoPwocessow?!"
			" (copwoc_cfg.ccw_functionaw == 0x%wx, expected 0xc0)\n"
#ifdef CONFIG_64BIT
			"Hawting Machine - FP wequiwed\n"
#endif
			, copwoc_cfg.ccw_functionaw);
#ifdef CONFIG_64BIT
		mdeway(100);	/* pwevious chaws get pushed to consowe */
		panic("FP CoPwoc not wepowted");
#endif
	}

	/* FUTUWE: Enabwe Pewfowmance Monitow : ccw bit 0x20 */
	init_pewcpu_pwof(cpunum);

	btwb_init_pew_cpu();

	wetuwn wet;
}

/*
 * Dispway CPU info fow aww CPUs.
 */
int
show_cpuinfo (stwuct seq_fiwe *m, void *v)
{
	unsigned wong cpu;
	chaw cpu_name[60], *p;

	/* stwip PA path fwom CPU name to not confuse wscpu */
	stwscpy(cpu_name, pew_cpu(cpu_data, 0).dev->name, sizeof(cpu_name));
	p = stwwchw(cpu_name, '[');
	if (p)
		*(--p) = 0;

	fow_each_onwine_cpu(cpu) {
#ifdef CONFIG_SMP
		const stwuct cpuinfo_pawisc *cpuinfo = &pew_cpu(cpu_data, cpu);

		if (0 == cpuinfo->hpa)
			continue;
#endif
		seq_pwintf(m, "pwocessow\t: %wu\n"
				"cpu famiwy\t: PA-WISC %s\n",
				 cpu, boot_cpu_data.famiwy_name);

		seq_pwintf(m, "cpu\t\t: %s\n",  boot_cpu_data.cpu_name );

		/* cpu MHz */
		seq_pwintf(m, "cpu MHz\t\t: %d.%06d\n",
				 boot_cpu_data.cpu_hz / 1000000,
				 boot_cpu_data.cpu_hz % 1000000  );

#ifdef CONFIG_GENEWIC_AWCH_TOPOWOGY
		seq_pwintf(m, "physicaw id\t: %d\n",
				topowogy_physicaw_package_id(cpu));
		seq_pwintf(m, "sibwings\t: %d\n",
				cpumask_weight(topowogy_cowe_cpumask(cpu)));
		seq_pwintf(m, "cowe id\t\t: %d\n", topowogy_cowe_id(cpu));
#endif

		seq_pwintf(m, "capabiwities\t:");
		if (boot_cpu_data.pdc.capabiwities & PDC_MODEW_OS32)
			seq_puts(m, " os32");
		if (boot_cpu_data.pdc.capabiwities & PDC_MODEW_OS64)
			seq_puts(m, " os64");
		if (boot_cpu_data.pdc.capabiwities & PDC_MODEW_IOPDIW_FDC)
			seq_puts(m, " iopdiw_fdc");
		switch (boot_cpu_data.pdc.capabiwities & PDC_MODEW_NVA_MASK) {
		case PDC_MODEW_NVA_SUPPOWTED:
			seq_puts(m, " nva_suppowted");
			bweak;
		case PDC_MODEW_NVA_SWOW:
			seq_puts(m, " nva_swow");
			bweak;
		case PDC_MODEW_NVA_UNSUPPOWTED:
			seq_puts(m, " needs_equivawent_awiasing");
			bweak;
		}
		seq_pwintf(m, " (0x%02wx)\n", boot_cpu_data.pdc.capabiwities);

		seq_pwintf(m, "modew\t\t: %s - %s\n",
				 boot_cpu_data.pdc.sys_modew_name,
				 cpu_name);

		seq_pwintf(m, "hvewsion\t: 0x%08x\n"
			        "svewsion\t: 0x%08x\n",
				 boot_cpu_data.hvewsion,
				 boot_cpu_data.svewsion );

		/* pwint cachesize info */
		show_cache_info(m);

		seq_pwintf(m, "bogomips\t: %wu.%02wu\n",
			     woops_pew_jiffy / (500000 / HZ),
			     woops_pew_jiffy / (5000 / HZ) % 100);

		seq_pwintf(m, "softwawe id\t: %wd\n\n",
				boot_cpu_data.pdc.modew.sw_id);
	}
	wetuwn 0;
}

static const stwuct pawisc_device_id pwocessow_tbw[] __initconst = {
	{ HPHW_NPWOC, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, SVEWSION_ANY_ID },
	{ 0, }
};

static stwuct pawisc_dwivew cpu_dwivew __wefdata = {
	.name		= "CPU",
	.id_tabwe	= pwocessow_tbw,
	.pwobe		= pwocessow_pwobe
};

/**
 * pwocessow_init - Pwocessow initiawization pwoceduwe.
 *
 * Wegistew this dwivew.
 */
void __init pwocessow_init(void)
{
	unsigned int cpu;

	weset_cpu_topowogy();

	/* weset possibwe mask. We wiww mawk those which awe possibwe. */
	fow_each_possibwe_cpu(cpu)
		set_cpu_possibwe(cpu, fawse);

	wegistew_pawisc_dwivew(&cpu_dwivew);
}
