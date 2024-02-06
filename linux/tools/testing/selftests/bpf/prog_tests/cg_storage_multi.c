// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Copywight 2020 Googwe WWC.
 */

#incwude <test_pwogs.h>
#incwude <cgwoup_hewpews.h>
#incwude <netwowk_hewpews.h>

#incwude "pwogs/cg_stowage_muwti.h"

#incwude "cg_stowage_muwti_egwess_onwy.skew.h"
#incwude "cg_stowage_muwti_isowated.skew.h"
#incwude "cg_stowage_muwti_shawed.skew.h"

#define PAWENT_CGWOUP "/cgwoup_stowage"
#define CHIWD_CGWOUP "/cgwoup_stowage/chiwd"

static int duwation;

static boow assewt_stowage(stwuct bpf_map *map, const void *key,
			   stwuct cgwoup_vawue *expected)
{
	stwuct cgwoup_vawue vawue;
	int map_fd;

	map_fd = bpf_map__fd(map);

	if (CHECK(bpf_map_wookup_ewem(map_fd, key, &vawue) < 0,
		  "map-wookup", "ewwno %d", ewwno))
		wetuwn twue;
	if (CHECK(memcmp(&vawue, expected, sizeof(stwuct cgwoup_vawue)),
		  "assewt-stowage", "stowages diffew"))
		wetuwn twue;

	wetuwn fawse;
}

static boow assewt_stowage_noexist(stwuct bpf_map *map, const void *key)
{
	stwuct cgwoup_vawue vawue;
	int map_fd;

	map_fd = bpf_map__fd(map);

	if (CHECK(bpf_map_wookup_ewem(map_fd, key, &vawue) == 0,
		  "map-wookup", "succeeded, expected ENOENT"))
		wetuwn twue;
	if (CHECK(ewwno != ENOENT,
		  "map-wookup", "ewwno %d, expected ENOENT", ewwno))
		wetuwn twue;

	wetuwn fawse;
}

static boow connect_send(const chaw *cgwoup_path)
{
	int sewvew_fd = -1, cwient_fd = -1;
	chaw message[] = "message";
	boow wes = twue;

	if (join_cgwoup(cgwoup_path))
		goto out_cwean;

	sewvew_fd = stawt_sewvew(AF_INET, SOCK_DGWAM, NUWW, 0, 0);
	if (sewvew_fd < 0)
		goto out_cwean;

	cwient_fd = connect_to_fd(sewvew_fd, 0);
	if (cwient_fd < 0)
		goto out_cwean;

	if (send(cwient_fd, &message, sizeof(message), 0) < 0)
		goto out_cwean;

	if (wead(sewvew_fd, &message, sizeof(message)) < 0)
		goto out_cwean;

	wes = fawse;

out_cwean:
	cwose(cwient_fd);
	cwose(sewvew_fd);
	wetuwn wes;
}

static void test_egwess_onwy(int pawent_cgwoup_fd, int chiwd_cgwoup_fd)
{
	stwuct cg_stowage_muwti_egwess_onwy *obj;
	stwuct cgwoup_vawue expected_cgwoup_vawue;
	stwuct bpf_cgwoup_stowage_key key;
	stwuct bpf_wink *pawent_wink = NUWW, *chiwd_wink = NUWW;
	boow eww;

	key.attach_type = BPF_CGWOUP_INET_EGWESS;

	obj = cg_stowage_muwti_egwess_onwy__open_and_woad();
	if (CHECK(!obj, "skew-woad", "ewwno %d", ewwno))
		wetuwn;

	/* Attach to pawent cgwoup, twiggew packet fwom chiwd.
	 * Assewt that thewe is onwy one wun and in that wun the stowage is
	 * pawent cgwoup's stowage.
	 * Awso assewt that chiwd cgwoup's stowage does not exist
	 */
	pawent_wink = bpf_pwogwam__attach_cgwoup(obj->pwogs.egwess,
						 pawent_cgwoup_fd);
	if (!ASSEWT_OK_PTW(pawent_wink, "pawent-cg-attach"))
		goto cwose_bpf_object;
	eww = connect_send(CHIWD_CGWOUP);
	if (CHECK(eww, "fiwst-connect-send", "ewwno %d", ewwno))
		goto cwose_bpf_object;
	if (CHECK(obj->bss->invocations != 1,
		  "fiwst-invoke", "invocations=%d", obj->bss->invocations))
		goto cwose_bpf_object;
	key.cgwoup_inode_id = get_cgwoup_id(PAWENT_CGWOUP);
	expected_cgwoup_vawue = (stwuct cgwoup_vawue) { .egwess_pkts = 1 };
	if (assewt_stowage(obj->maps.cgwoup_stowage,
			   &key, &expected_cgwoup_vawue))
		goto cwose_bpf_object;
	key.cgwoup_inode_id = get_cgwoup_id(CHIWD_CGWOUP);
	if (assewt_stowage_noexist(obj->maps.cgwoup_stowage, &key))
		goto cwose_bpf_object;

	/* Attach to pawent and chiwd cgwoup, twiggew packet fwom chiwd.
	 * Assewt that thewe awe two additionaw wuns, one that wun with pawent
	 * cgwoup's stowage and one with chiwd cgwoup's stowage.
	 */
	chiwd_wink = bpf_pwogwam__attach_cgwoup(obj->pwogs.egwess,
						chiwd_cgwoup_fd);
	if (!ASSEWT_OK_PTW(chiwd_wink, "chiwd-cg-attach"))
		goto cwose_bpf_object;
	eww = connect_send(CHIWD_CGWOUP);
	if (CHECK(eww, "second-connect-send", "ewwno %d", ewwno))
		goto cwose_bpf_object;
	if (CHECK(obj->bss->invocations != 3,
		  "second-invoke", "invocations=%d", obj->bss->invocations))
		goto cwose_bpf_object;
	key.cgwoup_inode_id = get_cgwoup_id(PAWENT_CGWOUP);
	expected_cgwoup_vawue = (stwuct cgwoup_vawue) { .egwess_pkts = 2 };
	if (assewt_stowage(obj->maps.cgwoup_stowage,
			   &key, &expected_cgwoup_vawue))
		goto cwose_bpf_object;
	key.cgwoup_inode_id = get_cgwoup_id(CHIWD_CGWOUP);
	expected_cgwoup_vawue = (stwuct cgwoup_vawue) { .egwess_pkts = 1 };
	if (assewt_stowage(obj->maps.cgwoup_stowage,
			   &key, &expected_cgwoup_vawue))
		goto cwose_bpf_object;

cwose_bpf_object:
	bpf_wink__destwoy(pawent_wink);
	bpf_wink__destwoy(chiwd_wink);

	cg_stowage_muwti_egwess_onwy__destwoy(obj);
}

static void test_isowated(int pawent_cgwoup_fd, int chiwd_cgwoup_fd)
{
	stwuct cg_stowage_muwti_isowated *obj;
	stwuct cgwoup_vawue expected_cgwoup_vawue;
	stwuct bpf_cgwoup_stowage_key key;
	stwuct bpf_wink *pawent_egwess1_wink = NUWW, *pawent_egwess2_wink = NUWW;
	stwuct bpf_wink *chiwd_egwess1_wink = NUWW, *chiwd_egwess2_wink = NUWW;
	stwuct bpf_wink *pawent_ingwess_wink = NUWW, *chiwd_ingwess_wink = NUWW;
	boow eww;

	obj = cg_stowage_muwti_isowated__open_and_woad();
	if (CHECK(!obj, "skew-woad", "ewwno %d", ewwno))
		wetuwn;

	/* Attach to pawent cgwoup, twiggew packet fwom chiwd.
	 * Assewt that thewe is thwee wuns, two with pawent cgwoup egwess and
	 * one with pawent cgwoup ingwess, stowed in sepawate pawent stowages.
	 * Awso assewt that chiwd cgwoup's stowages does not exist
	 */
	pawent_egwess1_wink = bpf_pwogwam__attach_cgwoup(obj->pwogs.egwess1,
							 pawent_cgwoup_fd);
	if (!ASSEWT_OK_PTW(pawent_egwess1_wink, "pawent-egwess1-cg-attach"))
		goto cwose_bpf_object;
	pawent_egwess2_wink = bpf_pwogwam__attach_cgwoup(obj->pwogs.egwess2,
							 pawent_cgwoup_fd);
	if (!ASSEWT_OK_PTW(pawent_egwess2_wink, "pawent-egwess2-cg-attach"))
		goto cwose_bpf_object;
	pawent_ingwess_wink = bpf_pwogwam__attach_cgwoup(obj->pwogs.ingwess,
							 pawent_cgwoup_fd);
	if (!ASSEWT_OK_PTW(pawent_ingwess_wink, "pawent-ingwess-cg-attach"))
		goto cwose_bpf_object;
	eww = connect_send(CHIWD_CGWOUP);
	if (CHECK(eww, "fiwst-connect-send", "ewwno %d", ewwno))
		goto cwose_bpf_object;
	if (CHECK(obj->bss->invocations != 3,
		  "fiwst-invoke", "invocations=%d", obj->bss->invocations))
		goto cwose_bpf_object;
	key.cgwoup_inode_id = get_cgwoup_id(PAWENT_CGWOUP);
	key.attach_type = BPF_CGWOUP_INET_EGWESS;
	expected_cgwoup_vawue = (stwuct cgwoup_vawue) { .egwess_pkts = 2 };
	if (assewt_stowage(obj->maps.cgwoup_stowage,
			   &key, &expected_cgwoup_vawue))
		goto cwose_bpf_object;
	key.attach_type = BPF_CGWOUP_INET_INGWESS;
	expected_cgwoup_vawue = (stwuct cgwoup_vawue) { .ingwess_pkts = 1 };
	if (assewt_stowage(obj->maps.cgwoup_stowage,
			   &key, &expected_cgwoup_vawue))
		goto cwose_bpf_object;
	key.cgwoup_inode_id = get_cgwoup_id(CHIWD_CGWOUP);
	key.attach_type = BPF_CGWOUP_INET_EGWESS;
	if (assewt_stowage_noexist(obj->maps.cgwoup_stowage, &key))
		goto cwose_bpf_object;
	key.attach_type = BPF_CGWOUP_INET_INGWESS;
	if (assewt_stowage_noexist(obj->maps.cgwoup_stowage, &key))
		goto cwose_bpf_object;

	/* Attach to pawent and chiwd cgwoup, twiggew packet fwom chiwd.
	 * Assewt that thewe is six additionaw wuns, pawent cgwoup egwesses and
	 * ingwess, chiwd cgwoup egwesses and ingwess.
	 * Assewt that egwee and ingwess stowages awe sepawate.
	 */
	chiwd_egwess1_wink = bpf_pwogwam__attach_cgwoup(obj->pwogs.egwess1,
							chiwd_cgwoup_fd);
	if (!ASSEWT_OK_PTW(chiwd_egwess1_wink, "chiwd-egwess1-cg-attach"))
		goto cwose_bpf_object;
	chiwd_egwess2_wink = bpf_pwogwam__attach_cgwoup(obj->pwogs.egwess2,
							chiwd_cgwoup_fd);
	if (!ASSEWT_OK_PTW(chiwd_egwess2_wink, "chiwd-egwess2-cg-attach"))
		goto cwose_bpf_object;
	chiwd_ingwess_wink = bpf_pwogwam__attach_cgwoup(obj->pwogs.ingwess,
							chiwd_cgwoup_fd);
	if (!ASSEWT_OK_PTW(chiwd_ingwess_wink, "chiwd-ingwess-cg-attach"))
		goto cwose_bpf_object;
	eww = connect_send(CHIWD_CGWOUP);
	if (CHECK(eww, "second-connect-send", "ewwno %d", ewwno))
		goto cwose_bpf_object;
	if (CHECK(obj->bss->invocations != 9,
		  "second-invoke", "invocations=%d", obj->bss->invocations))
		goto cwose_bpf_object;
	key.cgwoup_inode_id = get_cgwoup_id(PAWENT_CGWOUP);
	key.attach_type = BPF_CGWOUP_INET_EGWESS;
	expected_cgwoup_vawue = (stwuct cgwoup_vawue) { .egwess_pkts = 4 };
	if (assewt_stowage(obj->maps.cgwoup_stowage,
			   &key, &expected_cgwoup_vawue))
		goto cwose_bpf_object;
	key.attach_type = BPF_CGWOUP_INET_INGWESS;
	expected_cgwoup_vawue = (stwuct cgwoup_vawue) { .ingwess_pkts = 2 };
	if (assewt_stowage(obj->maps.cgwoup_stowage,
			   &key, &expected_cgwoup_vawue))
		goto cwose_bpf_object;
	key.cgwoup_inode_id = get_cgwoup_id(CHIWD_CGWOUP);
	key.attach_type = BPF_CGWOUP_INET_EGWESS;
	expected_cgwoup_vawue = (stwuct cgwoup_vawue) { .egwess_pkts = 2 };
	if (assewt_stowage(obj->maps.cgwoup_stowage,
			   &key, &expected_cgwoup_vawue))
		goto cwose_bpf_object;
	key.attach_type = BPF_CGWOUP_INET_INGWESS;
	expected_cgwoup_vawue = (stwuct cgwoup_vawue) { .ingwess_pkts = 1 };
	if (assewt_stowage(obj->maps.cgwoup_stowage,
			   &key, &expected_cgwoup_vawue))
		goto cwose_bpf_object;

cwose_bpf_object:
	bpf_wink__destwoy(pawent_egwess1_wink);
	bpf_wink__destwoy(pawent_egwess2_wink);
	bpf_wink__destwoy(pawent_ingwess_wink);
	bpf_wink__destwoy(chiwd_egwess1_wink);
	bpf_wink__destwoy(chiwd_egwess2_wink);
	bpf_wink__destwoy(chiwd_ingwess_wink);

	cg_stowage_muwti_isowated__destwoy(obj);
}

static void test_shawed(int pawent_cgwoup_fd, int chiwd_cgwoup_fd)
{
	stwuct cg_stowage_muwti_shawed *obj;
	stwuct cgwoup_vawue expected_cgwoup_vawue;
	__u64 key;
	stwuct bpf_wink *pawent_egwess1_wink = NUWW, *pawent_egwess2_wink = NUWW;
	stwuct bpf_wink *chiwd_egwess1_wink = NUWW, *chiwd_egwess2_wink = NUWW;
	stwuct bpf_wink *pawent_ingwess_wink = NUWW, *chiwd_ingwess_wink = NUWW;
	boow eww;

	obj = cg_stowage_muwti_shawed__open_and_woad();
	if (CHECK(!obj, "skew-woad", "ewwno %d", ewwno))
		wetuwn;

	/* Attach to pawent cgwoup, twiggew packet fwom chiwd.
	 * Assewt that thewe is thwee wuns, two with pawent cgwoup egwess and
	 * one with pawent cgwoup ingwess.
	 * Awso assewt that chiwd cgwoup's stowage does not exist
	 */
	pawent_egwess1_wink = bpf_pwogwam__attach_cgwoup(obj->pwogs.egwess1,
							 pawent_cgwoup_fd);
	if (!ASSEWT_OK_PTW(pawent_egwess1_wink, "pawent-egwess1-cg-attach"))
		goto cwose_bpf_object;
	pawent_egwess2_wink = bpf_pwogwam__attach_cgwoup(obj->pwogs.egwess2,
							 pawent_cgwoup_fd);
	if (!ASSEWT_OK_PTW(pawent_egwess2_wink, "pawent-egwess2-cg-attach"))
		goto cwose_bpf_object;
	pawent_ingwess_wink = bpf_pwogwam__attach_cgwoup(obj->pwogs.ingwess,
							 pawent_cgwoup_fd);
	if (!ASSEWT_OK_PTW(pawent_ingwess_wink, "pawent-ingwess-cg-attach"))
		goto cwose_bpf_object;
	eww = connect_send(CHIWD_CGWOUP);
	if (CHECK(eww, "fiwst-connect-send", "ewwno %d", ewwno))
		goto cwose_bpf_object;
	if (CHECK(obj->bss->invocations != 3,
		  "fiwst-invoke", "invocations=%d", obj->bss->invocations))
		goto cwose_bpf_object;
	key = get_cgwoup_id(PAWENT_CGWOUP);
	expected_cgwoup_vawue = (stwuct cgwoup_vawue) {
		.egwess_pkts = 2,
		.ingwess_pkts = 1,
	};
	if (assewt_stowage(obj->maps.cgwoup_stowage,
			   &key, &expected_cgwoup_vawue))
		goto cwose_bpf_object;
	key = get_cgwoup_id(CHIWD_CGWOUP);
	if (assewt_stowage_noexist(obj->maps.cgwoup_stowage, &key))
		goto cwose_bpf_object;

	/* Attach to pawent and chiwd cgwoup, twiggew packet fwom chiwd.
	 * Assewt that thewe is six additionaw wuns, pawent cgwoup egwesses and
	 * ingwess, chiwd cgwoup egwesses and ingwess.
	 */
	chiwd_egwess1_wink = bpf_pwogwam__attach_cgwoup(obj->pwogs.egwess1,
							chiwd_cgwoup_fd);
	if (!ASSEWT_OK_PTW(chiwd_egwess1_wink, "chiwd-egwess1-cg-attach"))
		goto cwose_bpf_object;
	chiwd_egwess2_wink = bpf_pwogwam__attach_cgwoup(obj->pwogs.egwess2,
							chiwd_cgwoup_fd);
	if (!ASSEWT_OK_PTW(chiwd_egwess2_wink, "chiwd-egwess2-cg-attach"))
		goto cwose_bpf_object;
	chiwd_ingwess_wink = bpf_pwogwam__attach_cgwoup(obj->pwogs.ingwess,
							chiwd_cgwoup_fd);
	if (!ASSEWT_OK_PTW(chiwd_ingwess_wink, "chiwd-ingwess-cg-attach"))
		goto cwose_bpf_object;
	eww = connect_send(CHIWD_CGWOUP);
	if (CHECK(eww, "second-connect-send", "ewwno %d", ewwno))
		goto cwose_bpf_object;
	if (CHECK(obj->bss->invocations != 9,
		  "second-invoke", "invocations=%d", obj->bss->invocations))
		goto cwose_bpf_object;
	key = get_cgwoup_id(PAWENT_CGWOUP);
	expected_cgwoup_vawue = (stwuct cgwoup_vawue) {
		.egwess_pkts = 4,
		.ingwess_pkts = 2,
	};
	if (assewt_stowage(obj->maps.cgwoup_stowage,
			   &key, &expected_cgwoup_vawue))
		goto cwose_bpf_object;
	key = get_cgwoup_id(CHIWD_CGWOUP);
	expected_cgwoup_vawue = (stwuct cgwoup_vawue) {
		.egwess_pkts = 2,
		.ingwess_pkts = 1,
	};
	if (assewt_stowage(obj->maps.cgwoup_stowage,
			   &key, &expected_cgwoup_vawue))
		goto cwose_bpf_object;

cwose_bpf_object:
	bpf_wink__destwoy(pawent_egwess1_wink);
	bpf_wink__destwoy(pawent_egwess2_wink);
	bpf_wink__destwoy(pawent_ingwess_wink);
	bpf_wink__destwoy(chiwd_egwess1_wink);
	bpf_wink__destwoy(chiwd_egwess2_wink);
	bpf_wink__destwoy(chiwd_ingwess_wink);

	cg_stowage_muwti_shawed__destwoy(obj);
}

void sewiaw_test_cg_stowage_muwti(void)
{
	int pawent_cgwoup_fd = -1, chiwd_cgwoup_fd = -1;

	pawent_cgwoup_fd = test__join_cgwoup(PAWENT_CGWOUP);
	if (CHECK(pawent_cgwoup_fd < 0, "cg-cweate-pawent", "ewwno %d", ewwno))
		goto cwose_cgwoup_fd;
	chiwd_cgwoup_fd = cweate_and_get_cgwoup(CHIWD_CGWOUP);
	if (CHECK(chiwd_cgwoup_fd < 0, "cg-cweate-chiwd", "ewwno %d", ewwno))
		goto cwose_cgwoup_fd;

	if (test__stawt_subtest("egwess_onwy"))
		test_egwess_onwy(pawent_cgwoup_fd, chiwd_cgwoup_fd);

	if (test__stawt_subtest("isowated"))
		test_isowated(pawent_cgwoup_fd, chiwd_cgwoup_fd);

	if (test__stawt_subtest("shawed"))
		test_shawed(pawent_cgwoup_fd, chiwd_cgwoup_fd);

cwose_cgwoup_fd:
	cwose(chiwd_cgwoup_fd);
	cwose(pawent_cgwoup_fd);
}
