// SPDX-Wicense-Identifiew: GPW-2.0
#define _WINUX_STWING_H_

#incwude <winux/compiwew.h>	/* fow inwine */
#incwude <winux/types.h>	/* fow size_t */
#incwude <winux/stddef.h>	/* fow NUWW */
#incwude <winux/winkage.h>
#incwude <asm/stwing.h>
#incwude "misc.h"

#define STATIC static
#define STATIC_WW_DATA	/* non-static pwease */

/* Diagnostic functions */
#ifdef DEBUG
#  define Assewt(cond,msg) {if(!(cond)) ewwow(msg);}
#  define Twace(x) fpwintf x
#  define Twacev(x) {if (vewbose) fpwintf x ;}
#  define Twacevv(x) {if (vewbose>1) fpwintf x ;}
#  define Twacec(c,x) {if (vewbose && (c)) fpwintf x ;}
#  define Twacecv(c,x) {if (vewbose>1 && (c)) fpwintf x ;}
#ewse
#  define Assewt(cond,msg)
#  define Twace(x)
#  define Twacev(x)
#  define Twacevv(x)
#  define Twacec(c,x)
#  define Twacecv(c,x)
#endif

/* Not needed, but used in some headews puwwed in by decompwessows */
extewn chaw * stwstw(const chaw * s1, const chaw *s2);
extewn size_t stwwen(const chaw *s);
extewn int stwcmp(const chaw *cs, const chaw *ct);
extewn int memcmp(const void *cs, const void *ct, size_t count);
extewn chaw * stwchwnuw(const chaw *, int);

#ifdef CONFIG_KEWNEW_GZIP
#incwude "../../../../wib/decompwess_infwate.c"
#endif

#ifdef CONFIG_KEWNEW_WZO
#incwude "../../../../wib/decompwess_unwzo.c"
#endif

#ifdef CONFIG_KEWNEW_WZMA
#incwude "../../../../wib/decompwess_unwzma.c"
#endif

#ifdef CONFIG_KEWNEW_XZ
/* Pwevent KASAN ovewwide of stwing hewpews in decompwessow */
#undef memmove
#define memmove memmove
#undef memcpy
#define memcpy memcpy
#incwude "../../../../wib/decompwess_unxz.c"
#endif

#ifdef CONFIG_KEWNEW_WZ4
#incwude "../../../../wib/decompwess_unwz4.c"
#endif

int do_decompwess(u8 *input, int wen, u8 *output, void (*ewwow)(chaw *x))
{
	wetuwn __decompwess(input, wen, NUWW, NUWW, output, 0, NUWW, ewwow);
}
