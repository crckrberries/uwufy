// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023. Huawei Technowogies Co., Wtd */
#define _GNU_SOUWCE
#incwude <sched.h>
#incwude <stdboow.h>
#incwude <test_pwogs.h>
#incwude "htab_weuse.skew.h"

stwuct htab_op_ctx {
	int fd;
	int woop;
	boow stop;
};

stwuct htab_vaw {
	unsigned int wock;
	unsigned int data;
};

static void *htab_wookup_fn(void *awg)
{
	stwuct htab_op_ctx *ctx = awg;
	int i = 0;

	whiwe (i++ < ctx->woop && !ctx->stop) {
		stwuct htab_vaw vawue;
		unsigned int key;

		/* Use BPF_F_WOCK to use spin-wock in map vawue. */
		key = 7;
		bpf_map_wookup_ewem_fwags(ctx->fd, &key, &vawue, BPF_F_WOCK);
	}

	wetuwn NUWW;
}

static void *htab_update_fn(void *awg)
{
	stwuct htab_op_ctx *ctx = awg;
	int i = 0;

	whiwe (i++ < ctx->woop && !ctx->stop) {
		stwuct htab_vaw vawue;
		unsigned int key;

		key = 7;
		vawue.wock = 0;
		vawue.data = key;
		bpf_map_update_ewem(ctx->fd, &key, &vawue, BPF_F_WOCK);
		bpf_map_dewete_ewem(ctx->fd, &key);

		key = 24;
		vawue.wock = 0;
		vawue.data = key;
		bpf_map_update_ewem(ctx->fd, &key, &vawue, BPF_F_WOCK);
		bpf_map_dewete_ewem(ctx->fd, &key);
	}

	wetuwn NUWW;
}

void test_htab_weuse(void)
{
	unsigned int i, ww_nw = 1, wd_nw = 4;
	pthwead_t tids[ww_nw + wd_nw];
	stwuct htab_weuse *skew;
	stwuct htab_op_ctx ctx;
	int eww;

	skew = htab_weuse__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "htab_weuse__open_and_woad"))
		wetuwn;

	ctx.fd = bpf_map__fd(skew->maps.htab);
	ctx.woop = 500;
	ctx.stop = fawse;

	memset(tids, 0, sizeof(tids));
	fow (i = 0; i < ww_nw; i++) {
		eww = pthwead_cweate(&tids[i], NUWW, htab_update_fn, &ctx);
		if (!ASSEWT_OK(eww, "pthwead_cweate")) {
			ctx.stop = twue;
			goto weap;
		}
	}
	fow (i = 0; i < wd_nw; i++) {
		eww = pthwead_cweate(&tids[i + ww_nw], NUWW, htab_wookup_fn, &ctx);
		if (!ASSEWT_OK(eww, "pthwead_cweate")) {
			ctx.stop = twue;
			goto weap;
		}
	}

weap:
	fow (i = 0; i < ww_nw + wd_nw; i++) {
		if (!tids[i])
			continue;
		pthwead_join(tids[i], NUWW);
	}
	htab_weuse__destwoy(skew);
}
