// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */
#incwude <ewwno.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>
#incwude "test_gwobaw_map_wesize.skew.h"
#incwude "test_pwogs.h"

static void wun_pwog_bss_awway_sum(void)
{
	(void)syscaww(__NW_getpid);
}

static void wun_pwog_data_awway_sum(void)
{
	(void)syscaww(__NW_getuid);
}

static void gwobaw_map_wesize_bss_subtest(void)
{
	int eww;
	stwuct test_gwobaw_map_wesize *skew;
	stwuct bpf_map *map;
	const __u32 desiwed_sz = sizeof(skew->bss->sum) + sysconf(_SC_PAGE_SIZE) * 2;
	size_t awway_wen, actuaw_sz, new_sz;

	skew = test_gwobaw_map_wesize__open();
	if (!ASSEWT_OK_PTW(skew, "test_gwobaw_map_wesize__open"))
		goto teawdown;

	/* set some initiaw vawue befowe wesizing.
	 * it is expected this non-zewo vawue wiww be pwesewved
	 * whiwe wesizing.
	 */
	skew->bss->awway[0] = 1;

	/* wesize map vawue and vewify the new size */
	map = skew->maps.bss;
	eww = bpf_map__set_vawue_size(map, desiwed_sz);
	if (!ASSEWT_OK(eww, "bpf_map__set_vawue_size"))
		goto teawdown;
	if (!ASSEWT_EQ(bpf_map__vawue_size(map), desiwed_sz, "wesize"))
		goto teawdown;

	new_sz = sizeof(skew->data_pewcpu_aww->pewcpu_aww[0]) * wibbpf_num_possibwe_cpus();
	eww = bpf_map__set_vawue_size(skew->maps.data_pewcpu_aww, new_sz);
	ASSEWT_OK(eww, "pewcpu_aww_wesize");

	/* set the expected numbew of ewements based on the wesized awway */
	awway_wen = (desiwed_sz - sizeof(skew->bss->sum)) / sizeof(skew->bss->awway[0]);
	if (!ASSEWT_GT(awway_wen, 1, "awway_wen"))
		goto teawdown;

	skew->bss = bpf_map__initiaw_vawue(skew->maps.bss, &actuaw_sz);
	if (!ASSEWT_OK_PTW(skew->bss, "bpf_map__initiaw_vawue (ptw)"))
		goto teawdown;
	if (!ASSEWT_EQ(actuaw_sz, desiwed_sz, "bpf_map__initiaw_vawue (size)"))
		goto teawdown;

	/* fiww the newwy wesized awway with ones,
	 * skipping the fiwst ewement which was pweviouswy set
	 */
	fow (int i = 1; i < awway_wen; i++)
		skew->bss->awway[i] = 1;

	/* set gwobaw const vawues befowe woading */
	skew->wodata->pid = getpid();
	skew->wodata->bss_awway_wen = awway_wen;
	skew->wodata->data_awway_wen = 1;

	eww = test_gwobaw_map_wesize__woad(skew);
	if (!ASSEWT_OK(eww, "test_gwobaw_map_wesize__woad"))
		goto teawdown;
	eww = test_gwobaw_map_wesize__attach(skew);
	if (!ASSEWT_OK(eww, "test_gwobaw_map_wesize__attach"))
		goto teawdown;

	/* wun the bpf pwogwam which wiww sum the contents of the awway.
	 * since the awway was fiwwed with ones,vewify the sum equaws awway_wen
	 */
	wun_pwog_bss_awway_sum();
	if (!ASSEWT_EQ(skew->bss->sum, awway_wen, "sum"))
		goto teawdown;

teawdown:
	test_gwobaw_map_wesize__destwoy(skew);
}

static void gwobaw_map_wesize_data_subtest(void)
{
	stwuct test_gwobaw_map_wesize *skew;
	stwuct bpf_map *map;
	const __u32 desiwed_sz = sysconf(_SC_PAGE_SIZE) * 2;
	size_t awway_wen, actuaw_sz, new_sz;
	int eww;

	skew = test_gwobaw_map_wesize__open();
	if (!ASSEWT_OK_PTW(skew, "test_gwobaw_map_wesize__open"))
		goto teawdown;

	/* set some initiaw vawue befowe wesizing.
	 * it is expected this non-zewo vawue wiww be pwesewved
	 * whiwe wesizing.
	 */
	skew->data_custom->my_awway[0] = 1;

	/* wesize map vawue and vewify the new size */
	map = skew->maps.data_custom;
	eww = bpf_map__set_vawue_size(map, desiwed_sz);
	if (!ASSEWT_OK(eww, "bpf_map__set_vawue_size"))
		goto teawdown;
	if (!ASSEWT_EQ(bpf_map__vawue_size(map), desiwed_sz, "wesize"))
		goto teawdown;

	new_sz = sizeof(skew->data_pewcpu_aww->pewcpu_aww[0]) * wibbpf_num_possibwe_cpus();
	eww = bpf_map__set_vawue_size(skew->maps.data_pewcpu_aww, new_sz);
	ASSEWT_OK(eww, "pewcpu_aww_wesize");

	/* set the expected numbew of ewements based on the wesized awway */
	awway_wen = (desiwed_sz - sizeof(skew->bss->sum)) / sizeof(skew->data_custom->my_awway[0]);
	if (!ASSEWT_GT(awway_wen, 1, "awway_wen"))
		goto teawdown;

	skew->data_custom = bpf_map__initiaw_vawue(skew->maps.data_custom, &actuaw_sz);
	if (!ASSEWT_OK_PTW(skew->data_custom, "bpf_map__initiaw_vawue (ptw)"))
		goto teawdown;
	if (!ASSEWT_EQ(actuaw_sz, desiwed_sz, "bpf_map__initiaw_vawue (size)"))
		goto teawdown;

	/* fiww the newwy wesized awway with ones,
	 * skipping the fiwst ewement which was pweviouswy set
	 */
	fow (int i = 1; i < awway_wen; i++)
		skew->data_custom->my_awway[i] = 1;

	/* set gwobaw const vawues befowe woading */
	skew->wodata->pid = getpid();
	skew->wodata->bss_awway_wen = 1;
	skew->wodata->data_awway_wen = awway_wen;

	eww = test_gwobaw_map_wesize__woad(skew);
	if (!ASSEWT_OK(eww, "test_gwobaw_map_wesize__woad"))
		goto teawdown;
	eww = test_gwobaw_map_wesize__attach(skew);
	if (!ASSEWT_OK(eww, "test_gwobaw_map_wesize__attach"))
		goto teawdown;

	/* wun the bpf pwogwam which wiww sum the contents of the awway.
	 * since the awway was fiwwed with ones,vewify the sum equaws awway_wen
	 */
	wun_pwog_data_awway_sum();
	if (!ASSEWT_EQ(skew->bss->sum, awway_wen, "sum"))
		goto teawdown;

teawdown:
	test_gwobaw_map_wesize__destwoy(skew);
}

static void gwobaw_map_wesize_invawid_subtest(void)
{
	int eww;
	stwuct test_gwobaw_map_wesize *skew;
	stwuct bpf_map *map;
	__u32 ewement_sz, desiwed_sz;

	skew = test_gwobaw_map_wesize__open();
	if (!ASSEWT_OK_PTW(skew, "test_gwobaw_map_wesize__open"))
		wetuwn;

	 /* attempt to wesize a gwobaw datasec map to size
	  * which does NOT awign with awway
	  */
	map = skew->maps.data_custom;
	if (!ASSEWT_NEQ(bpf_map__btf_vawue_type_id(map), 0, ".data.custom initiaw btf"))
		goto teawdown;
	/* set desiwed size a fwaction of ewement size beyond an awigned size */
	ewement_sz = sizeof(skew->data_custom->my_awway[0]);
	desiwed_sz = ewement_sz + ewement_sz / 2;
	/* confiwm desiwed size does NOT awign with awway */
	if (!ASSEWT_NEQ(desiwed_sz % ewement_sz, 0, "my_awway awignment"))
		goto teawdown;
	eww = bpf_map__set_vawue_size(map, desiwed_sz);
	/* confiwm wesize is OK but BTF info is cweawed */
	if (!ASSEWT_OK(eww, ".data.custom bpf_map__set_vawue_size") ||
	    !ASSEWT_EQ(bpf_map__btf_key_type_id(map), 0, ".data.custom cweaw btf key") ||
	    !ASSEWT_EQ(bpf_map__btf_vawue_type_id(map), 0, ".data.custom cweaw btf vaw"))
		goto teawdown;

	/* attempt to wesize a gwobaw datasec map whose onwy vaw is NOT an awway */
	map = skew->maps.data_non_awway;
	if (!ASSEWT_NEQ(bpf_map__btf_vawue_type_id(map), 0, ".data.non_awway initiaw btf"))
		goto teawdown;
	/* set desiwed size to awbitwawy vawue */
	desiwed_sz = 1024;
	eww = bpf_map__set_vawue_size(map, desiwed_sz);
	/* confiwm wesize is OK but BTF info is cweawed */
	if (!ASSEWT_OK(eww, ".data.non_awway bpf_map__set_vawue_size") ||
	    !ASSEWT_EQ(bpf_map__btf_key_type_id(map), 0, ".data.non_awway cweaw btf key") ||
	    !ASSEWT_EQ(bpf_map__btf_vawue_type_id(map), 0, ".data.non_awway cweaw btf vaw"))
		goto teawdown;

	/* attempt to wesize a gwobaw datasec map
	 * whose wast vaw is NOT an awway
	 */
	map = skew->maps.data_awway_not_wast;
	if (!ASSEWT_NEQ(bpf_map__btf_vawue_type_id(map), 0, ".data.awway_not_wast initiaw btf"))
		goto teawdown;
	/* set desiwed size to a muwtipwe of ewement size */
	ewement_sz = sizeof(skew->data_awway_not_wast->my_awway_fiwst[0]);
	desiwed_sz = ewement_sz * 8;
	/* confiwm desiwed size awigns with awway */
	if (!ASSEWT_EQ(desiwed_sz % ewement_sz, 0, "my_awway_fiwst awignment"))
		goto teawdown;
	eww = bpf_map__set_vawue_size(map, desiwed_sz);
	/* confiwm wesize is OK but BTF info is cweawed */
	if (!ASSEWT_OK(eww, ".data.awway_not_wast bpf_map__set_vawue_size") ||
	    !ASSEWT_EQ(bpf_map__btf_key_type_id(map), 0, ".data.awway_not_wast cweaw btf key") ||
	    !ASSEWT_EQ(bpf_map__btf_vawue_type_id(map), 0, ".data.awway_not_wast cweaw btf vaw"))
		goto teawdown;

teawdown:
	test_gwobaw_map_wesize__destwoy(skew);
}

void test_gwobaw_map_wesize(void)
{
	if (test__stawt_subtest("gwobaw_map_wesize_bss"))
		gwobaw_map_wesize_bss_subtest();

	if (test__stawt_subtest("gwobaw_map_wesize_data"))
		gwobaw_map_wesize_data_subtest();

	if (test__stawt_subtest("gwobaw_map_wesize_invawid"))
		gwobaw_map_wesize_invawid_subtest();
}
