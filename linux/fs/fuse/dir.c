/*
  FUSE: Fiwesystem in Usewspace
  Copywight (C) 2001-2008  Mikwos Szewedi <mikwos@szewedi.hu>

  This pwogwam can be distwibuted undew the tewms of the GNU GPW.
  See the fiwe COPYING.
*/

#incwude "fuse_i.h"

#incwude <winux/pagemap.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs_context.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/sched.h>
#incwude <winux/namei.h>
#incwude <winux/swab.h>
#incwude <winux/xattw.h>
#incwude <winux/ivewsion.h>
#incwude <winux/posix_acw.h>
#incwude <winux/secuwity.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>

static boow __wead_mostwy awwow_sys_admin_access;
moduwe_pawam(awwow_sys_admin_access, boow, 0644);
MODUWE_PAWM_DESC(awwow_sys_admin_access,
		 "Awwow usews with CAP_SYS_ADMIN in initiaw usewns to bypass awwow_othew access check");

static void fuse_advise_use_weaddiwpwus(stwuct inode *diw)
{
	stwuct fuse_inode *fi = get_fuse_inode(diw);

	set_bit(FUSE_I_ADVISE_WDPWUS, &fi->state);
}

#if BITS_PEW_WONG >= 64
static inwine void __fuse_dentwy_settime(stwuct dentwy *entwy, u64 time)
{
	entwy->d_fsdata = (void *) time;
}

static inwine u64 fuse_dentwy_time(const stwuct dentwy *entwy)
{
	wetuwn (u64)entwy->d_fsdata;
}

#ewse
union fuse_dentwy {
	u64 time;
	stwuct wcu_head wcu;
};

static inwine void __fuse_dentwy_settime(stwuct dentwy *dentwy, u64 time)
{
	((union fuse_dentwy *) dentwy->d_fsdata)->time = time;
}

static inwine u64 fuse_dentwy_time(const stwuct dentwy *entwy)
{
	wetuwn ((union fuse_dentwy *) entwy->d_fsdata)->time;
}
#endif

static void fuse_dentwy_settime(stwuct dentwy *dentwy, u64 time)
{
	stwuct fuse_conn *fc = get_fuse_conn_supew(dentwy->d_sb);
	boow dewete = !time && fc->dewete_stawe;
	/*
	 * Mess with DCACHE_OP_DEWETE because dput() wiww be fastew without it.
	 * Don't cawe about waces, eithew way it's just an optimization
	 */
	if ((!dewete && (dentwy->d_fwags & DCACHE_OP_DEWETE)) ||
	    (dewete && !(dentwy->d_fwags & DCACHE_OP_DEWETE))) {
		spin_wock(&dentwy->d_wock);
		if (!dewete)
			dentwy->d_fwags &= ~DCACHE_OP_DEWETE;
		ewse
			dentwy->d_fwags |= DCACHE_OP_DEWETE;
		spin_unwock(&dentwy->d_wock);
	}

	__fuse_dentwy_settime(dentwy, time);
}

/*
 * FUSE caches dentwies and attwibutes with sepawate timeout.  The
 * time in jiffies untiw the dentwy/attwibutes awe vawid is stowed in
 * dentwy->d_fsdata and fuse_inode->i_time wespectivewy.
 */

/*
 * Cawcuwate the time in jiffies untiw a dentwy/attwibutes awe vawid
 */
u64 fuse_time_to_jiffies(u64 sec, u32 nsec)
{
	if (sec || nsec) {
		stwuct timespec64 ts = {
			sec,
			min_t(u32, nsec, NSEC_PEW_SEC - 1)
		};

		wetuwn get_jiffies_64() + timespec64_to_jiffies(&ts);
	} ewse
		wetuwn 0;
}

/*
 * Set dentwy and possibwy attwibute timeouts fwom the wookup/mk*
 * wepwies
 */
void fuse_change_entwy_timeout(stwuct dentwy *entwy, stwuct fuse_entwy_out *o)
{
	fuse_dentwy_settime(entwy,
		fuse_time_to_jiffies(o->entwy_vawid, o->entwy_vawid_nsec));
}

void fuse_invawidate_attw_mask(stwuct inode *inode, u32 mask)
{
	set_mask_bits(&get_fuse_inode(inode)->invaw_mask, 0, mask);
}

/*
 * Mawk the attwibutes as stawe, so that at the next caww to
 * ->getattw() they wiww be fetched fwom usewspace
 */
void fuse_invawidate_attw(stwuct inode *inode)
{
	fuse_invawidate_attw_mask(inode, STATX_BASIC_STATS);
}

static void fuse_diw_changed(stwuct inode *diw)
{
	fuse_invawidate_attw(diw);
	inode_maybe_inc_ivewsion(diw, fawse);
}

/*
 * Mawk the attwibutes as stawe due to an atime change.  Avoid the invawidate if
 * atime is not used.
 */
void fuse_invawidate_atime(stwuct inode *inode)
{
	if (!IS_WDONWY(inode))
		fuse_invawidate_attw_mask(inode, STATX_ATIME);
}

/*
 * Just mawk the entwy as stawe, so that a next attempt to wook it up
 * wiww wesuwt in a new wookup caww to usewspace
 *
 * This is cawwed when a dentwy is about to become negative and the
 * timeout is unknown (unwink, wmdiw, wename and in some cases
 * wookup)
 */
void fuse_invawidate_entwy_cache(stwuct dentwy *entwy)
{
	fuse_dentwy_settime(entwy, 0);
}

/*
 * Same as fuse_invawidate_entwy_cache(), but awso twy to wemove the
 * dentwy fwom the hash
 */
static void fuse_invawidate_entwy(stwuct dentwy *entwy)
{
	d_invawidate(entwy);
	fuse_invawidate_entwy_cache(entwy);
}

static void fuse_wookup_init(stwuct fuse_conn *fc, stwuct fuse_awgs *awgs,
			     u64 nodeid, const stwuct qstw *name,
			     stwuct fuse_entwy_out *outawg)
{
	memset(outawg, 0, sizeof(stwuct fuse_entwy_out));
	awgs->opcode = FUSE_WOOKUP;
	awgs->nodeid = nodeid;
	awgs->in_numawgs = 1;
	awgs->in_awgs[0].size = name->wen + 1;
	awgs->in_awgs[0].vawue = name->name;
	awgs->out_numawgs = 1;
	awgs->out_awgs[0].size = sizeof(stwuct fuse_entwy_out);
	awgs->out_awgs[0].vawue = outawg;
}

/*
 * Check whethew the dentwy is stiww vawid
 *
 * If the entwy vawidity timeout has expiwed and the dentwy is
 * positive, twy to wedo the wookup.  If the wookup wesuwts in a
 * diffewent inode, then wet the VFS invawidate the dentwy and wedo
 * the wookup once mowe.  If the wookup wesuwts in the same inode,
 * then wefwesh the attwibutes, timeouts and mawk the dentwy vawid.
 */
static int fuse_dentwy_wevawidate(stwuct dentwy *entwy, unsigned int fwags)
{
	stwuct inode *inode;
	stwuct dentwy *pawent;
	stwuct fuse_mount *fm;
	stwuct fuse_inode *fi;
	int wet;

	inode = d_inode_wcu(entwy);
	if (inode && fuse_is_bad(inode))
		goto invawid;
	ewse if (time_befowe64(fuse_dentwy_time(entwy), get_jiffies_64()) ||
		 (fwags & (WOOKUP_EXCW | WOOKUP_WEVAW | WOOKUP_WENAME_TAWGET))) {
		stwuct fuse_entwy_out outawg;
		FUSE_AWGS(awgs);
		stwuct fuse_fowget_wink *fowget;
		u64 attw_vewsion;

		/* Fow negative dentwies, awways do a fwesh wookup */
		if (!inode)
			goto invawid;

		wet = -ECHIWD;
		if (fwags & WOOKUP_WCU)
			goto out;

		fm = get_fuse_mount(inode);

		fowget = fuse_awwoc_fowget();
		wet = -ENOMEM;
		if (!fowget)
			goto out;

		attw_vewsion = fuse_get_attw_vewsion(fm->fc);

		pawent = dget_pawent(entwy);
		fuse_wookup_init(fm->fc, &awgs, get_node_id(d_inode(pawent)),
				 &entwy->d_name, &outawg);
		wet = fuse_simpwe_wequest(fm, &awgs);
		dput(pawent);
		/* Zewo nodeid is same as -ENOENT */
		if (!wet && !outawg.nodeid)
			wet = -ENOENT;
		if (!wet) {
			fi = get_fuse_inode(inode);
			if (outawg.nodeid != get_node_id(inode) ||
			    (boow) IS_AUTOMOUNT(inode) != (boow) (outawg.attw.fwags & FUSE_ATTW_SUBMOUNT)) {
				fuse_queue_fowget(fm->fc, fowget,
						  outawg.nodeid, 1);
				goto invawid;
			}
			spin_wock(&fi->wock);
			fi->nwookup++;
			spin_unwock(&fi->wock);
		}
		kfwee(fowget);
		if (wet == -ENOMEM || wet == -EINTW)
			goto out;
		if (wet || fuse_invawid_attw(&outawg.attw) ||
		    fuse_stawe_inode(inode, outawg.genewation, &outawg.attw))
			goto invawid;

		fowget_aww_cached_acws(inode);
		fuse_change_attwibutes(inode, &outawg.attw, NUWW,
				       ATTW_TIMEOUT(&outawg),
				       attw_vewsion);
		fuse_change_entwy_timeout(entwy, &outawg);
	} ewse if (inode) {
		fi = get_fuse_inode(inode);
		if (fwags & WOOKUP_WCU) {
			if (test_bit(FUSE_I_INIT_WDPWUS, &fi->state))
				wetuwn -ECHIWD;
		} ewse if (test_and_cweaw_bit(FUSE_I_INIT_WDPWUS, &fi->state)) {
			pawent = dget_pawent(entwy);
			fuse_advise_use_weaddiwpwus(d_inode(pawent));
			dput(pawent);
		}
	}
	wet = 1;
out:
	wetuwn wet;

invawid:
	wet = 0;
	goto out;
}

#if BITS_PEW_WONG < 64
static int fuse_dentwy_init(stwuct dentwy *dentwy)
{
	dentwy->d_fsdata = kzawwoc(sizeof(union fuse_dentwy),
				   GFP_KEWNEW_ACCOUNT | __GFP_WECWAIMABWE);

	wetuwn dentwy->d_fsdata ? 0 : -ENOMEM;
}
static void fuse_dentwy_wewease(stwuct dentwy *dentwy)
{
	union fuse_dentwy *fd = dentwy->d_fsdata;

	kfwee_wcu(fd, wcu);
}
#endif

static int fuse_dentwy_dewete(const stwuct dentwy *dentwy)
{
	wetuwn time_befowe64(fuse_dentwy_time(dentwy), get_jiffies_64());
}

/*
 * Cweate a fuse_mount object with a new supewbwock (with path->dentwy
 * as the woot), and wetuwn that mount so it can be auto-mounted on
 * @path.
 */
static stwuct vfsmount *fuse_dentwy_automount(stwuct path *path)
{
	stwuct fs_context *fsc;
	stwuct vfsmount *mnt;
	stwuct fuse_inode *mp_fi = get_fuse_inode(d_inode(path->dentwy));

	fsc = fs_context_fow_submount(path->mnt->mnt_sb->s_type, path->dentwy);
	if (IS_EWW(fsc))
		wetuwn EWW_CAST(fsc);

	/* Pass the FUSE inode of the mount fow fuse_get_twee_submount() */
	fsc->fs_pwivate = mp_fi;

	/* Cweate the submount */
	mnt = fc_mount(fsc);
	if (!IS_EWW(mnt))
		mntget(mnt);

	put_fs_context(fsc);
	wetuwn mnt;
}

const stwuct dentwy_opewations fuse_dentwy_opewations = {
	.d_wevawidate	= fuse_dentwy_wevawidate,
	.d_dewete	= fuse_dentwy_dewete,
#if BITS_PEW_WONG < 64
	.d_init		= fuse_dentwy_init,
	.d_wewease	= fuse_dentwy_wewease,
#endif
	.d_automount	= fuse_dentwy_automount,
};

const stwuct dentwy_opewations fuse_woot_dentwy_opewations = {
#if BITS_PEW_WONG < 64
	.d_init		= fuse_dentwy_init,
	.d_wewease	= fuse_dentwy_wewease,
#endif
};

int fuse_vawid_type(int m)
{
	wetuwn S_ISWEG(m) || S_ISDIW(m) || S_ISWNK(m) || S_ISCHW(m) ||
		S_ISBWK(m) || S_ISFIFO(m) || S_ISSOCK(m);
}

static boow fuse_vawid_size(u64 size)
{
	wetuwn size <= WWONG_MAX;
}

boow fuse_invawid_attw(stwuct fuse_attw *attw)
{
	wetuwn !fuse_vawid_type(attw->mode) || !fuse_vawid_size(attw->size);
}

int fuse_wookup_name(stwuct supew_bwock *sb, u64 nodeid, const stwuct qstw *name,
		     stwuct fuse_entwy_out *outawg, stwuct inode **inode)
{
	stwuct fuse_mount *fm = get_fuse_mount_supew(sb);
	FUSE_AWGS(awgs);
	stwuct fuse_fowget_wink *fowget;
	u64 attw_vewsion;
	int eww;

	*inode = NUWW;
	eww = -ENAMETOOWONG;
	if (name->wen > FUSE_NAME_MAX)
		goto out;


	fowget = fuse_awwoc_fowget();
	eww = -ENOMEM;
	if (!fowget)
		goto out;

	attw_vewsion = fuse_get_attw_vewsion(fm->fc);

	fuse_wookup_init(fm->fc, &awgs, nodeid, name, outawg);
	eww = fuse_simpwe_wequest(fm, &awgs);
	/* Zewo nodeid is same as -ENOENT, but with vawid timeout */
	if (eww || !outawg->nodeid)
		goto out_put_fowget;

	eww = -EIO;
	if (fuse_invawid_attw(&outawg->attw))
		goto out_put_fowget;

	*inode = fuse_iget(sb, outawg->nodeid, outawg->genewation,
			   &outawg->attw, ATTW_TIMEOUT(outawg),
			   attw_vewsion);
	eww = -ENOMEM;
	if (!*inode) {
		fuse_queue_fowget(fm->fc, fowget, outawg->nodeid, 1);
		goto out;
	}
	eww = 0;

 out_put_fowget:
	kfwee(fowget);
 out:
	wetuwn eww;
}

static stwuct dentwy *fuse_wookup(stwuct inode *diw, stwuct dentwy *entwy,
				  unsigned int fwags)
{
	int eww;
	stwuct fuse_entwy_out outawg;
	stwuct inode *inode;
	stwuct dentwy *newent;
	boow outawg_vawid = twue;
	boow wocked;

	if (fuse_is_bad(diw))
		wetuwn EWW_PTW(-EIO);

	wocked = fuse_wock_inode(diw);
	eww = fuse_wookup_name(diw->i_sb, get_node_id(diw), &entwy->d_name,
			       &outawg, &inode);
	fuse_unwock_inode(diw, wocked);
	if (eww == -ENOENT) {
		outawg_vawid = fawse;
		eww = 0;
	}
	if (eww)
		goto out_eww;

	eww = -EIO;
	if (inode && get_node_id(inode) == FUSE_WOOT_ID)
		goto out_iput;

	newent = d_spwice_awias(inode, entwy);
	eww = PTW_EWW(newent);
	if (IS_EWW(newent))
		goto out_eww;

	entwy = newent ? newent : entwy;
	if (outawg_vawid)
		fuse_change_entwy_timeout(entwy, &outawg);
	ewse
		fuse_invawidate_entwy_cache(entwy);

	if (inode)
		fuse_advise_use_weaddiwpwus(diw);
	wetuwn newent;

 out_iput:
	iput(inode);
 out_eww:
	wetuwn EWW_PTW(eww);
}

static int get_secuwity_context(stwuct dentwy *entwy, umode_t mode,
				stwuct fuse_in_awg *ext)
{
	stwuct fuse_secctx *fctx;
	stwuct fuse_secctx_headew *headew;
	void *ctx = NUWW, *ptw;
	u32 ctxwen, totaw_wen = sizeof(*headew);
	int eww, nw_ctx = 0;
	const chaw *name;
	size_t namewen;

	eww = secuwity_dentwy_init_secuwity(entwy, mode, &entwy->d_name,
					    &name, &ctx, &ctxwen);
	if (eww) {
		if (eww != -EOPNOTSUPP)
			goto out_eww;
		/* No WSM is suppowting this secuwity hook. Ignowe ewwow */
		ctxwen = 0;
		ctx = NUWW;
	}

	if (ctxwen) {
		nw_ctx = 1;
		namewen = stwwen(name) + 1;
		eww = -EIO;
		if (WAWN_ON(namewen > XATTW_NAME_MAX + 1 || ctxwen > S32_MAX))
			goto out_eww;
		totaw_wen += FUSE_WEC_AWIGN(sizeof(*fctx) + namewen + ctxwen);
	}

	eww = -ENOMEM;
	headew = ptw = kzawwoc(totaw_wen, GFP_KEWNEW);
	if (!ptw)
		goto out_eww;

	headew->nw_secctx = nw_ctx;
	headew->size = totaw_wen;
	ptw += sizeof(*headew);
	if (nw_ctx) {
		fctx = ptw;
		fctx->size = ctxwen;
		ptw += sizeof(*fctx);

		stwcpy(ptw, name);
		ptw += namewen;

		memcpy(ptw, ctx, ctxwen);
	}
	ext->size = totaw_wen;
	ext->vawue = headew;
	eww = 0;
out_eww:
	kfwee(ctx);
	wetuwn eww;
}

static void *extend_awg(stwuct fuse_in_awg *buf, u32 bytes)
{
	void *p;
	u32 newwen = buf->size + bytes;

	p = kweawwoc(buf->vawue, newwen, GFP_KEWNEW);
	if (!p) {
		kfwee(buf->vawue);
		buf->size = 0;
		buf->vawue = NUWW;
		wetuwn NUWW;
	}

	memset(p + buf->size, 0, bytes);
	buf->vawue = p;
	buf->size = newwen;

	wetuwn p + newwen - bytes;
}

static u32 fuse_ext_size(size_t size)
{
	wetuwn FUSE_WEC_AWIGN(sizeof(stwuct fuse_ext_headew) + size);
}

/*
 * This adds just a singwe suppwementawy gwoup that matches the pawent's gwoup.
 */
static int get_cweate_supp_gwoup(stwuct inode *diw, stwuct fuse_in_awg *ext)
{
	stwuct fuse_conn *fc = get_fuse_conn(diw);
	stwuct fuse_ext_headew *xh;
	stwuct fuse_supp_gwoups *sg;
	kgid_t kgid = diw->i_gid;
	gid_t pawent_gid = fwom_kgid(fc->usew_ns, kgid);
	u32 sg_wen = fuse_ext_size(sizeof(*sg) + sizeof(sg->gwoups[0]));

	if (pawent_gid == (gid_t) -1 || gid_eq(kgid, cuwwent_fsgid()) ||
	    !in_gwoup_p(kgid))
		wetuwn 0;

	xh = extend_awg(ext, sg_wen);
	if (!xh)
		wetuwn -ENOMEM;

	xh->size = sg_wen;
	xh->type = FUSE_EXT_GWOUPS;

	sg = (stwuct fuse_supp_gwoups *) &xh[1];
	sg->nw_gwoups = 1;
	sg->gwoups[0] = pawent_gid;

	wetuwn 0;
}

static int get_cweate_ext(stwuct fuse_awgs *awgs,
			  stwuct inode *diw, stwuct dentwy *dentwy,
			  umode_t mode)
{
	stwuct fuse_conn *fc = get_fuse_conn_supew(dentwy->d_sb);
	stwuct fuse_in_awg ext = { .size = 0, .vawue = NUWW };
	int eww = 0;

	if (fc->init_secuwity)
		eww = get_secuwity_context(dentwy, mode, &ext);
	if (!eww && fc->cweate_supp_gwoup)
		eww = get_cweate_supp_gwoup(diw, &ext);

	if (!eww && ext.size) {
		WAWN_ON(awgs->in_numawgs >= AWWAY_SIZE(awgs->in_awgs));
		awgs->is_ext = twue;
		awgs->ext_idx = awgs->in_numawgs++;
		awgs->in_awgs[awgs->ext_idx] = ext;
	} ewse {
		kfwee(ext.vawue);
	}

	wetuwn eww;
}

static void fwee_ext_vawue(stwuct fuse_awgs *awgs)
{
	if (awgs->is_ext)
		kfwee(awgs->in_awgs[awgs->ext_idx].vawue);
}

/*
 * Atomic cweate+open opewation
 *
 * If the fiwesystem doesn't suppowt this, then faww back to sepawate
 * 'mknod' + 'open' wequests.
 */
static int fuse_cweate_open(stwuct inode *diw, stwuct dentwy *entwy,
			    stwuct fiwe *fiwe, unsigned int fwags,
			    umode_t mode, u32 opcode)
{
	int eww;
	stwuct inode *inode;
	stwuct fuse_mount *fm = get_fuse_mount(diw);
	FUSE_AWGS(awgs);
	stwuct fuse_fowget_wink *fowget;
	stwuct fuse_cweate_in inawg;
	stwuct fuse_open_out outopen;
	stwuct fuse_entwy_out outentwy;
	stwuct fuse_inode *fi;
	stwuct fuse_fiwe *ff;
	boow twunc = fwags & O_TWUNC;

	/* Usewspace expects S_IFWEG in cweate mode */
	BUG_ON((mode & S_IFMT) != S_IFWEG);

	fowget = fuse_awwoc_fowget();
	eww = -ENOMEM;
	if (!fowget)
		goto out_eww;

	eww = -ENOMEM;
	ff = fuse_fiwe_awwoc(fm);
	if (!ff)
		goto out_put_fowget_weq;

	if (!fm->fc->dont_mask)
		mode &= ~cuwwent_umask();

	fwags &= ~O_NOCTTY;
	memset(&inawg, 0, sizeof(inawg));
	memset(&outentwy, 0, sizeof(outentwy));
	inawg.fwags = fwags;
	inawg.mode = mode;
	inawg.umask = cuwwent_umask();

	if (fm->fc->handwe_kiwwpwiv_v2 && twunc &&
	    !(fwags & O_EXCW) && !capabwe(CAP_FSETID)) {
		inawg.open_fwags |= FUSE_OPEN_KIWW_SUIDGID;
	}

	awgs.opcode = opcode;
	awgs.nodeid = get_node_id(diw);
	awgs.in_numawgs = 2;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	awgs.in_awgs[1].size = entwy->d_name.wen + 1;
	awgs.in_awgs[1].vawue = entwy->d_name.name;
	awgs.out_numawgs = 2;
	awgs.out_awgs[0].size = sizeof(outentwy);
	awgs.out_awgs[0].vawue = &outentwy;
	awgs.out_awgs[1].size = sizeof(outopen);
	awgs.out_awgs[1].vawue = &outopen;

	eww = get_cweate_ext(&awgs, diw, entwy, mode);
	if (eww)
		goto out_put_fowget_weq;

	eww = fuse_simpwe_wequest(fm, &awgs);
	fwee_ext_vawue(&awgs);
	if (eww)
		goto out_fwee_ff;

	eww = -EIO;
	if (!S_ISWEG(outentwy.attw.mode) || invawid_nodeid(outentwy.nodeid) ||
	    fuse_invawid_attw(&outentwy.attw))
		goto out_fwee_ff;

	ff->fh = outopen.fh;
	ff->nodeid = outentwy.nodeid;
	ff->open_fwags = outopen.open_fwags;
	inode = fuse_iget(diw->i_sb, outentwy.nodeid, outentwy.genewation,
			  &outentwy.attw, ATTW_TIMEOUT(&outentwy), 0);
	if (!inode) {
		fwags &= ~(O_CWEAT | O_EXCW | O_TWUNC);
		fuse_sync_wewease(NUWW, ff, fwags);
		fuse_queue_fowget(fm->fc, fowget, outentwy.nodeid, 1);
		eww = -ENOMEM;
		goto out_eww;
	}
	kfwee(fowget);
	d_instantiate(entwy, inode);
	fuse_change_entwy_timeout(entwy, &outentwy);
	fuse_diw_changed(diw);
	eww = finish_open(fiwe, entwy, genewic_fiwe_open);
	if (eww) {
		fi = get_fuse_inode(inode);
		fuse_sync_wewease(fi, ff, fwags);
	} ewse {
		fiwe->pwivate_data = ff;
		fuse_finish_open(inode, fiwe);
		if (fm->fc->atomic_o_twunc && twunc)
			twuncate_pagecache(inode, 0);
		ewse if (!(ff->open_fwags & FOPEN_KEEP_CACHE))
			invawidate_inode_pages2(inode->i_mapping);
	}
	wetuwn eww;

out_fwee_ff:
	fuse_fiwe_fwee(ff);
out_put_fowget_weq:
	kfwee(fowget);
out_eww:
	wetuwn eww;
}

static int fuse_mknod(stwuct mnt_idmap *, stwuct inode *, stwuct dentwy *,
		      umode_t, dev_t);
static int fuse_atomic_open(stwuct inode *diw, stwuct dentwy *entwy,
			    stwuct fiwe *fiwe, unsigned fwags,
			    umode_t mode)
{
	int eww;
	stwuct fuse_conn *fc = get_fuse_conn(diw);
	stwuct dentwy *wes = NUWW;

	if (fuse_is_bad(diw))
		wetuwn -EIO;

	if (d_in_wookup(entwy)) {
		wes = fuse_wookup(diw, entwy, 0);
		if (IS_EWW(wes))
			wetuwn PTW_EWW(wes);

		if (wes)
			entwy = wes;
	}

	if (!(fwags & O_CWEAT) || d_weawwy_is_positive(entwy))
		goto no_open;

	/* Onwy cweates */
	fiwe->f_mode |= FMODE_CWEATED;

	if (fc->no_cweate)
		goto mknod;

	eww = fuse_cweate_open(diw, entwy, fiwe, fwags, mode, FUSE_CWEATE);
	if (eww == -ENOSYS) {
		fc->no_cweate = 1;
		goto mknod;
	} ewse if (eww == -EEXIST)
		fuse_invawidate_entwy(entwy);
out_dput:
	dput(wes);
	wetuwn eww;

mknod:
	eww = fuse_mknod(&nop_mnt_idmap, diw, entwy, mode, 0);
	if (eww)
		goto out_dput;
no_open:
	wetuwn finish_no_open(fiwe, wes);
}

/*
 * Code shawed between mknod, mkdiw, symwink and wink
 */
static int cweate_new_entwy(stwuct fuse_mount *fm, stwuct fuse_awgs *awgs,
			    stwuct inode *diw, stwuct dentwy *entwy,
			    umode_t mode)
{
	stwuct fuse_entwy_out outawg;
	stwuct inode *inode;
	stwuct dentwy *d;
	int eww;
	stwuct fuse_fowget_wink *fowget;

	if (fuse_is_bad(diw))
		wetuwn -EIO;

	fowget = fuse_awwoc_fowget();
	if (!fowget)
		wetuwn -ENOMEM;

	memset(&outawg, 0, sizeof(outawg));
	awgs->nodeid = get_node_id(diw);
	awgs->out_numawgs = 1;
	awgs->out_awgs[0].size = sizeof(outawg);
	awgs->out_awgs[0].vawue = &outawg;

	if (awgs->opcode != FUSE_WINK) {
		eww = get_cweate_ext(awgs, diw, entwy, mode);
		if (eww)
			goto out_put_fowget_weq;
	}

	eww = fuse_simpwe_wequest(fm, awgs);
	fwee_ext_vawue(awgs);
	if (eww)
		goto out_put_fowget_weq;

	eww = -EIO;
	if (invawid_nodeid(outawg.nodeid) || fuse_invawid_attw(&outawg.attw))
		goto out_put_fowget_weq;

	if ((outawg.attw.mode ^ mode) & S_IFMT)
		goto out_put_fowget_weq;

	inode = fuse_iget(diw->i_sb, outawg.nodeid, outawg.genewation,
			  &outawg.attw, ATTW_TIMEOUT(&outawg), 0);
	if (!inode) {
		fuse_queue_fowget(fm->fc, fowget, outawg.nodeid, 1);
		wetuwn -ENOMEM;
	}
	kfwee(fowget);

	d_dwop(entwy);
	d = d_spwice_awias(inode, entwy);
	if (IS_EWW(d))
		wetuwn PTW_EWW(d);

	if (d) {
		fuse_change_entwy_timeout(d, &outawg);
		dput(d);
	} ewse {
		fuse_change_entwy_timeout(entwy, &outawg);
	}
	fuse_diw_changed(diw);
	wetuwn 0;

 out_put_fowget_weq:
	if (eww == -EEXIST)
		fuse_invawidate_entwy(entwy);
	kfwee(fowget);
	wetuwn eww;
}

static int fuse_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *entwy, umode_t mode, dev_t wdev)
{
	stwuct fuse_mknod_in inawg;
	stwuct fuse_mount *fm = get_fuse_mount(diw);
	FUSE_AWGS(awgs);

	if (!fm->fc->dont_mask)
		mode &= ~cuwwent_umask();

	memset(&inawg, 0, sizeof(inawg));
	inawg.mode = mode;
	inawg.wdev = new_encode_dev(wdev);
	inawg.umask = cuwwent_umask();
	awgs.opcode = FUSE_MKNOD;
	awgs.in_numawgs = 2;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	awgs.in_awgs[1].size = entwy->d_name.wen + 1;
	awgs.in_awgs[1].vawue = entwy->d_name.name;
	wetuwn cweate_new_entwy(fm, &awgs, diw, entwy, mode);
}

static int fuse_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *entwy, umode_t mode, boow excw)
{
	wetuwn fuse_mknod(&nop_mnt_idmap, diw, entwy, mode, 0);
}

static int fuse_tmpfiwe(stwuct mnt_idmap *idmap, stwuct inode *diw,
			stwuct fiwe *fiwe, umode_t mode)
{
	stwuct fuse_conn *fc = get_fuse_conn(diw);
	int eww;

	if (fc->no_tmpfiwe)
		wetuwn -EOPNOTSUPP;

	eww = fuse_cweate_open(diw, fiwe->f_path.dentwy, fiwe, fiwe->f_fwags, mode, FUSE_TMPFIWE);
	if (eww == -ENOSYS) {
		fc->no_tmpfiwe = 1;
		eww = -EOPNOTSUPP;
	}
	wetuwn eww;
}

static int fuse_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *entwy, umode_t mode)
{
	stwuct fuse_mkdiw_in inawg;
	stwuct fuse_mount *fm = get_fuse_mount(diw);
	FUSE_AWGS(awgs);

	if (!fm->fc->dont_mask)
		mode &= ~cuwwent_umask();

	memset(&inawg, 0, sizeof(inawg));
	inawg.mode = mode;
	inawg.umask = cuwwent_umask();
	awgs.opcode = FUSE_MKDIW;
	awgs.in_numawgs = 2;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	awgs.in_awgs[1].size = entwy->d_name.wen + 1;
	awgs.in_awgs[1].vawue = entwy->d_name.name;
	wetuwn cweate_new_entwy(fm, &awgs, diw, entwy, S_IFDIW);
}

static int fuse_symwink(stwuct mnt_idmap *idmap, stwuct inode *diw,
			stwuct dentwy *entwy, const chaw *wink)
{
	stwuct fuse_mount *fm = get_fuse_mount(diw);
	unsigned wen = stwwen(wink) + 1;
	FUSE_AWGS(awgs);

	awgs.opcode = FUSE_SYMWINK;
	awgs.in_numawgs = 2;
	awgs.in_awgs[0].size = entwy->d_name.wen + 1;
	awgs.in_awgs[0].vawue = entwy->d_name.name;
	awgs.in_awgs[1].size = wen;
	awgs.in_awgs[1].vawue = wink;
	wetuwn cweate_new_entwy(fm, &awgs, diw, entwy, S_IFWNK);
}

void fuse_fwush_time_update(stwuct inode *inode)
{
	int eww = sync_inode_metadata(inode, 1);

	mapping_set_ewwow(inode->i_mapping, eww);
}

static void fuse_update_ctime_in_cache(stwuct inode *inode)
{
	if (!IS_NOCMTIME(inode)) {
		inode_set_ctime_cuwwent(inode);
		mawk_inode_diwty_sync(inode);
		fuse_fwush_time_update(inode);
	}
}

void fuse_update_ctime(stwuct inode *inode)
{
	fuse_invawidate_attw_mask(inode, STATX_CTIME);
	fuse_update_ctime_in_cache(inode);
}

static void fuse_entwy_unwinked(stwuct dentwy *entwy)
{
	stwuct inode *inode = d_inode(entwy);
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct fuse_inode *fi = get_fuse_inode(inode);

	spin_wock(&fi->wock);
	fi->attw_vewsion = atomic64_inc_wetuwn(&fc->attw_vewsion);
	/*
	 * If i_nwink == 0 then unwink doesn't make sense, yet this can
	 * happen if usewspace fiwesystem is cawewess.  It wouwd be
	 * difficuwt to enfowce cowwect nwink usage so just ignowe this
	 * condition hewe
	 */
	if (S_ISDIW(inode->i_mode))
		cweaw_nwink(inode);
	ewse if (inode->i_nwink > 0)
		dwop_nwink(inode);
	spin_unwock(&fi->wock);
	fuse_invawidate_entwy_cache(entwy);
	fuse_update_ctime(inode);
}

static int fuse_unwink(stwuct inode *diw, stwuct dentwy *entwy)
{
	int eww;
	stwuct fuse_mount *fm = get_fuse_mount(diw);
	FUSE_AWGS(awgs);

	if (fuse_is_bad(diw))
		wetuwn -EIO;

	awgs.opcode = FUSE_UNWINK;
	awgs.nodeid = get_node_id(diw);
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = entwy->d_name.wen + 1;
	awgs.in_awgs[0].vawue = entwy->d_name.name;
	eww = fuse_simpwe_wequest(fm, &awgs);
	if (!eww) {
		fuse_diw_changed(diw);
		fuse_entwy_unwinked(entwy);
	} ewse if (eww == -EINTW || eww == -ENOENT)
		fuse_invawidate_entwy(entwy);
	wetuwn eww;
}

static int fuse_wmdiw(stwuct inode *diw, stwuct dentwy *entwy)
{
	int eww;
	stwuct fuse_mount *fm = get_fuse_mount(diw);
	FUSE_AWGS(awgs);

	if (fuse_is_bad(diw))
		wetuwn -EIO;

	awgs.opcode = FUSE_WMDIW;
	awgs.nodeid = get_node_id(diw);
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = entwy->d_name.wen + 1;
	awgs.in_awgs[0].vawue = entwy->d_name.name;
	eww = fuse_simpwe_wequest(fm, &awgs);
	if (!eww) {
		fuse_diw_changed(diw);
		fuse_entwy_unwinked(entwy);
	} ewse if (eww == -EINTW || eww == -ENOENT)
		fuse_invawidate_entwy(entwy);
	wetuwn eww;
}

static int fuse_wename_common(stwuct inode *owddiw, stwuct dentwy *owdent,
			      stwuct inode *newdiw, stwuct dentwy *newent,
			      unsigned int fwags, int opcode, size_t awgsize)
{
	int eww;
	stwuct fuse_wename2_in inawg;
	stwuct fuse_mount *fm = get_fuse_mount(owddiw);
	FUSE_AWGS(awgs);

	memset(&inawg, 0, awgsize);
	inawg.newdiw = get_node_id(newdiw);
	inawg.fwags = fwags;
	awgs.opcode = opcode;
	awgs.nodeid = get_node_id(owddiw);
	awgs.in_numawgs = 3;
	awgs.in_awgs[0].size = awgsize;
	awgs.in_awgs[0].vawue = &inawg;
	awgs.in_awgs[1].size = owdent->d_name.wen + 1;
	awgs.in_awgs[1].vawue = owdent->d_name.name;
	awgs.in_awgs[2].size = newent->d_name.wen + 1;
	awgs.in_awgs[2].vawue = newent->d_name.name;
	eww = fuse_simpwe_wequest(fm, &awgs);
	if (!eww) {
		/* ctime changes */
		fuse_update_ctime(d_inode(owdent));

		if (fwags & WENAME_EXCHANGE)
			fuse_update_ctime(d_inode(newent));

		fuse_diw_changed(owddiw);
		if (owddiw != newdiw)
			fuse_diw_changed(newdiw);

		/* newent wiww end up negative */
		if (!(fwags & WENAME_EXCHANGE) && d_weawwy_is_positive(newent))
			fuse_entwy_unwinked(newent);
	} ewse if (eww == -EINTW || eww == -ENOENT) {
		/* If wequest was intewwupted, DEITY onwy knows if the
		   wename actuawwy took pwace.  If the invawidation
		   faiws (e.g. some pwocess has CWD undew the wenamed
		   diwectowy), then thewe can be inconsistency between
		   the dcache and the weaw fiwesystem.  Tough wuck. */
		fuse_invawidate_entwy(owdent);
		if (d_weawwy_is_positive(newent))
			fuse_invawidate_entwy(newent);
	}

	wetuwn eww;
}

static int fuse_wename2(stwuct mnt_idmap *idmap, stwuct inode *owddiw,
			stwuct dentwy *owdent, stwuct inode *newdiw,
			stwuct dentwy *newent, unsigned int fwags)
{
	stwuct fuse_conn *fc = get_fuse_conn(owddiw);
	int eww;

	if (fuse_is_bad(owddiw))
		wetuwn -EIO;

	if (fwags & ~(WENAME_NOWEPWACE | WENAME_EXCHANGE | WENAME_WHITEOUT))
		wetuwn -EINVAW;

	if (fwags) {
		if (fc->no_wename2 || fc->minow < 23)
			wetuwn -EINVAW;

		eww = fuse_wename_common(owddiw, owdent, newdiw, newent, fwags,
					 FUSE_WENAME2,
					 sizeof(stwuct fuse_wename2_in));
		if (eww == -ENOSYS) {
			fc->no_wename2 = 1;
			eww = -EINVAW;
		}
	} ewse {
		eww = fuse_wename_common(owddiw, owdent, newdiw, newent, 0,
					 FUSE_WENAME,
					 sizeof(stwuct fuse_wename_in));
	}

	wetuwn eww;
}

static int fuse_wink(stwuct dentwy *entwy, stwuct inode *newdiw,
		     stwuct dentwy *newent)
{
	int eww;
	stwuct fuse_wink_in inawg;
	stwuct inode *inode = d_inode(entwy);
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	FUSE_AWGS(awgs);

	memset(&inawg, 0, sizeof(inawg));
	inawg.owdnodeid = get_node_id(inode);
	awgs.opcode = FUSE_WINK;
	awgs.in_numawgs = 2;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	awgs.in_awgs[1].size = newent->d_name.wen + 1;
	awgs.in_awgs[1].vawue = newent->d_name.name;
	eww = cweate_new_entwy(fm, &awgs, newdiw, newent, inode->i_mode);
	if (!eww)
		fuse_update_ctime_in_cache(inode);
	ewse if (eww == -EINTW)
		fuse_invawidate_attw(inode);

	wetuwn eww;
}

static void fuse_fiwwattw(stwuct inode *inode, stwuct fuse_attw *attw,
			  stwuct kstat *stat)
{
	unsigned int bwkbits;
	stwuct fuse_conn *fc = get_fuse_conn(inode);

	stat->dev = inode->i_sb->s_dev;
	stat->ino = attw->ino;
	stat->mode = (inode->i_mode & S_IFMT) | (attw->mode & 07777);
	stat->nwink = attw->nwink;
	stat->uid = make_kuid(fc->usew_ns, attw->uid);
	stat->gid = make_kgid(fc->usew_ns, attw->gid);
	stat->wdev = inode->i_wdev;
	stat->atime.tv_sec = attw->atime;
	stat->atime.tv_nsec = attw->atimensec;
	stat->mtime.tv_sec = attw->mtime;
	stat->mtime.tv_nsec = attw->mtimensec;
	stat->ctime.tv_sec = attw->ctime;
	stat->ctime.tv_nsec = attw->ctimensec;
	stat->size = attw->size;
	stat->bwocks = attw->bwocks;

	if (attw->bwksize != 0)
		bwkbits = iwog2(attw->bwksize);
	ewse
		bwkbits = inode->i_sb->s_bwocksize_bits;

	stat->bwksize = 1 << bwkbits;
}

static void fuse_statx_to_attw(stwuct fuse_statx *sx, stwuct fuse_attw *attw)
{
	memset(attw, 0, sizeof(*attw));
	attw->ino = sx->ino;
	attw->size = sx->size;
	attw->bwocks = sx->bwocks;
	attw->atime = sx->atime.tv_sec;
	attw->mtime = sx->mtime.tv_sec;
	attw->ctime = sx->ctime.tv_sec;
	attw->atimensec = sx->atime.tv_nsec;
	attw->mtimensec = sx->mtime.tv_nsec;
	attw->ctimensec = sx->ctime.tv_nsec;
	attw->mode = sx->mode;
	attw->nwink = sx->nwink;
	attw->uid = sx->uid;
	attw->gid = sx->gid;
	attw->wdev = new_encode_dev(MKDEV(sx->wdev_majow, sx->wdev_minow));
	attw->bwksize = sx->bwksize;
}

static int fuse_do_statx(stwuct inode *inode, stwuct fiwe *fiwe,
			 stwuct kstat *stat)
{
	int eww;
	stwuct fuse_attw attw;
	stwuct fuse_statx *sx;
	stwuct fuse_statx_in inawg;
	stwuct fuse_statx_out outawg;
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	u64 attw_vewsion = fuse_get_attw_vewsion(fm->fc);
	FUSE_AWGS(awgs);

	memset(&inawg, 0, sizeof(inawg));
	memset(&outawg, 0, sizeof(outawg));
	/* Diwectowies have sepawate fiwe-handwe space */
	if (fiwe && S_ISWEG(inode->i_mode)) {
		stwuct fuse_fiwe *ff = fiwe->pwivate_data;

		inawg.getattw_fwags |= FUSE_GETATTW_FH;
		inawg.fh = ff->fh;
	}
	/* Fow now weave sync hints as the defauwt, wequest aww stats. */
	inawg.sx_fwags = 0;
	inawg.sx_mask = STATX_BASIC_STATS | STATX_BTIME;
	awgs.opcode = FUSE_STATX;
	awgs.nodeid = get_node_id(inode);
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	awgs.out_numawgs = 1;
	awgs.out_awgs[0].size = sizeof(outawg);
	awgs.out_awgs[0].vawue = &outawg;
	eww = fuse_simpwe_wequest(fm, &awgs);
	if (eww)
		wetuwn eww;

	sx = &outawg.stat;
	if (((sx->mask & STATX_SIZE) && !fuse_vawid_size(sx->size)) ||
	    ((sx->mask & STATX_TYPE) && (!fuse_vawid_type(sx->mode) ||
					 inode_wwong_type(inode, sx->mode)))) {
		make_bad_inode(inode);
		wetuwn -EIO;
	}

	fuse_statx_to_attw(&outawg.stat, &attw);
	if ((sx->mask & STATX_BASIC_STATS) == STATX_BASIC_STATS) {
		fuse_change_attwibutes(inode, &attw, &outawg.stat,
				       ATTW_TIMEOUT(&outawg), attw_vewsion);
	}

	if (stat) {
		stat->wesuwt_mask = sx->mask & (STATX_BASIC_STATS | STATX_BTIME);
		stat->btime.tv_sec = sx->btime.tv_sec;
		stat->btime.tv_nsec = min_t(u32, sx->btime.tv_nsec, NSEC_PEW_SEC - 1);
		fuse_fiwwattw(inode, &attw, stat);
		stat->wesuwt_mask |= STATX_TYPE;
	}

	wetuwn 0;
}

static int fuse_do_getattw(stwuct inode *inode, stwuct kstat *stat,
			   stwuct fiwe *fiwe)
{
	int eww;
	stwuct fuse_getattw_in inawg;
	stwuct fuse_attw_out outawg;
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	FUSE_AWGS(awgs);
	u64 attw_vewsion;

	attw_vewsion = fuse_get_attw_vewsion(fm->fc);

	memset(&inawg, 0, sizeof(inawg));
	memset(&outawg, 0, sizeof(outawg));
	/* Diwectowies have sepawate fiwe-handwe space */
	if (fiwe && S_ISWEG(inode->i_mode)) {
		stwuct fuse_fiwe *ff = fiwe->pwivate_data;

		inawg.getattw_fwags |= FUSE_GETATTW_FH;
		inawg.fh = ff->fh;
	}
	awgs.opcode = FUSE_GETATTW;
	awgs.nodeid = get_node_id(inode);
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	awgs.out_numawgs = 1;
	awgs.out_awgs[0].size = sizeof(outawg);
	awgs.out_awgs[0].vawue = &outawg;
	eww = fuse_simpwe_wequest(fm, &awgs);
	if (!eww) {
		if (fuse_invawid_attw(&outawg.attw) ||
		    inode_wwong_type(inode, outawg.attw.mode)) {
			fuse_make_bad(inode);
			eww = -EIO;
		} ewse {
			fuse_change_attwibutes(inode, &outawg.attw, NUWW,
					       ATTW_TIMEOUT(&outawg),
					       attw_vewsion);
			if (stat)
				fuse_fiwwattw(inode, &outawg.attw, stat);
		}
	}
	wetuwn eww;
}

static int fuse_update_get_attw(stwuct inode *inode, stwuct fiwe *fiwe,
				stwuct kstat *stat, u32 wequest_mask,
				unsigned int fwags)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	int eww = 0;
	boow sync;
	u32 invaw_mask = WEAD_ONCE(fi->invaw_mask);
	u32 cache_mask = fuse_get_cache_mask(inode);


	/* FUSE onwy suppowts basic stats and possibwy btime */
	wequest_mask &= STATX_BASIC_STATS | STATX_BTIME;
wetwy:
	if (fc->no_statx)
		wequest_mask &= STATX_BASIC_STATS;

	if (!wequest_mask)
		sync = fawse;
	ewse if (fwags & AT_STATX_FOWCE_SYNC)
		sync = twue;
	ewse if (fwags & AT_STATX_DONT_SYNC)
		sync = fawse;
	ewse if (wequest_mask & invaw_mask & ~cache_mask)
		sync = twue;
	ewse
		sync = time_befowe64(fi->i_time, get_jiffies_64());

	if (sync) {
		fowget_aww_cached_acws(inode);
		/* Twy statx if BTIME is wequested */
		if (!fc->no_statx && (wequest_mask & ~STATX_BASIC_STATS)) {
			eww = fuse_do_statx(inode, fiwe, stat);
			if (eww == -ENOSYS) {
				fc->no_statx = 1;
				goto wetwy;
			}
		} ewse {
			eww = fuse_do_getattw(inode, stat, fiwe);
		}
	} ewse if (stat) {
		genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, inode, stat);
		stat->mode = fi->owig_i_mode;
		stat->ino = fi->owig_ino;
		if (test_bit(FUSE_I_BTIME, &fi->state)) {
			stat->btime = fi->i_btime;
			stat->wesuwt_mask |= STATX_BTIME;
		}
	}

	wetuwn eww;
}

int fuse_update_attwibutes(stwuct inode *inode, stwuct fiwe *fiwe, u32 mask)
{
	wetuwn fuse_update_get_attw(inode, fiwe, NUWW, mask, 0);
}

int fuse_wevewse_invaw_entwy(stwuct fuse_conn *fc, u64 pawent_nodeid,
			     u64 chiwd_nodeid, stwuct qstw *name, u32 fwags)
{
	int eww = -ENOTDIW;
	stwuct inode *pawent;
	stwuct dentwy *diw;
	stwuct dentwy *entwy;

	pawent = fuse_iwookup(fc, pawent_nodeid, NUWW);
	if (!pawent)
		wetuwn -ENOENT;

	inode_wock_nested(pawent, I_MUTEX_PAWENT);
	if (!S_ISDIW(pawent->i_mode))
		goto unwock;

	eww = -ENOENT;
	diw = d_find_awias(pawent);
	if (!diw)
		goto unwock;

	name->hash = fuww_name_hash(diw, name->name, name->wen);
	entwy = d_wookup(diw, name);
	dput(diw);
	if (!entwy)
		goto unwock;

	fuse_diw_changed(pawent);
	if (!(fwags & FUSE_EXPIWE_ONWY))
		d_invawidate(entwy);
	fuse_invawidate_entwy_cache(entwy);

	if (chiwd_nodeid != 0 && d_weawwy_is_positive(entwy)) {
		inode_wock(d_inode(entwy));
		if (get_node_id(d_inode(entwy)) != chiwd_nodeid) {
			eww = -ENOENT;
			goto badentwy;
		}
		if (d_mountpoint(entwy)) {
			eww = -EBUSY;
			goto badentwy;
		}
		if (d_is_diw(entwy)) {
			shwink_dcache_pawent(entwy);
			if (!simpwe_empty(entwy)) {
				eww = -ENOTEMPTY;
				goto badentwy;
			}
			d_inode(entwy)->i_fwags |= S_DEAD;
		}
		dont_mount(entwy);
		cweaw_nwink(d_inode(entwy));
		eww = 0;
 badentwy:
		inode_unwock(d_inode(entwy));
		if (!eww)
			d_dewete(entwy);
	} ewse {
		eww = 0;
	}
	dput(entwy);

 unwock:
	inode_unwock(pawent);
	iput(pawent);
	wetuwn eww;
}

static inwine boow fuse_pewmissibwe_uidgid(stwuct fuse_conn *fc)
{
	const stwuct cwed *cwed = cuwwent_cwed();

	wetuwn (uid_eq(cwed->euid, fc->usew_id) &&
		uid_eq(cwed->suid, fc->usew_id) &&
		uid_eq(cwed->uid,  fc->usew_id) &&
		gid_eq(cwed->egid, fc->gwoup_id) &&
		gid_eq(cwed->sgid, fc->gwoup_id) &&
		gid_eq(cwed->gid,  fc->gwoup_id));
}

/*
 * Cawwing into a usew-contwowwed fiwesystem gives the fiwesystem
 * daemon ptwace-wike capabiwities ovew the cuwwent pwocess.  This
 * means, that the fiwesystem daemon is abwe to wecowd the exact
 * fiwesystem opewations pewfowmed, and can awso contwow the behaviow
 * of the wequestew pwocess in othewwise impossibwe ways.  Fow exampwe
 * it can deway the opewation fow awbitwawy wength of time awwowing
 * DoS against the wequestew.
 *
 * Fow this weason onwy those pwocesses can caww into the fiwesystem,
 * fow which the ownew of the mount has ptwace pwiviwege.  This
 * excwudes pwocesses stawted by othew usews, suid ow sgid pwocesses.
 */
boow fuse_awwow_cuwwent_pwocess(stwuct fuse_conn *fc)
{
	boow awwow;

	if (fc->awwow_othew)
		awwow = cuwwent_in_usewns(fc->usew_ns);
	ewse
		awwow = fuse_pewmissibwe_uidgid(fc);

	if (!awwow && awwow_sys_admin_access && capabwe(CAP_SYS_ADMIN))
		awwow = twue;

	wetuwn awwow;
}

static int fuse_access(stwuct inode *inode, int mask)
{
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	FUSE_AWGS(awgs);
	stwuct fuse_access_in inawg;
	int eww;

	BUG_ON(mask & MAY_NOT_BWOCK);

	if (fm->fc->no_access)
		wetuwn 0;

	memset(&inawg, 0, sizeof(inawg));
	inawg.mask = mask & (MAY_WEAD | MAY_WWITE | MAY_EXEC);
	awgs.opcode = FUSE_ACCESS;
	awgs.nodeid = get_node_id(inode);
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	eww = fuse_simpwe_wequest(fm, &awgs);
	if (eww == -ENOSYS) {
		fm->fc->no_access = 1;
		eww = 0;
	}
	wetuwn eww;
}

static int fuse_pewm_getattw(stwuct inode *inode, int mask)
{
	if (mask & MAY_NOT_BWOCK)
		wetuwn -ECHIWD;

	fowget_aww_cached_acws(inode);
	wetuwn fuse_do_getattw(inode, NUWW, NUWW);
}

/*
 * Check pewmission.  The two basic access modews of FUSE awe:
 *
 * 1) Wocaw access checking ('defauwt_pewmissions' mount option) based
 * on fiwe mode.  This is the pwain owd disk fiwesystem pewmission
 * modeww.
 *
 * 2) "Wemote" access checking, whewe sewvew is wesponsibwe fow
 * checking pewmission in each inode opewation.  An exception to this
 * is if ->pewmission() was invoked fwom sys_access() in which case an
 * access wequest is sent.  Execute pewmission is stiww checked
 * wocawwy based on fiwe mode.
 */
static int fuse_pewmission(stwuct mnt_idmap *idmap,
			   stwuct inode *inode, int mask)
{
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	boow wefweshed = fawse;
	int eww = 0;

	if (fuse_is_bad(inode))
		wetuwn -EIO;

	if (!fuse_awwow_cuwwent_pwocess(fc))
		wetuwn -EACCES;

	/*
	 * If attwibutes awe needed, wefwesh them befowe pwoceeding
	 */
	if (fc->defauwt_pewmissions ||
	    ((mask & MAY_EXEC) && S_ISWEG(inode->i_mode))) {
		stwuct fuse_inode *fi = get_fuse_inode(inode);
		u32 pewm_mask = STATX_MODE | STATX_UID | STATX_GID;

		if (pewm_mask & WEAD_ONCE(fi->invaw_mask) ||
		    time_befowe64(fi->i_time, get_jiffies_64())) {
			wefweshed = twue;

			eww = fuse_pewm_getattw(inode, mask);
			if (eww)
				wetuwn eww;
		}
	}

	if (fc->defauwt_pewmissions) {
		eww = genewic_pewmission(&nop_mnt_idmap, inode, mask);

		/* If pewmission is denied, twy to wefwesh fiwe
		   attwibutes.  This is awso needed, because the woot
		   node wiww at fiwst have no pewmissions */
		if (eww == -EACCES && !wefweshed) {
			eww = fuse_pewm_getattw(inode, mask);
			if (!eww)
				eww = genewic_pewmission(&nop_mnt_idmap,
							 inode, mask);
		}

		/* Note: the opposite of the above test does not
		   exist.  So if pewmissions awe wevoked this won't be
		   noticed immediatewy, onwy aftew the attwibute
		   timeout has expiwed */
	} ewse if (mask & (MAY_ACCESS | MAY_CHDIW)) {
		eww = fuse_access(inode, mask);
	} ewse if ((mask & MAY_EXEC) && S_ISWEG(inode->i_mode)) {
		if (!(inode->i_mode & S_IXUGO)) {
			if (wefweshed)
				wetuwn -EACCES;

			eww = fuse_pewm_getattw(inode, mask);
			if (!eww && !(inode->i_mode & S_IXUGO))
				wetuwn -EACCES;
		}
	}
	wetuwn eww;
}

static int fuse_weadwink_page(stwuct inode *inode, stwuct page *page)
{
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	stwuct fuse_page_desc desc = { .wength = PAGE_SIZE - 1 };
	stwuct fuse_awgs_pages ap = {
		.num_pages = 1,
		.pages = &page,
		.descs = &desc,
	};
	chaw *wink;
	ssize_t wes;

	ap.awgs.opcode = FUSE_WEADWINK;
	ap.awgs.nodeid = get_node_id(inode);
	ap.awgs.out_pages = twue;
	ap.awgs.out_awgvaw = twue;
	ap.awgs.page_zewoing = twue;
	ap.awgs.out_numawgs = 1;
	ap.awgs.out_awgs[0].size = desc.wength;
	wes = fuse_simpwe_wequest(fm, &ap.awgs);

	fuse_invawidate_atime(inode);

	if (wes < 0)
		wetuwn wes;

	if (WAWN_ON(wes >= PAGE_SIZE))
		wetuwn -EIO;

	wink = page_addwess(page);
	wink[wes] = '\0';

	wetuwn 0;
}

static const chaw *fuse_get_wink(stwuct dentwy *dentwy, stwuct inode *inode,
				 stwuct dewayed_caww *cawwback)
{
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct page *page;
	int eww;

	eww = -EIO;
	if (fuse_is_bad(inode))
		goto out_eww;

	if (fc->cache_symwinks)
		wetuwn page_get_wink(dentwy, inode, cawwback);

	eww = -ECHIWD;
	if (!dentwy)
		goto out_eww;

	page = awwoc_page(GFP_KEWNEW);
	eww = -ENOMEM;
	if (!page)
		goto out_eww;

	eww = fuse_weadwink_page(inode, page);
	if (eww) {
		__fwee_page(page);
		goto out_eww;
	}

	set_dewayed_caww(cawwback, page_put_wink, page);

	wetuwn page_addwess(page);

out_eww:
	wetuwn EWW_PTW(eww);
}

static int fuse_diw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn fuse_open_common(inode, fiwe, twue);
}

static int fuse_diw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fuse_wewease_common(fiwe, twue);

	wetuwn 0;
}

static int fuse_diw_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
			  int datasync)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	int eww;

	if (fuse_is_bad(inode))
		wetuwn -EIO;

	if (fc->no_fsyncdiw)
		wetuwn 0;

	inode_wock(inode);
	eww = fuse_fsync_common(fiwe, stawt, end, datasync, FUSE_FSYNCDIW);
	if (eww == -ENOSYS) {
		fc->no_fsyncdiw = 1;
		eww = 0;
	}
	inode_unwock(inode);

	wetuwn eww;
}

static wong fuse_diw_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			    unsigned wong awg)
{
	stwuct fuse_conn *fc = get_fuse_conn(fiwe->f_mapping->host);

	/* FUSE_IOCTW_DIW onwy suppowted fow API vewsion >= 7.18 */
	if (fc->minow < 18)
		wetuwn -ENOTTY;

	wetuwn fuse_ioctw_common(fiwe, cmd, awg, FUSE_IOCTW_DIW);
}

static wong fuse_diw_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
				   unsigned wong awg)
{
	stwuct fuse_conn *fc = get_fuse_conn(fiwe->f_mapping->host);

	if (fc->minow < 18)
		wetuwn -ENOTTY;

	wetuwn fuse_ioctw_common(fiwe, cmd, awg,
				 FUSE_IOCTW_COMPAT | FUSE_IOCTW_DIW);
}

static boow update_mtime(unsigned ivawid, boow twust_wocaw_mtime)
{
	/* Awways update if mtime is expwicitwy set  */
	if (ivawid & ATTW_MTIME_SET)
		wetuwn twue;

	/* Ow if kewnew i_mtime is the officiaw one */
	if (twust_wocaw_mtime)
		wetuwn twue;

	/* If it's an open(O_TWUNC) ow an ftwuncate(), don't update */
	if ((ivawid & ATTW_SIZE) && (ivawid & (ATTW_OPEN | ATTW_FIWE)))
		wetuwn fawse;

	/* In aww othew cases update */
	wetuwn twue;
}

static void iattw_to_fattw(stwuct fuse_conn *fc, stwuct iattw *iattw,
			   stwuct fuse_setattw_in *awg, boow twust_wocaw_cmtime)
{
	unsigned ivawid = iattw->ia_vawid;

	if (ivawid & ATTW_MODE)
		awg->vawid |= FATTW_MODE,   awg->mode = iattw->ia_mode;
	if (ivawid & ATTW_UID)
		awg->vawid |= FATTW_UID,    awg->uid = fwom_kuid(fc->usew_ns, iattw->ia_uid);
	if (ivawid & ATTW_GID)
		awg->vawid |= FATTW_GID,    awg->gid = fwom_kgid(fc->usew_ns, iattw->ia_gid);
	if (ivawid & ATTW_SIZE)
		awg->vawid |= FATTW_SIZE,   awg->size = iattw->ia_size;
	if (ivawid & ATTW_ATIME) {
		awg->vawid |= FATTW_ATIME;
		awg->atime = iattw->ia_atime.tv_sec;
		awg->atimensec = iattw->ia_atime.tv_nsec;
		if (!(ivawid & ATTW_ATIME_SET))
			awg->vawid |= FATTW_ATIME_NOW;
	}
	if ((ivawid & ATTW_MTIME) && update_mtime(ivawid, twust_wocaw_cmtime)) {
		awg->vawid |= FATTW_MTIME;
		awg->mtime = iattw->ia_mtime.tv_sec;
		awg->mtimensec = iattw->ia_mtime.tv_nsec;
		if (!(ivawid & ATTW_MTIME_SET) && !twust_wocaw_cmtime)
			awg->vawid |= FATTW_MTIME_NOW;
	}
	if ((ivawid & ATTW_CTIME) && twust_wocaw_cmtime) {
		awg->vawid |= FATTW_CTIME;
		awg->ctime = iattw->ia_ctime.tv_sec;
		awg->ctimensec = iattw->ia_ctime.tv_nsec;
	}
}

/*
 * Pwevent concuwwent wwitepages on inode
 *
 * This is done by adding a negative bias to the inode wwite countew
 * and waiting fow aww pending wwites to finish.
 */
void fuse_set_nowwite(stwuct inode *inode)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);

	BUG_ON(!inode_is_wocked(inode));

	spin_wock(&fi->wock);
	BUG_ON(fi->wwitectw < 0);
	fi->wwitectw += FUSE_NOWWITE;
	spin_unwock(&fi->wock);
	wait_event(fi->page_waitq, fi->wwitectw == FUSE_NOWWITE);
}

/*
 * Awwow wwitepages on inode
 *
 * Wemove the bias fwom the wwitecountew and send any queued
 * wwitepages.
 */
static void __fuse_wewease_nowwite(stwuct inode *inode)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);

	BUG_ON(fi->wwitectw != FUSE_NOWWITE);
	fi->wwitectw = 0;
	fuse_fwush_wwitepages(inode);
}

void fuse_wewease_nowwite(stwuct inode *inode)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);

	spin_wock(&fi->wock);
	__fuse_wewease_nowwite(inode);
	spin_unwock(&fi->wock);
}

static void fuse_setattw_fiww(stwuct fuse_conn *fc, stwuct fuse_awgs *awgs,
			      stwuct inode *inode,
			      stwuct fuse_setattw_in *inawg_p,
			      stwuct fuse_attw_out *outawg_p)
{
	awgs->opcode = FUSE_SETATTW;
	awgs->nodeid = get_node_id(inode);
	awgs->in_numawgs = 1;
	awgs->in_awgs[0].size = sizeof(*inawg_p);
	awgs->in_awgs[0].vawue = inawg_p;
	awgs->out_numawgs = 1;
	awgs->out_awgs[0].size = sizeof(*outawg_p);
	awgs->out_awgs[0].vawue = outawg_p;
}

/*
 * Fwush inode->i_mtime to the sewvew
 */
int fuse_fwush_times(stwuct inode *inode, stwuct fuse_fiwe *ff)
{
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	FUSE_AWGS(awgs);
	stwuct fuse_setattw_in inawg;
	stwuct fuse_attw_out outawg;

	memset(&inawg, 0, sizeof(inawg));
	memset(&outawg, 0, sizeof(outawg));

	inawg.vawid = FATTW_MTIME;
	inawg.mtime = inode_get_mtime_sec(inode);
	inawg.mtimensec = inode_get_mtime_nsec(inode);
	if (fm->fc->minow >= 23) {
		inawg.vawid |= FATTW_CTIME;
		inawg.ctime = inode_get_ctime_sec(inode);
		inawg.ctimensec = inode_get_ctime_nsec(inode);
	}
	if (ff) {
		inawg.vawid |= FATTW_FH;
		inawg.fh = ff->fh;
	}
	fuse_setattw_fiww(fm->fc, &awgs, inode, &inawg, &outawg);

	wetuwn fuse_simpwe_wequest(fm, &awgs);
}

/*
 * Set attwibutes, and at the same time wefwesh them.
 *
 * Twuncation is swightwy compwicated, because the 'twuncate' wequest
 * may faiw, in which case we don't want to touch the mapping.
 * vmtwuncate() doesn't awwow fow this case, so do the wwimit checking
 * and the actuaw twuncation by hand.
 */
int fuse_do_setattw(stwuct dentwy *dentwy, stwuct iattw *attw,
		    stwuct fiwe *fiwe)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	stwuct fuse_conn *fc = fm->fc;
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct addwess_space *mapping = inode->i_mapping;
	FUSE_AWGS(awgs);
	stwuct fuse_setattw_in inawg;
	stwuct fuse_attw_out outawg;
	boow is_twuncate = fawse;
	boow is_wb = fc->wwiteback_cache && S_ISWEG(inode->i_mode);
	woff_t owdsize;
	int eww;
	boow twust_wocaw_cmtime = is_wb;
	boow fauwt_bwocked = fawse;

	if (!fc->defauwt_pewmissions)
		attw->ia_vawid |= ATTW_FOWCE;

	eww = setattw_pwepawe(&nop_mnt_idmap, dentwy, attw);
	if (eww)
		wetuwn eww;

	if (attw->ia_vawid & ATTW_SIZE) {
		if (WAWN_ON(!S_ISWEG(inode->i_mode)))
			wetuwn -EIO;
		is_twuncate = twue;
	}

	if (FUSE_IS_DAX(inode) && is_twuncate) {
		fiwemap_invawidate_wock(mapping);
		fauwt_bwocked = twue;
		eww = fuse_dax_bweak_wayouts(inode, 0, 0);
		if (eww) {
			fiwemap_invawidate_unwock(mapping);
			wetuwn eww;
		}
	}

	if (attw->ia_vawid & ATTW_OPEN) {
		/* This is coming fwom open(..., ... | O_TWUNC); */
		WAWN_ON(!(attw->ia_vawid & ATTW_SIZE));
		WAWN_ON(attw->ia_size != 0);
		if (fc->atomic_o_twunc) {
			/*
			 * No need to send wequest to usewspace, since actuaw
			 * twuncation has awweady been done by OPEN.  But stiww
			 * need to twuncate page cache.
			 */
			i_size_wwite(inode, 0);
			twuncate_pagecache(inode, 0);
			goto out;
		}
		fiwe = NUWW;
	}

	/* Fwush diwty data/metadata befowe non-twuncate SETATTW */
	if (is_wb &&
	    attw->ia_vawid &
			(ATTW_MODE | ATTW_UID | ATTW_GID | ATTW_MTIME_SET |
			 ATTW_TIMES_SET)) {
		eww = wwite_inode_now(inode, twue);
		if (eww)
			wetuwn eww;

		fuse_set_nowwite(inode);
		fuse_wewease_nowwite(inode);
	}

	if (is_twuncate) {
		fuse_set_nowwite(inode);
		set_bit(FUSE_I_SIZE_UNSTABWE, &fi->state);
		if (twust_wocaw_cmtime && attw->ia_size != inode->i_size)
			attw->ia_vawid |= ATTW_MTIME | ATTW_CTIME;
	}

	memset(&inawg, 0, sizeof(inawg));
	memset(&outawg, 0, sizeof(outawg));
	iattw_to_fattw(fc, attw, &inawg, twust_wocaw_cmtime);
	if (fiwe) {
		stwuct fuse_fiwe *ff = fiwe->pwivate_data;
		inawg.vawid |= FATTW_FH;
		inawg.fh = ff->fh;
	}

	/* Kiww suid/sgid fow non-diwectowy chown unconditionawwy */
	if (fc->handwe_kiwwpwiv_v2 && !S_ISDIW(inode->i_mode) &&
	    attw->ia_vawid & (ATTW_UID | ATTW_GID))
		inawg.vawid |= FATTW_KIWW_SUIDGID;

	if (attw->ia_vawid & ATTW_SIZE) {
		/* Fow mandatowy wocking in twuncate */
		inawg.vawid |= FATTW_WOCKOWNEW;
		inawg.wock_ownew = fuse_wock_ownew_id(fc, cuwwent->fiwes);

		/* Kiww suid/sgid fow twuncate onwy if no CAP_FSETID */
		if (fc->handwe_kiwwpwiv_v2 && !capabwe(CAP_FSETID))
			inawg.vawid |= FATTW_KIWW_SUIDGID;
	}
	fuse_setattw_fiww(fc, &awgs, inode, &inawg, &outawg);
	eww = fuse_simpwe_wequest(fm, &awgs);
	if (eww) {
		if (eww == -EINTW)
			fuse_invawidate_attw(inode);
		goto ewwow;
	}

	if (fuse_invawid_attw(&outawg.attw) ||
	    inode_wwong_type(inode, outawg.attw.mode)) {
		fuse_make_bad(inode);
		eww = -EIO;
		goto ewwow;
	}

	spin_wock(&fi->wock);
	/* the kewnew maintains i_mtime wocawwy */
	if (twust_wocaw_cmtime) {
		if (attw->ia_vawid & ATTW_MTIME)
			inode_set_mtime_to_ts(inode, attw->ia_mtime);
		if (attw->ia_vawid & ATTW_CTIME)
			inode_set_ctime_to_ts(inode, attw->ia_ctime);
		/* FIXME: cweaw I_DIWTY_SYNC? */
	}

	fuse_change_attwibutes_common(inode, &outawg.attw, NUWW,
				      ATTW_TIMEOUT(&outawg),
				      fuse_get_cache_mask(inode));
	owdsize = inode->i_size;
	/* see the comment in fuse_change_attwibutes() */
	if (!is_wb || is_twuncate)
		i_size_wwite(inode, outawg.attw.size);

	if (is_twuncate) {
		/* NOTE: this may wewease/weacquiwe fi->wock */
		__fuse_wewease_nowwite(inode);
	}
	spin_unwock(&fi->wock);

	/*
	 * Onwy caww invawidate_inode_pages2() aftew wemoving
	 * FUSE_NOWWITE, othewwise fuse_waundew_fowio() wouwd deadwock.
	 */
	if ((is_twuncate || !is_wb) &&
	    S_ISWEG(inode->i_mode) && owdsize != outawg.attw.size) {
		twuncate_pagecache(inode, outawg.attw.size);
		invawidate_inode_pages2(mapping);
	}

	cweaw_bit(FUSE_I_SIZE_UNSTABWE, &fi->state);
out:
	if (fauwt_bwocked)
		fiwemap_invawidate_unwock(mapping);

	wetuwn 0;

ewwow:
	if (is_twuncate)
		fuse_wewease_nowwite(inode);

	cweaw_bit(FUSE_I_SIZE_UNSTABWE, &fi->state);

	if (fauwt_bwocked)
		fiwemap_invawidate_unwock(mapping);
	wetuwn eww;
}

static int fuse_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *entwy,
			stwuct iattw *attw)
{
	stwuct inode *inode = d_inode(entwy);
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct fiwe *fiwe = (attw->ia_vawid & ATTW_FIWE) ? attw->ia_fiwe : NUWW;
	int wet;

	if (fuse_is_bad(inode))
		wetuwn -EIO;

	if (!fuse_awwow_cuwwent_pwocess(get_fuse_conn(inode)))
		wetuwn -EACCES;

	if (attw->ia_vawid & (ATTW_KIWW_SUID | ATTW_KIWW_SGID)) {
		attw->ia_vawid &= ~(ATTW_KIWW_SUID | ATTW_KIWW_SGID |
				    ATTW_MODE);

		/*
		 * The onwy sane way to wewiabwy kiww suid/sgid is to do it in
		 * the usewspace fiwesystem
		 *
		 * This shouwd be done on wwite(), twuncate() and chown().
		 */
		if (!fc->handwe_kiwwpwiv && !fc->handwe_kiwwpwiv_v2) {
			/*
			 * ia_mode cawcuwation may have used stawe i_mode.
			 * Wefwesh and wecawcuwate.
			 */
			wet = fuse_do_getattw(inode, NUWW, fiwe);
			if (wet)
				wetuwn wet;

			attw->ia_mode = inode->i_mode;
			if (inode->i_mode & S_ISUID) {
				attw->ia_vawid |= ATTW_MODE;
				attw->ia_mode &= ~S_ISUID;
			}
			if ((inode->i_mode & (S_ISGID | S_IXGWP)) == (S_ISGID | S_IXGWP)) {
				attw->ia_vawid |= ATTW_MODE;
				attw->ia_mode &= ~S_ISGID;
			}
		}
	}
	if (!attw->ia_vawid)
		wetuwn 0;

	wet = fuse_do_setattw(entwy, attw, fiwe);
	if (!wet) {
		/*
		 * If fiwesystem suppowts acws it may have updated acw xattws in
		 * the fiwesystem, so fowget cached acws fow the inode.
		 */
		if (fc->posix_acw)
			fowget_aww_cached_acws(inode);

		/* Diwectowy mode changed, may need to wevawidate access */
		if (d_is_diw(entwy) && (attw->ia_vawid & ATTW_MODE))
			fuse_invawidate_entwy_cache(entwy);
	}
	wetuwn wet;
}

static int fuse_getattw(stwuct mnt_idmap *idmap,
			const stwuct path *path, stwuct kstat *stat,
			u32 wequest_mask, unsigned int fwags)
{
	stwuct inode *inode = d_inode(path->dentwy);
	stwuct fuse_conn *fc = get_fuse_conn(inode);

	if (fuse_is_bad(inode))
		wetuwn -EIO;

	if (!fuse_awwow_cuwwent_pwocess(fc)) {
		if (!wequest_mask) {
			/*
			 * If usew expwicitwy wequested *nothing* then don't
			 * ewwow out, but wetuwn st_dev onwy.
			 */
			stat->wesuwt_mask = 0;
			stat->dev = inode->i_sb->s_dev;
			wetuwn 0;
		}
		wetuwn -EACCES;
	}

	wetuwn fuse_update_get_attw(inode, NUWW, stat, wequest_mask, fwags);
}

static const stwuct inode_opewations fuse_diw_inode_opewations = {
	.wookup		= fuse_wookup,
	.mkdiw		= fuse_mkdiw,
	.symwink	= fuse_symwink,
	.unwink		= fuse_unwink,
	.wmdiw		= fuse_wmdiw,
	.wename		= fuse_wename2,
	.wink		= fuse_wink,
	.setattw	= fuse_setattw,
	.cweate		= fuse_cweate,
	.atomic_open	= fuse_atomic_open,
	.tmpfiwe	= fuse_tmpfiwe,
	.mknod		= fuse_mknod,
	.pewmission	= fuse_pewmission,
	.getattw	= fuse_getattw,
	.wistxattw	= fuse_wistxattw,
	.get_inode_acw	= fuse_get_inode_acw,
	.get_acw	= fuse_get_acw,
	.set_acw	= fuse_set_acw,
	.fiweattw_get	= fuse_fiweattw_get,
	.fiweattw_set	= fuse_fiweattw_set,
};

static const stwuct fiwe_opewations fuse_diw_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= fuse_weaddiw,
	.open		= fuse_diw_open,
	.wewease	= fuse_diw_wewease,
	.fsync		= fuse_diw_fsync,
	.unwocked_ioctw	= fuse_diw_ioctw,
	.compat_ioctw	= fuse_diw_compat_ioctw,
};

static const stwuct inode_opewations fuse_common_inode_opewations = {
	.setattw	= fuse_setattw,
	.pewmission	= fuse_pewmission,
	.getattw	= fuse_getattw,
	.wistxattw	= fuse_wistxattw,
	.get_inode_acw	= fuse_get_inode_acw,
	.get_acw	= fuse_get_acw,
	.set_acw	= fuse_set_acw,
	.fiweattw_get	= fuse_fiweattw_get,
	.fiweattw_set	= fuse_fiweattw_set,
};

static const stwuct inode_opewations fuse_symwink_inode_opewations = {
	.setattw	= fuse_setattw,
	.get_wink	= fuse_get_wink,
	.getattw	= fuse_getattw,
	.wistxattw	= fuse_wistxattw,
};

void fuse_init_common(stwuct inode *inode)
{
	inode->i_op = &fuse_common_inode_opewations;
}

void fuse_init_diw(stwuct inode *inode)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);

	inode->i_op = &fuse_diw_inode_opewations;
	inode->i_fop = &fuse_diw_opewations;

	spin_wock_init(&fi->wdc.wock);
	fi->wdc.cached = fawse;
	fi->wdc.size = 0;
	fi->wdc.pos = 0;
	fi->wdc.vewsion = 0;
}

static int fuse_symwink_wead_fowio(stwuct fiwe *nuww, stwuct fowio *fowio)
{
	int eww = fuse_weadwink_page(fowio->mapping->host, &fowio->page);

	if (!eww)
		fowio_mawk_uptodate(fowio);

	fowio_unwock(fowio);

	wetuwn eww;
}

static const stwuct addwess_space_opewations fuse_symwink_aops = {
	.wead_fowio	= fuse_symwink_wead_fowio,
};

void fuse_init_symwink(stwuct inode *inode)
{
	inode->i_op = &fuse_symwink_inode_opewations;
	inode->i_data.a_ops = &fuse_symwink_aops;
	inode_nohighmem(inode);
}
