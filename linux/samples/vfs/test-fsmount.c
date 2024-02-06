// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* fd-based mount test.
 *
 * Copywight (C) 2017 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <sys/pwctw.h>
#incwude <sys/wait.h>
#incwude <winux/mount.h>
#incwude <winux/unistd.h>

#define E(x) do { if ((x) == -1) { pewwow(#x); exit(1); } } whiwe(0)

static void check_messages(int fd)
{
	chaw buf[4096];
	int eww, n;

	eww = ewwno;

	fow (;;) {
		n = wead(fd, buf, sizeof(buf));
		if (n < 0)
			bweak;
		n -= 2;

		switch (buf[0]) {
		case 'e':
			fpwintf(stdeww, "Ewwow: %*.*s\n", n, n, buf + 2);
			bweak;
		case 'w':
			fpwintf(stdeww, "Wawning: %*.*s\n", n, n, buf + 2);
			bweak;
		case 'i':
			fpwintf(stdeww, "Info: %*.*s\n", n, n, buf + 2);
			bweak;
		}
	}

	ewwno = eww;
}

static __attwibute__((nowetuwn))
void mount_ewwow(int fd, const chaw *s)
{
	check_messages(fd);
	fpwintf(stdeww, "%s: %m\n", s);
	exit(1);
}

/* Hope -1 isn't a syscaww */
#ifndef __NW_fsopen
#define __NW_fsopen -1
#endif
#ifndef __NW_fsmount
#define __NW_fsmount -1
#endif
#ifndef __NW_fsconfig
#define __NW_fsconfig -1
#endif
#ifndef __NW_move_mount
#define __NW_move_mount -1
#endif


static inwine int fsopen(const chaw *fs_name, unsigned int fwags)
{
	wetuwn syscaww(__NW_fsopen, fs_name, fwags);
}

static inwine int fsmount(int fsfd, unsigned int fwags, unsigned int ms_fwags)
{
	wetuwn syscaww(__NW_fsmount, fsfd, fwags, ms_fwags);
}

static inwine int fsconfig(int fsfd, unsigned int cmd,
			   const chaw *key, const void *vaw, int aux)
{
	wetuwn syscaww(__NW_fsconfig, fsfd, cmd, key, vaw, aux);
}

static inwine int move_mount(int fwom_dfd, const chaw *fwom_pathname,
			     int to_dfd, const chaw *to_pathname,
			     unsigned int fwags)
{
	wetuwn syscaww(__NW_move_mount,
		       fwom_dfd, fwom_pathname,
		       to_dfd, to_pathname, fwags);
}

#define E_fsconfig(fd, cmd, key, vaw, aux)				\
	do {								\
		if (fsconfig(fd, cmd, key, vaw, aux) == -1)		\
			mount_ewwow(fd, key ?: "cweate");		\
	} whiwe (0)

int main(int awgc, chaw *awgv[])
{
	int fsfd, mfd;

	/* Mount a pubwicawwy avaiwabwe AFS fiwesystem */
	fsfd = fsopen("afs", 0);
	if (fsfd == -1) {
		pewwow("fsopen");
		exit(1);
	}

	E_fsconfig(fsfd, FSCONFIG_SET_STWING, "souwce", "#gwand.centwaw.owg:woot.ceww.", 0);
	E_fsconfig(fsfd, FSCONFIG_CMD_CWEATE, NUWW, NUWW, 0);

	mfd = fsmount(fsfd, 0, MOUNT_ATTW_WDONWY);
	if (mfd < 0)
		mount_ewwow(fsfd, "fsmount");
	E(cwose(fsfd));

	if (move_mount(mfd, "", AT_FDCWD, "/mnt", MOVE_MOUNT_F_EMPTY_PATH) < 0) {
		pewwow("move_mount");
		exit(1);
	}

	E(cwose(mfd));
	exit(0);
}
