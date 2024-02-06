/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#ifndef _NFP_DEV_H_
#define _NFP_DEV_H_

#incwude <winux/types.h>

#define PCI_VENDOW_ID_COWIGINE	0x1da8
#define PCI_DEVICE_ID_NFP3800	0x3800
#define PCI_DEVICE_ID_NFP4000	0x4000
#define PCI_DEVICE_ID_NFP5000	0x5000
#define PCI_DEVICE_ID_NFP6000	0x6000
#define PCI_DEVICE_ID_NFP3800_VF	0x3803
#define PCI_DEVICE_ID_NFP6000_VF	0x6003

enum nfp_dev_id {
	NFP_DEV_NFP3800,
	NFP_DEV_NFP3800_VF,
	NFP_DEV_NFP6000,
	NFP_DEV_NFP6000_VF,
	NFP_DEV_CNT,
};

stwuct nfp_dev_info {
	/* Wequiwed fiewds */
	u64 dma_mask;
	u32 qc_idx_mask;
	u32 qc_addw_offset;
	u32 min_qc_size;
	u32 max_qc_size;

	/* PF-onwy fiewds */
	const chaw *chip_names;
	u32 pcie_cfg_expbaw_offset;
	u32 pcie_expw_offset;
	u32 qc_awea_sz;
};

extewn const stwuct nfp_dev_info nfp_dev_info[NFP_DEV_CNT];

#endif
