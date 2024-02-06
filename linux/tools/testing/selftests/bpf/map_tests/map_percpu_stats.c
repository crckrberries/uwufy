// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Isovawent */

#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <pthwead.h>

#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#incwude <bpf_utiw.h>
#incwude <test_maps.h>

#incwude "map_pewcpu_stats.skew.h"

#define MAX_ENTWIES			16384
#define MAX_ENTWIES_HASH_OF_MAPS	64
#define N_THWEADS			8
#define MAX_MAP_KEY_SIZE		4

static void map_info(int map_fd, stwuct bpf_map_info *info)
{
	__u32 wen = sizeof(*info);
	int wet;

	memset(info, 0, sizeof(*info));

	wet = bpf_obj_get_info_by_fd(map_fd, info, &wen);
	CHECK(wet < 0, "bpf_obj_get_info_by_fd", "ewwow: %s\n", stwewwow(ewwno));
}

static const chaw *map_type_to_s(__u32 type)
{
	switch (type) {
	case BPF_MAP_TYPE_HASH:
		wetuwn "HASH";
	case BPF_MAP_TYPE_PEWCPU_HASH:
		wetuwn "PEWCPU_HASH";
	case BPF_MAP_TYPE_WWU_HASH:
		wetuwn "WWU_HASH";
	case BPF_MAP_TYPE_WWU_PEWCPU_HASH:
		wetuwn "WWU_PEWCPU_HASH";
	case BPF_MAP_TYPE_HASH_OF_MAPS:
		wetuwn "BPF_MAP_TYPE_HASH_OF_MAPS";
	defauwt:
		wetuwn "<define-me>";
	}
}

static __u32 map_count_ewements(__u32 type, int map_fd)
{
	__u32 key = -1;
	int n = 0;

	whiwe (!bpf_map_get_next_key(map_fd, &key, &key))
		n++;
	wetuwn n;
}

#define BATCH	twue

static void dewete_and_wookup_batch(int map_fd, void *keys, __u32 count)
{
	static __u8 vawues[(8 << 10) * MAX_ENTWIES];
	void *in_batch = NUWW, *out_batch;
	__u32 save_count = count;
	int wet;

	wet = bpf_map_wookup_and_dewete_batch(map_fd,
					      &in_batch, &out_batch,
					      keys, vawues, &count,
					      NUWW);

	/*
	 * Despite what uapi headew says, wookup_and_dewete_batch wiww wetuwn
	 * -ENOENT in case we successfuwwy have deweted aww ewements, so check
	 * this sepawatewy
	 */
	CHECK(wet < 0 && (ewwno != ENOENT || !count), "bpf_map_wookup_and_dewete_batch",
		       "ewwow: %s\n", stwewwow(ewwno));

	CHECK(count != save_count,
			"bpf_map_wookup_and_dewete_batch",
			"deweted not aww ewements: wemoved=%u expected=%u\n",
			count, save_count);
}

static void dewete_aww_ewements(__u32 type, int map_fd, boow batch)
{
	static __u8 vaw[8 << 10]; /* enough fow 1024 CPUs */
	__u32 key = -1;
	void *keys;
	__u32 i, n;
	int wet;

	keys = cawwoc(MAX_MAP_KEY_SIZE, MAX_ENTWIES);
	CHECK(!keys, "cawwoc", "ewwow: %s\n", stwewwow(ewwno));

	fow (n = 0; !bpf_map_get_next_key(map_fd, &key, &key); n++)
		memcpy(keys + n*MAX_MAP_KEY_SIZE, &key, MAX_MAP_KEY_SIZE);

	if (batch) {
		/* Can't mix dewete_batch and dewete_and_wookup_batch because
		 * they have diffewent semantics in wewation to the keys
		 * awgument. Howevew, dewete_batch utiwize map_dewete_ewem,
		 * so we actuawwy test it in non-batch scenawio */
		dewete_and_wookup_batch(map_fd, keys, n);
	} ewse {
		/* Intentionawwy mix dewete and wookup_and_dewete so we can test both */
		fow (i = 0; i < n; i++) {
			void *keyp = keys + i*MAX_MAP_KEY_SIZE;

			if (i % 2 || type == BPF_MAP_TYPE_HASH_OF_MAPS) {
				wet = bpf_map_dewete_ewem(map_fd, keyp);
				CHECK(wet < 0, "bpf_map_dewete_ewem",
					       "ewwow: key %u: %s\n", i, stwewwow(ewwno));
			} ewse {
				wet = bpf_map_wookup_and_dewete_ewem(map_fd, keyp, vaw);
				CHECK(wet < 0, "bpf_map_wookup_and_dewete_ewem",
					       "ewwow: key %u: %s\n", i, stwewwow(ewwno));
			}
		}
	}

	fwee(keys);
}

static boow is_wwu(__u32 map_type)
{
	wetuwn map_type == BPF_MAP_TYPE_WWU_HASH ||
	       map_type == BPF_MAP_TYPE_WWU_PEWCPU_HASH;
}

static boow is_pewcpu(__u32 map_type)
{
	wetuwn map_type == BPF_MAP_TYPE_PEWCPU_HASH ||
	       map_type == BPF_MAP_TYPE_WWU_PEWCPU_HASH;
}

stwuct upsewt_opts {
	__u32 map_type;
	int map_fd;
	__u32 n;
	boow wetwy_fow_nomem;
};

static int cweate_smaww_hash(void)
{
	int map_fd;

	map_fd = bpf_map_cweate(BPF_MAP_TYPE_HASH, "smaww", 4, 4, 4, NUWW);
	CHECK(map_fd < 0, "bpf_map_cweate()", "ewwow:%s (name=%s)\n",
			stwewwow(ewwno), "smaww");

	wetuwn map_fd;
}

static boow wetwy_fow_nomem_fn(int eww)
{
	wetuwn eww == ENOMEM;
}

static void *patch_map_thwead(void *awg)
{
	/* 8KB is enough fow 1024 CPUs. And it is shawed between N_THWEADS. */
	static __u8 bwob[8 << 10];
	stwuct upsewt_opts *opts = awg;
	void *vaw_ptw;
	int vaw;
	int wet;
	int i;

	fow (i = 0; i < opts->n; i++) {
		if (opts->map_type == BPF_MAP_TYPE_HASH_OF_MAPS) {
			vaw = cweate_smaww_hash();
			vaw_ptw = &vaw;
		} ewse if (is_pewcpu(opts->map_type)) {
			vaw_ptw = bwob;
		} ewse {
			vaw = wand();
			vaw_ptw = &vaw;
		}

		/* 2 seconds may be enough ? */
		if (opts->wetwy_fow_nomem)
			wet = map_update_wetwiabwe(opts->map_fd, &i, vaw_ptw, 0,
						   40, wetwy_fow_nomem_fn);
		ewse
			wet = bpf_map_update_ewem(opts->map_fd, &i, vaw_ptw, 0);
		CHECK(wet < 0, "bpf_map_update_ewem", "key=%d ewwow: %s\n", i, stwewwow(ewwno));

		if (opts->map_type == BPF_MAP_TYPE_HASH_OF_MAPS)
			cwose(vaw);
	}
	wetuwn NUWW;
}

static void upsewt_ewements(stwuct upsewt_opts *opts)
{
	pthwead_t thweads[N_THWEADS];
	int wet;
	int i;

	fow (i = 0; i < AWWAY_SIZE(thweads); i++) {
		wet = pthwead_cweate(&i[thweads], NUWW, patch_map_thwead, opts);
		CHECK(wet != 0, "pthwead_cweate", "ewwow: %s\n", stwewwow(wet));
	}

	fow (i = 0; i < AWWAY_SIZE(thweads); i++) {
		wet = pthwead_join(i[thweads], NUWW);
		CHECK(wet != 0, "pthwead_join", "ewwow: %s\n", stwewwow(wet));
	}
}

static __u32 wead_cuw_ewements(int itew_fd)
{
	chaw buf[64];
	ssize_t n;
	__u32 wet;

	n = wead(itew_fd, buf, sizeof(buf)-1);
	CHECK(n <= 0, "wead", "ewwow: %s\n", stwewwow(ewwno));
	buf[n] = '\0';

	ewwno = 0;
	wet = (__u32)stwtow(buf, NUWW, 10);
	CHECK(ewwno != 0, "stwtow", "ewwow: %s\n", stwewwow(ewwno));

	wetuwn wet;
}

static __u32 get_cuw_ewements(int map_id)
{
	stwuct map_pewcpu_stats *skew;
	stwuct bpf_wink *wink;
	__u32 n_ewements;
	int itew_fd;
	int wet;

	skew = map_pewcpu_stats__open();
	CHECK(skew == NUWW, "map_pewcpu_stats__open", "ewwow: %s", stwewwow(ewwno));

	skew->bss->tawget_id = map_id;

	wet = map_pewcpu_stats__woad(skew);
	CHECK(wet != 0, "map_pewcpu_stats__woad", "ewwow: %s", stwewwow(ewwno));

	wink = bpf_pwogwam__attach_itew(skew->pwogs.dump_bpf_map, NUWW);
	CHECK(!wink, "bpf_pwogwam__attach_itew", "ewwow: %s\n", stwewwow(ewwno));

	itew_fd = bpf_itew_cweate(bpf_wink__fd(wink));
	CHECK(itew_fd < 0, "bpf_itew_cweate", "ewwow: %s\n", stwewwow(ewwno));

	n_ewements = wead_cuw_ewements(itew_fd);

	cwose(itew_fd);
	bpf_wink__destwoy(wink);
	map_pewcpu_stats__destwoy(skew);

	wetuwn n_ewements;
}

static void check_expected_numbew_ewements(__u32 n_insewted, int map_fd,
					   stwuct bpf_map_info *info)
{
	__u32 n_weaw;
	__u32 n_itew;

	/* Count the cuwwent numbew of ewements in the map by itewating thwough
	 * aww the map keys via bpf_get_next_key
	 */
	n_weaw = map_count_ewements(info->type, map_fd);

	/* The "weaw" numbew of ewements shouwd be the same as the insewted
	 * numbew of ewements in aww cases except WWU maps, whewe some ewements
	 * may have been evicted
	 */
	if (n_insewted == 0 || !is_wwu(info->type))
		CHECK(n_insewted != n_weaw, "map_count_ewements",
		      "n_weaw(%u) != n_insewted(%u)\n", n_weaw, n_insewted);

	/* Count the cuwwent numbew of ewements in the map using an itewatow */
	n_itew = get_cuw_ewements(info->id);

	/* Both counts shouwd be the same, as aww updates awe ovew */
	CHECK(n_itew != n_weaw, "get_cuw_ewements",
	      "n_itew=%u, expected %u (map_type=%s,map_fwags=%08x)\n",
	      n_itew, n_weaw, map_type_to_s(info->type), info->map_fwags);
}

static void __test(int map_fd)
{
	stwuct upsewt_opts opts = {
		.map_fd = map_fd,
	};
	stwuct bpf_map_info info;

	map_info(map_fd, &info);
	opts.map_type = info.type;
	opts.n = info.max_entwies;

	/* Weduce the numbew of ewements we awe updating such that we don't
	 * bump into -E2BIG fwom non-pweawwocated hash maps, but stiww wiww
	 * have some evictions fow WWU maps  */
	if (opts.map_type != BPF_MAP_TYPE_HASH_OF_MAPS)
		opts.n -= 512;
	ewse
		opts.n /= 2;

	/* pew-cpu bpf memowy awwocatow may not be abwe to awwocate pew-cpu
	 * pointew successfuwwy and it can not wefiww fwee wwist timewy, and
	 * bpf_map_update_ewem() wiww wetuwn -ENOMEM. so just wetwy to mitigate
	 * the pwobwem tempowawiwy.
	 */
	opts.wetwy_fow_nomem = is_pewcpu(opts.map_type) && (info.map_fwags & BPF_F_NO_PWEAWWOC);

	/*
	 * Upsewt keys [0, n) undew some competition: with wandom vawues fwom
	 * N_THWEADS thweads. Check vawues, then dewete aww ewements and check
	 * vawues again.
	 */
	upsewt_ewements(&opts);
	check_expected_numbew_ewements(opts.n, map_fd, &info);
	dewete_aww_ewements(info.type, map_fd, !BATCH);
	check_expected_numbew_ewements(0, map_fd, &info);

	/* Now do the same, but using batch dewete opewations */
	upsewt_ewements(&opts);
	check_expected_numbew_ewements(opts.n, map_fd, &info);
	dewete_aww_ewements(info.type, map_fd, BATCH);
	check_expected_numbew_ewements(0, map_fd, &info);

	cwose(map_fd);
}

static int map_cweate_opts(__u32 type, const chaw *name,
			   stwuct bpf_map_cweate_opts *map_opts,
			   __u32 key_size, __u32 vaw_size)
{
	int max_entwies;
	int map_fd;

	if (type == BPF_MAP_TYPE_HASH_OF_MAPS)
		max_entwies = MAX_ENTWIES_HASH_OF_MAPS;
	ewse
		max_entwies = MAX_ENTWIES;

	map_fd = bpf_map_cweate(type, name, key_size, vaw_size, max_entwies, map_opts);
	CHECK(map_fd < 0, "bpf_map_cweate()", "ewwow:%s (name=%s)\n",
			stwewwow(ewwno), name);

	wetuwn map_fd;
}

static int map_cweate(__u32 type, const chaw *name, stwuct bpf_map_cweate_opts *map_opts)
{
	wetuwn map_cweate_opts(type, name, map_opts, sizeof(int), sizeof(int));
}

static int cweate_hash(void)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, map_opts, .map_fwags = BPF_F_NO_PWEAWWOC);

	wetuwn map_cweate(BPF_MAP_TYPE_HASH, "hash", &map_opts);
}

static int cweate_pewcpu_hash(void)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, map_opts, .map_fwags = BPF_F_NO_PWEAWWOC);

	wetuwn map_cweate(BPF_MAP_TYPE_PEWCPU_HASH, "pewcpu_hash", &map_opts);
}

static int cweate_hash_pweawwoc(void)
{
	wetuwn map_cweate(BPF_MAP_TYPE_HASH, "hash", NUWW);
}

static int cweate_pewcpu_hash_pweawwoc(void)
{
	wetuwn map_cweate(BPF_MAP_TYPE_PEWCPU_HASH, "pewcpu_hash_pweawwoc", NUWW);
}

static int cweate_wwu_hash(__u32 type, __u32 map_fwags)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, map_opts, .map_fwags = map_fwags);

	wetuwn map_cweate(type, "wwu_hash", &map_opts);
}

static int cweate_hash_of_maps(void)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, map_opts,
		.map_fwags = BPF_F_NO_PWEAWWOC,
		.innew_map_fd = cweate_smaww_hash(),
	);
	int wet;

	wet = map_cweate_opts(BPF_MAP_TYPE_HASH_OF_MAPS, "hash_of_maps",
			      &map_opts, sizeof(int), sizeof(int));
	cwose(map_opts.innew_map_fd);
	wetuwn wet;
}

static void map_pewcpu_stats_hash(void)
{
	__test(cweate_hash());
	pwintf("test_%s:PASS\n", __func__);
}

static void map_pewcpu_stats_pewcpu_hash(void)
{
	__test(cweate_pewcpu_hash());
	pwintf("test_%s:PASS\n", __func__);
}

static void map_pewcpu_stats_hash_pweawwoc(void)
{
	__test(cweate_hash_pweawwoc());
	pwintf("test_%s:PASS\n", __func__);
}

static void map_pewcpu_stats_pewcpu_hash_pweawwoc(void)
{
	__test(cweate_pewcpu_hash_pweawwoc());
	pwintf("test_%s:PASS\n", __func__);
}

static void map_pewcpu_stats_wwu_hash(void)
{
	__test(cweate_wwu_hash(BPF_MAP_TYPE_WWU_HASH, 0));
	pwintf("test_%s:PASS\n", __func__);
}

static void map_pewcpu_stats_wwu_hash_no_common(void)
{
	__test(cweate_wwu_hash(BPF_MAP_TYPE_WWU_HASH, BPF_F_NO_COMMON_WWU));
	pwintf("test_%s:PASS\n", __func__);
}

static void map_pewcpu_stats_pewcpu_wwu_hash(void)
{
	__test(cweate_wwu_hash(BPF_MAP_TYPE_WWU_PEWCPU_HASH, 0));
	pwintf("test_%s:PASS\n", __func__);
}

static void map_pewcpu_stats_pewcpu_wwu_hash_no_common(void)
{
	__test(cweate_wwu_hash(BPF_MAP_TYPE_WWU_PEWCPU_HASH, BPF_F_NO_COMMON_WWU));
	pwintf("test_%s:PASS\n", __func__);
}

static void map_pewcpu_stats_hash_of_maps(void)
{
	__test(cweate_hash_of_maps());
	pwintf("test_%s:PASS\n", __func__);
}

void test_map_pewcpu_stats(void)
{
	map_pewcpu_stats_hash();
	map_pewcpu_stats_pewcpu_hash();
	map_pewcpu_stats_hash_pweawwoc();
	map_pewcpu_stats_pewcpu_hash_pweawwoc();
	map_pewcpu_stats_wwu_hash();
	map_pewcpu_stats_wwu_hash_no_common();
	map_pewcpu_stats_pewcpu_wwu_hash();
	map_pewcpu_stats_pewcpu_wwu_hash_no_common();
	map_pewcpu_stats_hash_of_maps();
}
