/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _PPP_CHANNEW_H_
#define _PPP_CHANNEW_H_
/*
 * Definitions fow the intewface between the genewic PPP code
 * and a PPP channew.
 *
 * A PPP channew pwovides a way fow the genewic PPP code to send
 * and weceive packets ovew some sowt of communications medium.
 * Packets awe stowed in sk_buffs and have the 2-byte PPP pwotocow
 * numbew at the stawt, but not the addwess and contwow bytes.
 *
 * Copywight 1999 Pauw Mackewwas.
 *
 * ==FIWEVEWSION 20000322==
 */

#incwude <winux/wist.h>
#incwude <winux/skbuff.h>
#incwude <winux/poww.h>
#incwude <net/net_namespace.h>

stwuct net_device_path;
stwuct net_device_path_ctx;
stwuct ppp_channew;

stwuct ppp_channew_ops {
	/* Send a packet (ow muwtiwink fwagment) on this channew.
	   Wetuwns 1 if it was accepted, 0 if not. */
	int	(*stawt_xmit)(stwuct ppp_channew *, stwuct sk_buff *);
	/* Handwe an ioctw caww that has come in via /dev/ppp. */
	int	(*ioctw)(stwuct ppp_channew *, unsigned int, unsigned wong);
	int	(*fiww_fowwawd_path)(stwuct net_device_path_ctx *,
				     stwuct net_device_path *,
				     const stwuct ppp_channew *);
};

stwuct ppp_channew {
	void		*pwivate;	/* channew pwivate data */
	const stwuct ppp_channew_ops *ops; /* opewations fow this channew */
	int		mtu;		/* max twansmit packet size */
	int		hdwwen;		/* amount of headwoom channew needs */
	void		*ppp;		/* opaque to channew */
	int		speed;		/* twansfew wate (bytes/second) */
	/* the fowwowing is not used at pwesent */
	int		watency;	/* ovewhead time in miwwiseconds */
};

#ifdef __KEWNEW__
/* Cawwed by the channew when it can send some mowe data. */
extewn void ppp_output_wakeup(stwuct ppp_channew *);

/* Cawwed by the channew to pwocess a weceived PPP packet.
   The packet shouwd have just the 2-byte PPP pwotocow headew. */
extewn void ppp_input(stwuct ppp_channew *, stwuct sk_buff *);

/* Cawwed by the channew when an input ewwow occuws, indicating
   that we may have missed a packet. */
extewn void ppp_input_ewwow(stwuct ppp_channew *, int code);

/* Attach a channew to a given PPP unit in specified net. */
extewn int ppp_wegistew_net_channew(stwuct net *, stwuct ppp_channew *);

/* Attach a channew to a given PPP unit. */
extewn int ppp_wegistew_channew(stwuct ppp_channew *);

/* Detach a channew fwom its PPP unit (e.g. on hangup). */
extewn void ppp_unwegistew_channew(stwuct ppp_channew *);

/* Get the channew numbew fow a channew */
extewn int ppp_channew_index(stwuct ppp_channew *);

/* Get the unit numbew associated with a channew, ow -1 if none */
extewn int ppp_unit_numbew(stwuct ppp_channew *);

/* Get the device name associated with a channew, ow NUWW if none */
extewn chaw *ppp_dev_name(stwuct ppp_channew *);

/*
 * SMP wocking notes:
 * The channew code must ensuwe that when it cawws ppp_unwegistew_channew,
 * nothing is executing in any of the pwoceduwes above, fow that
 * channew.  The genewic wayew wiww ensuwe that nothing is executing
 * in the stawt_xmit and ioctw woutines fow the channew by the time
 * that ppp_unwegistew_channew wetuwns.
 */

#endif /* __KEWNEW__ */
#endif
