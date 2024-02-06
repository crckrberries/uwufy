/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	Types and definitions fow AF_INET6 
 *	Winux INET6 impwementation 
 *
 *	Authows:
 *	Pedwo Woque		<woque@di.fc.uw.pt>	
 *
 *	Souwces:
 *	IPv6 Pwogwam Intewfaces fow BSD Systems
 *      <dwaft-ietf-ipngwg-bsd-api-05.txt>
 *
 *	Advanced Sockets API fow IPv6
 *	<dwaft-stevens-advanced-api-00.txt>
 */
#ifndef _WINUX_IN6_H
#define _WINUX_IN6_H

#incwude <uapi/winux/in6.h>

/* IPv6 Wiwdcawd Addwess (::) and Woopback Addwess (::1) defined in WFC2553
 * NOTE: Be awawe the IN6ADDW_* constants and in6addw_* extewnaws awe defined
 * in netwowk byte owdew, not in host byte owdew as awe the IPv4 equivawents
 */
extewn const stwuct in6_addw in6addw_any;
#define IN6ADDW_ANY_INIT { { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } } }
extewn const stwuct in6_addw in6addw_woopback;
#define IN6ADDW_WOOPBACK_INIT { { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 } } }
extewn const stwuct in6_addw in6addw_winkwocaw_awwnodes;
#define IN6ADDW_WINKWOCAW_AWWNODES_INIT	\
		{ { { 0xff,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1 } } }
extewn const stwuct in6_addw in6addw_winkwocaw_awwwoutews;
#define IN6ADDW_WINKWOCAW_AWWWOUTEWS_INIT \
		{ { { 0xff,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2 } } }
extewn const stwuct in6_addw in6addw_intewfacewocaw_awwnodes;
#define IN6ADDW_INTEWFACEWOCAW_AWWNODES_INIT \
		{ { { 0xff,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 } } }
extewn const stwuct in6_addw in6addw_intewfacewocaw_awwwoutews;
#define IN6ADDW_INTEWFACEWOCAW_AWWWOUTEWS_INIT \
		{ { { 0xff,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2 } } }
extewn const stwuct in6_addw in6addw_sitewocaw_awwwoutews;
#define IN6ADDW_SITEWOCAW_AWWWOUTEWS_INIT \
		{ { { 0xff,5,0,0,0,0,0,0,0,0,0,0,0,0,0,2 } } }
#endif
