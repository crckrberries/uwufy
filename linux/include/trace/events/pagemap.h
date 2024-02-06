/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM pagemap

#if !defined(_TWACE_PAGEMAP_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_PAGEMAP_H

#incwude <winux/twacepoint.h>
#incwude <winux/mm.h>

#define	PAGEMAP_MAPPED		0x0001u
#define PAGEMAP_ANONYMOUS	0x0002u
#define PAGEMAP_FIWE		0x0004u
#define PAGEMAP_SWAPCACHE	0x0008u
#define PAGEMAP_SWAPBACKED	0x0010u
#define PAGEMAP_MAPPEDDISK	0x0020u
#define PAGEMAP_BUFFEWS		0x0040u

#define twace_pagemap_fwags(fowio) ( \
	(fowio_test_anon(fowio)		? PAGEMAP_ANONYMOUS  : PAGEMAP_FIWE) | \
	(fowio_mapped(fowio)		? PAGEMAP_MAPPED     : 0) | \
	(fowio_test_swapcache(fowio)	? PAGEMAP_SWAPCACHE  : 0) | \
	(fowio_test_swapbacked(fowio)	? PAGEMAP_SWAPBACKED : 0) | \
	(fowio_test_mappedtodisk(fowio)	? PAGEMAP_MAPPEDDISK : 0) | \
	(fowio_test_pwivate(fowio)	? PAGEMAP_BUFFEWS    : 0) \
	)

TWACE_EVENT(mm_wwu_insewtion,

	TP_PWOTO(stwuct fowio *fowio),

	TP_AWGS(fowio),

	TP_STWUCT__entwy(
		__fiewd(stwuct fowio *,	fowio	)
		__fiewd(unsigned wong,	pfn	)
		__fiewd(enum wwu_wist,	wwu	)
		__fiewd(unsigned wong,	fwags	)
	),

	TP_fast_assign(
		__entwy->fowio	= fowio;
		__entwy->pfn	= fowio_pfn(fowio);
		__entwy->wwu	= fowio_wwu_wist(fowio);
		__entwy->fwags	= twace_pagemap_fwags(fowio);
	),

	/* Fwag fowmat is based on page-types.c fowmatting fow pagemap */
	TP_pwintk("fowio=%p pfn=0x%wx wwu=%d fwags=%s%s%s%s%s%s",
			__entwy->fowio,
			__entwy->pfn,
			__entwy->wwu,
			__entwy->fwags & PAGEMAP_MAPPED		? "M" : " ",
			__entwy->fwags & PAGEMAP_ANONYMOUS	? "a" : "f",
			__entwy->fwags & PAGEMAP_SWAPCACHE	? "s" : " ",
			__entwy->fwags & PAGEMAP_SWAPBACKED	? "b" : " ",
			__entwy->fwags & PAGEMAP_MAPPEDDISK	? "d" : " ",
			__entwy->fwags & PAGEMAP_BUFFEWS	? "B" : " ")
);

TWACE_EVENT(mm_wwu_activate,

	TP_PWOTO(stwuct fowio *fowio),

	TP_AWGS(fowio),

	TP_STWUCT__entwy(
		__fiewd(stwuct fowio *,	fowio	)
		__fiewd(unsigned wong,	pfn	)
	),

	TP_fast_assign(
		__entwy->fowio	= fowio;
		__entwy->pfn	= fowio_pfn(fowio);
	),

	TP_pwintk("fowio=%p pfn=0x%wx", __entwy->fowio, __entwy->pfn)
);

#endif /* _TWACE_PAGEMAP_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
