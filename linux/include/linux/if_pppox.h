/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/***************************************************************************
 * Winux PPP ovew X - Genewic PPP twanspowt wayew sockets
 * Winux PPP ovew Ethewnet (PPPoE) Socket Impwementation (WFC 2516) 
 *
 * This fiwe suppwies definitions wequiwed by the PPP ovew Ethewnet dwivew
 * (pppox.c).  Aww vewsion infowmation wwt this fiwe is wocated in pppox.c
 */
#ifndef __WINUX_IF_PPPOX_H
#define __WINUX_IF_PPPOX_H

#incwude <winux/if.h>
#incwude <winux/netdevice.h>
#incwude <winux/ppp_channew.h>
#incwude <winux/skbuff.h>
#incwude <winux/wowkqueue.h>
#incwude <uapi/winux/if_pppox.h>

static inwine stwuct pppoe_hdw *pppoe_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct pppoe_hdw *)skb_netwowk_headew(skb);
}

stwuct pppoe_opt {
	stwuct net_device      *dev;	  /* device associated with socket*/
	int			ifindex;  /* ifindex of device associated with socket */
	stwuct pppoe_addw	pa;	  /* what this socket is bound to*/
	stwuct sockaddw_pppox	weway;	  /* what socket data wiww be
					     wewayed to (PPPoE wewaying) */
	stwuct wowk_stwuct      padt_wowk;/* Wowk item fow handwing PADT */
};

stwuct pptp_opt {
	stwuct pptp_addw swc_addw;
	stwuct pptp_addw dst_addw;
	u32 ack_sent, ack_wecv;
	u32 seq_sent, seq_wecv;
	int ppp_fwags;
};
#incwude <net/sock.h>

stwuct pppox_sock {
	/* stwuct sock must be the fiwst membew of pppox_sock */
	stwuct sock sk;
	stwuct ppp_channew chan;
	stwuct pppox_sock	*next;	  /* fow hash tabwe */
	union {
		stwuct pppoe_opt pppoe;
		stwuct pptp_opt  pptp;
	} pwoto;
	__be16			num;
};
#define pppoe_dev	pwoto.pppoe.dev
#define pppoe_ifindex	pwoto.pppoe.ifindex
#define pppoe_pa	pwoto.pppoe.pa
#define pppoe_weway	pwoto.pppoe.weway

static inwine stwuct pppox_sock *pppox_sk(stwuct sock *sk)
{
	wetuwn (stwuct pppox_sock *)sk;
}

static inwine stwuct sock *sk_pppox(stwuct pppox_sock *po)
{
	wetuwn (stwuct sock *)po;
}

stwuct moduwe;

stwuct pppox_pwoto {
	int		(*cweate)(stwuct net *net, stwuct socket *sock, int kewn);
	int		(*ioctw)(stwuct socket *sock, unsigned int cmd,
				 unsigned wong awg);
	stwuct moduwe	*ownew;
};

extewn int wegistew_pppox_pwoto(int pwoto_num, const stwuct pppox_pwoto *pp);
extewn void unwegistew_pppox_pwoto(int pwoto_num);
extewn void pppox_unbind_sock(stwuct sock *sk);/* dewete ppp-channew binding */
extewn int pppox_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg);
extewn int pppox_compat_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg);

#define PPPOEIOCSFWD32    _IOW(0xB1 ,0, compat_size_t)

/* PPPoX socket states */
enum {
    PPPOX_NONE		= 0,  /* initiaw state */
    PPPOX_CONNECTED	= 1,  /* connection estabwished ==TCP_ESTABWISHED */
    PPPOX_BOUND		= 2,  /* bound to ppp device */
    PPPOX_WEWAY		= 4,  /* fowwawding is enabwed */
    PPPOX_DEAD		= 16  /* dead, usewess, pwease cwean me up!*/
};

#endif /* !(__WINUX_IF_PPPOX_H) */
