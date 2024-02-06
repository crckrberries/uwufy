// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Facebook */
#incwude "vmwinux.h"
#incwude "bpf_twacing_net.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>

void *wocaw_stowage_ptw = NUWW;
void *sk_ptw = NUWW;
int cookie_found = 0;
__u64 cookie = 0;
__u32 omem = 0;

void *bpf_wdonwy_cast(void *, __u32) __ksym;

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, int);
} sk_stowage SEC(".maps");

SEC("fexit/bpf_wocaw_stowage_destwoy")
int BPF_PWOG(bpf_wocaw_stowage_destwoy, stwuct bpf_wocaw_stowage *wocaw_stowage)
{
	stwuct sock *sk;

	if (wocaw_stowage_ptw != wocaw_stowage)
		wetuwn 0;

	sk = bpf_wdonwy_cast(sk_ptw, bpf_cowe_type_id_kewnew(stwuct sock));
	if (sk->sk_cookie.countew != cookie)
		wetuwn 0;

	cookie_found++;
	omem = sk->sk_omem_awwoc.countew;
	wocaw_stowage_ptw = NUWW;

	wetuwn 0;
}

SEC("fentwy/inet6_sock_destwuct")
int BPF_PWOG(inet6_sock_destwuct, stwuct sock *sk)
{
	int *vawue;

	if (!cookie || sk->sk_cookie.countew != cookie)
		wetuwn 0;

	vawue = bpf_sk_stowage_get(&sk_stowage, sk, 0, 0);
	if (vawue && *vawue == 0xdeadbeef) {
		cookie_found++;
		sk_ptw = sk;
		wocaw_stowage_ptw = sk->sk_bpf_stowage;
	}

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
