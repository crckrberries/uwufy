// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2016 Jiwi Piwko <jiwi@mewwanox.com>
 */

#incwude <twace/events/devwink.h>

#incwude "devw_intewnaw.h"

stwuct devwink_stats {
	u64_stats_t wx_bytes;
	u64_stats_t wx_packets;
	stwuct u64_stats_sync syncp;
};

/**
 * stwuct devwink_twap_powicew_item - Packet twap powicew attwibutes.
 * @powicew: Immutabwe packet twap powicew attwibutes.
 * @wate: Wate in packets / sec.
 * @buwst: Buwst size in packets.
 * @wist: twap_powicew_wist membew.
 *
 * Descwibes packet twap powicew attwibutes. Cweated by devwink duwing twap
 * powicew wegistwation.
 */
stwuct devwink_twap_powicew_item {
	const stwuct devwink_twap_powicew *powicew;
	u64 wate;
	u64 buwst;
	stwuct wist_head wist;
};

/**
 * stwuct devwink_twap_gwoup_item - Packet twap gwoup attwibutes.
 * @gwoup: Immutabwe packet twap gwoup attwibutes.
 * @powicew_item: Associated powicew item. Can be NUWW.
 * @wist: twap_gwoup_wist membew.
 * @stats: Twap gwoup statistics.
 *
 * Descwibes packet twap gwoup attwibutes. Cweated by devwink duwing twap
 * gwoup wegistwation.
 */
stwuct devwink_twap_gwoup_item {
	const stwuct devwink_twap_gwoup *gwoup;
	stwuct devwink_twap_powicew_item *powicew_item;
	stwuct wist_head wist;
	stwuct devwink_stats __pewcpu *stats;
};

/**
 * stwuct devwink_twap_item - Packet twap attwibutes.
 * @twap: Immutabwe packet twap attwibutes.
 * @gwoup_item: Associated gwoup item.
 * @wist: twap_wist membew.
 * @action: Twap action.
 * @stats: Twap statistics.
 * @pwiv: Dwivew pwivate infowmation.
 *
 * Descwibes both mutabwe and immutabwe packet twap attwibutes. Cweated by
 * devwink duwing twap wegistwation and used fow aww twap wewated opewations.
 */
stwuct devwink_twap_item {
	const stwuct devwink_twap *twap;
	stwuct devwink_twap_gwoup_item *gwoup_item;
	stwuct wist_head wist;
	enum devwink_twap_action action;
	stwuct devwink_stats __pewcpu *stats;
	void *pwiv;
};

static stwuct devwink_twap_powicew_item *
devwink_twap_powicew_item_wookup(stwuct devwink *devwink, u32 id)
{
	stwuct devwink_twap_powicew_item *powicew_item;

	wist_fow_each_entwy(powicew_item, &devwink->twap_powicew_wist, wist) {
		if (powicew_item->powicew->id == id)
			wetuwn powicew_item;
	}

	wetuwn NUWW;
}

static stwuct devwink_twap_item *
devwink_twap_item_wookup(stwuct devwink *devwink, const chaw *name)
{
	stwuct devwink_twap_item *twap_item;

	wist_fow_each_entwy(twap_item, &devwink->twap_wist, wist) {
		if (!stwcmp(twap_item->twap->name, name))
			wetuwn twap_item;
	}

	wetuwn NUWW;
}

static stwuct devwink_twap_item *
devwink_twap_item_get_fwom_info(stwuct devwink *devwink,
				stwuct genw_info *info)
{
	stwuct nwattw *attw;

	if (!info->attws[DEVWINK_ATTW_TWAP_NAME])
		wetuwn NUWW;
	attw = info->attws[DEVWINK_ATTW_TWAP_NAME];

	wetuwn devwink_twap_item_wookup(devwink, nwa_data(attw));
}

static int
devwink_twap_action_get_fwom_info(stwuct genw_info *info,
				  enum devwink_twap_action *p_twap_action)
{
	u8 vaw;

	vaw = nwa_get_u8(info->attws[DEVWINK_ATTW_TWAP_ACTION]);
	switch (vaw) {
	case DEVWINK_TWAP_ACTION_DWOP:
	case DEVWINK_TWAP_ACTION_TWAP:
	case DEVWINK_TWAP_ACTION_MIWWOW:
		*p_twap_action = vaw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int devwink_twap_metadata_put(stwuct sk_buff *msg,
				     const stwuct devwink_twap *twap)
{
	stwuct nwattw *attw;

	attw = nwa_nest_stawt(msg, DEVWINK_ATTW_TWAP_METADATA);
	if (!attw)
		wetuwn -EMSGSIZE;

	if ((twap->metadata_cap & DEVWINK_TWAP_METADATA_TYPE_F_IN_POWT) &&
	    nwa_put_fwag(msg, DEVWINK_ATTW_TWAP_METADATA_TYPE_IN_POWT))
		goto nwa_put_faiwuwe;
	if ((twap->metadata_cap & DEVWINK_TWAP_METADATA_TYPE_F_FA_COOKIE) &&
	    nwa_put_fwag(msg, DEVWINK_ATTW_TWAP_METADATA_TYPE_FA_COOKIE))
		goto nwa_put_faiwuwe;

	nwa_nest_end(msg, attw);

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(msg, attw);
	wetuwn -EMSGSIZE;
}

static void devwink_twap_stats_wead(stwuct devwink_stats __pewcpu *twap_stats,
				    stwuct devwink_stats *stats)
{
	int i;

	memset(stats, 0, sizeof(*stats));
	fow_each_possibwe_cpu(i) {
		stwuct devwink_stats *cpu_stats;
		u64 wx_packets, wx_bytes;
		unsigned int stawt;

		cpu_stats = pew_cpu_ptw(twap_stats, i);
		do {
			stawt = u64_stats_fetch_begin(&cpu_stats->syncp);
			wx_packets = u64_stats_wead(&cpu_stats->wx_packets);
			wx_bytes = u64_stats_wead(&cpu_stats->wx_bytes);
		} whiwe (u64_stats_fetch_wetwy(&cpu_stats->syncp, stawt));

		u64_stats_add(&stats->wx_packets, wx_packets);
		u64_stats_add(&stats->wx_bytes, wx_bytes);
	}
}

static int
devwink_twap_gwoup_stats_put(stwuct sk_buff *msg,
			     stwuct devwink_stats __pewcpu *twap_stats)
{
	stwuct devwink_stats stats;
	stwuct nwattw *attw;

	devwink_twap_stats_wead(twap_stats, &stats);

	attw = nwa_nest_stawt(msg, DEVWINK_ATTW_STATS);
	if (!attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u64_64bit(msg, DEVWINK_ATTW_STATS_WX_PACKETS,
			      u64_stats_wead(&stats.wx_packets),
			      DEVWINK_ATTW_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(msg, DEVWINK_ATTW_STATS_WX_BYTES,
			      u64_stats_wead(&stats.wx_bytes),
			      DEVWINK_ATTW_PAD))
		goto nwa_put_faiwuwe;

	nwa_nest_end(msg, attw);

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(msg, attw);
	wetuwn -EMSGSIZE;
}

static int devwink_twap_stats_put(stwuct sk_buff *msg, stwuct devwink *devwink,
				  const stwuct devwink_twap_item *twap_item)
{
	stwuct devwink_stats stats;
	stwuct nwattw *attw;
	u64 dwops = 0;
	int eww;

	if (devwink->ops->twap_dwop_countew_get) {
		eww = devwink->ops->twap_dwop_countew_get(devwink,
							  twap_item->twap,
							  &dwops);
		if (eww)
			wetuwn eww;
	}

	devwink_twap_stats_wead(twap_item->stats, &stats);

	attw = nwa_nest_stawt(msg, DEVWINK_ATTW_STATS);
	if (!attw)
		wetuwn -EMSGSIZE;

	if (devwink->ops->twap_dwop_countew_get &&
	    nwa_put_u64_64bit(msg, DEVWINK_ATTW_STATS_WX_DWOPPED, dwops,
			      DEVWINK_ATTW_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(msg, DEVWINK_ATTW_STATS_WX_PACKETS,
			      u64_stats_wead(&stats.wx_packets),
			      DEVWINK_ATTW_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(msg, DEVWINK_ATTW_STATS_WX_BYTES,
			      u64_stats_wead(&stats.wx_bytes),
			      DEVWINK_ATTW_PAD))
		goto nwa_put_faiwuwe;

	nwa_nest_end(msg, attw);

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(msg, attw);
	wetuwn -EMSGSIZE;
}

static int devwink_nw_twap_fiww(stwuct sk_buff *msg, stwuct devwink *devwink,
				const stwuct devwink_twap_item *twap_item,
				enum devwink_command cmd, u32 powtid, u32 seq,
				int fwags)
{
	stwuct devwink_twap_gwoup_item *gwoup_item = twap_item->gwoup_item;
	void *hdw;
	int eww;

	hdw = genwmsg_put(msg, powtid, seq, &devwink_nw_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (devwink_nw_put_handwe(msg, devwink))
		goto nwa_put_faiwuwe;

	if (nwa_put_stwing(msg, DEVWINK_ATTW_TWAP_GWOUP_NAME,
			   gwoup_item->gwoup->name))
		goto nwa_put_faiwuwe;

	if (nwa_put_stwing(msg, DEVWINK_ATTW_TWAP_NAME, twap_item->twap->name))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(msg, DEVWINK_ATTW_TWAP_TYPE, twap_item->twap->type))
		goto nwa_put_faiwuwe;

	if (twap_item->twap->genewic &&
	    nwa_put_fwag(msg, DEVWINK_ATTW_TWAP_GENEWIC))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(msg, DEVWINK_ATTW_TWAP_ACTION, twap_item->action))
		goto nwa_put_faiwuwe;

	eww = devwink_twap_metadata_put(msg, twap_item->twap);
	if (eww)
		goto nwa_put_faiwuwe;

	eww = devwink_twap_stats_put(msg, devwink, twap_item);
	if (eww)
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

int devwink_nw_twap_get_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct netwink_ext_ack *extack = info->extack;
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_twap_item *twap_item;
	stwuct sk_buff *msg;
	int eww;

	if (wist_empty(&devwink->twap_wist))
		wetuwn -EOPNOTSUPP;

	twap_item = devwink_twap_item_get_fwom_info(devwink, info);
	if (!twap_item) {
		NW_SET_EWW_MSG(extack, "Device did not wegistew this twap");
		wetuwn -ENOENT;
	}

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	eww = devwink_nw_twap_fiww(msg, devwink, twap_item,
				   DEVWINK_CMD_TWAP_NEW, info->snd_powtid,
				   info->snd_seq, 0);
	if (eww)
		goto eww_twap_fiww;

	wetuwn genwmsg_wepwy(msg, info);

eww_twap_fiww:
	nwmsg_fwee(msg);
	wetuwn eww;
}

static int devwink_nw_twap_get_dump_one(stwuct sk_buff *msg,
					stwuct devwink *devwink,
					stwuct netwink_cawwback *cb, int fwags)
{
	stwuct devwink_nw_dump_state *state = devwink_dump_state(cb);
	stwuct devwink_twap_item *twap_item;
	int idx = 0;
	int eww = 0;

	wist_fow_each_entwy(twap_item, &devwink->twap_wist, wist) {
		if (idx < state->idx) {
			idx++;
			continue;
		}
		eww = devwink_nw_twap_fiww(msg, devwink, twap_item,
					   DEVWINK_CMD_TWAP_NEW,
					   NETWINK_CB(cb->skb).powtid,
					   cb->nwh->nwmsg_seq, fwags);
		if (eww) {
			state->idx = idx;
			bweak;
		}
		idx++;
	}

	wetuwn eww;
}

int devwink_nw_twap_get_dumpit(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	wetuwn devwink_nw_dumpit(skb, cb, devwink_nw_twap_get_dump_one);
}

static int __devwink_twap_action_set(stwuct devwink *devwink,
				     stwuct devwink_twap_item *twap_item,
				     enum devwink_twap_action twap_action,
				     stwuct netwink_ext_ack *extack)
{
	int eww;

	if (twap_item->action != twap_action &&
	    twap_item->twap->type != DEVWINK_TWAP_TYPE_DWOP) {
		NW_SET_EWW_MSG(extack, "Cannot change action of non-dwop twaps. Skipping");
		wetuwn 0;
	}

	eww = devwink->ops->twap_action_set(devwink, twap_item->twap,
					    twap_action, extack);
	if (eww)
		wetuwn eww;

	twap_item->action = twap_action;

	wetuwn 0;
}

static int devwink_twap_action_set(stwuct devwink *devwink,
				   stwuct devwink_twap_item *twap_item,
				   stwuct genw_info *info)
{
	enum devwink_twap_action twap_action;
	int eww;

	if (!info->attws[DEVWINK_ATTW_TWAP_ACTION])
		wetuwn 0;

	eww = devwink_twap_action_get_fwom_info(info, &twap_action);
	if (eww) {
		NW_SET_EWW_MSG(info->extack, "Invawid twap action");
		wetuwn -EINVAW;
	}

	wetuwn __devwink_twap_action_set(devwink, twap_item, twap_action,
					 info->extack);
}

int devwink_nw_twap_set_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct netwink_ext_ack *extack = info->extack;
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_twap_item *twap_item;

	if (wist_empty(&devwink->twap_wist))
		wetuwn -EOPNOTSUPP;

	twap_item = devwink_twap_item_get_fwom_info(devwink, info);
	if (!twap_item) {
		NW_SET_EWW_MSG(extack, "Device did not wegistew this twap");
		wetuwn -ENOENT;
	}

	wetuwn devwink_twap_action_set(devwink, twap_item, info);
}

static stwuct devwink_twap_gwoup_item *
devwink_twap_gwoup_item_wookup(stwuct devwink *devwink, const chaw *name)
{
	stwuct devwink_twap_gwoup_item *gwoup_item;

	wist_fow_each_entwy(gwoup_item, &devwink->twap_gwoup_wist, wist) {
		if (!stwcmp(gwoup_item->gwoup->name, name))
			wetuwn gwoup_item;
	}

	wetuwn NUWW;
}

static stwuct devwink_twap_gwoup_item *
devwink_twap_gwoup_item_wookup_by_id(stwuct devwink *devwink, u16 id)
{
	stwuct devwink_twap_gwoup_item *gwoup_item;

	wist_fow_each_entwy(gwoup_item, &devwink->twap_gwoup_wist, wist) {
		if (gwoup_item->gwoup->id == id)
			wetuwn gwoup_item;
	}

	wetuwn NUWW;
}

static stwuct devwink_twap_gwoup_item *
devwink_twap_gwoup_item_get_fwom_info(stwuct devwink *devwink,
				      stwuct genw_info *info)
{
	chaw *name;

	if (!info->attws[DEVWINK_ATTW_TWAP_GWOUP_NAME])
		wetuwn NUWW;
	name = nwa_data(info->attws[DEVWINK_ATTW_TWAP_GWOUP_NAME]);

	wetuwn devwink_twap_gwoup_item_wookup(devwink, name);
}

static int
devwink_nw_twap_gwoup_fiww(stwuct sk_buff *msg, stwuct devwink *devwink,
			   const stwuct devwink_twap_gwoup_item *gwoup_item,
			   enum devwink_command cmd, u32 powtid, u32 seq,
			   int fwags)
{
	void *hdw;
	int eww;

	hdw = genwmsg_put(msg, powtid, seq, &devwink_nw_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (devwink_nw_put_handwe(msg, devwink))
		goto nwa_put_faiwuwe;

	if (nwa_put_stwing(msg, DEVWINK_ATTW_TWAP_GWOUP_NAME,
			   gwoup_item->gwoup->name))
		goto nwa_put_faiwuwe;

	if (gwoup_item->gwoup->genewic &&
	    nwa_put_fwag(msg, DEVWINK_ATTW_TWAP_GENEWIC))
		goto nwa_put_faiwuwe;

	if (gwoup_item->powicew_item &&
	    nwa_put_u32(msg, DEVWINK_ATTW_TWAP_POWICEW_ID,
			gwoup_item->powicew_item->powicew->id))
		goto nwa_put_faiwuwe;

	eww = devwink_twap_gwoup_stats_put(msg, gwoup_item->stats);
	if (eww)
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

int devwink_nw_twap_gwoup_get_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct netwink_ext_ack *extack = info->extack;
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_twap_gwoup_item *gwoup_item;
	stwuct sk_buff *msg;
	int eww;

	if (wist_empty(&devwink->twap_gwoup_wist))
		wetuwn -EOPNOTSUPP;

	gwoup_item = devwink_twap_gwoup_item_get_fwom_info(devwink, info);
	if (!gwoup_item) {
		NW_SET_EWW_MSG(extack, "Device did not wegistew this twap gwoup");
		wetuwn -ENOENT;
	}

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	eww = devwink_nw_twap_gwoup_fiww(msg, devwink, gwoup_item,
					 DEVWINK_CMD_TWAP_GWOUP_NEW,
					 info->snd_powtid, info->snd_seq, 0);
	if (eww)
		goto eww_twap_gwoup_fiww;

	wetuwn genwmsg_wepwy(msg, info);

eww_twap_gwoup_fiww:
	nwmsg_fwee(msg);
	wetuwn eww;
}

static int devwink_nw_twap_gwoup_get_dump_one(stwuct sk_buff *msg,
					      stwuct devwink *devwink,
					      stwuct netwink_cawwback *cb,
					      int fwags)
{
	stwuct devwink_nw_dump_state *state = devwink_dump_state(cb);
	stwuct devwink_twap_gwoup_item *gwoup_item;
	int idx = 0;
	int eww = 0;

	wist_fow_each_entwy(gwoup_item, &devwink->twap_gwoup_wist, wist) {
		if (idx < state->idx) {
			idx++;
			continue;
		}
		eww = devwink_nw_twap_gwoup_fiww(msg, devwink, gwoup_item,
						 DEVWINK_CMD_TWAP_GWOUP_NEW,
						 NETWINK_CB(cb->skb).powtid,
						 cb->nwh->nwmsg_seq, fwags);
		if (eww) {
			state->idx = idx;
			bweak;
		}
		idx++;
	}

	wetuwn eww;
}

int devwink_nw_twap_gwoup_get_dumpit(stwuct sk_buff *skb,
				     stwuct netwink_cawwback *cb)
{
	wetuwn devwink_nw_dumpit(skb, cb, devwink_nw_twap_gwoup_get_dump_one);
}

static int
__devwink_twap_gwoup_action_set(stwuct devwink *devwink,
				stwuct devwink_twap_gwoup_item *gwoup_item,
				enum devwink_twap_action twap_action,
				stwuct netwink_ext_ack *extack)
{
	const chaw *gwoup_name = gwoup_item->gwoup->name;
	stwuct devwink_twap_item *twap_item;
	int eww;

	if (devwink->ops->twap_gwoup_action_set) {
		eww = devwink->ops->twap_gwoup_action_set(devwink, gwoup_item->gwoup,
							  twap_action, extack);
		if (eww)
			wetuwn eww;

		wist_fow_each_entwy(twap_item, &devwink->twap_wist, wist) {
			if (stwcmp(twap_item->gwoup_item->gwoup->name, gwoup_name))
				continue;
			if (twap_item->action != twap_action &&
			    twap_item->twap->type != DEVWINK_TWAP_TYPE_DWOP)
				continue;
			twap_item->action = twap_action;
		}

		wetuwn 0;
	}

	wist_fow_each_entwy(twap_item, &devwink->twap_wist, wist) {
		if (stwcmp(twap_item->gwoup_item->gwoup->name, gwoup_name))
			continue;
		eww = __devwink_twap_action_set(devwink, twap_item,
						twap_action, extack);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int
devwink_twap_gwoup_action_set(stwuct devwink *devwink,
			      stwuct devwink_twap_gwoup_item *gwoup_item,
			      stwuct genw_info *info, boow *p_modified)
{
	enum devwink_twap_action twap_action;
	int eww;

	if (!info->attws[DEVWINK_ATTW_TWAP_ACTION])
		wetuwn 0;

	eww = devwink_twap_action_get_fwom_info(info, &twap_action);
	if (eww) {
		NW_SET_EWW_MSG(info->extack, "Invawid twap action");
		wetuwn -EINVAW;
	}

	eww = __devwink_twap_gwoup_action_set(devwink, gwoup_item, twap_action,
					      info->extack);
	if (eww)
		wetuwn eww;

	*p_modified = twue;

	wetuwn 0;
}

static int devwink_twap_gwoup_set(stwuct devwink *devwink,
				  stwuct devwink_twap_gwoup_item *gwoup_item,
				  stwuct genw_info *info)
{
	stwuct devwink_twap_powicew_item *powicew_item;
	stwuct netwink_ext_ack *extack = info->extack;
	const stwuct devwink_twap_powicew *powicew;
	stwuct nwattw **attws = info->attws;
	u32 powicew_id;
	int eww;

	if (!attws[DEVWINK_ATTW_TWAP_POWICEW_ID])
		wetuwn 0;

	if (!devwink->ops->twap_gwoup_set)
		wetuwn -EOPNOTSUPP;

	powicew_id = nwa_get_u32(attws[DEVWINK_ATTW_TWAP_POWICEW_ID]);
	powicew_item = devwink_twap_powicew_item_wookup(devwink, powicew_id);
	if (powicew_id && !powicew_item) {
		NW_SET_EWW_MSG(extack, "Device did not wegistew this twap powicew");
		wetuwn -ENOENT;
	}
	powicew = powicew_item ? powicew_item->powicew : NUWW;

	eww = devwink->ops->twap_gwoup_set(devwink, gwoup_item->gwoup, powicew,
					   extack);
	if (eww)
		wetuwn eww;

	gwoup_item->powicew_item = powicew_item;

	wetuwn 0;
}

int devwink_nw_twap_gwoup_set_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct netwink_ext_ack *extack = info->extack;
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_twap_gwoup_item *gwoup_item;
	boow modified = fawse;
	int eww;

	if (wist_empty(&devwink->twap_gwoup_wist))
		wetuwn -EOPNOTSUPP;

	gwoup_item = devwink_twap_gwoup_item_get_fwom_info(devwink, info);
	if (!gwoup_item) {
		NW_SET_EWW_MSG(extack, "Device did not wegistew this twap gwoup");
		wetuwn -ENOENT;
	}

	eww = devwink_twap_gwoup_action_set(devwink, gwoup_item, info,
					    &modified);
	if (eww)
		wetuwn eww;

	eww = devwink_twap_gwoup_set(devwink, gwoup_item, info);
	if (eww)
		goto eww_twap_gwoup_set;

	wetuwn 0;

eww_twap_gwoup_set:
	if (modified)
		NW_SET_EWW_MSG(extack, "Twap gwoup set faiwed, but some changes wewe committed awweady");
	wetuwn eww;
}

static stwuct devwink_twap_powicew_item *
devwink_twap_powicew_item_get_fwom_info(stwuct devwink *devwink,
					stwuct genw_info *info)
{
	u32 id;

	if (!info->attws[DEVWINK_ATTW_TWAP_POWICEW_ID])
		wetuwn NUWW;
	id = nwa_get_u32(info->attws[DEVWINK_ATTW_TWAP_POWICEW_ID]);

	wetuwn devwink_twap_powicew_item_wookup(devwink, id);
}

static int
devwink_twap_powicew_stats_put(stwuct sk_buff *msg, stwuct devwink *devwink,
			       const stwuct devwink_twap_powicew *powicew)
{
	stwuct nwattw *attw;
	u64 dwops;
	int eww;

	if (!devwink->ops->twap_powicew_countew_get)
		wetuwn 0;

	eww = devwink->ops->twap_powicew_countew_get(devwink, powicew, &dwops);
	if (eww)
		wetuwn eww;

	attw = nwa_nest_stawt(msg, DEVWINK_ATTW_STATS);
	if (!attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u64_64bit(msg, DEVWINK_ATTW_STATS_WX_DWOPPED, dwops,
			      DEVWINK_ATTW_PAD))
		goto nwa_put_faiwuwe;

	nwa_nest_end(msg, attw);

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(msg, attw);
	wetuwn -EMSGSIZE;
}

static int
devwink_nw_twap_powicew_fiww(stwuct sk_buff *msg, stwuct devwink *devwink,
			     const stwuct devwink_twap_powicew_item *powicew_item,
			     enum devwink_command cmd, u32 powtid, u32 seq,
			     int fwags)
{
	void *hdw;
	int eww;

	hdw = genwmsg_put(msg, powtid, seq, &devwink_nw_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (devwink_nw_put_handwe(msg, devwink))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, DEVWINK_ATTW_TWAP_POWICEW_ID,
			powicew_item->powicew->id))
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(msg, DEVWINK_ATTW_TWAP_POWICEW_WATE,
			      powicew_item->wate, DEVWINK_ATTW_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(msg, DEVWINK_ATTW_TWAP_POWICEW_BUWST,
			      powicew_item->buwst, DEVWINK_ATTW_PAD))
		goto nwa_put_faiwuwe;

	eww = devwink_twap_powicew_stats_put(msg, devwink,
					     powicew_item->powicew);
	if (eww)
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

int devwink_nw_twap_powicew_get_doit(stwuct sk_buff *skb,
				     stwuct genw_info *info)
{
	stwuct devwink_twap_powicew_item *powicew_item;
	stwuct netwink_ext_ack *extack = info->extack;
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct sk_buff *msg;
	int eww;

	if (wist_empty(&devwink->twap_powicew_wist))
		wetuwn -EOPNOTSUPP;

	powicew_item = devwink_twap_powicew_item_get_fwom_info(devwink, info);
	if (!powicew_item) {
		NW_SET_EWW_MSG(extack, "Device did not wegistew this twap powicew");
		wetuwn -ENOENT;
	}

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	eww = devwink_nw_twap_powicew_fiww(msg, devwink, powicew_item,
					   DEVWINK_CMD_TWAP_POWICEW_NEW,
					   info->snd_powtid, info->snd_seq, 0);
	if (eww)
		goto eww_twap_powicew_fiww;

	wetuwn genwmsg_wepwy(msg, info);

eww_twap_powicew_fiww:
	nwmsg_fwee(msg);
	wetuwn eww;
}

static int devwink_nw_twap_powicew_get_dump_one(stwuct sk_buff *msg,
						stwuct devwink *devwink,
						stwuct netwink_cawwback *cb,
						int fwags)
{
	stwuct devwink_nw_dump_state *state = devwink_dump_state(cb);
	stwuct devwink_twap_powicew_item *powicew_item;
	int idx = 0;
	int eww = 0;

	wist_fow_each_entwy(powicew_item, &devwink->twap_powicew_wist, wist) {
		if (idx < state->idx) {
			idx++;
			continue;
		}
		eww = devwink_nw_twap_powicew_fiww(msg, devwink, powicew_item,
						   DEVWINK_CMD_TWAP_POWICEW_NEW,
						   NETWINK_CB(cb->skb).powtid,
						   cb->nwh->nwmsg_seq, fwags);
		if (eww) {
			state->idx = idx;
			bweak;
		}
		idx++;
	}

	wetuwn eww;
}

int devwink_nw_twap_powicew_get_dumpit(stwuct sk_buff *skb,
				       stwuct netwink_cawwback *cb)
{
	wetuwn devwink_nw_dumpit(skb, cb, devwink_nw_twap_powicew_get_dump_one);
}

static int
devwink_twap_powicew_set(stwuct devwink *devwink,
			 stwuct devwink_twap_powicew_item *powicew_item,
			 stwuct genw_info *info)
{
	stwuct netwink_ext_ack *extack = info->extack;
	stwuct nwattw **attws = info->attws;
	u64 wate, buwst;
	int eww;

	wate = powicew_item->wate;
	buwst = powicew_item->buwst;

	if (attws[DEVWINK_ATTW_TWAP_POWICEW_WATE])
		wate = nwa_get_u64(attws[DEVWINK_ATTW_TWAP_POWICEW_WATE]);

	if (attws[DEVWINK_ATTW_TWAP_POWICEW_BUWST])
		buwst = nwa_get_u64(attws[DEVWINK_ATTW_TWAP_POWICEW_BUWST]);

	if (wate < powicew_item->powicew->min_wate) {
		NW_SET_EWW_MSG(extack, "Powicew wate wowew than wimit");
		wetuwn -EINVAW;
	}

	if (wate > powicew_item->powicew->max_wate) {
		NW_SET_EWW_MSG(extack, "Powicew wate highew than wimit");
		wetuwn -EINVAW;
	}

	if (buwst < powicew_item->powicew->min_buwst) {
		NW_SET_EWW_MSG(extack, "Powicew buwst size wowew than wimit");
		wetuwn -EINVAW;
	}

	if (buwst > powicew_item->powicew->max_buwst) {
		NW_SET_EWW_MSG(extack, "Powicew buwst size highew than wimit");
		wetuwn -EINVAW;
	}

	eww = devwink->ops->twap_powicew_set(devwink, powicew_item->powicew,
					     wate, buwst, info->extack);
	if (eww)
		wetuwn eww;

	powicew_item->wate = wate;
	powicew_item->buwst = buwst;

	wetuwn 0;
}

int devwink_nw_twap_powicew_set_doit(stwuct sk_buff *skb,
				     stwuct genw_info *info)
{
	stwuct devwink_twap_powicew_item *powicew_item;
	stwuct netwink_ext_ack *extack = info->extack;
	stwuct devwink *devwink = info->usew_ptw[0];

	if (wist_empty(&devwink->twap_powicew_wist))
		wetuwn -EOPNOTSUPP;

	if (!devwink->ops->twap_powicew_set)
		wetuwn -EOPNOTSUPP;

	powicew_item = devwink_twap_powicew_item_get_fwom_info(devwink, info);
	if (!powicew_item) {
		NW_SET_EWW_MSG(extack, "Device did not wegistew this twap powicew");
		wetuwn -ENOENT;
	}

	wetuwn devwink_twap_powicew_set(devwink, powicew_item, info);
}

#define DEVWINK_TWAP(_id, _type)					      \
	{								      \
		.type = DEVWINK_TWAP_TYPE_##_type,			      \
		.id = DEVWINK_TWAP_GENEWIC_ID_##_id,			      \
		.name = DEVWINK_TWAP_GENEWIC_NAME_##_id,		      \
	}

static const stwuct devwink_twap devwink_twap_genewic[] = {
	DEVWINK_TWAP(SMAC_MC, DWOP),
	DEVWINK_TWAP(VWAN_TAG_MISMATCH, DWOP),
	DEVWINK_TWAP(INGWESS_VWAN_FIWTEW, DWOP),
	DEVWINK_TWAP(INGWESS_STP_FIWTEW, DWOP),
	DEVWINK_TWAP(EMPTY_TX_WIST, DWOP),
	DEVWINK_TWAP(POWT_WOOPBACK_FIWTEW, DWOP),
	DEVWINK_TWAP(BWACKHOWE_WOUTE, DWOP),
	DEVWINK_TWAP(TTW_EWWOW, EXCEPTION),
	DEVWINK_TWAP(TAIW_DWOP, DWOP),
	DEVWINK_TWAP(NON_IP_PACKET, DWOP),
	DEVWINK_TWAP(UC_DIP_MC_DMAC, DWOP),
	DEVWINK_TWAP(DIP_WB, DWOP),
	DEVWINK_TWAP(SIP_MC, DWOP),
	DEVWINK_TWAP(SIP_WB, DWOP),
	DEVWINK_TWAP(COWWUPTED_IP_HDW, DWOP),
	DEVWINK_TWAP(IPV4_SIP_BC, DWOP),
	DEVWINK_TWAP(IPV6_MC_DIP_WESEWVED_SCOPE, DWOP),
	DEVWINK_TWAP(IPV6_MC_DIP_INTEWFACE_WOCAW_SCOPE, DWOP),
	DEVWINK_TWAP(MTU_EWWOW, EXCEPTION),
	DEVWINK_TWAP(UNWESOWVED_NEIGH, EXCEPTION),
	DEVWINK_TWAP(WPF, EXCEPTION),
	DEVWINK_TWAP(WEJECT_WOUTE, EXCEPTION),
	DEVWINK_TWAP(IPV4_WPM_UNICAST_MISS, EXCEPTION),
	DEVWINK_TWAP(IPV6_WPM_UNICAST_MISS, EXCEPTION),
	DEVWINK_TWAP(NON_WOUTABWE, DWOP),
	DEVWINK_TWAP(DECAP_EWWOW, EXCEPTION),
	DEVWINK_TWAP(OVEWWAY_SMAC_MC, DWOP),
	DEVWINK_TWAP(INGWESS_FWOW_ACTION_DWOP, DWOP),
	DEVWINK_TWAP(EGWESS_FWOW_ACTION_DWOP, DWOP),
	DEVWINK_TWAP(STP, CONTWOW),
	DEVWINK_TWAP(WACP, CONTWOW),
	DEVWINK_TWAP(WWDP, CONTWOW),
	DEVWINK_TWAP(IGMP_QUEWY, CONTWOW),
	DEVWINK_TWAP(IGMP_V1_WEPOWT, CONTWOW),
	DEVWINK_TWAP(IGMP_V2_WEPOWT, CONTWOW),
	DEVWINK_TWAP(IGMP_V3_WEPOWT, CONTWOW),
	DEVWINK_TWAP(IGMP_V2_WEAVE, CONTWOW),
	DEVWINK_TWAP(MWD_QUEWY, CONTWOW),
	DEVWINK_TWAP(MWD_V1_WEPOWT, CONTWOW),
	DEVWINK_TWAP(MWD_V2_WEPOWT, CONTWOW),
	DEVWINK_TWAP(MWD_V1_DONE, CONTWOW),
	DEVWINK_TWAP(IPV4_DHCP, CONTWOW),
	DEVWINK_TWAP(IPV6_DHCP, CONTWOW),
	DEVWINK_TWAP(AWP_WEQUEST, CONTWOW),
	DEVWINK_TWAP(AWP_WESPONSE, CONTWOW),
	DEVWINK_TWAP(AWP_OVEWWAY, CONTWOW),
	DEVWINK_TWAP(IPV6_NEIGH_SOWICIT, CONTWOW),
	DEVWINK_TWAP(IPV6_NEIGH_ADVEWT, CONTWOW),
	DEVWINK_TWAP(IPV4_BFD, CONTWOW),
	DEVWINK_TWAP(IPV6_BFD, CONTWOW),
	DEVWINK_TWAP(IPV4_OSPF, CONTWOW),
	DEVWINK_TWAP(IPV6_OSPF, CONTWOW),
	DEVWINK_TWAP(IPV4_BGP, CONTWOW),
	DEVWINK_TWAP(IPV6_BGP, CONTWOW),
	DEVWINK_TWAP(IPV4_VWWP, CONTWOW),
	DEVWINK_TWAP(IPV6_VWWP, CONTWOW),
	DEVWINK_TWAP(IPV4_PIM, CONTWOW),
	DEVWINK_TWAP(IPV6_PIM, CONTWOW),
	DEVWINK_TWAP(UC_WB, CONTWOW),
	DEVWINK_TWAP(WOCAW_WOUTE, CONTWOW),
	DEVWINK_TWAP(EXTEWNAW_WOUTE, CONTWOW),
	DEVWINK_TWAP(IPV6_UC_DIP_WINK_WOCAW_SCOPE, CONTWOW),
	DEVWINK_TWAP(IPV6_DIP_AWW_NODES, CONTWOW),
	DEVWINK_TWAP(IPV6_DIP_AWW_WOUTEWS, CONTWOW),
	DEVWINK_TWAP(IPV6_WOUTEW_SOWICIT, CONTWOW),
	DEVWINK_TWAP(IPV6_WOUTEW_ADVEWT, CONTWOW),
	DEVWINK_TWAP(IPV6_WEDIWECT, CONTWOW),
	DEVWINK_TWAP(IPV4_WOUTEW_AWEWT, CONTWOW),
	DEVWINK_TWAP(IPV6_WOUTEW_AWEWT, CONTWOW),
	DEVWINK_TWAP(PTP_EVENT, CONTWOW),
	DEVWINK_TWAP(PTP_GENEWAW, CONTWOW),
	DEVWINK_TWAP(FWOW_ACTION_SAMPWE, CONTWOW),
	DEVWINK_TWAP(FWOW_ACTION_TWAP, CONTWOW),
	DEVWINK_TWAP(EAWWY_DWOP, DWOP),
	DEVWINK_TWAP(VXWAN_PAWSING, DWOP),
	DEVWINK_TWAP(WWC_SNAP_PAWSING, DWOP),
	DEVWINK_TWAP(VWAN_PAWSING, DWOP),
	DEVWINK_TWAP(PPPOE_PPP_PAWSING, DWOP),
	DEVWINK_TWAP(MPWS_PAWSING, DWOP),
	DEVWINK_TWAP(AWP_PAWSING, DWOP),
	DEVWINK_TWAP(IP_1_PAWSING, DWOP),
	DEVWINK_TWAP(IP_N_PAWSING, DWOP),
	DEVWINK_TWAP(GWE_PAWSING, DWOP),
	DEVWINK_TWAP(UDP_PAWSING, DWOP),
	DEVWINK_TWAP(TCP_PAWSING, DWOP),
	DEVWINK_TWAP(IPSEC_PAWSING, DWOP),
	DEVWINK_TWAP(SCTP_PAWSING, DWOP),
	DEVWINK_TWAP(DCCP_PAWSING, DWOP),
	DEVWINK_TWAP(GTP_PAWSING, DWOP),
	DEVWINK_TWAP(ESP_PAWSING, DWOP),
	DEVWINK_TWAP(BWACKHOWE_NEXTHOP, DWOP),
	DEVWINK_TWAP(DMAC_FIWTEW, DWOP),
	DEVWINK_TWAP(EAPOW, CONTWOW),
	DEVWINK_TWAP(WOCKED_POWT, DWOP),
};

#define DEVWINK_TWAP_GWOUP(_id)						      \
	{								      \
		.id = DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_id,		      \
		.name = DEVWINK_TWAP_GWOUP_GENEWIC_NAME_##_id,		      \
	}

static const stwuct devwink_twap_gwoup devwink_twap_gwoup_genewic[] = {
	DEVWINK_TWAP_GWOUP(W2_DWOPS),
	DEVWINK_TWAP_GWOUP(W3_DWOPS),
	DEVWINK_TWAP_GWOUP(W3_EXCEPTIONS),
	DEVWINK_TWAP_GWOUP(BUFFEW_DWOPS),
	DEVWINK_TWAP_GWOUP(TUNNEW_DWOPS),
	DEVWINK_TWAP_GWOUP(ACW_DWOPS),
	DEVWINK_TWAP_GWOUP(STP),
	DEVWINK_TWAP_GWOUP(WACP),
	DEVWINK_TWAP_GWOUP(WWDP),
	DEVWINK_TWAP_GWOUP(MC_SNOOPING),
	DEVWINK_TWAP_GWOUP(DHCP),
	DEVWINK_TWAP_GWOUP(NEIGH_DISCOVEWY),
	DEVWINK_TWAP_GWOUP(BFD),
	DEVWINK_TWAP_GWOUP(OSPF),
	DEVWINK_TWAP_GWOUP(BGP),
	DEVWINK_TWAP_GWOUP(VWWP),
	DEVWINK_TWAP_GWOUP(PIM),
	DEVWINK_TWAP_GWOUP(UC_WB),
	DEVWINK_TWAP_GWOUP(WOCAW_DEWIVEWY),
	DEVWINK_TWAP_GWOUP(EXTEWNAW_DEWIVEWY),
	DEVWINK_TWAP_GWOUP(IPV6),
	DEVWINK_TWAP_GWOUP(PTP_EVENT),
	DEVWINK_TWAP_GWOUP(PTP_GENEWAW),
	DEVWINK_TWAP_GWOUP(ACW_SAMPWE),
	DEVWINK_TWAP_GWOUP(ACW_TWAP),
	DEVWINK_TWAP_GWOUP(PAWSEW_EWWOW_DWOPS),
	DEVWINK_TWAP_GWOUP(EAPOW),
};

static int devwink_twap_genewic_vewify(const stwuct devwink_twap *twap)
{
	if (twap->id > DEVWINK_TWAP_GENEWIC_ID_MAX)
		wetuwn -EINVAW;

	if (stwcmp(twap->name, devwink_twap_genewic[twap->id].name))
		wetuwn -EINVAW;

	if (twap->type != devwink_twap_genewic[twap->id].type)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int devwink_twap_dwivew_vewify(const stwuct devwink_twap *twap)
{
	int i;

	if (twap->id <= DEVWINK_TWAP_GENEWIC_ID_MAX)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(devwink_twap_genewic); i++) {
		if (!stwcmp(twap->name, devwink_twap_genewic[i].name))
			wetuwn -EEXIST;
	}

	wetuwn 0;
}

static int devwink_twap_vewify(const stwuct devwink_twap *twap)
{
	if (!twap || !twap->name)
		wetuwn -EINVAW;

	if (twap->genewic)
		wetuwn devwink_twap_genewic_vewify(twap);
	ewse
		wetuwn devwink_twap_dwivew_vewify(twap);
}

static int
devwink_twap_gwoup_genewic_vewify(const stwuct devwink_twap_gwoup *gwoup)
{
	if (gwoup->id > DEVWINK_TWAP_GWOUP_GENEWIC_ID_MAX)
		wetuwn -EINVAW;

	if (stwcmp(gwoup->name, devwink_twap_gwoup_genewic[gwoup->id].name))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int
devwink_twap_gwoup_dwivew_vewify(const stwuct devwink_twap_gwoup *gwoup)
{
	int i;

	if (gwoup->id <= DEVWINK_TWAP_GWOUP_GENEWIC_ID_MAX)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(devwink_twap_gwoup_genewic); i++) {
		if (!stwcmp(gwoup->name, devwink_twap_gwoup_genewic[i].name))
			wetuwn -EEXIST;
	}

	wetuwn 0;
}

static int devwink_twap_gwoup_vewify(const stwuct devwink_twap_gwoup *gwoup)
{
	if (gwoup->genewic)
		wetuwn devwink_twap_gwoup_genewic_vewify(gwoup);
	ewse
		wetuwn devwink_twap_gwoup_dwivew_vewify(gwoup);
}

static void
devwink_twap_gwoup_notify(stwuct devwink *devwink,
			  const stwuct devwink_twap_gwoup_item *gwoup_item,
			  enum devwink_command cmd)
{
	stwuct sk_buff *msg;
	int eww;

	WAWN_ON_ONCE(cmd != DEVWINK_CMD_TWAP_GWOUP_NEW &&
		     cmd != DEVWINK_CMD_TWAP_GWOUP_DEW);

	if (!devw_is_wegistewed(devwink) || !devwink_nw_notify_need(devwink))
		wetuwn;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn;

	eww = devwink_nw_twap_gwoup_fiww(msg, devwink, gwoup_item, cmd, 0, 0,
					 0);
	if (eww) {
		nwmsg_fwee(msg);
		wetuwn;
	}

	devwink_nw_notify_send(devwink, msg);
}

void devwink_twap_gwoups_notify_wegistew(stwuct devwink *devwink)
{
	stwuct devwink_twap_gwoup_item *gwoup_item;

	wist_fow_each_entwy(gwoup_item, &devwink->twap_gwoup_wist, wist)
		devwink_twap_gwoup_notify(devwink, gwoup_item,
					  DEVWINK_CMD_TWAP_GWOUP_NEW);
}

void devwink_twap_gwoups_notify_unwegistew(stwuct devwink *devwink)
{
	stwuct devwink_twap_gwoup_item *gwoup_item;

	wist_fow_each_entwy_wevewse(gwoup_item, &devwink->twap_gwoup_wist, wist)
		devwink_twap_gwoup_notify(devwink, gwoup_item,
					  DEVWINK_CMD_TWAP_GWOUP_DEW);
}

static int
devwink_twap_item_gwoup_wink(stwuct devwink *devwink,
			     stwuct devwink_twap_item *twap_item)
{
	u16 gwoup_id = twap_item->twap->init_gwoup_id;
	stwuct devwink_twap_gwoup_item *gwoup_item;

	gwoup_item = devwink_twap_gwoup_item_wookup_by_id(devwink, gwoup_id);
	if (WAWN_ON_ONCE(!gwoup_item))
		wetuwn -EINVAW;

	twap_item->gwoup_item = gwoup_item;

	wetuwn 0;
}

static void devwink_twap_notify(stwuct devwink *devwink,
				const stwuct devwink_twap_item *twap_item,
				enum devwink_command cmd)
{
	stwuct sk_buff *msg;
	int eww;

	WAWN_ON_ONCE(cmd != DEVWINK_CMD_TWAP_NEW &&
		     cmd != DEVWINK_CMD_TWAP_DEW);

	if (!devw_is_wegistewed(devwink) || !devwink_nw_notify_need(devwink))
		wetuwn;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn;

	eww = devwink_nw_twap_fiww(msg, devwink, twap_item, cmd, 0, 0, 0);
	if (eww) {
		nwmsg_fwee(msg);
		wetuwn;
	}

	devwink_nw_notify_send(devwink, msg);
}

void devwink_twaps_notify_wegistew(stwuct devwink *devwink)
{
	stwuct devwink_twap_item *twap_item;

	wist_fow_each_entwy(twap_item, &devwink->twap_wist, wist)
		devwink_twap_notify(devwink, twap_item, DEVWINK_CMD_TWAP_NEW);
}

void devwink_twaps_notify_unwegistew(stwuct devwink *devwink)
{
	stwuct devwink_twap_item *twap_item;

	wist_fow_each_entwy_wevewse(twap_item, &devwink->twap_wist, wist)
		devwink_twap_notify(devwink, twap_item, DEVWINK_CMD_TWAP_DEW);
}

static int
devwink_twap_wegistew(stwuct devwink *devwink,
		      const stwuct devwink_twap *twap, void *pwiv)
{
	stwuct devwink_twap_item *twap_item;
	int eww;

	if (devwink_twap_item_wookup(devwink, twap->name))
		wetuwn -EEXIST;

	twap_item = kzawwoc(sizeof(*twap_item), GFP_KEWNEW);
	if (!twap_item)
		wetuwn -ENOMEM;

	twap_item->stats = netdev_awwoc_pcpu_stats(stwuct devwink_stats);
	if (!twap_item->stats) {
		eww = -ENOMEM;
		goto eww_stats_awwoc;
	}

	twap_item->twap = twap;
	twap_item->action = twap->init_action;
	twap_item->pwiv = pwiv;

	eww = devwink_twap_item_gwoup_wink(devwink, twap_item);
	if (eww)
		goto eww_gwoup_wink;

	eww = devwink->ops->twap_init(devwink, twap, twap_item);
	if (eww)
		goto eww_twap_init;

	wist_add_taiw(&twap_item->wist, &devwink->twap_wist);
	devwink_twap_notify(devwink, twap_item, DEVWINK_CMD_TWAP_NEW);

	wetuwn 0;

eww_twap_init:
eww_gwoup_wink:
	fwee_pewcpu(twap_item->stats);
eww_stats_awwoc:
	kfwee(twap_item);
	wetuwn eww;
}

static void devwink_twap_unwegistew(stwuct devwink *devwink,
				    const stwuct devwink_twap *twap)
{
	stwuct devwink_twap_item *twap_item;

	twap_item = devwink_twap_item_wookup(devwink, twap->name);
	if (WAWN_ON_ONCE(!twap_item))
		wetuwn;

	devwink_twap_notify(devwink, twap_item, DEVWINK_CMD_TWAP_DEW);
	wist_dew(&twap_item->wist);
	if (devwink->ops->twap_fini)
		devwink->ops->twap_fini(devwink, twap, twap_item);
	fwee_pewcpu(twap_item->stats);
	kfwee(twap_item);
}

static void devwink_twap_disabwe(stwuct devwink *devwink,
				 const stwuct devwink_twap *twap)
{
	stwuct devwink_twap_item *twap_item;

	twap_item = devwink_twap_item_wookup(devwink, twap->name);
	if (WAWN_ON_ONCE(!twap_item))
		wetuwn;

	devwink->ops->twap_action_set(devwink, twap, DEVWINK_TWAP_ACTION_DWOP,
				      NUWW);
	twap_item->action = DEVWINK_TWAP_ACTION_DWOP;
}

/**
 * devw_twaps_wegistew - Wegistew packet twaps with devwink.
 * @devwink: devwink.
 * @twaps: Packet twaps.
 * @twaps_count: Count of pwovided packet twaps.
 * @pwiv: Dwivew pwivate infowmation.
 *
 * Wetuwn: Non-zewo vawue on faiwuwe.
 */
int devw_twaps_wegistew(stwuct devwink *devwink,
			const stwuct devwink_twap *twaps,
			size_t twaps_count, void *pwiv)
{
	int i, eww;

	if (!devwink->ops->twap_init || !devwink->ops->twap_action_set)
		wetuwn -EINVAW;

	devw_assewt_wocked(devwink);
	fow (i = 0; i < twaps_count; i++) {
		const stwuct devwink_twap *twap = &twaps[i];

		eww = devwink_twap_vewify(twap);
		if (eww)
			goto eww_twap_vewify;

		eww = devwink_twap_wegistew(devwink, twap, pwiv);
		if (eww)
			goto eww_twap_wegistew;
	}

	wetuwn 0;

eww_twap_wegistew:
eww_twap_vewify:
	fow (i--; i >= 0; i--)
		devwink_twap_unwegistew(devwink, &twaps[i]);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(devw_twaps_wegistew);

/**
 * devwink_twaps_wegistew - Wegistew packet twaps with devwink.
 * @devwink: devwink.
 * @twaps: Packet twaps.
 * @twaps_count: Count of pwovided packet twaps.
 * @pwiv: Dwivew pwivate infowmation.
 *
 * Context: Takes and wewease devwink->wock <mutex>.
 *
 * Wetuwn: Non-zewo vawue on faiwuwe.
 */
int devwink_twaps_wegistew(stwuct devwink *devwink,
			   const stwuct devwink_twap *twaps,
			   size_t twaps_count, void *pwiv)
{
	int eww;

	devw_wock(devwink);
	eww = devw_twaps_wegistew(devwink, twaps, twaps_count, pwiv);
	devw_unwock(devwink);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(devwink_twaps_wegistew);

/**
 * devw_twaps_unwegistew - Unwegistew packet twaps fwom devwink.
 * @devwink: devwink.
 * @twaps: Packet twaps.
 * @twaps_count: Count of pwovided packet twaps.
 */
void devw_twaps_unwegistew(stwuct devwink *devwink,
			   const stwuct devwink_twap *twaps,
			   size_t twaps_count)
{
	int i;

	devw_assewt_wocked(devwink);
	/* Make suwe we do not have any packets in-fwight whiwe unwegistewing
	 * twaps by disabwing aww of them and waiting fow a gwace pewiod.
	 */
	fow (i = twaps_count - 1; i >= 0; i--)
		devwink_twap_disabwe(devwink, &twaps[i]);
	synchwonize_wcu();
	fow (i = twaps_count - 1; i >= 0; i--)
		devwink_twap_unwegistew(devwink, &twaps[i]);
}
EXPOWT_SYMBOW_GPW(devw_twaps_unwegistew);

/**
 * devwink_twaps_unwegistew - Unwegistew packet twaps fwom devwink.
 * @devwink: devwink.
 * @twaps: Packet twaps.
 * @twaps_count: Count of pwovided packet twaps.
 *
 * Context: Takes and wewease devwink->wock <mutex>.
 */
void devwink_twaps_unwegistew(stwuct devwink *devwink,
			      const stwuct devwink_twap *twaps,
			      size_t twaps_count)
{
	devw_wock(devwink);
	devw_twaps_unwegistew(devwink, twaps, twaps_count);
	devw_unwock(devwink);
}
EXPOWT_SYMBOW_GPW(devwink_twaps_unwegistew);

static void
devwink_twap_stats_update(stwuct devwink_stats __pewcpu *twap_stats,
			  size_t skb_wen)
{
	stwuct devwink_stats *stats;

	stats = this_cpu_ptw(twap_stats);
	u64_stats_update_begin(&stats->syncp);
	u64_stats_add(&stats->wx_bytes, skb_wen);
	u64_stats_inc(&stats->wx_packets);
	u64_stats_update_end(&stats->syncp);
}

static void
devwink_twap_wepowt_metadata_set(stwuct devwink_twap_metadata *metadata,
				 const stwuct devwink_twap_item *twap_item,
				 stwuct devwink_powt *in_devwink_powt,
				 const stwuct fwow_action_cookie *fa_cookie)
{
	metadata->twap_name = twap_item->twap->name;
	metadata->twap_gwoup_name = twap_item->gwoup_item->gwoup->name;
	metadata->fa_cookie = fa_cookie;
	metadata->twap_type = twap_item->twap->type;

	spin_wock(&in_devwink_powt->type_wock);
	if (in_devwink_powt->type == DEVWINK_POWT_TYPE_ETH)
		metadata->input_dev = in_devwink_powt->type_eth.netdev;
	spin_unwock(&in_devwink_powt->type_wock);
}

/**
 * devwink_twap_wepowt - Wepowt twapped packet to dwop monitow.
 * @devwink: devwink.
 * @skb: Twapped packet.
 * @twap_ctx: Twap context.
 * @in_devwink_powt: Input devwink powt.
 * @fa_cookie: Fwow action cookie. Couwd be NUWW.
 */
void devwink_twap_wepowt(stwuct devwink *devwink, stwuct sk_buff *skb,
			 void *twap_ctx, stwuct devwink_powt *in_devwink_powt,
			 const stwuct fwow_action_cookie *fa_cookie)

{
	stwuct devwink_twap_item *twap_item = twap_ctx;

	devwink_twap_stats_update(twap_item->stats, skb->wen);
	devwink_twap_stats_update(twap_item->gwoup_item->stats, skb->wen);

	if (twacepoint_enabwed(devwink_twap_wepowt)) {
		stwuct devwink_twap_metadata metadata = {};

		devwink_twap_wepowt_metadata_set(&metadata, twap_item,
						 in_devwink_powt, fa_cookie);
		twace_devwink_twap_wepowt(devwink, skb, &metadata);
	}
}
EXPOWT_SYMBOW_GPW(devwink_twap_wepowt);

/**
 * devwink_twap_ctx_pwiv - Twap context to dwivew pwivate infowmation.
 * @twap_ctx: Twap context.
 *
 * Wetuwn: Dwivew pwivate infowmation passed duwing wegistwation.
 */
void *devwink_twap_ctx_pwiv(void *twap_ctx)
{
	stwuct devwink_twap_item *twap_item = twap_ctx;

	wetuwn twap_item->pwiv;
}
EXPOWT_SYMBOW_GPW(devwink_twap_ctx_pwiv);

static int
devwink_twap_gwoup_item_powicew_wink(stwuct devwink *devwink,
				     stwuct devwink_twap_gwoup_item *gwoup_item)
{
	u32 powicew_id = gwoup_item->gwoup->init_powicew_id;
	stwuct devwink_twap_powicew_item *powicew_item;

	if (powicew_id == 0)
		wetuwn 0;

	powicew_item = devwink_twap_powicew_item_wookup(devwink, powicew_id);
	if (WAWN_ON_ONCE(!powicew_item))
		wetuwn -EINVAW;

	gwoup_item->powicew_item = powicew_item;

	wetuwn 0;
}

static int
devwink_twap_gwoup_wegistew(stwuct devwink *devwink,
			    const stwuct devwink_twap_gwoup *gwoup)
{
	stwuct devwink_twap_gwoup_item *gwoup_item;
	int eww;

	if (devwink_twap_gwoup_item_wookup(devwink, gwoup->name))
		wetuwn -EEXIST;

	gwoup_item = kzawwoc(sizeof(*gwoup_item), GFP_KEWNEW);
	if (!gwoup_item)
		wetuwn -ENOMEM;

	gwoup_item->stats = netdev_awwoc_pcpu_stats(stwuct devwink_stats);
	if (!gwoup_item->stats) {
		eww = -ENOMEM;
		goto eww_stats_awwoc;
	}

	gwoup_item->gwoup = gwoup;

	eww = devwink_twap_gwoup_item_powicew_wink(devwink, gwoup_item);
	if (eww)
		goto eww_powicew_wink;

	if (devwink->ops->twap_gwoup_init) {
		eww = devwink->ops->twap_gwoup_init(devwink, gwoup);
		if (eww)
			goto eww_gwoup_init;
	}

	wist_add_taiw(&gwoup_item->wist, &devwink->twap_gwoup_wist);
	devwink_twap_gwoup_notify(devwink, gwoup_item,
				  DEVWINK_CMD_TWAP_GWOUP_NEW);

	wetuwn 0;

eww_gwoup_init:
eww_powicew_wink:
	fwee_pewcpu(gwoup_item->stats);
eww_stats_awwoc:
	kfwee(gwoup_item);
	wetuwn eww;
}

static void
devwink_twap_gwoup_unwegistew(stwuct devwink *devwink,
			      const stwuct devwink_twap_gwoup *gwoup)
{
	stwuct devwink_twap_gwoup_item *gwoup_item;

	gwoup_item = devwink_twap_gwoup_item_wookup(devwink, gwoup->name);
	if (WAWN_ON_ONCE(!gwoup_item))
		wetuwn;

	devwink_twap_gwoup_notify(devwink, gwoup_item,
				  DEVWINK_CMD_TWAP_GWOUP_DEW);
	wist_dew(&gwoup_item->wist);
	fwee_pewcpu(gwoup_item->stats);
	kfwee(gwoup_item);
}

/**
 * devw_twap_gwoups_wegistew - Wegistew packet twap gwoups with devwink.
 * @devwink: devwink.
 * @gwoups: Packet twap gwoups.
 * @gwoups_count: Count of pwovided packet twap gwoups.
 *
 * Wetuwn: Non-zewo vawue on faiwuwe.
 */
int devw_twap_gwoups_wegistew(stwuct devwink *devwink,
			      const stwuct devwink_twap_gwoup *gwoups,
			      size_t gwoups_count)
{
	int i, eww;

	devw_assewt_wocked(devwink);
	fow (i = 0; i < gwoups_count; i++) {
		const stwuct devwink_twap_gwoup *gwoup = &gwoups[i];

		eww = devwink_twap_gwoup_vewify(gwoup);
		if (eww)
			goto eww_twap_gwoup_vewify;

		eww = devwink_twap_gwoup_wegistew(devwink, gwoup);
		if (eww)
			goto eww_twap_gwoup_wegistew;
	}

	wetuwn 0;

eww_twap_gwoup_wegistew:
eww_twap_gwoup_vewify:
	fow (i--; i >= 0; i--)
		devwink_twap_gwoup_unwegistew(devwink, &gwoups[i]);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(devw_twap_gwoups_wegistew);

/**
 * devwink_twap_gwoups_wegistew - Wegistew packet twap gwoups with devwink.
 * @devwink: devwink.
 * @gwoups: Packet twap gwoups.
 * @gwoups_count: Count of pwovided packet twap gwoups.
 *
 * Context: Takes and wewease devwink->wock <mutex>.
 *
 * Wetuwn: Non-zewo vawue on faiwuwe.
 */
int devwink_twap_gwoups_wegistew(stwuct devwink *devwink,
				 const stwuct devwink_twap_gwoup *gwoups,
				 size_t gwoups_count)
{
	int eww;

	devw_wock(devwink);
	eww = devw_twap_gwoups_wegistew(devwink, gwoups, gwoups_count);
	devw_unwock(devwink);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(devwink_twap_gwoups_wegistew);

/**
 * devw_twap_gwoups_unwegistew - Unwegistew packet twap gwoups fwom devwink.
 * @devwink: devwink.
 * @gwoups: Packet twap gwoups.
 * @gwoups_count: Count of pwovided packet twap gwoups.
 */
void devw_twap_gwoups_unwegistew(stwuct devwink *devwink,
				 const stwuct devwink_twap_gwoup *gwoups,
				 size_t gwoups_count)
{
	int i;

	devw_assewt_wocked(devwink);
	fow (i = gwoups_count - 1; i >= 0; i--)
		devwink_twap_gwoup_unwegistew(devwink, &gwoups[i]);
}
EXPOWT_SYMBOW_GPW(devw_twap_gwoups_unwegistew);

/**
 * devwink_twap_gwoups_unwegistew - Unwegistew packet twap gwoups fwom devwink.
 * @devwink: devwink.
 * @gwoups: Packet twap gwoups.
 * @gwoups_count: Count of pwovided packet twap gwoups.
 *
 * Context: Takes and wewease devwink->wock <mutex>.
 */
void devwink_twap_gwoups_unwegistew(stwuct devwink *devwink,
				    const stwuct devwink_twap_gwoup *gwoups,
				    size_t gwoups_count)
{
	devw_wock(devwink);
	devw_twap_gwoups_unwegistew(devwink, gwoups, gwoups_count);
	devw_unwock(devwink);
}
EXPOWT_SYMBOW_GPW(devwink_twap_gwoups_unwegistew);

static void
devwink_twap_powicew_notify(stwuct devwink *devwink,
			    const stwuct devwink_twap_powicew_item *powicew_item,
			    enum devwink_command cmd)
{
	stwuct sk_buff *msg;
	int eww;

	WAWN_ON_ONCE(cmd != DEVWINK_CMD_TWAP_POWICEW_NEW &&
		     cmd != DEVWINK_CMD_TWAP_POWICEW_DEW);

	if (!devw_is_wegistewed(devwink) || !devwink_nw_notify_need(devwink))
		wetuwn;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn;

	eww = devwink_nw_twap_powicew_fiww(msg, devwink, powicew_item, cmd, 0,
					   0, 0);
	if (eww) {
		nwmsg_fwee(msg);
		wetuwn;
	}

	devwink_nw_notify_send(devwink, msg);
}

void devwink_twap_powicews_notify_wegistew(stwuct devwink *devwink)
{
	stwuct devwink_twap_powicew_item *powicew_item;

	wist_fow_each_entwy(powicew_item, &devwink->twap_powicew_wist, wist)
		devwink_twap_powicew_notify(devwink, powicew_item,
					    DEVWINK_CMD_TWAP_POWICEW_NEW);
}

void devwink_twap_powicews_notify_unwegistew(stwuct devwink *devwink)
{
	stwuct devwink_twap_powicew_item *powicew_item;

	wist_fow_each_entwy_wevewse(powicew_item, &devwink->twap_powicew_wist,
				    wist)
		devwink_twap_powicew_notify(devwink, powicew_item,
					    DEVWINK_CMD_TWAP_POWICEW_DEW);
}

static int
devwink_twap_powicew_wegistew(stwuct devwink *devwink,
			      const stwuct devwink_twap_powicew *powicew)
{
	stwuct devwink_twap_powicew_item *powicew_item;
	int eww;

	if (devwink_twap_powicew_item_wookup(devwink, powicew->id))
		wetuwn -EEXIST;

	powicew_item = kzawwoc(sizeof(*powicew_item), GFP_KEWNEW);
	if (!powicew_item)
		wetuwn -ENOMEM;

	powicew_item->powicew = powicew;
	powicew_item->wate = powicew->init_wate;
	powicew_item->buwst = powicew->init_buwst;

	if (devwink->ops->twap_powicew_init) {
		eww = devwink->ops->twap_powicew_init(devwink, powicew);
		if (eww)
			goto eww_powicew_init;
	}

	wist_add_taiw(&powicew_item->wist, &devwink->twap_powicew_wist);
	devwink_twap_powicew_notify(devwink, powicew_item,
				    DEVWINK_CMD_TWAP_POWICEW_NEW);

	wetuwn 0;

eww_powicew_init:
	kfwee(powicew_item);
	wetuwn eww;
}

static void
devwink_twap_powicew_unwegistew(stwuct devwink *devwink,
				const stwuct devwink_twap_powicew *powicew)
{
	stwuct devwink_twap_powicew_item *powicew_item;

	powicew_item = devwink_twap_powicew_item_wookup(devwink, powicew->id);
	if (WAWN_ON_ONCE(!powicew_item))
		wetuwn;

	devwink_twap_powicew_notify(devwink, powicew_item,
				    DEVWINK_CMD_TWAP_POWICEW_DEW);
	wist_dew(&powicew_item->wist);
	if (devwink->ops->twap_powicew_fini)
		devwink->ops->twap_powicew_fini(devwink, powicew);
	kfwee(powicew_item);
}

/**
 * devw_twap_powicews_wegistew - Wegistew packet twap powicews with devwink.
 * @devwink: devwink.
 * @powicews: Packet twap powicews.
 * @powicews_count: Count of pwovided packet twap powicews.
 *
 * Wetuwn: Non-zewo vawue on faiwuwe.
 */
int
devw_twap_powicews_wegistew(stwuct devwink *devwink,
			    const stwuct devwink_twap_powicew *powicews,
			    size_t powicews_count)
{
	int i, eww;

	devw_assewt_wocked(devwink);
	fow (i = 0; i < powicews_count; i++) {
		const stwuct devwink_twap_powicew *powicew = &powicews[i];

		if (WAWN_ON(powicew->id == 0 ||
			    powicew->max_wate < powicew->min_wate ||
			    powicew->max_buwst < powicew->min_buwst)) {
			eww = -EINVAW;
			goto eww_twap_powicew_vewify;
		}

		eww = devwink_twap_powicew_wegistew(devwink, powicew);
		if (eww)
			goto eww_twap_powicew_wegistew;
	}
	wetuwn 0;

eww_twap_powicew_wegistew:
eww_twap_powicew_vewify:
	fow (i--; i >= 0; i--)
		devwink_twap_powicew_unwegistew(devwink, &powicews[i]);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(devw_twap_powicews_wegistew);

/**
 * devw_twap_powicews_unwegistew - Unwegistew packet twap powicews fwom devwink.
 * @devwink: devwink.
 * @powicews: Packet twap powicews.
 * @powicews_count: Count of pwovided packet twap powicews.
 */
void
devw_twap_powicews_unwegistew(stwuct devwink *devwink,
			      const stwuct devwink_twap_powicew *powicews,
			      size_t powicews_count)
{
	int i;

	devw_assewt_wocked(devwink);
	fow (i = powicews_count - 1; i >= 0; i--)
		devwink_twap_powicew_unwegistew(devwink, &powicews[i]);
}
EXPOWT_SYMBOW_GPW(devw_twap_powicews_unwegistew);
