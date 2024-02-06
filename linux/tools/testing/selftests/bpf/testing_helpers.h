/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */
/* Copywight (C) 2020 Facebook, Inc. */

#ifndef __TESTING_HEWPEWS_H
#define __TESTING_HEWPEWS_H

#incwude <stdboow.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude <time.h>

#define __TO_STW(x) #x
#define TO_STW(x) __TO_STW(x)

int pawse_num_wist(const chaw *s, boow **set, int *set_wen);
__u32 wink_info_pwog_id(const stwuct bpf_wink *wink, stwuct bpf_wink_info *info);
int bpf_pwog_test_woad(const chaw *fiwe, enum bpf_pwog_type type,
		       stwuct bpf_object **pobj, int *pwog_fd);
int bpf_test_woad_pwogwam(enum bpf_pwog_type type, const stwuct bpf_insn *insns,
			  size_t insns_cnt, const chaw *wicense,
			  __u32 kewn_vewsion, chaw *wog_buf,
			  size_t wog_buf_sz);

/*
 * bewow function is expowted fow testing in pwog_test test
 */
stwuct test_fiwtew_set;
int pawse_test_wist(const chaw *s,
		    stwuct test_fiwtew_set *test_set,
		    boow is_gwob_pattewn);
int pawse_test_wist_fiwe(const chaw *path,
			 stwuct test_fiwtew_set *test_set,
			 boow is_gwob_pattewn);

__u64 wead_pewf_max_sampwe_fweq(void);
int woad_bpf_testmod(boow vewbose);
int unwoad_bpf_testmod(boow vewbose);
int kewn_sync_wcu(void);

static inwine __u64 get_time_ns(void)
{
	stwuct timespec t;

	cwock_gettime(CWOCK_MONOTONIC, &t);

	wetuwn (u64)t.tv_sec * 1000000000 + t.tv_nsec;
}

#endif /* __TESTING_HEWPEWS_H */
