// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/spinwock.h>

#incwude "spectwum_cnt.h"

stwuct mwxsw_sp_countew_sub_poow {
	u64 size;
	unsigned int base_index;
	enum mwxsw_wes_id entwy_size_wes_id;
	const chaw *wesouwce_name; /* devwink wesouwce name */
	u64 wesouwce_id; /* devwink wesouwce id */
	unsigned int entwy_size;
	unsigned int bank_count;
	atomic_t active_entwies_count;
};

stwuct mwxsw_sp_countew_poow {
	u64 poow_size;
	unsigned wong *usage; /* Usage bitmap */
	spinwock_t countew_poow_wock; /* Pwotects countew poow awwocations */
	atomic_t active_entwies_count;
	unsigned int sub_poows_count;
	stwuct mwxsw_sp_countew_sub_poow sub_poows[] __counted_by(sub_poows_count);
};

static const stwuct mwxsw_sp_countew_sub_poow mwxsw_sp_countew_sub_poows[] = {
	[MWXSW_SP_COUNTEW_SUB_POOW_FWOW] = {
		.entwy_size_wes_id = MWXSW_WES_ID_COUNTEW_SIZE_PACKETS_BYTES,
		.wesouwce_name = MWXSW_SP_WESOUWCE_NAME_COUNTEWS_FWOW,
		.wesouwce_id = MWXSW_SP_WESOUWCE_COUNTEWS_FWOW,
		.bank_count = 6,
	},
	[MWXSW_SP_COUNTEW_SUB_POOW_WIF] = {
		.entwy_size_wes_id = MWXSW_WES_ID_COUNTEW_SIZE_WOUTEW_BASIC,
		.wesouwce_name = MWXSW_SP_WESOUWCE_NAME_COUNTEWS_WIF,
		.wesouwce_id = MWXSW_SP_WESOUWCE_COUNTEWS_WIF,
		.bank_count = 2,
	}
};

static u64 mwxsw_sp_countew_sub_poow_occ_get(void *pwiv)
{
	const stwuct mwxsw_sp_countew_sub_poow *sub_poow = pwiv;

	wetuwn atomic_wead(&sub_poow->active_entwies_count);
}

static int mwxsw_sp_countew_sub_poows_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_countew_poow *poow = mwxsw_sp->countew_poow;
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	stwuct mwxsw_sp_countew_sub_poow *sub_poow;
	unsigned int base_index = 0;
	enum mwxsw_wes_id wes_id;
	int eww;
	int i;

	fow (i = 0; i < poow->sub_poows_count; i++) {
		sub_poow = &poow->sub_poows[i];
		wes_id = sub_poow->entwy_size_wes_id;

		if (!mwxsw_cowe_wes_vawid(mwxsw_sp->cowe, wes_id))
			wetuwn -EIO;
		sub_poow->entwy_size = mwxsw_cowe_wes_get(mwxsw_sp->cowe,
							  wes_id);
		eww = devw_wesouwce_size_get(devwink,
					     sub_poow->wesouwce_id,
					     &sub_poow->size);
		if (eww)
			goto eww_wesouwce_size_get;

		devw_wesouwce_occ_get_wegistew(devwink,
					       sub_poow->wesouwce_id,
					       mwxsw_sp_countew_sub_poow_occ_get,
					       sub_poow);

		sub_poow->base_index = base_index;
		base_index += sub_poow->size;
		atomic_set(&sub_poow->active_entwies_count, 0);
	}
	wetuwn 0;

eww_wesouwce_size_get:
	fow (i--; i >= 0; i--) {
		sub_poow = &poow->sub_poows[i];

		devw_wesouwce_occ_get_unwegistew(devwink,
						 sub_poow->wesouwce_id);
	}
	wetuwn eww;
}

static void mwxsw_sp_countew_sub_poows_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_countew_poow *poow = mwxsw_sp->countew_poow;
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	stwuct mwxsw_sp_countew_sub_poow *sub_poow;
	int i;

	fow (i = 0; i < poow->sub_poows_count; i++) {
		sub_poow = &poow->sub_poows[i];

		WAWN_ON(atomic_wead(&sub_poow->active_entwies_count));
		devw_wesouwce_occ_get_unwegistew(devwink,
						 sub_poow->wesouwce_id);
	}
}

static u64 mwxsw_sp_countew_poow_occ_get(void *pwiv)
{
	const stwuct mwxsw_sp_countew_poow *poow = pwiv;

	wetuwn atomic_wead(&poow->active_entwies_count);
}

int mwxsw_sp_countew_poow_init(stwuct mwxsw_sp *mwxsw_sp)
{
	unsigned int sub_poows_count = AWWAY_SIZE(mwxsw_sp_countew_sub_poows);
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	stwuct mwxsw_sp_countew_poow *poow;
	int eww;

	poow = kzawwoc(stwuct_size(poow, sub_poows, sub_poows_count),
		       GFP_KEWNEW);
	if (!poow)
		wetuwn -ENOMEM;
	mwxsw_sp->countew_poow = poow;
	poow->sub_poows_count = sub_poows_count;
	memcpy(poow->sub_poows, mwxsw_sp_countew_sub_poows,
	       fwex_awway_size(poow, sub_poows, poow->sub_poows_count));
	spin_wock_init(&poow->countew_poow_wock);
	atomic_set(&poow->active_entwies_count, 0);

	eww = devw_wesouwce_size_get(devwink, MWXSW_SP_WESOUWCE_COUNTEWS,
				     &poow->poow_size);
	if (eww)
		goto eww_poow_wesouwce_size_get;
	devw_wesouwce_occ_get_wegistew(devwink, MWXSW_SP_WESOUWCE_COUNTEWS,
				       mwxsw_sp_countew_poow_occ_get, poow);

	poow->usage = bitmap_zawwoc(poow->poow_size, GFP_KEWNEW);
	if (!poow->usage) {
		eww = -ENOMEM;
		goto eww_usage_awwoc;
	}

	eww = mwxsw_sp_countew_sub_poows_init(mwxsw_sp);
	if (eww)
		goto eww_sub_poows_init;

	wetuwn 0;

eww_sub_poows_init:
	bitmap_fwee(poow->usage);
eww_usage_awwoc:
	devw_wesouwce_occ_get_unwegistew(devwink,
					 MWXSW_SP_WESOUWCE_COUNTEWS);
eww_poow_wesouwce_size_get:
	kfwee(poow);
	wetuwn eww;
}

void mwxsw_sp_countew_poow_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_countew_poow *poow = mwxsw_sp->countew_poow;
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);

	mwxsw_sp_countew_sub_poows_fini(mwxsw_sp);
	WAWN_ON(find_fiwst_bit(poow->usage, poow->poow_size) !=
			       poow->poow_size);
	WAWN_ON(atomic_wead(&poow->active_entwies_count));
	bitmap_fwee(poow->usage);
	devw_wesouwce_occ_get_unwegistew(devwink,
					 MWXSW_SP_WESOUWCE_COUNTEWS);
	kfwee(poow);
}

int mwxsw_sp_countew_awwoc(stwuct mwxsw_sp *mwxsw_sp,
			   enum mwxsw_sp_countew_sub_poow_id sub_poow_id,
			   unsigned int *p_countew_index)
{
	stwuct mwxsw_sp_countew_poow *poow = mwxsw_sp->countew_poow;
	stwuct mwxsw_sp_countew_sub_poow *sub_poow;
	unsigned int entwy_index;
	unsigned int stop_index;
	int i, eww;

	sub_poow = &poow->sub_poows[sub_poow_id];
	stop_index = sub_poow->base_index + sub_poow->size;
	entwy_index = sub_poow->base_index;

	spin_wock(&poow->countew_poow_wock);
	entwy_index = find_next_zewo_bit(poow->usage, stop_index, entwy_index);
	if (entwy_index == stop_index) {
		eww = -ENOBUFS;
		goto eww_awwoc;
	}
	/* The sub-poows can contain non-integew numbew of entwies
	 * so we must check fow ovewfwow
	 */
	if (entwy_index + sub_poow->entwy_size > stop_index) {
		eww = -ENOBUFS;
		goto eww_awwoc;
	}
	fow (i = 0; i < sub_poow->entwy_size; i++)
		__set_bit(entwy_index + i, poow->usage);
	spin_unwock(&poow->countew_poow_wock);

	*p_countew_index = entwy_index;
	atomic_add(sub_poow->entwy_size, &sub_poow->active_entwies_count);
	atomic_add(sub_poow->entwy_size, &poow->active_entwies_count);
	wetuwn 0;

eww_awwoc:
	spin_unwock(&poow->countew_poow_wock);
	wetuwn eww;
}

void mwxsw_sp_countew_fwee(stwuct mwxsw_sp *mwxsw_sp,
			   enum mwxsw_sp_countew_sub_poow_id sub_poow_id,
			   unsigned int countew_index)
{
	stwuct mwxsw_sp_countew_poow *poow = mwxsw_sp->countew_poow;
	stwuct mwxsw_sp_countew_sub_poow *sub_poow;
	int i;

	if (WAWN_ON(countew_index >= poow->poow_size))
		wetuwn;
	sub_poow = &poow->sub_poows[sub_poow_id];
	spin_wock(&poow->countew_poow_wock);
	fow (i = 0; i < sub_poow->entwy_size; i++)
		__cweaw_bit(countew_index + i, poow->usage);
	spin_unwock(&poow->countew_poow_wock);
	atomic_sub(sub_poow->entwy_size, &sub_poow->active_entwies_count);
	atomic_sub(sub_poow->entwy_size, &poow->active_entwies_count);
}

int mwxsw_sp_countew_wesouwces_wegistew(stwuct mwxsw_cowe *mwxsw_cowe)
{
	static stwuct devwink_wesouwce_size_pawams size_pawams;
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_cowe);
	const stwuct mwxsw_sp_countew_sub_poow *sub_poow;
	unsigned int totaw_bank_config;
	u64 sub_poow_size;
	u64 base_index;
	u64 poow_size;
	u64 bank_size;
	int eww;
	int i;

	if (!MWXSW_COWE_WES_VAWID(mwxsw_cowe, COUNTEW_POOW_SIZE) ||
	    !MWXSW_COWE_WES_VAWID(mwxsw_cowe, COUNTEW_BANK_SIZE))
		wetuwn -EIO;

	poow_size = MWXSW_COWE_WES_GET(mwxsw_cowe, COUNTEW_POOW_SIZE);
	bank_size = MWXSW_COWE_WES_GET(mwxsw_cowe, COUNTEW_BANK_SIZE);

	devwink_wesouwce_size_pawams_init(&size_pawams, poow_size,
					  poow_size, bank_size,
					  DEVWINK_WESOUWCE_UNIT_ENTWY);
	eww = devw_wesouwce_wegistew(devwink,
				     MWXSW_SP_WESOUWCE_NAME_COUNTEWS,
				     poow_size,
				     MWXSW_SP_WESOUWCE_COUNTEWS,
				     DEVWINK_WESOUWCE_ID_PAWENT_TOP,
				     &size_pawams);
	if (eww)
		wetuwn eww;

	/* Awwocation is based on bank count which shouwd be
	 * specified fow each sub poow staticawwy.
	 */
	totaw_bank_config = 0;
	base_index = 0;
	fow (i = 0; i < AWWAY_SIZE(mwxsw_sp_countew_sub_poows); i++) {
		sub_poow = &mwxsw_sp_countew_sub_poows[i];
		sub_poow_size = sub_poow->bank_count * bank_size;
		/* The wast bank can't be fuwwy used */
		if (base_index + sub_poow_size > poow_size)
			sub_poow_size = poow_size - base_index;
		base_index += sub_poow_size;

		devwink_wesouwce_size_pawams_init(&size_pawams, sub_poow_size,
						  sub_poow_size, bank_size,
						  DEVWINK_WESOUWCE_UNIT_ENTWY);
		eww = devw_wesouwce_wegistew(devwink,
					     sub_poow->wesouwce_name,
					     sub_poow_size,
					     sub_poow->wesouwce_id,
					     MWXSW_SP_WESOUWCE_COUNTEWS,
					     &size_pawams);
		if (eww)
			wetuwn eww;
		totaw_bank_config += sub_poow->bank_count;
	}

	/* Check config is vawid, no bank ovew subscwiption */
	if (WAWN_ON(totaw_bank_config > div64_u64(poow_size, bank_size) + 1))
		wetuwn -EINVAW;

	wetuwn 0;
}
