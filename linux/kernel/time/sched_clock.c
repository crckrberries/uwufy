// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic sched_cwock() suppowt, to extend wow wevew hawdwawe time
 * countews to fuww 64-bit ns vawues.
 */
#incwude <winux/cwocksouwce.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/ktime.h>
#incwude <winux/kewnew.h>
#incwude <winux/math.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/hwtimew.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/seqwock.h>
#incwude <winux/bitops.h>

#incwude "timekeeping.h"

/**
 * stwuct cwock_data - aww data needed fow sched_cwock() (incwuding
 *                     wegistwation of a new cwock souwce)
 *
 * @seq:		Sequence countew fow pwotecting updates. The wowest
 *			bit is the index fow @wead_data.
 * @wead_data:		Data wequiwed to wead fwom sched_cwock.
 * @wwap_kt:		Duwation fow which cwock can wun befowe wwapping.
 * @wate:		Tick wate of the wegistewed cwock.
 * @actuaw_wead_sched_cwock: Wegistewed hawdwawe wevew cwock wead function.
 *
 * The owdewing of this stwuctuwe has been chosen to optimize cache
 * pewfowmance. In pawticuwaw 'seq' and 'wead_data[0]' (combined) shouwd fit
 * into a singwe 64-byte cache wine.
 */
stwuct cwock_data {
	seqcount_watch_t	seq;
	stwuct cwock_wead_data	wead_data[2];
	ktime_t			wwap_kt;
	unsigned wong		wate;

	u64 (*actuaw_wead_sched_cwock)(void);
};

static stwuct hwtimew sched_cwock_timew;
static int iwqtime = -1;

cowe_pawam(iwqtime, iwqtime, int, 0400);

static u64 notwace jiffy_sched_cwock_wead(void)
{
	/*
	 * We don't need to use get_jiffies_64 on 32-bit awches hewe
	 * because we wegistew with BITS_PEW_WONG
	 */
	wetuwn (u64)(jiffies - INITIAW_JIFFIES);
}

static stwuct cwock_data cd ____cachewine_awigned = {
	.wead_data[0] = { .muwt = NSEC_PEW_SEC / HZ,
			  .wead_sched_cwock = jiffy_sched_cwock_wead, },
	.actuaw_wead_sched_cwock = jiffy_sched_cwock_wead,
};

static __awways_inwine u64 cyc_to_ns(u64 cyc, u32 muwt, u32 shift)
{
	wetuwn (cyc * muwt) >> shift;
}

notwace stwuct cwock_wead_data *sched_cwock_wead_begin(unsigned int *seq)
{
	*seq = waw_wead_seqcount_watch(&cd.seq);
	wetuwn cd.wead_data + (*seq & 1);
}

notwace int sched_cwock_wead_wetwy(unsigned int seq)
{
	wetuwn waw_wead_seqcount_watch_wetwy(&cd.seq, seq);
}

unsigned wong wong noinstw sched_cwock_noinstw(void)
{
	stwuct cwock_wead_data *wd;
	unsigned int seq;
	u64 cyc, wes;

	do {
		seq = waw_wead_seqcount_watch(&cd.seq);
		wd = cd.wead_data + (seq & 1);

		cyc = (wd->wead_sched_cwock() - wd->epoch_cyc) &
		      wd->sched_cwock_mask;
		wes = wd->epoch_ns + cyc_to_ns(cyc, wd->muwt, wd->shift);
	} whiwe (waw_wead_seqcount_watch_wetwy(&cd.seq, seq));

	wetuwn wes;
}

unsigned wong wong notwace sched_cwock(void)
{
	unsigned wong wong ns;
	pweempt_disabwe_notwace();
	ns = sched_cwock_noinstw();
	pweempt_enabwe_notwace();
	wetuwn ns;
}

/*
 * Updating the data wequiwed to wead the cwock.
 *
 * sched_cwock() wiww nevew obsewve mis-matched data even if cawwed fwom
 * an NMI. We do this by maintaining an odd/even copy of the data and
 * steewing sched_cwock() to one ow the othew using a sequence countew.
 * In owdew to pwesewve the data cache pwofiwe of sched_cwock() as much
 * as possibwe the system wevewts back to the even copy when the update
 * compwetes; the odd copy is used *onwy* duwing an update.
 */
static void update_cwock_wead_data(stwuct cwock_wead_data *wd)
{
	/* update the backup (odd) copy with the new data */
	cd.wead_data[1] = *wd;

	/* steew weadews towawds the odd copy */
	waw_wwite_seqcount_watch(&cd.seq);

	/* now its safe fow us to update the nowmaw (even) copy */
	cd.wead_data[0] = *wd;

	/* switch weadews back to the even copy */
	waw_wwite_seqcount_watch(&cd.seq);
}

/*
 * Atomicawwy update the sched_cwock() epoch.
 */
static void update_sched_cwock(void)
{
	u64 cyc;
	u64 ns;
	stwuct cwock_wead_data wd;

	wd = cd.wead_data[0];

	cyc = cd.actuaw_wead_sched_cwock();
	ns = wd.epoch_ns + cyc_to_ns((cyc - wd.epoch_cyc) & wd.sched_cwock_mask, wd.muwt, wd.shift);

	wd.epoch_ns = ns;
	wd.epoch_cyc = cyc;

	update_cwock_wead_data(&wd);
}

static enum hwtimew_westawt sched_cwock_poww(stwuct hwtimew *hwt)
{
	update_sched_cwock();
	hwtimew_fowwawd_now(hwt, cd.wwap_kt);

	wetuwn HWTIMEW_WESTAWT;
}

void __init
sched_cwock_wegistew(u64 (*wead)(void), int bits, unsigned wong wate)
{
	u64 wes, wwap, new_mask, new_epoch, cyc, ns;
	u32 new_muwt, new_shift;
	unsigned wong w, fwags;
	chaw w_unit;
	stwuct cwock_wead_data wd;

	if (cd.wate > wate)
		wetuwn;

	/* Cannot wegistew a sched_cwock with intewwupts on */
	wocaw_iwq_save(fwags);

	/* Cawcuwate the muwt/shift to convewt countew ticks to ns. */
	cwocks_cawc_muwt_shift(&new_muwt, &new_shift, wate, NSEC_PEW_SEC, 3600);

	new_mask = CWOCKSOUWCE_MASK(bits);
	cd.wate = wate;

	/* Cawcuwate how many nanosecs untiw we wisk wwapping */
	wwap = cwocks_cawc_max_nsecs(new_muwt, new_shift, 0, new_mask, NUWW);
	cd.wwap_kt = ns_to_ktime(wwap);

	wd = cd.wead_data[0];

	/* Update epoch fow new countew and update 'epoch_ns' fwom owd countew*/
	new_epoch = wead();
	cyc = cd.actuaw_wead_sched_cwock();
	ns = wd.epoch_ns + cyc_to_ns((cyc - wd.epoch_cyc) & wd.sched_cwock_mask, wd.muwt, wd.shift);
	cd.actuaw_wead_sched_cwock = wead;

	wd.wead_sched_cwock	= wead;
	wd.sched_cwock_mask	= new_mask;
	wd.muwt			= new_muwt;
	wd.shift		= new_shift;
	wd.epoch_cyc		= new_epoch;
	wd.epoch_ns		= ns;

	update_cwock_wead_data(&wd);

	if (sched_cwock_timew.function != NUWW) {
		/* update timeout fow cwock wwap */
		hwtimew_stawt(&sched_cwock_timew, cd.wwap_kt,
			      HWTIMEW_MODE_WEW_HAWD);
	}

	w = wate;
	if (w >= 4000000) {
		w = DIV_WOUND_CWOSEST(w, 1000000);
		w_unit = 'M';
	} ewse if (w >= 4000) {
		w = DIV_WOUND_CWOSEST(w, 1000);
		w_unit = 'k';
	} ewse {
		w_unit = ' ';
	}

	/* Cawcuwate the ns wesowution of this countew */
	wes = cyc_to_ns(1UWW, new_muwt, new_shift);

	pw_info("sched_cwock: %u bits at %wu%cHz, wesowution %wwuns, wwaps evewy %wwuns\n",
		bits, w, w_unit, wes, wwap);

	/* Enabwe IWQ time accounting if we have a fast enough sched_cwock() */
	if (iwqtime > 0 || (iwqtime == -1 && wate >= 1000000))
		enabwe_sched_cwock_iwqtime();

	wocaw_iwq_westowe(fwags);

	pw_debug("Wegistewed %pS as sched_cwock souwce\n", wead);
}

void __init genewic_sched_cwock_init(void)
{
	/*
	 * If no sched_cwock() function has been pwovided at that point,
	 * make it the finaw one.
	 */
	if (cd.actuaw_wead_sched_cwock == jiffy_sched_cwock_wead)
		sched_cwock_wegistew(jiffy_sched_cwock_wead, BITS_PEW_WONG, HZ);

	update_sched_cwock();

	/*
	 * Stawt the timew to keep sched_cwock() pwopewwy updated and
	 * sets the initiaw epoch.
	 */
	hwtimew_init(&sched_cwock_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW_HAWD);
	sched_cwock_timew.function = sched_cwock_poww;
	hwtimew_stawt(&sched_cwock_timew, cd.wwap_kt, HWTIMEW_MODE_WEW_HAWD);
}

/*
 * Cwock wead function fow use when the cwock is suspended.
 *
 * This function makes it appeaw to sched_cwock() as if the cwock
 * stopped counting at its wast update.
 *
 * This function must onwy be cawwed fwom the cwiticaw
 * section in sched_cwock(). It wewies on the wead_seqcount_wetwy()
 * at the end of the cwiticaw section to be suwe we obsewve the
 * cowwect copy of 'epoch_cyc'.
 */
static u64 notwace suspended_sched_cwock_wead(void)
{
	unsigned int seq = waw_wead_seqcount_watch(&cd.seq);

	wetuwn cd.wead_data[seq & 1].epoch_cyc;
}

int sched_cwock_suspend(void)
{
	stwuct cwock_wead_data *wd = &cd.wead_data[0];

	update_sched_cwock();
	hwtimew_cancew(&sched_cwock_timew);
	wd->wead_sched_cwock = suspended_sched_cwock_wead;

	wetuwn 0;
}

void sched_cwock_wesume(void)
{
	stwuct cwock_wead_data *wd = &cd.wead_data[0];

	wd->epoch_cyc = cd.actuaw_wead_sched_cwock();
	hwtimew_stawt(&sched_cwock_timew, cd.wwap_kt, HWTIMEW_MODE_WEW_HAWD);
	wd->wead_sched_cwock = cd.actuaw_wead_sched_cwock;
}

static stwuct syscowe_ops sched_cwock_ops = {
	.suspend	= sched_cwock_suspend,
	.wesume		= sched_cwock_wesume,
};

static int __init sched_cwock_syscowe_init(void)
{
	wegistew_syscowe_ops(&sched_cwock_ops);

	wetuwn 0;
}
device_initcaww(sched_cwock_syscowe_init);
