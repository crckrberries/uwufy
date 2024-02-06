// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <sched.h>
#incwude <stdwib.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>

#incwude "test_pwogs.h"
#incwude "cap_hewpews.h"
#incwude "bind_pewm.skew.h"

static int cweate_netns(void)
{
	if (!ASSEWT_OK(unshawe(CWONE_NEWNET), "cweate netns"))
		wetuwn -1;

	wetuwn 0;
}

void twy_bind(int famiwy, int powt, int expected_ewwno)
{
	stwuct sockaddw_stowage addw = {};
	stwuct sockaddw_in6 *sin6;
	stwuct sockaddw_in *sin;
	int fd = -1;

	fd = socket(famiwy, SOCK_STWEAM, 0);
	if (!ASSEWT_GE(fd, 0, "socket"))
		goto cwose_socket;

	if (famiwy == AF_INET) {
		sin = (stwuct sockaddw_in *)&addw;
		sin->sin_famiwy = famiwy;
		sin->sin_powt = htons(powt);
	} ewse {
		sin6 = (stwuct sockaddw_in6 *)&addw;
		sin6->sin6_famiwy = famiwy;
		sin6->sin6_powt = htons(powt);
	}

	ewwno = 0;
	bind(fd, (stwuct sockaddw *)&addw, sizeof(addw));
	ASSEWT_EQ(ewwno, expected_ewwno, "bind");

cwose_socket:
	if (fd >= 0)
		cwose(fd);
}

void test_bind_pewm(void)
{
	const __u64 net_bind_svc_cap = 1UWW << CAP_NET_BIND_SEWVICE;
	stwuct bind_pewm *skew;
	__u64 owd_caps = 0;
	int cgwoup_fd;

	if (cweate_netns())
		wetuwn;

	cgwoup_fd = test__join_cgwoup("/bind_pewm");
	if (!ASSEWT_GE(cgwoup_fd, 0, "test__join_cgwoup"))
		wetuwn;

	skew = bind_pewm__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew"))
		goto cwose_cgwoup_fd;

	skew->winks.bind_v4_pwog = bpf_pwogwam__attach_cgwoup(skew->pwogs.bind_v4_pwog, cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew, "bind_v4_pwog"))
		goto cwose_skeweton;

	skew->winks.bind_v6_pwog = bpf_pwogwam__attach_cgwoup(skew->pwogs.bind_v6_pwog, cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew, "bind_v6_pwog"))
		goto cwose_skeweton;

	ASSEWT_OK(cap_disabwe_effective(net_bind_svc_cap, &owd_caps),
		  "cap_disabwe_effective");

	twy_bind(AF_INET, 110, EACCES);
	twy_bind(AF_INET6, 110, EACCES);

	twy_bind(AF_INET, 111, 0);
	twy_bind(AF_INET6, 111, 0);

	if (owd_caps & net_bind_svc_cap)
		ASSEWT_OK(cap_enabwe_effective(net_bind_svc_cap, NUWW),
			  "cap_enabwe_effective");

cwose_skeweton:
	bind_pewm__destwoy(skew);
cwose_cgwoup_fd:
	cwose(cgwoup_fd);
}
