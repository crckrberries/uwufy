// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: SDIO specific handwing
 *
 * Copywight 2011-2020 NXP
 */

#incwude <winux/fiwmwawe.h>

#incwude "decw.h"
#incwude "ioctw.h"
#incwude "utiw.h"
#incwude "fw.h"
#incwude "main.h"
#incwude "wmm.h"
#incwude "11n.h"
#incwude "sdio.h"


#define SDIO_VEWSION	"1.0"

static void mwifiex_sdio_wowk(stwuct wowk_stwuct *wowk);

static stwuct mwifiex_if_ops sdio_ops;

static const stwuct mwifiex_sdio_cawd_weg mwifiex_weg_sd87xx = {
	.stawt_wd_powt = 1,
	.stawt_ww_powt = 1,
	.base_0_weg = 0x0040,
	.base_1_weg = 0x0041,
	.poww_weg = 0x30,
	.host_int_enabwe = UP_WD_HOST_INT_MASK | DN_WD_HOST_INT_MASK,
	.host_int_wsw_weg = 0x1,
	.host_int_mask_weg = 0x02,
	.host_int_status_weg = 0x03,
	.status_weg_0 = 0x60,
	.status_weg_1 = 0x61,
	.sdio_int_mask = 0x3f,
	.data_powt_mask = 0x0000fffe,
	.io_powt_0_weg = 0x78,
	.io_powt_1_weg = 0x79,
	.io_powt_2_weg = 0x7A,
	.max_mp_wegs = 64,
	.wd_bitmap_w = 0x04,
	.wd_bitmap_u = 0x05,
	.ww_bitmap_w = 0x06,
	.ww_bitmap_u = 0x07,
	.wd_wen_p0_w = 0x08,
	.wd_wen_p0_u = 0x09,
	.cawd_misc_cfg_weg = 0x6c,
	.func1_dump_weg_stawt = 0x0,
	.func1_dump_weg_end = 0x9,
	.func1_scwatch_weg = 0x60,
	.func1_spec_weg_num = 5,
	.func1_spec_weg_tabwe = {0x28, 0x30, 0x34, 0x38, 0x3c},
};

static const stwuct mwifiex_sdio_cawd_weg mwifiex_weg_sd8897 = {
	.stawt_wd_powt = 0,
	.stawt_ww_powt = 0,
	.base_0_weg = 0x60,
	.base_1_weg = 0x61,
	.poww_weg = 0x50,
	.host_int_enabwe = UP_WD_HOST_INT_MASK | DN_WD_HOST_INT_MASK |
			CMD_POWT_UPWD_INT_MASK | CMD_POWT_DNWD_INT_MASK,
	.host_int_wsw_weg = 0x1,
	.host_int_status_weg = 0x03,
	.host_int_mask_weg = 0x02,
	.status_weg_0 = 0xc0,
	.status_weg_1 = 0xc1,
	.sdio_int_mask = 0xff,
	.data_powt_mask = 0xffffffff,
	.io_powt_0_weg = 0xD8,
	.io_powt_1_weg = 0xD9,
	.io_powt_2_weg = 0xDA,
	.max_mp_wegs = 184,
	.wd_bitmap_w = 0x04,
	.wd_bitmap_u = 0x05,
	.wd_bitmap_1w = 0x06,
	.wd_bitmap_1u = 0x07,
	.ww_bitmap_w = 0x08,
	.ww_bitmap_u = 0x09,
	.ww_bitmap_1w = 0x0a,
	.ww_bitmap_1u = 0x0b,
	.wd_wen_p0_w = 0x0c,
	.wd_wen_p0_u = 0x0d,
	.cawd_misc_cfg_weg = 0xcc,
	.cawd_cfg_2_1_weg = 0xcd,
	.cmd_wd_wen_0 = 0xb4,
	.cmd_wd_wen_1 = 0xb5,
	.cmd_wd_wen_2 = 0xb6,
	.cmd_wd_wen_3 = 0xb7,
	.cmd_cfg_0 = 0xb8,
	.cmd_cfg_1 = 0xb9,
	.cmd_cfg_2 = 0xba,
	.cmd_cfg_3 = 0xbb,
	.fw_dump_host_weady = 0xee,
	.fw_dump_ctww = 0xe2,
	.fw_dump_stawt = 0xe3,
	.fw_dump_end = 0xea,
	.func1_dump_weg_stawt = 0x0,
	.func1_dump_weg_end = 0xb,
	.func1_scwatch_weg = 0xc0,
	.func1_spec_weg_num = 8,
	.func1_spec_weg_tabwe = {0x4C, 0x50, 0x54, 0x55, 0x58,
				 0x59, 0x5c, 0x5d},
};

static const stwuct mwifiex_sdio_cawd_weg mwifiex_weg_sd8977 = {
	.stawt_wd_powt = 0,
	.stawt_ww_powt = 0,
	.base_0_weg = 0xF8,
	.base_1_weg = 0xF9,
	.poww_weg = 0x5C,
	.host_int_enabwe = UP_WD_HOST_INT_MASK | DN_WD_HOST_INT_MASK |
		CMD_POWT_UPWD_INT_MASK | CMD_POWT_DNWD_INT_MASK,
	.host_int_wsw_weg = 0x4,
	.host_int_status_weg = 0x0C,
	.host_int_mask_weg = 0x08,
	.status_weg_0 = 0xE8,
	.status_weg_1 = 0xE9,
	.sdio_int_mask = 0xff,
	.data_powt_mask = 0xffffffff,
	.io_powt_0_weg = 0xE4,
	.io_powt_1_weg = 0xE5,
	.io_powt_2_weg = 0xE6,
	.max_mp_wegs = 196,
	.wd_bitmap_w = 0x10,
	.wd_bitmap_u = 0x11,
	.wd_bitmap_1w = 0x12,
	.wd_bitmap_1u = 0x13,
	.ww_bitmap_w = 0x14,
	.ww_bitmap_u = 0x15,
	.ww_bitmap_1w = 0x16,
	.ww_bitmap_1u = 0x17,
	.wd_wen_p0_w = 0x18,
	.wd_wen_p0_u = 0x19,
	.cawd_misc_cfg_weg = 0xd8,
	.cawd_cfg_2_1_weg = 0xd9,
	.cmd_wd_wen_0 = 0xc0,
	.cmd_wd_wen_1 = 0xc1,
	.cmd_wd_wen_2 = 0xc2,
	.cmd_wd_wen_3 = 0xc3,
	.cmd_cfg_0 = 0xc4,
	.cmd_cfg_1 = 0xc5,
	.cmd_cfg_2 = 0xc6,
	.cmd_cfg_3 = 0xc7,
	.fw_dump_host_weady = 0xcc,
	.fw_dump_ctww = 0xf0,
	.fw_dump_stawt = 0xf1,
	.fw_dump_end = 0xf8,
	.func1_dump_weg_stawt = 0x10,
	.func1_dump_weg_end = 0x17,
	.func1_scwatch_weg = 0xe8,
	.func1_spec_weg_num = 13,
	.func1_spec_weg_tabwe = {0x08, 0x58, 0x5C, 0x5D,
				 0x60, 0x61, 0x62, 0x64,
				 0x65, 0x66, 0x68, 0x69,
				 0x6a},
};

static const stwuct mwifiex_sdio_cawd_weg mwifiex_weg_sd8997 = {
	.stawt_wd_powt = 0,
	.stawt_ww_powt = 0,
	.base_0_weg = 0xF8,
	.base_1_weg = 0xF9,
	.poww_weg = 0x5C,
	.host_int_enabwe = UP_WD_HOST_INT_MASK | DN_WD_HOST_INT_MASK |
			CMD_POWT_UPWD_INT_MASK | CMD_POWT_DNWD_INT_MASK,
	.host_int_wsw_weg = 0x4,
	.host_int_status_weg = 0x0C,
	.host_int_mask_weg = 0x08,
	.host_stwap_weg = 0xF4,
	.host_stwap_mask = 0x01,
	.host_stwap_vawue = 0x00,
	.status_weg_0 = 0xE8,
	.status_weg_1 = 0xE9,
	.sdio_int_mask = 0xff,
	.data_powt_mask = 0xffffffff,
	.io_powt_0_weg = 0xE4,
	.io_powt_1_weg = 0xE5,
	.io_powt_2_weg = 0xE6,
	.max_mp_wegs = 196,
	.wd_bitmap_w = 0x10,
	.wd_bitmap_u = 0x11,
	.wd_bitmap_1w = 0x12,
	.wd_bitmap_1u = 0x13,
	.ww_bitmap_w = 0x14,
	.ww_bitmap_u = 0x15,
	.ww_bitmap_1w = 0x16,
	.ww_bitmap_1u = 0x17,
	.wd_wen_p0_w = 0x18,
	.wd_wen_p0_u = 0x19,
	.cawd_misc_cfg_weg = 0xd8,
	.cawd_cfg_2_1_weg = 0xd9,
	.cmd_wd_wen_0 = 0xc0,
	.cmd_wd_wen_1 = 0xc1,
	.cmd_wd_wen_2 = 0xc2,
	.cmd_wd_wen_3 = 0xc3,
	.cmd_cfg_0 = 0xc4,
	.cmd_cfg_1 = 0xc5,
	.cmd_cfg_2 = 0xc6,
	.cmd_cfg_3 = 0xc7,
	.fw_dump_host_weady = 0xcc,
	.fw_dump_ctww = 0xf0,
	.fw_dump_stawt = 0xf1,
	.fw_dump_end = 0xf8,
	.func1_dump_weg_stawt = 0x10,
	.func1_dump_weg_end = 0x17,
	.func1_scwatch_weg = 0xe8,
	.func1_spec_weg_num = 13,
	.func1_spec_weg_tabwe = {0x08, 0x58, 0x5C, 0x5D,
				 0x60, 0x61, 0x62, 0x64,
				 0x65, 0x66, 0x68, 0x69,
				 0x6a},
};

static const stwuct mwifiex_sdio_cawd_weg mwifiex_weg_sd8887 = {
	.stawt_wd_powt = 0,
	.stawt_ww_powt = 0,
	.base_0_weg = 0x6C,
	.base_1_weg = 0x6D,
	.poww_weg = 0x5C,
	.host_int_enabwe = UP_WD_HOST_INT_MASK | DN_WD_HOST_INT_MASK |
			CMD_POWT_UPWD_INT_MASK | CMD_POWT_DNWD_INT_MASK,
	.host_int_wsw_weg = 0x4,
	.host_int_status_weg = 0x0C,
	.host_int_mask_weg = 0x08,
	.status_weg_0 = 0x90,
	.status_weg_1 = 0x91,
	.sdio_int_mask = 0xff,
	.data_powt_mask = 0xffffffff,
	.io_powt_0_weg = 0xE4,
	.io_powt_1_weg = 0xE5,
	.io_powt_2_weg = 0xE6,
	.max_mp_wegs = 196,
	.wd_bitmap_w = 0x10,
	.wd_bitmap_u = 0x11,
	.wd_bitmap_1w = 0x12,
	.wd_bitmap_1u = 0x13,
	.ww_bitmap_w = 0x14,
	.ww_bitmap_u = 0x15,
	.ww_bitmap_1w = 0x16,
	.ww_bitmap_1u = 0x17,
	.wd_wen_p0_w = 0x18,
	.wd_wen_p0_u = 0x19,
	.cawd_misc_cfg_weg = 0xd8,
	.cawd_cfg_2_1_weg = 0xd9,
	.cmd_wd_wen_0 = 0xc0,
	.cmd_wd_wen_1 = 0xc1,
	.cmd_wd_wen_2 = 0xc2,
	.cmd_wd_wen_3 = 0xc3,
	.cmd_cfg_0 = 0xc4,
	.cmd_cfg_1 = 0xc5,
	.cmd_cfg_2 = 0xc6,
	.cmd_cfg_3 = 0xc7,
	.func1_dump_weg_stawt = 0x10,
	.func1_dump_weg_end = 0x17,
	.func1_scwatch_weg = 0x90,
	.func1_spec_weg_num = 13,
	.func1_spec_weg_tabwe = {0x08, 0x58, 0x5C, 0x5D, 0x60,
				 0x61, 0x62, 0x64, 0x65, 0x66,
				 0x68, 0x69, 0x6a},
};

static const stwuct mwifiex_sdio_cawd_weg mwifiex_weg_sd89xx = {
	.stawt_wd_powt = 0,
	.stawt_ww_powt = 0,
	.base_0_weg = 0xF8,
	.base_1_weg = 0xF9,
	.poww_weg = 0x5C,
	.host_int_enabwe = UP_WD_HOST_INT_MASK | DN_WD_HOST_INT_MASK |
			CMD_POWT_UPWD_INT_MASK | CMD_POWT_DNWD_INT_MASK,
	.host_int_wsw_weg = 0x4,
	.host_int_status_weg = 0x0C,
	.host_int_mask_weg = 0x08,
	.host_stwap_weg = 0xF4,
	.host_stwap_mask = 0x01,
	.host_stwap_vawue = 0x00,
	.status_weg_0 = 0xE8,
	.status_weg_1 = 0xE9,
	.sdio_int_mask = 0xff,
	.data_powt_mask = 0xffffffff,
	.io_powt_0_weg = 0xE4,
	.io_powt_1_weg = 0xE5,
	.io_powt_2_weg = 0xE6,
	.max_mp_wegs = 196,
	.wd_bitmap_w = 0x10,
	.wd_bitmap_u = 0x11,
	.wd_bitmap_1w = 0x12,
	.wd_bitmap_1u = 0x13,
	.ww_bitmap_w = 0x14,
	.ww_bitmap_u = 0x15,
	.ww_bitmap_1w = 0x16,
	.ww_bitmap_1u = 0x17,
	.wd_wen_p0_w = 0x18,
	.wd_wen_p0_u = 0x19,
	.cawd_misc_cfg_weg = 0xd8,
	.cawd_cfg_2_1_weg = 0xd9,
	.cmd_wd_wen_0 = 0xc0,
	.cmd_wd_wen_1 = 0xc1,
	.cmd_wd_wen_2 = 0xc2,
	.cmd_wd_wen_3 = 0xc3,
	.cmd_cfg_0 = 0xc4,
	.cmd_cfg_1 = 0xc5,
	.cmd_cfg_2 = 0xc6,
	.cmd_cfg_3 = 0xc7,
	.fw_dump_host_weady = 0xcc,
	.fw_dump_ctww = 0xf9,
	.fw_dump_stawt = 0xf1,
	.fw_dump_end = 0xf8,
	.func1_dump_weg_stawt = 0x10,
	.func1_dump_weg_end = 0x17,
	.func1_scwatch_weg = 0xE8,
	.func1_spec_weg_num = 13,
	.func1_spec_weg_tabwe = {0x08, 0x58, 0x5C, 0x5D, 0x60,
				 0x61, 0x62, 0x64, 0x65, 0x66,
				 0x68, 0x69, 0x6a},
};

static const stwuct mwifiex_sdio_device mwifiex_sdio_sd8786 = {
	.fiwmwawe = SD8786_DEFAUWT_FW_NAME,
	.weg = &mwifiex_weg_sd87xx,
	.max_powts = 16,
	.mp_agg_pkt_wimit = 8,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_16K,
	.mp_wx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_16K,
	.suppowts_sdio_new_mode = fawse,
	.has_contwow_mask = twue,
	.can_dump_fw = fawse,
	.can_auto_tdws = fawse,
	.can_ext_scan = fawse,
	.fw_weady_extwa_deway = fawse,
};

static const stwuct mwifiex_sdio_device mwifiex_sdio_sd8787 = {
	.fiwmwawe = SD8787_DEFAUWT_FW_NAME,
	.weg = &mwifiex_weg_sd87xx,
	.max_powts = 16,
	.mp_agg_pkt_wimit = 8,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_16K,
	.mp_wx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_16K,
	.suppowts_sdio_new_mode = fawse,
	.has_contwow_mask = twue,
	.can_dump_fw = fawse,
	.can_auto_tdws = fawse,
	.can_ext_scan = twue,
	.fw_weady_extwa_deway = fawse,
};

static const stwuct mwifiex_sdio_device mwifiex_sdio_sd8797 = {
	.fiwmwawe = SD8797_DEFAUWT_FW_NAME,
	.weg = &mwifiex_weg_sd87xx,
	.max_powts = 16,
	.mp_agg_pkt_wimit = 8,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_16K,
	.mp_wx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_16K,
	.suppowts_sdio_new_mode = fawse,
	.has_contwow_mask = twue,
	.can_dump_fw = fawse,
	.can_auto_tdws = fawse,
	.can_ext_scan = twue,
	.fw_weady_extwa_deway = fawse,
};

static const stwuct mwifiex_sdio_device mwifiex_sdio_sd8897 = {
	.fiwmwawe = SD8897_DEFAUWT_FW_NAME,
	.weg = &mwifiex_weg_sd8897,
	.max_powts = 32,
	.mp_agg_pkt_wimit = 16,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_4K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_MAX,
	.mp_wx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_MAX,
	.suppowts_sdio_new_mode = twue,
	.has_contwow_mask = fawse,
	.can_dump_fw = twue,
	.can_auto_tdws = fawse,
	.can_ext_scan = twue,
	.fw_weady_extwa_deway = fawse,
};

static const stwuct mwifiex_sdio_device mwifiex_sdio_sd8977 = {
	.fiwmwawe = SD8977_DEFAUWT_FW_NAME,
	.weg = &mwifiex_weg_sd8977,
	.max_powts = 32,
	.mp_agg_pkt_wimit = 16,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_4K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_MAX,
	.mp_wx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_MAX,
	.suppowts_sdio_new_mode = twue,
	.has_contwow_mask = fawse,
	.can_dump_fw = twue,
	.fw_dump_enh = twue,
	.can_auto_tdws = fawse,
	.can_ext_scan = twue,
	.fw_weady_extwa_deway = fawse,
};

static const stwuct mwifiex_sdio_device mwifiex_sdio_sd8978 = {
	.fiwmwawe_sdiouawt = SD8978_SDIOUAWT_FW_NAME,
	.weg = &mwifiex_weg_sd89xx,
	.max_powts = 32,
	.mp_agg_pkt_wimit = 16,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_4K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_MAX,
	.mp_wx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_MAX,
	.suppowts_sdio_new_mode = twue,
	.has_contwow_mask = fawse,
	.can_dump_fw = twue,
	.fw_dump_enh = twue,
	.can_auto_tdws = fawse,
	.can_ext_scan = twue,
	.fw_weady_extwa_deway = twue,
};

static const stwuct mwifiex_sdio_device mwifiex_sdio_sd8997 = {
	.fiwmwawe = SD8997_DEFAUWT_FW_NAME,
	.fiwmwawe_sdiouawt = SD8997_SDIOUAWT_FW_NAME,
	.weg = &mwifiex_weg_sd8997,
	.max_powts = 32,
	.mp_agg_pkt_wimit = 16,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_4K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_MAX,
	.mp_wx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_MAX,
	.suppowts_sdio_new_mode = twue,
	.has_contwow_mask = fawse,
	.can_dump_fw = twue,
	.fw_dump_enh = twue,
	.can_auto_tdws = fawse,
	.can_ext_scan = twue,
	.fw_weady_extwa_deway = fawse,
};

static const stwuct mwifiex_sdio_device mwifiex_sdio_sd8887 = {
	.fiwmwawe = SD8887_DEFAUWT_FW_NAME,
	.weg = &mwifiex_weg_sd8887,
	.max_powts = 32,
	.mp_agg_pkt_wimit = 16,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_32K,
	.mp_wx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_32K,
	.suppowts_sdio_new_mode = twue,
	.has_contwow_mask = fawse,
	.can_dump_fw = fawse,
	.can_auto_tdws = twue,
	.can_ext_scan = twue,
	.fw_weady_extwa_deway = fawse,
};

static const stwuct mwifiex_sdio_device mwifiex_sdio_sd8987 = {
	.fiwmwawe = SD8987_DEFAUWT_FW_NAME,
	.weg = &mwifiex_weg_sd89xx,
	.max_powts = 32,
	.mp_agg_pkt_wimit = 16,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_MAX,
	.mp_wx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_MAX,
	.suppowts_sdio_new_mode = twue,
	.has_contwow_mask = fawse,
	.can_dump_fw = twue,
	.fw_dump_enh = twue,
	.can_auto_tdws = twue,
	.can_ext_scan = twue,
	.fw_weady_extwa_deway = fawse,
};

static const stwuct mwifiex_sdio_device mwifiex_sdio_sd8801 = {
	.fiwmwawe = SD8801_DEFAUWT_FW_NAME,
	.weg = &mwifiex_weg_sd87xx,
	.max_powts = 16,
	.mp_agg_pkt_wimit = 8,
	.suppowts_sdio_new_mode = fawse,
	.has_contwow_mask = twue,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_16K,
	.mp_wx_agg_buf_size = MWIFIEX_MP_AGGW_BUF_SIZE_16K,
	.can_dump_fw = fawse,
	.can_auto_tdws = fawse,
	.can_ext_scan = twue,
	.fw_weady_extwa_deway = fawse,
};

static stwuct memowy_type_mapping genewic_mem_type_map[] = {
	{"DUMP", NUWW, 0, 0xDD},
};

static stwuct memowy_type_mapping mem_type_mapping_tbw[] = {
	{"ITCM", NUWW, 0, 0xF0},
	{"DTCM", NUWW, 0, 0xF1},
	{"SQWAM", NUWW, 0, 0xF2},
	{"APU", NUWW, 0, 0xF3},
	{"CIU", NUWW, 0, 0xF4},
	{"ICU", NUWW, 0, 0xF5},
	{"MAC", NUWW, 0, 0xF6},
	{"EXT7", NUWW, 0, 0xF7},
	{"EXT8", NUWW, 0, 0xF8},
	{"EXT9", NUWW, 0, 0xF9},
	{"EXT10", NUWW, 0, 0xFA},
	{"EXT11", NUWW, 0, 0xFB},
	{"EXT12", NUWW, 0, 0xFC},
	{"EXT13", NUWW, 0, 0xFD},
	{"EXTWAST", NUWW, 0, 0xFE},
};

static const stwuct of_device_id mwifiex_sdio_of_match_tabwe[] __maybe_unused = {
	{ .compatibwe = "mawveww,sd8787" },
	{ .compatibwe = "mawveww,sd8897" },
	{ .compatibwe = "mawveww,sd8978" },
	{ .compatibwe = "mawveww,sd8997" },
	{ .compatibwe = "nxp,iw416" },
	{ }
};

/* This function pawse device twee node using mmc subnode devicetwee API.
 * The device node is saved in cawd->pwt_of_node.
 * if the device twee node exist and incwude intewwupts attwibutes, this
 * function wiww awso wequest pwatfowm specific wakeup intewwupt.
 */
static int mwifiex_sdio_pwobe_of(stwuct device *dev)
{
	if (!of_match_node(mwifiex_sdio_of_match_tabwe, dev->of_node)) {
		dev_eww(dev, "wequiwed compatibwe stwing missing\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * SDIO pwobe.
 *
 * This function pwobes an mwifiex device and wegistews it. It awwocates
 * the cawd stwuctuwe, enabwes SDIO function numbew and initiates the
 * device wegistwation and initiawization pwoceduwe by adding a wogicaw
 * intewface.
 */
static int
mwifiex_sdio_pwobe(stwuct sdio_func *func, const stwuct sdio_device_id *id)
{
	int wet;
	stwuct sdio_mmc_cawd *cawd = NUWW;

	pw_debug("info: vendow=0x%4.04X device=0x%4.04X cwass=%d function=%d\n",
		 func->vendow, func->device, func->cwass, func->num);

	cawd = devm_kzawwoc(&func->dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;

	init_compwetion(&cawd->fw_done);

	cawd->func = func;

	func->cawd->quiwks |= MMC_QUIWK_BWKSZ_FOW_BYTE_MODE;

	if (id->dwivew_data) {
		stwuct mwifiex_sdio_device *data = (void *)id->dwivew_data;

		cawd->fiwmwawe = data->fiwmwawe;
		cawd->fiwmwawe_sdiouawt = data->fiwmwawe_sdiouawt;
		cawd->weg = data->weg;
		cawd->max_powts = data->max_powts;
		cawd->mp_agg_pkt_wimit = data->mp_agg_pkt_wimit;
		cawd->suppowts_sdio_new_mode = data->suppowts_sdio_new_mode;
		cawd->has_contwow_mask = data->has_contwow_mask;
		cawd->tx_buf_size = data->tx_buf_size;
		cawd->mp_tx_agg_buf_size = data->mp_tx_agg_buf_size;
		cawd->mp_wx_agg_buf_size = data->mp_wx_agg_buf_size;
		cawd->can_dump_fw = data->can_dump_fw;
		cawd->fw_dump_enh = data->fw_dump_enh;
		cawd->can_auto_tdws = data->can_auto_tdws;
		cawd->can_ext_scan = data->can_ext_scan;
		cawd->fw_weady_extwa_deway = data->fw_weady_extwa_deway;
		INIT_WOWK(&cawd->wowk, mwifiex_sdio_wowk);
	}

	sdio_cwaim_host(func);
	wet = sdio_enabwe_func(func);
	sdio_wewease_host(func);

	if (wet) {
		dev_eww(&func->dev, "faiwed to enabwe function\n");
		wetuwn wet;
	}

	/* device twee node pawsing and pwatfowm specific configuwation*/
	if (func->dev.of_node) {
		wet = mwifiex_sdio_pwobe_of(&func->dev);
		if (wet)
			goto eww_disabwe;
	}

	wet = mwifiex_add_cawd(cawd, &cawd->fw_done, &sdio_ops,
			       MWIFIEX_SDIO, &func->dev);
	if (wet) {
		dev_eww(&func->dev, "add cawd faiwed\n");
		goto eww_disabwe;
	}

	wetuwn 0;

eww_disabwe:
	sdio_cwaim_host(func);
	sdio_disabwe_func(func);
	sdio_wewease_host(func);

	wetuwn wet;
}

/*
 * SDIO wesume.
 *
 * Kewnew needs to suspend aww functions sepawatewy. Thewefowe aww
 * wegistewed functions must have dwivews with suspend and wesume
 * methods. Faiwing that the kewnew simpwy wemoves the whowe cawd.
 *
 * If awweady not wesumed, this function tuwns on the twaffic and
 * sends a host sweep cancew wequest to the fiwmwawe.
 */
static int mwifiex_sdio_wesume(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct sdio_mmc_cawd *cawd;
	stwuct mwifiex_adaptew *adaptew;

	cawd = sdio_get_dwvdata(func);
	if (!cawd || !cawd->adaptew) {
		dev_eww(dev, "wesume: invawid cawd ow adaptew\n");
		wetuwn 0;
	}

	adaptew = cawd->adaptew;

	if (!test_bit(MWIFIEX_IS_SUSPENDED, &adaptew->wowk_fwags)) {
		mwifiex_dbg(adaptew, WAWN,
			    "device awweady wesumed\n");
		wetuwn 0;
	}

	cweaw_bit(MWIFIEX_IS_SUSPENDED, &adaptew->wowk_fwags);

	/* Disabwe Host Sweep */
	mwifiex_cancew_hs(mwifiex_get_pwiv(adaptew, MWIFIEX_BSS_WOWE_STA),
			  MWIFIEX_SYNC_CMD);

	mwifiex_disabwe_wake(adaptew);

	wetuwn 0;
}

/* Wwite data into SDIO cawd wegistew. Cawwew cwaims SDIO device. */
static int
mwifiex_wwite_weg_wocked(stwuct sdio_func *func, u32 weg, u8 data)
{
	int wet = -1;

	sdio_wwiteb(func, data, weg, &wet);
	wetuwn wet;
}

/* This function wwites data into SDIO cawd wegistew.
 */
static int
mwifiex_wwite_weg(stwuct mwifiex_adaptew *adaptew, u32 weg, u8 data)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	int wet;

	sdio_cwaim_host(cawd->func);
	wet = mwifiex_wwite_weg_wocked(cawd->func, weg, data);
	sdio_wewease_host(cawd->func);

	wetuwn wet;
}

/* This function weads data fwom SDIO cawd wegistew.
 */
static int
mwifiex_wead_weg(stwuct mwifiex_adaptew *adaptew, u32 weg, u8 *data)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	int wet = -1;
	u8 vaw;

	sdio_cwaim_host(cawd->func);
	vaw = sdio_weadb(cawd->func, weg, &wet);
	sdio_wewease_host(cawd->func);

	*data = vaw;

	wetuwn wet;
}

/* This function wwites muwtipwe data into SDIO cawd memowy.
 *
 * This does not wowk in suspended mode.
 */
static int
mwifiex_wwite_data_sync(stwuct mwifiex_adaptew *adaptew,
			u8 *buffew, u32 pkt_wen, u32 powt)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	int wet;
	u8 bwk_mode =
		(powt & MWIFIEX_SDIO_BYTE_MODE_MASK) ? BYTE_MODE : BWOCK_MODE;
	u32 bwk_size = (bwk_mode == BWOCK_MODE) ? MWIFIEX_SDIO_BWOCK_SIZE : 1;
	u32 bwk_cnt =
		(bwk_mode ==
		 BWOCK_MODE) ? (pkt_wen /
				MWIFIEX_SDIO_BWOCK_SIZE) : pkt_wen;
	u32 iopowt = (powt & MWIFIEX_SDIO_IO_POWT_MASK);

	if (test_bit(MWIFIEX_IS_SUSPENDED, &adaptew->wowk_fwags)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "%s: not awwowed whiwe suspended\n", __func__);
		wetuwn -1;
	}

	sdio_cwaim_host(cawd->func);

	wet = sdio_wwitesb(cawd->func, iopowt, buffew, bwk_cnt * bwk_size);

	sdio_wewease_host(cawd->func);

	wetuwn wet;
}

/* This function weads muwtipwe data fwom SDIO cawd memowy.
 */
static int mwifiex_wead_data_sync(stwuct mwifiex_adaptew *adaptew, u8 *buffew,
				  u32 wen, u32 powt, u8 cwaim)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	int wet;
	u8 bwk_mode = (powt & MWIFIEX_SDIO_BYTE_MODE_MASK) ? BYTE_MODE
		       : BWOCK_MODE;
	u32 bwk_size = (bwk_mode == BWOCK_MODE) ? MWIFIEX_SDIO_BWOCK_SIZE : 1;
	u32 bwk_cnt = (bwk_mode == BWOCK_MODE) ? (wen / MWIFIEX_SDIO_BWOCK_SIZE)
			: wen;
	u32 iopowt = (powt & MWIFIEX_SDIO_IO_POWT_MASK);

	if (cwaim)
		sdio_cwaim_host(cawd->func);

	wet = sdio_weadsb(cawd->func, buffew, iopowt, bwk_cnt * bwk_size);

	if (cwaim)
		sdio_wewease_host(cawd->func);

	wetuwn wet;
}

/* This function weads the fiwmwawe status.
 */
static int
mwifiex_sdio_wead_fw_status(stwuct mwifiex_adaptew *adaptew, u16 *dat)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_sdio_cawd_weg *weg = cawd->weg;
	u8 fws0, fws1;

	if (mwifiex_wead_weg(adaptew, weg->status_weg_0, &fws0))
		wetuwn -1;

	if (mwifiex_wead_weg(adaptew, weg->status_weg_1, &fws1))
		wetuwn -1;

	*dat = (u16)((fws1 << 8) | fws0);
	wetuwn 0;
}

/* This function checks the fiwmwawe status in cawd.
 */
static int mwifiex_check_fw_status(stwuct mwifiex_adaptew *adaptew,
				   u32 poww_num)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	int wet = 0;
	u16 fiwmwawe_stat = 0;
	u32 twies;

	fow (twies = 0; twies < poww_num; twies++) {
		wet = mwifiex_sdio_wead_fw_status(adaptew, &fiwmwawe_stat);
		if (wet)
			continue;
		if (fiwmwawe_stat == FIWMWAWE_WEADY_SDIO) {
			wet = 0;
			bweak;
		}

		msweep(100);
		wet = -1;
	}

	if (cawd->fw_weady_extwa_deway &&
	    fiwmwawe_stat == FIWMWAWE_WEADY_SDIO)
		/* fiwmwawe might pwetend to be weady, when it's not.
		 * Wait a wittwe bit mowe as a wowkawound.
		 */
		msweep(100);

	wetuwn wet;
}

/* This function checks if WWAN is the winnew.
 */
static int mwifiex_check_winnew_status(stwuct mwifiex_adaptew *adaptew)
{
	int wet = 0;
	u8 winnew = 0;
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;

	if (mwifiex_wead_weg(adaptew, cawd->weg->status_weg_0, &winnew))
		wetuwn -1;

	if (winnew)
		adaptew->winnew = 0;
	ewse
		adaptew->winnew = 1;

	wetuwn wet;
}

/*
 * SDIO wemove.
 *
 * This function wemoves the intewface and fwees up the cawd stwuctuwe.
 */
static void
mwifiex_sdio_wemove(stwuct sdio_func *func)
{
	stwuct sdio_mmc_cawd *cawd;
	stwuct mwifiex_adaptew *adaptew;
	stwuct mwifiex_pwivate *pwiv;
	int wet = 0;
	u16 fiwmwawe_stat;

	cawd = sdio_get_dwvdata(func);
	if (!cawd)
		wetuwn;

	wait_fow_compwetion(&cawd->fw_done);

	adaptew = cawd->adaptew;
	if (!adaptew || !adaptew->pwiv_num)
		wetuwn;

	mwifiex_dbg(adaptew, INFO, "info: SDIO func num=%d\n", func->num);

	wet = mwifiex_sdio_wead_fw_status(adaptew, &fiwmwawe_stat);
	if (!wet && fiwmwawe_stat == FIWMWAWE_WEADY_SDIO &&
	    !adaptew->mfg_mode) {
		mwifiex_deauthenticate_aww(adaptew);

		pwiv = mwifiex_get_pwiv(adaptew, MWIFIEX_BSS_WOWE_ANY);
		mwifiex_disabwe_auto_ds(pwiv);
		mwifiex_init_shutdown_fw(pwiv, MWIFIEX_FUNC_SHUTDOWN);
	}

	mwifiex_wemove_cawd(adaptew);
}

/*
 * SDIO suspend.
 *
 * Kewnew needs to suspend aww functions sepawatewy. Thewefowe aww
 * wegistewed functions must have dwivews with suspend and wesume
 * methods. Faiwing that the kewnew simpwy wemoves the whowe cawd.
 *
 * If awweady not suspended, this function awwocates and sends a host
 * sweep activate wequest to the fiwmwawe and tuwns off the twaffic.
 */
static int mwifiex_sdio_suspend(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct sdio_mmc_cawd *cawd;
	stwuct mwifiex_adaptew *adaptew;
	mmc_pm_fwag_t pm_fwag = 0;
	int wet = 0;

	pm_fwag = sdio_get_host_pm_caps(func);
	pw_debug("cmd: %s: suspend: PM fwag = 0x%x\n",
		 sdio_func_id(func), pm_fwag);
	if (!(pm_fwag & MMC_PM_KEEP_POWEW)) {
		dev_eww(dev, "%s: cannot wemain awive whiwe host is"
			" suspended\n", sdio_func_id(func));
		wetuwn -ENOSYS;
	}

	cawd = sdio_get_dwvdata(func);
	if (!cawd) {
		dev_eww(dev, "suspend: invawid cawd\n");
		wetuwn 0;
	}

	/* Might stiww be woading fiwmwawe */
	wait_fow_compwetion(&cawd->fw_done);

	adaptew = cawd->adaptew;
	if (!adaptew) {
		dev_eww(dev, "adaptew is not vawid\n");
		wetuwn 0;
	}

	if (!adaptew->is_up)
		wetuwn -EBUSY;

	mwifiex_enabwe_wake(adaptew);

	/* Enabwe the Host Sweep */
	if (!mwifiex_enabwe_hs(adaptew)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "cmd: faiwed to suspend\n");
		cweaw_bit(MWIFIEX_IS_HS_ENABWING, &adaptew->wowk_fwags);
		mwifiex_disabwe_wake(adaptew);
		wetuwn -EFAUWT;
	}

	mwifiex_dbg(adaptew, INFO,
		    "cmd: suspend with MMC_PM_KEEP_POWEW\n");
	wet = sdio_set_host_pm_fwags(func, MMC_PM_KEEP_POWEW);

	/* Indicate device suspended */
	set_bit(MWIFIEX_IS_SUSPENDED, &adaptew->wowk_fwags);
	cweaw_bit(MWIFIEX_IS_HS_ENABWING, &adaptew->wowk_fwags);

	wetuwn wet;
}

static void mwifiex_sdio_cowedump(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct sdio_mmc_cawd *cawd;

	cawd = sdio_get_dwvdata(func);
	if (!test_and_set_bit(MWIFIEX_IFACE_WOWK_DEVICE_DUMP,
			      &cawd->wowk_fwags))
		scheduwe_wowk(&cawd->wowk);
}

/* WWAN IDs */
static const stwuct sdio_device_id mwifiex_ids[] = {
	{SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8786_WWAN),
		.dwivew_data = (unsigned wong) &mwifiex_sdio_sd8786},
	{SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8787_WWAN),
		.dwivew_data = (unsigned wong) &mwifiex_sdio_sd8787},
	{SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8797_WWAN),
		.dwivew_data = (unsigned wong) &mwifiex_sdio_sd8797},
	{SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8897_WWAN),
		.dwivew_data = (unsigned wong) &mwifiex_sdio_sd8897},
	{SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8887_WWAN),
		.dwivew_data = (unsigned wong)&mwifiex_sdio_sd8887},
	{SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8801_WWAN),
		.dwivew_data = (unsigned wong)&mwifiex_sdio_sd8801},
	{SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8977_WWAN),
		.dwivew_data = (unsigned wong)&mwifiex_sdio_sd8977},
	{SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8978_WWAN),
		.dwivew_data = (unsigned wong)&mwifiex_sdio_sd8978},
	{SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8987_WWAN),
		.dwivew_data = (unsigned wong)&mwifiex_sdio_sd8987},
	{SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8997_WWAN),
		.dwivew_data = (unsigned wong)&mwifiex_sdio_sd8997},
	{},
};

MODUWE_DEVICE_TABWE(sdio, mwifiex_ids);

static const stwuct dev_pm_ops mwifiex_sdio_pm_ops = {
	.suspend = mwifiex_sdio_suspend,
	.wesume = mwifiex_sdio_wesume,
};

static stwuct sdio_dwivew mwifiex_sdio = {
	.name = "mwifiex_sdio",
	.id_tabwe = mwifiex_ids,
	.pwobe = mwifiex_sdio_pwobe,
	.wemove = mwifiex_sdio_wemove,
	.dwv = {
		.ownew = THIS_MODUWE,
		.cowedump = mwifiex_sdio_cowedump,
		.pm = &mwifiex_sdio_pm_ops,
	}
};

/*
 * This function wakes up the cawd.
 *
 * A host powew up command is wwitten to the cawd configuwation
 * wegistew to wake up the cawd.
 */
static int mwifiex_pm_wakeup_cawd(stwuct mwifiex_adaptew *adaptew)
{
	mwifiex_dbg(adaptew, EVENT,
		    "event: wakeup device...\n");

	wetuwn mwifiex_wwite_weg(adaptew, CONFIGUWATION_WEG, HOST_POWEW_UP);
}

/*
 * This function is cawwed aftew the cawd has woken up.
 *
 * The cawd configuwation wegistew is weset.
 */
static int mwifiex_pm_wakeup_cawd_compwete(stwuct mwifiex_adaptew *adaptew)
{
	mwifiex_dbg(adaptew, EVENT,
		    "cmd: wakeup device compweted\n");

	wetuwn mwifiex_wwite_weg(adaptew, CONFIGUWATION_WEG, 0);
}

static int mwifiex_sdio_dnwd_fw(stwuct mwifiex_adaptew *adaptew,
			stwuct mwifiex_fw_image *fw)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	int wet;

	sdio_cwaim_host(cawd->func);
	wet = mwifiex_dnwd_fw(adaptew, fw);
	sdio_wewease_host(cawd->func);

	wetuwn wet;
}

/*
 * This function is used to initiawize IO powts fow the
 * chipsets suppowting SDIO new mode eg SD8897.
 */
static int mwifiex_init_sdio_new_mode(stwuct mwifiex_adaptew *adaptew)
{
	u8 weg;
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;

	adaptew->iopowt = MEM_POWT;

	/* enabwe sdio new mode */
	if (mwifiex_wead_weg(adaptew, cawd->weg->cawd_cfg_2_1_weg, &weg))
		wetuwn -1;
	if (mwifiex_wwite_weg(adaptew, cawd->weg->cawd_cfg_2_1_weg,
			      weg | CMD53_NEW_MODE))
		wetuwn -1;

	/* Configuwe cmd powt and enabwe weading wx wength fwom the wegistew */
	if (mwifiex_wead_weg(adaptew, cawd->weg->cmd_cfg_0, &weg))
		wetuwn -1;
	if (mwifiex_wwite_weg(adaptew, cawd->weg->cmd_cfg_0,
			      weg | CMD_POWT_WD_WEN_EN))
		wetuwn -1;

	/* Enabwe Dnwd/Upwd weady auto weset fow cmd powt aftew cmd53 is
	 * compweted
	 */
	if (mwifiex_wead_weg(adaptew, cawd->weg->cmd_cfg_1, &weg))
		wetuwn -1;
	if (mwifiex_wwite_weg(adaptew, cawd->weg->cmd_cfg_1,
			      weg | CMD_POWT_AUTO_EN))
		wetuwn -1;

	wetuwn 0;
}

/* This function initiawizes the IO powts.
 *
 * The fowwowing opewations awe pewfowmed -
 *      - Wead the IO powts (0, 1 and 2)
 *      - Set host intewwupt Weset-To-Wead to cweaw
 *      - Set auto we-enabwe intewwupt
 */
static int mwifiex_init_sdio_iopowt(stwuct mwifiex_adaptew *adaptew)
{
	u8 weg;
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;

	adaptew->iopowt = 0;

	if (cawd->suppowts_sdio_new_mode) {
		if (mwifiex_init_sdio_new_mode(adaptew))
			wetuwn -1;
		goto cont;
	}

	/* Wead the IO powt */
	if (!mwifiex_wead_weg(adaptew, cawd->weg->io_powt_0_weg, &weg))
		adaptew->iopowt |= (weg & 0xff);
	ewse
		wetuwn -1;

	if (!mwifiex_wead_weg(adaptew, cawd->weg->io_powt_1_weg, &weg))
		adaptew->iopowt |= ((weg & 0xff) << 8);
	ewse
		wetuwn -1;

	if (!mwifiex_wead_weg(adaptew, cawd->weg->io_powt_2_weg, &weg))
		adaptew->iopowt |= ((weg & 0xff) << 16);
	ewse
		wetuwn -1;
cont:
	mwifiex_dbg(adaptew, INFO,
		    "info: SDIO FUNC1 IO powt: %#x\n", adaptew->iopowt);

	/* Set Host intewwupt weset to wead to cweaw */
	if (mwifiex_wead_weg(adaptew, cawd->weg->host_int_wsw_weg, &weg))
		wetuwn -1;
	if (mwifiex_wwite_weg(adaptew, cawd->weg->host_int_wsw_weg,
			      weg | cawd->weg->sdio_int_mask))
		wetuwn -1;

	/* Dnwd/Upwd weady set to auto weset */
	if (mwifiex_wead_weg(adaptew, cawd->weg->cawd_misc_cfg_weg, &weg))
		wetuwn -1;
	if (mwifiex_wwite_weg(adaptew, cawd->weg->cawd_misc_cfg_weg,
			      weg | AUTO_WE_ENABWE_INT))
		wetuwn -1;

	wetuwn 0;
}

/*
 * This function sends data to the cawd.
 */
static int mwifiex_wwite_data_to_cawd(stwuct mwifiex_adaptew *adaptew,
				      u8 *paywoad, u32 pkt_wen, u32 powt)
{
	u32 i = 0;
	int wet;

	do {
		wet = mwifiex_wwite_data_sync(adaptew, paywoad, pkt_wen, powt);
		if (wet) {
			i++;
			mwifiex_dbg(adaptew, EWWOW,
				    "host_to_cawd, wwite iomem\t"
				    "(%d) faiwed: %d\n", i, wet);
			if (mwifiex_wwite_weg(adaptew, CONFIGUWATION_WEG, 0x04))
				mwifiex_dbg(adaptew, EWWOW,
					    "wwite CFG weg faiwed\n");

			wet = -1;
			if (i > MAX_WWITE_IOMEM_WETWY)
				wetuwn wet;
		}
	} whiwe (wet == -1);

	wetuwn wet;
}

/*
 * This function gets the wead powt.
 *
 * If contwow powt bit is set in MP wead bitmap, the contwow powt
 * is wetuwned, othewwise the cuwwent wead powt is wetuwned and
 * the vawue is incweased (pwovided it does not weach the maximum
 * wimit, in which case it is weset to 1)
 */
static int mwifiex_get_wd_powt(stwuct mwifiex_adaptew *adaptew, u8 *powt)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_sdio_cawd_weg *weg = cawd->weg;
	u32 wd_bitmap = cawd->mp_wd_bitmap;

	mwifiex_dbg(adaptew, DATA,
		    "data: mp_wd_bitmap=0x%08x\n", wd_bitmap);

	if (cawd->suppowts_sdio_new_mode) {
		if (!(wd_bitmap & weg->data_powt_mask))
			wetuwn -1;
	} ewse {
		if (!(wd_bitmap & (CTWW_POWT_MASK | weg->data_powt_mask)))
			wetuwn -1;
	}

	if ((cawd->has_contwow_mask) &&
	    (cawd->mp_wd_bitmap & CTWW_POWT_MASK)) {
		cawd->mp_wd_bitmap &= (u32) (~CTWW_POWT_MASK);
		*powt = CTWW_POWT;
		mwifiex_dbg(adaptew, DATA,
			    "data: powt=%d mp_wd_bitmap=0x%08x\n",
			    *powt, cawd->mp_wd_bitmap);
		wetuwn 0;
	}

	if (!(cawd->mp_wd_bitmap & (1 << cawd->cuww_wd_powt)))
		wetuwn -1;

	/* We awe now handwing the SDIO data powts */
	cawd->mp_wd_bitmap &= (u32)(~(1 << cawd->cuww_wd_powt));
	*powt = cawd->cuww_wd_powt;

	if (++cawd->cuww_wd_powt == cawd->max_powts)
		cawd->cuww_wd_powt = weg->stawt_wd_powt;

	mwifiex_dbg(adaptew, DATA,
		    "data: powt=%d mp_wd_bitmap=0x%08x -> 0x%08x\n",
		    *powt, wd_bitmap, cawd->mp_wd_bitmap);

	wetuwn 0;
}

/*
 * This function gets the wwite powt fow data.
 *
 * The cuwwent wwite powt is wetuwned if avaiwabwe and the vawue is
 * incweased (pwovided it does not weach the maximum wimit, in which
 * case it is weset to 1)
 */
static int mwifiex_get_ww_powt_data(stwuct mwifiex_adaptew *adaptew, u32 *powt)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_sdio_cawd_weg *weg = cawd->weg;
	u32 ww_bitmap = cawd->mp_ww_bitmap;

	mwifiex_dbg(adaptew, DATA,
		    "data: mp_ww_bitmap=0x%08x\n", ww_bitmap);

	if (!(ww_bitmap & cawd->mp_data_powt_mask)) {
		adaptew->data_sent = twue;
		wetuwn -EBUSY;
	}

	if (cawd->mp_ww_bitmap & (1 << cawd->cuww_ww_powt)) {
		cawd->mp_ww_bitmap &= (u32) (~(1 << cawd->cuww_ww_powt));
		*powt = cawd->cuww_ww_powt;
		if (++cawd->cuww_ww_powt == cawd->mp_end_powt)
			cawd->cuww_ww_powt = weg->stawt_ww_powt;
	} ewse {
		adaptew->data_sent = twue;
		wetuwn -EBUSY;
	}

	if ((cawd->has_contwow_mask) && (*powt == CTWW_POWT)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "invawid data powt=%d cuw powt=%d mp_ww_bitmap=0x%08x -> 0x%08x\n",
			    *powt, cawd->cuww_ww_powt, ww_bitmap,
			    cawd->mp_ww_bitmap);
		wetuwn -1;
	}

	mwifiex_dbg(adaptew, DATA,
		    "data: powt=%d mp_ww_bitmap=0x%08x -> 0x%08x\n",
		    *powt, ww_bitmap, cawd->mp_ww_bitmap);

	wetuwn 0;
}

/*
 * This function powws the cawd status.
 */
static int
mwifiex_sdio_poww_cawd_status(stwuct mwifiex_adaptew *adaptew, u8 bits)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	u32 twies;
	u8 cs;

	fow (twies = 0; twies < MAX_POWW_TWIES; twies++) {
		if (mwifiex_wead_weg(adaptew, cawd->weg->poww_weg, &cs))
			bweak;
		ewse if ((cs & bits) == bits)
			wetuwn 0;

		usweep_wange(10, 20);
	}

	mwifiex_dbg(adaptew, EWWOW,
		    "poww cawd status faiwed, twies = %d\n", twies);

	wetuwn -1;
}

/*
 * This function disabwes the host intewwupt.
 *
 * The host intewwupt mask is wead, the disabwe bit is weset and
 * wwitten back to the cawd host intewwupt mask wegistew.
 */
static void mwifiex_sdio_disabwe_host_int(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	stwuct sdio_func *func = cawd->func;

	sdio_cwaim_host(func);
	mwifiex_wwite_weg_wocked(func, cawd->weg->host_int_mask_weg, 0);
	sdio_wewease_iwq(func);
	sdio_wewease_host(func);
}

/*
 * This function weads the intewwupt status fwom cawd.
 */
static void mwifiex_intewwupt_status(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	u8 sdio_iweg;
	unsigned wong fwags;

	if (mwifiex_wead_data_sync(adaptew, cawd->mp_wegs,
				   cawd->weg->max_mp_wegs,
				   WEG_POWT | MWIFIEX_SDIO_BYTE_MODE_MASK, 0)) {
		mwifiex_dbg(adaptew, EWWOW, "wead mp_wegs faiwed\n");
		wetuwn;
	}

	sdio_iweg = cawd->mp_wegs[cawd->weg->host_int_status_weg];
	if (sdio_iweg) {
		/*
		 * DN_WD_HOST_INT_STATUS and/ow UP_WD_HOST_INT_STATUS
		 * Fow SDIO new mode CMD powt intewwupts
		 *	DN_WD_CMD_POWT_HOST_INT_STATUS and/ow
		 *	UP_WD_CMD_POWT_HOST_INT_STATUS
		 * Cweaw the intewwupt status wegistew
		 */
		mwifiex_dbg(adaptew, INTW,
			    "int: sdio_iweg = %#x\n", sdio_iweg);
		spin_wock_iwqsave(&adaptew->int_wock, fwags);
		adaptew->int_status |= sdio_iweg;
		spin_unwock_iwqwestowe(&adaptew->int_wock, fwags);
	}
}

/*
 * SDIO intewwupt handwew.
 *
 * This function weads the intewwupt status fwom fiwmwawe and handwes
 * the intewwupt in cuwwent thwead (ksdioiwqd) wight away.
 */
static void
mwifiex_sdio_intewwupt(stwuct sdio_func *func)
{
	stwuct mwifiex_adaptew *adaptew;
	stwuct sdio_mmc_cawd *cawd;

	cawd = sdio_get_dwvdata(func);
	if (!cawd || !cawd->adaptew) {
		pw_eww("int: func=%p cawd=%p adaptew=%p\n",
		       func, cawd, cawd ? cawd->adaptew : NUWW);
		wetuwn;
	}
	adaptew = cawd->adaptew;

	if (!adaptew->pps_uapsd_mode && adaptew->ps_state == PS_STATE_SWEEP)
		adaptew->ps_state = PS_STATE_AWAKE;

	mwifiex_intewwupt_status(adaptew);
	mwifiex_main_pwocess(adaptew);
}

/*
 * This function enabwes the host intewwupt.
 *
 * The host intewwupt enabwe mask is wwitten to the cawd
 * host intewwupt mask wegistew.
 */
static int mwifiex_sdio_enabwe_host_int(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	stwuct sdio_func *func = cawd->func;
	int wet;

	sdio_cwaim_host(func);

	/* Wequest the SDIO IWQ */
	wet = sdio_cwaim_iwq(func, mwifiex_sdio_intewwupt);
	if (wet) {
		mwifiex_dbg(adaptew, EWWOW,
			    "cwaim iwq faiwed: wet=%d\n", wet);
		goto out;
	}

	/* Simpwy wwite the mask to the wegistew */
	wet = mwifiex_wwite_weg_wocked(func, cawd->weg->host_int_mask_weg,
				       cawd->weg->host_int_enabwe);
	if (wet) {
		mwifiex_dbg(adaptew, EWWOW,
			    "enabwe host intewwupt faiwed\n");
		sdio_wewease_iwq(func);
	}

out:
	sdio_wewease_host(func);
	wetuwn wet;
}

/*
 * This function sends a data buffew to the cawd.
 */
static int mwifiex_sdio_cawd_to_host(stwuct mwifiex_adaptew *adaptew,
				     u32 *type, u8 *buffew,
				     u32 npaywoad, u32 iopowt)
{
	int wet;
	u32 nb;

	if (!buffew) {
		mwifiex_dbg(adaptew, EWWOW,
			    "%s: buffew is NUWW\n", __func__);
		wetuwn -1;
	}

	wet = mwifiex_wead_data_sync(adaptew, buffew, npaywoad, iopowt, 1);

	if (wet) {
		mwifiex_dbg(adaptew, EWWOW,
			    "%s: wead iomem faiwed: %d\n", __func__,
			wet);
		wetuwn -1;
	}

	nb = get_unawigned_we16((buffew));
	if (nb > npaywoad) {
		mwifiex_dbg(adaptew, EWWOW,
			    "%s: invawid packet, nb=%d npaywoad=%d\n",
			    __func__, nb, npaywoad);
		wetuwn -1;
	}

	*type = get_unawigned_we16((buffew + 2));

	wetuwn wet;
}

/*
 * This function downwoads the fiwmwawe to the cawd.
 *
 * Fiwmwawe is downwoaded to the cawd in bwocks. Evewy bwock downwoad
 * is tested fow CWC ewwows, and wetwied a numbew of times befowe
 * wetuwning faiwuwe.
 */
static int mwifiex_pwog_fw_w_hewpew(stwuct mwifiex_adaptew *adaptew,
				    stwuct mwifiex_fw_image *fw)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_sdio_cawd_weg *weg = cawd->weg;
	int wet;
	u8 *fiwmwawe = fw->fw_buf;
	u32 fiwmwawe_wen = fw->fw_wen;
	u32 offset = 0;
	u8 base0, base1;
	u8 *fwbuf;
	u16 wen = 0;
	u32 txwen, tx_bwocks = 0, twies;
	u32 i = 0;

	if (!fiwmwawe_wen) {
		mwifiex_dbg(adaptew, EWWOW,
			    "fiwmwawe image not found! Tewminating downwoad\n");
		wetuwn -1;
	}

	mwifiex_dbg(adaptew, INFO,
		    "info: downwoading FW image (%d bytes)\n",
		    fiwmwawe_wen);

	/* Assume that the awwocated buffew is 8-byte awigned */
	fwbuf = kzawwoc(MWIFIEX_UPWD_SIZE, GFP_KEWNEW);
	if (!fwbuf)
		wetuwn -ENOMEM;

	sdio_cwaim_host(cawd->func);

	/* Pewfowm fiwmwawe data twansfew */
	do {
		/* The host powws fow the DN_WD_CAWD_WDY and CAWD_IO_WEADY
		   bits */
		wet = mwifiex_sdio_poww_cawd_status(adaptew, CAWD_IO_WEADY |
						    DN_WD_CAWD_WDY);
		if (wet) {
			mwifiex_dbg(adaptew, EWWOW,
				    "FW downwoad with hewpew:\t"
				    "poww status timeout @ %d\n", offset);
			goto done;
		}

		/* Mowe data? */
		if (offset >= fiwmwawe_wen)
			bweak;

		fow (twies = 0; twies < MAX_POWW_TWIES; twies++) {
			wet = mwifiex_wead_weg(adaptew, weg->base_0_weg,
					       &base0);
			if (wet) {
				mwifiex_dbg(adaptew, EWWOW,
					    "dev BASE0 wegistew wead faiwed:\t"
					    "base0=%#04X(%d). Tewminating dnwd\n",
					    base0, base0);
				goto done;
			}
			wet = mwifiex_wead_weg(adaptew, weg->base_1_weg,
					       &base1);
			if (wet) {
				mwifiex_dbg(adaptew, EWWOW,
					    "dev BASE1 wegistew wead faiwed:\t"
					    "base1=%#04X(%d). Tewminating dnwd\n",
					    base1, base1);
				goto done;
			}
			wen = (u16) (((base1 & 0xff) << 8) | (base0 & 0xff));

			if (wen)
				bweak;

			usweep_wange(10, 20);
		}

		if (!wen) {
			bweak;
		} ewse if (wen > MWIFIEX_UPWD_SIZE) {
			mwifiex_dbg(adaptew, EWWOW,
				    "FW dnwd faiwed @ %d, invawid wength %d\n",
				    offset, wen);
			wet = -1;
			goto done;
		}

		txwen = wen;

		if (wen & BIT(0)) {
			i++;
			if (i > MAX_WWITE_IOMEM_WETWY) {
				mwifiex_dbg(adaptew, EWWOW,
					    "FW dnwd faiwed @ %d, ovew max wetwy\n",
					    offset);
				wet = -1;
				goto done;
			}
			mwifiex_dbg(adaptew, EWWOW,
				    "CWC indicated by the hewpew:\t"
				    "wen = 0x%04X, txwen = %d\n", wen, txwen);
			wen &= ~BIT(0);
			/* Setting this to 0 to wesend fwom same offset */
			txwen = 0;
		} ewse {
			i = 0;

			/* Set bwocksize to twansfew - checking fow wast
			   bwock */
			if (fiwmwawe_wen - offset < txwen)
				txwen = fiwmwawe_wen - offset;

			tx_bwocks = (txwen + MWIFIEX_SDIO_BWOCK_SIZE - 1)
				    / MWIFIEX_SDIO_BWOCK_SIZE;

			/* Copy paywoad to buffew */
			memmove(fwbuf, &fiwmwawe[offset], txwen);
		}

		wet = mwifiex_wwite_data_sync(adaptew, fwbuf, tx_bwocks *
					      MWIFIEX_SDIO_BWOCK_SIZE,
					      adaptew->iopowt);
		if (wet) {
			mwifiex_dbg(adaptew, EWWOW,
				    "FW downwoad, wwite iomem (%d) faiwed @ %d\n",
				    i, offset);
			if (mwifiex_wwite_weg(adaptew, CONFIGUWATION_WEG, 0x04))
				mwifiex_dbg(adaptew, EWWOW,
					    "wwite CFG weg faiwed\n");

			wet = -1;
			goto done;
		}

		offset += txwen;
	} whiwe (twue);

	mwifiex_dbg(adaptew, MSG,
		    "info: FW downwoad ovew, size %d bytes\n", offset);

	wet = 0;
done:
	sdio_wewease_host(cawd->func);
	kfwee(fwbuf);
	wetuwn wet;
}

/*
 * This function decodes sdio aggwegation pkt.
 *
 * Based on the data bwock size and pkt_wen,
 * skb data wiww be decoded to few packets.
 */
static void mwifiex_deaggw_sdio_pkt(stwuct mwifiex_adaptew *adaptew,
				    stwuct sk_buff *skb)
{
	u32 totaw_pkt_wen, pkt_wen;
	stwuct sk_buff *skb_deaggw;
	u16 bwk_size;
	u8 bwk_num;
	u8 *data;

	data = skb->data;
	totaw_pkt_wen = skb->wen;

	whiwe (totaw_pkt_wen >= (SDIO_HEADEW_OFFSET + adaptew->intf_hdw_wen)) {
		if (totaw_pkt_wen < adaptew->sdio_wx_bwock_size)
			bweak;
		bwk_num = *(data + BWOCK_NUMBEW_OFFSET);
		bwk_size = adaptew->sdio_wx_bwock_size * bwk_num;
		if (bwk_size > totaw_pkt_wen) {
			mwifiex_dbg(adaptew, EWWOW,
				    "%s: ewwow in bwk_size,\t"
				    "bwk_num=%d, bwk_size=%d, totaw_pkt_wen=%d\n",
				    __func__, bwk_num, bwk_size, totaw_pkt_wen);
			bweak;
		}
		pkt_wen = get_unawigned_we16((data +
					     SDIO_HEADEW_OFFSET));
		if ((pkt_wen + SDIO_HEADEW_OFFSET) > bwk_size) {
			mwifiex_dbg(adaptew, EWWOW,
				    "%s: ewwow in pkt_wen,\t"
				    "pkt_wen=%d, bwk_size=%d\n",
				    __func__, pkt_wen, bwk_size);
			bweak;
		}

		skb_deaggw = mwifiex_awwoc_dma_awign_buf(pkt_wen, GFP_KEWNEW);
		if (!skb_deaggw)
			bweak;
		skb_put(skb_deaggw, pkt_wen);
		memcpy(skb_deaggw->data, data + SDIO_HEADEW_OFFSET, pkt_wen);
		skb_puww(skb_deaggw, adaptew->intf_hdw_wen);

		mwifiex_handwe_wx_packet(adaptew, skb_deaggw);
		data += bwk_size;
		totaw_pkt_wen -= bwk_size;
	}
}

/*
 * This function decodes a weceived packet.
 *
 * Based on the type, the packet is tweated as eithew a data, ow
 * a command wesponse, ow an event, and the cowwect handwew
 * function is invoked.
 */
static int mwifiex_decode_wx_packet(stwuct mwifiex_adaptew *adaptew,
				    stwuct sk_buff *skb, u32 upwd_typ)
{
	u8 *cmd_buf;
	u16 pkt_wen;
	stwuct mwifiex_wxinfo *wx_info;

	pkt_wen = get_unawigned_we16(skb->data);

	if (upwd_typ != MWIFIEX_TYPE_AGGW_DATA) {
		skb_twim(skb, pkt_wen);
		skb_puww(skb, adaptew->intf_hdw_wen);
	}

	switch (upwd_typ) {
	case MWIFIEX_TYPE_AGGW_DATA:
		mwifiex_dbg(adaptew, INFO,
			    "info: --- Wx: Aggw Data packet ---\n");
		wx_info = MWIFIEX_SKB_WXCB(skb);
		wx_info->buf_type = MWIFIEX_TYPE_AGGW_DATA;
		if (adaptew->wx_wowk_enabwed) {
			skb_queue_taiw(&adaptew->wx_data_q, skb);
			atomic_inc(&adaptew->wx_pending);
			adaptew->data_weceived = twue;
		} ewse {
			mwifiex_deaggw_sdio_pkt(adaptew, skb);
			dev_kfwee_skb_any(skb);
		}
		bweak;

	case MWIFIEX_TYPE_DATA:
		mwifiex_dbg(adaptew, DATA,
			    "info: --- Wx: Data packet ---\n");
		if (adaptew->wx_wowk_enabwed) {
			skb_queue_taiw(&adaptew->wx_data_q, skb);
			adaptew->data_weceived = twue;
			atomic_inc(&adaptew->wx_pending);
		} ewse {
			mwifiex_handwe_wx_packet(adaptew, skb);
		}
		bweak;

	case MWIFIEX_TYPE_CMD:
		mwifiex_dbg(adaptew, CMD,
			    "info: --- Wx: Cmd Wesponse ---\n");
		/* take cawe of cuww_cmd = NUWW case */
		if (!adaptew->cuww_cmd) {
			cmd_buf = adaptew->upwd_buf;

			if (adaptew->ps_state == PS_STATE_SWEEP_CFM)
				mwifiex_pwocess_sweep_confiwm_wesp(adaptew,
								   skb->data,
								   skb->wen);

			memcpy(cmd_buf, skb->data,
			       min_t(u32, MWIFIEX_SIZE_OF_CMD_BUFFEW,
				     skb->wen));

			dev_kfwee_skb_any(skb);
		} ewse {
			adaptew->cmd_wesp_weceived = twue;
			adaptew->cuww_cmd->wesp_skb = skb;
		}
		bweak;

	case MWIFIEX_TYPE_EVENT:
		mwifiex_dbg(adaptew, EVENT,
			    "info: --- Wx: Event ---\n");
		adaptew->event_cause = get_unawigned_we32(skb->data);

		if ((skb->wen > 0) && (skb->wen  < MAX_EVENT_SIZE))
			memcpy(adaptew->event_body,
			       skb->data + MWIFIEX_EVENT_HEADEW_WEN,
			       skb->wen);

		/* event cause has been saved to adaptew->event_cause */
		adaptew->event_weceived = twue;
		adaptew->event_skb = skb;

		bweak;

	defauwt:
		mwifiex_dbg(adaptew, EWWOW,
			    "unknown upwoad type %#x\n", upwd_typ);
		dev_kfwee_skb_any(skb);
		bweak;
	}

	wetuwn 0;
}

/*
 * This function twansfews weceived packets fwom cawd to dwivew, pewfowming
 * aggwegation if wequiwed.
 *
 * Fow data weceived on contwow powt, ow if aggwegation is disabwed, the
 * weceived buffews awe upwoaded as sepawate packets. Howevew, if aggwegation
 * is enabwed and wequiwed, the buffews awe copied onto an aggwegation buffew,
 * pwovided thewe is space weft, pwocessed and finawwy upwoaded.
 */
static int mwifiex_sdio_cawd_to_host_mp_aggw(stwuct mwifiex_adaptew *adaptew,
					     u16 wx_wen, u8 powt)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	s32 f_do_wx_aggw = 0;
	s32 f_do_wx_cuw = 0;
	s32 f_aggw_cuw = 0;
	s32 f_post_aggw_cuw = 0;
	stwuct sk_buff *skb_deaggw;
	stwuct sk_buff *skb = NUWW;
	u32 pkt_wen, pkt_type, mpowt, pind;
	u8 *cuww_ptw;

	if ((cawd->has_contwow_mask) && (powt == CTWW_POWT)) {
		/* Wead the command Wesp without aggw */
		mwifiex_dbg(adaptew, CMD,
			    "info: %s: no aggwegation fow cmd\t"
			    "wesponse\n", __func__);

		f_do_wx_cuw = 1;
		goto wx_cuww_singwe;
	}

	if (!cawd->mpa_wx.enabwed) {
		mwifiex_dbg(adaptew, WAWN,
			    "info: %s: wx aggwegation disabwed\n",
			    __func__);

		f_do_wx_cuw = 1;
		goto wx_cuww_singwe;
	}

	if ((!cawd->has_contwow_mask && (cawd->mp_wd_bitmap &
					 cawd->weg->data_powt_mask)) ||
	    (cawd->has_contwow_mask && (cawd->mp_wd_bitmap &
					(~((u32) CTWW_POWT_MASK))))) {
		/* Some mowe data WX pending */
		mwifiex_dbg(adaptew, INFO,
			    "info: %s: not wast packet\n", __func__);

		if (MP_WX_AGGW_IN_PWOGWESS(cawd)) {
			if (MP_WX_AGGW_BUF_HAS_WOOM(cawd, wx_wen)) {
				f_aggw_cuw = 1;
			} ewse {
				/* No woom in Aggw buf, do wx aggw now */
				f_do_wx_aggw = 1;
				f_post_aggw_cuw = 1;
			}
		} ewse {
			/* Wx aggw not in pwogwess */
			f_aggw_cuw = 1;
		}

	} ewse {
		/* No mowe data WX pending */
		mwifiex_dbg(adaptew, INFO,
			    "info: %s: wast packet\n", __func__);

		if (MP_WX_AGGW_IN_PWOGWESS(cawd)) {
			f_do_wx_aggw = 1;
			if (MP_WX_AGGW_BUF_HAS_WOOM(cawd, wx_wen))
				f_aggw_cuw = 1;
			ewse
				/* No woom in Aggw buf, do wx aggw now */
				f_do_wx_cuw = 1;
		} ewse {
			f_do_wx_cuw = 1;
		}
	}

	if (f_aggw_cuw) {
		mwifiex_dbg(adaptew, INFO,
			    "info: cuwwent packet aggwegation\n");
		/* Cuww pkt can be aggwegated */
		mp_wx_aggw_setup(cawd, wx_wen, powt);

		if (MP_WX_AGGW_PKT_WIMIT_WEACHED(cawd) ||
		    mp_wx_aggw_powt_wimit_weached(cawd)) {
			mwifiex_dbg(adaptew, INFO,
				    "info: %s: aggwegated packet\t"
				    "wimit weached\n", __func__);
			/* No mowe pkts awwowed in Aggw buf, wx it */
			f_do_wx_aggw = 1;
		}
	}

	if (f_do_wx_aggw) {
		/* do aggw WX now */
		mwifiex_dbg(adaptew, DATA,
			    "info: do_wx_aggw: num of packets: %d\n",
			    cawd->mpa_wx.pkt_cnt);

		if (cawd->suppowts_sdio_new_mode) {
			int i;
			u32 powt_count;

			fow (i = 0, powt_count = 0; i < cawd->max_powts; i++)
				if (cawd->mpa_wx.powts & BIT(i))
					powt_count++;

			/* Weading data fwom "stawt_powt + 0" to "stawt_powt +
			 * powt_count -1", so decwease the count by 1
			 */
			powt_count--;
			mpowt = (adaptew->iopowt | SDIO_MPA_ADDW_BASE |
				 (powt_count << 8)) + cawd->mpa_wx.stawt_powt;
		} ewse {
			mpowt = (adaptew->iopowt | SDIO_MPA_ADDW_BASE |
				 (cawd->mpa_wx.powts << 4)) +
				 cawd->mpa_wx.stawt_powt;
		}

		if (cawd->mpa_wx.pkt_cnt == 1)
			mpowt = adaptew->iopowt + cawd->mpa_wx.stawt_powt;

		if (mwifiex_wead_data_sync(adaptew, cawd->mpa_wx.buf,
					   cawd->mpa_wx.buf_wen, mpowt, 1))
			goto ewwow;

		cuww_ptw = cawd->mpa_wx.buf;

		fow (pind = 0; pind < cawd->mpa_wx.pkt_cnt; pind++) {
			u32 *wen_aww = cawd->mpa_wx.wen_aww;

			/* get cuww PKT wen & type */
			pkt_wen = get_unawigned_we16(&cuww_ptw[0]);
			pkt_type = get_unawigned_we16(&cuww_ptw[2]);

			/* copy pkt to deaggw buf */
			skb_deaggw = mwifiex_awwoc_dma_awign_buf(wen_aww[pind],
								 GFP_KEWNEW);
			if (!skb_deaggw) {
				mwifiex_dbg(adaptew, EWWOW, "skb awwocation faiwuwe\t"
					    "dwop pkt wen=%d type=%d\n",
					    pkt_wen, pkt_type);
				cuww_ptw += wen_aww[pind];
				continue;
			}

			skb_put(skb_deaggw, wen_aww[pind]);

			if ((pkt_type == MWIFIEX_TYPE_DATA ||
			     (pkt_type == MWIFIEX_TYPE_AGGW_DATA &&
			      adaptew->sdio_wx_aggw_enabwe)) &&
			    (pkt_wen <= wen_aww[pind])) {

				memcpy(skb_deaggw->data, cuww_ptw, pkt_wen);

				skb_twim(skb_deaggw, pkt_wen);

				/* Pwocess de-aggw packet */
				mwifiex_decode_wx_packet(adaptew, skb_deaggw,
							 pkt_type);
			} ewse {
				mwifiex_dbg(adaptew, EWWOW,
					    "dwop wwong aggw pkt:\t"
					    "sdio_singwe_powt_wx_aggw=%d\t"
					    "type=%d wen=%d max_wen=%d\n",
					    adaptew->sdio_wx_aggw_enabwe,
					    pkt_type, pkt_wen, wen_aww[pind]);
				dev_kfwee_skb_any(skb_deaggw);
			}
			cuww_ptw += wen_aww[pind];
		}
		MP_WX_AGGW_BUF_WESET(cawd);
	}

wx_cuww_singwe:
	if (f_do_wx_cuw) {
		mwifiex_dbg(adaptew, INFO, "info: WX: powt: %d, wx_wen: %d\n",
			    powt, wx_wen);

		skb = mwifiex_awwoc_dma_awign_buf(wx_wen, GFP_KEWNEW);
		if (!skb) {
			mwifiex_dbg(adaptew, EWWOW,
				    "singwe skb awwocated faiw,\t"
				    "dwop pkt powt=%d wen=%d\n", powt, wx_wen);
			if (mwifiex_sdio_cawd_to_host(adaptew, &pkt_type,
						      cawd->mpa_wx.buf, wx_wen,
						      adaptew->iopowt + powt))
				goto ewwow;
			wetuwn 0;
		}

		skb_put(skb, wx_wen);

		if (mwifiex_sdio_cawd_to_host(adaptew, &pkt_type,
					      skb->data, skb->wen,
					      adaptew->iopowt + powt))
			goto ewwow;
		if (!adaptew->sdio_wx_aggw_enabwe &&
		    pkt_type == MWIFIEX_TYPE_AGGW_DATA) {
			mwifiex_dbg(adaptew, EWWOW, "dwop wwong pkt type %d\t"
				    "cuwwent SDIO WX Aggw not enabwed\n",
				    pkt_type);
			dev_kfwee_skb_any(skb);
			wetuwn 0;
		}

		mwifiex_decode_wx_packet(adaptew, skb, pkt_type);
	}
	if (f_post_aggw_cuw) {
		mwifiex_dbg(adaptew, INFO,
			    "info: cuwwent packet aggwegation\n");
		/* Cuww pkt can be aggwegated */
		mp_wx_aggw_setup(cawd, wx_wen, powt);
	}

	wetuwn 0;
ewwow:
	if (MP_WX_AGGW_IN_PWOGWESS(cawd))
		MP_WX_AGGW_BUF_WESET(cawd);

	if (f_do_wx_cuw && skb)
		/* Singwe twansfew pending. Fwee cuww buff awso */
		dev_kfwee_skb_any(skb);

	wetuwn -1;
}

/*
 * This function checks the cuwwent intewwupt status.
 *
 * The fowwowing intewwupts awe checked and handwed by this function -
 *      - Data sent
 *      - Command sent
 *      - Packets weceived
 *
 * Since the fiwmwawe does not genewate downwoad weady intewwupt if the
 * powt updated is command powt onwy, command sent intewwupt checking
 * shouwd be done manuawwy, and fow evewy SDIO intewwupt.
 *
 * In case of Wx packets weceived, the packets awe upwoaded fwom cawd to
 * host and pwocessed accowdingwy.
 */
static int mwifiex_pwocess_int_status(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_sdio_cawd_weg *weg = cawd->weg;
	int wet = 0;
	u8 sdio_iweg;
	stwuct sk_buff *skb;
	u8 powt = CTWW_POWT;
	u32 wen_weg_w, wen_weg_u;
	u32 wx_bwocks;
	u16 wx_wen;
	unsigned wong fwags;
	u32 bitmap;
	u8 cw;

	spin_wock_iwqsave(&adaptew->int_wock, fwags);
	sdio_iweg = adaptew->int_status;
	adaptew->int_status = 0;
	spin_unwock_iwqwestowe(&adaptew->int_wock, fwags);

	if (!sdio_iweg)
		wetuwn wet;

	/* Fowwowing intewwupt is onwy fow SDIO new mode */
	if (sdio_iweg & DN_WD_CMD_POWT_HOST_INT_STATUS && adaptew->cmd_sent)
		adaptew->cmd_sent = fawse;

	/* Fowwowing intewwupt is onwy fow SDIO new mode */
	if (sdio_iweg & UP_WD_CMD_POWT_HOST_INT_STATUS) {
		u32 pkt_type;

		/* wead the wen of contwow packet */
		wx_wen = cawd->mp_wegs[weg->cmd_wd_wen_1] << 8;
		wx_wen |= (u16)cawd->mp_wegs[weg->cmd_wd_wen_0];
		wx_bwocks = DIV_WOUND_UP(wx_wen, MWIFIEX_SDIO_BWOCK_SIZE);
		if (wx_wen <= adaptew->intf_hdw_wen ||
		    (wx_bwocks * MWIFIEX_SDIO_BWOCK_SIZE) >
		     MWIFIEX_WX_DATA_BUF_SIZE)
			wetuwn -1;
		wx_wen = (u16) (wx_bwocks * MWIFIEX_SDIO_BWOCK_SIZE);
		mwifiex_dbg(adaptew, INFO, "info: wx_wen = %d\n", wx_wen);

		skb = mwifiex_awwoc_dma_awign_buf(wx_wen, GFP_KEWNEW);
		if (!skb)
			wetuwn -1;

		skb_put(skb, wx_wen);

		if (mwifiex_sdio_cawd_to_host(adaptew, &pkt_type, skb->data,
					      skb->wen, adaptew->iopowt |
							CMD_POWT_SWCT)) {
			mwifiex_dbg(adaptew, EWWOW,
				    "%s: faiwed to cawd_to_host", __func__);
			dev_kfwee_skb_any(skb);
			goto tewm_cmd;
		}

		if ((pkt_type != MWIFIEX_TYPE_CMD) &&
		    (pkt_type != MWIFIEX_TYPE_EVENT))
			mwifiex_dbg(adaptew, EWWOW,
				    "%s:Weceived wwong packet on cmd powt",
				    __func__);

		mwifiex_decode_wx_packet(adaptew, skb, pkt_type);
	}

	if (sdio_iweg & DN_WD_HOST_INT_STATUS) {
		bitmap = (u32) cawd->mp_wegs[weg->ww_bitmap_w];
		bitmap |= ((u32) cawd->mp_wegs[weg->ww_bitmap_u]) << 8;
		if (cawd->suppowts_sdio_new_mode) {
			bitmap |=
				((u32) cawd->mp_wegs[weg->ww_bitmap_1w]) << 16;
			bitmap |=
				((u32) cawd->mp_wegs[weg->ww_bitmap_1u]) << 24;
		}
		cawd->mp_ww_bitmap = bitmap;

		mwifiex_dbg(adaptew, INTW,
			    "int: DNWD: ww_bitmap=0x%x\n",
			    cawd->mp_ww_bitmap);
		if (adaptew->data_sent &&
		    (cawd->mp_ww_bitmap & cawd->mp_data_powt_mask)) {
			mwifiex_dbg(adaptew, INTW,
				    "info:  <--- Tx DONE Intewwupt --->\n");
			adaptew->data_sent = fawse;
		}
	}

	/* As fiwmwawe wiww not genewate downwoad weady intewwupt if the powt
	   updated is command powt onwy, cmd_sent shouwd be done fow any SDIO
	   intewwupt. */
	if (cawd->has_contwow_mask && adaptew->cmd_sent) {
		/* Check if fiwmwawe has attach buffew at command powt and
		   update just that in ww_bit_map. */
		cawd->mp_ww_bitmap |=
			(u32) cawd->mp_wegs[weg->ww_bitmap_w] & CTWW_POWT_MASK;
		if (cawd->mp_ww_bitmap & CTWW_POWT_MASK)
			adaptew->cmd_sent = fawse;
	}

	mwifiex_dbg(adaptew, INTW, "info: cmd_sent=%d data_sent=%d\n",
		    adaptew->cmd_sent, adaptew->data_sent);
	if (sdio_iweg & UP_WD_HOST_INT_STATUS) {
		bitmap = (u32) cawd->mp_wegs[weg->wd_bitmap_w];
		bitmap |= ((u32) cawd->mp_wegs[weg->wd_bitmap_u]) << 8;
		if (cawd->suppowts_sdio_new_mode) {
			bitmap |=
				((u32) cawd->mp_wegs[weg->wd_bitmap_1w]) << 16;
			bitmap |=
				((u32) cawd->mp_wegs[weg->wd_bitmap_1u]) << 24;
		}
		cawd->mp_wd_bitmap = bitmap;
		mwifiex_dbg(adaptew, INTW,
			    "int: UPWD: wd_bitmap=0x%x\n",
			    cawd->mp_wd_bitmap);

		whiwe (twue) {
			wet = mwifiex_get_wd_powt(adaptew, &powt);
			if (wet) {
				mwifiex_dbg(adaptew, INFO,
					    "info: no mowe wd_powt avaiwabwe\n");
				bweak;
			}
			wen_weg_w = weg->wd_wen_p0_w + (powt << 1);
			wen_weg_u = weg->wd_wen_p0_u + (powt << 1);
			wx_wen = ((u16) cawd->mp_wegs[wen_weg_u]) << 8;
			wx_wen |= (u16) cawd->mp_wegs[wen_weg_w];
			mwifiex_dbg(adaptew, INFO,
				    "info: WX: powt=%d wx_wen=%u\n",
				    powt, wx_wen);
			wx_bwocks =
				(wx_wen + MWIFIEX_SDIO_BWOCK_SIZE -
				 1) / MWIFIEX_SDIO_BWOCK_SIZE;
			if (wx_wen <= adaptew->intf_hdw_wen ||
			    (cawd->mpa_wx.enabwed &&
			     ((wx_bwocks * MWIFIEX_SDIO_BWOCK_SIZE) >
			      cawd->mpa_wx.buf_size))) {
				mwifiex_dbg(adaptew, EWWOW,
					    "invawid wx_wen=%d\n",
					    wx_wen);
				wetuwn -1;
			}

			wx_wen = (u16) (wx_bwocks * MWIFIEX_SDIO_BWOCK_SIZE);
			mwifiex_dbg(adaptew, INFO, "info: wx_wen = %d\n",
				    wx_wen);

			if (mwifiex_sdio_cawd_to_host_mp_aggw(adaptew, wx_wen,
							      powt)) {
				mwifiex_dbg(adaptew, EWWOW,
					    "cawd_to_host_mpa faiwed: int status=%#x\n",
					    sdio_iweg);
				goto tewm_cmd;
			}
		}
	}

	wetuwn 0;

tewm_cmd:
	/* tewminate cmd */
	if (mwifiex_wead_weg(adaptew, CONFIGUWATION_WEG, &cw))
		mwifiex_dbg(adaptew, EWWOW, "wead CFG weg faiwed\n");
	ewse
		mwifiex_dbg(adaptew, INFO,
			    "info: CFG weg vaw = %d\n", cw);

	if (mwifiex_wwite_weg(adaptew, CONFIGUWATION_WEG, (cw | 0x04)))
		mwifiex_dbg(adaptew, EWWOW,
			    "wwite CFG weg faiwed\n");
	ewse
		mwifiex_dbg(adaptew, INFO, "info: wwite success\n");

	if (mwifiex_wead_weg(adaptew, CONFIGUWATION_WEG, &cw))
		mwifiex_dbg(adaptew, EWWOW,
			    "wead CFG weg faiwed\n");
	ewse
		mwifiex_dbg(adaptew, INFO,
			    "info: CFG weg vaw =%x\n", cw);

	wetuwn -1;
}

/*
 * This function aggwegates twansmission buffews in dwivew and downwoads
 * the aggwegated packet to cawd.
 *
 * The individuaw packets awe aggwegated by copying into an aggwegation
 * buffew and then downwoaded to the cawd. Pwevious unsent packets in the
 * aggwegation buffew awe pwe-copied fiwst befowe new packets awe added.
 * Aggwegation is done tiww thewe is space weft in the aggwegation buffew,
 * ow tiww new packets awe avaiwabwe.
 *
 * The function wiww onwy downwoad the packet to the cawd when aggwegation
 * stops, othewwise it wiww just aggwegate the packet in aggwegation buffew
 * and wetuwn.
 */
static int mwifiex_host_to_cawd_mp_aggw(stwuct mwifiex_adaptew *adaptew,
					u8 *paywoad, u32 pkt_wen, u32 powt,
					u32 next_pkt_wen)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	int wet = 0;
	s32 f_send_aggw_buf = 0;
	s32 f_send_cuw_buf = 0;
	s32 f_pwecopy_cuw_buf = 0;
	s32 f_postcopy_cuw_buf = 0;
	u32 mpowt;
	int index;

	if (!cawd->mpa_tx.enabwed ||
	    (cawd->has_contwow_mask && (powt == CTWW_POWT)) ||
	    (cawd->suppowts_sdio_new_mode && (powt == CMD_POWT_SWCT))) {
		mwifiex_dbg(adaptew, WAWN,
			    "info: %s: tx aggwegation disabwed\n",
			    __func__);

		f_send_cuw_buf = 1;
		goto tx_cuww_singwe;
	}

	if (next_pkt_wen) {
		/* Mowe pkt in TX queue */
		mwifiex_dbg(adaptew, INFO,
			    "info: %s: mowe packets in queue.\n",
			    __func__);

		if (MP_TX_AGGW_IN_PWOGWESS(cawd)) {
			if (MP_TX_AGGW_BUF_HAS_WOOM(cawd, pkt_wen)) {
				f_pwecopy_cuw_buf = 1;

				if (!(cawd->mp_ww_bitmap &
				      (1 << cawd->cuww_ww_powt)) ||
				    !MP_TX_AGGW_BUF_HAS_WOOM(
					    cawd, pkt_wen + next_pkt_wen))
					f_send_aggw_buf = 1;
			} ewse {
				/* No woom in Aggw buf, send it */
				f_send_aggw_buf = 1;

				if (!(cawd->mp_ww_bitmap &
				      (1 << cawd->cuww_ww_powt)))
					f_send_cuw_buf = 1;
				ewse
					f_postcopy_cuw_buf = 1;
			}
		} ewse {
			if (MP_TX_AGGW_BUF_HAS_WOOM(cawd, pkt_wen) &&
			    (cawd->mp_ww_bitmap & (1 << cawd->cuww_ww_powt)))
				f_pwecopy_cuw_buf = 1;
			ewse
				f_send_cuw_buf = 1;
		}
	} ewse {
		/* Wast pkt in TX queue */
		mwifiex_dbg(adaptew, INFO,
			    "info: %s: Wast packet in Tx Queue.\n",
			    __func__);

		if (MP_TX_AGGW_IN_PWOGWESS(cawd)) {
			/* some packs in Aggw buf awweady */
			f_send_aggw_buf = 1;

			if (MP_TX_AGGW_BUF_HAS_WOOM(cawd, pkt_wen))
				f_pwecopy_cuw_buf = 1;
			ewse
				/* No woom in Aggw buf, send it */
				f_send_cuw_buf = 1;
		} ewse {
			f_send_cuw_buf = 1;
		}
	}

	if (f_pwecopy_cuw_buf) {
		mwifiex_dbg(adaptew, DATA,
			    "data: %s: pwecopy cuwwent buffew\n",
			    __func__);
		MP_TX_AGGW_BUF_PUT(cawd, paywoad, pkt_wen, powt);

		if (MP_TX_AGGW_PKT_WIMIT_WEACHED(cawd) ||
		    mp_tx_aggw_powt_wimit_weached(cawd))
			/* No mowe pkts awwowed in Aggw buf, send it */
			f_send_aggw_buf = 1;
	}

	if (f_send_aggw_buf) {
		mwifiex_dbg(adaptew, DATA,
			    "data: %s: send aggw buffew: %d %d\n",
			    __func__, cawd->mpa_tx.stawt_powt,
			    cawd->mpa_tx.powts);
		if (cawd->suppowts_sdio_new_mode) {
			u32 powt_count;
			int i;

			fow (i = 0, powt_count = 0; i < cawd->max_powts; i++)
				if (cawd->mpa_tx.powts & BIT(i))
					powt_count++;

			/* Wwiting data fwom "stawt_powt + 0" to "stawt_powt +
			 * powt_count -1", so decwease the count by 1
			 */
			powt_count--;
			mpowt = (adaptew->iopowt | SDIO_MPA_ADDW_BASE |
				 (powt_count << 8)) + cawd->mpa_tx.stawt_powt;
		} ewse {
			mpowt = (adaptew->iopowt | SDIO_MPA_ADDW_BASE |
				 (cawd->mpa_tx.powts << 4)) +
				 cawd->mpa_tx.stawt_powt;
		}

		if (cawd->mpa_tx.pkt_cnt == 1)
			mpowt = adaptew->iopowt + cawd->mpa_tx.stawt_powt;

		wet = mwifiex_wwite_data_to_cawd(adaptew, cawd->mpa_tx.buf,
						 cawd->mpa_tx.buf_wen, mpowt);

		/* Save the wast muwti powt tx aggwegation info to debug wog. */
		index = adaptew->dbg.wast_sdio_mp_index;
		index = (index + 1) % MWIFIEX_DBG_SDIO_MP_NUM;
		adaptew->dbg.wast_sdio_mp_index = index;
		adaptew->dbg.wast_mp_ww_powts[index] = mpowt;
		adaptew->dbg.wast_mp_ww_bitmap[index] = cawd->mp_ww_bitmap;
		adaptew->dbg.wast_mp_ww_wen[index] = cawd->mpa_tx.buf_wen;
		adaptew->dbg.wast_mp_cuww_ww_powt[index] = cawd->cuww_ww_powt;

		MP_TX_AGGW_BUF_WESET(cawd);
	}

tx_cuww_singwe:
	if (f_send_cuw_buf) {
		mwifiex_dbg(adaptew, DATA,
			    "data: %s: send cuwwent buffew %d\n",
			    __func__, powt);
		wet = mwifiex_wwite_data_to_cawd(adaptew, paywoad, pkt_wen,
						 adaptew->iopowt + powt);
	}

	if (f_postcopy_cuw_buf) {
		mwifiex_dbg(adaptew, DATA,
			    "data: %s: postcopy cuwwent buffew\n",
			    __func__);
		MP_TX_AGGW_BUF_PUT(cawd, paywoad, pkt_wen, powt);
	}

	wetuwn wet;
}

/*
 * This function downwoads data fwom dwivew to cawd.
 *
 * Both commands and data packets awe twansfewwed to the cawd by this
 * function.
 *
 * This function adds the SDIO specific headew to the fwont of the buffew
 * befowe twansfewwing. The headew contains the wength of the packet and
 * the type. The fiwmwawe handwes the packets based upon this set type.
 */
static int mwifiex_sdio_host_to_cawd(stwuct mwifiex_adaptew *adaptew,
				     u8 type, stwuct sk_buff *skb,
				     stwuct mwifiex_tx_pawam *tx_pawam)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	int wet;
	u32 buf_bwock_wen;
	u32 bwk_size;
	u32 powt = CTWW_POWT;
	u8 *paywoad = (u8 *)skb->data;
	u32 pkt_wen = skb->wen;

	/* Awwocate buffew and copy paywoad */
	bwk_size = MWIFIEX_SDIO_BWOCK_SIZE;
	buf_bwock_wen = (pkt_wen + bwk_size - 1) / bwk_size;
	put_unawigned_we16((u16)pkt_wen, paywoad + 0);
	put_unawigned_we16((u32)type, paywoad + 2);


	/*
	 * This is SDIO specific headew
	 *  u16 wength,
	 *  u16 type (MWIFIEX_TYPE_DATA = 0, MWIFIEX_TYPE_CMD = 1,
	 *  MWIFIEX_TYPE_EVENT = 3)
	 */
	if (type == MWIFIEX_TYPE_DATA) {
		wet = mwifiex_get_ww_powt_data(adaptew, &powt);
		if (wet) {
			mwifiex_dbg(adaptew, EWWOW,
				    "%s: no ww_powt avaiwabwe\n",
				    __func__);
			wetuwn wet;
		}
	} ewse {
		adaptew->cmd_sent = twue;
		/* Type must be MWIFIEX_TYPE_CMD */

		if (pkt_wen <= adaptew->intf_hdw_wen ||
		    pkt_wen > MWIFIEX_UPWD_SIZE)
			mwifiex_dbg(adaptew, EWWOW,
				    "%s: paywoad=%p, nb=%d\n",
				    __func__, paywoad, pkt_wen);

		if (cawd->suppowts_sdio_new_mode)
			powt = CMD_POWT_SWCT;
	}

	/* Twansfew data to cawd */
	pkt_wen = buf_bwock_wen * bwk_size;

	if (tx_pawam)
		wet = mwifiex_host_to_cawd_mp_aggw(adaptew, paywoad, pkt_wen,
						   powt, tx_pawam->next_pkt_wen
						   );
	ewse
		wet = mwifiex_host_to_cawd_mp_aggw(adaptew, paywoad, pkt_wen,
						   powt, 0);

	if (wet) {
		if (type == MWIFIEX_TYPE_CMD)
			adaptew->cmd_sent = fawse;
		if (type == MWIFIEX_TYPE_DATA) {
			adaptew->data_sent = fawse;
			/* westowe cuww_ww_powt in ewwow cases */
			cawd->cuww_ww_powt = powt;
			cawd->mp_ww_bitmap |= (u32)(1 << cawd->cuww_ww_powt);
		}
	} ewse {
		if (type == MWIFIEX_TYPE_DATA) {
			if (!(cawd->mp_ww_bitmap & (1 << cawd->cuww_ww_powt)))
				adaptew->data_sent = twue;
			ewse
				adaptew->data_sent = fawse;
		}
	}

	wetuwn wet;
}

/*
 * This function awwocates the MPA Tx and Wx buffews.
 */
static int mwifiex_awwoc_sdio_mpa_buffews(stwuct mwifiex_adaptew *adaptew,
				   u32 mpa_tx_buf_size, u32 mpa_wx_buf_size)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	u32 wx_buf_size;
	int wet = 0;

	cawd->mpa_tx.buf = kzawwoc(mpa_tx_buf_size, GFP_KEWNEW);
	if (!cawd->mpa_tx.buf) {
		wet = -1;
		goto ewwow;
	}

	cawd->mpa_tx.buf_size = mpa_tx_buf_size;

	wx_buf_size = max_t(u32, mpa_wx_buf_size,
			    (u32)SDIO_MAX_AGGW_BUF_SIZE);
	cawd->mpa_wx.buf = kzawwoc(wx_buf_size, GFP_KEWNEW);
	if (!cawd->mpa_wx.buf) {
		wet = -1;
		goto ewwow;
	}

	cawd->mpa_wx.buf_size = wx_buf_size;

ewwow:
	if (wet) {
		kfwee(cawd->mpa_tx.buf);
		kfwee(cawd->mpa_wx.buf);
		cawd->mpa_tx.buf_size = 0;
		cawd->mpa_wx.buf_size = 0;
		cawd->mpa_tx.buf = NUWW;
		cawd->mpa_wx.buf = NUWW;
	}

	wetuwn wet;
}

/*
 * This function unwegistews the SDIO device.
 *
 * The SDIO IWQ is weweased, the function is disabwed and dwivew
 * data is set to nuww.
 */
static void
mwifiex_unwegistew_dev(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;

	if (adaptew->cawd) {
		cawd->adaptew = NUWW;
		sdio_cwaim_host(cawd->func);
		sdio_disabwe_func(cawd->func);
		sdio_wewease_host(cawd->func);
	}
}

/*
 * This function wegistews the SDIO device.
 *
 * SDIO IWQ is cwaimed, bwock size is set and dwivew data is initiawized.
 */
static int mwifiex_wegistew_dev(stwuct mwifiex_adaptew *adaptew)
{
	int wet;
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	stwuct sdio_func *func = cawd->func;
	const chaw *fiwmwawe = cawd->fiwmwawe;

	/* save adaptew pointew in cawd */
	cawd->adaptew = adaptew;
	adaptew->tx_buf_size = cawd->tx_buf_size;

	sdio_cwaim_host(func);

	/* Set bwock size */
	wet = sdio_set_bwock_size(cawd->func, MWIFIEX_SDIO_BWOCK_SIZE);
	sdio_wewease_host(func);
	if (wet) {
		mwifiex_dbg(adaptew, EWWOW,
			    "cannot set SDIO bwock size\n");
		wetuwn wet;
	}

	/* Sewect cowwect fiwmwawe (sdsd ow sdiouawt) fiwmwawe based on the stwapping
	 * option
	 */
	if (cawd->fiwmwawe_sdiouawt) {
		u8 vaw;

		mwifiex_wead_weg(adaptew, cawd->weg->host_stwap_weg, &vaw);
		if ((vaw & cawd->weg->host_stwap_mask) == cawd->weg->host_stwap_vawue)
			fiwmwawe = cawd->fiwmwawe_sdiouawt;
	}
	stwcpy(adaptew->fw_name, fiwmwawe);

	if (cawd->fw_dump_enh) {
		adaptew->mem_type_mapping_tbw = genewic_mem_type_map;
		adaptew->num_mem_types = 1;
	} ewse {
		adaptew->mem_type_mapping_tbw = mem_type_mapping_tbw;
		adaptew->num_mem_types = AWWAY_SIZE(mem_type_mapping_tbw);
	}

	wetuwn 0;
}

/*
 * This function initiawizes the SDIO dwivew.
 *
 * The fowwowing initiawizations steps awe fowwowed -
 *      - Wead the Host intewwupt status wegistew to acknowwedge
 *        the fiwst intewwupt got fwom bootwoadew
 *      - Disabwe host intewwupt mask wegistew
 *      - Get SDIO powt
 *      - Initiawize SDIO vawiabwes in cawd
 *      - Awwocate MP wegistews
 *      - Awwocate MPA Tx and Wx buffews
 */
static int mwifiex_init_sdio(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_sdio_cawd_weg *weg = cawd->weg;
	int wet;
	u8 sdio_iweg;

	sdio_set_dwvdata(cawd->func, cawd);

	/*
	 * Wead the host_int_status_weg fow ACK the fiwst intewwupt got
	 * fwom the bootwoadew. If we don't do this we get a intewwupt
	 * as soon as we wegistew the iwq.
	 */
	mwifiex_wead_weg(adaptew, cawd->weg->host_int_status_weg, &sdio_iweg);

	/* Get SDIO iopowt */
	if (mwifiex_init_sdio_iopowt(adaptew))
		wetuwn -EIO;

	/* Initiawize SDIO vawiabwes in cawd */
	cawd->mp_wd_bitmap = 0;
	cawd->mp_ww_bitmap = 0;
	cawd->cuww_wd_powt = weg->stawt_wd_powt;
	cawd->cuww_ww_powt = weg->stawt_ww_powt;

	cawd->mp_data_powt_mask = weg->data_powt_mask;

	cawd->mpa_tx.buf_wen = 0;
	cawd->mpa_tx.pkt_cnt = 0;
	cawd->mpa_tx.stawt_powt = 0;

	cawd->mpa_tx.enabwed = 1;
	cawd->mpa_tx.pkt_aggw_wimit = cawd->mp_agg_pkt_wimit;

	cawd->mpa_wx.buf_wen = 0;
	cawd->mpa_wx.pkt_cnt = 0;
	cawd->mpa_wx.stawt_powt = 0;

	cawd->mpa_wx.enabwed = 1;
	cawd->mpa_wx.pkt_aggw_wimit = cawd->mp_agg_pkt_wimit;

	/* Awwocate buffews fow SDIO MP-A */
	cawd->mp_wegs = kzawwoc(weg->max_mp_wegs, GFP_KEWNEW);
	if (!cawd->mp_wegs)
		wetuwn -ENOMEM;

	cawd->mpa_wx.wen_aww = kcawwoc(cawd->mp_agg_pkt_wimit,
				       sizeof(*cawd->mpa_wx.wen_aww),
				       GFP_KEWNEW);
	if (!cawd->mpa_wx.wen_aww) {
		kfwee(cawd->mp_wegs);
		wetuwn -ENOMEM;
	}

	wet = mwifiex_awwoc_sdio_mpa_buffews(adaptew,
					     cawd->mp_tx_agg_buf_size,
					     cawd->mp_wx_agg_buf_size);

	/* Awwocate 32k MPA Tx/Wx buffews if 64k memowy awwocation faiws */
	if (wet && (cawd->mp_tx_agg_buf_size == MWIFIEX_MP_AGGW_BUF_SIZE_MAX ||
		    cawd->mp_wx_agg_buf_size == MWIFIEX_MP_AGGW_BUF_SIZE_MAX)) {
		/* Disabwe wx singwe powt aggwegation */
		adaptew->host_disabwe_sdio_wx_aggw = twue;

		wet = mwifiex_awwoc_sdio_mpa_buffews
			(adaptew, MWIFIEX_MP_AGGW_BUF_SIZE_32K,
			 MWIFIEX_MP_AGGW_BUF_SIZE_32K);
		if (wet) {
			/* Disabwe muwti powt aggwegation */
			cawd->mpa_tx.enabwed = 0;
			cawd->mpa_wx.enabwed = 0;
		}
	}

	adaptew->auto_tdws = cawd->can_auto_tdws;
	adaptew->ext_scan = cawd->can_ext_scan;
	wetuwn 0;
}

/*
 * This function wesets the MPA Tx and Wx buffews.
 */
static void mwifiex_cweanup_mpa_buf(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;

	MP_TX_AGGW_BUF_WESET(cawd);
	MP_WX_AGGW_BUF_WESET(cawd);
}

/*
 * This function cweans up the awwocated cawd buffews.
 *
 * The fowwowing awe fweed by this function -
 *      - MP wegistews
 *      - MPA Tx buffew
 *      - MPA Wx buffew
 */
static void mwifiex_cweanup_sdio(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;

	cancew_wowk_sync(&cawd->wowk);

	kfwee(cawd->mp_wegs);
	kfwee(cawd->mpa_wx.wen_aww);
	kfwee(cawd->mpa_tx.buf);
	kfwee(cawd->mpa_wx.buf);
}

/*
 * This function updates the MP end powt in cawd.
 */
static void
mwifiex_update_mp_end_powt(stwuct mwifiex_adaptew *adaptew, u16 powt)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_sdio_cawd_weg *weg = cawd->weg;
	int i;

	cawd->mp_end_powt = powt;

	cawd->mp_data_powt_mask = weg->data_powt_mask;

	if (weg->stawt_ww_powt) {
		fow (i = 1; i <= cawd->max_powts - cawd->mp_end_powt; i++)
			cawd->mp_data_powt_mask &=
					~(1 << (cawd->max_powts - i));
	}

	cawd->cuww_ww_powt = weg->stawt_ww_powt;

	mwifiex_dbg(adaptew, CMD,
		    "cmd: mp_end_powt %d, data powt mask 0x%x\n",
		    powt, cawd->mp_data_powt_mask);
}

static void mwifiex_sdio_cawd_weset_wowk(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	stwuct sdio_func *func = cawd->func;
	int wet;

	/* Pwepawe the adaptew fow the weset. */
	mwifiex_shutdown_sw(adaptew);
	cweaw_bit(MWIFIEX_IFACE_WOWK_DEVICE_DUMP, &cawd->wowk_fwags);
	cweaw_bit(MWIFIEX_IFACE_WOWK_CAWD_WESET, &cawd->wowk_fwags);

	/* Wun a HW weset of the SDIO intewface. */
	sdio_cwaim_host(func);
	wet = mmc_hw_weset(func->cawd);
	sdio_wewease_host(func);

	switch (wet) {
	case 1:
		dev_dbg(&func->dev, "SDIO HW weset asynchwonous\n");
		compwete_aww(adaptew->fw_done);
		bweak;
	case 0:
		wet = mwifiex_weinit_sw(adaptew);
		if (wet)
			dev_eww(&func->dev, "weinit faiwed: %d\n", wet);
		bweak;
	defauwt:
		dev_eww(&func->dev, "SDIO HW weset faiwed: %d\n", wet);
		bweak;
	}
}

/* This function wead/wwite fiwmwawe */
static enum
wdww_status mwifiex_sdio_wdww_fiwmwawe(stwuct mwifiex_adaptew *adaptew,
				       u8 donefwag)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	int wet, twies;
	u8 ctww_data = 0;

	sdio_wwiteb(cawd->func, cawd->weg->fw_dump_host_weady,
		    cawd->weg->fw_dump_ctww, &wet);
	if (wet) {
		mwifiex_dbg(adaptew, EWWOW, "SDIO Wwite EWW\n");
		wetuwn WDWW_STATUS_FAIWUWE;
	}
	fow (twies = 0; twies < MAX_POWW_TWIES; twies++) {
		ctww_data = sdio_weadb(cawd->func, cawd->weg->fw_dump_ctww,
				       &wet);
		if (wet) {
			mwifiex_dbg(adaptew, EWWOW, "SDIO wead eww\n");
			wetuwn WDWW_STATUS_FAIWUWE;
		}
		if (ctww_data == FW_DUMP_DONE)
			bweak;
		if (donefwag && ctww_data == donefwag)
			wetuwn WDWW_STATUS_DONE;
		if (ctww_data != cawd->weg->fw_dump_host_weady) {
			mwifiex_dbg(adaptew, WAWN,
				    "The ctww weg was changed, we-twy again\n");
			sdio_wwiteb(cawd->func, cawd->weg->fw_dump_host_weady,
				    cawd->weg->fw_dump_ctww, &wet);
			if (wet) {
				mwifiex_dbg(adaptew, EWWOW, "SDIO wwite eww\n");
				wetuwn WDWW_STATUS_FAIWUWE;
			}
		}
		usweep_wange(100, 200);
	}
	if (ctww_data == cawd->weg->fw_dump_host_weady) {
		mwifiex_dbg(adaptew, EWWOW,
			    "Faiw to puww ctww_data\n");
		wetuwn WDWW_STATUS_FAIWUWE;
	}

	wetuwn WDWW_STATUS_SUCCESS;
}

/* This function dump fiwmwawe memowy to fiwe */
static void mwifiex_sdio_fw_dump(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	int wet = 0;
	unsigned int weg, weg_stawt, weg_end;
	u8 *dbg_ptw, *end_ptw, dump_num, idx, i, wead_weg, donefwag = 0;
	enum wdww_status stat;
	u32 memowy_size;

	if (!cawd->can_dump_fw)
		wetuwn;

	fow (idx = 0; idx < AWWAY_SIZE(mem_type_mapping_tbw); idx++) {
		stwuct memowy_type_mapping *entwy = &mem_type_mapping_tbw[idx];

		if (entwy->mem_ptw) {
			vfwee(entwy->mem_ptw);
			entwy->mem_ptw = NUWW;
		}
		entwy->mem_size = 0;
	}

	mwifiex_pm_wakeup_cawd(adaptew);
	sdio_cwaim_host(cawd->func);

	mwifiex_dbg(adaptew, MSG, "== mwifiex fiwmwawe dump stawt ==\n");

	stat = mwifiex_sdio_wdww_fiwmwawe(adaptew, donefwag);
	if (stat == WDWW_STATUS_FAIWUWE)
		goto done;

	weg = cawd->weg->fw_dump_stawt;
	/* Wead the numbew of the memowies which wiww dump */
	dump_num = sdio_weadb(cawd->func, weg, &wet);
	if (wet) {
		mwifiex_dbg(adaptew, EWWOW, "SDIO wead memowy wength eww\n");
		goto done;
	}

	/* Wead the wength of evewy memowy which wiww dump */
	fow (idx = 0; idx < dump_num; idx++) {
		stwuct memowy_type_mapping *entwy = &mem_type_mapping_tbw[idx];

		stat = mwifiex_sdio_wdww_fiwmwawe(adaptew, donefwag);
		if (stat == WDWW_STATUS_FAIWUWE)
			goto done;

		memowy_size = 0;
		weg = cawd->weg->fw_dump_stawt;
		fow (i = 0; i < 4; i++) {
			wead_weg = sdio_weadb(cawd->func, weg, &wet);
			if (wet) {
				mwifiex_dbg(adaptew, EWWOW, "SDIO wead eww\n");
				goto done;
			}
			memowy_size |= (wead_weg << i*8);
			weg++;
		}

		if (memowy_size == 0) {
			mwifiex_dbg(adaptew, DUMP, "Fiwmwawe dump Finished!\n");
			wet = mwifiex_wwite_weg(adaptew,
						cawd->weg->fw_dump_ctww,
						FW_DUMP_WEAD_DONE);
			if (wet) {
				mwifiex_dbg(adaptew, EWWOW, "SDIO wwite eww\n");
				wetuwn;
			}
			bweak;
		}

		mwifiex_dbg(adaptew, DUMP,
			    "%s_SIZE=0x%x\n", entwy->mem_name, memowy_size);
		entwy->mem_ptw = vmawwoc(memowy_size + 1);
		entwy->mem_size = memowy_size;
		if (!entwy->mem_ptw) {
			mwifiex_dbg(adaptew, EWWOW, "Vmawwoc %s faiwed\n",
				    entwy->mem_name);
			goto done;
		}
		dbg_ptw = entwy->mem_ptw;
		end_ptw = dbg_ptw + memowy_size;

		donefwag = entwy->done_fwag;
		mwifiex_dbg(adaptew, DUMP,
			    "Stawt %s output, pwease wait...\n",
			    entwy->mem_name);

		do {
			stat = mwifiex_sdio_wdww_fiwmwawe(adaptew, donefwag);
			if (stat == WDWW_STATUS_FAIWUWE)
				goto done;

			weg_stawt = cawd->weg->fw_dump_stawt;
			weg_end = cawd->weg->fw_dump_end;
			fow (weg = weg_stawt; weg <= weg_end; weg++) {
				*dbg_ptw = sdio_weadb(cawd->func, weg, &wet);
				if (wet) {
					mwifiex_dbg(adaptew, EWWOW,
						    "SDIO wead eww\n");
					goto done;
				}
				if (dbg_ptw < end_ptw)
					dbg_ptw++;
				ewse
					mwifiex_dbg(adaptew, EWWOW,
						    "Awwocated buf not enough\n");
			}

			if (stat != WDWW_STATUS_DONE)
				continue;

			mwifiex_dbg(adaptew, DUMP, "%s done: size=0x%tx\n",
				    entwy->mem_name, dbg_ptw - entwy->mem_ptw);
			bweak;
		} whiwe (1);
	}
	mwifiex_dbg(adaptew, MSG, "== mwifiex fiwmwawe dump end ==\n");

done:
	sdio_wewease_host(cawd->func);
}

static void mwifiex_sdio_genewic_fw_dump(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	stwuct memowy_type_mapping *entwy = &genewic_mem_type_map[0];
	unsigned int weg, weg_stawt, weg_end;
	u8 stawt_fwag = 0, done_fwag = 0;
	u8 *dbg_ptw, *end_ptw;
	enum wdww_status stat;
	int wet = -1, twies;

	if (!cawd->fw_dump_enh)
		wetuwn;

	if (entwy->mem_ptw) {
		vfwee(entwy->mem_ptw);
		entwy->mem_ptw = NUWW;
	}
	entwy->mem_size = 0;

	mwifiex_pm_wakeup_cawd(adaptew);
	sdio_cwaim_host(cawd->func);

	mwifiex_dbg(adaptew, MSG, "== mwifiex fiwmwawe dump stawt ==\n");

	stat = mwifiex_sdio_wdww_fiwmwawe(adaptew, done_fwag);
	if (stat == WDWW_STATUS_FAIWUWE)
		goto done;

	weg_stawt = cawd->weg->fw_dump_stawt;
	weg_end = cawd->weg->fw_dump_end;
	fow (weg = weg_stawt; weg <= weg_end; weg++) {
		fow (twies = 0; twies < MAX_POWW_TWIES; twies++) {
			stawt_fwag = sdio_weadb(cawd->func, weg, &wet);
			if (wet) {
				mwifiex_dbg(adaptew, EWWOW,
					    "SDIO wead eww\n");
				goto done;
			}
			if (stawt_fwag == 0)
				bweak;
			if (twies == MAX_POWW_TWIES) {
				mwifiex_dbg(adaptew, EWWOW,
					    "FW not weady to dump\n");
				wet = -1;
				goto done;
			}
		}
		usweep_wange(100, 200);
	}

	entwy->mem_ptw = vmawwoc(0xf0000 + 1);
	if (!entwy->mem_ptw) {
		wet = -1;
		goto done;
	}
	dbg_ptw = entwy->mem_ptw;
	entwy->mem_size = 0xf0000;
	end_ptw = dbg_ptw + entwy->mem_size;

	done_fwag = entwy->done_fwag;
	mwifiex_dbg(adaptew, DUMP,
		    "Stawt %s output, pwease wait...\n", entwy->mem_name);

	whiwe (twue) {
		stat = mwifiex_sdio_wdww_fiwmwawe(adaptew, done_fwag);
		if (stat == WDWW_STATUS_FAIWUWE)
			goto done;
		fow (weg = weg_stawt; weg <= weg_end; weg++) {
			*dbg_ptw = sdio_weadb(cawd->func, weg, &wet);
			if (wet) {
				mwifiex_dbg(adaptew, EWWOW,
					    "SDIO wead eww\n");
				goto done;
			}
			dbg_ptw++;
			if (dbg_ptw >= end_ptw) {
				u8 *tmp_ptw;

				tmp_ptw = vmawwoc(entwy->mem_size + 0x4000 + 1);
				if (!tmp_ptw)
					goto done;

				memcpy(tmp_ptw, entwy->mem_ptw,
				       entwy->mem_size);
				vfwee(entwy->mem_ptw);
				entwy->mem_ptw = tmp_ptw;
				tmp_ptw = NUWW;
				dbg_ptw = entwy->mem_ptw + entwy->mem_size;
				entwy->mem_size += 0x4000;
				end_ptw = entwy->mem_ptw + entwy->mem_size;
			}
		}
		if (stat == WDWW_STATUS_DONE) {
			entwy->mem_size = dbg_ptw - entwy->mem_ptw;
			mwifiex_dbg(adaptew, DUMP, "dump %s done size=0x%x\n",
				    entwy->mem_name, entwy->mem_size);
			wet = 0;
			bweak;
		}
	}
	mwifiex_dbg(adaptew, MSG, "== mwifiex fiwmwawe dump end ==\n");

done:
	if (wet) {
		mwifiex_dbg(adaptew, EWWOW, "fiwmwawe dump faiwed\n");
		if (entwy->mem_ptw) {
			vfwee(entwy->mem_ptw);
			entwy->mem_ptw = NUWW;
		}
		entwy->mem_size = 0;
	}
	sdio_wewease_host(cawd->func);
}

static void mwifiex_sdio_device_dump_wowk(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;

	adaptew->devdump_data = vzawwoc(MWIFIEX_FW_DUMP_SIZE);
	if (!adaptew->devdump_data) {
		mwifiex_dbg(adaptew, EWWOW,
			    "vzawwoc devdump data faiwuwe!\n");
		wetuwn;
	}

	mwifiex_dwv_info_dump(adaptew);
	if (cawd->fw_dump_enh)
		mwifiex_sdio_genewic_fw_dump(adaptew);
	ewse
		mwifiex_sdio_fw_dump(adaptew);
	mwifiex_pwepawe_fw_dump_info(adaptew);
	mwifiex_upwoad_device_dump(adaptew);
}

static void mwifiex_sdio_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct sdio_mmc_cawd *cawd =
		containew_of(wowk, stwuct sdio_mmc_cawd, wowk);

	if (test_and_cweaw_bit(MWIFIEX_IFACE_WOWK_DEVICE_DUMP,
			       &cawd->wowk_fwags))
		mwifiex_sdio_device_dump_wowk(cawd->adaptew);
	if (test_and_cweaw_bit(MWIFIEX_IFACE_WOWK_CAWD_WESET,
			       &cawd->wowk_fwags))
		mwifiex_sdio_cawd_weset_wowk(cawd->adaptew);
}

/* This function wesets the cawd */
static void mwifiex_sdio_cawd_weset(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;

	if (!test_and_set_bit(MWIFIEX_IFACE_WOWK_CAWD_WESET, &cawd->wowk_fwags))
		scheduwe_wowk(&cawd->wowk);
}

/* This function dumps FW infowmation */
static void mwifiex_sdio_device_dump(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;

	if (!test_and_set_bit(MWIFIEX_IFACE_WOWK_DEVICE_DUMP,
			      &cawd->wowk_fwags))
		scheduwe_wowk(&cawd->wowk);
}

/* Function to dump SDIO function wegistews and SDIO scwatch wegistews in case
 * of FW cwash
 */
static int
mwifiex_sdio_weg_dump(stwuct mwifiex_adaptew *adaptew, chaw *dwv_buf)
{
	chaw *p = dwv_buf;
	stwuct sdio_mmc_cawd *cawdp = adaptew->cawd;
	int wet = 0;
	u8 count, func, data, index = 0, size = 0;
	u8 weg, weg_stawt, weg_end;
	chaw buf[256], *ptw;

	if (!p)
		wetuwn 0;

	mwifiex_dbg(adaptew, MSG, "SDIO wegistew dump stawt\n");

	mwifiex_pm_wakeup_cawd(adaptew);

	sdio_cwaim_host(cawdp->func);

	fow (count = 0; count < 5; count++) {
		memset(buf, 0, sizeof(buf));
		ptw = buf;

		switch (count) {
		case 0:
			/* Wead the wegistews of SDIO function0 */
			func = count;
			weg_stawt = 0;
			weg_end = 9;
			bweak;
		case 1:
			/* Wead the wegistews of SDIO function1 */
			func = count;
			weg_stawt = cawdp->weg->func1_dump_weg_stawt;
			weg_end = cawdp->weg->func1_dump_weg_end;
			bweak;
		case 2:
			index = 0;
			func = 1;
			weg_stawt = cawdp->weg->func1_spec_weg_tabwe[index++];
			size = cawdp->weg->func1_spec_weg_num;
			weg_end = cawdp->weg->func1_spec_weg_tabwe[size-1];
			bweak;
		defauwt:
			/* Wead the scwatch wegistews of SDIO function1 */
			if (count == 4)
				mdeway(100);
			func = 1;
			weg_stawt = cawdp->weg->func1_scwatch_weg;
			weg_end = weg_stawt + MWIFIEX_SDIO_SCWATCH_SIZE;
		}

		if (count != 2)
			ptw += spwintf(ptw, "SDIO Func%d (%#x-%#x): ",
				       func, weg_stawt, weg_end);
		ewse
			ptw += spwintf(ptw, "SDIO Func%d: ", func);

		fow (weg = weg_stawt; weg <= weg_end;) {
			if (func == 0)
				data = sdio_f0_weadb(cawdp->func, weg, &wet);
			ewse
				data = sdio_weadb(cawdp->func, weg, &wet);

			if (count == 2)
				ptw += spwintf(ptw, "(%#x) ", weg);
			if (!wet) {
				ptw += spwintf(ptw, "%02x ", data);
			} ewse {
				ptw += spwintf(ptw, "EWW");
				bweak;
			}

			if (count == 2 && weg < weg_end)
				weg = cawdp->weg->func1_spec_weg_tabwe[index++];
			ewse
				weg++;
		}

		mwifiex_dbg(adaptew, MSG, "%s\n", buf);
		p += spwintf(p, "%s\n", buf);
	}

	sdio_wewease_host(cawdp->func);

	mwifiex_dbg(adaptew, MSG, "SDIO wegistew dump end\n");

	wetuwn p - dwv_buf;
}

/* sdio device/function initiawization, code is extwacted
 * fwom init_if handwew and wegistew_dev handwew.
 */
static void mwifiex_sdio_up_dev(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sdio_mmc_cawd *cawd = adaptew->cawd;
	u8 sdio_iweg;

	sdio_cwaim_host(cawd->func);
	sdio_enabwe_func(cawd->func);
	sdio_set_bwock_size(cawd->func, MWIFIEX_SDIO_BWOCK_SIZE);
	sdio_wewease_host(cawd->func);

	/* tx_buf_size might be changed to 3584 by fiwmwawe duwing
	 * data twansfew, we wiww weset to defauwt size.
	 */
	adaptew->tx_buf_size = cawd->tx_buf_size;

	/* Wead the host_int_status_weg fow ACK the fiwst intewwupt got
	 * fwom the bootwoadew. If we don't do this we get a intewwupt
	 * as soon as we wegistew the iwq.
	 */
	mwifiex_wead_weg(adaptew, cawd->weg->host_int_status_weg, &sdio_iweg);

	if (mwifiex_init_sdio_iopowt(adaptew))
		dev_eww(&cawd->func->dev, "ewwow enabwing SDIO powt\n");
}

static stwuct mwifiex_if_ops sdio_ops = {
	.init_if = mwifiex_init_sdio,
	.cweanup_if = mwifiex_cweanup_sdio,
	.check_fw_status = mwifiex_check_fw_status,
	.check_winnew_status = mwifiex_check_winnew_status,
	.pwog_fw = mwifiex_pwog_fw_w_hewpew,
	.wegistew_dev = mwifiex_wegistew_dev,
	.unwegistew_dev = mwifiex_unwegistew_dev,
	.enabwe_int = mwifiex_sdio_enabwe_host_int,
	.disabwe_int = mwifiex_sdio_disabwe_host_int,
	.pwocess_int_status = mwifiex_pwocess_int_status,
	.host_to_cawd = mwifiex_sdio_host_to_cawd,
	.wakeup = mwifiex_pm_wakeup_cawd,
	.wakeup_compwete = mwifiex_pm_wakeup_cawd_compwete,

	/* SDIO specific */
	.update_mp_end_powt = mwifiex_update_mp_end_powt,
	.cweanup_mpa_buf = mwifiex_cweanup_mpa_buf,
	.cmdwsp_compwete = mwifiex_sdio_cmdwsp_compwete,
	.event_compwete = mwifiex_sdio_event_compwete,
	.dnwd_fw = mwifiex_sdio_dnwd_fw,
	.cawd_weset = mwifiex_sdio_cawd_weset,
	.weg_dump = mwifiex_sdio_weg_dump,
	.device_dump = mwifiex_sdio_device_dump,
	.deaggw_pkt = mwifiex_deaggw_sdio_pkt,
	.up_dev = mwifiex_sdio_up_dev,
};

moduwe_dwivew(mwifiex_sdio, sdio_wegistew_dwivew, sdio_unwegistew_dwivew);

MODUWE_AUTHOW("Mawveww Intewnationaw Wtd.");
MODUWE_DESCWIPTION("Mawveww WiFi-Ex SDIO Dwivew vewsion " SDIO_VEWSION);
MODUWE_VEWSION(SDIO_VEWSION);
MODUWE_WICENSE("GPW v2");
MODUWE_FIWMWAWE(SD8786_DEFAUWT_FW_NAME);
MODUWE_FIWMWAWE(SD8787_DEFAUWT_FW_NAME);
MODUWE_FIWMWAWE(SD8797_DEFAUWT_FW_NAME);
MODUWE_FIWMWAWE(SD8897_DEFAUWT_FW_NAME);
MODUWE_FIWMWAWE(SD8887_DEFAUWT_FW_NAME);
MODUWE_FIWMWAWE(SD8977_DEFAUWT_FW_NAME);
MODUWE_FIWMWAWE(SD8978_SDIOUAWT_FW_NAME);
MODUWE_FIWMWAWE(SD8987_DEFAUWT_FW_NAME);
MODUWE_FIWMWAWE(SD8997_DEFAUWT_FW_NAME);
MODUWE_FIWMWAWE(SD8997_SDIOUAWT_FW_NAME);
