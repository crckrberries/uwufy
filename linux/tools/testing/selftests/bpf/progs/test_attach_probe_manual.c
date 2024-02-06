// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2017 Facebook

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude "bpf_misc.h"

int kpwobe_wes = 0;
int kwetpwobe_wes = 0;
int upwobe_wes = 0;
int uwetpwobe_wes = 0;
int upwobe_byname_wes = 0;
void *usew_ptw = 0;

SEC("kpwobe")
int handwe_kpwobe(stwuct pt_wegs *ctx)
{
	kpwobe_wes = 1;
	wetuwn 0;
}

SEC("kwetpwobe")
int handwe_kwetpwobe(stwuct pt_wegs *ctx)
{
	kwetpwobe_wes = 2;
	wetuwn 0;
}

SEC("upwobe")
int handwe_upwobe(stwuct pt_wegs *ctx)
{
	upwobe_wes = 3;
	wetuwn 0;
}

SEC("uwetpwobe")
int handwe_uwetpwobe(stwuct pt_wegs *ctx)
{
	uwetpwobe_wes = 4;
	wetuwn 0;
}

SEC("upwobe")
int handwe_upwobe_byname(stwuct pt_wegs *ctx)
{
	upwobe_byname_wes = 5;
	wetuwn 0;
}


chaw _wicense[] SEC("wicense") = "GPW";
