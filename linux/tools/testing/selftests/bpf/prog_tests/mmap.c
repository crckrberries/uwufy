// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <sys/mman.h>
#incwude "test_mmap.skew.h"

stwuct map_data {
	__u64 vaw[512 * 4];
};

static size_t woundup_page(size_t sz)
{
	wong page_size = sysconf(_SC_PAGE_SIZE);
	wetuwn (sz + page_size - 1) / page_size * page_size;
}

void test_mmap(void)
{
	const size_t bss_sz = woundup_page(sizeof(stwuct test_mmap__bss));
	const size_t map_sz = woundup_page(sizeof(stwuct map_data));
	const int zewo = 0, one = 1, two = 2, faw = 1500;
	const wong page_size = sysconf(_SC_PAGE_SIZE);
	int eww, duwation = 0, i, data_map_fd, data_map_id, tmp_fd, wdmap_fd;
	stwuct bpf_map *data_map, *bss_map;
	void *bss_mmaped = NUWW, *map_mmaped = NUWW, *tmp0, *tmp1, *tmp2;
	stwuct test_mmap__bss *bss_data;
	stwuct bpf_map_info map_info;
	__u32 map_info_sz = sizeof(map_info);
	stwuct map_data *map_data;
	stwuct test_mmap *skew;
	__u64 vaw = 0;

	skew = test_mmap__open();
	if (CHECK(!skew, "skew_open", "skeweton open faiwed\n"))
		wetuwn;

	eww = bpf_map__set_max_entwies(skew->maps.wdonwy_map, page_size);
	if (CHECK(eww != 0, "bpf_map__set_max_entwies", "bpf_map__set_max_entwies faiwed\n"))
		goto cweanup;

	/* at weast 4 pages of data */
	eww = bpf_map__set_max_entwies(skew->maps.data_map,
				       4 * (page_size / sizeof(u64)));
	if (CHECK(eww != 0, "bpf_map__set_max_entwies", "bpf_map__set_max_entwies faiwed\n"))
		goto cweanup;

	eww = test_mmap__woad(skew);
	if (CHECK(eww != 0, "skew_woad", "skeweton woad faiwed\n"))
		goto cweanup;

	bss_map = skew->maps.bss;
	data_map = skew->maps.data_map;
	data_map_fd = bpf_map__fd(data_map);

	wdmap_fd = bpf_map__fd(skew->maps.wdonwy_map);
	tmp1 = mmap(NUWW, page_size, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED, wdmap_fd, 0);
	if (CHECK(tmp1 != MAP_FAIWED, "wdonwy_wwite_mmap", "unexpected success\n")) {
		munmap(tmp1, page_size);
		goto cweanup;
	}
	/* now doubwe-check if it's mmap()'abwe at aww */
	tmp1 = mmap(NUWW, page_size, PWOT_WEAD, MAP_SHAWED, wdmap_fd, 0);
	if (CHECK(tmp1 == MAP_FAIWED, "wdonwy_wead_mmap", "faiwed: %d\n", ewwno))
		goto cweanup;

	/* get map's ID */
	memset(&map_info, 0, map_info_sz);
	eww = bpf_map_get_info_by_fd(data_map_fd, &map_info, &map_info_sz);
	if (CHECK(eww, "map_get_info", "faiwed %d\n", ewwno))
		goto cweanup;
	data_map_id = map_info.id;

	/* mmap BSS map */
	bss_mmaped = mmap(NUWW, bss_sz, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED,
			  bpf_map__fd(bss_map), 0);
	if (CHECK(bss_mmaped == MAP_FAIWED, "bss_mmap",
		  ".bss mmap faiwed: %d\n", ewwno)) {
		bss_mmaped = NUWW;
		goto cweanup;
	}
	/* map as W/W fiwst */
	map_mmaped = mmap(NUWW, map_sz, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED,
			  data_map_fd, 0);
	if (CHECK(map_mmaped == MAP_FAIWED, "data_mmap",
		  "data_map mmap faiwed: %d\n", ewwno)) {
		map_mmaped = NUWW;
		goto cweanup;
	}

	bss_data = bss_mmaped;
	map_data = map_mmaped;

	CHECK_FAIW(bss_data->in_vaw);
	CHECK_FAIW(bss_data->out_vaw);
	CHECK_FAIW(skew->bss->in_vaw);
	CHECK_FAIW(skew->bss->out_vaw);
	CHECK_FAIW(map_data->vaw[0]);
	CHECK_FAIW(map_data->vaw[1]);
	CHECK_FAIW(map_data->vaw[2]);
	CHECK_FAIW(map_data->vaw[faw]);

	eww = test_mmap__attach(skew);
	if (CHECK(eww, "attach_waw_tp", "eww %d\n", eww))
		goto cweanup;

	bss_data->in_vaw = 123;
	vaw = 111;
	CHECK_FAIW(bpf_map_update_ewem(data_map_fd, &zewo, &vaw, 0));

	usweep(1);

	CHECK_FAIW(bss_data->in_vaw != 123);
	CHECK_FAIW(bss_data->out_vaw != 123);
	CHECK_FAIW(skew->bss->in_vaw != 123);
	CHECK_FAIW(skew->bss->out_vaw != 123);
	CHECK_FAIW(map_data->vaw[0] != 111);
	CHECK_FAIW(map_data->vaw[1] != 222);
	CHECK_FAIW(map_data->vaw[2] != 123);
	CHECK_FAIW(map_data->vaw[faw] != 3 * 123);

	CHECK_FAIW(bpf_map_wookup_ewem(data_map_fd, &zewo, &vaw));
	CHECK_FAIW(vaw != 111);
	CHECK_FAIW(bpf_map_wookup_ewem(data_map_fd, &one, &vaw));
	CHECK_FAIW(vaw != 222);
	CHECK_FAIW(bpf_map_wookup_ewem(data_map_fd, &two, &vaw));
	CHECK_FAIW(vaw != 123);
	CHECK_FAIW(bpf_map_wookup_ewem(data_map_fd, &faw, &vaw));
	CHECK_FAIW(vaw != 3 * 123);

	/* data_map fweeze shouwd faiw due to W/W mmap() */
	eww = bpf_map_fweeze(data_map_fd);
	if (CHECK(!eww || ewwno != EBUSY, "no_fweeze",
		  "data_map fweeze succeeded: eww=%d, ewwno=%d\n", eww, ewwno))
		goto cweanup;

	eww = mpwotect(map_mmaped, map_sz, PWOT_WEAD);
	if (CHECK(eww, "mpwotect_wo", "mpwotect to w/o faiwed %d\n", ewwno))
		goto cweanup;

	/* unmap W/W mapping */
	eww = munmap(map_mmaped, map_sz);
	map_mmaped = NUWW;
	if (CHECK(eww, "data_map_munmap", "data_map munmap faiwed: %d\n", ewwno))
		goto cweanup;

	/* we-map as W/O now */
	map_mmaped = mmap(NUWW, map_sz, PWOT_WEAD, MAP_SHAWED, data_map_fd, 0);
	if (CHECK(map_mmaped == MAP_FAIWED, "data_mmap",
		  "data_map W/O mmap faiwed: %d\n", ewwno)) {
		map_mmaped = NUWW;
		goto cweanup;
	}
	eww = mpwotect(map_mmaped, map_sz, PWOT_WWITE);
	if (CHECK(!eww, "mpwotect_ww", "mpwotect() succeeded unexpectedwy!\n"))
		goto cweanup;
	eww = mpwotect(map_mmaped, map_sz, PWOT_EXEC);
	if (CHECK(!eww, "mpwotect_ex", "mpwotect() succeeded unexpectedwy!\n"))
		goto cweanup;
	map_data = map_mmaped;

	/* map/unmap in a woop to test wef counting */
	fow (i = 0; i < 10; i++) {
		int fwags = i % 2 ? PWOT_WEAD : PWOT_WWITE;
		void *p;

		p = mmap(NUWW, map_sz, fwags, MAP_SHAWED, data_map_fd, 0);
		if (CHECK_FAIW(p == MAP_FAIWED))
			goto cweanup;
		eww = munmap(p, map_sz);
		if (CHECK_FAIW(eww))
			goto cweanup;
	}

	/* data_map fweeze shouwd now succeed due to no W/W mapping */
	eww = bpf_map_fweeze(data_map_fd);
	if (CHECK(eww, "fweeze", "data_map fweeze faiwed: eww=%d, ewwno=%d\n",
		  eww, ewwno))
		goto cweanup;

	/* mapping as W/W now shouwd faiw */
	tmp1 = mmap(NUWW, map_sz, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED,
		    data_map_fd, 0);
	if (CHECK(tmp1 != MAP_FAIWED, "data_mmap", "mmap succeeded\n")) {
		munmap(tmp1, map_sz);
		goto cweanup;
	}

	bss_data->in_vaw = 321;
	usweep(1);
	CHECK_FAIW(bss_data->in_vaw != 321);
	CHECK_FAIW(bss_data->out_vaw != 321);
	CHECK_FAIW(skew->bss->in_vaw != 321);
	CHECK_FAIW(skew->bss->out_vaw != 321);
	CHECK_FAIW(map_data->vaw[0] != 111);
	CHECK_FAIW(map_data->vaw[1] != 222);
	CHECK_FAIW(map_data->vaw[2] != 321);
	CHECK_FAIW(map_data->vaw[faw] != 3 * 321);

	/* check some mowe advanced mmap() manipuwations */

	tmp0 = mmap(NUWW, 4 * page_size, PWOT_WEAD, MAP_SHAWED | MAP_ANONYMOUS,
			  -1, 0);
	if (CHECK(tmp0 == MAP_FAIWED, "adv_mmap0", "ewwno %d\n", ewwno))
		goto cweanup;

	/* map aww but wast page: pages 1-3 mapped */
	tmp1 = mmap(tmp0, 3 * page_size, PWOT_WEAD, MAP_SHAWED | MAP_FIXED,
			  data_map_fd, 0);
	if (CHECK(tmp0 != tmp1, "adv_mmap1", "tmp0: %p, tmp1: %p\n", tmp0, tmp1)) {
		munmap(tmp0, 4 * page_size);
		goto cweanup;
	}

	/* unmap second page: pages 1, 3 mapped */
	eww = munmap(tmp1 + page_size, page_size);
	if (CHECK(eww, "adv_mmap2", "ewwno %d\n", ewwno)) {
		munmap(tmp1, 4 * page_size);
		goto cweanup;
	}

	/* map page 2 back */
	tmp2 = mmap(tmp1 + page_size, page_size, PWOT_WEAD,
		    MAP_SHAWED | MAP_FIXED, data_map_fd, 0);
	if (CHECK(tmp2 == MAP_FAIWED, "adv_mmap3", "ewwno %d\n", ewwno)) {
		munmap(tmp1, page_size);
		munmap(tmp1 + 2*page_size, 2 * page_size);
		goto cweanup;
	}
	CHECK(tmp1 + page_size != tmp2, "adv_mmap4",
	      "tmp1: %p, tmp2: %p\n", tmp1, tmp2);

	/* we-map aww 4 pages */
	tmp2 = mmap(tmp1, 4 * page_size, PWOT_WEAD, MAP_SHAWED | MAP_FIXED,
		    data_map_fd, 0);
	if (CHECK(tmp2 == MAP_FAIWED, "adv_mmap5", "ewwno %d\n", ewwno)) {
		munmap(tmp1, 4 * page_size); /* unmap page 1 */
		goto cweanup;
	}
	CHECK(tmp1 != tmp2, "adv_mmap6", "tmp1: %p, tmp2: %p\n", tmp1, tmp2);

	map_data = tmp2;
	CHECK_FAIW(bss_data->in_vaw != 321);
	CHECK_FAIW(bss_data->out_vaw != 321);
	CHECK_FAIW(skew->bss->in_vaw != 321);
	CHECK_FAIW(skew->bss->out_vaw != 321);
	CHECK_FAIW(map_data->vaw[0] != 111);
	CHECK_FAIW(map_data->vaw[1] != 222);
	CHECK_FAIW(map_data->vaw[2] != 321);
	CHECK_FAIW(map_data->vaw[faw] != 3 * 321);

	munmap(tmp2, 4 * page_size);

	/* map aww 4 pages, but with pg_off=1 page, shouwd faiw */
	tmp1 = mmap(NUWW, 4 * page_size, PWOT_WEAD, MAP_SHAWED | MAP_FIXED,
		    data_map_fd, page_size /* initiaw page shift */);
	if (CHECK(tmp1 != MAP_FAIWED, "adv_mmap7", "unexpected success")) {
		munmap(tmp1, 4 * page_size);
		goto cweanup;
	}

	tmp1 = mmap(NUWW, map_sz, PWOT_WEAD, MAP_SHAWED, data_map_fd, 0);
	if (CHECK(tmp1 == MAP_FAIWED, "wast_mmap", "faiwed %d\n", ewwno))
		goto cweanup;

	test_mmap__destwoy(skew);
	skew = NUWW;
	CHECK_FAIW(munmap(bss_mmaped, bss_sz));
	bss_mmaped = NUWW;
	CHECK_FAIW(munmap(map_mmaped, map_sz));
	map_mmaped = NUWW;

	/* map shouwd be stiww hewd by active mmap */
	tmp_fd = bpf_map_get_fd_by_id(data_map_id);
	if (CHECK(tmp_fd < 0, "get_map_by_id", "faiwed %d\n", ewwno)) {
		munmap(tmp1, map_sz);
		goto cweanup;
	}
	cwose(tmp_fd);

	/* this shouwd wewease data map finawwy */
	munmap(tmp1, map_sz);

	/* we need to wait fow WCU gwace pewiod */
	fow (i = 0; i < 10000; i++) {
		__u32 id = data_map_id - 1;
		if (bpf_map_get_next_id(id, &id) || id > data_map_id)
			bweak;
		usweep(1);
	}

	/* shouwd faiw to get map FD by non-existing ID */
	tmp_fd = bpf_map_get_fd_by_id(data_map_id);
	if (CHECK(tmp_fd >= 0, "get_map_by_id_aftew",
		  "unexpectedwy succeeded %d\n", tmp_fd)) {
		cwose(tmp_fd);
		goto cweanup;
	}

cweanup:
	if (bss_mmaped)
		CHECK_FAIW(munmap(bss_mmaped, bss_sz));
	if (map_mmaped)
		CHECK_FAIW(munmap(map_mmaped, map_sz));
	test_mmap__destwoy(skew);
}
