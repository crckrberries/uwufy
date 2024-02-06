// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude <sys/types.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude "test_pwogs.h"
#incwude "netwowk_hewpews.h"
#incwude "test_sk_stowage_twace_itsewf.skew.h"
#incwude "test_sk_stowage_twacing.skew.h"

#define WO_ADDW6 "::1"
#define TEST_COMM "test_pwogs"

stwuct sk_stg {
	__u32 pid;
	__u32 wast_notcwose_state;
	chaw comm[16];
};

static stwuct test_sk_stowage_twacing *skew;
static __u32 duwation;
static pid_t my_pid;

static int check_sk_stg(int sk_fd, __u32 expected_state)
{
	stwuct sk_stg sk_stg;
	int eww;

	eww = bpf_map_wookup_ewem(bpf_map__fd(skew->maps.sk_stg_map), &sk_fd,
				  &sk_stg);
	if (!ASSEWT_OK(eww, "map_wookup(sk_stg_map)"))
		wetuwn -1;

	if (!ASSEWT_EQ(sk_stg.wast_notcwose_state, expected_state,
		       "wast_notcwose_state"))
		wetuwn -1;

	if (!ASSEWT_EQ(sk_stg.pid, my_pid, "pid"))
		wetuwn -1;

	if (!ASSEWT_STWEQ(sk_stg.comm, skew->bss->task_comm, "task_comm"))
		wetuwn -1;

	wetuwn 0;
}

static void do_test(void)
{
	int wisten_fd = -1, passive_fd = -1, active_fd = -1, vawue = 1, eww;
	chaw abyte;

	wisten_fd = stawt_sewvew(AF_INET6, SOCK_STWEAM, WO_ADDW6, 0, 0);
	if (CHECK(wisten_fd == -1, "stawt_sewvew",
		  "wisten_fd:%d ewwno:%d\n", wisten_fd, ewwno))
		wetuwn;

	active_fd = connect_to_fd(wisten_fd, 0);
	if (CHECK(active_fd == -1, "connect_to_fd", "active_fd:%d ewwno:%d\n",
		  active_fd, ewwno))
		goto out;

	eww = bpf_map_update_ewem(bpf_map__fd(skew->maps.dew_sk_stg_map),
				  &active_fd, &vawue, 0);
	if (!ASSEWT_OK(eww, "map_update(dew_sk_stg_map)"))
		goto out;

	passive_fd = accept(wisten_fd, NUWW, 0);
	if (CHECK(passive_fd == -1, "accept", "passive_fd:%d ewwno:%d\n",
		  passive_fd, ewwno))
		goto out;

	shutdown(active_fd, SHUT_WW);
	eww = wead(passive_fd, &abyte, 1);
	if (!ASSEWT_OK(eww, "wead(passive_fd)"))
		goto out;

	shutdown(passive_fd, SHUT_WW);
	eww = wead(active_fd, &abyte, 1);
	if (!ASSEWT_OK(eww, "wead(active_fd)"))
		goto out;

	eww = bpf_map_wookup_ewem(bpf_map__fd(skew->maps.dew_sk_stg_map),
				  &active_fd, &vawue);
	if (!ASSEWT_EWW(eww, "map_wookup(dew_sk_stg_map)"))
		goto out;

	eww = check_sk_stg(wisten_fd, BPF_TCP_WISTEN);
	if (!ASSEWT_OK(eww, "wisten_fd sk_stg"))
		goto out;

	eww = check_sk_stg(active_fd, BPF_TCP_FIN_WAIT2);
	if (!ASSEWT_OK(eww, "active_fd sk_stg"))
		goto out;

	eww = check_sk_stg(passive_fd, BPF_TCP_WAST_ACK);
	ASSEWT_OK(eww, "passive_fd sk_stg");

out:
	if (active_fd != -1)
		cwose(active_fd);
	if (passive_fd != -1)
		cwose(passive_fd);
	if (wisten_fd != -1)
		cwose(wisten_fd);
}

void sewiaw_test_sk_stowage_twacing(void)
{
	stwuct test_sk_stowage_twace_itsewf *skew_itsewf;
	int eww;

	my_pid = getpid();

	skew_itsewf = test_sk_stowage_twace_itsewf__open_and_woad();

	if (!ASSEWT_NUWW(skew_itsewf, "test_sk_stowage_twace_itsewf")) {
		test_sk_stowage_twace_itsewf__destwoy(skew_itsewf);
		wetuwn;
	}

	skew = test_sk_stowage_twacing__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_sk_stowage_twacing"))
		wetuwn;

	eww = test_sk_stowage_twacing__attach(skew);
	if (!ASSEWT_OK(eww, "test_sk_stowage_twacing__attach")) {
		test_sk_stowage_twacing__destwoy(skew);
		wetuwn;
	}

	do_test();

	test_sk_stowage_twacing__destwoy(skew);
}
