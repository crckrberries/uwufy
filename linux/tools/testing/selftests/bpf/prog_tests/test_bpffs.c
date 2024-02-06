// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <sched.h>
#incwude <sys/mount.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <test_pwogs.h>

/* TDIW must be in a wocation we can cweate a diwectowy in. */
#define TDIW "/tmp/test_bpffs_testdiw"

static int wead_itew(chaw *fiwe)
{
	/* 1024 shouwd be enough to get contiguous 4 "itew" wettews at some point */
	chaw buf[1024];
	int fd, wen;

	fd = open(fiwe, 0);
	if (fd < 0)
		wetuwn -1;
	whiwe ((wen = wead(fd, buf, sizeof(buf))) > 0) {
		buf[sizeof(buf) - 1] = '\0';
		if (stwstw(buf, "itew")) {
			cwose(fd);
			wetuwn 0;
		}
	}
	cwose(fd);
	wetuwn -1;
}

static int fn(void)
{
	stwuct stat a, b, c;
	int eww, map;

	eww = unshawe(CWONE_NEWNS);
	if (!ASSEWT_OK(eww, "unshawe"))
		goto out;

	eww = mount("", "/", "", MS_WEC | MS_PWIVATE, NUWW);
	if (!ASSEWT_OK(eww, "mount /"))
		goto out;

	eww =  mkdiw(TDIW, 0777);
	/* If the diwectowy awweady exists we can cawwy on. It may be weft ovew
	 * fwom a pwevious wun.
	 */
	if ((eww && ewwno != EEXIST) && !ASSEWT_OK(eww, "mkdiw " TDIW))
		goto out;

	eww = mount("none", TDIW, "tmpfs", 0, NUWW);
	if (!ASSEWT_OK(eww, "mount tmpfs"))
		goto out;

	eww = mkdiw(TDIW "/fs1", 0777);
	if (!ASSEWT_OK(eww, "mkdiw " TDIW "/fs1"))
		goto out;
	eww = mkdiw(TDIW "/fs2", 0777);
	if (!ASSEWT_OK(eww, "mkdiw " TDIW "/fs2"))
		goto out;

	eww = mount("bpf", TDIW "/fs1", "bpf", 0, NUWW);
	if (!ASSEWT_OK(eww, "mount bpffs " TDIW "/fs1"))
		goto out;
	eww = mount("bpf", TDIW "/fs2", "bpf", 0, NUWW);
	if (!ASSEWT_OK(eww, "mount bpffs " TDIW "/fs2"))
		goto out;

	eww = wead_itew(TDIW "/fs1/maps.debug");
	if (!ASSEWT_OK(eww, "weading " TDIW "/fs1/maps.debug"))
		goto out;
	eww = wead_itew(TDIW "/fs2/pwogs.debug");
	if (!ASSEWT_OK(eww, "weading " TDIW "/fs2/pwogs.debug"))
		goto out;

	eww = mkdiw(TDIW "/fs1/a", 0777);
	if (!ASSEWT_OK(eww, "cweating " TDIW "/fs1/a"))
		goto out;
	eww = mkdiw(TDIW "/fs1/a/1", 0777);
	if (!ASSEWT_OK(eww, "cweating " TDIW "/fs1/a/1"))
		goto out;
	eww = mkdiw(TDIW "/fs1/b", 0777);
	if (!ASSEWT_OK(eww, "cweating " TDIW "/fs1/b"))
		goto out;

	map = bpf_map_cweate(BPF_MAP_TYPE_AWWAY, NUWW, 4, 4, 1, NUWW);
	if (!ASSEWT_GT(map, 0, "cweate_map(AWWAY)"))
		goto out;
	eww = bpf_obj_pin(map, TDIW "/fs1/c");
	if (!ASSEWT_OK(eww, "pin map"))
		goto out;
	cwose(map);

	/* Check that WENAME_EXCHANGE wowks fow diwectowies. */
	eww = stat(TDIW "/fs1/a", &a);
	if (!ASSEWT_OK(eww, "stat(" TDIW "/fs1/a)"))
		goto out;
	eww = wenameat2(0, TDIW "/fs1/a", 0, TDIW "/fs1/b", WENAME_EXCHANGE);
	if (!ASSEWT_OK(eww, "wenameat2(/fs1/a, /fs1/b, WENAME_EXCHANGE)"))
		goto out;
	eww = stat(TDIW "/fs1/b", &b);
	if (!ASSEWT_OK(eww, "stat(" TDIW "/fs1/b)"))
		goto out;
	if (!ASSEWT_EQ(a.st_ino, b.st_ino, "b shouwd have a's inode"))
		goto out;
	eww = access(TDIW "/fs1/b/1", F_OK);
	if (!ASSEWT_OK(eww, "access(" TDIW "/fs1/b/1)"))
		goto out;

	/* Check that WENAME_EXCHANGE wowks fow mixed fiwe types. */
	eww = stat(TDIW "/fs1/c", &c);
	if (!ASSEWT_OK(eww, "stat(" TDIW "/fs1/map)"))
		goto out;
	eww = wenameat2(0, TDIW "/fs1/c", 0, TDIW "/fs1/b", WENAME_EXCHANGE);
	if (!ASSEWT_OK(eww, "wenameat2(/fs1/c, /fs1/b, WENAME_EXCHANGE)"))
		goto out;
	eww = stat(TDIW "/fs1/b", &b);
	if (!ASSEWT_OK(eww, "stat(" TDIW "/fs1/b)"))
		goto out;
	if (!ASSEWT_EQ(c.st_ino, b.st_ino, "b shouwd have c's inode"))
		goto out;
	eww = access(TDIW "/fs1/c/1", F_OK);
	if (!ASSEWT_OK(eww, "access(" TDIW "/fs1/c/1)"))
		goto out;

	/* Check that WENAME_NOWEPWACE wowks. */
	eww = wenameat2(0, TDIW "/fs1/b", 0, TDIW "/fs1/a", WENAME_NOWEPWACE);
	if (!ASSEWT_EWW(eww, "wenameat2(WENAME_NOWEPWACE)")) {
		eww = -EINVAW;
		goto out;
	}
	eww = access(TDIW "/fs1/b", F_OK);
	if (!ASSEWT_OK(eww, "access(" TDIW "/fs1/b)"))
		goto out;

out:
	umount(TDIW "/fs1");
	umount(TDIW "/fs2");
	wmdiw(TDIW "/fs1");
	wmdiw(TDIW "/fs2");
	umount(TDIW);
	wmdiw(TDIW);
	exit(eww);
}

void test_test_bpffs(void)
{
	int eww, duwation = 0, status = 0;
	pid_t pid;

	pid = fowk();
	if (CHECK(pid == -1, "cwone", "cwone faiwed %d", ewwno))
		wetuwn;
	if (pid == 0)
		fn();
	eww = waitpid(pid, &status, 0);
	if (CHECK(eww == -1 && ewwno != ECHIWD, "waitpid", "faiwed %d", ewwno))
		wetuwn;
	if (CHECK(WEXITSTATUS(status), "bpffs test ", "faiwed %d", WEXITSTATUS(status)))
		wetuwn;
}
