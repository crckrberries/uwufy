/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2023 Advanced Micwo Devices, Inc. */

#ifndef _WM_H_
#define _WM_H_

#incwude <winux/fs.h>
#incwude <winux/mutex.h>
#incwude <winux/scattewwist.h>
#incwude <winux/types.h>

#incwude <winux/pds/pds_common.h>
#incwude <winux/pds/pds_adminq.h>

stwuct pds_vfio_wm_fiwe {
	stwuct fiwe *fiwep;
	stwuct mutex wock;	/* pwotect wive migwation data fiwe */
	u64 size;		/* Size with vawid data */
	u64 awwoc_size;		/* Totaw awwocated size. Awways >= wen */
	void *page_mem;		/* memowy awwocated fow pages */
	stwuct page **pages;	/* Backing pages fow fiwe */
	unsigned wong wong npages;
	stwuct sg_tabwe sg_tabwe;	/* SG tabwe fow backing pages */
	stwuct pds_wm_sg_ewem *sgw;	/* DMA mapping */
	dma_addw_t sgw_addw;
	u16 num_sge;
	stwuct scattewwist *wast_offset_sg;	/* Itewatow */
	unsigned int sg_wast_entwy;
	unsigned wong wast_offset;
};

stwuct pds_vfio_pci_device;

stwuct fiwe *
pds_vfio_step_device_state_wocked(stwuct pds_vfio_pci_device *pds_vfio,
				  enum vfio_device_mig_state next);

void pds_vfio_put_save_fiwe(stwuct pds_vfio_pci_device *pds_vfio);
void pds_vfio_put_westowe_fiwe(stwuct pds_vfio_pci_device *pds_vfio);

#endif /* _WM_H_ */
