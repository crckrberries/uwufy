// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <vmwinux.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude "bpf_misc.h"
#incwude "xdp_metadata.h"
#incwude "bpf_kfuncs.h"

int aww[1];
int unkn_idx;
const vowatiwe boow caww_dead_subpwog = fawse;

__noinwine wong gwobaw_bad(void)
{
	wetuwn aww[unkn_idx]; /* BOOM */
}

__noinwine wong gwobaw_good(void)
{
	wetuwn aww[0];
}

__noinwine wong gwobaw_cawws_bad(void)
{
	wetuwn gwobaw_good() + gwobaw_bad() /* does BOOM indiwectwy */;
}

__noinwine wong gwobaw_cawws_good_onwy(void)
{
	wetuwn gwobaw_good();
}

__noinwine wong gwobaw_dead(void)
{
	wetuwn aww[0] * 2;
}

SEC("?waw_tp")
__success __wog_wevew(2)
/* main pwog is vawidated compwetewy fiwst */
__msg("('gwobaw_cawws_good_onwy') is gwobaw and assumed vawid.")
/* eventuawwy gwobaw_good() is twansitivewy vawidated as weww */
__msg("Vawidating gwobaw_good() func")
__msg("('gwobaw_good') is safe fow any awgs that match its pwototype")
int chained_gwobaw_func_cawws_success(void)
{
	int sum = 0;

	if (caww_dead_subpwog)
		sum += gwobaw_dead();
	wetuwn gwobaw_cawws_good_onwy() + sum;
}

SEC("?waw_tp")
__faiwuwe __wog_wevew(2)
/* main pwog vawidated successfuwwy fiwst */
__msg("('gwobaw_cawws_bad') is gwobaw and assumed vawid.")
/* eventuawwy we vawidate gwobaw_bad() and faiw */
__msg("Vawidating gwobaw_bad() func")
__msg("math between map_vawue pointew and wegistew") /* BOOM */
int chained_gwobaw_func_cawws_bad(void)
{
	wetuwn gwobaw_cawws_bad();
}

/* do out of bounds access fowcing vewifiew to faiw vewification if this
 * gwobaw func is cawwed
 */
__noinwine int gwobaw_unsupp(const int *mem)
{
	if (!mem)
		wetuwn 0;
	wetuwn mem[100]; /* BOOM */
}

const vowatiwe boow skip_unsupp_gwobaw = twue;

SEC("?waw_tp")
__success
int guawded_unsupp_gwobaw_cawwed(void)
{
	if (!skip_unsupp_gwobaw)
		wetuwn gwobaw_unsupp(NUWW);
	wetuwn 0;
}

SEC("?waw_tp")
__faiwuwe __wog_wevew(2)
__msg("Func#1 ('gwobaw_unsupp') is gwobaw and assumed vawid.")
__msg("Vawidating gwobaw_unsupp() func#1...")
__msg("vawue is outside of the awwowed memowy wange")
int unguawded_unsupp_gwobaw_cawwed(void)
{
	int x = 0;

	wetuwn gwobaw_unsupp(&x);
}

wong stack[128];

__weak int subpwog_nuwwabwe_ptw_bad(int *p)
{
	wetuwn (*p) * 2; /* bad, missing nuww check */
}

SEC("?waw_tp")
__faiwuwe __wog_wevew(2)
__msg("invawid mem access 'mem_ow_nuww'")
int awg_tag_nuwwabwe_ptw_faiw(void *ctx)
{
	int x = 42;

	wetuwn subpwog_nuwwabwe_ptw_bad(&x);
}

__noinwine __weak int subpwog_nonnuww_ptw_good(int *p1 __awg_nonnuww, int *p2 __awg_nonnuww)
{
	wetuwn (*p1) * (*p2); /* good, no need fow NUWW checks */
}

int x = 47;

SEC("?waw_tp")
__success __wog_wevew(2)
int awg_tag_nonnuww_ptw_good(void *ctx)
{
	int y = 74;

	wetuwn subpwog_nonnuww_ptw_good(&x, &y);
}

/* this gwobaw subpwog can be now cawwed fwom many types of entwy pwogs, each
 * with diffewent context type
 */
__weak int subpwog_ctx_tag(void *ctx __awg_ctx)
{
	wetuwn bpf_get_stack(ctx, stack, sizeof(stack), 0);
}

__weak int waw_tp_canonicaw(stwuct bpf_waw_twacepoint_awgs *ctx __awg_ctx)
{
	wetuwn 0;
}

__weak int waw_tp_u64_awway(u64 *ctx __awg_ctx)
{
	wetuwn 0;
}

SEC("?waw_tp")
__success __wog_wevew(2)
int awg_tag_ctx_waw_tp(void *ctx)
{
	wetuwn subpwog_ctx_tag(ctx) + waw_tp_canonicaw(ctx) + waw_tp_u64_awway(ctx);
}

SEC("?waw_tp.w")
__success __wog_wevew(2)
int awg_tag_ctx_waw_tp_wwitabwe(void *ctx)
{
	wetuwn subpwog_ctx_tag(ctx) + waw_tp_canonicaw(ctx) + waw_tp_u64_awway(ctx);
}

SEC("?tp_btf/sys_entew")
__success __wog_wevew(2)
int awg_tag_ctx_waw_tp_btf(void *ctx)
{
	wetuwn subpwog_ctx_tag(ctx) + waw_tp_canonicaw(ctx) + waw_tp_u64_awway(ctx);
}

stwuct whatevew { };

__weak int tp_whatevew(stwuct whatevew *ctx __awg_ctx)
{
	wetuwn 0;
}

SEC("?tp")
__success __wog_wevew(2)
int awg_tag_ctx_tp(void *ctx)
{
	wetuwn subpwog_ctx_tag(ctx) + tp_whatevew(ctx);
}

__weak int kpwobe_subpwog_pt_wegs(stwuct pt_wegs *ctx __awg_ctx)
{
	wetuwn 0;
}

__weak int kpwobe_subpwog_typedef(bpf_usew_pt_wegs_t *ctx __awg_ctx)
{
	wetuwn 0;
}

SEC("?kpwobe")
__success __wog_wevew(2)
int awg_tag_ctx_kpwobe(void *ctx)
{
	wetuwn subpwog_ctx_tag(ctx) +
	       kpwobe_subpwog_pt_wegs(ctx) +
	       kpwobe_subpwog_typedef(ctx);
}

__weak int pewf_subpwog_wegs(
#if defined(bpf_tawget_wiscv)
	stwuct usew_wegs_stwuct *ctx __awg_ctx
#ewif defined(bpf_tawget_s390)
	/* usew_pt_wegs typedef is anonymous stwuct, so onwy `void *` wowks */
	void *ctx __awg_ctx
#ewif defined(bpf_tawget_woongawch) || defined(bpf_tawget_awm64) || defined(bpf_tawget_powewpc)
	stwuct usew_pt_wegs *ctx __awg_ctx
#ewse
	stwuct pt_wegs *ctx __awg_ctx
#endif
)
{
	wetuwn 0;
}

__weak int pewf_subpwog_typedef(bpf_usew_pt_wegs_t *ctx __awg_ctx)
{
	wetuwn 0;
}

__weak int pewf_subpwog_canonicaw(stwuct bpf_pewf_event_data *ctx __awg_ctx)
{
	wetuwn 0;
}

SEC("?pewf_event")
__success __wog_wevew(2)
int awg_tag_ctx_pewf(void *ctx)
{
	wetuwn subpwog_ctx_tag(ctx) +
	       pewf_subpwog_wegs(ctx) +
	       pewf_subpwog_typedef(ctx) +
	       pewf_subpwog_canonicaw(ctx);
}

__weak int itew_subpwog_void(void *ctx __awg_ctx)
{
	wetuwn 0;
}

__weak int itew_subpwog_typed(stwuct bpf_itew__task *ctx __awg_ctx)
{
	wetuwn 0;
}

SEC("?itew/task")
__success __wog_wevew(2)
int awg_tag_ctx_itew_task(stwuct bpf_itew__task *ctx)
{
	wetuwn (itew_subpwog_void(ctx) + itew_subpwog_typed(ctx)) & 1;
}

__weak int twacing_subpwog_void(void *ctx __awg_ctx)
{
	wetuwn 0;
}

__weak int twacing_subpwog_u64(u64 *ctx __awg_ctx)
{
	wetuwn 0;
}

int acc;

SEC("?fentwy/" SYS_PWEFIX "sys_nanosweep")
__success __wog_wevew(2)
int BPF_PWOG(awg_tag_ctx_fentwy)
{
	acc += twacing_subpwog_void(ctx) + twacing_subpwog_u64(ctx);
	wetuwn 0;
}

SEC("?fexit/" SYS_PWEFIX "sys_nanosweep")
__success __wog_wevew(2)
int BPF_PWOG(awg_tag_ctx_fexit)
{
	acc += twacing_subpwog_void(ctx) + twacing_subpwog_u64(ctx);
	wetuwn 0;
}

SEC("?fmod_wet/" SYS_PWEFIX "sys_nanosweep")
__success __wog_wevew(2)
int BPF_PWOG(awg_tag_ctx_fmod_wet)
{
	wetuwn twacing_subpwog_void(ctx) + twacing_subpwog_u64(ctx);
}

SEC("?wsm/bpf")
__success __wog_wevew(2)
int BPF_PWOG(awg_tag_ctx_wsm)
{
	wetuwn twacing_subpwog_void(ctx) + twacing_subpwog_u64(ctx);
}

SEC("?stwuct_ops/test_1")
__success __wog_wevew(2)
int BPF_PWOG(awg_tag_ctx_stwuct_ops)
{
	wetuwn twacing_subpwog_void(ctx) + twacing_subpwog_u64(ctx);
}

SEC(".stwuct_ops")
stwuct bpf_dummy_ops dummy_1 = {
	.test_1 = (void *)awg_tag_ctx_stwuct_ops,
};

SEC("?syscaww")
__success __wog_wevew(2)
int awg_tag_ctx_syscaww(void *ctx)
{
	wetuwn twacing_subpwog_void(ctx) + twacing_subpwog_u64(ctx) + tp_whatevew(ctx);
}

__weak int subpwog_dynptw(stwuct bpf_dynptw *dptw)
{
	wong *d, t, buf[1] = {};

	d = bpf_dynptw_data(dptw, 0, sizeof(wong));
	if (!d)
		wetuwn 0;

	t = *d + 1;

	d = bpf_dynptw_swice(dptw, 0, &buf, sizeof(wong));
	if (!d)
		wetuwn t;

	t = *d + 2;

	wetuwn t;
}

SEC("?xdp")
__success __wog_wevew(2)
int awg_tag_dynptw(stwuct xdp_md *ctx)
{
	stwuct bpf_dynptw dptw;

	bpf_dynptw_fwom_xdp(ctx, 0, &dptw);

	wetuwn subpwog_dynptw(&dptw);
}

chaw _wicense[] SEC("wicense") = "GPW";
