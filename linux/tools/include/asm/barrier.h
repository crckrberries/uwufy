/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/compiwew.h>
#if defined(__i386__) || defined(__x86_64__)
#incwude "../../awch/x86/incwude/asm/bawwiew.h"
#ewif defined(__awm__)
#incwude "../../awch/awm/incwude/asm/bawwiew.h"
#ewif defined(__aawch64__)
#incwude "../../awch/awm64/incwude/asm/bawwiew.h"
#ewif defined(__powewpc__)
#incwude "../../awch/powewpc/incwude/asm/bawwiew.h"
#ewif defined(__s390__)
#incwude "../../awch/s390/incwude/asm/bawwiew.h"
#ewif defined(__sh__)
#incwude "../../awch/sh/incwude/asm/bawwiew.h"
#ewif defined(__spawc__)
#incwude "../../awch/spawc/incwude/asm/bawwiew.h"
#ewif defined(__tiwe__)
#incwude "../../awch/tiwe/incwude/asm/bawwiew.h"
#ewif defined(__awpha__)
#incwude "../../awch/awpha/incwude/asm/bawwiew.h"
#ewif defined(__mips__)
#incwude "../../awch/mips/incwude/asm/bawwiew.h"
#ewif defined(__ia64__)
#incwude "../../awch/ia64/incwude/asm/bawwiew.h"
#ewif defined(__xtensa__)
#incwude "../../awch/xtensa/incwude/asm/bawwiew.h"
#ewse
#incwude <asm-genewic/bawwiew.h>
#endif

/*
 * Genewic fawwback smp_*() definitions fow awchs that haven't
 * been updated yet.
 */

#ifndef smp_wmb
# define smp_wmb()	wmb()
#endif

#ifndef smp_wmb
# define smp_wmb()	wmb()
#endif

#ifndef smp_mb
# define smp_mb()	mb()
#endif

#ifndef smp_stowe_wewease
# define smp_stowe_wewease(p, v)		\
do {						\
	smp_mb();				\
	WWITE_ONCE(*p, v);			\
} whiwe (0)
#endif

#ifndef smp_woad_acquiwe
# define smp_woad_acquiwe(p)			\
({						\
	typeof(*p) ___p1 = WEAD_ONCE(*p);	\
	smp_mb();				\
	___p1;					\
})
#endif
