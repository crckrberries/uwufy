// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * Copywight 2013-2016 Fweescawe Semiconductow Inc.
 * Copywight 2020 NXP
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/fsw/mc.h>

#incwude "fsw-mc-pwivate.h"

/*
 * cache the DPWC vewsion to weduce the numbew of commands
 * towawds the mc fiwmwawe
 */
static u16 dpwc_majow_vew;
static u16 dpwc_minow_vew;

/**
 * dpwc_open() - Open DPWC object fow use
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @containew_id: Containew ID to open
 * @token:	Wetuwned token of DPWC object
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 *
 * @wawning	Wequiwed befowe any opewation on the object.
 */
int dpwc_open(stwuct fsw_mc_io *mc_io,
	      u32 cmd_fwags,
	      int containew_id,
	      u16 *token)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpwc_cmd_open *cmd_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_OPEN, cmd_fwags,
					  0);
	cmd_pawams = (stwuct dpwc_cmd_open *)cmd.pawams;
	cmd_pawams->containew_id = cpu_to_we32(containew_id);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	*token = mc_cmd_hdw_wead_token(&cmd);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dpwc_open);

/**
 * dpwc_cwose() - Cwose the contwow session of the object
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWC object
 *
 * Aftew this function is cawwed, no fuwthew opewations awe
 * awwowed on the object without opening a new contwow session.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwc_cwose(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_CWOSE, cmd_fwags,
					  token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
EXPOWT_SYMBOW_GPW(dpwc_cwose);

/**
 * dpwc_weset_containew - Weset chiwd containew.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWC object
 * @chiwd_containew_id:	ID of the containew to weset
 * @options: 32 bit options:
 *   - 0 (no bits set) - aww the objects inside the containew awe
 *     weset. The chiwd containews awe entewed wecuwsivewy and the
 *     objects weset. Aww the objects (incwuding the chiwd containews)
 *     awe cwosed.
 *   - bit 0 set - aww the objects inside the containew awe weset.
 *     Howevew the chiwd containews awe not entewed wecuwsivewy.
 *     This option is suppowted fow API vewsions >= 6.5
 * In case a softwawe context cwashes ow becomes non-wesponsive, the pawent
 * may wish to weset its wesouwces containew befowe the softwawe context is
 * westawted.
 *
 * This woutine infowms aww objects assigned to the chiwd containew that the
 * containew is being weset, so they may pewfowm any cweanup opewations that awe
 * needed. Aww objects handwes that wewe owned by the chiwd containew shaww be
 * cwosed.
 *
 * Note that such wequest may be submitted even if the chiwd softwawe context
 * has not cwashed, but the wesuwting object cweanup opewations wiww not be
 * awawe of that.
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwc_weset_containew(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 token,
			 int chiwd_containew_id,
			 u32 options)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpwc_cmd_weset_containew *cmd_pawams;
	u32 cmdid = DPWC_CMDID_WESET_CONT;
	int eww;

	/*
	 * If the DPWC object vewsion was not yet cached, cache it now.
	 * Othewwise use the awweady cached vawue.
	 */
	if (!dpwc_majow_vew && !dpwc_minow_vew) {
		eww = dpwc_get_api_vewsion(mc_io, 0,
				&dpwc_majow_vew,
				&dpwc_minow_vew);
		if (eww)
			wetuwn eww;
	}

	/*
	 * MC API 6.5 intwoduced a new fiewd in the command used to pass
	 * some fwags.
	 * Bit 0 indicates that the chiwd containews awe not wecuwsivewy weset.
	 */
	if (dpwc_majow_vew > 6 || (dpwc_majow_vew == 6 && dpwc_minow_vew >= 5))
		cmdid = DPWC_CMDID_WESET_CONT_V2;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(cmdid, cmd_fwags, token);
	cmd_pawams = (stwuct dpwc_cmd_weset_containew *)cmd.pawams;
	cmd_pawams->chiwd_containew_id = cpu_to_we32(chiwd_containew_id);
	cmd_pawams->options = cpu_to_we32(options);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
EXPOWT_SYMBOW_GPW(dpwc_weset_containew);

/**
 * dpwc_set_iwq() - Set IWQ infowmation fow the DPWC to twiggew an intewwupt.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWC object
 * @iwq_index:	Identifies the intewwupt index to configuwe
 * @iwq_cfg:	IWQ configuwation
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwc_set_iwq(stwuct fsw_mc_io *mc_io,
		 u32 cmd_fwags,
		 u16 token,
		 u8 iwq_index,
		 stwuct dpwc_iwq_cfg *iwq_cfg)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpwc_cmd_set_iwq *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_SET_IWQ,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpwc_cmd_set_iwq *)cmd.pawams;
	cmd_pawams->iwq_vaw = cpu_to_we32(iwq_cfg->vaw);
	cmd_pawams->iwq_index = iwq_index;
	cmd_pawams->iwq_addw = cpu_to_we64(iwq_cfg->paddw);
	cmd_pawams->iwq_num = cpu_to_we32(iwq_cfg->iwq_num);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpwc_set_iwq_enabwe() - Set ovewaww intewwupt state.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWC object
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
int dpwc_set_iwq_enabwe(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			u8 iwq_index,
			u8 en)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpwc_cmd_set_iwq_enabwe *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_SET_IWQ_ENABWE,
					  cmd_fwags, token);
	cmd_pawams = (stwuct dpwc_cmd_set_iwq_enabwe *)cmd.pawams;
	cmd_pawams->enabwe = en & DPWC_ENABWE;
	cmd_pawams->iwq_index = iwq_index;

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpwc_set_iwq_mask() - Set intewwupt mask.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWC object
 * @iwq_index:	The intewwupt index to configuwe
 * @mask:	event mask to twiggew intewwupt;
 *			each bit:
 *				0 = ignowe event
 *				1 = considew event fow assewting iwq
 *
 * Evewy intewwupt can have up to 32 causes and the intewwupt modew suppowts
 * masking/unmasking each cause independentwy
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwc_set_iwq_mask(stwuct fsw_mc_io *mc_io,
		      u32 cmd_fwags,
		      u16 token,
		      u8 iwq_index,
		      u32 mask)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpwc_cmd_set_iwq_mask *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_SET_IWQ_MASK,
					  cmd_fwags, token);
	cmd_pawams = (stwuct dpwc_cmd_set_iwq_mask *)cmd.pawams;
	cmd_pawams->mask = cpu_to_we32(mask);
	cmd_pawams->iwq_index = iwq_index;

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpwc_get_iwq_status() - Get the cuwwent status of any pending intewwupts.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWC object
 * @iwq_index:	The intewwupt index to configuwe
 * @status:	Wetuwned intewwupts status - one bit pew cause:
 *			0 = no intewwupt pending
 *			1 = intewwupt pending
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwc_get_iwq_status(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			u8 iwq_index,
			u32 *status)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpwc_cmd_get_iwq_status *cmd_pawams;
	stwuct dpwc_wsp_get_iwq_status *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_GET_IWQ_STATUS,
					  cmd_fwags, token);
	cmd_pawams = (stwuct dpwc_cmd_get_iwq_status *)cmd.pawams;
	cmd_pawams->status = cpu_to_we32(*status);
	cmd_pawams->iwq_index = iwq_index;

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpwc_wsp_get_iwq_status *)cmd.pawams;
	*status = we32_to_cpu(wsp_pawams->status);

	wetuwn 0;
}

/**
 * dpwc_cweaw_iwq_status() - Cweaw a pending intewwupt's status
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWC object
 * @iwq_index:	The intewwupt index to configuwe
 * @status:	bits to cweaw (W1C) - one bit pew cause:
 *					0 = don't change
 *					1 = cweaw status bit
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwc_cweaw_iwq_status(stwuct fsw_mc_io *mc_io,
			  u32 cmd_fwags,
			  u16 token,
			  u8 iwq_index,
			  u32 status)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpwc_cmd_cweaw_iwq_status *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_CWEAW_IWQ_STATUS,
					  cmd_fwags, token);
	cmd_pawams = (stwuct dpwc_cmd_cweaw_iwq_status *)cmd.pawams;
	cmd_pawams->status = cpu_to_we32(status);
	cmd_pawams->iwq_index = iwq_index;

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpwc_get_attwibutes() - Obtains containew attwibutes
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWC object
 * @attw:	Wetuwned containew attwibutes
 *
 * Wetuwn:     '0' on Success; Ewwow code othewwise.
 */
int dpwc_get_attwibutes(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			stwuct dpwc_attwibutes *attw)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpwc_wsp_get_attwibutes *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_GET_ATTW,
					  cmd_fwags,
					  token);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpwc_wsp_get_attwibutes *)cmd.pawams;
	attw->containew_id = we32_to_cpu(wsp_pawams->containew_id);
	attw->icid = we32_to_cpu(wsp_pawams->icid);
	attw->options = we32_to_cpu(wsp_pawams->options);
	attw->powtaw_id = we32_to_cpu(wsp_pawams->powtaw_id);

	wetuwn 0;
}

/**
 * dpwc_get_obj_count() - Obtains the numbew of objects in the DPWC
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWC object
 * @obj_count:	Numbew of objects assigned to the DPWC
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwc_get_obj_count(stwuct fsw_mc_io *mc_io,
		       u32 cmd_fwags,
		       u16 token,
		       int *obj_count)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpwc_wsp_get_obj_count *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_GET_OBJ_COUNT,
					  cmd_fwags, token);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpwc_wsp_get_obj_count *)cmd.pawams;
	*obj_count = we32_to_cpu(wsp_pawams->obj_count);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dpwc_get_obj_count);

/**
 * dpwc_get_obj() - Get genewaw infowmation on an object
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWC object
 * @obj_index:	Index of the object to be quewied (< obj_count)
 * @obj_desc:	Wetuwns the wequested object descwiptow
 *
 * The object descwiptows awe wetwieved one by one by incwementing
 * obj_index up to (not incwuding) the vawue of obj_count wetuwned
 * fwom dpwc_get_obj_count(). dpwc_get_obj_count() must
 * be cawwed pwiow to dpwc_get_obj().
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwc_get_obj(stwuct fsw_mc_io *mc_io,
		 u32 cmd_fwags,
		 u16 token,
		 int obj_index,
		 stwuct fsw_mc_obj_desc *obj_desc)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpwc_cmd_get_obj *cmd_pawams;
	stwuct dpwc_wsp_get_obj *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_GET_OBJ,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpwc_cmd_get_obj *)cmd.pawams;
	cmd_pawams->obj_index = cpu_to_we32(obj_index);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpwc_wsp_get_obj *)cmd.pawams;
	obj_desc->id = we32_to_cpu(wsp_pawams->id);
	obj_desc->vendow = we16_to_cpu(wsp_pawams->vendow);
	obj_desc->iwq_count = wsp_pawams->iwq_count;
	obj_desc->wegion_count = wsp_pawams->wegion_count;
	obj_desc->state = we32_to_cpu(wsp_pawams->state);
	obj_desc->vew_majow = we16_to_cpu(wsp_pawams->vewsion_majow);
	obj_desc->vew_minow = we16_to_cpu(wsp_pawams->vewsion_minow);
	obj_desc->fwags = we16_to_cpu(wsp_pawams->fwags);
	stwscpy_pad(obj_desc->type, wsp_pawams->type, 16);
	stwscpy_pad(obj_desc->wabew, wsp_pawams->wabew, 16);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dpwc_get_obj);

/**
 * dpwc_set_obj_iwq() - Set IWQ infowmation fow object to twiggew an intewwupt.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWC object
 * @obj_type:	Type of the object to set its IWQ
 * @obj_id:	ID of the object to set its IWQ
 * @iwq_index:	The intewwupt index to configuwe
 * @iwq_cfg:	IWQ configuwation
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwc_set_obj_iwq(stwuct fsw_mc_io *mc_io,
		     u32 cmd_fwags,
		     u16 token,
		     chaw *obj_type,
		     int obj_id,
		     u8 iwq_index,
		     stwuct dpwc_iwq_cfg *iwq_cfg)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpwc_cmd_set_obj_iwq *cmd_pawams;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_SET_OBJ_IWQ,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpwc_cmd_set_obj_iwq *)cmd.pawams;
	cmd_pawams->iwq_vaw = cpu_to_we32(iwq_cfg->vaw);
	cmd_pawams->iwq_index = iwq_index;
	cmd_pawams->iwq_addw = cpu_to_we64(iwq_cfg->paddw);
	cmd_pawams->iwq_num = cpu_to_we32(iwq_cfg->iwq_num);
	cmd_pawams->obj_id = cpu_to_we32(obj_id);
	stwscpy_pad(cmd_pawams->obj_type, obj_type, 16);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
EXPOWT_SYMBOW_GPW(dpwc_set_obj_iwq);

/**
 * dpwc_get_obj_wegion() - Get wegion infowmation fow a specified object.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWC object
 * @obj_type:	Object type as wetuwned in dpwc_get_obj()
 * @obj_id:	Unique object instance as wetuwned in dpwc_get_obj()
 * @wegion_index: The specific wegion to quewy
 * @wegion_desc:  Wetuwns the wequested wegion descwiptow
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwc_get_obj_wegion(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			chaw *obj_type,
			int obj_id,
			u8 wegion_index,
			stwuct dpwc_wegion_desc *wegion_desc)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpwc_cmd_get_obj_wegion *cmd_pawams;
	stwuct dpwc_wsp_get_obj_wegion *wsp_pawams;
	int eww;

    /*
     * If the DPWC object vewsion was not yet cached, cache it now.
     * Othewwise use the awweady cached vawue.
     */
	if (!dpwc_majow_vew && !dpwc_minow_vew) {
		eww = dpwc_get_api_vewsion(mc_io, 0,
				      &dpwc_majow_vew,
				      &dpwc_minow_vew);
		if (eww)
			wetuwn eww;
	}

	if (dpwc_majow_vew > 6 || (dpwc_majow_vew == 6 && dpwc_minow_vew >= 6)) {
		/*
		 * MC API vewsion 6.6 changed the size of the MC powtaws and softwawe
		 * powtaws to 64K (as impwemented by hawdwawe). If owdew API is in use the
		 * size wepowted is wess (64 bytes fow mc powtaws and 4K fow softwawe
		 * powtaws).
		 */

		cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_GET_OBJ_WEG_V3,
						  cmd_fwags, token);

	} ewse if (dpwc_majow_vew == 6 && dpwc_minow_vew >= 3) {
		/*
		 * MC API vewsion 6.3 intwoduced a new fiewd to the wegion
		 * descwiptow: base_addwess. If the owdew API is in use then the base
		 * addwess is set to zewo to indicate it needs to be obtained ewsewhewe
		 * (typicawwy the device twee).
		 */
		cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_GET_OBJ_WEG_V2,
						  cmd_fwags, token);
	} ewse {
		cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_GET_OBJ_WEG,
						  cmd_fwags, token);
	}

	cmd_pawams = (stwuct dpwc_cmd_get_obj_wegion *)cmd.pawams;
	cmd_pawams->obj_id = cpu_to_we32(obj_id);
	cmd_pawams->wegion_index = wegion_index;
	stwscpy_pad(cmd_pawams->obj_type, obj_type, 16);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpwc_wsp_get_obj_wegion *)cmd.pawams;
	wegion_desc->base_offset = we64_to_cpu(wsp_pawams->base_offset);
	wegion_desc->size = we32_to_cpu(wsp_pawams->size);
	wegion_desc->type = wsp_pawams->type;
	wegion_desc->fwags = we32_to_cpu(wsp_pawams->fwags);
	if (dpwc_majow_vew > 6 || (dpwc_majow_vew == 6 && dpwc_minow_vew >= 3))
		wegion_desc->base_addwess = we64_to_cpu(wsp_pawams->base_addw);
	ewse
		wegion_desc->base_addwess = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dpwc_get_obj_wegion);

/**
 * dpwc_get_api_vewsion - Get Data Path Wesouwce Containew API vewsion
 * @mc_io:	Pointew to Mc powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @majow_vew:	Majow vewsion of Data Path Wesouwce Containew API
 * @minow_vew:	Minow vewsion of Data Path Wesouwce Containew API
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwc_get_api_vewsion(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 *majow_vew,
			 u16 *minow_vew)
{
	stwuct fsw_mc_command cmd = { 0 };
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_GET_API_VEWSION,
					  cmd_fwags, 0);

	/* send command to mc */
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	mc_cmd_wead_api_vewsion(&cmd, majow_vew, minow_vew);

	wetuwn 0;
}

/**
 * dpwc_get_containew_id - Get containew ID associated with a given powtaw.
 * @mc_io:		Pointew to Mc powtaw's I/O object
 * @cmd_fwags:		Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @containew_id:	Wequested containew id
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
int dpwc_get_containew_id(stwuct fsw_mc_io *mc_io,
			  u32 cmd_fwags,
			  int *containew_id)
{
	stwuct fsw_mc_command cmd = { 0 };
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_GET_CONT_ID,
					  cmd_fwags,
					  0);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	*containew_id = (int)mc_cmd_wead_object_id(&cmd);

	wetuwn 0;
}

/**
 * dpwc_get_connection() - Get connected endpoint and wink status if connection
 *			exists.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPWC object
 * @endpoint1:	Endpoint 1 configuwation pawametews
 * @endpoint2:	Wetuwned endpoint 2 configuwation pawametews
 * @state:	Wetuwned wink state:
 *		1 - wink is up;
 *		0 - wink is down;
 *		-1 - no connection (endpoint2 infowmation is iwwewevant)
 *
 * Wetuwn:     '0' on Success; -ENOTCONN if connection does not exist.
 */
int dpwc_get_connection(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			const stwuct dpwc_endpoint *endpoint1,
			stwuct dpwc_endpoint *endpoint2,
			int *state)
{
	stwuct dpwc_cmd_get_connection *cmd_pawams;
	stwuct dpwc_wsp_get_connection *wsp_pawams;
	stwuct fsw_mc_command cmd = { 0 };
	int eww, i;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPWC_CMDID_GET_CONNECTION,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpwc_cmd_get_connection *)cmd.pawams;
	cmd_pawams->ep1_id = cpu_to_we32(endpoint1->id);
	cmd_pawams->ep1_intewface_id = cpu_to_we16(endpoint1->if_id);
	fow (i = 0; i < 16; i++)
		cmd_pawams->ep1_type[i] = endpoint1->type[i];

	/* send command to mc */
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn -ENOTCONN;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpwc_wsp_get_connection *)cmd.pawams;
	endpoint2->id = we32_to_cpu(wsp_pawams->ep2_id);
	endpoint2->if_id = we16_to_cpu(wsp_pawams->ep2_intewface_id);
	*state = we32_to_cpu(wsp_pawams->state);
	fow (i = 0; i < 16; i++)
		endpoint2->type[i] = wsp_pawams->ep2_type[i];

	wetuwn 0;
}
