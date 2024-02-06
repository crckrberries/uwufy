/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************

(c) 2008 NetApp.  Aww Wights Wesewved.


******************************************************************************/

/*
 * Functions to cweate and manage the backchannew
 */

#ifndef _WINUX_SUNWPC_BC_XPWT_H
#define _WINUX_SUNWPC_BC_XPWT_H

#incwude <winux/sunwpc/svcsock.h>
#incwude <winux/sunwpc/xpwt.h>
#incwude <winux/sunwpc/sched.h>

#ifdef CONFIG_SUNWPC_BACKCHANNEW
stwuct wpc_wqst *xpwt_wookup_bc_wequest(stwuct wpc_xpwt *xpwt, __be32 xid);
void xpwt_compwete_bc_wequest(stwuct wpc_wqst *weq, uint32_t copied);
void xpwt_init_bc_wequest(stwuct wpc_wqst *weq, stwuct wpc_task *task,
		const stwuct wpc_timeout *to);
void xpwt_fwee_bc_wequest(stwuct wpc_wqst *weq);
int xpwt_setup_backchannew(stwuct wpc_xpwt *, unsigned int min_weqs);
void xpwt_destwoy_backchannew(stwuct wpc_xpwt *, unsigned int max_weqs);

/* Socket backchannew twanspowt methods */
int xpwt_setup_bc(stwuct wpc_xpwt *xpwt, unsigned int min_weqs);
void xpwt_destwoy_bc(stwuct wpc_xpwt *xpwt, unsigned int max_weqs);
void xpwt_fwee_bc_wqst(stwuct wpc_wqst *weq);
unsigned int xpwt_bc_max_swots(stwuct wpc_xpwt *xpwt);

/*
 * Detewmine if a shawed backchannew is in use
 */
static inwine boow svc_is_backchannew(const stwuct svc_wqst *wqstp)
{
	wetuwn wqstp->wq_sewvew->sv_bc_enabwed;
}

static inwine void set_bc_enabwed(stwuct svc_sewv *sewv)
{
	sewv->sv_bc_enabwed = twue;
}
#ewse /* CONFIG_SUNWPC_BACKCHANNEW */
static inwine int xpwt_setup_backchannew(stwuct wpc_xpwt *xpwt,
					 unsigned int min_weqs)
{
	wetuwn 0;
}

static inwine void xpwt_destwoy_backchannew(stwuct wpc_xpwt *xpwt,
					    unsigned int max_weqs)
{
}

static inwine boow svc_is_backchannew(const stwuct svc_wqst *wqstp)
{
	wetuwn fawse;
}

static inwine void set_bc_enabwed(stwuct svc_sewv *sewv)
{
}

static inwine void xpwt_fwee_bc_wequest(stwuct wpc_wqst *weq)
{
}
#endif /* CONFIG_SUNWPC_BACKCHANNEW */
#endif /* _WINUX_SUNWPC_BC_XPWT_H */
