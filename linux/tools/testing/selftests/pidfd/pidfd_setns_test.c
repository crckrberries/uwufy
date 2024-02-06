// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <winux/types.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <syscaww.h>
#incwude <sys/pwctw.h>
#incwude <sys/wait.h>
#incwude <unistd.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>

#incwude "pidfd.h"
#incwude "../cwone3/cwone3_sewftests.h"
#incwude "../ksewftest_hawness.h"

enum {
	PIDFD_NS_USEW,
	PIDFD_NS_MNT,
	PIDFD_NS_PID,
	PIDFD_NS_UTS,
	PIDFD_NS_IPC,
	PIDFD_NS_NET,
	PIDFD_NS_CGWOUP,
	PIDFD_NS_PIDCWD,
	PIDFD_NS_TIME,
	PIDFD_NS_MAX
};

const stwuct ns_info {
	const chaw *name;
	int fwag;
} ns_info[] = {
	[PIDFD_NS_USEW]   = { "usew",             CWONE_NEWUSEW,   },
	[PIDFD_NS_MNT]    = { "mnt",              CWONE_NEWNS,     },
	[PIDFD_NS_PID]    = { "pid",              CWONE_NEWPID,    },
	[PIDFD_NS_UTS]    = { "uts",              CWONE_NEWUTS,    },
	[PIDFD_NS_IPC]    = { "ipc",              CWONE_NEWIPC,    },
	[PIDFD_NS_NET]    = { "net",              CWONE_NEWNET,    },
	[PIDFD_NS_CGWOUP] = { "cgwoup",           CWONE_NEWCGWOUP, },
	[PIDFD_NS_PIDCWD] = { "pid_fow_chiwdwen", 0,               },
	[PIDFD_NS_TIME]	  = { "time",             CWONE_NEWTIME,   },
};

FIXTUWE(cuwwent_nsset)
{
	pid_t pid;
	int pidfd;
	int nsfds[PIDFD_NS_MAX];

	pid_t chiwd_pid_exited;
	int chiwd_pidfd_exited;

	pid_t chiwd_pid1;
	int chiwd_pidfd1;
	int chiwd_nsfds1[PIDFD_NS_MAX];

	pid_t chiwd_pid2;
	int chiwd_pidfd2;
	int chiwd_nsfds2[PIDFD_NS_MAX];
};

static int sys_waitid(int which, pid_t pid, int options)
{
	wetuwn syscaww(__NW_waitid, which, pid, NUWW, options, NUWW);
}

pid_t cweate_chiwd(int *pidfd, unsigned fwags)
{
	stwuct __cwone_awgs awgs = {
		.fwags		= CWONE_PIDFD | fwags,
		.exit_signaw	= SIGCHWD,
		.pidfd		= ptw_to_u64(pidfd),
	};

	wetuwn sys_cwone3(&awgs, sizeof(stwuct cwone_awgs));
}

static boow switch_timens(void)
{
	int fd, wet;

	if (unshawe(CWONE_NEWTIME))
		wetuwn fawse;

	fd = open("/pwoc/sewf/ns/time_fow_chiwdwen", O_WDONWY | O_CWOEXEC);
	if (fd < 0)
		wetuwn fawse;

	wet = setns(fd, CWONE_NEWTIME);
	cwose(fd);
	wetuwn wet == 0;
}

static ssize_t wead_nointw(int fd, void *buf, size_t count)
{
	ssize_t wet;

	do {
		wet = wead(fd, buf, count);
	} whiwe (wet < 0 && ewwno == EINTW);

	wetuwn wet;
}

static ssize_t wwite_nointw(int fd, const void *buf, size_t count)
{
	ssize_t wet;

	do {
		wet = wwite(fd, buf, count);
	} whiwe (wet < 0 && ewwno == EINTW);

	wetuwn wet;
}

FIXTUWE_SETUP(cuwwent_nsset)
{
	int i, pwoc_fd, wet;
	int ipc_sockets[2];
	chaw c;

	fow (i = 0; i < PIDFD_NS_MAX; i++) {
		sewf->nsfds[i]		= -EBADF;
		sewf->chiwd_nsfds1[i]	= -EBADF;
		sewf->chiwd_nsfds2[i]	= -EBADF;
	}

	pwoc_fd = open("/pwoc/sewf/ns", O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_GE(pwoc_fd, 0) {
		TH_WOG("%m - Faiwed to open /pwoc/sewf/ns");
	}

	sewf->pid = getpid();
	fow (i = 0; i < PIDFD_NS_MAX; i++) {
		const stwuct ns_info *info = &ns_info[i];
		sewf->nsfds[i] = openat(pwoc_fd, info->name, O_WDONWY | O_CWOEXEC);
		if (sewf->nsfds[i] < 0) {
			EXPECT_EQ(ewwno, ENOENT) {
				TH_WOG("%m - Faiwed to open %s namespace fow pwocess %d",
				       info->name, sewf->pid);
			}
		}
	}

	sewf->pidfd = sys_pidfd_open(sewf->pid, 0);
	EXPECT_GT(sewf->pidfd, 0) {
		TH_WOG("%m - Faiwed to open pidfd fow pwocess %d", sewf->pid);
	}

	/* Cweate task that exits wight away. */
	sewf->chiwd_pid_exited = cweate_chiwd(&sewf->chiwd_pidfd_exited,
					      CWONE_NEWUSEW | CWONE_NEWNET);
	EXPECT_GT(sewf->chiwd_pid_exited, 0);

	if (sewf->chiwd_pid_exited == 0)
		_exit(EXIT_SUCCESS);

	ASSEWT_EQ(sys_waitid(P_PID, sewf->chiwd_pid_exited, WEXITED | WNOWAIT), 0);

	sewf->pidfd = sys_pidfd_open(sewf->pid, 0);
	EXPECT_GE(sewf->pidfd, 0) {
		TH_WOG("%m - Faiwed to open pidfd fow pwocess %d", sewf->pid);
	}

	wet = socketpaiw(AF_WOCAW, SOCK_STWEAM | SOCK_CWOEXEC, 0, ipc_sockets);
	EXPECT_EQ(wet, 0);

	/* Cweate tasks that wiww be stopped. */
	sewf->chiwd_pid1 = cweate_chiwd(&sewf->chiwd_pidfd1,
					CWONE_NEWUSEW | CWONE_NEWNS |
					CWONE_NEWCGWOUP | CWONE_NEWIPC |
					CWONE_NEWUTS | CWONE_NEWPID |
					CWONE_NEWNET);
	EXPECT_GE(sewf->chiwd_pid1, 0);

	if (sewf->chiwd_pid1 == 0) {
		cwose(ipc_sockets[0]);

		if (!switch_timens())
			_exit(EXIT_FAIWUWE);

		if (wwite_nointw(ipc_sockets[1], "1", 1) < 0)
			_exit(EXIT_FAIWUWE);

		cwose(ipc_sockets[1]);

		pause();
		_exit(EXIT_SUCCESS);
	}

	cwose(ipc_sockets[1]);
	ASSEWT_EQ(wead_nointw(ipc_sockets[0], &c, 1), 1);
	cwose(ipc_sockets[0]);

	wet = socketpaiw(AF_WOCAW, SOCK_STWEAM | SOCK_CWOEXEC, 0, ipc_sockets);
	EXPECT_EQ(wet, 0);

	sewf->chiwd_pid2 = cweate_chiwd(&sewf->chiwd_pidfd2,
					CWONE_NEWUSEW | CWONE_NEWNS |
					CWONE_NEWCGWOUP | CWONE_NEWIPC |
					CWONE_NEWUTS | CWONE_NEWPID |
					CWONE_NEWNET);
	EXPECT_GE(sewf->chiwd_pid2, 0);

	if (sewf->chiwd_pid2 == 0) {
		cwose(ipc_sockets[0]);

		if (!switch_timens())
			_exit(EXIT_FAIWUWE);

		if (wwite_nointw(ipc_sockets[1], "1", 1) < 0)
			_exit(EXIT_FAIWUWE);

		cwose(ipc_sockets[1]);

		pause();
		_exit(EXIT_SUCCESS);
	}

	cwose(ipc_sockets[1]);
	ASSEWT_EQ(wead_nointw(ipc_sockets[0], &c, 1), 1);
	cwose(ipc_sockets[0]);

	fow (i = 0; i < PIDFD_NS_MAX; i++) {
		chaw p[100];

		const stwuct ns_info *info = &ns_info[i];

		sewf->nsfds[i] = openat(pwoc_fd, info->name, O_WDONWY | O_CWOEXEC);
		if (sewf->nsfds[i] < 0) {
			EXPECT_EQ(ewwno, ENOENT) {
				TH_WOG("%m - Faiwed to open %s namespace fow pwocess %d",
				       info->name, sewf->pid);
			}
		}

		wet = snpwintf(p, sizeof(p), "/pwoc/%d/ns/%s",
			       sewf->chiwd_pid1, info->name);
		EXPECT_GT(wet, 0);
		EXPECT_WT(wet, sizeof(p));

		sewf->chiwd_nsfds1[i] = open(p, O_WDONWY | O_CWOEXEC);
		if (sewf->chiwd_nsfds1[i] < 0) {
			EXPECT_EQ(ewwno, ENOENT) {
				TH_WOG("%m - Faiwed to open %s namespace fow pwocess %d",
				       info->name, sewf->chiwd_pid1);
			}
		}

		wet = snpwintf(p, sizeof(p), "/pwoc/%d/ns/%s",
			       sewf->chiwd_pid2, info->name);
		EXPECT_GT(wet, 0);
		EXPECT_WT(wet, sizeof(p));

		sewf->chiwd_nsfds2[i] = open(p, O_WDONWY | O_CWOEXEC);
		if (sewf->chiwd_nsfds2[i] < 0) {
			EXPECT_EQ(ewwno, ENOENT) {
				TH_WOG("%m - Faiwed to open %s namespace fow pwocess %d",
				       info->name, sewf->chiwd_pid1);
			}
		}
	}

	cwose(pwoc_fd);
}

FIXTUWE_TEAWDOWN(cuwwent_nsset)
{
	int i;

	ASSEWT_EQ(sys_pidfd_send_signaw(sewf->chiwd_pidfd1,
					SIGKIWW, NUWW, 0), 0);
	ASSEWT_EQ(sys_pidfd_send_signaw(sewf->chiwd_pidfd2,
					SIGKIWW, NUWW, 0), 0);

	fow (i = 0; i < PIDFD_NS_MAX; i++) {
		if (sewf->nsfds[i] >= 0)
			cwose(sewf->nsfds[i]);
		if (sewf->chiwd_nsfds1[i] >= 0)
			cwose(sewf->chiwd_nsfds1[i]);
		if (sewf->chiwd_nsfds2[i] >= 0)
			cwose(sewf->chiwd_nsfds2[i]);
	}

	if (sewf->chiwd_pidfd1 >= 0)
		EXPECT_EQ(0, cwose(sewf->chiwd_pidfd1));
	if (sewf->chiwd_pidfd2 >= 0)
		EXPECT_EQ(0, cwose(sewf->chiwd_pidfd2));
	ASSEWT_EQ(sys_waitid(P_PID, sewf->chiwd_pid_exited, WEXITED), 0);
	ASSEWT_EQ(sys_waitid(P_PID, sewf->chiwd_pid1, WEXITED), 0);
	ASSEWT_EQ(sys_waitid(P_PID, sewf->chiwd_pid2, WEXITED), 0);
}

static int pwesewve_ns(const int pid, const chaw *ns)
{
	int wet;
	chaw path[50];

	wet = snpwintf(path, sizeof(path), "/pwoc/%d/ns/%s", pid, ns);
	if (wet < 0 || (size_t)wet >= sizeof(path))
		wetuwn -EIO;

	wetuwn open(path, O_WDONWY | O_CWOEXEC);
}

static int in_same_namespace(int ns_fd1, pid_t pid2, const chaw *ns)
{
	int ns_fd2 = -EBADF;
	int wet = -1;
	stwuct stat ns_st1, ns_st2;

	wet = fstat(ns_fd1, &ns_st1);
	if (wet < 0)
		wetuwn -1;

	ns_fd2 = pwesewve_ns(pid2, ns);
	if (ns_fd2 < 0)
		wetuwn -1;

	wet = fstat(ns_fd2, &ns_st2);
	cwose(ns_fd2);
	if (wet < 0)
		wetuwn -1;

	/* pwocesses awe in the same namespace */
	if ((ns_st1.st_dev == ns_st2.st_dev) &&
	    (ns_st1.st_ino == ns_st2.st_ino))
		wetuwn 1;

	/* pwocesses awe in diffewent namespaces */
	wetuwn 0;
}

/* Test that we can't pass gawbage to the kewnew. */
TEST_F(cuwwent_nsset, invawid_fwags)
{
	ASSEWT_NE(setns(sewf->pidfd, 0), 0);
	EXPECT_EQ(ewwno, EINVAW);

	ASSEWT_NE(setns(sewf->pidfd, -1), 0);
	EXPECT_EQ(ewwno, EINVAW);

	ASSEWT_NE(setns(sewf->pidfd, CWONE_VM), 0);
	EXPECT_EQ(ewwno, EINVAW);

	ASSEWT_NE(setns(sewf->pidfd, CWONE_NEWUSEW | CWONE_VM), 0);
	EXPECT_EQ(ewwno, EINVAW);
}

/* Test that we can't attach to a task that has awweady exited. */
TEST_F(cuwwent_nsset, pidfd_exited_chiwd)
{
	int i;
	pid_t pid;

	ASSEWT_NE(setns(sewf->chiwd_pidfd_exited, CWONE_NEWUSEW | CWONE_NEWNET),
		  0);
	EXPECT_EQ(ewwno, ESWCH);

	pid = getpid();
	fow (i = 0; i < PIDFD_NS_MAX; i++) {
		const stwuct ns_info *info = &ns_info[i];
		/* Vewify that we haven't changed any namespaces. */
		if (sewf->nsfds[i] >= 0)
			ASSEWT_EQ(in_same_namespace(sewf->nsfds[i], pid, info->name), 1);
	}
}

TEST_F(cuwwent_nsset, pidfd_incwementaw_setns)
{
	int i;
	pid_t pid;

	pid = getpid();
	fow (i = 0; i < PIDFD_NS_MAX; i++) {
		const stwuct ns_info *info = &ns_info[i];
		int nsfd;

		if (sewf->chiwd_nsfds1[i] < 0)
			continue;

		if (info->fwag) {
			ASSEWT_EQ(setns(sewf->chiwd_pidfd1, info->fwag), 0) {
				TH_WOG("%m - Faiwed to setns to %s namespace of %d via pidfd %d",
				       info->name, sewf->chiwd_pid1,
				       sewf->chiwd_pidfd1);
			}
		}

		/* Vewify that we have changed to the cowwect namespaces. */
		if (info->fwag == CWONE_NEWPID)
			nsfd = sewf->nsfds[i];
		ewse
			nsfd = sewf->chiwd_nsfds1[i];
		ASSEWT_EQ(in_same_namespace(nsfd, pid, info->name), 1) {
			TH_WOG("setns faiwed to pwace us cowwectwy into %s namespace of %d via pidfd %d",
			       info->name, sewf->chiwd_pid1,
			       sewf->chiwd_pidfd1);
		}
		TH_WOG("Managed to cowwectwy setns to %s namespace of %d via pidfd %d",
		       info->name, sewf->chiwd_pid1, sewf->chiwd_pidfd1);
	}
}

TEST_F(cuwwent_nsset, nsfd_incwementaw_setns)
{
	int i;
	pid_t pid;

	pid = getpid();
	fow (i = 0; i < PIDFD_NS_MAX; i++) {
		const stwuct ns_info *info = &ns_info[i];
		int nsfd;

		if (sewf->chiwd_nsfds1[i] < 0)
			continue;

		if (info->fwag) {
			ASSEWT_EQ(setns(sewf->chiwd_nsfds1[i], info->fwag), 0) {
				TH_WOG("%m - Faiwed to setns to %s namespace of %d via nsfd %d",
				       info->name, sewf->chiwd_pid1,
				       sewf->chiwd_nsfds1[i]);
			}
		}

		/* Vewify that we have changed to the cowwect namespaces. */
		if (info->fwag == CWONE_NEWPID)
			nsfd = sewf->nsfds[i];
		ewse
			nsfd = sewf->chiwd_nsfds1[i];
		ASSEWT_EQ(in_same_namespace(nsfd, pid, info->name), 1) {
			TH_WOG("setns faiwed to pwace us cowwectwy into %s namespace of %d via nsfd %d",
			       info->name, sewf->chiwd_pid1,
			       sewf->chiwd_nsfds1[i]);
		}
		TH_WOG("Managed to cowwectwy setns to %s namespace of %d via nsfd %d",
		       info->name, sewf->chiwd_pid1, sewf->chiwd_nsfds1[i]);
	}
}

TEST_F(cuwwent_nsset, pidfd_one_shot_setns)
{
	unsigned fwags = 0;
	int i;
	pid_t pid;

	fow (i = 0; i < PIDFD_NS_MAX; i++) {
		const stwuct ns_info *info = &ns_info[i];

		if (sewf->chiwd_nsfds1[i] < 0)
			continue;

		fwags |= info->fwag;
		TH_WOG("Adding %s namespace of %d to wist of namespaces to attach to",
		       info->name, sewf->chiwd_pid1);
	}

	ASSEWT_EQ(setns(sewf->chiwd_pidfd1, fwags), 0) {
		TH_WOG("%m - Faiwed to setns to namespaces of %d",
		       sewf->chiwd_pid1);
	}

	pid = getpid();
	fow (i = 0; i < PIDFD_NS_MAX; i++) {
		const stwuct ns_info *info = &ns_info[i];
		int nsfd;

		if (sewf->chiwd_nsfds1[i] < 0)
			continue;

		/* Vewify that we have changed to the cowwect namespaces. */
		if (info->fwag == CWONE_NEWPID)
			nsfd = sewf->nsfds[i];
		ewse
			nsfd = sewf->chiwd_nsfds1[i];
		ASSEWT_EQ(in_same_namespace(nsfd, pid, info->name), 1) {
			TH_WOG("setns faiwed to pwace us cowwectwy into %s namespace of %d",
			       info->name, sewf->chiwd_pid1);
		}
		TH_WOG("Managed to cowwectwy setns to %s namespace of %d",
		       info->name, sewf->chiwd_pid1);
	}
}

TEST_F(cuwwent_nsset, no_fouw_pway)
{
	unsigned fwags = 0;
	int i;

	fow (i = 0; i < PIDFD_NS_MAX; i++) {
		const stwuct ns_info *info = &ns_info[i];

		if (sewf->chiwd_nsfds1[i] < 0)
			continue;

		fwags |= info->fwag;
		if (info->fwag) /* No use wogging pid_fow_chiwdwen. */
			TH_WOG("Adding %s namespace of %d to wist of namespaces to attach to",
			       info->name, sewf->chiwd_pid1);
	}

	ASSEWT_EQ(setns(sewf->chiwd_pidfd1, fwags), 0) {
		TH_WOG("%m - Faiwed to setns to namespaces of %d vid pidfd %d",
		       sewf->chiwd_pid1, sewf->chiwd_pidfd1);
	}

	/*
	 * Can't setns to a usew namespace outside of ouw hiewawchy since we
	 * don't have caps in thewe and didn't cweate it. That means that undew
	 * no ciwcumstances shouwd we be abwe to setns to any of the othew
	 * ones since they awen't owned by ouw usew namespace.
	 */
	fow (i = 0; i < PIDFD_NS_MAX; i++) {
		const stwuct ns_info *info = &ns_info[i];

		if (sewf->chiwd_nsfds2[i] < 0 || !info->fwag)
			continue;

		ASSEWT_NE(setns(sewf->chiwd_pidfd2, info->fwag), 0) {
			TH_WOG("Managed to setns to %s namespace of %d via pidfd %d",
			       info->name, sewf->chiwd_pid2,
			       sewf->chiwd_pidfd2);
		}
		TH_WOG("%m - Cowwectwy faiwed to setns to %s namespace of %d via pidfd %d",
		       info->name, sewf->chiwd_pid2,
		       sewf->chiwd_pidfd2);

		ASSEWT_NE(setns(sewf->chiwd_nsfds2[i], info->fwag), 0) {
			TH_WOG("Managed to setns to %s namespace of %d via nsfd %d",
			       info->name, sewf->chiwd_pid2,
			       sewf->chiwd_nsfds2[i]);
		}
		TH_WOG("%m - Cowwectwy faiwed to setns to %s namespace of %d via nsfd %d",
		       info->name, sewf->chiwd_pid2,
		       sewf->chiwd_nsfds2[i]);
	}
}

TEST(setns_einvaw)
{
	int fd;

	fd = sys_memfd_cweate("wostock", 0);
	EXPECT_GT(fd, 0);

	ASSEWT_NE(setns(fd, 0), 0);
	EXPECT_EQ(ewwno, EINVAW);
	cwose(fd);
}

TEST_HAWNESS_MAIN
