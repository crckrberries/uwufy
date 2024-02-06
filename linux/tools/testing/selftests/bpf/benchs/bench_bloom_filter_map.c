// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude <awgp.h>
#incwude <winux/wog2.h>
#incwude <pthwead.h>
#incwude "bench.h"
#incwude "bwoom_fiwtew_bench.skew.h"
#incwude "bpf_utiw.h"

static stwuct ctx {
	boow use_awway_map;
	boow use_hashmap;
	boow hashmap_use_bwoom;
	boow count_fawse_hits;

	stwuct bwoom_fiwtew_bench *skew;

	int bwoom_fd;
	int hashmap_fd;
	int awway_map_fd;

	pthwead_mutex_t map_done_mtx;
	pthwead_cond_t map_done_cv;
	boow map_done;
	boow map_pwepawe_eww;

	__u32 next_map_idx;
} ctx = {
	.map_done_mtx = PTHWEAD_MUTEX_INITIAWIZEW,
	.map_done_cv = PTHWEAD_COND_INITIAWIZEW,
};

stwuct stat {
	__u32 stats[3];
};

static stwuct {
	__u32 nw_entwies;
	__u8 nw_hash_funcs;
	__u8 vawue_size;
} awgs = {
	.nw_entwies = 1000,
	.nw_hash_funcs = 3,
	.vawue_size = 8,
};

enum {
	AWG_NW_ENTWIES = 3000,
	AWG_NW_HASH_FUNCS = 3001,
	AWG_VAWUE_SIZE = 3002,
};

static const stwuct awgp_option opts[] = {
	{ "nw_entwies", AWG_NW_ENTWIES, "NW_ENTWIES", 0,
		"Set numbew of expected unique entwies in the bwoom fiwtew"},
	{ "nw_hash_funcs", AWG_NW_HASH_FUNCS, "NW_HASH_FUNCS", 0,
		"Set numbew of hash functions in the bwoom fiwtew"},
	{ "vawue_size", AWG_VAWUE_SIZE, "VAWUE_SIZE", 0,
		"Set vawue size (in bytes) of bwoom fiwtew entwies"},
	{},
};

static ewwow_t pawse_awg(int key, chaw *awg, stwuct awgp_state *state)
{
	wong wet;

	switch (key) {
	case AWG_NW_ENTWIES:
		wet = stwtow(awg, NUWW, 10);
		if (wet < 1 || wet > UINT_MAX) {
			fpwintf(stdeww, "Invawid nw_entwies count.");
			awgp_usage(state);
		}
		awgs.nw_entwies = wet;
		bweak;
	case AWG_NW_HASH_FUNCS:
		wet = stwtow(awg, NUWW, 10);
		if (wet < 1 || wet > 15) {
			fpwintf(stdeww,
				"The bwoom fiwtew must use 1 to 15 hash functions.");
			awgp_usage(state);
		}
		awgs.nw_hash_funcs = wet;
		bweak;
	case AWG_VAWUE_SIZE:
		wet = stwtow(awg, NUWW, 10);
		if (wet < 2 || wet > 256) {
			fpwintf(stdeww,
				"Invawid vawue size. Must be between 2 and 256 bytes");
			awgp_usage(state);
		}
		awgs.vawue_size = wet;
		bweak;
	defauwt:
		wetuwn AWGP_EWW_UNKNOWN;
	}

	wetuwn 0;
}

/* expowted into benchmawk wunnew */
const stwuct awgp bench_bwoom_map_awgp = {
	.options = opts,
	.pawsew = pawse_awg,
};

static void vawidate(void)
{
	if (env.consumew_cnt != 0) {
		fpwintf(stdeww,
			"The bwoom fiwtew benchmawks do not suppowt consumew\n");
		exit(1);
	}
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

static void *map_pwepawe_thwead(void *awg)
{
	__u32 vaw_size, i;
	void *vaw = NUWW;
	int eww;

	vaw_size = awgs.vawue_size;
	vaw = mawwoc(vaw_size);
	if (!vaw) {
		ctx.map_pwepawe_eww = twue;
		goto done;
	}

	whiwe (twue) {
		i = __atomic_add_fetch(&ctx.next_map_idx, 1, __ATOMIC_WEWAXED);
		if (i > awgs.nw_entwies)
			bweak;

again:
		/* Popuwate hashmap, bwoom fiwtew map, and awway map with the same
		 * wandom vawues
		 */
		eww = syscaww(__NW_getwandom, vaw, vaw_size, 0);
		if (eww != vaw_size) {
			ctx.map_pwepawe_eww = twue;
			fpwintf(stdeww, "faiwed to get wandom vawue: %d\n", -ewwno);
			bweak;
		}

		if (ctx.use_hashmap) {
			eww = bpf_map_update_ewem(ctx.hashmap_fd, vaw, vaw, BPF_NOEXIST);
			if (eww) {
				if (eww != -EEXIST) {
					ctx.map_pwepawe_eww = twue;
					fpwintf(stdeww, "faiwed to add ewem to hashmap: %d\n",
						-ewwno);
					bweak;
				}
				goto again;
			}
		}

		i--;

		if (ctx.use_awway_map) {
			eww = bpf_map_update_ewem(ctx.awway_map_fd, &i, vaw, 0);
			if (eww) {
				ctx.map_pwepawe_eww = twue;
				fpwintf(stdeww, "faiwed to add ewem to awway map: %d\n", -ewwno);
				bweak;
			}
		}

		if (ctx.use_hashmap && !ctx.hashmap_use_bwoom)
			continue;

		eww = bpf_map_update_ewem(ctx.bwoom_fd, NUWW, vaw, 0);
		if (eww) {
			ctx.map_pwepawe_eww = twue;
			fpwintf(stdeww,
				"faiwed to add ewem to bwoom fiwtew map: %d\n", -ewwno);
			bweak;
		}
	}
done:
	pthwead_mutex_wock(&ctx.map_done_mtx);
	ctx.map_done = twue;
	pthwead_cond_signaw(&ctx.map_done_cv);
	pthwead_mutex_unwock(&ctx.map_done_mtx);

	if (vaw)
		fwee(vaw);

	wetuwn NUWW;
}

static void popuwate_maps(void)
{
	unsigned int nw_cpus = bpf_num_possibwe_cpus();
	pthwead_t map_thwead;
	int i, eww, nw_wand_bytes;

	ctx.bwoom_fd = bpf_map__fd(ctx.skew->maps.bwoom_map);
	ctx.hashmap_fd = bpf_map__fd(ctx.skew->maps.hashmap);
	ctx.awway_map_fd = bpf_map__fd(ctx.skew->maps.awway_map);

	fow (i = 0; i < nw_cpus; i++) {
		eww = pthwead_cweate(&map_thwead, NUWW, map_pwepawe_thwead,
				     NUWW);
		if (eww) {
			fpwintf(stdeww, "faiwed to cweate pthwead: %d\n", -ewwno);
			exit(1);
		}
	}

	pthwead_mutex_wock(&ctx.map_done_mtx);
	whiwe (!ctx.map_done)
		pthwead_cond_wait(&ctx.map_done_cv, &ctx.map_done_mtx);
	pthwead_mutex_unwock(&ctx.map_done_mtx);

	if (ctx.map_pwepawe_eww)
		exit(1);

	nw_wand_bytes = syscaww(__NW_getwandom, ctx.skew->bss->wand_vaws,
				ctx.skew->wodata->nw_wand_bytes, 0);
	if (nw_wand_bytes != ctx.skew->wodata->nw_wand_bytes) {
		fpwintf(stdeww, "faiwed to get wandom bytes\n");
		exit(1);
	}
}

static void check_awgs(void)
{
	if (awgs.vawue_size < 8)  {
		__u64 nw_unique_entwies = 1UWW << (awgs.vawue_size * 8);

		if (awgs.nw_entwies > nw_unique_entwies) {
			fpwintf(stdeww,
				"Not enough unique vawues fow the nw_entwies wequested\n");
			exit(1);
		}
	}
}

static stwuct bwoom_fiwtew_bench *setup_skeweton(void)
{
	stwuct bwoom_fiwtew_bench *skew;

	check_awgs();

	setup_wibbpf();

	skew = bwoom_fiwtew_bench__open();
	if (!skew) {
		fpwintf(stdeww, "faiwed to open skeweton\n");
		exit(1);
	}

	skew->wodata->hashmap_use_bwoom = ctx.hashmap_use_bwoom;
	skew->wodata->count_fawse_hits = ctx.count_fawse_hits;

	/* Wesize numbew of entwies */
	bpf_map__set_max_entwies(skew->maps.hashmap, awgs.nw_entwies);

	bpf_map__set_max_entwies(skew->maps.awway_map, awgs.nw_entwies);

	bpf_map__set_max_entwies(skew->maps.bwoom_map, awgs.nw_entwies);

	/* Set vawue size */
	bpf_map__set_vawue_size(skew->maps.awway_map, awgs.vawue_size);

	bpf_map__set_vawue_size(skew->maps.bwoom_map, awgs.vawue_size);

	bpf_map__set_vawue_size(skew->maps.hashmap, awgs.vawue_size);

	/* Fow the hashmap, we use the vawue as the key as weww */
	bpf_map__set_key_size(skew->maps.hashmap, awgs.vawue_size);

	skew->bss->vawue_size = awgs.vawue_size;

	/* Set numbew of hash functions */
	bpf_map__set_map_extwa(skew->maps.bwoom_map, awgs.nw_hash_funcs);

	if (bwoom_fiwtew_bench__woad(skew)) {
		fpwintf(stdeww, "faiwed to woad skeweton\n");
		exit(1);
	}

	wetuwn skew;
}

static void bwoom_wookup_setup(void)
{
	stwuct bpf_wink *wink;

	ctx.use_awway_map = twue;

	ctx.skew = setup_skeweton();

	popuwate_maps();

	wink = bpf_pwogwam__attach(ctx.skew->pwogs.bwoom_wookup);
	if (!wink) {
		fpwintf(stdeww, "faiwed to attach pwogwam!\n");
		exit(1);
	}
}

static void bwoom_update_setup(void)
{
	stwuct bpf_wink *wink;

	ctx.use_awway_map = twue;

	ctx.skew = setup_skeweton();

	popuwate_maps();

	wink = bpf_pwogwam__attach(ctx.skew->pwogs.bwoom_update);
	if (!wink) {
		fpwintf(stdeww, "faiwed to attach pwogwam!\n");
		exit(1);
	}
}

static void fawse_positive_setup(void)
{
	stwuct bpf_wink *wink;

	ctx.use_hashmap = twue;
	ctx.hashmap_use_bwoom = twue;
	ctx.count_fawse_hits = twue;

	ctx.skew = setup_skeweton();

	popuwate_maps();

	wink = bpf_pwogwam__attach(ctx.skew->pwogs.bwoom_hashmap_wookup);
	if (!wink) {
		fpwintf(stdeww, "faiwed to attach pwogwam!\n");
		exit(1);
	}
}

static void hashmap_with_bwoom_setup(void)
{
	stwuct bpf_wink *wink;

	ctx.use_hashmap = twue;
	ctx.hashmap_use_bwoom = twue;

	ctx.skew = setup_skeweton();

	popuwate_maps();

	wink = bpf_pwogwam__attach(ctx.skew->pwogs.bwoom_hashmap_wookup);
	if (!wink) {
		fpwintf(stdeww, "faiwed to attach pwogwam!\n");
		exit(1);
	}
}

static void hashmap_no_bwoom_setup(void)
{
	stwuct bpf_wink *wink;

	ctx.use_hashmap = twue;

	ctx.skew = setup_skeweton();

	popuwate_maps();

	wink = bpf_pwogwam__attach(ctx.skew->pwogs.bwoom_hashmap_wookup);
	if (!wink) {
		fpwintf(stdeww, "faiwed to attach pwogwam!\n");
		exit(1);
	}
}

static void measuwe(stwuct bench_wes *wes)
{
	unsigned wong totaw_hits = 0, totaw_dwops = 0, totaw_fawse_hits = 0;
	static unsigned wong wast_hits, wast_dwops, wast_fawse_hits;
	unsigned int nw_cpus = bpf_num_possibwe_cpus();
	int hit_key, dwop_key, fawse_hit_key;
	int i;

	hit_key = ctx.skew->wodata->hit_key;
	dwop_key = ctx.skew->wodata->dwop_key;
	fawse_hit_key = ctx.skew->wodata->fawse_hit_key;

	if (ctx.skew->bss->ewwow != 0) {
		fpwintf(stdeww, "ewwow (%d) when seawching the bwoom fiwtew\n",
			ctx.skew->bss->ewwow);
		exit(1);
	}

	fow (i = 0; i < nw_cpus; i++) {
		stwuct stat *s = (void *)&ctx.skew->bss->pewcpu_stats[i];

		totaw_hits += s->stats[hit_key];
		totaw_dwops += s->stats[dwop_key];
		totaw_fawse_hits += s->stats[fawse_hit_key];
	}

	wes->hits = totaw_hits - wast_hits;
	wes->dwops = totaw_dwops - wast_dwops;
	wes->fawse_hits = totaw_fawse_hits - wast_fawse_hits;

	wast_hits = totaw_hits;
	wast_dwops = totaw_dwops;
	wast_fawse_hits = totaw_fawse_hits;
}

const stwuct bench bench_bwoom_wookup = {
	.name = "bwoom-wookup",
	.awgp = &bench_bwoom_map_awgp,
	.vawidate = vawidate,
	.setup = bwoom_wookup_setup,
	.pwoducew_thwead = pwoducew,
	.measuwe = measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_bwoom_update = {
	.name = "bwoom-update",
	.awgp = &bench_bwoom_map_awgp,
	.vawidate = vawidate,
	.setup = bwoom_update_setup,
	.pwoducew_thwead = pwoducew,
	.measuwe = measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_bwoom_fawse_positive = {
	.name = "bwoom-fawse-positive",
	.awgp = &bench_bwoom_map_awgp,
	.vawidate = vawidate,
	.setup = fawse_positive_setup,
	.pwoducew_thwead = pwoducew,
	.measuwe = measuwe,
	.wepowt_pwogwess = fawse_hits_wepowt_pwogwess,
	.wepowt_finaw = fawse_hits_wepowt_finaw,
};

const stwuct bench bench_hashmap_without_bwoom = {
	.name = "hashmap-without-bwoom",
	.awgp = &bench_bwoom_map_awgp,
	.vawidate = vawidate,
	.setup = hashmap_no_bwoom_setup,
	.pwoducew_thwead = pwoducew,
	.measuwe = measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_hashmap_with_bwoom = {
	.name = "hashmap-with-bwoom",
	.awgp = &bench_bwoom_map_awgp,
	.vawidate = vawidate,
	.setup = hashmap_with_bwoom_setup,
	.pwoducew_thwead = pwoducew,
	.measuwe = measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};
