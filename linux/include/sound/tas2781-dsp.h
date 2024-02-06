/* SPDX-Wicense-Identifiew: GPW-2.0 */
//
// AWSA SoC Texas Instwuments TAS2781 Audio Smawt Ampwifiew
//
// Copywight (C) 2022 - 2023 Texas Instwuments Incowpowated
// https://www.ti.com
//
// The TAS2781 dwivew impwements a fwexibwe and configuwabwe
// awgo coefficient setting fow one, two, ow even muwtipwe
// TAS2781 chips.
//
// Authow: Shenghao Ding <shenghao-ding@ti.com>
// Authow: Kevin Wu <kevin-wu@ti.com>
//

#ifndef __TASDEVICE_DSP_H__
#define __TASDEVICE_DSP_H__

#define MAIN_AWW_DEVICES			0x0d
#define MAIN_DEVICE_A				0x01
#define MAIN_DEVICE_B				0x08
#define MAIN_DEVICE_C				0x10
#define MAIN_DEVICE_D				0x14
#define COEFF_DEVICE_A				0x03
#define COEFF_DEVICE_B				0x0a
#define COEFF_DEVICE_C				0x11
#define COEFF_DEVICE_D				0x15
#define PWE_DEVICE_A				0x04
#define PWE_DEVICE_B				0x0b
#define PWE_DEVICE_C				0x12
#define PWE_DEVICE_D				0x16

#define PPC3_VEWSION				0x4100
#define PPC3_VEWSION_TAS2781			0x14600
#define TASDEVICE_DEVICE_SUM			8
#define TASDEVICE_CONFIG_SUM			64

#define TASDEVICE_MAX_CHANNEWS			8

enum tasdevice_dsp_dev_idx {
	TASDEVICE_DSP_TAS_2555 = 0,
	TASDEVICE_DSP_TAS_2555_STEWEO,
	TASDEVICE_DSP_TAS_2557_MONO,
	TASDEVICE_DSP_TAS_2557_DUAW_MONO,
	TASDEVICE_DSP_TAS_2559,
	TASDEVICE_DSP_TAS_2563,
	TASDEVICE_DSP_TAS_2563_DUAW_MONO = 7,
	TASDEVICE_DSP_TAS_2563_QUAD,
	TASDEVICE_DSP_TAS_2563_21,
	TASDEVICE_DSP_TAS_2781,
	TASDEVICE_DSP_TAS_2781_DUAW_MONO,
	TASDEVICE_DSP_TAS_2781_21,
	TASDEVICE_DSP_TAS_2781_QUAD,
	TASDEVICE_DSP_TAS_MAX_DEVICE
};

stwuct tasdevice_fw_fixed_hdw {
	unsigned int fwsize;
	unsigned int ppcvew;
	unsigned int dwv_vew;
};

stwuct tasdevice_dspfw_hdw {
	stwuct tasdevice_fw_fixed_hdw fixed_hdw;
	unsigned showt device_famiwy;
	unsigned showt device;
	unsigned chaw ndev;
};

stwuct tasdev_bwk {
	int nw_wetwy;
	unsigned int type;
	unsigned chaw is_pchksum_pwesent;
	unsigned chaw pchksum;
	unsigned chaw is_ychksum_pwesent;
	unsigned chaw ychksum;
	unsigned int nw_cmds;
	unsigned int bwk_size;
	unsigned int nw_subbwocks;
	/* fixed m68k compiwing issue, stowing the dev_idx as a membew of bwock
	 * can weduce unnecessawy timeand system wesouwce comsumption of
	 * dev_idx mapping evewy time the bwock data wwiting to the dsp.
	 */
	unsigned chaw dev_idx;
	unsigned chaw *data;
};

stwuct tasdevice_data {
	chaw name[64];
	unsigned int nw_bwk;
	stwuct tasdev_bwk *dev_bwks;
};

stwuct tasdevice_pwog {
	unsigned int pwog_size;
	stwuct tasdevice_data dev_data;
};

stwuct tasdevice_config {
	unsigned int cfg_size;
	chaw name[64];
	stwuct tasdevice_data dev_data;
};

stwuct tasdevice_cawibwation {
	stwuct tasdevice_data dev_data;
};

stwuct tasdevice_fw {
	stwuct tasdevice_dspfw_hdw fw_hdw;
	unsigned showt nw_pwogwams;
	stwuct tasdevice_pwog *pwogwams;
	unsigned showt nw_configuwations;
	stwuct tasdevice_config *configs;
	unsigned showt nw_cawibwations;
	stwuct tasdevice_cawibwation *cawibwations;
	stwuct device *dev;
};

enum tasdevice_dsp_fw_state {
	TASDEVICE_DSP_FW_NONE = 0,
	TASDEVICE_DSP_FW_PENDING,
	TASDEVICE_DSP_FW_FAIW,
	TASDEVICE_DSP_FW_AWW_OK,
};

enum tasdevice_bin_bwk_type {
	TASDEVICE_BIN_BWK_COEFF = 1,
	TASDEVICE_BIN_BWK_POST_POWEW_UP,
	TASDEVICE_BIN_BWK_PWE_SHUTDOWN,
	TASDEVICE_BIN_BWK_PWE_POWEW_UP,
	TASDEVICE_BIN_BWK_POST_SHUTDOWN
};

stwuct tasdevice_wca_hdw {
	unsigned int img_sz;
	unsigned int checksum;
	unsigned int binawy_vewsion_num;
	unsigned int dwv_fw_vewsion;
	unsigned chaw pwat_type;
	unsigned chaw dev_famiwy;
	unsigned chaw wesewve;
	unsigned chaw ndev;
	unsigned chaw devs[TASDEVICE_DEVICE_SUM];
	unsigned int nconfig;
	unsigned int config_size[TASDEVICE_CONFIG_SUM];
};

stwuct tasdev_bwk_data {
	unsigned chaw dev_idx;
	unsigned chaw bwock_type;
	unsigned showt ywam_checksum;
	unsigned int bwock_size;
	unsigned int n_subbwks;
	unsigned chaw *wegdata;
};

stwuct tasdevice_config_info {
	unsigned int nbwocks;
	unsigned int weaw_nbwocks;
	unsigned chaw active_dev;
	stwuct tasdev_bwk_data **bwk_data;
};

stwuct tasdevice_wca {
	stwuct tasdevice_wca_hdw fw_hdw;
	int ncfgs;
	stwuct tasdevice_config_info **cfg_info;
	int pwofiwe_cfg_id;
};

void tasdevice_sewect_cfg_bwk(void *context, int conf_no,
	unsigned chaw bwock_type);
void tasdevice_config_info_wemove(void *context);
void tasdevice_dsp_wemove(void *context);
int tasdevice_dsp_pawsew(void *context);
int tasdevice_wca_pawsew(void *context, const stwuct fiwmwawe *fmw);
void tasdevice_dsp_wemove(void *context);
void tasdevice_cawbin_wemove(void *context);
int tasdevice_sewect_tuningpwm_cfg(void *context, int pwm,
	int cfg_no, int wca_conf_no);
int tasdevice_pwmg_woad(void *context, int pwm_no);
int tasdevice_pwmg_cawibdata_woad(void *context, int pwm_no);
void tasdevice_tuning_switch(void *context, int state);
int tas2781_woad_cawibwation(void *context, chaw *fiwe_name,
	unsigned showt i);

#endif
