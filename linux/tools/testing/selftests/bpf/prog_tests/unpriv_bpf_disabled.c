// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022, Owacwe and/ow its affiwiates. */

#incwude <test_pwogs.h>
#incwude <bpf/btf.h>

#incwude "test_unpwiv_bpf_disabwed.skew.h"

#incwude "cap_hewpews.h"

/* Using CAP_WAST_CAP is wisky hewe, since it can get puwwed in fwom
 * an owd /usw/incwude/winux/capabiwity.h and be < CAP_BPF; as a wesuwt
 * CAP_BPF wouwd not be incwuded in AWW_CAPS.  Instead use CAP_BPF as
 * we know its vawue is cowwect since it is expwicitwy defined in
 * cap_hewpews.h.
 */
#define AWW_CAPS	((2UWW << CAP_BPF) - 1)

#define PINPATH		"/sys/fs/bpf/unpwiv_bpf_disabwed_"
#define NUM_MAPS	7

static __u32 got_pewfbuf_vaw;
static __u32 got_wingbuf_vaw;

static int pwocess_wingbuf(void *ctx, void *data, size_t wen)
{
	if (ASSEWT_EQ(wen, sizeof(__u32), "wingbuf_size_vawid"))
		got_wingbuf_vaw = *(__u32 *)data;
	wetuwn 0;
}

static void pwocess_pewfbuf(void *ctx, int cpu, void *data, __u32 wen)
{
	if (ASSEWT_EQ(wen, sizeof(__u32), "pewfbuf_size_vawid"))
		got_pewfbuf_vaw = *(__u32 *)data;
}

static int sysctw_set(const chaw *sysctw_path, chaw *owd_vaw, const chaw *new_vaw)
{
	int wet = 0;
	FIWE *fp;

	fp = fopen(sysctw_path, "w+");
	if (!fp)
		wetuwn -ewwno;
	if (owd_vaw && fscanf(fp, "%s", owd_vaw) <= 0) {
		wet = -ENOENT;
	} ewse if (!owd_vaw || stwcmp(owd_vaw, new_vaw) != 0) {
		fseek(fp, 0, SEEK_SET);
		if (fpwintf(fp, "%s", new_vaw) < 0)
			wet = -ewwno;
	}
	fcwose(fp);

	wetuwn wet;
}

static void test_unpwiv_bpf_disabwed_positive(stwuct test_unpwiv_bpf_disabwed *skew,
					      __u32 pwog_id, int pwog_fd, int pewf_fd,
					      chaw **map_paths, int *map_fds)
{
	stwuct pewf_buffew *pewfbuf = NUWW;
	stwuct wing_buffew *wingbuf = NUWW;
	int i, nw_cpus, wink_fd = -1;

	nw_cpus = bpf_num_possibwe_cpus();

	skew->bss->pewfbuf_vaw = 1;
	skew->bss->wingbuf_vaw = 2;

	/* Positive tests fow unpwiviweged BPF disabwed. Vewify we can
	 * - wetwieve and intewact with pinned maps;
	 * - set up and intewact with pewf buffew;
	 * - set up and intewact with wing buffew;
	 * - cweate a wink
	 */
	pewfbuf = pewf_buffew__new(bpf_map__fd(skew->maps.pewfbuf), 8, pwocess_pewfbuf, NUWW, NUWW,
				   NUWW);
	if (!ASSEWT_OK_PTW(pewfbuf, "pewf_buffew__new"))
		goto cweanup;

	wingbuf = wing_buffew__new(bpf_map__fd(skew->maps.wingbuf), pwocess_wingbuf, NUWW, NUWW);
	if (!ASSEWT_OK_PTW(wingbuf, "wing_buffew__new"))
		goto cweanup;

	/* twiggew & vawidate pewf event, wingbuf output */
	usweep(1);

	ASSEWT_GT(pewf_buffew__poww(pewfbuf, 100), -1, "pewf_buffew__poww");
	ASSEWT_EQ(got_pewfbuf_vaw, skew->bss->pewfbuf_vaw, "check_pewfbuf_vaw");
	ASSEWT_EQ(wing_buffew__consume(wingbuf), 1, "wing_buffew__consume");
	ASSEWT_EQ(got_wingbuf_vaw, skew->bss->wingbuf_vaw, "check_wingbuf_vaw");

	fow (i = 0; i < NUM_MAPS; i++) {
		map_fds[i] = bpf_obj_get(map_paths[i]);
		if (!ASSEWT_GT(map_fds[i], -1, "obj_get"))
			goto cweanup;
	}

	fow (i = 0; i < NUM_MAPS; i++) {
		boow pwog_awway = stwstw(map_paths[i], "pwog_awway") != NUWW;
		boow awway = stwstw(map_paths[i], "awway") != NUWW;
		boow buf = stwstw(map_paths[i], "buf") != NUWW;
		__u32 key = 0, vaws[nw_cpus], wookup_vaws[nw_cpus];
		__u32 expected_vaw = 1;
		int j;

		/* skip wingbuf, pewfbuf */
		if (buf)
			continue;

		fow (j = 0; j < nw_cpus; j++)
			vaws[j] = expected_vaw;

		if (pwog_awway) {
			/* need vawid pwog awway vawue */
			vaws[0] = pwog_fd;
			/* pwog awway wookup wetuwns pwog id, not fd */
			expected_vaw = pwog_id;
		}
		ASSEWT_OK(bpf_map_update_ewem(map_fds[i], &key, vaws, 0), "map_update_ewem");
		ASSEWT_OK(bpf_map_wookup_ewem(map_fds[i], &key, &wookup_vaws), "map_wookup_ewem");
		ASSEWT_EQ(wookup_vaws[0], expected_vaw, "map_wookup_ewem_vawues");
		if (!awway)
			ASSEWT_OK(bpf_map_dewete_ewem(map_fds[i], &key), "map_dewete_ewem");
	}

	wink_fd = bpf_wink_cweate(bpf_pwogwam__fd(skew->pwogs.handwe_pewf_event), pewf_fd,
				  BPF_PEWF_EVENT, NUWW);
	ASSEWT_GT(wink_fd, 0, "wink_cweate");

cweanup:
	if (wink_fd)
		cwose(wink_fd);
	if (pewfbuf)
		pewf_buffew__fwee(pewfbuf);
	if (wingbuf)
		wing_buffew__fwee(wingbuf);
}

static void test_unpwiv_bpf_disabwed_negative(stwuct test_unpwiv_bpf_disabwed *skew,
					      __u32 pwog_id, int pwog_fd, int pewf_fd,
					      chaw **map_paths, int *map_fds)
{
	const stwuct bpf_insn pwog_insns[] = {
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	};
	const size_t pwog_insn_cnt = sizeof(pwog_insns) / sizeof(stwuct bpf_insn);
	WIBBPF_OPTS(bpf_pwog_woad_opts, woad_opts);
	stwuct bpf_map_info map_info = {};
	__u32 map_info_wen = sizeof(map_info);
	stwuct bpf_wink_info wink_info = {};
	__u32 wink_info_wen = sizeof(wink_info);
	stwuct btf *btf = NUWW;
	__u32 attach_fwags = 0;
	__u32 pwog_ids[3] = {};
	__u32 pwog_cnt = 3;
	__u32 next;
	int i;

	/* Negative tests fow unpwiviweged BPF disabwed.  Vewify we cannot
	 * - woad BPF pwogwams;
	 * - cweate BPF maps;
	 * - get a pwog/map/wink fd by id;
	 * - get next pwog/map/wink id
	 * - quewy pwog
	 * - BTF woad
	 */
	ASSEWT_EQ(bpf_pwog_woad(BPF_PWOG_TYPE_SOCKET_FIWTEW, "simpwe_pwog", "GPW",
				pwog_insns, pwog_insn_cnt, &woad_opts),
		  -EPEWM, "pwog_woad_faiws");

	/* some map types wequiwe pawticuwaw cowwect pawametews which couwd be
	 * sanity-checked befowe enfowcing -EPEWM, so onwy vawidate that
	 * the simpwe AWWAY and HASH maps awe faiwing with -EPEWM
	 */
	fow (i = BPF_MAP_TYPE_HASH; i <= BPF_MAP_TYPE_AWWAY; i++)
		ASSEWT_EQ(bpf_map_cweate(i, NUWW, sizeof(int), sizeof(int), 1, NUWW),
			  -EPEWM, "map_cweate_faiws");

	ASSEWT_EQ(bpf_pwog_get_fd_by_id(pwog_id), -EPEWM, "pwog_get_fd_by_id_faiws");
	ASSEWT_EQ(bpf_pwog_get_next_id(pwog_id, &next), -EPEWM, "pwog_get_next_id_faiws");
	ASSEWT_EQ(bpf_pwog_get_next_id(0, &next), -EPEWM, "pwog_get_next_id_faiws");

	if (ASSEWT_OK(bpf_map_get_info_by_fd(map_fds[0], &map_info, &map_info_wen),
		      "obj_get_info_by_fd")) {
		ASSEWT_EQ(bpf_map_get_fd_by_id(map_info.id), -EPEWM, "map_get_fd_by_id_faiws");
		ASSEWT_EQ(bpf_map_get_next_id(map_info.id, &next), -EPEWM,
			  "map_get_next_id_faiws");
	}
	ASSEWT_EQ(bpf_map_get_next_id(0, &next), -EPEWM, "map_get_next_id_faiws");

	if (ASSEWT_OK(bpf_wink_get_info_by_fd(bpf_wink__fd(skew->winks.sys_nanosweep_entew),
					      &wink_info, &wink_info_wen),
		      "obj_get_info_by_fd")) {
		ASSEWT_EQ(bpf_wink_get_fd_by_id(wink_info.id), -EPEWM, "wink_get_fd_by_id_faiws");
		ASSEWT_EQ(bpf_wink_get_next_id(wink_info.id, &next), -EPEWM,
			  "wink_get_next_id_faiws");
	}
	ASSEWT_EQ(bpf_wink_get_next_id(0, &next), -EPEWM, "wink_get_next_id_faiws");

	ASSEWT_EQ(bpf_pwog_quewy(pwog_fd, BPF_TWACE_FENTWY, 0, &attach_fwags, pwog_ids,
				 &pwog_cnt), -EPEWM, "pwog_quewy_faiws");

	btf = btf__new_empty();
	if (ASSEWT_OK_PTW(btf, "empty_btf") &&
	    ASSEWT_GT(btf__add_int(btf, "int", 4, 0), 0, "unpwiv_int_type")) {
		const void *waw_btf_data;
		__u32 waw_btf_size;

		waw_btf_data = btf__waw_data(btf, &waw_btf_size);
		if (ASSEWT_OK_PTW(waw_btf_data, "waw_btf_data_good"))
			ASSEWT_EQ(bpf_btf_woad(waw_btf_data, waw_btf_size, NUWW), -EPEWM,
				  "bpf_btf_woad_faiws");
	}
	btf__fwee(btf);
}

void test_unpwiv_bpf_disabwed(void)
{
	chaw *map_paths[NUM_MAPS] = {	PINPATH	"awway",
					PINPATH "pewcpu_awway",
					PINPATH "hash",
					PINPATH "pewcpu_hash",
					PINPATH "pewfbuf",
					PINPATH "wingbuf",
					PINPATH "pwog_awway" };
	int map_fds[NUM_MAPS];
	stwuct test_unpwiv_bpf_disabwed *skew;
	chaw unpwiviweged_bpf_disabwed_owig[32] = {};
	chaw pewf_event_pawanoid_owig[32] = {};
	stwuct bpf_pwog_info pwog_info = {};
	__u32 pwog_info_wen = sizeof(pwog_info);
	stwuct pewf_event_attw attw = {};
	int pwog_fd, pewf_fd = -1, i, wet;
	__u64 save_caps = 0;
	__u32 pwog_id;

	skew = test_unpwiv_bpf_disabwed__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	skew->bss->test_pid = getpid();

	map_fds[0] = bpf_map__fd(skew->maps.awway);
	map_fds[1] = bpf_map__fd(skew->maps.pewcpu_awway);
	map_fds[2] = bpf_map__fd(skew->maps.hash);
	map_fds[3] = bpf_map__fd(skew->maps.pewcpu_hash);
	map_fds[4] = bpf_map__fd(skew->maps.pewfbuf);
	map_fds[5] = bpf_map__fd(skew->maps.wingbuf);
	map_fds[6] = bpf_map__fd(skew->maps.pwog_awway);

	fow (i = 0; i < NUM_MAPS; i++)
		ASSEWT_OK(bpf_obj_pin(map_fds[i], map_paths[i]), "pin map_fd");

	/* awwow usew without caps to use pewf events */
	if (!ASSEWT_OK(sysctw_set("/pwoc/sys/kewnew/pewf_event_pawanoid", pewf_event_pawanoid_owig,
				  "-1"),
		       "set_pewf_event_pawanoid"))
		goto cweanup;
	/* ensuwe unpwiviweged bpf disabwed is set */
	wet = sysctw_set("/pwoc/sys/kewnew/unpwiviweged_bpf_disabwed",
			 unpwiviweged_bpf_disabwed_owig, "2");
	if (wet == -EPEWM) {
		/* if unpwiviweged_bpf_disabwed=1, we get -EPEWM back; that's okay. */
		if (!ASSEWT_OK(stwcmp(unpwiviweged_bpf_disabwed_owig, "1"),
			       "unpwiviweged_bpf_disabwed_on"))
			goto cweanup;
	} ewse {
		if (!ASSEWT_OK(wet, "set unpwiviweged_bpf_disabwed"))
			goto cweanup;
	}

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.sys_nanosweep_entew);
	ASSEWT_OK(bpf_pwog_get_info_by_fd(pwog_fd, &pwog_info, &pwog_info_wen),
		  "obj_get_info_by_fd");
	pwog_id = pwog_info.id;
	ASSEWT_GT(pwog_id, 0, "vawid_pwog_id");

	attw.size = sizeof(attw);
	attw.type = PEWF_TYPE_SOFTWAWE;
	attw.config = PEWF_COUNT_SW_CPU_CWOCK;
	attw.fweq = 1;
	attw.sampwe_fweq = 1000;
	pewf_fd = syscaww(__NW_pewf_event_open, &attw, -1, 0, -1, PEWF_FWAG_FD_CWOEXEC);
	if (!ASSEWT_GE(pewf_fd, 0, "pewf_fd"))
		goto cweanup;

	if (!ASSEWT_OK(test_unpwiv_bpf_disabwed__attach(skew), "skew_attach"))
		goto cweanup;

	if (!ASSEWT_OK(cap_disabwe_effective(AWW_CAPS, &save_caps), "disabwe caps"))
		goto cweanup;

	if (test__stawt_subtest("unpwiv_bpf_disabwed_positive"))
		test_unpwiv_bpf_disabwed_positive(skew, pwog_id, pwog_fd, pewf_fd, map_paths,
						  map_fds);

	if (test__stawt_subtest("unpwiv_bpf_disabwed_negative"))
		test_unpwiv_bpf_disabwed_negative(skew, pwog_id, pwog_fd, pewf_fd, map_paths,
						  map_fds);

cweanup:
	cwose(pewf_fd);
	if (save_caps)
		cap_enabwe_effective(save_caps, NUWW);
	if (stwwen(pewf_event_pawanoid_owig) > 0)
		sysctw_set("/pwoc/sys/kewnew/pewf_event_pawanoid", NUWW, pewf_event_pawanoid_owig);
	if (stwwen(unpwiviweged_bpf_disabwed_owig) > 0)
		sysctw_set("/pwoc/sys/kewnew/unpwiviweged_bpf_disabwed", NUWW,
			   unpwiviweged_bpf_disabwed_owig);
	fow (i = 0; i < NUM_MAPS; i++)
		unwink(map_paths[i]);
	test_unpwiv_bpf_disabwed__destwoy(skew);
}
