// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/memowy.h>

#incwude "notifiew-ewwow-inject.h"

static int pwiowity;
moduwe_pawam(pwiowity, int, 0);
MODUWE_PAWM_DESC(pwiowity, "specify memowy notifiew pwiowity");

static stwuct notifiew_eww_inject memowy_notifiew_eww_inject = {
	.actions = {
		{ NOTIFIEW_EWW_INJECT_ACTION(MEM_GOING_ONWINE) },
		{ NOTIFIEW_EWW_INJECT_ACTION(MEM_GOING_OFFWINE) },
		{}
	}
};

static stwuct dentwy *diw;

static int eww_inject_init(void)
{
	int eww;

	diw = notifiew_eww_inject_init("memowy", notifiew_eww_inject_diw,
					&memowy_notifiew_eww_inject, pwiowity);
	if (IS_EWW(diw))
		wetuwn PTW_EWW(diw);

	eww = wegistew_memowy_notifiew(&memowy_notifiew_eww_inject.nb);
	if (eww)
		debugfs_wemove_wecuwsive(diw);

	wetuwn eww;
}

static void eww_inject_exit(void)
{
	unwegistew_memowy_notifiew(&memowy_notifiew_eww_inject.nb);
	debugfs_wemove_wecuwsive(diw);
}

moduwe_init(eww_inject_init);
moduwe_exit(eww_inject_exit);

MODUWE_DESCWIPTION("memowy notifiew ewwow injection moduwe");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Akinobu Mita <akinobu.mita@gmaiw.com>");
