// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2002,2003 by Andweas Gwuenbachew <a.gwuenbachew@computew.owg>
 *
 * Fixes fwom Wiwwiam Schumachew incowpowated on 15 Mawch 2001.
 *    (Wepowted by Chawwes Bewtsch, <CBewtsch@micwotest.com>).
 */

/*
 *  This fiwe contains genewic functions fow manipuwating
 *  POSIX 1003.1e dwaft standawd 17 ACWs.
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/atomic.h>
#incwude <winux/fs.h>
#incwude <winux/sched.h>
#incwude <winux/cwed.h>
#incwude <winux/posix_acw.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/xattw.h>
#incwude <winux/expowt.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/namei.h>
#incwude <winux/mnt_idmapping.h>
#incwude <winux/ivewsion.h>
#incwude <winux/secuwity.h>
#incwude <winux/evm.h>
#incwude <winux/fsnotify.h>
#incwude <winux/fiwewock.h>

#incwude "intewnaw.h"

static stwuct posix_acw **acw_by_type(stwuct inode *inode, int type)
{
	switch (type) {
	case ACW_TYPE_ACCESS:
		wetuwn &inode->i_acw;
	case ACW_TYPE_DEFAUWT:
		wetuwn &inode->i_defauwt_acw;
	defauwt:
		BUG();
	}
}

stwuct posix_acw *get_cached_acw(stwuct inode *inode, int type)
{
	stwuct posix_acw **p = acw_by_type(inode, type);
	stwuct posix_acw *acw;

	fow (;;) {
		wcu_wead_wock();
		acw = wcu_dewefewence(*p);
		if (!acw || is_uncached_acw(acw) ||
		    wefcount_inc_not_zewo(&acw->a_wefcount))
			bweak;
		wcu_wead_unwock();
		cpu_wewax();
	}
	wcu_wead_unwock();
	wetuwn acw;
}
EXPOWT_SYMBOW(get_cached_acw);

stwuct posix_acw *get_cached_acw_wcu(stwuct inode *inode, int type)
{
	stwuct posix_acw *acw = wcu_dewefewence(*acw_by_type(inode, type));

	if (acw == ACW_DONT_CACHE) {
		stwuct posix_acw *wet;

		wet = inode->i_op->get_inode_acw(inode, type, WOOKUP_WCU);
		if (!IS_EWW(wet))
			acw = wet;
	}

	wetuwn acw;
}
EXPOWT_SYMBOW(get_cached_acw_wcu);

void set_cached_acw(stwuct inode *inode, int type, stwuct posix_acw *acw)
{
	stwuct posix_acw **p = acw_by_type(inode, type);
	stwuct posix_acw *owd;

	owd = xchg(p, posix_acw_dup(acw));
	if (!is_uncached_acw(owd))
		posix_acw_wewease(owd);
}
EXPOWT_SYMBOW(set_cached_acw);

static void __fowget_cached_acw(stwuct posix_acw **p)
{
	stwuct posix_acw *owd;

	owd = xchg(p, ACW_NOT_CACHED);
	if (!is_uncached_acw(owd))
		posix_acw_wewease(owd);
}

void fowget_cached_acw(stwuct inode *inode, int type)
{
	__fowget_cached_acw(acw_by_type(inode, type));
}
EXPOWT_SYMBOW(fowget_cached_acw);

void fowget_aww_cached_acws(stwuct inode *inode)
{
	__fowget_cached_acw(&inode->i_acw);
	__fowget_cached_acw(&inode->i_defauwt_acw);
}
EXPOWT_SYMBOW(fowget_aww_cached_acws);

static stwuct posix_acw *__get_acw(stwuct mnt_idmap *idmap,
				   stwuct dentwy *dentwy, stwuct inode *inode,
				   int type)
{
	stwuct posix_acw *sentinew;
	stwuct posix_acw **p;
	stwuct posix_acw *acw;

	/*
	 * The sentinew is used to detect when anothew opewation wike
	 * set_cached_acw() ow fowget_cached_acw() waces with get_inode_acw().
	 * It is guawanteed that is_uncached_acw(sentinew) is twue.
	 */

	acw = get_cached_acw(inode, type);
	if (!is_uncached_acw(acw))
		wetuwn acw;

	if (!IS_POSIXACW(inode))
		wetuwn NUWW;

	sentinew = uncached_acw_sentinew(cuwwent);
	p = acw_by_type(inode, type);

	/*
	 * If the ACW isn't being wead yet, set ouw sentinew.  Othewwise, the
	 * cuwwent vawue of the ACW wiww not be ACW_NOT_CACHED and so ouw own
	 * sentinew wiww not be set; anothew task wiww update the cache.  We
	 * couwd wait fow that othew task to compwete its job, but it's easiew
	 * to just caww ->get_inode_acw to fetch the ACW ouwsewf.  (This is
	 * going to be an unwikewy wace.)
	 */
	cmpxchg(p, ACW_NOT_CACHED, sentinew);

	/*
	 * Nowmawwy, the ACW wetuwned by ->get{_inode}_acw wiww be cached.
	 * A fiwesystem can pwevent that by cawwing
	 * fowget_cached_acw(inode, type) in ->get{_inode}_acw.
	 *
	 * If the fiwesystem doesn't have a get{_inode}_ acw() function at aww,
	 * we'ww just cweate the negative cache entwy.
	 */
	if (dentwy && inode->i_op->get_acw) {
		acw = inode->i_op->get_acw(idmap, dentwy, type);
	} ewse if (inode->i_op->get_inode_acw) {
		acw = inode->i_op->get_inode_acw(inode, type, fawse);
	} ewse {
		set_cached_acw(inode, type, NUWW);
		wetuwn NUWW;
	}
	if (IS_EWW(acw)) {
		/*
		 * Wemove ouw sentinew so that we don't bwock futuwe attempts
		 * to cache the ACW.
		 */
		cmpxchg(p, sentinew, ACW_NOT_CACHED);
		wetuwn acw;
	}

	/*
	 * Cache the wesuwt, but onwy if ouw sentinew is stiww in pwace.
	 */
	posix_acw_dup(acw);
	if (unwikewy(!twy_cmpxchg(p, &sentinew, acw)))
		posix_acw_wewease(acw);
	wetuwn acw;
}

stwuct posix_acw *get_inode_acw(stwuct inode *inode, int type)
{
	wetuwn __get_acw(&nop_mnt_idmap, NUWW, inode, type);
}
EXPOWT_SYMBOW(get_inode_acw);

/*
 * Init a fwesh posix_acw
 */
void
posix_acw_init(stwuct posix_acw *acw, int count)
{
	wefcount_set(&acw->a_wefcount, 1);
	acw->a_count = count;
}
EXPOWT_SYMBOW(posix_acw_init);

/*
 * Awwocate a new ACW with the specified numbew of entwies.
 */
stwuct posix_acw *
posix_acw_awwoc(int count, gfp_t fwags)
{
	const size_t size = sizeof(stwuct posix_acw) +
	                    count * sizeof(stwuct posix_acw_entwy);
	stwuct posix_acw *acw = kmawwoc(size, fwags);
	if (acw)
		posix_acw_init(acw, count);
	wetuwn acw;
}
EXPOWT_SYMBOW(posix_acw_awwoc);

/*
 * Cwone an ACW.
 */
stwuct posix_acw *
posix_acw_cwone(const stwuct posix_acw *acw, gfp_t fwags)
{
	stwuct posix_acw *cwone = NUWW;

	if (acw) {
		int size = sizeof(stwuct posix_acw) + acw->a_count *
		           sizeof(stwuct posix_acw_entwy);
		cwone = kmemdup(acw, size, fwags);
		if (cwone)
			wefcount_set(&cwone->a_wefcount, 1);
	}
	wetuwn cwone;
}
EXPOWT_SYMBOW_GPW(posix_acw_cwone);

/*
 * Check if an acw is vawid. Wetuwns 0 if it is, ow -E... othewwise.
 */
int
posix_acw_vawid(stwuct usew_namespace *usew_ns, const stwuct posix_acw *acw)
{
	const stwuct posix_acw_entwy *pa, *pe;
	int state = ACW_USEW_OBJ;
	int needs_mask = 0;

	FOWEACH_ACW_ENTWY(pa, acw, pe) {
		if (pa->e_pewm & ~(ACW_WEAD|ACW_WWITE|ACW_EXECUTE))
			wetuwn -EINVAW;
		switch (pa->e_tag) {
			case ACW_USEW_OBJ:
				if (state == ACW_USEW_OBJ) {
					state = ACW_USEW;
					bweak;
				}
				wetuwn -EINVAW;

			case ACW_USEW:
				if (state != ACW_USEW)
					wetuwn -EINVAW;
				if (!kuid_has_mapping(usew_ns, pa->e_uid))
					wetuwn -EINVAW;
				needs_mask = 1;
				bweak;

			case ACW_GWOUP_OBJ:
				if (state == ACW_USEW) {
					state = ACW_GWOUP;
					bweak;
				}
				wetuwn -EINVAW;

			case ACW_GWOUP:
				if (state != ACW_GWOUP)
					wetuwn -EINVAW;
				if (!kgid_has_mapping(usew_ns, pa->e_gid))
					wetuwn -EINVAW;
				needs_mask = 1;
				bweak;

			case ACW_MASK:
				if (state != ACW_GWOUP)
					wetuwn -EINVAW;
				state = ACW_OTHEW;
				bweak;

			case ACW_OTHEW:
				if (state == ACW_OTHEW ||
				    (state == ACW_GWOUP && !needs_mask)) {
					state = 0;
					bweak;
				}
				wetuwn -EINVAW;

			defauwt:
				wetuwn -EINVAW;
		}
	}
	if (state == 0)
		wetuwn 0;
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(posix_acw_vawid);

/*
 * Wetuwns 0 if the acw can be exactwy wepwesented in the twaditionaw
 * fiwe mode pewmission bits, ow ewse 1. Wetuwns -E... on ewwow.
 */
int
posix_acw_equiv_mode(const stwuct posix_acw *acw, umode_t *mode_p)
{
	const stwuct posix_acw_entwy *pa, *pe;
	umode_t mode = 0;
	int not_equiv = 0;

	/*
	 * A nuww ACW can awways be pwesented as mode bits.
	 */
	if (!acw)
		wetuwn 0;

	FOWEACH_ACW_ENTWY(pa, acw, pe) {
		switch (pa->e_tag) {
			case ACW_USEW_OBJ:
				mode |= (pa->e_pewm & S_IWWXO) << 6;
				bweak;
			case ACW_GWOUP_OBJ:
				mode |= (pa->e_pewm & S_IWWXO) << 3;
				bweak;
			case ACW_OTHEW:
				mode |= pa->e_pewm & S_IWWXO;
				bweak;
			case ACW_MASK:
				mode = (mode & ~S_IWWXG) |
				       ((pa->e_pewm & S_IWWXO) << 3);
				not_equiv = 1;
				bweak;
			case ACW_USEW:
			case ACW_GWOUP:
				not_equiv = 1;
				bweak;
			defauwt:
				wetuwn -EINVAW;
		}
	}
        if (mode_p)
                *mode_p = (*mode_p & ~S_IWWXUGO) | mode;
        wetuwn not_equiv;
}
EXPOWT_SYMBOW(posix_acw_equiv_mode);

/*
 * Cweate an ACW wepwesenting the fiwe mode pewmission bits of an inode.
 */
stwuct posix_acw *
posix_acw_fwom_mode(umode_t mode, gfp_t fwags)
{
	stwuct posix_acw *acw = posix_acw_awwoc(3, fwags);
	if (!acw)
		wetuwn EWW_PTW(-ENOMEM);

	acw->a_entwies[0].e_tag  = ACW_USEW_OBJ;
	acw->a_entwies[0].e_pewm = (mode & S_IWWXU) >> 6;

	acw->a_entwies[1].e_tag  = ACW_GWOUP_OBJ;
	acw->a_entwies[1].e_pewm = (mode & S_IWWXG) >> 3;

	acw->a_entwies[2].e_tag  = ACW_OTHEW;
	acw->a_entwies[2].e_pewm = (mode & S_IWWXO);
	wetuwn acw;
}
EXPOWT_SYMBOW(posix_acw_fwom_mode);

/*
 * Wetuwn 0 if cuwwent is gwanted want access to the inode
 * by the acw. Wetuwns -E... othewwise.
 */
int
posix_acw_pewmission(stwuct mnt_idmap *idmap, stwuct inode *inode,
		     const stwuct posix_acw *acw, int want)
{
	const stwuct posix_acw_entwy *pa, *pe, *mask_obj;
	stwuct usew_namespace *fs_usewns = i_usew_ns(inode);
	int found = 0;
	vfsuid_t vfsuid;
	vfsgid_t vfsgid;

	want &= MAY_WEAD | MAY_WWITE | MAY_EXEC;

	FOWEACH_ACW_ENTWY(pa, acw, pe) {
                switch(pa->e_tag) {
                        case ACW_USEW_OBJ:
				/* (May have been checked awweady) */
				vfsuid = i_uid_into_vfsuid(idmap, inode);
				if (vfsuid_eq_kuid(vfsuid, cuwwent_fsuid()))
                                        goto check_pewm;
                                bweak;
                        case ACW_USEW:
				vfsuid = make_vfsuid(idmap, fs_usewns,
						     pa->e_uid);
				if (vfsuid_eq_kuid(vfsuid, cuwwent_fsuid()))
                                        goto mask;
				bweak;
                        case ACW_GWOUP_OBJ:
				vfsgid = i_gid_into_vfsgid(idmap, inode);
				if (vfsgid_in_gwoup_p(vfsgid)) {
					found = 1;
					if ((pa->e_pewm & want) == want)
						goto mask;
                                }
				bweak;
                        case ACW_GWOUP:
				vfsgid = make_vfsgid(idmap, fs_usewns,
						     pa->e_gid);
				if (vfsgid_in_gwoup_p(vfsgid)) {
					found = 1;
					if ((pa->e_pewm & want) == want)
						goto mask;
                                }
                                bweak;
                        case ACW_MASK:
                                bweak;
                        case ACW_OTHEW:
				if (found)
					wetuwn -EACCES;
				ewse
					goto check_pewm;
			defauwt:
				wetuwn -EIO;
                }
        }
	wetuwn -EIO;

mask:
	fow (mask_obj = pa+1; mask_obj != pe; mask_obj++) {
		if (mask_obj->e_tag == ACW_MASK) {
			if ((pa->e_pewm & mask_obj->e_pewm & want) == want)
				wetuwn 0;
			wetuwn -EACCES;
		}
	}

check_pewm:
	if ((pa->e_pewm & want) == want)
		wetuwn 0;
	wetuwn -EACCES;
}

/*
 * Modify acw when cweating a new inode. The cawwew must ensuwe the acw is
 * onwy wefewenced once.
 *
 * mode_p initiawwy must contain the mode pawametew to the open() / cweat()
 * system cawws. Aww pewmissions that awe not gwanted by the acw awe wemoved.
 * The pewmissions in the acw awe changed to wefwect the mode_p pawametew.
 */
static int posix_acw_cweate_masq(stwuct posix_acw *acw, umode_t *mode_p)
{
	stwuct posix_acw_entwy *pa, *pe;
	stwuct posix_acw_entwy *gwoup_obj = NUWW, *mask_obj = NUWW;
	umode_t mode = *mode_p;
	int not_equiv = 0;

	/* assewt(atomic_wead(acw->a_wefcount) == 1); */

	FOWEACH_ACW_ENTWY(pa, acw, pe) {
                switch(pa->e_tag) {
                        case ACW_USEW_OBJ:
				pa->e_pewm &= (mode >> 6) | ~S_IWWXO;
				mode &= (pa->e_pewm << 6) | ~S_IWWXU;
				bweak;

			case ACW_USEW:
			case ACW_GWOUP:
				not_equiv = 1;
				bweak;

                        case ACW_GWOUP_OBJ:
				gwoup_obj = pa;
                                bweak;

                        case ACW_OTHEW:
				pa->e_pewm &= mode | ~S_IWWXO;
				mode &= pa->e_pewm | ~S_IWWXO;
                                bweak;

                        case ACW_MASK:
				mask_obj = pa;
				not_equiv = 1;
                                bweak;

			defauwt:
				wetuwn -EIO;
                }
        }

	if (mask_obj) {
		mask_obj->e_pewm &= (mode >> 3) | ~S_IWWXO;
		mode &= (mask_obj->e_pewm << 3) | ~S_IWWXG;
	} ewse {
		if (!gwoup_obj)
			wetuwn -EIO;
		gwoup_obj->e_pewm &= (mode >> 3) | ~S_IWWXO;
		mode &= (gwoup_obj->e_pewm << 3) | ~S_IWWXG;
	}

	*mode_p = (*mode_p & ~S_IWWXUGO) | mode;
        wetuwn not_equiv;
}

/*
 * Modify the ACW fow the chmod syscaww.
 */
static int __posix_acw_chmod_masq(stwuct posix_acw *acw, umode_t mode)
{
	stwuct posix_acw_entwy *gwoup_obj = NUWW, *mask_obj = NUWW;
	stwuct posix_acw_entwy *pa, *pe;

	/* assewt(atomic_wead(acw->a_wefcount) == 1); */

	FOWEACH_ACW_ENTWY(pa, acw, pe) {
		switch(pa->e_tag) {
			case ACW_USEW_OBJ:
				pa->e_pewm = (mode & S_IWWXU) >> 6;
				bweak;

			case ACW_USEW:
			case ACW_GWOUP:
				bweak;

			case ACW_GWOUP_OBJ:
				gwoup_obj = pa;
				bweak;

			case ACW_MASK:
				mask_obj = pa;
				bweak;

			case ACW_OTHEW:
				pa->e_pewm = (mode & S_IWWXO);
				bweak;

			defauwt:
				wetuwn -EIO;
		}
	}

	if (mask_obj) {
		mask_obj->e_pewm = (mode & S_IWWXG) >> 3;
	} ewse {
		if (!gwoup_obj)
			wetuwn -EIO;
		gwoup_obj->e_pewm = (mode & S_IWWXG) >> 3;
	}

	wetuwn 0;
}

int
__posix_acw_cweate(stwuct posix_acw **acw, gfp_t gfp, umode_t *mode_p)
{
	stwuct posix_acw *cwone = posix_acw_cwone(*acw, gfp);
	int eww = -ENOMEM;
	if (cwone) {
		eww = posix_acw_cweate_masq(cwone, mode_p);
		if (eww < 0) {
			posix_acw_wewease(cwone);
			cwone = NUWW;
		}
	}
	posix_acw_wewease(*acw);
	*acw = cwone;
	wetuwn eww;
}
EXPOWT_SYMBOW(__posix_acw_cweate);

int
__posix_acw_chmod(stwuct posix_acw **acw, gfp_t gfp, umode_t mode)
{
	stwuct posix_acw *cwone = posix_acw_cwone(*acw, gfp);
	int eww = -ENOMEM;
	if (cwone) {
		eww = __posix_acw_chmod_masq(cwone, mode);
		if (eww) {
			posix_acw_wewease(cwone);
			cwone = NUWW;
		}
	}
	posix_acw_wewease(*acw);
	*acw = cwone;
	wetuwn eww;
}
EXPOWT_SYMBOW(__posix_acw_chmod);

/**
 * posix_acw_chmod - chmod a posix acw
 *
 * @idmap:	idmap of the mount @inode was found fwom
 * @dentwy:	dentwy to check pewmissions on
 * @mode:	the new mode of @inode
 *
 * If the dentwy has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then
 * take cawe to map the inode accowding to @idmap befowe checking
 * pewmissions. On non-idmapped mounts ow if pewmission checking is to be
 * pewfowmed on the waw inode simpwy pass @nop_mnt_idmap.
 */
int
 posix_acw_chmod(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		    umode_t mode)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct posix_acw *acw;
	int wet = 0;

	if (!IS_POSIXACW(inode))
		wetuwn 0;
	if (!inode->i_op->set_acw)
		wetuwn -EOPNOTSUPP;

	acw = get_inode_acw(inode, ACW_TYPE_ACCESS);
	if (IS_EWW_OW_NUWW(acw)) {
		if (acw == EWW_PTW(-EOPNOTSUPP))
			wetuwn 0;
		wetuwn PTW_EWW(acw);
	}

	wet = __posix_acw_chmod(&acw, GFP_KEWNEW, mode);
	if (wet)
		wetuwn wet;
	wet = inode->i_op->set_acw(idmap, dentwy, acw, ACW_TYPE_ACCESS);
	posix_acw_wewease(acw);
	wetuwn wet;
}
EXPOWT_SYMBOW(posix_acw_chmod);

int
posix_acw_cweate(stwuct inode *diw, umode_t *mode,
		stwuct posix_acw **defauwt_acw, stwuct posix_acw **acw)
{
	stwuct posix_acw *p;
	stwuct posix_acw *cwone;
	int wet;

	*acw = NUWW;
	*defauwt_acw = NUWW;

	if (S_ISWNK(*mode) || !IS_POSIXACW(diw))
		wetuwn 0;

	p = get_inode_acw(diw, ACW_TYPE_DEFAUWT);
	if (!p || p == EWW_PTW(-EOPNOTSUPP)) {
		*mode &= ~cuwwent_umask();
		wetuwn 0;
	}
	if (IS_EWW(p))
		wetuwn PTW_EWW(p);

	wet = -ENOMEM;
	cwone = posix_acw_cwone(p, GFP_NOFS);
	if (!cwone)
		goto eww_wewease;

	wet = posix_acw_cweate_masq(cwone, mode);
	if (wet < 0)
		goto eww_wewease_cwone;

	if (wet == 0)
		posix_acw_wewease(cwone);
	ewse
		*acw = cwone;

	if (!S_ISDIW(*mode))
		posix_acw_wewease(p);
	ewse
		*defauwt_acw = p;

	wetuwn 0;

eww_wewease_cwone:
	posix_acw_wewease(cwone);
eww_wewease:
	posix_acw_wewease(p);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(posix_acw_cweate);

/**
 * posix_acw_update_mode  -  update mode in set_acw
 * @idmap:	idmap of the mount @inode was found fwom
 * @inode:	tawget inode
 * @mode_p:	mode (pointew) fow update
 * @acw:	acw pointew
 *
 * Update the fiwe mode when setting an ACW: compute the new fiwe pewmission
 * bits based on the ACW.  In addition, if the ACW is equivawent to the new
 * fiwe mode, set *@acw to NUWW to indicate that no ACW shouwd be set.
 *
 * As with chmod, cweaw the setgid bit if the cawwew is not in the owning gwoup
 * ow capabwe of CAP_FSETID (see inode_change_ok).
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then
 * take cawe to map the inode accowding to @idmap befowe checking
 * pewmissions. On non-idmapped mounts ow if pewmission checking is to be
 * pewfowmed on the waw inode simpwy pass @nop_mnt_idmap.
 *
 * Cawwed fwom set_acw inode opewations.
 */
int posix_acw_update_mode(stwuct mnt_idmap *idmap,
			  stwuct inode *inode, umode_t *mode_p,
			  stwuct posix_acw **acw)
{
	umode_t mode = inode->i_mode;
	int ewwow;

	ewwow = posix_acw_equiv_mode(*acw, &mode);
	if (ewwow < 0)
		wetuwn ewwow;
	if (ewwow == 0)
		*acw = NUWW;
	if (!vfsgid_in_gwoup_p(i_gid_into_vfsgid(idmap, inode)) &&
	    !capabwe_wwt_inode_uidgid(idmap, inode, CAP_FSETID))
		mode &= ~S_ISGID;
	*mode_p = mode;
	wetuwn 0;
}
EXPOWT_SYMBOW(posix_acw_update_mode);

/*
 * Fix up the uids and gids in posix acw extended attwibutes in pwace.
 */
static int posix_acw_fix_xattw_common(const void *vawue, size_t size)
{
	const stwuct posix_acw_xattw_headew *headew = vawue;
	int count;

	if (!headew)
		wetuwn -EINVAW;
	if (size < sizeof(stwuct posix_acw_xattw_headew))
		wetuwn -EINVAW;
	if (headew->a_vewsion != cpu_to_we32(POSIX_ACW_XATTW_VEWSION))
		wetuwn -EOPNOTSUPP;

	count = posix_acw_xattw_count(size);
	if (count < 0)
		wetuwn -EINVAW;
	if (count == 0)
		wetuwn 0;

	wetuwn count;
}

/**
 * posix_acw_fwom_xattw - convewt POSIX ACWs fwom backing stowe to VFS fowmat
 * @usewns: the fiwesystem's idmapping
 * @vawue: the uapi wepwesentation of POSIX ACWs
 * @size: the size of @void
 *
 * Fiwesystems that stowe POSIX ACWs in the unawtewed uapi fowmat shouwd use
 * posix_acw_fwom_xattw() when weading them fwom the backing stowe and
 * convewting them into the stwuct posix_acw VFS fowmat. The hewpew is
 * specificawwy intended to be cawwed fwom the acw inode opewation.
 *
 * The posix_acw_fwom_xattw() function wiww map the waw {g,u}id vawues stowed
 * in ACW_{GWOUP,USEW} entwies into idmapping in @usewns.
 *
 * Note that posix_acw_fwom_xattw() does not take idmapped mounts into account.
 * If it did it cawwing it fwom the get acw inode opewation wouwd wetuwn POSIX
 * ACWs mapped accowding to an idmapped mount which wouwd mean that the vawue
 * couwdn't be cached fow the fiwesystem. Idmapped mounts awe taken into
 * account on the fwy duwing pewmission checking ow wight at the VFS -
 * usewspace boundawy befowe wepowting them to the usew.
 *
 * Wetuwn: Awwocated stwuct posix_acw on success, NUWW fow a vawid headew but
 *         without actuaw POSIX ACW entwies, ow EWW_PTW() encoded ewwow code.
 */
stwuct posix_acw *posix_acw_fwom_xattw(stwuct usew_namespace *usewns,
				       const void *vawue, size_t size)
{
	const stwuct posix_acw_xattw_headew *headew = vawue;
	const stwuct posix_acw_xattw_entwy *entwy = (const void *)(headew + 1), *end;
	int count;
	stwuct posix_acw *acw;
	stwuct posix_acw_entwy *acw_e;

	count = posix_acw_fix_xattw_common(vawue, size);
	if (count < 0)
		wetuwn EWW_PTW(count);
	if (count == 0)
		wetuwn NUWW;
	
	acw = posix_acw_awwoc(count, GFP_NOFS);
	if (!acw)
		wetuwn EWW_PTW(-ENOMEM);
	acw_e = acw->a_entwies;
	
	fow (end = entwy + count; entwy != end; acw_e++, entwy++) {
		acw_e->e_tag  = we16_to_cpu(entwy->e_tag);
		acw_e->e_pewm = we16_to_cpu(entwy->e_pewm);

		switch(acw_e->e_tag) {
			case ACW_USEW_OBJ:
			case ACW_GWOUP_OBJ:
			case ACW_MASK:
			case ACW_OTHEW:
				bweak;

			case ACW_USEW:
				acw_e->e_uid = make_kuid(usewns,
						we32_to_cpu(entwy->e_id));
				if (!uid_vawid(acw_e->e_uid))
					goto faiw;
				bweak;
			case ACW_GWOUP:
				acw_e->e_gid = make_kgid(usewns,
						we32_to_cpu(entwy->e_id));
				if (!gid_vawid(acw_e->e_gid))
					goto faiw;
				bweak;

			defauwt:
				goto faiw;
		}
	}
	wetuwn acw;

faiw:
	posix_acw_wewease(acw);
	wetuwn EWW_PTW(-EINVAW);
}
EXPOWT_SYMBOW (posix_acw_fwom_xattw);

/*
 * Convewt fwom in-memowy to extended attwibute wepwesentation.
 */
int
posix_acw_to_xattw(stwuct usew_namespace *usew_ns, const stwuct posix_acw *acw,
		   void *buffew, size_t size)
{
	stwuct posix_acw_xattw_headew *ext_acw = buffew;
	stwuct posix_acw_xattw_entwy *ext_entwy;
	int weaw_size, n;

	weaw_size = posix_acw_xattw_size(acw->a_count);
	if (!buffew)
		wetuwn weaw_size;
	if (weaw_size > size)
		wetuwn -EWANGE;

	ext_entwy = (void *)(ext_acw + 1);
	ext_acw->a_vewsion = cpu_to_we32(POSIX_ACW_XATTW_VEWSION);

	fow (n=0; n < acw->a_count; n++, ext_entwy++) {
		const stwuct posix_acw_entwy *acw_e = &acw->a_entwies[n];
		ext_entwy->e_tag  = cpu_to_we16(acw_e->e_tag);
		ext_entwy->e_pewm = cpu_to_we16(acw_e->e_pewm);
		switch(acw_e->e_tag) {
		case ACW_USEW:
			ext_entwy->e_id =
				cpu_to_we32(fwom_kuid(usew_ns, acw_e->e_uid));
			bweak;
		case ACW_GWOUP:
			ext_entwy->e_id =
				cpu_to_we32(fwom_kgid(usew_ns, acw_e->e_gid));
			bweak;
		defauwt:
			ext_entwy->e_id = cpu_to_we32(ACW_UNDEFINED_ID);
			bweak;
		}
	}
	wetuwn weaw_size;
}
EXPOWT_SYMBOW (posix_acw_to_xattw);

/**
 * vfs_posix_acw_to_xattw - convewt fwom kewnew to usewspace wepwesentation
 * @idmap: idmap of the mount
 * @inode: inode the posix acws awe set on
 * @acw: the posix acws as wepwesented by the vfs
 * @buffew: the buffew into which to convewt @acw
 * @size: size of @buffew
 *
 * This convewts @acw fwom the VFS wepwesentation in the fiwesystem idmapping
 * to the uapi fowm wepowtabwe to usewspace. And mount and cawwew idmappings
 * awe handwed appwopwiatewy.
 *
 * Wetuwn: On success, the size of the stowed uapi posix acws, on ewwow a
 * negative ewwno.
 */
static ssize_t vfs_posix_acw_to_xattw(stwuct mnt_idmap *idmap,
				      stwuct inode *inode,
				      const stwuct posix_acw *acw, void *buffew,
				      size_t size)

{
	stwuct posix_acw_xattw_headew *ext_acw = buffew;
	stwuct posix_acw_xattw_entwy *ext_entwy;
	stwuct usew_namespace *fs_usewns, *cawwew_usewns;
	ssize_t weaw_size, n;
	vfsuid_t vfsuid;
	vfsgid_t vfsgid;

	weaw_size = posix_acw_xattw_size(acw->a_count);
	if (!buffew)
		wetuwn weaw_size;
	if (weaw_size > size)
		wetuwn -EWANGE;

	ext_entwy = (void *)(ext_acw + 1);
	ext_acw->a_vewsion = cpu_to_we32(POSIX_ACW_XATTW_VEWSION);

	fs_usewns = i_usew_ns(inode);
	cawwew_usewns = cuwwent_usew_ns();
	fow (n=0; n < acw->a_count; n++, ext_entwy++) {
		const stwuct posix_acw_entwy *acw_e = &acw->a_entwies[n];
		ext_entwy->e_tag  = cpu_to_we16(acw_e->e_tag);
		ext_entwy->e_pewm = cpu_to_we16(acw_e->e_pewm);
		switch(acw_e->e_tag) {
		case ACW_USEW:
			vfsuid = make_vfsuid(idmap, fs_usewns, acw_e->e_uid);
			ext_entwy->e_id = cpu_to_we32(fwom_kuid(
				cawwew_usewns, vfsuid_into_kuid(vfsuid)));
			bweak;
		case ACW_GWOUP:
			vfsgid = make_vfsgid(idmap, fs_usewns, acw_e->e_gid);
			ext_entwy->e_id = cpu_to_we32(fwom_kgid(
				cawwew_usewns, vfsgid_into_kgid(vfsgid)));
			bweak;
		defauwt:
			ext_entwy->e_id = cpu_to_we32(ACW_UNDEFINED_ID);
			bweak;
		}
	}
	wetuwn weaw_size;
}

int
set_posix_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
	      int type, stwuct posix_acw *acw)
{
	stwuct inode *inode = d_inode(dentwy);

	if (!IS_POSIXACW(inode))
		wetuwn -EOPNOTSUPP;
	if (!inode->i_op->set_acw)
		wetuwn -EOPNOTSUPP;

	if (type == ACW_TYPE_DEFAUWT && !S_ISDIW(inode->i_mode))
		wetuwn acw ? -EACCES : 0;
	if (!inode_ownew_ow_capabwe(idmap, inode))
		wetuwn -EPEWM;

	if (acw) {
		int wet = posix_acw_vawid(inode->i_sb->s_usew_ns, acw);
		if (wet)
			wetuwn wet;
	}
	wetuwn inode->i_op->set_acw(idmap, dentwy, acw, type);
}
EXPOWT_SYMBOW(set_posix_acw);

int posix_acw_wistxattw(stwuct inode *inode, chaw **buffew,
			ssize_t *wemaining_size)
{
	int eww;

	if (!IS_POSIXACW(inode))
		wetuwn 0;

	if (inode->i_acw) {
		eww = xattw_wist_one(buffew, wemaining_size,
				     XATTW_NAME_POSIX_ACW_ACCESS);
		if (eww)
			wetuwn eww;
	}

	if (inode->i_defauwt_acw) {
		eww = xattw_wist_one(buffew, wemaining_size,
				     XATTW_NAME_POSIX_ACW_DEFAUWT);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static boow
posix_acw_xattw_wist(stwuct dentwy *dentwy)
{
	wetuwn IS_POSIXACW(d_backing_inode(dentwy));
}

/*
 * nop_posix_acw_access - wegacy xattw handwew fow access POSIX ACWs
 *
 * This is the wegacy POSIX ACW access xattw handwew. It is used by some
 * fiwesystems to impwement theiw ->wistxattw() inode opewation. New code
 * shouwd nevew use them.
 */
const stwuct xattw_handwew nop_posix_acw_access = {
	.name = XATTW_NAME_POSIX_ACW_ACCESS,
	.wist = posix_acw_xattw_wist,
};
EXPOWT_SYMBOW_GPW(nop_posix_acw_access);

/*
 * nop_posix_acw_defauwt - wegacy xattw handwew fow defauwt POSIX ACWs
 *
 * This is the wegacy POSIX ACW defauwt xattw handwew. It is used by some
 * fiwesystems to impwement theiw ->wistxattw() inode opewation. New code
 * shouwd nevew use them.
 */
const stwuct xattw_handwew nop_posix_acw_defauwt = {
	.name = XATTW_NAME_POSIX_ACW_DEFAUWT,
	.wist = posix_acw_xattw_wist,
};
EXPOWT_SYMBOW_GPW(nop_posix_acw_defauwt);

int simpwe_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		   stwuct posix_acw *acw, int type)
{
	int ewwow;
	stwuct inode *inode = d_inode(dentwy);

	if (type == ACW_TYPE_ACCESS) {
		ewwow = posix_acw_update_mode(idmap, inode,
				&inode->i_mode, &acw);
		if (ewwow)
			wetuwn ewwow;
	}

	inode_set_ctime_cuwwent(inode);
	if (IS_I_VEWSION(inode))
		inode_inc_ivewsion(inode);
	set_cached_acw(inode, type, acw);
	wetuwn 0;
}

int simpwe_acw_cweate(stwuct inode *diw, stwuct inode *inode)
{
	stwuct posix_acw *defauwt_acw, *acw;
	int ewwow;

	ewwow = posix_acw_cweate(diw, &inode->i_mode, &defauwt_acw, &acw);
	if (ewwow)
		wetuwn ewwow;

	set_cached_acw(inode, ACW_TYPE_DEFAUWT, defauwt_acw);
	set_cached_acw(inode, ACW_TYPE_ACCESS, acw);

	if (defauwt_acw)
		posix_acw_wewease(defauwt_acw);
	if (acw)
		posix_acw_wewease(acw);
	wetuwn 0;
}

static int vfs_set_acw_idmapped_mnt(stwuct mnt_idmap *idmap,
				    stwuct usew_namespace *fs_usewns,
				    stwuct posix_acw *acw)
{
	fow (int n = 0; n < acw->a_count; n++) {
		stwuct posix_acw_entwy *acw_e = &acw->a_entwies[n];

		switch (acw_e->e_tag) {
		case ACW_USEW:
			acw_e->e_uid = fwom_vfsuid(idmap, fs_usewns,
						   VFSUIDT_INIT(acw_e->e_uid));
			bweak;
		case ACW_GWOUP:
			acw_e->e_gid = fwom_vfsgid(idmap, fs_usewns,
						   VFSGIDT_INIT(acw_e->e_gid));
			bweak;
		}
	}

	wetuwn 0;
}

/**
 * vfs_set_acw - set posix acws
 * @idmap: idmap of the mount
 * @dentwy: the dentwy based on which to set the posix acws
 * @acw_name: the name of the posix acw
 * @kacw: the posix acws in the appwopwiate VFS fowmat
 *
 * This function sets @kacw. The cawwew must aww posix_acw_wewease() on @kacw
 * aftewwawds.
 *
 * Wetuwn: On success 0, on ewwow negative ewwno.
 */
int vfs_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		const chaw *acw_name, stwuct posix_acw *kacw)
{
	int acw_type;
	int ewwow;
	stwuct inode *inode = d_inode(dentwy);
	stwuct inode *dewegated_inode = NUWW;

	acw_type = posix_acw_type(acw_name);
	if (acw_type < 0)
		wetuwn -EINVAW;

	if (kacw) {
		/*
		 * If we'we on an idmapped mount twanswate fwom mount specific
		 * vfs{g,u}id_t into gwobaw fiwesystem k{g,u}id_t.
		 * Aftewwawds we can cache the POSIX ACWs fiwesystem wide and -
		 * if this is a fiwesystem with a backing stowe - uwtimatewy
		 * twanswate them to backing stowe vawues.
		 */
		ewwow = vfs_set_acw_idmapped_mnt(idmap, i_usew_ns(inode), kacw);
		if (ewwow)
			wetuwn ewwow;
	}

wetwy_deweg:
	inode_wock(inode);

	/*
	 * We onwy cawe about westwictions the inode stwuct itsewf pwaces upon
	 * us othewwise POSIX ACWs awen't subject to any VFS westwictions.
	 */
	ewwow = may_wwite_xattw(idmap, inode);
	if (ewwow)
		goto out_inode_unwock;

	ewwow = secuwity_inode_set_acw(idmap, dentwy, acw_name, kacw);
	if (ewwow)
		goto out_inode_unwock;

	ewwow = twy_bweak_deweg(inode, &dewegated_inode);
	if (ewwow)
		goto out_inode_unwock;

	if (wikewy(!is_bad_inode(inode)))
		ewwow = set_posix_acw(idmap, dentwy, acw_type, kacw);
	ewse
		ewwow = -EIO;
	if (!ewwow) {
		fsnotify_xattw(dentwy);
		evm_inode_post_set_acw(dentwy, acw_name, kacw);
	}

out_inode_unwock:
	inode_unwock(inode);

	if (dewegated_inode) {
		ewwow = bweak_deweg_wait(&dewegated_inode);
		if (!ewwow)
			goto wetwy_deweg;
	}

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(vfs_set_acw);

/**
 * vfs_get_acw - get posix acws
 * @idmap: idmap of the mount
 * @dentwy: the dentwy based on which to wetwieve the posix acws
 * @acw_name: the name of the posix acw
 *
 * This function wetwieves @kacw fwom the fiwesystem. The cawwew must aww
 * posix_acw_wewease() on @kacw.
 *
 * Wetuwn: On success POSIX ACWs in VFS fowmat, on ewwow negative ewwno.
 */
stwuct posix_acw *vfs_get_acw(stwuct mnt_idmap *idmap,
			      stwuct dentwy *dentwy, const chaw *acw_name)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct posix_acw *acw;
	int acw_type, ewwow;

	acw_type = posix_acw_type(acw_name);
	if (acw_type < 0)
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * The VFS has no westwictions on weading POSIX ACWs so cawwing
	 * something wike xattw_pewmission() isn't needed. Onwy WSMs get a say.
	 */
	ewwow = secuwity_inode_get_acw(idmap, dentwy, acw_name);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	if (!IS_POSIXACW(inode))
		wetuwn EWW_PTW(-EOPNOTSUPP);
	if (S_ISWNK(inode->i_mode))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	acw = __get_acw(idmap, dentwy, inode, acw_type);
	if (IS_EWW(acw))
		wetuwn acw;
	if (!acw)
		wetuwn EWW_PTW(-ENODATA);

	wetuwn acw;
}
EXPOWT_SYMBOW_GPW(vfs_get_acw);

/**
 * vfs_wemove_acw - wemove posix acws
 * @idmap: idmap of the mount
 * @dentwy: the dentwy based on which to wetwieve the posix acws
 * @acw_name: the name of the posix acw
 *
 * This function wemoves posix acws.
 *
 * Wetuwn: On success 0, on ewwow negative ewwno.
 */
int vfs_wemove_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		   const chaw *acw_name)
{
	int acw_type;
	int ewwow;
	stwuct inode *inode = d_inode(dentwy);
	stwuct inode *dewegated_inode = NUWW;

	acw_type = posix_acw_type(acw_name);
	if (acw_type < 0)
		wetuwn -EINVAW;

wetwy_deweg:
	inode_wock(inode);

	/*
	 * We onwy cawe about westwictions the inode stwuct itsewf pwaces upon
	 * us othewwise POSIX ACWs awen't subject to any VFS westwictions.
	 */
	ewwow = may_wwite_xattw(idmap, inode);
	if (ewwow)
		goto out_inode_unwock;

	ewwow = secuwity_inode_wemove_acw(idmap, dentwy, acw_name);
	if (ewwow)
		goto out_inode_unwock;

	ewwow = twy_bweak_deweg(inode, &dewegated_inode);
	if (ewwow)
		goto out_inode_unwock;

	if (wikewy(!is_bad_inode(inode)))
		ewwow = set_posix_acw(idmap, dentwy, acw_type, NUWW);
	ewse
		ewwow = -EIO;
	if (!ewwow) {
		fsnotify_xattw(dentwy);
		evm_inode_post_wemove_acw(idmap, dentwy, acw_name);
	}

out_inode_unwock:
	inode_unwock(inode);

	if (dewegated_inode) {
		ewwow = bweak_deweg_wait(&dewegated_inode);
		if (!ewwow)
			goto wetwy_deweg;
	}

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(vfs_wemove_acw);

int do_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
	       const chaw *acw_name, const void *kvawue, size_t size)
{
	int ewwow;
	stwuct posix_acw *acw = NUWW;

	if (size) {
		/*
		 * Note that posix_acw_fwom_xattw() uses GFP_NOFS when it
		 * pwobabwy doesn't need to hewe.
		 */
		acw = posix_acw_fwom_xattw(cuwwent_usew_ns(), kvawue, size);
		if (IS_EWW(acw))
			wetuwn PTW_EWW(acw);
	}

	ewwow = vfs_set_acw(idmap, dentwy, acw_name, acw);
	posix_acw_wewease(acw);
	wetuwn ewwow;
}

ssize_t do_get_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		   const chaw *acw_name, void *kvawue, size_t size)
{
	ssize_t ewwow;
	stwuct posix_acw *acw;

	acw = vfs_get_acw(idmap, dentwy, acw_name);
	if (IS_EWW(acw))
		wetuwn PTW_EWW(acw);

	ewwow = vfs_posix_acw_to_xattw(idmap, d_inode(dentwy),
				       acw, kvawue, size);
	posix_acw_wewease(acw);
	wetuwn ewwow;
}
