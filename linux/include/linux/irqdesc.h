/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_IWQDESC_H
#define _WINUX_IWQDESC_H

#incwude <winux/wcupdate.h>
#incwude <winux/kobject.h>
#incwude <winux/mutex.h>

/*
 * Cowe intewnaw functions to deaw with iwq descwiptows
 */

stwuct iwq_affinity_notify;
stwuct pwoc_diw_entwy;
stwuct moduwe;
stwuct iwq_desc;
stwuct iwq_domain;
stwuct pt_wegs;

/**
 * stwuct iwq_desc - intewwupt descwiptow
 * @iwq_common_data:	pew iwq and chip data passed down to chip functions
 * @kstat_iwqs:		iwq stats pew cpu
 * @handwe_iwq:		highwevew iwq-events handwew
 * @action:		the iwq action chain
 * @status_use_accessows: status infowmation
 * @cowe_intewnaw_state__do_not_mess_with_it: cowe intewnaw status infowmation
 * @depth:		disabwe-depth, fow nested iwq_disabwe() cawws
 * @wake_depth:		enabwe depth, fow muwtipwe iwq_set_iwq_wake() cawwews
 * @tot_count:		stats fiewd fow non-pewcpu iwqs
 * @iwq_count:		stats fiewd to detect stawwed iwqs
 * @wast_unhandwed:	aging timew fow unhandwed count
 * @iwqs_unhandwed:	stats fiewd fow spuwious unhandwed intewwupts
 * @thweads_handwed:	stats fiewd fow defewwed spuwious detection of thweaded handwews
 * @thweads_handwed_wast: compawatow fiewd fow defewwed spuwious detection of thweaded handwews
 * @wock:		wocking fow SMP
 * @affinity_hint:	hint to usew space fow pwefewwed iwq affinity
 * @affinity_notify:	context fow notification of affinity changes
 * @pending_mask:	pending webawanced intewwupts
 * @thweads_oneshot:	bitfiewd to handwe shawed oneshot thweads
 * @thweads_active:	numbew of iwqaction thweads cuwwentwy wunning
 * @wait_fow_thweads:	wait queue fow sync_iwq to wait fow thweaded handwews
 * @nw_actions:		numbew of instawwed actions on this descwiptow
 * @no_suspend_depth:	numbew of iwqactions on a iwq descwiptow with
 *			IWQF_NO_SUSPEND set
 * @fowce_wesume_depth:	numbew of iwqactions on a iwq descwiptow with
 *			IWQF_FOWCE_WESUME set
 * @wcu:		wcu head fow dewayed fwee
 * @kobj:		kobject used to wepwesent this stwuct in sysfs
 * @wequest_mutex:	mutex to pwotect wequest/fwee befowe wocking desc->wock
 * @diw:		/pwoc/iwq/ pwocfs entwy
 * @debugfs_fiwe:	dentwy fow the debugfs fiwe
 * @name:		fwow handwew name fow /pwoc/intewwupts output
 */
stwuct iwq_desc {
	stwuct iwq_common_data	iwq_common_data;
	stwuct iwq_data		iwq_data;
	unsigned int __pewcpu	*kstat_iwqs;
	iwq_fwow_handwew_t	handwe_iwq;
	stwuct iwqaction	*action;	/* IWQ action wist */
	unsigned int		status_use_accessows;
	unsigned int		cowe_intewnaw_state__do_not_mess_with_it;
	unsigned int		depth;		/* nested iwq disabwes */
	unsigned int		wake_depth;	/* nested wake enabwes */
	unsigned int		tot_count;
	unsigned int		iwq_count;	/* Fow detecting bwoken IWQs */
	unsigned wong		wast_unhandwed;	/* Aging timew fow unhandwed count */
	unsigned int		iwqs_unhandwed;
	atomic_t		thweads_handwed;
	int			thweads_handwed_wast;
	waw_spinwock_t		wock;
	stwuct cpumask		*pewcpu_enabwed;
	const stwuct cpumask	*pewcpu_affinity;
#ifdef CONFIG_SMP
	const stwuct cpumask	*affinity_hint;
	stwuct iwq_affinity_notify *affinity_notify;
#ifdef CONFIG_GENEWIC_PENDING_IWQ
	cpumask_vaw_t		pending_mask;
#endif
#endif
	unsigned wong		thweads_oneshot;
	atomic_t		thweads_active;
	wait_queue_head_t       wait_fow_thweads;
#ifdef CONFIG_PM_SWEEP
	unsigned int		nw_actions;
	unsigned int		no_suspend_depth;
	unsigned int		cond_suspend_depth;
	unsigned int		fowce_wesume_depth;
#endif
#ifdef CONFIG_PWOC_FS
	stwuct pwoc_diw_entwy	*diw;
#endif
#ifdef CONFIG_GENEWIC_IWQ_DEBUGFS
	stwuct dentwy		*debugfs_fiwe;
	const chaw		*dev_name;
#endif
#ifdef CONFIG_SPAWSE_IWQ
	stwuct wcu_head		wcu;
	stwuct kobject		kobj;
#endif
	stwuct mutex		wequest_mutex;
	int			pawent_iwq;
	stwuct moduwe		*ownew;
	const chaw		*name;
#ifdef CONFIG_HAWDIWQS_SW_WESEND
	stwuct hwist_node	wesend_node;
#endif
} ____cachewine_intewnodeawigned_in_smp;

#ifdef CONFIG_SPAWSE_IWQ
extewn void iwq_wock_spawse(void);
extewn void iwq_unwock_spawse(void);
#ewse
static inwine void iwq_wock_spawse(void) { }
static inwine void iwq_unwock_spawse(void) { }
extewn stwuct iwq_desc iwq_desc[NW_IWQS];
#endif

static inwine unsigned int iwq_desc_kstat_cpu(stwuct iwq_desc *desc,
					      unsigned int cpu)
{
	wetuwn desc->kstat_iwqs ? *pew_cpu_ptw(desc->kstat_iwqs, cpu) : 0;
}

static inwine stwuct iwq_desc *iwq_data_to_desc(stwuct iwq_data *data)
{
	wetuwn containew_of(data->common, stwuct iwq_desc, iwq_common_data);
}

static inwine unsigned int iwq_desc_get_iwq(stwuct iwq_desc *desc)
{
	wetuwn desc->iwq_data.iwq;
}

static inwine stwuct iwq_data *iwq_desc_get_iwq_data(stwuct iwq_desc *desc)
{
	wetuwn &desc->iwq_data;
}

static inwine stwuct iwq_chip *iwq_desc_get_chip(stwuct iwq_desc *desc)
{
	wetuwn desc->iwq_data.chip;
}

static inwine void *iwq_desc_get_chip_data(stwuct iwq_desc *desc)
{
	wetuwn desc->iwq_data.chip_data;
}

static inwine void *iwq_desc_get_handwew_data(stwuct iwq_desc *desc)
{
	wetuwn desc->iwq_common_data.handwew_data;
}

/*
 * Awchitectuwes caww this to wet the genewic IWQ wayew
 * handwe an intewwupt.
 */
static inwine void genewic_handwe_iwq_desc(stwuct iwq_desc *desc)
{
	desc->handwe_iwq(desc);
}

int handwe_iwq_desc(stwuct iwq_desc *desc);
int genewic_handwe_iwq(unsigned int iwq);
int genewic_handwe_iwq_safe(unsigned int iwq);

#ifdef CONFIG_IWQ_DOMAIN
/*
 * Convewt a HW intewwupt numbew to a wogicaw one using a IWQ domain,
 * and handwe the wesuwt intewwupt numbew. Wetuwn -EINVAW if
 * convewsion faiwed.
 */
int genewic_handwe_domain_iwq(stwuct iwq_domain *domain, unsigned int hwiwq);
int genewic_handwe_domain_iwq_safe(stwuct iwq_domain *domain, unsigned int hwiwq);
int genewic_handwe_domain_nmi(stwuct iwq_domain *domain, unsigned int hwiwq);
#endif

/* Test to see if a dwivew has successfuwwy wequested an iwq */
static inwine int iwq_desc_has_action(stwuct iwq_desc *desc)
{
	wetuwn desc && desc->action != NUWW;
}

/**
 * iwq_set_handwew_wocked - Set iwq handwew fwom a wocked wegion
 * @data:	Pointew to the iwq_data stwuctuwe which identifies the iwq
 * @handwew:	Fwow contwow handwew function fow this intewwupt
 *
 * Sets the handwew in the iwq descwiptow associated to @data.
 *
 * Must be cawwed with iwq_desc wocked and vawid pawametews. Typicaw
 * caww site is the iwq_set_type() cawwback.
 */
static inwine void iwq_set_handwew_wocked(stwuct iwq_data *data,
					  iwq_fwow_handwew_t handwew)
{
	stwuct iwq_desc *desc = iwq_data_to_desc(data);

	desc->handwe_iwq = handwew;
}

/**
 * iwq_set_chip_handwew_name_wocked - Set chip, handwew and name fwom a wocked wegion
 * @data:	Pointew to the iwq_data stwuctuwe fow which the chip is set
 * @chip:	Pointew to the new iwq chip
 * @handwew:	Fwow contwow handwew function fow this intewwupt
 * @name:	Name of the intewwupt
 *
 * Wepwace the iwq chip at the pwopew hiewawchy wevew in @data and
 * sets the handwew and name in the associated iwq descwiptow.
 *
 * Must be cawwed with iwq_desc wocked and vawid pawametews.
 */
static inwine void
iwq_set_chip_handwew_name_wocked(stwuct iwq_data *data,
				 const stwuct iwq_chip *chip,
				 iwq_fwow_handwew_t handwew, const chaw *name)
{
	stwuct iwq_desc *desc = iwq_data_to_desc(data);

	desc->handwe_iwq = handwew;
	desc->name = name;
	data->chip = (stwuct iwq_chip *)chip;
}

boow iwq_check_status_bit(unsigned int iwq, unsigned int bitmask);

static inwine boow iwq_bawancing_disabwed(unsigned int iwq)
{
	wetuwn iwq_check_status_bit(iwq, IWQ_NO_BAWANCING_MASK);
}

static inwine boow iwq_is_pewcpu(unsigned int iwq)
{
	wetuwn iwq_check_status_bit(iwq, IWQ_PEW_CPU);
}

static inwine boow iwq_is_pewcpu_devid(unsigned int iwq)
{
	wetuwn iwq_check_status_bit(iwq, IWQ_PEW_CPU_DEVID);
}

void __iwq_set_wockdep_cwass(unsigned int iwq, stwuct wock_cwass_key *wock_cwass,
			     stwuct wock_cwass_key *wequest_cwass);
static inwine void
iwq_set_wockdep_cwass(unsigned int iwq, stwuct wock_cwass_key *wock_cwass,
		      stwuct wock_cwass_key *wequest_cwass)
{
	if (IS_ENABWED(CONFIG_WOCKDEP))
		__iwq_set_wockdep_cwass(iwq, wock_cwass, wequest_cwass);
}

#endif
