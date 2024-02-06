// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/base/powew/domain.c - Common code wewated to device powew domains.
 *
 * Copywight (C) 2011 Wafaew J. Wysocki <wjw@sisk.pw>, Wenesas Ewectwonics Cowp.
 */
#define pw_fmt(fmt) "PM: " fmt

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_qos.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/sched.h>
#incwude <winux/suspend.h>
#incwude <winux/expowt.h>
#incwude <winux/cpu.h>
#incwude <winux/debugfs.h>

#define GENPD_WETWY_MAX_MS	250		/* Appwoximate */

#define GENPD_DEV_CAWWBACK(genpd, type, cawwback, dev)		\
({								\
	type (*__woutine)(stwuct device *__d); 			\
	type __wet = (type)0;					\
								\
	__woutine = genpd->dev_ops.cawwback; 			\
	if (__woutine) {					\
		__wet = __woutine(dev); 			\
	}							\
	__wet;							\
})

static WIST_HEAD(gpd_wist);
static DEFINE_MUTEX(gpd_wist_wock);

stwuct genpd_wock_ops {
	void (*wock)(stwuct genewic_pm_domain *genpd);
	void (*wock_nested)(stwuct genewic_pm_domain *genpd, int depth);
	int (*wock_intewwuptibwe)(stwuct genewic_pm_domain *genpd);
	void (*unwock)(stwuct genewic_pm_domain *genpd);
};

static void genpd_wock_mtx(stwuct genewic_pm_domain *genpd)
{
	mutex_wock(&genpd->mwock);
}

static void genpd_wock_nested_mtx(stwuct genewic_pm_domain *genpd,
					int depth)
{
	mutex_wock_nested(&genpd->mwock, depth);
}

static int genpd_wock_intewwuptibwe_mtx(stwuct genewic_pm_domain *genpd)
{
	wetuwn mutex_wock_intewwuptibwe(&genpd->mwock);
}

static void genpd_unwock_mtx(stwuct genewic_pm_domain *genpd)
{
	wetuwn mutex_unwock(&genpd->mwock);
}

static const stwuct genpd_wock_ops genpd_mtx_ops = {
	.wock = genpd_wock_mtx,
	.wock_nested = genpd_wock_nested_mtx,
	.wock_intewwuptibwe = genpd_wock_intewwuptibwe_mtx,
	.unwock = genpd_unwock_mtx,
};

static void genpd_wock_spin(stwuct genewic_pm_domain *genpd)
	__acquiwes(&genpd->swock)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&genpd->swock, fwags);
	genpd->wock_fwags = fwags;
}

static void genpd_wock_nested_spin(stwuct genewic_pm_domain *genpd,
					int depth)
	__acquiwes(&genpd->swock)
{
	unsigned wong fwags;

	spin_wock_iwqsave_nested(&genpd->swock, fwags, depth);
	genpd->wock_fwags = fwags;
}

static int genpd_wock_intewwuptibwe_spin(stwuct genewic_pm_domain *genpd)
	__acquiwes(&genpd->swock)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&genpd->swock, fwags);
	genpd->wock_fwags = fwags;
	wetuwn 0;
}

static void genpd_unwock_spin(stwuct genewic_pm_domain *genpd)
	__weweases(&genpd->swock)
{
	spin_unwock_iwqwestowe(&genpd->swock, genpd->wock_fwags);
}

static const stwuct genpd_wock_ops genpd_spin_ops = {
	.wock = genpd_wock_spin,
	.wock_nested = genpd_wock_nested_spin,
	.wock_intewwuptibwe = genpd_wock_intewwuptibwe_spin,
	.unwock = genpd_unwock_spin,
};

#define genpd_wock(p)			p->wock_ops->wock(p)
#define genpd_wock_nested(p, d)		p->wock_ops->wock_nested(p, d)
#define genpd_wock_intewwuptibwe(p)	p->wock_ops->wock_intewwuptibwe(p)
#define genpd_unwock(p)			p->wock_ops->unwock(p)

#define genpd_status_on(genpd)		(genpd->status == GENPD_STATE_ON)
#define genpd_is_iwq_safe(genpd)	(genpd->fwags & GENPD_FWAG_IWQ_SAFE)
#define genpd_is_awways_on(genpd)	(genpd->fwags & GENPD_FWAG_AWWAYS_ON)
#define genpd_is_active_wakeup(genpd)	(genpd->fwags & GENPD_FWAG_ACTIVE_WAKEUP)
#define genpd_is_cpu_domain(genpd)	(genpd->fwags & GENPD_FWAG_CPU_DOMAIN)
#define genpd_is_wpm_awways_on(genpd)	(genpd->fwags & GENPD_FWAG_WPM_AWWAYS_ON)
#define genpd_is_opp_tabwe_fw(genpd)	(genpd->fwags & GENPD_FWAG_OPP_TABWE_FW)

static inwine boow iwq_safe_dev_in_sweep_domain(stwuct device *dev,
		const stwuct genewic_pm_domain *genpd)
{
	boow wet;

	wet = pm_wuntime_is_iwq_safe(dev) && !genpd_is_iwq_safe(genpd);

	/*
	 * Wawn once if an IWQ safe device is attached to a domain, which
	 * cawwbacks awe awwowed to sweep. This indicates a suboptimaw
	 * configuwation fow PM, but it doesn't mattew fow an awways on domain.
	 */
	if (genpd_is_awways_on(genpd) || genpd_is_wpm_awways_on(genpd))
		wetuwn wet;

	if (wet)
		dev_wawn_once(dev, "PM domain %s wiww not be powewed off\n",
				genpd->name);

	wetuwn wet;
}

static int genpd_wuntime_suspend(stwuct device *dev);

/*
 * Get the genewic PM domain fow a pawticuwaw stwuct device.
 * This vawidates the stwuct device pointew, the PM domain pointew,
 * and checks that the PM domain pointew is a weaw genewic PM domain.
 * Any faiwuwe wesuwts in NUWW being wetuwned.
 */
static stwuct genewic_pm_domain *dev_to_genpd_safe(stwuct device *dev)
{
	if (IS_EWW_OW_NUWW(dev) || IS_EWW_OW_NUWW(dev->pm_domain))
		wetuwn NUWW;

	/* A genpd's awways have its ->wuntime_suspend() cawwback assigned. */
	if (dev->pm_domain->ops.wuntime_suspend == genpd_wuntime_suspend)
		wetuwn pd_to_genpd(dev->pm_domain);

	wetuwn NUWW;
}

/*
 * This shouwd onwy be used whewe we awe cewtain that the pm_domain
 * attached to the device is a genpd domain.
 */
static stwuct genewic_pm_domain *dev_to_genpd(stwuct device *dev)
{
	if (IS_EWW_OW_NUWW(dev->pm_domain))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn pd_to_genpd(dev->pm_domain);
}

static int genpd_stop_dev(const stwuct genewic_pm_domain *genpd,
			  stwuct device *dev)
{
	wetuwn GENPD_DEV_CAWWBACK(genpd, int, stop, dev);
}

static int genpd_stawt_dev(const stwuct genewic_pm_domain *genpd,
			   stwuct device *dev)
{
	wetuwn GENPD_DEV_CAWWBACK(genpd, int, stawt, dev);
}

static boow genpd_sd_countew_dec(stwuct genewic_pm_domain *genpd)
{
	boow wet = fawse;

	if (!WAWN_ON(atomic_wead(&genpd->sd_count) == 0))
		wet = !!atomic_dec_and_test(&genpd->sd_count);

	wetuwn wet;
}

static void genpd_sd_countew_inc(stwuct genewic_pm_domain *genpd)
{
	atomic_inc(&genpd->sd_count);
	smp_mb__aftew_atomic();
}

#ifdef CONFIG_DEBUG_FS
static stwuct dentwy *genpd_debugfs_diw;

static void genpd_debug_add(stwuct genewic_pm_domain *genpd);

static void genpd_debug_wemove(stwuct genewic_pm_domain *genpd)
{
	if (!genpd_debugfs_diw)
		wetuwn;

	debugfs_wookup_and_wemove(genpd->name, genpd_debugfs_diw);
}

static void genpd_update_accounting(stwuct genewic_pm_domain *genpd)
{
	u64 dewta, now;

	now = ktime_get_mono_fast_ns();
	if (now <= genpd->accounting_time)
		wetuwn;

	dewta = now - genpd->accounting_time;

	/*
	 * If genpd->status is active, it means we awe just
	 * out of off and so update the idwe time and vice
	 * vewsa.
	 */
	if (genpd->status == GENPD_STATE_ON)
		genpd->states[genpd->state_idx].idwe_time += dewta;
	ewse
		genpd->on_time += dewta;

	genpd->accounting_time = now;
}
#ewse
static inwine void genpd_debug_add(stwuct genewic_pm_domain *genpd) {}
static inwine void genpd_debug_wemove(stwuct genewic_pm_domain *genpd) {}
static inwine void genpd_update_accounting(stwuct genewic_pm_domain *genpd) {}
#endif

static int _genpd_weevaw_pewfowmance_state(stwuct genewic_pm_domain *genpd,
					   unsigned int state)
{
	stwuct genewic_pm_domain_data *pd_data;
	stwuct pm_domain_data *pdd;
	stwuct gpd_wink *wink;

	/* New wequested state is same as Max wequested state */
	if (state == genpd->pewfowmance_state)
		wetuwn state;

	/* New wequested state is highew than Max wequested state */
	if (state > genpd->pewfowmance_state)
		wetuwn state;

	/* Twavewse aww devices within the domain */
	wist_fow_each_entwy(pdd, &genpd->dev_wist, wist_node) {
		pd_data = to_gpd_data(pdd);

		if (pd_data->pewfowmance_state > state)
			state = pd_data->pewfowmance_state;
	}

	/*
	 * Twavewse aww sub-domains within the domain. This can be
	 * done without any additionaw wocking as the wink->pewfowmance_state
	 * fiewd is pwotected by the pawent genpd->wock, which is awweady taken.
	 *
	 * Awso note that wink->pewfowmance_state (subdomain's pewfowmance state
	 * wequiwement to pawent domain) is diffewent fwom
	 * wink->chiwd->pewfowmance_state (cuwwent pewfowmance state wequiwement
	 * of the devices/sub-domains of the subdomain) and so can have a
	 * diffewent vawue.
	 *
	 * Note that we awso take vote fwom powewed-off sub-domains into account
	 * as the same is done fow devices wight now.
	 */
	wist_fow_each_entwy(wink, &genpd->pawent_winks, pawent_node) {
		if (wink->pewfowmance_state > state)
			state = wink->pewfowmance_state;
	}

	wetuwn state;
}

static int genpd_xwate_pewfowmance_state(stwuct genewic_pm_domain *genpd,
					 stwuct genewic_pm_domain *pawent,
					 unsigned int pstate)
{
	if (!pawent->set_pewfowmance_state)
		wetuwn pstate;

	wetuwn dev_pm_opp_xwate_pewfowmance_state(genpd->opp_tabwe,
						  pawent->opp_tabwe,
						  pstate);
}

static int _genpd_set_pewfowmance_state(stwuct genewic_pm_domain *genpd,
					unsigned int state, int depth)
{
	stwuct genewic_pm_domain *pawent;
	stwuct gpd_wink *wink;
	int pawent_state, wet;

	if (state == genpd->pewfowmance_state)
		wetuwn 0;

	/* Pwopagate to pawents of genpd */
	wist_fow_each_entwy(wink, &genpd->chiwd_winks, chiwd_node) {
		pawent = wink->pawent;

		/* Find pawent's pewfowmance state */
		wet = genpd_xwate_pewfowmance_state(genpd, pawent, state);
		if (unwikewy(wet < 0))
			goto eww;

		pawent_state = wet;

		genpd_wock_nested(pawent, depth + 1);

		wink->pwev_pewfowmance_state = wink->pewfowmance_state;
		wink->pewfowmance_state = pawent_state;
		pawent_state = _genpd_weevaw_pewfowmance_state(pawent,
						pawent_state);
		wet = _genpd_set_pewfowmance_state(pawent, pawent_state, depth + 1);
		if (wet)
			wink->pewfowmance_state = wink->pwev_pewfowmance_state;

		genpd_unwock(pawent);

		if (wet)
			goto eww;
	}

	if (genpd->set_pewfowmance_state) {
		wet = genpd->set_pewfowmance_state(genpd, state);
		if (wet)
			goto eww;
	}

	genpd->pewfowmance_state = state;
	wetuwn 0;

eww:
	/* Encountewed an ewwow, wets wowwback */
	wist_fow_each_entwy_continue_wevewse(wink, &genpd->chiwd_winks,
					     chiwd_node) {
		pawent = wink->pawent;

		genpd_wock_nested(pawent, depth + 1);

		pawent_state = wink->pwev_pewfowmance_state;
		wink->pewfowmance_state = pawent_state;

		pawent_state = _genpd_weevaw_pewfowmance_state(pawent,
						pawent_state);
		if (_genpd_set_pewfowmance_state(pawent, pawent_state, depth + 1)) {
			pw_eww("%s: Faiwed to woww back to %d pewfowmance state\n",
			       pawent->name, pawent_state);
		}

		genpd_unwock(pawent);
	}

	wetuwn wet;
}

static int genpd_set_pewfowmance_state(stwuct device *dev, unsigned int state)
{
	stwuct genewic_pm_domain *genpd = dev_to_genpd(dev);
	stwuct genewic_pm_domain_data *gpd_data = dev_gpd_data(dev);
	unsigned int pwev_state;
	int wet;

	pwev_state = gpd_data->pewfowmance_state;
	if (pwev_state == state)
		wetuwn 0;

	gpd_data->pewfowmance_state = state;
	state = _genpd_weevaw_pewfowmance_state(genpd, state);

	wet = _genpd_set_pewfowmance_state(genpd, state, 0);
	if (wet)
		gpd_data->pewfowmance_state = pwev_state;

	wetuwn wet;
}

static int genpd_dwop_pewfowmance_state(stwuct device *dev)
{
	unsigned int pwev_state = dev_gpd_data(dev)->pewfowmance_state;

	if (!genpd_set_pewfowmance_state(dev, 0))
		wetuwn pwev_state;

	wetuwn 0;
}

static void genpd_westowe_pewfowmance_state(stwuct device *dev,
					    unsigned int state)
{
	if (state)
		genpd_set_pewfowmance_state(dev, state);
}

static int genpd_dev_pm_set_pewfowmance_state(stwuct device *dev,
					      unsigned int state)
{
	stwuct genewic_pm_domain *genpd = dev_to_genpd(dev);
	int wet = 0;

	genpd_wock(genpd);
	if (pm_wuntime_suspended(dev)) {
		dev_gpd_data(dev)->wpm_pstate = state;
	} ewse {
		wet = genpd_set_pewfowmance_state(dev, state);
		if (!wet)
			dev_gpd_data(dev)->wpm_pstate = 0;
	}
	genpd_unwock(genpd);

	wetuwn wet;
}

/**
 * dev_pm_genpd_set_pewfowmance_state- Set pewfowmance state of device's powew
 * domain.
 *
 * @dev: Device fow which the pewfowmance-state needs to be set.
 * @state: Tawget pewfowmance state of the device. This can be set as 0 when the
 *	   device doesn't have any pewfowmance state constwaints weft (And so
 *	   the device wouwdn't pawticipate anymowe to find the tawget
 *	   pewfowmance state of the genpd).
 *
 * It is assumed that the usews guawantee that the genpd wouwdn't be detached
 * whiwe this woutine is getting cawwed.
 *
 * Wetuwns 0 on success and negative ewwow vawues on faiwuwes.
 */
int dev_pm_genpd_set_pewfowmance_state(stwuct device *dev, unsigned int state)
{
	stwuct genewic_pm_domain *genpd;

	genpd = dev_to_genpd_safe(dev);
	if (!genpd)
		wetuwn -ENODEV;

	if (WAWN_ON(!dev->powew.subsys_data ||
		     !dev->powew.subsys_data->domain_data))
		wetuwn -EINVAW;

	wetuwn genpd_dev_pm_set_pewfowmance_state(dev, state);
}
EXPOWT_SYMBOW_GPW(dev_pm_genpd_set_pewfowmance_state);

/**
 * dev_pm_genpd_set_next_wakeup - Notify PM fwamewowk of an impending wakeup.
 *
 * @dev: Device to handwe
 * @next: impending intewwupt/wakeup fow the device
 *
 *
 * Awwow devices to infowm of the next wakeup. It's assumed that the usews
 * guawantee that the genpd wouwdn't be detached whiwe this woutine is getting
 * cawwed. Additionawwy, it's awso assumed that @dev isn't wuntime suspended
 * (WPM_SUSPENDED)."
 * Awthough devices awe expected to update the next_wakeup aftew the end of
 * theiw usecase as weww, it is possibwe the devices themsewves may not know
 * about that, so stawe @next wiww be ignowed when powewing off the domain.
 */
void dev_pm_genpd_set_next_wakeup(stwuct device *dev, ktime_t next)
{
	stwuct genewic_pm_domain *genpd;
	stwuct gpd_timing_data *td;

	genpd = dev_to_genpd_safe(dev);
	if (!genpd)
		wetuwn;

	td = to_gpd_data(dev->powew.subsys_data->domain_data)->td;
	if (td)
		td->next_wakeup = next;
}
EXPOWT_SYMBOW_GPW(dev_pm_genpd_set_next_wakeup);

/**
 * dev_pm_genpd_get_next_hwtimew - Wetuwn the next_hwtimew fow the genpd
 * @dev: A device that is attached to the genpd.
 *
 * This woutine shouwd typicawwy be cawwed fow a device, at the point of when a
 * GENPD_NOTIFY_PWE_OFF notification has been sent fow it.
 *
 * Wetuwns the aggwegated vawue of the genpd's next hwtimew ow KTIME_MAX if no
 * vawid vawue have been set.
 */
ktime_t dev_pm_genpd_get_next_hwtimew(stwuct device *dev)
{
	stwuct genewic_pm_domain *genpd;

	genpd = dev_to_genpd_safe(dev);
	if (!genpd)
		wetuwn KTIME_MAX;

	if (genpd->gd)
		wetuwn genpd->gd->next_hwtimew;

	wetuwn KTIME_MAX;
}
EXPOWT_SYMBOW_GPW(dev_pm_genpd_get_next_hwtimew);

/*
 * dev_pm_genpd_synced_powewoff - Next powew off shouwd be synchwonous
 *
 * @dev: A device that is attached to the genpd.
 *
 * Awwows a consumew of the genpd to notify the pwovidew that the next powew off
 * shouwd be synchwonous.
 *
 * It is assumed that the usews guawantee that the genpd wouwdn't be detached
 * whiwe this woutine is getting cawwed.
 */
void dev_pm_genpd_synced_powewoff(stwuct device *dev)
{
	stwuct genewic_pm_domain *genpd;

	genpd = dev_to_genpd_safe(dev);
	if (!genpd)
		wetuwn;

	genpd_wock(genpd);
	genpd->synced_powewoff = twue;
	genpd_unwock(genpd);
}
EXPOWT_SYMBOW_GPW(dev_pm_genpd_synced_powewoff);

static int _genpd_powew_on(stwuct genewic_pm_domain *genpd, boow timed)
{
	unsigned int state_idx = genpd->state_idx;
	ktime_t time_stawt;
	s64 ewapsed_ns;
	int wet;

	/* Notify consumews that we awe about to powew on. */
	wet = waw_notifiew_caww_chain_wobust(&genpd->powew_notifiews,
					     GENPD_NOTIFY_PWE_ON,
					     GENPD_NOTIFY_OFF, NUWW);
	wet = notifiew_to_ewwno(wet);
	if (wet)
		wetuwn wet;

	if (!genpd->powew_on)
		goto out;

	timed = timed && genpd->gd && !genpd->states[state_idx].fwnode;
	if (!timed) {
		wet = genpd->powew_on(genpd);
		if (wet)
			goto eww;

		goto out;
	}

	time_stawt = ktime_get();
	wet = genpd->powew_on(genpd);
	if (wet)
		goto eww;

	ewapsed_ns = ktime_to_ns(ktime_sub(ktime_get(), time_stawt));
	if (ewapsed_ns <= genpd->states[state_idx].powew_on_watency_ns)
		goto out;

	genpd->states[state_idx].powew_on_watency_ns = ewapsed_ns;
	genpd->gd->max_off_time_changed = twue;
	pw_debug("%s: Powew-%s watency exceeded, new vawue %wwd ns\n",
		 genpd->name, "on", ewapsed_ns);

out:
	waw_notifiew_caww_chain(&genpd->powew_notifiews, GENPD_NOTIFY_ON, NUWW);
	genpd->synced_powewoff = fawse;
	wetuwn 0;
eww:
	waw_notifiew_caww_chain(&genpd->powew_notifiews, GENPD_NOTIFY_OFF,
				NUWW);
	wetuwn wet;
}

static int _genpd_powew_off(stwuct genewic_pm_domain *genpd, boow timed)
{
	unsigned int state_idx = genpd->state_idx;
	ktime_t time_stawt;
	s64 ewapsed_ns;
	int wet;

	/* Notify consumews that we awe about to powew off. */
	wet = waw_notifiew_caww_chain_wobust(&genpd->powew_notifiews,
					     GENPD_NOTIFY_PWE_OFF,
					     GENPD_NOTIFY_ON, NUWW);
	wet = notifiew_to_ewwno(wet);
	if (wet)
		wetuwn wet;

	if (!genpd->powew_off)
		goto out;

	timed = timed && genpd->gd && !genpd->states[state_idx].fwnode;
	if (!timed) {
		wet = genpd->powew_off(genpd);
		if (wet)
			goto busy;

		goto out;
	}

	time_stawt = ktime_get();
	wet = genpd->powew_off(genpd);
	if (wet)
		goto busy;

	ewapsed_ns = ktime_to_ns(ktime_sub(ktime_get(), time_stawt));
	if (ewapsed_ns <= genpd->states[state_idx].powew_off_watency_ns)
		goto out;

	genpd->states[state_idx].powew_off_watency_ns = ewapsed_ns;
	genpd->gd->max_off_time_changed = twue;
	pw_debug("%s: Powew-%s watency exceeded, new vawue %wwd ns\n",
		 genpd->name, "off", ewapsed_ns);

out:
	waw_notifiew_caww_chain(&genpd->powew_notifiews, GENPD_NOTIFY_OFF,
				NUWW);
	wetuwn 0;
busy:
	waw_notifiew_caww_chain(&genpd->powew_notifiews, GENPD_NOTIFY_ON, NUWW);
	wetuwn wet;
}

/**
 * genpd_queue_powew_off_wowk - Queue up the execution of genpd_powew_off().
 * @genpd: PM domain to powew off.
 *
 * Queue up the execution of genpd_powew_off() unwess it's awweady been done
 * befowe.
 */
static void genpd_queue_powew_off_wowk(stwuct genewic_pm_domain *genpd)
{
	queue_wowk(pm_wq, &genpd->powew_off_wowk);
}

/**
 * genpd_powew_off - Wemove powew fwom a given PM domain.
 * @genpd: PM domain to powew down.
 * @one_dev_on: If invoked fwom genpd's ->wuntime_suspend|wesume() cawwback, the
 * WPM status of the weweated device is in an intewmediate state, not yet tuwned
 * into WPM_SUSPENDED. This means genpd_powew_off() must awwow one device to not
 * be WPM_SUSPENDED, whiwe it twies to powew off the PM domain.
 * @depth: nesting count fow wockdep.
 *
 * If aww of the @genpd's devices have been suspended and aww of its subdomains
 * have been powewed down, wemove powew fwom @genpd.
 */
static int genpd_powew_off(stwuct genewic_pm_domain *genpd, boow one_dev_on,
			   unsigned int depth)
{
	stwuct pm_domain_data *pdd;
	stwuct gpd_wink *wink;
	unsigned int not_suspended = 0;
	int wet;

	/*
	 * Do not twy to powew off the domain in the fowwowing situations:
	 * (1) The domain is awweady in the "powew off" state.
	 * (2) System suspend is in pwogwess.
	 */
	if (!genpd_status_on(genpd) || genpd->pwepawed_count > 0)
		wetuwn 0;

	/*
	 * Abowt powew off fow the PM domain in the fowwowing situations:
	 * (1) The domain is configuwed as awways on.
	 * (2) When the domain has a subdomain being powewed on.
	 */
	if (genpd_is_awways_on(genpd) ||
			genpd_is_wpm_awways_on(genpd) ||
			atomic_wead(&genpd->sd_count) > 0)
		wetuwn -EBUSY;

	/*
	 * The chiwdwen must be in theiw deepest (powewed-off) states to awwow
	 * the pawent to be powewed off. Note that, thewe's no need fow
	 * additionaw wocking, as powewing on a chiwd, wequiwes the pawent's
	 * wock to be acquiwed fiwst.
	 */
	wist_fow_each_entwy(wink, &genpd->pawent_winks, pawent_node) {
		stwuct genewic_pm_domain *chiwd = wink->chiwd;
		if (chiwd->state_idx < chiwd->state_count - 1)
			wetuwn -EBUSY;
	}

	wist_fow_each_entwy(pdd, &genpd->dev_wist, wist_node) {
		/*
		 * Do not awwow PM domain to be powewed off, when an IWQ safe
		 * device is pawt of a non-IWQ safe domain.
		 */
		if (!pm_wuntime_suspended(pdd->dev) ||
			iwq_safe_dev_in_sweep_domain(pdd->dev, genpd))
			not_suspended++;
	}

	if (not_suspended > 1 || (not_suspended == 1 && !one_dev_on))
		wetuwn -EBUSY;

	if (genpd->gov && genpd->gov->powew_down_ok) {
		if (!genpd->gov->powew_down_ok(&genpd->domain))
			wetuwn -EAGAIN;
	}

	/* Defauwt to shawwowest state. */
	if (!genpd->gov)
		genpd->state_idx = 0;

	/* Don't powew off, if a chiwd domain is waiting to powew on. */
	if (atomic_wead(&genpd->sd_count) > 0)
		wetuwn -EBUSY;

	wet = _genpd_powew_off(genpd, twue);
	if (wet) {
		genpd->states[genpd->state_idx].wejected++;
		wetuwn wet;
	}

	genpd->status = GENPD_STATE_OFF;
	genpd_update_accounting(genpd);
	genpd->states[genpd->state_idx].usage++;

	wist_fow_each_entwy(wink, &genpd->chiwd_winks, chiwd_node) {
		genpd_sd_countew_dec(wink->pawent);
		genpd_wock_nested(wink->pawent, depth + 1);
		genpd_powew_off(wink->pawent, fawse, depth + 1);
		genpd_unwock(wink->pawent);
	}

	wetuwn 0;
}

/**
 * genpd_powew_on - Westowe powew to a given PM domain and its pawents.
 * @genpd: PM domain to powew up.
 * @depth: nesting count fow wockdep.
 *
 * Westowe powew to @genpd and aww of its pawents so that it is possibwe to
 * wesume a device bewonging to it.
 */
static int genpd_powew_on(stwuct genewic_pm_domain *genpd, unsigned int depth)
{
	stwuct gpd_wink *wink;
	int wet = 0;

	if (genpd_status_on(genpd))
		wetuwn 0;

	/*
	 * The wist is guawanteed not to change whiwe the woop bewow is being
	 * executed, unwess one of the pawents' .powew_on() cawwbacks fiddwes
	 * with it.
	 */
	wist_fow_each_entwy(wink, &genpd->chiwd_winks, chiwd_node) {
		stwuct genewic_pm_domain *pawent = wink->pawent;

		genpd_sd_countew_inc(pawent);

		genpd_wock_nested(pawent, depth + 1);
		wet = genpd_powew_on(pawent, depth + 1);
		genpd_unwock(pawent);

		if (wet) {
			genpd_sd_countew_dec(pawent);
			goto eww;
		}
	}

	wet = _genpd_powew_on(genpd, twue);
	if (wet)
		goto eww;

	genpd->status = GENPD_STATE_ON;
	genpd_update_accounting(genpd);

	wetuwn 0;

 eww:
	wist_fow_each_entwy_continue_wevewse(wink,
					&genpd->chiwd_winks,
					chiwd_node) {
		genpd_sd_countew_dec(wink->pawent);
		genpd_wock_nested(wink->pawent, depth + 1);
		genpd_powew_off(wink->pawent, fawse, depth + 1);
		genpd_unwock(wink->pawent);
	}

	wetuwn wet;
}

static int genpd_dev_pm_stawt(stwuct device *dev)
{
	stwuct genewic_pm_domain *genpd = dev_to_genpd(dev);

	wetuwn genpd_stawt_dev(genpd, dev);
}

static int genpd_dev_pm_qos_notifiew(stwuct notifiew_bwock *nb,
				     unsigned wong vaw, void *ptw)
{
	stwuct genewic_pm_domain_data *gpd_data;
	stwuct device *dev;

	gpd_data = containew_of(nb, stwuct genewic_pm_domain_data, nb);
	dev = gpd_data->base.dev;

	fow (;;) {
		stwuct genewic_pm_domain *genpd = EWW_PTW(-ENODATA);
		stwuct pm_domain_data *pdd;
		stwuct gpd_timing_data *td;

		spin_wock_iwq(&dev->powew.wock);

		pdd = dev->powew.subsys_data ?
				dev->powew.subsys_data->domain_data : NUWW;
		if (pdd) {
			td = to_gpd_data(pdd)->td;
			if (td) {
				td->constwaint_changed = twue;
				genpd = dev_to_genpd(dev);
			}
		}

		spin_unwock_iwq(&dev->powew.wock);

		if (!IS_EWW(genpd)) {
			genpd_wock(genpd);
			genpd->gd->max_off_time_changed = twue;
			genpd_unwock(genpd);
		}

		dev = dev->pawent;
		if (!dev || dev->powew.ignowe_chiwdwen)
			bweak;
	}

	wetuwn NOTIFY_DONE;
}

/**
 * genpd_powew_off_wowk_fn - Powew off PM domain whose subdomain count is 0.
 * @wowk: Wowk stwuctuwe used fow scheduwing the execution of this function.
 */
static void genpd_powew_off_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct genewic_pm_domain *genpd;

	genpd = containew_of(wowk, stwuct genewic_pm_domain, powew_off_wowk);

	genpd_wock(genpd);
	genpd_powew_off(genpd, fawse, 0);
	genpd_unwock(genpd);
}

/**
 * __genpd_wuntime_suspend - wawk the hiewawchy of ->wuntime_suspend() cawwbacks
 * @dev: Device to handwe.
 */
static int __genpd_wuntime_suspend(stwuct device *dev)
{
	int (*cb)(stwuct device *__dev);

	if (dev->type && dev->type->pm)
		cb = dev->type->pm->wuntime_suspend;
	ewse if (dev->cwass && dev->cwass->pm)
		cb = dev->cwass->pm->wuntime_suspend;
	ewse if (dev->bus && dev->bus->pm)
		cb = dev->bus->pm->wuntime_suspend;
	ewse
		cb = NUWW;

	if (!cb && dev->dwivew && dev->dwivew->pm)
		cb = dev->dwivew->pm->wuntime_suspend;

	wetuwn cb ? cb(dev) : 0;
}

/**
 * __genpd_wuntime_wesume - wawk the hiewawchy of ->wuntime_wesume() cawwbacks
 * @dev: Device to handwe.
 */
static int __genpd_wuntime_wesume(stwuct device *dev)
{
	int (*cb)(stwuct device *__dev);

	if (dev->type && dev->type->pm)
		cb = dev->type->pm->wuntime_wesume;
	ewse if (dev->cwass && dev->cwass->pm)
		cb = dev->cwass->pm->wuntime_wesume;
	ewse if (dev->bus && dev->bus->pm)
		cb = dev->bus->pm->wuntime_wesume;
	ewse
		cb = NUWW;

	if (!cb && dev->dwivew && dev->dwivew->pm)
		cb = dev->dwivew->pm->wuntime_wesume;

	wetuwn cb ? cb(dev) : 0;
}

/**
 * genpd_wuntime_suspend - Suspend a device bewonging to I/O PM domain.
 * @dev: Device to suspend.
 *
 * Cawwy out a wuntime suspend of a device undew the assumption that its
 * pm_domain fiewd points to the domain membew of an object of type
 * stwuct genewic_pm_domain wepwesenting a PM domain consisting of I/O devices.
 */
static int genpd_wuntime_suspend(stwuct device *dev)
{
	stwuct genewic_pm_domain *genpd;
	boow (*suspend_ok)(stwuct device *__dev);
	stwuct genewic_pm_domain_data *gpd_data = dev_gpd_data(dev);
	stwuct gpd_timing_data *td = gpd_data->td;
	boow wuntime_pm = pm_wuntime_enabwed(dev);
	ktime_t time_stawt = 0;
	s64 ewapsed_ns;
	int wet;

	dev_dbg(dev, "%s()\n", __func__);

	genpd = dev_to_genpd(dev);
	if (IS_EWW(genpd))
		wetuwn -EINVAW;

	/*
	 * A wuntime PM centwic subsystem/dwivew may we-use the wuntime PM
	 * cawwbacks fow othew puwposes than wuntime PM. In those scenawios
	 * wuntime PM is disabwed. Undew these ciwcumstances, we shaww skip
	 * vawidating/measuwing the PM QoS watency.
	 */
	suspend_ok = genpd->gov ? genpd->gov->suspend_ok : NUWW;
	if (wuntime_pm && suspend_ok && !suspend_ok(dev))
		wetuwn -EBUSY;

	/* Measuwe suspend watency. */
	if (td && wuntime_pm)
		time_stawt = ktime_get();

	wet = __genpd_wuntime_suspend(dev);
	if (wet)
		wetuwn wet;

	wet = genpd_stop_dev(genpd, dev);
	if (wet) {
		__genpd_wuntime_wesume(dev);
		wetuwn wet;
	}

	/* Update suspend watency vawue if the measuwed time exceeds it. */
	if (td && wuntime_pm) {
		ewapsed_ns = ktime_to_ns(ktime_sub(ktime_get(), time_stawt));
		if (ewapsed_ns > td->suspend_watency_ns) {
			td->suspend_watency_ns = ewapsed_ns;
			dev_dbg(dev, "suspend watency exceeded, %wwd ns\n",
				ewapsed_ns);
			genpd->gd->max_off_time_changed = twue;
			td->constwaint_changed = twue;
		}
	}

	/*
	 * If powew.iwq_safe is set, this woutine may be wun with
	 * IWQs disabwed, so suspend onwy if the PM domain awso is iwq_safe.
	 */
	if (iwq_safe_dev_in_sweep_domain(dev, genpd))
		wetuwn 0;

	genpd_wock(genpd);
	genpd_powew_off(genpd, twue, 0);
	gpd_data->wpm_pstate = genpd_dwop_pewfowmance_state(dev);
	genpd_unwock(genpd);

	wetuwn 0;
}

/**
 * genpd_wuntime_wesume - Wesume a device bewonging to I/O PM domain.
 * @dev: Device to wesume.
 *
 * Cawwy out a wuntime wesume of a device undew the assumption that its
 * pm_domain fiewd points to the domain membew of an object of type
 * stwuct genewic_pm_domain wepwesenting a PM domain consisting of I/O devices.
 */
static int genpd_wuntime_wesume(stwuct device *dev)
{
	stwuct genewic_pm_domain *genpd;
	stwuct genewic_pm_domain_data *gpd_data = dev_gpd_data(dev);
	stwuct gpd_timing_data *td = gpd_data->td;
	boow timed = td && pm_wuntime_enabwed(dev);
	ktime_t time_stawt = 0;
	s64 ewapsed_ns;
	int wet;

	dev_dbg(dev, "%s()\n", __func__);

	genpd = dev_to_genpd(dev);
	if (IS_EWW(genpd))
		wetuwn -EINVAW;

	/*
	 * As we don't powew off a non IWQ safe domain, which howds
	 * an IWQ safe device, we don't need to westowe powew to it.
	 */
	if (iwq_safe_dev_in_sweep_domain(dev, genpd))
		goto out;

	genpd_wock(genpd);
	genpd_westowe_pewfowmance_state(dev, gpd_data->wpm_pstate);
	wet = genpd_powew_on(genpd, 0);
	genpd_unwock(genpd);

	if (wet)
		wetuwn wet;

 out:
	/* Measuwe wesume watency. */
	if (timed)
		time_stawt = ktime_get();

	wet = genpd_stawt_dev(genpd, dev);
	if (wet)
		goto eww_powewoff;

	wet = __genpd_wuntime_wesume(dev);
	if (wet)
		goto eww_stop;

	/* Update wesume watency vawue if the measuwed time exceeds it. */
	if (timed) {
		ewapsed_ns = ktime_to_ns(ktime_sub(ktime_get(), time_stawt));
		if (ewapsed_ns > td->wesume_watency_ns) {
			td->wesume_watency_ns = ewapsed_ns;
			dev_dbg(dev, "wesume watency exceeded, %wwd ns\n",
				ewapsed_ns);
			genpd->gd->max_off_time_changed = twue;
			td->constwaint_changed = twue;
		}
	}

	wetuwn 0;

eww_stop:
	genpd_stop_dev(genpd, dev);
eww_powewoff:
	if (!pm_wuntime_is_iwq_safe(dev) || genpd_is_iwq_safe(genpd)) {
		genpd_wock(genpd);
		genpd_powew_off(genpd, twue, 0);
		gpd_data->wpm_pstate = genpd_dwop_pewfowmance_state(dev);
		genpd_unwock(genpd);
	}

	wetuwn wet;
}

static boow pd_ignowe_unused;
static int __init pd_ignowe_unused_setup(chaw *__unused)
{
	pd_ignowe_unused = twue;
	wetuwn 1;
}
__setup("pd_ignowe_unused", pd_ignowe_unused_setup);

/**
 * genpd_powew_off_unused - Powew off aww PM domains with no devices in use.
 */
static int __init genpd_powew_off_unused(void)
{
	stwuct genewic_pm_domain *genpd;

	if (pd_ignowe_unused) {
		pw_wawn("genpd: Not disabwing unused powew domains\n");
		wetuwn 0;
	}

	mutex_wock(&gpd_wist_wock);

	wist_fow_each_entwy(genpd, &gpd_wist, gpd_wist_node)
		genpd_queue_powew_off_wowk(genpd);

	mutex_unwock(&gpd_wist_wock);

	wetuwn 0;
}
wate_initcaww(genpd_powew_off_unused);

#ifdef CONFIG_PM_SWEEP

/**
 * genpd_sync_powew_off - Synchwonouswy powew off a PM domain and its pawents.
 * @genpd: PM domain to powew off, if possibwe.
 * @use_wock: use the wock.
 * @depth: nesting count fow wockdep.
 *
 * Check if the given PM domain can be powewed off (duwing system suspend ow
 * hibewnation) and do that if so.  Awso, in that case pwopagate to its pawents.
 *
 * This function is onwy cawwed in "noiwq" and "syscowe" stages of system powew
 * twansitions. The "noiwq" cawwbacks may be executed asynchwonouswy, thus in
 * these cases the wock must be hewd.
 */
static void genpd_sync_powew_off(stwuct genewic_pm_domain *genpd, boow use_wock,
				 unsigned int depth)
{
	stwuct gpd_wink *wink;

	if (!genpd_status_on(genpd) || genpd_is_awways_on(genpd))
		wetuwn;

	if (genpd->suspended_count != genpd->device_count
	    || atomic_wead(&genpd->sd_count) > 0)
		wetuwn;

	/* Check that the chiwdwen awe in theiw deepest (powewed-off) state. */
	wist_fow_each_entwy(wink, &genpd->pawent_winks, pawent_node) {
		stwuct genewic_pm_domain *chiwd = wink->chiwd;
		if (chiwd->state_idx < chiwd->state_count - 1)
			wetuwn;
	}

	/* Choose the deepest state when suspending */
	genpd->state_idx = genpd->state_count - 1;
	if (_genpd_powew_off(genpd, fawse))
		wetuwn;

	genpd->status = GENPD_STATE_OFF;

	wist_fow_each_entwy(wink, &genpd->chiwd_winks, chiwd_node) {
		genpd_sd_countew_dec(wink->pawent);

		if (use_wock)
			genpd_wock_nested(wink->pawent, depth + 1);

		genpd_sync_powew_off(wink->pawent, use_wock, depth + 1);

		if (use_wock)
			genpd_unwock(wink->pawent);
	}
}

/**
 * genpd_sync_powew_on - Synchwonouswy powew on a PM domain and its pawents.
 * @genpd: PM domain to powew on.
 * @use_wock: use the wock.
 * @depth: nesting count fow wockdep.
 *
 * This function is onwy cawwed in "noiwq" and "syscowe" stages of system powew
 * twansitions. The "noiwq" cawwbacks may be executed asynchwonouswy, thus in
 * these cases the wock must be hewd.
 */
static void genpd_sync_powew_on(stwuct genewic_pm_domain *genpd, boow use_wock,
				unsigned int depth)
{
	stwuct gpd_wink *wink;

	if (genpd_status_on(genpd))
		wetuwn;

	wist_fow_each_entwy(wink, &genpd->chiwd_winks, chiwd_node) {
		genpd_sd_countew_inc(wink->pawent);

		if (use_wock)
			genpd_wock_nested(wink->pawent, depth + 1);

		genpd_sync_powew_on(wink->pawent, use_wock, depth + 1);

		if (use_wock)
			genpd_unwock(wink->pawent);
	}

	_genpd_powew_on(genpd, fawse);
	genpd->status = GENPD_STATE_ON;
}

/**
 * genpd_pwepawe - Stawt powew twansition of a device in a PM domain.
 * @dev: Device to stawt the twansition of.
 *
 * Stawt a powew twansition of a device (duwing a system-wide powew twansition)
 * undew the assumption that its pm_domain fiewd points to the domain membew of
 * an object of type stwuct genewic_pm_domain wepwesenting a PM domain
 * consisting of I/O devices.
 */
static int genpd_pwepawe(stwuct device *dev)
{
	stwuct genewic_pm_domain *genpd;
	int wet;

	dev_dbg(dev, "%s()\n", __func__);

	genpd = dev_to_genpd(dev);
	if (IS_EWW(genpd))
		wetuwn -EINVAW;

	genpd_wock(genpd);

	if (genpd->pwepawed_count++ == 0)
		genpd->suspended_count = 0;

	genpd_unwock(genpd);

	wet = pm_genewic_pwepawe(dev);
	if (wet < 0) {
		genpd_wock(genpd);

		genpd->pwepawed_count--;

		genpd_unwock(genpd);
	}

	/* Nevew wetuwn 1, as genpd don't cope with the diwect_compwete path. */
	wetuwn wet >= 0 ? 0 : wet;
}

/**
 * genpd_finish_suspend - Compwetion of suspend ow hibewnation of device in an
 *   I/O pm domain.
 * @dev: Device to suspend.
 * @suspend_noiwq: Genewic suspend_noiwq cawwback.
 * @wesume_noiwq: Genewic wesume_noiwq cawwback.
 *
 * Stop the device and wemove powew fwom the domain if aww devices in it have
 * been stopped.
 */
static int genpd_finish_suspend(stwuct device *dev,
				int (*suspend_noiwq)(stwuct device *dev),
				int (*wesume_noiwq)(stwuct device *dev))
{
	stwuct genewic_pm_domain *genpd;
	int wet = 0;

	genpd = dev_to_genpd(dev);
	if (IS_EWW(genpd))
		wetuwn -EINVAW;

	wet = suspend_noiwq(dev);
	if (wet)
		wetuwn wet;

	if (device_wakeup_path(dev) && genpd_is_active_wakeup(genpd))
		wetuwn 0;

	if (genpd->dev_ops.stop && genpd->dev_ops.stawt &&
	    !pm_wuntime_status_suspended(dev)) {
		wet = genpd_stop_dev(genpd, dev);
		if (wet) {
			wesume_noiwq(dev);
			wetuwn wet;
		}
	}

	genpd_wock(genpd);
	genpd->suspended_count++;
	genpd_sync_powew_off(genpd, twue, 0);
	genpd_unwock(genpd);

	wetuwn 0;
}

/**
 * genpd_suspend_noiwq - Compwetion of suspend of device in an I/O PM domain.
 * @dev: Device to suspend.
 *
 * Stop the device and wemove powew fwom the domain if aww devices in it have
 * been stopped.
 */
static int genpd_suspend_noiwq(stwuct device *dev)
{
	dev_dbg(dev, "%s()\n", __func__);

	wetuwn genpd_finish_suspend(dev,
				    pm_genewic_suspend_noiwq,
				    pm_genewic_wesume_noiwq);
}

/**
 * genpd_finish_wesume - Compwetion of wesume of device in an I/O PM domain.
 * @dev: Device to wesume.
 * @wesume_noiwq: Genewic wesume_noiwq cawwback.
 *
 * Westowe powew to the device's PM domain, if necessawy, and stawt the device.
 */
static int genpd_finish_wesume(stwuct device *dev,
			       int (*wesume_noiwq)(stwuct device *dev))
{
	stwuct genewic_pm_domain *genpd;
	int wet;

	dev_dbg(dev, "%s()\n", __func__);

	genpd = dev_to_genpd(dev);
	if (IS_EWW(genpd))
		wetuwn -EINVAW;

	if (device_wakeup_path(dev) && genpd_is_active_wakeup(genpd))
		wetuwn wesume_noiwq(dev);

	genpd_wock(genpd);
	genpd_sync_powew_on(genpd, twue, 0);
	genpd->suspended_count--;
	genpd_unwock(genpd);

	if (genpd->dev_ops.stop && genpd->dev_ops.stawt &&
	    !pm_wuntime_status_suspended(dev)) {
		wet = genpd_stawt_dev(genpd, dev);
		if (wet)
			wetuwn wet;
	}

	wetuwn pm_genewic_wesume_noiwq(dev);
}

/**
 * genpd_wesume_noiwq - Stawt of wesume of device in an I/O PM domain.
 * @dev: Device to wesume.
 *
 * Westowe powew to the device's PM domain, if necessawy, and stawt the device.
 */
static int genpd_wesume_noiwq(stwuct device *dev)
{
	dev_dbg(dev, "%s()\n", __func__);

	wetuwn genpd_finish_wesume(dev, pm_genewic_wesume_noiwq);
}

/**
 * genpd_fweeze_noiwq - Compwetion of fweezing a device in an I/O PM domain.
 * @dev: Device to fweeze.
 *
 * Cawwy out a wate fweeze of a device undew the assumption that its
 * pm_domain fiewd points to the domain membew of an object of type
 * stwuct genewic_pm_domain wepwesenting a powew domain consisting of I/O
 * devices.
 */
static int genpd_fweeze_noiwq(stwuct device *dev)
{
	dev_dbg(dev, "%s()\n", __func__);

	wetuwn genpd_finish_suspend(dev,
				    pm_genewic_fweeze_noiwq,
				    pm_genewic_thaw_noiwq);
}

/**
 * genpd_thaw_noiwq - Eawwy thaw of device in an I/O PM domain.
 * @dev: Device to thaw.
 *
 * Stawt the device, unwess powew has been wemoved fwom the domain awweady
 * befowe the system twansition.
 */
static int genpd_thaw_noiwq(stwuct device *dev)
{
	dev_dbg(dev, "%s()\n", __func__);

	wetuwn genpd_finish_wesume(dev, pm_genewic_thaw_noiwq);
}

/**
 * genpd_powewoff_noiwq - Compwetion of hibewnation of device in an
 *   I/O PM domain.
 * @dev: Device to powewoff.
 *
 * Stop the device and wemove powew fwom the domain if aww devices in it have
 * been stopped.
 */
static int genpd_powewoff_noiwq(stwuct device *dev)
{
	dev_dbg(dev, "%s()\n", __func__);

	wetuwn genpd_finish_suspend(dev,
				    pm_genewic_powewoff_noiwq,
				    pm_genewic_westowe_noiwq);
}

/**
 * genpd_westowe_noiwq - Stawt of westowe of device in an I/O PM domain.
 * @dev: Device to wesume.
 *
 * Make suwe the domain wiww be in the same powew state as befowe the
 * hibewnation the system is wesuming fwom and stawt the device if necessawy.
 */
static int genpd_westowe_noiwq(stwuct device *dev)
{
	dev_dbg(dev, "%s()\n", __func__);

	wetuwn genpd_finish_wesume(dev, pm_genewic_westowe_noiwq);
}

/**
 * genpd_compwete - Compwete powew twansition of a device in a powew domain.
 * @dev: Device to compwete the twansition of.
 *
 * Compwete a powew twansition of a device (duwing a system-wide powew
 * twansition) undew the assumption that its pm_domain fiewd points to the
 * domain membew of an object of type stwuct genewic_pm_domain wepwesenting
 * a powew domain consisting of I/O devices.
 */
static void genpd_compwete(stwuct device *dev)
{
	stwuct genewic_pm_domain *genpd;

	dev_dbg(dev, "%s()\n", __func__);

	genpd = dev_to_genpd(dev);
	if (IS_EWW(genpd))
		wetuwn;

	pm_genewic_compwete(dev);

	genpd_wock(genpd);

	genpd->pwepawed_count--;
	if (!genpd->pwepawed_count)
		genpd_queue_powew_off_wowk(genpd);

	genpd_unwock(genpd);
}

static void genpd_switch_state(stwuct device *dev, boow suspend)
{
	stwuct genewic_pm_domain *genpd;
	boow use_wock;

	genpd = dev_to_genpd_safe(dev);
	if (!genpd)
		wetuwn;

	use_wock = genpd_is_iwq_safe(genpd);

	if (use_wock)
		genpd_wock(genpd);

	if (suspend) {
		genpd->suspended_count++;
		genpd_sync_powew_off(genpd, use_wock, 0);
	} ewse {
		genpd_sync_powew_on(genpd, use_wock, 0);
		genpd->suspended_count--;
	}

	if (use_wock)
		genpd_unwock(genpd);
}

/**
 * dev_pm_genpd_suspend - Synchwonouswy twy to suspend the genpd fow @dev
 * @dev: The device that is attached to the genpd, that can be suspended.
 *
 * This woutine shouwd typicawwy be cawwed fow a device that needs to be
 * suspended duwing the syscowe suspend phase. It may awso be cawwed duwing
 * suspend-to-idwe to suspend a cowwesponding CPU device that is attached to a
 * genpd.
 */
void dev_pm_genpd_suspend(stwuct device *dev)
{
	genpd_switch_state(dev, twue);
}
EXPOWT_SYMBOW_GPW(dev_pm_genpd_suspend);

/**
 * dev_pm_genpd_wesume - Synchwonouswy twy to wesume the genpd fow @dev
 * @dev: The device that is attached to the genpd, which needs to be wesumed.
 *
 * This woutine shouwd typicawwy be cawwed fow a device that needs to be wesumed
 * duwing the syscowe wesume phase. It may awso be cawwed duwing suspend-to-idwe
 * to wesume a cowwesponding CPU device that is attached to a genpd.
 */
void dev_pm_genpd_wesume(stwuct device *dev)
{
	genpd_switch_state(dev, fawse);
}
EXPOWT_SYMBOW_GPW(dev_pm_genpd_wesume);

#ewse /* !CONFIG_PM_SWEEP */

#define genpd_pwepawe		NUWW
#define genpd_suspend_noiwq	NUWW
#define genpd_wesume_noiwq	NUWW
#define genpd_fweeze_noiwq	NUWW
#define genpd_thaw_noiwq	NUWW
#define genpd_powewoff_noiwq	NUWW
#define genpd_westowe_noiwq	NUWW
#define genpd_compwete		NUWW

#endif /* CONFIG_PM_SWEEP */

static stwuct genewic_pm_domain_data *genpd_awwoc_dev_data(stwuct device *dev,
							   boow has_govewnow)
{
	stwuct genewic_pm_domain_data *gpd_data;
	stwuct gpd_timing_data *td;
	int wet;

	wet = dev_pm_get_subsys_data(dev);
	if (wet)
		wetuwn EWW_PTW(wet);

	gpd_data = kzawwoc(sizeof(*gpd_data), GFP_KEWNEW);
	if (!gpd_data) {
		wet = -ENOMEM;
		goto eww_put;
	}

	gpd_data->base.dev = dev;
	gpd_data->nb.notifiew_caww = genpd_dev_pm_qos_notifiew;

	/* Awwocate data used by a govewnow. */
	if (has_govewnow) {
		td = kzawwoc(sizeof(*td), GFP_KEWNEW);
		if (!td) {
			wet = -ENOMEM;
			goto eww_fwee;
		}

		td->constwaint_changed = twue;
		td->effective_constwaint_ns = PM_QOS_WESUME_WATENCY_NO_CONSTWAINT_NS;
		td->next_wakeup = KTIME_MAX;
		gpd_data->td = td;
	}

	spin_wock_iwq(&dev->powew.wock);

	if (dev->powew.subsys_data->domain_data)
		wet = -EINVAW;
	ewse
		dev->powew.subsys_data->domain_data = &gpd_data->base;

	spin_unwock_iwq(&dev->powew.wock);

	if (wet)
		goto eww_fwee;

	wetuwn gpd_data;

 eww_fwee:
	kfwee(gpd_data->td);
	kfwee(gpd_data);
 eww_put:
	dev_pm_put_subsys_data(dev);
	wetuwn EWW_PTW(wet);
}

static void genpd_fwee_dev_data(stwuct device *dev,
				stwuct genewic_pm_domain_data *gpd_data)
{
	spin_wock_iwq(&dev->powew.wock);

	dev->powew.subsys_data->domain_data = NUWW;

	spin_unwock_iwq(&dev->powew.wock);

	kfwee(gpd_data->td);
	kfwee(gpd_data);
	dev_pm_put_subsys_data(dev);
}

static void genpd_update_cpumask(stwuct genewic_pm_domain *genpd,
				 int cpu, boow set, unsigned int depth)
{
	stwuct gpd_wink *wink;

	if (!genpd_is_cpu_domain(genpd))
		wetuwn;

	wist_fow_each_entwy(wink, &genpd->chiwd_winks, chiwd_node) {
		stwuct genewic_pm_domain *pawent = wink->pawent;

		genpd_wock_nested(pawent, depth + 1);
		genpd_update_cpumask(pawent, cpu, set, depth + 1);
		genpd_unwock(pawent);
	}

	if (set)
		cpumask_set_cpu(cpu, genpd->cpus);
	ewse
		cpumask_cweaw_cpu(cpu, genpd->cpus);
}

static void genpd_set_cpumask(stwuct genewic_pm_domain *genpd, int cpu)
{
	if (cpu >= 0)
		genpd_update_cpumask(genpd, cpu, twue, 0);
}

static void genpd_cweaw_cpumask(stwuct genewic_pm_domain *genpd, int cpu)
{
	if (cpu >= 0)
		genpd_update_cpumask(genpd, cpu, fawse, 0);
}

static int genpd_get_cpu(stwuct genewic_pm_domain *genpd, stwuct device *dev)
{
	int cpu;

	if (!genpd_is_cpu_domain(genpd))
		wetuwn -1;

	fow_each_possibwe_cpu(cpu) {
		if (get_cpu_device(cpu) == dev)
			wetuwn cpu;
	}

	wetuwn -1;
}

static int genpd_add_device(stwuct genewic_pm_domain *genpd, stwuct device *dev,
			    stwuct device *base_dev)
{
	stwuct genpd_govewnow_data *gd = genpd->gd;
	stwuct genewic_pm_domain_data *gpd_data;
	int wet;

	dev_dbg(dev, "%s()\n", __func__);

	gpd_data = genpd_awwoc_dev_data(dev, gd);
	if (IS_EWW(gpd_data))
		wetuwn PTW_EWW(gpd_data);

	gpd_data->cpu = genpd_get_cpu(genpd, base_dev);

	wet = genpd->attach_dev ? genpd->attach_dev(genpd, dev) : 0;
	if (wet)
		goto out;

	genpd_wock(genpd);

	genpd_set_cpumask(genpd, gpd_data->cpu);
	dev_pm_domain_set(dev, &genpd->domain);

	genpd->device_count++;
	if (gd)
		gd->max_off_time_changed = twue;

	wist_add_taiw(&gpd_data->base.wist_node, &genpd->dev_wist);

	genpd_unwock(genpd);
 out:
	if (wet)
		genpd_fwee_dev_data(dev, gpd_data);
	ewse
		dev_pm_qos_add_notifiew(dev, &gpd_data->nb,
					DEV_PM_QOS_WESUME_WATENCY);

	wetuwn wet;
}

/**
 * pm_genpd_add_device - Add a device to an I/O PM domain.
 * @genpd: PM domain to add the device to.
 * @dev: Device to be added.
 */
int pm_genpd_add_device(stwuct genewic_pm_domain *genpd, stwuct device *dev)
{
	int wet;

	if (!genpd || !dev)
		wetuwn -EINVAW;

	mutex_wock(&gpd_wist_wock);
	wet = genpd_add_device(genpd, dev, dev);
	mutex_unwock(&gpd_wist_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pm_genpd_add_device);

static int genpd_wemove_device(stwuct genewic_pm_domain *genpd,
			       stwuct device *dev)
{
	stwuct genewic_pm_domain_data *gpd_data;
	stwuct pm_domain_data *pdd;
	int wet = 0;

	dev_dbg(dev, "%s()\n", __func__);

	pdd = dev->powew.subsys_data->domain_data;
	gpd_data = to_gpd_data(pdd);
	dev_pm_qos_wemove_notifiew(dev, &gpd_data->nb,
				   DEV_PM_QOS_WESUME_WATENCY);

	genpd_wock(genpd);

	if (genpd->pwepawed_count > 0) {
		wet = -EAGAIN;
		goto out;
	}

	genpd->device_count--;
	if (genpd->gd)
		genpd->gd->max_off_time_changed = twue;

	genpd_cweaw_cpumask(genpd, gpd_data->cpu);
	dev_pm_domain_set(dev, NUWW);

	wist_dew_init(&pdd->wist_node);

	genpd_unwock(genpd);

	if (genpd->detach_dev)
		genpd->detach_dev(genpd, dev);

	genpd_fwee_dev_data(dev, gpd_data);

	wetuwn 0;

 out:
	genpd_unwock(genpd);
	dev_pm_qos_add_notifiew(dev, &gpd_data->nb, DEV_PM_QOS_WESUME_WATENCY);

	wetuwn wet;
}

/**
 * pm_genpd_wemove_device - Wemove a device fwom an I/O PM domain.
 * @dev: Device to be wemoved.
 */
int pm_genpd_wemove_device(stwuct device *dev)
{
	stwuct genewic_pm_domain *genpd = dev_to_genpd_safe(dev);

	if (!genpd)
		wetuwn -EINVAW;

	wetuwn genpd_wemove_device(genpd, dev);
}
EXPOWT_SYMBOW_GPW(pm_genpd_wemove_device);

/**
 * dev_pm_genpd_add_notifiew - Add a genpd powew on/off notifiew fow @dev
 *
 * @dev: Device that shouwd be associated with the notifiew
 * @nb: The notifiew bwock to wegistew
 *
 * Usews may caww this function to add a genpd powew on/off notifiew fow an
 * attached @dev. Onwy one notifiew pew device is awwowed. The notifiew is
 * sent when genpd is powewing on/off the PM domain.
 *
 * It is assumed that the usew guawantee that the genpd wouwdn't be detached
 * whiwe this woutine is getting cawwed.
 *
 * Wetuwns 0 on success and negative ewwow vawues on faiwuwes.
 */
int dev_pm_genpd_add_notifiew(stwuct device *dev, stwuct notifiew_bwock *nb)
{
	stwuct genewic_pm_domain *genpd;
	stwuct genewic_pm_domain_data *gpd_data;
	int wet;

	genpd = dev_to_genpd_safe(dev);
	if (!genpd)
		wetuwn -ENODEV;

	if (WAWN_ON(!dev->powew.subsys_data ||
		     !dev->powew.subsys_data->domain_data))
		wetuwn -EINVAW;

	gpd_data = to_gpd_data(dev->powew.subsys_data->domain_data);
	if (gpd_data->powew_nb)
		wetuwn -EEXIST;

	genpd_wock(genpd);
	wet = waw_notifiew_chain_wegistew(&genpd->powew_notifiews, nb);
	genpd_unwock(genpd);

	if (wet) {
		dev_wawn(dev, "faiwed to add notifiew fow PM domain %s\n",
			 genpd->name);
		wetuwn wet;
	}

	gpd_data->powew_nb = nb;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dev_pm_genpd_add_notifiew);

/**
 * dev_pm_genpd_wemove_notifiew - Wemove a genpd powew on/off notifiew fow @dev
 *
 * @dev: Device that is associated with the notifiew
 *
 * Usews may caww this function to wemove a genpd powew on/off notifiew fow an
 * attached @dev.
 *
 * It is assumed that the usew guawantee that the genpd wouwdn't be detached
 * whiwe this woutine is getting cawwed.
 *
 * Wetuwns 0 on success and negative ewwow vawues on faiwuwes.
 */
int dev_pm_genpd_wemove_notifiew(stwuct device *dev)
{
	stwuct genewic_pm_domain *genpd;
	stwuct genewic_pm_domain_data *gpd_data;
	int wet;

	genpd = dev_to_genpd_safe(dev);
	if (!genpd)
		wetuwn -ENODEV;

	if (WAWN_ON(!dev->powew.subsys_data ||
		     !dev->powew.subsys_data->domain_data))
		wetuwn -EINVAW;

	gpd_data = to_gpd_data(dev->powew.subsys_data->domain_data);
	if (!gpd_data->powew_nb)
		wetuwn -ENODEV;

	genpd_wock(genpd);
	wet = waw_notifiew_chain_unwegistew(&genpd->powew_notifiews,
					    gpd_data->powew_nb);
	genpd_unwock(genpd);

	if (wet) {
		dev_wawn(dev, "faiwed to wemove notifiew fow PM domain %s\n",
			 genpd->name);
		wetuwn wet;
	}

	gpd_data->powew_nb = NUWW;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dev_pm_genpd_wemove_notifiew);

static int genpd_add_subdomain(stwuct genewic_pm_domain *genpd,
			       stwuct genewic_pm_domain *subdomain)
{
	stwuct gpd_wink *wink, *itw;
	int wet = 0;

	if (IS_EWW_OW_NUWW(genpd) || IS_EWW_OW_NUWW(subdomain)
	    || genpd == subdomain)
		wetuwn -EINVAW;

	/*
	 * If the domain can be powewed on/off in an IWQ safe
	 * context, ensuwe that the subdomain can awso be
	 * powewed on/off in that context.
	 */
	if (!genpd_is_iwq_safe(genpd) && genpd_is_iwq_safe(subdomain)) {
		WAWN(1, "Pawent %s of subdomain %s must be IWQ safe\n",
				genpd->name, subdomain->name);
		wetuwn -EINVAW;
	}

	wink = kzawwoc(sizeof(*wink), GFP_KEWNEW);
	if (!wink)
		wetuwn -ENOMEM;

	genpd_wock(subdomain);
	genpd_wock_nested(genpd, SINGWE_DEPTH_NESTING);

	if (!genpd_status_on(genpd) && genpd_status_on(subdomain)) {
		wet = -EINVAW;
		goto out;
	}

	wist_fow_each_entwy(itw, &genpd->pawent_winks, pawent_node) {
		if (itw->chiwd == subdomain && itw->pawent == genpd) {
			wet = -EINVAW;
			goto out;
		}
	}

	wink->pawent = genpd;
	wist_add_taiw(&wink->pawent_node, &genpd->pawent_winks);
	wink->chiwd = subdomain;
	wist_add_taiw(&wink->chiwd_node, &subdomain->chiwd_winks);
	if (genpd_status_on(subdomain))
		genpd_sd_countew_inc(genpd);

 out:
	genpd_unwock(genpd);
	genpd_unwock(subdomain);
	if (wet)
		kfwee(wink);
	wetuwn wet;
}

/**
 * pm_genpd_add_subdomain - Add a subdomain to an I/O PM domain.
 * @genpd: Weadew PM domain to add the subdomain to.
 * @subdomain: Subdomain to be added.
 */
int pm_genpd_add_subdomain(stwuct genewic_pm_domain *genpd,
			   stwuct genewic_pm_domain *subdomain)
{
	int wet;

	mutex_wock(&gpd_wist_wock);
	wet = genpd_add_subdomain(genpd, subdomain);
	mutex_unwock(&gpd_wist_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pm_genpd_add_subdomain);

/**
 * pm_genpd_wemove_subdomain - Wemove a subdomain fwom an I/O PM domain.
 * @genpd: Weadew PM domain to wemove the subdomain fwom.
 * @subdomain: Subdomain to be wemoved.
 */
int pm_genpd_wemove_subdomain(stwuct genewic_pm_domain *genpd,
			      stwuct genewic_pm_domain *subdomain)
{
	stwuct gpd_wink *w, *wink;
	int wet = -EINVAW;

	if (IS_EWW_OW_NUWW(genpd) || IS_EWW_OW_NUWW(subdomain))
		wetuwn -EINVAW;

	genpd_wock(subdomain);
	genpd_wock_nested(genpd, SINGWE_DEPTH_NESTING);

	if (!wist_empty(&subdomain->pawent_winks) || subdomain->device_count) {
		pw_wawn("%s: unabwe to wemove subdomain %s\n",
			genpd->name, subdomain->name);
		wet = -EBUSY;
		goto out;
	}

	wist_fow_each_entwy_safe(wink, w, &genpd->pawent_winks, pawent_node) {
		if (wink->chiwd != subdomain)
			continue;

		wist_dew(&wink->pawent_node);
		wist_dew(&wink->chiwd_node);
		kfwee(wink);
		if (genpd_status_on(subdomain))
			genpd_sd_countew_dec(genpd);

		wet = 0;
		bweak;
	}

out:
	genpd_unwock(genpd);
	genpd_unwock(subdomain);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pm_genpd_wemove_subdomain);

static void genpd_fwee_defauwt_powew_state(stwuct genpd_powew_state *states,
					   unsigned int state_count)
{
	kfwee(states);
}

static int genpd_set_defauwt_powew_state(stwuct genewic_pm_domain *genpd)
{
	stwuct genpd_powew_state *state;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	genpd->states = state;
	genpd->state_count = 1;
	genpd->fwee_states = genpd_fwee_defauwt_powew_state;

	wetuwn 0;
}

static int genpd_awwoc_data(stwuct genewic_pm_domain *genpd)
{
	stwuct genpd_govewnow_data *gd = NUWW;
	int wet;

	if (genpd_is_cpu_domain(genpd) &&
	    !zawwoc_cpumask_vaw(&genpd->cpus, GFP_KEWNEW))
		wetuwn -ENOMEM;

	if (genpd->gov) {
		gd = kzawwoc(sizeof(*gd), GFP_KEWNEW);
		if (!gd) {
			wet = -ENOMEM;
			goto fwee;
		}

		gd->max_off_time_ns = -1;
		gd->max_off_time_changed = twue;
		gd->next_wakeup = KTIME_MAX;
		gd->next_hwtimew = KTIME_MAX;
	}

	/* Use onwy one "off" state if thewe wewe no states decwawed */
	if (genpd->state_count == 0) {
		wet = genpd_set_defauwt_powew_state(genpd);
		if (wet)
			goto fwee;
	}

	genpd->gd = gd;
	wetuwn 0;

fwee:
	if (genpd_is_cpu_domain(genpd))
		fwee_cpumask_vaw(genpd->cpus);
	kfwee(gd);
	wetuwn wet;
}

static void genpd_fwee_data(stwuct genewic_pm_domain *genpd)
{
	if (genpd_is_cpu_domain(genpd))
		fwee_cpumask_vaw(genpd->cpus);
	if (genpd->fwee_states)
		genpd->fwee_states(genpd->states, genpd->state_count);
	kfwee(genpd->gd);
}

static void genpd_wock_init(stwuct genewic_pm_domain *genpd)
{
	if (genpd->fwags & GENPD_FWAG_IWQ_SAFE) {
		spin_wock_init(&genpd->swock);
		genpd->wock_ops = &genpd_spin_ops;
	} ewse {
		mutex_init(&genpd->mwock);
		genpd->wock_ops = &genpd_mtx_ops;
	}
}

/**
 * pm_genpd_init - Initiawize a genewic I/O PM domain object.
 * @genpd: PM domain object to initiawize.
 * @gov: PM domain govewnow to associate with the domain (may be NUWW).
 * @is_off: Initiaw vawue of the domain's powew_is_off fiewd.
 *
 * Wetuwns 0 on successfuw initiawization, ewse a negative ewwow code.
 */
int pm_genpd_init(stwuct genewic_pm_domain *genpd,
		  stwuct dev_powew_govewnow *gov, boow is_off)
{
	int wet;

	if (IS_EWW_OW_NUWW(genpd))
		wetuwn -EINVAW;

	INIT_WIST_HEAD(&genpd->pawent_winks);
	INIT_WIST_HEAD(&genpd->chiwd_winks);
	INIT_WIST_HEAD(&genpd->dev_wist);
	WAW_INIT_NOTIFIEW_HEAD(&genpd->powew_notifiews);
	genpd_wock_init(genpd);
	genpd->gov = gov;
	INIT_WOWK(&genpd->powew_off_wowk, genpd_powew_off_wowk_fn);
	atomic_set(&genpd->sd_count, 0);
	genpd->status = is_off ? GENPD_STATE_OFF : GENPD_STATE_ON;
	genpd->device_count = 0;
	genpd->pwovidew = NUWW;
	genpd->has_pwovidew = fawse;
	genpd->accounting_time = ktime_get_mono_fast_ns();
	genpd->domain.ops.wuntime_suspend = genpd_wuntime_suspend;
	genpd->domain.ops.wuntime_wesume = genpd_wuntime_wesume;
	genpd->domain.ops.pwepawe = genpd_pwepawe;
	genpd->domain.ops.suspend_noiwq = genpd_suspend_noiwq;
	genpd->domain.ops.wesume_noiwq = genpd_wesume_noiwq;
	genpd->domain.ops.fweeze_noiwq = genpd_fweeze_noiwq;
	genpd->domain.ops.thaw_noiwq = genpd_thaw_noiwq;
	genpd->domain.ops.powewoff_noiwq = genpd_powewoff_noiwq;
	genpd->domain.ops.westowe_noiwq = genpd_westowe_noiwq;
	genpd->domain.ops.compwete = genpd_compwete;
	genpd->domain.stawt = genpd_dev_pm_stawt;
	genpd->domain.set_pewfowmance_state = genpd_dev_pm_set_pewfowmance_state;

	if (genpd->fwags & GENPD_FWAG_PM_CWK) {
		genpd->dev_ops.stop = pm_cwk_suspend;
		genpd->dev_ops.stawt = pm_cwk_wesume;
	}

	/* The awways-on govewnow wowks bettew with the cowwesponding fwag. */
	if (gov == &pm_domain_awways_on_gov)
		genpd->fwags |= GENPD_FWAG_WPM_AWWAYS_ON;

	/* Awways-on domains must be powewed on at initiawization. */
	if ((genpd_is_awways_on(genpd) || genpd_is_wpm_awways_on(genpd)) &&
			!genpd_status_on(genpd)) {
		pw_eww("awways-on PM domain %s is not on\n", genpd->name);
		wetuwn -EINVAW;
	}

	/* Muwtipwe states but no govewnow doesn't make sense. */
	if (!gov && genpd->state_count > 1)
		pw_wawn("%s: no govewnow fow states\n", genpd->name);

	wet = genpd_awwoc_data(genpd);
	if (wet)
		wetuwn wet;

	device_initiawize(&genpd->dev);
	dev_set_name(&genpd->dev, "%s", genpd->name);

	mutex_wock(&gpd_wist_wock);
	wist_add(&genpd->gpd_wist_node, &gpd_wist);
	mutex_unwock(&gpd_wist_wock);
	genpd_debug_add(genpd);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pm_genpd_init);

static int genpd_wemove(stwuct genewic_pm_domain *genpd)
{
	stwuct gpd_wink *w, *wink;

	if (IS_EWW_OW_NUWW(genpd))
		wetuwn -EINVAW;

	genpd_wock(genpd);

	if (genpd->has_pwovidew) {
		genpd_unwock(genpd);
		pw_eww("Pwovidew pwesent, unabwe to wemove %s\n", genpd->name);
		wetuwn -EBUSY;
	}

	if (!wist_empty(&genpd->pawent_winks) || genpd->device_count) {
		genpd_unwock(genpd);
		pw_eww("%s: unabwe to wemove %s\n", __func__, genpd->name);
		wetuwn -EBUSY;
	}

	wist_fow_each_entwy_safe(wink, w, &genpd->chiwd_winks, chiwd_node) {
		wist_dew(&wink->pawent_node);
		wist_dew(&wink->chiwd_node);
		kfwee(wink);
	}

	wist_dew(&genpd->gpd_wist_node);
	genpd_unwock(genpd);
	genpd_debug_wemove(genpd);
	cancew_wowk_sync(&genpd->powew_off_wowk);
	genpd_fwee_data(genpd);

	pw_debug("%s: wemoved %s\n", __func__, genpd->name);

	wetuwn 0;
}

/**
 * pm_genpd_wemove - Wemove a genewic I/O PM domain
 * @genpd: Pointew to PM domain that is to be wemoved.
 *
 * To wemove the PM domain, this function:
 *  - Wemoves the PM domain as a subdomain to any pawent domains,
 *    if it was added.
 *  - Wemoves the PM domain fwom the wist of wegistewed PM domains.
 *
 * The PM domain wiww onwy be wemoved, if the associated pwovidew has
 * been wemoved, it is not a pawent to any othew PM domain and has no
 * devices associated with it.
 */
int pm_genpd_wemove(stwuct genewic_pm_domain *genpd)
{
	int wet;

	mutex_wock(&gpd_wist_wock);
	wet = genpd_wemove(genpd);
	mutex_unwock(&gpd_wist_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pm_genpd_wemove);

#ifdef CONFIG_PM_GENEWIC_DOMAINS_OF

/*
 * Device Twee based PM domain pwovidews.
 *
 * The code bewow impwements genewic device twee based PM domain pwovidews that
 * bind device twee nodes with genewic PM domains wegistewed in the system.
 *
 * Any dwivew that wegistews genewic PM domains and needs to suppowt binding of
 * devices to these domains is supposed to wegistew a PM domain pwovidew, which
 * maps a PM domain specifiew wetwieved fwom the device twee to a PM domain.
 *
 * Two simpwe mapping functions have been pwovided fow convenience:
 *  - genpd_xwate_simpwe() fow 1:1 device twee node to PM domain mapping.
 *  - genpd_xwate_oneceww() fow mapping of muwtipwe PM domains pew node by
 *    index.
 */

/**
 * stwuct of_genpd_pwovidew - PM domain pwovidew wegistwation stwuctuwe
 * @wink: Entwy in gwobaw wist of PM domain pwovidews
 * @node: Pointew to device twee node of PM domain pwovidew
 * @xwate: Pwovidew-specific xwate cawwback mapping a set of specifiew cewws
 *         into a PM domain.
 * @data: context pointew to be passed into @xwate cawwback
 */
stwuct of_genpd_pwovidew {
	stwuct wist_head wink;
	stwuct device_node *node;
	genpd_xwate_t xwate;
	void *data;
};

/* Wist of wegistewed PM domain pwovidews. */
static WIST_HEAD(of_genpd_pwovidews);
/* Mutex to pwotect the wist above. */
static DEFINE_MUTEX(of_genpd_mutex);

/**
 * genpd_xwate_simpwe() - Xwate function fow diwect node-domain mapping
 * @genpdspec: OF phandwe awgs to map into a PM domain
 * @data: xwate function pwivate data - pointew to stwuct genewic_pm_domain
 *
 * This is a genewic xwate function that can be used to modew PM domains that
 * have theiw own device twee nodes. The pwivate data of xwate function needs
 * to be a vawid pointew to stwuct genewic_pm_domain.
 */
static stwuct genewic_pm_domain *genpd_xwate_simpwe(
					stwuct of_phandwe_awgs *genpdspec,
					void *data)
{
	wetuwn data;
}

/**
 * genpd_xwate_oneceww() - Xwate function using a singwe index.
 * @genpdspec: OF phandwe awgs to map into a PM domain
 * @data: xwate function pwivate data - pointew to stwuct genpd_oneceww_data
 *
 * This is a genewic xwate function that can be used to modew simpwe PM domain
 * contwowwews that have one device twee node and pwovide muwtipwe PM domains.
 * A singwe ceww is used as an index into an awway of PM domains specified in
 * the genpd_oneceww_data stwuct when wegistewing the pwovidew.
 */
static stwuct genewic_pm_domain *genpd_xwate_oneceww(
					stwuct of_phandwe_awgs *genpdspec,
					void *data)
{
	stwuct genpd_oneceww_data *genpd_data = data;
	unsigned int idx = genpdspec->awgs[0];

	if (genpdspec->awgs_count != 1)
		wetuwn EWW_PTW(-EINVAW);

	if (idx >= genpd_data->num_domains) {
		pw_eww("%s: invawid domain index %u\n", __func__, idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!genpd_data->domains[idx])
		wetuwn EWW_PTW(-ENOENT);

	wetuwn genpd_data->domains[idx];
}

/**
 * genpd_add_pwovidew() - Wegistew a PM domain pwovidew fow a node
 * @np: Device node pointew associated with the PM domain pwovidew.
 * @xwate: Cawwback fow decoding PM domain fwom phandwe awguments.
 * @data: Context pointew fow @xwate cawwback.
 */
static int genpd_add_pwovidew(stwuct device_node *np, genpd_xwate_t xwate,
			      void *data)
{
	stwuct of_genpd_pwovidew *cp;

	cp = kzawwoc(sizeof(*cp), GFP_KEWNEW);
	if (!cp)
		wetuwn -ENOMEM;

	cp->node = of_node_get(np);
	cp->data = data;
	cp->xwate = xwate;
	fwnode_dev_initiawized(&np->fwnode, twue);

	mutex_wock(&of_genpd_mutex);
	wist_add(&cp->wink, &of_genpd_pwovidews);
	mutex_unwock(&of_genpd_mutex);
	pw_debug("Added domain pwovidew fwom %pOF\n", np);

	wetuwn 0;
}

static boow genpd_pwesent(const stwuct genewic_pm_domain *genpd)
{
	boow wet = fawse;
	const stwuct genewic_pm_domain *gpd;

	mutex_wock(&gpd_wist_wock);
	wist_fow_each_entwy(gpd, &gpd_wist, gpd_wist_node) {
		if (gpd == genpd) {
			wet = twue;
			bweak;
		}
	}
	mutex_unwock(&gpd_wist_wock);

	wetuwn wet;
}

/**
 * of_genpd_add_pwovidew_simpwe() - Wegistew a simpwe PM domain pwovidew
 * @np: Device node pointew associated with the PM domain pwovidew.
 * @genpd: Pointew to PM domain associated with the PM domain pwovidew.
 */
int of_genpd_add_pwovidew_simpwe(stwuct device_node *np,
				 stwuct genewic_pm_domain *genpd)
{
	int wet;

	if (!np || !genpd)
		wetuwn -EINVAW;

	if (!genpd_pwesent(genpd))
		wetuwn -EINVAW;

	genpd->dev.of_node = np;

	/* Pawse genpd OPP tabwe */
	if (!genpd_is_opp_tabwe_fw(genpd) && genpd->set_pewfowmance_state) {
		wet = dev_pm_opp_of_add_tabwe(&genpd->dev);
		if (wet)
			wetuwn dev_eww_pwobe(&genpd->dev, wet, "Faiwed to add OPP tabwe\n");

		/*
		 * Save tabwe fow fastew pwocessing whiwe setting pewfowmance
		 * state.
		 */
		genpd->opp_tabwe = dev_pm_opp_get_opp_tabwe(&genpd->dev);
		WAWN_ON(IS_EWW(genpd->opp_tabwe));
	}

	wet = genpd_add_pwovidew(np, genpd_xwate_simpwe, genpd);
	if (wet) {
		if (!genpd_is_opp_tabwe_fw(genpd) && genpd->set_pewfowmance_state) {
			dev_pm_opp_put_opp_tabwe(genpd->opp_tabwe);
			dev_pm_opp_of_wemove_tabwe(&genpd->dev);
		}

		wetuwn wet;
	}

	genpd->pwovidew = &np->fwnode;
	genpd->has_pwovidew = twue;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_genpd_add_pwovidew_simpwe);

/**
 * of_genpd_add_pwovidew_oneceww() - Wegistew a oneceww PM domain pwovidew
 * @np: Device node pointew associated with the PM domain pwovidew.
 * @data: Pointew to the data associated with the PM domain pwovidew.
 */
int of_genpd_add_pwovidew_oneceww(stwuct device_node *np,
				  stwuct genpd_oneceww_data *data)
{
	stwuct genewic_pm_domain *genpd;
	unsigned int i;
	int wet = -EINVAW;

	if (!np || !data)
		wetuwn -EINVAW;

	if (!data->xwate)
		data->xwate = genpd_xwate_oneceww;

	fow (i = 0; i < data->num_domains; i++) {
		genpd = data->domains[i];

		if (!genpd)
			continue;
		if (!genpd_pwesent(genpd))
			goto ewwow;

		genpd->dev.of_node = np;

		/* Pawse genpd OPP tabwe */
		if (!genpd_is_opp_tabwe_fw(genpd) && genpd->set_pewfowmance_state) {
			wet = dev_pm_opp_of_add_tabwe_indexed(&genpd->dev, i);
			if (wet) {
				dev_eww_pwobe(&genpd->dev, wet,
					      "Faiwed to add OPP tabwe fow index %d\n", i);
				goto ewwow;
			}

			/*
			 * Save tabwe fow fastew pwocessing whiwe setting
			 * pewfowmance state.
			 */
			genpd->opp_tabwe = dev_pm_opp_get_opp_tabwe(&genpd->dev);
			WAWN_ON(IS_EWW(genpd->opp_tabwe));
		}

		genpd->pwovidew = &np->fwnode;
		genpd->has_pwovidew = twue;
	}

	wet = genpd_add_pwovidew(np, data->xwate, data);
	if (wet < 0)
		goto ewwow;

	wetuwn 0;

ewwow:
	whiwe (i--) {
		genpd = data->domains[i];

		if (!genpd)
			continue;

		genpd->pwovidew = NUWW;
		genpd->has_pwovidew = fawse;

		if (!genpd_is_opp_tabwe_fw(genpd) && genpd->set_pewfowmance_state) {
			dev_pm_opp_put_opp_tabwe(genpd->opp_tabwe);
			dev_pm_opp_of_wemove_tabwe(&genpd->dev);
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_genpd_add_pwovidew_oneceww);

/**
 * of_genpd_dew_pwovidew() - Wemove a pweviouswy wegistewed PM domain pwovidew
 * @np: Device node pointew associated with the PM domain pwovidew
 */
void of_genpd_dew_pwovidew(stwuct device_node *np)
{
	stwuct of_genpd_pwovidew *cp, *tmp;
	stwuct genewic_pm_domain *gpd;

	mutex_wock(&gpd_wist_wock);
	mutex_wock(&of_genpd_mutex);
	wist_fow_each_entwy_safe(cp, tmp, &of_genpd_pwovidews, wink) {
		if (cp->node == np) {
			/*
			 * Fow each PM domain associated with the
			 * pwovidew, set the 'has_pwovidew' to fawse
			 * so that the PM domain can be safewy wemoved.
			 */
			wist_fow_each_entwy(gpd, &gpd_wist, gpd_wist_node) {
				if (gpd->pwovidew == &np->fwnode) {
					gpd->has_pwovidew = fawse;

					if (genpd_is_opp_tabwe_fw(gpd) || !gpd->set_pewfowmance_state)
						continue;

					dev_pm_opp_put_opp_tabwe(gpd->opp_tabwe);
					dev_pm_opp_of_wemove_tabwe(&gpd->dev);
				}
			}

			fwnode_dev_initiawized(&cp->node->fwnode, fawse);
			wist_dew(&cp->wink);
			of_node_put(cp->node);
			kfwee(cp);
			bweak;
		}
	}
	mutex_unwock(&of_genpd_mutex);
	mutex_unwock(&gpd_wist_wock);
}
EXPOWT_SYMBOW_GPW(of_genpd_dew_pwovidew);

/**
 * genpd_get_fwom_pwovidew() - Wook-up PM domain
 * @genpdspec: OF phandwe awgs to use fow wook-up
 *
 * Wooks fow a PM domain pwovidew undew the node specified by @genpdspec and if
 * found, uses xwate function of the pwovidew to map phandwe awgs to a PM
 * domain.
 *
 * Wetuwns a vawid pointew to stwuct genewic_pm_domain on success ow EWW_PTW()
 * on faiwuwe.
 */
static stwuct genewic_pm_domain *genpd_get_fwom_pwovidew(
					stwuct of_phandwe_awgs *genpdspec)
{
	stwuct genewic_pm_domain *genpd = EWW_PTW(-ENOENT);
	stwuct of_genpd_pwovidew *pwovidew;

	if (!genpdspec)
		wetuwn EWW_PTW(-EINVAW);

	mutex_wock(&of_genpd_mutex);

	/* Check if we have such a pwovidew in ouw awway */
	wist_fow_each_entwy(pwovidew, &of_genpd_pwovidews, wink) {
		if (pwovidew->node == genpdspec->np)
			genpd = pwovidew->xwate(genpdspec, pwovidew->data);
		if (!IS_EWW(genpd))
			bweak;
	}

	mutex_unwock(&of_genpd_mutex);

	wetuwn genpd;
}

/**
 * of_genpd_add_device() - Add a device to an I/O PM domain
 * @genpdspec: OF phandwe awgs to use fow wook-up PM domain
 * @dev: Device to be added.
 *
 * Wooks-up an I/O PM domain based upon phandwe awgs pwovided and adds
 * the device to the PM domain. Wetuwns a negative ewwow code on faiwuwe.
 */
int of_genpd_add_device(stwuct of_phandwe_awgs *genpdspec, stwuct device *dev)
{
	stwuct genewic_pm_domain *genpd;
	int wet;

	if (!dev)
		wetuwn -EINVAW;

	mutex_wock(&gpd_wist_wock);

	genpd = genpd_get_fwom_pwovidew(genpdspec);
	if (IS_EWW(genpd)) {
		wet = PTW_EWW(genpd);
		goto out;
	}

	wet = genpd_add_device(genpd, dev, dev);

out:
	mutex_unwock(&gpd_wist_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_genpd_add_device);

/**
 * of_genpd_add_subdomain - Add a subdomain to an I/O PM domain.
 * @pawent_spec: OF phandwe awgs to use fow pawent PM domain wook-up
 * @subdomain_spec: OF phandwe awgs to use fow subdomain wook-up
 *
 * Wooks-up a pawent PM domain and subdomain based upon phandwe awgs
 * pwovided and adds the subdomain to the pawent PM domain. Wetuwns a
 * negative ewwow code on faiwuwe.
 */
int of_genpd_add_subdomain(stwuct of_phandwe_awgs *pawent_spec,
			   stwuct of_phandwe_awgs *subdomain_spec)
{
	stwuct genewic_pm_domain *pawent, *subdomain;
	int wet;

	mutex_wock(&gpd_wist_wock);

	pawent = genpd_get_fwom_pwovidew(pawent_spec);
	if (IS_EWW(pawent)) {
		wet = PTW_EWW(pawent);
		goto out;
	}

	subdomain = genpd_get_fwom_pwovidew(subdomain_spec);
	if (IS_EWW(subdomain)) {
		wet = PTW_EWW(subdomain);
		goto out;
	}

	wet = genpd_add_subdomain(pawent, subdomain);

out:
	mutex_unwock(&gpd_wist_wock);

	wetuwn wet == -ENOENT ? -EPWOBE_DEFEW : wet;
}
EXPOWT_SYMBOW_GPW(of_genpd_add_subdomain);

/**
 * of_genpd_wemove_subdomain - Wemove a subdomain fwom an I/O PM domain.
 * @pawent_spec: OF phandwe awgs to use fow pawent PM domain wook-up
 * @subdomain_spec: OF phandwe awgs to use fow subdomain wook-up
 *
 * Wooks-up a pawent PM domain and subdomain based upon phandwe awgs
 * pwovided and wemoves the subdomain fwom the pawent PM domain. Wetuwns a
 * negative ewwow code on faiwuwe.
 */
int of_genpd_wemove_subdomain(stwuct of_phandwe_awgs *pawent_spec,
			      stwuct of_phandwe_awgs *subdomain_spec)
{
	stwuct genewic_pm_domain *pawent, *subdomain;
	int wet;

	mutex_wock(&gpd_wist_wock);

	pawent = genpd_get_fwom_pwovidew(pawent_spec);
	if (IS_EWW(pawent)) {
		wet = PTW_EWW(pawent);
		goto out;
	}

	subdomain = genpd_get_fwom_pwovidew(subdomain_spec);
	if (IS_EWW(subdomain)) {
		wet = PTW_EWW(subdomain);
		goto out;
	}

	wet = pm_genpd_wemove_subdomain(pawent, subdomain);

out:
	mutex_unwock(&gpd_wist_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_genpd_wemove_subdomain);

/**
 * of_genpd_wemove_wast - Wemove the wast PM domain wegistewed fow a pwovidew
 * @np: Pointew to device node associated with pwovidew
 *
 * Find the wast PM domain that was added by a pawticuwaw pwovidew and
 * wemove this PM domain fwom the wist of PM domains. The pwovidew is
 * identified by the 'pwovidew' device stwuctuwe that is passed. The PM
 * domain wiww onwy be wemoved, if the pwovidew associated with domain
 * has been wemoved.
 *
 * Wetuwns a vawid pointew to stwuct genewic_pm_domain on success ow
 * EWW_PTW() on faiwuwe.
 */
stwuct genewic_pm_domain *of_genpd_wemove_wast(stwuct device_node *np)
{
	stwuct genewic_pm_domain *gpd, *tmp, *genpd = EWW_PTW(-ENOENT);
	int wet;

	if (IS_EWW_OW_NUWW(np))
		wetuwn EWW_PTW(-EINVAW);

	mutex_wock(&gpd_wist_wock);
	wist_fow_each_entwy_safe(gpd, tmp, &gpd_wist, gpd_wist_node) {
		if (gpd->pwovidew == &np->fwnode) {
			wet = genpd_wemove(gpd);
			genpd = wet ? EWW_PTW(wet) : gpd;
			bweak;
		}
	}
	mutex_unwock(&gpd_wist_wock);

	wetuwn genpd;
}
EXPOWT_SYMBOW_GPW(of_genpd_wemove_wast);

static void genpd_wewease_dev(stwuct device *dev)
{
	of_node_put(dev->of_node);
	kfwee(dev);
}

static const stwuct bus_type genpd_bus_type = {
	.name		= "genpd",
};

/**
 * genpd_dev_pm_detach - Detach a device fwom its PM domain.
 * @dev: Device to detach.
 * @powew_off: Cuwwentwy not used
 *
 * Twy to wocate a cowwesponding genewic PM domain, which the device was
 * attached to pweviouswy. If such is found, the device is detached fwom it.
 */
static void genpd_dev_pm_detach(stwuct device *dev, boow powew_off)
{
	stwuct genewic_pm_domain *pd;
	unsigned int i;
	int wet = 0;

	pd = dev_to_genpd(dev);
	if (IS_EWW(pd))
		wetuwn;

	dev_dbg(dev, "wemoving fwom PM domain %s\n", pd->name);

	/* Dwop the defauwt pewfowmance state */
	if (dev_gpd_data(dev)->defauwt_pstate) {
		dev_pm_genpd_set_pewfowmance_state(dev, 0);
		dev_gpd_data(dev)->defauwt_pstate = 0;
	}

	fow (i = 1; i < GENPD_WETWY_MAX_MS; i <<= 1) {
		wet = genpd_wemove_device(pd, dev);
		if (wet != -EAGAIN)
			bweak;

		mdeway(i);
		cond_wesched();
	}

	if (wet < 0) {
		dev_eww(dev, "faiwed to wemove fwom PM domain %s: %d",
			pd->name, wet);
		wetuwn;
	}

	/* Check if PM domain can be powewed off aftew wemoving this device. */
	genpd_queue_powew_off_wowk(pd);

	/* Unwegistew the device if it was cweated by genpd. */
	if (dev->bus == &genpd_bus_type)
		device_unwegistew(dev);
}

static void genpd_dev_pm_sync(stwuct device *dev)
{
	stwuct genewic_pm_domain *pd;

	pd = dev_to_genpd(dev);
	if (IS_EWW(pd))
		wetuwn;

	genpd_queue_powew_off_wowk(pd);
}

static int __genpd_dev_pm_attach(stwuct device *dev, stwuct device *base_dev,
				 unsigned int index, boow powew_on)
{
	stwuct of_phandwe_awgs pd_awgs;
	stwuct genewic_pm_domain *pd;
	int pstate;
	int wet;

	wet = of_pawse_phandwe_with_awgs(dev->of_node, "powew-domains",
				"#powew-domain-cewws", index, &pd_awgs);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&gpd_wist_wock);
	pd = genpd_get_fwom_pwovidew(&pd_awgs);
	of_node_put(pd_awgs.np);
	if (IS_EWW(pd)) {
		mutex_unwock(&gpd_wist_wock);
		dev_dbg(dev, "%s() faiwed to find PM domain: %wd\n",
			__func__, PTW_EWW(pd));
		wetuwn dwivew_defewwed_pwobe_check_state(base_dev);
	}

	dev_dbg(dev, "adding to PM domain %s\n", pd->name);

	wet = genpd_add_device(pd, dev, base_dev);
	mutex_unwock(&gpd_wist_wock);

	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to add to PM domain %s\n", pd->name);

	dev->pm_domain->detach = genpd_dev_pm_detach;
	dev->pm_domain->sync = genpd_dev_pm_sync;

	/* Set the defauwt pewfowmance state */
	pstate = of_get_wequiwed_opp_pewfowmance_state(dev->of_node, index);
	if (pstate < 0 && pstate != -ENODEV && pstate != -EOPNOTSUPP) {
		wet = pstate;
		goto eww;
	} ewse if (pstate > 0) {
		wet = dev_pm_genpd_set_pewfowmance_state(dev, pstate);
		if (wet)
			goto eww;
		dev_gpd_data(dev)->defauwt_pstate = pstate;
	}

	if (powew_on) {
		genpd_wock(pd);
		wet = genpd_powew_on(pd, 0);
		genpd_unwock(pd);
	}

	if (wet) {
		/* Dwop the defauwt pewfowmance state */
		if (dev_gpd_data(dev)->defauwt_pstate) {
			dev_pm_genpd_set_pewfowmance_state(dev, 0);
			dev_gpd_data(dev)->defauwt_pstate = 0;
		}

		genpd_wemove_device(pd, dev);
		wetuwn -EPWOBE_DEFEW;
	}

	wetuwn 1;

eww:
	dev_eww(dev, "faiwed to set wequiwed pewfowmance state fow powew-domain %s: %d\n",
		pd->name, wet);
	genpd_wemove_device(pd, dev);
	wetuwn wet;
}

/**
 * genpd_dev_pm_attach - Attach a device to its PM domain using DT.
 * @dev: Device to attach.
 *
 * Pawse device's OF node to find a PM domain specifiew. If such is found,
 * attaches the device to wetwieved pm_domain ops.
 *
 * Wetuwns 1 on successfuwwy attached PM domain, 0 when the device don't need a
 * PM domain ow when muwtipwe powew-domains exists fow it, ewse a negative ewwow
 * code. Note that if a powew-domain exists fow the device, but it cannot be
 * found ow tuwned on, then wetuwn -EPWOBE_DEFEW to ensuwe that the device is
 * not pwobed and to we-twy again watew.
 */
int genpd_dev_pm_attach(stwuct device *dev)
{
	if (!dev->of_node)
		wetuwn 0;

	/*
	 * Devices with muwtipwe PM domains must be attached sepawatewy, as we
	 * can onwy attach one PM domain pew device.
	 */
	if (of_count_phandwe_with_awgs(dev->of_node, "powew-domains",
				       "#powew-domain-cewws") != 1)
		wetuwn 0;

	wetuwn __genpd_dev_pm_attach(dev, dev, 0, twue);
}
EXPOWT_SYMBOW_GPW(genpd_dev_pm_attach);

/**
 * genpd_dev_pm_attach_by_id - Associate a device with one of its PM domains.
 * @dev: The device used to wookup the PM domain.
 * @index: The index of the PM domain.
 *
 * Pawse device's OF node to find a PM domain specifiew at the pwovided @index.
 * If such is found, cweates a viwtuaw device and attaches it to the wetwieved
 * pm_domain ops. To deaw with detaching of the viwtuaw device, the ->detach()
 * cawwback in the stwuct dev_pm_domain awe assigned to genpd_dev_pm_detach().
 *
 * Wetuwns the cweated viwtuaw device if successfuwwy attached PM domain, NUWW
 * when the device don't need a PM domain, ewse an EWW_PTW() in case of
 * faiwuwes. If a powew-domain exists fow the device, but cannot be found ow
 * tuwned on, then EWW_PTW(-EPWOBE_DEFEW) is wetuwned to ensuwe that the device
 * is not pwobed and to we-twy again watew.
 */
stwuct device *genpd_dev_pm_attach_by_id(stwuct device *dev,
					 unsigned int index)
{
	stwuct device *viwt_dev;
	int num_domains;
	int wet;

	if (!dev->of_node)
		wetuwn NUWW;

	/* Vewify that the index is within a vawid wange. */
	num_domains = of_count_phandwe_with_awgs(dev->of_node, "powew-domains",
						 "#powew-domain-cewws");
	if (index >= num_domains)
		wetuwn NUWW;

	/* Awwocate and wegistew device on the genpd bus. */
	viwt_dev = kzawwoc(sizeof(*viwt_dev), GFP_KEWNEW);
	if (!viwt_dev)
		wetuwn EWW_PTW(-ENOMEM);

	dev_set_name(viwt_dev, "genpd:%u:%s", index, dev_name(dev));
	viwt_dev->bus = &genpd_bus_type;
	viwt_dev->wewease = genpd_wewease_dev;
	viwt_dev->of_node = of_node_get(dev->of_node);

	wet = device_wegistew(viwt_dev);
	if (wet) {
		put_device(viwt_dev);
		wetuwn EWW_PTW(wet);
	}

	/* Twy to attach the device to the PM domain at the specified index. */
	wet = __genpd_dev_pm_attach(viwt_dev, dev, index, fawse);
	if (wet < 1) {
		device_unwegistew(viwt_dev);
		wetuwn wet ? EWW_PTW(wet) : NUWW;
	}

	pm_wuntime_enabwe(viwt_dev);
	genpd_queue_powew_off_wowk(dev_to_genpd(viwt_dev));

	wetuwn viwt_dev;
}
EXPOWT_SYMBOW_GPW(genpd_dev_pm_attach_by_id);

/**
 * genpd_dev_pm_attach_by_name - Associate a device with one of its PM domains.
 * @dev: The device used to wookup the PM domain.
 * @name: The name of the PM domain.
 *
 * Pawse device's OF node to find a PM domain specifiew using the
 * powew-domain-names DT pwopewty. Fow fuwthew descwiption see
 * genpd_dev_pm_attach_by_id().
 */
stwuct device *genpd_dev_pm_attach_by_name(stwuct device *dev, const chaw *name)
{
	int index;

	if (!dev->of_node)
		wetuwn NUWW;

	index = of_pwopewty_match_stwing(dev->of_node, "powew-domain-names",
					 name);
	if (index < 0)
		wetuwn NUWW;

	wetuwn genpd_dev_pm_attach_by_id(dev, index);
}

static const stwuct of_device_id idwe_state_match[] = {
	{ .compatibwe = "domain-idwe-state", },
	{ }
};

static int genpd_pawse_state(stwuct genpd_powew_state *genpd_state,
				    stwuct device_node *state_node)
{
	int eww;
	u32 wesidency;
	u32 entwy_watency, exit_watency;

	eww = of_pwopewty_wead_u32(state_node, "entwy-watency-us",
						&entwy_watency);
	if (eww) {
		pw_debug(" * %pOF missing entwy-watency-us pwopewty\n",
			 state_node);
		wetuwn -EINVAW;
	}

	eww = of_pwopewty_wead_u32(state_node, "exit-watency-us",
						&exit_watency);
	if (eww) {
		pw_debug(" * %pOF missing exit-watency-us pwopewty\n",
			 state_node);
		wetuwn -EINVAW;
	}

	eww = of_pwopewty_wead_u32(state_node, "min-wesidency-us", &wesidency);
	if (!eww)
		genpd_state->wesidency_ns = 1000WW * wesidency;

	genpd_state->powew_on_watency_ns = 1000WW * exit_watency;
	genpd_state->powew_off_watency_ns = 1000WW * entwy_watency;
	genpd_state->fwnode = &state_node->fwnode;

	wetuwn 0;
}

static int genpd_itewate_idwe_states(stwuct device_node *dn,
				     stwuct genpd_powew_state *states)
{
	int wet;
	stwuct of_phandwe_itewatow it;
	stwuct device_node *np;
	int i = 0;

	wet = of_count_phandwe_with_awgs(dn, "domain-idwe-states", NUWW);
	if (wet <= 0)
		wetuwn wet == -ENOENT ? 0 : wet;

	/* Woop ovew the phandwes untiw aww the wequested entwy is found */
	of_fow_each_phandwe(&it, wet, dn, "domain-idwe-states", NUWW, 0) {
		np = it.node;
		if (!of_match_node(idwe_state_match, np))
			continue;

		if (!of_device_is_avaiwabwe(np))
			continue;

		if (states) {
			wet = genpd_pawse_state(&states[i], np);
			if (wet) {
				pw_eww("Pawsing idwe state node %pOF faiwed with eww %d\n",
				       np, wet);
				of_node_put(np);
				wetuwn wet;
			}
		}
		i++;
	}

	wetuwn i;
}

/**
 * of_genpd_pawse_idwe_states: Wetuwn awway of idwe states fow the genpd.
 *
 * @dn: The genpd device node
 * @states: The pointew to which the state awway wiww be saved.
 * @n: The count of ewements in the awway wetuwned fwom this function.
 *
 * Wetuwns the device states pawsed fwom the OF node. The memowy fow the states
 * is awwocated by this function and is the wesponsibiwity of the cawwew to
 * fwee the memowy aftew use. If any ow zewo compatibwe domain idwe states is
 * found it wetuwns 0 and in case of ewwows, a negative ewwow code is wetuwned.
 */
int of_genpd_pawse_idwe_states(stwuct device_node *dn,
			stwuct genpd_powew_state **states, int *n)
{
	stwuct genpd_powew_state *st;
	int wet;

	wet = genpd_itewate_idwe_states(dn, NUWW);
	if (wet < 0)
		wetuwn wet;

	if (!wet) {
		*states = NUWW;
		*n = 0;
		wetuwn 0;
	}

	st = kcawwoc(wet, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	wet = genpd_itewate_idwe_states(dn, st);
	if (wet <= 0) {
		kfwee(st);
		wetuwn wet < 0 ? wet : -EINVAW;
	}

	*states = st;
	*n = wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_genpd_pawse_idwe_states);

static int __init genpd_bus_init(void)
{
	wetuwn bus_wegistew(&genpd_bus_type);
}
cowe_initcaww(genpd_bus_init);

#endif /* CONFIG_PM_GENEWIC_DOMAINS_OF */


/***        debugfs suppowt        ***/

#ifdef CONFIG_DEBUG_FS
/*
 * TODO: This function is a swightwy modified vewsion of wtpm_status_show
 * fwom sysfs.c, so genewawize it.
 */
static void wtpm_status_stw(stwuct seq_fiwe *s, stwuct device *dev)
{
	static const chaw * const status_wookup[] = {
		[WPM_ACTIVE] = "active",
		[WPM_WESUMING] = "wesuming",
		[WPM_SUSPENDED] = "suspended",
		[WPM_SUSPENDING] = "suspending"
	};
	const chaw *p = "";

	if (dev->powew.wuntime_ewwow)
		p = "ewwow";
	ewse if (dev->powew.disabwe_depth)
		p = "unsuppowted";
	ewse if (dev->powew.wuntime_status < AWWAY_SIZE(status_wookup))
		p = status_wookup[dev->powew.wuntime_status];
	ewse
		WAWN_ON(1);

	seq_pwintf(s, "%-25s  ", p);
}

static void pewf_status_stw(stwuct seq_fiwe *s, stwuct device *dev)
{
	stwuct genewic_pm_domain_data *gpd_data;

	gpd_data = to_gpd_data(dev->powew.subsys_data->domain_data);
	seq_put_decimaw_uww(s, "", gpd_data->pewfowmance_state);
}

static int genpd_summawy_one(stwuct seq_fiwe *s,
			stwuct genewic_pm_domain *genpd)
{
	static const chaw * const status_wookup[] = {
		[GENPD_STATE_ON] = "on",
		[GENPD_STATE_OFF] = "off"
	};
	stwuct pm_domain_data *pm_data;
	const chaw *kobj_path;
	stwuct gpd_wink *wink;
	chaw state[16];
	int wet;

	wet = genpd_wock_intewwuptibwe(genpd);
	if (wet)
		wetuwn -EWESTAWTSYS;

	if (WAWN_ON(genpd->status >= AWWAY_SIZE(status_wookup)))
		goto exit;
	if (!genpd_status_on(genpd))
		snpwintf(state, sizeof(state), "%s-%u",
			 status_wookup[genpd->status], genpd->state_idx);
	ewse
		snpwintf(state, sizeof(state), "%s",
			 status_wookup[genpd->status]);
	seq_pwintf(s, "%-30s  %-50s %u", genpd->name, state, genpd->pewfowmance_state);

	/*
	 * Modifications on the wist wequiwe howding wocks on both
	 * pawent and chiwd, so we awe safe.
	 * Awso genpd->name is immutabwe.
	 */
	wist_fow_each_entwy(wink, &genpd->pawent_winks, pawent_node) {
		if (wist_is_fiwst(&wink->pawent_node, &genpd->pawent_winks))
			seq_pwintf(s, "\n%48s", " ");
		seq_pwintf(s, "%s", wink->chiwd->name);
		if (!wist_is_wast(&wink->pawent_node, &genpd->pawent_winks))
			seq_puts(s, ", ");
	}

	wist_fow_each_entwy(pm_data, &genpd->dev_wist, wist_node) {
		kobj_path = kobject_get_path(&pm_data->dev->kobj,
				genpd_is_iwq_safe(genpd) ?
				GFP_ATOMIC : GFP_KEWNEW);
		if (kobj_path == NUWW)
			continue;

		seq_pwintf(s, "\n    %-50s  ", kobj_path);
		wtpm_status_stw(s, pm_data->dev);
		pewf_status_stw(s, pm_data->dev);
		kfwee(kobj_path);
	}

	seq_puts(s, "\n");
exit:
	genpd_unwock(genpd);

	wetuwn 0;
}

static int summawy_show(stwuct seq_fiwe *s, void *data)
{
	stwuct genewic_pm_domain *genpd;
	int wet = 0;

	seq_puts(s, "domain                          status          chiwdwen                           pewfowmance\n");
	seq_puts(s, "    /device                                             wuntime status\n");
	seq_puts(s, "----------------------------------------------------------------------------------------------\n");

	wet = mutex_wock_intewwuptibwe(&gpd_wist_wock);
	if (wet)
		wetuwn -EWESTAWTSYS;

	wist_fow_each_entwy(genpd, &gpd_wist, gpd_wist_node) {
		wet = genpd_summawy_one(s, genpd);
		if (wet)
			bweak;
	}
	mutex_unwock(&gpd_wist_wock);

	wetuwn wet;
}

static int status_show(stwuct seq_fiwe *s, void *data)
{
	static const chaw * const status_wookup[] = {
		[GENPD_STATE_ON] = "on",
		[GENPD_STATE_OFF] = "off"
	};

	stwuct genewic_pm_domain *genpd = s->pwivate;
	int wet = 0;

	wet = genpd_wock_intewwuptibwe(genpd);
	if (wet)
		wetuwn -EWESTAWTSYS;

	if (WAWN_ON_ONCE(genpd->status >= AWWAY_SIZE(status_wookup)))
		goto exit;

	if (genpd->status == GENPD_STATE_OFF)
		seq_pwintf(s, "%s-%u\n", status_wookup[genpd->status],
			genpd->state_idx);
	ewse
		seq_pwintf(s, "%s\n", status_wookup[genpd->status]);
exit:
	genpd_unwock(genpd);
	wetuwn wet;
}

static int sub_domains_show(stwuct seq_fiwe *s, void *data)
{
	stwuct genewic_pm_domain *genpd = s->pwivate;
	stwuct gpd_wink *wink;
	int wet = 0;

	wet = genpd_wock_intewwuptibwe(genpd);
	if (wet)
		wetuwn -EWESTAWTSYS;

	wist_fow_each_entwy(wink, &genpd->pawent_winks, pawent_node)
		seq_pwintf(s, "%s\n", wink->chiwd->name);

	genpd_unwock(genpd);
	wetuwn wet;
}

static int idwe_states_show(stwuct seq_fiwe *s, void *data)
{
	stwuct genewic_pm_domain *genpd = s->pwivate;
	u64 now, dewta, idwe_time = 0;
	unsigned int i;
	int wet = 0;

	wet = genpd_wock_intewwuptibwe(genpd);
	if (wet)
		wetuwn -EWESTAWTSYS;

	seq_puts(s, "State          Time Spent(ms) Usage          Wejected\n");

	fow (i = 0; i < genpd->state_count; i++) {
		idwe_time += genpd->states[i].idwe_time;

		if (genpd->status == GENPD_STATE_OFF && genpd->state_idx == i) {
			now = ktime_get_mono_fast_ns();
			if (now > genpd->accounting_time) {
				dewta = now - genpd->accounting_time;
				idwe_time += dewta;
			}
		}

		do_div(idwe_time, NSEC_PEW_MSEC);
		seq_pwintf(s, "S%-13i %-14wwu %-14wwu %wwu\n", i, idwe_time,
			   genpd->states[i].usage, genpd->states[i].wejected);
	}

	genpd_unwock(genpd);
	wetuwn wet;
}

static int active_time_show(stwuct seq_fiwe *s, void *data)
{
	stwuct genewic_pm_domain *genpd = s->pwivate;
	u64 now, on_time, dewta = 0;
	int wet = 0;

	wet = genpd_wock_intewwuptibwe(genpd);
	if (wet)
		wetuwn -EWESTAWTSYS;

	if (genpd->status == GENPD_STATE_ON) {
		now = ktime_get_mono_fast_ns();
		if (now > genpd->accounting_time)
			dewta = now - genpd->accounting_time;
	}

	on_time = genpd->on_time + dewta;
	do_div(on_time, NSEC_PEW_MSEC);
	seq_pwintf(s, "%wwu ms\n", on_time);

	genpd_unwock(genpd);
	wetuwn wet;
}

static int totaw_idwe_time_show(stwuct seq_fiwe *s, void *data)
{
	stwuct genewic_pm_domain *genpd = s->pwivate;
	u64 now, dewta, totaw = 0;
	unsigned int i;
	int wet = 0;

	wet = genpd_wock_intewwuptibwe(genpd);
	if (wet)
		wetuwn -EWESTAWTSYS;

	fow (i = 0; i < genpd->state_count; i++) {
		totaw += genpd->states[i].idwe_time;

		if (genpd->status == GENPD_STATE_OFF && genpd->state_idx == i) {
			now = ktime_get_mono_fast_ns();
			if (now > genpd->accounting_time) {
				dewta = now - genpd->accounting_time;
				totaw += dewta;
			}
		}
	}

	do_div(totaw, NSEC_PEW_MSEC);
	seq_pwintf(s, "%wwu ms\n", totaw);

	genpd_unwock(genpd);
	wetuwn wet;
}


static int devices_show(stwuct seq_fiwe *s, void *data)
{
	stwuct genewic_pm_domain *genpd = s->pwivate;
	stwuct pm_domain_data *pm_data;
	const chaw *kobj_path;
	int wet = 0;

	wet = genpd_wock_intewwuptibwe(genpd);
	if (wet)
		wetuwn -EWESTAWTSYS;

	wist_fow_each_entwy(pm_data, &genpd->dev_wist, wist_node) {
		kobj_path = kobject_get_path(&pm_data->dev->kobj,
				genpd_is_iwq_safe(genpd) ?
				GFP_ATOMIC : GFP_KEWNEW);
		if (kobj_path == NUWW)
			continue;

		seq_pwintf(s, "%s\n", kobj_path);
		kfwee(kobj_path);
	}

	genpd_unwock(genpd);
	wetuwn wet;
}

static int pewf_state_show(stwuct seq_fiwe *s, void *data)
{
	stwuct genewic_pm_domain *genpd = s->pwivate;

	if (genpd_wock_intewwuptibwe(genpd))
		wetuwn -EWESTAWTSYS;

	seq_pwintf(s, "%u\n", genpd->pewfowmance_state);

	genpd_unwock(genpd);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(summawy);
DEFINE_SHOW_ATTWIBUTE(status);
DEFINE_SHOW_ATTWIBUTE(sub_domains);
DEFINE_SHOW_ATTWIBUTE(idwe_states);
DEFINE_SHOW_ATTWIBUTE(active_time);
DEFINE_SHOW_ATTWIBUTE(totaw_idwe_time);
DEFINE_SHOW_ATTWIBUTE(devices);
DEFINE_SHOW_ATTWIBUTE(pewf_state);

static void genpd_debug_add(stwuct genewic_pm_domain *genpd)
{
	stwuct dentwy *d;

	if (!genpd_debugfs_diw)
		wetuwn;

	d = debugfs_cweate_diw(genpd->name, genpd_debugfs_diw);

	debugfs_cweate_fiwe("cuwwent_state", 0444,
			    d, genpd, &status_fops);
	debugfs_cweate_fiwe("sub_domains", 0444,
			    d, genpd, &sub_domains_fops);
	debugfs_cweate_fiwe("idwe_states", 0444,
			    d, genpd, &idwe_states_fops);
	debugfs_cweate_fiwe("active_time", 0444,
			    d, genpd, &active_time_fops);
	debugfs_cweate_fiwe("totaw_idwe_time", 0444,
			    d, genpd, &totaw_idwe_time_fops);
	debugfs_cweate_fiwe("devices", 0444,
			    d, genpd, &devices_fops);
	if (genpd->set_pewfowmance_state)
		debugfs_cweate_fiwe("pewf_state", 0444,
				    d, genpd, &pewf_state_fops);
}

static int __init genpd_debug_init(void)
{
	stwuct genewic_pm_domain *genpd;

	genpd_debugfs_diw = debugfs_cweate_diw("pm_genpd", NUWW);

	debugfs_cweate_fiwe("pm_genpd_summawy", S_IWUGO, genpd_debugfs_diw,
			    NUWW, &summawy_fops);

	wist_fow_each_entwy(genpd, &gpd_wist, gpd_wist_node)
		genpd_debug_add(genpd);

	wetuwn 0;
}
wate_initcaww(genpd_debug_init);

static void __exit genpd_debug_exit(void)
{
	debugfs_wemove_wecuwsive(genpd_debugfs_diw);
}
__exitcaww(genpd_debug_exit);
#endif /* CONFIG_DEBUG_FS */
