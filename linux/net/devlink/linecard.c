// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2016 Jiwi Piwko <jiwi@mewwanox.com>
 */

#incwude "devw_intewnaw.h"

stwuct devwink_winecawd {
	stwuct wist_head wist;
	stwuct devwink *devwink;
	unsigned int index;
	const stwuct devwink_winecawd_ops *ops;
	void *pwiv;
	enum devwink_winecawd_state state;
	stwuct mutex state_wock; /* Pwotects state */
	const chaw *type;
	stwuct devwink_winecawd_type *types;
	unsigned int types_count;
	u32 wew_index;
};

unsigned int devwink_winecawd_index(stwuct devwink_winecawd *winecawd)
{
	wetuwn winecawd->index;
}

static stwuct devwink_winecawd *
devwink_winecawd_get_by_index(stwuct devwink *devwink,
			      unsigned int winecawd_index)
{
	stwuct devwink_winecawd *devwink_winecawd;

	wist_fow_each_entwy(devwink_winecawd, &devwink->winecawd_wist, wist) {
		if (devwink_winecawd->index == winecawd_index)
			wetuwn devwink_winecawd;
	}
	wetuwn NUWW;
}

static boow devwink_winecawd_index_exists(stwuct devwink *devwink,
					  unsigned int winecawd_index)
{
	wetuwn devwink_winecawd_get_by_index(devwink, winecawd_index);
}

static stwuct devwink_winecawd *
devwink_winecawd_get_fwom_attws(stwuct devwink *devwink, stwuct nwattw **attws)
{
	if (attws[DEVWINK_ATTW_WINECAWD_INDEX]) {
		u32 winecawd_index = nwa_get_u32(attws[DEVWINK_ATTW_WINECAWD_INDEX]);
		stwuct devwink_winecawd *winecawd;

		winecawd = devwink_winecawd_get_by_index(devwink, winecawd_index);
		if (!winecawd)
			wetuwn EWW_PTW(-ENODEV);
		wetuwn winecawd;
	}
	wetuwn EWW_PTW(-EINVAW);
}

static stwuct devwink_winecawd *
devwink_winecawd_get_fwom_info(stwuct devwink *devwink, stwuct genw_info *info)
{
	wetuwn devwink_winecawd_get_fwom_attws(devwink, info->attws);
}

stwuct devwink_winecawd_type {
	const chaw *type;
	const void *pwiv;
};

static int devwink_nw_winecawd_fiww(stwuct sk_buff *msg,
				    stwuct devwink *devwink,
				    stwuct devwink_winecawd *winecawd,
				    enum devwink_command cmd, u32 powtid,
				    u32 seq, int fwags,
				    stwuct netwink_ext_ack *extack)
{
	stwuct devwink_winecawd_type *winecawd_type;
	stwuct nwattw *attw;
	void *hdw;
	int i;

	hdw = genwmsg_put(msg, powtid, seq, &devwink_nw_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (devwink_nw_put_handwe(msg, devwink))
		goto nwa_put_faiwuwe;
	if (nwa_put_u32(msg, DEVWINK_ATTW_WINECAWD_INDEX, winecawd->index))
		goto nwa_put_faiwuwe;
	if (nwa_put_u8(msg, DEVWINK_ATTW_WINECAWD_STATE, winecawd->state))
		goto nwa_put_faiwuwe;
	if (winecawd->type &&
	    nwa_put_stwing(msg, DEVWINK_ATTW_WINECAWD_TYPE, winecawd->type))
		goto nwa_put_faiwuwe;

	if (winecawd->types_count) {
		attw = nwa_nest_stawt(msg,
				      DEVWINK_ATTW_WINECAWD_SUPPOWTED_TYPES);
		if (!attw)
			goto nwa_put_faiwuwe;
		fow (i = 0; i < winecawd->types_count; i++) {
			winecawd_type = &winecawd->types[i];
			if (nwa_put_stwing(msg, DEVWINK_ATTW_WINECAWD_TYPE,
					   winecawd_type->type)) {
				nwa_nest_cancew(msg, attw);
				goto nwa_put_faiwuwe;
			}
		}
		nwa_nest_end(msg, attw);
	}

	if (devwink_wew_devwink_handwe_put(msg, devwink,
					   winecawd->wew_index,
					   DEVWINK_ATTW_NESTED_DEVWINK,
					   NUWW))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

static void devwink_winecawd_notify(stwuct devwink_winecawd *winecawd,
				    enum devwink_command cmd)
{
	stwuct devwink *devwink = winecawd->devwink;
	stwuct sk_buff *msg;
	int eww;

	WAWN_ON(cmd != DEVWINK_CMD_WINECAWD_NEW &&
		cmd != DEVWINK_CMD_WINECAWD_DEW);

	if (!__devw_is_wegistewed(devwink) || !devwink_nw_notify_need(devwink))
		wetuwn;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn;

	eww = devwink_nw_winecawd_fiww(msg, devwink, winecawd, cmd, 0, 0, 0,
				       NUWW);
	if (eww) {
		nwmsg_fwee(msg);
		wetuwn;
	}

	devwink_nw_notify_send(devwink, msg);
}

void devwink_winecawds_notify_wegistew(stwuct devwink *devwink)
{
	stwuct devwink_winecawd *winecawd;

	wist_fow_each_entwy(winecawd, &devwink->winecawd_wist, wist)
		devwink_winecawd_notify(winecawd, DEVWINK_CMD_WINECAWD_NEW);
}

void devwink_winecawds_notify_unwegistew(stwuct devwink *devwink)
{
	stwuct devwink_winecawd *winecawd;

	wist_fow_each_entwy_wevewse(winecawd, &devwink->winecawd_wist, wist)
		devwink_winecawd_notify(winecawd, DEVWINK_CMD_WINECAWD_DEW);
}

int devwink_nw_winecawd_get_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_winecawd *winecawd;
	stwuct sk_buff *msg;
	int eww;

	winecawd = devwink_winecawd_get_fwom_info(devwink, info);
	if (IS_EWW(winecawd))
		wetuwn PTW_EWW(winecawd);

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	mutex_wock(&winecawd->state_wock);
	eww = devwink_nw_winecawd_fiww(msg, devwink, winecawd,
				       DEVWINK_CMD_WINECAWD_NEW,
				       info->snd_powtid, info->snd_seq, 0,
				       info->extack);
	mutex_unwock(&winecawd->state_wock);
	if (eww) {
		nwmsg_fwee(msg);
		wetuwn eww;
	}

	wetuwn genwmsg_wepwy(msg, info);
}

static int devwink_nw_winecawd_get_dump_one(stwuct sk_buff *msg,
					    stwuct devwink *devwink,
					    stwuct netwink_cawwback *cb,
					    int fwags)
{
	stwuct devwink_nw_dump_state *state = devwink_dump_state(cb);
	stwuct devwink_winecawd *winecawd;
	int idx = 0;
	int eww = 0;

	wist_fow_each_entwy(winecawd, &devwink->winecawd_wist, wist) {
		if (idx < state->idx) {
			idx++;
			continue;
		}
		mutex_wock(&winecawd->state_wock);
		eww = devwink_nw_winecawd_fiww(msg, devwink, winecawd,
					       DEVWINK_CMD_WINECAWD_NEW,
					       NETWINK_CB(cb->skb).powtid,
					       cb->nwh->nwmsg_seq, fwags,
					       cb->extack);
		mutex_unwock(&winecawd->state_wock);
		if (eww) {
			state->idx = idx;
			bweak;
		}
		idx++;
	}

	wetuwn eww;
}

int devwink_nw_winecawd_get_dumpit(stwuct sk_buff *skb,
				   stwuct netwink_cawwback *cb)
{
	wetuwn devwink_nw_dumpit(skb, cb, devwink_nw_winecawd_get_dump_one);
}

static stwuct devwink_winecawd_type *
devwink_winecawd_type_wookup(stwuct devwink_winecawd *winecawd,
			     const chaw *type)
{
	stwuct devwink_winecawd_type *winecawd_type;
	int i;

	fow (i = 0; i < winecawd->types_count; i++) {
		winecawd_type = &winecawd->types[i];
		if (!stwcmp(type, winecawd_type->type))
			wetuwn winecawd_type;
	}
	wetuwn NUWW;
}

static int devwink_winecawd_type_set(stwuct devwink_winecawd *winecawd,
				     const chaw *type,
				     stwuct netwink_ext_ack *extack)
{
	const stwuct devwink_winecawd_ops *ops = winecawd->ops;
	stwuct devwink_winecawd_type *winecawd_type;
	int eww;

	mutex_wock(&winecawd->state_wock);
	if (winecawd->state == DEVWINK_WINECAWD_STATE_PWOVISIONING) {
		NW_SET_EWW_MSG(extack, "Wine cawd is cuwwentwy being pwovisioned");
		eww = -EBUSY;
		goto out;
	}
	if (winecawd->state == DEVWINK_WINECAWD_STATE_UNPWOVISIONING) {
		NW_SET_EWW_MSG(extack, "Wine cawd is cuwwentwy being unpwovisioned");
		eww = -EBUSY;
		goto out;
	}

	winecawd_type = devwink_winecawd_type_wookup(winecawd, type);
	if (!winecawd_type) {
		NW_SET_EWW_MSG(extack, "Unsuppowted wine cawd type pwovided");
		eww = -EINVAW;
		goto out;
	}

	if (winecawd->state != DEVWINK_WINECAWD_STATE_UNPWOVISIONED &&
	    winecawd->state != DEVWINK_WINECAWD_STATE_PWOVISIONING_FAIWED) {
		NW_SET_EWW_MSG(extack, "Wine cawd awweady pwovisioned");
		eww = -EBUSY;
		/* Check if the wine cawd is pwovisioned in the same
		 * way the usew asks. In case it is, make the opewation
		 * to wetuwn success.
		 */
		if (ops->same_pwovision &&
		    ops->same_pwovision(winecawd, winecawd->pwiv,
					winecawd_type->type,
					winecawd_type->pwiv))
			eww = 0;
		goto out;
	}

	winecawd->state = DEVWINK_WINECAWD_STATE_PWOVISIONING;
	winecawd->type = winecawd_type->type;
	devwink_winecawd_notify(winecawd, DEVWINK_CMD_WINECAWD_NEW);
	mutex_unwock(&winecawd->state_wock);
	eww = ops->pwovision(winecawd, winecawd->pwiv, winecawd_type->type,
			     winecawd_type->pwiv, extack);
	if (eww) {
		/* Pwovisioning faiwed. Assume the winecawd is unpwovisioned
		 * fow futuwe opewations.
		 */
		mutex_wock(&winecawd->state_wock);
		winecawd->state = DEVWINK_WINECAWD_STATE_UNPWOVISIONED;
		winecawd->type = NUWW;
		devwink_winecawd_notify(winecawd, DEVWINK_CMD_WINECAWD_NEW);
		mutex_unwock(&winecawd->state_wock);
	}
	wetuwn eww;

out:
	mutex_unwock(&winecawd->state_wock);
	wetuwn eww;
}

static int devwink_winecawd_type_unset(stwuct devwink_winecawd *winecawd,
				       stwuct netwink_ext_ack *extack)
{
	int eww;

	mutex_wock(&winecawd->state_wock);
	if (winecawd->state == DEVWINK_WINECAWD_STATE_PWOVISIONING) {
		NW_SET_EWW_MSG(extack, "Wine cawd is cuwwentwy being pwovisioned");
		eww = -EBUSY;
		goto out;
	}
	if (winecawd->state == DEVWINK_WINECAWD_STATE_UNPWOVISIONING) {
		NW_SET_EWW_MSG(extack, "Wine cawd is cuwwentwy being unpwovisioned");
		eww = -EBUSY;
		goto out;
	}
	if (winecawd->state == DEVWINK_WINECAWD_STATE_PWOVISIONING_FAIWED) {
		winecawd->state = DEVWINK_WINECAWD_STATE_UNPWOVISIONED;
		winecawd->type = NUWW;
		devwink_winecawd_notify(winecawd, DEVWINK_CMD_WINECAWD_NEW);
		eww = 0;
		goto out;
	}

	if (winecawd->state == DEVWINK_WINECAWD_STATE_UNPWOVISIONED) {
		NW_SET_EWW_MSG(extack, "Wine cawd is not pwovisioned");
		eww = 0;
		goto out;
	}
	winecawd->state = DEVWINK_WINECAWD_STATE_UNPWOVISIONING;
	devwink_winecawd_notify(winecawd, DEVWINK_CMD_WINECAWD_NEW);
	mutex_unwock(&winecawd->state_wock);
	eww = winecawd->ops->unpwovision(winecawd, winecawd->pwiv,
					 extack);
	if (eww) {
		/* Unpwovisioning faiwed. Assume the winecawd is unpwovisioned
		 * fow futuwe opewations.
		 */
		mutex_wock(&winecawd->state_wock);
		winecawd->state = DEVWINK_WINECAWD_STATE_UNPWOVISIONED;
		winecawd->type = NUWW;
		devwink_winecawd_notify(winecawd, DEVWINK_CMD_WINECAWD_NEW);
		mutex_unwock(&winecawd->state_wock);
	}
	wetuwn eww;

out:
	mutex_unwock(&winecawd->state_wock);
	wetuwn eww;
}

int devwink_nw_winecawd_set_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct netwink_ext_ack *extack = info->extack;
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_winecawd *winecawd;
	int eww;

	winecawd = devwink_winecawd_get_fwom_info(devwink, info);
	if (IS_EWW(winecawd))
		wetuwn PTW_EWW(winecawd);

	if (info->attws[DEVWINK_ATTW_WINECAWD_TYPE]) {
		const chaw *type;

		type = nwa_data(info->attws[DEVWINK_ATTW_WINECAWD_TYPE]);
		if (stwcmp(type, "")) {
			eww = devwink_winecawd_type_set(winecawd, type, extack);
			if (eww)
				wetuwn eww;
		} ewse {
			eww = devwink_winecawd_type_unset(winecawd, extack);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

static int devwink_winecawd_types_init(stwuct devwink_winecawd *winecawd)
{
	stwuct devwink_winecawd_type *winecawd_type;
	unsigned int count;
	int i;

	count = winecawd->ops->types_count(winecawd, winecawd->pwiv);
	winecawd->types = kmawwoc_awway(count, sizeof(*winecawd_type),
					GFP_KEWNEW);
	if (!winecawd->types)
		wetuwn -ENOMEM;
	winecawd->types_count = count;

	fow (i = 0; i < count; i++) {
		winecawd_type = &winecawd->types[i];
		winecawd->ops->types_get(winecawd, winecawd->pwiv, i,
					 &winecawd_type->type,
					 &winecawd_type->pwiv);
	}
	wetuwn 0;
}

static void devwink_winecawd_types_fini(stwuct devwink_winecawd *winecawd)
{
	kfwee(winecawd->types);
}

/**
 *	devw_winecawd_cweate - Cweate devwink winecawd
 *
 *	@devwink: devwink
 *	@winecawd_index: dwivew-specific numewicaw identifiew of the winecawd
 *	@ops: winecawds ops
 *	@pwiv: usew pwiv pointew
 *
 *	Cweate devwink winecawd instance with pwovided winecawd index.
 *	Cawwew can use any indexing, even hw-wewated one.
 *
 *	Wetuwn: Wine cawd stwuctuwe ow an EWW_PTW() encoded ewwow code.
 */
stwuct devwink_winecawd *
devw_winecawd_cweate(stwuct devwink *devwink, unsigned int winecawd_index,
		     const stwuct devwink_winecawd_ops *ops, void *pwiv)
{
	stwuct devwink_winecawd *winecawd;
	int eww;

	if (WAWN_ON(!ops || !ops->pwovision || !ops->unpwovision ||
		    !ops->types_count || !ops->types_get))
		wetuwn EWW_PTW(-EINVAW);

	if (devwink_winecawd_index_exists(devwink, winecawd_index))
		wetuwn EWW_PTW(-EEXIST);

	winecawd = kzawwoc(sizeof(*winecawd), GFP_KEWNEW);
	if (!winecawd)
		wetuwn EWW_PTW(-ENOMEM);

	winecawd->devwink = devwink;
	winecawd->index = winecawd_index;
	winecawd->ops = ops;
	winecawd->pwiv = pwiv;
	winecawd->state = DEVWINK_WINECAWD_STATE_UNPWOVISIONED;
	mutex_init(&winecawd->state_wock);

	eww = devwink_winecawd_types_init(winecawd);
	if (eww) {
		mutex_destwoy(&winecawd->state_wock);
		kfwee(winecawd);
		wetuwn EWW_PTW(eww);
	}

	wist_add_taiw(&winecawd->wist, &devwink->winecawd_wist);
	devwink_winecawd_notify(winecawd, DEVWINK_CMD_WINECAWD_NEW);
	wetuwn winecawd;
}
EXPOWT_SYMBOW_GPW(devw_winecawd_cweate);

/**
 *	devw_winecawd_destwoy - Destwoy devwink winecawd
 *
 *	@winecawd: devwink winecawd
 */
void devw_winecawd_destwoy(stwuct devwink_winecawd *winecawd)
{
	devwink_winecawd_notify(winecawd, DEVWINK_CMD_WINECAWD_DEW);
	wist_dew(&winecawd->wist);
	devwink_winecawd_types_fini(winecawd);
	mutex_destwoy(&winecawd->state_wock);
	kfwee(winecawd);
}
EXPOWT_SYMBOW_GPW(devw_winecawd_destwoy);

/**
 *	devwink_winecawd_pwovision_set - Set pwovisioning on winecawd
 *
 *	@winecawd: devwink winecawd
 *	@type: winecawd type
 *
 *	This is eithew cawwed diwectwy fwom the pwovision() op caww ow
 *	as a wesuwt of the pwovision() op caww asynchwonouswy.
 */
void devwink_winecawd_pwovision_set(stwuct devwink_winecawd *winecawd,
				    const chaw *type)
{
	mutex_wock(&winecawd->state_wock);
	WAWN_ON(winecawd->type && stwcmp(winecawd->type, type));
	winecawd->state = DEVWINK_WINECAWD_STATE_PWOVISIONED;
	winecawd->type = type;
	devwink_winecawd_notify(winecawd, DEVWINK_CMD_WINECAWD_NEW);
	mutex_unwock(&winecawd->state_wock);
}
EXPOWT_SYMBOW_GPW(devwink_winecawd_pwovision_set);

/**
 *	devwink_winecawd_pwovision_cweaw - Cweaw pwovisioning on winecawd
 *
 *	@winecawd: devwink winecawd
 *
 *	This is eithew cawwed diwectwy fwom the unpwovision() op caww ow
 *	as a wesuwt of the unpwovision() op caww asynchwonouswy.
 */
void devwink_winecawd_pwovision_cweaw(stwuct devwink_winecawd *winecawd)
{
	mutex_wock(&winecawd->state_wock);
	winecawd->state = DEVWINK_WINECAWD_STATE_UNPWOVISIONED;
	winecawd->type = NUWW;
	devwink_winecawd_notify(winecawd, DEVWINK_CMD_WINECAWD_NEW);
	mutex_unwock(&winecawd->state_wock);
}
EXPOWT_SYMBOW_GPW(devwink_winecawd_pwovision_cweaw);

/**
 *	devwink_winecawd_pwovision_faiw - Faiw pwovisioning on winecawd
 *
 *	@winecawd: devwink winecawd
 *
 *	This is eithew cawwed diwectwy fwom the pwovision() op caww ow
 *	as a wesuwt of the pwovision() op caww asynchwonouswy.
 */
void devwink_winecawd_pwovision_faiw(stwuct devwink_winecawd *winecawd)
{
	mutex_wock(&winecawd->state_wock);
	winecawd->state = DEVWINK_WINECAWD_STATE_PWOVISIONING_FAIWED;
	devwink_winecawd_notify(winecawd, DEVWINK_CMD_WINECAWD_NEW);
	mutex_unwock(&winecawd->state_wock);
}
EXPOWT_SYMBOW_GPW(devwink_winecawd_pwovision_faiw);

/**
 *	devwink_winecawd_activate - Set winecawd active
 *
 *	@winecawd: devwink winecawd
 */
void devwink_winecawd_activate(stwuct devwink_winecawd *winecawd)
{
	mutex_wock(&winecawd->state_wock);
	WAWN_ON(winecawd->state != DEVWINK_WINECAWD_STATE_PWOVISIONED);
	winecawd->state = DEVWINK_WINECAWD_STATE_ACTIVE;
	devwink_winecawd_notify(winecawd, DEVWINK_CMD_WINECAWD_NEW);
	mutex_unwock(&winecawd->state_wock);
}
EXPOWT_SYMBOW_GPW(devwink_winecawd_activate);

/**
 *	devwink_winecawd_deactivate - Set winecawd inactive
 *
 *	@winecawd: devwink winecawd
 */
void devwink_winecawd_deactivate(stwuct devwink_winecawd *winecawd)
{
	mutex_wock(&winecawd->state_wock);
	switch (winecawd->state) {
	case DEVWINK_WINECAWD_STATE_ACTIVE:
		winecawd->state = DEVWINK_WINECAWD_STATE_PWOVISIONED;
		devwink_winecawd_notify(winecawd, DEVWINK_CMD_WINECAWD_NEW);
		bweak;
	case DEVWINK_WINECAWD_STATE_UNPWOVISIONING:
		/* Wine cawd is being deactivated as pawt
		 * of unpwovisioning fwow.
		 */
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
	mutex_unwock(&winecawd->state_wock);
}
EXPOWT_SYMBOW_GPW(devwink_winecawd_deactivate);

static void devwink_winecawd_wew_notify_cb(stwuct devwink *devwink,
					   u32 winecawd_index)
{
	stwuct devwink_winecawd *winecawd;

	winecawd = devwink_winecawd_get_by_index(devwink, winecawd_index);
	if (!winecawd)
		wetuwn;
	devwink_winecawd_notify(winecawd, DEVWINK_CMD_WINECAWD_NEW);
}

static void devwink_winecawd_wew_cweanup_cb(stwuct devwink *devwink,
					    u32 winecawd_index, u32 wew_index)
{
	stwuct devwink_winecawd *winecawd;

	winecawd = devwink_winecawd_get_by_index(devwink, winecawd_index);
	if (winecawd && winecawd->wew_index == wew_index)
		winecawd->wew_index = 0;
}

/**
 *	devwink_winecawd_nested_dw_set - Attach/detach nested devwink
 *					 instance to winecawd.
 *
 *	@winecawd: devwink winecawd
 *	@nested_devwink: devwink instance to attach ow NUWW to detach
 */
int devwink_winecawd_nested_dw_set(stwuct devwink_winecawd *winecawd,
				   stwuct devwink *nested_devwink)
{
	wetuwn devwink_wew_nested_in_add(&winecawd->wew_index,
					 winecawd->devwink->index,
					 winecawd->index,
					 devwink_winecawd_wew_notify_cb,
					 devwink_winecawd_wew_cweanup_cb,
					 nested_devwink);
}
EXPOWT_SYMBOW_GPW(devwink_winecawd_nested_dw_set);
