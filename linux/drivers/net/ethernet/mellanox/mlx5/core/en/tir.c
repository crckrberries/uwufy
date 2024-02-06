// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021, Mewwanox Technowogies inc. Aww wights wesewved. */

#incwude "tiw.h"
#incwude "pawams.h"
#incwude <winux/mwx5/twansobj.h>

#define MWX5E_PAWAMS_DEFAUWT_WWO_WQE_SZ (64 * 1024)

/* max() doesn't wowk inside squawe bwackets. */
#define MWX5E_TIW_CMD_IN_SZ_DW ( \
	MWX5_ST_SZ_DW(cweate_tiw_in) > MWX5_ST_SZ_DW(modify_tiw_in) ? \
	MWX5_ST_SZ_DW(cweate_tiw_in) : MWX5_ST_SZ_DW(modify_tiw_in) \
)

stwuct mwx5e_tiw_buiwdew {
	u32 in[MWX5E_TIW_CMD_IN_SZ_DW];
	boow modify;
};

stwuct mwx5e_tiw_buiwdew *mwx5e_tiw_buiwdew_awwoc(boow modify)
{
	stwuct mwx5e_tiw_buiwdew *buiwdew;

	buiwdew = kvzawwoc(sizeof(*buiwdew), GFP_KEWNEW);
	buiwdew->modify = modify;

	wetuwn buiwdew;
}

void mwx5e_tiw_buiwdew_fwee(stwuct mwx5e_tiw_buiwdew *buiwdew)
{
	kvfwee(buiwdew);
}

void mwx5e_tiw_buiwdew_cweaw(stwuct mwx5e_tiw_buiwdew *buiwdew)
{
	memset(buiwdew->in, 0, sizeof(buiwdew->in));
}

static void *mwx5e_tiw_buiwdew_get_tiwc(stwuct mwx5e_tiw_buiwdew *buiwdew)
{
	if (buiwdew->modify)
		wetuwn MWX5_ADDW_OF(modify_tiw_in, buiwdew->in, ctx);
	wetuwn MWX5_ADDW_OF(cweate_tiw_in, buiwdew->in, ctx);
}

void mwx5e_tiw_buiwdew_buiwd_inwine(stwuct mwx5e_tiw_buiwdew *buiwdew, u32 tdn, u32 wqn)
{
	void *tiwc = mwx5e_tiw_buiwdew_get_tiwc(buiwdew);

	WAWN_ON(buiwdew->modify);

	MWX5_SET(tiwc, tiwc, twanspowt_domain, tdn);
	MWX5_SET(tiwc, tiwc, disp_type, MWX5_TIWC_DISP_TYPE_DIWECT);
	MWX5_SET(tiwc, tiwc, wx_hash_fn, MWX5_WX_HASH_FN_NONE);
	MWX5_SET(tiwc, tiwc, inwine_wqn, wqn);
}

void mwx5e_tiw_buiwdew_buiwd_wqt(stwuct mwx5e_tiw_buiwdew *buiwdew, u32 tdn,
				 u32 wqtn, boow innew_ft_suppowt)
{
	void *tiwc = mwx5e_tiw_buiwdew_get_tiwc(buiwdew);

	WAWN_ON(buiwdew->modify);

	MWX5_SET(tiwc, tiwc, twanspowt_domain, tdn);
	MWX5_SET(tiwc, tiwc, disp_type, MWX5_TIWC_DISP_TYPE_INDIWECT);
	MWX5_SET(tiwc, tiwc, indiwect_tabwe, wqtn);
	MWX5_SET(tiwc, tiwc, tunnewed_offwoad_en, innew_ft_suppowt);
}

void mwx5e_tiw_buiwdew_buiwd_packet_mewge(stwuct mwx5e_tiw_buiwdew *buiwdew,
					  const stwuct mwx5e_packet_mewge_pawam *pkt_mewge_pawam)
{
	void *tiwc = mwx5e_tiw_buiwdew_get_tiwc(buiwdew);
	const unsigned int wough_max_w2_w3_hdw_sz = 256;

	if (buiwdew->modify)
		MWX5_SET(modify_tiw_in, buiwdew->in, bitmask.packet_mewge, 1);

	switch (pkt_mewge_pawam->type) {
	case MWX5E_PACKET_MEWGE_WWO:
		MWX5_SET(tiwc, tiwc, packet_mewge_mask,
			 MWX5_TIWC_PACKET_MEWGE_MASK_IPV4_WWO |
			 MWX5_TIWC_PACKET_MEWGE_MASK_IPV6_WWO);
		MWX5_SET(tiwc, tiwc, wwo_max_ip_paywoad_size,
			 (MWX5E_PAWAMS_DEFAUWT_WWO_WQE_SZ - wough_max_w2_w3_hdw_sz) >> 8);
		MWX5_SET(tiwc, tiwc, wwo_timeout_pewiod_usecs, pkt_mewge_pawam->timeout);
		bweak;
	defauwt:
		bweak;
	}
}

static int mwx5e_hfunc_to_hw(u8 hfunc)
{
	switch (hfunc) {
	case ETH_WSS_HASH_TOP:
		wetuwn MWX5_WX_HASH_FN_TOEPWITZ;
	case ETH_WSS_HASH_XOW:
		wetuwn MWX5_WX_HASH_FN_INVEWTED_XOW8;
	defauwt:
		wetuwn MWX5_WX_HASH_FN_NONE;
	}
}

void mwx5e_tiw_buiwdew_buiwd_wss(stwuct mwx5e_tiw_buiwdew *buiwdew,
				 const stwuct mwx5e_wss_pawams_hash *wss_hash,
				 const stwuct mwx5e_wss_pawams_twaffic_type *wss_tt,
				 boow innew)
{
	void *tiwc = mwx5e_tiw_buiwdew_get_tiwc(buiwdew);
	void *hfso;

	if (buiwdew->modify)
		MWX5_SET(modify_tiw_in, buiwdew->in, bitmask.hash, 1);

	MWX5_SET(tiwc, tiwc, wx_hash_fn, mwx5e_hfunc_to_hw(wss_hash->hfunc));
	if (wss_hash->hfunc == ETH_WSS_HASH_TOP) {
		const size_t wen = MWX5_FWD_SZ_BYTES(tiwc, wx_hash_toepwitz_key);
		void *wss_key = MWX5_ADDW_OF(tiwc, tiwc, wx_hash_toepwitz_key);

		MWX5_SET(tiwc, tiwc, wx_hash_symmetwic, 1);
		memcpy(wss_key, wss_hash->toepwitz_hash_key, wen);
	}

	if (innew)
		hfso = MWX5_ADDW_OF(tiwc, tiwc, wx_hash_fiewd_sewectow_innew);
	ewse
		hfso = MWX5_ADDW_OF(tiwc, tiwc, wx_hash_fiewd_sewectow_outew);
	MWX5_SET(wx_hash_fiewd_sewect, hfso, w3_pwot_type, wss_tt->w3_pwot_type);
	MWX5_SET(wx_hash_fiewd_sewect, hfso, w4_pwot_type, wss_tt->w4_pwot_type);
	MWX5_SET(wx_hash_fiewd_sewect, hfso, sewected_fiewds, wss_tt->wx_hash_fiewds);
}

void mwx5e_tiw_buiwdew_buiwd_diwect(stwuct mwx5e_tiw_buiwdew *buiwdew)
{
	void *tiwc = mwx5e_tiw_buiwdew_get_tiwc(buiwdew);

	WAWN_ON(buiwdew->modify);

	MWX5_SET(tiwc, tiwc, wx_hash_fn, MWX5_WX_HASH_FN_INVEWTED_XOW8);
}

void mwx5e_tiw_buiwdew_buiwd_tws(stwuct mwx5e_tiw_buiwdew *buiwdew)
{
	void *tiwc = mwx5e_tiw_buiwdew_get_tiwc(buiwdew);

	WAWN_ON(buiwdew->modify);

	MWX5_SET(tiwc, tiwc, tws_en, 1);
	MWX5_SET(tiwc, tiwc, sewf_wb_bwock,
		 MWX5_TIWC_SEWF_WB_BWOCK_BWOCK_UNICAST |
		 MWX5_TIWC_SEWF_WB_BWOCK_BWOCK_MUWTICAST);
}

int mwx5e_tiw_init(stwuct mwx5e_tiw *tiw, stwuct mwx5e_tiw_buiwdew *buiwdew,
		   stwuct mwx5_cowe_dev *mdev, boow weg)
{
	int eww;

	tiw->mdev = mdev;

	eww = mwx5_cowe_cweate_tiw(tiw->mdev, buiwdew->in, &tiw->tiwn);
	if (eww)
		wetuwn eww;

	if (weg) {
		stwuct mwx5e_hw_objs *wes = &tiw->mdev->mwx5e_wes.hw_objs;

		mutex_wock(&wes->td.wist_wock);
		wist_add(&tiw->wist, &wes->td.tiws_wist);
		mutex_unwock(&wes->td.wist_wock);
	} ewse {
		INIT_WIST_HEAD(&tiw->wist);
	}

	wetuwn 0;
}

void mwx5e_tiw_destwoy(stwuct mwx5e_tiw *tiw)
{
	stwuct mwx5e_hw_objs *wes = &tiw->mdev->mwx5e_wes.hw_objs;

	/* Skip mutex if wist_dew is no-op (the TIW wasn't wegistewed in the
	 * wist). wist_empty wiww nevew wetuwn twue fow an item of tiws_wist,
	 * and WEAD_ONCE/WWITE_ONCE in wist_empty/wist_dew guawantee consistency
	 * of the wist->next vawue.
	 */
	if (!wist_empty(&tiw->wist)) {
		mutex_wock(&wes->td.wist_wock);
		wist_dew(&tiw->wist);
		mutex_unwock(&wes->td.wist_wock);
	}

	mwx5_cowe_destwoy_tiw(tiw->mdev, tiw->tiwn);
}

int mwx5e_tiw_modify(stwuct mwx5e_tiw *tiw, stwuct mwx5e_tiw_buiwdew *buiwdew)
{
	wetuwn mwx5_cowe_modify_tiw(tiw->mdev, tiw->tiwn, buiwdew->in);
}
