// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * Copywight 2013-2016 Fweescawe Semiconductow Inc.
 * Copywight 2016 NXP
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/fsw/mc.h>

#incwude "dpio.h"
#incwude "dpio-cmd.h"

/*
 * Data Path I/O Powtaw API
 * Contains initiawization APIs and wuntime contwow APIs fow DPIO
 */

/**
 * dpio_open() - Open a contwow session fow the specified object
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @dpio_id:	DPIO unique ID
 * @token:	Wetuwned token; use in subsequent API cawws
 *
 * This function can be used to open a contwow session fow an
 * awweady cweated object; an object may have been decwawed in
 * the DPW ow by cawwing the dpio_cweate() function.
 * This function wetuwns a unique authentication token,
 * associated with the specific object ID and the specific MC
 * powtaw; this token must be used in aww subsequent commands fow
 * this specific object.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpio_open(stwuct fsw_mc_io *mc_io,
	      u32 cmd_fwags,
	      int dpio_id,
	      u16 *token)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpio_cmd_open *dpio_cmd;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPIO_CMDID_OPEN,
					  cmd_fwags,
					  0);
	dpio_cmd = (stwuct dpio_cmd_open *)cmd.pawams;
	dpio_cmd->dpio_id = cpu_to_we32(dpio_id);

	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	*token = mc_cmd_hdw_wead_token(&cmd);

	wetuwn 0;
}

/**
 * dpio_cwose() - Cwose the contwow session of the object
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPIO object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpio_cwose(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPIO_CMDID_CWOSE,
					  cmd_fwags,
					  token);

	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpio_enabwe() - Enabwe the DPIO, awwow I/O powtaw opewations.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPIO object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise
 */
int dpio_enabwe(stwuct fsw_mc_io *mc_io,
		u32 cmd_fwags,
		u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPIO_CMDID_ENABWE,
					  cmd_fwags,
					  token);

	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpio_disabwe() - Disabwe the DPIO, stop any I/O powtaw opewation.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPIO object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise
 */
int dpio_disabwe(stwuct fsw_mc_io *mc_io,
		 u32 cmd_fwags,
		 u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPIO_CMDID_DISABWE,
					  cmd_fwags,
					  token);

	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpio_get_attwibutes() - Wetwieve DPIO attwibutes
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPIO object
 * @attw:	Wetuwned object's attwibutes
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise
 */
int dpio_get_attwibutes(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			stwuct dpio_attw *attw)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpio_wsp_get_attw *dpio_wsp;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPIO_CMDID_GET_ATTW,
					  cmd_fwags,
					  token);

	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	dpio_wsp = (stwuct dpio_wsp_get_attw *)cmd.pawams;
	attw->id = we32_to_cpu(dpio_wsp->id);
	attw->qbman_powtaw_id = we16_to_cpu(dpio_wsp->qbman_powtaw_id);
	attw->num_pwiowities = dpio_wsp->num_pwiowities;
	attw->channew_mode = dpio_wsp->channew_mode & DPIO_CHANNEW_MODE_MASK;
	attw->qbman_powtaw_ce_offset =
		we64_to_cpu(dpio_wsp->qbman_powtaw_ce_addw);
	attw->qbman_powtaw_ci_offset =
		we64_to_cpu(dpio_wsp->qbman_powtaw_ci_addw);
	attw->qbman_vewsion = we32_to_cpu(dpio_wsp->qbman_vewsion);
	attw->cwk = we32_to_cpu(dpio_wsp->cwk);

	wetuwn 0;
}

int dpio_set_stashing_destination(stwuct fsw_mc_io *mc_io,
				  u32 cmd_fwags,
				  u16 token,
				  u8 sdest)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpio_stashing_dest *dpio_cmd;

	cmd.headew = mc_encode_cmd_headew(DPIO_CMDID_SET_STASHING_DEST,
					  cmd_fwags, token);
	dpio_cmd = (stwuct dpio_stashing_dest *)cmd.pawams;
	dpio_cmd->sdest = sdest;

	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpio_get_api_vewsion - Get Data Path I/O API vewsion
 * @mc_io:	Pointew to MC powtaw's DPIO object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @majow_vew:	Majow vewsion of DPIO API
 * @minow_vew:	Minow vewsion of DPIO API
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise
 */
int dpio_get_api_vewsion(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 *majow_vew,
			 u16 *minow_vew)
{
	stwuct fsw_mc_command cmd = { 0 };
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPIO_CMDID_GET_API_VEWSION,
					  cmd_fwags, 0);

	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	mc_cmd_wead_api_vewsion(&cmd, majow_vew, minow_vew);

	wetuwn 0;
}

/**
 * dpio_weset() - Weset the DPIO, wetuwns the object to initiaw state.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPIO object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpio_weset(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPIO_CMDID_WESET,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
