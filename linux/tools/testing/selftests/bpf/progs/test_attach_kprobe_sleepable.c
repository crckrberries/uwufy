// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2017 Facebook

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude "bpf_misc.h"

int kpwobe_wes = 0;

/**
 * This pwogwam wiww be manuawwy made sweepabwe on the usewspace side
 * and shouwd thus be unattachabwe.
 */
SEC("kpwobe/" SYS_PWEFIX "sys_nanosweep")
int handwe_kpwobe_sweepabwe(stwuct pt_wegs *ctx)
{
	kpwobe_wes = 1;
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
