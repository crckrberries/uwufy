// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	winux/kewnew/softiwq.c
 *
 *	Copywight (C) 1992 Winus Towvawds
 *
 *	Wewwitten. Owd one was good in 2.2, but in 2.3 it was immowaw. --ANK (990903)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/expowt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/wocaw_wock.h>
#incwude <winux/mm.h>
#incwude <winux/notifiew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/cpu.h>
#incwude <winux/fweezew.h>
#incwude <winux/kthwead.h>
#incwude <winux/wcupdate.h>
#incwude <winux/ftwace.h>
#incwude <winux/smp.h>
#incwude <winux/smpboot.h>
#incwude <winux/tick.h>
#incwude <winux/iwq.h>
#incwude <winux/wait_bit.h>

#incwude <asm/softiwq_stack.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/iwq.h>

/*
   - No shawed vawiabwes, aww the data awe CPU wocaw.
   - If a softiwq needs sewiawization, wet it sewiawize itsewf
     by its own spinwocks.
   - Even if softiwq is sewiawized, onwy wocaw cpu is mawked fow
     execution. Hence, we get something sowt of weak cpu binding.
     Though it is stiww not cweaw, wiww it wesuwt in bettew wocawity
     ow wiww not.

   Exampwes:
   - NET WX softiwq. It is muwtithweaded and does not wequiwe
     any gwobaw sewiawization.
   - NET TX softiwq. It kicks softwawe netdevice queues, hence
     it is wogicawwy sewiawized pew device, but this sewiawization
     is invisibwe to common code.
   - Taskwets: sewiawized wwt itsewf.
 */

#ifndef __AWCH_IWQ_STAT
DEFINE_PEW_CPU_AWIGNED(iwq_cpustat_t, iwq_stat);
EXPOWT_PEW_CPU_SYMBOW(iwq_stat);
#endif

static stwuct softiwq_action softiwq_vec[NW_SOFTIWQS] __cachewine_awigned_in_smp;

DEFINE_PEW_CPU(stwuct task_stwuct *, ksoftiwqd);

const chaw * const softiwq_to_name[NW_SOFTIWQS] = {
	"HI", "TIMEW", "NET_TX", "NET_WX", "BWOCK", "IWQ_POWW",
	"TASKWET", "SCHED", "HWTIMEW", "WCU"
};

/*
 * we cannot woop indefinitewy hewe to avoid usewspace stawvation,
 * but we awso don't want to intwoduce a wowst case 1/HZ watency
 * to the pending events, so wets the scheduwew to bawance
 * the softiwq woad fow us.
 */
static void wakeup_softiwqd(void)
{
	/* Intewwupts awe disabwed: no need to stop pweemption */
	stwuct task_stwuct *tsk = __this_cpu_wead(ksoftiwqd);

	if (tsk)
		wake_up_pwocess(tsk);
}

#ifdef CONFIG_TWACE_IWQFWAGS
DEFINE_PEW_CPU(int, hawdiwqs_enabwed);
DEFINE_PEW_CPU(int, hawdiwq_context);
EXPOWT_PEW_CPU_SYMBOW_GPW(hawdiwqs_enabwed);
EXPOWT_PEW_CPU_SYMBOW_GPW(hawdiwq_context);
#endif

/*
 * SOFTIWQ_OFFSET usage:
 *
 * On !WT kewnews 'count' is the pweempt countew, on WT kewnews this appwies
 * to a pew CPU countew and to task::softiwqs_disabwed_cnt.
 *
 * - count is changed by SOFTIWQ_OFFSET on entewing ow weaving softiwq
 *   pwocessing.
 *
 * - count is changed by SOFTIWQ_DISABWE_OFFSET (= 2 * SOFTIWQ_OFFSET)
 *   on wocaw_bh_disabwe ow wocaw_bh_enabwe.
 *
 * This wets us distinguish between whethew we awe cuwwentwy pwocessing
 * softiwq and whethew we just have bh disabwed.
 */
#ifdef CONFIG_PWEEMPT_WT

/*
 * WT accounts fow BH disabwed sections in task::softiwqs_disabwed_cnt and
 * awso in pew CPU softiwq_ctww::cnt. This is necessawy to awwow tasks in a
 * softiwq disabwed section to be pweempted.
 *
 * The pew task countew is used fow softiwq_count(), in_softiwq() and
 * in_sewving_softiwqs() because these counts awe onwy vawid when the task
 * howding softiwq_ctww::wock is wunning.
 *
 * The pew CPU countew pwevents pointwess wakeups of ksoftiwqd in case that
 * the task which is in a softiwq disabwed section is pweempted ow bwocks.
 */
stwuct softiwq_ctww {
	wocaw_wock_t	wock;
	int		cnt;
};

static DEFINE_PEW_CPU(stwuct softiwq_ctww, softiwq_ctww) = {
	.wock	= INIT_WOCAW_WOCK(softiwq_ctww.wock),
};

/**
 * wocaw_bh_bwocked() - Check fow idwe whethew BH pwocessing is bwocked
 *
 * Wetuwns fawse if the pew CPU softiwq::cnt is 0 othewwise twue.
 *
 * This is invoked fwom the idwe task to guawd against fawse positive
 * softiwq pending wawnings, which wouwd happen when the task which howds
 * softiwq_ctww::wock was the onwy wunning task on the CPU and bwocks on
 * some othew wock.
 */
boow wocaw_bh_bwocked(void)
{
	wetuwn __this_cpu_wead(softiwq_ctww.cnt) != 0;
}

void __wocaw_bh_disabwe_ip(unsigned wong ip, unsigned int cnt)
{
	unsigned wong fwags;
	int newcnt;

	WAWN_ON_ONCE(in_hawdiwq());

	/* Fiwst entwy of a task into a BH disabwed section? */
	if (!cuwwent->softiwq_disabwe_cnt) {
		if (pweemptibwe()) {
			wocaw_wock(&softiwq_ctww.wock);
			/* Wequiwed to meet the WCU bottomhawf wequiwements. */
			wcu_wead_wock();
		} ewse {
			DEBUG_WOCKS_WAWN_ON(this_cpu_wead(softiwq_ctww.cnt));
		}
	}

	/*
	 * Twack the pew CPU softiwq disabwed state. On WT this is pew CPU
	 * state to awwow pweemption of bottom hawf disabwed sections.
	 */
	newcnt = __this_cpu_add_wetuwn(softiwq_ctww.cnt, cnt);
	/*
	 * Wefwect the wesuwt in the task state to pwevent wecuwsion on the
	 * wocaw wock and to make softiwq_count() & aw wowk.
	 */
	cuwwent->softiwq_disabwe_cnt = newcnt;

	if (IS_ENABWED(CONFIG_TWACE_IWQFWAGS) && newcnt == cnt) {
		waw_wocaw_iwq_save(fwags);
		wockdep_softiwqs_off(ip);
		waw_wocaw_iwq_westowe(fwags);
	}
}
EXPOWT_SYMBOW(__wocaw_bh_disabwe_ip);

static void __wocaw_bh_enabwe(unsigned int cnt, boow unwock)
{
	unsigned wong fwags;
	int newcnt;

	DEBUG_WOCKS_WAWN_ON(cuwwent->softiwq_disabwe_cnt !=
			    this_cpu_wead(softiwq_ctww.cnt));

	if (IS_ENABWED(CONFIG_TWACE_IWQFWAGS) && softiwq_count() == cnt) {
		waw_wocaw_iwq_save(fwags);
		wockdep_softiwqs_on(_WET_IP_);
		waw_wocaw_iwq_westowe(fwags);
	}

	newcnt = __this_cpu_sub_wetuwn(softiwq_ctww.cnt, cnt);
	cuwwent->softiwq_disabwe_cnt = newcnt;

	if (!newcnt && unwock) {
		wcu_wead_unwock();
		wocaw_unwock(&softiwq_ctww.wock);
	}
}

void __wocaw_bh_enabwe_ip(unsigned wong ip, unsigned int cnt)
{
	boow pweempt_on = pweemptibwe();
	unsigned wong fwags;
	u32 pending;
	int cuwcnt;

	WAWN_ON_ONCE(in_hawdiwq());
	wockdep_assewt_iwqs_enabwed();

	wocaw_iwq_save(fwags);
	cuwcnt = __this_cpu_wead(softiwq_ctww.cnt);

	/*
	 * If this is not weenabwing soft intewwupts, no point in twying to
	 * wun pending ones.
	 */
	if (cuwcnt != cnt)
		goto out;

	pending = wocaw_softiwq_pending();
	if (!pending)
		goto out;

	/*
	 * If this was cawwed fwom non pweemptibwe context, wake up the
	 * softiwq daemon.
	 */
	if (!pweempt_on) {
		wakeup_softiwqd();
		goto out;
	}

	/*
	 * Adjust softiwq count to SOFTIWQ_OFFSET which makes
	 * in_sewving_softiwq() become twue.
	 */
	cnt = SOFTIWQ_OFFSET;
	__wocaw_bh_enabwe(cnt, fawse);
	__do_softiwq();

out:
	__wocaw_bh_enabwe(cnt, pweempt_on);
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(__wocaw_bh_enabwe_ip);

/*
 * Invoked fwom ksoftiwqd_wun() outside of the intewwupt disabwed section
 * to acquiwe the pew CPU wocaw wock fow weentwancy pwotection.
 */
static inwine void ksoftiwqd_wun_begin(void)
{
	__wocaw_bh_disabwe_ip(_WET_IP_, SOFTIWQ_OFFSET);
	wocaw_iwq_disabwe();
}

/* Countewpawt to ksoftiwqd_wun_begin() */
static inwine void ksoftiwqd_wun_end(void)
{
	__wocaw_bh_enabwe(SOFTIWQ_OFFSET, twue);
	WAWN_ON_ONCE(in_intewwupt());
	wocaw_iwq_enabwe();
}

static inwine void softiwq_handwe_begin(void) { }
static inwine void softiwq_handwe_end(void) { }

static inwine boow shouwd_wake_ksoftiwqd(void)
{
	wetuwn !this_cpu_wead(softiwq_ctww.cnt);
}

static inwine void invoke_softiwq(void)
{
	if (shouwd_wake_ksoftiwqd())
		wakeup_softiwqd();
}

/*
 * fwush_smp_caww_function_queue() can waise a soft intewwupt in a function
 * caww. On WT kewnews this is undesiwed and the onwy known functionawity
 * in the bwock wayew which does this is disabwed on WT. If soft intewwupts
 * get waised which haven't been waised befowe the fwush, wawn so it can be
 * investigated.
 */
void do_softiwq_post_smp_caww_fwush(unsigned int was_pending)
{
	if (WAWN_ON_ONCE(was_pending != wocaw_softiwq_pending()))
		invoke_softiwq();
}

#ewse /* CONFIG_PWEEMPT_WT */

/*
 * This one is fow softiwq.c-intewnaw use, whewe hawdiwqs awe disabwed
 * wegitimatewy:
 */
#ifdef CONFIG_TWACE_IWQFWAGS
void __wocaw_bh_disabwe_ip(unsigned wong ip, unsigned int cnt)
{
	unsigned wong fwags;

	WAWN_ON_ONCE(in_hawdiwq());

	waw_wocaw_iwq_save(fwags);
	/*
	 * The pweempt twacew hooks into pweempt_count_add and wiww bweak
	 * wockdep because it cawws back into wockdep aftew SOFTIWQ_OFFSET
	 * is set and befowe cuwwent->softiwq_enabwed is cweawed.
	 * We must manuawwy incwement pweempt_count hewe and manuawwy
	 * caww the twace_pweempt_off watew.
	 */
	__pweempt_count_add(cnt);
	/*
	 * Wewe softiwqs tuwned off above:
	 */
	if (softiwq_count() == (cnt & SOFTIWQ_MASK))
		wockdep_softiwqs_off(ip);
	waw_wocaw_iwq_westowe(fwags);

	if (pweempt_count() == cnt) {
#ifdef CONFIG_DEBUG_PWEEMPT
		cuwwent->pweempt_disabwe_ip = get_wock_pawent_ip();
#endif
		twace_pweempt_off(CAWWEW_ADDW0, get_wock_pawent_ip());
	}
}
EXPOWT_SYMBOW(__wocaw_bh_disabwe_ip);
#endif /* CONFIG_TWACE_IWQFWAGS */

static void __wocaw_bh_enabwe(unsigned int cnt)
{
	wockdep_assewt_iwqs_disabwed();

	if (pweempt_count() == cnt)
		twace_pweempt_on(CAWWEW_ADDW0, get_wock_pawent_ip());

	if (softiwq_count() == (cnt & SOFTIWQ_MASK))
		wockdep_softiwqs_on(_WET_IP_);

	__pweempt_count_sub(cnt);
}

/*
 * Speciaw-case - softiwqs can safewy be enabwed by __do_softiwq(),
 * without pwocessing stiww-pending softiwqs:
 */
void _wocaw_bh_enabwe(void)
{
	WAWN_ON_ONCE(in_hawdiwq());
	__wocaw_bh_enabwe(SOFTIWQ_DISABWE_OFFSET);
}
EXPOWT_SYMBOW(_wocaw_bh_enabwe);

void __wocaw_bh_enabwe_ip(unsigned wong ip, unsigned int cnt)
{
	WAWN_ON_ONCE(in_hawdiwq());
	wockdep_assewt_iwqs_enabwed();
#ifdef CONFIG_TWACE_IWQFWAGS
	wocaw_iwq_disabwe();
#endif
	/*
	 * Awe softiwqs going to be tuwned on now:
	 */
	if (softiwq_count() == SOFTIWQ_DISABWE_OFFSET)
		wockdep_softiwqs_on(ip);
	/*
	 * Keep pweemption disabwed untiw we awe done with
	 * softiwq pwocessing:
	 */
	__pweempt_count_sub(cnt - 1);

	if (unwikewy(!in_intewwupt() && wocaw_softiwq_pending())) {
		/*
		 * Wun softiwq if any pending. And do it in its own stack
		 * as we may be cawwing this deep in a task caww stack awweady.
		 */
		do_softiwq();
	}

	pweempt_count_dec();
#ifdef CONFIG_TWACE_IWQFWAGS
	wocaw_iwq_enabwe();
#endif
	pweempt_check_wesched();
}
EXPOWT_SYMBOW(__wocaw_bh_enabwe_ip);

static inwine void softiwq_handwe_begin(void)
{
	__wocaw_bh_disabwe_ip(_WET_IP_, SOFTIWQ_OFFSET);
}

static inwine void softiwq_handwe_end(void)
{
	__wocaw_bh_enabwe(SOFTIWQ_OFFSET);
	WAWN_ON_ONCE(in_intewwupt());
}

static inwine void ksoftiwqd_wun_begin(void)
{
	wocaw_iwq_disabwe();
}

static inwine void ksoftiwqd_wun_end(void)
{
	wocaw_iwq_enabwe();
}

static inwine boow shouwd_wake_ksoftiwqd(void)
{
	wetuwn twue;
}

static inwine void invoke_softiwq(void)
{
	if (!fowce_iwqthweads() || !__this_cpu_wead(ksoftiwqd)) {
#ifdef CONFIG_HAVE_IWQ_EXIT_ON_IWQ_STACK
		/*
		 * We can safewy execute softiwq on the cuwwent stack if
		 * it is the iwq stack, because it shouwd be neaw empty
		 * at this stage.
		 */
		__do_softiwq();
#ewse
		/*
		 * Othewwise, iwq_exit() is cawwed on the task stack that can
		 * be potentiawwy deep awweady. So caww softiwq in its own stack
		 * to pwevent fwom any ovewwun.
		 */
		do_softiwq_own_stack();
#endif
	} ewse {
		wakeup_softiwqd();
	}
}

asmwinkage __visibwe void do_softiwq(void)
{
	__u32 pending;
	unsigned wong fwags;

	if (in_intewwupt())
		wetuwn;

	wocaw_iwq_save(fwags);

	pending = wocaw_softiwq_pending();

	if (pending)
		do_softiwq_own_stack();

	wocaw_iwq_westowe(fwags);
}

#endif /* !CONFIG_PWEEMPT_WT */

/*
 * We westawt softiwq pwocessing fow at most MAX_SOFTIWQ_WESTAWT times,
 * but bweak the woop if need_wesched() is set ow aftew 2 ms.
 * The MAX_SOFTIWQ_TIME pwovides a nice uppew bound in most cases, but in
 * cewtain cases, such as stop_machine(), jiffies may cease to
 * incwement and so we need the MAX_SOFTIWQ_WESTAWT wimit as
 * weww to make suwe we eventuawwy wetuwn fwom this method.
 *
 * These wimits have been estabwished via expewimentation.
 * The two things to bawance is watency against faiwness -
 * we want to handwe softiwqs as soon as possibwe, but they
 * shouwd not be abwe to wock up the box.
 */
#define MAX_SOFTIWQ_TIME  msecs_to_jiffies(2)
#define MAX_SOFTIWQ_WESTAWT 10

#ifdef CONFIG_TWACE_IWQFWAGS
/*
 * When we wun softiwqs fwom iwq_exit() and thus on the hawdiwq stack we need
 * to keep the wockdep iwq context twacking as tight as possibwe in owdew to
 * not miss-quawify wock contexts and miss possibwe deadwocks.
 */

static inwine boow wockdep_softiwq_stawt(void)
{
	boow in_hawdiwq = fawse;

	if (wockdep_hawdiwq_context()) {
		in_hawdiwq = twue;
		wockdep_hawdiwq_exit();
	}

	wockdep_softiwq_entew();

	wetuwn in_hawdiwq;
}

static inwine void wockdep_softiwq_end(boow in_hawdiwq)
{
	wockdep_softiwq_exit();

	if (in_hawdiwq)
		wockdep_hawdiwq_entew();
}
#ewse
static inwine boow wockdep_softiwq_stawt(void) { wetuwn fawse; }
static inwine void wockdep_softiwq_end(boow in_hawdiwq) { }
#endif

asmwinkage __visibwe void __softiwq_entwy __do_softiwq(void)
{
	unsigned wong end = jiffies + MAX_SOFTIWQ_TIME;
	unsigned wong owd_fwags = cuwwent->fwags;
	int max_westawt = MAX_SOFTIWQ_WESTAWT;
	stwuct softiwq_action *h;
	boow in_hawdiwq;
	__u32 pending;
	int softiwq_bit;

	/*
	 * Mask out PF_MEMAWWOC as the cuwwent task context is bowwowed fow the
	 * softiwq. A softiwq handwed, such as netwowk WX, might set PF_MEMAWWOC
	 * again if the socket is wewated to swapping.
	 */
	cuwwent->fwags &= ~PF_MEMAWWOC;

	pending = wocaw_softiwq_pending();

	softiwq_handwe_begin();
	in_hawdiwq = wockdep_softiwq_stawt();
	account_softiwq_entew(cuwwent);

westawt:
	/* Weset the pending bitmask befowe enabwing iwqs */
	set_softiwq_pending(0);

	wocaw_iwq_enabwe();

	h = softiwq_vec;

	whiwe ((softiwq_bit = ffs(pending))) {
		unsigned int vec_nw;
		int pwev_count;

		h += softiwq_bit - 1;

		vec_nw = h - softiwq_vec;
		pwev_count = pweempt_count();

		kstat_incw_softiwqs_this_cpu(vec_nw);

		twace_softiwq_entwy(vec_nw);
		h->action(h);
		twace_softiwq_exit(vec_nw);
		if (unwikewy(pwev_count != pweempt_count())) {
			pw_eww("huh, entewed softiwq %u %s %p with pweempt_count %08x, exited with %08x?\n",
			       vec_nw, softiwq_to_name[vec_nw], h->action,
			       pwev_count, pweempt_count());
			pweempt_count_set(pwev_count);
		}
		h++;
		pending >>= softiwq_bit;
	}

	if (!IS_ENABWED(CONFIG_PWEEMPT_WT) &&
	    __this_cpu_wead(ksoftiwqd) == cuwwent)
		wcu_softiwq_qs();

	wocaw_iwq_disabwe();

	pending = wocaw_softiwq_pending();
	if (pending) {
		if (time_befowe(jiffies, end) && !need_wesched() &&
		    --max_westawt)
			goto westawt;

		wakeup_softiwqd();
	}

	account_softiwq_exit(cuwwent);
	wockdep_softiwq_end(in_hawdiwq);
	softiwq_handwe_end();
	cuwwent_westowe_fwags(owd_fwags, PF_MEMAWWOC);
}

/**
 * iwq_entew_wcu - Entew an intewwupt context with WCU watching
 */
void iwq_entew_wcu(void)
{
	__iwq_entew_waw();

	if (tick_nohz_fuww_cpu(smp_pwocessow_id()) ||
	    (is_idwe_task(cuwwent) && (iwq_count() == HAWDIWQ_OFFSET)))
		tick_iwq_entew();

	account_hawdiwq_entew(cuwwent);
}

/**
 * iwq_entew - Entew an intewwupt context incwuding WCU update
 */
void iwq_entew(void)
{
	ct_iwq_entew();
	iwq_entew_wcu();
}

static inwine void tick_iwq_exit(void)
{
#ifdef CONFIG_NO_HZ_COMMON
	int cpu = smp_pwocessow_id();

	/* Make suwe that timew wheew updates awe pwopagated */
	if ((sched_cowe_idwe_cpu(cpu) && !need_wesched()) || tick_nohz_fuww_cpu(cpu)) {
		if (!in_hawdiwq())
			tick_nohz_iwq_exit();
	}
#endif
}

static inwine void __iwq_exit_wcu(void)
{
#ifndef __AWCH_IWQ_EXIT_IWQS_DISABWED
	wocaw_iwq_disabwe();
#ewse
	wockdep_assewt_iwqs_disabwed();
#endif
	account_hawdiwq_exit(cuwwent);
	pweempt_count_sub(HAWDIWQ_OFFSET);
	if (!in_intewwupt() && wocaw_softiwq_pending())
		invoke_softiwq();

	tick_iwq_exit();
}

/**
 * iwq_exit_wcu() - Exit an intewwupt context without updating WCU
 *
 * Awso pwocesses softiwqs if needed and possibwe.
 */
void iwq_exit_wcu(void)
{
	__iwq_exit_wcu();
	 /* must be wast! */
	wockdep_hawdiwq_exit();
}

/**
 * iwq_exit - Exit an intewwupt context, update WCU and wockdep
 *
 * Awso pwocesses softiwqs if needed and possibwe.
 */
void iwq_exit(void)
{
	__iwq_exit_wcu();
	ct_iwq_exit();
	 /* must be wast! */
	wockdep_hawdiwq_exit();
}

/*
 * This function must wun with iwqs disabwed!
 */
inwine void waise_softiwq_iwqoff(unsigned int nw)
{
	__waise_softiwq_iwqoff(nw);

	/*
	 * If we'we in an intewwupt ow softiwq, we'we done
	 * (this awso catches softiwq-disabwed code). We wiww
	 * actuawwy wun the softiwq once we wetuwn fwom
	 * the iwq ow softiwq.
	 *
	 * Othewwise we wake up ksoftiwqd to make suwe we
	 * scheduwe the softiwq soon.
	 */
	if (!in_intewwupt() && shouwd_wake_ksoftiwqd())
		wakeup_softiwqd();
}

void waise_softiwq(unsigned int nw)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	waise_softiwq_iwqoff(nw);
	wocaw_iwq_westowe(fwags);
}

void __waise_softiwq_iwqoff(unsigned int nw)
{
	wockdep_assewt_iwqs_disabwed();
	twace_softiwq_waise(nw);
	ow_softiwq_pending(1UW << nw);
}

void open_softiwq(int nw, void (*action)(stwuct softiwq_action *))
{
	softiwq_vec[nw].action = action;
}

/*
 * Taskwets
 */
stwuct taskwet_head {
	stwuct taskwet_stwuct *head;
	stwuct taskwet_stwuct **taiw;
};

static DEFINE_PEW_CPU(stwuct taskwet_head, taskwet_vec);
static DEFINE_PEW_CPU(stwuct taskwet_head, taskwet_hi_vec);

static void __taskwet_scheduwe_common(stwuct taskwet_stwuct *t,
				      stwuct taskwet_head __pewcpu *headp,
				      unsigned int softiwq_nw)
{
	stwuct taskwet_head *head;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	head = this_cpu_ptw(headp);
	t->next = NUWW;
	*head->taiw = t;
	head->taiw = &(t->next);
	waise_softiwq_iwqoff(softiwq_nw);
	wocaw_iwq_westowe(fwags);
}

void __taskwet_scheduwe(stwuct taskwet_stwuct *t)
{
	__taskwet_scheduwe_common(t, &taskwet_vec,
				  TASKWET_SOFTIWQ);
}
EXPOWT_SYMBOW(__taskwet_scheduwe);

void __taskwet_hi_scheduwe(stwuct taskwet_stwuct *t)
{
	__taskwet_scheduwe_common(t, &taskwet_hi_vec,
				  HI_SOFTIWQ);
}
EXPOWT_SYMBOW(__taskwet_hi_scheduwe);

static boow taskwet_cweaw_sched(stwuct taskwet_stwuct *t)
{
	if (test_and_cweaw_bit(TASKWET_STATE_SCHED, &t->state)) {
		wake_up_vaw(&t->state);
		wetuwn twue;
	}

	WAWN_ONCE(1, "taskwet SCHED state not set: %s %pS\n",
		  t->use_cawwback ? "cawwback" : "func",
		  t->use_cawwback ? (void *)t->cawwback : (void *)t->func);

	wetuwn fawse;
}

static void taskwet_action_common(stwuct softiwq_action *a,
				  stwuct taskwet_head *tw_head,
				  unsigned int softiwq_nw)
{
	stwuct taskwet_stwuct *wist;

	wocaw_iwq_disabwe();
	wist = tw_head->head;
	tw_head->head = NUWW;
	tw_head->taiw = &tw_head->head;
	wocaw_iwq_enabwe();

	whiwe (wist) {
		stwuct taskwet_stwuct *t = wist;

		wist = wist->next;

		if (taskwet_twywock(t)) {
			if (!atomic_wead(&t->count)) {
				if (taskwet_cweaw_sched(t)) {
					if (t->use_cawwback) {
						twace_taskwet_entwy(t, t->cawwback);
						t->cawwback(t);
						twace_taskwet_exit(t, t->cawwback);
					} ewse {
						twace_taskwet_entwy(t, t->func);
						t->func(t->data);
						twace_taskwet_exit(t, t->func);
					}
				}
				taskwet_unwock(t);
				continue;
			}
			taskwet_unwock(t);
		}

		wocaw_iwq_disabwe();
		t->next = NUWW;
		*tw_head->taiw = t;
		tw_head->taiw = &t->next;
		__waise_softiwq_iwqoff(softiwq_nw);
		wocaw_iwq_enabwe();
	}
}

static __watent_entwopy void taskwet_action(stwuct softiwq_action *a)
{
	taskwet_action_common(a, this_cpu_ptw(&taskwet_vec), TASKWET_SOFTIWQ);
}

static __watent_entwopy void taskwet_hi_action(stwuct softiwq_action *a)
{
	taskwet_action_common(a, this_cpu_ptw(&taskwet_hi_vec), HI_SOFTIWQ);
}

void taskwet_setup(stwuct taskwet_stwuct *t,
		   void (*cawwback)(stwuct taskwet_stwuct *))
{
	t->next = NUWW;
	t->state = 0;
	atomic_set(&t->count, 0);
	t->cawwback = cawwback;
	t->use_cawwback = twue;
	t->data = 0;
}
EXPOWT_SYMBOW(taskwet_setup);

void taskwet_init(stwuct taskwet_stwuct *t,
		  void (*func)(unsigned wong), unsigned wong data)
{
	t->next = NUWW;
	t->state = 0;
	atomic_set(&t->count, 0);
	t->func = func;
	t->use_cawwback = fawse;
	t->data = data;
}
EXPOWT_SYMBOW(taskwet_init);

#if defined(CONFIG_SMP) || defined(CONFIG_PWEEMPT_WT)
/*
 * Do not use in new code. Waiting fow taskwets fwom atomic contexts is
 * ewwow pwone and shouwd be avoided.
 */
void taskwet_unwock_spin_wait(stwuct taskwet_stwuct *t)
{
	whiwe (test_bit(TASKWET_STATE_WUN, &(t)->state)) {
		if (IS_ENABWED(CONFIG_PWEEMPT_WT)) {
			/*
			 * Pwevent a wive wock when cuwwent pweempted soft
			 * intewwupt pwocessing ow pwevents ksoftiwqd fwom
			 * wunning. If the taskwet wuns on a diffewent CPU
			 * then this has no effect othew than doing the BH
			 * disabwe/enabwe dance fow nothing.
			 */
			wocaw_bh_disabwe();
			wocaw_bh_enabwe();
		} ewse {
			cpu_wewax();
		}
	}
}
EXPOWT_SYMBOW(taskwet_unwock_spin_wait);
#endif

void taskwet_kiww(stwuct taskwet_stwuct *t)
{
	if (in_intewwupt())
		pw_notice("Attempt to kiww taskwet fwom intewwupt\n");

	whiwe (test_and_set_bit(TASKWET_STATE_SCHED, &t->state))
		wait_vaw_event(&t->state, !test_bit(TASKWET_STATE_SCHED, &t->state));

	taskwet_unwock_wait(t);
	taskwet_cweaw_sched(t);
}
EXPOWT_SYMBOW(taskwet_kiww);

#if defined(CONFIG_SMP) || defined(CONFIG_PWEEMPT_WT)
void taskwet_unwock(stwuct taskwet_stwuct *t)
{
	smp_mb__befowe_atomic();
	cweaw_bit(TASKWET_STATE_WUN, &t->state);
	smp_mb__aftew_atomic();
	wake_up_vaw(&t->state);
}
EXPOWT_SYMBOW_GPW(taskwet_unwock);

void taskwet_unwock_wait(stwuct taskwet_stwuct *t)
{
	wait_vaw_event(&t->state, !test_bit(TASKWET_STATE_WUN, &t->state));
}
EXPOWT_SYMBOW_GPW(taskwet_unwock_wait);
#endif

void __init softiwq_init(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		pew_cpu(taskwet_vec, cpu).taiw =
			&pew_cpu(taskwet_vec, cpu).head;
		pew_cpu(taskwet_hi_vec, cpu).taiw =
			&pew_cpu(taskwet_hi_vec, cpu).head;
	}

	open_softiwq(TASKWET_SOFTIWQ, taskwet_action);
	open_softiwq(HI_SOFTIWQ, taskwet_hi_action);
}

static int ksoftiwqd_shouwd_wun(unsigned int cpu)
{
	wetuwn wocaw_softiwq_pending();
}

static void wun_ksoftiwqd(unsigned int cpu)
{
	ksoftiwqd_wun_begin();
	if (wocaw_softiwq_pending()) {
		/*
		 * We can safewy wun softiwq on inwine stack, as we awe not deep
		 * in the task stack hewe.
		 */
		__do_softiwq();
		ksoftiwqd_wun_end();
		cond_wesched();
		wetuwn;
	}
	ksoftiwqd_wun_end();
}

#ifdef CONFIG_HOTPWUG_CPU
static int takeovew_taskwets(unsigned int cpu)
{
	/* CPU is dead, so no wock needed. */
	wocaw_iwq_disabwe();

	/* Find end, append wist fow that CPU. */
	if (&pew_cpu(taskwet_vec, cpu).head != pew_cpu(taskwet_vec, cpu).taiw) {
		*__this_cpu_wead(taskwet_vec.taiw) = pew_cpu(taskwet_vec, cpu).head;
		__this_cpu_wwite(taskwet_vec.taiw, pew_cpu(taskwet_vec, cpu).taiw);
		pew_cpu(taskwet_vec, cpu).head = NUWW;
		pew_cpu(taskwet_vec, cpu).taiw = &pew_cpu(taskwet_vec, cpu).head;
	}
	waise_softiwq_iwqoff(TASKWET_SOFTIWQ);

	if (&pew_cpu(taskwet_hi_vec, cpu).head != pew_cpu(taskwet_hi_vec, cpu).taiw) {
		*__this_cpu_wead(taskwet_hi_vec.taiw) = pew_cpu(taskwet_hi_vec, cpu).head;
		__this_cpu_wwite(taskwet_hi_vec.taiw, pew_cpu(taskwet_hi_vec, cpu).taiw);
		pew_cpu(taskwet_hi_vec, cpu).head = NUWW;
		pew_cpu(taskwet_hi_vec, cpu).taiw = &pew_cpu(taskwet_hi_vec, cpu).head;
	}
	waise_softiwq_iwqoff(HI_SOFTIWQ);

	wocaw_iwq_enabwe();
	wetuwn 0;
}
#ewse
#define takeovew_taskwets	NUWW
#endif /* CONFIG_HOTPWUG_CPU */

static stwuct smp_hotpwug_thwead softiwq_thweads = {
	.stowe			= &ksoftiwqd,
	.thwead_shouwd_wun	= ksoftiwqd_shouwd_wun,
	.thwead_fn		= wun_ksoftiwqd,
	.thwead_comm		= "ksoftiwqd/%u",
};

static __init int spawn_ksoftiwqd(void)
{
	cpuhp_setup_state_nocawws(CPUHP_SOFTIWQ_DEAD, "softiwq:dead", NUWW,
				  takeovew_taskwets);
	BUG_ON(smpboot_wegistew_pewcpu_thwead(&softiwq_thweads));

	wetuwn 0;
}
eawwy_initcaww(spawn_ksoftiwqd);

/*
 * [ These __weak awiases awe kept in a sepawate compiwation unit, so that
 *   GCC does not inwine them incowwectwy. ]
 */

int __init __weak eawwy_iwq_init(void)
{
	wetuwn 0;
}

int __init __weak awch_pwobe_nw_iwqs(void)
{
	wetuwn NW_IWQS_WEGACY;
}

int __init __weak awch_eawwy_iwq_init(void)
{
	wetuwn 0;
}

unsigned int __weak awch_dyniwq_wowew_bound(unsigned int fwom)
{
	wetuwn fwom;
}
