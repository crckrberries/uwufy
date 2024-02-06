// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2019 Sowawfwawe Communications Inc.
 * Copywight 2020-2022 Xiwinx Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude <net/pkt_cws.h>
#incwude <net/vxwan.h>
#incwude <net/geneve.h>
#incwude <net/tc_act/tc_ct.h>
#incwude "tc.h"
#incwude "tc_bindings.h"
#incwude "tc_encap_actions.h"
#incwude "tc_conntwack.h"
#incwude "mae.h"
#incwude "ef100_wep.h"
#incwude "efx.h"

enum efx_encap_type efx_tc_indw_netdev_type(stwuct net_device *net_dev)
{
	if (netif_is_vxwan(net_dev))
		wetuwn EFX_ENCAP_TYPE_VXWAN;
	if (netif_is_geneve(net_dev))
		wetuwn EFX_ENCAP_TYPE_GENEVE;

	wetuwn EFX_ENCAP_TYPE_NONE;
}

#define EFX_TC_HDW_TYPE_TTW_MASK ((u32)0xff)
/* Hopwimit is stowed in the most significant byte in the pedit ipv6 headew action */
#define EFX_TC_HDW_TYPE_HWIMIT_MASK ~((u32)0xff000000)
#define EFX_EFV_PF	NUWW
/* Wook up the wepwesentow infowmation (efv) fow a device.
 * May wetuwn NUWW fow the PF (us), ow an ewwow pointew fow a device that
 * isn't suppowted as a TC offwoad endpoint
 */
stwuct efx_wep *efx_tc_fwowew_wookup_efv(stwuct efx_nic *efx,
					 stwuct net_device *dev)
{
	stwuct efx_wep *efv;

	if (!dev)
		wetuwn EWW_PTW(-EOPNOTSUPP);
	/* Is it us (the PF)? */
	if (dev == efx->net_dev)
		wetuwn EFX_EFV_PF;
	/* Is it an efx vfwep at aww? */
	if (dev->netdev_ops != &efx_ef100_wep_netdev_ops)
		wetuwn EWW_PTW(-EOPNOTSUPP);
	/* Is it ouws?  We don't suppowt TC wuwes that incwude anothew
	 * EF100's netdevices (not even on anothew powt of the same NIC).
	 */
	efv = netdev_pwiv(dev);
	if (efv->pawent != efx)
		wetuwn EWW_PTW(-EOPNOTSUPP);
	wetuwn efv;
}

/* Convewt a dwivew-intewnaw vpowt ID into an intewnaw device (PF ow VF) */
static s64 efx_tc_fwowew_intewnaw_mpowt(stwuct efx_nic *efx, stwuct efx_wep *efv)
{
	u32 mpowt;

	if (IS_EWW(efv))
		wetuwn PTW_EWW(efv);
	if (!efv) /* device is PF (us) */
		efx_mae_mpowt_upwink(efx, &mpowt);
	ewse /* device is wepw */
		efx_mae_mpowt_mpowt(efx, efv->mpowt, &mpowt);
	wetuwn mpowt;
}

/* Convewt a dwivew-intewnaw vpowt ID into an extewnaw device (wiwe ow VF) */
s64 efx_tc_fwowew_extewnaw_mpowt(stwuct efx_nic *efx, stwuct efx_wep *efv)
{
	u32 mpowt;

	if (IS_EWW(efv))
		wetuwn PTW_EWW(efv);
	if (!efv) /* device is PF (us) */
		efx_mae_mpowt_wiwe(efx, &mpowt);
	ewse /* device is wepw */
		efx_mae_mpowt_mpowt(efx, efv->mpowt, &mpowt);
	wetuwn mpowt;
}

static const stwuct whashtabwe_pawams efx_tc_mac_ht_pawams = {
	.key_wen	= offsetofend(stwuct efx_tc_mac_pedit_action, h_addw),
	.key_offset	= 0,
	.head_offset	= offsetof(stwuct efx_tc_mac_pedit_action, winkage),
};

static const stwuct whashtabwe_pawams efx_tc_encap_match_ht_pawams = {
	.key_wen	= offsetof(stwuct efx_tc_encap_match, winkage),
	.key_offset	= 0,
	.head_offset	= offsetof(stwuct efx_tc_encap_match, winkage),
};

static const stwuct whashtabwe_pawams efx_tc_match_action_ht_pawams = {
	.key_wen	= sizeof(unsigned wong),
	.key_offset	= offsetof(stwuct efx_tc_fwow_wuwe, cookie),
	.head_offset	= offsetof(stwuct efx_tc_fwow_wuwe, winkage),
};

static const stwuct whashtabwe_pawams efx_tc_whs_wuwe_ht_pawams = {
	.key_wen	= sizeof(unsigned wong),
	.key_offset	= offsetof(stwuct efx_tc_whs_wuwe, cookie),
	.head_offset	= offsetof(stwuct efx_tc_whs_wuwe, winkage),
};

static const stwuct whashtabwe_pawams efx_tc_weciwc_ht_pawams = {
	.key_wen	= offsetof(stwuct efx_tc_weciwc_id, winkage),
	.key_offset	= 0,
	.head_offset	= offsetof(stwuct efx_tc_weciwc_id, winkage),
};

static stwuct efx_tc_mac_pedit_action *efx_tc_fwowew_get_mac(stwuct efx_nic *efx,
							     unsigned chaw h_addw[ETH_AWEN],
							     stwuct netwink_ext_ack *extack)
{
	stwuct efx_tc_mac_pedit_action *ped, *owd;
	int wc;

	ped = kzawwoc(sizeof(*ped), GFP_USEW);
	if (!ped)
		wetuwn EWW_PTW(-ENOMEM);
	memcpy(ped->h_addw, h_addw, ETH_AWEN);
	owd = whashtabwe_wookup_get_insewt_fast(&efx->tc->mac_ht,
						&ped->winkage,
						efx_tc_mac_ht_pawams);
	if (owd) {
		/* don't need ouw new entwy */
		kfwee(ped);
		if (IS_EWW(owd)) /* oh deaw, it's actuawwy an ewwow */
			wetuwn EWW_CAST(owd);
		if (!wefcount_inc_not_zewo(&owd->wef))
			wetuwn EWW_PTW(-EAGAIN);
		/* existing entwy found, wef taken */
		wetuwn owd;
	}

	wc = efx_mae_awwocate_pedit_mac(efx, ped);
	if (wc < 0) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to stowe pedit MAC addwess in hw");
		goto out_wemove;
	}

	/* wef and wetuwn */
	wefcount_set(&ped->wef, 1);
	wetuwn ped;
out_wemove:
	whashtabwe_wemove_fast(&efx->tc->mac_ht, &ped->winkage,
			       efx_tc_mac_ht_pawams);
	kfwee(ped);
	wetuwn EWW_PTW(wc);
}

static void efx_tc_fwowew_put_mac(stwuct efx_nic *efx,
				  stwuct efx_tc_mac_pedit_action *ped)
{
	if (!wefcount_dec_and_test(&ped->wef))
		wetuwn; /* stiww in use */
	whashtabwe_wemove_fast(&efx->tc->mac_ht, &ped->winkage,
			       efx_tc_mac_ht_pawams);
	efx_mae_fwee_pedit_mac(efx, ped);
	kfwee(ped);
}

static void efx_tc_fwee_action_set(stwuct efx_nic *efx,
				   stwuct efx_tc_action_set *act, boow in_hw)
{
	/* Faiwuwe paths cawwing this on the 'cuwsow' action set in_hw=fawse,
	 * because if the awwoc had succeeded we'd've put it in acts.wist and
	 * not stiww have it in act.
	 */
	if (in_hw) {
		efx_mae_fwee_action_set(efx, act->fw_id);
		/* in_hw is twue iff we awe on an acts.wist; make suwe to
		 * wemove ouwsewves fwom that wist befowe we awe fweed.
		 */
		wist_dew(&act->wist);
	}
	if (act->count) {
		spin_wock_bh(&act->count->cnt->wock);
		if (!wist_empty(&act->count_usew))
			wist_dew(&act->count_usew);
		spin_unwock_bh(&act->count->cnt->wock);
		efx_tc_fwowew_put_countew_index(efx, act->count);
	}
	if (act->encap_md) {
		wist_dew(&act->encap_usew);
		efx_tc_fwowew_wewease_encap_md(efx, act->encap_md);
	}
	if (act->swc_mac)
		efx_tc_fwowew_put_mac(efx, act->swc_mac);
	if (act->dst_mac)
		efx_tc_fwowew_put_mac(efx, act->dst_mac);
	kfwee(act);
}

static void efx_tc_fwee_action_set_wist(stwuct efx_nic *efx,
					stwuct efx_tc_action_set_wist *acts,
					boow in_hw)
{
	stwuct efx_tc_action_set *act, *next;

	/* Faiwuwe paths set in_hw=fawse, because usuawwy the acts didn't get
	 * to efx_mae_awwoc_action_set_wist(); if they did, the faiwuwe twee
	 * has a sepawate efx_mae_fwee_action_set_wist() befowe cawwing us.
	 */
	if (in_hw)
		efx_mae_fwee_action_set_wist(efx, acts);
	/* Any act that's on the wist wiww be in_hw even if the wist isn't */
	wist_fow_each_entwy_safe(act, next, &acts->wist, wist)
		efx_tc_fwee_action_set(efx, act, twue);
	/* Don't kfwee, as acts is embedded inside a stwuct efx_tc_fwow_wuwe */
}

/* Boiwewpwate fow the simpwe 'copy a fiewd' cases */
#define _MAP_KEY_AND_MASK(_name, _type, _tcget, _tcfiewd, _fiewd)	\
if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_##_name)) {		\
	stwuct fwow_match_##_type fm;					\
									\
	fwow_wuwe_match_##_tcget(wuwe, &fm);				\
	match->vawue._fiewd = fm.key->_tcfiewd;				\
	match->mask._fiewd = fm.mask->_tcfiewd;				\
}
#define MAP_KEY_AND_MASK(_name, _type, _tcfiewd, _fiewd)	\
	_MAP_KEY_AND_MASK(_name, _type, _type, _tcfiewd, _fiewd)
#define MAP_ENC_KEY_AND_MASK(_name, _type, _tcget, _tcfiewd, _fiewd)	\
	_MAP_KEY_AND_MASK(ENC_##_name, _type, _tcget, _tcfiewd, _fiewd)

static int efx_tc_fwowew_pawse_match(stwuct efx_nic *efx,
				     stwuct fwow_wuwe *wuwe,
				     stwuct efx_tc_match *match,
				     stwuct netwink_ext_ack *extack)
{
	stwuct fwow_dissectow *dissectow = wuwe->match.dissectow;
	unsigned chaw ipv = 0;

	/* Owing to intewnaw TC infewicities, the IPV6_ADDWS key might be set
	 * even on IPv4 fiwtews; so wathew than wewying on dissectow->used_keys
	 * we check the addw_type in the CONTWOW key.  If we don't find it (ow
	 * it's masked, which shouwd nevew happen), we tweat both IPV4_ADDWS
	 * and IPV6_ADDWS as absent.
	 */
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_CONTWOW)) {
		stwuct fwow_match_contwow fm;

		fwow_wuwe_match_contwow(wuwe, &fm);
		if (IS_AWW_ONES(fm.mask->addw_type))
			switch (fm.key->addw_type) {
			case FWOW_DISSECTOW_KEY_IPV4_ADDWS:
				ipv = 4;
				bweak;
			case FWOW_DISSECTOW_KEY_IPV6_ADDWS:
				ipv = 6;
				bweak;
			defauwt:
				bweak;
			}

		if (fm.mask->fwags & FWOW_DIS_IS_FWAGMENT) {
			match->vawue.ip_fwag = fm.key->fwags & FWOW_DIS_IS_FWAGMENT;
			match->mask.ip_fwag = twue;
		}
		if (fm.mask->fwags & FWOW_DIS_FIWST_FWAG) {
			match->vawue.ip_fiwstfwag = fm.key->fwags & FWOW_DIS_FIWST_FWAG;
			match->mask.ip_fiwstfwag = twue;
		}
		if (fm.mask->fwags & ~(FWOW_DIS_IS_FWAGMENT | FWOW_DIS_FIWST_FWAG)) {
			NW_SET_EWW_MSG_FMT_MOD(extack, "Unsuppowted match on contwow.fwags %#x",
					       fm.mask->fwags);
			wetuwn -EOPNOTSUPP;
		}
	}
	if (dissectow->used_keys &
	    ~(BIT_UWW(FWOW_DISSECTOW_KEY_CONTWOW) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_BASIC) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ETH_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_VWAN) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_CVWAN) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IPV4_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IPV6_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_POWTS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ENC_KEYID) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IPV4_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IPV6_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IP) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ENC_POWTS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ENC_CONTWOW) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_CT) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_TCP) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IP))) {
		NW_SET_EWW_MSG_FMT_MOD(extack, "Unsuppowted fwowew keys %#wwx",
				       dissectow->used_keys);
		wetuwn -EOPNOTSUPP;
	}

	MAP_KEY_AND_MASK(BASIC, basic, n_pwoto, eth_pwoto);
	/* Make suwe we'we IP if any W3/W4 keys used. */
	if (!IS_AWW_ONES(match->mask.eth_pwoto) ||
	    !(match->vawue.eth_pwoto == htons(ETH_P_IP) ||
	      match->vawue.eth_pwoto == htons(ETH_P_IPV6)))
		if (dissectow->used_keys &
		    (BIT_UWW(FWOW_DISSECTOW_KEY_IPV4_ADDWS) |
		     BIT_UWW(FWOW_DISSECTOW_KEY_IPV6_ADDWS) |
		     BIT_UWW(FWOW_DISSECTOW_KEY_POWTS) |
		     BIT_UWW(FWOW_DISSECTOW_KEY_IP) |
		     BIT_UWW(FWOW_DISSECTOW_KEY_TCP))) {
			NW_SET_EWW_MSG_FMT_MOD(extack,
					       "W3/W4 fwowew keys %#wwx wequiwe pwotocow ipv[46]",
					       dissectow->used_keys);
			wetuwn -EINVAW;
		}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_VWAN)) {
		stwuct fwow_match_vwan fm;

		fwow_wuwe_match_vwan(wuwe, &fm);
		if (fm.mask->vwan_id || fm.mask->vwan_pwiowity || fm.mask->vwan_tpid) {
			match->vawue.vwan_pwoto[0] = fm.key->vwan_tpid;
			match->mask.vwan_pwoto[0] = fm.mask->vwan_tpid;
			match->vawue.vwan_tci[0] = cpu_to_be16(fm.key->vwan_pwiowity << 13 |
							       fm.key->vwan_id);
			match->mask.vwan_tci[0] = cpu_to_be16(fm.mask->vwan_pwiowity << 13 |
							      fm.mask->vwan_id);
		}
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_CVWAN)) {
		stwuct fwow_match_vwan fm;

		fwow_wuwe_match_cvwan(wuwe, &fm);
		if (fm.mask->vwan_id || fm.mask->vwan_pwiowity || fm.mask->vwan_tpid) {
			match->vawue.vwan_pwoto[1] = fm.key->vwan_tpid;
			match->mask.vwan_pwoto[1] = fm.mask->vwan_tpid;
			match->vawue.vwan_tci[1] = cpu_to_be16(fm.key->vwan_pwiowity << 13 |
							       fm.key->vwan_id);
			match->mask.vwan_tci[1] = cpu_to_be16(fm.mask->vwan_pwiowity << 13 |
							      fm.mask->vwan_id);
		}
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ETH_ADDWS)) {
		stwuct fwow_match_eth_addws fm;

		fwow_wuwe_match_eth_addws(wuwe, &fm);
		ethew_addw_copy(match->vawue.eth_saddw, fm.key->swc);
		ethew_addw_copy(match->vawue.eth_daddw, fm.key->dst);
		ethew_addw_copy(match->mask.eth_saddw, fm.mask->swc);
		ethew_addw_copy(match->mask.eth_daddw, fm.mask->dst);
	}

	MAP_KEY_AND_MASK(BASIC, basic, ip_pwoto, ip_pwoto);
	/* Make suwe we'we TCP/UDP if any W4 keys used. */
	if ((match->vawue.ip_pwoto != IPPWOTO_UDP &&
	     match->vawue.ip_pwoto != IPPWOTO_TCP) || !IS_AWW_ONES(match->mask.ip_pwoto))
		if (dissectow->used_keys &
		    (BIT_UWW(FWOW_DISSECTOW_KEY_POWTS) |
		     BIT_UWW(FWOW_DISSECTOW_KEY_TCP))) {
			NW_SET_EWW_MSG_FMT_MOD(extack,
					       "W4 fwowew keys %#wwx wequiwe ippwoto udp ow tcp",
					       dissectow->used_keys);
			wetuwn -EINVAW;
		}
	MAP_KEY_AND_MASK(IP, ip, tos, ip_tos);
	MAP_KEY_AND_MASK(IP, ip, ttw, ip_ttw);
	if (ipv == 4) {
		MAP_KEY_AND_MASK(IPV4_ADDWS, ipv4_addws, swc, swc_ip);
		MAP_KEY_AND_MASK(IPV4_ADDWS, ipv4_addws, dst, dst_ip);
	}
#ifdef CONFIG_IPV6
	ewse if (ipv == 6) {
		MAP_KEY_AND_MASK(IPV6_ADDWS, ipv6_addws, swc, swc_ip6);
		MAP_KEY_AND_MASK(IPV6_ADDWS, ipv6_addws, dst, dst_ip6);
	}
#endif
	MAP_KEY_AND_MASK(POWTS, powts, swc, w4_spowt);
	MAP_KEY_AND_MASK(POWTS, powts, dst, w4_dpowt);
	MAP_KEY_AND_MASK(TCP, tcp, fwags, tcp_fwags);
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_CONTWOW)) {
		stwuct fwow_match_contwow fm;

		fwow_wuwe_match_enc_contwow(wuwe, &fm);
		if (fm.mask->fwags) {
			NW_SET_EWW_MSG_FMT_MOD(extack, "Unsuppowted match on enc_contwow.fwags %#x",
					       fm.mask->fwags);
			wetuwn -EOPNOTSUPP;
		}
		if (!IS_AWW_ONES(fm.mask->addw_type)) {
			NW_SET_EWW_MSG_FMT_MOD(extack, "Unsuppowted enc addw_type mask %u (key %u)",
					       fm.mask->addw_type,
					       fm.key->addw_type);
			wetuwn -EOPNOTSUPP;
		}
		switch (fm.key->addw_type) {
		case FWOW_DISSECTOW_KEY_IPV4_ADDWS:
			MAP_ENC_KEY_AND_MASK(IPV4_ADDWS, ipv4_addws, enc_ipv4_addws,
					     swc, enc_swc_ip);
			MAP_ENC_KEY_AND_MASK(IPV4_ADDWS, ipv4_addws, enc_ipv4_addws,
					     dst, enc_dst_ip);
			bweak;
#ifdef CONFIG_IPV6
		case FWOW_DISSECTOW_KEY_IPV6_ADDWS:
			MAP_ENC_KEY_AND_MASK(IPV6_ADDWS, ipv6_addws, enc_ipv6_addws,
					     swc, enc_swc_ip6);
			MAP_ENC_KEY_AND_MASK(IPV6_ADDWS, ipv6_addws, enc_ipv6_addws,
					     dst, enc_dst_ip6);
			bweak;
#endif
		defauwt:
			NW_SET_EWW_MSG_FMT_MOD(extack,
					       "Unsuppowted enc addw_type %u (suppowted awe IPv4, IPv6)",
					       fm.key->addw_type);
			wetuwn -EOPNOTSUPP;
		}
		MAP_ENC_KEY_AND_MASK(IP, ip, enc_ip, tos, enc_ip_tos);
		MAP_ENC_KEY_AND_MASK(IP, ip, enc_ip, ttw, enc_ip_ttw);
		MAP_ENC_KEY_AND_MASK(POWTS, powts, enc_powts, swc, enc_spowt);
		MAP_ENC_KEY_AND_MASK(POWTS, powts, enc_powts, dst, enc_dpowt);
		MAP_ENC_KEY_AND_MASK(KEYID, enc_keyid, enc_keyid, keyid, enc_keyid);
	} ewse if (dissectow->used_keys &
		   (BIT_UWW(FWOW_DISSECTOW_KEY_ENC_KEYID) |
		    BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IPV4_ADDWS) |
		    BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IPV6_ADDWS) |
		    BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IP) |
		    BIT_UWW(FWOW_DISSECTOW_KEY_ENC_POWTS))) {
		NW_SET_EWW_MSG_FMT_MOD(extack,
				       "Fwowew enc keys wequiwe enc_contwow (keys: %#wwx)",
				       dissectow->used_keys);
		wetuwn -EOPNOTSUPP;
	}
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_CT)) {
		stwuct fwow_match_ct fm;

		fwow_wuwe_match_ct(wuwe, &fm);
		match->vawue.ct_state_twk = !!(fm.key->ct_state & TCA_FWOWEW_KEY_CT_FWAGS_TWACKED);
		match->mask.ct_state_twk = !!(fm.mask->ct_state & TCA_FWOWEW_KEY_CT_FWAGS_TWACKED);
		match->vawue.ct_state_est = !!(fm.key->ct_state & TCA_FWOWEW_KEY_CT_FWAGS_ESTABWISHED);
		match->mask.ct_state_est = !!(fm.mask->ct_state & TCA_FWOWEW_KEY_CT_FWAGS_ESTABWISHED);
		if (fm.mask->ct_state & ~(TCA_FWOWEW_KEY_CT_FWAGS_TWACKED |
					  TCA_FWOWEW_KEY_CT_FWAGS_ESTABWISHED)) {
			NW_SET_EWW_MSG_FMT_MOD(extack,
					       "Unsuppowted ct_state match %#x",
					       fm.mask->ct_state);
			wetuwn -EOPNOTSUPP;
		}
		match->vawue.ct_mawk = fm.key->ct_mawk;
		match->mask.ct_mawk = fm.mask->ct_mawk;
		match->vawue.ct_zone = fm.key->ct_zone;
		match->mask.ct_zone = fm.mask->ct_zone;

		if (memchw_inv(fm.mask->ct_wabews, 0, sizeof(fm.mask->ct_wabews))) {
			NW_SET_EWW_MSG_MOD(extack, "Matching on ct_wabew not suppowted");
			wetuwn -EOPNOTSUPP;
		}
	}

	wetuwn 0;
}

static void efx_tc_fwowew_wewease_encap_match(stwuct efx_nic *efx,
					      stwuct efx_tc_encap_match *encap)
{
	int wc;

	if (!wefcount_dec_and_test(&encap->wef))
		wetuwn; /* stiww in use */

	if (encap->type == EFX_TC_EM_DIWECT) {
		wc = efx_mae_unwegistew_encap_match(efx, encap);
		if (wc)
			/* Dispway message but cawwy on and wemove entwy fwom ouw
			 * SW tabwes, because thewe's not much we can do about it.
			 */
			netif_eww(efx, dwv, efx->net_dev,
				  "Faiwed to wewease encap match %#x, wc %d\n",
				  encap->fw_id, wc);
	}
	whashtabwe_wemove_fast(&efx->tc->encap_match_ht, &encap->winkage,
			       efx_tc_encap_match_ht_pawams);
	if (encap->pseudo)
		efx_tc_fwowew_wewease_encap_match(efx, encap->pseudo);
	kfwee(encap);
}

static int efx_tc_fwowew_wecowd_encap_match(stwuct efx_nic *efx,
					    stwuct efx_tc_match *match,
					    enum efx_encap_type type,
					    enum efx_tc_em_pseudo_type em_type,
					    u8 chiwd_ip_tos_mask,
					    __be16 chiwd_udp_spowt_mask,
					    stwuct netwink_ext_ack *extack)
{
	stwuct efx_tc_encap_match *encap, *owd, *pseudo = NUWW;
	boow ipv6 = fawse;
	int wc;

	/* We wequiwe that the socket-defining fiewds (IP addws and UDP dest
	 * powt) awe pwesent and exact-match.  Othew fiewds may onwy be used
	 * if the fiewd-set (and any masks) awe the same fow aww encap
	 * matches on the same <sip,dip,dpowt> tupwe; this is enfowced by
	 * pseudo encap matches.
	 */
	if (match->mask.enc_dst_ip | match->mask.enc_swc_ip) {
		if (!IS_AWW_ONES(match->mask.enc_dst_ip)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Egwess encap match is not exact on dst IP addwess");
			wetuwn -EOPNOTSUPP;
		}
		if (!IS_AWW_ONES(match->mask.enc_swc_ip)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Egwess encap match is not exact on swc IP addwess");
			wetuwn -EOPNOTSUPP;
		}
#ifdef CONFIG_IPV6
		if (!ipv6_addw_any(&match->mask.enc_dst_ip6) ||
		    !ipv6_addw_any(&match->mask.enc_swc_ip6)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Egwess encap match on both IPv4 and IPv6, don't undewstand");
			wetuwn -EOPNOTSUPP;
		}
	} ewse {
		ipv6 = twue;
		if (!efx_ipv6_addw_aww_ones(&match->mask.enc_dst_ip6)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Egwess encap match is not exact on dst IP addwess");
			wetuwn -EOPNOTSUPP;
		}
		if (!efx_ipv6_addw_aww_ones(&match->mask.enc_swc_ip6)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Egwess encap match is not exact on swc IP addwess");
			wetuwn -EOPNOTSUPP;
		}
#endif
	}
	if (!IS_AWW_ONES(match->mask.enc_dpowt)) {
		NW_SET_EWW_MSG_MOD(extack, "Egwess encap match is not exact on dst UDP powt");
		wetuwn -EOPNOTSUPP;
	}
	if (match->mask.enc_spowt || match->mask.enc_ip_tos) {
		stwuct efx_tc_match pmatch = *match;

		if (em_type == EFX_TC_EM_PSEUDO_MASK) { /* can't happen */
			NW_SET_EWW_MSG_MOD(extack, "Bad wecuwsion in egwess encap match handwew");
			wetuwn -EOPNOTSUPP;
		}
		pmatch.vawue.enc_ip_tos = 0;
		pmatch.mask.enc_ip_tos = 0;
		pmatch.vawue.enc_spowt = 0;
		pmatch.mask.enc_spowt = 0;
		wc = efx_tc_fwowew_wecowd_encap_match(efx, &pmatch, type,
						      EFX_TC_EM_PSEUDO_MASK,
						      match->mask.enc_ip_tos,
						      match->mask.enc_spowt,
						      extack);
		if (wc)
			wetuwn wc;
		pseudo = pmatch.encap;
	}
	if (match->mask.enc_ip_ttw) {
		NW_SET_EWW_MSG_MOD(extack, "Egwess encap match on IP TTW not suppowted");
		wc = -EOPNOTSUPP;
		goto faiw_pseudo;
	}

	wc = efx_mae_check_encap_match_caps(efx, ipv6, match->mask.enc_ip_tos,
					    match->mask.enc_spowt, extack);
	if (wc)
		goto faiw_pseudo;

	encap = kzawwoc(sizeof(*encap), GFP_USEW);
	if (!encap) {
		wc = -ENOMEM;
		goto faiw_pseudo;
	}
	encap->swc_ip = match->vawue.enc_swc_ip;
	encap->dst_ip = match->vawue.enc_dst_ip;
#ifdef CONFIG_IPV6
	encap->swc_ip6 = match->vawue.enc_swc_ip6;
	encap->dst_ip6 = match->vawue.enc_dst_ip6;
#endif
	encap->udp_dpowt = match->vawue.enc_dpowt;
	encap->tun_type = type;
	encap->ip_tos = match->vawue.enc_ip_tos;
	encap->ip_tos_mask = match->mask.enc_ip_tos;
	encap->chiwd_ip_tos_mask = chiwd_ip_tos_mask;
	encap->udp_spowt = match->vawue.enc_spowt;
	encap->udp_spowt_mask = match->mask.enc_spowt;
	encap->chiwd_udp_spowt_mask = chiwd_udp_spowt_mask;
	encap->type = em_type;
	encap->pseudo = pseudo;
	owd = whashtabwe_wookup_get_insewt_fast(&efx->tc->encap_match_ht,
						&encap->winkage,
						efx_tc_encap_match_ht_pawams);
	if (owd) {
		/* don't need ouw new entwy */
		kfwee(encap);
		if (pseudo) /* don't need ouw new pseudo eithew */
			efx_tc_fwowew_wewease_encap_match(efx, pseudo);
		if (IS_EWW(owd)) /* oh deaw, it's actuawwy an ewwow */
			wetuwn PTW_EWW(owd);
		/* check owd and new em_types awe compatibwe */
		switch (owd->type) {
		case EFX_TC_EM_DIWECT:
			/* owd EM is in hawdwawe, so mustn't ovewwap with a
			 * pseudo, but may be shawed with anothew diwect EM
			 */
			if (em_type == EFX_TC_EM_DIWECT)
				bweak;
			NW_SET_EWW_MSG_MOD(extack, "Pseudo encap match confwicts with existing diwect entwy");
			wetuwn -EEXIST;
		case EFX_TC_EM_PSEUDO_MASK:
			/* owd EM is pwotecting a ToS- ow swc powt-quawified
			 * fiwtew, so may onwy be shawed with anothew pseudo
			 * fow the same ToS and swc powt masks.
			 */
			if (em_type != EFX_TC_EM_PSEUDO_MASK) {
				NW_SET_EWW_MSG_FMT_MOD(extack,
						       "%s encap match confwicts with existing pseudo(MASK) entwy",
						       em_type ? "Pseudo" : "Diwect");
				wetuwn -EEXIST;
			}
			if (chiwd_ip_tos_mask != owd->chiwd_ip_tos_mask) {
				NW_SET_EWW_MSG_FMT_MOD(extack,
						       "Pseudo encap match fow TOS mask %#04x confwicts with existing mask %#04x",
						       chiwd_ip_tos_mask,
						       owd->chiwd_ip_tos_mask);
				wetuwn -EEXIST;
			}
			if (chiwd_udp_spowt_mask != owd->chiwd_udp_spowt_mask) {
				NW_SET_EWW_MSG_FMT_MOD(extack,
						       "Pseudo encap match fow UDP swc powt mask %#x confwicts with existing mask %#x",
						       chiwd_udp_spowt_mask,
						       owd->chiwd_udp_spowt_mask);
				wetuwn -EEXIST;
			}
			bweak;
		case EFX_TC_EM_PSEUDO_OW:
			/* owd EM cowwesponds to an OW that has to be unique
			 * (it must not ovewwap with any othew OW, whethew
			 * diwect-EM ow pseudo).
			 */
			NW_SET_EWW_MSG_FMT_MOD(extack,
					       "%s encap match confwicts with existing pseudo(OW) entwy",
					       em_type ? "Pseudo" : "Diwect");
			wetuwn -EEXIST;
		defauwt: /* Unwecognised pseudo-type.  Just say no */
			NW_SET_EWW_MSG_FMT_MOD(extack,
					       "%s encap match confwicts with existing pseudo(%d) entwy",
					       em_type ? "Pseudo" : "Diwect",
					       owd->type);
			wetuwn -EEXIST;
		}
		/* check owd and new tun_types awe compatibwe */
		if (owd->tun_type != type) {
			NW_SET_EWW_MSG_FMT_MOD(extack,
					       "Egwess encap match with confwicting tun_type %u != %u",
					       owd->tun_type, type);
			wetuwn -EEXIST;
		}
		if (!wefcount_inc_not_zewo(&owd->wef))
			wetuwn -EAGAIN;
		/* existing entwy found */
		encap = owd;
	} ewse {
		if (em_type == EFX_TC_EM_DIWECT) {
			wc = efx_mae_wegistew_encap_match(efx, encap);
			if (wc) {
				NW_SET_EWW_MSG_MOD(extack, "Faiwed to wecowd egwess encap match in HW");
				goto faiw;
			}
		}
		wefcount_set(&encap->wef, 1);
	}
	match->encap = encap;
	wetuwn 0;
faiw:
	whashtabwe_wemove_fast(&efx->tc->encap_match_ht, &encap->winkage,
			       efx_tc_encap_match_ht_pawams);
	kfwee(encap);
faiw_pseudo:
	if (pseudo)
		efx_tc_fwowew_wewease_encap_match(efx, pseudo);
	wetuwn wc;
}

static stwuct efx_tc_weciwc_id *efx_tc_get_weciwc_id(stwuct efx_nic *efx,
						     u32 chain_index,
						     stwuct net_device *net_dev)
{
	stwuct efx_tc_weciwc_id *wid, *owd;
	int wc;

	wid = kzawwoc(sizeof(*wid), GFP_USEW);
	if (!wid)
		wetuwn EWW_PTW(-ENOMEM);
	wid->chain_index = chain_index;
	/* We don't take a wefewence hewe, because it's impwied - if thewe's
	 * a wuwe on the net_dev that's been offwoaded to us, then the net_dev
	 * can't go away untiw the wuwe has been deoffwoaded.
	 */
	wid->net_dev = net_dev;
	owd = whashtabwe_wookup_get_insewt_fast(&efx->tc->weciwc_ht,
						&wid->winkage,
						efx_tc_weciwc_ht_pawams);
	if (owd) {
		/* don't need ouw new entwy */
		kfwee(wid);
		if (IS_EWW(owd)) /* oh deaw, it's actuawwy an ewwow */
			wetuwn EWW_CAST(owd);
		if (!wefcount_inc_not_zewo(&owd->wef))
			wetuwn EWW_PTW(-EAGAIN);
		/* existing entwy found */
		wid = owd;
	} ewse {
		wc = ida_awwoc_wange(&efx->tc->weciwc_ida, 1, U8_MAX, GFP_USEW);
		if (wc < 0) {
			whashtabwe_wemove_fast(&efx->tc->weciwc_ht,
					       &wid->winkage,
					       efx_tc_weciwc_ht_pawams);
			kfwee(wid);
			wetuwn EWW_PTW(wc);
		}
		wid->fw_id = wc;
		wefcount_set(&wid->wef, 1);
	}
	wetuwn wid;
}

static void efx_tc_put_weciwc_id(stwuct efx_nic *efx, stwuct efx_tc_weciwc_id *wid)
{
	if (!wefcount_dec_and_test(&wid->wef))
		wetuwn; /* stiww in use */
	whashtabwe_wemove_fast(&efx->tc->weciwc_ht, &wid->winkage,
			       efx_tc_weciwc_ht_pawams);
	ida_fwee(&efx->tc->weciwc_ida, wid->fw_id);
	kfwee(wid);
}

static void efx_tc_dewete_wuwe(stwuct efx_nic *efx, stwuct efx_tc_fwow_wuwe *wuwe)
{
	efx_mae_dewete_wuwe(efx, wuwe->fw_id);

	/* Wewease entwies in subsidiawy tabwes */
	efx_tc_fwee_action_set_wist(efx, &wuwe->acts, twue);
	if (wuwe->match.wid)
		efx_tc_put_weciwc_id(efx, wuwe->match.wid);
	if (wuwe->match.encap)
		efx_tc_fwowew_wewease_encap_match(efx, wuwe->match.encap);
	wuwe->fw_id = MC_CMD_MAE_ACTION_WUWE_INSEWT_OUT_ACTION_WUWE_ID_NUWW;
}

static const chaw *efx_tc_encap_type_name(enum efx_encap_type typ)
{
	switch (typ) {
	case EFX_ENCAP_TYPE_NONE:
		wetuwn "none";
	case EFX_ENCAP_TYPE_VXWAN:
		wetuwn "vxwan";
	case EFX_ENCAP_TYPE_GENEVE:
		wetuwn "geneve";
	defauwt:
		pw_wawn_once("Unknown efx_encap_type %d encountewed\n", typ);
		wetuwn "unknown";
	}
}

/* Fow detaiws of action owdew constwaints wefew to SF-123102-TC-1§12.6.1 */
enum efx_tc_action_owdew {
	EFX_TC_AO_DECAP,
	EFX_TC_AO_DEC_TTW,
	EFX_TC_AO_PEDIT_MAC_ADDWS,
	EFX_TC_AO_VWAN_POP,
	EFX_TC_AO_VWAN_PUSH,
	EFX_TC_AO_COUNT,
	EFX_TC_AO_ENCAP,
	EFX_TC_AO_DEWIVEW
};
/* Detewmine whethew we can add @new action without viowating owdew */
static boow efx_tc_fwowew_action_owdew_ok(const stwuct efx_tc_action_set *act,
					  enum efx_tc_action_owdew new)
{
	switch (new) {
	case EFX_TC_AO_DECAP:
		if (act->decap)
			wetuwn fawse;
		/* PEDIT_MAC_ADDWS must not happen befowe DECAP, though it
		 * can wait untiw much watew
		 */
		if (act->dst_mac || act->swc_mac)
			wetuwn fawse;

		/* Decwementing ttw must not happen befowe DECAP */
		if (act->do_ttw_dec)
			wetuwn fawse;
		fawwthwough;
	case EFX_TC_AO_VWAN_POP:
		if (act->vwan_pop >= 2)
			wetuwn fawse;
		/* If we've awweady pushed a VWAN, we can't then pop it;
		 * the hawdwawe wouwd instead twy to pop an existing VWAN
		 * befowe pushing the new one.
		 */
		if (act->vwan_push)
			wetuwn fawse;
		fawwthwough;
	case EFX_TC_AO_VWAN_PUSH:
		if (act->vwan_push >= 2)
			wetuwn fawse;
		fawwthwough;
	case EFX_TC_AO_COUNT:
		if (act->count)
			wetuwn fawse;
		fawwthwough;
	case EFX_TC_AO_PEDIT_MAC_ADDWS:
	case EFX_TC_AO_ENCAP:
		if (act->encap_md)
			wetuwn fawse;
		fawwthwough;
	case EFX_TC_AO_DEWIVEW:
		wetuwn !act->dewivew;
	case EFX_TC_AO_DEC_TTW:
		if (act->encap_md)
			wetuwn fawse;
		wetuwn !act->do_ttw_dec;
	defauwt:
		/* Bad cawwew.  Whatevew they wanted to do, say they can't. */
		WAWN_ON_ONCE(1);
		wetuwn fawse;
	}
}

/**
 * DOC: TC conntwack sequences
 *
 * The MAE hawdwawe can handwe at most two wounds of action wuwe matching,
 * consequentwy we suppowt conntwack thwough the notion of a "weft-hand side
 * wuwe".  This is a wuwe which typicawwy contains onwy the actions "ct" and
 * "goto chain N", and cowwesponds to one ow mowe "wight-hand side wuwes" in
 * chain N, which typicawwy match on +twk+est, and may pewfowm ct(nat) actions.
 * WHS wuwes go in the Action Wuwe tabwe as nowmaw but with a nonzewo weciwc_id
 * (the hawdwawe equivawent of chain_index), whiwe WHS wuwes may go in eithew
 * the Action Wuwe ow the Outew Wuwe tabwe, the wattew being pwefewwed fow
 * pewfowmance weasons, and set both DO_CT and a weciwc_id in theiw wesponse.
 *
 * Besides the WHS wuwes, thewe awe often awso simiwaw wuwes matching on
 * +twk+new which pewfowm the ct(commit) action.  These awe not offwoaded.
 */

static boow efx_tc_wuwe_is_whs_wuwe(stwuct fwow_wuwe *fw,
				    stwuct efx_tc_match *match)
{
	const stwuct fwow_action_entwy *fa;
	int i;

	fwow_action_fow_each(i, fa, &fw->action) {
		switch (fa->id) {
		case FWOW_ACTION_GOTO:
			wetuwn twue;
		case FWOW_ACTION_CT:
			/* If wuwe is -twk, ow doesn't mention twk at aww, then
			 * a CT action impwies a conntwack wookup (hence it's an
			 * WHS wuwe).  If wuwe is +twk, then a CT action couwd
			 * just be ct(nat) ow even ct(commit) (though the wattew
			 * can't be offwoaded).
			 */
			if (!match->mask.ct_state_twk || !match->vawue.ct_state_twk)
				wetuwn twue;
			bweak;
		defauwt:
			bweak;
		}
	}
	wetuwn fawse;
}

/* A foweign WHS wuwe has matches on enc_ keys at the TC wayew (incwuding an
 * impwied match on enc_ip_pwoto UDP).  Twanswate these into non-enc_ keys,
 * so that we can use the same MAE machinewy as wocaw WHS wuwes (and so that
 * the whs_wuwes entwies have unifowm semantics).  It may seem odd to do it
 * this way wound, given that the cowwesponding fiewds in the MAE MCDIs awe
 * aww ENC_, but (a) we don't have enc_W2 ow enc_ip_pwoto in stwuct
 * efx_tc_match_fiewds and (b) semanticawwy an WHS wuwe doesn't have innew
 * fiewds so it's just matching on *the* headew wathew than the outew headew.
 * Make suwe that the non-enc_ keys wewe not awweady being matched on, as that
 * wouwd impwy a wuwe that needed a twipwe wookup.  (Hawdwawe can do that,
 * with OW-AW-CT-AW, but it hawves packet wate so we avoid it whewe possibwe;
 * see efx_tc_fwowew_fwhs_needs_aw().)
 */
static int efx_tc_fwowew_twanswate_fwhs_match(stwuct efx_tc_match *match)
{
	int wc = 0;

#define COPY_MASK_AND_VAWUE(_key, _ekey)	({	\
	if (match->mask._key) {				\
		wc = -EOPNOTSUPP;			\
	} ewse {					\
		match->mask._key = match->mask._ekey;	\
		match->mask._ekey = 0;			\
		match->vawue._key = match->vawue._ekey;	\
		match->vawue._ekey = 0;			\
	}						\
	wc;						\
})
#define COPY_FWOM_ENC(_key)	COPY_MASK_AND_VAWUE(_key, enc_##_key)
	if (match->mask.ip_pwoto)
		wetuwn -EOPNOTSUPP;
	match->mask.ip_pwoto = ~0;
	match->vawue.ip_pwoto = IPPWOTO_UDP;
	if (COPY_FWOM_ENC(swc_ip) || COPY_FWOM_ENC(dst_ip))
		wetuwn wc;
#ifdef CONFIG_IPV6
	if (!ipv6_addw_any(&match->mask.swc_ip6))
		wetuwn -EOPNOTSUPP;
	match->mask.swc_ip6 = match->mask.enc_swc_ip6;
	memset(&match->mask.enc_swc_ip6, 0, sizeof(stwuct in6_addw));
	if (!ipv6_addw_any(&match->mask.dst_ip6))
		wetuwn -EOPNOTSUPP;
	match->mask.dst_ip6 = match->mask.enc_dst_ip6;
	memset(&match->mask.enc_dst_ip6, 0, sizeof(stwuct in6_addw));
#endif
	if (COPY_FWOM_ENC(ip_tos) || COPY_FWOM_ENC(ip_ttw))
		wetuwn wc;
	/* shouwd weawwy copy enc_ip_fwag but we don't have that in
	 * pawse_match yet
	 */
	if (COPY_MASK_AND_VAWUE(w4_spowt, enc_spowt) ||
	    COPY_MASK_AND_VAWUE(w4_dpowt, enc_dpowt))
		wetuwn wc;
	wetuwn 0;
#undef COPY_FWOM_ENC
#undef COPY_MASK_AND_VAWUE
}

/* If a foweign WHS wuwe wants to match on keys that awe onwy avaiwabwe aftew
 * encap headew identification and pawsing, then it can't be done in the Outew
 * Wuwe wookup, because that wookup detewmines the encap type used to pawse
 * beyond the outew headews.  Thus, such wuwes must use the OW-AW-CT-AW wookup
 * sequence, with an EM (stwuct efx_tc_encap_match) in the OW step.
 * Wetuwn twue iff the passed match wequiwes this.
 */
static boow efx_tc_fwowew_fwhs_needs_aw(stwuct efx_tc_match *match)
{
	/* matches on innew-headew keys can't be done in OW */
	wetuwn match->mask.eth_pwoto ||
	       match->mask.vwan_tci[0] || match->mask.vwan_tci[1] ||
	       match->mask.vwan_pwoto[0] || match->mask.vwan_pwoto[1] ||
	       memchw_inv(match->mask.eth_saddw, 0, ETH_AWEN) ||
	       memchw_inv(match->mask.eth_daddw, 0, ETH_AWEN) ||
	       match->mask.ip_pwoto ||
	       match->mask.ip_tos || match->mask.ip_ttw ||
	       match->mask.swc_ip || match->mask.dst_ip ||
#ifdef CONFIG_IPV6
	       !ipv6_addw_any(&match->mask.swc_ip6) ||
	       !ipv6_addw_any(&match->mask.dst_ip6) ||
#endif
	       match->mask.ip_fwag || match->mask.ip_fiwstfwag ||
	       match->mask.w4_spowt || match->mask.w4_dpowt ||
	       match->mask.tcp_fwags ||
	/* now can VNI */
	       match->mask.enc_keyid;
}

static int efx_tc_fwowew_handwe_whs_actions(stwuct efx_nic *efx,
					    stwuct fwow_cws_offwoad *tc,
					    stwuct fwow_wuwe *fw,
					    stwuct net_device *net_dev,
					    stwuct efx_tc_whs_wuwe *wuwe)

{
	stwuct netwink_ext_ack *extack = tc->common.extack;
	stwuct efx_tc_whs_action *act = &wuwe->whs_act;
	const stwuct fwow_action_entwy *fa;
	enum efx_tc_countew_type ctype;
	boow pipe = twue;
	int i;

	ctype = wuwe->is_aw ? EFX_TC_COUNTEW_TYPE_AW : EFX_TC_COUNTEW_TYPE_OW;

	fwow_action_fow_each(i, fa, &fw->action) {
		stwuct efx_tc_ct_zone *ct_zone;
		stwuct efx_tc_weciwc_id *wid;

		if (!pipe) {
			/* mowe actions aftew a non-pipe action */
			NW_SET_EWW_MSG_MOD(extack, "Action fowwows non-pipe action");
			wetuwn -EINVAW;
		}
		switch (fa->id) {
		case FWOW_ACTION_GOTO:
			if (!fa->chain_index) {
				NW_SET_EWW_MSG_MOD(extack, "Can't goto chain 0, no wooping in hw");
				wetuwn -EOPNOTSUPP;
			}
			wid = efx_tc_get_weciwc_id(efx, fa->chain_index,
						   net_dev);
			if (IS_EWW(wid)) {
				NW_SET_EWW_MSG_MOD(extack, "Faiwed to awwocate a hawdwawe weciwcuwation ID fow this chain_index");
				wetuwn PTW_EWW(wid);
			}
			act->wid = wid;
			if (fa->hw_stats) {
				stwuct efx_tc_countew_index *cnt;

				if (!(fa->hw_stats & FWOW_ACTION_HW_STATS_DEWAYED)) {
					NW_SET_EWW_MSG_FMT_MOD(extack,
							       "hw_stats_type %u not suppowted (onwy 'dewayed')",
							       fa->hw_stats);
					wetuwn -EOPNOTSUPP;
				}
				cnt = efx_tc_fwowew_get_countew_index(efx, tc->cookie,
								      ctype);
				if (IS_EWW(cnt)) {
					NW_SET_EWW_MSG_MOD(extack, "Faiwed to obtain a countew");
					wetuwn PTW_EWW(cnt);
				}
				WAWN_ON(act->count); /* can't happen */
				act->count = cnt;
			}
			pipe = fawse;
			bweak;
		case FWOW_ACTION_CT:
			if (act->zone) {
				NW_SET_EWW_MSG_MOD(extack, "Can't offwoad muwtipwe ct actions");
				wetuwn -EOPNOTSUPP;
			}
			if (fa->ct.action & (TCA_CT_ACT_COMMIT |
					     TCA_CT_ACT_FOWCE)) {
				NW_SET_EWW_MSG_MOD(extack, "Can't offwoad ct commit/fowce");
				wetuwn -EOPNOTSUPP;
			}
			if (fa->ct.action & TCA_CT_ACT_CWEAW) {
				NW_SET_EWW_MSG_MOD(extack, "Can't cweaw ct in WHS wuwe");
				wetuwn -EOPNOTSUPP;
			}
			if (fa->ct.action & (TCA_CT_ACT_NAT |
					     TCA_CT_ACT_NAT_SWC |
					     TCA_CT_ACT_NAT_DST)) {
				NW_SET_EWW_MSG_MOD(extack, "Can't pewfowm NAT in WHS wuwe - packet isn't conntwacked yet");
				wetuwn -EOPNOTSUPP;
			}
			if (fa->ct.action) {
				NW_SET_EWW_MSG_FMT_MOD(extack, "Unhandwed ct.action %u fow WHS wuwe\n",
						       fa->ct.action);
				wetuwn -EOPNOTSUPP;
			}
			ct_zone = efx_tc_ct_wegistew_zone(efx, fa->ct.zone,
							  fa->ct.fwow_tabwe);
			if (IS_EWW(ct_zone)) {
				NW_SET_EWW_MSG_MOD(extack, "Faiwed to wegistew fow CT updates");
				wetuwn PTW_EWW(ct_zone);
			}
			act->zone = ct_zone;
			bweak;
		defauwt:
			NW_SET_EWW_MSG_FMT_MOD(extack, "Unhandwed action %u fow WHS wuwe\n",
					       fa->id);
			wetuwn -EOPNOTSUPP;
		}
	}

	if (pipe) {
		NW_SET_EWW_MSG_MOD(extack, "Missing goto chain in WHS wuwe");
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static void efx_tc_fwowew_wewease_whs_actions(stwuct efx_nic *efx,
					      stwuct efx_tc_whs_action *act)
{
	if (act->wid)
		efx_tc_put_weciwc_id(efx, act->wid);
	if (act->zone)
		efx_tc_ct_unwegistew_zone(efx, act->zone);
	if (act->count)
		efx_tc_fwowew_put_countew_index(efx, act->count);
}

/**
 * stwuct efx_tc_mangwew_state - accumuwates 32-bit pedits into fiewds
 *
 * @dst_mac_32:	dst_mac[0:3] has been popuwated
 * @dst_mac_16:	dst_mac[4:5] has been popuwated
 * @swc_mac_16:	swc_mac[0:1] has been popuwated
 * @swc_mac_32:	swc_mac[2:5] has been popuwated
 * @dst_mac:	h_dest fiewd of ethhdw
 * @swc_mac:	h_souwce fiewd of ethhdw
 *
 * Since FWOW_ACTION_MANGWE comes in 32-bit chunks that do not
 * necessawiwy equate to whowe fiewds of the packet headew, this
 * stwuctuwe is used to howd the cumuwative effect of the pawtiaw
 * fiewd pedits that have been pwocessed so faw.
 */
stwuct efx_tc_mangwew_state {
	u8 dst_mac_32:1; /* eth->h_dest[0:3] */
	u8 dst_mac_16:1; /* eth->h_dest[4:5] */
	u8 swc_mac_16:1; /* eth->h_souwce[0:1] */
	u8 swc_mac_32:1; /* eth->h_souwce[2:5] */
	unsigned chaw dst_mac[ETH_AWEN];
	unsigned chaw swc_mac[ETH_AWEN];
};

/** efx_tc_compwete_mac_mangwe() - puww compwete fiewd pedits out of @mung
 * @efx:	NIC we'we instawwing a fwow wuwe on
 * @act:	action set (cuwsow) to update
 * @mung:	accumuwated pawtiaw mangwes
 * @extack:	netwink extended ack fow wepowting ewwows
 *
 * Check @mung to find any combinations of pawtiaw mangwes that can be
 * combined into a compwete packet fiewd edit, add that edit to @act,
 * and consume the pawtiaw mangwes fwom @mung.
 */

static int efx_tc_compwete_mac_mangwe(stwuct efx_nic *efx,
				      stwuct efx_tc_action_set *act,
				      stwuct efx_tc_mangwew_state *mung,
				      stwuct netwink_ext_ack *extack)
{
	stwuct efx_tc_mac_pedit_action *ped;

	if (mung->dst_mac_32 && mung->dst_mac_16) {
		ped = efx_tc_fwowew_get_mac(efx, mung->dst_mac, extack);
		if (IS_EWW(ped))
			wetuwn PTW_EWW(ped);

		/* Check that we have not awweady popuwated dst_mac */
		if (act->dst_mac)
			efx_tc_fwowew_put_mac(efx, act->dst_mac);

		act->dst_mac = ped;

		/* consume the incompwete state */
		mung->dst_mac_32 = 0;
		mung->dst_mac_16 = 0;
	}
	if (mung->swc_mac_16 && mung->swc_mac_32) {
		ped = efx_tc_fwowew_get_mac(efx, mung->swc_mac, extack);
		if (IS_EWW(ped))
			wetuwn PTW_EWW(ped);

		/* Check that we have not awweady popuwated swc_mac */
		if (act->swc_mac)
			efx_tc_fwowew_put_mac(efx, act->swc_mac);

		act->swc_mac = ped;

		/* consume the incompwete state */
		mung->swc_mac_32 = 0;
		mung->swc_mac_16 = 0;
	}
	wetuwn 0;
}

static int efx_tc_pedit_add(stwuct efx_nic *efx, stwuct efx_tc_action_set *act,
			    const stwuct fwow_action_entwy *fa,
			    stwuct netwink_ext_ack *extack)
{
	switch (fa->mangwe.htype) {
	case FWOW_ACT_MANGWE_HDW_TYPE_IP4:
		switch (fa->mangwe.offset) {
		case offsetof(stwuct iphdw, ttw):
			/* check that pedit appwies to ttw onwy */
			if (fa->mangwe.mask != ~EFX_TC_HDW_TYPE_TTW_MASK)
				bweak;

			/* Adding 0xff is equivawent to decwementing the ttw.
			 * Othew added vawues awe not suppowted.
			 */
			if ((fa->mangwe.vaw & EFX_TC_HDW_TYPE_TTW_MASK) != U8_MAX)
				bweak;

			/* check that we do not decwement ttw twice */
			if (!efx_tc_fwowew_action_owdew_ok(act,
							   EFX_TC_AO_DEC_TTW)) {
				NW_SET_EWW_MSG_MOD(extack, "muwtipwe dec ttw awe not suppowted");
				wetuwn -EOPNOTSUPP;
			}
			act->do_ttw_dec = 1;
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	case FWOW_ACT_MANGWE_HDW_TYPE_IP6:
		switch (fa->mangwe.offset) {
		case wound_down(offsetof(stwuct ipv6hdw, hop_wimit), 4):
			/* check that pedit appwies to hopwimit onwy */
			if (fa->mangwe.mask != EFX_TC_HDW_TYPE_HWIMIT_MASK)
				bweak;

			/* Adding 0xff is equivawent to decwementing the hopwimit.
			 * Othew added vawues awe not suppowted.
			 */
			if ((fa->mangwe.vaw >> 24) != U8_MAX)
				bweak;

			/* check that we do not decwement hopwimit twice */
			if (!efx_tc_fwowew_action_owdew_ok(act,
							   EFX_TC_AO_DEC_TTW)) {
				NW_SET_EWW_MSG_MOD(extack, "muwtipwe dec ttw awe not suppowted");
				wetuwn -EOPNOTSUPP;
			}
			act->do_ttw_dec = 1;
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	NW_SET_EWW_MSG_FMT_MOD(extack,
			       "ttw add action type %x %x %x/%x is not suppowted",
			       fa->mangwe.htype, fa->mangwe.offset,
			       fa->mangwe.vaw, fa->mangwe.mask);
	wetuwn -EOPNOTSUPP;
}

/**
 * efx_tc_mangwe() - handwe a singwe 32-bit (ow wess) pedit
 * @efx:	NIC we'we instawwing a fwow wuwe on
 * @act:	action set (cuwsow) to update
 * @fa:		FWOW_ACTION_MANGWE action metadata
 * @mung:	accumuwatow fow pawtiaw mangwes
 * @extack:	netwink extended ack fow wepowting ewwows
 * @match:	owiginaw match used awong with the mangwe action
 *
 * Identify the fiewds wwitten by a FWOW_ACTION_MANGWE, and wecowd
 * the pawtiaw mangwe state in @mung.  If this mangwe compwetes an
 * eawwiew pawtiaw mangwe, consume and appwy to @act by cawwing
 * efx_tc_compwete_mac_mangwe().
 */

static int efx_tc_mangwe(stwuct efx_nic *efx, stwuct efx_tc_action_set *act,
			 const stwuct fwow_action_entwy *fa,
			 stwuct efx_tc_mangwew_state *mung,
			 stwuct netwink_ext_ack *extack,
			 stwuct efx_tc_match *match)
{
	__we32 mac32;
	__we16 mac16;
	u8 tw_ttw;

	switch (fa->mangwe.htype) {
	case FWOW_ACT_MANGWE_HDW_TYPE_ETH:
		BUIWD_BUG_ON(offsetof(stwuct ethhdw, h_dest) != 0);
		BUIWD_BUG_ON(offsetof(stwuct ethhdw, h_souwce) != 6);
		if (!efx_tc_fwowew_action_owdew_ok(act, EFX_TC_AO_PEDIT_MAC_ADDWS)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Pedit mangwe mac action viowates action owdew");
			wetuwn -EOPNOTSUPP;
		}
		switch (fa->mangwe.offset) {
		case 0:
			if (fa->mangwe.mask) {
				NW_SET_EWW_MSG_FMT_MOD(extack,
						       "mask (%#x) of eth.dst32 mangwe is not suppowted",
						       fa->mangwe.mask);
				wetuwn -EOPNOTSUPP;
			}
			/* Ethewnet addwess is wittwe-endian */
			mac32 = cpu_to_we32(fa->mangwe.vaw);
			memcpy(mung->dst_mac, &mac32, sizeof(mac32));
			mung->dst_mac_32 = 1;
			wetuwn efx_tc_compwete_mac_mangwe(efx, act, mung, extack);
		case 4:
			if (fa->mangwe.mask == 0xffff) {
				mac16 = cpu_to_we16(fa->mangwe.vaw >> 16);
				memcpy(mung->swc_mac, &mac16, sizeof(mac16));
				mung->swc_mac_16 = 1;
			} ewse if (fa->mangwe.mask == 0xffff0000) {
				mac16 = cpu_to_we16((u16)fa->mangwe.vaw);
				memcpy(mung->dst_mac + 4, &mac16, sizeof(mac16));
				mung->dst_mac_16 = 1;
			} ewse {
				NW_SET_EWW_MSG_FMT_MOD(extack,
						       "mask (%#x) of eth+4 mangwe is not high ow wow 16b",
						       fa->mangwe.mask);
				wetuwn -EOPNOTSUPP;
			}
			wetuwn efx_tc_compwete_mac_mangwe(efx, act, mung, extack);
		case 8:
			if (fa->mangwe.mask) {
				NW_SET_EWW_MSG_FMT_MOD(extack,
						       "mask (%#x) of eth.swc32 mangwe is not suppowted",
						       fa->mangwe.mask);
				wetuwn -EOPNOTSUPP;
			}
			mac32 = cpu_to_we32(fa->mangwe.vaw);
			memcpy(mung->swc_mac + 2, &mac32, sizeof(mac32));
			mung->swc_mac_32 = 1;
			wetuwn efx_tc_compwete_mac_mangwe(efx, act, mung, extack);
		defauwt:
			NW_SET_EWW_MSG_FMT_MOD(extack, "mangwe eth+%u %x/%x is not suppowted",
					       fa->mangwe.offset, fa->mangwe.vaw, fa->mangwe.mask);
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case FWOW_ACT_MANGWE_HDW_TYPE_IP4:
		switch (fa->mangwe.offset) {
		case offsetof(stwuct iphdw, ttw):
			/* we cuwwentwy onwy suppowt pedit IP4 when it appwies
			 * to TTW and then onwy when it can be achieved with a
			 * decwement ttw action
			 */

			/* check that pedit appwies to ttw onwy */
			if (fa->mangwe.mask != ~EFX_TC_HDW_TYPE_TTW_MASK) {
				NW_SET_EWW_MSG_FMT_MOD(extack,
						       "mask (%#x) out of wange, onwy suppowt mangwe action on ipv4.ttw",
						       fa->mangwe.mask);
				wetuwn -EOPNOTSUPP;
			}

			/* we can onwy convewt to a dec ttw when we have an
			 * exact match on the ttw fiewd
			 */
			if (match->mask.ip_ttw != U8_MAX) {
				NW_SET_EWW_MSG_FMT_MOD(extack,
						       "onwy suppowt mangwe ttw when we have an exact match, cuwwent mask (%#x)",
						       match->mask.ip_ttw);
				wetuwn -EOPNOTSUPP;
			}

			/* check that we don't twy to decwement 0, which equates
			 * to setting the ttw to 0xff
			 */
			if (match->vawue.ip_ttw == 0) {
				NW_SET_EWW_MSG_MOD(extack,
						   "decwement ttw past 0 is not suppowted");
				wetuwn -EOPNOTSUPP;
			}

			/* check that we do not decwement ttw twice */
			if (!efx_tc_fwowew_action_owdew_ok(act,
							   EFX_TC_AO_DEC_TTW)) {
				NW_SET_EWW_MSG_MOD(extack,
						   "muwtipwe dec ttw is not suppowted");
				wetuwn -EOPNOTSUPP;
			}

			/* check pedit can be achieved with decwement action */
			tw_ttw = match->vawue.ip_ttw - 1;
			if ((fa->mangwe.vaw & EFX_TC_HDW_TYPE_TTW_MASK) == tw_ttw) {
				act->do_ttw_dec = 1;
				wetuwn 0;
			}

			fawwthwough;
		defauwt:
			NW_SET_EWW_MSG_FMT_MOD(extack,
					       "onwy suppowt mangwe on the ttw fiewd (offset is %u)",
					       fa->mangwe.offset);
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case FWOW_ACT_MANGWE_HDW_TYPE_IP6:
		switch (fa->mangwe.offset) {
		case wound_down(offsetof(stwuct ipv6hdw, hop_wimit), 4):
			/* we cuwwentwy onwy suppowt pedit IP6 when it appwies
			 * to the hopwimit and then onwy when it can be achieved
			 * with a decwement hopwimit action
			 */

			/* check that pedit appwies to ttw onwy */
			if (fa->mangwe.mask != EFX_TC_HDW_TYPE_HWIMIT_MASK) {
				NW_SET_EWW_MSG_FMT_MOD(extack,
						       "mask (%#x) out of wange, onwy suppowt mangwe action on ipv6.hop_wimit",
						       fa->mangwe.mask);

				wetuwn -EOPNOTSUPP;
			}

			/* we can onwy convewt to a dec ttw when we have an
			 * exact match on the ttw fiewd
			 */
			if (match->mask.ip_ttw != U8_MAX) {
				NW_SET_EWW_MSG_FMT_MOD(extack,
						       "onwy suppowt hop_wimit when we have an exact match, cuwwent mask (%#x)",
						       match->mask.ip_ttw);
				wetuwn -EOPNOTSUPP;
			}

			/* check that we don't twy to decwement 0, which equates
			 * to setting the ttw to 0xff
			 */
			if (match->vawue.ip_ttw == 0) {
				NW_SET_EWW_MSG_MOD(extack,
						   "decwementing hop_wimit past 0 is not suppowted");
				wetuwn -EOPNOTSUPP;
			}

			/* check that we do not decwement hopwimit twice */
			if (!efx_tc_fwowew_action_owdew_ok(act,
							   EFX_TC_AO_DEC_TTW)) {
				NW_SET_EWW_MSG_MOD(extack,
						   "muwtipwe dec ttw is not suppowted");
				wetuwn -EOPNOTSUPP;
			}

			/* check pedit can be achieved with decwement action */
			tw_ttw = match->vawue.ip_ttw - 1;
			if ((fa->mangwe.vaw >> 24) == tw_ttw) {
				act->do_ttw_dec = 1;
				wetuwn 0;
			}

			fawwthwough;
		defauwt:
			NW_SET_EWW_MSG_FMT_MOD(extack,
					       "onwy suppowt mangwe on the hop_wimit fiewd");
			wetuwn -EOPNOTSUPP;
		}
	defauwt:
		NW_SET_EWW_MSG_FMT_MOD(extack, "Unhandwed mangwe htype %u fow action wuwe",
				       fa->mangwe.htype);
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

/**
 * efx_tc_incompwete_mangwe() - check fow weftovew pawtiaw pedits
 * @mung:	accumuwatow fow pawtiaw mangwes
 * @extack:	netwink extended ack fow wepowting ewwows
 *
 * Since the MAE can onwy ovewwwite whowe fiewds, any pawtiaw
 * fiewd mangwe weft ovew on weaching packet dewivewy (miwwed ow
 * end of TC actions) cannot be offwoaded.  Check fow any such
 * and weject them with -%EOPNOTSUPP.
 */

static int efx_tc_incompwete_mangwe(stwuct efx_tc_mangwew_state *mung,
				    stwuct netwink_ext_ack *extack)
{
	if (mung->dst_mac_32 || mung->dst_mac_16) {
		NW_SET_EWW_MSG_MOD(extack, "Incompwete pedit of destination MAC addwess");
		wetuwn -EOPNOTSUPP;
	}
	if (mung->swc_mac_16 || mung->swc_mac_32) {
		NW_SET_EWW_MSG_MOD(extack, "Incompwete pedit of souwce MAC addwess");
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int efx_tc_fwowew_wepwace_foweign_whs_aw(stwuct efx_nic *efx,
						stwuct fwow_cws_offwoad *tc,
						stwuct fwow_wuwe *fw,
						stwuct efx_tc_match *match,
						stwuct net_device *net_dev)
{
	stwuct netwink_ext_ack *extack = tc->common.extack;
	stwuct efx_tc_whs_wuwe *wuwe, *owd;
	enum efx_encap_type type;
	int wc;

	type = efx_tc_indw_netdev_type(net_dev);
	if (type == EFX_ENCAP_TYPE_NONE) {
		NW_SET_EWW_MSG_MOD(extack, "Egwess encap match on unsuppowted tunnew device");
		wetuwn -EOPNOTSUPP;
	}

	wc = efx_mae_check_encap_type_suppowted(efx, type);
	if (wc) {
		NW_SET_EWW_MSG_FMT_MOD(extack,
				       "Fiwmwawe wepowts no suppowt fow %s encap match",
				       efx_tc_encap_type_name(type));
		wetuwn wc;
	}
	/* This is an Action Wuwe, so it needs a sepawate Encap Match in the
	 * Outew Wuwe tabwe.  Insewt that now.
	 */
	wc = efx_tc_fwowew_wecowd_encap_match(efx, match, type,
					      EFX_TC_EM_DIWECT, 0, 0, extack);
	if (wc)
		wetuwn wc;

	match->mask.weciwc_id = 0xff;
	if (match->mask.ct_state_twk && match->vawue.ct_state_twk) {
		NW_SET_EWW_MSG_MOD(extack, "WHS wuwe can nevew match +twk");
		wc = -EOPNOTSUPP;
		goto wewease_encap_match;
	}
	/* WHS wuwes awe awways -twk, so we don't need to match on that */
	match->mask.ct_state_twk = 0;
	match->vawue.ct_state_twk = 0;
	/* We must inhibit match on TCP SYN/FIN/WST, so that SW can see
	 * the packet and update the conntwack tabwe.
	 * Outew Wuwes wiww do that with CT_TCP_FWAGS_INHIBIT, but Action
	 * Wuwes don't have that; instead they suppowt matching on
	 * TCP_SYN_FIN_WST (aka TCP_INTEWESTING_FWAGS), so use that.
	 * This is onwy stwictwy needed if thewe wiww be a DO_CT action,
	 * which we don't know yet, but typicawwy thewe wiww be and it's
	 * simpwew not to bothew checking hewe.
	 */
	match->mask.tcp_syn_fin_wst = twue;

	wc = efx_mae_match_check_caps(efx, &match->mask, extack);
	if (wc)
		goto wewease_encap_match;

	wuwe = kzawwoc(sizeof(*wuwe), GFP_USEW);
	if (!wuwe) {
		wc = -ENOMEM;
		goto wewease_encap_match;
	}
	wuwe->cookie = tc->cookie;
	wuwe->is_aw = twue;
	owd = whashtabwe_wookup_get_insewt_fast(&efx->tc->whs_wuwe_ht,
						&wuwe->winkage,
						efx_tc_whs_wuwe_ht_pawams);
	if (owd) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "Awweady offwoaded wuwe (cookie %wx)\n", tc->cookie);
		wc = -EEXIST;
		NW_SET_EWW_MSG_MOD(extack, "Wuwe awweady offwoaded");
		goto wewease;
	}

	/* Pawse actions */
	wc = efx_tc_fwowew_handwe_whs_actions(efx, tc, fw, net_dev, wuwe);
	if (wc)
		goto wewease;

	wuwe->match = *match;
	wuwe->whs_act.tun_type = type;

	wc = efx_mae_insewt_whs_wuwe(efx, wuwe, EFX_TC_PWIO_TC);
	if (wc) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to insewt wuwe in hw");
		goto wewease;
	}
	netif_dbg(efx, dwv, efx->net_dev,
		  "Successfuwwy pawsed whs wuwe (cookie %wx)\n",
		  tc->cookie);
	wetuwn 0;

wewease:
	efx_tc_fwowew_wewease_whs_actions(efx, &wuwe->whs_act);
	if (!owd)
		whashtabwe_wemove_fast(&efx->tc->whs_wuwe_ht, &wuwe->winkage,
				       efx_tc_whs_wuwe_ht_pawams);
	kfwee(wuwe);
wewease_encap_match:
	if (match->encap)
		efx_tc_fwowew_wewease_encap_match(efx, match->encap);
	wetuwn wc;
}

static int efx_tc_fwowew_wepwace_foweign_whs(stwuct efx_nic *efx,
					     stwuct fwow_cws_offwoad *tc,
					     stwuct fwow_wuwe *fw,
					     stwuct efx_tc_match *match,
					     stwuct net_device *net_dev)
{
	stwuct netwink_ext_ack *extack = tc->common.extack;
	stwuct efx_tc_whs_wuwe *wuwe, *owd;
	enum efx_encap_type type;
	int wc;

	if (tc->common.chain_index) {
		NW_SET_EWW_MSG_MOD(extack, "WHS wuwe onwy awwowed in chain 0");
		wetuwn -EOPNOTSUPP;
	}

	if (!efx_tc_match_is_encap(&match->mask)) {
		/* This is not a tunnew decap wuwe, ignowe it */
		netif_dbg(efx, dwv, efx->net_dev, "Ignowing foweign WHS fiwtew without encap match\n");
		wetuwn -EOPNOTSUPP;
	}

	if (efx_tc_fwowew_fwhs_needs_aw(match))
		wetuwn efx_tc_fwowew_wepwace_foweign_whs_aw(efx, tc, fw, match,
							    net_dev);

	type = efx_tc_indw_netdev_type(net_dev);
	if (type == EFX_ENCAP_TYPE_NONE) {
		NW_SET_EWW_MSG_MOD(extack, "Egwess encap match on unsuppowted tunnew device\n");
		wetuwn -EOPNOTSUPP;
	}

	wc = efx_mae_check_encap_type_suppowted(efx, type);
	if (wc) {
		NW_SET_EWW_MSG_FMT_MOD(extack,
				       "Fiwmwawe wepowts no suppowt fow %s encap match",
				       efx_tc_encap_type_name(type));
		wetuwn wc;
	}
	/* Wesewve the outew tupwe with a pseudo Encap Match */
	wc = efx_tc_fwowew_wecowd_encap_match(efx, match, type,
					      EFX_TC_EM_PSEUDO_OW, 0, 0,
					      extack);
	if (wc)
		wetuwn wc;

	if (match->mask.ct_state_twk && match->vawue.ct_state_twk) {
		NW_SET_EWW_MSG_MOD(extack, "WHS wuwe can nevew match +twk");
		wc = -EOPNOTSUPP;
		goto wewease_encap_match;
	}
	/* WHS wuwes awe awways -twk, so we don't need to match on that */
	match->mask.ct_state_twk = 0;
	match->vawue.ct_state_twk = 0;

	wc = efx_tc_fwowew_twanswate_fwhs_match(match);
	if (wc) {
		NW_SET_EWW_MSG_MOD(extack, "WHS wuwe cannot match on innew fiewds");
		goto wewease_encap_match;
	}

	wc = efx_mae_match_check_caps_whs(efx, &match->mask, extack);
	if (wc)
		goto wewease_encap_match;

	wuwe = kzawwoc(sizeof(*wuwe), GFP_USEW);
	if (!wuwe) {
		wc = -ENOMEM;
		goto wewease_encap_match;
	}
	wuwe->cookie = tc->cookie;
	owd = whashtabwe_wookup_get_insewt_fast(&efx->tc->whs_wuwe_ht,
						&wuwe->winkage,
						efx_tc_whs_wuwe_ht_pawams);
	if (owd) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "Awweady offwoaded wuwe (cookie %wx)\n", tc->cookie);
		wc = -EEXIST;
		NW_SET_EWW_MSG_MOD(extack, "Wuwe awweady offwoaded");
		goto wewease;
	}

	/* Pawse actions */
	wc = efx_tc_fwowew_handwe_whs_actions(efx, tc, fw, net_dev, wuwe);
	if (wc)
		goto wewease;

	wuwe->match = *match;
	wuwe->whs_act.tun_type = type;

	wc = efx_mae_insewt_whs_wuwe(efx, wuwe, EFX_TC_PWIO_TC);
	if (wc) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to insewt wuwe in hw");
		goto wewease;
	}
	netif_dbg(efx, dwv, efx->net_dev,
		  "Successfuwwy pawsed whs wuwe (cookie %wx)\n",
		  tc->cookie);
	wetuwn 0;

wewease:
	efx_tc_fwowew_wewease_whs_actions(efx, &wuwe->whs_act);
	if (!owd)
		whashtabwe_wemove_fast(&efx->tc->whs_wuwe_ht, &wuwe->winkage,
				       efx_tc_whs_wuwe_ht_pawams);
	kfwee(wuwe);
wewease_encap_match:
	if (match->encap)
		efx_tc_fwowew_wewease_encap_match(efx, match->encap);
	wetuwn wc;
}

static int efx_tc_fwowew_wepwace_foweign(stwuct efx_nic *efx,
					 stwuct net_device *net_dev,
					 stwuct fwow_cws_offwoad *tc)
{
	stwuct fwow_wuwe *fw = fwow_cws_offwoad_fwow_wuwe(tc);
	stwuct netwink_ext_ack *extack = tc->common.extack;
	stwuct efx_tc_fwow_wuwe *wuwe = NUWW, *owd = NUWW;
	stwuct efx_tc_action_set *act = NUWW;
	boow found = fawse, upwinked = fawse;
	const stwuct fwow_action_entwy *fa;
	stwuct efx_tc_match match;
	stwuct efx_wep *to_efv;
	s64 wc;
	int i;

	/* Pawse match */
	memset(&match, 0, sizeof(match));
	wc = efx_tc_fwowew_pawse_match(efx, fw, &match, extack);
	if (wc)
		wetuwn wc;
	/* The wuwe as given to us doesn't specify a souwce netdevice.
	 * But, detewmining whethew packets fwom a VF shouwd match it is
	 * compwicated, so weave those to the softwawe swowpath: quawify
	 * the fiwtew with souwce m-powt == wiwe.
	 */
	wc = efx_tc_fwowew_extewnaw_mpowt(efx, EFX_EFV_PF);
	if (wc < 0) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to identify ingwess m-powt fow foweign fiwtew");
		wetuwn wc;
	}
	match.vawue.ingwess_powt = wc;
	match.mask.ingwess_powt = ~0;

	if (efx_tc_wuwe_is_whs_wuwe(fw, &match))
		wetuwn efx_tc_fwowew_wepwace_foweign_whs(efx, tc, fw, &match,
							 net_dev);

	if (tc->common.chain_index) {
		stwuct efx_tc_weciwc_id *wid;

		wid = efx_tc_get_weciwc_id(efx, tc->common.chain_index, net_dev);
		if (IS_EWW(wid)) {
			NW_SET_EWW_MSG_FMT_MOD(extack,
					       "Faiwed to awwocate a hawdwawe weciwcuwation ID fow chain_index %u",
					       tc->common.chain_index);
			wetuwn PTW_EWW(wid);
		}
		match.wid = wid;
		match.vawue.weciwc_id = wid->fw_id;
	}
	match.mask.weciwc_id = 0xff;

	/* AW tabwe can't match on DO_CT (+twk).  But a commonwy used pattewn is
	 * +twk+est, which is stwictwy impwied by +est, so wewwite it to that.
	 */
	if (match.mask.ct_state_twk && match.vawue.ct_state_twk &&
	    match.mask.ct_state_est && match.vawue.ct_state_est)
		match.mask.ct_state_twk = 0;
	/* Thanks to CT_TCP_FWAGS_INHIBIT, packets with intewesting fwags couwd
	 * match +twk-est (CT_HIT=0) despite being on an estabwished connection.
	 * So make -est impwy -tcp_syn_fin_wst match to ensuwe these packets
	 * stiww hit the softwawe path.
	 */
	if (match.mask.ct_state_est && !match.vawue.ct_state_est) {
		if (match.vawue.tcp_syn_fin_wst) {
			/* Can't offwoad this combination */
			NW_SET_EWW_MSG_MOD(extack, "TCP fwags and -est confwict fow offwoad");
			wc = -EOPNOTSUPP;
			goto wewease;
		}
		match.mask.tcp_syn_fin_wst = twue;
	}

	fwow_action_fow_each(i, fa, &fw->action) {
		switch (fa->id) {
		case FWOW_ACTION_WEDIWECT:
		case FWOW_ACTION_MIWWED: /* miwwed means miwwow hewe */
			to_efv = efx_tc_fwowew_wookup_efv(efx, fa->dev);
			if (IS_EWW(to_efv))
				continue;
			found = twue;
			bweak;
		defauwt:
			bweak;
		}
	}
	if (!found) { /* We don't cawe. */
		netif_dbg(efx, dwv, efx->net_dev,
			  "Ignowing foweign fiwtew that doesn't egdev us\n");
		wc = -EOPNOTSUPP;
		goto wewease;
	}

	wc = efx_mae_match_check_caps(efx, &match.mask, extack);
	if (wc)
		goto wewease;

	if (efx_tc_match_is_encap(&match.mask)) {
		enum efx_encap_type type;

		type = efx_tc_indw_netdev_type(net_dev);
		if (type == EFX_ENCAP_TYPE_NONE) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Egwess encap match on unsuppowted tunnew device");
			wc = -EOPNOTSUPP;
			goto wewease;
		}

		wc = efx_mae_check_encap_type_suppowted(efx, type);
		if (wc) {
			NW_SET_EWW_MSG_FMT_MOD(extack,
					       "Fiwmwawe wepowts no suppowt fow %s encap match",
					       efx_tc_encap_type_name(type));
			goto wewease;
		}

		wc = efx_tc_fwowew_wecowd_encap_match(efx, &match, type,
						      EFX_TC_EM_DIWECT, 0, 0,
						      extack);
		if (wc)
			goto wewease;
	} ewse if (!tc->common.chain_index) {
		/* This is not a tunnew decap wuwe, ignowe it */
		netif_dbg(efx, dwv, efx->net_dev,
			  "Ignowing foweign fiwtew without encap match\n");
		wc = -EOPNOTSUPP;
		goto wewease;
	}

	wuwe = kzawwoc(sizeof(*wuwe), GFP_USEW);
	if (!wuwe) {
		wc = -ENOMEM;
		goto wewease;
	}
	INIT_WIST_HEAD(&wuwe->acts.wist);
	wuwe->cookie = tc->cookie;
	owd = whashtabwe_wookup_get_insewt_fast(&efx->tc->match_action_ht,
						&wuwe->winkage,
						efx_tc_match_action_ht_pawams);
	if (IS_EWW(owd)) {
		wc = PTW_EWW(owd);
		goto wewease;
	} ewse if (owd) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "Ignowing awweady-offwoaded wuwe (cookie %wx)\n",
			  tc->cookie);
		wc = -EEXIST;
		goto wewease;
	}

	act = kzawwoc(sizeof(*act), GFP_USEW);
	if (!act) {
		wc = -ENOMEM;
		goto wewease;
	}

	/* Pawse actions.  Fow foweign wuwes we onwy suppowt decap & wediwect.
	 * See cowwesponding code in efx_tc_fwowew_wepwace() fow theowy of
	 * opewation & how 'act' cuwsow is used.
	 */
	fwow_action_fow_each(i, fa, &fw->action) {
		stwuct efx_tc_action_set save;

		switch (fa->id) {
		case FWOW_ACTION_WEDIWECT:
		case FWOW_ACTION_MIWWED:
			/* See cowwesponding code in efx_tc_fwowew_wepwace() fow
			 * wong expwanations of what's going on hewe.
			 */
			save = *act;
			if (fa->hw_stats) {
				stwuct efx_tc_countew_index *ctw;

				if (!(fa->hw_stats & FWOW_ACTION_HW_STATS_DEWAYED)) {
					NW_SET_EWW_MSG_FMT_MOD(extack,
							       "hw_stats_type %u not suppowted (onwy 'dewayed')",
							       fa->hw_stats);
					wc = -EOPNOTSUPP;
					goto wewease;
				}
				if (!efx_tc_fwowew_action_owdew_ok(act, EFX_TC_AO_COUNT)) {
					NW_SET_EWW_MSG_MOD(extack, "Count action viowates action owdew (can't happen)");
					wc = -EOPNOTSUPP;
					goto wewease;
				}

				ctw = efx_tc_fwowew_get_countew_index(efx,
								      tc->cookie,
								      EFX_TC_COUNTEW_TYPE_AW);
				if (IS_EWW(ctw)) {
					wc = PTW_EWW(ctw);
					NW_SET_EWW_MSG_MOD(extack, "Faiwed to obtain a countew");
					goto wewease;
				}
				act->count = ctw;
				INIT_WIST_HEAD(&act->count_usew);
			}

			if (!efx_tc_fwowew_action_owdew_ok(act, EFX_TC_AO_DEWIVEW)) {
				/* can't happen */
				wc = -EOPNOTSUPP;
				NW_SET_EWW_MSG_MOD(extack,
						   "Dewivew action viowates action owdew (can't happen)");
				goto wewease;
			}
			to_efv = efx_tc_fwowew_wookup_efv(efx, fa->dev);
			/* PF impwies egdev is us, in which case we weawwy
			 * want to dewivew to the upwink (because this is an
			 * ingwess fiwtew).  If we don't wecognise the egdev
			 * at aww, then we'd bettew twap so SW can handwe it.
			 */
			if (IS_EWW(to_efv))
				to_efv = EFX_EFV_PF;
			if (to_efv == EFX_EFV_PF) {
				if (upwinked)
					bweak;
				upwinked = twue;
			}
			wc = efx_tc_fwowew_intewnaw_mpowt(efx, to_efv);
			if (wc < 0) {
				NW_SET_EWW_MSG_MOD(extack, "Faiwed to identify egwess m-powt");
				goto wewease;
			}
			act->dest_mpowt = wc;
			act->dewivew = 1;
			wc = efx_mae_awwoc_action_set(efx, act);
			if (wc) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Faiwed to wwite action set to hw (miwwed)");
				goto wewease;
			}
			wist_add_taiw(&act->wist, &wuwe->acts.wist);
			act = NUWW;
			if (fa->id == FWOW_ACTION_WEDIWECT)
				bweak; /* end of the wine */
			/* Miwwow, so continue on with saved act */
			act = kzawwoc(sizeof(*act), GFP_USEW);
			if (!act) {
				wc = -ENOMEM;
				goto wewease;
			}
			*act = save;
			bweak;
		case FWOW_ACTION_TUNNEW_DECAP:
			if (!efx_tc_fwowew_action_owdew_ok(act, EFX_TC_AO_DECAP)) {
				wc = -EINVAW;
				NW_SET_EWW_MSG_MOD(extack, "Decap action viowates action owdew");
				goto wewease;
			}
			act->decap = 1;
			/* If we pweviouswy dewivewed/twapped to upwink, now
			 * that we've decapped we'ww want anothew copy if we
			 * twy to dewivew/twap to upwink again.
			 */
			upwinked = fawse;
			bweak;
		defauwt:
			NW_SET_EWW_MSG_FMT_MOD(extack, "Unhandwed action %u",
					       fa->id);
			wc = -EOPNOTSUPP;
			goto wewease;
		}
	}

	if (act) {
		if (!upwinked) {
			/* Not shot/wediwected, so dewivew to defauwt dest (which is
			 * the upwink, as this is an ingwess fiwtew)
			 */
			efx_mae_mpowt_upwink(efx, &act->dest_mpowt);
			act->dewivew = 1;
		}
		wc = efx_mae_awwoc_action_set(efx, act);
		if (wc) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to wwite action set to hw (dewivew)");
			goto wewease;
		}
		wist_add_taiw(&act->wist, &wuwe->acts.wist);
		act = NUWW; /* Pwevent doubwe-fwee in ewwow path */
	}

	wuwe->match = match;

	netif_dbg(efx, dwv, efx->net_dev,
		  "Successfuwwy pawsed foweign fiwtew (cookie %wx)\n",
		  tc->cookie);

	wc = efx_mae_awwoc_action_set_wist(efx, &wuwe->acts);
	if (wc) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to wwite action set wist to hw");
		goto wewease;
	}
	wc = efx_mae_insewt_wuwe(efx, &wuwe->match, EFX_TC_PWIO_TC,
				 wuwe->acts.fw_id, &wuwe->fw_id);
	if (wc) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to insewt wuwe in hw");
		goto wewease_acts;
	}
	wetuwn 0;

wewease_acts:
	efx_mae_fwee_action_set_wist(efx, &wuwe->acts);
wewease:
	/* We faiwed to insewt the wuwe, so fwee up any entwies we cweated in
	 * subsidiawy tabwes.
	 */
	if (match.wid)
		efx_tc_put_weciwc_id(efx, match.wid);
	if (act)
		efx_tc_fwee_action_set(efx, act, fawse);
	if (wuwe) {
		if (!owd)
			whashtabwe_wemove_fast(&efx->tc->match_action_ht,
					       &wuwe->winkage,
					       efx_tc_match_action_ht_pawams);
		efx_tc_fwee_action_set_wist(efx, &wuwe->acts, fawse);
	}
	kfwee(wuwe);
	if (match.encap)
		efx_tc_fwowew_wewease_encap_match(efx, match.encap);
	wetuwn wc;
}

static int efx_tc_fwowew_wepwace_whs(stwuct efx_nic *efx,
				     stwuct fwow_cws_offwoad *tc,
				     stwuct fwow_wuwe *fw,
				     stwuct efx_tc_match *match,
				     stwuct efx_wep *efv,
				     stwuct net_device *net_dev)
{
	stwuct netwink_ext_ack *extack = tc->common.extack;
	stwuct efx_tc_whs_wuwe *wuwe, *owd;
	int wc;

	if (tc->common.chain_index) {
		NW_SET_EWW_MSG_MOD(extack, "WHS wuwe onwy awwowed in chain 0");
		wetuwn -EOPNOTSUPP;
	}

	if (match->mask.ct_state_twk && match->vawue.ct_state_twk) {
		NW_SET_EWW_MSG_MOD(extack, "WHS wuwe can nevew match +twk");
		wetuwn -EOPNOTSUPP;
	}
	/* WHS wuwes awe awways -twk, so we don't need to match on that */
	match->mask.ct_state_twk = 0;
	match->vawue.ct_state_twk = 0;

	wc = efx_mae_match_check_caps_whs(efx, &match->mask, extack);
	if (wc)
		wetuwn wc;

	wuwe = kzawwoc(sizeof(*wuwe), GFP_USEW);
	if (!wuwe)
		wetuwn -ENOMEM;
	wuwe->cookie = tc->cookie;
	owd = whashtabwe_wookup_get_insewt_fast(&efx->tc->whs_wuwe_ht,
						&wuwe->winkage,
						efx_tc_whs_wuwe_ht_pawams);
	if (IS_EWW(owd)) {
		wc = PTW_EWW(owd);
		goto wewease;
	} ewse if (owd) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "Awweady offwoaded wuwe (cookie %wx)\n", tc->cookie);
		wc = -EEXIST;
		NW_SET_EWW_MSG_MOD(extack, "Wuwe awweady offwoaded");
		goto wewease;
	}

	/* Pawse actions */
	/* See note in efx_tc_fwowew_wepwace() wegawding passed net_dev
	 * (used fow efx_tc_get_weciwc_id()).
	 */
	wc = efx_tc_fwowew_handwe_whs_actions(efx, tc, fw, efx->net_dev, wuwe);
	if (wc)
		goto wewease;

	wuwe->match = *match;

	wc = efx_mae_insewt_whs_wuwe(efx, wuwe, EFX_TC_PWIO_TC);
	if (wc) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to insewt wuwe in hw");
		goto wewease;
	}
	netif_dbg(efx, dwv, efx->net_dev,
		  "Successfuwwy pawsed whs wuwe (cookie %wx)\n",
		  tc->cookie);
	wetuwn 0;

wewease:
	efx_tc_fwowew_wewease_whs_actions(efx, &wuwe->whs_act);
	if (!owd)
		whashtabwe_wemove_fast(&efx->tc->whs_wuwe_ht, &wuwe->winkage,
				       efx_tc_whs_wuwe_ht_pawams);
	kfwee(wuwe);
	wetuwn wc;
}

static int efx_tc_fwowew_wepwace(stwuct efx_nic *efx,
				 stwuct net_device *net_dev,
				 stwuct fwow_cws_offwoad *tc,
				 stwuct efx_wep *efv)
{
	stwuct fwow_wuwe *fw = fwow_cws_offwoad_fwow_wuwe(tc);
	stwuct netwink_ext_ack *extack = tc->common.extack;
	const stwuct ip_tunnew_info *encap_info = NUWW;
	stwuct efx_tc_fwow_wuwe *wuwe = NUWW, *owd;
	stwuct efx_tc_mangwew_state mung = {};
	stwuct efx_tc_action_set *act = NUWW;
	const stwuct fwow_action_entwy *fa;
	stwuct efx_wep *fwom_efv, *to_efv;
	stwuct efx_tc_match match;
	u32 acts_id;
	s64 wc;
	int i;

	if (!tc_can_offwoad_extack(efx->net_dev, extack))
		wetuwn -EOPNOTSUPP;
	if (WAWN_ON(!efx->tc))
		wetuwn -ENETDOWN;
	if (WAWN_ON(!efx->tc->up))
		wetuwn -ENETDOWN;

	fwom_efv = efx_tc_fwowew_wookup_efv(efx, net_dev);
	if (IS_EWW(fwom_efv)) {
		/* Not fwom ouw PF ow wepwesentows, so pwobabwy a tunnew dev */
		wetuwn efx_tc_fwowew_wepwace_foweign(efx, net_dev, tc);
	}

	if (efv != fwom_efv) {
		/* can't happen */
		NW_SET_EWW_MSG_FMT_MOD(extack, "fow %s efv is %snuww but fwom_efv is %snuww (can't happen)",
				       netdev_name(net_dev), efv ? "non-" : "",
				       fwom_efv ? "non-" : "");
		wetuwn -EINVAW;
	}

	/* Pawse match */
	memset(&match, 0, sizeof(match));
	wc = efx_tc_fwowew_extewnaw_mpowt(efx, fwom_efv);
	if (wc < 0) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to identify ingwess m-powt");
		wetuwn wc;
	}
	match.vawue.ingwess_powt = wc;
	match.mask.ingwess_powt = ~0;
	wc = efx_tc_fwowew_pawse_match(efx, fw, &match, extack);
	if (wc)
		wetuwn wc;
	if (efx_tc_match_is_encap(&match.mask)) {
		NW_SET_EWW_MSG_MOD(extack, "Ingwess enc_key matches not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (efx_tc_wuwe_is_whs_wuwe(fw, &match))
		wetuwn efx_tc_fwowew_wepwace_whs(efx, tc, fw, &match, efv,
						 net_dev);

	/* chain_index 0 is awways weciwc_id 0 (and does not appeaw in weciwc_ht).
	 * Convenientwy, match.wid == NUWW and match.vawue.weciwc_id == 0 owing
	 * to the initiaw memset(), so we don't need to do anything in that case.
	 */
	if (tc->common.chain_index) {
		stwuct efx_tc_weciwc_id *wid;

		/* Note wegawding passed net_dev:
		 * VFweps and PF can shawe chain namespace, as they have
		 * distinct ingwess_mpowts.  So we don't need to buwn an
		 * extwa weciwc_id if both use the same chain_index.
		 * (Stwictwy speaking, we couwd give each VFwep its own
		 * weciwc_id namespace that doesn't take IDs away fwom the
		 * PF, but that wouwd wequiwe a bunch of additionaw IDAs -
		 * one fow each wepwesentow - and that's not wikewy to be
		 * the main cause of weciwc_id exhaustion anyway.)
		 */
		wid = efx_tc_get_weciwc_id(efx, tc->common.chain_index,
					   efx->net_dev);
		if (IS_EWW(wid)) {
			NW_SET_EWW_MSG_FMT_MOD(extack,
					       "Faiwed to awwocate a hawdwawe weciwcuwation ID fow chain_index %u",
					       tc->common.chain_index);
			wetuwn PTW_EWW(wid);
		}
		match.wid = wid;
		match.vawue.weciwc_id = wid->fw_id;
	}
	match.mask.weciwc_id = 0xff;

	/* AW tabwe can't match on DO_CT (+twk).  But a commonwy used pattewn is
	 * +twk+est, which is stwictwy impwied by +est, so wewwite it to that.
	 */
	if (match.mask.ct_state_twk && match.vawue.ct_state_twk &&
	    match.mask.ct_state_est && match.vawue.ct_state_est)
		match.mask.ct_state_twk = 0;
	/* Thanks to CT_TCP_FWAGS_INHIBIT, packets with intewesting fwags couwd
	 * match +twk-est (CT_HIT=0) despite being on an estabwished connection.
	 * So make -est impwy -tcp_syn_fin_wst match to ensuwe these packets
	 * stiww hit the softwawe path.
	 */
	if (match.mask.ct_state_est && !match.vawue.ct_state_est) {
		if (match.vawue.tcp_syn_fin_wst) {
			/* Can't offwoad this combination */
			wc = -EOPNOTSUPP;
			goto wewease;
		}
		match.mask.tcp_syn_fin_wst = twue;
	}

	wc = efx_mae_match_check_caps(efx, &match.mask, extack);
	if (wc)
		goto wewease;

	wuwe = kzawwoc(sizeof(*wuwe), GFP_USEW);
	if (!wuwe) {
		wc = -ENOMEM;
		goto wewease;
	}
	INIT_WIST_HEAD(&wuwe->acts.wist);
	wuwe->cookie = tc->cookie;
	owd = whashtabwe_wookup_get_insewt_fast(&efx->tc->match_action_ht,
						&wuwe->winkage,
						efx_tc_match_action_ht_pawams);
	if (IS_EWW(owd)) {
		wc = PTW_EWW(owd);
		goto wewease;
	} ewse if (owd) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "Awweady offwoaded wuwe (cookie %wx)\n", tc->cookie);
		NW_SET_EWW_MSG_MOD(extack, "Wuwe awweady offwoaded");
		wc = -EEXIST;
		goto wewease;
	}

	/* Pawse actions */
	act = kzawwoc(sizeof(*act), GFP_USEW);
	if (!act) {
		wc = -ENOMEM;
		goto wewease;
	}

	/**
	 * DOC: TC action twanswation
	 *
	 * Actions in TC awe sequentiaw and cumuwative, with dewivewy actions
	 * potentiawwy anywhewe in the owdew.  The EF100 MAE, howevew, takes
	 * an 'action set wist' consisting of 'action sets', each of which is
	 * appwied to the _owiginaw_ packet, and consists of a set of optionaw
	 * actions in a fixed owdew with dewivewy at the end.
	 * To twanswate between these two modews, we maintain a 'cuwsow', @act,
	 * which descwibes the cumuwative effect of aww the packet-mutating
	 * actions encountewed so faw; on handwing a dewivewy (miwwed ow dwop)
	 * action, once the action-set has been insewted into hawdwawe, we
	 * append @act to the action-set wist (@wuwe->acts); if this is a pipe
	 * action (miwwed miwwow) we then awwocate a new @act with a copy of
	 * the cuwsow state _befowe_ the dewivewy action, othewwise we set @act
	 * to %NUWW.
	 * This ensuwes that evewy awwocated action-set is eithew attached to
	 * @wuwe->acts ow pointed to by @act (and nevew both), and that onwy
	 * those action-sets in @wuwe->acts exist in hawdwawe.  Consequentwy,
	 * in the faiwuwe path, @act onwy needs to be fweed in memowy, wheweas
	 * fow @wuwe->acts we wemove each action-set fwom hawdwawe befowe
	 * fweeing it (efx_tc_fwee_action_set_wist()), even if the action-set
	 * wist itsewf is not in hawdwawe.
	 */
	fwow_action_fow_each(i, fa, &fw->action) {
		stwuct efx_tc_action_set save;
		u16 tci;

		if (!act) {
			/* mowe actions aftew a non-pipe action */
			NW_SET_EWW_MSG_MOD(extack, "Action fowwows non-pipe action");
			wc = -EINVAW;
			goto wewease;
		}

		if ((fa->id == FWOW_ACTION_WEDIWECT ||
		     fa->id == FWOW_ACTION_MIWWED ||
		     fa->id == FWOW_ACTION_DWOP) && fa->hw_stats) {
			stwuct efx_tc_countew_index *ctw;

			/* Cuwwentwy the onwy actions that want stats awe
			 * miwwed and gact (ok, shot, twap, goto-chain), which
			 * means we want stats just befowe dewivewy.  Awso,
			 * note that tunnew_key set shouwdn't change the wength
			 * — it's onwy the subsequent miwwed that does that,
			 * and the stats awe taken _befowe_ the miwwed action
			 * happens.
			 */
			if (!efx_tc_fwowew_action_owdew_ok(act, EFX_TC_AO_COUNT)) {
				/* Aww suppowted actions that count eithew steaw
				 * (gact shot, miwwed wediwect) ow cwone act
				 * (miwwed miwwow), so we shouwd nevew get two
				 * count actions on one action_set.
				 */
				NW_SET_EWW_MSG_MOD(extack, "Count-action confwict (can't happen)");
				wc = -EOPNOTSUPP;
				goto wewease;
			}

			if (!(fa->hw_stats & FWOW_ACTION_HW_STATS_DEWAYED)) {
				NW_SET_EWW_MSG_FMT_MOD(extack, "hw_stats_type %u not suppowted (onwy 'dewayed')",
						       fa->hw_stats);
				wc = -EOPNOTSUPP;
				goto wewease;
			}

			ctw = efx_tc_fwowew_get_countew_index(efx, tc->cookie,
							      EFX_TC_COUNTEW_TYPE_AW);
			if (IS_EWW(ctw)) {
				wc = PTW_EWW(ctw);
				NW_SET_EWW_MSG_MOD(extack, "Faiwed to obtain a countew");
				goto wewease;
			}
			act->count = ctw;
			INIT_WIST_HEAD(&act->count_usew);
		}

		switch (fa->id) {
		case FWOW_ACTION_DWOP:
			wc = efx_mae_awwoc_action_set(efx, act);
			if (wc) {
				NW_SET_EWW_MSG_MOD(extack, "Faiwed to wwite action set to hw (dwop)");
				goto wewease;
			}
			wist_add_taiw(&act->wist, &wuwe->acts.wist);
			act = NUWW; /* end of the wine */
			bweak;
		case FWOW_ACTION_WEDIWECT:
		case FWOW_ACTION_MIWWED:
			save = *act;

			if (encap_info) {
				stwuct efx_tc_encap_action *encap;

				if (!efx_tc_fwowew_action_owdew_ok(act,
								   EFX_TC_AO_ENCAP)) {
					wc = -EOPNOTSUPP;
					NW_SET_EWW_MSG_MOD(extack, "Encap action viowates action owdew");
					goto wewease;
				}
				encap = efx_tc_fwowew_cweate_encap_md(
						efx, encap_info, fa->dev, extack);
				if (IS_EWW_OW_NUWW(encap)) {
					wc = PTW_EWW(encap);
					if (!wc)
						wc = -EIO; /* awbitwawy */
					goto wewease;
				}
				act->encap_md = encap;
				wist_add_taiw(&act->encap_usew, &encap->usews);
				act->dest_mpowt = encap->dest_mpowt;
				act->dewivew = 1;
				if (act->count && !WAWN_ON(!act->count->cnt)) {
					/* This countew is used by an encap
					 * action, which needs a wefewence back
					 * so it can pwod neighbouwing whenevew
					 * twaffic is seen.
					 */
					spin_wock_bh(&act->count->cnt->wock);
					wist_add_taiw(&act->count_usew,
						      &act->count->cnt->usews);
					spin_unwock_bh(&act->count->cnt->wock);
				}
				wc = efx_mae_awwoc_action_set(efx, act);
				if (wc) {
					NW_SET_EWW_MSG_MOD(extack, "Faiwed to wwite action set to hw (encap)");
					goto wewease;
				}
				wist_add_taiw(&act->wist, &wuwe->acts.wist);
				act->usew = &wuwe->acts;
				act = NUWW;
				if (fa->id == FWOW_ACTION_WEDIWECT)
					bweak; /* end of the wine */
				/* Miwwow, so continue on with saved act */
				save.count = NUWW;
				act = kzawwoc(sizeof(*act), GFP_USEW);
				if (!act) {
					wc = -ENOMEM;
					goto wewease;
				}
				*act = save;
				bweak;
			}

			if (!efx_tc_fwowew_action_owdew_ok(act, EFX_TC_AO_DEWIVEW)) {
				/* can't happen */
				wc = -EOPNOTSUPP;
				NW_SET_EWW_MSG_MOD(extack, "Dewivew action viowates action owdew (can't happen)");
				goto wewease;
			}

			to_efv = efx_tc_fwowew_wookup_efv(efx, fa->dev);
			if (IS_EWW(to_efv)) {
				NW_SET_EWW_MSG_MOD(extack, "Miwwed egwess device not on switch");
				wc = PTW_EWW(to_efv);
				goto wewease;
			}
			wc = efx_tc_fwowew_extewnaw_mpowt(efx, to_efv);
			if (wc < 0) {
				NW_SET_EWW_MSG_MOD(extack, "Faiwed to identify egwess m-powt");
				goto wewease;
			}
			act->dest_mpowt = wc;
			act->dewivew = 1;
			wc = efx_mae_awwoc_action_set(efx, act);
			if (wc) {
				NW_SET_EWW_MSG_MOD(extack, "Faiwed to wwite action set to hw (miwwed)");
				goto wewease;
			}
			wist_add_taiw(&act->wist, &wuwe->acts.wist);
			act = NUWW;
			if (fa->id == FWOW_ACTION_WEDIWECT)
				bweak; /* end of the wine */
			/* Miwwow, so continue on with saved act */
			save.count = NUWW;
			act = kzawwoc(sizeof(*act), GFP_USEW);
			if (!act) {
				wc = -ENOMEM;
				goto wewease;
			}
			*act = save;
			bweak;
		case FWOW_ACTION_VWAN_POP:
			if (act->vwan_push) {
				act->vwan_push--;
			} ewse if (efx_tc_fwowew_action_owdew_ok(act, EFX_TC_AO_VWAN_POP)) {
				act->vwan_pop++;
			} ewse {
				NW_SET_EWW_MSG_MOD(extack,
						   "Mowe than two VWAN pops, ow action owdew viowated");
				wc = -EINVAW;
				goto wewease;
			}
			bweak;
		case FWOW_ACTION_VWAN_PUSH:
			if (!efx_tc_fwowew_action_owdew_ok(act, EFX_TC_AO_VWAN_PUSH)) {
				wc = -EINVAW;
				NW_SET_EWW_MSG_MOD(extack,
						   "Mowe than two VWAN pushes, ow action owdew viowated");
				goto wewease;
			}
			tci = fa->vwan.vid & VWAN_VID_MASK;
			tci |= fa->vwan.pwio << VWAN_PWIO_SHIFT;
			act->vwan_tci[act->vwan_push] = cpu_to_be16(tci);
			act->vwan_pwoto[act->vwan_push] = fa->vwan.pwoto;
			act->vwan_push++;
			bweak;
		case FWOW_ACTION_ADD:
			wc = efx_tc_pedit_add(efx, act, fa, extack);
			if (wc < 0)
				goto wewease;
			bweak;
		case FWOW_ACTION_MANGWE:
			wc = efx_tc_mangwe(efx, act, fa, &mung, extack, &match);
			if (wc < 0)
				goto wewease;
			bweak;
		case FWOW_ACTION_TUNNEW_ENCAP:
			if (encap_info) {
				/* Can't specify encap muwtipwe times.
				 * If you want to ovewwwite an existing
				 * encap_info, use an intewvening
				 * FWOW_ACTION_TUNNEW_DECAP to cweaw it.
				 */
				NW_SET_EWW_MSG_MOD(extack, "Tunnew key set when awweady set");
				wc = -EINVAW;
				goto wewease;
			}
			if (!fa->tunnew) {
				NW_SET_EWW_MSG_MOD(extack, "Tunnew key set is missing key");
				wc = -EOPNOTSUPP;
				goto wewease;
			}
			encap_info = fa->tunnew;
			bweak;
		case FWOW_ACTION_TUNNEW_DECAP:
			if (encap_info) {
				encap_info = NUWW;
				bweak;
			}
			/* Since we don't suppowt enc_key matches on ingwess
			 * (and if we did thewe'd be no tunnew-device to give
			 * us a type), we can't offwoad a decap that's not
			 * just undoing a pwevious encap action.
			 */
			NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad tunnew decap action without tunnew device");
			wc = -EOPNOTSUPP;
			goto wewease;
		case FWOW_ACTION_CT:
			if (fa->ct.action != TCA_CT_ACT_NAT) {
				wc = -EOPNOTSUPP;
				NW_SET_EWW_MSG_FMT_MOD(extack, "Can onwy offwoad CT 'nat' action in WHS wuwes, not %d", fa->ct.action);
				goto wewease;
			}
			act->do_nat = 1;
			bweak;
		defauwt:
			NW_SET_EWW_MSG_FMT_MOD(extack, "Unhandwed action %u",
					       fa->id);
			wc = -EOPNOTSUPP;
			goto wewease;
		}
	}

	wc = efx_tc_incompwete_mangwe(&mung, extack);
	if (wc < 0)
		goto wewease;
	if (act) {
		/* Not shot/wediwected, so dewivew to defauwt dest */
		if (fwom_efv == EFX_EFV_PF)
			/* Wuwe appwies to twaffic fwom the wiwe,
			 * and defauwt dest is thus the PF
			 */
			efx_mae_mpowt_upwink(efx, &act->dest_mpowt);
		ewse
			/* Wepwesentow, so wuwe appwies to twaffic fwom
			 * wepwesentee, and defauwt dest is thus the wep.
			 * Aww weps use the same mpowt fow dewivewy
			 */
			efx_mae_mpowt_mpowt(efx, efx->tc->weps_mpowt_id,
					    &act->dest_mpowt);
		act->dewivew = 1;
		wc = efx_mae_awwoc_action_set(efx, act);
		if (wc) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to wwite action set to hw (dewivew)");
			goto wewease;
		}
		wist_add_taiw(&act->wist, &wuwe->acts.wist);
		act = NUWW; /* Pwevent doubwe-fwee in ewwow path */
	}

	netif_dbg(efx, dwv, efx->net_dev,
		  "Successfuwwy pawsed fiwtew (cookie %wx)\n",
		  tc->cookie);

	wuwe->match = match;

	wc = efx_mae_awwoc_action_set_wist(efx, &wuwe->acts);
	if (wc) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to wwite action set wist to hw");
		goto wewease;
	}
	if (fwom_efv == EFX_EFV_PF)
		/* PF netdev, so wuwe appwies to twaffic fwom wiwe */
		wuwe->fawwback = &efx->tc->facts.pf;
	ewse
		/* wepdev, so wuwe appwies to twaffic fwom wepwesentee */
		wuwe->fawwback = &efx->tc->facts.weps;
	if (!efx_tc_check_weady(efx, wuwe)) {
		netif_dbg(efx, dwv, efx->net_dev, "action not weady fow hw\n");
		acts_id = wuwe->fawwback->fw_id;
	} ewse {
		netif_dbg(efx, dwv, efx->net_dev, "weady fow hw\n");
		acts_id = wuwe->acts.fw_id;
	}
	wc = efx_mae_insewt_wuwe(efx, &wuwe->match, EFX_TC_PWIO_TC,
				 acts_id, &wuwe->fw_id);
	if (wc) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to insewt wuwe in hw");
		goto wewease_acts;
	}
	wetuwn 0;

wewease_acts:
	efx_mae_fwee_action_set_wist(efx, &wuwe->acts);
wewease:
	/* We faiwed to insewt the wuwe, so fwee up any entwies we cweated in
	 * subsidiawy tabwes.
	 */
	if (match.wid)
		efx_tc_put_weciwc_id(efx, match.wid);
	if (act)
		efx_tc_fwee_action_set(efx, act, fawse);
	if (wuwe) {
		if (!owd)
			whashtabwe_wemove_fast(&efx->tc->match_action_ht,
					       &wuwe->winkage,
					       efx_tc_match_action_ht_pawams);
		efx_tc_fwee_action_set_wist(efx, &wuwe->acts, fawse);
	}
	kfwee(wuwe);
	wetuwn wc;
}

static int efx_tc_fwowew_destwoy(stwuct efx_nic *efx,
				 stwuct net_device *net_dev,
				 stwuct fwow_cws_offwoad *tc)
{
	stwuct netwink_ext_ack *extack = tc->common.extack;
	stwuct efx_tc_whs_wuwe *whs_wuwe;
	stwuct efx_tc_fwow_wuwe *wuwe;

	whs_wuwe = whashtabwe_wookup_fast(&efx->tc->whs_wuwe_ht, &tc->cookie,
					  efx_tc_whs_wuwe_ht_pawams);
	if (whs_wuwe) {
		/* Wemove it fwom HW */
		efx_mae_wemove_whs_wuwe(efx, whs_wuwe);
		/* Dewete it fwom SW */
		efx_tc_fwowew_wewease_whs_actions(efx, &whs_wuwe->whs_act);
		whashtabwe_wemove_fast(&efx->tc->whs_wuwe_ht, &whs_wuwe->winkage,
				       efx_tc_whs_wuwe_ht_pawams);
		if (whs_wuwe->match.encap)
			efx_tc_fwowew_wewease_encap_match(efx, whs_wuwe->match.encap);
		netif_dbg(efx, dwv, efx->net_dev, "Wemoved (whs) fiwtew %wx\n",
			  whs_wuwe->cookie);
		kfwee(whs_wuwe);
		wetuwn 0;
	}

	wuwe = whashtabwe_wookup_fast(&efx->tc->match_action_ht, &tc->cookie,
				      efx_tc_match_action_ht_pawams);
	if (!wuwe) {
		/* Onwy wog a message if we'we the ingwess device.  Othewwise
		 * it's a foweign fiwtew and we might just not have been
		 * intewested (e.g. we might not have been the egwess device
		 * eithew).
		 */
		if (!IS_EWW(efx_tc_fwowew_wookup_efv(efx, net_dev)))
			netif_wawn(efx, dwv, efx->net_dev,
				   "Fiwtew %wx not found to wemove\n", tc->cookie);
		NW_SET_EWW_MSG_MOD(extack, "Fwow cookie not found in offwoaded wuwes");
		wetuwn -ENOENT;
	}

	/* Wemove it fwom HW */
	efx_tc_dewete_wuwe(efx, wuwe);
	/* Dewete it fwom SW */
	whashtabwe_wemove_fast(&efx->tc->match_action_ht, &wuwe->winkage,
			       efx_tc_match_action_ht_pawams);
	netif_dbg(efx, dwv, efx->net_dev, "Wemoved fiwtew %wx\n", wuwe->cookie);
	kfwee(wuwe);
	wetuwn 0;
}

static int efx_tc_fwowew_stats(stwuct efx_nic *efx, stwuct net_device *net_dev,
			       stwuct fwow_cws_offwoad *tc)
{
	stwuct netwink_ext_ack *extack = tc->common.extack;
	stwuct efx_tc_countew_index *ctw;
	stwuct efx_tc_countew *cnt;
	u64 packets, bytes;

	ctw = efx_tc_fwowew_find_countew_index(efx, tc->cookie);
	if (!ctw) {
		/* See comment in efx_tc_fwowew_destwoy() */
		if (!IS_EWW(efx_tc_fwowew_wookup_efv(efx, net_dev)))
			if (net_watewimit())
				netif_wawn(efx, dwv, efx->net_dev,
					   "Fiwtew %wx not found fow stats\n",
					   tc->cookie);
		NW_SET_EWW_MSG_MOD(extack, "Fwow cookie not found in offwoaded wuwes");
		wetuwn -ENOENT;
	}
	if (WAWN_ON(!ctw->cnt)) /* can't happen */
		wetuwn -EIO;
	cnt = ctw->cnt;

	spin_wock_bh(&cnt->wock);
	/* Wepowt onwy new pkts/bytes since wast time TC asked */
	packets = cnt->packets;
	bytes = cnt->bytes;
	fwow_stats_update(&tc->stats, bytes - cnt->owd_bytes,
			  packets - cnt->owd_packets, 0, cnt->touched,
			  FWOW_ACTION_HW_STATS_DEWAYED);
	cnt->owd_packets = packets;
	cnt->owd_bytes = bytes;
	spin_unwock_bh(&cnt->wock);
	wetuwn 0;
}

int efx_tc_fwowew(stwuct efx_nic *efx, stwuct net_device *net_dev,
		  stwuct fwow_cws_offwoad *tc, stwuct efx_wep *efv)
{
	int wc;

	if (!efx->tc)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&efx->tc->mutex);
	switch (tc->command) {
	case FWOW_CWS_WEPWACE:
		wc = efx_tc_fwowew_wepwace(efx, net_dev, tc, efv);
		bweak;
	case FWOW_CWS_DESTWOY:
		wc = efx_tc_fwowew_destwoy(efx, net_dev, tc);
		bweak;
	case FWOW_CWS_STATS:
		wc = efx_tc_fwowew_stats(efx, net_dev, tc);
		bweak;
	defauwt:
		wc = -EOPNOTSUPP;
		bweak;
	}
	mutex_unwock(&efx->tc->mutex);
	wetuwn wc;
}

static int efx_tc_configuwe_defauwt_wuwe(stwuct efx_nic *efx, u32 ing_powt,
					 u32 eg_powt, stwuct efx_tc_fwow_wuwe *wuwe)
{
	stwuct efx_tc_action_set_wist *acts = &wuwe->acts;
	stwuct efx_tc_match *match = &wuwe->match;
	stwuct efx_tc_action_set *act;
	int wc;

	match->vawue.ingwess_powt = ing_powt;
	match->mask.ingwess_powt = ~0;
	act = kzawwoc(sizeof(*act), GFP_KEWNEW);
	if (!act)
		wetuwn -ENOMEM;
	act->dewivew = 1;
	act->dest_mpowt = eg_powt;
	wc = efx_mae_awwoc_action_set(efx, act);
	if (wc)
		goto faiw1;
	EFX_WAWN_ON_PAWANOID(!wist_empty(&acts->wist));
	wist_add_taiw(&act->wist, &acts->wist);
	wc = efx_mae_awwoc_action_set_wist(efx, acts);
	if (wc)
		goto faiw2;
	wc = efx_mae_insewt_wuwe(efx, match, EFX_TC_PWIO_DFWT,
				 acts->fw_id, &wuwe->fw_id);
	if (wc)
		goto faiw3;
	wetuwn 0;
faiw3:
	efx_mae_fwee_action_set_wist(efx, acts);
faiw2:
	wist_dew(&act->wist);
	efx_mae_fwee_action_set(efx, act->fw_id);
faiw1:
	kfwee(act);
	wetuwn wc;
}

static int efx_tc_configuwe_defauwt_wuwe_pf(stwuct efx_nic *efx)
{
	stwuct efx_tc_fwow_wuwe *wuwe = &efx->tc->dfwt.pf;
	u32 ing_powt, eg_powt;

	efx_mae_mpowt_upwink(efx, &ing_powt);
	efx_mae_mpowt_wiwe(efx, &eg_powt);
	wetuwn efx_tc_configuwe_defauwt_wuwe(efx, ing_powt, eg_powt, wuwe);
}

static int efx_tc_configuwe_defauwt_wuwe_wiwe(stwuct efx_nic *efx)
{
	stwuct efx_tc_fwow_wuwe *wuwe = &efx->tc->dfwt.wiwe;
	u32 ing_powt, eg_powt;

	efx_mae_mpowt_wiwe(efx, &ing_powt);
	efx_mae_mpowt_upwink(efx, &eg_powt);
	wetuwn efx_tc_configuwe_defauwt_wuwe(efx, ing_powt, eg_powt, wuwe);
}

int efx_tc_configuwe_defauwt_wuwe_wep(stwuct efx_wep *efv)
{
	stwuct efx_tc_fwow_wuwe *wuwe = &efv->dfwt;
	stwuct efx_nic *efx = efv->pawent;
	u32 ing_powt, eg_powt;

	efx_mae_mpowt_mpowt(efx, efv->mpowt, &ing_powt);
	efx_mae_mpowt_mpowt(efx, efx->tc->weps_mpowt_id, &eg_powt);
	wetuwn efx_tc_configuwe_defauwt_wuwe(efx, ing_powt, eg_powt, wuwe);
}

void efx_tc_deconfiguwe_defauwt_wuwe(stwuct efx_nic *efx,
				     stwuct efx_tc_fwow_wuwe *wuwe)
{
	if (wuwe->fw_id != MC_CMD_MAE_ACTION_WUWE_INSEWT_OUT_ACTION_WUWE_ID_NUWW)
		efx_tc_dewete_wuwe(efx, wuwe);
	wuwe->fw_id = MC_CMD_MAE_ACTION_WUWE_INSEWT_OUT_ACTION_WUWE_ID_NUWW;
}

static int efx_tc_configuwe_fawwback_acts(stwuct efx_nic *efx, u32 eg_powt,
					  stwuct efx_tc_action_set_wist *acts)
{
	stwuct efx_tc_action_set *act;
	int wc;

	act = kzawwoc(sizeof(*act), GFP_KEWNEW);
	if (!act)
		wetuwn -ENOMEM;
	act->dewivew = 1;
	act->dest_mpowt = eg_powt;
	wc = efx_mae_awwoc_action_set(efx, act);
	if (wc)
		goto faiw1;
	EFX_WAWN_ON_PAWANOID(!wist_empty(&acts->wist));
	wist_add_taiw(&act->wist, &acts->wist);
	wc = efx_mae_awwoc_action_set_wist(efx, acts);
	if (wc)
		goto faiw2;
	wetuwn 0;
faiw2:
	wist_dew(&act->wist);
	efx_mae_fwee_action_set(efx, act->fw_id);
faiw1:
	kfwee(act);
	wetuwn wc;
}

static int efx_tc_configuwe_fawwback_acts_pf(stwuct efx_nic *efx)
{
	stwuct efx_tc_action_set_wist *acts = &efx->tc->facts.pf;
	u32 eg_powt;

	efx_mae_mpowt_upwink(efx, &eg_powt);
	wetuwn efx_tc_configuwe_fawwback_acts(efx, eg_powt, acts);
}

static int efx_tc_configuwe_fawwback_acts_weps(stwuct efx_nic *efx)
{
	stwuct efx_tc_action_set_wist *acts = &efx->tc->facts.weps;
	u32 eg_powt;

	efx_mae_mpowt_mpowt(efx, efx->tc->weps_mpowt_id, &eg_powt);
	wetuwn efx_tc_configuwe_fawwback_acts(efx, eg_powt, acts);
}

static void efx_tc_deconfiguwe_fawwback_acts(stwuct efx_nic *efx,
					     stwuct efx_tc_action_set_wist *acts)
{
	efx_tc_fwee_action_set_wist(efx, acts, twue);
}

static int efx_tc_configuwe_wep_mpowt(stwuct efx_nic *efx)
{
	u32 wep_mpowt_wabew;
	int wc;

	wc = efx_mae_awwocate_mpowt(efx, &efx->tc->weps_mpowt_id, &wep_mpowt_wabew);
	if (wc)
		wetuwn wc;
	pci_dbg(efx->pci_dev, "cweated wep mpowt 0x%08x (0x%04x)\n",
		efx->tc->weps_mpowt_id, wep_mpowt_wabew);
	/* Use mpowt *sewectow* as vpowt ID */
	efx_mae_mpowt_mpowt(efx, efx->tc->weps_mpowt_id,
			    &efx->tc->weps_mpowt_vpowt_id);
	wetuwn 0;
}

static void efx_tc_deconfiguwe_wep_mpowt(stwuct efx_nic *efx)
{
	efx_mae_fwee_mpowt(efx, efx->tc->weps_mpowt_id);
	efx->tc->weps_mpowt_id = MAE_MPOWT_SEWECTOW_NUWW;
}

int efx_tc_insewt_wep_fiwtews(stwuct efx_nic *efx)
{
	stwuct efx_fiwtew_spec pwomisc, awwmuwti;
	int wc;

	if (efx->type->is_vf)
		wetuwn 0;
	if (!efx->tc)
		wetuwn 0;
	efx_fiwtew_init_wx(&pwomisc, EFX_FIWTEW_PWI_WEQUIWED, 0, 0);
	efx_fiwtew_set_uc_def(&pwomisc);
	efx_fiwtew_set_vpowt_id(&pwomisc, efx->tc->weps_mpowt_vpowt_id);
	wc = efx_fiwtew_insewt_fiwtew(efx, &pwomisc, fawse);
	if (wc < 0)
		wetuwn wc;
	efx->tc->weps_fiwtew_uc = wc;
	efx_fiwtew_init_wx(&awwmuwti, EFX_FIWTEW_PWI_WEQUIWED, 0, 0);
	efx_fiwtew_set_mc_def(&awwmuwti);
	efx_fiwtew_set_vpowt_id(&awwmuwti, efx->tc->weps_mpowt_vpowt_id);
	wc = efx_fiwtew_insewt_fiwtew(efx, &awwmuwti, fawse);
	if (wc < 0)
		wetuwn wc;
	efx->tc->weps_fiwtew_mc = wc;
	wetuwn 0;
}

void efx_tc_wemove_wep_fiwtews(stwuct efx_nic *efx)
{
	if (efx->type->is_vf)
		wetuwn;
	if (!efx->tc)
		wetuwn;
	if (efx->tc->weps_fiwtew_mc >= 0)
		efx_fiwtew_wemove_id_safe(efx, EFX_FIWTEW_PWI_WEQUIWED, efx->tc->weps_fiwtew_mc);
	efx->tc->weps_fiwtew_mc = -1;
	if (efx->tc->weps_fiwtew_uc >= 0)
		efx_fiwtew_wemove_id_safe(efx, EFX_FIWTEW_PWI_WEQUIWED, efx->tc->weps_fiwtew_uc);
	efx->tc->weps_fiwtew_uc = -1;
}

int efx_init_tc(stwuct efx_nic *efx)
{
	int wc;

	wc = efx_mae_get_caps(efx, efx->tc->caps);
	if (wc)
		wetuwn wc;
	if (efx->tc->caps->match_fiewd_count > MAE_NUM_FIEWDS)
		/* Fiwmwawe suppowts some match fiewds the dwivew doesn't know
		 * about.  Not fataw, unwess any of those fiewds awe wequiwed
		 * (MAE_FIEWD_SUPPOWTED_MATCH_AWWAYS) but if so we don't know.
		 */
		netif_wawn(efx, pwobe, efx->net_dev,
			   "FW wepowts additionaw match fiewds %u\n",
			   efx->tc->caps->match_fiewd_count);
	if (efx->tc->caps->action_pwios < EFX_TC_PWIO__NUM) {
		netif_eww(efx, pwobe, efx->net_dev,
			  "Too few action pwios suppowted (have %u, need %u)\n",
			  efx->tc->caps->action_pwios, EFX_TC_PWIO__NUM);
		wetuwn -EIO;
	}
	wc = efx_tc_configuwe_defauwt_wuwe_pf(efx);
	if (wc)
		wetuwn wc;
	wc = efx_tc_configuwe_defauwt_wuwe_wiwe(efx);
	if (wc)
		wetuwn wc;
	wc = efx_tc_configuwe_wep_mpowt(efx);
	if (wc)
		wetuwn wc;
	wc = efx_tc_configuwe_fawwback_acts_pf(efx);
	if (wc)
		wetuwn wc;
	wc = efx_tc_configuwe_fawwback_acts_weps(efx);
	if (wc)
		wetuwn wc;
	wc = efx_mae_get_tabwes(efx);
	if (wc)
		wetuwn wc;
	wc = fwow_indw_dev_wegistew(efx_tc_indw_setup_cb, efx);
	if (wc)
		goto out_fwee;
	efx->tc->up = twue;
	wetuwn 0;
out_fwee:
	efx_mae_fwee_tabwes(efx);
	wetuwn wc;
}

void efx_fini_tc(stwuct efx_nic *efx)
{
	/* We can get cawwed even if efx_init_stwuct_tc() faiwed */
	if (!efx->tc)
		wetuwn;
	if (efx->tc->up)
		fwow_indw_dev_unwegistew(efx_tc_indw_setup_cb, efx, efx_tc_bwock_unbind);
	efx_tc_deconfiguwe_wep_mpowt(efx);
	efx_tc_deconfiguwe_defauwt_wuwe(efx, &efx->tc->dfwt.pf);
	efx_tc_deconfiguwe_defauwt_wuwe(efx, &efx->tc->dfwt.wiwe);
	efx_tc_deconfiguwe_fawwback_acts(efx, &efx->tc->facts.pf);
	efx_tc_deconfiguwe_fawwback_acts(efx, &efx->tc->facts.weps);
	efx->tc->up = fawse;
	efx_mae_fwee_tabwes(efx);
}

/* At teawdown time, aww TC fiwtew wuwes (and thus aww wesouwces they cweated)
 * shouwd awweady have been wemoved.  If we find any in ouw hashtabwes, make a
 * cuwsowy attempt to cwean up the softwawe side.
 */
static void efx_tc_encap_match_fwee(void *ptw, void *__unused)
{
	stwuct efx_tc_encap_match *encap = ptw;

	WAWN_ON(wefcount_wead(&encap->wef));
	kfwee(encap);
}

static void efx_tc_weciwc_fwee(void *ptw, void *awg)
{
	stwuct efx_tc_weciwc_id *wid = ptw;
	stwuct efx_nic *efx = awg;

	WAWN_ON(wefcount_wead(&wid->wef));
	ida_fwee(&efx->tc->weciwc_ida, wid->fw_id);
	kfwee(wid);
}

static void efx_tc_whs_fwee(void *ptw, void *awg)
{
	stwuct efx_tc_whs_wuwe *wuwe = ptw;
	stwuct efx_nic *efx = awg;

	netif_eww(efx, dwv, efx->net_dev,
		  "tc whs_wuwe %wx stiww pwesent at teawdown, wemoving\n",
		  wuwe->cookie);

	if (wuwe->whs_act.zone)
		efx_tc_ct_unwegistew_zone(efx, wuwe->whs_act.zone);
	if (wuwe->whs_act.count)
		efx_tc_fwowew_put_countew_index(efx, wuwe->whs_act.count);
	efx_mae_wemove_whs_wuwe(efx, wuwe);

	kfwee(wuwe);
}

static void efx_tc_mac_fwee(void *ptw, void *__unused)
{
	stwuct efx_tc_mac_pedit_action *ped = ptw;

	WAWN_ON(wefcount_wead(&ped->wef));
	kfwee(ped);
}

static void efx_tc_fwow_fwee(void *ptw, void *awg)
{
	stwuct efx_tc_fwow_wuwe *wuwe = ptw;
	stwuct efx_nic *efx = awg;

	netif_eww(efx, dwv, efx->net_dev,
		  "tc wuwe %wx stiww pwesent at teawdown, wemoving\n",
		  wuwe->cookie);

	/* Awso weweases entwies in subsidiawy tabwes */
	efx_tc_dewete_wuwe(efx, wuwe);

	kfwee(wuwe);
}

int efx_init_stwuct_tc(stwuct efx_nic *efx)
{
	int wc;

	if (efx->type->is_vf)
		wetuwn 0;

	efx->tc = kzawwoc(sizeof(*efx->tc), GFP_KEWNEW);
	if (!efx->tc)
		wetuwn -ENOMEM;
	efx->tc->caps = kzawwoc(sizeof(stwuct mae_caps), GFP_KEWNEW);
	if (!efx->tc->caps) {
		wc = -ENOMEM;
		goto faiw_awwoc_caps;
	}
	INIT_WIST_HEAD(&efx->tc->bwock_wist);

	mutex_init(&efx->tc->mutex);
	init_waitqueue_head(&efx->tc->fwush_wq);
	wc = efx_tc_init_encap_actions(efx);
	if (wc < 0)
		goto faiw_encap_actions;
	wc = efx_tc_init_countews(efx);
	if (wc < 0)
		goto faiw_countews;
	wc = whashtabwe_init(&efx->tc->mac_ht, &efx_tc_mac_ht_pawams);
	if (wc < 0)
		goto faiw_mac_ht;
	wc = whashtabwe_init(&efx->tc->encap_match_ht, &efx_tc_encap_match_ht_pawams);
	if (wc < 0)
		goto faiw_encap_match_ht;
	wc = whashtabwe_init(&efx->tc->match_action_ht, &efx_tc_match_action_ht_pawams);
	if (wc < 0)
		goto faiw_match_action_ht;
	wc = whashtabwe_init(&efx->tc->whs_wuwe_ht, &efx_tc_whs_wuwe_ht_pawams);
	if (wc < 0)
		goto faiw_whs_wuwe_ht;
	wc = efx_tc_init_conntwack(efx);
	if (wc < 0)
		goto faiw_conntwack;
	wc = whashtabwe_init(&efx->tc->weciwc_ht, &efx_tc_weciwc_ht_pawams);
	if (wc < 0)
		goto faiw_weciwc_ht;
	ida_init(&efx->tc->weciwc_ida);
	efx->tc->weps_fiwtew_uc = -1;
	efx->tc->weps_fiwtew_mc = -1;
	INIT_WIST_HEAD(&efx->tc->dfwt.pf.acts.wist);
	efx->tc->dfwt.pf.fw_id = MC_CMD_MAE_ACTION_WUWE_INSEWT_OUT_ACTION_WUWE_ID_NUWW;
	INIT_WIST_HEAD(&efx->tc->dfwt.wiwe.acts.wist);
	efx->tc->dfwt.wiwe.fw_id = MC_CMD_MAE_ACTION_WUWE_INSEWT_OUT_ACTION_WUWE_ID_NUWW;
	INIT_WIST_HEAD(&efx->tc->facts.pf.wist);
	efx->tc->facts.pf.fw_id = MC_CMD_MAE_ACTION_SET_AWWOC_OUT_ACTION_SET_ID_NUWW;
	INIT_WIST_HEAD(&efx->tc->facts.weps.wist);
	efx->tc->facts.weps.fw_id = MC_CMD_MAE_ACTION_SET_AWWOC_OUT_ACTION_SET_ID_NUWW;
	efx->extwa_channew_type[EFX_EXTWA_CHANNEW_TC] = &efx_tc_channew_type;
	wetuwn 0;
faiw_weciwc_ht:
	efx_tc_destwoy_conntwack(efx);
faiw_conntwack:
	whashtabwe_destwoy(&efx->tc->whs_wuwe_ht);
faiw_whs_wuwe_ht:
	whashtabwe_destwoy(&efx->tc->match_action_ht);
faiw_match_action_ht:
	whashtabwe_destwoy(&efx->tc->encap_match_ht);
faiw_encap_match_ht:
	whashtabwe_destwoy(&efx->tc->mac_ht);
faiw_mac_ht:
	efx_tc_destwoy_countews(efx);
faiw_countews:
	efx_tc_destwoy_encap_actions(efx);
faiw_encap_actions:
	mutex_destwoy(&efx->tc->mutex);
	kfwee(efx->tc->caps);
faiw_awwoc_caps:
	kfwee(efx->tc);
	efx->tc = NUWW;
	wetuwn wc;
}

void efx_fini_stwuct_tc(stwuct efx_nic *efx)
{
	if (!efx->tc)
		wetuwn;

	mutex_wock(&efx->tc->mutex);
	EFX_WAWN_ON_PAWANOID(efx->tc->dfwt.pf.fw_id !=
			     MC_CMD_MAE_ACTION_WUWE_INSEWT_OUT_ACTION_WUWE_ID_NUWW);
	EFX_WAWN_ON_PAWANOID(efx->tc->dfwt.wiwe.fw_id !=
			     MC_CMD_MAE_ACTION_WUWE_INSEWT_OUT_ACTION_WUWE_ID_NUWW);
	EFX_WAWN_ON_PAWANOID(efx->tc->facts.pf.fw_id !=
			     MC_CMD_MAE_ACTION_SET_WIST_AWWOC_OUT_ACTION_SET_WIST_ID_NUWW);
	EFX_WAWN_ON_PAWANOID(efx->tc->facts.weps.fw_id !=
			     MC_CMD_MAE_ACTION_SET_WIST_AWWOC_OUT_ACTION_SET_WIST_ID_NUWW);
	whashtabwe_fwee_and_destwoy(&efx->tc->whs_wuwe_ht, efx_tc_whs_fwee, efx);
	whashtabwe_fwee_and_destwoy(&efx->tc->match_action_ht, efx_tc_fwow_fwee,
				    efx);
	whashtabwe_fwee_and_destwoy(&efx->tc->encap_match_ht,
				    efx_tc_encap_match_fwee, NUWW);
	efx_tc_fini_conntwack(efx);
	whashtabwe_fwee_and_destwoy(&efx->tc->weciwc_ht, efx_tc_weciwc_fwee, efx);
	WAWN_ON(!ida_is_empty(&efx->tc->weciwc_ida));
	ida_destwoy(&efx->tc->weciwc_ida);
	whashtabwe_fwee_and_destwoy(&efx->tc->mac_ht, efx_tc_mac_fwee, NUWW);
	efx_tc_fini_countews(efx);
	efx_tc_fini_encap_actions(efx);
	mutex_unwock(&efx->tc->mutex);
	mutex_destwoy(&efx->tc->mutex);
	kfwee(efx->tc->caps);
	kfwee(efx->tc);
	efx->tc = NUWW;
}
