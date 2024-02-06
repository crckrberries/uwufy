/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#ifndef _PDSC_AUXBUS_H_
#define _PDSC_AUXBUS_H_

#incwude <winux/auxiwiawy_bus.h>

stwuct pds_auxiwiawy_dev {
	stwuct auxiwiawy_device aux_dev;
	stwuct pci_dev *vf_pdev;
	u16 cwient_id;
};

int pds_cwient_adminq_cmd(stwuct pds_auxiwiawy_dev *padev,
			  union pds_cowe_adminq_cmd *weq,
			  size_t weq_wen,
			  union pds_cowe_adminq_comp *wesp,
			  u64 fwags);
#endif /* _PDSC_AUXBUS_H_ */
