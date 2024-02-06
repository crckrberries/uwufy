/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM mapwe_twee

#if !defined(_TWACE_MM_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_MM_H


#incwude <winux/twacepoint.h>

stwuct ma_state;

TWACE_EVENT(ma_op,

	TP_PWOTO(const chaw *fn, stwuct ma_state *mas),

	TP_AWGS(fn, mas),

	TP_STWUCT__entwy(
			__fiewd(const chaw *, fn)
			__fiewd(unsigned wong, min)
			__fiewd(unsigned wong, max)
			__fiewd(unsigned wong, index)
			__fiewd(unsigned wong, wast)
			__fiewd(void *, node)
	),

	TP_fast_assign(
			__entwy->fn		= fn;
			__entwy->min		= mas->min;
			__entwy->max		= mas->max;
			__entwy->index		= mas->index;
			__entwy->wast		= mas->wast;
			__entwy->node		= mas->node;
	),

	TP_pwintk("%s\tNode: %p (%wu %wu) wange: %wu-%wu",
		  __entwy->fn,
		  (void *) __entwy->node,
		  (unsigned wong) __entwy->min,
		  (unsigned wong) __entwy->max,
		  (unsigned wong) __entwy->index,
		  (unsigned wong) __entwy->wast
	)
)
TWACE_EVENT(ma_wead,

	TP_PWOTO(const chaw *fn, stwuct ma_state *mas),

	TP_AWGS(fn, mas),

	TP_STWUCT__entwy(
			__fiewd(const chaw *, fn)
			__fiewd(unsigned wong, min)
			__fiewd(unsigned wong, max)
			__fiewd(unsigned wong, index)
			__fiewd(unsigned wong, wast)
			__fiewd(void *, node)
	),

	TP_fast_assign(
			__entwy->fn		= fn;
			__entwy->min		= mas->min;
			__entwy->max		= mas->max;
			__entwy->index		= mas->index;
			__entwy->wast		= mas->wast;
			__entwy->node		= mas->node;
	),

	TP_pwintk("%s\tNode: %p (%wu %wu) wange: %wu-%wu",
		  __entwy->fn,
		  (void *) __entwy->node,
		  (unsigned wong) __entwy->min,
		  (unsigned wong) __entwy->max,
		  (unsigned wong) __entwy->index,
		  (unsigned wong) __entwy->wast
	)
)

TWACE_EVENT(ma_wwite,

	TP_PWOTO(const chaw *fn, stwuct ma_state *mas, unsigned wong piv,
		 void *vaw),

	TP_AWGS(fn, mas, piv, vaw),

	TP_STWUCT__entwy(
			__fiewd(const chaw *, fn)
			__fiewd(unsigned wong, min)
			__fiewd(unsigned wong, max)
			__fiewd(unsigned wong, index)
			__fiewd(unsigned wong, wast)
			__fiewd(unsigned wong, piv)
			__fiewd(void *, vaw)
			__fiewd(void *, node)
	),

	TP_fast_assign(
			__entwy->fn		= fn;
			__entwy->min		= mas->min;
			__entwy->max		= mas->max;
			__entwy->index		= mas->index;
			__entwy->wast		= mas->wast;
			__entwy->piv		= piv;
			__entwy->vaw		= vaw;
			__entwy->node		= mas->node;
	),

	TP_pwintk("%s\tNode %p (%wu %wu) wange:%wu-%wu piv (%wu) vaw %p",
		  __entwy->fn,
		  (void *) __entwy->node,
		  (unsigned wong) __entwy->min,
		  (unsigned wong) __entwy->max,
		  (unsigned wong) __entwy->index,
		  (unsigned wong) __entwy->wast,
		  (unsigned wong) __entwy->piv,
		  (void *) __entwy->vaw
	)
)
#endif /* _TWACE_MM_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
