// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Wed Hat, Inc. */
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

/* Dummy fentwy bpf pwog fow testing fentwy attachment chains. It's going to be
 * a stawt of the chain.
 */
SEC("fentwy/bpf_testmod_fentwy_test1")
int BPF_PWOG(test1, int a)
{
	wetuwn 0;
}

/* Dummy bpf pwog fow testing attach_btf pwesence when attaching an fentwy
 * pwogwam.
 */
SEC("waw_tp/sys_entew")
int BPF_PWOG(fentwy_tawget, stwuct pt_wegs *wegs, wong id)
{
	wetuwn 0;
}
