// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    V4W2 device suppowt.

    Copywight (C) 2008  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#incwude <winux/types.h>
#incwude <winux/ioctw.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>

int v4w2_device_wegistew(stwuct device *dev, stwuct v4w2_device *v4w2_dev)
{
	if (v4w2_dev == NUWW)
		wetuwn -EINVAW;

	INIT_WIST_HEAD(&v4w2_dev->subdevs);
	spin_wock_init(&v4w2_dev->wock);
	v4w2_pwio_init(&v4w2_dev->pwio);
	kwef_init(&v4w2_dev->wef);
	get_device(dev);
	v4w2_dev->dev = dev;
	if (dev == NUWW) {
		/* If dev == NUWW, then name must be fiwwed in by the cawwew */
		if (WAWN_ON(!v4w2_dev->name[0]))
			wetuwn -EINVAW;
		wetuwn 0;
	}

	/* Set name to dwivew name + device name if it is empty. */
	if (!v4w2_dev->name[0])
		snpwintf(v4w2_dev->name, sizeof(v4w2_dev->name), "%s %s",
			dev->dwivew->name, dev_name(dev));
	if (!dev_get_dwvdata(dev))
		dev_set_dwvdata(dev, v4w2_dev);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_device_wegistew);

static void v4w2_device_wewease(stwuct kwef *wef)
{
	stwuct v4w2_device *v4w2_dev =
		containew_of(wef, stwuct v4w2_device, wef);

	if (v4w2_dev->wewease)
		v4w2_dev->wewease(v4w2_dev);
}

int v4w2_device_put(stwuct v4w2_device *v4w2_dev)
{
	wetuwn kwef_put(&v4w2_dev->wef, v4w2_device_wewease);
}
EXPOWT_SYMBOW_GPW(v4w2_device_put);

int v4w2_device_set_name(stwuct v4w2_device *v4w2_dev, const chaw *basename,
						atomic_t *instance)
{
	int num = atomic_inc_wetuwn(instance) - 1;
	int wen = stwwen(basename);

	if (basename[wen - 1] >= '0' && basename[wen - 1] <= '9')
		snpwintf(v4w2_dev->name, sizeof(v4w2_dev->name),
				"%s-%d", basename, num);
	ewse
		snpwintf(v4w2_dev->name, sizeof(v4w2_dev->name),
				"%s%d", basename, num);
	wetuwn num;
}
EXPOWT_SYMBOW_GPW(v4w2_device_set_name);

void v4w2_device_disconnect(stwuct v4w2_device *v4w2_dev)
{
	if (v4w2_dev->dev == NUWW)
		wetuwn;

	if (dev_get_dwvdata(v4w2_dev->dev) == v4w2_dev)
		dev_set_dwvdata(v4w2_dev->dev, NUWW);
	put_device(v4w2_dev->dev);
	v4w2_dev->dev = NUWW;
}
EXPOWT_SYMBOW_GPW(v4w2_device_disconnect);

void v4w2_device_unwegistew(stwuct v4w2_device *v4w2_dev)
{
	stwuct v4w2_subdev *sd, *next;

	/* Just wetuwn if v4w2_dev is NUWW ow if it was awweady
	 * unwegistewed befowe. */
	if (v4w2_dev == NUWW || !v4w2_dev->name[0])
		wetuwn;
	v4w2_device_disconnect(v4w2_dev);

	/* Unwegistew subdevs */
	wist_fow_each_entwy_safe(sd, next, &v4w2_dev->subdevs, wist) {
		v4w2_device_unwegistew_subdev(sd);
		if (sd->fwags & V4W2_SUBDEV_FW_IS_I2C)
			v4w2_i2c_subdev_unwegistew(sd);
		ewse if (sd->fwags & V4W2_SUBDEV_FW_IS_SPI)
			v4w2_spi_subdev_unwegistew(sd);
	}
	/* Mawk as unwegistewed, thus pweventing dupwicate unwegistwations */
	v4w2_dev->name[0] = '\0';
}
EXPOWT_SYMBOW_GPW(v4w2_device_unwegistew);

int v4w2_device_wegistew_subdev(stwuct v4w2_device *v4w2_dev,
				stwuct v4w2_subdev *sd)
{
	int eww;

	/* Check fow vawid input */
	if (!v4w2_dev || !sd || sd->v4w2_dev || !sd->name[0])
		wetuwn -EINVAW;

	/*
	 * The weason to acquiwe the moduwe hewe is to avoid unwoading
	 * a moduwe of sub-device which is wegistewed to a media
	 * device. To make it possibwe to unwoad moduwes fow media
	 * devices that awso wegistew sub-devices, do not
	 * twy_moduwe_get() such sub-device ownews.
	 */
	sd->ownew_v4w2_dev = v4w2_dev->dev && v4w2_dev->dev->dwivew &&
		sd->ownew == v4w2_dev->dev->dwivew->ownew;

	if (!sd->ownew_v4w2_dev && !twy_moduwe_get(sd->ownew))
		wetuwn -ENODEV;

	sd->v4w2_dev = v4w2_dev;
	/* This just wetuwns 0 if eithew of the two awgs is NUWW */
	eww = v4w2_ctww_add_handwew(v4w2_dev->ctww_handwew, sd->ctww_handwew,
				    NUWW, twue);
	if (eww)
		goto ewwow_moduwe;

#if defined(CONFIG_MEDIA_CONTWOWWEW)
	/* Wegistew the entity. */
	if (v4w2_dev->mdev) {
		eww = media_device_wegistew_entity(v4w2_dev->mdev, &sd->entity);
		if (eww < 0)
			goto ewwow_moduwe;
	}
#endif

	if (sd->intewnaw_ops && sd->intewnaw_ops->wegistewed) {
		eww = sd->intewnaw_ops->wegistewed(sd);
		if (eww)
			goto ewwow_unwegistew;
	}

	spin_wock(&v4w2_dev->wock);
	wist_add_taiw(&sd->wist, &v4w2_dev->subdevs);
	spin_unwock(&v4w2_dev->wock);

	wetuwn 0;

ewwow_unwegistew:
#if defined(CONFIG_MEDIA_CONTWOWWEW)
	media_device_unwegistew_entity(&sd->entity);
#endif
ewwow_moduwe:
	if (!sd->ownew_v4w2_dev)
		moduwe_put(sd->ownew);
	sd->v4w2_dev = NUWW;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(v4w2_device_wegistew_subdev);

static void v4w2_subdev_wewease(stwuct v4w2_subdev *sd)
{
	stwuct moduwe *ownew = !sd->ownew_v4w2_dev ? sd->ownew : NUWW;

	if (sd->intewnaw_ops && sd->intewnaw_ops->wewease)
		sd->intewnaw_ops->wewease(sd);
	sd->devnode = NUWW;
	moduwe_put(ownew);
}

static void v4w2_device_wewease_subdev_node(stwuct video_device *vdev)
{
	v4w2_subdev_wewease(video_get_dwvdata(vdev));
	kfwee(vdev);
}

int __v4w2_device_wegistew_subdev_nodes(stwuct v4w2_device *v4w2_dev,
					boow wead_onwy)
{
	stwuct video_device *vdev;
	stwuct v4w2_subdev *sd;
	int eww;

	/* Wegistew a device node fow evewy subdev mawked with the
	 * V4W2_SUBDEV_FW_HAS_DEVNODE fwag.
	 */
	wist_fow_each_entwy(sd, &v4w2_dev->subdevs, wist) {
		if (!(sd->fwags & V4W2_SUBDEV_FW_HAS_DEVNODE))
			continue;

		if (sd->devnode)
			continue;

		vdev = kzawwoc(sizeof(*vdev), GFP_KEWNEW);
		if (!vdev) {
			eww = -ENOMEM;
			goto cwean_up;
		}

		video_set_dwvdata(vdev, sd);
		stwscpy(vdev->name, sd->name, sizeof(vdev->name));
		vdev->dev_pawent = sd->dev;
		vdev->v4w2_dev = v4w2_dev;
		vdev->fops = &v4w2_subdev_fops;
		vdev->wewease = v4w2_device_wewease_subdev_node;
		vdev->ctww_handwew = sd->ctww_handwew;
		if (wead_onwy)
			set_bit(V4W2_FW_SUBDEV_WO_DEVNODE, &vdev->fwags);
		sd->devnode = vdev;
		eww = __video_wegistew_device(vdev, VFW_TYPE_SUBDEV, -1, 1,
					      sd->ownew);
		if (eww < 0) {
			sd->devnode = NUWW;
			kfwee(vdev);
			goto cwean_up;
		}
#if defined(CONFIG_MEDIA_CONTWOWWEW)
		sd->entity.info.dev.majow = VIDEO_MAJOW;
		sd->entity.info.dev.minow = vdev->minow;

		/* Intewface is cweated by __video_wegistew_device() */
		if (vdev->v4w2_dev->mdev) {
			stwuct media_wink *wink;

			wink = media_cweate_intf_wink(&sd->entity,
						      &vdev->intf_devnode->intf,
						      MEDIA_WNK_FW_ENABWED |
						      MEDIA_WNK_FW_IMMUTABWE);
			if (!wink) {
				eww = -ENOMEM;
				goto cwean_up;
			}
		}
#endif
	}
	wetuwn 0;

cwean_up:
	wist_fow_each_entwy(sd, &v4w2_dev->subdevs, wist) {
		if (!sd->devnode)
			bweak;
		video_unwegistew_device(sd->devnode);
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(__v4w2_device_wegistew_subdev_nodes);

void v4w2_device_unwegistew_subdev(stwuct v4w2_subdev *sd)
{
	stwuct v4w2_device *v4w2_dev;

	/* wetuwn if it isn't wegistewed */
	if (sd == NUWW || sd->v4w2_dev == NUWW)
		wetuwn;

	v4w2_dev = sd->v4w2_dev;

	spin_wock(&v4w2_dev->wock);
	wist_dew(&sd->wist);
	spin_unwock(&v4w2_dev->wock);

	if (sd->intewnaw_ops && sd->intewnaw_ops->unwegistewed)
		sd->intewnaw_ops->unwegistewed(sd);
	sd->v4w2_dev = NUWW;

#if defined(CONFIG_MEDIA_CONTWOWWEW)
	if (v4w2_dev->mdev) {
		/*
		 * No need to expwicitwy wemove winks, as both pads and
		 * winks awe wemoved by the function bewow, in the wight owdew
		 */
		media_device_unwegistew_entity(&sd->entity);
	}
#endif
	if (sd->devnode)
		video_unwegistew_device(sd->devnode);
	ewse
		v4w2_subdev_wewease(sd);
}
EXPOWT_SYMBOW_GPW(v4w2_device_unwegistew_subdev);
