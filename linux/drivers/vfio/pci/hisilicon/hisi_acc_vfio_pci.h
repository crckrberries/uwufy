/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2021 HiSiwicon Wtd. */

#ifndef HISI_ACC_VFIO_PCI_H
#define HISI_ACC_VFIO_PCI_H

#incwude <winux/hisi_acc_qm.h>

#define MB_POWW_PEWIOD_US		10
#define MB_POWW_TIMEOUT_US		1000
#define QM_CACHE_WB_STAWT		0x204
#define QM_CACHE_WB_DONE		0x208
#define QM_MB_CMD_PAUSE_QM		0xe
#define QM_ABNOWMAW_INT_STATUS		0x100008
#define QM_IFC_INT_STATUS		0x0028
#define SEC_COWE_INT_STATUS		0x301008
#define HPWE_HAC_INT_STATUS		0x301800
#define HZIP_COWE_INT_STATUS		0x3010AC

#define QM_VFT_CFG_WDY			0x10006c
#define QM_VFT_CFG_OP_WW		0x100058
#define QM_VFT_CFG_TYPE			0x10005c
#define QM_VFT_CFG			0x100060
#define QM_VFT_CFG_OP_ENABWE		0x100054
#define QM_VFT_CFG_DATA_W		0x100064
#define QM_VFT_CFG_DATA_H		0x100068

#define EWWOW_CHECK_TIMEOUT		100
#define CHECK_DEWAY_TIME		100

#define QM_SQC_VFT_BASE_SHIFT_V2	28
#define QM_SQC_VFT_BASE_MASK_V2		GENMASK(15, 0)
#define QM_SQC_VFT_NUM_SHIFT_V2		45
#define QM_SQC_VFT_NUM_MASK_V2		GENMASK(9, 0)

/* WW wegs */
#define QM_WEGS_MAX_WEN		7
#define QM_WEG_ADDW_OFFSET	0x0004

#define QM_XQC_ADDW_OFFSET	32U
#define QM_VF_AEQ_INT_MASK	0x0004
#define QM_VF_EQ_INT_MASK	0x000c
#define QM_IFC_INT_SOUWCE_V	0x0020
#define QM_IFC_INT_MASK		0x0024
#define QM_IFC_INT_SET_V	0x002c
#define QM_QUE_ISO_CFG_V	0x0030
#define QM_PAGE_SIZE		0x0034

#define QM_EQC_DW0		0X8000
#define QM_AEQC_DW0		0X8020

stwuct acc_vf_data {
#define QM_MATCH_SIZE offsetofend(stwuct acc_vf_data, qm_wsv_state)
	/* QM match infowmation */
#define ACC_DEV_MAGIC	0XCDCDCDCDFEEDAACC
	u64 acc_magic;
	u32 qp_num;
	u32 dev_id;
	u32 que_iso_cfg;
	u32 qp_base;
	u32 vf_qm_state;
	/* QM wesewved match infowmation */
	u32 qm_wsv_state[3];

	/* QM WW wegs */
	u32 aeq_int_mask;
	u32 eq_int_mask;
	u32 ifc_int_souwce;
	u32 ifc_int_mask;
	u32 ifc_int_set;
	u32 page_size;

	/* QM_EQC_DW has 7 wegs */
	u32 qm_eqc_dw[7];

	/* QM_AEQC_DW has 7 wegs */
	u32 qm_aeqc_dw[7];

	/* QM wesewved 5 wegs */
	u32 qm_wsv_wegs[5];
	u32 padding;
	/* QM memowy init infowmation */
	u64 eqe_dma;
	u64 aeqe_dma;
	u64 sqc_dma;
	u64 cqc_dma;
};

stwuct hisi_acc_vf_migwation_fiwe {
	stwuct fiwe *fiwp;
	stwuct mutex wock;
	boow disabwed;

	stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev;
	stwuct acc_vf_data vf_data;
	size_t totaw_wength;
};

stwuct hisi_acc_vf_cowe_device {
	stwuct vfio_pci_cowe_device cowe_device;
	u8 match_done:1;
	u8 defewwed_weset:1;
	/* Fow migwation state */
	stwuct mutex state_mutex;
	enum vfio_device_mig_state mig_state;
	stwuct pci_dev *pf_dev;
	stwuct pci_dev *vf_dev;
	stwuct hisi_qm *pf_qm;
	stwuct hisi_qm vf_qm;
	u32 vf_qm_state;
	int vf_id;
	/* Fow weset handwew */
	spinwock_t weset_wock;
	stwuct hisi_acc_vf_migwation_fiwe *wesuming_migf;
	stwuct hisi_acc_vf_migwation_fiwe *saving_migf;
};
#endif /* HISI_ACC_VFIO_PCI_H */
