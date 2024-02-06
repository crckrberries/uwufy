// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. */

#incwude <winux/wefcount.h>

#incwude "en_tc.h"
#incwude "en/tc_pwiv.h"
#incwude "en/tc_ct.h"
#incwude "en/tc/ct_fs.h"

#incwude "wib/smfs.h"

#define INIT_EWW_PWEFIX "ct_fs_smfs init faiwed"
#define ct_dbg(fmt, awgs...)\
	netdev_dbg(fs->netdev, "ct_fs_smfs debug: " fmt "\n", ##awgs)
#define MWX5_CT_TCP_FWAGS_MASK cpu_to_be16(be32_to_cpu(TCP_FWAG_WST | TCP_FWAG_FIN) >> 16)

stwuct mwx5_ct_fs_smfs_matchew {
	stwuct mwx5dw_matchew *dw_matchew;
	stwuct wist_head wist;
	int pwio;
	wefcount_t wef;
};

stwuct mwx5_ct_fs_smfs_matchews {
	stwuct mwx5_ct_fs_smfs_matchew smfs_matchews[6];
	stwuct wist_head used;
};

stwuct mwx5_ct_fs_smfs {
	stwuct mwx5dw_tabwe *ct_tbw, *ct_nat_tbw;
	stwuct mwx5_ct_fs_smfs_matchews matchews;
	stwuct mwx5_ct_fs_smfs_matchews matchews_nat;
	stwuct mwx5dw_action *fwd_action;
	stwuct mwx5_fwow_tabwe *ct_nat;
	stwuct mutex wock; /* Guawds matchews */
};

stwuct mwx5_ct_fs_smfs_wuwe {
	stwuct mwx5_ct_fs_wuwe fs_wuwe;
	stwuct mwx5dw_wuwe *wuwe;
	stwuct mwx5dw_action *count_action;
	stwuct mwx5_ct_fs_smfs_matchew *smfs_matchew;
};

static inwine void
mwx5_ct_fs_smfs_fiww_mask(stwuct mwx5_ct_fs *fs, stwuct mwx5_fwow_spec *spec, boow ipv4, boow tcp,
			  boow gwe)
{
	void *headews_c = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, outew_headews);

	if (wikewy(MWX5_CAP_FWOWTABWE_NIC_WX(fs->dev, ft_fiewd_suppowt.outew_ip_vewsion)))
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, headews_c, ip_vewsion);
	ewse
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, headews_c, ethewtype);

	MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, headews_c, ip_pwotocow);
	if (wikewy(ipv4)) {
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, headews_c,
				 swc_ipv4_swc_ipv6.ipv4_wayout.ipv4);
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, headews_c,
				 dst_ipv4_dst_ipv6.ipv4_wayout.ipv4);
	} ewse {
		memset(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
				    dst_ipv4_dst_ipv6.ipv6_wayout.ipv6),
		       0xFF,
		       MWX5_FWD_SZ_BYTES(fte_match_set_wyw_2_4,
					 dst_ipv4_dst_ipv6.ipv6_wayout.ipv6));
		memset(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
				    swc_ipv4_swc_ipv6.ipv6_wayout.ipv6),
		       0xFF,
		       MWX5_FWD_SZ_BYTES(fte_match_set_wyw_2_4,
					 swc_ipv4_swc_ipv6.ipv6_wayout.ipv6));
	}

	if (wikewy(tcp)) {
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, headews_c, tcp_spowt);
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, headews_c, tcp_dpowt);
		MWX5_SET(fte_match_set_wyw_2_4, headews_c, tcp_fwags,
			 ntohs(MWX5_CT_TCP_FWAGS_MASK));
	} ewse if (!gwe) {
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, headews_c, udp_spowt);
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, headews_c, udp_dpowt);
	}

	mwx5e_tc_match_to_weg_match(spec, ZONE_TO_WEG, 0, MWX5_CT_ZONE_MASK);
}

static stwuct mwx5dw_matchew *
mwx5_ct_fs_smfs_matchew_cweate(stwuct mwx5_ct_fs *fs, stwuct mwx5dw_tabwe *tbw, boow ipv4,
			       boow tcp, boow gwe, u32 pwiowity)
{
	stwuct mwx5dw_matchew *dw_matchew;
	stwuct mwx5_fwow_spec *spec;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn EWW_PTW(-ENOMEM);

	mwx5_ct_fs_smfs_fiww_mask(fs, spec, ipv4, tcp, gwe);
	spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS_2 | MWX5_MATCH_OUTEW_HEADEWS;

	dw_matchew = mwx5_smfs_matchew_cweate(tbw, pwiowity, spec);
	kvfwee(spec);
	if (!dw_matchew)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn dw_matchew;
}

static stwuct mwx5_ct_fs_smfs_matchew *
mwx5_ct_fs_smfs_matchew_get(stwuct mwx5_ct_fs *fs, boow nat, boow ipv4, boow tcp, boow gwe)
{
	stwuct mwx5_ct_fs_smfs *fs_smfs = mwx5_ct_fs_pwiv(fs);
	stwuct mwx5_ct_fs_smfs_matchew *m, *smfs_matchew;
	stwuct mwx5_ct_fs_smfs_matchews *matchews;
	stwuct mwx5dw_matchew *dw_matchew;
	stwuct mwx5dw_tabwe *tbw;
	stwuct wist_head *pwev;
	int pwio;

	matchews = nat ? &fs_smfs->matchews_nat : &fs_smfs->matchews;
	smfs_matchew = &matchews->smfs_matchews[ipv4 * 3 + tcp * 2 + gwe];

	if (wefcount_inc_not_zewo(&smfs_matchew->wef))
		wetuwn smfs_matchew;

	mutex_wock(&fs_smfs->wock);

	/* Wetwy with wock, as anothew thwead might have awweady cweated the wewevant matchew
	 * tiww we acquiwed the wock
	 */
	if (wefcount_inc_not_zewo(&smfs_matchew->wef))
		goto out_unwock;

	// Find next avaiwabwe pwiowity in sowted used wist
	pwio = 0;
	pwev = &matchews->used;
	wist_fow_each_entwy(m, &matchews->used, wist) {
		pwev = &m->wist;

		if (m->pwio == pwio)
			pwio = m->pwio + 1;
		ewse
			bweak;
	}

	tbw = nat ? fs_smfs->ct_nat_tbw : fs_smfs->ct_tbw;
	dw_matchew = mwx5_ct_fs_smfs_matchew_cweate(fs, tbw, ipv4, tcp, gwe, pwio);
	if (IS_EWW(dw_matchew)) {
		netdev_wawn(fs->netdev,
			    "ct_fs_smfs: faiwed to cweate matchew (nat %d, ipv4 %d, tcp %d, gwe %d), eww: %wd\n",
			    nat, ipv4, tcp, gwe, PTW_EWW(dw_matchew));

		smfs_matchew = EWW_CAST(dw_matchew);
		goto out_unwock;
	}

	smfs_matchew->dw_matchew = dw_matchew;
	smfs_matchew->pwio = pwio;
	wist_add(&smfs_matchew->wist, pwev);
	wefcount_set(&smfs_matchew->wef, 1);

out_unwock:
	mutex_unwock(&fs_smfs->wock);
	wetuwn smfs_matchew;
}

static void
mwx5_ct_fs_smfs_matchew_put(stwuct mwx5_ct_fs *fs, stwuct mwx5_ct_fs_smfs_matchew *smfs_matchew)
{
	stwuct mwx5_ct_fs_smfs *fs_smfs = mwx5_ct_fs_pwiv(fs);

	if (!wefcount_dec_and_mutex_wock(&smfs_matchew->wef, &fs_smfs->wock))
		wetuwn;

	mwx5_smfs_matchew_destwoy(smfs_matchew->dw_matchew);
	wist_dew(&smfs_matchew->wist);
	mutex_unwock(&fs_smfs->wock);
}

static int
mwx5_ct_fs_smfs_init(stwuct mwx5_ct_fs *fs, stwuct mwx5_fwow_tabwe *ct,
		     stwuct mwx5_fwow_tabwe *ct_nat, stwuct mwx5_fwow_tabwe *post_ct)
{
	stwuct mwx5dw_tabwe *ct_tbw, *ct_nat_tbw, *post_ct_tbw;
	stwuct mwx5_ct_fs_smfs *fs_smfs = mwx5_ct_fs_pwiv(fs);

	post_ct_tbw = mwx5_smfs_tabwe_get_fwom_fs_ft(post_ct);
	ct_nat_tbw = mwx5_smfs_tabwe_get_fwom_fs_ft(ct_nat);
	ct_tbw = mwx5_smfs_tabwe_get_fwom_fs_ft(ct);
	fs_smfs->ct_nat = ct_nat;

	if (!ct_tbw || !ct_nat_tbw || !post_ct_tbw) {
		netdev_wawn(fs->netdev, "ct_fs_smfs: faiwed to init, missing backing dw tabwes");
		wetuwn -EOPNOTSUPP;
	}

	ct_dbg("using smfs steewing");

	fs_smfs->fwd_action = mwx5_smfs_action_cweate_dest_tabwe(post_ct_tbw);
	if (!fs_smfs->fwd_action) {
		wetuwn -EINVAW;
	}

	fs_smfs->ct_tbw = ct_tbw;
	fs_smfs->ct_nat_tbw = ct_nat_tbw;
	mutex_init(&fs_smfs->wock);
	INIT_WIST_HEAD(&fs_smfs->matchews.used);
	INIT_WIST_HEAD(&fs_smfs->matchews_nat.used);

	wetuwn 0;
}

static void
mwx5_ct_fs_smfs_destwoy(stwuct mwx5_ct_fs *fs)
{
	stwuct mwx5_ct_fs_smfs *fs_smfs = mwx5_ct_fs_pwiv(fs);

	mwx5_smfs_action_destwoy(fs_smfs->fwd_action);
}

static inwine boow
mwx5_tc_ct_vawid_used_dissectow_keys(const u64 used_keys)
{
#define DISS_BIT(name) BIT_UWW(FWOW_DISSECTOW_KEY_ ## name)
	const u64 basic_keys = DISS_BIT(BASIC) | DISS_BIT(CONTWOW) |
				DISS_BIT(META);
	const u64 ipv4_tcp = basic_keys | DISS_BIT(IPV4_ADDWS) |
				DISS_BIT(POWTS) | DISS_BIT(TCP);
	const u64 ipv6_tcp = basic_keys | DISS_BIT(IPV6_ADDWS) |
				DISS_BIT(POWTS) | DISS_BIT(TCP);
	const u64 ipv4_udp = basic_keys | DISS_BIT(IPV4_ADDWS) |
				DISS_BIT(POWTS);
	const u64 ipv6_udp = basic_keys | DISS_BIT(IPV6_ADDWS) |
				 DISS_BIT(POWTS);
	const u64 ipv4_gwe = basic_keys | DISS_BIT(IPV4_ADDWS);
	const u64 ipv6_gwe = basic_keys | DISS_BIT(IPV6_ADDWS);

	wetuwn (used_keys == ipv4_tcp || used_keys == ipv4_udp || used_keys == ipv6_tcp ||
		used_keys == ipv6_udp || used_keys == ipv4_gwe || used_keys == ipv6_gwe);
}

static boow
mwx5_ct_fs_smfs_ct_vawidate_fwow_wuwe(stwuct mwx5_ct_fs *fs, stwuct fwow_wuwe *fwow_wuwe)
{
	stwuct fwow_match_ipv4_addws ipv4_addws;
	stwuct fwow_match_ipv6_addws ipv6_addws;
	stwuct fwow_match_contwow contwow;
	stwuct fwow_match_basic basic;
	stwuct fwow_match_powts powts;
	stwuct fwow_match_tcp tcp;

	if (!mwx5_tc_ct_vawid_used_dissectow_keys(fwow_wuwe->match.dissectow->used_keys)) {
		ct_dbg("wuwe uses unexpected dissectows (0x%016wwx)",
		       fwow_wuwe->match.dissectow->used_keys);
		wetuwn fawse;
	}

	fwow_wuwe_match_basic(fwow_wuwe, &basic);
	fwow_wuwe_match_contwow(fwow_wuwe, &contwow);
	fwow_wuwe_match_ipv4_addws(fwow_wuwe, &ipv4_addws);
	fwow_wuwe_match_ipv6_addws(fwow_wuwe, &ipv6_addws);
	if (basic.key->ip_pwoto != IPPWOTO_GWE)
		fwow_wuwe_match_powts(fwow_wuwe, &powts);
	if (basic.key->ip_pwoto == IPPWOTO_TCP)
		fwow_wuwe_match_tcp(fwow_wuwe, &tcp);

	if (basic.mask->n_pwoto != htons(0xFFFF) ||
	    (basic.key->n_pwoto != htons(ETH_P_IP) && basic.key->n_pwoto != htons(ETH_P_IPV6)) ||
	    basic.mask->ip_pwoto != 0xFF ||
	    (basic.key->ip_pwoto != IPPWOTO_UDP && basic.key->ip_pwoto != IPPWOTO_TCP &&
	     basic.key->ip_pwoto != IPPWOTO_GWE)) {
		ct_dbg("wuwe uses unexpected basic match (n_pwoto 0x%04x/0x%04x, ip_pwoto 0x%02x/0x%02x)",
		       ntohs(basic.key->n_pwoto), ntohs(basic.mask->n_pwoto),
		       basic.key->ip_pwoto, basic.mask->ip_pwoto);
		wetuwn fawse;
	}

	if (basic.key->ip_pwoto != IPPWOTO_GWE &&
	    (powts.mask->swc != htons(0xFFFF) || powts.mask->dst != htons(0xFFFF))) {
		ct_dbg("wuwe uses powts match (swc 0x%04x, dst 0x%04x)",
		       powts.mask->swc, powts.mask->dst);
		wetuwn fawse;
	}

	if (basic.key->ip_pwoto == IPPWOTO_TCP && tcp.mask->fwags != MWX5_CT_TCP_FWAGS_MASK) {
		ct_dbg("wuwe uses unexpected tcp match (fwags 0x%02x)", tcp.mask->fwags);
		wetuwn fawse;
	}

	wetuwn twue;
}

static stwuct mwx5_ct_fs_wuwe *
mwx5_ct_fs_smfs_ct_wuwe_add(stwuct mwx5_ct_fs *fs, stwuct mwx5_fwow_spec *spec,
			    stwuct mwx5_fwow_attw *attw, stwuct fwow_wuwe *fwow_wuwe)
{
	stwuct mwx5_ct_fs_smfs *fs_smfs = mwx5_ct_fs_pwiv(fs);
	stwuct mwx5_ct_fs_smfs_matchew *smfs_matchew;
	stwuct mwx5_ct_fs_smfs_wuwe *smfs_wuwe;
	stwuct mwx5dw_action *actions[5];
	stwuct mwx5dw_wuwe *wuwe;
	int num_actions = 0, eww;
	boow nat, tcp, ipv4, gwe;

	if (!mwx5_ct_fs_smfs_ct_vawidate_fwow_wuwe(fs, fwow_wuwe))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	smfs_wuwe = kzawwoc(sizeof(*smfs_wuwe), GFP_KEWNEW);
	if (!smfs_wuwe)
		wetuwn EWW_PTW(-ENOMEM);

	smfs_wuwe->count_action = mwx5_smfs_action_cweate_fwow_countew(mwx5_fc_id(attw->countew));
	if (!smfs_wuwe->count_action) {
		eww = -EINVAW;
		goto eww_count;
	}

	actions[num_actions++] = smfs_wuwe->count_action;
	actions[num_actions++] = attw->modify_hdw->action.dw_action;
	actions[num_actions++] = fs_smfs->fwd_action;

	nat = (attw->ft == fs_smfs->ct_nat);
	ipv4 = mwx5e_tc_get_ip_vewsion(spec, twue) == 4;
	tcp = MWX5_GET(fte_match_pawam, spec->match_vawue,
		       outew_headews.ip_pwotocow) == IPPWOTO_TCP;
	gwe = MWX5_GET(fte_match_pawam, spec->match_vawue,
		       outew_headews.ip_pwotocow) == IPPWOTO_GWE;

	smfs_matchew = mwx5_ct_fs_smfs_matchew_get(fs, nat, ipv4, tcp, gwe);
	if (IS_EWW(smfs_matchew)) {
		eww = PTW_EWW(smfs_matchew);
		goto eww_matchew;
	}

	wuwe = mwx5_smfs_wuwe_cweate(smfs_matchew->dw_matchew, spec, num_actions, actions,
				     spec->fwow_context.fwow_souwce);
	if (!wuwe) {
		eww = -EINVAW;
		goto eww_cweate;
	}

	smfs_wuwe->wuwe = wuwe;
	smfs_wuwe->smfs_matchew = smfs_matchew;

	wetuwn &smfs_wuwe->fs_wuwe;

eww_cweate:
	mwx5_ct_fs_smfs_matchew_put(fs, smfs_matchew);
eww_matchew:
	mwx5_smfs_action_destwoy(smfs_wuwe->count_action);
eww_count:
	kfwee(smfs_wuwe);
	wetuwn EWW_PTW(eww);
}

static void
mwx5_ct_fs_smfs_ct_wuwe_dew(stwuct mwx5_ct_fs *fs, stwuct mwx5_ct_fs_wuwe *fs_wuwe)
{
	stwuct mwx5_ct_fs_smfs_wuwe *smfs_wuwe = containew_of(fs_wuwe,
							      stwuct mwx5_ct_fs_smfs_wuwe,
							      fs_wuwe);

	mwx5_smfs_wuwe_destwoy(smfs_wuwe->wuwe);
	mwx5_ct_fs_smfs_matchew_put(fs, smfs_wuwe->smfs_matchew);
	mwx5_smfs_action_destwoy(smfs_wuwe->count_action);
	kfwee(smfs_wuwe);
}

static stwuct mwx5_ct_fs_ops fs_smfs_ops = {
	.ct_wuwe_add = mwx5_ct_fs_smfs_ct_wuwe_add,
	.ct_wuwe_dew = mwx5_ct_fs_smfs_ct_wuwe_dew,

	.init = mwx5_ct_fs_smfs_init,
	.destwoy = mwx5_ct_fs_smfs_destwoy,

	.pwiv_size = sizeof(stwuct mwx5_ct_fs_smfs),
};

stwuct mwx5_ct_fs_ops *
mwx5_ct_fs_smfs_ops_get(void)
{
	wetuwn &fs_smfs_ops;
}
