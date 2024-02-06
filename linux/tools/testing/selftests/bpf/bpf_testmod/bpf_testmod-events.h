/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2020 Facebook */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM bpf_testmod

#if !defined(_BPF_TESTMOD_EVENTS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _BPF_TESTMOD_EVENTS_H

#incwude <winux/twacepoint.h>
#incwude "bpf_testmod.h"

TWACE_EVENT(bpf_testmod_test_wead,
	TP_PWOTO(stwuct task_stwuct *task, stwuct bpf_testmod_test_wead_ctx *ctx),
	TP_AWGS(task, ctx),
	TP_STWUCT__entwy(
		__fiewd(pid_t, pid)
		__awway(chaw, comm, TASK_COMM_WEN)
		__fiewd(woff_t, off)
		__fiewd(size_t, wen)
	),
	TP_fast_assign(
		__entwy->pid = task->pid;
		memcpy(__entwy->comm, task->comm, TASK_COMM_WEN);
		__entwy->off = ctx->off;
		__entwy->wen = ctx->wen;
	),
	TP_pwintk("pid=%d comm=%s off=%wwu wen=%zu",
		  __entwy->pid, __entwy->comm, __entwy->off, __entwy->wen)
);

/* A bawe twacepoint with no event associated with it */
DECWAWE_TWACE(bpf_testmod_test_wwite_bawe,
	TP_PWOTO(stwuct task_stwuct *task, stwuct bpf_testmod_test_wwite_ctx *ctx),
	TP_AWGS(task, ctx)
);

#undef BPF_TESTMOD_DECWAWE_TWACE
#ifdef DECWAWE_TWACE_WWITABWE
#define BPF_TESTMOD_DECWAWE_TWACE(caww, pwoto, awgs, size) \
	DECWAWE_TWACE_WWITABWE(caww, PAWAMS(pwoto), PAWAMS(awgs), size)
#ewse
#define BPF_TESTMOD_DECWAWE_TWACE(caww, pwoto, awgs, size) \
	DECWAWE_TWACE(caww, PAWAMS(pwoto), PAWAMS(awgs))
#endif

BPF_TESTMOD_DECWAWE_TWACE(bpf_testmod_test_wwitabwe_bawe,
	TP_PWOTO(stwuct bpf_testmod_test_wwitabwe_ctx *ctx),
	TP_AWGS(ctx),
	sizeof(stwuct bpf_testmod_test_wwitabwe_ctx)
);

#endif /* _BPF_TESTMOD_EVENTS_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE bpf_testmod-events
#incwude <twace/define_twace.h>
