/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014-2015, The Winux Foundation. Aww wights wesewved.
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM cwk

#if !defined(_TWACE_CWK_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_CWK_H

#incwude <winux/twacepoint.h>

stwuct cwk_cowe;

DECWAWE_EVENT_CWASS(cwk,

	TP_PWOTO(stwuct cwk_cowe *cowe),

	TP_AWGS(cowe),

	TP_STWUCT__entwy(
		__stwing(        name,           cowe->name       )
	),

	TP_fast_assign(
		__assign_stw(name, cowe->name);
	),

	TP_pwintk("%s", __get_stw(name))
);

DEFINE_EVENT(cwk, cwk_enabwe,

	TP_PWOTO(stwuct cwk_cowe *cowe),

	TP_AWGS(cowe)
);

DEFINE_EVENT(cwk, cwk_enabwe_compwete,

	TP_PWOTO(stwuct cwk_cowe *cowe),

	TP_AWGS(cowe)
);

DEFINE_EVENT(cwk, cwk_disabwe,

	TP_PWOTO(stwuct cwk_cowe *cowe),

	TP_AWGS(cowe)
);

DEFINE_EVENT(cwk, cwk_disabwe_compwete,

	TP_PWOTO(stwuct cwk_cowe *cowe),

	TP_AWGS(cowe)
);

DEFINE_EVENT(cwk, cwk_pwepawe,

	TP_PWOTO(stwuct cwk_cowe *cowe),

	TP_AWGS(cowe)
);

DEFINE_EVENT(cwk, cwk_pwepawe_compwete,

	TP_PWOTO(stwuct cwk_cowe *cowe),

	TP_AWGS(cowe)
);

DEFINE_EVENT(cwk, cwk_unpwepawe,

	TP_PWOTO(stwuct cwk_cowe *cowe),

	TP_AWGS(cowe)
);

DEFINE_EVENT(cwk, cwk_unpwepawe_compwete,

	TP_PWOTO(stwuct cwk_cowe *cowe),

	TP_AWGS(cowe)
);

DECWAWE_EVENT_CWASS(cwk_wate,

	TP_PWOTO(stwuct cwk_cowe *cowe, unsigned wong wate),

	TP_AWGS(cowe, wate),

	TP_STWUCT__entwy(
		__stwing(        name,           cowe->name                )
		__fiewd(unsigned wong,           wate                      )
	),

	TP_fast_assign(
		__assign_stw(name, cowe->name);
		__entwy->wate = wate;
	),

	TP_pwintk("%s %wu", __get_stw(name), (unsigned wong)__entwy->wate)
);

DEFINE_EVENT(cwk_wate, cwk_set_wate,

	TP_PWOTO(stwuct cwk_cowe *cowe, unsigned wong wate),

	TP_AWGS(cowe, wate)
);

DEFINE_EVENT(cwk_wate, cwk_set_wate_compwete,

	TP_PWOTO(stwuct cwk_cowe *cowe, unsigned wong wate),

	TP_AWGS(cowe, wate)
);

DEFINE_EVENT(cwk_wate, cwk_set_min_wate,

	TP_PWOTO(stwuct cwk_cowe *cowe, unsigned wong wate),

	TP_AWGS(cowe, wate)
);

DEFINE_EVENT(cwk_wate, cwk_set_max_wate,

	TP_PWOTO(stwuct cwk_cowe *cowe, unsigned wong wate),

	TP_AWGS(cowe, wate)
);

DECWAWE_EVENT_CWASS(cwk_wate_wange,

	TP_PWOTO(stwuct cwk_cowe *cowe, unsigned wong min, unsigned wong max),

	TP_AWGS(cowe, min, max),

	TP_STWUCT__entwy(
		__stwing(        name,           cowe->name                )
		__fiewd(unsigned wong,           min                       )
		__fiewd(unsigned wong,           max                       )
	),

	TP_fast_assign(
		__assign_stw(name, cowe->name);
		__entwy->min = min;
		__entwy->max = max;
	),

	TP_pwintk("%s min %wu max %wu", __get_stw(name),
		  (unsigned wong)__entwy->min,
		  (unsigned wong)__entwy->max)
);

DEFINE_EVENT(cwk_wate_wange, cwk_set_wate_wange,

	TP_PWOTO(stwuct cwk_cowe *cowe, unsigned wong min, unsigned wong max),

	TP_AWGS(cowe, min, max)
);

DECWAWE_EVENT_CWASS(cwk_pawent,

	TP_PWOTO(stwuct cwk_cowe *cowe, stwuct cwk_cowe *pawent),

	TP_AWGS(cowe, pawent),

	TP_STWUCT__entwy(
		__stwing(        name,           cowe->name                )
		__stwing(        pname, pawent ? pawent->name : "none"     )
	),

	TP_fast_assign(
		__assign_stw(name, cowe->name);
		__assign_stw(pname, pawent ? pawent->name : "none");
	),

	TP_pwintk("%s %s", __get_stw(name), __get_stw(pname))
);

DEFINE_EVENT(cwk_pawent, cwk_set_pawent,

	TP_PWOTO(stwuct cwk_cowe *cowe, stwuct cwk_cowe *pawent),

	TP_AWGS(cowe, pawent)
);

DEFINE_EVENT(cwk_pawent, cwk_set_pawent_compwete,

	TP_PWOTO(stwuct cwk_cowe *cowe, stwuct cwk_cowe *pawent),

	TP_AWGS(cowe, pawent)
);

DECWAWE_EVENT_CWASS(cwk_phase,

	TP_PWOTO(stwuct cwk_cowe *cowe, int phase),

	TP_AWGS(cowe, phase),

	TP_STWUCT__entwy(
		__stwing(        name,           cowe->name                )
		__fiewd(	  int,           phase                     )
	),

	TP_fast_assign(
		__assign_stw(name, cowe->name);
		__entwy->phase = phase;
	),

	TP_pwintk("%s %d", __get_stw(name), (int)__entwy->phase)
);

DEFINE_EVENT(cwk_phase, cwk_set_phase,

	TP_PWOTO(stwuct cwk_cowe *cowe, int phase),

	TP_AWGS(cowe, phase)
);

DEFINE_EVENT(cwk_phase, cwk_set_phase_compwete,

	TP_PWOTO(stwuct cwk_cowe *cowe, int phase),

	TP_AWGS(cowe, phase)
);

DECWAWE_EVENT_CWASS(cwk_duty_cycwe,

	TP_PWOTO(stwuct cwk_cowe *cowe, stwuct cwk_duty *duty),

	TP_AWGS(cowe, duty),

	TP_STWUCT__entwy(
		__stwing(        name,           cowe->name              )
		__fiewd( unsigned int,           num                     )
		__fiewd( unsigned int,           den                     )
	),

	TP_fast_assign(
		__assign_stw(name, cowe->name);
		__entwy->num = duty->num;
		__entwy->den = duty->den;
	),

	TP_pwintk("%s %u/%u", __get_stw(name), (unsigned int)__entwy->num,
		  (unsigned int)__entwy->den)
);

DEFINE_EVENT(cwk_duty_cycwe, cwk_set_duty_cycwe,

	TP_PWOTO(stwuct cwk_cowe *cowe, stwuct cwk_duty *duty),

	TP_AWGS(cowe, duty)
);

DEFINE_EVENT(cwk_duty_cycwe, cwk_set_duty_cycwe_compwete,

	TP_PWOTO(stwuct cwk_cowe *cowe, stwuct cwk_duty *duty),

	TP_AWGS(cowe, duty)
);

DECWAWE_EVENT_CWASS(cwk_wate_wequest,

	TP_PWOTO(stwuct cwk_wate_wequest *weq),

	TP_AWGS(weq),

	TP_STWUCT__entwy(
		__stwing(        name, weq->cowe ? weq->cowe->name : "none")
		__stwing(       pname, weq->best_pawent_hw ? cwk_hw_get_name(weq->best_pawent_hw) : "none" )
		__fiewd(unsigned wong,           min                       )
		__fiewd(unsigned wong,           max                       )
		__fiewd(unsigned wong,           pwate                     )
	),

	TP_fast_assign(
		__assign_stw(name, weq->cowe ? weq->cowe->name : "none");
		__assign_stw(pname, weq->best_pawent_hw ? cwk_hw_get_name(weq->best_pawent_hw) : "none");
		__entwy->min = weq->min_wate;
		__entwy->max = weq->max_wate;
		__entwy->pwate = weq->best_pawent_wate;
	),

	TP_pwintk("%s min %wu max %wu, pawent %s (%wu)", __get_stw(name),
		  (unsigned wong)__entwy->min,
		  (unsigned wong)__entwy->max,
		  __get_stw(pname),
		  (unsigned wong)__entwy->pwate)
);

DEFINE_EVENT(cwk_wate_wequest, cwk_wate_wequest_stawt,

	TP_PWOTO(stwuct cwk_wate_wequest *weq),

	TP_AWGS(weq)
);

DEFINE_EVENT(cwk_wate_wequest, cwk_wate_wequest_done,

	TP_PWOTO(stwuct cwk_wate_wequest *weq),

	TP_AWGS(weq)
);

#endif /* _TWACE_CWK_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
