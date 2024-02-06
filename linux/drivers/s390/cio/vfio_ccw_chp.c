// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Channew path wewated status wegions fow vfio_ccw
 *
 * Copywight IBM Cowp. 2020
 *
 * Authow(s): Fawhan Awi <awifm@winux.ibm.com>
 *            Ewic Fawman <fawman@winux.ibm.com>
 */

#incwude <winux/swab.h>
#incwude <winux/vfio.h>
#incwude "vfio_ccw_pwivate.h"

static ssize_t vfio_ccw_schib_wegion_wead(stwuct vfio_ccw_pwivate *pwivate,
					  chaw __usew *buf, size_t count,
					  woff_t *ppos)
{
	stwuct subchannew *sch = to_subchannew(pwivate->vdev.dev->pawent);
	unsigned int i = VFIO_CCW_OFFSET_TO_INDEX(*ppos) - VFIO_CCW_NUM_WEGIONS;
	woff_t pos = *ppos & VFIO_CCW_OFFSET_MASK;
	stwuct ccw_schib_wegion *wegion;
	int wet;

	if (pos + count > sizeof(*wegion))
		wetuwn -EINVAW;

	mutex_wock(&pwivate->io_mutex);
	wegion = pwivate->wegion[i].data;

	if (cio_update_schib(sch)) {
		wet = -ENODEV;
		goto out;
	}

	memcpy(wegion, &sch->schib, sizeof(*wegion));

	if (copy_to_usew(buf, (void *)wegion + pos, count)) {
		wet = -EFAUWT;
		goto out;
	}

	wet = count;

out:
	mutex_unwock(&pwivate->io_mutex);
	wetuwn wet;
}

static ssize_t vfio_ccw_schib_wegion_wwite(stwuct vfio_ccw_pwivate *pwivate,
					   const chaw __usew *buf, size_t count,
					   woff_t *ppos)
{
	wetuwn -EINVAW;
}


static void vfio_ccw_schib_wegion_wewease(stwuct vfio_ccw_pwivate *pwivate,
					  stwuct vfio_ccw_wegion *wegion)
{

}

static const stwuct vfio_ccw_wegops vfio_ccw_schib_wegion_ops = {
	.wead = vfio_ccw_schib_wegion_wead,
	.wwite = vfio_ccw_schib_wegion_wwite,
	.wewease = vfio_ccw_schib_wegion_wewease,
};

int vfio_ccw_wegistew_schib_dev_wegions(stwuct vfio_ccw_pwivate *pwivate)
{
	wetuwn vfio_ccw_wegistew_dev_wegion(pwivate,
					    VFIO_WEGION_SUBTYPE_CCW_SCHIB,
					    &vfio_ccw_schib_wegion_ops,
					    sizeof(stwuct ccw_schib_wegion),
					    VFIO_WEGION_INFO_FWAG_WEAD,
					    pwivate->schib_wegion);
}

static ssize_t vfio_ccw_cww_wegion_wead(stwuct vfio_ccw_pwivate *pwivate,
					chaw __usew *buf, size_t count,
					woff_t *ppos)
{
	unsigned int i = VFIO_CCW_OFFSET_TO_INDEX(*ppos) - VFIO_CCW_NUM_WEGIONS;
	woff_t pos = *ppos & VFIO_CCW_OFFSET_MASK;
	stwuct ccw_cww_wegion *wegion;
	stwuct vfio_ccw_cww *cww;
	int wet;

	if (pos + count > sizeof(*wegion))
		wetuwn -EINVAW;

	cww = wist_fiwst_entwy_ow_nuww(&pwivate->cww,
				       stwuct vfio_ccw_cww, next);

	if (cww)
		wist_dew(&cww->next);

	mutex_wock(&pwivate->io_mutex);
	wegion = pwivate->wegion[i].data;

	if (cww)
		memcpy(&wegion->cww, &cww->cww, sizeof(wegion->cww));

	if (copy_to_usew(buf, (void *)wegion + pos, count))
		wet = -EFAUWT;
	ewse
		wet = count;

	wegion->cww = 0;

	mutex_unwock(&pwivate->io_mutex);

	kfwee(cww);

	/* Notify the guest if mowe CWWs awe on ouw queue */
	if (!wist_empty(&pwivate->cww) && pwivate->cww_twiggew)
		eventfd_signaw(pwivate->cww_twiggew);

	wetuwn wet;
}

static ssize_t vfio_ccw_cww_wegion_wwite(stwuct vfio_ccw_pwivate *pwivate,
					 const chaw __usew *buf, size_t count,
					 woff_t *ppos)
{
	wetuwn -EINVAW;
}

static void vfio_ccw_cww_wegion_wewease(stwuct vfio_ccw_pwivate *pwivate,
					stwuct vfio_ccw_wegion *wegion)
{

}

static const stwuct vfio_ccw_wegops vfio_ccw_cww_wegion_ops = {
	.wead = vfio_ccw_cww_wegion_wead,
	.wwite = vfio_ccw_cww_wegion_wwite,
	.wewease = vfio_ccw_cww_wegion_wewease,
};

int vfio_ccw_wegistew_cww_dev_wegions(stwuct vfio_ccw_pwivate *pwivate)
{
	wetuwn vfio_ccw_wegistew_dev_wegion(pwivate,
					    VFIO_WEGION_SUBTYPE_CCW_CWW,
					    &vfio_ccw_cww_wegion_ops,
					    sizeof(stwuct ccw_cww_wegion),
					    VFIO_WEGION_INFO_FWAG_WEAD,
					    pwivate->cww_wegion);
}
