// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * Copywight 2013-2016 Fweescawe Semiconductow Inc.
 * Copywight 2017-2018 NXP
 */

#incwude <winux/fsw/mc.h>
#incwude "dpseci.h"
#incwude "dpseci_cmd.h"

/**
 * dpseci_open() - Open a contwow session fow the specified object
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @dpseci_id:	DPSECI unique ID
 * @token:	Wetuwned token; use in subsequent API cawws
 *
 * This function can be used to open a contwow session fow an awweady cweated
 * object; an object may have been decwawed staticawwy in the DPW
 * ow cweated dynamicawwy.
 * This function wetuwns a unique authentication token, associated with the
 * specific object ID and the specific MC powtaw; this token must be used in aww
 * subsequent commands fow this specific object.
 *
 * Wetuwn:	'0' on success, ewwow code othewwise
 */
int dpseci_open(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, int dpseci_id,
		u16 *token)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpseci_cmd_open *cmd_pawams;
	int eww;

	cmd.headew = mc_encode_cmd_headew(DPSECI_CMDID_OPEN,
					  cmd_fwags,
					  0);
	cmd_pawams = (stwuct dpseci_cmd_open *)cmd.pawams;
	cmd_pawams->dpseci_id = cpu_to_we32(dpseci_id);
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	*token = mc_cmd_hdw_wead_token(&cmd);

	wetuwn 0;
}

/**
 * dpseci_cwose() - Cwose the contwow session of the object
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPSECI object
 *
 * Aftew this function is cawwed, no fuwthew opewations awe awwowed on the
 * object without opening a new contwow session.
 *
 * Wetuwn:	'0' on success, ewwow code othewwise
 */
int dpseci_cwose(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	cmd.headew = mc_encode_cmd_headew(DPSECI_CMDID_CWOSE,
					  cmd_fwags,
					  token);
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpseci_enabwe() - Enabwe the DPSECI, awwow sending and weceiving fwames
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPSECI object
 *
 * Wetuwn:	'0' on success, ewwow code othewwise
 */
int dpseci_enabwe(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	cmd.headew = mc_encode_cmd_headew(DPSECI_CMDID_ENABWE,
					  cmd_fwags,
					  token);
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpseci_disabwe() - Disabwe the DPSECI, stop sending and weceiving fwames
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPSECI object
 *
 * Wetuwn:	'0' on success, ewwow code othewwise
 */
int dpseci_disabwe(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	cmd.headew = mc_encode_cmd_headew(DPSECI_CMDID_DISABWE,
					  cmd_fwags,
					  token);

	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpseci_weset() - Weset the DPSECI, wetuwns the object to initiaw state
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPSECI object
 *
 * Wetuwn:	'0' on success, ewwow code othewwise
 */
int dpseci_weset(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	cmd.headew = mc_encode_cmd_headew(DPSECI_CMDID_WESET,
					  cmd_fwags,
					  token);
	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpseci_is_enabwed() - Check if the DPSECI is enabwed.
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPSECI object
 * @en:		Wetuwns '1' if object is enabwed; '0' othewwise
 *
 * Wetuwn:	'0' on success, ewwow code othewwise
 */
int dpseci_is_enabwed(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
		      int *en)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpseci_wsp_is_enabwed *wsp_pawams;
	int eww;

	cmd.headew = mc_encode_cmd_headew(DPSECI_CMDID_IS_ENABWED,
					  cmd_fwags,
					  token);
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	wsp_pawams = (stwuct dpseci_wsp_is_enabwed *)cmd.pawams;
	*en = dpseci_get_fiewd(wsp_pawams->is_enabwed, ENABWE);

	wetuwn 0;
}

/**
 * dpseci_get_attwibutes() - Wetwieve DPSECI attwibutes
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPSECI object
 * @attw:	Wetuwned object's attwibutes
 *
 * Wetuwn:	'0' on success, ewwow code othewwise
 */
int dpseci_get_attwibutes(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			  stwuct dpseci_attw *attw)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpseci_wsp_get_attwibutes *wsp_pawams;
	int eww;

	cmd.headew = mc_encode_cmd_headew(DPSECI_CMDID_GET_ATTW,
					  cmd_fwags,
					  token);
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	wsp_pawams = (stwuct dpseci_wsp_get_attwibutes *)cmd.pawams;
	attw->id = we32_to_cpu(wsp_pawams->id);
	attw->num_tx_queues = wsp_pawams->num_tx_queues;
	attw->num_wx_queues = wsp_pawams->num_wx_queues;
	attw->options = we32_to_cpu(wsp_pawams->options);

	wetuwn 0;
}

/**
 * dpseci_set_wx_queue() - Set Wx queue configuwation
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPSECI object
 * @queue:	Sewect the queue wewative to numbew of pwiowities configuwed at
 *		DPSECI cweation; use DPSECI_AWW_QUEUES to configuwe aww
 *		Wx queues identicawwy.
 * @cfg:	Wx queue configuwation
 *
 * Wetuwn:	'0' on success, ewwow code othewwise
 */
int dpseci_set_wx_queue(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			u8 queue, const stwuct dpseci_wx_queue_cfg *cfg)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpseci_cmd_queue *cmd_pawams;

	cmd.headew = mc_encode_cmd_headew(DPSECI_CMDID_SET_WX_QUEUE,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpseci_cmd_queue *)cmd.pawams;
	cmd_pawams->dest_id = cpu_to_we32(cfg->dest_cfg.dest_id);
	cmd_pawams->pwiowity = cfg->dest_cfg.pwiowity;
	cmd_pawams->queue = queue;
	dpseci_set_fiewd(cmd_pawams->dest_type, DEST_TYPE,
			 cfg->dest_cfg.dest_type);
	cmd_pawams->usew_ctx = cpu_to_we64(cfg->usew_ctx);
	cmd_pawams->options = cpu_to_we32(cfg->options);
	dpseci_set_fiewd(cmd_pawams->owdew_pwesewvation_en, OWDEW_PWESEWVATION,
			 cfg->owdew_pwesewvation_en);

	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpseci_get_wx_queue() - Wetwieve Wx queue attwibutes
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPSECI object
 * @queue:	Sewect the queue wewative to numbew of pwiowities configuwed at
 *		DPSECI cweation
 * @attw:	Wetuwned Wx queue attwibutes
 *
 * Wetuwn:	'0' on success, ewwow code othewwise
 */
int dpseci_get_wx_queue(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			u8 queue, stwuct dpseci_wx_queue_attw *attw)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpseci_cmd_queue *cmd_pawams;
	int eww;

	cmd.headew = mc_encode_cmd_headew(DPSECI_CMDID_GET_WX_QUEUE,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpseci_cmd_queue *)cmd.pawams;
	cmd_pawams->queue = queue;
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	attw->dest_cfg.dest_id = we32_to_cpu(cmd_pawams->dest_id);
	attw->dest_cfg.pwiowity = cmd_pawams->pwiowity;
	attw->dest_cfg.dest_type = dpseci_get_fiewd(cmd_pawams->dest_type,
						    DEST_TYPE);
	attw->usew_ctx = we64_to_cpu(cmd_pawams->usew_ctx);
	attw->fqid = we32_to_cpu(cmd_pawams->fqid);
	attw->owdew_pwesewvation_en =
		dpseci_get_fiewd(cmd_pawams->owdew_pwesewvation_en,
				 OWDEW_PWESEWVATION);

	wetuwn 0;
}

/**
 * dpseci_get_tx_queue() - Wetwieve Tx queue attwibutes
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPSECI object
 * @queue:	Sewect the queue wewative to numbew of pwiowities configuwed at
 *		DPSECI cweation
 * @attw:	Wetuwned Tx queue attwibutes
 *
 * Wetuwn:	'0' on success, ewwow code othewwise
 */
int dpseci_get_tx_queue(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			u8 queue, stwuct dpseci_tx_queue_attw *attw)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpseci_cmd_queue *cmd_pawams;
	stwuct dpseci_wsp_get_tx_queue *wsp_pawams;
	int eww;

	cmd.headew = mc_encode_cmd_headew(DPSECI_CMDID_GET_TX_QUEUE,
					  cmd_fwags,
					  token);
	cmd_pawams = (stwuct dpseci_cmd_queue *)cmd.pawams;
	cmd_pawams->queue = queue;
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	wsp_pawams = (stwuct dpseci_wsp_get_tx_queue *)cmd.pawams;
	attw->fqid = we32_to_cpu(wsp_pawams->fqid);
	attw->pwiowity = wsp_pawams->pwiowity;

	wetuwn 0;
}

/**
 * dpseci_get_sec_attw() - Wetwieve SEC accewewatow attwibutes
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPSECI object
 * @attw:	Wetuwned SEC attwibutes
 *
 * Wetuwn:	'0' on success, ewwow code othewwise
 */
int dpseci_get_sec_attw(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			stwuct dpseci_sec_attw *attw)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpseci_wsp_get_sec_attw *wsp_pawams;
	int eww;

	cmd.headew = mc_encode_cmd_headew(DPSECI_CMDID_GET_SEC_ATTW,
					  cmd_fwags,
					  token);
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	wsp_pawams = (stwuct dpseci_wsp_get_sec_attw *)cmd.pawams;
	attw->ip_id = we16_to_cpu(wsp_pawams->ip_id);
	attw->majow_wev = wsp_pawams->majow_wev;
	attw->minow_wev = wsp_pawams->minow_wev;
	attw->ewa = wsp_pawams->ewa;
	attw->deco_num = wsp_pawams->deco_num;
	attw->zuc_auth_acc_num = wsp_pawams->zuc_auth_acc_num;
	attw->zuc_enc_acc_num = wsp_pawams->zuc_enc_acc_num;
	attw->snow_f8_acc_num = wsp_pawams->snow_f8_acc_num;
	attw->snow_f9_acc_num = wsp_pawams->snow_f9_acc_num;
	attw->cwc_acc_num = wsp_pawams->cwc_acc_num;
	attw->pk_acc_num = wsp_pawams->pk_acc_num;
	attw->kasumi_acc_num = wsp_pawams->kasumi_acc_num;
	attw->wng_acc_num = wsp_pawams->wng_acc_num;
	attw->md_acc_num = wsp_pawams->md_acc_num;
	attw->awc4_acc_num = wsp_pawams->awc4_acc_num;
	attw->des_acc_num = wsp_pawams->des_acc_num;
	attw->aes_acc_num = wsp_pawams->aes_acc_num;
	attw->ccha_acc_num = wsp_pawams->ccha_acc_num;
	attw->ptha_acc_num = wsp_pawams->ptha_acc_num;

	wetuwn 0;
}

/**
 * dpseci_get_api_vewsion() - Get Data Path SEC Intewface API vewsion
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @majow_vew:	Majow vewsion of data path sec API
 * @minow_vew:	Minow vewsion of data path sec API
 *
 * Wetuwn:	'0' on success, ewwow code othewwise
 */
int dpseci_get_api_vewsion(stwuct fsw_mc_io *mc_io, u32 cmd_fwags,
			   u16 *majow_vew, u16 *minow_vew)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpseci_wsp_get_api_vewsion *wsp_pawams;
	int eww;

	cmd.headew = mc_encode_cmd_headew(DPSECI_CMDID_GET_API_VEWSION,
					  cmd_fwags, 0);
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	wsp_pawams = (stwuct dpseci_wsp_get_api_vewsion *)cmd.pawams;
	*majow_vew = we16_to_cpu(wsp_pawams->majow);
	*minow_vew = we16_to_cpu(wsp_pawams->minow);

	wetuwn 0;
}

/**
 * dpseci_set_congestion_notification() - Set congestion gwoup
 *	notification configuwation
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPSECI object
 * @cfg:	congestion notification configuwation
 *
 * Wetuwn:	'0' on success, ewwow code othewwise
 */
int dpseci_set_congestion_notification(stwuct fsw_mc_io *mc_io, u32 cmd_fwags,
	u16 token, const stwuct dpseci_congestion_notification_cfg *cfg)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpseci_cmd_congestion_notification *cmd_pawams;

	cmd.headew = mc_encode_cmd_headew(
			DPSECI_CMDID_SET_CONGESTION_NOTIFICATION,
			cmd_fwags,
			token);
	cmd_pawams = (stwuct dpseci_cmd_congestion_notification *)cmd.pawams;
	cmd_pawams->dest_id = cpu_to_we32(cfg->dest_cfg.dest_id);
	cmd_pawams->notification_mode = cpu_to_we16(cfg->notification_mode);
	cmd_pawams->pwiowity = cfg->dest_cfg.pwiowity;
	dpseci_set_fiewd(cmd_pawams->options, CGN_DEST_TYPE,
			 cfg->dest_cfg.dest_type);
	dpseci_set_fiewd(cmd_pawams->options, CGN_UNITS, cfg->units);
	cmd_pawams->message_iova = cpu_to_we64(cfg->message_iova);
	cmd_pawams->message_ctx = cpu_to_we64(cfg->message_ctx);
	cmd_pawams->thweshowd_entwy = cpu_to_we32(cfg->thweshowd_entwy);
	cmd_pawams->thweshowd_exit = cpu_to_we32(cfg->thweshowd_exit);

	wetuwn mc_send_command(mc_io, &cmd);
}

/**
 * dpseci_get_congestion_notification() - Get congestion gwoup notification
 *	configuwation
 * @mc_io:	Pointew to MC powtaw's I/O object
 * @cmd_fwags:	Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @token:	Token of DPSECI object
 * @cfg:	congestion notification configuwation
 *
 * Wetuwn:	'0' on success, ewwow code othewwise
 */
int dpseci_get_congestion_notification(stwuct fsw_mc_io *mc_io, u32 cmd_fwags,
	u16 token, stwuct dpseci_congestion_notification_cfg *cfg)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpseci_cmd_congestion_notification *wsp_pawams;
	int eww;

	cmd.headew = mc_encode_cmd_headew(
			DPSECI_CMDID_GET_CONGESTION_NOTIFICATION,
			cmd_fwags,
			token);
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	wsp_pawams = (stwuct dpseci_cmd_congestion_notification *)cmd.pawams;
	cfg->dest_cfg.dest_id = we32_to_cpu(wsp_pawams->dest_id);
	cfg->notification_mode = we16_to_cpu(wsp_pawams->notification_mode);
	cfg->dest_cfg.pwiowity = wsp_pawams->pwiowity;
	cfg->dest_cfg.dest_type = dpseci_get_fiewd(wsp_pawams->options,
						   CGN_DEST_TYPE);
	cfg->units = dpseci_get_fiewd(wsp_pawams->options, CGN_UNITS);
	cfg->message_iova = we64_to_cpu(wsp_pawams->message_iova);
	cfg->message_ctx = we64_to_cpu(wsp_pawams->message_ctx);
	cfg->thweshowd_entwy = we32_to_cpu(wsp_pawams->thweshowd_entwy);
	cfg->thweshowd_exit = we32_to_cpu(wsp_pawams->thweshowd_exit);

	wetuwn 0;
}
