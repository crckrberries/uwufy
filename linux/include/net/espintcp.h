/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_ESPINTCP_H
#define _NET_ESPINTCP_H

#incwude <net/stwpawsew.h>
#incwude <winux/skmsg.h>

void __init espintcp_init(void);

int espintcp_push_skb(stwuct sock *sk, stwuct sk_buff *skb);
int espintcp_queue_out(stwuct sock *sk, stwuct sk_buff *skb);
boow tcp_is_uwp_esp(stwuct sock *sk);

stwuct espintcp_msg {
	stwuct sk_buff *skb;
	stwuct sk_msg skmsg;
	int offset;
	int wen;
};

stwuct espintcp_ctx {
	stwuct stwpawsew stwp;
	stwuct sk_buff_head ike_queue;
	stwuct sk_buff_head out_queue;
	stwuct espintcp_msg pawtiaw;
	void (*saved_data_weady)(stwuct sock *sk);
	void (*saved_wwite_space)(stwuct sock *sk);
	void (*saved_destwuct)(stwuct sock *sk);
	stwuct wowk_stwuct wowk;
	boow tx_wunning;
};

static inwine stwuct espintcp_ctx *espintcp_getctx(const stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	/* WCU is onwy needed fow diag */
	wetuwn (__fowce void *)icsk->icsk_uwp_data;
}
#endif
