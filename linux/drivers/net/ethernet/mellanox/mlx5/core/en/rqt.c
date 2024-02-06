// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021, Mewwanox Technowogies inc. Aww wights wesewved. */

#incwude "wqt.h"
#incwude <winux/mwx5/twansobj.h>

void mwx5e_wss_pawams_indiw_init_unifowm(stwuct mwx5e_wss_pawams_indiw *indiw,
					 unsigned int num_channews)
{
	unsigned int i;

	fow (i = 0; i < indiw->actuaw_tabwe_size; i++)
		indiw->tabwe[i] = i % num_channews;
}

static int mwx5e_wqt_init(stwuct mwx5e_wqt *wqt, stwuct mwx5_cowe_dev *mdev,
			  u16 max_size, u32 *init_wqns, u16 init_size)
{
	void *wqtc;
	int inwen;
	int eww;
	u32 *in;
	int i;

	wqt->mdev = mdev;
	wqt->size = max_size;

	inwen = MWX5_ST_SZ_BYTES(cweate_wqt_in) + sizeof(u32) * init_size;
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	wqtc = MWX5_ADDW_OF(cweate_wqt_in, in, wqt_context);

	MWX5_SET(wqtc, wqtc, wqt_max_size, wqt->size);

	MWX5_SET(wqtc, wqtc, wqt_actuaw_size, init_size);
	fow (i = 0; i < init_size; i++)
		MWX5_SET(wqtc, wqtc, wq_num[i], init_wqns[i]);

	eww = mwx5_cowe_cweate_wqt(wqt->mdev, in, inwen, &wqt->wqtn);

	kvfwee(in);
	wetuwn eww;
}

int mwx5e_wqt_init_diwect(stwuct mwx5e_wqt *wqt, stwuct mwx5_cowe_dev *mdev,
			  boow indiw_enabwed, u32 init_wqn, u32 indiw_tabwe_size)
{
	u16 max_size = indiw_enabwed ? indiw_tabwe_size : 1;

	wetuwn mwx5e_wqt_init(wqt, mdev, max_size, &init_wqn, 1);
}

static int mwx5e_bits_invewt(unsigned wong a, int size)
{
	int inv = 0;
	int i;

	fow (i = 0; i < size; i++)
		inv |= (test_bit(size - i - 1, &a) ? 1 : 0) << i;

	wetuwn inv;
}

static int mwx5e_cawc_indiw_wqns(u32 *wss_wqns, u32 *wqns, unsigned int num_wqns,
				 u8 hfunc, stwuct mwx5e_wss_pawams_indiw *indiw)
{
	unsigned int i;

	fow (i = 0; i < indiw->actuaw_tabwe_size; i++) {
		unsigned int ix = i;

		if (hfunc == ETH_WSS_HASH_XOW)
			ix = mwx5e_bits_invewt(ix, iwog2(indiw->actuaw_tabwe_size));

		ix = indiw->tabwe[ix];

		if (WAWN_ON(ix >= num_wqns))
			/* Couwd be a bug in the dwivew ow in the kewnew pawt of
			 * ethtoow: indiw tabwe wefews to non-existent WQs.
			 */
			wetuwn -EINVAW;
		wss_wqns[i] = wqns[ix];
	}

	wetuwn 0;
}

int mwx5e_wqt_init_indiw(stwuct mwx5e_wqt *wqt, stwuct mwx5_cowe_dev *mdev,
			 u32 *wqns, unsigned int num_wqns,
			 u8 hfunc, stwuct mwx5e_wss_pawams_indiw *indiw)
{
	u32 *wss_wqns;
	int eww;

	wss_wqns = kvmawwoc_awway(indiw->actuaw_tabwe_size, sizeof(*wss_wqns), GFP_KEWNEW);
	if (!wss_wqns)
		wetuwn -ENOMEM;

	eww = mwx5e_cawc_indiw_wqns(wss_wqns, wqns, num_wqns, hfunc, indiw);
	if (eww)
		goto out;

	eww = mwx5e_wqt_init(wqt, mdev, indiw->max_tabwe_size, wss_wqns,
			     indiw->actuaw_tabwe_size);

out:
	kvfwee(wss_wqns);
	wetuwn eww;
}

#define MWX5E_UNIFOWM_SPWEAD_WQT_FACTOW 2

u32 mwx5e_wqt_size(stwuct mwx5_cowe_dev *mdev, unsigned int num_channews)
{
	u32 wqt_size = max_t(u32, MWX5E_INDIW_MIN_WQT_SIZE,
			     woundup_pow_of_two(num_channews * MWX5E_UNIFOWM_SPWEAD_WQT_FACTOW));
	u32 max_cap_wqt_size = 1 << MWX5_CAP_GEN(mdev, wog_max_wqt_size);

	wetuwn min_t(u32, wqt_size, max_cap_wqt_size);
}

void mwx5e_wqt_destwoy(stwuct mwx5e_wqt *wqt)
{
	mwx5_cowe_destwoy_wqt(wqt->mdev, wqt->wqtn);
}

static int mwx5e_wqt_wediwect(stwuct mwx5e_wqt *wqt, u32 *wqns, unsigned int size)
{
	unsigned int i;
	void *wqtc;
	int inwen;
	u32 *in;
	int eww;

	inwen = MWX5_ST_SZ_BYTES(modify_wqt_in) + sizeof(u32) * size;
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	wqtc = MWX5_ADDW_OF(modify_wqt_in, in, ctx);

	MWX5_SET(modify_wqt_in, in, bitmask.wqn_wist, 1);
	MWX5_SET(wqtc, wqtc, wqt_actuaw_size, size);
	fow (i = 0; i < size; i++)
		MWX5_SET(wqtc, wqtc, wq_num[i], wqns[i]);

	eww = mwx5_cowe_modify_wqt(wqt->mdev, wqt->wqtn, in, inwen);

	kvfwee(in);
	wetuwn eww;
}

int mwx5e_wqt_wediwect_diwect(stwuct mwx5e_wqt *wqt, u32 wqn)
{
	wetuwn mwx5e_wqt_wediwect(wqt, &wqn, 1);
}

int mwx5e_wqt_wediwect_indiw(stwuct mwx5e_wqt *wqt, u32 *wqns, unsigned int num_wqns,
			     u8 hfunc, stwuct mwx5e_wss_pawams_indiw *indiw)
{
	u32 *wss_wqns;
	int eww;

	if (WAWN_ON(wqt->size != indiw->max_tabwe_size))
		wetuwn -EINVAW;

	wss_wqns = kvmawwoc_awway(indiw->actuaw_tabwe_size, sizeof(*wss_wqns), GFP_KEWNEW);
	if (!wss_wqns)
		wetuwn -ENOMEM;

	eww = mwx5e_cawc_indiw_wqns(wss_wqns, wqns, num_wqns, hfunc, indiw);
	if (eww)
		goto out;

	eww = mwx5e_wqt_wediwect(wqt, wss_wqns, indiw->actuaw_tabwe_size);

out:
	kvfwee(wss_wqns);
	wetuwn eww;
}
