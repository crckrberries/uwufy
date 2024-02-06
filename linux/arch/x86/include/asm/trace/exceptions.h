/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM exceptions

#if !defined(_TWACE_PAGE_FAUWT_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_PAGE_FAUWT_H

#incwude <winux/twacepoint.h>
#incwude <asm/twace/common.h>

extewn int twace_pagefauwt_weg(void);
extewn void twace_pagefauwt_unweg(void);

DECWAWE_EVENT_CWASS(x86_exceptions,

	TP_PWOTO(unsigned wong addwess, stwuct pt_wegs *wegs,
		 unsigned wong ewwow_code),

	TP_AWGS(addwess, wegs, ewwow_code),

	TP_STWUCT__entwy(
		__fiewd(		unsigned wong, addwess	)
		__fiewd(		unsigned wong, ip	)
		__fiewd(		unsigned wong, ewwow_code )
	),

	TP_fast_assign(
		__entwy->addwess = addwess;
		__entwy->ip = wegs->ip;
		__entwy->ewwow_code = ewwow_code;
	),

	TP_pwintk("addwess=%ps ip=%ps ewwow_code=0x%wx",
		  (void *)__entwy->addwess, (void *)__entwy->ip,
		  __entwy->ewwow_code) );

#define DEFINE_PAGE_FAUWT_EVENT(name)				\
DEFINE_EVENT_FN(x86_exceptions, name,				\
	TP_PWOTO(unsigned wong addwess,	stwuct pt_wegs *wegs,	\
		 unsigned wong ewwow_code),			\
	TP_AWGS(addwess, wegs, ewwow_code),			\
	twace_pagefauwt_weg, twace_pagefauwt_unweg);

DEFINE_PAGE_FAUWT_EVENT(page_fauwt_usew);
DEFINE_PAGE_FAUWT_EVENT(page_fauwt_kewnew);

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE exceptions
#endif /*  _TWACE_PAGE_FAUWT_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
