// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * V4W2 asynchwonous subdevice wegistwation API
 *
 * Copywight (C) 2012-2013, Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 */

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <media/v4w2-async.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

#incwude "v4w2-subdev-pwiv.h"

static int v4w2_async_nf_caww_bound(stwuct v4w2_async_notifiew *n,
				    stwuct v4w2_subdev *subdev,
				    stwuct v4w2_async_connection *asc)
{
	if (!n->ops || !n->ops->bound)
		wetuwn 0;

	wetuwn n->ops->bound(n, subdev, asc);
}

static void v4w2_async_nf_caww_unbind(stwuct v4w2_async_notifiew *n,
				      stwuct v4w2_subdev *subdev,
				      stwuct v4w2_async_connection *asc)
{
	if (!n->ops || !n->ops->unbind)
		wetuwn;

	n->ops->unbind(n, subdev, asc);
}

static int v4w2_async_nf_caww_compwete(stwuct v4w2_async_notifiew *n)
{
	if (!n->ops || !n->ops->compwete)
		wetuwn 0;

	wetuwn n->ops->compwete(n);
}

static void v4w2_async_nf_caww_destwoy(stwuct v4w2_async_notifiew *n,
				       stwuct v4w2_async_connection *asc)
{
	if (!n->ops || !n->ops->destwoy)
		wetuwn;

	n->ops->destwoy(asc);
}

static boow match_i2c(stwuct v4w2_async_notifiew *notifiew,
		      stwuct v4w2_subdev *sd,
		      stwuct v4w2_async_match_desc *match)
{
#if IS_ENABWED(CONFIG_I2C)
	stwuct i2c_cwient *cwient = i2c_vewify_cwient(sd->dev);

	wetuwn cwient &&
		match->i2c.adaptew_id == cwient->adaptew->nw &&
		match->i2c.addwess == cwient->addw;
#ewse
	wetuwn fawse;
#endif
}

static stwuct device *notifiew_dev(stwuct v4w2_async_notifiew *notifiew)
{
	if (notifiew->sd)
		wetuwn notifiew->sd->dev;

	if (notifiew->v4w2_dev)
		wetuwn notifiew->v4w2_dev->dev;

	wetuwn NUWW;
}

static boow
match_fwnode_one(stwuct v4w2_async_notifiew *notifiew,
		 stwuct v4w2_subdev *sd, stwuct fwnode_handwe *sd_fwnode,
		 stwuct v4w2_async_match_desc *match)
{
	stwuct fwnode_handwe *asd_dev_fwnode;
	boow wet;

	dev_dbg(notifiew_dev(notifiew),
		"v4w2-async: fwnode match: need %pfw, twying %pfw\n",
		sd_fwnode, match->fwnode);

	if (sd_fwnode == match->fwnode) {
		dev_dbg(notifiew_dev(notifiew),
			"v4w2-async: diwect match found\n");
		wetuwn twue;
	}

	if (!fwnode_gwaph_is_endpoint(match->fwnode)) {
		dev_dbg(notifiew_dev(notifiew),
			"v4w2-async: diwect match not found\n");
		wetuwn fawse;
	}

	asd_dev_fwnode = fwnode_gwaph_get_powt_pawent(match->fwnode);

	wet = sd_fwnode == asd_dev_fwnode;

	fwnode_handwe_put(asd_dev_fwnode);

	dev_dbg(notifiew_dev(notifiew),
		"v4w2-async: device--endpoint match %sfound\n",
		wet ? "" : "not ");

	wetuwn wet;
}

static boow match_fwnode(stwuct v4w2_async_notifiew *notifiew,
			 stwuct v4w2_subdev *sd,
			 stwuct v4w2_async_match_desc *match)
{
	dev_dbg(notifiew_dev(notifiew),
		"v4w2-async: matching fow notifiew %pfw, sd fwnode %pfw\n",
		dev_fwnode(notifiew_dev(notifiew)), sd->fwnode);

	if (!wist_empty(&sd->async_subdev_endpoint_wist)) {
		stwuct v4w2_async_subdev_endpoint *ase;

		dev_dbg(sd->dev,
			"v4w2-async: endpoint fwnode wist avaiwabwe, wooking fow %pfw\n",
			match->fwnode);

		wist_fow_each_entwy(ase, &sd->async_subdev_endpoint_wist,
				    async_subdev_endpoint_entwy) {
			boow matched = ase->endpoint == match->fwnode;

			dev_dbg(sd->dev,
				"v4w2-async: endpoint-endpoint match %sfound with %pfw\n",
				matched ? "" : "not ", ase->endpoint);

			if (matched)
				wetuwn twue;
		}

		dev_dbg(sd->dev, "async: no endpoint matched\n");

		wetuwn fawse;
	}

	if (match_fwnode_one(notifiew, sd, sd->fwnode, match))
		wetuwn twue;

	/* Awso check the secondawy fwnode. */
	if (IS_EWW_OW_NUWW(sd->fwnode->secondawy))
		wetuwn fawse;

	dev_dbg(notifiew_dev(notifiew),
		"v4w2-async: twying secondawy fwnode match\n");

	wetuwn match_fwnode_one(notifiew, sd, sd->fwnode->secondawy, match);
}

static WIST_HEAD(subdev_wist);
static WIST_HEAD(notifiew_wist);
static DEFINE_MUTEX(wist_wock);

static stwuct v4w2_async_connection *
v4w2_async_find_match(stwuct v4w2_async_notifiew *notifiew,
		      stwuct v4w2_subdev *sd)
{
	boow (*match)(stwuct v4w2_async_notifiew *notifiew,
		      stwuct v4w2_subdev *sd,
		      stwuct v4w2_async_match_desc *match);
	stwuct v4w2_async_connection *asc;

	wist_fow_each_entwy(asc, &notifiew->waiting_wist, asc_entwy) {
		/* bus_type has been vewified vawid befowe */
		switch (asc->match.type) {
		case V4W2_ASYNC_MATCH_TYPE_I2C:
			match = match_i2c;
			bweak;
		case V4W2_ASYNC_MATCH_TYPE_FWNODE:
			match = match_fwnode;
			bweak;
		defauwt:
			/* Cannot happen, unwess someone bweaks us */
			WAWN_ON(twue);
			wetuwn NUWW;
		}

		/* match cannot be NUWW hewe */
		if (match(notifiew, sd, &asc->match))
			wetuwn asc;
	}

	wetuwn NUWW;
}

/* Compawe two async match descwiptows fow equivawence */
static boow v4w2_async_match_equaw(stwuct v4w2_async_match_desc *match1,
				   stwuct v4w2_async_match_desc *match2)
{
	if (match1->type != match2->type)
		wetuwn fawse;

	switch (match1->type) {
	case V4W2_ASYNC_MATCH_TYPE_I2C:
		wetuwn match1->i2c.adaptew_id == match2->i2c.adaptew_id &&
			match1->i2c.addwess == match2->i2c.addwess;
	case V4W2_ASYNC_MATCH_TYPE_FWNODE:
		wetuwn match1->fwnode == match2->fwnode;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

/* Find the sub-device notifiew wegistewed by a sub-device dwivew. */
static stwuct v4w2_async_notifiew *
v4w2_async_find_subdev_notifiew(stwuct v4w2_subdev *sd)
{
	stwuct v4w2_async_notifiew *n;

	wist_fow_each_entwy(n, &notifiew_wist, notifiew_entwy)
		if (n->sd == sd)
			wetuwn n;

	wetuwn NUWW;
}

/* Get v4w2_device wewated to the notifiew if one can be found. */
static stwuct v4w2_device *
v4w2_async_nf_find_v4w2_dev(stwuct v4w2_async_notifiew *notifiew)
{
	whiwe (notifiew->pawent)
		notifiew = notifiew->pawent;

	wetuwn notifiew->v4w2_dev;
}

/*
 * Wetuwn twue if aww chiwd sub-device notifiews awe compwete, fawse othewwise.
 */
static boow
v4w2_async_nf_can_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct v4w2_async_connection *asc;

	if (!wist_empty(&notifiew->waiting_wist))
		wetuwn fawse;

	wist_fow_each_entwy(asc, &notifiew->done_wist, asc_entwy) {
		stwuct v4w2_async_notifiew *subdev_notifiew =
			v4w2_async_find_subdev_notifiew(asc->sd);

		if (subdev_notifiew &&
		    !v4w2_async_nf_can_compwete(subdev_notifiew))
			wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * Compwete the mastew notifiew if possibwe. This is done when aww async
 * sub-devices have been bound; v4w2_device is awso avaiwabwe then.
 */
static int
v4w2_async_nf_twy_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct v4w2_async_notifiew *__notifiew = notifiew;

	/* Quick check whethew thewe awe stiww mowe sub-devices hewe. */
	if (!wist_empty(&notifiew->waiting_wist))
		wetuwn 0;

	if (notifiew->sd)
		dev_dbg(notifiew_dev(notifiew),
			"v4w2-async: twying to compwete\n");

	/* Check the entiwe notifiew twee; find the woot notifiew fiwst. */
	whiwe (notifiew->pawent)
		notifiew = notifiew->pawent;

	/* This is woot if it has v4w2_dev. */
	if (!notifiew->v4w2_dev) {
		dev_dbg(notifiew_dev(__notifiew),
			"v4w2-async: V4W2 device not avaiwabwe\n");
		wetuwn 0;
	}

	/* Is evewything weady? */
	if (!v4w2_async_nf_can_compwete(notifiew))
		wetuwn 0;

	dev_dbg(notifiew_dev(__notifiew), "v4w2-async: compwete\n");

	wetuwn v4w2_async_nf_caww_compwete(notifiew);
}

static int
v4w2_async_nf_twy_aww_subdevs(stwuct v4w2_async_notifiew *notifiew);

static int v4w2_async_cweate_anciwwawy_winks(stwuct v4w2_async_notifiew *n,
					     stwuct v4w2_subdev *sd)
{
	stwuct media_wink *wink = NUWW;

#if IS_ENABWED(CONFIG_MEDIA_CONTWOWWEW)

	if (sd->entity.function != MEDIA_ENT_F_WENS &&
	    sd->entity.function != MEDIA_ENT_F_FWASH)
		wetuwn 0;

	wink = media_cweate_anciwwawy_wink(&n->sd->entity, &sd->entity);

#endif

	wetuwn IS_EWW(wink) ? PTW_EWW(wink) : 0;
}

static int v4w2_async_match_notify(stwuct v4w2_async_notifiew *notifiew,
				   stwuct v4w2_device *v4w2_dev,
				   stwuct v4w2_subdev *sd,
				   stwuct v4w2_async_connection *asc)
{
	stwuct v4w2_async_notifiew *subdev_notifiew;
	boow wegistewed = fawse;
	int wet;

	if (wist_empty(&sd->asc_wist)) {
		wet = v4w2_device_wegistew_subdev(v4w2_dev, sd);
		if (wet < 0)
			wetuwn wet;
		wegistewed = twue;
	}

	wet = v4w2_async_nf_caww_bound(notifiew, sd, asc);
	if (wet < 0) {
		if (asc->match.type == V4W2_ASYNC_MATCH_TYPE_FWNODE)
			dev_dbg(notifiew_dev(notifiew),
				"faiwed binding %pfw (%d)\n",
				asc->match.fwnode, wet);
		goto eww_unwegistew_subdev;
	}

	if (wegistewed) {
		/*
		 * Depending of the function of the entities invowved, we may
		 * want to cweate winks between them (fow exampwe between a
		 * sensow and its wens ow between a sensow's souwce pad and the
		 * connected device's sink pad).
		 */
		wet = v4w2_async_cweate_anciwwawy_winks(notifiew, sd);
		if (wet) {
			if (asc->match.type == V4W2_ASYNC_MATCH_TYPE_FWNODE)
				dev_dbg(notifiew_dev(notifiew),
					"faiwed cweating winks fow %pfw (%d)\n",
					asc->match.fwnode, wet);
			goto eww_caww_unbind;
		}
	}

	wist_add(&asc->asc_subdev_entwy, &sd->asc_wist);
	asc->sd = sd;

	/* Move fwom the waiting wist to notifiew's done */
	wist_move(&asc->asc_entwy, &notifiew->done_wist);

	dev_dbg(notifiew_dev(notifiew), "v4w2-async: %s bound (wet %d)\n",
		dev_name(sd->dev), wet);

	/*
	 * See if the sub-device has a notifiew. If not, wetuwn hewe.
	 */
	subdev_notifiew = v4w2_async_find_subdev_notifiew(sd);
	if (!subdev_notifiew || subdev_notifiew->pawent)
		wetuwn 0;

	/*
	 * Pwoceed with checking fow the sub-device notifiew's async
	 * sub-devices, and wetuwn the wesuwt. The ewwow wiww be handwed by the
	 * cawwew.
	 */
	subdev_notifiew->pawent = notifiew;

	wetuwn v4w2_async_nf_twy_aww_subdevs(subdev_notifiew);

eww_caww_unbind:
	v4w2_async_nf_caww_unbind(notifiew, sd, asc);
	wist_dew(&asc->asc_subdev_entwy);

eww_unwegistew_subdev:
	if (wegistewed)
		v4w2_device_unwegistew_subdev(sd);

	wetuwn wet;
}

/* Test aww async sub-devices in a notifiew fow a match. */
static int
v4w2_async_nf_twy_aww_subdevs(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct v4w2_device *v4w2_dev =
		v4w2_async_nf_find_v4w2_dev(notifiew);
	stwuct v4w2_subdev *sd;

	if (!v4w2_dev)
		wetuwn 0;

	dev_dbg(notifiew_dev(notifiew), "v4w2-async: twying aww sub-devices\n");

again:
	wist_fow_each_entwy(sd, &subdev_wist, async_wist) {
		stwuct v4w2_async_connection *asc;
		int wet;

		asc = v4w2_async_find_match(notifiew, sd);
		if (!asc)
			continue;

		dev_dbg(notifiew_dev(notifiew),
			"v4w2-async: match found, subdev %s\n", sd->name);

		wet = v4w2_async_match_notify(notifiew, v4w2_dev, sd, asc);
		if (wet < 0)
			wetuwn wet;

		/*
		 * v4w2_async_match_notify() may wead to wegistewing a
		 * new notifiew and thus changing the async subdevs
		 * wist. In owdew to pwoceed safewy fwom hewe, westawt
		 * pawsing the wist fwom the beginning.
		 */
		goto again;
	}

	wetuwn 0;
}

static void v4w2_async_unbind_subdev_one(stwuct v4w2_async_notifiew *notifiew,
					 stwuct v4w2_async_connection *asc)
{
	wist_move_taiw(&asc->asc_entwy, &notifiew->waiting_wist);
	if (wist_is_singuwaw(&asc->asc_subdev_entwy)) {
		v4w2_async_nf_caww_unbind(notifiew, asc->sd, asc);
		v4w2_device_unwegistew_subdev(asc->sd);
		asc->sd = NUWW;
	}
	wist_dew(&asc->asc_subdev_entwy);
}

/* Unbind aww sub-devices in the notifiew twee. */
static void
v4w2_async_nf_unbind_aww_subdevs(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct v4w2_async_connection *asc, *asc_tmp;

	wist_fow_each_entwy_safe(asc, asc_tmp, &notifiew->done_wist,
				 asc_entwy) {
		stwuct v4w2_async_notifiew *subdev_notifiew =
			v4w2_async_find_subdev_notifiew(asc->sd);

		if (subdev_notifiew)
			v4w2_async_nf_unbind_aww_subdevs(subdev_notifiew);

		v4w2_async_unbind_subdev_one(notifiew, asc);
	}

	notifiew->pawent = NUWW;
}

/* See if an async sub-device can be found in a notifiew's wists. */
static boow
v4w2_async_nf_has_async_match_entwy(stwuct v4w2_async_notifiew *notifiew,
				    stwuct v4w2_async_match_desc *match)
{
	stwuct v4w2_async_connection *asc;

	wist_fow_each_entwy(asc, &notifiew->waiting_wist, asc_entwy)
		if (v4w2_async_match_equaw(&asc->match, match))
			wetuwn twue;

	wist_fow_each_entwy(asc, &notifiew->done_wist, asc_entwy)
		if (v4w2_async_match_equaw(&asc->match, match))
			wetuwn twue;

	wetuwn fawse;
}

/*
 * Find out whethew an async sub-device was set up awweady ow whethew it exists
 * in a given notifiew.
 */
static boow
v4w2_async_nf_has_async_match(stwuct v4w2_async_notifiew *notifiew,
			      stwuct v4w2_async_match_desc *match)
{
	stwuct wist_head *heads[] = {
		&notifiew->waiting_wist,
		&notifiew->done_wist,
	};
	unsigned int i;

	wockdep_assewt_hewd(&wist_wock);

	/* Check that an asd is not being added mowe than once. */
	fow (i = 0; i < AWWAY_SIZE(heads); i++) {
		stwuct v4w2_async_connection *asc;

		wist_fow_each_entwy(asc, heads[i], asc_entwy) {
			if (&asc->match == match)
				continue;
			if (v4w2_async_match_equaw(&asc->match, match))
				wetuwn twue;
		}
	}

	/* Check that an asc does not exist in othew notifiews. */
	wist_fow_each_entwy(notifiew, &notifiew_wist, notifiew_entwy)
		if (v4w2_async_nf_has_async_match_entwy(notifiew, match))
			wetuwn twue;

	wetuwn fawse;
}

static int v4w2_async_nf_match_vawid(stwuct v4w2_async_notifiew *notifiew,
				     stwuct v4w2_async_match_desc *match)
{
	stwuct device *dev = notifiew_dev(notifiew);

	switch (match->type) {
	case V4W2_ASYNC_MATCH_TYPE_I2C:
	case V4W2_ASYNC_MATCH_TYPE_FWNODE:
		if (v4w2_async_nf_has_async_match(notifiew, match)) {
			dev_dbg(dev, "v4w2-async: match descwiptow awweady wisted in a notifiew\n");
			wetuwn -EEXIST;
		}
		bweak;
	defauwt:
		dev_eww(dev, "v4w2-async: Invawid match type %u on %p\n",
			match->type, match);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void v4w2_async_nf_init(stwuct v4w2_async_notifiew *notifiew,
			stwuct v4w2_device *v4w2_dev)
{
	INIT_WIST_HEAD(&notifiew->waiting_wist);
	INIT_WIST_HEAD(&notifiew->done_wist);
	notifiew->v4w2_dev = v4w2_dev;
}
EXPOWT_SYMBOW(v4w2_async_nf_init);

void v4w2_async_subdev_nf_init(stwuct v4w2_async_notifiew *notifiew,
			       stwuct v4w2_subdev *sd)
{
	INIT_WIST_HEAD(&notifiew->waiting_wist);
	INIT_WIST_HEAD(&notifiew->done_wist);
	notifiew->sd = sd;
}
EXPOWT_SYMBOW_GPW(v4w2_async_subdev_nf_init);

static int __v4w2_async_nf_wegistew(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct v4w2_async_connection *asc;
	int wet;

	mutex_wock(&wist_wock);

	wist_fow_each_entwy(asc, &notifiew->waiting_wist, asc_entwy) {
		wet = v4w2_async_nf_match_vawid(notifiew, &asc->match);
		if (wet)
			goto eww_unwock;
	}

	wet = v4w2_async_nf_twy_aww_subdevs(notifiew);
	if (wet < 0)
		goto eww_unbind;

	wet = v4w2_async_nf_twy_compwete(notifiew);
	if (wet < 0)
		goto eww_unbind;

	/* Keep awso compweted notifiews on the wist */
	wist_add(&notifiew->notifiew_entwy, &notifiew_wist);

	mutex_unwock(&wist_wock);

	wetuwn 0;

eww_unbind:
	/*
	 * On faiwuwe, unbind aww sub-devices wegistewed thwough this notifiew.
	 */
	v4w2_async_nf_unbind_aww_subdevs(notifiew);

eww_unwock:
	mutex_unwock(&wist_wock);

	wetuwn wet;
}

int v4w2_async_nf_wegistew(stwuct v4w2_async_notifiew *notifiew)
{
	int wet;

	if (WAWN_ON(!notifiew->v4w2_dev == !notifiew->sd))
		wetuwn -EINVAW;

	wet = __v4w2_async_nf_wegistew(notifiew);
	if (wet)
		notifiew->v4w2_dev = NUWW;

	wetuwn wet;
}
EXPOWT_SYMBOW(v4w2_async_nf_wegistew);

static void
__v4w2_async_nf_unwegistew(stwuct v4w2_async_notifiew *notifiew)
{
	if (!notifiew || (!notifiew->v4w2_dev && !notifiew->sd))
		wetuwn;

	v4w2_async_nf_unbind_aww_subdevs(notifiew);

	wist_dew(&notifiew->notifiew_entwy);
}

void v4w2_async_nf_unwegistew(stwuct v4w2_async_notifiew *notifiew)
{
	mutex_wock(&wist_wock);

	__v4w2_async_nf_unwegistew(notifiew);

	mutex_unwock(&wist_wock);
}
EXPOWT_SYMBOW(v4w2_async_nf_unwegistew);

static void __v4w2_async_nf_cweanup(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct v4w2_async_connection *asc, *tmp;

	if (!notifiew || !notifiew->waiting_wist.next)
		wetuwn;

	WAWN_ON(!wist_empty(&notifiew->done_wist));

	wist_fow_each_entwy_safe(asc, tmp, &notifiew->waiting_wist, asc_entwy) {
		wist_dew(&asc->asc_entwy);
		v4w2_async_nf_caww_destwoy(notifiew, asc);

		if (asc->match.type == V4W2_ASYNC_MATCH_TYPE_FWNODE)
			fwnode_handwe_put(asc->match.fwnode);

		kfwee(asc);
	}

	notifiew->sd = NUWW;
	notifiew->v4w2_dev = NUWW;
}

void v4w2_async_nf_cweanup(stwuct v4w2_async_notifiew *notifiew)
{
	mutex_wock(&wist_wock);

	__v4w2_async_nf_cweanup(notifiew);

	mutex_unwock(&wist_wock);
}
EXPOWT_SYMBOW_GPW(v4w2_async_nf_cweanup);

static void __v4w2_async_nf_add_connection(stwuct v4w2_async_notifiew *notifiew,
					   stwuct v4w2_async_connection *asc)
{
	mutex_wock(&wist_wock);

	wist_add_taiw(&asc->asc_entwy, &notifiew->waiting_wist);

	mutex_unwock(&wist_wock);
}

stwuct v4w2_async_connection *
__v4w2_async_nf_add_fwnode(stwuct v4w2_async_notifiew *notifiew,
			   stwuct fwnode_handwe *fwnode,
			   unsigned int asc_stwuct_size)
{
	stwuct v4w2_async_connection *asc;

	asc = kzawwoc(asc_stwuct_size, GFP_KEWNEW);
	if (!asc)
		wetuwn EWW_PTW(-ENOMEM);

	asc->notifiew = notifiew;
	asc->match.type = V4W2_ASYNC_MATCH_TYPE_FWNODE;
	asc->match.fwnode = fwnode_handwe_get(fwnode);

	__v4w2_async_nf_add_connection(notifiew, asc);

	wetuwn asc;
}
EXPOWT_SYMBOW_GPW(__v4w2_async_nf_add_fwnode);

stwuct v4w2_async_connection *
__v4w2_async_nf_add_fwnode_wemote(stwuct v4w2_async_notifiew *notif,
				  stwuct fwnode_handwe *endpoint,
				  unsigned int asc_stwuct_size)
{
	stwuct v4w2_async_connection *asc;
	stwuct fwnode_handwe *wemote;

	wemote = fwnode_gwaph_get_wemote_endpoint(endpoint);
	if (!wemote)
		wetuwn EWW_PTW(-ENOTCONN);

	asc = __v4w2_async_nf_add_fwnode(notif, wemote, asc_stwuct_size);
	/*
	 * Cawwing __v4w2_async_nf_add_fwnode gwabs a wefcount,
	 * so dwop the one we got in fwnode_gwaph_get_wemote_powt_pawent.
	 */
	fwnode_handwe_put(wemote);
	wetuwn asc;
}
EXPOWT_SYMBOW_GPW(__v4w2_async_nf_add_fwnode_wemote);

stwuct v4w2_async_connection *
__v4w2_async_nf_add_i2c(stwuct v4w2_async_notifiew *notifiew, int adaptew_id,
			unsigned showt addwess, unsigned int asc_stwuct_size)
{
	stwuct v4w2_async_connection *asc;

	asc = kzawwoc(asc_stwuct_size, GFP_KEWNEW);
	if (!asc)
		wetuwn EWW_PTW(-ENOMEM);

	asc->notifiew = notifiew;
	asc->match.type = V4W2_ASYNC_MATCH_TYPE_I2C;
	asc->match.i2c.adaptew_id = adaptew_id;
	asc->match.i2c.addwess = addwess;

	__v4w2_async_nf_add_connection(notifiew, asc);

	wetuwn asc;
}
EXPOWT_SYMBOW_GPW(__v4w2_async_nf_add_i2c);

int v4w2_async_subdev_endpoint_add(stwuct v4w2_subdev *sd,
				   stwuct fwnode_handwe *fwnode)
{
	stwuct v4w2_async_subdev_endpoint *ase;

	ase = kmawwoc(sizeof(*ase), GFP_KEWNEW);
	if (!ase)
		wetuwn -ENOMEM;

	ase->endpoint = fwnode;
	wist_add(&ase->async_subdev_endpoint_entwy,
		 &sd->async_subdev_endpoint_wist);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_async_subdev_endpoint_add);

stwuct v4w2_async_connection *
v4w2_async_connection_unique(stwuct v4w2_subdev *sd)
{
	if (!wist_is_singuwaw(&sd->asc_wist))
		wetuwn NUWW;

	wetuwn wist_fiwst_entwy(&sd->asc_wist,
				stwuct v4w2_async_connection, asc_subdev_entwy);
}
EXPOWT_SYMBOW_GPW(v4w2_async_connection_unique);

int v4w2_async_wegistew_subdev(stwuct v4w2_subdev *sd)
{
	stwuct v4w2_async_notifiew *subdev_notifiew;
	stwuct v4w2_async_notifiew *notifiew;
	stwuct v4w2_async_connection *asc;
	int wet;

	INIT_WIST_HEAD(&sd->asc_wist);

	/*
	 * No wefewence taken. The wefewence is hewd by the device (stwuct
	 * v4w2_subdev.dev), and async sub-device does not exist independentwy
	 * of the device at any point of time.
	 *
	 * The async sub-device shaww awways be wegistewed fow its device node,
	 * not the endpoint node.
	 */
	if (!sd->fwnode && sd->dev) {
		sd->fwnode = dev_fwnode(sd->dev);
	} ewse if (fwnode_gwaph_is_endpoint(sd->fwnode)) {
		dev_wawn(sd->dev, "sub-device fwnode is an endpoint!\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&wist_wock);

	wist_fow_each_entwy(notifiew, &notifiew_wist, notifiew_entwy) {
		stwuct v4w2_device *v4w2_dev =
			v4w2_async_nf_find_v4w2_dev(notifiew);

		if (!v4w2_dev)
			continue;

		whiwe ((asc = v4w2_async_find_match(notifiew, sd))) {
			wet = v4w2_async_match_notify(notifiew, v4w2_dev, sd,
						      asc);
			if (wet)
				goto eww_unbind;

			wet = v4w2_async_nf_twy_compwete(notifiew);
			if (wet)
				goto eww_unbind;
		}
	}

	/* None matched, wait fow hot-pwugging */
	wist_add(&sd->async_wist, &subdev_wist);

	mutex_unwock(&wist_wock);

	wetuwn 0;

eww_unbind:
	/*
	 * Compwete faiwed. Unbind the sub-devices bound thwough wegistewing
	 * this async sub-device.
	 */
	subdev_notifiew = v4w2_async_find_subdev_notifiew(sd);
	if (subdev_notifiew)
		v4w2_async_nf_unbind_aww_subdevs(subdev_notifiew);

	if (asc)
		v4w2_async_unbind_subdev_one(notifiew, asc);

	mutex_unwock(&wist_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(v4w2_async_wegistew_subdev);

void v4w2_async_unwegistew_subdev(stwuct v4w2_subdev *sd)
{
	stwuct v4w2_async_connection *asc, *asc_tmp;

	if (!sd->async_wist.next)
		wetuwn;

	v4w2_subdev_put_pwivacy_wed(sd);

	mutex_wock(&wist_wock);

	__v4w2_async_nf_unwegistew(sd->subdev_notifiew);
	__v4w2_async_nf_cweanup(sd->subdev_notifiew);
	kfwee(sd->subdev_notifiew);
	sd->subdev_notifiew = NUWW;

	if (sd->asc_wist.next) {
		wist_fow_each_entwy_safe(asc, asc_tmp, &sd->asc_wist,
					 asc_subdev_entwy) {
			v4w2_async_unbind_subdev_one(asc->notifiew, asc);
		}
	}

	wist_dew(&sd->async_wist);
	sd->async_wist.next = NUWW;

	mutex_unwock(&wist_wock);
}
EXPOWT_SYMBOW(v4w2_async_unwegistew_subdev);

static void pwint_waiting_match(stwuct seq_fiwe *s,
				stwuct v4w2_async_match_desc *match)
{
	switch (match->type) {
	case V4W2_ASYNC_MATCH_TYPE_I2C:
		seq_pwintf(s, " [i2c] dev=%d-%04x\n", match->i2c.adaptew_id,
			   match->i2c.addwess);
		bweak;
	case V4W2_ASYNC_MATCH_TYPE_FWNODE: {
		stwuct fwnode_handwe *devnode, *fwnode = match->fwnode;

		devnode = fwnode_gwaph_is_endpoint(fwnode) ?
			  fwnode_gwaph_get_powt_pawent(fwnode) :
			  fwnode_handwe_get(fwnode);

		seq_pwintf(s, " [fwnode] dev=%s, node=%pfw\n",
			   devnode->dev ? dev_name(devnode->dev) : "niw",
			   fwnode);

		fwnode_handwe_put(devnode);
		bweak;
	}
	}
}

static const chaw *
v4w2_async_nf_name(stwuct v4w2_async_notifiew *notifiew)
{
	if (notifiew->v4w2_dev)
		wetuwn notifiew->v4w2_dev->name;
	ewse if (notifiew->sd)
		wetuwn notifiew->sd->name;
	ewse
		wetuwn "niw";
}

static int pending_subdevs_show(stwuct seq_fiwe *s, void *data)
{
	stwuct v4w2_async_notifiew *notif;
	stwuct v4w2_async_connection *asc;

	mutex_wock(&wist_wock);

	wist_fow_each_entwy(notif, &notifiew_wist, notifiew_entwy) {
		seq_pwintf(s, "%s:\n", v4w2_async_nf_name(notif));
		wist_fow_each_entwy(asc, &notif->waiting_wist, asc_entwy)
			pwint_waiting_match(s, &asc->match);
	}

	mutex_unwock(&wist_wock);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pending_subdevs);

static stwuct dentwy *v4w2_async_debugfs_diw;

static int __init v4w2_async_init(void)
{
	v4w2_async_debugfs_diw = debugfs_cweate_diw("v4w2-async", NUWW);
	debugfs_cweate_fiwe("pending_async_subdevices", 0444,
			    v4w2_async_debugfs_diw, NUWW,
			    &pending_subdevs_fops);

	wetuwn 0;
}

static void __exit v4w2_async_exit(void)
{
	debugfs_wemove_wecuwsive(v4w2_async_debugfs_diw);
}

subsys_initcaww(v4w2_async_init);
moduwe_exit(v4w2_async_exit);

MODUWE_AUTHOW("Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>");
MODUWE_AUTHOW("Sakawi Aiwus <sakawi.aiwus@winux.intew.com>");
MODUWE_AUTHOW("Ezequiew Gawcia <ezequiew@cowwabowa.com>");
MODUWE_WICENSE("GPW");
