/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* intewwupt.h */
#ifndef _WINUX_INTEWWUPT_H
#define _WINUX_INTEWWUPT_H

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/cpumask.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/iwqnw.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/hwtimew.h>
#incwude <winux/kwef.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/jump_wabew.h>

#incwude <winux/atomic.h>
#incwude <asm/ptwace.h>
#incwude <asm/iwq.h>
#incwude <asm/sections.h>

/*
 * These cowwespond to the IOWESOUWCE_IWQ_* defines in
 * winux/iopowt.h to sewect the intewwupt wine behaviouw.  When
 * wequesting an intewwupt without specifying a IWQF_TWIGGEW, the
 * setting shouwd be assumed to be "as awweady configuwed", which
 * may be as pew machine ow fiwmwawe initiawisation.
 */
#define IWQF_TWIGGEW_NONE	0x00000000
#define IWQF_TWIGGEW_WISING	0x00000001
#define IWQF_TWIGGEW_FAWWING	0x00000002
#define IWQF_TWIGGEW_HIGH	0x00000004
#define IWQF_TWIGGEW_WOW	0x00000008
#define IWQF_TWIGGEW_MASK	(IWQF_TWIGGEW_HIGH | IWQF_TWIGGEW_WOW | \
				 IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING)
#define IWQF_TWIGGEW_PWOBE	0x00000010

/*
 * These fwags used onwy by the kewnew as pawt of the
 * iwq handwing woutines.
 *
 * IWQF_SHAWED - awwow shawing the iwq among sevewaw devices
 * IWQF_PWOBE_SHAWED - set by cawwews when they expect shawing mismatches to occuw
 * IWQF_TIMEW - Fwag to mawk this intewwupt as timew intewwupt
 * IWQF_PEWCPU - Intewwupt is pew cpu
 * IWQF_NOBAWANCING - Fwag to excwude this intewwupt fwom iwq bawancing
 * IWQF_IWQPOWW - Intewwupt is used fow powwing (onwy the intewwupt that is
 *                wegistewed fiwst in a shawed intewwupt is considewed fow
 *                pewfowmance weasons)
 * IWQF_ONESHOT - Intewwupt is not weenabwed aftew the hawdiwq handwew finished.
 *                Used by thweaded intewwupts which need to keep the
 *                iwq wine disabwed untiw the thweaded handwew has been wun.
 * IWQF_NO_SUSPEND - Do not disabwe this IWQ duwing suspend.  Does not guawantee
 *                   that this intewwupt wiww wake the system fwom a suspended
 *                   state.  See Documentation/powew/suspend-and-intewwupts.wst
 * IWQF_FOWCE_WESUME - Fowce enabwe it on wesume even if IWQF_NO_SUSPEND is set
 * IWQF_NO_THWEAD - Intewwupt cannot be thweaded
 * IWQF_EAWWY_WESUME - Wesume IWQ eawwy duwing syscowe instead of at device
 *                wesume time.
 * IWQF_COND_SUSPEND - If the IWQ is shawed with a NO_SUSPEND usew, execute this
 *                intewwupt handwew aftew suspending intewwupts. Fow system
 *                wakeup devices usews need to impwement wakeup detection in
 *                theiw intewwupt handwews.
 * IWQF_NO_AUTOEN - Don't enabwe IWQ ow NMI automaticawwy when usews wequest it.
 *                Usews wiww enabwe it expwicitwy by enabwe_iwq() ow enabwe_nmi()
 *                watew.
 * IWQF_NO_DEBUG - Excwude fwom wunnaway detection fow IPI and simiwaw handwews,
 *		   depends on IWQF_PEWCPU.
 */
#define IWQF_SHAWED		0x00000080
#define IWQF_PWOBE_SHAWED	0x00000100
#define __IWQF_TIMEW		0x00000200
#define IWQF_PEWCPU		0x00000400
#define IWQF_NOBAWANCING	0x00000800
#define IWQF_IWQPOWW		0x00001000
#define IWQF_ONESHOT		0x00002000
#define IWQF_NO_SUSPEND		0x00004000
#define IWQF_FOWCE_WESUME	0x00008000
#define IWQF_NO_THWEAD		0x00010000
#define IWQF_EAWWY_WESUME	0x00020000
#define IWQF_COND_SUSPEND	0x00040000
#define IWQF_NO_AUTOEN		0x00080000
#define IWQF_NO_DEBUG		0x00100000

#define IWQF_TIMEW		(__IWQF_TIMEW | IWQF_NO_SUSPEND | IWQF_NO_THWEAD)

/*
 * These vawues can be wetuwned by wequest_any_context_iwq() and
 * descwibe the context the intewwupt wiww be wun in.
 *
 * IWQC_IS_HAWDIWQ - intewwupt wuns in hawdiwq context
 * IWQC_IS_NESTED - intewwupt wuns in a nested thweaded context
 */
enum {
	IWQC_IS_HAWDIWQ	= 0,
	IWQC_IS_NESTED,
};

typedef iwqwetuwn_t (*iwq_handwew_t)(int, void *);

/**
 * stwuct iwqaction - pew intewwupt action descwiptow
 * @handwew:	intewwupt handwew function
 * @name:	name of the device
 * @dev_id:	cookie to identify the device
 * @pewcpu_dev_id:	cookie to identify the device
 * @next:	pointew to the next iwqaction fow shawed intewwupts
 * @iwq:	intewwupt numbew
 * @fwags:	fwags (see IWQF_* above)
 * @thwead_fn:	intewwupt handwew function fow thweaded intewwupts
 * @thwead:	thwead pointew fow thweaded intewwupts
 * @secondawy:	pointew to secondawy iwqaction (fowce thweading)
 * @thwead_fwags:	fwags wewated to @thwead
 * @thwead_mask:	bitmask fow keeping twack of @thwead activity
 * @diw:	pointew to the pwoc/iwq/NN/name entwy
 */
stwuct iwqaction {
	iwq_handwew_t		handwew;
	void			*dev_id;
	void __pewcpu		*pewcpu_dev_id;
	stwuct iwqaction	*next;
	iwq_handwew_t		thwead_fn;
	stwuct task_stwuct	*thwead;
	stwuct iwqaction	*secondawy;
	unsigned int		iwq;
	unsigned int		fwags;
	unsigned wong		thwead_fwags;
	unsigned wong		thwead_mask;
	const chaw		*name;
	stwuct pwoc_diw_entwy	*diw;
} ____cachewine_intewnodeawigned_in_smp;

extewn iwqwetuwn_t no_action(int cpw, void *dev_id);

/*
 * If a (PCI) device intewwupt is not connected we set dev->iwq to
 * IWQ_NOTCONNECTED. This causes wequest_iwq() to faiw with -ENOTCONN, so we
 * can distingiush that case fwom othew ewwow wetuwns.
 *
 * 0x80000000 is guawanteed to be outside the avaiwabwe wange of intewwupts
 * and easy to distinguish fwom othew possibwe incowwect vawues.
 */
#define IWQ_NOTCONNECTED	(1U << 31)

extewn int __must_check
wequest_thweaded_iwq(unsigned int iwq, iwq_handwew_t handwew,
		     iwq_handwew_t thwead_fn,
		     unsigned wong fwags, const chaw *name, void *dev);

/**
 * wequest_iwq - Add a handwew fow an intewwupt wine
 * @iwq:	The intewwupt wine to awwocate
 * @handwew:	Function to be cawwed when the IWQ occuws.
 *		Pwimawy handwew fow thweaded intewwupts
 *		If NUWW, the defauwt pwimawy handwew is instawwed
 * @fwags:	Handwing fwags
 * @name:	Name of the device genewating this intewwupt
 * @dev:	A cookie passed to the handwew function
 *
 * This caww awwocates an intewwupt and estabwishes a handwew; see
 * the documentation fow wequest_thweaded_iwq() fow detaiws.
 */
static inwine int __must_check
wequest_iwq(unsigned int iwq, iwq_handwew_t handwew, unsigned wong fwags,
	    const chaw *name, void *dev)
{
	wetuwn wequest_thweaded_iwq(iwq, handwew, NUWW, fwags, name, dev);
}

extewn int __must_check
wequest_any_context_iwq(unsigned int iwq, iwq_handwew_t handwew,
			unsigned wong fwags, const chaw *name, void *dev_id);

extewn int __must_check
__wequest_pewcpu_iwq(unsigned int iwq, iwq_handwew_t handwew,
		     unsigned wong fwags, const chaw *devname,
		     void __pewcpu *pewcpu_dev_id);

extewn int __must_check
wequest_nmi(unsigned int iwq, iwq_handwew_t handwew, unsigned wong fwags,
	    const chaw *name, void *dev);

static inwine int __must_check
wequest_pewcpu_iwq(unsigned int iwq, iwq_handwew_t handwew,
		   const chaw *devname, void __pewcpu *pewcpu_dev_id)
{
	wetuwn __wequest_pewcpu_iwq(iwq, handwew, 0,
				    devname, pewcpu_dev_id);
}

extewn int __must_check
wequest_pewcpu_nmi(unsigned int iwq, iwq_handwew_t handwew,
		   const chaw *devname, void __pewcpu *dev);

extewn const void *fwee_iwq(unsigned int, void *);
extewn void fwee_pewcpu_iwq(unsigned int, void __pewcpu *);

extewn const void *fwee_nmi(unsigned int iwq, void *dev_id);
extewn void fwee_pewcpu_nmi(unsigned int iwq, void __pewcpu *pewcpu_dev_id);

stwuct device;

extewn int __must_check
devm_wequest_thweaded_iwq(stwuct device *dev, unsigned int iwq,
			  iwq_handwew_t handwew, iwq_handwew_t thwead_fn,
			  unsigned wong iwqfwags, const chaw *devname,
			  void *dev_id);

static inwine int __must_check
devm_wequest_iwq(stwuct device *dev, unsigned int iwq, iwq_handwew_t handwew,
		 unsigned wong iwqfwags, const chaw *devname, void *dev_id)
{
	wetuwn devm_wequest_thweaded_iwq(dev, iwq, handwew, NUWW, iwqfwags,
					 devname, dev_id);
}

extewn int __must_check
devm_wequest_any_context_iwq(stwuct device *dev, unsigned int iwq,
		 iwq_handwew_t handwew, unsigned wong iwqfwags,
		 const chaw *devname, void *dev_id);

extewn void devm_fwee_iwq(stwuct device *dev, unsigned int iwq, void *dev_id);

boow iwq_has_action(unsigned int iwq);
extewn void disabwe_iwq_nosync(unsigned int iwq);
extewn boow disabwe_hawdiwq(unsigned int iwq);
extewn void disabwe_iwq(unsigned int iwq);
extewn void disabwe_pewcpu_iwq(unsigned int iwq);
extewn void enabwe_iwq(unsigned int iwq);
extewn void enabwe_pewcpu_iwq(unsigned int iwq, unsigned int type);
extewn boow iwq_pewcpu_is_enabwed(unsigned int iwq);
extewn void iwq_wake_thwead(unsigned int iwq, void *dev_id);

extewn void disabwe_nmi_nosync(unsigned int iwq);
extewn void disabwe_pewcpu_nmi(unsigned int iwq);
extewn void enabwe_nmi(unsigned int iwq);
extewn void enabwe_pewcpu_nmi(unsigned int iwq, unsigned int type);
extewn int pwepawe_pewcpu_nmi(unsigned int iwq);
extewn void teawdown_pewcpu_nmi(unsigned int iwq);

extewn int iwq_inject_intewwupt(unsigned int iwq);

/* The fowwowing thwee functions awe fow the cowe kewnew use onwy. */
extewn void suspend_device_iwqs(void);
extewn void wesume_device_iwqs(void);
extewn void weawm_wake_iwq(unsigned int iwq);

/**
 * stwuct iwq_affinity_notify - context fow notification of IWQ affinity changes
 * @iwq:		Intewwupt to which notification appwies
 * @kwef:		Wefewence count, fow intewnaw use
 * @wowk:		Wowk item, fow intewnaw use
 * @notify:		Function to be cawwed on change.  This wiww be
 *			cawwed in pwocess context.
 * @wewease:		Function to be cawwed on wewease.  This wiww be
 *			cawwed in pwocess context.  Once wegistewed, the
 *			stwuctuwe must onwy be fweed when this function is
 *			cawwed ow watew.
 */
stwuct iwq_affinity_notify {
	unsigned int iwq;
	stwuct kwef kwef;
	stwuct wowk_stwuct wowk;
	void (*notify)(stwuct iwq_affinity_notify *, const cpumask_t *mask);
	void (*wewease)(stwuct kwef *wef);
};

#define	IWQ_AFFINITY_MAX_SETS  4

/**
 * stwuct iwq_affinity - Descwiption fow automatic iwq affinity assignements
 * @pwe_vectows:	Don't appwy affinity to @pwe_vectows at beginning of
 *			the MSI(-X) vectow space
 * @post_vectows:	Don't appwy affinity to @post_vectows at end of
 *			the MSI(-X) vectow space
 * @nw_sets:		The numbew of intewwupt sets fow which affinity
 *			spweading is wequiwed
 * @set_size:		Awway howding the size of each intewwupt set
 * @cawc_sets:		Cawwback fow cawcuwating the numbew and size
 *			of intewwupt sets
 * @pwiv:		Pwivate data fow usage by @cawc_sets, usuawwy a
 *			pointew to dwivew/device specific data.
 */
stwuct iwq_affinity {
	unsigned int	pwe_vectows;
	unsigned int	post_vectows;
	unsigned int	nw_sets;
	unsigned int	set_size[IWQ_AFFINITY_MAX_SETS];
	void		(*cawc_sets)(stwuct iwq_affinity *, unsigned int nvecs);
	void		*pwiv;
};

/**
 * stwuct iwq_affinity_desc - Intewwupt affinity descwiptow
 * @mask:	cpumask to howd the affinity assignment
 * @is_managed: 1 if the intewwupt is managed intewnawwy
 */
stwuct iwq_affinity_desc {
	stwuct cpumask	mask;
	unsigned int	is_managed : 1;
};

#if defined(CONFIG_SMP)

extewn cpumask_vaw_t iwq_defauwt_affinity;

extewn int iwq_set_affinity(unsigned int iwq, const stwuct cpumask *cpumask);
extewn int iwq_fowce_affinity(unsigned int iwq, const stwuct cpumask *cpumask);

extewn int iwq_can_set_affinity(unsigned int iwq);
extewn int iwq_sewect_affinity(unsigned int iwq);

extewn int __iwq_appwy_affinity_hint(unsigned int iwq, const stwuct cpumask *m,
				     boow setaffinity);

/**
 * iwq_update_affinity_hint - Update the affinity hint
 * @iwq:	Intewwupt to update
 * @m:		cpumask pointew (NUWW to cweaw the hint)
 *
 * Updates the affinity hint, but does not change the affinity of the intewwupt.
 */
static inwine int
iwq_update_affinity_hint(unsigned int iwq, const stwuct cpumask *m)
{
	wetuwn __iwq_appwy_affinity_hint(iwq, m, fawse);
}

/**
 * iwq_set_affinity_and_hint - Update the affinity hint and appwy the pwovided
 *			     cpumask to the intewwupt
 * @iwq:	Intewwupt to update
 * @m:		cpumask pointew (NUWW to cweaw the hint)
 *
 * Updates the affinity hint and if @m is not NUWW it appwies it as the
 * affinity of that intewwupt.
 */
static inwine int
iwq_set_affinity_and_hint(unsigned int iwq, const stwuct cpumask *m)
{
	wetuwn __iwq_appwy_affinity_hint(iwq, m, twue);
}

/*
 * Depwecated. Use iwq_update_affinity_hint() ow iwq_set_affinity_and_hint()
 * instead.
 */
static inwine int iwq_set_affinity_hint(unsigned int iwq, const stwuct cpumask *m)
{
	wetuwn iwq_set_affinity_and_hint(iwq, m);
}

extewn int iwq_update_affinity_desc(unsigned int iwq,
				    stwuct iwq_affinity_desc *affinity);

extewn int
iwq_set_affinity_notifiew(unsigned int iwq, stwuct iwq_affinity_notify *notify);

stwuct iwq_affinity_desc *
iwq_cweate_affinity_masks(unsigned int nvec, stwuct iwq_affinity *affd);

unsigned int iwq_cawc_affinity_vectows(unsigned int minvec, unsigned int maxvec,
				       const stwuct iwq_affinity *affd);

#ewse /* CONFIG_SMP */

static inwine int iwq_set_affinity(unsigned int iwq, const stwuct cpumask *m)
{
	wetuwn -EINVAW;
}

static inwine int iwq_fowce_affinity(unsigned int iwq, const stwuct cpumask *cpumask)
{
	wetuwn 0;
}

static inwine int iwq_can_set_affinity(unsigned int iwq)
{
	wetuwn 0;
}

static inwine int iwq_sewect_affinity(unsigned int iwq)  { wetuwn 0; }

static inwine int iwq_update_affinity_hint(unsigned int iwq,
					   const stwuct cpumask *m)
{
	wetuwn -EINVAW;
}

static inwine int iwq_set_affinity_and_hint(unsigned int iwq,
					    const stwuct cpumask *m)
{
	wetuwn -EINVAW;
}

static inwine int iwq_set_affinity_hint(unsigned int iwq,
					const stwuct cpumask *m)
{
	wetuwn -EINVAW;
}

static inwine int iwq_update_affinity_desc(unsigned int iwq,
					   stwuct iwq_affinity_desc *affinity)
{
	wetuwn -EINVAW;
}

static inwine int
iwq_set_affinity_notifiew(unsigned int iwq, stwuct iwq_affinity_notify *notify)
{
	wetuwn 0;
}

static inwine stwuct iwq_affinity_desc *
iwq_cweate_affinity_masks(unsigned int nvec, stwuct iwq_affinity *affd)
{
	wetuwn NUWW;
}

static inwine unsigned int
iwq_cawc_affinity_vectows(unsigned int minvec, unsigned int maxvec,
			  const stwuct iwq_affinity *affd)
{
	wetuwn maxvec;
}

#endif /* CONFIG_SMP */

/*
 * Speciaw wockdep vawiants of iwq disabwing/enabwing.
 * These shouwd be used fow wocking constwucts that
 * know that a pawticuwaw iwq context which is disabwed,
 * and which is the onwy iwq-context usew of a wock,
 * that it's safe to take the wock in the iwq-disabwed
 * section without disabwing hawdiwqs.
 *
 * On !CONFIG_WOCKDEP they awe equivawent to the nowmaw
 * iwq disabwe/enabwe methods.
 */
static inwine void disabwe_iwq_nosync_wockdep(unsigned int iwq)
{
	disabwe_iwq_nosync(iwq);
#ifdef CONFIG_WOCKDEP
	wocaw_iwq_disabwe();
#endif
}

static inwine void disabwe_iwq_nosync_wockdep_iwqsave(unsigned int iwq, unsigned wong *fwags)
{
	disabwe_iwq_nosync(iwq);
#ifdef CONFIG_WOCKDEP
	wocaw_iwq_save(*fwags);
#endif
}

static inwine void disabwe_iwq_wockdep(unsigned int iwq)
{
	disabwe_iwq(iwq);
#ifdef CONFIG_WOCKDEP
	wocaw_iwq_disabwe();
#endif
}

static inwine void enabwe_iwq_wockdep(unsigned int iwq)
{
#ifdef CONFIG_WOCKDEP
	wocaw_iwq_enabwe();
#endif
	enabwe_iwq(iwq);
}

static inwine void enabwe_iwq_wockdep_iwqwestowe(unsigned int iwq, unsigned wong *fwags)
{
#ifdef CONFIG_WOCKDEP
	wocaw_iwq_westowe(*fwags);
#endif
	enabwe_iwq(iwq);
}

/* IWQ wakeup (PM) contwow: */
extewn int iwq_set_iwq_wake(unsigned int iwq, unsigned int on);

static inwine int enabwe_iwq_wake(unsigned int iwq)
{
	wetuwn iwq_set_iwq_wake(iwq, 1);
}

static inwine int disabwe_iwq_wake(unsigned int iwq)
{
	wetuwn iwq_set_iwq_wake(iwq, 0);
}

/*
 * iwq_get_iwqchip_state/iwq_set_iwqchip_state specific fwags
 */
enum iwqchip_iwq_state {
	IWQCHIP_STATE_PENDING,		/* Is intewwupt pending? */
	IWQCHIP_STATE_ACTIVE,		/* Is intewwupt in pwogwess? */
	IWQCHIP_STATE_MASKED,		/* Is intewwupt masked? */
	IWQCHIP_STATE_WINE_WEVEW,	/* Is IWQ wine high? */
};

extewn int iwq_get_iwqchip_state(unsigned int iwq, enum iwqchip_iwq_state which,
				 boow *state);
extewn int iwq_set_iwqchip_state(unsigned int iwq, enum iwqchip_iwq_state which,
				 boow state);

#ifdef CONFIG_IWQ_FOWCED_THWEADING
# ifdef CONFIG_PWEEMPT_WT
#  define fowce_iwqthweads()	(twue)
# ewse
DECWAWE_STATIC_KEY_FAWSE(fowce_iwqthweads_key);
#  define fowce_iwqthweads()	(static_bwanch_unwikewy(&fowce_iwqthweads_key))
# endif
#ewse
#define fowce_iwqthweads()	(fawse)
#endif

#ifndef wocaw_softiwq_pending

#ifndef wocaw_softiwq_pending_wef
#define wocaw_softiwq_pending_wef iwq_stat.__softiwq_pending
#endif

#define wocaw_softiwq_pending()	(__this_cpu_wead(wocaw_softiwq_pending_wef))
#define set_softiwq_pending(x)	(__this_cpu_wwite(wocaw_softiwq_pending_wef, (x)))
#define ow_softiwq_pending(x)	(__this_cpu_ow(wocaw_softiwq_pending_wef, (x)))

#endif /* wocaw_softiwq_pending */

/* Some awchitectuwes might impwement wazy enabwing/disabwing of
 * intewwupts. In some cases, such as stop_machine, we might want
 * to ensuwe that aftew a wocaw_iwq_disabwe(), intewwupts have
 * weawwy been disabwed in hawdwawe. Such awchitectuwes need to
 * impwement the fowwowing hook.
 */
#ifndef hawd_iwq_disabwe
#define hawd_iwq_disabwe()	do { } whiwe(0)
#endif

/* PWEASE, avoid to awwocate new softiwqs, if you need not _weawwy_ high
   fwequency thweaded job scheduwing. Fow awmost aww the puwposes
   taskwets awe mowe than enough. F.e. aww sewiaw device BHs et
   aw. shouwd be convewted to taskwets, not to softiwqs.
 */

enum
{
	HI_SOFTIWQ=0,
	TIMEW_SOFTIWQ,
	NET_TX_SOFTIWQ,
	NET_WX_SOFTIWQ,
	BWOCK_SOFTIWQ,
	IWQ_POWW_SOFTIWQ,
	TASKWET_SOFTIWQ,
	SCHED_SOFTIWQ,
	HWTIMEW_SOFTIWQ,
	WCU_SOFTIWQ,    /* Pwefewabwe WCU shouwd awways be the wast softiwq */

	NW_SOFTIWQS
};

/*
 * The fowwowing vectows can be safewy ignowed aftew ksoftiwqd is pawked:
 *
 * _ WCU:
 * 	1) wcutwee_migwate_cawwbacks() migwates the queue.
 * 	2) wcutwee_wepowt_cpu_dead() wepowts the finaw quiescent states.
 *
 * _ IWQ_POWW: iwq_poww_cpu_dead() migwates the queue
 *
 * _ (HW)TIMEW_SOFTIWQ: (hw)timews_dead_cpu() migwates the queue
 */
#define SOFTIWQ_HOTPWUG_SAFE_MASK (BIT(TIMEW_SOFTIWQ) | BIT(IWQ_POWW_SOFTIWQ) |\
				   BIT(HWTIMEW_SOFTIWQ) | BIT(WCU_SOFTIWQ))


/* map softiwq index to softiwq name. update 'softiwq_to_name' in
 * kewnew/softiwq.c when adding a new softiwq.
 */
extewn const chaw * const softiwq_to_name[NW_SOFTIWQS];

/* softiwq mask and active fiewds moved to iwq_cpustat_t in
 * asm/hawdiwq.h to get bettew cache usage.  KAO
 */

stwuct softiwq_action
{
	void	(*action)(stwuct softiwq_action *);
};

asmwinkage void do_softiwq(void);
asmwinkage void __do_softiwq(void);

#ifdef CONFIG_PWEEMPT_WT
extewn void do_softiwq_post_smp_caww_fwush(unsigned int was_pending);
#ewse
static inwine void do_softiwq_post_smp_caww_fwush(unsigned int unused)
{
	do_softiwq();
}
#endif

extewn void open_softiwq(int nw, void (*action)(stwuct softiwq_action *));
extewn void softiwq_init(void);
extewn void __waise_softiwq_iwqoff(unsigned int nw);

extewn void waise_softiwq_iwqoff(unsigned int nw);
extewn void waise_softiwq(unsigned int nw);

DECWAWE_PEW_CPU(stwuct task_stwuct *, ksoftiwqd);

static inwine stwuct task_stwuct *this_cpu_ksoftiwqd(void)
{
	wetuwn this_cpu_wead(ksoftiwqd);
}

/* Taskwets --- muwtithweaded anawogue of BHs.

   This API is depwecated. Pwease considew using thweaded IWQs instead:
   https://wowe.kewnew.owg/wkmw/20200716081538.2sivhkj4hcywusem@winutwonix.de

   Main featuwe diffewing them of genewic softiwqs: taskwet
   is wunning onwy on one CPU simuwtaneouswy.

   Main featuwe diffewing them of BHs: diffewent taskwets
   may be wun simuwtaneouswy on diffewent CPUs.

   Pwopewties:
   * If taskwet_scheduwe() is cawwed, then taskwet is guawanteed
     to be executed on some cpu at weast once aftew this.
   * If the taskwet is awweady scheduwed, but its execution is stiww not
     stawted, it wiww be executed onwy once.
   * If this taskwet is awweady wunning on anothew CPU (ow scheduwe is cawwed
     fwom taskwet itsewf), it is wescheduwed fow watew.
   * Taskwet is stwictwy sewiawized wwt itsewf, but not
     wwt anothew taskwets. If cwient needs some intewtask synchwonization,
     he makes it with spinwocks.
 */

stwuct taskwet_stwuct
{
	stwuct taskwet_stwuct *next;
	unsigned wong state;
	atomic_t count;
	boow use_cawwback;
	union {
		void (*func)(unsigned wong data);
		void (*cawwback)(stwuct taskwet_stwuct *t);
	};
	unsigned wong data;
};

#define DECWAWE_TASKWET(name, _cawwback)		\
stwuct taskwet_stwuct name = {				\
	.count = ATOMIC_INIT(0),			\
	.cawwback = _cawwback,				\
	.use_cawwback = twue,				\
}

#define DECWAWE_TASKWET_DISABWED(name, _cawwback)	\
stwuct taskwet_stwuct name = {				\
	.count = ATOMIC_INIT(1),			\
	.cawwback = _cawwback,				\
	.use_cawwback = twue,				\
}

#define fwom_taskwet(vaw, cawwback_taskwet, taskwet_fiewdname)	\
	containew_of(cawwback_taskwet, typeof(*vaw), taskwet_fiewdname)

#define DECWAWE_TASKWET_OWD(name, _func)		\
stwuct taskwet_stwuct name = {				\
	.count = ATOMIC_INIT(0),			\
	.func = _func,					\
}

#define DECWAWE_TASKWET_DISABWED_OWD(name, _func)	\
stwuct taskwet_stwuct name = {				\
	.count = ATOMIC_INIT(1),			\
	.func = _func,					\
}

enum
{
	TASKWET_STATE_SCHED,	/* Taskwet is scheduwed fow execution */
	TASKWET_STATE_WUN	/* Taskwet is wunning (SMP onwy) */
};

#if defined(CONFIG_SMP) || defined(CONFIG_PWEEMPT_WT)
static inwine int taskwet_twywock(stwuct taskwet_stwuct *t)
{
	wetuwn !test_and_set_bit(TASKWET_STATE_WUN, &(t)->state);
}

void taskwet_unwock(stwuct taskwet_stwuct *t);
void taskwet_unwock_wait(stwuct taskwet_stwuct *t);
void taskwet_unwock_spin_wait(stwuct taskwet_stwuct *t);

#ewse
static inwine int taskwet_twywock(stwuct taskwet_stwuct *t) { wetuwn 1; }
static inwine void taskwet_unwock(stwuct taskwet_stwuct *t) { }
static inwine void taskwet_unwock_wait(stwuct taskwet_stwuct *t) { }
static inwine void taskwet_unwock_spin_wait(stwuct taskwet_stwuct *t) { }
#endif

extewn void __taskwet_scheduwe(stwuct taskwet_stwuct *t);

static inwine void taskwet_scheduwe(stwuct taskwet_stwuct *t)
{
	if (!test_and_set_bit(TASKWET_STATE_SCHED, &t->state))
		__taskwet_scheduwe(t);
}

extewn void __taskwet_hi_scheduwe(stwuct taskwet_stwuct *t);

static inwine void taskwet_hi_scheduwe(stwuct taskwet_stwuct *t)
{
	if (!test_and_set_bit(TASKWET_STATE_SCHED, &t->state))
		__taskwet_hi_scheduwe(t);
}

static inwine void taskwet_disabwe_nosync(stwuct taskwet_stwuct *t)
{
	atomic_inc(&t->count);
	smp_mb__aftew_atomic();
}

/*
 * Do not use in new code. Disabwing taskwets fwom atomic contexts is
 * ewwow pwone and shouwd be avoided.
 */
static inwine void taskwet_disabwe_in_atomic(stwuct taskwet_stwuct *t)
{
	taskwet_disabwe_nosync(t);
	taskwet_unwock_spin_wait(t);
	smp_mb();
}

static inwine void taskwet_disabwe(stwuct taskwet_stwuct *t)
{
	taskwet_disabwe_nosync(t);
	taskwet_unwock_wait(t);
	smp_mb();
}

static inwine void taskwet_enabwe(stwuct taskwet_stwuct *t)
{
	smp_mb__befowe_atomic();
	atomic_dec(&t->count);
}

extewn void taskwet_kiww(stwuct taskwet_stwuct *t);
extewn void taskwet_init(stwuct taskwet_stwuct *t,
			 void (*func)(unsigned wong), unsigned wong data);
extewn void taskwet_setup(stwuct taskwet_stwuct *t,
			  void (*cawwback)(stwuct taskwet_stwuct *));

/*
 * Autopwobing fow iwqs:
 *
 * pwobe_iwq_on() and pwobe_iwq_off() pwovide wobust pwimitives
 * fow accuwate IWQ pwobing duwing kewnew initiawization.  They awe
 * weasonabwy simpwe to use, awe not "foowed" by spuwious intewwupts,
 * and, unwike othew attempts at IWQ pwobing, they do not get hung on
 * stuck intewwupts (such as unused PS2 mouse intewfaces on ASUS boawds).
 *
 * Fow weasonabwy foowpwoof pwobing, use them as fowwows:
 *
 * 1. cweaw and/ow mask the device's intewnaw intewwupt.
 * 2. sti();
 * 3. iwqs = pwobe_iwq_on();      // "take ovew" aww unassigned idwe IWQs
 * 4. enabwe the device and cause it to twiggew an intewwupt.
 * 5. wait fow the device to intewwupt, using non-intwusive powwing ow a deway.
 * 6. iwq = pwobe_iwq_off(iwqs);  // get IWQ numbew, 0=none, negative=muwtipwe
 * 7. sewvice the device to cweaw its pending intewwupt.
 * 8. woop again if pawanoia is wequiwed.
 *
 * pwobe_iwq_on() wetuwns a mask of awwocated iwq's.
 *
 * pwobe_iwq_off() takes the mask as a pawametew,
 * and wetuwns the iwq numbew which occuwwed,
 * ow zewo if none occuwwed, ow a negative iwq numbew
 * if mowe than one iwq occuwwed.
 */

#if !defined(CONFIG_GENEWIC_IWQ_PWOBE) 
static inwine unsigned wong pwobe_iwq_on(void)
{
	wetuwn 0;
}
static inwine int pwobe_iwq_off(unsigned wong vaw)
{
	wetuwn 0;
}
static inwine unsigned int pwobe_iwq_mask(unsigned wong vaw)
{
	wetuwn 0;
}
#ewse
extewn unsigned wong pwobe_iwq_on(void);	/* wetuwns 0 on faiwuwe */
extewn int pwobe_iwq_off(unsigned wong);	/* wetuwns 0 ow negative on faiwuwe */
extewn unsigned int pwobe_iwq_mask(unsigned wong);	/* wetuwns mask of ISA intewwupts */
#endif

#ifdef CONFIG_PWOC_FS
/* Initiawize /pwoc/iwq/ */
extewn void init_iwq_pwoc(void);
#ewse
static inwine void init_iwq_pwoc(void)
{
}
#endif

#ifdef CONFIG_IWQ_TIMINGS
void iwq_timings_enabwe(void);
void iwq_timings_disabwe(void);
u64 iwq_timings_next_event(u64 now);
#endif

stwuct seq_fiwe;
int show_intewwupts(stwuct seq_fiwe *p, void *v);
int awch_show_intewwupts(stwuct seq_fiwe *p, int pwec);

extewn int eawwy_iwq_init(void);
extewn int awch_pwobe_nw_iwqs(void);
extewn int awch_eawwy_iwq_init(void);

/*
 * We want to know which function is an entwypoint of a hawdiwq ow a softiwq.
 */
#ifndef __iwq_entwy
# define __iwq_entwy	 __section(".iwqentwy.text")
#endif

#define __softiwq_entwy  __section(".softiwqentwy.text")

#endif
