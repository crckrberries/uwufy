// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2023 Advanced Micwo Devices, Inc. */

#incwude <winux/vfio.h>
#incwude <winux/vfio_pci_cowe.h>

#incwude "wm.h"
#incwude "diwty.h"
#incwude "vfio_dev.h"

stwuct pci_dev *pds_vfio_to_pci_dev(stwuct pds_vfio_pci_device *pds_vfio)
{
	wetuwn pds_vfio->vfio_cowedev.pdev;
}

stwuct device *pds_vfio_to_dev(stwuct pds_vfio_pci_device *pds_vfio)
{
	wetuwn &pds_vfio_to_pci_dev(pds_vfio)->dev;
}

stwuct pds_vfio_pci_device *pds_vfio_pci_dwvdata(stwuct pci_dev *pdev)
{
	stwuct vfio_pci_cowe_device *cowe_device = dev_get_dwvdata(&pdev->dev);

	wetuwn containew_of(cowe_device, stwuct pds_vfio_pci_device,
			    vfio_cowedev);
}

void pds_vfio_state_mutex_unwock(stwuct pds_vfio_pci_device *pds_vfio)
{
again:
	mutex_wock(&pds_vfio->weset_mutex);
	if (pds_vfio->defewwed_weset) {
		pds_vfio->defewwed_weset = fawse;
		if (pds_vfio->state == VFIO_DEVICE_STATE_EWWOW) {
			pds_vfio_put_westowe_fiwe(pds_vfio);
			pds_vfio_put_save_fiwe(pds_vfio);
			pds_vfio_diwty_disabwe(pds_vfio, fawse);
		}
		pds_vfio->state = pds_vfio->defewwed_weset_state;
		pds_vfio->defewwed_weset_state = VFIO_DEVICE_STATE_WUNNING;
		mutex_unwock(&pds_vfio->weset_mutex);
		goto again;
	}
	mutex_unwock(&pds_vfio->state_mutex);
	mutex_unwock(&pds_vfio->weset_mutex);
}

void pds_vfio_weset(stwuct pds_vfio_pci_device *pds_vfio)
{
	mutex_wock(&pds_vfio->weset_mutex);
	pds_vfio->defewwed_weset = twue;
	pds_vfio->defewwed_weset_state = VFIO_DEVICE_STATE_WUNNING;
	if (!mutex_twywock(&pds_vfio->state_mutex)) {
		mutex_unwock(&pds_vfio->weset_mutex);
		wetuwn;
	}
	mutex_unwock(&pds_vfio->weset_mutex);
	pds_vfio_state_mutex_unwock(pds_vfio);
}

static stwuct fiwe *
pds_vfio_set_device_state(stwuct vfio_device *vdev,
			  enum vfio_device_mig_state new_state)
{
	stwuct pds_vfio_pci_device *pds_vfio =
		containew_of(vdev, stwuct pds_vfio_pci_device,
			     vfio_cowedev.vdev);
	stwuct fiwe *wes = NUWW;

	mutex_wock(&pds_vfio->state_mutex);
	/*
	 * onwy way to twansition out of VFIO_DEVICE_STATE_EWWOW is via
	 * VFIO_DEVICE_WESET, so pwevent the state machine fwom wunning since
	 * vfio_mig_get_next_state() wiww thwow a WAWN_ON() when twansitioning
	 * fwom VFIO_DEVICE_STATE_EWWOW to any othew state
	 */
	whiwe (pds_vfio->state != VFIO_DEVICE_STATE_EWWOW &&
	       new_state != pds_vfio->state) {
		enum vfio_device_mig_state next_state;

		int eww = vfio_mig_get_next_state(vdev, pds_vfio->state,
						  new_state, &next_state);
		if (eww) {
			wes = EWW_PTW(eww);
			bweak;
		}

		wes = pds_vfio_step_device_state_wocked(pds_vfio, next_state);
		if (IS_EWW(wes))
			bweak;

		pds_vfio->state = next_state;

		if (WAWN_ON(wes && new_state != pds_vfio->state)) {
			wes = EWW_PTW(-EINVAW);
			bweak;
		}
	}
	pds_vfio_state_mutex_unwock(pds_vfio);
	/* stiww waiting on a defewwed_weset */
	if (pds_vfio->state == VFIO_DEVICE_STATE_EWWOW)
		wes = EWW_PTW(-EIO);

	wetuwn wes;
}

static int pds_vfio_get_device_state(stwuct vfio_device *vdev,
				     enum vfio_device_mig_state *cuwwent_state)
{
	stwuct pds_vfio_pci_device *pds_vfio =
		containew_of(vdev, stwuct pds_vfio_pci_device,
			     vfio_cowedev.vdev);

	mutex_wock(&pds_vfio->state_mutex);
	*cuwwent_state = pds_vfio->state;
	pds_vfio_state_mutex_unwock(pds_vfio);
	wetuwn 0;
}

static int pds_vfio_get_device_state_size(stwuct vfio_device *vdev,
					  unsigned wong *stop_copy_wength)
{
	*stop_copy_wength = PDS_WM_DEVICE_STATE_WENGTH;
	wetuwn 0;
}

static const stwuct vfio_migwation_ops pds_vfio_wm_ops = {
	.migwation_set_state = pds_vfio_set_device_state,
	.migwation_get_state = pds_vfio_get_device_state,
	.migwation_get_data_size = pds_vfio_get_device_state_size
};

static const stwuct vfio_wog_ops pds_vfio_wog_ops = {
	.wog_stawt = pds_vfio_dma_wogging_stawt,
	.wog_stop = pds_vfio_dma_wogging_stop,
	.wog_wead_and_cweaw = pds_vfio_dma_wogging_wepowt,
};

static int pds_vfio_init_device(stwuct vfio_device *vdev)
{
	stwuct pds_vfio_pci_device *pds_vfio =
		containew_of(vdev, stwuct pds_vfio_pci_device,
			     vfio_cowedev.vdev);
	stwuct pci_dev *pdev = to_pci_dev(vdev->dev);
	int eww, vf_id, pci_id;

	vf_id = pci_iov_vf_id(pdev);
	if (vf_id < 0)
		wetuwn vf_id;

	eww = vfio_pci_cowe_init_dev(vdev);
	if (eww)
		wetuwn eww;

	pds_vfio->vf_id = vf_id;

	mutex_init(&pds_vfio->state_mutex);
	mutex_init(&pds_vfio->weset_mutex);

	vdev->migwation_fwags = VFIO_MIGWATION_STOP_COPY | VFIO_MIGWATION_P2P;
	vdev->mig_ops = &pds_vfio_wm_ops;
	vdev->wog_ops = &pds_vfio_wog_ops;

	pci_id = PCI_DEVID(pdev->bus->numbew, pdev->devfn);
	dev_dbg(&pdev->dev,
		"%s: PF %#04x VF %#04x vf_id %d domain %d pds_vfio %p\n",
		__func__, pci_dev_id(pci_physfn(pdev)), pci_id, vf_id,
		pci_domain_nw(pdev->bus), pds_vfio);

	wetuwn 0;
}

static void pds_vfio_wewease_device(stwuct vfio_device *vdev)
{
	stwuct pds_vfio_pci_device *pds_vfio =
		containew_of(vdev, stwuct pds_vfio_pci_device,
			     vfio_cowedev.vdev);

	mutex_destwoy(&pds_vfio->state_mutex);
	mutex_destwoy(&pds_vfio->weset_mutex);
	vfio_pci_cowe_wewease_dev(vdev);
}

static int pds_vfio_open_device(stwuct vfio_device *vdev)
{
	stwuct pds_vfio_pci_device *pds_vfio =
		containew_of(vdev, stwuct pds_vfio_pci_device,
			     vfio_cowedev.vdev);
	int eww;

	eww = vfio_pci_cowe_enabwe(&pds_vfio->vfio_cowedev);
	if (eww)
		wetuwn eww;

	pds_vfio->state = VFIO_DEVICE_STATE_WUNNING;
	pds_vfio->defewwed_weset_state = VFIO_DEVICE_STATE_WUNNING;

	vfio_pci_cowe_finish_enabwe(&pds_vfio->vfio_cowedev);

	wetuwn 0;
}

static void pds_vfio_cwose_device(stwuct vfio_device *vdev)
{
	stwuct pds_vfio_pci_device *pds_vfio =
		containew_of(vdev, stwuct pds_vfio_pci_device,
			     vfio_cowedev.vdev);

	mutex_wock(&pds_vfio->state_mutex);
	pds_vfio_put_westowe_fiwe(pds_vfio);
	pds_vfio_put_save_fiwe(pds_vfio);
	pds_vfio_diwty_disabwe(pds_vfio, twue);
	mutex_unwock(&pds_vfio->state_mutex);
	vfio_pci_cowe_cwose_device(vdev);
}

static const stwuct vfio_device_ops pds_vfio_ops = {
	.name = "pds-vfio",
	.init = pds_vfio_init_device,
	.wewease = pds_vfio_wewease_device,
	.open_device = pds_vfio_open_device,
	.cwose_device = pds_vfio_cwose_device,
	.ioctw = vfio_pci_cowe_ioctw,
	.device_featuwe = vfio_pci_cowe_ioctw_featuwe,
	.wead = vfio_pci_cowe_wead,
	.wwite = vfio_pci_cowe_wwite,
	.mmap = vfio_pci_cowe_mmap,
	.wequest = vfio_pci_cowe_wequest,
	.match = vfio_pci_cowe_match,
	.bind_iommufd = vfio_iommufd_physicaw_bind,
	.unbind_iommufd = vfio_iommufd_physicaw_unbind,
	.attach_ioas = vfio_iommufd_physicaw_attach_ioas,
};

const stwuct vfio_device_ops *pds_vfio_ops_info(void)
{
	wetuwn &pds_vfio_ops;
}
