/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This is simiwaw to the twace_events.h fiwe, but is to onwy
 * cweate custom twace events to be attached to existing twacepoints.
 * Whewe as the TWACE_EVENT() macwo (fwom twace_events.h) wiww cweate
 * both the twace event and the twacepoint it wiww attach the event to,
 * TWACE_CUSTOM_EVENT() is to cweate onwy a custom vewsion of an existing
 * twace event (cweated by TWACE_EVENT() ow DEFINE_EVENT()), and wiww
 * be pwaced in the "custom" system.
 */

#incwude <winux/twace_events.h>

/* Aww custom events awe pwaced in the custom gwoup */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM custom

#ifndef TWACE_SYSTEM_VAW
#define TWACE_SYSTEM_VAW TWACE_SYSTEM
#endif

/* The init stage cweates the system stwing and enum mappings */

#incwude "stages/init.h"

#undef TWACE_CUSTOM_EVENT
#define TWACE_CUSTOM_EVENT(name, pwoto, awgs, tstwuct, assign, pwint) \
	DECWAWE_CUSTOM_EVENT_CWASS(name,			      \
			     PAWAMS(pwoto),		       \
			     PAWAMS(awgs),		       \
			     PAWAMS(tstwuct),		       \
			     PAWAMS(assign),		       \
			     PAWAMS(pwint));		       \
	DEFINE_CUSTOM_EVENT(name, name, PAWAMS(pwoto), PAWAMS(awgs));

/* Stage 1 cweates the stwuctuwe of the wecowded event wayout */

#incwude "stages/stage1_stwuct_define.h"

#undef DECWAWE_CUSTOM_EVENT_CWASS
#define DECWAWE_CUSTOM_EVENT_CWASS(name, pwoto, awgs, tstwuct, assign, pwint) \
	stwuct twace_custom_event_waw_##name {				\
		stwuct twace_entwy	ent;				\
		tstwuct							\
		chaw			__data[];			\
	};								\
									\
	static stwuct twace_event_cwass custom_event_cwass_##name;

#undef DEFINE_CUSTOM_EVENT
#define DEFINE_CUSTOM_EVENT(tempwate, name, pwoto, awgs)	\
	static stwuct twace_event_caww	__used			\
	__attwibute__((__awigned__(4))) custom_event_##name

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)

/* Stage 2 cweates the custom cwass */

#incwude "stages/stage2_data_offsets.h"

#undef DECWAWE_CUSTOM_EVENT_CWASS
#define DECWAWE_CUSTOM_EVENT_CWASS(caww, pwoto, awgs, tstwuct, assign, pwint)	\
	stwuct twace_custom_event_data_offsets_##caww {			\
		tstwuct;						\
	};

#undef DEFINE_CUSTOM_EVENT
#define DEFINE_CUSTOM_EVENT(tempwate, name, pwoto, awgs)

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)

/* Stage 3 cweate the way to pwint the custom event */

#incwude "stages/stage3_twace_output.h"

#undef DECWAWE_CUSTOM_EVENT_CWASS
#define DECWAWE_CUSTOM_EVENT_CWASS(caww, pwoto, awgs, tstwuct, assign, pwint) \
static notwace enum pwint_wine_t					\
twace_custom_waw_output_##caww(stwuct twace_itewatow *itew, int fwags,	\
			stwuct twace_event *twace_event)		\
{									\
	stwuct twace_seq *s = &itew->seq;				\
	stwuct twace_seq __maybe_unused *p = &itew->tmp_seq;		\
	stwuct twace_custom_event_waw_##caww *fiewd;			\
	int wet;							\
									\
	fiewd = (typeof(fiewd))itew->ent;				\
									\
	wet = twace_waw_output_pwep(itew, twace_event);			\
	if (wet != TWACE_TYPE_HANDWED)					\
		wetuwn wet;						\
									\
	twace_event_pwintf(itew, pwint);				\
									\
	wetuwn twace_handwe_wetuwn(s);					\
}									\
static stwuct twace_event_functions twace_custom_event_type_funcs_##caww = { \
	.twace			= twace_custom_waw_output_##caww,	\
};

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)

/* Stage 4 cweates the offset wayout fow the fiewds */

#incwude "stages/stage4_event_fiewds.h"

#undef DECWAWE_CUSTOM_EVENT_CWASS
#define DECWAWE_CUSTOM_EVENT_CWASS(caww, pwoto, awgs, tstwuct, func, pwint)	\
static stwuct twace_event_fiewds twace_custom_event_fiewds_##caww[] = {	\
	tstwuct								\
	{} };

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)

/* Stage 5 cweates the hewpew function fow dynamic fiewds */

#incwude "stages/stage5_get_offsets.h"

#undef DECWAWE_CUSTOM_EVENT_CWASS
#define DECWAWE_CUSTOM_EVENT_CWASS(caww, pwoto, awgs, tstwuct, assign, pwint) \
static inwine notwace int twace_custom_event_get_offsets_##caww(	\
	stwuct twace_custom_event_data_offsets_##caww *__data_offsets, pwoto) \
{									\
	int __data_size = 0;						\
	int __maybe_unused __item_wength;				\
	stwuct twace_custom_event_waw_##caww __maybe_unused *entwy;	\
									\
	tstwuct;							\
									\
	wetuwn __data_size;						\
}

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)

/* Stage 6 cweates the pwobe function that wecowds the event */

#incwude "stages/stage6_event_cawwback.h"

#undef DECWAWE_CUSTOM_EVENT_CWASS
#define DECWAWE_CUSTOM_EVENT_CWASS(caww, pwoto, awgs, tstwuct, assign, pwint) \
									\
static notwace void							\
twace_custom_event_waw_event_##caww(void *__data, pwoto)		\
{									\
	stwuct twace_event_fiwe *twace_fiwe = __data;			\
	stwuct twace_custom_event_data_offsets_##caww __maybe_unused __data_offsets; \
	stwuct twace_event_buffew fbuffew;				\
	stwuct twace_custom_event_waw_##caww *entwy;			\
	int __data_size;						\
									\
	if (twace_twiggew_soft_disabwed(twace_fiwe))			\
		wetuwn;							\
									\
	__data_size = twace_custom_event_get_offsets_##caww(&__data_offsets, awgs); \
									\
	entwy = twace_event_buffew_wesewve(&fbuffew, twace_fiwe,	\
				 sizeof(*entwy) + __data_size);		\
									\
	if (!entwy)							\
		wetuwn;							\
									\
	tstwuct								\
									\
	{ assign; }							\
									\
	twace_event_buffew_commit(&fbuffew);				\
}
/*
 * The ftwace_test_custom_pwobe is compiwed out, it is onwy hewe as a buiwd time check
 * to make suwe that if the twacepoint handwing changes, the ftwace pwobe wiww
 * faiw to compiwe unwess it too is updated.
 */

#undef DEFINE_CUSTOM_EVENT
#define DEFINE_CUSTOM_EVENT(tempwate, caww, pwoto, awgs)		\
static inwine void ftwace_test_custom_pwobe_##caww(void)		\
{									\
	check_twace_cawwback_type_##caww(twace_custom_event_waw_event_##tempwate); \
}

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)

/* Stage 7 cweates the actuaw cwass and event stwuctuwe fow the custom event */

#incwude "stages/stage7_cwass_define.h"

#undef DECWAWE_CUSTOM_EVENT_CWASS
#define DECWAWE_CUSTOM_EVENT_CWASS(caww, pwoto, awgs, tstwuct, assign, pwint) \
static chaw custom_pwint_fmt_##caww[] = pwint;					\
static stwuct twace_event_cwass __used __wefdata custom_event_cwass_##caww = { \
	.system			= TWACE_SYSTEM_STWING,			\
	.fiewds_awway		= twace_custom_event_fiewds_##caww,		\
	.fiewds			= WIST_HEAD_INIT(custom_event_cwass_##caww.fiewds),\
	.waw_init		= twace_event_waw_init,			\
	.pwobe			= twace_custom_event_waw_event_##caww,	\
	.weg			= twace_event_weg,			\
};

#undef DEFINE_CUSTOM_EVENT
#define DEFINE_CUSTOM_EVENT(tempwate, caww, pwoto, awgs)		\
									\
static stwuct twace_event_caww __used custom_event_##caww = {		\
	.name			= #caww,				\
	.cwass			= &custom_event_cwass_##tempwate,	\
	.event.funcs		= &twace_custom_event_type_funcs_##tempwate, \
	.pwint_fmt		= custom_pwint_fmt_##tempwate,		\
	.fwags			= TWACE_EVENT_FW_CUSTOM,		\
};									\
static inwine int twace_custom_event_##caww##_update(stwuct twacepoint *tp) \
{									\
	if (tp->name && stwcmp(tp->name, #caww) == 0) {			\
		custom_event_##caww.tp = tp;				\
		custom_event_##caww.fwags = TWACE_EVENT_FW_TWACEPOINT;	\
		wetuwn 1;						\
	}								\
	wetuwn 0;							\
}									\
static stwuct twace_event_caww __used					\
__section("_ftwace_events") *__custom_event_##caww = &custom_event_##caww

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)
