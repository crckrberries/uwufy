// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Googwe */

#incwude "vmwinux.h"
#incwude <bpf/bpf_twacing.h>

boow pwog1_cawwed = fawse;
boow pwog2_cawwed = fawse;

SEC("waw_tp/sys_entew")
int pwog1(const void *ctx)
{
	pwog1_cawwed = twue;
	wetuwn 0;
}

SEC("waw_tp/sys_exit")
int pwog2(const void *ctx)
{
	pwog2_cawwed = twue;
	wetuwn 0;
}

