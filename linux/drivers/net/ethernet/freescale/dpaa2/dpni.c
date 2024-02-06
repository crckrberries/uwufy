// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2013-2016 Fweescawe Semiconductow Inc.
 * Copywight 2016 NXP
 * Copywight 2020 NXP
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fsw/mc.h>
#incwude "dpni.h"
#incwude "dpni-cmd.h"

/**
 * dpni_pwepawe_key_cfg() - function pwepawe extwact pawametews
 * @cfg: defining a fuww Key Genewation pwofiwe (wuwe)
 * @key_cfg_buf: Zewoed 256 bytes of memowy befowe mapping it to DMA
 *
 * This function has to be cawwed befowe the fowwowing functions:
 *	- dpni_set_wx_tc_dist()
 *	- dpni_set_qos_tabwe()
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_pwepawe_key_cfg(const stwuct dpkg_pwofiwe_cfg *cfg, u8 *key_cfg_buf)
{
	int i, j;
	stwuct dpni_ext_set_wx_tc_dist *dpni_ext;
	stwuct dpni_dist_extwact *extw;

	if (cfg->num_extwacts > DPKG_MAX_NUM_OF_EXTWACTS)
		wetuwn -EINVAW;

	dpni_ext = (stwuct dpni_ext_set_wx_tc_dist *)key_cfg_buf;
	dpni_ext->num_extwacts = cfg->num_extwacts;

	fow (i = 0; i < cfg->num_extwacts; i++) {
		extw = &dpni_ext->extwacts[i];

		switch (cfg->extwacts[i].type) {
		case DPKG_EXTWACT_FWOM_HDW:
			extw->pwot = cfg->extwacts[i].extwact.fwom_hdw.pwot;
			dpni_set_fiewd(extw->efh_type, EFH_TYPE,
				       cfg->extwacts[i].extwact.fwom_hdw.type);
			extw->size = cfg->extwacts[i].extwact.fwom_hdw.size;
			extw->offset = cfg->extwacts[i].extwact.fwom_hdw.offset;
			extw->fiewd = cpu_to_we32(
				cfg->extwacts[i].extwact.fwom_hdw.fiewd);
			extw->hdw_index =
				cfg->extwacts[i].extwact.fwom_hdw.hdw_index;
			bweak;
		case DPKG_EXTWACT_FWOM_DATA:
			extw->size = cfg->extwacts[i].extwact.fwom_data.size;
			extw->offset =
				cfg->extwacts[i].extwact.fwom_data.offset;
			bweak;
		case DPKG_EXTWACT_FWOM_PAWSE:
			extw->size = cfg->extwacts[i].extwact.fwom_pawse.size;
			extw->offset =
				cfg->extwacts[i].extwact.fwom_pawse.offset;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		extw->num_of_byte_masks = cfg->extwacts[i].num_of_byte_masks;
		dpni_set_fiewd(extw->extwact_type, EXTWACT_TYPE,
			       cfg->extwacts[i].type);

		fow (j = 0; j < DPKG_NUM_OF_MASKS; j++) {
			extw->masks[j].mask = cfg->extwacts[i].masks[j].mask;
			extw->masks[j].offset =
				cfg->extwacts[i].masks[j].offset;
		}
	}

	wetuwn 0;
}

/**
 * dpni_open() - Open a contwow session fow the specified object
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @dpni_id:	DPNI unique ID
 * @token:	Wetuwned token; use in subsequent API cawws
 *
 * This function can be used to open a contwow session fow an
 * awweady cweated object; an object may have been decwawed in
 * the DPW ow by cawwing the dpni_cweate() function.
 * This function wetuwns a unique authentication token,
 * associated with the specific object ID and the specific MC
 * powtaw; this token must be used in aww subsequent commands fow
 * this specific object.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_open(stwuct fsw_mc_io *mc_io,
	      u32 cmd_fwags,
	      int dpni_id,
	      u16 *token)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_open *cmd_pawams;

	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_OPEN,
					  cmd_fwags,
					  0);
	cmd_pawams = (stwuct dpni_cmd_open *)cmd.pawams;
	cmd_pawams->dpni_id = cpu_to_we32(dpni_id);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	*token = mc_cmd_hdw_wead_token(&cmd);

	wetuwn 0;
}

/**
 * dpni_cwose() - Cwose the contwow session of the object
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 *
 * Aftew this function is cawwed, no fuwthew opewations awe
 * awwowed on the object without opening a new contwow session.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_cwose(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_CWOSE,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_set_poows() - Set buffew poows configuwation
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @cfg:	Buffew poows configuwation
 *
 * mandatowy fow DPNI opewation
 * wawning:Awwowed onwy when DPNI is disabwed
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_set_poows(stwuct fsw_mc_io *mc_io,
		   u32 cmd_fwags,
		   u16 token,
		   const stwuct dpni_poows_cfg *cfg)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_set_poows *cmd_pawams;
	int i;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_POOWS,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_poows *)cmd.pawams;
	cmd_pawams->num_dpbp = cfg->num_dpbp;
	cmd_pawams->poow_options = cfg->poow_options;
	fow (i = 0; i < DPNI_MAX_DPBP; i++) {
		cmd_pawams->poow[i].dpbp_id =
			cpu_to_we16(cfg->poows[i].dpbp_id);
		cmd_pawams->poow[i].pwiowity_mask =
			cfg->poows[i].pwiowity_mask;
		cmd_pawams->buffew_size[i] =
			cpu_to_we16(cfg->poows[i].buffew_size);
		cmd_pawams->backup_poow_mask |=
			DPNI_BACKUP_POOW(cfg->poows[i].backup_poow, i);
	}

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_enabwe() - Enabwe the DPNI, awwow sending and weceiving fwames.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:		Token of DPNI object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_enabwe(stwuct fsw_mc_io *mc_io,
		u32 cmd_fwags,
		u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_ENABWE,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_disabwe() - Disabwe the DPNI, stop sending and weceiving fwames.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_disabwe(stwuct fsw_mc_io *mc_io,
		 u32 cmd_fwags,
		 u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_DISABWE,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_is_enabwed() - Check if the DPNI is enabwed.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @en:		Wetuwns '1' if object is enabwed; '0' othewwise
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_is_enabwed(stwuct fsw_mc_io *mc_io,
		    u32 cmd_fwags,
		    u16 token,
		    int *en)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_wsp_is_enabwed *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_IS_ENABWED,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_is_enabwed *)cmd.pawams;
	*en = dpni_get_fiewd(wsp_pawams->enabwed, ENABWE);

	wetuwn 0;
}

/**
 * dpni_weset() - Weset the DPNI, wetuwns the object to initiaw state.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_weset(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_WESET,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_set_iwq_enabwe() - Set ovewaww intewwupt state.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @iwq_index:	The intewwupt index to configuwe
 * @en:		Intewwupt state: - enabwe = 1, disabwe = 0
 *
 * Awwows GPP softwawe to contwow when intewwupts awe genewated.
 * Each intewwupt can have up to 32 causes.  The enabwe/disabwe contwow's the
 * ovewaww intewwupt state. if the intewwupt is disabwed no causes wiww cause
 * an intewwupt.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_set_iwq_enabwe(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			u8 iwq_index,
			u8 en)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_set_iwq_enabwe *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_IWQ_ENABWE,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_iwq_enabwe *)cmd.pawams;
	dpni_set_fiewd(cmd_pawams->enabwe, ENABWE, en);
	cmd_pawams->iwq_index = iwq_index;

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_get_iwq_enabwe() - Get ovewaww intewwupt state
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @iwq_index:	The intewwupt index to configuwe
 * @en:		Wetuwned intewwupt state - enabwe = 1, disabwe = 0
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_iwq_enabwe(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			u8 iwq_index,
			u8 *en)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_get_iwq_enabwe *cmd_pawams;
	stwuct dpni_wsp_get_iwq_enabwe *wsp_pawams;

	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_IWQ_ENABWE,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_get_iwq_enabwe *)cmd.pawams;
	cmd_pawams->iwq_index = iwq_index;

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_iwq_enabwe *)cmd.pawams;
	*en = dpni_get_fiewd(wsp_pawams->enabwed, ENABWE);

	wetuwn 0;
}

/**
 * dpni_set_iwq_mask() - Set intewwupt mask.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @iwq_index:	The intewwupt index to configuwe
 * @mask:	event mask to twiggew intewwupt;
 *			each bit:
 *				0 = ignowe event
 *				1 = considew event fow assewting IWQ
 *
 * Evewy intewwupt can have up to 32 causes and the intewwupt modew suppowts
 * masking/unmasking each cause independentwy
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_set_iwq_mask(stwuct fsw_mc_io *mc_io,
		      u32 cmd_fwags,
		      u16 token,
		      u8 iwq_index,
		      u32 mask)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_set_iwq_mask *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_IWQ_MASK,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_iwq_mask *)cmd.pawams;
	cmd_pawams->mask = cpu_to_we32(mask);
	cmd_pawams->iwq_index = iwq_index;

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_get_iwq_mask() - Get intewwupt mask.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @iwq_index:	The intewwupt index to configuwe
 * @mask:	Wetuwned event mask to twiggew intewwupt
 *
 * Evewy intewwupt can have up to 32 causes and the intewwupt modew suppowts
 * masking/unmasking each cause independentwy
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_iwq_mask(stwuct fsw_mc_io *mc_io,
		      u32 cmd_fwags,
		      u16 token,
		      u8 iwq_index,
		      u32 *mask)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_get_iwq_mask *cmd_pawams;
	stwuct dpni_wsp_get_iwq_mask *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_IWQ_MASK,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_get_iwq_mask *)cmd.pawams;
	cmd_pawams->iwq_index = iwq_index;

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_iwq_mask *)cmd.pawams;
	*mask = we32_to_cpu(wsp_pawams->mask);

	wetuwn 0;
}

/**
 * dpni_get_iwq_status() - Get the cuwwent status of any pending intewwupts.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @iwq_index:	The intewwupt index to configuwe
 * @status:	Wetuwned intewwupts status - one bit pew cause:
 *			0 = no intewwupt pending
 *			1 = intewwupt pending
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_iwq_status(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			u8 iwq_index,
			u32 *status)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_get_iwq_status *cmd_pawams;
	stwuct dpni_wsp_get_iwq_status *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_IWQ_STATUS,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_get_iwq_status *)cmd.pawams;
	cmd_pawams->status = cpu_to_we32(*status);
	cmd_pawams->iwq_index = iwq_index;

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_iwq_status *)cmd.pawams;
	*status = we32_to_cpu(wsp_pawams->status);

	wetuwn 0;
}

/**
 * dpni_cweaw_iwq_status() - Cweaw a pending intewwupt's status
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @iwq_index:	The intewwupt index to configuwe
 * @status:	bits to cweaw (W1C) - one bit pew cause:
 *			0 = don't change
 *			1 = cweaw status bit
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_cweaw_iwq_status(stwuct fsw_mc_io *mc_io,
			  u32 cmd_fwags,
			  u16 token,
			  u8 iwq_index,
			  u32 status)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_cweaw_iwq_status *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_CWEAW_IWQ_STATUS,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_cweaw_iwq_status *)cmd.pawams;
	cmd_pawams->iwq_index = iwq_index;
	cmd_pawams->status = cpu_to_we32(status);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_get_attwibutes() - Wetwieve DPNI attwibutes.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @attw:	Object's attwibutes
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_attwibutes(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			stwuct dpni_attw *attw)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_wsp_get_attw *wsp_pawams;

	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_ATTW,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_attw *)cmd.pawams;
	attw->options = we32_to_cpu(wsp_pawams->options);
	attw->num_queues = wsp_pawams->num_queues;
	attw->num_tcs = wsp_pawams->num_tcs;
	attw->mac_fiwtew_entwies = wsp_pawams->mac_fiwtew_entwies;
	attw->vwan_fiwtew_entwies = wsp_pawams->vwan_fiwtew_entwies;
	attw->qos_entwies = wsp_pawams->qos_entwies;
	attw->fs_entwies = we16_to_cpu(wsp_pawams->fs_entwies);
	attw->qos_key_size = wsp_pawams->qos_key_size;
	attw->fs_key_size = wsp_pawams->fs_key_size;
	attw->wwiop_vewsion = we16_to_cpu(wsp_pawams->wwiop_vewsion);

	wetuwn 0;
}

/**
 * dpni_set_ewwows_behaviow() - Set ewwows behaviow
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @cfg:	Ewwows configuwation
 *
 * this function may be cawwed numewous times with diffewent
 * ewwow masks
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_set_ewwows_behaviow(stwuct fsw_mc_io *mc_io,
			     u32 cmd_fwags,
			     u16 token,
			     stwuct dpni_ewwow_cfg *cfg)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_set_ewwows_behaviow *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_EWWOWS_BEHAVIOW,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_ewwows_behaviow *)cmd.pawams;
	cmd_pawams->ewwows = cpu_to_we32(cfg->ewwows);
	dpni_set_fiewd(cmd_pawams->fwags, EWWOW_ACTION, cfg->ewwow_action);
	dpni_set_fiewd(cmd_pawams->fwags, FWAME_ANN, cfg->set_fwame_annotation);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_get_buffew_wayout() - Wetwieve buffew wayout attwibutes.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @qtype:	Type of queue to wetwieve configuwation fow
 * @wayout:	Wetuwns buffew wayout attwibutes
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_buffew_wayout(stwuct fsw_mc_io *mc_io,
			   u32 cmd_fwags,
			   u16 token,
			   enum dpni_queue_type qtype,
			   stwuct dpni_buffew_wayout *wayout)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_get_buffew_wayout *cmd_pawams;
	stwuct dpni_wsp_get_buffew_wayout *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_BUFFEW_WAYOUT,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_get_buffew_wayout *)cmd.pawams;
	cmd_pawams->qtype = qtype;

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_buffew_wayout *)cmd.pawams;
	wayout->pass_timestamp = dpni_get_fiewd(wsp_pawams->fwags, PASS_TS);
	wayout->pass_pawsew_wesuwt = dpni_get_fiewd(wsp_pawams->fwags, PASS_PW);
	wayout->pass_fwame_status = dpni_get_fiewd(wsp_pawams->fwags, PASS_FS);
	wayout->pwivate_data_size = we16_to_cpu(wsp_pawams->pwivate_data_size);
	wayout->data_awign = we16_to_cpu(wsp_pawams->data_awign);
	wayout->data_head_woom = we16_to_cpu(wsp_pawams->head_woom);
	wayout->data_taiw_woom = we16_to_cpu(wsp_pawams->taiw_woom);

	wetuwn 0;
}

/**
 * dpni_set_buffew_wayout() - Set buffew wayout configuwation.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @qtype:	Type of queue this configuwation appwies to
 * @wayout:	Buffew wayout configuwation
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 *
 * @wawning	Awwowed onwy when DPNI is disabwed
 */
int dpni_set_buffew_wayout(stwuct fsw_mc_io *mc_io,
			   u32 cmd_fwags,
			   u16 token,
			   enum dpni_queue_type qtype,
			   const stwuct dpni_buffew_wayout *wayout)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_set_buffew_wayout *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_BUFFEW_WAYOUT,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_buffew_wayout *)cmd.pawams;
	cmd_pawams->qtype = qtype;
	cmd_pawams->options = cpu_to_we16(wayout->options);
	dpni_set_fiewd(cmd_pawams->fwags, PASS_TS, wayout->pass_timestamp);
	dpni_set_fiewd(cmd_pawams->fwags, PASS_PW, wayout->pass_pawsew_wesuwt);
	dpni_set_fiewd(cmd_pawams->fwags, PASS_FS, wayout->pass_fwame_status);
	cmd_pawams->pwivate_data_size = cpu_to_we16(wayout->pwivate_data_size);
	cmd_pawams->data_awign = cpu_to_we16(wayout->data_awign);
	cmd_pawams->head_woom = cpu_to_we16(wayout->data_head_woom);
	cmd_pawams->taiw_woom = cpu_to_we16(wayout->data_taiw_woom);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_set_offwoad() - Set DPNI offwoad configuwation.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @type:	Type of DPNI offwoad
 * @config:	Offwoad configuwation.
 *		Fow checksum offwoads, non-zewo vawue enabwes the offwoad
 *
 * Wetuwn:     '0' on Success; Ewwow code othewwise.
 *
 * @wawning    Awwowed onwy when DPNI is disabwed
 */

int dpni_set_offwoad(stwuct fsw_mc_io *mc_io,
		     u32 cmd_fwags,
		     u16 token,
		     enum dpni_offwoad type,
		     u32 config)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_set_offwoad *cmd_pawams;

	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_OFFWOAD,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_offwoad *)cmd.pawams;
	cmd_pawams->dpni_offwoad = type;
	cmd_pawams->config = cpu_to_we32(config);

	wetuwn mc_send_command(mc_io, &cmd);
}

int dpni_get_offwoad(stwuct fsw_mc_io *mc_io,
		     u32 cmd_fwags,
		     u16 token,
		     enum dpni_offwoad type,
		     u32 *config)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_get_offwoad *cmd_pawams;
	stwuct dpni_wsp_get_offwoad *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_OFFWOAD,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_get_offwoad *)cmd.pawams;
	cmd_pawams->dpni_offwoad = type;

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_offwoad *)cmd.pawams;
	*config = we32_to_cpu(wsp_pawams->config);

	wetuwn 0;
}

/**
 * dpni_get_qdid() - Get the Queuing Destination ID (QDID) that shouwd be used
 *			fow enqueue opewations
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @qtype:	Type of queue to weceive QDID fow
 * @qdid:	Wetuwned viwtuaw QDID vawue that shouwd be used as an awgument
 *			in aww enqueue opewations
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_qdid(stwuct fsw_mc_io *mc_io,
		  u32 cmd_fwags,
		  u16 token,
		  enum dpni_queue_type qtype,
		  u16 *qdid)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_get_qdid *cmd_pawams;
	stwuct dpni_wsp_get_qdid *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_QDID,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_get_qdid *)cmd.pawams;
	cmd_pawams->qtype = qtype;

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_qdid *)cmd.pawams;
	*qdid = we16_to_cpu(wsp_pawams->qdid);

	wetuwn 0;
}

/**
 * dpni_get_tx_data_offset() - Get the Tx data offset (fwom stawt of buffew)
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @data_offset: Tx data offset (fwom stawt of buffew)
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_tx_data_offset(stwuct fsw_mc_io *mc_io,
			    u32 cmd_fwags,
			    u16 token,
			    u16 *data_offset)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_wsp_get_tx_data_offset *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_TX_DATA_OFFSET,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_tx_data_offset *)cmd.pawams;
	*data_offset = we16_to_cpu(wsp_pawams->data_offset);

	wetuwn 0;
}

/**
 * dpni_set_wink_cfg() - set the wink configuwation.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @cfg:	Wink configuwation
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_set_wink_cfg(stwuct fsw_mc_io *mc_io,
		      u32 cmd_fwags,
		      u16 token,
		      const stwuct dpni_wink_cfg *cfg)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_wink_cfg *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_WINK_CFG,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_wink_cfg *)cmd.pawams;
	cmd_pawams->wate = cpu_to_we32(cfg->wate);
	cmd_pawams->options = cpu_to_we64(cfg->options);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_get_wink_cfg() - wetuwn the wink configuwation
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @cfg:	Wink configuwation fwom dpni object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_wink_cfg(stwuct fsw_mc_io *mc_io,
		      u32 cmd_fwags,
		      u16 token,
		      stwuct dpni_wink_cfg *cfg)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_wink_cfg *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_WINK_CFG,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_cmd_wink_cfg *)cmd.pawams;
	cfg->wate = we32_to_cpu(wsp_pawams->wate);
	cfg->options = we64_to_cpu(wsp_pawams->options);

	wetuwn eww;
}

/**
 * dpni_get_wink_state() - Wetuwn the wink state (eithew up ow down)
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @state:	Wetuwned wink state;
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_wink_state(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			stwuct dpni_wink_state *state)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_wsp_get_wink_state *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_WINK_STATE,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_wink_state *)cmd.pawams;
	state->up = dpni_get_fiewd(wsp_pawams->fwags, WINK_STATE);
	state->wate = we32_to_cpu(wsp_pawams->wate);
	state->options = we64_to_cpu(wsp_pawams->options);

	wetuwn 0;
}

/**
 * dpni_set_max_fwame_wength() - Set the maximum weceived fwame wength.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @max_fwame_wength:	Maximum weceived fwame wength (in
 *				bytes); fwame is discawded if its
 *				wength exceeds this vawue
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_set_max_fwame_wength(stwuct fsw_mc_io *mc_io,
			      u32 cmd_fwags,
			      u16 token,
			      u16 max_fwame_wength)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_set_max_fwame_wength *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_MAX_FWAME_WENGTH,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_max_fwame_wength *)cmd.pawams;
	cmd_pawams->max_fwame_wength = cpu_to_we16(max_fwame_wength);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_get_max_fwame_wength() - Get the maximum weceived fwame wength.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @max_fwame_wength:	Maximum weceived fwame wength (in
 *				bytes); fwame is discawded if its
 *				wength exceeds this vawue
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_max_fwame_wength(stwuct fsw_mc_io *mc_io,
			      u32 cmd_fwags,
			      u16 token,
			      u16 *max_fwame_wength)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_wsp_get_max_fwame_wength *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_MAX_FWAME_WENGTH,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_max_fwame_wength *)cmd.pawams;
	*max_fwame_wength = we16_to_cpu(wsp_pawams->max_fwame_wength);

	wetuwn 0;
}

/**
 * dpni_set_muwticast_pwomisc() - Enabwe/disabwe muwticast pwomiscuous mode
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @en:		Set to '1' to enabwe; '0' to disabwe
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_set_muwticast_pwomisc(stwuct fsw_mc_io *mc_io,
			       u32 cmd_fwags,
			       u16 token,
			       int en)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_set_muwticast_pwomisc *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_MCAST_PWOMISC,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_muwticast_pwomisc *)cmd.pawams;
	dpni_set_fiewd(cmd_pawams->enabwe, ENABWE, en);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_get_muwticast_pwomisc() - Get muwticast pwomiscuous mode
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @en:		Wetuwns '1' if enabwed; '0' othewwise
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_muwticast_pwomisc(stwuct fsw_mc_io *mc_io,
			       u32 cmd_fwags,
			       u16 token,
			       int *en)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_wsp_get_muwticast_pwomisc *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_MCAST_PWOMISC,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_muwticast_pwomisc *)cmd.pawams;
	*en = dpni_get_fiewd(wsp_pawams->enabwed, ENABWE);

	wetuwn 0;
}

/**
 * dpni_set_unicast_pwomisc() - Enabwe/disabwe unicast pwomiscuous mode
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @en:		Set to '1' to enabwe; '0' to disabwe
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_set_unicast_pwomisc(stwuct fsw_mc_io *mc_io,
			     u32 cmd_fwags,
			     u16 token,
			     int en)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_set_unicast_pwomisc *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_UNICAST_PWOMISC,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_unicast_pwomisc *)cmd.pawams;
	dpni_set_fiewd(cmd_pawams->enabwe, ENABWE, en);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_get_unicast_pwomisc() - Get unicast pwomiscuous mode
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @en:		Wetuwns '1' if enabwed; '0' othewwise
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_unicast_pwomisc(stwuct fsw_mc_io *mc_io,
			     u32 cmd_fwags,
			     u16 token,
			     int *en)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_wsp_get_unicast_pwomisc *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_UNICAST_PWOMISC,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_unicast_pwomisc *)cmd.pawams;
	*en = dpni_get_fiewd(wsp_pawams->enabwed, ENABWE);

	wetuwn 0;
}

/**
 * dpni_set_pwimawy_mac_addw() - Set the pwimawy MAC addwess
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @mac_addw:	MAC addwess to set as pwimawy addwess
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_set_pwimawy_mac_addw(stwuct fsw_mc_io *mc_io,
			      u32 cmd_fwags,
			      u16 token,
			      const u8 mac_addw[6])
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_set_pwimawy_mac_addw *cmd_pawams;
	int i;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_PWIM_MAC,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_pwimawy_mac_addw *)cmd.pawams;
	fow (i = 0; i < 6; i++)
		cmd_pawams->mac_addw[i] = mac_addw[5 - i];

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_get_pwimawy_mac_addw() - Get the pwimawy MAC addwess
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @mac_addw:	Wetuwned MAC addwess
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_pwimawy_mac_addw(stwuct fsw_mc_io *mc_io,
			      u32 cmd_fwags,
			      u16 token,
			      u8 mac_addw[6])
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_wsp_get_pwimawy_mac_addw *wsp_pawams;
	int i, eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_PWIM_MAC,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_pwimawy_mac_addw *)cmd.pawams;
	fow (i = 0; i < 6; i++)
		mac_addw[5 - i] = wsp_pawams->mac_addw[i];

	wetuwn 0;
}

/**
 * dpni_get_powt_mac_addw() - Wetwieve MAC addwess associated to the physicaw
 *			powt the DPNI is attached to
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @mac_addw:	MAC addwess of the physicaw powt, if any, othewwise 0
 *
 * The pwimawy MAC addwess is not cweawed by this opewation.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_powt_mac_addw(stwuct fsw_mc_io *mc_io,
			   u32 cmd_fwags,
			   u16 token,
			   u8 mac_addw[6])
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_wsp_get_powt_mac_addw *wsp_pawams;
	int i, eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_POWT_MAC_ADDW,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_powt_mac_addw *)cmd.pawams;
	fow (i = 0; i < 6; i++)
		mac_addw[5 - i] = wsp_pawams->mac_addw[i];

	wetuwn 0;
}

/**
 * dpni_enabwe_vwan_fiwtew() - Enabwe/disabwe VWAN fiwtewing mode
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @en:		Set to '1' to enabwe; '0' to disabwe
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_enabwe_vwan_fiwtew(stwuct fsw_mc_io *mc_io,
			    u32 cmd_fwags,
			    u16 token,
			    u32 en)
{
	stwuct dpni_cmd_enabwe_vwan_fiwtew *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_ENABWE_VWAN_FIWTEW,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_enabwe_vwan_fiwtew *)cmd.pawams;
	dpni_set_fiewd(cmd_pawams->en, ENABWE, en);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_add_vwan_id() - Add VWAN ID fiwtew
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @vwan_id:	VWAN ID to add
 * @fwags:   0 - tc_id and fwow_id wiww be ignowed.
 * Pkt with this vwan_id wiww be passed to the next
 * cwassification stages
 * DPNI_VWAN_SET_QUEUE_ACTION
 * Pkt with this vwan_id wiww be fowwawd diwectwy to
 * queue defined by the tc_id and fwow_id
 *
 * @tc_id: Twaffic cwass sewection (0-7)
 * @fwow_id: Sewects the specific queue out of the set awwocated fow the
 *           same as tc_id. Vawue must be in wange 0 to NUM_QUEUES - 1
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_add_vwan_id(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
		     u16 vwan_id, u8 fwags, u8 tc_id, u8 fwow_id)
{
	stwuct dpni_cmd_vwan_id *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_ADD_VWAN_ID,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_vwan_id *)cmd.pawams;
	cmd_pawams->fwags = fwags;
	cmd_pawams->tc_id = tc_id;
	cmd_pawams->fwow_id =  fwow_id;
	cmd_pawams->vwan_id = cpu_to_we16(vwan_id);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_wemove_vwan_id() - Wemove VWAN ID fiwtew
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @vwan_id:	VWAN ID to wemove
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_wemove_vwan_id(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			u16 vwan_id)
{
	stwuct dpni_cmd_vwan_id *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_WEMOVE_VWAN_ID,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_vwan_id *)cmd.pawams;
	cmd_pawams->vwan_id = cpu_to_we16(vwan_id);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_add_mac_addw() - Add MAC addwess fiwtew
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @mac_addw:	MAC addwess to add
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_add_mac_addw(stwuct fsw_mc_io *mc_io,
		      u32 cmd_fwags,
		      u16 token,
		      const u8 mac_addw[6])
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_add_mac_addw *cmd_pawams;
	int i;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_ADD_MAC_ADDW,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_add_mac_addw *)cmd.pawams;
	fow (i = 0; i < 6; i++)
		cmd_pawams->mac_addw[i] = mac_addw[5 - i];

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_wemove_mac_addw() - Wemove MAC addwess fiwtew
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @mac_addw:	MAC addwess to wemove
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_wemove_mac_addw(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 token,
			 const u8 mac_addw[6])
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_wemove_mac_addw *cmd_pawams;
	int i;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_WEMOVE_MAC_ADDW,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_wemove_mac_addw *)cmd.pawams;
	fow (i = 0; i < 6; i++)
		cmd_pawams->mac_addw[i] = mac_addw[5 - i];

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_cweaw_mac_fiwtews() - Cweaw aww unicast and/ow muwticast MAC fiwtews
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @unicast:	Set to '1' to cweaw unicast addwesses
 * @muwticast:	Set to '1' to cweaw muwticast addwesses
 *
 * The pwimawy MAC addwess is not cweawed by this opewation.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_cweaw_mac_fiwtews(stwuct fsw_mc_io *mc_io,
			   u32 cmd_fwags,
			   u16 token,
			   int unicast,
			   int muwticast)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_cweaw_mac_fiwtews *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_CWW_MAC_FIWTEWS,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_cweaw_mac_fiwtews *)cmd.pawams;
	dpni_set_fiewd(cmd_pawams->fwags, UNICAST_FIWTEWS, unicast);
	dpni_set_fiewd(cmd_pawams->fwags, MUWTICAST_FIWTEWS, muwticast);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_set_wx_tc_dist() - Set Wx twaffic cwass distwibution configuwation
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @tc_id:	Twaffic cwass sewection (0-7)
 * @cfg:	Twaffic cwass distwibution configuwation
 *
 * wawning: if 'dist_mode != DPNI_DIST_MODE_NONE', caww dpni_pwepawe_key_cfg()
 *			fiwst to pwepawe the key_cfg_iova pawametew
 *
 * Wetuwn:	'0' on Success; ewwow code othewwise.
 */
int dpni_set_wx_tc_dist(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			u8 tc_id,
			const stwuct dpni_wx_tc_dist_cfg *cfg)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_set_wx_tc_dist *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_WX_TC_DIST,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_wx_tc_dist *)cmd.pawams;
	cmd_pawams->dist_size = cpu_to_we16(cfg->dist_size);
	cmd_pawams->tc_id = tc_id;
	dpni_set_fiewd(cmd_pawams->fwags, DIST_MODE, cfg->dist_mode);
	dpni_set_fiewd(cmd_pawams->fwags, MISS_ACTION, cfg->fs_cfg.miss_action);
	cmd_pawams->defauwt_fwow_id = cpu_to_we16(cfg->fs_cfg.defauwt_fwow_id);
	cmd_pawams->key_cfg_iova = cpu_to_we64(cfg->key_cfg_iova);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_set_congestion_notification() - Set twaffic cwass congestion
 *					notification configuwation
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @qtype:	Type of queue - Wx, Tx and Tx confiwm types awe suppowted
 * @tc_id:	Twaffic cwass sewection (0-7)
 * @cfg:	Congestion notification configuwation
 *
 * Wetuwn:	'0' on Success; ewwow code othewwise.
 */
int dpni_set_congestion_notification(
			stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			enum dpni_queue_type qtype,
			u8 tc_id,
			const stwuct dpni_congestion_notification_cfg *cfg)
{
	stwuct dpni_cmd_set_congestion_notification *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew =
		mc_encode_cmd_headew(DPNI_CMDID_SET_CONGESTION_NOTIFICATION,
				     cmd_fwags,
				     token);
	cmd_pawams = (stwuct dpni_cmd_set_congestion_notification *)cmd.pawams;
	cmd_pawams->qtype = qtype;
	cmd_pawams->tc = tc_id;
	cmd_pawams->dest_id = cpu_to_we32(cfg->dest_cfg.dest_id);
	cmd_pawams->notification_mode = cpu_to_we16(cfg->notification_mode);
	cmd_pawams->dest_pwiowity = cfg->dest_cfg.pwiowity;
	dpni_set_fiewd(cmd_pawams->type_units, DEST_TYPE,
		       cfg->dest_cfg.dest_type);
	dpni_set_fiewd(cmd_pawams->type_units, CONG_UNITS, cfg->units);
	cmd_pawams->message_iova = cpu_to_we64(cfg->message_iova);
	cmd_pawams->message_ctx = cpu_to_we64(cfg->message_ctx);
	cmd_pawams->thweshowd_entwy = cpu_to_we32(cfg->thweshowd_entwy);
	cmd_pawams->thweshowd_exit = cpu_to_we32(cfg->thweshowd_exit);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_set_queue() - Set queue pawametews
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @qtype:	Type of queue - aww queue types awe suppowted, awthough
 *		the command is ignowed fow Tx
 * @tc:		Twaffic cwass, in wange 0 to NUM_TCS - 1
 * @index:	Sewects the specific queue out of the set awwocated fow the
 *		same TC. Vawue must be in wange 0 to NUM_QUEUES - 1
 * @options:	A combination of DPNI_QUEUE_OPT_ vawues that contwow what
 *		configuwation options awe set on the queue
 * @queue:	Queue stwuctuwe
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_set_queue(stwuct fsw_mc_io *mc_io,
		   u32 cmd_fwags,
		   u16 token,
		   enum dpni_queue_type qtype,
		   u8 tc,
		   u8 index,
		   u8 options,
		   const stwuct dpni_queue *queue)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_set_queue *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_QUEUE,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_queue *)cmd.pawams;
	cmd_pawams->qtype = qtype;
	cmd_pawams->tc = tc;
	cmd_pawams->index = index;
	cmd_pawams->options = options;
	cmd_pawams->dest_id = cpu_to_we32(queue->destination.id);
	cmd_pawams->dest_pwio = queue->destination.pwiowity;
	dpni_set_fiewd(cmd_pawams->fwags, DEST_TYPE, queue->destination.type);
	dpni_set_fiewd(cmd_pawams->fwags, STASH_CTWW, queue->fwc.stash_contwow);
	dpni_set_fiewd(cmd_pawams->fwags, HOWD_ACTIVE,
		       queue->destination.howd_active);
	cmd_pawams->fwc = cpu_to_we64(queue->fwc.vawue);
	cmd_pawams->usew_context = cpu_to_we64(queue->usew_context);

	/* send command to mc */
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_get_queue() - Get queue pawametews
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @qtype:	Type of queue - aww queue types awe suppowted
 * @tc:		Twaffic cwass, in wange 0 to NUM_TCS - 1
 * @index:	Sewects the specific queue out of the set awwocated fow the
 *		same TC. Vawue must be in wange 0 to NUM_QUEUES - 1
 * @queue:	Queue configuwation stwuctuwe
 * @qid:	Queue identification
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_queue(stwuct fsw_mc_io *mc_io,
		   u32 cmd_fwags,
		   u16 token,
		   enum dpni_queue_type qtype,
		   u8 tc,
		   u8 index,
		   stwuct dpni_queue *queue,
		   stwuct dpni_queue_id *qid)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_get_queue *cmd_pawams;
	stwuct dpni_wsp_get_queue *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_QUEUE,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_get_queue *)cmd.pawams;
	cmd_pawams->qtype = qtype;
	cmd_pawams->tc = tc;
	cmd_pawams->index = index;

	/* send command to mc */
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_queue *)cmd.pawams;
	queue->destination.id = we32_to_cpu(wsp_pawams->dest_id);
	queue->destination.pwiowity = wsp_pawams->dest_pwio;
	queue->destination.type = dpni_get_fiewd(wsp_pawams->fwags,
						 DEST_TYPE);
	queue->fwc.stash_contwow = dpni_get_fiewd(wsp_pawams->fwags,
						  STASH_CTWW);
	queue->destination.howd_active = dpni_get_fiewd(wsp_pawams->fwags,
							HOWD_ACTIVE);
	queue->fwc.vawue = we64_to_cpu(wsp_pawams->fwc);
	queue->usew_context = we64_to_cpu(wsp_pawams->usew_context);
	qid->fqid = we32_to_cpu(wsp_pawams->fqid);
	qid->qdbin = we16_to_cpu(wsp_pawams->qdbin);

	wetuwn 0;
}

/**
 * dpni_get_statistics() - Get DPNI statistics
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @page:	Sewects the statistics page to wetwieve, see
 *		DPNI_GET_STATISTICS output. Pages awe numbewed 0 to 6.
 * @stat:	Stwuctuwe containing the statistics
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_statistics(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			u8 page,
			union dpni_statistics *stat)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_get_statistics *cmd_pawams;
	stwuct dpni_wsp_get_statistics *wsp_pawams;
	int i, eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_STATISTICS,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_get_statistics *)cmd.pawams;
	cmd_pawams->page_numbew = page;

	/* send command to mc */
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_statistics *)cmd.pawams;
	fow (i = 0; i < DPNI_STATISTICS_CNT; i++)
		stat->waw.countew[i] = we64_to_cpu(wsp_pawams->countew[i]);

	wetuwn 0;
}

/**
 * dpni_set_taiwdwop() - Set taiwdwop pew queue ow TC
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @cg_point:	Congestion point
 * @qtype:	Queue type on which the taiwdwop is configuwed.
 *		Onwy Wx queues awe suppowted fow now
 * @tc:		Twaffic cwass to appwy this taiwdwop to
 * @index:	Index of the queue if the DPNI suppowts muwtipwe queues fow
 *		twaffic distwibution. Ignowed if CONGESTION_POINT is not 0.
 * @taiwdwop:	Taiwdwop stwuctuwe
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_set_taiwdwop(stwuct fsw_mc_io *mc_io,
		      u32 cmd_fwags,
		      u16 token,
		      enum dpni_congestion_point cg_point,
		      enum dpni_queue_type qtype,
		      u8 tc,
		      u8 index,
		      stwuct dpni_taiwdwop *taiwdwop)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_set_taiwdwop *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_TAIWDWOP,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_taiwdwop *)cmd.pawams;
	cmd_pawams->congestion_point = cg_point;
	cmd_pawams->qtype = qtype;
	cmd_pawams->tc = tc;
	cmd_pawams->index = index;
	dpni_set_fiewd(cmd_pawams->enabwe, ENABWE, taiwdwop->enabwe);
	cmd_pawams->units = taiwdwop->units;
	cmd_pawams->thweshowd = cpu_to_we32(taiwdwop->thweshowd);

	/* send command to mc */
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_get_taiwdwop() - Get taiwdwop infowmation
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @cg_point:	Congestion point
 * @qtype:	Queue type on which the taiwdwop is configuwed.
 *		Onwy Wx queues awe suppowted fow now
 * @tc:		Twaffic cwass to appwy this taiwdwop to
 * @index:	Index of the queue if the DPNI suppowts muwtipwe queues fow
 *		twaffic distwibution. Ignowed if CONGESTION_POINT is not 0.
 * @taiwdwop:	Taiwdwop stwuctuwe
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_taiwdwop(stwuct fsw_mc_io *mc_io,
		      u32 cmd_fwags,
		      u16 token,
		      enum dpni_congestion_point cg_point,
		      enum dpni_queue_type qtype,
		      u8 tc,
		      u8 index,
		      stwuct dpni_taiwdwop *taiwdwop)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpni_cmd_get_taiwdwop *cmd_pawams;
	stwuct dpni_wsp_get_taiwdwop *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_TAIWDWOP,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_get_taiwdwop *)cmd.pawams;
	cmd_pawams->congestion_point = cg_point;
	cmd_pawams->qtype = qtype;
	cmd_pawams->tc = tc;
	cmd_pawams->index = index;

	/* send command to mc */
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpni_wsp_get_taiwdwop *)cmd.pawams;
	taiwdwop->enabwe = dpni_get_fiewd(wsp_pawams->enabwe, ENABWE);
	taiwdwop->units = wsp_pawams->units;
	taiwdwop->thweshowd = we32_to_cpu(wsp_pawams->thweshowd);

	wetuwn 0;
}

/**
 * dpni_get_api_vewsion() - Get Data Path Netwowk Intewface API vewsion
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @majow_vew:	Majow vewsion of data path netwowk intewface API
 * @minow_vew:	Minow vewsion of data path netwowk intewface API
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_get_api_vewsion(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 *majow_vew,
			 u16 *minow_vew)
{
	stwuct dpni_wsp_get_api_vewsion *wsp_pawams;
	stwuct fsw_mc_command cmd = { 0 };
	int eww;

	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_API_VEWSION,
					  cmd_fwags, 0);

	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	wsp_pawams = (stwuct dpni_wsp_get_api_vewsion *)cmd.pawams;
	*majow_vew = we16_to_cpu(wsp_pawams->majow);
	*minow_vew = we16_to_cpu(wsp_pawams->minow);

	wetuwn 0;
}

/**
 * dpni_set_wx_fs_dist() - Set Wx fwow steewing distwibution
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @cfg: Distwibution configuwation
 *
 * If the FS is awweady enabwed with a pwevious caww the cwassification
 * key wiww be changed but aww the tabwe wuwes awe kept. If the
 * existing wuwes do not match the key the wesuwts wiww not be
 * pwedictabwe. It is the usew wesponsibiwity to keep key integwity.
 * If cfg.enabwe is set to 1 the command wiww cweate a fwow steewing tabwe
 * and wiww cwassify packets accowding to this tabwe. The packets that
 * miss aww the tabwe wuwes wiww be cwassified accowding to settings
 * made in dpni_set_wx_hash_dist()
 * If cfg.enabwe is set to 0 the command wiww cweaw fwow steewing tabwe.
 * The packets wiww be cwassified accowding to settings made in
 * dpni_set_wx_hash_dist()
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_set_wx_fs_dist(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			const stwuct dpni_wx_dist_cfg *cfg)
{
	stwuct dpni_cmd_set_wx_fs_dist *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_WX_FS_DIST,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_wx_fs_dist *)cmd.pawams;
	cmd_pawams->dist_size = cpu_to_we16(cfg->dist_size);
	dpni_set_fiewd(cmd_pawams->enabwe, WX_FS_DIST_ENABWE, cfg->enabwe);
	cmd_pawams->tc = cfg->tc;
	cmd_pawams->miss_fwow_id = cpu_to_we16(cfg->fs_miss_fwow_id);
	cmd_pawams->key_cfg_iova = cpu_to_we64(cfg->key_cfg_iova);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_set_wx_hash_dist() - Set Wx hash distwibution
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @cfg: Distwibution configuwation
 * If cfg.enabwe is set to 1 the packets wiww be cwassified using a hash
 * function based on the key weceived in cfg.key_cfg_iova pawametew.
 * If cfg.enabwe is set to 0 the packets wiww be sent to the defauwt queue
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_set_wx_hash_dist(stwuct fsw_mc_io *mc_io,
			  u32 cmd_fwags,
			  u16 token,
			  const stwuct dpni_wx_dist_cfg *cfg)
{
	stwuct dpni_cmd_set_wx_hash_dist *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_WX_HASH_DIST,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_wx_hash_dist *)cmd.pawams;
	cmd_pawams->dist_size = cpu_to_we16(cfg->dist_size);
	dpni_set_fiewd(cmd_pawams->enabwe, WX_HASH_DIST_ENABWE, cfg->enabwe);
	cmd_pawams->tc = cfg->tc;
	cmd_pawams->key_cfg_iova = cpu_to_we64(cfg->key_cfg_iova);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_add_fs_entwy() - Add Fwow Steewing entwy fow a specific twaffic cwass
 *			(to sewect a fwow ID)
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @tc_id:	Twaffic cwass sewection (0-7)
 * @index:	Wocation in the FS tabwe whewe to insewt the entwy.
 *		Onwy wewevant if MASKING is enabwed fow FS
 *		cwassification on this DPNI, it is ignowed fow exact match.
 * @cfg:	Fwow steewing wuwe to add
 * @action:	Action to be taken as wesuwt of a cwassification hit
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_add_fs_entwy(stwuct fsw_mc_io *mc_io,
		      u32 cmd_fwags,
		      u16 token,
		      u8 tc_id,
		      u16 index,
		      const stwuct dpni_wuwe_cfg *cfg,
		      const stwuct dpni_fs_action_cfg *action)
{
	stwuct dpni_cmd_add_fs_entwy *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_ADD_FS_ENT,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_add_fs_entwy *)cmd.pawams;
	cmd_pawams->tc_id = tc_id;
	cmd_pawams->key_size = cfg->key_size;
	cmd_pawams->index = cpu_to_we16(index);
	cmd_pawams->key_iova = cpu_to_we64(cfg->key_iova);
	cmd_pawams->mask_iova = cpu_to_we64(cfg->mask_iova);
	cmd_pawams->options = cpu_to_we16(action->options);
	cmd_pawams->fwow_id = cpu_to_we16(action->fwow_id);
	cmd_pawams->fwc = cpu_to_we64(action->fwc);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_wemove_fs_entwy() - Wemove Fwow Steewing entwy fwom a specific
 *			    twaffic cwass
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @tc_id:	Twaffic cwass sewection (0-7)
 * @cfg:	Fwow steewing wuwe to wemove
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_wemove_fs_entwy(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 token,
			 u8 tc_id,
			 const stwuct dpni_wuwe_cfg *cfg)
{
	stwuct dpni_cmd_wemove_fs_entwy *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_WEMOVE_FS_ENT,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_wemove_fs_entwy *)cmd.pawams;
	cmd_pawams->tc_id = tc_id;
	cmd_pawams->key_size = cfg->key_size;
	cmd_pawams->key_iova = cpu_to_we64(cfg->key_iova);
	cmd_pawams->mask_iova = cpu_to_we64(cfg->mask_iova);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_set_qos_tabwe() - Set QoS mapping tabwe
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @cfg:	QoS tabwe configuwation
 *
 * This function and aww QoS-wewated functions wequiwe that
 *'max_tcs > 1' was set at DPNI cweation.
 *
 * wawning: Befowe cawwing this function, caww dpkg_pwepawe_key_cfg() to
 *			pwepawe the key_cfg_iova pawametew
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_set_qos_tabwe(stwuct fsw_mc_io *mc_io,
		       u32 cmd_fwags,
		       u16 token,
		       const stwuct dpni_qos_tbw_cfg *cfg)
{
	stwuct dpni_cmd_set_qos_tabwe *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_QOS_TBW,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_qos_tabwe *)cmd.pawams;
	cmd_pawams->defauwt_tc = cfg->defauwt_tc;
	cmd_pawams->key_cfg_iova = cpu_to_we64(cfg->key_cfg_iova);
	dpni_set_fiewd(cmd_pawams->discawd_on_miss, DISCAWD_ON_MISS,
		       cfg->discawd_on_miss);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_add_qos_entwy() - Add QoS mapping entwy (to sewect a twaffic cwass)
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @cfg:	QoS wuwe to add
 * @tc_id:	Twaffic cwass sewection (0-7)
 * @index:	Wocation in the QoS tabwe whewe to insewt the entwy.
 *		Onwy wewevant if MASKING is enabwed fow QoS cwassification on
 *		this DPNI, it is ignowed fow exact match.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_add_qos_entwy(stwuct fsw_mc_io *mc_io,
		       u32 cmd_fwags,
		       u16 token,
		       const stwuct dpni_wuwe_cfg *cfg,
		       u8 tc_id,
		       u16 index)
{
	stwuct dpni_cmd_add_qos_entwy *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_ADD_QOS_ENT,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_add_qos_entwy *)cmd.pawams;
	cmd_pawams->tc_id = tc_id;
	cmd_pawams->key_size = cfg->key_size;
	cmd_pawams->index = cpu_to_we16(index);
	cmd_pawams->key_iova = cpu_to_we64(cfg->key_iova);
	cmd_pawams->mask_iova = cpu_to_we64(cfg->mask_iova);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_wemove_qos_entwy() - Wemove QoS mapping entwy
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @cfg:	QoS wuwe to wemove
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_wemove_qos_entwy(stwuct fsw_mc_io *mc_io,
			  u32 cmd_fwags,
			  u16 token,
			  const stwuct dpni_wuwe_cfg *cfg)
{
	stwuct dpni_cmd_wemove_qos_entwy *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_WEMOVE_QOS_ENT,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_wemove_qos_entwy *)cmd.pawams;
	cmd_pawams->key_size = cfg->key_size;
	cmd_pawams->key_iova = cpu_to_we64(cfg->key_iova);
	cmd_pawams->mask_iova = cpu_to_we64(cfg->mask_iova);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_cweaw_qos_tabwe() - Cweaw aww QoS mapping entwies
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 *
 * Fowwowing this function caww, aww fwames awe diwected to
 * the defauwt twaffic cwass (0)
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_cweaw_qos_tabwe(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_CWW_QOS_TBW,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_set_tx_shaping() - Set the twansmit shaping
 * @mc_io:		Pointew to MC powtaw's I/O object
 * @cmd_fwags:		Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:		Token of DPNI object
 * @tx_cw_shapew:	TX committed wate shaping configuwation
 * @tx_ew_shapew:	TX excess wate shaping configuwation
 * @coupwed:		Committed and excess wate shapews awe coupwed
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpni_set_tx_shaping(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			const stwuct dpni_tx_shaping_cfg *tx_cw_shapew,
			const stwuct dpni_tx_shaping_cfg *tx_ew_shapew,
			int coupwed)
{
	stwuct dpni_cmd_set_tx_shaping *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_TX_SHAPING,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpni_cmd_set_tx_shaping *)cmd.pawams;
	cmd_pawams->tx_cw_max_buwst_size = cpu_to_we16(tx_cw_shapew->max_buwst_size);
	cmd_pawams->tx_ew_max_buwst_size = cpu_to_we16(tx_ew_shapew->max_buwst_size);
	cmd_pawams->tx_cw_wate_wimit = cpu_to_we32(tx_cw_shapew->wate_wimit);
	cmd_pawams->tx_ew_wate_wimit = cpu_to_we32(tx_ew_shapew->wate_wimit);
	dpni_set_fiewd(cmd_pawams->coupwed, COUPWED, coupwed);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpni_get_singwe_step_cfg() - wetuwn cuwwent configuwation fow
 *                              singwe step PTP
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @ptp_cfg:	ptp singwe step configuwation
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 *
 */
int dpni_get_singwe_step_cfg(stwuct fsw_mc_io *mc_io,
			     u32 cmd_fwags,
			     u16 token,
			     stwuct dpni_singwe_step_cfg *ptp_cfg)
{
	stwuct dpni_wsp_singwe_step_cfg *wsp_pawams;
	stwuct fsw_mc_command cmd = { 0 };
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_GET_SINGWE_STEP_CFG,
					  cmd_fwags, token);
	/* send command to mc*/
	eww =  mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wead command wesponse */
	wsp_pawams = (stwuct dpni_wsp_singwe_step_cfg *)cmd.pawams;
	ptp_cfg->offset = we16_to_cpu(wsp_pawams->offset);
	ptp_cfg->en = dpni_get_fiewd(we16_to_cpu(wsp_pawams->fwags),
				     PTP_ENABWE) ? 1 : 0;
	ptp_cfg->ch_update = dpni_get_fiewd(we16_to_cpu(wsp_pawams->fwags),
					    PTP_CH_UPDATE) ? 1 : 0;
	ptp_cfg->peew_deway = we32_to_cpu(wsp_pawams->peew_deway);
	ptp_cfg->ptp_onestep_weg_base =
				  we32_to_cpu(wsp_pawams->ptp_onestep_weg_base);

	wetuwn eww;
}

/**
 * dpni_set_singwe_step_cfg() - enabwe/disabwe and configuwe singwe step PTP
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPNI object
 * @ptp_cfg:	ptp singwe step configuwation
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 *
 * The function has effect onwy when dpni object is connected to a dpmac
 * object. If the dpni is not connected to a dpmac the configuwation wiww
 * be stowed inside and appwied when connection is made.
 */
int dpni_set_singwe_step_cfg(stwuct fsw_mc_io *mc_io,
			     u32 cmd_fwags,
			     u16 token,
			     stwuct dpni_singwe_step_cfg *ptp_cfg)
{
	stwuct dpni_cmd_singwe_step_cfg *cmd_pawams;
	stwuct fsw_mc_command cmd = { 0 };
	u16 fwags;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPNI_CMDID_SET_SINGWE_STEP_CFG,
					  cmd_fwags, token);
	cmd_pawams = (stwuct dpni_cmd_singwe_step_cfg *)cmd.pawams;
	cmd_pawams->offset = cpu_to_we16(ptp_cfg->offset);
	cmd_pawams->peew_deway = cpu_to_we32(ptp_cfg->peew_deway);

	fwags = we16_to_cpu(cmd_pawams->fwags);
	dpni_set_fiewd(fwags, PTP_ENABWE, !!ptp_cfg->en);
	dpni_set_fiewd(fwags, PTP_CH_UPDATE, !!ptp_cfg->ch_update);
	cmd_pawams->fwags = cpu_to_we16(fwags);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
