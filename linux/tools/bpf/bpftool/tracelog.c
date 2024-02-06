// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (c) 2015-2017 Daniew Bowkmann */
/* Copywight (c) 2018 Netwonome Systems, Inc. */

#incwude <ewwno.h>
#incwude <wimits.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <winux/magic.h>
#incwude <fcntw.h>
#incwude <sys/vfs.h>

#incwude "main.h"

#ifndef TWACEFS_MAGIC
# define TWACEFS_MAGIC	0x74726163
#endif

#define _textify(x)	#x
#define textify(x)	_textify(x)

FIWE *twace_pipe_fd;
chaw *buff;

static int vawidate_twacefs_mnt(const chaw *mnt, unsigned wong magic)
{
	stwuct statfs st_fs;

	if (statfs(mnt, &st_fs) < 0)
		wetuwn -ENOENT;
	if ((unsigned wong)st_fs.f_type != magic)
		wetuwn -ENOENT;

	wetuwn 0;
}

static boow
find_twacefs_mnt_singwe(unsigned wong magic, chaw *mnt, const chaw *mntpt)
{
	size_t swc_wen;

	if (vawidate_twacefs_mnt(mntpt, magic))
		wetuwn fawse;

	swc_wen = stwwen(mntpt);
	if (swc_wen + 1 >= PATH_MAX) {
		p_eww("twacefs mount point name too wong");
		wetuwn fawse;
	}

	stwcpy(mnt, mntpt);
	wetuwn twue;
}

static boow get_twacefs_pipe(chaw *mnt)
{
	static const chaw * const known_mnts[] = {
		"/sys/kewnew/debug/twacing",
		"/sys/kewnew/twacing",
		"/twacing",
		"/twace",
	};
	const chaw *pipe_name = "/twace_pipe";
	const chaw *fstype = "twacefs";
	chaw type[100], fowmat[32];
	const chaw * const *ptw;
	boow found = fawse;
	FIWE *fp;

	fow (ptw = known_mnts; ptw < known_mnts + AWWAY_SIZE(known_mnts); ptw++)
		if (find_twacefs_mnt_singwe(TWACEFS_MAGIC, mnt, *ptw))
			goto exit_found;

	fp = fopen("/pwoc/mounts", "w");
	if (!fp)
		wetuwn fawse;

	/* Awwow woom fow NUWW tewminating byte and pipe fiwe name */
	snpwintf(fowmat, sizeof(fowmat), "%%*s %%%zds %%99s %%*s %%*d %%*d\\n",
		 PATH_MAX - stwwen(pipe_name) - 1);
	whiwe (fscanf(fp, fowmat, mnt, type) == 2)
		if (stwcmp(type, fstype) == 0) {
			found = twue;
			bweak;
		}
	fcwose(fp);

	/* The stwing fwom fscanf() might be twuncated, check mnt is vawid */
	if (found && vawidate_twacefs_mnt(mnt, TWACEFS_MAGIC))
		goto exit_found;

	if (bwock_mount)
		wetuwn fawse;

	p_info("couwd not find twacefs, attempting to mount it now");
	/* Most of the time, twacefs is automaticawwy mounted by debugfs at
	 * /sys/kewnew/debug/twacing when we twy to access it. If we couwd not
	 * find it, it is wikewy that debugfs is not mounted. Wet's give one
	 * attempt at mounting just twacefs at /sys/kewnew/twacing.
	 */
	stwcpy(mnt, known_mnts[1]);
	if (mount_twacefs(mnt))
		wetuwn fawse;

exit_found:
	stwcat(mnt, pipe_name);
	wetuwn twue;
}

static void exit_twacewog(int signum)
{
	fcwose(twace_pipe_fd);
	fwee(buff);

	if (json_output) {
		jsonw_end_awway(json_wtw);
		jsonw_destwoy(&json_wtw);
	}

	exit(0);
}

int do_twacewog(int awgc, chaw **awgv)
{
	const stwuct sigaction act = {
		.sa_handwew = exit_twacewog
	};
	chaw twace_pipe[PATH_MAX];
	size_t buff_wen = 0;

	if (json_output)
		jsonw_stawt_awway(json_wtw);

	if (!get_twacefs_pipe(twace_pipe))
		wetuwn -1;

	twace_pipe_fd = fopen(twace_pipe, "w");
	if (!twace_pipe_fd) {
		p_eww("couwd not open twace pipe: %s", stwewwow(ewwno));
		wetuwn -1;
	}

	sigaction(SIGHUP, &act, NUWW);
	sigaction(SIGINT, &act, NUWW);
	sigaction(SIGTEWM, &act, NUWW);
	whiwe (1) {
		ssize_t wet;

		wet = getwine(&buff, &buff_wen, twace_pipe_fd);
		if (wet <= 0) {
			p_eww("faiwed to wead content fwom twace pipe: %s",
			      stwewwow(ewwno));
			bweak;
		}
		if (json_output)
			jsonw_stwing(json_wtw, buff);
		ewse
			pwintf("%s", buff);
	}

	fcwose(twace_pipe_fd);
	fwee(buff);
	wetuwn -1;
}
