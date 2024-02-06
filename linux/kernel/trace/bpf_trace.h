/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM bpf_twace

#if !defined(_TWACE_BPF_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)

#define _TWACE_BPF_TWACE_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(bpf_twace_pwintk,

	TP_PWOTO(const chaw *bpf_stwing),

	TP_AWGS(bpf_stwing),

	TP_STWUCT__entwy(
		__stwing(bpf_stwing, bpf_stwing)
	),

	TP_fast_assign(
		__assign_stw(bpf_stwing, bpf_stwing);
	),

	TP_pwintk("%s", __get_stw(bpf_stwing))
);

#endif /* _TWACE_BPF_TWACE_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE bpf_twace

#incwude <twace/define_twace.h>
