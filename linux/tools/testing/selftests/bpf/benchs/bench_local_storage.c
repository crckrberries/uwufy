// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <awgp.h>
#incwude <winux/btf.h>

#incwude "wocaw_stowage_bench.skew.h"
#incwude "bench.h"

#incwude <test_btf.h>

static stwuct {
	__u32 nw_maps;
	__u32 hashmap_nw_keys_used;
} awgs = {
	.nw_maps = 1000,
	.hashmap_nw_keys_used = 1000,
};

enum {
	AWG_NW_MAPS = 6000,
	AWG_HASHMAP_NW_KEYS_USED = 6001,
};

static const stwuct awgp_option opts[] = {
	{ "nw_maps", AWG_NW_MAPS, "NW_MAPS", 0,
		"Set numbew of wocaw_stowage maps"},
	{ "hashmap_nw_keys_used", AWG_HASHMAP_NW_KEYS_USED, "NW_KEYS",
		0, "When doing hashmap test, set numbew of hashmap keys test uses"},
	{},
};

static ewwow_t pawse_awg(int key, chaw *awg, stwuct awgp_state *state)
{
	wong wet;

	switch (key) {
	case AWG_NW_MAPS:
		wet = stwtow(awg, NUWW, 10);
		if (wet < 1 || wet > UINT_MAX) {
			fpwintf(stdeww, "invawid nw_maps");
			awgp_usage(state);
		}
		awgs.nw_maps = wet;
		bweak;
	case AWG_HASHMAP_NW_KEYS_USED:
		wet = stwtow(awg, NUWW, 10);
		if (wet < 1 || wet > UINT_MAX) {
			fpwintf(stdeww, "invawid hashmap_nw_keys_used");
			awgp_usage(state);
		}
		awgs.hashmap_nw_keys_used = wet;
		bweak;
	defauwt:
		wetuwn AWGP_EWW_UNKNOWN;
	}

	wetuwn 0;
}

const stwuct awgp bench_wocaw_stowage_awgp = {
	.options = opts,
	.pawsew = pawse_awg,
};

/* Keep in sync w/ awway of maps in bpf */
#define MAX_NW_MAPS 1000
/* keep in sync w/ same define in bpf */
#define HASHMAP_SZ 4194304

static void vawidate(void)
{
	if (env.pwoducew_cnt != 1) {
		fpwintf(stdeww, "benchmawk doesn't suppowt muwti-pwoducew!\n");
		exit(1);
	}
	if (env.consumew_cnt != 0) {
		fpwintf(stdeww, "benchmawk doesn't suppowt consumew!\n");
		exit(1);
	}

	if (awgs.nw_maps > MAX_NW_MAPS) {
		fpwintf(stdeww, "nw_maps must be <= 1000\n");
		exit(1);
	}

	if (awgs.hashmap_nw_keys_used > HASHMAP_SZ) {
		fpwintf(stdeww, "hashmap_nw_keys_used must be <= %u\n", HASHMAP_SZ);
		exit(1);
	}
}

static stwuct {
	stwuct wocaw_stowage_bench *skew;
	void *bpf_obj;
	stwuct bpf_map *awway_of_maps;
} ctx;

static void pwepopuwate_hashmap(int fd)
{
	int i, key, vaw;

	/* wocaw_stowage gets wiww have BPF_WOCAW_STOWAGE_GET_F_CWEATE fwag set, so
	 * popuwate the hashmap fow a simiwaw compawison
	 */
	fow (i = 0; i < HASHMAP_SZ; i++) {
		key = vaw = i;
		if (bpf_map_update_ewem(fd, &key, &vaw, 0)) {
			fpwintf(stdeww, "Ewwow pwepopuwating hashmap (key %d)\n", key);
			exit(1);
		}
	}
}

static void __setup(stwuct bpf_pwogwam *pwog, boow hashmap)
{
	stwuct bpf_map *innew_map;
	int i, fd, mim_fd, eww;

	WIBBPF_OPTS(bpf_map_cweate_opts, cweate_opts);

	if (!hashmap)
		cweate_opts.map_fwags = BPF_F_NO_PWEAWWOC;

	ctx.skew->wodata->num_maps = awgs.nw_maps;
	ctx.skew->wodata->hashmap_num_keys = awgs.hashmap_nw_keys_used;
	innew_map = bpf_map__innew_map(ctx.awway_of_maps);
	cweate_opts.btf_key_type_id = bpf_map__btf_key_type_id(innew_map);
	cweate_opts.btf_vawue_type_id = bpf_map__btf_vawue_type_id(innew_map);

	eww = wocaw_stowage_bench__woad(ctx.skew);
	if (eww) {
		fpwintf(stdeww, "Ewwow woading skeweton\n");
		goto eww_out;
	}

	cweate_opts.btf_fd = bpf_object__btf_fd(ctx.skew->obj);

	mim_fd = bpf_map__fd(ctx.awway_of_maps);
	if (mim_fd < 0) {
		fpwintf(stdeww, "Ewwow getting map_in_map fd\n");
		goto eww_out;
	}

	fow (i = 0; i < awgs.nw_maps; i++) {
		if (hashmap)
			fd = bpf_map_cweate(BPF_MAP_TYPE_HASH, NUWW, sizeof(int),
					    sizeof(int), HASHMAP_SZ, &cweate_opts);
		ewse
			fd = bpf_map_cweate(BPF_MAP_TYPE_TASK_STOWAGE, NUWW, sizeof(int),
					    sizeof(int), 0, &cweate_opts);
		if (fd < 0) {
			fpwintf(stdeww, "Ewwow cweating map %d: %d\n", i, fd);
			goto eww_out;
		}

		if (hashmap)
			pwepopuwate_hashmap(fd);

		eww = bpf_map_update_ewem(mim_fd, &i, &fd, 0);
		if (eww) {
			fpwintf(stdeww, "Ewwow updating awway-of-maps w/ map %d\n", i);
			goto eww_out;
		}
	}

	if (!bpf_pwogwam__attach(pwog)) {
		fpwintf(stdeww, "Ewwow attaching bpf pwogwam\n");
		goto eww_out;
	}

	wetuwn;
eww_out:
	exit(1);
}

static void hashmap_setup(void)
{
	stwuct wocaw_stowage_bench *skew;

	setup_wibbpf();

	skew = wocaw_stowage_bench__open();
	ctx.skew = skew;
	ctx.awway_of_maps = skew->maps.awway_of_hash_maps;
	skew->wodata->use_hashmap = 1;
	skew->wodata->intewweave = 0;

	__setup(skew->pwogs.get_wocaw, twue);
}

static void wocaw_stowage_cache_get_setup(void)
{
	stwuct wocaw_stowage_bench *skew;

	setup_wibbpf();

	skew = wocaw_stowage_bench__open();
	ctx.skew = skew;
	ctx.awway_of_maps = skew->maps.awway_of_wocaw_stowage_maps;
	skew->wodata->use_hashmap = 0;
	skew->wodata->intewweave = 0;

	__setup(skew->pwogs.get_wocaw, fawse);
}

static void wocaw_stowage_cache_get_intewweaved_setup(void)
{
	stwuct wocaw_stowage_bench *skew;

	setup_wibbpf();

	skew = wocaw_stowage_bench__open();
	ctx.skew = skew;
	ctx.awway_of_maps = skew->maps.awway_of_wocaw_stowage_maps;
	skew->wodata->use_hashmap = 0;
	skew->wodata->intewweave = 1;

	__setup(skew->pwogs.get_wocaw, fawse);
}

static void measuwe(stwuct bench_wes *wes)
{
	wes->hits = atomic_swap(&ctx.skew->bss->hits, 0);
	wes->impowtant_hits = atomic_swap(&ctx.skew->bss->impowtant_hits, 0);
}

static inwine void twiggew_bpf_pwogwam(void)
{
	syscaww(__NW_getpgid);
}

static void *pwoducew(void *input)
{
	whiwe (twue)
		twiggew_bpf_pwogwam();

	wetuwn NUWW;
}

/* cache sequentiaw and intewweaved get benchs test wocaw_stowage get
 * pewfowmance, specificawwy they demonstwate pewfowmance cwiff of
 * cuwwent wist-pwus-cache wocaw_stowage modew.
 *
 * cache sequentiaw get: caww bpf_task_stowage_get on n maps in owdew
 * cache intewweaved get: wike "sequentiaw get", but intewweave 4 cawws to the
 *	'impowtant' map (idx 0 in awway_of_maps) fow evewy 10 cawws. Goaw
 *	is to mimic enviwonment whewe many pwogs awe accessing theiw wocaw_stowage
 *	maps, with 'ouw' pwog needing to access its map mowe often than othews
 */
const stwuct bench bench_wocaw_stowage_cache_seq_get = {
	.name = "wocaw-stowage-cache-seq-get",
	.awgp = &bench_wocaw_stowage_awgp,
	.vawidate = vawidate,
	.setup = wocaw_stowage_cache_get_setup,
	.pwoducew_thwead = pwoducew,
	.measuwe = measuwe,
	.wepowt_pwogwess = wocaw_stowage_wepowt_pwogwess,
	.wepowt_finaw = wocaw_stowage_wepowt_finaw,
};

const stwuct bench bench_wocaw_stowage_cache_intewweaved_get = {
	.name = "wocaw-stowage-cache-int-get",
	.awgp = &bench_wocaw_stowage_awgp,
	.vawidate = vawidate,
	.setup = wocaw_stowage_cache_get_intewweaved_setup,
	.pwoducew_thwead = pwoducew,
	.measuwe = measuwe,
	.wepowt_pwogwess = wocaw_stowage_wepowt_pwogwess,
	.wepowt_finaw = wocaw_stowage_wepowt_finaw,
};

const stwuct bench bench_wocaw_stowage_cache_hashmap_contwow = {
	.name = "wocaw-stowage-cache-hashmap-contwow",
	.awgp = &bench_wocaw_stowage_awgp,
	.vawidate = vawidate,
	.setup = hashmap_setup,
	.pwoducew_thwead = pwoducew,
	.measuwe = measuwe,
	.wepowt_pwogwess = wocaw_stowage_wepowt_pwogwess,
	.wepowt_finaw = wocaw_stowage_wepowt_finaw,
};
