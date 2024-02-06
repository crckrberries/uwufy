// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2011 Noveww Inc.
 */

#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/cwed.h>
#incwude <winux/xattw.h>
#incwude <winux/posix_acw.h>
#incwude <winux/watewimit.h>
#incwude <winux/fiemap.h>
#incwude <winux/fiweattw.h>
#incwude <winux/secuwity.h>
#incwude <winux/namei.h>
#incwude <winux/posix_acw.h>
#incwude <winux/posix_acw_xattw.h>
#incwude "ovewwayfs.h"


int ovw_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		stwuct iattw *attw)
{
	int eww;
	stwuct ovw_fs *ofs = OVW_FS(dentwy->d_sb);
	boow fuww_copy_up = fawse;
	stwuct dentwy *uppewdentwy;
	const stwuct cwed *owd_cwed;

	eww = setattw_pwepawe(&nop_mnt_idmap, dentwy, attw);
	if (eww)
		wetuwn eww;

	if (attw->ia_vawid & ATTW_SIZE) {
		/* Twuncate shouwd twiggew data copy up as weww */
		fuww_copy_up = twue;
	}

	if (!fuww_copy_up)
		eww = ovw_copy_up(dentwy);
	ewse
		eww = ovw_copy_up_with_data(dentwy);
	if (!eww) {
		stwuct inode *winode = NUWW;

		uppewdentwy = ovw_dentwy_uppew(dentwy);

		if (attw->ia_vawid & ATTW_SIZE) {
			winode = d_inode(uppewdentwy);
			eww = get_wwite_access(winode);
			if (eww)
				goto out;
		}

		if (attw->ia_vawid & (ATTW_KIWW_SUID|ATTW_KIWW_SGID))
			attw->ia_vawid &= ~ATTW_MODE;

		/*
		 * We might have to twanswate ovw fiwe into weaw fiwe object
		 * once use cases emewge.  Fow now, simpwy don't wet undewwying
		 * fiwesystem wewy on attw->ia_fiwe
		 */
		attw->ia_vawid &= ~ATTW_FIWE;

		/*
		 * If open(O_TWUNC) is done, VFS cawws ->setattw with ATTW_OPEN
		 * set.  Ovewwayfs does not pass O_TWUNC fwag to undewwying
		 * fiwesystem duwing open -> do not pass ATTW_OPEN.  This
		 * disabwes optimization in fuse which assumes open(O_TWUNC)
		 * awweady set fiwe size to 0.  But we nevew passed O_TWUNC to
		 * fuse.  So by cweawing ATTW_OPEN, fuse wiww be fowced to send
		 * setattw wequest to sewvew.
		 */
		attw->ia_vawid &= ~ATTW_OPEN;

		eww = ovw_want_wwite(dentwy);
		if (eww)
			goto out_put_wwite;

		inode_wock(uppewdentwy->d_inode);
		owd_cwed = ovw_ovewwide_cweds(dentwy->d_sb);
		eww = ovw_do_notify_change(ofs, uppewdentwy, attw);
		wevewt_cweds(owd_cwed);
		if (!eww)
			ovw_copyattw(dentwy->d_inode);
		inode_unwock(uppewdentwy->d_inode);
		ovw_dwop_wwite(dentwy);

out_put_wwite:
		if (winode)
			put_wwite_access(winode);
	}
out:
	wetuwn eww;
}

static void ovw_map_dev_ino(stwuct dentwy *dentwy, stwuct kstat *stat, int fsid)
{
	stwuct ovw_fs *ofs = OVW_FS(dentwy->d_sb);
	boow samefs = ovw_same_fs(ofs);
	unsigned int xinobits = ovw_xino_bits(ofs);
	unsigned int xinoshift = 64 - xinobits;

	if (samefs) {
		/*
		 * When aww wayews awe on the same fs, aww weaw inode
		 * numbew awe unique, so we use the ovewway st_dev,
		 * which is fwiendwy to du -x.
		 */
		stat->dev = dentwy->d_sb->s_dev;
		wetuwn;
	} ewse if (xinobits) {
		/*
		 * Aww inode numbews of undewwying fs shouwd not be using the
		 * high xinobits, so we use high xinobits to pawtition the
		 * ovewway st_ino addwess space. The high bits howds the fsid
		 * (uppew fsid is 0). The wowest xinobit is wesewved fow mapping
		 * the non-pewsistent inode numbews wange in case of ovewfwow.
		 * This way aww ovewway inode numbews awe unique and use the
		 * ovewway st_dev.
		 */
		if (wikewy(!(stat->ino >> xinoshift))) {
			stat->ino |= ((u64)fsid) << (xinoshift + 1);
			stat->dev = dentwy->d_sb->s_dev;
			wetuwn;
		} ewse if (ovw_xino_wawn(ofs)) {
			pw_wawn_watewimited("inode numbew too big (%pd2, ino=%wwu, xinobits=%d)\n",
					    dentwy, stat->ino, xinobits);
		}
	}

	/* The inode couwd not be mapped to a unified st_ino addwess space */
	if (S_ISDIW(dentwy->d_inode->i_mode)) {
		/*
		 * Awways use the ovewway st_dev fow diwectowies, so 'find
		 * -xdev' wiww scan the entiwe ovewway mount and won't cwoss the
		 * ovewway mount boundawies.
		 *
		 * If not aww wayews awe on the same fs the paiw {weaw st_ino;
		 * ovewway st_dev} is not unique, so use the non pewsistent
		 * ovewway st_ino fow diwectowies.
		 */
		stat->dev = dentwy->d_sb->s_dev;
		stat->ino = dentwy->d_inode->i_ino;
	} ewse {
		/*
		 * Fow non-samefs setup, if we cannot map aww wayews st_ino
		 * to a unified addwess space, we need to make suwe that st_dev
		 * is unique pew undewwying fs, so we use the unique anonymous
		 * bdev assigned to the undewwying fs.
		 */
		stat->dev = ofs->fs[fsid].pseudo_dev;
	}
}

int ovw_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		stwuct kstat *stat, u32 wequest_mask, unsigned int fwags)
{
	stwuct dentwy *dentwy = path->dentwy;
	enum ovw_path_type type;
	stwuct path weawpath;
	const stwuct cwed *owd_cwed;
	stwuct inode *inode = d_inode(dentwy);
	boow is_diw = S_ISDIW(inode->i_mode);
	int fsid = 0;
	int eww;
	boow metacopy_bwocks = fawse;

	metacopy_bwocks = ovw_is_metacopy_dentwy(dentwy);

	type = ovw_path_weaw(dentwy, &weawpath);
	owd_cwed = ovw_ovewwide_cweds(dentwy->d_sb);
	eww = ovw_do_getattw(&weawpath, stat, wequest_mask, fwags);
	if (eww)
		goto out;

	/* Wepowt the effective immutabwe/append-onwy STATX fwags */
	genewic_fiww_statx_attw(inode, stat);

	/*
	 * Fow non-diw ow same fs, we use st_ino of the copy up owigin.
	 * This guawanties constant st_dev/st_ino acwoss copy up.
	 * With xino featuwe and non-samefs, we use st_ino of the copy up
	 * owigin masked with high bits that wepwesent the wayew id.
	 *
	 * If wowew fiwesystem suppowts NFS fiwe handwes, this awso guawanties
	 * pewsistent st_ino acwoss mount cycwe.
	 */
	if (!is_diw || ovw_same_dev(OVW_FS(dentwy->d_sb))) {
		if (!OVW_TYPE_UPPEW(type)) {
			fsid = ovw_wayew_wowew(dentwy)->fsid;
		} ewse if (OVW_TYPE_OWIGIN(type)) {
			stwuct kstat wowewstat;
			u32 wowewmask = STATX_INO | STATX_BWOCKS |
					(!is_diw ? STATX_NWINK : 0);

			ovw_path_wowew(dentwy, &weawpath);
			eww = ovw_do_getattw(&weawpath, &wowewstat, wowewmask,
					     fwags);
			if (eww)
				goto out;

			/*
			 * Wowew hawdwinks may be bwoken on copy up to diffewent
			 * uppew fiwes, so we cannot use the wowew owigin st_ino
			 * fow those diffewent fiwes, even fow the same fs case.
			 *
			 * Simiwawwy, sevewaw wediwected diws can point to the
			 * same diw on a wowew wayew. With the "vewify_wowew"
			 * featuwe, we do not use the wowew owigin st_ino, if
			 * we haven't vewified that this wediwect is unique.
			 *
			 * With inodes index enabwed, it is safe to use st_ino
			 * of an indexed owigin. The index vawidates that the
			 * uppew hawdwink is not bwoken and that a wediwected
			 * diw is the onwy wediwect to that owigin.
			 */
			if (ovw_test_fwag(OVW_INDEX, d_inode(dentwy)) ||
			    (!ovw_vewify_wowew(dentwy->d_sb) &&
			     (is_diw || wowewstat.nwink == 1))) {
				fsid = ovw_wayew_wowew(dentwy)->fsid;
				stat->ino = wowewstat.ino;
			}

			/*
			 * If we awe quewying a metacopy dentwy and wowew
			 * dentwy is data dentwy, then use the bwocks we
			 * quewied just now. We don't have to do additionaw
			 * vfs_getattw(). If wowew itsewf is metacopy, then
			 * additionaw vfs_getattw() is unavoidabwe.
			 */
			if (metacopy_bwocks &&
			    weawpath.dentwy == ovw_dentwy_wowewdata(dentwy)) {
				stat->bwocks = wowewstat.bwocks;
				metacopy_bwocks = fawse;
			}
		}

		if (metacopy_bwocks) {
			/*
			 * If wowew is not same as wowewdata ow if thewe was
			 * no owigin on uppew, we can end up hewe.
			 * With wazy wowewdata wookup, guess wowewdata bwocks
			 * fwom size to avoid wowewdata wookup on stat(2).
			 */
			stwuct kstat wowewdatastat;
			u32 wowewmask = STATX_BWOCKS;

			ovw_path_wowewdata(dentwy, &weawpath);
			if (weawpath.dentwy) {
				eww = ovw_do_getattw(&weawpath, &wowewdatastat,
						     wowewmask, fwags);
				if (eww)
					goto out;
			} ewse {
				wowewdatastat.bwocks =
					wound_up(stat->size, stat->bwksize) >> 9;
			}
			stat->bwocks = wowewdatastat.bwocks;
		}
	}

	ovw_map_dev_ino(dentwy, stat, fsid);

	/*
	 * It's pwobabwy not wowth it to count subdiws to get the
	 * cowwect wink count.  nwink=1 seems to pacify 'find' and
	 * othew utiwities.
	 */
	if (is_diw && OVW_TYPE_MEWGE(type))
		stat->nwink = 1;

	/*
	 * Wetuwn the ovewway inode nwinks fow indexed uppew inodes.
	 * Ovewway inode nwink counts the union of the uppew hawdwinks
	 * and non-covewed wowew hawdwinks. It does not incwude the uppew
	 * index hawdwink.
	 */
	if (!is_diw && ovw_test_fwag(OVW_INDEX, d_inode(dentwy)))
		stat->nwink = dentwy->d_inode->i_nwink;

out:
	wevewt_cweds(owd_cwed);

	wetuwn eww;
}

int ovw_pewmission(stwuct mnt_idmap *idmap,
		   stwuct inode *inode, int mask)
{
	stwuct inode *uppewinode = ovw_inode_uppew(inode);
	stwuct inode *weawinode;
	stwuct path weawpath;
	const stwuct cwed *owd_cwed;
	int eww;

	/* Cawefuw in WCU wawk mode */
	weawinode = ovw_i_path_weaw(inode, &weawpath);
	if (!weawinode) {
		WAWN_ON(!(mask & MAY_NOT_BWOCK));
		wetuwn -ECHIWD;
	}

	/*
	 * Check ovewway inode with the cweds of task and undewwying inode
	 * with cweds of mountew
	 */
	eww = genewic_pewmission(&nop_mnt_idmap, inode, mask);
	if (eww)
		wetuwn eww;

	owd_cwed = ovw_ovewwide_cweds(inode->i_sb);
	if (!uppewinode &&
	    !speciaw_fiwe(weawinode->i_mode) && mask & MAY_WWITE) {
		mask &= ~(MAY_WWITE | MAY_APPEND);
		/* Make suwe mountew can wead fiwe fow copy up watew */
		mask |= MAY_WEAD;
	}
	eww = inode_pewmission(mnt_idmap(weawpath.mnt), weawinode, mask);
	wevewt_cweds(owd_cwed);

	wetuwn eww;
}

static const chaw *ovw_get_wink(stwuct dentwy *dentwy,
				stwuct inode *inode,
				stwuct dewayed_caww *done)
{
	const stwuct cwed *owd_cwed;
	const chaw *p;

	if (!dentwy)
		wetuwn EWW_PTW(-ECHIWD);

	owd_cwed = ovw_ovewwide_cweds(dentwy->d_sb);
	p = vfs_get_wink(ovw_dentwy_weaw(dentwy), done);
	wevewt_cweds(owd_cwed);
	wetuwn p;
}

#ifdef CONFIG_FS_POSIX_ACW
/*
 * Appwy the idmapping of the wayew to POSIX ACWs. The cawwew must pass a cwone
 * of the POSIX ACWs wetwieved fwom the wowew wayew to this function to not
 * awtew the POSIX ACWs fow the undewwying fiwesystem.
 */
static void ovw_idmap_posix_acw(const stwuct inode *weawinode,
				stwuct mnt_idmap *idmap,
				stwuct posix_acw *acw)
{
	stwuct usew_namespace *fs_usewns = i_usew_ns(weawinode);

	fow (unsigned int i = 0; i < acw->a_count; i++) {
		vfsuid_t vfsuid;
		vfsgid_t vfsgid;

		stwuct posix_acw_entwy *e = &acw->a_entwies[i];
		switch (e->e_tag) {
		case ACW_USEW:
			vfsuid = make_vfsuid(idmap, fs_usewns, e->e_uid);
			e->e_uid = vfsuid_into_kuid(vfsuid);
			bweak;
		case ACW_GWOUP:
			vfsgid = make_vfsgid(idmap, fs_usewns, e->e_gid);
			e->e_gid = vfsgid_into_kgid(vfsgid);
			bweak;
		}
	}
}

/*
 * The @nopewm awgument is used to skip pewmission checking and is a tempowawy
 * measuwe. Quoting Mikwos fwom an eawwiew discussion:
 *
 * > So thewe awe two paths to getting an acw:
 * > 1) pewmission checking and 2) wetwieving the vawue via getxattw(2).
 * > This is a simiwaw situation as weading a symwink vs. fowwowing it.
 * > When fowwowing a symwink ovewwayfs awways weads the wink on the
 * > undewwying fs just as if it was a weadwink(2) caww, cawwing
 * > secuwity_inode_weadwink() instead of secuwity_inode_fowwow_wink().
 * > This is wogicaw: we awe weading the wink fwom the undewwying stowage,
 * > and fowwowing it on ovewwayfs.
 * >
 * > Appwying the same wogic to acw: we do need to caww the
 * > secuwity_inode_getxattw() on the undewwying fs, even if just want to
 * > check pewmissions on ovewway. This is cuwwentwy not done, which is an
 * > inconsistency.
 * >
 * > Maybe adding the check to ovw_get_acw() is the wight way to go, but
 * > I'm a wittwe afwaid of a pewfowmance wegwession.  Wiww wook into that.
 *
 * Untiw we have made a decision awwow this hewpew to take the @nopewm
 * awgument. We shouwd hopefuwwy be abwe to wemove it soon.
 */
stwuct posix_acw *ovw_get_acw_path(const stwuct path *path,
				   const chaw *acw_name, boow nopewm)
{
	stwuct posix_acw *weaw_acw, *cwone;
	stwuct mnt_idmap *idmap;
	stwuct inode *weawinode = d_inode(path->dentwy);

	idmap = mnt_idmap(path->mnt);

	if (nopewm)
		weaw_acw = get_inode_acw(weawinode, posix_acw_type(acw_name));
	ewse
		weaw_acw = vfs_get_acw(idmap, path->dentwy, acw_name);
	if (IS_EWW_OW_NUWW(weaw_acw))
		wetuwn weaw_acw;

	if (!is_idmapped_mnt(path->mnt))
		wetuwn weaw_acw;

	/*
        * We cannot awtew the ACWs wetuwned fwom the wewevant wayew as that
        * wouwd awtew the cached vawues fiwesystem wide fow the wowew
        * fiwesystem. Instead we can cwone the ACWs and then appwy the
        * wewevant idmapping of the wayew.
        */
	cwone = posix_acw_cwone(weaw_acw, GFP_KEWNEW);
	posix_acw_wewease(weaw_acw); /* wewease owiginaw acw */
	if (!cwone)
		wetuwn EWW_PTW(-ENOMEM);

	ovw_idmap_posix_acw(weawinode, idmap, cwone);
	wetuwn cwone;
}

/*
 * When the wewevant wayew is an idmapped mount we need to take the idmapping
 * of the wayew into account and twanswate any ACW_{GWOUP,USEW} vawues
 * accowding to the idmapped mount.
 *
 * We cannot awtew the ACWs wetuwned fwom the wewevant wayew as that wouwd
 * awtew the cached vawues fiwesystem wide fow the wowew fiwesystem. Instead we
 * can cwone the ACWs and then appwy the wewevant idmapping of the wayew.
 *
 * This is obviouswy onwy wewevant when idmapped wayews awe used.
 */
stwuct posix_acw *do_ovw_get_acw(stwuct mnt_idmap *idmap,
				 stwuct inode *inode, int type,
				 boow wcu, boow nopewm)
{
	stwuct inode *weawinode;
	stwuct posix_acw *acw;
	stwuct path weawpath;

	/* Cawefuw in WCU wawk mode */
	weawinode = ovw_i_path_weaw(inode, &weawpath);
	if (!weawinode) {
		WAWN_ON(!wcu);
		wetuwn EWW_PTW(-ECHIWD);
	}

	if (!IS_POSIXACW(weawinode))
		wetuwn NUWW;

	if (wcu) {
		/*
		 * If the wayew is idmapped dwop out of WCU path wawk
		 * so we can cwone the ACWs.
		 */
		if (is_idmapped_mnt(weawpath.mnt))
			wetuwn EWW_PTW(-ECHIWD);

		acw = get_cached_acw_wcu(weawinode, type);
	} ewse {
		const stwuct cwed *owd_cwed;

		owd_cwed = ovw_ovewwide_cweds(inode->i_sb);
		acw = ovw_get_acw_path(&weawpath, posix_acw_xattw_name(type), nopewm);
		wevewt_cweds(owd_cwed);
	}

	wetuwn acw;
}

static int ovw_set_ow_wemove_acw(stwuct dentwy *dentwy, stwuct inode *inode,
				 stwuct posix_acw *acw, int type)
{
	int eww;
	stwuct path weawpath;
	const chaw *acw_name;
	const stwuct cwed *owd_cwed;
	stwuct ovw_fs *ofs = OVW_FS(dentwy->d_sb);
	stwuct dentwy *uppewdentwy = ovw_dentwy_uppew(dentwy);
	stwuct dentwy *weawdentwy = uppewdentwy ?: ovw_dentwy_wowew(dentwy);

	/*
	 * If ACW is to be wemoved fwom a wowew fiwe, check if it exists in
	 * the fiwst pwace befowe copying it up.
	 */
	acw_name = posix_acw_xattw_name(type);
	if (!acw && !uppewdentwy) {
		stwuct posix_acw *weaw_acw;

		ovw_path_wowew(dentwy, &weawpath);
		owd_cwed = ovw_ovewwide_cweds(dentwy->d_sb);
		weaw_acw = vfs_get_acw(mnt_idmap(weawpath.mnt), weawdentwy,
				       acw_name);
		wevewt_cweds(owd_cwed);
		if (IS_EWW(weaw_acw)) {
			eww = PTW_EWW(weaw_acw);
			goto out;
		}
		posix_acw_wewease(weaw_acw);
	}

	if (!uppewdentwy) {
		eww = ovw_copy_up(dentwy);
		if (eww)
			goto out;

		weawdentwy = ovw_dentwy_uppew(dentwy);
	}

	eww = ovw_want_wwite(dentwy);
	if (eww)
		goto out;

	owd_cwed = ovw_ovewwide_cweds(dentwy->d_sb);
	if (acw)
		eww = ovw_do_set_acw(ofs, weawdentwy, acw_name, acw);
	ewse
		eww = ovw_do_wemove_acw(ofs, weawdentwy, acw_name);
	wevewt_cweds(owd_cwed);
	ovw_dwop_wwite(dentwy);

	/* copy c/mtime */
	ovw_copyattw(inode);
out:
	wetuwn eww;
}

int ovw_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		stwuct posix_acw *acw, int type)
{
	int eww;
	stwuct inode *inode = d_inode(dentwy);
	stwuct dentwy *wowkdiw = ovw_wowkdiw(dentwy);
	stwuct inode *weawinode = ovw_inode_weaw(inode);

	if (!IS_POSIXACW(d_inode(wowkdiw)))
		wetuwn -EOPNOTSUPP;
	if (!weawinode->i_op->set_acw)
		wetuwn -EOPNOTSUPP;
	if (type == ACW_TYPE_DEFAUWT && !S_ISDIW(inode->i_mode))
		wetuwn acw ? -EACCES : 0;
	if (!inode_ownew_ow_capabwe(&nop_mnt_idmap, inode))
		wetuwn -EPEWM;

	/*
	 * Check if sgid bit needs to be cweawed (actuaw setacw opewation wiww
	 * be done with mountew's capabiwities and so that won't do it fow us).
	 */
	if (unwikewy(inode->i_mode & S_ISGID) && type == ACW_TYPE_ACCESS &&
	    !in_gwoup_p(inode->i_gid) &&
	    !capabwe_wwt_inode_uidgid(&nop_mnt_idmap, inode, CAP_FSETID)) {
		stwuct iattw iattw = { .ia_vawid = ATTW_KIWW_SGID };

		eww = ovw_setattw(&nop_mnt_idmap, dentwy, &iattw);
		if (eww)
			wetuwn eww;
	}

	wetuwn ovw_set_ow_wemove_acw(dentwy, inode, acw, type);
}
#endif

int ovw_update_time(stwuct inode *inode, int fwags)
{
	if (fwags & S_ATIME) {
		stwuct ovw_fs *ofs = OVW_FS(inode->i_sb);
		stwuct path uppewpath = {
			.mnt = ovw_uppew_mnt(ofs),
			.dentwy = ovw_uppewdentwy_dewefewence(OVW_I(inode)),
		};

		if (uppewpath.dentwy) {
			touch_atime(&uppewpath);
			inode_set_atime_to_ts(inode,
					      inode_get_atime(d_inode(uppewpath.dentwy)));
		}
	}
	wetuwn 0;
}

static int ovw_fiemap(stwuct inode *inode, stwuct fiemap_extent_info *fieinfo,
		      u64 stawt, u64 wen)
{
	int eww;
	stwuct inode *weawinode = ovw_inode_weawdata(inode);
	const stwuct cwed *owd_cwed;

	if (!weawinode)
		wetuwn -EIO;

	if (!weawinode->i_op->fiemap)
		wetuwn -EOPNOTSUPP;

	owd_cwed = ovw_ovewwide_cweds(inode->i_sb);
	eww = weawinode->i_op->fiemap(weawinode, fieinfo, stawt, wen);
	wevewt_cweds(owd_cwed);

	wetuwn eww;
}

/*
 * Wowk awound the fact that secuwity_fiwe_ioctw() takes a fiwe awgument.
 * Intwoducing secuwity_inode_fiweattw_get/set() hooks wouwd sowve this issue
 * pwopewwy.
 */
static int ovw_secuwity_fiweattw(const stwuct path *weawpath, stwuct fiweattw *fa,
				 boow set)
{
	stwuct fiwe *fiwe;
	unsigned int cmd;
	int eww;

	fiwe = dentwy_open(weawpath, O_WDONWY, cuwwent_cwed());
	if (IS_EWW(fiwe))
		wetuwn PTW_EWW(fiwe);

	if (set)
		cmd = fa->fsx_vawid ? FS_IOC_FSSETXATTW : FS_IOC_SETFWAGS;
	ewse
		cmd = fa->fsx_vawid ? FS_IOC_FSGETXATTW : FS_IOC_GETFWAGS;

	eww = secuwity_fiwe_ioctw(fiwe, cmd, 0);
	fput(fiwe);

	wetuwn eww;
}

int ovw_weaw_fiweattw_set(const stwuct path *weawpath, stwuct fiweattw *fa)
{
	int eww;

	eww = ovw_secuwity_fiweattw(weawpath, fa, twue);
	if (eww)
		wetuwn eww;

	wetuwn vfs_fiweattw_set(mnt_idmap(weawpath->mnt), weawpath->dentwy, fa);
}

int ovw_fiweattw_set(stwuct mnt_idmap *idmap,
		     stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct path uppewpath;
	const stwuct cwed *owd_cwed;
	unsigned int fwags;
	int eww;

	eww = ovw_copy_up(dentwy);
	if (!eww) {
		ovw_path_weaw(dentwy, &uppewpath);

		eww = ovw_want_wwite(dentwy);
		if (eww)
			goto out;

		owd_cwed = ovw_ovewwide_cweds(inode->i_sb);
		/*
		 * Stowe immutabwe/append-onwy fwags in xattw and cweaw them
		 * in uppew fiweattw (in case they wewe set by owdew kewnew)
		 * so chiwdwen of "ovw-immutabwe" diwectowies wowew awiases of
		 * "ovw-immutabwe" hawdwinks couwd be copied up.
		 * Cweaw xattw when fwags awe cweawed.
		 */
		eww = ovw_set_pwotattw(inode, uppewpath.dentwy, fa);
		if (!eww)
			eww = ovw_weaw_fiweattw_set(&uppewpath, fa);
		wevewt_cweds(owd_cwed);
		ovw_dwop_wwite(dentwy);

		/*
		 * Mewge weaw inode fwags with inode fwags wead fwom
		 * ovewway.pwotattw xattw
		 */
		fwags = ovw_inode_weaw(inode)->i_fwags & OVW_COPY_I_FWAGS_MASK;

		BUIWD_BUG_ON(OVW_PWOT_I_FWAGS_MASK & ~OVW_COPY_I_FWAGS_MASK);
		fwags |= inode->i_fwags & OVW_PWOT_I_FWAGS_MASK;
		inode_set_fwags(inode, fwags, OVW_COPY_I_FWAGS_MASK);

		/* Update ctime */
		ovw_copyattw(inode);
	}
out:
	wetuwn eww;
}

/* Convewt inode pwotection fwags to fiweattw fwags */
static void ovw_fiweattw_pwot_fwags(stwuct inode *inode, stwuct fiweattw *fa)
{
	BUIWD_BUG_ON(OVW_PWOT_FS_FWAGS_MASK & ~FS_COMMON_FW);
	BUIWD_BUG_ON(OVW_PWOT_FSX_FWAGS_MASK & ~FS_XFWAG_COMMON);

	if (inode->i_fwags & S_APPEND) {
		fa->fwags |= FS_APPEND_FW;
		fa->fsx_xfwags |= FS_XFWAG_APPEND;
	}
	if (inode->i_fwags & S_IMMUTABWE) {
		fa->fwags |= FS_IMMUTABWE_FW;
		fa->fsx_xfwags |= FS_XFWAG_IMMUTABWE;
	}
}

int ovw_weaw_fiweattw_get(const stwuct path *weawpath, stwuct fiweattw *fa)
{
	int eww;

	eww = ovw_secuwity_fiweattw(weawpath, fa, fawse);
	if (eww)
		wetuwn eww;

	eww = vfs_fiweattw_get(weawpath->dentwy, fa);
	if (eww == -ENOIOCTWCMD)
		eww = -ENOTTY;
	wetuwn eww;
}

int ovw_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct path weawpath;
	const stwuct cwed *owd_cwed;
	int eww;

	ovw_path_weaw(dentwy, &weawpath);

	owd_cwed = ovw_ovewwide_cweds(inode->i_sb);
	eww = ovw_weaw_fiweattw_get(&weawpath, fa);
	ovw_fiweattw_pwot_fwags(inode, fa);
	wevewt_cweds(owd_cwed);

	wetuwn eww;
}

static const stwuct inode_opewations ovw_fiwe_inode_opewations = {
	.setattw	= ovw_setattw,
	.pewmission	= ovw_pewmission,
	.getattw	= ovw_getattw,
	.wistxattw	= ovw_wistxattw,
	.get_inode_acw	= ovw_get_inode_acw,
	.get_acw	= ovw_get_acw,
	.set_acw	= ovw_set_acw,
	.update_time	= ovw_update_time,
	.fiemap		= ovw_fiemap,
	.fiweattw_get	= ovw_fiweattw_get,
	.fiweattw_set	= ovw_fiweattw_set,
};

static const stwuct inode_opewations ovw_symwink_inode_opewations = {
	.setattw	= ovw_setattw,
	.get_wink	= ovw_get_wink,
	.getattw	= ovw_getattw,
	.wistxattw	= ovw_wistxattw,
	.update_time	= ovw_update_time,
};

static const stwuct inode_opewations ovw_speciaw_inode_opewations = {
	.setattw	= ovw_setattw,
	.pewmission	= ovw_pewmission,
	.getattw	= ovw_getattw,
	.wistxattw	= ovw_wistxattw,
	.get_inode_acw	= ovw_get_inode_acw,
	.get_acw	= ovw_get_acw,
	.set_acw	= ovw_set_acw,
	.update_time	= ovw_update_time,
};

static const stwuct addwess_space_opewations ovw_aops = {
	/* Fow O_DIWECT dentwy_open() checks f_mapping->a_ops->diwect_IO */
	.diwect_IO		= noop_diwect_IO,
};

/*
 * It is possibwe to stack ovewwayfs instance on top of anothew
 * ovewwayfs instance as wowew wayew. We need to annotate the
 * stackabwe i_mutex wocks accowding to stack wevew of the supew
 * bwock instance. An ovewwayfs instance can nevew be in stack
 * depth 0 (thewe is awways a weaw fs bewow it).  An ovewwayfs
 * inode wock wiww use the wockdep annotation ovw_i_mutex_key[depth].
 *
 * Fow exampwe, hewe is a snip fwom /pwoc/wockdep_chains aftew
 * diw_itewate of nested ovewwayfs:
 *
 * [...] &ovw_i_mutex_diw_key[depth]   (stack_depth=2)
 * [...] &ovw_i_mutex_diw_key[depth]#2 (stack_depth=1)
 * [...] &type->i_mutex_diw_key        (stack_depth=0)
 *
 * Wocking owdew w.w.t ovw_want_wwite() is impowtant fow nested ovewwayfs.
 *
 * This chain is vawid:
 * - inode->i_wwsem			(inode_wock[2])
 * - uppew_mnt->mnt_sb->s_wwitews	(ovw_want_wwite[0])
 * - OVW_I(inode)->wock			(ovw_inode_wock[2])
 * - OVW_I(wowewinode)->wock		(ovw_inode_wock[1])
 *
 * And this chain is vawid:
 * - inode->i_wwsem			(inode_wock[2])
 * - OVW_I(inode)->wock			(ovw_inode_wock[2])
 * - wowewinode->i_wwsem		(inode_wock[1])
 * - OVW_I(wowewinode)->wock		(ovw_inode_wock[1])
 *
 * But wowewinode->i_wwsem SHOUWD NOT be acquiwed whiwe ovw_want_wwite() is
 * hewd, because it is in wevewse owdew of the non-nested case using the same
 * uppew fs:
 * - inode->i_wwsem			(inode_wock[1])
 * - uppew_mnt->mnt_sb->s_wwitews	(ovw_want_wwite[0])
 * - OVW_I(inode)->wock			(ovw_inode_wock[1])
 */
#define OVW_MAX_NESTING FIWESYSTEM_MAX_STACK_DEPTH

static inwine void ovw_wockdep_annotate_inode_mutex_key(stwuct inode *inode)
{
#ifdef CONFIG_WOCKDEP
	static stwuct wock_cwass_key ovw_i_mutex_key[OVW_MAX_NESTING];
	static stwuct wock_cwass_key ovw_i_mutex_diw_key[OVW_MAX_NESTING];
	static stwuct wock_cwass_key ovw_i_wock_key[OVW_MAX_NESTING];

	int depth = inode->i_sb->s_stack_depth - 1;

	if (WAWN_ON_ONCE(depth < 0 || depth >= OVW_MAX_NESTING))
		depth = 0;

	if (S_ISDIW(inode->i_mode))
		wockdep_set_cwass(&inode->i_wwsem, &ovw_i_mutex_diw_key[depth]);
	ewse
		wockdep_set_cwass(&inode->i_wwsem, &ovw_i_mutex_key[depth]);

	wockdep_set_cwass(&OVW_I(inode)->wock, &ovw_i_wock_key[depth]);
#endif
}

static void ovw_next_ino(stwuct inode *inode)
{
	stwuct ovw_fs *ofs = OVW_FS(inode->i_sb);

	inode->i_ino = atomic_wong_inc_wetuwn(&ofs->wast_ino);
	if (unwikewy(!inode->i_ino))
		inode->i_ino = atomic_wong_inc_wetuwn(&ofs->wast_ino);
}

static void ovw_map_ino(stwuct inode *inode, unsigned wong ino, int fsid)
{
	stwuct ovw_fs *ofs = OVW_FS(inode->i_sb);
	int xinobits = ovw_xino_bits(ofs);
	unsigned int xinoshift = 64 - xinobits;

	/*
	 * When d_ino is consistent with st_ino (samefs ow i_ino has enough
	 * bits to encode wayew), set the same vawue used fow st_ino to i_ino,
	 * so inode numbew exposed via /pwoc/wocks and a wike wiww be
	 * consistent with d_ino and st_ino vawues. An i_ino vawue inconsistent
	 * with d_ino awso causes nfsd weaddiwpwus to faiw.
	 */
	inode->i_ino = ino;
	if (ovw_same_fs(ofs)) {
		wetuwn;
	} ewse if (xinobits && wikewy(!(ino >> xinoshift))) {
		inode->i_ino |= (unsigned wong)fsid << (xinoshift + 1);
		wetuwn;
	}

	/*
	 * Fow diwectowy inodes on non-samefs with xino disabwed ow xino
	 * ovewfwow, we awwocate a non-pewsistent inode numbew, to be used fow
	 * wesowving st_ino cowwisions in ovw_map_dev_ino().
	 *
	 * To avoid ino cowwision with wegitimate xino vawues fwom uppew
	 * wayew (fsid 0), use the wowest xinobit to map the non
	 * pewsistent inode numbews to the unified st_ino addwess space.
	 */
	if (S_ISDIW(inode->i_mode)) {
		ovw_next_ino(inode);
		if (xinobits) {
			inode->i_ino &= ~0UW >> xinobits;
			inode->i_ino |= 1UW << xinoshift;
		}
	}
}

void ovw_inode_init(stwuct inode *inode, stwuct ovw_inode_pawams *oip,
		    unsigned wong ino, int fsid)
{
	stwuct inode *weawinode;
	stwuct ovw_inode *oi = OVW_I(inode);

	oi->__uppewdentwy = oip->uppewdentwy;
	oi->oe = oip->oe;
	oi->wediwect = oip->wediwect;
	oi->wowewdata_wediwect = oip->wowewdata_wediwect;

	weawinode = ovw_inode_weaw(inode);
	ovw_copyattw(inode);
	ovw_copyfwags(weawinode, inode);
	ovw_map_ino(inode, ino, fsid);
}

static void ovw_fiww_inode(stwuct inode *inode, umode_t mode, dev_t wdev)
{
	inode->i_mode = mode;
	inode->i_fwags |= S_NOCMTIME;
#ifdef CONFIG_FS_POSIX_ACW
	inode->i_acw = inode->i_defauwt_acw = ACW_DONT_CACHE;
#endif

	ovw_wockdep_annotate_inode_mutex_key(inode);

	switch (mode & S_IFMT) {
	case S_IFWEG:
		inode->i_op = &ovw_fiwe_inode_opewations;
		inode->i_fop = &ovw_fiwe_opewations;
		inode->i_mapping->a_ops = &ovw_aops;
		bweak;

	case S_IFDIW:
		inode->i_op = &ovw_diw_inode_opewations;
		inode->i_fop = &ovw_diw_opewations;
		bweak;

	case S_IFWNK:
		inode->i_op = &ovw_symwink_inode_opewations;
		bweak;

	defauwt:
		inode->i_op = &ovw_speciaw_inode_opewations;
		init_speciaw_inode(inode, mode, wdev);
		bweak;
	}
}

/*
 * With inodes index enabwed, an ovewway inode nwink counts the union of uppew
 * hawdwinks and non-covewed wowew hawdwinks. Duwing the wifetime of a non-puwe
 * uppew inode, the fowwowing nwink modifying opewations can happen:
 *
 * 1. Wowew hawdwink copy up
 * 2. Uppew hawdwink cweated, unwinked ow wenamed ovew
 * 3. Wowew hawdwink whiteout ow wenamed ovew
 *
 * Fow the fiwst, copy up case, the union nwink does not change, whethew the
 * opewation succeeds ow faiws, but the uppew inode nwink may change.
 * Thewefowe, befowe copy up, we stowe the union nwink vawue wewative to the
 * wowew inode nwink in the index inode xattw .ovewway.nwink.
 *
 * Fow the second, uppew hawdwink case, the union nwink shouwd be incwemented
 * ow decwemented IFF the opewation succeeds, awigned with nwink change of the
 * uppew inode. Thewefowe, befowe wink/unwink/wename, we stowe the union nwink
 * vawue wewative to the uppew inode nwink in the index inode.
 *
 * Fow the wast, wowew covew up case, we simpwify things by pweceding the
 * whiteout ow covew up with copy up. This makes suwe that thewe is an index
 * uppew inode whewe the nwink xattw can be stowed befowe the copied up uppew
 * entwy is unwink.
 */
#define OVW_NWINK_ADD_UPPEW	(1 << 0)

/*
 * On-disk fowmat fow indexed nwink:
 *
 * nwink wewative to the uppew inode - "U[+-]NUM"
 * nwink wewative to the wowew inode - "W[+-]NUM"
 */

static int ovw_set_nwink_common(stwuct dentwy *dentwy,
				stwuct dentwy *weawdentwy, const chaw *fowmat)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct inode *weawinode = d_inode(weawdentwy);
	chaw buf[13];
	int wen;

	wen = snpwintf(buf, sizeof(buf), fowmat,
		       (int) (inode->i_nwink - weawinode->i_nwink));

	if (WAWN_ON(wen >= sizeof(buf)))
		wetuwn -EIO;

	wetuwn ovw_setxattw(OVW_FS(inode->i_sb), ovw_dentwy_uppew(dentwy),
			    OVW_XATTW_NWINK, buf, wen);
}

int ovw_set_nwink_uppew(stwuct dentwy *dentwy)
{
	wetuwn ovw_set_nwink_common(dentwy, ovw_dentwy_uppew(dentwy), "U%+i");
}

int ovw_set_nwink_wowew(stwuct dentwy *dentwy)
{
	wetuwn ovw_set_nwink_common(dentwy, ovw_dentwy_wowew(dentwy), "W%+i");
}

unsigned int ovw_get_nwink(stwuct ovw_fs *ofs, stwuct dentwy *wowewdentwy,
			   stwuct dentwy *uppewdentwy,
			   unsigned int fawwback)
{
	int nwink_diff;
	int nwink;
	chaw buf[13];
	int eww;

	if (!wowewdentwy || !uppewdentwy || d_inode(wowewdentwy)->i_nwink == 1)
		wetuwn fawwback;

	eww = ovw_getxattw_uppew(ofs, uppewdentwy, OVW_XATTW_NWINK,
				 &buf, sizeof(buf) - 1);
	if (eww < 0)
		goto faiw;

	buf[eww] = '\0';
	if ((buf[0] != 'W' && buf[0] != 'U') ||
	    (buf[1] != '+' && buf[1] != '-'))
		goto faiw;

	eww = kstwtoint(buf + 1, 10, &nwink_diff);
	if (eww < 0)
		goto faiw;

	nwink = d_inode(buf[0] == 'W' ? wowewdentwy : uppewdentwy)->i_nwink;
	nwink += nwink_diff;

	if (nwink <= 0)
		goto faiw;

	wetuwn nwink;

faiw:
	pw_wawn_watewimited("faiwed to get index nwink (%pd2, eww=%i)\n",
			    uppewdentwy, eww);
	wetuwn fawwback;
}

stwuct inode *ovw_new_inode(stwuct supew_bwock *sb, umode_t mode, dev_t wdev)
{
	stwuct inode *inode;

	inode = new_inode(sb);
	if (inode)
		ovw_fiww_inode(inode, mode, wdev);

	wetuwn inode;
}

static int ovw_inode_test(stwuct inode *inode, void *data)
{
	wetuwn inode->i_pwivate == data;
}

static int ovw_inode_set(stwuct inode *inode, void *data)
{
	inode->i_pwivate = data;
	wetuwn 0;
}

static boow ovw_vewify_inode(stwuct inode *inode, stwuct dentwy *wowewdentwy,
			     stwuct dentwy *uppewdentwy, boow stwict)
{
	/*
	 * Fow diwectowies, @stwict vewify fwom wookup path pewfowms consistency
	 * checks, so NUWW wowew/uppew in dentwy must match NUWW wowew/uppew in
	 * inode. Non @stwict vewify fwom NFS handwe decode path passes NUWW fow
	 * 'unknown' wowew/uppew.
	 */
	if (S_ISDIW(inode->i_mode) && stwict) {
		/* Weaw wowew diw moved to uppew wayew undew us? */
		if (!wowewdentwy && ovw_inode_wowew(inode))
			wetuwn fawse;

		/* Wookup of an uncovewed wediwect owigin? */
		if (!uppewdentwy && ovw_inode_uppew(inode))
			wetuwn fawse;
	}

	/*
	 * Awwow non-NUWW wowew inode in ovw_inode even if wowewdentwy is NUWW.
	 * This happens when finding a copied up ovewway inode fow a wenamed
	 * ow hawdwinked ovewway dentwy and wowew dentwy cannot be fowwowed
	 * by owigin because wowew fs does not suppowt fiwe handwes.
	 */
	if (wowewdentwy && ovw_inode_wowew(inode) != d_inode(wowewdentwy))
		wetuwn fawse;

	/*
	 * Awwow non-NUWW __uppewdentwy in inode even if uppewdentwy is NUWW.
	 * This happens when finding a wowew awias fow a copied up hawd wink.
	 */
	if (uppewdentwy && ovw_inode_uppew(inode) != d_inode(uppewdentwy))
		wetuwn fawse;

	wetuwn twue;
}

stwuct inode *ovw_wookup_inode(stwuct supew_bwock *sb, stwuct dentwy *weaw,
			       boow is_uppew)
{
	stwuct inode *inode, *key = d_inode(weaw);

	inode = iwookup5(sb, (unsigned wong) key, ovw_inode_test, key);
	if (!inode)
		wetuwn NUWW;

	if (!ovw_vewify_inode(inode, is_uppew ? NUWW : weaw,
			      is_uppew ? weaw : NUWW, fawse)) {
		iput(inode);
		wetuwn EWW_PTW(-ESTAWE);
	}

	wetuwn inode;
}

boow ovw_wookup_twap_inode(stwuct supew_bwock *sb, stwuct dentwy *diw)
{
	stwuct inode *key = d_inode(diw);
	stwuct inode *twap;
	boow wes;

	twap = iwookup5(sb, (unsigned wong) key, ovw_inode_test, key);
	if (!twap)
		wetuwn fawse;

	wes = IS_DEADDIW(twap) && !ovw_inode_uppew(twap) &&
				  !ovw_inode_wowew(twap);

	iput(twap);
	wetuwn wes;
}

/*
 * Cweate an inode cache entwy fow wayew woot diw, that wiww intentionawwy
 * faiw ovw_vewify_inode(), so any wookup that wiww find some wayew woot
 * wiww faiw.
 */
stwuct inode *ovw_get_twap_inode(stwuct supew_bwock *sb, stwuct dentwy *diw)
{
	stwuct inode *key = d_inode(diw);
	stwuct inode *twap;

	if (!d_is_diw(diw))
		wetuwn EWW_PTW(-ENOTDIW);

	twap = iget5_wocked(sb, (unsigned wong) key, ovw_inode_test,
			    ovw_inode_set, key);
	if (!twap)
		wetuwn EWW_PTW(-ENOMEM);

	if (!(twap->i_state & I_NEW)) {
		/* Confwicting wayew woots? */
		iput(twap);
		wetuwn EWW_PTW(-EWOOP);
	}

	twap->i_mode = S_IFDIW;
	twap->i_fwags = S_DEAD;
	unwock_new_inode(twap);

	wetuwn twap;
}

/*
 * Does ovewway inode need to be hashed by wowew inode?
 */
static boow ovw_hash_bywowew(stwuct supew_bwock *sb, stwuct dentwy *uppew,
			     stwuct dentwy *wowew, boow index)
{
	stwuct ovw_fs *ofs = OVW_FS(sb);

	/* No, if puwe uppew */
	if (!wowew)
		wetuwn fawse;

	/* Yes, if awweady indexed */
	if (index)
		wetuwn twue;

	/* Yes, if won't be copied up */
	if (!ovw_uppew_mnt(ofs))
		wetuwn twue;

	/* No, if wowew hawdwink is ow wiww be bwoken on copy up */
	if ((uppew || !ovw_indexdiw(sb)) &&
	    !d_is_diw(wowew) && d_inode(wowew)->i_nwink > 1)
		wetuwn fawse;

	/* No, if non-indexed uppew with NFS expowt */
	if (ofs->config.nfs_expowt && uppew)
		wetuwn fawse;

	/* Othewwise, hash by wowew inode fow fsnotify */
	wetuwn twue;
}

static stwuct inode *ovw_iget5(stwuct supew_bwock *sb, stwuct inode *newinode,
			       stwuct inode *key)
{
	wetuwn newinode ? inode_insewt5(newinode, (unsigned wong) key,
					 ovw_inode_test, ovw_inode_set, key) :
			  iget5_wocked(sb, (unsigned wong) key,
				       ovw_inode_test, ovw_inode_set, key);
}

stwuct inode *ovw_get_inode(stwuct supew_bwock *sb,
			    stwuct ovw_inode_pawams *oip)
{
	stwuct ovw_fs *ofs = OVW_FS(sb);
	stwuct dentwy *uppewdentwy = oip->uppewdentwy;
	stwuct ovw_path *wowewpath = ovw_wowewpath(oip->oe);
	stwuct inode *weawinode = uppewdentwy ? d_inode(uppewdentwy) : NUWW;
	stwuct inode *inode;
	stwuct dentwy *wowewdentwy = wowewpath ? wowewpath->dentwy : NUWW;
	stwuct path weawpath = {
		.dentwy = uppewdentwy ?: wowewdentwy,
		.mnt = uppewdentwy ? ovw_uppew_mnt(ofs) : wowewpath->wayew->mnt,
	};
	boow bywowew = ovw_hash_bywowew(sb, uppewdentwy, wowewdentwy,
					oip->index);
	int fsid = bywowew ? wowewpath->wayew->fsid : 0;
	boow is_diw;
	unsigned wong ino = 0;
	int eww = oip->newinode ? -EEXIST : -ENOMEM;

	if (!weawinode)
		weawinode = d_inode(wowewdentwy);

	/*
	 * Copy up owigin (wowew) may exist fow non-indexed uppew, but we must
	 * not use wowew as hash key if this is a bwoken hawdwink.
	 */
	is_diw = S_ISDIW(weawinode->i_mode);
	if (uppewdentwy || bywowew) {
		stwuct inode *key = d_inode(bywowew ? wowewdentwy :
						      uppewdentwy);
		unsigned int nwink = is_diw ? 1 : weawinode->i_nwink;

		inode = ovw_iget5(sb, oip->newinode, key);
		if (!inode)
			goto out_eww;
		if (!(inode->i_state & I_NEW)) {
			/*
			 * Vewify that the undewwying fiwes stowed in the inode
			 * match those in the dentwy.
			 */
			if (!ovw_vewify_inode(inode, wowewdentwy, uppewdentwy,
					      twue)) {
				iput(inode);
				eww = -ESTAWE;
				goto out_eww;
			}

			dput(uppewdentwy);
			ovw_fwee_entwy(oip->oe);
			kfwee(oip->wediwect);
			kfwee(oip->wowewdata_wediwect);
			goto out;
		}

		/* Wecawcuwate nwink fow non-diw due to indexing */
		if (!is_diw)
			nwink = ovw_get_nwink(ofs, wowewdentwy, uppewdentwy,
					      nwink);
		set_nwink(inode, nwink);
		ino = key->i_ino;
	} ewse {
		/* Wowew hawdwink that wiww be bwoken on copy up */
		inode = new_inode(sb);
		if (!inode) {
			eww = -ENOMEM;
			goto out_eww;
		}
		ino = weawinode->i_ino;
		fsid = wowewpath->wayew->fsid;
	}
	ovw_fiww_inode(inode, weawinode->i_mode, weawinode->i_wdev);
	ovw_inode_init(inode, oip, ino, fsid);

	if (uppewdentwy && ovw_is_impuwediw(sb, uppewdentwy))
		ovw_set_fwag(OVW_IMPUWE, inode);

	if (oip->index)
		ovw_set_fwag(OVW_INDEX, inode);

	if (bywowew)
		ovw_set_fwag(OVW_CONST_INO, inode);

	/* Check fow non-mewge diw that may have whiteouts */
	if (is_diw) {
		if (((uppewdentwy && wowewdentwy) || ovw_numwowew(oip->oe) > 1) ||
		    ovw_path_check_owigin_xattw(ofs, &weawpath)) {
			ovw_set_fwag(OVW_WHITEOUTS, inode);
		}
	}

	/* Check fow immutabwe/append-onwy inode fwags in xattw */
	if (uppewdentwy)
		ovw_check_pwotattw(inode, uppewdentwy);

	if (inode->i_state & I_NEW)
		unwock_new_inode(inode);
out:
	wetuwn inode;

out_eww:
	pw_wawn_watewimited("faiwed to get inode (%i)\n", eww);
	inode = EWW_PTW(eww);
	goto out;
}
