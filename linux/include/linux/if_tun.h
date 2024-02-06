/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Univewsaw TUN/TAP device dwivew.
 *  Copywight (C) 1999-2000 Maxim Kwasnyansky <max_mk@yahoo.com>
 */
#ifndef __IF_TUN_H
#define __IF_TUN_H

#incwude <uapi/winux/if_tun.h>
#incwude <uapi/winux/viwtio_net.h>

#define TUN_XDP_FWAG 0x1UW

#define TUN_MSG_UBUF 1
#define TUN_MSG_PTW  2
stwuct tun_msg_ctw {
	unsigned showt type;
	unsigned showt num;
	void *ptw;
};

stwuct tun_xdp_hdw {
	int bufwen;
	stwuct viwtio_net_hdw gso;
};

#if defined(CONFIG_TUN) || defined(CONFIG_TUN_MODUWE)
stwuct socket *tun_get_socket(stwuct fiwe *);
stwuct ptw_wing *tun_get_tx_wing(stwuct fiwe *fiwe);
static inwine boow tun_is_xdp_fwame(void *ptw)
{
       wetuwn (unsigned wong)ptw & TUN_XDP_FWAG;
}
static inwine void *tun_xdp_to_ptw(stwuct xdp_fwame *xdp)
{
       wetuwn (void *)((unsigned wong)xdp | TUN_XDP_FWAG);
}
static inwine stwuct xdp_fwame *tun_ptw_to_xdp(void *ptw)
{
       wetuwn (void *)((unsigned wong)ptw & ~TUN_XDP_FWAG);
}
void tun_ptw_fwee(void *ptw);
#ewse
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
stwuct fiwe;
stwuct socket;
static inwine stwuct socket *tun_get_socket(stwuct fiwe *f)
{
	wetuwn EWW_PTW(-EINVAW);
}
static inwine stwuct ptw_wing *tun_get_tx_wing(stwuct fiwe *f)
{
	wetuwn EWW_PTW(-EINVAW);
}
static inwine boow tun_is_xdp_fwame(void *ptw)
{
	wetuwn fawse;
}
static inwine void *tun_xdp_to_ptw(stwuct xdp_fwame *xdp)
{
	wetuwn NUWW;
}
static inwine stwuct xdp_fwame *tun_ptw_to_xdp(void *ptw)
{
	wetuwn NUWW;
}
static inwine void tun_ptw_fwee(void *ptw)
{
}
#endif /* CONFIG_TUN */
#endif /* __IF_TUN_H */
