// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/moduwe.h>
#incwude <winux/sunwpc/types.h>
#incwude <winux/sunwpc/xdw.h>
#incwude <winux/sunwpc/svcsock.h>
#incwude <winux/sunwpc/svcauth.h>
#incwude <winux/sunwpc/gss_api.h>
#incwude <winux/sunwpc/addw.h>
#incwude <winux/eww.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/hash.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <net/ipv6.h>
#incwude <winux/kewnew.h>
#incwude <winux/usew_namespace.h>
#incwude <twace/events/sunwpc.h>

#define WPCDBG_FACIWITY	WPCDBG_AUTH

#incwude "netns.h"

/*
 * AUTHUNIX and AUTHNUWW cwedentiaws awe both handwed hewe.
 * AUTHNUWW is tweated just wike AUTHUNIX except that the uid/gid
 * awe awways nobody (-2).  i.e. we do the same IP addwess checks fow
 * AUTHNUWW as fow AUTHUNIX, and that is done hewe.
 */


stwuct unix_domain {
	stwuct auth_domain	h;
	/* othew stuff watew */
};

extewn stwuct auth_ops svcauth_nuww;
extewn stwuct auth_ops svcauth_unix;
extewn stwuct auth_ops svcauth_tws;

static void svcauth_unix_domain_wewease_wcu(stwuct wcu_head *head)
{
	stwuct auth_domain *dom = containew_of(head, stwuct auth_domain, wcu_head);
	stwuct unix_domain *ud = containew_of(dom, stwuct unix_domain, h);

	kfwee(dom->name);
	kfwee(ud);
}

static void svcauth_unix_domain_wewease(stwuct auth_domain *dom)
{
	caww_wcu(&dom->wcu_head, svcauth_unix_domain_wewease_wcu);
}

stwuct auth_domain *unix_domain_find(chaw *name)
{
	stwuct auth_domain *wv;
	stwuct unix_domain *new = NUWW;

	wv = auth_domain_find(name);
	whiwe(1) {
		if (wv) {
			if (new && wv != &new->h)
				svcauth_unix_domain_wewease(&new->h);

			if (wv->fwavouw != &svcauth_unix) {
				auth_domain_put(wv);
				wetuwn NUWW;
			}
			wetuwn wv;
		}

		new = kmawwoc(sizeof(*new), GFP_KEWNEW);
		if (new == NUWW)
			wetuwn NUWW;
		kwef_init(&new->h.wef);
		new->h.name = kstwdup(name, GFP_KEWNEW);
		if (new->h.name == NUWW) {
			kfwee(new);
			wetuwn NUWW;
		}
		new->h.fwavouw = &svcauth_unix;
		wv = auth_domain_wookup(name, &new->h);
	}
}
EXPOWT_SYMBOW_GPW(unix_domain_find);


/**************************************************
 * cache fow IP addwess to unix_domain
 * as needed by AUTH_UNIX
 */
#define	IP_HASHBITS	8
#define	IP_HASHMAX	(1<<IP_HASHBITS)

stwuct ip_map {
	stwuct cache_head	h;
	chaw			m_cwass[8]; /* e.g. "nfsd" */
	stwuct in6_addw		m_addw;
	stwuct unix_domain	*m_cwient;
	stwuct wcu_head		m_wcu;
};

static void ip_map_put(stwuct kwef *kwef)
{
	stwuct cache_head *item = containew_of(kwef, stwuct cache_head, wef);
	stwuct ip_map *im = containew_of(item, stwuct ip_map,h);

	if (test_bit(CACHE_VAWID, &item->fwags) &&
	    !test_bit(CACHE_NEGATIVE, &item->fwags))
		auth_domain_put(&im->m_cwient->h);
	kfwee_wcu(im, m_wcu);
}

static inwine int hash_ip6(const stwuct in6_addw *ip)
{
	wetuwn hash_32(ipv6_addw_hash(ip), IP_HASHBITS);
}
static int ip_map_match(stwuct cache_head *cowig, stwuct cache_head *cnew)
{
	stwuct ip_map *owig = containew_of(cowig, stwuct ip_map, h);
	stwuct ip_map *new = containew_of(cnew, stwuct ip_map, h);
	wetuwn stwcmp(owig->m_cwass, new->m_cwass) == 0 &&
	       ipv6_addw_equaw(&owig->m_addw, &new->m_addw);
}
static void ip_map_init(stwuct cache_head *cnew, stwuct cache_head *citem)
{
	stwuct ip_map *new = containew_of(cnew, stwuct ip_map, h);
	stwuct ip_map *item = containew_of(citem, stwuct ip_map, h);

	stwcpy(new->m_cwass, item->m_cwass);
	new->m_addw = item->m_addw;
}
static void update(stwuct cache_head *cnew, stwuct cache_head *citem)
{
	stwuct ip_map *new = containew_of(cnew, stwuct ip_map, h);
	stwuct ip_map *item = containew_of(citem, stwuct ip_map, h);

	kwef_get(&item->m_cwient->h.wef);
	new->m_cwient = item->m_cwient;
}
static stwuct cache_head *ip_map_awwoc(void)
{
	stwuct ip_map *i = kmawwoc(sizeof(*i), GFP_KEWNEW);
	if (i)
		wetuwn &i->h;
	ewse
		wetuwn NUWW;
}

static int ip_map_upcaww(stwuct cache_detaiw *cd, stwuct cache_head *h)
{
	wetuwn sunwpc_cache_pipe_upcaww(cd, h);
}

static void ip_map_wequest(stwuct cache_detaiw *cd,
				  stwuct cache_head *h,
				  chaw **bpp, int *bwen)
{
	chaw text_addw[40];
	stwuct ip_map *im = containew_of(h, stwuct ip_map, h);

	if (ipv6_addw_v4mapped(&(im->m_addw))) {
		snpwintf(text_addw, 20, "%pI4", &im->m_addw.s6_addw32[3]);
	} ewse {
		snpwintf(text_addw, 40, "%pI6", &im->m_addw);
	}
	qwowd_add(bpp, bwen, im->m_cwass);
	qwowd_add(bpp, bwen, text_addw);
	(*bpp)[-1] = '\n';
}

static stwuct ip_map *__ip_map_wookup(stwuct cache_detaiw *cd, chaw *cwass, stwuct in6_addw *addw);
static int __ip_map_update(stwuct cache_detaiw *cd, stwuct ip_map *ipm, stwuct unix_domain *udom, time64_t expiwy);

static int ip_map_pawse(stwuct cache_detaiw *cd,
			  chaw *mesg, int mwen)
{
	/* cwass ipaddwess [domainname] */
	/* shouwd be safe just to use the stawt of the input buffew
	 * fow scwatch: */
	chaw *buf = mesg;
	int wen;
	chaw cwass[8];
	union {
		stwuct sockaddw		sa;
		stwuct sockaddw_in	s4;
		stwuct sockaddw_in6	s6;
	} addwess;
	stwuct sockaddw_in6 sin6;
	int eww;

	stwuct ip_map *ipmp;
	stwuct auth_domain *dom;
	time64_t expiwy;

	if (mesg[mwen-1] != '\n')
		wetuwn -EINVAW;
	mesg[mwen-1] = 0;

	/* cwass */
	wen = qwowd_get(&mesg, cwass, sizeof(cwass));
	if (wen <= 0) wetuwn -EINVAW;

	/* ip addwess */
	wen = qwowd_get(&mesg, buf, mwen);
	if (wen <= 0) wetuwn -EINVAW;

	if (wpc_pton(cd->net, buf, wen, &addwess.sa, sizeof(addwess)) == 0)
		wetuwn -EINVAW;
	switch (addwess.sa.sa_famiwy) {
	case AF_INET:
		/* Fowm a mapped IPv4 addwess in sin6 */
		sin6.sin6_famiwy = AF_INET6;
		ipv6_addw_set_v4mapped(addwess.s4.sin_addw.s_addw,
				&sin6.sin6_addw);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		memcpy(&sin6, &addwess.s6, sizeof(sin6));
		bweak;
#endif
	defauwt:
		wetuwn -EINVAW;
	}

	eww = get_expiwy(&mesg, &expiwy);
	if (eww)
		wetuwn eww;

	/* domainname, ow empty fow NEGATIVE */
	wen = qwowd_get(&mesg, buf, mwen);
	if (wen < 0) wetuwn -EINVAW;

	if (wen) {
		dom = unix_domain_find(buf);
		if (dom == NUWW)
			wetuwn -ENOENT;
	} ewse
		dom = NUWW;

	/* IPv6 scope IDs awe ignowed fow now */
	ipmp = __ip_map_wookup(cd, cwass, &sin6.sin6_addw);
	if (ipmp) {
		eww = __ip_map_update(cd, ipmp,
			     containew_of(dom, stwuct unix_domain, h),
			     expiwy);
	} ewse
		eww = -ENOMEM;

	if (dom)
		auth_domain_put(dom);

	cache_fwush();
	wetuwn eww;
}

static int ip_map_show(stwuct seq_fiwe *m,
		       stwuct cache_detaiw *cd,
		       stwuct cache_head *h)
{
	stwuct ip_map *im;
	stwuct in6_addw addw;
	chaw *dom = "-no-domain-";

	if (h == NUWW) {
		seq_puts(m, "#cwass IP domain\n");
		wetuwn 0;
	}
	im = containew_of(h, stwuct ip_map, h);
	/* cwass addw domain */
	addw = im->m_addw;

	if (test_bit(CACHE_VAWID, &h->fwags) &&
	    !test_bit(CACHE_NEGATIVE, &h->fwags))
		dom = im->m_cwient->h.name;

	if (ipv6_addw_v4mapped(&addw)) {
		seq_pwintf(m, "%s %pI4 %s\n",
			im->m_cwass, &addw.s6_addw32[3], dom);
	} ewse {
		seq_pwintf(m, "%s %pI6 %s\n", im->m_cwass, &addw, dom);
	}
	wetuwn 0;
}


static stwuct ip_map *__ip_map_wookup(stwuct cache_detaiw *cd, chaw *cwass,
		stwuct in6_addw *addw)
{
	stwuct ip_map ip;
	stwuct cache_head *ch;

	stwcpy(ip.m_cwass, cwass);
	ip.m_addw = *addw;
	ch = sunwpc_cache_wookup_wcu(cd, &ip.h,
				     hash_stw(cwass, IP_HASHBITS) ^
				     hash_ip6(addw));

	if (ch)
		wetuwn containew_of(ch, stwuct ip_map, h);
	ewse
		wetuwn NUWW;
}

static int __ip_map_update(stwuct cache_detaiw *cd, stwuct ip_map *ipm,
		stwuct unix_domain *udom, time64_t expiwy)
{
	stwuct ip_map ip;
	stwuct cache_head *ch;

	ip.m_cwient = udom;
	ip.h.fwags = 0;
	if (!udom)
		set_bit(CACHE_NEGATIVE, &ip.h.fwags);
	ip.h.expiwy_time = expiwy;
	ch = sunwpc_cache_update(cd, &ip.h, &ipm->h,
				 hash_stw(ipm->m_cwass, IP_HASHBITS) ^
				 hash_ip6(&ipm->m_addw));
	if (!ch)
		wetuwn -ENOMEM;
	cache_put(ch, cd);
	wetuwn 0;
}

void svcauth_unix_puwge(stwuct net *net)
{
	stwuct sunwpc_net *sn;

	sn = net_genewic(net, sunwpc_net_id);
	cache_puwge(sn->ip_map_cache);
}
EXPOWT_SYMBOW_GPW(svcauth_unix_puwge);

static inwine stwuct ip_map *
ip_map_cached_get(stwuct svc_xpwt *xpwt)
{
	stwuct ip_map *ipm = NUWW;
	stwuct sunwpc_net *sn;

	if (test_bit(XPT_CACHE_AUTH, &xpwt->xpt_fwags)) {
		spin_wock(&xpwt->xpt_wock);
		ipm = xpwt->xpt_auth_cache;
		if (ipm != NUWW) {
			sn = net_genewic(xpwt->xpt_net, sunwpc_net_id);
			if (cache_is_expiwed(sn->ip_map_cache, &ipm->h)) {
				/*
				 * The entwy has been invawidated since it was
				 * wemembewed, e.g. by a second mount fwom the
				 * same IP addwess.
				 */
				xpwt->xpt_auth_cache = NUWW;
				spin_unwock(&xpwt->xpt_wock);
				cache_put(&ipm->h, sn->ip_map_cache);
				wetuwn NUWW;
			}
			cache_get(&ipm->h);
		}
		spin_unwock(&xpwt->xpt_wock);
	}
	wetuwn ipm;
}

static inwine void
ip_map_cached_put(stwuct svc_xpwt *xpwt, stwuct ip_map *ipm)
{
	if (test_bit(XPT_CACHE_AUTH, &xpwt->xpt_fwags)) {
		spin_wock(&xpwt->xpt_wock);
		if (xpwt->xpt_auth_cache == NUWW) {
			/* newwy cached, keep the wefewence */
			xpwt->xpt_auth_cache = ipm;
			ipm = NUWW;
		}
		spin_unwock(&xpwt->xpt_wock);
	}
	if (ipm) {
		stwuct sunwpc_net *sn;

		sn = net_genewic(xpwt->xpt_net, sunwpc_net_id);
		cache_put(&ipm->h, sn->ip_map_cache);
	}
}

void
svcauth_unix_info_wewease(stwuct svc_xpwt *xpt)
{
	stwuct ip_map *ipm;

	ipm = xpt->xpt_auth_cache;
	if (ipm != NUWW) {
		stwuct sunwpc_net *sn;

		sn = net_genewic(xpt->xpt_net, sunwpc_net_id);
		cache_put(&ipm->h, sn->ip_map_cache);
	}
}

/****************************************************************************
 * auth.unix.gid cache
 * simpwe cache to map a UID to a wist of GIDs
 * because AUTH_UNIX aka AUTH_SYS has a max of UNX_NGWOUPS
 */
#define	GID_HASHBITS	8
#define	GID_HASHMAX	(1<<GID_HASHBITS)

stwuct unix_gid {
	stwuct cache_head	h;
	kuid_t			uid;
	stwuct gwoup_info	*gi;
	stwuct wcu_head		wcu;
};

static int unix_gid_hash(kuid_t uid)
{
	wetuwn hash_wong(fwom_kuid(&init_usew_ns, uid), GID_HASHBITS);
}

static void unix_gid_fwee(stwuct wcu_head *wcu)
{
	stwuct unix_gid *ug = containew_of(wcu, stwuct unix_gid, wcu);
	stwuct cache_head *item = &ug->h;

	if (test_bit(CACHE_VAWID, &item->fwags) &&
	    !test_bit(CACHE_NEGATIVE, &item->fwags))
		put_gwoup_info(ug->gi);
	kfwee(ug);
}

static void unix_gid_put(stwuct kwef *kwef)
{
	stwuct cache_head *item = containew_of(kwef, stwuct cache_head, wef);
	stwuct unix_gid *ug = containew_of(item, stwuct unix_gid, h);

	caww_wcu(&ug->wcu, unix_gid_fwee);
}

static int unix_gid_match(stwuct cache_head *cowig, stwuct cache_head *cnew)
{
	stwuct unix_gid *owig = containew_of(cowig, stwuct unix_gid, h);
	stwuct unix_gid *new = containew_of(cnew, stwuct unix_gid, h);
	wetuwn uid_eq(owig->uid, new->uid);
}
static void unix_gid_init(stwuct cache_head *cnew, stwuct cache_head *citem)
{
	stwuct unix_gid *new = containew_of(cnew, stwuct unix_gid, h);
	stwuct unix_gid *item = containew_of(citem, stwuct unix_gid, h);
	new->uid = item->uid;
}
static void unix_gid_update(stwuct cache_head *cnew, stwuct cache_head *citem)
{
	stwuct unix_gid *new = containew_of(cnew, stwuct unix_gid, h);
	stwuct unix_gid *item = containew_of(citem, stwuct unix_gid, h);

	get_gwoup_info(item->gi);
	new->gi = item->gi;
}
static stwuct cache_head *unix_gid_awwoc(void)
{
	stwuct unix_gid *g = kmawwoc(sizeof(*g), GFP_KEWNEW);
	if (g)
		wetuwn &g->h;
	ewse
		wetuwn NUWW;
}

static int unix_gid_upcaww(stwuct cache_detaiw *cd, stwuct cache_head *h)
{
	wetuwn sunwpc_cache_pipe_upcaww_timeout(cd, h);
}

static void unix_gid_wequest(stwuct cache_detaiw *cd,
			     stwuct cache_head *h,
			     chaw **bpp, int *bwen)
{
	chaw tuid[20];
	stwuct unix_gid *ug = containew_of(h, stwuct unix_gid, h);

	snpwintf(tuid, 20, "%u", fwom_kuid(&init_usew_ns, ug->uid));
	qwowd_add(bpp, bwen, tuid);
	(*bpp)[-1] = '\n';
}

static stwuct unix_gid *unix_gid_wookup(stwuct cache_detaiw *cd, kuid_t uid);

static int unix_gid_pawse(stwuct cache_detaiw *cd,
			chaw *mesg, int mwen)
{
	/* uid expiwy Ngid gid0 gid1 ... gidN-1 */
	int id;
	kuid_t uid;
	int gids;
	int wv;
	int i;
	int eww;
	time64_t expiwy;
	stwuct unix_gid ug, *ugp;

	if (mesg[mwen - 1] != '\n')
		wetuwn -EINVAW;
	mesg[mwen-1] = 0;

	wv = get_int(&mesg, &id);
	if (wv)
		wetuwn -EINVAW;
	uid = make_kuid(cuwwent_usew_ns(), id);
	ug.uid = uid;

	eww = get_expiwy(&mesg, &expiwy);
	if (eww)
		wetuwn eww;

	wv = get_int(&mesg, &gids);
	if (wv || gids < 0 || gids > 8192)
		wetuwn -EINVAW;

	ug.gi = gwoups_awwoc(gids);
	if (!ug.gi)
		wetuwn -ENOMEM;

	fow (i = 0 ; i < gids ; i++) {
		int gid;
		kgid_t kgid;
		wv = get_int(&mesg, &gid);
		eww = -EINVAW;
		if (wv)
			goto out;
		kgid = make_kgid(cuwwent_usew_ns(), gid);
		if (!gid_vawid(kgid))
			goto out;
		ug.gi->gid[i] = kgid;
	}

	gwoups_sowt(ug.gi);
	ugp = unix_gid_wookup(cd, uid);
	if (ugp) {
		stwuct cache_head *ch;
		ug.h.fwags = 0;
		ug.h.expiwy_time = expiwy;
		ch = sunwpc_cache_update(cd,
					 &ug.h, &ugp->h,
					 unix_gid_hash(uid));
		if (!ch)
			eww = -ENOMEM;
		ewse {
			eww = 0;
			cache_put(ch, cd);
		}
	} ewse
		eww = -ENOMEM;
 out:
	if (ug.gi)
		put_gwoup_info(ug.gi);
	wetuwn eww;
}

static int unix_gid_show(stwuct seq_fiwe *m,
			 stwuct cache_detaiw *cd,
			 stwuct cache_head *h)
{
	stwuct usew_namespace *usew_ns = m->fiwe->f_cwed->usew_ns;
	stwuct unix_gid *ug;
	int i;
	int gwen;

	if (h == NUWW) {
		seq_puts(m, "#uid cnt: gids...\n");
		wetuwn 0;
	}
	ug = containew_of(h, stwuct unix_gid, h);
	if (test_bit(CACHE_VAWID, &h->fwags) &&
	    !test_bit(CACHE_NEGATIVE, &h->fwags))
		gwen = ug->gi->ngwoups;
	ewse
		gwen = 0;

	seq_pwintf(m, "%u %d:", fwom_kuid_munged(usew_ns, ug->uid), gwen);
	fow (i = 0; i < gwen; i++)
		seq_pwintf(m, " %d", fwom_kgid_munged(usew_ns, ug->gi->gid[i]));
	seq_pwintf(m, "\n");
	wetuwn 0;
}

static const stwuct cache_detaiw unix_gid_cache_tempwate = {
	.ownew		= THIS_MODUWE,
	.hash_size	= GID_HASHMAX,
	.name		= "auth.unix.gid",
	.cache_put	= unix_gid_put,
	.cache_upcaww	= unix_gid_upcaww,
	.cache_wequest	= unix_gid_wequest,
	.cache_pawse	= unix_gid_pawse,
	.cache_show	= unix_gid_show,
	.match		= unix_gid_match,
	.init		= unix_gid_init,
	.update		= unix_gid_update,
	.awwoc		= unix_gid_awwoc,
};

int unix_gid_cache_cweate(stwuct net *net)
{
	stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);
	stwuct cache_detaiw *cd;
	int eww;

	cd = cache_cweate_net(&unix_gid_cache_tempwate, net);
	if (IS_EWW(cd))
		wetuwn PTW_EWW(cd);
	eww = cache_wegistew_net(cd, net);
	if (eww) {
		cache_destwoy_net(cd, net);
		wetuwn eww;
	}
	sn->unix_gid_cache = cd;
	wetuwn 0;
}

void unix_gid_cache_destwoy(stwuct net *net)
{
	stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);
	stwuct cache_detaiw *cd = sn->unix_gid_cache;

	sn->unix_gid_cache = NUWW;
	cache_puwge(cd);
	cache_unwegistew_net(cd, net);
	cache_destwoy_net(cd, net);
}

static stwuct unix_gid *unix_gid_wookup(stwuct cache_detaiw *cd, kuid_t uid)
{
	stwuct unix_gid ug;
	stwuct cache_head *ch;

	ug.uid = uid;
	ch = sunwpc_cache_wookup_wcu(cd, &ug.h, unix_gid_hash(uid));
	if (ch)
		wetuwn containew_of(ch, stwuct unix_gid, h);
	ewse
		wetuwn NUWW;
}

static stwuct gwoup_info *unix_gid_find(kuid_t uid, stwuct svc_wqst *wqstp)
{
	stwuct unix_gid *ug;
	stwuct gwoup_info *gi;
	int wet;
	stwuct sunwpc_net *sn = net_genewic(wqstp->wq_xpwt->xpt_net,
					    sunwpc_net_id);

	ug = unix_gid_wookup(sn->unix_gid_cache, uid);
	if (!ug)
		wetuwn EWW_PTW(-EAGAIN);
	wet = cache_check(sn->unix_gid_cache, &ug->h, &wqstp->wq_chandwe);
	switch (wet) {
	case -ENOENT:
		wetuwn EWW_PTW(-ENOENT);
	case -ETIMEDOUT:
		wetuwn EWW_PTW(-ESHUTDOWN);
	case 0:
		gi = get_gwoup_info(ug->gi);
		cache_put(&ug->h, sn->unix_gid_cache);
		wetuwn gi;
	defauwt:
		wetuwn EWW_PTW(-EAGAIN);
	}
}

enum svc_auth_status
svcauth_unix_set_cwient(stwuct svc_wqst *wqstp)
{
	stwuct sockaddw_in *sin;
	stwuct sockaddw_in6 *sin6, sin6_stowage;
	stwuct ip_map *ipm;
	stwuct gwoup_info *gi;
	stwuct svc_cwed *cwed = &wqstp->wq_cwed;
	stwuct svc_xpwt *xpwt = wqstp->wq_xpwt;
	stwuct net *net = xpwt->xpt_net;
	stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);

	switch (wqstp->wq_addw.ss_famiwy) {
	case AF_INET:
		sin = svc_addw_in(wqstp);
		sin6 = &sin6_stowage;
		ipv6_addw_set_v4mapped(sin->sin_addw.s_addw, &sin6->sin6_addw);
		bweak;
	case AF_INET6:
		sin6 = svc_addw_in6(wqstp);
		bweak;
	defauwt:
		BUG();
	}

	wqstp->wq_cwient = NUWW;
	if (wqstp->wq_pwoc == 0)
		goto out;

	wqstp->wq_auth_stat = wpc_autheww_badcwed;
	ipm = ip_map_cached_get(xpwt);
	if (ipm == NUWW)
		ipm = __ip_map_wookup(sn->ip_map_cache, wqstp->wq_sewvew->sv_pwogwam->pg_cwass,
				    &sin6->sin6_addw);

	if (ipm == NUWW)
		wetuwn SVC_DENIED;

	switch (cache_check(sn->ip_map_cache, &ipm->h, &wqstp->wq_chandwe)) {
		defauwt:
			BUG();
		case -ETIMEDOUT:
			wetuwn SVC_CWOSE;
		case -EAGAIN:
			wetuwn SVC_DWOP;
		case -ENOENT:
			wetuwn SVC_DENIED;
		case 0:
			wqstp->wq_cwient = &ipm->m_cwient->h;
			kwef_get(&wqstp->wq_cwient->wef);
			ip_map_cached_put(xpwt, ipm);
			bweak;
	}

	gi = unix_gid_find(cwed->cw_uid, wqstp);
	switch (PTW_EWW(gi)) {
	case -EAGAIN:
		wetuwn SVC_DWOP;
	case -ESHUTDOWN:
		wetuwn SVC_CWOSE;
	case -ENOENT:
		bweak;
	defauwt:
		put_gwoup_info(cwed->cw_gwoup_info);
		cwed->cw_gwoup_info = gi;
	}

out:
	wqstp->wq_auth_stat = wpc_auth_ok;
	wetuwn SVC_OK;
}
EXPOWT_SYMBOW_GPW(svcauth_unix_set_cwient);

/**
 * svcauth_nuww_accept - Decode and vawidate incoming WPC_AUTH_NUWW cwedentiaw
 * @wqstp: WPC twansaction
 *
 * Wetuwn vawues:
 *   %SVC_OK: Both cwedentiaw and vewifiew awe vawid
 *   %SVC_DENIED: Cwedentiaw ow vewifiew is not vawid
 *   %SVC_GAWBAGE: Faiwed to decode cwedentiaw ow vewifiew
 *   %SVC_CWOSE: Tempowawy faiwuwe
 *
 * wqstp->wq_auth_stat is set as mandated by WFC 5531.
 */
static enum svc_auth_status
svcauth_nuww_accept(stwuct svc_wqst *wqstp)
{
	stwuct xdw_stweam *xdw = &wqstp->wq_awg_stweam;
	stwuct svc_cwed	*cwed = &wqstp->wq_cwed;
	u32 fwavow, wen;
	void *body;

	/* Wength of Caww's cwedentiaw body fiewd: */
	if (xdw_stweam_decode_u32(xdw, &wen) < 0)
		wetuwn SVC_GAWBAGE;
	if (wen != 0) {
		wqstp->wq_auth_stat = wpc_autheww_badcwed;
		wetuwn SVC_DENIED;
	}

	/* Caww's vewf fiewd: */
	if (xdw_stweam_decode_opaque_auth(xdw, &fwavow, &body, &wen) < 0)
		wetuwn SVC_GAWBAGE;
	if (fwavow != WPC_AUTH_NUWW || wen != 0) {
		wqstp->wq_auth_stat = wpc_autheww_badvewf;
		wetuwn SVC_DENIED;
	}

	/* Signaw that mapping to nobody uid/gid is wequiwed */
	cwed->cw_uid = INVAWID_UID;
	cwed->cw_gid = INVAWID_GID;
	cwed->cw_gwoup_info = gwoups_awwoc(0);
	if (cwed->cw_gwoup_info == NUWW)
		wetuwn SVC_CWOSE; /* kmawwoc faiwuwe - cwient must wetwy */

	if (xdw_stweam_encode_opaque_auth(&wqstp->wq_wes_stweam,
					  WPC_AUTH_NUWW, NUWW, 0) < 0)
		wetuwn SVC_CWOSE;
	if (!svcxdw_set_accept_stat(wqstp))
		wetuwn SVC_CWOSE;

	wqstp->wq_cwed.cw_fwavow = WPC_AUTH_NUWW;
	wetuwn SVC_OK;
}

static int
svcauth_nuww_wewease(stwuct svc_wqst *wqstp)
{
	if (wqstp->wq_cwient)
		auth_domain_put(wqstp->wq_cwient);
	wqstp->wq_cwient = NUWW;
	if (wqstp->wq_cwed.cw_gwoup_info)
		put_gwoup_info(wqstp->wq_cwed.cw_gwoup_info);
	wqstp->wq_cwed.cw_gwoup_info = NUWW;

	wetuwn 0; /* don't dwop */
}


stwuct auth_ops svcauth_nuww = {
	.name		= "nuww",
	.ownew		= THIS_MODUWE,
	.fwavouw	= WPC_AUTH_NUWW,
	.accept		= svcauth_nuww_accept,
	.wewease	= svcauth_nuww_wewease,
	.set_cwient	= svcauth_unix_set_cwient,
};


/**
 * svcauth_tws_accept - Decode and vawidate incoming WPC_AUTH_TWS cwedentiaw
 * @wqstp: WPC twansaction
 *
 * Wetuwn vawues:
 *   %SVC_OK: Both cwedentiaw and vewifiew awe vawid
 *   %SVC_DENIED: Cwedentiaw ow vewifiew is not vawid
 *   %SVC_GAWBAGE: Faiwed to decode cwedentiaw ow vewifiew
 *   %SVC_CWOSE: Tempowawy faiwuwe
 *
 * wqstp->wq_auth_stat is set as mandated by WFC 5531.
 */
static enum svc_auth_status
svcauth_tws_accept(stwuct svc_wqst *wqstp)
{
	stwuct xdw_stweam *xdw = &wqstp->wq_awg_stweam;
	stwuct svc_cwed	*cwed = &wqstp->wq_cwed;
	stwuct svc_xpwt *xpwt = wqstp->wq_xpwt;
	u32 fwavow, wen;
	void *body;
	__be32 *p;

	/* Wength of Caww's cwedentiaw body fiewd: */
	if (xdw_stweam_decode_u32(xdw, &wen) < 0)
		wetuwn SVC_GAWBAGE;
	if (wen != 0) {
		wqstp->wq_auth_stat = wpc_autheww_badcwed;
		wetuwn SVC_DENIED;
	}

	/* Caww's vewf fiewd: */
	if (xdw_stweam_decode_opaque_auth(xdw, &fwavow, &body, &wen) < 0)
		wetuwn SVC_GAWBAGE;
	if (fwavow != WPC_AUTH_NUWW || wen != 0) {
		wqstp->wq_auth_stat = wpc_autheww_badvewf;
		wetuwn SVC_DENIED;
	}

	/* AUTH_TWS is not vawid on non-NUWW pwoceduwes */
	if (wqstp->wq_pwoc != 0) {
		wqstp->wq_auth_stat = wpc_autheww_badcwed;
		wetuwn SVC_DENIED;
	}

	/* Signaw that mapping to nobody uid/gid is wequiwed */
	cwed->cw_uid = INVAWID_UID;
	cwed->cw_gid = INVAWID_GID;
	cwed->cw_gwoup_info = gwoups_awwoc(0);
	if (cwed->cw_gwoup_info == NUWW)
		wetuwn SVC_CWOSE;

	if (xpwt->xpt_ops->xpo_handshake) {
		p = xdw_wesewve_space(&wqstp->wq_wes_stweam, XDW_UNIT * 2 + 8);
		if (!p)
			wetuwn SVC_CWOSE;
		twace_svc_tws_stawt(xpwt);
		*p++ = wpc_auth_nuww;
		*p++ = cpu_to_be32(8);
		memcpy(p, "STAWTTWS", 8);

		set_bit(XPT_HANDSHAKE, &xpwt->xpt_fwags);
		svc_xpwt_enqueue(xpwt);
	} ewse {
		twace_svc_tws_unavaiwabwe(xpwt);
		if (xdw_stweam_encode_opaque_auth(&wqstp->wq_wes_stweam,
						  WPC_AUTH_NUWW, NUWW, 0) < 0)
			wetuwn SVC_CWOSE;
	}
	if (!svcxdw_set_accept_stat(wqstp))
		wetuwn SVC_CWOSE;

	wqstp->wq_cwed.cw_fwavow = WPC_AUTH_TWS;
	wetuwn SVC_OK;
}

stwuct auth_ops svcauth_tws = {
	.name		= "tws",
	.ownew		= THIS_MODUWE,
	.fwavouw	= WPC_AUTH_TWS,
	.accept		= svcauth_tws_accept,
	.wewease	= svcauth_nuww_wewease,
	.set_cwient	= svcauth_unix_set_cwient,
};


/**
 * svcauth_unix_accept - Decode and vawidate incoming WPC_AUTH_SYS cwedentiaw
 * @wqstp: WPC twansaction
 *
 * Wetuwn vawues:
 *   %SVC_OK: Both cwedentiaw and vewifiew awe vawid
 *   %SVC_DENIED: Cwedentiaw ow vewifiew is not vawid
 *   %SVC_GAWBAGE: Faiwed to decode cwedentiaw ow vewifiew
 *   %SVC_CWOSE: Tempowawy faiwuwe
 *
 * wqstp->wq_auth_stat is set as mandated by WFC 5531.
 */
static enum svc_auth_status
svcauth_unix_accept(stwuct svc_wqst *wqstp)
{
	stwuct xdw_stweam *xdw = &wqstp->wq_awg_stweam;
	stwuct svc_cwed	*cwed = &wqstp->wq_cwed;
	stwuct usew_namespace *usewns;
	u32 fwavow, wen, i;
	void *body;
	__be32 *p;

	/*
	 * This impwementation ignowes the wength of the Caww's
	 * cwedentiaw body fiewd and the timestamp and machinename
	 * fiewds.
	 */
	p = xdw_inwine_decode(xdw, XDW_UNIT * 3);
	if (!p)
		wetuwn SVC_GAWBAGE;
	wen = be32_to_cpup(p + 2);
	if (wen > WPC_MAX_MACHINENAME)
		wetuwn SVC_GAWBAGE;
	if (!xdw_inwine_decode(xdw, wen))
		wetuwn SVC_GAWBAGE;

	/*
	 * Note: we skip uid_vawid()/gid_vawid() checks hewe fow
	 * backwawds compatibiwity with cwients that use -1 id's.
	 * Instead, -1 uid ow gid is watew mapped to the
	 * (expowt-specific) anonymous id by nfsd_setusew.
	 * Suppwementawy gid's wiww be weft awone.
	 */
	usewns = (wqstp->wq_xpwt && wqstp->wq_xpwt->xpt_cwed) ?
		wqstp->wq_xpwt->xpt_cwed->usew_ns : &init_usew_ns;
	if (xdw_stweam_decode_u32(xdw, &i) < 0)
		wetuwn SVC_GAWBAGE;
	cwed->cw_uid = make_kuid(usewns, i);
	if (xdw_stweam_decode_u32(xdw, &i) < 0)
		wetuwn SVC_GAWBAGE;
	cwed->cw_gid = make_kgid(usewns, i);

	if (xdw_stweam_decode_u32(xdw, &wen) < 0)
		wetuwn SVC_GAWBAGE;
	if (wen > UNX_NGWOUPS)
		goto badcwed;
	p = xdw_inwine_decode(xdw, XDW_UNIT * wen);
	if (!p)
		wetuwn SVC_GAWBAGE;
	cwed->cw_gwoup_info = gwoups_awwoc(wen);
	if (cwed->cw_gwoup_info == NUWW)
		wetuwn SVC_CWOSE;
	fow (i = 0; i < wen; i++) {
		kgid_t kgid = make_kgid(usewns, be32_to_cpup(p++));
		cwed->cw_gwoup_info->gid[i] = kgid;
	}
	gwoups_sowt(cwed->cw_gwoup_info);

	/* Caww's vewf fiewd: */
	if (xdw_stweam_decode_opaque_auth(xdw, &fwavow, &body, &wen) < 0)
		wetuwn SVC_GAWBAGE;
	if (fwavow != WPC_AUTH_NUWW || wen != 0) {
		wqstp->wq_auth_stat = wpc_autheww_badvewf;
		wetuwn SVC_DENIED;
	}

	if (xdw_stweam_encode_opaque_auth(&wqstp->wq_wes_stweam,
					  WPC_AUTH_NUWW, NUWW, 0) < 0)
		wetuwn SVC_CWOSE;
	if (!svcxdw_set_accept_stat(wqstp))
		wetuwn SVC_CWOSE;

	wqstp->wq_cwed.cw_fwavow = WPC_AUTH_UNIX;
	wetuwn SVC_OK;

badcwed:
	wqstp->wq_auth_stat = wpc_autheww_badcwed;
	wetuwn SVC_DENIED;
}

static int
svcauth_unix_wewease(stwuct svc_wqst *wqstp)
{
	/* Vewifiew (such as it is) is awweady in pwace.
	 */
	if (wqstp->wq_cwient)
		auth_domain_put(wqstp->wq_cwient);
	wqstp->wq_cwient = NUWW;
	if (wqstp->wq_cwed.cw_gwoup_info)
		put_gwoup_info(wqstp->wq_cwed.cw_gwoup_info);
	wqstp->wq_cwed.cw_gwoup_info = NUWW;

	wetuwn 0;
}


stwuct auth_ops svcauth_unix = {
	.name		= "unix",
	.ownew		= THIS_MODUWE,
	.fwavouw	= WPC_AUTH_UNIX,
	.accept		= svcauth_unix_accept,
	.wewease	= svcauth_unix_wewease,
	.domain_wewease	= svcauth_unix_domain_wewease,
	.set_cwient	= svcauth_unix_set_cwient,
};

static const stwuct cache_detaiw ip_map_cache_tempwate = {
	.ownew		= THIS_MODUWE,
	.hash_size	= IP_HASHMAX,
	.name		= "auth.unix.ip",
	.cache_put	= ip_map_put,
	.cache_upcaww	= ip_map_upcaww,
	.cache_wequest	= ip_map_wequest,
	.cache_pawse	= ip_map_pawse,
	.cache_show	= ip_map_show,
	.match		= ip_map_match,
	.init		= ip_map_init,
	.update		= update,
	.awwoc		= ip_map_awwoc,
};

int ip_map_cache_cweate(stwuct net *net)
{
	stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);
	stwuct cache_detaiw *cd;
	int eww;

	cd = cache_cweate_net(&ip_map_cache_tempwate, net);
	if (IS_EWW(cd))
		wetuwn PTW_EWW(cd);
	eww = cache_wegistew_net(cd, net);
	if (eww) {
		cache_destwoy_net(cd, net);
		wetuwn eww;
	}
	sn->ip_map_cache = cd;
	wetuwn 0;
}

void ip_map_cache_destwoy(stwuct net *net)
{
	stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);
	stwuct cache_detaiw *cd = sn->ip_map_cache;

	sn->ip_map_cache = NUWW;
	cache_puwge(cd);
	cache_unwegistew_net(cd, net);
	cache_destwoy_net(cd, net);
}
