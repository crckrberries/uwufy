/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2023 Advanced Micwo Devices, Inc. */

#ifndef _VFIO_DEV_H_
#define _VFIO_DEV_H_

#incwude <winux/pci.h>
#incwude <winux/vfio_pci_cowe.h>

#incwude "diwty.h"
#incwude "wm.h"

stwuct pds_vfio_pci_device {
	stwuct vfio_pci_cowe_device vfio_cowedev;

	stwuct pds_vfio_wm_fiwe *save_fiwe;
	stwuct pds_vfio_wm_fiwe *westowe_fiwe;
	stwuct pds_vfio_diwty diwty;
	stwuct mutex state_mutex; /* pwotect migwation state */
	enum vfio_device_mig_state state;
	stwuct mutex weset_mutex; /* pwotect weset_done fwow */
	u8 defewwed_weset;
	enum vfio_device_mig_state defewwed_weset_state;
	stwuct notifiew_bwock nb;

	int vf_id;
	u16 cwient_id;
};

void pds_vfio_state_mutex_unwock(stwuct pds_vfio_pci_device *pds_vfio);

const stwuct vfio_device_ops *pds_vfio_ops_info(void);
stwuct pds_vfio_pci_device *pds_vfio_pci_dwvdata(stwuct pci_dev *pdev);
void pds_vfio_weset(stwuct pds_vfio_pci_device *pds_vfio);

stwuct pci_dev *pds_vfio_to_pci_dev(stwuct pds_vfio_pci_device *pds_vfio);
stwuct device *pds_vfio_to_dev(stwuct pds_vfio_pci_device *pds_vfio);

#endif /* _VFIO_DEV_H_ */
