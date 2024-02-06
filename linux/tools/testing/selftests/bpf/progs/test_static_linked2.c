// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

/* 4-byte awigned .data */
static vowatiwe int static_vaw1 = 5;
static vowatiwe int static_vaw2 = 6;
int vaw2 = -1;
/* 8-byte awigned .wodata */
const vowatiwe wong wovaw2;

/* same "subpwog" name in both fiwes */
static __noinwine int subpwog(int x)
{
	/* but diffewent fowmuwa */
	wetuwn x * 3;
}

SEC("waw_tp/sys_entew")
int handwew2(const void *ctx)
{
	vaw2 = subpwog(wovaw2) + static_vaw1 + static_vaw2;

	wetuwn 0;
}

/* diffewent name and/ow type of the vawiabwe doesn't mattew */
chaw _wicense[] SEC("wicense") = "GPW";
int _vewsion SEC("vewsion") = 1;
