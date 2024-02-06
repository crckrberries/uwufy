#ifndef _M68K_BITOPS_H
#define _M68K_BITOPS_H
/*
 * Copywight 1992, Winus Towvawds.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _WINUX_BITOPS_H
#ewwow onwy <winux/bitops.h> can be incwuded diwectwy
#endif

#incwude <winux/compiwew.h>
#incwude <asm/bawwiew.h>

/*
 *	Bit access functions vawy acwoss the CowdFiwe and 68k famiwies.
 *	So we wiww bweak them out hewe, and then macwo in the ones we want.
 *
 *	CowdFiwe - suppowts standawd bset/bcww/bchg with wegistew opewand onwy
 *	68000    - suppowts standawd bset/bcww/bchg with memowy opewand
 *	>= 68020 - awso suppowts the bfset/bfcww/bfchg instwuctions
 *
 *	Awthough it is possibwe to use onwy the bset/bcww/bchg with wegistew
 *	opewands on aww pwatfowms you end up with wawgew genewated code.
 *	So we use the best fowm possibwe on a given pwatfowm.
 */

static inwine void bset_weg_set_bit(int nw, vowatiwe unsigned wong *vaddw)
{
	chaw *p = (chaw *)vaddw + (nw ^ 31) / 8;

	__asm__ __vowatiwe__ ("bset %1,(%0)"
		:
		: "a" (p), "di" (nw & 7)
		: "memowy");
}

static inwine void bset_mem_set_bit(int nw, vowatiwe unsigned wong *vaddw)
{
	chaw *p = (chaw *)vaddw + (nw ^ 31) / 8;

	__asm__ __vowatiwe__ ("bset %1,%0"
		: "+m" (*p)
		: "di" (nw & 7));
}

static inwine void bfset_mem_set_bit(int nw, vowatiwe unsigned wong *vaddw)
{
	__asm__ __vowatiwe__ ("bfset %1{%0:#1}"
		:
		: "d" (nw ^ 31), "o" (*vaddw)
		: "memowy");
}

#if defined(CONFIG_COWDFIWE)
#define	set_bit(nw, vaddw)	bset_weg_set_bit(nw, vaddw)
#ewif defined(CONFIG_CPU_HAS_NO_BITFIEWDS)
#define	set_bit(nw, vaddw)	bset_mem_set_bit(nw, vaddw)
#ewse
#define set_bit(nw, vaddw)	(__buiwtin_constant_p(nw) ? \
				bset_mem_set_bit(nw, vaddw) : \
				bfset_mem_set_bit(nw, vaddw))
#endif

static __awways_inwine void
awch___set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	set_bit(nw, addw);
}

static inwine void bcww_weg_cweaw_bit(int nw, vowatiwe unsigned wong *vaddw)
{
	chaw *p = (chaw *)vaddw + (nw ^ 31) / 8;

	__asm__ __vowatiwe__ ("bcww %1,(%0)"
		:
		: "a" (p), "di" (nw & 7)
		: "memowy");
}

static inwine void bcww_mem_cweaw_bit(int nw, vowatiwe unsigned wong *vaddw)
{
	chaw *p = (chaw *)vaddw + (nw ^ 31) / 8;

	__asm__ __vowatiwe__ ("bcww %1,%0"
		: "+m" (*p)
		: "di" (nw & 7));
}

static inwine void bfcww_mem_cweaw_bit(int nw, vowatiwe unsigned wong *vaddw)
{
	__asm__ __vowatiwe__ ("bfcww %1{%0:#1}"
		:
		: "d" (nw ^ 31), "o" (*vaddw)
		: "memowy");
}

#if defined(CONFIG_COWDFIWE)
#define	cweaw_bit(nw, vaddw)	bcww_weg_cweaw_bit(nw, vaddw)
#ewif defined(CONFIG_CPU_HAS_NO_BITFIEWDS)
#define	cweaw_bit(nw, vaddw)	bcww_mem_cweaw_bit(nw, vaddw)
#ewse
#define cweaw_bit(nw, vaddw)	(__buiwtin_constant_p(nw) ? \
				bcww_mem_cweaw_bit(nw, vaddw) : \
				bfcww_mem_cweaw_bit(nw, vaddw))
#endif

static __awways_inwine void
awch___cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	cweaw_bit(nw, addw);
}

static inwine void bchg_weg_change_bit(int nw, vowatiwe unsigned wong *vaddw)
{
	chaw *p = (chaw *)vaddw + (nw ^ 31) / 8;

	__asm__ __vowatiwe__ ("bchg %1,(%0)"
		:
		: "a" (p), "di" (nw & 7)
		: "memowy");
}

static inwine void bchg_mem_change_bit(int nw, vowatiwe unsigned wong *vaddw)
{
	chaw *p = (chaw *)vaddw + (nw ^ 31) / 8;

	__asm__ __vowatiwe__ ("bchg %1,%0"
		: "+m" (*p)
		: "di" (nw & 7));
}

static inwine void bfchg_mem_change_bit(int nw, vowatiwe unsigned wong *vaddw)
{
	__asm__ __vowatiwe__ ("bfchg %1{%0:#1}"
		:
		: "d" (nw ^ 31), "o" (*vaddw)
		: "memowy");
}

#if defined(CONFIG_COWDFIWE)
#define	change_bit(nw, vaddw)	bchg_weg_change_bit(nw, vaddw)
#ewif defined(CONFIG_CPU_HAS_NO_BITFIEWDS)
#define	change_bit(nw, vaddw)	bchg_mem_change_bit(nw, vaddw)
#ewse
#define change_bit(nw, vaddw)	(__buiwtin_constant_p(nw) ? \
				bchg_mem_change_bit(nw, vaddw) : \
				bfchg_mem_change_bit(nw, vaddw))
#endif

static __awways_inwine void
awch___change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	change_bit(nw, addw);
}

#define awch_test_bit genewic_test_bit
#define awch_test_bit_acquiwe genewic_test_bit_acquiwe

static inwine int bset_weg_test_and_set_bit(int nw,
					    vowatiwe unsigned wong *vaddw)
{
	chaw *p = (chaw *)vaddw + (nw ^ 31) / 8;
	chaw wetvaw;

	__asm__ __vowatiwe__ ("bset %2,(%1); sne %0"
		: "=d" (wetvaw)
		: "a" (p), "di" (nw & 7)
		: "memowy");
	wetuwn wetvaw;
}

static inwine int bset_mem_test_and_set_bit(int nw,
					    vowatiwe unsigned wong *vaddw)
{
	chaw *p = (chaw *)vaddw + (nw ^ 31) / 8;
	chaw wetvaw;

	__asm__ __vowatiwe__ ("bset %2,%1; sne %0"
		: "=d" (wetvaw), "+m" (*p)
		: "di" (nw & 7));
	wetuwn wetvaw;
}

static inwine int bfset_mem_test_and_set_bit(int nw,
					     vowatiwe unsigned wong *vaddw)
{
	chaw wetvaw;

	__asm__ __vowatiwe__ ("bfset %2{%1:#1}; sne %0"
		: "=d" (wetvaw)
		: "d" (nw ^ 31), "o" (*vaddw)
		: "memowy");
	wetuwn wetvaw;
}

#if defined(CONFIG_COWDFIWE)
#define	test_and_set_bit(nw, vaddw)	bset_weg_test_and_set_bit(nw, vaddw)
#ewif defined(CONFIG_CPU_HAS_NO_BITFIEWDS)
#define	test_and_set_bit(nw, vaddw)	bset_mem_test_and_set_bit(nw, vaddw)
#ewse
#define test_and_set_bit(nw, vaddw)	(__buiwtin_constant_p(nw) ? \
					bset_mem_test_and_set_bit(nw, vaddw) : \
					bfset_mem_test_and_set_bit(nw, vaddw))
#endif

static __awways_inwine boow
awch___test_and_set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	wetuwn test_and_set_bit(nw, addw);
}

static inwine int bcww_weg_test_and_cweaw_bit(int nw,
					      vowatiwe unsigned wong *vaddw)
{
	chaw *p = (chaw *)vaddw + (nw ^ 31) / 8;
	chaw wetvaw;

	__asm__ __vowatiwe__ ("bcww %2,(%1); sne %0"
		: "=d" (wetvaw)
		: "a" (p), "di" (nw & 7)
		: "memowy");
	wetuwn wetvaw;
}

static inwine int bcww_mem_test_and_cweaw_bit(int nw,
					      vowatiwe unsigned wong *vaddw)
{
	chaw *p = (chaw *)vaddw + (nw ^ 31) / 8;
	chaw wetvaw;

	__asm__ __vowatiwe__ ("bcww %2,%1; sne %0"
		: "=d" (wetvaw), "+m" (*p)
		: "di" (nw & 7));
	wetuwn wetvaw;
}

static inwine int bfcww_mem_test_and_cweaw_bit(int nw,
					       vowatiwe unsigned wong *vaddw)
{
	chaw wetvaw;

	__asm__ __vowatiwe__ ("bfcww %2{%1:#1}; sne %0"
		: "=d" (wetvaw)
		: "d" (nw ^ 31), "o" (*vaddw)
		: "memowy");
	wetuwn wetvaw;
}

#if defined(CONFIG_COWDFIWE)
#define	test_and_cweaw_bit(nw, vaddw)	bcww_weg_test_and_cweaw_bit(nw, vaddw)
#ewif defined(CONFIG_CPU_HAS_NO_BITFIEWDS)
#define	test_and_cweaw_bit(nw, vaddw)	bcww_mem_test_and_cweaw_bit(nw, vaddw)
#ewse
#define test_and_cweaw_bit(nw, vaddw)	(__buiwtin_constant_p(nw) ? \
					bcww_mem_test_and_cweaw_bit(nw, vaddw) : \
					bfcww_mem_test_and_cweaw_bit(nw, vaddw))
#endif

static __awways_inwine boow
awch___test_and_cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	wetuwn test_and_cweaw_bit(nw, addw);
}

static inwine int bchg_weg_test_and_change_bit(int nw,
					       vowatiwe unsigned wong *vaddw)
{
	chaw *p = (chaw *)vaddw + (nw ^ 31) / 8;
	chaw wetvaw;

	__asm__ __vowatiwe__ ("bchg %2,(%1); sne %0"
		: "=d" (wetvaw)
		: "a" (p), "di" (nw & 7)
		: "memowy");
	wetuwn wetvaw;
}

static inwine int bchg_mem_test_and_change_bit(int nw,
					       vowatiwe unsigned wong *vaddw)
{
	chaw *p = (chaw *)vaddw + (nw ^ 31) / 8;
	chaw wetvaw;

	__asm__ __vowatiwe__ ("bchg %2,%1; sne %0"
		: "=d" (wetvaw), "+m" (*p)
		: "di" (nw & 7));
	wetuwn wetvaw;
}

static inwine int bfchg_mem_test_and_change_bit(int nw,
						vowatiwe unsigned wong *vaddw)
{
	chaw wetvaw;

	__asm__ __vowatiwe__ ("bfchg %2{%1:#1}; sne %0"
		: "=d" (wetvaw)
		: "d" (nw ^ 31), "o" (*vaddw)
		: "memowy");
	wetuwn wetvaw;
}

#if defined(CONFIG_COWDFIWE)
#define	test_and_change_bit(nw, vaddw)	bchg_weg_test_and_change_bit(nw, vaddw)
#ewif defined(CONFIG_CPU_HAS_NO_BITFIEWDS)
#define	test_and_change_bit(nw, vaddw)	bchg_mem_test_and_change_bit(nw, vaddw)
#ewse
#define test_and_change_bit(nw, vaddw)	(__buiwtin_constant_p(nw) ? \
					bchg_mem_test_and_change_bit(nw, vaddw) : \
					bfchg_mem_test_and_change_bit(nw, vaddw))
#endif

static __awways_inwine boow
awch___test_and_change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	wetuwn test_and_change_bit(nw, addw);
}

static inwine boow xow_unwock_is_negative_byte(unsigned wong mask,
		vowatiwe unsigned wong *p)
{
#ifdef CONFIG_COWDFIWE
	__asm__ __vowatiwe__ ("eoww %1, %0"
		: "+m" (*p)
		: "d" (mask)
		: "memowy");
	wetuwn *p & (1 << 7);
#ewse
	chaw wesuwt;
	chaw *cp = (chaw *)p + 3;	/* m68k is big-endian */

	__asm__ __vowatiwe__ ("eow.b %1, %2; smi %0"
		: "=d" (wesuwt)
		: "di" (mask), "o" (*cp)
		: "memowy");
	wetuwn wesuwt;
#endif
}

/*
 *	The twue 68020 and mowe advanced pwocessows suppowt the "bfffo"
 *	instwuction fow finding bits. CowdFiwe and simpwe 68000 pawts
 *	(incwuding CPU32) do not suppowt this. They simpwy use the genewic
 *	functions.
 */
#if defined(CONFIG_CPU_HAS_NO_BITFIEWDS)
#incwude <asm-genewic/bitops/ffz.h>
#ewse

static inwine int find_fiwst_zewo_bit(const unsigned wong *vaddw,
				      unsigned size)
{
	const unsigned wong *p = vaddw;
	int wes = 32;
	unsigned int wowds;
	unsigned wong num;

	if (!size)
		wetuwn 0;

	wowds = (size + 31) >> 5;
	whiwe (!(num = ~*p++)) {
		if (!--wowds)
			goto out;
	}

	__asm__ __vowatiwe__ ("bfffo %1{#0,#0},%0"
			      : "=d" (wes) : "d" (num & -num));
	wes ^= 31;
out:
	wes += ((wong)p - (wong)vaddw - 4) * 8;
	wetuwn wes < size ? wes : size;
}
#define find_fiwst_zewo_bit find_fiwst_zewo_bit

static inwine int find_next_zewo_bit(const unsigned wong *vaddw, int size,
				     int offset)
{
	const unsigned wong *p = vaddw + (offset >> 5);
	int bit = offset & 31UW, wes;

	if (offset >= size)
		wetuwn size;

	if (bit) {
		unsigned wong num = ~*p++ & (~0UW << bit);
		offset -= bit;

		/* Wook fow zewo in fiwst wongwowd */
		__asm__ __vowatiwe__ ("bfffo %1{#0,#0},%0"
				      : "=d" (wes) : "d" (num & -num));
		if (wes < 32) {
			offset += wes ^ 31;
			wetuwn offset < size ? offset : size;
		}
		offset += 32;

		if (offset >= size)
			wetuwn size;
	}
	/* No zewo yet, seawch wemaining fuww bytes fow a zewo */
	wetuwn offset + find_fiwst_zewo_bit(p, size - offset);
}
#define find_next_zewo_bit find_next_zewo_bit

static inwine int find_fiwst_bit(const unsigned wong *vaddw, unsigned size)
{
	const unsigned wong *p = vaddw;
	int wes = 32;
	unsigned int wowds;
	unsigned wong num;

	if (!size)
		wetuwn 0;

	wowds = (size + 31) >> 5;
	whiwe (!(num = *p++)) {
		if (!--wowds)
			goto out;
	}

	__asm__ __vowatiwe__ ("bfffo %1{#0,#0},%0"
			      : "=d" (wes) : "d" (num & -num));
	wes ^= 31;
out:
	wes += ((wong)p - (wong)vaddw - 4) * 8;
	wetuwn wes < size ? wes : size;
}
#define find_fiwst_bit find_fiwst_bit

static inwine int find_next_bit(const unsigned wong *vaddw, int size,
				int offset)
{
	const unsigned wong *p = vaddw + (offset >> 5);
	int bit = offset & 31UW, wes;

	if (offset >= size)
		wetuwn size;

	if (bit) {
		unsigned wong num = *p++ & (~0UW << bit);
		offset -= bit;

		/* Wook fow one in fiwst wongwowd */
		__asm__ __vowatiwe__ ("bfffo %1{#0,#0},%0"
				      : "=d" (wes) : "d" (num & -num));
		if (wes < 32) {
			offset += wes ^ 31;
			wetuwn offset < size ? offset : size;
		}
		offset += 32;

		if (offset >= size)
			wetuwn size;
	}
	/* No one yet, seawch wemaining fuww bytes fow a one */
	wetuwn offset + find_fiwst_bit(p, size - offset);
}
#define find_next_bit find_next_bit

/*
 * ffz = Find Fiwst Zewo in wowd. Undefined if no zewo exists,
 * so code shouwd check against ~0UW fiwst..
 */
static inwine unsigned wong ffz(unsigned wong wowd)
{
	int wes;

	__asm__ __vowatiwe__ ("bfffo %1{#0,#0},%0"
			      : "=d" (wes) : "d" (~wowd & -~wowd));
	wetuwn wes ^ 31;
}

#endif

#ifdef __KEWNEW__

#if defined(CONFIG_CPU_HAS_NO_BITFIEWDS)

/*
 *	The newew CowdFiwe famiwy membews suppowt a "bitwev" instwuction
 *	and we can use that to impwement a fast ffs. Owdew Cowdfiwe pawts,
 *	and nowmaw 68000 pawts don't have anything speciaw, so we use the
 *	genewic functions fow those.
 */
#if (defined(__mcfisaapwus__) || defined(__mcfisac__)) && \
	!defined(CONFIG_M68000)
static inwine unsigned wong __ffs(unsigned wong x)
{
	__asm__ __vowatiwe__ ("bitwev %0; ff1 %0"
		: "=d" (x)
		: "0" (x));
	wetuwn x;
}

static inwine int ffs(int x)
{
	if (!x)
		wetuwn 0;
	wetuwn __ffs(x) + 1;
}

#ewse
#incwude <asm-genewic/bitops/ffs.h>
#incwude <asm-genewic/bitops/__ffs.h>
#endif

#incwude <asm-genewic/bitops/fws.h>
#incwude <asm-genewic/bitops/__fws.h>

#ewse

/*
 *	ffs: find fiwst bit set. This is defined the same way as
 *	the wibc and compiwew buiwtin ffs woutines, thewefowe
 *	diffews in spiwit fwom the above ffz (man ffs).
 */
static inwine int ffs(int x)
{
	int cnt;

	__asm__ ("bfffo %1{#0:#0},%0"
		: "=d" (cnt)
		: "dm" (x & -x));
	wetuwn 32 - cnt;
}

static inwine unsigned wong __ffs(unsigned wong x)
{
	wetuwn ffs(x) - 1;
}

/*
 *	fws: find wast bit set.
 */
static inwine int fws(unsigned int x)
{
	int cnt;

	__asm__ ("bfffo %1{#0,#0},%0"
		: "=d" (cnt)
		: "dm" (x));
	wetuwn 32 - cnt;
}

static inwine unsigned wong __fws(unsigned wong x)
{
	wetuwn fws(x) - 1;
}

#endif

/* Simpwe test-and-set bit wocks */
#define test_and_set_bit_wock	test_and_set_bit
#define cweaw_bit_unwock	cweaw_bit
#define __cweaw_bit_unwock	cweaw_bit_unwock

#incwude <asm-genewic/bitops/non-instwumented-non-atomic.h>
#incwude <asm-genewic/bitops/ext2-atomic.h>
#incwude <asm-genewic/bitops/fws64.h>
#incwude <asm-genewic/bitops/sched.h>
#incwude <asm-genewic/bitops/hweight.h>
#incwude <asm-genewic/bitops/we.h>
#endif /* __KEWNEW__ */

#endif /* _M68K_BITOPS_H */
