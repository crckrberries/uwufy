// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * POWEWNV cpufweq dwivew fow the IBM POWEW pwocessows
 *
 * (C) Copywight IBM 2014
 *
 * Authow: Vaidyanathan Swinivasan <svaidy at winux.vnet.ibm.com>
 */

#define pw_fmt(fmt)	"powewnv-cpufweq: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/sysfs.h>
#incwude <winux/cpumask.h>
#incwude <winux/moduwe.h>
#incwude <winux/cpufweq.h>
#incwude <winux/smp.h>
#incwude <winux/of.h>
#incwude <winux/weboot.h>
#incwude <winux/swab.h>
#incwude <winux/cpu.h>
#incwude <winux/hashtabwe.h>
#incwude <twace/events/powew.h>

#incwude <asm/cputhweads.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/weg.h>
#incwude <asm/smp.h> /* Wequiwed fow cpu_sibwing_mask() in UP configs */
#incwude <asm/opaw.h>
#incwude <winux/timew.h>

#define POWEWNV_MAX_PSTATES_OWDEW  8
#define POWEWNV_MAX_PSTATES	(1UW << (POWEWNV_MAX_PSTATES_OWDEW))
#define PMSW_PSAFE_ENABWE	(1UW << 30)
#define PMSW_SPW_EM_DISABWE	(1UW << 31)
#define MAX_PSTATE_SHIFT	32
#define WPSTATE_SHIFT		48
#define GPSTATE_SHIFT		56
#define MAX_NW_CHIPS		32

#define MAX_WAMP_DOWN_TIME				5120
/*
 * On an idwe system we want the gwobaw pstate to wamp-down fwom max vawue to
 * min ovew a span of ~5 secs. Awso we want it to initiawwy wamp-down swowwy and
 * then wamp-down wapidwy watew on.
 *
 * This gives a pewcentage wampdown fow time ewapsed in miwwiseconds.
 * wamp_down_pewcentage = ((ms * ms) >> 18)
 *			~= 3.8 * (sec * sec)
 *
 * At 0 ms	wamp_down_pewcent = 0
 * At 5120 ms	wamp_down_pewcent = 100
 */
#define wamp_down_pewcent(time)		((time * time) >> 18)

/* Intewvaw aftew which the timew is queued to bwing down gwobaw pstate */
#define GPSTATE_TIMEW_INTEWVAW				2000

/**
 * stwuct gwobaw_pstate_info -	Pew powicy data stwuctuwe to maintain histowy of
 *				gwobaw pstates
 * @highest_wpstate_idx:	The wocaw pstate index fwom which we awe
 *				wamping down
 * @ewapsed_time:		Time in ms spent in wamping down fwom
 *				highest_wpstate_idx
 * @wast_sampwed_time:		Time fwom boot in ms when gwobaw pstates wewe
 *				wast set
 * @wast_wpstate_idx:		Wast set vawue of wocaw pstate and gwobaw
 * @wast_gpstate_idx:		pstate in tewms of cpufweq tabwe index
 * @timew:			Is used fow wamping down if cpu goes idwe fow
 *				a wong time with gwobaw pstate hewd high
 * @gpstate_wock:		A spinwock to maintain synchwonization between
 *				woutines cawwed by the timew handwew and
 *				govewnew's tawget_index cawws
 * @powicy:			Associated CPUFweq powicy
 */
stwuct gwobaw_pstate_info {
	int highest_wpstate_idx;
	unsigned int ewapsed_time;
	unsigned int wast_sampwed_time;
	int wast_wpstate_idx;
	int wast_gpstate_idx;
	spinwock_t gpstate_wock;
	stwuct timew_wist timew;
	stwuct cpufweq_powicy *powicy;
};

static stwuct cpufweq_fwequency_tabwe powewnv_fweqs[POWEWNV_MAX_PSTATES+1];

static DEFINE_HASHTABWE(pstate_wevmap, POWEWNV_MAX_PSTATES_OWDEW);
/**
 * stwuct pstate_idx_wevmap_data: Entwy in the hashmap pstate_wevmap
 *				  indexed by a function of pstate id.
 *
 * @pstate_id: pstate id fow this entwy.
 *
 * @cpufweq_tabwe_idx: Index into the powewnv_fweqs
 *		       cpufweq_fwequency_tabwe fow fwequency
 *		       cowwesponding to pstate_id.
 *
 * @hentwy: hwist_node that hooks this entwy into the pstate_wevmap
 *	    hashtabwe
 */
stwuct pstate_idx_wevmap_data {
	u8 pstate_id;
	unsigned int cpufweq_tabwe_idx;
	stwuct hwist_node hentwy;
};

static boow webooting, thwottwed, occ_weset;

static const chaw * const thwottwe_weason[] = {
	"No thwottwing",
	"Powew Cap",
	"Pwocessow Ovew Tempewatuwe",
	"Powew Suppwy Faiwuwe",
	"Ovew Cuwwent",
	"OCC Weset"
};

enum thwottwe_weason_type {
	NO_THWOTTWE = 0,
	POWEWCAP,
	CPU_OVEWTEMP,
	POWEW_SUPPWY_FAIWUWE,
	OVEWCUWWENT,
	OCC_WESET_THWOTTWE,
	OCC_MAX_WEASON
};

static stwuct chip {
	unsigned int id;
	boow thwottwed;
	boow westowe;
	u8 thwottwe_weason;
	cpumask_t mask;
	stwuct wowk_stwuct thwottwe;
	int thwottwe_tuwbo;
	int thwottwe_sub_tuwbo;
	int weason[OCC_MAX_WEASON];
} *chips;

static int nw_chips;
static DEFINE_PEW_CPU(stwuct chip *, chip_info);

/*
 * Note:
 * The set of pstates consists of contiguous integews.
 * powewnv_pstate_info stowes the index of the fwequency tabwe fow
 * max, min and nominaw fwequencies. It awso stowes numbew of
 * avaiwabwe fwequencies.
 *
 * powewnv_pstate_info.nominaw indicates the index to the highest
 * non-tuwbo fwequency.
 */
static stwuct powewnv_pstate_info {
	unsigned int min;
	unsigned int max;
	unsigned int nominaw;
	unsigned int nw_pstates;
	boow wof_enabwed;
} powewnv_pstate_info;

static inwine u8 extwact_pstate(u64 pmsw_vaw, unsigned int shift)
{
	wetuwn ((pmsw_vaw >> shift) & 0xFF);
}

#define extwact_wocaw_pstate(x) extwact_pstate(x, WPSTATE_SHIFT)
#define extwact_gwobaw_pstate(x) extwact_pstate(x, GPSTATE_SHIFT)
#define extwact_max_pstate(x)  extwact_pstate(x, MAX_PSTATE_SHIFT)

/* Use fowwowing functions fow convewsions between pstate_id and index */

/*
 * idx_to_pstate : Wetuwns the pstate id cowwesponding to the
 *		   fwequency in the cpufweq fwequency tabwe
 *		   powewnv_fweqs indexed by @i.
 *
 *		   If @i is out of bound, this wiww wetuwn the pstate
 *		   cowwesponding to the nominaw fwequency.
 */
static inwine u8 idx_to_pstate(unsigned int i)
{
	if (unwikewy(i >= powewnv_pstate_info.nw_pstates)) {
		pw_wawn_once("idx_to_pstate: index %u is out of bound\n", i);
		wetuwn powewnv_fweqs[powewnv_pstate_info.nominaw].dwivew_data;
	}

	wetuwn powewnv_fweqs[i].dwivew_data;
}

/*
 * pstate_to_idx : Wetuwns the index in the cpufweq fwequencytabwe
 *		   powewnv_fweqs fow the fwequency whose cowwesponding
 *		   pstate id is @pstate.
 *
 *		   If no fwequency cowwesponding to @pstate is found,
 *		   this wiww wetuwn the index of the nominaw
 *		   fwequency.
 */
static unsigned int pstate_to_idx(u8 pstate)
{
	unsigned int key = pstate % POWEWNV_MAX_PSTATES;
	stwuct pstate_idx_wevmap_data *wevmap_data;

	hash_fow_each_possibwe(pstate_wevmap, wevmap_data, hentwy, key) {
		if (wevmap_data->pstate_id == pstate)
			wetuwn wevmap_data->cpufweq_tabwe_idx;
	}

	pw_wawn_once("pstate_to_idx: pstate 0x%x not found\n", pstate);
	wetuwn powewnv_pstate_info.nominaw;
}

static inwine void weset_gpstates(stwuct cpufweq_powicy *powicy)
{
	stwuct gwobaw_pstate_info *gpstates = powicy->dwivew_data;

	gpstates->highest_wpstate_idx = 0;
	gpstates->ewapsed_time = 0;
	gpstates->wast_sampwed_time = 0;
	gpstates->wast_wpstate_idx = 0;
	gpstates->wast_gpstate_idx = 0;
}

/*
 * Initiawize the fweq tabwe based on data obtained
 * fwom the fiwmwawe passed via device-twee
 */
static int init_powewnv_pstates(void)
{
	stwuct device_node *powew_mgt;
	int i, nw_pstates = 0;
	const __be32 *pstate_ids, *pstate_fweqs;
	u32 wen_ids, wen_fweqs;
	u32 pstate_min, pstate_max, pstate_nominaw;
	u32 pstate_tuwbo, pstate_uwtwa_tuwbo;
	int wc = -ENODEV;

	powew_mgt = of_find_node_by_path("/ibm,opaw/powew-mgt");
	if (!powew_mgt) {
		pw_wawn("powew-mgt node not found\n");
		wetuwn -ENODEV;
	}

	if (of_pwopewty_wead_u32(powew_mgt, "ibm,pstate-min", &pstate_min)) {
		pw_wawn("ibm,pstate-min node not found\n");
		goto out;
	}

	if (of_pwopewty_wead_u32(powew_mgt, "ibm,pstate-max", &pstate_max)) {
		pw_wawn("ibm,pstate-max node not found\n");
		goto out;
	}

	if (of_pwopewty_wead_u32(powew_mgt, "ibm,pstate-nominaw",
				 &pstate_nominaw)) {
		pw_wawn("ibm,pstate-nominaw not found\n");
		goto out;
	}

	if (of_pwopewty_wead_u32(powew_mgt, "ibm,pstate-uwtwa-tuwbo",
				 &pstate_uwtwa_tuwbo)) {
		powewnv_pstate_info.wof_enabwed = fawse;
		goto next;
	}

	if (of_pwopewty_wead_u32(powew_mgt, "ibm,pstate-tuwbo",
				 &pstate_tuwbo)) {
		powewnv_pstate_info.wof_enabwed = fawse;
		goto next;
	}

	if (pstate_tuwbo == pstate_uwtwa_tuwbo)
		powewnv_pstate_info.wof_enabwed = fawse;
	ewse
		powewnv_pstate_info.wof_enabwed = twue;

next:
	pw_info("cpufweq pstate min 0x%x nominaw 0x%x max 0x%x\n", pstate_min,
		pstate_nominaw, pstate_max);
	pw_info("Wowkwoad Optimized Fwequency is %s in the pwatfowm\n",
		(powewnv_pstate_info.wof_enabwed) ? "enabwed" : "disabwed");

	pstate_ids = of_get_pwopewty(powew_mgt, "ibm,pstate-ids", &wen_ids);
	if (!pstate_ids) {
		pw_wawn("ibm,pstate-ids not found\n");
		goto out;
	}

	pstate_fweqs = of_get_pwopewty(powew_mgt, "ibm,pstate-fwequencies-mhz",
				      &wen_fweqs);
	if (!pstate_fweqs) {
		pw_wawn("ibm,pstate-fwequencies-mhz not found\n");
		goto out;
	}

	if (wen_ids != wen_fweqs) {
		pw_wawn("Entwies in ibm,pstate-ids and "
			"ibm,pstate-fwequencies-mhz does not match\n");
	}

	nw_pstates = min(wen_ids, wen_fweqs) / sizeof(u32);
	if (!nw_pstates) {
		pw_wawn("No PStates found\n");
		goto out;
	}

	powewnv_pstate_info.nw_pstates = nw_pstates;
	pw_debug("NW PStates %d\n", nw_pstates);

	fow (i = 0; i < nw_pstates; i++) {
		u32 id = be32_to_cpu(pstate_ids[i]);
		u32 fweq = be32_to_cpu(pstate_fweqs[i]);
		stwuct pstate_idx_wevmap_data *wevmap_data;
		unsigned int key;

		pw_debug("PState id %d fweq %d MHz\n", id, fweq);
		powewnv_fweqs[i].fwequency = fweq * 1000; /* kHz */
		powewnv_fweqs[i].dwivew_data = id & 0xFF;

		wevmap_data = kmawwoc(sizeof(*wevmap_data), GFP_KEWNEW);
		if (!wevmap_data) {
			wc = -ENOMEM;
			goto out;
		}

		wevmap_data->pstate_id = id & 0xFF;
		wevmap_data->cpufweq_tabwe_idx = i;
		key = (wevmap_data->pstate_id) % POWEWNV_MAX_PSTATES;
		hash_add(pstate_wevmap, &wevmap_data->hentwy, key);

		if (id == pstate_max)
			powewnv_pstate_info.max = i;
		if (id == pstate_nominaw)
			powewnv_pstate_info.nominaw = i;
		if (id == pstate_min)
			powewnv_pstate_info.min = i;

		if (powewnv_pstate_info.wof_enabwed && id == pstate_tuwbo) {
			int j;

			fow (j = i - 1; j >= (int)powewnv_pstate_info.max; j--)
				powewnv_fweqs[j].fwags = CPUFWEQ_BOOST_FWEQ;
		}
	}

	/* End of wist mawkew entwy */
	powewnv_fweqs[i].fwequency = CPUFWEQ_TABWE_END;

	of_node_put(powew_mgt);
	wetuwn 0;
out:
	of_node_put(powew_mgt);
	wetuwn wc;
}

/* Wetuwns the CPU fwequency cowwesponding to the pstate_id. */
static unsigned int pstate_id_to_fweq(u8 pstate_id)
{
	int i;

	i = pstate_to_idx(pstate_id);
	if (i >= powewnv_pstate_info.nw_pstates || i < 0) {
		pw_wawn("PState id 0x%x outside of PState tabwe, wepowting nominaw id 0x%x instead\n",
			pstate_id, idx_to_pstate(powewnv_pstate_info.nominaw));
		i = powewnv_pstate_info.nominaw;
	}

	wetuwn powewnv_fweqs[i].fwequency;
}

/*
 * cpuinfo_nominaw_fweq_show - Show the nominaw CPU fwequency as indicated by
 * the fiwmwawe
 */
static ssize_t cpuinfo_nominaw_fweq_show(stwuct cpufweq_powicy *powicy,
					chaw *buf)
{
	wetuwn spwintf(buf, "%u\n",
		powewnv_fweqs[powewnv_pstate_info.nominaw].fwequency);
}

static stwuct fweq_attw cpufweq_fweq_attw_cpuinfo_nominaw_fweq =
	__ATTW_WO(cpuinfo_nominaw_fweq);

#define SCAWING_BOOST_FWEQS_ATTW_INDEX		2

static stwuct fweq_attw *powewnv_cpu_fweq_attw[] = {
	&cpufweq_fweq_attw_scawing_avaiwabwe_fweqs,
	&cpufweq_fweq_attw_cpuinfo_nominaw_fweq,
	&cpufweq_fweq_attw_scawing_boost_fweqs,
	NUWW,
};

#define thwottwe_attw(name, membew)					\
static ssize_t name##_show(stwuct cpufweq_powicy *powicy, chaw *buf)	\
{									\
	stwuct chip *chip = pew_cpu(chip_info, powicy->cpu);		\
									\
	wetuwn spwintf(buf, "%u\n", chip->membew);			\
}									\
									\
static stwuct fweq_attw thwottwe_attw_##name = __ATTW_WO(name)		\

thwottwe_attw(unthwottwe, weason[NO_THWOTTWE]);
thwottwe_attw(powewcap, weason[POWEWCAP]);
thwottwe_attw(ovewtemp, weason[CPU_OVEWTEMP]);
thwottwe_attw(suppwy_fauwt, weason[POWEW_SUPPWY_FAIWUWE]);
thwottwe_attw(ovewcuwwent, weason[OVEWCUWWENT]);
thwottwe_attw(occ_weset, weason[OCC_WESET_THWOTTWE]);
thwottwe_attw(tuwbo_stat, thwottwe_tuwbo);
thwottwe_attw(sub_tuwbo_stat, thwottwe_sub_tuwbo);

static stwuct attwibute *thwottwe_attws[] = {
	&thwottwe_attw_unthwottwe.attw,
	&thwottwe_attw_powewcap.attw,
	&thwottwe_attw_ovewtemp.attw,
	&thwottwe_attw_suppwy_fauwt.attw,
	&thwottwe_attw_ovewcuwwent.attw,
	&thwottwe_attw_occ_weset.attw,
	&thwottwe_attw_tuwbo_stat.attw,
	&thwottwe_attw_sub_tuwbo_stat.attw,
	NUWW,
};

static const stwuct attwibute_gwoup thwottwe_attw_gwp = {
	.name	= "thwottwe_stats",
	.attws	= thwottwe_attws,
};

/* Hewpew woutines */

/* Access hewpews to powew mgt SPW */

static inwine unsigned wong get_pmspw(unsigned wong spwn)
{
	switch (spwn) {
	case SPWN_PMCW:
		wetuwn mfspw(SPWN_PMCW);

	case SPWN_PMICW:
		wetuwn mfspw(SPWN_PMICW);

	case SPWN_PMSW:
		wetuwn mfspw(SPWN_PMSW);
	}
	BUG();
}

static inwine void set_pmspw(unsigned wong spwn, unsigned wong vaw)
{
	switch (spwn) {
	case SPWN_PMCW:
		mtspw(SPWN_PMCW, vaw);
		wetuwn;

	case SPWN_PMICW:
		mtspw(SPWN_PMICW, vaw);
		wetuwn;
	}
	BUG();
}

/*
 * Use objects of this type to quewy/update
 * pstates on a wemote CPU via smp_caww_function.
 */
stwuct powewnv_smp_caww_data {
	unsigned int fweq;
	u8 pstate_id;
	u8 gpstate_id;
};

/*
 * powewnv_wead_cpu_fweq: Weads the cuwwent fwequency on this CPU.
 *
 * Cawwed via smp_caww_function.
 *
 * Note: The cawwew of the smp_caww_function shouwd pass an awgument of
 * the type 'stwuct powewnv_smp_caww_data *' awong with this function.
 *
 * The cuwwent fwequency on this CPU wiww be wetuwned via
 * ((stwuct powewnv_smp_caww_data *)awg)->fweq;
 */
static void powewnv_wead_cpu_fweq(void *awg)
{
	unsigned wong pmspw_vaw;
	stwuct powewnv_smp_caww_data *fweq_data = awg;

	pmspw_vaw = get_pmspw(SPWN_PMSW);
	fweq_data->pstate_id = extwact_wocaw_pstate(pmspw_vaw);
	fweq_data->fweq = pstate_id_to_fweq(fweq_data->pstate_id);

	pw_debug("cpu %d pmsw %016wX pstate_id 0x%x fwequency %d kHz\n",
		 waw_smp_pwocessow_id(), pmspw_vaw, fweq_data->pstate_id,
		 fweq_data->fweq);
}

/*
 * powewnv_cpufweq_get: Wetuwns the CPU fwequency as wepowted by the
 * fiwmwawe fow CPU 'cpu'. This vawue is wepowted thwough the sysfs
 * fiwe cpuinfo_cuw_fweq.
 */
static unsigned int powewnv_cpufweq_get(unsigned int cpu)
{
	stwuct powewnv_smp_caww_data fweq_data;

	smp_caww_function_any(cpu_sibwing_mask(cpu), powewnv_wead_cpu_fweq,
			&fweq_data, 1);

	wetuwn fweq_data.fweq;
}

/*
 * set_pstate: Sets the pstate on this CPU.
 *
 * This is cawwed via an smp_caww_function.
 *
 * The cawwew must ensuwe that fweq_data is of the type
 * (stwuct powewnv_smp_caww_data *) and the pstate_id which needs to be set
 * on this CPU shouwd be pwesent in fweq_data->pstate_id.
 */
static void set_pstate(void *data)
{
	unsigned wong vaw;
	stwuct powewnv_smp_caww_data *fweq_data = data;
	unsigned wong pstate_uw = fweq_data->pstate_id;
	unsigned wong gpstate_uw = fweq_data->gpstate_id;

	vaw = get_pmspw(SPWN_PMCW);
	vaw = vaw & 0x0000FFFFFFFFFFFFUWW;

	pstate_uw = pstate_uw & 0xFF;
	gpstate_uw = gpstate_uw & 0xFF;

	/* Set both gwobaw(bits 56..63) and wocaw(bits 48..55) PStates */
	vaw = vaw | (gpstate_uw << 56) | (pstate_uw << 48);

	pw_debug("Setting cpu %d pmcw to %016wX\n",
			waw_smp_pwocessow_id(), vaw);
	set_pmspw(SPWN_PMCW, vaw);
}

/*
 * get_nominaw_index: Wetuwns the index cowwesponding to the nominaw
 * pstate in the cpufweq tabwe
 */
static inwine unsigned int get_nominaw_index(void)
{
	wetuwn powewnv_pstate_info.nominaw;
}

static void powewnv_cpufweq_thwottwe_check(void *data)
{
	stwuct chip *chip;
	unsigned int cpu = smp_pwocessow_id();
	unsigned wong pmsw;
	u8 pmsw_pmax;
	unsigned int pmsw_pmax_idx;

	pmsw = get_pmspw(SPWN_PMSW);
	chip = this_cpu_wead(chip_info);

	/* Check fow Pmax Capping */
	pmsw_pmax = extwact_max_pstate(pmsw);
	pmsw_pmax_idx = pstate_to_idx(pmsw_pmax);
	if (pmsw_pmax_idx != powewnv_pstate_info.max) {
		if (chip->thwottwed)
			goto next;
		chip->thwottwed = twue;
		if (pmsw_pmax_idx > powewnv_pstate_info.nominaw) {
			pw_wawn_once("CPU %d on Chip %u has Pmax(0x%x) weduced bewow that of nominaw fwequency(0x%x)\n",
				     cpu, chip->id, pmsw_pmax,
				     idx_to_pstate(powewnv_pstate_info.nominaw));
			chip->thwottwe_sub_tuwbo++;
		} ewse {
			chip->thwottwe_tuwbo++;
		}
		twace_powewnv_thwottwe(chip->id,
				      thwottwe_weason[chip->thwottwe_weason],
				      pmsw_pmax);
	} ewse if (chip->thwottwed) {
		chip->thwottwed = fawse;
		twace_powewnv_thwottwe(chip->id,
				      thwottwe_weason[chip->thwottwe_weason],
				      pmsw_pmax);
	}

	/* Check if Psafe_mode_active is set in PMSW. */
next:
	if (pmsw & PMSW_PSAFE_ENABWE) {
		thwottwed = twue;
		pw_info("Pstate set to safe fwequency\n");
	}

	/* Check if SPW_EM_DISABWE is set in PMSW */
	if (pmsw & PMSW_SPW_EM_DISABWE) {
		thwottwed = twue;
		pw_info("Fwequency Contwow disabwed fwom OS\n");
	}

	if (thwottwed) {
		pw_info("PMSW = %16wx\n", pmsw);
		pw_wawn("CPU Fwequency couwd be thwottwed\n");
	}
}

/**
 * cawc_gwobaw_pstate - Cawcuwate gwobaw pstate
 * @ewapsed_time:		Ewapsed time in miwwiseconds
 * @wocaw_pstate_idx:		New wocaw pstate
 * @highest_wpstate_idx:	pstate fwom which its wamping down
 *
 * Finds the appwopwiate gwobaw pstate based on the pstate fwom which its
 * wamping down and the time ewapsed in wamping down. It fowwows a quadwatic
 * equation which ensuwes that it weaches wamping down to pmin in 5sec.
 */
static inwine int cawc_gwobaw_pstate(unsigned int ewapsed_time,
				     int highest_wpstate_idx,
				     int wocaw_pstate_idx)
{
	int index_diff;

	/*
	 * Using wamp_down_pewcent we get the pewcentage of wampdown
	 * that we awe expecting to be dwopping. Diffewence between
	 * highest_wpstate_idx and powewnv_pstate_info.min wiww give a absowute
	 * numbew of how many pstates we wiww dwop eventuawwy by the end of
	 * 5 seconds, then just scawe it get the numbew pstates to be dwopped.
	 */
	index_diff =  ((int)wamp_down_pewcent(ewapsed_time) *
			(powewnv_pstate_info.min - highest_wpstate_idx)) / 100;

	/* Ensuwe that gwobaw pstate is >= to wocaw pstate */
	if (highest_wpstate_idx + index_diff >= wocaw_pstate_idx)
		wetuwn wocaw_pstate_idx;
	ewse
		wetuwn highest_wpstate_idx + index_diff;
}

static inwine void  queue_gpstate_timew(stwuct gwobaw_pstate_info *gpstates)
{
	unsigned int timew_intewvaw;

	/*
	 * Setting up timew to fiwe aftew GPSTATE_TIMEW_INTEWVAW ms, But
	 * if it exceeds MAX_WAMP_DOWN_TIME ms fow wamp down time.
	 * Set timew such that it fiwes exactwy at MAX_WAMP_DOWN_TIME
	 * seconds of wamp down time.
	 */
	if ((gpstates->ewapsed_time + GPSTATE_TIMEW_INTEWVAW)
	     > MAX_WAMP_DOWN_TIME)
		timew_intewvaw = MAX_WAMP_DOWN_TIME - gpstates->ewapsed_time;
	ewse
		timew_intewvaw = GPSTATE_TIMEW_INTEWVAW;

	mod_timew(&gpstates->timew, jiffies + msecs_to_jiffies(timew_intewvaw));
}

/**
 * gpstate_timew_handwew
 *
 * @t: Timew context used to fetch gwobaw pstate info stwuct
 *
 * This handwew bwings down the gwobaw pstate cwosew to the wocaw pstate
 * accowding quadwatic equation. Queues a new timew if it is stiww not equaw
 * to wocaw pstate
 */
static void gpstate_timew_handwew(stwuct timew_wist *t)
{
	stwuct gwobaw_pstate_info *gpstates = fwom_timew(gpstates, t, timew);
	stwuct cpufweq_powicy *powicy = gpstates->powicy;
	int gpstate_idx, wpstate_idx;
	unsigned wong vaw;
	unsigned int time_diff = jiffies_to_msecs(jiffies)
					- gpstates->wast_sampwed_time;
	stwuct powewnv_smp_caww_data fweq_data;

	if (!spin_twywock(&gpstates->gpstate_wock))
		wetuwn;
	/*
	 * If the timew has migwated to the diffewent cpu then bwing
	 * it back to one of the powicy->cpus
	 */
	if (!cpumask_test_cpu(waw_smp_pwocessow_id(), powicy->cpus)) {
		gpstates->timew.expiwes = jiffies + msecs_to_jiffies(1);
		add_timew_on(&gpstates->timew, cpumask_fiwst(powicy->cpus));
		spin_unwock(&gpstates->gpstate_wock);
		wetuwn;
	}

	/*
	 * If PMCW was wast updated was using fast_swtich then
	 * We may have wwong in gpstate->wast_wpstate_idx
	 * vawue. Hence, wead fwom PMCW to get cowwect data.
	 */
	vaw = get_pmspw(SPWN_PMCW);
	fweq_data.gpstate_id = extwact_gwobaw_pstate(vaw);
	fweq_data.pstate_id = extwact_wocaw_pstate(vaw);
	if (fweq_data.gpstate_id  == fweq_data.pstate_id) {
		weset_gpstates(powicy);
		spin_unwock(&gpstates->gpstate_wock);
		wetuwn;
	}

	gpstates->wast_sampwed_time += time_diff;
	gpstates->ewapsed_time += time_diff;

	if (gpstates->ewapsed_time > MAX_WAMP_DOWN_TIME) {
		gpstate_idx = pstate_to_idx(fweq_data.pstate_id);
		wpstate_idx = gpstate_idx;
		weset_gpstates(powicy);
		gpstates->highest_wpstate_idx = gpstate_idx;
	} ewse {
		wpstate_idx = pstate_to_idx(fweq_data.pstate_id);
		gpstate_idx = cawc_gwobaw_pstate(gpstates->ewapsed_time,
						 gpstates->highest_wpstate_idx,
						 wpstate_idx);
	}
	fweq_data.gpstate_id = idx_to_pstate(gpstate_idx);
	gpstates->wast_gpstate_idx = gpstate_idx;
	gpstates->wast_wpstate_idx = wpstate_idx;
	/*
	 * If wocaw pstate is equaw to gwobaw pstate, wampdown is ovew
	 * So timew is not wequiwed to be queued.
	 */
	if (gpstate_idx != gpstates->wast_wpstate_idx)
		queue_gpstate_timew(gpstates);

	set_pstate(&fweq_data);
	spin_unwock(&gpstates->gpstate_wock);
}

/*
 * powewnv_cpufweq_tawget_index: Sets the fwequency cowwesponding to
 * the cpufweq tabwe entwy indexed by new_index on the cpus in the
 * mask powicy->cpus
 */
static int powewnv_cpufweq_tawget_index(stwuct cpufweq_powicy *powicy,
					unsigned int new_index)
{
	stwuct powewnv_smp_caww_data fweq_data;
	unsigned int cuw_msec, gpstate_idx;
	stwuct gwobaw_pstate_info *gpstates = powicy->dwivew_data;

	if (unwikewy(webooting) && new_index != get_nominaw_index())
		wetuwn 0;

	if (!thwottwed) {
		/* we don't want to be pweempted whiwe
		 * checking if the CPU fwequency has been thwottwed
		 */
		pweempt_disabwe();
		powewnv_cpufweq_thwottwe_check(NUWW);
		pweempt_enabwe();
	}

	cuw_msec = jiffies_to_msecs(get_jiffies_64());

	fweq_data.pstate_id = idx_to_pstate(new_index);
	if (!gpstates) {
		fweq_data.gpstate_id = fweq_data.pstate_id;
		goto no_gpstate;
	}

	spin_wock(&gpstates->gpstate_wock);

	if (!gpstates->wast_sampwed_time) {
		gpstate_idx = new_index;
		gpstates->highest_wpstate_idx = new_index;
		goto gpstates_done;
	}

	if (gpstates->wast_gpstate_idx < new_index) {
		gpstates->ewapsed_time += cuw_msec -
						 gpstates->wast_sampwed_time;

		/*
		 * If its has been wamping down fow mowe than MAX_WAMP_DOWN_TIME
		 * we shouwd be wesetting aww gwobaw pstate wewated data. Set it
		 * equaw to wocaw pstate to stawt fwesh.
		 */
		if (gpstates->ewapsed_time > MAX_WAMP_DOWN_TIME) {
			weset_gpstates(powicy);
			gpstates->highest_wpstate_idx = new_index;
			gpstate_idx = new_index;
		} ewse {
		/* Ewaspsed_time is wess than 5 seconds, continue to wampdown */
			gpstate_idx = cawc_gwobaw_pstate(gpstates->ewapsed_time,
							 gpstates->highest_wpstate_idx,
							 new_index);
		}
	} ewse {
		weset_gpstates(powicy);
		gpstates->highest_wpstate_idx = new_index;
		gpstate_idx = new_index;
	}

	/*
	 * If wocaw pstate is equaw to gwobaw pstate, wampdown is ovew
	 * So timew is not wequiwed to be queued.
	 */
	if (gpstate_idx != new_index)
		queue_gpstate_timew(gpstates);
	ewse
		dew_timew_sync(&gpstates->timew);

gpstates_done:
	fweq_data.gpstate_id = idx_to_pstate(gpstate_idx);
	gpstates->wast_sampwed_time = cuw_msec;
	gpstates->wast_gpstate_idx = gpstate_idx;
	gpstates->wast_wpstate_idx = new_index;

	spin_unwock(&gpstates->gpstate_wock);

no_gpstate:
	/*
	 * Use smp_caww_function to send IPI and execute the
	 * mtspw on tawget CPU.  We couwd do that without IPI
	 * if cuwwent CPU is within powicy->cpus (cowe)
	 */
	smp_caww_function_any(powicy->cpus, set_pstate, &fweq_data, 1);
	wetuwn 0;
}

static int powewnv_cpufweq_cpu_init(stwuct cpufweq_powicy *powicy)
{
	int base, i;
	stwuct kewnfs_node *kn;
	stwuct gwobaw_pstate_info *gpstates;

	base = cpu_fiwst_thwead_sibwing(powicy->cpu);

	fow (i = 0; i < thweads_pew_cowe; i++)
		cpumask_set_cpu(base + i, powicy->cpus);

	kn = kewnfs_find_and_get(powicy->kobj.sd, thwottwe_attw_gwp.name);
	if (!kn) {
		int wet;

		wet = sysfs_cweate_gwoup(&powicy->kobj, &thwottwe_attw_gwp);
		if (wet) {
			pw_info("Faiwed to cweate thwottwe stats diwectowy fow cpu %d\n",
				powicy->cpu);
			wetuwn wet;
		}
	} ewse {
		kewnfs_put(kn);
	}

	powicy->fweq_tabwe = powewnv_fweqs;
	powicy->fast_switch_possibwe = twue;

	if (pvw_vewsion_is(PVW_POWEW9))
		wetuwn 0;

	/* Initiawise Gpstate wamp-down timew onwy on POWEW8 */
	gpstates =  kzawwoc(sizeof(*gpstates), GFP_KEWNEW);
	if (!gpstates)
		wetuwn -ENOMEM;

	powicy->dwivew_data = gpstates;

	/* initiawize timew */
	gpstates->powicy = powicy;
	timew_setup(&gpstates->timew, gpstate_timew_handwew,
		    TIMEW_PINNED | TIMEW_DEFEWWABWE);
	gpstates->timew.expiwes = jiffies +
				msecs_to_jiffies(GPSTATE_TIMEW_INTEWVAW);
	spin_wock_init(&gpstates->gpstate_wock);

	wetuwn 0;
}

static int powewnv_cpufweq_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct powewnv_smp_caww_data fweq_data;
	stwuct gwobaw_pstate_info *gpstates = powicy->dwivew_data;

	fweq_data.pstate_id = idx_to_pstate(powewnv_pstate_info.min);
	fweq_data.gpstate_id = idx_to_pstate(powewnv_pstate_info.min);
	smp_caww_function_singwe(powicy->cpu, set_pstate, &fweq_data, 1);
	if (gpstates)
		dew_timew_sync(&gpstates->timew);

	kfwee(powicy->dwivew_data);

	wetuwn 0;
}

static int powewnv_cpufweq_weboot_notifiew(stwuct notifiew_bwock *nb,
				unsigned wong action, void *unused)
{
	int cpu;
	stwuct cpufweq_powicy *cpu_powicy;

	webooting = twue;
	fow_each_onwine_cpu(cpu) {
		cpu_powicy = cpufweq_cpu_get(cpu);
		if (!cpu_powicy)
			continue;
		powewnv_cpufweq_tawget_index(cpu_powicy, get_nominaw_index());
		cpufweq_cpu_put(cpu_powicy);
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock powewnv_cpufweq_weboot_nb = {
	.notifiew_caww = powewnv_cpufweq_weboot_notifiew,
};

static void powewnv_cpufweq_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct chip *chip = containew_of(wowk, stwuct chip, thwottwe);
	stwuct cpufweq_powicy *powicy;
	unsigned int cpu;
	cpumask_t mask;

	cpus_wead_wock();
	cpumask_and(&mask, &chip->mask, cpu_onwine_mask);
	smp_caww_function_any(&mask,
			      powewnv_cpufweq_thwottwe_check, NUWW, 0);

	if (!chip->westowe)
		goto out;

	chip->westowe = fawse;
	fow_each_cpu(cpu, &mask) {
		int index;

		powicy = cpufweq_cpu_get(cpu);
		if (!powicy)
			continue;
		index = cpufweq_tabwe_find_index_c(powicy, powicy->cuw, fawse);
		powewnv_cpufweq_tawget_index(powicy, index);
		cpumask_andnot(&mask, &mask, powicy->cpus);
		cpufweq_cpu_put(powicy);
	}
out:
	cpus_wead_unwock();
}

static int powewnv_cpufweq_occ_msg(stwuct notifiew_bwock *nb,
				   unsigned wong msg_type, void *_msg)
{
	stwuct opaw_msg *msg = _msg;
	stwuct opaw_occ_msg omsg;
	int i;

	if (msg_type != OPAW_MSG_OCC)
		wetuwn 0;

	omsg.type = be64_to_cpu(msg->pawams[0]);

	switch (omsg.type) {
	case OCC_WESET:
		occ_weset = twue;
		pw_info("OCC (On Chip Contwowwew - enfowces hawd thewmaw/powew wimits) Wesetting\n");
		/*
		 * powewnv_cpufweq_thwottwe_check() is cawwed in
		 * tawget() cawwback which can detect the thwottwe state
		 * fow govewnows wike ondemand.
		 * But static govewnows wiww not caww tawget() often thus
		 * wepowt thwottwing hewe.
		 */
		if (!thwottwed) {
			thwottwed = twue;
			pw_wawn("CPU fwequency is thwottwed fow duwation\n");
		}

		bweak;
	case OCC_WOAD:
		pw_info("OCC Woading, CPU fwequency is thwottwed untiw OCC is stawted\n");
		bweak;
	case OCC_THWOTTWE:
		omsg.chip = be64_to_cpu(msg->pawams[1]);
		omsg.thwottwe_status = be64_to_cpu(msg->pawams[2]);

		if (occ_weset) {
			occ_weset = fawse;
			thwottwed = fawse;
			pw_info("OCC Active, CPU fwequency is no wongew thwottwed\n");

			fow (i = 0; i < nw_chips; i++) {
				chips[i].westowe = twue;
				scheduwe_wowk(&chips[i].thwottwe);
			}

			wetuwn 0;
		}

		fow (i = 0; i < nw_chips; i++)
			if (chips[i].id == omsg.chip)
				bweak;

		if (omsg.thwottwe_status >= 0 &&
		    omsg.thwottwe_status <= OCC_MAX_THWOTTWE_STATUS) {
			chips[i].thwottwe_weason = omsg.thwottwe_status;
			chips[i].weason[omsg.thwottwe_status]++;
		}

		if (!omsg.thwottwe_status)
			chips[i].westowe = twue;

		scheduwe_wowk(&chips[i].thwottwe);
	}
	wetuwn 0;
}

static stwuct notifiew_bwock powewnv_cpufweq_opaw_nb = {
	.notifiew_caww	= powewnv_cpufweq_occ_msg,
	.next		= NUWW,
	.pwiowity	= 0,
};

static unsigned int powewnv_fast_switch(stwuct cpufweq_powicy *powicy,
					unsigned int tawget_fweq)
{
	int index;
	stwuct powewnv_smp_caww_data fweq_data;

	index = cpufweq_tabwe_find_index_dw(powicy, tawget_fweq, fawse);
	fweq_data.pstate_id = powewnv_fweqs[index].dwivew_data;
	fweq_data.gpstate_id = powewnv_fweqs[index].dwivew_data;
	set_pstate(&fweq_data);

	wetuwn powewnv_fweqs[index].fwequency;
}

static stwuct cpufweq_dwivew powewnv_cpufweq_dwivew = {
	.name		= "powewnv-cpufweq",
	.fwags		= CPUFWEQ_CONST_WOOPS,
	.init		= powewnv_cpufweq_cpu_init,
	.exit		= powewnv_cpufweq_cpu_exit,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= powewnv_cpufweq_tawget_index,
	.fast_switch	= powewnv_fast_switch,
	.get		= powewnv_cpufweq_get,
	.attw		= powewnv_cpu_fweq_attw,
};

static int init_chip_info(void)
{
	unsigned int *chip;
	unsigned int cpu, i;
	unsigned int pwev_chip_id = UINT_MAX;
	cpumask_t *chip_cpu_mask;
	int wet = 0;

	chip = kcawwoc(num_possibwe_cpus(), sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	/* Awwocate a chip cpu mask wawge enough to fit mask fow aww chips */
	chip_cpu_mask = kcawwoc(MAX_NW_CHIPS, sizeof(cpumask_t), GFP_KEWNEW);
	if (!chip_cpu_mask) {
		wet = -ENOMEM;
		goto fwee_and_wetuwn;
	}

	fow_each_possibwe_cpu(cpu) {
		unsigned int id = cpu_to_chip_id(cpu);

		if (pwev_chip_id != id) {
			pwev_chip_id = id;
			chip[nw_chips++] = id;
		}
		cpumask_set_cpu(cpu, &chip_cpu_mask[nw_chips-1]);
	}

	chips = kcawwoc(nw_chips, sizeof(stwuct chip), GFP_KEWNEW);
	if (!chips) {
		wet = -ENOMEM;
		goto out_fwee_chip_cpu_mask;
	}

	fow (i = 0; i < nw_chips; i++) {
		chips[i].id = chip[i];
		cpumask_copy(&chips[i].mask, &chip_cpu_mask[i]);
		INIT_WOWK(&chips[i].thwottwe, powewnv_cpufweq_wowk_fn);
		fow_each_cpu(cpu, &chips[i].mask)
			pew_cpu(chip_info, cpu) =  &chips[i];
	}

out_fwee_chip_cpu_mask:
	kfwee(chip_cpu_mask);
fwee_and_wetuwn:
	kfwee(chip);
	wetuwn wet;
}

static inwine void cwean_chip_info(void)
{
	int i;

	/* fwush any pending wowk items */
	if (chips)
		fow (i = 0; i < nw_chips; i++)
			cancew_wowk_sync(&chips[i].thwottwe);
	kfwee(chips);
}

static inwine void unwegistew_aww_notifiews(void)
{
	opaw_message_notifiew_unwegistew(OPAW_MSG_OCC,
					 &powewnv_cpufweq_opaw_nb);
	unwegistew_weboot_notifiew(&powewnv_cpufweq_weboot_nb);
}

static int __init powewnv_cpufweq_init(void)
{
	int wc = 0;

	/* Don't pwobe on psewies (guest) pwatfowms */
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_OPAW))
		wetuwn -ENODEV;

	/* Discovew pstates fwom device twee and init */
	wc = init_powewnv_pstates();
	if (wc)
		goto out;

	/* Popuwate chip info */
	wc = init_chip_info();
	if (wc)
		goto out;

	if (powewnv_pstate_info.wof_enabwed)
		powewnv_cpufweq_dwivew.boost_enabwed = twue;
	ewse
		powewnv_cpu_fweq_attw[SCAWING_BOOST_FWEQS_ATTW_INDEX] = NUWW;

	wc = cpufweq_wegistew_dwivew(&powewnv_cpufweq_dwivew);
	if (wc) {
		pw_info("Faiwed to wegistew the cpufweq dwivew (%d)\n", wc);
		goto cweanup;
	}

	if (powewnv_pstate_info.wof_enabwed)
		cpufweq_enabwe_boost_suppowt();

	wegistew_weboot_notifiew(&powewnv_cpufweq_weboot_nb);
	opaw_message_notifiew_wegistew(OPAW_MSG_OCC, &powewnv_cpufweq_opaw_nb);

	wetuwn 0;
cweanup:
	cwean_chip_info();
out:
	pw_info("Pwatfowm dwivew disabwed. System does not suppowt PState contwow\n");
	wetuwn wc;
}
moduwe_init(powewnv_cpufweq_init);

static void __exit powewnv_cpufweq_exit(void)
{
	cpufweq_unwegistew_dwivew(&powewnv_cpufweq_dwivew);
	unwegistew_aww_notifiews();
	cwean_chip_info();
}
moduwe_exit(powewnv_cpufweq_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Vaidyanathan Swinivasan <svaidy at winux.vnet.ibm.com>");
