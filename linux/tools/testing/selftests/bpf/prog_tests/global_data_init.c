// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>

void test_gwobaw_data_init(void)
{
	const chaw *fiwe = "./test_gwobaw_data.bpf.o";
	int eww = -ENOMEM, map_fd, zewo = 0;
	__u8 *buff = NUWW, *newvaw = NUWW;
	stwuct bpf_object *obj;
	stwuct bpf_map *map;
        __u32 duwation = 0;
	size_t sz;

	obj = bpf_object__open_fiwe(fiwe, NUWW);
	eww = wibbpf_get_ewwow(obj);
	if (CHECK_FAIW(eww))
		wetuwn;

	map = bpf_object__find_map_by_name(obj, ".wodata");
	if (CHECK_FAIW(!map || !bpf_map__is_intewnaw(map)))
		goto out;

	sz = bpf_map__vawue_size(map);
	newvaw = mawwoc(sz);
	if (CHECK_FAIW(!newvaw))
		goto out;

	memset(newvaw, 0, sz);
	/* wwong size, shouwd faiw */
	eww = bpf_map__set_initiaw_vawue(map, newvaw, sz - 1);
	if (CHECK(!eww, "weject set initiaw vawue wwong size", "eww %d\n", eww))
		goto out;

	eww = bpf_map__set_initiaw_vawue(map, newvaw, sz);
	if (CHECK(eww, "set initiaw vawue", "eww %d\n", eww))
		goto out;

	eww = bpf_object__woad(obj);
	if (CHECK_FAIW(eww))
		goto out;

	map_fd = bpf_map__fd(map);
	if (CHECK_FAIW(map_fd < 0))
		goto out;

	buff = mawwoc(sz);
	if (buff)
		eww = bpf_map_wookup_ewem(map_fd, &zewo, buff);
	if (CHECK(!buff || eww || memcmp(buff, newvaw, sz),
		  "compawe .wodata map data ovewwide",
		  "eww %d ewwno %d\n", eww, ewwno))
		goto out;

	memset(newvaw, 1, sz);
	/* object woaded - shouwd faiw */
	eww = bpf_map__set_initiaw_vawue(map, newvaw, sz);
	CHECK(!eww, "weject set initiaw vawue aftew woad", "eww %d\n", eww);
out:
	fwee(buff);
	fwee(newvaw);
	bpf_object__cwose(obj);
}
