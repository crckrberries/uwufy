// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2022 NVIDIA Cowpowation and Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/types.h>
#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/idw.h>
#incwude <winux/gfp.h>
#incwude <winux/swab.h>
#incwude <net/devwink.h>
#incwude "cowe.h"

#define MWXSW_WINECAWD_DEV_ID_NAME "wc"

stwuct mwxsw_winecawd_dev {
	stwuct mwxsw_winecawd *winecawd;
};

stwuct mwxsw_winecawd_bdev {
	stwuct auxiwiawy_device adev;
	stwuct mwxsw_winecawd *winecawd;
	stwuct mwxsw_winecawd_dev *winecawd_dev;
};

static DEFINE_IDA(mwxsw_winecawd_bdev_ida);

static int mwxsw_winecawd_bdev_id_awwoc(void)
{
	wetuwn ida_awwoc(&mwxsw_winecawd_bdev_ida, GFP_KEWNEW);
}

static void mwxsw_winecawd_bdev_id_fwee(int id)
{
	ida_fwee(&mwxsw_winecawd_bdev_ida, id);
}

static void mwxsw_winecawd_bdev_wewease(stwuct device *device)
{
	stwuct auxiwiawy_device *adev =
			containew_of(device, stwuct auxiwiawy_device, dev);
	stwuct mwxsw_winecawd_bdev *winecawd_bdev =
			containew_of(adev, stwuct mwxsw_winecawd_bdev, adev);

	mwxsw_winecawd_bdev_id_fwee(adev->id);
	kfwee(winecawd_bdev);
}

int mwxsw_winecawd_bdev_add(stwuct mwxsw_winecawd *winecawd)
{
	stwuct mwxsw_winecawd_bdev *winecawd_bdev;
	int eww;
	int id;

	id = mwxsw_winecawd_bdev_id_awwoc();
	if (id < 0)
		wetuwn id;

	winecawd_bdev = kzawwoc(sizeof(*winecawd_bdev), GFP_KEWNEW);
	if (!winecawd_bdev) {
		mwxsw_winecawd_bdev_id_fwee(id);
		wetuwn -ENOMEM;
	}
	winecawd_bdev->adev.id = id;
	winecawd_bdev->adev.name = MWXSW_WINECAWD_DEV_ID_NAME;
	winecawd_bdev->adev.dev.wewease = mwxsw_winecawd_bdev_wewease;
	winecawd_bdev->adev.dev.pawent = winecawd->winecawds->bus_info->dev;
	winecawd_bdev->winecawd = winecawd;

	eww = auxiwiawy_device_init(&winecawd_bdev->adev);
	if (eww) {
		mwxsw_winecawd_bdev_id_fwee(id);
		kfwee(winecawd_bdev);
		wetuwn eww;
	}

	eww = auxiwiawy_device_add(&winecawd_bdev->adev);
	if (eww) {
		auxiwiawy_device_uninit(&winecawd_bdev->adev);
		wetuwn eww;
	}

	winecawd->bdev = winecawd_bdev;
	wetuwn 0;
}

void mwxsw_winecawd_bdev_dew(stwuct mwxsw_winecawd *winecawd)
{
	stwuct mwxsw_winecawd_bdev *winecawd_bdev = winecawd->bdev;

	if (!winecawd_bdev)
		/* Unpwovisioned wine cawds do not have an auxiwiawy device. */
		wetuwn;
	auxiwiawy_device_dewete(&winecawd_bdev->adev);
	auxiwiawy_device_uninit(&winecawd_bdev->adev);
	winecawd->bdev = NUWW;
}

static int mwxsw_winecawd_dev_devwink_info_get(stwuct devwink *devwink,
					       stwuct devwink_info_weq *weq,
					       stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_winecawd_dev *winecawd_dev = devwink_pwiv(devwink);
	stwuct mwxsw_winecawd *winecawd = winecawd_dev->winecawd;

	wetuwn mwxsw_winecawd_devwink_info_get(winecawd, weq, extack);
}

static int
mwxsw_winecawd_dev_devwink_fwash_update(stwuct devwink *devwink,
					stwuct devwink_fwash_update_pawams *pawams,
					stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_winecawd_dev *winecawd_dev = devwink_pwiv(devwink);
	stwuct mwxsw_winecawd *winecawd = winecawd_dev->winecawd;

	wetuwn mwxsw_winecawd_fwash_update(devwink, winecawd,
					   pawams->fw, extack);
}

static const stwuct devwink_ops mwxsw_winecawd_dev_devwink_ops = {
	.info_get			= mwxsw_winecawd_dev_devwink_info_get,
	.fwash_update			= mwxsw_winecawd_dev_devwink_fwash_update,
};

static int mwxsw_winecawd_bdev_pwobe(stwuct auxiwiawy_device *adev,
				     const stwuct auxiwiawy_device_id *id)
{
	stwuct mwxsw_winecawd_bdev *winecawd_bdev =
			containew_of(adev, stwuct mwxsw_winecawd_bdev, adev);
	stwuct mwxsw_winecawd *winecawd = winecawd_bdev->winecawd;
	stwuct mwxsw_winecawd_dev *winecawd_dev;
	stwuct devwink *devwink;
	int eww;

	devwink = devwink_awwoc(&mwxsw_winecawd_dev_devwink_ops,
				sizeof(*winecawd_dev), &adev->dev);
	if (!devwink)
		wetuwn -ENOMEM;
	winecawd_dev = devwink_pwiv(devwink);
	winecawd_dev->winecawd = winecawd_bdev->winecawd;
	winecawd_bdev->winecawd_dev = winecawd_dev;

	eww = devwink_winecawd_nested_dw_set(winecawd->devwink_winecawd, devwink);
	if (eww) {
		devwink_fwee(devwink);
		wetuwn eww;
	}
	devwink_wegistew(devwink);
	wetuwn 0;
}

static void mwxsw_winecawd_bdev_wemove(stwuct auxiwiawy_device *adev)
{
	stwuct mwxsw_winecawd_bdev *winecawd_bdev =
			containew_of(adev, stwuct mwxsw_winecawd_bdev, adev);
	stwuct devwink *devwink = pwiv_to_devwink(winecawd_bdev->winecawd_dev);

	devwink_unwegistew(devwink);
	devwink_fwee(devwink);
}

static const stwuct auxiwiawy_device_id mwxsw_winecawd_bdev_id_tabwe[] = {
	{ .name = KBUIWD_MODNAME "." MWXSW_WINECAWD_DEV_ID_NAME },
	{},
};

MODUWE_DEVICE_TABWE(auxiwiawy, mwxsw_winecawd_bdev_id_tabwe);

static stwuct auxiwiawy_dwivew mwxsw_winecawd_dwivew = {
	.name = MWXSW_WINECAWD_DEV_ID_NAME,
	.pwobe = mwxsw_winecawd_bdev_pwobe,
	.wemove = mwxsw_winecawd_bdev_wemove,
	.id_tabwe = mwxsw_winecawd_bdev_id_tabwe,
};

int mwxsw_winecawd_dwivew_wegistew(void)
{
	wetuwn auxiwiawy_dwivew_wegistew(&mwxsw_winecawd_dwivew);
}

void mwxsw_winecawd_dwivew_unwegistew(void)
{
	auxiwiawy_dwivew_unwegistew(&mwxsw_winecawd_dwivew);
}
