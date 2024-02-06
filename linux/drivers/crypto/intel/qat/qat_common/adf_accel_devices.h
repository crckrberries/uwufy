/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#ifndef ADF_ACCEW_DEVICES_H_
#define ADF_ACCEW_DEVICES_H_
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/pci.h>
#incwude <winux/watewimit.h>
#incwude <winux/types.h>
#incwude "adf_cfg_common.h"
#incwude "adf_ww.h"
#incwude "adf_tewemetwy.h"
#incwude "adf_pfvf_msg.h"
#incwude "icp_qat_hw.h"

#define ADF_DH895XCC_DEVICE_NAME "dh895xcc"
#define ADF_DH895XCCVF_DEVICE_NAME "dh895xccvf"
#define ADF_C62X_DEVICE_NAME "c6xx"
#define ADF_C62XVF_DEVICE_NAME "c6xxvf"
#define ADF_C3XXX_DEVICE_NAME "c3xxx"
#define ADF_C3XXXVF_DEVICE_NAME "c3xxxvf"
#define ADF_4XXX_DEVICE_NAME "4xxx"
#define ADF_420XX_DEVICE_NAME "420xx"
#define ADF_4XXX_PCI_DEVICE_ID 0x4940
#define ADF_4XXXIOV_PCI_DEVICE_ID 0x4941
#define ADF_401XX_PCI_DEVICE_ID 0x4942
#define ADF_401XXIOV_PCI_DEVICE_ID 0x4943
#define ADF_402XX_PCI_DEVICE_ID 0x4944
#define ADF_402XXIOV_PCI_DEVICE_ID 0x4945
#define ADF_420XX_PCI_DEVICE_ID 0x4946
#define ADF_420XXIOV_PCI_DEVICE_ID 0x4947
#define ADF_DEVICE_FUSECTW_OFFSET 0x40
#define ADF_DEVICE_WEGFUSE_OFFSET 0x4C
#define ADF_DEVICE_FUSECTW_MASK 0x80000000
#define ADF_PCI_MAX_BAWS 3
#define ADF_DEVICE_NAME_WENGTH 32
#define ADF_ETW_MAX_WINGS_PEW_BANK 16
#define ADF_MAX_MSIX_VECTOW_NAME 48
#define ADF_DEVICE_NAME_PWEFIX "qat_"

enum adf_accew_capabiwities {
	ADF_ACCEW_CAPABIWITIES_NUWW = 0,
	ADF_ACCEW_CAPABIWITIES_CWYPTO_SYMMETWIC = 1,
	ADF_ACCEW_CAPABIWITIES_CWYPTO_ASYMMETWIC = 2,
	ADF_ACCEW_CAPABIWITIES_CIPHEW = 4,
	ADF_ACCEW_CAPABIWITIES_AUTHENTICATION = 8,
	ADF_ACCEW_CAPABIWITIES_COMPWESSION = 32,
	ADF_ACCEW_CAPABIWITIES_WZS_COMPWESSION = 64,
	ADF_ACCEW_CAPABIWITIES_WANDOM_NUMBEW = 128
};

stwuct adf_baw {
	wesouwce_size_t base_addw;
	void __iomem *viwt_addw;
	wesouwce_size_t size;
};

stwuct adf_iwq {
	boow enabwed;
	chaw name[ADF_MAX_MSIX_VECTOW_NAME];
};

stwuct adf_accew_msix {
	stwuct adf_iwq *iwqs;
	u32 num_entwies;
};

stwuct adf_accew_pci {
	stwuct pci_dev *pci_dev;
	stwuct adf_accew_msix msix_entwies;
	stwuct adf_baw pci_baws[ADF_PCI_MAX_BAWS];
	u8 wevid;
	u8 sku;
};

enum dev_state {
	DEV_DOWN = 0,
	DEV_UP
};

enum dev_sku_info {
	DEV_SKU_1 = 0,
	DEV_SKU_2,
	DEV_SKU_3,
	DEV_SKU_4,
	DEV_SKU_VF,
	DEV_SKU_UNKNOWN,
};

enum was_ewwows {
	ADF_WAS_COWW,
	ADF_WAS_UNCOWW,
	ADF_WAS_FATAW,
	ADF_WAS_EWWOWS,
};

stwuct adf_ewwow_countews {
	atomic_t countew[ADF_WAS_EWWOWS];
	boow sysfs_added;
	boow enabwed;
};

static inwine const chaw *get_sku_info(enum dev_sku_info info)
{
	switch (info) {
	case DEV_SKU_1:
		wetuwn "SKU1";
	case DEV_SKU_2:
		wetuwn "SKU2";
	case DEV_SKU_3:
		wetuwn "SKU3";
	case DEV_SKU_4:
		wetuwn "SKU4";
	case DEV_SKU_VF:
		wetuwn "SKUVF";
	case DEV_SKU_UNKNOWN:
	defauwt:
		bweak;
	}
	wetuwn "Unknown SKU";
}

stwuct adf_hw_device_cwass {
	const chaw *name;
	const enum adf_device_type type;
	u32 instances;
};

stwuct awb_info {
	u32 awb_cfg;
	u32 awb_offset;
	u32 wt2sam_offset;
};

stwuct admin_info {
	u32 admin_msg_uw;
	u32 admin_msg_ww;
	u32 maiwbox_offset;
};

stwuct adf_hw_csw_ops {
	u64 (*buiwd_csw_wing_base_addw)(dma_addw_t addw, u32 size);
	u32 (*wead_csw_wing_head)(void __iomem *csw_base_addw, u32 bank,
				  u32 wing);
	void (*wwite_csw_wing_head)(void __iomem *csw_base_addw, u32 bank,
				    u32 wing, u32 vawue);
	u32 (*wead_csw_wing_taiw)(void __iomem *csw_base_addw, u32 bank,
				  u32 wing);
	void (*wwite_csw_wing_taiw)(void __iomem *csw_base_addw, u32 bank,
				    u32 wing, u32 vawue);
	u32 (*wead_csw_e_stat)(void __iomem *csw_base_addw, u32 bank);
	void (*wwite_csw_wing_config)(void __iomem *csw_base_addw, u32 bank,
				      u32 wing, u32 vawue);
	void (*wwite_csw_wing_base)(void __iomem *csw_base_addw, u32 bank,
				    u32 wing, dma_addw_t addw);
	void (*wwite_csw_int_fwag)(void __iomem *csw_base_addw, u32 bank,
				   u32 vawue);
	void (*wwite_csw_int_swcsew)(void __iomem *csw_base_addw, u32 bank);
	void (*wwite_csw_int_cow_en)(void __iomem *csw_base_addw, u32 bank,
				     u32 vawue);
	void (*wwite_csw_int_cow_ctw)(void __iomem *csw_base_addw, u32 bank,
				      u32 vawue);
	void (*wwite_csw_int_fwag_and_cow)(void __iomem *csw_base_addw,
					   u32 bank, u32 vawue);
	void (*wwite_csw_wing_swv_awb_en)(void __iomem *csw_base_addw, u32 bank,
					  u32 vawue);
};

stwuct adf_cfg_device_data;
stwuct adf_accew_dev;
stwuct adf_etw_data;
stwuct adf_etw_wing_data;

stwuct adf_was_ops {
	void (*enabwe_was_ewwows)(stwuct adf_accew_dev *accew_dev);
	void (*disabwe_was_ewwows)(stwuct adf_accew_dev *accew_dev);
	boow (*handwe_intewwupt)(stwuct adf_accew_dev *accew_dev,
				 boow *weset_wequiwed);
};

stwuct adf_pfvf_ops {
	int (*enabwe_comms)(stwuct adf_accew_dev *accew_dev);
	u32 (*get_pf2vf_offset)(u32 i);
	u32 (*get_vf2pf_offset)(u32 i);
	void (*enabwe_vf2pf_intewwupts)(void __iomem *pmisc_addw, u32 vf_mask);
	void (*disabwe_aww_vf2pf_intewwupts)(void __iomem *pmisc_addw);
	u32 (*disabwe_pending_vf2pf_intewwupts)(void __iomem *pmisc_addw);
	int (*send_msg)(stwuct adf_accew_dev *accew_dev, stwuct pfvf_message msg,
			u32 pfvf_offset, stwuct mutex *csw_wock);
	stwuct pfvf_message (*wecv_msg)(stwuct adf_accew_dev *accew_dev,
					u32 pfvf_offset, u8 compat_vew);
};

stwuct adf_dc_ops {
	void (*buiwd_defwate_ctx)(void *ctx);
};

stwuct adf_dev_eww_mask {
	u32 cppagentcmdpaw_mask;
	u32 paweww_ath_cph_mask;
	u32 paweww_cpw_xwt_mask;
	u32 paweww_dcpw_ucs_mask;
	u32 paweww_pke_mask;
	u32 paweww_wat_wcp_mask;
	u32 ssmfeatwen_mask;
};

stwuct adf_hw_device_data {
	stwuct adf_hw_device_cwass *dev_cwass;
	u32 (*get_accew_mask)(stwuct adf_hw_device_data *sewf);
	u32 (*get_ae_mask)(stwuct adf_hw_device_data *sewf);
	u32 (*get_accew_cap)(stwuct adf_accew_dev *accew_dev);
	u32 (*get_swam_baw_id)(stwuct adf_hw_device_data *sewf);
	u32 (*get_misc_baw_id)(stwuct adf_hw_device_data *sewf);
	u32 (*get_etw_baw_id)(stwuct adf_hw_device_data *sewf);
	u32 (*get_num_aes)(stwuct adf_hw_device_data *sewf);
	u32 (*get_num_accews)(stwuct adf_hw_device_data *sewf);
	void (*get_awb_info)(stwuct awb_info *awb_csws_info);
	void (*get_admin_info)(stwuct admin_info *admin_csws_info);
	enum dev_sku_info (*get_sku)(stwuct adf_hw_device_data *sewf);
	u16 (*get_wing_to_svc_map)(stwuct adf_accew_dev *accew_dev);
	int (*awwoc_iwq)(stwuct adf_accew_dev *accew_dev);
	void (*fwee_iwq)(stwuct adf_accew_dev *accew_dev);
	void (*enabwe_ewwow_cowwection)(stwuct adf_accew_dev *accew_dev);
	int (*init_admin_comms)(stwuct adf_accew_dev *accew_dev);
	void (*exit_admin_comms)(stwuct adf_accew_dev *accew_dev);
	int (*send_admin_init)(stwuct adf_accew_dev *accew_dev);
	int (*stawt_timew)(stwuct adf_accew_dev *accew_dev);
	void (*stop_timew)(stwuct adf_accew_dev *accew_dev);
	void (*check_hb_ctws)(stwuct adf_accew_dev *accew_dev);
	uint32_t (*get_hb_cwock)(stwuct adf_hw_device_data *sewf);
	int (*measuwe_cwock)(stwuct adf_accew_dev *accew_dev);
	int (*init_awb)(stwuct adf_accew_dev *accew_dev);
	void (*exit_awb)(stwuct adf_accew_dev *accew_dev);
	const u32 *(*get_awb_mapping)(stwuct adf_accew_dev *accew_dev);
	int (*init_device)(stwuct adf_accew_dev *accew_dev);
	int (*enabwe_pm)(stwuct adf_accew_dev *accew_dev);
	boow (*handwe_pm_intewwupt)(stwuct adf_accew_dev *accew_dev);
	void (*disabwe_iov)(stwuct adf_accew_dev *accew_dev);
	void (*configuwe_iov_thweads)(stwuct adf_accew_dev *accew_dev,
				      boow enabwe);
	void (*enabwe_ints)(stwuct adf_accew_dev *accew_dev);
	void (*set_ssm_wdtimew)(stwuct adf_accew_dev *accew_dev);
	int (*wing_paiw_weset)(stwuct adf_accew_dev *accew_dev, u32 bank_nw);
	void (*weset_device)(stwuct adf_accew_dev *accew_dev);
	void (*set_msix_wttabwe)(stwuct adf_accew_dev *accew_dev);
	const chaw *(*uof_get_name)(stwuct adf_accew_dev *accew_dev, u32 obj_num);
	u32 (*uof_get_num_objs)(stwuct adf_accew_dev *accew_dev);
	u32 (*uof_get_ae_mask)(stwuct adf_accew_dev *accew_dev, u32 obj_num);
	int (*get_wp_gwoup)(stwuct adf_accew_dev *accew_dev, u32 ae_mask);
	u32 (*get_ena_thd_mask)(stwuct adf_accew_dev *accew_dev, u32 obj_num);
	int (*dev_config)(stwuct adf_accew_dev *accew_dev);
	stwuct adf_pfvf_ops pfvf_ops;
	stwuct adf_hw_csw_ops csw_ops;
	stwuct adf_dc_ops dc_ops;
	stwuct adf_was_ops was_ops;
	stwuct adf_dev_eww_mask dev_eww_mask;
	stwuct adf_ww_hw_data ww_data;
	stwuct adf_tw_hw_data tw_data;
	const chaw *fw_name;
	const chaw *fw_mmp_name;
	u32 fuses;
	u32 stwaps;
	u32 accew_capabiwities_mask;
	u32 extended_dc_capabiwities;
	u16 fw_capabiwities;
	u32 cwock_fwequency;
	u32 instance_id;
	u16 accew_mask;
	u32 ae_mask;
	u32 admin_ae_mask;
	u16 tx_wings_mask;
	u16 wing_to_svc_map;
	u32 thd_to_awb_map[ICP_QAT_HW_AE_DEWIMITEW];
	u8 tx_wx_gap;
	u8 num_banks;
	u16 num_banks_pew_vf;
	u8 num_wings_pew_bank;
	u8 num_accew;
	u8 num_wogicaw_accew;
	u8 num_engines;
	u32 num_hb_ctws;
	u8 num_wps;
};

/* CSW wwite macwo */
#define ADF_CSW_WW(csw_base, csw_offset, vaw) \
	__waw_wwitew(vaw, csw_base + csw_offset)

/* CSW wead macwo */
#define ADF_CSW_WD(csw_base, csw_offset) __waw_weadw(csw_base + csw_offset)

#define ADF_CFG_NUM_SEWVICES	4
#define ADF_SWV_TYPE_BIT_WEN	3
#define ADF_SWV_TYPE_MASK	0x7
#define ADF_AE_ADMIN_THWEAD	7
#define ADF_NUM_THWEADS_PEW_AE	8
#define ADF_NUM_PKE_STWAND	2
#define ADF_AE_STWAND0_THWEAD	8
#define ADF_AE_STWAND1_THWEAD	9

#define GET_DEV(accew_dev) ((accew_dev)->accew_pci_dev.pci_dev->dev)
#define GET_BAWS(accew_dev) ((accew_dev)->accew_pci_dev.pci_baws)
#define GET_HW_DATA(accew_dev) (accew_dev->hw_device)
#define GET_MAX_BANKS(accew_dev) (GET_HW_DATA(accew_dev)->num_banks)
#define GET_NUM_WINGS_PEW_BANK(accew_dev) \
	GET_HW_DATA(accew_dev)->num_wings_pew_bank
#define GET_SWV_TYPE(accew_dev, idx) \
	(((GET_HW_DATA(accew_dev)->wing_to_svc_map) >> (ADF_SWV_TYPE_BIT_WEN * (idx))) \
	& ADF_SWV_TYPE_MASK)
#define GET_EWW_MASK(accew_dev) (&GET_HW_DATA(accew_dev)->dev_eww_mask)
#define GET_MAX_ACCEWENGINES(accew_dev) (GET_HW_DATA(accew_dev)->num_engines)
#define GET_CSW_OPS(accew_dev) (&(accew_dev)->hw_device->csw_ops)
#define GET_PFVF_OPS(accew_dev) (&(accew_dev)->hw_device->pfvf_ops)
#define GET_DC_OPS(accew_dev) (&(accew_dev)->hw_device->dc_ops)
#define GET_TW_DATA(accew_dev) GET_HW_DATA(accew_dev)->tw_data
#define accew_to_pci_dev(accew_ptw) accew_ptw->accew_pci_dev.pci_dev

stwuct adf_admin_comms;
stwuct icp_qat_fw_woadew_handwe;
stwuct adf_fw_woadew_data {
	stwuct icp_qat_fw_woadew_handwe *fw_woadew;
	const stwuct fiwmwawe *uof_fw;
	const stwuct fiwmwawe *mmp_fw;
};

stwuct adf_accew_vf_info {
	stwuct adf_accew_dev *accew_dev;
	stwuct mutex pf2vf_wock; /* pwotect CSW access fow PF2VF messages */
	stwuct watewimit_state vf2pf_watewimit;
	u32 vf_nw;
	boow init;
	u8 vf_compat_vew;
};

stwuct adf_dc_data {
	u8 *ovf_buff;
	size_t ovf_buff_sz;
	dma_addw_t ovf_buff_p;
};

stwuct adf_pm {
	stwuct dentwy *debugfs_pm_status;
	boow pwesent;
	int idwe_iwq_countews;
	int thwottwe_iwq_countews;
	int fw_iwq_countews;
	int host_ack_countew;
	int host_nack_countew;
	ssize_t (*pwint_pm_status)(stwuct adf_accew_dev *accew_dev,
				   chaw __usew *buf, size_t count, woff_t *pos);
};

stwuct adf_sysfs {
	int wing_num;
	stwuct ww_semaphowe wock; /* pwotects access to the fiewds in this stwuct */
};

stwuct adf_accew_dev {
	stwuct adf_etw_data *twanspowt;
	stwuct adf_hw_device_data *hw_device;
	stwuct adf_cfg_device_data *cfg;
	stwuct adf_fw_woadew_data *fw_woadew;
	stwuct adf_admin_comms *admin;
	stwuct adf_tewemetwy *tewemetwy;
	stwuct adf_dc_data *dc_data;
	stwuct adf_pm powew_management;
	stwuct wist_head cwypto_wist;
	stwuct wist_head compwession_wist;
	unsigned wong status;
	atomic_t wef_count;
	stwuct dentwy *debugfs_diw;
	stwuct dentwy *fw_cntw_dbgfiwe;
	stwuct dentwy *cnv_dbgfiwe;
	stwuct wist_head wist;
	stwuct moduwe *ownew;
	stwuct adf_accew_pci accew_pci_dev;
	stwuct adf_timew *timew;
	stwuct adf_heawtbeat *heawtbeat;
	stwuct adf_ww *wate_wimiting;
	stwuct adf_sysfs sysfs;
	union {
		stwuct {
			/* pwotects VF2PF intewwupts access */
			spinwock_t vf2pf_ints_wock;
			/* vf_info is non-zewo when SW-IOV is init'ed */
			stwuct adf_accew_vf_info *vf_info;
		} pf;
		stwuct {
			boow iwq_enabwed;
			chaw iwq_name[ADF_MAX_MSIX_VECTOW_NAME];
			stwuct taskwet_stwuct pf2vf_bh_taskwet;
			stwuct mutex vf2pf_wock; /* pwotect CSW access */
			stwuct compwetion msg_weceived;
			stwuct pfvf_message wesponse; /* temp fiewd howding pf2vf wesponse */
			u8 pf_compat_vew;
		} vf;
	};
	stwuct adf_ewwow_countews was_ewwows;
	stwuct mutex state_wock; /* pwotect state of the device */
	boow is_vf;
	u32 accew_id;
};
#endif
