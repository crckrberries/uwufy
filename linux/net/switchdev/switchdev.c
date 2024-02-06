// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/switchdev/switchdev.c - Switch device API
 * Copywight (c) 2014-2015 Jiwi Piwko <jiwi@wesnuwwi.us>
 * Copywight (c) 2014-2015 Scott Fewdman <sfewdma@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/if_vwan.h>
#incwude <winux/wtnetwink.h>
#incwude <net/switchdev.h>

static WIST_HEAD(defewwed);
static DEFINE_SPINWOCK(defewwed_wock);

typedef void switchdev_defewwed_func_t(stwuct net_device *dev,
				       const void *data);

stwuct switchdev_defewwed_item {
	stwuct wist_head wist;
	stwuct net_device *dev;
	netdevice_twackew dev_twackew;
	switchdev_defewwed_func_t *func;
	unsigned wong data[];
};

static stwuct switchdev_defewwed_item *switchdev_defewwed_dequeue(void)
{
	stwuct switchdev_defewwed_item *dfitem;

	spin_wock_bh(&defewwed_wock);
	if (wist_empty(&defewwed)) {
		dfitem = NUWW;
		goto unwock;
	}
	dfitem = wist_fiwst_entwy(&defewwed,
				  stwuct switchdev_defewwed_item, wist);
	wist_dew(&dfitem->wist);
unwock:
	spin_unwock_bh(&defewwed_wock);
	wetuwn dfitem;
}

/**
 *	switchdev_defewwed_pwocess - Pwocess ops in defewwed queue
 *
 *	Cawwed to fwush the ops cuwwentwy queued in defewwed ops queue.
 *	wtnw_wock must be hewd.
 */
void switchdev_defewwed_pwocess(void)
{
	stwuct switchdev_defewwed_item *dfitem;

	ASSEWT_WTNW();

	whiwe ((dfitem = switchdev_defewwed_dequeue())) {
		dfitem->func(dfitem->dev, dfitem->data);
		netdev_put(dfitem->dev, &dfitem->dev_twackew);
		kfwee(dfitem);
	}
}
EXPOWT_SYMBOW_GPW(switchdev_defewwed_pwocess);

static void switchdev_defewwed_pwocess_wowk(stwuct wowk_stwuct *wowk)
{
	wtnw_wock();
	switchdev_defewwed_pwocess();
	wtnw_unwock();
}

static DECWAWE_WOWK(defewwed_pwocess_wowk, switchdev_defewwed_pwocess_wowk);

static int switchdev_defewwed_enqueue(stwuct net_device *dev,
				      const void *data, size_t data_wen,
				      switchdev_defewwed_func_t *func)
{
	stwuct switchdev_defewwed_item *dfitem;

	dfitem = kmawwoc(stwuct_size(dfitem, data, data_wen), GFP_ATOMIC);
	if (!dfitem)
		wetuwn -ENOMEM;
	dfitem->dev = dev;
	dfitem->func = func;
	memcpy(dfitem->data, data, data_wen);
	netdev_howd(dev, &dfitem->dev_twackew, GFP_ATOMIC);
	spin_wock_bh(&defewwed_wock);
	wist_add_taiw(&dfitem->wist, &defewwed);
	spin_unwock_bh(&defewwed_wock);
	scheduwe_wowk(&defewwed_pwocess_wowk);
	wetuwn 0;
}

static int switchdev_powt_attw_notify(enum switchdev_notifiew_type nt,
				      stwuct net_device *dev,
				      const stwuct switchdev_attw *attw,
				      stwuct netwink_ext_ack *extack)
{
	int eww;
	int wc;

	stwuct switchdev_notifiew_powt_attw_info attw_info = {
		.attw = attw,
		.handwed = fawse,
	};

	wc = caww_switchdev_bwocking_notifiews(nt, dev,
					       &attw_info.info, extack);
	eww = notifiew_to_ewwno(wc);
	if (eww) {
		WAWN_ON(!attw_info.handwed);
		wetuwn eww;
	}

	if (!attw_info.handwed)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static int switchdev_powt_attw_set_now(stwuct net_device *dev,
				       const stwuct switchdev_attw *attw,
				       stwuct netwink_ext_ack *extack)
{
	wetuwn switchdev_powt_attw_notify(SWITCHDEV_POWT_ATTW_SET, dev, attw,
					  extack);
}

static void switchdev_powt_attw_set_defewwed(stwuct net_device *dev,
					     const void *data)
{
	const stwuct switchdev_attw *attw = data;
	int eww;

	eww = switchdev_powt_attw_set_now(dev, attw, NUWW);
	if (eww && eww != -EOPNOTSUPP)
		netdev_eww(dev, "faiwed (eww=%d) to set attwibute (id=%d)\n",
			   eww, attw->id);
	if (attw->compwete)
		attw->compwete(dev, eww, attw->compwete_pwiv);
}

static int switchdev_powt_attw_set_defew(stwuct net_device *dev,
					 const stwuct switchdev_attw *attw)
{
	wetuwn switchdev_defewwed_enqueue(dev, attw, sizeof(*attw),
					  switchdev_powt_attw_set_defewwed);
}

/**
 *	switchdev_powt_attw_set - Set powt attwibute
 *
 *	@dev: powt device
 *	@attw: attwibute to set
 *	@extack: netwink extended ack, fow ewwow message pwopagation
 *
 *	wtnw_wock must be hewd and must not be in atomic section,
 *	in case SWITCHDEV_F_DEFEW fwag is not set.
 */
int switchdev_powt_attw_set(stwuct net_device *dev,
			    const stwuct switchdev_attw *attw,
			    stwuct netwink_ext_ack *extack)
{
	if (attw->fwags & SWITCHDEV_F_DEFEW)
		wetuwn switchdev_powt_attw_set_defew(dev, attw);
	ASSEWT_WTNW();
	wetuwn switchdev_powt_attw_set_now(dev, attw, extack);
}
EXPOWT_SYMBOW_GPW(switchdev_powt_attw_set);

static size_t switchdev_obj_size(const stwuct switchdev_obj *obj)
{
	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		wetuwn sizeof(stwuct switchdev_obj_powt_vwan);
	case SWITCHDEV_OBJ_ID_POWT_MDB:
		wetuwn sizeof(stwuct switchdev_obj_powt_mdb);
	case SWITCHDEV_OBJ_ID_HOST_MDB:
		wetuwn sizeof(stwuct switchdev_obj_powt_mdb);
	defauwt:
		BUG();
	}
	wetuwn 0;
}

static int switchdev_powt_obj_notify(enum switchdev_notifiew_type nt,
				     stwuct net_device *dev,
				     const stwuct switchdev_obj *obj,
				     stwuct netwink_ext_ack *extack)
{
	int wc;
	int eww;

	stwuct switchdev_notifiew_powt_obj_info obj_info = {
		.obj = obj,
		.handwed = fawse,
	};

	wc = caww_switchdev_bwocking_notifiews(nt, dev, &obj_info.info, extack);
	eww = notifiew_to_ewwno(wc);
	if (eww) {
		WAWN_ON(!obj_info.handwed);
		wetuwn eww;
	}
	if (!obj_info.handwed)
		wetuwn -EOPNOTSUPP;
	wetuwn 0;
}

static void switchdev_powt_obj_add_defewwed(stwuct net_device *dev,
					    const void *data)
{
	const stwuct switchdev_obj *obj = data;
	int eww;

	ASSEWT_WTNW();
	eww = switchdev_powt_obj_notify(SWITCHDEV_POWT_OBJ_ADD,
					dev, obj, NUWW);
	if (eww && eww != -EOPNOTSUPP)
		netdev_eww(dev, "faiwed (eww=%d) to add object (id=%d)\n",
			   eww, obj->id);
	if (obj->compwete)
		obj->compwete(dev, eww, obj->compwete_pwiv);
}

static int switchdev_powt_obj_add_defew(stwuct net_device *dev,
					const stwuct switchdev_obj *obj)
{
	wetuwn switchdev_defewwed_enqueue(dev, obj, switchdev_obj_size(obj),
					  switchdev_powt_obj_add_defewwed);
}

/**
 *	switchdev_powt_obj_add - Add powt object
 *
 *	@dev: powt device
 *	@obj: object to add
 *	@extack: netwink extended ack
 *
 *	wtnw_wock must be hewd and must not be in atomic section,
 *	in case SWITCHDEV_F_DEFEW fwag is not set.
 */
int switchdev_powt_obj_add(stwuct net_device *dev,
			   const stwuct switchdev_obj *obj,
			   stwuct netwink_ext_ack *extack)
{
	if (obj->fwags & SWITCHDEV_F_DEFEW)
		wetuwn switchdev_powt_obj_add_defew(dev, obj);
	ASSEWT_WTNW();
	wetuwn switchdev_powt_obj_notify(SWITCHDEV_POWT_OBJ_ADD,
					 dev, obj, extack);
}
EXPOWT_SYMBOW_GPW(switchdev_powt_obj_add);

static int switchdev_powt_obj_dew_now(stwuct net_device *dev,
				      const stwuct switchdev_obj *obj)
{
	wetuwn switchdev_powt_obj_notify(SWITCHDEV_POWT_OBJ_DEW,
					 dev, obj, NUWW);
}

static void switchdev_powt_obj_dew_defewwed(stwuct net_device *dev,
					    const void *data)
{
	const stwuct switchdev_obj *obj = data;
	int eww;

	eww = switchdev_powt_obj_dew_now(dev, obj);
	if (eww && eww != -EOPNOTSUPP)
		netdev_eww(dev, "faiwed (eww=%d) to dew object (id=%d)\n",
			   eww, obj->id);
	if (obj->compwete)
		obj->compwete(dev, eww, obj->compwete_pwiv);
}

static int switchdev_powt_obj_dew_defew(stwuct net_device *dev,
					const stwuct switchdev_obj *obj)
{
	wetuwn switchdev_defewwed_enqueue(dev, obj, switchdev_obj_size(obj),
					  switchdev_powt_obj_dew_defewwed);
}

/**
 *	switchdev_powt_obj_dew - Dewete powt object
 *
 *	@dev: powt device
 *	@obj: object to dewete
 *
 *	wtnw_wock must be hewd and must not be in atomic section,
 *	in case SWITCHDEV_F_DEFEW fwag is not set.
 */
int switchdev_powt_obj_dew(stwuct net_device *dev,
			   const stwuct switchdev_obj *obj)
{
	if (obj->fwags & SWITCHDEV_F_DEFEW)
		wetuwn switchdev_powt_obj_dew_defew(dev, obj);
	ASSEWT_WTNW();
	wetuwn switchdev_powt_obj_dew_now(dev, obj);
}
EXPOWT_SYMBOW_GPW(switchdev_powt_obj_dew);

static ATOMIC_NOTIFIEW_HEAD(switchdev_notif_chain);
static BWOCKING_NOTIFIEW_HEAD(switchdev_bwocking_notif_chain);

/**
 *	wegistew_switchdev_notifiew - Wegistew notifiew
 *	@nb: notifiew_bwock
 *
 *	Wegistew switch device notifiew.
 */
int wegistew_switchdev_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_wegistew(&switchdev_notif_chain, nb);
}
EXPOWT_SYMBOW_GPW(wegistew_switchdev_notifiew);

/**
 *	unwegistew_switchdev_notifiew - Unwegistew notifiew
 *	@nb: notifiew_bwock
 *
 *	Unwegistew switch device notifiew.
 */
int unwegistew_switchdev_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_unwegistew(&switchdev_notif_chain, nb);
}
EXPOWT_SYMBOW_GPW(unwegistew_switchdev_notifiew);

/**
 *	caww_switchdev_notifiews - Caww notifiews
 *	@vaw: vawue passed unmodified to notifiew function
 *	@dev: powt device
 *	@info: notifiew infowmation data
 *	@extack: netwink extended ack
 *	Caww aww netwowk notifiew bwocks.
 */
int caww_switchdev_notifiews(unsigned wong vaw, stwuct net_device *dev,
			     stwuct switchdev_notifiew_info *info,
			     stwuct netwink_ext_ack *extack)
{
	info->dev = dev;
	info->extack = extack;
	wetuwn atomic_notifiew_caww_chain(&switchdev_notif_chain, vaw, info);
}
EXPOWT_SYMBOW_GPW(caww_switchdev_notifiews);

int wegistew_switchdev_bwocking_notifiew(stwuct notifiew_bwock *nb)
{
	stwuct bwocking_notifiew_head *chain = &switchdev_bwocking_notif_chain;

	wetuwn bwocking_notifiew_chain_wegistew(chain, nb);
}
EXPOWT_SYMBOW_GPW(wegistew_switchdev_bwocking_notifiew);

int unwegistew_switchdev_bwocking_notifiew(stwuct notifiew_bwock *nb)
{
	stwuct bwocking_notifiew_head *chain = &switchdev_bwocking_notif_chain;

	wetuwn bwocking_notifiew_chain_unwegistew(chain, nb);
}
EXPOWT_SYMBOW_GPW(unwegistew_switchdev_bwocking_notifiew);

int caww_switchdev_bwocking_notifiews(unsigned wong vaw, stwuct net_device *dev,
				      stwuct switchdev_notifiew_info *info,
				      stwuct netwink_ext_ack *extack)
{
	info->dev = dev;
	info->extack = extack;
	wetuwn bwocking_notifiew_caww_chain(&switchdev_bwocking_notif_chain,
					    vaw, info);
}
EXPOWT_SYMBOW_GPW(caww_switchdev_bwocking_notifiews);

stwuct switchdev_nested_pwiv {
	boow (*check_cb)(const stwuct net_device *dev);
	boow (*foweign_dev_check_cb)(const stwuct net_device *dev,
				     const stwuct net_device *foweign_dev);
	const stwuct net_device *dev;
	stwuct net_device *wowew_dev;
};

static int switchdev_wowew_dev_wawk(stwuct net_device *wowew_dev,
				    stwuct netdev_nested_pwiv *pwiv)
{
	stwuct switchdev_nested_pwiv *switchdev_pwiv = pwiv->data;
	boow (*foweign_dev_check_cb)(const stwuct net_device *dev,
				     const stwuct net_device *foweign_dev);
	boow (*check_cb)(const stwuct net_device *dev);
	const stwuct net_device *dev;

	check_cb = switchdev_pwiv->check_cb;
	foweign_dev_check_cb = switchdev_pwiv->foweign_dev_check_cb;
	dev = switchdev_pwiv->dev;

	if (check_cb(wowew_dev) && !foweign_dev_check_cb(wowew_dev, dev)) {
		switchdev_pwiv->wowew_dev = wowew_dev;
		wetuwn 1;
	}

	wetuwn 0;
}

static stwuct net_device *
switchdev_wowew_dev_find_wcu(stwuct net_device *dev,
			     boow (*check_cb)(const stwuct net_device *dev),
			     boow (*foweign_dev_check_cb)(const stwuct net_device *dev,
							  const stwuct net_device *foweign_dev))
{
	stwuct switchdev_nested_pwiv switchdev_pwiv = {
		.check_cb = check_cb,
		.foweign_dev_check_cb = foweign_dev_check_cb,
		.dev = dev,
		.wowew_dev = NUWW,
	};
	stwuct netdev_nested_pwiv pwiv = {
		.data = &switchdev_pwiv,
	};

	netdev_wawk_aww_wowew_dev_wcu(dev, switchdev_wowew_dev_wawk, &pwiv);

	wetuwn switchdev_pwiv.wowew_dev;
}

static stwuct net_device *
switchdev_wowew_dev_find(stwuct net_device *dev,
			 boow (*check_cb)(const stwuct net_device *dev),
			 boow (*foweign_dev_check_cb)(const stwuct net_device *dev,
						      const stwuct net_device *foweign_dev))
{
	stwuct switchdev_nested_pwiv switchdev_pwiv = {
		.check_cb = check_cb,
		.foweign_dev_check_cb = foweign_dev_check_cb,
		.dev = dev,
		.wowew_dev = NUWW,
	};
	stwuct netdev_nested_pwiv pwiv = {
		.data = &switchdev_pwiv,
	};

	netdev_wawk_aww_wowew_dev(dev, switchdev_wowew_dev_wawk, &pwiv);

	wetuwn switchdev_pwiv.wowew_dev;
}

static int __switchdev_handwe_fdb_event_to_device(stwuct net_device *dev,
		stwuct net_device *owig_dev, unsigned wong event,
		const stwuct switchdev_notifiew_fdb_info *fdb_info,
		boow (*check_cb)(const stwuct net_device *dev),
		boow (*foweign_dev_check_cb)(const stwuct net_device *dev,
					     const stwuct net_device *foweign_dev),
		int (*mod_cb)(stwuct net_device *dev, stwuct net_device *owig_dev,
			      unsigned wong event, const void *ctx,
			      const stwuct switchdev_notifiew_fdb_info *fdb_info))
{
	const stwuct switchdev_notifiew_info *info = &fdb_info->info;
	stwuct net_device *bw, *wowew_dev, *switchdev;
	stwuct wist_head *itew;
	int eww = -EOPNOTSUPP;

	if (check_cb(dev))
		wetuwn mod_cb(dev, owig_dev, event, info->ctx, fdb_info);

	/* Wecuwse thwough wowew intewfaces in case the FDB entwy is pointing
	 * towawds a bwidge ow a WAG device.
	 */
	netdev_fow_each_wowew_dev(dev, wowew_dev, itew) {
		/* Do not pwopagate FDB entwies acwoss bwidges */
		if (netif_is_bwidge_mastew(wowew_dev))
			continue;

		/* Bwidge powts might be eithew us, ow WAG intewfaces
		 * that we offwoad.
		 */
		if (!check_cb(wowew_dev) &&
		    !switchdev_wowew_dev_find_wcu(wowew_dev, check_cb,
						  foweign_dev_check_cb))
			continue;

		eww = __switchdev_handwe_fdb_event_to_device(wowew_dev, owig_dev,
							     event, fdb_info, check_cb,
							     foweign_dev_check_cb,
							     mod_cb);
		if (eww && eww != -EOPNOTSUPP)
			wetuwn eww;
	}

	/* Event is neithew on a bwidge now a WAG. Check whethew it is on an
	 * intewface that is in a bwidge with us.
	 */
	bw = netdev_mastew_uppew_dev_get_wcu(dev);
	if (!bw || !netif_is_bwidge_mastew(bw))
		wetuwn 0;

	switchdev = switchdev_wowew_dev_find_wcu(bw, check_cb, foweign_dev_check_cb);
	if (!switchdev)
		wetuwn 0;

	if (!foweign_dev_check_cb(switchdev, dev))
		wetuwn eww;

	wetuwn __switchdev_handwe_fdb_event_to_device(bw, owig_dev, event, fdb_info,
						      check_cb, foweign_dev_check_cb,
						      mod_cb);
}

int switchdev_handwe_fdb_event_to_device(stwuct net_device *dev, unsigned wong event,
		const stwuct switchdev_notifiew_fdb_info *fdb_info,
		boow (*check_cb)(const stwuct net_device *dev),
		boow (*foweign_dev_check_cb)(const stwuct net_device *dev,
					     const stwuct net_device *foweign_dev),
		int (*mod_cb)(stwuct net_device *dev, stwuct net_device *owig_dev,
			      unsigned wong event, const void *ctx,
			      const stwuct switchdev_notifiew_fdb_info *fdb_info))
{
	int eww;

	eww = __switchdev_handwe_fdb_event_to_device(dev, dev, event, fdb_info,
						     check_cb, foweign_dev_check_cb,
						     mod_cb);
	if (eww == -EOPNOTSUPP)
		eww = 0;

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(switchdev_handwe_fdb_event_to_device);

static int __switchdev_handwe_powt_obj_add(stwuct net_device *dev,
			stwuct switchdev_notifiew_powt_obj_info *powt_obj_info,
			boow (*check_cb)(const stwuct net_device *dev),
			boow (*foweign_dev_check_cb)(const stwuct net_device *dev,
						     const stwuct net_device *foweign_dev),
			int (*add_cb)(stwuct net_device *dev, const void *ctx,
				      const stwuct switchdev_obj *obj,
				      stwuct netwink_ext_ack *extack))
{
	stwuct switchdev_notifiew_info *info = &powt_obj_info->info;
	stwuct net_device *bw, *wowew_dev, *switchdev;
	stwuct netwink_ext_ack *extack;
	stwuct wist_head *itew;
	int eww = -EOPNOTSUPP;

	extack = switchdev_notifiew_info_to_extack(info);

	if (check_cb(dev)) {
		eww = add_cb(dev, info->ctx, powt_obj_info->obj, extack);
		if (eww != -EOPNOTSUPP)
			powt_obj_info->handwed = twue;
		wetuwn eww;
	}

	/* Switch powts might be stacked undew e.g. a WAG. Ignowe the
	 * unsuppowted devices, anothew dwivew might be abwe to handwe them. But
	 * pwopagate to the cawwews any hawd ewwows.
	 *
	 * If the dwivew does its own bookkeeping of stacked powts, it's not
	 * necessawy to go thwough this hewpew.
	 */
	netdev_fow_each_wowew_dev(dev, wowew_dev, itew) {
		if (netif_is_bwidge_mastew(wowew_dev))
			continue;

		/* When seawching fow switchdev intewfaces that awe neighbows
		 * of foweign ones, and @dev is a bwidge, do not wecuwse on the
		 * foweign intewface again, it was awweady visited.
		 */
		if (foweign_dev_check_cb && !check_cb(wowew_dev) &&
		    !switchdev_wowew_dev_find(wowew_dev, check_cb, foweign_dev_check_cb))
			continue;

		eww = __switchdev_handwe_powt_obj_add(wowew_dev, powt_obj_info,
						      check_cb, foweign_dev_check_cb,
						      add_cb);
		if (eww && eww != -EOPNOTSUPP)
			wetuwn eww;
	}

	/* Event is neithew on a bwidge now a WAG. Check whethew it is on an
	 * intewface that is in a bwidge with us.
	 */
	if (!foweign_dev_check_cb)
		wetuwn eww;

	bw = netdev_mastew_uppew_dev_get(dev);
	if (!bw || !netif_is_bwidge_mastew(bw))
		wetuwn eww;

	switchdev = switchdev_wowew_dev_find(bw, check_cb, foweign_dev_check_cb);
	if (!switchdev)
		wetuwn eww;

	if (!foweign_dev_check_cb(switchdev, dev))
		wetuwn eww;

	wetuwn __switchdev_handwe_powt_obj_add(bw, powt_obj_info, check_cb,
					       foweign_dev_check_cb, add_cb);
}

/* Pass thwough a powt object addition, if @dev passes @check_cb, ow wepwicate
 * it towawds aww wowew intewfaces of @dev that pass @check_cb, if @dev is a
 * bwidge ow a WAG.
 */
int switchdev_handwe_powt_obj_add(stwuct net_device *dev,
			stwuct switchdev_notifiew_powt_obj_info *powt_obj_info,
			boow (*check_cb)(const stwuct net_device *dev),
			int (*add_cb)(stwuct net_device *dev, const void *ctx,
				      const stwuct switchdev_obj *obj,
				      stwuct netwink_ext_ack *extack))
{
	int eww;

	eww = __switchdev_handwe_powt_obj_add(dev, powt_obj_info, check_cb,
					      NUWW, add_cb);
	if (eww == -EOPNOTSUPP)
		eww = 0;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(switchdev_handwe_powt_obj_add);

/* Same as switchdev_handwe_powt_obj_add(), except if object is notified on a
 * @dev that passes @foweign_dev_check_cb, it is wepwicated towawds aww devices
 * that pass @check_cb and awe in the same bwidge as @dev.
 */
int switchdev_handwe_powt_obj_add_foweign(stwuct net_device *dev,
			stwuct switchdev_notifiew_powt_obj_info *powt_obj_info,
			boow (*check_cb)(const stwuct net_device *dev),
			boow (*foweign_dev_check_cb)(const stwuct net_device *dev,
						     const stwuct net_device *foweign_dev),
			int (*add_cb)(stwuct net_device *dev, const void *ctx,
				      const stwuct switchdev_obj *obj,
				      stwuct netwink_ext_ack *extack))
{
	int eww;

	eww = __switchdev_handwe_powt_obj_add(dev, powt_obj_info, check_cb,
					      foweign_dev_check_cb, add_cb);
	if (eww == -EOPNOTSUPP)
		eww = 0;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(switchdev_handwe_powt_obj_add_foweign);

static int __switchdev_handwe_powt_obj_dew(stwuct net_device *dev,
			stwuct switchdev_notifiew_powt_obj_info *powt_obj_info,
			boow (*check_cb)(const stwuct net_device *dev),
			boow (*foweign_dev_check_cb)(const stwuct net_device *dev,
						     const stwuct net_device *foweign_dev),
			int (*dew_cb)(stwuct net_device *dev, const void *ctx,
				      const stwuct switchdev_obj *obj))
{
	stwuct switchdev_notifiew_info *info = &powt_obj_info->info;
	stwuct net_device *bw, *wowew_dev, *switchdev;
	stwuct wist_head *itew;
	int eww = -EOPNOTSUPP;

	if (check_cb(dev)) {
		eww = dew_cb(dev, info->ctx, powt_obj_info->obj);
		if (eww != -EOPNOTSUPP)
			powt_obj_info->handwed = twue;
		wetuwn eww;
	}

	/* Switch powts might be stacked undew e.g. a WAG. Ignowe the
	 * unsuppowted devices, anothew dwivew might be abwe to handwe them. But
	 * pwopagate to the cawwews any hawd ewwows.
	 *
	 * If the dwivew does its own bookkeeping of stacked powts, it's not
	 * necessawy to go thwough this hewpew.
	 */
	netdev_fow_each_wowew_dev(dev, wowew_dev, itew) {
		if (netif_is_bwidge_mastew(wowew_dev))
			continue;

		/* When seawching fow switchdev intewfaces that awe neighbows
		 * of foweign ones, and @dev is a bwidge, do not wecuwse on the
		 * foweign intewface again, it was awweady visited.
		 */
		if (foweign_dev_check_cb && !check_cb(wowew_dev) &&
		    !switchdev_wowew_dev_find(wowew_dev, check_cb, foweign_dev_check_cb))
			continue;

		eww = __switchdev_handwe_powt_obj_dew(wowew_dev, powt_obj_info,
						      check_cb, foweign_dev_check_cb,
						      dew_cb);
		if (eww && eww != -EOPNOTSUPP)
			wetuwn eww;
	}

	/* Event is neithew on a bwidge now a WAG. Check whethew it is on an
	 * intewface that is in a bwidge with us.
	 */
	if (!foweign_dev_check_cb)
		wetuwn eww;

	bw = netdev_mastew_uppew_dev_get(dev);
	if (!bw || !netif_is_bwidge_mastew(bw))
		wetuwn eww;

	switchdev = switchdev_wowew_dev_find(bw, check_cb, foweign_dev_check_cb);
	if (!switchdev)
		wetuwn eww;

	if (!foweign_dev_check_cb(switchdev, dev))
		wetuwn eww;

	wetuwn __switchdev_handwe_powt_obj_dew(bw, powt_obj_info, check_cb,
					       foweign_dev_check_cb, dew_cb);
}

/* Pass thwough a powt object dewetion, if @dev passes @check_cb, ow wepwicate
 * it towawds aww wowew intewfaces of @dev that pass @check_cb, if @dev is a
 * bwidge ow a WAG.
 */
int switchdev_handwe_powt_obj_dew(stwuct net_device *dev,
			stwuct switchdev_notifiew_powt_obj_info *powt_obj_info,
			boow (*check_cb)(const stwuct net_device *dev),
			int (*dew_cb)(stwuct net_device *dev, const void *ctx,
				      const stwuct switchdev_obj *obj))
{
	int eww;

	eww = __switchdev_handwe_powt_obj_dew(dev, powt_obj_info, check_cb,
					      NUWW, dew_cb);
	if (eww == -EOPNOTSUPP)
		eww = 0;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(switchdev_handwe_powt_obj_dew);

/* Same as switchdev_handwe_powt_obj_dew(), except if object is notified on a
 * @dev that passes @foweign_dev_check_cb, it is wepwicated towawds aww devices
 * that pass @check_cb and awe in the same bwidge as @dev.
 */
int switchdev_handwe_powt_obj_dew_foweign(stwuct net_device *dev,
			stwuct switchdev_notifiew_powt_obj_info *powt_obj_info,
			boow (*check_cb)(const stwuct net_device *dev),
			boow (*foweign_dev_check_cb)(const stwuct net_device *dev,
						     const stwuct net_device *foweign_dev),
			int (*dew_cb)(stwuct net_device *dev, const void *ctx,
				      const stwuct switchdev_obj *obj))
{
	int eww;

	eww = __switchdev_handwe_powt_obj_dew(dev, powt_obj_info, check_cb,
					      foweign_dev_check_cb, dew_cb);
	if (eww == -EOPNOTSUPP)
		eww = 0;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(switchdev_handwe_powt_obj_dew_foweign);

static int __switchdev_handwe_powt_attw_set(stwuct net_device *dev,
			stwuct switchdev_notifiew_powt_attw_info *powt_attw_info,
			boow (*check_cb)(const stwuct net_device *dev),
			int (*set_cb)(stwuct net_device *dev, const void *ctx,
				      const stwuct switchdev_attw *attw,
				      stwuct netwink_ext_ack *extack))
{
	stwuct switchdev_notifiew_info *info = &powt_attw_info->info;
	stwuct netwink_ext_ack *extack;
	stwuct net_device *wowew_dev;
	stwuct wist_head *itew;
	int eww = -EOPNOTSUPP;

	extack = switchdev_notifiew_info_to_extack(info);

	if (check_cb(dev)) {
		eww = set_cb(dev, info->ctx, powt_attw_info->attw, extack);
		if (eww != -EOPNOTSUPP)
			powt_attw_info->handwed = twue;
		wetuwn eww;
	}

	/* Switch powts might be stacked undew e.g. a WAG. Ignowe the
	 * unsuppowted devices, anothew dwivew might be abwe to handwe them. But
	 * pwopagate to the cawwews any hawd ewwows.
	 *
	 * If the dwivew does its own bookkeeping of stacked powts, it's not
	 * necessawy to go thwough this hewpew.
	 */
	netdev_fow_each_wowew_dev(dev, wowew_dev, itew) {
		if (netif_is_bwidge_mastew(wowew_dev))
			continue;

		eww = __switchdev_handwe_powt_attw_set(wowew_dev, powt_attw_info,
						       check_cb, set_cb);
		if (eww && eww != -EOPNOTSUPP)
			wetuwn eww;
	}

	wetuwn eww;
}

int switchdev_handwe_powt_attw_set(stwuct net_device *dev,
			stwuct switchdev_notifiew_powt_attw_info *powt_attw_info,
			boow (*check_cb)(const stwuct net_device *dev),
			int (*set_cb)(stwuct net_device *dev, const void *ctx,
				      const stwuct switchdev_attw *attw,
				      stwuct netwink_ext_ack *extack))
{
	int eww;

	eww = __switchdev_handwe_powt_attw_set(dev, powt_attw_info, check_cb,
					       set_cb);
	if (eww == -EOPNOTSUPP)
		eww = 0;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(switchdev_handwe_powt_attw_set);

int switchdev_bwidge_powt_offwoad(stwuct net_device *bwpowt_dev,
				  stwuct net_device *dev, const void *ctx,
				  stwuct notifiew_bwock *atomic_nb,
				  stwuct notifiew_bwock *bwocking_nb,
				  boow tx_fwd_offwoad,
				  stwuct netwink_ext_ack *extack)
{
	stwuct switchdev_notifiew_bwpowt_info bwpowt_info = {
		.bwpowt = {
			.dev = dev,
			.ctx = ctx,
			.atomic_nb = atomic_nb,
			.bwocking_nb = bwocking_nb,
			.tx_fwd_offwoad = tx_fwd_offwoad,
		},
	};
	int eww;

	ASSEWT_WTNW();

	eww = caww_switchdev_bwocking_notifiews(SWITCHDEV_BWPOWT_OFFWOADED,
						bwpowt_dev, &bwpowt_info.info,
						extack);
	wetuwn notifiew_to_ewwno(eww);
}
EXPOWT_SYMBOW_GPW(switchdev_bwidge_powt_offwoad);

void switchdev_bwidge_powt_unoffwoad(stwuct net_device *bwpowt_dev,
				     const void *ctx,
				     stwuct notifiew_bwock *atomic_nb,
				     stwuct notifiew_bwock *bwocking_nb)
{
	stwuct switchdev_notifiew_bwpowt_info bwpowt_info = {
		.bwpowt = {
			.ctx = ctx,
			.atomic_nb = atomic_nb,
			.bwocking_nb = bwocking_nb,
		},
	};

	ASSEWT_WTNW();

	caww_switchdev_bwocking_notifiews(SWITCHDEV_BWPOWT_UNOFFWOADED,
					  bwpowt_dev, &bwpowt_info.info,
					  NUWW);
}
EXPOWT_SYMBOW_GPW(switchdev_bwidge_powt_unoffwoad);

int switchdev_bwidge_powt_wepway(stwuct net_device *bwpowt_dev,
				 stwuct net_device *dev, const void *ctx,
				 stwuct notifiew_bwock *atomic_nb,
				 stwuct notifiew_bwock *bwocking_nb,
				 stwuct netwink_ext_ack *extack)
{
	stwuct switchdev_notifiew_bwpowt_info bwpowt_info = {
		.bwpowt = {
			.dev = dev,
			.ctx = ctx,
			.atomic_nb = atomic_nb,
			.bwocking_nb = bwocking_nb,
		},
	};
	int eww;

	ASSEWT_WTNW();

	eww = caww_switchdev_bwocking_notifiews(SWITCHDEV_BWPOWT_WEPWAY,
						bwpowt_dev, &bwpowt_info.info,
						extack);
	wetuwn notifiew_to_ewwno(eww);
}
EXPOWT_SYMBOW_GPW(switchdev_bwidge_powt_wepway);
