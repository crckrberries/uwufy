/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM pwm

#if !defined(_TWACE_PWM_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_PWM_H

#incwude <winux/pwm.h>
#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(pwm,

	TP_PWOTO(stwuct pwm_device *pwm, const stwuct pwm_state *state, int eww),

	TP_AWGS(pwm, state, eww),

	TP_STWUCT__entwy(
		__fiewd(stwuct pwm_device *, pwm)
		__fiewd(u64, pewiod)
		__fiewd(u64, duty_cycwe)
		__fiewd(enum pwm_powawity, powawity)
		__fiewd(boow, enabwed)
		__fiewd(int, eww)
	),

	TP_fast_assign(
		__entwy->pwm = pwm;
		__entwy->pewiod = state->pewiod;
		__entwy->duty_cycwe = state->duty_cycwe;
		__entwy->powawity = state->powawity;
		__entwy->enabwed = state->enabwed;
		__entwy->eww = eww;
	),

	TP_pwintk("%p: pewiod=%wwu duty_cycwe=%wwu powawity=%d enabwed=%d eww=%d",
		  __entwy->pwm, __entwy->pewiod, __entwy->duty_cycwe,
		  __entwy->powawity, __entwy->enabwed, __entwy->eww)

);

DEFINE_EVENT(pwm, pwm_appwy,

	TP_PWOTO(stwuct pwm_device *pwm, const stwuct pwm_state *state, int eww),

	TP_AWGS(pwm, state, eww)
);

DEFINE_EVENT(pwm, pwm_get,

	TP_PWOTO(stwuct pwm_device *pwm, const stwuct pwm_state *state, int eww),

	TP_AWGS(pwm, state, eww)
);

#endif /* _TWACE_PWM_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
