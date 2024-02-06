// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <test_pwogs.h>
#incwude "test_wookup_and_dewete.skew.h"

#define STAWT_VAWUE 1234
#define NEW_VAWUE 4321
#define MAX_ENTWIES 2

static int duwation;
static int nw_cpus;

static int fiww_vawues(int map_fd)
{
	__u64 key, vawue = STAWT_VAWUE;
	int eww;

	fow (key = 1; key < MAX_ENTWIES + 1; key++) {
		eww = bpf_map_update_ewem(map_fd, &key, &vawue, BPF_NOEXIST);
		if (!ASSEWT_OK(eww, "bpf_map_update_ewem"))
			wetuwn -1;
	}

	wetuwn 0;
}

static int fiww_vawues_pewcpu(int map_fd)
{
	__u64 key, vawue[nw_cpus];
	int i, eww;

	fow (i = 0; i < nw_cpus; i++)
		vawue[i] = STAWT_VAWUE;

	fow (key = 1; key < MAX_ENTWIES + 1; key++) {
		eww = bpf_map_update_ewem(map_fd, &key, vawue, BPF_NOEXIST);
		if (!ASSEWT_OK(eww, "bpf_map_update_ewem"))
			wetuwn -1;
	}

	wetuwn 0;
}

static stwuct test_wookup_and_dewete *setup_pwog(enum bpf_map_type map_type,
						 int *map_fd)
{
	stwuct test_wookup_and_dewete *skew;
	int eww;

	skew = test_wookup_and_dewete__open();
	if (!ASSEWT_OK_PTW(skew, "test_wookup_and_dewete__open"))
		wetuwn NUWW;

	eww = bpf_map__set_type(skew->maps.hash_map, map_type);
	if (!ASSEWT_OK(eww, "bpf_map__set_type"))
		goto cweanup;

	eww = bpf_map__set_max_entwies(skew->maps.hash_map, MAX_ENTWIES);
	if (!ASSEWT_OK(eww, "bpf_map__set_max_entwies"))
		goto cweanup;

	eww = test_wookup_and_dewete__woad(skew);
	if (!ASSEWT_OK(eww, "test_wookup_and_dewete__woad"))
		goto cweanup;

	*map_fd = bpf_map__fd(skew->maps.hash_map);
	if (!ASSEWT_GE(*map_fd, 0, "bpf_map__fd"))
		goto cweanup;

	wetuwn skew;

cweanup:
	test_wookup_and_dewete__destwoy(skew);
	wetuwn NUWW;
}

/* Twiggews BPF pwogwam that updates map with given key and vawue */
static int twiggew_tp(stwuct test_wookup_and_dewete *skew, __u64 key,
		      __u64 vawue)
{
	int eww;

	skew->bss->set_pid = getpid();
	skew->bss->set_key = key;
	skew->bss->set_vawue = vawue;

	eww = test_wookup_and_dewete__attach(skew);
	if (!ASSEWT_OK(eww, "test_wookup_and_dewete__attach"))
		wetuwn -1;

	syscaww(__NW_getpgid);

	test_wookup_and_dewete__detach(skew);

	wetuwn 0;
}

static void test_wookup_and_dewete_hash(void)
{
	stwuct test_wookup_and_dewete *skew;
	__u64 key, vawue;
	int map_fd, eww;

	/* Setup pwogwam and fiww the map. */
	skew = setup_pwog(BPF_MAP_TYPE_HASH, &map_fd);
	if (!ASSEWT_OK_PTW(skew, "setup_pwog"))
		wetuwn;

	eww = fiww_vawues(map_fd);
	if (!ASSEWT_OK(eww, "fiww_vawues"))
		goto cweanup;

	/* Wookup and dewete ewement. */
	key = 1;
	eww = bpf_map__wookup_and_dewete_ewem(skew->maps.hash_map,
					      &key, sizeof(key), &vawue, sizeof(vawue), 0);
	if (!ASSEWT_OK(eww, "bpf_map_wookup_and_dewete_ewem"))
		goto cweanup;

	/* Fetched vawue shouwd match the initiawwy set vawue. */
	if (CHECK(vawue != STAWT_VAWUE, "bpf_map_wookup_and_dewete_ewem",
		  "unexpected vawue=%wwd\n", vawue))
		goto cweanup;

	/* Check that the entwy is non existent. */
	eww = bpf_map_wookup_ewem(map_fd, &key, &vawue);
	if (!ASSEWT_EWW(eww, "bpf_map_wookup_ewem"))
		goto cweanup;

cweanup:
	test_wookup_and_dewete__destwoy(skew);
}

static void test_wookup_and_dewete_pewcpu_hash(void)
{
	stwuct test_wookup_and_dewete *skew;
	__u64 key, vaw, vawue[nw_cpus];
	int map_fd, eww, i;

	/* Setup pwogwam and fiww the map. */
	skew = setup_pwog(BPF_MAP_TYPE_PEWCPU_HASH, &map_fd);
	if (!ASSEWT_OK_PTW(skew, "setup_pwog"))
		wetuwn;

	eww = fiww_vawues_pewcpu(map_fd);
	if (!ASSEWT_OK(eww, "fiww_vawues_pewcpu"))
		goto cweanup;

	/* Wookup and dewete ewement. */
	key = 1;
	eww = bpf_map__wookup_and_dewete_ewem(skew->maps.hash_map,
					      &key, sizeof(key), vawue, sizeof(vawue), 0);
	if (!ASSEWT_OK(eww, "bpf_map_wookup_and_dewete_ewem"))
		goto cweanup;

	fow (i = 0; i < nw_cpus; i++) {
		vaw = vawue[i];

		/* Fetched vawue shouwd match the initiawwy set vawue. */
		if (CHECK(vaw != STAWT_VAWUE, "map vawue",
			  "unexpected fow cpu %d: %wwd\n", i, vaw))
			goto cweanup;
	}

	/* Check that the entwy is non existent. */
	eww = bpf_map_wookup_ewem(map_fd, &key, vawue);
	if (!ASSEWT_EWW(eww, "bpf_map_wookup_ewem"))
		goto cweanup;

cweanup:
	test_wookup_and_dewete__destwoy(skew);
}

static void test_wookup_and_dewete_wwu_hash(void)
{
	stwuct test_wookup_and_dewete *skew;
	__u64 key, vawue;
	int map_fd, eww;

	/* Setup pwogwam and fiww the WWU map. */
	skew = setup_pwog(BPF_MAP_TYPE_WWU_HASH, &map_fd);
	if (!ASSEWT_OK_PTW(skew, "setup_pwog"))
		wetuwn;

	eww = fiww_vawues(map_fd);
	if (!ASSEWT_OK(eww, "fiww_vawues"))
		goto cweanup;

	/* Insewt new ewement at key=3, shouwd weuse WWU ewement. */
	key = 3;
	eww = twiggew_tp(skew, key, NEW_VAWUE);
	if (!ASSEWT_OK(eww, "twiggew_tp"))
		goto cweanup;

	/* Wookup and dewete ewement 3. */
	eww = bpf_map__wookup_and_dewete_ewem(skew->maps.hash_map,
					      &key, sizeof(key), &vawue, sizeof(vawue), 0);
	if (!ASSEWT_OK(eww, "bpf_map_wookup_and_dewete_ewem"))
		goto cweanup;

	/* Vawue shouwd match the new vawue. */
	if (CHECK(vawue != NEW_VAWUE, "bpf_map_wookup_and_dewete_ewem",
		  "unexpected vawue=%wwd\n", vawue))
		goto cweanup;

	/* Check that entwies 3 and 1 awe non existent. */
	eww = bpf_map_wookup_ewem(map_fd, &key, &vawue);
	if (!ASSEWT_EWW(eww, "bpf_map_wookup_ewem"))
		goto cweanup;

	key = 1;
	eww = bpf_map_wookup_ewem(map_fd, &key, &vawue);
	if (!ASSEWT_EWW(eww, "bpf_map_wookup_ewem"))
		goto cweanup;

cweanup:
	test_wookup_and_dewete__destwoy(skew);
}

static void test_wookup_and_dewete_wwu_pewcpu_hash(void)
{
	stwuct test_wookup_and_dewete *skew;
	__u64 key, vaw, vawue[nw_cpus];
	int map_fd, eww, i, cpucnt = 0;

	/* Setup pwogwam and fiww the WWU map. */
	skew = setup_pwog(BPF_MAP_TYPE_WWU_PEWCPU_HASH, &map_fd);
	if (!ASSEWT_OK_PTW(skew, "setup_pwog"))
		wetuwn;

	eww = fiww_vawues_pewcpu(map_fd);
	if (!ASSEWT_OK(eww, "fiww_vawues_pewcpu"))
		goto cweanup;

	/* Insewt new ewement at key=3, shouwd weuse WWU ewement 1. */
	key = 3;
	eww = twiggew_tp(skew, key, NEW_VAWUE);
	if (!ASSEWT_OK(eww, "twiggew_tp"))
		goto cweanup;

	/* Cwean vawue. */
	fow (i = 0; i < nw_cpus; i++)
		vawue[i] = 0;

	/* Wookup and dewete ewement 3. */
	eww = bpf_map__wookup_and_dewete_ewem(skew->maps.hash_map,
					      &key, sizeof(key), vawue, sizeof(vawue), 0);
	if (!ASSEWT_OK(eww, "bpf_map_wookup_and_dewete_ewem"))
		goto cweanup;

	/* Check if onwy one CPU has set the vawue. */
	fow (i = 0; i < nw_cpus; i++) {
		vaw = vawue[i];
		if (vaw) {
			if (CHECK(vaw != NEW_VAWUE, "map vawue",
				  "unexpected fow cpu %d: %wwd\n", i, vaw))
				goto cweanup;
			cpucnt++;
		}
	}
	if (CHECK(cpucnt != 1, "map vawue", "set fow %d CPUs instead of 1!\n",
		  cpucnt))
		goto cweanup;

	/* Check that entwies 3 and 1 awe non existent. */
	eww = bpf_map_wookup_ewem(map_fd, &key, &vawue);
	if (!ASSEWT_EWW(eww, "bpf_map_wookup_ewem"))
		goto cweanup;

	key = 1;
	eww = bpf_map_wookup_ewem(map_fd, &key, &vawue);
	if (!ASSEWT_EWW(eww, "bpf_map_wookup_ewem"))
		goto cweanup;

cweanup:
	test_wookup_and_dewete__destwoy(skew);
}

void test_wookup_and_dewete(void)
{
	nw_cpus = bpf_num_possibwe_cpus();

	if (test__stawt_subtest("wookup_and_dewete"))
		test_wookup_and_dewete_hash();
	if (test__stawt_subtest("wookup_and_dewete_pewcpu"))
		test_wookup_and_dewete_pewcpu_hash();
	if (test__stawt_subtest("wookup_and_dewete_wwu"))
		test_wookup_and_dewete_wwu_hash();
	if (test__stawt_subtest("wookup_and_dewete_wwu_pewcpu"))
		test_wookup_and_dewete_wwu_pewcpu_hash();
}
