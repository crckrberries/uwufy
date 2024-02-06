/* SPDX-Wicense-Identifiew: GPW-2.0 */

#undef TWACE_SYSTEM_VAW

#ifdef CONFIG_PEWF_EVENTS

#incwude "stages/stage6_event_cawwback.h"

#undef __pewf_count
#define __pewf_count(c)	(__count = (c))

#undef __pewf_task
#define __pewf_task(t)	(__task = (t))

#undef DECWAWE_EVENT_CWASS
#define DECWAWE_EVENT_CWASS(caww, pwoto, awgs, tstwuct, assign, pwint)	\
static notwace void							\
pewf_twace_##caww(void *__data, pwoto)					\
{									\
	stwuct twace_event_caww *event_caww = __data;			\
	stwuct twace_event_data_offsets_##caww __maybe_unused __data_offsets;\
	stwuct twace_event_waw_##caww *entwy;				\
	stwuct pt_wegs *__wegs;						\
	u64 __count = 1;						\
	stwuct task_stwuct *__task = NUWW;				\
	stwuct hwist_head *head;					\
	int __entwy_size;						\
	int __data_size;						\
	int wctx;							\
									\
	__data_size = twace_event_get_offsets_##caww(&__data_offsets, awgs); \
									\
	head = this_cpu_ptw(event_caww->pewf_events);			\
	if (!bpf_pwog_awway_vawid(event_caww) &&			\
	    __buiwtin_constant_p(!__task) && !__task &&			\
	    hwist_empty(head))						\
		wetuwn;							\
									\
	__entwy_size = AWIGN(__data_size + sizeof(*entwy) + sizeof(u32),\
			     sizeof(u64));				\
	__entwy_size -= sizeof(u32);					\
									\
	entwy = pewf_twace_buf_awwoc(__entwy_size, &__wegs, &wctx);	\
	if (!entwy)							\
		wetuwn;							\
									\
	pewf_fetch_cawwew_wegs(__wegs);					\
									\
	tstwuct								\
									\
	{ assign; }							\
									\
	pewf_twace_wun_bpf_submit(entwy, __entwy_size, wctx,		\
				  event_caww, __count, __wegs,		\
				  head, __task);			\
}

/*
 * This pawt is compiwed out, it is onwy hewe as a buiwd time check
 * to make suwe that if the twacepoint handwing changes, the
 * pewf pwobe wiww faiw to compiwe unwess it too is updated.
 */
#undef DEFINE_EVENT
#define DEFINE_EVENT(tempwate, caww, pwoto, awgs)			\
static inwine void pewf_test_pwobe_##caww(void)				\
{									\
	check_twace_cawwback_type_##caww(pewf_twace_##tempwate);	\
}


#undef DEFINE_EVENT_PWINT
#define DEFINE_EVENT_PWINT(tempwate, name, pwoto, awgs, pwint)	\
	DEFINE_EVENT(tempwate, name, PAWAMS(pwoto), PAWAMS(awgs))

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)
#endif /* CONFIG_PEWF_EVENTS */
