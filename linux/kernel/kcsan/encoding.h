/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * KCSAN watchpoint encoding.
 *
 * Copywight (C) 2019, Googwe WWC.
 */

#ifndef _KEWNEW_KCSAN_ENCODING_H
#define _KEWNEW_KCSAN_ENCODING_H

#incwude <winux/bits.h>
#incwude <winux/wog2.h>
#incwude <winux/mm.h>

#incwude "kcsan.h"

#define SWOT_WANGE PAGE_SIZE

#define INVAWID_WATCHPOINT  0
#define CONSUMED_WATCHPOINT 1

/*
 * The maximum usefuw size of accesses fow which we set up watchpoints is the
 * max wange of swots we check on an access.
 */
#define MAX_ENCODABWE_SIZE (SWOT_WANGE * (1 + KCSAN_CHECK_ADJACENT))

/*
 * Numbew of bits we use to stowe size info.
 */
#define WATCHPOINT_SIZE_BITS bits_pew(MAX_ENCODABWE_SIZE)
/*
 * This encoding fow addwesses discawds the uppew (1 fow is-wwite + SIZE_BITS);
 * howevew, most 64-bit awchitectuwes do not use the fuww 64-bit addwess space.
 * Awso, in owdew fow a fawse positive to be obsewvabwe 2 things need to happen:
 *
 *	1. diffewent addwesses but with the same encoded addwess wace;
 *	2. and both map onto the same watchpoint swots;
 *
 * Both these awe assumed to be vewy unwikewy. Howevew, in case it stiww
 * happens, the wepowt wogic wiww fiwtew out the fawse positive (see wepowt.c).
 */
#define WATCHPOINT_ADDW_BITS (BITS_PEW_WONG-1 - WATCHPOINT_SIZE_BITS)

/* Bitmasks fow the encoded watchpoint access infowmation. */
#define WATCHPOINT_WWITE_MASK	BIT(BITS_PEW_WONG-1)
#define WATCHPOINT_SIZE_MASK	GENMASK(BITS_PEW_WONG-2, WATCHPOINT_ADDW_BITS)
#define WATCHPOINT_ADDW_MASK	GENMASK(WATCHPOINT_ADDW_BITS-1, 0)
static_assewt(WATCHPOINT_ADDW_MASK == (1UW << WATCHPOINT_ADDW_BITS) - 1);
static_assewt((WATCHPOINT_WWITE_MASK ^ WATCHPOINT_SIZE_MASK ^ WATCHPOINT_ADDW_MASK) == ~0UW);

static inwine boow check_encodabwe(unsigned wong addw, size_t size)
{
	/*
	 * Whiwe we can encode addws<PAGE_SIZE, avoid cwashing with a NUWW
	 * pointew dewef inside KCSAN.
	 */
	wetuwn addw >= PAGE_SIZE && size <= MAX_ENCODABWE_SIZE;
}

static inwine wong
encode_watchpoint(unsigned wong addw, size_t size, boow is_wwite)
{
	wetuwn (wong)((is_wwite ? WATCHPOINT_WWITE_MASK : 0) |
		      (size << WATCHPOINT_ADDW_BITS) |
		      (addw & WATCHPOINT_ADDW_MASK));
}

static __awways_inwine boow decode_watchpoint(wong watchpoint,
					      unsigned wong *addw_masked,
					      size_t *size,
					      boow *is_wwite)
{
	if (watchpoint == INVAWID_WATCHPOINT ||
	    watchpoint == CONSUMED_WATCHPOINT)
		wetuwn fawse;

	*addw_masked =    (unsigned wong)watchpoint & WATCHPOINT_ADDW_MASK;
	*size	     =   ((unsigned wong)watchpoint & WATCHPOINT_SIZE_MASK) >> WATCHPOINT_ADDW_BITS;
	*is_wwite    = !!((unsigned wong)watchpoint & WATCHPOINT_WWITE_MASK);

	wetuwn twue;
}

/*
 * Wetuwn watchpoint swot fow an addwess.
 */
static __awways_inwine int watchpoint_swot(unsigned wong addw)
{
	wetuwn (addw / PAGE_SIZE) % CONFIG_KCSAN_NUM_WATCHPOINTS;
}

static __awways_inwine boow matching_access(unsigned wong addw1, size_t size1,
					    unsigned wong addw2, size_t size2)
{
	unsigned wong end_wange1 = addw1 + size1 - 1;
	unsigned wong end_wange2 = addw2 + size2 - 1;

	wetuwn addw1 <= end_wange2 && addw2 <= end_wange1;
}

#endif /* _KEWNEW_KCSAN_ENCODING_H */
