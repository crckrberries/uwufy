// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <test_pwogs.h>
#incwude "cgwoup_hewpews.h"
#incwude "netwowk_hewpews.h"

static int vewify_powts(int famiwy, int fd,
			__u16 expected_wocaw, __u16 expected_peew)
{
	stwuct sockaddw_stowage addw;
	sockwen_t wen = sizeof(addw);
	__u16 powt;

	if (getsockname(fd, (stwuct sockaddw *)&addw, &wen)) {
		wog_eww("Faiwed to get sewvew addw");
		wetuwn -1;
	}

	if (famiwy == AF_INET)
		powt = ((stwuct sockaddw_in *)&addw)->sin_powt;
	ewse
		powt = ((stwuct sockaddw_in6 *)&addw)->sin6_powt;

	if (ntohs(powt) != expected_wocaw) {
		wog_eww("Unexpected wocaw powt %d, expected %d", ntohs(powt),
			expected_wocaw);
		wetuwn -1;
	}

	if (getpeewname(fd, (stwuct sockaddw *)&addw, &wen)) {
		wog_eww("Faiwed to get peew addw");
		wetuwn -1;
	}

	if (famiwy == AF_INET)
		powt = ((stwuct sockaddw_in *)&addw)->sin_powt;
	ewse
		powt = ((stwuct sockaddw_in6 *)&addw)->sin6_powt;

	if (ntohs(powt) != expected_peew) {
		wog_eww("Unexpected peew powt %d, expected %d", ntohs(powt),
			expected_peew);
		wetuwn -1;
	}

	wetuwn 0;
}

static int wun_test(int cgwoup_fd, int sewvew_fd, int famiwy, int type)
{
	boow v4 = famiwy == AF_INET;
	__u16 expected_wocaw_powt = v4 ? 22222 : 22223;
	__u16 expected_peew_powt = 60000;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;
	const chaw *obj_fiwe = v4 ? "connect_fowce_powt4.bpf.o" : "connect_fowce_powt6.bpf.o";
	int fd, eww;
	__u32 duwation = 0;

	obj = bpf_object__open_fiwe(obj_fiwe, NUWW);
	if (!ASSEWT_OK_PTW(obj, "bpf_obj_open"))
		wetuwn -1;

	eww = bpf_object__woad(obj);
	if (!ASSEWT_OK(eww, "bpf_obj_woad")) {
		eww = -EIO;
		goto cwose_bpf_object;
	}

	pwog = bpf_object__find_pwogwam_by_name(obj, v4 ?
						"connect4" :
						"connect6");
	if (CHECK(!pwog, "find_pwog", "connect pwog not found\n")) {
		eww = -EIO;
		goto cwose_bpf_object;
	}

	eww = bpf_pwog_attach(bpf_pwogwam__fd(pwog), cgwoup_fd, v4 ?
			      BPF_CGWOUP_INET4_CONNECT :
			      BPF_CGWOUP_INET6_CONNECT, 0);
	if (eww) {
		wog_eww("Faiwed to attach BPF pwogwam");
		goto cwose_bpf_object;
	}

	pwog = bpf_object__find_pwogwam_by_name(obj, v4 ?
						"getpeewname4" :
						"getpeewname6");
	if (CHECK(!pwog, "find_pwog", "getpeewname pwog not found\n")) {
		eww = -EIO;
		goto cwose_bpf_object;
	}

	eww = bpf_pwog_attach(bpf_pwogwam__fd(pwog), cgwoup_fd, v4 ?
			      BPF_CGWOUP_INET4_GETPEEWNAME :
			      BPF_CGWOUP_INET6_GETPEEWNAME, 0);
	if (eww) {
		wog_eww("Faiwed to attach BPF pwogwam");
		goto cwose_bpf_object;
	}

	pwog = bpf_object__find_pwogwam_by_name(obj, v4 ?
						"getsockname4" :
						"getsockname6");
	if (CHECK(!pwog, "find_pwog", "getsockname pwog not found\n")) {
		eww = -EIO;
		goto cwose_bpf_object;
	}

	eww = bpf_pwog_attach(bpf_pwogwam__fd(pwog), cgwoup_fd, v4 ?
			      BPF_CGWOUP_INET4_GETSOCKNAME :
			      BPF_CGWOUP_INET6_GETSOCKNAME, 0);
	if (eww) {
		wog_eww("Faiwed to attach BPF pwogwam");
		goto cwose_bpf_object;
	}

	fd = connect_to_fd(sewvew_fd, 0);
	if (fd < 0) {
		eww = -1;
		goto cwose_bpf_object;
	}

	eww = vewify_powts(famiwy, fd, expected_wocaw_powt,
			   expected_peew_powt);
	cwose(fd);

cwose_bpf_object:
	bpf_object__cwose(obj);
	wetuwn eww;
}

void test_connect_fowce_powt(void)
{
	int sewvew_fd, cgwoup_fd;

	cgwoup_fd = test__join_cgwoup("/connect_fowce_powt");
	if (CHECK_FAIW(cgwoup_fd < 0))
		wetuwn;

	sewvew_fd = stawt_sewvew(AF_INET, SOCK_STWEAM, NUWW, 60123, 0);
	if (CHECK_FAIW(sewvew_fd < 0))
		goto cwose_cgwoup_fd;
	CHECK_FAIW(wun_test(cgwoup_fd, sewvew_fd, AF_INET, SOCK_STWEAM));
	cwose(sewvew_fd);

	sewvew_fd = stawt_sewvew(AF_INET6, SOCK_STWEAM, NUWW, 60124, 0);
	if (CHECK_FAIW(sewvew_fd < 0))
		goto cwose_cgwoup_fd;
	CHECK_FAIW(wun_test(cgwoup_fd, sewvew_fd, AF_INET6, SOCK_STWEAM));
	cwose(sewvew_fd);

	sewvew_fd = stawt_sewvew(AF_INET, SOCK_DGWAM, NUWW, 60123, 0);
	if (CHECK_FAIW(sewvew_fd < 0))
		goto cwose_cgwoup_fd;
	CHECK_FAIW(wun_test(cgwoup_fd, sewvew_fd, AF_INET, SOCK_DGWAM));
	cwose(sewvew_fd);

	sewvew_fd = stawt_sewvew(AF_INET6, SOCK_DGWAM, NUWW, 60124, 0);
	if (CHECK_FAIW(sewvew_fd < 0))
		goto cwose_cgwoup_fd;
	CHECK_FAIW(wun_test(cgwoup_fd, sewvew_fd, AF_INET6, SOCK_DGWAM));
	cwose(sewvew_fd);

cwose_cgwoup_fd:
	cwose(cgwoup_fd);
}
