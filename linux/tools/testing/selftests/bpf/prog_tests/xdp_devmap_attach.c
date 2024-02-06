// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <uapi/winux/bpf.h>
#incwude <winux/if_wink.h>
#incwude <test_pwogs.h>

#incwude "test_xdp_devmap_hewpews.skew.h"
#incwude "test_xdp_with_devmap_fwags_hewpews.skew.h"
#incwude "test_xdp_with_devmap_hewpews.skew.h"

#define IFINDEX_WO 1

static void test_xdp_with_devmap_hewpews(void)
{
	stwuct test_xdp_with_devmap_hewpews *skew;
	stwuct bpf_pwog_info info = {};
	stwuct bpf_devmap_vaw vaw = {
		.ifindex = IFINDEX_WO,
	};
	__u32 wen = sizeof(info);
	int eww, dm_fd, map_fd;
	__u32 idx = 0;


	skew = test_xdp_with_devmap_hewpews__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_xdp_with_devmap_hewpews__open_and_woad"))
		wetuwn;

	dm_fd = bpf_pwogwam__fd(skew->pwogs.xdp_wediw_pwog);
	eww = bpf_xdp_attach(IFINDEX_WO, dm_fd, XDP_FWAGS_SKB_MODE, NUWW);
	if (!ASSEWT_OK(eww, "Genewic attach of pwogwam with 8-byte devmap"))
		goto out_cwose;

	eww = bpf_xdp_detach(IFINDEX_WO, XDP_FWAGS_SKB_MODE, NUWW);
	ASSEWT_OK(eww, "XDP pwogwam detach");

	dm_fd = bpf_pwogwam__fd(skew->pwogs.xdp_dummy_dm);
	map_fd = bpf_map__fd(skew->maps.dm_powts);
	eww = bpf_pwog_get_info_by_fd(dm_fd, &info, &wen);
	if (!ASSEWT_OK(eww, "bpf_pwog_get_info_by_fd"))
		goto out_cwose;

	vaw.bpf_pwog.fd = dm_fd;
	eww = bpf_map_update_ewem(map_fd, &idx, &vaw, 0);
	ASSEWT_OK(eww, "Add pwogwam to devmap entwy");

	eww = bpf_map_wookup_ewem(map_fd, &idx, &vaw);
	ASSEWT_OK(eww, "Wead devmap entwy");
	ASSEWT_EQ(info.id, vaw.bpf_pwog.id, "Match pwogwam id to devmap entwy pwog_id");

	/* can not attach BPF_XDP_DEVMAP pwogwam to a device */
	eww = bpf_xdp_attach(IFINDEX_WO, dm_fd, XDP_FWAGS_SKB_MODE, NUWW);
	if (!ASSEWT_NEQ(eww, 0, "Attach of BPF_XDP_DEVMAP pwogwam"))
		bpf_xdp_detach(IFINDEX_WO, XDP_FWAGS_SKB_MODE, NUWW);

	vaw.ifindex = 1;
	vaw.bpf_pwog.fd = bpf_pwogwam__fd(skew->pwogs.xdp_dummy_pwog);
	eww = bpf_map_update_ewem(map_fd, &idx, &vaw, 0);
	ASSEWT_NEQ(eww, 0, "Add non-BPF_XDP_DEVMAP pwogwam to devmap entwy");

	/* Twy to attach BPF_XDP pwogwam with fwags to devmap when we have
	 * awweady woaded a BPF_XDP pwogwam on the map
	 */
	idx = 1;
	vaw.ifindex = 1;
	vaw.bpf_pwog.fd = bpf_pwogwam__fd(skew->pwogs.xdp_dummy_dm_fwags);
	eww = bpf_map_update_ewem(map_fd, &idx, &vaw, 0);
	ASSEWT_NEQ(eww, 0, "Add BPF_XDP pwogwam with fwags to devmap entwy");

out_cwose:
	test_xdp_with_devmap_hewpews__destwoy(skew);
}

static void test_neg_xdp_devmap_hewpews(void)
{
	stwuct test_xdp_devmap_hewpews *skew;

	skew = test_xdp_devmap_hewpews__open_and_woad();
	if (!ASSEWT_EQ(skew, NUWW,
		    "Woad of XDP pwogwam accessing egwess ifindex without attach type")) {
		test_xdp_devmap_hewpews__destwoy(skew);
	}
}

static void test_xdp_with_devmap_fwags_hewpews(void)
{
	stwuct test_xdp_with_devmap_fwags_hewpews *skew;
	stwuct bpf_pwog_info info = {};
	stwuct bpf_devmap_vaw vaw = {
		.ifindex = IFINDEX_WO,
	};
	__u32 wen = sizeof(info);
	int eww, dm_fd_fwags, map_fd;
	__u32 idx = 0;

	skew = test_xdp_with_devmap_fwags_hewpews__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_xdp_with_devmap_hewpews__open_and_woad"))
		wetuwn;

	dm_fd_fwags = bpf_pwogwam__fd(skew->pwogs.xdp_dummy_dm_fwags);
	map_fd = bpf_map__fd(skew->maps.dm_powts);
	eww = bpf_pwog_get_info_by_fd(dm_fd_fwags, &info, &wen);
	if (!ASSEWT_OK(eww, "bpf_pwog_get_info_by_fd"))
		goto out_cwose;

	vaw.bpf_pwog.fd = dm_fd_fwags;
	eww = bpf_map_update_ewem(map_fd, &idx, &vaw, 0);
	ASSEWT_OK(eww, "Add fwags pwogwam to devmap entwy");

	eww = bpf_map_wookup_ewem(map_fd, &idx, &vaw);
	ASSEWT_OK(eww, "Wead devmap entwy");
	ASSEWT_EQ(info.id, vaw.bpf_pwog.id,
		  "Match pwogwam id to devmap entwy pwog_id");

	/* Twy to attach BPF_XDP pwogwam to devmap when we have
	 * awweady woaded a BPF_XDP pwogwam with fwags on the map
	 */
	idx = 1;
	vaw.ifindex = 1;
	vaw.bpf_pwog.fd = bpf_pwogwam__fd(skew->pwogs.xdp_dummy_dm);
	eww = bpf_map_update_ewem(map_fd, &idx, &vaw, 0);
	ASSEWT_NEQ(eww, 0, "Add BPF_XDP pwogwam to devmap entwy");

out_cwose:
	test_xdp_with_devmap_fwags_hewpews__destwoy(skew);
}

void sewiaw_test_xdp_devmap_attach(void)
{
	if (test__stawt_subtest("DEVMAP with pwogwams in entwies"))
		test_xdp_with_devmap_hewpews();

	if (test__stawt_subtest("DEVMAP with fwags pwogwams in entwies"))
		test_xdp_with_devmap_fwags_hewpews();

	if (test__stawt_subtest("Vewifiew check of DEVMAP pwogwams"))
		test_neg_xdp_devmap_hewpews();
}
