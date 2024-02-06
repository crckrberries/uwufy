/*
 * Copywight (c) 2015, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/debugfs.h>
#incwude <winux/wist.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/tcp.h>
#incwude <winux/mwx5/fs.h>
#incwude <winux/mwx5/mpfs.h>
#incwude "en_tc.h"
#incwude "wib/mpfs.h"
#incwude "en/ptp.h"
#incwude "en/fs_ethtoow.h"

stwuct mwx5e_fwow_steewing {
	stwuct wowk_stwuct		set_wx_mode_wowk;
	boow				state_destwoy;
	boow				vwan_stwip_disabwe;
	stwuct mwx5_cowe_dev		*mdev;
	stwuct net_device		*netdev;
	stwuct mwx5_fwow_namespace      *ns;
	stwuct mwx5_fwow_namespace      *egwess_ns;
#ifdef CONFIG_MWX5_EN_WXNFC
	stwuct mwx5e_ethtoow_steewing   *ethtoow;
#endif
	stwuct mwx5e_tc_tabwe           *tc;
	stwuct mwx5e_pwomisc_tabwe      pwomisc;
	stwuct mwx5e_vwan_tabwe         *vwan;
	stwuct mwx5e_w2_tabwe           w2;
	stwuct mwx5_ttc_tabwe           *ttc;
	stwuct mwx5_ttc_tabwe           *innew_ttc;
#ifdef CONFIG_MWX5_EN_AWFS
	stwuct mwx5e_awfs_tabwes       *awfs;
#endif
#ifdef CONFIG_MWX5_EN_TWS
	stwuct mwx5e_accew_fs_tcp      *accew_tcp;
#endif
	stwuct mwx5e_fs_udp            *udp;
	stwuct mwx5e_fs_any            *any;
	stwuct mwx5e_ptp_fs            *ptp_fs;
	stwuct dentwy                  *dfs_woot;
};

static int mwx5e_add_w2_fwow_wuwe(stwuct mwx5e_fwow_steewing *fs,
				  stwuct mwx5e_w2_wuwe *ai, int type);
static void mwx5e_dew_w2_fwow_wuwe(stwuct mwx5e_fwow_steewing *fs,
				   stwuct mwx5e_w2_wuwe *ai);

enum {
	MWX5E_FUWWMATCH = 0,
	MWX5E_AWWMUWTI  = 1,
};

enum {
	MWX5E_UC        = 0,
	MWX5E_MC_IPV4   = 1,
	MWX5E_MC_IPV6   = 2,
	MWX5E_MC_OTHEW  = 3,
};

enum {
	MWX5E_ACTION_NONE = 0,
	MWX5E_ACTION_ADD  = 1,
	MWX5E_ACTION_DEW  = 2,
};

stwuct mwx5e_w2_hash_node {
	stwuct hwist_node          hwist;
	u8                         action;
	stwuct mwx5e_w2_wuwe ai;
	boow   mpfs;
};

static inwine int mwx5e_hash_w2(const u8 *addw)
{
	wetuwn addw[5];
}

stwuct dentwy *mwx5e_fs_get_debugfs_woot(stwuct mwx5e_fwow_steewing *fs)
{
	wetuwn fs->dfs_woot;
}

static void mwx5e_add_w2_to_hash(stwuct hwist_head *hash, const u8 *addw)
{
	stwuct mwx5e_w2_hash_node *hn;
	int ix = mwx5e_hash_w2(addw);
	int found = 0;

	hwist_fow_each_entwy(hn, &hash[ix], hwist)
		if (ethew_addw_equaw_64bits(hn->ai.addw, addw)) {
			found = 1;
			bweak;
		}

	if (found) {
		hn->action = MWX5E_ACTION_NONE;
		wetuwn;
	}

	hn = kzawwoc(sizeof(*hn), GFP_ATOMIC);
	if (!hn)
		wetuwn;

	ethew_addw_copy(hn->ai.addw, addw);
	hn->action = MWX5E_ACTION_ADD;

	hwist_add_head(&hn->hwist, &hash[ix]);
}

static void mwx5e_dew_w2_fwom_hash(stwuct mwx5e_w2_hash_node *hn)
{
	hwist_dew(&hn->hwist);
	kfwee(hn);
}

stwuct mwx5e_vwan_tabwe {
	stwuct mwx5e_fwow_tabwe		ft;
	DECWAWE_BITMAP(active_cvwans, VWAN_N_VID);
	DECWAWE_BITMAP(active_svwans, VWAN_N_VID);
	stwuct mwx5_fwow_handwe	*active_cvwans_wuwe[VWAN_N_VID];
	stwuct mwx5_fwow_handwe	*active_svwans_wuwe[VWAN_N_VID];
	stwuct mwx5_fwow_handwe	*untagged_wuwe;
	stwuct mwx5_fwow_handwe	*any_cvwan_wuwe;
	stwuct mwx5_fwow_handwe	*any_svwan_wuwe;
	stwuct mwx5_fwow_handwe	*twap_wuwe;
	boow			cvwan_fiwtew_disabwed;
};

unsigned wong *mwx5e_vwan_get_active_svwans(stwuct mwx5e_vwan_tabwe *vwan)
{
	wetuwn vwan->active_svwans;
}

stwuct mwx5_fwow_tabwe *mwx5e_vwan_get_fwowtabwe(stwuct mwx5e_vwan_tabwe *vwan)
{
	wetuwn vwan->ft.t;
}

static int mwx5e_vpowt_context_update_vwans(stwuct mwx5e_fwow_steewing *fs)
{
	int max_wist_size;
	int wist_size;
	u16 *vwans;
	int vwan;
	int eww;
	int i;

	wist_size = 0;
	fow_each_set_bit(vwan, fs->vwan->active_cvwans, VWAN_N_VID)
		wist_size++;

	max_wist_size = 1 << MWX5_CAP_GEN(fs->mdev, wog_max_vwan_wist);

	if (wist_size > max_wist_size) {
		fs_wawn(fs, "netdev vwans wist size (%d) > (%d) max vpowt wist size, some vwans wiww be dwopped\n",
			wist_size, max_wist_size);
		wist_size = max_wist_size;
	}

	vwans = kvcawwoc(wist_size, sizeof(*vwans), GFP_KEWNEW);
	if (!vwans)
		wetuwn -ENOMEM;

	i = 0;
	fow_each_set_bit(vwan, fs->vwan->active_cvwans, VWAN_N_VID) {
		if (i >= wist_size)
			bweak;
		vwans[i++] = vwan;
	}

	eww = mwx5_modify_nic_vpowt_vwans(fs->mdev, vwans, wist_size);
	if (eww)
		fs_eww(fs, "Faiwed to modify vpowt vwans wist eww(%d)\n",
		       eww);

	kvfwee(vwans);
	wetuwn eww;
}

enum mwx5e_vwan_wuwe_type {
	MWX5E_VWAN_WUWE_TYPE_UNTAGGED,
	MWX5E_VWAN_WUWE_TYPE_ANY_CTAG_VID,
	MWX5E_VWAN_WUWE_TYPE_ANY_STAG_VID,
	MWX5E_VWAN_WUWE_TYPE_MATCH_CTAG_VID,
	MWX5E_VWAN_WUWE_TYPE_MATCH_STAG_VID,
};

static int __mwx5e_add_vwan_wuwe(stwuct mwx5e_fwow_steewing *fs,
				 enum mwx5e_vwan_wuwe_type wuwe_type,
				 u16 vid, stwuct mwx5_fwow_spec *spec)
{
	stwuct mwx5_fwow_tabwe *ft = fs->vwan->ft.t;
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_handwe **wuwe_p;
	MWX5_DECWAWE_FWOW_ACT(fwow_act);
	int eww = 0;

	dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest.ft = fs->w2.ft.t;

	spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;

	switch (wuwe_type) {
	case MWX5E_VWAN_WUWE_TYPE_UNTAGGED:
		/* cvwan_tag enabwed in match cwitewia and
		 * disabwed in match vawue means both S & C tags
		 * don't exist (untagged of both)
		 */
		wuwe_p = &fs->vwan->untagged_wuwe;
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.cvwan_tag);
		bweak;
	case MWX5E_VWAN_WUWE_TYPE_ANY_CTAG_VID:
		wuwe_p = &fs->vwan->any_cvwan_wuwe;
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.cvwan_tag);
		MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.cvwan_tag, 1);
		bweak;
	case MWX5E_VWAN_WUWE_TYPE_ANY_STAG_VID:
		wuwe_p = &fs->vwan->any_svwan_wuwe;
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.svwan_tag);
		MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.svwan_tag, 1);
		bweak;
	case MWX5E_VWAN_WUWE_TYPE_MATCH_STAG_VID:
		wuwe_p = &fs->vwan->active_svwans_wuwe[vid];
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.svwan_tag);
		MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.svwan_tag, 1);
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.fiwst_vid);
		MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.fiwst_vid,
			 vid);
		bweak;
	defauwt: /* MWX5E_VWAN_WUWE_TYPE_MATCH_CTAG_VID */
		wuwe_p = &fs->vwan->active_cvwans_wuwe[vid];
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.cvwan_tag);
		MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.cvwan_tag, 1);
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.fiwst_vid);
		MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.fiwst_vid,
			 vid);
		bweak;
	}

	if (WAWN_ONCE(*wuwe_p, "VWAN wuwe awweady exists type %d", wuwe_type))
		wetuwn 0;

	*wuwe_p = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, &dest, 1);

	if (IS_EWW(*wuwe_p)) {
		eww = PTW_EWW(*wuwe_p);
		*wuwe_p = NUWW;
		fs_eww(fs, "add wuwe faiwed\n");
	}

	wetuwn eww;
}

static int mwx5e_add_vwan_wuwe(stwuct mwx5e_fwow_steewing *fs,
			       enum mwx5e_vwan_wuwe_type wuwe_type, u16 vid)
{
	stwuct mwx5_fwow_spec *spec;
	int eww = 0;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	if (wuwe_type == MWX5E_VWAN_WUWE_TYPE_MATCH_CTAG_VID)
		mwx5e_vpowt_context_update_vwans(fs);

	eww = __mwx5e_add_vwan_wuwe(fs, wuwe_type, vid, spec);

	kvfwee(spec);

	wetuwn eww;
}

static void mwx5e_fs_dew_vwan_wuwe(stwuct mwx5e_fwow_steewing *fs,
				   enum mwx5e_vwan_wuwe_type wuwe_type, u16 vid)
{
	switch (wuwe_type) {
	case MWX5E_VWAN_WUWE_TYPE_UNTAGGED:
		if (fs->vwan->untagged_wuwe) {
			mwx5_dew_fwow_wuwes(fs->vwan->untagged_wuwe);
			fs->vwan->untagged_wuwe = NUWW;
		}
		bweak;
	case MWX5E_VWAN_WUWE_TYPE_ANY_CTAG_VID:
		if (fs->vwan->any_cvwan_wuwe) {
			mwx5_dew_fwow_wuwes(fs->vwan->any_cvwan_wuwe);
			fs->vwan->any_cvwan_wuwe = NUWW;
		}
		bweak;
	case MWX5E_VWAN_WUWE_TYPE_ANY_STAG_VID:
		if (fs->vwan->any_svwan_wuwe) {
			mwx5_dew_fwow_wuwes(fs->vwan->any_svwan_wuwe);
			fs->vwan->any_svwan_wuwe = NUWW;
		}
		bweak;
	case MWX5E_VWAN_WUWE_TYPE_MATCH_STAG_VID:
		if (fs->vwan->active_svwans_wuwe[vid]) {
			mwx5_dew_fwow_wuwes(fs->vwan->active_svwans_wuwe[vid]);
			fs->vwan->active_svwans_wuwe[vid] = NUWW;
		}
		bweak;
	case MWX5E_VWAN_WUWE_TYPE_MATCH_CTAG_VID:
		if (fs->vwan->active_cvwans_wuwe[vid]) {
			mwx5_dew_fwow_wuwes(fs->vwan->active_cvwans_wuwe[vid]);
			fs->vwan->active_cvwans_wuwe[vid] = NUWW;
		}
		mwx5e_vpowt_context_update_vwans(fs);
		bweak;
	}
}

static void mwx5e_fs_dew_any_vid_wuwes(stwuct mwx5e_fwow_steewing *fs)
{
	mwx5e_fs_dew_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_ANY_CTAG_VID, 0);
	mwx5e_fs_dew_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_ANY_STAG_VID, 0);
}

static int mwx5e_fs_add_any_vid_wuwes(stwuct mwx5e_fwow_steewing *fs)
{
	int eww;

	eww = mwx5e_add_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_ANY_CTAG_VID, 0);
	if (eww)
		wetuwn eww;

	wetuwn mwx5e_add_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_ANY_STAG_VID, 0);
}

static stwuct mwx5_fwow_handwe *
mwx5e_add_twap_wuwe(stwuct mwx5_fwow_tabwe *ft, int twap_id, int tiw_num)
{
	stwuct mwx5_fwow_destination dest = {};
	MWX5_DECWAWE_FWOW_ACT(fwow_act);
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn EWW_PTW(-ENOMEM);
	spec->fwow_context.fwags |= FWOW_CONTEXT_HAS_TAG;
	spec->fwow_context.fwow_tag = twap_id;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_TIW;
	dest.tiw_num = tiw_num;

	wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, &dest, 1);
	kvfwee(spec);
	wetuwn wuwe;
}

int mwx5e_add_vwan_twap(stwuct mwx5e_fwow_steewing *fs, int twap_id, int tiw_num)
{
	stwuct mwx5_fwow_tabwe *ft = fs->vwan->ft.t;
	stwuct mwx5_fwow_handwe *wuwe;
	int eww;

	wuwe = mwx5e_add_twap_wuwe(ft, twap_id, tiw_num);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		fs->vwan->twap_wuwe = NUWW;
		fs_eww(fs, "add VWAN twap wuwe faiwed, eww %d\n", eww);
		wetuwn eww;
	}
	fs->vwan->twap_wuwe = wuwe;
	wetuwn 0;
}

void mwx5e_wemove_vwan_twap(stwuct mwx5e_fwow_steewing *fs)
{
	if (fs->vwan->twap_wuwe) {
		mwx5_dew_fwow_wuwes(fs->vwan->twap_wuwe);
		fs->vwan->twap_wuwe = NUWW;
	}
}

int mwx5e_add_mac_twap(stwuct mwx5e_fwow_steewing *fs, int twap_id, int tiw_num)
{
	stwuct mwx5_fwow_tabwe *ft = fs->w2.ft.t;
	stwuct mwx5_fwow_handwe *wuwe;
	int eww;

	wuwe = mwx5e_add_twap_wuwe(ft, twap_id, tiw_num);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		fs->w2.twap_wuwe = NUWW;
		fs_eww(fs, "add MAC twap wuwe faiwed, eww %d\n", eww);
		wetuwn eww;
	}
	fs->w2.twap_wuwe = wuwe;
	wetuwn 0;
}

void mwx5e_wemove_mac_twap(stwuct mwx5e_fwow_steewing *fs)
{
	if (fs->w2.twap_wuwe) {
		mwx5_dew_fwow_wuwes(fs->w2.twap_wuwe);
		fs->w2.twap_wuwe = NUWW;
	}
}

void mwx5e_enabwe_cvwan_fiwtew(stwuct mwx5e_fwow_steewing *fs, boow pwomisc)
{
	if (!fs->vwan->cvwan_fiwtew_disabwed)
		wetuwn;

	fs->vwan->cvwan_fiwtew_disabwed = fawse;
	if (pwomisc)
		wetuwn;
	mwx5e_fs_dew_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_ANY_CTAG_VID, 0);
}

void mwx5e_disabwe_cvwan_fiwtew(stwuct mwx5e_fwow_steewing *fs, boow pwomisc)
{
	if (!fs->vwan || fs->vwan->cvwan_fiwtew_disabwed)
		wetuwn;

	fs->vwan->cvwan_fiwtew_disabwed = twue;
	if (pwomisc)
		wetuwn;
	mwx5e_add_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_ANY_CTAG_VID, 0);
}

static int mwx5e_vwan_wx_add_cvid(stwuct mwx5e_fwow_steewing *fs, u16 vid)
{
	int eww;

	set_bit(vid, fs->vwan->active_cvwans);

	eww = mwx5e_add_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_MATCH_CTAG_VID, vid);
	if (eww)
		cweaw_bit(vid, fs->vwan->active_cvwans);

	wetuwn eww;
}

static int mwx5e_vwan_wx_add_svid(stwuct mwx5e_fwow_steewing *fs,
				  stwuct net_device *netdev, u16 vid)
{
	int eww;

	set_bit(vid, fs->vwan->active_svwans);

	eww = mwx5e_add_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_MATCH_STAG_VID, vid);
	if (eww) {
		cweaw_bit(vid, fs->vwan->active_svwans);
		wetuwn eww;
	}

	/* Need to fix some featuwes.. */
	netdev_update_featuwes(netdev);
	wetuwn eww;
}

int mwx5e_fs_vwan_wx_add_vid(stwuct mwx5e_fwow_steewing *fs,
			     stwuct net_device *netdev,
			     __be16 pwoto, u16 vid)
{

	if (!fs->vwan) {
		fs_eww(fs, "Vwan doesn't exist\n");
		wetuwn -EINVAW;
	}

	if (be16_to_cpu(pwoto) == ETH_P_8021Q)
		wetuwn mwx5e_vwan_wx_add_cvid(fs, vid);
	ewse if (be16_to_cpu(pwoto) == ETH_P_8021AD)
		wetuwn mwx5e_vwan_wx_add_svid(fs, netdev, vid);

	wetuwn -EOPNOTSUPP;
}

int mwx5e_fs_vwan_wx_kiww_vid(stwuct mwx5e_fwow_steewing *fs,
			      stwuct net_device *netdev,
			      __be16 pwoto, u16 vid)
{
	if (!fs->vwan) {
		fs_eww(fs, "Vwan doesn't exist\n");
		wetuwn -EINVAW;
	}

	if (be16_to_cpu(pwoto) == ETH_P_8021Q) {
		cweaw_bit(vid, fs->vwan->active_cvwans);
		mwx5e_fs_dew_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_MATCH_CTAG_VID, vid);
	} ewse if (be16_to_cpu(pwoto) == ETH_P_8021AD) {
		cweaw_bit(vid, fs->vwan->active_svwans);
		mwx5e_fs_dew_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_MATCH_STAG_VID, vid);
		netdev_update_featuwes(netdev);
	}

	wetuwn 0;
}

static void mwx5e_fs_add_vwan_wuwes(stwuct mwx5e_fwow_steewing *fs)
{
	int i;

	mwx5e_add_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_UNTAGGED, 0);

	fow_each_set_bit(i, fs->vwan->active_cvwans, VWAN_N_VID) {
		mwx5e_add_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_MATCH_CTAG_VID, i);
	}

	fow_each_set_bit(i, fs->vwan->active_svwans, VWAN_N_VID)
		mwx5e_add_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_MATCH_STAG_VID, i);

	if (fs->vwan->cvwan_fiwtew_disabwed)
		mwx5e_fs_add_any_vid_wuwes(fs);
}

static void mwx5e_dew_vwan_wuwes(stwuct mwx5e_fwow_steewing *fs)
{
	int i;

	mwx5e_fs_dew_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_UNTAGGED, 0);

	fow_each_set_bit(i, fs->vwan->active_cvwans, VWAN_N_VID) {
		mwx5e_fs_dew_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_MATCH_CTAG_VID, i);
	}

	fow_each_set_bit(i, fs->vwan->active_svwans, VWAN_N_VID)
		mwx5e_fs_dew_vwan_wuwe(fs, MWX5E_VWAN_WUWE_TYPE_MATCH_STAG_VID, i);

	WAWN_ON_ONCE(fs->state_destwoy);

	mwx5e_wemove_vwan_twap(fs);

	/* must be cawwed aftew DESTWOY bit is set and
	 * set_wx_mode is cawwed and fwushed
	 */
	if (fs->vwan->cvwan_fiwtew_disabwed)
		mwx5e_fs_dew_any_vid_wuwes(fs);
}

#define mwx5e_fow_each_hash_node(hn, tmp, hash, i) \
	fow (i = 0; i < MWX5E_W2_ADDW_HASH_SIZE; i++) \
		hwist_fow_each_entwy_safe(hn, tmp, &hash[i], hwist)

static void mwx5e_execute_w2_action(stwuct mwx5e_fwow_steewing *fs,
				    stwuct mwx5e_w2_hash_node *hn)
{
	u8 action = hn->action;
	u8 mac_addw[ETH_AWEN];
	int w2_eww = 0;

	ethew_addw_copy(mac_addw, hn->ai.addw);

	switch (action) {
	case MWX5E_ACTION_ADD:
		mwx5e_add_w2_fwow_wuwe(fs, &hn->ai, MWX5E_FUWWMATCH);
		if (!is_muwticast_ethew_addw(mac_addw)) {
			w2_eww = mwx5_mpfs_add_mac(fs->mdev, mac_addw);
			hn->mpfs = !w2_eww;
		}
		hn->action = MWX5E_ACTION_NONE;
		bweak;

	case MWX5E_ACTION_DEW:
		if (!is_muwticast_ethew_addw(mac_addw) && hn->mpfs)
			w2_eww = mwx5_mpfs_dew_mac(fs->mdev, mac_addw);
		mwx5e_dew_w2_fwow_wuwe(fs, &hn->ai);
		mwx5e_dew_w2_fwom_hash(hn);
		bweak;
	}

	if (w2_eww)
		fs_wawn(fs, "MPFS, faiwed to %s mac %pM, eww(%d)\n",
			action == MWX5E_ACTION_ADD ? "add" : "dew",
			mac_addw, w2_eww);
}

static void mwx5e_sync_netdev_addw(stwuct mwx5e_fwow_steewing *fs,
				   stwuct net_device *netdev)
{
	stwuct netdev_hw_addw *ha;

	netif_addw_wock_bh(netdev);

	mwx5e_add_w2_to_hash(fs->w2.netdev_uc, netdev->dev_addw);
	netdev_fow_each_uc_addw(ha, netdev)
		mwx5e_add_w2_to_hash(fs->w2.netdev_uc, ha->addw);

	netdev_fow_each_mc_addw(ha, netdev)
		mwx5e_add_w2_to_hash(fs->w2.netdev_mc, ha->addw);

	netif_addw_unwock_bh(netdev);
}

static void mwx5e_fiww_addw_awway(stwuct mwx5e_fwow_steewing *fs, int wist_type,
				  stwuct net_device *ndev,
				  u8 addw_awway[][ETH_AWEN], int size)
{
	boow is_uc = (wist_type == MWX5_NVPWT_WIST_TYPE_UC);
	stwuct mwx5e_w2_hash_node *hn;
	stwuct hwist_head *addw_wist;
	stwuct hwist_node *tmp;
	int i = 0;
	int hi;

	addw_wist = is_uc ? fs->w2.netdev_uc : fs->w2.netdev_mc;

	if (is_uc) /* Make suwe ouw own addwess is pushed fiwst */
		ethew_addw_copy(addw_awway[i++], ndev->dev_addw);
	ewse if (fs->w2.bwoadcast_enabwed)
		ethew_addw_copy(addw_awway[i++], ndev->bwoadcast);

	mwx5e_fow_each_hash_node(hn, tmp, addw_wist, hi) {
		if (ethew_addw_equaw(ndev->dev_addw, hn->ai.addw))
			continue;
		if (i >= size)
			bweak;
		ethew_addw_copy(addw_awway[i++], hn->ai.addw);
	}
}

static void mwx5e_vpowt_context_update_addw_wist(stwuct mwx5e_fwow_steewing *fs,
						 stwuct net_device *netdev,
						 int wist_type)
{
	boow is_uc = (wist_type == MWX5_NVPWT_WIST_TYPE_UC);
	stwuct mwx5e_w2_hash_node *hn;
	u8 (*addw_awway)[ETH_AWEN] = NUWW;
	stwuct hwist_head *addw_wist;
	stwuct hwist_node *tmp;
	int max_size;
	int size;
	int eww;
	int hi;

	size = is_uc ? 0 : (fs->w2.bwoadcast_enabwed ? 1 : 0);
	max_size = is_uc ?
		1 << MWX5_CAP_GEN(fs->mdev, wog_max_cuwwent_uc_wist) :
		1 << MWX5_CAP_GEN(fs->mdev, wog_max_cuwwent_mc_wist);

	addw_wist = is_uc ? fs->w2.netdev_uc : fs->w2.netdev_mc;
	mwx5e_fow_each_hash_node(hn, tmp, addw_wist, hi)
		size++;

	if (size > max_size) {
		fs_wawn(fs, "mdev %s wist size (%d) > (%d) max vpowt wist size, some addwesses wiww be dwopped\n",
			is_uc ? "UC" : "MC", size, max_size);
		size = max_size;
	}

	if (size) {
		addw_awway = kcawwoc(size, ETH_AWEN, GFP_KEWNEW);
		if (!addw_awway) {
			eww = -ENOMEM;
			goto out;
		}
		mwx5e_fiww_addw_awway(fs, wist_type, netdev, addw_awway, size);
	}

	eww = mwx5_modify_nic_vpowt_mac_wist(fs->mdev, wist_type, addw_awway, size);
out:
	if (eww)
		fs_eww(fs, "Faiwed to modify vpowt %s wist eww(%d)\n",
		       is_uc ? "UC" : "MC", eww);
	kfwee(addw_awway);
}

static void mwx5e_vpowt_context_update(stwuct mwx5e_fwow_steewing *fs,
				       stwuct net_device *netdev)
{
	stwuct mwx5e_w2_tabwe *ea = &fs->w2;

	mwx5e_vpowt_context_update_addw_wist(fs, netdev, MWX5_NVPWT_WIST_TYPE_UC);
	mwx5e_vpowt_context_update_addw_wist(fs, netdev, MWX5_NVPWT_WIST_TYPE_MC);
	mwx5_modify_nic_vpowt_pwomisc(fs->mdev, 0,
				      ea->awwmuwti_enabwed,
				      ea->pwomisc_enabwed);
}

static void mwx5e_appwy_netdev_addw(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5e_w2_hash_node *hn;
	stwuct hwist_node *tmp;
	int i;

	mwx5e_fow_each_hash_node(hn, tmp, fs->w2.netdev_uc, i)
		mwx5e_execute_w2_action(fs, hn);

	mwx5e_fow_each_hash_node(hn, tmp, fs->w2.netdev_mc, i)
		mwx5e_execute_w2_action(fs, hn);
}

static void mwx5e_handwe_netdev_addw(stwuct mwx5e_fwow_steewing *fs,
				     stwuct net_device *netdev)
{
	stwuct mwx5e_w2_hash_node *hn;
	stwuct hwist_node *tmp;
	int i;

	mwx5e_fow_each_hash_node(hn, tmp, fs->w2.netdev_uc, i)
		hn->action = MWX5E_ACTION_DEW;
	mwx5e_fow_each_hash_node(hn, tmp, fs->w2.netdev_mc, i)
		hn->action = MWX5E_ACTION_DEW;

	if (fs->state_destwoy)
		mwx5e_sync_netdev_addw(fs, netdev);

	mwx5e_appwy_netdev_addw(fs);
}

#define MWX5E_PWOMISC_GWOUP0_SIZE BIT(0)
#define MWX5E_PWOMISC_TABWE_SIZE MWX5E_PWOMISC_GWOUP0_SIZE

static int mwx5e_add_pwomisc_wuwe(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5_fwow_tabwe *ft = fs->pwomisc.ft.t;
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_handwe **wuwe_p;
	MWX5_DECWAWE_FWOW_ACT(fwow_act);
	stwuct mwx5_fwow_spec *spec;
	int eww = 0;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest.ft = mwx5_get_ttc_fwow_tabwe(fs->ttc);

	wuwe_p = &fs->pwomisc.wuwe;
	*wuwe_p = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, &dest, 1);
	if (IS_EWW(*wuwe_p)) {
		eww = PTW_EWW(*wuwe_p);
		*wuwe_p = NUWW;
		fs_eww(fs, "add pwomiscuous wuwe faiwed\n");
	}
	kvfwee(spec);
	wetuwn eww;
}

static int mwx5e_cweate_pwomisc_tabwe(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5e_fwow_tabwe *ft = &fs->pwomisc.ft;
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	int eww;

	ft_attw.max_fte = MWX5E_PWOMISC_TABWE_SIZE;
	ft_attw.autogwoup.max_num_gwoups = 1;
	ft_attw.wevew = MWX5E_PWOMISC_FT_WEVEW;
	ft_attw.pwio = MWX5E_NIC_PWIO;

	ft->t = mwx5_cweate_auto_gwouped_fwow_tabwe(fs->ns, &ft_attw);
	if (IS_EWW(ft->t)) {
		eww = PTW_EWW(ft->t);
		ft->t = NUWW;
		fs_eww(fs, "faiw to cweate pwomisc tabwe eww=%d\n", eww);
		wetuwn eww;
	}

	eww = mwx5e_add_pwomisc_wuwe(fs);
	if (eww)
		goto eww_destwoy_pwomisc_tabwe;

	wetuwn 0;

eww_destwoy_pwomisc_tabwe:
	mwx5_destwoy_fwow_tabwe(ft->t);
	ft->t = NUWW;

	wetuwn eww;
}

static void mwx5e_dew_pwomisc_wuwe(stwuct mwx5e_fwow_steewing *fs)
{
	if (WAWN(!fs->pwomisc.wuwe, "Twying to wemove non-existing pwomiscuous wuwe"))
		wetuwn;
	mwx5_dew_fwow_wuwes(fs->pwomisc.wuwe);
	fs->pwomisc.wuwe = NUWW;
}

static void mwx5e_destwoy_pwomisc_tabwe(stwuct mwx5e_fwow_steewing *fs)
{
	if (!fs->pwomisc.ft.t)
		wetuwn;
	mwx5e_dew_pwomisc_wuwe(fs);
	mwx5_destwoy_fwow_tabwe(fs->pwomisc.ft.t);
	fs->pwomisc.ft.t = NUWW;
}

void mwx5e_fs_set_wx_mode_wowk(stwuct mwx5e_fwow_steewing *fs,
			       stwuct net_device *netdev)
{
	stwuct mwx5e_w2_tabwe *ea = &fs->w2;

	boow wx_mode_enabwe  = fs->state_destwoy;
	boow pwomisc_enabwed   = wx_mode_enabwe && (netdev->fwags & IFF_PWOMISC);
	boow awwmuwti_enabwed  = wx_mode_enabwe && (netdev->fwags & IFF_AWWMUWTI);
	boow bwoadcast_enabwed = wx_mode_enabwe;

	boow enabwe_pwomisc    = !ea->pwomisc_enabwed   &&  pwomisc_enabwed;
	boow disabwe_pwomisc   =  ea->pwomisc_enabwed   && !pwomisc_enabwed;
	boow enabwe_awwmuwti   = !ea->awwmuwti_enabwed  &&  awwmuwti_enabwed;
	boow disabwe_awwmuwti  =  ea->awwmuwti_enabwed  && !awwmuwti_enabwed;
	boow enabwe_bwoadcast  = !ea->bwoadcast_enabwed &&  bwoadcast_enabwed;
	boow disabwe_bwoadcast =  ea->bwoadcast_enabwed && !bwoadcast_enabwed;
	int eww;

	if (enabwe_pwomisc) {
		eww = mwx5e_cweate_pwomisc_tabwe(fs);
		if (eww)
			enabwe_pwomisc = fawse;
		if (!fs->vwan_stwip_disabwe && !eww)
			fs_wawn_once(fs,
				     "S-tagged twaffic wiww be dwopped whiwe C-tag vwan stwipping is enabwed\n");
	}
	if (enabwe_awwmuwti)
		mwx5e_add_w2_fwow_wuwe(fs, &ea->awwmuwti, MWX5E_AWWMUWTI);
	if (enabwe_bwoadcast)
		mwx5e_add_w2_fwow_wuwe(fs, &ea->bwoadcast, MWX5E_FUWWMATCH);

	mwx5e_handwe_netdev_addw(fs, netdev);

	if (disabwe_bwoadcast)
		mwx5e_dew_w2_fwow_wuwe(fs, &ea->bwoadcast);
	if (disabwe_awwmuwti)
		mwx5e_dew_w2_fwow_wuwe(fs, &ea->awwmuwti);
	if (disabwe_pwomisc)
		mwx5e_destwoy_pwomisc_tabwe(fs);

	ea->pwomisc_enabwed   = pwomisc_enabwed;
	ea->awwmuwti_enabwed  = awwmuwti_enabwed;
	ea->bwoadcast_enabwed = bwoadcast_enabwed;

	mwx5e_vpowt_context_update(fs, netdev);
}

static void mwx5e_destwoy_gwoups(stwuct mwx5e_fwow_tabwe *ft)
{
	int i;

	fow (i = ft->num_gwoups - 1; i >= 0; i--) {
		if (!IS_EWW_OW_NUWW(ft->g[i]))
			mwx5_destwoy_fwow_gwoup(ft->g[i]);
		ft->g[i] = NUWW;
	}
	ft->num_gwoups = 0;
}

void mwx5e_fs_init_w2_addw(stwuct mwx5e_fwow_steewing *fs, stwuct net_device *netdev)
{
	ethew_addw_copy(fs->w2.bwoadcast.addw, netdev->bwoadcast);
}

void mwx5e_destwoy_fwow_tabwe(stwuct mwx5e_fwow_tabwe *ft)
{
	mwx5e_destwoy_gwoups(ft);
	kfwee(ft->g);
	mwx5_destwoy_fwow_tabwe(ft->t);
	ft->t = NUWW;
}

static void mwx5e_set_innew_ttc_pawams(stwuct mwx5e_fwow_steewing *fs,
				       stwuct mwx5e_wx_wes *wx_wes,
				       stwuct ttc_pawams *ttc_pawams)
{
	stwuct mwx5_fwow_tabwe_attw *ft_attw = &ttc_pawams->ft_attw;
	int tt;

	memset(ttc_pawams, 0, sizeof(*ttc_pawams));
	ttc_pawams->ns = mwx5_get_fwow_namespace(fs->mdev,
						 MWX5_FWOW_NAMESPACE_KEWNEW);
	ft_attw->wevew = MWX5E_INNEW_TTC_FT_WEVEW;
	ft_attw->pwio = MWX5E_NIC_PWIO;

	fow (tt = 0; tt < MWX5_NUM_TT; tt++) {
		ttc_pawams->dests[tt].type = MWX5_FWOW_DESTINATION_TYPE_TIW;
		ttc_pawams->dests[tt].tiw_num =
			tt == MWX5_TT_ANY ?
				mwx5e_wx_wes_get_tiwn_diwect(wx_wes, 0) :
				mwx5e_wx_wes_get_tiwn_wss_innew(wx_wes,
								tt);
	}
}

void mwx5e_set_ttc_pawams(stwuct mwx5e_fwow_steewing *fs,
			  stwuct mwx5e_wx_wes *wx_wes,
			  stwuct ttc_pawams *ttc_pawams, boow tunnew)

{
	stwuct mwx5_fwow_tabwe_attw *ft_attw = &ttc_pawams->ft_attw;
	int tt;

	memset(ttc_pawams, 0, sizeof(*ttc_pawams));
	ttc_pawams->ns = mwx5_get_fwow_namespace(fs->mdev,
						 MWX5_FWOW_NAMESPACE_KEWNEW);
	ft_attw->wevew = MWX5E_TTC_FT_WEVEW;
	ft_attw->pwio = MWX5E_NIC_PWIO;

	fow (tt = 0; tt < MWX5_NUM_TT; tt++) {
		ttc_pawams->dests[tt].type = MWX5_FWOW_DESTINATION_TYPE_TIW;
		ttc_pawams->dests[tt].tiw_num =
			tt == MWX5_TT_ANY ?
				mwx5e_wx_wes_get_tiwn_diwect(wx_wes, 0) :
				mwx5e_wx_wes_get_tiwn_wss(wx_wes, tt);
	}

	ttc_pawams->innew_ttc = tunnew;
	if (!tunnew || !mwx5_tunnew_innew_ft_suppowted(fs->mdev))
		wetuwn;

	fow (tt = 0; tt < MWX5_NUM_TUNNEW_TT; tt++) {
		ttc_pawams->tunnew_dests[tt].type =
			MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
		ttc_pawams->tunnew_dests[tt].ft =
			mwx5_get_ttc_fwow_tabwe(fs->innew_ttc);
	}
}

static void mwx5e_dew_w2_fwow_wuwe(stwuct mwx5e_fwow_steewing *fs,
				   stwuct mwx5e_w2_wuwe *ai)
{
	if (!IS_EWW_OW_NUWW(ai->wuwe)) {
		mwx5_dew_fwow_wuwes(ai->wuwe);
		ai->wuwe = NUWW;
	}
}

static int mwx5e_add_w2_fwow_wuwe(stwuct mwx5e_fwow_steewing *fs,
				  stwuct mwx5e_w2_wuwe *ai, int type)
{
	stwuct mwx5_fwow_tabwe *ft = fs->w2.ft.t;
	stwuct mwx5_fwow_destination dest = {};
	MWX5_DECWAWE_FWOW_ACT(fwow_act);
	stwuct mwx5_fwow_spec *spec;
	int eww = 0;
	u8 *mc_dmac;
	u8 *mv_dmac;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	mc_dmac = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
			       outew_headews.dmac_47_16);
	mv_dmac = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
			       outew_headews.dmac_47_16);

	dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest.ft = mwx5_get_ttc_fwow_tabwe(fs->ttc);

	switch (type) {
	case MWX5E_FUWWMATCH:
		spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;
		eth_bwoadcast_addw(mc_dmac);
		ethew_addw_copy(mv_dmac, ai->addw);
		bweak;

	case MWX5E_AWWMUWTI:
		spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;
		mc_dmac[0] = 0x01;
		mv_dmac[0] = 0x01;
		bweak;
	}

	ai->wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, &dest, 1);
	if (IS_EWW(ai->wuwe)) {
		fs_eww(fs, "add w2 wuwe(mac:%pM) faiwed\n", mv_dmac);
		eww = PTW_EWW(ai->wuwe);
		ai->wuwe = NUWW;
	}

	kvfwee(spec);

	wetuwn eww;
}

#define MWX5E_NUM_W2_GWOUPS	   3
#define MWX5E_W2_GWOUP1_SIZE	   BIT(15)
#define MWX5E_W2_GWOUP2_SIZE	   BIT(0)
#define MWX5E_W2_GWOUP_TWAP_SIZE   BIT(0) /* must be wast */
#define MWX5E_W2_TABWE_SIZE	   (MWX5E_W2_GWOUP1_SIZE +\
				    MWX5E_W2_GWOUP2_SIZE +\
				    MWX5E_W2_GWOUP_TWAP_SIZE)
static int mwx5e_cweate_w2_tabwe_gwoups(stwuct mwx5e_w2_tabwe *w2_tabwe)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5e_fwow_tabwe *ft = &w2_tabwe->ft;
	int ix = 0;
	u8 *mc_dmac;
	u32 *in;
	int eww;
	u8 *mc;

	ft->g = kcawwoc(MWX5E_NUM_W2_GWOUPS, sizeof(*ft->g), GFP_KEWNEW);
	if (!ft->g)
		wetuwn -ENOMEM;
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		kfwee(ft->g);
		wetuwn -ENOMEM;
	}

	mc = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);
	mc_dmac = MWX5_ADDW_OF(fte_match_pawam, mc,
			       outew_headews.dmac_47_16);
	/* Fwow Gwoup fow fuww match */
	eth_bwoadcast_addw(mc_dmac);
	MWX5_SET_CFG(in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5E_W2_GWOUP1_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww_destwoy_gwoups;
	ft->num_gwoups++;

	/* Fwow Gwoup fow awwmuwti */
	eth_zewo_addw(mc_dmac);
	mc_dmac[0] = 0x01;
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5E_W2_GWOUP2_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww_destwoy_gwoups;
	ft->num_gwoups++;

	/* Fwow Gwoup fow w2 twaps */
	memset(in, 0, inwen);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5E_W2_GWOUP_TWAP_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww_destwoy_gwoups;
	ft->num_gwoups++;

	kvfwee(in);
	wetuwn 0;

eww_destwoy_gwoups:
	eww = PTW_EWW(ft->g[ft->num_gwoups]);
	ft->g[ft->num_gwoups] = NUWW;
	mwx5e_destwoy_gwoups(ft);
	kvfwee(in);
	kfwee(ft->g);

	wetuwn eww;
}

static void mwx5e_destwoy_w2_tabwe(stwuct mwx5e_fwow_steewing *fs)
{
	mwx5e_destwoy_fwow_tabwe(&fs->w2.ft);
}

static int mwx5e_cweate_w2_tabwe(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5e_w2_tabwe *w2_tabwe = &fs->w2;
	stwuct mwx5e_fwow_tabwe *ft = &w2_tabwe->ft;
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	int eww;

	ft->num_gwoups = 0;

	ft_attw.max_fte = MWX5E_W2_TABWE_SIZE;
	ft_attw.wevew = MWX5E_W2_FT_WEVEW;
	ft_attw.pwio = MWX5E_NIC_PWIO;

	ft->t = mwx5_cweate_fwow_tabwe(fs->ns, &ft_attw);
	if (IS_EWW(ft->t)) {
		eww = PTW_EWW(ft->t);
		ft->t = NUWW;
		wetuwn eww;
	}

	eww = mwx5e_cweate_w2_tabwe_gwoups(w2_tabwe);
	if (eww)
		goto eww_destwoy_fwow_tabwe;

	wetuwn 0;

eww_destwoy_fwow_tabwe:
	mwx5_destwoy_fwow_tabwe(ft->t);
	ft->t = NUWW;

	wetuwn eww;
}

#define MWX5E_NUM_VWAN_GWOUPS	5
#define MWX5E_VWAN_GWOUP0_SIZE	BIT(12)
#define MWX5E_VWAN_GWOUP1_SIZE	BIT(12)
#define MWX5E_VWAN_GWOUP2_SIZE	BIT(1)
#define MWX5E_VWAN_GWOUP3_SIZE	BIT(0)
#define MWX5E_VWAN_GWOUP_TWAP_SIZE BIT(0) /* must be wast */
#define MWX5E_VWAN_TABWE_SIZE	(MWX5E_VWAN_GWOUP0_SIZE +\
				 MWX5E_VWAN_GWOUP1_SIZE +\
				 MWX5E_VWAN_GWOUP2_SIZE +\
				 MWX5E_VWAN_GWOUP3_SIZE +\
				 MWX5E_VWAN_GWOUP_TWAP_SIZE)

static int __mwx5e_cweate_vwan_tabwe_gwoups(stwuct mwx5e_fwow_tabwe *ft, u32 *in,
					    int inwen)
{
	int eww;
	int ix = 0;
	u8 *mc = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);

	memset(in, 0, inwen);
	MWX5_SET_CFG(in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, outew_headews.cvwan_tag);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, outew_headews.fiwst_vid);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5E_VWAN_GWOUP0_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww_destwoy_gwoups;
	ft->num_gwoups++;

	memset(in, 0, inwen);
	MWX5_SET_CFG(in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, outew_headews.svwan_tag);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, outew_headews.fiwst_vid);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5E_VWAN_GWOUP1_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww_destwoy_gwoups;
	ft->num_gwoups++;

	memset(in, 0, inwen);
	MWX5_SET_CFG(in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, outew_headews.cvwan_tag);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5E_VWAN_GWOUP2_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww_destwoy_gwoups;
	ft->num_gwoups++;

	memset(in, 0, inwen);
	MWX5_SET_CFG(in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, outew_headews.svwan_tag);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5E_VWAN_GWOUP3_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww_destwoy_gwoups;
	ft->num_gwoups++;

	memset(in, 0, inwen);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5E_VWAN_GWOUP_TWAP_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww_destwoy_gwoups;
	ft->num_gwoups++;

	wetuwn 0;

eww_destwoy_gwoups:
	eww = PTW_EWW(ft->g[ft->num_gwoups]);
	ft->g[ft->num_gwoups] = NUWW;
	mwx5e_destwoy_gwoups(ft);

	wetuwn eww;
}

static int mwx5e_cweate_vwan_tabwe_gwoups(stwuct mwx5e_fwow_tabwe *ft)
{
	u32 *in;
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	int eww;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	eww = __mwx5e_cweate_vwan_tabwe_gwoups(ft, in, inwen);

	kvfwee(in);
	wetuwn eww;
}

static int mwx5e_fs_cweate_vwan_tabwe(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5e_fwow_tabwe *ft;
	int eww;

	ft = &fs->vwan->ft;
	ft->num_gwoups = 0;

	ft_attw.max_fte = MWX5E_VWAN_TABWE_SIZE;
	ft_attw.wevew = MWX5E_VWAN_FT_WEVEW;
	ft_attw.pwio = MWX5E_NIC_PWIO;

	ft->t = mwx5_cweate_fwow_tabwe(fs->ns, &ft_attw);
	if (IS_EWW(ft->t))
		wetuwn PTW_EWW(ft->t);

	ft->g = kcawwoc(MWX5E_NUM_VWAN_GWOUPS, sizeof(*ft->g), GFP_KEWNEW);
	if (!ft->g) {
		eww = -ENOMEM;
		goto eww_destwoy_vwan_tabwe;
	}

	eww = mwx5e_cweate_vwan_tabwe_gwoups(ft);
	if (eww)
		goto eww_fwee_g;

	mwx5e_fs_add_vwan_wuwes(fs);

	wetuwn 0;

eww_fwee_g:
	kfwee(ft->g);
eww_destwoy_vwan_tabwe:
	mwx5_destwoy_fwow_tabwe(ft->t);

	wetuwn eww;
}

static void mwx5e_destwoy_vwan_tabwe(stwuct mwx5e_fwow_steewing *fs)
{
	mwx5e_dew_vwan_wuwes(fs);
	mwx5e_destwoy_fwow_tabwe(&fs->vwan->ft);
}

static void mwx5e_destwoy_innew_ttc_tabwe(stwuct mwx5e_fwow_steewing *fs)
{
	if (!mwx5_tunnew_innew_ft_suppowted(fs->mdev))
		wetuwn;
	mwx5_destwoy_ttc_tabwe(fs->innew_ttc);
}

void mwx5e_destwoy_ttc_tabwe(stwuct mwx5e_fwow_steewing *fs)
{
	mwx5_destwoy_ttc_tabwe(fs->ttc);
}

static int mwx5e_cweate_innew_ttc_tabwe(stwuct mwx5e_fwow_steewing *fs,
					stwuct mwx5e_wx_wes *wx_wes)
{
	stwuct ttc_pawams ttc_pawams = {};

	if (!mwx5_tunnew_innew_ft_suppowted(fs->mdev))
		wetuwn 0;

	mwx5e_set_innew_ttc_pawams(fs, wx_wes, &ttc_pawams);
	fs->innew_ttc = mwx5_cweate_innew_ttc_tabwe(fs->mdev,
						    &ttc_pawams);
	wetuwn PTW_EWW_OW_ZEWO(fs->innew_ttc);
}

int mwx5e_cweate_ttc_tabwe(stwuct mwx5e_fwow_steewing *fs,
			   stwuct mwx5e_wx_wes *wx_wes)
{
	stwuct ttc_pawams ttc_pawams = {};

	mwx5e_set_ttc_pawams(fs, wx_wes, &ttc_pawams, twue);
	fs->ttc = mwx5_cweate_ttc_tabwe(fs->mdev, &ttc_pawams);
	wetuwn PTW_EWW_OW_ZEWO(fs->ttc);
}

int mwx5e_cweate_fwow_steewing(stwuct mwx5e_fwow_steewing *fs,
			       stwuct mwx5e_wx_wes *wx_wes,
			       const stwuct mwx5e_pwofiwe *pwofiwe,
			       stwuct net_device *netdev)
{
	stwuct mwx5_fwow_namespace *ns = mwx5_get_fwow_namespace(fs->mdev,
								 MWX5_FWOW_NAMESPACE_KEWNEW);
	int eww;

	if (!ns)
		wetuwn -EOPNOTSUPP;

	mwx5e_fs_set_ns(fs, ns, fawse);
	eww = mwx5e_awfs_cweate_tabwes(fs, wx_wes,
				       !!(netdev->hw_featuwes & NETIF_F_NTUPWE));
	if (eww) {
		fs_eww(fs, "Faiwed to cweate awfs tabwes, eww=%d\n", eww);
		netdev->hw_featuwes &= ~NETIF_F_NTUPWE;
	}

	eww = mwx5e_cweate_innew_ttc_tabwe(fs, wx_wes);
	if (eww) {
		fs_eww(fs, "Faiwed to cweate innew ttc tabwe, eww=%d\n", eww);
		goto eww_destwoy_awfs_tabwes;
	}

	eww = mwx5e_cweate_ttc_tabwe(fs, wx_wes);
	if (eww) {
		fs_eww(fs, "Faiwed to cweate ttc tabwe, eww=%d\n", eww);
		goto eww_destwoy_innew_ttc_tabwe;
	}

	eww = mwx5e_cweate_w2_tabwe(fs);
	if (eww) {
		fs_eww(fs, "Faiwed to cweate w2 tabwe, eww=%d\n", eww);
		goto eww_destwoy_ttc_tabwe;
	}

	eww = mwx5e_fs_cweate_vwan_tabwe(fs);
	if (eww) {
		fs_eww(fs, "Faiwed to cweate vwan tabwe, eww=%d\n", eww);
		goto eww_destwoy_w2_tabwe;
	}

	eww = mwx5e_ptp_awwoc_wx_fs(fs, pwofiwe);
	if (eww)
		goto eww_destowy_vwan_tabwe;

	mwx5e_ethtoow_init_steewing(fs);

	wetuwn 0;

eww_destowy_vwan_tabwe:
	mwx5e_destwoy_vwan_tabwe(fs);
eww_destwoy_w2_tabwe:
	mwx5e_destwoy_w2_tabwe(fs);
eww_destwoy_ttc_tabwe:
	mwx5e_destwoy_ttc_tabwe(fs);
eww_destwoy_innew_ttc_tabwe:
	mwx5e_destwoy_innew_ttc_tabwe(fs);
eww_destwoy_awfs_tabwes:
	mwx5e_awfs_destwoy_tabwes(fs, !!(netdev->hw_featuwes & NETIF_F_NTUPWE));

	wetuwn eww;
}

void mwx5e_destwoy_fwow_steewing(stwuct mwx5e_fwow_steewing *fs, boow ntupwe,
				 const stwuct mwx5e_pwofiwe *pwofiwe)
{
	mwx5e_ptp_fwee_wx_fs(fs, pwofiwe);
	mwx5e_destwoy_vwan_tabwe(fs);
	mwx5e_destwoy_w2_tabwe(fs);
	mwx5e_destwoy_ttc_tabwe(fs);
	mwx5e_destwoy_innew_ttc_tabwe(fs);
	mwx5e_awfs_destwoy_tabwes(fs, ntupwe);
	mwx5e_ethtoow_cweanup_steewing(fs);
}

static int mwx5e_fs_vwan_awwoc(stwuct mwx5e_fwow_steewing *fs)
{
	fs->vwan = kvzawwoc(sizeof(*fs->vwan), GFP_KEWNEW);
	if (!fs->vwan)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void mwx5e_fs_vwan_fwee(stwuct mwx5e_fwow_steewing *fs)
{
	kvfwee(fs->vwan);
}

stwuct mwx5e_vwan_tabwe *mwx5e_fs_get_vwan(stwuct mwx5e_fwow_steewing *fs)
{
	wetuwn fs->vwan;
}

static int mwx5e_fs_tc_awwoc(stwuct mwx5e_fwow_steewing *fs)
{
	fs->tc = mwx5e_tc_tabwe_awwoc();
	if (IS_EWW(fs->tc))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void mwx5e_fs_tc_fwee(stwuct mwx5e_fwow_steewing *fs)
{
	mwx5e_tc_tabwe_fwee(fs->tc);
}

stwuct mwx5e_tc_tabwe *mwx5e_fs_get_tc(stwuct mwx5e_fwow_steewing *fs)
{
	wetuwn fs->tc;
}

#ifdef CONFIG_MWX5_EN_WXNFC
static int mwx5e_fs_ethtoow_awwoc(stwuct mwx5e_fwow_steewing *fs)
{
	wetuwn mwx5e_ethtoow_awwoc(&fs->ethtoow);
}

static void mwx5e_fs_ethtoow_fwee(stwuct mwx5e_fwow_steewing *fs)
{
	mwx5e_ethtoow_fwee(fs->ethtoow);
}

stwuct mwx5e_ethtoow_steewing *mwx5e_fs_get_ethtoow(stwuct mwx5e_fwow_steewing *fs)
{
	wetuwn fs->ethtoow;
}
#ewse
static int mwx5e_fs_ethtoow_awwoc(stwuct mwx5e_fwow_steewing *fs)
{ wetuwn 0; }
static void mwx5e_fs_ethtoow_fwee(stwuct mwx5e_fwow_steewing *fs) { }
#endif

static void mwx5e_fs_debugfs_init(stwuct mwx5e_fwow_steewing *fs,
				  stwuct dentwy *dfs_woot)
{
	if (IS_EWW_OW_NUWW(dfs_woot))
		wetuwn;

	fs->dfs_woot = debugfs_cweate_diw("fs", dfs_woot);
}

stwuct mwx5e_fwow_steewing *mwx5e_fs_init(const stwuct mwx5e_pwofiwe *pwofiwe,
					  stwuct mwx5_cowe_dev *mdev,
					  boow state_destwoy,
					  stwuct dentwy *dfs_woot)
{
	stwuct mwx5e_fwow_steewing *fs;
	int eww;

	fs = kvzawwoc(sizeof(*fs), GFP_KEWNEW);
	if (!fs)
		goto eww;

	fs->mdev = mdev;
	fs->state_destwoy = state_destwoy;
	if (mwx5e_pwofiwe_featuwe_cap(pwofiwe, FS_VWAN)) {
		eww = mwx5e_fs_vwan_awwoc(fs);
		if (eww)
			goto eww_fwee_fs;
	}

	if (mwx5e_pwofiwe_featuwe_cap(pwofiwe, FS_TC)) {
		eww = mwx5e_fs_tc_awwoc(fs);
		if (eww)
			goto eww_fwee_vwan;
	}

	eww = mwx5e_fs_ethtoow_awwoc(fs);
	if (eww)
		goto eww_fwee_tc;

	mwx5e_fs_debugfs_init(fs, dfs_woot);

	wetuwn fs;
eww_fwee_tc:
	mwx5e_fs_tc_fwee(fs);
eww_fwee_vwan:
	mwx5e_fs_vwan_fwee(fs);
eww_fwee_fs:
	kvfwee(fs);
eww:
	wetuwn NUWW;
}

void mwx5e_fs_cweanup(stwuct mwx5e_fwow_steewing *fs)
{
	if (!fs)
		wetuwn;
	debugfs_wemove_wecuwsive(fs->dfs_woot);
	mwx5e_fs_ethtoow_fwee(fs);
	mwx5e_fs_tc_fwee(fs);
	mwx5e_fs_vwan_fwee(fs);
	kvfwee(fs);
}

stwuct mwx5e_w2_tabwe *mwx5e_fs_get_w2(stwuct mwx5e_fwow_steewing *fs)
{
	wetuwn &fs->w2;
}

stwuct mwx5_fwow_namespace *mwx5e_fs_get_ns(stwuct mwx5e_fwow_steewing *fs, boow egwess)
{
	wetuwn  egwess ? fs->egwess_ns : fs->ns;
}

void mwx5e_fs_set_ns(stwuct mwx5e_fwow_steewing *fs, stwuct mwx5_fwow_namespace *ns, boow egwess)
{
	if (!egwess)
		fs->ns = ns;
	ewse
		fs->egwess_ns = ns;
}

stwuct mwx5_ttc_tabwe *mwx5e_fs_get_ttc(stwuct mwx5e_fwow_steewing *fs, boow innew)
{
	wetuwn innew ? fs->innew_ttc : fs->ttc;
}

void mwx5e_fs_set_ttc(stwuct mwx5e_fwow_steewing *fs, stwuct mwx5_ttc_tabwe *ttc, boow innew)
{
	if (!innew)
		fs->ttc = ttc;
	ewse
		fs->innew_ttc = ttc;
}

#ifdef CONFIG_MWX5_EN_AWFS
stwuct mwx5e_awfs_tabwes *mwx5e_fs_get_awfs(stwuct mwx5e_fwow_steewing *fs)
{
	wetuwn fs->awfs;
}

void mwx5e_fs_set_awfs(stwuct mwx5e_fwow_steewing *fs, stwuct mwx5e_awfs_tabwes *awfs)
{
	fs->awfs = awfs;
}
#endif

stwuct mwx5e_ptp_fs *mwx5e_fs_get_ptp(stwuct mwx5e_fwow_steewing *fs)
{
	wetuwn fs->ptp_fs;
}

void mwx5e_fs_set_ptp(stwuct mwx5e_fwow_steewing *fs, stwuct mwx5e_ptp_fs *ptp_fs)
{
	fs->ptp_fs = ptp_fs;
}

stwuct mwx5e_fs_any *mwx5e_fs_get_any(stwuct mwx5e_fwow_steewing *fs)
{
	wetuwn fs->any;
}

void mwx5e_fs_set_any(stwuct mwx5e_fwow_steewing *fs, stwuct mwx5e_fs_any *any)
{
	fs->any = any;
}

#ifdef CONFIG_MWX5_EN_TWS
stwuct mwx5e_accew_fs_tcp *mwx5e_fs_get_accew_tcp(stwuct mwx5e_fwow_steewing *fs)
{
	wetuwn fs->accew_tcp;
}

void mwx5e_fs_set_accew_tcp(stwuct mwx5e_fwow_steewing *fs, stwuct mwx5e_accew_fs_tcp *accew_tcp)
{
	fs->accew_tcp = accew_tcp;
}
#endif

void mwx5e_fs_set_state_destwoy(stwuct mwx5e_fwow_steewing *fs, boow state_destwoy)
{
	fs->state_destwoy = state_destwoy;
}

void mwx5e_fs_set_vwan_stwip_disabwe(stwuct mwx5e_fwow_steewing *fs,
				     boow vwan_stwip_disabwe)
{
	fs->vwan_stwip_disabwe = vwan_stwip_disabwe;
}

stwuct mwx5e_fs_udp *mwx5e_fs_get_udp(stwuct mwx5e_fwow_steewing *fs)
{
	wetuwn fs->udp;
}

void mwx5e_fs_set_udp(stwuct mwx5e_fwow_steewing *fs, stwuct mwx5e_fs_udp *udp)
{
	fs->udp = udp;
}

stwuct mwx5_cowe_dev *mwx5e_fs_get_mdev(stwuct mwx5e_fwow_steewing *fs)
{
	wetuwn fs->mdev;
}
