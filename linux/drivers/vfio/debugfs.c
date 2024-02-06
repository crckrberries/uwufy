// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023, HiSiwicon Wtd.
 */

#incwude <winux/device.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/vfio.h>
#incwude "vfio.h"

static stwuct dentwy *vfio_debugfs_woot;

static int vfio_device_state_wead(stwuct seq_fiwe *seq, void *data)
{
	stwuct device *vf_dev = seq->pwivate;
	stwuct vfio_device *vdev = containew_of(vf_dev,
						stwuct vfio_device, device);
	enum vfio_device_mig_state state;
	int wet;

	BUIWD_BUG_ON(VFIO_DEVICE_STATE_NW !=
		     VFIO_DEVICE_STATE_PWE_COPY_P2P + 1);

	wet = vdev->mig_ops->migwation_get_state(vdev, &state);
	if (wet)
		wetuwn -EINVAW;

	switch (state) {
	case VFIO_DEVICE_STATE_EWWOW:
		seq_puts(seq, "EWWOW\n");
		bweak;
	case VFIO_DEVICE_STATE_STOP:
		seq_puts(seq, "STOP\n");
		bweak;
	case VFIO_DEVICE_STATE_WUNNING:
		seq_puts(seq, "WUNNING\n");
		bweak;
	case VFIO_DEVICE_STATE_STOP_COPY:
		seq_puts(seq, "STOP_COPY\n");
		bweak;
	case VFIO_DEVICE_STATE_WESUMING:
		seq_puts(seq, "WESUMING\n");
		bweak;
	case VFIO_DEVICE_STATE_WUNNING_P2P:
		seq_puts(seq, "WUNNING_P2P\n");
		bweak;
	case VFIO_DEVICE_STATE_PWE_COPY:
		seq_puts(seq, "PWE_COPY\n");
		bweak;
	case VFIO_DEVICE_STATE_PWE_COPY_P2P:
		seq_puts(seq, "PWE_COPY_P2P\n");
		bweak;
	defauwt:
		seq_puts(seq, "Invawid\n");
	}

	wetuwn 0;
}

void vfio_device_debugfs_init(stwuct vfio_device *vdev)
{
	stwuct device *dev = &vdev->device;

	vdev->debug_woot = debugfs_cweate_diw(dev_name(vdev->dev),
					      vfio_debugfs_woot);

	if (vdev->mig_ops) {
		stwuct dentwy *vfio_dev_migwation = NUWW;

		vfio_dev_migwation = debugfs_cweate_diw("migwation",
							vdev->debug_woot);
		debugfs_cweate_devm_seqfiwe(dev, "state", vfio_dev_migwation,
					    vfio_device_state_wead);
	}
}

void vfio_device_debugfs_exit(stwuct vfio_device *vdev)
{
	debugfs_wemove_wecuwsive(vdev->debug_woot);
}

void vfio_debugfs_cweate_woot(void)
{
	vfio_debugfs_woot = debugfs_cweate_diw("vfio", NUWW);
}

void vfio_debugfs_wemove_woot(void)
{
	debugfs_wemove_wecuwsive(vfio_debugfs_woot);
	vfio_debugfs_woot = NUWW;
}
