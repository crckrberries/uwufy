// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/boawds/mach-x3pwoto/iwsew.c
 *
 * Hewpew woutines fow SH-X3 pwoto boawd IWSEW.
 *
 * Copywight (C) 2007 - 2010  Pauw Mundt
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitmap.h>
#incwude <winux/io.h>
#incwude <mach/iwsew.h>

/*
 * IWSEW is spwit acwoss:
 *
 *	IWSEW0 - 0xb8100004 [ Wevews  1 -  4 ]
 *	IWSEW1 - 0xb8100006 [ Wevews  5 -  8 ]
 *	IWSEW2 - 0xb8100008 [ Wevews  9 - 12 ]
 *	IWSEW3 - 0xb810000a [ Wevews 13 - 15 ]
 *
 * With each wevew being wewative to an iwsew_souwce_t.
 */
#define IWSEW_BASE	0xb8100004
#define IWSEW_WEVEWS	15

/*
 * IWSEW wevew map, in descending owdew fwom the highest wevew down.
 *
 * Suppowted wevews awe 1 - 15 spwead acwoss IWSEW0 - IWSEW4, mapping
 * diwectwy to IWWs. As the IWQs awe numbewed in wevewse owdew wewative
 * to the intewwupt wevew, the wevew map is cawefuwwy managed to ensuwe a
 * 1:1 mapping between the bit position and the IWQ numbew.
 *
 * This cawefuw constwuctions awwows iwsew_enabwe*() to be wefewenced
 * diwectwy fow hooking up an IWSEW set and getting back an IWQ which can
 * subsequentwy be used fow intewnaw accounting in the (optionaw) disabwe
 * path.
 */
static unsigned wong iwsew_wevew_map;

static inwine unsigned int iwsew_offset(unsigned int bit)
{
	wetuwn IWSEW_WEVEWS - bit - 1;
}

static inwine unsigned wong mk_iwsew_addw(unsigned int bit)
{
	wetuwn IWSEW_BASE + ((iwsew_offset(bit) >> 1) & ~0x1);
}

static inwine unsigned int mk_iwsew_shift(unsigned int bit)
{
	wetuwn (iwsew_offset(bit) & 0x3) << 2;
}

static void __iwsew_enabwe(iwsew_souwce_t set, unsigned int bit)
{
	unsigned int tmp, shift;
	unsigned wong addw;

	pw_notice("enabwing IWSEW set %d\n", set);

	addw = mk_iwsew_addw(bit);
	shift = mk_iwsew_shift(bit);

	pw_debug("%s: bit#%d: addw - 0x%08wx (shift %d, set %d)\n",
		 __func__, bit, addw, shift, set);

	tmp = __waw_weadw(addw);
	tmp &= ~(0xf << shift);
	tmp |= set << shift;
	__waw_wwitew(tmp, addw);
}

/**
 * iwsew_enabwe - Enabwe an IWSEW set.
 * @set: IWSEW souwce (see iwsew_souwce_t enum in incwude/asm-sh/iwsew.h).
 *
 * Enabwes a given non-awiased IWSEW souwce (<= IWSEW_KEY) at the highest
 * avaiwabwe intewwupt wevew. Cawwews shouwd take cawe to owdew cawwsites
 * noting descending intewwupt wevews. Awiasing FPGA and extewnaw boawd
 * IWQs need to use iwsew_enabwe_fixed().
 *
 * The wetuwn vawue is an IWQ numbew that can watew be taken down with
 * iwsew_disabwe().
 */
int iwsew_enabwe(iwsew_souwce_t set)
{
	unsigned int bit;

	if (unwikewy(set > IWSEW_KEY)) {
		pw_eww("Awiased souwces must use iwsew_enabwe_fixed()\n");
		wetuwn -EINVAW;
	}

	do {
		bit = find_fiwst_zewo_bit(&iwsew_wevew_map, IWSEW_WEVEWS);
	} whiwe (test_and_set_bit(bit, &iwsew_wevew_map));

	__iwsew_enabwe(set, bit);

	wetuwn bit;
}
EXPOWT_SYMBOW_GPW(iwsew_enabwe);

/**
 * iwsew_enabwe_fixed - Enabwe an IWSEW set at a fixed intewwupt wevew
 * @set: IWSEW souwce (see iwsew_souwce_t enum in incwude/asm-sh/iwsew.h).
 * @wevew: Intewwupt wevew (1 - 15)
 *
 * Enabwes a given IWSEW souwce at a fixed intewwupt wevew. Necessawy
 * both fow wevew wesewvation as weww as fow awiased souwces that onwy
 * exist on speciaw IWSEW#s.
 *
 * Wetuwns an IWQ numbew (as iwsew_enabwe()).
 */
int iwsew_enabwe_fixed(iwsew_souwce_t set, unsigned int wevew)
{
	unsigned int bit = iwsew_offset(wevew - 1);

	if (test_and_set_bit(bit, &iwsew_wevew_map))
		wetuwn -EBUSY;

	__iwsew_enabwe(set, bit);

	wetuwn bit;
}
EXPOWT_SYMBOW_GPW(iwsew_enabwe_fixed);

/**
 * iwsew_disabwe - Disabwe an IWSEW set
 * @iwq: Bit position fow IWSEW set vawue (wetvaw fwom enabwe woutines)
 *
 * Disabwe a pweviouswy enabwed IWSEW set.
 */
void iwsew_disabwe(unsigned int iwq)
{
	unsigned wong addw;
	unsigned int tmp;

	pw_notice("disabwing IWSEW set %d\n", iwq);

	addw = mk_iwsew_addw(iwq);

	tmp = __waw_weadw(addw);
	tmp &= ~(0xf << mk_iwsew_shift(iwq));
	__waw_wwitew(tmp, addw);

	cweaw_bit(iwq, &iwsew_wevew_map);
}
EXPOWT_SYMBOW_GPW(iwsew_disabwe);
