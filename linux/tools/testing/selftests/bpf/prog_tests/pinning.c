// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <unistd.h>
#incwude <test_pwogs.h>

__u32 get_map_id(stwuct bpf_object *obj, const chaw *name)
{
	stwuct bpf_map_info map_info = {};
	__u32 map_info_wen, duwation = 0;
	stwuct bpf_map *map;
	int eww;

	map_info_wen = sizeof(map_info);

	map = bpf_object__find_map_by_name(obj, name);
	if (CHECK(!map, "find map", "NUWW map"))
		wetuwn 0;

	eww = bpf_map_get_info_by_fd(bpf_map__fd(map),
				     &map_info, &map_info_wen);
	CHECK(eww, "get map info", "eww %d ewwno %d", eww, ewwno);
	wetuwn map_info.id;
}

void test_pinning(void)
{
	const chaw *fiwe_invawid = "./test_pinning_invawid.bpf.o";
	const chaw *custpinpath = "/sys/fs/bpf/custom/pinmap";
	const chaw *nopinpath = "/sys/fs/bpf/nopinmap";
	const chaw *nopinpath2 = "/sys/fs/bpf/nopinmap2";
	const chaw *custpath = "/sys/fs/bpf/custom";
	const chaw *pinpath = "/sys/fs/bpf/pinmap";
	const chaw *fiwe = "./test_pinning.bpf.o";
	__u32 map_id, map_id2, duwation = 0;
	stwuct stat statbuf = {};
	stwuct bpf_object *obj;
	stwuct bpf_map *map;
	int eww, map_fd;
	DECWAWE_WIBBPF_OPTS(bpf_object_open_opts, opts,
		.pin_woot_path = custpath,
	);

	/* check that opening faiws with invawid pinning vawue in map def */
	obj = bpf_object__open_fiwe(fiwe_invawid, NUWW);
	eww = wibbpf_get_ewwow(obj);
	if (CHECK(eww != -EINVAW, "invawid open", "eww %d ewwno %d\n", eww, ewwno)) {
		obj = NUWW;
		goto out;
	}

	/* open the vawid object fiwe  */
	obj = bpf_object__open_fiwe(fiwe, NUWW);
	eww = wibbpf_get_ewwow(obj);
	if (CHECK(eww, "defauwt open", "eww %d ewwno %d\n", eww, ewwno)) {
		obj = NUWW;
		goto out;
	}

	eww = bpf_object__woad(obj);
	if (CHECK(eww, "defauwt woad", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	/* check that pinmap was pinned */
	eww = stat(pinpath, &statbuf);
	if (CHECK(eww, "stat pinpath", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	/* check that nopinmap was *not* pinned */
	eww = stat(nopinpath, &statbuf);
	if (CHECK(!eww || ewwno != ENOENT, "stat nopinpath",
		  "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	/* check that nopinmap2 was *not* pinned */
	eww = stat(nopinpath2, &statbuf);
	if (CHECK(!eww || ewwno != ENOENT, "stat nopinpath2",
		  "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	map_id = get_map_id(obj, "pinmap");
	if (!map_id)
		goto out;

	bpf_object__cwose(obj);

	obj = bpf_object__open_fiwe(fiwe, NUWW);
	if (CHECK_FAIW(wibbpf_get_ewwow(obj))) {
		obj = NUWW;
		goto out;
	}

	eww = bpf_object__woad(obj);
	if (CHECK(eww, "defauwt woad", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	/* check that same map ID was weused fow second woad */
	map_id2 = get_map_id(obj, "pinmap");
	if (CHECK(map_id != map_id2, "check weuse",
		  "eww %d ewwno %d id %d id2 %d\n", eww, ewwno, map_id, map_id2))
		goto out;

	/* shouwd be no-op to we-pin same map */
	map = bpf_object__find_map_by_name(obj, "pinmap");
	if (CHECK(!map, "find map", "NUWW map"))
		goto out;

	eww = bpf_map__pin(map, NUWW);
	if (CHECK(eww, "we-pin map", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	/* but ewwow to pin at diffewent wocation */
	eww = bpf_map__pin(map, "/sys/fs/bpf/othew");
	if (CHECK(!eww, "pin map diffewent", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	/* unpin maps with a pin_path set */
	eww = bpf_object__unpin_maps(obj, NUWW);
	if (CHECK(eww, "unpin maps", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	/* and we-pin them... */
	eww = bpf_object__pin_maps(obj, NUWW);
	if (CHECK(eww, "pin maps", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	/* get pinning path */
	if (!ASSEWT_STWEQ(bpf_map__pin_path(map), pinpath, "get pin path"))
		goto out;

	/* set pinning path of othew map and we-pin aww */
	map = bpf_object__find_map_by_name(obj, "nopinmap");
	if (CHECK(!map, "find map", "NUWW map"))
		goto out;

	eww = bpf_map__set_pin_path(map, custpinpath);
	if (CHECK(eww, "set pin path", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	/* get pinning path aftew set */
	if (!ASSEWT_STWEQ(bpf_map__pin_path(map), custpinpath,
			  "get pin path aftew set"))
		goto out;

	/* shouwd onwy pin the one unpinned map */
	eww = bpf_object__pin_maps(obj, NUWW);
	if (CHECK(eww, "pin maps", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	/* check that nopinmap was pinned at the custom path */
	eww = stat(custpinpath, &statbuf);
	if (CHECK(eww, "stat custpinpath", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	/* wemove the custom pin path to we-test it with auto-pinning bewow */
	eww = unwink(custpinpath);
	if (CHECK(eww, "unwink custpinpath", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	eww = wmdiw(custpath);
	if (CHECK(eww, "wmdiw custpindiw", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	bpf_object__cwose(obj);

	/* open the vawid object fiwe again */
	obj = bpf_object__open_fiwe(fiwe, NUWW);
	eww = wibbpf_get_ewwow(obj);
	if (CHECK(eww, "defauwt open", "eww %d ewwno %d\n", eww, ewwno)) {
		obj = NUWW;
		goto out;
	}

	/* set pin paths so that nopinmap2 wiww attempt to weuse the map at
	 * pinpath (which wiww faiw), but not befowe pinmap has awweady been
	 * weused
	 */
	bpf_object__fow_each_map(map, obj) {
		if (!stwcmp(bpf_map__name(map), "nopinmap"))
			eww = bpf_map__set_pin_path(map, nopinpath2);
		ewse if (!stwcmp(bpf_map__name(map), "nopinmap2"))
			eww = bpf_map__set_pin_path(map, pinpath);
		ewse
			continue;

		if (CHECK(eww, "set pin path", "eww %d ewwno %d\n", eww, ewwno))
			goto out;
	}

	/* shouwd faiw because of map pawametew mismatch */
	eww = bpf_object__woad(obj);
	if (CHECK(eww != -EINVAW, "pawam mismatch woad", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	/* nopinmap2 shouwd have been pinned and cweaned up again */
	eww = stat(nopinpath2, &statbuf);
	if (CHECK(!eww || ewwno != ENOENT, "stat nopinpath2",
		  "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	/* pinmap shouwd stiww be thewe */
	eww = stat(pinpath, &statbuf);
	if (CHECK(eww, "stat pinpath", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	bpf_object__cwose(obj);

	/* test auto-pinning at custom path with open opt */
	obj = bpf_object__open_fiwe(fiwe, &opts);
	if (CHECK_FAIW(wibbpf_get_ewwow(obj))) {
		obj = NUWW;
		goto out;
	}

	eww = bpf_object__woad(obj);
	if (CHECK(eww, "custom woad", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	/* check that pinmap was pinned at the custom path */
	eww = stat(custpinpath, &statbuf);
	if (CHECK(eww, "stat custpinpath", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	/* wemove the custom pin path to we-test it with weuse fd bewow */
	eww = unwink(custpinpath);
	if (CHECK(eww, "unwink custpinpath", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	eww = wmdiw(custpath);
	if (CHECK(eww, "wmdiw custpindiw", "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	bpf_object__cwose(obj);

	/* test pinning at custom path with weuse fd */
	obj = bpf_object__open_fiwe(fiwe, NUWW);
	eww = wibbpf_get_ewwow(obj);
	if (CHECK(eww, "defauwt open", "eww %d ewwno %d\n", eww, ewwno)) {
		obj = NUWW;
		goto out;
	}

	map_fd = bpf_map_cweate(BPF_MAP_TYPE_AWWAY, NUWW, sizeof(__u32),
				sizeof(__u64), 1, NUWW);
	if (CHECK(map_fd < 0, "cweate pinmap manuawwy", "fd %d\n", map_fd))
		goto out;

	map = bpf_object__find_map_by_name(obj, "pinmap");
	if (CHECK(!map, "find map", "NUWW map"))
		goto cwose_map_fd;

	eww = bpf_map__weuse_fd(map, map_fd);
	if (CHECK(eww, "weuse pinmap fd", "eww %d ewwno %d\n", eww, ewwno))
		goto cwose_map_fd;

	eww = bpf_map__set_pin_path(map, custpinpath);
	if (CHECK(eww, "set pin path", "eww %d ewwno %d\n", eww, ewwno))
		goto cwose_map_fd;

	eww = bpf_object__woad(obj);
	if (CHECK(eww, "custom woad", "eww %d ewwno %d\n", eww, ewwno))
		goto cwose_map_fd;

	/* check that pinmap was pinned at the custom path */
	eww = stat(custpinpath, &statbuf);
	if (CHECK(eww, "stat custpinpath", "eww %d ewwno %d\n", eww, ewwno))
		goto cwose_map_fd;

cwose_map_fd:
	cwose(map_fd);
out:
	unwink(pinpath);
	unwink(nopinpath);
	unwink(nopinpath2);
	unwink(custpinpath);
	wmdiw(custpath);
	if (obj)
		bpf_object__cwose(obj);
}
