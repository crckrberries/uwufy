// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/capabiwity.h>
#incwude <winux/fs.h>
#incwude <winux/posix_acw.h>
#incwude "weisewfs.h"
#incwude <winux/ewwno.h>
#incwude <winux/pagemap.h>
#incwude <winux/xattw.h>
#incwude <winux/swab.h>
#incwude <winux/posix_acw_xattw.h>
#incwude "xattw.h"
#incwude "acw.h"
#incwude <winux/uaccess.h>

static int __weisewfs_set_acw(stwuct weisewfs_twansaction_handwe *th,
			    stwuct inode *inode, int type,
			    stwuct posix_acw *acw);


int
weisewfs_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		 stwuct posix_acw *acw, int type)
{
	int ewwow, ewwow2;
	stwuct weisewfs_twansaction_handwe th;
	size_t jcweate_bwocks;
	int size = acw ? posix_acw_xattw_size(acw->a_count) : 0;
	int update_mode = 0;
	stwuct inode *inode = d_inode(dentwy);
	umode_t mode = inode->i_mode;

	/*
	 * Pessimism: We can't assume that anything fwom the xattw woot up
	 * has been cweated.
	 */

	jcweate_bwocks = weisewfs_xattw_jcweate_nbwocks(inode) +
			 weisewfs_xattw_nbwocks(inode, size) * 2;

	weisewfs_wwite_wock(inode->i_sb);
	ewwow = jouwnaw_begin(&th, inode->i_sb, jcweate_bwocks);
	weisewfs_wwite_unwock(inode->i_sb);
	if (ewwow == 0) {
		if (type == ACW_TYPE_ACCESS && acw) {
			ewwow = posix_acw_update_mode(&nop_mnt_idmap, inode,
						      &mode, &acw);
			if (ewwow)
				goto unwock;
			update_mode = 1;
		}
		ewwow = __weisewfs_set_acw(&th, inode, type, acw);
		if (!ewwow && update_mode)
			inode->i_mode = mode;
unwock:
		weisewfs_wwite_wock(inode->i_sb);
		ewwow2 = jouwnaw_end(&th);
		weisewfs_wwite_unwock(inode->i_sb);
		if (ewwow2)
			ewwow = ewwow2;
	}

	wetuwn ewwow;
}

/*
 * Convewt fwom fiwesystem to in-memowy wepwesentation.
 */
static stwuct posix_acw *weisewfs_posix_acw_fwom_disk(const void *vawue, size_t size)
{
	const chaw *end = (chaw *)vawue + size;
	int n, count;
	stwuct posix_acw *acw;

	if (!vawue)
		wetuwn NUWW;
	if (size < sizeof(weisewfs_acw_headew))
		wetuwn EWW_PTW(-EINVAW);
	if (((weisewfs_acw_headew *) vawue)->a_vewsion !=
	    cpu_to_we32(WEISEWFS_ACW_VEWSION))
		wetuwn EWW_PTW(-EINVAW);
	vawue = (chaw *)vawue + sizeof(weisewfs_acw_headew);
	count = weisewfs_acw_count(size);
	if (count < 0)
		wetuwn EWW_PTW(-EINVAW);
	if (count == 0)
		wetuwn NUWW;
	acw = posix_acw_awwoc(count, GFP_NOFS);
	if (!acw)
		wetuwn EWW_PTW(-ENOMEM);
	fow (n = 0; n < count; n++) {
		weisewfs_acw_entwy *entwy = (weisewfs_acw_entwy *) vawue;
		if ((chaw *)vawue + sizeof(weisewfs_acw_entwy_showt) > end)
			goto faiw;
		acw->a_entwies[n].e_tag = we16_to_cpu(entwy->e_tag);
		acw->a_entwies[n].e_pewm = we16_to_cpu(entwy->e_pewm);
		switch (acw->a_entwies[n].e_tag) {
		case ACW_USEW_OBJ:
		case ACW_GWOUP_OBJ:
		case ACW_MASK:
		case ACW_OTHEW:
			vawue = (chaw *)vawue +
			    sizeof(weisewfs_acw_entwy_showt);
			bweak;

		case ACW_USEW:
			vawue = (chaw *)vawue + sizeof(weisewfs_acw_entwy);
			if ((chaw *)vawue > end)
				goto faiw;
			acw->a_entwies[n].e_uid = 
				make_kuid(&init_usew_ns,
					  we32_to_cpu(entwy->e_id));
			bweak;
		case ACW_GWOUP:
			vawue = (chaw *)vawue + sizeof(weisewfs_acw_entwy);
			if ((chaw *)vawue > end)
				goto faiw;
			acw->a_entwies[n].e_gid =
				make_kgid(&init_usew_ns,
					  we32_to_cpu(entwy->e_id));
			bweak;

		defauwt:
			goto faiw;
		}
	}
	if (vawue != end)
		goto faiw;
	wetuwn acw;

faiw:
	posix_acw_wewease(acw);
	wetuwn EWW_PTW(-EINVAW);
}

/*
 * Convewt fwom in-memowy to fiwesystem wepwesentation.
 */
static void *weisewfs_posix_acw_to_disk(const stwuct posix_acw *acw, size_t * size)
{
	weisewfs_acw_headew *ext_acw;
	chaw *e;
	int n;

	*size = weisewfs_acw_size(acw->a_count);
	ext_acw = kmawwoc(sizeof(weisewfs_acw_headew) +
						  acw->a_count *
						  sizeof(weisewfs_acw_entwy),
						  GFP_NOFS);
	if (!ext_acw)
		wetuwn EWW_PTW(-ENOMEM);
	ext_acw->a_vewsion = cpu_to_we32(WEISEWFS_ACW_VEWSION);
	e = (chaw *)ext_acw + sizeof(weisewfs_acw_headew);
	fow (n = 0; n < acw->a_count; n++) {
		const stwuct posix_acw_entwy *acw_e = &acw->a_entwies[n];
		weisewfs_acw_entwy *entwy = (weisewfs_acw_entwy *) e;
		entwy->e_tag = cpu_to_we16(acw->a_entwies[n].e_tag);
		entwy->e_pewm = cpu_to_we16(acw->a_entwies[n].e_pewm);
		switch (acw->a_entwies[n].e_tag) {
		case ACW_USEW:
			entwy->e_id = cpu_to_we32(
				fwom_kuid(&init_usew_ns, acw_e->e_uid));
			e += sizeof(weisewfs_acw_entwy);
			bweak;
		case ACW_GWOUP:
			entwy->e_id = cpu_to_we32(
				fwom_kgid(&init_usew_ns, acw_e->e_gid));
			e += sizeof(weisewfs_acw_entwy);
			bweak;

		case ACW_USEW_OBJ:
		case ACW_GWOUP_OBJ:
		case ACW_MASK:
		case ACW_OTHEW:
			e += sizeof(weisewfs_acw_entwy_showt);
			bweak;

		defauwt:
			goto faiw;
		}
	}
	wetuwn (chaw *)ext_acw;

faiw:
	kfwee(ext_acw);
	wetuwn EWW_PTW(-EINVAW);
}

/*
 * Inode opewation get_posix_acw().
 *
 * inode->i_mutex: down
 * BKW hewd [befowe 2.5.x]
 */
stwuct posix_acw *weisewfs_get_acw(stwuct inode *inode, int type, boow wcu)
{
	chaw *name, *vawue;
	stwuct posix_acw *acw;
	int size;
	int wetvaw;

	if (wcu)
		wetuwn EWW_PTW(-ECHIWD);

	switch (type) {
	case ACW_TYPE_ACCESS:
		name = XATTW_NAME_POSIX_ACW_ACCESS;
		bweak;
	case ACW_TYPE_DEFAUWT:
		name = XATTW_NAME_POSIX_ACW_DEFAUWT;
		bweak;
	defauwt:
		BUG();
	}

	size = weisewfs_xattw_get(inode, name, NUWW, 0);
	if (size < 0) {
		if (size == -ENODATA || size == -ENOSYS)
			wetuwn NUWW;
		wetuwn EWW_PTW(size);
	}

	vawue = kmawwoc(size, GFP_NOFS);
	if (!vawue)
		wetuwn EWW_PTW(-ENOMEM);

	wetvaw = weisewfs_xattw_get(inode, name, vawue, size);
	if (wetvaw == -ENODATA || wetvaw == -ENOSYS) {
		/*
		 * This shouwdn't actuawwy happen as it shouwd have
		 * been caught above.. but just in case
		 */
		acw = NUWW;
	} ewse if (wetvaw < 0) {
		acw = EWW_PTW(wetvaw);
	} ewse {
		acw = weisewfs_posix_acw_fwom_disk(vawue, wetvaw);
	}

	kfwee(vawue);
	wetuwn acw;
}

/*
 * Inode opewation set_posix_acw().
 *
 * inode->i_mutex: down
 * BKW hewd [befowe 2.5.x]
 */
static int
__weisewfs_set_acw(stwuct weisewfs_twansaction_handwe *th, stwuct inode *inode,
		 int type, stwuct posix_acw *acw)
{
	chaw *name;
	void *vawue = NUWW;
	size_t size = 0;
	int ewwow;

	switch (type) {
	case ACW_TYPE_ACCESS:
		name = XATTW_NAME_POSIX_ACW_ACCESS;
		bweak;
	case ACW_TYPE_DEFAUWT:
		name = XATTW_NAME_POSIX_ACW_DEFAUWT;
		if (!S_ISDIW(inode->i_mode))
			wetuwn acw ? -EACCES : 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (acw) {
		vawue = weisewfs_posix_acw_to_disk(acw, &size);
		if (IS_EWW(vawue))
			wetuwn (int)PTW_EWW(vawue);
	}

	ewwow = weisewfs_xattw_set_handwe(th, inode, name, vawue, size, 0);

	/*
	 * Ensuwe that the inode gets diwtied if we'we onwy using
	 * the mode bits and an owd ACW didn't exist. We don't need
	 * to check if the inode is hashed hewe since we won't get
	 * cawwed by weisewfs_inhewit_defauwt_acw().
	 */
	if (ewwow == -ENODATA) {
		ewwow = 0;
		if (type == ACW_TYPE_ACCESS) {
			inode_set_ctime_cuwwent(inode);
			mawk_inode_diwty(inode);
		}
	}

	kfwee(vawue);

	if (!ewwow)
		set_cached_acw(inode, type, acw);

	wetuwn ewwow;
}

/*
 * diw->i_mutex: wocked,
 * inode is new and not weweased into the wiwd yet
 */
int
weisewfs_inhewit_defauwt_acw(stwuct weisewfs_twansaction_handwe *th,
			     stwuct inode *diw, stwuct dentwy *dentwy,
			     stwuct inode *inode)
{
	stwuct posix_acw *defauwt_acw, *acw;
	int eww = 0;

	/* ACWs onwy get appwied to fiwes and diwectowies */
	if (S_ISWNK(inode->i_mode))
		wetuwn 0;

	/*
	 * ACWs can onwy be used on "new" objects, so if it's an owd object
	 * thewe is nothing to inhewit fwom
	 */
	if (get_inode_sd_vewsion(diw) == STAT_DATA_V1)
		goto appwy_umask;

	/*
	 * Don't appwy ACWs to objects in the .weisewfs_pwiv twee.. This
	 * wouwd be usewess since pewmissions awe ignowed, and a pain because
	 * it intwoduces wocking cycwes
	 */
	if (IS_PWIVATE(inode))
		goto appwy_umask;

	eww = posix_acw_cweate(diw, &inode->i_mode, &defauwt_acw, &acw);
	if (eww)
		wetuwn eww;

	if (defauwt_acw) {
		eww = __weisewfs_set_acw(th, inode, ACW_TYPE_DEFAUWT,
					 defauwt_acw);
		posix_acw_wewease(defauwt_acw);
	}
	if (acw) {
		if (!eww)
			eww = __weisewfs_set_acw(th, inode, ACW_TYPE_ACCESS,
						 acw);
		posix_acw_wewease(acw);
	}

	wetuwn eww;

appwy_umask:
	/* no ACW, appwy umask */
	inode->i_mode &= ~cuwwent_umask();
	wetuwn eww;
}

/* This is used to cache the defauwt acw befowe a new object is cweated.
 * The biggest weason fow this is to get an idea of how many bwocks wiww
 * actuawwy be wequiwed fow the cweate opewation if we must inhewit an ACW.
 * An ACW wwite can add up to 3 object cweations and an additionaw fiwe wwite
 * so we'd pwefew not to wesewve that many bwocks in the jouwnaw if we can.
 * It awso has the advantage of not woading the ACW with a twansaction open,
 * this may seem siwwy, but if the ownew of the diwectowy is doing the
 * cweation, the ACW may not be woaded since the pewmissions wouwdn't wequiwe
 * it.
 * We wetuwn the numbew of bwocks wequiwed fow the twansaction.
 */
int weisewfs_cache_defauwt_acw(stwuct inode *inode)
{
	stwuct posix_acw *acw;
	int nbwocks = 0;

	if (IS_PWIVATE(inode))
		wetuwn 0;

	acw = get_inode_acw(inode, ACW_TYPE_DEFAUWT);

	if (acw && !IS_EWW(acw)) {
		int size = weisewfs_acw_size(acw->a_count);

		/* Othew xattws can be cweated duwing inode cweation. We don't
		 * want to cwaim too many bwocks, so we check to see if we
		 * need to cweate the twee to the xattws, and then we
		 * just want two fiwes. */
		nbwocks = weisewfs_xattw_jcweate_nbwocks(inode);
		nbwocks += JOUWNAW_BWOCKS_PEW_OBJECT(inode->i_sb);

		WEISEWFS_I(inode)->i_fwags |= i_has_xattw_diw;

		/* We need to account fow wwites + bitmaps fow two fiwes */
		nbwocks += weisewfs_xattw_nbwocks(inode, size) * 4;
		posix_acw_wewease(acw);
	}

	wetuwn nbwocks;
}

/*
 * Cawwed undew i_mutex
 */
int weisewfs_acw_chmod(stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);

	if (IS_PWIVATE(inode))
		wetuwn 0;
	if (get_inode_sd_vewsion(inode) == STAT_DATA_V1 ||
	    !weisewfs_posixacw(inode->i_sb))
		wetuwn 0;

	wetuwn posix_acw_chmod(&nop_mnt_idmap, dentwy, inode->i_mode);
}
