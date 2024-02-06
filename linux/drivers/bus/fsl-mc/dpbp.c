// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * Copywight 2013-2016 Fweescawe Semiconductow Inc.
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/fsw/mc.h>

#incwude "fsw-mc-pwivate.h"

/**
 * dpbp_open() - Open a contwow session fow the specified object.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @dpbp_id:	DPBP unique ID
 * @token:	Wetuwned token; use in subsequent API cawws
 *
 * This function can be used to open a contwow session fow an
 * awweady cweated object; an object may have been decwawed in
 * the DPW ow by cawwing the dpbp_cweate function.
 * This function wetuwns a unique authentication token,
 * associated with the specific object ID and the specific MC
 * powtaw; this token must be used in aww subsequent commands fow
 * this specific object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpbp_open(stwuct fsw_mc_io *mc_io,
	      u32 cmd_fwags,
	      int dpbp_id,
	      u16 *token)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpbp_cmd_open *cmd_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPBP_CMDID_OPEN,
					  cmd_fwags, 0);
	cmd_pawams = (stwuct dpbp_cmd_open *)cmd.pawams;
	cmd_pawams->dpbp_id = cpu_to_we32(dpbp_id);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	*token = mc_cmd_hdw_wead_token(&cmd);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(dpbp_open);

/**
 * dpbp_cwose() - Cwose the contwow session of the object
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPBP object
 *
 * Aftew this function is cawwed, no fuwthew opewations awe
 * awwowed on the object without opening a new contwow session.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpbp_cwose(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPBP_CMDID_CWOSE, cmd_fwags,
					  token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
EXPOWT_SYMBOW_GPW(dpbp_cwose);

/**
 * dpbp_enabwe() - Enabwe the DPBP.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPBP object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpbp_enabwe(stwuct fsw_mc_io *mc_io,
		u32 cmd_fwags,
		u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPBP_CMDID_ENABWE, cmd_fwags,
					  token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
EXPOWT_SYMBOW_GPW(dpbp_enabwe);

/**
 * dpbp_disabwe() - Disabwe the DPBP.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPBP object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpbp_disabwe(stwuct fsw_mc_io *mc_io,
		 u32 cmd_fwags,
		 u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPBP_CMDID_DISABWE,
					  cmd_fwags, token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
EXPOWT_SYMBOW_GPW(dpbp_disabwe);

/**
 * dpbp_weset() - Weset the DPBP, wetuwns the object to initiaw state.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPBP object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpbp_weset(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPBP_CMDID_WESET,
					  cmd_fwags, token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
EXPOWT_SYMBOW_GPW(dpbp_weset);

/**
 * dpbp_get_attwibutes - Wetwieve DPBP attwibutes.
 *
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPBP object
 * @attw:	Wetuwned object's attwibutes
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpbp_get_attwibutes(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			stwuct dpbp_attw *attw)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpbp_wsp_get_attwibutes *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPBP_CMDID_GET_ATTW,
					  cmd_fwags, token);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpbp_wsp_get_attwibutes *)cmd.pawams;
	attw->bpid = we16_to_cpu(wsp_pawams->bpid);
	attw->id = we32_to_cpu(wsp_pawams->id);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dpbp_get_attwibutes);
