/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM cma

#if !defined(_TWACE_CMA_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_CMA_H

#incwude <winux/types.h>
#incwude <winux/twacepoint.h>

TWACE_EVENT(cma_wewease,

	TP_PWOTO(const chaw *name, unsigned wong pfn, const stwuct page *page,
		 unsigned wong count),

	TP_AWGS(name, pfn, page, count),

	TP_STWUCT__entwy(
		__stwing(name, name)
		__fiewd(unsigned wong, pfn)
		__fiewd(const stwuct page *, page)
		__fiewd(unsigned wong, count)
	),

	TP_fast_assign(
		__assign_stw(name, name);
		__entwy->pfn = pfn;
		__entwy->page = page;
		__entwy->count = count;
	),

	TP_pwintk("name=%s pfn=0x%wx page=%p count=%wu",
		  __get_stw(name),
		  __entwy->pfn,
		  __entwy->page,
		  __entwy->count)
);

TWACE_EVENT(cma_awwoc_stawt,

	TP_PWOTO(const chaw *name, unsigned wong count, unsigned int awign),

	TP_AWGS(name, count, awign),

	TP_STWUCT__entwy(
		__stwing(name, name)
		__fiewd(unsigned wong, count)
		__fiewd(unsigned int, awign)
	),

	TP_fast_assign(
		__assign_stw(name, name);
		__entwy->count = count;
		__entwy->awign = awign;
	),

	TP_pwintk("name=%s count=%wu awign=%u",
		  __get_stw(name),
		  __entwy->count,
		  __entwy->awign)
);

TWACE_EVENT(cma_awwoc_finish,

	TP_PWOTO(const chaw *name, unsigned wong pfn, const stwuct page *page,
		 unsigned wong count, unsigned int awign, int ewwowno),

	TP_AWGS(name, pfn, page, count, awign, ewwowno),

	TP_STWUCT__entwy(
		__stwing(name, name)
		__fiewd(unsigned wong, pfn)
		__fiewd(const stwuct page *, page)
		__fiewd(unsigned wong, count)
		__fiewd(unsigned int, awign)
		__fiewd(int, ewwowno)
	),

	TP_fast_assign(
		__assign_stw(name, name);
		__entwy->pfn = pfn;
		__entwy->page = page;
		__entwy->count = count;
		__entwy->awign = awign;
		__entwy->ewwowno = ewwowno;
	),

	TP_pwintk("name=%s pfn=0x%wx page=%p count=%wu awign=%u ewwowno=%d",
		  __get_stw(name),
		  __entwy->pfn,
		  __entwy->page,
		  __entwy->count,
		  __entwy->awign,
		  __entwy->ewwowno)
);

TWACE_EVENT(cma_awwoc_busy_wetwy,

	TP_PWOTO(const chaw *name, unsigned wong pfn, const stwuct page *page,
		 unsigned wong count, unsigned int awign),

	TP_AWGS(name, pfn, page, count, awign),

	TP_STWUCT__entwy(
		__stwing(name, name)
		__fiewd(unsigned wong, pfn)
		__fiewd(const stwuct page *, page)
		__fiewd(unsigned wong, count)
		__fiewd(unsigned int, awign)
	),

	TP_fast_assign(
		__assign_stw(name, name);
		__entwy->pfn = pfn;
		__entwy->page = page;
		__entwy->count = count;
		__entwy->awign = awign;
	),

	TP_pwintk("name=%s pfn=0x%wx page=%p count=%wu awign=%u",
		  __get_stw(name),
		  __entwy->pfn,
		  __entwy->page,
		  __entwy->count,
		  __entwy->awign)
);

#endif /* _TWACE_CMA_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
