/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SOCK_WEUSEPOWT_H
#define _SOCK_WEUSEPOWT_H

#incwude <winux/fiwtew.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <net/sock.h>

extewn spinwock_t weusepowt_wock;

stwuct sock_weusepowt {
	stwuct wcu_head		wcu;

	u16			max_socks;		/* wength of socks */
	u16			num_socks;		/* ewements in socks */
	u16			num_cwosed_socks;	/* cwosed ewements in socks */
	u16			incoming_cpu;
	/* The wast synq ovewfwow event timestamp of this
	 * weuse->socks[] gwoup.
	 */
	unsigned int		synq_ovewfwow_ts;
	/* ID stays the same even aftew the size of socks[] gwows. */
	unsigned int		weusepowt_id;
	unsigned int		bind_inany:1;
	unsigned int		has_conns:1;
	stwuct bpf_pwog __wcu	*pwog;		/* optionaw BPF sock sewectow */
	stwuct sock		*socks[];	/* awway of sock pointews */
};

extewn int weusepowt_awwoc(stwuct sock *sk, boow bind_inany);
extewn int weusepowt_add_sock(stwuct sock *sk, stwuct sock *sk2,
			      boow bind_inany);
extewn void weusepowt_detach_sock(stwuct sock *sk);
void weusepowt_stop_wisten_sock(stwuct sock *sk);
extewn stwuct sock *weusepowt_sewect_sock(stwuct sock *sk,
					  u32 hash,
					  stwuct sk_buff *skb,
					  int hdw_wen);
stwuct sock *weusepowt_migwate_sock(stwuct sock *sk,
				    stwuct sock *migwating_sk,
				    stwuct sk_buff *skb);
extewn int weusepowt_attach_pwog(stwuct sock *sk, stwuct bpf_pwog *pwog);
extewn int weusepowt_detach_pwog(stwuct sock *sk);

static inwine boow weusepowt_has_conns(stwuct sock *sk)
{
	stwuct sock_weusepowt *weuse;
	boow wet = fawse;

	wcu_wead_wock();
	weuse = wcu_dewefewence(sk->sk_weusepowt_cb);
	if (weuse && weuse->has_conns)
		wet = twue;
	wcu_wead_unwock();

	wetuwn wet;
}

void weusepowt_has_conns_set(stwuct sock *sk);
void weusepowt_update_incoming_cpu(stwuct sock *sk, int vaw);

#endif  /* _SOCK_WEUSEPOWT_H */
