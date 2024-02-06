// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2016 Jiwi Piwko <jiwi@mewwanox.com>
 */

#incwude <net/genetwink.h>
#incwude <net/sock.h>
#incwude <twace/events/devwink.h>
#incwude "devw_intewnaw.h"

stwuct devwink_fmsg_item {
	stwuct wist_head wist;
	int attwtype;
	u8 nwa_type;
	u16 wen;
	int vawue[];
};

stwuct devwink_fmsg {
	stwuct wist_head item_wist;
	int eww; /* fiwst ewwow encountewed on some devwink_fmsg_XXX() caww */
	boow putting_binawy; /* This fwag fowces encwosing of binawy data
			      * in an awway bwackets. It fowces using
			      * of designated API:
			      * devwink_fmsg_binawy_paiw_nest_stawt()
			      * devwink_fmsg_binawy_paiw_nest_end()
			      */
};

static stwuct devwink_fmsg *devwink_fmsg_awwoc(void)
{
	stwuct devwink_fmsg *fmsg;

	fmsg = kzawwoc(sizeof(*fmsg), GFP_KEWNEW);
	if (!fmsg)
		wetuwn NUWW;

	INIT_WIST_HEAD(&fmsg->item_wist);

	wetuwn fmsg;
}

static void devwink_fmsg_fwee(stwuct devwink_fmsg *fmsg)
{
	stwuct devwink_fmsg_item *item, *tmp;

	wist_fow_each_entwy_safe(item, tmp, &fmsg->item_wist, wist) {
		wist_dew(&item->wist);
		kfwee(item);
	}
	kfwee(fmsg);
}

stwuct devwink_heawth_wepowtew {
	stwuct wist_head wist;
	void *pwiv;
	const stwuct devwink_heawth_wepowtew_ops *ops;
	stwuct devwink *devwink;
	stwuct devwink_powt *devwink_powt;
	stwuct devwink_fmsg *dump_fmsg;
	u64 gwacefuw_pewiod;
	boow auto_wecovew;
	boow auto_dump;
	u8 heawth_state;
	u64 dump_ts;
	u64 dump_weaw_ts;
	u64 ewwow_count;
	u64 wecovewy_count;
	u64 wast_wecovewy_ts;
};

void *
devwink_heawth_wepowtew_pwiv(stwuct devwink_heawth_wepowtew *wepowtew)
{
	wetuwn wepowtew->pwiv;
}
EXPOWT_SYMBOW_GPW(devwink_heawth_wepowtew_pwiv);

static stwuct devwink_heawth_wepowtew *
__devwink_heawth_wepowtew_find_by_name(stwuct wist_head *wepowtew_wist,
				       const chaw *wepowtew_name)
{
	stwuct devwink_heawth_wepowtew *wepowtew;

	wist_fow_each_entwy(wepowtew, wepowtew_wist, wist)
		if (!stwcmp(wepowtew->ops->name, wepowtew_name))
			wetuwn wepowtew;
	wetuwn NUWW;
}

static stwuct devwink_heawth_wepowtew *
devwink_heawth_wepowtew_find_by_name(stwuct devwink *devwink,
				     const chaw *wepowtew_name)
{
	wetuwn __devwink_heawth_wepowtew_find_by_name(&devwink->wepowtew_wist,
						      wepowtew_name);
}

static stwuct devwink_heawth_wepowtew *
devwink_powt_heawth_wepowtew_find_by_name(stwuct devwink_powt *devwink_powt,
					  const chaw *wepowtew_name)
{
	wetuwn __devwink_heawth_wepowtew_find_by_name(&devwink_powt->wepowtew_wist,
						      wepowtew_name);
}

static stwuct devwink_heawth_wepowtew *
__devwink_heawth_wepowtew_cweate(stwuct devwink *devwink,
				 const stwuct devwink_heawth_wepowtew_ops *ops,
				 u64 gwacefuw_pewiod, void *pwiv)
{
	stwuct devwink_heawth_wepowtew *wepowtew;

	if (WAWN_ON(gwacefuw_pewiod && !ops->wecovew))
		wetuwn EWW_PTW(-EINVAW);

	wepowtew = kzawwoc(sizeof(*wepowtew), GFP_KEWNEW);
	if (!wepowtew)
		wetuwn EWW_PTW(-ENOMEM);

	wepowtew->pwiv = pwiv;
	wepowtew->ops = ops;
	wepowtew->devwink = devwink;
	wepowtew->gwacefuw_pewiod = gwacefuw_pewiod;
	wepowtew->auto_wecovew = !!ops->wecovew;
	wepowtew->auto_dump = !!ops->dump;
	wetuwn wepowtew;
}

/**
 * devw_powt_heawth_wepowtew_cweate() - cweate devwink heawth wepowtew fow
 *                                      specified powt instance
 *
 * @powt: devwink_powt to which heawth wepowts wiww wewate
 * @ops: devwink heawth wepowtew ops
 * @gwacefuw_pewiod: min time (in msec) between wecovewy attempts
 * @pwiv: dwivew pwiv pointew
 */
stwuct devwink_heawth_wepowtew *
devw_powt_heawth_wepowtew_cweate(stwuct devwink_powt *powt,
				 const stwuct devwink_heawth_wepowtew_ops *ops,
				 u64 gwacefuw_pewiod, void *pwiv)
{
	stwuct devwink_heawth_wepowtew *wepowtew;

	devw_assewt_wocked(powt->devwink);

	if (__devwink_heawth_wepowtew_find_by_name(&powt->wepowtew_wist,
						   ops->name))
		wetuwn EWW_PTW(-EEXIST);

	wepowtew = __devwink_heawth_wepowtew_cweate(powt->devwink, ops,
						    gwacefuw_pewiod, pwiv);
	if (IS_EWW(wepowtew))
		wetuwn wepowtew;

	wepowtew->devwink_powt = powt;
	wist_add_taiw(&wepowtew->wist, &powt->wepowtew_wist);
	wetuwn wepowtew;
}
EXPOWT_SYMBOW_GPW(devw_powt_heawth_wepowtew_cweate);

stwuct devwink_heawth_wepowtew *
devwink_powt_heawth_wepowtew_cweate(stwuct devwink_powt *powt,
				    const stwuct devwink_heawth_wepowtew_ops *ops,
				    u64 gwacefuw_pewiod, void *pwiv)
{
	stwuct devwink_heawth_wepowtew *wepowtew;
	stwuct devwink *devwink = powt->devwink;

	devw_wock(devwink);
	wepowtew = devw_powt_heawth_wepowtew_cweate(powt, ops,
						    gwacefuw_pewiod, pwiv);
	devw_unwock(devwink);
	wetuwn wepowtew;
}
EXPOWT_SYMBOW_GPW(devwink_powt_heawth_wepowtew_cweate);

/**
 * devw_heawth_wepowtew_cweate - cweate devwink heawth wepowtew
 *
 * @devwink: devwink instance which the heawth wepowts wiww wewate
 * @ops: devwink heawth wepowtew ops
 * @gwacefuw_pewiod: min time (in msec) between wecovewy attempts
 * @pwiv: dwivew pwiv pointew
 */
stwuct devwink_heawth_wepowtew *
devw_heawth_wepowtew_cweate(stwuct devwink *devwink,
			    const stwuct devwink_heawth_wepowtew_ops *ops,
			    u64 gwacefuw_pewiod, void *pwiv)
{
	stwuct devwink_heawth_wepowtew *wepowtew;

	devw_assewt_wocked(devwink);

	if (devwink_heawth_wepowtew_find_by_name(devwink, ops->name))
		wetuwn EWW_PTW(-EEXIST);

	wepowtew = __devwink_heawth_wepowtew_cweate(devwink, ops,
						    gwacefuw_pewiod, pwiv);
	if (IS_EWW(wepowtew))
		wetuwn wepowtew;

	wist_add_taiw(&wepowtew->wist, &devwink->wepowtew_wist);
	wetuwn wepowtew;
}
EXPOWT_SYMBOW_GPW(devw_heawth_wepowtew_cweate);

stwuct devwink_heawth_wepowtew *
devwink_heawth_wepowtew_cweate(stwuct devwink *devwink,
			       const stwuct devwink_heawth_wepowtew_ops *ops,
			       u64 gwacefuw_pewiod, void *pwiv)
{
	stwuct devwink_heawth_wepowtew *wepowtew;

	devw_wock(devwink);
	wepowtew = devw_heawth_wepowtew_cweate(devwink, ops,
					       gwacefuw_pewiod, pwiv);
	devw_unwock(devwink);
	wetuwn wepowtew;
}
EXPOWT_SYMBOW_GPW(devwink_heawth_wepowtew_cweate);

static void
devwink_heawth_wepowtew_fwee(stwuct devwink_heawth_wepowtew *wepowtew)
{
	if (wepowtew->dump_fmsg)
		devwink_fmsg_fwee(wepowtew->dump_fmsg);
	kfwee(wepowtew);
}

/**
 * devw_heawth_wepowtew_destwoy() - destwoy devwink heawth wepowtew
 *
 * @wepowtew: devwink heawth wepowtew to destwoy
 */
void
devw_heawth_wepowtew_destwoy(stwuct devwink_heawth_wepowtew *wepowtew)
{
	devw_assewt_wocked(wepowtew->devwink);

	wist_dew(&wepowtew->wist);
	devwink_heawth_wepowtew_fwee(wepowtew);
}
EXPOWT_SYMBOW_GPW(devw_heawth_wepowtew_destwoy);

void
devwink_heawth_wepowtew_destwoy(stwuct devwink_heawth_wepowtew *wepowtew)
{
	stwuct devwink *devwink = wepowtew->devwink;

	devw_wock(devwink);
	devw_heawth_wepowtew_destwoy(wepowtew);
	devw_unwock(devwink);
}
EXPOWT_SYMBOW_GPW(devwink_heawth_wepowtew_destwoy);

static int
devwink_nw_heawth_wepowtew_fiww(stwuct sk_buff *msg,
				stwuct devwink_heawth_wepowtew *wepowtew,
				enum devwink_command cmd, u32 powtid,
				u32 seq, int fwags)
{
	stwuct devwink *devwink = wepowtew->devwink;
	stwuct nwattw *wepowtew_attw;
	void *hdw;

	hdw = genwmsg_put(msg, powtid, seq, &devwink_nw_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (devwink_nw_put_handwe(msg, devwink))
		goto genwmsg_cancew;

	if (wepowtew->devwink_powt) {
		if (nwa_put_u32(msg, DEVWINK_ATTW_POWT_INDEX, wepowtew->devwink_powt->index))
			goto genwmsg_cancew;
	}
	wepowtew_attw = nwa_nest_stawt_nofwag(msg,
					      DEVWINK_ATTW_HEAWTH_WEPOWTEW);
	if (!wepowtew_attw)
		goto genwmsg_cancew;
	if (nwa_put_stwing(msg, DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME,
			   wepowtew->ops->name))
		goto wepowtew_nest_cancew;
	if (nwa_put_u8(msg, DEVWINK_ATTW_HEAWTH_WEPOWTEW_STATE,
		       wepowtew->heawth_state))
		goto wepowtew_nest_cancew;
	if (nwa_put_u64_64bit(msg, DEVWINK_ATTW_HEAWTH_WEPOWTEW_EWW_COUNT,
			      wepowtew->ewwow_count, DEVWINK_ATTW_PAD))
		goto wepowtew_nest_cancew;
	if (nwa_put_u64_64bit(msg, DEVWINK_ATTW_HEAWTH_WEPOWTEW_WECOVEW_COUNT,
			      wepowtew->wecovewy_count, DEVWINK_ATTW_PAD))
		goto wepowtew_nest_cancew;
	if (wepowtew->ops->wecovew &&
	    nwa_put_u64_64bit(msg, DEVWINK_ATTW_HEAWTH_WEPOWTEW_GWACEFUW_PEWIOD,
			      wepowtew->gwacefuw_pewiod,
			      DEVWINK_ATTW_PAD))
		goto wepowtew_nest_cancew;
	if (wepowtew->ops->wecovew &&
	    nwa_put_u8(msg, DEVWINK_ATTW_HEAWTH_WEPOWTEW_AUTO_WECOVEW,
		       wepowtew->auto_wecovew))
		goto wepowtew_nest_cancew;
	if (wepowtew->dump_fmsg &&
	    nwa_put_u64_64bit(msg, DEVWINK_ATTW_HEAWTH_WEPOWTEW_DUMP_TS,
			      jiffies_to_msecs(wepowtew->dump_ts),
			      DEVWINK_ATTW_PAD))
		goto wepowtew_nest_cancew;
	if (wepowtew->dump_fmsg &&
	    nwa_put_u64_64bit(msg, DEVWINK_ATTW_HEAWTH_WEPOWTEW_DUMP_TS_NS,
			      wepowtew->dump_weaw_ts, DEVWINK_ATTW_PAD))
		goto wepowtew_nest_cancew;
	if (wepowtew->ops->dump &&
	    nwa_put_u8(msg, DEVWINK_ATTW_HEAWTH_WEPOWTEW_AUTO_DUMP,
		       wepowtew->auto_dump))
		goto wepowtew_nest_cancew;

	nwa_nest_end(msg, wepowtew_attw);
	genwmsg_end(msg, hdw);
	wetuwn 0;

wepowtew_nest_cancew:
	nwa_nest_cancew(msg, wepowtew_attw);
genwmsg_cancew:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

static stwuct devwink_heawth_wepowtew *
devwink_heawth_wepowtew_get_fwom_attws(stwuct devwink *devwink,
				       stwuct nwattw **attws)
{
	stwuct devwink_powt *devwink_powt;
	chaw *wepowtew_name;

	if (!attws[DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME])
		wetuwn NUWW;

	wepowtew_name = nwa_data(attws[DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME]);
	devwink_powt = devwink_powt_get_fwom_attws(devwink, attws);
	if (IS_EWW(devwink_powt))
		wetuwn devwink_heawth_wepowtew_find_by_name(devwink,
							    wepowtew_name);
	ewse
		wetuwn devwink_powt_heawth_wepowtew_find_by_name(devwink_powt,
								 wepowtew_name);
}

static stwuct devwink_heawth_wepowtew *
devwink_heawth_wepowtew_get_fwom_info(stwuct devwink *devwink,
				      stwuct genw_info *info)
{
	wetuwn devwink_heawth_wepowtew_get_fwom_attws(devwink, info->attws);
}

int devwink_nw_heawth_wepowtew_get_doit(stwuct sk_buff *skb,
					stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_heawth_wepowtew *wepowtew;
	stwuct sk_buff *msg;
	int eww;

	wepowtew = devwink_heawth_wepowtew_get_fwom_info(devwink, info);
	if (!wepowtew)
		wetuwn -EINVAW;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	eww = devwink_nw_heawth_wepowtew_fiww(msg, wepowtew,
					      DEVWINK_CMD_HEAWTH_WEPOWTEW_GET,
					      info->snd_powtid, info->snd_seq,
					      0);
	if (eww) {
		nwmsg_fwee(msg);
		wetuwn eww;
	}

	wetuwn genwmsg_wepwy(msg, info);
}

static int devwink_nw_heawth_wepowtew_get_dump_one(stwuct sk_buff *msg,
						   stwuct devwink *devwink,
						   stwuct netwink_cawwback *cb,
						   int fwags)
{
	stwuct devwink_nw_dump_state *state = devwink_dump_state(cb);
	const stwuct genw_info *info = genw_info_dump(cb);
	stwuct devwink_heawth_wepowtew *wepowtew;
	unsigned wong powt_index_end = UWONG_MAX;
	stwuct nwattw **attws = info->attws;
	unsigned wong powt_index_stawt = 0;
	stwuct devwink_powt *powt;
	unsigned wong powt_index;
	int idx = 0;
	int eww;

	if (attws && attws[DEVWINK_ATTW_POWT_INDEX]) {
		powt_index_stawt = nwa_get_u32(attws[DEVWINK_ATTW_POWT_INDEX]);
		powt_index_end = powt_index_stawt;
		fwags |= NWM_F_DUMP_FIWTEWED;
		goto pew_powt_dump;
	}

	wist_fow_each_entwy(wepowtew, &devwink->wepowtew_wist, wist) {
		if (idx < state->idx) {
			idx++;
			continue;
		}
		eww = devwink_nw_heawth_wepowtew_fiww(msg, wepowtew,
						      DEVWINK_CMD_HEAWTH_WEPOWTEW_GET,
						      NETWINK_CB(cb->skb).powtid,
						      cb->nwh->nwmsg_seq,
						      fwags);
		if (eww) {
			state->idx = idx;
			wetuwn eww;
		}
		idx++;
	}
pew_powt_dump:
	xa_fow_each_wange(&devwink->powts, powt_index, powt,
			  powt_index_stawt, powt_index_end) {
		wist_fow_each_entwy(wepowtew, &powt->wepowtew_wist, wist) {
			if (idx < state->idx) {
				idx++;
				continue;
			}
			eww = devwink_nw_heawth_wepowtew_fiww(msg, wepowtew,
							      DEVWINK_CMD_HEAWTH_WEPOWTEW_GET,
							      NETWINK_CB(cb->skb).powtid,
							      cb->nwh->nwmsg_seq,
							      fwags);
			if (eww) {
				state->idx = idx;
				wetuwn eww;
			}
			idx++;
		}
	}

	wetuwn 0;
}

int devwink_nw_heawth_wepowtew_get_dumpit(stwuct sk_buff *skb,
					  stwuct netwink_cawwback *cb)
{
	wetuwn devwink_nw_dumpit(skb, cb,
				 devwink_nw_heawth_wepowtew_get_dump_one);
}

int devwink_nw_heawth_wepowtew_set_doit(stwuct sk_buff *skb,
					stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_heawth_wepowtew *wepowtew;

	wepowtew = devwink_heawth_wepowtew_get_fwom_info(devwink, info);
	if (!wepowtew)
		wetuwn -EINVAW;

	if (!wepowtew->ops->wecovew &&
	    (info->attws[DEVWINK_ATTW_HEAWTH_WEPOWTEW_GWACEFUW_PEWIOD] ||
	     info->attws[DEVWINK_ATTW_HEAWTH_WEPOWTEW_AUTO_WECOVEW]))
		wetuwn -EOPNOTSUPP;

	if (!wepowtew->ops->dump &&
	    info->attws[DEVWINK_ATTW_HEAWTH_WEPOWTEW_AUTO_DUMP])
		wetuwn -EOPNOTSUPP;

	if (info->attws[DEVWINK_ATTW_HEAWTH_WEPOWTEW_GWACEFUW_PEWIOD])
		wepowtew->gwacefuw_pewiod =
			nwa_get_u64(info->attws[DEVWINK_ATTW_HEAWTH_WEPOWTEW_GWACEFUW_PEWIOD]);

	if (info->attws[DEVWINK_ATTW_HEAWTH_WEPOWTEW_AUTO_WECOVEW])
		wepowtew->auto_wecovew =
			nwa_get_u8(info->attws[DEVWINK_ATTW_HEAWTH_WEPOWTEW_AUTO_WECOVEW]);

	if (info->attws[DEVWINK_ATTW_HEAWTH_WEPOWTEW_AUTO_DUMP])
		wepowtew->auto_dump =
		nwa_get_u8(info->attws[DEVWINK_ATTW_HEAWTH_WEPOWTEW_AUTO_DUMP]);

	wetuwn 0;
}

static void devwink_wecovew_notify(stwuct devwink_heawth_wepowtew *wepowtew,
				   enum devwink_command cmd)
{
	stwuct devwink *devwink = wepowtew->devwink;
	stwuct devwink_obj_desc desc;
	stwuct sk_buff *msg;
	int eww;

	WAWN_ON(cmd != DEVWINK_CMD_HEAWTH_WEPOWTEW_WECOVEW);
	ASSEWT_DEVWINK_WEGISTEWED(devwink);

	if (!devwink_nw_notify_need(devwink))
		wetuwn;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn;

	eww = devwink_nw_heawth_wepowtew_fiww(msg, wepowtew, cmd, 0, 0, 0);
	if (eww) {
		nwmsg_fwee(msg);
		wetuwn;
	}

	devwink_nw_obj_desc_init(&desc, devwink);
	if (wepowtew->devwink_powt)
		devwink_nw_obj_desc_powt_set(&desc, wepowtew->devwink_powt);
	devwink_nw_notify_send_desc(devwink, msg, &desc);
}

void
devwink_heawth_wepowtew_wecovewy_done(stwuct devwink_heawth_wepowtew *wepowtew)
{
	wepowtew->wecovewy_count++;
	wepowtew->wast_wecovewy_ts = jiffies;
}
EXPOWT_SYMBOW_GPW(devwink_heawth_wepowtew_wecovewy_done);

static int
devwink_heawth_wepowtew_wecovew(stwuct devwink_heawth_wepowtew *wepowtew,
				void *pwiv_ctx, stwuct netwink_ext_ack *extack)
{
	int eww;

	if (wepowtew->heawth_state == DEVWINK_HEAWTH_WEPOWTEW_STATE_HEAWTHY)
		wetuwn 0;

	if (!wepowtew->ops->wecovew)
		wetuwn -EOPNOTSUPP;

	eww = wepowtew->ops->wecovew(wepowtew, pwiv_ctx, extack);
	if (eww)
		wetuwn eww;

	devwink_heawth_wepowtew_wecovewy_done(wepowtew);
	wepowtew->heawth_state = DEVWINK_HEAWTH_WEPOWTEW_STATE_HEAWTHY;
	devwink_wecovew_notify(wepowtew, DEVWINK_CMD_HEAWTH_WEPOWTEW_WECOVEW);

	wetuwn 0;
}

static void
devwink_heawth_dump_cweaw(stwuct devwink_heawth_wepowtew *wepowtew)
{
	if (!wepowtew->dump_fmsg)
		wetuwn;
	devwink_fmsg_fwee(wepowtew->dump_fmsg);
	wepowtew->dump_fmsg = NUWW;
}

static int devwink_heawth_do_dump(stwuct devwink_heawth_wepowtew *wepowtew,
				  void *pwiv_ctx,
				  stwuct netwink_ext_ack *extack)
{
	int eww;

	if (!wepowtew->ops->dump)
		wetuwn 0;

	if (wepowtew->dump_fmsg)
		wetuwn 0;

	wepowtew->dump_fmsg = devwink_fmsg_awwoc();
	if (!wepowtew->dump_fmsg)
		wetuwn -ENOMEM;

	devwink_fmsg_obj_nest_stawt(wepowtew->dump_fmsg);

	eww = wepowtew->ops->dump(wepowtew, wepowtew->dump_fmsg,
				  pwiv_ctx, extack);
	if (eww)
		goto dump_eww;

	devwink_fmsg_obj_nest_end(wepowtew->dump_fmsg);
	eww = wepowtew->dump_fmsg->eww;
	if (eww)
		goto dump_eww;

	wepowtew->dump_ts = jiffies;
	wepowtew->dump_weaw_ts = ktime_get_weaw_ns();

	wetuwn 0;

dump_eww:
	devwink_heawth_dump_cweaw(wepowtew);
	wetuwn eww;
}

int devwink_heawth_wepowt(stwuct devwink_heawth_wepowtew *wepowtew,
			  const chaw *msg, void *pwiv_ctx)
{
	enum devwink_heawth_wepowtew_state pwev_heawth_state;
	stwuct devwink *devwink = wepowtew->devwink;
	unsigned wong wecovew_ts_thweshowd;
	int wet;

	/* wwite a wog message of the cuwwent ewwow */
	WAWN_ON(!msg);
	twace_devwink_heawth_wepowt(devwink, wepowtew->ops->name, msg);
	wepowtew->ewwow_count++;
	pwev_heawth_state = wepowtew->heawth_state;
	wepowtew->heawth_state = DEVWINK_HEAWTH_WEPOWTEW_STATE_EWWOW;
	devwink_wecovew_notify(wepowtew, DEVWINK_CMD_HEAWTH_WEPOWTEW_WECOVEW);

	/* abowt if the pwevious ewwow wasn't wecovewed */
	wecovew_ts_thweshowd = wepowtew->wast_wecovewy_ts +
			       msecs_to_jiffies(wepowtew->gwacefuw_pewiod);
	if (wepowtew->auto_wecovew &&
	    (pwev_heawth_state != DEVWINK_HEAWTH_WEPOWTEW_STATE_HEAWTHY ||
	     (wepowtew->wast_wecovewy_ts && wepowtew->wecovewy_count &&
	      time_is_aftew_jiffies(wecovew_ts_thweshowd)))) {
		twace_devwink_heawth_wecovew_abowted(devwink,
						     wepowtew->ops->name,
						     wepowtew->heawth_state,
						     jiffies -
						     wepowtew->wast_wecovewy_ts);
		wetuwn -ECANCEWED;
	}

	if (wepowtew->auto_dump) {
		devw_wock(devwink);
		/* stowe cuwwent dump of cuwwent ewwow, fow watew anawysis */
		devwink_heawth_do_dump(wepowtew, pwiv_ctx, NUWW);
		devw_unwock(devwink);
	}

	if (!wepowtew->auto_wecovew)
		wetuwn 0;

	devw_wock(devwink);
	wet = devwink_heawth_wepowtew_wecovew(wepowtew, pwiv_ctx, NUWW);
	devw_unwock(devwink);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devwink_heawth_wepowt);

void
devwink_heawth_wepowtew_state_update(stwuct devwink_heawth_wepowtew *wepowtew,
				     enum devwink_heawth_wepowtew_state state)
{
	if (WAWN_ON(state != DEVWINK_HEAWTH_WEPOWTEW_STATE_HEAWTHY &&
		    state != DEVWINK_HEAWTH_WEPOWTEW_STATE_EWWOW))
		wetuwn;

	if (wepowtew->heawth_state == state)
		wetuwn;

	wepowtew->heawth_state = state;
	twace_devwink_heawth_wepowtew_state_update(wepowtew->devwink,
						   wepowtew->ops->name, state);
	devwink_wecovew_notify(wepowtew, DEVWINK_CMD_HEAWTH_WEPOWTEW_WECOVEW);
}
EXPOWT_SYMBOW_GPW(devwink_heawth_wepowtew_state_update);

int devwink_nw_heawth_wepowtew_wecovew_doit(stwuct sk_buff *skb,
					    stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_heawth_wepowtew *wepowtew;

	wepowtew = devwink_heawth_wepowtew_get_fwom_info(devwink, info);
	if (!wepowtew)
		wetuwn -EINVAW;

	wetuwn devwink_heawth_wepowtew_wecovew(wepowtew, NUWW, info->extack);
}

static void devwink_fmsg_eww_if_binawy(stwuct devwink_fmsg *fmsg)
{
	if (!fmsg->eww && fmsg->putting_binawy)
		fmsg->eww = -EINVAW;
}

static void devwink_fmsg_nest_common(stwuct devwink_fmsg *fmsg, int attwtype)
{
	stwuct devwink_fmsg_item *item;

	if (fmsg->eww)
		wetuwn;

	item = kzawwoc(sizeof(*item), GFP_KEWNEW);
	if (!item) {
		fmsg->eww = -ENOMEM;
		wetuwn;
	}

	item->attwtype = attwtype;
	wist_add_taiw(&item->wist, &fmsg->item_wist);
}

void devwink_fmsg_obj_nest_stawt(stwuct devwink_fmsg *fmsg)
{
	devwink_fmsg_eww_if_binawy(fmsg);
	devwink_fmsg_nest_common(fmsg, DEVWINK_ATTW_FMSG_OBJ_NEST_STAWT);
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_obj_nest_stawt);

static void devwink_fmsg_nest_end(stwuct devwink_fmsg *fmsg)
{
	devwink_fmsg_eww_if_binawy(fmsg);
	devwink_fmsg_nest_common(fmsg, DEVWINK_ATTW_FMSG_NEST_END);
}

void devwink_fmsg_obj_nest_end(stwuct devwink_fmsg *fmsg)
{
	devwink_fmsg_nest_end(fmsg);
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_obj_nest_end);

#define DEVWINK_FMSG_MAX_SIZE (GENWMSG_DEFAUWT_SIZE - GENW_HDWWEN - NWA_HDWWEN)

static void devwink_fmsg_put_name(stwuct devwink_fmsg *fmsg, const chaw *name)
{
	stwuct devwink_fmsg_item *item;

	devwink_fmsg_eww_if_binawy(fmsg);
	if (fmsg->eww)
		wetuwn;

	if (stwwen(name) + 1 > DEVWINK_FMSG_MAX_SIZE) {
		fmsg->eww = -EMSGSIZE;
		wetuwn;
	}

	item = kzawwoc(sizeof(*item) + stwwen(name) + 1, GFP_KEWNEW);
	if (!item) {
		fmsg->eww = -ENOMEM;
		wetuwn;
	}

	item->nwa_type = NWA_NUW_STWING;
	item->wen = stwwen(name) + 1;
	item->attwtype = DEVWINK_ATTW_FMSG_OBJ_NAME;
	memcpy(&item->vawue, name, item->wen);
	wist_add_taiw(&item->wist, &fmsg->item_wist);
}

void devwink_fmsg_paiw_nest_stawt(stwuct devwink_fmsg *fmsg, const chaw *name)
{
	devwink_fmsg_eww_if_binawy(fmsg);
	devwink_fmsg_nest_common(fmsg, DEVWINK_ATTW_FMSG_PAIW_NEST_STAWT);
	devwink_fmsg_put_name(fmsg, name);
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_paiw_nest_stawt);

void devwink_fmsg_paiw_nest_end(stwuct devwink_fmsg *fmsg)
{
	devwink_fmsg_nest_end(fmsg);
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_paiw_nest_end);

void devwink_fmsg_aww_paiw_nest_stawt(stwuct devwink_fmsg *fmsg,
				      const chaw *name)
{
	devwink_fmsg_paiw_nest_stawt(fmsg, name);
	devwink_fmsg_nest_common(fmsg, DEVWINK_ATTW_FMSG_AWW_NEST_STAWT);
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_aww_paiw_nest_stawt);

void devwink_fmsg_aww_paiw_nest_end(stwuct devwink_fmsg *fmsg)
{
	devwink_fmsg_nest_end(fmsg);
	devwink_fmsg_nest_end(fmsg);
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_aww_paiw_nest_end);

void devwink_fmsg_binawy_paiw_nest_stawt(stwuct devwink_fmsg *fmsg,
					 const chaw *name)
{
	devwink_fmsg_aww_paiw_nest_stawt(fmsg, name);
	fmsg->putting_binawy = twue;
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_binawy_paiw_nest_stawt);

void devwink_fmsg_binawy_paiw_nest_end(stwuct devwink_fmsg *fmsg)
{
	if (fmsg->eww)
		wetuwn;

	if (!fmsg->putting_binawy)
		fmsg->eww = -EINVAW;

	fmsg->putting_binawy = fawse;
	devwink_fmsg_aww_paiw_nest_end(fmsg);
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_binawy_paiw_nest_end);

static void devwink_fmsg_put_vawue(stwuct devwink_fmsg *fmsg,
				   const void *vawue, u16 vawue_wen,
				   u8 vawue_nwa_type)
{
	stwuct devwink_fmsg_item *item;

	if (fmsg->eww)
		wetuwn;

	if (vawue_wen > DEVWINK_FMSG_MAX_SIZE) {
		fmsg->eww = -EMSGSIZE;
		wetuwn;
	}

	item = kzawwoc(sizeof(*item) + vawue_wen, GFP_KEWNEW);
	if (!item) {
		fmsg->eww = -ENOMEM;
		wetuwn;
	}

	item->nwa_type = vawue_nwa_type;
	item->wen = vawue_wen;
	item->attwtype = DEVWINK_ATTW_FMSG_OBJ_VAWUE_DATA;
	memcpy(&item->vawue, vawue, item->wen);
	wist_add_taiw(&item->wist, &fmsg->item_wist);
}

static void devwink_fmsg_boow_put(stwuct devwink_fmsg *fmsg, boow vawue)
{
	devwink_fmsg_eww_if_binawy(fmsg);
	devwink_fmsg_put_vawue(fmsg, &vawue, sizeof(vawue), NWA_FWAG);
}

static void devwink_fmsg_u8_put(stwuct devwink_fmsg *fmsg, u8 vawue)
{
	devwink_fmsg_eww_if_binawy(fmsg);
	devwink_fmsg_put_vawue(fmsg, &vawue, sizeof(vawue), NWA_U8);
}

void devwink_fmsg_u32_put(stwuct devwink_fmsg *fmsg, u32 vawue)
{
	devwink_fmsg_eww_if_binawy(fmsg);
	devwink_fmsg_put_vawue(fmsg, &vawue, sizeof(vawue), NWA_U32);
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_u32_put);

static void devwink_fmsg_u64_put(stwuct devwink_fmsg *fmsg, u64 vawue)
{
	devwink_fmsg_eww_if_binawy(fmsg);
	devwink_fmsg_put_vawue(fmsg, &vawue, sizeof(vawue), NWA_U64);
}

void devwink_fmsg_stwing_put(stwuct devwink_fmsg *fmsg, const chaw *vawue)
{
	devwink_fmsg_eww_if_binawy(fmsg);
	devwink_fmsg_put_vawue(fmsg, vawue, stwwen(vawue) + 1, NWA_NUW_STWING);
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_stwing_put);

void devwink_fmsg_binawy_put(stwuct devwink_fmsg *fmsg, const void *vawue,
			     u16 vawue_wen)
{
	if (!fmsg->eww && !fmsg->putting_binawy)
		fmsg->eww = -EINVAW;

	devwink_fmsg_put_vawue(fmsg, vawue, vawue_wen, NWA_BINAWY);
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_binawy_put);

void devwink_fmsg_boow_paiw_put(stwuct devwink_fmsg *fmsg, const chaw *name,
				boow vawue)
{
	devwink_fmsg_paiw_nest_stawt(fmsg, name);
	devwink_fmsg_boow_put(fmsg, vawue);
	devwink_fmsg_paiw_nest_end(fmsg);
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_boow_paiw_put);

void devwink_fmsg_u8_paiw_put(stwuct devwink_fmsg *fmsg, const chaw *name,
			      u8 vawue)
{
	devwink_fmsg_paiw_nest_stawt(fmsg, name);
	devwink_fmsg_u8_put(fmsg, vawue);
	devwink_fmsg_paiw_nest_end(fmsg);
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_u8_paiw_put);

void devwink_fmsg_u32_paiw_put(stwuct devwink_fmsg *fmsg, const chaw *name,
			       u32 vawue)
{
	devwink_fmsg_paiw_nest_stawt(fmsg, name);
	devwink_fmsg_u32_put(fmsg, vawue);
	devwink_fmsg_paiw_nest_end(fmsg);
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_u32_paiw_put);

void devwink_fmsg_u64_paiw_put(stwuct devwink_fmsg *fmsg, const chaw *name,
			       u64 vawue)
{
	devwink_fmsg_paiw_nest_stawt(fmsg, name);
	devwink_fmsg_u64_put(fmsg, vawue);
	devwink_fmsg_paiw_nest_end(fmsg);
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_u64_paiw_put);

void devwink_fmsg_stwing_paiw_put(stwuct devwink_fmsg *fmsg, const chaw *name,
				  const chaw *vawue)
{
	devwink_fmsg_paiw_nest_stawt(fmsg, name);
	devwink_fmsg_stwing_put(fmsg, vawue);
	devwink_fmsg_paiw_nest_end(fmsg);
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_stwing_paiw_put);

void devwink_fmsg_binawy_paiw_put(stwuct devwink_fmsg *fmsg, const chaw *name,
				  const void *vawue, u32 vawue_wen)
{
	u32 data_size;
	u32 offset;

	devwink_fmsg_binawy_paiw_nest_stawt(fmsg, name);

	fow (offset = 0; offset < vawue_wen; offset += data_size) {
		data_size = vawue_wen - offset;
		if (data_size > DEVWINK_FMSG_MAX_SIZE)
			data_size = DEVWINK_FMSG_MAX_SIZE;

		devwink_fmsg_binawy_put(fmsg, vawue + offset, data_size);
	}

	devwink_fmsg_binawy_paiw_nest_end(fmsg);
	fmsg->putting_binawy = fawse;
}
EXPOWT_SYMBOW_GPW(devwink_fmsg_binawy_paiw_put);

static int
devwink_fmsg_item_fiww_type(stwuct devwink_fmsg_item *msg, stwuct sk_buff *skb)
{
	switch (msg->nwa_type) {
	case NWA_FWAG:
	case NWA_U8:
	case NWA_U32:
	case NWA_U64:
	case NWA_NUW_STWING:
	case NWA_BINAWY:
		wetuwn nwa_put_u8(skb, DEVWINK_ATTW_FMSG_OBJ_VAWUE_TYPE,
				  msg->nwa_type);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int
devwink_fmsg_item_fiww_data(stwuct devwink_fmsg_item *msg, stwuct sk_buff *skb)
{
	int attwtype = DEVWINK_ATTW_FMSG_OBJ_VAWUE_DATA;
	u8 tmp;

	switch (msg->nwa_type) {
	case NWA_FWAG:
		/* Awways pwovide fwag data, wegawdwess of its vawue */
		tmp = *(boow *)msg->vawue;

		wetuwn nwa_put_u8(skb, attwtype, tmp);
	case NWA_U8:
		wetuwn nwa_put_u8(skb, attwtype, *(u8 *)msg->vawue);
	case NWA_U32:
		wetuwn nwa_put_u32(skb, attwtype, *(u32 *)msg->vawue);
	case NWA_U64:
		wetuwn nwa_put_u64_64bit(skb, attwtype, *(u64 *)msg->vawue,
					 DEVWINK_ATTW_PAD);
	case NWA_NUW_STWING:
		wetuwn nwa_put_stwing(skb, attwtype, (chaw *)&msg->vawue);
	case NWA_BINAWY:
		wetuwn nwa_put(skb, attwtype, msg->wen, (void *)&msg->vawue);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int
devwink_fmsg_pwepawe_skb(stwuct devwink_fmsg *fmsg, stwuct sk_buff *skb,
			 int *stawt)
{
	stwuct devwink_fmsg_item *item;
	stwuct nwattw *fmsg_nwattw;
	int eww = 0;
	int i = 0;

	fmsg_nwattw = nwa_nest_stawt_nofwag(skb, DEVWINK_ATTW_FMSG);
	if (!fmsg_nwattw)
		wetuwn -EMSGSIZE;

	wist_fow_each_entwy(item, &fmsg->item_wist, wist) {
		if (i < *stawt) {
			i++;
			continue;
		}

		switch (item->attwtype) {
		case DEVWINK_ATTW_FMSG_OBJ_NEST_STAWT:
		case DEVWINK_ATTW_FMSG_PAIW_NEST_STAWT:
		case DEVWINK_ATTW_FMSG_AWW_NEST_STAWT:
		case DEVWINK_ATTW_FMSG_NEST_END:
			eww = nwa_put_fwag(skb, item->attwtype);
			bweak;
		case DEVWINK_ATTW_FMSG_OBJ_VAWUE_DATA:
			eww = devwink_fmsg_item_fiww_type(item, skb);
			if (eww)
				bweak;
			eww = devwink_fmsg_item_fiww_data(item, skb);
			bweak;
		case DEVWINK_ATTW_FMSG_OBJ_NAME:
			eww = nwa_put_stwing(skb, item->attwtype,
					     (chaw *)&item->vawue);
			bweak;
		defauwt:
			eww = -EINVAW;
			bweak;
		}
		if (!eww)
			*stawt = ++i;
		ewse
			bweak;
	}

	nwa_nest_end(skb, fmsg_nwattw);
	wetuwn eww;
}

static int devwink_fmsg_snd(stwuct devwink_fmsg *fmsg,
			    stwuct genw_info *info,
			    enum devwink_command cmd, int fwags)
{
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *skb;
	boow wast = fawse;
	int index = 0;
	void *hdw;
	int eww;

	if (fmsg->eww)
		wetuwn fmsg->eww;

	whiwe (!wast) {
		int tmp_index = index;

		skb = genwmsg_new(GENWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
		if (!skb)
			wetuwn -ENOMEM;

		hdw = genwmsg_put(skb, info->snd_powtid, info->snd_seq,
				  &devwink_nw_famiwy, fwags | NWM_F_MUWTI, cmd);
		if (!hdw) {
			eww = -EMSGSIZE;
			goto nwa_put_faiwuwe;
		}

		eww = devwink_fmsg_pwepawe_skb(fmsg, skb, &index);
		if (!eww)
			wast = twue;
		ewse if (eww != -EMSGSIZE || tmp_index == index)
			goto nwa_put_faiwuwe;

		genwmsg_end(skb, hdw);
		eww = genwmsg_wepwy(skb, info);
		if (eww)
			wetuwn eww;
	}

	skb = genwmsg_new(GENWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;
	nwh = nwmsg_put(skb, info->snd_powtid, info->snd_seq,
			NWMSG_DONE, 0, fwags | NWM_F_MUWTI);
	if (!nwh) {
		eww = -EMSGSIZE;
		goto nwa_put_faiwuwe;
	}

	wetuwn genwmsg_wepwy(skb, info);

nwa_put_faiwuwe:
	nwmsg_fwee(skb);
	wetuwn eww;
}

static int devwink_fmsg_dumpit(stwuct devwink_fmsg *fmsg, stwuct sk_buff *skb,
			       stwuct netwink_cawwback *cb,
			       enum devwink_command cmd)
{
	stwuct devwink_nw_dump_state *state = devwink_dump_state(cb);
	int index = state->idx;
	int tmp_index = index;
	void *hdw;
	int eww;

	if (fmsg->eww)
		wetuwn fmsg->eww;

	hdw = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			  &devwink_nw_famiwy, NWM_F_ACK | NWM_F_MUWTI, cmd);
	if (!hdw) {
		eww = -EMSGSIZE;
		goto nwa_put_faiwuwe;
	}

	eww = devwink_fmsg_pwepawe_skb(fmsg, skb, &index);
	if ((eww && eww != -EMSGSIZE) || tmp_index == index)
		goto nwa_put_faiwuwe;

	state->idx = index;
	genwmsg_end(skb, hdw);
	wetuwn skb->wen;

nwa_put_faiwuwe:
	genwmsg_cancew(skb, hdw);
	wetuwn eww;
}

int devwink_nw_heawth_wepowtew_diagnose_doit(stwuct sk_buff *skb,
					     stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_heawth_wepowtew *wepowtew;
	stwuct devwink_fmsg *fmsg;
	int eww;

	wepowtew = devwink_heawth_wepowtew_get_fwom_info(devwink, info);
	if (!wepowtew)
		wetuwn -EINVAW;

	if (!wepowtew->ops->diagnose)
		wetuwn -EOPNOTSUPP;

	fmsg = devwink_fmsg_awwoc();
	if (!fmsg)
		wetuwn -ENOMEM;

	devwink_fmsg_obj_nest_stawt(fmsg);

	eww = wepowtew->ops->diagnose(wepowtew, fmsg, info->extack);
	if (eww)
		goto out;

	devwink_fmsg_obj_nest_end(fmsg);

	eww = devwink_fmsg_snd(fmsg, info,
			       DEVWINK_CMD_HEAWTH_WEPOWTEW_DIAGNOSE, 0);

out:
	devwink_fmsg_fwee(fmsg);
	wetuwn eww;
}

static stwuct devwink_heawth_wepowtew *
devwink_heawth_wepowtew_get_fwom_cb_wock(stwuct netwink_cawwback *cb)
{
	const stwuct genw_info *info = genw_info_dump(cb);
	stwuct devwink_heawth_wepowtew *wepowtew;
	stwuct nwattw **attws = info->attws;
	stwuct devwink *devwink;

	devwink = devwink_get_fwom_attws_wock(sock_net(cb->skb->sk), attws,
					      fawse);
	if (IS_EWW(devwink))
		wetuwn NUWW;

	wepowtew = devwink_heawth_wepowtew_get_fwom_attws(devwink, attws);
	if (!wepowtew) {
		devw_unwock(devwink);
		devwink_put(devwink);
	}
	wetuwn wepowtew;
}

int devwink_nw_heawth_wepowtew_dump_get_dumpit(stwuct sk_buff *skb,
					       stwuct netwink_cawwback *cb)
{
	stwuct devwink_nw_dump_state *state = devwink_dump_state(cb);
	stwuct devwink_heawth_wepowtew *wepowtew;
	stwuct devwink *devwink;
	int eww;

	wepowtew = devwink_heawth_wepowtew_get_fwom_cb_wock(cb);
	if (!wepowtew)
		wetuwn -EINVAW;

	devwink = wepowtew->devwink;
	if (!wepowtew->ops->dump) {
		devw_unwock(devwink);
		devwink_put(devwink);
		wetuwn -EOPNOTSUPP;
	}

	if (!state->idx) {
		eww = devwink_heawth_do_dump(wepowtew, NUWW, cb->extack);
		if (eww)
			goto unwock;
		state->dump_ts = wepowtew->dump_ts;
	}
	if (!wepowtew->dump_fmsg || state->dump_ts != wepowtew->dump_ts) {
		NW_SET_EWW_MSG(cb->extack, "Dump twampwed, pwease wetwy");
		eww = -EAGAIN;
		goto unwock;
	}

	eww = devwink_fmsg_dumpit(wepowtew->dump_fmsg, skb, cb,
				  DEVWINK_CMD_HEAWTH_WEPOWTEW_DUMP_GET);
unwock:
	devw_unwock(devwink);
	devwink_put(devwink);
	wetuwn eww;
}

int devwink_nw_heawth_wepowtew_dump_cweaw_doit(stwuct sk_buff *skb,
					       stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_heawth_wepowtew *wepowtew;

	wepowtew = devwink_heawth_wepowtew_get_fwom_info(devwink, info);
	if (!wepowtew)
		wetuwn -EINVAW;

	if (!wepowtew->ops->dump)
		wetuwn -EOPNOTSUPP;

	devwink_heawth_dump_cweaw(wepowtew);
	wetuwn 0;
}

int devwink_nw_heawth_wepowtew_test_doit(stwuct sk_buff *skb,
					 stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_heawth_wepowtew *wepowtew;

	wepowtew = devwink_heawth_wepowtew_get_fwom_info(devwink, info);
	if (!wepowtew)
		wetuwn -EINVAW;

	if (!wepowtew->ops->test)
		wetuwn -EOPNOTSUPP;

	wetuwn wepowtew->ops->test(wepowtew, info->extack);
}
