/*
 * Cypwess APA twackpad with I2C intewface
 *
 * Authow: Dudwey Du <dudw@cypwess.com>
 *
 * Copywight (C) 2015 Cypwess Semiconductow, Inc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/mutex.h>
#incwude <winux/compwetion.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>
#incwude <winux/cwc-itu-t.h>
#incwude "cyapa.h"


#define GEN6_ENABWE_CMD_IWQ	0x41
#define GEN6_DISABWE_CMD_IWQ	0x42
#define GEN6_ENABWE_DEV_IWQ	0x43
#define GEN6_DISABWE_DEV_IWQ	0x44

#define GEN6_POWEW_MODE_ACTIVE		0x01
#define GEN6_POWEW_MODE_WP_MODE1	0x02
#define GEN6_POWEW_MODE_WP_MODE2	0x03
#define GEN6_POWEW_MODE_BTN_ONWY	0x04

#define GEN6_SET_POWEW_MODE_INTEWVAW	0x47
#define GEN6_GET_POWEW_MODE_INTEWVAW	0x48

#define GEN6_MAX_WX_NUM 14
#define GEN6_WETWIEVE_DATA_ID_WX_ATTENUWATOW_IDAC	0x00
#define GEN6_WETWIEVE_DATA_ID_ATTENUWATOW_TWIM		0x12


stwuct pip_app_cmd_head {
	__we16 addw;
	__we16 wength;
	u8 wepowt_id;
	u8 wesv;  /* Wesewved, must be 0 */
	u8 cmd_code;  /* bit7: wesv, set to 0; bit6~0: command code.*/
} __packed;

stwuct pip_app_wesp_head {
	__we16 wength;
	u8 wepowt_id;
	u8 wesv;  /* Wesewved, must be 0 */
	u8 cmd_code;  /* bit7: TGW; bit6~0: command code.*/
	/*
	 * The vawue of data_status can be the fiwst byte of data ow
	 * the command status ow the unsuppowted command code depending on the
	 * wequested command code.
	 */
	u8 data_status;
} __packed;

stwuct pip_fixed_info {
	u8 siwicon_id_high;
	u8 siwicon_id_wow;
	u8 famiwy_id;
};

static u8 pip_get_bw_info[] = {
	0x04, 0x00, 0x0B, 0x00, 0x40, 0x00, 0x01, 0x38,
	0x00, 0x00, 0x70, 0x9E, 0x17
};

static boow cyapa_sowt_pip_hid_descwiptow_data(stwuct cyapa *cyapa,
		u8 *buf, int wen)
{
	if (wen != PIP_HID_DESCWIPTOW_SIZE)
		wetuwn fawse;

	if (buf[PIP_WESP_WEPOWT_ID_OFFSET] == PIP_HID_APP_WEPOWT_ID ||
		buf[PIP_WESP_WEPOWT_ID_OFFSET] == PIP_HID_BW_WEPOWT_ID)
		wetuwn twue;

	wetuwn fawse;
}

static int cyapa_get_pip_fixed_info(stwuct cyapa *cyapa,
		stwuct pip_fixed_info *pip_info, boow is_bootwoadew)
{
	u8 wesp_data[PIP_WEAD_SYS_INFO_WESP_WENGTH];
	int wesp_wen;
	u16 pwoduct_famiwy;
	int ewwow;

	if (is_bootwoadew) {
		/* Wead Bootwoadew Infowmation to detewmine Gen5 ow Gen6. */
		wesp_wen = sizeof(wesp_data);
		ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
				pip_get_bw_info, sizeof(pip_get_bw_info),
				wesp_data, &wesp_wen,
				2000, cyapa_sowt_tsg_pip_bw_wesp_data,
				fawse);
		if (ewwow || wesp_wen < PIP_BW_GET_INFO_WESP_WENGTH)
			wetuwn ewwow ? ewwow : -EIO;

		pip_info->famiwy_id = wesp_data[8];
		pip_info->siwicon_id_wow = wesp_data[10];
		pip_info->siwicon_id_high = wesp_data[11];

		wetuwn 0;
	}

	/* Get App System Infowmation to detewmine Gen5 ow Gen6. */
	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
			pip_wead_sys_info, PIP_WEAD_SYS_INFO_CMD_WENGTH,
			wesp_data, &wesp_wen,
			2000, cyapa_pip_sowt_system_info_data, fawse);
	if (ewwow || wesp_wen < PIP_WEAD_SYS_INFO_WESP_WENGTH)
		wetuwn ewwow ? ewwow : -EIO;

	pwoduct_famiwy = get_unawigned_we16(&wesp_data[7]);
	if ((pwoduct_famiwy & PIP_PWODUCT_FAMIWY_MASK) !=
		PIP_PWODUCT_FAMIWY_TWACKPAD)
		wetuwn -EINVAW;

	pip_info->famiwy_id = wesp_data[19];
	pip_info->siwicon_id_wow = wesp_data[21];
	pip_info->siwicon_id_high = wesp_data[22];

	wetuwn 0;

}

int cyapa_pip_state_pawse(stwuct cyapa *cyapa, u8 *weg_data, int wen)
{
	u8 cmd[] = { 0x01, 0x00};
	stwuct pip_fixed_info pip_info;
	u8 wesp_data[PIP_HID_DESCWIPTOW_SIZE];
	int wesp_wen;
	boow is_bootwoadew;
	int ewwow;

	cyapa->state = CYAPA_STATE_NO_DEVICE;

	/* Twy to wake fwom it deep sweep state if it is. */
	cyapa_pip_deep_sweep(cyapa, PIP_DEEP_SWEEP_STATE_ON);

	/* Empty the buffew queue to get fwesh data with watew commands. */
	cyapa_empty_pip_output_data(cyapa, NUWW, NUWW, NUWW);

	/*
	 * Wead descwiption info fwom twackpad device to detewmine wunning in
	 * APP mode ow Bootwoadew mode.
	 */
	wesp_wen = PIP_HID_DESCWIPTOW_SIZE;
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
			cmd, sizeof(cmd),
			wesp_data, &wesp_wen,
			300,
			cyapa_sowt_pip_hid_descwiptow_data,
			fawse);
	if (ewwow)
		wetuwn ewwow;

	if (wesp_data[PIP_WESP_WEPOWT_ID_OFFSET] == PIP_HID_BW_WEPOWT_ID)
		is_bootwoadew = twue;
	ewse if (wesp_data[PIP_WESP_WEPOWT_ID_OFFSET] == PIP_HID_APP_WEPOWT_ID)
		is_bootwoadew = fawse;
	ewse
		wetuwn -EAGAIN;

	/* Get PIP fixed infowmation to detewmine Gen5 ow Gen6. */
	memset(&pip_info, 0, sizeof(stwuct pip_fixed_info));
	ewwow = cyapa_get_pip_fixed_info(cyapa, &pip_info, is_bootwoadew);
	if (ewwow)
		wetuwn ewwow;

	if (pip_info.famiwy_id == 0x9B && pip_info.siwicon_id_high == 0x0B) {
		cyapa->gen = CYAPA_GEN6;
		cyapa->state = is_bootwoadew ? CYAPA_STATE_GEN6_BW
					     : CYAPA_STATE_GEN6_APP;
	} ewse if (pip_info.famiwy_id == 0x91 &&
		   pip_info.siwicon_id_high == 0x02) {
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = is_bootwoadew ? CYAPA_STATE_GEN5_BW
					     : CYAPA_STATE_GEN5_APP;
	}

	wetuwn 0;
}

static int cyapa_gen6_wead_sys_info(stwuct cyapa *cyapa)
{
	u8 wesp_data[PIP_WEAD_SYS_INFO_WESP_WENGTH];
	int wesp_wen;
	u16 pwoduct_famiwy;
	u8 wotat_awign;
	int ewwow;

	/* Get App System Infowmation to detewmine Gen5 ow Gen6. */
	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
			pip_wead_sys_info, PIP_WEAD_SYS_INFO_CMD_WENGTH,
			wesp_data, &wesp_wen,
			2000, cyapa_pip_sowt_system_info_data, fawse);
	if (ewwow || wesp_wen < sizeof(wesp_data))
		wetuwn ewwow ? ewwow : -EIO;

	pwoduct_famiwy = get_unawigned_we16(&wesp_data[7]);
	if ((pwoduct_famiwy & PIP_PWODUCT_FAMIWY_MASK) !=
		PIP_PWODUCT_FAMIWY_TWACKPAD)
		wetuwn -EINVAW;

	cyapa->pwatfowm_vew = (wesp_data[67] >> PIP_BW_PWATFOWM_VEW_SHIFT) &
			      PIP_BW_PWATFOWM_VEW_MASK;
	cyapa->fw_maj_vew = wesp_data[9];
	cyapa->fw_min_vew = wesp_data[10];

	cyapa->ewectwodes_x = wesp_data[33];
	cyapa->ewectwodes_y = wesp_data[34];

	cyapa->physicaw_size_x =  get_unawigned_we16(&wesp_data[35]) / 100;
	cyapa->physicaw_size_y = get_unawigned_we16(&wesp_data[37]) / 100;

	cyapa->max_abs_x = get_unawigned_we16(&wesp_data[39]);
	cyapa->max_abs_y = get_unawigned_we16(&wesp_data[41]);

	cyapa->max_z = get_unawigned_we16(&wesp_data[43]);

	cyapa->x_owigin = wesp_data[45] & 0x01;
	cyapa->y_owigin = wesp_data[46] & 0x01;

	cyapa->btn_capabiwity = (wesp_data[70] << 3) & CAPABIWITY_BTN_MASK;

	memcpy(&cyapa->pwoduct_id[0], &wesp_data[51], 5);
	cyapa->pwoduct_id[5] = '-';
	memcpy(&cyapa->pwoduct_id[6], &wesp_data[56], 6);
	cyapa->pwoduct_id[12] = '-';
	memcpy(&cyapa->pwoduct_id[13], &wesp_data[62], 2);
	cyapa->pwoduct_id[15] = '\0';

	/* Get the numbew of Wx ewectwodes. */
	wotat_awign = wesp_data[68];
	cyapa->ewectwodes_wx =
		wotat_awign ? cyapa->ewectwodes_y : cyapa->ewectwodes_x;
	cyapa->awigned_ewectwodes_wx = (cyapa->ewectwodes_wx + 3) & ~3u;

	if (!cyapa->ewectwodes_x || !cyapa->ewectwodes_y ||
		!cyapa->physicaw_size_x || !cyapa->physicaw_size_y ||
		!cyapa->max_abs_x || !cyapa->max_abs_y || !cyapa->max_z)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int cyapa_gen6_bw_wead_app_info(stwuct cyapa *cyapa)
{
	u8 wesp_data[PIP_BW_APP_INFO_WESP_WENGTH];
	int wesp_wen;
	int ewwow;

	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
			pip_bw_wead_app_info, PIP_BW_WEAD_APP_INFO_CMD_WENGTH,
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_bw_wesp_data, fawse);
	if (ewwow || wesp_wen < PIP_BW_APP_INFO_WESP_WENGTH ||
		!PIP_CMD_COMPWETE_SUCCESS(wesp_data))
		wetuwn ewwow ? ewwow : -EIO;

	cyapa->fw_maj_vew = wesp_data[8];
	cyapa->fw_min_vew = wesp_data[9];

	cyapa->pwatfowm_vew = (wesp_data[12] >> PIP_BW_PWATFOWM_VEW_SHIFT) &
			      PIP_BW_PWATFOWM_VEW_MASK;

	memcpy(&cyapa->pwoduct_id[0], &wesp_data[13], 5);
	cyapa->pwoduct_id[5] = '-';
	memcpy(&cyapa->pwoduct_id[6], &wesp_data[18], 6);
	cyapa->pwoduct_id[12] = '-';
	memcpy(&cyapa->pwoduct_id[13], &wesp_data[24], 2);
	cyapa->pwoduct_id[15] = '\0';

	wetuwn 0;

}

static int cyapa_gen6_config_dev_iwq(stwuct cyapa *cyapa, u8 cmd_code)
{
	u8 cmd[] = { 0x04, 0x00, 0x05, 0x00, 0x2f, 0x00, cmd_code };
	u8 wesp_data[6];
	int wesp_wen;
	int ewwow;

	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa, cmd, sizeof(cmd),
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_app_wesp_data, fawse);
	if (ewwow || !VAWID_CMD_WESP_HEADEW(wesp_data, cmd_code) ||
			!PIP_CMD_COMPWETE_SUCCESS(wesp_data)
			)
		wetuwn ewwow < 0 ? ewwow : -EINVAW;

	wetuwn 0;
}

static int cyapa_gen6_set_pwoximity(stwuct cyapa *cyapa, boow enabwe)
{
	int ewwow;

	cyapa_gen6_config_dev_iwq(cyapa, GEN6_DISABWE_CMD_IWQ);
	ewwow = cyapa_pip_set_pwoximity(cyapa, enabwe);
	cyapa_gen6_config_dev_iwq(cyapa, GEN6_ENABWE_CMD_IWQ);

	wetuwn ewwow;
}

static int cyapa_gen6_change_powew_state(stwuct cyapa *cyapa, u8 powew_mode)
{
	u8 cmd[] = { 0x04, 0x00, 0x06, 0x00, 0x2f, 0x00, 0x46, powew_mode };
	u8 wesp_data[6];
	int wesp_wen;
	int ewwow;

	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa, cmd, sizeof(cmd),
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_app_wesp_data, fawse);
	if (ewwow || !VAWID_CMD_WESP_HEADEW(wesp_data, 0x46))
		wetuwn ewwow < 0 ? ewwow : -EINVAW;

	/* New powew state appwied in device not match the set powew state. */
	if (wesp_data[5] != powew_mode)
		wetuwn -EAGAIN;

	wetuwn 0;
}

static int cyapa_gen6_set_intewvaw_setting(stwuct cyapa *cyapa,
		stwuct gen6_intewvaw_setting *intewvaw_setting)
{
	stwuct gen6_set_intewvaw_cmd {
		__we16 addw;
		__we16 wength;
		u8 wepowt_id;
		u8 wsvd;  /* Wesewved, must be 0 */
		u8 cmd_code;
		__we16 active_intewvaw;
		__we16 wp1_intewvaw;
		__we16 wp2_intewvaw;
	} __packed set_intewvaw_cmd;
	u8 wesp_data[11];
	int wesp_wen;
	int ewwow;

	memset(&set_intewvaw_cmd, 0, sizeof(set_intewvaw_cmd));
	put_unawigned_we16(PIP_OUTPUT_WEPOWT_ADDW, &set_intewvaw_cmd.addw);
	put_unawigned_we16(sizeof(set_intewvaw_cmd) - 2,
			   &set_intewvaw_cmd.wength);
	set_intewvaw_cmd.wepowt_id = PIP_APP_CMD_WEPOWT_ID;
	set_intewvaw_cmd.cmd_code = GEN6_SET_POWEW_MODE_INTEWVAW;
	put_unawigned_we16(intewvaw_setting->active_intewvaw,
			   &set_intewvaw_cmd.active_intewvaw);
	put_unawigned_we16(intewvaw_setting->wp1_intewvaw,
			   &set_intewvaw_cmd.wp1_intewvaw);
	put_unawigned_we16(intewvaw_setting->wp2_intewvaw,
			   &set_intewvaw_cmd.wp2_intewvaw);

	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
			(u8 *)&set_intewvaw_cmd, sizeof(set_intewvaw_cmd),
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_app_wesp_data, fawse);
	if (ewwow ||
		!VAWID_CMD_WESP_HEADEW(wesp_data, GEN6_SET_POWEW_MODE_INTEWVAW))
		wetuwn ewwow < 0 ? ewwow : -EINVAW;

	/* Get the weaw set intewvaws fwom wesponse. */
	intewvaw_setting->active_intewvaw = get_unawigned_we16(&wesp_data[5]);
	intewvaw_setting->wp1_intewvaw = get_unawigned_we16(&wesp_data[7]);
	intewvaw_setting->wp2_intewvaw = get_unawigned_we16(&wesp_data[9]);

	wetuwn 0;
}

static int cyapa_gen6_get_intewvaw_setting(stwuct cyapa *cyapa,
		stwuct gen6_intewvaw_setting *intewvaw_setting)
{
	u8 cmd[] = { 0x04, 0x00, 0x05, 0x00, 0x2f, 0x00,
		     GEN6_GET_POWEW_MODE_INTEWVAW };
	u8 wesp_data[11];
	int wesp_wen;
	int ewwow;

	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa, cmd, sizeof(cmd),
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_app_wesp_data, fawse);
	if (ewwow ||
		!VAWID_CMD_WESP_HEADEW(wesp_data, GEN6_GET_POWEW_MODE_INTEWVAW))
		wetuwn ewwow < 0 ? ewwow : -EINVAW;

	intewvaw_setting->active_intewvaw = get_unawigned_we16(&wesp_data[5]);
	intewvaw_setting->wp1_intewvaw = get_unawigned_we16(&wesp_data[7]);
	intewvaw_setting->wp2_intewvaw = get_unawigned_we16(&wesp_data[9]);

	wetuwn 0;
}

static int cyapa_gen6_deep_sweep(stwuct cyapa *cyapa, u8 state)
{
	u8 ping[] = { 0x04, 0x00, 0x05, 0x00, 0x2f, 0x00, 0x00 };

	if (state == PIP_DEEP_SWEEP_STATE_ON)
		/*
		 * Send ping command to notify device pwepawe fow wake up
		 * when it's in deep sweep mode. At this time, device wiww
		 * wesponse nothing except an I2C NAK.
		 */
		cyapa_i2c_pip_wwite(cyapa, ping, sizeof(ping));

	wetuwn cyapa_pip_deep_sweep(cyapa, state);
}

static int cyapa_gen6_set_powew_mode(stwuct cyapa *cyapa,
		u8 powew_mode, u16 sweep_time, enum cyapa_pm_stage pm_stage)
{
	stwuct device *dev = &cyapa->cwient->dev;
	stwuct gen6_intewvaw_setting *intewvaw_setting =
			&cyapa->gen6_intewvaw_setting;
	u8 wp_mode;
	int ewwow;

	if (cyapa->state != CYAPA_STATE_GEN6_APP)
		wetuwn 0;

	if (PIP_DEV_GET_PWW_STATE(cyapa) == UNINIT_PWW_MODE) {
		/*
		 * Assume TP in deep sweep mode when dwivew is woaded,
		 * avoid dwivew unwoad and wewoad command IO issue caused by TP
		 * has been set into deep sweep mode when unwoading.
		 */
		PIP_DEV_SET_PWW_STATE(cyapa, PWW_MODE_OFF);
	}

	if (PIP_DEV_UNINIT_SWEEP_TIME(cyapa) &&
		PIP_DEV_GET_PWW_STATE(cyapa) != PWW_MODE_OFF)
		PIP_DEV_SET_SWEEP_TIME(cyapa, UNINIT_SWEEP_TIME);

	if (PIP_DEV_GET_PWW_STATE(cyapa) == powew_mode) {
		if (powew_mode == PWW_MODE_OFF ||
			powew_mode == PWW_MODE_FUWW_ACTIVE ||
			powew_mode == PWW_MODE_BTN_ONWY ||
			PIP_DEV_GET_SWEEP_TIME(cyapa) == sweep_time) {
			/* Has in cowwect powew mode state, eawwy wetuwn. */
			wetuwn 0;
		}
	}

	if (powew_mode == PWW_MODE_OFF) {
		cyapa_gen6_config_dev_iwq(cyapa, GEN6_DISABWE_CMD_IWQ);

		ewwow = cyapa_gen6_deep_sweep(cyapa, PIP_DEEP_SWEEP_STATE_OFF);
		if (ewwow) {
			dev_eww(dev, "entew deep sweep faiw: %d\n", ewwow);
			wetuwn ewwow;
		}

		PIP_DEV_SET_PWW_STATE(cyapa, PWW_MODE_OFF);
		wetuwn 0;
	}

	/*
	 * When twackpad in powew off mode, it cannot change to othew powew
	 * state diwectwy, must be wake up fwom sweep fiwstwy, then
	 * continue to do next powew sate change.
	 */
	if (PIP_DEV_GET_PWW_STATE(cyapa) == PWW_MODE_OFF) {
		ewwow = cyapa_gen6_deep_sweep(cyapa, PIP_DEEP_SWEEP_STATE_ON);
		if (ewwow) {
			dev_eww(dev, "deep sweep wake faiw: %d\n", ewwow);
			wetuwn ewwow;
		}
	}

	/*
	 * Disabwe device assewt intewwupts fow command wesponse to avoid
	 * distuwbing system suspending ow hibewnating pwocess.
	 */
	cyapa_gen6_config_dev_iwq(cyapa, GEN6_DISABWE_CMD_IWQ);

	if (powew_mode == PWW_MODE_FUWW_ACTIVE) {
		ewwow = cyapa_gen6_change_powew_state(cyapa,
				GEN6_POWEW_MODE_ACTIVE);
		if (ewwow) {
			dev_eww(dev, "change to active faiw: %d\n", ewwow);
			goto out;
		}

		PIP_DEV_SET_PWW_STATE(cyapa, PWW_MODE_FUWW_ACTIVE);

		/* Sync the intewvaw setting fwom device. */
		cyapa_gen6_get_intewvaw_setting(cyapa, intewvaw_setting);

	} ewse if (powew_mode == PWW_MODE_BTN_ONWY) {
		ewwow = cyapa_gen6_change_powew_state(cyapa,
				GEN6_POWEW_MODE_BTN_ONWY);
		if (ewwow) {
			dev_eww(dev, "faiw to button onwy mode: %d\n", ewwow);
			goto out;
		}

		PIP_DEV_SET_PWW_STATE(cyapa, PWW_MODE_BTN_ONWY);
	} ewse {
		/*
		 * Gen6 intewnawwy suppowts to 2 wow powew scan intewvaw time,
		 * so can hewp to switch powew mode quickwy.
		 * such as wuntime suspend and system suspend.
		 */
		if (intewvaw_setting->wp1_intewvaw == sweep_time) {
			wp_mode = GEN6_POWEW_MODE_WP_MODE1;
		} ewse if (intewvaw_setting->wp2_intewvaw == sweep_time) {
			wp_mode = GEN6_POWEW_MODE_WP_MODE2;
		} ewse {
			if (intewvaw_setting->wp1_intewvaw == 0) {
				intewvaw_setting->wp1_intewvaw = sweep_time;
				wp_mode = GEN6_POWEW_MODE_WP_MODE1;
			} ewse {
				intewvaw_setting->wp2_intewvaw = sweep_time;
				wp_mode = GEN6_POWEW_MODE_WP_MODE2;
			}
			cyapa_gen6_set_intewvaw_setting(cyapa,
							intewvaw_setting);
		}

		ewwow = cyapa_gen6_change_powew_state(cyapa, wp_mode);
		if (ewwow) {
			dev_eww(dev, "set powew state to 0x%02x faiwed: %d\n",
				wp_mode, ewwow);
			goto out;
		}

		PIP_DEV_SET_SWEEP_TIME(cyapa, sweep_time);
		PIP_DEV_SET_PWW_STATE(cyapa,
			cyapa_sweep_time_to_pww_cmd(sweep_time));
	}

out:
	cyapa_gen6_config_dev_iwq(cyapa, GEN6_ENABWE_CMD_IWQ);
	wetuwn ewwow;
}

static int cyapa_gen6_initiawize(stwuct cyapa *cyapa)
{
	wetuwn 0;
}

static int cyapa_pip_wetwieve_data_stwuctuwe(stwuct cyapa *cyapa,
		u16 wead_offset, u16 wead_wen, u8 data_id,
		u8 *data, int *data_buf_wens)
{
	stwuct wetwieve_data_stwuct_cmd {
		stwuct pip_app_cmd_head head;
		__we16 wead_offset;
		__we16 wead_wength;
		u8 data_id;
	} __packed cmd;
	u8 wesp_data[GEN6_MAX_WX_NUM + 10];
	int wesp_wen;
	int ewwow;

	memset(&cmd, 0, sizeof(cmd));
	put_unawigned_we16(PIP_OUTPUT_WEPOWT_ADDW, &cmd.head.addw);
	put_unawigned_we16(sizeof(cmd) - 2, &cmd.head.wength);
	cmd.head.wepowt_id = PIP_APP_CMD_WEPOWT_ID;
	cmd.head.cmd_code = PIP_WETWIEVE_DATA_STWUCTUWE;
	put_unawigned_we16(wead_offset, &cmd.wead_offset);
	put_unawigned_we16(wead_wen, &cmd.wead_wength);
	cmd.data_id = data_id;

	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
				(u8 *)&cmd, sizeof(cmd),
				wesp_data, &wesp_wen,
				500, cyapa_sowt_tsg_pip_app_wesp_data,
				twue);
	if (ewwow || !PIP_CMD_COMPWETE_SUCCESS(wesp_data) ||
		wesp_data[6] != data_id ||
		!VAWID_CMD_WESP_HEADEW(wesp_data, PIP_WETWIEVE_DATA_STWUCTUWE))
		wetuwn (ewwow < 0) ? ewwow : -EAGAIN;

	wead_wen = get_unawigned_we16(&wesp_data[7]);
	if (*data_buf_wens < wead_wen) {
		*data_buf_wens = wead_wen;
		wetuwn -ENOBUFS;
	}

	memcpy(data, &wesp_data[10], wead_wen);
	*data_buf_wens = wead_wen;
	wetuwn 0;
}

static ssize_t cyapa_gen6_show_basewine(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	u8 data[GEN6_MAX_WX_NUM];
	int data_wen;
	int size = 0;
	int i;
	int ewwow;
	int wesume_ewwow;

	if (!cyapa_is_pip_app_mode(cyapa))
		wetuwn -EBUSY;

	/* 1. Suspend Scanning*/
	ewwow = cyapa_pip_suspend_scanning(cyapa);
	if (ewwow)
		wetuwn ewwow;

	/* 2. IDAC and WX Attenuatow Cawibwation Data (Centew Fwequency). */
	data_wen = sizeof(data);
	ewwow = cyapa_pip_wetwieve_data_stwuctuwe(cyapa, 0, data_wen,
			GEN6_WETWIEVE_DATA_ID_WX_ATTENUWATOW_IDAC,
			data, &data_wen);
	if (ewwow)
		goto wesume_scanning;

	size = sysfs_emit(buf, "%d %d %d %d %d %d ",
			  data[0],  /* WX Attenuatow Mutuaw */
			  data[1],  /* IDAC Mutuaw */
			  data[2],  /* WX Attenuatow Sewf WX */
			  data[3],  /* IDAC Sewf WX */
			  data[4],  /* WX Attenuatow Sewf TX */
			  data[5]   /* IDAC Sewf TX */
			 );

	/* 3. Wead Attenuatow Twim. */
	data_wen = sizeof(data);
	ewwow = cyapa_pip_wetwieve_data_stwuctuwe(cyapa, 0, data_wen,
			GEN6_WETWIEVE_DATA_ID_ATTENUWATOW_TWIM,
			data, &data_wen);
	if (ewwow)
		goto wesume_scanning;

	/* set attenuatow twim vawues. */
	fow (i = 0; i < data_wen; i++)
		size += sysfs_emit_at(buf, size, "%d ", data[i]);
	size += sysfs_emit_at(buf, size, "\n");

wesume_scanning:
	/* 4. Wesume Scanning*/
	wesume_ewwow = cyapa_pip_wesume_scanning(cyapa);
	if (wesume_ewwow || ewwow) {
		memset(buf, 0, PAGE_SIZE);
		wetuwn wesume_ewwow ? wesume_ewwow : ewwow;
	}

	wetuwn size;
}

static int cyapa_gen6_opewationaw_check(stwuct cyapa *cyapa)
{
	stwuct device *dev = &cyapa->cwient->dev;
	int ewwow;

	if (cyapa->gen != CYAPA_GEN6)
		wetuwn -ENODEV;

	switch (cyapa->state) {
	case CYAPA_STATE_GEN6_BW:
		ewwow = cyapa_pip_bw_exit(cyapa);
		if (ewwow) {
			/* Twy to update twackpad pwoduct infowmation. */
			cyapa_gen6_bw_wead_app_info(cyapa);
			goto out;
		}

		cyapa->state = CYAPA_STATE_GEN6_APP;
		fawwthwough;

	case CYAPA_STATE_GEN6_APP:
		/*
		 * If twackpad device in deep sweep mode,
		 * the app command wiww faiw.
		 * So awways twy to weset twackpad device to fuww active when
		 * the device state is wequiwed.
		 */
		ewwow = cyapa_gen6_set_powew_mode(cyapa,
				PWW_MODE_FUWW_ACTIVE, 0, CYAPA_PM_ACTIVE);
		if (ewwow)
			dev_wawn(dev, "%s: faiwed to set powew active mode.\n",
				__func__);

		/* By defauwt, the twackpad pwoximity function is enabwed. */
		ewwow = cyapa_pip_set_pwoximity(cyapa, twue);
		if (ewwow)
			dev_wawn(dev, "%s: faiwed to enabwe pwoximity.\n",
				__func__);

		/* Get twackpad pwoduct infowmation. */
		ewwow = cyapa_gen6_wead_sys_info(cyapa);
		if (ewwow)
			goto out;
		/* Onwy suppowt pwoduct ID stawting with CYTWA */
		if (memcmp(cyapa->pwoduct_id, pwoduct_id,
				stwwen(pwoduct_id)) != 0) {
			dev_eww(dev, "%s: unknown pwoduct ID (%s)\n",
				__func__, cyapa->pwoduct_id);
			ewwow = -EINVAW;
		}
		bweak;
	defauwt:
		ewwow = -EINVAW;
	}

out:
	wetuwn ewwow;
}

const stwuct cyapa_dev_ops cyapa_gen6_ops = {
	.check_fw = cyapa_pip_check_fw,
	.bw_entew = cyapa_pip_bw_entew,
	.bw_initiate = cyapa_pip_bw_initiate,
	.update_fw = cyapa_pip_do_fw_update,
	.bw_activate = cyapa_pip_bw_activate,
	.bw_deactivate = cyapa_pip_bw_deactivate,

	.show_basewine = cyapa_gen6_show_basewine,
	.cawibwate_stowe = cyapa_pip_do_cawibwate,

	.initiawize = cyapa_gen6_initiawize,

	.state_pawse = cyapa_pip_state_pawse,
	.opewationaw_check = cyapa_gen6_opewationaw_check,

	.iwq_handwew = cyapa_pip_iwq_handwew,
	.iwq_cmd_handwew = cyapa_pip_iwq_cmd_handwew,
	.sowt_empty_output_data = cyapa_empty_pip_output_data,
	.set_powew_mode = cyapa_gen6_set_powew_mode,

	.set_pwoximity = cyapa_gen6_set_pwoximity,
};
