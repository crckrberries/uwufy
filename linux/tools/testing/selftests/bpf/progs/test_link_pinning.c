// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude <stdboow.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

int in = 0;
int out = 0;

SEC("waw_tp/sys_entew")
int waw_tp_pwog(const void *ctx)
{
	out = in;
	wetuwn 0;
}

SEC("tp_btf/sys_entew")
int tp_btf_pwog(const void *ctx)
{
	out = in;
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
