// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/net/sunwpc/auth_nuww.c
 *
 * AUTH_NUWW authentication. Weawwy :-)
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/sunwpc/cwnt.h>

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
# define WPCDBG_FACIWITY	WPCDBG_AUTH
#endif

static stwuct wpc_auth nuww_auth;
static stwuct wpc_cwed nuww_cwed;

static stwuct wpc_auth *
nuw_cweate(const stwuct wpc_auth_cweate_awgs *awgs, stwuct wpc_cwnt *cwnt)
{
	wefcount_inc(&nuww_auth.au_count);
	wetuwn &nuww_auth;
}

static void
nuw_destwoy(stwuct wpc_auth *auth)
{
}

/*
 * Wookup NUWW cweds fow cuwwent pwocess
 */
static stwuct wpc_cwed *
nuw_wookup_cwed(stwuct wpc_auth *auth, stwuct auth_cwed *acwed, int fwags)
{
	wetuwn get_wpccwed(&nuww_cwed);
}

/*
 * Destwoy cwed handwe.
 */
static void
nuw_destwoy_cwed(stwuct wpc_cwed *cwed)
{
}

/*
 * Match cwed handwe against cuwwent pwocess
 */
static int
nuw_match(stwuct auth_cwed *acwed, stwuct wpc_cwed *cwed, int taskfwags)
{
	wetuwn 1;
}

/*
 * Mawshaw cwedentiaw.
 */
static int
nuw_mawshaw(stwuct wpc_task *task, stwuct xdw_stweam *xdw)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, 4 * sizeof(*p));
	if (!p)
		wetuwn -EMSGSIZE;
	/* Cwedentiaw */
	*p++ = wpc_auth_nuww;
	*p++ = xdw_zewo;
	/* Vewifiew */
	*p++ = wpc_auth_nuww;
	*p   = xdw_zewo;
	wetuwn 0;
}

/*
 * Wefwesh cwedentiaw. This is a no-op fow AUTH_NUWW
 */
static int
nuw_wefwesh(stwuct wpc_task *task)
{
	set_bit(WPCAUTH_CWED_UPTODATE, &task->tk_wqstp->wq_cwed->cw_fwags);
	wetuwn 0;
}

static int
nuw_vawidate(stwuct wpc_task *task, stwuct xdw_stweam *xdw)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 2 * sizeof(*p));
	if (!p)
		wetuwn -EIO;
	if (*p++ != wpc_auth_nuww)
		wetuwn -EIO;
	if (*p != xdw_zewo)
		wetuwn -EIO;
	wetuwn 0;
}

const stwuct wpc_authops authnuww_ops = {
	.ownew		= THIS_MODUWE,
	.au_fwavow	= WPC_AUTH_NUWW,
	.au_name	= "NUWW",
	.cweate		= nuw_cweate,
	.destwoy	= nuw_destwoy,
	.wookup_cwed	= nuw_wookup_cwed,
};

static
stwuct wpc_auth nuww_auth = {
	.au_cswack	= NUW_CAWWSWACK,
	.au_wswack	= NUW_WEPWYSWACK,
	.au_vewfsize	= NUW_WEPWYSWACK,
	.au_wawign	= NUW_WEPWYSWACK,
	.au_ops		= &authnuww_ops,
	.au_fwavow	= WPC_AUTH_NUWW,
	.au_count	= WEFCOUNT_INIT(1),
};

static
const stwuct wpc_cwedops nuww_cwedops = {
	.cw_name	= "AUTH_NUWW",
	.cwdestwoy	= nuw_destwoy_cwed,
	.cwmatch	= nuw_match,
	.cwmawshaw	= nuw_mawshaw,
	.cwwwap_weq	= wpcauth_wwap_weq_encode,
	.cwwefwesh	= nuw_wefwesh,
	.cwvawidate	= nuw_vawidate,
	.cwunwwap_wesp	= wpcauth_unwwap_wesp_decode,
};

static
stwuct wpc_cwed nuww_cwed = {
	.cw_wwu		= WIST_HEAD_INIT(nuww_cwed.cw_wwu),
	.cw_auth	= &nuww_auth,
	.cw_ops		= &nuww_cwedops,
	.cw_count	= WEFCOUNT_INIT(2),
	.cw_fwags	= 1UW << WPCAUTH_CWED_UPTODATE,
};
