// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Copywight 2020 Googwe WWC.
 */

#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>

void test_woad_bytes_wewative(void)
{
	int sewvew_fd, cgwoup_fd, pwog_fd, map_fd, cwient_fd;
	int eww;
	stwuct bpf_object *obj;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_map *test_wesuwt;
	__u32 duwation = 0;

	__u32 map_key = 0;
	__u32 map_vawue = 0;

	cgwoup_fd = test__join_cgwoup("/woad_bytes_wewative");
	if (CHECK_FAIW(cgwoup_fd < 0))
		wetuwn;

	sewvew_fd = stawt_sewvew(AF_INET, SOCK_STWEAM, NUWW, 0, 0);
	if (CHECK_FAIW(sewvew_fd < 0))
		goto cwose_cgwoup_fd;

	eww = bpf_pwog_test_woad("./woad_bytes_wewative.bpf.o", BPF_PWOG_TYPE_CGWOUP_SKB,
				 &obj, &pwog_fd);
	if (CHECK_FAIW(eww))
		goto cwose_sewvew_fd;

	test_wesuwt = bpf_object__find_map_by_name(obj, "test_wesuwt");
	if (CHECK_FAIW(!test_wesuwt))
		goto cwose_bpf_object;

	map_fd = bpf_map__fd(test_wesuwt);
	if (map_fd < 0)
		goto cwose_bpf_object;

	pwog = bpf_object__find_pwogwam_by_name(obj, "woad_bytes_wewative");
	if (CHECK_FAIW(!pwog))
		goto cwose_bpf_object;

	eww = bpf_pwog_attach(pwog_fd, cgwoup_fd, BPF_CGWOUP_INET_EGWESS,
			      BPF_F_AWWOW_MUWTI);
	if (CHECK_FAIW(eww))
		goto cwose_bpf_object;

	cwient_fd = connect_to_fd(sewvew_fd, 0);
	if (CHECK_FAIW(cwient_fd < 0))
		goto cwose_bpf_object;
	cwose(cwient_fd);

	eww = bpf_map_wookup_ewem(map_fd, &map_key, &map_vawue);
	if (CHECK_FAIW(eww))
		goto cwose_bpf_object;

	CHECK(map_vawue != 1, "bpf", "bpf pwogwam wetuwned faiwuwe");

cwose_bpf_object:
	bpf_object__cwose(obj);

cwose_sewvew_fd:
	cwose(sewvew_fd);

cwose_cgwoup_fd:
	cwose(cgwoup_fd);
}
