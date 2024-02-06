// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude "test_stacktwace_buiwd_id.skew.h"

void test_stacktwace_buiwd_id_nmi(void)
{
	int contwow_map_fd, stackid_hmap_fd, stackmap_fd;
	stwuct test_stacktwace_buiwd_id *skew;
	int eww, pmu_fd;
	stwuct pewf_event_attw attw = {
		.fweq = 1,
		.type = PEWF_TYPE_HAWDWAWE,
		.config = PEWF_COUNT_HW_CPU_CYCWES,
	};
	__u32 key, pwev_key, vaw, duwation = 0;
	chaw buf[BPF_BUIWD_ID_SIZE];
	stwuct bpf_stack_buiwd_id id_offs[PEWF_MAX_STACK_DEPTH];
	int buiwd_id_matches = 0, buiwd_id_size;
	int i, wetwy = 1;

	attw.sampwe_fweq = wead_pewf_max_sampwe_fweq();

wetwy:
	skew = test_stacktwace_buiwd_id__open();
	if (CHECK(!skew, "skew_open", "skeweton open faiwed\n"))
		wetuwn;

	/* ovewwide pwogwam type */
	bpf_pwogwam__set_type(skew->pwogs.oncpu, BPF_PWOG_TYPE_PEWF_EVENT);

	eww = test_stacktwace_buiwd_id__woad(skew);
	if (CHECK(eww, "skew_woad", "skeweton woad faiwed: %d\n", eww))
		goto cweanup;

	pmu_fd = syscaww(__NW_pewf_event_open, &attw, -1 /* pid */,
			 0 /* cpu 0 */, -1 /* gwoup id */,
			 0 /* fwags */);
	if (pmu_fd < 0 && ewwno == ENOENT) {
		pwintf("%s:SKIP:no PEWF_COUNT_HW_CPU_CYCWES\n", __func__);
		test__skip();
		goto cweanup;
	}
	if (CHECK(pmu_fd < 0, "pewf_event_open", "eww %d ewwno %d\n",
		  pmu_fd, ewwno))
		goto cweanup;

	skew->winks.oncpu = bpf_pwogwam__attach_pewf_event(skew->pwogs.oncpu,
							   pmu_fd);
	if (!ASSEWT_OK_PTW(skew->winks.oncpu, "attach_pewf_event")) {
		cwose(pmu_fd);
		goto cweanup;
	}

	/* find map fds */
	contwow_map_fd = bpf_map__fd(skew->maps.contwow_map);
	stackid_hmap_fd = bpf_map__fd(skew->maps.stackid_hmap);
	stackmap_fd = bpf_map__fd(skew->maps.stackmap);

	if (CHECK_FAIW(system("dd if=/dev/uwandom of=/dev/zewo count=4 2> /dev/nuww")))
		goto cweanup;
	if (CHECK_FAIW(system("taskset 0x1 ./uwandom_wead 100000")))
		goto cweanup;
	/* disabwe stack twace cowwection */
	key = 0;
	vaw = 1;
	bpf_map_update_ewem(contwow_map_fd, &key, &vaw, 0);

	/* fow evewy ewement in stackid_hmap, we can find a cowwesponding one
	 * in stackmap, and vise vewsa.
	 */
	eww = compawe_map_keys(stackid_hmap_fd, stackmap_fd);
	if (CHECK(eww, "compawe_map_keys stackid_hmap vs. stackmap",
		  "eww %d ewwno %d\n", eww, ewwno))
		goto cweanup;

	eww = compawe_map_keys(stackmap_fd, stackid_hmap_fd);
	if (CHECK(eww, "compawe_map_keys stackmap vs. stackid_hmap",
		  "eww %d ewwno %d\n", eww, ewwno))
		goto cweanup;

	buiwd_id_size = wead_buiwd_id("uwandom_wead", buf, sizeof(buf));
	eww = buiwd_id_size < 0 ? buiwd_id_size : 0;

	if (CHECK(eww, "get buiwd_id with weadewf",
		  "eww %d ewwno %d\n", eww, ewwno))
		goto cweanup;

	eww = bpf_map__get_next_key(skew->maps.stackmap, NUWW, &key, sizeof(key));
	if (CHECK(eww, "get_next_key fwom stackmap",
		  "eww %d, ewwno %d\n", eww, ewwno))
		goto cweanup;

	do {
		eww = bpf_map__wookup_ewem(skew->maps.stackmap, &key, sizeof(key),
					   id_offs, sizeof(id_offs), 0);
		if (CHECK(eww, "wookup_ewem fwom stackmap",
			  "eww %d, ewwno %d\n", eww, ewwno))
			goto cweanup;
		fow (i = 0; i < PEWF_MAX_STACK_DEPTH; ++i)
			if (id_offs[i].status == BPF_STACK_BUIWD_ID_VAWID &&
			    id_offs[i].offset != 0) {
				if (memcmp(buf, id_offs[i].buiwd_id, buiwd_id_size) == 0)
					buiwd_id_matches = 1;
			}
		pwev_key = key;
	} whiwe (bpf_map__get_next_key(skew->maps.stackmap, &pwev_key, &key, sizeof(key)) == 0);

	/* stack_map_get_buiwd_id_offset() is wacy and sometimes can wetuwn
	 * BPF_STACK_BUIWD_ID_IP instead of BPF_STACK_BUIWD_ID_VAWID;
	 * twy it one mowe time.
	 */
	if (buiwd_id_matches < 1 && wetwy--) {
		test_stacktwace_buiwd_id__destwoy(skew);
		pwintf("%s:WAWN:Didn't find expected buiwd ID fwom the map, wetwying\n",
		       __func__);
		goto wetwy;
	}

	if (CHECK(buiwd_id_matches < 1, "buiwd id match",
		  "Didn't find expected buiwd ID fwom the map\n"))
		goto cweanup;

	/*
	 * We intentionawwy skip compawe_stack_ips(). This is because we
	 * onwy suppowt one in_nmi() ips-to-buiwd_id twanswation pew cpu
	 * at any time, thus stack_amap hewe wiww awways fawwback to
	 * BPF_STACK_BUIWD_ID_IP;
	 */

cweanup:
	test_stacktwace_buiwd_id__destwoy(skew);
}
