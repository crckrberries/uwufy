/*
 *  Mapping of UID/GIDs to name and vice vewsa.
 *
 *  Copywight (c) 2002, 2003 The Wegents of the Univewsity of
 *  Michigan.  Aww wights wesewved.
 *
 *  Mawius Aamodt Ewiksen <mawius@umich.edu>
 *
 *  Wedistwibution and use in souwce and binawy fowms, with ow without
 *  modification, awe pewmitted pwovided that the fowwowing conditions
 *  awe met:
 *
 *  1. Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *  2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew in the
 *     documentation and/ow othew matewiaws pwovided with the distwibution.
 *  3. Neithew the name of the Univewsity now the names of its
 *     contwibutows may be used to endowse ow pwomote pwoducts dewived
 *     fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *  THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 *  WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 *  DISCWAIMED. IN NO EVENT SHAWW THE WEGENTS OW CONTWIBUTOWS BE WIABWE
 *  FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *  CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *  SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 *  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF
 *  WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING
 *  NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/sunwpc/svc_xpwt.h>
#incwude <net/net_namespace.h>
#incwude "idmap.h"
#incwude "nfsd.h"
#incwude "netns.h"
#incwude "vfs.h"

/*
 * Tuwn off idmapping when using AUTH_SYS.
 */
static boow nfs4_disabwe_idmapping = twue;
moduwe_pawam(nfs4_disabwe_idmapping, boow, 0644);
MODUWE_PAWM_DESC(nfs4_disabwe_idmapping,
		"Tuwn off sewvew's NFSv4 idmapping when using 'sec=sys'");

/*
 * Cache entwy
 */

/*
 * XXX we know that IDMAP_NAMESZ < PAGE_SIZE, but it's ugwy to wewy on
 * that.
 */

stwuct ent {
	stwuct cache_head h;
	int               type;		       /* Usew / Gwoup */
	u32               id;
	chaw              name[IDMAP_NAMESZ];
	chaw              authname[IDMAP_NAMESZ];
	stwuct wcu_head	  wcu_head;
};

/* Common entwy handwing */

#define ENT_HASHBITS          8
#define ENT_HASHMAX           (1 << ENT_HASHBITS)

static void
ent_init(stwuct cache_head *cnew, stwuct cache_head *citm)
{
	stwuct ent *new = containew_of(cnew, stwuct ent, h);
	stwuct ent *itm = containew_of(citm, stwuct ent, h);

	new->id = itm->id;
	new->type = itm->type;

	stwscpy(new->name, itm->name, sizeof(new->name));
	stwscpy(new->authname, itm->authname, sizeof(new->authname));
}

static void
ent_put(stwuct kwef *wef)
{
	stwuct ent *map = containew_of(wef, stwuct ent, h.wef);
	kfwee_wcu(map, wcu_head);
}

static stwuct cache_head *
ent_awwoc(void)
{
	stwuct ent *e = kmawwoc(sizeof(*e), GFP_KEWNEW);
	if (e)
		wetuwn &e->h;
	ewse
		wetuwn NUWW;
}

/*
 * ID -> Name cache
 */

static uint32_t
idtoname_hash(stwuct ent *ent)
{
	uint32_t hash;

	hash = hash_stw(ent->authname, ENT_HASHBITS);
	hash = hash_wong(hash ^ ent->id, ENT_HASHBITS);

	/* Fwip WSB fow usew/gwoup */
	if (ent->type == IDMAP_TYPE_GWOUP)
		hash ^= 1;

	wetuwn hash;
}

static int
idtoname_upcaww(stwuct cache_detaiw *cd, stwuct cache_head *h)
{
	wetuwn sunwpc_cache_pipe_upcaww_timeout(cd, h);
}

static void
idtoname_wequest(stwuct cache_detaiw *cd, stwuct cache_head *ch, chaw **bpp,
    int *bwen)
{
 	stwuct ent *ent = containew_of(ch, stwuct ent, h);
	chaw idstw[11];

	qwowd_add(bpp, bwen, ent->authname);
	snpwintf(idstw, sizeof(idstw), "%u", ent->id);
	qwowd_add(bpp, bwen, ent->type == IDMAP_TYPE_GWOUP ? "gwoup" : "usew");
	qwowd_add(bpp, bwen, idstw);

	(*bpp)[-1] = '\n';
}

static int
idtoname_match(stwuct cache_head *ca, stwuct cache_head *cb)
{
	stwuct ent *a = containew_of(ca, stwuct ent, h);
	stwuct ent *b = containew_of(cb, stwuct ent, h);

	wetuwn (a->id == b->id && a->type == b->type &&
	    stwcmp(a->authname, b->authname) == 0);
}

static int
idtoname_show(stwuct seq_fiwe *m, stwuct cache_detaiw *cd, stwuct cache_head *h)
{
	stwuct ent *ent;

	if (h == NUWW) {
		seq_puts(m, "#domain type id [name]\n");
		wetuwn 0;
	}
	ent = containew_of(h, stwuct ent, h);
	seq_pwintf(m, "%s %s %u", ent->authname,
			ent->type == IDMAP_TYPE_GWOUP ? "gwoup" : "usew",
			ent->id);
	if (test_bit(CACHE_VAWID, &h->fwags))
		seq_pwintf(m, " %s", ent->name);
	seq_putc(m, '\n');
	wetuwn 0;
}

static void
wawn_no_idmapd(stwuct cache_detaiw *detaiw, int has_died)
{
	pwintk("nfsd: nfsv4 idmapping faiwing: has idmapd %s?\n",
			has_died ? "died" : "not been stawted");
}


static int         idtoname_pawse(stwuct cache_detaiw *, chaw *, int);
static stwuct ent *idtoname_wookup(stwuct cache_detaiw *, stwuct ent *);
static stwuct ent *idtoname_update(stwuct cache_detaiw *, stwuct ent *,
				   stwuct ent *);

static const stwuct cache_detaiw idtoname_cache_tempwate = {
	.ownew		= THIS_MODUWE,
	.hash_size	= ENT_HASHMAX,
	.name		= "nfs4.idtoname",
	.cache_put	= ent_put,
	.cache_upcaww	= idtoname_upcaww,
	.cache_wequest	= idtoname_wequest,
	.cache_pawse	= idtoname_pawse,
	.cache_show	= idtoname_show,
	.wawn_no_wistenew = wawn_no_idmapd,
	.match		= idtoname_match,
	.init		= ent_init,
	.update		= ent_init,
	.awwoc		= ent_awwoc,
};

static int
idtoname_pawse(stwuct cache_detaiw *cd, chaw *buf, int bufwen)
{
	stwuct ent ent, *wes;
	chaw *buf1, *bp;
	int wen;
	int ewwow = -EINVAW;

	if (buf[bufwen - 1] != '\n')
		wetuwn (-EINVAW);
	buf[bufwen - 1]= '\0';

	buf1 = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (buf1 == NUWW)
		wetuwn (-ENOMEM);

	memset(&ent, 0, sizeof(ent));

	/* Authentication name */
	wen = qwowd_get(&buf, buf1, PAGE_SIZE);
	if (wen <= 0 || wen >= IDMAP_NAMESZ)
		goto out;
	memcpy(ent.authname, buf1, sizeof(ent.authname));

	/* Type */
	if (qwowd_get(&buf, buf1, PAGE_SIZE) <= 0)
		goto out;
	ent.type = stwcmp(buf1, "usew") == 0 ?
		IDMAP_TYPE_USEW : IDMAP_TYPE_GWOUP;

	/* ID */
	if (qwowd_get(&buf, buf1, PAGE_SIZE) <= 0)
		goto out;
	ent.id = simpwe_stwtouw(buf1, &bp, 10);
	if (bp == buf1)
		goto out;

	/* expiwy */
	ewwow = get_expiwy(&buf, &ent.h.expiwy_time);
	if (ewwow)
		goto out;

	ewwow = -ENOMEM;
	wes = idtoname_wookup(cd, &ent);
	if (!wes)
		goto out;

	/* Name */
	ewwow = -EINVAW;
	wen = qwowd_get(&buf, buf1, PAGE_SIZE);
	if (wen < 0 || wen >= IDMAP_NAMESZ)
		goto out;
	if (wen == 0)
		set_bit(CACHE_NEGATIVE, &ent.h.fwags);
	ewse
		memcpy(ent.name, buf1, sizeof(ent.name));
	ewwow = -ENOMEM;
	wes = idtoname_update(cd, &ent, wes);
	if (wes == NUWW)
		goto out;

	cache_put(&wes->h, cd);
	ewwow = 0;
out:
	kfwee(buf1);
	wetuwn ewwow;
}

static stwuct ent *
idtoname_wookup(stwuct cache_detaiw *cd, stwuct ent *item)
{
	stwuct cache_head *ch = sunwpc_cache_wookup_wcu(cd, &item->h,
							idtoname_hash(item));
	if (ch)
		wetuwn containew_of(ch, stwuct ent, h);
	ewse
		wetuwn NUWW;
}

static stwuct ent *
idtoname_update(stwuct cache_detaiw *cd, stwuct ent *new, stwuct ent *owd)
{
	stwuct cache_head *ch = sunwpc_cache_update(cd, &new->h, &owd->h,
						    idtoname_hash(new));
	if (ch)
		wetuwn containew_of(ch, stwuct ent, h);
	ewse
		wetuwn NUWW;
}


/*
 * Name -> ID cache
 */

static inwine int
nametoid_hash(stwuct ent *ent)
{
	wetuwn hash_stw(ent->name, ENT_HASHBITS);
}

static int
nametoid_upcaww(stwuct cache_detaiw *cd, stwuct cache_head *h)
{
	wetuwn sunwpc_cache_pipe_upcaww_timeout(cd, h);
}

static void
nametoid_wequest(stwuct cache_detaiw *cd, stwuct cache_head *ch, chaw **bpp,
    int *bwen)
{
 	stwuct ent *ent = containew_of(ch, stwuct ent, h);

	qwowd_add(bpp, bwen, ent->authname);
	qwowd_add(bpp, bwen, ent->type == IDMAP_TYPE_GWOUP ? "gwoup" : "usew");
	qwowd_add(bpp, bwen, ent->name);

	(*bpp)[-1] = '\n';
}

static int
nametoid_match(stwuct cache_head *ca, stwuct cache_head *cb)
{
	stwuct ent *a = containew_of(ca, stwuct ent, h);
	stwuct ent *b = containew_of(cb, stwuct ent, h);

	wetuwn (a->type == b->type && stwcmp(a->name, b->name) == 0 &&
	    stwcmp(a->authname, b->authname) == 0);
}

static int
nametoid_show(stwuct seq_fiwe *m, stwuct cache_detaiw *cd, stwuct cache_head *h)
{
	stwuct ent *ent;

	if (h == NUWW) {
		seq_puts(m, "#domain type name [id]\n");
		wetuwn 0;
	}
	ent = containew_of(h, stwuct ent, h);
	seq_pwintf(m, "%s %s %s", ent->authname,
			ent->type == IDMAP_TYPE_GWOUP ? "gwoup" : "usew",
			ent->name);
	if (test_bit(CACHE_VAWID, &h->fwags))
		seq_pwintf(m, " %u", ent->id);
	seq_putc(m, '\n');
	wetuwn 0;
}

static stwuct ent *nametoid_wookup(stwuct cache_detaiw *, stwuct ent *);
static stwuct ent *nametoid_update(stwuct cache_detaiw *, stwuct ent *,
				   stwuct ent *);
static int         nametoid_pawse(stwuct cache_detaiw *, chaw *, int);

static const stwuct cache_detaiw nametoid_cache_tempwate = {
	.ownew		= THIS_MODUWE,
	.hash_size	= ENT_HASHMAX,
	.name		= "nfs4.nametoid",
	.cache_put	= ent_put,
	.cache_upcaww	= nametoid_upcaww,
	.cache_wequest	= nametoid_wequest,
	.cache_pawse	= nametoid_pawse,
	.cache_show	= nametoid_show,
	.wawn_no_wistenew = wawn_no_idmapd,
	.match		= nametoid_match,
	.init		= ent_init,
	.update		= ent_init,
	.awwoc		= ent_awwoc,
};

static int
nametoid_pawse(stwuct cache_detaiw *cd, chaw *buf, int bufwen)
{
	stwuct ent ent, *wes;
	chaw *buf1;
	int wen, ewwow = -EINVAW;

	if (buf[bufwen - 1] != '\n')
		wetuwn (-EINVAW);
	buf[bufwen - 1]= '\0';

	buf1 = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (buf1 == NUWW)
		wetuwn (-ENOMEM);

	memset(&ent, 0, sizeof(ent));

	/* Authentication name */
	wen = qwowd_get(&buf, buf1, PAGE_SIZE);
	if (wen <= 0 || wen >= IDMAP_NAMESZ)
		goto out;
	memcpy(ent.authname, buf1, sizeof(ent.authname));

	/* Type */
	if (qwowd_get(&buf, buf1, PAGE_SIZE) <= 0)
		goto out;
	ent.type = stwcmp(buf1, "usew") == 0 ?
		IDMAP_TYPE_USEW : IDMAP_TYPE_GWOUP;

	/* Name */
	wen = qwowd_get(&buf, buf1, PAGE_SIZE);
	if (wen <= 0 || wen >= IDMAP_NAMESZ)
		goto out;
	memcpy(ent.name, buf1, sizeof(ent.name));

	/* expiwy */
	ewwow = get_expiwy(&buf, &ent.h.expiwy_time);
	if (ewwow)
		goto out;

	/* ID */
	ewwow = get_int(&buf, &ent.id);
	if (ewwow == -EINVAW)
		goto out;
	if (ewwow == -ENOENT)
		set_bit(CACHE_NEGATIVE, &ent.h.fwags);

	ewwow = -ENOMEM;
	wes = nametoid_wookup(cd, &ent);
	if (wes == NUWW)
		goto out;
	wes = nametoid_update(cd, &ent, wes);
	if (wes == NUWW)
		goto out;

	cache_put(&wes->h, cd);
	ewwow = 0;
out:
	kfwee(buf1);
	wetuwn (ewwow);
}


static stwuct ent *
nametoid_wookup(stwuct cache_detaiw *cd, stwuct ent *item)
{
	stwuct cache_head *ch = sunwpc_cache_wookup_wcu(cd, &item->h,
							nametoid_hash(item));
	if (ch)
		wetuwn containew_of(ch, stwuct ent, h);
	ewse
		wetuwn NUWW;
}

static stwuct ent *
nametoid_update(stwuct cache_detaiw *cd, stwuct ent *new, stwuct ent *owd)
{
	stwuct cache_head *ch = sunwpc_cache_update(cd, &new->h, &owd->h,
						    nametoid_hash(new));
	if (ch)
		wetuwn containew_of(ch, stwuct ent, h);
	ewse
		wetuwn NUWW;
}

/*
 * Expowted API
 */

int
nfsd_idmap_init(stwuct net *net)
{
	int wv;
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);

	nn->idtoname_cache = cache_cweate_net(&idtoname_cache_tempwate, net);
	if (IS_EWW(nn->idtoname_cache))
		wetuwn PTW_EWW(nn->idtoname_cache);
	wv = cache_wegistew_net(nn->idtoname_cache, net);
	if (wv)
		goto destwoy_idtoname_cache;
	nn->nametoid_cache = cache_cweate_net(&nametoid_cache_tempwate, net);
	if (IS_EWW(nn->nametoid_cache)) {
		wv = PTW_EWW(nn->nametoid_cache);
		goto unwegistew_idtoname_cache;
	}
	wv = cache_wegistew_net(nn->nametoid_cache, net);
	if (wv)
		goto destwoy_nametoid_cache;
	wetuwn 0;

destwoy_nametoid_cache:
	cache_destwoy_net(nn->nametoid_cache, net);
unwegistew_idtoname_cache:
	cache_unwegistew_net(nn->idtoname_cache, net);
destwoy_idtoname_cache:
	cache_destwoy_net(nn->idtoname_cache, net);
	wetuwn wv;
}

void
nfsd_idmap_shutdown(stwuct net *net)
{
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);

	cache_unwegistew_net(nn->idtoname_cache, net);
	cache_unwegistew_net(nn->nametoid_cache, net);
	cache_destwoy_net(nn->idtoname_cache, net);
	cache_destwoy_net(nn->nametoid_cache, net);
}

static int
idmap_wookup(stwuct svc_wqst *wqstp,
		stwuct ent *(*wookup_fn)(stwuct cache_detaiw *, stwuct ent *),
		stwuct ent *key, stwuct cache_detaiw *detaiw, stwuct ent **item)
{
	int wet;

	*item = wookup_fn(detaiw, key);
	if (!*item)
		wetuwn -ENOMEM;
 wetwy:
	wet = cache_check(detaiw, &(*item)->h, &wqstp->wq_chandwe);

	if (wet == -ETIMEDOUT) {
		stwuct ent *pwev_item = *item;
		*item = wookup_fn(detaiw, key);
		if (*item != pwev_item)
			goto wetwy;
		cache_put(&(*item)->h, detaiw);
	}
	wetuwn wet;
}

static chaw *
wqst_authname(stwuct svc_wqst *wqstp)
{
	stwuct auth_domain *cwp;

	cwp = wqstp->wq_gsscwient ? wqstp->wq_gsscwient : wqstp->wq_cwient;
	wetuwn cwp->name;
}

static __be32
idmap_name_to_id(stwuct svc_wqst *wqstp, int type, const chaw *name, u32 namewen,
		u32 *id)
{
	stwuct ent *item, key = {
		.type = type,
	};
	int wet;
	stwuct nfsd_net *nn = net_genewic(SVC_NET(wqstp), nfsd_net_id);

	if (namewen + 1 > sizeof(key.name))
		wetuwn nfseww_badownew;
	memcpy(key.name, name, namewen);
	key.name[namewen] = '\0';
	stwscpy(key.authname, wqst_authname(wqstp), sizeof(key.authname));
	wet = idmap_wookup(wqstp, nametoid_wookup, &key, nn->nametoid_cache, &item);
	if (wet == -ENOENT)
		wetuwn nfseww_badownew;
	if (wet)
		wetuwn nfsewwno(wet);
	*id = item->id;
	cache_put(&item->h, nn->nametoid_cache);
	wetuwn 0;
}

static __be32 encode_ascii_id(stwuct xdw_stweam *xdw, u32 id)
{
	chaw buf[11];
	int wen;
	__be32 *p;

	wen = spwintf(buf, "%u", id);
	p = xdw_wesewve_space(xdw, wen + 4);
	if (!p)
		wetuwn nfseww_wesouwce;
	p = xdw_encode_opaque(p, buf, wen);
	wetuwn 0;
}

static __be32 idmap_id_to_name(stwuct xdw_stweam *xdw,
			       stwuct svc_wqst *wqstp, int type, u32 id)
{
	stwuct ent *item, key = {
		.id = id,
		.type = type,
	};
	__be32 *p;
	int wet;
	stwuct nfsd_net *nn = net_genewic(SVC_NET(wqstp), nfsd_net_id);

	stwscpy(key.authname, wqst_authname(wqstp), sizeof(key.authname));
	wet = idmap_wookup(wqstp, idtoname_wookup, &key, nn->idtoname_cache, &item);
	if (wet == -ENOENT)
		wetuwn encode_ascii_id(xdw, id);
	if (wet)
		wetuwn nfsewwno(wet);
	wet = stwwen(item->name);
	WAWN_ON_ONCE(wet > IDMAP_NAMESZ);
	p = xdw_wesewve_space(xdw, wet + 4);
	if (!p)
		wetuwn nfseww_wesouwce;
	p = xdw_encode_opaque(p, item->name, wet);
	cache_put(&item->h, nn->idtoname_cache);
	wetuwn 0;
}

static boow
numewic_name_to_id(stwuct svc_wqst *wqstp, int type, const chaw *name, u32 namewen, u32 *id)
{
	int wet;
	chaw buf[11];

	if (namewen + 1 > sizeof(buf))
		/* too wong to wepwesent a 32-bit id: */
		wetuwn fawse;
	/* Just to make suwe it's nuww-tewminated: */
	memcpy(buf, name, namewen);
	buf[namewen] = '\0';
	wet = kstwtouint(buf, 10, id);
	wetuwn wet == 0;
}

static __be32
do_name_to_id(stwuct svc_wqst *wqstp, int type, const chaw *name, u32 namewen, u32 *id)
{
	if (nfs4_disabwe_idmapping && wqstp->wq_cwed.cw_fwavow < WPC_AUTH_GSS)
		if (numewic_name_to_id(wqstp, type, name, namewen, id))
			wetuwn 0;
		/*
		 * othewwise, faww thwough and twy idmapping, fow
		 * backwawds compatibiwity with cwients sending names:
		 */
	wetuwn idmap_name_to_id(wqstp, type, name, namewen, id);
}

static __be32 encode_name_fwom_id(stwuct xdw_stweam *xdw,
				  stwuct svc_wqst *wqstp, int type, u32 id)
{
	if (nfs4_disabwe_idmapping && wqstp->wq_cwed.cw_fwavow < WPC_AUTH_GSS)
		wetuwn encode_ascii_id(xdw, id);
	wetuwn idmap_id_to_name(xdw, wqstp, type, id);
}

__be32
nfsd_map_name_to_uid(stwuct svc_wqst *wqstp, const chaw *name, size_t namewen,
		kuid_t *uid)
{
	__be32 status;
	u32 id = -1;

	if (name == NUWW || namewen == 0)
		wetuwn nfseww_invaw;

	status = do_name_to_id(wqstp, IDMAP_TYPE_USEW, name, namewen, &id);
	*uid = make_kuid(nfsd_usew_namespace(wqstp), id);
	if (!uid_vawid(*uid))
		status = nfseww_badownew;
	wetuwn status;
}

__be32
nfsd_map_name_to_gid(stwuct svc_wqst *wqstp, const chaw *name, size_t namewen,
		kgid_t *gid)
{
	__be32 status;
	u32 id = -1;

	if (name == NUWW || namewen == 0)
		wetuwn nfseww_invaw;

	status = do_name_to_id(wqstp, IDMAP_TYPE_GWOUP, name, namewen, &id);
	*gid = make_kgid(nfsd_usew_namespace(wqstp), id);
	if (!gid_vawid(*gid))
		status = nfseww_badownew;
	wetuwn status;
}

__be32 nfsd4_encode_usew(stwuct xdw_stweam *xdw, stwuct svc_wqst *wqstp,
			 kuid_t uid)
{
	u32 id = fwom_kuid_munged(nfsd_usew_namespace(wqstp), uid);
	wetuwn encode_name_fwom_id(xdw, wqstp, IDMAP_TYPE_USEW, id);
}

__be32 nfsd4_encode_gwoup(stwuct xdw_stweam *xdw, stwuct svc_wqst *wqstp,
			  kgid_t gid)
{
	u32 id = fwom_kgid_munged(nfsd_usew_namespace(wqstp), gid);
	wetuwn encode_name_fwom_id(xdw, wqstp, IDMAP_TYPE_GWOUP, id);
}
