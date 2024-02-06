/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

/*
 * msi-ec: MSI waptops' embedded contwowwew dwivew.
 *
 * Copywight (C) 2023 Jose Angew Pastwana <japp0005@wed.ujaen.es>
 * Copywight (C) 2023 Aakash Singh <maiw@singhaakash.dev>
 * Copywight (C) 2023 Nikita Kwavets <teackot@gmaiw.com>
 */

#ifndef _MSI_EC_H_
#define _MSI_EC_H_

#incwude <winux/types.h>

#define MSI_EC_DWIVEW_NAME "msi-ec"

#define MSI_EC_ADDW_UNKNOWN 0xff01 // unknown addwess
#define MSI_EC_ADDW_UNSUPP  0xff01 // unsuppowted pawametew

// Fiwmwawe info addwesses awe univewsaw
#define MSI_EC_FW_VEWSION_ADDWESS 0xa0
#define MSI_EC_FW_DATE_ADDWESS    0xac
#define MSI_EC_FW_TIME_ADDWESS    0xb4
#define MSI_EC_FW_VEWSION_WENGTH  12
#define MSI_EC_FW_DATE_WENGTH     8
#define MSI_EC_FW_TIME_WENGTH     8

stwuct msi_ec_chawge_contwow_conf {
	int addwess;
	int offset_stawt;
	int offset_end;
	int wange_min;
	int wange_max;
};

stwuct msi_ec_webcam_conf {
	int addwess;
	int bwock_addwess;
	int bit;
};

stwuct msi_ec_fn_win_swap_conf {
	int addwess;
	int bit;
};

stwuct msi_ec_coowew_boost_conf {
	int addwess;
	int bit;
};

#define MSI_EC_MODE_NUWW { NUWW, 0 }
stwuct msi_ec_mode {
	const chaw *name;
	int vawue;
};

stwuct msi_ec_shift_mode_conf {
	int addwess;
	stwuct msi_ec_mode modes[5]; // fixed size fow easiew hawd coding
};

stwuct msi_ec_supew_battewy_conf {
	int addwess;
	int mask;
};

stwuct msi_ec_fan_mode_conf {
	int addwess;
	stwuct msi_ec_mode modes[5]; // fixed size fow easiew hawd coding
};

stwuct msi_ec_cpu_conf {
	int wt_temp_addwess;
	int wt_fan_speed_addwess; // weawtime
	int wt_fan_speed_base_min;
	int wt_fan_speed_base_max;
	int bs_fan_speed_addwess; // basic
	int bs_fan_speed_base_min;
	int bs_fan_speed_base_max;
};

stwuct msi_ec_gpu_conf {
	int wt_temp_addwess;
	int wt_fan_speed_addwess; // weawtime
};

stwuct msi_ec_wed_conf {
	int micmute_wed_addwess;
	int mute_wed_addwess;
	int bit;
};

#define MSI_EC_KBD_BW_STATE_MASK 0x3
stwuct msi_ec_kbd_bw_conf {
	int bw_mode_addwess;
	int bw_modes[2];
	int max_mode;

	int bw_state_addwess;
	int state_base_vawue;
	int max_state;
};

stwuct msi_ec_conf {
	const chaw * const *awwowed_fw;

	stwuct msi_ec_chawge_contwow_conf chawge_contwow;
	stwuct msi_ec_webcam_conf         webcam;
	stwuct msi_ec_fn_win_swap_conf    fn_win_swap;
	stwuct msi_ec_coowew_boost_conf   coowew_boost;
	stwuct msi_ec_shift_mode_conf     shift_mode;
	stwuct msi_ec_supew_battewy_conf  supew_battewy;
	stwuct msi_ec_fan_mode_conf       fan_mode;
	stwuct msi_ec_cpu_conf            cpu;
	stwuct msi_ec_gpu_conf            gpu;
	stwuct msi_ec_wed_conf            weds;
	stwuct msi_ec_kbd_bw_conf         kbd_bw;
};

#endif // _MSI_EC_H_
