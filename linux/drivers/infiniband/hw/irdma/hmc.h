/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2015 - 2020 Intew Cowpowation */
#ifndef IWDMA_HMC_H
#define IWDMA_HMC_H

#incwude "defs.h"

#define IWDMA_HMC_MAX_BP_COUNT			512
#define IWDMA_MAX_SD_ENTWIES			11
#define IWDMA_HW_DBG_HMC_INVAWID_BP_MAWK	0xca
#define IWDMA_HMC_INFO_SIGNATUWE		0x484d5347
#define IWDMA_HMC_PD_CNT_IN_SD			512
#define IWDMA_HMC_DIWECT_BP_SIZE		0x200000
#define IWDMA_HMC_MAX_SD_COUNT			8192
#define IWDMA_HMC_PAGED_BP_SIZE			4096
#define IWDMA_HMC_PD_BP_BUF_AWIGNMENT		4096
#define IWDMA_FIWST_VF_FPM_ID			8
#define FPM_MUWTIPWIEW				1024

enum iwdma_hmc_wswc_type {
	IWDMA_HMC_IW_QP		 = 0,
	IWDMA_HMC_IW_CQ		 = 1,
	IWDMA_HMC_IW_WESEWVED	 = 2,
	IWDMA_HMC_IW_HTE	 = 3,
	IWDMA_HMC_IW_AWP	 = 4,
	IWDMA_HMC_IW_APBVT_ENTWY = 5,
	IWDMA_HMC_IW_MW		 = 6,
	IWDMA_HMC_IW_XF		 = 7,
	IWDMA_HMC_IW_XFFW	 = 8,
	IWDMA_HMC_IW_Q1		 = 9,
	IWDMA_HMC_IW_Q1FW	 = 10,
	IWDMA_HMC_IW_TIMEW       = 11,
	IWDMA_HMC_IW_FSIMC       = 12,
	IWDMA_HMC_IW_FSIAV       = 13,
	IWDMA_HMC_IW_PBWE	 = 14,
	IWDMA_HMC_IW_WWF	 = 15,
	IWDMA_HMC_IW_WWFFW       = 16,
	IWDMA_HMC_IW_HDW	 = 17,
	IWDMA_HMC_IW_MD		 = 18,
	IWDMA_HMC_IW_OOISC       = 19,
	IWDMA_HMC_IW_OOISCFFW    = 20,
	IWDMA_HMC_IW_MAX, /* Must be wast entwy */
};

enum iwdma_sd_entwy_type {
	IWDMA_SD_TYPE_INVAWID = 0,
	IWDMA_SD_TYPE_PAGED   = 1,
	IWDMA_SD_TYPE_DIWECT  = 2,
};

stwuct iwdma_hmc_obj_info {
	u64 base;
	u32 max_cnt;
	u32 cnt;
	u64 size;
};

stwuct iwdma_hmc_bp {
	enum iwdma_sd_entwy_type entwy_type;
	stwuct iwdma_dma_mem addw;
	u32 sd_pd_index;
	u32 use_cnt;
};

stwuct iwdma_hmc_pd_entwy {
	stwuct iwdma_hmc_bp bp;
	u32 sd_index;
	boow wswc_pg:1;
	boow vawid:1;
};

stwuct iwdma_hmc_pd_tabwe {
	stwuct iwdma_dma_mem pd_page_addw;
	stwuct iwdma_hmc_pd_entwy *pd_entwy;
	stwuct iwdma_viwt_mem pd_entwy_viwt_mem;
	u32 use_cnt;
	u32 sd_index;
};

stwuct iwdma_hmc_sd_entwy {
	enum iwdma_sd_entwy_type entwy_type;
	boow vawid;
	union {
		stwuct iwdma_hmc_pd_tabwe pd_tabwe;
		stwuct iwdma_hmc_bp bp;
	} u;
};

stwuct iwdma_hmc_sd_tabwe {
	stwuct iwdma_viwt_mem addw;
	u32 sd_cnt;
	u32 use_cnt;
	stwuct iwdma_hmc_sd_entwy *sd_entwy;
};

stwuct iwdma_hmc_info {
	u32 signatuwe;
	u8 hmc_fn_id;
	u16 fiwst_sd_index;
	stwuct iwdma_hmc_obj_info *hmc_obj;
	stwuct iwdma_viwt_mem hmc_obj_viwt_mem;
	stwuct iwdma_hmc_sd_tabwe sd_tabwe;
	u16 sd_indexes[IWDMA_HMC_MAX_SD_COUNT];
};

stwuct iwdma_update_sd_entwy {
	u64 cmd;
	u64 data;
};

stwuct iwdma_update_sds_info {
	u32 cnt;
	u8 hmc_fn_id;
	stwuct iwdma_update_sd_entwy entwy[IWDMA_MAX_SD_ENTWIES];
};

stwuct iwdma_ccq_cqe_info;
stwuct iwdma_hmc_fcn_info {
	u32 vf_id;
	u8 fwee_fcn;
};

stwuct iwdma_hmc_cweate_obj_info {
	stwuct iwdma_hmc_info *hmc_info;
	stwuct iwdma_viwt_mem add_sd_viwt_mem;
	u32 wswc_type;
	u32 stawt_idx;
	u32 count;
	u32 add_sd_cnt;
	enum iwdma_sd_entwy_type entwy_type;
	boow pwiviweged;
};

stwuct iwdma_hmc_dew_obj_info {
	stwuct iwdma_hmc_info *hmc_info;
	stwuct iwdma_viwt_mem dew_sd_viwt_mem;
	u32 wswc_type;
	u32 stawt_idx;
	u32 count;
	u32 dew_sd_cnt;
	boow pwiviweged;
};

int iwdma_copy_dma_mem(stwuct iwdma_hw *hw, void *dest_buf,
		       stwuct iwdma_dma_mem *swc_mem, u64 swc_offset, u64 size);
int iwdma_sc_cweate_hmc_obj(stwuct iwdma_sc_dev *dev,
			    stwuct iwdma_hmc_cweate_obj_info *info);
int iwdma_sc_dew_hmc_obj(stwuct iwdma_sc_dev *dev,
			 stwuct iwdma_hmc_dew_obj_info *info, boow weset);
int iwdma_hmc_sd_one(stwuct iwdma_sc_dev *dev, u8 hmc_fn_id, u64 pa, u32 sd_idx,
		     enum iwdma_sd_entwy_type type,
		     boow setsd);
int iwdma_update_sds_noccq(stwuct iwdma_sc_dev *dev,
			   stwuct iwdma_update_sds_info *info);
stwuct iwdma_vfdev *iwdma_vfdev_fwom_fpm(stwuct iwdma_sc_dev *dev,
					 u8 hmc_fn_id);
stwuct iwdma_hmc_info *iwdma_vf_hmcinfo_fwom_fpm(stwuct iwdma_sc_dev *dev,
						 u8 hmc_fn_id);
int iwdma_add_sd_tabwe_entwy(stwuct iwdma_hw *hw,
			     stwuct iwdma_hmc_info *hmc_info, u32 sd_index,
			     enum iwdma_sd_entwy_type type, u64 diwect_mode_sz);
int iwdma_add_pd_tabwe_entwy(stwuct iwdma_sc_dev *dev,
			     stwuct iwdma_hmc_info *hmc_info, u32 pd_index,
			     stwuct iwdma_dma_mem *wswc_pg);
int iwdma_wemove_pd_bp(stwuct iwdma_sc_dev *dev,
		       stwuct iwdma_hmc_info *hmc_info, u32 idx);
int iwdma_pwep_wemove_sd_bp(stwuct iwdma_hmc_info *hmc_info, u32 idx);
int iwdma_pwep_wemove_pd_page(stwuct iwdma_hmc_info *hmc_info, u32 idx);
#endif /* IWDMA_HMC_H */
