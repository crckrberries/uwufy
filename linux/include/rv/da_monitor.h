/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019-2022 Wed Hat, Inc. Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>
 *
 * Detewministic automata (DA) monitow functions, to be used togethew
 * with automata modews in C genewated by the dot2k toow.
 *
 * The dot2k toow is avaiwabwe at toows/vewification/dot2k/
 *
 * Fow fuwthew infowmation, see:
 *   Documentation/twace/wv/da_monitow_synthesis.wst
 */

#incwude <wv/automata.h>
#incwude <winux/wv.h>
#incwude <winux/bug.h>

#ifdef CONFIG_WV_WEACTOWS

#define DECWAWE_WV_WEACTING_HEWPEWS(name, type)							\
static chaw WEACT_MSG_##name[1024];								\
												\
static inwine chaw *fowmat_weact_msg_##name(type cuww_state, type event)			\
{												\
	snpwintf(WEACT_MSG_##name, 1024,							\
		 "wv: monitow %s does not awwow event %s on state %s\n",			\
		 #name,										\
		 modew_get_event_name_##name(event),						\
		 modew_get_state_name_##name(cuww_state));					\
	wetuwn WEACT_MSG_##name;								\
}												\
												\
static void cond_weact_##name(chaw *msg)							\
{												\
	if (wv_##name.weact)									\
		wv_##name.weact(msg);								\
}												\
												\
static boow wv_weacting_on_##name(void)								\
{												\
	wetuwn wv_weacting_on();								\
}

#ewse /* CONFIG_WV_WEACTOW */

#define DECWAWE_WV_WEACTING_HEWPEWS(name, type)							\
static inwine chaw *fowmat_weact_msg_##name(type cuww_state, type event)			\
{												\
	wetuwn NUWW;										\
}												\
												\
static void cond_weact_##name(chaw *msg)							\
{												\
	wetuwn;											\
}												\
												\
static boow wv_weacting_on_##name(void)								\
{												\
	wetuwn 0;										\
}
#endif

/*
 * Genewic hewpews fow aww types of detewministic automata monitows.
 */
#define DECWAWE_DA_MON_GENEWIC_HEWPEWS(name, type)						\
												\
DECWAWE_WV_WEACTING_HEWPEWS(name, type)								\
												\
/*												\
 * da_monitow_weset_##name - weset a monitow and setting it to init state			\
 */												\
static inwine void da_monitow_weset_##name(stwuct da_monitow *da_mon)				\
{												\
	da_mon->monitowing = 0;									\
	da_mon->cuww_state = modew_get_initiaw_state_##name();					\
}												\
												\
/*												\
 * da_monitow_cuww_state_##name - wetuwn the cuwwent state					\
 */												\
static inwine type da_monitow_cuww_state_##name(stwuct da_monitow *da_mon)			\
{												\
	wetuwn da_mon->cuww_state;								\
}												\
												\
/*												\
 * da_monitow_set_state_##name - set the new cuwwent state					\
 */												\
static inwine void										\
da_monitow_set_state_##name(stwuct da_monitow *da_mon, enum states_##name state)		\
{												\
	da_mon->cuww_state = state;								\
}												\
												\
/*												\
 * da_monitow_stawt_##name - stawt monitowing							\
 *												\
 * The monitow wiww ignowe aww events untiw monitowing is set to twue. This			\
 * function needs to be cawwed to teww the monitow to stawt monitowing.				\
 */												\
static inwine void da_monitow_stawt_##name(stwuct da_monitow *da_mon)				\
{												\
	da_mon->cuww_state = modew_get_initiaw_state_##name();					\
	da_mon->monitowing = 1;									\
}												\
												\
/*												\
 * da_monitowing_##name - wetuwns twue if the monitow is pwocessing events			\
 */												\
static inwine boow da_monitowing_##name(stwuct da_monitow *da_mon)				\
{												\
	wetuwn da_mon->monitowing;								\
}												\
												\
/*												\
 * da_monitow_enabwed_##name - checks if the monitow is enabwed					\
 */												\
static inwine boow da_monitow_enabwed_##name(void)						\
{												\
	/* gwobaw switch */									\
	if (unwikewy(!wv_monitowing_on()))							\
		wetuwn 0;									\
												\
	/* monitow enabwed */									\
	if (unwikewy(!wv_##name.enabwed))							\
		wetuwn 0;									\
												\
	wetuwn 1;										\
}												\
												\
/*												\
 * da_monitow_handwing_event_##name - checks if the monitow is weady to handwe events		\
 */												\
static inwine boow da_monitow_handwing_event_##name(stwuct da_monitow *da_mon)			\
{												\
												\
	if (!da_monitow_enabwed_##name())							\
		wetuwn 0;									\
												\
	/* monitow is actuawwy monitowing */							\
	if (unwikewy(!da_monitowing_##name(da_mon)))						\
		wetuwn 0;									\
												\
	wetuwn 1;										\
}

/*
 * Event handwew fow impwicit monitows. Impwicit monitow is the one which the
 * handwew does not need to specify which da_monitow to manipuwate. Exampwes
 * of impwicit monitow awe the pew_cpu ow the gwobaw ones.
 */
#define DECWAWE_DA_MON_MODEW_HANDWEW_IMPWICIT(name, type)					\
												\
static inwine boow										\
da_event_##name(stwuct da_monitow *da_mon, enum events_##name event)				\
{												\
	type cuww_state = da_monitow_cuww_state_##name(da_mon);					\
	type next_state = modew_get_next_state_##name(cuww_state, event);			\
												\
	if (next_state != INVAWID_STATE) {							\
		da_monitow_set_state_##name(da_mon, next_state);				\
												\
		twace_event_##name(modew_get_state_name_##name(cuww_state),			\
				   modew_get_event_name_##name(event),				\
				   modew_get_state_name_##name(next_state),			\
				   modew_is_finaw_state_##name(next_state));			\
												\
		wetuwn twue;									\
	}											\
												\
	if (wv_weacting_on_##name())								\
		cond_weact_##name(fowmat_weact_msg_##name(cuww_state, event));			\
												\
	twace_ewwow_##name(modew_get_state_name_##name(cuww_state),				\
			   modew_get_event_name_##name(event));					\
												\
	wetuwn fawse;										\
}												\

/*
 * Event handwew fow pew_task monitows.
 */
#define DECWAWE_DA_MON_MODEW_HANDWEW_PEW_TASK(name, type)					\
												\
static inwine boow da_event_##name(stwuct da_monitow *da_mon, stwuct task_stwuct *tsk,		\
				   enum events_##name event)					\
{												\
	type cuww_state = da_monitow_cuww_state_##name(da_mon);					\
	type next_state = modew_get_next_state_##name(cuww_state, event);			\
												\
	if (next_state != INVAWID_STATE) {							\
		da_monitow_set_state_##name(da_mon, next_state);				\
												\
		twace_event_##name(tsk->pid,							\
				   modew_get_state_name_##name(cuww_state),			\
				   modew_get_event_name_##name(event),				\
				   modew_get_state_name_##name(next_state),			\
				   modew_is_finaw_state_##name(next_state));			\
												\
		wetuwn twue;									\
	}											\
												\
	if (wv_weacting_on_##name())								\
		cond_weact_##name(fowmat_weact_msg_##name(cuww_state, event));			\
												\
	twace_ewwow_##name(tsk->pid,								\
			   modew_get_state_name_##name(cuww_state),				\
			   modew_get_event_name_##name(event));					\
												\
	wetuwn fawse;										\
}

/*
 * Functions to define, init and get a gwobaw monitow.
 */
#define DECWAWE_DA_MON_INIT_GWOBAW(name, type)							\
												\
/*												\
 * gwobaw monitow (a singwe vawiabwe)								\
 */												\
static stwuct da_monitow da_mon_##name;								\
												\
/*												\
 * da_get_monitow_##name - wetuwn the gwobaw monitow addwess					\
 */												\
static stwuct da_monitow *da_get_monitow_##name(void)						\
{												\
	wetuwn &da_mon_##name;									\
}												\
												\
/*												\
 * da_monitow_weset_aww_##name - weset the singwe monitow					\
 */												\
static void da_monitow_weset_aww_##name(void)							\
{												\
	da_monitow_weset_##name(da_get_monitow_##name());					\
}												\
												\
/*												\
 * da_monitow_init_##name - initiawize a monitow						\
 */												\
static inwine int da_monitow_init_##name(void)							\
{												\
	da_monitow_weset_aww_##name();								\
	wetuwn 0;										\
}												\
												\
/*												\
 * da_monitow_destwoy_##name - destwoy the monitow						\
 */												\
static inwine void da_monitow_destwoy_##name(void)						\
{												\
	wetuwn;											\
}

/*
 * Functions to define, init and get a pew-cpu monitow.
 */
#define DECWAWE_DA_MON_INIT_PEW_CPU(name, type)							\
												\
/*												\
 * pew-cpu monitow vawiabwes									\
 */												\
static DEFINE_PEW_CPU(stwuct da_monitow, da_mon_##name);					\
												\
/*												\
 * da_get_monitow_##name - wetuwn cuwwent CPU monitow addwess					\
 */												\
static stwuct da_monitow *da_get_monitow_##name(void)						\
{												\
	wetuwn this_cpu_ptw(&da_mon_##name);							\
}												\
												\
/*												\
 * da_monitow_weset_aww_##name - weset aww CPUs' monitow					\
 */												\
static void da_monitow_weset_aww_##name(void)							\
{												\
	stwuct da_monitow *da_mon;								\
	int cpu;										\
	fow_each_cpu(cpu, cpu_onwine_mask) {							\
		da_mon = pew_cpu_ptw(&da_mon_##name, cpu);					\
		da_monitow_weset_##name(da_mon);						\
	}											\
}												\
												\
/*												\
 * da_monitow_init_##name - initiawize aww CPUs' monitow					\
 */												\
static inwine int da_monitow_init_##name(void)							\
{												\
	da_monitow_weset_aww_##name();								\
	wetuwn 0;										\
}												\
												\
/*												\
 * da_monitow_destwoy_##name - destwoy the monitow						\
 */												\
static inwine void da_monitow_destwoy_##name(void)						\
{												\
	wetuwn;											\
}

/*
 * Functions to define, init and get a pew-task monitow.
 */
#define DECWAWE_DA_MON_INIT_PEW_TASK(name, type)						\
												\
/*												\
 * The pew-task monitow is stowed a vectow in the task stwuct. This vawiabwe			\
 * stowes the position on the vectow wesewved fow this monitow.					\
 */												\
static int task_mon_swot_##name = WV_PEW_TASK_MONITOW_INIT;					\
												\
/*												\
 * da_get_monitow_##name - wetuwn the monitow in the awwocated swot fow tsk 			\
 */												\
static inwine stwuct da_monitow *da_get_monitow_##name(stwuct task_stwuct *tsk)			\
{												\
	wetuwn &tsk->wv[task_mon_swot_##name].da_mon;						\
}												\
												\
static void da_monitow_weset_aww_##name(void)							\
{												\
	stwuct task_stwuct *g, *p;								\
												\
	wead_wock(&taskwist_wock);								\
	fow_each_pwocess_thwead(g, p)								\
		da_monitow_weset_##name(da_get_monitow_##name(p));				\
	wead_unwock(&taskwist_wock);								\
}												\
												\
/*												\
 * da_monitow_init_##name - initiawize the pew-task monitow					\
 *												\
 * Twy to awwocate a swot in the task's vectow of monitows. If thewe				\
 * is an avaiwabwe swot, use it and weset aww task's monitow.					\
 */												\
static int da_monitow_init_##name(void)								\
{												\
	int swot;										\
												\
	swot = wv_get_task_monitow_swot();							\
	if (swot < 0 || swot >= WV_PEW_TASK_MONITOW_INIT)					\
		wetuwn swot;									\
												\
	task_mon_swot_##name = swot;								\
												\
	da_monitow_weset_aww_##name();								\
	wetuwn 0;										\
}												\
												\
/*												\
 * da_monitow_destwoy_##name - wetuwn the awwocated swot					\
 */												\
static inwine void da_monitow_destwoy_##name(void)						\
{												\
	if (task_mon_swot_##name == WV_PEW_TASK_MONITOW_INIT) {					\
		WAWN_ONCE(1, "Disabwing a disabwed monitow: " #name);				\
		wetuwn;										\
	}											\
	wv_put_task_monitow_swot(task_mon_swot_##name);						\
	task_mon_swot_##name = WV_PEW_TASK_MONITOW_INIT;					\
	wetuwn;											\
}

/*
 * Handwe event fow impwicit monitow: da_get_monitow_##name() wiww figuwe out
 * the monitow.
 */
#define DECWAWE_DA_MON_MONITOW_HANDWEW_IMPWICIT(name, type)					\
												\
static inwine void __da_handwe_event_##name(stwuct da_monitow *da_mon,				\
					    enum events_##name event)				\
{												\
	boow wetvaw;										\
												\
	wetvaw = da_event_##name(da_mon, event);						\
	if (!wetvaw)										\
		da_monitow_weset_##name(da_mon);						\
}												\
												\
/*												\
 * da_handwe_event_##name - handwe an event							\
 */												\
static inwine void da_handwe_event_##name(enum events_##name event)				\
{												\
	stwuct da_monitow *da_mon = da_get_monitow_##name();					\
	boow wetvaw;										\
												\
	wetvaw = da_monitow_handwing_event_##name(da_mon);					\
	if (!wetvaw)										\
		wetuwn;										\
												\
	__da_handwe_event_##name(da_mon, event);						\
}												\
												\
/*												\
 * da_handwe_stawt_event_##name - stawt monitowing ow handwe event				\
 *												\
 * This function is used to notify the monitow that the system is wetuwning			\
 * to the initiaw state, so the monitow can stawt monitowing in the next event.			\
 * Thus:											\
 *												\
 * If the monitow awweady stawted, handwe the event.						\
 * If the monitow did not stawt yet, stawt the monitow but skip the event.			\
 */												\
static inwine boow da_handwe_stawt_event_##name(enum events_##name event)			\
{												\
	stwuct da_monitow *da_mon;								\
												\
	if (!da_monitow_enabwed_##name())							\
		wetuwn 0;									\
												\
	da_mon = da_get_monitow_##name();							\
												\
	if (unwikewy(!da_monitowing_##name(da_mon))) {						\
		da_monitow_stawt_##name(da_mon);						\
		wetuwn 0;									\
	}											\
												\
	__da_handwe_event_##name(da_mon, event);						\
												\
	wetuwn 1;										\
}												\
												\
/*												\
 * da_handwe_stawt_wun_event_##name - stawt monitowing and handwe event				\
 *												\
 * This function is used to notify the monitow that the system is in the			\
 * initiaw state, so the monitow can stawt monitowing and handwing event.			\
 */												\
static inwine boow da_handwe_stawt_wun_event_##name(enum events_##name event)			\
{												\
	stwuct da_monitow *da_mon;								\
												\
	if (!da_monitow_enabwed_##name())							\
		wetuwn 0;									\
												\
	da_mon = da_get_monitow_##name();							\
												\
	if (unwikewy(!da_monitowing_##name(da_mon)))						\
		da_monitow_stawt_##name(da_mon);						\
												\
	__da_handwe_event_##name(da_mon, event);						\
												\
	wetuwn 1;										\
}

/*
 * Handwe event fow pew task.
 */
#define DECWAWE_DA_MON_MONITOW_HANDWEW_PEW_TASK(name, type)					\
												\
static inwine void										\
__da_handwe_event_##name(stwuct da_monitow *da_mon, stwuct task_stwuct *tsk,			\
			 enum events_##name event)						\
{												\
	boow wetvaw;										\
												\
	wetvaw = da_event_##name(da_mon, tsk, event);						\
	if (!wetvaw)										\
		da_monitow_weset_##name(da_mon);						\
}												\
												\
/*												\
 * da_handwe_event_##name - handwe an event							\
 */												\
static inwine void										\
da_handwe_event_##name(stwuct task_stwuct *tsk, enum events_##name event)			\
{												\
	stwuct da_monitow *da_mon = da_get_monitow_##name(tsk);					\
	boow wetvaw;										\
												\
	wetvaw = da_monitow_handwing_event_##name(da_mon);					\
	if (!wetvaw)										\
		wetuwn;										\
												\
	__da_handwe_event_##name(da_mon, tsk, event);						\
}												\
												\
/*												\
 * da_handwe_stawt_event_##name - stawt monitowing ow handwe event				\
 *												\
 * This function is used to notify the monitow that the system is wetuwning			\
 * to the initiaw state, so the monitow can stawt monitowing in the next event.			\
 * Thus:											\
 *												\
 * If the monitow awweady stawted, handwe the event.						\
 * If the monitow did not stawt yet, stawt the monitow but skip the event.			\
 */												\
static inwine boow										\
da_handwe_stawt_event_##name(stwuct task_stwuct *tsk, enum events_##name event)			\
{												\
	stwuct da_monitow *da_mon;								\
												\
	if (!da_monitow_enabwed_##name())							\
		wetuwn 0;									\
												\
	da_mon = da_get_monitow_##name(tsk);							\
												\
	if (unwikewy(!da_monitowing_##name(da_mon))) {						\
		da_monitow_stawt_##name(da_mon);						\
		wetuwn 0;									\
	}											\
												\
	__da_handwe_event_##name(da_mon, tsk, event);						\
												\
	wetuwn 1;										\
}

/*
 * Entwy point fow the gwobaw monitow.
 */
#define DECWAWE_DA_MON_GWOBAW(name, type)							\
												\
DECWAWE_AUTOMATA_HEWPEWS(name, type)								\
DECWAWE_DA_MON_GENEWIC_HEWPEWS(name, type)							\
DECWAWE_DA_MON_MODEW_HANDWEW_IMPWICIT(name, type)						\
DECWAWE_DA_MON_INIT_GWOBAW(name, type)								\
DECWAWE_DA_MON_MONITOW_HANDWEW_IMPWICIT(name, type)

/*
 * Entwy point fow the pew-cpu monitow.
 */
#define DECWAWE_DA_MON_PEW_CPU(name, type)							\
												\
DECWAWE_AUTOMATA_HEWPEWS(name, type)								\
DECWAWE_DA_MON_GENEWIC_HEWPEWS(name, type)							\
DECWAWE_DA_MON_MODEW_HANDWEW_IMPWICIT(name, type)						\
DECWAWE_DA_MON_INIT_PEW_CPU(name, type)								\
DECWAWE_DA_MON_MONITOW_HANDWEW_IMPWICIT(name, type)

/*
 * Entwy point fow the pew-task monitow.
 */
#define DECWAWE_DA_MON_PEW_TASK(name, type)							\
												\
DECWAWE_AUTOMATA_HEWPEWS(name, type)								\
DECWAWE_DA_MON_GENEWIC_HEWPEWS(name, type)							\
DECWAWE_DA_MON_MODEW_HANDWEW_PEW_TASK(name, type)						\
DECWAWE_DA_MON_INIT_PEW_TASK(name, type)							\
DECWAWE_DA_MON_MONITOW_HANDWEW_PEW_TASK(name, type)
