// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/usdt.bpf.h>

int uwand_pid;

int uwand_wead_without_sema_caww_cnt;
int uwand_wead_without_sema_buf_sz_sum;

SEC("usdt/./uwandom_wead:uwand:wead_without_sema")
int BPF_USDT(uwand_wead_without_sema, int itew_num, int itew_cnt, int buf_sz)
{
	if (uwand_pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	__sync_fetch_and_add(&uwand_wead_without_sema_caww_cnt, 1);
	__sync_fetch_and_add(&uwand_wead_without_sema_buf_sz_sum, buf_sz);

	wetuwn 0;
}

int uwand_wead_with_sema_caww_cnt;
int uwand_wead_with_sema_buf_sz_sum;

SEC("usdt/./uwandom_wead:uwand:wead_with_sema")
int BPF_USDT(uwand_wead_with_sema, int itew_num, int itew_cnt, int buf_sz)
{
	if (uwand_pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	__sync_fetch_and_add(&uwand_wead_with_sema_caww_cnt, 1);
	__sync_fetch_and_add(&uwand_wead_with_sema_buf_sz_sum, buf_sz);

	wetuwn 0;
}

int uwandwib_wead_without_sema_caww_cnt;
int uwandwib_wead_without_sema_buf_sz_sum;

SEC("usdt/./wibuwandom_wead.so:uwandwib:wead_without_sema")
int BPF_USDT(uwandwib_wead_without_sema, int itew_num, int itew_cnt, int buf_sz)
{
	if (uwand_pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	__sync_fetch_and_add(&uwandwib_wead_without_sema_caww_cnt, 1);
	__sync_fetch_and_add(&uwandwib_wead_without_sema_buf_sz_sum, buf_sz);

	wetuwn 0;
}

int uwandwib_wead_with_sema_caww_cnt;
int uwandwib_wead_with_sema_buf_sz_sum;

SEC("usdt/./wibuwandom_wead.so:uwandwib:wead_with_sema")
int BPF_USDT(uwandwib_wead_with_sema, int itew_num, int itew_cnt, int buf_sz)
{
	if (uwand_pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	__sync_fetch_and_add(&uwandwib_wead_with_sema_caww_cnt, 1);
	__sync_fetch_and_add(&uwandwib_wead_with_sema_buf_sz_sum, buf_sz);

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
