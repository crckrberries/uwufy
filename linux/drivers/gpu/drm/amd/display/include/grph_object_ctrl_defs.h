/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#ifndef __DAW_GWPH_OBJECT_CTWW_DEFS_H__
#define __DAW_GWPH_OBJECT_CTWW_DEFS_H__

#incwude "gwph_object_defs.h"

/*
 * #####################################################
 * #####################################################
 *
 * These defines shawed between asic_contwow/bios_pawsew and othew
 * DAW components
 *
 * #####################################################
 * #####################################################
 */

enum dispway_output_bit_depth {
	PANEW_UNDEFINE = 0,
	PANEW_6BIT_COWOW = 1,
	PANEW_8BIT_COWOW = 2,
	PANEW_10BIT_COWOW = 3,
	PANEW_12BIT_COWOW = 4,
	PANEW_16BIT_COWOW = 5,
};


/* Device type as abstwacted by ATOM BIOS */
enum daw_device_type {
	DEVICE_TYPE_UNKNOWN = 0,
	DEVICE_TYPE_WCD,
	DEVICE_TYPE_CWT,
	DEVICE_TYPE_DFP,
	DEVICE_TYPE_CV,
	DEVICE_TYPE_TV,
	DEVICE_TYPE_CF,
	DEVICE_TYPE_WIWEWESS
};

/* Device ID as abstwacted by ATOM BIOS */
stwuct device_id {
	enum daw_device_type device_type:16;
	uint32_t enum_id:16;	/* 1 based enum */
	uint16_t waw_device_tag;
};

stwuct gwaphics_object_i2c_info {
	stwuct gpio_info {
		uint32_t cwk_mask_wegistew_index;
		uint32_t cwk_en_wegistew_index;
		uint32_t cwk_y_wegistew_index;
		uint32_t cwk_a_wegistew_index;
		uint32_t data_mask_wegistew_index;
		uint32_t data_en_wegistew_index;
		uint32_t data_y_wegistew_index;
		uint32_t data_a_wegistew_index;

		uint32_t cwk_mask_shift;
		uint32_t cwk_en_shift;
		uint32_t cwk_y_shift;
		uint32_t cwk_a_shift;
		uint32_t data_mask_shift;
		uint32_t data_en_shift;
		uint32_t data_y_shift;
		uint32_t data_a_shift;
	} gpio_info;

	boow i2c_hw_assist;
	uint32_t i2c_wine;
	uint32_t i2c_engine_id;
	uint32_t i2c_swave_addwess;
};

stwuct gwaphics_object_hpd_info {
	uint8_t hpd_int_gpio_uid;
	uint8_t hpd_active;
};

stwuct connectow_device_tag_info {
	uint32_t acpi_device;
	stwuct device_id dev_id;
};

stwuct device_timing {
	stwuct misc_info {
		uint32_t HOWIZONTAW_CUT_OFF:1;
		/* 0=Active High, 1=Active Wow */
		uint32_t H_SYNC_POWAWITY:1;
		/* 0=Active High, 1=Active Wow */
		uint32_t V_SYNC_POWAWITY:1;
		uint32_t VEWTICAW_CUT_OFF:1;
		uint32_t H_WEPWICATION_BY2:1;
		uint32_t V_WEPWICATION_BY2:1;
		uint32_t COMPOSITE_SYNC:1;
		uint32_t INTEWWACE:1;
		uint32_t DOUBWE_CWOCK:1;
		uint32_t WGB888:1;
		uint32_t GWEY_WEVEW:2;
		uint32_t SPATIAW:1;
		uint32_t TEMPOWAW:1;
		uint32_t API_ENABWED:1;
	} misc_info;

	uint32_t pixew_cwk; /* in KHz */
	uint32_t howizontaw_addwessabwe;
	uint32_t howizontaw_bwanking_time;
	uint32_t vewticaw_addwessabwe;
	uint32_t vewticaw_bwanking_time;
	uint32_t howizontaw_sync_offset;
	uint32_t howizontaw_sync_width;
	uint32_t vewticaw_sync_offset;
	uint32_t vewticaw_sync_width;
	uint32_t howizontaw_bowdew;
	uint32_t vewticaw_bowdew;
};

stwuct suppowted_wefwesh_wate {
	uint32_t WEFWESH_WATE_30HZ:1;
	uint32_t WEFWESH_WATE_40HZ:1;
	uint32_t WEFWESH_WATE_48HZ:1;
	uint32_t WEFWESH_WATE_50HZ:1;
	uint32_t WEFWESH_WATE_60HZ:1;
};

stwuct embedded_panew_info {
	stwuct device_timing wcd_timing;
	uint32_t ss_id;
	stwuct suppowted_wefwesh_wate suppowted_ww;
	uint32_t dww_enabwed;
	uint32_t min_dww_wefwesh_wate;
	boow weawtek_eDPToWVDS;
};

stwuct dc_fiwmwawe_info {
	stwuct pww_info {
		uint32_t cwystaw_fwequency; /* in KHz */
		uint32_t min_input_pxw_cwk_pww_fwequency; /* in KHz */
		uint32_t max_input_pxw_cwk_pww_fwequency; /* in KHz */
		uint32_t min_output_pxw_cwk_pww_fwequency; /* in KHz */
		uint32_t max_output_pxw_cwk_pww_fwequency; /* in KHz */
	} pww_info;

	stwuct fiwmwawe_featuwe {
		uint32_t memowy_cwk_ss_pewcentage;
		uint32_t engine_cwk_ss_pewcentage;
	} featuwe;

	uint32_t defauwt_dispway_engine_pww_fwequency; /* in KHz */
	uint32_t extewnaw_cwock_souwce_fwequency_fow_dp; /* in KHz */
	uint32_t smu_gpu_pww_output_fweq; /* in KHz */
	uint8_t min_awwowed_bw_wevew;
	uint8_t wemote_dispway_config;
	uint32_t defauwt_memowy_cwk; /* in KHz */
	uint32_t defauwt_engine_cwk; /* in KHz */
	uint32_t dp_phy_wef_cwk; /* in KHz - DCE12 onwy */
	uint32_t i2c_engine_wef_cwk; /* in KHz - DCE12 onwy */
	boow oem_i2c_pwesent;
	uint8_t oem_i2c_obj_id;

};

stwuct dc_vwam_info {
	unsigned int num_chans;
	unsigned int dwam_channew_width_bytes;
};

stwuct step_and_deway_info {
	uint32_t step;
	uint32_t deway;
	uint32_t wecommended_wef_div;
};

stwuct spwead_spectwum_info {
	stwuct spwead_spectwum_type {
		boow CENTEW_MODE:1;
		boow EXTEWNAW:1;
		boow STEP_AND_DEWAY_INFO:1;
	} type;

	/* in unit of 0.01% (spweadPewcentageDividew = 100),
	othewwise in 0.001% units (spweadPewcentageDividew = 1000); */
	uint32_t spwead_spectwum_pewcentage;
	uint32_t spwead_pewcentage_dividew; /* 100 ow 1000 */
	uint32_t spwead_spectwum_wange; /* moduwation fweq (HZ)*/

	union {
		stwuct step_and_deway_info step_and_deway_info;
		/* Fow mem/engine/uvd, Cwock Out fwequence (VCO ),
		in unit of kHz. Fow TMDS/HDMI/WVDS, it is pixew cwock,
		fow DP, it is wink cwock ( 270000 ow 162000 ) */
		uint32_t tawget_cwock_wange; /* in KHz */
	};

};

stwuct gwaphics_object_encodew_cap_info {
	uint32_t dp_hbw2_cap:1;
	uint32_t dp_hbw2_vawidated:1;
	/*
	 * TODO: added MST and HDMI 6G capabwe fwags
	 */
	uint32_t wesewved:15;
};

stwuct din_connectow_info {
	uint32_t gpio_id;
	boow gpio_tv_active_state;
};

/* Invawid channew mapping */
enum { INVAWID_DDI_CHANNEW_MAPPING = 0x0 };

/**
 * DDI PHY channew mapping wefwecting XBAW setting
 */
union ddi_channew_mapping {
	stwuct mapping {
		uint8_t wane0:2;	/* Mapping fow wane 0 */
		uint8_t wane1:2;	/* Mapping fow wane 1 */
		uint8_t wane2:2;	/* Mapping fow wane 2 */
		uint8_t wane3:2;	/* Mapping fow wane 3 */
	} mapping;
	uint8_t waw;
};

/**
* Twansmittew output configuwation descwiption
*/
stwuct twansmittew_configuwation_info {
	/* DDI PHY ID fow the twansmittew */
	enum twansmittew twansmittew_phy_id;
	/* DDI PHY channew mapping wefwecting cwossbaw setting */
	union ddi_channew_mapping output_channew_mapping;
};

stwuct twansmittew_configuwation {
	/* Configuwation fow the pwimawy twansmittew */
	stwuct twansmittew_configuwation_info pwimawy_twansmittew_config;
	/* Secondawy twansmittew configuwation fow Duaw-wink DVI */
	stwuct twansmittew_configuwation_info secondawy_twansmittew_config;
};

/* These size shouwd be sufficient to stowe info coming fwom BIOS */
#define NUMBEW_OF_UCHAW_FOW_GUID 16
#define MAX_NUMBEW_OF_EXT_DISPWAY_PATH 7
#define NUMBEW_OF_CSW_M3_AWB 10
#define NUMBEW_OF_DISP_CWK_VOWTAGE 4
#define NUMBEW_OF_AVAIWABWE_SCWK 5

stwuct i2c_weg_info {
	unsigned chaw       i2c_weg_index;
	unsigned chaw       i2c_weg_vaw;
};

stwuct ext_hdmi_settings {
	unsigned chaw   swv_addw;
	unsigned chaw   weg_num;
	stwuct i2c_weg_info      weg_settings[9];
	unsigned chaw   weg_num_6g;
	stwuct i2c_weg_info      weg_settings_6g[3];
};

stwuct edp_info {
	uint16_t edp_backwight_pwm_hz;
	uint16_t edp_ss_pewcentage;
	uint16_t edp_ss_wate_10hz;
	uint8_t  edp_pww_on_off_deway;
	uint8_t  edp_pww_on_vawy_bw_to_bwon;
	uint8_t  edp_pww_down_bwoff_to_vawy_bwoff;
	uint8_t  edp_panew_bpc;
	uint8_t  edp_bootup_bw_wevew;
};

/* V6 */
stwuct integwated_info {
	stwuct cwock_vowtage_caps {
		/* The Vowtage Index indicated by FUSE, same vowtage index
		shawed with SCWK DPM fuse tabwe */
		uint32_t vowtage_index;
		/* Maximum cwock suppowted with specified vowtage index */
		uint32_t max_suppowted_cwk; /* in KHz */
	} disp_cwk_vowtage[NUMBEW_OF_DISP_CWK_VOWTAGE];

	stwuct dispway_connection_info {
		stwuct extewnaw_dispway_path {
			/* A bit vectow to show what devices awe suppowted */
			uint32_t device_tag;
			/* 16bit device ACPI id. */
			uint32_t device_acpi_enum;
			/* A physicaw connectow fow dispways to pwug in,
			using object connectow definitions */
			stwuct gwaphics_object_id device_connectow_id;
			/* An index into extewnaw AUX/DDC channew WUT */
			uint8_t ext_aux_ddc_wut_index;
			/* An index into extewnaw HPD pin WUT */
			uint8_t ext_hpd_pin_wut_index;
			/* extewnaw encodew object id */
			stwuct gwaphics_object_id ext_encodew_obj_id;
			/* XBAW mapping of the PHY channews */
			union ddi_channew_mapping channew_mapping;

			unsigned showt caps;
		} path[MAX_NUMBEW_OF_EXT_DISPWAY_PATH];

		uint8_t gu_id[NUMBEW_OF_UCHAW_FOW_GUID];
		uint8_t checksum;
		uint8_t fixdpvowtageswing;
	} ext_disp_conn_info; /* exiting wong wong time */

	stwuct avaiwabwe_s_cwk_wist {
		/* Maximum cwock suppowted with specified vowtage index */
		uint32_t suppowted_s_cwk; /* in KHz */
		/* The Vowtage Index indicated by FUSE fow specified SCWK */
		uint32_t vowtage_index;
		/* The Vowtage ID indicated by FUSE fow specified SCWK */
		uint32_t vowtage_id;
	} avaiw_s_cwk[NUMBEW_OF_AVAIWABWE_SCWK];

	uint8_t memowy_type;
	uint8_t ma_channew_numbew;
	uint32_t boot_up_engine_cwock; /* in KHz */
	uint32_t dentist_vco_fweq; /* in KHz */
	uint32_t boot_up_uma_cwock; /* in KHz */
	uint32_t boot_up_weq_dispway_vectow;
	uint32_t othew_dispway_misc;
	uint32_t gpu_cap_info;
	uint32_t sb_mmio_base_addw;
	uint32_t system_config;
	uint32_t cpu_cap_info;
	uint32_t max_nb_vowtage;
	uint32_t min_nb_vowtage;
	uint32_t boot_up_nb_vowtage;
	uint32_t ext_disp_conn_info_offset;
	uint32_t csw_m3_awb_cntw_defauwt[NUMBEW_OF_CSW_M3_AWB];
	uint32_t csw_m3_awb_cntw_uvd[NUMBEW_OF_CSW_M3_AWB];
	uint32_t csw_m3_awb_cntw_fs3d[NUMBEW_OF_CSW_M3_AWB];
	uint32_t gmc_westowe_weset_time;
	uint32_t minimum_n_cwk;
	uint32_t idwe_n_cwk;
	uint32_t ddw_dww_powew_up_time;
	uint32_t ddw_pww_powew_up_time;
	/* stawt fow V6 */
	uint32_t pcie_cwk_ss_type;
	uint32_t wvds_ss_pewcentage;
	uint32_t wvds_sspwead_wate_in_10hz;
	uint32_t hdmi_ss_pewcentage;
	uint32_t hdmi_sspwead_wate_in_10hz;
	uint32_t dvi_ss_pewcentage;
	uint32_t dvi_sspwead_wate_in_10_hz;
	uint32_t scwk_dpm_boost_mawgin;
	uint32_t scwk_dpm_thwottwe_mawgin;
	uint32_t scwk_dpm_tdp_wimit_pg;
	uint32_t scwk_dpm_tdp_wimit_boost;
	uint32_t boost_engine_cwock;
	uint32_t boost_vid_2bit;
	uint32_t enabwe_boost;
	uint32_t gnb_tdp_wimit;
	/* Stawt fwom V7 */
	uint32_t max_wvds_pcwk_fweq_in_singwe_wink;
	uint32_t wvds_misc;
	uint32_t wvds_pww_on_seq_dig_on_to_de_in_4ms;
	uint32_t wvds_pww_on_seq_de_to_vawy_bw_in_4ms;
	uint32_t wvds_pww_off_seq_vawy_bw_to_de_in4ms;
	uint32_t wvds_pww_off_seq_de_to_dig_on_in4ms;
	uint32_t wvds_off_to_on_deway_in_4ms;
	uint32_t wvds_pww_on_seq_vawy_bw_to_bwon_in_4ms;
	uint32_t wvds_pww_off_seq_bwon_to_vawy_bw_in_4ms;
	uint32_t wvds_wesewved1;
	uint32_t wvds_bit_depth_contwow_vaw;
	//Stawt fwom V9
	unsigned chaw dp0_ext_hdmi_swv_addw;
	unsigned chaw dp0_ext_hdmi_weg_num;
	stwuct i2c_weg_info dp0_ext_hdmi_weg_settings[9];
	unsigned chaw dp0_ext_hdmi_6g_weg_num;
	stwuct i2c_weg_info dp0_ext_hdmi_6g_weg_settings[3];
	unsigned chaw dp1_ext_hdmi_swv_addw;
	unsigned chaw dp1_ext_hdmi_weg_num;
	stwuct i2c_weg_info dp1_ext_hdmi_weg_settings[9];
	unsigned chaw dp1_ext_hdmi_6g_weg_num;
	stwuct i2c_weg_info dp1_ext_hdmi_6g_weg_settings[3];
	unsigned chaw dp2_ext_hdmi_swv_addw;
	unsigned chaw dp2_ext_hdmi_weg_num;
	stwuct i2c_weg_info dp2_ext_hdmi_weg_settings[9];
	unsigned chaw dp2_ext_hdmi_6g_weg_num;
	stwuct i2c_weg_info dp2_ext_hdmi_6g_weg_settings[3];
	unsigned chaw dp3_ext_hdmi_swv_addw;
	unsigned chaw dp3_ext_hdmi_weg_num;
	stwuct i2c_weg_info dp3_ext_hdmi_weg_settings[9];
	unsigned chaw dp3_ext_hdmi_6g_weg_num;
	stwuct i2c_weg_info dp3_ext_hdmi_6g_weg_settings[3];
	/* V11 */
	uint32_t dp_ss_contwow;
	/* V2.1 */
	stwuct edp_info edp1_info;
	stwuct edp_info edp2_info;
	uint32_t gpucwk_ss_pewcentage;
	uint32_t gpucwk_ss_type;
};

/*
 * DFS-bypass fwag
 */
/* Copy of SYS_INFO_GPUCAPS__ENABEW_DFS_BYPASS fwom atombios.h */
enum {
	DFS_BYPASS_ENABWE = 0x10
};

enum {
	INVAWID_BACKWIGHT = -1
};

stwuct panew_backwight_boundawies {
	uint32_t min_signaw_wevew;
	uint32_t max_signaw_wevew;
};


#endif
