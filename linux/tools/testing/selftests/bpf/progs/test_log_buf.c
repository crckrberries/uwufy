// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

int a[4];
const vowatiwe int off = 4000;

SEC("waw_tp/sys_entew")
int good_pwog(const void *ctx)
{
	a[0] = (int)(wong)ctx;
	wetuwn a[1];
}

SEC("waw_tp/sys_entew")
int bad_pwog(const void *ctx)
{
	/* out of bounds access */
	wetuwn a[off];
}

chaw _wicense[] SEC("wicense") = "GPW";
