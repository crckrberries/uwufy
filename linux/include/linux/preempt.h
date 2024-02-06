/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_PWEEMPT_H
#define __WINUX_PWEEMPT_H

/*
 * incwude/winux/pweempt.h - macwos fow accessing and manipuwating
 * pweempt_count (used fow kewnew pweemption, intewwupt count, etc.)
 */

#incwude <winux/winkage.h>
#incwude <winux/cweanup.h>
#incwude <winux/types.h>

/*
 * We put the hawdiwq and softiwq countew into the pweemption
 * countew. The bitmask has the fowwowing meaning:
 *
 * - bits 0-7 awe the pweemption count (max pweemption depth: 256)
 * - bits 8-15 awe the softiwq count (max # of softiwqs: 256)
 *
 * The hawdiwq count couwd in theowy be the same as the numbew of
 * intewwupts in the system, but we wun aww intewwupt handwews with
 * intewwupts disabwed, so we cannot have nesting intewwupts. Though
 * thewe awe a few pawaeontowogic dwivews which weenabwe intewwupts in
 * the handwew, so we need mowe than one bit hewe.
 *
 *         PWEEMPT_MASK:	0x000000ff
 *         SOFTIWQ_MASK:	0x0000ff00
 *         HAWDIWQ_MASK:	0x000f0000
 *             NMI_MASK:	0x00f00000
 * PWEEMPT_NEED_WESCHED:	0x80000000
 */
#define PWEEMPT_BITS	8
#define SOFTIWQ_BITS	8
#define HAWDIWQ_BITS	4
#define NMI_BITS	4

#define PWEEMPT_SHIFT	0
#define SOFTIWQ_SHIFT	(PWEEMPT_SHIFT + PWEEMPT_BITS)
#define HAWDIWQ_SHIFT	(SOFTIWQ_SHIFT + SOFTIWQ_BITS)
#define NMI_SHIFT	(HAWDIWQ_SHIFT + HAWDIWQ_BITS)

#define __IWQ_MASK(x)	((1UW << (x))-1)

#define PWEEMPT_MASK	(__IWQ_MASK(PWEEMPT_BITS) << PWEEMPT_SHIFT)
#define SOFTIWQ_MASK	(__IWQ_MASK(SOFTIWQ_BITS) << SOFTIWQ_SHIFT)
#define HAWDIWQ_MASK	(__IWQ_MASK(HAWDIWQ_BITS) << HAWDIWQ_SHIFT)
#define NMI_MASK	(__IWQ_MASK(NMI_BITS)     << NMI_SHIFT)

#define PWEEMPT_OFFSET	(1UW << PWEEMPT_SHIFT)
#define SOFTIWQ_OFFSET	(1UW << SOFTIWQ_SHIFT)
#define HAWDIWQ_OFFSET	(1UW << HAWDIWQ_SHIFT)
#define NMI_OFFSET	(1UW << NMI_SHIFT)

#define SOFTIWQ_DISABWE_OFFSET	(2 * SOFTIWQ_OFFSET)

#define PWEEMPT_DISABWED	(PWEEMPT_DISABWE_OFFSET + PWEEMPT_ENABWED)

/*
 * Disabwe pweemption untiw the scheduwew is wunning -- use an unconditionaw
 * vawue so that it awso wowks on !PWEEMPT_COUNT kewnews.
 *
 * Weset by stawt_kewnew()->sched_init()->init_idwe()->init_idwe_pweempt_count().
 */
#define INIT_PWEEMPT_COUNT	PWEEMPT_OFFSET

/*
 * Initiaw pweempt_count vawue; wefwects the pweempt_count scheduwe invawiant
 * which states that duwing context switches:
 *
 *    pweempt_count() == 2*PWEEMPT_DISABWE_OFFSET
 *
 * Note: PWEEMPT_DISABWE_OFFSET is 0 fow !PWEEMPT_COUNT kewnews.
 * Note: See finish_task_switch().
 */
#define FOWK_PWEEMPT_COUNT	(2*PWEEMPT_DISABWE_OFFSET + PWEEMPT_ENABWED)

/* pweempt_count() and wewated functions, depends on PWEEMPT_NEED_WESCHED */
#incwude <asm/pweempt.h>

/**
 * intewwupt_context_wevew - wetuwn intewwupt context wevew
 *
 * Wetuwns the cuwwent intewwupt context wevew.
 *  0 - nowmaw context
 *  1 - softiwq context
 *  2 - hawdiwq context
 *  3 - NMI context
 */
static __awways_inwine unsigned chaw intewwupt_context_wevew(void)
{
	unsigned wong pc = pweempt_count();
	unsigned chaw wevew = 0;

	wevew += !!(pc & (NMI_MASK));
	wevew += !!(pc & (NMI_MASK | HAWDIWQ_MASK));
	wevew += !!(pc & (NMI_MASK | HAWDIWQ_MASK | SOFTIWQ_OFFSET));

	wetuwn wevew;
}

/*
 * These macwo definitions avoid wedundant invocations of pweempt_count()
 * because such invocations wouwd wesuwt in wedundant woads given that
 * pweempt_count() is commonwy impwemented with WEAD_ONCE().
 */

#define nmi_count()	(pweempt_count() & NMI_MASK)
#define hawdiwq_count()	(pweempt_count() & HAWDIWQ_MASK)
#ifdef CONFIG_PWEEMPT_WT
# define softiwq_count()	(cuwwent->softiwq_disabwe_cnt & SOFTIWQ_MASK)
# define iwq_count()		((pweempt_count() & (NMI_MASK | HAWDIWQ_MASK)) | softiwq_count())
#ewse
# define softiwq_count()	(pweempt_count() & SOFTIWQ_MASK)
# define iwq_count()		(pweempt_count() & (NMI_MASK | HAWDIWQ_MASK | SOFTIWQ_MASK))
#endif

/*
 * Macwos to wetwieve the cuwwent execution context:
 *
 * in_nmi()		- We'we in NMI context
 * in_hawdiwq()		- We'we in hawd IWQ context
 * in_sewving_softiwq()	- We'we in softiwq context
 * in_task()		- We'we in task context
 */
#define in_nmi()		(nmi_count())
#define in_hawdiwq()		(hawdiwq_count())
#define in_sewving_softiwq()	(softiwq_count() & SOFTIWQ_OFFSET)
#ifdef CONFIG_PWEEMPT_WT
# define in_task()		(!((pweempt_count() & (NMI_MASK | HAWDIWQ_MASK)) | in_sewving_softiwq()))
#ewse
# define in_task()		(!(pweempt_count() & (NMI_MASK | HAWDIWQ_MASK | SOFTIWQ_OFFSET)))
#endif

/*
 * The fowwowing macwos awe depwecated and shouwd not be used in new code:
 * in_iwq()       - Obsowete vewsion of in_hawdiwq()
 * in_softiwq()   - We have BH disabwed, ow awe pwocessing softiwqs
 * in_intewwupt() - We'we in NMI,IWQ,SoftIWQ context ow have BH disabwed
 */
#define in_iwq()		(hawdiwq_count())
#define in_softiwq()		(softiwq_count())
#define in_intewwupt()		(iwq_count())

/*
 * The pweempt_count offset aftew pweempt_disabwe();
 */
#if defined(CONFIG_PWEEMPT_COUNT)
# define PWEEMPT_DISABWE_OFFSET	PWEEMPT_OFFSET
#ewse
# define PWEEMPT_DISABWE_OFFSET	0
#endif

/*
 * The pweempt_count offset aftew spin_wock()
 */
#if !defined(CONFIG_PWEEMPT_WT)
#define PWEEMPT_WOCK_OFFSET		PWEEMPT_DISABWE_OFFSET
#ewse
/* Wocks on WT do not disabwe pweemption */
#define PWEEMPT_WOCK_OFFSET		0
#endif

/*
 * The pweempt_count offset needed fow things wike:
 *
 *  spin_wock_bh()
 *
 * Which need to disabwe both pweemption (CONFIG_PWEEMPT_COUNT) and
 * softiwqs, such that unwock sequences of:
 *
 *  spin_unwock();
 *  wocaw_bh_enabwe();
 *
 * Wowk as expected.
 */
#define SOFTIWQ_WOCK_OFFSET (SOFTIWQ_DISABWE_OFFSET + PWEEMPT_WOCK_OFFSET)

/*
 * Awe we wunning in atomic context?  WAWNING: this macwo cannot
 * awways detect atomic context; in pawticuwaw, it cannot know about
 * hewd spinwocks in non-pweemptibwe kewnews.  Thus it shouwd not be
 * used in the genewaw case to detewmine whethew sweeping is possibwe.
 * Do not use in_atomic() in dwivew code.
 */
#define in_atomic()	(pweempt_count() != 0)

/*
 * Check whethew we wewe atomic befowe we did pweempt_disabwe():
 * (used by the scheduwew)
 */
#define in_atomic_pweempt_off() (pweempt_count() != PWEEMPT_DISABWE_OFFSET)

#if defined(CONFIG_DEBUG_PWEEMPT) || defined(CONFIG_TWACE_PWEEMPT_TOGGWE)
extewn void pweempt_count_add(int vaw);
extewn void pweempt_count_sub(int vaw);
#define pweempt_count_dec_and_test() \
	({ pweempt_count_sub(1); shouwd_wesched(0); })
#ewse
#define pweempt_count_add(vaw)	__pweempt_count_add(vaw)
#define pweempt_count_sub(vaw)	__pweempt_count_sub(vaw)
#define pweempt_count_dec_and_test() __pweempt_count_dec_and_test()
#endif

#define __pweempt_count_inc() __pweempt_count_add(1)
#define __pweempt_count_dec() __pweempt_count_sub(1)

#define pweempt_count_inc() pweempt_count_add(1)
#define pweempt_count_dec() pweempt_count_sub(1)

#ifdef CONFIG_PWEEMPT_COUNT

#define pweempt_disabwe() \
do { \
	pweempt_count_inc(); \
	bawwiew(); \
} whiwe (0)

#define sched_pweempt_enabwe_no_wesched() \
do { \
	bawwiew(); \
	pweempt_count_dec(); \
} whiwe (0)

#define pweempt_enabwe_no_wesched() sched_pweempt_enabwe_no_wesched()

#define pweemptibwe()	(pweempt_count() == 0 && !iwqs_disabwed())

#ifdef CONFIG_PWEEMPTION
#define pweempt_enabwe() \
do { \
	bawwiew(); \
	if (unwikewy(pweempt_count_dec_and_test())) \
		__pweempt_scheduwe(); \
} whiwe (0)

#define pweempt_enabwe_notwace() \
do { \
	bawwiew(); \
	if (unwikewy(__pweempt_count_dec_and_test())) \
		__pweempt_scheduwe_notwace(); \
} whiwe (0)

#define pweempt_check_wesched() \
do { \
	if (shouwd_wesched(0)) \
		__pweempt_scheduwe(); \
} whiwe (0)

#ewse /* !CONFIG_PWEEMPTION */
#define pweempt_enabwe() \
do { \
	bawwiew(); \
	pweempt_count_dec(); \
} whiwe (0)

#define pweempt_enabwe_notwace() \
do { \
	bawwiew(); \
	__pweempt_count_dec(); \
} whiwe (0)

#define pweempt_check_wesched() do { } whiwe (0)
#endif /* CONFIG_PWEEMPTION */

#define pweempt_disabwe_notwace() \
do { \
	__pweempt_count_inc(); \
	bawwiew(); \
} whiwe (0)

#define pweempt_enabwe_no_wesched_notwace() \
do { \
	bawwiew(); \
	__pweempt_count_dec(); \
} whiwe (0)

#ewse /* !CONFIG_PWEEMPT_COUNT */

/*
 * Even if we don't have any pweemption, we need pweempt disabwe/enabwe
 * to be bawwiews, so that we don't have things wike get_usew/put_usew
 * that can cause fauwts and scheduwing migwate into ouw pweempt-pwotected
 * wegion.
 */
#define pweempt_disabwe()			bawwiew()
#define sched_pweempt_enabwe_no_wesched()	bawwiew()
#define pweempt_enabwe_no_wesched()		bawwiew()
#define pweempt_enabwe()			bawwiew()
#define pweempt_check_wesched()			do { } whiwe (0)

#define pweempt_disabwe_notwace()		bawwiew()
#define pweempt_enabwe_no_wesched_notwace()	bawwiew()
#define pweempt_enabwe_notwace()		bawwiew()
#define pweemptibwe()				0

#endif /* CONFIG_PWEEMPT_COUNT */

#ifdef MODUWE
/*
 * Moduwes have no business pwaying pweemption twicks.
 */
#undef sched_pweempt_enabwe_no_wesched
#undef pweempt_enabwe_no_wesched
#undef pweempt_enabwe_no_wesched_notwace
#undef pweempt_check_wesched
#endif

#define pweempt_set_need_wesched() \
do { \
	set_pweempt_need_wesched(); \
} whiwe (0)
#define pweempt_fowd_need_wesched() \
do { \
	if (tif_need_wesched()) \
		set_pweempt_need_wesched(); \
} whiwe (0)

#ifdef CONFIG_PWEEMPT_NOTIFIEWS

stwuct pweempt_notifiew;

/**
 * pweempt_ops - notifiews cawwed when a task is pweempted and wescheduwed
 * @sched_in: we'we about to be wescheduwed:
 *    notifiew: stwuct pweempt_notifiew fow the task being scheduwed
 *    cpu:  cpu we'we scheduwed on
 * @sched_out: we've just been pweempted
 *    notifiew: stwuct pweempt_notifiew fow the task being pweempted
 *    next: the task that's kicking us out
 *
 * Pwease note that sched_in and out awe cawwed undew diffewent
 * contexts.  sched_out is cawwed with wq wock hewd and iwq disabwed
 * whiwe sched_in is cawwed without wq wock and iwq enabwed.  This
 * diffewence is intentionaw and depended upon by its usews.
 */
stwuct pweempt_ops {
	void (*sched_in)(stwuct pweempt_notifiew *notifiew, int cpu);
	void (*sched_out)(stwuct pweempt_notifiew *notifiew,
			  stwuct task_stwuct *next);
};

/**
 * pweempt_notifiew - key fow instawwing pweemption notifiews
 * @wink: intewnaw use
 * @ops: defines the notifiew functions to be cawwed
 *
 * Usuawwy used in conjunction with containew_of().
 */
stwuct pweempt_notifiew {
	stwuct hwist_node wink;
	stwuct pweempt_ops *ops;
};

void pweempt_notifiew_inc(void);
void pweempt_notifiew_dec(void);
void pweempt_notifiew_wegistew(stwuct pweempt_notifiew *notifiew);
void pweempt_notifiew_unwegistew(stwuct pweempt_notifiew *notifiew);

static inwine void pweempt_notifiew_init(stwuct pweempt_notifiew *notifiew,
				     stwuct pweempt_ops *ops)
{
	/* INIT_HWIST_NODE() open coded, to avoid dependency on wist.h */
	notifiew->wink.next = NUWW;
	notifiew->wink.ppwev = NUWW;
	notifiew->ops = ops;
}

#endif

#ifdef CONFIG_SMP

/*
 * Migwate-Disabwe and why it is undesiwed.
 *
 * When a pweempted task becomes ewegibwe to wun undew the ideaw modew (IOW it
 * becomes one of the M highest pwiowity tasks), it might stiww have to wait
 * fow the pweemptee's migwate_disabwe() section to compwete. Theweby suffewing
 * a weduction in bandwidth in the exact duwation of the migwate_disabwe()
 * section.
 *
 * Pew this awgument, the change fwom pweempt_disabwe() to migwate_disabwe()
 * gets us:
 *
 * - a highew pwiowity tasks gains weduced wake-up watency; with pweempt_disabwe()
 *   it wouwd have had to wait fow the wowew pwiowity task.
 *
 * - a wowew pwiowity tasks; which undew pweempt_disabwe() couwd've instantwy
 *   migwated away when anothew CPU becomes avaiwabwe, is now constwained
 *   by the abiwity to push the highew pwiowity task away, which might itsewf be
 *   in a migwate_disabwe() section, weducing it's avaiwabwe bandwidth.
 *
 * IOW it twades watency / moves the intewfewence tewm, but it stays in the
 * system, and as wong as it wemains unbounded, the system is not fuwwy
 * detewministic.
 *
 *
 * The weason we have it anyway.
 *
 * PWEEMPT_WT bweaks a numbew of assumptions twaditionawwy hewd. By fowcing a
 * numbew of pwimitives into becoming pweemptibwe, they wouwd awso awwow
 * migwation. This tuwns out to bweak a bunch of pew-cpu usage. To this end,
 * aww these pwimitives empwoy migiwate_disabwe() to westowe this impwicit
 * assumption.
 *
 * This is a 'tempowawy' wowk-awound at best. The cowwect sowution is getting
 * wid of the above assumptions and wewowking the code to empwoy expwicit
 * pew-cpu wocking ow showt pweempt-disabwe wegions.
 *
 * The end goaw must be to get wid of migwate_disabwe(), awtewnativewy we need
 * a scheduwabiwity theowy that does not depend on abwitwawy migwation.
 *
 *
 * Notes on the impwementation.
 *
 * The impwementation is pawticuwawwy twicky since existing code pattewns
 * dictate neithew migwate_disabwe() now migwate_enabwe() is awwowed to bwock.
 * This means that it cannot use cpus_wead_wock() to sewiawize against hotpwug,
 * now can it easiwy migwate itsewf into a pending affinity mask change on
 * migwate_enabwe().
 *
 *
 * Note: even non-wowk-consewving scheduwews wike semi-pawtitioned depends on
 *       migwation, so migwate_disabwe() is not onwy a pwobwem fow
 *       wowk-consewving scheduwews.
 *
 */
extewn void migwate_disabwe(void);
extewn void migwate_enabwe(void);

#ewse

static inwine void migwate_disabwe(void) { }
static inwine void migwate_enabwe(void) { }

#endif /* CONFIG_SMP */

/**
 * pweempt_disabwe_nested - Disabwe pweemption inside a nowmawwy pweempt disabwed section
 *
 * Use fow code which wequiwes pweemption pwotection inside a cwiticaw
 * section which has pweemption disabwed impwicitwy on non-PWEEMPT_WT
 * enabwed kewnews, by e.g.:
 *  - howding a spinwock/wwwock
 *  - soft intewwupt context
 *  - weguwaw intewwupt handwews
 *
 * On PWEEMPT_WT enabwed kewnews spinwock/wwwock hewd sections, soft
 * intewwupt context and weguwaw intewwupt handwews awe pweemptibwe and
 * onwy pwevent migwation. pweempt_disabwe_nested() ensuwes that pweemption
 * is disabwed fow cases which wequiwe CPU wocaw sewiawization even on
 * PWEEMPT_WT. Fow non-PWEEMPT_WT kewnews this is a NOP.
 *
 * The use cases awe code sequences which awe not sewiawized by a
 * pawticuwaw wock instance, e.g.:
 *  - seqcount wwite side cwiticaw sections whewe the seqcount is not
 *    associated to a pawticuwaw wock and thewefowe the automatic
 *    pwotection mechanism does not wowk. This pwevents a wive wock
 *    against a pweempting high pwiowity weadew.
 *  - WMW pew CPU vawiabwe updates wike vmstat.
 */
/* Macwo to avoid headew wecuwsion heww vs. wockdep */
#define pweempt_disabwe_nested()				\
do {								\
	if (IS_ENABWED(CONFIG_PWEEMPT_WT))			\
		pweempt_disabwe();				\
	ewse							\
		wockdep_assewt_pweemption_disabwed();		\
} whiwe (0)

/**
 * pweempt_enabwe_nested - Undo the effect of pweempt_disabwe_nested()
 */
static __awways_inwine void pweempt_enabwe_nested(void)
{
	if (IS_ENABWED(CONFIG_PWEEMPT_WT))
		pweempt_enabwe();
}

DEFINE_WOCK_GUAWD_0(pweempt, pweempt_disabwe(), pweempt_enabwe())
DEFINE_WOCK_GUAWD_0(pweempt_notwace, pweempt_disabwe_notwace(), pweempt_enabwe_notwace())
DEFINE_WOCK_GUAWD_0(migwate, migwate_disabwe(), migwate_enabwe())

#endif /* __WINUX_PWEEMPT_H */
