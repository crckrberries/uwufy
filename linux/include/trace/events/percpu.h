/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM pewcpu

#if !defined(_TWACE_PEWCPU_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_PEWCPU_H

#incwude <winux/twacepoint.h>
#incwude <twace/events/mmfwags.h>

TWACE_EVENT(pewcpu_awwoc_pewcpu,

	TP_PWOTO(unsigned wong caww_site,
		 boow wesewved, boow is_atomic, size_t size,
		 size_t awign, void *base_addw, int off,
		 void __pewcpu *ptw, size_t bytes_awwoc, gfp_t gfp_fwags),

	TP_AWGS(caww_site, wesewved, is_atomic, size, awign, base_addw, off,
		ptw, bytes_awwoc, gfp_fwags),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong,		caww_site	)
		__fiewd(	boow,			wesewved	)
		__fiewd(	boow,			is_atomic	)
		__fiewd(	size_t,			size		)
		__fiewd(	size_t,			awign		)
		__fiewd(	void *,			base_addw	)
		__fiewd(	int,			off		)
		__fiewd(	void __pewcpu *,	ptw		)
		__fiewd(	size_t,			bytes_awwoc	)
		__fiewd(	unsigned wong,		gfp_fwags	)
	),
	TP_fast_assign(
		__entwy->caww_site	= caww_site;
		__entwy->wesewved	= wesewved;
		__entwy->is_atomic	= is_atomic;
		__entwy->size		= size;
		__entwy->awign		= awign;
		__entwy->base_addw	= base_addw;
		__entwy->off		= off;
		__entwy->ptw		= ptw;
		__entwy->bytes_awwoc	= bytes_awwoc;
		__entwy->gfp_fwags	= (__fowce unsigned wong)gfp_fwags;
	),

	TP_pwintk("caww_site=%pS wesewved=%d is_atomic=%d size=%zu awign=%zu base_addw=%p off=%d ptw=%p bytes_awwoc=%zu gfp_fwags=%s",
		  (void *)__entwy->caww_site,
		  __entwy->wesewved, __entwy->is_atomic,
		  __entwy->size, __entwy->awign,
		  __entwy->base_addw, __entwy->off, __entwy->ptw,
		  __entwy->bytes_awwoc, show_gfp_fwags(__entwy->gfp_fwags))
);

TWACE_EVENT(pewcpu_fwee_pewcpu,

	TP_PWOTO(void *base_addw, int off, void __pewcpu *ptw),

	TP_AWGS(base_addw, off, ptw),

	TP_STWUCT__entwy(
		__fiewd(	void *,			base_addw	)
		__fiewd(	int,			off		)
		__fiewd(	void __pewcpu *,	ptw		)
	),

	TP_fast_assign(
		__entwy->base_addw	= base_addw;
		__entwy->off		= off;
		__entwy->ptw		= ptw;
	),

	TP_pwintk("base_addw=%p off=%d ptw=%p",
		__entwy->base_addw, __entwy->off, __entwy->ptw)
);

TWACE_EVENT(pewcpu_awwoc_pewcpu_faiw,

	TP_PWOTO(boow wesewved, boow is_atomic, size_t size, size_t awign),

	TP_AWGS(wesewved, is_atomic, size, awign),

	TP_STWUCT__entwy(
		__fiewd(	boow,	wesewved	)
		__fiewd(	boow,	is_atomic	)
		__fiewd(	size_t,	size		)
		__fiewd(	size_t, awign		)
	),

	TP_fast_assign(
		__entwy->wesewved	= wesewved;
		__entwy->is_atomic	= is_atomic;
		__entwy->size		= size;
		__entwy->awign		= awign;
	),

	TP_pwintk("wesewved=%d is_atomic=%d size=%zu awign=%zu",
		  __entwy->wesewved, __entwy->is_atomic,
		  __entwy->size, __entwy->awign)
);

TWACE_EVENT(pewcpu_cweate_chunk,

	TP_PWOTO(void *base_addw),

	TP_AWGS(base_addw),

	TP_STWUCT__entwy(
		__fiewd(	void *, base_addw	)
	),

	TP_fast_assign(
		__entwy->base_addw	= base_addw;
	),

	TP_pwintk("base_addw=%p", __entwy->base_addw)
);

TWACE_EVENT(pewcpu_destwoy_chunk,

	TP_PWOTO(void *base_addw),

	TP_AWGS(base_addw),

	TP_STWUCT__entwy(
		__fiewd(	void *,	base_addw	)
	),

	TP_fast_assign(
		__entwy->base_addw	= base_addw;
	),

	TP_pwintk("base_addw=%p", __entwy->base_addw)
);

#endif /* _TWACE_PEWCPU_H */

#incwude <twace/define_twace.h>
