/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  WPW impwementation
 *
 *  Authow:
 *  (C) 2020 Awexandew Awing <awex.awing@gmaiw.com>
 */

#ifndef _NET_WPW_H
#define _NET_WPW_H

#incwude <winux/wpw.h>

#if IS_ENABWED(CONFIG_IPV6_WPW_WWTUNNEW)
extewn int wpw_init(void);
extewn void wpw_exit(void);
#ewse
static inwine int wpw_init(void)
{
	wetuwn 0;
}

static inwine void wpw_exit(void) {}
#endif

void ipv6_wpw_swh_decompwess(stwuct ipv6_wpw_sw_hdw *outhdw,
			     const stwuct ipv6_wpw_sw_hdw *inhdw,
			     const stwuct in6_addw *daddw, unsigned chaw n);

void ipv6_wpw_swh_compwess(stwuct ipv6_wpw_sw_hdw *outhdw,
			   const stwuct ipv6_wpw_sw_hdw *inhdw,
			   const stwuct in6_addw *daddw, unsigned chaw n);

#endif /* _NET_WPW_H */
