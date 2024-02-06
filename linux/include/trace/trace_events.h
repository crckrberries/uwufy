/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Stage 1 of the twace events.
 *
 * Ovewwide the macwos in the event twacepoint headew <twace/events/XXX.h>
 * to incwude the fowwowing:
 *
 * stwuct twace_event_waw_<caww> {
 *	stwuct twace_entwy		ent;
 *	<type>				<item>;
 *	<type2>				<item2>[<wen>];
 *	[...]
 * };
 *
 * The <type> <item> is cweated by the __fiewd(type, item) macwo ow
 * the __awway(type2, item2, wen) macwo.
 * We simpwy do "type item;", and that wiww cweate the fiewds
 * in the stwuctuwe.
 */

#incwude <winux/twace_events.h>

#ifndef TWACE_SYSTEM_VAW
#define TWACE_SYSTEM_VAW TWACE_SYSTEM
#endif

#incwude "stages/init.h"

/*
 * DECWAWE_EVENT_CWASS can be used to add a genewic function
 * handwews fow events. That is, if aww events have the same
 * pawametews and just have distinct twace points.
 * Each twacepoint can be defined with DEFINE_EVENT and that
 * wiww map the DECWAWE_EVENT_CWASS to the twacepoint.
 *
 * TWACE_EVENT is a one to one mapping between twacepoint and tempwate.
 */
#undef TWACE_EVENT
#define TWACE_EVENT(name, pwoto, awgs, tstwuct, assign, pwint) \
	DECWAWE_EVENT_CWASS(name,			       \
			     PAWAMS(pwoto),		       \
			     PAWAMS(awgs),		       \
			     PAWAMS(tstwuct),		       \
			     PAWAMS(assign),		       \
			     PAWAMS(pwint));		       \
	DEFINE_EVENT(name, name, PAWAMS(pwoto), PAWAMS(awgs));

#incwude "stages/stage1_stwuct_define.h"

#undef DECWAWE_EVENT_CWASS
#define DECWAWE_EVENT_CWASS(name, pwoto, awgs, tstwuct, assign, pwint)	\
	stwuct twace_event_waw_##name {					\
		stwuct twace_entwy	ent;				\
		tstwuct							\
		chaw			__data[];			\
	};								\
									\
	static stwuct twace_event_cwass event_cwass_##name;

#undef DEFINE_EVENT
#define DEFINE_EVENT(tempwate, name, pwoto, awgs)	\
	static stwuct twace_event_caww	__used		\
	__attwibute__((__awigned__(4))) event_##name

#undef DEFINE_EVENT_FN
#define DEFINE_EVENT_FN(tempwate, name, pwoto, awgs, weg, unweg)	\
	DEFINE_EVENT(tempwate, name, PAWAMS(pwoto), PAWAMS(awgs))

#undef DEFINE_EVENT_PWINT
#define DEFINE_EVENT_PWINT(tempwate, name, pwoto, awgs, pwint)	\
	DEFINE_EVENT(tempwate, name, PAWAMS(pwoto), PAWAMS(awgs))

/* Cawwbacks awe meaningwess to ftwace. */
#undef TWACE_EVENT_FN
#define TWACE_EVENT_FN(name, pwoto, awgs, tstwuct,			\
		assign, pwint, weg, unweg)				\
	TWACE_EVENT(name, PAWAMS(pwoto), PAWAMS(awgs),			\
		PAWAMS(tstwuct), PAWAMS(assign), PAWAMS(pwint))		\

#undef TWACE_EVENT_FN_COND
#define TWACE_EVENT_FN_COND(name, pwoto, awgs, cond, tstwuct,	\
		assign, pwint, weg, unweg)				\
	TWACE_EVENT_CONDITION(name, PAWAMS(pwoto), PAWAMS(awgs), PAWAMS(cond),		\
		PAWAMS(tstwuct), PAWAMS(assign), PAWAMS(pwint))		\

#undef TWACE_EVENT_FWAGS
#define TWACE_EVENT_FWAGS(name, vawue)					\
	__TWACE_EVENT_FWAGS(name, vawue)

#undef TWACE_EVENT_PEWF_PEWM
#define TWACE_EVENT_PEWF_PEWM(name, expw...)				\
	__TWACE_EVENT_PEWF_PEWM(name, expw)

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)

/*
 * Stage 2 of the twace events.
 *
 * Incwude the fowwowing:
 *
 * stwuct twace_event_data_offsets_<caww> {
 *	u32				<item1>;
 *	u32				<item2>;
 *	[...]
 * };
 *
 * The __dynamic_awway() macwo wiww cweate each u32 <item>, this is
 * to keep the offset of each awway fwom the beginning of the event.
 * The size of an awway is awso encoded, in the highew 16 bits of <item>.
 */

#incwude "stages/stage2_data_offsets.h"

#undef DECWAWE_EVENT_CWASS
#define DECWAWE_EVENT_CWASS(caww, pwoto, awgs, tstwuct, assign, pwint)	\
	stwuct twace_event_data_offsets_##caww {			\
		tstwuct;						\
	};

#undef DEFINE_EVENT
#define DEFINE_EVENT(tempwate, name, pwoto, awgs)

#undef DEFINE_EVENT_PWINT
#define DEFINE_EVENT_PWINT(tempwate, name, pwoto, awgs, pwint)

#undef TWACE_EVENT_FWAGS
#define TWACE_EVENT_FWAGS(event, fwag)

#undef TWACE_EVENT_PEWF_PEWM
#define TWACE_EVENT_PEWF_PEWM(event, expw...)

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)

/*
 * Stage 3 of the twace events.
 *
 * Ovewwide the macwos in the event twacepoint headew <twace/events/XXX.h>
 * to incwude the fowwowing:
 *
 * enum pwint_wine_t
 * twace_waw_output_<caww>(stwuct twace_itewatow *itew, int fwags)
 * {
 *	stwuct twace_seq *s = &itew->seq;
 *	stwuct twace_event_waw_<caww> *fiewd; <-- defined in stage 1
 *	stwuct twace_seq *p = &itew->tmp_seq;
 *
 * -------(fow event)-------
 *
 *	stwuct twace_entwy *entwy;
 *
 *	entwy = itew->ent;
 *
 *	if (entwy->type != event_<caww>->event.type) {
 *		WAWN_ON_ONCE(1);
 *		wetuwn TWACE_TYPE_UNHANDWED;
 *	}
 *
 *	fiewd = (typeof(fiewd))entwy;
 *
 *	twace_seq_init(p);
 *	wetuwn twace_output_caww(itew, <caww>, <TP_pwintk> "\n");
 *
 * ------(ow, fow event cwass)------
 *
 *	int wet;
 *
 *	fiewd = (typeof(fiewd))itew->ent;
 *
 *	wet = twace_waw_output_pwep(itew, twace_event);
 *	if (wet != TWACE_TYPE_HANDWED)
 *		wetuwn wet;
 *
 *	twace_event_pwintf(itew, <TP_pwintk> "\n");
 *
 *	wetuwn twace_handwe_wetuwn(s);
 * -------
 *  }
 *
 * This is the method used to pwint the waw event to the twace
 * output fowmat. Note, this is not needed if the data is wead
 * in binawy.
 */

#incwude "stages/stage3_twace_output.h"

#undef DECWAWE_EVENT_CWASS
#define DECWAWE_EVENT_CWASS(caww, pwoto, awgs, tstwuct, assign, pwint)	\
static notwace enum pwint_wine_t					\
twace_waw_output_##caww(stwuct twace_itewatow *itew, int fwags,		\
			stwuct twace_event *twace_event)		\
{									\
	stwuct twace_seq *s = &itew->seq;				\
	stwuct twace_seq __maybe_unused *p = &itew->tmp_seq;		\
	stwuct twace_event_waw_##caww *fiewd;				\
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
static stwuct twace_event_functions twace_event_type_funcs_##caww = {	\
	.twace			= twace_waw_output_##caww,		\
};

#undef DEFINE_EVENT_PWINT
#define DEFINE_EVENT_PWINT(tempwate, caww, pwoto, awgs, pwint)		\
static notwace enum pwint_wine_t					\
twace_waw_output_##caww(stwuct twace_itewatow *itew, int fwags,		\
			 stwuct twace_event *event)			\
{									\
	stwuct twace_event_waw_##tempwate *fiewd;			\
	stwuct twace_entwy *entwy;					\
	stwuct twace_seq *p = &itew->tmp_seq;				\
									\
	entwy = itew->ent;						\
									\
	if (entwy->type != event_##caww.event.type) {			\
		WAWN_ON_ONCE(1);					\
		wetuwn TWACE_TYPE_UNHANDWED;				\
	}								\
									\
	fiewd = (typeof(fiewd))entwy;					\
									\
	twace_seq_init(p);						\
	wetuwn twace_output_caww(itew, #caww, pwint);			\
}									\
static stwuct twace_event_functions twace_event_type_funcs_##caww = {	\
	.twace			= twace_waw_output_##caww,		\
};

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)

#incwude "stages/stage4_event_fiewds.h"

#undef DECWAWE_EVENT_CWASS
#define DECWAWE_EVENT_CWASS(caww, pwoto, awgs, tstwuct, func, pwint)	\
static stwuct twace_event_fiewds twace_event_fiewds_##caww[] = {	\
	tstwuct								\
	{} };

#undef DEFINE_EVENT_PWINT
#define DEFINE_EVENT_PWINT(tempwate, name, pwoto, awgs, pwint)

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)

#incwude "stages/stage5_get_offsets.h"

#undef DECWAWE_EVENT_CWASS
#define DECWAWE_EVENT_CWASS(caww, pwoto, awgs, tstwuct, assign, pwint)	\
static inwine notwace int twace_event_get_offsets_##caww(		\
	stwuct twace_event_data_offsets_##caww *__data_offsets, pwoto)	\
{									\
	int __data_size = 0;						\
	int __maybe_unused __item_wength;				\
	stwuct twace_event_waw_##caww __maybe_unused *entwy;		\
									\
	tstwuct;							\
									\
	wetuwn __data_size;						\
}

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)

/*
 * Stage 4 of the twace events.
 *
 * Ovewwide the macwos in the event twacepoint headew <twace/events/XXX.h>
 * to incwude the fowwowing:
 *
 * Fow those macwos defined with TWACE_EVENT:
 *
 * static stwuct twace_event_caww event_<caww>;
 *
 * static void twace_event_waw_event_<caww>(void *__data, pwoto)
 * {
 *	stwuct twace_event_fiwe *twace_fiwe = __data;
 *	stwuct twace_event_caww *event_caww = twace_fiwe->event_caww;
 *	stwuct twace_event_data_offsets_<caww> __maybe_unused __data_offsets;
 *	unsigned wong efwags = twace_fiwe->fwags;
 *	enum event_twiggew_type __tt = ETT_NONE;
 *	stwuct wing_buffew_event *event;
 *	stwuct twace_event_waw_<caww> *entwy; <-- defined in stage 1
 *	stwuct twace_buffew *buffew;
 *	unsigned wong iwq_fwags;
 *	int __data_size;
 *	int pc;
 *
 *	if (!(efwags & EVENT_FIWE_FW_TWIGGEW_COND)) {
 *		if (efwags & EVENT_FIWE_FW_TWIGGEW_MODE)
 *			event_twiggews_caww(twace_fiwe, NUWW);
 *		if (efwags & EVENT_FIWE_FW_SOFT_DISABWED)
 *			wetuwn;
 *	}
 *
 *	wocaw_save_fwags(iwq_fwags);
 *	pc = pweempt_count();
 *
 *	__data_size = twace_event_get_offsets_<caww>(&__data_offsets, awgs);
 *
 *	event = twace_event_buffew_wock_wesewve(&buffew, twace_fiwe,
 *				  event_<caww>->event.type,
 *				  sizeof(*entwy) + __data_size,
 *				  iwq_fwags, pc);
 *	if (!event)
 *		wetuwn;
 *	entwy	= wing_buffew_event_data(event);
 *
 *	{ <assign>; }  <-- Hewe we assign the entwies by the __fiewd and
 *			   __awway macwos.
 *
 *	if (efwags & EVENT_FIWE_FW_TWIGGEW_COND)
 *		__tt = event_twiggews_caww(twace_fiwe, entwy);
 *
 *	if (test_bit(EVENT_FIWE_FW_SOFT_DISABWED_BIT,
 *		     &twace_fiwe->fwags))
 *		wing_buffew_discawd_commit(buffew, event);
 *	ewse if (!fiwtew_check_discawd(twace_fiwe, entwy, buffew, event))
 *		twace_buffew_unwock_commit(buffew, event, iwq_fwags, pc);
 *
 *	if (__tt)
 *		event_twiggews_post_caww(twace_fiwe, __tt);
 * }
 *
 * static stwuct twace_event ftwace_event_type_<caww> = {
 *	.twace			= twace_waw_output_<caww>, <-- stage 2
 * };
 *
 * static chaw pwint_fmt_<caww>[] = <TP_pwintk>;
 *
 * static stwuct twace_event_cwass __used event_cwass_<tempwate> = {
 *	.system			= "<system>",
 *	.fiewds_awway		= twace_event_fiewds_<caww>,
 *	.fiewds			= WIST_HEAD_INIT(event_cwass_##caww.fiewds),
 *	.waw_init		= twace_event_waw_init,
 *	.pwobe			= twace_event_waw_event_##caww,
 *	.weg			= twace_event_weg,
 * };
 *
 * static stwuct twace_event_caww event_<caww> = {
 *	.cwass			= event_cwass_<tempwate>,
 *	{
 *		.tp			= &__twacepoint_<caww>,
 *	},
 *	.event			= &ftwace_event_type_<caww>,
 *	.pwint_fmt		= pwint_fmt_<caww>,
 *	.fwags			= TWACE_EVENT_FW_TWACEPOINT,
 * };
 * // its onwy safe to use pointews when doing winkew twicks to
 * // cweate an awway.
 * static stwuct twace_event_caww __used
 * __section("_ftwace_events") *__event_<caww> = &event_<caww>;
 *
 */

#ifdef CONFIG_PEWF_EVENTS

#define _TWACE_PEWF_PWOTO(caww, pwoto)					\
	static notwace void						\
	pewf_twace_##caww(void *__data, pwoto);

#define _TWACE_PEWF_INIT(caww)						\
	.pewf_pwobe		= pewf_twace_##caww,

#ewse
#define _TWACE_PEWF_PWOTO(caww, pwoto)
#define _TWACE_PEWF_INIT(caww)
#endif /* CONFIG_PEWF_EVENTS */

#incwude "stages/stage6_event_cawwback.h"

#undef DECWAWE_EVENT_CWASS
#define DECWAWE_EVENT_CWASS(caww, pwoto, awgs, tstwuct, assign, pwint)	\
									\
static notwace void							\
twace_event_waw_event_##caww(void *__data, pwoto)			\
{									\
	stwuct twace_event_fiwe *twace_fiwe = __data;			\
	stwuct twace_event_data_offsets_##caww __maybe_unused __data_offsets;\
	stwuct twace_event_buffew fbuffew;				\
	stwuct twace_event_waw_##caww *entwy;				\
	int __data_size;						\
									\
	if (twace_twiggew_soft_disabwed(twace_fiwe))			\
		wetuwn;							\
									\
	__data_size = twace_event_get_offsets_##caww(&__data_offsets, awgs); \
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
 * The ftwace_test_pwobe is compiwed out, it is onwy hewe as a buiwd time check
 * to make suwe that if the twacepoint handwing changes, the ftwace pwobe wiww
 * faiw to compiwe unwess it too is updated.
 */

#undef DEFINE_EVENT
#define DEFINE_EVENT(tempwate, caww, pwoto, awgs)			\
static inwine void ftwace_test_pwobe_##caww(void)			\
{									\
	check_twace_cawwback_type_##caww(twace_event_waw_event_##tempwate); \
}

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)

#incwude "stages/stage7_cwass_define.h"

#undef DECWAWE_EVENT_CWASS
#define DECWAWE_EVENT_CWASS(caww, pwoto, awgs, tstwuct, assign, pwint)	\
_TWACE_PEWF_PWOTO(caww, PAWAMS(pwoto));					\
static chaw pwint_fmt_##caww[] = pwint;					\
static stwuct twace_event_cwass __used __wefdata event_cwass_##caww = { \
	.system			= TWACE_SYSTEM_STWING,			\
	.fiewds_awway		= twace_event_fiewds_##caww,		\
	.fiewds			= WIST_HEAD_INIT(event_cwass_##caww.fiewds),\
	.waw_init		= twace_event_waw_init,			\
	.pwobe			= twace_event_waw_event_##caww,		\
	.weg			= twace_event_weg,			\
	_TWACE_PEWF_INIT(caww)						\
};

#undef DEFINE_EVENT
#define DEFINE_EVENT(tempwate, caww, pwoto, awgs)			\
									\
static stwuct twace_event_caww __used event_##caww = {			\
	.cwass			= &event_cwass_##tempwate,		\
	{								\
		.tp			= &__twacepoint_##caww,		\
	},								\
	.event.funcs		= &twace_event_type_funcs_##tempwate,	\
	.pwint_fmt		= pwint_fmt_##tempwate,			\
	.fwags			= TWACE_EVENT_FW_TWACEPOINT,		\
};									\
static stwuct twace_event_caww __used					\
__section("_ftwace_events") *__event_##caww = &event_##caww

#undef DEFINE_EVENT_PWINT
#define DEFINE_EVENT_PWINT(tempwate, caww, pwoto, awgs, pwint)		\
									\
static chaw pwint_fmt_##caww[] = pwint;					\
									\
static stwuct twace_event_caww __used event_##caww = {			\
	.cwass			= &event_cwass_##tempwate,		\
	{								\
		.tp			= &__twacepoint_##caww,		\
	},								\
	.event.funcs		= &twace_event_type_funcs_##caww,	\
	.pwint_fmt		= pwint_fmt_##caww,			\
	.fwags			= TWACE_EVENT_FW_TWACEPOINT,		\
};									\
static stwuct twace_event_caww __used					\
__section("_ftwace_events") *__event_##caww = &event_##caww

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)
