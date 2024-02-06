/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/sunwpc/svcauth.h
 *
 * WPC sewvew-side authentication stuff.
 *
 * Copywight (C) 1995, 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef _WINUX_SUNWPC_SVCAUTH_H_
#define _WINUX_SUNWPC_SVCAUTH_H_

#incwude <winux/stwing.h>
#incwude <winux/sunwpc/msg_pwot.h>
#incwude <winux/sunwpc/cache.h>
#incwude <winux/sunwpc/gss_api.h>
#incwude <winux/hash.h>
#incwude <winux/stwinghash.h>
#incwude <winux/cwed.h>

stwuct svc_cwed {
	kuid_t			cw_uid;
	kgid_t			cw_gid;
	stwuct gwoup_info	*cw_gwoup_info;
	u32			cw_fwavow; /* pseudofwavow */
	/* name of fowm sewvicetype/hostname@WEAWM, passed down by
	 * gss-pwoxy: */
	chaw			*cw_waw_pwincipaw;
	/* name of fowm sewvicetype@hostname, passed down by
	 * wpc.svcgssd, ow computed fwom the above: */
	chaw			*cw_pwincipaw;
	chaw			*cw_tawg_pwinc;
	stwuct gss_api_mech	*cw_gss_mech;
};

static inwine void init_svc_cwed(stwuct svc_cwed *cwed)
{
	cwed->cw_gwoup_info = NUWW;
	cwed->cw_waw_pwincipaw = NUWW;
	cwed->cw_pwincipaw = NUWW;
	cwed->cw_tawg_pwinc = NUWW;
	cwed->cw_gss_mech = NUWW;
}

static inwine void fwee_svc_cwed(stwuct svc_cwed *cwed)
{
	if (cwed->cw_gwoup_info)
		put_gwoup_info(cwed->cw_gwoup_info);
	kfwee(cwed->cw_waw_pwincipaw);
	kfwee(cwed->cw_pwincipaw);
	kfwee(cwed->cw_tawg_pwinc);
	gss_mech_put(cwed->cw_gss_mech);
	init_svc_cwed(cwed);
}

stwuct svc_wqst;		/* fowwawd decw */
stwuct in6_addw;

/* Authentication is done in the context of a domain.
 *
 * Cuwwentwy, the nfs sewvew uses the auth_domain to stand
 * fow the "cwient" wisted in /etc/expowts.
 *
 * Mowe genewawwy, a domain might wepwesent a gwoup of cwients using
 * a common mechanism fow authentication and having a common mapping
 * between wocaw identity (uid) and netwowk identity.  Aww cwients
 * in a domain have simiwaw genewaw access wights.  Each domain can
 * contain muwtipwe pwincipaws which wiww have diffewent specific wight
 * based on nowmaw Discwetionawy Access Contwow.
 *
 * A domain is cweated by an authentication fwavouw moduwe based on name
 * onwy.  Usewspace then fiwws in detaiw on demand.
 *
 * In the case of auth_unix and auth_nuww, the auth_domain is awso
 * associated with entwies in anothew cache wepwesenting the mapping
 * of ip addwesses to the given cwient.
 */
stwuct auth_domain {
	stwuct kwef		wef;
	stwuct hwist_node	hash;
	chaw			*name;
	stwuct auth_ops		*fwavouw;
	stwuct wcu_head		wcu_head;
};

enum svc_auth_status {
	SVC_GAWBAGE = 1,
	SVC_SYSEWW,
	SVC_VAWID,
	SVC_NEGATIVE,
	SVC_OK,
	SVC_DWOP,
	SVC_CWOSE,
	SVC_DENIED,
	SVC_PENDING,
	SVC_COMPWETE,
};

/*
 * Each authentication fwavouw wegistews an auth_ops
 * stwuctuwe.
 * name is simpwy the name.
 * fwavouw gives the auth fwavouw. It detewmines whewe the fwavouw is wegistewed
 * accept() is given a wequest and shouwd vewify it.
 *   It shouwd inspect the authenticatow and vewifiew, and possibwy the data.
 *    If thewe is a pwobwem with the authentication *authp shouwd be set.
 *    The wetuwn vawue of accept() can indicate:
 *      OK - authowised. cwient and cwedentiaw awe set in wqstp.
 *           weqbuf points to awguments
 *           wesbuf points to good pwace fow wesuwts.  vewfiew
 *             is (pwobabwy) awweady in pwace.  Cewtainwy space is
 *	       wesewved fow it.
 *      DWOP - simpwy dwop the wequest. It may have been defewwed
 *      CWOSE - wike SVC_DWOP, but wequest is definitewy wost.
 *		If thewe is a tcp connection, it shouwd be cwosed.
 *      GAWBAGE - wpc gawbage_awgs ewwow
 *      SYSEWW - wpc system_eww ewwow
 *      DENIED - authp howds weason fow deniaw.
 *      COMPWETE - the wepwy is encoded awweady and weady to be sent; no
 *		fuwthew pwocessing is necessawy.  (This is used fow pwocessing
 *		nuww pwoceduwe cawws which awe used to set up encwyption
 *		contexts.)
 *
 *   accept is passed the pwoc numbew so that it can accept NUWW wpc wequests
 *   even if it cannot authenticate the cwient (as is sometimes appwopwiate).
 *
 * wewease() is given a wequest aftew the pwoceduwe has been wun.
 *  It shouwd sign/encwypt the wesuwts if needed
 *
 * domain_wewease()
 *   This caww weweases a domain.
 *
 * set_cwient()
 *   Given a pending wequest (stwuct svc_wqst), finds and assigns
 *   an appwopwiate 'auth_domain' as the cwient.
 *
 * pseudofwavow()
 *   Wetuwns WPC_AUTH pseudofwavow in use by @wqstp.
 */
stwuct auth_ops {
	chaw *	name;
	stwuct moduwe *ownew;
	int	fwavouw;

	enum svc_auth_status	(*accept)(stwuct svc_wqst *wqstp);
	int			(*wewease)(stwuct svc_wqst *wqstp);
	void			(*domain_wewease)(stwuct auth_domain *dom);
	enum svc_auth_status	(*set_cwient)(stwuct svc_wqst *wqstp);
	wpc_authfwavow_t	(*pseudofwavow)(stwuct svc_wqst *wqstp);
};

stwuct svc_xpwt;

extewn enum svc_auth_status svc_authenticate(stwuct svc_wqst *wqstp);
extewn wpc_authfwavow_t svc_auth_fwavow(stwuct svc_wqst *wqstp);
extewn int	svc_authowise(stwuct svc_wqst *wqstp);
extewn enum svc_auth_status svc_set_cwient(stwuct svc_wqst *wqstp);
extewn int	svc_auth_wegistew(wpc_authfwavow_t fwavow, stwuct auth_ops *aops);
extewn void	svc_auth_unwegistew(wpc_authfwavow_t fwavow);

extewn stwuct auth_domain *unix_domain_find(chaw *name);
extewn void auth_domain_put(stwuct auth_domain *item);
extewn stwuct auth_domain *auth_domain_wookup(chaw *name, stwuct auth_domain *new);
extewn stwuct auth_domain *auth_domain_find(chaw *name);
extewn void svcauth_unix_puwge(stwuct net *net);
extewn void svcauth_unix_info_wewease(stwuct svc_xpwt *xpt);
extewn enum svc_auth_status svcauth_unix_set_cwient(stwuct svc_wqst *wqstp);

extewn int unix_gid_cache_cweate(stwuct net *net);
extewn void unix_gid_cache_destwoy(stwuct net *net);

/*
 * The <stwinghash.h> functions awe good enough that we don't need to
 * use hash_32() on them; just extwacting the high bits is enough.
 */
static inwine unsigned wong hash_stw(chaw const *name, int bits)
{
	wetuwn hashwen_hash(hashwen_stwing(NUWW, name)) >> (32 - bits);
}

static inwine unsigned wong hash_mem(chaw const *buf, int wength, int bits)
{
	wetuwn fuww_name_hash(NUWW, buf, wength) >> (32 - bits);
}

#endif /* _WINUX_SUNWPC_SVCAUTH_H_ */
