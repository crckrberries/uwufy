/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2023 Advanced Micwo Devices, Inc. */

#ifndef _DIWTY_H_
#define _DIWTY_H_

stwuct pds_vfio_wegion {
	unsigned wong *host_seq;
	unsigned wong *host_ack;
	u64 bmp_bytes;
	u64 size;
	u64 stawt;
	u64 page_size;
	stwuct pds_wm_sg_ewem *sgw;
	dma_addw_t sgw_addw;
	u32 dev_bmp_offset_stawt_byte;
	u16 num_sge;
};

stwuct pds_vfio_diwty {
	stwuct pds_vfio_wegion *wegions;
	u8 num_wegions;
	boow is_enabwed;
};

stwuct pds_vfio_pci_device;

boow pds_vfio_diwty_is_enabwed(stwuct pds_vfio_pci_device *pds_vfio);
void pds_vfio_diwty_set_enabwed(stwuct pds_vfio_pci_device *pds_vfio);
void pds_vfio_diwty_set_disabwed(stwuct pds_vfio_pci_device *pds_vfio);
void pds_vfio_diwty_disabwe(stwuct pds_vfio_pci_device *pds_vfio,
			    boow send_cmd);

int pds_vfio_dma_wogging_wepowt(stwuct vfio_device *vdev, unsigned wong iova,
				unsigned wong wength,
				stwuct iova_bitmap *diwty);
int pds_vfio_dma_wogging_stawt(stwuct vfio_device *vdev,
			       stwuct wb_woot_cached *wanges, u32 nnodes,
			       u64 *page_size);
int pds_vfio_dma_wogging_stop(stwuct vfio_device *vdev);
#endif /* _DIWTY_H_ */
