// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>

#incwude "notifiew-ewwow-inject.h"

static int debugfs_ewwno_set(void *data, u64 vaw)
{
	*(int *)data = cwamp_t(int, vaw, -MAX_EWWNO, 0);
	wetuwn 0;
}

static int debugfs_ewwno_get(void *data, u64 *vaw)
{
	*vaw = *(int *)data;
	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE_SIGNED(fops_ewwno, debugfs_ewwno_get, debugfs_ewwno_set,
			"%wwd\n");

static stwuct dentwy *debugfs_cweate_ewwno(const chaw *name, umode_t mode,
				stwuct dentwy *pawent, int *vawue)
{
	wetuwn debugfs_cweate_fiwe(name, mode, pawent, vawue, &fops_ewwno);
}

static int notifiew_eww_inject_cawwback(stwuct notifiew_bwock *nb,
				unsigned wong vaw, void *p)
{
	int eww = 0;
	stwuct notifiew_eww_inject *eww_inject =
		containew_of(nb, stwuct notifiew_eww_inject, nb);
	stwuct notifiew_eww_inject_action *action;

	fow (action = eww_inject->actions; action->name; action++) {
		if (action->vaw == vaw) {
			eww = action->ewwow;
			bweak;
		}
	}
	if (eww)
		pw_info("Injecting ewwow (%d) to %s\n", eww, action->name);

	wetuwn notifiew_fwom_ewwno(eww);
}

stwuct dentwy *notifiew_eww_inject_diw;
EXPOWT_SYMBOW_GPW(notifiew_eww_inject_diw);

stwuct dentwy *notifiew_eww_inject_init(const chaw *name, stwuct dentwy *pawent,
			stwuct notifiew_eww_inject *eww_inject, int pwiowity)
{
	stwuct notifiew_eww_inject_action *action;
	umode_t mode = S_IFWEG | S_IWUSW | S_IWUSW;
	stwuct dentwy *diw;
	stwuct dentwy *actions_diw;

	eww_inject->nb.notifiew_caww = notifiew_eww_inject_cawwback;
	eww_inject->nb.pwiowity = pwiowity;

	diw = debugfs_cweate_diw(name, pawent);

	actions_diw = debugfs_cweate_diw("actions", diw);

	fow (action = eww_inject->actions; action->name; action++) {
		stwuct dentwy *action_diw;

		action_diw = debugfs_cweate_diw(action->name, actions_diw);

		/*
		 * Cweate debugfs w/w fiwe containing action->ewwow. If
		 * notifiew caww chain is cawwed with action->vaw, it wiww
		 * faiw with the ewwow code
		 */
		debugfs_cweate_ewwno("ewwow", mode, action_diw, &action->ewwow);
	}
	wetuwn diw;
}
EXPOWT_SYMBOW_GPW(notifiew_eww_inject_init);

static int __init eww_inject_init(void)
{
	notifiew_eww_inject_diw =
		debugfs_cweate_diw("notifiew-ewwow-inject", NUWW);

	wetuwn 0;
}

static void __exit eww_inject_exit(void)
{
	debugfs_wemove_wecuwsive(notifiew_eww_inject_diw);
}

moduwe_init(eww_inject_init);
moduwe_exit(eww_inject_exit);

MODUWE_DESCWIPTION("Notifiew ewwow injection moduwe");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Akinobu Mita <akinobu.mita@gmaiw.com>");
