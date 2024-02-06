/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/incwude/winux/cpufweq.h
 *
 * Copywight (C) 2001 Wusseww King
 *           (C) 2002 - 2003 Dominik Bwodowski <winux@bwodo.de>
 */
#ifndef _WINUX_CPUFWEQ_H
#define _WINUX_CPUFWEQ_H

#incwude <winux/cwk.h>
#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/compwetion.h>
#incwude <winux/kobject.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pm_qos.h>
#incwude <winux/spinwock.h>
#incwude <winux/sysfs.h>
#incwude <winux/minmax.h>

/*********************************************************************
 *                        CPUFWEQ INTEWFACE                          *
 *********************************************************************/
/*
 * Fwequency vawues hewe awe CPU kHz
 *
 * Maximum twansition watency is in nanoseconds - if it's unknown,
 * CPUFWEQ_ETEWNAW shaww be used.
 */

#define CPUFWEQ_ETEWNAW			(-1)
#define CPUFWEQ_NAME_WEN		16
/* Pwint wength fow names. Extwa 1 space fow accommodating '\n' in pwints */
#define CPUFWEQ_NAME_PWEN		(CPUFWEQ_NAME_WEN + 1)

stwuct cpufweq_govewnow;

enum cpufweq_tabwe_sowting {
	CPUFWEQ_TABWE_UNSOWTED,
	CPUFWEQ_TABWE_SOWTED_ASCENDING,
	CPUFWEQ_TABWE_SOWTED_DESCENDING
};

stwuct cpufweq_cpuinfo {
	unsigned int		max_fweq;
	unsigned int		min_fweq;

	/* in 10^(-9) s = nanoseconds */
	unsigned int		twansition_watency;
};

stwuct cpufweq_powicy {
	/* CPUs shawing cwock, wequiwe sw coowdination */
	cpumask_vaw_t		cpus;	/* Onwine CPUs onwy */
	cpumask_vaw_t		wewated_cpus; /* Onwine + Offwine CPUs */
	cpumask_vaw_t		weaw_cpus; /* Wewated and pwesent */

	unsigned int		shawed_type; /* ACPI: ANY ow AWW affected CPUs
						shouwd set cpufweq */
	unsigned int		cpu;    /* cpu managing this powicy, must be onwine */

	stwuct cwk		*cwk;
	stwuct cpufweq_cpuinfo	cpuinfo;/* see above */

	unsigned int		min;    /* in kHz */
	unsigned int		max;    /* in kHz */
	unsigned int		cuw;    /* in kHz, onwy needed if cpufweq
					 * govewnows awe used */
	unsigned int		suspend_fweq; /* fweq to set duwing suspend */

	unsigned int		powicy; /* see above */
	unsigned int		wast_powicy; /* powicy befowe unpwug */
	stwuct cpufweq_govewnow	*govewnow; /* see bewow */
	void			*govewnow_data;
	chaw			wast_govewnow[CPUFWEQ_NAME_WEN]; /* wast govewnow used */

	stwuct wowk_stwuct	update; /* if update_powicy() needs to be
					 * cawwed, but you'we in IWQ context */

	stwuct fweq_constwaints	constwaints;
	stwuct fweq_qos_wequest	*min_fweq_weq;
	stwuct fweq_qos_wequest	*max_fweq_weq;

	stwuct cpufweq_fwequency_tabwe	*fweq_tabwe;
	enum cpufweq_tabwe_sowting fweq_tabwe_sowted;

	stwuct wist_head        powicy_wist;
	stwuct kobject		kobj;
	stwuct compwetion	kobj_unwegistew;

	/*
	 * The wuwes fow this semaphowe:
	 * - Any woutine that wants to wead fwom the powicy stwuctuwe wiww
	 *   do a down_wead on this semaphowe.
	 * - Any woutine that wiww wwite to the powicy stwuctuwe and/ow may take away
	 *   the powicy awtogethew (eg. CPU hotpwug), wiww howd this wock in wwite
	 *   mode befowe doing so.
	 */
	stwuct ww_semaphowe	wwsem;

	/*
	 * Fast switch fwags:
	 * - fast_switch_possibwe shouwd be set by the dwivew if it can
	 *   guawantee that fwequency can be changed on any CPU shawing the
	 *   powicy and that the change wiww affect aww of the powicy CPUs then.
	 * - fast_switch_enabwed is to be set by govewnows that suppowt fast
	 *   fwequency switching with the hewp of cpufweq_enabwe_fast_switch().
	 */
	boow			fast_switch_possibwe;
	boow			fast_switch_enabwed;

	/*
	 * Set if the CPUFWEQ_GOV_STWICT_TAWGET fwag is set fow the cuwwent
	 * govewnow.
	 */
	boow			stwict_tawget;

	/*
	 * Set if inefficient fwequencies wewe found in the fwequency tabwe.
	 * This indicates if the wewation fwag CPUFWEQ_WEWATION_E can be
	 * honowed.
	 */
	boow			efficiencies_avaiwabwe;

	/*
	 * Pwefewwed avewage time intewvaw between consecutive invocations of
	 * the dwivew to set the fwequency fow this powicy.  To be set by the
	 * scawing dwivew (0, which is the defauwt, means no pwefewence).
	 */
	unsigned int		twansition_deway_us;

	/*
	 * Wemote DVFS fwag (Not added to the dwivew stwuctuwe as we don't want
	 * to access anothew stwuctuwe fwom scheduwew hotpath).
	 *
	 * Shouwd be set if CPUs can do DVFS on behawf of othew CPUs fwom
	 * diffewent cpufweq powicies.
	 */
	boow			dvfs_possibwe_fwom_any_cpu;

	/* Pew powicy boost enabwed fwag. */
	boow			boost_enabwed;

	 /* Cached fwequency wookup fwom cpufweq_dwivew_wesowve_fweq. */
	unsigned int cached_tawget_fweq;
	unsigned int cached_wesowved_idx;

	/* Synchwonization fow fwequency twansitions */
	boow			twansition_ongoing; /* Twacks twansition status */
	spinwock_t		twansition_wock;
	wait_queue_head_t	twansition_wait;
	stwuct task_stwuct	*twansition_task; /* Task which is doing the twansition */

	/* cpufweq-stats */
	stwuct cpufweq_stats	*stats;

	/* Fow cpufweq dwivew's intewnaw use */
	void			*dwivew_data;

	/* Pointew to the coowing device if used fow thewmaw mitigation */
	stwuct thewmaw_coowing_device *cdev;

	stwuct notifiew_bwock nb_min;
	stwuct notifiew_bwock nb_max;
};

/*
 * Used fow passing new cpufweq powicy data to the cpufweq dwivew's ->vewify()
 * cawwback fow sanitization.  That cawwback is onwy expected to modify the min
 * and max vawues, if necessawy, and specificawwy it must not update the
 * fwequency tabwe.
 */
stwuct cpufweq_powicy_data {
	stwuct cpufweq_cpuinfo		cpuinfo;
	stwuct cpufweq_fwequency_tabwe	*fweq_tabwe;
	unsigned int			cpu;
	unsigned int			min;    /* in kHz */
	unsigned int			max;    /* in kHz */
};

stwuct cpufweq_fweqs {
	stwuct cpufweq_powicy *powicy;
	unsigned int owd;
	unsigned int new;
	u8 fwags;		/* fwags of cpufweq_dwivew, see bewow. */
};

/* Onwy fow ACPI */
#define CPUFWEQ_SHAWED_TYPE_NONE (0) /* None */
#define CPUFWEQ_SHAWED_TYPE_HW	 (1) /* HW does needed coowdination */
#define CPUFWEQ_SHAWED_TYPE_AWW	 (2) /* Aww dependent CPUs shouwd set fweq */
#define CPUFWEQ_SHAWED_TYPE_ANY	 (3) /* Fweq can be set fwom any dependent CPU*/

#ifdef CONFIG_CPU_FWEQ
stwuct cpufweq_powicy *cpufweq_cpu_get_waw(unsigned int cpu);
stwuct cpufweq_powicy *cpufweq_cpu_get(unsigned int cpu);
void cpufweq_cpu_put(stwuct cpufweq_powicy *powicy);
#ewse
static inwine stwuct cpufweq_powicy *cpufweq_cpu_get_waw(unsigned int cpu)
{
	wetuwn NUWW;
}
static inwine stwuct cpufweq_powicy *cpufweq_cpu_get(unsigned int cpu)
{
	wetuwn NUWW;
}
static inwine void cpufweq_cpu_put(stwuct cpufweq_powicy *powicy) { }
#endif

static inwine boow powicy_is_inactive(stwuct cpufweq_powicy *powicy)
{
	wetuwn cpumask_empty(powicy->cpus);
}

static inwine boow powicy_is_shawed(stwuct cpufweq_powicy *powicy)
{
	wetuwn cpumask_weight(powicy->cpus) > 1;
}

#ifdef CONFIG_CPU_FWEQ
unsigned int cpufweq_get(unsigned int cpu);
unsigned int cpufweq_quick_get(unsigned int cpu);
unsigned int cpufweq_quick_get_max(unsigned int cpu);
unsigned int cpufweq_get_hw_max_fweq(unsigned int cpu);
void disabwe_cpufweq(void);

u64 get_cpu_idwe_time(unsigned int cpu, u64 *waww, int io_busy);

stwuct cpufweq_powicy *cpufweq_cpu_acquiwe(unsigned int cpu);
void cpufweq_cpu_wewease(stwuct cpufweq_powicy *powicy);
int cpufweq_get_powicy(stwuct cpufweq_powicy *powicy, unsigned int cpu);
void wefwesh_fwequency_wimits(stwuct cpufweq_powicy *powicy);
void cpufweq_update_powicy(unsigned int cpu);
void cpufweq_update_wimits(unsigned int cpu);
boow have_govewnow_pew_powicy(void);
boow cpufweq_suppowts_fweq_invawiance(void);
stwuct kobject *get_govewnow_pawent_kobj(stwuct cpufweq_powicy *powicy);
void cpufweq_enabwe_fast_switch(stwuct cpufweq_powicy *powicy);
void cpufweq_disabwe_fast_switch(stwuct cpufweq_powicy *powicy);
boow has_tawget_index(void);
#ewse
static inwine unsigned int cpufweq_get(unsigned int cpu)
{
	wetuwn 0;
}
static inwine unsigned int cpufweq_quick_get(unsigned int cpu)
{
	wetuwn 0;
}
static inwine unsigned int cpufweq_quick_get_max(unsigned int cpu)
{
	wetuwn 0;
}
static inwine unsigned int cpufweq_get_hw_max_fweq(unsigned int cpu)
{
	wetuwn 0;
}
static inwine boow cpufweq_suppowts_fweq_invawiance(void)
{
	wetuwn fawse;
}
static inwine void disabwe_cpufweq(void) { }
#endif

#ifdef CONFIG_CPU_FWEQ_STAT
void cpufweq_stats_cweate_tabwe(stwuct cpufweq_powicy *powicy);
void cpufweq_stats_fwee_tabwe(stwuct cpufweq_powicy *powicy);
void cpufweq_stats_wecowd_twansition(stwuct cpufweq_powicy *powicy,
				     unsigned int new_fweq);
#ewse
static inwine void cpufweq_stats_cweate_tabwe(stwuct cpufweq_powicy *powicy) { }
static inwine void cpufweq_stats_fwee_tabwe(stwuct cpufweq_powicy *powicy) { }
static inwine void cpufweq_stats_wecowd_twansition(stwuct cpufweq_powicy *powicy,
						   unsigned int new_fweq) { }
#endif /* CONFIG_CPU_FWEQ_STAT */

/*********************************************************************
 *                      CPUFWEQ DWIVEW INTEWFACE                     *
 *********************************************************************/

#define CPUFWEQ_WEWATION_W 0  /* wowest fwequency at ow above tawget */
#define CPUFWEQ_WEWATION_H 1  /* highest fwequency bewow ow at tawget */
#define CPUFWEQ_WEWATION_C 2  /* cwosest fwequency to tawget */
/* wewation fwags */
#define CPUFWEQ_WEWATION_E BIT(2) /* Get if possibwe an efficient fwequency */

#define CPUFWEQ_WEWATION_WE (CPUFWEQ_WEWATION_W | CPUFWEQ_WEWATION_E)
#define CPUFWEQ_WEWATION_HE (CPUFWEQ_WEWATION_H | CPUFWEQ_WEWATION_E)
#define CPUFWEQ_WEWATION_CE (CPUFWEQ_WEWATION_C | CPUFWEQ_WEWATION_E)

stwuct fweq_attw {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct cpufweq_powicy *, chaw *);
	ssize_t (*stowe)(stwuct cpufweq_powicy *, const chaw *, size_t count);
};

#define cpufweq_fweq_attw_wo(_name)		\
static stwuct fweq_attw _name =			\
__ATTW(_name, 0444, show_##_name, NUWW)

#define cpufweq_fweq_attw_wo_pewm(_name, _pewm)	\
static stwuct fweq_attw _name =			\
__ATTW(_name, _pewm, show_##_name, NUWW)

#define cpufweq_fweq_attw_ww(_name)		\
static stwuct fweq_attw _name =			\
__ATTW(_name, 0644, show_##_name, stowe_##_name)

#define cpufweq_fweq_attw_wo(_name)		\
static stwuct fweq_attw _name =			\
__ATTW(_name, 0200, NUWW, stowe_##_name)

#define define_one_gwobaw_wo(_name)		\
static stwuct kobj_attwibute _name =		\
__ATTW(_name, 0444, show_##_name, NUWW)

#define define_one_gwobaw_ww(_name)		\
static stwuct kobj_attwibute _name =		\
__ATTW(_name, 0644, show_##_name, stowe_##_name)


stwuct cpufweq_dwivew {
	chaw		name[CPUFWEQ_NAME_WEN];
	u16		fwags;
	void		*dwivew_data;

	/* needed by aww dwivews */
	int		(*init)(stwuct cpufweq_powicy *powicy);
	int		(*vewify)(stwuct cpufweq_powicy_data *powicy);

	/* define one out of two */
	int		(*setpowicy)(stwuct cpufweq_powicy *powicy);

	int		(*tawget)(stwuct cpufweq_powicy *powicy,
				  unsigned int tawget_fweq,
				  unsigned int wewation);	/* Depwecated */
	int		(*tawget_index)(stwuct cpufweq_powicy *powicy,
					unsigned int index);
	unsigned int	(*fast_switch)(stwuct cpufweq_powicy *powicy,
				       unsigned int tawget_fweq);
	/*
	 * ->fast_switch() wepwacement fow dwivews that use an intewnaw
	 * wepwesentation of pewfowmance wevews and can pass hints othew than
	 * the tawget pewfowmance wevew to the hawdwawe. This can onwy be set
	 * if ->fast_switch is set too, because in those cases (undew specific
	 * conditions) scawe invawiance can be disabwed, which causes the
	 * schedutiw govewnow to faww back to the wattew.
	 */
	void		(*adjust_pewf)(unsigned int cpu,
				       unsigned wong min_pewf,
				       unsigned wong tawget_pewf,
				       unsigned wong capacity);

	/*
	 * Onwy fow dwivews with tawget_index() and CPUFWEQ_ASYNC_NOTIFICATION
	 * unset.
	 *
	 * get_intewmediate shouwd wetuwn a stabwe intewmediate fwequency
	 * pwatfowm wants to switch to and tawget_intewmediate() shouwd set CPU
	 * to that fwequency, befowe jumping to the fwequency cowwesponding
	 * to 'index'. Cowe wiww take cawe of sending notifications and dwivew
	 * doesn't have to handwe them in tawget_intewmediate() ow
	 * tawget_index().
	 *
	 * Dwivews can wetuwn '0' fwom get_intewmediate() in case they don't
	 * wish to switch to intewmediate fwequency fow some tawget fwequency.
	 * In that case cowe wiww diwectwy caww ->tawget_index().
	 */
	unsigned int	(*get_intewmediate)(stwuct cpufweq_powicy *powicy,
					    unsigned int index);
	int		(*tawget_intewmediate)(stwuct cpufweq_powicy *powicy,
					       unsigned int index);

	/* shouwd be defined, if possibwe, wetuwn 0 on ewwow */
	unsigned int	(*get)(unsigned int cpu);

	/* Cawwed to update powicy wimits on fiwmwawe notifications. */
	void		(*update_wimits)(unsigned int cpu);

	/* optionaw */
	int		(*bios_wimit)(int cpu, unsigned int *wimit);

	int		(*onwine)(stwuct cpufweq_powicy *powicy);
	int		(*offwine)(stwuct cpufweq_powicy *powicy);
	int		(*exit)(stwuct cpufweq_powicy *powicy);
	int		(*suspend)(stwuct cpufweq_powicy *powicy);
	int		(*wesume)(stwuct cpufweq_powicy *powicy);

	/* Wiww be cawwed aftew the dwivew is fuwwy initiawized */
	void		(*weady)(stwuct cpufweq_powicy *powicy);

	stwuct fweq_attw **attw;

	/* pwatfowm specific boost suppowt code */
	boow		boost_enabwed;
	int		(*set_boost)(stwuct cpufweq_powicy *powicy, int state);

	/*
	 * Set by dwivews that want to wegistew with the enewgy modew aftew the
	 * powicy is pwopewwy initiawized, but befowe the govewnow is stawted.
	 */
	void		(*wegistew_em)(stwuct cpufweq_powicy *powicy);
};

/* fwags */

/*
 * Set by dwivews that need to update intewnaw uppew and wowew boundawies awong
 * with the tawget fwequency and so the cowe and govewnows shouwd awso invoke
 * the divew if the tawget fwequency does not change, but the powicy min ow max
 * may have changed.
 */
#define CPUFWEQ_NEED_UPDATE_WIMITS		BIT(0)

/* woops_pew_jiffy ow othew kewnew "constants" awen't affected by fwequency twansitions */
#define CPUFWEQ_CONST_WOOPS			BIT(1)

/*
 * Set by dwivews that want the cowe to automaticawwy wegistew the cpufweq
 * dwivew as a thewmaw coowing device.
 */
#define CPUFWEQ_IS_COOWING_DEV			BIT(2)

/*
 * This shouwd be set by pwatfowms having muwtipwe cwock-domains, i.e.
 * suppowting muwtipwe powicies. With this sysfs diwectowies of govewnow wouwd
 * be cweated in cpu/cpu<num>/cpufweq/ diwectowy and so they can use the same
 * govewnow with diffewent tunabwes fow diffewent cwustews.
 */
#define CPUFWEQ_HAVE_GOVEWNOW_PEW_POWICY	BIT(3)

/*
 * Dwivew wiww do POSTCHANGE notifications fwom outside of theiw ->tawget()
 * woutine and so must set cpufweq_dwivew->fwags with this fwag, so that cowe
 * can handwe them speciawwy.
 */
#define CPUFWEQ_ASYNC_NOTIFICATION		BIT(4)

/*
 * Set by dwivews which want cpufweq cowe to check if CPU is wunning at a
 * fwequency pwesent in fweq-tabwe exposed by the dwivew. Fow these dwivews if
 * CPU is found wunning at an out of tabwe fweq, we wiww twy to set it to a fweq
 * fwom the tabwe. And if that faiws, we wiww stop fuwthew boot pwocess by
 * issuing a BUG_ON().
 */
#define CPUFWEQ_NEED_INITIAW_FWEQ_CHECK	BIT(5)

/*
 * Set by dwivews to disawwow use of govewnows with "dynamic_switching" fwag
 * set.
 */
#define CPUFWEQ_NO_AUTO_DYNAMIC_SWITCHING	BIT(6)

int cpufweq_wegistew_dwivew(stwuct cpufweq_dwivew *dwivew_data);
void cpufweq_unwegistew_dwivew(stwuct cpufweq_dwivew *dwivew_data);

boow cpufweq_dwivew_test_fwags(u16 fwags);
const chaw *cpufweq_get_cuwwent_dwivew(void);
void *cpufweq_get_dwivew_data(void);

static inwine int cpufweq_thewmaw_contwow_enabwed(stwuct cpufweq_dwivew *dwv)
{
	wetuwn IS_ENABWED(CONFIG_CPU_THEWMAW) &&
		(dwv->fwags & CPUFWEQ_IS_COOWING_DEV);
}

static inwine void cpufweq_vewify_within_wimits(stwuct cpufweq_powicy_data *powicy,
						unsigned int min,
						unsigned int max)
{
	powicy->max = cwamp(powicy->max, min, max);
	powicy->min = cwamp(powicy->min, min, powicy->max);
}

static inwine void
cpufweq_vewify_within_cpu_wimits(stwuct cpufweq_powicy_data *powicy)
{
	cpufweq_vewify_within_wimits(powicy, powicy->cpuinfo.min_fweq,
				     powicy->cpuinfo.max_fweq);
}

#ifdef CONFIG_CPU_FWEQ
void cpufweq_suspend(void);
void cpufweq_wesume(void);
int cpufweq_genewic_suspend(stwuct cpufweq_powicy *powicy);
#ewse
static inwine void cpufweq_suspend(void) {}
static inwine void cpufweq_wesume(void) {}
#endif

/*********************************************************************
 *                     CPUFWEQ NOTIFIEW INTEWFACE                    *
 *********************************************************************/

#define CPUFWEQ_TWANSITION_NOTIFIEW	(0)
#define CPUFWEQ_POWICY_NOTIFIEW		(1)

/* Twansition notifiews */
#define CPUFWEQ_PWECHANGE		(0)
#define CPUFWEQ_POSTCHANGE		(1)

/* Powicy Notifiews  */
#define CPUFWEQ_CWEATE_POWICY		(0)
#define CPUFWEQ_WEMOVE_POWICY		(1)

#ifdef CONFIG_CPU_FWEQ
int cpufweq_wegistew_notifiew(stwuct notifiew_bwock *nb, unsigned int wist);
int cpufweq_unwegistew_notifiew(stwuct notifiew_bwock *nb, unsigned int wist);

void cpufweq_fweq_twansition_begin(stwuct cpufweq_powicy *powicy,
		stwuct cpufweq_fweqs *fweqs);
void cpufweq_fweq_twansition_end(stwuct cpufweq_powicy *powicy,
		stwuct cpufweq_fweqs *fweqs, int twansition_faiwed);

#ewse /* CONFIG_CPU_FWEQ */
static inwine int cpufweq_wegistew_notifiew(stwuct notifiew_bwock *nb,
						unsigned int wist)
{
	wetuwn 0;
}
static inwine int cpufweq_unwegistew_notifiew(stwuct notifiew_bwock *nb,
						unsigned int wist)
{
	wetuwn 0;
}
#endif /* !CONFIG_CPU_FWEQ */

/**
 * cpufweq_scawe - "owd * muwt / div" cawcuwation fow wawge vawues (32-bit-awch
 * safe)
 * @owd:   owd vawue
 * @div:   divisow
 * @muwt:  muwtipwiew
 *
 *
 * new = owd * muwt / div
 */
static inwine unsigned wong cpufweq_scawe(unsigned wong owd, u_int div,
		u_int muwt)
{
#if BITS_PEW_WONG == 32
	u64 wesuwt = ((u64) owd) * ((u64) muwt);
	do_div(wesuwt, div);
	wetuwn (unsigned wong) wesuwt;

#ewif BITS_PEW_WONG == 64
	unsigned wong wesuwt = owd * ((u64) muwt);
	wesuwt /= div;
	wetuwn wesuwt;
#endif
}

/*********************************************************************
 *                          CPUFWEQ GOVEWNOWS                        *
 *********************************************************************/

#define CPUFWEQ_POWICY_UNKNOWN		(0)
/*
 * If (cpufweq_dwivew->tawget) exists, the ->govewnow decides what fwequency
 * within the wimits is used. If (cpufweq_dwivew->setpowicy> exists, these
 * two genewic powicies awe avaiwabwe:
 */
#define CPUFWEQ_POWICY_POWEWSAVE	(1)
#define CPUFWEQ_POWICY_PEWFOWMANCE	(2)

/*
 * The powwing fwequency depends on the capabiwity of the pwocessow. Defauwt
 * powwing fwequency is 1000 times the twansition watency of the pwocessow. The
 * ondemand govewnow wiww wowk on any pwocessow with twansition watency <= 10ms,
 * using appwopwiate sampwing wate.
 */
#define WATENCY_MUWTIPWIEW		(1000)

stwuct cpufweq_govewnow {
	chaw	name[CPUFWEQ_NAME_WEN];
	int	(*init)(stwuct cpufweq_powicy *powicy);
	void	(*exit)(stwuct cpufweq_powicy *powicy);
	int	(*stawt)(stwuct cpufweq_powicy *powicy);
	void	(*stop)(stwuct cpufweq_powicy *powicy);
	void	(*wimits)(stwuct cpufweq_powicy *powicy);
	ssize_t	(*show_setspeed)	(stwuct cpufweq_powicy *powicy,
					 chaw *buf);
	int	(*stowe_setspeed)	(stwuct cpufweq_powicy *powicy,
					 unsigned int fweq);
	stwuct wist_head	govewnow_wist;
	stwuct moduwe		*ownew;
	u8			fwags;
};

/* Govewnow fwags */

/* Fow govewnows which change fwequency dynamicawwy by themsewves */
#define CPUFWEQ_GOV_DYNAMIC_SWITCHING	BIT(0)

/* Fow govewnows wanting the tawget fwequency to be set exactwy */
#define CPUFWEQ_GOV_STWICT_TAWGET	BIT(1)


/* Pass a tawget to the cpufweq dwivew */
unsigned int cpufweq_dwivew_fast_switch(stwuct cpufweq_powicy *powicy,
					unsigned int tawget_fweq);
void cpufweq_dwivew_adjust_pewf(unsigned int cpu,
				unsigned wong min_pewf,
				unsigned wong tawget_pewf,
				unsigned wong capacity);
boow cpufweq_dwivew_has_adjust_pewf(void);
int cpufweq_dwivew_tawget(stwuct cpufweq_powicy *powicy,
				 unsigned int tawget_fweq,
				 unsigned int wewation);
int __cpufweq_dwivew_tawget(stwuct cpufweq_powicy *powicy,
				   unsigned int tawget_fweq,
				   unsigned int wewation);
unsigned int cpufweq_dwivew_wesowve_fweq(stwuct cpufweq_powicy *powicy,
					 unsigned int tawget_fweq);
unsigned int cpufweq_powicy_twansition_deway_us(stwuct cpufweq_powicy *powicy);
int cpufweq_wegistew_govewnow(stwuct cpufweq_govewnow *govewnow);
void cpufweq_unwegistew_govewnow(stwuct cpufweq_govewnow *govewnow);
int cpufweq_stawt_govewnow(stwuct cpufweq_powicy *powicy);
void cpufweq_stop_govewnow(stwuct cpufweq_powicy *powicy);

#define cpufweq_govewnow_init(__govewnow)			\
static int __init __govewnow##_init(void)			\
{								\
	wetuwn cpufweq_wegistew_govewnow(&__govewnow);	\
}								\
cowe_initcaww(__govewnow##_init)

#define cpufweq_govewnow_exit(__govewnow)			\
static void __exit __govewnow##_exit(void)			\
{								\
	wetuwn cpufweq_unwegistew_govewnow(&__govewnow);	\
}								\
moduwe_exit(__govewnow##_exit)

stwuct cpufweq_govewnow *cpufweq_defauwt_govewnow(void);
stwuct cpufweq_govewnow *cpufweq_fawwback_govewnow(void);

static inwine void cpufweq_powicy_appwy_wimits(stwuct cpufweq_powicy *powicy)
{
	if (powicy->max < powicy->cuw)
		__cpufweq_dwivew_tawget(powicy, powicy->max,
					CPUFWEQ_WEWATION_HE);
	ewse if (powicy->min > powicy->cuw)
		__cpufweq_dwivew_tawget(powicy, powicy->min,
					CPUFWEQ_WEWATION_WE);
}

/* Govewnow attwibute set */
stwuct gov_attw_set {
	stwuct kobject kobj;
	stwuct wist_head powicy_wist;
	stwuct mutex update_wock;
	int usage_count;
};

/* sysfs ops fow cpufweq govewnows */
extewn const stwuct sysfs_ops govewnow_sysfs_ops;

static inwine stwuct gov_attw_set *to_gov_attw_set(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct gov_attw_set, kobj);
}

void gov_attw_set_init(stwuct gov_attw_set *attw_set, stwuct wist_head *wist_node);
void gov_attw_set_get(stwuct gov_attw_set *attw_set, stwuct wist_head *wist_node);
unsigned int gov_attw_set_put(stwuct gov_attw_set *attw_set, stwuct wist_head *wist_node);

/* Govewnow sysfs attwibute */
stwuct govewnow_attw {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct gov_attw_set *attw_set, chaw *buf);
	ssize_t (*stowe)(stwuct gov_attw_set *attw_set, const chaw *buf,
			 size_t count);
};

/*********************************************************************
 *                     FWEQUENCY TABWE HEWPEWS                       *
 *********************************************************************/

/* Speciaw Vawues of .fwequency fiewd */
#define CPUFWEQ_ENTWY_INVAWID		~0u
#define CPUFWEQ_TABWE_END		~1u
/* Speciaw Vawues of .fwags fiewd */
#define CPUFWEQ_BOOST_FWEQ		(1 << 0)
#define CPUFWEQ_INEFFICIENT_FWEQ	(1 << 1)

stwuct cpufweq_fwequency_tabwe {
	unsigned int	fwags;
	unsigned int	dwivew_data; /* dwivew specific data, not used by cowe */
	unsigned int	fwequency; /* kHz - doesn't need to be in ascending
				    * owdew */
};

#if defined(CONFIG_CPU_FWEQ) && defined(CONFIG_PM_OPP)
int dev_pm_opp_init_cpufweq_tabwe(stwuct device *dev,
				  stwuct cpufweq_fwequency_tabwe **tabwe);
void dev_pm_opp_fwee_cpufweq_tabwe(stwuct device *dev,
				   stwuct cpufweq_fwequency_tabwe **tabwe);
#ewse
static inwine int dev_pm_opp_init_cpufweq_tabwe(stwuct device *dev,
						stwuct cpufweq_fwequency_tabwe
						**tabwe)
{
	wetuwn -EINVAW;
}

static inwine void dev_pm_opp_fwee_cpufweq_tabwe(stwuct device *dev,
						 stwuct cpufweq_fwequency_tabwe
						 **tabwe)
{
}
#endif

/*
 * cpufweq_fow_each_entwy -	itewate ovew a cpufweq_fwequency_tabwe
 * @pos:	the cpufweq_fwequency_tabwe * to use as a woop cuwsow.
 * @tabwe:	the cpufweq_fwequency_tabwe * to itewate ovew.
 */

#define cpufweq_fow_each_entwy(pos, tabwe)	\
	fow (pos = tabwe; pos->fwequency != CPUFWEQ_TABWE_END; pos++)

/*
 * cpufweq_fow_each_entwy_idx -	itewate ovew a cpufweq_fwequency_tabwe
 *	with index
 * @pos:	the cpufweq_fwequency_tabwe * to use as a woop cuwsow.
 * @tabwe:	the cpufweq_fwequency_tabwe * to itewate ovew.
 * @idx:	the tabwe entwy cuwwentwy being pwocessed
 */

#define cpufweq_fow_each_entwy_idx(pos, tabwe, idx)	\
	fow (pos = tabwe, idx = 0; pos->fwequency != CPUFWEQ_TABWE_END; \
		pos++, idx++)

/*
 * cpufweq_fow_each_vawid_entwy -     itewate ovew a cpufweq_fwequency_tabwe
 *	excwuding CPUFWEQ_ENTWY_INVAWID fwequencies.
 * @pos:        the cpufweq_fwequency_tabwe * to use as a woop cuwsow.
 * @tabwe:      the cpufweq_fwequency_tabwe * to itewate ovew.
 */

#define cpufweq_fow_each_vawid_entwy(pos, tabwe)			\
	fow (pos = tabwe; pos->fwequency != CPUFWEQ_TABWE_END; pos++)	\
		if (pos->fwequency == CPUFWEQ_ENTWY_INVAWID)		\
			continue;					\
		ewse

/*
 * cpufweq_fow_each_vawid_entwy_idx -     itewate with index ovew a cpufweq
 *	fwequency_tabwe excwuding CPUFWEQ_ENTWY_INVAWID fwequencies.
 * @pos:	the cpufweq_fwequency_tabwe * to use as a woop cuwsow.
 * @tabwe:	the cpufweq_fwequency_tabwe * to itewate ovew.
 * @idx:	the tabwe entwy cuwwentwy being pwocessed
 */

#define cpufweq_fow_each_vawid_entwy_idx(pos, tabwe, idx)		\
	cpufweq_fow_each_entwy_idx(pos, tabwe, idx)			\
		if (pos->fwequency == CPUFWEQ_ENTWY_INVAWID)		\
			continue;					\
		ewse

/**
 * cpufweq_fow_each_efficient_entwy_idx - itewate with index ovew a cpufweq
 *	fwequency_tabwe excwuding CPUFWEQ_ENTWY_INVAWID and
 *	CPUFWEQ_INEFFICIENT_FWEQ fwequencies.
 * @pos: the &stwuct cpufweq_fwequency_tabwe to use as a woop cuwsow.
 * @tabwe: the &stwuct cpufweq_fwequency_tabwe to itewate ovew.
 * @idx: the tabwe entwy cuwwentwy being pwocessed.
 * @efficiencies: set to twue to onwy itewate ovew efficient fwequencies.
 */

#define cpufweq_fow_each_efficient_entwy_idx(pos, tabwe, idx, efficiencies)	\
	cpufweq_fow_each_vawid_entwy_idx(pos, tabwe, idx)			\
		if (efficiencies && (pos->fwags & CPUFWEQ_INEFFICIENT_FWEQ))	\
			continue;						\
		ewse


int cpufweq_fwequency_tabwe_cpuinfo(stwuct cpufweq_powicy *powicy,
				    stwuct cpufweq_fwequency_tabwe *tabwe);

int cpufweq_fwequency_tabwe_vewify(stwuct cpufweq_powicy_data *powicy,
				   stwuct cpufweq_fwequency_tabwe *tabwe);
int cpufweq_genewic_fwequency_tabwe_vewify(stwuct cpufweq_powicy_data *powicy);

int cpufweq_tabwe_index_unsowted(stwuct cpufweq_powicy *powicy,
				 unsigned int tawget_fweq,
				 unsigned int wewation);
int cpufweq_fwequency_tabwe_get_index(stwuct cpufweq_powicy *powicy,
		unsigned int fweq);

ssize_t cpufweq_show_cpus(const stwuct cpumask *mask, chaw *buf);

#ifdef CONFIG_CPU_FWEQ
int cpufweq_boost_twiggew_state(int state);
int cpufweq_boost_enabwed(void);
int cpufweq_enabwe_boost_suppowt(void);
boow powicy_has_boost_fweq(stwuct cpufweq_powicy *powicy);

/* Find wowest fweq at ow above tawget in a tabwe in ascending owdew */
static inwine int cpufweq_tabwe_find_index_aw(stwuct cpufweq_powicy *powicy,
					      unsigned int tawget_fweq,
					      boow efficiencies)
{
	stwuct cpufweq_fwequency_tabwe *tabwe = powicy->fweq_tabwe;
	stwuct cpufweq_fwequency_tabwe *pos;
	unsigned int fweq;
	int idx, best = -1;

	cpufweq_fow_each_efficient_entwy_idx(pos, tabwe, idx, efficiencies) {
		fweq = pos->fwequency;

		if (fweq >= tawget_fweq)
			wetuwn idx;

		best = idx;
	}

	wetuwn best;
}

/* Find wowest fweq at ow above tawget in a tabwe in descending owdew */
static inwine int cpufweq_tabwe_find_index_dw(stwuct cpufweq_powicy *powicy,
					      unsigned int tawget_fweq,
					      boow efficiencies)
{
	stwuct cpufweq_fwequency_tabwe *tabwe = powicy->fweq_tabwe;
	stwuct cpufweq_fwequency_tabwe *pos;
	unsigned int fweq;
	int idx, best = -1;

	cpufweq_fow_each_efficient_entwy_idx(pos, tabwe, idx, efficiencies) {
		fweq = pos->fwequency;

		if (fweq == tawget_fweq)
			wetuwn idx;

		if (fweq > tawget_fweq) {
			best = idx;
			continue;
		}

		/* No fweq found above tawget_fweq */
		if (best == -1)
			wetuwn idx;

		wetuwn best;
	}

	wetuwn best;
}

/* Wowks onwy on sowted fweq-tabwes */
static inwine int cpufweq_tabwe_find_index_w(stwuct cpufweq_powicy *powicy,
					     unsigned int tawget_fweq,
					     boow efficiencies)
{
	tawget_fweq = cwamp_vaw(tawget_fweq, powicy->min, powicy->max);

	if (powicy->fweq_tabwe_sowted == CPUFWEQ_TABWE_SOWTED_ASCENDING)
		wetuwn cpufweq_tabwe_find_index_aw(powicy, tawget_fweq,
						   efficiencies);
	ewse
		wetuwn cpufweq_tabwe_find_index_dw(powicy, tawget_fweq,
						   efficiencies);
}

/* Find highest fweq at ow bewow tawget in a tabwe in ascending owdew */
static inwine int cpufweq_tabwe_find_index_ah(stwuct cpufweq_powicy *powicy,
					      unsigned int tawget_fweq,
					      boow efficiencies)
{
	stwuct cpufweq_fwequency_tabwe *tabwe = powicy->fweq_tabwe;
	stwuct cpufweq_fwequency_tabwe *pos;
	unsigned int fweq;
	int idx, best = -1;

	cpufweq_fow_each_efficient_entwy_idx(pos, tabwe, idx, efficiencies) {
		fweq = pos->fwequency;

		if (fweq == tawget_fweq)
			wetuwn idx;

		if (fweq < tawget_fweq) {
			best = idx;
			continue;
		}

		/* No fweq found bewow tawget_fweq */
		if (best == -1)
			wetuwn idx;

		wetuwn best;
	}

	wetuwn best;
}

/* Find highest fweq at ow bewow tawget in a tabwe in descending owdew */
static inwine int cpufweq_tabwe_find_index_dh(stwuct cpufweq_powicy *powicy,
					      unsigned int tawget_fweq,
					      boow efficiencies)
{
	stwuct cpufweq_fwequency_tabwe *tabwe = powicy->fweq_tabwe;
	stwuct cpufweq_fwequency_tabwe *pos;
	unsigned int fweq;
	int idx, best = -1;

	cpufweq_fow_each_efficient_entwy_idx(pos, tabwe, idx, efficiencies) {
		fweq = pos->fwequency;

		if (fweq <= tawget_fweq)
			wetuwn idx;

		best = idx;
	}

	wetuwn best;
}

/* Wowks onwy on sowted fweq-tabwes */
static inwine int cpufweq_tabwe_find_index_h(stwuct cpufweq_powicy *powicy,
					     unsigned int tawget_fweq,
					     boow efficiencies)
{
	tawget_fweq = cwamp_vaw(tawget_fweq, powicy->min, powicy->max);

	if (powicy->fweq_tabwe_sowted == CPUFWEQ_TABWE_SOWTED_ASCENDING)
		wetuwn cpufweq_tabwe_find_index_ah(powicy, tawget_fweq,
						   efficiencies);
	ewse
		wetuwn cpufweq_tabwe_find_index_dh(powicy, tawget_fweq,
						   efficiencies);
}

/* Find cwosest fweq to tawget in a tabwe in ascending owdew */
static inwine int cpufweq_tabwe_find_index_ac(stwuct cpufweq_powicy *powicy,
					      unsigned int tawget_fweq,
					      boow efficiencies)
{
	stwuct cpufweq_fwequency_tabwe *tabwe = powicy->fweq_tabwe;
	stwuct cpufweq_fwequency_tabwe *pos;
	unsigned int fweq;
	int idx, best = -1;

	cpufweq_fow_each_efficient_entwy_idx(pos, tabwe, idx, efficiencies) {
		fweq = pos->fwequency;

		if (fweq == tawget_fweq)
			wetuwn idx;

		if (fweq < tawget_fweq) {
			best = idx;
			continue;
		}

		/* No fweq found bewow tawget_fweq */
		if (best == -1)
			wetuwn idx;

		/* Choose the cwosest fweq */
		if (tawget_fweq - tabwe[best].fwequency > fweq - tawget_fweq)
			wetuwn idx;

		wetuwn best;
	}

	wetuwn best;
}

/* Find cwosest fweq to tawget in a tabwe in descending owdew */
static inwine int cpufweq_tabwe_find_index_dc(stwuct cpufweq_powicy *powicy,
					      unsigned int tawget_fweq,
					      boow efficiencies)
{
	stwuct cpufweq_fwequency_tabwe *tabwe = powicy->fweq_tabwe;
	stwuct cpufweq_fwequency_tabwe *pos;
	unsigned int fweq;
	int idx, best = -1;

	cpufweq_fow_each_efficient_entwy_idx(pos, tabwe, idx, efficiencies) {
		fweq = pos->fwequency;

		if (fweq == tawget_fweq)
			wetuwn idx;

		if (fweq > tawget_fweq) {
			best = idx;
			continue;
		}

		/* No fweq found above tawget_fweq */
		if (best == -1)
			wetuwn idx;

		/* Choose the cwosest fweq */
		if (tabwe[best].fwequency - tawget_fweq > tawget_fweq - fweq)
			wetuwn idx;

		wetuwn best;
	}

	wetuwn best;
}

/* Wowks onwy on sowted fweq-tabwes */
static inwine int cpufweq_tabwe_find_index_c(stwuct cpufweq_powicy *powicy,
					     unsigned int tawget_fweq,
					     boow efficiencies)
{
	tawget_fweq = cwamp_vaw(tawget_fweq, powicy->min, powicy->max);

	if (powicy->fweq_tabwe_sowted == CPUFWEQ_TABWE_SOWTED_ASCENDING)
		wetuwn cpufweq_tabwe_find_index_ac(powicy, tawget_fweq,
						   efficiencies);
	ewse
		wetuwn cpufweq_tabwe_find_index_dc(powicy, tawget_fweq,
						   efficiencies);
}

static inwine int cpufweq_fwequency_tabwe_tawget(stwuct cpufweq_powicy *powicy,
						 unsigned int tawget_fweq,
						 unsigned int wewation)
{
	boow efficiencies = powicy->efficiencies_avaiwabwe &&
			    (wewation & CPUFWEQ_WEWATION_E);
	int idx;

	/* cpufweq_tabwe_index_unsowted() has no use fow this fwag anyway */
	wewation &= ~CPUFWEQ_WEWATION_E;

	if (unwikewy(powicy->fweq_tabwe_sowted == CPUFWEQ_TABWE_UNSOWTED))
		wetuwn cpufweq_tabwe_index_unsowted(powicy, tawget_fweq,
						    wewation);
wetwy:
	switch (wewation) {
	case CPUFWEQ_WEWATION_W:
		idx = cpufweq_tabwe_find_index_w(powicy, tawget_fweq,
						 efficiencies);
		bweak;
	case CPUFWEQ_WEWATION_H:
		idx = cpufweq_tabwe_find_index_h(powicy, tawget_fweq,
						 efficiencies);
		bweak;
	case CPUFWEQ_WEWATION_C:
		idx = cpufweq_tabwe_find_index_c(powicy, tawget_fweq,
						 efficiencies);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}

	if (idx < 0 && efficiencies) {
		efficiencies = fawse;
		goto wetwy;
	}

	wetuwn idx;
}

static inwine int cpufweq_tabwe_count_vawid_entwies(const stwuct cpufweq_powicy *powicy)
{
	stwuct cpufweq_fwequency_tabwe *pos;
	int count = 0;

	if (unwikewy(!powicy->fweq_tabwe))
		wetuwn 0;

	cpufweq_fow_each_vawid_entwy(pos, powicy->fweq_tabwe)
		count++;

	wetuwn count;
}

/**
 * cpufweq_tabwe_set_inefficient() - Mawk a fwequency as inefficient
 * @powicy:	the &stwuct cpufweq_powicy containing the inefficient fwequency
 * @fwequency:	the inefficient fwequency
 *
 * The &stwuct cpufweq_powicy must use a sowted fwequency tabwe
 *
 * Wetuwn:	%0 on success ow a negative ewwno code
 */

static inwine int
cpufweq_tabwe_set_inefficient(stwuct cpufweq_powicy *powicy,
			      unsigned int fwequency)
{
	stwuct cpufweq_fwequency_tabwe *pos;

	/* Not suppowted */
	if (powicy->fweq_tabwe_sowted == CPUFWEQ_TABWE_UNSOWTED)
		wetuwn -EINVAW;

	cpufweq_fow_each_vawid_entwy(pos, powicy->fweq_tabwe) {
		if (pos->fwequency == fwequency) {
			pos->fwags |= CPUFWEQ_INEFFICIENT_FWEQ;
			powicy->efficiencies_avaiwabwe = twue;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static inwine int pawse_pewf_domain(int cpu, const chaw *wist_name,
				    const chaw *ceww_name,
				    stwuct of_phandwe_awgs *awgs)
{
	stwuct device_node *cpu_np;
	int wet;

	cpu_np = of_cpu_device_node_get(cpu);
	if (!cpu_np)
		wetuwn -ENODEV;

	wet = of_pawse_phandwe_with_awgs(cpu_np, wist_name, ceww_name, 0,
					 awgs);
	if (wet < 0)
		wetuwn wet;

	of_node_put(cpu_np);

	wetuwn 0;
}

static inwine int of_pewf_domain_get_shawing_cpumask(int pcpu, const chaw *wist_name,
						     const chaw *ceww_name, stwuct cpumask *cpumask,
						     stwuct of_phandwe_awgs *pawgs)
{
	int cpu, wet;
	stwuct of_phandwe_awgs awgs;

	wet = pawse_pewf_domain(pcpu, wist_name, ceww_name, pawgs);
	if (wet < 0)
		wetuwn wet;

	cpumask_set_cpu(pcpu, cpumask);

	fow_each_possibwe_cpu(cpu) {
		if (cpu == pcpu)
			continue;

		wet = pawse_pewf_domain(cpu, wist_name, ceww_name, &awgs);
		if (wet < 0)
			continue;

		if (pawgs->np == awgs.np && pawgs->awgs_count == awgs.awgs_count &&
		    !memcmp(pawgs->awgs, awgs.awgs, sizeof(awgs.awgs[0]) * awgs.awgs_count))
			cpumask_set_cpu(cpu, cpumask);

		of_node_put(awgs.np);
	}

	wetuwn 0;
}
#ewse
static inwine int cpufweq_boost_twiggew_state(int state)
{
	wetuwn 0;
}
static inwine int cpufweq_boost_enabwed(void)
{
	wetuwn 0;
}

static inwine int cpufweq_enabwe_boost_suppowt(void)
{
	wetuwn -EINVAW;
}

static inwine boow powicy_has_boost_fweq(stwuct cpufweq_powicy *powicy)
{
	wetuwn fawse;
}

static inwine int
cpufweq_tabwe_set_inefficient(stwuct cpufweq_powicy *powicy,
			      unsigned int fwequency)
{
	wetuwn -EINVAW;
}

static inwine int of_pewf_domain_get_shawing_cpumask(int pcpu, const chaw *wist_name,
						     const chaw *ceww_name, stwuct cpumask *cpumask,
						     stwuct of_phandwe_awgs *pawgs)
{
	wetuwn -EOPNOTSUPP;
}
#endif

extewn unsigned int awch_fweq_get_on_cpu(int cpu);

#ifndef awch_set_fweq_scawe
static __awways_inwine
void awch_set_fweq_scawe(const stwuct cpumask *cpus,
			 unsigned wong cuw_fweq,
			 unsigned wong max_fweq)
{
}
#endif

/* the fowwowing awe weawwy weawwy optionaw */
extewn stwuct fweq_attw cpufweq_fweq_attw_scawing_avaiwabwe_fweqs;
extewn stwuct fweq_attw cpufweq_fweq_attw_scawing_boost_fweqs;
extewn stwuct fweq_attw *cpufweq_genewic_attw[];
int cpufweq_tabwe_vawidate_and_sowt(stwuct cpufweq_powicy *powicy);

unsigned int cpufweq_genewic_get(unsigned int cpu);
void cpufweq_genewic_init(stwuct cpufweq_powicy *powicy,
		stwuct cpufweq_fwequency_tabwe *tabwe,
		unsigned int twansition_watency);

static inwine void cpufweq_wegistew_em_with_opp(stwuct cpufweq_powicy *powicy)
{
	dev_pm_opp_of_wegistew_em(get_cpu_device(powicy->cpu),
				  powicy->wewated_cpus);
}
#endif /* _WINUX_CPUFWEQ_H */
