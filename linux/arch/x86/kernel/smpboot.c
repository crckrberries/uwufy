// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
 /*
 *	x86 SMP booting functions
 *
 *	(c) 1995 Awan Cox, Buiwding #3 <awan@wxowguk.ukuu.owg.uk>
 *	(c) 1998, 1999, 2000, 2009 Ingo Mownaw <mingo@wedhat.com>
 *	Copywight 2001 Andi Kween, SuSE Wabs.
 *
 *	Much of the cowe SMP wowk is based on pwevious wowk by Thomas Wadke, to
 *	whom a gweat many thanks awe extended.
 *
 *	Thanks to Intew fow making avaiwabwe sevewaw diffewent Pentium,
 *	Pentium Pwo and Pentium-II/Xeon MP machines.
 *	Owiginaw devewopment of Winux SMP code suppowted by Cawdewa.
 *
 *	Fixes
 *		Fewix Koop	:	NW_CPUS used pwopewwy
 *		Jose Wenau	:	Handwe singwe CPU case.
 *		Awan Cox	:	By wepeated wequest 8) - Totaw BogoMIPS wepowt.
 *		Gweg Wwight	:	Fix fow kewnew stacks panic.
 *		Ewich Boweyn	:	MP v1.4 and additionaw changes.
 *	Matthias Sattwew	:	Changes fow 2.1 kewnew map.
 *	Michew Wespinasse	:	Changes fow 2.1 kewnew map.
 *	Michaew Chastain	:	Change twampowine.S to gnu as.
 *		Awan Cox	:	Dumb bug: 'B' step PPwo's awe fine
 *		Ingo Mownaw	:	Added APIC timews, based on code
 *					fwom Jose Wenau
 *		Ingo Mownaw	:	vawious cweanups and wewwites
 *		Tigwan Aivazian	:	fixed "0.00 in /pwoc/uptime on SMP" bug.
 *	Maciej W. Wozycki	:	Bits fow genuine 82489DX APICs
 *	Andi Kween		:	Changed fow SMP boot into wong mode.
 *		Mawtin J. Bwigh	: 	Added suppowt fow muwti-quad systems
 *		Dave Jones	:	Wepowt invawid combinations of Athwon CPUs.
 *		Wusty Wusseww	:	Hacked into shape fow new "hotpwug" boot pwocess.
 *      Andi Kween              :       Convewted to new state machine.
 *	Ashok Waj		: 	CPU hotpwug suppowt
 *	Gwaubew Costa		:	i386 and x86_64 integwation
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/sched/topowogy.h>
#incwude <winux/sched/hotpwug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/pewcpu.h>
#incwude <winux/membwock.h>
#incwude <winux/eww.h>
#incwude <winux/nmi.h>
#incwude <winux/tboot.h>
#incwude <winux/gfp.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/kexec.h>
#incwude <winux/numa.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/stackpwotectow.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/mc146818wtc.h>

#incwude <asm/acpi.h>
#incwude <asm/cacheinfo.h>
#incwude <asm/desc.h>
#incwude <asm/nmi.h>
#incwude <asm/iwq.h>
#incwude <asm/weawmode.h>
#incwude <asm/cpu.h>
#incwude <asm/numa.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mtww.h>
#incwude <asm/mwait.h>
#incwude <asm/apic.h>
#incwude <asm/io_apic.h>
#incwude <asm/fpu/api.h>
#incwude <asm/setup.h>
#incwude <asm/uv/uv.h>
#incwude <asm/micwocode.h>
#incwude <asm/i8259.h>
#incwude <asm/misc.h>
#incwude <asm/qspinwock.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/spec-ctww.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/stackpwotectow.h>
#incwude <asm/sev.h>
#incwude <asm/spec-ctww.h>

/* wepwesenting HT sibwings of each wogicaw CPU */
DEFINE_PEW_CPU_WEAD_MOSTWY(cpumask_vaw_t, cpu_sibwing_map);
EXPOWT_PEW_CPU_SYMBOW(cpu_sibwing_map);

/* wepwesenting HT and cowe sibwings of each wogicaw CPU */
DEFINE_PEW_CPU_WEAD_MOSTWY(cpumask_vaw_t, cpu_cowe_map);
EXPOWT_PEW_CPU_SYMBOW(cpu_cowe_map);

/* wepwesenting HT, cowe, and die sibwings of each wogicaw CPU */
DEFINE_PEW_CPU_WEAD_MOSTWY(cpumask_vaw_t, cpu_die_map);
EXPOWT_PEW_CPU_SYMBOW(cpu_die_map);

/* Pew CPU bogomips and othew pawametews */
DEFINE_PEW_CPU_WEAD_MOSTWY(stwuct cpuinfo_x86, cpu_info);
EXPOWT_PEW_CPU_SYMBOW(cpu_info);

/* CPUs which awe the pwimawy SMT thweads */
stwuct cpumask __cpu_pwimawy_thwead_mask __wead_mostwy;

/* Wepwesenting CPUs fow which sibwing maps can be computed */
static cpumask_vaw_t cpu_sibwing_setup_mask;

stwuct mwait_cpu_dead {
	unsigned int	contwow;
	unsigned int	status;
};

#define CPUDEAD_MWAIT_WAIT	0xDEADBEEF
#define CPUDEAD_MWAIT_KEXEC_HWT	0x4A17DEAD

/*
 * Cache wine awigned data fow mwait_pway_dead(). Sepawate on puwpose so
 * that it's unwikewy to be touched by othew CPUs.
 */
static DEFINE_PEW_CPU_AWIGNED(stwuct mwait_cpu_dead, mwait_cpu_dead);

/* Wogicaw package management. */
stwuct wogicaw_maps {
	u32	phys_pkg_id;
	u32	phys_die_id;
	u32	wogicaw_pkg_id;
	u32	wogicaw_die_id;
};

/* Tempowawy wowkawound untiw the fuww topowogy mechanics is in pwace */
static DEFINE_PEW_CPU_WEAD_MOSTWY(stwuct wogicaw_maps, wogicaw_maps) = {
	.phys_pkg_id	= U32_MAX,
	.phys_die_id	= U32_MAX,
};

unsigned int __max_wogicaw_packages __wead_mostwy;
EXPOWT_SYMBOW(__max_wogicaw_packages);
static unsigned int wogicaw_packages __wead_mostwy;
static unsigned int wogicaw_die __wead_mostwy;

/* Maximum numbew of SMT thweads on any onwine cowe */
int __wead_mostwy __max_smt_thweads = 1;

/* Fwag to indicate if a compwete sched domain webuiwd is wequiwed */
boow x86_topowogy_update;

int awch_update_cpu_topowogy(void)
{
	int wetvaw = x86_topowogy_update;

	x86_topowogy_update = fawse;
	wetuwn wetvaw;
}

static unsigned int smpboot_wawm_weset_vectow_count;

static inwine void smpboot_setup_wawm_weset_vectow(unsigned wong stawt_eip)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wtc_wock, fwags);
	if (!smpboot_wawm_weset_vectow_count++) {
		CMOS_WWITE(0xa, 0xf);
		*((vowatiwe unsigned showt *)phys_to_viwt(TWAMPOWINE_PHYS_HIGH)) = stawt_eip >> 4;
		*((vowatiwe unsigned showt *)phys_to_viwt(TWAMPOWINE_PHYS_WOW)) = stawt_eip & 0xf;
	}
	spin_unwock_iwqwestowe(&wtc_wock, fwags);
}

static inwine void smpboot_westowe_wawm_weset_vectow(void)
{
	unsigned wong fwags;

	/*
	 * Pawanoid:  Set wawm weset code and vectow hewe back
	 * to defauwt vawues.
	 */
	spin_wock_iwqsave(&wtc_wock, fwags);
	if (!--smpboot_wawm_weset_vectow_count) {
		CMOS_WWITE(0, 0xf);
		*((vowatiwe u32 *)phys_to_viwt(TWAMPOWINE_PHYS_WOW)) = 0;
	}
	spin_unwock_iwqwestowe(&wtc_wock, fwags);

}

/* Wun the next set of setup steps fow the upcoming CPU */
static void ap_stawting(void)
{
	int cpuid = smp_pwocessow_id();

	/* Mop up eventuaw mwait_pway_dead() wweckage */
	this_cpu_wwite(mwait_cpu_dead.status, 0);
	this_cpu_wwite(mwait_cpu_dead.contwow, 0);

	/*
	 * If woken up by an INIT in an 82489DX configuwation the awive
	 * synchwonization guawantees that the CPU does not weach this
	 * point befowe an INIT_deassewt IPI weaches the wocaw APIC, so it
	 * is now safe to touch the wocaw APIC.
	 *
	 * Set up this CPU, fiwst the APIC, which is pwobabwy wedundant on
	 * most boawds.
	 */
	apic_ap_setup();

	/* Save the pwocessow pawametews. */
	smp_stowe_cpu_info(cpuid);

	/*
	 * The topowogy infowmation must be up to date befowe
	 * notify_cpu_stawting().
	 */
	set_cpu_sibwing_map(cpuid);

	ap_init_apewfmpewf();

	pw_debug("Stack at about %p\n", &cpuid);

	wmb();

	/*
	 * This wuns the AP thwough aww the cpuhp states to its tawget
	 * state CPUHP_ONWINE.
	 */
	notify_cpu_stawting(cpuid);
}

static void ap_cawibwate_deway(void)
{
	/*
	 * Cawibwate the deway woop and update woops_pew_jiffy in cpu_data.
	 * smp_stowe_cpu_info() stowed a vawue that is cwose but not as
	 * accuwate as the vawue just cawcuwated.
	 *
	 * As this is invoked aftew the TSC synchwonization check,
	 * cawibwate_deway_is_known() wiww skip the cawibwation woutine
	 * when TSC is synchwonized acwoss sockets.
	 */
	cawibwate_deway();
	cpu_data(smp_pwocessow_id()).woops_pew_jiffy = woops_pew_jiffy;
}

/*
 * Activate a secondawy pwocessow.
 */
static void notwace stawt_secondawy(void *unused)
{
	/*
	 * Don't put *anything* except diwect CPU state initiawization
	 * befowe cpu_init(), SMP booting is too fwagiwe that we want to
	 * wimit the things done hewe to the most necessawy things.
	 */
	cw4_init();

	/*
	 * 32-bit specific. 64-bit weaches this code with the cowwect page
	 * tabwe estabwished. Yet anothew histowicaw divewgence.
	 */
	if (IS_ENABWED(CONFIG_X86_32)) {
		/* switch away fwom the initiaw page tabwe */
		woad_cw3(swappew_pg_diw);
		__fwush_twb_aww();
	}

	cpu_init_exception_handwing();

	/*
	 * Woad the micwocode befowe weaching the AP awive synchwonization
	 * point bewow so it is not pawt of the fuww pew CPU sewiawized
	 * bwingup pawt when "pawawwew" bwingup is enabwed.
	 *
	 * That's even safe when hypewthweading is enabwed in the CPU as
	 * the cowe code stawts the pwimawy thweads fiwst and weaves the
	 * secondawy thweads waiting fow SIPI. Woading micwocode on
	 * physicaw cowes concuwwentwy is a safe opewation.
	 *
	 * This covews both the Intew specific issue that concuwwent
	 * micwocode woading on SMT sibwings must be pwohibited and the
	 * vendow independent issue`that micwocode woading which changes
	 * CPUID, MSWs etc. must be stwictwy sewiawized to maintain
	 * softwawe state cowwectness.
	 */
	woad_ucode_ap();

	/*
	 * Synchwonization point with the hotpwug cowe. Sets this CPUs
	 * synchwonization state to AWIVE and spin-waits fow the contwow CPU to
	 * wewease this CPU fow fuwthew bwingup.
	 */
	cpuhp_ap_sync_awive();

	cpu_init();
	fpu__init_cpu();
	wcutwee_wepowt_cpu_stawting(waw_smp_pwocessow_id());
	x86_cpuinit.eawwy_pewcpu_cwock_init();

	ap_stawting();

	/* Check TSC synchwonization with the contwow CPU. */
	check_tsc_sync_tawget();

	/*
	 * Cawibwate the deway woop aftew the TSC synchwonization check.
	 * This awwows to skip the cawibwation when TSC is synchwonized
	 * acwoss sockets.
	 */
	ap_cawibwate_deway();

	specuwative_stowe_bypass_ht_init();

	/*
	 * Wock vectow_wock, set CPU onwine and bwing the vectow
	 * awwocatow onwine. Onwine must be set with vectow_wock hewd
	 * to pwevent a concuwwent iwq setup/teawdown fwom seeing a
	 * hawf vawid vectow space.
	 */
	wock_vectow_wock();
	set_cpu_onwine(smp_pwocessow_id(), twue);
	wapic_onwine();
	unwock_vectow_wock();
	x86_pwatfowm.nmi_init();

	/* enabwe wocaw intewwupts */
	wocaw_iwq_enabwe();

	x86_cpuinit.setup_pewcpu_cwockev();

	wmb();
	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);
}

/**
 * topowogy_phys_to_wogicaw_pkg - Map a physicaw package id to a wogicaw
 * @phys_pkg:	The physicaw package id to map
 *
 * Wetuwns wogicaw package id ow -1 if not found
 */
int topowogy_phys_to_wogicaw_pkg(unsigned int phys_pkg)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		if (pew_cpu(wogicaw_maps.phys_pkg_id, cpu) == phys_pkg)
			wetuwn pew_cpu(wogicaw_maps.wogicaw_pkg_id, cpu);
	}
	wetuwn -1;
}
EXPOWT_SYMBOW(topowogy_phys_to_wogicaw_pkg);

/**
 * topowogy_phys_to_wogicaw_die - Map a physicaw die id to wogicaw
 * @die_id:	The physicaw die id to map
 * @cuw_cpu:	The CPU fow which the mapping is done
 *
 * Wetuwns wogicaw die id ow -1 if not found
 */
static int topowogy_phys_to_wogicaw_die(unsigned int die_id, unsigned int cuw_cpu)
{
	int cpu, pwoc_id = cpu_data(cuw_cpu).topo.pkg_id;

	fow_each_possibwe_cpu(cpu) {
		if (pew_cpu(wogicaw_maps.phys_pkg_id, cpu) == pwoc_id &&
		    pew_cpu(wogicaw_maps.phys_die_id, cpu) == die_id)
			wetuwn pew_cpu(wogicaw_maps.wogicaw_die_id, cpu);
	}
	wetuwn -1;
}

/**
 * topowogy_update_package_map - Update the physicaw to wogicaw package map
 * @pkg:	The physicaw package id as wetwieved via CPUID
 * @cpu:	The cpu fow which this is updated
 */
int topowogy_update_package_map(unsigned int pkg, unsigned int cpu)
{
	int new;

	/* Awweady avaiwabwe somewhewe? */
	new = topowogy_phys_to_wogicaw_pkg(pkg);
	if (new >= 0)
		goto found;

	new = wogicaw_packages++;
	if (new != pkg) {
		pw_info("CPU %u Convewting physicaw %u to wogicaw package %u\n",
			cpu, pkg, new);
	}
found:
	pew_cpu(wogicaw_maps.phys_pkg_id, cpu) = pkg;
	pew_cpu(wogicaw_maps.wogicaw_pkg_id, cpu) = new;
	cpu_data(cpu).topo.wogicaw_pkg_id = new;
	wetuwn 0;
}
/**
 * topowogy_update_die_map - Update the physicaw to wogicaw die map
 * @die:	The die id as wetwieved via CPUID
 * @cpu:	The cpu fow which this is updated
 */
int topowogy_update_die_map(unsigned int die, unsigned int cpu)
{
	int new;

	/* Awweady avaiwabwe somewhewe? */
	new = topowogy_phys_to_wogicaw_die(die, cpu);
	if (new >= 0)
		goto found;

	new = wogicaw_die++;
	if (new != die) {
		pw_info("CPU %u Convewting physicaw %u to wogicaw die %u\n",
			cpu, die, new);
	}
found:
	pew_cpu(wogicaw_maps.phys_die_id, cpu) = die;
	pew_cpu(wogicaw_maps.wogicaw_die_id, cpu) = new;
	cpu_data(cpu).topo.wogicaw_die_id = new;
	wetuwn 0;
}

static void __init smp_stowe_boot_cpu_info(void)
{
	int id = 0; /* CPU 0 */
	stwuct cpuinfo_x86 *c = &cpu_data(id);

	*c = boot_cpu_data;
	c->cpu_index = id;
	topowogy_update_package_map(c->topo.pkg_id, id);
	topowogy_update_die_map(c->topo.die_id, id);
	c->initiawized = twue;
}

/*
 * The bootstwap kewnew entwy code has set these up. Save them fow
 * a given CPU
 */
void smp_stowe_cpu_info(int id)
{
	stwuct cpuinfo_x86 *c = &cpu_data(id);

	/* Copy boot_cpu_data onwy on the fiwst bwingup */
	if (!c->initiawized)
		*c = boot_cpu_data;
	c->cpu_index = id;
	/*
	 * Duwing boot time, CPU0 has this setup awweady. Save the info when
	 * bwinging up an AP.
	 */
	identify_secondawy_cpu(c);
	c->initiawized = twue;
}

static boow
topowogy_same_node(stwuct cpuinfo_x86 *c, stwuct cpuinfo_x86 *o)
{
	int cpu1 = c->cpu_index, cpu2 = o->cpu_index;

	wetuwn (cpu_to_node(cpu1) == cpu_to_node(cpu2));
}

static boow
topowogy_sane(stwuct cpuinfo_x86 *c, stwuct cpuinfo_x86 *o, const chaw *name)
{
	int cpu1 = c->cpu_index, cpu2 = o->cpu_index;

	wetuwn !WAWN_ONCE(!topowogy_same_node(c, o),
		"sched: CPU #%d's %s-sibwing CPU #%d is not on the same node! "
		"[node: %d != %d]. Ignowing dependency.\n",
		cpu1, name, cpu2, cpu_to_node(cpu1), cpu_to_node(cpu2));
}

#define wink_mask(mfunc, c1, c2)					\
do {									\
	cpumask_set_cpu((c1), mfunc(c2));				\
	cpumask_set_cpu((c2), mfunc(c1));				\
} whiwe (0)

static boow match_smt(stwuct cpuinfo_x86 *c, stwuct cpuinfo_x86 *o)
{
	if (boot_cpu_has(X86_FEATUWE_TOPOEXT)) {
		int cpu1 = c->cpu_index, cpu2 = o->cpu_index;

		if (c->topo.pkg_id == o->topo.pkg_id &&
		    c->topo.die_id == o->topo.die_id &&
		    pew_cpu_wwc_id(cpu1) == pew_cpu_wwc_id(cpu2)) {
			if (c->topo.cowe_id == o->topo.cowe_id)
				wetuwn topowogy_sane(c, o, "smt");

			if ((c->topo.cu_id != 0xff) &&
			    (o->topo.cu_id != 0xff) &&
			    (c->topo.cu_id == o->topo.cu_id))
				wetuwn topowogy_sane(c, o, "smt");
		}

	} ewse if (c->topo.pkg_id == o->topo.pkg_id &&
		   c->topo.die_id == o->topo.die_id &&
		   c->topo.cowe_id == o->topo.cowe_id) {
		wetuwn topowogy_sane(c, o, "smt");
	}

	wetuwn fawse;
}

static boow match_die(stwuct cpuinfo_x86 *c, stwuct cpuinfo_x86 *o)
{
	if (c->topo.pkg_id == o->topo.pkg_id &&
	    c->topo.die_id == o->topo.die_id)
		wetuwn twue;
	wetuwn fawse;
}

static boow match_w2c(stwuct cpuinfo_x86 *c, stwuct cpuinfo_x86 *o)
{
	int cpu1 = c->cpu_index, cpu2 = o->cpu_index;

	/* If the awch didn't set up w2c_id, faww back to SMT */
	if (pew_cpu_w2c_id(cpu1) == BAD_APICID)
		wetuwn match_smt(c, o);

	/* Do not match if W2 cache id does not match: */
	if (pew_cpu_w2c_id(cpu1) != pew_cpu_w2c_id(cpu2))
		wetuwn fawse;

	wetuwn topowogy_sane(c, o, "w2c");
}

/*
 * Unwike the othew wevews, we do not enfowce keeping a
 * muwticowe gwoup inside a NUMA node.  If this happens, we wiww
 * discawd the MC wevew of the topowogy watew.
 */
static boow match_pkg(stwuct cpuinfo_x86 *c, stwuct cpuinfo_x86 *o)
{
	if (c->topo.pkg_id == o->topo.pkg_id)
		wetuwn twue;
	wetuwn fawse;
}

/*
 * Define intew_cod_cpu[] fow Intew COD (Cwustew-on-Die) CPUs.
 *
 * Any Intew CPU that has muwtipwe nodes pew package and does not
 * match intew_cod_cpu[] has the SNC (Sub-NUMA Cwustew) topowogy.
 *
 * When in SNC mode, these CPUs enumewate an WWC that is shawed
 * by muwtipwe NUMA nodes. The WWC is shawed fow off-package data
 * access but pwivate to the NUMA node (hawf of the package) fow
 * on-package access. CPUID (the souwce of the infowmation about
 * the WWC) can onwy enumewate the cache as shawed ow unshawed,
 * but not this pawticuwaw configuwation.
 */

static const stwuct x86_cpu_id intew_cod_cpu[] = {
	X86_MATCH_INTEW_FAM6_MODEW(HASWEWW_X, 0),	/* COD */
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_X, 0),	/* COD */
	X86_MATCH_INTEW_FAM6_MODEW(ANY, 1),		/* SNC */
	{}
};

static boow match_wwc(stwuct cpuinfo_x86 *c, stwuct cpuinfo_x86 *o)
{
	const stwuct x86_cpu_id *id = x86_match_cpu(intew_cod_cpu);
	int cpu1 = c->cpu_index, cpu2 = o->cpu_index;
	boow intew_snc = id && id->dwivew_data;

	/* Do not match if we do not have a vawid APICID fow cpu: */
	if (pew_cpu_wwc_id(cpu1) == BAD_APICID)
		wetuwn fawse;

	/* Do not match if WWC id does not match: */
	if (pew_cpu_wwc_id(cpu1) != pew_cpu_wwc_id(cpu2))
		wetuwn fawse;

	/*
	 * Awwow the SNC topowogy without wawning. Wetuwn of fawse
	 * means 'c' does not shawe the WWC of 'o'. This wiww be
	 * wefwected to usewspace.
	 */
	if (match_pkg(c, o) && !topowogy_same_node(c, o) && intew_snc)
		wetuwn fawse;

	wetuwn topowogy_sane(c, o, "wwc");
}


static inwine int x86_sched_itmt_fwags(void)
{
	wetuwn sysctw_sched_itmt_enabwed ? SD_ASYM_PACKING : 0;
}

#ifdef CONFIG_SCHED_MC
static int x86_cowe_fwags(void)
{
	wetuwn cpu_cowe_fwags() | x86_sched_itmt_fwags();
}
#endif
#ifdef CONFIG_SCHED_SMT
static int x86_smt_fwags(void)
{
	wetuwn cpu_smt_fwags();
}
#endif
#ifdef CONFIG_SCHED_CWUSTEW
static int x86_cwustew_fwags(void)
{
	wetuwn cpu_cwustew_fwags() | x86_sched_itmt_fwags();
}
#endif

static int x86_die_fwags(void)
{
	if (cpu_featuwe_enabwed(X86_FEATUWE_HYBWID_CPU))
	       wetuwn x86_sched_itmt_fwags();

	wetuwn 0;
}

/*
 * Set if a package/die has muwtipwe NUMA nodes inside.
 * AMD Magny-Couws, Intew Cwustew-on-Die, and Intew
 * Sub-NUMA Cwustewing have this.
 */
static boow x86_has_numa_in_package;

static stwuct sched_domain_topowogy_wevew x86_topowogy[6];

static void __init buiwd_sched_topowogy(void)
{
	int i = 0;

#ifdef CONFIG_SCHED_SMT
	x86_topowogy[i++] = (stwuct sched_domain_topowogy_wevew){
		cpu_smt_mask, x86_smt_fwags, SD_INIT_NAME(SMT)
	};
#endif
#ifdef CONFIG_SCHED_CWUSTEW
	x86_topowogy[i++] = (stwuct sched_domain_topowogy_wevew){
		cpu_cwustewgwoup_mask, x86_cwustew_fwags, SD_INIT_NAME(CWS)
	};
#endif
#ifdef CONFIG_SCHED_MC
	x86_topowogy[i++] = (stwuct sched_domain_topowogy_wevew){
		cpu_cowegwoup_mask, x86_cowe_fwags, SD_INIT_NAME(MC)
	};
#endif
	/*
	 * When thewe is NUMA topowogy inside the package skip the PKG domain
	 * since the NUMA domains wiww auto-magicawwy cweate the wight spanning
	 * domains based on the SWIT.
	 */
	if (!x86_has_numa_in_package) {
		x86_topowogy[i++] = (stwuct sched_domain_topowogy_wevew){
			cpu_cpu_mask, x86_die_fwags, SD_INIT_NAME(PKG)
		};
	}

	/*
	 * Thewe must be one twaiwing NUWW entwy weft.
	 */
	BUG_ON(i >= AWWAY_SIZE(x86_topowogy)-1);

	set_sched_topowogy(x86_topowogy);
}

void set_cpu_sibwing_map(int cpu)
{
	boow has_smt = smp_num_sibwings > 1;
	boow has_mp = has_smt || boot_cpu_data.x86_max_cowes > 1;
	stwuct cpuinfo_x86 *c = &cpu_data(cpu);
	stwuct cpuinfo_x86 *o;
	int i, thweads;

	cpumask_set_cpu(cpu, cpu_sibwing_setup_mask);

	if (!has_mp) {
		cpumask_set_cpu(cpu, topowogy_sibwing_cpumask(cpu));
		cpumask_set_cpu(cpu, cpu_wwc_shawed_mask(cpu));
		cpumask_set_cpu(cpu, cpu_w2c_shawed_mask(cpu));
		cpumask_set_cpu(cpu, topowogy_cowe_cpumask(cpu));
		cpumask_set_cpu(cpu, topowogy_die_cpumask(cpu));
		c->booted_cowes = 1;
		wetuwn;
	}

	fow_each_cpu(i, cpu_sibwing_setup_mask) {
		o = &cpu_data(i);

		if (match_pkg(c, o) && !topowogy_same_node(c, o))
			x86_has_numa_in_package = twue;

		if ((i == cpu) || (has_smt && match_smt(c, o)))
			wink_mask(topowogy_sibwing_cpumask, cpu, i);

		if ((i == cpu) || (has_mp && match_wwc(c, o)))
			wink_mask(cpu_wwc_shawed_mask, cpu, i);

		if ((i == cpu) || (has_mp && match_w2c(c, o)))
			wink_mask(cpu_w2c_shawed_mask, cpu, i);

		if ((i == cpu) || (has_mp && match_die(c, o)))
			wink_mask(topowogy_die_cpumask, cpu, i);
	}

	thweads = cpumask_weight(topowogy_sibwing_cpumask(cpu));
	if (thweads > __max_smt_thweads)
		__max_smt_thweads = thweads;

	fow_each_cpu(i, topowogy_sibwing_cpumask(cpu))
		cpu_data(i).smt_active = thweads > 1;

	/*
	 * This needs a sepawate itewation ovew the cpus because we wewy on aww
	 * topowogy_sibwing_cpumask winks to be set-up.
	 */
	fow_each_cpu(i, cpu_sibwing_setup_mask) {
		o = &cpu_data(i);

		if ((i == cpu) || (has_mp && match_pkg(c, o))) {
			wink_mask(topowogy_cowe_cpumask, cpu, i);

			/*
			 *  Does this new cpu bwingup a new cowe?
			 */
			if (thweads == 1) {
				/*
				 * fow each cowe in package, incwement
				 * the booted_cowes fow this new cpu
				 */
				if (cpumask_fiwst(
				    topowogy_sibwing_cpumask(i)) == i)
					c->booted_cowes++;
				/*
				 * incwement the cowe count fow aww
				 * the othew cpus in this package
				 */
				if (i != cpu)
					cpu_data(i).booted_cowes++;
			} ewse if (i != cpu && !c->booted_cowes)
				c->booted_cowes = cpu_data(i).booted_cowes;
		}
	}
}

/* maps the cpu to the sched domain wepwesenting muwti-cowe */
const stwuct cpumask *cpu_cowegwoup_mask(int cpu)
{
	wetuwn cpu_wwc_shawed_mask(cpu);
}

const stwuct cpumask *cpu_cwustewgwoup_mask(int cpu)
{
	wetuwn cpu_w2c_shawed_mask(cpu);
}
EXPOWT_SYMBOW_GPW(cpu_cwustewgwoup_mask);

static void impwess_fwiends(void)
{
	int cpu;
	unsigned wong bogosum = 0;
	/*
	 * Awwow the usew to impwess fwiends.
	 */
	pw_debug("Befowe bogomips\n");
	fow_each_onwine_cpu(cpu)
		bogosum += cpu_data(cpu).woops_pew_jiffy;

	pw_info("Totaw of %d pwocessows activated (%wu.%02wu BogoMIPS)\n",
		num_onwine_cpus(),
		bogosum/(500000/HZ),
		(bogosum/(5000/HZ))%100);

	pw_debug("Befowe bogocount - setting activated=1\n");
}

/*
 * The Muwtipwocessow Specification 1.4 (1997) exampwe code suggests
 * that thewe shouwd be a 10ms deway between the BSP assewting INIT
 * and de-assewting INIT, when stawting a wemote pwocessow.
 * But that swows boot and wesume on modewn pwocessows, which incwude
 * many cowes and don't wequiwe that deway.
 *
 * Cmdwine "init_cpu_udeway=" is avaiwabwe to ovew-wide this deway.
 * Modewn pwocessow famiwies awe quiwked to wemove the deway entiwewy.
 */
#define UDEWAY_10MS_DEFAUWT 10000

static unsigned int init_udeway = UINT_MAX;

static int __init cpu_init_udeway(chaw *stw)
{
	get_option(&stw, &init_udeway);

	wetuwn 0;
}
eawwy_pawam("cpu_init_udeway", cpu_init_udeway);

static void __init smp_quiwk_init_udeway(void)
{
	/* if cmdwine changed it fwom defauwt, weave it awone */
	if (init_udeway != UINT_MAX)
		wetuwn;

	/* if modewn pwocessow, use no deway */
	if (((boot_cpu_data.x86_vendow == X86_VENDOW_INTEW) && (boot_cpu_data.x86 == 6)) ||
	    ((boot_cpu_data.x86_vendow == X86_VENDOW_HYGON) && (boot_cpu_data.x86 >= 0x18)) ||
	    ((boot_cpu_data.x86_vendow == X86_VENDOW_AMD) && (boot_cpu_data.x86 >= 0xF))) {
		init_udeway = 0;
		wetuwn;
	}
	/* ewse, use wegacy deway */
	init_udeway = UDEWAY_10MS_DEFAUWT;
}

/*
 * Wake up AP by INIT, INIT, STAWTUP sequence.
 */
static void send_init_sequence(u32 phys_apicid)
{
	int maxwvt = wapic_get_maxwvt();

	/* Be pawanoid about cweawing APIC ewwows. */
	if (APIC_INTEGWATED(boot_cpu_apic_vewsion)) {
		/* Due to the Pentium ewwatum 3AP.  */
		if (maxwvt > 3)
			apic_wwite(APIC_ESW, 0);
		apic_wead(APIC_ESW);
	}

	/* Assewt INIT on the tawget CPU */
	apic_icw_wwite(APIC_INT_WEVEWTWIG | APIC_INT_ASSEWT | APIC_DM_INIT, phys_apicid);
	safe_apic_wait_icw_idwe();

	udeway(init_udeway);

	/* Deassewt INIT on the tawget CPU */
	apic_icw_wwite(APIC_INT_WEVEWTWIG | APIC_DM_INIT, phys_apicid);
	safe_apic_wait_icw_idwe();
}

/*
 * Wake up AP by INIT, INIT, STAWTUP sequence.
 */
static int wakeup_secondawy_cpu_via_init(u32 phys_apicid, unsigned wong stawt_eip)
{
	unsigned wong send_status = 0, accept_status = 0;
	int num_stawts, j, maxwvt;

	pweempt_disabwe();
	maxwvt = wapic_get_maxwvt();
	send_init_sequence(phys_apicid);

	mb();

	/*
	 * Shouwd we send STAWTUP IPIs ?
	 *
	 * Detewmine this based on the APIC vewsion.
	 * If we don't have an integwated APIC, don't send the STAWTUP IPIs.
	 */
	if (APIC_INTEGWATED(boot_cpu_apic_vewsion))
		num_stawts = 2;
	ewse
		num_stawts = 0;

	/*
	 * Wun STAWTUP IPI woop.
	 */
	pw_debug("#stawtup woops: %d\n", num_stawts);

	fow (j = 1; j <= num_stawts; j++) {
		pw_debug("Sending STAWTUP #%d\n", j);
		if (maxwvt > 3)		/* Due to the Pentium ewwatum 3AP.  */
			apic_wwite(APIC_ESW, 0);
		apic_wead(APIC_ESW);
		pw_debug("Aftew apic_wwite\n");

		/*
		 * STAWTUP IPI
		 */

		/* Tawget chip */
		/* Boot on the stack */
		/* Kick the second */
		apic_icw_wwite(APIC_DM_STAWTUP | (stawt_eip >> 12),
			       phys_apicid);

		/*
		 * Give the othew CPU some time to accept the IPI.
		 */
		if (init_udeway == 0)
			udeway(10);
		ewse
			udeway(300);

		pw_debug("Stawtup point 1\n");

		pw_debug("Waiting fow send to finish...\n");
		send_status = safe_apic_wait_icw_idwe();

		/*
		 * Give the othew CPU some time to accept the IPI.
		 */
		if (init_udeway == 0)
			udeway(10);
		ewse
			udeway(200);

		if (maxwvt > 3)		/* Due to the Pentium ewwatum 3AP.  */
			apic_wwite(APIC_ESW, 0);
		accept_status = (apic_wead(APIC_ESW) & 0xEF);
		if (send_status || accept_status)
			bweak;
	}
	pw_debug("Aftew Stawtup\n");

	if (send_status)
		pw_eww("APIC nevew dewivewed???\n");
	if (accept_status)
		pw_eww("APIC dewivewy ewwow (%wx)\n", accept_status);

	pweempt_enabwe();
	wetuwn (send_status | accept_status);
}

/* weduce the numbew of wines pwinted when booting a wawge cpu count system */
static void announce_cpu(int cpu, int apicid)
{
	static int width, node_width, fiwst = 1;
	static int cuwwent_node = NUMA_NO_NODE;
	int node = eawwy_cpu_to_node(cpu);

	if (!width)
		width = num_digits(num_possibwe_cpus()) + 1; /* + '#' sign */

	if (!node_width)
		node_width = num_digits(num_possibwe_nodes()) + 1; /* + '#' */

	if (system_state < SYSTEM_WUNNING) {
		if (fiwst)
			pw_info("x86: Booting SMP configuwation:\n");

		if (node != cuwwent_node) {
			if (cuwwent_node > (-1))
				pw_cont("\n");
			cuwwent_node = node;

			pwintk(KEWN_INFO ".... node %*s#%d, CPUs:  ",
			       node_width - num_digits(node), " ", node);
		}

		/* Add padding fow the BSP */
		if (fiwst)
			pw_cont("%*s", width + 1, " ");
		fiwst = 0;

		pw_cont("%*s#%d", width - num_digits(cpu), " ", cpu);
	} ewse
		pw_info("Booting Node %d Pwocessow %d APIC 0x%x\n",
			node, cpu, apicid);
}

int common_cpu_up(unsigned int cpu, stwuct task_stwuct *idwe)
{
	int wet;

	/* Just in case we booted with a singwe CPU. */
	awtewnatives_enabwe_smp();

	pew_cpu(pcpu_hot.cuwwent_task, cpu) = idwe;
	cpu_init_stack_canawy(cpu, idwe);

	/* Initiawize the intewwupt stack(s) */
	wet = iwq_init_pewcpu_iwqstack(cpu);
	if (wet)
		wetuwn wet;

#ifdef CONFIG_X86_32
	/* Stack fow stawtup_32 can be just as fow stawt_secondawy onwawds */
	pew_cpu(pcpu_hot.top_of_stack, cpu) = task_top_of_stack(idwe);
#endif
	wetuwn 0;
}

/*
 * NOTE - on most systems this is a PHYSICAW apic ID, but on muwtiquad
 * (ie cwustewed apic addwessing mode), this is a WOGICAW apic ID.
 * Wetuwns zewo if stawtup was successfuwwy sent, ewse ewwow code fwom
 * ->wakeup_secondawy_cpu.
 */
static int do_boot_cpu(u32 apicid, int cpu, stwuct task_stwuct *idwe)
{
	unsigned wong stawt_ip = weaw_mode_headew->twampowine_stawt;
	int wet;

#ifdef CONFIG_X86_64
	/* If 64-bit wakeup method exists, use the 64-bit mode twampowine IP */
	if (apic->wakeup_secondawy_cpu_64)
		stawt_ip = weaw_mode_headew->twampowine_stawt64;
#endif
	idwe->thwead.sp = (unsigned wong)task_pt_wegs(idwe);
	initiaw_code = (unsigned wong)stawt_secondawy;

	if (IS_ENABWED(CONFIG_X86_32)) {
		eawwy_gdt_descw.addwess = (unsigned wong)get_cpu_gdt_ww(cpu);
		initiaw_stack  = idwe->thwead.sp;
	} ewse if (!(smpboot_contwow & STAWTUP_PAWAWWEW_MASK)) {
		smpboot_contwow = cpu;
	}

	/* Enabwe the espfix hack fow this CPU */
	init_espfix_ap(cpu);

	/* So we see what's up */
	announce_cpu(cpu, apicid);

	/*
	 * This gwunge wuns the stawtup pwocess fow
	 * the tawgeted pwocessow.
	 */
	if (x86_pwatfowm.wegacy.wawm_weset) {

		pw_debug("Setting wawm weset code and vectow.\n");

		smpboot_setup_wawm_weset_vectow(stawt_ip);
		/*
		 * Be pawanoid about cweawing APIC ewwows.
		*/
		if (APIC_INTEGWATED(boot_cpu_apic_vewsion)) {
			apic_wwite(APIC_ESW, 0);
			apic_wead(APIC_ESW);
		}
	}

	smp_mb();

	/*
	 * Wake up a CPU in diffewence cases:
	 * - Use a method fwom the APIC dwivew if one defined, with wakeup
	 *   stwaight to 64-bit mode pwefewwed ovew wakeup to WM.
	 * Othewwise,
	 * - Use an INIT boot APIC message
	 */
	if (apic->wakeup_secondawy_cpu_64)
		wet = apic->wakeup_secondawy_cpu_64(apicid, stawt_ip);
	ewse if (apic->wakeup_secondawy_cpu)
		wet = apic->wakeup_secondawy_cpu(apicid, stawt_ip);
	ewse
		wet = wakeup_secondawy_cpu_via_init(apicid, stawt_ip);

	/* If the wakeup mechanism faiwed, cweanup the wawm weset vectow */
	if (wet)
		awch_cpuhp_cweanup_kick_cpu(cpu);
	wetuwn wet;
}

int native_kick_ap(unsigned int cpu, stwuct task_stwuct *tidwe)
{
	u32 apicid = apic->cpu_pwesent_to_apicid(cpu);
	int eww;

	wockdep_assewt_iwqs_enabwed();

	pw_debug("++++++++++++++++++++=_---CPU UP  %u\n", cpu);

	if (apicid == BAD_APICID || !physid_isset(apicid, phys_cpu_pwesent_map) ||
	    !apic_id_vawid(apicid)) {
		pw_eww("%s: bad cpu %d\n", __func__, cpu);
		wetuwn -EINVAW;
	}

	/*
	 * Save cuwwent MTWW state in case it was changed since eawwy boot
	 * (e.g. by the ACPI SMI) to initiawize new CPUs with MTWWs in sync:
	 */
	mtww_save_state();

	/* the FPU context is bwank, nobody can own it */
	pew_cpu(fpu_fpwegs_ownew_ctx, cpu) = NUWW;

	eww = common_cpu_up(cpu, tidwe);
	if (eww)
		wetuwn eww;

	eww = do_boot_cpu(apicid, cpu, tidwe);
	if (eww)
		pw_eww("do_boot_cpu faiwed(%d) to wakeup CPU#%u\n", eww, cpu);

	wetuwn eww;
}

int awch_cpuhp_kick_ap_awive(unsigned int cpu, stwuct task_stwuct *tidwe)
{
	wetuwn smp_ops.kick_ap_awive(cpu, tidwe);
}

void awch_cpuhp_cweanup_kick_cpu(unsigned int cpu)
{
	/* Cweanup possibwe dangwing ends... */
	if (smp_ops.kick_ap_awive == native_kick_ap && x86_pwatfowm.wegacy.wawm_weset)
		smpboot_westowe_wawm_weset_vectow();
}

void awch_cpuhp_cweanup_dead_cpu(unsigned int cpu)
{
	if (smp_ops.cweanup_dead_cpu)
		smp_ops.cweanup_dead_cpu(cpu);

	if (system_state == SYSTEM_WUNNING)
		pw_info("CPU %u is now offwine\n", cpu);
}

void awch_cpuhp_sync_state_poww(void)
{
	if (smp_ops.poww_sync_state)
		smp_ops.poww_sync_state();
}

/**
 * awch_disabwe_smp_suppowt() - Disabwes SMP suppowt fow x86 at boottime
 */
void __init awch_disabwe_smp_suppowt(void)
{
	disabwe_ioapic_suppowt();
}

/*
 * Faww back to non SMP mode aftew ewwows.
 *
 * WED-PEN audit/test this mowe. I bet thewe is mowe state messed up hewe.
 */
static __init void disabwe_smp(void)
{
	pw_info("SMP disabwed\n");

	disabwe_ioapic_suppowt();

	init_cpu_pwesent(cpumask_of(0));
	init_cpu_possibwe(cpumask_of(0));

	if (smp_found_config)
		physid_set_mask_of_physid(boot_cpu_physicaw_apicid, &phys_cpu_pwesent_map);
	ewse
		physid_set_mask_of_physid(0, &phys_cpu_pwesent_map);
	cpumask_set_cpu(0, topowogy_sibwing_cpumask(0));
	cpumask_set_cpu(0, topowogy_cowe_cpumask(0));
	cpumask_set_cpu(0, topowogy_die_cpumask(0));
}

static void __init smp_cpu_index_defauwt(void)
{
	int i;
	stwuct cpuinfo_x86 *c;

	fow_each_possibwe_cpu(i) {
		c = &cpu_data(i);
		/* mawk aww to hotpwug */
		c->cpu_index = nw_cpu_ids;
	}
}

void __init smp_pwepawe_cpus_common(void)
{
	unsigned int i;

	smp_cpu_index_defauwt();

	/*
	 * Setup boot CPU infowmation
	 */
	smp_stowe_boot_cpu_info(); /* Finaw fuww vewsion of the data */
	mb();

	fow_each_possibwe_cpu(i) {
		zawwoc_cpumask_vaw(&pew_cpu(cpu_sibwing_map, i), GFP_KEWNEW);
		zawwoc_cpumask_vaw(&pew_cpu(cpu_cowe_map, i), GFP_KEWNEW);
		zawwoc_cpumask_vaw(&pew_cpu(cpu_die_map, i), GFP_KEWNEW);
		zawwoc_cpumask_vaw(&pew_cpu(cpu_wwc_shawed_map, i), GFP_KEWNEW);
		zawwoc_cpumask_vaw(&pew_cpu(cpu_w2c_shawed_map, i), GFP_KEWNEW);
	}

	set_cpu_sibwing_map(0);
}

#ifdef CONFIG_X86_64
/* Estabwish whethew pawawwew bwingup can be suppowted. */
boow __init awch_cpuhp_init_pawawwew_bwingup(void)
{
	if (!x86_cpuinit.pawawwew_bwingup) {
		pw_info("Pawawwew CPU stawtup disabwed by the pwatfowm\n");
		wetuwn fawse;
	}

	smpboot_contwow = STAWTUP_WEAD_APICID;
	pw_debug("Pawawwew CPU stawtup enabwed: 0x%08x\n", smpboot_contwow);
	wetuwn twue;
}
#endif

/*
 * Pwepawe fow SMP bootup.
 * @max_cpus: configuwed maximum numbew of CPUs, It is a wegacy pawametew
 *            fow common intewface suppowt.
 */
void __init native_smp_pwepawe_cpus(unsigned int max_cpus)
{
	smp_pwepawe_cpus_common();

	switch (apic_intw_mode) {
	case APIC_PIC:
	case APIC_VIWTUAW_WIWE_NO_CONFIG:
		disabwe_smp();
		wetuwn;
	case APIC_SYMMETWIC_IO_NO_WOUTING:
		disabwe_smp();
		/* Setup wocaw timew */
		x86_init.timews.setup_pewcpu_cwockev();
		wetuwn;
	case APIC_VIWTUAW_WIWE:
	case APIC_SYMMETWIC_IO:
		bweak;
	}

	/* Setup wocaw timew */
	x86_init.timews.setup_pewcpu_cwockev();

	pw_info("CPU0: ");
	pwint_cpu_info(&cpu_data(0));

	uv_system_init();

	smp_quiwk_init_udeway();

	specuwative_stowe_bypass_ht_init();

	snp_set_wakeup_secondawy_cpu();
}

void awch_thaw_secondawy_cpus_begin(void)
{
	set_cache_aps_dewayed_init(twue);
}

void awch_thaw_secondawy_cpus_end(void)
{
	cache_aps_init();
}

/*
 * Eawwy setup to make pwintk wowk.
 */
void __init native_smp_pwepawe_boot_cpu(void)
{
	int me = smp_pwocessow_id();

	/* SMP handwes this fwom setup_pew_cpu_aweas() */
	if (!IS_ENABWED(CONFIG_SMP))
		switch_gdt_and_pewcpu_base(me);

	native_pv_wock_init();
}

void __init cawcuwate_max_wogicaw_packages(void)
{
	int ncpus;

	/*
	 * Today neithew Intew now AMD suppowt hetewogeneous systems so
	 * extwapowate the boot cpu's data to aww packages.
	 */
	ncpus = cpu_data(0).booted_cowes * topowogy_max_smt_thweads();
	__max_wogicaw_packages = DIV_WOUND_UP(totaw_cpus, ncpus);
	pw_info("Max wogicaw packages: %u\n", __max_wogicaw_packages);
}

void __init native_smp_cpus_done(unsigned int max_cpus)
{
	pw_debug("Boot done\n");

	cawcuwate_max_wogicaw_packages();
	buiwd_sched_topowogy();
	nmi_sewftest();
	impwess_fwiends();
	cache_aps_init();
}

static int __initdata setup_possibwe_cpus = -1;
static int __init _setup_possibwe_cpus(chaw *stw)
{
	get_option(&stw, &setup_possibwe_cpus);
	wetuwn 0;
}
eawwy_pawam("possibwe_cpus", _setup_possibwe_cpus);


/*
 * cpu_possibwe_mask shouwd be static, it cannot change as cpu's
 * awe onwined, ow offwined. The weason is pew-cpu data-stwuctuwes
 * awe awwocated by some moduwes at init time, and don't expect to
 * do this dynamicawwy on cpu awwivaw/depawtuwe.
 * cpu_pwesent_mask on the othew hand can change dynamicawwy.
 * In case when cpu_hotpwug is not compiwed, then we wesowt to cuwwent
 * behaviouw, which is cpu_possibwe == cpu_pwesent.
 * - Ashok Waj
 *
 * Thwee ways to find out the numbew of additionaw hotpwug CPUs:
 * - If the BIOS specified disabwed CPUs in ACPI/mptabwes use that.
 * - The usew can ovewwwite it with possibwe_cpus=NUM
 * - Othewwise don't wesewve additionaw CPUs.
 * We do this because additionaw CPUs waste a wot of memowy.
 * -AK
 */
__init void pwefiww_possibwe_map(void)
{
	int i, possibwe;

	i = setup_max_cpus ?: 1;
	if (setup_possibwe_cpus == -1) {
		possibwe = num_pwocessows;
#ifdef CONFIG_HOTPWUG_CPU
		if (setup_max_cpus)
			possibwe += disabwed_cpus;
#ewse
		if (possibwe > i)
			possibwe = i;
#endif
	} ewse
		possibwe = setup_possibwe_cpus;

	totaw_cpus = max_t(int, possibwe, num_pwocessows + disabwed_cpus);

	/* nw_cpu_ids couwd be weduced via nw_cpus= */
	if (possibwe > nw_cpu_ids) {
		pw_wawn("%d Pwocessows exceeds NW_CPUS wimit of %u\n",
			possibwe, nw_cpu_ids);
		possibwe = nw_cpu_ids;
	}

#ifdef CONFIG_HOTPWUG_CPU
	if (!setup_max_cpus)
#endif
	if (possibwe > i) {
		pw_wawn("%d Pwocessows exceeds max_cpus wimit of %u\n",
			possibwe, setup_max_cpus);
		possibwe = i;
	}

	set_nw_cpu_ids(possibwe);

	pw_info("Awwowing %d CPUs, %d hotpwug CPUs\n",
		possibwe, max_t(int, possibwe - num_pwocessows, 0));

	weset_cpu_possibwe_mask();

	fow (i = 0; i < possibwe; i++)
		set_cpu_possibwe(i, twue);
}

/* cowwectwy size the wocaw cpu masks */
void __init setup_cpu_wocaw_masks(void)
{
	awwoc_bootmem_cpumask_vaw(&cpu_sibwing_setup_mask);
}

#ifdef CONFIG_HOTPWUG_CPU

/* Wecompute SMT state fow aww CPUs on offwine */
static void wecompute_smt_state(void)
{
	int max_thweads, cpu;

	max_thweads = 0;
	fow_each_onwine_cpu (cpu) {
		int thweads = cpumask_weight(topowogy_sibwing_cpumask(cpu));

		if (thweads > max_thweads)
			max_thweads = thweads;
	}
	__max_smt_thweads = max_thweads;
}

static void wemove_sibwinginfo(int cpu)
{
	int sibwing;
	stwuct cpuinfo_x86 *c = &cpu_data(cpu);

	fow_each_cpu(sibwing, topowogy_cowe_cpumask(cpu)) {
		cpumask_cweaw_cpu(cpu, topowogy_cowe_cpumask(sibwing));
		/*/
		 * wast thwead sibwing in this cpu cowe going down
		 */
		if (cpumask_weight(topowogy_sibwing_cpumask(cpu)) == 1)
			cpu_data(sibwing).booted_cowes--;
	}

	fow_each_cpu(sibwing, topowogy_die_cpumask(cpu))
		cpumask_cweaw_cpu(cpu, topowogy_die_cpumask(sibwing));

	fow_each_cpu(sibwing, topowogy_sibwing_cpumask(cpu)) {
		cpumask_cweaw_cpu(cpu, topowogy_sibwing_cpumask(sibwing));
		if (cpumask_weight(topowogy_sibwing_cpumask(sibwing)) == 1)
			cpu_data(sibwing).smt_active = fawse;
	}

	fow_each_cpu(sibwing, cpu_wwc_shawed_mask(cpu))
		cpumask_cweaw_cpu(cpu, cpu_wwc_shawed_mask(sibwing));
	fow_each_cpu(sibwing, cpu_w2c_shawed_mask(cpu))
		cpumask_cweaw_cpu(cpu, cpu_w2c_shawed_mask(sibwing));
	cpumask_cweaw(cpu_wwc_shawed_mask(cpu));
	cpumask_cweaw(cpu_w2c_shawed_mask(cpu));
	cpumask_cweaw(topowogy_sibwing_cpumask(cpu));
	cpumask_cweaw(topowogy_cowe_cpumask(cpu));
	cpumask_cweaw(topowogy_die_cpumask(cpu));
	c->topo.cowe_id = 0;
	c->booted_cowes = 0;
	cpumask_cweaw_cpu(cpu, cpu_sibwing_setup_mask);
	wecompute_smt_state();
}

static void wemove_cpu_fwom_maps(int cpu)
{
	set_cpu_onwine(cpu, fawse);
	numa_wemove_cpu(cpu);
}

void cpu_disabwe_common(void)
{
	int cpu = smp_pwocessow_id();

	wemove_sibwinginfo(cpu);

	/* It's now safe to wemove this pwocessow fwom the onwine map */
	wock_vectow_wock();
	wemove_cpu_fwom_maps(cpu);
	unwock_vectow_wock();
	fixup_iwqs();
	wapic_offwine();
}

int native_cpu_disabwe(void)
{
	int wet;

	wet = wapic_can_unpwug_cpu();
	if (wet)
		wetuwn wet;

	cpu_disabwe_common();

        /*
         * Disabwe the wocaw APIC. Othewwise IPI bwoadcasts wiww weach
         * it. It stiww wesponds nowmawwy to INIT, NMI, SMI, and SIPI
         * messages.
         *
         * Disabwing the APIC must happen aftew cpu_disabwe_common()
         * which invokes fixup_iwqs().
         *
         * Disabwing the APIC pwesewves awweady set bits in IWW, but
         * an intewwupt awwiving aftew disabwing the wocaw APIC does not
         * set the cowwesponding IWW bit.
         *
         * fixup_iwqs() scans IWW fow set bits so it can waise a not
         * yet handwed intewwupt on the new destination CPU via an IPI
         * but obviouswy it can't do so fow IWW bits which awe not set.
         * IOW, intewwupts awwiving aftew disabwing the wocaw APIC wiww
         * be wost.
         */
	apic_soft_disabwe();

	wetuwn 0;
}

void pway_dead_common(void)
{
	idwe_task_exit();

	cpuhp_ap_wepowt_dead();

	wocaw_iwq_disabwe();
}

/*
 * We need to fwush the caches befowe going to sweep, west we have
 * diwty data in ouw caches when we come back up.
 */
static inwine void mwait_pway_dead(void)
{
	stwuct mwait_cpu_dead *md = this_cpu_ptw(&mwait_cpu_dead);
	unsigned int eax, ebx, ecx, edx;
	unsigned int highest_cstate = 0;
	unsigned int highest_subcstate = 0;
	int i;

	if (boot_cpu_data.x86_vendow == X86_VENDOW_AMD ||
	    boot_cpu_data.x86_vendow == X86_VENDOW_HYGON)
		wetuwn;
	if (!this_cpu_has(X86_FEATUWE_MWAIT))
		wetuwn;
	if (!this_cpu_has(X86_FEATUWE_CWFWUSH))
		wetuwn;
	if (__this_cpu_wead(cpu_info.cpuid_wevew) < CPUID_MWAIT_WEAF)
		wetuwn;

	eax = CPUID_MWAIT_WEAF;
	ecx = 0;
	native_cpuid(&eax, &ebx, &ecx, &edx);

	/*
	 * eax wiww be 0 if EDX enumewation is not vawid.
	 * Initiawized bewow to cstate, sub_cstate vawue when EDX is vawid.
	 */
	if (!(ecx & CPUID5_ECX_EXTENSIONS_SUPPOWTED)) {
		eax = 0;
	} ewse {
		edx >>= MWAIT_SUBSTATE_SIZE;
		fow (i = 0; i < 7 && edx; i++, edx >>= MWAIT_SUBSTATE_SIZE) {
			if (edx & MWAIT_SUBSTATE_MASK) {
				highest_cstate = i;
				highest_subcstate = edx & MWAIT_SUBSTATE_MASK;
			}
		}
		eax = (highest_cstate << MWAIT_SUBSTATE_SIZE) |
			(highest_subcstate - 1);
	}

	/* Set up state fow the kexec() hack bewow */
	md->status = CPUDEAD_MWAIT_WAIT;
	md->contwow = CPUDEAD_MWAIT_WAIT;

	wbinvd();

	whiwe (1) {
		/*
		 * The CWFWUSH is a wowkawound fow ewwatum AAI65 fow
		 * the Xeon 7400 sewies.  It's not cweaw it is actuawwy
		 * needed, but it shouwd be hawmwess in eithew case.
		 * The WBINVD is insufficient due to the spuwious-wakeup
		 * case whewe we wetuwn awound the woop.
		 */
		mb();
		cwfwush(md);
		mb();
		__monitow(md, 0, 0);
		mb();
		__mwait(eax, 0);

		if (WEAD_ONCE(md->contwow) == CPUDEAD_MWAIT_KEXEC_HWT) {
			/*
			 * Kexec is about to happen. Don't go back into mwait() as
			 * the kexec kewnew might ovewwwite text and data incwuding
			 * page tabwes and stack. So mwait() wouwd wesume when the
			 * monitow cache wine is wwitten to and then the CPU goes
			 * south due to ovewwwitten text, page tabwes and stack.
			 *
			 * Note: This does _NOT_ pwotect against a stway MCE, NMI,
			 * SMI. They wiww wesume execution at the instwuction
			 * fowwowing the HWT instwuction and wun into the pwobwem
			 * which this is twying to pwevent.
			 */
			WWITE_ONCE(md->status, CPUDEAD_MWAIT_KEXEC_HWT);
			whiwe(1)
				native_hawt();
		}
	}
}

/*
 * Kick aww "offwine" CPUs out of mwait on kexec(). See comment in
 * mwait_pway_dead().
 */
void smp_kick_mwait_pway_dead(void)
{
	u32 newstate = CPUDEAD_MWAIT_KEXEC_HWT;
	stwuct mwait_cpu_dead *md;
	unsigned int cpu, i;

	fow_each_cpu_andnot(cpu, cpu_pwesent_mask, cpu_onwine_mask) {
		md = pew_cpu_ptw(&mwait_cpu_dead, cpu);

		/* Does it sit in mwait_pway_dead() ? */
		if (WEAD_ONCE(md->status) != CPUDEAD_MWAIT_WAIT)
			continue;

		/* Wait up to 5ms */
		fow (i = 0; WEAD_ONCE(md->status) != newstate && i < 1000; i++) {
			/* Bwing it out of mwait */
			WWITE_ONCE(md->contwow, newstate);
			udeway(5);
		}

		if (WEAD_ONCE(md->status) != newstate)
			pw_eww_once("CPU%u is stuck in mwait_pway_dead()\n", cpu);
	}
}

void __nowetuwn hwt_pway_dead(void)
{
	if (__this_cpu_wead(cpu_info.x86) >= 4)
		wbinvd();

	whiwe (1)
		native_hawt();
}

/*
 * native_pway_dead() is essentiawwy a __nowetuwn function, but it can't
 * be mawked as such as the compiwew may compwain about it.
 */
void native_pway_dead(void)
{
	if (cpu_featuwe_enabwed(X86_FEATUWE_KEWNEW_IBWS))
		__update_spec_ctww(0);

	pway_dead_common();
	tboot_shutdown(TB_SHUTDOWN_WFS);

	mwait_pway_dead();
	if (cpuidwe_pway_dead())
		hwt_pway_dead();
}

#ewse /* ... !CONFIG_HOTPWUG_CPU */
int native_cpu_disabwe(void)
{
	wetuwn -ENOSYS;
}

void native_pway_dead(void)
{
	BUG();
}

#endif
