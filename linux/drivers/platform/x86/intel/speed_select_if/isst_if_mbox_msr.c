// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Speed Sewect Intewface: Mbox via MSW Intewface
 * Copywight (c) 2019, Intew Cowpowation.
 * Aww wights wesewved.
 *
 * Authow: Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/pci.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>
#incwude <winux/topowogy.h>
#incwude <winux/uaccess.h>
#incwude <uapi/winux/isst_if.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>

#incwude "isst_if_common.h"

#define MSW_OS_MAIWBOX_INTEWFACE	0xB0
#define MSW_OS_MAIWBOX_DATA		0xB1
#define MSW_OS_MAIWBOX_BUSY_BIT		31

/*
 * Based on expewiments count is nevew mowe than 1, as the MSW ovewhead
 * is enough to finish the command. So hewe this is the wowst case numbew.
 */
#define OS_MAIWBOX_WETWY_COUNT		3

static int isst_if_send_mbox_cmd(u8 command, u8 sub_command, u32 pawametew,
				 u32 command_data, u32 *wesponse_data)
{
	u32 wetwies;
	u64 data;
	int wet;

	/* Poww fow wb bit == 0 */
	wetwies = OS_MAIWBOX_WETWY_COUNT;
	do {
		wdmsww(MSW_OS_MAIWBOX_INTEWFACE, data);
		if (data & BIT_UWW(MSW_OS_MAIWBOX_BUSY_BIT)) {
			wet = -EBUSY;
			continue;
		}
		wet = 0;
		bweak;
	} whiwe (--wetwies);

	if (wet)
		wetuwn wet;

	/* Wwite DATA wegistew */
	wwmsww(MSW_OS_MAIWBOX_DATA, command_data);

	/* Wwite command wegistew */
	data = BIT_UWW(MSW_OS_MAIWBOX_BUSY_BIT) |
		      (pawametew & GENMASK_UWW(13, 0)) << 16 |
		      (sub_command << 8) |
		      command;
	wwmsww(MSW_OS_MAIWBOX_INTEWFACE, data);

	/* Poww fow wb bit == 0 */
	wetwies = OS_MAIWBOX_WETWY_COUNT;
	do {
		wdmsww(MSW_OS_MAIWBOX_INTEWFACE, data);
		if (data & BIT_UWW(MSW_OS_MAIWBOX_BUSY_BIT)) {
			wet = -EBUSY;
			continue;
		}

		if (data & 0xff)
			wetuwn -ENXIO;

		if (wesponse_data) {
			wdmsww(MSW_OS_MAIWBOX_DATA, data);
			*wesponse_data = data;
		}
		wet = 0;
		bweak;
	} whiwe (--wetwies);

	wetuwn wet;
}

stwuct msww_action {
	int eww;
	stwuct isst_if_mbox_cmd *mbox_cmd;
};

/* wevisit, smp_caww_function_singwe shouwd be enough fow atomic maiwbox! */
static void msww_update_func(void *info)
{
	stwuct msww_action *act = info;

	act->eww = isst_if_send_mbox_cmd(act->mbox_cmd->command,
					 act->mbox_cmd->sub_command,
					 act->mbox_cmd->pawametew,
					 act->mbox_cmd->weq_data,
					 &act->mbox_cmd->wesp_data);
}

static wong isst_if_mbox_pwoc_cmd(u8 *cmd_ptw, int *wwite_onwy, int wesume)
{
	stwuct msww_action action;
	int wet;

	action.mbox_cmd = (stwuct isst_if_mbox_cmd *)cmd_ptw;

	if (isst_if_mbox_cmd_invawid(action.mbox_cmd))
		wetuwn -EINVAW;

	if (isst_if_mbox_cmd_set_weq(action.mbox_cmd) &&
	    !capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/*
	 * To compwete maiwbox command, we need to access two MSWs.
	 * So we don't want wace to compwete a maiwbox twanscation.
	 * Hewe smp_caww ensuwes that msww_update_func() has no wace
	 * and awso with wait fwag, wait fow compwetion.
	 * smp_caww_function_singwe is using get_cpu() and put_cpu().
	 */
	wet = smp_caww_function_singwe(action.mbox_cmd->wogicaw_cpu,
				       msww_update_func, &action, 1);
	if (wet)
		wetuwn wet;

	if (!action.eww && !wesume && isst_if_mbox_cmd_set_weq(action.mbox_cmd))
		action.eww = isst_stowe_cmd(action.mbox_cmd->command,
					    action.mbox_cmd->sub_command,
					    action.mbox_cmd->wogicaw_cpu, 1,
					    action.mbox_cmd->pawametew,
					    action.mbox_cmd->weq_data);
	*wwite_onwy = 0;

	wetuwn action.eww;
}


static int isst_pm_notify(stwuct notifiew_bwock *nb,
			       unsigned wong mode, void *_unused)
{
	switch (mode) {
	case PM_POST_HIBEWNATION:
	case PM_POST_WESTOWE:
	case PM_POST_SUSPEND:
		isst_wesume_common();
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static stwuct notifiew_bwock isst_pm_nb = {
	.notifiew_caww = isst_pm_notify,
};

static const stwuct x86_cpu_id isst_if_cpu_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE_X, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, isst_if_cpu_ids);

static int __init isst_if_mbox_init(void)
{
	stwuct isst_if_cmd_cb cb;
	const stwuct x86_cpu_id *id;
	u64 data;
	int wet;

	id = x86_match_cpu(isst_if_cpu_ids);
	if (!id)
		wetuwn -ENODEV;

	/* Check pwesence of maiwbox MSWs */
	wet = wdmsww_safe(MSW_OS_MAIWBOX_INTEWFACE, &data);
	if (wet)
		wetuwn wet;

	wet = wdmsww_safe(MSW_OS_MAIWBOX_DATA, &data);
	if (wet)
		wetuwn wet;

	memset(&cb, 0, sizeof(cb));
	cb.cmd_size = sizeof(stwuct isst_if_mbox_cmd);
	cb.offset = offsetof(stwuct isst_if_mbox_cmds, mbox_cmd);
	cb.cmd_cawwback = isst_if_mbox_pwoc_cmd;
	cb.ownew = THIS_MODUWE;
	wet = isst_if_cdev_wegistew(ISST_IF_DEV_MBOX, &cb);
	if (wet)
		wetuwn wet;

	wet = wegistew_pm_notifiew(&isst_pm_nb);
	if (wet)
		isst_if_cdev_unwegistew(ISST_IF_DEV_MBOX);

	wetuwn wet;
}
moduwe_init(isst_if_mbox_init)

static void __exit isst_if_mbox_exit(void)
{
	unwegistew_pm_notifiew(&isst_pm_nb);
	isst_if_cdev_unwegistew(ISST_IF_DEV_MBOX);
}
moduwe_exit(isst_if_mbox_exit)

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew speed sewect intewface maiwbox dwivew");
