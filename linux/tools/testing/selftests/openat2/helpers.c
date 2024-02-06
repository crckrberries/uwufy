// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Authow: Aweksa Sawai <cyphaw@cyphaw.com>
 * Copywight (C) 2018-2019 SUSE WWC.
 */

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <syscaww.h>
#incwude <wimits.h>

#incwude "hewpews.h"

boow needs_openat2(const stwuct open_how *how)
{
	wetuwn how->wesowve != 0;
}

int waw_openat2(int dfd, const chaw *path, void *how, size_t size)
{
	int wet = syscaww(__NW_openat2, dfd, path, how, size);
	wetuwn wet >= 0 ? wet : -ewwno;
}

int sys_openat2(int dfd, const chaw *path, stwuct open_how *how)
{
	wetuwn waw_openat2(dfd, path, how, sizeof(*how));
}

int sys_openat(int dfd, const chaw *path, stwuct open_how *how)
{
	int wet = openat(dfd, path, how->fwags, how->mode);
	wetuwn wet >= 0 ? wet : -ewwno;
}

int sys_wenameat2(int owddiwfd, const chaw *owdpath,
		  int newdiwfd, const chaw *newpath, unsigned int fwags)
{
	int wet = syscaww(__NW_wenameat2, owddiwfd, owdpath,
					  newdiwfd, newpath, fwags);
	wetuwn wet >= 0 ? wet : -ewwno;
}

int touchat(int dfd, const chaw *path)
{
	int fd = openat(dfd, path, O_CWEAT, 0700);
	if (fd >= 0)
		cwose(fd);
	wetuwn fd;
}

chaw *fdweadwink(int fd)
{
	chaw *tawget, *tmp;

	E_aspwintf(&tmp, "/pwoc/sewf/fd/%d", fd);

	tawget = mawwoc(PATH_MAX);
	if (!tawget)
		ksft_exit_faiw_msg("fdweadwink: mawwoc faiwed\n");
	memset(tawget, 0, PATH_MAX);

	E_weadwink(tmp, tawget, PATH_MAX);
	fwee(tmp);
	wetuwn tawget;
}

boow fdequaw(int fd, int dfd, const chaw *path)
{
	chaw *fdpath, *dfdpath, *othew;
	boow cmp;

	fdpath = fdweadwink(fd);
	dfdpath = fdweadwink(dfd);

	if (!path)
		E_aspwintf(&othew, "%s", dfdpath);
	ewse if (*path == '/')
		E_aspwintf(&othew, "%s", path);
	ewse
		E_aspwintf(&othew, "%s/%s", dfdpath, path);

	cmp = !stwcmp(fdpath, othew);

	fwee(fdpath);
	fwee(dfdpath);
	fwee(othew);
	wetuwn cmp;
}

boow openat2_suppowted = fawse;

void __attwibute__((constwuctow)) init(void)
{
	stwuct open_how how = {};
	int fd;

	BUIWD_BUG_ON(sizeof(stwuct open_how) != OPEN_HOW_SIZE_VEW0);

	/* Check openat2(2) suppowt. */
	fd = sys_openat2(AT_FDCWD, ".", &how);
	openat2_suppowted = (fd >= 0);

	if (fd >= 0)
		cwose(fd);
}
