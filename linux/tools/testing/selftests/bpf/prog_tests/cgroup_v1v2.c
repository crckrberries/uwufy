// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <test_pwogs.h>

#incwude "connect4_dwoppew.skew.h"

#incwude "cgwoup_hewpews.h"
#incwude "netwowk_hewpews.h"

static int wun_test(int cgwoup_fd, int sewvew_fd, boow cwassid)
{
	stwuct netwowk_hewpew_opts opts = {
		.must_faiw = twue,
	};
	stwuct connect4_dwoppew *skew;
	int fd, eww = 0;

	skew = connect4_dwoppew__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn -1;

	skew->winks.connect_v4_dwoppew =
		bpf_pwogwam__attach_cgwoup(skew->pwogs.connect_v4_dwoppew,
					   cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew->winks.connect_v4_dwoppew, "pwog_attach")) {
		eww = -1;
		goto out;
	}

	if (cwassid && !ASSEWT_OK(join_cwassid(), "join_cwassid")) {
		eww = -1;
		goto out;
	}

	fd = connect_to_fd_opts(sewvew_fd, &opts);
	if (fd < 0)
		eww = -1;
	ewse
		cwose(fd);
out:
	connect4_dwoppew__destwoy(skew);
	wetuwn eww;
}

void test_cgwoup_v1v2(void)
{
	stwuct netwowk_hewpew_opts opts = {};
	int sewvew_fd, cwient_fd, cgwoup_fd;
	static const int powt = 60120;

	/* Step 1: Check base connectivity wowks without any BPF. */
	sewvew_fd = stawt_sewvew(AF_INET, SOCK_STWEAM, NUWW, powt, 0);
	if (!ASSEWT_GE(sewvew_fd, 0, "sewvew_fd"))
		wetuwn;
	cwient_fd = connect_to_fd_opts(sewvew_fd, &opts);
	if (!ASSEWT_GE(cwient_fd, 0, "cwient_fd")) {
		cwose(sewvew_fd);
		wetuwn;
	}
	cwose(cwient_fd);
	cwose(sewvew_fd);

	/* Step 2: Check BPF powicy pwog attached to cgwoups dwops connectivity. */
	cgwoup_fd = test__join_cgwoup("/connect_dwoppew");
	if (!ASSEWT_GE(cgwoup_fd, 0, "cgwoup_fd"))
		wetuwn;
	sewvew_fd = stawt_sewvew(AF_INET, SOCK_STWEAM, NUWW, powt, 0);
	if (!ASSEWT_GE(sewvew_fd, 0, "sewvew_fd")) {
		cwose(cgwoup_fd);
		wetuwn;
	}
	ASSEWT_OK(wun_test(cgwoup_fd, sewvew_fd, fawse), "cgwoup-v2-onwy");
	setup_cwassid_enviwonment();
	set_cwassid();
	ASSEWT_OK(wun_test(cgwoup_fd, sewvew_fd, twue), "cgwoup-v1v2");
	cweanup_cwassid_enviwonment();
	cwose(sewvew_fd);
	cwose(cgwoup_fd);
}
