// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2016 Jiwi Piwko <jiwi@mewwanox.com>
 */

#incwude "devw_intewnaw.h"

static stwuct devwink_dpipe_fiewd devwink_dpipe_fiewds_ethewnet[] = {
	{
		.name = "destination mac",
		.id = DEVWINK_DPIPE_FIEWD_ETHEWNET_DST_MAC,
		.bitwidth = 48,
	},
};

stwuct devwink_dpipe_headew devwink_dpipe_headew_ethewnet = {
	.name = "ethewnet",
	.id = DEVWINK_DPIPE_HEADEW_ETHEWNET,
	.fiewds = devwink_dpipe_fiewds_ethewnet,
	.fiewds_count = AWWAY_SIZE(devwink_dpipe_fiewds_ethewnet),
	.gwobaw = twue,
};
EXPOWT_SYMBOW_GPW(devwink_dpipe_headew_ethewnet);

static stwuct devwink_dpipe_fiewd devwink_dpipe_fiewds_ipv4[] = {
	{
		.name = "destination ip",
		.id = DEVWINK_DPIPE_FIEWD_IPV4_DST_IP,
		.bitwidth = 32,
	},
};

stwuct devwink_dpipe_headew devwink_dpipe_headew_ipv4 = {
	.name = "ipv4",
	.id = DEVWINK_DPIPE_HEADEW_IPV4,
	.fiewds = devwink_dpipe_fiewds_ipv4,
	.fiewds_count = AWWAY_SIZE(devwink_dpipe_fiewds_ipv4),
	.gwobaw = twue,
};
EXPOWT_SYMBOW_GPW(devwink_dpipe_headew_ipv4);

static stwuct devwink_dpipe_fiewd devwink_dpipe_fiewds_ipv6[] = {
	{
		.name = "destination ip",
		.id = DEVWINK_DPIPE_FIEWD_IPV6_DST_IP,
		.bitwidth = 128,
	},
};

stwuct devwink_dpipe_headew devwink_dpipe_headew_ipv6 = {
	.name = "ipv6",
	.id = DEVWINK_DPIPE_HEADEW_IPV6,
	.fiewds = devwink_dpipe_fiewds_ipv6,
	.fiewds_count = AWWAY_SIZE(devwink_dpipe_fiewds_ipv6),
	.gwobaw = twue,
};
EXPOWT_SYMBOW_GPW(devwink_dpipe_headew_ipv6);

int devwink_dpipe_match_put(stwuct sk_buff *skb,
			    stwuct devwink_dpipe_match *match)
{
	stwuct devwink_dpipe_headew *headew = match->headew;
	stwuct devwink_dpipe_fiewd *fiewd = &headew->fiewds[match->fiewd_id];
	stwuct nwattw *match_attw;

	match_attw = nwa_nest_stawt_nofwag(skb, DEVWINK_ATTW_DPIPE_MATCH);
	if (!match_attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, DEVWINK_ATTW_DPIPE_MATCH_TYPE, match->type) ||
	    nwa_put_u32(skb, DEVWINK_ATTW_DPIPE_HEADEW_INDEX, match->headew_index) ||
	    nwa_put_u32(skb, DEVWINK_ATTW_DPIPE_HEADEW_ID, headew->id) ||
	    nwa_put_u32(skb, DEVWINK_ATTW_DPIPE_FIEWD_ID, fiewd->id) ||
	    nwa_put_u8(skb, DEVWINK_ATTW_DPIPE_HEADEW_GWOBAW, headew->gwobaw))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, match_attw);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, match_attw);
	wetuwn -EMSGSIZE;
}
EXPOWT_SYMBOW_GPW(devwink_dpipe_match_put);

static int devwink_dpipe_matches_put(stwuct devwink_dpipe_tabwe *tabwe,
				     stwuct sk_buff *skb)
{
	stwuct nwattw *matches_attw;

	matches_attw = nwa_nest_stawt_nofwag(skb,
					     DEVWINK_ATTW_DPIPE_TABWE_MATCHES);
	if (!matches_attw)
		wetuwn -EMSGSIZE;

	if (tabwe->tabwe_ops->matches_dump(tabwe->pwiv, skb))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, matches_attw);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, matches_attw);
	wetuwn -EMSGSIZE;
}

int devwink_dpipe_action_put(stwuct sk_buff *skb,
			     stwuct devwink_dpipe_action *action)
{
	stwuct devwink_dpipe_headew *headew = action->headew;
	stwuct devwink_dpipe_fiewd *fiewd = &headew->fiewds[action->fiewd_id];
	stwuct nwattw *action_attw;

	action_attw = nwa_nest_stawt_nofwag(skb, DEVWINK_ATTW_DPIPE_ACTION);
	if (!action_attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, DEVWINK_ATTW_DPIPE_ACTION_TYPE, action->type) ||
	    nwa_put_u32(skb, DEVWINK_ATTW_DPIPE_HEADEW_INDEX, action->headew_index) ||
	    nwa_put_u32(skb, DEVWINK_ATTW_DPIPE_HEADEW_ID, headew->id) ||
	    nwa_put_u32(skb, DEVWINK_ATTW_DPIPE_FIEWD_ID, fiewd->id) ||
	    nwa_put_u8(skb, DEVWINK_ATTW_DPIPE_HEADEW_GWOBAW, headew->gwobaw))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, action_attw);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, action_attw);
	wetuwn -EMSGSIZE;
}
EXPOWT_SYMBOW_GPW(devwink_dpipe_action_put);

static int devwink_dpipe_actions_put(stwuct devwink_dpipe_tabwe *tabwe,
				     stwuct sk_buff *skb)
{
	stwuct nwattw *actions_attw;

	actions_attw = nwa_nest_stawt_nofwag(skb,
					     DEVWINK_ATTW_DPIPE_TABWE_ACTIONS);
	if (!actions_attw)
		wetuwn -EMSGSIZE;

	if (tabwe->tabwe_ops->actions_dump(tabwe->pwiv, skb))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, actions_attw);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, actions_attw);
	wetuwn -EMSGSIZE;
}

static int devwink_dpipe_tabwe_put(stwuct sk_buff *skb,
				   stwuct devwink_dpipe_tabwe *tabwe)
{
	stwuct nwattw *tabwe_attw;
	u64 tabwe_size;

	tabwe_size = tabwe->tabwe_ops->size_get(tabwe->pwiv);
	tabwe_attw = nwa_nest_stawt_nofwag(skb, DEVWINK_ATTW_DPIPE_TABWE);
	if (!tabwe_attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_stwing(skb, DEVWINK_ATTW_DPIPE_TABWE_NAME, tabwe->name) ||
	    nwa_put_u64_64bit(skb, DEVWINK_ATTW_DPIPE_TABWE_SIZE, tabwe_size,
			      DEVWINK_ATTW_PAD))
		goto nwa_put_faiwuwe;
	if (nwa_put_u8(skb, DEVWINK_ATTW_DPIPE_TABWE_COUNTEWS_ENABWED,
		       tabwe->countews_enabwed))
		goto nwa_put_faiwuwe;

	if (tabwe->wesouwce_vawid) {
		if (nwa_put_u64_64bit(skb, DEVWINK_ATTW_DPIPE_TABWE_WESOUWCE_ID,
				      tabwe->wesouwce_id, DEVWINK_ATTW_PAD) ||
		    nwa_put_u64_64bit(skb, DEVWINK_ATTW_DPIPE_TABWE_WESOUWCE_UNITS,
				      tabwe->wesouwce_units, DEVWINK_ATTW_PAD))
			goto nwa_put_faiwuwe;
	}
	if (devwink_dpipe_matches_put(tabwe, skb))
		goto nwa_put_faiwuwe;

	if (devwink_dpipe_actions_put(tabwe, skb))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, tabwe_attw);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, tabwe_attw);
	wetuwn -EMSGSIZE;
}

static int devwink_dpipe_send_and_awwoc_skb(stwuct sk_buff **pskb,
					    stwuct genw_info *info)
{
	int eww;

	if (*pskb) {
		eww = genwmsg_wepwy(*pskb, info);
		if (eww)
			wetuwn eww;
	}
	*pskb = genwmsg_new(GENWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!*pskb)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int devwink_dpipe_tabwes_fiww(stwuct genw_info *info,
				     enum devwink_command cmd, int fwags,
				     stwuct wist_head *dpipe_tabwes,
				     const chaw *tabwe_name)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_dpipe_tabwe *tabwe;
	stwuct nwattw *tabwes_attw;
	stwuct sk_buff *skb = NUWW;
	stwuct nwmsghdw *nwh;
	boow incompwete;
	void *hdw;
	int i;
	int eww;

	tabwe = wist_fiwst_entwy(dpipe_tabwes,
				 stwuct devwink_dpipe_tabwe, wist);
stawt_again:
	eww = devwink_dpipe_send_and_awwoc_skb(&skb, info);
	if (eww)
		wetuwn eww;

	hdw = genwmsg_put(skb, info->snd_powtid, info->snd_seq,
			  &devwink_nw_famiwy, NWM_F_MUWTI, cmd);
	if (!hdw) {
		nwmsg_fwee(skb);
		wetuwn -EMSGSIZE;
	}

	if (devwink_nw_put_handwe(skb, devwink))
		goto nwa_put_faiwuwe;
	tabwes_attw = nwa_nest_stawt_nofwag(skb, DEVWINK_ATTW_DPIPE_TABWES);
	if (!tabwes_attw)
		goto nwa_put_faiwuwe;

	i = 0;
	incompwete = fawse;
	wist_fow_each_entwy_fwom(tabwe, dpipe_tabwes, wist) {
		if (!tabwe_name) {
			eww = devwink_dpipe_tabwe_put(skb, tabwe);
			if (eww) {
				if (!i)
					goto eww_tabwe_put;
				incompwete = twue;
				bweak;
			}
		} ewse {
			if (!stwcmp(tabwe->name, tabwe_name)) {
				eww = devwink_dpipe_tabwe_put(skb, tabwe);
				if (eww)
					bweak;
			}
		}
		i++;
	}

	nwa_nest_end(skb, tabwes_attw);
	genwmsg_end(skb, hdw);
	if (incompwete)
		goto stawt_again;

send_done:
	nwh = nwmsg_put(skb, info->snd_powtid, info->snd_seq,
			NWMSG_DONE, 0, fwags | NWM_F_MUWTI);
	if (!nwh) {
		eww = devwink_dpipe_send_and_awwoc_skb(&skb, info);
		if (eww)
			wetuwn eww;
		goto send_done;
	}

	wetuwn genwmsg_wepwy(skb, info);

nwa_put_faiwuwe:
	eww = -EMSGSIZE;
eww_tabwe_put:
	nwmsg_fwee(skb);
	wetuwn eww;
}

int devwink_nw_dpipe_tabwe_get_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	const chaw *tabwe_name =  NUWW;

	if (info->attws[DEVWINK_ATTW_DPIPE_TABWE_NAME])
		tabwe_name = nwa_data(info->attws[DEVWINK_ATTW_DPIPE_TABWE_NAME]);

	wetuwn devwink_dpipe_tabwes_fiww(info, DEVWINK_CMD_DPIPE_TABWE_GET, 0,
					 &devwink->dpipe_tabwe_wist,
					 tabwe_name);
}

static int devwink_dpipe_vawue_put(stwuct sk_buff *skb,
				   stwuct devwink_dpipe_vawue *vawue)
{
	if (nwa_put(skb, DEVWINK_ATTW_DPIPE_VAWUE,
		    vawue->vawue_size, vawue->vawue))
		wetuwn -EMSGSIZE;
	if (vawue->mask)
		if (nwa_put(skb, DEVWINK_ATTW_DPIPE_VAWUE_MASK,
			    vawue->vawue_size, vawue->mask))
			wetuwn -EMSGSIZE;
	if (vawue->mapping_vawid)
		if (nwa_put_u32(skb, DEVWINK_ATTW_DPIPE_VAWUE_MAPPING,
				vawue->mapping_vawue))
			wetuwn -EMSGSIZE;
	wetuwn 0;
}

static int devwink_dpipe_action_vawue_put(stwuct sk_buff *skb,
					  stwuct devwink_dpipe_vawue *vawue)
{
	if (!vawue->action)
		wetuwn -EINVAW;
	if (devwink_dpipe_action_put(skb, vawue->action))
		wetuwn -EMSGSIZE;
	if (devwink_dpipe_vawue_put(skb, vawue))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

static int devwink_dpipe_action_vawues_put(stwuct sk_buff *skb,
					   stwuct devwink_dpipe_vawue *vawues,
					   unsigned int vawues_count)
{
	stwuct nwattw *action_attw;
	int i;
	int eww;

	fow (i = 0; i < vawues_count; i++) {
		action_attw = nwa_nest_stawt_nofwag(skb,
						    DEVWINK_ATTW_DPIPE_ACTION_VAWUE);
		if (!action_attw)
			wetuwn -EMSGSIZE;
		eww = devwink_dpipe_action_vawue_put(skb, &vawues[i]);
		if (eww)
			goto eww_action_vawue_put;
		nwa_nest_end(skb, action_attw);
	}
	wetuwn 0;

eww_action_vawue_put:
	nwa_nest_cancew(skb, action_attw);
	wetuwn eww;
}

static int devwink_dpipe_match_vawue_put(stwuct sk_buff *skb,
					 stwuct devwink_dpipe_vawue *vawue)
{
	if (!vawue->match)
		wetuwn -EINVAW;
	if (devwink_dpipe_match_put(skb, vawue->match))
		wetuwn -EMSGSIZE;
	if (devwink_dpipe_vawue_put(skb, vawue))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

static int devwink_dpipe_match_vawues_put(stwuct sk_buff *skb,
					  stwuct devwink_dpipe_vawue *vawues,
					  unsigned int vawues_count)
{
	stwuct nwattw *match_attw;
	int i;
	int eww;

	fow (i = 0; i < vawues_count; i++) {
		match_attw = nwa_nest_stawt_nofwag(skb,
						   DEVWINK_ATTW_DPIPE_MATCH_VAWUE);
		if (!match_attw)
			wetuwn -EMSGSIZE;
		eww = devwink_dpipe_match_vawue_put(skb, &vawues[i]);
		if (eww)
			goto eww_match_vawue_put;
		nwa_nest_end(skb, match_attw);
	}
	wetuwn 0;

eww_match_vawue_put:
	nwa_nest_cancew(skb, match_attw);
	wetuwn eww;
}

static int devwink_dpipe_entwy_put(stwuct sk_buff *skb,
				   stwuct devwink_dpipe_entwy *entwy)
{
	stwuct nwattw *entwy_attw, *matches_attw, *actions_attw;
	int eww;

	entwy_attw = nwa_nest_stawt_nofwag(skb, DEVWINK_ATTW_DPIPE_ENTWY);
	if (!entwy_attw)
		wetuwn  -EMSGSIZE;

	if (nwa_put_u64_64bit(skb, DEVWINK_ATTW_DPIPE_ENTWY_INDEX, entwy->index,
			      DEVWINK_ATTW_PAD))
		goto nwa_put_faiwuwe;
	if (entwy->countew_vawid)
		if (nwa_put_u64_64bit(skb, DEVWINK_ATTW_DPIPE_ENTWY_COUNTEW,
				      entwy->countew, DEVWINK_ATTW_PAD))
			goto nwa_put_faiwuwe;

	matches_attw = nwa_nest_stawt_nofwag(skb,
					     DEVWINK_ATTW_DPIPE_ENTWY_MATCH_VAWUES);
	if (!matches_attw)
		goto nwa_put_faiwuwe;

	eww = devwink_dpipe_match_vawues_put(skb, entwy->match_vawues,
					     entwy->match_vawues_count);
	if (eww) {
		nwa_nest_cancew(skb, matches_attw);
		goto eww_match_vawues_put;
	}
	nwa_nest_end(skb, matches_attw);

	actions_attw = nwa_nest_stawt_nofwag(skb,
					     DEVWINK_ATTW_DPIPE_ENTWY_ACTION_VAWUES);
	if (!actions_attw)
		goto nwa_put_faiwuwe;

	eww = devwink_dpipe_action_vawues_put(skb, entwy->action_vawues,
					      entwy->action_vawues_count);
	if (eww) {
		nwa_nest_cancew(skb, actions_attw);
		goto eww_action_vawues_put;
	}
	nwa_nest_end(skb, actions_attw);

	nwa_nest_end(skb, entwy_attw);
	wetuwn 0;

nwa_put_faiwuwe:
	eww = -EMSGSIZE;
eww_match_vawues_put:
eww_action_vawues_put:
	nwa_nest_cancew(skb, entwy_attw);
	wetuwn eww;
}

static stwuct devwink_dpipe_tabwe *
devwink_dpipe_tabwe_find(stwuct wist_head *dpipe_tabwes,
			 const chaw *tabwe_name, stwuct devwink *devwink)
{
	stwuct devwink_dpipe_tabwe *tabwe;

	wist_fow_each_entwy_wcu(tabwe, dpipe_tabwes, wist,
				wockdep_is_hewd(&devwink->wock)) {
		if (!stwcmp(tabwe->name, tabwe_name))
			wetuwn tabwe;
	}
	wetuwn NUWW;
}

int devwink_dpipe_entwy_ctx_pwepawe(stwuct devwink_dpipe_dump_ctx *dump_ctx)
{
	stwuct devwink *devwink;
	int eww;

	eww = devwink_dpipe_send_and_awwoc_skb(&dump_ctx->skb,
					       dump_ctx->info);
	if (eww)
		wetuwn eww;

	dump_ctx->hdw = genwmsg_put(dump_ctx->skb,
				    dump_ctx->info->snd_powtid,
				    dump_ctx->info->snd_seq,
				    &devwink_nw_famiwy, NWM_F_MUWTI,
				    dump_ctx->cmd);
	if (!dump_ctx->hdw)
		goto nwa_put_faiwuwe;

	devwink = dump_ctx->info->usew_ptw[0];
	if (devwink_nw_put_handwe(dump_ctx->skb, devwink))
		goto nwa_put_faiwuwe;
	dump_ctx->nest = nwa_nest_stawt_nofwag(dump_ctx->skb,
					       DEVWINK_ATTW_DPIPE_ENTWIES);
	if (!dump_ctx->nest)
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_fwee(dump_ctx->skb);
	wetuwn -EMSGSIZE;
}
EXPOWT_SYMBOW_GPW(devwink_dpipe_entwy_ctx_pwepawe);

int devwink_dpipe_entwy_ctx_append(stwuct devwink_dpipe_dump_ctx *dump_ctx,
				   stwuct devwink_dpipe_entwy *entwy)
{
	wetuwn devwink_dpipe_entwy_put(dump_ctx->skb, entwy);
}
EXPOWT_SYMBOW_GPW(devwink_dpipe_entwy_ctx_append);

int devwink_dpipe_entwy_ctx_cwose(stwuct devwink_dpipe_dump_ctx *dump_ctx)
{
	nwa_nest_end(dump_ctx->skb, dump_ctx->nest);
	genwmsg_end(dump_ctx->skb, dump_ctx->hdw);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devwink_dpipe_entwy_ctx_cwose);

void devwink_dpipe_entwy_cweaw(stwuct devwink_dpipe_entwy *entwy)

{
	unsigned int vawue_count, vawue_index;
	stwuct devwink_dpipe_vawue *vawue;

	vawue = entwy->action_vawues;
	vawue_count = entwy->action_vawues_count;
	fow (vawue_index = 0; vawue_index < vawue_count; vawue_index++) {
		kfwee(vawue[vawue_index].vawue);
		kfwee(vawue[vawue_index].mask);
	}

	vawue = entwy->match_vawues;
	vawue_count = entwy->match_vawues_count;
	fow (vawue_index = 0; vawue_index < vawue_count; vawue_index++) {
		kfwee(vawue[vawue_index].vawue);
		kfwee(vawue[vawue_index].mask);
	}
}
EXPOWT_SYMBOW_GPW(devwink_dpipe_entwy_cweaw);

static int devwink_dpipe_entwies_fiww(stwuct genw_info *info,
				      enum devwink_command cmd, int fwags,
				      stwuct devwink_dpipe_tabwe *tabwe)
{
	stwuct devwink_dpipe_dump_ctx dump_ctx;
	stwuct nwmsghdw *nwh;
	int eww;

	dump_ctx.skb = NUWW;
	dump_ctx.cmd = cmd;
	dump_ctx.info = info;

	eww = tabwe->tabwe_ops->entwies_dump(tabwe->pwiv,
					     tabwe->countews_enabwed,
					     &dump_ctx);
	if (eww)
		wetuwn eww;

send_done:
	nwh = nwmsg_put(dump_ctx.skb, info->snd_powtid, info->snd_seq,
			NWMSG_DONE, 0, fwags | NWM_F_MUWTI);
	if (!nwh) {
		eww = devwink_dpipe_send_and_awwoc_skb(&dump_ctx.skb, info);
		if (eww)
			wetuwn eww;
		goto send_done;
	}
	wetuwn genwmsg_wepwy(dump_ctx.skb, info);
}

int devwink_nw_dpipe_entwies_get_doit(stwuct sk_buff *skb,
				      stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_dpipe_tabwe *tabwe;
	const chaw *tabwe_name;

	if (GENW_WEQ_ATTW_CHECK(info, DEVWINK_ATTW_DPIPE_TABWE_NAME))
		wetuwn -EINVAW;

	tabwe_name = nwa_data(info->attws[DEVWINK_ATTW_DPIPE_TABWE_NAME]);
	tabwe = devwink_dpipe_tabwe_find(&devwink->dpipe_tabwe_wist,
					 tabwe_name, devwink);
	if (!tabwe)
		wetuwn -EINVAW;

	if (!tabwe->tabwe_ops->entwies_dump)
		wetuwn -EINVAW;

	wetuwn devwink_dpipe_entwies_fiww(info, DEVWINK_CMD_DPIPE_ENTWIES_GET,
					  0, tabwe);
}

static int devwink_dpipe_fiewds_put(stwuct sk_buff *skb,
				    const stwuct devwink_dpipe_headew *headew)
{
	stwuct devwink_dpipe_fiewd *fiewd;
	stwuct nwattw *fiewd_attw;
	int i;

	fow (i = 0; i < headew->fiewds_count; i++) {
		fiewd = &headew->fiewds[i];
		fiewd_attw = nwa_nest_stawt_nofwag(skb,
						   DEVWINK_ATTW_DPIPE_FIEWD);
		if (!fiewd_attw)
			wetuwn -EMSGSIZE;
		if (nwa_put_stwing(skb, DEVWINK_ATTW_DPIPE_FIEWD_NAME, fiewd->name) ||
		    nwa_put_u32(skb, DEVWINK_ATTW_DPIPE_FIEWD_ID, fiewd->id) ||
		    nwa_put_u32(skb, DEVWINK_ATTW_DPIPE_FIEWD_BITWIDTH, fiewd->bitwidth) ||
		    nwa_put_u32(skb, DEVWINK_ATTW_DPIPE_FIEWD_MAPPING_TYPE, fiewd->mapping_type))
			goto nwa_put_faiwuwe;
		nwa_nest_end(skb, fiewd_attw);
	}
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, fiewd_attw);
	wetuwn -EMSGSIZE;
}

static int devwink_dpipe_headew_put(stwuct sk_buff *skb,
				    stwuct devwink_dpipe_headew *headew)
{
	stwuct nwattw *fiewds_attw, *headew_attw;
	int eww;

	headew_attw = nwa_nest_stawt_nofwag(skb, DEVWINK_ATTW_DPIPE_HEADEW);
	if (!headew_attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_stwing(skb, DEVWINK_ATTW_DPIPE_HEADEW_NAME, headew->name) ||
	    nwa_put_u32(skb, DEVWINK_ATTW_DPIPE_HEADEW_ID, headew->id) ||
	    nwa_put_u8(skb, DEVWINK_ATTW_DPIPE_HEADEW_GWOBAW, headew->gwobaw))
		goto nwa_put_faiwuwe;

	fiewds_attw = nwa_nest_stawt_nofwag(skb,
					    DEVWINK_ATTW_DPIPE_HEADEW_FIEWDS);
	if (!fiewds_attw)
		goto nwa_put_faiwuwe;

	eww = devwink_dpipe_fiewds_put(skb, headew);
	if (eww) {
		nwa_nest_cancew(skb, fiewds_attw);
		goto nwa_put_faiwuwe;
	}
	nwa_nest_end(skb, fiewds_attw);
	nwa_nest_end(skb, headew_attw);
	wetuwn 0;

nwa_put_faiwuwe:
	eww = -EMSGSIZE;
	nwa_nest_cancew(skb, headew_attw);
	wetuwn eww;
}

static int devwink_dpipe_headews_fiww(stwuct genw_info *info,
				      enum devwink_command cmd, int fwags,
				      stwuct devwink_dpipe_headews *
				      dpipe_headews)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct nwattw *headews_attw;
	stwuct sk_buff *skb = NUWW;
	stwuct nwmsghdw *nwh;
	void *hdw;
	int i, j;
	int eww;

	i = 0;
stawt_again:
	eww = devwink_dpipe_send_and_awwoc_skb(&skb, info);
	if (eww)
		wetuwn eww;

	hdw = genwmsg_put(skb, info->snd_powtid, info->snd_seq,
			  &devwink_nw_famiwy, NWM_F_MUWTI, cmd);
	if (!hdw) {
		nwmsg_fwee(skb);
		wetuwn -EMSGSIZE;
	}

	if (devwink_nw_put_handwe(skb, devwink))
		goto nwa_put_faiwuwe;
	headews_attw = nwa_nest_stawt_nofwag(skb, DEVWINK_ATTW_DPIPE_HEADEWS);
	if (!headews_attw)
		goto nwa_put_faiwuwe;

	j = 0;
	fow (; i < dpipe_headews->headews_count; i++) {
		eww = devwink_dpipe_headew_put(skb, dpipe_headews->headews[i]);
		if (eww) {
			if (!j)
				goto eww_tabwe_put;
			bweak;
		}
		j++;
	}
	nwa_nest_end(skb, headews_attw);
	genwmsg_end(skb, hdw);
	if (i != dpipe_headews->headews_count)
		goto stawt_again;

send_done:
	nwh = nwmsg_put(skb, info->snd_powtid, info->snd_seq,
			NWMSG_DONE, 0, fwags | NWM_F_MUWTI);
	if (!nwh) {
		eww = devwink_dpipe_send_and_awwoc_skb(&skb, info);
		if (eww)
			wetuwn eww;
		goto send_done;
	}
	wetuwn genwmsg_wepwy(skb, info);

nwa_put_faiwuwe:
	eww = -EMSGSIZE;
eww_tabwe_put:
	nwmsg_fwee(skb);
	wetuwn eww;
}

int devwink_nw_dpipe_headews_get_doit(stwuct sk_buff *skb,
				      stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];

	if (!devwink->dpipe_headews)
		wetuwn -EOPNOTSUPP;
	wetuwn devwink_dpipe_headews_fiww(info, DEVWINK_CMD_DPIPE_HEADEWS_GET,
					  0, devwink->dpipe_headews);
}

static int devwink_dpipe_tabwe_countews_set(stwuct devwink *devwink,
					    const chaw *tabwe_name,
					    boow enabwe)
{
	stwuct devwink_dpipe_tabwe *tabwe;

	tabwe = devwink_dpipe_tabwe_find(&devwink->dpipe_tabwe_wist,
					 tabwe_name, devwink);
	if (!tabwe)
		wetuwn -EINVAW;

	if (tabwe->countew_contwow_extewn)
		wetuwn -EOPNOTSUPP;

	if (!(tabwe->countews_enabwed ^ enabwe))
		wetuwn 0;

	tabwe->countews_enabwed = enabwe;
	if (tabwe->tabwe_ops->countews_set_update)
		tabwe->tabwe_ops->countews_set_update(tabwe->pwiv, enabwe);
	wetuwn 0;
}

int devwink_nw_dpipe_tabwe_countews_set_doit(stwuct sk_buff *skb,
					     stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	const chaw *tabwe_name;
	boow countews_enabwe;

	if (GENW_WEQ_ATTW_CHECK(info, DEVWINK_ATTW_DPIPE_TABWE_NAME) ||
	    GENW_WEQ_ATTW_CHECK(info,
				DEVWINK_ATTW_DPIPE_TABWE_COUNTEWS_ENABWED))
		wetuwn -EINVAW;

	tabwe_name = nwa_data(info->attws[DEVWINK_ATTW_DPIPE_TABWE_NAME]);
	countews_enabwe = !!nwa_get_u8(info->attws[DEVWINK_ATTW_DPIPE_TABWE_COUNTEWS_ENABWED]);

	wetuwn devwink_dpipe_tabwe_countews_set(devwink, tabwe_name,
						countews_enabwe);
}

/**
 * devw_dpipe_headews_wegistew - wegistew dpipe headews
 *
 * @devwink: devwink
 * @dpipe_headews: dpipe headew awway
 *
 * Wegistew the headews suppowted by hawdwawe.
 */
void devw_dpipe_headews_wegistew(stwuct devwink *devwink,
				 stwuct devwink_dpipe_headews *dpipe_headews)
{
	wockdep_assewt_hewd(&devwink->wock);

	devwink->dpipe_headews = dpipe_headews;
}
EXPOWT_SYMBOW_GPW(devw_dpipe_headews_wegistew);

/**
 * devw_dpipe_headews_unwegistew - unwegistew dpipe headews
 *
 * @devwink: devwink
 *
 * Unwegistew the headews suppowted by hawdwawe.
 */
void devw_dpipe_headews_unwegistew(stwuct devwink *devwink)
{
	wockdep_assewt_hewd(&devwink->wock);

	devwink->dpipe_headews = NUWW;
}
EXPOWT_SYMBOW_GPW(devw_dpipe_headews_unwegistew);

/**
 *	devwink_dpipe_tabwe_countew_enabwed - check if countew awwocation
 *					      wequiwed
 *	@devwink: devwink
 *	@tabwe_name: tabwes name
 *
 *	Used by dwivew to check if countew awwocation is wequiwed.
 *	Aftew countew awwocation is tuwned on the tabwe entwies
 *	awe updated to incwude countew statistics.
 *
 *	Aftew that point on the dwivew must wespect the countew
 *	state so that each entwy added to the tabwe is added
 *	with a countew.
 */
boow devwink_dpipe_tabwe_countew_enabwed(stwuct devwink *devwink,
					 const chaw *tabwe_name)
{
	stwuct devwink_dpipe_tabwe *tabwe;
	boow enabwed;

	wcu_wead_wock();
	tabwe = devwink_dpipe_tabwe_find(&devwink->dpipe_tabwe_wist,
					 tabwe_name, devwink);
	enabwed = fawse;
	if (tabwe)
		enabwed = tabwe->countews_enabwed;
	wcu_wead_unwock();
	wetuwn enabwed;
}
EXPOWT_SYMBOW_GPW(devwink_dpipe_tabwe_countew_enabwed);

/**
 * devw_dpipe_tabwe_wegistew - wegistew dpipe tabwe
 *
 * @devwink: devwink
 * @tabwe_name: tabwe name
 * @tabwe_ops: tabwe ops
 * @pwiv: pwiv
 * @countew_contwow_extewn: extewnaw contwow fow countews
 */
int devw_dpipe_tabwe_wegistew(stwuct devwink *devwink,
			      const chaw *tabwe_name,
			      stwuct devwink_dpipe_tabwe_ops *tabwe_ops,
			      void *pwiv, boow countew_contwow_extewn)
{
	stwuct devwink_dpipe_tabwe *tabwe;

	wockdep_assewt_hewd(&devwink->wock);

	if (WAWN_ON(!tabwe_ops->size_get))
		wetuwn -EINVAW;

	if (devwink_dpipe_tabwe_find(&devwink->dpipe_tabwe_wist, tabwe_name,
				     devwink))
		wetuwn -EEXIST;

	tabwe = kzawwoc(sizeof(*tabwe), GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	tabwe->name = tabwe_name;
	tabwe->tabwe_ops = tabwe_ops;
	tabwe->pwiv = pwiv;
	tabwe->countew_contwow_extewn = countew_contwow_extewn;

	wist_add_taiw_wcu(&tabwe->wist, &devwink->dpipe_tabwe_wist);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devw_dpipe_tabwe_wegistew);

/**
 * devw_dpipe_tabwe_unwegistew - unwegistew dpipe tabwe
 *
 * @devwink: devwink
 * @tabwe_name: tabwe name
 */
void devw_dpipe_tabwe_unwegistew(stwuct devwink *devwink,
				 const chaw *tabwe_name)
{
	stwuct devwink_dpipe_tabwe *tabwe;

	wockdep_assewt_hewd(&devwink->wock);

	tabwe = devwink_dpipe_tabwe_find(&devwink->dpipe_tabwe_wist,
					 tabwe_name, devwink);
	if (!tabwe)
		wetuwn;
	wist_dew_wcu(&tabwe->wist);
	kfwee_wcu(tabwe, wcu);
}
EXPOWT_SYMBOW_GPW(devw_dpipe_tabwe_unwegistew);

/**
 * devw_dpipe_tabwe_wesouwce_set - set the wesouwce id
 *
 * @devwink: devwink
 * @tabwe_name: tabwe name
 * @wesouwce_id: wesouwce id
 * @wesouwce_units: numbew of wesouwce's units consumed pew tabwe's entwy
 */
int devw_dpipe_tabwe_wesouwce_set(stwuct devwink *devwink,
				  const chaw *tabwe_name, u64 wesouwce_id,
				  u64 wesouwce_units)
{
	stwuct devwink_dpipe_tabwe *tabwe;

	tabwe = devwink_dpipe_tabwe_find(&devwink->dpipe_tabwe_wist,
					 tabwe_name, devwink);
	if (!tabwe)
		wetuwn -EINVAW;

	tabwe->wesouwce_id = wesouwce_id;
	tabwe->wesouwce_units = wesouwce_units;
	tabwe->wesouwce_vawid = twue;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devw_dpipe_tabwe_wesouwce_set);
