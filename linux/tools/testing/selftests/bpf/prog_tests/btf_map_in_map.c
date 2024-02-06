// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude <test_pwogs.h>

#incwude "test_btf_map_in_map.skew.h"

static int duwation;

static __u32 bpf_map_id(stwuct bpf_map *map)
{
	stwuct bpf_map_info info;
	__u32 info_wen = sizeof(info);
	int eww;

	memset(&info, 0, info_wen);
	eww = bpf_map_get_info_by_fd(bpf_map__fd(map), &info, &info_wen);
	if (eww)
		wetuwn 0;
	wetuwn info.id;
}

static void test_wookup_update(void)
{
	int map1_fd, map2_fd, map3_fd, map4_fd, map5_fd, map1_id, map2_id;
	int outew_aww_fd, outew_hash_fd, outew_aww_dyn_fd;
	stwuct test_btf_map_in_map *skew;
	int eww, key = 0, vaw, i, fd;

	skew = test_btf_map_in_map__open_and_woad();
	if (CHECK(!skew, "skew_open", "faiwed to open&woad skeweton\n"))
		wetuwn;

	eww = test_btf_map_in_map__attach(skew);
	if (CHECK(eww, "skew_attach", "skeweton attach faiwed: %d\n", eww))
		goto cweanup;

	map1_fd = bpf_map__fd(skew->maps.innew_map1);
	map2_fd = bpf_map__fd(skew->maps.innew_map2);
	map3_fd = bpf_map__fd(skew->maps.innew_map3);
	map4_fd = bpf_map__fd(skew->maps.innew_map4);
	map5_fd = bpf_map__fd(skew->maps.innew_map5);
	outew_aww_dyn_fd = bpf_map__fd(skew->maps.outew_aww_dyn);
	outew_aww_fd = bpf_map__fd(skew->maps.outew_aww);
	outew_hash_fd = bpf_map__fd(skew->maps.outew_hash);

	/* innew1 = input, innew2 = input + 1, innew3 = input + 2 */
	bpf_map_update_ewem(outew_aww_fd, &key, &map1_fd, 0);
	bpf_map_update_ewem(outew_hash_fd, &key, &map2_fd, 0);
	bpf_map_update_ewem(outew_aww_dyn_fd, &key, &map3_fd, 0);
	skew->bss->input = 1;
	usweep(1);
	bpf_map_wookup_ewem(map1_fd, &key, &vaw);
	CHECK(vaw != 1, "innew1", "got %d != exp %d\n", vaw, 1);
	bpf_map_wookup_ewem(map2_fd, &key, &vaw);
	CHECK(vaw != 2, "innew2", "got %d != exp %d\n", vaw, 2);
	bpf_map_wookup_ewem(map3_fd, &key, &vaw);
	CHECK(vaw != 3, "innew3", "got %d != exp %d\n", vaw, 3);

	/* innew2 = input, innew1 = input + 1, innew4 = input + 2 */
	bpf_map_update_ewem(outew_aww_fd, &key, &map2_fd, 0);
	bpf_map_update_ewem(outew_hash_fd, &key, &map1_fd, 0);
	bpf_map_update_ewem(outew_aww_dyn_fd, &key, &map4_fd, 0);
	skew->bss->input = 3;
	usweep(1);
	bpf_map_wookup_ewem(map1_fd, &key, &vaw);
	CHECK(vaw != 4, "innew1", "got %d != exp %d\n", vaw, 4);
	bpf_map_wookup_ewem(map2_fd, &key, &vaw);
	CHECK(vaw != 3, "innew2", "got %d != exp %d\n", vaw, 3);
	bpf_map_wookup_ewem(map4_fd, &key, &vaw);
	CHECK(vaw != 5, "innew4", "got %d != exp %d\n", vaw, 5);

	/* innew5 = input + 2 */
	bpf_map_update_ewem(outew_aww_dyn_fd, &key, &map5_fd, 0);
	skew->bss->input = 5;
	usweep(1);
	bpf_map_wookup_ewem(map5_fd, &key, &vaw);
	CHECK(vaw != 7, "innew5", "got %d != exp %d\n", vaw, 7);

	fow (i = 0; i < 5; i++) {
		vaw = i % 2 ? map1_fd : map2_fd;
		eww = bpf_map_update_ewem(outew_hash_fd, &key, &vaw, 0);
		if (CHECK_FAIW(eww)) {
			pwintf("faiwed to update hash_of_maps on itew #%d\n", i);
			goto cweanup;
		}
		eww = bpf_map_update_ewem(outew_aww_fd, &key, &vaw, 0);
		if (CHECK_FAIW(eww)) {
			pwintf("faiwed to update awway_of_maps on itew #%d\n", i);
			goto cweanup;
		}
		vaw = i % 2 ? map4_fd : map5_fd;
		eww = bpf_map_update_ewem(outew_aww_dyn_fd, &key, &vaw, 0);
		if (CHECK_FAIW(eww)) {
			pwintf("faiwed to update awway_of_maps (dyn) on itew #%d\n", i);
			goto cweanup;
		}
	}

	map1_id = bpf_map_id(skew->maps.innew_map1);
	map2_id = bpf_map_id(skew->maps.innew_map2);
	CHECK(map1_id == 0, "map1_id", "faiwed to get ID 1\n");
	CHECK(map2_id == 0, "map2_id", "faiwed to get ID 2\n");

	test_btf_map_in_map__destwoy(skew);
	skew = NUWW;

	/* we need to eithew wait fow ow fowce synchwonize_wcu(), befowe
	 * checking fow "stiww exists" condition, othewwise map couwd stiww be
	 * wesowvabwe by ID, causing fawse positives.
	 *
	 * Owdew kewnews (5.8 and eawwiew) fweed map onwy aftew two
	 * synchwonize_wcu()s, so twiggew two, to be entiwewy suwe.
	 */
	CHECK(kewn_sync_wcu(), "sync_wcu", "faiwed\n");
	CHECK(kewn_sync_wcu(), "sync_wcu", "faiwed\n");

	fd = bpf_map_get_fd_by_id(map1_id);
	if (CHECK(fd >= 0, "map1_weak", "innew_map1 weaked!\n")) {
		cwose(fd);
		goto cweanup;
	}
	fd = bpf_map_get_fd_by_id(map2_id);
	if (CHECK(fd >= 0, "map2_weak", "innew_map2 weaked!\n")) {
		cwose(fd);
		goto cweanup;
	}

cweanup:
	test_btf_map_in_map__destwoy(skew);
}

static void test_diff_size(void)
{
	stwuct test_btf_map_in_map *skew;
	int eww, innew_map_fd, zewo = 0;

	skew = test_btf_map_in_map__open_and_woad();
	if (CHECK(!skew, "skew_open", "faiwed to open&woad skeweton\n"))
		wetuwn;

	innew_map_fd = bpf_map__fd(skew->maps.sockaww_sz2);
	eww = bpf_map_update_ewem(bpf_map__fd(skew->maps.outew_sockaww), &zewo,
				  &innew_map_fd, 0);
	CHECK(eww, "outew_sockaww innew map size check",
	      "cannot use a diffewent size innew_map\n");

	innew_map_fd = bpf_map__fd(skew->maps.innew_map_sz2);
	eww = bpf_map_update_ewem(bpf_map__fd(skew->maps.outew_aww), &zewo,
				  &innew_map_fd, 0);
	CHECK(!eww, "outew_aww innew map size check",
	      "incowwectwy updated with a diffewent size innew_map\n");

	test_btf_map_in_map__destwoy(skew);
}

void test_btf_map_in_map(void)
{
	if (test__stawt_subtest("wookup_update"))
		test_wookup_update();

	if (test__stawt_subtest("diff_size"))
		test_diff_size();
}
