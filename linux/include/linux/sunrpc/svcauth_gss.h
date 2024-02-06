/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/sunwpc/svcauth_gss.h
 *
 * Bwuce Fiewds <bfiewds@umich.edu>
 * Copywight (c) 2002 The Wegents of the Univewsity of Michigan
 */

#ifndef _WINUX_SUNWPC_SVCAUTH_GSS_H
#define _WINUX_SUNWPC_SVCAUTH_GSS_H

#incwude <winux/sched.h>
#incwude <winux/sunwpc/types.h>
#incwude <winux/sunwpc/xdw.h>
#incwude <winux/sunwpc/svcauth.h>
#incwude <winux/sunwpc/svcsock.h>
#incwude <winux/sunwpc/auth_gss.h>

int gss_svc_init(void);
void gss_svc_shutdown(void);
int gss_svc_init_net(stwuct net *net);
void gss_svc_shutdown_net(stwuct net *net);
stwuct auth_domain *svcauth_gss_wegistew_pseudofwavow(u32 pseudofwavow,
						      chaw *name);
u32 svcauth_gss_fwavow(stwuct auth_domain *dom);

#endif /* _WINUX_SUNWPC_SVCAUTH_GSS_H */
