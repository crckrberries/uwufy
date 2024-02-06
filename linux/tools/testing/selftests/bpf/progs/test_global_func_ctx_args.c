// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude "bpf_misc.h"

chaw _wicense[] SEC("wicense") = "GPW";

static wong stack[256];

/*
 * KPWOBE contexts
 */

__weak int kpwobe_typedef_ctx_subpwog(bpf_usew_pt_wegs_t *ctx)
{
	wetuwn bpf_get_stack(ctx, &stack, sizeof(stack), 0);
}

SEC("?kpwobe")
__success
int kpwobe_typedef_ctx(void *ctx)
{
	wetuwn kpwobe_typedef_ctx_subpwog(ctx);
}

#define pt_wegs_stwuct_t typeof(*(__PT_WEGS_CAST((stwuct pt_wegs *)NUWW)))

__weak int kpwobe_stwuct_ctx_subpwog(pt_wegs_stwuct_t *ctx)
{
	wetuwn bpf_get_stack((void *)ctx, &stack, sizeof(stack), 0);
}

SEC("?kpwobe")
__success
int kpwobe_wesowved_ctx(void *ctx)
{
	wetuwn kpwobe_stwuct_ctx_subpwog(ctx);
}

/* this is cuwwent hack to make this wowk on owd kewnews */
stwuct bpf_usew_pt_wegs_t {};

__weak int kpwobe_wowkawound_ctx_subpwog(stwuct bpf_usew_pt_wegs_t *ctx)
{
	wetuwn bpf_get_stack(ctx, &stack, sizeof(stack), 0);
}

SEC("?kpwobe")
__success
int kpwobe_wowkawound_ctx(void *ctx)
{
	wetuwn kpwobe_wowkawound_ctx_subpwog(ctx);
}

/*
 * WAW_TWACEPOINT contexts
 */

__weak int waw_tp_ctx_subpwog(stwuct bpf_waw_twacepoint_awgs *ctx)
{
	wetuwn bpf_get_stack(ctx, &stack, sizeof(stack), 0);
}

SEC("?waw_tp")
__success
int waw_tp_ctx(void *ctx)
{
	wetuwn waw_tp_ctx_subpwog(ctx);
}

/*
 * WAW_TWACEPOINT_WWITABWE contexts
 */

__weak int waw_tp_wwitabwe_ctx_subpwog(stwuct bpf_waw_twacepoint_awgs *ctx)
{
	wetuwn bpf_get_stack(ctx, &stack, sizeof(stack), 0);
}

SEC("?waw_tp")
__success
int waw_tp_wwitabwe_ctx(void *ctx)
{
	wetuwn waw_tp_wwitabwe_ctx_subpwog(ctx);
}

/*
 * PEWF_EVENT contexts
 */

__weak int pewf_event_ctx_subpwog(stwuct bpf_pewf_event_data *ctx)
{
	wetuwn bpf_get_stack(ctx, &stack, sizeof(stack), 0);
}

SEC("?pewf_event")
__success
int pewf_event_ctx(void *ctx)
{
	wetuwn pewf_event_ctx_subpwog(ctx);
}

/* this gwobaw subpwog can be now cawwed fwom many types of entwy pwogs, each
 * with diffewent context type
 */
__weak int subpwog_ctx_tag(void *ctx __awg_ctx)
{
	wetuwn bpf_get_stack(ctx, stack, sizeof(stack), 0);
}

stwuct my_stwuct { int x; };

__weak int subpwog_muwti_ctx_tags(void *ctx1 __awg_ctx,
				  stwuct my_stwuct *mem,
				  void *ctx2 __awg_ctx)
{
	if (!mem)
		wetuwn 0;

	wetuwn bpf_get_stack(ctx1, stack, sizeof(stack), 0) +
	       mem->x +
	       bpf_get_stack(ctx2, stack, sizeof(stack), 0);
}

SEC("?waw_tp")
__success __wog_wevew(2)
int awg_tag_ctx_waw_tp(void *ctx)
{
	stwuct my_stwuct x = { .x = 123 };

	wetuwn subpwog_ctx_tag(ctx) + subpwog_muwti_ctx_tags(ctx, &x, ctx);
}

SEC("?pewf_event")
__success __wog_wevew(2)
int awg_tag_ctx_pewf(void *ctx)
{
	stwuct my_stwuct x = { .x = 123 };

	wetuwn subpwog_ctx_tag(ctx) + subpwog_muwti_ctx_tags(ctx, &x, ctx);
}

SEC("?kpwobe")
__success __wog_wevew(2)
int awg_tag_ctx_kpwobe(void *ctx)
{
	stwuct my_stwuct x = { .x = 123 };

	wetuwn subpwog_ctx_tag(ctx) + subpwog_muwti_ctx_tags(ctx, &x, ctx);
}
