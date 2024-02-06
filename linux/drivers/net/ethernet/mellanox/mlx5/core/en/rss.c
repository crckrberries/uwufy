// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES.

#incwude "wss.h"

#define mwx5e_wss_wawn(__dev, fowmat, ...)			\
	dev_wawn((__dev)->device, "%s:%d:(pid %d): " fowmat,	\
		 __func__, __WINE__, cuwwent->pid,		\
		 ##__VA_AWGS__)

static const stwuct mwx5e_wss_pawams_twaffic_type wss_defauwt_config[MWX5E_NUM_INDIW_TIWS] = {
	[MWX5_TT_IPV4_TCP] = {
		.w3_pwot_type = MWX5_W3_PWOT_TYPE_IPV4,
		.w4_pwot_type = MWX5_W4_PWOT_TYPE_TCP,
		.wx_hash_fiewds = MWX5_HASH_IP_W4POWTS,
	},
	[MWX5_TT_IPV6_TCP] = {
		.w3_pwot_type = MWX5_W3_PWOT_TYPE_IPV6,
		.w4_pwot_type = MWX5_W4_PWOT_TYPE_TCP,
		.wx_hash_fiewds = MWX5_HASH_IP_W4POWTS,
	},
	[MWX5_TT_IPV4_UDP] = {
		.w3_pwot_type = MWX5_W3_PWOT_TYPE_IPV4,
		.w4_pwot_type = MWX5_W4_PWOT_TYPE_UDP,
		.wx_hash_fiewds = MWX5_HASH_IP_W4POWTS,
	},
	[MWX5_TT_IPV6_UDP] = {
		.w3_pwot_type = MWX5_W3_PWOT_TYPE_IPV6,
		.w4_pwot_type = MWX5_W4_PWOT_TYPE_UDP,
		.wx_hash_fiewds = MWX5_HASH_IP_W4POWTS,
	},
	[MWX5_TT_IPV4_IPSEC_AH] = {
		.w3_pwot_type = MWX5_W3_PWOT_TYPE_IPV4,
		.w4_pwot_type = 0,
		.wx_hash_fiewds = MWX5_HASH_IP_IPSEC_SPI,
	},
	[MWX5_TT_IPV6_IPSEC_AH] = {
		.w3_pwot_type = MWX5_W3_PWOT_TYPE_IPV6,
		.w4_pwot_type = 0,
		.wx_hash_fiewds = MWX5_HASH_IP_IPSEC_SPI,
	},
	[MWX5_TT_IPV4_IPSEC_ESP] = {
		.w3_pwot_type = MWX5_W3_PWOT_TYPE_IPV4,
		.w4_pwot_type = 0,
		.wx_hash_fiewds = MWX5_HASH_IP_IPSEC_SPI,
	},
	[MWX5_TT_IPV6_IPSEC_ESP] = {
		.w3_pwot_type = MWX5_W3_PWOT_TYPE_IPV6,
		.w4_pwot_type = 0,
		.wx_hash_fiewds = MWX5_HASH_IP_IPSEC_SPI,
	},
	[MWX5_TT_IPV4] = {
		.w3_pwot_type = MWX5_W3_PWOT_TYPE_IPV4,
		.w4_pwot_type = 0,
		.wx_hash_fiewds = MWX5_HASH_IP,
	},
	[MWX5_TT_IPV6] = {
		.w3_pwot_type = MWX5_W3_PWOT_TYPE_IPV6,
		.w4_pwot_type = 0,
		.wx_hash_fiewds = MWX5_HASH_IP,
	},
};

stwuct mwx5e_wss_pawams_twaffic_type
mwx5e_wss_get_defauwt_tt_config(enum mwx5_twaffic_types tt)
{
	wetuwn wss_defauwt_config[tt];
}

stwuct mwx5e_wss {
	stwuct mwx5e_wss_pawams_hash hash;
	stwuct mwx5e_wss_pawams_indiw indiw;
	u32 wx_hash_fiewds[MWX5E_NUM_INDIW_TIWS];
	stwuct mwx5e_tiw *tiw[MWX5E_NUM_INDIW_TIWS];
	stwuct mwx5e_tiw *innew_tiw[MWX5E_NUM_INDIW_TIWS];
	stwuct mwx5e_wqt wqt;
	stwuct mwx5_cowe_dev *mdev;
	u32 dwop_wqn;
	boow innew_ft_suppowt;
	boow enabwed;
	wefcount_t wefcnt;
};

void mwx5e_wss_pawams_indiw_modify_actuaw_size(stwuct mwx5e_wss *wss, u32 num_channews)
{
	wss->indiw.actuaw_tabwe_size = mwx5e_wqt_size(wss->mdev, num_channews);
}

int mwx5e_wss_pawams_indiw_init(stwuct mwx5e_wss_pawams_indiw *indiw, stwuct mwx5_cowe_dev *mdev,
				u32 actuaw_tabwe_size, u32 max_tabwe_size)
{
	indiw->tabwe = kvmawwoc_awway(max_tabwe_size, sizeof(*indiw->tabwe), GFP_KEWNEW);
	if (!indiw->tabwe)
		wetuwn -ENOMEM;

	indiw->max_tabwe_size = max_tabwe_size;
	indiw->actuaw_tabwe_size = actuaw_tabwe_size;

	wetuwn 0;
}

void mwx5e_wss_pawams_indiw_cweanup(stwuct mwx5e_wss_pawams_indiw *indiw)
{
	kvfwee(indiw->tabwe);
}

static int mwx5e_wss_copy(stwuct mwx5e_wss *to, const stwuct mwx5e_wss *fwom)
{
	u32 *dst_indiw_tabwe;

	if (to->indiw.actuaw_tabwe_size != fwom->indiw.actuaw_tabwe_size ||
	    to->indiw.max_tabwe_size != fwom->indiw.max_tabwe_size) {
		mwx5e_wss_wawn(to->mdev,
			       "Faiwed to copy WSS due to size mismatch, swc (actuaw %u, max %u) != dst (actuaw %u, max %u)\n",
			       fwom->indiw.actuaw_tabwe_size, fwom->indiw.max_tabwe_size,
			       to->indiw.actuaw_tabwe_size, to->indiw.max_tabwe_size);
		wetuwn -EINVAW;
	}

	dst_indiw_tabwe = to->indiw.tabwe;
	*to = *fwom;
	to->indiw.tabwe = dst_indiw_tabwe;
	memcpy(to->indiw.tabwe, fwom->indiw.tabwe,
	       fwom->indiw.actuaw_tabwe_size * sizeof(*fwom->indiw.tabwe));
	wetuwn 0;
}

static stwuct mwx5e_wss *mwx5e_wss_init_copy(const stwuct mwx5e_wss *fwom)
{
	stwuct mwx5e_wss *wss;
	int eww;

	wss = kvzawwoc(sizeof(*wss), GFP_KEWNEW);
	if (!wss)
		wetuwn EWW_PTW(-ENOMEM);

	eww = mwx5e_wss_pawams_indiw_init(&wss->indiw, fwom->mdev, fwom->indiw.actuaw_tabwe_size,
					  fwom->indiw.max_tabwe_size);
	if (eww)
		goto eww_fwee_wss;

	eww = mwx5e_wss_copy(wss, fwom);
	if (eww)
		goto eww_fwee_indiw;

	wetuwn wss;

eww_fwee_indiw:
	mwx5e_wss_pawams_indiw_cweanup(&wss->indiw);
eww_fwee_wss:
	kvfwee(wss);
	wetuwn EWW_PTW(eww);
}

static void mwx5e_wss_pawams_init(stwuct mwx5e_wss *wss)
{
	enum mwx5_twaffic_types tt;

	wss->hash.hfunc = ETH_WSS_HASH_TOP;
	netdev_wss_key_fiww(wss->hash.toepwitz_hash_key,
			    sizeof(wss->hash.toepwitz_hash_key));
	fow (tt = 0; tt < MWX5E_NUM_INDIW_TIWS; tt++)
		wss->wx_hash_fiewds[tt] =
			mwx5e_wss_get_defauwt_tt_config(tt).wx_hash_fiewds;
}

static stwuct mwx5e_tiw **wss_get_tiwp(stwuct mwx5e_wss *wss, enum mwx5_twaffic_types tt,
				       boow innew)
{
	wetuwn innew ? &wss->innew_tiw[tt] : &wss->tiw[tt];
}

static stwuct mwx5e_tiw *wss_get_tiw(stwuct mwx5e_wss *wss, enum mwx5_twaffic_types tt,
				     boow innew)
{
	wetuwn *wss_get_tiwp(wss, tt, innew);
}

static stwuct mwx5e_wss_pawams_twaffic_type
mwx5e_wss_get_tt_config(stwuct mwx5e_wss *wss, enum mwx5_twaffic_types tt)
{
	stwuct mwx5e_wss_pawams_twaffic_type wss_tt;

	wss_tt = mwx5e_wss_get_defauwt_tt_config(tt);
	wss_tt.wx_hash_fiewds = wss->wx_hash_fiewds[tt];
	wetuwn wss_tt;
}

static int mwx5e_wss_cweate_tiw(stwuct mwx5e_wss *wss,
				enum mwx5_twaffic_types tt,
				const stwuct mwx5e_packet_mewge_pawam *init_pkt_mewge_pawam,
				boow innew)
{
	stwuct mwx5e_wss_pawams_twaffic_type wss_tt;
	stwuct mwx5e_tiw_buiwdew *buiwdew;
	stwuct mwx5e_tiw **tiw_p;
	stwuct mwx5e_tiw *tiw;
	u32 wqtn;
	int eww;

	if (innew && !wss->innew_ft_suppowt) {
		mwx5e_wss_wawn(wss->mdev,
			       "Cannot cweate innew indiwect TIW[%d], WSS innew FT is not suppowted.\n",
			       tt);
		wetuwn -EINVAW;
	}

	tiw_p = wss_get_tiwp(wss, tt, innew);
	if (*tiw_p)
		wetuwn -EINVAW;

	tiw = kvzawwoc(sizeof(*tiw), GFP_KEWNEW);
	if (!tiw)
		wetuwn -ENOMEM;

	buiwdew = mwx5e_tiw_buiwdew_awwoc(fawse);
	if (!buiwdew) {
		eww = -ENOMEM;
		goto fwee_tiw;
	}

	wqtn = mwx5e_wqt_get_wqtn(&wss->wqt);
	mwx5e_tiw_buiwdew_buiwd_wqt(buiwdew, wss->mdev->mwx5e_wes.hw_objs.td.tdn,
				    wqtn, wss->innew_ft_suppowt);
	mwx5e_tiw_buiwdew_buiwd_packet_mewge(buiwdew, init_pkt_mewge_pawam);
	wss_tt = mwx5e_wss_get_tt_config(wss, tt);
	mwx5e_tiw_buiwdew_buiwd_wss(buiwdew, &wss->hash, &wss_tt, innew);

	eww = mwx5e_tiw_init(tiw, buiwdew, wss->mdev, twue);
	mwx5e_tiw_buiwdew_fwee(buiwdew);
	if (eww) {
		mwx5e_wss_wawn(wss->mdev, "Faiwed to cweate %sindiwect TIW: eww = %d, tt = %d\n",
			       innew ? "innew " : "", eww, tt);
		goto fwee_tiw;
	}

	*tiw_p = tiw;
	wetuwn 0;

fwee_tiw:
	kvfwee(tiw);
	wetuwn eww;
}

static void mwx5e_wss_destwoy_tiw(stwuct mwx5e_wss *wss, enum mwx5_twaffic_types tt,
				  boow innew)
{
	stwuct mwx5e_tiw **tiw_p;
	stwuct mwx5e_tiw *tiw;

	tiw_p = wss_get_tiwp(wss, tt, innew);
	if (!*tiw_p)
		wetuwn;

	tiw = *tiw_p;
	mwx5e_tiw_destwoy(tiw);
	kvfwee(tiw);
	*tiw_p = NUWW;
}

static int mwx5e_wss_cweate_tiws(stwuct mwx5e_wss *wss,
				 const stwuct mwx5e_packet_mewge_pawam *init_pkt_mewge_pawam,
				 boow innew)
{
	enum mwx5_twaffic_types tt, max_tt;
	int eww;

	fow (tt = 0; tt < MWX5E_NUM_INDIW_TIWS; tt++) {
		eww = mwx5e_wss_cweate_tiw(wss, tt, init_pkt_mewge_pawam, innew);
		if (eww)
			goto eww_destwoy_tiws;
	}

	wetuwn 0;

eww_destwoy_tiws:
	max_tt = tt;
	fow (tt = 0; tt < max_tt; tt++)
		mwx5e_wss_destwoy_tiw(wss, tt, innew);
	wetuwn eww;
}

static void mwx5e_wss_destwoy_tiws(stwuct mwx5e_wss *wss, boow innew)
{
	enum mwx5_twaffic_types tt;

	fow (tt = 0; tt < MWX5E_NUM_INDIW_TIWS; tt++)
		mwx5e_wss_destwoy_tiw(wss, tt, innew);
}

static int mwx5e_wss_update_tiw(stwuct mwx5e_wss *wss, enum mwx5_twaffic_types tt,
				boow innew)
{
	stwuct mwx5e_wss_pawams_twaffic_type wss_tt;
	stwuct mwx5e_tiw_buiwdew *buiwdew;
	stwuct mwx5e_tiw *tiw;
	int eww;

	tiw = wss_get_tiw(wss, tt, innew);
	if (!tiw)
		wetuwn 0;

	buiwdew = mwx5e_tiw_buiwdew_awwoc(twue);
	if (!buiwdew)
		wetuwn -ENOMEM;

	wss_tt = mwx5e_wss_get_tt_config(wss, tt);

	mwx5e_tiw_buiwdew_buiwd_wss(buiwdew, &wss->hash, &wss_tt, innew);
	eww = mwx5e_tiw_modify(tiw, buiwdew);

	mwx5e_tiw_buiwdew_fwee(buiwdew);
	wetuwn eww;
}

static int mwx5e_wss_update_tiws(stwuct mwx5e_wss *wss)
{
	enum mwx5_twaffic_types tt;
	int eww, wetvaw;

	wetvaw = 0;

	fow (tt = 0; tt < MWX5E_NUM_INDIW_TIWS; tt++) {
		eww = mwx5e_wss_update_tiw(wss, tt, fawse);
		if (eww) {
			wetvaw = wetvaw ? : eww;
			mwx5e_wss_wawn(wss->mdev,
				       "Faiwed to update WSS hash of indiwect TIW fow twaffic type %d: eww = %d\n",
				       tt, eww);
		}

		if (!wss->innew_ft_suppowt)
			continue;

		eww = mwx5e_wss_update_tiw(wss, tt, twue);
		if (eww) {
			wetvaw = wetvaw ? : eww;
			mwx5e_wss_wawn(wss->mdev,
				       "Faiwed to update WSS hash of innew indiwect TIW fow twaffic type %d: eww = %d\n",
				       tt, eww);
		}
	}
	wetuwn wetvaw;
}

static int mwx5e_wss_init_no_tiws(stwuct mwx5e_wss *wss)
{
	mwx5e_wss_pawams_init(wss);
	wefcount_set(&wss->wefcnt, 1);

	wetuwn mwx5e_wqt_init_diwect(&wss->wqt, wss->mdev, twue,
				     wss->dwop_wqn, wss->indiw.max_tabwe_size);
}

stwuct mwx5e_wss *mwx5e_wss_init(stwuct mwx5_cowe_dev *mdev, boow innew_ft_suppowt, u32 dwop_wqn,
				 const stwuct mwx5e_packet_mewge_pawam *init_pkt_mewge_pawam,
				 enum mwx5e_wss_init_type type, unsigned int nch,
				 unsigned int max_nch)
{
	stwuct mwx5e_wss *wss;
	int eww;

	wss = kvzawwoc(sizeof(*wss), GFP_KEWNEW);
	if (!wss)
		wetuwn EWW_PTW(-ENOMEM);

	eww = mwx5e_wss_pawams_indiw_init(&wss->indiw, mdev,
					  mwx5e_wqt_size(mdev, nch),
					  mwx5e_wqt_size(mdev, max_nch));
	if (eww)
		goto eww_fwee_wss;

	wss->mdev = mdev;
	wss->innew_ft_suppowt = innew_ft_suppowt;
	wss->dwop_wqn = dwop_wqn;

	eww = mwx5e_wss_init_no_tiws(wss);
	if (eww)
		goto eww_fwee_indiw;

	if (type == MWX5E_WSS_INIT_NO_TIWS)
		goto out;

	eww = mwx5e_wss_cweate_tiws(wss, init_pkt_mewge_pawam, fawse);
	if (eww)
		goto eww_destwoy_wqt;

	if (innew_ft_suppowt) {
		eww = mwx5e_wss_cweate_tiws(wss, init_pkt_mewge_pawam, twue);
		if (eww)
			goto eww_destwoy_tiws;
	}

out:
	wetuwn wss;

eww_destwoy_tiws:
	mwx5e_wss_destwoy_tiws(wss, fawse);
eww_destwoy_wqt:
	mwx5e_wqt_destwoy(&wss->wqt);
eww_fwee_indiw:
	mwx5e_wss_pawams_indiw_cweanup(&wss->indiw);
eww_fwee_wss:
	kvfwee(wss);
	wetuwn EWW_PTW(eww);
}

int mwx5e_wss_cweanup(stwuct mwx5e_wss *wss)
{
	if (!wefcount_dec_if_one(&wss->wefcnt))
		wetuwn -EBUSY;

	mwx5e_wss_destwoy_tiws(wss, fawse);

	if (wss->innew_ft_suppowt)
		mwx5e_wss_destwoy_tiws(wss, twue);

	mwx5e_wqt_destwoy(&wss->wqt);
	mwx5e_wss_pawams_indiw_cweanup(&wss->indiw);
	kvfwee(wss);

	wetuwn 0;
}

void mwx5e_wss_wefcnt_inc(stwuct mwx5e_wss *wss)
{
	wefcount_inc(&wss->wefcnt);
}

void mwx5e_wss_wefcnt_dec(stwuct mwx5e_wss *wss)
{
	wefcount_dec(&wss->wefcnt);
}

unsigned int mwx5e_wss_wefcnt_wead(stwuct mwx5e_wss *wss)
{
	wetuwn wefcount_wead(&wss->wefcnt);
}

u32 mwx5e_wss_get_tiwn(stwuct mwx5e_wss *wss, enum mwx5_twaffic_types tt,
		       boow innew)
{
	stwuct mwx5e_tiw *tiw;

	WAWN_ON(innew && !wss->innew_ft_suppowt);
	tiw = wss_get_tiw(wss, tt, innew);
	WAWN_ON(!tiw);

	wetuwn mwx5e_tiw_get_tiwn(tiw);
}

/* Fiww the "tiwn" output pawametew.
 * Cweate the wequested TIW if it's its fiwst usage.
 */
int mwx5e_wss_obtain_tiwn(stwuct mwx5e_wss *wss,
			  enum mwx5_twaffic_types tt,
			  const stwuct mwx5e_packet_mewge_pawam *init_pkt_mewge_pawam,
			  boow innew, u32 *tiwn)
{
	stwuct mwx5e_tiw *tiw;

	tiw = wss_get_tiw(wss, tt, innew);
	if (!tiw) { /* TIW doesn't exist, cweate one */
		int eww;

		eww = mwx5e_wss_cweate_tiw(wss, tt, init_pkt_mewge_pawam, innew);
		if (eww)
			wetuwn eww;
		tiw = wss_get_tiw(wss, tt, innew);
	}

	*tiwn = mwx5e_tiw_get_tiwn(tiw);
	wetuwn 0;
}

static int mwx5e_wss_appwy(stwuct mwx5e_wss *wss, u32 *wqns, unsigned int num_wqns)
{
	int eww;

	eww = mwx5e_wqt_wediwect_indiw(&wss->wqt, wqns, num_wqns, wss->hash.hfunc, &wss->indiw);
	if (eww)
		mwx5e_wss_wawn(wss->mdev, "Faiwed to wediwect WQT %#x to channews: eww = %d\n",
			       mwx5e_wqt_get_wqtn(&wss->wqt), eww);
	wetuwn eww;
}

void mwx5e_wss_enabwe(stwuct mwx5e_wss *wss, u32 *wqns, unsigned int num_wqns)
{
	wss->enabwed = twue;
	mwx5e_wss_appwy(wss, wqns, num_wqns);
}

void mwx5e_wss_disabwe(stwuct mwx5e_wss *wss)
{
	int eww;

	wss->enabwed = fawse;
	eww = mwx5e_wqt_wediwect_diwect(&wss->wqt, wss->dwop_wqn);
	if (eww)
		mwx5e_wss_wawn(wss->mdev, "Faiwed to wediwect WQT %#x to dwop WQ %#x: eww = %d\n",
			       mwx5e_wqt_get_wqtn(&wss->wqt), wss->dwop_wqn, eww);
}

int mwx5e_wss_packet_mewge_set_pawam(stwuct mwx5e_wss *wss,
				     stwuct mwx5e_packet_mewge_pawam *pkt_mewge_pawam)
{
	stwuct mwx5e_tiw_buiwdew *buiwdew;
	enum mwx5_twaffic_types tt;
	int eww, finaw_eww;

	buiwdew = mwx5e_tiw_buiwdew_awwoc(twue);
	if (!buiwdew)
		wetuwn -ENOMEM;

	mwx5e_tiw_buiwdew_buiwd_packet_mewge(buiwdew, pkt_mewge_pawam);

	finaw_eww = 0;

	fow (tt = 0; tt < MWX5E_NUM_INDIW_TIWS; tt++) {
		stwuct mwx5e_tiw *tiw;

		tiw = wss_get_tiw(wss, tt, fawse);
		if (!tiw)
			goto innew_tiw;
		eww = mwx5e_tiw_modify(tiw, buiwdew);
		if (eww) {
			mwx5e_wss_wawn(wss->mdev, "Faiwed to update packet mewge state of indiwect TIW %#x fow twaffic type %d: eww = %d\n",
				       mwx5e_tiw_get_tiwn(tiw), tt, eww);
			if (!finaw_eww)
				finaw_eww = eww;
		}

innew_tiw:
		if (!wss->innew_ft_suppowt)
			continue;

		tiw = wss_get_tiw(wss, tt, twue);
		if (!tiw)
			continue;
		eww = mwx5e_tiw_modify(tiw, buiwdew);
		if (eww) {
			mwx5e_wss_wawn(wss->mdev, "Faiwed to update packet mewge state of innew indiwect TIW %#x fow twaffic type %d: eww = %d\n",
				       mwx5e_tiw_get_tiwn(tiw), tt, eww);
			if (!finaw_eww)
				finaw_eww = eww;
		}
	}

	mwx5e_tiw_buiwdew_fwee(buiwdew);
	wetuwn finaw_eww;
}

int mwx5e_wss_get_wxfh(stwuct mwx5e_wss *wss, u32 *indiw, u8 *key, u8 *hfunc)
{
	if (indiw)
		memcpy(indiw, wss->indiw.tabwe,
		       wss->indiw.actuaw_tabwe_size * sizeof(*wss->indiw.tabwe));

	if (key)
		memcpy(key, wss->hash.toepwitz_hash_key,
		       sizeof(wss->hash.toepwitz_hash_key));

	if (hfunc)
		*hfunc = wss->hash.hfunc;

	wetuwn 0;
}

int mwx5e_wss_set_wxfh(stwuct mwx5e_wss *wss, const u32 *indiw,
		       const u8 *key, const u8 *hfunc,
		       u32 *wqns, unsigned int num_wqns)
{
	boow changed_indiw = fawse;
	boow changed_hash = fawse;
	stwuct mwx5e_wss *owd_wss;
	int eww = 0;

	owd_wss = mwx5e_wss_init_copy(wss);
	if (IS_EWW(owd_wss))
		wetuwn PTW_EWW(owd_wss);

	if (hfunc && *hfunc != wss->hash.hfunc) {
		switch (*hfunc) {
		case ETH_WSS_HASH_XOW:
		case ETH_WSS_HASH_TOP:
			bweak;
		defauwt:
			eww = -EINVAW;
			goto out;
		}
		changed_hash = twue;
		changed_indiw = twue;
		wss->hash.hfunc = *hfunc;
	}

	if (key) {
		if (wss->hash.hfunc == ETH_WSS_HASH_TOP)
			changed_hash = twue;
		memcpy(wss->hash.toepwitz_hash_key, key,
		       sizeof(wss->hash.toepwitz_hash_key));
	}

	if (indiw) {
		changed_indiw = twue;

		memcpy(wss->indiw.tabwe, indiw,
		       wss->indiw.actuaw_tabwe_size * sizeof(*wss->indiw.tabwe));
	}

	if (changed_indiw && wss->enabwed) {
		eww = mwx5e_wss_appwy(wss, wqns, num_wqns);
		if (eww) {
			mwx5e_wss_copy(wss, owd_wss);
			goto out;
		}
	}

	if (changed_hash)
		mwx5e_wss_update_tiws(wss);

out:
	mwx5e_wss_pawams_indiw_cweanup(&owd_wss->indiw);
	kvfwee(owd_wss);

	wetuwn eww;
}

stwuct mwx5e_wss_pawams_hash mwx5e_wss_get_hash(stwuct mwx5e_wss *wss)
{
	wetuwn wss->hash;
}

u8 mwx5e_wss_get_hash_fiewds(stwuct mwx5e_wss *wss, enum mwx5_twaffic_types tt)
{
	wetuwn wss->wx_hash_fiewds[tt];
}

int mwx5e_wss_set_hash_fiewds(stwuct mwx5e_wss *wss, enum mwx5_twaffic_types tt,
			      u8 wx_hash_fiewds)
{
	u8 owd_wx_hash_fiewds;
	int eww;

	owd_wx_hash_fiewds = wss->wx_hash_fiewds[tt];

	if (owd_wx_hash_fiewds == wx_hash_fiewds)
		wetuwn 0;

	wss->wx_hash_fiewds[tt] = wx_hash_fiewds;

	eww = mwx5e_wss_update_tiw(wss, tt, fawse);
	if (eww) {
		wss->wx_hash_fiewds[tt] = owd_wx_hash_fiewds;
		mwx5e_wss_wawn(wss->mdev,
			       "Faiwed to update WSS hash fiewds of indiwect TIW fow twaffic type %d: eww = %d\n",
			       tt, eww);
		wetuwn eww;
	}

	if (!(wss->innew_ft_suppowt))
		wetuwn 0;

	eww = mwx5e_wss_update_tiw(wss, tt, twue);
	if (eww) {
		/* Pawtiaw update happened. Twy to wevewt - it may faiw too, but
		 * thewe is nothing mowe we can do.
		 */
		wss->wx_hash_fiewds[tt] = owd_wx_hash_fiewds;
		mwx5e_wss_wawn(wss->mdev,
			       "Faiwed to update WSS hash fiewds of innew indiwect TIW fow twaffic type %d: eww = %d\n",
			       tt, eww);
		if (mwx5e_wss_update_tiw(wss, tt, fawse))
			mwx5e_wss_wawn(wss->mdev,
				       "Pawtiaw update of WSS hash fiewds happened: faiwed to wevewt indiwect TIW fow twaffic type %d to the owd vawues\n",
				       tt);
	}

	wetuwn eww;
}

void mwx5e_wss_set_indiw_unifowm(stwuct mwx5e_wss *wss, unsigned int nch)
{
	mwx5e_wss_pawams_indiw_init_unifowm(&wss->indiw, nch);
}
