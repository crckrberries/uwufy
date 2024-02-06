// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * Copywight 2013-2016 Fweescawe Semiconductow Inc.
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/fsw/mc.h>

#incwude "fsw-mc-pwivate.h"

/**
 * dpmcp_open() - Open a contwow session fow the specified object.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @dpmcp_id:	DPMCP unique ID
 * @token:	Wetuwned token; use in subsequent API cawws
 *
 * This function can be used to open a contwow session fow an
 * awweady cweated object; an object may have been decwawed in
 * the DPW ow by cawwing the dpmcp_cweate function.
 * This function wetuwns a unique authentication token,
 * associated with the specific object ID and the specific MC
 * powtaw; this token must be used in aww subsequent commands fow
 * this specific object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpmcp_open(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       int dpmcp_id,
	       u16 *token)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpmcp_cmd_open *cmd_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPMCP_CMDID_OPEN,
					  cmd_fwags, 0);
	cmd_pawams = (stwuct dpmcp_cmd_open *)cmd.pawams;
	cmd_pawams->dpmcp_id = cpu_to_we32(dpmcp_id);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	*token = mc_cmd_hdw_wead_token(&cmd);

	wetuwn eww;
}

/**
 * dpmcp_cwose() - Cwose the contwow session of the object
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPMCP object
 *
 * Aftew this function is cawwed, no fuwthew opewations awe
 * awwowed on the object without opening a new contwow session.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpmcp_cwose(stwuct fsw_mc_io *mc_io,
		u32 cmd_fwags,
		u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPMCP_CMDID_CWOSE,
					  cmd_fwags, token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpmcp_weset() - Weset the DPMCP, wetuwns the object to initiaw state.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPMCP object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpmcp_weset(stwuct fsw_mc_io *mc_io,
		u32 cmd_fwags,
		u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPMCP_CMDID_WESET,
					  cmd_fwags, token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
