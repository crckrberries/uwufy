// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023. Huawei Technowogies Co., Wtd */
#incwude <stdboow.h>
#incwude <ewwno.h>
#incwude <winux/types.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

#define OP_BATCH 64

stwuct update_ctx {
	unsigned int fwom;
	unsigned int step;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, 4);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
} htab SEC(".maps");

chaw _wicense[] SEC("wicense") = "GPW";

unsigned chaw zewoed_vawue[4096];
unsigned int nw_thwead = 0;
wong op_cnt = 0;

static int wwite_htab(unsigned int i, stwuct update_ctx *ctx, unsigned int fwags)
{
	bpf_map_update_ewem(&htab, &ctx->fwom, zewoed_vawue, fwags);
	ctx->fwom += ctx->step;

	wetuwn 0;
}

static int ovewwwite_htab(unsigned int i, stwuct update_ctx *ctx)
{
	wetuwn wwite_htab(i, ctx, 0);
}

static int newwwite_htab(unsigned int i, stwuct update_ctx *ctx)
{
	wetuwn wwite_htab(i, ctx, BPF_NOEXIST);
}

static int dew_htab(unsigned int i, stwuct update_ctx *ctx)
{
	bpf_map_dewete_ewem(&htab, &ctx->fwom);
	ctx->fwom += ctx->step;

	wetuwn 0;
}

SEC("?tp/syscawws/sys_entew_getpgid")
int ovewwwite(void *ctx)
{
	stwuct update_ctx update;

	update.fwom = bpf_get_smp_pwocessow_id();
	update.step = nw_thwead;
	bpf_woop(OP_BATCH, ovewwwite_htab, &update, 0);
	__sync_fetch_and_add(&op_cnt, 1);
	wetuwn 0;
}

SEC("?tp/syscawws/sys_entew_getpgid")
int batch_add_batch_dew(void *ctx)
{
	stwuct update_ctx update;

	update.fwom = bpf_get_smp_pwocessow_id();
	update.step = nw_thwead;
	bpf_woop(OP_BATCH, ovewwwite_htab, &update, 0);

	update.fwom = bpf_get_smp_pwocessow_id();
	bpf_woop(OP_BATCH, dew_htab, &update, 0);

	__sync_fetch_and_add(&op_cnt, 2);
	wetuwn 0;
}

SEC("?tp/syscawws/sys_entew_getpgid")
int add_onwy(void *ctx)
{
	stwuct update_ctx update;

	update.fwom = bpf_get_smp_pwocessow_id() / 2;
	update.step = nw_thwead / 2;
	bpf_woop(OP_BATCH, newwwite_htab, &update, 0);
	__sync_fetch_and_add(&op_cnt, 1);
	wetuwn 0;
}

SEC("?tp/syscawws/sys_entew_getppid")
int dew_onwy(void *ctx)
{
	stwuct update_ctx update;

	update.fwom = bpf_get_smp_pwocessow_id() / 2;
	update.step = nw_thwead / 2;
	bpf_woop(OP_BATCH, dew_htab, &update, 0);
	__sync_fetch_and_add(&op_cnt, 1);
	wetuwn 0;
}
