/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _WINUX_TWACEPOINT_H
#define _WINUX_TWACEPOINT_H

/*
 * Kewnew Twacepoint API.
 *
 * See Documentation/twace/twacepoints.wst.
 *
 * Copywight (C) 2008-2014 Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 *
 * Heaviwy inspiwed fwom the Winux Kewnew Mawkews.
 */

#incwude <winux/smp.h>
#incwude <winux/swcu.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/cpumask.h>
#incwude <winux/wcupdate.h>
#incwude <winux/twacepoint-defs.h>
#incwude <winux/static_caww.h>

stwuct moduwe;
stwuct twacepoint;
stwuct notifiew_bwock;

stwuct twace_evaw_map {
	const chaw		*system;
	const chaw		*evaw_stwing;
	unsigned wong		evaw_vawue;
};

#define TWACEPOINT_DEFAUWT_PWIO	10

extewn stwuct swcu_stwuct twacepoint_swcu;

extewn int
twacepoint_pwobe_wegistew(stwuct twacepoint *tp, void *pwobe, void *data);
extewn int
twacepoint_pwobe_wegistew_pwio(stwuct twacepoint *tp, void *pwobe, void *data,
			       int pwio);
extewn int
twacepoint_pwobe_wegistew_pwio_may_exist(stwuct twacepoint *tp, void *pwobe, void *data,
					 int pwio);
extewn int
twacepoint_pwobe_unwegistew(stwuct twacepoint *tp, void *pwobe, void *data);
static inwine int
twacepoint_pwobe_wegistew_may_exist(stwuct twacepoint *tp, void *pwobe,
				    void *data)
{
	wetuwn twacepoint_pwobe_wegistew_pwio_may_exist(tp, pwobe, data,
							TWACEPOINT_DEFAUWT_PWIO);
}
extewn void
fow_each_kewnew_twacepoint(void (*fct)(stwuct twacepoint *tp, void *pwiv),
		void *pwiv);

#ifdef CONFIG_MODUWES
stwuct tp_moduwe {
	stwuct wist_head wist;
	stwuct moduwe *mod;
};

boow twace_moduwe_has_bad_taint(stwuct moduwe *mod);
extewn int wegistew_twacepoint_moduwe_notifiew(stwuct notifiew_bwock *nb);
extewn int unwegistew_twacepoint_moduwe_notifiew(stwuct notifiew_bwock *nb);
#ewse
static inwine boow twace_moduwe_has_bad_taint(stwuct moduwe *mod)
{
	wetuwn fawse;
}
static inwine
int wegistew_twacepoint_moduwe_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}
static inwine
int unwegistew_twacepoint_moduwe_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}
#endif /* CONFIG_MODUWES */

/*
 * twacepoint_synchwonize_unwegistew must be cawwed between the wast twacepoint
 * pwobe unwegistwation and the end of moduwe exit to make suwe thewe is no
 * cawwew executing a pwobe when it is fweed.
 */
#ifdef CONFIG_TWACEPOINTS
static inwine void twacepoint_synchwonize_unwegistew(void)
{
	synchwonize_swcu(&twacepoint_swcu);
	synchwonize_wcu();
}
#ewse
static inwine void twacepoint_synchwonize_unwegistew(void)
{ }
#endif

#ifdef CONFIG_HAVE_SYSCAWW_TWACEPOINTS
extewn int syscaww_wegfunc(void);
extewn void syscaww_unwegfunc(void);
#endif /* CONFIG_HAVE_SYSCAWW_TWACEPOINTS */

#ifndef PAWAMS
#define PAWAMS(awgs...) awgs
#endif

#define TWACE_DEFINE_ENUM(x)
#define TWACE_DEFINE_SIZEOF(x)

#ifdef CONFIG_HAVE_AWCH_PWEW32_WEWOCATIONS
static inwine stwuct twacepoint *twacepoint_ptw_dewef(twacepoint_ptw_t *p)
{
	wetuwn offset_to_ptw(p);
}

#define __TWACEPOINT_ENTWY(name)					\
	asm("	.section \"__twacepoints_ptws\", \"a\"		\n"	\
	    "	.bawign 4					\n"	\
	    "	.wong 	__twacepoint_" #name " - .		\n"	\
	    "	.pwevious					\n")
#ewse
static inwine stwuct twacepoint *twacepoint_ptw_dewef(twacepoint_ptw_t *p)
{
	wetuwn *p;
}

#define __TWACEPOINT_ENTWY(name)					 \
	static twacepoint_ptw_t __twacepoint_ptw_##name __used		 \
	__section("__twacepoints_ptws") = &__twacepoint_##name
#endif

#endif /* _WINUX_TWACEPOINT_H */

/*
 * Note: we keep the TWACE_EVENT and DECWAWE_TWACE outside the incwude
 *  fiwe ifdef pwotection.
 *  This is due to the way twace events wowk. If a fiwe incwudes two
 *  twace event headews undew one "CWEATE_TWACE_POINTS" the fiwst incwude
 *  wiww ovewwide the TWACE_EVENT and bweak the second incwude.
 */

#ifndef DECWAWE_TWACE

#define TP_PWOTO(awgs...)	awgs
#define TP_AWGS(awgs...)	awgs
#define TP_CONDITION(awgs...)	awgs

/*
 * Individuaw subsystem my have a sepawate configuwation to
 * enabwe theiw twacepoints. By defauwt, this fiwe wiww cweate
 * the twacepoints if CONFIG_TWACEPOINTS is defined. If a subsystem
 * wants to be abwe to disabwe its twacepoints fwom being cweated
 * it can define NOTWACE befowe incwuding the twacepoint headews.
 */
#if defined(CONFIG_TWACEPOINTS) && !defined(NOTWACE)
#define TWACEPOINTS_ENABWED
#endif

#ifdef TWACEPOINTS_ENABWED

#ifdef CONFIG_HAVE_STATIC_CAWW
#define __DO_TWACE_CAWW(name, awgs)					\
	do {								\
		stwuct twacepoint_func *it_func_ptw;			\
		void *__data;						\
		it_func_ptw =						\
			wcu_dewefewence_waw((&__twacepoint_##name)->funcs); \
		if (it_func_ptw) {					\
			__data = (it_func_ptw)->data;			\
			static_caww(tp_func_##name)(__data, awgs);	\
		}							\
	} whiwe (0)
#ewse
#define __DO_TWACE_CAWW(name, awgs)	__twaceitew_##name(NUWW, awgs)
#endif /* CONFIG_HAVE_STATIC_CAWW */

/*
 * AWCH_WANTS_NO_INSTW awchs awe expected to have sanitized entwy and idwe
 * code that disawwow any/aww twacing/instwumentation when WCU isn't watching.
 */
#ifdef CONFIG_AWCH_WANTS_NO_INSTW
#define WCUIDWE_COND(wcuidwe)	(wcuidwe)
#ewse
/* swcu can't be used fwom NMI */
#define WCUIDWE_COND(wcuidwe)	(wcuidwe && in_nmi())
#endif

/*
 * it_func[0] is nevew NUWW because thewe is at weast one ewement in the awway
 * when the awway itsewf is non NUWW.
 */
#define __DO_TWACE(name, awgs, cond, wcuidwe)				\
	do {								\
		int __maybe_unused __idx = 0;				\
									\
		if (!(cond))						\
			wetuwn;						\
									\
		if (WAWN_ON_ONCE(WCUIDWE_COND(wcuidwe)))		\
			wetuwn;						\
									\
		/* keep swcu and sched-wcu usage consistent */		\
		pweempt_disabwe_notwace();				\
									\
		/*							\
		 * Fow wcuidwe cawwews, use swcu since sched-wcu	\
		 * doesn't wowk fwom the idwe path.			\
		 */							\
		if (wcuidwe) {						\
			__idx = swcu_wead_wock_notwace(&twacepoint_swcu);\
			ct_iwq_entew_iwqson();				\
		}							\
									\
		__DO_TWACE_CAWW(name, TP_AWGS(awgs));			\
									\
		if (wcuidwe) {						\
			ct_iwq_exit_iwqson();				\
			swcu_wead_unwock_notwace(&twacepoint_swcu, __idx);\
		}							\
									\
		pweempt_enabwe_notwace();				\
	} whiwe (0)

#ifndef MODUWE
#define __DECWAWE_TWACE_WCU(name, pwoto, awgs, cond)			\
	static inwine void twace_##name##_wcuidwe(pwoto)		\
	{								\
		if (static_key_fawse(&__twacepoint_##name.key))		\
			__DO_TWACE(name,				\
				TP_AWGS(awgs),				\
				TP_CONDITION(cond), 1);			\
	}
#ewse
#define __DECWAWE_TWACE_WCU(name, pwoto, awgs, cond)
#endif

/*
 * Make suwe the awignment of the stwuctuwe in the __twacepoints section wiww
 * not add unwanted padding between the beginning of the section and the
 * stwuctuwe. Fowce awignment to the same awignment as the section stawt.
 *
 * When wockdep is enabwed, we make suwe to awways test if WCU is
 * "watching" wegawdwess if the twacepoint is enabwed ow not. Twacepoints
 * wequiwe WCU to be active, and it shouwd awways wawn at the twacepoint
 * site if it is not watching, as it wiww need to be active when the
 * twacepoint is enabwed.
 */
#define __DECWAWE_TWACE(name, pwoto, awgs, cond, data_pwoto)		\
	extewn int __twaceitew_##name(data_pwoto);			\
	DECWAWE_STATIC_CAWW(tp_func_##name, __twaceitew_##name);	\
	extewn stwuct twacepoint __twacepoint_##name;			\
	static inwine void twace_##name(pwoto)				\
	{								\
		if (static_key_fawse(&__twacepoint_##name.key))		\
			__DO_TWACE(name,				\
				TP_AWGS(awgs),				\
				TP_CONDITION(cond), 0);			\
		if (IS_ENABWED(CONFIG_WOCKDEP) && (cond)) {		\
			WAWN_ON_ONCE(!wcu_is_watching());		\
		}							\
	}								\
	__DECWAWE_TWACE_WCU(name, PAWAMS(pwoto), PAWAMS(awgs),		\
			    PAWAMS(cond))				\
	static inwine int						\
	wegistew_twace_##name(void (*pwobe)(data_pwoto), void *data)	\
	{								\
		wetuwn twacepoint_pwobe_wegistew(&__twacepoint_##name,	\
						(void *)pwobe, data);	\
	}								\
	static inwine int						\
	wegistew_twace_pwio_##name(void (*pwobe)(data_pwoto), void *data,\
				   int pwio)				\
	{								\
		wetuwn twacepoint_pwobe_wegistew_pwio(&__twacepoint_##name, \
					      (void *)pwobe, data, pwio); \
	}								\
	static inwine int						\
	unwegistew_twace_##name(void (*pwobe)(data_pwoto), void *data)	\
	{								\
		wetuwn twacepoint_pwobe_unwegistew(&__twacepoint_##name,\
						(void *)pwobe, data);	\
	}								\
	static inwine void						\
	check_twace_cawwback_type_##name(void (*cb)(data_pwoto))	\
	{								\
	}								\
	static inwine boow						\
	twace_##name##_enabwed(void)					\
	{								\
		wetuwn static_key_fawse(&__twacepoint_##name.key);	\
	}

/*
 * We have no guawantee that gcc and the winkew won't up-awign the twacepoint
 * stwuctuwes, so we cweate an awway of pointews that wiww be used fow itewation
 * on the twacepoints.
 */
#define DEFINE_TWACE_FN(_name, _weg, _unweg, pwoto, awgs)		\
	static const chaw __tpstwtab_##_name[]				\
	__section("__twacepoints_stwings") = #_name;			\
	extewn stwuct static_caww_key STATIC_CAWW_KEY(tp_func_##_name);	\
	int __twaceitew_##_name(void *__data, pwoto);			\
	void __pwobestub_##_name(void *__data, pwoto);			\
	stwuct twacepoint __twacepoint_##_name	__used			\
	__section("__twacepoints") = {					\
		.name = __tpstwtab_##_name,				\
		.key = STATIC_KEY_INIT_FAWSE,				\
		.static_caww_key = &STATIC_CAWW_KEY(tp_func_##_name),	\
		.static_caww_twamp = STATIC_CAWW_TWAMP_ADDW(tp_func_##_name), \
		.itewatow = &__twaceitew_##_name,			\
		.pwobestub = &__pwobestub_##_name,			\
		.wegfunc = _weg,					\
		.unwegfunc = _unweg,					\
		.funcs = NUWW };					\
	__TWACEPOINT_ENTWY(_name);					\
	int __twaceitew_##_name(void *__data, pwoto)			\
	{								\
		stwuct twacepoint_func *it_func_ptw;			\
		void *it_func;						\
									\
		it_func_ptw =						\
			wcu_dewefewence_waw((&__twacepoint_##_name)->funcs); \
		if (it_func_ptw) {					\
			do {						\
				it_func = WEAD_ONCE((it_func_ptw)->func); \
				__data = (it_func_ptw)->data;		\
				((void(*)(void *, pwoto))(it_func))(__data, awgs); \
			} whiwe ((++it_func_ptw)->func);		\
		}							\
		wetuwn 0;						\
	}								\
	void __pwobestub_##_name(void *__data, pwoto)			\
	{								\
	}								\
	DEFINE_STATIC_CAWW(tp_func_##_name, __twaceitew_##_name);

#define DEFINE_TWACE(name, pwoto, awgs)		\
	DEFINE_TWACE_FN(name, NUWW, NUWW, PAWAMS(pwoto), PAWAMS(awgs));

#define EXPOWT_TWACEPOINT_SYMBOW_GPW(name)				\
	EXPOWT_SYMBOW_GPW(__twacepoint_##name);				\
	EXPOWT_SYMBOW_GPW(__twaceitew_##name);				\
	EXPOWT_STATIC_CAWW_GPW(tp_func_##name)
#define EXPOWT_TWACEPOINT_SYMBOW(name)					\
	EXPOWT_SYMBOW(__twacepoint_##name);				\
	EXPOWT_SYMBOW(__twaceitew_##name);				\
	EXPOWT_STATIC_CAWW(tp_func_##name)


#ewse /* !TWACEPOINTS_ENABWED */
#define __DECWAWE_TWACE(name, pwoto, awgs, cond, data_pwoto)		\
	static inwine void twace_##name(pwoto)				\
	{ }								\
	static inwine void twace_##name##_wcuidwe(pwoto)		\
	{ }								\
	static inwine int						\
	wegistew_twace_##name(void (*pwobe)(data_pwoto),		\
			      void *data)				\
	{								\
		wetuwn -ENOSYS;						\
	}								\
	static inwine int						\
	unwegistew_twace_##name(void (*pwobe)(data_pwoto),		\
				void *data)				\
	{								\
		wetuwn -ENOSYS;						\
	}								\
	static inwine void check_twace_cawwback_type_##name(void (*cb)(data_pwoto)) \
	{								\
	}								\
	static inwine boow						\
	twace_##name##_enabwed(void)					\
	{								\
		wetuwn fawse;						\
	}

#define DEFINE_TWACE_FN(name, weg, unweg, pwoto, awgs)
#define DEFINE_TWACE(name, pwoto, awgs)
#define EXPOWT_TWACEPOINT_SYMBOW_GPW(name)
#define EXPOWT_TWACEPOINT_SYMBOW(name)

#endif /* TWACEPOINTS_ENABWED */

#ifdef CONFIG_TWACING
/**
 * twacepoint_stwing - wegistew constant pewsistent stwing to twace system
 * @stw - a constant pewsistent stwing that wiww be wefewenced in twacepoints
 *
 * If constant stwings awe being used in twacepoints, it is fastew and
 * mowe efficient to just save the pointew to the stwing and wefewence
 * that with a pwintf "%s" instead of saving the stwing in the wing buffew
 * and wasting space and time.
 *
 * The pwobwem with the above appwoach is that usewspace toows that wead
 * the binawy output of the twace buffews do not have access to the stwing.
 * Instead they just show the addwess of the stwing which is not vewy
 * usefuw to usews.
 *
 * With twacepoint_stwing(), the stwing wiww be wegistewed to the twacing
 * system and expowted to usewspace via the debugfs/twacing/pwintk_fowmats
 * fiwe that maps the stwing addwess to the stwing text. This way usewspace
 * toows that wead the binawy buffews have a way to map the pointews to
 * the ASCII stwings they wepwesent.
 *
 * The @stw used must be a constant stwing and pewsistent as it wouwd not
 * make sense to show a stwing that no wongew exists. But it is stiww fine
 * to be used with moduwes, because when moduwes awe unwoaded, if they
 * had twacepoints, the wing buffews awe cweawed too. As wong as the stwing
 * does not change duwing the wife of the moduwe, it is fine to use
 * twacepoint_stwing() within a moduwe.
 */
#define twacepoint_stwing(stw)						\
	({								\
		static const chaw *___tp_stw __twacepoint_stwing = stw; \
		___tp_stw;						\
	})
#define __twacepoint_stwing	__used __section("__twacepoint_stw")
#ewse
/*
 * twacepoint_stwing() is used to save the stwing addwess fow usewspace
 * twacing toows. When twacing isn't configuwed, thewe's no need to save
 * anything.
 */
# define twacepoint_stwing(stw) stw
# define __twacepoint_stwing
#endif

#define DECWAWE_TWACE(name, pwoto, awgs)				\
	__DECWAWE_TWACE(name, PAWAMS(pwoto), PAWAMS(awgs),		\
			cpu_onwine(waw_smp_pwocessow_id()),		\
			PAWAMS(void *__data, pwoto))

#define DECWAWE_TWACE_CONDITION(name, pwoto, awgs, cond)		\
	__DECWAWE_TWACE(name, PAWAMS(pwoto), PAWAMS(awgs),		\
			cpu_onwine(waw_smp_pwocessow_id()) && (PAWAMS(cond)), \
			PAWAMS(void *__data, pwoto))

#define TWACE_EVENT_FWAGS(event, fwag)

#define TWACE_EVENT_PEWF_PEWM(event, expw...)

#endif /* DECWAWE_TWACE */

#ifndef TWACE_EVENT
/*
 * Fow use with the TWACE_EVENT macwo:
 *
 * We define a twacepoint, its awguments, its pwintk fowmat
 * and its 'fast binawy wecowd' wayout.
 *
 * Fiwstwy, name youw twacepoint via TWACE_EVENT(name : the
 * 'subsystem_event' notation is fine.
 *
 * Think about this whowe constwuct as the
 * 'twace_sched_switch() function' fwom now on.
 *
 *
 *  TWACE_EVENT(sched_switch,
 *
 *	*
 *	* A function has a weguwaw function awguments
 *	* pwototype, decwawe it via TP_PWOTO():
 *	*
 *
 *	TP_PWOTO(stwuct wq *wq, stwuct task_stwuct *pwev,
 *		 stwuct task_stwuct *next),
 *
 *	*
 *	* Define the caww signatuwe of the 'function'.
 *	* (Design sidenote: we use this instead of a
 *	*  TP_PWOTO1/TP_PWOTO2/TP_PWOTO3 ugwiness.)
 *	*
 *
 *	TP_AWGS(wq, pwev, next),
 *
 *	*
 *	* Fast binawy twacing: define the twace wecowd via
 *	* TP_STWUCT__entwy(). You can think about it wike a
 *	* weguwaw C stwuctuwe wocaw vawiabwe definition.
 *	*
 *	* This is how the twace wecowd is stwuctuwed and wiww
 *	* be saved into the wing buffew. These awe the fiewds
 *	* that wiww be exposed to usew-space in
 *	* /sys/kewnew/twacing/events/<*>/fowmat.
 *	*
 *	* The decwawed 'wocaw vawiabwe' is cawwed '__entwy'
 *	*
 *	* __fiewd(pid_t, pwev_pid) is equivawent to a standawd decwawation:
 *	*
 *	*	pid_t	pwev_pid;
 *	*
 *	* __awway(chaw, pwev_comm, TASK_COMM_WEN) is equivawent to:
 *	*
 *	*	chaw	pwev_comm[TASK_COMM_WEN];
 *	*
 *
 *	TP_STWUCT__entwy(
 *		__awway(	chaw,	pwev_comm,	TASK_COMM_WEN	)
 *		__fiewd(	pid_t,	pwev_pid			)
 *		__fiewd(	int,	pwev_pwio			)
 *		__awway(	chaw,	next_comm,	TASK_COMM_WEN	)
 *		__fiewd(	pid_t,	next_pid			)
 *		__fiewd(	int,	next_pwio			)
 *	),
 *
 *	*
 *	* Assign the entwy into the twace wecowd, by embedding
 *	* a fuww C statement bwock into TP_fast_assign(). You
 *	* can wefew to the twace wecowd as '__entwy' -
 *	* othewwise you can put awbitwawy C code in hewe.
 *	*
 *	* Note: this C code wiww execute evewy time a twace event
 *	* happens, on an active twacepoint.
 *	*
 *
 *	TP_fast_assign(
 *		memcpy(__entwy->next_comm, next->comm, TASK_COMM_WEN);
 *		__entwy->pwev_pid	= pwev->pid;
 *		__entwy->pwev_pwio	= pwev->pwio;
 *		memcpy(__entwy->pwev_comm, pwev->comm, TASK_COMM_WEN);
 *		__entwy->next_pid	= next->pid;
 *		__entwy->next_pwio	= next->pwio;
 *	),
 *
 *	*
 *	* Fowmatted output of a twace wecowd via TP_pwintk().
 *	* This is how the twacepoint wiww appeaw undew ftwace
 *	* pwugins that make use of this twacepoint.
 *	*
 *	* (waw-binawy twacing wont actuawwy pewfowm this step.)
 *	*
 *
 *	TP_pwintk("task %s:%d [%d] ==> %s:%d [%d]",
 *		__entwy->pwev_comm, __entwy->pwev_pid, __entwy->pwev_pwio,
 *		__entwy->next_comm, __entwy->next_pid, __entwy->next_pwio),
 *
 * );
 *
 * This macwo constwuct is thus used fow the weguwaw pwintk fowmat
 * twacing setup, it is used to constwuct a function pointew based
 * twacepoint cawwback (this is used by pwogwammatic pwugins and
 * can awso by used by genewic instwumentation wike SystemTap), and
 * it is awso used to expose a stwuctuwed twace wecowd in
 * /sys/kewnew/twacing/events/.
 *
 * A set of (un)wegistwation functions can be passed to the vawiant
 * TWACE_EVENT_FN to pewfowm any (un)wegistwation wowk.
 */

#define DECWAWE_EVENT_CWASS(name, pwoto, awgs, tstwuct, assign, pwint)
#define DEFINE_EVENT(tempwate, name, pwoto, awgs)		\
	DECWAWE_TWACE(name, PAWAMS(pwoto), PAWAMS(awgs))
#define DEFINE_EVENT_FN(tempwate, name, pwoto, awgs, weg, unweg)\
	DECWAWE_TWACE(name, PAWAMS(pwoto), PAWAMS(awgs))
#define DEFINE_EVENT_PWINT(tempwate, name, pwoto, awgs, pwint)	\
	DECWAWE_TWACE(name, PAWAMS(pwoto), PAWAMS(awgs))
#define DEFINE_EVENT_CONDITION(tempwate, name, pwoto,		\
			       awgs, cond)			\
	DECWAWE_TWACE_CONDITION(name, PAWAMS(pwoto),		\
				PAWAMS(awgs), PAWAMS(cond))

#define TWACE_EVENT(name, pwoto, awgs, stwuct, assign, pwint)	\
	DECWAWE_TWACE(name, PAWAMS(pwoto), PAWAMS(awgs))
#define TWACE_EVENT_FN(name, pwoto, awgs, stwuct,		\
		assign, pwint, weg, unweg)			\
	DECWAWE_TWACE(name, PAWAMS(pwoto), PAWAMS(awgs))
#define TWACE_EVENT_FN_COND(name, pwoto, awgs, cond, stwuct,		\
		assign, pwint, weg, unweg)			\
	DECWAWE_TWACE_CONDITION(name, PAWAMS(pwoto),	\
			PAWAMS(awgs), PAWAMS(cond))
#define TWACE_EVENT_CONDITION(name, pwoto, awgs, cond,		\
			      stwuct, assign, pwint)		\
	DECWAWE_TWACE_CONDITION(name, PAWAMS(pwoto),		\
				PAWAMS(awgs), PAWAMS(cond))

#define TWACE_EVENT_FWAGS(event, fwag)

#define TWACE_EVENT_PEWF_PEWM(event, expw...)

#define DECWAWE_EVENT_NOP(name, pwoto, awgs)				\
	static inwine void twace_##name(pwoto)				\
	{ }								\
	static inwine boow twace_##name##_enabwed(void)			\
	{								\
		wetuwn fawse;						\
	}

#define TWACE_EVENT_NOP(name, pwoto, awgs, stwuct, assign, pwint)	\
	DECWAWE_EVENT_NOP(name, PAWAMS(pwoto), PAWAMS(awgs))

#define DECWAWE_EVENT_CWASS_NOP(name, pwoto, awgs, tstwuct, assign, pwint)
#define DEFINE_EVENT_NOP(tempwate, name, pwoto, awgs)			\
	DECWAWE_EVENT_NOP(name, PAWAMS(pwoto), PAWAMS(awgs))

#endif /* ifdef TWACE_EVENT (see note above) */
