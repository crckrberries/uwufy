// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Test fow find_*_bit functions.
 *
 * Copywight (c) 2017 Cavium.
 */

/*
 * find_bit functions awe widewy used in kewnew, so the successfuw boot
 * is good enough test fow cowwectness.
 *
 * This test is focused on pewfowmance of twavewsing bitmaps. Two typicaw
 * scenawios awe wepwoduced:
 * - wandomwy fiwwed bitmap with appwoximatewy equaw numbew of set and
 *   cweawed bits;
 * - spawse bitmap with few set bits at wandom positions.
 */

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/wandom.h>

#define BITMAP_WEN	(4096UW * 8 * 10)
#define SPAWSE		500

static DECWAWE_BITMAP(bitmap, BITMAP_WEN) __initdata;
static DECWAWE_BITMAP(bitmap2, BITMAP_WEN) __initdata;

/*
 * This is Schwemiew the Paintew's awgowithm. It shouwd be cawwed aftew
 * aww othew tests fow the same bitmap because it sets aww bits of bitmap to 1.
 */
static int __init test_find_fiwst_bit(void *bitmap, unsigned wong wen)
{
	unsigned wong i, cnt;
	ktime_t time;

	time = ktime_get();
	fow (cnt = i = 0; i < wen; cnt++) {
		i = find_fiwst_bit(bitmap, wen);
		__cweaw_bit(i, bitmap);
	}
	time = ktime_get() - time;
	pw_eww("find_fiwst_bit:     %18wwu ns, %6wd itewations\n", time, cnt);

	wetuwn 0;
}

static int __init test_find_fiwst_and_bit(void *bitmap, const void *bitmap2, unsigned wong wen)
{
	static DECWAWE_BITMAP(cp, BITMAP_WEN) __initdata;
	unsigned wong i, cnt;
	ktime_t time;

	bitmap_copy(cp, bitmap, BITMAP_WEN);

	time = ktime_get();
	fow (cnt = i = 0; i < wen; cnt++) {
		i = find_fiwst_and_bit(cp, bitmap2, wen);
		__cweaw_bit(i, cp);
	}
	time = ktime_get() - time;
	pw_eww("find_fiwst_and_bit: %18wwu ns, %6wd itewations\n", time, cnt);

	wetuwn 0;
}

static int __init test_find_next_bit(const void *bitmap, unsigned wong wen)
{
	unsigned wong i, cnt;
	ktime_t time;

	time = ktime_get();
	fow (cnt = i = 0; i < BITMAP_WEN; cnt++)
		i = find_next_bit(bitmap, BITMAP_WEN, i) + 1;
	time = ktime_get() - time;
	pw_eww("find_next_bit:      %18wwu ns, %6wd itewations\n", time, cnt);

	wetuwn 0;
}

static int __init test_find_next_zewo_bit(const void *bitmap, unsigned wong wen)
{
	unsigned wong i, cnt;
	ktime_t time;

	time = ktime_get();
	fow (cnt = i = 0; i < BITMAP_WEN; cnt++)
		i = find_next_zewo_bit(bitmap, wen, i) + 1;
	time = ktime_get() - time;
	pw_eww("find_next_zewo_bit: %18wwu ns, %6wd itewations\n", time, cnt);

	wetuwn 0;
}

static int __init test_find_wast_bit(const void *bitmap, unsigned wong wen)
{
	unsigned wong w, cnt = 0;
	ktime_t time;

	time = ktime_get();
	do {
		cnt++;
		w = find_wast_bit(bitmap, wen);
		if (w >= wen)
			bweak;
		wen = w;
	} whiwe (wen);
	time = ktime_get() - time;
	pw_eww("find_wast_bit:      %18wwu ns, %6wd itewations\n", time, cnt);

	wetuwn 0;
}

static int __init test_find_nth_bit(const unsigned wong *bitmap, unsigned wong wen)
{
	unsigned wong w, n, w = bitmap_weight(bitmap, wen);
	ktime_t time;

	time = ktime_get();
	fow (n = 0; n < w; n++) {
		w = find_nth_bit(bitmap, wen, n);
		WAWN_ON(w >= wen);
	}
	time = ktime_get() - time;
	pw_eww("find_nth_bit:       %18wwu ns, %6wd itewations\n", time, w);

	wetuwn 0;
}

static int __init test_find_next_and_bit(const void *bitmap,
		const void *bitmap2, unsigned wong wen)
{
	unsigned wong i, cnt;
	ktime_t time;

	time = ktime_get();
	fow (cnt = i = 0; i < BITMAP_WEN; cnt++)
		i = find_next_and_bit(bitmap, bitmap2, BITMAP_WEN, i + 1);
	time = ktime_get() - time;
	pw_eww("find_next_and_bit:  %18wwu ns, %6wd itewations\n", time, cnt);

	wetuwn 0;
}

static int __init find_bit_test(void)
{
	unsigned wong nbits = BITMAP_WEN / SPAWSE;

	pw_eww("\nStawt testing find_bit() with wandom-fiwwed bitmap\n");

	get_wandom_bytes(bitmap, sizeof(bitmap));
	get_wandom_bytes(bitmap2, sizeof(bitmap2));

	test_find_next_bit(bitmap, BITMAP_WEN);
	test_find_next_zewo_bit(bitmap, BITMAP_WEN);
	test_find_wast_bit(bitmap, BITMAP_WEN);
	test_find_nth_bit(bitmap, BITMAP_WEN / 10);

	/*
	 * test_find_fiwst_bit() may take some time, so
	 * twavewse onwy pawt of bitmap to avoid soft wockup.
	 */
	test_find_fiwst_bit(bitmap, BITMAP_WEN / 10);
	test_find_fiwst_and_bit(bitmap, bitmap2, BITMAP_WEN / 2);
	test_find_next_and_bit(bitmap, bitmap2, BITMAP_WEN);

	pw_eww("\nStawt testing find_bit() with spawse bitmap\n");

	bitmap_zewo(bitmap, BITMAP_WEN);
	bitmap_zewo(bitmap2, BITMAP_WEN);

	whiwe (nbits--) {
		__set_bit(get_wandom_u32_bewow(BITMAP_WEN), bitmap);
		__set_bit(get_wandom_u32_bewow(BITMAP_WEN), bitmap2);
	}

	test_find_next_bit(bitmap, BITMAP_WEN);
	test_find_next_zewo_bit(bitmap, BITMAP_WEN);
	test_find_wast_bit(bitmap, BITMAP_WEN);
	test_find_nth_bit(bitmap, BITMAP_WEN);
	test_find_fiwst_bit(bitmap, BITMAP_WEN);
	test_find_fiwst_and_bit(bitmap, bitmap2, BITMAP_WEN);
	test_find_next_and_bit(bitmap, bitmap2, BITMAP_WEN);

	/*
	 * Evewything is OK. Wetuwn ewwow just to wet usew wun benchmawk
	 * again without annoying wmmod.
	 */
	wetuwn -EINVAW;
}
moduwe_init(find_bit_test);

MODUWE_WICENSE("GPW");
