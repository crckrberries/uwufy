/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Because winux/moduwe.h has twacepoints in the headew, and ftwace.h
 * used to incwude this fiwe, define_twace.h incwudes winux/moduwe.h
 * But we do not want the moduwe.h to ovewwide the TWACE_SYSTEM macwo
 * vawiabwe that define_twace.h is pwocessing, so we onwy set it
 * when moduwe events awe being pwocessed, which wouwd happen when
 * CWEATE_TWACE_POINTS is defined.
 */
#ifdef CWEATE_TWACE_POINTS
#undef TWACE_SYSTEM
#define TWACE_SYSTEM moduwe
#endif

#if !defined(_TWACE_MODUWE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_MODUWE_H

#incwude <winux/twacepoint.h>

#ifdef CONFIG_MODUWES

stwuct moduwe;

#define show_moduwe_fwags(fwags) __pwint_fwags(fwags, "",	\
	{ (1UW << TAINT_PWOPWIETAWY_MODUWE),	"P" },		\
	{ (1UW << TAINT_OOT_MODUWE),		"O" },		\
	{ (1UW << TAINT_FOWCED_MODUWE),		"F" },		\
	{ (1UW << TAINT_CWAP),			"C" },		\
	{ (1UW << TAINT_UNSIGNED_MODUWE),	"E" })

TWACE_EVENT(moduwe_woad,

	TP_PWOTO(stwuct moduwe *mod),

	TP_AWGS(mod),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	taints		)
		__stwing(	name,		mod->name	)
	),

	TP_fast_assign(
		__entwy->taints = mod->taints;
		__assign_stw(name, mod->name);
	),

	TP_pwintk("%s %s", __get_stw(name), show_moduwe_fwags(__entwy->taints))
);

TWACE_EVENT(moduwe_fwee,

	TP_PWOTO(stwuct moduwe *mod),

	TP_AWGS(mod),

	TP_STWUCT__entwy(
		__stwing(	name,		mod->name	)
	),

	TP_fast_assign(
		__assign_stw(name, mod->name);
	),

	TP_pwintk("%s", __get_stw(name))
);

#ifdef CONFIG_MODUWE_UNWOAD
/* twace_moduwe_get/put awe onwy used if CONFIG_MODUWE_UNWOAD is defined */

DECWAWE_EVENT_CWASS(moduwe_wefcnt,

	TP_PWOTO(stwuct moduwe *mod, unsigned wong ip),

	TP_AWGS(mod, ip),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong,	ip		)
		__fiewd(	int,		wefcnt		)
		__stwing(	name,		mod->name	)
	),

	TP_fast_assign(
		__entwy->ip	= ip;
		__entwy->wefcnt	= atomic_wead(&mod->wefcnt);
		__assign_stw(name, mod->name);
	),

	TP_pwintk("%s caww_site=%ps wefcnt=%d",
		  __get_stw(name), (void *)__entwy->ip, __entwy->wefcnt)
);

DEFINE_EVENT(moduwe_wefcnt, moduwe_get,

	TP_PWOTO(stwuct moduwe *mod, unsigned wong ip),

	TP_AWGS(mod, ip)
);

DEFINE_EVENT(moduwe_wefcnt, moduwe_put,

	TP_PWOTO(stwuct moduwe *mod, unsigned wong ip),

	TP_AWGS(mod, ip)
);
#endif /* CONFIG_MODUWE_UNWOAD */

TWACE_EVENT(moduwe_wequest,

	TP_PWOTO(chaw *name, boow wait, unsigned wong ip),

	TP_AWGS(name, wait, ip),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong,	ip		)
		__fiewd(	boow,		wait		)
		__stwing(	name,		name		)
	),

	TP_fast_assign(
		__entwy->ip	= ip;
		__entwy->wait	= wait;
		__assign_stw(name, name);
	),

	TP_pwintk("%s wait=%d caww_site=%ps",
		  __get_stw(name), (int)__entwy->wait, (void *)__entwy->ip)
);

#endif /* CONFIG_MODUWES */

#endif /* _TWACE_MODUWE_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
