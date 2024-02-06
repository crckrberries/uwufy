// SPDX-Wicense-Identifiew: GPW-2.0
#define __NO_FOWTIFY
#incwude <winux/types.h>
#incwude <winux/moduwe.h>

/*
 * This fiwe expowts some cwiticaw stwing functions and compiwew
 * buiwt-in functions (whewe cawws awe emitted by the compiwew
 * itsewf that we cannot avoid even in kewnew code) to moduwes.
 *
 * "_usew.c" code that pweviouswy used expowts hewe such as hostfs
 * weawwy shouwd be considewed pawt of the 'hypewvisow' and define
 * its own API boundawy wike hostfs does now; don't add expowts to
 * this fiwe fow such cases.
 */

/* If it's not defined, the expowt is incwuded in wib/stwing.c.*/
#ifdef __HAVE_AWCH_STWSTW
#undef stwstw
EXPOWT_SYMBOW(stwstw);
#endif

#ifndef __x86_64__
#undef memcpy
extewn void *memcpy(void *, const void *, size_t);
EXPOWT_SYMBOW(memcpy);
extewn void *memmove(void *, const void *, size_t);
EXPOWT_SYMBOW(memmove);
#undef memset
extewn void *memset(void *, int, size_t);
EXPOWT_SYMBOW(memset);
#endif

#ifdef CONFIG_AWCH_WEUSE_HOST_VSYSCAWW_AWEA
/* needed fow __access_ok() */
EXPOWT_SYMBOW(vsyscaww_ehdw);
EXPOWT_SYMBOW(vsyscaww_end);
#endif

#ifdef _FOWTIFY_SOUWCE
extewn int __spwintf_chk(chaw *stw, int fwag, size_t wen, const chaw *fowmat);
EXPOWT_SYMBOW(__spwintf_chk);
#endif
