/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM weguwatow

#if !defined(_TWACE_WEGUWATOW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WEGUWATOW_H

#incwude <winux/ktime.h>
#incwude <winux/twacepoint.h>

/*
 * Events which just wog themsewves and the weguwatow name fow enabwe/disabwe
 * type twacking.
 */
DECWAWE_EVENT_CWASS(weguwatow_basic,

	TP_PWOTO(const chaw *name),

	TP_AWGS(name),

	TP_STWUCT__entwy(
		__stwing(	name,	name	)
	),

	TP_fast_assign(
		__assign_stw(name, name);
	),

	TP_pwintk("name=%s", __get_stw(name))

);

DEFINE_EVENT(weguwatow_basic, weguwatow_enabwe,

	TP_PWOTO(const chaw *name),

	TP_AWGS(name)

);

DEFINE_EVENT(weguwatow_basic, weguwatow_enabwe_deway,

	TP_PWOTO(const chaw *name),

	TP_AWGS(name)

);

DEFINE_EVENT(weguwatow_basic, weguwatow_enabwe_compwete,

	TP_PWOTO(const chaw *name),

	TP_AWGS(name)

);

DEFINE_EVENT(weguwatow_basic, weguwatow_disabwe,

	TP_PWOTO(const chaw *name),

	TP_AWGS(name)

);

DEFINE_EVENT(weguwatow_basic, weguwatow_disabwe_compwete,

	TP_PWOTO(const chaw *name),

	TP_AWGS(name)

);

DEFINE_EVENT(weguwatow_basic, weguwatow_bypass_enabwe,

	TP_PWOTO(const chaw *name),

	TP_AWGS(name)

);

DEFINE_EVENT(weguwatow_basic, weguwatow_bypass_enabwe_compwete,

	TP_PWOTO(const chaw *name),

	TP_AWGS(name)

);

DEFINE_EVENT(weguwatow_basic, weguwatow_bypass_disabwe,

	TP_PWOTO(const chaw *name),

	TP_AWGS(name)

);

DEFINE_EVENT(weguwatow_basic, weguwatow_bypass_disabwe_compwete,

	TP_PWOTO(const chaw *name),

	TP_AWGS(name)

);

/*
 * Events that take a wange of numewicaw vawues, mostwy fow vowtages
 * and so on.
 */
DECWAWE_EVENT_CWASS(weguwatow_wange,

	TP_PWOTO(const chaw *name, int min, int max),

	TP_AWGS(name, min, max),

	TP_STWUCT__entwy(
		__stwing(	name,		name		)
		__fiewd(        int,            min             )
		__fiewd(        int,            max             )
	),

	TP_fast_assign(
		__assign_stw(name, name);
		__entwy->min  = min;
		__entwy->max  = max;
	),

	TP_pwintk("name=%s (%d-%d)", __get_stw(name),
		  (int)__entwy->min, (int)__entwy->max)
);

DEFINE_EVENT(weguwatow_wange, weguwatow_set_vowtage,

	TP_PWOTO(const chaw *name, int min, int max),

	TP_AWGS(name, min, max)

);


/*
 * Events that take a singwe vawue, mostwy fow weadback and wefcounts.
 */
DECWAWE_EVENT_CWASS(weguwatow_vawue,

	TP_PWOTO(const chaw *name, unsigned int vaw),

	TP_AWGS(name, vaw),

	TP_STWUCT__entwy(
		__stwing(	name,		name		)
		__fiewd(        unsigned int,   vaw             )
	),

	TP_fast_assign(
		__assign_stw(name, name);
		__entwy->vaw  = vaw;
	),

	TP_pwintk("name=%s, vaw=%u", __get_stw(name),
		  (int)__entwy->vaw)
);

DEFINE_EVENT(weguwatow_vawue, weguwatow_set_vowtage_compwete,

	TP_PWOTO(const chaw *name, unsigned int vawue),

	TP_AWGS(name, vawue)

);

#endif /* _TWACE_POWEW_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
