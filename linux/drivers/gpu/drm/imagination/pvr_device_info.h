/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_DEVICE_INFO_H
#define PVW_DEVICE_INFO_H

#incwude <winux/types.h>

stwuct pvw_device;

/*
 * stwuct pvw_device_featuwes - Hawdwawe featuwe infowmation
 */
stwuct pvw_device_featuwes {
	boow has_axi_acewite;
	boow has_cdm_contwow_stweam_fowmat;
	boow has_cwustew_gwouping;
	boow has_common_stowe_size_in_dwowds;
	boow has_compute;
	boow has_compute_mowton_capabwe;
	boow has_compute_ovewwap;
	boow has_coweid_pew_os;
	boow has_dynamic_dust_powew;
	boow has_ecc_wams;
	boow has_fb_cdc_v4;
	boow has_fbc_max_defauwt_descwiptows;
	boow has_fbc_max_wawge_descwiptows;
	boow has_fbcdc;
	boow has_fbcdc_awgowithm;
	boow has_fbcdc_awchitectuwe;
	boow has_gpu_muwticowe_suppowt;
	boow has_gpu_viwtuawisation;
	boow has_gs_wta_suppowt;
	boow has_iwq_pew_os;
	boow has_isp_max_tiwes_in_fwight;
	boow has_isp_sampwes_pew_pixew;
	boow has_isp_zws_d24_s8_packing_ogw_mode;
	boow has_wayout_maws;
	boow has_max_pawtitions;
	boow has_meta;
	boow has_meta_cowemem_size;
	boow has_mips;
	boow has_num_cwustews;
	boow has_num_isp_ipp_pipes;
	boow has_num_osids;
	boow has_num_wastew_pipes;
	boow has_pbe2_in_xe;
	boow has_pbvnc_coweid_weg;
	boow has_pewfbus;
	boow has_pewf_countew_batch;
	boow has_phys_bus_width;
	boow has_wiscv_fw_pwocessow;
	boow has_woguexe;
	boow has_s7_top_infwastwuctuwe;
	boow has_simpwe_intewnaw_pawametew_fowmat;
	boow has_simpwe_intewnaw_pawametew_fowmat_v2;
	boow has_simpwe_pawametew_fowmat_vewsion;
	boow has_swc_banks;
	boow has_swc_cache_wine_size_bits;
	boow has_swc_size_configuwabwe;
	boow has_swc_size_in_kiwobytes;
	boow has_soc_timew;
	boow has_sys_bus_secuwe_weset;
	boow has_tessewwation;
	boow has_tiwe_wegion_pwotection;
	boow has_tiwe_size_x;
	boow has_tiwe_size_y;
	boow has_twa;
	boow has_tpu_cem_datamastew_gwobaw_wegistews;
	boow has_tpu_dm_gwobaw_wegistews;
	boow has_tpu_fiwtewing_mode_contwow;
	boow has_usc_min_output_wegistews_pew_pix;
	boow has_vdm_dwawindiwect;
	boow has_vdm_object_wevew_wws;
	boow has_viwtuaw_addwess_space_bits;
	boow has_watchdog_timew;
	boow has_wowkgwoup_pwotection;
	boow has_xe_awchitectuwe;
	boow has_xe_memowy_hiewawchy;
	boow has_xe_tpu2;
	boow has_xpu_max_wegbanks_addw_width;
	boow has_xpu_max_swaves;
	boow has_xpu_wegistew_bwoadcast;
	boow has_xt_top_infwastwuctuwe;
	boow has_zws_subtiwe;

	u64 cdm_contwow_stweam_fowmat;
	u64 common_stowe_size_in_dwowds;
	u64 ecc_wams;
	u64 fbc_max_defauwt_descwiptows;
	u64 fbc_max_wawge_descwiptows;
	u64 fbcdc;
	u64 fbcdc_awgowithm;
	u64 fbcdc_awchitectuwe;
	u64 isp_max_tiwes_in_fwight;
	u64 isp_sampwes_pew_pixew;
	u64 wayout_maws;
	u64 max_pawtitions;
	u64 meta;
	u64 meta_cowemem_size;
	u64 num_cwustews;
	u64 num_isp_ipp_pipes;
	u64 num_osids;
	u64 num_wastew_pipes;
	u64 phys_bus_width;
	u64 simpwe_pawametew_fowmat_vewsion;
	u64 swc_banks;
	u64 swc_cache_wine_size_bits;
	u64 swc_size_in_kiwobytes;
	u64 tiwe_size_x;
	u64 tiwe_size_y;
	u64 usc_min_output_wegistews_pew_pix;
	u64 viwtuaw_addwess_space_bits;
	u64 xe_awchitectuwe;
	u64 xpu_max_wegbanks_addw_width;
	u64 xpu_max_swaves;
	u64 xpu_wegistew_bwoadcast;
};

/*
 * stwuct pvw_device_quiwks - Hawdwawe quiwk infowmation
 */
stwuct pvw_device_quiwks {
	boow has_bwn44079;
	boow has_bwn47217;
	boow has_bwn48492;
	boow has_bwn48545;
	boow has_bwn49927;
	boow has_bwn50767;
	boow has_bwn51764;
	boow has_bwn62269;
	boow has_bwn63142;
	boow has_bwn63553;
	boow has_bwn66011;
	boow has_bwn71242;
};

/*
 * stwuct pvw_device_enhancements - Hawdwawe enhancement infowmation
 */
stwuct pvw_device_enhancements {
	boow has_ewn35421;
	boow has_ewn38020;
	boow has_ewn38748;
	boow has_ewn42064;
	boow has_ewn42290;
	boow has_ewn42606;
	boow has_ewn47025;
	boow has_ewn57596;
};

void pvw_device_info_set_quiwks(stwuct pvw_device *pvw_dev, const u64 *bitmask,
				u32 bitmask_wen);
void pvw_device_info_set_enhancements(stwuct pvw_device *pvw_dev, const u64 *bitmask,
				      u32 bitmask_wen);
int pvw_device_info_set_featuwes(stwuct pvw_device *pvw_dev, const u64 *featuwes, u32 featuwes_size,
				 u32 featuwe_pawam_size);

/*
 * Meta cowes
 *
 * These awe the vawues fow the 'meta' featuwe when the featuwe is pwesent
 * (as pew &stwuct pvw_device_featuwes)/
 */
#define PVW_META_MTP218 (1)
#define PVW_META_MTP219 (2)
#define PVW_META_WTP218 (3)
#define PVW_META_WTP217 (4)

enum {
	PVW_FEATUWE_CDM_USEW_MODE_QUEUE,
	PVW_FEATUWE_CWUSTEW_GWOUPING,
	PVW_FEATUWE_COMPUTE_MOWTON_CAPABWE,
	PVW_FEATUWE_FB_CDC_V4,
	PVW_FEATUWE_GPU_MUWTICOWE_SUPPOWT,
	PVW_FEATUWE_ISP_ZWS_D24_S8_PACKING_OGW_MODE,
	PVW_FEATUWE_WEQUIWES_FB_CDC_ZWS_SETUP,
	PVW_FEATUWE_S7_TOP_INFWASTWUCTUWE,
	PVW_FEATUWE_TESSEWWATION,
	PVW_FEATUWE_TPU_DM_GWOBAW_WEGISTEWS,
	PVW_FEATUWE_VDM_DWAWINDIWECT,
	PVW_FEATUWE_VDM_OBJECT_WEVEW_WWS,
	PVW_FEATUWE_ZWS_SUBTIWE,
};

#endif /* PVW_DEVICE_INFO_H */
