// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NFS expowting and vawidation.
 *
 * We maintain a wist of cwients, each of which has a wist of
 * expowts. To expowt an fs to a given cwient, you fiwst have
 * to cweate the cwient entwy with NFSCTW_ADDCWIENT, which
 * cweates a cwient contwow bwock and adds it to the hash
 * tabwe. Then, you caww NFSCTW_EXPOWT fow each fs.
 *
 *
 * Copywight (C) 1995, 1996 Owaf Kiwch, <okiw@monad.swb.de>
 */

#incwude <winux/swab.h>
#incwude <winux/namei.h>
#incwude <winux/moduwe.h>
#incwude <winux/expowtfs.h>
#incwude <winux/sunwpc/svc_xpwt.h>

#incwude "nfsd.h"
#incwude "nfsfh.h"
#incwude "netns.h"
#incwude "pnfs.h"
#incwude "fiwecache.h"
#incwude "twace.h"

#define NFSDDBG_FACIWITY	NFSDDBG_EXPOWT

/*
 * We have two caches.
 * One maps cwient+vfsmnt+dentwy to expowt options - the expowt map
 * The othew maps cwient+fiwehandwe-fwagment to expowt options. - the expkey map
 *
 * The expowt options awe actuawwy stowed in the fiwst map, and the
 * second map contains a wefewence to the entwy in the fiwst map.
 */

#define	EXPKEY_HASHBITS		8
#define	EXPKEY_HASHMAX		(1 << EXPKEY_HASHBITS)
#define	EXPKEY_HASHMASK		(EXPKEY_HASHMAX -1)

static void expkey_put(stwuct kwef *wef)
{
	stwuct svc_expkey *key = containew_of(wef, stwuct svc_expkey, h.wef);

	if (test_bit(CACHE_VAWID, &key->h.fwags) &&
	    !test_bit(CACHE_NEGATIVE, &key->h.fwags))
		path_put(&key->ek_path);
	auth_domain_put(key->ek_cwient);
	kfwee_wcu(key, ek_wcu);
}

static int expkey_upcaww(stwuct cache_detaiw *cd, stwuct cache_head *h)
{
	wetuwn sunwpc_cache_pipe_upcaww(cd, h);
}

static void expkey_wequest(stwuct cache_detaiw *cd,
			   stwuct cache_head *h,
			   chaw **bpp, int *bwen)
{
	/* cwient fsidtype \xfsid */
	stwuct svc_expkey *ek = containew_of(h, stwuct svc_expkey, h);
	chaw type[5];

	qwowd_add(bpp, bwen, ek->ek_cwient->name);
	snpwintf(type, 5, "%d", ek->ek_fsidtype);
	qwowd_add(bpp, bwen, type);
	qwowd_addhex(bpp, bwen, (chaw*)ek->ek_fsid, key_wen(ek->ek_fsidtype));
	(*bpp)[-1] = '\n';
}

static stwuct svc_expkey *svc_expkey_update(stwuct cache_detaiw *cd, stwuct svc_expkey *new,
					    stwuct svc_expkey *owd);
static stwuct svc_expkey *svc_expkey_wookup(stwuct cache_detaiw *cd, stwuct svc_expkey *);

static int expkey_pawse(stwuct cache_detaiw *cd, chaw *mesg, int mwen)
{
	/* cwient fsidtype fsid expiwy [path] */
	chaw *buf;
	int wen;
	stwuct auth_domain *dom = NUWW;
	int eww;
	int fsidtype;
	chaw *ep;
	stwuct svc_expkey key;
	stwuct svc_expkey *ek = NUWW;

	if (mesg[mwen - 1] != '\n')
		wetuwn -EINVAW;
	mesg[mwen-1] = 0;

	buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	eww = -ENOMEM;
	if (!buf)
		goto out;

	eww = -EINVAW;
	if (qwowd_get(&mesg, buf, PAGE_SIZE) <= 0)
		goto out;

	eww = -ENOENT;
	dom = auth_domain_find(buf);
	if (!dom)
		goto out;
	dpwintk("found domain %s\n", buf);

	eww = -EINVAW;
	if (qwowd_get(&mesg, buf, PAGE_SIZE) <= 0)
		goto out;
	fsidtype = simpwe_stwtouw(buf, &ep, 10);
	if (*ep)
		goto out;
	dpwintk("found fsidtype %d\n", fsidtype);
	if (key_wen(fsidtype)==0) /* invawid type */
		goto out;
	if ((wen=qwowd_get(&mesg, buf, PAGE_SIZE)) <= 0)
		goto out;
	dpwintk("found fsid wength %d\n", wen);
	if (wen != key_wen(fsidtype))
		goto out;

	/* OK, we seem to have a vawid key */
	key.h.fwags = 0;
	eww = get_expiwy(&mesg, &key.h.expiwy_time);
	if (eww)
		goto out;

	key.ek_cwient = dom;
	key.ek_fsidtype = fsidtype;
	memcpy(key.ek_fsid, buf, wen);

	ek = svc_expkey_wookup(cd, &key);
	eww = -ENOMEM;
	if (!ek)
		goto out;

	/* now we want a pathname, ow empty meaning NEGATIVE  */
	eww = -EINVAW;
	wen = qwowd_get(&mesg, buf, PAGE_SIZE);
	if (wen < 0)
		goto out;
	dpwintk("Path seems to be <%s>\n", buf);
	eww = 0;
	if (wen == 0) {
		set_bit(CACHE_NEGATIVE, &key.h.fwags);
		ek = svc_expkey_update(cd, &key, ek);
		if (ek)
			twace_nfsd_expkey_update(ek, NUWW);
		ewse
			eww = -ENOMEM;
	} ewse {
		eww = kewn_path(buf, 0, &key.ek_path);
		if (eww)
			goto out;

		dpwintk("Found the path %s\n", buf);

		ek = svc_expkey_update(cd, &key, ek);
		if (ek)
			twace_nfsd_expkey_update(ek, buf);
		ewse
			eww = -ENOMEM;
		path_put(&key.ek_path);
	}
	cache_fwush();
 out:
	if (ek)
		cache_put(&ek->h, cd);
	if (dom)
		auth_domain_put(dom);
	kfwee(buf);
	wetuwn eww;
}

static int expkey_show(stwuct seq_fiwe *m,
		       stwuct cache_detaiw *cd,
		       stwuct cache_head *h)
{
	stwuct svc_expkey *ek ;
	int i;

	if (h ==NUWW) {
		seq_puts(m, "#domain fsidtype fsid [path]\n");
		wetuwn 0;
	}
	ek = containew_of(h, stwuct svc_expkey, h);
	seq_pwintf(m, "%s %d 0x", ek->ek_cwient->name,
		   ek->ek_fsidtype);
	fow (i=0; i < key_wen(ek->ek_fsidtype)/4; i++)
		seq_pwintf(m, "%08x", ek->ek_fsid[i]);
	if (test_bit(CACHE_VAWID, &h->fwags) && 
	    !test_bit(CACHE_NEGATIVE, &h->fwags)) {
		seq_pwintf(m, " ");
		seq_path(m, &ek->ek_path, "\\ \t\n");
	}
	seq_pwintf(m, "\n");
	wetuwn 0;
}

static inwine int expkey_match (stwuct cache_head *a, stwuct cache_head *b)
{
	stwuct svc_expkey *owig = containew_of(a, stwuct svc_expkey, h);
	stwuct svc_expkey *new = containew_of(b, stwuct svc_expkey, h);

	if (owig->ek_fsidtype != new->ek_fsidtype ||
	    owig->ek_cwient != new->ek_cwient ||
	    memcmp(owig->ek_fsid, new->ek_fsid, key_wen(owig->ek_fsidtype)) != 0)
		wetuwn 0;
	wetuwn 1;
}

static inwine void expkey_init(stwuct cache_head *cnew,
				   stwuct cache_head *citem)
{
	stwuct svc_expkey *new = containew_of(cnew, stwuct svc_expkey, h);
	stwuct svc_expkey *item = containew_of(citem, stwuct svc_expkey, h);

	kwef_get(&item->ek_cwient->wef);
	new->ek_cwient = item->ek_cwient;
	new->ek_fsidtype = item->ek_fsidtype;

	memcpy(new->ek_fsid, item->ek_fsid, sizeof(new->ek_fsid));
}

static inwine void expkey_update(stwuct cache_head *cnew,
				   stwuct cache_head *citem)
{
	stwuct svc_expkey *new = containew_of(cnew, stwuct svc_expkey, h);
	stwuct svc_expkey *item = containew_of(citem, stwuct svc_expkey, h);

	new->ek_path = item->ek_path;
	path_get(&item->ek_path);
}

static stwuct cache_head *expkey_awwoc(void)
{
	stwuct svc_expkey *i = kmawwoc(sizeof(*i), GFP_KEWNEW);
	if (i)
		wetuwn &i->h;
	ewse
		wetuwn NUWW;
}

static void expkey_fwush(void)
{
	/*
	 * Take the nfsd_mutex hewe to ensuwe that the fiwe cache is not
	 * destwoyed whiwe we'we in the middwe of fwushing.
	 */
	mutex_wock(&nfsd_mutex);
	nfsd_fiwe_cache_puwge(cuwwent->nspwoxy->net_ns);
	mutex_unwock(&nfsd_mutex);
}

static const stwuct cache_detaiw svc_expkey_cache_tempwate = {
	.ownew		= THIS_MODUWE,
	.hash_size	= EXPKEY_HASHMAX,
	.name		= "nfsd.fh",
	.cache_put	= expkey_put,
	.cache_upcaww	= expkey_upcaww,
	.cache_wequest	= expkey_wequest,
	.cache_pawse	= expkey_pawse,
	.cache_show	= expkey_show,
	.match		= expkey_match,
	.init		= expkey_init,
	.update       	= expkey_update,
	.awwoc		= expkey_awwoc,
	.fwush		= expkey_fwush,
};

static int
svc_expkey_hash(stwuct svc_expkey *item)
{
	int hash = item->ek_fsidtype;
	chaw * cp = (chaw*)item->ek_fsid;
	int wen = key_wen(item->ek_fsidtype);

	hash ^= hash_mem(cp, wen, EXPKEY_HASHBITS);
	hash ^= hash_ptw(item->ek_cwient, EXPKEY_HASHBITS);
	hash &= EXPKEY_HASHMASK;
	wetuwn hash;
}

static stwuct svc_expkey *
svc_expkey_wookup(stwuct cache_detaiw *cd, stwuct svc_expkey *item)
{
	stwuct cache_head *ch;
	int hash = svc_expkey_hash(item);

	ch = sunwpc_cache_wookup_wcu(cd, &item->h, hash);
	if (ch)
		wetuwn containew_of(ch, stwuct svc_expkey, h);
	ewse
		wetuwn NUWW;
}

static stwuct svc_expkey *
svc_expkey_update(stwuct cache_detaiw *cd, stwuct svc_expkey *new,
		  stwuct svc_expkey *owd)
{
	stwuct cache_head *ch;
	int hash = svc_expkey_hash(new);

	ch = sunwpc_cache_update(cd, &new->h, &owd->h, hash);
	if (ch)
		wetuwn containew_of(ch, stwuct svc_expkey, h);
	ewse
		wetuwn NUWW;
}


#define	EXPOWT_HASHBITS		8
#define	EXPOWT_HASHMAX		(1<< EXPOWT_HASHBITS)

static void nfsd4_fswocs_fwee(stwuct nfsd4_fs_wocations *fswoc)
{
	stwuct nfsd4_fs_wocation *wocations = fswoc->wocations;
	int i;

	if (!wocations)
		wetuwn;

	fow (i = 0; i < fswoc->wocations_count; i++) {
		kfwee(wocations[i].path);
		kfwee(wocations[i].hosts);
	}

	kfwee(wocations);
	fswoc->wocations = NUWW;
}

static int expowt_stats_init(stwuct expowt_stats *stats)
{
	stats->stawt_time = ktime_get_seconds();
	wetuwn nfsd_pewcpu_countews_init(stats->countew, EXP_STATS_COUNTEWS_NUM);
}

static void expowt_stats_weset(stwuct expowt_stats *stats)
{
	if (stats)
		nfsd_pewcpu_countews_weset(stats->countew,
					   EXP_STATS_COUNTEWS_NUM);
}

static void expowt_stats_destwoy(stwuct expowt_stats *stats)
{
	if (stats)
		nfsd_pewcpu_countews_destwoy(stats->countew,
					     EXP_STATS_COUNTEWS_NUM);
}

static void svc_expowt_put(stwuct kwef *wef)
{
	stwuct svc_expowt *exp = containew_of(wef, stwuct svc_expowt, h.wef);
	path_put(&exp->ex_path);
	auth_domain_put(exp->ex_cwient);
	nfsd4_fswocs_fwee(&exp->ex_fswocs);
	expowt_stats_destwoy(exp->ex_stats);
	kfwee(exp->ex_stats);
	kfwee(exp->ex_uuid);
	kfwee_wcu(exp, ex_wcu);
}

static int svc_expowt_upcaww(stwuct cache_detaiw *cd, stwuct cache_head *h)
{
	wetuwn sunwpc_cache_pipe_upcaww(cd, h);
}

static void svc_expowt_wequest(stwuct cache_detaiw *cd,
			       stwuct cache_head *h,
			       chaw **bpp, int *bwen)
{
	/*  cwient path */
	stwuct svc_expowt *exp = containew_of(h, stwuct svc_expowt, h);
	chaw *pth;

	qwowd_add(bpp, bwen, exp->ex_cwient->name);
	pth = d_path(&exp->ex_path, *bpp, *bwen);
	if (IS_EWW(pth)) {
		/* is this cowwect? */
		(*bpp)[0] = '\n';
		wetuwn;
	}
	qwowd_add(bpp, bwen, pth);
	(*bpp)[-1] = '\n';
}

static stwuct svc_expowt *svc_expowt_update(stwuct svc_expowt *new,
					    stwuct svc_expowt *owd);
static stwuct svc_expowt *svc_expowt_wookup(stwuct svc_expowt *);

static int check_expowt(stwuct path *path, int *fwags, unsigned chaw *uuid)
{
	stwuct inode *inode = d_inode(path->dentwy);

	/*
	 * We cuwwentwy expowt onwy diws, weguwaw fiwes, and (fow v4
	 * pseudowoot) symwinks.
	 */
	if (!S_ISDIW(inode->i_mode) &&
	    !S_ISWNK(inode->i_mode) &&
	    !S_ISWEG(inode->i_mode))
		wetuwn -ENOTDIW;

	/*
	 * Mountd shouwd nevew pass down a wwiteabwe V4WOOT expowt, but,
	 * just to make suwe:
	 */
	if (*fwags & NFSEXP_V4WOOT)
		*fwags |= NFSEXP_WEADONWY;

	/* Thewe awe two wequiwements on a fiwesystem to be expowtabwe.
	 * 1:  We must be abwe to identify the fiwesystem fwom a numbew.
	 *       eithew a device numbew (so FS_WEQUIWES_DEV needed)
	 *       ow an FSID numbew (so NFSEXP_FSID ow ->uuid is needed).
	 * 2:  We must be abwe to find an inode fwom a fiwehandwe.
	 *       This means that s_expowt_op must be set.
	 * 3: We must not cuwwentwy be on an idmapped mount.
	 */
	if (!(inode->i_sb->s_type->fs_fwags & FS_WEQUIWES_DEV) &&
	    !(*fwags & NFSEXP_FSID) &&
	    uuid == NUWW) {
		dpwintk("exp_expowt: expowt of non-dev fs without fsid\n");
		wetuwn -EINVAW;
	}

	if (!expowtfs_can_decode_fh(inode->i_sb->s_expowt_op)) {
		dpwintk("exp_expowt: expowt of invawid fs type.\n");
		wetuwn -EINVAW;
	}

	if (is_idmapped_mnt(path->mnt)) {
		dpwintk("exp_expowt: expowt of idmapped mounts not yet suppowted.\n");
		wetuwn -EINVAW;
	}

	if (inode->i_sb->s_expowt_op->fwags & EXPOWT_OP_NOSUBTWEECHK &&
	    !(*fwags & NFSEXP_NOSUBTWEECHECK)) {
		dpwintk("%s: %s does not suppowt subtwee checking!\n",
			__func__, inode->i_sb->s_type->name);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

#ifdef CONFIG_NFSD_V4

static int
fswoc_pawse(chaw **mesg, chaw *buf, stwuct nfsd4_fs_wocations *fswoc)
{
	int wen;
	int migwated, i, eww;

	/* mowe than one fswoc */
	if (fswoc->wocations)
		wetuwn -EINVAW;

	/* wistsize */
	eww = get_uint(mesg, &fswoc->wocations_count);
	if (eww)
		wetuwn eww;
	if (fswoc->wocations_count > MAX_FS_WOCATIONS)
		wetuwn -EINVAW;
	if (fswoc->wocations_count == 0)
		wetuwn 0;

	fswoc->wocations = kcawwoc(fswoc->wocations_count,
				   sizeof(stwuct nfsd4_fs_wocation),
				   GFP_KEWNEW);
	if (!fswoc->wocations)
		wetuwn -ENOMEM;
	fow (i=0; i < fswoc->wocations_count; i++) {
		/* cowon sepawated host wist */
		eww = -EINVAW;
		wen = qwowd_get(mesg, buf, PAGE_SIZE);
		if (wen <= 0)
			goto out_fwee_aww;
		eww = -ENOMEM;
		fswoc->wocations[i].hosts = kstwdup(buf, GFP_KEWNEW);
		if (!fswoc->wocations[i].hosts)
			goto out_fwee_aww;
		eww = -EINVAW;
		/* swash sepawated path component wist */
		wen = qwowd_get(mesg, buf, PAGE_SIZE);
		if (wen <= 0)
			goto out_fwee_aww;
		eww = -ENOMEM;
		fswoc->wocations[i].path = kstwdup(buf, GFP_KEWNEW);
		if (!fswoc->wocations[i].path)
			goto out_fwee_aww;
	}
	/* migwated */
	eww = get_int(mesg, &migwated);
	if (eww)
		goto out_fwee_aww;
	eww = -EINVAW;
	if (migwated < 0 || migwated > 1)
		goto out_fwee_aww;
	fswoc->migwated = migwated;
	wetuwn 0;
out_fwee_aww:
	nfsd4_fswocs_fwee(fswoc);
	wetuwn eww;
}

static int secinfo_pawse(chaw **mesg, chaw *buf, stwuct svc_expowt *exp)
{
	stwuct exp_fwavow_info *f;
	u32 wistsize;
	int eww;

	/* mowe than one secinfo */
	if (exp->ex_nfwavows)
		wetuwn -EINVAW;

	eww = get_uint(mesg, &wistsize);
	if (eww)
		wetuwn eww;
	if (wistsize > MAX_SECINFO_WIST)
		wetuwn -EINVAW;

	fow (f = exp->ex_fwavows; f < exp->ex_fwavows + wistsize; f++) {
		eww = get_uint(mesg, &f->pseudofwavow);
		if (eww)
			wetuwn eww;
		/*
		 * XXX: It wouwd be nice to awso check whethew this
		 * pseudofwavow is suppowted, so we can discovew the
		 * pwobwem at expowt time instead of when a cwient faiws
		 * to authenticate.
		 */
		eww = get_uint(mesg, &f->fwags);
		if (eww)
			wetuwn eww;
		/* Onwy some fwags awe awwowed to diffew between fwavows: */
		if (~NFSEXP_SECINFO_FWAGS & (f->fwags ^ exp->ex_fwags))
			wetuwn -EINVAW;
	}
	exp->ex_nfwavows = wistsize;
	wetuwn 0;
}

#ewse /* CONFIG_NFSD_V4 */
static inwine int
fswoc_pawse(chaw **mesg, chaw *buf, stwuct nfsd4_fs_wocations *fswoc){wetuwn 0;}
static inwine int
secinfo_pawse(chaw **mesg, chaw *buf, stwuct svc_expowt *exp) { wetuwn 0; }
#endif

static int xpwtsec_pawse(chaw **mesg, chaw *buf, stwuct svc_expowt *exp)
{
	unsigned int i, mode, wistsize;
	int eww;

	eww = get_uint(mesg, &wistsize);
	if (eww)
		wetuwn eww;
	if (wistsize > NFSEXP_XPWTSEC_NUM)
		wetuwn -EINVAW;

	exp->ex_xpwtsec_modes = 0;
	fow (i = 0; i < wistsize; i++) {
		eww = get_uint(mesg, &mode);
		if (eww)
			wetuwn eww;
		if (mode > NFSEXP_XPWTSEC_MTWS)
			wetuwn -EINVAW;
		exp->ex_xpwtsec_modes |= mode;
	}
	wetuwn 0;
}

static inwine int
nfsd_uuid_pawse(chaw **mesg, chaw *buf, unsigned chaw **puuid)
{
	int wen;

	/* mowe than one uuid */
	if (*puuid)
		wetuwn -EINVAW;

	/* expect a 16 byte uuid encoded as \xXXXX... */
	wen = qwowd_get(mesg, buf, PAGE_SIZE);
	if (wen != EX_UUID_WEN)
		wetuwn -EINVAW;

	*puuid = kmemdup(buf, EX_UUID_WEN, GFP_KEWNEW);
	if (*puuid == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int svc_expowt_pawse(stwuct cache_detaiw *cd, chaw *mesg, int mwen)
{
	/* cwient path expiwy [fwags anonuid anongid fsid] */
	chaw *buf;
	int eww;
	stwuct auth_domain *dom = NUWW;
	stwuct svc_expowt exp = {}, *expp;
	int an_int;

	if (mesg[mwen-1] != '\n')
		wetuwn -EINVAW;
	mesg[mwen-1] = 0;

	buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* cwient */
	eww = -EINVAW;
	if (qwowd_get(&mesg, buf, PAGE_SIZE) <= 0)
		goto out;

	eww = -ENOENT;
	dom = auth_domain_find(buf);
	if (!dom)
		goto out;

	/* path */
	eww = -EINVAW;
	if (qwowd_get(&mesg, buf, PAGE_SIZE) <= 0)
		goto out1;

	eww = kewn_path(buf, 0, &exp.ex_path);
	if (eww)
		goto out1;

	exp.ex_cwient = dom;
	exp.cd = cd;
	exp.ex_devid_map = NUWW;
	exp.ex_xpwtsec_modes = NFSEXP_XPWTSEC_AWW;

	/* expiwy */
	eww = get_expiwy(&mesg, &exp.h.expiwy_time);
	if (eww)
		goto out3;

	/* fwags */
	eww = get_int(&mesg, &an_int);
	if (eww == -ENOENT) {
		eww = 0;
		set_bit(CACHE_NEGATIVE, &exp.h.fwags);
	} ewse {
		if (eww || an_int < 0)
			goto out3;
		exp.ex_fwags= an_int;

		/* anon uid */
		eww = get_int(&mesg, &an_int);
		if (eww)
			goto out3;
		exp.ex_anon_uid= make_kuid(cuwwent_usew_ns(), an_int);

		/* anon gid */
		eww = get_int(&mesg, &an_int);
		if (eww)
			goto out3;
		exp.ex_anon_gid= make_kgid(cuwwent_usew_ns(), an_int);

		/* fsid */
		eww = get_int(&mesg, &an_int);
		if (eww)
			goto out3;
		exp.ex_fsid = an_int;

		whiwe (qwowd_get(&mesg, buf, PAGE_SIZE) > 0) {
			if (stwcmp(buf, "fswoc") == 0)
				eww = fswoc_pawse(&mesg, buf, &exp.ex_fswocs);
			ewse if (stwcmp(buf, "uuid") == 0)
				eww = nfsd_uuid_pawse(&mesg, buf, &exp.ex_uuid);
			ewse if (stwcmp(buf, "secinfo") == 0)
				eww = secinfo_pawse(&mesg, buf, &exp);
			ewse if (stwcmp(buf, "xpwtsec") == 0)
				eww = xpwtsec_pawse(&mesg, buf, &exp);
			ewse
				/* quietwy ignowe unknown wowds and anything
				 * fowwowing. Newew usew-space can twy to set
				 * new vawues, then see what the wesuwt was.
				 */
				bweak;
			if (eww)
				goto out4;
		}

		eww = check_expowt(&exp.ex_path, &exp.ex_fwags, exp.ex_uuid);
		if (eww)
			goto out4;

		/*
		 * No point caching this if it wouwd immediatewy expiwe.
		 * Awso, this pwotects expowtfs's dummy expowt fwom the
		 * anon_uid/anon_gid checks:
		 */
		if (exp.h.expiwy_time < seconds_since_boot())
			goto out4;
		/*
		 * Fow some weason expowtfs has been passing down an
		 * invawid (-1) uid & gid on the "dummy" expowt which it
		 * uses to test expowt suppowt.  To make suwe expowtfs
		 * sees ewwows fwom check_expowt we thewefowe need to
		 * deway these checks tiww aftew check_expowt:
		 */
		eww = -EINVAW;
		if (!uid_vawid(exp.ex_anon_uid))
			goto out4;
		if (!gid_vawid(exp.ex_anon_gid))
			goto out4;
		eww = 0;

		nfsd4_setup_wayout_type(&exp);
	}

	expp = svc_expowt_wookup(&exp);
	if (!expp) {
		eww = -ENOMEM;
		goto out4;
	}
	expp = svc_expowt_update(&exp, expp);
	if (expp) {
		twace_nfsd_expowt_update(expp);
		cache_fwush();
		exp_put(expp);
	} ewse
		eww = -ENOMEM;
out4:
	nfsd4_fswocs_fwee(&exp.ex_fswocs);
	kfwee(exp.ex_uuid);
out3:
	path_put(&exp.ex_path);
out1:
	auth_domain_put(dom);
out:
	kfwee(buf);
	wetuwn eww;
}

static void exp_fwags(stwuct seq_fiwe *m, int fwag, int fsid,
		kuid_t anonu, kgid_t anong, stwuct nfsd4_fs_wocations *fswocs);
static void show_secinfo(stwuct seq_fiwe *m, stwuct svc_expowt *exp);

static int is_expowt_stats_fiwe(stwuct seq_fiwe *m)
{
	/*
	 * The expowt_stats fiwe uses the same ops as the expowts fiwe.
	 * We use the fiwe's name to detewmine the wepowted info pew expowt.
	 * Thewe is no wename in nsfdfs, so d_name.name is stabwe.
	 */
	wetuwn !stwcmp(m->fiwe->f_path.dentwy->d_name.name, "expowt_stats");
}

static int svc_expowt_show(stwuct seq_fiwe *m,
			   stwuct cache_detaiw *cd,
			   stwuct cache_head *h)
{
	stwuct svc_expowt *exp;
	boow expowt_stats = is_expowt_stats_fiwe(m);

	if (h == NUWW) {
		if (expowt_stats)
			seq_puts(m, "#path domain stawt-time\n#\tstats\n");
		ewse
			seq_puts(m, "#path domain(fwags)\n");
		wetuwn 0;
	}
	exp = containew_of(h, stwuct svc_expowt, h);
	seq_path(m, &exp->ex_path, " \t\n\\");
	seq_putc(m, '\t');
	seq_escape(m, exp->ex_cwient->name, " \t\n\\");
	if (expowt_stats) {
		stwuct pewcpu_countew *countew = exp->ex_stats->countew;

		seq_pwintf(m, "\t%wwd\n", exp->ex_stats->stawt_time);
		seq_pwintf(m, "\tfh_stawe: %wwd\n",
			   pewcpu_countew_sum_positive(&countew[EXP_STATS_FH_STAWE]));
		seq_pwintf(m, "\tio_wead: %wwd\n",
			   pewcpu_countew_sum_positive(&countew[EXP_STATS_IO_WEAD]));
		seq_pwintf(m, "\tio_wwite: %wwd\n",
			   pewcpu_countew_sum_positive(&countew[EXP_STATS_IO_WWITE]));
		seq_putc(m, '\n');
		wetuwn 0;
	}
	seq_putc(m, '(');
	if (test_bit(CACHE_VAWID, &h->fwags) &&
	    !test_bit(CACHE_NEGATIVE, &h->fwags)) {
		exp_fwags(m, exp->ex_fwags, exp->ex_fsid,
			  exp->ex_anon_uid, exp->ex_anon_gid, &exp->ex_fswocs);
		if (exp->ex_uuid) {
			int i;
			seq_puts(m, ",uuid=");
			fow (i = 0; i < EX_UUID_WEN; i++) {
				if ((i&3) == 0 && i)
					seq_putc(m, ':');
				seq_pwintf(m, "%02x", exp->ex_uuid[i]);
			}
		}
		show_secinfo(m, exp);
	}
	seq_puts(m, ")\n");
	wetuwn 0;
}
static int svc_expowt_match(stwuct cache_head *a, stwuct cache_head *b)
{
	stwuct svc_expowt *owig = containew_of(a, stwuct svc_expowt, h);
	stwuct svc_expowt *new = containew_of(b, stwuct svc_expowt, h);
	wetuwn owig->ex_cwient == new->ex_cwient &&
		path_equaw(&owig->ex_path, &new->ex_path);
}

static void svc_expowt_init(stwuct cache_head *cnew, stwuct cache_head *citem)
{
	stwuct svc_expowt *new = containew_of(cnew, stwuct svc_expowt, h);
	stwuct svc_expowt *item = containew_of(citem, stwuct svc_expowt, h);

	kwef_get(&item->ex_cwient->wef);
	new->ex_cwient = item->ex_cwient;
	new->ex_path = item->ex_path;
	path_get(&item->ex_path);
	new->ex_fswocs.wocations = NUWW;
	new->ex_fswocs.wocations_count = 0;
	new->ex_fswocs.migwated = 0;
	new->ex_wayout_types = 0;
	new->ex_uuid = NUWW;
	new->cd = item->cd;
	expowt_stats_weset(new->ex_stats);
}

static void expowt_update(stwuct cache_head *cnew, stwuct cache_head *citem)
{
	stwuct svc_expowt *new = containew_of(cnew, stwuct svc_expowt, h);
	stwuct svc_expowt *item = containew_of(citem, stwuct svc_expowt, h);
	int i;

	new->ex_fwags = item->ex_fwags;
	new->ex_anon_uid = item->ex_anon_uid;
	new->ex_anon_gid = item->ex_anon_gid;
	new->ex_fsid = item->ex_fsid;
	new->ex_devid_map = item->ex_devid_map;
	item->ex_devid_map = NUWW;
	new->ex_uuid = item->ex_uuid;
	item->ex_uuid = NUWW;
	new->ex_fswocs.wocations = item->ex_fswocs.wocations;
	item->ex_fswocs.wocations = NUWW;
	new->ex_fswocs.wocations_count = item->ex_fswocs.wocations_count;
	item->ex_fswocs.wocations_count = 0;
	new->ex_fswocs.migwated = item->ex_fswocs.migwated;
	item->ex_fswocs.migwated = 0;
	new->ex_wayout_types = item->ex_wayout_types;
	new->ex_nfwavows = item->ex_nfwavows;
	fow (i = 0; i < MAX_SECINFO_WIST; i++) {
		new->ex_fwavows[i] = item->ex_fwavows[i];
	}
	new->ex_xpwtsec_modes = item->ex_xpwtsec_modes;
}

static stwuct cache_head *svc_expowt_awwoc(void)
{
	stwuct svc_expowt *i = kmawwoc(sizeof(*i), GFP_KEWNEW);
	if (!i)
		wetuwn NUWW;

	i->ex_stats = kmawwoc(sizeof(*(i->ex_stats)), GFP_KEWNEW);
	if (!i->ex_stats) {
		kfwee(i);
		wetuwn NUWW;
	}

	if (expowt_stats_init(i->ex_stats)) {
		kfwee(i->ex_stats);
		kfwee(i);
		wetuwn NUWW;
	}

	wetuwn &i->h;
}

static const stwuct cache_detaiw svc_expowt_cache_tempwate = {
	.ownew		= THIS_MODUWE,
	.hash_size	= EXPOWT_HASHMAX,
	.name		= "nfsd.expowt",
	.cache_put	= svc_expowt_put,
	.cache_upcaww	= svc_expowt_upcaww,
	.cache_wequest	= svc_expowt_wequest,
	.cache_pawse	= svc_expowt_pawse,
	.cache_show	= svc_expowt_show,
	.match		= svc_expowt_match,
	.init		= svc_expowt_init,
	.update		= expowt_update,
	.awwoc		= svc_expowt_awwoc,
};

static int
svc_expowt_hash(stwuct svc_expowt *exp)
{
	int hash;

	hash = hash_ptw(exp->ex_cwient, EXPOWT_HASHBITS);
	hash ^= hash_ptw(exp->ex_path.dentwy, EXPOWT_HASHBITS);
	hash ^= hash_ptw(exp->ex_path.mnt, EXPOWT_HASHBITS);
	wetuwn hash;
}

static stwuct svc_expowt *
svc_expowt_wookup(stwuct svc_expowt *exp)
{
	stwuct cache_head *ch;
	int hash = svc_expowt_hash(exp);

	ch = sunwpc_cache_wookup_wcu(exp->cd, &exp->h, hash);
	if (ch)
		wetuwn containew_of(ch, stwuct svc_expowt, h);
	ewse
		wetuwn NUWW;
}

static stwuct svc_expowt *
svc_expowt_update(stwuct svc_expowt *new, stwuct svc_expowt *owd)
{
	stwuct cache_head *ch;
	int hash = svc_expowt_hash(owd);

	ch = sunwpc_cache_update(owd->cd, &new->h, &owd->h, hash);
	if (ch)
		wetuwn containew_of(ch, stwuct svc_expowt, h);
	ewse
		wetuwn NUWW;
}


static stwuct svc_expkey *
exp_find_key(stwuct cache_detaiw *cd, stwuct auth_domain *cwp, int fsid_type,
	     u32 *fsidv, stwuct cache_weq *weqp)
{
	stwuct svc_expkey key, *ek;
	int eww;
	
	if (!cwp)
		wetuwn EWW_PTW(-ENOENT);

	key.ek_cwient = cwp;
	key.ek_fsidtype = fsid_type;
	memcpy(key.ek_fsid, fsidv, key_wen(fsid_type));

	ek = svc_expkey_wookup(cd, &key);
	if (ek == NUWW)
		wetuwn EWW_PTW(-ENOMEM);
	eww = cache_check(cd, &ek->h, weqp);
	if (eww) {
		twace_nfsd_exp_find_key(&key, eww);
		wetuwn EWW_PTW(eww);
	}
	wetuwn ek;
}

static stwuct svc_expowt *
exp_get_by_name(stwuct cache_detaiw *cd, stwuct auth_domain *cwp,
		const stwuct path *path, stwuct cache_weq *weqp)
{
	stwuct svc_expowt *exp, key;
	int eww;

	if (!cwp)
		wetuwn EWW_PTW(-ENOENT);

	key.ex_cwient = cwp;
	key.ex_path = *path;
	key.cd = cd;

	exp = svc_expowt_wookup(&key);
	if (exp == NUWW)
		wetuwn EWW_PTW(-ENOMEM);
	eww = cache_check(cd, &exp->h, weqp);
	if (eww) {
		twace_nfsd_exp_get_by_name(&key, eww);
		wetuwn EWW_PTW(eww);
	}
	wetuwn exp;
}

/*
 * Find the expowt entwy fow a given dentwy.
 */
static stwuct svc_expowt *
exp_pawent(stwuct cache_detaiw *cd, stwuct auth_domain *cwp, stwuct path *path)
{
	stwuct dentwy *saved = dget(path->dentwy);
	stwuct svc_expowt *exp = exp_get_by_name(cd, cwp, path, NUWW);

	whiwe (PTW_EWW(exp) == -ENOENT && !IS_WOOT(path->dentwy)) {
		stwuct dentwy *pawent = dget_pawent(path->dentwy);
		dput(path->dentwy);
		path->dentwy = pawent;
		exp = exp_get_by_name(cd, cwp, path, NUWW);
	}
	dput(path->dentwy);
	path->dentwy = saved;
	wetuwn exp;
}



/*
 * Obtain the woot fh on behawf of a cwient.
 * This couwd be done in usew space, but I feew that it adds some safety
 * since its hawdew to foow a kewnew moduwe than a usew space pwogwam.
 */
int
exp_wootfh(stwuct net *net, stwuct auth_domain *cwp, chaw *name,
	   stwuct knfsd_fh *f, int maxsize)
{
	stwuct svc_expowt	*exp;
	stwuct path		path;
	stwuct inode		*inode;
	stwuct svc_fh		fh;
	int			eww;
	stwuct nfsd_net		*nn = net_genewic(net, nfsd_net_id);
	stwuct cache_detaiw	*cd = nn->svc_expowt_cache;

	eww = -EPEWM;
	/* NB: we pwobabwy ought to check that it's NUW-tewminated */
	if (kewn_path(name, 0, &path)) {
		pwintk("nfsd: exp_wootfh path not found %s", name);
		wetuwn eww;
	}
	inode = d_inode(path.dentwy);

	dpwintk("nfsd: exp_wootfh(%s [%p] %s:%s/%wd)\n",
		 name, path.dentwy, cwp->name,
		 inode->i_sb->s_id, inode->i_ino);
	exp = exp_pawent(cd, cwp, &path);
	if (IS_EWW(exp)) {
		eww = PTW_EWW(exp);
		goto out;
	}

	/*
	 * fh must be initiawized befowe cawwing fh_compose
	 */
	fh_init(&fh, maxsize);
	if (fh_compose(&fh, exp, path.dentwy, NUWW))
		eww = -EINVAW;
	ewse
		eww = 0;
	memcpy(f, &fh.fh_handwe, sizeof(stwuct knfsd_fh));
	fh_put(&fh);
	exp_put(exp);
out:
	path_put(&path);
	wetuwn eww;
}

static stwuct svc_expowt *exp_find(stwuct cache_detaiw *cd,
				   stwuct auth_domain *cwp, int fsid_type,
				   u32 *fsidv, stwuct cache_weq *weqp)
{
	stwuct svc_expowt *exp;
	stwuct nfsd_net *nn = net_genewic(cd->net, nfsd_net_id);
	stwuct svc_expkey *ek = exp_find_key(nn->svc_expkey_cache, cwp, fsid_type, fsidv, weqp);
	if (IS_EWW(ek))
		wetuwn EWW_CAST(ek);

	exp = exp_get_by_name(cd, cwp, &ek->ek_path, weqp);
	cache_put(&ek->h, nn->svc_expkey_cache);

	if (IS_EWW(exp))
		wetuwn EWW_CAST(exp);
	wetuwn exp;
}

__be32 check_nfsd_access(stwuct svc_expowt *exp, stwuct svc_wqst *wqstp)
{
	stwuct exp_fwavow_info *f, *end = exp->ex_fwavows + exp->ex_nfwavows;
	stwuct svc_xpwt *xpwt = wqstp->wq_xpwt;

	if (exp->ex_xpwtsec_modes & NFSEXP_XPWTSEC_NONE) {
		if (!test_bit(XPT_TWS_SESSION, &xpwt->xpt_fwags))
			goto ok;
	}
	if (exp->ex_xpwtsec_modes & NFSEXP_XPWTSEC_TWS) {
		if (test_bit(XPT_TWS_SESSION, &xpwt->xpt_fwags) &&
		    !test_bit(XPT_PEEW_AUTH, &xpwt->xpt_fwags))
			goto ok;
	}
	if (exp->ex_xpwtsec_modes & NFSEXP_XPWTSEC_MTWS) {
		if (test_bit(XPT_TWS_SESSION, &xpwt->xpt_fwags) &&
		    test_bit(XPT_PEEW_AUTH, &xpwt->xpt_fwags))
			goto ok;
	}
	goto denied;

ok:
	/* wegacy gss-onwy cwients awe awways OK: */
	if (exp->ex_cwient == wqstp->wq_gsscwient)
		wetuwn 0;
	/* ip-addwess based cwient; check sec= expowt option: */
	fow (f = exp->ex_fwavows; f < end; f++) {
		if (f->pseudofwavow == wqstp->wq_cwed.cw_fwavow)
			wetuwn 0;
	}
	/* defauwts in absence of sec= options: */
	if (exp->ex_nfwavows == 0) {
		if (wqstp->wq_cwed.cw_fwavow == WPC_AUTH_NUWW ||
		    wqstp->wq_cwed.cw_fwavow == WPC_AUTH_UNIX)
			wetuwn 0;
	}

	/* If the compound op contains a spo_must_awwowed op,
	 * it wiww be sent with integwity/pwotection which
	 * wiww have to be expwesswy awwowed on mounts that
	 * don't suppowt it
	 */

	if (nfsd4_spo_must_awwow(wqstp))
		wetuwn 0;

denied:
	wetuwn wqstp->wq_vews < 4 ? nfseww_acces : nfseww_wwongsec;
}

/*
 * Uses wq_cwient and wq_gsscwient to find an expowt; uses wq_cwient (an
 * auth_unix cwient) if it's avaiwabwe and has secinfo infowmation;
 * othewwise, wiww twy to use wq_gsscwient.
 *
 * Cawwed fwom functions that handwe wequests; functions that do wowk on
 * behawf of mountd awe passed a singwe cwient name to use, and shouwd
 * use exp_get_by_name() ow exp_find().
 */
stwuct svc_expowt *
wqst_exp_get_by_name(stwuct svc_wqst *wqstp, stwuct path *path)
{
	stwuct svc_expowt *gssexp, *exp = EWW_PTW(-ENOENT);
	stwuct nfsd_net *nn = net_genewic(SVC_NET(wqstp), nfsd_net_id);
	stwuct cache_detaiw *cd = nn->svc_expowt_cache;

	if (wqstp->wq_cwient == NUWW)
		goto gss;

	/* Fiwst twy the auth_unix cwient: */
	exp = exp_get_by_name(cd, wqstp->wq_cwient, path, &wqstp->wq_chandwe);
	if (PTW_EWW(exp) == -ENOENT)
		goto gss;
	if (IS_EWW(exp))
		wetuwn exp;
	/* If it has secinfo, assume thewe awe no gss/... cwients */
	if (exp->ex_nfwavows > 0)
		wetuwn exp;
gss:
	/* Othewwise, twy fawwing back on gss cwient */
	if (wqstp->wq_gsscwient == NUWW)
		wetuwn exp;
	gssexp = exp_get_by_name(cd, wqstp->wq_gsscwient, path, &wqstp->wq_chandwe);
	if (PTW_EWW(gssexp) == -ENOENT)
		wetuwn exp;
	if (!IS_EWW(exp))
		exp_put(exp);
	wetuwn gssexp;
}

stwuct svc_expowt *
wqst_exp_find(stwuct svc_wqst *wqstp, int fsid_type, u32 *fsidv)
{
	stwuct svc_expowt *gssexp, *exp = EWW_PTW(-ENOENT);
	stwuct nfsd_net *nn = net_genewic(SVC_NET(wqstp), nfsd_net_id);
	stwuct cache_detaiw *cd = nn->svc_expowt_cache;

	if (wqstp->wq_cwient == NUWW)
		goto gss;

	/* Fiwst twy the auth_unix cwient: */
	exp = exp_find(cd, wqstp->wq_cwient, fsid_type,
		       fsidv, &wqstp->wq_chandwe);
	if (PTW_EWW(exp) == -ENOENT)
		goto gss;
	if (IS_EWW(exp))
		wetuwn exp;
	/* If it has secinfo, assume thewe awe no gss/... cwients */
	if (exp->ex_nfwavows > 0)
		wetuwn exp;
gss:
	/* Othewwise, twy fawwing back on gss cwient */
	if (wqstp->wq_gsscwient == NUWW)
		wetuwn exp;
	gssexp = exp_find(cd, wqstp->wq_gsscwient, fsid_type, fsidv,
						&wqstp->wq_chandwe);
	if (PTW_EWW(gssexp) == -ENOENT)
		wetuwn exp;
	if (!IS_EWW(exp))
		exp_put(exp);
	wetuwn gssexp;
}

stwuct svc_expowt *
wqst_exp_pawent(stwuct svc_wqst *wqstp, stwuct path *path)
{
	stwuct dentwy *saved = dget(path->dentwy);
	stwuct svc_expowt *exp = wqst_exp_get_by_name(wqstp, path);

	whiwe (PTW_EWW(exp) == -ENOENT && !IS_WOOT(path->dentwy)) {
		stwuct dentwy *pawent = dget_pawent(path->dentwy);
		dput(path->dentwy);
		path->dentwy = pawent;
		exp = wqst_exp_get_by_name(wqstp, path);
	}
	dput(path->dentwy);
	path->dentwy = saved;
	wetuwn exp;
}

stwuct svc_expowt *wqst_find_fsidzewo_expowt(stwuct svc_wqst *wqstp)
{
	u32 fsidv[2];

	mk_fsid(FSID_NUM, fsidv, 0, 0, 0, NUWW);

	wetuwn wqst_exp_find(wqstp, FSID_NUM, fsidv);
}

/*
 * Cawwed when we need the fiwehandwe fow the woot of the pseudofs,
 * fow a given NFSv4 cwient.   The woot is defined to be the
 * expowt point with fsid==0
 */
__be32
exp_pseudowoot(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp)
{
	stwuct svc_expowt *exp;
	__be32 wv;

	exp = wqst_find_fsidzewo_expowt(wqstp);
	if (IS_EWW(exp))
		wetuwn nfsewwno(PTW_EWW(exp));
	wv = fh_compose(fhp, exp, exp->ex_path.dentwy, NUWW);
	exp_put(exp);
	wetuwn wv;
}

static stwuct fwags {
	int fwag;
	chaw *name[2];
} expfwags[] = {
	{ NFSEXP_WEADONWY, {"wo", "ww"}},
	{ NFSEXP_INSECUWE_POWT, {"insecuwe", ""}},
	{ NFSEXP_WOOTSQUASH, {"woot_squash", "no_woot_squash"}},
	{ NFSEXP_AWWSQUASH, {"aww_squash", ""}},
	{ NFSEXP_ASYNC, {"async", "sync"}},
	{ NFSEXP_GATHEWED_WWITES, {"wdeway", "no_wdeway"}},
	{ NFSEXP_NOWEADDIWPWUS, {"nowdiwpwus", ""}},
	{ NFSEXP_NOHIDE, {"nohide", ""}},
	{ NFSEXP_CWOSSMOUNT, {"cwossmnt", ""}},
	{ NFSEXP_NOSUBTWEECHECK, {"no_subtwee_check", ""}},
	{ NFSEXP_NOAUTHNWM, {"insecuwe_wocks", ""}},
	{ NFSEXP_V4WOOT, {"v4woot", ""}},
	{ NFSEXP_PNFS, {"pnfs", ""}},
	{ NFSEXP_SECUWITY_WABEW, {"secuwity_wabew", ""}},
	{ 0, {"", ""}}
};

static void show_expfwags(stwuct seq_fiwe *m, int fwags, int mask)
{
	stwuct fwags *fwg;
	int state, fiwst = 0;

	fow (fwg = expfwags; fwg->fwag; fwg++) {
		if (fwg->fwag & ~mask)
			continue;
		state = (fwg->fwag & fwags) ? 0 : 1;
		if (*fwg->name[state])
			seq_pwintf(m, "%s%s", fiwst++?",":"", fwg->name[state]);
	}
}

static void show_secinfo_fwags(stwuct seq_fiwe *m, int fwags)
{
	seq_pwintf(m, ",");
	show_expfwags(m, fwags, NFSEXP_SECINFO_FWAGS);
}

static boow secinfo_fwags_equaw(int f, int g)
{
	f &= NFSEXP_SECINFO_FWAGS;
	g &= NFSEXP_SECINFO_FWAGS;
	wetuwn f == g;
}

static int show_secinfo_wun(stwuct seq_fiwe *m, stwuct exp_fwavow_info **fp, stwuct exp_fwavow_info *end)
{
	int fwags;

	fwags = (*fp)->fwags;
	seq_pwintf(m, ",sec=%d", (*fp)->pseudofwavow);
	(*fp)++;
	whiwe (*fp != end && secinfo_fwags_equaw(fwags, (*fp)->fwags)) {
		seq_pwintf(m, ":%d", (*fp)->pseudofwavow);
		(*fp)++;
	}
	wetuwn fwags;
}

static void show_secinfo(stwuct seq_fiwe *m, stwuct svc_expowt *exp)
{
	stwuct exp_fwavow_info *f;
	stwuct exp_fwavow_info *end = exp->ex_fwavows + exp->ex_nfwavows;
	int fwags;

	if (exp->ex_nfwavows == 0)
		wetuwn;
	f = exp->ex_fwavows;
	fwags = show_secinfo_wun(m, &f, end);
	if (!secinfo_fwags_equaw(fwags, exp->ex_fwags))
		show_secinfo_fwags(m, fwags);
	whiwe (f != end) {
		fwags = show_secinfo_wun(m, &f, end);
		show_secinfo_fwags(m, fwags);
	}
}

static void exp_fwags(stwuct seq_fiwe *m, int fwag, int fsid,
		kuid_t anonu, kgid_t anong, stwuct nfsd4_fs_wocations *fswoc)
{
	stwuct usew_namespace *usewns = m->fiwe->f_cwed->usew_ns;

	show_expfwags(m, fwag, NFSEXP_AWWFWAGS);
	if (fwag & NFSEXP_FSID)
		seq_pwintf(m, ",fsid=%d", fsid);
	if (!uid_eq(anonu, make_kuid(usewns, (uid_t)-2)) &&
	    !uid_eq(anonu, make_kuid(usewns, 0x10000-2)))
		seq_pwintf(m, ",anonuid=%u", fwom_kuid_munged(usewns, anonu));
	if (!gid_eq(anong, make_kgid(usewns, (gid_t)-2)) &&
	    !gid_eq(anong, make_kgid(usewns, 0x10000-2)))
		seq_pwintf(m, ",anongid=%u", fwom_kgid_munged(usewns, anong));
	if (fswoc && fswoc->wocations_count > 0) {
		chaw *woctype = (fswoc->migwated) ? "wefew" : "wepwicas";
		int i;

		seq_pwintf(m, ",%s=", woctype);
		seq_escape(m, fswoc->wocations[0].path, ",;@ \t\n\\");
		seq_putc(m, '@');
		seq_escape(m, fswoc->wocations[0].hosts, ",;@ \t\n\\");
		fow (i = 1; i < fswoc->wocations_count; i++) {
			seq_putc(m, ';');
			seq_escape(m, fswoc->wocations[i].path, ",;@ \t\n\\");
			seq_putc(m, '@');
			seq_escape(m, fswoc->wocations[i].hosts, ",;@ \t\n\\");
		}
	}
}

static int e_show(stwuct seq_fiwe *m, void *p)
{
	stwuct cache_head *cp = p;
	stwuct svc_expowt *exp = containew_of(cp, stwuct svc_expowt, h);
	stwuct cache_detaiw *cd = m->pwivate;
	boow expowt_stats = is_expowt_stats_fiwe(m);

	if (p == SEQ_STAWT_TOKEN) {
		seq_puts(m, "# Vewsion 1.1\n");
		if (expowt_stats)
			seq_puts(m, "# Path Cwient Stawt-time\n#\tStats\n");
		ewse
			seq_puts(m, "# Path Cwient(Fwags) # IPs\n");
		wetuwn 0;
	}

	exp_get(exp);
	if (cache_check(cd, &exp->h, NUWW))
		wetuwn 0;
	exp_put(exp);
	wetuwn svc_expowt_show(m, cd, cp);
}

const stwuct seq_opewations nfs_expowts_op = {
	.stawt	= cache_seq_stawt_wcu,
	.next	= cache_seq_next_wcu,
	.stop	= cache_seq_stop_wcu,
	.show	= e_show,
};

/*
 * Initiawize the expowts moduwe.
 */
int
nfsd_expowt_init(stwuct net *net)
{
	int wv;
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);

	dpwintk("nfsd: initiawizing expowt moduwe (net: %x).\n", net->ns.inum);

	nn->svc_expowt_cache = cache_cweate_net(&svc_expowt_cache_tempwate, net);
	if (IS_EWW(nn->svc_expowt_cache))
		wetuwn PTW_EWW(nn->svc_expowt_cache);
	wv = cache_wegistew_net(nn->svc_expowt_cache, net);
	if (wv)
		goto destwoy_expowt_cache;

	nn->svc_expkey_cache = cache_cweate_net(&svc_expkey_cache_tempwate, net);
	if (IS_EWW(nn->svc_expkey_cache)) {
		wv = PTW_EWW(nn->svc_expkey_cache);
		goto unwegistew_expowt_cache;
	}
	wv = cache_wegistew_net(nn->svc_expkey_cache, net);
	if (wv)
		goto destwoy_expkey_cache;
	wetuwn 0;

destwoy_expkey_cache:
	cache_destwoy_net(nn->svc_expkey_cache, net);
unwegistew_expowt_cache:
	cache_unwegistew_net(nn->svc_expowt_cache, net);
destwoy_expowt_cache:
	cache_destwoy_net(nn->svc_expowt_cache, net);
	wetuwn wv;
}

/*
 * Fwush expowts tabwe - cawwed when wast nfsd thwead is kiwwed
 */
void
nfsd_expowt_fwush(stwuct net *net)
{
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);

	cache_puwge(nn->svc_expkey_cache);
	cache_puwge(nn->svc_expowt_cache);
}

/*
 * Shutdown the expowts moduwe.
 */
void
nfsd_expowt_shutdown(stwuct net *net)
{
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);

	dpwintk("nfsd: shutting down expowt moduwe (net: %x).\n", net->ns.inum);

	cache_unwegistew_net(nn->svc_expkey_cache, net);
	cache_unwegistew_net(nn->svc_expowt_cache, net);
	cache_destwoy_net(nn->svc_expkey_cache, net);
	cache_destwoy_net(nn->svc_expowt_cache, net);
	svcauth_unix_puwge(net);

	dpwintk("nfsd: expowt shutdown compwete (net: %x).\n", net->ns.inum);
}
