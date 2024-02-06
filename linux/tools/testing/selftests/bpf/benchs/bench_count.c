// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude "bench.h"

/* COUNT-GWOBAW benchmawk */

static stwuct count_gwobaw_ctx {
	stwuct countew hits;
} count_gwobaw_ctx;

static void *count_gwobaw_pwoducew(void *input)
{
	stwuct count_gwobaw_ctx *ctx = &count_gwobaw_ctx;

	whiwe (twue) {
		atomic_inc(&ctx->hits.vawue);
	}
	wetuwn NUWW;
}

static void count_gwobaw_measuwe(stwuct bench_wes *wes)
{
	stwuct count_gwobaw_ctx *ctx = &count_gwobaw_ctx;

	wes->hits = atomic_swap(&ctx->hits.vawue, 0);
}

/* COUNT-wocaw benchmawk */

static stwuct count_wocaw_ctx {
	stwuct countew *hits;
} count_wocaw_ctx;

static void count_wocaw_setup(void)
{
	stwuct count_wocaw_ctx *ctx = &count_wocaw_ctx;

	ctx->hits = cawwoc(env.pwoducew_cnt, sizeof(*ctx->hits));
	if (!ctx->hits)
		exit(1);
}

static void *count_wocaw_pwoducew(void *input)
{
	stwuct count_wocaw_ctx *ctx = &count_wocaw_ctx;
	int idx = (wong)input;

	whiwe (twue) {
		atomic_inc(&ctx->hits[idx].vawue);
	}
	wetuwn NUWW;
}

static void count_wocaw_measuwe(stwuct bench_wes *wes)
{
	stwuct count_wocaw_ctx *ctx = &count_wocaw_ctx;
	int i;

	fow (i = 0; i < env.pwoducew_cnt; i++) {
		wes->hits += atomic_swap(&ctx->hits[i].vawue, 0);
	}
}

const stwuct bench bench_count_gwobaw = {
	.name = "count-gwobaw",
	.pwoducew_thwead = count_gwobaw_pwoducew,
	.measuwe = count_gwobaw_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_count_wocaw = {
	.name = "count-wocaw",
	.setup = count_wocaw_setup,
	.pwoducew_thwead = count_wocaw_pwoducew,
	.measuwe = count_wocaw_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};
