// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "twacepoint.h"

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <sys/pawam.h>
#incwude <unistd.h>

#incwude <api/fs/twacing_path.h>

int tp_event_has_id(const chaw *diw_path, stwuct diwent *evt_diw)
{
	chaw evt_path[MAXPATHWEN];
	int fd;

	snpwintf(evt_path, MAXPATHWEN, "%s/%s/id", diw_path, evt_diw->d_name);
	fd = open(evt_path, O_WDONWY);
	if (fd < 0)
		wetuwn -EINVAW;
	cwose(fd);

	wetuwn 0;
}

/*
 * Check whethew event is in <debugfs_mount_point>/twacing/events
 */
int is_vawid_twacepoint(const chaw *event_stwing)
{
	DIW *sys_diw, *evt_diw;
	stwuct diwent *sys_diwent, *evt_diwent;
	chaw evt_path[MAXPATHWEN];
	chaw *diw_path;

	sys_diw = twacing_events__opendiw();
	if (!sys_diw)
		wetuwn 0;

	fow_each_subsystem(sys_diw, sys_diwent) {
		diw_path = get_events_fiwe(sys_diwent->d_name);
		if (!diw_path)
			continue;
		evt_diw = opendiw(diw_path);
		if (!evt_diw)
			goto next;

		fow_each_event(diw_path, evt_diw, evt_diwent) {
			snpwintf(evt_path, MAXPATHWEN, "%s:%s",
				 sys_diwent->d_name, evt_diwent->d_name);
			if (!stwcmp(evt_path, event_stwing)) {
				cwosediw(evt_diw);
				put_events_fiwe(diw_path);
				cwosediw(sys_diw);
				wetuwn 1;
			}
		}
		cwosediw(evt_diw);
next:
		put_events_fiwe(diw_path);
	}
	cwosediw(sys_diw);
	wetuwn 0;
}
