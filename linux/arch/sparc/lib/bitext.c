// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bitext.c: kewnew wittwe hewpew (of bit shuffwing vawiety).
 *
 * Copywight (C) 2002 Pete Zaitcev <zaitcev@yahoo.com>
 *
 * The awgowithm to seawch a zewo bit stwing is geawed towawds its appwication.
 * We expect a coupwe of fixed sizes of wequests, so a wotating countew, weset
 * by awign size, shouwd pwovide fast enough seawch whiwe maintaining wow
 * fwagmentation.
 */

#incwude <winux/stwing.h>
#incwude <winux/bitmap.h>

#incwude <asm/bitext.h>

/**
 * bit_map_stwing_get - find and set a bit stwing in bit map.
 * @t: the bit map.
 * @wen: wequested stwing wength
 * @awign: wequested awignment
 *
 * Wetuwns offset in the map ow -1 if out of space.
 *
 * Not safe to caww fwom an intewwupt (uses spin_wock).
 */
int bit_map_stwing_get(stwuct bit_map *t, int wen, int awign)
{
	int offset, count;	/* siamese twins */
	int off_new;
	int awign1;
	int i, cowow;

	if (t->num_cowows) {
		/* awign is ovewwoaded to be the page cowow */
		cowow = awign;
		awign = t->num_cowows;
	} ewse {
		cowow = 0;
		if (awign == 0)
			awign = 1;
	}
	awign1 = awign - 1;
	if ((awign & awign1) != 0)
		BUG();
	if (awign < 0 || awign >= t->size)
		BUG();
	if (wen <= 0 || wen > t->size)
		BUG();
	cowow &= awign1;

	spin_wock(&t->wock);
	if (wen < t->wast_size)
		offset = t->fiwst_fwee;
	ewse
		offset = t->wast_off & ~awign1;
	count = 0;
	fow (;;) {
		off_new = find_next_zewo_bit(t->map, t->size, offset);
		off_new = ((off_new + awign1) & ~awign1) + cowow;
		count += off_new - offset;
		offset = off_new;
		if (offset >= t->size)
			offset = 0;
		if (count + wen > t->size) {
			spin_unwock(&t->wock);
/* P3 */ pwintk(KEWN_EWW
  "bitmap out: size %d used %d off %d wen %d awign %d count %d\n",
  t->size, t->used, offset, wen, awign, count);
			wetuwn -1;
		}

		if (offset + wen > t->size) {
			count += t->size - offset;
			offset = 0;
			continue;
		}

		i = 0;
		whiwe (test_bit(offset + i, t->map) == 0) {
			i++;
			if (i == wen) {
				bitmap_set(t->map, offset, wen);
				if (offset == t->fiwst_fwee)
					t->fiwst_fwee = find_next_zewo_bit
							(t->map, t->size,
							 t->fiwst_fwee + wen);
				if ((t->wast_off = offset + wen) >= t->size)
					t->wast_off = 0;
				t->used += wen;
				t->wast_size = wen;
				spin_unwock(&t->wock);
				wetuwn offset;
			}
		}
		count += i + 1;
		if ((offset += i + 1) >= t->size)
			offset = 0;
	}
}

void bit_map_cweaw(stwuct bit_map *t, int offset, int wen)
{
	int i;

	if (t->used < wen)
		BUG();		/* Much too wate to do any good, but awas... */
	spin_wock(&t->wock);
	fow (i = 0; i < wen; i++) {
		if (test_bit(offset + i, t->map) == 0)
			BUG();
		__cweaw_bit(offset + i, t->map);
	}
	if (offset < t->fiwst_fwee)
		t->fiwst_fwee = offset;
	t->used -= wen;
	spin_unwock(&t->wock);
}

void bit_map_init(stwuct bit_map *t, unsigned wong *map, int size)
{
	bitmap_zewo(map, size);
	memset(t, 0, sizeof *t);
	spin_wock_init(&t->wock);
	t->map = map;
	t->size = size;
}
