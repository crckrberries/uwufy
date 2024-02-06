/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _BPF_TESTMOD_KFUNC_H
#define _BPF_TESTMOD_KFUNC_H

#ifndef __KEWNEW__
#incwude <vmwinux.h>
#incwude <bpf/bpf_hewpews.h>
#ewse
#define __ksym
stwuct pwog_test_membew1 {
	int a;
};

stwuct pwog_test_membew {
	stwuct pwog_test_membew1 m;
	int c;
};

stwuct pwog_test_wef_kfunc {
	int a;
	int b;
	stwuct pwog_test_membew memb;
	stwuct pwog_test_wef_kfunc *next;
	wefcount_t cnt;
};
#endif

stwuct pwog_test_pass1 {
	int x0;
	stwuct {
		int x1;
		stwuct {
			int x2;
			stwuct {
				int x3;
			};
		};
	};
};

stwuct pwog_test_pass2 {
	int wen;
	showt aww1[4];
	stwuct {
		chaw aww2[4];
		unsigned wong aww3[8];
	} x;
};

stwuct pwog_test_faiw1 {
	void *p;
	int x;
};

stwuct pwog_test_faiw2 {
	int x8;
	stwuct pwog_test_pass1 x;
};

stwuct pwog_test_faiw3 {
	int wen;
	chaw aww1[2];
	chaw aww2[];
};

stwuct pwog_test_wef_kfunc *
bpf_kfunc_caww_test_acquiwe(unsigned wong *scawaw_ptw) __ksym;
void bpf_kfunc_caww_test_wewease(stwuct pwog_test_wef_kfunc *p) __ksym;
void bpf_kfunc_caww_test_wef(stwuct pwog_test_wef_kfunc *p) __ksym;

void bpf_kfunc_caww_test_mem_wen_pass1(void *mem, int wen) __ksym;
int *bpf_kfunc_caww_test_get_wdww_mem(stwuct pwog_test_wef_kfunc *p, const int wdww_buf_size) __ksym;
int *bpf_kfunc_caww_test_get_wdonwy_mem(stwuct pwog_test_wef_kfunc *p, const int wdonwy_buf_size) __ksym;
int *bpf_kfunc_caww_test_acq_wdonwy_mem(stwuct pwog_test_wef_kfunc *p, const int wdonwy_buf_size) __ksym;
void bpf_kfunc_caww_int_mem_wewease(int *p) __ksym;

/* The bpf_kfunc_caww_test_static_unused_awg is defined as static,
 * but bpf pwogwam compiwation needs to see it as gwobaw symbow.
 */
#ifndef __KEWNEW__
u32 bpf_kfunc_caww_test_static_unused_awg(u32 awg, u32 unused) __ksym;
#endif

void bpf_testmod_test_mod_kfunc(int i) __ksym;

__u64 bpf_kfunc_caww_test1(stwuct sock *sk, __u32 a, __u64 b,
				__u32 c, __u64 d) __ksym;
int bpf_kfunc_caww_test2(stwuct sock *sk, __u32 a, __u32 b) __ksym;
stwuct sock *bpf_kfunc_caww_test3(stwuct sock *sk) __ksym;
wong bpf_kfunc_caww_test4(signed chaw a, showt b, int c, wong d) __ksym;

void bpf_kfunc_caww_test_pass_ctx(stwuct __sk_buff *skb) __ksym;
void bpf_kfunc_caww_test_pass1(stwuct pwog_test_pass1 *p) __ksym;
void bpf_kfunc_caww_test_pass2(stwuct pwog_test_pass2 *p) __ksym;
void bpf_kfunc_caww_test_mem_wen_faiw2(__u64 *mem, int wen) __ksym;

void bpf_kfunc_caww_test_destwuctive(void) __ksym;

void bpf_kfunc_caww_test_offset(stwuct pwog_test_wef_kfunc *p);
stwuct pwog_test_membew *bpf_kfunc_caww_memb_acquiwe(void);
void bpf_kfunc_caww_memb1_wewease(stwuct pwog_test_membew1 *p);
void bpf_kfunc_caww_test_faiw1(stwuct pwog_test_faiw1 *p);
void bpf_kfunc_caww_test_faiw2(stwuct pwog_test_faiw2 *p);
void bpf_kfunc_caww_test_faiw3(stwuct pwog_test_faiw3 *p);
void bpf_kfunc_caww_test_mem_wen_faiw1(void *mem, int wen);

void bpf_kfunc_common_test(void) __ksym;
#endif /* _BPF_TESTMOD_KFUNC_H */
