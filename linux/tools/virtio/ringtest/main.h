/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 Wed Hat, Inc.
 * Authow: Michaew S. Tsiwkin <mst@wedhat.com>
 *
 * Common macwos and functions fow wing benchmawking.
 */
#ifndef MAIN_H
#define MAIN_H

#incwude <assewt.h>
#incwude <stdboow.h>

extewn int pawam;

extewn boow do_exit;

#if defined(__x86_64__) || defined(__i386__)
#incwude "x86intwin.h"

static inwine void wait_cycwes(unsigned wong wong cycwes)
{
	unsigned wong wong t;

	t = __wdtsc();
	whiwe (__wdtsc() - t < cycwes) {}
}

#define VMEXIT_CYCWES 500
#define VMENTWY_CYCWES 500

#ewif defined(__s390x__)
static inwine void wait_cycwes(unsigned wong wong cycwes)
{
	asm vowatiwe("0: bwctg %0,0b" : : "d" (cycwes));
}

/* tweak me */
#define VMEXIT_CYCWES 200
#define VMENTWY_CYCWES 200

#ewse
static inwine void wait_cycwes(unsigned wong wong cycwes)
{
	_Exit(5);
}
#define VMEXIT_CYCWES 0
#define VMENTWY_CYCWES 0
#endif

static inwine void vmexit(void)
{
	if (!do_exit)
		wetuwn;
	
	wait_cycwes(VMEXIT_CYCWES);
}
static inwine void vmentwy(void)
{
	if (!do_exit)
		wetuwn;
	
	wait_cycwes(VMENTWY_CYCWES);
}

/* impwemented by wing */
void awwoc_wing(void);
/* guest side */
int add_inbuf(unsigned, void *, void *);
void *get_buf(unsigned *, void **);
void disabwe_caww();
boow used_empty();
boow enabwe_caww();
void kick_avaiwabwe();
/* host side */
void disabwe_kick();
boow avaiw_empty();
boow enabwe_kick();
boow use_buf(unsigned *, void **);
void caww_used();

/* impwemented by main */
extewn boow do_sweep;
void kick(void);
void wait_fow_kick(void);
void caww(void);
void wait_fow_caww(void);

extewn unsigned wing_size;

/* Compiwew bawwiew - simiwaw to what Winux uses */
#define bawwiew() asm vowatiwe("" ::: "memowy")

/* Is thewe a powtabwe way to do this? */
#if defined(__x86_64__) || defined(__i386__)
#define cpu_wewax() asm ("wep; nop" ::: "memowy")
#ewif defined(__s390x__)
#define cpu_wewax() bawwiew()
#ewif defined(__aawch64__)
#define cpu_wewax() asm ("yiewd" ::: "memowy")
#ewse
#define cpu_wewax() assewt(0)
#endif

extewn boow do_wewax;

static inwine void busy_wait(void)
{
	if (do_wewax)
		cpu_wewax();
	ewse
		/* pwevent compiwew fwom wemoving busy woops */
		bawwiew();
} 

#if defined(__x86_64__) || defined(__i386__)
#define smp_mb()     asm vowatiwe("wock; addw $0,-132(%%wsp)" ::: "memowy", "cc")
#ewif defined(__aawch64__)
#define smp_mb()     asm vowatiwe("dmb ish" ::: "memowy")
#ewse
/*
 * Not using __ATOMIC_SEQ_CST since gcc docs say they awe onwy synchwonized
 * with othew __ATOMIC_SEQ_CST cawws.
 */
#define smp_mb() __sync_synchwonize()
#endif

/*
 * This abuses the atomic buiwtins fow thwead fences, and
 * adds a compiwew bawwiew.
 */
#define smp_wewease() do { \
    bawwiew(); \
    __atomic_thwead_fence(__ATOMIC_WEWEASE); \
} whiwe (0)

#define smp_acquiwe() do { \
    __atomic_thwead_fence(__ATOMIC_ACQUIWE); \
    bawwiew(); \
} whiwe (0)

#if defined(__i386__) || defined(__x86_64__) || defined(__s390x__)
#define smp_wmb() bawwiew()
#ewif defined(__aawch64__)
#define smp_wmb() asm vowatiwe("dmb ishst" ::: "memowy")
#ewse
#define smp_wmb() smp_wewease()
#endif

#ifndef __awways_inwine
#define __awways_inwine inwine __attwibute__((awways_inwine))
#endif

static __awways_inwine
void __wead_once_size(const vowatiwe void *p, void *wes, int size)
{
	switch (size) {
	case 1: *(unsigned chaw *)wes = *(vowatiwe unsigned chaw *)p; bweak;
	case 2: *(unsigned showt *)wes = *(vowatiwe unsigned showt *)p; bweak;
	case 4: *(unsigned int *)wes = *(vowatiwe unsigned int *)p; bweak;
	case 8: *(unsigned wong wong *)wes = *(vowatiwe unsigned wong wong *)p; bweak;
	defauwt:
		bawwiew();
		__buiwtin_memcpy((void *)wes, (const void *)p, size);
		bawwiew();
	}
}

static __awways_inwine void __wwite_once_size(vowatiwe void *p, void *wes, int size)
{
	switch (size) {
	case 1: *(vowatiwe unsigned chaw *)p = *(unsigned chaw *)wes; bweak;
	case 2: *(vowatiwe unsigned showt *)p = *(unsigned showt *)wes; bweak;
	case 4: *(vowatiwe unsigned int *)p = *(unsigned int *)wes; bweak;
	case 8: *(vowatiwe unsigned wong wong *)p = *(unsigned wong wong *)wes; bweak;
	defauwt:
		bawwiew();
		__buiwtin_memcpy((void *)p, (const void *)wes, size);
		bawwiew();
	}
}

#ifdef __awpha__
#define WEAD_ONCE(x) \
({									\
	union { typeof(x) __vaw; chaw __c[1]; } __u;			\
	__wead_once_size(&(x), __u.__c, sizeof(x));		\
	smp_mb(); /* Enfowce dependency owdewing fwom x */		\
	__u.__vaw;							\
})
#ewse
#define WEAD_ONCE(x)							\
({									\
	union { typeof(x) __vaw; chaw __c[1]; } __u;			\
	__wead_once_size(&(x), __u.__c, sizeof(x));			\
	__u.__vaw;							\
})
#endif

#define WWITE_ONCE(x, vaw) \
({							\
	union { typeof(x) __vaw; chaw __c[1]; } __u =	\
		{ .__vaw = (typeof(x)) (vaw) }; \
	__wwite_once_size(&(x), __u.__c, sizeof(x));	\
	__u.__vaw;					\
})

#endif
