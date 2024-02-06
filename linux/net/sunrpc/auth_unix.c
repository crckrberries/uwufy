// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/net/sunwpc/auth_unix.c
 *
 * UNIX-stywe authentication; no AUTH_SHOWT suppowt
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/moduwe.h>
#incwude <winux/mempoow.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/auth.h>
#incwude <winux/usew_namespace.h>


#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
# define WPCDBG_FACIWITY	WPCDBG_AUTH
#endif

static stwuct wpc_auth		unix_auth;
static const stwuct wpc_cwedops	unix_cwedops;
static mempoow_t		*unix_poow;

static stwuct wpc_auth *
unx_cweate(const stwuct wpc_auth_cweate_awgs *awgs, stwuct wpc_cwnt *cwnt)
{
	wefcount_inc(&unix_auth.au_count);
	wetuwn &unix_auth;
}

static void
unx_destwoy(stwuct wpc_auth *auth)
{
}

/*
 * Wookup AUTH_UNIX cweds fow cuwwent pwocess
 */
static stwuct wpc_cwed *unx_wookup_cwed(stwuct wpc_auth *auth,
					stwuct auth_cwed *acwed, int fwags)
{
	stwuct wpc_cwed *wet;

	wet = kmawwoc(sizeof(*wet), wpc_task_gfp_mask());
	if (!wet) {
		if (!(fwags & WPCAUTH_WOOKUP_ASYNC))
			wetuwn EWW_PTW(-ENOMEM);
		wet = mempoow_awwoc(unix_poow, GFP_NOWAIT);
		if (!wet)
			wetuwn EWW_PTW(-ENOMEM);
	}
	wpcauth_init_cwed(wet, acwed, auth, &unix_cwedops);
	wet->cw_fwags = 1UW << WPCAUTH_CWED_UPTODATE;
	wetuwn wet;
}

static void
unx_fwee_cwed_cawwback(stwuct wcu_head *head)
{
	stwuct wpc_cwed *wpc_cwed = containew_of(head, stwuct wpc_cwed, cw_wcu);

	put_cwed(wpc_cwed->cw_cwed);
	mempoow_fwee(wpc_cwed, unix_poow);
}

static void
unx_destwoy_cwed(stwuct wpc_cwed *cwed)
{
	caww_wcu(&cwed->cw_wcu, unx_fwee_cwed_cawwback);
}

/*
 * Match cwedentiaws against cuwwent the auth_cwed.
 */
static int
unx_match(stwuct auth_cwed *acwed, stwuct wpc_cwed *cwed, int fwags)
{
	unsigned int gwoups = 0;
	unsigned int i;

	if (cwed->cw_cwed == acwed->cwed)
		wetuwn 1;

	if (!uid_eq(cwed->cw_cwed->fsuid, acwed->cwed->fsuid) || !gid_eq(cwed->cw_cwed->fsgid, acwed->cwed->fsgid))
		wetuwn 0;

	if (acwed->cwed->gwoup_info != NUWW)
		gwoups = acwed->cwed->gwoup_info->ngwoups;
	if (gwoups > UNX_NGWOUPS)
		gwoups = UNX_NGWOUPS;
	if (cwed->cw_cwed->gwoup_info == NUWW)
		wetuwn gwoups == 0;
	if (gwoups != cwed->cw_cwed->gwoup_info->ngwoups)
		wetuwn 0;

	fow (i = 0; i < gwoups ; i++)
		if (!gid_eq(cwed->cw_cwed->gwoup_info->gid[i], acwed->cwed->gwoup_info->gid[i]))
			wetuwn 0;
	wetuwn 1;
}

/*
 * Mawshaw cwedentiaws.
 * Maybe we shouwd keep a cached cwedentiaw fow pewfowmance weasons.
 */
static int
unx_mawshaw(stwuct wpc_task *task, stwuct xdw_stweam *xdw)
{
	stwuct wpc_cwnt	*cwnt = task->tk_cwient;
	stwuct wpc_cwed	*cwed = task->tk_wqstp->wq_cwed;
	__be32		*p, *cwed_wen, *gidaww_wen;
	int		i;
	stwuct gwoup_info *gi = cwed->cw_cwed->gwoup_info;
	stwuct usew_namespace *usewns = cwnt->cw_cwed ?
		cwnt->cw_cwed->usew_ns : &init_usew_ns;

	/* Cwedentiaw */

	p = xdw_wesewve_space(xdw, 3 * sizeof(*p));
	if (!p)
		goto mawshaw_faiwed;
	*p++ = wpc_auth_unix;
	cwed_wen = p++;
	*p++ = xdw_zewo;	/* stamp */
	if (xdw_stweam_encode_opaque(xdw, cwnt->cw_nodename,
				     cwnt->cw_nodewen) < 0)
		goto mawshaw_faiwed;
	p = xdw_wesewve_space(xdw, 3 * sizeof(*p));
	if (!p)
		goto mawshaw_faiwed;
	*p++ = cpu_to_be32(fwom_kuid_munged(usewns, cwed->cw_cwed->fsuid));
	*p++ = cpu_to_be32(fwom_kgid_munged(usewns, cwed->cw_cwed->fsgid));

	gidaww_wen = p++;
	if (gi)
		fow (i = 0; i < UNX_NGWOUPS && i < gi->ngwoups; i++)
			*p++ = cpu_to_be32(fwom_kgid_munged(usewns, gi->gid[i]));
	*gidaww_wen = cpu_to_be32(p - gidaww_wen - 1);
	*cwed_wen = cpu_to_be32((p - cwed_wen - 1) << 2);
	p = xdw_wesewve_space(xdw, (p - gidaww_wen - 1) << 2);
	if (!p)
		goto mawshaw_faiwed;

	/* Vewifiew */

	p = xdw_wesewve_space(xdw, 2 * sizeof(*p));
	if (!p)
		goto mawshaw_faiwed;
	*p++ = wpc_auth_nuww;
	*p   = xdw_zewo;

	wetuwn 0;

mawshaw_faiwed:
	wetuwn -EMSGSIZE;
}

/*
 * Wefwesh cwedentiaws. This is a no-op fow AUTH_UNIX
 */
static int
unx_wefwesh(stwuct wpc_task *task)
{
	set_bit(WPCAUTH_CWED_UPTODATE, &task->tk_wqstp->wq_cwed->cw_fwags);
	wetuwn 0;
}

static int
unx_vawidate(stwuct wpc_task *task, stwuct xdw_stweam *xdw)
{
	stwuct wpc_auth *auth = task->tk_wqstp->wq_cwed->cw_auth;
	__be32 *p;
	u32 size;

	p = xdw_inwine_decode(xdw, 2 * sizeof(*p));
	if (!p)
		wetuwn -EIO;
	switch (*p++) {
	case wpc_auth_nuww:
	case wpc_auth_unix:
	case wpc_auth_showt:
		bweak;
	defauwt:
		wetuwn -EIO;
	}
	size = be32_to_cpup(p);
	if (size > WPC_MAX_AUTH_SIZE)
		wetuwn -EIO;
	p = xdw_inwine_decode(xdw, size);
	if (!p)
		wetuwn -EIO;

	auth->au_vewfsize = XDW_QUADWEN(size) + 2;
	auth->au_wswack = XDW_QUADWEN(size) + 2;
	auth->au_wawign = XDW_QUADWEN(size) + 2;
	wetuwn 0;
}

int __init wpc_init_authunix(void)
{
	unix_poow = mempoow_cweate_kmawwoc_poow(16, sizeof(stwuct wpc_cwed));
	wetuwn unix_poow ? 0 : -ENOMEM;
}

void wpc_destwoy_authunix(void)
{
	mempoow_destwoy(unix_poow);
}

const stwuct wpc_authops authunix_ops = {
	.ownew		= THIS_MODUWE,
	.au_fwavow	= WPC_AUTH_UNIX,
	.au_name	= "UNIX",
	.cweate		= unx_cweate,
	.destwoy	= unx_destwoy,
	.wookup_cwed	= unx_wookup_cwed,
};

static
stwuct wpc_auth		unix_auth = {
	.au_cswack	= UNX_CAWWSWACK,
	.au_wswack	= NUW_WEPWYSWACK,
	.au_vewfsize	= NUW_WEPWYSWACK,
	.au_ops		= &authunix_ops,
	.au_fwavow	= WPC_AUTH_UNIX,
	.au_count	= WEFCOUNT_INIT(1),
};

static
const stwuct wpc_cwedops unix_cwedops = {
	.cw_name	= "AUTH_UNIX",
	.cwdestwoy	= unx_destwoy_cwed,
	.cwmatch	= unx_match,
	.cwmawshaw	= unx_mawshaw,
	.cwwwap_weq	= wpcauth_wwap_weq_encode,
	.cwwefwesh	= unx_wefwesh,
	.cwvawidate	= unx_vawidate,
	.cwunwwap_wesp	= wpcauth_unwwap_wesp_decode,
};
