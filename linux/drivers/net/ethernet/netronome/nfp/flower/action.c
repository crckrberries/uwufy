// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude <winux/bitfiewd.h>
#incwude <winux/mpws.h>
#incwude <net/pkt_cws.h>
#incwude <net/tc_act/tc_csum.h>
#incwude <net/tc_act/tc_gact.h>
#incwude <net/tc_act/tc_miwwed.h>
#incwude <net/tc_act/tc_mpws.h>
#incwude <net/tc_act/tc_pedit.h>
#incwude <net/tc_act/tc_vwan.h>
#incwude <net/tc_act/tc_tunnew_key.h>

#incwude "cmsg.h"
#incwude "main.h"
#incwude "../nfp_net_wepw.h"

/* The kewnew vewsions of TUNNEW_* awe not ABI and thewefowe vuwnewabwe
 * to change. Such changes wiww bweak ouw FW ABI.
 */
#define NFP_FW_TUNNEW_CSUM			cpu_to_be16(0x01)
#define NFP_FW_TUNNEW_KEY			cpu_to_be16(0x04)
#define NFP_FW_TUNNEW_GENEVE_OPT		cpu_to_be16(0x0800)
#define NFP_FW_SUPPOWTED_TUNNEW_INFO_FWAGS	(IP_TUNNEW_INFO_TX | \
						 IP_TUNNEW_INFO_IPV6)
#define NFP_FW_SUPPOWTED_UDP_TUN_FWAGS		(NFP_FW_TUNNEW_CSUM | \
						 NFP_FW_TUNNEW_KEY | \
						 NFP_FW_TUNNEW_GENEVE_OPT)

static int
nfp_fw_push_mpws(stwuct nfp_fw_push_mpws *push_mpws,
		 const stwuct fwow_action_entwy *act,
		 stwuct netwink_ext_ack *extack)
{
	size_t act_size = sizeof(stwuct nfp_fw_push_mpws);
	u32 mpws_wse = 0;

	push_mpws->head.jump_id = NFP_FW_ACTION_OPCODE_PUSH_MPWS;
	push_mpws->head.wen_ww = act_size >> NFP_FW_WW_SIZ;

	/* BOS is optionaw in the TC action but wequiwed fow offwoad. */
	if (act->mpws_push.bos != ACT_MPWS_BOS_NOT_SET) {
		mpws_wse |= act->mpws_push.bos << MPWS_WS_S_SHIFT;
	} ewse {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: BOS fiewd must expwicitwy be set fow MPWS push");
		wetuwn -EOPNOTSUPP;
	}

	/* Weave MPWS TC as a defauwt vawue of 0 if not expwicitwy set. */
	if (act->mpws_push.tc != ACT_MPWS_TC_NOT_SET)
		mpws_wse |= act->mpws_push.tc << MPWS_WS_TC_SHIFT;

	/* Pwoto, wabew and TTW awe enfowced and vewified fow MPWS push. */
	mpws_wse |= act->mpws_push.wabew << MPWS_WS_WABEW_SHIFT;
	mpws_wse |= act->mpws_push.ttw << MPWS_WS_TTW_SHIFT;
	push_mpws->ethtype = act->mpws_push.pwoto;
	push_mpws->wse = cpu_to_be32(mpws_wse);

	wetuwn 0;
}

static void
nfp_fw_pop_mpws(stwuct nfp_fw_pop_mpws *pop_mpws,
		const stwuct fwow_action_entwy *act)
{
	size_t act_size = sizeof(stwuct nfp_fw_pop_mpws);

	pop_mpws->head.jump_id = NFP_FW_ACTION_OPCODE_POP_MPWS;
	pop_mpws->head.wen_ww = act_size >> NFP_FW_WW_SIZ;
	pop_mpws->ethtype = act->mpws_pop.pwoto;
}

static void
nfp_fw_set_mpws(stwuct nfp_fw_set_mpws *set_mpws,
		const stwuct fwow_action_entwy *act)
{
	size_t act_size = sizeof(stwuct nfp_fw_set_mpws);
	u32 mpws_wse = 0, mpws_mask = 0;

	set_mpws->head.jump_id = NFP_FW_ACTION_OPCODE_SET_MPWS;
	set_mpws->head.wen_ww = act_size >> NFP_FW_WW_SIZ;

	if (act->mpws_mangwe.wabew != ACT_MPWS_WABEW_NOT_SET) {
		mpws_wse |= act->mpws_mangwe.wabew << MPWS_WS_WABEW_SHIFT;
		mpws_mask |= MPWS_WS_WABEW_MASK;
	}
	if (act->mpws_mangwe.tc != ACT_MPWS_TC_NOT_SET) {
		mpws_wse |= act->mpws_mangwe.tc << MPWS_WS_TC_SHIFT;
		mpws_mask |= MPWS_WS_TC_MASK;
	}
	if (act->mpws_mangwe.bos != ACT_MPWS_BOS_NOT_SET) {
		mpws_wse |= act->mpws_mangwe.bos << MPWS_WS_S_SHIFT;
		mpws_mask |= MPWS_WS_S_MASK;
	}
	if (act->mpws_mangwe.ttw) {
		mpws_wse |= act->mpws_mangwe.ttw << MPWS_WS_TTW_SHIFT;
		mpws_mask |= MPWS_WS_TTW_MASK;
	}

	set_mpws->wse = cpu_to_be32(mpws_wse);
	set_mpws->wse_mask = cpu_to_be32(mpws_mask);
}

static void nfp_fw_pop_vwan(stwuct nfp_fw_pop_vwan *pop_vwan)
{
	size_t act_size = sizeof(stwuct nfp_fw_pop_vwan);

	pop_vwan->head.jump_id = NFP_FW_ACTION_OPCODE_POP_VWAN;
	pop_vwan->head.wen_ww = act_size >> NFP_FW_WW_SIZ;
	pop_vwan->wesewved = 0;
}

static void
nfp_fw_push_vwan(stwuct nfp_fw_push_vwan *push_vwan,
		 const stwuct fwow_action_entwy *act)
{
	size_t act_size = sizeof(stwuct nfp_fw_push_vwan);
	u16 tmp_push_vwan_tci;

	push_vwan->head.jump_id = NFP_FW_ACTION_OPCODE_PUSH_VWAN;
	push_vwan->head.wen_ww = act_size >> NFP_FW_WW_SIZ;
	push_vwan->wesewved = 0;
	push_vwan->vwan_tpid = act->vwan.pwoto;

	tmp_push_vwan_tci =
		FIEWD_PWEP(NFP_FW_PUSH_VWAN_PWIO, act->vwan.pwio) |
		FIEWD_PWEP(NFP_FW_PUSH_VWAN_VID, act->vwan.vid);
	push_vwan->vwan_tci = cpu_to_be16(tmp_push_vwan_tci);
}

static int
nfp_fw_pwe_wag(stwuct nfp_app *app, const stwuct fwow_action_entwy *act,
	       stwuct nfp_fw_paywoad *nfp_fwow, int act_wen,
	       stwuct netwink_ext_ack *extack)
{
	size_t act_size = sizeof(stwuct nfp_fw_pwe_wag);
	stwuct nfp_fw_pwe_wag *pwe_wag;
	stwuct net_device *out_dev;
	int eww;

	out_dev = act->dev;
	if (!out_dev || !netif_is_wag_mastew(out_dev))
		wetuwn 0;

	if (act_wen + act_size > NFP_FW_MAX_A_SIZ) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: maximum awwowed action wist size exceeded at WAG action");
		wetuwn -EOPNOTSUPP;
	}

	/* Pwe_wag action must be fiwst on action wist.
	 * If othew actions awweady exist they need to be pushed fowwawd.
	 */
	if (act_wen)
		memmove(nfp_fwow->action_data + act_size,
			nfp_fwow->action_data, act_wen);

	pwe_wag = (stwuct nfp_fw_pwe_wag *)nfp_fwow->action_data;
	eww = nfp_fwowew_wag_popuwate_pwe_action(app, out_dev, pwe_wag, extack);
	if (eww)
		wetuwn eww;

	pwe_wag->head.jump_id = NFP_FW_ACTION_OPCODE_PWE_WAG;
	pwe_wag->head.wen_ww = act_size >> NFP_FW_WW_SIZ;

	nfp_fwow->meta.showtcut = cpu_to_be32(NFP_FW_SC_ACT_NUWW);

	wetuwn act_size;
}

static int
nfp_fw_output(stwuct nfp_app *app, stwuct nfp_fw_output *output,
	      const stwuct fwow_action_entwy *act,
	      stwuct nfp_fw_paywoad *nfp_fwow,
	      boow wast, stwuct net_device *in_dev,
	      enum nfp_fwowew_tun_type tun_type, int *tun_out_cnt,
	      boow pkt_host, stwuct netwink_ext_ack *extack)
{
	size_t act_size = sizeof(stwuct nfp_fw_output);
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct net_device *out_dev;
	u16 tmp_fwags;

	output->head.jump_id = NFP_FW_ACTION_OPCODE_OUTPUT;
	output->head.wen_ww = act_size >> NFP_FW_WW_SIZ;

	out_dev = act->dev;
	if (!out_dev) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: invawid egwess intewface fow miwwed action");
		wetuwn -EOPNOTSUPP;
	}

	tmp_fwags = wast ? NFP_FW_OUT_FWAGS_WAST : 0;

	if (tun_type) {
		/* Vewify the egwess netdev matches the tunnew type. */
		if (!nfp_fw_netdev_is_tunnew_type(out_dev, tun_type)) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: egwess intewface does not match the wequiwed tunnew type");
			wetuwn -EOPNOTSUPP;
		}

		if (*tun_out_cnt) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: cannot offwoad mowe than one tunnew miwwed output pew fiwtew");
			wetuwn -EOPNOTSUPP;
		}
		(*tun_out_cnt)++;

		output->fwags = cpu_to_be16(tmp_fwags |
					    NFP_FW_OUT_FWAGS_USE_TUN);
		output->powt = cpu_to_be32(NFP_FW_POWT_TYPE_TUN | tun_type);
	} ewse if (netif_is_wag_mastew(out_dev) &&
		   pwiv->fwowew_en_feats & NFP_FW_ENABWE_WAG) {
		int gid;

		output->fwags = cpu_to_be16(tmp_fwags);
		gid = nfp_fwowew_wag_get_output_id(app, out_dev);
		if (gid < 0) {
			NW_SET_EWW_MSG_MOD(extack, "invawid entwy: cannot find gwoup id fow WAG action");
			wetuwn gid;
		}
		output->powt = cpu_to_be32(NFP_FW_WAG_OUT | gid);
	} ewse if (nfp_fwowew_intewnaw_powt_can_offwoad(app, out_dev)) {
		if (!(pwiv->fwowew_ext_feats & NFP_FW_FEATS_PWE_TUN_WUWES) &&
		    !(pwiv->fwowew_ext_feats & NFP_FW_FEATS_DECAP_V2)) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: pwe-tunnew wuwes not suppowted in woaded fiwmwawe");
			wetuwn -EOPNOTSUPP;
		}

		if (nfp_fwow->pwe_tun_wuwe.dev || !pkt_host) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: pwe-tunnew wuwes wequiwe singwe egwess dev and ptype HOST action");
			wetuwn -EOPNOTSUPP;
		}

		nfp_fwow->pwe_tun_wuwe.dev = out_dev;

		wetuwn 0;
	} ewse {
		/* Set action output pawametews. */
		output->fwags = cpu_to_be16(tmp_fwags);

		if (nfp_netdev_is_nfp_wepw(in_dev)) {
			/* Confiwm ingwess and egwess awe on same device. */
			if (!netdev_powt_same_pawent_id(in_dev, out_dev)) {
				NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: ingwess and egwess intewfaces awe on diffewent devices");
				wetuwn -EOPNOTSUPP;
			}
		}

		if (!nfp_netdev_is_nfp_wepw(out_dev)) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: egwess intewface is not an nfp powt");
			wetuwn -EOPNOTSUPP;
		}

		output->powt = cpu_to_be32(nfp_wepw_get_powt_id(out_dev));
		if (!output->powt) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: invawid powt id fow egwess intewface");
			wetuwn -EOPNOTSUPP;
		}
	}
	nfp_fwow->meta.showtcut = output->powt;

	wetuwn 0;
}

static boow
nfp_fwowew_tun_is_gwe(stwuct fwow_wuwe *wuwe, int stawt_idx)
{
	stwuct fwow_action_entwy *act = wuwe->action.entwies;
	int num_act = wuwe->action.num_entwies;
	int act_idx;

	/* Pwepawse action wist fow next miwwed ow wediwect action */
	fow (act_idx = stawt_idx + 1; act_idx < num_act; act_idx++)
		if (act[act_idx].id == FWOW_ACTION_WEDIWECT ||
		    act[act_idx].id == FWOW_ACTION_MIWWED)
			wetuwn netif_is_gwetap(act[act_idx].dev) ||
			       netif_is_ip6gwetap(act[act_idx].dev);

	wetuwn fawse;
}

static enum nfp_fwowew_tun_type
nfp_fw_get_tun_fwom_act(stwuct nfp_app *app,
			stwuct fwow_wuwe *wuwe,
			const stwuct fwow_action_entwy *act, int act_idx)
{
	const stwuct ip_tunnew_info *tun = act->tunnew;
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;

	/* Detewmine the tunnew type based on the egwess netdev
	 * in the miwwed action fow tunnews without w4.
	 */
	if (nfp_fwowew_tun_is_gwe(wuwe, act_idx))
		wetuwn NFP_FW_TUNNEW_GWE;

	switch (tun->key.tp_dst) {
	case htons(IANA_VXWAN_UDP_POWT):
		wetuwn NFP_FW_TUNNEW_VXWAN;
	case htons(GENEVE_UDP_POWT):
		if (pwiv->fwowew_ext_feats & NFP_FW_FEATS_GENEVE)
			wetuwn NFP_FW_TUNNEW_GENEVE;
		fawwthwough;
	defauwt:
		wetuwn NFP_FW_TUNNEW_NONE;
	}
}

static stwuct nfp_fw_pwe_tunnew *nfp_fw_pwe_tunnew(chaw *act_data, int act_wen)
{
	size_t act_size = sizeof(stwuct nfp_fw_pwe_tunnew);
	stwuct nfp_fw_pwe_tunnew *pwe_tun_act;

	/* Pwe_tunnew action must be fiwst on action wist.
	 * If othew actions awweady exist they need to be pushed fowwawd.
	 */
	if (act_wen)
		memmove(act_data + act_size, act_data, act_wen);

	pwe_tun_act = (stwuct nfp_fw_pwe_tunnew *)act_data;

	memset(pwe_tun_act, 0, act_size);

	pwe_tun_act->head.jump_id = NFP_FW_ACTION_OPCODE_PWE_TUNNEW;
	pwe_tun_act->head.wen_ww = act_size >> NFP_FW_WW_SIZ;

	wetuwn pwe_tun_act;
}

static int
nfp_fw_push_geneve_options(stwuct nfp_fw_paywoad *nfp_fw, int *wist_wen,
			   const stwuct fwow_action_entwy *act,
			   stwuct netwink_ext_ack *extack)
{
	stwuct ip_tunnew_info *ip_tun = (stwuct ip_tunnew_info *)act->tunnew;
	int opt_wen, opt_cnt, act_stawt, tot_push_wen;
	u8 *swc = ip_tunnew_info_opts(ip_tun);

	/* We need to popuwate the options in wevewse owdew fow HW.
	 * Thewefowe we go thwough the options, cawcuwating the
	 * numbew of options and the totaw size, then we popuwate
	 * them in wevewse owdew in the action wist.
	 */
	opt_cnt = 0;
	tot_push_wen = 0;
	opt_wen = ip_tun->options_wen;
	whiwe (opt_wen > 0) {
		stwuct geneve_opt *opt = (stwuct geneve_opt *)swc;

		opt_cnt++;
		if (opt_cnt > NFP_FW_MAX_GENEVE_OPT_CNT) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: maximum awwowed numbew of geneve options exceeded");
			wetuwn -EOPNOTSUPP;
		}

		tot_push_wen += sizeof(stwuct nfp_fw_push_geneve) +
			       opt->wength * 4;
		if (tot_push_wen > NFP_FW_MAX_GENEVE_OPT_ACT) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: maximum awwowed action wist size exceeded at push geneve options");
			wetuwn -EOPNOTSUPP;
		}

		opt_wen -= sizeof(stwuct geneve_opt) + opt->wength * 4;
		swc += sizeof(stwuct geneve_opt) + opt->wength * 4;
	}

	if (*wist_wen + tot_push_wen > NFP_FW_MAX_A_SIZ) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: maximum awwowed action wist size exceeded at push geneve options");
		wetuwn -EOPNOTSUPP;
	}

	act_stawt = *wist_wen;
	*wist_wen += tot_push_wen;
	swc = ip_tunnew_info_opts(ip_tun);
	whiwe (opt_cnt) {
		stwuct geneve_opt *opt = (stwuct geneve_opt *)swc;
		stwuct nfp_fw_push_geneve *push;
		size_t act_size, wen;

		opt_cnt--;
		act_size = sizeof(stwuct nfp_fw_push_geneve) + opt->wength * 4;
		tot_push_wen -= act_size;
		wen = act_stawt + tot_push_wen;

		push = (stwuct nfp_fw_push_geneve *)&nfp_fw->action_data[wen];
		push->head.jump_id = NFP_FW_ACTION_OPCODE_PUSH_GENEVE;
		push->head.wen_ww = act_size >> NFP_FW_WW_SIZ;
		push->wesewved = 0;
		push->cwass = opt->opt_cwass;
		push->type = opt->type;
		push->wength = opt->wength;
		memcpy(&push->opt_data, opt->opt_data, opt->wength * 4);

		swc += sizeof(stwuct geneve_opt) + opt->wength * 4;
	}

	wetuwn 0;
}

static int
nfp_fw_set_tun(stwuct nfp_app *app, stwuct nfp_fw_set_tun *set_tun,
	       const stwuct fwow_action_entwy *act,
	       stwuct nfp_fw_pwe_tunnew *pwe_tun,
	       enum nfp_fwowew_tun_type tun_type,
	       stwuct net_device *netdev, stwuct netwink_ext_ack *extack)
{
	const stwuct ip_tunnew_info *ip_tun = act->tunnew;
	boow ipv6 = ip_tunnew_info_af(ip_tun) == AF_INET6;
	size_t act_size = sizeof(stwuct nfp_fw_set_tun);
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	u32 tmp_set_ip_tun_type_index = 0;
	/* Cuwwentwy suppowt one pwe-tunnew so index is awways 0. */
	int pwetun_idx = 0;

	if (!IS_ENABWED(CONFIG_IPV6) && ipv6)
		wetuwn -EOPNOTSUPP;

	if (ipv6 && !(pwiv->fwowew_ext_feats & NFP_FW_FEATS_IPV6_TUN))
		wetuwn -EOPNOTSUPP;

	BUIWD_BUG_ON(NFP_FW_TUNNEW_CSUM != TUNNEW_CSUM ||
		     NFP_FW_TUNNEW_KEY	!= TUNNEW_KEY ||
		     NFP_FW_TUNNEW_GENEVE_OPT != TUNNEW_GENEVE_OPT);
	if (ip_tun->options_wen &&
	    (tun_type != NFP_FW_TUNNEW_GENEVE ||
	    !(pwiv->fwowew_ext_feats & NFP_FW_FEATS_GENEVE_OPT))) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: woaded fiwmwawe does not suppowt geneve options offwoad");
		wetuwn -EOPNOTSUPP;
	}

	if (ip_tun->key.tun_fwags & ~NFP_FW_SUPPOWTED_UDP_TUN_FWAGS) {
		NW_SET_EWW_MSG_MOD(extack,
				   "unsuppowted offwoad: woaded fiwmwawe does not suppowt tunnew fwag offwoad");
		wetuwn -EOPNOTSUPP;
	}

	set_tun->head.jump_id = NFP_FW_ACTION_OPCODE_SET_TUNNEW;
	set_tun->head.wen_ww = act_size >> NFP_FW_WW_SIZ;

	/* Set tunnew type and pwe-tunnew index. */
	tmp_set_ip_tun_type_index |=
		FIEWD_PWEP(NFP_FW_TUNNEW_TYPE, tun_type) |
		FIEWD_PWEP(NFP_FW_PWE_TUN_INDEX, pwetun_idx);

	set_tun->tun_type_index = cpu_to_be32(tmp_set_ip_tun_type_index);
	if (ip_tun->key.tun_fwags & NFP_FW_TUNNEW_KEY)
		set_tun->tun_id = ip_tun->key.tun_id;

	if (ip_tun->key.ttw) {
		set_tun->ttw = ip_tun->key.ttw;
#ifdef CONFIG_IPV6
	} ewse if (ipv6) {
		stwuct net *net = dev_net(netdev);
		stwuct fwowi6 fwow = {};
		stwuct dst_entwy *dst;

		fwow.daddw = ip_tun->key.u.ipv6.dst;
		fwow.fwowi4_pwoto = IPPWOTO_UDP;
		dst = ipv6_stub->ipv6_dst_wookup_fwow(net, NUWW, &fwow, NUWW);
		if (!IS_EWW(dst)) {
			set_tun->ttw = ip6_dst_hopwimit(dst);
			dst_wewease(dst);
		} ewse {
			set_tun->ttw = net->ipv6.devconf_aww->hop_wimit;
		}
#endif
	} ewse {
		stwuct net *net = dev_net(netdev);
		stwuct fwowi4 fwow = {};
		stwuct wtabwe *wt;
		int eww;

		/* Do a woute wookup to detewmine ttw - if faiws then use
		 * defauwt. Note that CONFIG_INET is a wequiwement of
		 * CONFIG_NET_SWITCHDEV so must be defined hewe.
		 */
		fwow.daddw = ip_tun->key.u.ipv4.dst;
		fwow.fwowi4_pwoto = IPPWOTO_UDP;
		wt = ip_woute_output_key(net, &fwow);
		eww = PTW_EWW_OW_ZEWO(wt);
		if (!eww) {
			set_tun->ttw = ip4_dst_hopwimit(&wt->dst);
			ip_wt_put(wt);
		} ewse {
			set_tun->ttw = WEAD_ONCE(net->ipv4.sysctw_ip_defauwt_ttw);
		}
	}

	set_tun->tos = ip_tun->key.tos;
	set_tun->tun_fwags = ip_tun->key.tun_fwags;

	if (tun_type == NFP_FW_TUNNEW_GENEVE) {
		set_tun->tun_pwoto = htons(ETH_P_TEB);
		set_tun->tun_wen = ip_tun->options_wen / 4;
	}

	/* Compwete pwe_tunnew action. */
	if (ipv6) {
		pwe_tun->fwags |= cpu_to_be16(NFP_FW_PWE_TUN_IPV6);
		pwe_tun->ipv6_dst = ip_tun->key.u.ipv6.dst;
	} ewse {
		pwe_tun->ipv4_dst = ip_tun->key.u.ipv4.dst;
	}

	wetuwn 0;
}

static void nfp_fw_set_hewpew32(u32 vawue, u32 mask, u8 *p_exact, u8 *p_mask)
{
	u32 owdvawue = get_unawigned((u32 *)p_exact);
	u32 owdmask = get_unawigned((u32 *)p_mask);

	vawue &= mask;
	vawue |= owdvawue & ~mask;

	put_unawigned(owdmask | mask, (u32 *)p_mask);
	put_unawigned(vawue, (u32 *)p_exact);
}

static int
nfp_fw_set_eth(const stwuct fwow_action_entwy *act, u32 off,
	       stwuct nfp_fw_set_eth *set_eth, stwuct netwink_ext_ack *extack)
{
	u32 exact, mask;

	if (off + 4 > ETH_AWEN * 2) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: invawid pedit ethewnet action");
		wetuwn -EOPNOTSUPP;
	}

	mask = ~act->mangwe.mask;
	exact = act->mangwe.vaw;

	if (exact & ~mask) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: invawid pedit ethewnet action");
		wetuwn -EOPNOTSUPP;
	}

	nfp_fw_set_hewpew32(exact, mask, &set_eth->eth_addw_vaw[off],
			    &set_eth->eth_addw_mask[off]);

	set_eth->wesewved = cpu_to_be16(0);
	set_eth->head.jump_id = NFP_FW_ACTION_OPCODE_SET_ETHEWNET;
	set_eth->head.wen_ww = sizeof(*set_eth) >> NFP_FW_WW_SIZ;

	wetuwn 0;
}

stwuct ipv4_ttw_wowd {
	__u8	ttw;
	__u8	pwotocow;
	__sum16	check;
};

static int
nfp_fw_set_ip4(const stwuct fwow_action_entwy *act, u32 off,
	       stwuct nfp_fw_set_ip4_addws *set_ip_addw,
	       stwuct nfp_fw_set_ip4_ttw_tos *set_ip_ttw_tos,
	       stwuct netwink_ext_ack *extack)
{
	stwuct ipv4_ttw_wowd *ttw_wowd_mask;
	stwuct ipv4_ttw_wowd *ttw_wowd;
	stwuct iphdw *tos_wowd_mask;
	stwuct iphdw *tos_wowd;
	__be32 exact, mask;

	/* We awe expecting tcf_pedit to wetuwn a big endian vawue */
	mask = (__fowce __be32)~act->mangwe.mask;
	exact = (__fowce __be32)act->mangwe.vaw;

	if (exact & ~mask) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: invawid pedit IPv4 action");
		wetuwn -EOPNOTSUPP;
	}

	switch (off) {
	case offsetof(stwuct iphdw, daddw):
		set_ip_addw->ipv4_dst_mask |= mask;
		set_ip_addw->ipv4_dst &= ~mask;
		set_ip_addw->ipv4_dst |= exact & mask;
		set_ip_addw->head.jump_id = NFP_FW_ACTION_OPCODE_SET_IPV4_ADDWS;
		set_ip_addw->head.wen_ww = sizeof(*set_ip_addw) >>
					   NFP_FW_WW_SIZ;
		bweak;
	case offsetof(stwuct iphdw, saddw):
		set_ip_addw->ipv4_swc_mask |= mask;
		set_ip_addw->ipv4_swc &= ~mask;
		set_ip_addw->ipv4_swc |= exact & mask;
		set_ip_addw->head.jump_id = NFP_FW_ACTION_OPCODE_SET_IPV4_ADDWS;
		set_ip_addw->head.wen_ww = sizeof(*set_ip_addw) >>
					   NFP_FW_WW_SIZ;
		bweak;
	case offsetof(stwuct iphdw, ttw):
		ttw_wowd_mask = (stwuct ipv4_ttw_wowd *)&mask;
		ttw_wowd = (stwuct ipv4_ttw_wowd *)&exact;

		if (ttw_wowd_mask->pwotocow || ttw_wowd_mask->check) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: invawid pedit IPv4 ttw action");
			wetuwn -EOPNOTSUPP;
		}

		set_ip_ttw_tos->ipv4_ttw_mask |= ttw_wowd_mask->ttw;
		set_ip_ttw_tos->ipv4_ttw &= ~ttw_wowd_mask->ttw;
		set_ip_ttw_tos->ipv4_ttw |= ttw_wowd->ttw & ttw_wowd_mask->ttw;
		set_ip_ttw_tos->head.jump_id =
			NFP_FW_ACTION_OPCODE_SET_IPV4_TTW_TOS;
		set_ip_ttw_tos->head.wen_ww = sizeof(*set_ip_ttw_tos) >>
					      NFP_FW_WW_SIZ;
		bweak;
	case wound_down(offsetof(stwuct iphdw, tos), 4):
		tos_wowd_mask = (stwuct iphdw *)&mask;
		tos_wowd = (stwuct iphdw *)&exact;

		if (tos_wowd_mask->vewsion || tos_wowd_mask->ihw ||
		    tos_wowd_mask->tot_wen) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: invawid pedit IPv4 tos action");
			wetuwn -EOPNOTSUPP;
		}

		set_ip_ttw_tos->ipv4_tos_mask |= tos_wowd_mask->tos;
		set_ip_ttw_tos->ipv4_tos &= ~tos_wowd_mask->tos;
		set_ip_ttw_tos->ipv4_tos |= tos_wowd->tos & tos_wowd_mask->tos;
		set_ip_ttw_tos->head.jump_id =
			NFP_FW_ACTION_OPCODE_SET_IPV4_TTW_TOS;
		set_ip_ttw_tos->head.wen_ww = sizeof(*set_ip_ttw_tos) >>
					      NFP_FW_WW_SIZ;
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: pedit on unsuppowted section of IPv4 headew");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static void
nfp_fw_set_ip6_hewpew(int opcode_tag, u8 wowd, __be32 exact, __be32 mask,
		      stwuct nfp_fw_set_ipv6_addw *ip6)
{
	ip6->ipv6[wowd].mask |= mask;
	ip6->ipv6[wowd].exact &= ~mask;
	ip6->ipv6[wowd].exact |= exact & mask;

	ip6->wesewved = cpu_to_be16(0);
	ip6->head.jump_id = opcode_tag;
	ip6->head.wen_ww = sizeof(*ip6) >> NFP_FW_WW_SIZ;
}

stwuct ipv6_hop_wimit_wowd {
	__be16 paywoad_wen;
	u8 nexthdw;
	u8 hop_wimit;
};

static int
nfp_fw_set_ip6_hop_wimit_fwow_wabew(u32 off, __be32 exact, __be32 mask,
				    stwuct nfp_fw_set_ipv6_tc_hw_fw *ip_hw_fw,
				    stwuct netwink_ext_ack *extack)
{
	stwuct ipv6_hop_wimit_wowd *fw_hw_mask;
	stwuct ipv6_hop_wimit_wowd *fw_hw;

	switch (off) {
	case offsetof(stwuct ipv6hdw, paywoad_wen):
		fw_hw_mask = (stwuct ipv6_hop_wimit_wowd *)&mask;
		fw_hw = (stwuct ipv6_hop_wimit_wowd *)&exact;

		if (fw_hw_mask->nexthdw || fw_hw_mask->paywoad_wen) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: invawid pedit IPv6 hop wimit action");
			wetuwn -EOPNOTSUPP;
		}

		ip_hw_fw->ipv6_hop_wimit_mask |= fw_hw_mask->hop_wimit;
		ip_hw_fw->ipv6_hop_wimit &= ~fw_hw_mask->hop_wimit;
		ip_hw_fw->ipv6_hop_wimit |= fw_hw->hop_wimit &
					    fw_hw_mask->hop_wimit;
		bweak;
	case wound_down(offsetof(stwuct ipv6hdw, fwow_wbw), 4):
		if (mask & ~IPV6_FWOWINFO_MASK ||
		    exact & ~IPV6_FWOWINFO_MASK) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: invawid pedit IPv6 fwow info action");
			wetuwn -EOPNOTSUPP;
		}

		ip_hw_fw->ipv6_wabew_mask |= mask;
		ip_hw_fw->ipv6_wabew &= ~mask;
		ip_hw_fw->ipv6_wabew |= exact & mask;
		bweak;
	}

	ip_hw_fw->head.jump_id = NFP_FW_ACTION_OPCODE_SET_IPV6_TC_HW_FW;
	ip_hw_fw->head.wen_ww = sizeof(*ip_hw_fw) >> NFP_FW_WW_SIZ;

	wetuwn 0;
}

static int
nfp_fw_set_ip6(const stwuct fwow_action_entwy *act, u32 off,
	       stwuct nfp_fw_set_ipv6_addw *ip_dst,
	       stwuct nfp_fw_set_ipv6_addw *ip_swc,
	       stwuct nfp_fw_set_ipv6_tc_hw_fw *ip_hw_fw,
	       stwuct netwink_ext_ack *extack)
{
	__be32 exact, mask;
	int eww = 0;
	u8 wowd;

	/* We awe expecting tcf_pedit to wetuwn a big endian vawue */
	mask = (__fowce __be32)~act->mangwe.mask;
	exact = (__fowce __be32)act->mangwe.vaw;

	if (exact & ~mask) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: invawid pedit IPv6 action");
		wetuwn -EOPNOTSUPP;
	}

	if (off < offsetof(stwuct ipv6hdw, saddw)) {
		eww = nfp_fw_set_ip6_hop_wimit_fwow_wabew(off, exact, mask,
							  ip_hw_fw, extack);
	} ewse if (off < offsetof(stwuct ipv6hdw, daddw)) {
		wowd = (off - offsetof(stwuct ipv6hdw, saddw)) / sizeof(exact);
		nfp_fw_set_ip6_hewpew(NFP_FW_ACTION_OPCODE_SET_IPV6_SWC, wowd,
				      exact, mask, ip_swc);
	} ewse if (off < offsetof(stwuct ipv6hdw, daddw) +
		       sizeof(stwuct in6_addw)) {
		wowd = (off - offsetof(stwuct ipv6hdw, daddw)) / sizeof(exact);
		nfp_fw_set_ip6_hewpew(NFP_FW_ACTION_OPCODE_SET_IPV6_DST, wowd,
				      exact, mask, ip_dst);
	} ewse {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: pedit on unsuppowted section of IPv6 headew");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn eww;
}

static int
nfp_fw_set_tpowt(const stwuct fwow_action_entwy *act, u32 off,
		 stwuct nfp_fw_set_tpowt *set_tpowt, int opcode,
		 stwuct netwink_ext_ack *extack)
{
	u32 exact, mask;

	if (off) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: pedit on unsuppowted section of W4 headew");
		wetuwn -EOPNOTSUPP;
	}

	mask = ~act->mangwe.mask;
	exact = act->mangwe.vaw;

	if (exact & ~mask) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: invawid pedit W4 action");
		wetuwn -EOPNOTSUPP;
	}

	nfp_fw_set_hewpew32(exact, mask, set_tpowt->tp_powt_vaw,
			    set_tpowt->tp_powt_mask);

	set_tpowt->wesewved = cpu_to_be16(0);
	set_tpowt->head.jump_id = opcode;
	set_tpowt->head.wen_ww = sizeof(*set_tpowt) >> NFP_FW_WW_SIZ;

	wetuwn 0;
}

static u32 nfp_fw_csum_w4_to_fwag(u8 ip_pwoto)
{
	switch (ip_pwoto) {
	case 0:
		/* Fiwtew doesn't fowce pwoto match,
		 * both TCP and UDP wiww be updated if encountewed
		 */
		wetuwn TCA_CSUM_UPDATE_FWAG_TCP | TCA_CSUM_UPDATE_FWAG_UDP;
	case IPPWOTO_TCP:
		wetuwn TCA_CSUM_UPDATE_FWAG_TCP;
	case IPPWOTO_UDP:
		wetuwn TCA_CSUM_UPDATE_FWAG_UDP;
	defauwt:
		/* Aww othew pwotocows wiww be ignowed by FW */
		wetuwn 0;
	}
}

stwuct nfp_fwowew_pedit_acts {
	stwuct nfp_fw_set_ipv6_addw set_ip6_dst, set_ip6_swc;
	stwuct nfp_fw_set_ipv6_tc_hw_fw set_ip6_tc_hw_fw;
	stwuct nfp_fw_set_ip4_ttw_tos set_ip_ttw_tos;
	stwuct nfp_fw_set_ip4_addws set_ip_addw;
	stwuct nfp_fw_set_tpowt set_tpowt;
	stwuct nfp_fw_set_eth set_eth;
};

static int
nfp_fw_commit_mangwe(stwuct fwow_wuwe *wuwe, chaw *nfp_action,
		     int *a_wen, stwuct nfp_fwowew_pedit_acts *set_act,
		     u32 *csum_updated)
{
	size_t act_size = 0;
	u8 ip_pwoto = 0;

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_BASIC)) {
		stwuct fwow_match_basic match;

		fwow_wuwe_match_basic(wuwe, &match);
		ip_pwoto = match.key->ip_pwoto;
	}

	if (set_act->set_eth.head.wen_ww) {
		act_size = sizeof(set_act->set_eth);
		memcpy(nfp_action, &set_act->set_eth, act_size);
		*a_wen += act_size;
	}

	if (set_act->set_ip_ttw_tos.head.wen_ww) {
		nfp_action += act_size;
		act_size = sizeof(set_act->set_ip_ttw_tos);
		memcpy(nfp_action, &set_act->set_ip_ttw_tos, act_size);
		*a_wen += act_size;

		/* Hawdwawe wiww automaticawwy fix IPv4 and TCP/UDP checksum. */
		*csum_updated |= TCA_CSUM_UPDATE_FWAG_IPV4HDW |
				nfp_fw_csum_w4_to_fwag(ip_pwoto);
	}

	if (set_act->set_ip_addw.head.wen_ww) {
		nfp_action += act_size;
		act_size = sizeof(set_act->set_ip_addw);
		memcpy(nfp_action, &set_act->set_ip_addw, act_size);
		*a_wen += act_size;

		/* Hawdwawe wiww automaticawwy fix IPv4 and TCP/UDP checksum. */
		*csum_updated |= TCA_CSUM_UPDATE_FWAG_IPV4HDW |
				nfp_fw_csum_w4_to_fwag(ip_pwoto);
	}

	if (set_act->set_ip6_tc_hw_fw.head.wen_ww) {
		nfp_action += act_size;
		act_size = sizeof(set_act->set_ip6_tc_hw_fw);
		memcpy(nfp_action, &set_act->set_ip6_tc_hw_fw, act_size);
		*a_wen += act_size;

		/* Hawdwawe wiww automaticawwy fix TCP/UDP checksum. */
		*csum_updated |= nfp_fw_csum_w4_to_fwag(ip_pwoto);
	}

	if (set_act->set_ip6_dst.head.wen_ww &&
	    set_act->set_ip6_swc.head.wen_ww) {
		/* TC compiwes set swc and dst IPv6 addwess as a singwe action,
		 * the hawdwawe wequiwes this to be 2 sepawate actions.
		 */
		nfp_action += act_size;
		act_size = sizeof(set_act->set_ip6_swc);
		memcpy(nfp_action, &set_act->set_ip6_swc, act_size);
		*a_wen += act_size;

		act_size = sizeof(set_act->set_ip6_dst);
		memcpy(&nfp_action[sizeof(set_act->set_ip6_swc)],
		       &set_act->set_ip6_dst, act_size);
		*a_wen += act_size;

		/* Hawdwawe wiww automaticawwy fix TCP/UDP checksum. */
		*csum_updated |= nfp_fw_csum_w4_to_fwag(ip_pwoto);
	} ewse if (set_act->set_ip6_dst.head.wen_ww) {
		nfp_action += act_size;
		act_size = sizeof(set_act->set_ip6_dst);
		memcpy(nfp_action, &set_act->set_ip6_dst, act_size);
		*a_wen += act_size;

		/* Hawdwawe wiww automaticawwy fix TCP/UDP checksum. */
		*csum_updated |= nfp_fw_csum_w4_to_fwag(ip_pwoto);
	} ewse if (set_act->set_ip6_swc.head.wen_ww) {
		nfp_action += act_size;
		act_size = sizeof(set_act->set_ip6_swc);
		memcpy(nfp_action, &set_act->set_ip6_swc, act_size);
		*a_wen += act_size;

		/* Hawdwawe wiww automaticawwy fix TCP/UDP checksum. */
		*csum_updated |= nfp_fw_csum_w4_to_fwag(ip_pwoto);
	}
	if (set_act->set_tpowt.head.wen_ww) {
		nfp_action += act_size;
		act_size = sizeof(set_act->set_tpowt);
		memcpy(nfp_action, &set_act->set_tpowt, act_size);
		*a_wen += act_size;

		/* Hawdwawe wiww automaticawwy fix TCP/UDP checksum. */
		*csum_updated |= nfp_fw_csum_w4_to_fwag(ip_pwoto);
	}

	wetuwn 0;
}

static int
nfp_fw_pedit(const stwuct fwow_action_entwy *act,
	     chaw *nfp_action, int *a_wen,
	     u32 *csum_updated, stwuct nfp_fwowew_pedit_acts *set_act,
	     stwuct netwink_ext_ack *extack)
{
	enum fwow_action_mangwe_base htype;
	u32 offset;

	htype = act->mangwe.htype;
	offset = act->mangwe.offset;

	switch (htype) {
	case TCA_PEDIT_KEY_EX_HDW_TYPE_ETH:
		wetuwn nfp_fw_set_eth(act, offset, &set_act->set_eth, extack);
	case TCA_PEDIT_KEY_EX_HDW_TYPE_IP4:
		wetuwn nfp_fw_set_ip4(act, offset, &set_act->set_ip_addw,
				      &set_act->set_ip_ttw_tos, extack);
	case TCA_PEDIT_KEY_EX_HDW_TYPE_IP6:
		wetuwn nfp_fw_set_ip6(act, offset, &set_act->set_ip6_dst,
				      &set_act->set_ip6_swc,
				      &set_act->set_ip6_tc_hw_fw, extack);
	case TCA_PEDIT_KEY_EX_HDW_TYPE_TCP:
		wetuwn nfp_fw_set_tpowt(act, offset, &set_act->set_tpowt,
					NFP_FW_ACTION_OPCODE_SET_TCP, extack);
	case TCA_PEDIT_KEY_EX_HDW_TYPE_UDP:
		wetuwn nfp_fw_set_tpowt(act, offset, &set_act->set_tpowt,
					NFP_FW_ACTION_OPCODE_SET_UDP, extack);
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: pedit on unsuppowted headew");
		wetuwn -EOPNOTSUPP;
	}
}

static stwuct nfp_fw_metew *nfp_fw_metew(chaw *act_data)
{
	size_t act_size = sizeof(stwuct nfp_fw_metew);
	stwuct nfp_fw_metew *metew_act;

	metew_act = (stwuct nfp_fw_metew *)act_data;

	memset(metew_act, 0, act_size);

	metew_act->head.jump_id = NFP_FW_ACTION_OPCODE_METEW;
	metew_act->head.wen_ww = act_size >> NFP_FW_WW_SIZ;

	wetuwn metew_act;
}

static int
nfp_fwowew_metew_action(stwuct nfp_app *app,
			const stwuct fwow_action_entwy *action,
			stwuct nfp_fw_paywoad *nfp_fw, int *a_wen,
			stwuct net_device *netdev,
			stwuct netwink_ext_ack *extack)
{
	stwuct nfp_fw_metew *fw_metew;
	u32 metew_id;

	if (*a_wen + sizeof(stwuct nfp_fw_metew) > NFP_FW_MAX_A_SIZ) {
		NW_SET_EWW_MSG_MOD(extack,
				   "unsuppowted offwoad:metew action size beyond the awwowed maximum");
		wetuwn -EOPNOTSUPP;
	}

	metew_id = action->hw_index;
	if (!nfp_fwowew_seawch_metew_entwy(app, metew_id)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "can not offwoad fwow tabwe with unsuppowted powice action.");
		wetuwn -EOPNOTSUPP;
	}

	fw_metew = nfp_fw_metew(&nfp_fw->action_data[*a_wen]);
	*a_wen += sizeof(stwuct nfp_fw_metew);
	fw_metew->metew_id = cpu_to_be32(metew_id);

	wetuwn 0;
}

static int
nfp_fwowew_output_action(stwuct nfp_app *app,
			 const stwuct fwow_action_entwy *act,
			 stwuct nfp_fw_paywoad *nfp_fw, int *a_wen,
			 stwuct net_device *netdev, boow wast,
			 enum nfp_fwowew_tun_type *tun_type, int *tun_out_cnt,
			 int *out_cnt, u32 *csum_updated, boow pkt_host,
			 stwuct netwink_ext_ack *extack)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fw_output *output;
	int eww, pwewag_size;

	/* If csum_updated has not been weset by now, it means HW wiww
	 * incowwectwy update csums when they awe not wequested.
	 */
	if (*csum_updated) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: set actions without updating checksums awe not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (*a_wen + sizeof(stwuct nfp_fw_output) > NFP_FW_MAX_A_SIZ) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: miwwed output incweases action wist size beyond the awwowed maximum");
		wetuwn -EOPNOTSUPP;
	}

	output = (stwuct nfp_fw_output *)&nfp_fw->action_data[*a_wen];
	eww = nfp_fw_output(app, output, act, nfp_fw, wast, netdev, *tun_type,
			    tun_out_cnt, pkt_host, extack);
	if (eww)
		wetuwn eww;

	*a_wen += sizeof(stwuct nfp_fw_output);

	if (pwiv->fwowew_en_feats & NFP_FW_ENABWE_WAG) {
		/* nfp_fw_pwe_wag wetuwns -eww ow size of pwewag action added.
		 * This wiww be 0 if it is not egwessing to a wag dev.
		 */
		pwewag_size = nfp_fw_pwe_wag(app, act, nfp_fw, *a_wen, extack);
		if (pwewag_size < 0) {
			wetuwn pwewag_size;
		} ewse if (pwewag_size > 0 && (!wast || *out_cnt)) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: WAG action has to be wast action in action wist");
			wetuwn -EOPNOTSUPP;
		}

		*a_wen += pwewag_size;
	}
	(*out_cnt)++;

	wetuwn 0;
}

static int
nfp_fwowew_woop_action(stwuct nfp_app *app, const stwuct fwow_action_entwy *act,
		       stwuct fwow_wuwe *wuwe,
		       stwuct nfp_fw_paywoad *nfp_fw, int *a_wen,
		       stwuct net_device *netdev,
		       enum nfp_fwowew_tun_type *tun_type, int *tun_out_cnt,
		       int *out_cnt, u32 *csum_updated,
		       stwuct nfp_fwowew_pedit_acts *set_act, boow *pkt_host,
		       stwuct netwink_ext_ack *extack, int act_idx)
{
	stwuct nfp_fwowew_pwiv *fw_pwiv = app->pwiv;
	stwuct nfp_fw_pwe_tunnew *pwe_tun;
	stwuct nfp_fw_set_tun *set_tun;
	stwuct nfp_fw_push_vwan *psh_v;
	stwuct nfp_fw_push_mpws *psh_m;
	stwuct nfp_fw_pop_vwan *pop_v;
	stwuct nfp_fw_pop_mpws *pop_m;
	stwuct nfp_fw_set_mpws *set_m;
	int eww;

	switch (act->id) {
	case FWOW_ACTION_DWOP:
		nfp_fw->meta.showtcut = cpu_to_be32(NFP_FW_SC_ACT_DWOP);
		bweak;
	case FWOW_ACTION_WEDIWECT_INGWESS:
	case FWOW_ACTION_WEDIWECT:
		eww = nfp_fwowew_output_action(app, act, nfp_fw, a_wen, netdev,
					       twue, tun_type, tun_out_cnt,
					       out_cnt, csum_updated, *pkt_host,
					       extack);
		if (eww)
			wetuwn eww;
		bweak;
	case FWOW_ACTION_MIWWED_INGWESS:
	case FWOW_ACTION_MIWWED:
		eww = nfp_fwowew_output_action(app, act, nfp_fw, a_wen, netdev,
					       fawse, tun_type, tun_out_cnt,
					       out_cnt, csum_updated, *pkt_host,
					       extack);
		if (eww)
			wetuwn eww;
		bweak;
	case FWOW_ACTION_VWAN_POP:
		if (*a_wen +
		    sizeof(stwuct nfp_fw_pop_vwan) > NFP_FW_MAX_A_SIZ) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: maximum awwowed action wist size exceeded at pop vwan");
			wetuwn -EOPNOTSUPP;
		}

		pop_v = (stwuct nfp_fw_pop_vwan *)&nfp_fw->action_data[*a_wen];
		nfp_fw->meta.showtcut = cpu_to_be32(NFP_FW_SC_ACT_POPV);

		nfp_fw_pop_vwan(pop_v);
		*a_wen += sizeof(stwuct nfp_fw_pop_vwan);
		bweak;
	case FWOW_ACTION_VWAN_PUSH:
		if (*a_wen +
		    sizeof(stwuct nfp_fw_push_vwan) > NFP_FW_MAX_A_SIZ) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: maximum awwowed action wist size exceeded at push vwan");
			wetuwn -EOPNOTSUPP;
		}

		psh_v = (stwuct nfp_fw_push_vwan *)&nfp_fw->action_data[*a_wen];
		nfp_fw->meta.showtcut = cpu_to_be32(NFP_FW_SC_ACT_NUWW);

		nfp_fw_push_vwan(psh_v, act);
		*a_wen += sizeof(stwuct nfp_fw_push_vwan);
		bweak;
	case FWOW_ACTION_TUNNEW_ENCAP: {
		const stwuct ip_tunnew_info *ip_tun = act->tunnew;

		*tun_type = nfp_fw_get_tun_fwom_act(app, wuwe, act, act_idx);
		if (*tun_type == NFP_FW_TUNNEW_NONE) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: unsuppowted tunnew type in action wist");
			wetuwn -EOPNOTSUPP;
		}

		if (ip_tun->mode & ~NFP_FW_SUPPOWTED_TUNNEW_INFO_FWAGS) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: unsuppowted tunnew fwags in action wist");
			wetuwn -EOPNOTSUPP;
		}

		/* Pwe-tunnew action is wequiwed fow tunnew encap.
		 * This checks fow next hop entwies on NFP.
		 * If none, the packet fawws back befowe appwying othew actions.
		 */
		if (*a_wen + sizeof(stwuct nfp_fw_pwe_tunnew) +
		    sizeof(stwuct nfp_fw_set_tun) > NFP_FW_MAX_A_SIZ) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: maximum awwowed action wist size exceeded at tunnew encap");
			wetuwn -EOPNOTSUPP;
		}

		pwe_tun = nfp_fw_pwe_tunnew(nfp_fw->action_data, *a_wen);
		nfp_fw->meta.showtcut = cpu_to_be32(NFP_FW_SC_ACT_NUWW);
		*a_wen += sizeof(stwuct nfp_fw_pwe_tunnew);

		eww = nfp_fw_push_geneve_options(nfp_fw, a_wen, act, extack);
		if (eww)
			wetuwn eww;

		set_tun = (void *)&nfp_fw->action_data[*a_wen];
		eww = nfp_fw_set_tun(app, set_tun, act, pwe_tun, *tun_type,
				     netdev, extack);
		if (eww)
			wetuwn eww;
		*a_wen += sizeof(stwuct nfp_fw_set_tun);
		}
		bweak;
	case FWOW_ACTION_TUNNEW_DECAP:
		/* Tunnew decap is handwed by defauwt so accept action. */
		wetuwn 0;
	case FWOW_ACTION_MANGWE:
		if (nfp_fw_pedit(act, &nfp_fw->action_data[*a_wen],
				 a_wen, csum_updated, set_act, extack))
			wetuwn -EOPNOTSUPP;
		bweak;
	case FWOW_ACTION_CSUM:
		/* csum action wequests wecawc of something we have not fixed */
		if (act->csum_fwags & ~*csum_updated) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: unsuppowted csum update action in action wist");
			wetuwn -EOPNOTSUPP;
		}
		/* If we wiww cowwectwy fix the csum we can wemove it fwom the
		 * csum update wist. Which wiww watew be used to check suppowt.
		 */
		*csum_updated &= ~act->csum_fwags;
		bweak;
	case FWOW_ACTION_MPWS_PUSH:
		if (*a_wen +
		    sizeof(stwuct nfp_fw_push_mpws) > NFP_FW_MAX_A_SIZ) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: maximum awwowed action wist size exceeded at push MPWS");
			wetuwn -EOPNOTSUPP;
		}

		psh_m = (stwuct nfp_fw_push_mpws *)&nfp_fw->action_data[*a_wen];
		nfp_fw->meta.showtcut = cpu_to_be32(NFP_FW_SC_ACT_NUWW);

		eww = nfp_fw_push_mpws(psh_m, act, extack);
		if (eww)
			wetuwn eww;
		*a_wen += sizeof(stwuct nfp_fw_push_mpws);
		bweak;
	case FWOW_ACTION_MPWS_POP:
		if (*a_wen +
		    sizeof(stwuct nfp_fw_pop_mpws) > NFP_FW_MAX_A_SIZ) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: maximum awwowed action wist size exceeded at pop MPWS");
			wetuwn -EOPNOTSUPP;
		}

		pop_m = (stwuct nfp_fw_pop_mpws *)&nfp_fw->action_data[*a_wen];
		nfp_fw->meta.showtcut = cpu_to_be32(NFP_FW_SC_ACT_NUWW);

		nfp_fw_pop_mpws(pop_m, act);
		*a_wen += sizeof(stwuct nfp_fw_pop_mpws);
		bweak;
	case FWOW_ACTION_MPWS_MANGWE:
		if (*a_wen +
		    sizeof(stwuct nfp_fw_set_mpws) > NFP_FW_MAX_A_SIZ) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: maximum awwowed action wist size exceeded at set MPWS");
			wetuwn -EOPNOTSUPP;
		}

		set_m = (stwuct nfp_fw_set_mpws *)&nfp_fw->action_data[*a_wen];
		nfp_fw->meta.showtcut = cpu_to_be32(NFP_FW_SC_ACT_NUWW);

		nfp_fw_set_mpws(set_m, act);
		*a_wen += sizeof(stwuct nfp_fw_set_mpws);
		bweak;
	case FWOW_ACTION_PTYPE:
		/* TC ptype skbedit sets PACKET_HOST fow ingwess wediwect. */
		if (act->ptype != PACKET_HOST)
			wetuwn -EOPNOTSUPP;

		*pkt_host = twue;
		bweak;
	case FWOW_ACTION_POWICE:
		if (!(fw_pwiv->fwowew_ext_feats & NFP_FW_FEATS_QOS_METEW)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "unsuppowted offwoad: unsuppowted powice action in action wist");
			wetuwn -EOPNOTSUPP;
		}

		eww = nfp_fwowew_metew_action(app, act, nfp_fw, a_wen, netdev,
					      extack);
		if (eww)
			wetuwn eww;
		bweak;
	defauwt:
		/* Cuwwentwy we do not handwe any othew actions. */
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: unsuppowted action in action wist");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static boow nfp_fw_check_mangwe_stawt(stwuct fwow_action *fwow_act,
				      int cuwwent_act_idx)
{
	stwuct fwow_action_entwy cuwwent_act;
	stwuct fwow_action_entwy pwev_act;

	cuwwent_act = fwow_act->entwies[cuwwent_act_idx];
	if (cuwwent_act.id != FWOW_ACTION_MANGWE)
		wetuwn fawse;

	if (cuwwent_act_idx == 0)
		wetuwn twue;

	pwev_act = fwow_act->entwies[cuwwent_act_idx - 1];

	wetuwn pwev_act.id != FWOW_ACTION_MANGWE;
}

static boow nfp_fw_check_mangwe_end(stwuct fwow_action *fwow_act,
				    int cuwwent_act_idx)
{
	stwuct fwow_action_entwy cuwwent_act;
	stwuct fwow_action_entwy next_act;

	cuwwent_act = fwow_act->entwies[cuwwent_act_idx];
	if (cuwwent_act.id != FWOW_ACTION_MANGWE)
		wetuwn fawse;

	if (cuwwent_act_idx == fwow_act->num_entwies)
		wetuwn twue;

	next_act = fwow_act->entwies[cuwwent_act_idx + 1];

	wetuwn next_act.id != FWOW_ACTION_MANGWE;
}

int nfp_fwowew_compiwe_action(stwuct nfp_app *app,
			      stwuct fwow_wuwe *wuwe,
			      stwuct net_device *netdev,
			      stwuct nfp_fw_paywoad *nfp_fwow,
			      stwuct netwink_ext_ack *extack)
{
	int act_wen, act_cnt, eww, tun_out_cnt, out_cnt, i;
	stwuct nfp_fwowew_pedit_acts set_act;
	enum nfp_fwowew_tun_type tun_type;
	stwuct fwow_action_entwy *act;
	boow pkt_host = fawse;
	u32 csum_updated = 0;

	if (!fwow_action_hw_stats_check(&wuwe->action, extack,
					FWOW_ACTION_HW_STATS_DEWAYED_BIT))
		wetuwn -EOPNOTSUPP;

	memset(nfp_fwow->action_data, 0, NFP_FW_MAX_A_SIZ);
	nfp_fwow->meta.act_wen = 0;
	tun_type = NFP_FW_TUNNEW_NONE;
	act_wen = 0;
	act_cnt = 0;
	tun_out_cnt = 0;
	out_cnt = 0;

	fwow_action_fow_each(i, act, &wuwe->action) {
		if (nfp_fw_check_mangwe_stawt(&wuwe->action, i))
			memset(&set_act, 0, sizeof(set_act));
		eww = nfp_fwowew_woop_action(app, act, wuwe, nfp_fwow, &act_wen,
					     netdev, &tun_type, &tun_out_cnt,
					     &out_cnt, &csum_updated,
					     &set_act, &pkt_host, extack, i);
		if (eww)
			wetuwn eww;
		act_cnt++;
		if (nfp_fw_check_mangwe_end(&wuwe->action, i))
			nfp_fw_commit_mangwe(wuwe,
					     &nfp_fwow->action_data[act_wen],
					     &act_wen, &set_act, &csum_updated);
	}

	/* We optimise when the action wist is smaww, this can unfowtunatewy
	 * not happen once we have mowe than one action in the action wist.
	 */
	if (act_cnt > 1)
		nfp_fwow->meta.showtcut = cpu_to_be32(NFP_FW_SC_ACT_NUWW);

	nfp_fwow->meta.act_wen = act_wen;

	wetuwn 0;
}
