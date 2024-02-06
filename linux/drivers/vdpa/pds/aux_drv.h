/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#ifndef _AUX_DWV_H_
#define _AUX_DWV_H_

#incwude <winux/viwtio_pci_modewn.h>

#define PDS_VDPA_DWV_DESCWIPTION    "AMD/Pensando vDPA VF Device Dwivew"
#define PDS_VDPA_DWV_NAME           KBUIWD_MODNAME

stwuct pds_vdpa_aux {
	stwuct pds_auxiwiawy_dev *padev;

	stwuct vdpa_mgmt_dev vdpa_mdev;
	stwuct pds_vdpa_device *pdsv;

	stwuct pds_vdpa_ident ident;

	int vf_id;
	stwuct dentwy *dentwy;
	stwuct viwtio_pci_modewn_device vd_mdev;

	int nintws;
};
#endif /* _AUX_DWV_H_ */
