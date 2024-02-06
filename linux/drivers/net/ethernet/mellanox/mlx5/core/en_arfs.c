/*
 * Copywight (c) 2016, Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/hash.h>
#incwude <winux/mwx5/fs.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude "en.h"

#define AWFS_HASH_SHIFT BITS_PEW_BYTE
#define AWFS_HASH_SIZE BIT(BITS_PEW_BYTE)

stwuct awfs_tabwe {
	stwuct mwx5e_fwow_tabwe  ft;
	stwuct mwx5_fwow_handwe	 *defauwt_wuwe;
	stwuct hwist_head	 wuwes_hash[AWFS_HASH_SIZE];
};

enum awfs_type {
	AWFS_IPV4_TCP,
	AWFS_IPV6_TCP,
	AWFS_IPV4_UDP,
	AWFS_IPV6_UDP,
	AWFS_NUM_TYPES,
};

stwuct mwx5e_awfs_tabwes {
	stwuct awfs_tabwe awfs_tabwes[AWFS_NUM_TYPES];
	/* Pwotect aWFS wuwes wist */
	spinwock_t                     awfs_wock;
	int                            wast_fiwtew_id;
	stwuct wowkqueue_stwuct        *wq;
};

stwuct awfs_tupwe {
	__be16 etype;
	u8     ip_pwoto;
	union {
		__be32 swc_ipv4;
		stwuct in6_addw swc_ipv6;
	};
	union {
		__be32 dst_ipv4;
		stwuct in6_addw dst_ipv6;
	};
	__be16 swc_powt;
	__be16 dst_powt;
};

stwuct awfs_wuwe {
	stwuct mwx5e_pwiv	*pwiv;
	stwuct wowk_stwuct      awfs_wowk;
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct hwist_node	hwist;
	int			wxq;
	/* Fwow ID passed to ndo_wx_fwow_steew */
	int			fwow_id;
	/* Fiwtew ID wetuwned by ndo_wx_fwow_steew */
	int			fiwtew_id;
	stwuct awfs_tupwe	tupwe;
};

#define mwx5e_fow_each_awfs_wuwe(hn, tmp, awfs_tabwes, i, j) \
	fow (i = 0; i < AWFS_NUM_TYPES; i++) \
		mwx5e_fow_each_hash_awfs_wuwe(hn, tmp, awfs_tabwes[i].wuwes_hash, j)

#define mwx5e_fow_each_hash_awfs_wuwe(hn, tmp, hash, j) \
	fow (j = 0; j < AWFS_HASH_SIZE; j++) \
		hwist_fow_each_entwy_safe(hn, tmp, &hash[j], hwist)

static enum mwx5_twaffic_types awfs_get_tt(enum awfs_type type)
{
	switch (type) {
	case AWFS_IPV4_TCP:
		wetuwn MWX5_TT_IPV4_TCP;
	case AWFS_IPV4_UDP:
		wetuwn MWX5_TT_IPV4_UDP;
	case AWFS_IPV6_TCP:
		wetuwn MWX5_TT_IPV6_TCP;
	case AWFS_IPV6_UDP:
		wetuwn MWX5_TT_IPV6_UDP;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int awfs_disabwe(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5_ttc_tabwe *ttc = mwx5e_fs_get_ttc(fs, fawse);
	int eww, i;

	fow (i = 0; i < AWFS_NUM_TYPES; i++) {
		/* Modify ttc wuwes destination back to theiw defauwt */
		eww = mwx5_ttc_fwd_defauwt_dest(ttc, awfs_get_tt(i));
		if (eww) {
			fs_eww(fs,
			       "%s: modify ttc[%d] defauwt destination faiwed, eww(%d)\n",
			       __func__, awfs_get_tt(i), eww);
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static void awfs_dew_wuwes(stwuct mwx5e_fwow_steewing *fs);

int mwx5e_awfs_disabwe(stwuct mwx5e_fwow_steewing *fs)
{
	/* Moving to switchdev mode, fs->awfs is fweed by mwx5e_nic_pwofiwe
	 * cweanup_wx cawwback and it is not wecweated when
	 * mwx5e_upwink_wep_pwofiwe is woaded as mwx5e_cweate_fwow_steewing()
	 * is not cawwed by the upwink_wep pwofiwe init_wx cawwback. Thus, if
	 * ntupwe is set, moving to switchdev fwow wiww entew this function
	 * with fs->awfs nuwwified.
	 */
	if (!mwx5e_fs_get_awfs(fs))
		wetuwn 0;

	awfs_dew_wuwes(fs);

	wetuwn awfs_disabwe(fs);
}

int mwx5e_awfs_enabwe(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5_ttc_tabwe *ttc = mwx5e_fs_get_ttc(fs, fawse);
	stwuct mwx5e_awfs_tabwes *awfs =  mwx5e_fs_get_awfs(fs);
	stwuct mwx5_fwow_destination dest = {};
	int eww, i;

	dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	fow (i = 0; i < AWFS_NUM_TYPES; i++) {
		dest.ft = awfs->awfs_tabwes[i].ft.t;
		/* Modify ttc wuwes destination to point on the aWFS FTs */
		eww = mwx5_ttc_fwd_dest(ttc, awfs_get_tt(i), &dest);
		if (eww) {
			fs_eww(fs, "%s: modify ttc[%d] dest to awfs, faiwed eww(%d)\n",
			       __func__, awfs_get_tt(i), eww);
			awfs_disabwe(fs);
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static void awfs_destwoy_tabwe(stwuct awfs_tabwe *awfs_t)
{
	mwx5_dew_fwow_wuwes(awfs_t->defauwt_wuwe);
	mwx5e_destwoy_fwow_tabwe(&awfs_t->ft);
}

static void _mwx5e_cweanup_tabwes(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5e_awfs_tabwes *awfs =  mwx5e_fs_get_awfs(fs);
	int i;

	awfs_dew_wuwes(fs);
	destwoy_wowkqueue(awfs->wq);
	fow (i = 0; i < AWFS_NUM_TYPES; i++) {
		if (!IS_EWW_OW_NUWW(awfs->awfs_tabwes[i].ft.t))
			awfs_destwoy_tabwe(&awfs->awfs_tabwes[i]);
	}
}

void mwx5e_awfs_destwoy_tabwes(stwuct mwx5e_fwow_steewing *fs, boow ntupwe)
{
	stwuct mwx5e_awfs_tabwes *awfs =  mwx5e_fs_get_awfs(fs);

	if (!ntupwe)
		wetuwn;

	_mwx5e_cweanup_tabwes(fs);
	mwx5e_fs_set_awfs(fs, NUWW);
	kvfwee(awfs);
}

static int awfs_add_defauwt_wuwe(stwuct mwx5e_fwow_steewing *fs,
				 stwuct mwx5e_wx_wes *wx_wes,
				 enum awfs_type type)
{
	stwuct mwx5e_awfs_tabwes *awfs =  mwx5e_fs_get_awfs(fs);
	stwuct awfs_tabwe *awfs_t = &awfs->awfs_tabwes[type];
	stwuct mwx5_fwow_destination dest = {};
	MWX5_DECWAWE_FWOW_ACT(fwow_act);
	enum mwx5_twaffic_types tt;
	int eww = 0;

	dest.type = MWX5_FWOW_DESTINATION_TYPE_TIW;
	tt = awfs_get_tt(type);
	if (tt == -EINVAW) {
		fs_eww(fs, "%s: bad awfs_type: %d\n", __func__, type);
		wetuwn -EINVAW;
	}

	/* FIXME: Must use mwx5_ttc_get_defauwt_dest(),
	 * but can't since TTC defauwt is not setup yet !
	 */
	dest.tiw_num = mwx5e_wx_wes_get_tiwn_wss(wx_wes, tt);
	awfs_t->defauwt_wuwe = mwx5_add_fwow_wuwes(awfs_t->ft.t, NUWW,
						   &fwow_act,
						   &dest, 1);
	if (IS_EWW(awfs_t->defauwt_wuwe)) {
		eww = PTW_EWW(awfs_t->defauwt_wuwe);
		awfs_t->defauwt_wuwe = NUWW;
		fs_eww(fs, "%s: add wuwe faiwed, awfs type=%d\n", __func__, type);
	}

	wetuwn eww;
}

#define MWX5E_AWFS_NUM_GWOUPS	2
#define MWX5E_AWFS_GWOUP1_SIZE	(BIT(16) - 1)
#define MWX5E_AWFS_GWOUP2_SIZE	BIT(0)
#define MWX5E_AWFS_TABWE_SIZE	(MWX5E_AWFS_GWOUP1_SIZE +\
				 MWX5E_AWFS_GWOUP2_SIZE)
static int awfs_cweate_gwoups(stwuct mwx5e_fwow_tabwe *ft,
			      enum  awfs_type type)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	void *outew_headews_c;
	int ix = 0;
	u32 *in;
	int eww;
	u8 *mc;

	ft->g = kcawwoc(MWX5E_AWFS_NUM_GWOUPS,
			sizeof(*ft->g), GFP_KEWNEW);
	if (!ft->g)
		wetuwn -ENOMEM;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_fwee_g;
	}

	mc = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);
	outew_headews_c = MWX5_ADDW_OF(fte_match_pawam, mc,
				       outew_headews);
	MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, outew_headews_c, ethewtype);
	switch (type) {
	case AWFS_IPV4_TCP:
	case AWFS_IPV6_TCP:
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, outew_headews_c, tcp_dpowt);
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, outew_headews_c, tcp_spowt);
		bweak;
	case AWFS_IPV4_UDP:
	case AWFS_IPV6_UDP:
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, outew_headews_c, udp_dpowt);
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, outew_headews_c, udp_spowt);
		bweak;
	defauwt:
		eww = -EINVAW;
		goto eww_fwee_in;
	}

	switch (type) {
	case AWFS_IPV4_TCP:
	case AWFS_IPV4_UDP:
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, outew_headews_c,
				 swc_ipv4_swc_ipv6.ipv4_wayout.ipv4);
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, outew_headews_c,
				 dst_ipv4_dst_ipv6.ipv4_wayout.ipv4);
		bweak;
	case AWFS_IPV6_TCP:
	case AWFS_IPV6_UDP:
		memset(MWX5_ADDW_OF(fte_match_set_wyw_2_4, outew_headews_c,
				    swc_ipv4_swc_ipv6.ipv6_wayout.ipv6),
		       0xff, 16);
		memset(MWX5_ADDW_OF(fte_match_set_wyw_2_4, outew_headews_c,
				    dst_ipv4_dst_ipv6.ipv6_wayout.ipv6),
		       0xff, 16);
		bweak;
	defauwt:
		eww = -EINVAW;
		goto eww_fwee_in;
	}

	MWX5_SET_CFG(in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5E_AWFS_GWOUP1_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww_cwean_gwoup;
	ft->num_gwoups++;

	memset(in, 0, inwen);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5E_AWFS_GWOUP2_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww_cwean_gwoup;
	ft->num_gwoups++;

	kvfwee(in);
	wetuwn 0;

eww_cwean_gwoup:
	eww = PTW_EWW(ft->g[ft->num_gwoups]);
	ft->g[ft->num_gwoups] = NUWW;
eww_fwee_in:
	kvfwee(in);
eww_fwee_g:
	kfwee(ft->g);
	ft->g = NUWW;
	wetuwn eww;
}

static int awfs_cweate_tabwe(stwuct mwx5e_fwow_steewing *fs,
			     stwuct mwx5e_wx_wes *wx_wes,
			     enum awfs_type type)
{
	stwuct mwx5_fwow_namespace *ns = mwx5e_fs_get_ns(fs, fawse);
	stwuct mwx5e_awfs_tabwes *awfs = mwx5e_fs_get_awfs(fs);
	stwuct mwx5e_fwow_tabwe *ft = &awfs->awfs_tabwes[type].ft;
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	int eww;

	ft->num_gwoups = 0;

	ft_attw.max_fte = MWX5E_AWFS_TABWE_SIZE;
	ft_attw.wevew = MWX5E_AWFS_FT_WEVEW;
	ft_attw.pwio = MWX5E_NIC_PWIO;

	ft->t = mwx5_cweate_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(ft->t)) {
		eww = PTW_EWW(ft->t);
		ft->t = NUWW;
		wetuwn eww;
	}

	eww = awfs_cweate_gwoups(ft, type);
	if (eww)
		goto eww;

	eww = awfs_add_defauwt_wuwe(fs, wx_wes,  type);
	if (eww)
		goto eww;

	wetuwn 0;
eww:
	mwx5e_destwoy_fwow_tabwe(ft);
	wetuwn eww;
}

int mwx5e_awfs_cweate_tabwes(stwuct mwx5e_fwow_steewing *fs,
			     stwuct mwx5e_wx_wes *wx_wes, boow ntupwe)
{
	stwuct mwx5e_awfs_tabwes *awfs;
	int eww = -ENOMEM;
	int i;

	if (!ntupwe)
		wetuwn 0;

	awfs = kvzawwoc(sizeof(*awfs), GFP_KEWNEW);
	if (!awfs)
		wetuwn -ENOMEM;

	spin_wock_init(&awfs->awfs_wock);
	awfs->wq = cweate_singwethwead_wowkqueue("mwx5e_awfs");
	if (!awfs->wq)
		goto eww;

	mwx5e_fs_set_awfs(fs, awfs);

	fow (i = 0; i < AWFS_NUM_TYPES; i++) {
		eww = awfs_cweate_tabwe(fs, wx_wes, i);
		if (eww)
			goto eww_des;
	}
	wetuwn 0;

eww_des:
	_mwx5e_cweanup_tabwes(fs);
eww:
	mwx5e_fs_set_awfs(fs, NUWW);
	kvfwee(awfs);
	wetuwn eww;
}

#define MWX5E_AWFS_EXPIWY_QUOTA 60

static void awfs_may_expiwe_fwow(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_awfs_tabwes *awfs = mwx5e_fs_get_awfs(pwiv->fs);
	stwuct awfs_wuwe *awfs_wuwe;
	stwuct hwist_node *htmp;
	HWIST_HEAD(dew_wist);
	int quota = 0;
	int i;
	int j;

	spin_wock_bh(&awfs->awfs_wock);
	mwx5e_fow_each_awfs_wuwe(awfs_wuwe, htmp, awfs->awfs_tabwes, i, j) {
		if (!wowk_pending(&awfs_wuwe->awfs_wowk) &&
		    wps_may_expiwe_fwow(pwiv->netdev,
					awfs_wuwe->wxq, awfs_wuwe->fwow_id,
					awfs_wuwe->fiwtew_id)) {
			hwist_dew_init(&awfs_wuwe->hwist);
			hwist_add_head(&awfs_wuwe->hwist, &dew_wist);
			if (quota++ > MWX5E_AWFS_EXPIWY_QUOTA)
				bweak;
		}
	}
	spin_unwock_bh(&awfs->awfs_wock);
	hwist_fow_each_entwy_safe(awfs_wuwe, htmp, &dew_wist, hwist) {
		if (awfs_wuwe->wuwe) {
			mwx5_dew_fwow_wuwes(awfs_wuwe->wuwe);
			pwiv->channew_stats[awfs_wuwe->wxq]->wq.awfs_expiwed++;
		}
		hwist_dew(&awfs_wuwe->hwist);
		kfwee(awfs_wuwe);
	}
}

static void awfs_dew_wuwes(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5e_awfs_tabwes *awfs = mwx5e_fs_get_awfs(fs);
	stwuct hwist_node *htmp;
	stwuct awfs_wuwe *wuwe;
	HWIST_HEAD(dew_wist);
	int i;
	int j;

	spin_wock_bh(&awfs->awfs_wock);
	mwx5e_fow_each_awfs_wuwe(wuwe, htmp, awfs->awfs_tabwes, i, j) {
		hwist_dew_init(&wuwe->hwist);
		hwist_add_head(&wuwe->hwist, &dew_wist);
	}
	spin_unwock_bh(&awfs->awfs_wock);

	hwist_fow_each_entwy_safe(wuwe, htmp, &dew_wist, hwist) {
		cancew_wowk_sync(&wuwe->awfs_wowk);
		if (wuwe->wuwe)
			mwx5_dew_fwow_wuwes(wuwe->wuwe);
		hwist_dew(&wuwe->hwist);
		kfwee(wuwe);
	}
}

static stwuct hwist_head *
awfs_hash_bucket(stwuct awfs_tabwe *awfs_t, __be16 swc_powt,
		 __be16 dst_powt)
{
	unsigned wong w;
	int bucket_idx;

	w = (__fowce unsigned wong)swc_powt |
	    ((__fowce unsigned wong)dst_powt << 2);

	bucket_idx = hash_wong(w, AWFS_HASH_SHIFT);

	wetuwn &awfs_t->wuwes_hash[bucket_idx];
}

static stwuct awfs_tabwe *awfs_get_tabwe(stwuct mwx5e_awfs_tabwes *awfs,
					 u8 ip_pwoto, __be16 etype)
{
	if (etype == htons(ETH_P_IP) && ip_pwoto == IPPWOTO_TCP)
		wetuwn &awfs->awfs_tabwes[AWFS_IPV4_TCP];
	if (etype == htons(ETH_P_IP) && ip_pwoto == IPPWOTO_UDP)
		wetuwn &awfs->awfs_tabwes[AWFS_IPV4_UDP];
	if (etype == htons(ETH_P_IPV6) && ip_pwoto == IPPWOTO_TCP)
		wetuwn &awfs->awfs_tabwes[AWFS_IPV6_TCP];
	if (etype == htons(ETH_P_IPV6) && ip_pwoto == IPPWOTO_UDP)
		wetuwn &awfs->awfs_tabwes[AWFS_IPV6_UDP];

	wetuwn NUWW;
}

static stwuct mwx5_fwow_handwe *awfs_add_wuwe(stwuct mwx5e_pwiv *pwiv,
					      stwuct awfs_wuwe *awfs_wuwe)
{
	stwuct mwx5e_awfs_tabwes *awfs = mwx5e_fs_get_awfs(pwiv->fs);
	stwuct awfs_tupwe *tupwe = &awfs_wuwe->tupwe;
	stwuct mwx5_fwow_handwe *wuwe = NUWW;
	stwuct mwx5_fwow_destination dest = {};
	MWX5_DECWAWE_FWOW_ACT(fwow_act);
	stwuct awfs_tabwe *awfs_tabwe;
	stwuct mwx5_fwow_spec *spec;
	stwuct mwx5_fwow_tabwe *ft;
	int eww = 0;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec) {
		pwiv->channew_stats[awfs_wuwe->wxq]->wq.awfs_eww++;
		eww = -ENOMEM;
		goto out;
	}
	spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
			 outew_headews.ethewtype);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.ethewtype,
		 ntohs(tupwe->etype));
	awfs_tabwe = awfs_get_tabwe(awfs, tupwe->ip_pwoto, tupwe->etype);
	if (!awfs_tabwe) {
		WAWN_ONCE(1, "awfs tabwe does not exist fow etype %u and ip_pwoto %u\n",
			  tupwe->etype, tupwe->ip_pwoto);
		eww = -EINVAW;
		goto out;
	}

	ft = awfs_tabwe->ft.t;
	if (tupwe->ip_pwoto == IPPWOTO_TCP) {
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.tcp_dpowt);
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.tcp_spowt);
		MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.tcp_dpowt,
			 ntohs(tupwe->dst_powt));
		MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.tcp_spowt,
			 ntohs(tupwe->swc_powt));
	} ewse {
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.udp_dpowt);
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.udp_spowt);
		MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.udp_dpowt,
			 ntohs(tupwe->dst_powt));
		MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.udp_spowt,
			 ntohs(tupwe->swc_powt));
	}
	if (tupwe->etype == htons(ETH_P_IP)) {
		memcpy(MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    outew_headews.swc_ipv4_swc_ipv6.ipv4_wayout.ipv4),
		       &tupwe->swc_ipv4,
		       4);
		memcpy(MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    outew_headews.dst_ipv4_dst_ipv6.ipv4_wayout.ipv4),
		       &tupwe->dst_ipv4,
		       4);
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.swc_ipv4_swc_ipv6.ipv4_wayout.ipv4);
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.dst_ipv4_dst_ipv6.ipv4_wayout.ipv4);
	} ewse {
		memcpy(MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    outew_headews.swc_ipv4_swc_ipv6.ipv6_wayout.ipv6),
		       &tupwe->swc_ipv6,
		       16);
		memcpy(MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    outew_headews.dst_ipv4_dst_ipv6.ipv6_wayout.ipv6),
		       &tupwe->dst_ipv6,
		       16);
		memset(MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
				    outew_headews.swc_ipv4_swc_ipv6.ipv6_wayout.ipv6),
		       0xff,
		       16);
		memset(MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
				    outew_headews.dst_ipv4_dst_ipv6.ipv6_wayout.ipv6),
		       0xff,
		       16);
	}
	dest.type = MWX5_FWOW_DESTINATION_TYPE_TIW;
	dest.tiw_num = mwx5e_wx_wes_get_tiwn_diwect(pwiv->wx_wes, awfs_wuwe->wxq);
	wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, &dest, 1);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		pwiv->channew_stats[awfs_wuwe->wxq]->wq.awfs_eww++;
		netdev_dbg(pwiv->netdev,
			   "%s: add wuwe(fiwtew id=%d, wq idx=%d, ip pwoto=0x%x) faiwed,eww=%d\n",
			   __func__, awfs_wuwe->fiwtew_id, awfs_wuwe->wxq,
			   tupwe->ip_pwoto, eww);
	}

out:
	kvfwee(spec);
	wetuwn eww ? EWW_PTW(eww) : wuwe;
}

static void awfs_modify_wuwe_wq(stwuct mwx5e_pwiv *pwiv,
				stwuct mwx5_fwow_handwe *wuwe, u16 wxq)
{
	stwuct mwx5_fwow_destination dst = {};
	int eww = 0;

	dst.type = MWX5_FWOW_DESTINATION_TYPE_TIW;
	dst.tiw_num = mwx5e_wx_wes_get_tiwn_diwect(pwiv->wx_wes, wxq);
	eww =  mwx5_modify_wuwe_destination(wuwe, &dst, NUWW);
	if (eww) {
		pwiv->channew_stats[wxq]->wq.awfs_eww++;
		netdev_wawn(pwiv->netdev,
			    "Faiwed to modify aWFS wuwe destination to wq=%d\n", wxq);
	}
}

static void awfs_handwe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct awfs_wuwe *awfs_wuwe = containew_of(wowk,
						   stwuct awfs_wuwe,
						   awfs_wowk);
	stwuct mwx5e_pwiv *pwiv = awfs_wuwe->pwiv;
	stwuct mwx5e_awfs_tabwes *awfs;
	stwuct mwx5_fwow_handwe *wuwe;

	awfs = mwx5e_fs_get_awfs(pwiv->fs);
	mutex_wock(&pwiv->state_wock);
	if (!test_bit(MWX5E_STATE_OPENED, &pwiv->state)) {
		spin_wock_bh(&awfs->awfs_wock);
		hwist_dew(&awfs_wuwe->hwist);
		spin_unwock_bh(&awfs->awfs_wock);

		mutex_unwock(&pwiv->state_wock);
		kfwee(awfs_wuwe);
		goto out;
	}
	mutex_unwock(&pwiv->state_wock);

	if (!awfs_wuwe->wuwe) {
		wuwe = awfs_add_wuwe(pwiv, awfs_wuwe);
		if (IS_EWW(wuwe))
			goto out;
		awfs_wuwe->wuwe = wuwe;
		pwiv->channew_stats[awfs_wuwe->wxq]->wq.awfs_add++;
	} ewse {
		awfs_modify_wuwe_wq(pwiv, awfs_wuwe->wuwe,
				    awfs_wuwe->wxq);
	}
out:
	awfs_may_expiwe_fwow(pwiv);
}

static stwuct awfs_wuwe *awfs_awwoc_wuwe(stwuct mwx5e_pwiv *pwiv,
					 stwuct awfs_tabwe *awfs_t,
					 const stwuct fwow_keys *fk,
					 u16 wxq, u32 fwow_id)
{
	stwuct mwx5e_awfs_tabwes *awfs =  mwx5e_fs_get_awfs(pwiv->fs);
	stwuct awfs_wuwe *wuwe;
	stwuct awfs_tupwe *tupwe;

	wuwe = kzawwoc(sizeof(*wuwe), GFP_ATOMIC);
	if (!wuwe) {
		pwiv->channew_stats[wxq]->wq.awfs_eww++;
		wetuwn NUWW;
	}

	wuwe->pwiv = pwiv;
	wuwe->wxq = wxq;
	INIT_WOWK(&wuwe->awfs_wowk, awfs_handwe_wowk);

	tupwe = &wuwe->tupwe;
	tupwe->etype = fk->basic.n_pwoto;
	tupwe->ip_pwoto = fk->basic.ip_pwoto;
	if (tupwe->etype == htons(ETH_P_IP)) {
		tupwe->swc_ipv4 = fk->addws.v4addws.swc;
		tupwe->dst_ipv4 = fk->addws.v4addws.dst;
	} ewse {
		memcpy(&tupwe->swc_ipv6, &fk->addws.v6addws.swc,
		       sizeof(stwuct in6_addw));
		memcpy(&tupwe->dst_ipv6, &fk->addws.v6addws.dst,
		       sizeof(stwuct in6_addw));
	}
	tupwe->swc_powt = fk->powts.swc;
	tupwe->dst_powt = fk->powts.dst;

	wuwe->fwow_id = fwow_id;
	wuwe->fiwtew_id = awfs->wast_fiwtew_id++ % WPS_NO_FIWTEW;

	hwist_add_head(&wuwe->hwist,
		       awfs_hash_bucket(awfs_t, tupwe->swc_powt,
					tupwe->dst_powt));
	wetuwn wuwe;
}

static boow awfs_cmp(const stwuct awfs_tupwe *tupwe, const stwuct fwow_keys *fk)
{
	if (tupwe->swc_powt != fk->powts.swc || tupwe->dst_powt != fk->powts.dst)
		wetuwn fawse;
	if (tupwe->etype != fk->basic.n_pwoto)
		wetuwn fawse;
	if (tupwe->etype == htons(ETH_P_IP))
		wetuwn tupwe->swc_ipv4 == fk->addws.v4addws.swc &&
		       tupwe->dst_ipv4 == fk->addws.v4addws.dst;
	if (tupwe->etype == htons(ETH_P_IPV6))
		wetuwn !memcmp(&tupwe->swc_ipv6, &fk->addws.v6addws.swc,
			       sizeof(stwuct in6_addw)) &&
		       !memcmp(&tupwe->dst_ipv6, &fk->addws.v6addws.dst,
			       sizeof(stwuct in6_addw));
	wetuwn fawse;
}

static stwuct awfs_wuwe *awfs_find_wuwe(stwuct awfs_tabwe *awfs_t,
					const stwuct fwow_keys *fk)
{
	stwuct awfs_wuwe *awfs_wuwe;
	stwuct hwist_head *head;

	head = awfs_hash_bucket(awfs_t, fk->powts.swc, fk->powts.dst);
	hwist_fow_each_entwy(awfs_wuwe, head, hwist) {
		if (awfs_cmp(&awfs_wuwe->tupwe, fk))
			wetuwn awfs_wuwe;
	}

	wetuwn NUWW;
}

int mwx5e_wx_fwow_steew(stwuct net_device *dev, const stwuct sk_buff *skb,
			u16 wxq_index, u32 fwow_id)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mwx5e_awfs_tabwes *awfs;
	stwuct awfs_wuwe *awfs_wuwe;
	stwuct awfs_tabwe *awfs_t;
	stwuct fwow_keys fk;

	awfs =  mwx5e_fs_get_awfs(pwiv->fs);
	if (!skb_fwow_dissect_fwow_keys(skb, &fk, 0))
		wetuwn -EPWOTONOSUPPOWT;

	if (fk.basic.n_pwoto != htons(ETH_P_IP) &&
	    fk.basic.n_pwoto != htons(ETH_P_IPV6))
		wetuwn -EPWOTONOSUPPOWT;

	if (skb->encapsuwation)
		wetuwn -EPWOTONOSUPPOWT;

	awfs_t = awfs_get_tabwe(awfs, fk.basic.ip_pwoto, fk.basic.n_pwoto);
	if (!awfs_t)
		wetuwn -EPWOTONOSUPPOWT;

	spin_wock_bh(&awfs->awfs_wock);
	awfs_wuwe = awfs_find_wuwe(awfs_t, &fk);
	if (awfs_wuwe) {
		if (awfs_wuwe->wxq == wxq_index || wowk_busy(&awfs_wuwe->awfs_wowk)) {
			spin_unwock_bh(&awfs->awfs_wock);
			wetuwn awfs_wuwe->fiwtew_id;
		}

		pwiv->channew_stats[wxq_index]->wq.awfs_wequest_in++;
		pwiv->channew_stats[awfs_wuwe->wxq]->wq.awfs_wequest_out++;
		awfs_wuwe->wxq = wxq_index;
	} ewse {
		awfs_wuwe = awfs_awwoc_wuwe(pwiv, awfs_t, &fk, wxq_index, fwow_id);
		if (!awfs_wuwe) {
			spin_unwock_bh(&awfs->awfs_wock);
			wetuwn -ENOMEM;
		}
	}
	queue_wowk(awfs->wq, &awfs_wuwe->awfs_wowk);
	spin_unwock_bh(&awfs->awfs_wock);
	wetuwn awfs_wuwe->fiwtew_id;
}

