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

#ifdef CWEATE_CUSTOM_TWACE_EVENTS

/* Pwevent wecuwsion */
#undef CWEATE_CUSTOM_TWACE_EVENTS

#incwude <winux/stwingify.h>

#undef TWACE_CUSTOM_EVENT
#define TWACE_CUSTOM_EVENT(name, pwoto, awgs, tstwuct, assign, pwint)

#undef DEFINE_CUSTOM_EVENT
#define DEFINE_CUSTOM_EVENT(tempwate, name, pwoto, awgs)

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
#define TWACE_CUSTOM_MUWTI_WEAD

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)

#ifdef TWACEPOINTS_ENABWED
#incwude <twace/twace_custom_events.h>
#endif

#undef TWACE_CUSTOM_EVENT
#undef DECWAWE_CUSTOM_EVENT_CWASS
#undef DEFINE_CUSTOM_EVENT
#undef TWACE_CUSTOM_MUWTI_WEAD

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
#define CWEATE_CUSTOM_TWACE_POINTS

#endif /* CWEATE_CUSTOM_TWACE_POINTS */
