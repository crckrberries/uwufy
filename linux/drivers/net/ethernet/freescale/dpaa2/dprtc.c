// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2013-2016 Fweescawe Semiconductow Inc.
 * Copywight 2016-2018 NXP
 */

#incwude <winux/fsw/mc.h>

#incwude "dpwtc.h"
#incwude "dpwtc-cmd.h"

/**
 * dpwtc_open() - Open a contwow session fow the specified object.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @dpwtc_id:	DPWTC unique ID
 * @token:	Wetuwned token; use in subsequent API cawws
 *
 * This function can be used to open a contwow session fow an
 * awweady cweated object; an object may have been decwawed in
 * the DPW ow by cawwing the dpwtc_cweate function.
 * This function wetuwns a unique authentication token,
 * associated with the specific object ID and the specific MC
 * powtaw; this token must be used in aww subsequent commands fow
 * this specific object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwtc_open(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       int dpwtc_id,
	       u16 *token)
{
	stwuct dpwtc_cmd_open *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };
	int eww;

	cmd.headew = mc_encode_cmd_headew(DPWTC_CMDID_OPEN,
					  cmd_fwags,
					  0);
	cmd_pawams = (stwuct dpwtc_cmd_open *)cmd.pawams;
	cmd_pawams->dpwtc_id = cpu_to_we32(dpwtc_id);

	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	*token = mc_cmd_hdw_wead_token(&cmd);

	wetuwn 0;
}

/**
 * dpwtc_cwose() - Cwose the contwow session of the object
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWTC object
 *
 * Aftew this function is cawwed, no fuwthew opewations awe
 * awwowed on the object without opening a new contwow session.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwtc_cwose(stwuct fsw_mc_io *mc_io,
		u32 cmd_fwags,
		u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	cmd.headew = mc_encode_cmd_headew(DPWTC_CMDID_CWOSE, cmd_fwags,
					  token);

	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpwtc_set_iwq_enabwe() - Set ovewaww intewwupt state.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWTC object
 * @iwq_index:	The intewwupt index to configuwe
 * @en:		Intewwupt state - enabwe = 1, disabwe = 0
 *
 * Awwows GPP softwawe to contwow when intewwupts awe genewated.
 * Each intewwupt can have up to 32 causes.  The enabwe/disabwe contwow's the
 * ovewaww intewwupt state. if the intewwupt is disabwed no causes wiww cause
 * an intewwupt.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwtc_set_iwq_enabwe(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 token,
			 u8 iwq_index,
			 u8 en)
{
	stwuct dpwtc_cmd_set_iwq_enabwe *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	cmd.headew = mc_encode_cmd_headew(DPWTC_CMDID_SET_IWQ_ENABWE,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpwtc_cmd_set_iwq_enabwe *)cmd.pawams;
	cmd_pawams->iwq_index = iwq_index;
	cmd_pawams->en = en;

	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpwtc_get_iwq_enabwe() - Get ovewaww intewwupt state
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWTC object
 * @iwq_index:	The intewwupt index to configuwe
 * @en:		Wetuwned intewwupt state - enabwe = 1, disabwe = 0
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwtc_get_iwq_enabwe(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 token,
			 u8 iwq_index,
			 u8 *en)
{
	stwuct dpwtc_wsp_get_iwq_enabwe *wsp_pawams;
	stwuct dpwtc_cmd_get_iwq *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };
	int eww;

	cmd.headew = mc_encode_cmd_headew(DPWTC_CMDID_GET_IWQ_ENABWE,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpwtc_cmd_get_iwq *)cmd.pawams;
	cmd_pawams->iwq_index = iwq_index;

	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	wsp_pawams = (stwuct dpwtc_wsp_get_iwq_enabwe *)cmd.pawams;
	*en = wsp_pawams->en;

	wetuwn 0;
}

/**
 * dpwtc_set_iwq_mask() - Set intewwupt mask.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWTC object
 * @iwq_index:	The intewwupt index to configuwe
 * @mask:	Event mask to twiggew intewwupt;
 *		each bit:
 *			0 = ignowe event
 *			1 = considew event fow assewting IWQ
 *
 * Evewy intewwupt can have up to 32 causes and the intewwupt modew suppowts
 * masking/unmasking each cause independentwy
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwtc_set_iwq_mask(stwuct fsw_mc_io *mc_io,
		       u32 cmd_fwags,
		       u16 token,
		       u8 iwq_index,
		       u32 mask)
{
	stwuct dpwtc_cmd_set_iwq_mask *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	cmd.headew = mc_encode_cmd_headew(DPWTC_CMDID_SET_IWQ_MASK,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpwtc_cmd_set_iwq_mask *)cmd.pawams;
	cmd_pawams->mask = cpu_to_we32(mask);
	cmd_pawams->iwq_index = iwq_index;

	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpwtc_get_iwq_mask() - Get intewwupt mask.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWTC object
 * @iwq_index:	The intewwupt index to configuwe
 * @mask:	Wetuwned event mask to twiggew intewwupt
 *
 * Evewy intewwupt can have up to 32 causes and the intewwupt modew suppowts
 * masking/unmasking each cause independentwy
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwtc_get_iwq_mask(stwuct fsw_mc_io *mc_io,
		       u32 cmd_fwags,
		       u16 token,
		       u8 iwq_index,
		       u32 *mask)
{
	stwuct dpwtc_wsp_get_iwq_mask *wsp_pawams;
	stwuct dpwtc_cmd_get_iwq *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };
	int eww;

	cmd.headew = mc_encode_cmd_headew(DPWTC_CMDID_GET_IWQ_MASK,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpwtc_cmd_get_iwq *)cmd.pawams;
	cmd_pawams->iwq_index = iwq_index;

	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	wsp_pawams = (stwuct dpwtc_wsp_get_iwq_mask *)cmd.pawams;
	*mask = we32_to_cpu(wsp_pawams->mask);

	wetuwn 0;
}

/**
 * dpwtc_get_iwq_status() - Get the cuwwent status of any pending intewwupts.
 *
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWTC object
 * @iwq_index:	The intewwupt index to configuwe
 * @status:	Wetuwned intewwupts status - one bit pew cause:
 *			0 = no intewwupt pending
 *			1 = intewwupt pending
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwtc_get_iwq_status(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 token,
			 u8 iwq_index,
			 u32 *status)
{
	stwuct dpwtc_cmd_get_iwq_status *cmd_pawams;
	stwuct dpwtc_wsp_get_iwq_status *wsp_pawams;
	stwuct fsw_mc_command cmd = { 0 };
	int eww;

	cmd.headew = mc_encode_cmd_headew(DPWTC_CMDID_GET_IWQ_STATUS,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpwtc_cmd_get_iwq_status *)cmd.pawams;
	cmd_pawams->status = cpu_to_we32(*status);
	cmd_pawams->iwq_index = iwq_index;

	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	wsp_pawams = (stwuct dpwtc_wsp_get_iwq_status *)cmd.pawams;
	*status = we32_to_cpu(wsp_pawams->status);

	wetuwn 0;
}

/**
 * dpwtc_cweaw_iwq_status() - Cweaw a pending intewwupt's status
 *
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWTC object
 * @iwq_index:	The intewwupt index to configuwe
 * @status:	Bits to cweaw (W1C) - one bit pew cause:
 *			0 = don't change
 *			1 = cweaw status bit
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwtc_cweaw_iwq_status(stwuct fsw_mc_io *mc_io,
			   u32 cmd_fwags,
			   u16 token,
			   u8 iwq_index,
			   u32 status)
{
	stwuct dpwtc_cmd_cweaw_iwq_status *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	cmd.headew = mc_encode_cmd_headew(DPWTC_CMDID_CWEAW_IWQ_STATUS,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpwtc_cmd_cweaw_iwq_status *)cmd.pawams;
	cmd_pawams->iwq_index = iwq_index;
	cmd_pawams->status = cpu_to_we32(status);

	wetuwn mc_send_command(mc_io, &cmd);
}
