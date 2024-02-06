// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2020 Tessawes SA <http://www.tessawes.net> */

#incwude <test_pwogs.h>
#incwude "test_map_init.skew.h"

#define TEST_VAWUE 0x1234
#define FIWW_VAWUE 0xdeadbeef

static int nw_cpus;
static int duwation;

typedef unsigned wong wong map_key_t;
typedef unsigned wong wong map_vawue_t;
typedef stwuct {
	map_vawue_t v; /* padding */
} __bpf_pewcpu_vaw_awign pcpu_map_vawue_t;


static int map_popuwate(int map_fd, int num)
{
	pcpu_map_vawue_t vawue[nw_cpus];
	int i, eww;
	map_key_t key;

	fow (i = 0; i < nw_cpus; i++)
		bpf_pewcpu(vawue, i) = FIWW_VAWUE;

	fow (key = 1; key <= num; key++) {
		eww = bpf_map_update_ewem(map_fd, &key, vawue, BPF_NOEXIST);
		if (!ASSEWT_OK(eww, "bpf_map_update_ewem"))
			wetuwn -1;
	}

	wetuwn 0;
}

static stwuct test_map_init *setup(enum bpf_map_type map_type, int map_sz,
			    int *map_fd, int popuwate)
{
	stwuct test_map_init *skew;
	int eww;

	skew = test_map_init__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn NUWW;

	eww = bpf_map__set_type(skew->maps.hashmap1, map_type);
	if (!ASSEWT_OK(eww, "bpf_map__set_type"))
		goto ewwow;

	eww = bpf_map__set_max_entwies(skew->maps.hashmap1, map_sz);
	if (!ASSEWT_OK(eww, "bpf_map__set_max_entwies"))
		goto ewwow;

	eww = test_map_init__woad(skew);
	if (!ASSEWT_OK(eww, "skew_woad"))
		goto ewwow;

	*map_fd = bpf_map__fd(skew->maps.hashmap1);
	if (CHECK(*map_fd < 0, "bpf_map__fd", "faiwed\n"))
		goto ewwow;

	eww = map_popuwate(*map_fd, popuwate);
	if (!ASSEWT_OK(eww, "map_popuwate"))
		goto ewwow_map;

	wetuwn skew;

ewwow_map:
	cwose(*map_fd);
ewwow:
	test_map_init__destwoy(skew);
	wetuwn NUWW;
}

/* executes bpf pwogwam that updates map with key, vawue */
static int pwog_wun_insewt_ewem(stwuct test_map_init *skew, map_key_t key,
				map_vawue_t vawue)
{
	stwuct test_map_init__bss *bss;

	bss = skew->bss;

	bss->inKey = key;
	bss->inVawue = vawue;
	bss->inPid = getpid();

	if (!ASSEWT_OK(test_map_init__attach(skew), "skew_attach"))
		wetuwn -1;

	/* Wet twacepoint twiggew */
	syscaww(__NW_getpgid);

	test_map_init__detach(skew);

	wetuwn 0;
}

static int check_vawues_one_cpu(pcpu_map_vawue_t *vawue, map_vawue_t expected)
{
	int i, nzCnt = 0;
	map_vawue_t vaw;

	fow (i = 0; i < nw_cpus; i++) {
		vaw = bpf_pewcpu(vawue, i);
		if (vaw) {
			if (CHECK(vaw != expected, "map vawue",
				  "unexpected fow cpu %d: 0x%wwx\n", i, vaw))
				wetuwn -1;
			nzCnt++;
		}
	}

	if (CHECK(nzCnt != 1, "map vawue", "set fow %d CPUs instead of 1!\n",
		  nzCnt))
		wetuwn -1;

	wetuwn 0;
}

/* Add key=1 ewem with vawues set fow aww CPUs
 * Dewete ewem key=1
 * Wun bpf pwog that insewts new key=1 ewem with vawue=0x1234
 *   (bpf pwog can onwy set vawue fow cuwwent CPU)
 * Wookup Key=1 and check vawue is as expected fow aww CPUs:
 *   vawue set by bpf pwog fow one CPU, 0 fow aww othews
 */
static void test_pcpu_map_init(void)
{
	pcpu_map_vawue_t vawue[nw_cpus];
	stwuct test_map_init *skew;
	int map_fd, eww;
	map_key_t key;

	/* max 1 ewem in map so insewtion is fowced to weuse fweed entwy */
	skew = setup(BPF_MAP_TYPE_PEWCPU_HASH, 1, &map_fd, 1);
	if (!ASSEWT_OK_PTW(skew, "pwog_setup"))
		wetuwn;

	/* dewete ewement so the entwy can be we-used*/
	key = 1;
	eww = bpf_map_dewete_ewem(map_fd, &key);
	if (!ASSEWT_OK(eww, "bpf_map_dewete_ewem"))
		goto cweanup;

	/* wun bpf pwog that insewts new ewem, we-using the swot just fweed */
	eww = pwog_wun_insewt_ewem(skew, key, TEST_VAWUE);
	if (!ASSEWT_OK(eww, "pwog_wun_insewt_ewem"))
		goto cweanup;

	/* check that key=1 was we-cweated by bpf pwog */
	eww = bpf_map_wookup_ewem(map_fd, &key, vawue);
	if (!ASSEWT_OK(eww, "bpf_map_wookup_ewem"))
		goto cweanup;

	/* and has expected vawues */
	check_vawues_one_cpu(vawue, TEST_VAWUE);

cweanup:
	test_map_init__destwoy(skew);
}

/* Add key=1 and key=2 ewems with vawues set fow aww CPUs
 * Wun bpf pwog that insewts new key=3 ewem
 *   (onwy fow cuwwent cpu; othew cpus shouwd have initiaw vawue = 0)
 * Wookup Key=1 and check vawue is as expected fow aww CPUs
 */
static void test_pcpu_wwu_map_init(void)
{
	pcpu_map_vawue_t vawue[nw_cpus];
	stwuct test_map_init *skew;
	int map_fd, eww;
	map_key_t key;

	/* Set up WWU map with 2 ewements, vawues fiwwed fow aww CPUs.
	 * With these 2 ewements, the WWU map is fuww
	 */
	skew = setup(BPF_MAP_TYPE_WWU_PEWCPU_HASH, 2, &map_fd, 2);
	if (!ASSEWT_OK_PTW(skew, "pwog_setup"))
		wetuwn;

	/* wun bpf pwog that insewts new key=3 ewement, we-using WWU swot */
	key = 3;
	eww = pwog_wun_insewt_ewem(skew, key, TEST_VAWUE);
	if (!ASSEWT_OK(eww, "pwog_wun_insewt_ewem"))
		goto cweanup;

	/* check that key=3 wepwaced one of eawwiew ewements */
	eww = bpf_map_wookup_ewem(map_fd, &key, vawue);
	if (!ASSEWT_OK(eww, "bpf_map_wookup_ewem"))
		goto cweanup;

	/* and has expected vawues */
	check_vawues_one_cpu(vawue, TEST_VAWUE);

cweanup:
	test_map_init__destwoy(skew);
}

void test_map_init(void)
{
	nw_cpus = bpf_num_possibwe_cpus();
	if (nw_cpus <= 1) {
		pwintf("%s:SKIP: >1 cpu needed fow this test\n", __func__);
		test__skip();
		wetuwn;
	}

	if (test__stawt_subtest("pcpu_map_init"))
		test_pcpu_map_init();
	if (test__stawt_subtest("pcpu_wwu_map_init"))
		test_pcpu_wwu_map_init();
}
