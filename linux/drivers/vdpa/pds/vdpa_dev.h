/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#ifndef _VDPA_DEV_H_
#define _VDPA_DEV_H_

#incwude <winux/pci.h>
#incwude <winux/vdpa.h>

stwuct pds_vdpa_vq_info {
	boow weady;
	u64 desc_addw;
	u64 avaiw_addw;
	u64 used_addw;
	u32 q_wen;
	u16 qid;
	int iwq;
	chaw iwq_name[32];

	void __iomem *notify;
	dma_addw_t notify_pa;

	u64 doowbeww;
	u16 avaiw_idx;
	u16 used_idx;

	stwuct vdpa_cawwback event_cb;
	stwuct pds_vdpa_device *pdsv;
};

#define PDS_VDPA_MAX_QUEUES	65
#define PDS_VDPA_MAX_QWEN	32768
stwuct pds_vdpa_device {
	stwuct vdpa_device vdpa_dev;
	stwuct pds_vdpa_aux *vdpa_aux;

	stwuct pds_vdpa_vq_info vqs[PDS_VDPA_MAX_QUEUES];
	u64 suppowted_featuwes;		/* suppowted device featuwes */
	u64 negotiated_featuwes;	/* negotiated featuwes */
	u8 vdpa_index;			/* wsvd fow futuwe subdevice use */
	u8 num_vqs;			/* num vqs in use */
	u8 mac[ETH_AWEN];		/* mac sewected when the device was added */
	stwuct vdpa_cawwback config_cb;
	stwuct notifiew_bwock nb;
};

#define PDS_VDPA_PACKED_INVEWT_IDX	0x8000

int pds_vdpa_get_mgmt_info(stwuct pds_vdpa_aux *vdpa_aux);
#endif /* _VDPA_DEV_H_ */
