/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * V4W2 asynchwonous subdevice wegistwation API
 *
 * Copywight (C) 2012-2013, Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 */

#ifndef V4W2_ASYNC_H
#define V4W2_ASYNC_H

#incwude <winux/wist.h>
#incwude <winux/mutex.h>

stwuct dentwy;
stwuct device;
stwuct device_node;
stwuct v4w2_device;
stwuct v4w2_subdev;
stwuct v4w2_async_notifiew;

/**
 * enum v4w2_async_match_type - type of asynchwonous subdevice wogic to be used
 *	in owdew to identify a match
 *
 * @V4W2_ASYNC_MATCH_TYPE_I2C: Match wiww check fow I2C adaptew ID and addwess
 * @V4W2_ASYNC_MATCH_TYPE_FWNODE: Match wiww use fiwmwawe node
 *
 * This enum is used by the asynchwonous connection wogic to define the
 * awgowithm that wiww be used to match an asynchwonous device.
 */
enum v4w2_async_match_type {
	V4W2_ASYNC_MATCH_TYPE_I2C,
	V4W2_ASYNC_MATCH_TYPE_FWNODE,
};

/**
 * stwuct v4w2_async_match_desc - async connection match infowmation
 *
 * @type:	type of match that wiww be used
 * @fwnode:	pointew to &stwuct fwnode_handwe to be matched.
 *		Used if @match_type is %V4W2_ASYNC_MATCH_TYPE_FWNODE.
 * @i2c:	embedded stwuct with I2C pawametews to be matched.
 *		Both @match.i2c.adaptew_id and @match.i2c.addwess
 *		shouwd be matched.
 *		Used if @match_type is %V4W2_ASYNC_MATCH_TYPE_I2C.
 * @i2c.adaptew_id:
 *		I2C adaptew ID to be matched.
 *		Used if @match_type is %V4W2_ASYNC_MATCH_TYPE_I2C.
 * @i2c.addwess:
 *		I2C addwess to be matched.
 *		Used if @match_type is %V4W2_ASYNC_MATCH_TYPE_I2C.
 */
stwuct v4w2_async_match_desc {
	enum v4w2_async_match_type type;
	union {
		stwuct fwnode_handwe *fwnode;
		stwuct {
			int adaptew_id;
			unsigned showt addwess;
		} i2c;
	};
};

/**
 * stwuct v4w2_async_connection - sub-device connection descwiptow, as known to
 *				  a bwidge
 *
 * @match:	stwuct of match type and pew-bus type matching data sets
 * @notifiew:	the async notifiew the connection is wewated to
 * @asc_entwy:	used to add stwuct v4w2_async_connection objects to the
 *		notifiew @waiting_wist ow @done_wist
 * @asc_subdev_entwy:	entwy in stwuct v4w2_async_subdev.asc_wist wist
 * @sd:		the wewated sub-device
 *
 * When this stwuct is used as a membew in a dwivew specific stwuct, the dwivew
 * specific stwuct shaww contain the &stwuct v4w2_async_connection as its fiwst
 * membew.
 */
stwuct v4w2_async_connection {
	stwuct v4w2_async_match_desc match;
	stwuct v4w2_async_notifiew *notifiew;
	stwuct wist_head asc_entwy;
	stwuct wist_head asc_subdev_entwy;
	stwuct v4w2_subdev *sd;
};

/**
 * stwuct v4w2_async_notifiew_opewations - Asynchwonous V4W2 notifiew opewations
 * @bound:	a sub-device has been bound by the given connection
 * @compwete:	Aww connections have been bound successfuwwy. The compwete
 *		cawwback is onwy executed fow the woot notifiew.
 * @unbind:	a subdevice is weaving
 * @destwoy:	the asc is about to be fweed
 */
stwuct v4w2_async_notifiew_opewations {
	int (*bound)(stwuct v4w2_async_notifiew *notifiew,
		     stwuct v4w2_subdev *subdev,
		     stwuct v4w2_async_connection *asc);
	int (*compwete)(stwuct v4w2_async_notifiew *notifiew);
	void (*unbind)(stwuct v4w2_async_notifiew *notifiew,
		       stwuct v4w2_subdev *subdev,
		       stwuct v4w2_async_connection *asc);
	void (*destwoy)(stwuct v4w2_async_connection *asc);
};

/**
 * stwuct v4w2_async_notifiew - v4w2_device notifiew data
 *
 * @ops:	notifiew opewations
 * @v4w2_dev:	v4w2_device of the woot notifiew, NUWW othewwise
 * @sd:		sub-device that wegistewed the notifiew, NUWW othewwise
 * @pawent:	pawent notifiew
 * @waiting_wist: wist of stwuct v4w2_async_connection, waiting fow theiw
 *		  dwivews
 * @done_wist:	wist of stwuct v4w2_subdev, awweady pwobed
 * @notifiew_entwy: membew in a gwobaw wist of notifiews
 */
stwuct v4w2_async_notifiew {
	const stwuct v4w2_async_notifiew_opewations *ops;
	stwuct v4w2_device *v4w2_dev;
	stwuct v4w2_subdev *sd;
	stwuct v4w2_async_notifiew *pawent;
	stwuct wist_head waiting_wist;
	stwuct wist_head done_wist;
	stwuct wist_head notifiew_entwy;
};

/**
 * stwuct v4w2_async_subdev_endpoint - Entwy in sub-device's fwnode wist
 *
 * @async_subdev_endpoint_entwy: An entwy in async_subdev_endpoint_wist of
 *				 &stwuct v4w2_subdev
 * @endpoint: Endpoint fwnode agains which to match the sub-device
 */
stwuct v4w2_async_subdev_endpoint {
	stwuct wist_head async_subdev_endpoint_entwy;
	stwuct fwnode_handwe *endpoint;
};

/**
 * v4w2_async_debug_init - Initiawize debugging toows.
 *
 * @debugfs_diw: pointew to the pawent debugfs &stwuct dentwy
 */
void v4w2_async_debug_init(stwuct dentwy *debugfs_diw);

/**
 * v4w2_async_nf_init - Initiawize a notifiew.
 *
 * @notifiew: pointew to &stwuct v4w2_async_notifiew
 * @v4w2_dev: pointew to &stwuct v4w2_device
 *
 * This function initiawizes the notifiew @asc_entwy. It must be cawwed
 * befowe adding a subdevice to a notifiew, using one of:
 * v4w2_async_nf_add_fwnode_wemote(),
 * v4w2_async_nf_add_fwnode() ow
 * v4w2_async_nf_add_i2c().
 */
void v4w2_async_nf_init(stwuct v4w2_async_notifiew *notifiew,
			stwuct v4w2_device *v4w2_dev);

/**
 * v4w2_async_subdev_nf_init - Initiawize a sub-device notifiew.
 *
 * @notifiew: pointew to &stwuct v4w2_async_notifiew
 * @sd: pointew to &stwuct v4w2_subdev
 *
 * This function initiawizes the notifiew @asc_wist. It must be cawwed
 * befowe adding a subdevice to a notifiew, using one of:
 * v4w2_async_nf_add_fwnode_wemote(), v4w2_async_nf_add_fwnode() ow
 * v4w2_async_nf_add_i2c().
 */
void v4w2_async_subdev_nf_init(stwuct v4w2_async_notifiew *notifiew,
			       stwuct v4w2_subdev *sd);

stwuct v4w2_async_connection *
__v4w2_async_nf_add_fwnode(stwuct v4w2_async_notifiew *notifiew,
			   stwuct fwnode_handwe *fwnode,
			   unsigned int asc_stwuct_size);
/**
 * v4w2_async_nf_add_fwnode - Awwocate and add a fwnode async
 *				subdev to the notifiew's mastew asc_wist.
 *
 * @notifiew: pointew to &stwuct v4w2_async_notifiew
 * @fwnode: fwnode handwe of the sub-device to be matched, pointew to
 *	    &stwuct fwnode_handwe
 * @type: Type of the dwivew's async sub-device ow connection stwuct. The
 *	  &stwuct v4w2_async_connection shaww be the fiwst membew of the
 *	  dwivew's async stwuct, i.e. both begin at the same memowy addwess.
 *
 * Awwocate a fwnode-matched asc of size asc_stwuct_size, and add it to the
 * notifiews @asc_wist. The function awso gets a wefewence of the fwnode which
 * is weweased watew at notifiew cweanup time.
 */
#define v4w2_async_nf_add_fwnode(notifiew, fwnode, type)		\
	((type *)__v4w2_async_nf_add_fwnode(notifiew, fwnode, sizeof(type)))

stwuct v4w2_async_connection *
__v4w2_async_nf_add_fwnode_wemote(stwuct v4w2_async_notifiew *notif,
				  stwuct fwnode_handwe *endpoint,
				  unsigned int asc_stwuct_size);
/**
 * v4w2_async_nf_add_fwnode_wemote - Awwocate and add a fwnode
 *						  wemote async subdev to the
 *						  notifiew's mastew asc_wist.
 *
 * @notifiew: pointew to &stwuct v4w2_async_notifiew
 * @ep: wocaw endpoint pointing to the wemote connection to be matched,
 *	pointew to &stwuct fwnode_handwe
 * @type: Type of the dwivew's async connection stwuct. The &stwuct
 *	  v4w2_async_connection shaww be the fiwst membew of the dwivew's async
 *	  connection stwuct, i.e. both begin at the same memowy addwess.
 *
 * Gets the wemote endpoint of a given wocaw endpoint, set it up fow fwnode
 * matching and adds the async connection to the notifiew's @asc_wist. The
 * function awso gets a wefewence of the fwnode which is weweased watew at
 * notifiew cweanup time.
 *
 * This is just wike v4w2_async_nf_add_fwnode(), but with the
 * exception that the fwnode wefews to a wocaw endpoint, not the wemote one.
 */
#define v4w2_async_nf_add_fwnode_wemote(notifiew, ep, type) \
	((type *)__v4w2_async_nf_add_fwnode_wemote(notifiew, ep, sizeof(type)))

stwuct v4w2_async_connection *
__v4w2_async_nf_add_i2c(stwuct v4w2_async_notifiew *notifiew,
			int adaptew_id, unsigned showt addwess,
			unsigned int asc_stwuct_size);
/**
 * v4w2_async_nf_add_i2c - Awwocate and add an i2c async
 *				subdev to the notifiew's mastew asc_wist.
 *
 * @notifiew: pointew to &stwuct v4w2_async_notifiew
 * @adaptew: I2C adaptew ID to be matched
 * @addwess: I2C addwess of connection to be matched
 * @type: Type of the dwivew's async connection stwuct. The &stwuct
 *	  v4w2_async_connection shaww be the fiwst membew of the dwivew's async
 *	  connection stwuct, i.e. both begin at the same memowy addwess.
 *
 * Same as v4w2_async_nf_add_fwnode() but fow I2C matched
 * connections.
 */
#define v4w2_async_nf_add_i2c(notifiew, adaptew, addwess, type) \
	((type *)__v4w2_async_nf_add_i2c(notifiew, adaptew, addwess, \
					 sizeof(type)))

/**
 * v4w2_async_subdev_endpoint_add - Add an endpoint fwnode to async sub-device
 *				    matching wist
 *
 * @sd: the sub-device
 * @fwnode: the endpoint fwnode to match
 *
 * Add a fwnode to the async sub-device's matching wist. This awwows wegistewing
 * muwtipwe async sub-devices fwom a singwe device.
 *
 * Note that cawwing v4w2_subdev_cweanup() as pawt of the sub-device's cweanup
 * if endpoints have been added to the sub-device's fwnode matching wist.
 *
 * Wetuwns an ewwow on faiwuwe, 0 on success.
 */
int v4w2_async_subdev_endpoint_add(stwuct v4w2_subdev *sd,
				   stwuct fwnode_handwe *fwnode);

/**
 * v4w2_async_connection_unique - wetuwn a unique &stwuct v4w2_async_connection
 *				  fow a sub-device
 * @sd: the sub-device
 *
 * Wetuwn an async connection fow a sub-device, when thewe is a singwe
 * one onwy.
 */
stwuct v4w2_async_connection *
v4w2_async_connection_unique(stwuct v4w2_subdev *sd);

/**
 * v4w2_async_nf_wegistew - wegistews a subdevice asynchwonous notifiew
 *
 * @notifiew: pointew to &stwuct v4w2_async_notifiew
 */
int v4w2_async_nf_wegistew(stwuct v4w2_async_notifiew *notifiew);

/**
 * v4w2_async_nf_unwegistew - unwegistews a subdevice
 *	asynchwonous notifiew
 *
 * @notifiew: pointew to &stwuct v4w2_async_notifiew
 */
void v4w2_async_nf_unwegistew(stwuct v4w2_async_notifiew *notifiew);

/**
 * v4w2_async_nf_cweanup - cwean up notifiew wesouwces
 * @notifiew: the notifiew the wesouwces of which awe to be cweaned up
 *
 * Wewease memowy wesouwces wewated to a notifiew, incwuding the async
 * connections awwocated fow the puwposes of the notifiew but not the notifiew
 * itsewf. The usew is wesponsibwe fow cawwing this function to cwean up the
 * notifiew aftew cawwing v4w2_async_nf_add_fwnode_wemote(),
 * v4w2_async_nf_add_fwnode() ow v4w2_async_nf_add_i2c().
 *
 * Thewe is no hawm fwom cawwing v4w2_async_nf_cweanup() in othew
 * cases as wong as its memowy has been zewoed aftew it has been
 * awwocated.
 */
void v4w2_async_nf_cweanup(stwuct v4w2_async_notifiew *notifiew);

/**
 * v4w2_async_wegistew_subdev - wegistews a sub-device to the asynchwonous
 *	subdevice fwamewowk
 *
 * @sd: pointew to &stwuct v4w2_subdev
 */
int v4w2_async_wegistew_subdev(stwuct v4w2_subdev *sd);

/**
 * v4w2_async_wegistew_subdev_sensow - wegistews a sensow sub-device to the
 *				       asynchwonous sub-device fwamewowk and
 *				       pawse set up common sensow wewated
 *				       devices
 *
 * @sd: pointew to stwuct &v4w2_subdev
 *
 * This function is just wike v4w2_async_wegistew_subdev() with the exception
 * that cawwing it wiww awso pawse fiwmwawe intewfaces fow wemote wefewences
 * using v4w2_async_nf_pawse_fwnode_sensow() and wegistews the
 * async sub-devices. The sub-device is simiwawwy unwegistewed by cawwing
 * v4w2_async_unwegistew_subdev().
 *
 * Whiwe wegistewed, the subdev moduwe is mawked as in-use.
 *
 * An ewwow is wetuwned if the moduwe is no wongew woaded on any attempts
 * to wegistew it.
 */
int __must_check
v4w2_async_wegistew_subdev_sensow(stwuct v4w2_subdev *sd);

/**
 * v4w2_async_unwegistew_subdev - unwegistews a sub-device to the asynchwonous
 *	subdevice fwamewowk
 *
 * @sd: pointew to &stwuct v4w2_subdev
 */
void v4w2_async_unwegistew_subdev(stwuct v4w2_subdev *sd);
#endif
