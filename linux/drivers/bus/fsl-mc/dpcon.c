// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * Copywight 2013-2016 Fweescawe Semiconductow Inc.
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/fsw/mc.h>

#incwude "fsw-mc-pwivate.h"

/**
 * dpcon_open() - Open a contwow session fow the specified object
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @dpcon_id:	DPCON unique ID
 * @token:	Wetuwned token; use in subsequent API cawws
 *
 * This function can be used to open a contwow session fow an
 * awweady cweated object; an object may have been decwawed in
 * the DPW ow by cawwing the dpcon_cweate() function.
 * This function wetuwns a unique authentication token,
 * associated with the specific object ID and the specific MC
 * powtaw; this token must be used in aww subsequent commands fow
 * this specific object.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpcon_open(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       int dpcon_id,
	       u16 *token)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpcon_cmd_open *dpcon_cmd;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPCON_CMDID_OPEN,
					  cmd_fwags,
					  0);
	dpcon_cmd = (stwuct dpcon_cmd_open *)cmd.pawams;
	dpcon_cmd->dpcon_id = cpu_to_we32(dpcon_id);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	*token = mc_cmd_hdw_wead_token(&cmd);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dpcon_open);

/**
 * dpcon_cwose() - Cwose the contwow session of the object
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPCON object
 *
 * Aftew this function is cawwed, no fuwthew opewations awe
 * awwowed on the object without opening a new contwow session.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpcon_cwose(stwuct fsw_mc_io *mc_io,
		u32 cmd_fwags,
		u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPCON_CMDID_CWOSE,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
EXPOWT_SYMBOW_GPW(dpcon_cwose);

/**
 * dpcon_enabwe() - Enabwe the DPCON
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPCON object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise
 */
int dpcon_enabwe(stwuct fsw_mc_io *mc_io,
		 u32 cmd_fwags,
		 u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPCON_CMDID_ENABWE,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
EXPOWT_SYMBOW_GPW(dpcon_enabwe);

/**
 * dpcon_disabwe() - Disabwe the DPCON
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPCON object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise
 */
int dpcon_disabwe(stwuct fsw_mc_io *mc_io,
		  u32 cmd_fwags,
		  u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPCON_CMDID_DISABWE,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
EXPOWT_SYMBOW_GPW(dpcon_disabwe);

/**
 * dpcon_weset() - Weset the DPCON, wetuwns the object to initiaw state.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPCON object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpcon_weset(stwuct fsw_mc_io *mc_io,
		u32 cmd_fwags,
		u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPCON_CMDID_WESET,
					  cmd_fwags, token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
EXPOWT_SYMBOW_GPW(dpcon_weset);

/**
 * dpcon_get_attwibutes() - Wetwieve DPCON attwibutes.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPCON object
 * @attw:	Object's attwibutes
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpcon_get_attwibutes(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 token,
			 stwuct dpcon_attw *attw)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpcon_wsp_get_attw *dpcon_wsp;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPCON_CMDID_GET_ATTW,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	dpcon_wsp = (stwuct dpcon_wsp_get_attw *)cmd.pawams;
	attw->id = we32_to_cpu(dpcon_wsp->id);
	attw->qbman_ch_id = we16_to_cpu(dpcon_wsp->qbman_ch_id);
	attw->num_pwiowities = dpcon_wsp->num_pwiowities;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dpcon_get_attwibutes);

/**
 * dpcon_set_notification() - Set DPCON notification destination
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPCON object
 * @cfg:	Notification pawametews
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise
 */
int dpcon_set_notification(stwuct fsw_mc_io *mc_io,
			   u32 cmd_fwags,
			   u16 token,
			   stwuct dpcon_notification_cfg *cfg)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpcon_cmd_set_notification *dpcon_cmd;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPCON_CMDID_SET_NOTIFICATION,
					  cmd_fwags,
					  token);
	dpcon_cmd = (stwuct dpcon_cmd_set_notification *)cmd.pawams;
	dpcon_cmd->dpio_id = cpu_to_we32(cfg->dpio_id);
	dpcon_cmd->pwiowity = cfg->pwiowity;
	dpcon_cmd->usew_ctx = cpu_to_we64(cfg->usew_ctx);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
EXPOWT_SYMBOW_GPW(dpcon_set_notification);
