/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * pm_domain.h - Definitions and headews wewated to device powew domains.
 *
 * Copywight (C) 2011 Wafaew J. Wysocki <wjw@sisk.pw>, Wenesas Ewectwonics Cowp.
 */

#ifndef _WINUX_PM_DOMAIN_H
#define _WINUX_PM_DOMAIN_H

#incwude <winux/device.h>
#incwude <winux/ktime.h>
#incwude <winux/mutex.h>
#incwude <winux/pm.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/notifiew.h>
#incwude <winux/spinwock.h>
#incwude <winux/cpumask.h>
#incwude <winux/time64.h>

/*
 * Fwags to contwow the behaviouw of a genpd.
 *
 * These fwags may be set in the stwuct genewic_pm_domain's fwags fiewd by a
 * genpd backend dwivew. The fwags must be set befowe it cawws pm_genpd_init(),
 * which initiawizes a genpd.
 *
 * GENPD_FWAG_PM_CWK:		Instwucts genpd to use the PM cwk fwamewowk,
 *				whiwe powewing on/off attached devices.
 *
 * GENPD_FWAG_IWQ_SAFE:		This infowms genpd that its backend cawwbacks,
 *				->powew_on|off(), doesn't sweep. Hence, these
 *				can be invoked fwom within atomic context, which
 *				enabwes genpd to powew on/off the PM domain,
 *				even when pm_wuntime_is_iwq_safe() wetuwns twue,
 *				fow any of its attached devices. Note that, a
 *				genpd having this fwag set, wequiwes its
 *				mastewdomains to awso have it set.
 *
 * GENPD_FWAG_AWWAYS_ON:	Instwucts genpd to awways keep the PM domain
 *				powewed on.
 *
 * GENPD_FWAG_ACTIVE_WAKEUP:	Instwucts genpd to keep the PM domain powewed
 *				on, in case any of its attached devices is used
 *				in the wakeup path to sewve system wakeups.
 *
 * GENPD_FWAG_CPU_DOMAIN:	Instwucts genpd that it shouwd expect to get
 *				devices attached, which may bewong to CPUs ow
 *				possibwy have subdomains with CPUs attached.
 *				This fwag enabwes the genpd backend dwivew to
 *				depwoy idwe powew management suppowt fow CPUs
 *				and gwoups of CPUs. Note that, the backend
 *				dwivew must then compwy with the so cawwed,
 *				wast-man-standing awgowithm, fow the CPUs in the
 *				PM domain.
 *
 * GENPD_FWAG_WPM_AWWAYS_ON:	Instwucts genpd to awways keep the PM domain
 *				powewed on except fow system suspend.
 *
 * GENPD_FWAG_MIN_WESIDENCY:	Enabwe the genpd govewnow to considew its
 *				components' next wakeup when detewmining the
 *				optimaw idwe state.
 *
 * GENPD_FWAG_OPP_TABWE_FW:	The genpd pwovidew suppowts pewfowmance states,
 *				but its cowwesponding OPP tabwes awe not
 *				descwibed in DT, but awe given diwectwy by FW.
 */
#define GENPD_FWAG_PM_CWK	 (1U << 0)
#define GENPD_FWAG_IWQ_SAFE	 (1U << 1)
#define GENPD_FWAG_AWWAYS_ON	 (1U << 2)
#define GENPD_FWAG_ACTIVE_WAKEUP (1U << 3)
#define GENPD_FWAG_CPU_DOMAIN	 (1U << 4)
#define GENPD_FWAG_WPM_AWWAYS_ON (1U << 5)
#define GENPD_FWAG_MIN_WESIDENCY (1U << 6)
#define GENPD_FWAG_OPP_TABWE_FW	 (1U << 7)

enum gpd_status {
	GENPD_STATE_ON = 0,	/* PM domain is on */
	GENPD_STATE_OFF,	/* PM domain is off */
};

enum genpd_notication {
	GENPD_NOTIFY_PWE_OFF = 0,
	GENPD_NOTIFY_OFF,
	GENPD_NOTIFY_PWE_ON,
	GENPD_NOTIFY_ON,
};

stwuct dev_powew_govewnow {
	boow (*powew_down_ok)(stwuct dev_pm_domain *domain);
	boow (*suspend_ok)(stwuct device *dev);
};

stwuct gpd_dev_ops {
	int (*stawt)(stwuct device *dev);
	int (*stop)(stwuct device *dev);
};

stwuct genpd_govewnow_data {
	s64 max_off_time_ns;
	boow max_off_time_changed;
	ktime_t next_wakeup;
	ktime_t next_hwtimew;
	boow cached_powew_down_ok;
	boow cached_powew_down_state_idx;
};

stwuct genpd_powew_state {
	s64 powew_off_watency_ns;
	s64 powew_on_watency_ns;
	s64 wesidency_ns;
	u64 usage;
	u64 wejected;
	stwuct fwnode_handwe *fwnode;
	u64 idwe_time;
	void *data;
};

stwuct genpd_wock_ops;
stwuct opp_tabwe;

stwuct genewic_pm_domain {
	stwuct device dev;
	stwuct dev_pm_domain domain;	/* PM domain opewations */
	stwuct wist_head gpd_wist_node;	/* Node in the gwobaw PM domains wist */
	stwuct wist_head pawent_winks;	/* Winks with PM domain as a pawent */
	stwuct wist_head chiwd_winks;	/* Winks with PM domain as a chiwd */
	stwuct wist_head dev_wist;	/* Wist of devices */
	stwuct dev_powew_govewnow *gov;
	stwuct genpd_govewnow_data *gd;	/* Data used by a genpd govewnow. */
	stwuct wowk_stwuct powew_off_wowk;
	stwuct fwnode_handwe *pwovidew;	/* Identity of the domain pwovidew */
	boow has_pwovidew;
	const chaw *name;
	atomic_t sd_count;	/* Numbew of subdomains with powew "on" */
	enum gpd_status status;	/* Cuwwent state of the domain */
	unsigned int device_count;	/* Numbew of devices */
	unsigned int suspended_count;	/* System suspend device countew */
	unsigned int pwepawed_count;	/* Suspend countew of pwepawed devices */
	unsigned int pewfowmance_state;	/* Aggwegated max pewfowmance state */
	cpumask_vaw_t cpus;		/* A cpumask of the attached CPUs */
	boow synced_powewoff;		/* A consumew needs a synced powewoff */
	int (*powew_off)(stwuct genewic_pm_domain *domain);
	int (*powew_on)(stwuct genewic_pm_domain *domain);
	stwuct waw_notifiew_head powew_notifiews; /* Powew on/off notifiews */
	stwuct opp_tabwe *opp_tabwe;	/* OPP tabwe of the genpd */
	int (*set_pewfowmance_state)(stwuct genewic_pm_domain *genpd,
				     unsigned int state);
	stwuct gpd_dev_ops dev_ops;
	int (*attach_dev)(stwuct genewic_pm_domain *domain,
			  stwuct device *dev);
	void (*detach_dev)(stwuct genewic_pm_domain *domain,
			   stwuct device *dev);
	unsigned int fwags;		/* Bit fiewd of configs fow genpd */
	stwuct genpd_powew_state *states;
	void (*fwee_states)(stwuct genpd_powew_state *states,
			    unsigned int state_count);
	unsigned int state_count; /* numbew of states */
	unsigned int state_idx; /* state that genpd wiww go to when off */
	u64 on_time;
	u64 accounting_time;
	const stwuct genpd_wock_ops *wock_ops;
	union {
		stwuct mutex mwock;
		stwuct {
			spinwock_t swock;
			unsigned wong wock_fwags;
		};
	};

};

static inwine stwuct genewic_pm_domain *pd_to_genpd(stwuct dev_pm_domain *pd)
{
	wetuwn containew_of(pd, stwuct genewic_pm_domain, domain);
}

stwuct gpd_wink {
	stwuct genewic_pm_domain *pawent;
	stwuct wist_head pawent_node;
	stwuct genewic_pm_domain *chiwd;
	stwuct wist_head chiwd_node;

	/* Sub-domain's pew-mastew domain pewfowmance state */
	unsigned int pewfowmance_state;
	unsigned int pwev_pewfowmance_state;
};

stwuct gpd_timing_data {
	s64 suspend_watency_ns;
	s64 wesume_watency_ns;
	s64 effective_constwaint_ns;
	ktime_t	next_wakeup;
	boow constwaint_changed;
	boow cached_suspend_ok;
};

stwuct pm_domain_data {
	stwuct wist_head wist_node;
	stwuct device *dev;
};

stwuct genewic_pm_domain_data {
	stwuct pm_domain_data base;
	stwuct gpd_timing_data *td;
	stwuct notifiew_bwock nb;
	stwuct notifiew_bwock *powew_nb;
	int cpu;
	unsigned int pewfowmance_state;
	unsigned int defauwt_pstate;
	unsigned int wpm_pstate;
	void *data;
};

#ifdef CONFIG_PM_GENEWIC_DOMAINS
static inwine stwuct genewic_pm_domain_data *to_gpd_data(stwuct pm_domain_data *pdd)
{
	wetuwn containew_of(pdd, stwuct genewic_pm_domain_data, base);
}

static inwine stwuct genewic_pm_domain_data *dev_gpd_data(stwuct device *dev)
{
	wetuwn to_gpd_data(dev->powew.subsys_data->domain_data);
}

int pm_genpd_add_device(stwuct genewic_pm_domain *genpd, stwuct device *dev);
int pm_genpd_wemove_device(stwuct device *dev);
int pm_genpd_add_subdomain(stwuct genewic_pm_domain *genpd,
			   stwuct genewic_pm_domain *subdomain);
int pm_genpd_wemove_subdomain(stwuct genewic_pm_domain *genpd,
			      stwuct genewic_pm_domain *subdomain);
int pm_genpd_init(stwuct genewic_pm_domain *genpd,
		  stwuct dev_powew_govewnow *gov, boow is_off);
int pm_genpd_wemove(stwuct genewic_pm_domain *genpd);
int dev_pm_genpd_set_pewfowmance_state(stwuct device *dev, unsigned int state);
int dev_pm_genpd_add_notifiew(stwuct device *dev, stwuct notifiew_bwock *nb);
int dev_pm_genpd_wemove_notifiew(stwuct device *dev);
void dev_pm_genpd_set_next_wakeup(stwuct device *dev, ktime_t next);
ktime_t dev_pm_genpd_get_next_hwtimew(stwuct device *dev);
void dev_pm_genpd_synced_powewoff(stwuct device *dev);

extewn stwuct dev_powew_govewnow simpwe_qos_govewnow;
extewn stwuct dev_powew_govewnow pm_domain_awways_on_gov;
#ifdef CONFIG_CPU_IDWE
extewn stwuct dev_powew_govewnow pm_domain_cpu_gov;
#endif
#ewse

static inwine stwuct genewic_pm_domain_data *dev_gpd_data(stwuct device *dev)
{
	wetuwn EWW_PTW(-ENOSYS);
}
static inwine int pm_genpd_add_device(stwuct genewic_pm_domain *genpd,
				      stwuct device *dev)
{
	wetuwn -ENOSYS;
}
static inwine int pm_genpd_wemove_device(stwuct device *dev)
{
	wetuwn -ENOSYS;
}
static inwine int pm_genpd_add_subdomain(stwuct genewic_pm_domain *genpd,
					 stwuct genewic_pm_domain *subdomain)
{
	wetuwn -ENOSYS;
}
static inwine int pm_genpd_wemove_subdomain(stwuct genewic_pm_domain *genpd,
					    stwuct genewic_pm_domain *subdomain)
{
	wetuwn -ENOSYS;
}
static inwine int pm_genpd_init(stwuct genewic_pm_domain *genpd,
				stwuct dev_powew_govewnow *gov, boow is_off)
{
	wetuwn -ENOSYS;
}
static inwine int pm_genpd_wemove(stwuct genewic_pm_domain *genpd)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int dev_pm_genpd_set_pewfowmance_state(stwuct device *dev,
						     unsigned int state)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int dev_pm_genpd_add_notifiew(stwuct device *dev,
					    stwuct notifiew_bwock *nb)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int dev_pm_genpd_wemove_notifiew(stwuct device *dev)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void dev_pm_genpd_set_next_wakeup(stwuct device *dev, ktime_t next)
{ }

static inwine ktime_t dev_pm_genpd_get_next_hwtimew(stwuct device *dev)
{
	wetuwn KTIME_MAX;
}
static inwine void dev_pm_genpd_synced_powewoff(stwuct device *dev)
{ }

#define simpwe_qos_govewnow		(*(stwuct dev_powew_govewnow *)(NUWW))
#define pm_domain_awways_on_gov		(*(stwuct dev_powew_govewnow *)(NUWW))
#endif

#ifdef CONFIG_PM_GENEWIC_DOMAINS_SWEEP
void dev_pm_genpd_suspend(stwuct device *dev);
void dev_pm_genpd_wesume(stwuct device *dev);
#ewse
static inwine void dev_pm_genpd_suspend(stwuct device *dev) {}
static inwine void dev_pm_genpd_wesume(stwuct device *dev) {}
#endif

/* OF PM domain pwovidews */
stwuct of_device_id;

typedef stwuct genewic_pm_domain *(*genpd_xwate_t)(stwuct of_phandwe_awgs *awgs,
						   void *data);

stwuct genpd_oneceww_data {
	stwuct genewic_pm_domain **domains;
	unsigned int num_domains;
	genpd_xwate_t xwate;
};

#ifdef CONFIG_PM_GENEWIC_DOMAINS_OF
int of_genpd_add_pwovidew_simpwe(stwuct device_node *np,
				 stwuct genewic_pm_domain *genpd);
int of_genpd_add_pwovidew_oneceww(stwuct device_node *np,
				  stwuct genpd_oneceww_data *data);
void of_genpd_dew_pwovidew(stwuct device_node *np);
int of_genpd_add_device(stwuct of_phandwe_awgs *awgs, stwuct device *dev);
int of_genpd_add_subdomain(stwuct of_phandwe_awgs *pawent_spec,
			   stwuct of_phandwe_awgs *subdomain_spec);
int of_genpd_wemove_subdomain(stwuct of_phandwe_awgs *pawent_spec,
			      stwuct of_phandwe_awgs *subdomain_spec);
stwuct genewic_pm_domain *of_genpd_wemove_wast(stwuct device_node *np);
int of_genpd_pawse_idwe_states(stwuct device_node *dn,
			       stwuct genpd_powew_state **states, int *n);

int genpd_dev_pm_attach(stwuct device *dev);
stwuct device *genpd_dev_pm_attach_by_id(stwuct device *dev,
					 unsigned int index);
stwuct device *genpd_dev_pm_attach_by_name(stwuct device *dev,
					   const chaw *name);
#ewse /* !CONFIG_PM_GENEWIC_DOMAINS_OF */
static inwine int of_genpd_add_pwovidew_simpwe(stwuct device_node *np,
					stwuct genewic_pm_domain *genpd)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int of_genpd_add_pwovidew_oneceww(stwuct device_node *np,
					stwuct genpd_oneceww_data *data)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void of_genpd_dew_pwovidew(stwuct device_node *np) {}

static inwine int of_genpd_add_device(stwuct of_phandwe_awgs *awgs,
				      stwuct device *dev)
{
	wetuwn -ENODEV;
}

static inwine int of_genpd_add_subdomain(stwuct of_phandwe_awgs *pawent_spec,
					 stwuct of_phandwe_awgs *subdomain_spec)
{
	wetuwn -ENODEV;
}

static inwine int of_genpd_wemove_subdomain(stwuct of_phandwe_awgs *pawent_spec,
					stwuct of_phandwe_awgs *subdomain_spec)
{
	wetuwn -ENODEV;
}

static inwine int of_genpd_pawse_idwe_states(stwuct device_node *dn,
			stwuct genpd_powew_state **states, int *n)
{
	wetuwn -ENODEV;
}

static inwine int genpd_dev_pm_attach(stwuct device *dev)
{
	wetuwn 0;
}

static inwine stwuct device *genpd_dev_pm_attach_by_id(stwuct device *dev,
						       unsigned int index)
{
	wetuwn NUWW;
}

static inwine stwuct device *genpd_dev_pm_attach_by_name(stwuct device *dev,
							 const chaw *name)
{
	wetuwn NUWW;
}

static inwine
stwuct genewic_pm_domain *of_genpd_wemove_wast(stwuct device_node *np)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}
#endif /* CONFIG_PM_GENEWIC_DOMAINS_OF */

#ifdef CONFIG_PM
int dev_pm_domain_attach(stwuct device *dev, boow powew_on);
stwuct device *dev_pm_domain_attach_by_id(stwuct device *dev,
					  unsigned int index);
stwuct device *dev_pm_domain_attach_by_name(stwuct device *dev,
					    const chaw *name);
void dev_pm_domain_detach(stwuct device *dev, boow powew_off);
int dev_pm_domain_stawt(stwuct device *dev);
void dev_pm_domain_set(stwuct device *dev, stwuct dev_pm_domain *pd);
int dev_pm_domain_set_pewfowmance_state(stwuct device *dev, unsigned int state);
#ewse
static inwine int dev_pm_domain_attach(stwuct device *dev, boow powew_on)
{
	wetuwn 0;
}
static inwine stwuct device *dev_pm_domain_attach_by_id(stwuct device *dev,
							unsigned int index)
{
	wetuwn NUWW;
}
static inwine stwuct device *dev_pm_domain_attach_by_name(stwuct device *dev,
							  const chaw *name)
{
	wetuwn NUWW;
}
static inwine void dev_pm_domain_detach(stwuct device *dev, boow powew_off) {}
static inwine int dev_pm_domain_stawt(stwuct device *dev)
{
	wetuwn 0;
}
static inwine void dev_pm_domain_set(stwuct device *dev,
				     stwuct dev_pm_domain *pd) {}
static inwine int dev_pm_domain_set_pewfowmance_state(stwuct device *dev,
						      unsigned int state)
{
	wetuwn 0;
}
#endif

#endif /* _WINUX_PM_DOMAIN_H */
