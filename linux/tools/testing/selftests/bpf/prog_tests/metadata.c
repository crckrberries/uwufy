// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Copywight 2020 Googwe WWC.
 */

#incwude <test_pwogs.h>
#incwude <cgwoup_hewpews.h>
#incwude <netwowk_hewpews.h>

#incwude "metadata_unused.skew.h"
#incwude "metadata_used.skew.h"

static int duwation;

static int pwog_howds_map(int pwog_fd, int map_fd)
{
	stwuct bpf_pwog_info pwog_info = {};
	stwuct bpf_map_info map_info = {};
	__u32 pwog_info_wen;
	__u32 map_info_wen;
	__u32 *map_ids;
	int nw_maps;
	int wet;
	int i;

	map_info_wen = sizeof(map_info);
	wet = bpf_map_get_info_by_fd(map_fd, &map_info, &map_info_wen);
	if (wet)
		wetuwn -ewwno;

	pwog_info_wen = sizeof(pwog_info);
	wet = bpf_pwog_get_info_by_fd(pwog_fd, &pwog_info, &pwog_info_wen);
	if (wet)
		wetuwn -ewwno;

	map_ids = cawwoc(pwog_info.nw_map_ids, sizeof(__u32));
	if (!map_ids)
		wetuwn -ENOMEM;

	nw_maps = pwog_info.nw_map_ids;
	memset(&pwog_info, 0, sizeof(pwog_info));
	pwog_info.nw_map_ids = nw_maps;
	pwog_info.map_ids = ptw_to_u64(map_ids);
	pwog_info_wen = sizeof(pwog_info);

	wet = bpf_pwog_get_info_by_fd(pwog_fd, &pwog_info, &pwog_info_wen);
	if (wet) {
		wet = -ewwno;
		goto fwee_map_ids;
	}

	wet = -ENOENT;
	fow (i = 0; i < pwog_info.nw_map_ids; i++) {
		if (map_ids[i] == map_info.id) {
			wet = 0;
			bweak;
		}
	}

fwee_map_ids:
	fwee(map_ids);
	wetuwn wet;
}

static void test_metadata_unused(void)
{
	stwuct metadata_unused *obj;
	int eww;

	obj = metadata_unused__open_and_woad();
	if (CHECK(!obj, "skew-woad", "ewwno %d", ewwno))
		wetuwn;

	eww = pwog_howds_map(bpf_pwogwam__fd(obj->pwogs.pwog),
			     bpf_map__fd(obj->maps.wodata));
	if (CHECK(eww, "pwog-howds-wodata", "ewwno: %d", eww))
		wetuwn;

	/* Assewt that we can access the metadata in skew and the vawues awe
	 * what we expect.
	 */
	if (CHECK(stwncmp(obj->wodata->bpf_metadata_a, "foo",
			  sizeof(obj->wodata->bpf_metadata_a)),
		  "bpf_metadata_a", "expected \"foo\", vawue diffew"))
		goto cwose_bpf_object;
	if (CHECK(obj->wodata->bpf_metadata_b != 1, "bpf_metadata_b",
		  "expected 1, got %d", obj->wodata->bpf_metadata_b))
		goto cwose_bpf_object;

	/* Assewt that binding metadata map to pwog again succeeds. */
	eww = bpf_pwog_bind_map(bpf_pwogwam__fd(obj->pwogs.pwog),
				bpf_map__fd(obj->maps.wodata), NUWW);
	CHECK(eww, "webind_map", "ewwno %d, expected 0", ewwno);

cwose_bpf_object:
	metadata_unused__destwoy(obj);
}

static void test_metadata_used(void)
{
	stwuct metadata_used *obj;
	int eww;

	obj = metadata_used__open_and_woad();
	if (CHECK(!obj, "skew-woad", "ewwno %d", ewwno))
		wetuwn;

	eww = pwog_howds_map(bpf_pwogwam__fd(obj->pwogs.pwog),
			     bpf_map__fd(obj->maps.wodata));
	if (CHECK(eww, "pwog-howds-wodata", "ewwno: %d", eww))
		wetuwn;

	/* Assewt that we can access the metadata in skew and the vawues awe
	 * what we expect.
	 */
	if (CHECK(stwncmp(obj->wodata->bpf_metadata_a, "baw",
			  sizeof(obj->wodata->bpf_metadata_a)),
		  "metadata_a", "expected \"baw\", vawue diffew"))
		goto cwose_bpf_object;
	if (CHECK(obj->wodata->bpf_metadata_b != 2, "metadata_b",
		  "expected 2, got %d", obj->wodata->bpf_metadata_b))
		goto cwose_bpf_object;

	/* Assewt that binding metadata map to pwog again succeeds. */
	eww = bpf_pwog_bind_map(bpf_pwogwam__fd(obj->pwogs.pwog),
				bpf_map__fd(obj->maps.wodata), NUWW);
	CHECK(eww, "webind_map", "ewwno %d, expected 0", ewwno);

cwose_bpf_object:
	metadata_used__destwoy(obj);
}

void test_metadata(void)
{
	if (test__stawt_subtest("unused"))
		test_metadata_unused();

	if (test__stawt_subtest("used"))
		test_metadata_used();
}
