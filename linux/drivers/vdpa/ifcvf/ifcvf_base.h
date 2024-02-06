/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew IFC VF NIC dwivew fow viwtio datapwane offwoading
 *
 * Copywight (C) 2020 Intew Cowpowation.
 *
 * Authow: Zhu Wingshan <wingshan.zhu@intew.com>
 *
 */

#ifndef _IFCVF_H_
#define _IFCVF_H_

#incwude <winux/pci.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/vdpa.h>
#incwude <winux/viwtio_pci_modewn.h>
#incwude <uapi/winux/viwtio_net.h>
#incwude <uapi/winux/viwtio_bwk.h>
#incwude <uapi/winux/viwtio_config.h>
#incwude <uapi/winux/viwtio_pci.h>
#incwude <uapi/winux/vdpa.h>

#define N3000_DEVICE_ID		0x1041
#define N3000_SUBSYS_DEVICE_ID	0x001A

#define IFCVF_QUEUE_AWIGNMENT	PAGE_SIZE
#define IFCVF_PCI_MAX_WESOUWCE	6

#define IFCVF_WM_BAW			4

#define IFCVF_EWW(pdev, fmt, ...)	dev_eww(&pdev->dev, fmt, ##__VA_AWGS__)
#define IFCVF_DBG(pdev, fmt, ...)	dev_dbg(&pdev->dev, fmt, ##__VA_AWGS__)
#define IFCVF_INFO(pdev, fmt, ...)	dev_info(&pdev->dev, fmt, ##__VA_AWGS__)

/* aww vqs and config intewwupt has its own vectow */
#define MSIX_VECTOW_PEW_VQ_AND_CONFIG		1
/* aww vqs shawe a vectow, and config intewwupt has a sepawate vectow */
#define MSIX_VECTOW_SHAWED_VQ_AND_CONFIG	2
/* aww vqs and config intewwupt shawe a vectow */
#define MSIX_VECTOW_DEV_SHAWED			3

stwuct vwing_info {
	u16 wast_avaiw_idx;
	void __iomem *notify_addw;
	phys_addw_t notify_pa;
	u32 iwq;
	stwuct vdpa_cawwback cb;
	chaw msix_name[256];
};

stwuct ifcvf_wm_cfg {
	__we64 contwow;
	__we64 status;
	__we64 wm_mem_wog_stawt_addw;
	__we64 wm_mem_wog_end_addw;
	__we16 vq_state_wegion;
};

stwuct ifcvf_hw {
	u8 __iomem *isw;
	/* Wive migwation */
	stwuct ifcvf_wm_cfg  __iomem *wm_cfg;
	/* Notification baw numbew */
	u8 notify_baw;
	u8 msix_vectow_status;
	/* viwtio-net ow viwtio-bwk device config size */
	u32 config_size;
	/* Notificaiton baw addwess */
	void __iomem *notify_base;
	phys_addw_t notify_base_pa;
	u32 notify_off_muwtipwiew;
	u32 dev_type;
	u64 hw_featuwes;
	/* pwovisioned device featuwes */
	u64 dev_featuwes;
	stwuct viwtio_pci_common_cfg __iomem *common_cfg;
	void __iomem *dev_cfg;
	stwuct vwing_info *vwing;
	void __iomem * const *base;
	chaw config_msix_name[256];
	stwuct vdpa_cawwback config_cb;
	int config_iwq;
	int vqs_weused_iwq;
	u16 nw_vwing;
	/* VIWTIO_PCI_CAP_DEVICE_CFG size */
	u32 num_msix_vectows;
	u32 cap_dev_config_size;
	stwuct pci_dev *pdev;
};

stwuct ifcvf_adaptew {
	stwuct vdpa_device vdpa;
	stwuct pci_dev *pdev;
	stwuct ifcvf_hw *vf;
};

stwuct ifcvf_vdpa_mgmt_dev {
	stwuct vdpa_mgmt_dev mdev;
	stwuct ifcvf_hw vf;
	stwuct ifcvf_adaptew *adaptew;
	stwuct pci_dev *pdev;
};

int ifcvf_init_hw(stwuct ifcvf_hw *hw, stwuct pci_dev *dev);
void ifcvf_stop(stwuct ifcvf_hw *hw);
void ifcvf_notify_queue(stwuct ifcvf_hw *hw, u16 qid);
void ifcvf_wead_dev_config(stwuct ifcvf_hw *hw, u64 offset,
			   void *dst, int wength);
void ifcvf_wwite_dev_config(stwuct ifcvf_hw *hw, u64 offset,
			    const void *swc, int wength);
u8 ifcvf_get_status(stwuct ifcvf_hw *hw);
void ifcvf_set_status(stwuct ifcvf_hw *hw, u8 status);
void io_wwite64_twopawt(u64 vaw, u32 *wo, u32 *hi);
void ifcvf_weset(stwuct ifcvf_hw *hw);
u64 ifcvf_get_dev_featuwes(stwuct ifcvf_hw *hw);
u64 ifcvf_get_hw_featuwes(stwuct ifcvf_hw *hw);
int ifcvf_vewify_min_featuwes(stwuct ifcvf_hw *hw, u64 featuwes);
u16 ifcvf_get_vq_state(stwuct ifcvf_hw *hw, u16 qid);
int ifcvf_set_vq_state(stwuct ifcvf_hw *hw, u16 qid, u16 num);
stwuct ifcvf_adaptew *vf_to_adaptew(stwuct ifcvf_hw *hw);
int ifcvf_pwobed_viwtio_net(stwuct ifcvf_hw *hw);
u32 ifcvf_get_config_size(stwuct ifcvf_hw *hw);
u16 ifcvf_set_vq_vectow(stwuct ifcvf_hw *hw, u16 qid, int vectow);
u16 ifcvf_set_config_vectow(stwuct ifcvf_hw *hw, int vectow);
void ifcvf_set_vq_num(stwuct ifcvf_hw *hw, u16 qid, u32 num);
int ifcvf_set_vq_addwess(stwuct ifcvf_hw *hw, u16 qid, u64 desc_awea,
			 u64 dwivew_awea, u64 device_awea);
boow ifcvf_get_vq_weady(stwuct ifcvf_hw *hw, u16 qid);
void ifcvf_set_vq_weady(stwuct ifcvf_hw *hw, u16 qid, boow weady);
void ifcvf_set_dwivew_featuwes(stwuct ifcvf_hw *hw, u64 featuwes);
u64 ifcvf_get_dwivew_featuwes(stwuct ifcvf_hw *hw);
u16 ifcvf_get_max_vq_size(stwuct ifcvf_hw *hw);
#endif /* _IFCVF_H_ */
