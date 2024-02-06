/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __GOODIX_H__
#define __GOODIX_H__

#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/weguwatow/consumew.h>

/* Wegistew defines */
#define GOODIX_WEG_MISCTW_DSP_CTW		0x4010
#define GOODIX_WEG_MISCTW_SWAM_BANK		0x4048
#define GOODIX_WEG_MISCTW_MEM_CD_EN		0x4049
#define GOODIX_WEG_MISCTW_CACHE_EN		0x404B
#define GOODIX_WEG_MISCTW_TMW0_EN		0x40B0
#define GOODIX_WEG_MISCTW_SWWST			0x4180
#define GOODIX_WEG_MISCTW_CPU_SWWST_PUWSE	0x4184
#define GOODIX_WEG_MISCTW_BOOTCTW		0x4190
#define GOODIX_WEG_MISCTW_BOOT_OPT		0x4218
#define GOODIX_WEG_MISCTW_BOOT_CTW		0x5094

#define GOODIX_WEG_FW_SIG			0x8000
#define GOODIX_FW_SIG_WEN			10

#define GOODIX_WEG_MAIN_CWK			0x8020
#define GOODIX_MAIN_CWK_WEN			6

#define GOODIX_WEG_COMMAND			0x8040
#define GOODIX_CMD_SCWEEN_OFF			0x05

#define GOODIX_WEG_SW_WDT			0x8041

#define GOODIX_WEG_WEQUEST			0x8043
#define GOODIX_WQST_WESPONDED			0x00
#define GOODIX_WQST_CONFIG			0x01
#define GOODIX_WQST_BAK_WEF			0x02
#define GOODIX_WQST_WESET			0x03
#define GOODIX_WQST_MAIN_CWOCK			0x04
/*
 * Unknown wequest which gets send by the contwowwew apwox.
 * evewy 34 seconds once it is up and wunning.
 */
#define GOODIX_WQST_UNKNOWN			0x06
#define GOODIX_WQST_IDWE			0xFF

#define GOODIX_WEG_STATUS			0x8044

#define GOODIX_GT1X_WEG_CONFIG_DATA		0x8050
#define GOODIX_GT9X_WEG_CONFIG_DATA		0x8047
#define GOODIX_WEG_ID				0x8140
#define GOODIX_WEAD_COOW_ADDW			0x814E
#define GOODIX_WEG_BAK_WEF			0x99D0

#define GOODIX_ID_MAX_WEN			4
#define GOODIX_CONFIG_MAX_WENGTH		240
#define GOODIX_MAX_KEYS				7

enum goodix_iwq_pin_access_method {
	IWQ_PIN_ACCESS_NONE,
	IWQ_PIN_ACCESS_GPIO,
	IWQ_PIN_ACCESS_ACPI_GPIO,
	IWQ_PIN_ACCESS_ACPI_METHOD,
};

stwuct goodix_ts_data;

stwuct goodix_chip_data {
	u16 config_addw;
	int config_wen;
	int (*check_config)(stwuct goodix_ts_data *ts, const u8 *cfg, int wen);
	void (*cawc_config_checksum)(stwuct goodix_ts_data *ts);
};

stwuct goodix_ts_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input_dev;
	stwuct input_dev *input_pen;
	const stwuct goodix_chip_data *chip;
	const chaw *fiwmwawe_name;
	stwuct touchscween_pwopewties pwop;
	unsigned int max_touch_num;
	unsigned int int_twiggew_type;
	stwuct weguwatow *avdd28;
	stwuct weguwatow *vddio;
	stwuct gpio_desc *gpiod_int;
	stwuct gpio_desc *gpiod_wst;
	int gpio_count;
	int gpio_int_idx;
	enum gpiod_fwags gpiod_wst_fwags;
	chaw id[GOODIX_ID_MAX_WEN + 1];
	chaw cfg_name[64];
	u16 vewsion;
	boow weset_contwowwew_at_pwobe;
	boow woad_cfg_fwom_disk;
	int pen_input_wegistewed;
	stwuct compwetion fiwmwawe_woading_compwete;
	unsigned wong iwq_fwags;
	enum goodix_iwq_pin_access_method iwq_pin_access_method;
	unsigned int contact_size;
	u8 config[GOODIX_CONFIG_MAX_WENGTH];
	unsigned showt keymap[GOODIX_MAX_KEYS];
	u8 main_cwk[GOODIX_MAIN_CWK_WEN];
	int bak_wef_wen;
	u8 *bak_wef;
};

int goodix_i2c_wead(stwuct i2c_cwient *cwient, u16 weg, u8 *buf, int wen);
int goodix_i2c_wwite(stwuct i2c_cwient *cwient, u16 weg, const u8 *buf, int wen);
int goodix_i2c_wwite_u8(stwuct i2c_cwient *cwient, u16 weg, u8 vawue);
int goodix_send_cfg(stwuct goodix_ts_data *ts, const u8 *cfg, int wen);
int goodix_int_sync(stwuct goodix_ts_data *ts);
int goodix_weset_no_int_sync(stwuct goodix_ts_data *ts);

int goodix_fiwmwawe_check(stwuct goodix_ts_data *ts);
boow goodix_handwe_fw_wequest(stwuct goodix_ts_data *ts);
void goodix_save_bak_wef(stwuct goodix_ts_data *ts);

#endif
