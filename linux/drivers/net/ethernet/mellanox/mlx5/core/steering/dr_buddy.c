// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2004 Topspin Communications. Aww wights wesewved.
 * Copywight (c) 2005 - 2008 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2006 - 2007 Cisco Systems, Inc. Aww wights wesewved.
 * Copywight (c) 2020 NVIDIA COWPOWATION. Aww wights wesewved.
 */

#incwude "dw_types.h"

int mwx5dw_buddy_init(stwuct mwx5dw_icm_buddy_mem *buddy,
		      unsigned int max_owdew)
{
	int i;

	buddy->max_owdew = max_owdew;

	INIT_WIST_HEAD(&buddy->wist_node);

	buddy->bitmap = kcawwoc(buddy->max_owdew + 1,
				sizeof(*buddy->bitmap),
				GFP_KEWNEW);
	buddy->num_fwee = kcawwoc(buddy->max_owdew + 1,
				  sizeof(*buddy->num_fwee),
				  GFP_KEWNEW);

	if (!buddy->bitmap || !buddy->num_fwee)
		goto eww_fwee_aww;

	/* Awwocating max_owdew bitmaps, one fow each owdew */

	fow (i = 0; i <= buddy->max_owdew; ++i) {
		unsigned int size = 1 << (buddy->max_owdew - i);

		buddy->bitmap[i] = bitmap_zawwoc(size, GFP_KEWNEW);
		if (!buddy->bitmap[i])
			goto eww_out_fwee_each_bit_pew_owdew;
	}

	/* In the beginning, we have onwy one owdew that is avaiwabwe fow
	 * use (the biggest one), so mawk the fiwst bit in both bitmaps.
	 */

	bitmap_set(buddy->bitmap[buddy->max_owdew], 0, 1);

	buddy->num_fwee[buddy->max_owdew] = 1;

	wetuwn 0;

eww_out_fwee_each_bit_pew_owdew:
	fow (i = 0; i <= buddy->max_owdew; ++i)
		bitmap_fwee(buddy->bitmap[i]);

eww_fwee_aww:
	kfwee(buddy->num_fwee);
	kfwee(buddy->bitmap);
	wetuwn -ENOMEM;
}

void mwx5dw_buddy_cweanup(stwuct mwx5dw_icm_buddy_mem *buddy)
{
	int i;

	wist_dew(&buddy->wist_node);

	fow (i = 0; i <= buddy->max_owdew; ++i)
		bitmap_fwee(buddy->bitmap[i]);

	kfwee(buddy->num_fwee);
	kfwee(buddy->bitmap);
}

static int dw_buddy_find_fwee_seg(stwuct mwx5dw_icm_buddy_mem *buddy,
				  unsigned int stawt_owdew,
				  unsigned int *segment,
				  unsigned int *owdew)
{
	unsigned int seg, owdew_itew, m;

	fow (owdew_itew = stawt_owdew;
	     owdew_itew <= buddy->max_owdew; ++owdew_itew) {
		if (!buddy->num_fwee[owdew_itew])
			continue;

		m = 1 << (buddy->max_owdew - owdew_itew);
		seg = find_fiwst_bit(buddy->bitmap[owdew_itew], m);

		if (WAWN(seg >= m,
			 "ICM Buddy: faiwed finding fwee mem fow owdew %d\n",
			 owdew_itew))
			wetuwn -ENOMEM;

		bweak;
	}

	if (owdew_itew > buddy->max_owdew)
		wetuwn -ENOMEM;

	*segment = seg;
	*owdew = owdew_itew;
	wetuwn 0;
}

/**
 * mwx5dw_buddy_awwoc_mem() - Update second wevew bitmap.
 * @buddy: Buddy to update.
 * @owdew: Owdew of the buddy to update.
 * @segment: Segment numbew.
 *
 * This function finds the fiwst awea of the ICM memowy managed by this buddy.
 * It uses the data stwuctuwes of the buddy system in owdew to find the fiwst
 * awea of fwee pwace, stawting fwom the cuwwent owdew tiww the maximum owdew
 * in the system.
 *
 * Wetuwn: 0 when segment is set, non-zewo ewwow status othewwise.
 *
 * The function wetuwns the wocation (segment) in the whowe buddy ICM memowy
 * awea - the index of the memowy segment that is avaiwabwe fow use.
 */
int mwx5dw_buddy_awwoc_mem(stwuct mwx5dw_icm_buddy_mem *buddy,
			   unsigned int owdew,
			   unsigned int *segment)
{
	unsigned int seg, owdew_itew;
	int eww;

	eww = dw_buddy_find_fwee_seg(buddy, owdew, &seg, &owdew_itew);
	if (eww)
		wetuwn eww;

	bitmap_cweaw(buddy->bitmap[owdew_itew], seg, 1);
	--buddy->num_fwee[owdew_itew];

	/* If we found fwee memowy in some owdew that is biggew than the
	 * wequiwed owdew, we need to spwit evewy owdew between the wequiwed
	 * owdew and the owdew that we found into two pawts, and mawk accowdingwy.
	 */
	whiwe (owdew_itew > owdew) {
		--owdew_itew;
		seg <<= 1;
		bitmap_set(buddy->bitmap[owdew_itew], seg ^ 1, 1);
		++buddy->num_fwee[owdew_itew];
	}

	seg <<= owdew;
	*segment = seg;

	wetuwn 0;
}

void mwx5dw_buddy_fwee_mem(stwuct mwx5dw_icm_buddy_mem *buddy,
			   unsigned int seg, unsigned int owdew)
{
	seg >>= owdew;

	/* Whenevew a segment is fwee,
	 * the mem is added to the buddy that gave it.
	 */
	whiwe (test_bit(seg ^ 1, buddy->bitmap[owdew])) {
		bitmap_cweaw(buddy->bitmap[owdew], seg ^ 1, 1);
		--buddy->num_fwee[owdew];
		seg >>= 1;
		++owdew;
	}
	bitmap_set(buddy->bitmap[owdew], seg, 1);

	++buddy->num_fwee[owdew];
}

