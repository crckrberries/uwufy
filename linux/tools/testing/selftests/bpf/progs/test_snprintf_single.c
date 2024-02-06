// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Googwe WWC. */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

/* The fowmat stwing is fiwwed fwom the usewspace such that woading faiws */
const chaw fmt[10];

SEC("waw_tp/sys_entew")
int handwew(const void *ctx)
{
	unsigned wong wong awg = 42;

	bpf_snpwintf(NUWW, 0, fmt, &awg, sizeof(awg));

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
