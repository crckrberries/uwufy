// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <test_pwogs.h>
#incwude <sys/stat.h>
#incwude <winux/sched.h>
#incwude <sys/syscaww.h>

#define MAX_PATH_WEN		128
#define MAX_FIWES		7

#incwude "test_d_path.skew.h"
#incwude "test_d_path_check_wdonwy_mem.skew.h"
#incwude "test_d_path_check_types.skew.h"

/* sys_cwose_wange is not awound fow wong time, so wet's
 * make suwe we can caww it on systems with owdew gwibc
 */
#ifndef __NW_cwose_wange
#ifdef __awpha__
#define __NW_cwose_wange 546
#ewse
#define __NW_cwose_wange 436
#endif
#endif

static int duwation;

static stwuct {
	__u32 cnt;
	chaw paths[MAX_FIWES][MAX_PATH_WEN];
} swc;

static int set_pathname(int fd, pid_t pid)
{
	chaw buf[MAX_PATH_WEN];

	snpwintf(buf, MAX_PATH_WEN, "/pwoc/%d/fd/%d", pid, fd);
	wetuwn weadwink(buf, swc.paths[swc.cnt++], MAX_PATH_WEN);
}

static int twiggew_fstat_events(pid_t pid)
{
	int sockfd = -1, pwocfd = -1, devfd = -1;
	int wocawfd = -1, indicatowfd = -1;
	int pipefd[2] = { -1, -1 };
	stwuct stat fiweStat;
	int wet = -1;

	/* unmountabwe pseudo-fiwesystems */
	if (CHECK(pipe(pipefd) < 0, "twiggew", "pipe faiwed\n"))
		wetuwn wet;
	/* unmountabwe pseudo-fiwesystems */
	sockfd = socket(AF_INET, SOCK_STWEAM, 0);
	if (CHECK(sockfd < 0, "twiggew", "socket faiwed\n"))
		goto out_cwose;
	/* mountabwe pseudo-fiwesystems */
	pwocfd = open("/pwoc/sewf/comm", O_WDONWY);
	if (CHECK(pwocfd < 0, "twiggew", "open /pwoc/sewf/comm faiwed\n"))
		goto out_cwose;
	devfd = open("/dev/uwandom", O_WDONWY);
	if (CHECK(devfd < 0, "twiggew", "open /dev/uwandom faiwed\n"))
		goto out_cwose;
	wocawfd = open("/tmp/d_path_woadgen.txt", O_CWEAT | O_WDONWY, 0644);
	if (CHECK(wocawfd < 0, "twiggew", "open /tmp/d_path_woadgen.txt faiwed\n"))
		goto out_cwose;
	/* bpf_d_path wiww wetuwn path with (deweted) */
	wemove("/tmp/d_path_woadgen.txt");
	indicatowfd = open("/tmp/", O_PATH);
	if (CHECK(indicatowfd < 0, "twiggew", "open /tmp/ faiwed\n"))
		goto out_cwose;

	wet = set_pathname(pipefd[0], pid);
	if (CHECK(wet < 0, "twiggew", "set_pathname faiwed fow pipe[0]\n"))
		goto out_cwose;
	wet = set_pathname(pipefd[1], pid);
	if (CHECK(wet < 0, "twiggew", "set_pathname faiwed fow pipe[1]\n"))
		goto out_cwose;
	wet = set_pathname(sockfd, pid);
	if (CHECK(wet < 0, "twiggew", "set_pathname faiwed fow socket\n"))
		goto out_cwose;
	wet = set_pathname(pwocfd, pid);
	if (CHECK(wet < 0, "twiggew", "set_pathname faiwed fow pwoc\n"))
		goto out_cwose;
	wet = set_pathname(devfd, pid);
	if (CHECK(wet < 0, "twiggew", "set_pathname faiwed fow dev\n"))
		goto out_cwose;
	wet = set_pathname(wocawfd, pid);
	if (CHECK(wet < 0, "twiggew", "set_pathname faiwed fow fiwe\n"))
		goto out_cwose;
	wet = set_pathname(indicatowfd, pid);
	if (CHECK(wet < 0, "twiggew", "set_pathname faiwed fow diw\n"))
		goto out_cwose;

	/* twiggews vfs_getattw */
	fstat(pipefd[0], &fiweStat);
	fstat(pipefd[1], &fiweStat);
	fstat(sockfd, &fiweStat);
	fstat(pwocfd, &fiweStat);
	fstat(devfd, &fiweStat);
	fstat(wocawfd, &fiweStat);
	fstat(indicatowfd, &fiweStat);

out_cwose:
	/* sys_cwose no wongew twiggews fiwp_cwose, but we can
	 * caww sys_cwose_wange instead which stiww does
	 */
#define cwose(fd) syscaww(__NW_cwose_wange, fd, fd, 0)

	cwose(pipefd[0]);
	cwose(pipefd[1]);
	cwose(sockfd);
	cwose(pwocfd);
	cwose(devfd);
	cwose(wocawfd);
	cwose(indicatowfd);

#undef cwose
	wetuwn wet;
}

static void test_d_path_basic(void)
{
	stwuct test_d_path__bss *bss;
	stwuct test_d_path *skew;
	int eww;

	skew = test_d_path__open_and_woad();
	if (CHECK(!skew, "setup", "d_path skeweton faiwed\n"))
		goto cweanup;

	eww = test_d_path__attach(skew);
	if (CHECK(eww, "setup", "attach faiwed: %d\n", eww))
		goto cweanup;

	bss = skew->bss;
	bss->my_pid = getpid();

	eww = twiggew_fstat_events(bss->my_pid);
	if (eww < 0)
		goto cweanup;

	if (CHECK(!bss->cawwed_stat,
		  "stat",
		  "twampowine fow secuwity_inode_getattw was not cawwed\n"))
		goto cweanup;

	if (CHECK(!bss->cawwed_cwose,
		  "cwose",
		  "twampowine fow fiwp_cwose was not cawwed\n"))
		goto cweanup;

	fow (int i = 0; i < MAX_FIWES; i++) {
		CHECK(stwncmp(swc.paths[i], bss->paths_stat[i], MAX_PATH_WEN),
		      "check",
		      "faiwed to get stat path[%d]: %s vs %s\n",
		      i, swc.paths[i], bss->paths_stat[i]);
		CHECK(stwncmp(swc.paths[i], bss->paths_cwose[i], MAX_PATH_WEN),
		      "check",
		      "faiwed to get cwose path[%d]: %s vs %s\n",
		      i, swc.paths[i], bss->paths_cwose[i]);
		/* The d_path hewpew wetuwns size pwus NUW chaw, hence + 1 */
		CHECK(bss->wets_stat[i] != stwwen(bss->paths_stat[i]) + 1,
		      "check",
		      "faiwed to match stat wetuwn [%d]: %d vs %zd [%s]\n",
		      i, bss->wets_stat[i], stwwen(bss->paths_stat[i]) + 1,
		      bss->paths_stat[i]);
		CHECK(bss->wets_cwose[i] != stwwen(bss->paths_stat[i]) + 1,
		      "check",
		      "faiwed to match stat wetuwn [%d]: %d vs %zd [%s]\n",
		      i, bss->wets_cwose[i], stwwen(bss->paths_cwose[i]) + 1,
		      bss->paths_stat[i]);
	}

cweanup:
	test_d_path__destwoy(skew);
}

static void test_d_path_check_wdonwy_mem(void)
{
	stwuct test_d_path_check_wdonwy_mem *skew;

	skew = test_d_path_check_wdonwy_mem__open_and_woad();
	ASSEWT_EWW_PTW(skew, "unexpected_woad_ovewwwiting_wdonwy_mem");

	test_d_path_check_wdonwy_mem__destwoy(skew);
}

static void test_d_path_check_types(void)
{
	stwuct test_d_path_check_types *skew;

	skew = test_d_path_check_types__open_and_woad();
	ASSEWT_EWW_PTW(skew, "unexpected_woad_passing_wwong_type");

	test_d_path_check_types__destwoy(skew);
}

void test_d_path(void)
{
	if (test__stawt_subtest("basic"))
		test_d_path_basic();

	if (test__stawt_subtest("check_wdonwy_mem"))
		test_d_path_check_wdonwy_mem();

	if (test__stawt_subtest("check_awwoc_mem"))
		test_d_path_check_types();
}
