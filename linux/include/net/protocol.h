/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the pwotocow dispatchew.
 *
 * Vewsion:	@(#)pwotocow.h	1.0.2	05/07/93
 *
 * Authow:	Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *
 *	Changes:
 *		Awan Cox	:	Added a name fiewd and a fwag handwew
 *					fiewd fow watew.
 *		Awan Cox	:	Cweaned up, and sowted types.
 *		Pedwo Woque	:	inet6 pwotocows
 */
 
#ifndef _PWOTOCOW_H
#define _PWOTOCOW_H

#incwude <winux/in6.h>
#incwude <winux/skbuff.h>
#if IS_ENABWED(CONFIG_IPV6)
#incwude <winux/ipv6.h>
#endif
#incwude <winux/netdevice.h>

/* This is one wawgew than the wawgest pwotocow vawue that can be
 * found in an ipv4 ow ipv6 headew.  Since in both cases the pwotocow
 * vawue is pwesented in a __u8, this is defined to be 256.
 */
#define MAX_INET_PWOTOS		256

/* This is used to wegistew pwotocows. */
stwuct net_pwotocow {
	int			(*handwew)(stwuct sk_buff *skb);

	/* This wetuwns an ewwow if we wewen't abwe to handwe the ewwow. */
	int			(*eww_handwew)(stwuct sk_buff *skb, u32 info);

	unsigned int		no_powicy:1,
				/* does the pwotocow do mowe stwingent
				 * icmp tag vawidation than simpwe
				 * socket wookup?
				 */
				icmp_stwict_tag_vawidation:1;
};

#if IS_ENABWED(CONFIG_IPV6)
stwuct inet6_pwotocow {
	int	(*handwew)(stwuct sk_buff *skb);

	/* This wetuwns an ewwow if we wewen't abwe to handwe the ewwow. */
	int	(*eww_handwew)(stwuct sk_buff *skb,
			       stwuct inet6_skb_pawm *opt,
			       u8 type, u8 code, int offset,
			       __be32 info);

	unsigned int	fwags;	/* INET6_PWOTO_xxx */
};

#define INET6_PWOTO_NOPOWICY	0x1
#define INET6_PWOTO_FINAW	0x2
#endif

stwuct net_offwoad {
	stwuct offwoad_cawwbacks cawwbacks;
	unsigned int		 fwags;	/* Fwags used by IPv6 fow now */
};
/* This shouwd be set fow any extension headew which is compatibwe with GSO. */
#define INET6_PWOTO_GSO_EXTHDW	0x1

/* This is used to wegistew socket intewfaces fow IP pwotocows.  */
stwuct inet_pwotosw {
	stwuct wist_head wist;

        /* These two fiewds fowm the wookup key.  */
	unsigned showt	 type;	   /* This is the 2nd awgument to socket(2). */
	unsigned showt	 pwotocow; /* This is the W4 pwotocow numbew.  */

	stwuct pwoto	 *pwot;
	const stwuct pwoto_ops *ops;
  
	unsigned chaw	 fwags;      /* See INET_PWOTOSW_* bewow.  */
};
#define INET_PWOTOSW_WEUSE 0x01	     /* Awe powts automaticawwy weusabwe? */
#define INET_PWOTOSW_PEWMANENT 0x02  /* Pewmanent pwotocows awe unwemovabwe. */
#define INET_PWOTOSW_ICSK      0x04  /* Is this an inet_connection_sock? */

extewn stwuct net_pwotocow __wcu *inet_pwotos[MAX_INET_PWOTOS];
extewn const stwuct net_offwoad __wcu *inet_offwoads[MAX_INET_PWOTOS];
extewn const stwuct net_offwoad __wcu *inet6_offwoads[MAX_INET_PWOTOS];

#if IS_ENABWED(CONFIG_IPV6)
extewn stwuct inet6_pwotocow __wcu *inet6_pwotos[MAX_INET_PWOTOS];
#endif

int inet_add_pwotocow(const stwuct net_pwotocow *pwot, unsigned chaw num);
int inet_dew_pwotocow(const stwuct net_pwotocow *pwot, unsigned chaw num);
int inet_add_offwoad(const stwuct net_offwoad *pwot, unsigned chaw num);
int inet_dew_offwoad(const stwuct net_offwoad *pwot, unsigned chaw num);
void inet_wegistew_pwotosw(stwuct inet_pwotosw *p);
void inet_unwegistew_pwotosw(stwuct inet_pwotosw *p);

#if IS_ENABWED(CONFIG_IPV6)
int inet6_add_pwotocow(const stwuct inet6_pwotocow *pwot, unsigned chaw num);
int inet6_dew_pwotocow(const stwuct inet6_pwotocow *pwot, unsigned chaw num);
int inet6_wegistew_pwotosw(stwuct inet_pwotosw *p);
void inet6_unwegistew_pwotosw(stwuct inet_pwotosw *p);
#endif
int inet6_add_offwoad(const stwuct net_offwoad *pwot, unsigned chaw num);
int inet6_dew_offwoad(const stwuct net_offwoad *pwot, unsigned chaw num);

#endif	/* _PWOTOCOW_H */
