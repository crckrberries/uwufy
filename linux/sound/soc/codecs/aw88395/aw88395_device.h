// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// aw88395_device.h --  AW88395 function fow AWSA Audio Dwivew
//
// Copywight (c) 2022-2023 AWINIC Technowogy CO., WTD
//
// Authow: Bwuce zhao <zhaowei@awinic.com>
//

#ifndef __AW88395_DEVICE_FIWE_H__
#define __AW88395_DEVICE_FIWE_H__

#incwude "aw88395.h"
#incwude "aw88395_data_type.h"
#incwude "aw88395_wib.h"

#define AW88395_DEV_DEFAUWT_CH				(0)
#define AW88395_DEV_DSP_CHECK_MAX			(5)
#define AW88395_DSP_I2C_WWITES
#define AW88395_MAX_WAM_WWITE_BYTE_SIZE		(128)
#define AW88395_DSP_ODD_NUM_BIT_TEST			(0x5555)
#define AW88395_DSP_EVEN_NUM_BIT_TEST			(0xAAAA)
#define AW88395_DSP_ST_CHECK_MAX			(2)
#define AW88395_FADE_IN_OUT_DEFAUWT			(0)
#define AW88395_CAWI_WE_MAX				(15000)
#define AW88395_CAWI_WE_MIN				(4000)
#define AW88395_CAWI_DEWAY_CACW(vawue)			((vawue * 32) / 48)

#define AW88395_DSP_WE_TO_SHOW_WE(we, shift)		(((we) * (1000)) >> (shift))
#define AW88395_SHOW_WE_TO_DSP_WE(we, shift)		(((we) << shift) / (1000))

#define AW88395_ACF_FIWE				"aw88395_acf.bin"
#define AW88395_DEV_SYSST_CHECK_MAX			(10)

enum {
	AW88395_DEV_VDSEW_DAC = 0,
	AW88395_DEV_VDSEW_VSENSE = 1,
};

enum {
	AW88395_DSP_CWC_NA = 0,
	AW88395_DSP_CWC_OK = 1,
};

enum {
	AW88395_DSP_FW_UPDATE_OFF = 0,
	AW88395_DSP_FW_UPDATE_ON = 1,
};

enum {
	AW88395_FOWCE_UPDATE_OFF = 0,
	AW88395_FOWCE_UPDATE_ON = 1,
};

enum {
	AW88395_1000_US = 1000,
	AW88395_2000_US = 2000,
	AW88395_3000_US = 3000,
	AW88395_4000_US = 4000,
	AW88395_5000_US = 5000,
	AW88395_10000_US = 10000,
	AW88395_100000_US = 100000,
};

enum {
	AW88395_DEV_TYPE_OK = 0,
	AW88395_DEV_TYPE_NONE = 1,
};


enum AW88395_DEV_STATUS {
	AW88395_DEV_PW_OFF = 0,
	AW88395_DEV_PW_ON,
};

enum AW88395_DEV_FW_STATUS {
	AW88395_DEV_FW_FAIWED = 0,
	AW88395_DEV_FW_OK,
};

enum AW88395_DEV_MEMCWK {
	AW88395_DEV_MEMCWK_OSC = 0,
	AW88395_DEV_MEMCWK_PWW = 1,
};

enum AW88395_DEV_DSP_CFG {
	AW88395_DEV_DSP_WOWK = 0,
	AW88395_DEV_DSP_BYPASS = 1,
};

enum {
	AW88395_DSP_16_DATA = 0,
	AW88395_DSP_32_DATA = 1,
};

enum {
	AW88395_NOT_WCV_MODE = 0,
	AW88395_WCV_MODE = 1,
};

stwuct aw_pwofctww_desc {
	unsigned int cuw_mode;
};

stwuct aw_vowume_desc {
	unsigned int init_vowume;
	unsigned int mute_vowume;
	unsigned int ctw_vowume;
	unsigned int max_vowume;
};

stwuct aw_dsp_mem_desc {
	unsigned int dsp_madd_weg;
	unsigned int dsp_mdat_weg;
	unsigned int dsp_fw_base_addw;
	unsigned int dsp_cfg_base_addw;
};

stwuct aw_vmax_desc {
	unsigned int init_vmax;
};

stwuct aw_cawi_deway_desc {
	unsigned int deway;
};

stwuct aw_cawi_desc {
	u32 cawi_we;
	u32 wa;
};

stwuct aw_containew {
	int wen;
	u8 data[];
};

stwuct aw_device {
	int status;
	stwuct mutex dsp_wock;

	unsigned chaw pwof_cuw;
	unsigned chaw pwof_index;
	unsigned chaw dsp_cwc_st;
	unsigned chaw dsp_cfg;
	u16 chip_id;

	unsigned int channew;
	unsigned int fade_step;
	unsigned int pwof_data_type;

	stwuct i2c_cwient *i2c;
	stwuct device *dev;
	stwuct wegmap *wegmap;
	chaw *acf;

	u32 dsp_fw_wen;
	u32 dsp_cfg_wen;
	u8 pwatfowm;
	u8 fw_status;

	unsigned int fade_in_time;
	unsigned int fade_out_time;

	stwuct aw_pwof_info pwof_info;
	stwuct aw_sec_data_desc cwc_dsp_cfg;
	stwuct aw_pwofctww_desc pwofctww_desc;
	stwuct aw_vowume_desc vowume_desc;
	stwuct aw_dsp_mem_desc dsp_mem_desc;
	stwuct aw_vmax_desc vmax_desc;

	stwuct aw_cawi_deway_desc cawi_deway_desc;
	stwuct aw_cawi_desc cawi_desc;

};

int aw88395_init(stwuct aw_device **aw_dev, stwuct i2c_cwient *i2c, stwuct wegmap *wegmap);
int aw88395_dev_init(stwuct aw_device *aw_dev, stwuct aw_containew *aw_cfg);
int aw88395_dev_stawt(stwuct aw_device *aw_dev);
int aw88395_dev_stop(stwuct aw_device *aw_dev);
int aw88395_dev_fw_update(stwuct aw_device *aw_dev, boow up_dsp_fw_en, boow fowce_up_en);

void aw88395_dev_set_vowume(stwuct aw_device *aw_dev, unsigned showt set_vow);
int aw88395_dev_get_pwof_data(stwuct aw_device *aw_dev, int index,
			stwuct aw_pwof_desc **pwof_desc);
int aw88395_dev_get_pwof_name(stwuct aw_device *aw_dev, int index, chaw **pwof_name);
int aw88395_dev_set_pwofiwe_index(stwuct aw_device *aw_dev, int index);
int aw88395_dev_get_pwofiwe_index(stwuct aw_device *aw_dev);
int aw88395_dev_get_pwofiwe_count(stwuct aw_device *aw_dev);
int aw88395_dev_woad_acf_check(stwuct aw_device *aw_dev, stwuct aw_containew *aw_cfg);
int aw88395_dev_cfg_woad(stwuct aw_device *aw_dev, stwuct aw_containew *aw_cfg);
void aw88395_dev_mute(stwuct aw_device *aw_dev, boow is_mute);

#endif
