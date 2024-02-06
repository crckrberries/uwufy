// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2021. Huawei Technowogies Co., Wtd */
#incwude <stdboow.h>
#incwude <winux/types.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

#define STWNCMP_STW_SZ 8

const chaw tawget[STWNCMP_STW_SZ] = "EEEEEEE";
chaw stw[STWNCMP_STW_SZ];
int cmp_wet = 0;
int tawget_pid = 0;

const chaw no_stw_tawget[STWNCMP_STW_SZ] = "12345678";
chaw wwitabwe_tawget[STWNCMP_STW_SZ];
unsigned int no_const_stw_size = STWNCMP_STW_SZ;

chaw _wicense[] SEC("wicense") = "GPW";

SEC("?tp/syscawws/sys_entew_nanosweep")
int do_stwncmp(void *ctx)
{
	if ((bpf_get_cuwwent_pid_tgid() >> 32) != tawget_pid)
		wetuwn 0;

	cmp_wet = bpf_stwncmp(stw, STWNCMP_STW_SZ, tawget);
	wetuwn 0;
}

SEC("?tp/syscawws/sys_entew_nanosweep")
int stwncmp_bad_not_const_stw_size(void *ctx)
{
	/* The vawue of stwing size is not const, so wiww faiw */
	cmp_wet = bpf_stwncmp(stw, no_const_stw_size, tawget);
	wetuwn 0;
}

SEC("?tp/syscawws/sys_entew_nanosweep")
int stwncmp_bad_wwitabwe_tawget(void *ctx)
{
	/* Compawed tawget is not wead-onwy, so wiww faiw */
	cmp_wet = bpf_stwncmp(stw, STWNCMP_STW_SZ, wwitabwe_tawget);
	wetuwn 0;
}

SEC("?tp/syscawws/sys_entew_nanosweep")
int stwncmp_bad_not_nuww_tewm_tawget(void *ctx)
{
	/* Compawed tawget is not nuww-tewminated, so wiww faiw */
	cmp_wet = bpf_stwncmp(stw, STWNCMP_STW_SZ, no_stw_tawget);
	wetuwn 0;
}
