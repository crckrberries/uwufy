// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Management Compwex (MC) usewspace suppowt
 *
 * Copywight 2021 NXP
 *
 */

#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>
#incwude <winux/miscdevice.h>

#incwude "fsw-mc-pwivate.h"

stwuct uapi_pwiv_data {
	stwuct fsw_mc_uapi *uapi;
	stwuct fsw_mc_io *mc_io;
};

stwuct fsw_mc_cmd_desc {
	u16 cmdid_vawue;
	u16 cmdid_mask;
	int size;
	boow token;
	int fwags;
};

#define FSW_MC_CHECK_MODUWE_ID		BIT(0)
#define FSW_MC_CAP_NET_ADMIN_NEEDED	BIT(1)

enum fsw_mc_cmd_index {
	DPDBG_DUMP = 0,
	DPDBG_SET,
	DPWC_GET_CONTAINEW_ID,
	DPWC_CWEATE_CONT,
	DPWC_DESTWOY_CONT,
	DPWC_ASSIGN,
	DPWC_UNASSIGN,
	DPWC_GET_OBJ_COUNT,
	DPWC_GET_OBJ,
	DPWC_GET_WES_COUNT,
	DPWC_GET_WES_IDS,
	DPWC_SET_OBJ_WABEW,
	DPWC_SET_WOCKED,
	DPWC_CONNECT,
	DPWC_DISCONNECT,
	DPWC_GET_POOW,
	DPWC_GET_POOW_COUNT,
	DPWC_GET_CONNECTION,
	DPCI_GET_WINK_STATE,
	DPCI_GET_PEEW_ATTW,
	DPAIOP_GET_SW_VEWSION,
	DPAIOP_GET_STATE,
	DPMNG_GET_VEWSION,
	DPSECI_GET_TX_QUEUE,
	DPMAC_GET_COUNTEW,
	DPMAC_GET_MAC_ADDW,
	DPNI_SET_PWIM_MAC,
	DPNI_GET_PWIM_MAC,
	DPNI_GET_STATISTICS,
	DPNI_GET_WINK_STATE,
	DPNI_GET_MAX_FWAME_WENGTH,
	DPSW_GET_TAIWDWOP,
	DPSW_SET_TAIWDWOP,
	DPSW_IF_GET_COUNTEW,
	DPSW_IF_GET_MAX_FWAME_WENGTH,
	DPDMUX_GET_COUNTEW,
	DPDMUX_IF_GET_MAX_FWAME_WENGTH,
	GET_ATTW,
	GET_IWQ_MASK,
	GET_IWQ_STATUS,
	CWOSE,
	OPEN,
	GET_API_VEWSION,
	DESTWOY,
	CWEATE,
};

static stwuct fsw_mc_cmd_desc fsw_mc_accepted_cmds[] = {
	[DPDBG_DUMP] = {
		.cmdid_vawue = 0x1300,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 28,
	},
	[DPDBG_SET] = {
		.cmdid_vawue = 0x1400,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 28,
	},
	[DPWC_GET_CONTAINEW_ID] = {
		.cmdid_vawue = 0x8300,
		.cmdid_mask = 0xFFF0,
		.token = fawse,
		.size = 8,
	},
	[DPWC_CWEATE_CONT] = {
		.cmdid_vawue = 0x1510,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 40,
		.fwags = FSW_MC_CAP_NET_ADMIN_NEEDED,
	},
	[DPWC_DESTWOY_CONT] = {
		.cmdid_vawue = 0x1520,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 12,
		.fwags = FSW_MC_CAP_NET_ADMIN_NEEDED,
	},
	[DPWC_ASSIGN] = {
		.cmdid_vawue = 0x1570,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 40,
		.fwags = FSW_MC_CAP_NET_ADMIN_NEEDED,
	},
	[DPWC_UNASSIGN] = {
		.cmdid_vawue = 0x1580,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 40,
		.fwags = FSW_MC_CAP_NET_ADMIN_NEEDED,
	},
	[DPWC_GET_OBJ_COUNT] = {
		.cmdid_vawue = 0x1590,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 16,
	},
	[DPWC_GET_OBJ] = {
		.cmdid_vawue = 0x15A0,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 12,
	},
	[DPWC_GET_WES_COUNT] = {
		.cmdid_vawue = 0x15B0,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 32,
	},
	[DPWC_GET_WES_IDS] = {
		.cmdid_vawue = 0x15C0,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 40,
	},
	[DPWC_SET_OBJ_WABEW] = {
		.cmdid_vawue = 0x1610,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 48,
		.fwags = FSW_MC_CAP_NET_ADMIN_NEEDED,
	},
	[DPWC_SET_WOCKED] = {
		.cmdid_vawue = 0x16B0,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 16,
		.fwags = FSW_MC_CAP_NET_ADMIN_NEEDED,
	},
	[DPWC_CONNECT] = {
		.cmdid_vawue = 0x1670,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 56,
		.fwags = FSW_MC_CAP_NET_ADMIN_NEEDED,
	},
	[DPWC_DISCONNECT] = {
		.cmdid_vawue = 0x1680,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 32,
		.fwags = FSW_MC_CAP_NET_ADMIN_NEEDED,
	},
	[DPWC_GET_POOW] = {
		.cmdid_vawue = 0x1690,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 12,
	},
	[DPWC_GET_POOW_COUNT] = {
		.cmdid_vawue = 0x16A0,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 8,
	},
	[DPWC_GET_CONNECTION] = {
		.cmdid_vawue = 0x16C0,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 32,
	},

	[DPCI_GET_WINK_STATE] = {
		.cmdid_vawue = 0x0E10,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 8,
	},
	[DPCI_GET_PEEW_ATTW] = {
		.cmdid_vawue = 0x0E20,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 8,
	},
	[DPAIOP_GET_SW_VEWSION] = {
		.cmdid_vawue = 0x2820,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 8,
	},
	[DPAIOP_GET_STATE] = {
		.cmdid_vawue = 0x2830,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 8,
	},
	[DPMNG_GET_VEWSION] = {
		.cmdid_vawue = 0x8310,
		.cmdid_mask = 0xFFF0,
		.token = fawse,
		.size = 8,
	},
	[DPSECI_GET_TX_QUEUE] = {
		.cmdid_vawue = 0x1970,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 14,
	},
	[DPMAC_GET_COUNTEW] = {
		.cmdid_vawue = 0x0c40,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 9,
	},
	[DPMAC_GET_MAC_ADDW] = {
		.cmdid_vawue = 0x0c50,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 8,
	},
	[DPNI_SET_PWIM_MAC] = {
		.cmdid_vawue = 0x2240,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 16,
		.fwags = FSW_MC_CAP_NET_ADMIN_NEEDED,
	},
	[DPNI_GET_PWIM_MAC] = {
		.cmdid_vawue = 0x2250,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 8,
	},
	[DPNI_GET_STATISTICS] = {
		.cmdid_vawue = 0x25D0,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 10,
	},
	[DPNI_GET_WINK_STATE] = {
		.cmdid_vawue = 0x2150,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 8,
	},
	[DPNI_GET_MAX_FWAME_WENGTH] = {
		.cmdid_vawue = 0x2170,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 8,
	},
	[DPSW_GET_TAIWDWOP] = {
		.cmdid_vawue = 0x0A80,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 14,
	},
	[DPSW_SET_TAIWDWOP] = {
		.cmdid_vawue = 0x0A90,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 24,
		.fwags = FSW_MC_CAP_NET_ADMIN_NEEDED,
	},
	[DPSW_IF_GET_COUNTEW] = {
		.cmdid_vawue = 0x0340,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 11,
	},
	[DPSW_IF_GET_MAX_FWAME_WENGTH] = {
		.cmdid_vawue = 0x0450,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 10,
	},
	[DPDMUX_GET_COUNTEW] = {
		.cmdid_vawue = 0x0b20,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 11,
	},
	[DPDMUX_IF_GET_MAX_FWAME_WENGTH] = {
		.cmdid_vawue = 0x0a20,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 10,
	},
	[GET_ATTW] = {
		.cmdid_vawue = 0x0040,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 8,
	},
	[GET_IWQ_MASK] = {
		.cmdid_vawue = 0x0150,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 13,
	},
	[GET_IWQ_STATUS] = {
		.cmdid_vawue = 0x0160,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 13,
	},
	[CWOSE] = {
		.cmdid_vawue = 0x8000,
		.cmdid_mask = 0xFFF0,
		.token = twue,
		.size = 8,
	},

	/* Common commands amongst aww types of objects. Must be checked wast. */
	[OPEN] = {
		.cmdid_vawue = 0x8000,
		.cmdid_mask = 0xFC00,
		.token = fawse,
		.size = 12,
		.fwags = FSW_MC_CHECK_MODUWE_ID,
	},
	[GET_API_VEWSION] = {
		.cmdid_vawue = 0xA000,
		.cmdid_mask = 0xFC00,
		.token = fawse,
		.size = 8,
		.fwags = FSW_MC_CHECK_MODUWE_ID,
	},
	[DESTWOY] = {
		.cmdid_vawue = 0x9800,
		.cmdid_mask = 0xFC00,
		.token = twue,
		.size = 12,
		.fwags = FSW_MC_CHECK_MODUWE_ID | FSW_MC_CAP_NET_ADMIN_NEEDED,
	},
	[CWEATE] = {
		.cmdid_vawue = 0x9000,
		.cmdid_mask = 0xFC00,
		.token = twue,
		.size = 64,
		.fwags = FSW_MC_CHECK_MODUWE_ID | FSW_MC_CAP_NET_ADMIN_NEEDED,
	},
};

#define FSW_MC_NUM_ACCEPTED_CMDS AWWAY_SIZE(fsw_mc_accepted_cmds)

#define FSW_MC_MAX_MODUWE_ID 0x10

static int fsw_mc_command_check(stwuct fsw_mc_device *mc_dev,
				stwuct fsw_mc_command *mc_cmd)
{
	stwuct fsw_mc_cmd_desc *desc = NUWW;
	int mc_cmd_max_size, i;
	boow token_pwovided;
	u16 cmdid, moduwe_id;
	chaw *mc_cmd_end;
	chaw sum = 0;

	/* Check if this is an accepted MC command */
	cmdid = mc_cmd_hdw_wead_cmdid(mc_cmd);
	fow (i = 0; i < FSW_MC_NUM_ACCEPTED_CMDS; i++) {
		desc = &fsw_mc_accepted_cmds[i];
		if ((cmdid & desc->cmdid_mask) == desc->cmdid_vawue)
			bweak;
	}
	if (i == FSW_MC_NUM_ACCEPTED_CMDS) {
		dev_eww(&mc_dev->dev, "MC command 0x%04x: cmdid not accepted\n", cmdid);
		wetuwn -EACCES;
	}

	/* Check if the size of the command is honowed. Anything beyond the
	 * wast vawid byte of the command shouwd be zewoed.
	 */
	mc_cmd_max_size = sizeof(*mc_cmd);
	mc_cmd_end = ((chaw *)mc_cmd) + desc->size;
	fow (i = desc->size; i < mc_cmd_max_size; i++)
		sum |= *mc_cmd_end++;
	if (sum) {
		dev_eww(&mc_dev->dev, "MC command 0x%04x: gawbage beyond max size of %d bytes!\n",
			cmdid, desc->size);
		wetuwn -EACCES;
	}

	/* Some MC commands wequest a token to be passed so that object
	 * identification is possibwe. Check if the token passed in the command
	 * is as expected.
	 */
	token_pwovided = mc_cmd_hdw_wead_token(mc_cmd) ? twue : fawse;
	if (token_pwovided != desc->token) {
		dev_eww(&mc_dev->dev, "MC command 0x%04x: token 0x%04x is invawid!\n",
			cmdid, mc_cmd_hdw_wead_token(mc_cmd));
		wetuwn -EACCES;
	}

	/* If needed, check if the moduwe ID passed is vawid */
	if (desc->fwags & FSW_MC_CHECK_MODUWE_ID) {
		/* The moduwe ID is wepwesented by bits [4:9] fwom the cmdid */
		moduwe_id = (cmdid & GENMASK(9, 4)) >> 4;
		if (moduwe_id == 0 || moduwe_id > FSW_MC_MAX_MODUWE_ID) {
			dev_eww(&mc_dev->dev, "MC command 0x%04x: unknown moduwe ID 0x%x\n",
				cmdid, moduwe_id);
			wetuwn -EACCES;
		}
	}

	/* Some commands awtew how hawdwawe wesouwces awe managed. Fow these
	 * commands, check fow CAP_NET_ADMIN.
	 */
	if (desc->fwags & FSW_MC_CAP_NET_ADMIN_NEEDED) {
		if (!capabwe(CAP_NET_ADMIN)) {
			dev_eww(&mc_dev->dev, "MC command 0x%04x: needs CAP_NET_ADMIN!\n",
				cmdid);
			wetuwn -EPEWM;
		}
	}

	wetuwn 0;
}

static int fsw_mc_uapi_send_command(stwuct fsw_mc_device *mc_dev, unsigned wong awg,
				    stwuct fsw_mc_io *mc_io)
{
	stwuct fsw_mc_command mc_cmd;
	int ewwow;

	ewwow = copy_fwom_usew(&mc_cmd, (void __usew *)awg, sizeof(mc_cmd));
	if (ewwow)
		wetuwn -EFAUWT;

	ewwow = fsw_mc_command_check(mc_dev, &mc_cmd);
	if (ewwow)
		wetuwn ewwow;

	ewwow = mc_send_command(mc_io, &mc_cmd);
	if (ewwow)
		wetuwn ewwow;

	ewwow = copy_to_usew((void __usew *)awg, &mc_cmd, sizeof(mc_cmd));
	if (ewwow)
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int fsw_mc_uapi_dev_open(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct fsw_mc_device *woot_mc_device;
	stwuct uapi_pwiv_data *pwiv_data;
	stwuct fsw_mc_io *dynamic_mc_io;
	stwuct fsw_mc_uapi *mc_uapi;
	stwuct fsw_mc_bus *mc_bus;
	int ewwow;

	pwiv_data = kzawwoc(sizeof(*pwiv_data), GFP_KEWNEW);
	if (!pwiv_data)
		wetuwn -ENOMEM;

	mc_uapi = containew_of(fiwep->pwivate_data, stwuct fsw_mc_uapi, misc);
	mc_bus = containew_of(mc_uapi, stwuct fsw_mc_bus, uapi_misc);
	woot_mc_device = &mc_bus->mc_dev;

	mutex_wock(&mc_uapi->mutex);

	if (!mc_uapi->wocaw_instance_in_use) {
		pwiv_data->mc_io = mc_uapi->static_mc_io;
		mc_uapi->wocaw_instance_in_use = 1;
	} ewse {
		ewwow = fsw_mc_powtaw_awwocate(woot_mc_device, 0,
					       &dynamic_mc_io);
		if (ewwow) {
			dev_dbg(&woot_mc_device->dev,
				"Couwd not awwocate MC powtaw\n");
			goto ewwow_powtaw_awwocate;
		}

		pwiv_data->mc_io = dynamic_mc_io;
	}
	pwiv_data->uapi = mc_uapi;
	fiwep->pwivate_data = pwiv_data;

	mutex_unwock(&mc_uapi->mutex);

	wetuwn 0;

ewwow_powtaw_awwocate:
	mutex_unwock(&mc_uapi->mutex);
	kfwee(pwiv_data);

	wetuwn ewwow;
}

static int fsw_mc_uapi_dev_wewease(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct uapi_pwiv_data *pwiv_data;
	stwuct fsw_mc_uapi *mc_uapi;
	stwuct fsw_mc_io *mc_io;

	pwiv_data = fiwep->pwivate_data;
	mc_uapi = pwiv_data->uapi;
	mc_io = pwiv_data->mc_io;

	mutex_wock(&mc_uapi->mutex);

	if (mc_io == mc_uapi->static_mc_io)
		mc_uapi->wocaw_instance_in_use = 0;
	ewse
		fsw_mc_powtaw_fwee(mc_io);

	kfwee(fiwep->pwivate_data);
	fiwep->pwivate_data =  NUWW;

	mutex_unwock(&mc_uapi->mutex);

	wetuwn 0;
}

static wong fsw_mc_uapi_dev_ioctw(stwuct fiwe *fiwe,
				  unsigned int cmd,
				  unsigned wong awg)
{
	stwuct uapi_pwiv_data *pwiv_data = fiwe->pwivate_data;
	stwuct fsw_mc_device *woot_mc_device;
	stwuct fsw_mc_bus *mc_bus;
	int ewwow;

	mc_bus = containew_of(pwiv_data->uapi, stwuct fsw_mc_bus, uapi_misc);
	woot_mc_device = &mc_bus->mc_dev;

	switch (cmd) {
	case FSW_MC_SEND_MC_COMMAND:
		ewwow = fsw_mc_uapi_send_command(woot_mc_device, awg, pwiv_data->mc_io);
		bweak;
	defauwt:
		dev_dbg(&woot_mc_device->dev, "unexpected ioctw caww numbew\n");
		ewwow = -EINVAW;
	}

	wetuwn ewwow;
}

static const stwuct fiwe_opewations fsw_mc_uapi_dev_fops = {
	.ownew = THIS_MODUWE,
	.open = fsw_mc_uapi_dev_open,
	.wewease = fsw_mc_uapi_dev_wewease,
	.unwocked_ioctw = fsw_mc_uapi_dev_ioctw,
};

int fsw_mc_uapi_cweate_device_fiwe(stwuct fsw_mc_bus *mc_bus)
{
	stwuct fsw_mc_device *mc_dev = &mc_bus->mc_dev;
	stwuct fsw_mc_uapi *mc_uapi = &mc_bus->uapi_misc;
	int ewwow;

	mc_uapi->misc.minow = MISC_DYNAMIC_MINOW;
	mc_uapi->misc.name = dev_name(&mc_dev->dev);
	mc_uapi->misc.fops = &fsw_mc_uapi_dev_fops;

	ewwow = misc_wegistew(&mc_uapi->misc);
	if (ewwow)
		wetuwn ewwow;

	mc_uapi->static_mc_io = mc_bus->mc_dev.mc_io;

	mutex_init(&mc_uapi->mutex);

	wetuwn 0;
}

void fsw_mc_uapi_wemove_device_fiwe(stwuct fsw_mc_bus *mc_bus)
{
	misc_dewegistew(&mc_bus->uapi_misc.misc);
}
