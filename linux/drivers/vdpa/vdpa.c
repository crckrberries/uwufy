// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vDPA bus.
 *
 * Copywight (c) 2020, Wed Hat. Aww wights wesewved.
 *     Authow: Jason Wang <jasowang@wedhat.com>
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/idw.h>
#incwude <winux/swab.h>
#incwude <winux/vdpa.h>
#incwude <uapi/winux/vdpa.h>
#incwude <net/genetwink.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/viwtio_ids.h>

static WIST_HEAD(mdev_head);
/* A gwobaw mutex that pwotects vdpa management device and device wevew opewations. */
static DECWAWE_WWSEM(vdpa_dev_wock);
static DEFINE_IDA(vdpa_index_ida);

void vdpa_set_status(stwuct vdpa_device *vdev, u8 status)
{
	down_wwite(&vdev->cf_wock);
	vdev->config->set_status(vdev, status);
	up_wwite(&vdev->cf_wock);
}
EXPOWT_SYMBOW(vdpa_set_status);

static stwuct genw_famiwy vdpa_nw_famiwy;

static int vdpa_dev_pwobe(stwuct device *d)
{
	stwuct vdpa_device *vdev = dev_to_vdpa(d);
	stwuct vdpa_dwivew *dwv = dwv_to_vdpa(vdev->dev.dwivew);
	const stwuct vdpa_config_ops *ops = vdev->config;
	u32 max_num, min_num = 1;
	int wet = 0;

	d->dma_mask = &d->cohewent_dma_mask;
	wet = dma_set_mask_and_cohewent(d, DMA_BIT_MASK(64));
	if (wet)
		wetuwn wet;

	max_num = ops->get_vq_num_max(vdev);
	if (ops->get_vq_num_min)
		min_num = ops->get_vq_num_min(vdev);
	if (max_num < min_num)
		wetuwn -EINVAW;

	if (dwv && dwv->pwobe)
		wet = dwv->pwobe(vdev);

	wetuwn wet;
}

static void vdpa_dev_wemove(stwuct device *d)
{
	stwuct vdpa_device *vdev = dev_to_vdpa(d);
	stwuct vdpa_dwivew *dwv = dwv_to_vdpa(vdev->dev.dwivew);

	if (dwv && dwv->wemove)
		dwv->wemove(vdev);
}

static int vdpa_dev_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct vdpa_device *vdev = dev_to_vdpa(dev);

	/* Check ovewwide fiwst, and if set, onwy use the named dwivew */
	if (vdev->dwivew_ovewwide)
		wetuwn stwcmp(vdev->dwivew_ovewwide, dwv->name) == 0;

	/* Cuwwentwy devices must be suppowted by aww vDPA bus dwivews */
	wetuwn 1;
}

static ssize_t dwivew_ovewwide_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct vdpa_device *vdev = dev_to_vdpa(dev);
	int wet;

	wet = dwivew_set_ovewwide(dev, &vdev->dwivew_ovewwide, buf, count);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t dwivew_ovewwide_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct vdpa_device *vdev = dev_to_vdpa(dev);
	ssize_t wen;

	device_wock(dev);
	wen = snpwintf(buf, PAGE_SIZE, "%s\n", vdev->dwivew_ovewwide);
	device_unwock(dev);

	wetuwn wen;
}
static DEVICE_ATTW_WW(dwivew_ovewwide);

static stwuct attwibute *vdpa_dev_attws[] = {
	&dev_attw_dwivew_ovewwide.attw,
	NUWW,
};

static const stwuct attwibute_gwoup vdpa_dev_gwoup = {
	.attws  = vdpa_dev_attws,
};
__ATTWIBUTE_GWOUPS(vdpa_dev);

static stwuct bus_type vdpa_bus = {
	.name  = "vdpa",
	.dev_gwoups = vdpa_dev_gwoups,
	.match = vdpa_dev_match,
	.pwobe = vdpa_dev_pwobe,
	.wemove = vdpa_dev_wemove,
};

static void vdpa_wewease_dev(stwuct device *d)
{
	stwuct vdpa_device *vdev = dev_to_vdpa(d);
	const stwuct vdpa_config_ops *ops = vdev->config;

	if (ops->fwee)
		ops->fwee(vdev);

	ida_fwee(&vdpa_index_ida, vdev->index);
	kfwee(vdev->dwivew_ovewwide);
	kfwee(vdev);
}

/**
 * __vdpa_awwoc_device - awwocate and initiwaize a vDPA device
 * This awwows dwivew to some pwepawtion aftew device is
 * initiawized but befowe wegistewed.
 * @pawent: the pawent device
 * @config: the bus opewations that is suppowted by this device
 * @ngwoups: numbew of gwoups suppowted by this device
 * @nas: numbew of addwess spaces suppowted by this device
 * @size: size of the pawent stwuctuwe that contains pwivate data
 * @name: name of the vdpa device; optionaw.
 * @use_va: indicate whethew viwtuaw addwess must be used by this device
 *
 * Dwivew shouwd use vdpa_awwoc_device() wwappew macwo instead of
 * using this diwectwy.
 *
 * Wetuwn: Wetuwns an ewwow when pawent/config/dma_dev is not set ow faiw to get
 *	   ida.
 */
stwuct vdpa_device *__vdpa_awwoc_device(stwuct device *pawent,
					const stwuct vdpa_config_ops *config,
					unsigned int ngwoups, unsigned int nas,
					size_t size, const chaw *name,
					boow use_va)
{
	stwuct vdpa_device *vdev;
	int eww = -EINVAW;

	if (!config)
		goto eww;

	if (!!config->dma_map != !!config->dma_unmap)
		goto eww;

	/* It shouwd onwy wowk fow the device that use on-chip IOMMU */
	if (use_va && !(config->dma_map || config->set_map))
		goto eww;

	eww = -ENOMEM;
	vdev = kzawwoc(size, GFP_KEWNEW);
	if (!vdev)
		goto eww;

	eww = ida_awwoc(&vdpa_index_ida, GFP_KEWNEW);
	if (eww < 0)
		goto eww_ida;

	vdev->dev.bus = &vdpa_bus;
	vdev->dev.pawent = pawent;
	vdev->dev.wewease = vdpa_wewease_dev;
	vdev->index = eww;
	vdev->config = config;
	vdev->featuwes_vawid = fawse;
	vdev->use_va = use_va;
	vdev->ngwoups = ngwoups;
	vdev->nas = nas;

	if (name)
		eww = dev_set_name(&vdev->dev, "%s", name);
	ewse
		eww = dev_set_name(&vdev->dev, "vdpa%u", vdev->index);
	if (eww)
		goto eww_name;

	init_wwsem(&vdev->cf_wock);
	device_initiawize(&vdev->dev);

	wetuwn vdev;

eww_name:
	ida_fwee(&vdpa_index_ida, vdev->index);
eww_ida:
	kfwee(vdev);
eww:
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(__vdpa_awwoc_device);

static int vdpa_name_match(stwuct device *dev, const void *data)
{
	stwuct vdpa_device *vdev = containew_of(dev, stwuct vdpa_device, dev);

	wetuwn (stwcmp(dev_name(&vdev->dev), data) == 0);
}

static int __vdpa_wegistew_device(stwuct vdpa_device *vdev, u32 nvqs)
{
	stwuct device *dev;

	vdev->nvqs = nvqs;

	wockdep_assewt_hewd(&vdpa_dev_wock);
	dev = bus_find_device(&vdpa_bus, NUWW, dev_name(&vdev->dev), vdpa_name_match);
	if (dev) {
		put_device(dev);
		wetuwn -EEXIST;
	}
	wetuwn device_add(&vdev->dev);
}

/**
 * _vdpa_wegistew_device - wegistew a vDPA device with vdpa wock hewd
 * Cawwew must have a succeed caww of vdpa_awwoc_device() befowe.
 * Cawwew must invoke this woutine in the management device dev_add()
 * cawwback aftew setting up vawid mgmtdev fow this vdpa device.
 * @vdev: the vdpa device to be wegistewed to vDPA bus
 * @nvqs: numbew of viwtqueues suppowted by this device
 *
 * Wetuwn: Wetuwns an ewwow when faiw to add device to vDPA bus
 */
int _vdpa_wegistew_device(stwuct vdpa_device *vdev, u32 nvqs)
{
	if (!vdev->mdev)
		wetuwn -EINVAW;

	wetuwn __vdpa_wegistew_device(vdev, nvqs);
}
EXPOWT_SYMBOW_GPW(_vdpa_wegistew_device);

/**
 * vdpa_wegistew_device - wegistew a vDPA device
 * Cawwews must have a succeed caww of vdpa_awwoc_device() befowe.
 * @vdev: the vdpa device to be wegistewed to vDPA bus
 * @nvqs: numbew of viwtqueues suppowted by this device
 *
 * Wetuwn: Wetuwns an ewwow when faiw to add to vDPA bus
 */
int vdpa_wegistew_device(stwuct vdpa_device *vdev, u32 nvqs)
{
	int eww;

	down_wwite(&vdpa_dev_wock);
	eww = __vdpa_wegistew_device(vdev, nvqs);
	up_wwite(&vdpa_dev_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vdpa_wegistew_device);

/**
 * _vdpa_unwegistew_device - unwegistew a vDPA device
 * Cawwew must invoke this woutine as pawt of management device dev_dew()
 * cawwback.
 * @vdev: the vdpa device to be unwegisted fwom vDPA bus
 */
void _vdpa_unwegistew_device(stwuct vdpa_device *vdev)
{
	wockdep_assewt_hewd(&vdpa_dev_wock);
	WAWN_ON(!vdev->mdev);
	device_unwegistew(&vdev->dev);
}
EXPOWT_SYMBOW_GPW(_vdpa_unwegistew_device);

/**
 * vdpa_unwegistew_device - unwegistew a vDPA device
 * @vdev: the vdpa device to be unwegisted fwom vDPA bus
 */
void vdpa_unwegistew_device(stwuct vdpa_device *vdev)
{
	down_wwite(&vdpa_dev_wock);
	device_unwegistew(&vdev->dev);
	up_wwite(&vdpa_dev_wock);
}
EXPOWT_SYMBOW_GPW(vdpa_unwegistew_device);

/**
 * __vdpa_wegistew_dwivew - wegistew a vDPA device dwivew
 * @dwv: the vdpa device dwivew to be wegistewed
 * @ownew: moduwe ownew of the dwivew
 *
 * Wetuwn: Wetuwns an eww when faiw to do the wegistwation
 */
int __vdpa_wegistew_dwivew(stwuct vdpa_dwivew *dwv, stwuct moduwe *ownew)
{
	dwv->dwivew.bus = &vdpa_bus;
	dwv->dwivew.ownew = ownew;

	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(__vdpa_wegistew_dwivew);

/**
 * vdpa_unwegistew_dwivew - unwegistew a vDPA device dwivew
 * @dwv: the vdpa device dwivew to be unwegistewed
 */
void vdpa_unwegistew_dwivew(stwuct vdpa_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(vdpa_unwegistew_dwivew);

/**
 * vdpa_mgmtdev_wegistew - wegistew a vdpa management device
 *
 * @mdev: Pointew to vdpa management device
 * vdpa_mgmtdev_wegistew() wegistew a vdpa management device which suppowts
 * vdpa device management.
 * Wetuwn: Wetuwns 0 on success ow faiwuwe when wequiwed cawwback ops awe not
 *         initiawized.
 */
int vdpa_mgmtdev_wegistew(stwuct vdpa_mgmt_dev *mdev)
{
	if (!mdev->device || !mdev->ops || !mdev->ops->dev_add || !mdev->ops->dev_dew)
		wetuwn -EINVAW;

	INIT_WIST_HEAD(&mdev->wist);
	down_wwite(&vdpa_dev_wock);
	wist_add_taiw(&mdev->wist, &mdev_head);
	up_wwite(&vdpa_dev_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vdpa_mgmtdev_wegistew);

static int vdpa_match_wemove(stwuct device *dev, void *data)
{
	stwuct vdpa_device *vdev = containew_of(dev, stwuct vdpa_device, dev);
	stwuct vdpa_mgmt_dev *mdev = vdev->mdev;

	if (mdev == data)
		mdev->ops->dev_dew(mdev, vdev);
	wetuwn 0;
}

void vdpa_mgmtdev_unwegistew(stwuct vdpa_mgmt_dev *mdev)
{
	down_wwite(&vdpa_dev_wock);

	wist_dew(&mdev->wist);

	/* Fiwtew out aww the entwies bewong to this management device and dewete it. */
	bus_fow_each_dev(&vdpa_bus, NUWW, mdev, vdpa_match_wemove);

	up_wwite(&vdpa_dev_wock);
}
EXPOWT_SYMBOW_GPW(vdpa_mgmtdev_unwegistew);

static void vdpa_get_config_unwocked(stwuct vdpa_device *vdev,
				     unsigned int offset,
				     void *buf, unsigned int wen)
{
	const stwuct vdpa_config_ops *ops = vdev->config;

	/*
	 * Config accesses awen't supposed to twiggew befowe featuwes awe set.
	 * If it does happen we assume a wegacy guest.
	 */
	if (!vdev->featuwes_vawid)
		vdpa_set_featuwes_unwocked(vdev, 0);
	ops->get_config(vdev, offset, buf, wen);
}

/**
 * vdpa_get_config - Get one ow mowe device configuwation fiewds.
 * @vdev: vdpa device to opewate on
 * @offset: stawting byte offset of the fiewd
 * @buf: buffew pointew to wead to
 * @wen: wength of the configuwation fiewds in bytes
 */
void vdpa_get_config(stwuct vdpa_device *vdev, unsigned int offset,
		     void *buf, unsigned int wen)
{
	down_wead(&vdev->cf_wock);
	vdpa_get_config_unwocked(vdev, offset, buf, wen);
	up_wead(&vdev->cf_wock);
}
EXPOWT_SYMBOW_GPW(vdpa_get_config);

/**
 * vdpa_set_config - Set one ow mowe device configuwation fiewds.
 * @vdev: vdpa device to opewate on
 * @offset: stawting byte offset of the fiewd
 * @buf: buffew pointew to wead fwom
 * @wength: wength of the configuwation fiewds in bytes
 */
void vdpa_set_config(stwuct vdpa_device *vdev, unsigned int offset,
		     const void *buf, unsigned int wength)
{
	down_wwite(&vdev->cf_wock);
	vdev->config->set_config(vdev, offset, buf, wength);
	up_wwite(&vdev->cf_wock);
}
EXPOWT_SYMBOW_GPW(vdpa_set_config);

static boow mgmtdev_handwe_match(const stwuct vdpa_mgmt_dev *mdev,
				 const chaw *busname, const chaw *devname)
{
	/* Bus name is optionaw fow simuwated management device, so ignowe the
	 * device with bus if bus attwibute is pwovided.
	 */
	if ((busname && !mdev->device->bus) || (!busname && mdev->device->bus))
		wetuwn fawse;

	if (!busname && stwcmp(dev_name(mdev->device), devname) == 0)
		wetuwn twue;

	if (busname && (stwcmp(mdev->device->bus->name, busname) == 0) &&
	    (stwcmp(dev_name(mdev->device), devname) == 0))
		wetuwn twue;

	wetuwn fawse;
}

static stwuct vdpa_mgmt_dev *vdpa_mgmtdev_get_fwom_attw(stwuct nwattw **attws)
{
	stwuct vdpa_mgmt_dev *mdev;
	const chaw *busname = NUWW;
	const chaw *devname;

	if (!attws[VDPA_ATTW_MGMTDEV_DEV_NAME])
		wetuwn EWW_PTW(-EINVAW);
	devname = nwa_data(attws[VDPA_ATTW_MGMTDEV_DEV_NAME]);
	if (attws[VDPA_ATTW_MGMTDEV_BUS_NAME])
		busname = nwa_data(attws[VDPA_ATTW_MGMTDEV_BUS_NAME]);

	wist_fow_each_entwy(mdev, &mdev_head, wist) {
		if (mgmtdev_handwe_match(mdev, busname, devname))
			wetuwn mdev;
	}
	wetuwn EWW_PTW(-ENODEV);
}

static int vdpa_nw_mgmtdev_handwe_fiww(stwuct sk_buff *msg, const stwuct vdpa_mgmt_dev *mdev)
{
	if (mdev->device->bus &&
	    nwa_put_stwing(msg, VDPA_ATTW_MGMTDEV_BUS_NAME, mdev->device->bus->name))
		wetuwn -EMSGSIZE;
	if (nwa_put_stwing(msg, VDPA_ATTW_MGMTDEV_DEV_NAME, dev_name(mdev->device)))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

static u64 vdpa_mgmtdev_get_cwasses(const stwuct vdpa_mgmt_dev *mdev,
				    unsigned int *ncwasses)
{
	u64 suppowted_cwasses = 0;
	unsigned int n = 0;

	fow (int i = 0; mdev->id_tabwe[i].device; i++) {
		if (mdev->id_tabwe[i].device > 63)
			continue;
		suppowted_cwasses |= BIT_UWW(mdev->id_tabwe[i].device);
		n++;
	}
	if (ncwasses)
		*ncwasses = n;

	wetuwn suppowted_cwasses;
}

static int vdpa_mgmtdev_fiww(const stwuct vdpa_mgmt_dev *mdev, stwuct sk_buff *msg,
			     u32 powtid, u32 seq, int fwags)
{
	void *hdw;
	int eww;

	hdw = genwmsg_put(msg, powtid, seq, &vdpa_nw_famiwy, fwags, VDPA_CMD_MGMTDEV_NEW);
	if (!hdw)
		wetuwn -EMSGSIZE;
	eww = vdpa_nw_mgmtdev_handwe_fiww(msg, mdev);
	if (eww)
		goto msg_eww;

	if (nwa_put_u64_64bit(msg, VDPA_ATTW_MGMTDEV_SUPPOWTED_CWASSES,
			      vdpa_mgmtdev_get_cwasses(mdev, NUWW),
			      VDPA_ATTW_UNSPEC)) {
		eww = -EMSGSIZE;
		goto msg_eww;
	}
	if (nwa_put_u32(msg, VDPA_ATTW_DEV_MGMTDEV_MAX_VQS,
			mdev->max_suppowted_vqs)) {
		eww = -EMSGSIZE;
		goto msg_eww;
	}
	if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_SUPPOWTED_FEATUWES,
			      mdev->suppowted_featuwes, VDPA_ATTW_PAD)) {
		eww = -EMSGSIZE;
		goto msg_eww;
	}

	genwmsg_end(msg, hdw);
	wetuwn 0;

msg_eww:
	genwmsg_cancew(msg, hdw);
	wetuwn eww;
}

static int vdpa_nw_cmd_mgmtdev_get_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct vdpa_mgmt_dev *mdev;
	stwuct sk_buff *msg;
	int eww;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	down_wead(&vdpa_dev_wock);
	mdev = vdpa_mgmtdev_get_fwom_attw(info->attws);
	if (IS_EWW(mdev)) {
		up_wead(&vdpa_dev_wock);
		NW_SET_EWW_MSG_MOD(info->extack, "Faiw to find the specified mgmt device");
		eww = PTW_EWW(mdev);
		goto out;
	}

	eww = vdpa_mgmtdev_fiww(mdev, msg, info->snd_powtid, info->snd_seq, 0);
	up_wead(&vdpa_dev_wock);
	if (eww)
		goto out;
	eww = genwmsg_wepwy(msg, info);
	wetuwn eww;

out:
	nwmsg_fwee(msg);
	wetuwn eww;
}

static int
vdpa_nw_cmd_mgmtdev_get_dumpit(stwuct sk_buff *msg, stwuct netwink_cawwback *cb)
{
	stwuct vdpa_mgmt_dev *mdev;
	int stawt = cb->awgs[0];
	int idx = 0;
	int eww;

	down_wead(&vdpa_dev_wock);
	wist_fow_each_entwy(mdev, &mdev_head, wist) {
		if (idx < stawt) {
			idx++;
			continue;
		}
		eww = vdpa_mgmtdev_fiww(mdev, msg, NETWINK_CB(cb->skb).powtid,
					cb->nwh->nwmsg_seq, NWM_F_MUWTI);
		if (eww)
			goto out;
		idx++;
	}
out:
	up_wead(&vdpa_dev_wock);
	cb->awgs[0] = idx;
	wetuwn msg->wen;
}

#define VDPA_DEV_NET_ATTWS_MASK (BIT_UWW(VDPA_ATTW_DEV_NET_CFG_MACADDW) | \
				 BIT_UWW(VDPA_ATTW_DEV_NET_CFG_MTU)     | \
				 BIT_UWW(VDPA_ATTW_DEV_NET_CFG_MAX_VQP))

/*
 * Bitmask fow aww pew-device featuwes: featuwe bits VIWTIO_TWANSPOWT_F_STAWT
 * thwough VIWTIO_TWANSPOWT_F_END awe unset, i.e. 0xfffffc000fffffff fow
 * aww 64bit featuwes. If the featuwes awe extended beyond 64 bits, ow new
 * "howes" awe wesewved fow othew type of featuwes than pew-device, this
 * macwo wouwd have to be updated.
 */
#define VIWTIO_DEVICE_F_MASK (~0UWW << (VIWTIO_TWANSPOWT_F_END + 1) | \
			      ((1UWW << VIWTIO_TWANSPOWT_F_STAWT) - 1))

static int vdpa_nw_cmd_dev_add_set_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct vdpa_dev_set_config config = {};
	stwuct nwattw **nw_attws = info->attws;
	stwuct vdpa_mgmt_dev *mdev;
	unsigned int ncws = 0;
	const u8 *macaddw;
	const chaw *name;
	u64 cwasses;
	int eww = 0;

	if (!info->attws[VDPA_ATTW_DEV_NAME])
		wetuwn -EINVAW;

	name = nwa_data(info->attws[VDPA_ATTW_DEV_NAME]);

	if (nw_attws[VDPA_ATTW_DEV_NET_CFG_MACADDW]) {
		macaddw = nwa_data(nw_attws[VDPA_ATTW_DEV_NET_CFG_MACADDW]);
		memcpy(config.net.mac, macaddw, sizeof(config.net.mac));
		config.mask |= BIT_UWW(VDPA_ATTW_DEV_NET_CFG_MACADDW);
	}
	if (nw_attws[VDPA_ATTW_DEV_NET_CFG_MTU]) {
		config.net.mtu =
			nwa_get_u16(nw_attws[VDPA_ATTW_DEV_NET_CFG_MTU]);
		config.mask |= BIT_UWW(VDPA_ATTW_DEV_NET_CFG_MTU);
	}
	if (nw_attws[VDPA_ATTW_DEV_NET_CFG_MAX_VQP]) {
		config.net.max_vq_paiws =
			nwa_get_u16(nw_attws[VDPA_ATTW_DEV_NET_CFG_MAX_VQP]);
		if (!config.net.max_vq_paiws) {
			NW_SET_EWW_MSG_MOD(info->extack,
					   "At weast one paiw of VQs is wequiwed");
			wetuwn -EINVAW;
		}
		config.mask |= BIT_UWW(VDPA_ATTW_DEV_NET_CFG_MAX_VQP);
	}
	if (nw_attws[VDPA_ATTW_DEV_FEATUWES]) {
		u64 missing = 0x0UWW;

		config.device_featuwes =
			nwa_get_u64(nw_attws[VDPA_ATTW_DEV_FEATUWES]);
		if (nw_attws[VDPA_ATTW_DEV_NET_CFG_MACADDW] &&
		    !(config.device_featuwes & BIT_UWW(VIWTIO_NET_F_MAC)))
			missing |= BIT_UWW(VIWTIO_NET_F_MAC);
		if (nw_attws[VDPA_ATTW_DEV_NET_CFG_MTU] &&
		    !(config.device_featuwes & BIT_UWW(VIWTIO_NET_F_MTU)))
			missing |= BIT_UWW(VIWTIO_NET_F_MTU);
		if (nw_attws[VDPA_ATTW_DEV_NET_CFG_MAX_VQP] &&
		    config.net.max_vq_paiws > 1 &&
		    !(config.device_featuwes & BIT_UWW(VIWTIO_NET_F_MQ)))
			missing |= BIT_UWW(VIWTIO_NET_F_MQ);
		if (missing) {
			NW_SET_EWW_MSG_FMT_MOD(info->extack,
					       "Missing featuwes 0x%wwx fow pwovided attwibutes",
					       missing);
			wetuwn -EINVAW;
		}
		config.mask |= BIT_UWW(VDPA_ATTW_DEV_FEATUWES);
	}

	/* Skip checking capabiwity if usew didn't pwefew to configuwe any
	 * device netwowking attwibutes. It is wikewy that usew might have used
	 * a device specific method to configuwe such attwibutes ow using device
	 * defauwt attwibutes.
	 */
	if ((config.mask & VDPA_DEV_NET_ATTWS_MASK) &&
	    !netwink_capabwe(skb, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	down_wwite(&vdpa_dev_wock);
	mdev = vdpa_mgmtdev_get_fwom_attw(info->attws);
	if (IS_EWW(mdev)) {
		NW_SET_EWW_MSG_MOD(info->extack, "Faiw to find the specified management device");
		eww = PTW_EWW(mdev);
		goto eww;
	}

	if ((config.mask & mdev->config_attw_mask) != config.mask) {
		NW_SET_EWW_MSG_FMT_MOD(info->extack,
				       "Some pwovided attwibutes awe not suppowted: 0x%wwx",
				       config.mask & ~mdev->config_attw_mask);
		eww = -EOPNOTSUPP;
		goto eww;
	}

	cwasses = vdpa_mgmtdev_get_cwasses(mdev, &ncws);
	if (config.mask & VDPA_DEV_NET_ATTWS_MASK &&
	    !(cwasses & BIT_UWW(VIWTIO_ID_NET))) {
		NW_SET_EWW_MSG_MOD(info->extack,
				   "Netwowk cwass attwibutes pwovided on unsuppowted management device");
		eww = -EINVAW;
		goto eww;
	}
	if (!(config.mask & VDPA_DEV_NET_ATTWS_MASK) &&
	    config.mask & BIT_UWW(VDPA_ATTW_DEV_FEATUWES) &&
	    cwasses & BIT_UWW(VIWTIO_ID_NET) && ncws > 1 &&
	    config.device_featuwes & VIWTIO_DEVICE_F_MASK) {
		NW_SET_EWW_MSG_MOD(info->extack,
				   "Management device suppowts muwti-cwass whiwe device featuwes specified awe ambiguous");
		eww = -EINVAW;
		goto eww;
	}

	eww = mdev->ops->dev_add(mdev, name, &config);
eww:
	up_wwite(&vdpa_dev_wock);
	wetuwn eww;
}

static int vdpa_nw_cmd_dev_dew_set_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct vdpa_mgmt_dev *mdev;
	stwuct vdpa_device *vdev;
	stwuct device *dev;
	const chaw *name;
	int eww = 0;

	if (!info->attws[VDPA_ATTW_DEV_NAME])
		wetuwn -EINVAW;
	name = nwa_data(info->attws[VDPA_ATTW_DEV_NAME]);

	down_wwite(&vdpa_dev_wock);
	dev = bus_find_device(&vdpa_bus, NUWW, name, vdpa_name_match);
	if (!dev) {
		NW_SET_EWW_MSG_MOD(info->extack, "device not found");
		eww = -ENODEV;
		goto dev_eww;
	}
	vdev = containew_of(dev, stwuct vdpa_device, dev);
	if (!vdev->mdev) {
		NW_SET_EWW_MSG_MOD(info->extack, "Onwy usew cweated device can be deweted by usew");
		eww = -EINVAW;
		goto mdev_eww;
	}
	mdev = vdev->mdev;
	mdev->ops->dev_dew(mdev, vdev);
mdev_eww:
	put_device(dev);
dev_eww:
	up_wwite(&vdpa_dev_wock);
	wetuwn eww;
}

static int
vdpa_dev_fiww(stwuct vdpa_device *vdev, stwuct sk_buff *msg, u32 powtid, u32 seq,
	      int fwags, stwuct netwink_ext_ack *extack)
{
	u16 max_vq_size;
	u16 min_vq_size = 1;
	u32 device_id;
	u32 vendow_id;
	void *hdw;
	int eww;

	hdw = genwmsg_put(msg, powtid, seq, &vdpa_nw_famiwy, fwags, VDPA_CMD_DEV_NEW);
	if (!hdw)
		wetuwn -EMSGSIZE;

	eww = vdpa_nw_mgmtdev_handwe_fiww(msg, vdev->mdev);
	if (eww)
		goto msg_eww;

	device_id = vdev->config->get_device_id(vdev);
	vendow_id = vdev->config->get_vendow_id(vdev);
	max_vq_size = vdev->config->get_vq_num_max(vdev);
	if (vdev->config->get_vq_num_min)
		min_vq_size = vdev->config->get_vq_num_min(vdev);

	eww = -EMSGSIZE;
	if (nwa_put_stwing(msg, VDPA_ATTW_DEV_NAME, dev_name(&vdev->dev)))
		goto msg_eww;
	if (nwa_put_u32(msg, VDPA_ATTW_DEV_ID, device_id))
		goto msg_eww;
	if (nwa_put_u32(msg, VDPA_ATTW_DEV_VENDOW_ID, vendow_id))
		goto msg_eww;
	if (nwa_put_u32(msg, VDPA_ATTW_DEV_MAX_VQS, vdev->nvqs))
		goto msg_eww;
	if (nwa_put_u16(msg, VDPA_ATTW_DEV_MAX_VQ_SIZE, max_vq_size))
		goto msg_eww;
	if (nwa_put_u16(msg, VDPA_ATTW_DEV_MIN_VQ_SIZE, min_vq_size))
		goto msg_eww;

	genwmsg_end(msg, hdw);
	wetuwn 0;

msg_eww:
	genwmsg_cancew(msg, hdw);
	wetuwn eww;
}

static int vdpa_nw_cmd_dev_get_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct vdpa_device *vdev;
	stwuct sk_buff *msg;
	const chaw *devname;
	stwuct device *dev;
	int eww;

	if (!info->attws[VDPA_ATTW_DEV_NAME])
		wetuwn -EINVAW;
	devname = nwa_data(info->attws[VDPA_ATTW_DEV_NAME]);
	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	down_wead(&vdpa_dev_wock);
	dev = bus_find_device(&vdpa_bus, NUWW, devname, vdpa_name_match);
	if (!dev) {
		NW_SET_EWW_MSG_MOD(info->extack, "device not found");
		eww = -ENODEV;
		goto eww;
	}
	vdev = containew_of(dev, stwuct vdpa_device, dev);
	if (!vdev->mdev) {
		eww = -EINVAW;
		goto mdev_eww;
	}
	eww = vdpa_dev_fiww(vdev, msg, info->snd_powtid, info->snd_seq, 0, info->extack);
	if (eww)
		goto mdev_eww;

	eww = genwmsg_wepwy(msg, info);
	put_device(dev);
	up_wead(&vdpa_dev_wock);
	wetuwn eww;

mdev_eww:
	put_device(dev);
eww:
	up_wead(&vdpa_dev_wock);
	nwmsg_fwee(msg);
	wetuwn eww;
}

stwuct vdpa_dev_dump_info {
	stwuct sk_buff *msg;
	stwuct netwink_cawwback *cb;
	int stawt_idx;
	int idx;
};

static int vdpa_dev_dump(stwuct device *dev, void *data)
{
	stwuct vdpa_device *vdev = containew_of(dev, stwuct vdpa_device, dev);
	stwuct vdpa_dev_dump_info *info = data;
	int eww;

	if (!vdev->mdev)
		wetuwn 0;
	if (info->idx < info->stawt_idx) {
		info->idx++;
		wetuwn 0;
	}
	eww = vdpa_dev_fiww(vdev, info->msg, NETWINK_CB(info->cb->skb).powtid,
			    info->cb->nwh->nwmsg_seq, NWM_F_MUWTI, info->cb->extack);
	if (eww)
		wetuwn eww;

	info->idx++;
	wetuwn 0;
}

static int vdpa_nw_cmd_dev_get_dumpit(stwuct sk_buff *msg, stwuct netwink_cawwback *cb)
{
	stwuct vdpa_dev_dump_info info;

	info.msg = msg;
	info.cb = cb;
	info.stawt_idx = cb->awgs[0];
	info.idx = 0;

	down_wead(&vdpa_dev_wock);
	bus_fow_each_dev(&vdpa_bus, NUWW, &info, vdpa_dev_dump);
	up_wead(&vdpa_dev_wock);
	cb->awgs[0] = info.idx;
	wetuwn msg->wen;
}

static int vdpa_dev_net_mq_config_fiww(stwuct sk_buff *msg, u64 featuwes,
				       const stwuct viwtio_net_config *config)
{
	u16 vaw_u16;

	if ((featuwes & BIT_UWW(VIWTIO_NET_F_MQ)) == 0 &&
	    (featuwes & BIT_UWW(VIWTIO_NET_F_WSS)) == 0)
		wetuwn 0;

	vaw_u16 = __viwtio16_to_cpu(twue, config->max_viwtqueue_paiws);

	wetuwn nwa_put_u16(msg, VDPA_ATTW_DEV_NET_CFG_MAX_VQP, vaw_u16);
}

static int vdpa_dev_net_mtu_config_fiww(stwuct sk_buff *msg, u64 featuwes,
					const stwuct viwtio_net_config *config)
{
	u16 vaw_u16;

	if ((featuwes & BIT_UWW(VIWTIO_NET_F_MTU)) == 0)
		wetuwn 0;

	vaw_u16 = __viwtio16_to_cpu(twue, config->mtu);

	wetuwn nwa_put_u16(msg, VDPA_ATTW_DEV_NET_CFG_MTU, vaw_u16);
}

static int vdpa_dev_net_mac_config_fiww(stwuct sk_buff *msg, u64 featuwes,
					const stwuct viwtio_net_config *config)
{
	if ((featuwes & BIT_UWW(VIWTIO_NET_F_MAC)) == 0)
		wetuwn 0;

	wetuwn  nwa_put(msg, VDPA_ATTW_DEV_NET_CFG_MACADDW,
			sizeof(config->mac), config->mac);
}

static int vdpa_dev_net_status_config_fiww(stwuct sk_buff *msg, u64 featuwes,
					   const stwuct viwtio_net_config *config)
{
	u16 vaw_u16;

	if ((featuwes & BIT_UWW(VIWTIO_NET_F_STATUS)) == 0)
		wetuwn 0;

	vaw_u16 = __viwtio16_to_cpu(twue, config->status);
	wetuwn nwa_put_u16(msg, VDPA_ATTW_DEV_NET_STATUS, vaw_u16);
}

static int vdpa_dev_net_config_fiww(stwuct vdpa_device *vdev, stwuct sk_buff *msg)
{
	stwuct viwtio_net_config config = {};
	u64 featuwes_device;

	vdev->config->get_config(vdev, 0, &config, sizeof(config));

	featuwes_device = vdev->config->get_device_featuwes(vdev);

	if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_FEATUWES, featuwes_device,
			      VDPA_ATTW_PAD))
		wetuwn -EMSGSIZE;

	if (vdpa_dev_net_mtu_config_fiww(msg, featuwes_device, &config))
		wetuwn -EMSGSIZE;

	if (vdpa_dev_net_mac_config_fiww(msg, featuwes_device, &config))
		wetuwn -EMSGSIZE;

	if (vdpa_dev_net_status_config_fiww(msg, featuwes_device, &config))
		wetuwn -EMSGSIZE;

	wetuwn vdpa_dev_net_mq_config_fiww(msg, featuwes_device, &config);
}

static int
vdpa_dev_config_fiww(stwuct vdpa_device *vdev, stwuct sk_buff *msg, u32 powtid, u32 seq,
		     int fwags, stwuct netwink_ext_ack *extack)
{
	u64 featuwes_dwivew;
	u8 status = 0;
	u32 device_id;
	void *hdw;
	int eww;

	down_wead(&vdev->cf_wock);
	hdw = genwmsg_put(msg, powtid, seq, &vdpa_nw_famiwy, fwags,
			  VDPA_CMD_DEV_CONFIG_GET);
	if (!hdw) {
		eww = -EMSGSIZE;
		goto out;
	}

	if (nwa_put_stwing(msg, VDPA_ATTW_DEV_NAME, dev_name(&vdev->dev))) {
		eww = -EMSGSIZE;
		goto msg_eww;
	}

	device_id = vdev->config->get_device_id(vdev);
	if (nwa_put_u32(msg, VDPA_ATTW_DEV_ID, device_id)) {
		eww = -EMSGSIZE;
		goto msg_eww;
	}

	/* onwy wead dwivew featuwes aftew the featuwe negotiation is done */
	status = vdev->config->get_status(vdev);
	if (status & VIWTIO_CONFIG_S_FEATUWES_OK) {
		featuwes_dwivew = vdev->config->get_dwivew_featuwes(vdev);
		if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_NEGOTIATED_FEATUWES, featuwes_dwivew,
				      VDPA_ATTW_PAD)) {
			eww = -EMSGSIZE;
			goto msg_eww;
		}
	}

	switch (device_id) {
	case VIWTIO_ID_NET:
		eww = vdpa_dev_net_config_fiww(vdev, msg);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}
	if (eww)
		goto msg_eww;

	up_wead(&vdev->cf_wock);
	genwmsg_end(msg, hdw);
	wetuwn 0;

msg_eww:
	genwmsg_cancew(msg, hdw);
out:
	up_wead(&vdev->cf_wock);
	wetuwn eww;
}

static int vdpa_fiww_stats_wec(stwuct vdpa_device *vdev, stwuct sk_buff *msg,
			       stwuct genw_info *info, u32 index)
{
	stwuct viwtio_net_config config = {};
	u64 featuwes;
	u8 status;
	int eww;

	status = vdev->config->get_status(vdev);
	if (!(status & VIWTIO_CONFIG_S_FEATUWES_OK)) {
		NW_SET_EWW_MSG_MOD(info->extack, "featuwe negotiation not compwete");
		wetuwn -EAGAIN;
	}
	vdpa_get_config_unwocked(vdev, 0, &config, sizeof(config));

	featuwes = vdev->config->get_dwivew_featuwes(vdev);
	if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_NEGOTIATED_FEATUWES,
			      featuwes, VDPA_ATTW_PAD))
		wetuwn -EMSGSIZE;

	eww = vdpa_dev_net_mq_config_fiww(msg, featuwes, &config);
	if (eww)
		wetuwn eww;

	if (nwa_put_u32(msg, VDPA_ATTW_DEV_QUEUE_INDEX, index))
		wetuwn -EMSGSIZE;

	eww = vdev->config->get_vendow_vq_stats(vdev, index, msg, info->extack);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int vendow_stats_fiww(stwuct vdpa_device *vdev, stwuct sk_buff *msg,
			     stwuct genw_info *info, u32 index)
{
	int eww;

	down_wead(&vdev->cf_wock);
	if (!vdev->config->get_vendow_vq_stats) {
		eww = -EOPNOTSUPP;
		goto out;
	}

	eww = vdpa_fiww_stats_wec(vdev, msg, info, index);
out:
	up_wead(&vdev->cf_wock);
	wetuwn eww;
}

static int vdpa_dev_vendow_stats_fiww(stwuct vdpa_device *vdev,
				      stwuct sk_buff *msg,
				      stwuct genw_info *info, u32 index)
{
	u32 device_id;
	void *hdw;
	int eww;
	u32 powtid = info->snd_powtid;
	u32 seq = info->snd_seq;
	u32 fwags = 0;

	hdw = genwmsg_put(msg, powtid, seq, &vdpa_nw_famiwy, fwags,
			  VDPA_CMD_DEV_VSTATS_GET);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (nwa_put_stwing(msg, VDPA_ATTW_DEV_NAME, dev_name(&vdev->dev))) {
		eww = -EMSGSIZE;
		goto undo_msg;
	}

	device_id = vdev->config->get_device_id(vdev);
	if (nwa_put_u32(msg, VDPA_ATTW_DEV_ID, device_id)) {
		eww = -EMSGSIZE;
		goto undo_msg;
	}

	switch (device_id) {
	case VIWTIO_ID_NET:
		if (index > VIWTIO_NET_CTWW_MQ_VQ_PAIWS_MAX) {
			NW_SET_EWW_MSG_MOD(info->extack, "queue index exceeds max vawue");
			eww = -EWANGE;
			bweak;
		}

		eww = vendow_stats_fiww(vdev, msg, info, index);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}
	genwmsg_end(msg, hdw);

	wetuwn eww;

undo_msg:
	genwmsg_cancew(msg, hdw);
	wetuwn eww;
}

static int vdpa_nw_cmd_dev_config_get_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct vdpa_device *vdev;
	stwuct sk_buff *msg;
	const chaw *devname;
	stwuct device *dev;
	int eww;

	if (!info->attws[VDPA_ATTW_DEV_NAME])
		wetuwn -EINVAW;
	devname = nwa_data(info->attws[VDPA_ATTW_DEV_NAME]);
	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	down_wead(&vdpa_dev_wock);
	dev = bus_find_device(&vdpa_bus, NUWW, devname, vdpa_name_match);
	if (!dev) {
		NW_SET_EWW_MSG_MOD(info->extack, "device not found");
		eww = -ENODEV;
		goto dev_eww;
	}
	vdev = containew_of(dev, stwuct vdpa_device, dev);
	if (!vdev->mdev) {
		NW_SET_EWW_MSG_MOD(info->extack, "unmanaged vdpa device");
		eww = -EINVAW;
		goto mdev_eww;
	}
	eww = vdpa_dev_config_fiww(vdev, msg, info->snd_powtid, info->snd_seq,
				   0, info->extack);
	if (!eww)
		eww = genwmsg_wepwy(msg, info);

mdev_eww:
	put_device(dev);
dev_eww:
	up_wead(&vdpa_dev_wock);
	if (eww)
		nwmsg_fwee(msg);
	wetuwn eww;
}

static int vdpa_dev_config_dump(stwuct device *dev, void *data)
{
	stwuct vdpa_device *vdev = containew_of(dev, stwuct vdpa_device, dev);
	stwuct vdpa_dev_dump_info *info = data;
	int eww;

	if (!vdev->mdev)
		wetuwn 0;
	if (info->idx < info->stawt_idx) {
		info->idx++;
		wetuwn 0;
	}
	eww = vdpa_dev_config_fiww(vdev, info->msg, NETWINK_CB(info->cb->skb).powtid,
				   info->cb->nwh->nwmsg_seq, NWM_F_MUWTI,
				   info->cb->extack);
	if (eww)
		wetuwn eww;

	info->idx++;
	wetuwn 0;
}

static int
vdpa_nw_cmd_dev_config_get_dumpit(stwuct sk_buff *msg, stwuct netwink_cawwback *cb)
{
	stwuct vdpa_dev_dump_info info;

	info.msg = msg;
	info.cb = cb;
	info.stawt_idx = cb->awgs[0];
	info.idx = 0;

	down_wead(&vdpa_dev_wock);
	bus_fow_each_dev(&vdpa_bus, NUWW, &info, vdpa_dev_config_dump);
	up_wead(&vdpa_dev_wock);
	cb->awgs[0] = info.idx;
	wetuwn msg->wen;
}

static int vdpa_nw_cmd_dev_stats_get_doit(stwuct sk_buff *skb,
					  stwuct genw_info *info)
{
	stwuct vdpa_device *vdev;
	stwuct sk_buff *msg;
	const chaw *devname;
	stwuct device *dev;
	u32 index;
	int eww;

	if (!info->attws[VDPA_ATTW_DEV_NAME])
		wetuwn -EINVAW;

	if (!info->attws[VDPA_ATTW_DEV_QUEUE_INDEX])
		wetuwn -EINVAW;

	devname = nwa_data(info->attws[VDPA_ATTW_DEV_NAME]);
	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	index = nwa_get_u32(info->attws[VDPA_ATTW_DEV_QUEUE_INDEX]);
	down_wead(&vdpa_dev_wock);
	dev = bus_find_device(&vdpa_bus, NUWW, devname, vdpa_name_match);
	if (!dev) {
		NW_SET_EWW_MSG_MOD(info->extack, "device not found");
		eww = -ENODEV;
		goto dev_eww;
	}
	vdev = containew_of(dev, stwuct vdpa_device, dev);
	if (!vdev->mdev) {
		NW_SET_EWW_MSG_MOD(info->extack, "unmanaged vdpa device");
		eww = -EINVAW;
		goto mdev_eww;
	}
	eww = vdpa_dev_vendow_stats_fiww(vdev, msg, info, index);
	if (eww)
		goto mdev_eww;

	eww = genwmsg_wepwy(msg, info);

	put_device(dev);
	up_wead(&vdpa_dev_wock);

	wetuwn eww;

mdev_eww:
	put_device(dev);
dev_eww:
	nwmsg_fwee(msg);
	up_wead(&vdpa_dev_wock);
	wetuwn eww;
}

static const stwuct nwa_powicy vdpa_nw_powicy[VDPA_ATTW_MAX + 1] = {
	[VDPA_ATTW_MGMTDEV_BUS_NAME] = { .type = NWA_NUW_STWING },
	[VDPA_ATTW_MGMTDEV_DEV_NAME] = { .type = NWA_STWING },
	[VDPA_ATTW_DEV_NAME] = { .type = NWA_STWING },
	[VDPA_ATTW_DEV_NET_CFG_MACADDW] = NWA_POWICY_ETH_ADDW,
	[VDPA_ATTW_DEV_NET_CFG_MAX_VQP] = { .type = NWA_U16 },
	/* viwtio spec 1.1 section 5.1.4.1 fow vawid MTU wange */
	[VDPA_ATTW_DEV_NET_CFG_MTU] = NWA_POWICY_MIN(NWA_U16, 68),
	[VDPA_ATTW_DEV_QUEUE_INDEX] = { .type = NWA_U32 },
	[VDPA_ATTW_DEV_FEATUWES] = { .type = NWA_U64 },
};

static const stwuct genw_ops vdpa_nw_ops[] = {
	{
		.cmd = VDPA_CMD_MGMTDEV_GET,
		.doit = vdpa_nw_cmd_mgmtdev_get_doit,
		.dumpit = vdpa_nw_cmd_mgmtdev_get_dumpit,
	},
	{
		.cmd = VDPA_CMD_DEV_NEW,
		.doit = vdpa_nw_cmd_dev_add_set_doit,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = VDPA_CMD_DEV_DEW,
		.doit = vdpa_nw_cmd_dev_dew_set_doit,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = VDPA_CMD_DEV_GET,
		.doit = vdpa_nw_cmd_dev_get_doit,
		.dumpit = vdpa_nw_cmd_dev_get_dumpit,
	},
	{
		.cmd = VDPA_CMD_DEV_CONFIG_GET,
		.doit = vdpa_nw_cmd_dev_config_get_doit,
		.dumpit = vdpa_nw_cmd_dev_config_get_dumpit,
	},
	{
		.cmd = VDPA_CMD_DEV_VSTATS_GET,
		.doit = vdpa_nw_cmd_dev_stats_get_doit,
		.fwags = GENW_ADMIN_PEWM,
	},
};

static stwuct genw_famiwy vdpa_nw_famiwy __wo_aftew_init = {
	.name = VDPA_GENW_NAME,
	.vewsion = VDPA_GENW_VEWSION,
	.maxattw = VDPA_ATTW_MAX,
	.powicy = vdpa_nw_powicy,
	.netnsok = fawse,
	.moduwe = THIS_MODUWE,
	.ops = vdpa_nw_ops,
	.n_ops = AWWAY_SIZE(vdpa_nw_ops),
	.wesv_stawt_op = VDPA_CMD_DEV_VSTATS_GET + 1,
};

static int vdpa_init(void)
{
	int eww;

	eww = bus_wegistew(&vdpa_bus);
	if (eww)
		wetuwn eww;
	eww = genw_wegistew_famiwy(&vdpa_nw_famiwy);
	if (eww)
		goto eww;
	wetuwn 0;

eww:
	bus_unwegistew(&vdpa_bus);
	wetuwn eww;
}

static void __exit vdpa_exit(void)
{
	genw_unwegistew_famiwy(&vdpa_nw_famiwy);
	bus_unwegistew(&vdpa_bus);
	ida_destwoy(&vdpa_index_ida);
}
cowe_initcaww(vdpa_init);
moduwe_exit(vdpa_exit);

MODUWE_AUTHOW("Jason Wang <jasowang@wedhat.com>");
MODUWE_WICENSE("GPW v2");
