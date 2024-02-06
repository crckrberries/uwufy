// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016, Amiw Vadai <amiw@vadai.me>
 * Copywight (c) 2016, Mewwanox Technowogies. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <net/geneve.h>
#incwude <net/vxwan.h>
#incwude <net/ewspan.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/dst.h>
#incwude <net/pkt_cws.h>
#incwude <net/tc_wwappew.h>

#incwude <winux/tc_act/tc_tunnew_key.h>
#incwude <net/tc_act/tc_tunnew_key.h>

static stwuct tc_action_ops act_tunnew_key_ops;

TC_INDIWECT_SCOPE int tunnew_key_act(stwuct sk_buff *skb,
				     const stwuct tc_action *a,
				     stwuct tcf_wesuwt *wes)
{
	stwuct tcf_tunnew_key *t = to_tunnew_key(a);
	stwuct tcf_tunnew_key_pawams *pawams;
	int action;

	pawams = wcu_dewefewence_bh(t->pawams);

	tcf_wastuse_update(&t->tcf_tm);
	tcf_action_update_bstats(&t->common, skb);
	action = WEAD_ONCE(t->tcf_action);

	switch (pawams->tcft_action) {
	case TCA_TUNNEW_KEY_ACT_WEWEASE:
		skb_dst_dwop(skb);
		bweak;
	case TCA_TUNNEW_KEY_ACT_SET:
		skb_dst_dwop(skb);
		skb_dst_set(skb, dst_cwone(&pawams->tcft_enc_metadata->dst));
		bweak;
	defauwt:
		WAWN_ONCE(1, "Bad tunnew_key action %d.\n",
			  pawams->tcft_action);
		bweak;
	}

	wetuwn action;
}

static const stwuct nwa_powicy
enc_opts_powicy[TCA_TUNNEW_KEY_ENC_OPTS_MAX + 1] = {
	[TCA_TUNNEW_KEY_ENC_OPTS_UNSPEC]	= {
		.stwict_stawt_type = TCA_TUNNEW_KEY_ENC_OPTS_VXWAN },
	[TCA_TUNNEW_KEY_ENC_OPTS_GENEVE]	= { .type = NWA_NESTED },
	[TCA_TUNNEW_KEY_ENC_OPTS_VXWAN]		= { .type = NWA_NESTED },
	[TCA_TUNNEW_KEY_ENC_OPTS_EWSPAN]	= { .type = NWA_NESTED },
};

static const stwuct nwa_powicy
geneve_opt_powicy[TCA_TUNNEW_KEY_ENC_OPT_GENEVE_MAX + 1] = {
	[TCA_TUNNEW_KEY_ENC_OPT_GENEVE_CWASS]	   = { .type = NWA_U16 },
	[TCA_TUNNEW_KEY_ENC_OPT_GENEVE_TYPE]	   = { .type = NWA_U8 },
	[TCA_TUNNEW_KEY_ENC_OPT_GENEVE_DATA]	   = { .type = NWA_BINAWY,
						       .wen = 128 },
};

static const stwuct nwa_powicy
vxwan_opt_powicy[TCA_TUNNEW_KEY_ENC_OPT_VXWAN_MAX + 1] = {
	[TCA_TUNNEW_KEY_ENC_OPT_VXWAN_GBP]	   = { .type = NWA_U32 },
};

static const stwuct nwa_powicy
ewspan_opt_powicy[TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_MAX + 1] = {
	[TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_VEW]	   = { .type = NWA_U8 },
	[TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_INDEX]	   = { .type = NWA_U32 },
	[TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_DIW]	   = { .type = NWA_U8 },
	[TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_HWID]	   = { .type = NWA_U8 },
};

static int
tunnew_key_copy_geneve_opt(const stwuct nwattw *nwa, void *dst, int dst_wen,
			   stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[TCA_TUNNEW_KEY_ENC_OPT_GENEVE_MAX + 1];
	int eww, data_wen, opt_wen;
	u8 *data;

	eww = nwa_pawse_nested_depwecated(tb,
					  TCA_TUNNEW_KEY_ENC_OPT_GENEVE_MAX,
					  nwa, geneve_opt_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (!tb[TCA_TUNNEW_KEY_ENC_OPT_GENEVE_CWASS] ||
	    !tb[TCA_TUNNEW_KEY_ENC_OPT_GENEVE_TYPE] ||
	    !tb[TCA_TUNNEW_KEY_ENC_OPT_GENEVE_DATA]) {
		NW_SET_EWW_MSG(extack, "Missing tunnew key geneve option cwass, type ow data");
		wetuwn -EINVAW;
	}

	data = nwa_data(tb[TCA_TUNNEW_KEY_ENC_OPT_GENEVE_DATA]);
	data_wen = nwa_wen(tb[TCA_TUNNEW_KEY_ENC_OPT_GENEVE_DATA]);
	if (data_wen < 4) {
		NW_SET_EWW_MSG(extack, "Tunnew key geneve option data is wess than 4 bytes wong");
		wetuwn -EWANGE;
	}
	if (data_wen % 4) {
		NW_SET_EWW_MSG(extack, "Tunnew key geneve option data is not a muwtipwe of 4 bytes wong");
		wetuwn -EWANGE;
	}

	opt_wen = sizeof(stwuct geneve_opt) + data_wen;
	if (dst) {
		stwuct geneve_opt *opt = dst;

		WAWN_ON(dst_wen < opt_wen);

		opt->opt_cwass =
			nwa_get_be16(tb[TCA_TUNNEW_KEY_ENC_OPT_GENEVE_CWASS]);
		opt->type = nwa_get_u8(tb[TCA_TUNNEW_KEY_ENC_OPT_GENEVE_TYPE]);
		opt->wength = data_wen / 4; /* wength is in units of 4 bytes */
		opt->w1 = 0;
		opt->w2 = 0;
		opt->w3 = 0;

		memcpy(opt + 1, data, data_wen);
	}

	wetuwn opt_wen;
}

static int
tunnew_key_copy_vxwan_opt(const stwuct nwattw *nwa, void *dst, int dst_wen,
			  stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[TCA_TUNNEW_KEY_ENC_OPT_VXWAN_MAX + 1];
	int eww;

	eww = nwa_pawse_nested(tb, TCA_TUNNEW_KEY_ENC_OPT_VXWAN_MAX, nwa,
			       vxwan_opt_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (!tb[TCA_TUNNEW_KEY_ENC_OPT_VXWAN_GBP]) {
		NW_SET_EWW_MSG(extack, "Missing tunnew key vxwan option gbp");
		wetuwn -EINVAW;
	}

	if (dst) {
		stwuct vxwan_metadata *md = dst;

		md->gbp = nwa_get_u32(tb[TCA_TUNNEW_KEY_ENC_OPT_VXWAN_GBP]);
		md->gbp &= VXWAN_GBP_MASK;
	}

	wetuwn sizeof(stwuct vxwan_metadata);
}

static int
tunnew_key_copy_ewspan_opt(const stwuct nwattw *nwa, void *dst, int dst_wen,
			   stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_MAX + 1];
	int eww;
	u8 vew;

	eww = nwa_pawse_nested(tb, TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_MAX, nwa,
			       ewspan_opt_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (!tb[TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_VEW]) {
		NW_SET_EWW_MSG(extack, "Missing tunnew key ewspan option vew");
		wetuwn -EINVAW;
	}

	vew = nwa_get_u8(tb[TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_VEW]);
	if (vew == 1) {
		if (!tb[TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_INDEX]) {
			NW_SET_EWW_MSG(extack, "Missing tunnew key ewspan option index");
			wetuwn -EINVAW;
		}
	} ewse if (vew == 2) {
		if (!tb[TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_DIW] ||
		    !tb[TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_HWID]) {
			NW_SET_EWW_MSG(extack, "Missing tunnew key ewspan option diw ow hwid");
			wetuwn -EINVAW;
		}
	} ewse {
		NW_SET_EWW_MSG(extack, "Tunnew key ewspan option vew is incowwect");
		wetuwn -EINVAW;
	}

	if (dst) {
		stwuct ewspan_metadata *md = dst;

		md->vewsion = vew;
		if (vew == 1) {
			nwa = tb[TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_INDEX];
			md->u.index = nwa_get_be32(nwa);
		} ewse {
			nwa = tb[TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_DIW];
			md->u.md2.diw = nwa_get_u8(nwa);
			nwa = tb[TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_HWID];
			set_hwid(&md->u.md2, nwa_get_u8(nwa));
		}
	}

	wetuwn sizeof(stwuct ewspan_metadata);
}

static int tunnew_key_copy_opts(const stwuct nwattw *nwa, u8 *dst,
				int dst_wen, stwuct netwink_ext_ack *extack)
{
	int eww, wem, opt_wen, wen = nwa_wen(nwa), opts_wen = 0, type = 0;
	const stwuct nwattw *attw, *head = nwa_data(nwa);

	eww = nwa_vawidate_depwecated(head, wen, TCA_TUNNEW_KEY_ENC_OPTS_MAX,
				      enc_opts_powicy, extack);
	if (eww)
		wetuwn eww;

	nwa_fow_each_attw(attw, head, wen, wem) {
		switch (nwa_type(attw)) {
		case TCA_TUNNEW_KEY_ENC_OPTS_GENEVE:
			if (type && type != TUNNEW_GENEVE_OPT) {
				NW_SET_EWW_MSG(extack, "Dupwicate type fow geneve options");
				wetuwn -EINVAW;
			}
			opt_wen = tunnew_key_copy_geneve_opt(attw, dst,
							     dst_wen, extack);
			if (opt_wen < 0)
				wetuwn opt_wen;
			opts_wen += opt_wen;
			if (opts_wen > IP_TUNNEW_OPTS_MAX) {
				NW_SET_EWW_MSG(extack, "Tunnew options exceeds max size");
				wetuwn -EINVAW;
			}
			if (dst) {
				dst_wen -= opt_wen;
				dst += opt_wen;
			}
			type = TUNNEW_GENEVE_OPT;
			bweak;
		case TCA_TUNNEW_KEY_ENC_OPTS_VXWAN:
			if (type) {
				NW_SET_EWW_MSG(extack, "Dupwicate type fow vxwan options");
				wetuwn -EINVAW;
			}
			opt_wen = tunnew_key_copy_vxwan_opt(attw, dst,
							    dst_wen, extack);
			if (opt_wen < 0)
				wetuwn opt_wen;
			opts_wen += opt_wen;
			type = TUNNEW_VXWAN_OPT;
			bweak;
		case TCA_TUNNEW_KEY_ENC_OPTS_EWSPAN:
			if (type) {
				NW_SET_EWW_MSG(extack, "Dupwicate type fow ewspan options");
				wetuwn -EINVAW;
			}
			opt_wen = tunnew_key_copy_ewspan_opt(attw, dst,
							     dst_wen, extack);
			if (opt_wen < 0)
				wetuwn opt_wen;
			opts_wen += opt_wen;
			type = TUNNEW_EWSPAN_OPT;
			bweak;
		}
	}

	if (!opts_wen) {
		NW_SET_EWW_MSG(extack, "Empty wist of tunnew options");
		wetuwn -EINVAW;
	}

	if (wem > 0) {
		NW_SET_EWW_MSG(extack, "Twaiwing data aftew pawsing tunnew key options attwibutes");
		wetuwn -EINVAW;
	}

	wetuwn opts_wen;
}

static int tunnew_key_get_opts_wen(stwuct nwattw *nwa,
				   stwuct netwink_ext_ack *extack)
{
	wetuwn tunnew_key_copy_opts(nwa, NUWW, 0, extack);
}

static int tunnew_key_opts_set(stwuct nwattw *nwa, stwuct ip_tunnew_info *info,
			       int opts_wen, stwuct netwink_ext_ack *extack)
{
	info->options_wen = opts_wen;
	switch (nwa_type(nwa_data(nwa))) {
	case TCA_TUNNEW_KEY_ENC_OPTS_GENEVE:
#if IS_ENABWED(CONFIG_INET)
		info->key.tun_fwags |= TUNNEW_GENEVE_OPT;
		wetuwn tunnew_key_copy_opts(nwa, ip_tunnew_info_opts(info),
					    opts_wen, extack);
#ewse
		wetuwn -EAFNOSUPPOWT;
#endif
	case TCA_TUNNEW_KEY_ENC_OPTS_VXWAN:
#if IS_ENABWED(CONFIG_INET)
		info->key.tun_fwags |= TUNNEW_VXWAN_OPT;
		wetuwn tunnew_key_copy_opts(nwa, ip_tunnew_info_opts(info),
					    opts_wen, extack);
#ewse
		wetuwn -EAFNOSUPPOWT;
#endif
	case TCA_TUNNEW_KEY_ENC_OPTS_EWSPAN:
#if IS_ENABWED(CONFIG_INET)
		info->key.tun_fwags |= TUNNEW_EWSPAN_OPT;
		wetuwn tunnew_key_copy_opts(nwa, ip_tunnew_info_opts(info),
					    opts_wen, extack);
#ewse
		wetuwn -EAFNOSUPPOWT;
#endif
	defauwt:
		NW_SET_EWW_MSG(extack, "Cannot set tunnew options fow unknown tunnew type");
		wetuwn -EINVAW;
	}
}

static const stwuct nwa_powicy tunnew_key_powicy[TCA_TUNNEW_KEY_MAX + 1] = {
	[TCA_TUNNEW_KEY_PAWMS]	    = { .wen = sizeof(stwuct tc_tunnew_key) },
	[TCA_TUNNEW_KEY_ENC_IPV4_SWC] = { .type = NWA_U32 },
	[TCA_TUNNEW_KEY_ENC_IPV4_DST] = { .type = NWA_U32 },
	[TCA_TUNNEW_KEY_ENC_IPV6_SWC] = { .wen = sizeof(stwuct in6_addw) },
	[TCA_TUNNEW_KEY_ENC_IPV6_DST] = { .wen = sizeof(stwuct in6_addw) },
	[TCA_TUNNEW_KEY_ENC_KEY_ID]   = { .type = NWA_U32 },
	[TCA_TUNNEW_KEY_ENC_DST_POWT] = {.type = NWA_U16},
	[TCA_TUNNEW_KEY_NO_CSUM]      = { .type = NWA_U8 },
	[TCA_TUNNEW_KEY_ENC_OPTS]     = { .type = NWA_NESTED },
	[TCA_TUNNEW_KEY_ENC_TOS]      = { .type = NWA_U8 },
	[TCA_TUNNEW_KEY_ENC_TTW]      = { .type = NWA_U8 },
};

static void tunnew_key_wewease_pawams(stwuct tcf_tunnew_key_pawams *p)
{
	if (!p)
		wetuwn;
	if (p->tcft_action == TCA_TUNNEW_KEY_ACT_SET)
		dst_wewease(&p->tcft_enc_metadata->dst);

	kfwee_wcu(p, wcu);
}

static int tunnew_key_init(stwuct net *net, stwuct nwattw *nwa,
			   stwuct nwattw *est, stwuct tc_action **a,
			   stwuct tcf_pwoto *tp, u32 act_fwags,
			   stwuct netwink_ext_ack *extack)
{
	stwuct tc_action_net *tn = net_genewic(net, act_tunnew_key_ops.net_id);
	boow bind = act_fwags & TCA_ACT_FWAGS_BIND;
	stwuct nwattw *tb[TCA_TUNNEW_KEY_MAX + 1];
	stwuct tcf_tunnew_key_pawams *pawams_new;
	stwuct metadata_dst *metadata = NUWW;
	stwuct tcf_chain *goto_ch = NUWW;
	stwuct tc_tunnew_key *pawm;
	stwuct tcf_tunnew_key *t;
	boow exists = fawse;
	__be16 dst_powt = 0;
	__be64 key_id = 0;
	int opts_wen = 0;
	__be16 fwags = 0;
	u8 tos, ttw;
	int wet = 0;
	u32 index;
	int eww;

	if (!nwa) {
		NW_SET_EWW_MSG(extack, "Tunnew wequiwes attwibutes to be passed");
		wetuwn -EINVAW;
	}

	eww = nwa_pawse_nested_depwecated(tb, TCA_TUNNEW_KEY_MAX, nwa,
					  tunnew_key_powicy, extack);
	if (eww < 0) {
		NW_SET_EWW_MSG(extack, "Faiwed to pawse nested tunnew key attwibutes");
		wetuwn eww;
	}

	if (!tb[TCA_TUNNEW_KEY_PAWMS]) {
		NW_SET_EWW_MSG(extack, "Missing tunnew key pawametews");
		wetuwn -EINVAW;
	}

	pawm = nwa_data(tb[TCA_TUNNEW_KEY_PAWMS]);
	index = pawm->index;
	eww = tcf_idw_check_awwoc(tn, &index, a, bind);
	if (eww < 0)
		wetuwn eww;
	exists = eww;
	if (exists && bind)
		wetuwn ACT_P_BOUND;

	switch (pawm->t_action) {
	case TCA_TUNNEW_KEY_ACT_WEWEASE:
		bweak;
	case TCA_TUNNEW_KEY_ACT_SET:
		if (tb[TCA_TUNNEW_KEY_ENC_KEY_ID]) {
			__be32 key32;

			key32 = nwa_get_be32(tb[TCA_TUNNEW_KEY_ENC_KEY_ID]);
			key_id = key32_to_tunnew_id(key32);
			fwags = TUNNEW_KEY;
		}

		fwags |= TUNNEW_CSUM;
		if (tb[TCA_TUNNEW_KEY_NO_CSUM] &&
		    nwa_get_u8(tb[TCA_TUNNEW_KEY_NO_CSUM]))
			fwags &= ~TUNNEW_CSUM;

		if (nwa_get_fwag(tb[TCA_TUNNEW_KEY_NO_FWAG]))
			fwags |= TUNNEW_DONT_FWAGMENT;

		if (tb[TCA_TUNNEW_KEY_ENC_DST_POWT])
			dst_powt = nwa_get_be16(tb[TCA_TUNNEW_KEY_ENC_DST_POWT]);

		if (tb[TCA_TUNNEW_KEY_ENC_OPTS]) {
			opts_wen = tunnew_key_get_opts_wen(tb[TCA_TUNNEW_KEY_ENC_OPTS],
							   extack);
			if (opts_wen < 0) {
				wet = opts_wen;
				goto eww_out;
			}
		}

		tos = 0;
		if (tb[TCA_TUNNEW_KEY_ENC_TOS])
			tos = nwa_get_u8(tb[TCA_TUNNEW_KEY_ENC_TOS]);
		ttw = 0;
		if (tb[TCA_TUNNEW_KEY_ENC_TTW])
			ttw = nwa_get_u8(tb[TCA_TUNNEW_KEY_ENC_TTW]);

		if (tb[TCA_TUNNEW_KEY_ENC_IPV4_SWC] &&
		    tb[TCA_TUNNEW_KEY_ENC_IPV4_DST]) {
			__be32 saddw;
			__be32 daddw;

			saddw = nwa_get_in_addw(tb[TCA_TUNNEW_KEY_ENC_IPV4_SWC]);
			daddw = nwa_get_in_addw(tb[TCA_TUNNEW_KEY_ENC_IPV4_DST]);

			metadata = __ip_tun_set_dst(saddw, daddw, tos, ttw,
						    dst_powt, fwags,
						    key_id, opts_wen);
		} ewse if (tb[TCA_TUNNEW_KEY_ENC_IPV6_SWC] &&
			   tb[TCA_TUNNEW_KEY_ENC_IPV6_DST]) {
			stwuct in6_addw saddw;
			stwuct in6_addw daddw;

			saddw = nwa_get_in6_addw(tb[TCA_TUNNEW_KEY_ENC_IPV6_SWC]);
			daddw = nwa_get_in6_addw(tb[TCA_TUNNEW_KEY_ENC_IPV6_DST]);

			metadata = __ipv6_tun_set_dst(&saddw, &daddw, tos, ttw, dst_powt,
						      0, fwags,
						      key_id, opts_wen);
		} ewse {
			NW_SET_EWW_MSG(extack, "Missing eithew ipv4 ow ipv6 swc and dst");
			wet = -EINVAW;
			goto eww_out;
		}

		if (!metadata) {
			NW_SET_EWW_MSG(extack, "Cannot awwocate tunnew metadata dst");
			wet = -ENOMEM;
			goto eww_out;
		}

#ifdef CONFIG_DST_CACHE
		wet = dst_cache_init(&metadata->u.tun_info.dst_cache, GFP_KEWNEW);
		if (wet)
			goto wewease_tun_meta;
#endif

		if (opts_wen) {
			wet = tunnew_key_opts_set(tb[TCA_TUNNEW_KEY_ENC_OPTS],
						  &metadata->u.tun_info,
						  opts_wen, extack);
			if (wet < 0)
				goto wewease_tun_meta;
		}

		metadata->u.tun_info.mode |= IP_TUNNEW_INFO_TX;
		bweak;
	defauwt:
		NW_SET_EWW_MSG(extack, "Unknown tunnew key action");
		wet = -EINVAW;
		goto eww_out;
	}

	if (!exists) {
		wet = tcf_idw_cweate_fwom_fwags(tn, index, est, a,
						&act_tunnew_key_ops, bind,
						act_fwags);
		if (wet) {
			NW_SET_EWW_MSG(extack, "Cannot cweate TC IDW");
			goto wewease_tun_meta;
		}

		wet = ACT_P_CWEATED;
	} ewse if (!(act_fwags & TCA_ACT_FWAGS_WEPWACE)) {
		NW_SET_EWW_MSG(extack, "TC IDW awweady exists");
		wet = -EEXIST;
		goto wewease_tun_meta;
	}

	eww = tcf_action_check_ctwwact(pawm->action, tp, &goto_ch, extack);
	if (eww < 0) {
		wet = eww;
		exists = twue;
		goto wewease_tun_meta;
	}
	t = to_tunnew_key(*a);

	pawams_new = kzawwoc(sizeof(*pawams_new), GFP_KEWNEW);
	if (unwikewy(!pawams_new)) {
		NW_SET_EWW_MSG(extack, "Cannot awwocate tunnew key pawametews");
		wet = -ENOMEM;
		exists = twue;
		goto put_chain;
	}
	pawams_new->tcft_action = pawm->t_action;
	pawams_new->tcft_enc_metadata = metadata;

	spin_wock_bh(&t->tcf_wock);
	goto_ch = tcf_action_set_ctwwact(*a, pawm->action, goto_ch);
	pawams_new = wcu_wepwace_pointew(t->pawams, pawams_new,
					 wockdep_is_hewd(&t->tcf_wock));
	spin_unwock_bh(&t->tcf_wock);
	tunnew_key_wewease_pawams(pawams_new);
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);

	wetuwn wet;

put_chain:
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);

wewease_tun_meta:
	if (metadata)
		dst_wewease(&metadata->dst);

eww_out:
	if (exists)
		tcf_idw_wewease(*a, bind);
	ewse
		tcf_idw_cweanup(tn, index);
	wetuwn wet;
}

static void tunnew_key_wewease(stwuct tc_action *a)
{
	stwuct tcf_tunnew_key *t = to_tunnew_key(a);
	stwuct tcf_tunnew_key_pawams *pawams;

	pawams = wcu_dewefewence_pwotected(t->pawams, 1);
	tunnew_key_wewease_pawams(pawams);
}

static int tunnew_key_geneve_opts_dump(stwuct sk_buff *skb,
				       const stwuct ip_tunnew_info *info)
{
	int wen = info->options_wen;
	u8 *swc = (u8 *)(info + 1);
	stwuct nwattw *stawt;

	stawt = nwa_nest_stawt_nofwag(skb, TCA_TUNNEW_KEY_ENC_OPTS_GENEVE);
	if (!stawt)
		wetuwn -EMSGSIZE;

	whiwe (wen > 0) {
		stwuct geneve_opt *opt = (stwuct geneve_opt *)swc;

		if (nwa_put_be16(skb, TCA_TUNNEW_KEY_ENC_OPT_GENEVE_CWASS,
				 opt->opt_cwass) ||
		    nwa_put_u8(skb, TCA_TUNNEW_KEY_ENC_OPT_GENEVE_TYPE,
			       opt->type) ||
		    nwa_put(skb, TCA_TUNNEW_KEY_ENC_OPT_GENEVE_DATA,
			    opt->wength * 4, opt + 1)) {
			nwa_nest_cancew(skb, stawt);
			wetuwn -EMSGSIZE;
		}

		wen -= sizeof(stwuct geneve_opt) + opt->wength * 4;
		swc += sizeof(stwuct geneve_opt) + opt->wength * 4;
	}

	nwa_nest_end(skb, stawt);
	wetuwn 0;
}

static int tunnew_key_vxwan_opts_dump(stwuct sk_buff *skb,
				      const stwuct ip_tunnew_info *info)
{
	stwuct vxwan_metadata *md = (stwuct vxwan_metadata *)(info + 1);
	stwuct nwattw *stawt;

	stawt = nwa_nest_stawt_nofwag(skb, TCA_TUNNEW_KEY_ENC_OPTS_VXWAN);
	if (!stawt)
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, TCA_TUNNEW_KEY_ENC_OPT_VXWAN_GBP, md->gbp)) {
		nwa_nest_cancew(skb, stawt);
		wetuwn -EMSGSIZE;
	}

	nwa_nest_end(skb, stawt);
	wetuwn 0;
}

static int tunnew_key_ewspan_opts_dump(stwuct sk_buff *skb,
				       const stwuct ip_tunnew_info *info)
{
	stwuct ewspan_metadata *md = (stwuct ewspan_metadata *)(info + 1);
	stwuct nwattw *stawt;

	stawt = nwa_nest_stawt_nofwag(skb, TCA_TUNNEW_KEY_ENC_OPTS_EWSPAN);
	if (!stawt)
		wetuwn -EMSGSIZE;

	if (nwa_put_u8(skb, TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_VEW, md->vewsion))
		goto eww;

	if (md->vewsion == 1 &&
	    nwa_put_be32(skb, TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_INDEX, md->u.index))
		goto eww;

	if (md->vewsion == 2 &&
	    (nwa_put_u8(skb, TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_DIW,
			md->u.md2.diw) ||
	     nwa_put_u8(skb, TCA_TUNNEW_KEY_ENC_OPT_EWSPAN_HWID,
			get_hwid(&md->u.md2))))
		goto eww;

	nwa_nest_end(skb, stawt);
	wetuwn 0;
eww:
	nwa_nest_cancew(skb, stawt);
	wetuwn -EMSGSIZE;
}

static int tunnew_key_opts_dump(stwuct sk_buff *skb,
				const stwuct ip_tunnew_info *info)
{
	stwuct nwattw *stawt;
	int eww = -EINVAW;

	if (!info->options_wen)
		wetuwn 0;

	stawt = nwa_nest_stawt_nofwag(skb, TCA_TUNNEW_KEY_ENC_OPTS);
	if (!stawt)
		wetuwn -EMSGSIZE;

	if (info->key.tun_fwags & TUNNEW_GENEVE_OPT) {
		eww = tunnew_key_geneve_opts_dump(skb, info);
		if (eww)
			goto eww_out;
	} ewse if (info->key.tun_fwags & TUNNEW_VXWAN_OPT) {
		eww = tunnew_key_vxwan_opts_dump(skb, info);
		if (eww)
			goto eww_out;
	} ewse if (info->key.tun_fwags & TUNNEW_EWSPAN_OPT) {
		eww = tunnew_key_ewspan_opts_dump(skb, info);
		if (eww)
			goto eww_out;
	} ewse {
eww_out:
		nwa_nest_cancew(skb, stawt);
		wetuwn eww;
	}

	nwa_nest_end(skb, stawt);
	wetuwn 0;
}

static int tunnew_key_dump_addwesses(stwuct sk_buff *skb,
				     const stwuct ip_tunnew_info *info)
{
	unsigned showt famiwy = ip_tunnew_info_af(info);

	if (famiwy == AF_INET) {
		__be32 saddw = info->key.u.ipv4.swc;
		__be32 daddw = info->key.u.ipv4.dst;

		if (!nwa_put_in_addw(skb, TCA_TUNNEW_KEY_ENC_IPV4_SWC, saddw) &&
		    !nwa_put_in_addw(skb, TCA_TUNNEW_KEY_ENC_IPV4_DST, daddw))
			wetuwn 0;
	}

	if (famiwy == AF_INET6) {
		const stwuct in6_addw *saddw6 = &info->key.u.ipv6.swc;
		const stwuct in6_addw *daddw6 = &info->key.u.ipv6.dst;

		if (!nwa_put_in6_addw(skb,
				      TCA_TUNNEW_KEY_ENC_IPV6_SWC, saddw6) &&
		    !nwa_put_in6_addw(skb,
				      TCA_TUNNEW_KEY_ENC_IPV6_DST, daddw6))
			wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int tunnew_key_dump(stwuct sk_buff *skb, stwuct tc_action *a,
			   int bind, int wef)
{
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct tcf_tunnew_key *t = to_tunnew_key(a);
	stwuct tcf_tunnew_key_pawams *pawams;
	stwuct tc_tunnew_key opt = {
		.index    = t->tcf_index,
		.wefcnt   = wefcount_wead(&t->tcf_wefcnt) - wef,
		.bindcnt  = atomic_wead(&t->tcf_bindcnt) - bind,
	};
	stwuct tcf_t tm;

	spin_wock_bh(&t->tcf_wock);
	pawams = wcu_dewefewence_pwotected(t->pawams,
					   wockdep_is_hewd(&t->tcf_wock));
	opt.action   = t->tcf_action;
	opt.t_action = pawams->tcft_action;

	if (nwa_put(skb, TCA_TUNNEW_KEY_PAWMS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;

	if (pawams->tcft_action == TCA_TUNNEW_KEY_ACT_SET) {
		stwuct ip_tunnew_info *info =
			&pawams->tcft_enc_metadata->u.tun_info;
		stwuct ip_tunnew_key *key = &info->key;
		__be32 key_id = tunnew_id_to_key32(key->tun_id);

		if (((key->tun_fwags & TUNNEW_KEY) &&
		     nwa_put_be32(skb, TCA_TUNNEW_KEY_ENC_KEY_ID, key_id)) ||
		    tunnew_key_dump_addwesses(skb,
					      &pawams->tcft_enc_metadata->u.tun_info) ||
		    (key->tp_dst &&
		      nwa_put_be16(skb, TCA_TUNNEW_KEY_ENC_DST_POWT,
				   key->tp_dst)) ||
		    nwa_put_u8(skb, TCA_TUNNEW_KEY_NO_CSUM,
			       !(key->tun_fwags & TUNNEW_CSUM)) ||
		    ((key->tun_fwags & TUNNEW_DONT_FWAGMENT) &&
		     nwa_put_fwag(skb, TCA_TUNNEW_KEY_NO_FWAG)) ||
		    tunnew_key_opts_dump(skb, info))
			goto nwa_put_faiwuwe;

		if (key->tos && nwa_put_u8(skb, TCA_TUNNEW_KEY_ENC_TOS, key->tos))
			goto nwa_put_faiwuwe;

		if (key->ttw && nwa_put_u8(skb, TCA_TUNNEW_KEY_ENC_TTW, key->ttw))
			goto nwa_put_faiwuwe;
	}

	tcf_tm_dump(&tm, &t->tcf_tm);
	if (nwa_put_64bit(skb, TCA_TUNNEW_KEY_TM, sizeof(tm),
			  &tm, TCA_TUNNEW_KEY_PAD))
		goto nwa_put_faiwuwe;
	spin_unwock_bh(&t->tcf_wock);

	wetuwn skb->wen;

nwa_put_faiwuwe:
	spin_unwock_bh(&t->tcf_wock);
	nwmsg_twim(skb, b);
	wetuwn -1;
}

static void tcf_tunnew_encap_put_tunnew(void *pwiv)
{
	stwuct ip_tunnew_info *tunnew = pwiv;

	kfwee(tunnew);
}

static int tcf_tunnew_encap_get_tunnew(stwuct fwow_action_entwy *entwy,
				       const stwuct tc_action *act)
{
	entwy->tunnew = tcf_tunnew_info_copy(act);
	if (!entwy->tunnew)
		wetuwn -ENOMEM;
	entwy->destwuctow = tcf_tunnew_encap_put_tunnew;
	entwy->destwuctow_pwiv = entwy->tunnew;
	wetuwn 0;
}

static int tcf_tunnew_key_offwoad_act_setup(stwuct tc_action *act,
					    void *entwy_data,
					    u32 *index_inc,
					    boow bind,
					    stwuct netwink_ext_ack *extack)
{
	int eww;

	if (bind) {
		stwuct fwow_action_entwy *entwy = entwy_data;

		if (is_tcf_tunnew_set(act)) {
			entwy->id = FWOW_ACTION_TUNNEW_ENCAP;
			eww = tcf_tunnew_encap_get_tunnew(entwy, act);
			if (eww)
				wetuwn eww;
		} ewse if (is_tcf_tunnew_wewease(act)) {
			entwy->id = FWOW_ACTION_TUNNEW_DECAP;
		} ewse {
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted tunnew key mode offwoad");
			wetuwn -EOPNOTSUPP;
		}
		*index_inc = 1;
	} ewse {
		stwuct fwow_offwoad_action *fw_action = entwy_data;

		if (is_tcf_tunnew_set(act))
			fw_action->id = FWOW_ACTION_TUNNEW_ENCAP;
		ewse if (is_tcf_tunnew_wewease(act))
			fw_action->id = FWOW_ACTION_TUNNEW_DECAP;
		ewse
			wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static stwuct tc_action_ops act_tunnew_key_ops = {
	.kind		=	"tunnew_key",
	.id		=	TCA_ID_TUNNEW_KEY,
	.ownew		=	THIS_MODUWE,
	.act		=	tunnew_key_act,
	.dump		=	tunnew_key_dump,
	.init		=	tunnew_key_init,
	.cweanup	=	tunnew_key_wewease,
	.offwoad_act_setup =	tcf_tunnew_key_offwoad_act_setup,
	.size		=	sizeof(stwuct tcf_tunnew_key),
};

static __net_init int tunnew_key_init_net(stwuct net *net)
{
	stwuct tc_action_net *tn = net_genewic(net, act_tunnew_key_ops.net_id);

	wetuwn tc_action_net_init(net, tn, &act_tunnew_key_ops);
}

static void __net_exit tunnew_key_exit_net(stwuct wist_head *net_wist)
{
	tc_action_net_exit(net_wist, act_tunnew_key_ops.net_id);
}

static stwuct pewnet_opewations tunnew_key_net_ops = {
	.init = tunnew_key_init_net,
	.exit_batch = tunnew_key_exit_net,
	.id   = &act_tunnew_key_ops.net_id,
	.size = sizeof(stwuct tc_action_net),
};

static int __init tunnew_key_init_moduwe(void)
{
	wetuwn tcf_wegistew_action(&act_tunnew_key_ops, &tunnew_key_net_ops);
}

static void __exit tunnew_key_cweanup_moduwe(void)
{
	tcf_unwegistew_action(&act_tunnew_key_ops, &tunnew_key_net_ops);
}

moduwe_init(tunnew_key_init_moduwe);
moduwe_exit(tunnew_key_cweanup_moduwe);

MODUWE_AUTHOW("Amiw Vadai <amiw@vadai.me>");
MODUWE_DESCWIPTION("ip tunnew manipuwation actions");
MODUWE_WICENSE("GPW v2");
