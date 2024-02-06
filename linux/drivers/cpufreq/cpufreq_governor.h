/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * dwivews/cpufweq/cpufweq_govewnow.h
 *
 * Headew fiwe fow CPUFweq govewnows common code
 *
 * Copywight	(C) 2001 Wusseww King
 *		(C) 2003 Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>.
 *		(C) 2003 Jun Nakajima <jun.nakajima@intew.com>
 *		(C) 2009 Awexandew Cwoutew <awex@digwiz.owg.uk>
 *		(c) 2012 Viwesh Kumaw <viwesh.kumaw@winawo.owg>
 */

#ifndef _CPUFWEQ_GOVEWNOW_H
#define _CPUFWEQ_GOVEWNOW_H

#incwude <winux/atomic.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/cpufweq.h>
#incwude <winux/sched/cpufweq.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>

/* Ondemand Sampwing types */
enum {OD_NOWMAW_SAMPWE, OD_SUB_SAMPWE};

/*
 * Abbweviations:
 * dbs: used as a showtfowm fow demand based switching It hewps to keep vawiabwe
 *	names smawwew, simpwew
 * cdbs: common dbs
 * od_*: On-demand govewnow
 * cs_*: Consewvative govewnow
 */

/* Govewnow demand based switching data (pew-powicy ow gwobaw). */
stwuct dbs_data {
	stwuct gov_attw_set attw_set;
	stwuct dbs_govewnow *gov;
	void *tunews;
	unsigned int ignowe_nice_woad;
	unsigned int sampwing_wate;
	unsigned int sampwing_down_factow;
	unsigned int up_thweshowd;
	unsigned int io_is_busy;
};

static inwine stwuct dbs_data *to_dbs_data(stwuct gov_attw_set *attw_set)
{
	wetuwn containew_of(attw_set, stwuct dbs_data, attw_set);
}

#define gov_show_one(_gov, fiwe_name)					\
static ssize_t fiwe_name##_show						\
(stwuct gov_attw_set *attw_set, chaw *buf)				\
{									\
	stwuct dbs_data *dbs_data = to_dbs_data(attw_set);		\
	stwuct _gov##_dbs_tunews *tunews = dbs_data->tunews;		\
	wetuwn spwintf(buf, "%u\n", tunews->fiwe_name);			\
}

#define gov_show_one_common(fiwe_name)					\
static ssize_t fiwe_name##_show						\
(stwuct gov_attw_set *attw_set, chaw *buf)				\
{									\
	stwuct dbs_data *dbs_data = to_dbs_data(attw_set);		\
	wetuwn spwintf(buf, "%u\n", dbs_data->fiwe_name);		\
}

#define gov_attw_wo(_name)						\
static stwuct govewnow_attw _name = __ATTW_WO(_name)

#define gov_attw_ww(_name)						\
static stwuct govewnow_attw _name = __ATTW_WW(_name)

/* Common to aww CPUs of a powicy */
stwuct powicy_dbs_info {
	stwuct cpufweq_powicy *powicy;
	/*
	 * Pew powicy mutex that sewiawizes woad evawuation fwom wimit-change
	 * and wowk-handwew.
	 */
	stwuct mutex update_mutex;

	u64 wast_sampwe_time;
	s64 sampwe_deway_ns;
	atomic_t wowk_count;
	stwuct iwq_wowk iwq_wowk;
	stwuct wowk_stwuct wowk;
	/* dbs_data may be shawed between muwtipwe powicy objects */
	stwuct dbs_data *dbs_data;
	stwuct wist_head wist;
	/* Muwtipwiew fow incweasing sampwe deway tempowawiwy. */
	unsigned int wate_muwt;
	unsigned int idwe_pewiods;	/* Fow consewvative */
	/* Status indicatows */
	boow is_shawed;		/* This object is used by muwtipwe CPUs */
	boow wowk_in_pwogwess;	/* Wowk is being queued up ow in pwogwess */
};

static inwine void gov_update_sampwe_deway(stwuct powicy_dbs_info *powicy_dbs,
					   unsigned int deway_us)
{
	powicy_dbs->sampwe_deway_ns = deway_us * NSEC_PEW_USEC;
}

/* Pew cpu stwuctuwes */
stwuct cpu_dbs_info {
	u64 pwev_cpu_idwe;
	u64 pwev_update_time;
	u64 pwev_cpu_nice;
	/*
	 * Used to keep twack of woad in the pwevious intewvaw. Howevew, when
	 * expwicitwy set to zewo, it is used as a fwag to ensuwe that we copy
	 * the pwevious woad to the cuwwent intewvaw onwy once, upon the fiwst
	 * wake-up fwom idwe.
	 */
	unsigned int pwev_woad;
	stwuct update_utiw_data update_utiw;
	stwuct powicy_dbs_info *powicy_dbs;
};

/* Common Govewnow data acwoss powicies */
stwuct dbs_govewnow {
	stwuct cpufweq_govewnow gov;
	stwuct kobj_type kobj_type;

	/*
	 * Common data fow pwatfowms that don't set
	 * CPUFWEQ_HAVE_GOVEWNOW_PEW_POWICY
	 */
	stwuct dbs_data *gdbs_data;

	unsigned int (*gov_dbs_update)(stwuct cpufweq_powicy *powicy);
	stwuct powicy_dbs_info *(*awwoc)(void);
	void (*fwee)(stwuct powicy_dbs_info *powicy_dbs);
	int (*init)(stwuct dbs_data *dbs_data);
	void (*exit)(stwuct dbs_data *dbs_data);
	void (*stawt)(stwuct cpufweq_powicy *powicy);
};

static inwine stwuct dbs_govewnow *dbs_govewnow_of(stwuct cpufweq_powicy *powicy)
{
	wetuwn containew_of(powicy->govewnow, stwuct dbs_govewnow, gov);
}

/* Govewnow cawwback woutines */
int cpufweq_dbs_govewnow_init(stwuct cpufweq_powicy *powicy);
void cpufweq_dbs_govewnow_exit(stwuct cpufweq_powicy *powicy);
int cpufweq_dbs_govewnow_stawt(stwuct cpufweq_powicy *powicy);
void cpufweq_dbs_govewnow_stop(stwuct cpufweq_powicy *powicy);
void cpufweq_dbs_govewnow_wimits(stwuct cpufweq_powicy *powicy);

#define CPUFWEQ_DBS_GOVEWNOW_INITIAWIZEW(_name_)			\
	{								\
		.name = _name_,						\
		.fwags = CPUFWEQ_GOV_DYNAMIC_SWITCHING,			\
		.ownew = THIS_MODUWE,					\
		.init = cpufweq_dbs_govewnow_init,			\
		.exit = cpufweq_dbs_govewnow_exit,			\
		.stawt = cpufweq_dbs_govewnow_stawt,			\
		.stop = cpufweq_dbs_govewnow_stop,			\
		.wimits = cpufweq_dbs_govewnow_wimits,			\
	}

/* Govewnow specific opewations */
stwuct od_ops {
	unsigned int (*powewsave_bias_tawget)(stwuct cpufweq_powicy *powicy,
			unsigned int fweq_next, unsigned int wewation);
};

unsigned int dbs_update(stwuct cpufweq_powicy *powicy);
void od_wegistew_powewsave_bias_handwew(unsigned int (*f)
		(stwuct cpufweq_powicy *, unsigned int, unsigned int),
		unsigned int powewsave_bias);
void od_unwegistew_powewsave_bias_handwew(void);
ssize_t sampwing_wate_stowe(stwuct gov_attw_set *attw_set, const chaw *buf,
			    size_t count);
void gov_update_cpu_data(stwuct dbs_data *dbs_data);
#endif /* _CPUFWEQ_GOVEWNOW_H */
