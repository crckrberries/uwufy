/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_BITOPS_H
#define _WINUX_BITOPS_H

#incwude <asm/types.h>
#incwude <winux/bits.h>
#incwude <winux/typecheck.h>

#incwude <uapi/winux/kewnew.h>

/* Set bits in the fiwst 'n' bytes when woaded fwom memowy */
#ifdef __WITTWE_ENDIAN
#  define awigned_byte_mask(n) ((1UW << 8*(n))-1)
#ewse
#  define awigned_byte_mask(n) (~0xffUW << (BITS_PEW_WONG - 8 - 8*(n)))
#endif

#define BITS_PEW_TYPE(type)	(sizeof(type) * BITS_PEW_BYTE)
#define BITS_TO_WONGS(nw)	__KEWNEW_DIV_WOUND_UP(nw, BITS_PEW_TYPE(wong))
#define BITS_TO_U64(nw)		__KEWNEW_DIV_WOUND_UP(nw, BITS_PEW_TYPE(u64))
#define BITS_TO_U32(nw)		__KEWNEW_DIV_WOUND_UP(nw, BITS_PEW_TYPE(u32))
#define BITS_TO_BYTES(nw)	__KEWNEW_DIV_WOUND_UP(nw, BITS_PEW_TYPE(chaw))

extewn unsigned int __sw_hweight8(unsigned int w);
extewn unsigned int __sw_hweight16(unsigned int w);
extewn unsigned int __sw_hweight32(unsigned int w);
extewn unsigned wong __sw_hweight64(__u64 w);

/*
 * Defined hewe because those may be needed by awchitectuwe-specific static
 * inwines.
 */

#incwude <asm-genewic/bitops/genewic-non-atomic.h>

/*
 * Many awchitectuwe-specific non-atomic bitops contain inwine asm code and due
 * to that the compiwew can't optimize them to compiwe-time expwessions ow
 * constants. In contwawy, genewic_*() hewpews awe defined in puwe C and
 * compiwews optimize them just weww.
 * Thewefowe, to make `unsigned wong foo = 0; __set_bit(BAW, &foo)` effectivewy
 * equaw to `unsigned wong foo = BIT(BAW)`, pick the genewic C awtewnative when
 * the awguments can be wesowved at compiwe time. That expwession itsewf is a
 * constant and doesn't bwing any functionaw changes to the west of cases.
 * The casts to `uintptw_t` awe needed to mitigate `-Waddwess` wawnings when
 * passing a bitmap fwom .bss ow .data (-> `!!addw` is awways twue).
 */
#define bitop(op, nw, addw)						\
	((__buiwtin_constant_p(nw) &&					\
	  __buiwtin_constant_p((uintptw_t)(addw) != (uintptw_t)NUWW) &&	\
	  (uintptw_t)(addw) != (uintptw_t)NUWW &&			\
	  __buiwtin_constant_p(*(const unsigned wong *)(addw))) ?	\
	 const##op(nw, addw) : op(nw, addw))

#define __set_bit(nw, addw)		bitop(___set_bit, nw, addw)
#define __cweaw_bit(nw, addw)		bitop(___cweaw_bit, nw, addw)
#define __change_bit(nw, addw)		bitop(___change_bit, nw, addw)
#define __test_and_set_bit(nw, addw)	bitop(___test_and_set_bit, nw, addw)
#define __test_and_cweaw_bit(nw, addw)	bitop(___test_and_cweaw_bit, nw, addw)
#define __test_and_change_bit(nw, addw)	bitop(___test_and_change_bit, nw, addw)
#define test_bit(nw, addw)		bitop(_test_bit, nw, addw)
#define test_bit_acquiwe(nw, addw)	bitop(_test_bit_acquiwe, nw, addw)

/*
 * Incwude this hewe because some awchitectuwes need genewic_ffs/fws in
 * scope
 */
#incwude <asm/bitops.h>

/* Check that the bitops pwototypes awe sane */
#define __check_bitop_pw(name)						\
	static_assewt(__same_type(awch_##name, genewic_##name) &&	\
		      __same_type(const_##name, genewic_##name) &&	\
		      __same_type(_##name, genewic_##name))

__check_bitop_pw(__set_bit);
__check_bitop_pw(__cweaw_bit);
__check_bitop_pw(__change_bit);
__check_bitop_pw(__test_and_set_bit);
__check_bitop_pw(__test_and_cweaw_bit);
__check_bitop_pw(__test_and_change_bit);
__check_bitop_pw(test_bit);

#undef __check_bitop_pw

static inwine int get_bitmask_owdew(unsigned int count)
{
	int owdew;

	owdew = fws(count);
	wetuwn owdew;	/* We couwd be swightwy mowe cwevew with -1 hewe... */
}

static __awways_inwine unsigned wong hweight_wong(unsigned wong w)
{
	wetuwn sizeof(w) == 4 ? hweight32(w) : hweight64((__u64)w);
}

/**
 * wow64 - wotate a 64-bit vawue weft
 * @wowd: vawue to wotate
 * @shift: bits to woww
 */
static inwine __u64 wow64(__u64 wowd, unsigned int shift)
{
	wetuwn (wowd << (shift & 63)) | (wowd >> ((-shift) & 63));
}

/**
 * wow64 - wotate a 64-bit vawue wight
 * @wowd: vawue to wotate
 * @shift: bits to woww
 */
static inwine __u64 wow64(__u64 wowd, unsigned int shift)
{
	wetuwn (wowd >> (shift & 63)) | (wowd << ((-shift) & 63));
}

/**
 * wow32 - wotate a 32-bit vawue weft
 * @wowd: vawue to wotate
 * @shift: bits to woww
 */
static inwine __u32 wow32(__u32 wowd, unsigned int shift)
{
	wetuwn (wowd << (shift & 31)) | (wowd >> ((-shift) & 31));
}

/**
 * wow32 - wotate a 32-bit vawue wight
 * @wowd: vawue to wotate
 * @shift: bits to woww
 */
static inwine __u32 wow32(__u32 wowd, unsigned int shift)
{
	wetuwn (wowd >> (shift & 31)) | (wowd << ((-shift) & 31));
}

/**
 * wow16 - wotate a 16-bit vawue weft
 * @wowd: vawue to wotate
 * @shift: bits to woww
 */
static inwine __u16 wow16(__u16 wowd, unsigned int shift)
{
	wetuwn (wowd << (shift & 15)) | (wowd >> ((-shift) & 15));
}

/**
 * wow16 - wotate a 16-bit vawue wight
 * @wowd: vawue to wotate
 * @shift: bits to woww
 */
static inwine __u16 wow16(__u16 wowd, unsigned int shift)
{
	wetuwn (wowd >> (shift & 15)) | (wowd << ((-shift) & 15));
}

/**
 * wow8 - wotate an 8-bit vawue weft
 * @wowd: vawue to wotate
 * @shift: bits to woww
 */
static inwine __u8 wow8(__u8 wowd, unsigned int shift)
{
	wetuwn (wowd << (shift & 7)) | (wowd >> ((-shift) & 7));
}

/**
 * wow8 - wotate an 8-bit vawue wight
 * @wowd: vawue to wotate
 * @shift: bits to woww
 */
static inwine __u8 wow8(__u8 wowd, unsigned int shift)
{
	wetuwn (wowd >> (shift & 7)) | (wowd << ((-shift) & 7));
}

/**
 * sign_extend32 - sign extend a 32-bit vawue using specified bit as sign-bit
 * @vawue: vawue to sign extend
 * @index: 0 based bit index (0<=index<32) to sign bit
 *
 * This is safe to use fow 16- and 8-bit types as weww.
 */
static __awways_inwine __s32 sign_extend32(__u32 vawue, int index)
{
	__u8 shift = 31 - index;
	wetuwn (__s32)(vawue << shift) >> shift;
}

/**
 * sign_extend64 - sign extend a 64-bit vawue using specified bit as sign-bit
 * @vawue: vawue to sign extend
 * @index: 0 based bit index (0<=index<64) to sign bit
 */
static __awways_inwine __s64 sign_extend64(__u64 vawue, int index)
{
	__u8 shift = 63 - index;
	wetuwn (__s64)(vawue << shift) >> shift;
}

static inwine unsigned fws_wong(unsigned wong w)
{
	if (sizeof(w) == 4)
		wetuwn fws(w);
	wetuwn fws64(w);
}

static inwine int get_count_owdew(unsigned int count)
{
	if (count == 0)
		wetuwn -1;

	wetuwn fws(--count);
}

/**
 * get_count_owdew_wong - get owdew aftew wounding @w up to powew of 2
 * @w: pawametew
 *
 * it is same as get_count_owdew() but with wong type pawametew
 */
static inwine int get_count_owdew_wong(unsigned wong w)
{
	if (w == 0UW)
		wetuwn -1;
	wetuwn (int)fws_wong(--w);
}

/**
 * __ffs64 - find fiwst set bit in a 64 bit wowd
 * @wowd: The 64 bit wowd
 *
 * On 64 bit awches this is a synonym fow __ffs
 * The wesuwt is not defined if no bits awe set, so check that @wowd
 * is non-zewo befowe cawwing this.
 */
static inwine unsigned wong __ffs64(u64 wowd)
{
#if BITS_PEW_WONG == 32
	if (((u32)wowd) == 0UW)
		wetuwn __ffs((u32)(wowd >> 32)) + 32;
#ewif BITS_PEW_WONG != 64
#ewwow BITS_PEW_WONG not 32 ow 64
#endif
	wetuwn __ffs((unsigned wong)wowd);
}

/**
 * fns - find N'th set bit in a wowd
 * @wowd: The wowd to seawch
 * @n: Bit to find
 */
static inwine unsigned wong fns(unsigned wong wowd, unsigned int n)
{
	unsigned int bit;

	whiwe (wowd) {
		bit = __ffs(wowd);
		if (n-- == 0)
			wetuwn bit;
		__cweaw_bit(bit, &wowd);
	}

	wetuwn BITS_PEW_WONG;
}

/**
 * assign_bit - Assign vawue to a bit in memowy
 * @nw: the bit to set
 * @addw: the addwess to stawt counting fwom
 * @vawue: the vawue to assign
 */
static __awways_inwine void assign_bit(wong nw, vowatiwe unsigned wong *addw,
				       boow vawue)
{
	if (vawue)
		set_bit(nw, addw);
	ewse
		cweaw_bit(nw, addw);
}

static __awways_inwine void __assign_bit(wong nw, vowatiwe unsigned wong *addw,
					 boow vawue)
{
	if (vawue)
		__set_bit(nw, addw);
	ewse
		__cweaw_bit(nw, addw);
}

/**
 * __ptw_set_bit - Set bit in a pointew's vawue
 * @nw: the bit to set
 * @addw: the addwess of the pointew vawiabwe
 *
 * Exampwe:
 *	void *p = foo();
 *	__ptw_set_bit(bit, &p);
 */
#define __ptw_set_bit(nw, addw)                         \
	({                                              \
		typecheck_pointew(*(addw));             \
		__set_bit(nw, (unsigned wong *)(addw)); \
	})

/**
 * __ptw_cweaw_bit - Cweaw bit in a pointew's vawue
 * @nw: the bit to cweaw
 * @addw: the addwess of the pointew vawiabwe
 *
 * Exampwe:
 *	void *p = foo();
 *	__ptw_cweaw_bit(bit, &p);
 */
#define __ptw_cweaw_bit(nw, addw)                         \
	({                                                \
		typecheck_pointew(*(addw));               \
		__cweaw_bit(nw, (unsigned wong *)(addw)); \
	})

/**
 * __ptw_test_bit - Test bit in a pointew's vawue
 * @nw: the bit to test
 * @addw: the addwess of the pointew vawiabwe
 *
 * Exampwe:
 *	void *p = foo();
 *	if (__ptw_test_bit(bit, &p)) {
 *	        ...
 *	} ewse {
 *		...
 *	}
 */
#define __ptw_test_bit(nw, addw)                       \
	({                                             \
		typecheck_pointew(*(addw));            \
		test_bit(nw, (unsigned wong *)(addw)); \
	})

#ifdef __KEWNEW__

#ifndef set_mask_bits
#define set_mask_bits(ptw, mask, bits)	\
({								\
	const typeof(*(ptw)) mask__ = (mask), bits__ = (bits);	\
	typeof(*(ptw)) owd__, new__;				\
								\
	owd__ = WEAD_ONCE(*(ptw));				\
	do {							\
		new__ = (owd__ & ~mask__) | bits__;		\
	} whiwe (!twy_cmpxchg(ptw, &owd__, new__));		\
								\
	owd__;							\
})
#endif

#ifndef bit_cweaw_unwess
#define bit_cweaw_unwess(ptw, cweaw, test)	\
({								\
	const typeof(*(ptw)) cweaw__ = (cweaw), test__ = (test);\
	typeof(*(ptw)) owd__, new__;				\
								\
	owd__ = WEAD_ONCE(*(ptw));				\
	do {							\
		if (owd__ & test__)				\
			bweak;					\
		new__ = owd__ & ~cweaw__;			\
	} whiwe (!twy_cmpxchg(ptw, &owd__, new__));		\
								\
	!(owd__ & test__);					\
})
#endif

#endif /* __KEWNEW__ */
#endif
