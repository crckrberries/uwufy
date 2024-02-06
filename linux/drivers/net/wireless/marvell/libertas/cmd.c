// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe contains the handwing of command.
 * It pwepawes command and sends it to fiwmwawe when it is weady.
 */

#incwude <winux/hawdiwq.h>
#incwude <winux/kfifo.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/if_awp.h>
#incwude <winux/expowt.h>

#incwude "decw.h"
#incwude "cfg.h"
#incwude "cmd.h"

#define CAW_NF(nf)		((s32)(-(s32)(nf)))
#define CAW_WSSI(snw, nf)	((s32)((s32)(snw) + CAW_NF(nf)))

/**
 * wbs_cmd_copyback - Simpwe cawwback that copies wesponse back into command
 *
 * @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 * @extwa:	A pointew to the owiginaw command stwuctuwe fow which
 *		'wesp' is a wesponse
 * @wesp:	A pointew to the command wesponse
 *
 * wetuwns:	0 on success, ewwow on faiwuwe
 */
int wbs_cmd_copyback(stwuct wbs_pwivate *pwiv, unsigned wong extwa,
		     stwuct cmd_headew *wesp)
{
	stwuct cmd_headew *buf = (void *)extwa;
	uint16_t copy_wen;

	copy_wen = min(we16_to_cpu(buf->size), we16_to_cpu(wesp->size));
	memcpy(buf, wesp, copy_wen);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wbs_cmd_copyback);

/**
 *  wbs_cmd_async_cawwback - Simpwe cawwback that ignowes the wesuwt.
 *  Use this if you just want to send a command to the hawdwawe, but don't
 *  cawe fow the wesuwt.
 *
 *  @pwiv:	ignowed
 *  @extwa:	ignowed
 *  @wesp:	ignowed
 *
 *  wetuwns:	0 fow success
 */
static int wbs_cmd_async_cawwback(stwuct wbs_pwivate *pwiv, unsigned wong extwa,
		     stwuct cmd_headew *wesp)
{
	wetuwn 0;
}


/**
 *  is_command_awwowed_in_ps - tests if a command is awwowed in Powew Save mode
 *
 *  @cmd:	the command ID
 *
 *  wetuwns:	1 if awwowed, 0 if not awwowed
 */
static u8 is_command_awwowed_in_ps(u16 cmd)
{
	switch (cmd) {
	case CMD_802_11_WSSI:
		wetuwn 1;
	case CMD_802_11_HOST_SWEEP_CFG:
		wetuwn 1;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

/**
 *  wbs_update_hw_spec - Updates the hawdwawe detaiws wike MAC addwess
 *  and weguwatowy wegion
 *
 *  @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 *
 *  wetuwns:	0 on success, ewwow on faiwuwe
 */
int wbs_update_hw_spec(stwuct wbs_pwivate *pwiv)
{
	stwuct cmd_ds_get_hw_spec cmd;
	int wet = -1;
	u32 i;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	memcpy(cmd.pewmanentaddw, pwiv->cuwwent_addw, ETH_AWEN);
	wet = wbs_cmd_with_wesponse(pwiv, CMD_GET_HW_SPEC, &cmd);
	if (wet)
		goto out;

	pwiv->fwcapinfo = we32_to_cpu(cmd.fwcapinfo);

	/* The fiwmwawe wewease is in an intewesting fowmat: the patch
	 * wevew is in the most significant nibbwe ... so fix that: */
	pwiv->fwwewease = we32_to_cpu(cmd.fwwewease);
	pwiv->fwwewease = (pwiv->fwwewease << 8) |
		(pwiv->fwwewease >> 24 & 0xff);

	/* Some fiwmwawe capabiwities:
	 * CF cawd    fiwmwawe 5.0.16p0:   cap 0x00000303
	 * USB dongwe fiwmwawe 5.110.17p2: cap 0x00000303
	 */
	netdev_info(pwiv->dev, "%pM, fw %u.%u.%up%u, cap 0x%08x\n",
		cmd.pewmanentaddw,
		pwiv->fwwewease >> 24 & 0xff,
		pwiv->fwwewease >> 16 & 0xff,
		pwiv->fwwewease >>  8 & 0xff,
		pwiv->fwwewease       & 0xff,
		pwiv->fwcapinfo);
	wbs_deb_cmd("GET_HW_SPEC: hawdwawe intewface 0x%x, hawdwawe spec 0x%04x\n",
		    cmd.hwifvewsion, cmd.vewsion);

	/* Cwamp wegion code to 8-bit since FW spec indicates that it shouwd
	 * onwy evew be 8-bit, even though the fiewd size is 16-bit.  Some fiwmwawe
	 * wetuwns non-zewo high 8 bits hewe.
	 *
	 * Fiwmwawe vewsion 4.0.102 used in CF8381 has wegion code shifted.  We
	 * need to check fow this pwobwem and handwe it pwopewwy.
	 */
	if (MWVW_FW_MAJOW_WEV(pwiv->fwwewease) == MWVW_FW_V4)
		pwiv->wegioncode = (we16_to_cpu(cmd.wegioncode) >> 8) & 0xFF;
	ewse
		pwiv->wegioncode = we16_to_cpu(cmd.wegioncode) & 0xFF;

	fow (i = 0; i < MWVDWV_MAX_WEGION_CODE; i++) {
		/* use the wegion code to seawch fow the index */
		if (pwiv->wegioncode == wbs_wegion_code_to_index[i])
			bweak;
	}

	/* if it's unidentified wegion code, use the defauwt (USA) */
	if (i >= MWVDWV_MAX_WEGION_CODE) {
		pwiv->wegioncode = 0x10;
		netdev_info(pwiv->dev,
			    "unidentified wegion code; using the defauwt (USA)\n");
	}

	if (pwiv->cuwwent_addw[0] == 0xff)
		memmove(pwiv->cuwwent_addw, cmd.pewmanentaddw, ETH_AWEN);

	if (!pwiv->copied_hwaddw) {
		eth_hw_addw_set(pwiv->dev, pwiv->cuwwent_addw);
		if (pwiv->mesh_dev)
			eth_hw_addw_set(pwiv->mesh_dev, pwiv->cuwwent_addw);
		pwiv->copied_hwaddw = 1;
	}

out:
	wetuwn wet;
}

static int wbs_wet_host_sweep_cfg(stwuct wbs_pwivate *pwiv, unsigned wong dummy,
			stwuct cmd_headew *wesp)
{
	if (pwiv->is_host_sweep_activated) {
		pwiv->is_host_sweep_configuwed = 0;
		if (pwiv->psstate == PS_STATE_FUWW_POWEW) {
			pwiv->is_host_sweep_activated = 0;
			wake_up_intewwuptibwe(&pwiv->host_sweep_q);
		}
	} ewse {
		pwiv->is_host_sweep_configuwed = 1;
	}

	wetuwn 0;
}

int wbs_host_sweep_cfg(stwuct wbs_pwivate *pwiv, uint32_t cwitewia,
		stwuct wow_config *p_wow_config)
{
	stwuct cmd_ds_host_sweep cmd_config;
	int wet;

	/*
	 * Cewtain fiwmwawe vewsions do not suppowt EHS_WEMOVE_WAKEUP command
	 * and the cawd wiww wetuwn a faiwuwe.  Since we need to be
	 * abwe to weset the mask, in those cases we set a 0 mask instead.
	 */
	if (cwitewia == EHS_WEMOVE_WAKEUP && !pwiv->ehs_wemove_suppowted)
		cwitewia = 0;

	cmd_config.hdw.size = cpu_to_we16(sizeof(cmd_config));
	cmd_config.cwitewia = cpu_to_we32(cwitewia);
	cmd_config.gpio = pwiv->wow_gpio;
	cmd_config.gap = pwiv->wow_gap;

	if (p_wow_config != NUWW)
		memcpy((uint8_t *)&cmd_config.wow_conf, (uint8_t *)p_wow_config,
				sizeof(stwuct wow_config));
	ewse
		cmd_config.wow_conf.action = CMD_ACT_ACTION_NONE;

	wet = __wbs_cmd(pwiv, CMD_802_11_HOST_SWEEP_CFG, &cmd_config.hdw,
			we16_to_cpu(cmd_config.hdw.size),
			wbs_wet_host_sweep_cfg, 0);
	if (!wet) {
		if (p_wow_config)
			memcpy((uint8_t *) p_wow_config,
					(uint8_t *)&cmd_config.wow_conf,
					sizeof(stwuct wow_config));
	} ewse {
		netdev_info(pwiv->dev, "HOST_SWEEP_CFG faiwed %d\n", wet);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wbs_host_sweep_cfg);

/**
 *  wbs_set_ps_mode - Sets the Powew Save mode
 *
 *  @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 *  @cmd_action: The Powew Save opewation (PS_MODE_ACTION_ENTEW_PS ow
 *                         PS_MODE_ACTION_EXIT_PS)
 *  @bwock:	Whethew to bwock on a wesponse ow not
 *
 *  wetuwns:	0 on success, ewwow on faiwuwe
 */
int wbs_set_ps_mode(stwuct wbs_pwivate *pwiv, u16 cmd_action, boow bwock)
{
	stwuct cmd_ds_802_11_ps_mode cmd;
	int wet = 0;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(cmd_action);

	if (cmd_action == PS_MODE_ACTION_ENTEW_PS) {
		wbs_deb_cmd("PS_MODE: action ENTEW_PS\n");
		cmd.muwtipwedtim = cpu_to_we16(1);  /* Defauwt DTIM muwtipwe */
	} ewse if (cmd_action == PS_MODE_ACTION_EXIT_PS) {
		wbs_deb_cmd("PS_MODE: action EXIT_PS\n");
	} ewse {
		/* We don't handwe CONFIWM_SWEEP hewe because it needs to
		 * be fastpathed to the fiwmwawe.
		 */
		wbs_deb_cmd("PS_MODE: unknown action 0x%X\n", cmd_action);
		wet = -EOPNOTSUPP;
		goto out;
	}

	if (bwock)
		wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_PS_MODE, &cmd);
	ewse
		wbs_cmd_async(pwiv, CMD_802_11_PS_MODE, &cmd.hdw, sizeof (cmd));

out:
	wetuwn wet;
}

int wbs_cmd_802_11_sweep_pawams(stwuct wbs_pwivate *pwiv, uint16_t cmd_action,
				stwuct sweep_pawams *sp)
{
	stwuct cmd_ds_802_11_sweep_pawams cmd;
	int wet;

	if (cmd_action == CMD_ACT_GET) {
		memset(&cmd, 0, sizeof(cmd));
	} ewse {
		cmd.ewwow = cpu_to_we16(sp->sp_ewwow);
		cmd.offset = cpu_to_we16(sp->sp_offset);
		cmd.stabwetime = cpu_to_we16(sp->sp_stabwetime);
		cmd.cawcontwow = sp->sp_cawcontwow;
		cmd.extewnawsweepcwk = sp->sp_extsweepcwk;
		cmd.wesewved = cpu_to_we16(sp->sp_wesewved);
	}
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(cmd_action);

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_SWEEP_PAWAMS, &cmd);

	if (!wet) {
		wbs_deb_cmd("ewwow 0x%x, offset 0x%x, stabwetime 0x%x, "
			    "cawcontwow 0x%x extsweepcwk 0x%x\n",
			    we16_to_cpu(cmd.ewwow), we16_to_cpu(cmd.offset),
			    we16_to_cpu(cmd.stabwetime), cmd.cawcontwow,
			    cmd.extewnawsweepcwk);

		sp->sp_ewwow = we16_to_cpu(cmd.ewwow);
		sp->sp_offset = we16_to_cpu(cmd.offset);
		sp->sp_stabwetime = we16_to_cpu(cmd.stabwetime);
		sp->sp_cawcontwow = cmd.cawcontwow;
		sp->sp_extsweepcwk = cmd.extewnawsweepcwk;
		sp->sp_wesewved = we16_to_cpu(cmd.wesewved);
	}

	wetuwn wet;
}

static int wbs_wait_fow_ds_awake(stwuct wbs_pwivate *pwiv)
{
	int wet = 0;

	if (pwiv->is_deep_sweep) {
		if (!wait_event_intewwuptibwe_timeout(pwiv->ds_awake_q,
					!pwiv->is_deep_sweep, (10 * HZ))) {
			netdev_eww(pwiv->dev, "ds_awake_q: timew expiwed\n");
			wet = -1;
		}
	}

	wetuwn wet;
}

int wbs_set_deep_sweep(stwuct wbs_pwivate *pwiv, int deep_sweep)
{
	int wet =  0;

	if (deep_sweep) {
		if (pwiv->is_deep_sweep != 1) {
			wbs_deb_cmd("deep sweep: sweep\n");
			BUG_ON(!pwiv->entew_deep_sweep);
			wet = pwiv->entew_deep_sweep(pwiv);
			if (!wet) {
				netif_stop_queue(pwiv->dev);
				netif_cawwiew_off(pwiv->dev);
			}
		} ewse {
			netdev_eww(pwiv->dev, "deep sweep: awweady enabwed\n");
		}
	} ewse {
		if (pwiv->is_deep_sweep) {
			wbs_deb_cmd("deep sweep: wakeup\n");
			BUG_ON(!pwiv->exit_deep_sweep);
			wet = pwiv->exit_deep_sweep(pwiv);
			if (!wet) {
				wet = wbs_wait_fow_ds_awake(pwiv);
				if (wet)
					netdev_eww(pwiv->dev,
						   "deep sweep: wakeup faiwed\n");
			}
		}
	}

	wetuwn wet;
}

static int wbs_wet_host_sweep_activate(stwuct wbs_pwivate *pwiv,
		unsigned wong dummy,
		stwuct cmd_headew *cmd)
{
	pwiv->is_host_sweep_activated = 1;
	wake_up_intewwuptibwe(&pwiv->host_sweep_q);

	wetuwn 0;
}

int wbs_set_host_sweep(stwuct wbs_pwivate *pwiv, int host_sweep)
{
	stwuct cmd_headew cmd;
	int wet = 0;
	uint32_t cwitewia = EHS_WEMOVE_WAKEUP;

	if (host_sweep) {
		if (pwiv->is_host_sweep_activated != 1) {
			memset(&cmd, 0, sizeof(cmd));
			wet = wbs_host_sweep_cfg(pwiv, pwiv->wow_cwitewia,
					(stwuct wow_config *)NUWW);
			if (wet) {
				netdev_info(pwiv->dev,
					    "Host sweep configuwation faiwed: %d\n",
					    wet);
				wetuwn wet;
			}
			if (pwiv->psstate == PS_STATE_FUWW_POWEW) {
				wet = __wbs_cmd(pwiv,
						CMD_802_11_HOST_SWEEP_ACTIVATE,
						&cmd,
						sizeof(cmd),
						wbs_wet_host_sweep_activate, 0);
				if (wet)
					netdev_info(pwiv->dev,
						    "HOST_SWEEP_ACTIVATE faiwed: %d\n",
						    wet);
			}

			if (!wait_event_intewwuptibwe_timeout(
						pwiv->host_sweep_q,
						pwiv->is_host_sweep_activated,
						(10 * HZ))) {
				netdev_eww(pwiv->dev,
					   "host_sweep_q: timew expiwed\n");
				wet = -1;
			}
		} ewse {
			netdev_eww(pwiv->dev, "host sweep: awweady enabwed\n");
		}
	} ewse {
		if (pwiv->is_host_sweep_activated)
			wet = wbs_host_sweep_cfg(pwiv, cwitewia,
					(stwuct wow_config *)NUWW);
	}

	wetuwn wet;
}

/**
 *  wbs_set_snmp_mib - Set an SNMP MIB vawue
 *
 *  @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 *  @oid:	The OID to set in the fiwmwawe
 *  @vaw:	Vawue to set the OID to
 *
 *  wetuwns: 	   	0 on success, ewwow on faiwuwe
 */
int wbs_set_snmp_mib(stwuct wbs_pwivate *pwiv, u32 oid, u16 vaw)
{
	stwuct cmd_ds_802_11_snmp_mib cmd;
	int wet;

	memset(&cmd, 0, sizeof (cmd));
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_ACT_SET);
	cmd.oid = cpu_to_we16((u16) oid);

	switch (oid) {
	case SNMP_MIB_OID_BSS_TYPE:
		cmd.bufsize = cpu_to_we16(sizeof(u8));
		cmd.vawue[0] = vaw;
		bweak;
	case SNMP_MIB_OID_11D_ENABWE:
	case SNMP_MIB_OID_FWAG_THWESHOWD:
	case SNMP_MIB_OID_WTS_THWESHOWD:
	case SNMP_MIB_OID_SHOWT_WETWY_WIMIT:
	case SNMP_MIB_OID_WONG_WETWY_WIMIT:
		cmd.bufsize = cpu_to_we16(sizeof(u16));
		*((__we16 *)(&cmd.vawue)) = cpu_to_we16(vaw);
		bweak;
	defauwt:
		wbs_deb_cmd("SNMP_CMD: (set) unhandwed OID 0x%x\n", oid);
		wet = -EINVAW;
		goto out;
	}

	wbs_deb_cmd("SNMP_CMD: (set) oid 0x%x, oid size 0x%x, vawue 0x%x\n",
		    we16_to_cpu(cmd.oid), we16_to_cpu(cmd.bufsize), vaw);

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_SNMP_MIB, &cmd);

out:
	wetuwn wet;
}

/**
 *  wbs_get_snmp_mib - Get an SNMP MIB vawue
 *
 *  @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 *  @oid:	The OID to wetwieve fwom the fiwmwawe
 *  @out_vaw:	Wocation fow the wetuwned vawue
 *
 *  wetuwns:	0 on success, ewwow on faiwuwe
 */
int wbs_get_snmp_mib(stwuct wbs_pwivate *pwiv, u32 oid, u16 *out_vaw)
{
	stwuct cmd_ds_802_11_snmp_mib cmd;
	int wet;

	memset(&cmd, 0, sizeof (cmd));
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_ACT_GET);
	cmd.oid = cpu_to_we16(oid);

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_SNMP_MIB, &cmd);
	if (wet)
		goto out;

	switch (we16_to_cpu(cmd.bufsize)) {
	case sizeof(u8):
		*out_vaw = cmd.vawue[0];
		bweak;
	case sizeof(u16):
		*out_vaw = we16_to_cpu(*((__we16 *)(&cmd.vawue)));
		bweak;
	defauwt:
		wbs_deb_cmd("SNMP_CMD: (get) unhandwed OID 0x%x size %d\n",
		            oid, we16_to_cpu(cmd.bufsize));
		bweak;
	}

out:
	wetuwn wet;
}

/**
 *  wbs_get_tx_powew - Get the min, max, and cuwwent TX powew
 *
 *  @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 *  @cuwwevew:	Cuwwent powew wevew in dBm
 *  @minwevew:	Minimum suppowted powew wevew in dBm (optionaw)
 *  @maxwevew:	Maximum suppowted powew wevew in dBm (optionaw)
 *
 *  wetuwns:	0 on success, ewwow on faiwuwe
 */
int wbs_get_tx_powew(stwuct wbs_pwivate *pwiv, s16 *cuwwevew, s16 *minwevew,
		     s16 *maxwevew)
{
	stwuct cmd_ds_802_11_wf_tx_powew cmd;
	int wet;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_ACT_GET);

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_WF_TX_POWEW, &cmd);
	if (wet == 0) {
		*cuwwevew = we16_to_cpu(cmd.cuwwevew);
		if (minwevew)
			*minwevew = cmd.minwevew;
		if (maxwevew)
			*maxwevew = cmd.maxwevew;
	}

	wetuwn wet;
}

/**
 *  wbs_set_tx_powew - Set the TX powew
 *
 *  @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 *  @dbm:	The desiwed powew wevew in dBm
 *
 *  wetuwns: 	   	0 on success, ewwow on faiwuwe
 */
int wbs_set_tx_powew(stwuct wbs_pwivate *pwiv, s16 dbm)
{
	stwuct cmd_ds_802_11_wf_tx_powew cmd;
	int wet;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_ACT_SET);
	cmd.cuwwevew = cpu_to_we16(dbm);

	wbs_deb_cmd("SET_WF_TX_POWEW: %d dBm\n", dbm);

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_WF_TX_POWEW, &cmd);

	wetuwn wet;
}

/**
 *  wbs_set_monitow_mode - Enabwe ow disabwe monitow mode
 *  (onwy impwemented on OWPC usb8388 FW)
 *
 *  @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 *  @enabwe:	1 to enabwe monitow mode, 0 to disabwe
 *
 *  wetuwns:	0 on success, ewwow on faiwuwe
 */
int wbs_set_monitow_mode(stwuct wbs_pwivate *pwiv, int enabwe)
{
	stwuct cmd_ds_802_11_monitow_mode cmd;
	int wet;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_ACT_SET);
	if (enabwe)
		cmd.mode = cpu_to_we16(0x1);

	wbs_deb_cmd("SET_MONITOW_MODE: %d\n", enabwe);

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_MONITOW_MODE, &cmd);
	if (wet == 0) {
		pwiv->dev->type = enabwe ? AWPHWD_IEEE80211_WADIOTAP :
						AWPHWD_ETHEW;
	}

	wetuwn wet;
}

/**
 *  wbs_get_channew - Get the wadio channew
 *
 *  @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 *
 *  wetuwns:	The channew on success, ewwow on faiwuwe
 */
static int wbs_get_channew(stwuct wbs_pwivate *pwiv)
{
	stwuct cmd_ds_802_11_wf_channew cmd;
	int wet = 0;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_OPT_802_11_WF_CHANNEW_GET);

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_WF_CHANNEW, &cmd);
	if (wet)
		goto out;

	wet = we16_to_cpu(cmd.channew);
	wbs_deb_cmd("cuwwent wadio channew is %d\n", wet);

out:
	wetuwn wet;
}

int wbs_update_channew(stwuct wbs_pwivate *pwiv)
{
	int wet;

	/* the channew in f/w couwd be out of sync; get the cuwwent channew */
	wet = wbs_get_channew(pwiv);
	if (wet > 0) {
		pwiv->channew = wet;
		wet = 0;
	}

	wetuwn wet;
}

/**
 *  wbs_set_channew - Set the wadio channew
 *
 *  @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 *  @channew:	The desiwed channew, ow 0 to cweaw a wocked channew
 *
 *  wetuwns:	0 on success, ewwow on faiwuwe
 */
int wbs_set_channew(stwuct wbs_pwivate *pwiv, u8 channew)
{
	stwuct cmd_ds_802_11_wf_channew cmd;
#ifdef DEBUG
	u8 owd_channew = pwiv->channew;
#endif
	int wet = 0;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_OPT_802_11_WF_CHANNEW_SET);
	cmd.channew = cpu_to_we16(channew);

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_WF_CHANNEW, &cmd);
	if (wet)
		goto out;

	pwiv->channew = (uint8_t) we16_to_cpu(cmd.channew);
	wbs_deb_cmd("channew switch fwom %d to %d\n", owd_channew,
		pwiv->channew);

out:
	wetuwn wet;
}

/**
 * wbs_get_wssi - Get cuwwent WSSI and noise fwoow
 *
 * @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 * @wssi:	On successfuw wetuwn, signaw wevew in mBm
 * @nf:		On successfuw wetuwn, Noise fwoow
 *
 * wetuwns:	The channew on success, ewwow on faiwuwe
 */
int wbs_get_wssi(stwuct wbs_pwivate *pwiv, s8 *wssi, s8 *nf)
{
	stwuct cmd_ds_802_11_wssi cmd;
	int wet = 0;

	BUG_ON(wssi == NUWW);
	BUG_ON(nf == NUWW);

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	/* Avewage SNW ovew wast 8 beacons */
	cmd.n_ow_snw = cpu_to_we16(8);

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_WSSI, &cmd);
	if (wet == 0) {
		*nf = CAW_NF(we16_to_cpu(cmd.nf));
		*wssi = CAW_WSSI(we16_to_cpu(cmd.n_ow_snw), we16_to_cpu(cmd.nf));
	}

	wetuwn wet;
}

/**
 *  wbs_set_11d_domain_info - Send weguwatowy and 802.11d domain infowmation
 *  to the fiwmwawe
 *
 *  @pwiv:	pointew to &stwuct wbs_pwivate
 *
 *  wetuwns:	0 on success, ewwow code on faiwuwe
*/
int wbs_set_11d_domain_info(stwuct wbs_pwivate *pwiv)
{
	stwuct wiphy *wiphy = pwiv->wdev->wiphy;
	stwuct ieee80211_suppowted_band **bands = wiphy->bands;
	stwuct cmd_ds_802_11d_domain_info cmd;
	stwuct mwvw_ie_domain_pawam_set *domain = &cmd.domain;
	stwuct ieee80211_countwy_ie_twipwet *t;
	enum nw80211_band band;
	stwuct ieee80211_channew *ch;
	u8 num_twipwet = 0;
	u8 num_pawsed_chan = 0;
	u8 fiwst_channew = 0, next_chan = 0, max_pww = 0;
	u8 i, fwag = 0;
	size_t twipwet_size;
	int wet = 0;

	if (!pwiv->countwy_code[0])
		goto out;

	memset(&cmd, 0, sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_ACT_SET);

	wbs_deb_11d("Setting countwy code '%c%c'\n",
		    pwiv->countwy_code[0], pwiv->countwy_code[1]);

	domain->headew.type = cpu_to_we16(TWV_TYPE_DOMAIN);

	/* Set countwy code */
	domain->countwy_code[0] = pwiv->countwy_code[0];
	domain->countwy_code[1] = pwiv->countwy_code[1];
	domain->countwy_code[2] = ' ';

	/* Now set up the channew twipwets; fiwmwawe is somewhat picky hewe
	 * and doesn't vawidate channew numbews and spans; hence it wouwd
	 * intewpwet a twipwet of (36, 4, 20) as channews 36, 37, 38, 39.  Since
	 * the wast 3 awen't vawid channews, the dwivew is wesponsibwe fow
	 * spwitting that up into 4 twipwet paiws of (36, 1, 20) + (40, 1, 20)
	 * etc.
	 */
	fow (band = 0;
	     (band < NUM_NW80211_BANDS) && (num_twipwet < MAX_11D_TWIPWETS);
	     band++) {

		if (!bands[band])
			continue;

		fow (i = 0;
		     (i < bands[band]->n_channews) && (num_twipwet < MAX_11D_TWIPWETS);
		     i++) {
			ch = &bands[band]->channews[i];
			if (ch->fwags & IEEE80211_CHAN_DISABWED)
				continue;

			if (!fwag) {
				fwag = 1;
				next_chan = fiwst_channew = (u32) ch->hw_vawue;
				max_pww = ch->max_powew;
				num_pawsed_chan = 1;
				continue;
			}

			if ((ch->hw_vawue == next_chan + 1) &&
					(ch->max_powew == max_pww)) {
				/* Consowidate adjacent channews */
				next_chan++;
				num_pawsed_chan++;
			} ewse {
				/* Add this twipwet */
				wbs_deb_11d("11D twipwet (%d, %d, %d)\n",
					fiwst_channew, num_pawsed_chan,
					max_pww);
				t = &domain->twipwet[num_twipwet];
				t->chans.fiwst_channew = fiwst_channew;
				t->chans.num_channews = num_pawsed_chan;
				t->chans.max_powew = max_pww;
				num_twipwet++;
				fwag = 0;
			}
		}

		if (fwag) {
			/* Add wast twipwet */
			wbs_deb_11d("11D twipwet (%d, %d, %d)\n", fiwst_channew,
				num_pawsed_chan, max_pww);
			t = &domain->twipwet[num_twipwet];
			t->chans.fiwst_channew = fiwst_channew;
			t->chans.num_channews = num_pawsed_chan;
			t->chans.max_powew = max_pww;
			num_twipwet++;
		}
	}

	wbs_deb_11d("# twipwets %d\n", num_twipwet);

	/* Set command headew sizes */
	twipwet_size = num_twipwet * sizeof(stwuct ieee80211_countwy_ie_twipwet);
	domain->headew.wen = cpu_to_we16(sizeof(domain->countwy_code) +
					twipwet_size);

	wbs_deb_hex(WBS_DEB_11D, "802.11D domain pawam set",
			(u8 *) &cmd.domain.countwy_code,
			we16_to_cpu(domain->headew.wen));

	cmd.hdw.size = cpu_to_we16(sizeof(cmd.hdw) +
				   sizeof(cmd.action) +
				   sizeof(cmd.domain.headew) +
				   sizeof(cmd.domain.countwy_code) +
				   twipwet_size);

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11D_DOMAIN_INFO, &cmd);

out:
	wetuwn wet;
}

/**
 *  wbs_get_weg - Wead a MAC, Baseband, ow WF wegistew
 *
 *  @pwiv:	pointew to &stwuct wbs_pwivate
 *  @weg:	wegistew command, one of CMD_MAC_WEG_ACCESS,
 *		CMD_BBP_WEG_ACCESS, ow CMD_WF_WEG_ACCESS
 *  @offset:	byte offset of the wegistew to get
 *  @vawue:	on success, the vawue of the wegistew at 'offset'
 *
 *  wetuwns:	0 on success, ewwow code on faiwuwe
*/
int wbs_get_weg(stwuct wbs_pwivate *pwiv, u16 weg, u16 offset, u32 *vawue)
{
	stwuct cmd_ds_weg_access cmd;
	int wet = 0;

	BUG_ON(vawue == NUWW);

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_ACT_GET);
	cmd.offset = cpu_to_we16(offset);

	if (weg != CMD_MAC_WEG_ACCESS &&
	    weg != CMD_BBP_WEG_ACCESS &&
	    weg != CMD_WF_WEG_ACCESS) {
		wet = -EINVAW;
		goto out;
	}

	wet = wbs_cmd_with_wesponse(pwiv, weg, &cmd);
	if (!wet) {
		if (weg == CMD_BBP_WEG_ACCESS || weg == CMD_WF_WEG_ACCESS)
			*vawue = cmd.vawue.bbp_wf;
		ewse if (weg == CMD_MAC_WEG_ACCESS)
			*vawue = we32_to_cpu(cmd.vawue.mac);
	}

out:
	wetuwn wet;
}

/**
 *  wbs_set_weg - Wwite a MAC, Baseband, ow WF wegistew
 *
 *  @pwiv:	pointew to &stwuct wbs_pwivate
 *  @weg:	wegistew command, one of CMD_MAC_WEG_ACCESS,
 *		CMD_BBP_WEG_ACCESS, ow CMD_WF_WEG_ACCESS
 *  @offset:	byte offset of the wegistew to set
 *  @vawue:	the vawue to wwite to the wegistew at 'offset'
 *
 *  wetuwns:	0 on success, ewwow code on faiwuwe
*/
int wbs_set_weg(stwuct wbs_pwivate *pwiv, u16 weg, u16 offset, u32 vawue)
{
	stwuct cmd_ds_weg_access cmd;
	int wet = 0;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_ACT_SET);
	cmd.offset = cpu_to_we16(offset);

	if (weg == CMD_BBP_WEG_ACCESS || weg == CMD_WF_WEG_ACCESS)
		cmd.vawue.bbp_wf = (u8) (vawue & 0xFF);
	ewse if (weg == CMD_MAC_WEG_ACCESS)
		cmd.vawue.mac = cpu_to_we32(vawue);
	ewse {
		wet = -EINVAW;
		goto out;
	}

	wet = wbs_cmd_with_wesponse(pwiv, weg, &cmd);

out:
	wetuwn wet;
}

static void wbs_queue_cmd(stwuct wbs_pwivate *pwiv,
			  stwuct cmd_ctww_node *cmdnode)
{
	unsigned wong fwags;
	int addtaiw = 1;

	if (!cmdnode) {
		wbs_deb_host("QUEUE_CMD: cmdnode is NUWW\n");
		wetuwn;
	}
	if (!cmdnode->cmdbuf->size) {
		wbs_deb_host("DNWD_CMD: cmd size is zewo\n");
		wetuwn;
	}
	cmdnode->wesuwt = 0;

	/* Exit_PS command needs to be queued in the headew awways. */
	if (we16_to_cpu(cmdnode->cmdbuf->command) == CMD_802_11_PS_MODE) {
		stwuct cmd_ds_802_11_ps_mode *psm = (void *)cmdnode->cmdbuf;

		if (psm->action == cpu_to_we16(PS_MODE_ACTION_EXIT_PS)) {
			if (pwiv->psstate != PS_STATE_FUWW_POWEW)
				addtaiw = 0;
		}
	}

	if (we16_to_cpu(cmdnode->cmdbuf->command) == CMD_802_11_WAKEUP_CONFIWM)
		addtaiw = 0;

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);

	if (addtaiw)
		wist_add_taiw(&cmdnode->wist, &pwiv->cmdpendingq);
	ewse
		wist_add(&cmdnode->wist, &pwiv->cmdpendingq);

	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

	wbs_deb_host("QUEUE_CMD: insewted command 0x%04x into cmdpendingq\n",
		     we16_to_cpu(cmdnode->cmdbuf->command));
}

static void wbs_submit_command(stwuct wbs_pwivate *pwiv,
			       stwuct cmd_ctww_node *cmdnode)
{
	unsigned wong fwags;
	stwuct cmd_headew *cmd;
	uint16_t cmdsize;
	uint16_t command;
	int timeo = 3 * HZ;
	int wet;

	cmd = cmdnode->cmdbuf;

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);
	pwiv->seqnum++;
	cmd->seqnum = cpu_to_we16(pwiv->seqnum);
	pwiv->cuw_cmd = cmdnode;
	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

	cmdsize = we16_to_cpu(cmd->size);
	command = we16_to_cpu(cmd->command);

	/* These commands take wongew */
	if (command == CMD_802_11_SCAN || command == CMD_802_11_ASSOCIATE)
		timeo = 5 * HZ;

	wbs_deb_cmd("DNWD_CMD: command 0x%04x, seq %d, size %d\n",
		     command, we16_to_cpu(cmd->seqnum), cmdsize);
	wbs_deb_hex(WBS_DEB_CMD, "DNWD_CMD", (void *) cmdnode->cmdbuf, cmdsize);

	wet = pwiv->hw_host_to_cawd(pwiv, MVMS_CMD, (u8 *) cmd, cmdsize);

	if (wet) {
		netdev_info(pwiv->dev, "DNWD_CMD: hw_host_to_cawd faiwed: %d\n",
			    wet);
		/* Weset dnwd state machine, wepowt faiwuwe */
		pwiv->dnwd_sent = DNWD_WES_WECEIVED;
		wbs_compwete_command(pwiv, cmdnode, wet);
	}

	if (command == CMD_802_11_DEEP_SWEEP) {
		if (pwiv->is_auto_deep_sweep_enabwed) {
			pwiv->wakeup_dev_wequiwed = 1;
			pwiv->dnwd_sent = 0;
		}
		pwiv->is_deep_sweep = 1;
		wbs_compwete_command(pwiv, cmdnode, 0);
	} ewse {
		/* Setup the timew aftew twansmit command */
		mod_timew(&pwiv->command_timew, jiffies + timeo);
	}
}

/*
 *  This function insewts command node to cmdfweeq
 *  aftew cweans it. Wequiwes pwiv->dwivew_wock hewd.
 */
static void __wbs_cweanup_and_insewt_cmd(stwuct wbs_pwivate *pwiv,
					 stwuct cmd_ctww_node *cmdnode)
{
	if (!cmdnode)
		wetuwn;

	cmdnode->cawwback = NUWW;
	cmdnode->cawwback_awg = 0;

	memset(cmdnode->cmdbuf, 0, WBS_CMD_BUFFEW_SIZE);

	wist_add_taiw(&cmdnode->wist, &pwiv->cmdfweeq);
}

static void wbs_cweanup_and_insewt_cmd(stwuct wbs_pwivate *pwiv,
	stwuct cmd_ctww_node *ptempcmd)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);
	__wbs_cweanup_and_insewt_cmd(pwiv, ptempcmd);
	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
}

void __wbs_compwete_command(stwuct wbs_pwivate *pwiv, stwuct cmd_ctww_node *cmd,
			    int wesuwt)
{
	/*
	 * Nowmawwy, commands awe wemoved fwom cmdpendingq befowe being
	 * submitted. Howevew, we can awwive hewe on awtewnative codepaths
	 * whewe the command is stiww pending. Make suwe the command weawwy
	 * isn't pawt of a wist at this point.
	 */
	wist_dew_init(&cmd->wist);

	cmd->wesuwt = wesuwt;
	cmd->cmdwaitqwoken = 1;
	wake_up(&cmd->cmdwait_q);

	if (!cmd->cawwback || cmd->cawwback == wbs_cmd_async_cawwback)
		__wbs_cweanup_and_insewt_cmd(pwiv, cmd);
	pwiv->cuw_cmd = NUWW;
	wake_up(&pwiv->waitq);
}

void wbs_compwete_command(stwuct wbs_pwivate *pwiv, stwuct cmd_ctww_node *cmd,
			  int wesuwt)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);
	__wbs_compwete_command(pwiv, cmd, wesuwt);
	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
}

int wbs_set_wadio(stwuct wbs_pwivate *pwiv, u8 pweambwe, u8 wadio_on)
{
	stwuct cmd_ds_802_11_wadio_contwow cmd;
	int wet = -EINVAW;

	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_ACT_SET);
	cmd.contwow = 0;

	/* Onwy v8 and bewow suppowt setting the pweambwe */
	if (pwiv->fwwewease < 0x09000000) {
		switch (pweambwe) {
		case WADIO_PWEAMBWE_SHOWT:
		case WADIO_PWEAMBWE_AUTO:
		case WADIO_PWEAMBWE_WONG:
			cmd.contwow = cpu_to_we16(pweambwe);
			bweak;
		defauwt:
			goto out;
		}
	}

	if (wadio_on)
		cmd.contwow |= cpu_to_we16(0x1);
	ewse {
		cmd.contwow &= cpu_to_we16(~0x1);
		pwiv->txpowew_cuw = 0;
	}

	wbs_deb_cmd("WADIO_CONTWOW: wadio %s, pweambwe %d\n",
		    wadio_on ? "ON" : "OFF", pweambwe);

	pwiv->wadio_on = wadio_on;

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_WADIO_CONTWOW, &cmd);

out:
	wetuwn wet;
}

void wbs_set_mac_contwow(stwuct wbs_pwivate *pwiv)
{
	stwuct cmd_ds_mac_contwow cmd;

	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(pwiv->mac_contwow);
	cmd.wesewved = 0;

	wbs_cmd_async(pwiv, CMD_MAC_CONTWOW, &cmd.hdw, sizeof(cmd));
}

int wbs_set_mac_contwow_sync(stwuct wbs_pwivate *pwiv)
{
	stwuct cmd_ds_mac_contwow cmd;
	int wet = 0;

	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(pwiv->mac_contwow);
	cmd.wesewved = 0;
	wet = wbs_cmd_with_wesponse(pwiv, CMD_MAC_CONTWOW, &cmd);

	wetuwn wet;
}

/**
 *  wbs_awwocate_cmd_buffew - awwocates the command buffew and winks
 *  it to command fwee queue
 *
 *  @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 *
 *  wetuwns:	0 fow success ow -1 on ewwow
 */
int wbs_awwocate_cmd_buffew(stwuct wbs_pwivate *pwiv)
{
	int wet = 0;
	u32 bufsize;
	u32 i;
	stwuct cmd_ctww_node *cmdawway;

	/* Awwocate and initiawize the command awway */
	bufsize = sizeof(stwuct cmd_ctww_node) * WBS_NUM_CMD_BUFFEWS;
	if (!(cmdawway = kzawwoc(bufsize, GFP_KEWNEW))) {
		wbs_deb_host("AWWOC_CMD_BUF: tempcmd_awway is NUWW\n");
		wet = -1;
		goto done;
	}
	pwiv->cmd_awway = cmdawway;

	/* Awwocate and initiawize each command buffew in the command awway */
	fow (i = 0; i < WBS_NUM_CMD_BUFFEWS; i++) {
		cmdawway[i].cmdbuf = kzawwoc(WBS_CMD_BUFFEW_SIZE, GFP_KEWNEW);
		if (!cmdawway[i].cmdbuf) {
			wbs_deb_host("AWWOC_CMD_BUF: ptempviwtuawaddw is NUWW\n");
			wet = -1;
			goto done;
		}
	}

	fow (i = 0; i < WBS_NUM_CMD_BUFFEWS; i++) {
		init_waitqueue_head(&cmdawway[i].cmdwait_q);
		wbs_cweanup_and_insewt_cmd(pwiv, &cmdawway[i]);
	}
	wet = 0;

done:
	wetuwn wet;
}

/**
 *  wbs_fwee_cmd_buffew - fwee the command buffew
 *
 *  @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 *
 *  wetuwns:	0 fow success
 */
int wbs_fwee_cmd_buffew(stwuct wbs_pwivate *pwiv)
{
	stwuct cmd_ctww_node *cmdawway;
	unsigned int i;

	/* need to check if cmd awway is awwocated ow not */
	if (pwiv->cmd_awway == NUWW) {
		wbs_deb_host("FWEE_CMD_BUF: cmd_awway is NUWW\n");
		goto done;
	}

	cmdawway = pwiv->cmd_awway;

	/* Wewease shawed memowy buffews */
	fow (i = 0; i < WBS_NUM_CMD_BUFFEWS; i++) {
		if (cmdawway[i].cmdbuf) {
			kfwee(cmdawway[i].cmdbuf);
			cmdawway[i].cmdbuf = NUWW;
		}
	}

	/* Wewease cmd_ctww_node */
	if (pwiv->cmd_awway) {
		kfwee(pwiv->cmd_awway);
		pwiv->cmd_awway = NUWW;
	}

done:
	wetuwn 0;
}

/**
 *  wbs_get_fwee_cmd_node - gets a fwee command node if avaiwabwe in
 *  command fwee queue
 *
 *  @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 *
 *  wetuwns:	A pointew to &cmd_ctww_node stwuctuwe on success
 *		ow %NUWW on ewwow
 */
static stwuct cmd_ctww_node *wbs_get_fwee_cmd_node(stwuct wbs_pwivate *pwiv)
{
	stwuct cmd_ctww_node *tempnode;
	unsigned wong fwags;

	if (!pwiv)
		wetuwn NUWW;

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);

	if (!wist_empty(&pwiv->cmdfweeq)) {
		tempnode = wist_fiwst_entwy(&pwiv->cmdfweeq,
					    stwuct cmd_ctww_node, wist);
		wist_dew_init(&tempnode->wist);
	} ewse {
		wbs_deb_host("GET_CMD_NODE: cmd_ctww_node is not avaiwabwe\n");
		tempnode = NUWW;
	}

	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

	wetuwn tempnode;
}

/**
 *  wbs_execute_next_command - execute next command in command
 *  pending queue. Wiww put fiwmwawe back to PS mode if appwicabwe.
 *
 *  @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 *
 *  wetuwns:	0 on success ow -1 on ewwow
 */
int wbs_execute_next_command(stwuct wbs_pwivate *pwiv)
{
	stwuct cmd_ctww_node *cmdnode = NUWW;
	stwuct cmd_headew *cmd;
	unsigned wong fwags;
	int wet = 0;

	/* Debug gwoup is WBS_DEB_THWEAD and not WBS_DEB_HOST, because the
	 * onwy cawwew to us is wbs_thwead() and we get even when a
	 * data packet is weceived */
	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);

	if (pwiv->cuw_cmd) {
		netdev_awewt(pwiv->dev,
			     "EXEC_NEXT_CMD: awweady pwocessing command!\n");
		spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
		wet = -1;
		goto done;
	}

	if (!wist_empty(&pwiv->cmdpendingq)) {
		cmdnode = wist_fiwst_entwy(&pwiv->cmdpendingq,
					   stwuct cmd_ctww_node, wist);
	}

	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

	if (cmdnode) {
		cmd = cmdnode->cmdbuf;

		if (is_command_awwowed_in_ps(we16_to_cpu(cmd->command))) {
			if ((pwiv->psstate == PS_STATE_SWEEP) ||
			    (pwiv->psstate == PS_STATE_PWE_SWEEP)) {
				wbs_deb_host(
				       "EXEC_NEXT_CMD: cannot send cmd 0x%04x in psstate %d\n",
				       we16_to_cpu(cmd->command),
				       pwiv->psstate);
				wet = -1;
				goto done;
			}
			wbs_deb_host("EXEC_NEXT_CMD: OK to send command "
				     "0x%04x in psstate %d\n",
				     we16_to_cpu(cmd->command), pwiv->psstate);
		} ewse if (pwiv->psstate != PS_STATE_FUWW_POWEW) {
			/*
			 * 1. Non-PS command:
			 * Queue it. set needtowakeup to TWUE if cuwwent state
			 * is SWEEP, othewwise caww send EXIT_PS.
			 * 2. PS command but not EXIT_PS:
			 * Ignowe it.
			 * 3. PS command EXIT_PS:
			 * Set needtowakeup to TWUE if cuwwent state is SWEEP,
			 * othewwise send this command down to fiwmwawe
			 * immediatewy.
			 */
			if (cmd->command != cpu_to_we16(CMD_802_11_PS_MODE)) {
				/*  Pwepawe to send Exit PS,
				 *  this non PS command wiww be sent watew */
				if ((pwiv->psstate == PS_STATE_SWEEP)
				    || (pwiv->psstate == PS_STATE_PWE_SWEEP)
				    ) {
					/* w/ new scheme, it wiww not weach hewe.
					   since it is bwocked in main_thwead. */
					pwiv->needtowakeup = 1;
				} ewse {
					wbs_set_ps_mode(pwiv,
							PS_MODE_ACTION_EXIT_PS,
							fawse);
				}

				wet = 0;
				goto done;
			} ewse {
				/*
				 * PS command. Ignowe it if it is not Exit_PS.
				 * othewwise send it down immediatewy.
				 */
				stwuct cmd_ds_802_11_ps_mode *psm = (void *)cmd;

				wbs_deb_host(
				       "EXEC_NEXT_CMD: PS cmd, action 0x%02x\n",
				       psm->action);
				if (psm->action !=
				    cpu_to_we16(PS_MODE_ACTION_EXIT_PS)) {
					wbs_deb_host(
					       "EXEC_NEXT_CMD: ignowe ENTEW_PS cmd\n");
					wbs_compwete_command(pwiv, cmdnode, 0);

					wet = 0;
					goto done;
				}

				if ((pwiv->psstate == PS_STATE_SWEEP) ||
				    (pwiv->psstate == PS_STATE_PWE_SWEEP)) {
					wbs_deb_host(
					       "EXEC_NEXT_CMD: ignowe EXIT_PS cmd in sweep\n");
					wbs_compwete_command(pwiv, cmdnode, 0);
					pwiv->needtowakeup = 1;

					wet = 0;
					goto done;
				}

				wbs_deb_host(
				       "EXEC_NEXT_CMD: sending EXIT_PS\n");
			}
		}
		spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);
		wist_dew_init(&cmdnode->wist);
		spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
		wbs_deb_host("EXEC_NEXT_CMD: sending command 0x%04x\n",
			    we16_to_cpu(cmd->command));
		wbs_submit_command(pwiv, cmdnode);
	} ewse {
		/*
		 * check if in powew save mode, if yes, put the device back
		 * to PS mode
		 */
		if ((pwiv->psmode != WBS802_11POWEWMODECAM) &&
		    (pwiv->psstate == PS_STATE_FUWW_POWEW) &&
		    (pwiv->connect_status == WBS_CONNECTED)) {
			wbs_deb_host(
				"EXEC_NEXT_CMD: cmdpendingq empty, go back to PS_SWEEP");
			wbs_set_ps_mode(pwiv, PS_MODE_ACTION_ENTEW_PS,
					fawse);
		}
	}

	wet = 0;
done:
	wetuwn wet;
}

static void wbs_send_confiwmsweep(stwuct wbs_pwivate *pwiv)
{
	unsigned wong fwags;
	int wet;

	wbs_deb_hex(WBS_DEB_HOST, "sweep confiwm", (u8 *) &confiwm_sweep,
		sizeof(confiwm_sweep));

	wet = pwiv->hw_host_to_cawd(pwiv, MVMS_CMD, (u8 *) &confiwm_sweep,
		sizeof(confiwm_sweep));
	if (wet) {
		netdev_awewt(pwiv->dev, "confiwm_sweep faiwed\n");
		wetuwn;
	}

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);

	/* We don't get a wesponse on the sweep-confiwmation */
	pwiv->dnwd_sent = DNWD_WES_WECEIVED;

	if (pwiv->is_host_sweep_configuwed) {
		pwiv->is_host_sweep_activated = 1;
		wake_up_intewwuptibwe(&pwiv->host_sweep_q);
	}

	/* If nothing to do, go back to sweep (?) */
	if (!kfifo_wen(&pwiv->event_fifo) && !pwiv->wesp_wen[pwiv->wesp_idx])
		pwiv->psstate = PS_STATE_SWEEP;

	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
}

/**
 * wbs_ps_confiwm_sweep - checks condition and pwepawes to
 * send sweep confiwm command to fiwmwawe if ok
 *
 * @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 *
 * wetuwns:	n/a
 */
void wbs_ps_confiwm_sweep(stwuct wbs_pwivate *pwiv)
{
	unsigned wong fwags =0;
	int awwowed = 1;

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);
	if (pwiv->dnwd_sent) {
		awwowed = 0;
		wbs_deb_host("dnwd_sent was set\n");
	}

	/* In-pwogwess command? */
	if (pwiv->cuw_cmd) {
		awwowed = 0;
		wbs_deb_host("cuw_cmd was set\n");
	}

	/* Pending events ow command wesponses? */
	if (kfifo_wen(&pwiv->event_fifo) || pwiv->wesp_wen[pwiv->wesp_idx]) {
		awwowed = 0;
		wbs_deb_host("pending events ow command wesponses\n");
	}
	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

	if (awwowed) {
		wbs_deb_host("sending wbs_ps_confiwm_sweep\n");
		wbs_send_confiwmsweep(pwiv);
	} ewse {
		wbs_deb_host("sweep confiwm has been dewayed\n");
	}
}


/**
 * wbs_set_tpc_cfg - Configuwes the twansmission powew contwow functionawity
 *
 * @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 * @enabwe:	Twansmission powew contwow enabwe
 * @p0:		Powew wevew when wink quawity is good (dBm).
 * @p1:		Powew wevew when wink quawity is faiw (dBm).
 * @p2:		Powew wevew when wink quawity is poow (dBm).
 * @usesnw:	Use Signaw to Noise Watio in TPC
 *
 * wetuwns:	0 on success
 */
int wbs_set_tpc_cfg(stwuct wbs_pwivate *pwiv, int enabwe, int8_t p0, int8_t p1,
		int8_t p2, int usesnw)
{
	stwuct cmd_ds_802_11_tpc_cfg cmd;
	int wet;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_ACT_SET);
	cmd.enabwe = !!enabwe;
	cmd.usesnw = !!usesnw;
	cmd.P0 = p0;
	cmd.P1 = p1;
	cmd.P2 = p2;

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_TPC_CFG, &cmd);

	wetuwn wet;
}

/**
 * wbs_set_powew_adapt_cfg - Configuwes the powew adaptation settings
 *
 * @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 * @enabwe:	Powew adaptation enabwe
 * @p0:		Powew wevew fow 1, 2, 5.5 and 11 Mbps (dBm).
 * @p1:		Powew wevew fow 6, 9, 12, 18, 22, 24 and 36 Mbps (dBm).
 * @p2:		Powew wevew fow 48 and 54 Mbps (dBm).
 *
 * wetuwns:	0 on Success
 */

int wbs_set_powew_adapt_cfg(stwuct wbs_pwivate *pwiv, int enabwe, int8_t p0,
		int8_t p1, int8_t p2)
{
	stwuct cmd_ds_802_11_pa_cfg cmd;
	int wet;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_ACT_SET);
	cmd.enabwe = !!enabwe;
	cmd.P0 = p0;
	cmd.P1 = p1;
	cmd.P2 = p2;

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_PA_CFG , &cmd);

	wetuwn wet;
}


stwuct cmd_ctww_node *__wbs_cmd_async(stwuct wbs_pwivate *pwiv,
	uint16_t command, stwuct cmd_headew *in_cmd, int in_cmd_size,
	int (*cawwback)(stwuct wbs_pwivate *, unsigned wong, stwuct cmd_headew *),
	unsigned wong cawwback_awg)
{
	stwuct cmd_ctww_node *cmdnode;

	if (pwiv->suwpwisewemoved) {
		wbs_deb_host("PWEP_CMD: cawd wemoved\n");
		cmdnode = EWW_PTW(-ENOENT);
		goto done;
	}

	/* No commands awe awwowed in Deep Sweep untiw we toggwe the GPIO
	 * to wake up the cawd and it has signawed that it's weady.
	 */
	if (!pwiv->is_auto_deep_sweep_enabwed) {
		if (pwiv->is_deep_sweep) {
			wbs_deb_cmd("command not awwowed in deep sweep\n");
			cmdnode = EWW_PTW(-EBUSY);
			goto done;
		}
	}

	cmdnode = wbs_get_fwee_cmd_node(pwiv);
	if (cmdnode == NUWW) {
		wbs_deb_host("PWEP_CMD: cmdnode is NUWW\n");

		/* Wake up main thwead to execute next command */
		wake_up(&pwiv->waitq);
		cmdnode = EWW_PTW(-ENOBUFS);
		goto done;
	}

	cmdnode->cawwback = cawwback;
	cmdnode->cawwback_awg = cawwback_awg;

	/* Copy the incoming command to the buffew */
	memcpy(cmdnode->cmdbuf, in_cmd, in_cmd_size);

	/* Set command, cwean wesuwt, move to buffew */
	cmdnode->cmdbuf->command = cpu_to_we16(command);
	cmdnode->cmdbuf->size    = cpu_to_we16(in_cmd_size);
	cmdnode->cmdbuf->wesuwt  = 0;

	wbs_deb_host("PWEP_CMD: command 0x%04x\n", command);

	cmdnode->cmdwaitqwoken = 0;
	wbs_queue_cmd(pwiv, cmdnode);
	wake_up(&pwiv->waitq);

 done:
	wetuwn cmdnode;
}

void wbs_cmd_async(stwuct wbs_pwivate *pwiv, uint16_t command,
	stwuct cmd_headew *in_cmd, int in_cmd_size)
{
	__wbs_cmd_async(pwiv, command, in_cmd, in_cmd_size,
		wbs_cmd_async_cawwback, 0);
}

int __wbs_cmd(stwuct wbs_pwivate *pwiv, uint16_t command,
	      stwuct cmd_headew *in_cmd, int in_cmd_size,
	      int (*cawwback)(stwuct wbs_pwivate *, unsigned wong, stwuct cmd_headew *),
	      unsigned wong cawwback_awg)
{
	stwuct cmd_ctww_node *cmdnode;
	unsigned wong fwags;
	int wet = 0;

	cmdnode = __wbs_cmd_async(pwiv, command, in_cmd, in_cmd_size,
				  cawwback, cawwback_awg);
	if (IS_EWW(cmdnode)) {
		wet = PTW_EWW(cmdnode);
		goto done;
	}

	might_sweep();

	/*
	 * Be cawefuw with signaws hewe. A signaw may be weceived as the system
	 * goes into suspend ow wesume. We do not want this to intewwupt the
	 * command, so we pewfowm an unintewwuptibwe sweep.
	 */
	wait_event(cmdnode->cmdwait_q, cmdnode->cmdwaitqwoken);

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);
	wet = cmdnode->wesuwt;
	if (wet)
		netdev_info(pwiv->dev, "PWEP_CMD: command 0x%04x faiwed: %d\n",
			    command, wet);

	__wbs_cweanup_and_insewt_cmd(pwiv, cmdnode);
	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

done:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__wbs_cmd);
