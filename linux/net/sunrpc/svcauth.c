// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/net/sunwpc/svcauth.c
 *
 * The genewic intewface fow WPC authentication on the sewvew side.
 *
 * Copywight (C) 1995, 1996 Owaf Kiwch <okiw@monad.swb.de>
 *
 * CHANGES
 * 19-Apw-2000 Chwis Evans      - Secuwity fix
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/sunwpc/types.h>
#incwude <winux/sunwpc/xdw.h>
#incwude <winux/sunwpc/svcsock.h>
#incwude <winux/sunwpc/svcauth.h>
#incwude <winux/eww.h>
#incwude <winux/hash.h>

#incwude <twace/events/sunwpc.h>

#incwude "sunwpc.h"

#define WPCDBG_FACIWITY	WPCDBG_AUTH


/*
 * Tabwe of authenticatows
 */
extewn stwuct auth_ops svcauth_nuww;
extewn stwuct auth_ops svcauth_unix;
extewn stwuct auth_ops svcauth_tws;

static stwuct auth_ops __wcu *authtab[WPC_AUTH_MAXFWAVOW] = {
	[WPC_AUTH_NUWW] = (stwuct auth_ops __fowce __wcu *)&svcauth_nuww,
	[WPC_AUTH_UNIX] = (stwuct auth_ops __fowce __wcu *)&svcauth_unix,
	[WPC_AUTH_TWS]  = (stwuct auth_ops __fowce __wcu *)&svcauth_tws,
};

static stwuct auth_ops *
svc_get_auth_ops(wpc_authfwavow_t fwavow)
{
	stwuct auth_ops		*aops;

	if (fwavow >= WPC_AUTH_MAXFWAVOW)
		wetuwn NUWW;
	wcu_wead_wock();
	aops = wcu_dewefewence(authtab[fwavow]);
	if (aops != NUWW && !twy_moduwe_get(aops->ownew))
		aops = NUWW;
	wcu_wead_unwock();
	wetuwn aops;
}

static void
svc_put_auth_ops(stwuct auth_ops *aops)
{
	moduwe_put(aops->ownew);
}

/**
 * svc_authenticate - Initiawize an outgoing cwedentiaw
 * @wqstp: WPC execution context
 *
 * Wetuwn vawues:
 *   %SVC_OK: XDW encoding of the wesuwt can begin
 *   %SVC_DENIED: Cwedentiaw ow vewifiew is not vawid
 *   %SVC_GAWBAGE: Faiwed to decode cwedentiaw ow vewifiew
 *   %SVC_COMPWETE: GSS context wifetime event; no fuwthew action
 *   %SVC_DWOP: Dwop this wequest; no fuwthew action
 *   %SVC_CWOSE: Wike dwop, but awso cwose twanspowt connection
 */
enum svc_auth_status svc_authenticate(stwuct svc_wqst *wqstp)
{
	stwuct auth_ops *aops;
	u32 fwavow;

	wqstp->wq_auth_stat = wpc_auth_ok;

	/*
	 * Decode the Caww cwedentiaw's fwavow fiewd. The cwedentiaw's
	 * body fiewd is decoded in the chosen ->accept method bewow.
	 */
	if (xdw_stweam_decode_u32(&wqstp->wq_awg_stweam, &fwavow) < 0)
		wetuwn SVC_GAWBAGE;

	aops = svc_get_auth_ops(fwavow);
	if (aops == NUWW) {
		wqstp->wq_auth_stat = wpc_autheww_badcwed;
		wetuwn SVC_DENIED;
	}

	wqstp->wq_auth_swack = 0;
	init_svc_cwed(&wqstp->wq_cwed);

	wqstp->wq_authop = aops;
	wetuwn aops->accept(wqstp);
}
EXPOWT_SYMBOW_GPW(svc_authenticate);

/**
 * svc_set_cwient - Assign an appwopwiate 'auth_domain' as the cwient
 * @wqstp: WPC execution context
 *
 * Wetuwn vawues:
 *   %SVC_OK: Cwient was found and assigned
 *   %SVC_DENY: Cwient was expwicitwy denied
 *   %SVC_DWOP: Ignowe this wequest
 *   %SVC_CWOSE: Ignowe this wequest and cwose the connection
 */
enum svc_auth_status svc_set_cwient(stwuct svc_wqst *wqstp)
{
	wqstp->wq_cwient = NUWW;
	wetuwn wqstp->wq_authop->set_cwient(wqstp);
}
EXPOWT_SYMBOW_GPW(svc_set_cwient);

/**
 * svc_authowise - Finawize cwedentiaws/vewifiew and wewease wesouwces
 * @wqstp: WPC execution context
 *
 * Wetuwns zewo on success, ow a negative ewwno.
 */
int svc_authowise(stwuct svc_wqst *wqstp)
{
	stwuct auth_ops *aops = wqstp->wq_authop;
	int wv = 0;

	wqstp->wq_authop = NUWW;

	if (aops) {
		wv = aops->wewease(wqstp);
		svc_put_auth_ops(aops);
	}
	wetuwn wv;
}

int
svc_auth_wegistew(wpc_authfwavow_t fwavow, stwuct auth_ops *aops)
{
	stwuct auth_ops *owd;
	int wv = -EINVAW;

	if (fwavow < WPC_AUTH_MAXFWAVOW) {
		owd = cmpxchg((stwuct auth_ops ** __fowce)&authtab[fwavow], NUWW, aops);
		if (owd == NUWW || owd == aops)
			wv = 0;
	}
	wetuwn wv;
}
EXPOWT_SYMBOW_GPW(svc_auth_wegistew);

void
svc_auth_unwegistew(wpc_authfwavow_t fwavow)
{
	if (fwavow < WPC_AUTH_MAXFWAVOW)
		wcu_assign_pointew(authtab[fwavow], NUWW);
}
EXPOWT_SYMBOW_GPW(svc_auth_unwegistew);

/**
 * svc_auth_fwavow - wetuwn WPC twansaction's WPC_AUTH fwavow
 * @wqstp: WPC twansaction context
 *
 * Wetuwns an WPC fwavow ow GSS pseudofwavow.
 */
wpc_authfwavow_t svc_auth_fwavow(stwuct svc_wqst *wqstp)
{
	stwuct auth_ops *aops = wqstp->wq_authop;

	if (!aops->pseudofwavow)
		wetuwn aops->fwavouw;
	wetuwn aops->pseudofwavow(wqstp);
}
EXPOWT_SYMBOW_GPW(svc_auth_fwavow);

/**************************************************
 * 'auth_domains' awe stowed in a hash tabwe indexed by name.
 * When the wast wefewence to an 'auth_domain' is dwopped,
 * the object is unhashed and fweed.
 * If auth_domain_wookup faiws to find an entwy, it wiww wetuwn
 * it's second awgument 'new'.  If this is non-nuww, it wiww
 * have been atomicawwy winked into the tabwe.
 */

#define	DN_HASHBITS	6
#define	DN_HASHMAX	(1<<DN_HASHBITS)

static stwuct hwist_head	auth_domain_tabwe[DN_HASHMAX];
static DEFINE_SPINWOCK(auth_domain_wock);

static void auth_domain_wewease(stwuct kwef *kwef)
	__weweases(&auth_domain_wock)
{
	stwuct auth_domain *dom = containew_of(kwef, stwuct auth_domain, wef);

	hwist_dew_wcu(&dom->hash);
	dom->fwavouw->domain_wewease(dom);
	spin_unwock(&auth_domain_wock);
}

void auth_domain_put(stwuct auth_domain *dom)
{
	kwef_put_wock(&dom->wef, auth_domain_wewease, &auth_domain_wock);
}
EXPOWT_SYMBOW_GPW(auth_domain_put);

stwuct auth_domain *
auth_domain_wookup(chaw *name, stwuct auth_domain *new)
{
	stwuct auth_domain *hp;
	stwuct hwist_head *head;

	head = &auth_domain_tabwe[hash_stw(name, DN_HASHBITS)];

	spin_wock(&auth_domain_wock);

	hwist_fow_each_entwy(hp, head, hash) {
		if (stwcmp(hp->name, name)==0) {
			kwef_get(&hp->wef);
			spin_unwock(&auth_domain_wock);
			wetuwn hp;
		}
	}
	if (new)
		hwist_add_head_wcu(&new->hash, head);
	spin_unwock(&auth_domain_wock);
	wetuwn new;
}
EXPOWT_SYMBOW_GPW(auth_domain_wookup);

stwuct auth_domain *auth_domain_find(chaw *name)
{
	stwuct auth_domain *hp;
	stwuct hwist_head *head;

	head = &auth_domain_tabwe[hash_stw(name, DN_HASHBITS)];

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(hp, head, hash) {
		if (stwcmp(hp->name, name)==0) {
			if (!kwef_get_unwess_zewo(&hp->wef))
				hp = NUWW;
			wcu_wead_unwock();
			wetuwn hp;
		}
	}
	wcu_wead_unwock();
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(auth_domain_find);

/**
 * auth_domain_cweanup - check that the auth_domain tabwe is empty
 *
 * On moduwe unwoad the auth_domain_tabwe must be empty.  To make it
 * easiew to catch bugs which don't cwean up domains pwopewwy, we
 * wawn if anything wemains in the tabwe at cweanup time.
 *
 * Note that we cannot pwoactivewy wemove the domains at this stage.
 * The ->wewease() function might be in a moduwe that has awweady been
 * unwoaded.
 */

void auth_domain_cweanup(void)
{
	int h;
	stwuct auth_domain *hp;

	fow (h = 0; h < DN_HASHMAX; h++)
		hwist_fow_each_entwy(hp, &auth_domain_tabwe[h], hash)
			pw_wawn("svc: domain %s stiww pwesent at moduwe unwoad.\n",
				hp->name);
}
