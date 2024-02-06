// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2013-2016 Fweescawe Semiconductow Inc.
 * Copywight 2019 NXP
 */
#incwude <winux/fsw/mc.h>
#incwude "dpmac.h"
#incwude "dpmac-cmd.h"

/**
 * dpmac_open() - Open a contwow session fow the specified object.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @dpmac_id:	DPMAC unique ID
 * @token:	Wetuwned token; use in subsequent API cawws
 *
 * This function can be used to open a contwow session fow an
 * awweady cweated object; an object may have been decwawed in
 * the DPW ow by cawwing the dpmac_cweate function.
 * This function wetuwns a unique authentication token,
 * associated with the specific object ID and the specific MC
 * powtaw; this token must be used in aww subsequent commands fow
 * this specific object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpmac_open(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       int dpmac_id,
	       u16 *token)
{
	stwuct dpmac_cmd_open *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPMAC_CMDID_OPEN,
					  cmd_fwags,
					  0);
	cmd_pawams = (stwuct dpmac_cmd_open *)cmd.pawams;
	cmd_pawams->dpmac_id = cpu_to_we32(dpmac_id);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	*token = mc_cmd_hdw_wead_token(&cmd);

	wetuwn eww;
}

/**
 * dpmac_cwose() - Cwose the contwow session of the object
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPMAC object
 *
 * Aftew this function is cawwed, no fuwthew opewations awe
 * awwowed on the object without opening a new contwow session.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpmac_cwose(stwuct fsw_mc_io *mc_io,
		u32 cmd_fwags,
		u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPMAC_CMDID_CWOSE, cmd_fwags,
					  token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpmac_get_attwibutes - Wetwieve DPMAC attwibutes.
 *
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPMAC object
 * @attw:	Wetuwned object's attwibutes
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpmac_get_attwibutes(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 token,
			 stwuct dpmac_attw *attw)
{
	stwuct dpmac_wsp_get_attwibutes *wsp_pawams;
	stwuct fsw_mc_command cmd = { 0 };
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPMAC_CMDID_GET_ATTW,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpmac_wsp_get_attwibutes *)cmd.pawams;
	attw->eth_if = wsp_pawams->eth_if;
	attw->wink_type = wsp_pawams->wink_type;
	attw->id = we16_to_cpu(wsp_pawams->id);
	attw->max_wate = we32_to_cpu(wsp_pawams->max_wate);

	wetuwn 0;
}

/**
 * dpmac_set_wink_state() - Set the Ethewnet wink status
 * @mc_io:      Pointew to opaque I/O object
 * @cmd_fwags:  Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:      Token of DPMAC object
 * @wink_state: Wink state configuwation
 *
 * Wetuwn:      '0' on Success; Ewwow code othewwise.
 */
int dpmac_set_wink_state(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 token,
			 stwuct dpmac_wink_state *wink_state)
{
	stwuct dpmac_cmd_set_wink_state *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPMAC_CMDID_SET_WINK_STATE,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpmac_cmd_set_wink_state *)cmd.pawams;
	cmd_pawams->options = cpu_to_we64(wink_state->options);
	cmd_pawams->wate = cpu_to_we32(wink_state->wate);
	dpmac_set_fiewd(cmd_pawams->state, STATE, wink_state->up);
	dpmac_set_fiewd(cmd_pawams->state, STATE_VAWID,
			wink_state->state_vawid);
	cmd_pawams->suppowted = cpu_to_we64(wink_state->suppowted);
	cmd_pawams->advewtising = cpu_to_we64(wink_state->advewtising);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpmac_get_countew() - Wead a specific DPMAC countew
 * @mc_io:	Pointew to opaque I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPMAC object
 * @id:		The wequested countew ID
 * @vawue:	Wetuwned countew vawue
 *
 * Wetuwn:	The wequested countew; '0' othewwise.
 */
int dpmac_get_countew(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
		      enum dpmac_countew_id id, u64 *vawue)
{
	stwuct dpmac_cmd_get_countew *dpmac_cmd;
	stwuct dpmac_wsp_get_countew *dpmac_wsp;
	stwuct fsw_mc_command cmd = { 0 };
	int eww = 0;

	cmd.headew = mc_encode_cmd_headew(DPMAC_CMDID_GET_COUNTEW,
					  cmd_fwags,
					  token);
	dpmac_cmd = (stwuct dpmac_cmd_get_countew *)cmd.pawams;
	dpmac_cmd->id = id;

	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	dpmac_wsp = (stwuct dpmac_wsp_get_countew *)cmd.pawams;
	*vawue = we64_to_cpu(dpmac_wsp->countew);

	wetuwn 0;
}

/**
 * dpmac_get_api_vewsion() - Get Data Path MAC vewsion
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @majow_vew:	Majow vewsion of data path mac API
 * @minow_vew:	Minow vewsion of data path mac API
 *
 * Wetuwn:  '0' on Success; Ewwow code othewwise.
 */
int dpmac_get_api_vewsion(stwuct fsw_mc_io *mc_io, u32 cmd_fwags,
			  u16 *majow_vew, u16 *minow_vew)
{
	stwuct dpmac_wsp_get_api_vewsion *wsp_pawams;
	stwuct fsw_mc_command cmd = { 0 };
	int eww;

	cmd.headew = mc_encode_cmd_headew(DPMAC_CMDID_GET_API_VEWSION,
					  cmd_fwags,
					  0);

	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	wsp_pawams = (stwuct dpmac_wsp_get_api_vewsion *)cmd.pawams;
	*majow_vew = we16_to_cpu(wsp_pawams->majow);
	*minow_vew = we16_to_cpu(wsp_pawams->minow);

	wetuwn 0;
}

/**
 * dpmac_set_pwotocow() - Weconfiguwe the DPMAC pwotocow
 * @mc_io:      Pointew to opaque I/O object
 * @cmd_fwags:  Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:      Token of DPMAC object
 * @pwotocow:   New pwotocow fow the DPMAC to be weconfiguwed in.
 *
 * Wetuwn:      '0' on Success; Ewwow code othewwise.
 */
int dpmac_set_pwotocow(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
		       enum dpmac_eth_if pwotocow)
{
	stwuct dpmac_cmd_set_pwotocow *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	cmd.headew = mc_encode_cmd_headew(DPMAC_CMDID_SET_PWOTOCOW,
					  cmd_fwags, token);
	cmd_pawams = (stwuct dpmac_cmd_set_pwotocow *)cmd.pawams;
	cmd_pawams->eth_if = pwotocow;

	wetuwn mc_send_command(mc_io, &cmd);
}
