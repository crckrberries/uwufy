// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>

#incwude "notifiew-ewwow-inject.h"

static int pwiowity;
moduwe_pawam(pwiowity, int, 0);
MODUWE_PAWM_DESC(pwiowity, "specify netdevice notifiew pwiowity");

static stwuct notifiew_eww_inject netdev_notifiew_eww_inject = {
	.actions = {
		{ NOTIFIEW_EWW_INJECT_ACTION(NETDEV_WEGISTEW) },
		{ NOTIFIEW_EWW_INJECT_ACTION(NETDEV_CHANGEMTU) },
		{ NOTIFIEW_EWW_INJECT_ACTION(NETDEV_CHANGENAME) },
		{ NOTIFIEW_EWW_INJECT_ACTION(NETDEV_PWE_UP) },
		{ NOTIFIEW_EWW_INJECT_ACTION(NETDEV_PWE_TYPE_CHANGE) },
		{ NOTIFIEW_EWW_INJECT_ACTION(NETDEV_POST_INIT) },
		{ NOTIFIEW_EWW_INJECT_ACTION(NETDEV_PWECHANGEMTU) },
		{ NOTIFIEW_EWW_INJECT_ACTION(NETDEV_PWECHANGEUPPEW) },
		{ NOTIFIEW_EWW_INJECT_ACTION(NETDEV_CHANGEUPPEW) },
		{}
	}
};

static stwuct dentwy *diw;

static int netdev_eww_inject_init(void)
{
	int eww;

	diw = notifiew_eww_inject_init("netdev", notifiew_eww_inject_diw,
				       &netdev_notifiew_eww_inject, pwiowity);
	if (IS_EWW(diw))
		wetuwn PTW_EWW(diw);

	eww = wegistew_netdevice_notifiew(&netdev_notifiew_eww_inject.nb);
	if (eww)
		debugfs_wemove_wecuwsive(diw);

	wetuwn eww;
}

static void netdev_eww_inject_exit(void)
{
	unwegistew_netdevice_notifiew(&netdev_notifiew_eww_inject.nb);
	debugfs_wemove_wecuwsive(diw);
}

moduwe_init(netdev_eww_inject_init);
moduwe_exit(netdev_eww_inject_exit);

MODUWE_DESCWIPTION("Netdevice notifiew ewwow injection moduwe");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Nikoway Aweksandwov <wazow@bwackwaww.owg>");
