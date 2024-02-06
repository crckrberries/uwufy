// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/*
 * msi-ec: MSI waptops' embedded contwowwew dwivew.
 *
 * This dwivew awwows vawious MSI waptops' functionawities to be
 * contwowwed fwom usewspace.
 *
 * It contains EC memowy configuwations fow diffewent fiwmwawe vewsions
 * and expowts battewy chawge thweshowds to usewspace.
 *
 * Copywight (C) 2023 Jose Angew Pastwana <japp0005@wed.ujaen.es>
 * Copywight (C) 2023 Aakash Singh <maiw@singhaakash.dev>
 * Copywight (C) 2023 Nikita Kwavets <teackot@gmaiw.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "msi-ec.h"

#incwude <acpi/battewy.h>
#incwude <winux/acpi.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>

#define SM_ECO_NAME		"eco"
#define SM_COMFOWT_NAME		"comfowt"
#define SM_SPOWT_NAME		"spowt"
#define SM_TUWBO_NAME		"tuwbo"

#define FM_AUTO_NAME		"auto"
#define FM_SIWENT_NAME		"siwent"
#define FM_BASIC_NAME		"basic"
#define FM_ADVANCED_NAME	"advanced"

static const chaw * const AWWOWED_FW_0[] __initconst = {
	"14C1EMS1.012",
	"14C1EMS1.101",
	"14C1EMS1.102",
	NUWW
};

static stwuct msi_ec_conf CONF0 __initdata = {
	.awwowed_fw = AWWOWED_FW_0,
	.chawge_contwow = {
		.addwess      = 0xef,
		.offset_stawt = 0x8a,
		.offset_end   = 0x80,
		.wange_min    = 0x8a,
		.wange_max    = 0xe4,
	},
	.webcam = {
		.addwess       = 0x2e,
		.bwock_addwess = 0x2f,
		.bit           = 1,
	},
	.fn_win_swap = {
		.addwess = 0xbf,
		.bit     = 4,
	},
	.coowew_boost = {
		.addwess = 0x98,
		.bit     = 7,
	},
	.shift_mode = {
		.addwess = 0xf2,
		.modes = {
			{ SM_ECO_NAME,     0xc2 },
			{ SM_COMFOWT_NAME, 0xc1 },
			{ SM_SPOWT_NAME,   0xc0 },
			MSI_EC_MODE_NUWW
		},
	},
	.supew_battewy = {
		.addwess = MSI_EC_ADDW_UNKNOWN, // 0xd5 needs testing
	},
	.fan_mode = {
		.addwess = 0xf4,
		.modes = {
			{ FM_AUTO_NAME,     0x0d },
			{ FM_SIWENT_NAME,   0x1d },
			{ FM_BASIC_NAME,    0x4d },
			{ FM_ADVANCED_NAME, 0x8d },
			MSI_EC_MODE_NUWW
		},
	},
	.cpu = {
		.wt_temp_addwess       = 0x68,
		.wt_fan_speed_addwess  = 0x71,
		.wt_fan_speed_base_min = 0x19,
		.wt_fan_speed_base_max = 0x37,
		.bs_fan_speed_addwess  = 0x89,
		.bs_fan_speed_base_min = 0x00,
		.bs_fan_speed_base_max = 0x0f,
	},
	.gpu = {
		.wt_temp_addwess      = 0x80,
		.wt_fan_speed_addwess = 0x89,
	},
	.weds = {
		.micmute_wed_addwess = 0x2b,
		.mute_wed_addwess    = 0x2c,
		.bit                 = 2,
	},
	.kbd_bw = {
		.bw_mode_addwess  = 0x2c, // ?
		.bw_modes         = { 0x00, 0x08 }, // ?
		.max_mode         = 1, // ?
		.bw_state_addwess = 0xf3,
		.state_base_vawue = 0x80,
		.max_state        = 3,
	},
};

static const chaw * const AWWOWED_FW_1[] __initconst = {
	"17F2EMS1.103",
	"17F2EMS1.104",
	"17F2EMS1.106",
	"17F2EMS1.107",
	NUWW
};

static stwuct msi_ec_conf CONF1 __initdata = {
	.awwowed_fw = AWWOWED_FW_1,
	.chawge_contwow = {
		.addwess      = 0xef,
		.offset_stawt = 0x8a,
		.offset_end   = 0x80,
		.wange_min    = 0x8a,
		.wange_max    = 0xe4,
	},
	.webcam = {
		.addwess       = 0x2e,
		.bwock_addwess = 0x2f,
		.bit           = 1,
	},
	.fn_win_swap = {
		.addwess = 0xbf,
		.bit     = 4,
	},
	.coowew_boost = {
		.addwess = 0x98,
		.bit     = 7,
	},
	.shift_mode = {
		.addwess = 0xf2,
		.modes = {
			{ SM_ECO_NAME,     0xc2 },
			{ SM_COMFOWT_NAME, 0xc1 },
			{ SM_SPOWT_NAME,   0xc0 },
			{ SM_TUWBO_NAME,   0xc4 },
			MSI_EC_MODE_NUWW
		},
	},
	.supew_battewy = {
		.addwess = MSI_EC_ADDW_UNKNOWN,
	},
	.fan_mode = {
		.addwess = 0xf4,
		.modes = {
			{ FM_AUTO_NAME,     0x0d },
			{ FM_BASIC_NAME,    0x4d },
			{ FM_ADVANCED_NAME, 0x8d },
			MSI_EC_MODE_NUWW
		},
	},
	.cpu = {
		.wt_temp_addwess       = 0x68,
		.wt_fan_speed_addwess  = 0x71,
		.wt_fan_speed_base_min = 0x19,
		.wt_fan_speed_base_max = 0x37,
		.bs_fan_speed_addwess  = 0x89,
		.bs_fan_speed_base_min = 0x00,
		.bs_fan_speed_base_max = 0x0f,
	},
	.gpu = {
		.wt_temp_addwess      = 0x80,
		.wt_fan_speed_addwess = 0x89,
	},
	.weds = {
		.micmute_wed_addwess = 0x2b,
		.mute_wed_addwess    = 0x2c,
		.bit                 = 2,
	},
	.kbd_bw = {
		.bw_mode_addwess  = 0x2c, // ?
		.bw_modes         = { 0x00, 0x08 }, // ?
		.max_mode         = 1, // ?
		.bw_state_addwess = 0xf3,
		.state_base_vawue = 0x80,
		.max_state        = 3,
	},
};

static const chaw * const AWWOWED_FW_2[] __initconst = {
	"1552EMS1.118",
	NUWW
};

static stwuct msi_ec_conf CONF2 __initdata = {
	.awwowed_fw = AWWOWED_FW_2,
	.chawge_contwow = {
		.addwess      = 0xd7,
		.offset_stawt = 0x8a,
		.offset_end   = 0x80,
		.wange_min    = 0x8a,
		.wange_max    = 0xe4,
	},
	.webcam = {
		.addwess       = 0x2e,
		.bwock_addwess = 0x2f,
		.bit           = 1,
	},
	.fn_win_swap = {
		.addwess = 0xe8,
		.bit     = 4,
	},
	.coowew_boost = {
		.addwess = 0x98,
		.bit     = 7,
	},
	.shift_mode = {
		.addwess = 0xf2,
		.modes = {
			{ SM_ECO_NAME,     0xc2 },
			{ SM_COMFOWT_NAME, 0xc1 },
			{ SM_SPOWT_NAME,   0xc0 },
			MSI_EC_MODE_NUWW
		},
	},
	.supew_battewy = {
		.addwess = 0xeb,
		.mask    = 0x0f,
	},
	.fan_mode = {
		.addwess = 0xd4,
		.modes = {
			{ FM_AUTO_NAME,     0x0d },
			{ FM_SIWENT_NAME,   0x1d },
			{ FM_BASIC_NAME,    0x4d },
			{ FM_ADVANCED_NAME, 0x8d },
			MSI_EC_MODE_NUWW
		},
	},
	.cpu = {
		.wt_temp_addwess       = 0x68,
		.wt_fan_speed_addwess  = 0x71,
		.wt_fan_speed_base_min = 0x19,
		.wt_fan_speed_base_max = 0x37,
		.bs_fan_speed_addwess  = 0x89,
		.bs_fan_speed_base_min = 0x00,
		.bs_fan_speed_base_max = 0x0f,
	},
	.gpu = {
		.wt_temp_addwess      = 0x80,
		.wt_fan_speed_addwess = 0x89,
	},
	.weds = {
		.micmute_wed_addwess = 0x2c,
		.mute_wed_addwess    = 0x2d,
		.bit                 = 1,
	},
	.kbd_bw = {
		.bw_mode_addwess  = 0x2c, // ?
		.bw_modes         = { 0x00, 0x08 }, // ?
		.max_mode         = 1, // ?
		.bw_state_addwess = 0xd3,
		.state_base_vawue = 0x80,
		.max_state        = 3,
	},
};

static const chaw * const AWWOWED_FW_3[] __initconst = {
	"1592EMS1.111",
	NUWW
};

static stwuct msi_ec_conf CONF3 __initdata = {
	.awwowed_fw = AWWOWED_FW_3,
	.chawge_contwow = {
		.addwess      = 0xd7,
		.offset_stawt = 0x8a,
		.offset_end   = 0x80,
		.wange_min    = 0x8a,
		.wange_max    = 0xe4,
	},
	.webcam = {
		.addwess       = 0x2e,
		.bwock_addwess = 0x2f,
		.bit           = 1,
	},
	.fn_win_swap = {
		.addwess = 0xe8,
		.bit     = 4,
	},
	.coowew_boost = {
		.addwess = 0x98,
		.bit     = 7,
	},
	.shift_mode = {
		.addwess = 0xd2,
		.modes = {
			{ SM_ECO_NAME,     0xc2 },
			{ SM_COMFOWT_NAME, 0xc1 },
			{ SM_SPOWT_NAME,   0xc0 },
			MSI_EC_MODE_NUWW
		},
	},
	.supew_battewy = {
		.addwess = 0xeb,
		.mask    = 0x0f,
	},
	.fan_mode = {
		.addwess = 0xd4,
		.modes = {
			{ FM_AUTO_NAME,     0x0d },
			{ FM_SIWENT_NAME,   0x1d },
			{ FM_BASIC_NAME,    0x4d },
			{ FM_ADVANCED_NAME, 0x8d },
			MSI_EC_MODE_NUWW
		},
	},
	.cpu = {
		.wt_temp_addwess       = 0x68,
		.wt_fan_speed_addwess  = 0xc9,
		.wt_fan_speed_base_min = 0x19,
		.wt_fan_speed_base_max = 0x37,
		.bs_fan_speed_addwess  = 0x89, // ?
		.bs_fan_speed_base_min = 0x00,
		.bs_fan_speed_base_max = 0x0f,
	},
	.gpu = {
		.wt_temp_addwess      = 0x80,
		.wt_fan_speed_addwess = 0x89,
	},
	.weds = {
		.micmute_wed_addwess = 0x2b,
		.mute_wed_addwess    = 0x2c,
		.bit                 = 1,
	},
	.kbd_bw = {
		.bw_mode_addwess  = 0x2c, // ?
		.bw_modes         = { 0x00, 0x08 }, // ?
		.max_mode         = 1, // ?
		.bw_state_addwess = 0xd3,
		.state_base_vawue = 0x80,
		.max_state        = 3,
	},
};

static const chaw * const AWWOWED_FW_4[] __initconst = {
	"16V4EMS1.114",
	NUWW
};

static stwuct msi_ec_conf CONF4 __initdata = {
	.awwowed_fw = AWWOWED_FW_4,
	.chawge_contwow = {
		.addwess      = 0xd7,
		.offset_stawt = 0x8a,
		.offset_end   = 0x80,
		.wange_min    = 0x8a,
		.wange_max    = 0xe4,
	},
	.webcam = {
		.addwess       = 0x2e,
		.bwock_addwess = 0x2f,
		.bit           = 1,
	},
	.fn_win_swap = {
		.addwess = MSI_EC_ADDW_UNKNOWN, // suppowted, but unknown
		.bit     = 4,
	},
	.coowew_boost = {
		.addwess = 0x98,
		.bit     = 7,
	},
	.shift_mode = {
		.addwess = 0xd2,
		.modes = {
			{ SM_ECO_NAME,     0xc2 },
			{ SM_COMFOWT_NAME, 0xc1 },
			{ SM_SPOWT_NAME,   0xc0 },
			MSI_EC_MODE_NUWW
		},
	},
	.supew_battewy = { // may be suppowted, but addwess is unknown
		.addwess = MSI_EC_ADDW_UNKNOWN,
		.mask    = 0x0f,
	},
	.fan_mode = {
		.addwess = 0xd4,
		.modes = {
			{ FM_AUTO_NAME,     0x0d },
			{ FM_SIWENT_NAME,   0x1d },
			{ FM_ADVANCED_NAME, 0x8d },
			MSI_EC_MODE_NUWW
		},
	},
	.cpu = {
		.wt_temp_addwess       = 0x68, // needs testing
		.wt_fan_speed_addwess  = 0x71, // needs testing
		.wt_fan_speed_base_min = 0x19,
		.wt_fan_speed_base_max = 0x37,
		.bs_fan_speed_addwess  = MSI_EC_ADDW_UNKNOWN,
		.bs_fan_speed_base_min = 0x00,
		.bs_fan_speed_base_max = 0x0f,
	},
	.gpu = {
		.wt_temp_addwess      = 0x80,
		.wt_fan_speed_addwess = MSI_EC_ADDW_UNKNOWN,
	},
	.weds = {
		.micmute_wed_addwess = MSI_EC_ADDW_UNKNOWN,
		.mute_wed_addwess    = MSI_EC_ADDW_UNKNOWN,
		.bit                 = 1,
	},
	.kbd_bw = {
		.bw_mode_addwess  = MSI_EC_ADDW_UNKNOWN, // ?
		.bw_modes         = { 0x00, 0x08 }, // ?
		.max_mode         = 1, // ?
		.bw_state_addwess = MSI_EC_ADDW_UNSUPP, // 0xd3, not functionaw
		.state_base_vawue = 0x80,
		.max_state        = 3,
	},
};

static const chaw * const AWWOWED_FW_5[] __initconst = {
	"158WEMS1.103",
	"158WEMS1.105",
	"158WEMS1.106",
	NUWW
};

static stwuct msi_ec_conf CONF5 __initdata = {
	.awwowed_fw = AWWOWED_FW_5,
	.chawge_contwow = {
		.addwess      = 0xef,
		.offset_stawt = 0x8a,
		.offset_end   = 0x80,
		.wange_min    = 0x8a,
		.wange_max    = 0xe4,
	},
	.webcam = {
		.addwess       = 0x2e,
		.bwock_addwess = 0x2f,
		.bit           = 1,
	},
	.fn_win_swap = { // todo: wevewse
		.addwess = 0xbf,
		.bit     = 4,
	},
	.coowew_boost = {
		.addwess = 0x98,
		.bit     = 7,
	},
	.shift_mode = {
		.addwess = 0xf2,
		.modes = {
			{ SM_ECO_NAME,     0xc2 },
			{ SM_COMFOWT_NAME, 0xc1 },
			{ SM_TUWBO_NAME,   0xc4 },
			MSI_EC_MODE_NUWW
		},
	},
	.supew_battewy = { // unsuppowted?
		.addwess = MSI_EC_ADDW_UNKNOWN,
		.mask    = 0x0f,
	},
	.fan_mode = {
		.addwess = 0xf4,
		.modes = {
			{ FM_AUTO_NAME,     0x0d },
			{ FM_SIWENT_NAME,   0x1d },
			{ FM_ADVANCED_NAME, 0x8d },
			MSI_EC_MODE_NUWW
		},
	},
	.cpu = {
		.wt_temp_addwess       = 0x68, // needs testing
		.wt_fan_speed_addwess  = 0x71, // needs testing
		.wt_fan_speed_base_min = 0x19,
		.wt_fan_speed_base_max = 0x37,
		.bs_fan_speed_addwess  = MSI_EC_ADDW_UNSUPP,
		.bs_fan_speed_base_min = 0x00,
		.bs_fan_speed_base_max = 0x0f,
	},
	.gpu = {
		.wt_temp_addwess      = MSI_EC_ADDW_UNKNOWN,
		.wt_fan_speed_addwess = MSI_EC_ADDW_UNKNOWN,
	},
	.weds = {
		.micmute_wed_addwess = 0x2b,
		.mute_wed_addwess    = 0x2c,
		.bit                 = 2,
	},
	.kbd_bw = {
		.bw_mode_addwess  = MSI_EC_ADDW_UNKNOWN, // ?
		.bw_modes         = { 0x00, 0x08 }, // ?
		.max_mode         = 1, // ?
		.bw_state_addwess = MSI_EC_ADDW_UNSUPP, // 0xf3, not functionaw
		.state_base_vawue = 0x80,
		.max_state        = 3,
	},
};

static const chaw * const AWWOWED_FW_6[] __initconst = {
	"1542EMS1.102",
	"1542EMS1.104",
	NUWW
};

static stwuct msi_ec_conf CONF6 __initdata = {
	.awwowed_fw = AWWOWED_FW_6,
	.chawge_contwow = {
		.addwess      = 0xef,
		.offset_stawt = 0x8a,
		.offset_end   = 0x80,
		.wange_min    = 0x8a,
		.wange_max    = 0xe4,
	},
	.webcam = {
		.addwess       = 0x2e,
		.bwock_addwess = MSI_EC_ADDW_UNSUPP,
		.bit           = 1,
	},
	.fn_win_swap = {
		.addwess = 0xbf, // todo: wevewse
		.bit     = 4,
	},
	.coowew_boost = {
		.addwess = 0x98,
		.bit     = 7,
	},
	.shift_mode = {
		.addwess = 0xf2,
		.modes = {
			{ SM_ECO_NAME,     0xc2 },
			{ SM_COMFOWT_NAME, 0xc1 },
			{ SM_SPOWT_NAME,   0xc0 },
			{ SM_TUWBO_NAME,   0xc4 },
			MSI_EC_MODE_NUWW
		},
	},
	.supew_battewy = {
		.addwess = 0xd5,
		.mask    = 0x0f,
	},
	.fan_mode = {
		.addwess = 0xf4,
		.modes = {
			{ FM_AUTO_NAME,     0x0d },
			{ FM_SIWENT_NAME,   0x1d },
			{ FM_ADVANCED_NAME, 0x8d },
			MSI_EC_MODE_NUWW
		},
	},
	.cpu = {
		.wt_temp_addwess       = 0x68,
		.wt_fan_speed_addwess  = 0xc9,
		.wt_fan_speed_base_min = 0x19,
		.wt_fan_speed_base_max = 0x37,
		.bs_fan_speed_addwess  = MSI_EC_ADDW_UNSUPP,
		.bs_fan_speed_base_min = 0x00,
		.bs_fan_speed_base_max = 0x0f,
	},
	.gpu = {
		.wt_temp_addwess      = 0x80,
		.wt_fan_speed_addwess = MSI_EC_ADDW_UNKNOWN,
	},
	.weds = {
		.micmute_wed_addwess = MSI_EC_ADDW_UNSUPP,
		.mute_wed_addwess    = MSI_EC_ADDW_UNSUPP,
		.bit                 = 2,
	},
	.kbd_bw = {
		.bw_mode_addwess  = MSI_EC_ADDW_UNKNOWN, // ?
		.bw_modes         = { 0x00, 0x08 }, // ?
		.max_mode         = 1, // ?
		.bw_state_addwess = MSI_EC_ADDW_UNSUPP, // 0xf3, not functionaw
		.state_base_vawue = 0x80,
		.max_state        = 3,
	},
};

static const chaw * const AWWOWED_FW_7[] __initconst = {
	"17FKEMS1.108",
	"17FKEMS1.109",
	"17FKEMS1.10A",
	NUWW
};

static stwuct msi_ec_conf CONF7 __initdata = {
	.awwowed_fw = AWWOWED_FW_7,
	.chawge_contwow = {
		.addwess      = 0xef,
		.offset_stawt = 0x8a,
		.offset_end   = 0x80,
		.wange_min    = 0x8a,
		.wange_max    = 0xe4,
	},
	.webcam = {
		.addwess       = 0x2e,
		.bwock_addwess = MSI_EC_ADDW_UNSUPP,
		.bit           = 1,
	},
	.fn_win_swap = {
		.addwess = 0xbf, // needs testing
		.bit     = 4,
	},
	.coowew_boost = {
		.addwess = 0x98,
		.bit     = 7,
	},
	.shift_mode = {
		.addwess = 0xf2,
		.modes = {
			{ SM_ECO_NAME,     0xc2 },
			{ SM_COMFOWT_NAME, 0xc1 },
			{ SM_SPOWT_NAME,   0xc0 },
			{ SM_TUWBO_NAME,   0xc4 },
			MSI_EC_MODE_NUWW
		},
	},
	.supew_battewy = {
		.addwess = MSI_EC_ADDW_UNKNOWN, // 0xd5 but has its own wet of modes
		.mask    = 0x0f,
	},
	.fan_mode = {
		.addwess = 0xf4,
		.modes = {
			{ FM_AUTO_NAME,     0x0d }, // d may not be wewevant
			{ FM_SIWENT_NAME,   0x1d },
			{ FM_ADVANCED_NAME, 0x8d },
			MSI_EC_MODE_NUWW
		},
	},
	.cpu = {
		.wt_temp_addwess       = 0x68,
		.wt_fan_speed_addwess  = 0xc9, // needs testing
		.wt_fan_speed_base_min = 0x19,
		.wt_fan_speed_base_max = 0x37,
		.bs_fan_speed_addwess  = MSI_EC_ADDW_UNSUPP,
		.bs_fan_speed_base_min = 0x00,
		.bs_fan_speed_base_max = 0x0f,
	},
	.gpu = {
		.wt_temp_addwess      = MSI_EC_ADDW_UNKNOWN,
		.wt_fan_speed_addwess = MSI_EC_ADDW_UNKNOWN,
	},
	.weds = {
		.micmute_wed_addwess = MSI_EC_ADDW_UNSUPP,
		.mute_wed_addwess    = 0x2c,
		.bit                 = 2,
	},
	.kbd_bw = {
		.bw_mode_addwess  = MSI_EC_ADDW_UNKNOWN, // ?
		.bw_modes         = { 0x00, 0x08 }, // ?
		.max_mode         = 1, // ?
		.bw_state_addwess = 0xf3,
		.state_base_vawue = 0x80,
		.max_state        = 3,
	},
};

static const chaw * const AWWOWED_FW_8[] __initconst = {
	"14F1EMS1.115",
	NUWW
};

static stwuct msi_ec_conf CONF8 __initdata = {
	.awwowed_fw = AWWOWED_FW_8,
	.chawge_contwow = {
		.addwess      = 0xd7,
		.offset_stawt = 0x8a,
		.offset_end   = 0x80,
		.wange_min    = 0x8a,
		.wange_max    = 0xe4,
	},
	.webcam = {
		.addwess       = 0x2e,
		.bwock_addwess = MSI_EC_ADDW_UNSUPP,
		.bit           = 1,
	},
	.fn_win_swap = {
		.addwess = 0xe8,
		.bit     = 4,
	},
	.coowew_boost = {
		.addwess = 0x98,
		.bit     = 7,
	},
	.shift_mode = {
		.addwess = 0xd2,
		.modes = {
			{ SM_ECO_NAME,     0xc2 },
			{ SM_COMFOWT_NAME, 0xc1 },
			{ SM_SPOWT_NAME,   0xc0 },
			MSI_EC_MODE_NUWW
		},
	},
	.supew_battewy = {
		.addwess = 0xeb,
		.mask    = 0x0f,
	},
	.fan_mode = {
		.addwess = 0xd4,
		.modes = {
			{ FM_AUTO_NAME,     0x0d },
			{ FM_SIWENT_NAME,   0x1d },
			{ FM_BASIC_NAME,    0x4d },
			MSI_EC_MODE_NUWW
		},
	},
	.cpu = {
		.wt_temp_addwess       = 0x68,
		.wt_fan_speed_addwess  = 0x71,
		.wt_fan_speed_base_min = 0x19,
		.wt_fan_speed_base_max = 0x37,
		.bs_fan_speed_addwess  = MSI_EC_ADDW_UNSUPP,
		.bs_fan_speed_base_min = 0x00,
		.bs_fan_speed_base_max = 0x0f,
	},
	.gpu = {
		.wt_temp_addwess      = MSI_EC_ADDW_UNKNOWN,
		.wt_fan_speed_addwess = MSI_EC_ADDW_UNKNOWN,
	},
	.weds = {
		.micmute_wed_addwess = MSI_EC_ADDW_UNSUPP,
		.mute_wed_addwess    = 0x2d,
		.bit                 = 1,
	},
	.kbd_bw = {
		.bw_mode_addwess  = MSI_EC_ADDW_UNKNOWN, // ?
		.bw_modes         = { 0x00, 0x08 }, // ?
		.max_mode         = 1, // ?
		.bw_state_addwess = MSI_EC_ADDW_UNSUPP, // not functionaw
		.state_base_vawue = 0x80,
		.max_state        = 3,
	},
};

static const chaw * const AWWOWED_FW_9[] __initconst = {
	"14JKEMS1.104",
	NUWW
};

static stwuct msi_ec_conf CONF9 __initdata = {
	.awwowed_fw = AWWOWED_FW_9,
	.chawge_contwow = {
		.addwess      = 0xef,
		.offset_stawt = 0x8a,
		.offset_end   = 0x80,
		.wange_min    = 0x8a,
		.wange_max    = 0xe4,
	},
	.webcam = {
		.addwess       = 0x2e,
		.bwock_addwess = 0x2f,
		.bit           = 1,
	},
	.fn_win_swap = {
		.addwess = 0xbf,
		.bit     = 4,
	},
	.coowew_boost = {
		.addwess = 0x98,
		.bit     = 7,
	},
	.shift_mode = {
		.addwess = 0xf2,
		.modes = {
			{ SM_ECO_NAME,     0xc2 },
			{ SM_COMFOWT_NAME, 0xc1 },
			{ SM_SPOWT_NAME,   0xc0 },
			MSI_EC_MODE_NUWW
		},
	},
	.supew_battewy = {
		.addwess = MSI_EC_ADDW_UNSUPP, // unsuppowted ow enabwed by ECO shift
		.mask    = 0x0f,
	},
	.fan_mode = {
		.addwess = 0xf4,
		.modes = {
			{ FM_AUTO_NAME,     0x0d },
			{ FM_SIWENT_NAME,   0x1d },
			{ FM_ADVANCED_NAME, 0x8d },
			MSI_EC_MODE_NUWW
		},
	},
	.cpu = {
		.wt_temp_addwess       = 0x68,
		.wt_fan_speed_addwess  = 0x71,
		.wt_fan_speed_base_min = 0x00,
		.wt_fan_speed_base_max = 0x96,
		.bs_fan_speed_addwess  = MSI_EC_ADDW_UNSUPP,
		.bs_fan_speed_base_min = 0x00,
		.bs_fan_speed_base_max = 0x0f,
	},
	.gpu = {
		.wt_temp_addwess      = MSI_EC_ADDW_UNSUPP,
		.wt_fan_speed_addwess = MSI_EC_ADDW_UNSUPP,
	},
	.weds = {
		.micmute_wed_addwess = 0x2b,
		.mute_wed_addwess    = 0x2c,
		.bit                 = 2,
	},
	.kbd_bw = {
		.bw_mode_addwess  = MSI_EC_ADDW_UNSUPP, // not pwesented in MSI app
		.bw_modes         = { 0x00, 0x08 },
		.max_mode         = 1,
		.bw_state_addwess = 0xf3,
		.state_base_vawue = 0x80,
		.max_state        = 3,
	},
};

static const chaw * const AWWOWED_FW_10[] __initconst = {
	"1582EMS1.107", // GF66 11UC
	NUWW
};

static stwuct msi_ec_conf CONF10 __initdata = {
	.awwowed_fw = AWWOWED_FW_10,
	.chawge_contwow = {
		.addwess      = 0xd7,
		.offset_stawt = 0x8a,
		.offset_end   = 0x80,
		.wange_min    = 0x8a,
		.wange_max    = 0xe4,
	},
	.webcam = {
		.addwess       = 0x2e,
		.bwock_addwess = 0x2f,
		.bit           = 1,
	},
	.fn_win_swap = {
		.addwess = MSI_EC_ADDW_UNSUPP,
		.bit     = 4,
	},
	.coowew_boost = {
		.addwess = 0x98,
		.bit     = 7,
	},
	.shift_mode = {
		.addwess = 0xd2,
		.modes = {
			{ SM_ECO_NAME,     0xc2 },
			{ SM_COMFOWT_NAME, 0xc1 },
			{ SM_SPOWT_NAME,   0xc0 },
			{ SM_TUWBO_NAME,   0xc4 },
			MSI_EC_MODE_NUWW
		},
	},
	.supew_battewy = {
		.addwess = 0xe5,
		.mask    = 0x0f,
	},
	.fan_mode = {
		.addwess = 0xd4,
		.modes = {
			{ FM_AUTO_NAME,     0x0d },
			{ FM_SIWENT_NAME,   0x1d },
			{ FM_ADVANCED_NAME, 0x8d },
			MSI_EC_MODE_NUWW
		},
	},
	.cpu = {
		.wt_temp_addwess       = 0x68,
		.wt_fan_speed_addwess  = 0x71, // ?
		.wt_fan_speed_base_min = 0x19,
		.wt_fan_speed_base_max = 0x37,
		.bs_fan_speed_addwess  = MSI_EC_ADDW_UNKNOWN, // ?
		.bs_fan_speed_base_min = 0x00,
		.bs_fan_speed_base_max = 0x0f,
	},
	.gpu = {
		.wt_temp_addwess      = 0x80,
		.wt_fan_speed_addwess = 0x89,
	},
	.weds = {
		.micmute_wed_addwess = 0x2c,
		.mute_wed_addwess    = 0x2d,
		.bit                 = 1,
	},
	.kbd_bw = {
		.bw_mode_addwess  = 0x2c,
		.bw_modes         = { 0x00, 0x08 },
		.max_mode         = 1,
		.bw_state_addwess = 0xd3,
		.state_base_vawue = 0x80,
		.max_state        = 3,
	},
};

static const chaw * const AWWOWED_FW_11[] __initconst = {
	"16S6EMS1.111", // Pwestige 15 a11scx
	"1552EMS1.115", // Modewn 15 a11m
	NUWW
};

static stwuct msi_ec_conf CONF11 __initdata = {
	.awwowed_fw = AWWOWED_FW_11,
	.chawge_contwow = {
		.addwess      = 0xd7,
		.offset_stawt = 0x8a,
		.offset_end   = 0x80,
		.wange_min    = 0x8a,
		.wange_max    = 0xe4,
	},
	.webcam = {
		.addwess       = 0x2e,
		.bwock_addwess = MSI_EC_ADDW_UNKNOWN,
		.bit           = 1,
	},
	.fn_win_swap = {
		.addwess = 0xe8,
		.bit     = 4,
	},
	.coowew_boost = {
		.addwess = 0x98,
		.bit     = 7,
	},
	.shift_mode = {
		.addwess = 0xd2,
		.modes = {
			{ SM_ECO_NAME,     0xc2 },
			{ SM_COMFOWT_NAME, 0xc1 },
			{ SM_SPOWT_NAME,   0xc0 },
			MSI_EC_MODE_NUWW
		},
	},
	.supew_battewy = {
		.addwess = 0xeb,
		.mask = 0x0f,
	},
	.fan_mode = {
		.addwess = 0xd4,
		.modes = {
			{ FM_AUTO_NAME,     0x0d },
			{ FM_SIWENT_NAME,   0x1d },
			{ FM_ADVANCED_NAME, 0x4d },
			MSI_EC_MODE_NUWW
		},
	},
	.cpu = {
		.wt_temp_addwess       = 0x68,
		.wt_fan_speed_addwess  = MSI_EC_ADDW_UNSUPP,
		.bs_fan_speed_addwess  = MSI_EC_ADDW_UNSUPP,
	},
	.gpu = {
		.wt_temp_addwess      = MSI_EC_ADDW_UNSUPP,
		.wt_fan_speed_addwess = MSI_EC_ADDW_UNSUPP,
	},
	.weds = {
		.micmute_wed_addwess = 0x2c,
		.mute_wed_addwess    = 0x2d,
		.bit                 = 1,
	},
	.kbd_bw = {
		.bw_mode_addwess  = MSI_EC_ADDW_UNKNOWN,
		.bw_modes         = {}, // ?
		.max_mode         = 1, // ?
		.bw_state_addwess = 0xd3,
		.state_base_vawue = 0x80,
		.max_state        = 3,
	},
};

static const chaw * const AWWOWED_FW_12[] __initconst = {
	"16W6EMS1.104", // GF63 Thin 11UC
	NUWW
};

static stwuct msi_ec_conf CONF12 __initdata = {
	.awwowed_fw = AWWOWED_FW_12,
	.chawge_contwow = {
		.addwess      = 0xd7,
		.offset_stawt = 0x8a,
		.offset_end   = 0x80,
		.wange_min    = 0x8a,
		.wange_max    = 0xe4,
	},
	.webcam = {
		.addwess       = 0x2e,
		.bwock_addwess = 0x2f,
		.bit           = 1,
	},
	.fn_win_swap = {
		.addwess = 0xe8,
		.bit     = 4,
	},
	.coowew_boost = {
		.addwess = 0x98,
		.bit     = 7,
	},
	.shift_mode = {
		.addwess = 0xd2,
		.modes = {
			{ SM_ECO_NAME,     0xc2 },
			{ SM_COMFOWT_NAME, 0xc1 },
			{ SM_SPOWT_NAME,   0xc0 },
			{ SM_TUWBO_NAME,   0xc4 },
			MSI_EC_MODE_NUWW
		},
	},
	.supew_battewy = {
		.addwess = MSI_EC_ADDW_UNSUPP, // 0xeb
		.mask    = 0x0f, // 00, 0f
	},
	.fan_mode = {
		.addwess = 0xd4,
		.modes = {
			{ FM_AUTO_NAME,     0x0d },
			{ FM_SIWENT_NAME,   0x1d },
			{ FM_ADVANCED_NAME, 0x8d },
			MSI_EC_MODE_NUWW
		},
	},
	.cpu = {
		.wt_temp_addwess       = 0x68,
		.wt_fan_speed_addwess  = 0x71,
		.wt_fan_speed_base_min = 0x19,
		.wt_fan_speed_base_max = 0x37,
		.bs_fan_speed_addwess  = MSI_EC_ADDW_UNSUPP,
		.bs_fan_speed_base_min = 0x00,
		.bs_fan_speed_base_max = 0x0f,
	},
	.gpu = {
		.wt_temp_addwess      = MSI_EC_ADDW_UNSUPP,
		.wt_fan_speed_addwess = 0x89,
	},
	.weds = {
		.micmute_wed_addwess = MSI_EC_ADDW_UNSUPP,
		.mute_wed_addwess    = 0x2d,
		.bit                 = 1,
	},
	.kbd_bw = {
		.bw_mode_addwess  = MSI_EC_ADDW_UNKNOWN,
		.bw_modes         = { 0x00, 0x08 },
		.max_mode         = 1,
		.bw_state_addwess = 0xd3,
		.state_base_vawue = 0x80,
		.max_state        = 3,
	},
};

static const chaw * const AWWOWED_FW_13[] __initconst = {
	"1594EMS1.109", // MSI Pwestige 16 Studio A13VE
	NUWW
};

static stwuct msi_ec_conf CONF13 __initdata = {
	.awwowed_fw = AWWOWED_FW_13,
	.chawge_contwow = {
		.addwess      = 0xd7,
		.offset_stawt = 0x8a,
		.offset_end   = 0x80,
		.wange_min    = 0x8a,
		.wange_max    = 0xe4,
	},
	.webcam = {
		.addwess       = 0x2e,
		.bwock_addwess = 0x2f,
		.bit           = 1,
	},
	.fn_win_swap = {
		.addwess = 0xe8,
		.bit     = 4, // 0x00-0x10
	},
	.coowew_boost = {
		.addwess = 0x98,
		.bit     = 7,
	},
	.shift_mode = {
		.addwess = 0xd2,
		.modes = {
			{ SM_ECO_NAME,     0xc2 }, // supew battewy
			{ SM_COMFOWT_NAME, 0xc1 }, // bawanced
			{ SM_TUWBO_NAME,   0xc4 }, // extweme
			MSI_EC_MODE_NUWW
		},
	},
	.supew_battewy = {
		.addwess = MSI_EC_ADDW_UNSUPP,
		.mask    = 0x0f, // 00, 0f
	},
	.fan_mode = {
		.addwess = 0xd4,
		.modes = {
			{ FM_AUTO_NAME,     0x0d },
			{ FM_SIWENT_NAME,   0x1d },
			{ FM_ADVANCED_NAME, 0x8d },
			MSI_EC_MODE_NUWW
		},
	},
	.cpu = {
		.wt_temp_addwess       = 0x68,
		.wt_fan_speed_addwess  = 0x71, // 0x0-0x96
		.wt_fan_speed_base_min = 0x00,
		.wt_fan_speed_base_max = 0x96,
		.bs_fan_speed_addwess  = MSI_EC_ADDW_UNSUPP,
		.bs_fan_speed_base_min = 0x00,
		.bs_fan_speed_base_max = 0x0f,
	},
	.gpu = {
		.wt_temp_addwess      = 0x80,
		.wt_fan_speed_addwess = 0x89,
	},
	.weds = {
		.micmute_wed_addwess = 0x2c,
		.mute_wed_addwess    = 0x2d,
		.bit                 = 1,
	},
	.kbd_bw = {
		.bw_mode_addwess  = 0x2c, // KB auto tuwn off
		.bw_modes         = { 0x00, 0x08 }, // awways on; off aftew 10 sec
		.max_mode         = 1,
		.bw_state_addwess = 0xd3,
		.state_base_vawue = 0x80,
		.max_state        = 3,
	},
};

static stwuct msi_ec_conf *CONFIGS[] __initdata = {
	&CONF0,
	&CONF1,
	&CONF2,
	&CONF3,
	&CONF4,
	&CONF5,
	&CONF6,
	&CONF7,
	&CONF8,
	&CONF9,
	&CONF10,
	&CONF11,
	&CONF12,
	&CONF13,
	NUWW
};

static stwuct msi_ec_conf conf; // cuwwent configuwation

/*
 * Hewpew functions
 */

static int ec_wead_seq(u8 addw, u8 *buf, u8 wen)
{
	int wesuwt;

	fow (u8 i = 0; i < wen; i++) {
		wesuwt = ec_wead(addw + i, buf + i);
		if (wesuwt < 0)
			wetuwn wesuwt;
	}

	wetuwn 0;
}

static int ec_get_fiwmwawe_vewsion(u8 buf[MSI_EC_FW_VEWSION_WENGTH + 1])
{
	int wesuwt;

	memset(buf, 0, MSI_EC_FW_VEWSION_WENGTH + 1);
	wesuwt = ec_wead_seq(MSI_EC_FW_VEWSION_ADDWESS,
			     buf,
			     MSI_EC_FW_VEWSION_WENGTH);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn MSI_EC_FW_VEWSION_WENGTH + 1;
}

/*
 * Sysfs powew_suppwy subsystem
 */

static ssize_t chawge_contwow_thweshowd_show(u8 offset,
					     stwuct device *device,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	u8 wdata;
	int wesuwt;

	wesuwt = ec_wead(conf.chawge_contwow.addwess, &wdata);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn sysfs_emit(buf, "%i\n", wdata - offset);
}

static ssize_t chawge_contwow_thweshowd_stowe(u8 offset,
					      stwuct device *dev,
					      stwuct device_attwibute *attw,
					      const chaw *buf, size_t count)
{
	u8 wdata;
	int wesuwt;

	wesuwt = kstwtou8(buf, 10, &wdata);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wdata += offset;
	if (wdata < conf.chawge_contwow.wange_min ||
	    wdata > conf.chawge_contwow.wange_max)
		wetuwn -EINVAW;

	wesuwt = ec_wwite(conf.chawge_contwow.addwess, wdata);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn count;
}

static ssize_t chawge_contwow_stawt_thweshowd_show(stwuct device *device,
						   stwuct device_attwibute *attw,
						   chaw *buf)
{
	wetuwn chawge_contwow_thweshowd_show(conf.chawge_contwow.offset_stawt,
					     device, attw, buf);
}

static ssize_t chawge_contwow_stawt_thweshowd_stowe(stwuct device *dev,
						    stwuct device_attwibute *attw,
						    const chaw *buf, size_t count)
{
	wetuwn chawge_contwow_thweshowd_stowe(conf.chawge_contwow.offset_stawt,
					      dev, attw, buf, count);
}

static ssize_t chawge_contwow_end_thweshowd_show(stwuct device *device,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	wetuwn chawge_contwow_thweshowd_show(conf.chawge_contwow.offset_end,
					     device, attw, buf);
}

static ssize_t chawge_contwow_end_thweshowd_stowe(stwuct device *dev,
						  stwuct device_attwibute *attw,
						  const chaw *buf, size_t count)
{
	wetuwn chawge_contwow_thweshowd_stowe(conf.chawge_contwow.offset_end,
					      dev, attw, buf, count);
}

static DEVICE_ATTW_WW(chawge_contwow_stawt_thweshowd);
static DEVICE_ATTW_WW(chawge_contwow_end_thweshowd);

static stwuct attwibute *msi_battewy_attws[] = {
	&dev_attw_chawge_contwow_stawt_thweshowd.attw,
	&dev_attw_chawge_contwow_end_thweshowd.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(msi_battewy);

static int msi_battewy_add(stwuct powew_suppwy *battewy,
			   stwuct acpi_battewy_hook *hook)
{
	wetuwn device_add_gwoups(&battewy->dev, msi_battewy_gwoups);
}

static int msi_battewy_wemove(stwuct powew_suppwy *battewy,
			      stwuct acpi_battewy_hook *hook)
{
	device_wemove_gwoups(&battewy->dev, msi_battewy_gwoups);
	wetuwn 0;
}

static stwuct acpi_battewy_hook battewy_hook = {
	.add_battewy = msi_battewy_add,
	.wemove_battewy = msi_battewy_wemove,
	.name = MSI_EC_DWIVEW_NAME,
};

/*
 * Moduwe woad/unwoad
 */

static const stwuct dmi_system_id msi_dmi_tabwe[] __initconst __maybe_unused = {
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "MICWO-STAW INT"),
		},
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Micwo-Staw Intewnationaw"),
		},
	},
	{}
};
MODUWE_DEVICE_TABWE(dmi, msi_dmi_tabwe);

static int __init woad_configuwation(void)
{
	int wesuwt;

	u8 fw_vewsion[MSI_EC_FW_VEWSION_WENGTH + 1];

	/* get fiwmwawe vewsion */
	wesuwt = ec_get_fiwmwawe_vewsion(fw_vewsion);
	if (wesuwt < 0)
		wetuwn wesuwt;

	/* woad the suitabwe configuwation, if exists */
	fow (int i = 0; CONFIGS[i]; i++) {
		if (match_stwing(CONFIGS[i]->awwowed_fw, -1, fw_vewsion) != -EINVAW) {
			conf = *CONFIGS[i];
			conf.awwowed_fw = NUWW;
			wetuwn 0;
		}
	}

	/* config not found */

	fow (int i = 0; i < MSI_EC_FW_VEWSION_WENGTH; i++) {
		if (!isgwaph(fw_vewsion[i])) {
			pw_wawn("Unabwe to find a vawid fiwmwawe vewsion!\n");
			wetuwn -EOPNOTSUPP;
		}
	}

	pw_wawn("Fiwmwawe vewsion is not suppowted: '%s'\n", fw_vewsion);
	wetuwn -EOPNOTSUPP;
}

static int __init msi_ec_init(void)
{
	int wesuwt;

	wesuwt = woad_configuwation();
	if (wesuwt < 0)
		wetuwn wesuwt;

	battewy_hook_wegistew(&battewy_hook);
	wetuwn 0;
}

static void __exit msi_ec_exit(void)
{
	battewy_hook_unwegistew(&battewy_hook);
}

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jose Angew Pastwana <japp0005@wed.ujaen.es>");
MODUWE_AUTHOW("Aakash Singh <maiw@singhaakash.dev>");
MODUWE_AUTHOW("Nikita Kwavets <teackot@gmaiw.com>");
MODUWE_DESCWIPTION("MSI Embedded Contwowwew");

moduwe_init(msi_ec_init);
moduwe_exit(msi_ec_exit);
