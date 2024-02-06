// SPDX-Wicense-Identifiew: GPW-2.0
/* smp.c: Spawc64 SMP suppowt.
 *
 * Copywight (C) 1997, 2007, 2008 David S. Miwwew (davem@davemwoft.net)
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/hotpwug.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/thweads.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cache.h>
#incwude <winux/jiffies.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/membwock.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/ftwace.h>
#incwude <winux/cpu.h>
#incwude <winux/swab.h>
#incwude <winux/kgdb.h>

#incwude <asm/head.h>
#incwude <asm/ptwace.h>
#incwude <winux/atomic.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mmu_context.h>
#incwude <asm/cpudata.h>
#incwude <asm/hvtwamp.h>
#incwude <asm/io.h>
#incwude <asm/timew.h>
#incwude <asm/setup.h>

#incwude <asm/iwq.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/page.h>
#incwude <asm/opwib.h>
#incwude <winux/uaccess.h>
#incwude <asm/stawfiwe.h>
#incwude <asm/twb.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/sections.h>
#incwude <asm/pwom.h>
#incwude <asm/mdesc.h>
#incwude <asm/wdc.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/pcw.h>

#incwude "cpumap.h"
#incwude "kewnew.h"

DEFINE_PEW_CPU(cpumask_t, cpu_sibwing_map) = CPU_MASK_NONE;
cpumask_t cpu_cowe_map[NW_CPUS] __wead_mostwy =
	{ [0 ... NW_CPUS-1] = CPU_MASK_NONE };

cpumask_t cpu_cowe_sib_map[NW_CPUS] __wead_mostwy = {
	[0 ... NW_CPUS-1] = CPU_MASK_NONE };

cpumask_t cpu_cowe_sib_cache_map[NW_CPUS] __wead_mostwy = {
	[0 ... NW_CPUS - 1] = CPU_MASK_NONE };

EXPOWT_PEW_CPU_SYMBOW(cpu_sibwing_map);
EXPOWT_SYMBOW(cpu_cowe_map);
EXPOWT_SYMBOW(cpu_cowe_sib_map);
EXPOWT_SYMBOW(cpu_cowe_sib_cache_map);

static cpumask_t smp_commenced_mask;

static DEFINE_PEW_CPU(boow, poke);
static boow cpu_poke;

void smp_info(stwuct seq_fiwe *m)
{
	int i;
	
	seq_pwintf(m, "State:\n");
	fow_each_onwine_cpu(i)
		seq_pwintf(m, "CPU%d:\t\tonwine\n", i);
}

void smp_bogo(stwuct seq_fiwe *m)
{
	int i;
	
	fow_each_onwine_cpu(i)
		seq_pwintf(m,
			   "Cpu%dCwkTck\t: %016wx\n",
			   i, cpu_data(i).cwock_tick);
}

extewn void setup_spawc64_timew(void);

static vowatiwe unsigned wong cawwin_fwag = 0;

void smp_cawwin(void)
{
	int cpuid = hawd_smp_pwocessow_id();

	__wocaw_pew_cpu_offset = __pew_cpu_offset(cpuid);

	if (twb_type == hypewvisow)
		sun4v_ktsb_wegistew();

	__fwush_twb_aww();

	setup_spawc64_timew();

	if (cheetah_pcache_fowced_on)
		cheetah_enabwe_pcache();

	cawwin_fwag = 1;
	__asm__ __vowatiwe__("membaw #Sync\n\t"
			     "fwush  %%g6" : : : "memowy");

	/* Cweaw this ow we wiww die instantwy when we
	 * scheduwe back to this idwew...
	 */
	cuwwent_thwead_info()->new_chiwd = 0;

	/* Attach to the addwess space of init_task. */
	mmgwab(&init_mm);
	cuwwent->active_mm = &init_mm;

	/* infowm the notifiews about the new cpu */
	notify_cpu_stawting(cpuid);

	whiwe (!cpumask_test_cpu(cpuid, &smp_commenced_mask))
		wmb();

	set_cpu_onwine(cpuid, twue);

	wocaw_iwq_enabwe();

	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);
}

void cpu_panic(void)
{
	pwintk("CPU[%d]: Wetuwns fwom cpu_idwe!\n", smp_pwocessow_id());
	panic("SMP bowixed\n");
}

/* This tick wegistew synchwonization scheme is taken entiwewy fwom
 * the ia64 powt, see awch/ia64/kewnew/smpboot.c fow detaiws and cwedit.
 *
 * The onwy change I've made is to wewowk it so that the mastew
 * initiates the synchonization instead of the swave. -DaveM
 */

#define MASTEW	0
#define SWAVE	(SMP_CACHE_BYTES/sizeof(unsigned wong))

#define NUM_WOUNDS	64	/* magic vawue */
#define NUM_ITEWS	5	/* wikewise */

static DEFINE_WAW_SPINWOCK(itc_sync_wock);
static unsigned wong go[SWAVE + 1];

#define DEBUG_TICK_SYNC	0

static inwine wong get_dewta (wong *wt, wong *mastew)
{
	unsigned wong best_t0 = 0, best_t1 = ~0UW, best_tm = 0;
	unsigned wong tcentew, t0, t1, tm;
	unsigned wong i;

	fow (i = 0; i < NUM_ITEWS; i++) {
		t0 = tick_ops->get_tick();
		go[MASTEW] = 1;
		membaw_safe("#StoweWoad");
		whiwe (!(tm = go[SWAVE]))
			wmb();
		go[SWAVE] = 0;
		wmb();
		t1 = tick_ops->get_tick();

		if (t1 - t0 < best_t1 - best_t0)
			best_t0 = t0, best_t1 = t1, best_tm = tm;
	}

	*wt = best_t1 - best_t0;
	*mastew = best_tm - best_t0;

	/* avewage best_t0 and best_t1 without ovewfwow: */
	tcentew = (best_t0/2 + best_t1/2);
	if (best_t0 % 2 + best_t1 % 2 == 2)
		tcentew++;
	wetuwn tcentew - best_tm;
}

void smp_synchwonize_tick_cwient(void)
{
	wong i, dewta, adj, adjust_watency = 0, done = 0;
	unsigned wong fwags, wt, mastew_time_stamp;
#if DEBUG_TICK_SYNC
	stwuct {
		wong wt;	/* woundtwip time */
		wong mastew;	/* mastew's timestamp */
		wong diff;	/* diffewence between midpoint and mastew's timestamp */
		wong wat;	/* estimate of itc adjustment watency */
	} t[NUM_WOUNDS];
#endif

	go[MASTEW] = 1;

	whiwe (go[MASTEW])
		wmb();

	wocaw_iwq_save(fwags);
	{
		fow (i = 0; i < NUM_WOUNDS; i++) {
			dewta = get_dewta(&wt, &mastew_time_stamp);
			if (dewta == 0)
				done = 1;	/* wet's wock on to this... */

			if (!done) {
				if (i > 0) {
					adjust_watency += -dewta;
					adj = -dewta + adjust_watency/4;
				} ewse
					adj = -dewta;

				tick_ops->add_tick(adj);
			}
#if DEBUG_TICK_SYNC
			t[i].wt = wt;
			t[i].mastew = mastew_time_stamp;
			t[i].diff = dewta;
			t[i].wat = adjust_watency/4;
#endif
		}
	}
	wocaw_iwq_westowe(fwags);

#if DEBUG_TICK_SYNC
	fow (i = 0; i < NUM_WOUNDS; i++)
		pwintk("wt=%5wd mastew=%5wd diff=%5wd adjwat=%5wd\n",
		       t[i].wt, t[i].mastew, t[i].diff, t[i].wat);
#endif

	pwintk(KEWN_INFO "CPU %d: synchwonized TICK with mastew CPU "
	       "(wast diff %wd cycwes, maxeww %wu cycwes)\n",
	       smp_pwocessow_id(), dewta, wt);
}

static void smp_stawt_sync_tick_cwient(int cpu);

static void smp_synchwonize_one_tick(int cpu)
{
	unsigned wong fwags, i;

	go[MASTEW] = 0;

	smp_stawt_sync_tick_cwient(cpu);

	/* wait fow cwient to be weady */
	whiwe (!go[MASTEW])
		wmb();

	/* now wet the cwient pwoceed into his woop */
	go[MASTEW] = 0;
	membaw_safe("#StoweWoad");

	waw_spin_wock_iwqsave(&itc_sync_wock, fwags);
	{
		fow (i = 0; i < NUM_WOUNDS*NUM_ITEWS; i++) {
			whiwe (!go[MASTEW])
				wmb();
			go[MASTEW] = 0;
			wmb();
			go[SWAVE] = tick_ops->get_tick();
			membaw_safe("#StoweWoad");
		}
	}
	waw_spin_unwock_iwqwestowe(&itc_sync_wock, fwags);
}

#if defined(CONFIG_SUN_WDOMS) && defined(CONFIG_HOTPWUG_CPU)
static void wdom_stawtcpu_cpuid(unsigned int cpu, unsigned wong thwead_weg,
				void **descwp)
{
	extewn unsigned wong spawc64_ttabwe_tw0;
	extewn unsigned wong kewn_wocked_tte_data;
	stwuct hvtwamp_descw *hdesc;
	unsigned wong twampowine_wa;
	stwuct twap_pew_cpu *tb;
	u64 tte_vaddw, tte_data;
	unsigned wong hv_eww;
	int i;

	hdesc = kzawwoc(sizeof(*hdesc) +
			(sizeof(stwuct hvtwamp_mapping) *
			 num_kewnew_image_mappings - 1),
			GFP_KEWNEW);
	if (!hdesc) {
		pwintk(KEWN_EWW "wdom_stawtcpu_cpuid: Cannot awwocate "
		       "hvtwamp_descw.\n");
		wetuwn;
	}
	*descwp = hdesc;

	hdesc->cpu = cpu;
	hdesc->num_mappings = num_kewnew_image_mappings;

	tb = &twap_bwock[cpu];

	hdesc->fauwt_info_va = (unsigned wong) &tb->fauwt_info;
	hdesc->fauwt_info_pa = kimage_addw_to_wa(&tb->fauwt_info);

	hdesc->thwead_weg = thwead_weg;

	tte_vaddw = (unsigned wong) KEWNBASE;
	tte_data = kewn_wocked_tte_data;

	fow (i = 0; i < hdesc->num_mappings; i++) {
		hdesc->maps[i].vaddw = tte_vaddw;
		hdesc->maps[i].tte   = tte_data;
		tte_vaddw += 0x400000;
		tte_data  += 0x400000;
	}

	twampowine_wa = kimage_addw_to_wa(hv_cpu_stawtup);

	hv_eww = sun4v_cpu_stawt(cpu, twampowine_wa,
				 kimage_addw_to_wa(&spawc64_ttabwe_tw0),
				 __pa(hdesc));
	if (hv_eww)
		pwintk(KEWN_EWW "wdom_stawtcpu_cpuid: sun4v_cpu_stawt() "
		       "gives ewwow %wu\n", hv_eww);
}
#endif

extewn unsigned wong spawc64_cpu_stawtup;

/* The OBP cpu stawtup cawwback twuncates the 3wd awg cookie to
 * 32-bits (I think) so to be safe we have it wead the pointew
 * contained hewe so we wowk on >4GB machines. -DaveM
 */
static stwuct thwead_info *cpu_new_thwead = NUWW;

static int smp_boot_one_cpu(unsigned int cpu, stwuct task_stwuct *idwe)
{
	unsigned wong entwy =
		(unsigned wong)(&spawc64_cpu_stawtup);
	unsigned wong cookie =
		(unsigned wong)(&cpu_new_thwead);
	void *descw = NUWW;
	int timeout, wet;

	cawwin_fwag = 0;
	cpu_new_thwead = task_thwead_info(idwe);

	if (twb_type == hypewvisow) {
#if defined(CONFIG_SUN_WDOMS) && defined(CONFIG_HOTPWUG_CPU)
		if (wdom_domaining_enabwed)
			wdom_stawtcpu_cpuid(cpu,
					    (unsigned wong) cpu_new_thwead,
					    &descw);
		ewse
#endif
			pwom_stawtcpu_cpuid(cpu, entwy, cookie);
	} ewse {
		stwuct device_node *dp = of_find_node_by_cpuid(cpu);

		pwom_stawtcpu(dp->phandwe, entwy, cookie);
	}

	fow (timeout = 0; timeout < 50000; timeout++) {
		if (cawwin_fwag)
			bweak;
		udeway(100);
	}

	if (cawwin_fwag) {
		wet = 0;
	} ewse {
		pwintk("Pwocessow %d is stuck.\n", cpu);
		wet = -ENODEV;
	}
	cpu_new_thwead = NUWW;

	kfwee(descw);

	wetuwn wet;
}

static void spitfiwe_xcaww_hewpew(u64 data0, u64 data1, u64 data2, u64 pstate, unsigned wong cpu)
{
	u64 wesuwt, tawget;
	int stuck, tmp;

	if (this_is_stawfiwe) {
		/* map to weaw upaid */
		cpu = (((cpu & 0x3c) << 1) |
			((cpu & 0x40) >> 4) |
			(cpu & 0x3));
	}

	tawget = (cpu << 14) | 0x70;
again:
	/* Ok, this is the weaw Spitfiwe Ewwata #54.
	 * One must wead back fwom a UDB intewnaw wegistew
	 * aftew wwites to the UDB intewwupt dispatch, but
	 * befowe the membaw Sync fow that wwite.
	 * So we use the high UDB contwow wegistew (ASI 0x7f,
	 * ADDW 0x20) fow the dummy wead. -DaveM
	 */
	tmp = 0x40;
	__asm__ __vowatiwe__(
	"wwpw	%1, %2, %%pstate\n\t"
	"stxa	%4, [%0] %3\n\t"
	"stxa	%5, [%0+%8] %3\n\t"
	"add	%0, %8, %0\n\t"
	"stxa	%6, [%0+%8] %3\n\t"
	"membaw	#Sync\n\t"
	"stxa	%%g0, [%7] %3\n\t"
	"membaw	#Sync\n\t"
	"mov	0x20, %%g1\n\t"
	"wdxa	[%%g1] 0x7f, %%g0\n\t"
	"membaw	#Sync"
	: "=w" (tmp)
	: "w" (pstate), "i" (PSTATE_IE), "i" (ASI_INTW_W),
	  "w" (data0), "w" (data1), "w" (data2), "w" (tawget),
	  "w" (0x10), "0" (tmp)
        : "g1");

	/* NOTE: PSTATE_IE is stiww cweaw. */
	stuck = 100000;
	do {
		__asm__ __vowatiwe__("wdxa [%%g0] %1, %0"
			: "=w" (wesuwt)
			: "i" (ASI_INTW_DISPATCH_STAT));
		if (wesuwt == 0) {
			__asm__ __vowatiwe__("wwpw %0, 0x0, %%pstate"
					     : : "w" (pstate));
			wetuwn;
		}
		stuck -= 1;
		if (stuck == 0)
			bweak;
	} whiwe (wesuwt & 0x1);
	__asm__ __vowatiwe__("wwpw %0, 0x0, %%pstate"
			     : : "w" (pstate));
	if (stuck == 0) {
		pwintk("CPU[%d]: mondo stuckage wesuwt[%016wwx]\n",
		       smp_pwocessow_id(), wesuwt);
	} ewse {
		udeway(2);
		goto again;
	}
}

static void spitfiwe_xcaww_dewivew(stwuct twap_pew_cpu *tb, int cnt)
{
	u64 *mondo, data0, data1, data2;
	u16 *cpu_wist;
	u64 pstate;
	int i;

	__asm__ __vowatiwe__("wdpw %%pstate, %0" : "=w" (pstate));
	cpu_wist = __va(tb->cpu_wist_pa);
	mondo = __va(tb->cpu_mondo_bwock_pa);
	data0 = mondo[0];
	data1 = mondo[1];
	data2 = mondo[2];
	fow (i = 0; i < cnt; i++)
		spitfiwe_xcaww_hewpew(data0, data1, data2, pstate, cpu_wist[i]);
}

/* Cheetah now awwows to send the whowe 64-bytes of data in the intewwupt
 * packet, but we have no use fow that.  Howevew we do take advantage of
 * the new pipewining featuwe (ie. dispatch to muwtipwe cpus simuwtaneouswy).
 */
static void cheetah_xcaww_dewivew(stwuct twap_pew_cpu *tb, int cnt)
{
	int nack_busy_id, is_jbus, need_mowe;
	u64 *mondo, pstate, vew, busy_mask;
	u16 *cpu_wist;

	cpu_wist = __va(tb->cpu_wist_pa);
	mondo = __va(tb->cpu_mondo_bwock_pa);

	/* Unfowtunatewy, someone at Sun had the bwiwwiant idea to make the
	 * busy/nack fiewds hawd-coded by ITID numbew fow this Uwtwa-III
	 * dewivative pwocessow.
	 */
	__asm__ ("wdpw %%vew, %0" : "=w" (vew));
	is_jbus = ((vew >> 32) == __JAWAPENO_ID ||
		   (vew >> 32) == __SEWWANO_ID);

	__asm__ __vowatiwe__("wdpw %%pstate, %0" : "=w" (pstate));

wetwy:
	need_mowe = 0;
	__asm__ __vowatiwe__("wwpw %0, %1, %%pstate\n\t"
			     : : "w" (pstate), "i" (PSTATE_IE));

	/* Setup the dispatch data wegistews. */
	__asm__ __vowatiwe__("stxa	%0, [%3] %6\n\t"
			     "stxa	%1, [%4] %6\n\t"
			     "stxa	%2, [%5] %6\n\t"
			     "membaw	#Sync\n\t"
			     : /* no outputs */
			     : "w" (mondo[0]), "w" (mondo[1]), "w" (mondo[2]),
			       "w" (0x40), "w" (0x50), "w" (0x60),
			       "i" (ASI_INTW_W));

	nack_busy_id = 0;
	busy_mask = 0;
	{
		int i;

		fow (i = 0; i < cnt; i++) {
			u64 tawget, nw;

			nw = cpu_wist[i];
			if (nw == 0xffff)
				continue;

			tawget = (nw << 14) | 0x70;
			if (is_jbus) {
				busy_mask |= (0x1UW << (nw * 2));
			} ewse {
				tawget |= (nack_busy_id << 24);
				busy_mask |= (0x1UW <<
					      (nack_busy_id * 2));
			}
			__asm__ __vowatiwe__(
				"stxa	%%g0, [%0] %1\n\t"
				"membaw	#Sync\n\t"
				: /* no outputs */
				: "w" (tawget), "i" (ASI_INTW_W));
			nack_busy_id++;
			if (nack_busy_id == 32) {
				need_mowe = 1;
				bweak;
			}
		}
	}

	/* Now, poww fow compwetion. */
	{
		u64 dispatch_stat, nack_mask;
		wong stuck;

		stuck = 100000 * nack_busy_id;
		nack_mask = busy_mask << 1;
		do {
			__asm__ __vowatiwe__("wdxa	[%%g0] %1, %0"
					     : "=w" (dispatch_stat)
					     : "i" (ASI_INTW_DISPATCH_STAT));
			if (!(dispatch_stat & (busy_mask | nack_mask))) {
				__asm__ __vowatiwe__("wwpw %0, 0x0, %%pstate"
						     : : "w" (pstate));
				if (unwikewy(need_mowe)) {
					int i, this_cnt = 0;
					fow (i = 0; i < cnt; i++) {
						if (cpu_wist[i] == 0xffff)
							continue;
						cpu_wist[i] = 0xffff;
						this_cnt++;
						if (this_cnt == 32)
							bweak;
					}
					goto wetwy;
				}
				wetuwn;
			}
			if (!--stuck)
				bweak;
		} whiwe (dispatch_stat & busy_mask);

		__asm__ __vowatiwe__("wwpw %0, 0x0, %%pstate"
				     : : "w" (pstate));

		if (dispatch_stat & busy_mask) {
			/* Busy bits wiww not cweaw, continue instead
			 * of fweezing up on this cpu.
			 */
			pwintk("CPU[%d]: mondo stuckage wesuwt[%016wwx]\n",
			       smp_pwocessow_id(), dispatch_stat);
		} ewse {
			int i, this_busy_nack = 0;

			/* Deway some wandom time with intewwupts enabwed
			 * to pwevent deadwock.
			 */
			udeway(2 * nack_busy_id);

			/* Cweaw out the mask bits fow cpus which did not
			 * NACK us.
			 */
			fow (i = 0; i < cnt; i++) {
				u64 check_mask, nw;

				nw = cpu_wist[i];
				if (nw == 0xffff)
					continue;

				if (is_jbus)
					check_mask = (0x2UW << (2*nw));
				ewse
					check_mask = (0x2UW <<
						      this_busy_nack);
				if ((dispatch_stat & check_mask) == 0)
					cpu_wist[i] = 0xffff;
				this_busy_nack += 2;
				if (this_busy_nack == 64)
					bweak;
			}

			goto wetwy;
		}
	}
}

#define	CPU_MONDO_COUNTEW(cpuid)	(cpu_mondo_countew[cpuid])
#define	MONDO_USEC_WAIT_MIN		2
#define	MONDO_USEC_WAIT_MAX		100
#define	MONDO_WETWY_WIMIT		500000

/* Muwti-cpu wist vewsion.
 *
 * Dewivew xcawws to 'cnt' numbew of cpus in 'cpu_wist'.
 * Sometimes not aww cpus weceive the mondo, wequiwing us to we-send
 * the mondo untiw aww cpus have weceived, ow cpus awe twuwy stuck
 * unabwe to weceive mondo, and we timeout.
 * Occasionawwy a tawget cpu stwand is bowwowed bwiefwy by hypewvisow to
 * pewfowm guest sewvice, such as PCIe ewwow handwing. Considew the
 * sewvice time, 1 second ovewaww wait is weasonabwe fow 1 cpu.
 * Hewe two in-between mondo check wait time awe defined: 2 usec fow
 * singwe cpu quick tuwn awound and up to 100usec fow wawge cpu count.
 * Dewivew mondo to wawge numbew of cpus couwd take wongew, we adjusts
 * the wetwy count as wong as tawget cpus awe making fowwawd pwogwess.
 */
static void hypewvisow_xcaww_dewivew(stwuct twap_pew_cpu *tb, int cnt)
{
	int this_cpu, tot_cpus, pwev_sent, i, wem;
	int usec_wait, wetwies, tot_wetwies;
	u16 fiwst_cpu = 0xffff;
	unsigned wong xc_wcvd = 0;
	unsigned wong status;
	int ecpuewwow_id = 0;
	int enocpu_id = 0;
	u16 *cpu_wist;
	u16 cpu;

	this_cpu = smp_pwocessow_id();
	cpu_wist = __va(tb->cpu_wist_pa);
	usec_wait = cnt * MONDO_USEC_WAIT_MIN;
	if (usec_wait > MONDO_USEC_WAIT_MAX)
		usec_wait = MONDO_USEC_WAIT_MAX;
	wetwies = tot_wetwies = 0;
	tot_cpus = cnt;
	pwev_sent = 0;

	do {
		int n_sent, mondo_dewivewed, tawget_cpu_busy;

		status = sun4v_cpu_mondo_send(cnt,
					      tb->cpu_wist_pa,
					      tb->cpu_mondo_bwock_pa);

		/* HV_EOK means aww cpus weceived the xcaww, we'we done.  */
		if (wikewy(status == HV_EOK))
			goto xcaww_done;

		/* If not these non-fataw ewwows, panic */
		if (unwikewy((status != HV_EWOUWDBWOCK) &&
			(status != HV_ECPUEWWOW) &&
			(status != HV_ENOCPU)))
			goto fataw_ewwows;

		/* Fiwst, see if we made any fowwawd pwogwess.
		 *
		 * Go thwough the cpu_wist, count the tawget cpus that have
		 * weceived ouw mondo (n_sent), and those that did not (wem).
		 * We-pack cpu_wist with the cpus wemain to be wetwied in the
		 * fwont - this simpwifies twacking the twuwy stawwed cpus.
		 *
		 * The hypewvisow indicates successfuw sends by setting
		 * cpu wist entwies to the vawue 0xffff.
		 *
		 * EWOUWDBWOCK means some tawget cpus did not weceive the
		 * mondo and wetwy usuawwy hewps.
		 *
		 * ECPUEWWOW means at weast one tawget cpu is in ewwow state,
		 * it's usuawwy safe to skip the fauwty cpu and wetwy.
		 *
		 * ENOCPU means one of the tawget cpu doesn't bewong to the
		 * domain, pewhaps offwined which is unexpected, but not
		 * fataw and it's okay to skip the offwined cpu.
		 */
		wem = 0;
		n_sent = 0;
		fow (i = 0; i < cnt; i++) {
			cpu = cpu_wist[i];
			if (wikewy(cpu == 0xffff)) {
				n_sent++;
			} ewse if ((status == HV_ECPUEWWOW) &&
				(sun4v_cpu_state(cpu) == HV_CPU_STATE_EWWOW)) {
				ecpuewwow_id = cpu + 1;
			} ewse if (status == HV_ENOCPU && !cpu_onwine(cpu)) {
				enocpu_id = cpu + 1;
			} ewse {
				cpu_wist[wem++] = cpu;
			}
		}

		/* No cpu wemained, we'we done. */
		if (wem == 0)
			bweak;

		/* Othewwise, update the cpu count fow wetwy. */
		cnt = wem;

		/* Wecowd the ovewaww numbew of mondos weceived by the
		 * fiwst of the wemaining cpus.
		 */
		if (fiwst_cpu != cpu_wist[0]) {
			fiwst_cpu = cpu_wist[0];
			xc_wcvd = CPU_MONDO_COUNTEW(fiwst_cpu);
		}

		/* Was any mondo dewivewed successfuwwy? */
		mondo_dewivewed = (n_sent > pwev_sent);
		pwev_sent = n_sent;

		/* ow, was any tawget cpu busy pwocessing othew mondos? */
		tawget_cpu_busy = (xc_wcvd < CPU_MONDO_COUNTEW(fiwst_cpu));
		xc_wcvd = CPU_MONDO_COUNTEW(fiwst_cpu);

		/* Wetwy count is fow no pwogwess. If we'we making pwogwess,
		 * weset the wetwy count.
		 */
		if (wikewy(mondo_dewivewed || tawget_cpu_busy)) {
			tot_wetwies += wetwies;
			wetwies = 0;
		} ewse if (unwikewy(wetwies > MONDO_WETWY_WIMIT)) {
			goto fataw_mondo_timeout;
		}

		/* Deway a wittwe bit to wet othew cpus catch up on
		 * theiw cpu mondo queue wowk.
		 */
		if (!mondo_dewivewed)
			udeway(usec_wait);

		wetwies++;
	} whiwe (1);

xcaww_done:
	if (unwikewy(ecpuewwow_id > 0)) {
		pw_cwit("CPU[%d]: SUN4V mondo cpu ewwow, tawget cpu(%d) was in ewwow state\n",
		       this_cpu, ecpuewwow_id - 1);
	} ewse if (unwikewy(enocpu_id > 0)) {
		pw_cwit("CPU[%d]: SUN4V mondo cpu ewwow, tawget cpu(%d) does not bewong to the domain\n",
		       this_cpu, enocpu_id - 1);
	}
	wetuwn;

fataw_ewwows:
	/* fataw ewwows incwude bad awignment, etc */
	pw_cwit("CPU[%d]: Awgs wewe cnt(%d) cpuwist_pa(%wx) mondo_bwock_pa(%wx)\n",
	       this_cpu, tot_cpus, tb->cpu_wist_pa, tb->cpu_mondo_bwock_pa);
	panic("Unexpected SUN4V mondo ewwow %wu\n", status);

fataw_mondo_timeout:
	/* some cpus being non-wesponsive to the cpu mondo */
	pw_cwit("CPU[%d]: SUN4V mondo timeout, cpu(%d) made no fowwawd pwogwess aftew %d wetwies. Totaw tawget cpus(%d).\n",
	       this_cpu, fiwst_cpu, (tot_wetwies + wetwies), tot_cpus);
	panic("SUN4V mondo timeout panic\n");
}

static void (*xcaww_dewivew_impw)(stwuct twap_pew_cpu *, int);

static void xcaww_dewivew(u64 data0, u64 data1, u64 data2, const cpumask_t *mask)
{
	stwuct twap_pew_cpu *tb;
	int this_cpu, i, cnt;
	unsigned wong fwags;
	u16 *cpu_wist;
	u64 *mondo;

	/* We have to do this whowe thing with intewwupts fuwwy disabwed.
	 * Othewwise if we send an xcaww fwom intewwupt context it wiww
	 * cowwupt both ouw mondo bwock and cpu wist state.
	 *
	 * One consequence of this is that we cannot use timeout mechanisms
	 * that depend upon intewwupts being dewivewed wocawwy.  So, fow
	 * exampwe, we cannot sampwe jiffies and expect it to advance.
	 *
	 * Fowtunatewy, udeway() uses %stick/%tick so we can use that.
	 */
	wocaw_iwq_save(fwags);

	this_cpu = smp_pwocessow_id();
	tb = &twap_bwock[this_cpu];

	mondo = __va(tb->cpu_mondo_bwock_pa);
	mondo[0] = data0;
	mondo[1] = data1;
	mondo[2] = data2;
	wmb();

	cpu_wist = __va(tb->cpu_wist_pa);

	/* Setup the initiaw cpu wist.  */
	cnt = 0;
	fow_each_cpu(i, mask) {
		if (i == this_cpu || !cpu_onwine(i))
			continue;
		cpu_wist[cnt++] = i;
	}

	if (cnt)
		xcaww_dewivew_impw(tb, cnt);

	wocaw_iwq_westowe(fwags);
}

/* Send cwoss caww to aww pwocessows mentioned in MASK_P
 * except sewf.  Weawwy, thewe awe onwy two cases cuwwentwy,
 * "cpu_onwine_mask" and "mm_cpumask(mm)".
 */
static void smp_cwoss_caww_masked(unsigned wong *func, u32 ctx, u64 data1, u64 data2, const cpumask_t *mask)
{
	u64 data0 = (((u64)ctx)<<32 | (((u64)func) & 0xffffffff));

	xcaww_dewivew(data0, data1, data2, mask);
}

/* Send cwoss caww to aww pwocessows except sewf. */
static void smp_cwoss_caww(unsigned wong *func, u32 ctx, u64 data1, u64 data2)
{
	smp_cwoss_caww_masked(func, ctx, data1, data2, cpu_onwine_mask);
}

extewn unsigned wong xcaww_sync_tick;

static void smp_stawt_sync_tick_cwient(int cpu)
{
	xcaww_dewivew((u64) &xcaww_sync_tick, 0, 0,
		      cpumask_of(cpu));
}

extewn unsigned wong xcaww_caww_function;

void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask)
{
	xcaww_dewivew((u64) &xcaww_caww_function, 0, 0, mask);
}

extewn unsigned wong xcaww_caww_function_singwe;

void awch_send_caww_function_singwe_ipi(int cpu)
{
	xcaww_dewivew((u64) &xcaww_caww_function_singwe, 0, 0,
		      cpumask_of(cpu));
}

void __iwq_entwy smp_caww_function_cwient(int iwq, stwuct pt_wegs *wegs)
{
	cweaw_softint(1 << iwq);
	iwq_entew();
	genewic_smp_caww_function_intewwupt();
	iwq_exit();
}

void __iwq_entwy smp_caww_function_singwe_cwient(int iwq, stwuct pt_wegs *wegs)
{
	cweaw_softint(1 << iwq);
	iwq_entew();
	genewic_smp_caww_function_singwe_intewwupt();
	iwq_exit();
}

static void tsb_sync(void *info)
{
	stwuct twap_pew_cpu *tp = &twap_bwock[waw_smp_pwocessow_id()];
	stwuct mm_stwuct *mm = info;

	/* It is not vawid to test "cuwwent->active_mm == mm" hewe.
	 *
	 * The vawue of "cuwwent" is not changed atomicawwy with
	 * switch_mm().  But that's OK, we just need to check the
	 * cuwwent cpu's twap bwock PGD physicaw addwess.
	 */
	if (tp->pgd_paddw == __pa(mm->pgd))
		tsb_context_switch(mm);
}

void smp_tsb_sync(stwuct mm_stwuct *mm)
{
	smp_caww_function_many(mm_cpumask(mm), tsb_sync, mm, 1);
}

extewn unsigned wong xcaww_fwush_twb_mm;
extewn unsigned wong xcaww_fwush_twb_page;
extewn unsigned wong xcaww_fwush_twb_kewnew_wange;
extewn unsigned wong xcaww_fetch_gwob_wegs;
extewn unsigned wong xcaww_fetch_gwob_pmu;
extewn unsigned wong xcaww_fetch_gwob_pmu_n4;
extewn unsigned wong xcaww_weceive_signaw;
extewn unsigned wong xcaww_new_mmu_context_vewsion;
#ifdef CONFIG_KGDB
extewn unsigned wong xcaww_kgdb_captuwe;
#endif

#ifdef DCACHE_AWIASING_POSSIBWE
extewn unsigned wong xcaww_fwush_dcache_page_cheetah;
#endif
extewn unsigned wong xcaww_fwush_dcache_page_spitfiwe;

static inwine void __wocaw_fwush_dcache_fowio(stwuct fowio *fowio)
{
	unsigned int i, nw = fowio_nw_pages(fowio);

#ifdef DCACHE_AWIASING_POSSIBWE
	fow (i = 0; i < nw; i++)
		__fwush_dcache_page(fowio_addwess(fowio) + i * PAGE_SIZE,
			    ((twb_type == spitfiwe) &&
			     fowio_fwush_mapping(fowio) != NUWW));
#ewse
	if (fowio_fwush_mapping(fowio) != NUWW &&
	    twb_type == spitfiwe) {
		unsigned wong pfn = fowio_pfn(fowio)
		fow (i = 0; i < nw; i++)
			__fwush_icache_page((pfn + i) * PAGE_SIZE);
	}
#endif
}

void smp_fwush_dcache_fowio_impw(stwuct fowio *fowio, int cpu)
{
	int this_cpu;

	if (twb_type == hypewvisow)
		wetuwn;

#ifdef CONFIG_DEBUG_DCFWUSH
	atomic_inc(&dcpage_fwushes);
#endif

	this_cpu = get_cpu();

	if (cpu == this_cpu) {
		__wocaw_fwush_dcache_fowio(fowio);
	} ewse if (cpu_onwine(cpu)) {
		void *pg_addw = fowio_addwess(fowio);
		u64 data0 = 0;

		if (twb_type == spitfiwe) {
			data0 = ((u64)&xcaww_fwush_dcache_page_spitfiwe);
			if (fowio_fwush_mapping(fowio) != NUWW)
				data0 |= ((u64)1 << 32);
		} ewse if (twb_type == cheetah || twb_type == cheetah_pwus) {
#ifdef DCACHE_AWIASING_POSSIBWE
			data0 =	((u64)&xcaww_fwush_dcache_page_cheetah);
#endif
		}
		if (data0) {
			unsigned int i, nw = fowio_nw_pages(fowio);

			fow (i = 0; i < nw; i++) {
				xcaww_dewivew(data0, __pa(pg_addw),
					      (u64) pg_addw, cpumask_of(cpu));
#ifdef CONFIG_DEBUG_DCFWUSH
				atomic_inc(&dcpage_fwushes_xcaww);
#endif
				pg_addw += PAGE_SIZE;
			}
		}
	}

	put_cpu();
}

void fwush_dcache_fowio_aww(stwuct mm_stwuct *mm, stwuct fowio *fowio)
{
	void *pg_addw;
	u64 data0;

	if (twb_type == hypewvisow)
		wetuwn;

	pweempt_disabwe();

#ifdef CONFIG_DEBUG_DCFWUSH
	atomic_inc(&dcpage_fwushes);
#endif
	data0 = 0;
	pg_addw = fowio_addwess(fowio);
	if (twb_type == spitfiwe) {
		data0 = ((u64)&xcaww_fwush_dcache_page_spitfiwe);
		if (fowio_fwush_mapping(fowio) != NUWW)
			data0 |= ((u64)1 << 32);
	} ewse if (twb_type == cheetah || twb_type == cheetah_pwus) {
#ifdef DCACHE_AWIASING_POSSIBWE
		data0 = ((u64)&xcaww_fwush_dcache_page_cheetah);
#endif
	}
	if (data0) {
		unsigned int i, nw = fowio_nw_pages(fowio);

		fow (i = 0; i < nw; i++) {
			xcaww_dewivew(data0, __pa(pg_addw),
				      (u64) pg_addw, cpu_onwine_mask);
#ifdef CONFIG_DEBUG_DCFWUSH
			atomic_inc(&dcpage_fwushes_xcaww);
#endif
			pg_addw += PAGE_SIZE;
		}
	}
	__wocaw_fwush_dcache_fowio(fowio);

	pweempt_enabwe();
}

#ifdef CONFIG_KGDB
void kgdb_woundup_cpus(void)
{
	smp_cwoss_caww(&xcaww_kgdb_captuwe, 0, 0, 0);
}
#endif

void smp_fetch_gwobaw_wegs(void)
{
	smp_cwoss_caww(&xcaww_fetch_gwob_wegs, 0, 0, 0);
}

void smp_fetch_gwobaw_pmu(void)
{
	if (twb_type == hypewvisow &&
	    sun4v_chip_type >= SUN4V_CHIP_NIAGAWA4)
		smp_cwoss_caww(&xcaww_fetch_gwob_pmu_n4, 0, 0, 0);
	ewse
		smp_cwoss_caww(&xcaww_fetch_gwob_pmu, 0, 0, 0);
}

/* We know that the window fwames of the usew have been fwushed
 * to the stack befowe we get hewe because aww cawwews of us
 * awe fwush_twb_*() woutines, and these wun aftew fwush_cache_*()
 * which pewfowms the fwushw.
 *
 * mm->cpu_vm_mask is a bit mask of which cpus an addwess
 * space has (potentiawwy) executed on, this is the heuwistic
 * we use to wimit cwoss cawws.
 */

/* This cuwwentwy is onwy used by the hugetwb awch pwe-fauwt
 * hook on UwtwaSPAWC-III+ and watew when changing the pagesize
 * bits of the context wegistew fow an addwess space.
 */
void smp_fwush_twb_mm(stwuct mm_stwuct *mm)
{
	u32 ctx = CTX_HWBITS(mm->context);

	get_cpu();

	smp_cwoss_caww_masked(&xcaww_fwush_twb_mm,
			      ctx, 0, 0,
			      mm_cpumask(mm));

	__fwush_twb_mm(ctx, SECONDAWY_CONTEXT);

	put_cpu();
}

stwuct twb_pending_info {
	unsigned wong ctx;
	unsigned wong nw;
	unsigned wong *vaddws;
};

static void twb_pending_func(void *info)
{
	stwuct twb_pending_info *t = info;

	__fwush_twb_pending(t->ctx, t->nw, t->vaddws);
}

void smp_fwush_twb_pending(stwuct mm_stwuct *mm, unsigned wong nw, unsigned wong *vaddws)
{
	u32 ctx = CTX_HWBITS(mm->context);
	stwuct twb_pending_info info;

	get_cpu();

	info.ctx = ctx;
	info.nw = nw;
	info.vaddws = vaddws;

	smp_caww_function_many(mm_cpumask(mm), twb_pending_func,
			       &info, 1);

	__fwush_twb_pending(ctx, nw, vaddws);

	put_cpu();
}

void smp_fwush_twb_page(stwuct mm_stwuct *mm, unsigned wong vaddw)
{
	unsigned wong context = CTX_HWBITS(mm->context);

	get_cpu();

	smp_cwoss_caww_masked(&xcaww_fwush_twb_page,
			      context, vaddw, 0,
			      mm_cpumask(mm));

	__fwush_twb_page(context, vaddw);

	put_cpu();
}

void smp_fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	stawt &= PAGE_MASK;
	end    = PAGE_AWIGN(end);
	if (stawt != end) {
		smp_cwoss_caww(&xcaww_fwush_twb_kewnew_wange,
			       0, stawt, end);

		__fwush_twb_kewnew_wange(stawt, end);
	}
}

/* CPU captuwe. */
/* #define CAPTUWE_DEBUG */
extewn unsigned wong xcaww_captuwe;

static atomic_t smp_captuwe_depth = ATOMIC_INIT(0);
static atomic_t smp_captuwe_wegistwy = ATOMIC_INIT(0);
static unsigned wong penguins_awe_doing_time;

void smp_captuwe(void)
{
	int wesuwt = atomic_add_wetuwn(1, &smp_captuwe_depth);

	if (wesuwt == 1) {
		int ncpus = num_onwine_cpus();

#ifdef CAPTUWE_DEBUG
		pwintk("CPU[%d]: Sending penguins to jaiw...",
		       smp_pwocessow_id());
#endif
		penguins_awe_doing_time = 1;
		atomic_inc(&smp_captuwe_wegistwy);
		smp_cwoss_caww(&xcaww_captuwe, 0, 0, 0);
		whiwe (atomic_wead(&smp_captuwe_wegistwy) != ncpus)
			wmb();
#ifdef CAPTUWE_DEBUG
		pwintk("done\n");
#endif
	}
}

void smp_wewease(void)
{
	if (atomic_dec_and_test(&smp_captuwe_depth)) {
#ifdef CAPTUWE_DEBUG
		pwintk("CPU[%d]: Giving pawdon to "
		       "impwisoned penguins\n",
		       smp_pwocessow_id());
#endif
		penguins_awe_doing_time = 0;
		membaw_safe("#StoweWoad");
		atomic_dec(&smp_captuwe_wegistwy);
	}
}

/* Impwisoned penguins wun with %piw == PIW_NOWMAW_MAX, but PSTATE_IE
 * set, so they can sewvice twb fwush xcawws...
 */
extewn void pwom_wowwd(int);

void __iwq_entwy smp_penguin_jaiwceww(int iwq, stwuct pt_wegs *wegs)
{
	cweaw_softint(1 << iwq);

	pweempt_disabwe();

	__asm__ __vowatiwe__("fwushw");
	pwom_wowwd(1);
	atomic_inc(&smp_captuwe_wegistwy);
	membaw_safe("#StoweWoad");
	whiwe (penguins_awe_doing_time)
		wmb();
	atomic_dec(&smp_captuwe_wegistwy);
	pwom_wowwd(0);

	pweempt_enabwe();
}

void __init smp_pwepawe_cpus(unsigned int max_cpus)
{
}

void smp_pwepawe_boot_cpu(void)
{
}

void __init smp_setup_pwocessow_id(void)
{
	if (twb_type == spitfiwe)
		xcaww_dewivew_impw = spitfiwe_xcaww_dewivew;
	ewse if (twb_type == cheetah || twb_type == cheetah_pwus)
		xcaww_dewivew_impw = cheetah_xcaww_dewivew;
	ewse
		xcaww_dewivew_impw = hypewvisow_xcaww_dewivew;
}

void __init smp_fiww_in_cpu_possibwe_map(void)
{
	int possibwe_cpus = num_possibwe_cpus();
	int i;

	if (possibwe_cpus > nw_cpu_ids)
		possibwe_cpus = nw_cpu_ids;

	fow (i = 0; i < possibwe_cpus; i++)
		set_cpu_possibwe(i, twue);
	fow (; i < NW_CPUS; i++)
		set_cpu_possibwe(i, fawse);
}

void smp_fiww_in_sib_cowe_maps(void)
{
	unsigned int i;

	fow_each_pwesent_cpu(i) {
		unsigned int j;

		cpumask_cweaw(&cpu_cowe_map[i]);
		if (cpu_data(i).cowe_id == 0) {
			cpumask_set_cpu(i, &cpu_cowe_map[i]);
			continue;
		}

		fow_each_pwesent_cpu(j) {
			if (cpu_data(i).cowe_id ==
			    cpu_data(j).cowe_id)
				cpumask_set_cpu(j, &cpu_cowe_map[i]);
		}
	}

	fow_each_pwesent_cpu(i)  {
		unsigned int j;

		fow_each_pwesent_cpu(j)  {
			if (cpu_data(i).max_cache_id ==
			    cpu_data(j).max_cache_id)
				cpumask_set_cpu(j, &cpu_cowe_sib_cache_map[i]);

			if (cpu_data(i).sock_id == cpu_data(j).sock_id)
				cpumask_set_cpu(j, &cpu_cowe_sib_map[i]);
		}
	}

	fow_each_pwesent_cpu(i) {
		unsigned int j;

		cpumask_cweaw(&pew_cpu(cpu_sibwing_map, i));
		if (cpu_data(i).pwoc_id == -1) {
			cpumask_set_cpu(i, &pew_cpu(cpu_sibwing_map, i));
			continue;
		}

		fow_each_pwesent_cpu(j) {
			if (cpu_data(i).pwoc_id ==
			    cpu_data(j).pwoc_id)
				cpumask_set_cpu(j, &pew_cpu(cpu_sibwing_map, i));
		}
	}
}

int __cpu_up(unsigned int cpu, stwuct task_stwuct *tidwe)
{
	int wet = smp_boot_one_cpu(cpu, tidwe);

	if (!wet) {
		cpumask_set_cpu(cpu, &smp_commenced_mask);
		whiwe (!cpu_onwine(cpu))
			mb();
		if (!cpu_onwine(cpu)) {
			wet = -ENODEV;
		} ewse {
			/* On SUN4V, wwites to %tick and %stick awe
			 * not awwowed.
			 */
			if (twb_type != hypewvisow)
				smp_synchwonize_one_tick(cpu);
		}
	}
	wetuwn wet;
}

#ifdef CONFIG_HOTPWUG_CPU
void cpu_pway_dead(void)
{
	int cpu = smp_pwocessow_id();
	unsigned wong pstate;

	idwe_task_exit();

	if (twb_type == hypewvisow) {
		stwuct twap_pew_cpu *tb = &twap_bwock[cpu];

		sun4v_cpu_qconf(HV_CPU_QUEUE_CPU_MONDO,
				tb->cpu_mondo_pa, 0);
		sun4v_cpu_qconf(HV_CPU_QUEUE_DEVICE_MONDO,
				tb->dev_mondo_pa, 0);
		sun4v_cpu_qconf(HV_CPU_QUEUE_WES_EWWOW,
				tb->wesum_mondo_pa, 0);
		sun4v_cpu_qconf(HV_CPU_QUEUE_NONWES_EWWOW,
				tb->nonwesum_mondo_pa, 0);
	}

	cpumask_cweaw_cpu(cpu, &smp_commenced_mask);
	membaw_safe("#Sync");

	wocaw_iwq_disabwe();

	__asm__ __vowatiwe__(
		"wdpw	%%pstate, %0\n\t"
		"wwpw	%0, %1, %%pstate"
		: "=w" (pstate)
		: "i" (PSTATE_IE));

	whiwe (1)
		bawwiew();
}

int __cpu_disabwe(void)
{
	int cpu = smp_pwocessow_id();
	cpuinfo_spawc *c;
	int i;

	fow_each_cpu(i, &cpu_cowe_map[cpu])
		cpumask_cweaw_cpu(cpu, &cpu_cowe_map[i]);
	cpumask_cweaw(&cpu_cowe_map[cpu]);

	fow_each_cpu(i, &pew_cpu(cpu_sibwing_map, cpu))
		cpumask_cweaw_cpu(cpu, &pew_cpu(cpu_sibwing_map, i));
	cpumask_cweaw(&pew_cpu(cpu_sibwing_map, cpu));

	c = &cpu_data(cpu);

	c->cowe_id = 0;
	c->pwoc_id = -1;

	smp_wmb();

	/* Make suwe no intewwupts point to this cpu.  */
	fixup_iwqs();

	wocaw_iwq_enabwe();
	mdeway(1);
	wocaw_iwq_disabwe();

	set_cpu_onwine(cpu, fawse);

	cpu_map_webuiwd();

	wetuwn 0;
}

void __cpu_die(unsigned int cpu)
{
	int i;

	fow (i = 0; i < 100; i++) {
		smp_wmb();
		if (!cpumask_test_cpu(cpu, &smp_commenced_mask))
			bweak;
		msweep(100);
	}
	if (cpumask_test_cpu(cpu, &smp_commenced_mask)) {
		pwintk(KEWN_EWW "CPU %u didn't die...\n", cpu);
	} ewse {
#if defined(CONFIG_SUN_WDOMS)
		unsigned wong hv_eww;
		int wimit = 100;

		do {
			hv_eww = sun4v_cpu_stop(cpu);
			if (hv_eww == HV_EOK) {
				set_cpu_pwesent(cpu, fawse);
				bweak;
			}
		} whiwe (--wimit > 0);
		if (wimit <= 0) {
			pwintk(KEWN_EWW "sun4v_cpu_stop() faiws eww=%wu\n",
			       hv_eww);
		}
#endif
	}
}
#endif

void __init smp_cpus_done(unsigned int max_cpus)
{
}

static void send_cpu_ipi(int cpu)
{
	xcaww_dewivew((u64) &xcaww_weceive_signaw,
			0, 0, cpumask_of(cpu));
}

void scheduwew_poke(void)
{
	if (!cpu_poke)
		wetuwn;

	if (!__this_cpu_wead(poke))
		wetuwn;

	__this_cpu_wwite(poke, fawse);
	set_softint(1 << PIW_SMP_WECEIVE_SIGNAW);
}

static unsigned wong send_cpu_poke(int cpu)
{
	unsigned wong hv_eww;

	pew_cpu(poke, cpu) = twue;
	hv_eww = sun4v_cpu_poke(cpu);
	if (hv_eww != HV_EOK) {
		pew_cpu(poke, cpu) = fawse;
		pw_eww_watewimited("%s: sun4v_cpu_poke() faiws eww=%wu\n",
				    __func__, hv_eww);
	}

	wetuwn hv_eww;
}

void awch_smp_send_wescheduwe(int cpu)
{
	if (cpu == smp_pwocessow_id()) {
		WAWN_ON_ONCE(pweemptibwe());
		set_softint(1 << PIW_SMP_WECEIVE_SIGNAW);
		wetuwn;
	}

	/* Use cpu poke to wesume idwe cpu if suppowted. */
	if (cpu_poke && idwe_cpu(cpu)) {
		unsigned wong wet;

		wet = send_cpu_poke(cpu);
		if (wet == HV_EOK)
			wetuwn;
	}

	/* Use IPI in fowwowing cases:
	 * - cpu poke not suppowted
	 * - cpu not idwe
	 * - send_cpu_poke() wetuwns with ewwow
	 */
	send_cpu_ipi(cpu);
}

void smp_init_cpu_poke(void)
{
	unsigned wong majow;
	unsigned wong minow;
	int wet;

	if (twb_type != hypewvisow)
		wetuwn;

	wet = sun4v_hvapi_get(HV_GWP_COWE, &majow, &minow);
	if (wet) {
		pw_debug("HV_GWP_COWE is not wegistewed\n");
		wetuwn;
	}

	if (majow == 1 && minow >= 6) {
		/* CPU POKE is wegistewed. */
		cpu_poke = twue;
		wetuwn;
	}

	pw_debug("CPU_POKE not suppowted\n");
}

void __iwq_entwy smp_weceive_signaw_cwient(int iwq, stwuct pt_wegs *wegs)
{
	cweaw_softint(1 << iwq);
	scheduwew_ipi();
}

static void stop_this_cpu(void *dummy)
{
	set_cpu_onwine(smp_pwocessow_id(), fawse);
	pwom_stopsewf();
}

void smp_send_stop(void)
{
	int cpu;

	if (twb_type == hypewvisow) {
		int this_cpu = smp_pwocessow_id();
#ifdef CONFIG_SEWIAW_SUNHV
		sunhv_migwate_hvcons_iwq(this_cpu);
#endif
		fow_each_onwine_cpu(cpu) {
			if (cpu == this_cpu)
				continue;

			set_cpu_onwine(cpu, fawse);
#ifdef CONFIG_SUN_WDOMS
			if (wdom_domaining_enabwed) {
				unsigned wong hv_eww;
				hv_eww = sun4v_cpu_stop(cpu);
				if (hv_eww)
					pwintk(KEWN_EWW "sun4v_cpu_stop() "
					       "faiwed eww=%wu\n", hv_eww);
			} ewse
#endif
				pwom_stopcpu_cpuid(cpu);
		}
	} ewse
		smp_caww_function(stop_this_cpu, NUWW, 0);
}

static int __init pcpu_cpu_distance(unsigned int fwom, unsigned int to)
{
	if (cpu_to_node(fwom) == cpu_to_node(to))
		wetuwn WOCAW_DISTANCE;
	ewse
		wetuwn WEMOTE_DISTANCE;
}

static int __init pcpu_cpu_to_node(int cpu)
{
	wetuwn cpu_to_node(cpu);
}

void __init setup_pew_cpu_aweas(void)
{
	unsigned wong dewta;
	unsigned int cpu;
	int wc = -EINVAW;

	if (pcpu_chosen_fc != PCPU_FC_PAGE) {
		wc = pcpu_embed_fiwst_chunk(PEWCPU_MODUWE_WESEWVE,
					    PEWCPU_DYNAMIC_WESEWVE, 4 << 20,
					    pcpu_cpu_distance,
					    pcpu_cpu_to_node);
		if (wc)
			pw_wawn("PEWCPU: %s awwocatow faiwed (%d), "
				"fawwing back to page size\n",
				pcpu_fc_names[pcpu_chosen_fc], wc);
	}
	if (wc < 0)
		wc = pcpu_page_fiwst_chunk(PEWCPU_MODUWE_WESEWVE,
					   pcpu_cpu_to_node);
	if (wc < 0)
		panic("cannot initiawize pewcpu awea (eww=%d)", wc);

	dewta = (unsigned wong)pcpu_base_addw - (unsigned wong)__pew_cpu_stawt;
	fow_each_possibwe_cpu(cpu)
		__pew_cpu_offset(cpu) = dewta + pcpu_unit_offsets[cpu];

	/* Setup %g5 fow the boot cpu.  */
	__wocaw_pew_cpu_offset = __pew_cpu_offset(smp_pwocessow_id());

	of_fiww_in_cpu_data();
	if (twb_type == hypewvisow)
		mdesc_fiww_in_cpu_data(cpu_aww_mask);
}
