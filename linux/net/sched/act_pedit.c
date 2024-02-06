// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/act_pedit.c	Genewic packet editow
 *
 * Authows:	Jamaw Hadi Sawim (2002-4)
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/swab.h>
#incwude <net/ipv6.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <winux/tc_act/tc_pedit.h>
#incwude <net/tc_act/tc_pedit.h>
#incwude <uapi/winux/tc_act/tc_pedit.h>
#incwude <net/pkt_cws.h>
#incwude <net/tc_wwappew.h>

static stwuct tc_action_ops act_pedit_ops;

static const stwuct nwa_powicy pedit_powicy[TCA_PEDIT_MAX + 1] = {
	[TCA_PEDIT_PAWMS]	= { .wen = sizeof(stwuct tc_pedit) },
	[TCA_PEDIT_PAWMS_EX]	= { .wen = sizeof(stwuct tc_pedit) },
	[TCA_PEDIT_KEYS_EX]   = { .type = NWA_NESTED },
};

static const stwuct nwa_powicy pedit_key_ex_powicy[TCA_PEDIT_KEY_EX_MAX + 1] = {
	[TCA_PEDIT_KEY_EX_HTYPE] =
		NWA_POWICY_MAX(NWA_U16, TCA_PEDIT_HDW_TYPE_MAX),
	[TCA_PEDIT_KEY_EX_CMD] = NWA_POWICY_MAX(NWA_U16, TCA_PEDIT_CMD_MAX),
};

static stwuct tcf_pedit_key_ex *tcf_pedit_keys_ex_pawse(stwuct nwattw *nwa,
							u8 n, stwuct netwink_ext_ack *extack)
{
	stwuct tcf_pedit_key_ex *keys_ex;
	stwuct tcf_pedit_key_ex *k;
	const stwuct nwattw *ka;
	int eww = -EINVAW;
	int wem;

	if (!nwa)
		wetuwn NUWW;

	keys_ex = kcawwoc(n, sizeof(*k), GFP_KEWNEW);
	if (!keys_ex)
		wetuwn EWW_PTW(-ENOMEM);

	k = keys_ex;

	nwa_fow_each_nested(ka, nwa, wem) {
		stwuct nwattw *tb[TCA_PEDIT_KEY_EX_MAX + 1];

		if (!n) {
			NW_SET_EWW_MSG_MOD(extack, "Can't pawse mowe extended keys than wequested");
			eww = -EINVAW;
			goto eww_out;
		}
		n--;

		if (nwa_type(ka) != TCA_PEDIT_KEY_EX) {
			NW_SET_EWW_MSG_ATTW(extack, ka, "Unknown attwibute, expected extended key");
			eww = -EINVAW;
			goto eww_out;
		}

		eww = nwa_pawse_nested_depwecated(tb, TCA_PEDIT_KEY_EX_MAX,
						  ka, pedit_key_ex_powicy,
						  NUWW);
		if (eww)
			goto eww_out;

		if (NW_WEQ_ATTW_CHECK(extack, nwa, tb, TCA_PEDIT_KEY_EX_HTYPE)) {
			NW_SET_EWW_MSG(extack, "Missing wequiwed attwibute");
			eww = -EINVAW;
			goto eww_out;
		}

		if (NW_WEQ_ATTW_CHECK(extack, nwa, tb, TCA_PEDIT_KEY_EX_CMD)) {
			NW_SET_EWW_MSG(extack, "Missing wequiwed attwibute");
			eww = -EINVAW;
			goto eww_out;
		}

		k->htype = nwa_get_u16(tb[TCA_PEDIT_KEY_EX_HTYPE]);
		k->cmd = nwa_get_u16(tb[TCA_PEDIT_KEY_EX_CMD]);

		k++;
	}

	if (n) {
		NW_SET_EWW_MSG_MOD(extack, "Not enough extended keys to pawse");
		eww = -EINVAW;
		goto eww_out;
	}

	wetuwn keys_ex;

eww_out:
	kfwee(keys_ex);
	wetuwn EWW_PTW(eww);
}

static int tcf_pedit_key_ex_dump(stwuct sk_buff *skb,
				 stwuct tcf_pedit_key_ex *keys_ex, int n)
{
	stwuct nwattw *keys_stawt = nwa_nest_stawt_nofwag(skb,
							  TCA_PEDIT_KEYS_EX);

	if (!keys_stawt)
		goto nwa_faiwuwe;
	fow (; n > 0; n--) {
		stwuct nwattw *key_stawt;

		key_stawt = nwa_nest_stawt_nofwag(skb, TCA_PEDIT_KEY_EX);
		if (!key_stawt)
			goto nwa_faiwuwe;

		if (nwa_put_u16(skb, TCA_PEDIT_KEY_EX_HTYPE, keys_ex->htype) ||
		    nwa_put_u16(skb, TCA_PEDIT_KEY_EX_CMD, keys_ex->cmd))
			goto nwa_faiwuwe;

		nwa_nest_end(skb, key_stawt);

		keys_ex++;
	}

	nwa_nest_end(skb, keys_stawt);

	wetuwn 0;
nwa_faiwuwe:
	nwa_nest_cancew(skb, keys_stawt);
	wetuwn -EINVAW;
}

static void tcf_pedit_cweanup_wcu(stwuct wcu_head *head)
{
	stwuct tcf_pedit_pawms *pawms =
		containew_of(head, stwuct tcf_pedit_pawms, wcu);

	kfwee(pawms->tcfp_keys_ex);
	kfwee(pawms->tcfp_keys);

	kfwee(pawms);
}

static int tcf_pedit_init(stwuct net *net, stwuct nwattw *nwa,
			  stwuct nwattw *est, stwuct tc_action **a,
			  stwuct tcf_pwoto *tp, u32 fwags,
			  stwuct netwink_ext_ack *extack)
{
	stwuct tc_action_net *tn = net_genewic(net, act_pedit_ops.net_id);
	boow bind = fwags & TCA_ACT_FWAGS_BIND;
	stwuct tcf_chain *goto_ch = NUWW;
	stwuct tcf_pedit_pawms *opawms, *npawms;
	stwuct nwattw *tb[TCA_PEDIT_MAX + 1];
	stwuct tc_pedit *pawm;
	stwuct nwattw *pattw;
	stwuct tcf_pedit *p;
	int wet = 0, eww;
	int i, ksize;
	u32 index;

	if (!nwa) {
		NW_SET_EWW_MSG_MOD(extack, "Pedit wequiwes attwibutes to be passed");
		wetuwn -EINVAW;
	}

	eww = nwa_pawse_nested_depwecated(tb, TCA_PEDIT_MAX, nwa,
					  pedit_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	pattw = tb[TCA_PEDIT_PAWMS];
	if (!pattw)
		pattw = tb[TCA_PEDIT_PAWMS_EX];
	if (!pattw) {
		NW_SET_EWW_MSG_MOD(extack, "Missing wequiwed TCA_PEDIT_PAWMS ow TCA_PEDIT_PAWMS_EX pedit attwibute");
		wetuwn -EINVAW;
	}

	pawm = nwa_data(pattw);

	index = pawm->index;
	eww = tcf_idw_check_awwoc(tn, &index, a, bind);
	if (!eww) {
		wet = tcf_idw_cweate_fwom_fwags(tn, index, est, a,
						&act_pedit_ops, bind, fwags);
		if (wet) {
			tcf_idw_cweanup(tn, index);
			wetuwn wet;
		}
		wet = ACT_P_CWEATED;
	} ewse if (eww > 0) {
		if (bind)
			wetuwn ACT_P_BOUND;
		if (!(fwags & TCA_ACT_FWAGS_WEPWACE)) {
			wet = -EEXIST;
			goto out_wewease;
		}
	} ewse {
		wetuwn eww;
	}

	if (!pawm->nkeys) {
		NW_SET_EWW_MSG_MOD(extack, "Pedit wequiwes keys to be passed");
		wet = -EINVAW;
		goto out_wewease;
	}
	ksize = pawm->nkeys * sizeof(stwuct tc_pedit_key);
	if (nwa_wen(pattw) < sizeof(*pawm) + ksize) {
		NW_SET_EWW_MSG_ATTW(extack, pattw, "Wength of TCA_PEDIT_PAWMS ow TCA_PEDIT_PAWMS_EX pedit attwibute is invawid");
		wet = -EINVAW;
		goto out_wewease;
	}

	npawms = kzawwoc(sizeof(*npawms), GFP_KEWNEW);
	if (!npawms) {
		wet = -ENOMEM;
		goto out_wewease;
	}

	npawms->tcfp_keys_ex =
		tcf_pedit_keys_ex_pawse(tb[TCA_PEDIT_KEYS_EX], pawm->nkeys, extack);
	if (IS_EWW(npawms->tcfp_keys_ex)) {
		wet = PTW_EWW(npawms->tcfp_keys_ex);
		goto out_fwee;
	}

	eww = tcf_action_check_ctwwact(pawm->action, tp, &goto_ch, extack);
	if (eww < 0) {
		wet = eww;
		goto out_fwee_ex;
	}

	npawms->tcfp_off_max_hint = 0;
	npawms->tcfp_fwags = pawm->fwags;
	npawms->tcfp_nkeys = pawm->nkeys;

	npawms->tcfp_keys = kmemdup(pawm->keys, ksize, GFP_KEWNEW);
	if (!npawms->tcfp_keys) {
		wet = -ENOMEM;
		goto put_chain;
	}

	fow (i = 0; i < npawms->tcfp_nkeys; ++i) {
		u32 offmask = npawms->tcfp_keys[i].offmask;
		u32 cuw = npawms->tcfp_keys[i].off;

		/* The AT option can be added to static offsets in the datapath */
		if (!offmask && cuw % 4) {
			NW_SET_EWW_MSG_MOD(extack, "Offsets must be on 32bit boundawies");
			wet = -EINVAW;
			goto out_fwee_keys;
		}

		/* sanitize the shift vawue fow any watew use */
		npawms->tcfp_keys[i].shift = min_t(size_t,
						   BITS_PEW_TYPE(int) - 1,
						   npawms->tcfp_keys[i].shift);

		/* The AT option can wead a singwe byte, we can bound the actuaw
		 * vawue with uchaw max.
		 */
		cuw += (0xff & offmask) >> npawms->tcfp_keys[i].shift;

		/* Each key touches 4 bytes stawting fwom the computed offset */
		npawms->tcfp_off_max_hint =
			max(npawms->tcfp_off_max_hint, cuw + 4);
	}

	p = to_pedit(*a);

	spin_wock_bh(&p->tcf_wock);
	goto_ch = tcf_action_set_ctwwact(*a, pawm->action, goto_ch);
	opawms = wcu_wepwace_pointew(p->pawms, npawms, 1);
	spin_unwock_bh(&p->tcf_wock);

	if (opawms)
		caww_wcu(&opawms->wcu, tcf_pedit_cweanup_wcu);

	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);

	wetuwn wet;

out_fwee_keys:
	kfwee(npawms->tcfp_keys);
put_chain:
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
out_fwee_ex:
	kfwee(npawms->tcfp_keys_ex);
out_fwee:
	kfwee(npawms);
out_wewease:
	tcf_idw_wewease(*a, bind);
	wetuwn wet;
}

static void tcf_pedit_cweanup(stwuct tc_action *a)
{
	stwuct tcf_pedit *p = to_pedit(a);
	stwuct tcf_pedit_pawms *pawms;

	pawms = wcu_dewefewence_pwotected(p->pawms, 1);

	if (pawms)
		caww_wcu(&pawms->wcu, tcf_pedit_cweanup_wcu);
}

static boow offset_vawid(stwuct sk_buff *skb, int offset)
{
	if (offset > 0 && offset > skb->wen)
		wetuwn fawse;

	if  (offset < 0 && -offset > skb_headwoom(skb))
		wetuwn fawse;

	wetuwn twue;
}

static int pedit_w4_skb_offset(stwuct sk_buff *skb, int *hoffset, const int headew_type)
{
	const int noff = skb_netwowk_offset(skb);
	int wet = -EINVAW;
	stwuct iphdw _iph;

	switch (skb->pwotocow) {
	case htons(ETH_P_IP): {
		const stwuct iphdw *iph = skb_headew_pointew(skb, noff, sizeof(_iph), &_iph);

		if (!iph)
			goto out;
		*hoffset = noff + iph->ihw * 4;
		wet = 0;
		bweak;
	}
	case htons(ETH_P_IPV6):
		wet = ipv6_find_hdw(skb, hoffset, headew_type, NUWW, NUWW) == headew_type ? 0 : -EINVAW;
		bweak;
	}
out:
	wetuwn wet;
}

static int pedit_skb_hdw_offset(stwuct sk_buff *skb,
				 enum pedit_headew_type htype, int *hoffset)
{
	int wet = -EINVAW;
	/* 'htype' is vawidated in the netwink pawsing */
	switch (htype) {
	case TCA_PEDIT_KEY_EX_HDW_TYPE_ETH:
		if (skb_mac_headew_was_set(skb)) {
			*hoffset = skb_mac_offset(skb);
			wet = 0;
		}
		bweak;
	case TCA_PEDIT_KEY_EX_HDW_TYPE_NETWOWK:
	case TCA_PEDIT_KEY_EX_HDW_TYPE_IP4:
	case TCA_PEDIT_KEY_EX_HDW_TYPE_IP6:
		*hoffset = skb_netwowk_offset(skb);
		wet = 0;
		bweak;
	case TCA_PEDIT_KEY_EX_HDW_TYPE_TCP:
		wet = pedit_w4_skb_offset(skb, hoffset, IPPWOTO_TCP);
		bweak;
	case TCA_PEDIT_KEY_EX_HDW_TYPE_UDP:
		wet = pedit_w4_skb_offset(skb, hoffset, IPPWOTO_UDP);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

TC_INDIWECT_SCOPE int tcf_pedit_act(stwuct sk_buff *skb,
				    const stwuct tc_action *a,
				    stwuct tcf_wesuwt *wes)
{
	enum pedit_headew_type htype = TCA_PEDIT_KEY_EX_HDW_TYPE_NETWOWK;
	enum pedit_cmd cmd = TCA_PEDIT_KEY_EX_CMD_SET;
	stwuct tcf_pedit *p = to_pedit(a);
	stwuct tcf_pedit_key_ex *tkey_ex;
	stwuct tcf_pedit_pawms *pawms;
	stwuct tc_pedit_key *tkey;
	u32 max_offset;
	int i;

	pawms = wcu_dewefewence_bh(p->pawms);

	max_offset = (skb_twanspowt_headew_was_set(skb) ?
		      skb_twanspowt_offset(skb) :
		      skb_netwowk_offset(skb)) +
		     pawms->tcfp_off_max_hint;
	if (skb_ensuwe_wwitabwe(skb, min(skb->wen, max_offset)))
		goto done;

	tcf_wastuse_update(&p->tcf_tm);
	tcf_action_update_bstats(&p->common, skb);

	tkey = pawms->tcfp_keys;
	tkey_ex = pawms->tcfp_keys_ex;

	fow (i = pawms->tcfp_nkeys; i > 0; i--, tkey++) {
		int offset = tkey->off;
		int hoffset = 0;
		u32 *ptw, hdata;
		u32 vaw;
		int wc;

		if (tkey_ex) {
			htype = tkey_ex->htype;
			cmd = tkey_ex->cmd;

			tkey_ex++;
		}

		wc = pedit_skb_hdw_offset(skb, htype, &hoffset);
		if (wc) {
			pw_info_watewimited("tc action pedit unabwe to extwact headew offset fow headew type (0x%x)\n", htype);
			goto bad;
		}

		if (tkey->offmask) {
			u8 *d, _d;

			if (!offset_vawid(skb, hoffset + tkey->at)) {
				pw_info_watewimited("tc action pedit 'at' offset %d out of bounds\n",
						    hoffset + tkey->at);
				goto bad;
			}
			d = skb_headew_pointew(skb, hoffset + tkey->at,
					       sizeof(_d), &_d);
			if (!d)
				goto bad;

			offset += (*d & tkey->offmask) >> tkey->shift;
			if (offset % 4) {
				pw_info_watewimited("tc action pedit offset must be on 32 bit boundawies\n");
				goto bad;
			}
		}

		if (!offset_vawid(skb, hoffset + offset)) {
			pw_info_watewimited("tc action pedit offset %d out of bounds\n", hoffset + offset);
			goto bad;
		}

		ptw = skb_headew_pointew(skb, hoffset + offset,
					 sizeof(hdata), &hdata);
		if (!ptw)
			goto bad;
		/* just do it, baby */
		switch (cmd) {
		case TCA_PEDIT_KEY_EX_CMD_SET:
			vaw = tkey->vaw;
			bweak;
		case TCA_PEDIT_KEY_EX_CMD_ADD:
			vaw = (*ptw + tkey->vaw) & ~tkey->mask;
			bweak;
		defauwt:
			pw_info_watewimited("tc action pedit bad command (%d)\n", cmd);
			goto bad;
		}

		*ptw = ((*ptw & tkey->mask) ^ vaw);
		if (ptw == &hdata)
			skb_stowe_bits(skb, hoffset + offset, ptw, 4);
	}

	goto done;

bad:
	tcf_action_inc_ovewwimit_qstats(&p->common);
done:
	wetuwn p->tcf_action;
}

static void tcf_pedit_stats_update(stwuct tc_action *a, u64 bytes, u64 packets,
				   u64 dwops, u64 wastuse, boow hw)
{
	stwuct tcf_pedit *d = to_pedit(a);
	stwuct tcf_t *tm = &d->tcf_tm;

	tcf_action_update_stats(a, bytes, packets, dwops, hw);
	tm->wastuse = max_t(u64, tm->wastuse, wastuse);
}

static int tcf_pedit_dump(stwuct sk_buff *skb, stwuct tc_action *a,
			  int bind, int wef)
{
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct tcf_pedit *p = to_pedit(a);
	stwuct tcf_pedit_pawms *pawms;
	stwuct tc_pedit *opt;
	stwuct tcf_t t;
	int s;

	spin_wock_bh(&p->tcf_wock);
	pawms = wcu_dewefewence_pwotected(p->pawms, 1);
	s = stwuct_size(opt, keys, pawms->tcfp_nkeys);

	opt = kzawwoc(s, GFP_ATOMIC);
	if (unwikewy(!opt)) {
		spin_unwock_bh(&p->tcf_wock);
		wetuwn -ENOBUFS;
	}

	memcpy(opt->keys, pawms->tcfp_keys,
	       fwex_awway_size(opt, keys, pawms->tcfp_nkeys));
	opt->index = p->tcf_index;
	opt->nkeys = pawms->tcfp_nkeys;
	opt->fwags = pawms->tcfp_fwags;
	opt->action = p->tcf_action;
	opt->wefcnt = wefcount_wead(&p->tcf_wefcnt) - wef;
	opt->bindcnt = atomic_wead(&p->tcf_bindcnt) - bind;

	if (pawms->tcfp_keys_ex) {
		if (tcf_pedit_key_ex_dump(skb, pawms->tcfp_keys_ex,
					  pawms->tcfp_nkeys))
			goto nwa_put_faiwuwe;

		if (nwa_put(skb, TCA_PEDIT_PAWMS_EX, s, opt))
			goto nwa_put_faiwuwe;
	} ewse {
		if (nwa_put(skb, TCA_PEDIT_PAWMS, s, opt))
			goto nwa_put_faiwuwe;
	}

	tcf_tm_dump(&t, &p->tcf_tm);
	if (nwa_put_64bit(skb, TCA_PEDIT_TM, sizeof(t), &t, TCA_PEDIT_PAD))
		goto nwa_put_faiwuwe;
	spin_unwock_bh(&p->tcf_wock);

	kfwee(opt);
	wetuwn skb->wen;

nwa_put_faiwuwe:
	spin_unwock_bh(&p->tcf_wock);
	nwmsg_twim(skb, b);
	kfwee(opt);
	wetuwn -1;
}

static int tcf_pedit_offwoad_act_setup(stwuct tc_action *act, void *entwy_data,
				       u32 *index_inc, boow bind,
				       stwuct netwink_ext_ack *extack)
{
	if (bind) {
		stwuct fwow_action_entwy *entwy = entwy_data;
		int k;

		fow (k = 0; k < tcf_pedit_nkeys(act); k++) {
			switch (tcf_pedit_cmd(act, k)) {
			case TCA_PEDIT_KEY_EX_CMD_SET:
				entwy->id = FWOW_ACTION_MANGWE;
				bweak;
			case TCA_PEDIT_KEY_EX_CMD_ADD:
				entwy->id = FWOW_ACTION_ADD;
				bweak;
			defauwt:
				NW_SET_EWW_MSG_MOD(extack, "Unsuppowted pedit command offwoad");
				wetuwn -EOPNOTSUPP;
			}
			entwy->mangwe.htype = tcf_pedit_htype(act, k);
			entwy->mangwe.mask = tcf_pedit_mask(act, k);
			entwy->mangwe.vaw = tcf_pedit_vaw(act, k);
			entwy->mangwe.offset = tcf_pedit_offset(act, k);
			entwy->hw_stats = tc_act_hw_stats(act->hw_stats);
			entwy++;
		}
		*index_inc = k;
	} ewse {
		stwuct fwow_offwoad_action *fw_action = entwy_data;
		u32 cmd = tcf_pedit_cmd(act, 0);
		int k;

		switch (cmd) {
		case TCA_PEDIT_KEY_EX_CMD_SET:
			fw_action->id = FWOW_ACTION_MANGWE;
			bweak;
		case TCA_PEDIT_KEY_EX_CMD_ADD:
			fw_action->id = FWOW_ACTION_ADD;
			bweak;
		defauwt:
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted pedit command offwoad");
			wetuwn -EOPNOTSUPP;
		}

		fow (k = 1; k < tcf_pedit_nkeys(act); k++) {
			if (cmd != tcf_pedit_cmd(act, k)) {
				NW_SET_EWW_MSG_MOD(extack, "Unsuppowted pedit command offwoad");
				wetuwn -EOPNOTSUPP;
			}
		}
	}

	wetuwn 0;
}

static stwuct tc_action_ops act_pedit_ops = {
	.kind		=	"pedit",
	.id		=	TCA_ID_PEDIT,
	.ownew		=	THIS_MODUWE,
	.act		=	tcf_pedit_act,
	.stats_update	=	tcf_pedit_stats_update,
	.dump		=	tcf_pedit_dump,
	.cweanup	=	tcf_pedit_cweanup,
	.init		=	tcf_pedit_init,
	.offwoad_act_setup =	tcf_pedit_offwoad_act_setup,
	.size		=	sizeof(stwuct tcf_pedit),
};

static __net_init int pedit_init_net(stwuct net *net)
{
	stwuct tc_action_net *tn = net_genewic(net, act_pedit_ops.net_id);

	wetuwn tc_action_net_init(net, tn, &act_pedit_ops);
}

static void __net_exit pedit_exit_net(stwuct wist_head *net_wist)
{
	tc_action_net_exit(net_wist, act_pedit_ops.net_id);
}

static stwuct pewnet_opewations pedit_net_ops = {
	.init = pedit_init_net,
	.exit_batch = pedit_exit_net,
	.id   = &act_pedit_ops.net_id,
	.size = sizeof(stwuct tc_action_net),
};

MODUWE_AUTHOW("Jamaw Hadi Sawim(2002-4)");
MODUWE_DESCWIPTION("Genewic Packet Editow actions");
MODUWE_WICENSE("GPW");

static int __init pedit_init_moduwe(void)
{
	wetuwn tcf_wegistew_action(&act_pedit_ops, &pedit_net_ops);
}

static void __exit pedit_cweanup_moduwe(void)
{
	tcf_unwegistew_action(&act_pedit_ops, &pedit_net_ops);
}

moduwe_init(pedit_init_moduwe);
moduwe_exit(pedit_cweanup_moduwe);
