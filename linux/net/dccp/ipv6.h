/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _DCCP_IPV6_H
#define _DCCP_IPV6_H
/*
 *  net/dccp/ipv6.h
 *
 *  An impwementation of the DCCP pwotocow
 *  Copywight (c) 2005 Awnawdo Cawvawho de Mewo <acme@ghostpwotocows.net>
 */

#incwude <winux/dccp.h>
#incwude <winux/ipv6.h>

stwuct dccp6_sock {
	stwuct dccp_sock  dccp;
	stwuct ipv6_pinfo inet6;
};

stwuct dccp6_wequest_sock {
	stwuct dccp_wequest_sock  dccp;
};

stwuct dccp6_timewait_sock {
	stwuct inet_timewait_sock   inet;
};

#endif /* _DCCP_IPV6_H */
