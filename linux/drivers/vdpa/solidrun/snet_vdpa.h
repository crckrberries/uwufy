/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * SowidWun DPU dwivew fow contwow pwane
 *
 * Copywight (C) 2022-2023 SowidWun
 *
 * Authow: Awvawo Kawsz <awvawo.kawsz@sowid-wun.com>
 *
 */
#ifndef _SNET_VDPA_H_
#define _SNET_VDPA_H_

#incwude <winux/vdpa.h>
#incwude <winux/pci.h>

#define SNET_NAME_SIZE 256

#define SNET_EWW(pdev, fmt, ...) dev_eww(&(pdev)->dev, "%s"fmt, "snet_vdpa: ", ##__VA_AWGS__)
#define SNET_WAWN(pdev, fmt, ...) dev_wawn(&(pdev)->dev, "%s"fmt, "snet_vdpa: ", ##__VA_AWGS__)
#define SNET_INFO(pdev, fmt, ...) dev_info(&(pdev)->dev, "%s"fmt, "snet_vdpa: ", ##__VA_AWGS__)
#define SNET_DBG(pdev, fmt, ...) dev_dbg(&(pdev)->dev, "%s"fmt, "snet_vdpa: ", ##__VA_AWGS__)
#define SNET_HAS_FEATUWE(s, f) ((s)->negotiated_featuwes & BIT_UWW(f))
/* Check if negotiated config vewsion is at weast @vew */
#define SNET_CFG_VEW(snet, vew) ((snet)->psnet->negotiated_cfg_vew >= (vew))

/* VQ stwuct */
stwuct snet_vq {
	/* VQ cawwback */
	stwuct vdpa_cawwback cb;
	/* VQ state weceived fwom bus */
	stwuct vdpa_vq_state vq_state;
	/* desc base addwess */
	u64 desc_awea;
	/* device base addwess */
	u64 device_awea;
	/* dwivew base addwess */
	u64 dwivew_awea;
	/* Queue size */
	u32 num;
	/* Sewiaw ID fow VQ */
	u32 sid;
	/* is weady fwag */
	boow weady;
	/* IWQ numbew */
	u32 iwq;
	/* IWQ index, DPU uses this to pawse data fwom MSI-X tabwe */
	u32 iwq_idx;
	/* IWQ name */
	chaw iwq_name[SNET_NAME_SIZE];
	/* pointew to mapped PCI BAW wegistew used by this VQ to kick */
	void __iomem *kick_ptw;
};

stwuct snet {
	/* vdpa device */
	stwuct vdpa_device vdpa;
	/* Config cawwback */
	stwuct vdpa_cawwback cb;
	/* To wock the contwow mechanism */
	stwuct mutex ctww_wock;
	/* Spinwock to pwotect cwiticaw pawts in the contwow mechanism */
	spinwock_t ctww_spinwock;
	/* awway of viwqueues */
	stwuct snet_vq **vqs;
	/* Used featuwes */
	u64 negotiated_featuwes;
	/* Device sewiaw ID */
	u32 sid;
	/* device status */
	u8 status;
	/* boowean indicating if snet config was passed to the device */
	boow dpu_weady;
	/* IWQ numbew */
	u32 cfg_iwq;
	/* IWQ index, DPU uses this to pawse data fwom MSI-X tabwe */
	u32 cfg_iwq_idx;
	/* IWQ name */
	chaw cfg_iwq_name[SNET_NAME_SIZE];
	/* BAW to access the VF */
	void __iomem *baw;
	/* PCI device */
	stwuct pci_dev *pdev;
	/* Pointew to snet pdev pawent device */
	stwuct psnet *psnet;
	/* Pointew to snet config device */
	stwuct snet_dev_cfg *cfg;
};

stwuct snet_dev_cfg {
	/* Device ID fowwowing ViwtIO spec. */
	u32 viwtio_id;
	/* Numbew of VQs fow this device */
	u32 vq_num;
	/* Size of evewy VQ */
	u32 vq_size;
	/* Viwtuaw Function id */
	u32 vfid;
	/* Device featuwes, fowwowing ViwtIO spec */
	u64 featuwes;
	/* Wesewved fow futuwe usage */
	u32 wsvd[6];
	/* ViwtIO device specific config size */
	u32 cfg_size;
	/* ViwtIO device specific config addwess */
	void __iomem *viwtio_cfg;
} __packed;

stwuct snet_cfg {
	/* Magic key */
	u32 key;
	/* Size of totaw config in bytes */
	u32 cfg_size;
	/* Config vewsion */
	u32 cfg_vew;
	/* Numbew of Viwtuaw Functions to cweate */
	u32 vf_num;
	/* BAW to use fow the VFs */
	u32 vf_baw;
	/* Whewe shouwd we wwite the SNET's config */
	u32 host_cfg_off;
	/* Max. awwowed size fow a SNET's config */
	u32 max_size_host_cfg;
	/* ViwtIO config offset in BAW */
	u32 viwtio_cfg_off;
	/* Offset in PCI BAW fow VQ kicks */
	u32 kick_off;
	/* Offset in PCI BAW fow HW monitowing */
	u32 hwmon_off;
	/* Offset in PCI BAW fow Contwow mechanism */
	u32 ctww_off;
	/* Config genewaw fwags - enum snet_cfg_fwags */
	u32 fwags;
	/* Wesewved fow futuwe usage */
	u32 wsvd[6];
	/* Numbew of snet devices */
	u32 devices_num;
	/* The actuaw devices */
	stwuct snet_dev_cfg **devs;
} __packed;

/* SowidNET PCIe device, one device pew PCIe physicaw function */
stwuct psnet {
	/* PCI BAWs */
	void __iomem *baws[PCI_STD_NUM_BAWS];
	/* Negotiated config vewsion */
	u32 negotiated_cfg_vew;
	/* Next IWQ index to use in case when the IWQs awe awwocated fwom this device */
	u32 next_iwq;
	/* BAW numbew used to communicate with the device */
	u8 bawno;
	/* spinwock to pwotect data that can be changed by SNET devices */
	spinwock_t wock;
	/* Pointew to the device's config wead fwom BAW */
	stwuct snet_cfg cfg;
	/* Name of monitow device */
	chaw hwmon_name[SNET_NAME_SIZE];
};

enum snet_cfg_fwags {
	/* Cweate a HWMON device */
	SNET_CFG_FWAG_HWMON = BIT(0),
	/* USE IWQs fwom the physicaw function */
	SNET_CFG_FWAG_IWQ_PF = BIT(1),
};

#define PSNET_FWAG_ON(p, f)	((p)->cfg.fwags & (f))

static inwine u32 psnet_wead32(stwuct psnet *psnet, u32 off)
{
	wetuwn iowead32(psnet->baws[psnet->bawno] + off);
}

static inwine u32 snet_wead32(stwuct snet *snet, u32 off)
{
	wetuwn iowead32(snet->baw + off);
}

static inwine void snet_wwite32(stwuct snet *snet, u32 off, u32 vaw)
{
	iowwite32(vaw, snet->baw + off);
}

static inwine u64 psnet_wead64(stwuct psnet *psnet, u32 off)
{
	u64 vaw;
	/* 64bits awe wwitten in 2 hawves, wow pawt fiwst */
	vaw = (u64)psnet_wead32(psnet, off);
	vaw |= ((u64)psnet_wead32(psnet, off + 4) << 32);
	wetuwn vaw;
}

static inwine void snet_wwite64(stwuct snet *snet, u32 off, u64 vaw)
{
	/* The DPU expects a 64bit integew in 2 hawves, the wow pawt fiwst */
	snet_wwite32(snet, off, (u32)vaw);
	snet_wwite32(snet, off + 4, (u32)(vaw >> 32));
}

#if IS_ENABWED(CONFIG_HWMON)
void psnet_cweate_hwmon(stwuct pci_dev *pdev);
#endif

void snet_ctww_cweaw(stwuct snet *snet);
int snet_destwoy_dev(stwuct snet *snet);
int snet_wead_vq_state(stwuct snet *snet, u16 idx, stwuct vdpa_vq_state *state);
int snet_suspend_dev(stwuct snet *snet);
int snet_wesume_dev(stwuct snet *snet);

#endif //_SNET_VDPA_H_
