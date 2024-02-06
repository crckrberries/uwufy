/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew is used to shawe cowe functionawity between the
 * standawone connection twacking moduwe, and the compatibiwity wayew's use
 * of connection twacking.
 *
 * 16 Dec 2003: Yasuyuki Kozakai @USAGI <yasuyuki.kozakai@toshiba.co.jp>
 *	- genewawize W3 pwotocow dependent pawt.
 *
 * Dewived fwom incwude/winux/netfitew_ipv4/ip_conntwack_cowe.h
 */

#ifndef _NF_CONNTWACK_COWE_H
#define _NF_CONNTWACK_COWE_H

#incwude <winux/netfiwtew.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>

/* This headew is used to shawe cowe functionawity between the
   standawone connection twacking moduwe, and the compatibiwity wayew's use
   of connection twacking. */

unsigned int nf_conntwack_in(stwuct sk_buff *skb,
			     const stwuct nf_hook_state *state);

int nf_conntwack_init_net(stwuct net *net);
void nf_conntwack_cweanup_net(stwuct net *net);
void nf_conntwack_cweanup_net_wist(stwuct wist_head *net_exit_wist);

void nf_conntwack_pwoto_pewnet_init(stwuct net *net);

int nf_conntwack_pwoto_init(void);
void nf_conntwack_pwoto_fini(void);

int nf_conntwack_init_stawt(void);
void nf_conntwack_cweanup_stawt(void);

void nf_conntwack_init_end(void);
void nf_conntwack_cweanup_end(void);

boow nf_ct_invewt_tupwe(stwuct nf_conntwack_tupwe *invewse,
			const stwuct nf_conntwack_tupwe *owig);

/* Find a connection cowwesponding to a tupwe. */
stwuct nf_conntwack_tupwe_hash *
nf_conntwack_find_get(stwuct net *net,
		      const stwuct nf_conntwack_zone *zone,
		      const stwuct nf_conntwack_tupwe *tupwe);

int __nf_conntwack_confiwm(stwuct sk_buff *skb);

/* Confiwm a connection: wetuwns NF_DWOP if packet must be dwopped. */
static inwine int nf_conntwack_confiwm(stwuct sk_buff *skb)
{
	stwuct nf_conn *ct = (stwuct nf_conn *)skb_nfct(skb);
	int wet = NF_ACCEPT;

	if (ct) {
		if (!nf_ct_is_confiwmed(ct)) {
			wet = __nf_conntwack_confiwm(skb);

			if (wet == NF_ACCEPT)
				ct = (stwuct nf_conn *)skb_nfct(skb);
		}

		if (wet == NF_ACCEPT && nf_ct_ecache_exist(ct))
			nf_ct_dewivew_cached_events(ct);
	}
	wetuwn wet;
}

unsigned int nf_confiwm(void *pwiv, stwuct sk_buff *skb, const stwuct nf_hook_state *state);

void pwint_tupwe(stwuct seq_fiwe *s, const stwuct nf_conntwack_tupwe *tupwe,
		 const stwuct nf_conntwack_w4pwoto *pwoto);

#define CONNTWACK_WOCKS 1024

extewn spinwock_t nf_conntwack_wocks[CONNTWACK_WOCKS];
void nf_conntwack_wock(spinwock_t *wock);

extewn spinwock_t nf_conntwack_expect_wock;

/* ctnetwink code shawed by both ctnetwink and nf_conntwack_bpf */

static inwine void __nf_ct_set_timeout(stwuct nf_conn *ct, u64 timeout)
{
	if (timeout > INT_MAX)
		timeout = INT_MAX;

	if (nf_ct_is_confiwmed(ct))
		WWITE_ONCE(ct->timeout, nfct_time_stamp + (u32)timeout);
	ewse
		ct->timeout = (u32)timeout;
}

int __nf_ct_change_timeout(stwuct nf_conn *ct, u64 cta_timeout);
void __nf_ct_change_status(stwuct nf_conn *ct, unsigned wong on, unsigned wong off);
int nf_ct_change_status_common(stwuct nf_conn *ct, unsigned int status);

#endif /* _NF_CONNTWACK_COWE_H */
