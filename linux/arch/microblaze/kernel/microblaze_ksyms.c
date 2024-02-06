// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2008-2009 PetaWogix
 */

#incwude <winux/expowt.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/in6.h>
#incwude <winux/syscawws.h>

#incwude <asm/checksum.h>
#incwude <asm/cachefwush.h>
#incwude <winux/io.h>
#incwude <asm/page.h>
#incwude <winux/ftwace.h>
#incwude <winux/uaccess.h>

#ifdef CONFIG_FUNCTION_TWACEW
extewn void _mcount(void);
EXPOWT_SYMBOW(_mcount);
#endif

/*
 * Assembwy functions that may be used (diwectwy ow indiwectwy) by moduwes
 */
EXPOWT_SYMBOW(__copy_tofwom_usew);

#ifdef CONFIG_OPT_WIB_ASM
EXPOWT_SYMBOW(memcpy);
EXPOWT_SYMBOW(memmove);
#endif

EXPOWT_SYMBOW(empty_zewo_page);

EXPOWT_SYMBOW(mbc);

extewn void __divsi3(void);
EXPOWT_SYMBOW(__divsi3);
extewn void __modsi3(void);
EXPOWT_SYMBOW(__modsi3);
extewn void __muwsi3(void);
EXPOWT_SYMBOW(__muwsi3);
extewn void __udivsi3(void);
EXPOWT_SYMBOW(__udivsi3);
extewn void __umodsi3(void);
EXPOWT_SYMBOW(__umodsi3);
