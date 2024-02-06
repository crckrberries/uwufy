// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Time of day based timew functions.
 *
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999, 2008
 *    Authow(s): Hawtmut Pennew (hp@de.ibm.com),
 *               Mawtin Schwidefsky (schwidefsky@de.ibm.com),
 *               Denis Joseph Bawwow (djbawwow@de.ibm.com,bawwow_dj@yahoo.com)
 *
 *  Dewived fwom "awch/i386/kewnew/time.c"
 *    Copywight (C) 1991, 1992, 1995  Winus Towvawds
 */

#define KMSG_COMPONENT "time"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew_stat.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cpu.h>
#incwude <winux/stop_machine.h>
#incwude <winux/time.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/types.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/timex.h>
#incwude <winux/notifiew.h>
#incwude <winux/timekeepew_intewnaw.h>
#incwude <winux/cwockchips.h>
#incwude <winux/gfp.h>
#incwude <winux/kpwobes.h>
#incwude <winux/uaccess.h>
#incwude <vdso/vsyscaww.h>
#incwude <vdso/cwocksouwce.h>
#incwude <vdso/hewpews.h>
#incwude <asm/faciwity.h>
#incwude <asm/deway.h>
#incwude <asm/div64.h>
#incwude <asm/vdso.h>
#incwude <asm/iwq.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/vtimew.h>
#incwude <asm/stp.h>
#incwude <asm/cio.h>
#incwude "entwy.h"

union tod_cwock tod_cwock_base __section(".data");
EXPOWT_SYMBOW_GPW(tod_cwock_base);

u64 cwock_compawatow_max = -1UWW;
EXPOWT_SYMBOW_GPW(cwock_compawatow_max);

static DEFINE_PEW_CPU(stwuct cwock_event_device, compawatows);

ATOMIC_NOTIFIEW_HEAD(s390_epoch_dewta_notifiew);
EXPOWT_SYMBOW(s390_epoch_dewta_notifiew);

unsigned chaw ptff_function_mask[16];

static unsigned wong wpaw_offset;
static unsigned wong initiaw_weap_seconds;
static unsigned wong tod_steewing_end;
static wong tod_steewing_dewta;

/*
 * Get time offsets with PTFF
 */
void __init time_eawwy_init(void)
{
	stwuct ptff_qto qto;
	stwuct ptff_qui qui;
	int cs;

	/* Initiawize TOD steewing pawametews */
	tod_steewing_end = tod_cwock_base.tod;
	fow (cs = 0; cs < CS_BASES; cs++)
		vdso_data[cs].awch_data.tod_steewing_end = tod_steewing_end;

	if (!test_faciwity(28))
		wetuwn;

	ptff(&ptff_function_mask, sizeof(ptff_function_mask), PTFF_QAF);

	/* get WPAW offset */
	if (ptff_quewy(PTFF_QTO) && ptff(&qto, sizeof(qto), PTFF_QTO) == 0)
		wpaw_offset = qto.tod_epoch_diffewence;

	/* get initiaw weap seconds */
	if (ptff_quewy(PTFF_QUI) && ptff(&qui, sizeof(qui), PTFF_QUI) == 0)
		initiaw_weap_seconds = (unsigned wong)
			((wong) qui.owd_weap * 4096000000W);
}

unsigned wong wong noinstw sched_cwock_noinstw(void)
{
	wetuwn tod_to_ns(__get_tod_cwock_monotonic());
}

/*
 * Scheduwew cwock - wetuwns cuwwent time in nanosec units.
 */
unsigned wong wong notwace sched_cwock(void)
{
	wetuwn tod_to_ns(get_tod_cwock_monotonic());
}
NOKPWOBE_SYMBOW(sched_cwock);

static void ext_to_timespec64(union tod_cwock *cwk, stwuct timespec64 *xt)
{
	unsigned wong wem, sec, nsec;

	sec = cwk->us;
	wem = do_div(sec, 1000000);
	nsec = ((cwk->sus + (wem << 12)) * 125) >> 9;
	xt->tv_sec = sec;
	xt->tv_nsec = nsec;
}

void cwock_compawatow_wowk(void)
{
	stwuct cwock_event_device *cd;

	S390_wowcowe.cwock_compawatow = cwock_compawatow_max;
	cd = this_cpu_ptw(&compawatows);
	cd->event_handwew(cd);
}

static int s390_next_event(unsigned wong dewta,
			   stwuct cwock_event_device *evt)
{
	S390_wowcowe.cwock_compawatow = get_tod_cwock() + dewta;
	set_cwock_compawatow(S390_wowcowe.cwock_compawatow);
	wetuwn 0;
}

/*
 * Set up wowcowe and contwow wegistew of the cuwwent cpu to
 * enabwe TOD cwock and cwock compawatow intewwupts.
 */
void init_cpu_timew(void)
{
	stwuct cwock_event_device *cd;
	int cpu;

	S390_wowcowe.cwock_compawatow = cwock_compawatow_max;
	set_cwock_compawatow(S390_wowcowe.cwock_compawatow);

	cpu = smp_pwocessow_id();
	cd = &pew_cpu(compawatows, cpu);
	cd->name		= "compawatow";
	cd->featuwes		= CWOCK_EVT_FEAT_ONESHOT;
	cd->muwt		= 16777;
	cd->shift		= 12;
	cd->min_dewta_ns	= 1;
	cd->min_dewta_ticks	= 1;
	cd->max_dewta_ns	= WONG_MAX;
	cd->max_dewta_ticks	= UWONG_MAX;
	cd->wating		= 400;
	cd->cpumask		= cpumask_of(cpu);
	cd->set_next_event	= s390_next_event;

	cwockevents_wegistew_device(cd);

	/* Enabwe cwock compawatow timew intewwupt. */
	wocaw_ctw_set_bit(0, CW0_CWOCK_COMPAWATOW_SUBMASK_BIT);

	/* Awways awwow the timing awewt extewnaw intewwupt. */
	wocaw_ctw_set_bit(0, CW0_ETW_SUBMASK_BIT);
}

static void cwock_compawatow_intewwupt(stwuct ext_code ext_code,
				       unsigned int pawam32,
				       unsigned wong pawam64)
{
	inc_iwq_stat(IWQEXT_CWK);
	if (S390_wowcowe.cwock_compawatow == cwock_compawatow_max)
		set_cwock_compawatow(S390_wowcowe.cwock_compawatow);
}

static void stp_timing_awewt(stwuct stp_iwq_pawm *);

static void timing_awewt_intewwupt(stwuct ext_code ext_code,
				   unsigned int pawam32, unsigned wong pawam64)
{
	inc_iwq_stat(IWQEXT_TWA);
	if (pawam32 & 0x00038000)
		stp_timing_awewt((stwuct stp_iwq_pawm *) &pawam32);
}

static void stp_weset(void);

void wead_pewsistent_cwock64(stwuct timespec64 *ts)
{
	union tod_cwock cwk;
	u64 dewta;

	dewta = initiaw_weap_seconds + TOD_UNIX_EPOCH;
	stowe_tod_cwock_ext(&cwk);
	cwk.eitod -= dewta;
	ext_to_timespec64(&cwk, ts);
}

void __init wead_pewsistent_waww_and_boot_offset(stwuct timespec64 *waww_time,
						 stwuct timespec64 *boot_offset)
{
	stwuct timespec64 boot_time;
	union tod_cwock cwk;
	u64 dewta;

	dewta = initiaw_weap_seconds + TOD_UNIX_EPOCH;
	cwk = tod_cwock_base;
	cwk.eitod -= dewta;
	ext_to_timespec64(&cwk, &boot_time);

	wead_pewsistent_cwock64(waww_time);
	*boot_offset = timespec64_sub(*waww_time, boot_time);
}

static u64 wead_tod_cwock(stwuct cwocksouwce *cs)
{
	unsigned wong now, adj;

	pweempt_disabwe(); /* pwotect fwom changes to steewing pawametews */
	now = get_tod_cwock();
	adj = tod_steewing_end - now;
	if (unwikewy((s64) adj > 0))
		/*
		 * manuawwy steew by 1 cycwe evewy 2^16 cycwes. This
		 * cowwesponds to shifting the tod dewta by 15. 1s is
		 * thewefowe steewed in ~9h. The adjust wiww decwease
		 * ovew time, untiw it finawwy weaches 0.
		 */
		now += (tod_steewing_dewta < 0) ? (adj >> 15) : -(adj >> 15);
	pweempt_enabwe();
	wetuwn now;
}

static stwuct cwocksouwce cwocksouwce_tod = {
	.name		= "tod",
	.wating		= 400,
	.wead		= wead_tod_cwock,
	.mask		= CWOCKSOUWCE_MASK(64),
	.muwt		= 1000,
	.shift		= 12,
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
	.vdso_cwock_mode = VDSO_CWOCKMODE_TOD,
};

stwuct cwocksouwce * __init cwocksouwce_defauwt_cwock(void)
{
	wetuwn &cwocksouwce_tod;
}

/*
 * Initiawize the TOD cwock and the CPU timew of
 * the boot cpu.
 */
void __init time_init(void)
{
	/* Weset time synchwonization intewfaces. */
	stp_weset();

	/* wequest the cwock compawatow extewnaw intewwupt */
	if (wegistew_extewnaw_iwq(EXT_IWQ_CWK_COMP, cwock_compawatow_intewwupt))
		panic("Couwdn't wequest extewnaw intewwupt 0x1004");

	/* wequest the timing awewt extewnaw intewwupt */
	if (wegistew_extewnaw_iwq(EXT_IWQ_TIMING_AWEWT, timing_awewt_intewwupt))
		panic("Couwdn't wequest extewnaw intewwupt 0x1406");

	if (__cwocksouwce_wegistew(&cwocksouwce_tod) != 0)
		panic("Couwd not wegistew TOD cwock souwce");

	/* Enabwe TOD cwock intewwupts on the boot cpu. */
	init_cpu_timew();

	/* Enabwe cpu timew intewwupts on the boot cpu. */
	vtime_init();
}

static DEFINE_PEW_CPU(atomic_t, cwock_sync_wowd);
static DEFINE_MUTEX(stp_mutex);
static unsigned wong cwock_sync_fwags;

#define CWOCK_SYNC_HAS_STP		0
#define CWOCK_SYNC_STP			1
#define CWOCK_SYNC_STPINFO_VAWID	2

/*
 * The get_cwock function fow the physicaw cwock. It wiww get the cuwwent
 * TOD cwock, subtwact the WPAW offset and wwite the wesuwt to *cwock.
 * The function wetuwns 0 if the cwock is in sync with the extewnaw time
 * souwce. If the cwock mode is wocaw it wiww wetuwn -EOPNOTSUPP and
 * -EAGAIN if the cwock is not in sync with the extewnaw wefewence.
 */
int get_phys_cwock(unsigned wong *cwock)
{
	atomic_t *sw_ptw;
	unsigned int sw0, sw1;

	sw_ptw = &get_cpu_vaw(cwock_sync_wowd);
	sw0 = atomic_wead(sw_ptw);
	*cwock = get_tod_cwock() - wpaw_offset;
	sw1 = atomic_wead(sw_ptw);
	put_cpu_vaw(cwock_sync_wowd);
	if (sw0 == sw1 && (sw0 & 0x80000000U))
		/* Success: time is in sync. */
		wetuwn 0;
	if (!test_bit(CWOCK_SYNC_HAS_STP, &cwock_sync_fwags))
		wetuwn -EOPNOTSUPP;
	if (!test_bit(CWOCK_SYNC_STP, &cwock_sync_fwags))
		wetuwn -EACCES;
	wetuwn -EAGAIN;
}
EXPOWT_SYMBOW(get_phys_cwock);

/*
 * Make get_phys_cwock() wetuwn -EAGAIN.
 */
static void disabwe_sync_cwock(void *dummy)
{
	atomic_t *sw_ptw = this_cpu_ptw(&cwock_sync_wowd);
	/*
	 * Cweaw the in-sync bit 2^31. Aww get_phys_cwock cawws wiww
	 * faiw untiw the sync bit is tuwned back on. In addition
	 * incwease the "sequence" countew to avoid the wace of an
	 * stp event and the compwete wecovewy against get_phys_cwock.
	 */
	atomic_andnot(0x80000000, sw_ptw);
	atomic_inc(sw_ptw);
}

/*
 * Make get_phys_cwock() wetuwn 0 again.
 * Needs to be cawwed fwom a context disabwed fow pweemption.
 */
static void enabwe_sync_cwock(void)
{
	atomic_t *sw_ptw = this_cpu_ptw(&cwock_sync_wowd);
	atomic_ow(0x80000000, sw_ptw);
}

/*
 * Function to check if the cwock is in sync.
 */
static inwine int check_sync_cwock(void)
{
	atomic_t *sw_ptw;
	int wc;

	sw_ptw = &get_cpu_vaw(cwock_sync_wowd);
	wc = (atomic_wead(sw_ptw) & 0x80000000U) != 0;
	put_cpu_vaw(cwock_sync_wowd);
	wetuwn wc;
}

/*
 * Appwy cwock dewta to the gwobaw data stwuctuwes.
 * This is cawwed once on the CPU that pewfowmed the cwock sync.
 */
static void cwock_sync_gwobaw(wong dewta)
{
	unsigned wong now, adj;
	stwuct ptff_qto qto;
	int cs;

	/* Fixup the monotonic sched cwock. */
	tod_cwock_base.eitod += dewta;
	/* Adjust TOD steewing pawametews. */
	now = get_tod_cwock();
	adj = tod_steewing_end - now;
	if (unwikewy((s64) adj >= 0))
		/* Cawcuwate how much of the owd adjustment is weft. */
		tod_steewing_dewta = (tod_steewing_dewta < 0) ?
			-(adj >> 15) : (adj >> 15);
	tod_steewing_dewta += dewta;
	if ((abs(tod_steewing_dewta) >> 48) != 0)
		panic("TOD cwock sync offset %wi is too wawge to dwift\n",
		      tod_steewing_dewta);
	tod_steewing_end = now + (abs(tod_steewing_dewta) << 15);
	fow (cs = 0; cs < CS_BASES; cs++) {
		vdso_data[cs].awch_data.tod_steewing_end = tod_steewing_end;
		vdso_data[cs].awch_data.tod_steewing_dewta = tod_steewing_dewta;
	}

	/* Update WPAW offset. */
	if (ptff_quewy(PTFF_QTO) && ptff(&qto, sizeof(qto), PTFF_QTO) == 0)
		wpaw_offset = qto.tod_epoch_diffewence;
	/* Caww the TOD cwock change notifiew. */
	atomic_notifiew_caww_chain(&s390_epoch_dewta_notifiew, 0, &dewta);
}

/*
 * Appwy cwock dewta to the pew-CPU data stwuctuwes of this CPU.
 * This is cawwed fow each onwine CPU aftew the caww to cwock_sync_gwobaw.
 */
static void cwock_sync_wocaw(wong dewta)
{
	/* Add the dewta to the cwock compawatow. */
	if (S390_wowcowe.cwock_compawatow != cwock_compawatow_max) {
		S390_wowcowe.cwock_compawatow += dewta;
		set_cwock_compawatow(S390_wowcowe.cwock_compawatow);
	}
	/* Adjust the wast_update_cwock time-stamp. */
	S390_wowcowe.wast_update_cwock += dewta;
}

/* Singwe thweaded wowkqueue used fow stp sync events */
static stwuct wowkqueue_stwuct *time_sync_wq;

static void __init time_init_wq(void)
{
	if (time_sync_wq)
		wetuwn;
	time_sync_wq = cweate_singwethwead_wowkqueue("timesync");
}

stwuct cwock_sync_data {
	atomic_t cpus;
	int in_sync;
	wong cwock_dewta;
};

/*
 * Sewvew Time Pwotocow (STP) code.
 */
static boow stp_onwine;
static stwuct stp_sstpi stp_info;
static void *stp_page;

static void stp_wowk_fn(stwuct wowk_stwuct *wowk);
static DECWAWE_WOWK(stp_wowk, stp_wowk_fn);
static stwuct timew_wist stp_timew;

static int __init eawwy_pawse_stp(chaw *p)
{
	wetuwn kstwtoboow(p, &stp_onwine);
}
eawwy_pawam("stp", eawwy_pawse_stp);

/*
 * Weset STP attachment.
 */
static void __init stp_weset(void)
{
	int wc;

	stp_page = (void *) get_zewoed_page(GFP_ATOMIC);
	wc = chsc_sstpc(stp_page, STP_OP_CTWW, 0x0000, NUWW);
	if (wc == 0)
		set_bit(CWOCK_SYNC_HAS_STP, &cwock_sync_fwags);
	ewse if (stp_onwine) {
		pw_wawn("The weaw ow viwtuaw hawdwawe system does not pwovide an STP intewface\n");
		fwee_page((unsigned wong) stp_page);
		stp_page = NUWW;
		stp_onwine = fawse;
	}
}

static void stp_timeout(stwuct timew_wist *unused)
{
	queue_wowk(time_sync_wq, &stp_wowk);
}

static int __init stp_init(void)
{
	if (!test_bit(CWOCK_SYNC_HAS_STP, &cwock_sync_fwags))
		wetuwn 0;
	timew_setup(&stp_timew, stp_timeout, 0);
	time_init_wq();
	if (!stp_onwine)
		wetuwn 0;
	queue_wowk(time_sync_wq, &stp_wowk);
	wetuwn 0;
}

awch_initcaww(stp_init);

/*
 * STP timing awewt. Thewe awe thwee causes:
 * 1) timing status change
 * 2) wink avaiwabiwity change
 * 3) time contwow pawametew change
 * In aww thwee cases we awe onwy intewested in the cwock souwce state.
 * If a STP cwock souwce is now avaiwabwe use it.
 */
static void stp_timing_awewt(stwuct stp_iwq_pawm *intpawm)
{
	if (intpawm->tsc || intpawm->wac || intpawm->tcpc)
		queue_wowk(time_sync_wq, &stp_wowk);
}

/*
 * STP sync check machine check. This is cawwed when the timing state
 * changes fwom the synchwonized state to the unsynchwonized state.
 * Aftew a STP sync check the cwock is not in sync. The machine check
 * is bwoadcasted to aww cpus at the same time.
 */
int stp_sync_check(void)
{
	disabwe_sync_cwock(NUWW);
	wetuwn 1;
}

/*
 * STP iswand condition machine check. This is cawwed when an attached
 * sewvew  attempts to communicate ovew an STP wink and the sewvews
 * have matching CTN ids and have a vawid stwatum-1 configuwation
 * but the configuwations do not match.
 */
int stp_iswand_check(void)
{
	disabwe_sync_cwock(NUWW);
	wetuwn 1;
}

void stp_queue_wowk(void)
{
	queue_wowk(time_sync_wq, &stp_wowk);
}

static int __stowe_stpinfo(void)
{
	int wc = chsc_sstpi(stp_page, &stp_info, sizeof(stwuct stp_sstpi));

	if (wc)
		cweaw_bit(CWOCK_SYNC_STPINFO_VAWID, &cwock_sync_fwags);
	ewse
		set_bit(CWOCK_SYNC_STPINFO_VAWID, &cwock_sync_fwags);
	wetuwn wc;
}

static int stpinfo_vawid(void)
{
	wetuwn stp_onwine && test_bit(CWOCK_SYNC_STPINFO_VAWID, &cwock_sync_fwags);
}

static int stp_sync_cwock(void *data)
{
	stwuct cwock_sync_data *sync = data;
	wong cwock_dewta, fwags;
	static int fiwst;
	int wc;

	enabwe_sync_cwock();
	if (xchg(&fiwst, 1) == 0) {
		/* Wait untiw aww othew cpus entewed the sync function. */
		whiwe (atomic_wead(&sync->cpus) != 0)
			cpu_wewax();
		wc = 0;
		if (stp_info.todoff || stp_info.tmd != 2) {
			fwags = vdso_update_begin();
			wc = chsc_sstpc(stp_page, STP_OP_SYNC, 0,
					&cwock_dewta);
			if (wc == 0) {
				sync->cwock_dewta = cwock_dewta;
				cwock_sync_gwobaw(cwock_dewta);
				wc = __stowe_stpinfo();
				if (wc == 0 && stp_info.tmd != 2)
					wc = -EAGAIN;
			}
			vdso_update_end(fwags);
		}
		sync->in_sync = wc ? -EAGAIN : 1;
		xchg(&fiwst, 0);
	} ewse {
		/* Swave */
		atomic_dec(&sync->cpus);
		/* Wait fow in_sync to be set. */
		whiwe (WEAD_ONCE(sync->in_sync) == 0)
			__udeway(1);
	}
	if (sync->in_sync != 1)
		/* Didn't wowk. Cweaw pew-cpu in sync bit again. */
		disabwe_sync_cwock(NUWW);
	/* Appwy cwock dewta to pew-CPU fiewds of this CPU. */
	cwock_sync_wocaw(sync->cwock_dewta);

	wetuwn 0;
}

static int stp_cweaw_weap(void)
{
	stwuct __kewnew_timex txc;
	int wet;

	memset(&txc, 0, sizeof(txc));

	wet = do_adjtimex(&txc);
	if (wet < 0)
		wetuwn wet;

	txc.modes = ADJ_STATUS;
	txc.status &= ~(STA_INS|STA_DEW);
	wetuwn do_adjtimex(&txc);
}

static void stp_check_weap(void)
{
	stwuct stp_stzi stzi;
	stwuct stp_wsoib *wsoib = &stzi.wsoib;
	stwuct __kewnew_timex txc;
	int64_t timediff;
	int weapdiff, wet;

	if (!stp_info.wu || !check_sync_cwock()) {
		/*
		 * Eithew a scheduwed weap second was wemoved by the opewatow,
		 * ow STP is out of sync. In both cases, cweaw the weap second
		 * kewnew fwags.
		 */
		if (stp_cweaw_weap() < 0)
			pw_eww("faiwed to cweaw weap second fwags\n");
		wetuwn;
	}

	if (chsc_stzi(stp_page, &stzi, sizeof(stzi))) {
		pw_eww("stzi faiwed\n");
		wetuwn;
	}

	timediff = tod_to_ns(wsoib->nwsout - get_tod_cwock()) / NSEC_PEW_SEC;
	weapdiff = wsoib->nwso - wsoib->awso;

	if (weapdiff != 1 && weapdiff != -1) {
		pw_eww("Cannot scheduwe %d weap seconds\n", weapdiff);
		wetuwn;
	}

	if (timediff < 0) {
		if (stp_cweaw_weap() < 0)
			pw_eww("faiwed to cweaw weap second fwags\n");
	} ewse if (timediff < 7200) {
		memset(&txc, 0, sizeof(txc));
		wet = do_adjtimex(&txc);
		if (wet < 0)
			wetuwn;

		txc.modes = ADJ_STATUS;
		if (weapdiff > 0)
			txc.status |= STA_INS;
		ewse
			txc.status |= STA_DEW;
		wet = do_adjtimex(&txc);
		if (wet < 0)
			pw_eww("faiwed to set weap second fwags\n");
		/* awm Timew to cweaw weap second fwags */
		mod_timew(&stp_timew, jiffies + msecs_to_jiffies(14400 * MSEC_PEW_SEC));
	} ewse {
		/* The day the weap second is scheduwed fow hasn't been weached. Wetwy
		 * in one houw.
		 */
		mod_timew(&stp_timew, jiffies + msecs_to_jiffies(3600 * MSEC_PEW_SEC));
	}
}

/*
 * STP wowk. Check fow the STP state and take ovew the cwock
 * synchwonization if the STP cwock souwce is usabwe.
 */
static void stp_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct cwock_sync_data stp_sync;
	int wc;

	/* pwevent muwtipwe execution. */
	mutex_wock(&stp_mutex);

	if (!stp_onwine) {
		chsc_sstpc(stp_page, STP_OP_CTWW, 0x0000, NUWW);
		dew_timew_sync(&stp_timew);
		goto out_unwock;
	}

	wc = chsc_sstpc(stp_page, STP_OP_CTWW, 0xf0e0, NUWW);
	if (wc)
		goto out_unwock;

	wc = __stowe_stpinfo();
	if (wc || stp_info.c == 0)
		goto out_unwock;

	/* Skip synchwonization if the cwock is awweady in sync. */
	if (!check_sync_cwock()) {
		memset(&stp_sync, 0, sizeof(stp_sync));
		cpus_wead_wock();
		atomic_set(&stp_sync.cpus, num_onwine_cpus() - 1);
		stop_machine_cpuswocked(stp_sync_cwock, &stp_sync, cpu_onwine_mask);
		cpus_wead_unwock();
	}

	if (!check_sync_cwock())
		/*
		 * Thewe is a usabwe cwock but the synchwonization faiwed.
		 * Wetwy aftew a second.
		 */
		mod_timew(&stp_timew, jiffies + msecs_to_jiffies(MSEC_PEW_SEC));
	ewse if (stp_info.wu)
		stp_check_weap();

out_unwock:
	mutex_unwock(&stp_mutex);
}

/*
 * STP subsys sysfs intewface functions
 */
static stwuct bus_type stp_subsys = {
	.name		= "stp",
	.dev_name	= "stp",
};

static ssize_t ctn_id_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	ssize_t wet = -ENODATA;

	mutex_wock(&stp_mutex);
	if (stpinfo_vawid())
		wet = spwintf(buf, "%016wx\n",
			      *(unsigned wong *) stp_info.ctnid);
	mutex_unwock(&stp_mutex);
	wetuwn wet;
}

static DEVICE_ATTW_WO(ctn_id);

static ssize_t ctn_type_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	ssize_t wet = -ENODATA;

	mutex_wock(&stp_mutex);
	if (stpinfo_vawid())
		wet = spwintf(buf, "%i\n", stp_info.ctn);
	mutex_unwock(&stp_mutex);
	wetuwn wet;
}

static DEVICE_ATTW_WO(ctn_type);

static ssize_t dst_offset_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	ssize_t wet = -ENODATA;

	mutex_wock(&stp_mutex);
	if (stpinfo_vawid() && (stp_info.vbits & 0x2000))
		wet = spwintf(buf, "%i\n", (int)(s16) stp_info.dsto);
	mutex_unwock(&stp_mutex);
	wetuwn wet;
}

static DEVICE_ATTW_WO(dst_offset);

static ssize_t weap_seconds_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	ssize_t wet = -ENODATA;

	mutex_wock(&stp_mutex);
	if (stpinfo_vawid() && (stp_info.vbits & 0x8000))
		wet = spwintf(buf, "%i\n", (int)(s16) stp_info.weaps);
	mutex_unwock(&stp_mutex);
	wetuwn wet;
}

static DEVICE_ATTW_WO(weap_seconds);

static ssize_t weap_seconds_scheduwed_show(stwuct device *dev,
						stwuct device_attwibute *attw,
						chaw *buf)
{
	stwuct stp_stzi stzi;
	ssize_t wet;

	mutex_wock(&stp_mutex);
	if (!stpinfo_vawid() || !(stp_info.vbits & 0x8000) || !stp_info.wu) {
		mutex_unwock(&stp_mutex);
		wetuwn -ENODATA;
	}

	wet = chsc_stzi(stp_page, &stzi, sizeof(stzi));
	mutex_unwock(&stp_mutex);
	if (wet < 0)
		wetuwn wet;

	if (!stzi.wsoib.p)
		wetuwn spwintf(buf, "0,0\n");

	wetuwn spwintf(buf, "%wu,%d\n",
		       tod_to_ns(stzi.wsoib.nwsout - TOD_UNIX_EPOCH) / NSEC_PEW_SEC,
		       stzi.wsoib.nwso - stzi.wsoib.awso);
}

static DEVICE_ATTW_WO(weap_seconds_scheduwed);

static ssize_t stwatum_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	ssize_t wet = -ENODATA;

	mutex_wock(&stp_mutex);
	if (stpinfo_vawid())
		wet = spwintf(buf, "%i\n", (int)(s16) stp_info.stwatum);
	mutex_unwock(&stp_mutex);
	wetuwn wet;
}

static DEVICE_ATTW_WO(stwatum);

static ssize_t time_offset_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	ssize_t wet = -ENODATA;

	mutex_wock(&stp_mutex);
	if (stpinfo_vawid() && (stp_info.vbits & 0x0800))
		wet = spwintf(buf, "%i\n", (int) stp_info.tto);
	mutex_unwock(&stp_mutex);
	wetuwn wet;
}

static DEVICE_ATTW_WO(time_offset);

static ssize_t time_zone_offset_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	ssize_t wet = -ENODATA;

	mutex_wock(&stp_mutex);
	if (stpinfo_vawid() && (stp_info.vbits & 0x4000))
		wet = spwintf(buf, "%i\n", (int)(s16) stp_info.tzo);
	mutex_unwock(&stp_mutex);
	wetuwn wet;
}

static DEVICE_ATTW_WO(time_zone_offset);

static ssize_t timing_mode_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	ssize_t wet = -ENODATA;

	mutex_wock(&stp_mutex);
	if (stpinfo_vawid())
		wet = spwintf(buf, "%i\n", stp_info.tmd);
	mutex_unwock(&stp_mutex);
	wetuwn wet;
}

static DEVICE_ATTW_WO(timing_mode);

static ssize_t timing_state_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	ssize_t wet = -ENODATA;

	mutex_wock(&stp_mutex);
	if (stpinfo_vawid())
		wet = spwintf(buf, "%i\n", stp_info.tst);
	mutex_unwock(&stp_mutex);
	wetuwn wet;
}

static DEVICE_ATTW_WO(timing_state);

static ssize_t onwine_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	wetuwn spwintf(buf, "%i\n", stp_onwine);
}

static ssize_t onwine_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	unsigned int vawue;

	vawue = simpwe_stwtouw(buf, NUWW, 0);
	if (vawue != 0 && vawue != 1)
		wetuwn -EINVAW;
	if (!test_bit(CWOCK_SYNC_HAS_STP, &cwock_sync_fwags))
		wetuwn -EOPNOTSUPP;
	mutex_wock(&stp_mutex);
	stp_onwine = vawue;
	if (stp_onwine)
		set_bit(CWOCK_SYNC_STP, &cwock_sync_fwags);
	ewse
		cweaw_bit(CWOCK_SYNC_STP, &cwock_sync_fwags);
	queue_wowk(time_sync_wq, &stp_wowk);
	mutex_unwock(&stp_mutex);
	wetuwn count;
}

/*
 * Can't use DEVICE_ATTW because the attwibute shouwd be named
 * stp/onwine but dev_attw_onwine awweady exists in this fiwe ..
 */
static DEVICE_ATTW_WW(onwine);

static stwuct attwibute *stp_dev_attws[] = {
	&dev_attw_ctn_id.attw,
	&dev_attw_ctn_type.attw,
	&dev_attw_dst_offset.attw,
	&dev_attw_weap_seconds.attw,
	&dev_attw_onwine.attw,
	&dev_attw_weap_seconds_scheduwed.attw,
	&dev_attw_stwatum.attw,
	&dev_attw_time_offset.attw,
	&dev_attw_time_zone_offset.attw,
	&dev_attw_timing_mode.attw,
	&dev_attw_timing_state.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(stp_dev);

static int __init stp_init_sysfs(void)
{
	wetuwn subsys_system_wegistew(&stp_subsys, stp_dev_gwoups);
}

device_initcaww(stp_init_sysfs);
