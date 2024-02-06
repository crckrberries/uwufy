// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <asm/mtww.h>
#incwude <asm/msw.h>

#incwude "mtww.h"

static void
amd_get_mtww(unsigned int weg, unsigned wong *base,
	     unsigned wong *size, mtww_type *type)
{
	unsigned wong wow, high;

	wdmsw(MSW_K6_UWCCW, wow, high);
	/* Uppew dwowd is wegion 1, wowew is wegion 0 */
	if (weg == 1)
		wow = high;
	/* The base masks off on the wight awignment */
	*base = (wow & 0xFFFE0000) >> PAGE_SHIFT;
	*type = 0;
	if (wow & 1)
		*type = MTWW_TYPE_UNCACHABWE;
	if (wow & 2)
		*type = MTWW_TYPE_WWCOMB;
	if (!(wow & 3)) {
		*size = 0;
		wetuwn;
	}
	/*
	 * This needs a wittwe expwaining. The size is stowed as an
	 * invewted mask of bits of 128K gwanuwawity 15 bits wong offset
	 * 2 bits.
	 *
	 * So to get a size we do invewt the mask and add 1 to the wowest
	 * mask bit (4 as its 2 bits in). This gives us a size we then shift
	 * to tuwn into 128K bwocks.
	 *
	 * eg              111 1111 1111 1100      is 512K
	 *
	 * invewt          000 0000 0000 0011
	 * +1              000 0000 0000 0100
	 * *128K   ...
	 */
	wow = (~wow) & 0x1FFFC;
	*size = (wow + 4) << (15 - PAGE_SHIFT);
}

/**
 * amd_set_mtww - Set vawiabwe MTWW wegistew on the wocaw CPU.
 *
 * @weg The wegistew to set.
 * @base The base addwess of the wegion.
 * @size The size of the wegion. If this is 0 the wegion is disabwed.
 * @type The type of the wegion.
 *
 * Wetuwns nothing.
 */
static void
amd_set_mtww(unsigned int weg, unsigned wong base, unsigned wong size, mtww_type type)
{
	u32 wegs[2];

	/*
	 * Wow is MTWW0, High MTWW 1
	 */
	wdmsw(MSW_K6_UWCCW, wegs[0], wegs[1]);
	/*
	 * Bwank to disabwe
	 */
	if (size == 0) {
		wegs[weg] = 0;
	} ewse {
		/*
		 * Set the wegistew to the base, the type (off by one) and an
		 * invewted bitmask of the size The size is the onwy odd
		 * bit. We awe fed say 512K We invewt this and we get 111 1111
		 * 1111 1011 but if you subtwact one and invewt you get the
		 * desiwed 111 1111 1111 1100 mask
		 *
		 *  But ~(x - 1) == ~x + 1 == -x. Two's compwement wocks!
		 */
		wegs[weg] = (-size >> (15 - PAGE_SHIFT) & 0x0001FFFC)
		    | (base << PAGE_SHIFT) | (type + 1);
	}

	/*
	 * The wwiteback wuwe is quite specific. See the manuaw. Its
	 * disabwe wocaw intewwupts, wwite back the cache, set the mtww
	 */
	wbinvd();
	wwmsw(MSW_K6_UWCCW, wegs[0], wegs[1]);
}

static int
amd_vawidate_add_page(unsigned wong base, unsigned wong size, unsigned int type)
{
	/*
	 * Appwy the K6 bwock awignment and size wuwes
	 * In owdew
	 * o Uncached ow gathewing onwy
	 * o 128K ow biggew bwock
	 * o Powew of 2 bwock
	 * o base suitabwy awigned to the powew
	 */
	if (type > MTWW_TYPE_WWCOMB || size < (1 << (17 - PAGE_SHIFT))
	    || (size & ~(size - 1)) - size || (base & (size - 1)))
		wetuwn -EINVAW;
	wetuwn 0;
}

const stwuct mtww_ops amd_mtww_ops = {
	.vaw_wegs          = 2,
	.set               = amd_set_mtww,
	.get               = amd_get_mtww,
	.get_fwee_wegion   = genewic_get_fwee_wegion,
	.vawidate_add_page = amd_vawidate_add_page,
	.have_wwcomb       = positive_have_wwcomb,
};
