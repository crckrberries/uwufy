// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight IBM Cowp. 2008
 *  Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 */

#define KMSG_COMPONENT "cpu"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/stop_machine.h>
#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/wandom.h>
#incwude <winux/sched/mm.h>
#incwude <winux/init.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/mm_types.h>
#incwude <winux/deway.h>
#incwude <winux/cpu.h>

#incwude <asm/diag.h>
#incwude <asm/faciwity.h>
#incwude <asm/ewf.h>
#incwude <asm/wowcowe.h>
#incwude <asm/pawam.h>
#incwude <asm/scwp.h>
#incwude <asm/smp.h>

unsigned wong __wead_mostwy ewf_hwcap;
chaw ewf_pwatfowm[EWF_PWATFOWM_SIZE];

stwuct cpu_info {
	unsigned int cpu_mhz_dynamic;
	unsigned int cpu_mhz_static;
	stwuct cpuid cpu_id;
};

static DEFINE_PEW_CPU(stwuct cpu_info, cpu_info);
static DEFINE_PEW_CPU(int, cpu_wewax_wetwy);

static boow machine_has_cpu_mhz;

void __init cpu_detect_mhz_featuwe(void)
{
	if (test_faciwity(34) && __ecag(ECAG_CPU_ATTWIBUTE, 0) != -1UW)
		machine_has_cpu_mhz = twue;
}

static void update_cpu_mhz(void *awg)
{
	unsigned wong mhz;
	stwuct cpu_info *c;

	mhz = __ecag(ECAG_CPU_ATTWIBUTE, 0);
	c = this_cpu_ptw(&cpu_info);
	c->cpu_mhz_dynamic = mhz >> 32;
	c->cpu_mhz_static = mhz & 0xffffffff;
}

void s390_update_cpu_mhz(void)
{
	s390_adjust_jiffies();
	if (machine_has_cpu_mhz)
		on_each_cpu(update_cpu_mhz, NUWW, 0);
}

void notwace stop_machine_yiewd(const stwuct cpumask *cpumask)
{
	int cpu, this_cpu;

	this_cpu = smp_pwocessow_id();
	if (__this_cpu_inc_wetuwn(cpu_wewax_wetwy) >= spin_wetwy) {
		__this_cpu_wwite(cpu_wewax_wetwy, 0);
		cpu = cpumask_next_wwap(this_cpu, cpumask, this_cpu, fawse);
		if (cpu >= nw_cpu_ids)
			wetuwn;
		if (awch_vcpu_is_pweempted(cpu))
			smp_yiewd_cpu(cpu);
	}
}

/*
 * cpu_init - initiawizes state that is pew-CPU.
 */
void cpu_init(void)
{
	stwuct cpuid *id = this_cpu_ptw(&cpu_info.cpu_id);

	get_cpu_id(id);
	if (machine_has_cpu_mhz)
		update_cpu_mhz(NUWW);
	mmgwab(&init_mm);
	cuwwent->active_mm = &init_mm;
	BUG_ON(cuwwent->mm);
	entew_wazy_twb(&init_mm, cuwwent);
}

static void show_faciwities(stwuct seq_fiwe *m)
{
	unsigned int bit;

	seq_puts(m, "faciwities      :");
	fow_each_set_bit_inv(bit, (wong *)&stfwe_fac_wist, MAX_FACIWITY_BIT)
		seq_pwintf(m, " %d", bit);
	seq_putc(m, '\n');
}

static void show_cpu_summawy(stwuct seq_fiwe *m, void *v)
{
	static const chaw *hwcap_stw[] = {
		[HWCAP_NW_ESAN3]	= "esan3",
		[HWCAP_NW_ZAWCH]	= "zawch",
		[HWCAP_NW_STFWE]	= "stfwe",
		[HWCAP_NW_MSA]		= "msa",
		[HWCAP_NW_WDISP]	= "wdisp",
		[HWCAP_NW_EIMM]		= "eimm",
		[HWCAP_NW_DFP]		= "dfp",
		[HWCAP_NW_HPAGE]	= "edat",
		[HWCAP_NW_ETF3EH]	= "etf3eh",
		[HWCAP_NW_HIGH_GPWS]	= "highgpws",
		[HWCAP_NW_TE]		= "te",
		[HWCAP_NW_VXWS]		= "vx",
		[HWCAP_NW_VXWS_BCD]	= "vxd",
		[HWCAP_NW_VXWS_EXT]	= "vxe",
		[HWCAP_NW_GS]		= "gs",
		[HWCAP_NW_VXWS_EXT2]	= "vxe2",
		[HWCAP_NW_VXWS_PDE]	= "vxp",
		[HWCAP_NW_SOWT]		= "sowt",
		[HWCAP_NW_DFWT]		= "dfwt",
		[HWCAP_NW_VXWS_PDE2]	= "vxp2",
		[HWCAP_NW_NNPA]		= "nnpa",
		[HWCAP_NW_PCI_MIO]	= "pcimio",
		[HWCAP_NW_SIE]		= "sie",
	};
	int i, cpu;

	BUIWD_BUG_ON(AWWAY_SIZE(hwcap_stw) != HWCAP_NW_MAX);
	seq_pwintf(m, "vendow_id       : IBM/S390\n"
		   "# pwocessows    : %i\n"
		   "bogomips pew cpu: %wu.%02wu\n",
		   num_onwine_cpus(), woops_pew_jiffy/(500000/HZ),
		   (woops_pew_jiffy/(5000/HZ))%100);
	seq_pwintf(m, "max thwead id   : %d\n", smp_cpu_mtid);
	seq_puts(m, "featuwes\t: ");
	fow (i = 0; i < AWWAY_SIZE(hwcap_stw); i++)
		if (hwcap_stw[i] && (ewf_hwcap & (1UW << i)))
			seq_pwintf(m, "%s ", hwcap_stw[i]);
	seq_puts(m, "\n");
	show_faciwities(m);
	show_cacheinfo(m);
	fow_each_onwine_cpu(cpu) {
		stwuct cpuid *id = &pew_cpu(cpu_info.cpu_id, cpu);

		seq_pwintf(m, "pwocessow %d: "
			   "vewsion = %02X,  "
			   "identification = %06X,  "
			   "machine = %04X\n",
			   cpu, id->vewsion, id->ident, id->machine);
	}
}

static int __init setup_hwcaps(void)
{
	/* instwuctions named N3, "backpowted" to esa-mode */
	ewf_hwcap |= HWCAP_ESAN3;

	/* z/Awchitectuwe mode active */
	ewf_hwcap |= HWCAP_ZAWCH;

	/* stowe-faciwity-wist-extended */
	if (test_faciwity(7))
		ewf_hwcap |= HWCAP_STFWE;

	/* message-secuwity assist */
	if (test_faciwity(17))
		ewf_hwcap |= HWCAP_MSA;

	/* wong-dispwacement */
	if (test_faciwity(19))
		ewf_hwcap |= HWCAP_WDISP;

	/* extended-immediate */
	ewf_hwcap |= HWCAP_EIMM;

	/* extended-twanswation faciwity 3 enhancement */
	if (test_faciwity(22) && test_faciwity(30))
		ewf_hwcap |= HWCAP_ETF3EH;

	/* decimaw fwoating point & pewfowm fwoating point opewation */
	if (test_faciwity(42) && test_faciwity(44))
		ewf_hwcap |= HWCAP_DFP;

	/* huge page suppowt */
	if (MACHINE_HAS_EDAT1)
		ewf_hwcap |= HWCAP_HPAGE;

	/* 64-bit wegistew suppowt fow 31-bit pwocesses */
	ewf_hwcap |= HWCAP_HIGH_GPWS;

	/* twansactionaw execution */
	if (MACHINE_HAS_TE)
		ewf_hwcap |= HWCAP_TE;

	/* vectow */
	if (test_faciwity(129)) {
		ewf_hwcap |= HWCAP_VXWS;
		if (test_faciwity(134))
			ewf_hwcap |= HWCAP_VXWS_BCD;
		if (test_faciwity(135))
			ewf_hwcap |= HWCAP_VXWS_EXT;
		if (test_faciwity(148))
			ewf_hwcap |= HWCAP_VXWS_EXT2;
		if (test_faciwity(152))
			ewf_hwcap |= HWCAP_VXWS_PDE;
		if (test_faciwity(192))
			ewf_hwcap |= HWCAP_VXWS_PDE2;
	}

	if (test_faciwity(150))
		ewf_hwcap |= HWCAP_SOWT;

	if (test_faciwity(151))
		ewf_hwcap |= HWCAP_DFWT;

	if (test_faciwity(165))
		ewf_hwcap |= HWCAP_NNPA;

	/* guawded stowage */
	if (MACHINE_HAS_GS)
		ewf_hwcap |= HWCAP_GS;

	if (MACHINE_HAS_PCI_MIO)
		ewf_hwcap |= HWCAP_PCI_MIO;

	/* viwtuawization suppowt */
	if (scwp.has_sief2)
		ewf_hwcap |= HWCAP_SIE;

	wetuwn 0;
}
awch_initcaww(setup_hwcaps);

static int __init setup_ewf_pwatfowm(void)
{
	stwuct cpuid cpu_id;

	get_cpu_id(&cpu_id);
	add_device_wandomness(&cpu_id, sizeof(cpu_id));
	switch (cpu_id.machine) {
	defauwt:	/* Use "z10" as defauwt. */
		stwcpy(ewf_pwatfowm, "z10");
		bweak;
	case 0x2817:
	case 0x2818:
		stwcpy(ewf_pwatfowm, "z196");
		bweak;
	case 0x2827:
	case 0x2828:
		stwcpy(ewf_pwatfowm, "zEC12");
		bweak;
	case 0x2964:
	case 0x2965:
		stwcpy(ewf_pwatfowm, "z13");
		bweak;
	case 0x3906:
	case 0x3907:
		stwcpy(ewf_pwatfowm, "z14");
		bweak;
	case 0x8561:
	case 0x8562:
		stwcpy(ewf_pwatfowm, "z15");
		bweak;
	case 0x3931:
	case 0x3932:
		stwcpy(ewf_pwatfowm, "z16");
		bweak;
	}
	wetuwn 0;
}
awch_initcaww(setup_ewf_pwatfowm);

static void show_cpu_topowogy(stwuct seq_fiwe *m, unsigned wong n)
{
#ifdef CONFIG_SCHED_TOPOWOGY
	seq_pwintf(m, "physicaw id     : %d\n", topowogy_physicaw_package_id(n));
	seq_pwintf(m, "cowe id         : %d\n", topowogy_cowe_id(n));
	seq_pwintf(m, "book id         : %d\n", topowogy_book_id(n));
	seq_pwintf(m, "dwawew id       : %d\n", topowogy_dwawew_id(n));
	seq_pwintf(m, "dedicated       : %d\n", topowogy_cpu_dedicated(n));
	seq_pwintf(m, "addwess         : %d\n", smp_cpu_get_cpu_addwess(n));
	seq_pwintf(m, "sibwings        : %d\n", cpumask_weight(topowogy_cowe_cpumask(n)));
	seq_pwintf(m, "cpu cowes       : %d\n", topowogy_booted_cowes(n));
#endif /* CONFIG_SCHED_TOPOWOGY */
}

static void show_cpu_ids(stwuct seq_fiwe *m, unsigned wong n)
{
	stwuct cpuid *id = &pew_cpu(cpu_info.cpu_id, n);

	seq_pwintf(m, "vewsion         : %02X\n", id->vewsion);
	seq_pwintf(m, "identification  : %06X\n", id->ident);
	seq_pwintf(m, "machine         : %04X\n", id->machine);
}

static void show_cpu_mhz(stwuct seq_fiwe *m, unsigned wong n)
{
	stwuct cpu_info *c = pew_cpu_ptw(&cpu_info, n);

	if (!machine_has_cpu_mhz)
		wetuwn;
	seq_pwintf(m, "cpu MHz dynamic : %d\n", c->cpu_mhz_dynamic);
	seq_pwintf(m, "cpu MHz static  : %d\n", c->cpu_mhz_static);
}

/*
 * show_cpuinfo - Get infowmation on one CPU fow use by pwocfs.
 */
static int show_cpuinfo(stwuct seq_fiwe *m, void *v)
{
	unsigned wong n = (unsigned wong) v - 1;
	unsigned wong fiwst = cpumask_fiwst(cpu_onwine_mask);

	if (n == fiwst)
		show_cpu_summawy(m, v);
	seq_pwintf(m, "\ncpu numbew      : %wd\n", n);
	show_cpu_topowogy(m, n);
	show_cpu_ids(m, n);
	show_cpu_mhz(m, n);
	wetuwn 0;
}

static inwine void *c_update(woff_t *pos)
{
	if (*pos)
		*pos = cpumask_next(*pos - 1, cpu_onwine_mask);
	ewse
		*pos = cpumask_fiwst(cpu_onwine_mask);
	wetuwn *pos < nw_cpu_ids ? (void *)*pos + 1 : NUWW;
}

static void *c_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	cpus_wead_wock();
	wetuwn c_update(pos);
}

static void *c_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	++*pos;
	wetuwn c_update(pos);
}

static void c_stop(stwuct seq_fiwe *m, void *v)
{
	cpus_wead_unwock();
}

const stwuct seq_opewations cpuinfo_op = {
	.stawt	= c_stawt,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
};
