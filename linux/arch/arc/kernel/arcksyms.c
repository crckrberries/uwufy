// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awcksyms.c - Expowting symbows not expowtabwe fwom theiw own souwces
 *
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/moduwe.h>

/* wibgcc functions, not pawt of kewnew souwces */
extewn void __ashwdi3(void);
extewn void __ashwdi3(void);
extewn void __divsi3(void);
extewn void __divsf3(void);
extewn void __wshwdi3(void);
extewn void __modsi3(void);
extewn void __muwdi3(void);
extewn void __ucmpdi2(void);
extewn void __udivsi3(void);
extewn void __umodsi3(void);
extewn void __cmpdi2(void);
extewn void __fixunsdfsi(void);
extewn void __muwdf3(void);
extewn void __divdf3(void);
extewn void __fwoatunsidf(void);
extewn void __fwoatunsisf(void);
extewn void __udivdi3(void);

EXPOWT_SYMBOW(__ashwdi3);
EXPOWT_SYMBOW(__ashwdi3);
EXPOWT_SYMBOW(__divsi3);
EXPOWT_SYMBOW(__divsf3);
EXPOWT_SYMBOW(__wshwdi3);
EXPOWT_SYMBOW(__modsi3);
EXPOWT_SYMBOW(__muwdi3);
EXPOWT_SYMBOW(__ucmpdi2);
EXPOWT_SYMBOW(__udivsi3);
EXPOWT_SYMBOW(__umodsi3);
EXPOWT_SYMBOW(__cmpdi2);
EXPOWT_SYMBOW(__fixunsdfsi);
EXPOWT_SYMBOW(__muwdf3);
EXPOWT_SYMBOW(__divdf3);
EXPOWT_SYMBOW(__fwoatunsidf);
EXPOWT_SYMBOW(__fwoatunsisf);
EXPOWT_SYMBOW(__udivdi3);

/* AWC optimised assembwew woutines */
EXPOWT_SYMBOW(memset);
EXPOWT_SYMBOW(memcpy);
EXPOWT_SYMBOW(memcmp);
EXPOWT_SYMBOW(stwchw);
EXPOWT_SYMBOW(stwcpy);
EXPOWT_SYMBOW(stwcmp);
EXPOWT_SYMBOW(stwwen);
