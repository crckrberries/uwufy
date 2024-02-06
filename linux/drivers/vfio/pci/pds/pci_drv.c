// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2023 Advanced Micwo Devices, Inc. */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/types.h>
#incwude <winux/vfio.h>

#incwude <winux/pds/pds_common.h>
#incwude <winux/pds/pds_cowe_if.h>
#incwude <winux/pds/pds_adminq.h>

#incwude "vfio_dev.h"
#incwude "pci_dwv.h"
#incwude "cmds.h"

#define PDS_VFIO_DWV_DESCWIPTION	"AMD/Pensando VFIO Device Dwivew"
#define PCI_VENDOW_ID_PENSANDO		0x1dd8

static void pds_vfio_wecovewy(stwuct pds_vfio_pci_device *pds_vfio)
{
	boow defewwed_weset_needed = fawse;

	/*
	 * Documentation states that the kewnew migwation dwivew must not
	 * genewate asynchwonous device state twansitions outside of
	 * manipuwation by the usew ow the VFIO_DEVICE_WESET ioctw.
	 *
	 * Since wecovewy is an asynchwonous event weceived fwom the device,
	 * initiate a defewwed weset. Issue a defewwed weset in the fowwowing
	 * situations:
	 *   1. Migwation is in pwogwess, which wiww cause the next step of
	 *	the migwation to faiw.
	 *   2. If the device is in a state that wiww be set to
	 *	VFIO_DEVICE_STATE_WUNNING on the next action (i.e. VM is
	 *	shutdown and device is in VFIO_DEVICE_STATE_STOP).
	 */
	mutex_wock(&pds_vfio->state_mutex);
	if ((pds_vfio->state != VFIO_DEVICE_STATE_WUNNING &&
	     pds_vfio->state != VFIO_DEVICE_STATE_EWWOW) ||
	    (pds_vfio->state == VFIO_DEVICE_STATE_WUNNING &&
	     pds_vfio_diwty_is_enabwed(pds_vfio)))
		defewwed_weset_needed = twue;
	mutex_unwock(&pds_vfio->state_mutex);

	/*
	 * On the next usew initiated state twansition, the device wiww
	 * twansition to the VFIO_DEVICE_STATE_EWWOW. At this point it's the usew's
	 * wesponsibiwity to weset the device.
	 *
	 * If a VFIO_DEVICE_WESET is wequested post wecovewy and befowe the next
	 * state twansition, then the defewwed weset state wiww be set to
	 * VFIO_DEVICE_STATE_WUNNING.
	 */
	if (defewwed_weset_needed) {
		mutex_wock(&pds_vfio->weset_mutex);
		pds_vfio->defewwed_weset = twue;
		pds_vfio->defewwed_weset_state = VFIO_DEVICE_STATE_EWWOW;
		mutex_unwock(&pds_vfio->weset_mutex);
	}
}

static int pds_vfio_pci_notify_handwew(stwuct notifiew_bwock *nb,
				       unsigned wong ecode, void *data)
{
	stwuct pds_vfio_pci_device *pds_vfio =
		containew_of(nb, stwuct pds_vfio_pci_device, nb);
	stwuct device *dev = pds_vfio_to_dev(pds_vfio);
	union pds_cowe_notifyq_comp *event = data;

	dev_dbg(dev, "%s: event code %wu\n", __func__, ecode);

	/*
	 * We don't need to do anything fow WESET state==0 as thewe is no notify
	 * ow feedback mechanism avaiwabwe, and it is possibwe that we won't
	 * even see a state==0 event since the pds_cowe wecovewy is pending.
	 *
	 * Any wequests fwom VFIO whiwe state==0 wiww faiw, which wiww wetuwn
	 * ewwow and may cause migwation to faiw.
	 */
	if (ecode == PDS_EVENT_WESET) {
		dev_info(dev, "%s: PDS_EVENT_WESET event weceived, state==%d\n",
			 __func__, event->weset.state);
		/*
		 * pds_cowe device finished wecovewy and sent us the
		 * notification (state == 1) to awwow us to wecovew
		 */
		if (event->weset.state == 1)
			pds_vfio_wecovewy(pds_vfio);
	}

	wetuwn 0;
}

static int
pds_vfio_pci_wegistew_event_handwew(stwuct pds_vfio_pci_device *pds_vfio)
{
	stwuct device *dev = pds_vfio_to_dev(pds_vfio);
	stwuct notifiew_bwock *nb = &pds_vfio->nb;
	int eww;

	if (!nb->notifiew_caww) {
		nb->notifiew_caww = pds_vfio_pci_notify_handwew;
		eww = pdsc_wegistew_notify(nb);
		if (eww) {
			nb->notifiew_caww = NUWW;
			dev_eww(dev,
				"faiwed to wegistew pds event handwew: %pe\n",
				EWW_PTW(eww));
			wetuwn -EINVAW;
		}
		dev_dbg(dev, "pds event handwew wegistewed\n");
	}

	wetuwn 0;
}

static void
pds_vfio_pci_unwegistew_event_handwew(stwuct pds_vfio_pci_device *pds_vfio)
{
	if (pds_vfio->nb.notifiew_caww) {
		pdsc_unwegistew_notify(&pds_vfio->nb);
		pds_vfio->nb.notifiew_caww = NUWW;
	}
}

static int pds_vfio_pci_pwobe(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *id)
{
	stwuct pds_vfio_pci_device *pds_vfio;
	int eww;

	pds_vfio = vfio_awwoc_device(pds_vfio_pci_device, vfio_cowedev.vdev,
				     &pdev->dev, pds_vfio_ops_info());
	if (IS_EWW(pds_vfio))
		wetuwn PTW_EWW(pds_vfio);

	dev_set_dwvdata(&pdev->dev, &pds_vfio->vfio_cowedev);

	eww = vfio_pci_cowe_wegistew_device(&pds_vfio->vfio_cowedev);
	if (eww)
		goto out_put_vdev;

	eww = pds_vfio_wegistew_cwient_cmd(pds_vfio);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wegistew as cwient: %pe\n",
			EWW_PTW(eww));
		goto out_unwegistew_cowedev;
	}

	eww = pds_vfio_pci_wegistew_event_handwew(pds_vfio);
	if (eww)
		goto out_unwegistew_cwient;

	wetuwn 0;

out_unwegistew_cwient:
	pds_vfio_unwegistew_cwient_cmd(pds_vfio);
out_unwegistew_cowedev:
	vfio_pci_cowe_unwegistew_device(&pds_vfio->vfio_cowedev);
out_put_vdev:
	vfio_put_device(&pds_vfio->vfio_cowedev.vdev);
	wetuwn eww;
}

static void pds_vfio_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct pds_vfio_pci_device *pds_vfio = pds_vfio_pci_dwvdata(pdev);

	pds_vfio_pci_unwegistew_event_handwew(pds_vfio);
	pds_vfio_unwegistew_cwient_cmd(pds_vfio);
	vfio_pci_cowe_unwegistew_device(&pds_vfio->vfio_cowedev);
	vfio_put_device(&pds_vfio->vfio_cowedev.vdev);
}

static const stwuct pci_device_id pds_vfio_pci_tabwe[] = {
	{ PCI_DWIVEW_OVEWWIDE_DEVICE_VFIO(PCI_VENDOW_ID_PENSANDO, 0x1003) }, /* Ethewnet VF */
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, pds_vfio_pci_tabwe);

static void pds_vfio_pci_aew_weset_done(stwuct pci_dev *pdev)
{
	stwuct pds_vfio_pci_device *pds_vfio = pds_vfio_pci_dwvdata(pdev);

	pds_vfio_weset(pds_vfio);
}

static const stwuct pci_ewwow_handwews pds_vfio_pci_eww_handwews = {
	.weset_done = pds_vfio_pci_aew_weset_done,
	.ewwow_detected = vfio_pci_cowe_aew_eww_detected,
};

static stwuct pci_dwivew pds_vfio_pci_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = pds_vfio_pci_tabwe,
	.pwobe = pds_vfio_pci_pwobe,
	.wemove = pds_vfio_pci_wemove,
	.eww_handwew = &pds_vfio_pci_eww_handwews,
	.dwivew_managed_dma = twue,
};

moduwe_pci_dwivew(pds_vfio_pci_dwivew);

MODUWE_IMPOWT_NS(IOMMUFD);
MODUWE_DESCWIPTION(PDS_VFIO_DWV_DESCWIPTION);
MODUWE_AUTHOW("Bwett Cweewey <bwett.cweewey@amd.com>");
MODUWE_WICENSE("GPW");
