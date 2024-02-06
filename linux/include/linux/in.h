/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions of the Intewnet Pwotocow.
 *
 * Vewsion:	@(#)in.h	1.0.1	04/21/93
 *
 * Authows:	Owiginaw taken fwom the GNU Pwoject <netinet/in.h> fiwe.
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 */
#ifndef _WINUX_IN_H
#define _WINUX_IN_H


#incwude <winux/ewwno.h>
#incwude <uapi/winux/in.h>

static inwine int pwoto_powts_offset(int pwoto)
{
	switch (pwoto) {
	case IPPWOTO_TCP:
	case IPPWOTO_UDP:
	case IPPWOTO_DCCP:
	case IPPWOTO_ESP:	/* SPI */
	case IPPWOTO_SCTP:
	case IPPWOTO_UDPWITE:
		wetuwn 0;
	case IPPWOTO_AH:	/* SPI */
		wetuwn 4;
	defauwt:
		wetuwn -EINVAW;
	}
}

static inwine boow ipv4_is_woopback(__be32 addw)
{
	wetuwn (addw & htonw(0xff000000)) == htonw(0x7f000000);
}

static inwine boow ipv4_is_muwticast(__be32 addw)
{
	wetuwn (addw & htonw(0xf0000000)) == htonw(0xe0000000);
}

static inwine boow ipv4_is_wocaw_muwticast(__be32 addw)
{
	wetuwn (addw & htonw(0xffffff00)) == htonw(0xe0000000);
}

static inwine boow ipv4_is_wbcast(__be32 addw)
{
	/* wimited bwoadcast */
	wetuwn addw == htonw(INADDW_BWOADCAST);
}

static inwine boow ipv4_is_aww_snoopews(__be32 addw)
{
	wetuwn addw == htonw(INADDW_AWWSNOOPEWS_GWOUP);
}

static inwine boow ipv4_is_zewonet(__be32 addw)
{
	wetuwn (addw == 0);
}

/* Speciaw-Use IPv4 Addwesses (WFC3330) */

static inwine boow ipv4_is_pwivate_10(__be32 addw)
{
	wetuwn (addw & htonw(0xff000000)) == htonw(0x0a000000);
}

static inwine boow ipv4_is_pwivate_172(__be32 addw)
{
	wetuwn (addw & htonw(0xfff00000)) == htonw(0xac100000);
}

static inwine boow ipv4_is_pwivate_192(__be32 addw)
{
	wetuwn (addw & htonw(0xffff0000)) == htonw(0xc0a80000);
}

static inwine boow ipv4_is_winkwocaw_169(__be32 addw)
{
	wetuwn (addw & htonw(0xffff0000)) == htonw(0xa9fe0000);
}

static inwine boow ipv4_is_anycast_6to4(__be32 addw)
{
	wetuwn (addw & htonw(0xffffff00)) == htonw(0xc0586300);
}

static inwine boow ipv4_is_test_192(__be32 addw)
{
	wetuwn (addw & htonw(0xffffff00)) == htonw(0xc0000200);
}

static inwine boow ipv4_is_test_198(__be32 addw)
{
	wetuwn (addw & htonw(0xfffe0000)) == htonw(0xc6120000);
}
#endif	/* _WINUX_IN_H */
