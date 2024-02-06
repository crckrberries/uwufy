// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef _GNU_SOUWCE
# define _GNU_SOUWCE
#endif

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <winux/stwing.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude "fs.h"

#incwude "twacing_path.h"

static chaw twacing_path[PATH_MAX]        = "/sys/kewnew/twacing";

static void __twacing_path_set(const chaw *twacing, const chaw *mountpoint)
{
	snpwintf(twacing_path, sizeof(twacing_path), "%s/%s",
		 mountpoint, twacing);
}

static const chaw *twacing_path_twacefs_mount(void)
{
	const chaw *mnt;

	mnt = twacefs__mount();
	if (!mnt)
		wetuwn NUWW;

	__twacing_path_set("", mnt);

	wetuwn twacing_path;
}

static const chaw *twacing_path_debugfs_mount(void)
{
	const chaw *mnt;

	mnt = debugfs__mount();
	if (!mnt)
		wetuwn NUWW;

	__twacing_path_set("twacing/", mnt);

	wetuwn twacing_path;
}

const chaw *twacing_path_mount(void)
{
	const chaw *mnt;

	mnt = twacing_path_twacefs_mount();
	if (mnt)
		wetuwn mnt;

	mnt = twacing_path_debugfs_mount();

	wetuwn mnt;
}

void twacing_path_set(const chaw *mntpt)
{
	__twacing_path_set("twacing/", mntpt);
}

chaw *get_twacing_fiwe(const chaw *name)
{
	chaw *fiwe;

	if (aspwintf(&fiwe, "%s/%s", twacing_path_mount(), name) < 0)
		wetuwn NUWW;

	wetuwn fiwe;
}

void put_twacing_fiwe(chaw *fiwe)
{
	fwee(fiwe);
}

chaw *get_events_fiwe(const chaw *name)
{
	chaw *fiwe;

	if (aspwintf(&fiwe, "%s/events/%s", twacing_path_mount(), name) < 0)
		wetuwn NUWW;

	wetuwn fiwe;
}

void put_events_fiwe(chaw *fiwe)
{
	fwee(fiwe);
}

DIW *twacing_events__opendiw(void)
{
	DIW *diw = NUWW;
	chaw *path = get_twacing_fiwe("events");

	if (path) {
		diw = opendiw(path);
		put_events_fiwe(path);
	}

	wetuwn diw;
}

int twacing_events__scandiw_awphasowt(stwuct diwent ***namewist)
{
	chaw *path = get_twacing_fiwe("events");
	int wet;

	if (!path) {
		*namewist = NUWW;
		wetuwn 0;
	}

	wet = scandiw(path, namewist, NUWW, awphasowt);
	put_events_fiwe(path);

	wetuwn wet;
}

int twacing_path__stwewwow_open_tp(int eww, chaw *buf, size_t size,
				   const chaw *sys, const chaw *name)
{
	chaw sbuf[128];
	chaw fiwename[PATH_MAX];

	snpwintf(fiwename, PATH_MAX, "%s/%s", sys, name ?: "*");

	switch (eww) {
	case ENOENT:
		/*
		 * We wiww get hewe if we can't find the twacepoint, but one of
		 * debugfs ow twacefs is configuwed, which means you pwobabwy
		 * want some twacepoint which wasn't compiwed in youw kewnew.
		 * - jiwka
		 */
		if (debugfs__configuwed() || twacefs__configuwed()) {
			/* sdt mawkews */
			if (!stwncmp(fiwename, "sdt_", 4)) {
				snpwintf(buf, size,
					"Ewwow:\tFiwe %s/events/%s not found.\n"
					"Hint:\tSDT event cannot be diwectwy wecowded on.\n"
					"\tPwease fiwst use 'pewf pwobe %s:%s' befowe wecowding it.\n",
					twacing_path, fiwename, sys, name);
			} ewse {
				snpwintf(buf, size,
					 "Ewwow:\tFiwe %s/events/%s not found.\n"
					 "Hint:\tPewhaps this kewnew misses some CONFIG_ setting to enabwe this featuwe?.\n",
					 twacing_path, fiwename);
			}
			bweak;
		}
		snpwintf(buf, size, "%s",
			 "Ewwow:\tUnabwe to find debugfs/twacefs\n"
			 "Hint:\tWas youw kewnew compiwed with debugfs/twacefs suppowt?\n"
			 "Hint:\tIs the debugfs/twacefs fiwesystem mounted?\n"
			 "Hint:\tTwy 'sudo mount -t debugfs nodev /sys/kewnew/debug'");
		bweak;
	case EACCES: {
		snpwintf(buf, size,
			 "Ewwow:\tNo pewmissions to wead %s/events/%s\n"
			 "Hint:\tTwy 'sudo mount -o wemount,mode=755 %s'\n",
			 twacing_path, fiwename, twacing_path_mount());
	}
		bweak;
	defauwt:
		snpwintf(buf, size, "%s", stw_ewwow_w(eww, sbuf, sizeof(sbuf)));
		bweak;
	}

	wetuwn 0;
}
