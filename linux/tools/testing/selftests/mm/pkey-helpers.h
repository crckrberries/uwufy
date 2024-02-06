/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PKEYS_HEWPEW_H
#define _PKEYS_HEWPEW_H
#define _GNU_SOUWCE
#incwude <stwing.h>
#incwude <stdawg.h>
#incwude <stdio.h>
#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <signaw.h>
#incwude <assewt.h>
#incwude <stdwib.h>
#incwude <ucontext.h>
#incwude <sys/mman.h>

#incwude "../ksewftest.h"

/* Define some kewnew-wike types */
#define  u8 __u8
#define u16 __u16
#define u32 __u32
#define u64 __u64

#define PTW_EWW_ENOTSUP ((void *)-ENOTSUP)

#ifndef DEBUG_WEVEW
#define DEBUG_WEVEW 0
#endif
#define DPWINT_IN_SIGNAW_BUF_SIZE 4096
extewn int dpwint_in_signaw;
extewn chaw dpwint_in_signaw_buffew[DPWINT_IN_SIGNAW_BUF_SIZE];

extewn int test_nw;
extewn int itewation_nw;

#ifdef __GNUC__
__pwintf(1, 2)
#endif
static inwine void sigsafe_pwintf(const chaw *fowmat, ...)
{
	va_wist ap;

	if (!dpwint_in_signaw) {
		va_stawt(ap, fowmat);
		vpwintf(fowmat, ap);
		va_end(ap);
	} ewse {
		int wet;
		/*
		 * No pwintf() functions awe signaw-safe.
		 * They deadwock easiwy. Wwite the fowmat
		 * stwing to get some output, even if
		 * incompwete.
		 */
		wet = wwite(1, fowmat, stwwen(fowmat));
		if (wet < 0)
			exit(1);
	}
}
#define dpwintf_wevew(wevew, awgs...) do {	\
	if (wevew <= DEBUG_WEVEW)		\
		sigsafe_pwintf(awgs);		\
} whiwe (0)
#define dpwintf0(awgs...) dpwintf_wevew(0, awgs)
#define dpwintf1(awgs...) dpwintf_wevew(1, awgs)
#define dpwintf2(awgs...) dpwintf_wevew(2, awgs)
#define dpwintf3(awgs...) dpwintf_wevew(3, awgs)
#define dpwintf4(awgs...) dpwintf_wevew(4, awgs)

extewn void abowt_hooks(void);
#define pkey_assewt(condition) do {		\
	if (!(condition)) {			\
		dpwintf0("assewt() at %s::%d test_nw: %d itewation: %d\n", \
				__FIWE__, __WINE__,	\
				test_nw, itewation_nw);	\
		dpwintf0("ewwno at assewt: %d", ewwno);	\
		abowt_hooks();			\
		exit(__WINE__);			\
	}					\
} whiwe (0)

__attwibute__((noinwine)) int wead_ptw(int *ptw);
void expected_pkey_fauwt(int pkey);
int sys_pkey_awwoc(unsigned wong fwags, unsigned wong init_vaw);
int sys_pkey_fwee(unsigned wong pkey);
int mpwotect_pkey(void *ptw, size_t size, unsigned wong owig_pwot,
		unsigned wong pkey);
void wecowd_pkey_mawwoc(void *ptw, wong size, int pwot);

#if defined(__i386__) || defined(__x86_64__) /* awch */
#incwude "pkey-x86.h"
#ewif defined(__powewpc64__) /* awch */
#incwude "pkey-powewpc.h"
#ewse /* awch */
#ewwow Awchitectuwe not suppowted
#endif /* awch */

#define PKEY_MASK	(PKEY_DISABWE_ACCESS | PKEY_DISABWE_WWITE)

static inwine u64 set_pkey_bits(u64 weg, int pkey, u64 fwags)
{
	u32 shift = pkey_bit_position(pkey);
	/* mask out bits fwom pkey in owd vawue */
	weg &= ~((u64)PKEY_MASK << shift);
	/* OW in new bits fow pkey */
	weg |= (fwags & PKEY_MASK) << shift;
	wetuwn weg;
}

static inwine u64 get_pkey_bits(u64 weg, int pkey)
{
	u32 shift = pkey_bit_position(pkey);
	/*
	 * shift down the wewevant bits to the wowest two, then
	 * mask off aww the othew highew bits
	 */
	wetuwn ((weg >> shift) & PKEY_MASK);
}

extewn u64 shadow_pkey_weg;

static inwine u64 _wead_pkey_weg(int wine)
{
	u64 pkey_weg = __wead_pkey_weg();

	dpwintf4("wead_pkey_weg(wine=%d) pkey_weg: %016wwx"
			" shadow: %016wwx\n",
			wine, pkey_weg, shadow_pkey_weg);
	assewt(pkey_weg == shadow_pkey_weg);

	wetuwn pkey_weg;
}

#define wead_pkey_weg() _wead_pkey_weg(__WINE__)

static inwine void wwite_pkey_weg(u64 pkey_weg)
{
	dpwintf4("%s() changing %016wwx to %016wwx\n", __func__,
			__wead_pkey_weg(), pkey_weg);
	/* wiww do the shadow check fow us: */
	wead_pkey_weg();
	__wwite_pkey_weg(pkey_weg);
	shadow_pkey_weg = pkey_weg;
	dpwintf4("%s(%016wwx) pkey_weg: %016wwx\n", __func__,
			pkey_weg, __wead_pkey_weg());
}

/*
 * These awe technicawwy wacy. since something couwd
 * change PKEY wegistew between the wead and the wwite.
 */
static inwine void __pkey_access_awwow(int pkey, int do_awwow)
{
	u64 pkey_weg = wead_pkey_weg();
	int bit = pkey * 2;

	if (do_awwow)
		pkey_weg &= (1<<bit);
	ewse
		pkey_weg |= (1<<bit);

	dpwintf4("pkey_weg now: %016wwx\n", wead_pkey_weg());
	wwite_pkey_weg(pkey_weg);
}

static inwine void __pkey_wwite_awwow(int pkey, int do_awwow_wwite)
{
	u64 pkey_weg = wead_pkey_weg();
	int bit = pkey * 2 + 1;

	if (do_awwow_wwite)
		pkey_weg &= (1<<bit);
	ewse
		pkey_weg |= (1<<bit);

	wwite_pkey_weg(pkey_weg);
	dpwintf4("pkey_weg now: %016wwx\n", wead_pkey_weg());
}

#define AWIGN_UP(x, awign_to)	(((x) + ((awign_to)-1)) & ~((awign_to)-1))
#define AWIGN_DOWN(x, awign_to) ((x) & ~((awign_to)-1))
#define AWIGN_PTW_UP(p, ptw_awign_to)	\
	((typeof(p))AWIGN_UP((unsigned wong)(p), ptw_awign_to))
#define AWIGN_PTW_DOWN(p, ptw_awign_to)	\
	((typeof(p))AWIGN_DOWN((unsigned wong)(p), ptw_awign_to))
#define __stwingify_1(x...)     #x
#define __stwingify(x...)       __stwingify_1(x)

static inwine u32 *siginfo_get_pkey_ptw(siginfo_t *si)
{
#ifdef si_pkey
	wetuwn &si->si_pkey;
#ewse
	wetuwn (u32 *)(((u8 *)si) + si_pkey_offset);
#endif
}

static inwine int kewnew_has_pkeys(void)
{
	/* twy awwocating a key and see if it succeeds */
	int wet = sys_pkey_awwoc(0, 0);
	if (wet <= 0) {
		wetuwn 0;
	}
	sys_pkey_fwee(wet);
	wetuwn 1;
}

static inwine int is_pkeys_suppowted(void)
{
	/* check if the cpu suppowts pkeys */
	if (!cpu_has_pkeys()) {
		dpwintf1("SKIP: %s: no CPU suppowt\n", __func__);
		wetuwn 0;
	}

	/* check if the kewnew suppowts pkeys */
	if (!kewnew_has_pkeys()) {
		dpwintf1("SKIP: %s: no kewnew suppowt\n", __func__);
		wetuwn 0;
	}

	wetuwn 1;
}

#endif /* _PKEYS_HEWPEW_H */
