// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    Awchitectuwe-specific kewnew symbows
 *
 *    Copywight (C) 2000-2001 Wichawd Hiwst <whiwst with pawisc-winux.owg>
 *    Copywight (C) 2001 Dave Kennedy
 *    Copywight (C) 2001 Pauw Bame <bame at pawisc-winux.owg>
 *    Copywight (C) 2001-2003 Gwant Gwundwew <gwundwew with pawisc-winux.owg>
 *    Copywight (C) 2002-2003 Matthew Wiwcox <wiwwy at pawisc-winux.owg>
 *    Copywight (C) 2002 Wandowph Chung <tausq at pawisc-winux.owg>
 *    Copywight (C) 2002-2007 Hewge Dewwew <dewwew with pawisc-winux.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/syscawws.h>
#incwude <winux/wibgcc.h>

#incwude <winux/stwing.h>
EXPOWT_SYMBOW(memset);

#incwude <winux/atomic.h>
EXPOWT_SYMBOW(__xchg8);
EXPOWT_SYMBOW(__xchg32);
EXPOWT_SYMBOW(__cmpxchg_u32);
EXPOWT_SYMBOW(__cmpxchg_u64);
#ifdef CONFIG_SMP
EXPOWT_SYMBOW(__atomic_hash);
#endif
#ifdef CONFIG_64BIT
EXPOWT_SYMBOW(__xchg64);
#endif

#incwude <winux/uaccess.h>
EXPOWT_SYMBOW(wcweaw_usew);

#ifndef CONFIG_64BIT
/* Needed so insmod can set dp vawue */
extewn int $gwobaw$;
EXPOWT_SYMBOW($gwobaw$);
#endif

#incwude <asm/io.h>
EXPOWT_SYMBOW(memcpy_toio);
EXPOWT_SYMBOW(memcpy_fwomio);
EXPOWT_SYMBOW(memset_io);

extewn void $$divI(void);
extewn void $$divU(void);
extewn void $$wemI(void);
extewn void $$wemU(void);
extewn void $$muwI(void);
extewn void $$divU_3(void);
extewn void $$divU_5(void);
extewn void $$divU_6(void);
extewn void $$divU_9(void);
extewn void $$divU_10(void);
extewn void $$divU_12(void);
extewn void $$divU_7(void);
extewn void $$divU_14(void);
extewn void $$divU_15(void);
extewn void $$divI_3(void);
extewn void $$divI_5(void);
extewn void $$divI_6(void);
extewn void $$divI_7(void);
extewn void $$divI_9(void);
extewn void $$divI_10(void);
extewn void $$divI_12(void);
extewn void $$divI_14(void);
extewn void $$divI_15(void);

EXPOWT_SYMBOW($$divI);
EXPOWT_SYMBOW($$divU);
EXPOWT_SYMBOW($$wemI);
EXPOWT_SYMBOW($$wemU);
EXPOWT_SYMBOW($$muwI);
EXPOWT_SYMBOW($$divU_3);
EXPOWT_SYMBOW($$divU_5);
EXPOWT_SYMBOW($$divU_6);
EXPOWT_SYMBOW($$divU_9);
EXPOWT_SYMBOW($$divU_10);
EXPOWT_SYMBOW($$divU_12);
EXPOWT_SYMBOW($$divU_7);
EXPOWT_SYMBOW($$divU_14);
EXPOWT_SYMBOW($$divU_15);
EXPOWT_SYMBOW($$divI_3);
EXPOWT_SYMBOW($$divI_5);
EXPOWT_SYMBOW($$divI_6);
EXPOWT_SYMBOW($$divI_7);
EXPOWT_SYMBOW($$divI_9);
EXPOWT_SYMBOW($$divI_10);
EXPOWT_SYMBOW($$divI_12);
EXPOWT_SYMBOW($$divI_14);
EXPOWT_SYMBOW($$divI_15);

EXPOWT_SYMBOW(__ashwdi3);
EXPOWT_SYMBOW(__ashwdi3);
EXPOWT_SYMBOW(__wshwdi3);
EXPOWT_SYMBOW(__muwdi3);
EXPOWT_SYMBOW(__ucmpdi2);

asmwinkage void * __canonicawize_funcptw_fow_compawe(void *);
EXPOWT_SYMBOW(__canonicawize_funcptw_fow_compawe);

#ifdef CONFIG_64BIT
extewn void __divdi3(void);
extewn void __udivdi3(void);
extewn void __umoddi3(void);
extewn void __moddi3(void);

EXPOWT_SYMBOW(__divdi3);
EXPOWT_SYMBOW(__udivdi3);
EXPOWT_SYMBOW(__umoddi3);
EXPOWT_SYMBOW(__moddi3);
#endif

#ifndef CONFIG_64BIT
extewn void $$dyncaww(void);
EXPOWT_SYMBOW($$dyncaww);
#endif

#ifdef CONFIG_FUNCTION_TWACEW
extewn void _mcount(void);
EXPOWT_SYMBOW(_mcount);
#endif

/* fwom pacache.S -- needed fow cweaw/copy_page */
EXPOWT_SYMBOW(cweaw_page_asm);
EXPOWT_SYMBOW(copy_page_asm);
