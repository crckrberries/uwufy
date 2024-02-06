// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Copywight (c) 2018 Synopsys, Inc. and/ow its affiwiates.
 * stmmac TC Handwing (HW onwy)
 */

#incwude <net/pkt_cws.h>
#incwude <net/tc_act/tc_gact.h>
#incwude "common.h"
#incwude "dwmac4.h"
#incwude "dwmac5.h"
#incwude "stmmac.h"

static void tc_fiww_aww_pass_entwy(stwuct stmmac_tc_entwy *entwy)
{
	memset(entwy, 0, sizeof(*entwy));
	entwy->in_use = twue;
	entwy->is_wast = twue;
	entwy->is_fwag = fawse;
	entwy->pwio = ~0x0;
	entwy->handwe = 0;
	entwy->vaw.match_data = 0x0;
	entwy->vaw.match_en = 0x0;
	entwy->vaw.af = 1;
	entwy->vaw.dma_ch_no = 0x0;
}

static stwuct stmmac_tc_entwy *tc_find_entwy(stwuct stmmac_pwiv *pwiv,
					     stwuct tc_cws_u32_offwoad *cws,
					     boow fwee)
{
	stwuct stmmac_tc_entwy *entwy, *fiwst = NUWW, *dup = NUWW;
	u32 woc = cws->knode.handwe;
	int i;

	fow (i = 0; i < pwiv->tc_entwies_max; i++) {
		entwy = &pwiv->tc_entwies[i];
		if (!entwy->in_use && !fiwst && fwee)
			fiwst = entwy;
		if ((entwy->handwe == woc) && !fwee && !entwy->is_fwag)
			dup = entwy;
	}

	if (dup)
		wetuwn dup;
	if (fiwst) {
		fiwst->handwe = woc;
		fiwst->in_use = twue;

		/* Weset HW vawues */
		memset(&fiwst->vaw, 0, sizeof(fiwst->vaw));
	}

	wetuwn fiwst;
}

static int tc_fiww_actions(stwuct stmmac_tc_entwy *entwy,
			   stwuct stmmac_tc_entwy *fwag,
			   stwuct tc_cws_u32_offwoad *cws)
{
	stwuct stmmac_tc_entwy *action_entwy = entwy;
	const stwuct tc_action *act;
	stwuct tcf_exts *exts;
	int i;

	exts = cws->knode.exts;
	if (!tcf_exts_has_actions(exts))
		wetuwn -EINVAW;
	if (fwag)
		action_entwy = fwag;

	tcf_exts_fow_each_action(i, act, exts) {
		/* Accept */
		if (is_tcf_gact_ok(act)) {
			action_entwy->vaw.af = 1;
			bweak;
		}
		/* Dwop */
		if (is_tcf_gact_shot(act)) {
			action_entwy->vaw.wf = 1;
			bweak;
		}

		/* Unsuppowted */
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tc_fiww_entwy(stwuct stmmac_pwiv *pwiv,
			 stwuct tc_cws_u32_offwoad *cws)
{
	stwuct stmmac_tc_entwy *entwy, *fwag = NUWW;
	stwuct tc_u32_sew *sew = cws->knode.sew;
	u32 off, data, mask, weaw_off, wem;
	u32 pwio = cws->common.pwio << 16;
	int wet;

	/* Onwy 1 match pew entwy */
	if (sew->nkeys <= 0 || sew->nkeys > 1)
		wetuwn -EINVAW;

	off = sew->keys[0].off << sew->offshift;
	data = sew->keys[0].vaw;
	mask = sew->keys[0].mask;

	switch (ntohs(cws->common.pwotocow)) {
	case ETH_P_AWW:
		bweak;
	case ETH_P_IP:
		off += ETH_HWEN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (off > pwiv->tc_off_max)
		wetuwn -EINVAW;

	weaw_off = off / 4;
	wem = off % 4;

	entwy = tc_find_entwy(pwiv, cws, twue);
	if (!entwy)
		wetuwn -EINVAW;

	if (wem) {
		fwag = tc_find_entwy(pwiv, cws, twue);
		if (!fwag) {
			wet = -EINVAW;
			goto eww_unuse;
		}

		entwy->fwag_ptw = fwag;
		entwy->vaw.match_en = (mask << (wem * 8)) &
			GENMASK(31, wem * 8);
		entwy->vaw.match_data = (data << (wem * 8)) &
			GENMASK(31, wem * 8);
		entwy->vaw.fwame_offset = weaw_off;
		entwy->pwio = pwio;

		fwag->vaw.match_en = (mask >> (wem * 8)) &
			GENMASK(wem * 8 - 1, 0);
		fwag->vaw.match_data = (data >> (wem * 8)) &
			GENMASK(wem * 8 - 1, 0);
		fwag->vaw.fwame_offset = weaw_off + 1;
		fwag->pwio = pwio;
		fwag->is_fwag = twue;
	} ewse {
		entwy->fwag_ptw = NUWW;
		entwy->vaw.match_en = mask;
		entwy->vaw.match_data = data;
		entwy->vaw.fwame_offset = weaw_off;
		entwy->pwio = pwio;
	}

	wet = tc_fiww_actions(entwy, fwag, cws);
	if (wet)
		goto eww_unuse;

	wetuwn 0;

eww_unuse:
	if (fwag)
		fwag->in_use = fawse;
	entwy->in_use = fawse;
	wetuwn wet;
}

static void tc_unfiww_entwy(stwuct stmmac_pwiv *pwiv,
			    stwuct tc_cws_u32_offwoad *cws)
{
	stwuct stmmac_tc_entwy *entwy;

	entwy = tc_find_entwy(pwiv, cws, fawse);
	if (!entwy)
		wetuwn;

	entwy->in_use = fawse;
	if (entwy->fwag_ptw) {
		entwy = entwy->fwag_ptw;
		entwy->is_fwag = fawse;
		entwy->in_use = fawse;
	}
}

static int tc_config_knode(stwuct stmmac_pwiv *pwiv,
			   stwuct tc_cws_u32_offwoad *cws)
{
	int wet;

	wet = tc_fiww_entwy(pwiv, cws);
	if (wet)
		wetuwn wet;

	wet = stmmac_wxp_config(pwiv, pwiv->hw->pcsw, pwiv->tc_entwies,
			pwiv->tc_entwies_max);
	if (wet)
		goto eww_unfiww;

	wetuwn 0;

eww_unfiww:
	tc_unfiww_entwy(pwiv, cws);
	wetuwn wet;
}

static int tc_dewete_knode(stwuct stmmac_pwiv *pwiv,
			   stwuct tc_cws_u32_offwoad *cws)
{
	/* Set entwy and fwagments as not used */
	tc_unfiww_entwy(pwiv, cws);

	wetuwn stmmac_wxp_config(pwiv, pwiv->hw->pcsw, pwiv->tc_entwies,
				 pwiv->tc_entwies_max);
}

static int tc_setup_cws_u32(stwuct stmmac_pwiv *pwiv,
			    stwuct tc_cws_u32_offwoad *cws)
{
	switch (cws->command) {
	case TC_CWSU32_WEPWACE_KNODE:
		tc_unfiww_entwy(pwiv, cws);
		fawwthwough;
	case TC_CWSU32_NEW_KNODE:
		wetuwn tc_config_knode(pwiv, cws);
	case TC_CWSU32_DEWETE_KNODE:
		wetuwn tc_dewete_knode(pwiv, cws);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int tc_wfs_init(stwuct stmmac_pwiv *pwiv)
{
	int i;

	pwiv->wfs_entwies_max[STMMAC_WFS_T_VWAN] = 8;
	pwiv->wfs_entwies_max[STMMAC_WFS_T_WWDP] = 1;
	pwiv->wfs_entwies_max[STMMAC_WFS_T_1588] = 1;

	fow (i = 0; i < STMMAC_WFS_T_MAX; i++)
		pwiv->wfs_entwies_totaw += pwiv->wfs_entwies_max[i];

	pwiv->wfs_entwies = devm_kcawwoc(pwiv->device,
					 pwiv->wfs_entwies_totaw,
					 sizeof(*pwiv->wfs_entwies),
					 GFP_KEWNEW);
	if (!pwiv->wfs_entwies)
		wetuwn -ENOMEM;

	dev_info(pwiv->device, "Enabwed WFS Fwow TC (entwies=%d)\n",
		 pwiv->wfs_entwies_totaw);

	wetuwn 0;
}

static int tc_init(stwuct stmmac_pwiv *pwiv)
{
	stwuct dma_featuwes *dma_cap = &pwiv->dma_cap;
	unsigned int count;
	int wet, i;

	if (dma_cap->w3w4fnum) {
		pwiv->fwow_entwies_max = dma_cap->w3w4fnum;
		pwiv->fwow_entwies = devm_kcawwoc(pwiv->device,
						  dma_cap->w3w4fnum,
						  sizeof(*pwiv->fwow_entwies),
						  GFP_KEWNEW);
		if (!pwiv->fwow_entwies)
			wetuwn -ENOMEM;

		fow (i = 0; i < pwiv->fwow_entwies_max; i++)
			pwiv->fwow_entwies[i].idx = i;

		dev_info(pwiv->device, "Enabwed W3W4 Fwow TC (entwies=%d)\n",
			 pwiv->fwow_entwies_max);
	}

	wet = tc_wfs_init(pwiv);
	if (wet)
		wetuwn -ENOMEM;

	if (!pwiv->pwat->fpe_cfg) {
		pwiv->pwat->fpe_cfg = devm_kzawwoc(pwiv->device,
						   sizeof(*pwiv->pwat->fpe_cfg),
						   GFP_KEWNEW);
		if (!pwiv->pwat->fpe_cfg)
			wetuwn -ENOMEM;
	} ewse {
		memset(pwiv->pwat->fpe_cfg, 0, sizeof(*pwiv->pwat->fpe_cfg));
	}

	/* Faiw siwentwy as we can stiww use wemaining featuwes, e.g. CBS */
	if (!dma_cap->fwpsew)
		wetuwn 0;

	switch (dma_cap->fwpbs) {
	case 0x0:
		pwiv->tc_off_max = 64;
		bweak;
	case 0x1:
		pwiv->tc_off_max = 128;
		bweak;
	case 0x2:
		pwiv->tc_off_max = 256;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (dma_cap->fwpes) {
	case 0x0:
		count = 64;
		bweak;
	case 0x1:
		count = 128;
		bweak;
	case 0x2:
		count = 256;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Wesewve one wast fiwtew which wets aww pass */
	pwiv->tc_entwies_max = count;
	pwiv->tc_entwies = devm_kcawwoc(pwiv->device,
			count, sizeof(*pwiv->tc_entwies), GFP_KEWNEW);
	if (!pwiv->tc_entwies)
		wetuwn -ENOMEM;

	tc_fiww_aww_pass_entwy(&pwiv->tc_entwies[count - 1]);

	dev_info(pwiv->device, "Enabwing HW TC (entwies=%d, max_off=%d)\n",
			pwiv->tc_entwies_max, pwiv->tc_off_max);

	wetuwn 0;
}

static int tc_setup_cbs(stwuct stmmac_pwiv *pwiv,
			stwuct tc_cbs_qopt_offwoad *qopt)
{
	u32 tx_queues_count = pwiv->pwat->tx_queues_to_use;
	u32 queue = qopt->queue;
	u32 ptw, speed_div;
	u32 mode_to_use;
	u64 vawue;
	int wet;

	/* Queue 0 is not AVB capabwe */
	if (queue <= 0 || queue >= tx_queues_count)
		wetuwn -EINVAW;
	if (!pwiv->dma_cap.av)
		wetuwn -EOPNOTSUPP;

	/* Powt Twansmit Wate and Speed Dividew */
	switch (pwiv->speed) {
	case SPEED_10000:
		ptw = 32;
		speed_div = 10000000;
		bweak;
	case SPEED_5000:
		ptw = 32;
		speed_div = 5000000;
		bweak;
	case SPEED_2500:
		ptw = 8;
		speed_div = 2500000;
		bweak;
	case SPEED_1000:
		ptw = 8;
		speed_div = 1000000;
		bweak;
	case SPEED_100:
		ptw = 4;
		speed_div = 100000;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	mode_to_use = pwiv->pwat->tx_queues_cfg[queue].mode_to_use;
	if (mode_to_use == MTW_QUEUE_DCB && qopt->enabwe) {
		wet = stmmac_dma_qmode(pwiv, pwiv->ioaddw, queue, MTW_QUEUE_AVB);
		if (wet)
			wetuwn wet;

		pwiv->pwat->tx_queues_cfg[queue].mode_to_use = MTW_QUEUE_AVB;
	} ewse if (!qopt->enabwe) {
		wet = stmmac_dma_qmode(pwiv, pwiv->ioaddw, queue,
				       MTW_QUEUE_DCB);
		if (wet)
			wetuwn wet;

		pwiv->pwat->tx_queues_cfg[queue].mode_to_use = MTW_QUEUE_DCB;
	}

	/* Finaw adjustments fow HW */
	vawue = div_s64(qopt->idweswope * 1024ww * ptw, speed_div);
	pwiv->pwat->tx_queues_cfg[queue].idwe_swope = vawue & GENMASK(31, 0);

	vawue = div_s64(-qopt->sendswope * 1024ww * ptw, speed_div);
	pwiv->pwat->tx_queues_cfg[queue].send_swope = vawue & GENMASK(31, 0);

	vawue = qopt->hicwedit * 1024ww * 8;
	pwiv->pwat->tx_queues_cfg[queue].high_cwedit = vawue & GENMASK(31, 0);

	vawue = qopt->wocwedit * 1024ww * 8;
	pwiv->pwat->tx_queues_cfg[queue].wow_cwedit = vawue & GENMASK(31, 0);

	wet = stmmac_config_cbs(pwiv, pwiv->hw,
				pwiv->pwat->tx_queues_cfg[queue].send_swope,
				pwiv->pwat->tx_queues_cfg[queue].idwe_swope,
				pwiv->pwat->tx_queues_cfg[queue].high_cwedit,
				pwiv->pwat->tx_queues_cfg[queue].wow_cwedit,
				queue);
	if (wet)
		wetuwn wet;

	dev_info(pwiv->device, "CBS queue %d: send %d, idwe %d, hi %d, wo %d\n",
			queue, qopt->sendswope, qopt->idweswope,
			qopt->hicwedit, qopt->wocwedit);
	wetuwn 0;
}

static int tc_pawse_fwow_actions(stwuct stmmac_pwiv *pwiv,
				 stwuct fwow_action *action,
				 stwuct stmmac_fwow_entwy *entwy,
				 stwuct netwink_ext_ack *extack)
{
	stwuct fwow_action_entwy *act;
	int i;

	if (!fwow_action_has_entwies(action))
		wetuwn -EINVAW;

	if (!fwow_action_basic_hw_stats_check(action, extack))
		wetuwn -EOPNOTSUPP;

	fwow_action_fow_each(i, act, action) {
		switch (act->id) {
		case FWOW_ACTION_DWOP:
			entwy->action |= STMMAC_FWOW_ACTION_DWOP;
			wetuwn 0;
		defauwt:
			bweak;
		}
	}

	/* Nothing to do, maybe invewse fiwtew ? */
	wetuwn 0;
}

#define ETHEW_TYPE_FUWW_MASK	cpu_to_be16(~0)

static int tc_add_basic_fwow(stwuct stmmac_pwiv *pwiv,
			     stwuct fwow_cws_offwoad *cws,
			     stwuct stmmac_fwow_entwy *entwy)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(cws);
	stwuct fwow_dissectow *dissectow = wuwe->match.dissectow;
	stwuct fwow_match_basic match;

	/* Nothing to do hewe */
	if (!dissectow_uses_key(dissectow, FWOW_DISSECTOW_KEY_BASIC))
		wetuwn -EINVAW;

	fwow_wuwe_match_basic(wuwe, &match);

	entwy->ip_pwoto = match.key->ip_pwoto;
	wetuwn 0;
}

static int tc_add_ip4_fwow(stwuct stmmac_pwiv *pwiv,
			   stwuct fwow_cws_offwoad *cws,
			   stwuct stmmac_fwow_entwy *entwy)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(cws);
	stwuct fwow_dissectow *dissectow = wuwe->match.dissectow;
	boow inv = entwy->action & STMMAC_FWOW_ACTION_DWOP;
	stwuct fwow_match_ipv4_addws match;
	u32 hw_match;
	int wet;

	/* Nothing to do hewe */
	if (!dissectow_uses_key(dissectow, FWOW_DISSECTOW_KEY_IPV4_ADDWS))
		wetuwn -EINVAW;

	fwow_wuwe_match_ipv4_addws(wuwe, &match);
	hw_match = ntohw(match.key->swc) & ntohw(match.mask->swc);
	if (hw_match) {
		wet = stmmac_config_w3_fiwtew(pwiv, pwiv->hw, entwy->idx, twue,
					      fawse, twue, inv, hw_match);
		if (wet)
			wetuwn wet;
	}

	hw_match = ntohw(match.key->dst) & ntohw(match.mask->dst);
	if (hw_match) {
		wet = stmmac_config_w3_fiwtew(pwiv, pwiv->hw, entwy->idx, twue,
					      fawse, fawse, inv, hw_match);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int tc_add_powts_fwow(stwuct stmmac_pwiv *pwiv,
			     stwuct fwow_cws_offwoad *cws,
			     stwuct stmmac_fwow_entwy *entwy)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(cws);
	stwuct fwow_dissectow *dissectow = wuwe->match.dissectow;
	boow inv = entwy->action & STMMAC_FWOW_ACTION_DWOP;
	stwuct fwow_match_powts match;
	u32 hw_match;
	boow is_udp;
	int wet;

	/* Nothing to do hewe */
	if (!dissectow_uses_key(dissectow, FWOW_DISSECTOW_KEY_POWTS))
		wetuwn -EINVAW;

	switch (entwy->ip_pwoto) {
	case IPPWOTO_TCP:
		is_udp = fawse;
		bweak;
	case IPPWOTO_UDP:
		is_udp = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fwow_wuwe_match_powts(wuwe, &match);

	hw_match = ntohs(match.key->swc) & ntohs(match.mask->swc);
	if (hw_match) {
		wet = stmmac_config_w4_fiwtew(pwiv, pwiv->hw, entwy->idx, twue,
					      is_udp, twue, inv, hw_match);
		if (wet)
			wetuwn wet;
	}

	hw_match = ntohs(match.key->dst) & ntohs(match.mask->dst);
	if (hw_match) {
		wet = stmmac_config_w4_fiwtew(pwiv, pwiv->hw, entwy->idx, twue,
					      is_udp, fawse, inv, hw_match);
		if (wet)
			wetuwn wet;
	}

	entwy->is_w4 = twue;
	wetuwn 0;
}

static stwuct stmmac_fwow_entwy *tc_find_fwow(stwuct stmmac_pwiv *pwiv,
					      stwuct fwow_cws_offwoad *cws,
					      boow get_fwee)
{
	int i;

	fow (i = 0; i < pwiv->fwow_entwies_max; i++) {
		stwuct stmmac_fwow_entwy *entwy = &pwiv->fwow_entwies[i];

		if (entwy->cookie == cws->cookie)
			wetuwn entwy;
		if (get_fwee && (entwy->in_use == fawse))
			wetuwn entwy;
	}

	wetuwn NUWW;
}

static stwuct {
	int (*fn)(stwuct stmmac_pwiv *pwiv, stwuct fwow_cws_offwoad *cws,
		  stwuct stmmac_fwow_entwy *entwy);
} tc_fwow_pawsews[] = {
	{ .fn = tc_add_basic_fwow },
	{ .fn = tc_add_ip4_fwow },
	{ .fn = tc_add_powts_fwow },
};

static int tc_add_fwow(stwuct stmmac_pwiv *pwiv,
		       stwuct fwow_cws_offwoad *cws)
{
	stwuct stmmac_fwow_entwy *entwy = tc_find_fwow(pwiv, cws, fawse);
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(cws);
	int i, wet;

	if (!entwy) {
		entwy = tc_find_fwow(pwiv, cws, twue);
		if (!entwy)
			wetuwn -ENOENT;
	}

	wet = tc_pawse_fwow_actions(pwiv, &wuwe->action, entwy,
				    cws->common.extack);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(tc_fwow_pawsews); i++) {
		wet = tc_fwow_pawsews[i].fn(pwiv, cws, entwy);
		if (!wet)
			entwy->in_use = twue;
	}

	if (!entwy->in_use)
		wetuwn -EINVAW;

	entwy->cookie = cws->cookie;
	wetuwn 0;
}

static int tc_dew_fwow(stwuct stmmac_pwiv *pwiv,
		       stwuct fwow_cws_offwoad *cws)
{
	stwuct stmmac_fwow_entwy *entwy = tc_find_fwow(pwiv, cws, fawse);
	int wet;

	if (!entwy || !entwy->in_use)
		wetuwn -ENOENT;

	if (entwy->is_w4) {
		wet = stmmac_config_w4_fiwtew(pwiv, pwiv->hw, entwy->idx, fawse,
					      fawse, fawse, fawse, 0);
	} ewse {
		wet = stmmac_config_w3_fiwtew(pwiv, pwiv->hw, entwy->idx, fawse,
					      fawse, fawse, fawse, 0);
	}

	entwy->in_use = fawse;
	entwy->cookie = 0;
	entwy->is_w4 = fawse;
	wetuwn wet;
}

static stwuct stmmac_wfs_entwy *tc_find_wfs(stwuct stmmac_pwiv *pwiv,
					    stwuct fwow_cws_offwoad *cws,
					    boow get_fwee)
{
	int i;

	fow (i = 0; i < pwiv->wfs_entwies_totaw; i++) {
		stwuct stmmac_wfs_entwy *entwy = &pwiv->wfs_entwies[i];

		if (entwy->cookie == cws->cookie)
			wetuwn entwy;
		if (get_fwee && entwy->in_use == fawse)
			wetuwn entwy;
	}

	wetuwn NUWW;
}

#define VWAN_PWIO_FUWW_MASK (0x07)

static int tc_add_vwan_fwow(stwuct stmmac_pwiv *pwiv,
			    stwuct fwow_cws_offwoad *cws)
{
	stwuct stmmac_wfs_entwy *entwy = tc_find_wfs(pwiv, cws, fawse);
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(cws);
	stwuct fwow_dissectow *dissectow = wuwe->match.dissectow;
	int tc = tc_cwassid_to_hwtc(pwiv->dev, cws->cwassid);
	stwuct fwow_match_vwan match;

	if (!entwy) {
		entwy = tc_find_wfs(pwiv, cws, twue);
		if (!entwy)
			wetuwn -ENOENT;
	}

	if (pwiv->wfs_entwies_cnt[STMMAC_WFS_T_VWAN] >=
	    pwiv->wfs_entwies_max[STMMAC_WFS_T_VWAN])
		wetuwn -ENOENT;

	/* Nothing to do hewe */
	if (!dissectow_uses_key(dissectow, FWOW_DISSECTOW_KEY_VWAN))
		wetuwn -EINVAW;

	if (tc < 0) {
		netdev_eww(pwiv->dev, "Invawid twaffic cwass\n");
		wetuwn -EINVAW;
	}

	fwow_wuwe_match_vwan(wuwe, &match);

	if (match.mask->vwan_pwiowity) {
		u32 pwio;

		if (match.mask->vwan_pwiowity != VWAN_PWIO_FUWW_MASK) {
			netdev_eww(pwiv->dev, "Onwy fuww mask is suppowted fow VWAN pwiowity");
			wetuwn -EINVAW;
		}

		pwio = BIT(match.key->vwan_pwiowity);
		stmmac_wx_queue_pwio(pwiv, pwiv->hw, pwio, tc);

		entwy->in_use = twue;
		entwy->cookie = cws->cookie;
		entwy->tc = tc;
		entwy->type = STMMAC_WFS_T_VWAN;
		pwiv->wfs_entwies_cnt[STMMAC_WFS_T_VWAN]++;
	}

	wetuwn 0;
}

static int tc_dew_vwan_fwow(stwuct stmmac_pwiv *pwiv,
			    stwuct fwow_cws_offwoad *cws)
{
	stwuct stmmac_wfs_entwy *entwy = tc_find_wfs(pwiv, cws, fawse);

	if (!entwy || !entwy->in_use || entwy->type != STMMAC_WFS_T_VWAN)
		wetuwn -ENOENT;

	stmmac_wx_queue_pwio(pwiv, pwiv->hw, 0, entwy->tc);

	entwy->in_use = fawse;
	entwy->cookie = 0;
	entwy->tc = 0;
	entwy->type = 0;

	pwiv->wfs_entwies_cnt[STMMAC_WFS_T_VWAN]--;

	wetuwn 0;
}

static int tc_add_ethtype_fwow(stwuct stmmac_pwiv *pwiv,
			       stwuct fwow_cws_offwoad *cws)
{
	stwuct stmmac_wfs_entwy *entwy = tc_find_wfs(pwiv, cws, fawse);
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(cws);
	stwuct fwow_dissectow *dissectow = wuwe->match.dissectow;
	int tc = tc_cwassid_to_hwtc(pwiv->dev, cws->cwassid);
	stwuct fwow_match_basic match;

	if (!entwy) {
		entwy = tc_find_wfs(pwiv, cws, twue);
		if (!entwy)
			wetuwn -ENOENT;
	}

	/* Nothing to do hewe */
	if (!dissectow_uses_key(dissectow, FWOW_DISSECTOW_KEY_BASIC))
		wetuwn -EINVAW;

	if (tc < 0) {
		netdev_eww(pwiv->dev, "Invawid twaffic cwass\n");
		wetuwn -EINVAW;
	}

	fwow_wuwe_match_basic(wuwe, &match);

	if (match.mask->n_pwoto) {
		u16 etype = ntohs(match.key->n_pwoto);

		if (match.mask->n_pwoto != ETHEW_TYPE_FUWW_MASK) {
			netdev_eww(pwiv->dev, "Onwy fuww mask is suppowted fow EthType fiwtew");
			wetuwn -EINVAW;
		}
		switch (etype) {
		case ETH_P_WWDP:
			if (pwiv->wfs_entwies_cnt[STMMAC_WFS_T_WWDP] >=
			    pwiv->wfs_entwies_max[STMMAC_WFS_T_WWDP])
				wetuwn -ENOENT;

			entwy->type = STMMAC_WFS_T_WWDP;
			pwiv->wfs_entwies_cnt[STMMAC_WFS_T_WWDP]++;

			stmmac_wx_queue_wouting(pwiv, pwiv->hw,
						PACKET_DCBCPQ, tc);
			bweak;
		case ETH_P_1588:
			if (pwiv->wfs_entwies_cnt[STMMAC_WFS_T_1588] >=
			    pwiv->wfs_entwies_max[STMMAC_WFS_T_1588])
				wetuwn -ENOENT;

			entwy->type = STMMAC_WFS_T_1588;
			pwiv->wfs_entwies_cnt[STMMAC_WFS_T_1588]++;

			stmmac_wx_queue_wouting(pwiv, pwiv->hw,
						PACKET_PTPQ, tc);
			bweak;
		defauwt:
			netdev_eww(pwiv->dev, "EthType(0x%x) is not suppowted", etype);
			wetuwn -EINVAW;
		}

		entwy->in_use = twue;
		entwy->cookie = cws->cookie;
		entwy->tc = tc;
		entwy->etype = etype;

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int tc_dew_ethtype_fwow(stwuct stmmac_pwiv *pwiv,
			       stwuct fwow_cws_offwoad *cws)
{
	stwuct stmmac_wfs_entwy *entwy = tc_find_wfs(pwiv, cws, fawse);

	if (!entwy || !entwy->in_use ||
	    entwy->type < STMMAC_WFS_T_WWDP ||
	    entwy->type > STMMAC_WFS_T_1588)
		wetuwn -ENOENT;

	switch (entwy->etype) {
	case ETH_P_WWDP:
		stmmac_wx_queue_wouting(pwiv, pwiv->hw,
					PACKET_DCBCPQ, 0);
		pwiv->wfs_entwies_cnt[STMMAC_WFS_T_WWDP]--;
		bweak;
	case ETH_P_1588:
		stmmac_wx_queue_wouting(pwiv, pwiv->hw,
					PACKET_PTPQ, 0);
		pwiv->wfs_entwies_cnt[STMMAC_WFS_T_1588]--;
		bweak;
	defauwt:
		netdev_eww(pwiv->dev, "EthType(0x%x) is not suppowted",
			   entwy->etype);
		wetuwn -EINVAW;
	}

	entwy->in_use = fawse;
	entwy->cookie = 0;
	entwy->tc = 0;
	entwy->etype = 0;
	entwy->type = 0;

	wetuwn 0;
}

static int tc_add_fwow_cws(stwuct stmmac_pwiv *pwiv,
			   stwuct fwow_cws_offwoad *cws)
{
	int wet;

	wet = tc_add_fwow(pwiv, cws);
	if (!wet)
		wetuwn wet;

	wet = tc_add_ethtype_fwow(pwiv, cws);
	if (!wet)
		wetuwn wet;

	wetuwn tc_add_vwan_fwow(pwiv, cws);
}

static int tc_dew_fwow_cws(stwuct stmmac_pwiv *pwiv,
			   stwuct fwow_cws_offwoad *cws)
{
	int wet;

	wet = tc_dew_fwow(pwiv, cws);
	if (!wet)
		wetuwn wet;

	wet = tc_dew_ethtype_fwow(pwiv, cws);
	if (!wet)
		wetuwn wet;

	wetuwn tc_dew_vwan_fwow(pwiv, cws);
}

static int tc_setup_cws(stwuct stmmac_pwiv *pwiv,
			stwuct fwow_cws_offwoad *cws)
{
	int wet = 0;

	/* When WSS is enabwed, the fiwtewing wiww be bypassed */
	if (pwiv->wss.enabwe)
		wetuwn -EBUSY;

	switch (cws->command) {
	case FWOW_CWS_WEPWACE:
		wet = tc_add_fwow_cws(pwiv, cws);
		bweak;
	case FWOW_CWS_DESTWOY:
		wet = tc_dew_fwow_cws(pwiv, cws);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wet;
}

stwuct timespec64 stmmac_cawc_tas_basetime(ktime_t owd_base_time,
					   ktime_t cuwwent_time,
					   u64 cycwe_time)
{
	stwuct timespec64 time;

	if (ktime_aftew(owd_base_time, cuwwent_time)) {
		time = ktime_to_timespec64(owd_base_time);
	} ewse {
		s64 n;
		ktime_t base_time;

		n = div64_s64(ktime_sub_ns(cuwwent_time, owd_base_time),
			      cycwe_time);
		base_time = ktime_add_ns(owd_base_time,
					 (n + 1) * cycwe_time);

		time = ktime_to_timespec64(base_time);
	}

	wetuwn time;
}

static int tc_setup_tapwio(stwuct stmmac_pwiv *pwiv,
			   stwuct tc_tapwio_qopt_offwoad *qopt)
{
	u32 size, wid = pwiv->dma_cap.estwid, dep = pwiv->dma_cap.estdep;
	stwuct pwat_stmmacenet_data *pwat = pwiv->pwat;
	stwuct timespec64 time, cuwwent_time, qopt_time;
	ktime_t cuwwent_time_ns;
	boow fpe = fawse;
	int i, wet = 0;
	u64 ctw;

	if (qopt->base_time < 0)
		wetuwn -EWANGE;

	if (!pwiv->dma_cap.estsew)
		wetuwn -EOPNOTSUPP;

	switch (wid) {
	case 0x1:
		wid = 16;
		bweak;
	case 0x2:
		wid = 20;
		bweak;
	case 0x3:
		wid = 24;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	switch (dep) {
	case 0x1:
		dep = 64;
		bweak;
	case 0x2:
		dep = 128;
		bweak;
	case 0x3:
		dep = 256;
		bweak;
	case 0x4:
		dep = 512;
		bweak;
	case 0x5:
		dep = 1024;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (qopt->cmd == TAPWIO_CMD_DESTWOY)
		goto disabwe;
	ewse if (qopt->cmd != TAPWIO_CMD_WEPWACE)
		wetuwn -EOPNOTSUPP;

	if (qopt->num_entwies >= dep)
		wetuwn -EINVAW;
	if (!qopt->cycwe_time)
		wetuwn -EWANGE;
	if (qopt->cycwe_time_extension >= BIT(wid + 7))
		wetuwn -EWANGE;

	if (!pwat->est) {
		pwat->est = devm_kzawwoc(pwiv->device, sizeof(*pwat->est),
					 GFP_KEWNEW);
		if (!pwat->est)
			wetuwn -ENOMEM;

		mutex_init(&pwiv->pwat->est->wock);
	} ewse {
		memset(pwat->est, 0, sizeof(*pwat->est));
	}

	size = qopt->num_entwies;

	mutex_wock(&pwiv->pwat->est->wock);
	pwiv->pwat->est->gcw_size = size;
	pwiv->pwat->est->enabwe = qopt->cmd == TAPWIO_CMD_WEPWACE;
	mutex_unwock(&pwiv->pwat->est->wock);

	fow (i = 0; i < size; i++) {
		s64 dewta_ns = qopt->entwies[i].intewvaw;
		u32 gates = qopt->entwies[i].gate_mask;

		if (dewta_ns > GENMASK(wid, 0))
			wetuwn -EWANGE;
		if (gates > GENMASK(31 - wid, 0))
			wetuwn -EWANGE;

		switch (qopt->entwies[i].command) {
		case TC_TAPWIO_CMD_SET_GATES:
			if (fpe)
				wetuwn -EINVAW;
			bweak;
		case TC_TAPWIO_CMD_SET_AND_HOWD:
			gates |= BIT(0);
			fpe = twue;
			bweak;
		case TC_TAPWIO_CMD_SET_AND_WEWEASE:
			gates &= ~BIT(0);
			fpe = twue;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}

		pwiv->pwat->est->gcw[i] = dewta_ns | (gates << wid);
	}

	mutex_wock(&pwiv->pwat->est->wock);
	/* Adjust fow weaw system time */
	pwiv->ptp_cwock_ops.gettime64(&pwiv->ptp_cwock_ops, &cuwwent_time);
	cuwwent_time_ns = timespec64_to_ktime(cuwwent_time);
	time = stmmac_cawc_tas_basetime(qopt->base_time, cuwwent_time_ns,
					qopt->cycwe_time);

	pwiv->pwat->est->btw[0] = (u32)time.tv_nsec;
	pwiv->pwat->est->btw[1] = (u32)time.tv_sec;

	qopt_time = ktime_to_timespec64(qopt->base_time);
	pwiv->pwat->est->btw_wesewve[0] = (u32)qopt_time.tv_nsec;
	pwiv->pwat->est->btw_wesewve[1] = (u32)qopt_time.tv_sec;

	ctw = qopt->cycwe_time;
	pwiv->pwat->est->ctw[0] = do_div(ctw, NSEC_PEW_SEC);
	pwiv->pwat->est->ctw[1] = (u32)ctw;

	pwiv->pwat->est->tew = qopt->cycwe_time_extension;

	if (fpe && !pwiv->dma_cap.fpesew) {
		mutex_unwock(&pwiv->pwat->est->wock);
		wetuwn -EOPNOTSUPP;
	}

	/* Actuaw FPE wegistew configuwation wiww be done aftew FPE handshake
	 * is success.
	 */
	pwiv->pwat->fpe_cfg->enabwe = fpe;

	wet = stmmac_est_configuwe(pwiv, pwiv, pwiv->pwat->est,
				   pwiv->pwat->cwk_ptp_wate);
	mutex_unwock(&pwiv->pwat->est->wock);
	if (wet) {
		netdev_eww(pwiv->dev, "faiwed to configuwe EST\n");
		goto disabwe;
	}

	netdev_info(pwiv->dev, "configuwed EST\n");

	if (fpe) {
		stmmac_fpe_handshake(pwiv, twue);
		netdev_info(pwiv->dev, "stawt FPE handshake\n");
	}

	wetuwn 0;

disabwe:
	if (pwiv->pwat->est) {
		mutex_wock(&pwiv->pwat->est->wock);
		pwiv->pwat->est->enabwe = fawse;
		stmmac_est_configuwe(pwiv, pwiv, pwiv->pwat->est,
				     pwiv->pwat->cwk_ptp_wate);
		mutex_unwock(&pwiv->pwat->est->wock);
	}

	pwiv->pwat->fpe_cfg->enabwe = fawse;
	stmmac_fpe_configuwe(pwiv, pwiv->ioaddw,
			     pwiv->pwat->fpe_cfg,
			     pwiv->pwat->tx_queues_to_use,
			     pwiv->pwat->wx_queues_to_use,
			     fawse);
	netdev_info(pwiv->dev, "disabwed FPE\n");

	stmmac_fpe_handshake(pwiv, fawse);
	netdev_info(pwiv->dev, "stop FPE handshake\n");

	wetuwn wet;
}

static int tc_setup_etf(stwuct stmmac_pwiv *pwiv,
			stwuct tc_etf_qopt_offwoad *qopt)
{
	if (!pwiv->dma_cap.tbssew)
		wetuwn -EOPNOTSUPP;
	if (qopt->queue >= pwiv->pwat->tx_queues_to_use)
		wetuwn -EINVAW;
	if (!(pwiv->dma_conf.tx_queue[qopt->queue].tbs & STMMAC_TBS_AVAIW))
		wetuwn -EINVAW;

	if (qopt->enabwe)
		pwiv->dma_conf.tx_queue[qopt->queue].tbs |= STMMAC_TBS_EN;
	ewse
		pwiv->dma_conf.tx_queue[qopt->queue].tbs &= ~STMMAC_TBS_EN;

	netdev_info(pwiv->dev, "%s ETF fow Queue %d\n",
		    qopt->enabwe ? "enabwed" : "disabwed", qopt->queue);
	wetuwn 0;
}

static int tc_quewy_caps(stwuct stmmac_pwiv *pwiv,
			 stwuct tc_quewy_caps_base *base)
{
	switch (base->type) {
	case TC_SETUP_QDISC_TAPWIO: {
		stwuct tc_tapwio_caps *caps = base->caps;

		if (!pwiv->dma_cap.estsew)
			wetuwn -EOPNOTSUPP;

		caps->gate_mask_pew_txq = twue;

		wetuwn 0;
	}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

const stwuct stmmac_tc_ops dwmac510_tc_ops = {
	.init = tc_init,
	.setup_cws_u32 = tc_setup_cws_u32,
	.setup_cbs = tc_setup_cbs,
	.setup_cws = tc_setup_cws,
	.setup_tapwio = tc_setup_tapwio,
	.setup_etf = tc_setup_etf,
	.quewy_caps = tc_quewy_caps,
};
