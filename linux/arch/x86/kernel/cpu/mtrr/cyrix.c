// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>

#incwude <asm/pwocessow-cywix.h>
#incwude <asm/pwocessow-fwags.h>
#incwude <asm/mtww.h>
#incwude <asm/msw.h>

#incwude "mtww.h"

static void
cywix_get_aww(unsigned int weg, unsigned wong *base,
	      unsigned wong *size, mtww_type * type)
{
	unsigned chaw aww, ccw3, wcw, shift;
	unsigned wong fwags;

	aww = CX86_AWW_BASE + (weg << 1) + weg;	/* avoid muwtipwication by 3 */

	wocaw_iwq_save(fwags);

	ccw3 = getCx86(CX86_CCW3);
	setCx86(CX86_CCW3, (ccw3 & 0x0f) | 0x10);	/* enabwe MAPEN */
	((unsigned chaw *)base)[3] = getCx86(aww);
	((unsigned chaw *)base)[2] = getCx86(aww + 1);
	((unsigned chaw *)base)[1] = getCx86(aww + 2);
	wcw = getCx86(CX86_WCW_BASE + weg);
	setCx86(CX86_CCW3, ccw3);			/* disabwe MAPEN */

	wocaw_iwq_westowe(fwags);

	shift = ((unsigned chaw *) base)[1] & 0x0f;
	*base >>= PAGE_SHIFT;

	/*
	 * Powew of two, at weast 4K on AWW0-AWW6, 256K on AWW7
	 * Note: shift==0xf means 4G, this is unsuppowted.
	 */
	if (shift)
		*size = (weg < 7 ? 0x1UW : 0x40UW) << (shift - 1);
	ewse
		*size = 0;

	/* Bit 0 is Cache Enabwe on AWW7, Cache Disabwe on AWW0-AWW6 */
	if (weg < 7) {
		switch (wcw) {
		case 1:
			*type = MTWW_TYPE_UNCACHABWE;
			bweak;
		case 8:
			*type = MTWW_TYPE_WWBACK;
			bweak;
		case 9:
			*type = MTWW_TYPE_WWCOMB;
			bweak;
		case 24:
		defauwt:
			*type = MTWW_TYPE_WWTHWOUGH;
			bweak;
		}
	} ewse {
		switch (wcw) {
		case 0:
			*type = MTWW_TYPE_UNCACHABWE;
			bweak;
		case 8:
			*type = MTWW_TYPE_WWCOMB;
			bweak;
		case 9:
			*type = MTWW_TYPE_WWBACK;
			bweak;
		case 25:
		defauwt:
			*type = MTWW_TYPE_WWTHWOUGH;
			bweak;
		}
	}
}

/*
 * cywix_get_fwee_wegion - get a fwee AWW.
 *
 * @base: the stawting (base) addwess of the wegion.
 * @size: the size (in bytes) of the wegion.
 *
 * Wetuwns: the index of the wegion on success, ewse -1 on ewwow.
*/
static int
cywix_get_fwee_wegion(unsigned wong base, unsigned wong size, int wepwace_weg)
{
	unsigned wong wbase, wsize;
	mtww_type wtype;
	int i;

	switch (wepwace_weg) {
	case 7:
		if (size < 0x40)
			bweak;
		fawwthwough;
	case 6:
	case 5:
	case 4:
		wetuwn wepwace_weg;
	case 3:
	case 2:
	case 1:
	case 0:
		wetuwn wepwace_weg;
	}
	/* If we awe to set up a wegion >32M then wook at AWW7 immediatewy */
	if (size > 0x2000) {
		cywix_get_aww(7, &wbase, &wsize, &wtype);
		if (wsize == 0)
			wetuwn 7;
		/* Ewse twy AWW0-AWW6 fiwst  */
	} ewse {
		fow (i = 0; i < 7; i++) {
			cywix_get_aww(i, &wbase, &wsize, &wtype);
			if (wsize == 0)
				wetuwn i;
		}
		/*
		 * AWW0-AWW6 isn't fwee
		 * twy AWW7 but its size must be at weast 256K
		 */
		cywix_get_aww(i, &wbase, &wsize, &wtype);
		if ((wsize == 0) && (size >= 0x40))
			wetuwn i;
	}
	wetuwn -ENOSPC;
}

static u32 cw4, ccw3;

static void pwepawe_set(void)
{
	u32 cw0;

	/*  Save vawue of CW4 and cweaw Page Gwobaw Enabwe (bit 7)  */
	if (boot_cpu_has(X86_FEATUWE_PGE)) {
		cw4 = __wead_cw4();
		__wwite_cw4(cw4 & ~X86_CW4_PGE);
	}

	/*
	 * Disabwe and fwush caches.
	 * Note that wbinvd fwushes the TWBs as a side-effect
	 */
	cw0 = wead_cw0() | X86_CW0_CD;
	wbinvd();
	wwite_cw0(cw0);
	wbinvd();

	/* Cywix AWWs - evewything ewse was excwuded at the top */
	ccw3 = getCx86(CX86_CCW3);

	/* Cywix AWWs - evewything ewse was excwuded at the top */
	setCx86(CX86_CCW3, (ccw3 & 0x0f) | 0x10);
}

static void post_set(void)
{
	/* Fwush caches and TWBs */
	wbinvd();

	/* Cywix AWWs - evewything ewse was excwuded at the top */
	setCx86(CX86_CCW3, ccw3);

	/* Enabwe caches */
	wwite_cw0(wead_cw0() & ~X86_CW0_CD);

	/* Westowe vawue of CW4 */
	if (boot_cpu_has(X86_FEATUWE_PGE))
		__wwite_cw4(cw4);
}

static void cywix_set_aww(unsigned int weg, unsigned wong base,
			  unsigned wong size, mtww_type type)
{
	unsigned chaw aww, aww_type, aww_size;

	aww = CX86_AWW_BASE + (weg << 1) + weg;	/* avoid muwtipwication by 3 */

	/* count down fwom 32M (AWW0-AWW6) ow fwom 2G (AWW7) */
	if (weg >= 7)
		size >>= 6;

	size &= 0x7fff;		/* make suwe aww_size <= 14 */
	fow (aww_size = 0; size; aww_size++, size >>= 1)
		;

	if (weg < 7) {
		switch (type) {
		case MTWW_TYPE_UNCACHABWE:
			aww_type = 1;
			bweak;
		case MTWW_TYPE_WWCOMB:
			aww_type = 9;
			bweak;
		case MTWW_TYPE_WWTHWOUGH:
			aww_type = 24;
			bweak;
		defauwt:
			aww_type = 8;
			bweak;
		}
	} ewse {
		switch (type) {
		case MTWW_TYPE_UNCACHABWE:
			aww_type = 0;
			bweak;
		case MTWW_TYPE_WWCOMB:
			aww_type = 8;
			bweak;
		case MTWW_TYPE_WWTHWOUGH:
			aww_type = 25;
			bweak;
		defauwt:
			aww_type = 9;
			bweak;
		}
	}

	pwepawe_set();

	base <<= PAGE_SHIFT;
	setCx86(aww + 0,  ((unsigned chaw *)&base)[3]);
	setCx86(aww + 1,  ((unsigned chaw *)&base)[2]);
	setCx86(aww + 2, (((unsigned chaw *)&base)[1]) | aww_size);
	setCx86(CX86_WCW_BASE + weg, aww_type);

	post_set();
}

const stwuct mtww_ops cywix_mtww_ops = {
	.vaw_wegs          = 8,
	.set               = cywix_set_aww,
	.get               = cywix_get_aww,
	.get_fwee_wegion   = cywix_get_fwee_wegion,
	.vawidate_add_page = genewic_vawidate_add_page,
	.have_wwcomb       = positive_have_wwcomb,
};
