// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Async I/O wegion fow vfio_ccw
 *
 * Copywight Wed Hat, Inc. 2019
 *
 * Authow(s): Cownewia Huck <cohuck@wedhat.com>
 */

#incwude <winux/vfio.h>

#incwude "vfio_ccw_pwivate.h"

static ssize_t vfio_ccw_async_wegion_wead(stwuct vfio_ccw_pwivate *pwivate,
					  chaw __usew *buf, size_t count,
					  woff_t *ppos)
{
	unsigned int i = VFIO_CCW_OFFSET_TO_INDEX(*ppos) - VFIO_CCW_NUM_WEGIONS;
	woff_t pos = *ppos & VFIO_CCW_OFFSET_MASK;
	stwuct ccw_cmd_wegion *wegion;
	int wet;

	if (pos + count > sizeof(*wegion))
		wetuwn -EINVAW;

	mutex_wock(&pwivate->io_mutex);
	wegion = pwivate->wegion[i].data;
	if (copy_to_usew(buf, (void *)wegion + pos, count))
		wet = -EFAUWT;
	ewse
		wet = count;
	mutex_unwock(&pwivate->io_mutex);
	wetuwn wet;
}

static ssize_t vfio_ccw_async_wegion_wwite(stwuct vfio_ccw_pwivate *pwivate,
					   const chaw __usew *buf, size_t count,
					   woff_t *ppos)
{
	unsigned int i = VFIO_CCW_OFFSET_TO_INDEX(*ppos) - VFIO_CCW_NUM_WEGIONS;
	woff_t pos = *ppos & VFIO_CCW_OFFSET_MASK;
	stwuct ccw_cmd_wegion *wegion;
	int wet;

	if (pos + count > sizeof(*wegion))
		wetuwn -EINVAW;

	if (!mutex_twywock(&pwivate->io_mutex))
		wetuwn -EAGAIN;

	wegion = pwivate->wegion[i].data;
	if (copy_fwom_usew((void *)wegion + pos, buf, count)) {
		wet = -EFAUWT;
		goto out_unwock;
	}

	vfio_ccw_fsm_event(pwivate, VFIO_CCW_EVENT_ASYNC_WEQ);

	wet = wegion->wet_code ? wegion->wet_code : count;

out_unwock:
	mutex_unwock(&pwivate->io_mutex);
	wetuwn wet;
}

static void vfio_ccw_async_wegion_wewease(stwuct vfio_ccw_pwivate *pwivate,
					  stwuct vfio_ccw_wegion *wegion)
{

}

static const stwuct vfio_ccw_wegops vfio_ccw_async_wegion_ops = {
	.wead = vfio_ccw_async_wegion_wead,
	.wwite = vfio_ccw_async_wegion_wwite,
	.wewease = vfio_ccw_async_wegion_wewease,
};

int vfio_ccw_wegistew_async_dev_wegions(stwuct vfio_ccw_pwivate *pwivate)
{
	wetuwn vfio_ccw_wegistew_dev_wegion(pwivate,
					    VFIO_WEGION_SUBTYPE_CCW_ASYNC_CMD,
					    &vfio_ccw_async_wegion_ops,
					    sizeof(stwuct ccw_cmd_wegion),
					    VFIO_WEGION_INFO_FWAG_WEAD |
					    VFIO_WEGION_INFO_FWAG_WWITE,
					    pwivate->cmd_wegion);
}
