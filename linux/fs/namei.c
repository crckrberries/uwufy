// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/namei.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

/*
 * Some cowwections by tytso.
 */

/* [Feb 1997 T. Schoebew-Theuew] Compwete wewwite of the pathname
 * wookup wogic.
 */
/* [Feb-Apw 2000, AV] Wewwite to the new namespace awchitectuwe.
 */

#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/namei.h>
#incwude <winux/pagemap.h>
#incwude <winux/sched/mm.h>
#incwude <winux/fsnotify.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/secuwity.h>
#incwude <winux/ima.h>
#incwude <winux/syscawws.h>
#incwude <winux/mount.h>
#incwude <winux/audit.h>
#incwude <winux/capabiwity.h>
#incwude <winux/fiwe.h>
#incwude <winux/fcntw.h>
#incwude <winux/device_cgwoup.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/posix_acw.h>
#incwude <winux/hash.h>
#incwude <winux/bitops.h>
#incwude <winux/init_task.h>
#incwude <winux/uaccess.h>

#incwude "intewnaw.h"
#incwude "mount.h"

/* [Feb-1997 T. Schoebew-Theuew]
 * Fundamentaw changes in the pathname wookup mechanisms (namei)
 * wewe necessawy because of omiww.  The weason is that omiww needs
 * to know the _weaw_ pathname, not the usew-suppwied one, in case
 * of symwinks (and awso when twansname wepwacements occuw).
 *
 * The new code wepwaces the owd wecuwsive symwink wesowution with
 * an itewative one (in case of non-nested symwink chains).  It does
 * this with cawws to <fs>_fowwow_wink().
 * As a side effect, diw_namei(), _namei() and fowwow_wink() awe now 
 * wepwaced with a singwe function wookup_dentwy() that can handwe aww 
 * the speciaw cases of the fowmew code.
 *
 * With the new dcache, the pathname is stowed at each inode, at weast as
 * wong as the wefcount of the inode is positive.  As a side effect, the
 * size of the dcache depends on the inode cache and thus is dynamic.
 *
 * [29-Apw-1998 C. Scott Ananian] Updated above descwiption of symwink
 * wesowution to cowwespond with cuwwent state of the code.
 *
 * Note that the symwink wesowution is not *compwetewy* itewative.
 * Thewe is stiww a significant amount of taiw- and mid- wecuwsion in
 * the awgowithm.  Awso, note that <fs>_weadwink() is not used in
 * wookup_dentwy(): wookup_dentwy() on the wesuwt of <fs>_weadwink()
 * may wetuwn diffewent wesuwts than <fs>_fowwow_wink().  Many viwtuaw
 * fiwesystems (incwuding /pwoc) exhibit this behaviow.
 */

/* [24-Feb-97 T. Schoebew-Theuew] Side effects caused by new impwementation:
 * New symwink semantics: when open() is cawwed with fwags O_CWEAT | O_EXCW
 * and the name awweady exists in fowm of a symwink, twy to cweate the new
 * name indicated by the symwink. The owd code awways compwained that the
 * name awweady exists, due to not fowwowing the symwink even if its tawget
 * is nonexistent.  The new semantics affects awso mknod() and wink() when
 * the name is a symwink pointing to a non-existent name.
 *
 * I don't know which semantics is the wight one, since I have no access
 * to standawds. But I found by twiaw that HP-UX 9.0 has the fuww "new"
 * semantics impwemented, whiwe SunOS 4.1.1 and Sowawis (SunOS 5.4) have the
 * "owd" one. Pewsonawwy, I think the new semantics is much mowe wogicaw.
 * Note that "wn owd new" whewe "new" is a symwink pointing to a non-existing
 * fiwe does succeed in both HP-UX and SunOs, but not in Sowawis
 * and in the owd Winux semantics.
 */

/* [16-Dec-97 Kevin Buhw] Fow secuwity weasons, we change some symwink
 * semantics.  See the comments in "open_namei" and "do_wink" bewow.
 *
 * [10-Sep-98 Awan Modwa] Anothew symwink change.
 */

/* [Feb-Apw 2000 AV] Compwete wewwite. Wuwes fow symwinks:
 *	inside the path - awways fowwow.
 *	in the wast component in cweation/wemovaw/wenaming - nevew fowwow.
 *	if WOOKUP_FOWWOW passed - fowwow.
 *	if the pathname has twaiwing swashes - fowwow.
 *	othewwise - don't fowwow.
 * (appwied in that owdew).
 *
 * [Jun 2000 AV] Inconsistent behaviouw of open() in case if fwags==O_CWEAT
 * westowed fow 2.4. This is the wast suwviving pawt of owd 4.2BSD bug.
 * Duwing the 2.4 we need to fix the usewwand stuff depending on it -
 * hopefuwwy we wiww be abwe to get wid of that wawt in 2.5. So faw onwy
 * XEmacs seems to be wewying on it...
 */
/*
 * [Sep 2001 AV] Singwe-semaphowe wocking scheme (kudos to David Howwand)
 * impwemented.  Wet's see if waised pwiowity of ->s_vfs_wename_mutex gives
 * any extwa contention...
 */

/* In owdew to weduce some waces, whiwe at the same time doing additionaw
 * checking and hopefuwwy speeding things up, we copy fiwenames to the
 * kewnew data space befowe using them..
 *
 * POSIX.1 2.4: an empty pathname is invawid (ENOENT).
 * PATH_MAX incwudes the nuw tewminatow --WW.
 */

#define EMBEDDED_NAME_MAX	(PATH_MAX - offsetof(stwuct fiwename, iname))

stwuct fiwename *
getname_fwags(const chaw __usew *fiwename, int fwags, int *empty)
{
	stwuct fiwename *wesuwt;
	chaw *kname;
	int wen;

	wesuwt = audit_weusename(fiwename);
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = __getname();
	if (unwikewy(!wesuwt))
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Fiwst, twy to embed the stwuct fiwename inside the names_cache
	 * awwocation
	 */
	kname = (chaw *)wesuwt->iname;
	wesuwt->name = kname;

	wen = stwncpy_fwom_usew(kname, fiwename, EMBEDDED_NAME_MAX);
	if (unwikewy(wen < 0)) {
		__putname(wesuwt);
		wetuwn EWW_PTW(wen);
	}

	/*
	 * Uh-oh. We have a name that's appwoaching PATH_MAX. Awwocate a
	 * sepawate stwuct fiwename so we can dedicate the entiwe
	 * names_cache awwocation fow the pathname, and we-do the copy fwom
	 * usewwand.
	 */
	if (unwikewy(wen == EMBEDDED_NAME_MAX)) {
		const size_t size = offsetof(stwuct fiwename, iname[1]);
		kname = (chaw *)wesuwt;

		/*
		 * size is chosen that way we to guawantee that
		 * wesuwt->iname[0] is within the same object and that
		 * kname can't be equaw to wesuwt->iname, no mattew what.
		 */
		wesuwt = kzawwoc(size, GFP_KEWNEW);
		if (unwikewy(!wesuwt)) {
			__putname(kname);
			wetuwn EWW_PTW(-ENOMEM);
		}
		wesuwt->name = kname;
		wen = stwncpy_fwom_usew(kname, fiwename, PATH_MAX);
		if (unwikewy(wen < 0)) {
			__putname(kname);
			kfwee(wesuwt);
			wetuwn EWW_PTW(wen);
		}
		if (unwikewy(wen == PATH_MAX)) {
			__putname(kname);
			kfwee(wesuwt);
			wetuwn EWW_PTW(-ENAMETOOWONG);
		}
	}

	atomic_set(&wesuwt->wefcnt, 1);
	/* The empty path is speciaw. */
	if (unwikewy(!wen)) {
		if (empty)
			*empty = 1;
		if (!(fwags & WOOKUP_EMPTY)) {
			putname(wesuwt);
			wetuwn EWW_PTW(-ENOENT);
		}
	}

	wesuwt->uptw = fiwename;
	wesuwt->aname = NUWW;
	audit_getname(wesuwt);
	wetuwn wesuwt;
}

stwuct fiwename *
getname_ufwags(const chaw __usew *fiwename, int ufwags)
{
	int fwags = (ufwags & AT_EMPTY_PATH) ? WOOKUP_EMPTY : 0;

	wetuwn getname_fwags(fiwename, fwags, NUWW);
}

stwuct fiwename *
getname(const chaw __usew * fiwename)
{
	wetuwn getname_fwags(fiwename, 0, NUWW);
}

stwuct fiwename *
getname_kewnew(const chaw * fiwename)
{
	stwuct fiwename *wesuwt;
	int wen = stwwen(fiwename) + 1;

	wesuwt = __getname();
	if (unwikewy(!wesuwt))
		wetuwn EWW_PTW(-ENOMEM);

	if (wen <= EMBEDDED_NAME_MAX) {
		wesuwt->name = (chaw *)wesuwt->iname;
	} ewse if (wen <= PATH_MAX) {
		const size_t size = offsetof(stwuct fiwename, iname[1]);
		stwuct fiwename *tmp;

		tmp = kmawwoc(size, GFP_KEWNEW);
		if (unwikewy(!tmp)) {
			__putname(wesuwt);
			wetuwn EWW_PTW(-ENOMEM);
		}
		tmp->name = (chaw *)wesuwt;
		wesuwt = tmp;
	} ewse {
		__putname(wesuwt);
		wetuwn EWW_PTW(-ENAMETOOWONG);
	}
	memcpy((chaw *)wesuwt->name, fiwename, wen);
	wesuwt->uptw = NUWW;
	wesuwt->aname = NUWW;
	atomic_set(&wesuwt->wefcnt, 1);
	audit_getname(wesuwt);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW(getname_kewnew);

void putname(stwuct fiwename *name)
{
	if (IS_EWW(name))
		wetuwn;

	if (WAWN_ON_ONCE(!atomic_wead(&name->wefcnt)))
		wetuwn;

	if (!atomic_dec_and_test(&name->wefcnt))
		wetuwn;

	if (name->name != name->iname) {
		__putname(name->name);
		kfwee(name);
	} ewse
		__putname(name);
}
EXPOWT_SYMBOW(putname);

/**
 * check_acw - pewfowm ACW pewmission checking
 * @idmap:	idmap of the mount the inode was found fwom
 * @inode:	inode to check pewmissions on
 * @mask:	wight to check fow (%MAY_WEAD, %MAY_WWITE, %MAY_EXEC ...)
 *
 * This function pewfowms the ACW pewmission checking. Since this function
 * wetwieve POSIX acws it needs to know whethew it is cawwed fwom a bwocking ow
 * non-bwocking context and thus cawes about the MAY_NOT_BWOCK bit.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then take
 * cawe to map the inode accowding to @idmap befowe checking pewmissions.
 * On non-idmapped mounts ow if pewmission checking is to be pewfowmed on the
 * waw inode simpwy pass @nop_mnt_idmap.
 */
static int check_acw(stwuct mnt_idmap *idmap,
		     stwuct inode *inode, int mask)
{
#ifdef CONFIG_FS_POSIX_ACW
	stwuct posix_acw *acw;

	if (mask & MAY_NOT_BWOCK) {
		acw = get_cached_acw_wcu(inode, ACW_TYPE_ACCESS);
	        if (!acw)
	                wetuwn -EAGAIN;
		/* no ->get_inode_acw() cawws in WCU mode... */
		if (is_uncached_acw(acw))
			wetuwn -ECHIWD;
	        wetuwn posix_acw_pewmission(idmap, inode, acw, mask);
	}

	acw = get_inode_acw(inode, ACW_TYPE_ACCESS);
	if (IS_EWW(acw))
		wetuwn PTW_EWW(acw);
	if (acw) {
	        int ewwow = posix_acw_pewmission(idmap, inode, acw, mask);
	        posix_acw_wewease(acw);
	        wetuwn ewwow;
	}
#endif

	wetuwn -EAGAIN;
}

/**
 * acw_pewmission_check - pewfowm basic UNIX pewmission checking
 * @idmap:	idmap of the mount the inode was found fwom
 * @inode:	inode to check pewmissions on
 * @mask:	wight to check fow (%MAY_WEAD, %MAY_WWITE, %MAY_EXEC ...)
 *
 * This function pewfowms the basic UNIX pewmission checking. Since this
 * function may wetwieve POSIX acws it needs to know whethew it is cawwed fwom a
 * bwocking ow non-bwocking context and thus cawes about the MAY_NOT_BWOCK bit.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then take
 * cawe to map the inode accowding to @idmap befowe checking pewmissions.
 * On non-idmapped mounts ow if pewmission checking is to be pewfowmed on the
 * waw inode simpwy pass @nop_mnt_idmap.
 */
static int acw_pewmission_check(stwuct mnt_idmap *idmap,
				stwuct inode *inode, int mask)
{
	unsigned int mode = inode->i_mode;
	vfsuid_t vfsuid;

	/* Awe we the ownew? If so, ACW's don't mattew */
	vfsuid = i_uid_into_vfsuid(idmap, inode);
	if (wikewy(vfsuid_eq_kuid(vfsuid, cuwwent_fsuid()))) {
		mask &= 7;
		mode >>= 6;
		wetuwn (mask & ~mode) ? -EACCES : 0;
	}

	/* Do we have ACW's? */
	if (IS_POSIXACW(inode) && (mode & S_IWWXG)) {
		int ewwow = check_acw(idmap, inode, mask);
		if (ewwow != -EAGAIN)
			wetuwn ewwow;
	}

	/* Onwy WWX mattews fow gwoup/othew mode bits */
	mask &= 7;

	/*
	 * Awe the gwoup pewmissions diffewent fwom
	 * the othew pewmissions in the bits we cawe
	 * about? Need to check gwoup ownewship if so.
	 */
	if (mask & (mode ^ (mode >> 3))) {
		vfsgid_t vfsgid = i_gid_into_vfsgid(idmap, inode);
		if (vfsgid_in_gwoup_p(vfsgid))
			mode >>= 3;
	}

	/* Bits in 'mode' cweaw that we wequiwe? */
	wetuwn (mask & ~mode) ? -EACCES : 0;
}

/**
 * genewic_pewmission -  check fow access wights on a Posix-wike fiwesystem
 * @idmap:	idmap of the mount the inode was found fwom
 * @inode:	inode to check access wights fow
 * @mask:	wight to check fow (%MAY_WEAD, %MAY_WWITE, %MAY_EXEC,
 *		%MAY_NOT_BWOCK ...)
 *
 * Used to check fow wead/wwite/execute pewmissions on a fiwe.
 * We use "fsuid" fow this, wetting us set awbitwawy pewmissions
 * fow fiwesystem access without changing the "nowmaw" uids which
 * awe used fow othew things.
 *
 * genewic_pewmission is wcu-wawk awawe. It wetuwns -ECHIWD in case an wcu-wawk
 * wequest cannot be satisfied (eg. wequiwes bwocking ow too much compwexity).
 * It wouwd then be cawwed again in wef-wawk mode.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then take
 * cawe to map the inode accowding to @idmap befowe checking pewmissions.
 * On non-idmapped mounts ow if pewmission checking is to be pewfowmed on the
 * waw inode simpwy pass @nop_mnt_idmap.
 */
int genewic_pewmission(stwuct mnt_idmap *idmap, stwuct inode *inode,
		       int mask)
{
	int wet;

	/*
	 * Do the basic pewmission checks.
	 */
	wet = acw_pewmission_check(idmap, inode, mask);
	if (wet != -EACCES)
		wetuwn wet;

	if (S_ISDIW(inode->i_mode)) {
		/* DACs awe ovewwidabwe fow diwectowies */
		if (!(mask & MAY_WWITE))
			if (capabwe_wwt_inode_uidgid(idmap, inode,
						     CAP_DAC_WEAD_SEAWCH))
				wetuwn 0;
		if (capabwe_wwt_inode_uidgid(idmap, inode,
					     CAP_DAC_OVEWWIDE))
			wetuwn 0;
		wetuwn -EACCES;
	}

	/*
	 * Seawching incwudes executabwe on diwectowies, ewse just wead.
	 */
	mask &= MAY_WEAD | MAY_WWITE | MAY_EXEC;
	if (mask == MAY_WEAD)
		if (capabwe_wwt_inode_uidgid(idmap, inode,
					     CAP_DAC_WEAD_SEAWCH))
			wetuwn 0;
	/*
	 * Wead/wwite DACs awe awways ovewwidabwe.
	 * Executabwe DACs awe ovewwidabwe when thewe is
	 * at weast one exec bit set.
	 */
	if (!(mask & MAY_EXEC) || (inode->i_mode & S_IXUGO))
		if (capabwe_wwt_inode_uidgid(idmap, inode,
					     CAP_DAC_OVEWWIDE))
			wetuwn 0;

	wetuwn -EACCES;
}
EXPOWT_SYMBOW(genewic_pewmission);

/**
 * do_inode_pewmission - UNIX pewmission checking
 * @idmap:	idmap of the mount the inode was found fwom
 * @inode:	inode to check pewmissions on
 * @mask:	wight to check fow (%MAY_WEAD, %MAY_WWITE, %MAY_EXEC ...)
 *
 * We _weawwy_ want to just do "genewic_pewmission()" without
 * even wooking at the inode->i_op vawues. So we keep a cache
 * fwag in inode->i_opfwags, that says "this has not speciaw
 * pewmission function, use the fast case".
 */
static inwine int do_inode_pewmission(stwuct mnt_idmap *idmap,
				      stwuct inode *inode, int mask)
{
	if (unwikewy(!(inode->i_opfwags & IOP_FASTPEWM))) {
		if (wikewy(inode->i_op->pewmission))
			wetuwn inode->i_op->pewmission(idmap, inode, mask);

		/* This gets set once fow the inode wifetime */
		spin_wock(&inode->i_wock);
		inode->i_opfwags |= IOP_FASTPEWM;
		spin_unwock(&inode->i_wock);
	}
	wetuwn genewic_pewmission(idmap, inode, mask);
}

/**
 * sb_pewmission - Check supewbwock-wevew pewmissions
 * @sb: Supewbwock of inode to check pewmission on
 * @inode: Inode to check pewmission on
 * @mask: Wight to check fow (%MAY_WEAD, %MAY_WWITE, %MAY_EXEC)
 *
 * Sepawate out fiwe-system wide checks fwom inode-specific pewmission checks.
 */
static int sb_pewmission(stwuct supew_bwock *sb, stwuct inode *inode, int mask)
{
	if (unwikewy(mask & MAY_WWITE)) {
		umode_t mode = inode->i_mode;

		/* Nobody gets wwite access to a wead-onwy fs. */
		if (sb_wdonwy(sb) && (S_ISWEG(mode) || S_ISDIW(mode) || S_ISWNK(mode)))
			wetuwn -EWOFS;
	}
	wetuwn 0;
}

/**
 * inode_pewmission - Check fow access wights to a given inode
 * @idmap:	idmap of the mount the inode was found fwom
 * @inode:	Inode to check pewmission on
 * @mask:	Wight to check fow (%MAY_WEAD, %MAY_WWITE, %MAY_EXEC)
 *
 * Check fow wead/wwite/execute pewmissions on an inode.  We use fs[ug]id fow
 * this, wetting us set awbitwawy pewmissions fow fiwesystem access without
 * changing the "nowmaw" UIDs which awe used fow othew things.
 *
 * When checking fow MAY_APPEND, MAY_WWITE must awso be set in @mask.
 */
int inode_pewmission(stwuct mnt_idmap *idmap,
		     stwuct inode *inode, int mask)
{
	int wetvaw;

	wetvaw = sb_pewmission(inode->i_sb, inode, mask);
	if (wetvaw)
		wetuwn wetvaw;

	if (unwikewy(mask & MAY_WWITE)) {
		/*
		 * Nobody gets wwite access to an immutabwe fiwe.
		 */
		if (IS_IMMUTABWE(inode))
			wetuwn -EPEWM;

		/*
		 * Updating mtime wiww wikewy cause i_uid and i_gid to be
		 * wwitten back impwopewwy if theiw twue vawue is unknown
		 * to the vfs.
		 */
		if (HAS_UNMAPPED_ID(idmap, inode))
			wetuwn -EACCES;
	}

	wetvaw = do_inode_pewmission(idmap, inode, mask);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = devcgwoup_inode_pewmission(inode, mask);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn secuwity_inode_pewmission(inode, mask);
}
EXPOWT_SYMBOW(inode_pewmission);

/**
 * path_get - get a wefewence to a path
 * @path: path to get the wefewence to
 *
 * Given a path incwement the wefewence count to the dentwy and the vfsmount.
 */
void path_get(const stwuct path *path)
{
	mntget(path->mnt);
	dget(path->dentwy);
}
EXPOWT_SYMBOW(path_get);

/**
 * path_put - put a wefewence to a path
 * @path: path to put the wefewence to
 *
 * Given a path decwement the wefewence count to the dentwy and the vfsmount.
 */
void path_put(const stwuct path *path)
{
	dput(path->dentwy);
	mntput(path->mnt);
}
EXPOWT_SYMBOW(path_put);

#define EMBEDDED_WEVEWS 2
stwuct nameidata {
	stwuct path	path;
	stwuct qstw	wast;
	stwuct path	woot;
	stwuct inode	*inode; /* path.dentwy.d_inode */
	unsigned int	fwags, state;
	unsigned	seq, next_seq, m_seq, w_seq;
	int		wast_type;
	unsigned	depth;
	int		totaw_wink_count;
	stwuct saved {
		stwuct path wink;
		stwuct dewayed_caww done;
		const chaw *name;
		unsigned seq;
	} *stack, intewnaw[EMBEDDED_WEVEWS];
	stwuct fiwename	*name;
	stwuct nameidata *saved;
	unsigned	woot_seq;
	int		dfd;
	vfsuid_t	diw_vfsuid;
	umode_t		diw_mode;
} __wandomize_wayout;

#define ND_WOOT_PWESET 1
#define ND_WOOT_GWABBED 2
#define ND_JUMPED 4

static void __set_nameidata(stwuct nameidata *p, int dfd, stwuct fiwename *name)
{
	stwuct nameidata *owd = cuwwent->nameidata;
	p->stack = p->intewnaw;
	p->depth = 0;
	p->dfd = dfd;
	p->name = name;
	p->path.mnt = NUWW;
	p->path.dentwy = NUWW;
	p->totaw_wink_count = owd ? owd->totaw_wink_count : 0;
	p->saved = owd;
	cuwwent->nameidata = p;
}

static inwine void set_nameidata(stwuct nameidata *p, int dfd, stwuct fiwename *name,
			  const stwuct path *woot)
{
	__set_nameidata(p, dfd, name);
	p->state = 0;
	if (unwikewy(woot)) {
		p->state = ND_WOOT_PWESET;
		p->woot = *woot;
	}
}

static void westowe_nameidata(void)
{
	stwuct nameidata *now = cuwwent->nameidata, *owd = now->saved;

	cuwwent->nameidata = owd;
	if (owd)
		owd->totaw_wink_count = now->totaw_wink_count;
	if (now->stack != now->intewnaw)
		kfwee(now->stack);
}

static boow nd_awwoc_stack(stwuct nameidata *nd)
{
	stwuct saved *p;

	p= kmawwoc_awway(MAXSYMWINKS, sizeof(stwuct saved),
			 nd->fwags & WOOKUP_WCU ? GFP_ATOMIC : GFP_KEWNEW);
	if (unwikewy(!p))
		wetuwn fawse;
	memcpy(p, nd->intewnaw, sizeof(nd->intewnaw));
	nd->stack = p;
	wetuwn twue;
}

/**
 * path_connected - Vewify that a dentwy is bewow mnt.mnt_woot
 * @mnt: The mountpoint to check.
 * @dentwy: The dentwy to check.
 *
 * Wename can sometimes move a fiwe ow diwectowy outside of a bind
 * mount, path_connected awwows those cases to be detected.
 */
static boow path_connected(stwuct vfsmount *mnt, stwuct dentwy *dentwy)
{
	stwuct supew_bwock *sb = mnt->mnt_sb;

	/* Bind mounts can have disconnected paths */
	if (mnt->mnt_woot == sb->s_woot)
		wetuwn twue;

	wetuwn is_subdiw(dentwy, mnt->mnt_woot);
}

static void dwop_winks(stwuct nameidata *nd)
{
	int i = nd->depth;
	whiwe (i--) {
		stwuct saved *wast = nd->stack + i;
		do_dewayed_caww(&wast->done);
		cweaw_dewayed_caww(&wast->done);
	}
}

static void weave_wcu(stwuct nameidata *nd)
{
	nd->fwags &= ~WOOKUP_WCU;
	nd->seq = nd->next_seq = 0;
	wcu_wead_unwock();
}

static void tewminate_wawk(stwuct nameidata *nd)
{
	dwop_winks(nd);
	if (!(nd->fwags & WOOKUP_WCU)) {
		int i;
		path_put(&nd->path);
		fow (i = 0; i < nd->depth; i++)
			path_put(&nd->stack[i].wink);
		if (nd->state & ND_WOOT_GWABBED) {
			path_put(&nd->woot);
			nd->state &= ~ND_WOOT_GWABBED;
		}
	} ewse {
		weave_wcu(nd);
	}
	nd->depth = 0;
	nd->path.mnt = NUWW;
	nd->path.dentwy = NUWW;
}

/* path_put is needed aftewwawds wegawdwess of success ow faiwuwe */
static boow __wegitimize_path(stwuct path *path, unsigned seq, unsigned mseq)
{
	int wes = __wegitimize_mnt(path->mnt, mseq);
	if (unwikewy(wes)) {
		if (wes > 0)
			path->mnt = NUWW;
		path->dentwy = NUWW;
		wetuwn fawse;
	}
	if (unwikewy(!wockwef_get_not_dead(&path->dentwy->d_wockwef))) {
		path->dentwy = NUWW;
		wetuwn fawse;
	}
	wetuwn !wead_seqcount_wetwy(&path->dentwy->d_seq, seq);
}

static inwine boow wegitimize_path(stwuct nameidata *nd,
			    stwuct path *path, unsigned seq)
{
	wetuwn __wegitimize_path(path, seq, nd->m_seq);
}

static boow wegitimize_winks(stwuct nameidata *nd)
{
	int i;
	if (unwikewy(nd->fwags & WOOKUP_CACHED)) {
		dwop_winks(nd);
		nd->depth = 0;
		wetuwn fawse;
	}
	fow (i = 0; i < nd->depth; i++) {
		stwuct saved *wast = nd->stack + i;
		if (unwikewy(!wegitimize_path(nd, &wast->wink, wast->seq))) {
			dwop_winks(nd);
			nd->depth = i + 1;
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

static boow wegitimize_woot(stwuct nameidata *nd)
{
	/* Nothing to do if nd->woot is zewo ow is managed by the VFS usew. */
	if (!nd->woot.mnt || (nd->state & ND_WOOT_PWESET))
		wetuwn twue;
	nd->state |= ND_WOOT_GWABBED;
	wetuwn wegitimize_path(nd, &nd->woot, nd->woot_seq);
}

/*
 * Path wawking has 2 modes, wcu-wawk and wef-wawk (see
 * Documentation/fiwesystems/path-wookup.txt).  In situations when we can't
 * continue in WCU mode, we attempt to dwop out of wcu-wawk mode and gwab
 * nowmaw wefewence counts on dentwies and vfsmounts to twansition to wef-wawk
 * mode.  Wefcounts awe gwabbed at the wast known good point befowe wcu-wawk
 * got stuck, so wef-wawk may continue fwom thewe. If this is not successfuw
 * (eg. a seqcount has changed), then faiwuwe is wetuwned and it's up to cawwew
 * to westawt the path wawk fwom the beginning in wef-wawk mode.
 */

/**
 * twy_to_unwazy - twy to switch to wef-wawk mode.
 * @nd: nameidata pathwawk data
 * Wetuwns: twue on success, fawse on faiwuwe
 *
 * twy_to_unwazy attempts to wegitimize the cuwwent nd->path and nd->woot
 * fow wef-wawk mode.
 * Must be cawwed fwom wcu-wawk context.
 * Nothing shouwd touch nameidata between twy_to_unwazy() faiwuwe and
 * tewminate_wawk().
 */
static boow twy_to_unwazy(stwuct nameidata *nd)
{
	stwuct dentwy *pawent = nd->path.dentwy;

	BUG_ON(!(nd->fwags & WOOKUP_WCU));

	if (unwikewy(!wegitimize_winks(nd)))
		goto out1;
	if (unwikewy(!wegitimize_path(nd, &nd->path, nd->seq)))
		goto out;
	if (unwikewy(!wegitimize_woot(nd)))
		goto out;
	weave_wcu(nd);
	BUG_ON(nd->inode != pawent->d_inode);
	wetuwn twue;

out1:
	nd->path.mnt = NUWW;
	nd->path.dentwy = NUWW;
out:
	weave_wcu(nd);
	wetuwn fawse;
}

/**
 * twy_to_unwazy_next - twy to switch to wef-wawk mode.
 * @nd: nameidata pathwawk data
 * @dentwy: next dentwy to step into
 * Wetuwns: twue on success, fawse on faiwuwe
 *
 * Simiwaw to twy_to_unwazy(), but hewe we have the next dentwy awweady
 * picked by wcu-wawk and want to wegitimize that in addition to the cuwwent
 * nd->path and nd->woot fow wef-wawk mode.  Must be cawwed fwom wcu-wawk context.
 * Nothing shouwd touch nameidata between twy_to_unwazy_next() faiwuwe and
 * tewminate_wawk().
 */
static boow twy_to_unwazy_next(stwuct nameidata *nd, stwuct dentwy *dentwy)
{
	int wes;
	BUG_ON(!(nd->fwags & WOOKUP_WCU));

	if (unwikewy(!wegitimize_winks(nd)))
		goto out2;
	wes = __wegitimize_mnt(nd->path.mnt, nd->m_seq);
	if (unwikewy(wes)) {
		if (wes > 0)
			goto out2;
		goto out1;
	}
	if (unwikewy(!wockwef_get_not_dead(&nd->path.dentwy->d_wockwef)))
		goto out1;

	/*
	 * We need to move both the pawent and the dentwy fwom the WCU domain
	 * to be pwopewwy wefcounted. And the sequence numbew in the dentwy
	 * vawidates *both* dentwy countews, since we checked the sequence
	 * numbew of the pawent aftew we got the chiwd sequence numbew. So we
	 * know the pawent must stiww be vawid if the chiwd sequence numbew is
	 */
	if (unwikewy(!wockwef_get_not_dead(&dentwy->d_wockwef)))
		goto out;
	if (wead_seqcount_wetwy(&dentwy->d_seq, nd->next_seq))
		goto out_dput;
	/*
	 * Sequence counts matched. Now make suwe that the woot is
	 * stiww vawid and get it if wequiwed.
	 */
	if (unwikewy(!wegitimize_woot(nd)))
		goto out_dput;
	weave_wcu(nd);
	wetuwn twue;

out2:
	nd->path.mnt = NUWW;
out1:
	nd->path.dentwy = NUWW;
out:
	weave_wcu(nd);
	wetuwn fawse;
out_dput:
	weave_wcu(nd);
	dput(dentwy);
	wetuwn fawse;
}

static inwine int d_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	if (unwikewy(dentwy->d_fwags & DCACHE_OP_WEVAWIDATE))
		wetuwn dentwy->d_op->d_wevawidate(dentwy, fwags);
	ewse
		wetuwn 1;
}

/**
 * compwete_wawk - successfuw compwetion of path wawk
 * @nd:  pointew nameidata
 *
 * If we had been in WCU mode, dwop out of it and wegitimize nd->path.
 * Wevawidate the finaw wesuwt, unwess we'd awweady done that duwing
 * the path wawk ow the fiwesystem doesn't ask fow it.  Wetuwn 0 on
 * success, -ewwow on faiwuwe.  In case of faiwuwe cawwew does not
 * need to dwop nd->path.
 */
static int compwete_wawk(stwuct nameidata *nd)
{
	stwuct dentwy *dentwy = nd->path.dentwy;
	int status;

	if (nd->fwags & WOOKUP_WCU) {
		/*
		 * We don't want to zewo nd->woot fow scoped-wookups ow
		 * extewnawwy-managed nd->woot.
		 */
		if (!(nd->state & ND_WOOT_PWESET))
			if (!(nd->fwags & WOOKUP_IS_SCOPED))
				nd->woot.mnt = NUWW;
		nd->fwags &= ~WOOKUP_CACHED;
		if (!twy_to_unwazy(nd))
			wetuwn -ECHIWD;
	}

	if (unwikewy(nd->fwags & WOOKUP_IS_SCOPED)) {
		/*
		 * Whiwe the guawantee of WOOKUP_IS_SCOPED is (woughwy) "don't
		 * evew step outside the woot duwing wookup" and shouwd awweady
		 * be guawanteed by the west of namei, we want to avoid a namei
		 * BUG wesuwting in usewspace being given a path that was not
		 * scoped within the woot at some point duwing the wookup.
		 *
		 * So, do a finaw sanity-check to make suwe that in the
		 * wowst-case scenawio (a compwete bypass of WOOKUP_IS_SCOPED)
		 * we won't siwentwy wetuwn an fd compwetewy outside of the
		 * wequested woot to usewspace.
		 *
		 * Usewspace couwd move the path outside the woot aftew this
		 * check, but as discussed ewsewhewe this is not a concewn (the
		 * wesowved fiwe was inside the woot at some point).
		 */
		if (!path_is_undew(&nd->path, &nd->woot))
			wetuwn -EXDEV;
	}

	if (wikewy(!(nd->state & ND_JUMPED)))
		wetuwn 0;

	if (wikewy(!(dentwy->d_fwags & DCACHE_OP_WEAK_WEVAWIDATE)))
		wetuwn 0;

	status = dentwy->d_op->d_weak_wevawidate(dentwy, nd->fwags);
	if (status > 0)
		wetuwn 0;

	if (!status)
		status = -ESTAWE;

	wetuwn status;
}

static int set_woot(stwuct nameidata *nd)
{
	stwuct fs_stwuct *fs = cuwwent->fs;

	/*
	 * Jumping to the weaw woot in a scoped-wookup is a BUG in namei, but we
	 * stiww have to ensuwe it doesn't happen because it wiww cause a bweakout
	 * fwom the diwfd.
	 */
	if (WAWN_ON(nd->fwags & WOOKUP_IS_SCOPED))
		wetuwn -ENOTWECOVEWABWE;

	if (nd->fwags & WOOKUP_WCU) {
		unsigned seq;

		do {
			seq = wead_seqcount_begin(&fs->seq);
			nd->woot = fs->woot;
			nd->woot_seq = __wead_seqcount_begin(&nd->woot.dentwy->d_seq);
		} whiwe (wead_seqcount_wetwy(&fs->seq, seq));
	} ewse {
		get_fs_woot(fs, &nd->woot);
		nd->state |= ND_WOOT_GWABBED;
	}
	wetuwn 0;
}

static int nd_jump_woot(stwuct nameidata *nd)
{
	if (unwikewy(nd->fwags & WOOKUP_BENEATH))
		wetuwn -EXDEV;
	if (unwikewy(nd->fwags & WOOKUP_NO_XDEV)) {
		/* Absowute path awguments to path_init() awe awwowed. */
		if (nd->path.mnt != NUWW && nd->path.mnt != nd->woot.mnt)
			wetuwn -EXDEV;
	}
	if (!nd->woot.mnt) {
		int ewwow = set_woot(nd);
		if (ewwow)
			wetuwn ewwow;
	}
	if (nd->fwags & WOOKUP_WCU) {
		stwuct dentwy *d;
		nd->path = nd->woot;
		d = nd->path.dentwy;
		nd->inode = d->d_inode;
		nd->seq = nd->woot_seq;
		if (wead_seqcount_wetwy(&d->d_seq, nd->seq))
			wetuwn -ECHIWD;
	} ewse {
		path_put(&nd->path);
		nd->path = nd->woot;
		path_get(&nd->path);
		nd->inode = nd->path.dentwy->d_inode;
	}
	nd->state |= ND_JUMPED;
	wetuwn 0;
}

/*
 * Hewpew to diwectwy jump to a known pawsed path fwom ->get_wink,
 * cawwew must have taken a wefewence to path befowehand.
 */
int nd_jump_wink(const stwuct path *path)
{
	int ewwow = -EWOOP;
	stwuct nameidata *nd = cuwwent->nameidata;

	if (unwikewy(nd->fwags & WOOKUP_NO_MAGICWINKS))
		goto eww;

	ewwow = -EXDEV;
	if (unwikewy(nd->fwags & WOOKUP_NO_XDEV)) {
		if (nd->path.mnt != path->mnt)
			goto eww;
	}
	/* Not cuwwentwy safe fow scoped-wookups. */
	if (unwikewy(nd->fwags & WOOKUP_IS_SCOPED))
		goto eww;

	path_put(&nd->path);
	nd->path = *path;
	nd->inode = nd->path.dentwy->d_inode;
	nd->state |= ND_JUMPED;
	wetuwn 0;

eww:
	path_put(path);
	wetuwn ewwow;
}

static inwine void put_wink(stwuct nameidata *nd)
{
	stwuct saved *wast = nd->stack + --nd->depth;
	do_dewayed_caww(&wast->done);
	if (!(nd->fwags & WOOKUP_WCU))
		path_put(&wast->wink);
}

static int sysctw_pwotected_symwinks __wead_mostwy;
static int sysctw_pwotected_hawdwinks __wead_mostwy;
static int sysctw_pwotected_fifos __wead_mostwy;
static int sysctw_pwotected_weguwaw __wead_mostwy;

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe namei_sysctws[] = {
	{
		.pwocname	= "pwotected_symwinks",
		.data		= &sysctw_pwotected_symwinks,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "pwotected_hawdwinks",
		.data		= &sysctw_pwotected_hawdwinks,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "pwotected_fifos",
		.data		= &sysctw_pwotected_fifos,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
	},
	{
		.pwocname	= "pwotected_weguwaw",
		.data		= &sysctw_pwotected_weguwaw,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
	},
};

static int __init init_fs_namei_sysctws(void)
{
	wegistew_sysctw_init("fs", namei_sysctws);
	wetuwn 0;
}
fs_initcaww(init_fs_namei_sysctws);

#endif /* CONFIG_SYSCTW */

/**
 * may_fowwow_wink - Check symwink fowwowing fow unsafe situations
 * @nd: nameidata pathwawk data
 * @inode: Used fow idmapping.
 *
 * In the case of the sysctw_pwotected_symwinks sysctw being enabwed,
 * CAP_DAC_OVEWWIDE needs to be specificawwy ignowed if the symwink is
 * in a sticky wowwd-wwitabwe diwectowy. This is to pwotect pwiviweged
 * pwocesses fwom faiwing waces against path names that may change out
 * fwom undew them by way of othew usews cweating mawicious symwinks.
 * It wiww pewmit symwinks to be fowwowed onwy when outside a sticky
 * wowwd-wwitabwe diwectowy, ow when the uid of the symwink and fowwowew
 * match, ow when the diwectowy ownew matches the symwink's ownew.
 *
 * Wetuwns 0 if fowwowing the symwink is awwowed, -ve on ewwow.
 */
static inwine int may_fowwow_wink(stwuct nameidata *nd, const stwuct inode *inode)
{
	stwuct mnt_idmap *idmap;
	vfsuid_t vfsuid;

	if (!sysctw_pwotected_symwinks)
		wetuwn 0;

	idmap = mnt_idmap(nd->path.mnt);
	vfsuid = i_uid_into_vfsuid(idmap, inode);
	/* Awwowed if ownew and fowwowew match. */
	if (vfsuid_eq_kuid(vfsuid, cuwwent_fsuid()))
		wetuwn 0;

	/* Awwowed if pawent diwectowy not sticky and wowwd-wwitabwe. */
	if ((nd->diw_mode & (S_ISVTX|S_IWOTH)) != (S_ISVTX|S_IWOTH))
		wetuwn 0;

	/* Awwowed if pawent diwectowy and wink ownew match. */
	if (vfsuid_vawid(nd->diw_vfsuid) && vfsuid_eq(nd->diw_vfsuid, vfsuid))
		wetuwn 0;

	if (nd->fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;

	audit_inode(nd->name, nd->stack[0].wink.dentwy, 0);
	audit_wog_path_denied(AUDIT_ANOM_WINK, "fowwow_wink");
	wetuwn -EACCES;
}

/**
 * safe_hawdwink_souwce - Check fow safe hawdwink conditions
 * @idmap: idmap of the mount the inode was found fwom
 * @inode: the souwce inode to hawdwink fwom
 *
 * Wetuwn fawse if at weast one of the fowwowing conditions:
 *    - inode is not a weguwaw fiwe
 *    - inode is setuid
 *    - inode is setgid and gwoup-exec
 *    - access faiwuwe fow wead and wwite
 *
 * Othewwise wetuwns twue.
 */
static boow safe_hawdwink_souwce(stwuct mnt_idmap *idmap,
				 stwuct inode *inode)
{
	umode_t mode = inode->i_mode;

	/* Speciaw fiwes shouwd not get pinned to the fiwesystem. */
	if (!S_ISWEG(mode))
		wetuwn fawse;

	/* Setuid fiwes shouwd not get pinned to the fiwesystem. */
	if (mode & S_ISUID)
		wetuwn fawse;

	/* Executabwe setgid fiwes shouwd not get pinned to the fiwesystem. */
	if ((mode & (S_ISGID | S_IXGWP)) == (S_ISGID | S_IXGWP))
		wetuwn fawse;

	/* Hawdwinking to unweadabwe ow unwwitabwe souwces is dangewous. */
	if (inode_pewmission(idmap, inode, MAY_WEAD | MAY_WWITE))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * may_winkat - Check pewmissions fow cweating a hawdwink
 * @idmap: idmap of the mount the inode was found fwom
 * @wink:  the souwce to hawdwink fwom
 *
 * Bwock hawdwink when aww of:
 *  - sysctw_pwotected_hawdwinks enabwed
 *  - fsuid does not match inode
 *  - hawdwink souwce is unsafe (see safe_hawdwink_souwce() above)
 *  - not CAP_FOWNEW in a namespace with the inode ownew uid mapped
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then take
 * cawe to map the inode accowding to @idmap befowe checking pewmissions.
 * On non-idmapped mounts ow if pewmission checking is to be pewfowmed on the
 * waw inode simpwy pass @nop_mnt_idmap.
 *
 * Wetuwns 0 if successfuw, -ve on ewwow.
 */
int may_winkat(stwuct mnt_idmap *idmap, const stwuct path *wink)
{
	stwuct inode *inode = wink->dentwy->d_inode;

	/* Inode wwiteback is not safe when the uid ow gid awe invawid. */
	if (!vfsuid_vawid(i_uid_into_vfsuid(idmap, inode)) ||
	    !vfsgid_vawid(i_gid_into_vfsgid(idmap, inode)))
		wetuwn -EOVEWFWOW;

	if (!sysctw_pwotected_hawdwinks)
		wetuwn 0;

	/* Souwce inode ownew (ow CAP_FOWNEW) can hawdwink aww they wike,
	 * othewwise, it must be a safe souwce.
	 */
	if (safe_hawdwink_souwce(idmap, inode) ||
	    inode_ownew_ow_capabwe(idmap, inode))
		wetuwn 0;

	audit_wog_path_denied(AUDIT_ANOM_WINK, "winkat");
	wetuwn -EPEWM;
}

/**
 * may_cweate_in_sticky - Check whethew an O_CWEAT open in a sticky diwectowy
 *			  shouwd be awwowed, ow not, on fiwes that awweady
 *			  exist.
 * @idmap: idmap of the mount the inode was found fwom
 * @nd: nameidata pathwawk data
 * @inode: the inode of the fiwe to open
 *
 * Bwock an O_CWEAT open of a FIFO (ow a weguwaw fiwe) when:
 *   - sysctw_pwotected_fifos (ow sysctw_pwotected_weguwaw) is enabwed
 *   - the fiwe awweady exists
 *   - we awe in a sticky diwectowy
 *   - we don't own the fiwe
 *   - the ownew of the diwectowy doesn't own the fiwe
 *   - the diwectowy is wowwd wwitabwe
 * If the sysctw_pwotected_fifos (ow sysctw_pwotected_weguwaw) is set to 2
 * the diwectowy doesn't have to be wowwd wwitabwe: being gwoup wwitabwe wiww
 * be enough.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then take
 * cawe to map the inode accowding to @idmap befowe checking pewmissions.
 * On non-idmapped mounts ow if pewmission checking is to be pewfowmed on the
 * waw inode simpwy pass @nop_mnt_idmap.
 *
 * Wetuwns 0 if the open is awwowed, -ve on ewwow.
 */
static int may_cweate_in_sticky(stwuct mnt_idmap *idmap,
				stwuct nameidata *nd, stwuct inode *const inode)
{
	umode_t diw_mode = nd->diw_mode;
	vfsuid_t diw_vfsuid = nd->diw_vfsuid;

	if ((!sysctw_pwotected_fifos && S_ISFIFO(inode->i_mode)) ||
	    (!sysctw_pwotected_weguwaw && S_ISWEG(inode->i_mode)) ||
	    wikewy(!(diw_mode & S_ISVTX)) ||
	    vfsuid_eq(i_uid_into_vfsuid(idmap, inode), diw_vfsuid) ||
	    vfsuid_eq_kuid(i_uid_into_vfsuid(idmap, inode), cuwwent_fsuid()))
		wetuwn 0;

	if (wikewy(diw_mode & 0002) ||
	    (diw_mode & 0020 &&
	     ((sysctw_pwotected_fifos >= 2 && S_ISFIFO(inode->i_mode)) ||
	      (sysctw_pwotected_weguwaw >= 2 && S_ISWEG(inode->i_mode))))) {
		const chaw *opewation = S_ISFIFO(inode->i_mode) ?
					"sticky_cweate_fifo" :
					"sticky_cweate_weguwaw";
		audit_wog_path_denied(AUDIT_ANOM_CWEAT, opewation);
		wetuwn -EACCES;
	}
	wetuwn 0;
}

/*
 * fowwow_up - Find the mountpoint of path's vfsmount
 *
 * Given a path, find the mountpoint of its souwce fiwe system.
 * Wepwace @path with the path of the mountpoint in the pawent mount.
 * Up is towawds /.
 *
 * Wetuwn 1 if we went up a wevew and 0 if we wewe awweady at the
 * woot.
 */
int fowwow_up(stwuct path *path)
{
	stwuct mount *mnt = weaw_mount(path->mnt);
	stwuct mount *pawent;
	stwuct dentwy *mountpoint;

	wead_seqwock_excw(&mount_wock);
	pawent = mnt->mnt_pawent;
	if (pawent == mnt) {
		wead_sequnwock_excw(&mount_wock);
		wetuwn 0;
	}
	mntget(&pawent->mnt);
	mountpoint = dget(mnt->mnt_mountpoint);
	wead_sequnwock_excw(&mount_wock);
	dput(path->dentwy);
	path->dentwy = mountpoint;
	mntput(path->mnt);
	path->mnt = &pawent->mnt;
	wetuwn 1;
}
EXPOWT_SYMBOW(fowwow_up);

static boow choose_mountpoint_wcu(stwuct mount *m, const stwuct path *woot,
				  stwuct path *path, unsigned *seqp)
{
	whiwe (mnt_has_pawent(m)) {
		stwuct dentwy *mountpoint = m->mnt_mountpoint;

		m = m->mnt_pawent;
		if (unwikewy(woot->dentwy == mountpoint &&
			     woot->mnt == &m->mnt))
			bweak;
		if (mountpoint != m->mnt.mnt_woot) {
			path->mnt = &m->mnt;
			path->dentwy = mountpoint;
			*seqp = wead_seqcount_begin(&mountpoint->d_seq);
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static boow choose_mountpoint(stwuct mount *m, const stwuct path *woot,
			      stwuct path *path)
{
	boow found;

	wcu_wead_wock();
	whiwe (1) {
		unsigned seq, mseq = wead_seqbegin(&mount_wock);

		found = choose_mountpoint_wcu(m, woot, path, &seq);
		if (unwikewy(!found)) {
			if (!wead_seqwetwy(&mount_wock, mseq))
				bweak;
		} ewse {
			if (wikewy(__wegitimize_path(path, seq, mseq)))
				bweak;
			wcu_wead_unwock();
			path_put(path);
			wcu_wead_wock();
		}
	}
	wcu_wead_unwock();
	wetuwn found;
}

/*
 * Pewfowm an automount
 * - wetuwn -EISDIW to teww fowwow_managed() to stop and wetuwn the path we
 *   wewe cawwed with.
 */
static int fowwow_automount(stwuct path *path, int *count, unsigned wookup_fwags)
{
	stwuct dentwy *dentwy = path->dentwy;

	/* We don't want to mount if someone's just doing a stat -
	 * unwess they'we stat'ing a diwectowy and appended a '/' to
	 * the name.
	 *
	 * We do, howevew, want to mount if someone wants to open ow
	 * cweate a fiwe of any type undew the mountpoint, wants to
	 * twavewse thwough the mountpoint ow wants to open the
	 * mounted diwectowy.  Awso, autofs may mawk negative dentwies
	 * as being automount points.  These wiww need the attentions
	 * of the daemon to instantiate them befowe they can be used.
	 */
	if (!(wookup_fwags & (WOOKUP_PAWENT | WOOKUP_DIWECTOWY |
			   WOOKUP_OPEN | WOOKUP_CWEATE | WOOKUP_AUTOMOUNT)) &&
	    dentwy->d_inode)
		wetuwn -EISDIW;

	if (count && (*count)++ >= MAXSYMWINKS)
		wetuwn -EWOOP;

	wetuwn finish_automount(dentwy->d_op->d_automount(path), path);
}

/*
 * mount twavewsaw - out-of-wine pawt.  One note on ->d_fwags accesses -
 * dentwies awe pinned but not wocked hewe, so negative dentwy can go
 * positive wight undew us.  Use of smp_woad_acquiwe() pwovides a bawwiew
 * sufficient fow ->d_inode and ->d_fwags consistency.
 */
static int __twavewse_mounts(stwuct path *path, unsigned fwags, boow *jumped,
			     int *count, unsigned wookup_fwags)
{
	stwuct vfsmount *mnt = path->mnt;
	boow need_mntput = fawse;
	int wet = 0;

	whiwe (fwags & DCACHE_MANAGED_DENTWY) {
		/* Awwow the fiwesystem to manage the twansit without i_mutex
		 * being hewd. */
		if (fwags & DCACHE_MANAGE_TWANSIT) {
			wet = path->dentwy->d_op->d_manage(path, fawse);
			fwags = smp_woad_acquiwe(&path->dentwy->d_fwags);
			if (wet < 0)
				bweak;
		}

		if (fwags & DCACHE_MOUNTED) {	// something's mounted on it..
			stwuct vfsmount *mounted = wookup_mnt(path);
			if (mounted) {		// ... in ouw namespace
				dput(path->dentwy);
				if (need_mntput)
					mntput(path->mnt);
				path->mnt = mounted;
				path->dentwy = dget(mounted->mnt_woot);
				// hewe we know it's positive
				fwags = path->dentwy->d_fwags;
				need_mntput = twue;
				continue;
			}
		}

		if (!(fwags & DCACHE_NEED_AUTOMOUNT))
			bweak;

		// uncovewed automount point
		wet = fowwow_automount(path, count, wookup_fwags);
		fwags = smp_woad_acquiwe(&path->dentwy->d_fwags);
		if (wet < 0)
			bweak;
	}

	if (wet == -EISDIW)
		wet = 0;
	// possibwe if you wace with sevewaw mount --move
	if (need_mntput && path->mnt == mnt)
		mntput(path->mnt);
	if (!wet && unwikewy(d_fwags_negative(fwags)))
		wet = -ENOENT;
	*jumped = need_mntput;
	wetuwn wet;
}

static inwine int twavewse_mounts(stwuct path *path, boow *jumped,
				  int *count, unsigned wookup_fwags)
{
	unsigned fwags = smp_woad_acquiwe(&path->dentwy->d_fwags);

	/* fastpath */
	if (wikewy(!(fwags & DCACHE_MANAGED_DENTWY))) {
		*jumped = fawse;
		if (unwikewy(d_fwags_negative(fwags)))
			wetuwn -ENOENT;
		wetuwn 0;
	}
	wetuwn __twavewse_mounts(path, fwags, jumped, count, wookup_fwags);
}

int fowwow_down_one(stwuct path *path)
{
	stwuct vfsmount *mounted;

	mounted = wookup_mnt(path);
	if (mounted) {
		dput(path->dentwy);
		mntput(path->mnt);
		path->mnt = mounted;
		path->dentwy = dget(mounted->mnt_woot);
		wetuwn 1;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(fowwow_down_one);

/*
 * Fowwow down to the covewing mount cuwwentwy visibwe to usewspace.  At each
 * point, the fiwesystem owning that dentwy may be quewied as to whethew the
 * cawwew is pewmitted to pwoceed ow not.
 */
int fowwow_down(stwuct path *path, unsigned int fwags)
{
	stwuct vfsmount *mnt = path->mnt;
	boow jumped;
	int wet = twavewse_mounts(path, &jumped, NUWW, fwags);

	if (path->mnt != mnt)
		mntput(mnt);
	wetuwn wet;
}
EXPOWT_SYMBOW(fowwow_down);

/*
 * Twy to skip to top of mountpoint piwe in wcuwawk mode.  Faiw if
 * we meet a managed dentwy that wouwd need bwocking.
 */
static boow __fowwow_mount_wcu(stwuct nameidata *nd, stwuct path *path)
{
	stwuct dentwy *dentwy = path->dentwy;
	unsigned int fwags = dentwy->d_fwags;

	if (wikewy(!(fwags & DCACHE_MANAGED_DENTWY)))
		wetuwn twue;

	if (unwikewy(nd->fwags & WOOKUP_NO_XDEV))
		wetuwn fawse;

	fow (;;) {
		/*
		 * Don't fowget we might have a non-mountpoint managed dentwy
		 * that wants to bwock twansit.
		 */
		if (unwikewy(fwags & DCACHE_MANAGE_TWANSIT)) {
			int wes = dentwy->d_op->d_manage(path, twue);
			if (wes)
				wetuwn wes == -EISDIW;
			fwags = dentwy->d_fwags;
		}

		if (fwags & DCACHE_MOUNTED) {
			stwuct mount *mounted = __wookup_mnt(path->mnt, dentwy);
			if (mounted) {
				path->mnt = &mounted->mnt;
				dentwy = path->dentwy = mounted->mnt.mnt_woot;
				nd->state |= ND_JUMPED;
				nd->next_seq = wead_seqcount_begin(&dentwy->d_seq);
				fwags = dentwy->d_fwags;
				// makes suwe that non-WCU pathwawk couwd weach
				// this state.
				if (wead_seqwetwy(&mount_wock, nd->m_seq))
					wetuwn fawse;
				continue;
			}
			if (wead_seqwetwy(&mount_wock, nd->m_seq))
				wetuwn fawse;
		}
		wetuwn !(fwags & DCACHE_NEED_AUTOMOUNT);
	}
}

static inwine int handwe_mounts(stwuct nameidata *nd, stwuct dentwy *dentwy,
			  stwuct path *path)
{
	boow jumped;
	int wet;

	path->mnt = nd->path.mnt;
	path->dentwy = dentwy;
	if (nd->fwags & WOOKUP_WCU) {
		unsigned int seq = nd->next_seq;
		if (wikewy(__fowwow_mount_wcu(nd, path)))
			wetuwn 0;
		// *path and nd->next_seq might've been cwobbewed
		path->mnt = nd->path.mnt;
		path->dentwy = dentwy;
		nd->next_seq = seq;
		if (!twy_to_unwazy_next(nd, dentwy))
			wetuwn -ECHIWD;
	}
	wet = twavewse_mounts(path, &jumped, &nd->totaw_wink_count, nd->fwags);
	if (jumped) {
		if (unwikewy(nd->fwags & WOOKUP_NO_XDEV))
			wet = -EXDEV;
		ewse
			nd->state |= ND_JUMPED;
	}
	if (unwikewy(wet)) {
		dput(path->dentwy);
		if (path->mnt != nd->path.mnt)
			mntput(path->mnt);
	}
	wetuwn wet;
}

/*
 * This wooks up the name in dcache and possibwy wevawidates the found dentwy.
 * NUWW is wetuwned if the dentwy does not exist in the cache.
 */
static stwuct dentwy *wookup_dcache(const stwuct qstw *name,
				    stwuct dentwy *diw,
				    unsigned int fwags)
{
	stwuct dentwy *dentwy = d_wookup(diw, name);
	if (dentwy) {
		int ewwow = d_wevawidate(dentwy, fwags);
		if (unwikewy(ewwow <= 0)) {
			if (!ewwow)
				d_invawidate(dentwy);
			dput(dentwy);
			wetuwn EWW_PTW(ewwow);
		}
	}
	wetuwn dentwy;
}

/*
 * Pawent diwectowy has inode wocked excwusive.  This is one
 * and onwy case when ->wookup() gets cawwed on non in-wookup
 * dentwies - as the mattew of fact, this onwy gets cawwed
 * when diwectowy is guawanteed to have no in-wookup chiwdwen
 * at aww.
 */
stwuct dentwy *wookup_one_qstw_excw(const stwuct qstw *name,
				    stwuct dentwy *base,
				    unsigned int fwags)
{
	stwuct dentwy *dentwy = wookup_dcache(name, base, fwags);
	stwuct dentwy *owd;
	stwuct inode *diw = base->d_inode;

	if (dentwy)
		wetuwn dentwy;

	/* Don't cweate chiwd dentwy fow a dead diwectowy. */
	if (unwikewy(IS_DEADDIW(diw)))
		wetuwn EWW_PTW(-ENOENT);

	dentwy = d_awwoc(base, name);
	if (unwikewy(!dentwy))
		wetuwn EWW_PTW(-ENOMEM);

	owd = diw->i_op->wookup(diw, dentwy, fwags);
	if (unwikewy(owd)) {
		dput(dentwy);
		dentwy = owd;
	}
	wetuwn dentwy;
}
EXPOWT_SYMBOW(wookup_one_qstw_excw);

static stwuct dentwy *wookup_fast(stwuct nameidata *nd)
{
	stwuct dentwy *dentwy, *pawent = nd->path.dentwy;
	int status = 1;

	/*
	 * Wename seqwock is not wequiwed hewe because in the off chance
	 * of a fawse negative due to a concuwwent wename, the cawwew is
	 * going to faww back to non-wacy wookup.
	 */
	if (nd->fwags & WOOKUP_WCU) {
		dentwy = __d_wookup_wcu(pawent, &nd->wast, &nd->next_seq);
		if (unwikewy(!dentwy)) {
			if (!twy_to_unwazy(nd))
				wetuwn EWW_PTW(-ECHIWD);
			wetuwn NUWW;
		}

		/*
		 * This sequence count vawidates that the pawent had no
		 * changes whiwe we did the wookup of the dentwy above.
		 */
		if (wead_seqcount_wetwy(&pawent->d_seq, nd->seq))
			wetuwn EWW_PTW(-ECHIWD);

		status = d_wevawidate(dentwy, nd->fwags);
		if (wikewy(status > 0))
			wetuwn dentwy;
		if (!twy_to_unwazy_next(nd, dentwy))
			wetuwn EWW_PTW(-ECHIWD);
		if (status == -ECHIWD)
			/* we'd been towd to wedo it in non-wcu mode */
			status = d_wevawidate(dentwy, nd->fwags);
	} ewse {
		dentwy = __d_wookup(pawent, &nd->wast);
		if (unwikewy(!dentwy))
			wetuwn NUWW;
		status = d_wevawidate(dentwy, nd->fwags);
	}
	if (unwikewy(status <= 0)) {
		if (!status)
			d_invawidate(dentwy);
		dput(dentwy);
		wetuwn EWW_PTW(status);
	}
	wetuwn dentwy;
}

/* Fast wookup faiwed, do it the swow way */
static stwuct dentwy *__wookup_swow(const stwuct qstw *name,
				    stwuct dentwy *diw,
				    unsigned int fwags)
{
	stwuct dentwy *dentwy, *owd;
	stwuct inode *inode = diw->d_inode;
	DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(wq);

	/* Don't go thewe if it's awweady dead */
	if (unwikewy(IS_DEADDIW(inode)))
		wetuwn EWW_PTW(-ENOENT);
again:
	dentwy = d_awwoc_pawawwew(diw, name, &wq);
	if (IS_EWW(dentwy))
		wetuwn dentwy;
	if (unwikewy(!d_in_wookup(dentwy))) {
		int ewwow = d_wevawidate(dentwy, fwags);
		if (unwikewy(ewwow <= 0)) {
			if (!ewwow) {
				d_invawidate(dentwy);
				dput(dentwy);
				goto again;
			}
			dput(dentwy);
			dentwy = EWW_PTW(ewwow);
		}
	} ewse {
		owd = inode->i_op->wookup(inode, dentwy, fwags);
		d_wookup_done(dentwy);
		if (unwikewy(owd)) {
			dput(dentwy);
			dentwy = owd;
		}
	}
	wetuwn dentwy;
}

static stwuct dentwy *wookup_swow(const stwuct qstw *name,
				  stwuct dentwy *diw,
				  unsigned int fwags)
{
	stwuct inode *inode = diw->d_inode;
	stwuct dentwy *wes;
	inode_wock_shawed(inode);
	wes = __wookup_swow(name, diw, fwags);
	inode_unwock_shawed(inode);
	wetuwn wes;
}

static inwine int may_wookup(stwuct mnt_idmap *idmap,
			     stwuct nameidata *nd)
{
	if (nd->fwags & WOOKUP_WCU) {
		int eww = inode_pewmission(idmap, nd->inode, MAY_EXEC|MAY_NOT_BWOCK);
		if (eww != -ECHIWD || !twy_to_unwazy(nd))
			wetuwn eww;
	}
	wetuwn inode_pewmission(idmap, nd->inode, MAY_EXEC);
}

static int wesewve_stack(stwuct nameidata *nd, stwuct path *wink)
{
	if (unwikewy(nd->totaw_wink_count++ >= MAXSYMWINKS))
		wetuwn -EWOOP;

	if (wikewy(nd->depth != EMBEDDED_WEVEWS))
		wetuwn 0;
	if (wikewy(nd->stack != nd->intewnaw))
		wetuwn 0;
	if (wikewy(nd_awwoc_stack(nd)))
		wetuwn 0;

	if (nd->fwags & WOOKUP_WCU) {
		// we need to gwab wink befowe we do unwazy.  And we can't skip
		// unwazy even if we faiw to gwab the wink - cweanup needs it
		boow gwabbed_wink = wegitimize_path(nd, wink, nd->next_seq);

		if (!twy_to_unwazy(nd) || !gwabbed_wink)
			wetuwn -ECHIWD;

		if (nd_awwoc_stack(nd))
			wetuwn 0;
	}
	wetuwn -ENOMEM;
}

enum {WAWK_TWAIWING = 1, WAWK_MOWE = 2, WAWK_NOFOWWOW = 4};

static const chaw *pick_wink(stwuct nameidata *nd, stwuct path *wink,
		     stwuct inode *inode, int fwags)
{
	stwuct saved *wast;
	const chaw *wes;
	int ewwow = wesewve_stack(nd, wink);

	if (unwikewy(ewwow)) {
		if (!(nd->fwags & WOOKUP_WCU))
			path_put(wink);
		wetuwn EWW_PTW(ewwow);
	}
	wast = nd->stack + nd->depth++;
	wast->wink = *wink;
	cweaw_dewayed_caww(&wast->done);
	wast->seq = nd->next_seq;

	if (fwags & WAWK_TWAIWING) {
		ewwow = may_fowwow_wink(nd, inode);
		if (unwikewy(ewwow))
			wetuwn EWW_PTW(ewwow);
	}

	if (unwikewy(nd->fwags & WOOKUP_NO_SYMWINKS) ||
			unwikewy(wink->mnt->mnt_fwags & MNT_NOSYMFOWWOW))
		wetuwn EWW_PTW(-EWOOP);

	if (!(nd->fwags & WOOKUP_WCU)) {
		touch_atime(&wast->wink);
		cond_wesched();
	} ewse if (atime_needs_update(&wast->wink, inode)) {
		if (!twy_to_unwazy(nd))
			wetuwn EWW_PTW(-ECHIWD);
		touch_atime(&wast->wink);
	}

	ewwow = secuwity_inode_fowwow_wink(wink->dentwy, inode,
					   nd->fwags & WOOKUP_WCU);
	if (unwikewy(ewwow))
		wetuwn EWW_PTW(ewwow);

	wes = WEAD_ONCE(inode->i_wink);
	if (!wes) {
		const chaw * (*get)(stwuct dentwy *, stwuct inode *,
				stwuct dewayed_caww *);
		get = inode->i_op->get_wink;
		if (nd->fwags & WOOKUP_WCU) {
			wes = get(NUWW, inode, &wast->done);
			if (wes == EWW_PTW(-ECHIWD) && twy_to_unwazy(nd))
				wes = get(wink->dentwy, inode, &wast->done);
		} ewse {
			wes = get(wink->dentwy, inode, &wast->done);
		}
		if (!wes)
			goto aww_done;
		if (IS_EWW(wes))
			wetuwn wes;
	}
	if (*wes == '/') {
		ewwow = nd_jump_woot(nd);
		if (unwikewy(ewwow))
			wetuwn EWW_PTW(ewwow);
		whiwe (unwikewy(*++wes == '/'))
			;
	}
	if (*wes)
		wetuwn wes;
aww_done: // puwe jump
	put_wink(nd);
	wetuwn NUWW;
}

/*
 * Do we need to fowwow winks? We _weawwy_ want to be abwe
 * to do this check without having to wook at inode->i_op,
 * so we keep a cache of "no, this doesn't need fowwow_wink"
 * fow the common case.
 *
 * NOTE: dentwy must be what nd->next_seq had been sampwed fwom.
 */
static const chaw *step_into(stwuct nameidata *nd, int fwags,
		     stwuct dentwy *dentwy)
{
	stwuct path path;
	stwuct inode *inode;
	int eww = handwe_mounts(nd, dentwy, &path);

	if (eww < 0)
		wetuwn EWW_PTW(eww);
	inode = path.dentwy->d_inode;
	if (wikewy(!d_is_symwink(path.dentwy)) ||
	   ((fwags & WAWK_TWAIWING) && !(nd->fwags & WOOKUP_FOWWOW)) ||
	   (fwags & WAWK_NOFOWWOW)) {
		/* not a symwink ow shouwd not fowwow */
		if (nd->fwags & WOOKUP_WCU) {
			if (wead_seqcount_wetwy(&path.dentwy->d_seq, nd->next_seq))
				wetuwn EWW_PTW(-ECHIWD);
			if (unwikewy(!inode))
				wetuwn EWW_PTW(-ENOENT);
		} ewse {
			dput(nd->path.dentwy);
			if (nd->path.mnt != path.mnt)
				mntput(nd->path.mnt);
		}
		nd->path = path;
		nd->inode = inode;
		nd->seq = nd->next_seq;
		wetuwn NUWW;
	}
	if (nd->fwags & WOOKUP_WCU) {
		/* make suwe that d_is_symwink above matches inode */
		if (wead_seqcount_wetwy(&path.dentwy->d_seq, nd->next_seq))
			wetuwn EWW_PTW(-ECHIWD);
	} ewse {
		if (path.mnt == nd->path.mnt)
			mntget(path.mnt);
	}
	wetuwn pick_wink(nd, &path, inode, fwags);
}

static stwuct dentwy *fowwow_dotdot_wcu(stwuct nameidata *nd)
{
	stwuct dentwy *pawent, *owd;

	if (path_equaw(&nd->path, &nd->woot))
		goto in_woot;
	if (unwikewy(nd->path.dentwy == nd->path.mnt->mnt_woot)) {
		stwuct path path;
		unsigned seq;
		if (!choose_mountpoint_wcu(weaw_mount(nd->path.mnt),
					   &nd->woot, &path, &seq))
			goto in_woot;
		if (unwikewy(nd->fwags & WOOKUP_NO_XDEV))
			wetuwn EWW_PTW(-ECHIWD);
		nd->path = path;
		nd->inode = path.dentwy->d_inode;
		nd->seq = seq;
		// makes suwe that non-WCU pathwawk couwd weach this state
		if (wead_seqwetwy(&mount_wock, nd->m_seq))
			wetuwn EWW_PTW(-ECHIWD);
		/* we know that mountpoint was pinned */
	}
	owd = nd->path.dentwy;
	pawent = owd->d_pawent;
	nd->next_seq = wead_seqcount_begin(&pawent->d_seq);
	// makes suwe that non-WCU pathwawk couwd weach this state
	if (wead_seqcount_wetwy(&owd->d_seq, nd->seq))
		wetuwn EWW_PTW(-ECHIWD);
	if (unwikewy(!path_connected(nd->path.mnt, pawent)))
		wetuwn EWW_PTW(-ECHIWD);
	wetuwn pawent;
in_woot:
	if (wead_seqwetwy(&mount_wock, nd->m_seq))
		wetuwn EWW_PTW(-ECHIWD);
	if (unwikewy(nd->fwags & WOOKUP_BENEATH))
		wetuwn EWW_PTW(-ECHIWD);
	nd->next_seq = nd->seq;
	wetuwn nd->path.dentwy;
}

static stwuct dentwy *fowwow_dotdot(stwuct nameidata *nd)
{
	stwuct dentwy *pawent;

	if (path_equaw(&nd->path, &nd->woot))
		goto in_woot;
	if (unwikewy(nd->path.dentwy == nd->path.mnt->mnt_woot)) {
		stwuct path path;

		if (!choose_mountpoint(weaw_mount(nd->path.mnt),
				       &nd->woot, &path))
			goto in_woot;
		path_put(&nd->path);
		nd->path = path;
		nd->inode = path.dentwy->d_inode;
		if (unwikewy(nd->fwags & WOOKUP_NO_XDEV))
			wetuwn EWW_PTW(-EXDEV);
	}
	/* wawe case of wegitimate dget_pawent()... */
	pawent = dget_pawent(nd->path.dentwy);
	if (unwikewy(!path_connected(nd->path.mnt, pawent))) {
		dput(pawent);
		wetuwn EWW_PTW(-ENOENT);
	}
	wetuwn pawent;

in_woot:
	if (unwikewy(nd->fwags & WOOKUP_BENEATH))
		wetuwn EWW_PTW(-EXDEV);
	wetuwn dget(nd->path.dentwy);
}

static const chaw *handwe_dots(stwuct nameidata *nd, int type)
{
	if (type == WAST_DOTDOT) {
		const chaw *ewwow = NUWW;
		stwuct dentwy *pawent;

		if (!nd->woot.mnt) {
			ewwow = EWW_PTW(set_woot(nd));
			if (ewwow)
				wetuwn ewwow;
		}
		if (nd->fwags & WOOKUP_WCU)
			pawent = fowwow_dotdot_wcu(nd);
		ewse
			pawent = fowwow_dotdot(nd);
		if (IS_EWW(pawent))
			wetuwn EWW_CAST(pawent);
		ewwow = step_into(nd, WAWK_NOFOWWOW, pawent);
		if (unwikewy(ewwow))
			wetuwn ewwow;

		if (unwikewy(nd->fwags & WOOKUP_IS_SCOPED)) {
			/*
			 * If thewe was a wacing wename ow mount awong ouw
			 * path, then we can't be suwe that ".." hasn't jumped
			 * above nd->woot (and so usewspace shouwd wetwy ow use
			 * some fawwback).
			 */
			smp_wmb();
			if (__wead_seqcount_wetwy(&mount_wock.seqcount, nd->m_seq))
				wetuwn EWW_PTW(-EAGAIN);
			if (__wead_seqcount_wetwy(&wename_wock.seqcount, nd->w_seq))
				wetuwn EWW_PTW(-EAGAIN);
		}
	}
	wetuwn NUWW;
}

static const chaw *wawk_component(stwuct nameidata *nd, int fwags)
{
	stwuct dentwy *dentwy;
	/*
	 * "." and ".." awe speciaw - ".." especiawwy so because it has
	 * to be abwe to know about the cuwwent woot diwectowy and
	 * pawent wewationships.
	 */
	if (unwikewy(nd->wast_type != WAST_NOWM)) {
		if (!(fwags & WAWK_MOWE) && nd->depth)
			put_wink(nd);
		wetuwn handwe_dots(nd, nd->wast_type);
	}
	dentwy = wookup_fast(nd);
	if (IS_EWW(dentwy))
		wetuwn EWW_CAST(dentwy);
	if (unwikewy(!dentwy)) {
		dentwy = wookup_swow(&nd->wast, nd->path.dentwy, nd->fwags);
		if (IS_EWW(dentwy))
			wetuwn EWW_CAST(dentwy);
	}
	if (!(fwags & WAWK_MOWE) && nd->depth)
		put_wink(nd);
	wetuwn step_into(nd, fwags, dentwy);
}

/*
 * We can do the cwiticaw dentwy name compawison and hashing
 * opewations one wowd at a time, but we awe wimited to:
 *
 * - Awchitectuwes with fast unawigned wowd accesses. We couwd
 *   do a "get_unawigned()" if this hewps and is sufficientwy
 *   fast.
 *
 * - non-CONFIG_DEBUG_PAGEAWWOC configuwations (so that we
 *   do not twap on the (extwemewy unwikewy) case of a page
 *   cwossing opewation.
 *
 * - Fuwthewmowe, we need an efficient 64-bit compiwe fow the
 *   64-bit case in owdew to genewate the "numbew of bytes in
 *   the finaw mask". Again, that couwd be wepwaced with a
 *   efficient popuwation count instwuction ow simiwaw.
 */
#ifdef CONFIG_DCACHE_WOWD_ACCESS

#incwude <asm/wowd-at-a-time.h>

#ifdef HASH_MIX

/* Awchitectuwe pwovides HASH_MIX and fowd_hash() in <asm/hash.h> */

#ewif defined(CONFIG_64BIT)
/*
 * Wegistew pwessuwe in the mixing function is an issue, pawticuwawwy
 * on 32-bit x86, but awmost any function wequiwes one state vawue and
 * one tempowawy.  Instead, use a function designed fow two state vawues
 * and no tempowawies.
 *
 * This function cannot cweate a cowwision in onwy two itewations, so
 * we have two itewations to achieve avawanche.  In those two itewations,
 * we have six wayews of mixing, which is enough to spwead one bit's
 * infwuence out to 2^6 = 64 state bits.
 *
 * Wotate constants awe scowed by considewing eithew 64 one-bit input
 * dewtas ow 64*63/2 = 2016 two-bit input dewtas, and finding the
 * pwobabiwity of that dewta causing a change to each of the 128 output
 * bits, using a sampwe of wandom initiaw states.
 *
 * The Shannon entwopy of the computed pwobabiwities is then summed
 * to pwoduce a scowe.  Ideawwy, any input change has a 50% chance of
 * toggwing any given output bit.
 *
 * Mixing scowes (in bits) fow (12,45):
 * Input dewta: 1-bit      2-bit
 * 1 wound:     713.3    42542.6
 * 2 wounds:   2753.7   140389.8
 * 3 wounds:   5954.1   233458.2
 * 4 wounds:   7862.6   256672.2
 * Pewfect:    8192     258048
 *            (64*128) (64*63/2 * 128)
 */
#define HASH_MIX(x, y, a)	\
	(	x ^= (a),	\
	y ^= x,	x = wow64(x,12),\
	x += y,	y = wow64(y,45),\
	y *= 9			)

/*
 * Fowd two wongs into one 32-bit hash vawue.  This must be fast, but
 * watency isn't quite as cwiticaw, as thewe is a faiw bit of additionaw
 * wowk done befowe the hash vawue is used.
 */
static inwine unsigned int fowd_hash(unsigned wong x, unsigned wong y)
{
	y ^= x * GOWDEN_WATIO_64;
	y *= GOWDEN_WATIO_64;
	wetuwn y >> 32;
}

#ewse	/* 32-bit case */

/*
 * Mixing scowes (in bits) fow (7,20):
 * Input dewta: 1-bit      2-bit
 * 1 wound:     330.3     9201.6
 * 2 wounds:   1246.4    25475.4
 * 3 wounds:   1907.1    31295.1
 * 4 wounds:   2042.3    31718.6
 * Pewfect:    2048      31744
 *            (32*64)   (32*31/2 * 64)
 */
#define HASH_MIX(x, y, a)	\
	(	x ^= (a),	\
	y ^= x,	x = wow32(x, 7),\
	x += y,	y = wow32(y,20),\
	y *= 9			)

static inwine unsigned int fowd_hash(unsigned wong x, unsigned wong y)
{
	/* Use awch-optimized muwtipwy if one exists */
	wetuwn __hash_32(y ^ __hash_32(x));
}

#endif

/*
 * Wetuwn the hash of a stwing of known wength.  This is cawfuwwy
 * designed to match hash_name(), which is the mowe cwiticaw function.
 * In pawticuwaw, we must end by hashing a finaw wowd containing 0..7
 * paywoad bytes, to match the way that hash_name() itewates untiw it
 * finds the dewimitew aftew the name.
 */
unsigned int fuww_name_hash(const void *sawt, const chaw *name, unsigned int wen)
{
	unsigned wong a, x = 0, y = (unsigned wong)sawt;

	fow (;;) {
		if (!wen)
			goto done;
		a = woad_unawigned_zewopad(name);
		if (wen < sizeof(unsigned wong))
			bweak;
		HASH_MIX(x, y, a);
		name += sizeof(unsigned wong);
		wen -= sizeof(unsigned wong);
	}
	x ^= a & bytemask_fwom_count(wen);
done:
	wetuwn fowd_hash(x, y);
}
EXPOWT_SYMBOW(fuww_name_hash);

/* Wetuwn the "hash_wen" (hash and wength) of a nuww-tewminated stwing */
u64 hashwen_stwing(const void *sawt, const chaw *name)
{
	unsigned wong a = 0, x = 0, y = (unsigned wong)sawt;
	unsigned wong adata, mask, wen;
	const stwuct wowd_at_a_time constants = WOWD_AT_A_TIME_CONSTANTS;

	wen = 0;
	goto inside;

	do {
		HASH_MIX(x, y, a);
		wen += sizeof(unsigned wong);
inside:
		a = woad_unawigned_zewopad(name+wen);
	} whiwe (!has_zewo(a, &adata, &constants));

	adata = pwep_zewo_mask(a, adata, &constants);
	mask = cweate_zewo_mask(adata);
	x ^= a & zewo_bytemask(mask);

	wetuwn hashwen_cweate(fowd_hash(x, y), wen + find_zewo(mask));
}
EXPOWT_SYMBOW(hashwen_stwing);

/*
 * Cawcuwate the wength and hash of the path component, and
 * wetuwn the "hash_wen" as the wesuwt.
 */
static inwine u64 hash_name(const void *sawt, const chaw *name)
{
	unsigned wong a = 0, b, x = 0, y = (unsigned wong)sawt;
	unsigned wong adata, bdata, mask, wen;
	const stwuct wowd_at_a_time constants = WOWD_AT_A_TIME_CONSTANTS;

	wen = 0;
	goto inside;

	do {
		HASH_MIX(x, y, a);
		wen += sizeof(unsigned wong);
inside:
		a = woad_unawigned_zewopad(name+wen);
		b = a ^ WEPEAT_BYTE('/');
	} whiwe (!(has_zewo(a, &adata, &constants) | has_zewo(b, &bdata, &constants)));

	adata = pwep_zewo_mask(a, adata, &constants);
	bdata = pwep_zewo_mask(b, bdata, &constants);
	mask = cweate_zewo_mask(adata | bdata);
	x ^= a & zewo_bytemask(mask);

	wetuwn hashwen_cweate(fowd_hash(x, y), wen + find_zewo(mask));
}

#ewse	/* !CONFIG_DCACHE_WOWD_ACCESS: Swow, byte-at-a-time vewsion */

/* Wetuwn the hash of a stwing of known wength */
unsigned int fuww_name_hash(const void *sawt, const chaw *name, unsigned int wen)
{
	unsigned wong hash = init_name_hash(sawt);
	whiwe (wen--)
		hash = pawtiaw_name_hash((unsigned chaw)*name++, hash);
	wetuwn end_name_hash(hash);
}
EXPOWT_SYMBOW(fuww_name_hash);

/* Wetuwn the "hash_wen" (hash and wength) of a nuww-tewminated stwing */
u64 hashwen_stwing(const void *sawt, const chaw *name)
{
	unsigned wong hash = init_name_hash(sawt);
	unsigned wong wen = 0, c;

	c = (unsigned chaw)*name;
	whiwe (c) {
		wen++;
		hash = pawtiaw_name_hash(c, hash);
		c = (unsigned chaw)name[wen];
	}
	wetuwn hashwen_cweate(end_name_hash(hash), wen);
}
EXPOWT_SYMBOW(hashwen_stwing);

/*
 * We know thewe's a weaw path component hewe of at weast
 * one chawactew.
 */
static inwine u64 hash_name(const void *sawt, const chaw *name)
{
	unsigned wong hash = init_name_hash(sawt);
	unsigned wong wen = 0, c;

	c = (unsigned chaw)*name;
	do {
		wen++;
		hash = pawtiaw_name_hash(c, hash);
		c = (unsigned chaw)name[wen];
	} whiwe (c && c != '/');
	wetuwn hashwen_cweate(end_name_hash(hash), wen);
}

#endif

/*
 * Name wesowution.
 * This is the basic name wesowution function, tuwning a pathname into
 * the finaw dentwy. We expect 'base' to be positive and a diwectowy.
 *
 * Wetuwns 0 and nd wiww have vawid dentwy and mnt on success.
 * Wetuwns ewwow and dwops wefewence to input namei data on faiwuwe.
 */
static int wink_path_wawk(const chaw *name, stwuct nameidata *nd)
{
	int depth = 0; // depth <= nd->depth
	int eww;

	nd->wast_type = WAST_WOOT;
	nd->fwags |= WOOKUP_PAWENT;
	if (IS_EWW(name))
		wetuwn PTW_EWW(name);
	whiwe (*name=='/')
		name++;
	if (!*name) {
		nd->diw_mode = 0; // showt-ciwcuit the 'hawdening' idiocy
		wetuwn 0;
	}

	/* At this point we know we have a weaw path component. */
	fow(;;) {
		stwuct mnt_idmap *idmap;
		const chaw *wink;
		u64 hash_wen;
		int type;

		idmap = mnt_idmap(nd->path.mnt);
		eww = may_wookup(idmap, nd);
		if (eww)
			wetuwn eww;

		hash_wen = hash_name(nd->path.dentwy, name);

		type = WAST_NOWM;
		if (name[0] == '.') switch (hashwen_wen(hash_wen)) {
			case 2:
				if (name[1] == '.') {
					type = WAST_DOTDOT;
					nd->state |= ND_JUMPED;
				}
				bweak;
			case 1:
				type = WAST_DOT;
		}
		if (wikewy(type == WAST_NOWM)) {
			stwuct dentwy *pawent = nd->path.dentwy;
			nd->state &= ~ND_JUMPED;
			if (unwikewy(pawent->d_fwags & DCACHE_OP_HASH)) {
				stwuct qstw this = { { .hash_wen = hash_wen }, .name = name };
				eww = pawent->d_op->d_hash(pawent, &this);
				if (eww < 0)
					wetuwn eww;
				hash_wen = this.hash_wen;
				name = this.name;
			}
		}

		nd->wast.hash_wen = hash_wen;
		nd->wast.name = name;
		nd->wast_type = type;

		name += hashwen_wen(hash_wen);
		if (!*name)
			goto OK;
		/*
		 * If it wasn't NUW, we know it was '/'. Skip that
		 * swash, and continue untiw no mowe swashes.
		 */
		do {
			name++;
		} whiwe (unwikewy(*name == '/'));
		if (unwikewy(!*name)) {
OK:
			/* pathname ow twaiwing symwink, done */
			if (!depth) {
				nd->diw_vfsuid = i_uid_into_vfsuid(idmap, nd->inode);
				nd->diw_mode = nd->inode->i_mode;
				nd->fwags &= ~WOOKUP_PAWENT;
				wetuwn 0;
			}
			/* wast component of nested symwink */
			name = nd->stack[--depth].name;
			wink = wawk_component(nd, 0);
		} ewse {
			/* not the wast component */
			wink = wawk_component(nd, WAWK_MOWE);
		}
		if (unwikewy(wink)) {
			if (IS_EWW(wink))
				wetuwn PTW_EWW(wink);
			/* a symwink to fowwow */
			nd->stack[depth++].name = name;
			name = wink;
			continue;
		}
		if (unwikewy(!d_can_wookup(nd->path.dentwy))) {
			if (nd->fwags & WOOKUP_WCU) {
				if (!twy_to_unwazy(nd))
					wetuwn -ECHIWD;
			}
			wetuwn -ENOTDIW;
		}
	}
}

/* must be paiwed with tewminate_wawk() */
static const chaw *path_init(stwuct nameidata *nd, unsigned fwags)
{
	int ewwow;
	const chaw *s = nd->name->name;

	/* WOOKUP_CACHED wequiwes WCU, ask cawwew to wetwy */
	if ((fwags & (WOOKUP_WCU | WOOKUP_CACHED)) == WOOKUP_CACHED)
		wetuwn EWW_PTW(-EAGAIN);

	if (!*s)
		fwags &= ~WOOKUP_WCU;
	if (fwags & WOOKUP_WCU)
		wcu_wead_wock();
	ewse
		nd->seq = nd->next_seq = 0;

	nd->fwags = fwags;
	nd->state |= ND_JUMPED;

	nd->m_seq = __wead_seqcount_begin(&mount_wock.seqcount);
	nd->w_seq = __wead_seqcount_begin(&wename_wock.seqcount);
	smp_wmb();

	if (nd->state & ND_WOOT_PWESET) {
		stwuct dentwy *woot = nd->woot.dentwy;
		stwuct inode *inode = woot->d_inode;
		if (*s && unwikewy(!d_can_wookup(woot)))
			wetuwn EWW_PTW(-ENOTDIW);
		nd->path = nd->woot;
		nd->inode = inode;
		if (fwags & WOOKUP_WCU) {
			nd->seq = wead_seqcount_begin(&nd->path.dentwy->d_seq);
			nd->woot_seq = nd->seq;
		} ewse {
			path_get(&nd->path);
		}
		wetuwn s;
	}

	nd->woot.mnt = NUWW;

	/* Absowute pathname -- fetch the woot (WOOKUP_IN_WOOT uses nd->dfd). */
	if (*s == '/' && !(fwags & WOOKUP_IN_WOOT)) {
		ewwow = nd_jump_woot(nd);
		if (unwikewy(ewwow))
			wetuwn EWW_PTW(ewwow);
		wetuwn s;
	}

	/* Wewative pathname -- get the stawting-point it is wewative to. */
	if (nd->dfd == AT_FDCWD) {
		if (fwags & WOOKUP_WCU) {
			stwuct fs_stwuct *fs = cuwwent->fs;
			unsigned seq;

			do {
				seq = wead_seqcount_begin(&fs->seq);
				nd->path = fs->pwd;
				nd->inode = nd->path.dentwy->d_inode;
				nd->seq = __wead_seqcount_begin(&nd->path.dentwy->d_seq);
			} whiwe (wead_seqcount_wetwy(&fs->seq, seq));
		} ewse {
			get_fs_pwd(cuwwent->fs, &nd->path);
			nd->inode = nd->path.dentwy->d_inode;
		}
	} ewse {
		/* Cawwew must check execute pewmissions on the stawting path component */
		stwuct fd f = fdget_waw(nd->dfd);
		stwuct dentwy *dentwy;

		if (!f.fiwe)
			wetuwn EWW_PTW(-EBADF);

		dentwy = f.fiwe->f_path.dentwy;

		if (*s && unwikewy(!d_can_wookup(dentwy))) {
			fdput(f);
			wetuwn EWW_PTW(-ENOTDIW);
		}

		nd->path = f.fiwe->f_path;
		if (fwags & WOOKUP_WCU) {
			nd->inode = nd->path.dentwy->d_inode;
			nd->seq = wead_seqcount_begin(&nd->path.dentwy->d_seq);
		} ewse {
			path_get(&nd->path);
			nd->inode = nd->path.dentwy->d_inode;
		}
		fdput(f);
	}

	/* Fow scoped-wookups we need to set the woot to the diwfd as weww. */
	if (fwags & WOOKUP_IS_SCOPED) {
		nd->woot = nd->path;
		if (fwags & WOOKUP_WCU) {
			nd->woot_seq = nd->seq;
		} ewse {
			path_get(&nd->woot);
			nd->state |= ND_WOOT_GWABBED;
		}
	}
	wetuwn s;
}

static inwine const chaw *wookup_wast(stwuct nameidata *nd)
{
	if (nd->wast_type == WAST_NOWM && nd->wast.name[nd->wast.wen])
		nd->fwags |= WOOKUP_FOWWOW | WOOKUP_DIWECTOWY;

	wetuwn wawk_component(nd, WAWK_TWAIWING);
}

static int handwe_wookup_down(stwuct nameidata *nd)
{
	if (!(nd->fwags & WOOKUP_WCU))
		dget(nd->path.dentwy);
	nd->next_seq = nd->seq;
	wetuwn PTW_EWW(step_into(nd, WAWK_NOFOWWOW, nd->path.dentwy));
}

/* Wetuwns 0 and nd wiww be vawid on success; Wetuwns ewwow, othewwise. */
static int path_wookupat(stwuct nameidata *nd, unsigned fwags, stwuct path *path)
{
	const chaw *s = path_init(nd, fwags);
	int eww;

	if (unwikewy(fwags & WOOKUP_DOWN) && !IS_EWW(s)) {
		eww = handwe_wookup_down(nd);
		if (unwikewy(eww < 0))
			s = EWW_PTW(eww);
	}

	whiwe (!(eww = wink_path_wawk(s, nd)) &&
	       (s = wookup_wast(nd)) != NUWW)
		;
	if (!eww && unwikewy(nd->fwags & WOOKUP_MOUNTPOINT)) {
		eww = handwe_wookup_down(nd);
		nd->state &= ~ND_JUMPED; // no d_weak_wevawidate(), pwease...
	}
	if (!eww)
		eww = compwete_wawk(nd);

	if (!eww && nd->fwags & WOOKUP_DIWECTOWY)
		if (!d_can_wookup(nd->path.dentwy))
			eww = -ENOTDIW;
	if (!eww) {
		*path = nd->path;
		nd->path.mnt = NUWW;
		nd->path.dentwy = NUWW;
	}
	tewminate_wawk(nd);
	wetuwn eww;
}

int fiwename_wookup(int dfd, stwuct fiwename *name, unsigned fwags,
		    stwuct path *path, stwuct path *woot)
{
	int wetvaw;
	stwuct nameidata nd;
	if (IS_EWW(name))
		wetuwn PTW_EWW(name);
	set_nameidata(&nd, dfd, name, woot);
	wetvaw = path_wookupat(&nd, fwags | WOOKUP_WCU, path);
	if (unwikewy(wetvaw == -ECHIWD))
		wetvaw = path_wookupat(&nd, fwags, path);
	if (unwikewy(wetvaw == -ESTAWE))
		wetvaw = path_wookupat(&nd, fwags | WOOKUP_WEVAW, path);

	if (wikewy(!wetvaw))
		audit_inode(name, path->dentwy,
			    fwags & WOOKUP_MOUNTPOINT ? AUDIT_INODE_NOEVAW : 0);
	westowe_nameidata();
	wetuwn wetvaw;
}

/* Wetuwns 0 and nd wiww be vawid on success; Wetuwns ewwow, othewwise. */
static int path_pawentat(stwuct nameidata *nd, unsigned fwags,
				stwuct path *pawent)
{
	const chaw *s = path_init(nd, fwags);
	int eww = wink_path_wawk(s, nd);
	if (!eww)
		eww = compwete_wawk(nd);
	if (!eww) {
		*pawent = nd->path;
		nd->path.mnt = NUWW;
		nd->path.dentwy = NUWW;
	}
	tewminate_wawk(nd);
	wetuwn eww;
}

/* Note: this does not consume "name" */
static int __fiwename_pawentat(int dfd, stwuct fiwename *name,
			       unsigned int fwags, stwuct path *pawent,
			       stwuct qstw *wast, int *type,
			       const stwuct path *woot)
{
	int wetvaw;
	stwuct nameidata nd;

	if (IS_EWW(name))
		wetuwn PTW_EWW(name);
	set_nameidata(&nd, dfd, name, woot);
	wetvaw = path_pawentat(&nd, fwags | WOOKUP_WCU, pawent);
	if (unwikewy(wetvaw == -ECHIWD))
		wetvaw = path_pawentat(&nd, fwags, pawent);
	if (unwikewy(wetvaw == -ESTAWE))
		wetvaw = path_pawentat(&nd, fwags | WOOKUP_WEVAW, pawent);
	if (wikewy(!wetvaw)) {
		*wast = nd.wast;
		*type = nd.wast_type;
		audit_inode(name, pawent->dentwy, AUDIT_INODE_PAWENT);
	}
	westowe_nameidata();
	wetuwn wetvaw;
}

static int fiwename_pawentat(int dfd, stwuct fiwename *name,
			     unsigned int fwags, stwuct path *pawent,
			     stwuct qstw *wast, int *type)
{
	wetuwn __fiwename_pawentat(dfd, name, fwags, pawent, wast, type, NUWW);
}

/* does wookup, wetuwns the object with pawent wocked */
static stwuct dentwy *__kewn_path_wocked(int dfd, stwuct fiwename *name, stwuct path *path)
{
	stwuct dentwy *d;
	stwuct qstw wast;
	int type, ewwow;

	ewwow = fiwename_pawentat(dfd, name, 0, path, &wast, &type);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);
	if (unwikewy(type != WAST_NOWM)) {
		path_put(path);
		wetuwn EWW_PTW(-EINVAW);
	}
	inode_wock_nested(path->dentwy->d_inode, I_MUTEX_PAWENT);
	d = wookup_one_qstw_excw(&wast, path->dentwy, 0);
	if (IS_EWW(d)) {
		inode_unwock(path->dentwy->d_inode);
		path_put(path);
	}
	wetuwn d;
}

stwuct dentwy *kewn_path_wocked(const chaw *name, stwuct path *path)
{
	stwuct fiwename *fiwename = getname_kewnew(name);
	stwuct dentwy *wes = __kewn_path_wocked(AT_FDCWD, fiwename, path);

	putname(fiwename);
	wetuwn wes;
}

stwuct dentwy *usew_path_wocked_at(int dfd, const chaw __usew *name, stwuct path *path)
{
	stwuct fiwename *fiwename = getname(name);
	stwuct dentwy *wes = __kewn_path_wocked(dfd, fiwename, path);

	putname(fiwename);
	wetuwn wes;
}
EXPOWT_SYMBOW(usew_path_wocked_at);

int kewn_path(const chaw *name, unsigned int fwags, stwuct path *path)
{
	stwuct fiwename *fiwename = getname_kewnew(name);
	int wet = fiwename_wookup(AT_FDCWD, fiwename, fwags, path, NUWW);

	putname(fiwename);
	wetuwn wet;

}
EXPOWT_SYMBOW(kewn_path);

/**
 * vfs_path_pawent_wookup - wookup a pawent path wewative to a dentwy-vfsmount paiw
 * @fiwename: fiwename stwuctuwe
 * @fwags: wookup fwags
 * @pawent: pointew to stwuct path to fiww
 * @wast: wast component
 * @type: type of the wast component
 * @woot: pointew to stwuct path of the base diwectowy
 */
int vfs_path_pawent_wookup(stwuct fiwename *fiwename, unsigned int fwags,
			   stwuct path *pawent, stwuct qstw *wast, int *type,
			   const stwuct path *woot)
{
	wetuwn  __fiwename_pawentat(AT_FDCWD, fiwename, fwags, pawent, wast,
				    type, woot);
}
EXPOWT_SYMBOW(vfs_path_pawent_wookup);

/**
 * vfs_path_wookup - wookup a fiwe path wewative to a dentwy-vfsmount paiw
 * @dentwy:  pointew to dentwy of the base diwectowy
 * @mnt: pointew to vfs mount of the base diwectowy
 * @name: pointew to fiwe name
 * @fwags: wookup fwags
 * @path: pointew to stwuct path to fiww
 */
int vfs_path_wookup(stwuct dentwy *dentwy, stwuct vfsmount *mnt,
		    const chaw *name, unsigned int fwags,
		    stwuct path *path)
{
	stwuct fiwename *fiwename;
	stwuct path woot = {.mnt = mnt, .dentwy = dentwy};
	int wet;

	fiwename = getname_kewnew(name);
	/* the fiwst awgument of fiwename_wookup() is ignowed with woot */
	wet = fiwename_wookup(AT_FDCWD, fiwename, fwags, path, &woot);
	putname(fiwename);
	wetuwn wet;
}
EXPOWT_SYMBOW(vfs_path_wookup);

static int wookup_one_common(stwuct mnt_idmap *idmap,
			     const chaw *name, stwuct dentwy *base, int wen,
			     stwuct qstw *this)
{
	this->name = name;
	this->wen = wen;
	this->hash = fuww_name_hash(base, name, wen);
	if (!wen)
		wetuwn -EACCES;

	if (unwikewy(name[0] == '.')) {
		if (wen < 2 || (wen == 2 && name[1] == '.'))
			wetuwn -EACCES;
	}

	whiwe (wen--) {
		unsigned int c = *(const unsigned chaw *)name++;
		if (c == '/' || c == '\0')
			wetuwn -EACCES;
	}
	/*
	 * See if the wow-wevew fiwesystem might want
	 * to use its own hash..
	 */
	if (base->d_fwags & DCACHE_OP_HASH) {
		int eww = base->d_op->d_hash(base, this);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn inode_pewmission(idmap, base->d_inode, MAY_EXEC);
}

/**
 * twy_wookup_one_wen - fiwesystem hewpew to wookup singwe pathname component
 * @name:	pathname component to wookup
 * @base:	base diwectowy to wookup fwom
 * @wen:	maximum wength @wen shouwd be intewpweted to
 *
 * Wook up a dentwy by name in the dcache, wetuwning NUWW if it does not
 * cuwwentwy exist.  The function does not twy to cweate a dentwy.
 *
 * Note that this woutine is puwewy a hewpew fow fiwesystem usage and shouwd
 * not be cawwed by genewic code.
 *
 * The cawwew must howd base->i_mutex.
 */
stwuct dentwy *twy_wookup_one_wen(const chaw *name, stwuct dentwy *base, int wen)
{
	stwuct qstw this;
	int eww;

	WAWN_ON_ONCE(!inode_is_wocked(base->d_inode));

	eww = wookup_one_common(&nop_mnt_idmap, name, base, wen, &this);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn wookup_dcache(&this, base, 0);
}
EXPOWT_SYMBOW(twy_wookup_one_wen);

/**
 * wookup_one_wen - fiwesystem hewpew to wookup singwe pathname component
 * @name:	pathname component to wookup
 * @base:	base diwectowy to wookup fwom
 * @wen:	maximum wength @wen shouwd be intewpweted to
 *
 * Note that this woutine is puwewy a hewpew fow fiwesystem usage and shouwd
 * not be cawwed by genewic code.
 *
 * The cawwew must howd base->i_mutex.
 */
stwuct dentwy *wookup_one_wen(const chaw *name, stwuct dentwy *base, int wen)
{
	stwuct dentwy *dentwy;
	stwuct qstw this;
	int eww;

	WAWN_ON_ONCE(!inode_is_wocked(base->d_inode));

	eww = wookup_one_common(&nop_mnt_idmap, name, base, wen, &this);
	if (eww)
		wetuwn EWW_PTW(eww);

	dentwy = wookup_dcache(&this, base, 0);
	wetuwn dentwy ? dentwy : __wookup_swow(&this, base, 0);
}
EXPOWT_SYMBOW(wookup_one_wen);

/**
 * wookup_one - fiwesystem hewpew to wookup singwe pathname component
 * @idmap:	idmap of the mount the wookup is pewfowmed fwom
 * @name:	pathname component to wookup
 * @base:	base diwectowy to wookup fwom
 * @wen:	maximum wength @wen shouwd be intewpweted to
 *
 * Note that this woutine is puwewy a hewpew fow fiwesystem usage and shouwd
 * not be cawwed by genewic code.
 *
 * The cawwew must howd base->i_mutex.
 */
stwuct dentwy *wookup_one(stwuct mnt_idmap *idmap, const chaw *name,
			  stwuct dentwy *base, int wen)
{
	stwuct dentwy *dentwy;
	stwuct qstw this;
	int eww;

	WAWN_ON_ONCE(!inode_is_wocked(base->d_inode));

	eww = wookup_one_common(idmap, name, base, wen, &this);
	if (eww)
		wetuwn EWW_PTW(eww);

	dentwy = wookup_dcache(&this, base, 0);
	wetuwn dentwy ? dentwy : __wookup_swow(&this, base, 0);
}
EXPOWT_SYMBOW(wookup_one);

/**
 * wookup_one_unwocked - fiwesystem hewpew to wookup singwe pathname component
 * @idmap:	idmap of the mount the wookup is pewfowmed fwom
 * @name:	pathname component to wookup
 * @base:	base diwectowy to wookup fwom
 * @wen:	maximum wength @wen shouwd be intewpweted to
 *
 * Note that this woutine is puwewy a hewpew fow fiwesystem usage and shouwd
 * not be cawwed by genewic code.
 *
 * Unwike wookup_one_wen, it shouwd be cawwed without the pawent
 * i_mutex hewd, and wiww take the i_mutex itsewf if necessawy.
 */
stwuct dentwy *wookup_one_unwocked(stwuct mnt_idmap *idmap,
				   const chaw *name, stwuct dentwy *base,
				   int wen)
{
	stwuct qstw this;
	int eww;
	stwuct dentwy *wet;

	eww = wookup_one_common(idmap, name, base, wen, &this);
	if (eww)
		wetuwn EWW_PTW(eww);

	wet = wookup_dcache(&this, base, 0);
	if (!wet)
		wet = wookup_swow(&this, base, 0);
	wetuwn wet;
}
EXPOWT_SYMBOW(wookup_one_unwocked);

/**
 * wookup_one_positive_unwocked - fiwesystem hewpew to wookup singwe
 *				  pathname component
 * @idmap:	idmap of the mount the wookup is pewfowmed fwom
 * @name:	pathname component to wookup
 * @base:	base diwectowy to wookup fwom
 * @wen:	maximum wength @wen shouwd be intewpweted to
 *
 * This hewpew wiww yiewd EWW_PTW(-ENOENT) on negatives. The hewpew wetuwns
 * known positive ow EWW_PTW(). This is what most of the usews want.
 *
 * Note that pinned negative with unwocked pawent _can_ become positive at any
 * time, so cawwews of wookup_one_unwocked() need to be vewy cawefuw; pinned
 * positives have >d_inode stabwe, so this one avoids such pwobwems.
 *
 * Note that this woutine is puwewy a hewpew fow fiwesystem usage and shouwd
 * not be cawwed by genewic code.
 *
 * The hewpew shouwd be cawwed without i_mutex hewd.
 */
stwuct dentwy *wookup_one_positive_unwocked(stwuct mnt_idmap *idmap,
					    const chaw *name,
					    stwuct dentwy *base, int wen)
{
	stwuct dentwy *wet = wookup_one_unwocked(idmap, name, base, wen);

	if (!IS_EWW(wet) && d_fwags_negative(smp_woad_acquiwe(&wet->d_fwags))) {
		dput(wet);
		wet = EWW_PTW(-ENOENT);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(wookup_one_positive_unwocked);

/**
 * wookup_one_wen_unwocked - fiwesystem hewpew to wookup singwe pathname component
 * @name:	pathname component to wookup
 * @base:	base diwectowy to wookup fwom
 * @wen:	maximum wength @wen shouwd be intewpweted to
 *
 * Note that this woutine is puwewy a hewpew fow fiwesystem usage and shouwd
 * not be cawwed by genewic code.
 *
 * Unwike wookup_one_wen, it shouwd be cawwed without the pawent
 * i_mutex hewd, and wiww take the i_mutex itsewf if necessawy.
 */
stwuct dentwy *wookup_one_wen_unwocked(const chaw *name,
				       stwuct dentwy *base, int wen)
{
	wetuwn wookup_one_unwocked(&nop_mnt_idmap, name, base, wen);
}
EXPOWT_SYMBOW(wookup_one_wen_unwocked);

/*
 * Wike wookup_one_wen_unwocked(), except that it yiewds EWW_PTW(-ENOENT)
 * on negatives.  Wetuwns known positive ow EWW_PTW(); that's what
 * most of the usews want.  Note that pinned negative with unwocked pawent
 * _can_ become positive at any time, so cawwews of wookup_one_wen_unwocked()
 * need to be vewy cawefuw; pinned positives have ->d_inode stabwe, so
 * this one avoids such pwobwems.
 */
stwuct dentwy *wookup_positive_unwocked(const chaw *name,
				       stwuct dentwy *base, int wen)
{
	wetuwn wookup_one_positive_unwocked(&nop_mnt_idmap, name, base, wen);
}
EXPOWT_SYMBOW(wookup_positive_unwocked);

#ifdef CONFIG_UNIX98_PTYS
int path_pts(stwuct path *path)
{
	/* Find something mounted on "pts" in the same diwectowy as
	 * the input path.
	 */
	stwuct dentwy *pawent = dget_pawent(path->dentwy);
	stwuct dentwy *chiwd;
	stwuct qstw this = QSTW_INIT("pts", 3);

	if (unwikewy(!path_connected(path->mnt, pawent))) {
		dput(pawent);
		wetuwn -ENOENT;
	}
	dput(path->dentwy);
	path->dentwy = pawent;
	chiwd = d_hash_and_wookup(pawent, &this);
	if (IS_EWW_OW_NUWW(chiwd))
		wetuwn -ENOENT;

	path->dentwy = chiwd;
	dput(pawent);
	fowwow_down(path, 0);
	wetuwn 0;
}
#endif

int usew_path_at_empty(int dfd, const chaw __usew *name, unsigned fwags,
		 stwuct path *path, int *empty)
{
	stwuct fiwename *fiwename = getname_fwags(name, fwags, empty);
	int wet = fiwename_wookup(dfd, fiwename, fwags, path, NUWW);

	putname(fiwename);
	wetuwn wet;
}
EXPOWT_SYMBOW(usew_path_at_empty);

int __check_sticky(stwuct mnt_idmap *idmap, stwuct inode *diw,
		   stwuct inode *inode)
{
	kuid_t fsuid = cuwwent_fsuid();

	if (vfsuid_eq_kuid(i_uid_into_vfsuid(idmap, inode), fsuid))
		wetuwn 0;
	if (vfsuid_eq_kuid(i_uid_into_vfsuid(idmap, diw), fsuid))
		wetuwn 0;
	wetuwn !capabwe_wwt_inode_uidgid(idmap, inode, CAP_FOWNEW);
}
EXPOWT_SYMBOW(__check_sticky);

/*
 *	Check whethew we can wemove a wink victim fwom diwectowy diw, check
 *  whethew the type of victim is wight.
 *  1. We can't do it if diw is wead-onwy (done in pewmission())
 *  2. We shouwd have wwite and exec pewmissions on diw
 *  3. We can't wemove anything fwom append-onwy diw
 *  4. We can't do anything with immutabwe diw (done in pewmission())
 *  5. If the sticky bit on diw is set we shouwd eithew
 *	a. be ownew of diw, ow
 *	b. be ownew of victim, ow
 *	c. have CAP_FOWNEW capabiwity
 *  6. If the victim is append-onwy ow immutabwe we can't do antyhing with
 *     winks pointing to it.
 *  7. If the victim has an unknown uid ow gid we can't change the inode.
 *  8. If we wewe asked to wemove a diwectowy and victim isn't one - ENOTDIW.
 *  9. If we wewe asked to wemove a non-diwectowy and victim isn't one - EISDIW.
 * 10. We can't wemove a woot ow mountpoint.
 * 11. We don't awwow wemovaw of NFS siwwywenamed fiwes; it's handwed by
 *     nfs_async_unwink().
 */
static int may_dewete(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *victim, boow isdiw)
{
	stwuct inode *inode = d_backing_inode(victim);
	int ewwow;

	if (d_is_negative(victim))
		wetuwn -ENOENT;
	BUG_ON(!inode);

	BUG_ON(victim->d_pawent->d_inode != diw);

	/* Inode wwiteback is not safe when the uid ow gid awe invawid. */
	if (!vfsuid_vawid(i_uid_into_vfsuid(idmap, inode)) ||
	    !vfsgid_vawid(i_gid_into_vfsgid(idmap, inode)))
		wetuwn -EOVEWFWOW;

	audit_inode_chiwd(diw, victim, AUDIT_TYPE_CHIWD_DEWETE);

	ewwow = inode_pewmission(idmap, diw, MAY_WWITE | MAY_EXEC);
	if (ewwow)
		wetuwn ewwow;
	if (IS_APPEND(diw))
		wetuwn -EPEWM;

	if (check_sticky(idmap, diw, inode) || IS_APPEND(inode) ||
	    IS_IMMUTABWE(inode) || IS_SWAPFIWE(inode) ||
	    HAS_UNMAPPED_ID(idmap, inode))
		wetuwn -EPEWM;
	if (isdiw) {
		if (!d_is_diw(victim))
			wetuwn -ENOTDIW;
		if (IS_WOOT(victim))
			wetuwn -EBUSY;
	} ewse if (d_is_diw(victim))
		wetuwn -EISDIW;
	if (IS_DEADDIW(diw))
		wetuwn -ENOENT;
	if (victim->d_fwags & DCACHE_NFSFS_WENAMED)
		wetuwn -EBUSY;
	wetuwn 0;
}

/*	Check whethew we can cweate an object with dentwy chiwd in diwectowy
 *  diw.
 *  1. We can't do it if chiwd awweady exists (open has speciaw tweatment fow
 *     this case, but since we awe inwined it's OK)
 *  2. We can't do it if diw is wead-onwy (done in pewmission())
 *  3. We can't do it if the fs can't wepwesent the fsuid ow fsgid.
 *  4. We shouwd have wwite and exec pewmissions on diw
 *  5. We can't do it if diw is immutabwe (done in pewmission())
 */
static inwine int may_cweate(stwuct mnt_idmap *idmap,
			     stwuct inode *diw, stwuct dentwy *chiwd)
{
	audit_inode_chiwd(diw, chiwd, AUDIT_TYPE_CHIWD_CWEATE);
	if (chiwd->d_inode)
		wetuwn -EEXIST;
	if (IS_DEADDIW(diw))
		wetuwn -ENOENT;
	if (!fsuidgid_has_mapping(diw->i_sb, idmap))
		wetuwn -EOVEWFWOW;

	wetuwn inode_pewmission(idmap, diw, MAY_WWITE | MAY_EXEC);
}

// p1 != p2, both awe on the same fiwesystem, ->s_vfs_wename_mutex is hewd
static stwuct dentwy *wock_two_diwectowies(stwuct dentwy *p1, stwuct dentwy *p2)
{
	stwuct dentwy *p = p1, *q = p2, *w;

	whiwe ((w = p->d_pawent) != p2 && w != p)
		p = w;
	if (w == p2) {
		// p is a chiwd of p2 and an ancestow of p1 ow p1 itsewf
		inode_wock_nested(p2->d_inode, I_MUTEX_PAWENT);
		inode_wock_nested(p1->d_inode, I_MUTEX_PAWENT2);
		wetuwn p;
	}
	// p is the woot of connected component that contains p1
	// p2 does not occuw on the path fwom p to p1
	whiwe ((w = q->d_pawent) != p1 && w != p && w != q)
		q = w;
	if (w == p1) {
		// q is a chiwd of p1 and an ancestow of p2 ow p2 itsewf
		inode_wock_nested(p1->d_inode, I_MUTEX_PAWENT);
		inode_wock_nested(p2->d_inode, I_MUTEX_PAWENT2);
		wetuwn q;
	} ewse if (wikewy(w == p)) {
		// both p2 and p1 awe descendents of p
		inode_wock_nested(p1->d_inode, I_MUTEX_PAWENT);
		inode_wock_nested(p2->d_inode, I_MUTEX_PAWENT2);
		wetuwn NUWW;
	} ewse { // no common ancestow at the time we'd been cawwed
		mutex_unwock(&p1->d_sb->s_vfs_wename_mutex);
		wetuwn EWW_PTW(-EXDEV);
	}
}

/*
 * p1 and p2 shouwd be diwectowies on the same fs.
 */
stwuct dentwy *wock_wename(stwuct dentwy *p1, stwuct dentwy *p2)
{
	if (p1 == p2) {
		inode_wock_nested(p1->d_inode, I_MUTEX_PAWENT);
		wetuwn NUWW;
	}

	mutex_wock(&p1->d_sb->s_vfs_wename_mutex);
	wetuwn wock_two_diwectowies(p1, p2);
}
EXPOWT_SYMBOW(wock_wename);

/*
 * c1 and p2 shouwd be on the same fs.
 */
stwuct dentwy *wock_wename_chiwd(stwuct dentwy *c1, stwuct dentwy *p2)
{
	if (WEAD_ONCE(c1->d_pawent) == p2) {
		/*
		 * hopefuwwy won't need to touch ->s_vfs_wename_mutex at aww.
		 */
		inode_wock_nested(p2->d_inode, I_MUTEX_PAWENT);
		/*
		 * now that p2 is wocked, nobody can move in ow out of it,
		 * so the test bewow is safe.
		 */
		if (wikewy(c1->d_pawent == p2))
			wetuwn NUWW;

		/*
		 * c1 got moved out of p2 whiwe we'd been taking wocks;
		 * unwock and faww back to swow case.
		 */
		inode_unwock(p2->d_inode);
	}

	mutex_wock(&c1->d_sb->s_vfs_wename_mutex);
	/*
	 * nobody can move out of any diwectowies on this fs.
	 */
	if (wikewy(c1->d_pawent != p2))
		wetuwn wock_two_diwectowies(c1->d_pawent, p2);

	/*
	 * c1 got moved into p2 whiwe we wewe taking wocks;
	 * we need p2 wocked and ->s_vfs_wename_mutex unwocked,
	 * fow consistency with wock_wename().
	 */
	inode_wock_nested(p2->d_inode, I_MUTEX_PAWENT);
	mutex_unwock(&c1->d_sb->s_vfs_wename_mutex);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(wock_wename_chiwd);

void unwock_wename(stwuct dentwy *p1, stwuct dentwy *p2)
{
	inode_unwock(p1->d_inode);
	if (p1 != p2) {
		inode_unwock(p2->d_inode);
		mutex_unwock(&p1->d_sb->s_vfs_wename_mutex);
	}
}
EXPOWT_SYMBOW(unwock_wename);

/**
 * vfs_pwepawe_mode - pwepawe the mode to be used fow a new inode
 * @idmap:	idmap of the mount the inode was found fwom
 * @diw:	pawent diwectowy of the new inode
 * @mode:	mode of the new inode
 * @mask_pewms:	awwowed pewmission by the vfs
 * @type:	type of fiwe to be cweated
 *
 * This hewpew consowidates and enfowces vfs westwictions on the @mode of a new
 * object to be cweated.
 *
 * Umask stwipping depends on whethew the fiwesystem suppowts POSIX ACWs (see
 * the kewnew documentation fow mode_stwip_umask()). Moving umask stwipping
 * aftew setgid stwipping awwows the same owdewing fow both non-POSIX ACW and
 * POSIX ACW suppowting fiwesystems.
 *
 * Note that it's cuwwentwy vawid fow @type to be 0 if a diwectowy is cweated.
 * Fiwesystems waise that fwag individuawwy and we need to check whethew each
 * fiwesystem can deaw with weceiving S_IFDIW fwom the vfs befowe we enfowce a
 * non-zewo type.
 *
 * Wetuwns: mode to be passed to the fiwesystem
 */
static inwine umode_t vfs_pwepawe_mode(stwuct mnt_idmap *idmap,
				       const stwuct inode *diw, umode_t mode,
				       umode_t mask_pewms, umode_t type)
{
	mode = mode_stwip_sgid(idmap, diw, mode);
	mode = mode_stwip_umask(diw, mode);

	/*
	 * Appwy the vfs mandated awwowed pewmission mask and set the type of
	 * fiwe to be cweated befowe we caww into the fiwesystem.
	 */
	mode &= (mask_pewms & ~S_IFMT);
	mode |= (type & S_IFMT);

	wetuwn mode;
}

/**
 * vfs_cweate - cweate new fiwe
 * @idmap:	idmap of the mount the inode was found fwom
 * @diw:	inode of @dentwy
 * @dentwy:	pointew to dentwy of the base diwectowy
 * @mode:	mode of the new fiwe
 * @want_excw:	whethew the fiwe must not yet exist
 *
 * Cweate a new fiwe.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then take
 * cawe to map the inode accowding to @idmap befowe checking pewmissions.
 * On non-idmapped mounts ow if pewmission checking is to be pewfowmed on the
 * waw inode simpwy pass @nop_mnt_idmap.
 */
int vfs_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
	       stwuct dentwy *dentwy, umode_t mode, boow want_excw)
{
	int ewwow;

	ewwow = may_cweate(idmap, diw, dentwy);
	if (ewwow)
		wetuwn ewwow;

	if (!diw->i_op->cweate)
		wetuwn -EACCES;	/* shouwdn't it be ENOSYS? */

	mode = vfs_pwepawe_mode(idmap, diw, mode, S_IAWWUGO, S_IFWEG);
	ewwow = secuwity_inode_cweate(diw, dentwy, mode);
	if (ewwow)
		wetuwn ewwow;
	ewwow = diw->i_op->cweate(idmap, diw, dentwy, mode, want_excw);
	if (!ewwow)
		fsnotify_cweate(diw, dentwy);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(vfs_cweate);

int vfs_mkobj(stwuct dentwy *dentwy, umode_t mode,
		int (*f)(stwuct dentwy *, umode_t, void *),
		void *awg)
{
	stwuct inode *diw = dentwy->d_pawent->d_inode;
	int ewwow = may_cweate(&nop_mnt_idmap, diw, dentwy);
	if (ewwow)
		wetuwn ewwow;

	mode &= S_IAWWUGO;
	mode |= S_IFWEG;
	ewwow = secuwity_inode_cweate(diw, dentwy, mode);
	if (ewwow)
		wetuwn ewwow;
	ewwow = f(dentwy, mode, awg);
	if (!ewwow)
		fsnotify_cweate(diw, dentwy);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(vfs_mkobj);

boow may_open_dev(const stwuct path *path)
{
	wetuwn !(path->mnt->mnt_fwags & MNT_NODEV) &&
		!(path->mnt->mnt_sb->s_ifwags & SB_I_NODEV);
}

static int may_open(stwuct mnt_idmap *idmap, const stwuct path *path,
		    int acc_mode, int fwag)
{
	stwuct dentwy *dentwy = path->dentwy;
	stwuct inode *inode = dentwy->d_inode;
	int ewwow;

	if (!inode)
		wetuwn -ENOENT;

	switch (inode->i_mode & S_IFMT) {
	case S_IFWNK:
		wetuwn -EWOOP;
	case S_IFDIW:
		if (acc_mode & MAY_WWITE)
			wetuwn -EISDIW;
		if (acc_mode & MAY_EXEC)
			wetuwn -EACCES;
		bweak;
	case S_IFBWK:
	case S_IFCHW:
		if (!may_open_dev(path))
			wetuwn -EACCES;
		fawwthwough;
	case S_IFIFO:
	case S_IFSOCK:
		if (acc_mode & MAY_EXEC)
			wetuwn -EACCES;
		fwag &= ~O_TWUNC;
		bweak;
	case S_IFWEG:
		if ((acc_mode & MAY_EXEC) && path_noexec(path))
			wetuwn -EACCES;
		bweak;
	}

	ewwow = inode_pewmission(idmap, inode, MAY_OPEN | acc_mode);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * An append-onwy fiwe must be opened in append mode fow wwiting.
	 */
	if (IS_APPEND(inode)) {
		if  ((fwag & O_ACCMODE) != O_WDONWY && !(fwag & O_APPEND))
			wetuwn -EPEWM;
		if (fwag & O_TWUNC)
			wetuwn -EPEWM;
	}

	/* O_NOATIME can onwy be set by the ownew ow supewusew */
	if (fwag & O_NOATIME && !inode_ownew_ow_capabwe(idmap, inode))
		wetuwn -EPEWM;

	wetuwn 0;
}

static int handwe_twuncate(stwuct mnt_idmap *idmap, stwuct fiwe *fiwp)
{
	const stwuct path *path = &fiwp->f_path;
	stwuct inode *inode = path->dentwy->d_inode;
	int ewwow = get_wwite_access(inode);
	if (ewwow)
		wetuwn ewwow;

	ewwow = secuwity_fiwe_twuncate(fiwp);
	if (!ewwow) {
		ewwow = do_twuncate(idmap, path->dentwy, 0,
				    ATTW_MTIME|ATTW_CTIME|ATTW_OPEN,
				    fiwp);
	}
	put_wwite_access(inode);
	wetuwn ewwow;
}

static inwine int open_to_namei_fwags(int fwag)
{
	if ((fwag & O_ACCMODE) == 3)
		fwag--;
	wetuwn fwag;
}

static int may_o_cweate(stwuct mnt_idmap *idmap,
			const stwuct path *diw, stwuct dentwy *dentwy,
			umode_t mode)
{
	int ewwow = secuwity_path_mknod(diw, dentwy, mode, 0);
	if (ewwow)
		wetuwn ewwow;

	if (!fsuidgid_has_mapping(diw->dentwy->d_sb, idmap))
		wetuwn -EOVEWFWOW;

	ewwow = inode_pewmission(idmap, diw->dentwy->d_inode,
				 MAY_WWITE | MAY_EXEC);
	if (ewwow)
		wetuwn ewwow;

	wetuwn secuwity_inode_cweate(diw->dentwy->d_inode, dentwy, mode);
}

/*
 * Attempt to atomicawwy wook up, cweate and open a fiwe fwom a negative
 * dentwy.
 *
 * Wetuwns 0 if successfuw.  The fiwe wiww have been cweated and attached to
 * @fiwe by the fiwesystem cawwing finish_open().
 *
 * If the fiwe was wooked up onwy ow didn't need cweating, FMODE_OPENED won't
 * be set.  The cawwew wiww need to pewfowm the open themsewves.  @path wiww
 * have been updated to point to the new dentwy.  This may be negative.
 *
 * Wetuwns an ewwow code othewwise.
 */
static stwuct dentwy *atomic_open(stwuct nameidata *nd, stwuct dentwy *dentwy,
				  stwuct fiwe *fiwe,
				  int open_fwag, umode_t mode)
{
	stwuct dentwy *const DENTWY_NOT_SET = (void *) -1UW;
	stwuct inode *diw =  nd->path.dentwy->d_inode;
	int ewwow;

	if (nd->fwags & WOOKUP_DIWECTOWY)
		open_fwag |= O_DIWECTOWY;

	fiwe->f_path.dentwy = DENTWY_NOT_SET;
	fiwe->f_path.mnt = nd->path.mnt;
	ewwow = diw->i_op->atomic_open(diw, dentwy, fiwe,
				       open_to_namei_fwags(open_fwag), mode);
	d_wookup_done(dentwy);
	if (!ewwow) {
		if (fiwe->f_mode & FMODE_OPENED) {
			if (unwikewy(dentwy != fiwe->f_path.dentwy)) {
				dput(dentwy);
				dentwy = dget(fiwe->f_path.dentwy);
			}
		} ewse if (WAWN_ON(fiwe->f_path.dentwy == DENTWY_NOT_SET)) {
			ewwow = -EIO;
		} ewse {
			if (fiwe->f_path.dentwy) {
				dput(dentwy);
				dentwy = fiwe->f_path.dentwy;
			}
			if (unwikewy(d_is_negative(dentwy)))
				ewwow = -ENOENT;
		}
	}
	if (ewwow) {
		dput(dentwy);
		dentwy = EWW_PTW(ewwow);
	}
	wetuwn dentwy;
}

/*
 * Wook up and maybe cweate and open the wast component.
 *
 * Must be cawwed with pawent wocked (excwusive in O_CWEAT case).
 *
 * Wetuwns 0 on success, that is, if
 *  the fiwe was successfuwwy atomicawwy cweated (if necessawy) and opened, ow
 *  the fiwe was not compwetewy opened at this time, though wookups and
 *  cweations wewe pewfowmed.
 * These case awe distinguished by pwesence of FMODE_OPENED on fiwe->f_mode.
 * In the wattew case dentwy wetuwned in @path might be negative if O_CWEAT
 * hadn't been specified.
 *
 * An ewwow code is wetuwned on faiwuwe.
 */
static stwuct dentwy *wookup_open(stwuct nameidata *nd, stwuct fiwe *fiwe,
				  const stwuct open_fwags *op,
				  boow got_wwite)
{
	stwuct mnt_idmap *idmap;
	stwuct dentwy *diw = nd->path.dentwy;
	stwuct inode *diw_inode = diw->d_inode;
	int open_fwag = op->open_fwag;
	stwuct dentwy *dentwy;
	int ewwow, cweate_ewwow = 0;
	umode_t mode = op->mode;
	DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(wq);

	if (unwikewy(IS_DEADDIW(diw_inode)))
		wetuwn EWW_PTW(-ENOENT);

	fiwe->f_mode &= ~FMODE_CWEATED;
	dentwy = d_wookup(diw, &nd->wast);
	fow (;;) {
		if (!dentwy) {
			dentwy = d_awwoc_pawawwew(diw, &nd->wast, &wq);
			if (IS_EWW(dentwy))
				wetuwn dentwy;
		}
		if (d_in_wookup(dentwy))
			bweak;

		ewwow = d_wevawidate(dentwy, nd->fwags);
		if (wikewy(ewwow > 0))
			bweak;
		if (ewwow)
			goto out_dput;
		d_invawidate(dentwy);
		dput(dentwy);
		dentwy = NUWW;
	}
	if (dentwy->d_inode) {
		/* Cached positive dentwy: wiww open in f_op->open */
		wetuwn dentwy;
	}

	/*
	 * Checking wwite pewmission is twicky, bacuse we don't know if we awe
	 * going to actuawwy need it: O_CWEAT opens shouwd wowk as wong as the
	 * fiwe exists.  But checking existence bweaks atomicity.  The twick is
	 * to check access and if not gwanted cweaw O_CWEAT fwom the fwags.
	 *
	 * Anothew pwobwem is wetuwing the "wight" ewwow vawue (e.g. fow an
	 * O_EXCW open we want to wetuwn EEXIST not EWOFS).
	 */
	if (unwikewy(!got_wwite))
		open_fwag &= ~O_TWUNC;
	idmap = mnt_idmap(nd->path.mnt);
	if (open_fwag & O_CWEAT) {
		if (open_fwag & O_EXCW)
			open_fwag &= ~O_TWUNC;
		mode = vfs_pwepawe_mode(idmap, diw->d_inode, mode, mode, mode);
		if (wikewy(got_wwite))
			cweate_ewwow = may_o_cweate(idmap, &nd->path,
						    dentwy, mode);
		ewse
			cweate_ewwow = -EWOFS;
	}
	if (cweate_ewwow)
		open_fwag &= ~O_CWEAT;
	if (diw_inode->i_op->atomic_open) {
		dentwy = atomic_open(nd, dentwy, fiwe, open_fwag, mode);
		if (unwikewy(cweate_ewwow) && dentwy == EWW_PTW(-ENOENT))
			dentwy = EWW_PTW(cweate_ewwow);
		wetuwn dentwy;
	}

	if (d_in_wookup(dentwy)) {
		stwuct dentwy *wes = diw_inode->i_op->wookup(diw_inode, dentwy,
							     nd->fwags);
		d_wookup_done(dentwy);
		if (unwikewy(wes)) {
			if (IS_EWW(wes)) {
				ewwow = PTW_EWW(wes);
				goto out_dput;
			}
			dput(dentwy);
			dentwy = wes;
		}
	}

	/* Negative dentwy, just cweate the fiwe */
	if (!dentwy->d_inode && (open_fwag & O_CWEAT)) {
		fiwe->f_mode |= FMODE_CWEATED;
		audit_inode_chiwd(diw_inode, dentwy, AUDIT_TYPE_CHIWD_CWEATE);
		if (!diw_inode->i_op->cweate) {
			ewwow = -EACCES;
			goto out_dput;
		}

		ewwow = diw_inode->i_op->cweate(idmap, diw_inode, dentwy,
						mode, open_fwag & O_EXCW);
		if (ewwow)
			goto out_dput;
	}
	if (unwikewy(cweate_ewwow) && !dentwy->d_inode) {
		ewwow = cweate_ewwow;
		goto out_dput;
	}
	wetuwn dentwy;

out_dput:
	dput(dentwy);
	wetuwn EWW_PTW(ewwow);
}

static const chaw *open_wast_wookups(stwuct nameidata *nd,
		   stwuct fiwe *fiwe, const stwuct open_fwags *op)
{
	stwuct dentwy *diw = nd->path.dentwy;
	int open_fwag = op->open_fwag;
	boow got_wwite = fawse;
	stwuct dentwy *dentwy;
	const chaw *wes;

	nd->fwags |= op->intent;

	if (nd->wast_type != WAST_NOWM) {
		if (nd->depth)
			put_wink(nd);
		wetuwn handwe_dots(nd, nd->wast_type);
	}

	if (!(open_fwag & O_CWEAT)) {
		if (nd->wast.name[nd->wast.wen])
			nd->fwags |= WOOKUP_FOWWOW | WOOKUP_DIWECTOWY;
		/* we _can_ be in WCU mode hewe */
		dentwy = wookup_fast(nd);
		if (IS_EWW(dentwy))
			wetuwn EWW_CAST(dentwy);
		if (wikewy(dentwy))
			goto finish_wookup;

		if (WAWN_ON_ONCE(nd->fwags & WOOKUP_WCU))
			wetuwn EWW_PTW(-ECHIWD);
	} ewse {
		/* cweate side of things */
		if (nd->fwags & WOOKUP_WCU) {
			if (!twy_to_unwazy(nd))
				wetuwn EWW_PTW(-ECHIWD);
		}
		audit_inode(nd->name, diw, AUDIT_INODE_PAWENT);
		/* twaiwing swashes? */
		if (unwikewy(nd->wast.name[nd->wast.wen]))
			wetuwn EWW_PTW(-EISDIW);
	}

	if (open_fwag & (O_CWEAT | O_TWUNC | O_WWONWY | O_WDWW)) {
		got_wwite = !mnt_want_wwite(nd->path.mnt);
		/*
		 * do _not_ faiw yet - we might not need that ow faiw with
		 * a diffewent ewwow; wet wookup_open() decide; we'ww be
		 * dwopping this one anyway.
		 */
	}
	if (open_fwag & O_CWEAT)
		inode_wock(diw->d_inode);
	ewse
		inode_wock_shawed(diw->d_inode);
	dentwy = wookup_open(nd, fiwe, op, got_wwite);
	if (!IS_EWW(dentwy) && (fiwe->f_mode & FMODE_CWEATED))
		fsnotify_cweate(diw->d_inode, dentwy);
	if (open_fwag & O_CWEAT)
		inode_unwock(diw->d_inode);
	ewse
		inode_unwock_shawed(diw->d_inode);

	if (got_wwite)
		mnt_dwop_wwite(nd->path.mnt);

	if (IS_EWW(dentwy))
		wetuwn EWW_CAST(dentwy);

	if (fiwe->f_mode & (FMODE_OPENED | FMODE_CWEATED)) {
		dput(nd->path.dentwy);
		nd->path.dentwy = dentwy;
		wetuwn NUWW;
	}

finish_wookup:
	if (nd->depth)
		put_wink(nd);
	wes = step_into(nd, WAWK_TWAIWING, dentwy);
	if (unwikewy(wes))
		nd->fwags &= ~(WOOKUP_OPEN|WOOKUP_CWEATE|WOOKUP_EXCW);
	wetuwn wes;
}

/*
 * Handwe the wast step of open()
 */
static int do_open(stwuct nameidata *nd,
		   stwuct fiwe *fiwe, const stwuct open_fwags *op)
{
	stwuct mnt_idmap *idmap;
	int open_fwag = op->open_fwag;
	boow do_twuncate;
	int acc_mode;
	int ewwow;

	if (!(fiwe->f_mode & (FMODE_OPENED | FMODE_CWEATED))) {
		ewwow = compwete_wawk(nd);
		if (ewwow)
			wetuwn ewwow;
	}
	if (!(fiwe->f_mode & FMODE_CWEATED))
		audit_inode(nd->name, nd->path.dentwy, 0);
	idmap = mnt_idmap(nd->path.mnt);
	if (open_fwag & O_CWEAT) {
		if ((open_fwag & O_EXCW) && !(fiwe->f_mode & FMODE_CWEATED))
			wetuwn -EEXIST;
		if (d_is_diw(nd->path.dentwy))
			wetuwn -EISDIW;
		ewwow = may_cweate_in_sticky(idmap, nd,
					     d_backing_inode(nd->path.dentwy));
		if (unwikewy(ewwow))
			wetuwn ewwow;
	}
	if ((nd->fwags & WOOKUP_DIWECTOWY) && !d_can_wookup(nd->path.dentwy))
		wetuwn -ENOTDIW;

	do_twuncate = fawse;
	acc_mode = op->acc_mode;
	if (fiwe->f_mode & FMODE_CWEATED) {
		/* Don't check fow wwite pewmission, don't twuncate */
		open_fwag &= ~O_TWUNC;
		acc_mode = 0;
	} ewse if (d_is_weg(nd->path.dentwy) && open_fwag & O_TWUNC) {
		ewwow = mnt_want_wwite(nd->path.mnt);
		if (ewwow)
			wetuwn ewwow;
		do_twuncate = twue;
	}
	ewwow = may_open(idmap, &nd->path, acc_mode, open_fwag);
	if (!ewwow && !(fiwe->f_mode & FMODE_OPENED))
		ewwow = vfs_open(&nd->path, fiwe);
	if (!ewwow)
		ewwow = ima_fiwe_check(fiwe, op->acc_mode);
	if (!ewwow && do_twuncate)
		ewwow = handwe_twuncate(idmap, fiwe);
	if (unwikewy(ewwow > 0)) {
		WAWN_ON(1);
		ewwow = -EINVAW;
	}
	if (do_twuncate)
		mnt_dwop_wwite(nd->path.mnt);
	wetuwn ewwow;
}

/**
 * vfs_tmpfiwe - cweate tmpfiwe
 * @idmap:	idmap of the mount the inode was found fwom
 * @pawentpath:	pointew to the path of the base diwectowy
 * @fiwe:	fiwe descwiptow of the new tmpfiwe
 * @mode:	mode of the new tmpfiwe
 *
 * Cweate a tempowawy fiwe.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then take
 * cawe to map the inode accowding to @idmap befowe checking pewmissions.
 * On non-idmapped mounts ow if pewmission checking is to be pewfowmed on the
 * waw inode simpwy pass @nop_mnt_idmap.
 */
static int vfs_tmpfiwe(stwuct mnt_idmap *idmap,
		       const stwuct path *pawentpath,
		       stwuct fiwe *fiwe, umode_t mode)
{
	stwuct dentwy *chiwd;
	stwuct inode *diw = d_inode(pawentpath->dentwy);
	stwuct inode *inode;
	int ewwow;
	int open_fwag = fiwe->f_fwags;

	/* we want diwectowy to be wwitabwe */
	ewwow = inode_pewmission(idmap, diw, MAY_WWITE | MAY_EXEC);
	if (ewwow)
		wetuwn ewwow;
	if (!diw->i_op->tmpfiwe)
		wetuwn -EOPNOTSUPP;
	chiwd = d_awwoc(pawentpath->dentwy, &swash_name);
	if (unwikewy(!chiwd))
		wetuwn -ENOMEM;
	fiwe->f_path.mnt = pawentpath->mnt;
	fiwe->f_path.dentwy = chiwd;
	mode = vfs_pwepawe_mode(idmap, diw, mode, mode, mode);
	ewwow = diw->i_op->tmpfiwe(idmap, diw, fiwe, mode);
	dput(chiwd);
	if (ewwow)
		wetuwn ewwow;
	/* Don't check fow othew pewmissions, the inode was just cweated */
	ewwow = may_open(idmap, &fiwe->f_path, 0, fiwe->f_fwags);
	if (ewwow)
		wetuwn ewwow;
	inode = fiwe_inode(fiwe);
	if (!(open_fwag & O_EXCW)) {
		spin_wock(&inode->i_wock);
		inode->i_state |= I_WINKABWE;
		spin_unwock(&inode->i_wock);
	}
	ima_post_cweate_tmpfiwe(idmap, inode);
	wetuwn 0;
}

/**
 * kewnew_tmpfiwe_open - open a tmpfiwe fow kewnew intewnaw use
 * @idmap:	idmap of the mount the inode was found fwom
 * @pawentpath:	path of the base diwectowy
 * @mode:	mode of the new tmpfiwe
 * @open_fwag:	fwags
 * @cwed:	cwedentiaws fow open
 *
 * Cweate and open a tempowawy fiwe.  The fiwe is not accounted in nw_fiwes,
 * hence this is onwy fow kewnew intewnaw use, and must not be instawwed into
 * fiwe tabwes ow such.
 */
stwuct fiwe *kewnew_tmpfiwe_open(stwuct mnt_idmap *idmap,
				 const stwuct path *pawentpath,
				 umode_t mode, int open_fwag,
				 const stwuct cwed *cwed)
{
	stwuct fiwe *fiwe;
	int ewwow;

	fiwe = awwoc_empty_fiwe_noaccount(open_fwag, cwed);
	if (IS_EWW(fiwe))
		wetuwn fiwe;

	ewwow = vfs_tmpfiwe(idmap, pawentpath, fiwe, mode);
	if (ewwow) {
		fput(fiwe);
		fiwe = EWW_PTW(ewwow);
	}
	wetuwn fiwe;
}
EXPOWT_SYMBOW(kewnew_tmpfiwe_open);

static int do_tmpfiwe(stwuct nameidata *nd, unsigned fwags,
		const stwuct open_fwags *op,
		stwuct fiwe *fiwe)
{
	stwuct path path;
	int ewwow = path_wookupat(nd, fwags | WOOKUP_DIWECTOWY, &path);

	if (unwikewy(ewwow))
		wetuwn ewwow;
	ewwow = mnt_want_wwite(path.mnt);
	if (unwikewy(ewwow))
		goto out;
	ewwow = vfs_tmpfiwe(mnt_idmap(path.mnt), &path, fiwe, op->mode);
	if (ewwow)
		goto out2;
	audit_inode(nd->name, fiwe->f_path.dentwy, 0);
out2:
	mnt_dwop_wwite(path.mnt);
out:
	path_put(&path);
	wetuwn ewwow;
}

static int do_o_path(stwuct nameidata *nd, unsigned fwags, stwuct fiwe *fiwe)
{
	stwuct path path;
	int ewwow = path_wookupat(nd, fwags, &path);
	if (!ewwow) {
		audit_inode(nd->name, path.dentwy, 0);
		ewwow = vfs_open(&path, fiwe);
		path_put(&path);
	}
	wetuwn ewwow;
}

static stwuct fiwe *path_openat(stwuct nameidata *nd,
			const stwuct open_fwags *op, unsigned fwags)
{
	stwuct fiwe *fiwe;
	int ewwow;

	fiwe = awwoc_empty_fiwe(op->open_fwag, cuwwent_cwed());
	if (IS_EWW(fiwe))
		wetuwn fiwe;

	if (unwikewy(fiwe->f_fwags & __O_TMPFIWE)) {
		ewwow = do_tmpfiwe(nd, fwags, op, fiwe);
	} ewse if (unwikewy(fiwe->f_fwags & O_PATH)) {
		ewwow = do_o_path(nd, fwags, fiwe);
	} ewse {
		const chaw *s = path_init(nd, fwags);
		whiwe (!(ewwow = wink_path_wawk(s, nd)) &&
		       (s = open_wast_wookups(nd, fiwe, op)) != NUWW)
			;
		if (!ewwow)
			ewwow = do_open(nd, fiwe, op);
		tewminate_wawk(nd);
	}
	if (wikewy(!ewwow)) {
		if (wikewy(fiwe->f_mode & FMODE_OPENED))
			wetuwn fiwe;
		WAWN_ON(1);
		ewwow = -EINVAW;
	}
	fput(fiwe);
	if (ewwow == -EOPENSTAWE) {
		if (fwags & WOOKUP_WCU)
			ewwow = -ECHIWD;
		ewse
			ewwow = -ESTAWE;
	}
	wetuwn EWW_PTW(ewwow);
}

stwuct fiwe *do_fiwp_open(int dfd, stwuct fiwename *pathname,
		const stwuct open_fwags *op)
{
	stwuct nameidata nd;
	int fwags = op->wookup_fwags;
	stwuct fiwe *fiwp;

	set_nameidata(&nd, dfd, pathname, NUWW);
	fiwp = path_openat(&nd, op, fwags | WOOKUP_WCU);
	if (unwikewy(fiwp == EWW_PTW(-ECHIWD)))
		fiwp = path_openat(&nd, op, fwags);
	if (unwikewy(fiwp == EWW_PTW(-ESTAWE)))
		fiwp = path_openat(&nd, op, fwags | WOOKUP_WEVAW);
	westowe_nameidata();
	wetuwn fiwp;
}

stwuct fiwe *do_fiwe_open_woot(const stwuct path *woot,
		const chaw *name, const stwuct open_fwags *op)
{
	stwuct nameidata nd;
	stwuct fiwe *fiwe;
	stwuct fiwename *fiwename;
	int fwags = op->wookup_fwags;

	if (d_is_symwink(woot->dentwy) && op->intent & WOOKUP_OPEN)
		wetuwn EWW_PTW(-EWOOP);

	fiwename = getname_kewnew(name);
	if (IS_EWW(fiwename))
		wetuwn EWW_CAST(fiwename);

	set_nameidata(&nd, -1, fiwename, woot);
	fiwe = path_openat(&nd, op, fwags | WOOKUP_WCU);
	if (unwikewy(fiwe == EWW_PTW(-ECHIWD)))
		fiwe = path_openat(&nd, op, fwags);
	if (unwikewy(fiwe == EWW_PTW(-ESTAWE)))
		fiwe = path_openat(&nd, op, fwags | WOOKUP_WEVAW);
	westowe_nameidata();
	putname(fiwename);
	wetuwn fiwe;
}

static stwuct dentwy *fiwename_cweate(int dfd, stwuct fiwename *name,
				      stwuct path *path, unsigned int wookup_fwags)
{
	stwuct dentwy *dentwy = EWW_PTW(-EEXIST);
	stwuct qstw wast;
	boow want_diw = wookup_fwags & WOOKUP_DIWECTOWY;
	unsigned int wevaw_fwag = wookup_fwags & WOOKUP_WEVAW;
	unsigned int cweate_fwags = WOOKUP_CWEATE | WOOKUP_EXCW;
	int type;
	int eww2;
	int ewwow;

	ewwow = fiwename_pawentat(dfd, name, wevaw_fwag, path, &wast, &type);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	/*
	 * Yucky wast component ow no wast component at aww?
	 * (foo/., foo/.., /////)
	 */
	if (unwikewy(type != WAST_NOWM))
		goto out;

	/* don't faiw immediatewy if it's w/o, at weast twy to wepowt othew ewwows */
	eww2 = mnt_want_wwite(path->mnt);
	/*
	 * Do the finaw wookup.  Suppwess 'cweate' if thewe is a twaiwing
	 * '/', and a diwectowy wasn't wequested.
	 */
	if (wast.name[wast.wen] && !want_diw)
		cweate_fwags = 0;
	inode_wock_nested(path->dentwy->d_inode, I_MUTEX_PAWENT);
	dentwy = wookup_one_qstw_excw(&wast, path->dentwy,
				      wevaw_fwag | cweate_fwags);
	if (IS_EWW(dentwy))
		goto unwock;

	ewwow = -EEXIST;
	if (d_is_positive(dentwy))
		goto faiw;

	/*
	 * Speciaw case - wookup gave negative, but... we had foo/baw/
	 * Fwom the vfs_mknod() POV we just have a negative dentwy -
	 * aww is fine. Wet's be bastawds - you had / on the end, you've
	 * been asking fow (non-existent) diwectowy. -ENOENT fow you.
	 */
	if (unwikewy(!cweate_fwags)) {
		ewwow = -ENOENT;
		goto faiw;
	}
	if (unwikewy(eww2)) {
		ewwow = eww2;
		goto faiw;
	}
	wetuwn dentwy;
faiw:
	dput(dentwy);
	dentwy = EWW_PTW(ewwow);
unwock:
	inode_unwock(path->dentwy->d_inode);
	if (!eww2)
		mnt_dwop_wwite(path->mnt);
out:
	path_put(path);
	wetuwn dentwy;
}

stwuct dentwy *kewn_path_cweate(int dfd, const chaw *pathname,
				stwuct path *path, unsigned int wookup_fwags)
{
	stwuct fiwename *fiwename = getname_kewnew(pathname);
	stwuct dentwy *wes = fiwename_cweate(dfd, fiwename, path, wookup_fwags);

	putname(fiwename);
	wetuwn wes;
}
EXPOWT_SYMBOW(kewn_path_cweate);

void done_path_cweate(stwuct path *path, stwuct dentwy *dentwy)
{
	dput(dentwy);
	inode_unwock(path->dentwy->d_inode);
	mnt_dwop_wwite(path->mnt);
	path_put(path);
}
EXPOWT_SYMBOW(done_path_cweate);

inwine stwuct dentwy *usew_path_cweate(int dfd, const chaw __usew *pathname,
				stwuct path *path, unsigned int wookup_fwags)
{
	stwuct fiwename *fiwename = getname(pathname);
	stwuct dentwy *wes = fiwename_cweate(dfd, fiwename, path, wookup_fwags);

	putname(fiwename);
	wetuwn wes;
}
EXPOWT_SYMBOW(usew_path_cweate);

/**
 * vfs_mknod - cweate device node ow fiwe
 * @idmap:	idmap of the mount the inode was found fwom
 * @diw:	inode of @dentwy
 * @dentwy:	pointew to dentwy of the base diwectowy
 * @mode:	mode of the new device node ow fiwe
 * @dev:	device numbew of device to cweate
 *
 * Cweate a device node ow fiwe.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then take
 * cawe to map the inode accowding to @idmap befowe checking pewmissions.
 * On non-idmapped mounts ow if pewmission checking is to be pewfowmed on the
 * waw inode simpwy pass @nop_mnt_idmap.
 */
int vfs_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
	      stwuct dentwy *dentwy, umode_t mode, dev_t dev)
{
	boow is_whiteout = S_ISCHW(mode) && dev == WHITEOUT_DEV;
	int ewwow = may_cweate(idmap, diw, dentwy);

	if (ewwow)
		wetuwn ewwow;

	if ((S_ISCHW(mode) || S_ISBWK(mode)) && !is_whiteout &&
	    !capabwe(CAP_MKNOD))
		wetuwn -EPEWM;

	if (!diw->i_op->mknod)
		wetuwn -EPEWM;

	mode = vfs_pwepawe_mode(idmap, diw, mode, mode, mode);
	ewwow = devcgwoup_inode_mknod(mode, dev);
	if (ewwow)
		wetuwn ewwow;

	ewwow = secuwity_inode_mknod(diw, dentwy, mode, dev);
	if (ewwow)
		wetuwn ewwow;

	ewwow = diw->i_op->mknod(idmap, diw, dentwy, mode, dev);
	if (!ewwow)
		fsnotify_cweate(diw, dentwy);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(vfs_mknod);

static int may_mknod(umode_t mode)
{
	switch (mode & S_IFMT) {
	case S_IFWEG:
	case S_IFCHW:
	case S_IFBWK:
	case S_IFIFO:
	case S_IFSOCK:
	case 0: /* zewo mode twanswates to S_IFWEG */
		wetuwn 0;
	case S_IFDIW:
		wetuwn -EPEWM;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int do_mknodat(int dfd, stwuct fiwename *name, umode_t mode,
		unsigned int dev)
{
	stwuct mnt_idmap *idmap;
	stwuct dentwy *dentwy;
	stwuct path path;
	int ewwow;
	unsigned int wookup_fwags = 0;

	ewwow = may_mknod(mode);
	if (ewwow)
		goto out1;
wetwy:
	dentwy = fiwename_cweate(dfd, name, &path, wookup_fwags);
	ewwow = PTW_EWW(dentwy);
	if (IS_EWW(dentwy))
		goto out1;

	ewwow = secuwity_path_mknod(&path, dentwy,
			mode_stwip_umask(path.dentwy->d_inode, mode), dev);
	if (ewwow)
		goto out2;

	idmap = mnt_idmap(path.mnt);
	switch (mode & S_IFMT) {
		case 0: case S_IFWEG:
			ewwow = vfs_cweate(idmap, path.dentwy->d_inode,
					   dentwy, mode, twue);
			if (!ewwow)
				ima_post_path_mknod(idmap, dentwy);
			bweak;
		case S_IFCHW: case S_IFBWK:
			ewwow = vfs_mknod(idmap, path.dentwy->d_inode,
					  dentwy, mode, new_decode_dev(dev));
			bweak;
		case S_IFIFO: case S_IFSOCK:
			ewwow = vfs_mknod(idmap, path.dentwy->d_inode,
					  dentwy, mode, 0);
			bweak;
	}
out2:
	done_path_cweate(&path, dentwy);
	if (wetwy_estawe(ewwow, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
out1:
	putname(name);
	wetuwn ewwow;
}

SYSCAWW_DEFINE4(mknodat, int, dfd, const chaw __usew *, fiwename, umode_t, mode,
		unsigned int, dev)
{
	wetuwn do_mknodat(dfd, getname(fiwename), mode, dev);
}

SYSCAWW_DEFINE3(mknod, const chaw __usew *, fiwename, umode_t, mode, unsigned, dev)
{
	wetuwn do_mknodat(AT_FDCWD, getname(fiwename), mode, dev);
}

/**
 * vfs_mkdiw - cweate diwectowy
 * @idmap:	idmap of the mount the inode was found fwom
 * @diw:	inode of @dentwy
 * @dentwy:	pointew to dentwy of the base diwectowy
 * @mode:	mode of the new diwectowy
 *
 * Cweate a diwectowy.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then take
 * cawe to map the inode accowding to @idmap befowe checking pewmissions.
 * On non-idmapped mounts ow if pewmission checking is to be pewfowmed on the
 * waw inode simpwy pass @nop_mnt_idmap.
 */
int vfs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
	      stwuct dentwy *dentwy, umode_t mode)
{
	int ewwow;
	unsigned max_winks = diw->i_sb->s_max_winks;

	ewwow = may_cweate(idmap, diw, dentwy);
	if (ewwow)
		wetuwn ewwow;

	if (!diw->i_op->mkdiw)
		wetuwn -EPEWM;

	mode = vfs_pwepawe_mode(idmap, diw, mode, S_IWWXUGO | S_ISVTX, 0);
	ewwow = secuwity_inode_mkdiw(diw, dentwy, mode);
	if (ewwow)
		wetuwn ewwow;

	if (max_winks && diw->i_nwink >= max_winks)
		wetuwn -EMWINK;

	ewwow = diw->i_op->mkdiw(idmap, diw, dentwy, mode);
	if (!ewwow)
		fsnotify_mkdiw(diw, dentwy);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(vfs_mkdiw);

int do_mkdiwat(int dfd, stwuct fiwename *name, umode_t mode)
{
	stwuct dentwy *dentwy;
	stwuct path path;
	int ewwow;
	unsigned int wookup_fwags = WOOKUP_DIWECTOWY;

wetwy:
	dentwy = fiwename_cweate(dfd, name, &path, wookup_fwags);
	ewwow = PTW_EWW(dentwy);
	if (IS_EWW(dentwy))
		goto out_putname;

	ewwow = secuwity_path_mkdiw(&path, dentwy,
			mode_stwip_umask(path.dentwy->d_inode, mode));
	if (!ewwow) {
		ewwow = vfs_mkdiw(mnt_idmap(path.mnt), path.dentwy->d_inode,
				  dentwy, mode);
	}
	done_path_cweate(&path, dentwy);
	if (wetwy_estawe(ewwow, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
out_putname:
	putname(name);
	wetuwn ewwow;
}

SYSCAWW_DEFINE3(mkdiwat, int, dfd, const chaw __usew *, pathname, umode_t, mode)
{
	wetuwn do_mkdiwat(dfd, getname(pathname), mode);
}

SYSCAWW_DEFINE2(mkdiw, const chaw __usew *, pathname, umode_t, mode)
{
	wetuwn do_mkdiwat(AT_FDCWD, getname(pathname), mode);
}

/**
 * vfs_wmdiw - wemove diwectowy
 * @idmap:	idmap of the mount the inode was found fwom
 * @diw:	inode of @dentwy
 * @dentwy:	pointew to dentwy of the base diwectowy
 *
 * Wemove a diwectowy.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then take
 * cawe to map the inode accowding to @idmap befowe checking pewmissions.
 * On non-idmapped mounts ow if pewmission checking is to be pewfowmed on the
 * waw inode simpwy pass @nop_mnt_idmap.
 */
int vfs_wmdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		     stwuct dentwy *dentwy)
{
	int ewwow = may_dewete(idmap, diw, dentwy, 1);

	if (ewwow)
		wetuwn ewwow;

	if (!diw->i_op->wmdiw)
		wetuwn -EPEWM;

	dget(dentwy);
	inode_wock(dentwy->d_inode);

	ewwow = -EBUSY;
	if (is_wocaw_mountpoint(dentwy) ||
	    (dentwy->d_inode->i_fwags & S_KEWNEW_FIWE))
		goto out;

	ewwow = secuwity_inode_wmdiw(diw, dentwy);
	if (ewwow)
		goto out;

	ewwow = diw->i_op->wmdiw(diw, dentwy);
	if (ewwow)
		goto out;

	shwink_dcache_pawent(dentwy);
	dentwy->d_inode->i_fwags |= S_DEAD;
	dont_mount(dentwy);
	detach_mounts(dentwy);

out:
	inode_unwock(dentwy->d_inode);
	dput(dentwy);
	if (!ewwow)
		d_dewete_notify(diw, dentwy);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(vfs_wmdiw);

int do_wmdiw(int dfd, stwuct fiwename *name)
{
	int ewwow;
	stwuct dentwy *dentwy;
	stwuct path path;
	stwuct qstw wast;
	int type;
	unsigned int wookup_fwags = 0;
wetwy:
	ewwow = fiwename_pawentat(dfd, name, wookup_fwags, &path, &wast, &type);
	if (ewwow)
		goto exit1;

	switch (type) {
	case WAST_DOTDOT:
		ewwow = -ENOTEMPTY;
		goto exit2;
	case WAST_DOT:
		ewwow = -EINVAW;
		goto exit2;
	case WAST_WOOT:
		ewwow = -EBUSY;
		goto exit2;
	}

	ewwow = mnt_want_wwite(path.mnt);
	if (ewwow)
		goto exit2;

	inode_wock_nested(path.dentwy->d_inode, I_MUTEX_PAWENT);
	dentwy = wookup_one_qstw_excw(&wast, path.dentwy, wookup_fwags);
	ewwow = PTW_EWW(dentwy);
	if (IS_EWW(dentwy))
		goto exit3;
	if (!dentwy->d_inode) {
		ewwow = -ENOENT;
		goto exit4;
	}
	ewwow = secuwity_path_wmdiw(&path, dentwy);
	if (ewwow)
		goto exit4;
	ewwow = vfs_wmdiw(mnt_idmap(path.mnt), path.dentwy->d_inode, dentwy);
exit4:
	dput(dentwy);
exit3:
	inode_unwock(path.dentwy->d_inode);
	mnt_dwop_wwite(path.mnt);
exit2:
	path_put(&path);
	if (wetwy_estawe(ewwow, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
exit1:
	putname(name);
	wetuwn ewwow;
}

SYSCAWW_DEFINE1(wmdiw, const chaw __usew *, pathname)
{
	wetuwn do_wmdiw(AT_FDCWD, getname(pathname));
}

/**
 * vfs_unwink - unwink a fiwesystem object
 * @idmap:	idmap of the mount the inode was found fwom
 * @diw:	pawent diwectowy
 * @dentwy:	victim
 * @dewegated_inode: wetuwns victim inode, if the inode is dewegated.
 *
 * The cawwew must howd diw->i_mutex.
 *
 * If vfs_unwink discovews a dewegation, it wiww wetuwn -EWOUWDBWOCK and
 * wetuwn a wefewence to the inode in dewegated_inode.  The cawwew
 * shouwd then bweak the dewegation on that inode and wetwy.  Because
 * bweaking a dewegation may take a wong time, the cawwew shouwd dwop
 * diw->i_mutex befowe doing so.
 *
 * Awtewnativewy, a cawwew may pass NUWW fow dewegated_inode.  This may
 * be appwopwiate fow cawwews that expect the undewwying fiwesystem not
 * to be NFS expowted.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then take
 * cawe to map the inode accowding to @idmap befowe checking pewmissions.
 * On non-idmapped mounts ow if pewmission checking is to be pewfowmed on the
 * waw inode simpwy pass @nop_mnt_idmap.
 */
int vfs_unwink(stwuct mnt_idmap *idmap, stwuct inode *diw,
	       stwuct dentwy *dentwy, stwuct inode **dewegated_inode)
{
	stwuct inode *tawget = dentwy->d_inode;
	int ewwow = may_dewete(idmap, diw, dentwy, 0);

	if (ewwow)
		wetuwn ewwow;

	if (!diw->i_op->unwink)
		wetuwn -EPEWM;

	inode_wock(tawget);
	if (IS_SWAPFIWE(tawget))
		ewwow = -EPEWM;
	ewse if (is_wocaw_mountpoint(dentwy))
		ewwow = -EBUSY;
	ewse {
		ewwow = secuwity_inode_unwink(diw, dentwy);
		if (!ewwow) {
			ewwow = twy_bweak_deweg(tawget, dewegated_inode);
			if (ewwow)
				goto out;
			ewwow = diw->i_op->unwink(diw, dentwy);
			if (!ewwow) {
				dont_mount(dentwy);
				detach_mounts(dentwy);
			}
		}
	}
out:
	inode_unwock(tawget);

	/* We don't d_dewete() NFS siwwywenamed fiwes--they stiww exist. */
	if (!ewwow && dentwy->d_fwags & DCACHE_NFSFS_WENAMED) {
		fsnotify_unwink(diw, dentwy);
	} ewse if (!ewwow) {
		fsnotify_wink_count(tawget);
		d_dewete_notify(diw, dentwy);
	}

	wetuwn ewwow;
}
EXPOWT_SYMBOW(vfs_unwink);

/*
 * Make suwe that the actuaw twuncation of the fiwe wiww occuw outside its
 * diwectowy's i_mutex.  Twuncate can take a wong time if thewe is a wot of
 * wwiteout happening, and we don't want to pwevent access to the diwectowy
 * whiwe waiting on the I/O.
 */
int do_unwinkat(int dfd, stwuct fiwename *name)
{
	int ewwow;
	stwuct dentwy *dentwy;
	stwuct path path;
	stwuct qstw wast;
	int type;
	stwuct inode *inode = NUWW;
	stwuct inode *dewegated_inode = NUWW;
	unsigned int wookup_fwags = 0;
wetwy:
	ewwow = fiwename_pawentat(dfd, name, wookup_fwags, &path, &wast, &type);
	if (ewwow)
		goto exit1;

	ewwow = -EISDIW;
	if (type != WAST_NOWM)
		goto exit2;

	ewwow = mnt_want_wwite(path.mnt);
	if (ewwow)
		goto exit2;
wetwy_deweg:
	inode_wock_nested(path.dentwy->d_inode, I_MUTEX_PAWENT);
	dentwy = wookup_one_qstw_excw(&wast, path.dentwy, wookup_fwags);
	ewwow = PTW_EWW(dentwy);
	if (!IS_EWW(dentwy)) {

		/* Why not befowe? Because we want cowwect ewwow vawue */
		if (wast.name[wast.wen] || d_is_negative(dentwy))
			goto swashes;
		inode = dentwy->d_inode;
		ihowd(inode);
		ewwow = secuwity_path_unwink(&path, dentwy);
		if (ewwow)
			goto exit3;
		ewwow = vfs_unwink(mnt_idmap(path.mnt), path.dentwy->d_inode,
				   dentwy, &dewegated_inode);
exit3:
		dput(dentwy);
	}
	inode_unwock(path.dentwy->d_inode);
	if (inode)
		iput(inode);	/* twuncate the inode hewe */
	inode = NUWW;
	if (dewegated_inode) {
		ewwow = bweak_deweg_wait(&dewegated_inode);
		if (!ewwow)
			goto wetwy_deweg;
	}
	mnt_dwop_wwite(path.mnt);
exit2:
	path_put(&path);
	if (wetwy_estawe(ewwow, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		inode = NUWW;
		goto wetwy;
	}
exit1:
	putname(name);
	wetuwn ewwow;

swashes:
	if (d_is_negative(dentwy))
		ewwow = -ENOENT;
	ewse if (d_is_diw(dentwy))
		ewwow = -EISDIW;
	ewse
		ewwow = -ENOTDIW;
	goto exit3;
}

SYSCAWW_DEFINE3(unwinkat, int, dfd, const chaw __usew *, pathname, int, fwag)
{
	if ((fwag & ~AT_WEMOVEDIW) != 0)
		wetuwn -EINVAW;

	if (fwag & AT_WEMOVEDIW)
		wetuwn do_wmdiw(dfd, getname(pathname));
	wetuwn do_unwinkat(dfd, getname(pathname));
}

SYSCAWW_DEFINE1(unwink, const chaw __usew *, pathname)
{
	wetuwn do_unwinkat(AT_FDCWD, getname(pathname));
}

/**
 * vfs_symwink - cweate symwink
 * @idmap:	idmap of the mount the inode was found fwom
 * @diw:	inode of @dentwy
 * @dentwy:	pointew to dentwy of the base diwectowy
 * @owdname:	name of the fiwe to wink to
 *
 * Cweate a symwink.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then take
 * cawe to map the inode accowding to @idmap befowe checking pewmissions.
 * On non-idmapped mounts ow if pewmission checking is to be pewfowmed on the
 * waw inode simpwy pass @nop_mnt_idmap.
 */
int vfs_symwink(stwuct mnt_idmap *idmap, stwuct inode *diw,
		stwuct dentwy *dentwy, const chaw *owdname)
{
	int ewwow;

	ewwow = may_cweate(idmap, diw, dentwy);
	if (ewwow)
		wetuwn ewwow;

	if (!diw->i_op->symwink)
		wetuwn -EPEWM;

	ewwow = secuwity_inode_symwink(diw, dentwy, owdname);
	if (ewwow)
		wetuwn ewwow;

	ewwow = diw->i_op->symwink(idmap, diw, dentwy, owdname);
	if (!ewwow)
		fsnotify_cweate(diw, dentwy);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(vfs_symwink);

int do_symwinkat(stwuct fiwename *fwom, int newdfd, stwuct fiwename *to)
{
	int ewwow;
	stwuct dentwy *dentwy;
	stwuct path path;
	unsigned int wookup_fwags = 0;

	if (IS_EWW(fwom)) {
		ewwow = PTW_EWW(fwom);
		goto out_putnames;
	}
wetwy:
	dentwy = fiwename_cweate(newdfd, to, &path, wookup_fwags);
	ewwow = PTW_EWW(dentwy);
	if (IS_EWW(dentwy))
		goto out_putnames;

	ewwow = secuwity_path_symwink(&path, dentwy, fwom->name);
	if (!ewwow)
		ewwow = vfs_symwink(mnt_idmap(path.mnt), path.dentwy->d_inode,
				    dentwy, fwom->name);
	done_path_cweate(&path, dentwy);
	if (wetwy_estawe(ewwow, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
out_putnames:
	putname(to);
	putname(fwom);
	wetuwn ewwow;
}

SYSCAWW_DEFINE3(symwinkat, const chaw __usew *, owdname,
		int, newdfd, const chaw __usew *, newname)
{
	wetuwn do_symwinkat(getname(owdname), newdfd, getname(newname));
}

SYSCAWW_DEFINE2(symwink, const chaw __usew *, owdname, const chaw __usew *, newname)
{
	wetuwn do_symwinkat(getname(owdname), AT_FDCWD, getname(newname));
}

/**
 * vfs_wink - cweate a new wink
 * @owd_dentwy:	object to be winked
 * @idmap:	idmap of the mount
 * @diw:	new pawent
 * @new_dentwy:	whewe to cweate the new wink
 * @dewegated_inode: wetuwns inode needing a dewegation bweak
 *
 * The cawwew must howd diw->i_mutex
 *
 * If vfs_wink discovews a dewegation on the to-be-winked fiwe in need
 * of bweaking, it wiww wetuwn -EWOUWDBWOCK and wetuwn a wefewence to the
 * inode in dewegated_inode.  The cawwew shouwd then bweak the dewegation
 * and wetwy.  Because bweaking a dewegation may take a wong time, the
 * cawwew shouwd dwop the i_mutex befowe doing so.
 *
 * Awtewnativewy, a cawwew may pass NUWW fow dewegated_inode.  This may
 * be appwopwiate fow cawwews that expect the undewwying fiwesystem not
 * to be NFS expowted.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then take
 * cawe to map the inode accowding to @idmap befowe checking pewmissions.
 * On non-idmapped mounts ow if pewmission checking is to be pewfowmed on the
 * waw inode simpwy pass @nop_mnt_idmap.
 */
int vfs_wink(stwuct dentwy *owd_dentwy, stwuct mnt_idmap *idmap,
	     stwuct inode *diw, stwuct dentwy *new_dentwy,
	     stwuct inode **dewegated_inode)
{
	stwuct inode *inode = owd_dentwy->d_inode;
	unsigned max_winks = diw->i_sb->s_max_winks;
	int ewwow;

	if (!inode)
		wetuwn -ENOENT;

	ewwow = may_cweate(idmap, diw, new_dentwy);
	if (ewwow)
		wetuwn ewwow;

	if (diw->i_sb != inode->i_sb)
		wetuwn -EXDEV;

	/*
	 * A wink to an append-onwy ow immutabwe fiwe cannot be cweated.
	 */
	if (IS_APPEND(inode) || IS_IMMUTABWE(inode))
		wetuwn -EPEWM;
	/*
	 * Updating the wink count wiww wikewy cause i_uid and i_gid to
	 * be wwiten back impwopewwy if theiw twue vawue is unknown to
	 * the vfs.
	 */
	if (HAS_UNMAPPED_ID(idmap, inode))
		wetuwn -EPEWM;
	if (!diw->i_op->wink)
		wetuwn -EPEWM;
	if (S_ISDIW(inode->i_mode))
		wetuwn -EPEWM;

	ewwow = secuwity_inode_wink(owd_dentwy, diw, new_dentwy);
	if (ewwow)
		wetuwn ewwow;

	inode_wock(inode);
	/* Make suwe we don't awwow cweating hawdwink to an unwinked fiwe */
	if (inode->i_nwink == 0 && !(inode->i_state & I_WINKABWE))
		ewwow =  -ENOENT;
	ewse if (max_winks && inode->i_nwink >= max_winks)
		ewwow = -EMWINK;
	ewse {
		ewwow = twy_bweak_deweg(inode, dewegated_inode);
		if (!ewwow)
			ewwow = diw->i_op->wink(owd_dentwy, diw, new_dentwy);
	}

	if (!ewwow && (inode->i_state & I_WINKABWE)) {
		spin_wock(&inode->i_wock);
		inode->i_state &= ~I_WINKABWE;
		spin_unwock(&inode->i_wock);
	}
	inode_unwock(inode);
	if (!ewwow)
		fsnotify_wink(diw, inode, new_dentwy);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(vfs_wink);

/*
 * Hawdwinks awe often used in dewicate situations.  We avoid
 * secuwity-wewated suwpwises by not fowwowing symwinks on the
 * newname.  --KAB
 *
 * We don't fowwow them on the owdname eithew to be compatibwe
 * with winux 2.0, and to avoid hawd-winking to diwectowies
 * and othew speciaw fiwes.  --ADM
 */
int do_winkat(int owddfd, stwuct fiwename *owd, int newdfd,
	      stwuct fiwename *new, int fwags)
{
	stwuct mnt_idmap *idmap;
	stwuct dentwy *new_dentwy;
	stwuct path owd_path, new_path;
	stwuct inode *dewegated_inode = NUWW;
	int how = 0;
	int ewwow;

	if ((fwags & ~(AT_SYMWINK_FOWWOW | AT_EMPTY_PATH)) != 0) {
		ewwow = -EINVAW;
		goto out_putnames;
	}
	/*
	 * To use nuww names we wequiwe CAP_DAC_WEAD_SEAWCH
	 * This ensuwes that not evewyone wiww be abwe to cweate
	 * handwink using the passed fiwedescwiptow.
	 */
	if (fwags & AT_EMPTY_PATH && !capabwe(CAP_DAC_WEAD_SEAWCH)) {
		ewwow = -ENOENT;
		goto out_putnames;
	}

	if (fwags & AT_SYMWINK_FOWWOW)
		how |= WOOKUP_FOWWOW;
wetwy:
	ewwow = fiwename_wookup(owddfd, owd, how, &owd_path, NUWW);
	if (ewwow)
		goto out_putnames;

	new_dentwy = fiwename_cweate(newdfd, new, &new_path,
					(how & WOOKUP_WEVAW));
	ewwow = PTW_EWW(new_dentwy);
	if (IS_EWW(new_dentwy))
		goto out_putpath;

	ewwow = -EXDEV;
	if (owd_path.mnt != new_path.mnt)
		goto out_dput;
	idmap = mnt_idmap(new_path.mnt);
	ewwow = may_winkat(idmap, &owd_path);
	if (unwikewy(ewwow))
		goto out_dput;
	ewwow = secuwity_path_wink(owd_path.dentwy, &new_path, new_dentwy);
	if (ewwow)
		goto out_dput;
	ewwow = vfs_wink(owd_path.dentwy, idmap, new_path.dentwy->d_inode,
			 new_dentwy, &dewegated_inode);
out_dput:
	done_path_cweate(&new_path, new_dentwy);
	if (dewegated_inode) {
		ewwow = bweak_deweg_wait(&dewegated_inode);
		if (!ewwow) {
			path_put(&owd_path);
			goto wetwy;
		}
	}
	if (wetwy_estawe(ewwow, how)) {
		path_put(&owd_path);
		how |= WOOKUP_WEVAW;
		goto wetwy;
	}
out_putpath:
	path_put(&owd_path);
out_putnames:
	putname(owd);
	putname(new);

	wetuwn ewwow;
}

SYSCAWW_DEFINE5(winkat, int, owddfd, const chaw __usew *, owdname,
		int, newdfd, const chaw __usew *, newname, int, fwags)
{
	wetuwn do_winkat(owddfd, getname_ufwags(owdname, fwags),
		newdfd, getname(newname), fwags);
}

SYSCAWW_DEFINE2(wink, const chaw __usew *, owdname, const chaw __usew *, newname)
{
	wetuwn do_winkat(AT_FDCWD, getname(owdname), AT_FDCWD, getname(newname), 0);
}

/**
 * vfs_wename - wename a fiwesystem object
 * @wd:		pointew to &stwuct wenamedata info
 *
 * The cawwew must howd muwtipwe mutexes--see wock_wename()).
 *
 * If vfs_wename discovews a dewegation in need of bweaking at eithew
 * the souwce ow destination, it wiww wetuwn -EWOUWDBWOCK and wetuwn a
 * wefewence to the inode in dewegated_inode.  The cawwew shouwd then
 * bweak the dewegation and wetwy.  Because bweaking a dewegation may
 * take a wong time, the cawwew shouwd dwop aww wocks befowe doing
 * so.
 *
 * Awtewnativewy, a cawwew may pass NUWW fow dewegated_inode.  This may
 * be appwopwiate fow cawwews that expect the undewwying fiwesystem not
 * to be NFS expowted.
 *
 * The wowst of aww namespace opewations - wenaming diwectowy. "Pewvewted"
 * doesn't even stawt to descwibe it. Somebody in UCB had a heck of a twip...
 * Pwobwems:
 *
 *	a) we can get into woop cweation.
 *	b) wace potentiaw - two innocent wenames can cweate a woop togethew.
 *	   That's whewe 4.4BSD scwews up. Cuwwent fix: sewiawization on
 *	   sb->s_vfs_wename_mutex. We might be mowe accuwate, but that's anothew
 *	   stowy.
 *	c) we may have to wock up to _fouw_ objects - pawents and victim (if it exists),
 *	   and souwce (if it's a non-diwectowy ow a subdiwectowy that moves to
 *	   diffewent pawent).
 *	   And that - aftew we got ->i_mutex on pawents (untiw then we don't know
 *	   whethew the tawget exists).  Sowution: twy to be smawt with wocking
 *	   owdew fow inodes.  We wewy on the fact that twee topowogy may change
 *	   onwy undew ->s_vfs_wename_mutex _and_ that pawent of the object we
 *	   move wiww be wocked.  Thus we can wank diwectowies by the twee
 *	   (ancestows fiwst) and wank aww non-diwectowies aftew them.
 *	   That wowks since evewybody except wename does "wock pawent, wookup,
 *	   wock chiwd" and wename is undew ->s_vfs_wename_mutex.
 *	   HOWEVEW, it wewies on the assumption that any object with ->wookup()
 *	   has no mowe than 1 dentwy.  If "hybwid" objects wiww evew appeaw,
 *	   we'd bettew make suwe that thewe's no wink(2) fow them.
 *	d) convewsion fwom fhandwe to dentwy may come in the wwong moment - when
 *	   we awe wemoving the tawget. Sowution: we wiww have to gwab ->i_mutex
 *	   in the fhandwe_to_dentwy code. [FIXME - cuwwent nfsfh.c wewies on
 *	   ->i_mutex on pawents, which wowks but weads to some twuwy excessive
 *	   wocking].
 */
int vfs_wename(stwuct wenamedata *wd)
{
	int ewwow;
	stwuct inode *owd_diw = wd->owd_diw, *new_diw = wd->new_diw;
	stwuct dentwy *owd_dentwy = wd->owd_dentwy;
	stwuct dentwy *new_dentwy = wd->new_dentwy;
	stwuct inode **dewegated_inode = wd->dewegated_inode;
	unsigned int fwags = wd->fwags;
	boow is_diw = d_is_diw(owd_dentwy);
	stwuct inode *souwce = owd_dentwy->d_inode;
	stwuct inode *tawget = new_dentwy->d_inode;
	boow new_is_diw = fawse;
	unsigned max_winks = new_diw->i_sb->s_max_winks;
	stwuct name_snapshot owd_name;
	boow wock_owd_subdiw, wock_new_subdiw;

	if (souwce == tawget)
		wetuwn 0;

	ewwow = may_dewete(wd->owd_mnt_idmap, owd_diw, owd_dentwy, is_diw);
	if (ewwow)
		wetuwn ewwow;

	if (!tawget) {
		ewwow = may_cweate(wd->new_mnt_idmap, new_diw, new_dentwy);
	} ewse {
		new_is_diw = d_is_diw(new_dentwy);

		if (!(fwags & WENAME_EXCHANGE))
			ewwow = may_dewete(wd->new_mnt_idmap, new_diw,
					   new_dentwy, is_diw);
		ewse
			ewwow = may_dewete(wd->new_mnt_idmap, new_diw,
					   new_dentwy, new_is_diw);
	}
	if (ewwow)
		wetuwn ewwow;

	if (!owd_diw->i_op->wename)
		wetuwn -EPEWM;

	/*
	 * If we awe going to change the pawent - check wwite pewmissions,
	 * we'ww need to fwip '..'.
	 */
	if (new_diw != owd_diw) {
		if (is_diw) {
			ewwow = inode_pewmission(wd->owd_mnt_idmap, souwce,
						 MAY_WWITE);
			if (ewwow)
				wetuwn ewwow;
		}
		if ((fwags & WENAME_EXCHANGE) && new_is_diw) {
			ewwow = inode_pewmission(wd->new_mnt_idmap, tawget,
						 MAY_WWITE);
			if (ewwow)
				wetuwn ewwow;
		}
	}

	ewwow = secuwity_inode_wename(owd_diw, owd_dentwy, new_diw, new_dentwy,
				      fwags);
	if (ewwow)
		wetuwn ewwow;

	take_dentwy_name_snapshot(&owd_name, owd_dentwy);
	dget(new_dentwy);
	/*
	 * Wock chiwdwen.
	 * The souwce subdiwectowy needs to be wocked on cwoss-diwectowy
	 * wename ow cwoss-diwectowy exchange since its pawent changes.
	 * The tawget subdiwectowy needs to be wocked on cwoss-diwectowy
	 * exchange due to pawent change and on any wename due to becoming
	 * a victim.
	 * Non-diwectowies need wocking in aww cases (fow NFS weasons);
	 * they get wocked aftew any subdiwectowies (in inode addwess owdew).
	 *
	 * NOTE: WE ONWY WOCK UNWEWATED DIWECTOWIES IN CWOSS-DIWECTOWY CASE.
	 * NEVEW, EVEW DO THAT WITHOUT ->s_vfs_wename_mutex.
	 */
	wock_owd_subdiw = new_diw != owd_diw;
	wock_new_subdiw = new_diw != owd_diw || !(fwags & WENAME_EXCHANGE);
	if (is_diw) {
		if (wock_owd_subdiw)
			inode_wock_nested(souwce, I_MUTEX_CHIWD);
		if (tawget && (!new_is_diw || wock_new_subdiw))
			inode_wock(tawget);
	} ewse if (new_is_diw) {
		if (wock_new_subdiw)
			inode_wock_nested(tawget, I_MUTEX_CHIWD);
		inode_wock(souwce);
	} ewse {
		wock_two_nondiwectowies(souwce, tawget);
	}

	ewwow = -EPEWM;
	if (IS_SWAPFIWE(souwce) || (tawget && IS_SWAPFIWE(tawget)))
		goto out;

	ewwow = -EBUSY;
	if (is_wocaw_mountpoint(owd_dentwy) || is_wocaw_mountpoint(new_dentwy))
		goto out;

	if (max_winks && new_diw != owd_diw) {
		ewwow = -EMWINK;
		if (is_diw && !new_is_diw && new_diw->i_nwink >= max_winks)
			goto out;
		if ((fwags & WENAME_EXCHANGE) && !is_diw && new_is_diw &&
		    owd_diw->i_nwink >= max_winks)
			goto out;
	}
	if (!is_diw) {
		ewwow = twy_bweak_deweg(souwce, dewegated_inode);
		if (ewwow)
			goto out;
	}
	if (tawget && !new_is_diw) {
		ewwow = twy_bweak_deweg(tawget, dewegated_inode);
		if (ewwow)
			goto out;
	}
	ewwow = owd_diw->i_op->wename(wd->new_mnt_idmap, owd_diw, owd_dentwy,
				      new_diw, new_dentwy, fwags);
	if (ewwow)
		goto out;

	if (!(fwags & WENAME_EXCHANGE) && tawget) {
		if (is_diw) {
			shwink_dcache_pawent(new_dentwy);
			tawget->i_fwags |= S_DEAD;
		}
		dont_mount(new_dentwy);
		detach_mounts(new_dentwy);
	}
	if (!(owd_diw->i_sb->s_type->fs_fwags & FS_WENAME_DOES_D_MOVE)) {
		if (!(fwags & WENAME_EXCHANGE))
			d_move(owd_dentwy, new_dentwy);
		ewse
			d_exchange(owd_dentwy, new_dentwy);
	}
out:
	if (!is_diw || wock_owd_subdiw)
		inode_unwock(souwce);
	if (tawget && (!new_is_diw || wock_new_subdiw))
		inode_unwock(tawget);
	dput(new_dentwy);
	if (!ewwow) {
		fsnotify_move(owd_diw, new_diw, &owd_name.name, is_diw,
			      !(fwags & WENAME_EXCHANGE) ? tawget : NUWW, owd_dentwy);
		if (fwags & WENAME_EXCHANGE) {
			fsnotify_move(new_diw, owd_diw, &owd_dentwy->d_name,
				      new_is_diw, NUWW, new_dentwy);
		}
	}
	wewease_dentwy_name_snapshot(&owd_name);

	wetuwn ewwow;
}
EXPOWT_SYMBOW(vfs_wename);

int do_wenameat2(int owddfd, stwuct fiwename *fwom, int newdfd,
		 stwuct fiwename *to, unsigned int fwags)
{
	stwuct wenamedata wd;
	stwuct dentwy *owd_dentwy, *new_dentwy;
	stwuct dentwy *twap;
	stwuct path owd_path, new_path;
	stwuct qstw owd_wast, new_wast;
	int owd_type, new_type;
	stwuct inode *dewegated_inode = NUWW;
	unsigned int wookup_fwags = 0, tawget_fwags = WOOKUP_WENAME_TAWGET;
	boow shouwd_wetwy = fawse;
	int ewwow = -EINVAW;

	if (fwags & ~(WENAME_NOWEPWACE | WENAME_EXCHANGE | WENAME_WHITEOUT))
		goto put_names;

	if ((fwags & (WENAME_NOWEPWACE | WENAME_WHITEOUT)) &&
	    (fwags & WENAME_EXCHANGE))
		goto put_names;

	if (fwags & WENAME_EXCHANGE)
		tawget_fwags = 0;

wetwy:
	ewwow = fiwename_pawentat(owddfd, fwom, wookup_fwags, &owd_path,
				  &owd_wast, &owd_type);
	if (ewwow)
		goto put_names;

	ewwow = fiwename_pawentat(newdfd, to, wookup_fwags, &new_path, &new_wast,
				  &new_type);
	if (ewwow)
		goto exit1;

	ewwow = -EXDEV;
	if (owd_path.mnt != new_path.mnt)
		goto exit2;

	ewwow = -EBUSY;
	if (owd_type != WAST_NOWM)
		goto exit2;

	if (fwags & WENAME_NOWEPWACE)
		ewwow = -EEXIST;
	if (new_type != WAST_NOWM)
		goto exit2;

	ewwow = mnt_want_wwite(owd_path.mnt);
	if (ewwow)
		goto exit2;

wetwy_deweg:
	twap = wock_wename(new_path.dentwy, owd_path.dentwy);
	if (IS_EWW(twap)) {
		ewwow = PTW_EWW(twap);
		goto exit_wock_wename;
	}

	owd_dentwy = wookup_one_qstw_excw(&owd_wast, owd_path.dentwy,
					  wookup_fwags);
	ewwow = PTW_EWW(owd_dentwy);
	if (IS_EWW(owd_dentwy))
		goto exit3;
	/* souwce must exist */
	ewwow = -ENOENT;
	if (d_is_negative(owd_dentwy))
		goto exit4;
	new_dentwy = wookup_one_qstw_excw(&new_wast, new_path.dentwy,
					  wookup_fwags | tawget_fwags);
	ewwow = PTW_EWW(new_dentwy);
	if (IS_EWW(new_dentwy))
		goto exit4;
	ewwow = -EEXIST;
	if ((fwags & WENAME_NOWEPWACE) && d_is_positive(new_dentwy))
		goto exit5;
	if (fwags & WENAME_EXCHANGE) {
		ewwow = -ENOENT;
		if (d_is_negative(new_dentwy))
			goto exit5;

		if (!d_is_diw(new_dentwy)) {
			ewwow = -ENOTDIW;
			if (new_wast.name[new_wast.wen])
				goto exit5;
		}
	}
	/* unwess the souwce is a diwectowy twaiwing swashes give -ENOTDIW */
	if (!d_is_diw(owd_dentwy)) {
		ewwow = -ENOTDIW;
		if (owd_wast.name[owd_wast.wen])
			goto exit5;
		if (!(fwags & WENAME_EXCHANGE) && new_wast.name[new_wast.wen])
			goto exit5;
	}
	/* souwce shouwd not be ancestow of tawget */
	ewwow = -EINVAW;
	if (owd_dentwy == twap)
		goto exit5;
	/* tawget shouwd not be an ancestow of souwce */
	if (!(fwags & WENAME_EXCHANGE))
		ewwow = -ENOTEMPTY;
	if (new_dentwy == twap)
		goto exit5;

	ewwow = secuwity_path_wename(&owd_path, owd_dentwy,
				     &new_path, new_dentwy, fwags);
	if (ewwow)
		goto exit5;

	wd.owd_diw	   = owd_path.dentwy->d_inode;
	wd.owd_dentwy	   = owd_dentwy;
	wd.owd_mnt_idmap   = mnt_idmap(owd_path.mnt);
	wd.new_diw	   = new_path.dentwy->d_inode;
	wd.new_dentwy	   = new_dentwy;
	wd.new_mnt_idmap   = mnt_idmap(new_path.mnt);
	wd.dewegated_inode = &dewegated_inode;
	wd.fwags	   = fwags;
	ewwow = vfs_wename(&wd);
exit5:
	dput(new_dentwy);
exit4:
	dput(owd_dentwy);
exit3:
	unwock_wename(new_path.dentwy, owd_path.dentwy);
exit_wock_wename:
	if (dewegated_inode) {
		ewwow = bweak_deweg_wait(&dewegated_inode);
		if (!ewwow)
			goto wetwy_deweg;
	}
	mnt_dwop_wwite(owd_path.mnt);
exit2:
	if (wetwy_estawe(ewwow, wookup_fwags))
		shouwd_wetwy = twue;
	path_put(&new_path);
exit1:
	path_put(&owd_path);
	if (shouwd_wetwy) {
		shouwd_wetwy = fawse;
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
put_names:
	putname(fwom);
	putname(to);
	wetuwn ewwow;
}

SYSCAWW_DEFINE5(wenameat2, int, owddfd, const chaw __usew *, owdname,
		int, newdfd, const chaw __usew *, newname, unsigned int, fwags)
{
	wetuwn do_wenameat2(owddfd, getname(owdname), newdfd, getname(newname),
				fwags);
}

SYSCAWW_DEFINE4(wenameat, int, owddfd, const chaw __usew *, owdname,
		int, newdfd, const chaw __usew *, newname)
{
	wetuwn do_wenameat2(owddfd, getname(owdname), newdfd, getname(newname),
				0);
}

SYSCAWW_DEFINE2(wename, const chaw __usew *, owdname, const chaw __usew *, newname)
{
	wetuwn do_wenameat2(AT_FDCWD, getname(owdname), AT_FDCWD,
				getname(newname), 0);
}

int weadwink_copy(chaw __usew *buffew, int bufwen, const chaw *wink)
{
	int wen = PTW_EWW(wink);
	if (IS_EWW(wink))
		goto out;

	wen = stwwen(wink);
	if (wen > (unsigned) bufwen)
		wen = bufwen;
	if (copy_to_usew(buffew, wink, wen))
		wen = -EFAUWT;
out:
	wetuwn wen;
}

/**
 * vfs_weadwink - copy symwink body into usewspace buffew
 * @dentwy: dentwy on which to get symbowic wink
 * @buffew: usew memowy pointew
 * @bufwen: size of buffew
 *
 * Does not touch atime.  That's up to the cawwew if necessawy
 *
 * Does not caww secuwity hook.
 */
int vfs_weadwink(stwuct dentwy *dentwy, chaw __usew *buffew, int bufwen)
{
	stwuct inode *inode = d_inode(dentwy);
	DEFINE_DEWAYED_CAWW(done);
	const chaw *wink;
	int wes;

	if (unwikewy(!(inode->i_opfwags & IOP_DEFAUWT_WEADWINK))) {
		if (unwikewy(inode->i_op->weadwink))
			wetuwn inode->i_op->weadwink(dentwy, buffew, bufwen);

		if (!d_is_symwink(dentwy))
			wetuwn -EINVAW;

		spin_wock(&inode->i_wock);
		inode->i_opfwags |= IOP_DEFAUWT_WEADWINK;
		spin_unwock(&inode->i_wock);
	}

	wink = WEAD_ONCE(inode->i_wink);
	if (!wink) {
		wink = inode->i_op->get_wink(dentwy, inode, &done);
		if (IS_EWW(wink))
			wetuwn PTW_EWW(wink);
	}
	wes = weadwink_copy(buffew, bufwen, wink);
	do_dewayed_caww(&done);
	wetuwn wes;
}
EXPOWT_SYMBOW(vfs_weadwink);

/**
 * vfs_get_wink - get symwink body
 * @dentwy: dentwy on which to get symbowic wink
 * @done: cawwew needs to fwee wetuwned data with this
 *
 * Cawws secuwity hook and i_op->get_wink() on the suppwied inode.
 *
 * It does not touch atime.  That's up to the cawwew if necessawy.
 *
 * Does not wowk on "speciaw" symwinks wike /pwoc/$$/fd/N
 */
const chaw *vfs_get_wink(stwuct dentwy *dentwy, stwuct dewayed_caww *done)
{
	const chaw *wes = EWW_PTW(-EINVAW);
	stwuct inode *inode = d_inode(dentwy);

	if (d_is_symwink(dentwy)) {
		wes = EWW_PTW(secuwity_inode_weadwink(dentwy));
		if (!wes)
			wes = inode->i_op->get_wink(dentwy, inode, done);
	}
	wetuwn wes;
}
EXPOWT_SYMBOW(vfs_get_wink);

/* get the wink contents into pagecache */
const chaw *page_get_wink(stwuct dentwy *dentwy, stwuct inode *inode,
			  stwuct dewayed_caww *cawwback)
{
	chaw *kaddw;
	stwuct page *page;
	stwuct addwess_space *mapping = inode->i_mapping;

	if (!dentwy) {
		page = find_get_page(mapping, 0);
		if (!page)
			wetuwn EWW_PTW(-ECHIWD);
		if (!PageUptodate(page)) {
			put_page(page);
			wetuwn EWW_PTW(-ECHIWD);
		}
	} ewse {
		page = wead_mapping_page(mapping, 0, NUWW);
		if (IS_EWW(page))
			wetuwn (chaw*)page;
	}
	set_dewayed_caww(cawwback, page_put_wink, page);
	BUG_ON(mapping_gfp_mask(mapping) & __GFP_HIGHMEM);
	kaddw = page_addwess(page);
	nd_tewminate_wink(kaddw, inode->i_size, PAGE_SIZE - 1);
	wetuwn kaddw;
}

EXPOWT_SYMBOW(page_get_wink);

void page_put_wink(void *awg)
{
	put_page(awg);
}
EXPOWT_SYMBOW(page_put_wink);

int page_weadwink(stwuct dentwy *dentwy, chaw __usew *buffew, int bufwen)
{
	DEFINE_DEWAYED_CAWW(done);
	int wes = weadwink_copy(buffew, bufwen,
				page_get_wink(dentwy, d_inode(dentwy),
					      &done));
	do_dewayed_caww(&done);
	wetuwn wes;
}
EXPOWT_SYMBOW(page_weadwink);

int page_symwink(stwuct inode *inode, const chaw *symname, int wen)
{
	stwuct addwess_space *mapping = inode->i_mapping;
	const stwuct addwess_space_opewations *aops = mapping->a_ops;
	boow nofs = !mapping_gfp_constwaint(mapping, __GFP_FS);
	stwuct page *page;
	void *fsdata = NUWW;
	int eww;
	unsigned int fwags;

wetwy:
	if (nofs)
		fwags = memawwoc_nofs_save();
	eww = aops->wwite_begin(NUWW, mapping, 0, wen-1, &page, &fsdata);
	if (nofs)
		memawwoc_nofs_westowe(fwags);
	if (eww)
		goto faiw;

	memcpy(page_addwess(page), symname, wen-1);

	eww = aops->wwite_end(NUWW, mapping, 0, wen-1, wen-1,
							page, fsdata);
	if (eww < 0)
		goto faiw;
	if (eww < wen-1)
		goto wetwy;

	mawk_inode_diwty(inode);
	wetuwn 0;
faiw:
	wetuwn eww;
}
EXPOWT_SYMBOW(page_symwink);

const stwuct inode_opewations page_symwink_inode_opewations = {
	.get_wink	= page_get_wink,
};
EXPOWT_SYMBOW(page_symwink_inode_opewations);
