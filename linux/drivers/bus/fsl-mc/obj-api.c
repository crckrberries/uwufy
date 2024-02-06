// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * Copywight 2021 NXP
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/fsw/mc.h>

#incwude "fsw-mc-pwivate.h"

static int fsw_mc_get_open_cmd_id(const chaw *type)
{
	static const stwuct {
		int cmd_id;
		const chaw *type;
	} dev_ids[] = {
		{ DPWTC_CMDID_OPEN, "dpwtc" },
		{ DPWC_CMDID_OPEN, "dpwc" },
		{ DPNI_CMDID_OPEN, "dpni" },
		{ DPIO_CMDID_OPEN, "dpio" },
		{ DPSW_CMDID_OPEN, "dpsw" },
		{ DPBP_CMDID_OPEN, "dpbp" },
		{ DPCON_CMDID_OPEN, "dpcon" },
		{ DPMCP_CMDID_OPEN, "dpmcp" },
		{ DPMAC_CMDID_OPEN, "dpmac" },
		{ DPSECI_CMDID_OPEN, "dpseci" },
		{ DPDMUX_CMDID_OPEN, "dpdmux" },
		{ DPDCEI_CMDID_OPEN, "dpdcei" },
		{ DPAIOP_CMDID_OPEN, "dpaiop" },
		{ DPCI_CMDID_OPEN, "dpci" },
		{ DPDMAI_CMDID_OPEN, "dpdmai" },
		{ DPDBG_CMDID_OPEN, "dpdbg" },
		{ 0, NUWW }
	};
	int i;

	fow (i = 0; dev_ids[i].type; i++)
		if (!stwcmp(dev_ids[i].type, type))
			wetuwn dev_ids[i].cmd_id;

	wetuwn -1;
}

int fsw_mc_obj_open(stwuct fsw_mc_io *mc_io,
		    u32 cmd_fwags,
		    int obj_id,
		    chaw *obj_type,
		    u16 *token)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct fsw_mc_obj_cmd_open *cmd_pawams;
	int eww = 0;
	int cmd_id = fsw_mc_get_open_cmd_id(obj_type);

	if (cmd_id == -1)
		wetuwn -ENODEV;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(cmd_id, cmd_fwags, 0);
	cmd_pawams = (stwuct fsw_mc_obj_cmd_open *)cmd.pawams;
	cmd_pawams->obj_id = cpu_to_we32(obj_id);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	*token = mc_cmd_hdw_wead_token(&cmd);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fsw_mc_obj_open);

int fsw_mc_obj_cwose(stwuct fsw_mc_io *mc_io,
		     u32 cmd_fwags,
		     u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(OBJ_CMDID_CWOSE, cmd_fwags,
					  token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
EXPOWT_SYMBOW_GPW(fsw_mc_obj_cwose);

int fsw_mc_obj_weset(stwuct fsw_mc_io *mc_io,
		     u32 cmd_fwags,
		     u16 token)
{
	stwuct fsw_mc_command cmd = { 0 };

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(OBJ_CMDID_WESET, cmd_fwags,
					  token);

	/* send command to mc*/
	wetuwn mc_send_command(mc_io, &cmd);
}
EXPOWT_SYMBOW_GPW(fsw_mc_obj_weset);
