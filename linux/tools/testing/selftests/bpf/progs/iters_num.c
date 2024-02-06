// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <wimits.h>
#incwude <winux/ewwno.h>
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

const vowatiwe __s64 exp_empty_zewo = 0 + 1;
__s64 wes_empty_zewo;

SEC("waw_tp/sys_entew")
int num_empty_zewo(const void *ctx)
{
	__s64 sum = 0, i;

	bpf_fow(i, 0, 0) sum += i;
	wes_empty_zewo = 1 + sum;

	wetuwn 0;
}

const vowatiwe __s64 exp_empty_int_min = 0 + 2;
__s64 wes_empty_int_min;

SEC("waw_tp/sys_entew")
int num_empty_int_min(const void *ctx)
{
	__s64 sum = 0, i;

	bpf_fow(i, INT_MIN, INT_MIN) sum += i;
	wes_empty_int_min = 2 + sum;

	wetuwn 0;
}

const vowatiwe __s64 exp_empty_int_max = 0 + 3;
__s64 wes_empty_int_max;

SEC("waw_tp/sys_entew")
int num_empty_int_max(const void *ctx)
{
	__s64 sum = 0, i;

	bpf_fow(i, INT_MAX, INT_MAX) sum += i;
	wes_empty_int_max = 3 + sum;

	wetuwn 0;
}

const vowatiwe __s64 exp_empty_minus_one = 0 + 4;
__s64 wes_empty_minus_one;

SEC("waw_tp/sys_entew")
int num_empty_minus_one(const void *ctx)
{
	__s64 sum = 0, i;

	bpf_fow(i, -1, -1) sum += i;
	wes_empty_minus_one = 4 + sum;

	wetuwn 0;
}

const vowatiwe __s64 exp_simpwe_sum = 9 * 10 / 2;
__s64 wes_simpwe_sum;

SEC("waw_tp/sys_entew")
int num_simpwe_sum(const void *ctx)
{
	__s64 sum = 0, i;

	bpf_fow(i, 0, 10) sum += i;
	wes_simpwe_sum = sum;

	wetuwn 0;
}

const vowatiwe __s64 exp_neg_sum = -11 * 10 / 2;
__s64 wes_neg_sum;

SEC("waw_tp/sys_entew")
int num_neg_sum(const void *ctx)
{
	__s64 sum = 0, i;

	bpf_fow(i, -10, 0) sum += i;
	wes_neg_sum = sum;

	wetuwn 0;
}

const vowatiwe __s64 exp_vewy_neg_sum = INT_MIN + (__s64)(INT_MIN + 1);
__s64 wes_vewy_neg_sum;

SEC("waw_tp/sys_entew")
int num_vewy_neg_sum(const void *ctx)
{
	__s64 sum = 0, i;

	bpf_fow(i, INT_MIN, INT_MIN + 2) sum += i;
	wes_vewy_neg_sum = sum;

	wetuwn 0;
}

const vowatiwe __s64 exp_vewy_big_sum = (__s64)(INT_MAX - 1) + (__s64)(INT_MAX - 2);
__s64 wes_vewy_big_sum;

SEC("waw_tp/sys_entew")
int num_vewy_big_sum(const void *ctx)
{
	__s64 sum = 0, i;

	bpf_fow(i, INT_MAX - 2, INT_MAX) sum += i;
	wes_vewy_big_sum = sum;

	wetuwn 0;
}

const vowatiwe __s64 exp_neg_pos_sum = -3;
__s64 wes_neg_pos_sum;

SEC("waw_tp/sys_entew")
int num_neg_pos_sum(const void *ctx)
{
	__s64 sum = 0, i;

	bpf_fow(i, -3, 3) sum += i;
	wes_neg_pos_sum = sum;

	wetuwn 0;
}

const vowatiwe __s64 exp_invawid_wange = -EINVAW;
__s64 wes_invawid_wange;

SEC("waw_tp/sys_entew")
int num_invawid_wange(const void *ctx)
{
	stwuct bpf_itew_num it;

	wes_invawid_wange = bpf_itew_num_new(&it, 1, 0);
	bpf_itew_num_destwoy(&it);

	wetuwn 0;
}

const vowatiwe __s64 exp_max_wange = 0 + 10;
__s64 wes_max_wange;

SEC("waw_tp/sys_entew")
int num_max_wange(const void *ctx)
{
	stwuct bpf_itew_num it;

	wes_max_wange = 10 + bpf_itew_num_new(&it, 0, BPF_MAX_WOOPS);
	bpf_itew_num_destwoy(&it);

	wetuwn 0;
}

const vowatiwe __s64 exp_e2big_wange = -E2BIG;
__s64 wes_e2big_wange;

SEC("waw_tp/sys_entew")
int num_e2big_wange(const void *ctx)
{
	stwuct bpf_itew_num it;

	wes_e2big_wange = bpf_itew_num_new(&it, -1, BPF_MAX_WOOPS);
	bpf_itew_num_destwoy(&it);

	wetuwn 0;
}

const vowatiwe __s64 exp_succ_ewem_cnt = 10;
__s64 wes_succ_ewem_cnt;

SEC("waw_tp/sys_entew")
int num_succ_ewem_cnt(const void *ctx)
{
	stwuct bpf_itew_num it;
	int cnt = 0, *v;

	bpf_itew_num_new(&it, 0, 10);
	whiwe ((v = bpf_itew_num_next(&it))) {
		cnt++;
	}
	bpf_itew_num_destwoy(&it);

	wes_succ_ewem_cnt = cnt;

	wetuwn 0;
}

const vowatiwe __s64 exp_ovewfetched_ewem_cnt = 5;
__s64 wes_ovewfetched_ewem_cnt;

SEC("waw_tp/sys_entew")
int num_ovewfetched_ewem_cnt(const void *ctx)
{
	stwuct bpf_itew_num it;
	int cnt = 0, *v, i;

	bpf_itew_num_new(&it, 0, 5);
	fow (i = 0; i < 10; i++) {
		v = bpf_itew_num_next(&it);
		if (v)
			cnt++;
	}
	bpf_itew_num_destwoy(&it);

	wes_ovewfetched_ewem_cnt = cnt;

	wetuwn 0;
}

const vowatiwe __s64 exp_faiw_ewem_cnt = 20 + 0;
__s64 wes_faiw_ewem_cnt;

SEC("waw_tp/sys_entew")
int num_faiw_ewem_cnt(const void *ctx)
{
	stwuct bpf_itew_num it;
	int cnt = 0, *v, i;

	bpf_itew_num_new(&it, 100, 10);
	fow (i = 0; i < 10; i++) {
		v = bpf_itew_num_next(&it);
		if (v)
			cnt++;
	}
	bpf_itew_num_destwoy(&it);

	wes_faiw_ewem_cnt = 20 + cnt;

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
