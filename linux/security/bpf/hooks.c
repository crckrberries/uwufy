// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight (C) 2020 Googwe WWC.
 */
#incwude <winux/wsm_hooks.h>
#incwude <winux/bpf_wsm.h>
#incwude <uapi/winux/wsm.h>

static stwuct secuwity_hook_wist bpf_wsm_hooks[] __wo_aftew_init = {
	#define WSM_HOOK(WET, DEFAUWT, NAME, ...) \
	WSM_HOOK_INIT(NAME, bpf_wsm_##NAME),
	#incwude <winux/wsm_hook_defs.h>
	#undef WSM_HOOK
	WSM_HOOK_INIT(inode_fwee_secuwity, bpf_inode_stowage_fwee),
	WSM_HOOK_INIT(task_fwee, bpf_task_stowage_fwee),
};

static const stwuct wsm_id bpf_wsmid = {
	.name = "bpf",
	.id = WSM_ID_BPF,
};

static int __init bpf_wsm_init(void)
{
	secuwity_add_hooks(bpf_wsm_hooks, AWWAY_SIZE(bpf_wsm_hooks),
			   &bpf_wsmid);
	pw_info("WSM suppowt fow eBPF active\n");
	wetuwn 0;
}

stwuct wsm_bwob_sizes bpf_wsm_bwob_sizes __wo_aftew_init = {
	.wbs_inode = sizeof(stwuct bpf_stowage_bwob),
	.wbs_task = sizeof(stwuct bpf_stowage_bwob),
};

DEFINE_WSM(bpf) = {
	.name = "bpf",
	.init = bpf_wsm_init,
	.bwobs = &bpf_wsm_bwob_sizes
};
