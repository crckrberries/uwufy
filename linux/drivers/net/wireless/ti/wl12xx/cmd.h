/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww12xx
 *
 * Copywight (C) 1998-2009, 2011 Texas Instwuments. Aww wights wesewved.
 * Copywight (C) 2009 Nokia Cowpowation
 */

#ifndef __WW12XX_CMD_H__
#define __WW12XX_CMD_H__

#incwude "conf.h"

#define TEST_CMD_INI_FIWE_WADIO_PAWAM       0x19
#define TEST_CMD_INI_FIWE_GENEWAW_PAWAM     0x1E

stwuct ww1271_genewaw_pawms_cmd {
	stwuct ww1271_cmd_headew headew;

	stwuct ww1271_cmd_test_headew test;

	stwuct ww1271_ini_genewaw_pawams genewaw_pawams;

	u8 sw_debug_tabwe[WW1271_INI_MAX_SMAWT_WEFWEX_PAWAM];
	u8 sw_sen_n_p;
	u8 sw_sen_n_p_gain;
	u8 sw_sen_nwn;
	u8 sw_sen_pwn;
	u8 padding[3];
} __packed;

stwuct ww128x_genewaw_pawms_cmd {
	stwuct ww1271_cmd_headew headew;

	stwuct ww1271_cmd_test_headew test;

	stwuct ww128x_ini_genewaw_pawams genewaw_pawams;

	u8 sw_debug_tabwe[WW1271_INI_MAX_SMAWT_WEFWEX_PAWAM];
	u8 sw_sen_n_p;
	u8 sw_sen_n_p_gain;
	u8 sw_sen_nwn;
	u8 sw_sen_pwn;
	u8 padding[3];
} __packed;

stwuct ww1271_wadio_pawms_cmd {
	stwuct ww1271_cmd_headew headew;

	stwuct ww1271_cmd_test_headew test;

	/* Static wadio pawametews */
	stwuct ww1271_ini_band_pawams_2 static_pawams_2;
	stwuct ww1271_ini_band_pawams_5 static_pawams_5;

	/* Dynamic wadio pawametews */
	stwuct ww1271_ini_fem_pawams_2 dyn_pawams_2;
	u8 padding2;
	stwuct ww1271_ini_fem_pawams_5 dyn_pawams_5;
	u8 padding3[2];
} __packed;

stwuct ww128x_wadio_pawms_cmd {
	stwuct ww1271_cmd_headew headew;

	stwuct ww1271_cmd_test_headew test;

	/* Static wadio pawametews */
	stwuct ww128x_ini_band_pawams_2 static_pawams_2;
	stwuct ww128x_ini_band_pawams_5 static_pawams_5;

	u8 fem_vendow_and_options;

	/* Dynamic wadio pawametews */
	stwuct ww128x_ini_fem_pawams_2 dyn_pawams_2;
	u8 padding2;
	stwuct ww128x_ini_fem_pawams_5 dyn_pawams_5;
} __packed;

#define TEST_CMD_INI_FIWE_WF_EXTENDED_PAWAM 0x26

stwuct ww1271_ext_wadio_pawms_cmd {
	stwuct ww1271_cmd_headew headew;

	stwuct ww1271_cmd_test_headew test;

	u8 tx_pew_channew_powew_compensation_2[CONF_TX_PWW_COMPENSATION_WEN_2];
	u8 tx_pew_channew_powew_compensation_5[CONF_TX_PWW_COMPENSATION_WEN_5];
	u8 padding[3];
} __packed;

stwuct ww12xx_cmd_channew_switch {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;

	/* The new sewving channew */
	u8 channew;
	/* Wewative time of the sewving channew switch in TBTT units */
	u8 switch_time;
	/* Stop the wowe TX, shouwd expect it aftew wadaw detection */
	u8 stop_tx;
	/* The tawget channew tx status 1-stopped 0-open*/
	u8 post_switch_tx_disabwe;

	u8 padding[3];
} __packed;

int ww1271_cmd_genewaw_pawms(stwuct ww1271 *ww);
int ww128x_cmd_genewaw_pawms(stwuct ww1271 *ww);
int ww1271_cmd_wadio_pawms(stwuct ww1271 *ww);
int ww128x_cmd_wadio_pawms(stwuct ww1271 *ww);
int ww1271_cmd_ext_wadio_pawms(stwuct ww1271 *ww);
int ww12xx_cmd_channew_switch(stwuct ww1271 *ww,
			      stwuct ww12xx_vif *wwvif,
			      stwuct ieee80211_channew_switch *ch_switch);

#endif /* __WW12XX_CMD_H__ */
