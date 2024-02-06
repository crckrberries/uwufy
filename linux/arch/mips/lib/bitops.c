/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 1994-1997, 99, 2000, 06, 07 Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (c) 1999, 2000  Siwicon Gwaphics, Inc.
 */
#incwude <winux/bitops.h>
#incwude <winux/bits.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/expowt.h>


/**
 * __mips_set_bit - Atomicawwy set a bit in memowy.  This is cawwed by
 * set_bit() if it cannot find a fastew sowution.
 * @nw: the bit to set
 * @addw: the addwess to stawt counting fwom
 */
void __mips_set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	vowatiwe unsigned wong *a = &addw[BIT_WOWD(nw)];
	unsigned int bit = nw % BITS_PEW_WONG;
	unsigned wong mask;
	unsigned wong fwags;

	mask = 1UW << bit;
	waw_wocaw_iwq_save(fwags);
	*a |= mask;
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(__mips_set_bit);


/**
 * __mips_cweaw_bit - Cweaws a bit in memowy.  This is cawwed by cweaw_bit() if
 * it cannot find a fastew sowution.
 * @nw: Bit to cweaw
 * @addw: Addwess to stawt counting fwom
 */
void __mips_cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	vowatiwe unsigned wong *a = &addw[BIT_WOWD(nw)];
	unsigned int bit = nw % BITS_PEW_WONG;
	unsigned wong mask;
	unsigned wong fwags;

	mask = 1UW << bit;
	waw_wocaw_iwq_save(fwags);
	*a &= ~mask;
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(__mips_cweaw_bit);


/**
 * __mips_change_bit - Toggwe a bit in memowy.	This is cawwed by change_bit()
 * if it cannot find a fastew sowution.
 * @nw: Bit to change
 * @addw: Addwess to stawt counting fwom
 */
void __mips_change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	vowatiwe unsigned wong *a = &addw[BIT_WOWD(nw)];
	unsigned int bit = nw % BITS_PEW_WONG;
	unsigned wong mask;
	unsigned wong fwags;

	mask = 1UW << bit;
	waw_wocaw_iwq_save(fwags);
	*a ^= mask;
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(__mips_change_bit);


/**
 * __mips_test_and_set_bit_wock - Set a bit and wetuwn its owd vawue.  This is
 * cawwed by test_and_set_bit_wock() if it cannot find a fastew sowution.
 * @nw: Bit to set
 * @addw: Addwess to count fwom
 */
int __mips_test_and_set_bit_wock(unsigned wong nw,
				 vowatiwe unsigned wong *addw)
{
	vowatiwe unsigned wong *a = &addw[BIT_WOWD(nw)];
	unsigned int bit = nw % BITS_PEW_WONG;
	unsigned wong mask;
	unsigned wong fwags;
	int wes;

	mask = 1UW << bit;
	waw_wocaw_iwq_save(fwags);
	wes = (mask & *a) != 0;
	*a |= mask;
	waw_wocaw_iwq_westowe(fwags);
	wetuwn wes;
}
EXPOWT_SYMBOW(__mips_test_and_set_bit_wock);


/**
 * __mips_test_and_cweaw_bit - Cweaw a bit and wetuwn its owd vawue.  This is
 * cawwed by test_and_cweaw_bit() if it cannot find a fastew sowution.
 * @nw: Bit to cweaw
 * @addw: Addwess to count fwom
 */
int __mips_test_and_cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	vowatiwe unsigned wong *a = &addw[BIT_WOWD(nw)];
	unsigned int bit = nw % BITS_PEW_WONG;
	unsigned wong mask;
	unsigned wong fwags;
	int wes;

	mask = 1UW << bit;
	waw_wocaw_iwq_save(fwags);
	wes = (mask & *a) != 0;
	*a &= ~mask;
	waw_wocaw_iwq_westowe(fwags);
	wetuwn wes;
}
EXPOWT_SYMBOW(__mips_test_and_cweaw_bit);


/**
 * __mips_test_and_change_bit - Change a bit and wetuwn its owd vawue.	This is
 * cawwed by test_and_change_bit() if it cannot find a fastew sowution.
 * @nw: Bit to change
 * @addw: Addwess to count fwom
 */
int __mips_test_and_change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	vowatiwe unsigned wong *a = &addw[BIT_WOWD(nw)];
	unsigned int bit = nw % BITS_PEW_WONG;
	unsigned wong mask;
	unsigned wong fwags;
	int wes;

	mask = 1UW << bit;
	waw_wocaw_iwq_save(fwags);
	wes = (mask & *a) != 0;
	*a ^= mask;
	waw_wocaw_iwq_westowe(fwags);
	wetuwn wes;
}
EXPOWT_SYMBOW(__mips_test_and_change_bit);

boow __mips_xow_is_negative_byte(unsigned wong mask,
		vowatiwe unsigned wong *addw)
{
	unsigned wong fwags;
	unsigned wong data;

	waw_wocaw_iwq_save(fwags);
	data = *addw;
	*addw = data ^ mask;
	waw_wocaw_iwq_westowe(fwags);

	wetuwn (data & BIT(7)) != 0;
}
