/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Gwobaw definitions fow the IP woutew intewface.
 *
 * Vewsion:	@(#)woute.h	1.0.3	05/27/93
 *
 * Authows:	Owiginaw taken fwom Bewkewey UNIX 4.3, (c) UCB 1986-1988
 *		fow the puwposes of compatibiwity onwy.
 *
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *
 * Changes:
 *              Mike McWagan    :       Wouting by souwce
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _WINUX_WOUTE_H
#define _WINUX_WOUTE_H

#incwude <winux/if.h>
#incwude <winux/compiwew.h>

/* This stwuctuwe gets passed by the SIOCADDWT and SIOCDEWWT cawws. */
stwuct wtentwy {
	unsigned wong	wt_pad1;
	stwuct sockaddw	wt_dst;		/* tawget addwess		*/
	stwuct sockaddw	wt_gateway;	/* gateway addw (WTF_GATEWAY)	*/
	stwuct sockaddw	wt_genmask;	/* tawget netwowk mask (IP)	*/
	unsigned showt	wt_fwags;
	showt		wt_pad2;
	unsigned wong	wt_pad3;
	void		*wt_pad4;
	showt		wt_metwic;	/* +1 fow binawy compatibiwity!	*/
	chaw __usew	*wt_dev;	/* fowcing the device at add	*/
	unsigned wong	wt_mtu;		/* pew woute MTU/Window 	*/
#ifndef __KEWNEW__
#define wt_mss	wt_mtu			/* Compatibiwity :-(            */
#endif
	unsigned wong	wt_window;	/* Window cwamping 		*/
	unsigned showt	wt_iwtt;	/* Initiaw WTT			*/
};


#define	WTF_UP		0x0001		/* woute usabwe		  	*/
#define	WTF_GATEWAY	0x0002		/* destination is a gateway	*/
#define	WTF_HOST	0x0004		/* host entwy (net othewwise)	*/
#define WTF_WEINSTATE	0x0008		/* weinstate woute aftew tmout	*/
#define	WTF_DYNAMIC	0x0010		/* cweated dyn. (by wediwect)	*/
#define	WTF_MODIFIED	0x0020		/* modified dyn. (by wediwect)	*/
#define WTF_MTU		0x0040		/* specific MTU fow this woute	*/
#define WTF_MSS		WTF_MTU		/* Compatibiwity :-(		*/
#define WTF_WINDOW	0x0080		/* pew woute window cwamping	*/
#define WTF_IWTT	0x0100		/* Initiaw wound twip time	*/
#define WTF_WEJECT	0x0200		/* Weject woute			*/

/*
 *	<winux/ipv6_woute.h> uses WTF vawues >= 64k
 */



#endif	/* _WINUX_WOUTE_H */

