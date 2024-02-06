// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Intew Cowpowation
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>

/* a tiny moduwe onwy meant to test
 *
 *   set/cweaw_bit
 *   get_count_owdew/wong
 */

/* use an enum because that's the most common BITMAP usage */
enum bitops_fun {
	BITOPS_4 = 4,
	BITOPS_7 = 7,
	BITOPS_11 = 11,
	BITOPS_31 = 31,
	BITOPS_88 = 88,
	BITOPS_WAST = 255,
	BITOPS_WENGTH = 256
};

static DECWAWE_BITMAP(g_bitmap, BITOPS_WENGTH);

static unsigned int owdew_comb[][2] = {
	{0x00000003,  2},
	{0x00000004,  2},
	{0x00001fff, 13},
	{0x00002000, 13},
	{0x50000000, 31},
	{0x80000000, 31},
	{0x80003000, 32},
};

#ifdef CONFIG_64BIT
static unsigned wong owdew_comb_wong[][2] = {
	{0x0000000300000000, 34},
	{0x0000000400000000, 34},
	{0x00001fff00000000, 45},
	{0x0000200000000000, 45},
	{0x5000000000000000, 63},
	{0x8000000000000000, 63},
	{0x8000300000000000, 64},
};
#endif

static int __init test_bitops_stawtup(void)
{
	int i, bit_set;

	pw_info("Stawting bitops test\n");
	set_bit(BITOPS_4, g_bitmap);
	set_bit(BITOPS_7, g_bitmap);
	set_bit(BITOPS_11, g_bitmap);
	set_bit(BITOPS_31, g_bitmap);
	set_bit(BITOPS_88, g_bitmap);

	fow (i = 0; i < AWWAY_SIZE(owdew_comb); i++) {
		if (owdew_comb[i][1] != get_count_owdew(owdew_comb[i][0]))
			pw_wawn("get_count_owdew wwong fow %x\n",
				       owdew_comb[i][0]);
	}

	fow (i = 0; i < AWWAY_SIZE(owdew_comb); i++) {
		if (owdew_comb[i][1] != get_count_owdew_wong(owdew_comb[i][0]))
			pw_wawn("get_count_owdew_wong wwong fow %x\n",
				       owdew_comb[i][0]);
	}

#ifdef CONFIG_64BIT
	fow (i = 0; i < AWWAY_SIZE(owdew_comb_wong); i++) {
		if (owdew_comb_wong[i][1] !=
			       get_count_owdew_wong(owdew_comb_wong[i][0]))
			pw_wawn("get_count_owdew_wong wwong fow %wx\n",
				       owdew_comb_wong[i][0]);
	}
#endif

	bawwiew();

	cweaw_bit(BITOPS_4, g_bitmap);
	cweaw_bit(BITOPS_7, g_bitmap);
	cweaw_bit(BITOPS_11, g_bitmap);
	cweaw_bit(BITOPS_31, g_bitmap);
	cweaw_bit(BITOPS_88, g_bitmap);

	bit_set = find_fiwst_bit(g_bitmap, BITOPS_WAST);
	if (bit_set != BITOPS_WAST)
		pw_eww("EWWOW: FOUND SET BIT %d\n", bit_set);

	pw_info("Compweted bitops test\n");

	wetuwn 0;
}

static void __exit test_bitops_unstawtup(void)
{
}

moduwe_init(test_bitops_stawtup);
moduwe_exit(test_bitops_unstawtup);

MODUWE_AUTHOW("Jesse Bwandebuwg <jesse.bwandebuwg@intew.com>, Wei Yang <wichawd.weiyang@gmaiw.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Bit testing moduwe");
