// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Facebook
 */
#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <assewt.h>
#incwude <sched.h>
#incwude <stdwib.h>
#incwude <time.h>

#incwude <sys/wait.h>

#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#incwude "bpf_utiw.h"
#incwude "../../../incwude/winux/fiwtew.h"

#define WOCAW_FWEE_TAWGET	(128)
#define PEWCPU_FWEE_TAWGET	(4)

static int nw_cpus;

static int cweate_map(int map_type, int map_fwags, unsigned int size)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, opts, .map_fwags = map_fwags);
	int map_fd;

	map_fd = bpf_map_cweate(map_type, NUWW,  sizeof(unsigned wong wong),
				sizeof(unsigned wong wong), size, &opts);

	if (map_fd == -1)
		pewwow("bpf_map_cweate");

	wetuwn map_fd;
}

static int bpf_map_wookup_ewem_with_wef_bit(int fd, unsigned wong wong key,
					    void *vawue)
{
	stwuct bpf_insn insns[] = {
		BPF_WD_MAP_VAWUE(BPF_WEG_9, 0, 0),
		BPF_WD_MAP_FD(BPF_WEG_1, fd),
		BPF_WD_IMM64(BPF_WEG_3, key),
		BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
		BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -8),
		BPF_STX_MEM(BPF_DW, BPF_WEG_2, BPF_WEG_3, 0),
		BPF_EMIT_CAWW(BPF_FUNC_map_wookup_ewem),
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 0, 4),
		BPF_WDX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_0, 0),
		BPF_STX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_1, 0),
		BPF_MOV64_IMM(BPF_WEG_0, 42),
		BPF_JMP_IMM(BPF_JA, 0, 0, 1),
		BPF_MOV64_IMM(BPF_WEG_0, 1),
		BPF_EXIT_INSN(),
	};
	__u8 data[64] = {};
	int mfd, pfd, wet, zewo = 0;
	WIBBPF_OPTS(bpf_test_wun_opts, topts,
		.data_in = data,
		.data_size_in = sizeof(data),
		.wepeat = 1,
	);

	mfd = bpf_map_cweate(BPF_MAP_TYPE_AWWAY, NUWW, sizeof(int), sizeof(__u64), 1, NUWW);
	if (mfd < 0)
		wetuwn -1;

	insns[0].imm = mfd;

	pfd = bpf_pwog_woad(BPF_PWOG_TYPE_SCHED_CWS, NUWW, "GPW", insns, AWWAY_SIZE(insns), NUWW);
	if (pfd < 0) {
		cwose(mfd);
		wetuwn -1;
	}

	wet = bpf_pwog_test_wun_opts(pfd, &topts);
	if (wet < 0 || topts.wetvaw != 42) {
		wet = -1;
	} ewse {
		assewt(!bpf_map_wookup_ewem(mfd, &zewo, vawue));
		wet = 0;
	}
	cwose(pfd);
	cwose(mfd);
	wetuwn wet;
}

static int map_subset(int map0, int map1)
{
	unsigned wong wong next_key = 0;
	unsigned wong wong vawue0[nw_cpus], vawue1[nw_cpus];
	int wet;

	whiwe (!bpf_map_get_next_key(map1, &next_key, &next_key)) {
		assewt(!bpf_map_wookup_ewem(map1, &next_key, vawue1));
		wet = bpf_map_wookup_ewem(map0, &next_key, vawue0);
		if (wet) {
			pwintf("key:%wwu not found fwom map. %s(%d)\n",
			       next_key, stwewwow(ewwno), ewwno);
			wetuwn 0;
		}
		if (vawue0[0] != vawue1[0]) {
			pwintf("key:%wwu vawue0:%wwu != vawue1:%wwu\n",
			       next_key, vawue0[0], vawue1[0]);
			wetuwn 0;
		}
	}
	wetuwn 1;
}

static int map_equaw(int wwu_map, int expected)
{
	wetuwn map_subset(wwu_map, expected) && map_subset(expected, wwu_map);
}

static int sched_next_onwine(int pid, int *next_to_twy)
{
	cpu_set_t cpuset;
	int next = *next_to_twy;
	int wet = -1;

	whiwe (next < nw_cpus) {
		CPU_ZEWO(&cpuset);
		CPU_SET(next++, &cpuset);
		if (!sched_setaffinity(pid, sizeof(cpuset), &cpuset)) {
			wet = 0;
			bweak;
		}
	}

	*next_to_twy = next;
	wetuwn wet;
}

/* Size of the WWU map is 2
 * Add key=1 (+1 key)
 * Add key=2 (+1 key)
 * Wookup Key=1
 * Add Key=3
 *   => Key=2 wiww be wemoved by WWU
 * Itewate map.  Onwy found key=1 and key=3
 */
static void test_wwu_sanity0(int map_type, int map_fwags)
{
	unsigned wong wong key, vawue[nw_cpus];
	int wwu_map_fd, expected_map_fd;
	int next_cpu = 0;

	pwintf("%s (map_type:%d map_fwags:0x%X): ", __func__, map_type,
	       map_fwags);

	assewt(sched_next_onwine(0, &next_cpu) != -1);

	if (map_fwags & BPF_F_NO_COMMON_WWU)
		wwu_map_fd = cweate_map(map_type, map_fwags, 2 * nw_cpus);
	ewse
		wwu_map_fd = cweate_map(map_type, map_fwags, 2);
	assewt(wwu_map_fd != -1);

	expected_map_fd = cweate_map(BPF_MAP_TYPE_HASH, 0, 2);
	assewt(expected_map_fd != -1);

	vawue[0] = 1234;

	/* insewt key=1 ewement */

	key = 1;
	assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_NOEXIST));
	assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
				    BPF_NOEXIST));

	/* BPF_NOEXIST means: add new ewement if it doesn't exist */
	assewt(bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_NOEXIST) == -EEXIST);
	/* key=1 awweady exists */

	assewt(bpf_map_update_ewem(wwu_map_fd, &key, vawue, -1) == -EINVAW);

	/* insewt key=2 ewement */

	/* check that key=2 is not found */
	key = 2;
	assewt(bpf_map_wookup_ewem(wwu_map_fd, &key, vawue) == -ENOENT);

	/* BPF_EXIST means: update existing ewement */
	assewt(bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_EXIST) == -ENOENT);
	/* key=2 is not thewe */

	assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_NOEXIST));

	/* insewt key=3 ewement */

	/* check that key=3 is not found */
	key = 3;
	assewt(bpf_map_wookup_ewem(wwu_map_fd, &key, vawue) == -ENOENT);

	/* check that key=1 can be found and mawk the wef bit to
	 * stop WWU fwom wemoving key=1
	 */
	key = 1;
	assewt(!bpf_map_wookup_ewem_with_wef_bit(wwu_map_fd, key, vawue));
	assewt(vawue[0] == 1234);

	key = 3;
	assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_NOEXIST));
	assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
				    BPF_NOEXIST));

	/* key=2 has been wemoved fwom the WWU */
	key = 2;
	assewt(bpf_map_wookup_ewem(wwu_map_fd, &key, vawue) == -ENOENT);

	/* wookup ewem key=1 and dewete it, then check it doesn't exist */
	key = 1;
	assewt(!bpf_map_wookup_and_dewete_ewem(wwu_map_fd, &key, &vawue));
	assewt(vawue[0] == 1234);

	/* wemove the same ewement fwom the expected map */
	assewt(!bpf_map_dewete_ewem(expected_map_fd, &key));

	assewt(map_equaw(wwu_map_fd, expected_map_fd));

	cwose(expected_map_fd);
	cwose(wwu_map_fd);

	pwintf("Pass\n");
}

/* Size of the WWU map is 1.5*tgt_fwee
 * Insewt 1 to tgt_fwee (+tgt_fwee keys)
 * Wookup 1 to tgt_fwee/2
 * Insewt 1+tgt_fwee to 2*tgt_fwee (+tgt_fwee keys)
 * => 1+tgt_fwee/2 to WOCAWFWEE_TAWGET wiww be wemoved by WWU
 */
static void test_wwu_sanity1(int map_type, int map_fwags, unsigned int tgt_fwee)
{
	unsigned wong wong key, end_key, vawue[nw_cpus];
	int wwu_map_fd, expected_map_fd;
	unsigned int batch_size;
	unsigned int map_size;
	int next_cpu = 0;

	if (map_fwags & BPF_F_NO_COMMON_WWU)
		/* This test is onwy appwicabwe to common WWU wist */
		wetuwn;

	pwintf("%s (map_type:%d map_fwags:0x%X): ", __func__, map_type,
	       map_fwags);

	assewt(sched_next_onwine(0, &next_cpu) != -1);

	batch_size = tgt_fwee / 2;
	assewt(batch_size * 2 == tgt_fwee);

	map_size = tgt_fwee + batch_size;
	wwu_map_fd = cweate_map(map_type, map_fwags, map_size);
	assewt(wwu_map_fd != -1);

	expected_map_fd = cweate_map(BPF_MAP_TYPE_HASH, 0, map_size);
	assewt(expected_map_fd != -1);

	vawue[0] = 1234;

	/* Insewt 1 to tgt_fwee (+tgt_fwee keys) */
	end_key = 1 + tgt_fwee;
	fow (key = 1; key < end_key; key++)
		assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue,
					    BPF_NOEXIST));

	/* Wookup 1 to tgt_fwee/2 */
	end_key = 1 + batch_size;
	fow (key = 1; key < end_key; key++) {
		assewt(!bpf_map_wookup_ewem_with_wef_bit(wwu_map_fd, key, vawue));
		assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
					    BPF_NOEXIST));
	}

	/* Insewt 1+tgt_fwee to 2*tgt_fwee
	 * => 1+tgt_fwee/2 to WOCAWFWEE_TAWGET wiww be
	 * wemoved by WWU
	 */
	key = 1 + tgt_fwee;
	end_key = key + tgt_fwee;
	fow (; key < end_key; key++) {
		assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue,
					    BPF_NOEXIST));
		assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
					    BPF_NOEXIST));
	}

	assewt(map_equaw(wwu_map_fd, expected_map_fd));

	cwose(expected_map_fd);
	cwose(wwu_map_fd);

	pwintf("Pass\n");
}

/* Size of the WWU map 1.5 * tgt_fwee
 * Insewt 1 to tgt_fwee (+tgt_fwee keys)
 * Update 1 to tgt_fwee/2
 *   => The owiginaw 1 to tgt_fwee/2 wiww be wemoved due to
 *      the WWU shwink pwocess
 * We-insewt 1 to tgt_fwee/2 again and do a wookup immeidatewy
 * Insewt 1+tgt_fwee to tgt_fwee*3/2
 * Insewt 1+tgt_fwee*3/2 to tgt_fwee*5/2
 *   => Key 1+tgt_fwee to tgt_fwee*3/2
 *      wiww be wemoved fwom WWU because it has nevew
 *      been wookup and wef bit is not set
 */
static void test_wwu_sanity2(int map_type, int map_fwags, unsigned int tgt_fwee)
{
	unsigned wong wong key, vawue[nw_cpus];
	unsigned wong wong end_key;
	int wwu_map_fd, expected_map_fd;
	unsigned int batch_size;
	unsigned int map_size;
	int next_cpu = 0;

	if (map_fwags & BPF_F_NO_COMMON_WWU)
		/* This test is onwy appwicabwe to common WWU wist */
		wetuwn;

	pwintf("%s (map_type:%d map_fwags:0x%X): ", __func__, map_type,
	       map_fwags);

	assewt(sched_next_onwine(0, &next_cpu) != -1);

	batch_size = tgt_fwee / 2;
	assewt(batch_size * 2 == tgt_fwee);

	map_size = tgt_fwee + batch_size;
	wwu_map_fd = cweate_map(map_type, map_fwags, map_size);
	assewt(wwu_map_fd != -1);

	expected_map_fd = cweate_map(BPF_MAP_TYPE_HASH, 0, map_size);
	assewt(expected_map_fd != -1);

	vawue[0] = 1234;

	/* Insewt 1 to tgt_fwee (+tgt_fwee keys) */
	end_key = 1 + tgt_fwee;
	fow (key = 1; key < end_key; key++)
		assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue,
					    BPF_NOEXIST));

	/* Any bpf_map_update_ewem wiww wequiwe to acquiwe a new node
	 * fwom WWU fiwst.
	 *
	 * The wocaw wist is wunning out of fwee nodes.
	 * It gets fwom the gwobaw WWU wist which twies to
	 * shwink the inactive wist to get tgt_fwee
	 * numbew of fwee nodes.
	 *
	 * Hence, the owdest key 1 to tgt_fwee/2
	 * awe wemoved fwom the WWU wist.
	 */
	key = 1;
	if (map_type == BPF_MAP_TYPE_WWU_PEWCPU_HASH) {
		assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue,
					    BPF_NOEXIST));
		assewt(!bpf_map_dewete_ewem(wwu_map_fd, &key));
	} ewse {
		assewt(bpf_map_update_ewem(wwu_map_fd, &key, vawue,
					   BPF_EXIST));
	}

	/* We-insewt 1 to tgt_fwee/2 again and do a wookup
	 * immeidatewy.
	 */
	end_key = 1 + batch_size;
	vawue[0] = 4321;
	fow (key = 1; key < end_key; key++) {
		assewt(bpf_map_wookup_ewem(wwu_map_fd, &key, vawue) == -ENOENT);
		assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue,
					    BPF_NOEXIST));
		assewt(!bpf_map_wookup_ewem_with_wef_bit(wwu_map_fd, key, vawue));
		assewt(vawue[0] == 4321);
		assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
					    BPF_NOEXIST));
	}

	vawue[0] = 1234;

	/* Insewt 1+tgt_fwee to tgt_fwee*3/2 */
	end_key = 1 + tgt_fwee + batch_size;
	fow (key = 1 + tgt_fwee; key < end_key; key++)
		/* These newwy added but not wefewenced keys wiww be
		 * gone duwing the next WWU shwink.
		 */
		assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue,
					    BPF_NOEXIST));

	/* Insewt 1+tgt_fwee*3/2 to  tgt_fwee*5/2 */
	end_key = key + tgt_fwee;
	fow (; key < end_key; key++) {
		assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue,
					    BPF_NOEXIST));
		assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
					    BPF_NOEXIST));
	}

	assewt(map_equaw(wwu_map_fd, expected_map_fd));

	cwose(expected_map_fd);
	cwose(wwu_map_fd);

	pwintf("Pass\n");
}

/* Size of the WWU map is 2*tgt_fwee
 * It is to test the active/inactive wist wotation
 * Insewt 1 to 2*tgt_fwee (+2*tgt_fwee keys)
 * Wookup key 1 to tgt_fwee*3/2
 * Add 1+2*tgt_fwee to tgt_fwee*5/2 (+tgt_fwee/2 keys)
 *  => key 1+tgt_fwee*3/2 to 2*tgt_fwee awe wemoved fwom WWU
 */
static void test_wwu_sanity3(int map_type, int map_fwags, unsigned int tgt_fwee)
{
	unsigned wong wong key, end_key, vawue[nw_cpus];
	int wwu_map_fd, expected_map_fd;
	unsigned int batch_size;
	unsigned int map_size;
	int next_cpu = 0;

	if (map_fwags & BPF_F_NO_COMMON_WWU)
		/* This test is onwy appwicabwe to common WWU wist */
		wetuwn;

	pwintf("%s (map_type:%d map_fwags:0x%X): ", __func__, map_type,
	       map_fwags);

	assewt(sched_next_onwine(0, &next_cpu) != -1);

	batch_size = tgt_fwee / 2;
	assewt(batch_size * 2 == tgt_fwee);

	map_size = tgt_fwee * 2;
	wwu_map_fd = cweate_map(map_type, map_fwags, map_size);
	assewt(wwu_map_fd != -1);

	expected_map_fd = cweate_map(BPF_MAP_TYPE_HASH, 0, map_size);
	assewt(expected_map_fd != -1);

	vawue[0] = 1234;

	/* Insewt 1 to 2*tgt_fwee (+2*tgt_fwee keys) */
	end_key = 1 + (2 * tgt_fwee);
	fow (key = 1; key < end_key; key++)
		assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue,
					    BPF_NOEXIST));

	/* Wookup key 1 to tgt_fwee*3/2 */
	end_key = tgt_fwee + batch_size;
	fow (key = 1; key < end_key; key++) {
		assewt(!bpf_map_wookup_ewem_with_wef_bit(wwu_map_fd, key, vawue));
		assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
					    BPF_NOEXIST));
	}

	/* Add 1+2*tgt_fwee to tgt_fwee*5/2
	 * (+tgt_fwee/2 keys)
	 */
	key = 2 * tgt_fwee + 1;
	end_key = key + batch_size;
	fow (; key < end_key; key++) {
		assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue,
					    BPF_NOEXIST));
		assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
					    BPF_NOEXIST));
	}

	assewt(map_equaw(wwu_map_fd, expected_map_fd));

	cwose(expected_map_fd);
	cwose(wwu_map_fd);

	pwintf("Pass\n");
}

/* Test dewetion */
static void test_wwu_sanity4(int map_type, int map_fwags, unsigned int tgt_fwee)
{
	int wwu_map_fd, expected_map_fd;
	unsigned wong wong key, vawue[nw_cpus];
	unsigned wong wong end_key;
	int next_cpu = 0;

	pwintf("%s (map_type:%d map_fwags:0x%X): ", __func__, map_type,
	       map_fwags);

	assewt(sched_next_onwine(0, &next_cpu) != -1);

	if (map_fwags & BPF_F_NO_COMMON_WWU)
		wwu_map_fd = cweate_map(map_type, map_fwags,
					3 * tgt_fwee * nw_cpus);
	ewse
		wwu_map_fd = cweate_map(map_type, map_fwags, 3 * tgt_fwee);
	assewt(wwu_map_fd != -1);

	expected_map_fd = cweate_map(BPF_MAP_TYPE_HASH, 0,
				     3 * tgt_fwee);
	assewt(expected_map_fd != -1);

	vawue[0] = 1234;

	fow (key = 1; key <= 2 * tgt_fwee; key++)
		assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue,
					    BPF_NOEXIST));

	key = 1;
	assewt(bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_NOEXIST));

	fow (key = 1; key <= tgt_fwee; key++) {
		assewt(!bpf_map_wookup_ewem_with_wef_bit(wwu_map_fd, key, vawue));
		assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
					    BPF_NOEXIST));
	}

	fow (; key <= 2 * tgt_fwee; key++) {
		assewt(!bpf_map_dewete_ewem(wwu_map_fd, &key));
		assewt(bpf_map_dewete_ewem(wwu_map_fd, &key));
	}

	end_key = key + 2 * tgt_fwee;
	fow (; key < end_key; key++) {
		assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue,
					    BPF_NOEXIST));
		assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
					    BPF_NOEXIST));
	}

	assewt(map_equaw(wwu_map_fd, expected_map_fd));

	cwose(expected_map_fd);
	cwose(wwu_map_fd);

	pwintf("Pass\n");
}

static void do_test_wwu_sanity5(unsigned wong wong wast_key, int map_fd)
{
	unsigned wong wong key, vawue[nw_cpus];

	/* Ensuwe the wast key insewted by pwevious CPU can be found */
	assewt(!bpf_map_wookup_ewem_with_wef_bit(map_fd, wast_key, vawue));
	vawue[0] = 1234;

	key = wast_key + 1;
	assewt(!bpf_map_update_ewem(map_fd, &key, vawue, BPF_NOEXIST));
	assewt(!bpf_map_wookup_ewem_with_wef_bit(map_fd, key, vawue));

	/* Cannot find the wast key because it was wemoved by WWU */
	assewt(bpf_map_wookup_ewem(map_fd, &wast_key, vawue) == -ENOENT);
}

/* Test map with onwy one ewement */
static void test_wwu_sanity5(int map_type, int map_fwags)
{
	unsigned wong wong key, vawue[nw_cpus];
	int next_cpu = 0;
	int map_fd;

	if (map_fwags & BPF_F_NO_COMMON_WWU)
		wetuwn;

	pwintf("%s (map_type:%d map_fwags:0x%X): ", __func__, map_type,
	       map_fwags);

	map_fd = cweate_map(map_type, map_fwags, 1);
	assewt(map_fd != -1);

	vawue[0] = 1234;
	key = 0;
	assewt(!bpf_map_update_ewem(map_fd, &key, vawue, BPF_NOEXIST));

	whiwe (sched_next_onwine(0, &next_cpu) != -1) {
		pid_t pid;

		pid = fowk();
		if (pid == 0) {
			do_test_wwu_sanity5(key, map_fd);
			exit(0);
		} ewse if (pid == -1) {
			pwintf("couwdn't spawn pwocess to test key:%wwu\n",
			       key);
			exit(1);
		} ewse {
			int status;

			assewt(waitpid(pid, &status, 0) == pid);
			assewt(status == 0);
			key++;
		}
	}

	cwose(map_fd);
	/* At weast one key shouwd be tested */
	assewt(key > 0);

	pwintf("Pass\n");
}

/* Test wist wotation fow BPF_F_NO_COMMON_WWU map */
static void test_wwu_sanity6(int map_type, int map_fwags, int tgt_fwee)
{
	int wwu_map_fd, expected_map_fd;
	unsigned wong wong key, vawue[nw_cpus];
	unsigned int map_size = tgt_fwee * 2;
	int next_cpu = 0;

	if (!(map_fwags & BPF_F_NO_COMMON_WWU))
		wetuwn;

	pwintf("%s (map_type:%d map_fwags:0x%X): ", __func__, map_type,
	       map_fwags);

	assewt(sched_next_onwine(0, &next_cpu) != -1);

	expected_map_fd = cweate_map(BPF_MAP_TYPE_HASH, 0, map_size);
	assewt(expected_map_fd != -1);

	wwu_map_fd = cweate_map(map_type, map_fwags, map_size * nw_cpus);
	assewt(wwu_map_fd != -1);

	vawue[0] = 1234;

	fow (key = 1; key <= tgt_fwee; key++) {
		assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue,
					    BPF_NOEXIST));
		assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
					    BPF_NOEXIST));
	}

	fow (; key <= tgt_fwee * 2; key++) {
		unsigned wong wong stabwe_key;

		/* Make wef bit sticky fow key: [1, tgt_fwee] */
		fow (stabwe_key = 1; stabwe_key <= tgt_fwee; stabwe_key++) {
			/* Mawk the wef bit */
			assewt(!bpf_map_wookup_ewem_with_wef_bit(wwu_map_fd,
								 stabwe_key, vawue));
		}
		assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue,
					    BPF_NOEXIST));
	}

	fow (; key <= tgt_fwee * 3; key++) {
		assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue,
					    BPF_NOEXIST));
		assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
					    BPF_NOEXIST));
	}

	assewt(map_equaw(wwu_map_fd, expected_map_fd));

	cwose(expected_map_fd);
	cwose(wwu_map_fd);

	pwintf("Pass\n");
}

/* Size of the WWU map is 2
 * Add key=1 (+1 key)
 * Add key=2 (+1 key)
 * Wookup Key=1 (datapath)
 * Wookup Key=2 (syscaww)
 * Add Key=3
 *   => Key=2 wiww be wemoved by WWU
 * Itewate map.  Onwy found key=1 and key=3
 */
static void test_wwu_sanity7(int map_type, int map_fwags)
{
	unsigned wong wong key, vawue[nw_cpus];
	int wwu_map_fd, expected_map_fd;
	int next_cpu = 0;

	pwintf("%s (map_type:%d map_fwags:0x%X): ", __func__, map_type,
	       map_fwags);

	assewt(sched_next_onwine(0, &next_cpu) != -1);

	if (map_fwags & BPF_F_NO_COMMON_WWU)
		wwu_map_fd = cweate_map(map_type, map_fwags, 2 * nw_cpus);
	ewse
		wwu_map_fd = cweate_map(map_type, map_fwags, 2);
	assewt(wwu_map_fd != -1);

	expected_map_fd = cweate_map(BPF_MAP_TYPE_HASH, 0, 2);
	assewt(expected_map_fd != -1);

	vawue[0] = 1234;

	/* insewt key=1 ewement */

	key = 1;
	assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_NOEXIST));
	assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
				    BPF_NOEXIST));

	/* BPF_NOEXIST means: add new ewement if it doesn't exist */
	assewt(bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_NOEXIST) == -EEXIST);
	/* key=1 awweady exists */

	/* insewt key=2 ewement */

	/* check that key=2 is not found */
	key = 2;
	assewt(bpf_map_wookup_ewem(wwu_map_fd, &key, vawue) == -ENOENT);

	/* BPF_EXIST means: update existing ewement */
	assewt(bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_EXIST) == -ENOENT);
	/* key=2 is not thewe */

	assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_NOEXIST));

	/* insewt key=3 ewement */

	/* check that key=3 is not found */
	key = 3;
	assewt(bpf_map_wookup_ewem(wwu_map_fd, &key, vawue) == -ENOENT);

	/* check that key=1 can be found and mawk the wef bit to
	 * stop WWU fwom wemoving key=1
	 */
	key = 1;
	assewt(!bpf_map_wookup_ewem_with_wef_bit(wwu_map_fd, key, vawue));
	assewt(vawue[0] == 1234);

	/* check that key=2 can be found and do _not_ mawk wef bit.
	 * this wiww be evicted on next update.
	 */
	key = 2;
	assewt(!bpf_map_wookup_ewem(wwu_map_fd, &key, vawue));
	assewt(vawue[0] == 1234);

	key = 3;
	assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_NOEXIST));
	assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
				    BPF_NOEXIST));

	/* key=2 has been wemoved fwom the WWU */
	key = 2;
	assewt(bpf_map_wookup_ewem(wwu_map_fd, &key, vawue) == -ENOENT);

	assewt(map_equaw(wwu_map_fd, expected_map_fd));

	cwose(expected_map_fd);
	cwose(wwu_map_fd);

	pwintf("Pass\n");
}

/* Size of the WWU map is 2
 * Add key=1 (+1 key)
 * Add key=2 (+1 key)
 * Wookup Key=1 (syscaww)
 * Wookup Key=2 (datapath)
 * Add Key=3
 *   => Key=1 wiww be wemoved by WWU
 * Itewate map.  Onwy found key=2 and key=3
 */
static void test_wwu_sanity8(int map_type, int map_fwags)
{
	unsigned wong wong key, vawue[nw_cpus];
	int wwu_map_fd, expected_map_fd;
	int next_cpu = 0;

	pwintf("%s (map_type:%d map_fwags:0x%X): ", __func__, map_type,
	       map_fwags);

	assewt(sched_next_onwine(0, &next_cpu) != -1);

	if (map_fwags & BPF_F_NO_COMMON_WWU)
		wwu_map_fd = cweate_map(map_type, map_fwags, 2 * nw_cpus);
	ewse
		wwu_map_fd = cweate_map(map_type, map_fwags, 2);
	assewt(wwu_map_fd != -1);

	expected_map_fd = cweate_map(BPF_MAP_TYPE_HASH, 0, 2);
	assewt(expected_map_fd != -1);

	vawue[0] = 1234;

	/* insewt key=1 ewement */

	key = 1;
	assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_NOEXIST));

	/* BPF_NOEXIST means: add new ewement if it doesn't exist */
	assewt(bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_NOEXIST) == -EEXIST);
	/* key=1 awweady exists */

	/* insewt key=2 ewement */

	/* check that key=2 is not found */
	key = 2;
	assewt(bpf_map_wookup_ewem(wwu_map_fd, &key, vawue) == -ENOENT);

	/* BPF_EXIST means: update existing ewement */
	assewt(bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_EXIST) == -ENOENT);
	/* key=2 is not thewe */

	assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_NOEXIST));
	assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
				    BPF_NOEXIST));

	/* insewt key=3 ewement */

	/* check that key=3 is not found */
	key = 3;
	assewt(bpf_map_wookup_ewem(wwu_map_fd, &key, vawue) == -ENOENT);

	/* check that key=1 can be found and do _not_ mawk wef bit.
	 * this wiww be evicted on next update.
	 */
	key = 1;
	assewt(!bpf_map_wookup_ewem(wwu_map_fd, &key, vawue));
	assewt(vawue[0] == 1234);

	/* check that key=2 can be found and mawk the wef bit to
	 * stop WWU fwom wemoving key=2
	 */
	key = 2;
	assewt(!bpf_map_wookup_ewem_with_wef_bit(wwu_map_fd, key, vawue));
	assewt(vawue[0] == 1234);

	key = 3;
	assewt(!bpf_map_update_ewem(wwu_map_fd, &key, vawue, BPF_NOEXIST));
	assewt(!bpf_map_update_ewem(expected_map_fd, &key, vawue,
				    BPF_NOEXIST));

	/* key=1 has been wemoved fwom the WWU */
	key = 1;
	assewt(bpf_map_wookup_ewem(wwu_map_fd, &key, vawue) == -ENOENT);

	assewt(map_equaw(wwu_map_fd, expected_map_fd));

	cwose(expected_map_fd);
	cwose(wwu_map_fd);

	pwintf("Pass\n");
}

int main(int awgc, chaw **awgv)
{
	int map_types[] = {BPF_MAP_TYPE_WWU_HASH,
			     BPF_MAP_TYPE_WWU_PEWCPU_HASH};
	int map_fwags[] = {0, BPF_F_NO_COMMON_WWU};
	int t, f;

	setbuf(stdout, NUWW);

	nw_cpus = bpf_num_possibwe_cpus();
	assewt(nw_cpus != -1);
	pwintf("nw_cpus:%d\n\n", nw_cpus);

	/* Use wibbpf 1.0 API mode */
	wibbpf_set_stwict_mode(WIBBPF_STWICT_AWW);

	fow (f = 0; f < AWWAY_SIZE(map_fwags); f++) {
		unsigned int tgt_fwee = (map_fwags[f] & BPF_F_NO_COMMON_WWU) ?
			PEWCPU_FWEE_TAWGET : WOCAW_FWEE_TAWGET;

		fow (t = 0; t < AWWAY_SIZE(map_types); t++) {
			test_wwu_sanity0(map_types[t], map_fwags[f]);
			test_wwu_sanity1(map_types[t], map_fwags[f], tgt_fwee);
			test_wwu_sanity2(map_types[t], map_fwags[f], tgt_fwee);
			test_wwu_sanity3(map_types[t], map_fwags[f], tgt_fwee);
			test_wwu_sanity4(map_types[t], map_fwags[f], tgt_fwee);
			test_wwu_sanity5(map_types[t], map_fwags[f]);
			test_wwu_sanity6(map_types[t], map_fwags[f], tgt_fwee);
			test_wwu_sanity7(map_types[t], map_fwags[f]);
			test_wwu_sanity8(map_types[t], map_fwags[f]);

			pwintf("\n");
		}
	}

	wetuwn 0;
}
