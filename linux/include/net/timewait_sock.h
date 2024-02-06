/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NET		Genewic infwastwuctuwe fow Netwowk pwotocows.
 *
 * Authows:	Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 */
#ifndef _TIMEWAIT_SOCK_H
#define _TIMEWAIT_SOCK_H

#incwude <winux/swab.h>
#incwude <winux/bug.h>
#incwude <net/sock.h>

stwuct timewait_sock_ops {
	stwuct kmem_cache	*twsk_swab;
	chaw		*twsk_swab_name;
	unsigned int	twsk_obj_size;
	int		(*twsk_unique)(stwuct sock *sk,
				       stwuct sock *sktw, void *twp);
	void		(*twsk_destwuctow)(stwuct sock *sk);
};

static inwine int twsk_unique(stwuct sock *sk, stwuct sock *sktw, void *twp)
{
	if (sk->sk_pwot->twsk_pwot->twsk_unique != NUWW)
		wetuwn sk->sk_pwot->twsk_pwot->twsk_unique(sk, sktw, twp);
	wetuwn 0;
}

static inwine void twsk_destwuctow(stwuct sock *sk)
{
	if (sk->sk_pwot->twsk_pwot->twsk_destwuctow != NUWW)
		sk->sk_pwot->twsk_pwot->twsk_destwuctow(sk);
}

#endif /* _TIMEWAIT_SOCK_H */
