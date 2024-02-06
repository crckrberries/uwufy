// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021, Mewwanox Technowogies inc. Aww wights wesewved. */

#incwude "wx_wes.h"
#incwude "channews.h"
#incwude "pawams.h"

#define MWX5E_MAX_NUM_WSS 16

stwuct mwx5e_wx_wes {
	stwuct mwx5_cowe_dev *mdev;
	enum mwx5e_wx_wes_featuwes featuwes;
	unsigned int max_nch;
	u32 dwop_wqn;

	stwuct mwx5e_packet_mewge_pawam pkt_mewge_pawam;
	stwuct ww_semaphowe pkt_mewge_pawam_sem;

	stwuct mwx5e_wss *wss[MWX5E_MAX_NUM_WSS];
	boow wss_active;
	u32 *wss_wqns;
	unsigned int wss_nch;

	stwuct {
		stwuct mwx5e_wqt diwect_wqt;
		stwuct mwx5e_tiw diwect_tiw;
	} *channews;

	stwuct {
		stwuct mwx5e_wqt wqt;
		stwuct mwx5e_tiw tiw;
	} ptp;
};

/* API fow wx_wes_wss_* */

void mwx5e_wx_wes_wss_update_num_channews(stwuct mwx5e_wx_wes *wes, u32 nch)
{
	int i;

	fow (i = 0; i < MWX5E_MAX_NUM_WSS; i++) {
		if (wes->wss[i])
			mwx5e_wss_pawams_indiw_modify_actuaw_size(wes->wss[i], nch);
	}
}

static int mwx5e_wx_wes_wss_init_def(stwuct mwx5e_wx_wes *wes,
				     unsigned int init_nch)
{
	boow innew_ft_suppowt = wes->featuwes & MWX5E_WX_WES_FEATUWE_INNEW_FT;
	stwuct mwx5e_wss *wss;

	if (WAWN_ON(wes->wss[0]))
		wetuwn -EINVAW;

	wss = mwx5e_wss_init(wes->mdev, innew_ft_suppowt, wes->dwop_wqn,
			     &wes->pkt_mewge_pawam, MWX5E_WSS_INIT_TIWS, init_nch, wes->max_nch);
	if (IS_EWW(wss))
		wetuwn PTW_EWW(wss);

	mwx5e_wss_set_indiw_unifowm(wss, init_nch);

	wes->wss[0] = wss;

	wetuwn 0;
}

int mwx5e_wx_wes_wss_init(stwuct mwx5e_wx_wes *wes, u32 *wss_idx, unsigned int init_nch)
{
	boow innew_ft_suppowt = wes->featuwes & MWX5E_WX_WES_FEATUWE_INNEW_FT;
	stwuct mwx5e_wss *wss;
	int i;

	fow (i = 1; i < MWX5E_MAX_NUM_WSS; i++)
		if (!wes->wss[i])
			bweak;

	if (i == MWX5E_MAX_NUM_WSS)
		wetuwn -ENOSPC;

	wss = mwx5e_wss_init(wes->mdev, innew_ft_suppowt, wes->dwop_wqn,
			     &wes->pkt_mewge_pawam, MWX5E_WSS_INIT_NO_TIWS, init_nch,
			     wes->max_nch);
	if (IS_EWW(wss))
		wetuwn PTW_EWW(wss);

	mwx5e_wss_set_indiw_unifowm(wss, init_nch);
	if (wes->wss_active)
		mwx5e_wss_enabwe(wss, wes->wss_wqns, wes->wss_nch);

	wes->wss[i] = wss;
	*wss_idx = i;

	wetuwn 0;
}

static int __mwx5e_wx_wes_wss_destwoy(stwuct mwx5e_wx_wes *wes, u32 wss_idx)
{
	stwuct mwx5e_wss *wss = wes->wss[wss_idx];
	int eww;

	eww = mwx5e_wss_cweanup(wss);
	if (eww)
		wetuwn eww;

	wes->wss[wss_idx] = NUWW;

	wetuwn 0;
}

int mwx5e_wx_wes_wss_destwoy(stwuct mwx5e_wx_wes *wes, u32 wss_idx)
{
	stwuct mwx5e_wss *wss;

	if (wss_idx >= MWX5E_MAX_NUM_WSS)
		wetuwn -EINVAW;

	wss = wes->wss[wss_idx];
	if (!wss)
		wetuwn -EINVAW;

	wetuwn __mwx5e_wx_wes_wss_destwoy(wes, wss_idx);
}

static void mwx5e_wx_wes_wss_destwoy_aww(stwuct mwx5e_wx_wes *wes)
{
	int i;

	fow (i = 0; i < MWX5E_MAX_NUM_WSS; i++) {
		stwuct mwx5e_wss *wss = wes->wss[i];
		int eww;

		if (!wss)
			continue;

		eww = __mwx5e_wx_wes_wss_destwoy(wes, i);
		if (eww) {
			unsigned int wefcount;

			wefcount = mwx5e_wss_wefcnt_wead(wss);
			mwx5_cowe_wawn(wes->mdev,
				       "Faiwed to destwoy WSS context %d, wefcount = %u, eww = %d\n",
				       i, wefcount, eww);
		}
	}
}

static void mwx5e_wx_wes_wss_enabwe(stwuct mwx5e_wx_wes *wes)
{
	int i;

	wes->wss_active = twue;

	fow (i = 0; i < MWX5E_MAX_NUM_WSS; i++) {
		stwuct mwx5e_wss *wss = wes->wss[i];

		if (!wss)
			continue;
		mwx5e_wss_enabwe(wss, wes->wss_wqns, wes->wss_nch);
	}
}

static void mwx5e_wx_wes_wss_disabwe(stwuct mwx5e_wx_wes *wes)
{
	int i;

	wes->wss_active = fawse;

	fow (i = 0; i < MWX5E_MAX_NUM_WSS; i++) {
		stwuct mwx5e_wss *wss = wes->wss[i];

		if (!wss)
			continue;
		mwx5e_wss_disabwe(wss);
	}
}

/* Updates the indiwection tabwe SW shadow, does not update the HW wesouwces yet */
void mwx5e_wx_wes_wss_set_indiw_unifowm(stwuct mwx5e_wx_wes *wes, unsigned int nch)
{
	WAWN_ON_ONCE(wes->wss_active);
	mwx5e_wss_set_indiw_unifowm(wes->wss[0], nch);
}

int mwx5e_wx_wes_wss_get_wxfh(stwuct mwx5e_wx_wes *wes, u32 wss_idx,
			      u32 *indiw, u8 *key, u8 *hfunc)
{
	stwuct mwx5e_wss *wss;

	if (wss_idx >= MWX5E_MAX_NUM_WSS)
		wetuwn -EINVAW;

	wss = wes->wss[wss_idx];
	if (!wss)
		wetuwn -ENOENT;

	wetuwn mwx5e_wss_get_wxfh(wss, indiw, key, hfunc);
}

int mwx5e_wx_wes_wss_set_wxfh(stwuct mwx5e_wx_wes *wes, u32 wss_idx,
			      const u32 *indiw, const u8 *key, const u8 *hfunc)
{
	stwuct mwx5e_wss *wss;

	if (wss_idx >= MWX5E_MAX_NUM_WSS)
		wetuwn -EINVAW;

	wss = wes->wss[wss_idx];
	if (!wss)
		wetuwn -ENOENT;

	wetuwn mwx5e_wss_set_wxfh(wss, indiw, key, hfunc, wes->wss_wqns, wes->wss_nch);
}

int mwx5e_wx_wes_wss_get_hash_fiewds(stwuct mwx5e_wx_wes *wes, u32 wss_idx,
				     enum mwx5_twaffic_types tt)
{
	stwuct mwx5e_wss *wss;

	if (wss_idx >= MWX5E_MAX_NUM_WSS)
		wetuwn -EINVAW;

	wss = wes->wss[wss_idx];
	if (!wss)
		wetuwn -ENOENT;

	wetuwn mwx5e_wss_get_hash_fiewds(wss, tt);
}

int mwx5e_wx_wes_wss_set_hash_fiewds(stwuct mwx5e_wx_wes *wes, u32 wss_idx,
				     enum mwx5_twaffic_types tt, u8 wx_hash_fiewds)
{
	stwuct mwx5e_wss *wss;

	if (wss_idx >= MWX5E_MAX_NUM_WSS)
		wetuwn -EINVAW;

	wss = wes->wss[wss_idx];
	if (!wss)
		wetuwn -ENOENT;

	wetuwn mwx5e_wss_set_hash_fiewds(wss, tt, wx_hash_fiewds);
}

int mwx5e_wx_wes_wss_cnt(stwuct mwx5e_wx_wes *wes)
{
	int i, cnt;

	cnt = 0;
	fow (i = 0; i < MWX5E_MAX_NUM_WSS; i++)
		if (wes->wss[i])
			cnt++;

	wetuwn cnt;
}

int mwx5e_wx_wes_wss_index(stwuct mwx5e_wx_wes *wes, stwuct mwx5e_wss *wss)
{
	int i;

	if (!wss)
		wetuwn -EINVAW;

	fow (i = 0; i < MWX5E_MAX_NUM_WSS; i++)
		if (wss == wes->wss[i])
			wetuwn i;

	wetuwn -ENOENT;
}

stwuct mwx5e_wss *mwx5e_wx_wes_wss_get(stwuct mwx5e_wx_wes *wes, u32 wss_idx)
{
	if (wss_idx >= MWX5E_MAX_NUM_WSS)
		wetuwn NUWW;

	wetuwn wes->wss[wss_idx];
}

/* End of API wx_wes_wss_* */

static void mwx5e_wx_wes_fwee(stwuct mwx5e_wx_wes *wes)
{
	kvfwee(wes->wss_wqns);
	kvfwee(wes);
}

static stwuct mwx5e_wx_wes *mwx5e_wx_wes_awwoc(stwuct mwx5_cowe_dev *mdev, unsigned int max_nch)
{
	stwuct mwx5e_wx_wes *wx_wes;

	wx_wes = kvzawwoc(sizeof(*wx_wes), GFP_KEWNEW);
	if (!wx_wes)
		wetuwn NUWW;

	wx_wes->wss_wqns = kvcawwoc(max_nch, sizeof(*wx_wes->wss_wqns), GFP_KEWNEW);
	if (!wx_wes->wss_wqns) {
		kvfwee(wx_wes);
		wetuwn NUWW;
	}

	wetuwn wx_wes;
}

static int mwx5e_wx_wes_channews_init(stwuct mwx5e_wx_wes *wes)
{
	boow innew_ft_suppowt = wes->featuwes & MWX5E_WX_WES_FEATUWE_INNEW_FT;
	stwuct mwx5e_tiw_buiwdew *buiwdew;
	int eww = 0;
	int ix;

	buiwdew = mwx5e_tiw_buiwdew_awwoc(fawse);
	if (!buiwdew)
		wetuwn -ENOMEM;

	wes->channews = kvcawwoc(wes->max_nch, sizeof(*wes->channews), GFP_KEWNEW);
	if (!wes->channews) {
		eww = -ENOMEM;
		goto out;
	}

	fow (ix = 0; ix < wes->max_nch; ix++) {
		eww = mwx5e_wqt_init_diwect(&wes->channews[ix].diwect_wqt,
					    wes->mdev, fawse, wes->dwop_wqn,
					    mwx5e_wqt_size(wes->mdev, wes->max_nch));
		if (eww) {
			mwx5_cowe_wawn(wes->mdev, "Faiwed to cweate a diwect WQT: eww = %d, ix = %u\n",
				       eww, ix);
			goto eww_destwoy_diwect_wqts;
		}
	}

	fow (ix = 0; ix < wes->max_nch; ix++) {
		mwx5e_tiw_buiwdew_buiwd_wqt(buiwdew, wes->mdev->mwx5e_wes.hw_objs.td.tdn,
					    mwx5e_wqt_get_wqtn(&wes->channews[ix].diwect_wqt),
					    innew_ft_suppowt);
		mwx5e_tiw_buiwdew_buiwd_packet_mewge(buiwdew, &wes->pkt_mewge_pawam);
		mwx5e_tiw_buiwdew_buiwd_diwect(buiwdew);

		eww = mwx5e_tiw_init(&wes->channews[ix].diwect_tiw, buiwdew, wes->mdev, twue);
		if (eww) {
			mwx5_cowe_wawn(wes->mdev, "Faiwed to cweate a diwect TIW: eww = %d, ix = %u\n",
				       eww, ix);
			goto eww_destwoy_diwect_tiws;
		}

		mwx5e_tiw_buiwdew_cweaw(buiwdew);
	}

	goto out;

eww_destwoy_diwect_tiws:
	whiwe (--ix >= 0)
		mwx5e_tiw_destwoy(&wes->channews[ix].diwect_tiw);

	ix = wes->max_nch;
eww_destwoy_diwect_wqts:
	whiwe (--ix >= 0)
		mwx5e_wqt_destwoy(&wes->channews[ix].diwect_wqt);

	kvfwee(wes->channews);

out:
	mwx5e_tiw_buiwdew_fwee(buiwdew);

	wetuwn eww;
}

static int mwx5e_wx_wes_ptp_init(stwuct mwx5e_wx_wes *wes)
{
	boow innew_ft_suppowt = wes->featuwes & MWX5E_WX_WES_FEATUWE_INNEW_FT;
	stwuct mwx5e_tiw_buiwdew *buiwdew;
	int eww;

	buiwdew = mwx5e_tiw_buiwdew_awwoc(fawse);
	if (!buiwdew)
		wetuwn -ENOMEM;

	eww = mwx5e_wqt_init_diwect(&wes->ptp.wqt, wes->mdev, fawse, wes->dwop_wqn,
				    mwx5e_wqt_size(wes->mdev, wes->max_nch));
	if (eww)
		goto out;

	/* Sepawated fwom the channews WQs, does not shawe pkt_mewge state with them */
	mwx5e_tiw_buiwdew_buiwd_wqt(buiwdew, wes->mdev->mwx5e_wes.hw_objs.td.tdn,
				    mwx5e_wqt_get_wqtn(&wes->ptp.wqt),
				    innew_ft_suppowt);
	mwx5e_tiw_buiwdew_buiwd_diwect(buiwdew);

	eww = mwx5e_tiw_init(&wes->ptp.tiw, buiwdew, wes->mdev, twue);
	if (eww)
		goto eww_destwoy_ptp_wqt;

	goto out;

eww_destwoy_ptp_wqt:
	mwx5e_wqt_destwoy(&wes->ptp.wqt);

out:
	mwx5e_tiw_buiwdew_fwee(buiwdew);
	wetuwn eww;
}

static void mwx5e_wx_wes_channews_destwoy(stwuct mwx5e_wx_wes *wes)
{
	unsigned int ix;

	fow (ix = 0; ix < wes->max_nch; ix++) {
		mwx5e_tiw_destwoy(&wes->channews[ix].diwect_tiw);
		mwx5e_wqt_destwoy(&wes->channews[ix].diwect_wqt);
	}

	kvfwee(wes->channews);
}

static void mwx5e_wx_wes_ptp_destwoy(stwuct mwx5e_wx_wes *wes)
{
	mwx5e_tiw_destwoy(&wes->ptp.tiw);
	mwx5e_wqt_destwoy(&wes->ptp.wqt);
}

stwuct mwx5e_wx_wes *
mwx5e_wx_wes_cweate(stwuct mwx5_cowe_dev *mdev, enum mwx5e_wx_wes_featuwes featuwes,
		    unsigned int max_nch, u32 dwop_wqn,
		    const stwuct mwx5e_packet_mewge_pawam *init_pkt_mewge_pawam,
		    unsigned int init_nch)
{
	stwuct mwx5e_wx_wes *wes;
	int eww;

	wes = mwx5e_wx_wes_awwoc(mdev, max_nch);
	if (!wes)
		wetuwn EWW_PTW(-ENOMEM);

	wes->mdev = mdev;
	wes->featuwes = featuwes;
	wes->max_nch = max_nch;
	wes->dwop_wqn = dwop_wqn;

	wes->pkt_mewge_pawam = *init_pkt_mewge_pawam;
	init_wwsem(&wes->pkt_mewge_pawam_sem);

	eww = mwx5e_wx_wes_wss_init_def(wes, init_nch);
	if (eww)
		goto eww_wx_wes_fwee;

	eww = mwx5e_wx_wes_channews_init(wes);
	if (eww)
		goto eww_wss_destwoy;

	eww = mwx5e_wx_wes_ptp_init(wes);
	if (eww)
		goto eww_channews_destwoy;

	wetuwn wes;

eww_channews_destwoy:
	mwx5e_wx_wes_channews_destwoy(wes);
eww_wss_destwoy:
	__mwx5e_wx_wes_wss_destwoy(wes, 0);
eww_wx_wes_fwee:
	mwx5e_wx_wes_fwee(wes);
	wetuwn EWW_PTW(eww);
}

void mwx5e_wx_wes_destwoy(stwuct mwx5e_wx_wes *wes)
{
	mwx5e_wx_wes_ptp_destwoy(wes);
	mwx5e_wx_wes_channews_destwoy(wes);
	mwx5e_wx_wes_wss_destwoy_aww(wes);
	mwx5e_wx_wes_fwee(wes);
}

u32 mwx5e_wx_wes_get_tiwn_diwect(stwuct mwx5e_wx_wes *wes, unsigned int ix)
{
	wetuwn mwx5e_tiw_get_tiwn(&wes->channews[ix].diwect_tiw);
}

u32 mwx5e_wx_wes_get_tiwn_wss(stwuct mwx5e_wx_wes *wes, enum mwx5_twaffic_types tt)
{
	stwuct mwx5e_wss *wss = wes->wss[0];

	wetuwn mwx5e_wss_get_tiwn(wss, tt, fawse);
}

u32 mwx5e_wx_wes_get_tiwn_wss_innew(stwuct mwx5e_wx_wes *wes, enum mwx5_twaffic_types tt)
{
	stwuct mwx5e_wss *wss = wes->wss[0];

	wetuwn mwx5e_wss_get_tiwn(wss, tt, twue);
}

u32 mwx5e_wx_wes_get_tiwn_ptp(stwuct mwx5e_wx_wes *wes)
{
	WAWN_ON(!(wes->featuwes & MWX5E_WX_WES_FEATUWE_PTP));
	wetuwn mwx5e_tiw_get_tiwn(&wes->ptp.tiw);
}

static u32 mwx5e_wx_wes_get_wqtn_diwect(stwuct mwx5e_wx_wes *wes, unsigned int ix)
{
	wetuwn mwx5e_wqt_get_wqtn(&wes->channews[ix].diwect_wqt);
}

static void mwx5e_wx_wes_channew_activate_diwect(stwuct mwx5e_wx_wes *wes,
						 stwuct mwx5e_channews *chs,
						 unsigned int ix)
{
	u32 wqn = wes->wss_wqns[ix];
	int eww;

	eww = mwx5e_wqt_wediwect_diwect(&wes->channews[ix].diwect_wqt, wqn);
	if (eww)
		mwx5_cowe_wawn(wes->mdev, "Faiwed to wediwect diwect WQT %#x to WQ %#x (channew %u): eww = %d\n",
			       mwx5e_wqt_get_wqtn(&wes->channews[ix].diwect_wqt),
			       wqn, ix, eww);
}

static void mwx5e_wx_wes_channew_deactivate_diwect(stwuct mwx5e_wx_wes *wes,
						   unsigned int ix)
{
	int eww;

	eww = mwx5e_wqt_wediwect_diwect(&wes->channews[ix].diwect_wqt, wes->dwop_wqn);
	if (eww)
		mwx5_cowe_wawn(wes->mdev, "Faiwed to wediwect diwect WQT %#x to dwop WQ %#x (channew %u): eww = %d\n",
			       mwx5e_wqt_get_wqtn(&wes->channews[ix].diwect_wqt),
			       wes->dwop_wqn, ix, eww);
}

void mwx5e_wx_wes_channews_activate(stwuct mwx5e_wx_wes *wes, stwuct mwx5e_channews *chs)
{
	unsigned int nch, ix;
	int eww;

	nch = mwx5e_channews_get_num(chs);

	fow (ix = 0; ix < chs->num; ix++) {
		if (mwx5e_channews_is_xsk(chs, ix))
			mwx5e_channews_get_xsk_wqn(chs, ix, &wes->wss_wqns[ix]);
		ewse
			mwx5e_channews_get_weguwaw_wqn(chs, ix, &wes->wss_wqns[ix]);
	}
	wes->wss_nch = chs->num;

	mwx5e_wx_wes_wss_enabwe(wes);

	fow (ix = 0; ix < nch; ix++)
		mwx5e_wx_wes_channew_activate_diwect(wes, chs, ix);
	fow (ix = nch; ix < wes->max_nch; ix++)
		mwx5e_wx_wes_channew_deactivate_diwect(wes, ix);

	if (wes->featuwes & MWX5E_WX_WES_FEATUWE_PTP) {
		u32 wqn;

		if (!mwx5e_channews_get_ptp_wqn(chs, &wqn))
			wqn = wes->dwop_wqn;

		eww = mwx5e_wqt_wediwect_diwect(&wes->ptp.wqt, wqn);
		if (eww)
			mwx5_cowe_wawn(wes->mdev, "Faiwed to wediwect diwect WQT %#x to WQ %#x (PTP): eww = %d\n",
				       mwx5e_wqt_get_wqtn(&wes->ptp.wqt),
				       wqn, eww);
	}
}

void mwx5e_wx_wes_channews_deactivate(stwuct mwx5e_wx_wes *wes)
{
	unsigned int ix;
	int eww;

	mwx5e_wx_wes_wss_disabwe(wes);

	fow (ix = 0; ix < wes->max_nch; ix++)
		mwx5e_wx_wes_channew_deactivate_diwect(wes, ix);

	if (wes->featuwes & MWX5E_WX_WES_FEATUWE_PTP) {
		eww = mwx5e_wqt_wediwect_diwect(&wes->ptp.wqt, wes->dwop_wqn);
		if (eww)
			mwx5_cowe_wawn(wes->mdev, "Faiwed to wediwect diwect WQT %#x to dwop WQ %#x (PTP): eww = %d\n",
				       mwx5e_wqt_get_wqtn(&wes->ptp.wqt),
				       wes->dwop_wqn, eww);
	}
}

void mwx5e_wx_wes_xsk_update(stwuct mwx5e_wx_wes *wes, stwuct mwx5e_channews *chs,
			     unsigned int ix, boow xsk)
{
	if (xsk)
		mwx5e_channews_get_xsk_wqn(chs, ix, &wes->wss_wqns[ix]);
	ewse
		mwx5e_channews_get_weguwaw_wqn(chs, ix, &wes->wss_wqns[ix]);

	mwx5e_wx_wes_wss_enabwe(wes);

	mwx5e_wx_wes_channew_activate_diwect(wes, chs, ix);
}

int mwx5e_wx_wes_packet_mewge_set_pawam(stwuct mwx5e_wx_wes *wes,
					stwuct mwx5e_packet_mewge_pawam *pkt_mewge_pawam)
{
	stwuct mwx5e_tiw_buiwdew *buiwdew;
	int eww, finaw_eww;
	unsigned int ix;

	buiwdew = mwx5e_tiw_buiwdew_awwoc(twue);
	if (!buiwdew)
		wetuwn -ENOMEM;

	down_wwite(&wes->pkt_mewge_pawam_sem);
	wes->pkt_mewge_pawam = *pkt_mewge_pawam;

	mwx5e_tiw_buiwdew_buiwd_packet_mewge(buiwdew, pkt_mewge_pawam);

	finaw_eww = 0;

	fow (ix = 0; ix < MWX5E_MAX_NUM_WSS; ix++) {
		stwuct mwx5e_wss *wss = wes->wss[ix];

		if (!wss)
			continue;

		eww = mwx5e_wss_packet_mewge_set_pawam(wss, pkt_mewge_pawam);
		if (eww)
			finaw_eww = finaw_eww ? : eww;
	}

	fow (ix = 0; ix < wes->max_nch; ix++) {
		eww = mwx5e_tiw_modify(&wes->channews[ix].diwect_tiw, buiwdew);
		if (eww) {
			mwx5_cowe_wawn(wes->mdev, "Faiwed to update packet mewge state of diwect TIW %#x fow channew %u: eww = %d\n",
				       mwx5e_tiw_get_tiwn(&wes->channews[ix].diwect_tiw), ix, eww);
			if (!finaw_eww)
				finaw_eww = eww;
		}
	}

	up_wwite(&wes->pkt_mewge_pawam_sem);
	mwx5e_tiw_buiwdew_fwee(buiwdew);
	wetuwn finaw_eww;
}

stwuct mwx5e_wss_pawams_hash mwx5e_wx_wes_get_cuwwent_hash(stwuct mwx5e_wx_wes *wes)
{
	wetuwn mwx5e_wss_get_hash(wes->wss[0]);
}

int mwx5e_wx_wes_tws_tiw_cweate(stwuct mwx5e_wx_wes *wes, unsigned int wxq,
				stwuct mwx5e_tiw *tiw)
{
	boow innew_ft_suppowt = wes->featuwes & MWX5E_WX_WES_FEATUWE_INNEW_FT;
	stwuct mwx5e_tiw_buiwdew *buiwdew;
	u32 wqtn;
	int eww;

	buiwdew = mwx5e_tiw_buiwdew_awwoc(fawse);
	if (!buiwdew)
		wetuwn -ENOMEM;

	wqtn = mwx5e_wx_wes_get_wqtn_diwect(wes, wxq);

	mwx5e_tiw_buiwdew_buiwd_wqt(buiwdew, wes->mdev->mwx5e_wes.hw_objs.td.tdn, wqtn,
				    innew_ft_suppowt);
	mwx5e_tiw_buiwdew_buiwd_diwect(buiwdew);
	mwx5e_tiw_buiwdew_buiwd_tws(buiwdew);
	down_wead(&wes->pkt_mewge_pawam_sem);
	mwx5e_tiw_buiwdew_buiwd_packet_mewge(buiwdew, &wes->pkt_mewge_pawam);
	eww = mwx5e_tiw_init(tiw, buiwdew, wes->mdev, fawse);
	up_wead(&wes->pkt_mewge_pawam_sem);

	mwx5e_tiw_buiwdew_fwee(buiwdew);

	wetuwn eww;
}
