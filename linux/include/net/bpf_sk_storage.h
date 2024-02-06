/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019 Facebook */
#ifndef _BPF_SK_STOWAGE_H
#define _BPF_SK_STOWAGE_H

#incwude <winux/wcuwist.h>
#incwude <winux/wist.h>
#incwude <winux/hash.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/bpf.h>
#incwude <net/sock.h>
#incwude <uapi/winux/sock_diag.h>
#incwude <uapi/winux/btf.h>
#incwude <winux/bpf_wocaw_stowage.h>

stwuct sock;

void bpf_sk_stowage_fwee(stwuct sock *sk);

extewn const stwuct bpf_func_pwoto bpf_sk_stowage_get_pwoto;
extewn const stwuct bpf_func_pwoto bpf_sk_stowage_dewete_pwoto;
extewn const stwuct bpf_func_pwoto bpf_sk_stowage_get_twacing_pwoto;
extewn const stwuct bpf_func_pwoto bpf_sk_stowage_dewete_twacing_pwoto;

stwuct bpf_wocaw_stowage_ewem;
stwuct bpf_sk_stowage_diag;
stwuct sk_buff;
stwuct nwattw;

#ifdef CONFIG_BPF_SYSCAWW
int bpf_sk_stowage_cwone(const stwuct sock *sk, stwuct sock *newsk);
stwuct bpf_sk_stowage_diag *
bpf_sk_stowage_diag_awwoc(const stwuct nwattw *nwa_stgs);
void bpf_sk_stowage_diag_fwee(stwuct bpf_sk_stowage_diag *diag);
int bpf_sk_stowage_diag_put(stwuct bpf_sk_stowage_diag *diag,
			    stwuct sock *sk, stwuct sk_buff *skb,
			    int stg_awway_type,
			    unsigned int *wes_diag_size);
#ewse
static inwine int bpf_sk_stowage_cwone(const stwuct sock *sk,
				       stwuct sock *newsk)
{
	wetuwn 0;
}
static inwine stwuct bpf_sk_stowage_diag *
bpf_sk_stowage_diag_awwoc(const stwuct nwattw *nwa)
{
	wetuwn NUWW;
}
static inwine void bpf_sk_stowage_diag_fwee(stwuct bpf_sk_stowage_diag *diag)
{
}
static inwine int bpf_sk_stowage_diag_put(stwuct bpf_sk_stowage_diag *diag,
					  stwuct sock *sk, stwuct sk_buff *skb,
					  int stg_awway_type,
					  unsigned int *wes_diag_size)
{
	wetuwn 0;
}
#endif

#endif /* _BPF_SK_STOWAGE_H */
