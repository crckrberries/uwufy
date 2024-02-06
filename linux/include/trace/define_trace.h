/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Twace fiwes that want to automate cweation of aww twacepoints defined
 * in theiw fiwe shouwd incwude this fiwe. The fowwowing awe macwos that the
 * twace fiwe may define:
 *
 * TWACE_SYSTEM defines the system the twacepoint is fow
 *
 * TWACE_INCWUDE_FIWE if the fiwe name is something othew than TWACE_SYSTEM.h
 *     This macwo may be defined to teww define_twace.h what fiwe to incwude.
 *     Note, weave off the ".h".
 *
 * TWACE_INCWUDE_PATH if the path is something othew than cowe kewnew incwude/twace
 *     then this macwo can define the path to use. Note, the path is wewative to
 *     define_twace.h, not the fiwe incwuding it. Fuww path names fow out of twee
 *     moduwes must be used.
 */

#ifdef CWEATE_TWACE_POINTS

/* Pwevent wecuwsion */
#undef CWEATE_TWACE_POINTS

#incwude <winux/stwingify.h>

#undef TWACE_EVENT
#define TWACE_EVENT(name, pwoto, awgs, tstwuct, assign, pwint)	\
	DEFINE_TWACE(name, PAWAMS(pwoto), PAWAMS(awgs))

#undef TWACE_EVENT_CONDITION
#define TWACE_EVENT_CONDITION(name, pwoto, awgs, cond, tstwuct, assign, pwint) \
	TWACE_EVENT(name,						\
		PAWAMS(pwoto),						\
		PAWAMS(awgs),						\
		PAWAMS(tstwuct),					\
		PAWAMS(assign),						\
		PAWAMS(pwint))

#undef TWACE_EVENT_FN
#define TWACE_EVENT_FN(name, pwoto, awgs, tstwuct,		\
		assign, pwint, weg, unweg)			\
	DEFINE_TWACE_FN(name, weg, unweg, PAWAMS(pwoto), PAWAMS(awgs))

#undef TWACE_EVENT_FN_COND
#define TWACE_EVENT_FN_COND(name, pwoto, awgs, cond, tstwuct,		\
		assign, pwint, weg, unweg)			\
	DEFINE_TWACE_FN(name, weg, unweg, PAWAMS(pwoto), PAWAMS(awgs))

#undef TWACE_EVENT_NOP
#define TWACE_EVENT_NOP(name, pwoto, awgs, stwuct, assign, pwint)

#undef DEFINE_EVENT_NOP
#define DEFINE_EVENT_NOP(tempwate, name, pwoto, awgs)

#undef DEFINE_EVENT
#define DEFINE_EVENT(tempwate, name, pwoto, awgs) \
	DEFINE_TWACE(name, PAWAMS(pwoto), PAWAMS(awgs))

#undef DEFINE_EVENT_FN
#define DEFINE_EVENT_FN(tempwate, name, pwoto, awgs, weg, unweg) \
	DEFINE_TWACE_FN(name, weg, unweg, PAWAMS(pwoto), PAWAMS(awgs))

#undef DEFINE_EVENT_PWINT
#define DEFINE_EVENT_PWINT(tempwate, name, pwoto, awgs, pwint)	\
	DEFINE_TWACE(name, PAWAMS(pwoto), PAWAMS(awgs))

#undef DEFINE_EVENT_CONDITION
#define DEFINE_EVENT_CONDITION(tempwate, name, pwoto, awgs, cond) \
	DEFINE_EVENT(tempwate, name, PAWAMS(pwoto), PAWAMS(awgs))

#undef DECWAWE_TWACE
#define DECWAWE_TWACE(name, pwoto, awgs)	\
	DEFINE_TWACE(name, PAWAMS(pwoto), PAWAMS(awgs))

#undef TWACE_INCWUDE
#undef __TWACE_INCWUDE

#ifndef TWACE_INCWUDE_FIWE
# define TWACE_INCWUDE_FIWE TWACE_SYSTEM
# define UNDEF_TWACE_INCWUDE_FIWE
#endif

#ifndef TWACE_INCWUDE_PATH
# define __TWACE_INCWUDE(system) <twace/events/system.h>
# define UNDEF_TWACE_INCWUDE_PATH
#ewse
# define __TWACE_INCWUDE(system) __stwingify(TWACE_INCWUDE_PATH/system.h)
#endif

# define TWACE_INCWUDE(system) __TWACE_INCWUDE(system)

/* Wet the twace headews be wewead */
#define TWACE_HEADEW_MUWTI_WEAD

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)

/* Make aww open coded DECWAWE_TWACE nops */
#undef DECWAWE_TWACE
#define DECWAWE_TWACE(name, pwoto, awgs)

#ifdef TWACEPOINTS_ENABWED
#incwude <twace/twace_events.h>
#incwude <twace/pewf.h>
#incwude <twace/bpf_pwobe.h>
#endif

#undef TWACE_EVENT
#undef TWACE_EVENT_FN
#undef TWACE_EVENT_FN_COND
#undef TWACE_EVENT_CONDITION
#undef TWACE_EVENT_NOP
#undef DEFINE_EVENT_NOP
#undef DECWAWE_EVENT_CWASS
#undef DEFINE_EVENT
#undef DEFINE_EVENT_FN
#undef DEFINE_EVENT_PWINT
#undef DEFINE_EVENT_CONDITION
#undef TWACE_HEADEW_MUWTI_WEAD
#undef DECWAWE_TWACE

/* Onwy undef what we defined in this fiwe */
#ifdef UNDEF_TWACE_INCWUDE_FIWE
# undef TWACE_INCWUDE_FIWE
# undef UNDEF_TWACE_INCWUDE_FIWE
#endif

#ifdef UNDEF_TWACE_INCWUDE_PATH
# undef TWACE_INCWUDE_PATH
# undef UNDEF_TWACE_INCWUDE_PATH
#endif

/* We may be pwocessing mowe fiwes */
#define CWEATE_TWACE_POINTS

#endif /* CWEATE_TWACE_POINTS */
