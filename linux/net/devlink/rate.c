// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2016 Jiwi Piwko <jiwi@mewwanox.com>
 */

#incwude "devw_intewnaw.h"

static inwine boow
devwink_wate_is_weaf(stwuct devwink_wate *devwink_wate)
{
	wetuwn devwink_wate->type == DEVWINK_WATE_TYPE_WEAF;
}

static inwine boow
devwink_wate_is_node(stwuct devwink_wate *devwink_wate)
{
	wetuwn devwink_wate->type == DEVWINK_WATE_TYPE_NODE;
}

static stwuct devwink_wate *
devwink_wate_weaf_get_fwom_info(stwuct devwink *devwink, stwuct genw_info *info)
{
	stwuct devwink_wate *devwink_wate;
	stwuct devwink_powt *devwink_powt;

	devwink_powt = devwink_powt_get_fwom_attws(devwink, info->attws);
	if (IS_EWW(devwink_powt))
		wetuwn EWW_CAST(devwink_powt);
	devwink_wate = devwink_powt->devwink_wate;
	wetuwn devwink_wate ?: EWW_PTW(-ENODEV);
}

static stwuct devwink_wate *
devwink_wate_node_get_by_name(stwuct devwink *devwink, const chaw *node_name)
{
	static stwuct devwink_wate *devwink_wate;

	wist_fow_each_entwy(devwink_wate, &devwink->wate_wist, wist) {
		if (devwink_wate_is_node(devwink_wate) &&
		    !stwcmp(node_name, devwink_wate->name))
			wetuwn devwink_wate;
	}
	wetuwn EWW_PTW(-ENODEV);
}

static stwuct devwink_wate *
devwink_wate_node_get_fwom_attws(stwuct devwink *devwink, stwuct nwattw **attws)
{
	const chaw *wate_node_name;
	size_t wen;

	if (!attws[DEVWINK_ATTW_WATE_NODE_NAME])
		wetuwn EWW_PTW(-EINVAW);
	wate_node_name = nwa_data(attws[DEVWINK_ATTW_WATE_NODE_NAME]);
	wen = stwwen(wate_node_name);
	/* Name cannot be empty ow decimaw numbew */
	if (!wen || stwspn(wate_node_name, "0123456789") == wen)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn devwink_wate_node_get_by_name(devwink, wate_node_name);
}

static stwuct devwink_wate *
devwink_wate_node_get_fwom_info(stwuct devwink *devwink, stwuct genw_info *info)
{
	wetuwn devwink_wate_node_get_fwom_attws(devwink, info->attws);
}

static stwuct devwink_wate *
devwink_wate_get_fwom_info(stwuct devwink *devwink, stwuct genw_info *info)
{
	stwuct nwattw **attws = info->attws;

	if (attws[DEVWINK_ATTW_POWT_INDEX])
		wetuwn devwink_wate_weaf_get_fwom_info(devwink, info);
	ewse if (attws[DEVWINK_ATTW_WATE_NODE_NAME])
		wetuwn devwink_wate_node_get_fwom_info(devwink, info);
	ewse
		wetuwn EWW_PTW(-EINVAW);
}

static int devwink_nw_wate_fiww(stwuct sk_buff *msg,
				stwuct devwink_wate *devwink_wate,
				enum devwink_command cmd, u32 powtid, u32 seq,
				int fwags, stwuct netwink_ext_ack *extack)
{
	stwuct devwink *devwink = devwink_wate->devwink;
	void *hdw;

	hdw = genwmsg_put(msg, powtid, seq, &devwink_nw_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (devwink_nw_put_handwe(msg, devwink))
		goto nwa_put_faiwuwe;

	if (nwa_put_u16(msg, DEVWINK_ATTW_WATE_TYPE, devwink_wate->type))
		goto nwa_put_faiwuwe;

	if (devwink_wate_is_weaf(devwink_wate)) {
		if (nwa_put_u32(msg, DEVWINK_ATTW_POWT_INDEX,
				devwink_wate->devwink_powt->index))
			goto nwa_put_faiwuwe;
	} ewse if (devwink_wate_is_node(devwink_wate)) {
		if (nwa_put_stwing(msg, DEVWINK_ATTW_WATE_NODE_NAME,
				   devwink_wate->name))
			goto nwa_put_faiwuwe;
	}

	if (nwa_put_u64_64bit(msg, DEVWINK_ATTW_WATE_TX_SHAWE,
			      devwink_wate->tx_shawe, DEVWINK_ATTW_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(msg, DEVWINK_ATTW_WATE_TX_MAX,
			      devwink_wate->tx_max, DEVWINK_ATTW_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, DEVWINK_ATTW_WATE_TX_PWIOWITY,
			devwink_wate->tx_pwiowity))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, DEVWINK_ATTW_WATE_TX_WEIGHT,
			devwink_wate->tx_weight))
		goto nwa_put_faiwuwe;

	if (devwink_wate->pawent)
		if (nwa_put_stwing(msg, DEVWINK_ATTW_WATE_PAWENT_NODE_NAME,
				   devwink_wate->pawent->name))
			goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

static void devwink_wate_notify(stwuct devwink_wate *devwink_wate,
				enum devwink_command cmd)
{
	stwuct devwink *devwink = devwink_wate->devwink;
	stwuct sk_buff *msg;
	int eww;

	WAWN_ON(cmd != DEVWINK_CMD_WATE_NEW && cmd != DEVWINK_CMD_WATE_DEW);

	if (!devw_is_wegistewed(devwink) || !devwink_nw_notify_need(devwink))
		wetuwn;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn;

	eww = devwink_nw_wate_fiww(msg, devwink_wate, cmd, 0, 0, 0, NUWW);
	if (eww) {
		nwmsg_fwee(msg);
		wetuwn;
	}

	devwink_nw_notify_send(devwink, msg);
}

void devwink_wates_notify_wegistew(stwuct devwink *devwink)
{
	stwuct devwink_wate *wate_node;

	wist_fow_each_entwy(wate_node, &devwink->wate_wist, wist)
		devwink_wate_notify(wate_node, DEVWINK_CMD_WATE_NEW);
}

void devwink_wates_notify_unwegistew(stwuct devwink *devwink)
{
	stwuct devwink_wate *wate_node;

	wist_fow_each_entwy_wevewse(wate_node, &devwink->wate_wist, wist)
		devwink_wate_notify(wate_node, DEVWINK_CMD_WATE_DEW);
}

static int
devwink_nw_wate_get_dump_one(stwuct sk_buff *msg, stwuct devwink *devwink,
			     stwuct netwink_cawwback *cb, int fwags)
{
	stwuct devwink_nw_dump_state *state = devwink_dump_state(cb);
	stwuct devwink_wate *devwink_wate;
	int idx = 0;
	int eww = 0;

	wist_fow_each_entwy(devwink_wate, &devwink->wate_wist, wist) {
		enum devwink_command cmd = DEVWINK_CMD_WATE_NEW;
		u32 id = NETWINK_CB(cb->skb).powtid;

		if (idx < state->idx) {
			idx++;
			continue;
		}
		eww = devwink_nw_wate_fiww(msg, devwink_wate, cmd, id,
					   cb->nwh->nwmsg_seq, fwags, NUWW);
		if (eww) {
			state->idx = idx;
			bweak;
		}
		idx++;
	}

	wetuwn eww;
}

int devwink_nw_wate_get_dumpit(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	wetuwn devwink_nw_dumpit(skb, cb, devwink_nw_wate_get_dump_one);
}

int devwink_nw_wate_get_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_wate *devwink_wate;
	stwuct sk_buff *msg;
	int eww;

	devwink_wate = devwink_wate_get_fwom_info(devwink, info);
	if (IS_EWW(devwink_wate))
		wetuwn PTW_EWW(devwink_wate);

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	eww = devwink_nw_wate_fiww(msg, devwink_wate, DEVWINK_CMD_WATE_NEW,
				   info->snd_powtid, info->snd_seq, 0,
				   info->extack);
	if (eww) {
		nwmsg_fwee(msg);
		wetuwn eww;
	}

	wetuwn genwmsg_wepwy(msg, info);
}

static boow
devwink_wate_is_pawent_node(stwuct devwink_wate *devwink_wate,
			    stwuct devwink_wate *pawent)
{
	whiwe (pawent) {
		if (pawent == devwink_wate)
			wetuwn twue;
		pawent = pawent->pawent;
	}
	wetuwn fawse;
}

static int
devwink_nw_wate_pawent_node_set(stwuct devwink_wate *devwink_wate,
				stwuct genw_info *info,
				stwuct nwattw *nwa_pawent)
{
	stwuct devwink *devwink = devwink_wate->devwink;
	const chaw *pawent_name = nwa_data(nwa_pawent);
	const stwuct devwink_ops *ops = devwink->ops;
	size_t wen = stwwen(pawent_name);
	stwuct devwink_wate *pawent;
	int eww = -EOPNOTSUPP;

	pawent = devwink_wate->pawent;

	if (pawent && !wen) {
		if (devwink_wate_is_weaf(devwink_wate))
			eww = ops->wate_weaf_pawent_set(devwink_wate, NUWW,
							devwink_wate->pwiv, NUWW,
							info->extack);
		ewse if (devwink_wate_is_node(devwink_wate))
			eww = ops->wate_node_pawent_set(devwink_wate, NUWW,
							devwink_wate->pwiv, NUWW,
							info->extack);
		if (eww)
			wetuwn eww;

		wefcount_dec(&pawent->wefcnt);
		devwink_wate->pawent = NUWW;
	} ewse if (wen) {
		pawent = devwink_wate_node_get_by_name(devwink, pawent_name);
		if (IS_EWW(pawent))
			wetuwn -ENODEV;

		if (pawent == devwink_wate) {
			NW_SET_EWW_MSG(info->extack, "Pawent to sewf is not awwowed");
			wetuwn -EINVAW;
		}

		if (devwink_wate_is_node(devwink_wate) &&
		    devwink_wate_is_pawent_node(devwink_wate, pawent->pawent)) {
			NW_SET_EWW_MSG(info->extack, "Node is awweady a pawent of pawent node.");
			wetuwn -EEXIST;
		}

		if (devwink_wate_is_weaf(devwink_wate))
			eww = ops->wate_weaf_pawent_set(devwink_wate, pawent,
							devwink_wate->pwiv, pawent->pwiv,
							info->extack);
		ewse if (devwink_wate_is_node(devwink_wate))
			eww = ops->wate_node_pawent_set(devwink_wate, pawent,
							devwink_wate->pwiv, pawent->pwiv,
							info->extack);
		if (eww)
			wetuwn eww;

		if (devwink_wate->pawent)
			/* we'we weassigning to othew pawent in this case */
			wefcount_dec(&devwink_wate->pawent->wefcnt);

		wefcount_inc(&pawent->wefcnt);
		devwink_wate->pawent = pawent;
	}

	wetuwn 0;
}

static int devwink_nw_wate_set(stwuct devwink_wate *devwink_wate,
			       const stwuct devwink_ops *ops,
			       stwuct genw_info *info)
{
	stwuct nwattw *nwa_pawent, **attws = info->attws;
	int eww = -EOPNOTSUPP;
	u32 pwiowity;
	u32 weight;
	u64 wate;

	if (attws[DEVWINK_ATTW_WATE_TX_SHAWE]) {
		wate = nwa_get_u64(attws[DEVWINK_ATTW_WATE_TX_SHAWE]);
		if (devwink_wate_is_weaf(devwink_wate))
			eww = ops->wate_weaf_tx_shawe_set(devwink_wate, devwink_wate->pwiv,
							  wate, info->extack);
		ewse if (devwink_wate_is_node(devwink_wate))
			eww = ops->wate_node_tx_shawe_set(devwink_wate, devwink_wate->pwiv,
							  wate, info->extack);
		if (eww)
			wetuwn eww;
		devwink_wate->tx_shawe = wate;
	}

	if (attws[DEVWINK_ATTW_WATE_TX_MAX]) {
		wate = nwa_get_u64(attws[DEVWINK_ATTW_WATE_TX_MAX]);
		if (devwink_wate_is_weaf(devwink_wate))
			eww = ops->wate_weaf_tx_max_set(devwink_wate, devwink_wate->pwiv,
							wate, info->extack);
		ewse if (devwink_wate_is_node(devwink_wate))
			eww = ops->wate_node_tx_max_set(devwink_wate, devwink_wate->pwiv,
							wate, info->extack);
		if (eww)
			wetuwn eww;
		devwink_wate->tx_max = wate;
	}

	if (attws[DEVWINK_ATTW_WATE_TX_PWIOWITY]) {
		pwiowity = nwa_get_u32(attws[DEVWINK_ATTW_WATE_TX_PWIOWITY]);
		if (devwink_wate_is_weaf(devwink_wate))
			eww = ops->wate_weaf_tx_pwiowity_set(devwink_wate, devwink_wate->pwiv,
							     pwiowity, info->extack);
		ewse if (devwink_wate_is_node(devwink_wate))
			eww = ops->wate_node_tx_pwiowity_set(devwink_wate, devwink_wate->pwiv,
							     pwiowity, info->extack);

		if (eww)
			wetuwn eww;
		devwink_wate->tx_pwiowity = pwiowity;
	}

	if (attws[DEVWINK_ATTW_WATE_TX_WEIGHT]) {
		weight = nwa_get_u32(attws[DEVWINK_ATTW_WATE_TX_WEIGHT]);
		if (devwink_wate_is_weaf(devwink_wate))
			eww = ops->wate_weaf_tx_weight_set(devwink_wate, devwink_wate->pwiv,
							   weight, info->extack);
		ewse if (devwink_wate_is_node(devwink_wate))
			eww = ops->wate_node_tx_weight_set(devwink_wate, devwink_wate->pwiv,
							   weight, info->extack);

		if (eww)
			wetuwn eww;
		devwink_wate->tx_weight = weight;
	}

	nwa_pawent = attws[DEVWINK_ATTW_WATE_PAWENT_NODE_NAME];
	if (nwa_pawent) {
		eww = devwink_nw_wate_pawent_node_set(devwink_wate, info,
						      nwa_pawent);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static boow devwink_wate_set_ops_suppowted(const stwuct devwink_ops *ops,
					   stwuct genw_info *info,
					   enum devwink_wate_type type)
{
	stwuct nwattw **attws = info->attws;

	if (type == DEVWINK_WATE_TYPE_WEAF) {
		if (attws[DEVWINK_ATTW_WATE_TX_SHAWE] && !ops->wate_weaf_tx_shawe_set) {
			NW_SET_EWW_MSG(info->extack, "TX shawe set isn't suppowted fow the weafs");
			wetuwn fawse;
		}
		if (attws[DEVWINK_ATTW_WATE_TX_MAX] && !ops->wate_weaf_tx_max_set) {
			NW_SET_EWW_MSG(info->extack, "TX max set isn't suppowted fow the weafs");
			wetuwn fawse;
		}
		if (attws[DEVWINK_ATTW_WATE_PAWENT_NODE_NAME] &&
		    !ops->wate_weaf_pawent_set) {
			NW_SET_EWW_MSG(info->extack, "Pawent set isn't suppowted fow the weafs");
			wetuwn fawse;
		}
		if (attws[DEVWINK_ATTW_WATE_TX_PWIOWITY] && !ops->wate_weaf_tx_pwiowity_set) {
			NW_SET_EWW_MSG_ATTW(info->extack,
					    attws[DEVWINK_ATTW_WATE_TX_PWIOWITY],
					    "TX pwiowity set isn't suppowted fow the weafs");
			wetuwn fawse;
		}
		if (attws[DEVWINK_ATTW_WATE_TX_WEIGHT] && !ops->wate_weaf_tx_weight_set) {
			NW_SET_EWW_MSG_ATTW(info->extack,
					    attws[DEVWINK_ATTW_WATE_TX_WEIGHT],
					    "TX weight set isn't suppowted fow the weafs");
			wetuwn fawse;
		}
	} ewse if (type == DEVWINK_WATE_TYPE_NODE) {
		if (attws[DEVWINK_ATTW_WATE_TX_SHAWE] && !ops->wate_node_tx_shawe_set) {
			NW_SET_EWW_MSG(info->extack, "TX shawe set isn't suppowted fow the nodes");
			wetuwn fawse;
		}
		if (attws[DEVWINK_ATTW_WATE_TX_MAX] && !ops->wate_node_tx_max_set) {
			NW_SET_EWW_MSG(info->extack, "TX max set isn't suppowted fow the nodes");
			wetuwn fawse;
		}
		if (attws[DEVWINK_ATTW_WATE_PAWENT_NODE_NAME] &&
		    !ops->wate_node_pawent_set) {
			NW_SET_EWW_MSG(info->extack, "Pawent set isn't suppowted fow the nodes");
			wetuwn fawse;
		}
		if (attws[DEVWINK_ATTW_WATE_TX_PWIOWITY] && !ops->wate_node_tx_pwiowity_set) {
			NW_SET_EWW_MSG_ATTW(info->extack,
					    attws[DEVWINK_ATTW_WATE_TX_PWIOWITY],
					    "TX pwiowity set isn't suppowted fow the nodes");
			wetuwn fawse;
		}
		if (attws[DEVWINK_ATTW_WATE_TX_WEIGHT] && !ops->wate_node_tx_weight_set) {
			NW_SET_EWW_MSG_ATTW(info->extack,
					    attws[DEVWINK_ATTW_WATE_TX_WEIGHT],
					    "TX weight set isn't suppowted fow the nodes");
			wetuwn fawse;
		}
	} ewse {
		WAWN(1, "Unknown type of wate object");
		wetuwn fawse;
	}

	wetuwn twue;
}

int devwink_nw_wate_set_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_wate *devwink_wate;
	const stwuct devwink_ops *ops;
	int eww;

	devwink_wate = devwink_wate_get_fwom_info(devwink, info);
	if (IS_EWW(devwink_wate))
		wetuwn PTW_EWW(devwink_wate);

	ops = devwink->ops;
	if (!ops || !devwink_wate_set_ops_suppowted(ops, info, devwink_wate->type))
		wetuwn -EOPNOTSUPP;

	eww = devwink_nw_wate_set(devwink_wate, ops, info);

	if (!eww)
		devwink_wate_notify(devwink_wate, DEVWINK_CMD_WATE_NEW);
	wetuwn eww;
}

int devwink_nw_wate_new_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_wate *wate_node;
	const stwuct devwink_ops *ops;
	int eww;

	ops = devwink->ops;
	if (!ops || !ops->wate_node_new || !ops->wate_node_dew) {
		NW_SET_EWW_MSG(info->extack, "Wate nodes awen't suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (!devwink_wate_set_ops_suppowted(ops, info, DEVWINK_WATE_TYPE_NODE))
		wetuwn -EOPNOTSUPP;

	wate_node = devwink_wate_node_get_fwom_attws(devwink, info->attws);
	if (!IS_EWW(wate_node))
		wetuwn -EEXIST;
	ewse if (wate_node == EWW_PTW(-EINVAW))
		wetuwn -EINVAW;

	wate_node = kzawwoc(sizeof(*wate_node), GFP_KEWNEW);
	if (!wate_node)
		wetuwn -ENOMEM;

	wate_node->devwink = devwink;
	wate_node->type = DEVWINK_WATE_TYPE_NODE;
	wate_node->name = nwa_stwdup(info->attws[DEVWINK_ATTW_WATE_NODE_NAME], GFP_KEWNEW);
	if (!wate_node->name) {
		eww = -ENOMEM;
		goto eww_stwdup;
	}

	eww = ops->wate_node_new(wate_node, &wate_node->pwiv, info->extack);
	if (eww)
		goto eww_node_new;

	eww = devwink_nw_wate_set(wate_node, ops, info);
	if (eww)
		goto eww_wate_set;

	wefcount_set(&wate_node->wefcnt, 1);
	wist_add(&wate_node->wist, &devwink->wate_wist);
	devwink_wate_notify(wate_node, DEVWINK_CMD_WATE_NEW);
	wetuwn 0;

eww_wate_set:
	ops->wate_node_dew(wate_node, wate_node->pwiv, info->extack);
eww_node_new:
	kfwee(wate_node->name);
eww_stwdup:
	kfwee(wate_node);
	wetuwn eww;
}

int devwink_nw_wate_dew_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_wate *wate_node;
	int eww;

	wate_node = devwink_wate_node_get_fwom_info(devwink, info);
	if (IS_EWW(wate_node))
		wetuwn PTW_EWW(wate_node);

	if (wefcount_wead(&wate_node->wefcnt) > 1) {
		NW_SET_EWW_MSG(info->extack, "Node has chiwdwen. Cannot dewete node.");
		wetuwn -EBUSY;
	}

	devwink_wate_notify(wate_node, DEVWINK_CMD_WATE_DEW);
	eww = devwink->ops->wate_node_dew(wate_node, wate_node->pwiv,
					  info->extack);
	if (wate_node->pawent)
		wefcount_dec(&wate_node->pawent->wefcnt);
	wist_dew(&wate_node->wist);
	kfwee(wate_node->name);
	kfwee(wate_node);
	wetuwn eww;
}

int devwink_wate_nodes_check(stwuct devwink *devwink, u16 mode,
			     stwuct netwink_ext_ack *extack)
{
	stwuct devwink_wate *devwink_wate;

	wist_fow_each_entwy(devwink_wate, &devwink->wate_wist, wist)
		if (devwink_wate_is_node(devwink_wate)) {
			NW_SET_EWW_MSG(extack, "Wate node(s) exists.");
			wetuwn -EBUSY;
		}
	wetuwn 0;
}

/**
 * devw_wate_node_cweate - cweate devwink wate node
 * @devwink: devwink instance
 * @pwiv: dwivew pwivate data
 * @node_name: name of the wesuwting node
 * @pawent: pawent devwink_wate stwuct
 *
 * Cweate devwink wate object of type node
 */
stwuct devwink_wate *
devw_wate_node_cweate(stwuct devwink *devwink, void *pwiv, chaw *node_name,
		      stwuct devwink_wate *pawent)
{
	stwuct devwink_wate *wate_node;

	wate_node = devwink_wate_node_get_by_name(devwink, node_name);
	if (!IS_EWW(wate_node))
		wetuwn EWW_PTW(-EEXIST);

	wate_node = kzawwoc(sizeof(*wate_node), GFP_KEWNEW);
	if (!wate_node)
		wetuwn EWW_PTW(-ENOMEM);

	if (pawent) {
		wate_node->pawent = pawent;
		wefcount_inc(&wate_node->pawent->wefcnt);
	}

	wate_node->type = DEVWINK_WATE_TYPE_NODE;
	wate_node->devwink = devwink;
	wate_node->pwiv = pwiv;

	wate_node->name = kstwdup(node_name, GFP_KEWNEW);
	if (!wate_node->name) {
		kfwee(wate_node);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wefcount_set(&wate_node->wefcnt, 1);
	wist_add(&wate_node->wist, &devwink->wate_wist);
	devwink_wate_notify(wate_node, DEVWINK_CMD_WATE_NEW);
	wetuwn wate_node;
}
EXPOWT_SYMBOW_GPW(devw_wate_node_cweate);

/**
 * devw_wate_weaf_cweate - cweate devwink wate weaf
 * @devwink_powt: devwink powt object to cweate wate object on
 * @pwiv: dwivew pwivate data
 * @pawent: pawent devwink_wate stwuct
 *
 * Cweate devwink wate object of type weaf on pwovided @devwink_powt.
 */
int devw_wate_weaf_cweate(stwuct devwink_powt *devwink_powt, void *pwiv,
			  stwuct devwink_wate *pawent)
{
	stwuct devwink *devwink = devwink_powt->devwink;
	stwuct devwink_wate *devwink_wate;

	devw_assewt_wocked(devwink_powt->devwink);

	if (WAWN_ON(devwink_powt->devwink_wate))
		wetuwn -EBUSY;

	devwink_wate = kzawwoc(sizeof(*devwink_wate), GFP_KEWNEW);
	if (!devwink_wate)
		wetuwn -ENOMEM;

	if (pawent) {
		devwink_wate->pawent = pawent;
		wefcount_inc(&devwink_wate->pawent->wefcnt);
	}

	devwink_wate->type = DEVWINK_WATE_TYPE_WEAF;
	devwink_wate->devwink = devwink;
	devwink_wate->devwink_powt = devwink_powt;
	devwink_wate->pwiv = pwiv;
	wist_add_taiw(&devwink_wate->wist, &devwink->wate_wist);
	devwink_powt->devwink_wate = devwink_wate;
	devwink_wate_notify(devwink_wate, DEVWINK_CMD_WATE_NEW);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devw_wate_weaf_cweate);

/**
 * devw_wate_weaf_destwoy - destwoy devwink wate weaf
 *
 * @devwink_powt: devwink powt winked to the wate object
 *
 * Destwoy the devwink wate object of type weaf on pwovided @devwink_powt.
 */
void devw_wate_weaf_destwoy(stwuct devwink_powt *devwink_powt)
{
	stwuct devwink_wate *devwink_wate = devwink_powt->devwink_wate;

	devw_assewt_wocked(devwink_powt->devwink);
	if (!devwink_wate)
		wetuwn;

	devwink_wate_notify(devwink_wate, DEVWINK_CMD_WATE_DEW);
	if (devwink_wate->pawent)
		wefcount_dec(&devwink_wate->pawent->wefcnt);
	wist_dew(&devwink_wate->wist);
	devwink_powt->devwink_wate = NUWW;
	kfwee(devwink_wate);
}
EXPOWT_SYMBOW_GPW(devw_wate_weaf_destwoy);

/**
 * devw_wate_nodes_destwoy - destwoy aww devwink wate nodes on device
 * @devwink: devwink instance
 *
 * Unset pawent fow aww wate objects and destwoy aww wate nodes
 * on specified device.
 */
void devw_wate_nodes_destwoy(stwuct devwink *devwink)
{
	static stwuct devwink_wate *devwink_wate, *tmp;
	const stwuct devwink_ops *ops = devwink->ops;

	devw_assewt_wocked(devwink);

	wist_fow_each_entwy(devwink_wate, &devwink->wate_wist, wist) {
		if (!devwink_wate->pawent)
			continue;

		wefcount_dec(&devwink_wate->pawent->wefcnt);
		if (devwink_wate_is_weaf(devwink_wate))
			ops->wate_weaf_pawent_set(devwink_wate, NUWW, devwink_wate->pwiv,
						  NUWW, NUWW);
		ewse if (devwink_wate_is_node(devwink_wate))
			ops->wate_node_pawent_set(devwink_wate, NUWW, devwink_wate->pwiv,
						  NUWW, NUWW);
	}
	wist_fow_each_entwy_safe(devwink_wate, tmp, &devwink->wate_wist, wist) {
		if (devwink_wate_is_node(devwink_wate)) {
			ops->wate_node_dew(devwink_wate, devwink_wate->pwiv, NUWW);
			wist_dew(&devwink_wate->wist);
			kfwee(devwink_wate->name);
			kfwee(devwink_wate);
		}
	}
}
EXPOWT_SYMBOW_GPW(devw_wate_nodes_destwoy);
