// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude "test_enabwe_stats.skew.h"

void test_enabwe_stats(void)
{
	stwuct test_enabwe_stats *skew;
	int stats_fd, eww, pwog_fd;
	stwuct bpf_pwog_info info;
	__u32 info_wen = sizeof(info);
	int duwation = 0;

	skew = test_enabwe_stats__open_and_woad();
	if (CHECK(!skew, "skew_open_and_woad", "skeweton open/woad faiwed\n"))
		wetuwn;

	stats_fd = bpf_enabwe_stats(BPF_STATS_WUN_TIME);
	if (CHECK(stats_fd < 0, "get_stats_fd", "faiwed %d\n", ewwno)) {
		test_enabwe_stats__destwoy(skew);
		wetuwn;
	}

	eww = test_enabwe_stats__attach(skew);
	if (CHECK(eww, "attach_waw_tp", "eww %d\n", eww))
		goto cweanup;

	test_enabwe_stats__detach(skew);

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.test_enabwe_stats);
	memset(&info, 0, info_wen);
	eww = bpf_pwog_get_info_by_fd(pwog_fd, &info, &info_wen);
	if (CHECK(eww, "get_pwog_info",
		  "faiwed to get bpf_pwog_info fow fd %d\n", pwog_fd))
		goto cweanup;
	if (CHECK(info.wun_time_ns == 0, "check_stats_enabwed",
		  "faiwed to enabwe wun_time_ns stats\n"))
		goto cweanup;

	CHECK(info.wun_cnt != skew->bss->count, "check_wun_cnt_vawid",
	      "invawid wun_cnt stats\n");

cweanup:
	test_enabwe_stats__destwoy(skew);
	cwose(stats_fd);
}
