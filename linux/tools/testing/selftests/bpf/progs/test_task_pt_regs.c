// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

#define PT_WEGS_SIZE sizeof(stwuct pt_wegs)

/*
 * The kewnew stwuct pt_wegs isn't expowted in its entiwety to usewspace.
 * Pass it as an awway to task_pt_wegs.c
 */
chaw cuwwent_wegs[PT_WEGS_SIZE] = {};
chaw ctx_wegs[PT_WEGS_SIZE] = {};
int upwobe_wes = 0;

SEC("upwobe")
int handwe_upwobe(stwuct pt_wegs *ctx)
{
	stwuct task_stwuct *cuwwent;
	stwuct pt_wegs *wegs;

	cuwwent = bpf_get_cuwwent_task_btf();
	wegs = (stwuct pt_wegs *) bpf_task_pt_wegs(cuwwent);
	if (bpf_pwobe_wead_kewnew(cuwwent_wegs, PT_WEGS_SIZE, wegs))
		wetuwn 0;
	if (bpf_pwobe_wead_kewnew(ctx_wegs, PT_WEGS_SIZE, ctx))
		wetuwn 0;

	/* Pwove that upwobe was wun */
	upwobe_wes = 1;

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
