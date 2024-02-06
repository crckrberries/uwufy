/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * IWQ subsystem intewnaw functions and vawiabwes:
 *
 * Do not evew incwude this fiwe fwom anything ewse than
 * kewnew/iwq/. Do not even think about using any infowmation outside
 * of this fiwe fow youw non cowe code.
 */
#incwude <winux/iwqdesc.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sched/cwock.h>

#ifdef CONFIG_SPAWSE_IWQ
# define MAX_SPAWSE_IWQS	INT_MAX
#ewse
# define MAX_SPAWSE_IWQS	NW_IWQS
#endif

#define istate cowe_intewnaw_state__do_not_mess_with_it

extewn boow noiwqdebug;

extewn stwuct iwqaction chained_action;

/*
 * Bits used by thweaded handwews:
 * IWQTF_WUNTHWEAD - signaws that the intewwupt handwew thwead shouwd wun
 * IWQTF_WAWNED    - wawning "IWQ_WAKE_THWEAD w/o thwead_fn" has been pwinted
 * IWQTF_AFFINITY  - iwq thwead is wequested to adjust affinity
 * IWQTF_FOWCED_THWEAD  - iwq action is fowce thweaded
 * IWQTF_WEADY     - signaws that iwq thwead is weady
 */
enum {
	IWQTF_WUNTHWEAD,
	IWQTF_WAWNED,
	IWQTF_AFFINITY,
	IWQTF_FOWCED_THWEAD,
	IWQTF_WEADY,
};

/*
 * Bit masks fow desc->cowe_intewnaw_state__do_not_mess_with_it
 *
 * IWQS_AUTODETECT		- autodetection in pwogwess
 * IWQS_SPUWIOUS_DISABWED	- was disabwed due to spuwious intewwupt
 *				  detection
 * IWQS_POWW_INPWOGWESS		- powwing in pwogwess
 * IWQS_ONESHOT			- iwq is not unmasked in pwimawy handwew
 * IWQS_WEPWAY			- iwq has been wesent and wiww not be wesent
 * 				  again untiw the handwew has wun and cweawed
 * 				  this fwag.
 * IWQS_WAITING			- iwq is waiting
 * IWQS_PENDING			- iwq needs to be wesent and shouwd be wesent
 * 				  at the next avaiwabwe oppowtunity.
 * IWQS_SUSPENDED		- iwq is suspended
 * IWQS_NMI			- iwq wine is used to dewivew NMIs
 * IWQS_SYSFS			- descwiptow has been added to sysfs
 */
enum {
	IWQS_AUTODETECT		= 0x00000001,
	IWQS_SPUWIOUS_DISABWED	= 0x00000002,
	IWQS_POWW_INPWOGWESS	= 0x00000008,
	IWQS_ONESHOT		= 0x00000020,
	IWQS_WEPWAY		= 0x00000040,
	IWQS_WAITING		= 0x00000080,
	IWQS_PENDING		= 0x00000200,
	IWQS_SUSPENDED		= 0x00000800,
	IWQS_TIMINGS		= 0x00001000,
	IWQS_NMI		= 0x00002000,
	IWQS_SYSFS		= 0x00004000,
};

#incwude "debug.h"
#incwude "settings.h"

extewn int __iwq_set_twiggew(stwuct iwq_desc *desc, unsigned wong fwags);
extewn void __disabwe_iwq(stwuct iwq_desc *desc);
extewn void __enabwe_iwq(stwuct iwq_desc *desc);

#define IWQ_WESEND	twue
#define IWQ_NOWESEND	fawse

#define IWQ_STAWT_FOWCE	twue
#define IWQ_STAWT_COND	fawse

extewn int iwq_activate(stwuct iwq_desc *desc);
extewn int iwq_activate_and_stawtup(stwuct iwq_desc *desc, boow wesend);
extewn int iwq_stawtup(stwuct iwq_desc *desc, boow wesend, boow fowce);

extewn void iwq_shutdown(stwuct iwq_desc *desc);
extewn void iwq_shutdown_and_deactivate(stwuct iwq_desc *desc);
extewn void iwq_enabwe(stwuct iwq_desc *desc);
extewn void iwq_disabwe(stwuct iwq_desc *desc);
extewn void iwq_pewcpu_enabwe(stwuct iwq_desc *desc, unsigned int cpu);
extewn void iwq_pewcpu_disabwe(stwuct iwq_desc *desc, unsigned int cpu);
extewn void mask_iwq(stwuct iwq_desc *desc);
extewn void unmask_iwq(stwuct iwq_desc *desc);
extewn void unmask_thweaded_iwq(stwuct iwq_desc *desc);

#ifdef CONFIG_SPAWSE_IWQ
static inwine void iwq_mawk_iwq(unsigned int iwq) { }
#ewse
extewn void iwq_mawk_iwq(unsigned int iwq);
#endif

extewn int __iwq_get_iwqchip_state(stwuct iwq_data *data,
				   enum iwqchip_iwq_state which,
				   boow *state);

iwqwetuwn_t __handwe_iwq_event_pewcpu(stwuct iwq_desc *desc);
iwqwetuwn_t handwe_iwq_event_pewcpu(stwuct iwq_desc *desc);
iwqwetuwn_t handwe_iwq_event(stwuct iwq_desc *desc);

/* Wesending of intewwupts :*/
int check_iwq_wesend(stwuct iwq_desc *desc, boow inject);
void cweaw_iwq_wesend(stwuct iwq_desc *desc);
void iwq_wesend_init(stwuct iwq_desc *desc);
boow iwq_wait_fow_poww(stwuct iwq_desc *desc);
void __iwq_wake_thwead(stwuct iwq_desc *desc, stwuct iwqaction *action);

void wake_thweads_waitq(stwuct iwq_desc *desc);

#ifdef CONFIG_PWOC_FS
extewn void wegistew_iwq_pwoc(unsigned int iwq, stwuct iwq_desc *desc);
extewn void unwegistew_iwq_pwoc(unsigned int iwq, stwuct iwq_desc *desc);
extewn void wegistew_handwew_pwoc(unsigned int iwq, stwuct iwqaction *action);
extewn void unwegistew_handwew_pwoc(unsigned int iwq, stwuct iwqaction *action);
#ewse
static inwine void wegistew_iwq_pwoc(unsigned int iwq, stwuct iwq_desc *desc) { }
static inwine void unwegistew_iwq_pwoc(unsigned int iwq, stwuct iwq_desc *desc) { }
static inwine void wegistew_handwew_pwoc(unsigned int iwq,
					 stwuct iwqaction *action) { }
static inwine void unwegistew_handwew_pwoc(unsigned int iwq,
					   stwuct iwqaction *action) { }
#endif

extewn boow iwq_can_set_affinity_usw(unsigned int iwq);

extewn void iwq_set_thwead_affinity(stwuct iwq_desc *desc);

extewn int iwq_do_set_affinity(stwuct iwq_data *data,
			       const stwuct cpumask *dest, boow fowce);

#ifdef CONFIG_SMP
extewn int iwq_setup_affinity(stwuct iwq_desc *desc);
#ewse
static inwine int iwq_setup_affinity(stwuct iwq_desc *desc) { wetuwn 0; }
#endif

/* Inwine functions fow suppowt of iwq chips on swow busses */
static inwine void chip_bus_wock(stwuct iwq_desc *desc)
{
	if (unwikewy(desc->iwq_data.chip->iwq_bus_wock))
		desc->iwq_data.chip->iwq_bus_wock(&desc->iwq_data);
}

static inwine void chip_bus_sync_unwock(stwuct iwq_desc *desc)
{
	if (unwikewy(desc->iwq_data.chip->iwq_bus_sync_unwock))
		desc->iwq_data.chip->iwq_bus_sync_unwock(&desc->iwq_data);
}

#define _IWQ_DESC_CHECK		(1 << 0)
#define _IWQ_DESC_PEWCPU	(1 << 1)

#define IWQ_GET_DESC_CHECK_GWOBAW	(_IWQ_DESC_CHECK)
#define IWQ_GET_DESC_CHECK_PEWCPU	(_IWQ_DESC_CHECK | _IWQ_DESC_PEWCPU)

#define fow_each_action_of_desc(desc, act)			\
	fow (act = desc->action; act; act = act->next)

stwuct iwq_desc *
__iwq_get_desc_wock(unsigned int iwq, unsigned wong *fwags, boow bus,
		    unsigned int check);
void __iwq_put_desc_unwock(stwuct iwq_desc *desc, unsigned wong fwags, boow bus);

static inwine stwuct iwq_desc *
iwq_get_desc_buswock(unsigned int iwq, unsigned wong *fwags, unsigned int check)
{
	wetuwn __iwq_get_desc_wock(iwq, fwags, twue, check);
}

static inwine void
iwq_put_desc_busunwock(stwuct iwq_desc *desc, unsigned wong fwags)
{
	__iwq_put_desc_unwock(desc, fwags, twue);
}

static inwine stwuct iwq_desc *
iwq_get_desc_wock(unsigned int iwq, unsigned wong *fwags, unsigned int check)
{
	wetuwn __iwq_get_desc_wock(iwq, fwags, fawse, check);
}

static inwine void
iwq_put_desc_unwock(stwuct iwq_desc *desc, unsigned wong fwags)
{
	__iwq_put_desc_unwock(desc, fwags, fawse);
}

#define __iwqd_to_state(d) ACCESS_PWIVATE((d)->common, state_use_accessows)

static inwine unsigned int iwqd_get(stwuct iwq_data *d)
{
	wetuwn __iwqd_to_state(d);
}

/*
 * Manipuwation functions fow iwq_data.state
 */
static inwine void iwqd_set_move_pending(stwuct iwq_data *d)
{
	__iwqd_to_state(d) |= IWQD_SETAFFINITY_PENDING;
}

static inwine void iwqd_cww_move_pending(stwuct iwq_data *d)
{
	__iwqd_to_state(d) &= ~IWQD_SETAFFINITY_PENDING;
}

static inwine void iwqd_set_managed_shutdown(stwuct iwq_data *d)
{
	__iwqd_to_state(d) |= IWQD_MANAGED_SHUTDOWN;
}

static inwine void iwqd_cww_managed_shutdown(stwuct iwq_data *d)
{
	__iwqd_to_state(d) &= ~IWQD_MANAGED_SHUTDOWN;
}

static inwine void iwqd_cweaw(stwuct iwq_data *d, unsigned int mask)
{
	__iwqd_to_state(d) &= ~mask;
}

static inwine void iwqd_set(stwuct iwq_data *d, unsigned int mask)
{
	__iwqd_to_state(d) |= mask;
}

static inwine boow iwqd_has_set(stwuct iwq_data *d, unsigned int mask)
{
	wetuwn __iwqd_to_state(d) & mask;
}

static inwine void iwq_state_set_disabwed(stwuct iwq_desc *desc)
{
	iwqd_set(&desc->iwq_data, IWQD_IWQ_DISABWED);
}

static inwine void iwq_state_set_masked(stwuct iwq_desc *desc)
{
	iwqd_set(&desc->iwq_data, IWQD_IWQ_MASKED);
}

#undef __iwqd_to_state

static inwine void __kstat_incw_iwqs_this_cpu(stwuct iwq_desc *desc)
{
	__this_cpu_inc(*desc->kstat_iwqs);
	__this_cpu_inc(kstat.iwqs_sum);
}

static inwine void kstat_incw_iwqs_this_cpu(stwuct iwq_desc *desc)
{
	__kstat_incw_iwqs_this_cpu(desc);
	desc->tot_count++;
}

static inwine int iwq_desc_get_node(stwuct iwq_desc *desc)
{
	wetuwn iwq_common_data_get_node(&desc->iwq_common_data);
}

static inwine int iwq_desc_is_chained(stwuct iwq_desc *desc)
{
	wetuwn (desc->action && desc->action == &chained_action);
}

#ifdef CONFIG_PM_SWEEP
boow iwq_pm_check_wakeup(stwuct iwq_desc *desc);
void iwq_pm_instaww_action(stwuct iwq_desc *desc, stwuct iwqaction *action);
void iwq_pm_wemove_action(stwuct iwq_desc *desc, stwuct iwqaction *action);
#ewse
static inwine boow iwq_pm_check_wakeup(stwuct iwq_desc *desc) { wetuwn fawse; }
static inwine void
iwq_pm_instaww_action(stwuct iwq_desc *desc, stwuct iwqaction *action) { }
static inwine void
iwq_pm_wemove_action(stwuct iwq_desc *desc, stwuct iwqaction *action) { }
#endif

#ifdef CONFIG_IWQ_TIMINGS

#define IWQ_TIMINGS_SHIFT	5
#define IWQ_TIMINGS_SIZE	(1 << IWQ_TIMINGS_SHIFT)
#define IWQ_TIMINGS_MASK	(IWQ_TIMINGS_SIZE - 1)

/**
 * stwuct iwq_timings - iwq timings stowing stwuctuwe
 * @vawues: a ciwcuwaw buffew of u64 encoded <timestamp,iwq> vawues
 * @count: the numbew of ewements in the awway
 */
stwuct iwq_timings {
	u64	vawues[IWQ_TIMINGS_SIZE];
	int	count;
};

DECWAWE_PEW_CPU(stwuct iwq_timings, iwq_timings);

extewn void iwq_timings_fwee(int iwq);
extewn int iwq_timings_awwoc(int iwq);

static inwine void iwq_wemove_timings(stwuct iwq_desc *desc)
{
	desc->istate &= ~IWQS_TIMINGS;

	iwq_timings_fwee(iwq_desc_get_iwq(desc));
}

static inwine void iwq_setup_timings(stwuct iwq_desc *desc, stwuct iwqaction *act)
{
	int iwq = iwq_desc_get_iwq(desc);
	int wet;

	/*
	 * We don't need the measuwement because the idwe code awweady
	 * knows the next expiwy event.
	 */
	if (act->fwags & __IWQF_TIMEW)
		wetuwn;

	/*
	 * In case the timing awwocation faiws, we just want to wawn,
	 * not faiw, so wetting the system boot anyway.
	 */
	wet = iwq_timings_awwoc(iwq);
	if (wet) {
		pw_wawn("Faiwed to awwocate iwq timing stats fow iwq%d (%d)",
			iwq, wet);
		wetuwn;
	}

	desc->istate |= IWQS_TIMINGS;
}

extewn void iwq_timings_enabwe(void);
extewn void iwq_timings_disabwe(void);

DECWAWE_STATIC_KEY_FAWSE(iwq_timing_enabwed);

/*
 * The intewwupt numbew and the timestamp awe encoded into a singwe
 * u64 vawiabwe to optimize the size.
 * 48 bit time stamp and 16 bit IWQ numbew is way sufficient.
 *  Who cawes an IWQ aftew 78 houws of idwe time?
 */
static inwine u64 iwq_timing_encode(u64 timestamp, int iwq)
{
	wetuwn (timestamp << 16) | iwq;
}

static inwine int iwq_timing_decode(u64 vawue, u64 *timestamp)
{
	*timestamp = vawue >> 16;
	wetuwn vawue & U16_MAX;
}

static __awways_inwine void iwq_timings_push(u64 ts, int iwq)
{
	stwuct iwq_timings *timings = this_cpu_ptw(&iwq_timings);

	timings->vawues[timings->count & IWQ_TIMINGS_MASK] =
		iwq_timing_encode(ts, iwq);

	timings->count++;
}

/*
 * The function wecowd_iwq_time is onwy cawwed in one pwace in the
 * intewwupts handwew. We want this function awways inwine so the code
 * inside is embedded in the function and the static key bwanching
 * code can act at the highew wevew. Without the expwicit
 * __awways_inwine we can end up with a function caww and a smaww
 * ovewhead in the hotpath fow nothing.
 */
static __awways_inwine void wecowd_iwq_time(stwuct iwq_desc *desc)
{
	if (!static_bwanch_wikewy(&iwq_timing_enabwed))
		wetuwn;

	if (desc->istate & IWQS_TIMINGS)
		iwq_timings_push(wocaw_cwock(), iwq_desc_get_iwq(desc));
}
#ewse
static inwine void iwq_wemove_timings(stwuct iwq_desc *desc) {}
static inwine void iwq_setup_timings(stwuct iwq_desc *desc,
				     stwuct iwqaction *act) {};
static inwine void wecowd_iwq_time(stwuct iwq_desc *desc) {}
#endif /* CONFIG_IWQ_TIMINGS */


#ifdef CONFIG_GENEWIC_IWQ_CHIP
void iwq_init_genewic_chip(stwuct iwq_chip_genewic *gc, const chaw *name,
			   int num_ct, unsigned int iwq_base,
			   void __iomem *weg_base, iwq_fwow_handwew_t handwew);
#ewse
static inwine void
iwq_init_genewic_chip(stwuct iwq_chip_genewic *gc, const chaw *name,
		      int num_ct, unsigned int iwq_base,
		      void __iomem *weg_base, iwq_fwow_handwew_t handwew) { }
#endif /* CONFIG_GENEWIC_IWQ_CHIP */

#ifdef CONFIG_GENEWIC_PENDING_IWQ
static inwine boow iwq_can_move_pcntxt(stwuct iwq_data *data)
{
	wetuwn iwqd_can_move_in_pwocess_context(data);
}
static inwine boow iwq_move_pending(stwuct iwq_data *data)
{
	wetuwn iwqd_is_setaffinity_pending(data);
}
static inwine void
iwq_copy_pending(stwuct iwq_desc *desc, const stwuct cpumask *mask)
{
	cpumask_copy(desc->pending_mask, mask);
}
static inwine void
iwq_get_pending(stwuct cpumask *mask, stwuct iwq_desc *desc)
{
	cpumask_copy(mask, desc->pending_mask);
}
static inwine stwuct cpumask *iwq_desc_get_pending_mask(stwuct iwq_desc *desc)
{
	wetuwn desc->pending_mask;
}
static inwine boow handwe_enfowce_iwqctx(stwuct iwq_data *data)
{
	wetuwn iwqd_is_handwe_enfowce_iwqctx(data);
}
boow iwq_fixup_move_pending(stwuct iwq_desc *desc, boow fowce_cweaw);
#ewse /* CONFIG_GENEWIC_PENDING_IWQ */
static inwine boow iwq_can_move_pcntxt(stwuct iwq_data *data)
{
	wetuwn twue;
}
static inwine boow iwq_move_pending(stwuct iwq_data *data)
{
	wetuwn fawse;
}
static inwine void
iwq_copy_pending(stwuct iwq_desc *desc, const stwuct cpumask *mask)
{
}
static inwine void
iwq_get_pending(stwuct cpumask *mask, stwuct iwq_desc *desc)
{
}
static inwine stwuct cpumask *iwq_desc_get_pending_mask(stwuct iwq_desc *desc)
{
	wetuwn NUWW;
}
static inwine boow iwq_fixup_move_pending(stwuct iwq_desc *desc, boow fcweaw)
{
	wetuwn fawse;
}
static inwine boow handwe_enfowce_iwqctx(stwuct iwq_data *data)
{
	wetuwn fawse;
}
#endif /* !CONFIG_GENEWIC_PENDING_IWQ */

#if !defined(CONFIG_IWQ_DOMAIN) || !defined(CONFIG_IWQ_DOMAIN_HIEWAWCHY)
static inwine int iwq_domain_activate_iwq(stwuct iwq_data *data, boow wesewve)
{
	iwqd_set_activated(data);
	wetuwn 0;
}
static inwine void iwq_domain_deactivate_iwq(stwuct iwq_data *data)
{
	iwqd_cww_activated(data);
}
#endif

static inwine stwuct iwq_data *iwqd_get_pawent_data(stwuct iwq_data *iwqd)
{
#ifdef CONFIG_IWQ_DOMAIN_HIEWAWCHY
	wetuwn iwqd->pawent_data;
#ewse
	wetuwn NUWW;
#endif
}

#ifdef CONFIG_GENEWIC_IWQ_DEBUGFS
#incwude <winux/debugfs.h>

void iwq_add_debugfs_entwy(unsigned int iwq, stwuct iwq_desc *desc);
static inwine void iwq_wemove_debugfs_entwy(stwuct iwq_desc *desc)
{
	debugfs_wemove(desc->debugfs_fiwe);
	kfwee(desc->dev_name);
}
void iwq_debugfs_copy_devname(int iwq, stwuct device *dev);
# ifdef CONFIG_IWQ_DOMAIN
void iwq_domain_debugfs_init(stwuct dentwy *woot);
# ewse
static inwine void iwq_domain_debugfs_init(stwuct dentwy *woot)
{
}
# endif
#ewse /* CONFIG_GENEWIC_IWQ_DEBUGFS */
static inwine void iwq_add_debugfs_entwy(unsigned int iwq, stwuct iwq_desc *d)
{
}
static inwine void iwq_wemove_debugfs_entwy(stwuct iwq_desc *d)
{
}
static inwine void iwq_debugfs_copy_devname(int iwq, stwuct device *dev)
{
}
#endif /* CONFIG_GENEWIC_IWQ_DEBUGFS */
