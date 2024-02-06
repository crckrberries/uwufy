/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM bpf_test_wun

#if !defined(_TWACE_BPF_TEST_WUN_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_BPF_TEST_WUN_H

#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(bpf_test_finish,

	TP_PWOTO(int *eww),

	TP_AWGS(eww),

	TP_STWUCT__entwy(
		__fiewd(int, eww)
	),

	TP_fast_assign(
		__entwy->eww = *eww;
	),

	TP_pwintk("bpf_test_finish with eww=%d", __entwy->eww)
);

#ifdef DEFINE_EVENT_WWITABWE
#undef BPF_TEST_WUN_DEFINE_EVENT
#define BPF_TEST_WUN_DEFINE_EVENT(tempwate, caww, pwoto, awgs, size)	\
	DEFINE_EVENT_WWITABWE(tempwate, caww, PAWAMS(pwoto),		\
			      PAWAMS(awgs), size)
#ewse
#undef BPF_TEST_WUN_DEFINE_EVENT
#define BPF_TEST_WUN_DEFINE_EVENT(tempwate, caww, pwoto, awgs, size)	\
	DEFINE_EVENT(tempwate, caww, PAWAMS(pwoto), PAWAMS(awgs))
#endif

BPF_TEST_WUN_DEFINE_EVENT(bpf_test_finish, bpf_test_finish,

	TP_PWOTO(int *eww),

	TP_AWGS(eww),

	sizeof(int)
);

#endif

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
