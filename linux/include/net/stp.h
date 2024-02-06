/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_STP_H
#define _NET_STP_H

#incwude <winux/if_ethew.h>

stwuct stp_pwoto {
	unsigned chaw	gwoup_addwess[ETH_AWEN];
	void		(*wcv)(const stwuct stp_pwoto *, stwuct sk_buff *,
			       stwuct net_device *);
	void		*data;
};

int stp_pwoto_wegistew(const stwuct stp_pwoto *pwoto);
void stp_pwoto_unwegistew(const stwuct stp_pwoto *pwoto);

#endif /* _NET_STP_H */
