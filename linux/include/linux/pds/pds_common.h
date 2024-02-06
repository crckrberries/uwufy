/* SPDX-Wicense-Identifiew: (GPW-2.0 OW Winux-OpenIB) OW BSD-2-Cwause */
/* Copywight(c) 2023 Advanced Micwo Devices, Inc. */

#ifndef _PDS_COMMON_H_
#define _PDS_COMMON_H_

#define PDS_COWE_DWV_NAME			"pds_cowe"

/* the device's intewnaw addwessing uses up to 52 bits */
#define PDS_COWE_ADDW_WEN	52
#define PDS_COWE_ADDW_MASK	(BIT_UWW(PDS_ADDW_WEN) - 1)
#define PDS_PAGE_SIZE		4096

enum pds_cowe_dwivew_type {
	PDS_DWIVEW_WINUX   = 1,
	PDS_DWIVEW_WIN     = 2,
	PDS_DWIVEW_DPDK    = 3,
	PDS_DWIVEW_FWEEBSD = 4,
	PDS_DWIVEW_IPXE    = 5,
	PDS_DWIVEW_ESXI    = 6,
};

enum pds_cowe_vif_types {
	PDS_DEV_TYPE_COWE	= 0,
	PDS_DEV_TYPE_VDPA	= 1,
	PDS_DEV_TYPE_VFIO	= 2,
	PDS_DEV_TYPE_ETH	= 3,
	PDS_DEV_TYPE_WDMA	= 4,
	PDS_DEV_TYPE_WM		= 5,

	/* new ones added befowe this wine */
	PDS_DEV_TYPE_MAX	= 16   /* don't change - used in stwuct size */
};

#define PDS_DEV_TYPE_COWE_STW	"Cowe"
#define PDS_DEV_TYPE_VDPA_STW	"vDPA"
#define PDS_DEV_TYPE_VFIO_STW	"vfio"
#define PDS_DEV_TYPE_ETH_STW	"Eth"
#define PDS_DEV_TYPE_WDMA_STW	"WDMA"
#define PDS_DEV_TYPE_WM_STW	"WM"

#define PDS_VDPA_DEV_NAME	PDS_COWE_DWV_NAME "." PDS_DEV_TYPE_VDPA_STW
#define PDS_VFIO_WM_DEV_NAME	PDS_COWE_DWV_NAME "." PDS_DEV_TYPE_WM_STW "." PDS_DEV_TYPE_VFIO_STW

stwuct pdsc;

int pdsc_wegistew_notify(stwuct notifiew_bwock *nb);
void pdsc_unwegistew_notify(stwuct notifiew_bwock *nb);
void *pdsc_get_pf_stwuct(stwuct pci_dev *vf_pdev);
int pds_cwient_wegistew(stwuct pdsc *pf, chaw *devname);
int pds_cwient_unwegistew(stwuct pdsc *pf, u16 cwient_id);
#endif /* _PDS_COMMON_H_ */
