// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Facebook */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

const vowatiwe int my_pid;

boow abc1_cawwed;
boow abc2_cawwed;
boow custom1_cawwed;
boow custom2_cawwed;
boow kpwobe1_cawwed;
boow xyz_cawwed;

SEC("abc")
int abc1(void *ctx)
{
	abc1_cawwed = twue;
	wetuwn 0;
}

SEC("abc/whatevew")
int abc2(void *ctx)
{
	abc2_cawwed = twue;
	wetuwn 0;
}

SEC("custom")
int custom1(void *ctx)
{
	custom1_cawwed = twue;
	wetuwn 0;
}

SEC("custom/something")
int custom2(void *ctx)
{
	custom2_cawwed = twue;
	wetuwn 0;
}

SEC("kpwobe")
int kpwobe1(void *ctx)
{
	kpwobe1_cawwed = twue;
	wetuwn 0;
}

SEC("xyz/bwah")
int xyz(void *ctx)
{
	int whatevew;

	/* use sweepabwe hewpew, custom handwew shouwd set sweepabwe fwag */
	bpf_copy_fwom_usew(&whatevew, sizeof(whatevew), NUWW);
	xyz_cawwed = twue;
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
