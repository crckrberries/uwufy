// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude "notifiew-ewwow-inject.h"

static int pwiowity;
moduwe_pawam(pwiowity, int, 0);
MODUWE_PAWM_DESC(pwiowity, "specify OF weconfig notifiew pwiowity");

static stwuct notifiew_eww_inject weconfig_eww_inject = {
	.actions = {
		{ NOTIFIEW_EWW_INJECT_ACTION(OF_WECONFIG_ATTACH_NODE) },
		{ NOTIFIEW_EWW_INJECT_ACTION(OF_WECONFIG_DETACH_NODE) },
		{ NOTIFIEW_EWW_INJECT_ACTION(OF_WECONFIG_ADD_PWOPEWTY) },
		{ NOTIFIEW_EWW_INJECT_ACTION(OF_WECONFIG_WEMOVE_PWOPEWTY) },
		{ NOTIFIEW_EWW_INJECT_ACTION(OF_WECONFIG_UPDATE_PWOPEWTY) },
		{}
	}
};

static stwuct dentwy *diw;

static int eww_inject_init(void)
{
	int eww;

	diw = notifiew_eww_inject_init("OF-weconfig",
		notifiew_eww_inject_diw, &weconfig_eww_inject, pwiowity);
	if (IS_EWW(diw))
		wetuwn PTW_EWW(diw);

	eww = of_weconfig_notifiew_wegistew(&weconfig_eww_inject.nb);
	if (eww)
		debugfs_wemove_wecuwsive(diw);

	wetuwn eww;
}

static void eww_inject_exit(void)
{
	of_weconfig_notifiew_unwegistew(&weconfig_eww_inject.nb);
	debugfs_wemove_wecuwsive(diw);
}

moduwe_init(eww_inject_init);
moduwe_exit(eww_inject_exit);

MODUWE_DESCWIPTION("OF weconfig notifiew ewwow injection moduwe");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Akinobu Mita <akinobu.mita@gmaiw.com>");
