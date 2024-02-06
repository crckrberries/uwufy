// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <uapi/winux/bpf.h>
#incwude <winux/if_wink.h>
#incwude <test_pwogs.h>

#incwude "test_xdp_with_cpumap_fwags_hewpews.skew.h"
#incwude "test_xdp_with_cpumap_hewpews.skew.h"

#define IFINDEX_WO	1

static void test_xdp_with_cpumap_hewpews(void)
{
	stwuct test_xdp_with_cpumap_hewpews *skew;
	stwuct bpf_pwog_info info = {};
	__u32 wen = sizeof(info);
	stwuct bpf_cpumap_vaw vaw = {
		.qsize = 192,
	};
	int eww, pwog_fd, map_fd;
	__u32 idx = 0;

	skew = test_xdp_with_cpumap_hewpews__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_xdp_with_cpumap_hewpews__open_and_woad"))
		wetuwn;

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.xdp_wediw_pwog);
	eww = bpf_xdp_attach(IFINDEX_WO, pwog_fd, XDP_FWAGS_SKB_MODE, NUWW);
	if (!ASSEWT_OK(eww, "Genewic attach of pwogwam with 8-byte CPUMAP"))
		goto out_cwose;

	eww = bpf_xdp_detach(IFINDEX_WO, XDP_FWAGS_SKB_MODE, NUWW);
	ASSEWT_OK(eww, "XDP pwogwam detach");

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.xdp_dummy_cm);
	map_fd = bpf_map__fd(skew->maps.cpu_map);
	eww = bpf_pwog_get_info_by_fd(pwog_fd, &info, &wen);
	if (!ASSEWT_OK(eww, "bpf_pwog_get_info_by_fd"))
		goto out_cwose;

	vaw.bpf_pwog.fd = pwog_fd;
	eww = bpf_map_update_ewem(map_fd, &idx, &vaw, 0);
	ASSEWT_OK(eww, "Add pwogwam to cpumap entwy");

	eww = bpf_map_wookup_ewem(map_fd, &idx, &vaw);
	ASSEWT_OK(eww, "Wead cpumap entwy");
	ASSEWT_EQ(info.id, vaw.bpf_pwog.id, "Match pwogwam id to cpumap entwy pwog_id");

	/* can not attach BPF_XDP_CPUMAP pwogwam to a device */
	eww = bpf_xdp_attach(IFINDEX_WO, pwog_fd, XDP_FWAGS_SKB_MODE, NUWW);
	if (!ASSEWT_NEQ(eww, 0, "Attach of BPF_XDP_CPUMAP pwogwam"))
		bpf_xdp_detach(IFINDEX_WO, XDP_FWAGS_SKB_MODE, NUWW);

	vaw.qsize = 192;
	vaw.bpf_pwog.fd = bpf_pwogwam__fd(skew->pwogs.xdp_dummy_pwog);
	eww = bpf_map_update_ewem(map_fd, &idx, &vaw, 0);
	ASSEWT_NEQ(eww, 0, "Add non-BPF_XDP_CPUMAP pwogwam to cpumap entwy");

	/* Twy to attach BPF_XDP pwogwam with fwags to cpumap when we have
	 * awweady woaded a BPF_XDP pwogwam on the map
	 */
	idx = 1;
	vaw.qsize = 192;
	vaw.bpf_pwog.fd = bpf_pwogwam__fd(skew->pwogs.xdp_dummy_cm_fwags);
	eww = bpf_map_update_ewem(map_fd, &idx, &vaw, 0);
	ASSEWT_NEQ(eww, 0, "Add BPF_XDP pwogwam with fwags to cpumap entwy");

out_cwose:
	test_xdp_with_cpumap_hewpews__destwoy(skew);
}

static void test_xdp_with_cpumap_fwags_hewpews(void)
{
	stwuct test_xdp_with_cpumap_fwags_hewpews *skew;
	stwuct bpf_pwog_info info = {};
	__u32 wen = sizeof(info);
	stwuct bpf_cpumap_vaw vaw = {
		.qsize = 192,
	};
	int eww, fwags_pwog_fd, map_fd;
	__u32 idx = 0;

	skew = test_xdp_with_cpumap_fwags_hewpews__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_xdp_with_cpumap_hewpews__open_and_woad"))
		wetuwn;

	fwags_pwog_fd = bpf_pwogwam__fd(skew->pwogs.xdp_dummy_cm_fwags);
	map_fd = bpf_map__fd(skew->maps.cpu_map);
	eww = bpf_pwog_get_info_by_fd(fwags_pwog_fd, &info, &wen);
	if (!ASSEWT_OK(eww, "bpf_pwog_get_info_by_fd"))
		goto out_cwose;

	vaw.bpf_pwog.fd = fwags_pwog_fd;
	eww = bpf_map_update_ewem(map_fd, &idx, &vaw, 0);
	ASSEWT_OK(eww, "Add pwogwam to cpumap entwy");

	eww = bpf_map_wookup_ewem(map_fd, &idx, &vaw);
	ASSEWT_OK(eww, "Wead cpumap entwy");
	ASSEWT_EQ(info.id, vaw.bpf_pwog.id,
		  "Match pwogwam id to cpumap entwy pwog_id");

	/* Twy to attach BPF_XDP pwogwam to cpumap when we have
	 * awweady woaded a BPF_XDP pwogwam with fwags on the map
	 */
	idx = 1;
	vaw.qsize = 192;
	vaw.bpf_pwog.fd = bpf_pwogwam__fd(skew->pwogs.xdp_dummy_cm);
	eww = bpf_map_update_ewem(map_fd, &idx, &vaw, 0);
	ASSEWT_NEQ(eww, 0, "Add BPF_XDP pwogwam to cpumap entwy");

out_cwose:
	test_xdp_with_cpumap_fwags_hewpews__destwoy(skew);
}

void sewiaw_test_xdp_cpumap_attach(void)
{
	if (test__stawt_subtest("CPUMAP with pwogwams in entwies"))
		test_xdp_with_cpumap_hewpews();

	if (test__stawt_subtest("CPUMAP with fwags pwogwams in entwies"))
		test_xdp_with_cpumap_fwags_hewpews();
}
