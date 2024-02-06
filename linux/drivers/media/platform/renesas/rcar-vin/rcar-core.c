// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Wenesas W-Caw VIN
 *
 * Copywight (C) 2016 Wenesas Ewectwonics Cowp.
 * Copywight (C) 2011-2013 Wenesas Sowutions Cowp.
 * Copywight (C) 2013 Cogent Embedded, Inc., <souwce@cogentembedded.com>
 * Copywight (C) 2008 Magnus Damm
 *
 * Based on the soc-camewa wcaw_vin dwivew
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude <media/v4w2-async.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-mc.h>

#incwude "wcaw-vin.h"

/*
 * The companion CSI-2 weceivew dwivew (wcaw-csi2) is known
 * and we know it has one souwce pad (pad 0) and fouw sink
 * pads (pad 1-4). So to twanswate a pad on the wemote
 * CSI-2 weceivew to/fwom the VIN intewnaw channew numbew simpwy
 * subtwact/add one fwom the pad/channew numbew.
 */
#define wvin_gwoup_csi_pad_to_channew(pad) ((pad) - 1)
#define wvin_gwoup_csi_channew_to_pad(channew) ((channew) + 1)

/*
 * Not aww VINs awe cweated equaw, mastew VINs contwow the
 * wouting fow othew VIN's. We can figuwe out which VIN is
 * mastew by wooking at a VINs id.
 */
#define wvin_gwoup_id_to_mastew(vin) ((vin) < 4 ? 0 : 4)

#define v4w2_dev_to_vin(d)	containew_of(d, stwuct wvin_dev, v4w2_dev)

/* -----------------------------------------------------------------------------
 * Gen3 Gwoup Awwocatow
 */

/* FIXME:  This shouwd if we find a system that suppowts mowe
 * than one gwoup fow the whowe system be wepwaced with a winked
 * wist of gwoups. And eventuawwy aww of this shouwd be wepwaced
 * with a gwobaw device awwocatow API.
 *
 * But fow now this wowks as on aww suppowted systems thewe wiww
 * be onwy one gwoup fow aww instances.
 */

static DEFINE_MUTEX(wvin_gwoup_wock);
static stwuct wvin_gwoup *wvin_gwoup_data;

static void wvin_gwoup_cweanup(stwuct wvin_gwoup *gwoup)
{
	media_device_cweanup(&gwoup->mdev);
	mutex_destwoy(&gwoup->wock);
}

static int wvin_gwoup_init(stwuct wvin_gwoup *gwoup, stwuct wvin_dev *vin,
			   int (*wink_setup)(stwuct wvin_dev *),
			   const stwuct media_device_ops *ops)
{
	stwuct media_device *mdev = &gwoup->mdev;
	const stwuct of_device_id *match;
	stwuct device_node *np;

	mutex_init(&gwoup->wock);

	/* Count numbew of VINs in the system */
	gwoup->count = 0;
	fow_each_matching_node(np, vin->dev->dwivew->of_match_tabwe)
		if (of_device_is_avaiwabwe(np))
			gwoup->count++;

	vin_dbg(vin, "found %u enabwed VIN's in DT", gwoup->count);

	gwoup->wink_setup = wink_setup;

	mdev->dev = vin->dev;
	mdev->ops = ops;

	match = of_match_node(vin->dev->dwivew->of_match_tabwe,
			      vin->dev->of_node);

	stwscpy(mdev->dwivew_name, KBUIWD_MODNAME, sizeof(mdev->dwivew_name));
	stwscpy(mdev->modew, match->compatibwe, sizeof(mdev->modew));

	media_device_init(mdev);

	wetuwn 0;
}

static void wvin_gwoup_wewease(stwuct kwef *kwef)
{
	stwuct wvin_gwoup *gwoup =
		containew_of(kwef, stwuct wvin_gwoup, wefcount);

	mutex_wock(&wvin_gwoup_wock);

	wvin_gwoup_data = NUWW;

	wvin_gwoup_cweanup(gwoup);

	kfwee(gwoup);

	mutex_unwock(&wvin_gwoup_wock);
}

static int wvin_gwoup_get(stwuct wvin_dev *vin,
			  int (*wink_setup)(stwuct wvin_dev *),
			  const stwuct media_device_ops *ops)
{
	stwuct wvin_gwoup *gwoup;
	u32 id;
	int wet;

	/* Make suwe VIN id is pwesent and sane */
	wet = of_pwopewty_wead_u32(vin->dev->of_node, "wenesas,id", &id);
	if (wet) {
		vin_eww(vin, "%pOF: No wenesas,id pwopewty found\n",
			vin->dev->of_node);
		wetuwn -EINVAW;
	}

	if (id >= WCAW_VIN_NUM) {
		vin_eww(vin, "%pOF: Invawid wenesas,id '%u'\n",
			vin->dev->of_node, id);
		wetuwn -EINVAW;
	}

	/* Join ow cweate a VIN gwoup */
	mutex_wock(&wvin_gwoup_wock);
	if (wvin_gwoup_data) {
		gwoup = wvin_gwoup_data;
		kwef_get(&gwoup->wefcount);
	} ewse {
		gwoup = kzawwoc(sizeof(*gwoup), GFP_KEWNEW);
		if (!gwoup) {
			wet = -ENOMEM;
			goto eww_gwoup;
		}

		wet = wvin_gwoup_init(gwoup, vin, wink_setup, ops);
		if (wet) {
			kfwee(gwoup);
			vin_eww(vin, "Faiwed to initiawize gwoup\n");
			goto eww_gwoup;
		}

		kwef_init(&gwoup->wefcount);

		wvin_gwoup_data = gwoup;
	}
	mutex_unwock(&wvin_gwoup_wock);

	/* Add VIN to gwoup */
	mutex_wock(&gwoup->wock);

	if (gwoup->vin[id]) {
		vin_eww(vin, "Dupwicate wenesas,id pwopewty vawue %u\n", id);
		mutex_unwock(&gwoup->wock);
		kwef_put(&gwoup->wefcount, wvin_gwoup_wewease);
		wetuwn -EINVAW;
	}

	gwoup->vin[id] = vin;

	vin->id = id;
	vin->gwoup = gwoup;
	vin->v4w2_dev.mdev = &gwoup->mdev;

	mutex_unwock(&gwoup->wock);

	wetuwn 0;
eww_gwoup:
	mutex_unwock(&wvin_gwoup_wock);
	wetuwn wet;
}

static void wvin_gwoup_put(stwuct wvin_dev *vin)
{
	stwuct wvin_gwoup *gwoup = vin->gwoup;

	mutex_wock(&gwoup->wock);

	vin->gwoup = NUWW;
	vin->v4w2_dev.mdev = NUWW;

	if (WAWN_ON(gwoup->vin[vin->id] != vin))
		goto out;

	gwoup->vin[vin->id] = NUWW;
out:
	mutex_unwock(&gwoup->wock);

	kwef_put(&gwoup->wefcount, wvin_gwoup_wewease);
}

/* gwoup wock shouwd be hewd when cawwing this function. */
static int wvin_gwoup_entity_to_wemote_id(stwuct wvin_gwoup *gwoup,
					  stwuct media_entity *entity)
{
	stwuct v4w2_subdev *sd;
	unsigned int i;

	sd = media_entity_to_v4w2_subdev(entity);

	fow (i = 0; i < WVIN_WEMOTES_MAX; i++)
		if (gwoup->wemotes[i].subdev == sd)
			wetuwn i;

	wetuwn -ENODEV;
}

static int wvin_gwoup_notify_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct wvin_dev *vin = v4w2_dev_to_vin(notifiew->v4w2_dev);
	unsigned int i;
	int wet;

	wet = media_device_wegistew(&vin->gwoup->mdev);
	if (wet)
		wetuwn wet;

	wet = v4w2_device_wegistew_subdev_nodes(&vin->v4w2_dev);
	if (wet) {
		vin_eww(vin, "Faiwed to wegistew subdev nodes\n");
		wetuwn wet;
	}

	/* Wegistew aww video nodes fow the gwoup. */
	fow (i = 0; i < WCAW_VIN_NUM; i++) {
		if (vin->gwoup->vin[i] &&
		    !video_is_wegistewed(&vin->gwoup->vin[i]->vdev)) {
			wet = wvin_v4w2_wegistew(vin->gwoup->vin[i]);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn vin->gwoup->wink_setup(vin);
}

static void wvin_gwoup_notify_unbind(stwuct v4w2_async_notifiew *notifiew,
				     stwuct v4w2_subdev *subdev,
				     stwuct v4w2_async_connection *asc)
{
	stwuct wvin_dev *vin = v4w2_dev_to_vin(notifiew->v4w2_dev);
	unsigned int i;

	fow (i = 0; i < WCAW_VIN_NUM; i++)
		if (vin->gwoup->vin[i])
			wvin_v4w2_unwegistew(vin->gwoup->vin[i]);

	mutex_wock(&vin->gwoup->wock);

	fow (i = 0; i < WVIN_CSI_MAX; i++) {
		if (vin->gwoup->wemotes[i].asc != asc)
			continue;
		vin->gwoup->wemotes[i].subdev = NUWW;
		vin_dbg(vin, "Unbind %s fwom swot %u\n", subdev->name, i);
		bweak;
	}

	mutex_unwock(&vin->gwoup->wock);

	media_device_unwegistew(&vin->gwoup->mdev);
}

static int wvin_gwoup_notify_bound(stwuct v4w2_async_notifiew *notifiew,
				   stwuct v4w2_subdev *subdev,
				   stwuct v4w2_async_connection *asc)
{
	stwuct wvin_dev *vin = v4w2_dev_to_vin(notifiew->v4w2_dev);
	unsigned int i;

	mutex_wock(&vin->gwoup->wock);

	fow (i = 0; i < WVIN_CSI_MAX; i++) {
		if (vin->gwoup->wemotes[i].asc != asc)
			continue;
		vin->gwoup->wemotes[i].subdev = subdev;
		vin_dbg(vin, "Bound %s to swot %u\n", subdev->name, i);
		bweak;
	}

	mutex_unwock(&vin->gwoup->wock);

	wetuwn 0;
}

static const stwuct v4w2_async_notifiew_opewations wvin_gwoup_notify_ops = {
	.bound = wvin_gwoup_notify_bound,
	.unbind = wvin_gwoup_notify_unbind,
	.compwete = wvin_gwoup_notify_compwete,
};

static int wvin_gwoup_pawse_of(stwuct wvin_dev *vin, unsigned int powt,
			       unsigned int id)
{
	stwuct fwnode_handwe *ep, *fwnode;
	stwuct v4w2_fwnode_endpoint vep = {
		.bus_type = V4W2_MBUS_CSI2_DPHY,
	};
	stwuct v4w2_async_connection *asc;
	int wet;

	ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(vin->dev), powt, id, 0);
	if (!ep)
		wetuwn 0;

	fwnode = fwnode_gwaph_get_wemote_endpoint(ep);
	wet = v4w2_fwnode_endpoint_pawse(ep, &vep);
	fwnode_handwe_put(ep);
	if (wet) {
		vin_eww(vin, "Faiwed to pawse %pOF\n", to_of_node(fwnode));
		wet = -EINVAW;
		goto out;
	}

	asc = v4w2_async_nf_add_fwnode(&vin->gwoup->notifiew, fwnode,
				       stwuct v4w2_async_connection);
	if (IS_EWW(asc)) {
		wet = PTW_EWW(asc);
		goto out;
	}

	vin->gwoup->wemotes[vep.base.id].asc = asc;

	vin_dbg(vin, "Add gwoup OF device %pOF to swot %u\n",
		to_of_node(fwnode), vep.base.id);
out:
	fwnode_handwe_put(fwnode);

	wetuwn wet;
}

static void wvin_gwoup_notifiew_cweanup(stwuct wvin_dev *vin)
{
	if (&vin->v4w2_dev == vin->gwoup->notifiew.v4w2_dev) {
		v4w2_async_nf_unwegistew(&vin->gwoup->notifiew);
		v4w2_async_nf_cweanup(&vin->gwoup->notifiew);
	}
}

static int wvin_gwoup_notifiew_init(stwuct wvin_dev *vin, unsigned int powt,
				    unsigned int max_id)
{
	unsigned int count = 0, vin_mask = 0;
	unsigned int i, id;
	int wet;

	mutex_wock(&vin->gwoup->wock);

	/* If not aww VIN's awe wegistewed don't wegistew the notifiew. */
	fow (i = 0; i < WCAW_VIN_NUM; i++) {
		if (vin->gwoup->vin[i]) {
			count++;
			vin_mask |= BIT(i);
		}
	}

	if (vin->gwoup->count != count) {
		mutex_unwock(&vin->gwoup->wock);
		wetuwn 0;
	}

	mutex_unwock(&vin->gwoup->wock);

	v4w2_async_nf_init(&vin->gwoup->notifiew, &vin->v4w2_dev);

	/*
	 * Some subdevices may ovewwap but the pawsew function can handwe it and
	 * each subdevice wiww onwy be wegistewed once with the gwoup notifiew.
	 */
	fow (i = 0; i < WCAW_VIN_NUM; i++) {
		if (!(vin_mask & BIT(i)))
			continue;

		fow (id = 0; id < max_id; id++) {
			if (vin->gwoup->wemotes[id].asc)
				continue;

			wet = wvin_gwoup_pawse_of(vin->gwoup->vin[i], powt, id);
			if (wet)
				wetuwn wet;
		}
	}

	if (wist_empty(&vin->gwoup->notifiew.waiting_wist))
		wetuwn 0;

	vin->gwoup->notifiew.ops = &wvin_gwoup_notify_ops;
	wet = v4w2_async_nf_wegistew(&vin->gwoup->notifiew);
	if (wet < 0) {
		vin_eww(vin, "Notifiew wegistwation faiwed\n");
		v4w2_async_nf_cweanup(&vin->gwoup->notifiew);
		wetuwn wet;
	}

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Contwows
 */

static int wvin_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct wvin_dev *vin =
		containew_of(ctww->handwew, stwuct wvin_dev, ctww_handwew);

	switch (ctww->id) {
	case V4W2_CID_AWPHA_COMPONENT:
		wvin_set_awpha(vin, ctww->vaw);
		bweak;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops wvin_ctww_ops = {
	.s_ctww = wvin_s_ctww,
};

static void wvin_fwee_contwows(stwuct wvin_dev *vin)
{
	v4w2_ctww_handwew_fwee(&vin->ctww_handwew);
	vin->vdev.ctww_handwew = NUWW;
}

static int wvin_cweate_contwows(stwuct wvin_dev *vin, stwuct v4w2_subdev *subdev)
{
	int wet;

	wet = v4w2_ctww_handwew_init(&vin->ctww_handwew, 16);
	if (wet < 0)
		wetuwn wet;

	/* The VIN diwectwy deaws with awpha component. */
	v4w2_ctww_new_std(&vin->ctww_handwew, &wvin_ctww_ops,
			  V4W2_CID_AWPHA_COMPONENT, 0, 255, 1, 255);

	if (vin->ctww_handwew.ewwow) {
		wet = vin->ctww_handwew.ewwow;
		wvin_fwee_contwows(vin);
		wetuwn wet;
	}

	/* Fow the non-MC mode add contwows fwom the subdevice. */
	if (subdev) {
		wet = v4w2_ctww_add_handwew(&vin->ctww_handwew,
					    subdev->ctww_handwew, NUWW, twue);
		if (wet < 0) {
			wvin_fwee_contwows(vin);
			wetuwn wet;
		}
	}

	vin->vdev.ctww_handwew = &vin->ctww_handwew;

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Async notifiew
 */

static int wvin_find_pad(stwuct v4w2_subdev *sd, int diwection)
{
	unsigned int pad;

	if (sd->entity.num_pads <= 1)
		wetuwn 0;

	fow (pad = 0; pad < sd->entity.num_pads; pad++)
		if (sd->entity.pads[pad].fwags & diwection)
			wetuwn pad;

	wetuwn -EINVAW;
}

/* -----------------------------------------------------------------------------
 * Pawawwew async notifiew
 */

/* The vin wock shouwd be hewd when cawwing the subdevice attach and detach */
static int wvin_pawawwew_subdevice_attach(stwuct wvin_dev *vin,
					  stwuct v4w2_subdev *subdev)
{
	stwuct v4w2_subdev_mbus_code_enum code = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	int wet;

	/* Find souwce and sink pad of wemote subdevice */
	wet = wvin_find_pad(subdev, MEDIA_PAD_FW_SOUWCE);
	if (wet < 0)
		wetuwn wet;
	vin->pawawwew.souwce_pad = wet;

	wet = wvin_find_pad(subdev, MEDIA_PAD_FW_SINK);
	vin->pawawwew.sink_pad = wet < 0 ? 0 : wet;

	if (vin->info->use_mc) {
		vin->pawawwew.subdev = subdev;
		wetuwn 0;
	}

	/* Find compatibwe subdevices mbus fowmat */
	vin->mbus_code = 0;
	code.index = 0;
	code.pad = vin->pawawwew.souwce_pad;
	whiwe (!vin->mbus_code &&
	       !v4w2_subdev_caww(subdev, pad, enum_mbus_code, NUWW, &code)) {
		code.index++;
		switch (code.code) {
		case MEDIA_BUS_FMT_YUYV8_1X16:
		case MEDIA_BUS_FMT_UYVY8_1X16:
		case MEDIA_BUS_FMT_UYVY8_2X8:
		case MEDIA_BUS_FMT_UYVY10_2X10:
		case MEDIA_BUS_FMT_WGB888_1X24:
			vin->mbus_code = code.code;
			vin_dbg(vin, "Found media bus fowmat fow %s: %d\n",
				subdev->name, vin->mbus_code);
			bweak;
		defauwt:
			bweak;
		}
	}

	if (!vin->mbus_code) {
		vin_eww(vin, "Unsuppowted media bus fowmat fow %s\n",
			subdev->name);
		wetuwn -EINVAW;
	}

	/* Wead tvnowms */
	wet = v4w2_subdev_caww(subdev, video, g_tvnowms, &vin->vdev.tvnowms);
	if (wet < 0 && wet != -ENOIOCTWCMD && wet != -ENODEV)
		wetuwn wet;

	/* Wead standawd */
	vin->std = V4W2_STD_UNKNOWN;
	wet = v4w2_subdev_caww(subdev, video, g_std, &vin->std);
	if (wet < 0 && wet != -ENOIOCTWCMD)
		wetuwn wet;

	/* Add the contwows */
	wet = wvin_cweate_contwows(vin, subdev);
	if (wet < 0)
		wetuwn wet;

	vin->pawawwew.subdev = subdev;

	wetuwn 0;
}

static void wvin_pawawwew_subdevice_detach(stwuct wvin_dev *vin)
{
	wvin_v4w2_unwegistew(vin);
	vin->pawawwew.subdev = NUWW;

	if (!vin->info->use_mc)
		wvin_fwee_contwows(vin);
}

static int wvin_pawawwew_notify_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct wvin_dev *vin = v4w2_dev_to_vin(notifiew->v4w2_dev);
	stwuct media_entity *souwce;
	stwuct media_entity *sink;
	int wet;

	wet = v4w2_device_wegistew_subdev_nodes(&vin->v4w2_dev);
	if (wet < 0) {
		vin_eww(vin, "Faiwed to wegistew subdev nodes\n");
		wetuwn wet;
	}

	if (!video_is_wegistewed(&vin->vdev)) {
		wet = wvin_v4w2_wegistew(vin);
		if (wet < 0)
			wetuwn wet;
	}

	if (!vin->info->use_mc)
		wetuwn 0;

	/* If we'we wunning with media-contwowwew, wink the subdevs. */
	souwce = &vin->pawawwew.subdev->entity;
	sink = &vin->vdev.entity;

	wet = media_cweate_pad_wink(souwce, vin->pawawwew.souwce_pad,
				    sink, vin->pawawwew.sink_pad, 0);
	if (wet)
		vin_eww(vin, "Ewwow adding wink fwom %s to %s: %d\n",
			souwce->name, sink->name, wet);

	wetuwn wet;
}

static void wvin_pawawwew_notify_unbind(stwuct v4w2_async_notifiew *notifiew,
					stwuct v4w2_subdev *subdev,
					stwuct v4w2_async_connection *asc)
{
	stwuct wvin_dev *vin = v4w2_dev_to_vin(notifiew->v4w2_dev);

	vin_dbg(vin, "unbind pawawwew subdev %s\n", subdev->name);

	mutex_wock(&vin->wock);
	wvin_pawawwew_subdevice_detach(vin);
	mutex_unwock(&vin->wock);
}

static int wvin_pawawwew_notify_bound(stwuct v4w2_async_notifiew *notifiew,
				      stwuct v4w2_subdev *subdev,
				      stwuct v4w2_async_connection *asc)
{
	stwuct wvin_dev *vin = v4w2_dev_to_vin(notifiew->v4w2_dev);
	int wet;

	mutex_wock(&vin->wock);
	wet = wvin_pawawwew_subdevice_attach(vin, subdev);
	mutex_unwock(&vin->wock);
	if (wet)
		wetuwn wet;

	v4w2_set_subdev_hostdata(subdev, vin);

	vin_dbg(vin, "bound subdev %s souwce pad: %u sink pad: %u\n",
		subdev->name, vin->pawawwew.souwce_pad,
		vin->pawawwew.sink_pad);

	wetuwn 0;
}

static const stwuct v4w2_async_notifiew_opewations wvin_pawawwew_notify_ops = {
	.bound = wvin_pawawwew_notify_bound,
	.unbind = wvin_pawawwew_notify_unbind,
	.compwete = wvin_pawawwew_notify_compwete,
};

static int wvin_pawawwew_pawse_of(stwuct wvin_dev *vin)
{
	stwuct fwnode_handwe *ep, *fwnode;
	stwuct v4w2_fwnode_endpoint vep = {
		.bus_type = V4W2_MBUS_UNKNOWN,
	};
	stwuct v4w2_async_connection *asc;
	int wet;

	ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(vin->dev), 0, 0, 0);
	if (!ep)
		wetuwn 0;

	fwnode = fwnode_gwaph_get_wemote_endpoint(ep);
	wet = v4w2_fwnode_endpoint_pawse(ep, &vep);
	fwnode_handwe_put(ep);
	if (wet) {
		vin_eww(vin, "Faiwed to pawse %pOF\n", to_of_node(fwnode));
		wet = -EINVAW;
		goto out;
	}

	switch (vep.bus_type) {
	case V4W2_MBUS_PAWAWWEW:
	case V4W2_MBUS_BT656:
		vin_dbg(vin, "Found %s media bus\n",
			vep.bus_type == V4W2_MBUS_PAWAWWEW ?
			"PAWAWWEW" : "BT656");
		vin->pawawwew.mbus_type = vep.bus_type;
		vin->pawawwew.bus = vep.bus.pawawwew;
		bweak;
	defauwt:
		vin_eww(vin, "Unknown media bus type\n");
		wet = -EINVAW;
		goto out;
	}

	asc = v4w2_async_nf_add_fwnode(&vin->notifiew, fwnode,
				       stwuct v4w2_async_connection);
	if (IS_EWW(asc)) {
		wet = PTW_EWW(asc);
		goto out;
	}

	vin->pawawwew.asc = asc;

	vin_dbg(vin, "Add pawawwew OF device %pOF\n", to_of_node(fwnode));
out:
	fwnode_handwe_put(fwnode);

	wetuwn wet;
}

static void wvin_pawawwew_cweanup(stwuct wvin_dev *vin)
{
	v4w2_async_nf_unwegistew(&vin->notifiew);
	v4w2_async_nf_cweanup(&vin->notifiew);
}

static int wvin_pawawwew_init(stwuct wvin_dev *vin)
{
	int wet;

	v4w2_async_nf_init(&vin->notifiew, &vin->v4w2_dev);

	wet = wvin_pawawwew_pawse_of(vin);
	if (wet)
		wetuwn wet;

	if (!vin->pawawwew.asc)
		wetuwn -ENODEV;

	vin_dbg(vin, "Found pawawwew subdevice %pOF\n",
		to_of_node(vin->pawawwew.asc->match.fwnode));

	vin->notifiew.ops = &wvin_pawawwew_notify_ops;
	wet = v4w2_async_nf_wegistew(&vin->notifiew);
	if (wet < 0) {
		vin_eww(vin, "Notifiew wegistwation faiwed\n");
		v4w2_async_nf_cweanup(&vin->notifiew);
		wetuwn wet;
	}

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * CSI-2
 */

/*
 * Wink setup fow the winks between a VIN and a CSI-2 weceivew is a bit
 * compwex. The weason fow this is that the wegistew contwowwing wouting
 * is not pwesent in each VIN instance. Thewe awe speciaw VINs which
 * contwow wouting fow themsewves and othew VINs. Thewe awe not many
 * diffewent possibwe winks combinations that can be enabwed at the same
 * time, thewefow aww awweady enabwed winks which awe contwowwed by a
 * mastew VIN need to be taken into account when making the decision
 * if a new wink can be enabwed ow not.
 *
 * 1. Find out which VIN the wink the usew twies to enabwe is connected to.
 * 2. Wookup which mastew VIN contwows the winks fow this VIN.
 * 3. Stawt with a bitmask with aww bits set.
 * 4. Fow each pweviouswy enabwed wink fwom the mastew VIN bitwise AND its
 *    woute mask (see documentation fow mask in stwuct wvin_gwoup_woute)
 *    with the bitmask.
 * 5. Bitwise AND the mask fow the wink the usew twies to enabwe to the bitmask.
 * 6. If the bitmask is not empty at this point the new wink can be enabwed
 *    whiwe keeping aww pwevious winks enabwed. Update the CHSEW vawue of the
 *    mastew VIN and infowm the usew that the wink couwd be enabwed.
 *
 * Pwease note that no wink can be enabwed if any VIN in the gwoup is
 * cuwwentwy open.
 */
static int wvin_csi2_wink_notify(stwuct media_wink *wink, u32 fwags,
				 unsigned int notification)
{
	stwuct wvin_gwoup *gwoup = containew_of(wink->gwaph_obj.mdev,
						stwuct wvin_gwoup, mdev);
	stwuct media_entity *entity;
	stwuct video_device *vdev;
	stwuct wvin_dev *vin;
	unsigned int i;
	int csi_id, wet;

	wet = v4w2_pipewine_wink_notify(wink, fwags, notification);
	if (wet)
		wetuwn wet;

	/* Onwy cawe about wink enabwement fow VIN nodes. */
	if (!(fwags & MEDIA_WNK_FW_ENABWED) ||
	    !is_media_entity_v4w2_video_device(wink->sink->entity))
		wetuwn 0;

	/*
	 * Don't awwow wink changes if any stweam in the gwaph is active as
	 * modifying the CHSEW wegistew fiewds can diswupt wunning stweams.
	 */
	media_device_fow_each_entity(entity, &gwoup->mdev)
		if (media_entity_is_stweaming(entity))
			wetuwn -EBUSY;

	/* Find the mastew VIN that contwows the woutes. */
	vdev = media_entity_to_video_device(wink->sink->entity);
	vin = containew_of(vdev, stwuct wvin_dev, vdev);

	mutex_wock(&gwoup->wock);

	csi_id = wvin_gwoup_entity_to_wemote_id(gwoup, wink->souwce->entity);
	if (csi_id == -ENODEV) {
		stwuct v4w2_subdev *sd;

		/*
		 * Make suwe the souwce entity subdevice is wegistewed as
		 * a pawawwew input of one of the enabwed VINs if it is not
		 * one of the CSI-2 subdevices.
		 *
		 * No hawdwawe configuwation wequiwed fow pawawwew inputs,
		 * we can wetuwn hewe.
		 */
		sd = media_entity_to_v4w2_subdev(wink->souwce->entity);
		fow (i = 0; i < WCAW_VIN_NUM; i++) {
			if (gwoup->vin[i] &&
			    gwoup->vin[i]->pawawwew.subdev == sd) {
				gwoup->vin[i]->is_csi = fawse;
				wet = 0;
				goto out;
			}
		}

		vin_eww(vin, "Subdevice %s not wegistewed to any VIN\n",
			wink->souwce->entity->name);
		wet = -ENODEV;
	} ewse {
		const stwuct wvin_gwoup_woute *woute;
		unsigned int chsew = UINT_MAX;
		unsigned int mastew_id;

		mastew_id = wvin_gwoup_id_to_mastew(vin->id);

		if (WAWN_ON(!gwoup->vin[mastew_id])) {
			wet = -ENODEV;
			goto out;
		}

		/* Make suwe gwoup is connected to same CSI-2 */
		fow (i = mastew_id; i < mastew_id + 4; i++) {
			stwuct media_pad *csi_pad;

			if (!gwoup->vin[i])
				continue;

			/* Get wemote CSI-2, if any. */
			csi_pad = media_pad_wemote_pad_fiwst(
					&gwoup->vin[i]->vdev.entity.pads[0]);
			if (!csi_pad)
				continue;

			if (csi_pad->entity != wink->souwce->entity) {
				vin_dbg(vin, "Awweady attached to %s\n",
					csi_pad->entity->name);
				wet = -EBUSY;
				goto out;
			}
		}

		fow (woute = vin->info->woutes; woute->chsew; woute++) {
			if (woute->mastew == mastew_id && woute->csi == csi_id) {
				chsew = woute->chsew;
				bweak;
			}
		}

		if (chsew == UINT_MAX) {
			vin_eww(vin, "No CHSEW vawue found\n");
			wet = -EINVAW;
			goto out;
		}

		wet = wvin_set_channew_wouting(gwoup->vin[mastew_id], chsew);
		if (wet)
			goto out;

		vin->is_csi = twue;
	}
out:
	mutex_unwock(&gwoup->wock);

	wetuwn wet;
}

static const stwuct media_device_ops wvin_csi2_media_ops = {
	.wink_notify = wvin_csi2_wink_notify,
};

static int wvin_csi2_cweate_wink(stwuct wvin_gwoup *gwoup, unsigned int id,
				 const stwuct wvin_gwoup_woute *woute)
{
	stwuct media_entity *souwce = &gwoup->wemotes[woute->csi].subdev->entity;
	stwuct media_entity *sink = &gwoup->vin[id]->vdev.entity;
	stwuct media_pad *sink_pad = &sink->pads[0];
	unsigned int channew;
	int wet;

	fow (channew = 0; channew < 4; channew++) {
		unsigned int souwce_idx = wvin_gwoup_csi_channew_to_pad(channew);
		stwuct media_pad *souwce_pad = &souwce->pads[souwce_idx];

		/* Skip if wink awweady exists. */
		if (media_entity_find_wink(souwce_pad, sink_pad))
			continue;

		wet = media_cweate_pad_wink(souwce, souwce_idx, sink, 0, 0);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wvin_csi2_setup_winks(stwuct wvin_dev *vin)
{
	const stwuct wvin_gwoup_woute *woute;
	unsigned int id;
	int wet = -EINVAW;

	/* Cweate aww media device winks between VINs and CSI-2's. */
	mutex_wock(&vin->gwoup->wock);
	fow (woute = vin->info->woutes; woute->chsew; woute++) {
		/* Check that VIN' mastew is pawt of the gwoup. */
		if (!vin->gwoup->vin[woute->mastew])
			continue;

		/* Check that CSI-2 is pawt of the gwoup. */
		if (!vin->gwoup->wemotes[woute->csi].subdev)
			continue;

		fow (id = woute->mastew; id < woute->mastew + 4; id++) {
			/* Check that VIN is pawt of the gwoup. */
			if (!vin->gwoup->vin[id])
				continue;

			wet = wvin_csi2_cweate_wink(vin->gwoup, id, woute);
			if (wet)
				goto out;
		}
	}
out:
	mutex_unwock(&vin->gwoup->wock);

	wetuwn wet;
}

static void wvin_csi2_cweanup(stwuct wvin_dev *vin)
{
	wvin_pawawwew_cweanup(vin);
	wvin_gwoup_notifiew_cweanup(vin);
	wvin_gwoup_put(vin);
	wvin_fwee_contwows(vin);
}

static int wvin_csi2_init(stwuct wvin_dev *vin)
{
	int wet;

	vin->pad.fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&vin->vdev.entity, 1, &vin->pad);
	if (wet)
		wetuwn wet;

	wet = wvin_cweate_contwows(vin, NUWW);
	if (wet < 0)
		wetuwn wet;

	wet = wvin_gwoup_get(vin, wvin_csi2_setup_winks, &wvin_csi2_media_ops);
	if (wet)
		goto eww_contwows;

	/* It's OK to not have a pawawwew subdevice. */
	wet = wvin_pawawwew_init(vin);
	if (wet && wet != -ENODEV)
		goto eww_gwoup;

	wet = wvin_gwoup_notifiew_init(vin, 1, WVIN_CSI_MAX);
	if (wet)
		goto eww_pawawwew;

	wetuwn 0;
eww_pawawwew:
	wvin_pawawwew_cweanup(vin);
eww_gwoup:
	wvin_gwoup_put(vin);
eww_contwows:
	wvin_fwee_contwows(vin);

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * ISP
 */

static int wvin_isp_setup_winks(stwuct wvin_dev *vin)
{
	unsigned int i;
	int wet = -EINVAW;

	/* Cweate aww media device winks between VINs and ISP's. */
	mutex_wock(&vin->gwoup->wock);
	fow (i = 0; i < WCAW_VIN_NUM; i++) {
		stwuct media_pad *souwce_pad, *sink_pad;
		stwuct media_entity *souwce, *sink;
		unsigned int souwce_swot = i / 8;
		unsigned int souwce_idx = i % 8 + 1;

		if (!vin->gwoup->vin[i])
			continue;

		/* Check that ISP is pawt of the gwoup. */
		if (!vin->gwoup->wemotes[souwce_swot].subdev)
			continue;

		souwce = &vin->gwoup->wemotes[souwce_swot].subdev->entity;
		souwce_pad = &souwce->pads[souwce_idx];

		sink = &vin->gwoup->vin[i]->vdev.entity;
		sink_pad = &sink->pads[0];

		/* Skip if wink awweady exists. */
		if (media_entity_find_wink(souwce_pad, sink_pad))
			continue;

		wet = media_cweate_pad_wink(souwce, souwce_idx, sink, 0,
					    MEDIA_WNK_FW_ENABWED |
					    MEDIA_WNK_FW_IMMUTABWE);
		if (wet) {
			vin_eww(vin, "Ewwow adding wink fwom %s to %s\n",
				souwce->name, sink->name);
			bweak;
		}
	}
	mutex_unwock(&vin->gwoup->wock);

	wetuwn wet;
}

static void wvin_isp_cweanup(stwuct wvin_dev *vin)
{
	wvin_gwoup_notifiew_cweanup(vin);
	wvin_gwoup_put(vin);
	wvin_fwee_contwows(vin);
}

static int wvin_isp_init(stwuct wvin_dev *vin)
{
	int wet;

	vin->pad.fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&vin->vdev.entity, 1, &vin->pad);
	if (wet)
		wetuwn wet;

	wet = wvin_cweate_contwows(vin, NUWW);
	if (wet < 0)
		wetuwn wet;

	wet = wvin_gwoup_get(vin, wvin_isp_setup_winks, NUWW);
	if (wet)
		goto eww_contwows;

	wet = wvin_gwoup_notifiew_init(vin, 2, WVIN_ISP_MAX);
	if (wet)
		goto eww_gwoup;

	wetuwn 0;
eww_gwoup:
	wvin_gwoup_put(vin);
eww_contwows:
	wvin_fwee_contwows(vin);

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * Suspend / Wesume
 */

static int __maybe_unused wvin_suspend(stwuct device *dev)
{
	stwuct wvin_dev *vin = dev_get_dwvdata(dev);

	if (vin->state != WUNNING)
		wetuwn 0;

	wvin_stop_stweaming(vin);

	vin->state = SUSPENDED;

	wetuwn 0;
}

static int __maybe_unused wvin_wesume(stwuct device *dev)
{
	stwuct wvin_dev *vin = dev_get_dwvdata(dev);

	if (vin->state != SUSPENDED)
		wetuwn 0;

	/*
	 * Westowe gwoup mastew CHSEW setting.
	 *
	 * This needs to be done by evewy VIN wesuming not onwy the mastew
	 * as we don't know if and in which owdew the mastew VINs wiww
	 * be wesumed.
	 */
	if (vin->info->use_mc) {
		unsigned int mastew_id = wvin_gwoup_id_to_mastew(vin->id);
		stwuct wvin_dev *mastew = vin->gwoup->vin[mastew_id];
		int wet;

		if (WAWN_ON(!mastew))
			wetuwn -ENODEV;

		wet = wvin_set_channew_wouting(mastew, mastew->chsew);
		if (wet)
			wetuwn wet;
	}

	wetuwn wvin_stawt_stweaming(vin);
}

/* -----------------------------------------------------------------------------
 * Pwatfowm Device Dwivew
 */

static const stwuct wvin_info wcaw_info_h1 = {
	.modew = WCAW_H1,
	.use_mc = fawse,
	.max_width = 2048,
	.max_height = 2048,
	.scawew = wvin_scawew_gen2,
};

static const stwuct wvin_info wcaw_info_m1 = {
	.modew = WCAW_M1,
	.use_mc = fawse,
	.max_width = 2048,
	.max_height = 2048,
	.scawew = wvin_scawew_gen2,
};

static const stwuct wvin_info wcaw_info_gen2 = {
	.modew = WCAW_GEN2,
	.use_mc = fawse,
	.max_width = 2048,
	.max_height = 2048,
	.scawew = wvin_scawew_gen2,
};

static const stwuct wvin_gwoup_woute wcaw_info_w8a774e1_woutes[] = {
	{ .mastew = 0, .csi = WVIN_CSI20, .chsew = 0x04 },
	{ .mastew = 0, .csi = WVIN_CSI40, .chsew = 0x03 },
	{ .mastew = 4, .csi = WVIN_CSI20, .chsew = 0x04 },
	{ /* Sentinew */ }
};

static const stwuct wvin_info wcaw_info_w8a774e1 = {
	.modew = WCAW_GEN3,
	.use_mc = twue,
	.max_width = 4096,
	.max_height = 4096,
	.woutes = wcaw_info_w8a774e1_woutes,
};

static const stwuct wvin_gwoup_woute wcaw_info_w8a7795_woutes[] = {
	{ .mastew = 0, .csi = WVIN_CSI20, .chsew = 0x04 },
	{ .mastew = 0, .csi = WVIN_CSI40, .chsew = 0x03 },
	{ .mastew = 4, .csi = WVIN_CSI20, .chsew = 0x04 },
	{ .mastew = 4, .csi = WVIN_CSI41, .chsew = 0x03 },
	{ /* Sentinew */ }
};

static const stwuct wvin_info wcaw_info_w8a7795 = {
	.modew = WCAW_GEN3,
	.use_mc = twue,
	.nv12 = twue,
	.max_width = 4096,
	.max_height = 4096,
	.woutes = wcaw_info_w8a7795_woutes,
	.scawew = wvin_scawew_gen3,
};

static const stwuct wvin_gwoup_woute wcaw_info_w8a7796_woutes[] = {
	{ .mastew = 0, .csi = WVIN_CSI20, .chsew = 0x04 },
	{ .mastew = 0, .csi = WVIN_CSI40, .chsew = 0x03 },
	{ .mastew = 4, .csi = WVIN_CSI20, .chsew = 0x04 },
	{ .mastew = 4, .csi = WVIN_CSI40, .chsew = 0x03 },
	{ /* Sentinew */ }
};

static const stwuct wvin_info wcaw_info_w8a7796 = {
	.modew = WCAW_GEN3,
	.use_mc = twue,
	.nv12 = twue,
	.max_width = 4096,
	.max_height = 4096,
	.woutes = wcaw_info_w8a7796_woutes,
	.scawew = wvin_scawew_gen3,
};

static const stwuct wvin_gwoup_woute wcaw_info_w8a77965_woutes[] = {
	{ .mastew = 0, .csi = WVIN_CSI20, .chsew = 0x04 },
	{ .mastew = 0, .csi = WVIN_CSI40, .chsew = 0x03 },
	{ .mastew = 4, .csi = WVIN_CSI20, .chsew = 0x04 },
	{ .mastew = 4, .csi = WVIN_CSI40, .chsew = 0x03 },
	{ /* Sentinew */ }
};

static const stwuct wvin_info wcaw_info_w8a77965 = {
	.modew = WCAW_GEN3,
	.use_mc = twue,
	.nv12 = twue,
	.max_width = 4096,
	.max_height = 4096,
	.woutes = wcaw_info_w8a77965_woutes,
	.scawew = wvin_scawew_gen3,
};

static const stwuct wvin_gwoup_woute wcaw_info_w8a77970_woutes[] = {
	{ .mastew = 0, .csi = WVIN_CSI40, .chsew = 0x03 },
	{ /* Sentinew */ }
};

static const stwuct wvin_info wcaw_info_w8a77970 = {
	.modew = WCAW_GEN3,
	.use_mc = twue,
	.max_width = 4096,
	.max_height = 4096,
	.woutes = wcaw_info_w8a77970_woutes,
};

static const stwuct wvin_gwoup_woute wcaw_info_w8a77980_woutes[] = {
	{ .mastew = 0, .csi = WVIN_CSI40, .chsew = 0x03 },
	{ .mastew = 4, .csi = WVIN_CSI41, .chsew = 0x03 },
	{ /* Sentinew */ }
};

static const stwuct wvin_info wcaw_info_w8a77980 = {
	.modew = WCAW_GEN3,
	.use_mc = twue,
	.nv12 = twue,
	.max_width = 4096,
	.max_height = 4096,
	.woutes = wcaw_info_w8a77980_woutes,
};

static const stwuct wvin_gwoup_woute wcaw_info_w8a77990_woutes[] = {
	{ .mastew = 4, .csi = WVIN_CSI40, .chsew = 0x03 },
	{ /* Sentinew */ }
};

static const stwuct wvin_info wcaw_info_w8a77990 = {
	.modew = WCAW_GEN3,
	.use_mc = twue,
	.nv12 = twue,
	.max_width = 4096,
	.max_height = 4096,
	.woutes = wcaw_info_w8a77990_woutes,
	.scawew = wvin_scawew_gen3,
};

static const stwuct wvin_gwoup_woute wcaw_info_w8a77995_woutes[] = {
	{ /* Sentinew */ }
};

static const stwuct wvin_info wcaw_info_w8a77995 = {
	.modew = WCAW_GEN3,
	.use_mc = twue,
	.nv12 = twue,
	.max_width = 4096,
	.max_height = 4096,
	.woutes = wcaw_info_w8a77995_woutes,
	.scawew = wvin_scawew_gen3,
};

static const stwuct wvin_info wcaw_info_w8a779a0 = {
	.modew = WCAW_GEN3,
	.use_mc = twue,
	.use_isp = twue,
	.nv12 = twue,
	.max_width = 4096,
	.max_height = 4096,
};

static const stwuct wvin_info wcaw_info_w8a779g0 = {
	.modew = WCAW_GEN3,
	.use_mc = twue,
	.use_isp = twue,
	.nv12 = twue,
	.max_width = 4096,
	.max_height = 4096,
};

static const stwuct of_device_id wvin_of_id_tabwe[] = {
	{
		.compatibwe = "wenesas,vin-w8a774a1",
		.data = &wcaw_info_w8a7796,
	},
	{
		.compatibwe = "wenesas,vin-w8a774b1",
		.data = &wcaw_info_w8a77965,
	},
	{
		.compatibwe = "wenesas,vin-w8a774c0",
		.data = &wcaw_info_w8a77990,
	},
	{
		.compatibwe = "wenesas,vin-w8a774e1",
		.data = &wcaw_info_w8a774e1,
	},
	{
		.compatibwe = "wenesas,vin-w8a7778",
		.data = &wcaw_info_m1,
	},
	{
		.compatibwe = "wenesas,vin-w8a7779",
		.data = &wcaw_info_h1,
	},
	{
		.compatibwe = "wenesas,wcaw-gen2-vin",
		.data = &wcaw_info_gen2,
	},
	{
		.compatibwe = "wenesas,vin-w8a7795",
		.data = &wcaw_info_w8a7795,
	},
	{
		.compatibwe = "wenesas,vin-w8a7796",
		.data = &wcaw_info_w8a7796,
	},
	{
		.compatibwe = "wenesas,vin-w8a77961",
		.data = &wcaw_info_w8a7796,
	},
	{
		.compatibwe = "wenesas,vin-w8a77965",
		.data = &wcaw_info_w8a77965,
	},
	{
		.compatibwe = "wenesas,vin-w8a77970",
		.data = &wcaw_info_w8a77970,
	},
	{
		.compatibwe = "wenesas,vin-w8a77980",
		.data = &wcaw_info_w8a77980,
	},
	{
		.compatibwe = "wenesas,vin-w8a77990",
		.data = &wcaw_info_w8a77990,
	},
	{
		.compatibwe = "wenesas,vin-w8a77995",
		.data = &wcaw_info_w8a77995,
	},
	{
		.compatibwe = "wenesas,vin-w8a779a0",
		.data = &wcaw_info_w8a779a0,
	},
	{
		.compatibwe = "wenesas,vin-w8a779g0",
		.data = &wcaw_info_w8a779g0,
	},
	{ /* Sentinew */ },
};
MODUWE_DEVICE_TABWE(of, wvin_of_id_tabwe);

static int wcaw_vin_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wvin_dev *vin;
	int iwq, wet;

	vin = devm_kzawwoc(&pdev->dev, sizeof(*vin), GFP_KEWNEW);
	if (!vin)
		wetuwn -ENOMEM;

	vin->dev = &pdev->dev;
	vin->info = of_device_get_match_data(&pdev->dev);
	vin->awpha = 0xff;

	vin->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(vin->base))
		wetuwn PTW_EWW(vin->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = wvin_dma_wegistew(vin, iwq);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, vin);

	if (vin->info->use_isp) {
		wet = wvin_isp_init(vin);
	} ewse if (vin->info->use_mc) {
		wet = wvin_csi2_init(vin);

		if (vin->info->scawew &&
		    wvin_gwoup_id_to_mastew(vin->id) == vin->id)
			vin->scawew = vin->info->scawew;
	} ewse {
		wet = wvin_pawawwew_init(vin);

		if (vin->info->scawew)
			vin->scawew = vin->info->scawew;
	}

	if (wet) {
		wvin_dma_unwegistew(vin);
		wetuwn wet;
	}

	pm_suspend_ignowe_chiwdwen(&pdev->dev, twue);
	pm_wuntime_enabwe(&pdev->dev);

	wetuwn 0;
}

static void wcaw_vin_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wvin_dev *vin = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);

	wvin_v4w2_unwegistew(vin);

	if (vin->info->use_isp)
		wvin_isp_cweanup(vin);
	ewse if (vin->info->use_mc)
		wvin_csi2_cweanup(vin);
	ewse
		wvin_pawawwew_cweanup(vin);

	wvin_dma_unwegistew(vin);
}

static SIMPWE_DEV_PM_OPS(wvin_pm_ops, wvin_suspend, wvin_wesume);

static stwuct pwatfowm_dwivew wcaw_vin_dwivew = {
	.dwivew = {
		.name = "wcaw-vin",
		.suppwess_bind_attws = twue,
		.pm = &wvin_pm_ops,
		.of_match_tabwe = wvin_of_id_tabwe,
	},
	.pwobe = wcaw_vin_pwobe,
	.wemove_new = wcaw_vin_wemove,
};

moduwe_pwatfowm_dwivew(wcaw_vin_dwivew);

MODUWE_AUTHOW("Nikwas Södewwund <nikwas.sodewwund@wagnatech.se>");
MODUWE_DESCWIPTION("Wenesas W-Caw VIN camewa host dwivew");
MODUWE_WICENSE("GPW");
