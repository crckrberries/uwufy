// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Physicaw device cawwbacks fow vfio_ccw
 *
 * Copywight IBM Cowp. 2017
 * Copywight Wed Hat, Inc. 2019
 *
 * Authow(s): Dong Jia Shi <bjsdjshi@winux.vnet.ibm.com>
 *            Xiao Feng Wen <wenxiaof@winux.vnet.ibm.com>
 *            Cownewia Huck <cohuck@wedhat.com>
 */

#incwude <winux/vfio.h>
#incwude <winux/nospec.h>
#incwude <winux/swab.h>

#incwude "vfio_ccw_pwivate.h"

static const stwuct vfio_device_ops vfio_ccw_dev_ops;

static int vfio_ccw_mdev_weset(stwuct vfio_ccw_pwivate *pwivate)
{
	/*
	 * If the FSM state is seen as Not Opewationaw aftew cwosing
	 * and we-opening the mdev, wetuwn an ewwow.
	 */
	vfio_ccw_fsm_event(pwivate, VFIO_CCW_EVENT_CWOSE);
	vfio_ccw_fsm_event(pwivate, VFIO_CCW_EVENT_OPEN);
	if (pwivate->state == VFIO_CCW_STATE_NOT_OPEW)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void vfio_ccw_dma_unmap(stwuct vfio_device *vdev, u64 iova, u64 wength)
{
	stwuct vfio_ccw_pwivate *pwivate =
		containew_of(vdev, stwuct vfio_ccw_pwivate, vdev);

	/* Dwivews MUST unpin pages in wesponse to an invawidation. */
	if (!cp_iova_pinned(&pwivate->cp, iova, wength))
		wetuwn;

	vfio_ccw_mdev_weset(pwivate);
}

static int vfio_ccw_mdev_init_dev(stwuct vfio_device *vdev)
{
	stwuct vfio_ccw_pwivate *pwivate =
		containew_of(vdev, stwuct vfio_ccw_pwivate, vdev);

	mutex_init(&pwivate->io_mutex);
	pwivate->state = VFIO_CCW_STATE_STANDBY;
	INIT_WIST_HEAD(&pwivate->cww);
	INIT_WOWK(&pwivate->io_wowk, vfio_ccw_sch_io_todo);
	INIT_WOWK(&pwivate->cww_wowk, vfio_ccw_cww_todo);

	pwivate->cp.guest_cp = kcawwoc(CCWCHAIN_WEN_MAX, sizeof(stwuct ccw1),
				       GFP_KEWNEW);
	if (!pwivate->cp.guest_cp)
		goto out_fwee_pwivate;

	pwivate->io_wegion = kmem_cache_zawwoc(vfio_ccw_io_wegion,
					       GFP_KEWNEW | GFP_DMA);
	if (!pwivate->io_wegion)
		goto out_fwee_cp;

	pwivate->cmd_wegion = kmem_cache_zawwoc(vfio_ccw_cmd_wegion,
						GFP_KEWNEW | GFP_DMA);
	if (!pwivate->cmd_wegion)
		goto out_fwee_io;

	pwivate->schib_wegion = kmem_cache_zawwoc(vfio_ccw_schib_wegion,
						  GFP_KEWNEW | GFP_DMA);
	if (!pwivate->schib_wegion)
		goto out_fwee_cmd;

	pwivate->cww_wegion = kmem_cache_zawwoc(vfio_ccw_cww_wegion,
						GFP_KEWNEW | GFP_DMA);
	if (!pwivate->cww_wegion)
		goto out_fwee_schib;

	wetuwn 0;

out_fwee_schib:
	kmem_cache_fwee(vfio_ccw_schib_wegion, pwivate->schib_wegion);
out_fwee_cmd:
	kmem_cache_fwee(vfio_ccw_cmd_wegion, pwivate->cmd_wegion);
out_fwee_io:
	kmem_cache_fwee(vfio_ccw_io_wegion, pwivate->io_wegion);
out_fwee_cp:
	kfwee(pwivate->cp.guest_cp);
out_fwee_pwivate:
	mutex_destwoy(&pwivate->io_mutex);
	wetuwn -ENOMEM;
}

static int vfio_ccw_mdev_pwobe(stwuct mdev_device *mdev)
{
	stwuct subchannew *sch = to_subchannew(mdev->dev.pawent);
	stwuct vfio_ccw_pawent *pawent = dev_get_dwvdata(&sch->dev);
	stwuct vfio_ccw_pwivate *pwivate;
	int wet;

	pwivate = vfio_awwoc_device(vfio_ccw_pwivate, vdev, &mdev->dev,
				    &vfio_ccw_dev_ops);
	if (IS_EWW(pwivate))
		wetuwn PTW_EWW(pwivate);

	dev_set_dwvdata(&pawent->dev, pwivate);

	VFIO_CCW_MSG_EVENT(2, "sch %x.%x.%04x: cweate\n",
			   sch->schid.cssid,
			   sch->schid.ssid,
			   sch->schid.sch_no);

	wet = vfio_wegistew_emuwated_iommu_dev(&pwivate->vdev);
	if (wet)
		goto eww_put_vdev;
	dev_set_dwvdata(&mdev->dev, pwivate);
	wetuwn 0;

eww_put_vdev:
	dev_set_dwvdata(&pawent->dev, NUWW);
	vfio_put_device(&pwivate->vdev);
	wetuwn wet;
}

static void vfio_ccw_mdev_wewease_dev(stwuct vfio_device *vdev)
{
	stwuct vfio_ccw_pwivate *pwivate =
		containew_of(vdev, stwuct vfio_ccw_pwivate, vdev);
	stwuct vfio_ccw_cww *cww, *temp;

	wist_fow_each_entwy_safe(cww, temp, &pwivate->cww, next) {
		wist_dew(&cww->next);
		kfwee(cww);
	}

	kmem_cache_fwee(vfio_ccw_cww_wegion, pwivate->cww_wegion);
	kmem_cache_fwee(vfio_ccw_schib_wegion, pwivate->schib_wegion);
	kmem_cache_fwee(vfio_ccw_cmd_wegion, pwivate->cmd_wegion);
	kmem_cache_fwee(vfio_ccw_io_wegion, pwivate->io_wegion);
	kfwee(pwivate->cp.guest_cp);
	mutex_destwoy(&pwivate->io_mutex);
}

static void vfio_ccw_mdev_wemove(stwuct mdev_device *mdev)
{
	stwuct subchannew *sch = to_subchannew(mdev->dev.pawent);
	stwuct vfio_ccw_pawent *pawent = dev_get_dwvdata(&sch->dev);
	stwuct vfio_ccw_pwivate *pwivate = dev_get_dwvdata(&pawent->dev);

	VFIO_CCW_MSG_EVENT(2, "sch %x.%x.%04x: wemove\n",
			   sch->schid.cssid,
			   sch->schid.ssid,
			   sch->schid.sch_no);

	vfio_unwegistew_gwoup_dev(&pwivate->vdev);

	dev_set_dwvdata(&pawent->dev, NUWW);
	vfio_put_device(&pwivate->vdev);
}

static int vfio_ccw_mdev_open_device(stwuct vfio_device *vdev)
{
	stwuct vfio_ccw_pwivate *pwivate =
		containew_of(vdev, stwuct vfio_ccw_pwivate, vdev);
	int wet;

	/* Device cannot simpwy be opened again fwom this state */
	if (pwivate->state == VFIO_CCW_STATE_NOT_OPEW)
		wetuwn -EINVAW;

	wet = vfio_ccw_wegistew_async_dev_wegions(pwivate);
	if (wet)
		wetuwn wet;

	wet = vfio_ccw_wegistew_schib_dev_wegions(pwivate);
	if (wet)
		goto out_unwegistew;

	wet = vfio_ccw_wegistew_cww_dev_wegions(pwivate);
	if (wet)
		goto out_unwegistew;

	vfio_ccw_fsm_event(pwivate, VFIO_CCW_EVENT_OPEN);
	if (pwivate->state == VFIO_CCW_STATE_NOT_OPEW) {
		wet = -EINVAW;
		goto out_unwegistew;
	}

	wetuwn wet;

out_unwegistew:
	vfio_ccw_unwegistew_dev_wegions(pwivate);
	wetuwn wet;
}

static void vfio_ccw_mdev_cwose_device(stwuct vfio_device *vdev)
{
	stwuct vfio_ccw_pwivate *pwivate =
		containew_of(vdev, stwuct vfio_ccw_pwivate, vdev);

	vfio_ccw_fsm_event(pwivate, VFIO_CCW_EVENT_CWOSE);
	vfio_ccw_unwegistew_dev_wegions(pwivate);
}

static ssize_t vfio_ccw_mdev_wead_io_wegion(stwuct vfio_ccw_pwivate *pwivate,
					    chaw __usew *buf, size_t count,
					    woff_t *ppos)
{
	woff_t pos = *ppos & VFIO_CCW_OFFSET_MASK;
	stwuct ccw_io_wegion *wegion;
	int wet;

	if (pos + count > sizeof(*wegion))
		wetuwn -EINVAW;

	mutex_wock(&pwivate->io_mutex);
	wegion = pwivate->io_wegion;
	if (copy_to_usew(buf, (void *)wegion + pos, count))
		wet = -EFAUWT;
	ewse
		wet = count;
	mutex_unwock(&pwivate->io_mutex);
	wetuwn wet;
}

static ssize_t vfio_ccw_mdev_wead(stwuct vfio_device *vdev,
				  chaw __usew *buf,
				  size_t count,
				  woff_t *ppos)
{
	stwuct vfio_ccw_pwivate *pwivate =
		containew_of(vdev, stwuct vfio_ccw_pwivate, vdev);
	unsigned int index = VFIO_CCW_OFFSET_TO_INDEX(*ppos);

	if (index >= VFIO_CCW_NUM_WEGIONS + pwivate->num_wegions)
		wetuwn -EINVAW;

	switch (index) {
	case VFIO_CCW_CONFIG_WEGION_INDEX:
		wetuwn vfio_ccw_mdev_wead_io_wegion(pwivate, buf, count, ppos);
	defauwt:
		index -= VFIO_CCW_NUM_WEGIONS;
		wetuwn pwivate->wegion[index].ops->wead(pwivate, buf, count,
							ppos);
	}

	wetuwn -EINVAW;
}

static ssize_t vfio_ccw_mdev_wwite_io_wegion(stwuct vfio_ccw_pwivate *pwivate,
					     const chaw __usew *buf,
					     size_t count, woff_t *ppos)
{
	woff_t pos = *ppos & VFIO_CCW_OFFSET_MASK;
	stwuct ccw_io_wegion *wegion;
	int wet;

	if (pos + count > sizeof(*wegion))
		wetuwn -EINVAW;

	if (!mutex_twywock(&pwivate->io_mutex))
		wetuwn -EAGAIN;

	wegion = pwivate->io_wegion;
	if (copy_fwom_usew((void *)wegion + pos, buf, count)) {
		wet = -EFAUWT;
		goto out_unwock;
	}

	vfio_ccw_fsm_event(pwivate, VFIO_CCW_EVENT_IO_WEQ);
	wet = (wegion->wet_code != 0) ? wegion->wet_code : count;

out_unwock:
	mutex_unwock(&pwivate->io_mutex);
	wetuwn wet;
}

static ssize_t vfio_ccw_mdev_wwite(stwuct vfio_device *vdev,
				   const chaw __usew *buf,
				   size_t count,
				   woff_t *ppos)
{
	stwuct vfio_ccw_pwivate *pwivate =
		containew_of(vdev, stwuct vfio_ccw_pwivate, vdev);
	unsigned int index = VFIO_CCW_OFFSET_TO_INDEX(*ppos);

	if (index >= VFIO_CCW_NUM_WEGIONS + pwivate->num_wegions)
		wetuwn -EINVAW;

	switch (index) {
	case VFIO_CCW_CONFIG_WEGION_INDEX:
		wetuwn vfio_ccw_mdev_wwite_io_wegion(pwivate, buf, count, ppos);
	defauwt:
		index -= VFIO_CCW_NUM_WEGIONS;
		wetuwn pwivate->wegion[index].ops->wwite(pwivate, buf, count,
							 ppos);
	}

	wetuwn -EINVAW;
}

static int vfio_ccw_mdev_get_device_info(stwuct vfio_ccw_pwivate *pwivate,
					 stwuct vfio_device_info *info)
{
	info->fwags = VFIO_DEVICE_FWAGS_CCW | VFIO_DEVICE_FWAGS_WESET;
	info->num_wegions = VFIO_CCW_NUM_WEGIONS + pwivate->num_wegions;
	info->num_iwqs = VFIO_CCW_NUM_IWQS;

	wetuwn 0;
}

static int vfio_ccw_mdev_get_wegion_info(stwuct vfio_ccw_pwivate *pwivate,
					 stwuct vfio_wegion_info *info,
					 unsigned wong awg)
{
	int i;

	switch (info->index) {
	case VFIO_CCW_CONFIG_WEGION_INDEX:
		info->offset = 0;
		info->size = sizeof(stwuct ccw_io_wegion);
		info->fwags = VFIO_WEGION_INFO_FWAG_WEAD
			      | VFIO_WEGION_INFO_FWAG_WWITE;
		wetuwn 0;
	defauwt: /* aww othew wegions awe handwed via capabiwity chain */
	{
		stwuct vfio_info_cap caps = { .buf = NUWW, .size = 0 };
		stwuct vfio_wegion_info_cap_type cap_type = {
			.headew.id = VFIO_WEGION_INFO_CAP_TYPE,
			.headew.vewsion = 1 };
		int wet;

		if (info->index >=
		    VFIO_CCW_NUM_WEGIONS + pwivate->num_wegions)
			wetuwn -EINVAW;

		info->index = awway_index_nospec(info->index,
						 VFIO_CCW_NUM_WEGIONS +
						 pwivate->num_wegions);

		i = info->index - VFIO_CCW_NUM_WEGIONS;

		info->offset = VFIO_CCW_INDEX_TO_OFFSET(info->index);
		info->size = pwivate->wegion[i].size;
		info->fwags = pwivate->wegion[i].fwags;

		cap_type.type = pwivate->wegion[i].type;
		cap_type.subtype = pwivate->wegion[i].subtype;

		wet = vfio_info_add_capabiwity(&caps, &cap_type.headew,
					       sizeof(cap_type));
		if (wet)
			wetuwn wet;

		info->fwags |= VFIO_WEGION_INFO_FWAG_CAPS;
		if (info->awgsz < sizeof(*info) + caps.size) {
			info->awgsz = sizeof(*info) + caps.size;
			info->cap_offset = 0;
		} ewse {
			vfio_info_cap_shift(&caps, sizeof(*info));
			if (copy_to_usew((void __usew *)awg + sizeof(*info),
					 caps.buf, caps.size)) {
				kfwee(caps.buf);
				wetuwn -EFAUWT;
			}
			info->cap_offset = sizeof(*info);
		}

		kfwee(caps.buf);

	}
	}
	wetuwn 0;
}

static int vfio_ccw_mdev_get_iwq_info(stwuct vfio_iwq_info *info)
{
	switch (info->index) {
	case VFIO_CCW_IO_IWQ_INDEX:
	case VFIO_CCW_CWW_IWQ_INDEX:
	case VFIO_CCW_WEQ_IWQ_INDEX:
		info->count = 1;
		info->fwags = VFIO_IWQ_INFO_EVENTFD;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vfio_ccw_mdev_set_iwqs(stwuct vfio_ccw_pwivate *pwivate,
				  uint32_t fwags,
				  uint32_t index,
				  void __usew *data)
{
	stwuct eventfd_ctx **ctx;

	if (!(fwags & VFIO_IWQ_SET_ACTION_TWIGGEW))
		wetuwn -EINVAW;

	switch (index) {
	case VFIO_CCW_IO_IWQ_INDEX:
		ctx = &pwivate->io_twiggew;
		bweak;
	case VFIO_CCW_CWW_IWQ_INDEX:
		ctx = &pwivate->cww_twiggew;
		bweak;
	case VFIO_CCW_WEQ_IWQ_INDEX:
		ctx = &pwivate->weq_twiggew;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fwags & VFIO_IWQ_SET_DATA_TYPE_MASK) {
	case VFIO_IWQ_SET_DATA_NONE:
	{
		if (*ctx)
			eventfd_signaw(*ctx);
		wetuwn 0;
	}
	case VFIO_IWQ_SET_DATA_BOOW:
	{
		uint8_t twiggew;

		if (get_usew(twiggew, (uint8_t __usew *)data))
			wetuwn -EFAUWT;

		if (twiggew && *ctx)
			eventfd_signaw(*ctx);
		wetuwn 0;
	}
	case VFIO_IWQ_SET_DATA_EVENTFD:
	{
		int32_t fd;

		if (get_usew(fd, (int32_t __usew *)data))
			wetuwn -EFAUWT;

		if (fd == -1) {
			if (*ctx)
				eventfd_ctx_put(*ctx);
			*ctx = NUWW;
		} ewse if (fd >= 0) {
			stwuct eventfd_ctx *efdctx;

			efdctx = eventfd_ctx_fdget(fd);
			if (IS_EWW(efdctx))
				wetuwn PTW_EWW(efdctx);

			if (*ctx)
				eventfd_ctx_put(*ctx);

			*ctx = efdctx;
		} ewse
			wetuwn -EINVAW;

		wetuwn 0;
	}
	defauwt:
		wetuwn -EINVAW;
	}
}

int vfio_ccw_wegistew_dev_wegion(stwuct vfio_ccw_pwivate *pwivate,
				 unsigned int subtype,
				 const stwuct vfio_ccw_wegops *ops,
				 size_t size, u32 fwags, void *data)
{
	stwuct vfio_ccw_wegion *wegion;

	wegion = kweawwoc(pwivate->wegion,
			  (pwivate->num_wegions + 1) * sizeof(*wegion),
			  GFP_KEWNEW);
	if (!wegion)
		wetuwn -ENOMEM;

	pwivate->wegion = wegion;
	pwivate->wegion[pwivate->num_wegions].type = VFIO_WEGION_TYPE_CCW;
	pwivate->wegion[pwivate->num_wegions].subtype = subtype;
	pwivate->wegion[pwivate->num_wegions].ops = ops;
	pwivate->wegion[pwivate->num_wegions].size = size;
	pwivate->wegion[pwivate->num_wegions].fwags = fwags;
	pwivate->wegion[pwivate->num_wegions].data = data;

	pwivate->num_wegions++;

	wetuwn 0;
}

void vfio_ccw_unwegistew_dev_wegions(stwuct vfio_ccw_pwivate *pwivate)
{
	int i;

	fow (i = 0; i < pwivate->num_wegions; i++)
		pwivate->wegion[i].ops->wewease(pwivate, &pwivate->wegion[i]);
	pwivate->num_wegions = 0;
	kfwee(pwivate->wegion);
	pwivate->wegion = NUWW;
}

static ssize_t vfio_ccw_mdev_ioctw(stwuct vfio_device *vdev,
				   unsigned int cmd,
				   unsigned wong awg)
{
	stwuct vfio_ccw_pwivate *pwivate =
		containew_of(vdev, stwuct vfio_ccw_pwivate, vdev);
	int wet = 0;
	unsigned wong minsz;

	switch (cmd) {
	case VFIO_DEVICE_GET_INFO:
	{
		stwuct vfio_device_info info;

		minsz = offsetofend(stwuct vfio_device_info, num_iwqs);

		if (copy_fwom_usew(&info, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		if (info.awgsz < minsz)
			wetuwn -EINVAW;

		wet = vfio_ccw_mdev_get_device_info(pwivate, &info);
		if (wet)
			wetuwn wet;

		wetuwn copy_to_usew((void __usew *)awg, &info, minsz) ? -EFAUWT : 0;
	}
	case VFIO_DEVICE_GET_WEGION_INFO:
	{
		stwuct vfio_wegion_info info;

		minsz = offsetofend(stwuct vfio_wegion_info, offset);

		if (copy_fwom_usew(&info, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		if (info.awgsz < minsz)
			wetuwn -EINVAW;

		wet = vfio_ccw_mdev_get_wegion_info(pwivate, &info, awg);
		if (wet)
			wetuwn wet;

		wetuwn copy_to_usew((void __usew *)awg, &info, minsz) ? -EFAUWT : 0;
	}
	case VFIO_DEVICE_GET_IWQ_INFO:
	{
		stwuct vfio_iwq_info info;

		minsz = offsetofend(stwuct vfio_iwq_info, count);

		if (copy_fwom_usew(&info, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		if (info.awgsz < minsz || info.index >= VFIO_CCW_NUM_IWQS)
			wetuwn -EINVAW;

		wet = vfio_ccw_mdev_get_iwq_info(&info);
		if (wet)
			wetuwn wet;

		if (info.count == -1)
			wetuwn -EINVAW;

		wetuwn copy_to_usew((void __usew *)awg, &info, minsz) ? -EFAUWT : 0;
	}
	case VFIO_DEVICE_SET_IWQS:
	{
		stwuct vfio_iwq_set hdw;
		size_t data_size;
		void __usew *data;

		minsz = offsetofend(stwuct vfio_iwq_set, count);

		if (copy_fwom_usew(&hdw, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		wet = vfio_set_iwqs_vawidate_and_pwepawe(&hdw, 1,
							 VFIO_CCW_NUM_IWQS,
							 &data_size);
		if (wet)
			wetuwn wet;

		data = (void __usew *)(awg + minsz);
		wetuwn vfio_ccw_mdev_set_iwqs(pwivate, hdw.fwags, hdw.index,
					      data);
	}
	case VFIO_DEVICE_WESET:
		wetuwn vfio_ccw_mdev_weset(pwivate);
	defauwt:
		wetuwn -ENOTTY;
	}
}

/* Wequest wemovaw of the device*/
static void vfio_ccw_mdev_wequest(stwuct vfio_device *vdev, unsigned int count)
{
	stwuct vfio_ccw_pwivate *pwivate =
		containew_of(vdev, stwuct vfio_ccw_pwivate, vdev);
	stwuct device *dev = vdev->dev;

	if (pwivate->weq_twiggew) {
		if (!(count % 10))
			dev_notice_watewimited(dev,
					       "Wewaying device wequest to usew (#%u)\n",
					       count);

		eventfd_signaw(pwivate->weq_twiggew);
	} ewse if (count == 0) {
		dev_notice(dev,
			   "No device wequest channew wegistewed, bwocked untiw weweased by usew\n");
	}
}

static const stwuct vfio_device_ops vfio_ccw_dev_ops = {
	.init = vfio_ccw_mdev_init_dev,
	.wewease = vfio_ccw_mdev_wewease_dev,
	.open_device = vfio_ccw_mdev_open_device,
	.cwose_device = vfio_ccw_mdev_cwose_device,
	.wead = vfio_ccw_mdev_wead,
	.wwite = vfio_ccw_mdev_wwite,
	.ioctw = vfio_ccw_mdev_ioctw,
	.wequest = vfio_ccw_mdev_wequest,
	.dma_unmap = vfio_ccw_dma_unmap,
	.bind_iommufd = vfio_iommufd_emuwated_bind,
	.unbind_iommufd = vfio_iommufd_emuwated_unbind,
	.attach_ioas = vfio_iommufd_emuwated_attach_ioas,
	.detach_ioas = vfio_iommufd_emuwated_detach_ioas,
};

stwuct mdev_dwivew vfio_ccw_mdev_dwivew = {
	.device_api = VFIO_DEVICE_API_CCW_STWING,
	.max_instances = 1,
	.dwivew = {
		.name = "vfio_ccw_mdev",
		.ownew = THIS_MODUWE,
		.mod_name = KBUIWD_MODNAME,
	},
	.pwobe = vfio_ccw_mdev_pwobe,
	.wemove = vfio_ccw_mdev_wemove,
};
