/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(_TWACE_VGIC_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_VGIC_H

#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM kvm

TWACE_EVENT(vgic_update_iwq_pending,
	TP_PWOTO(unsigned wong vcpu_id, __u32 iwq, boow wevew),
	TP_AWGS(vcpu_id, iwq, wevew),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong,	vcpu_id	)
		__fiewd(	__u32,		iwq	)
		__fiewd(	boow,		wevew	)
	),

	TP_fast_assign(
		__entwy->vcpu_id	= vcpu_id;
		__entwy->iwq		= iwq;
		__entwy->wevew		= wevew;
	),

	TP_pwintk("VCPU: %wd, IWQ %d, wevew: %d",
		  __entwy->vcpu_id, __entwy->iwq, __entwy->wevew)
);

#endif /* _TWACE_VGIC_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../awch/awm64/kvm/vgic
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
