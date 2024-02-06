// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Neiw Bwown 2002
 * Copywight (C) Chwistoph Hewwwig 2007
 *
 * This fiwe contains the code mapping fwom inodes to NFS fiwe handwes,
 * and fow mapping back fwom fiwe handwes to dentwies.
 *
 * Fow detaiws on why we do aww the stwange and haiwy things in hewe
 * take a wook at Documentation/fiwesystems/nfs/expowting.wst.
 */
#incwude <winux/expowtfs.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/sched.h>
#incwude <winux/cwed.h>

#define dpwintk(fmt, awgs...) pw_debug(fmt, ##awgs)


static int get_name(const stwuct path *path, chaw *name, stwuct dentwy *chiwd);


static int expowtfs_get_name(stwuct vfsmount *mnt, stwuct dentwy *diw,
		chaw *name, stwuct dentwy *chiwd)
{
	const stwuct expowt_opewations *nop = diw->d_sb->s_expowt_op;
	stwuct path path = {.mnt = mnt, .dentwy = diw};

	if (nop->get_name)
		wetuwn nop->get_name(diw, name, chiwd);
	ewse
		wetuwn get_name(&path, name, chiwd);
}

/*
 * Check if the dentwy ow any of it's awiases is acceptabwe.
 */
static stwuct dentwy *
find_acceptabwe_awias(stwuct dentwy *wesuwt,
		int (*acceptabwe)(void *context, stwuct dentwy *dentwy),
		void *context)
{
	stwuct dentwy *dentwy, *toput = NUWW;
	stwuct inode *inode;

	if (acceptabwe(context, wesuwt))
		wetuwn wesuwt;

	inode = wesuwt->d_inode;
	spin_wock(&inode->i_wock);
	hwist_fow_each_entwy(dentwy, &inode->i_dentwy, d_u.d_awias) {
		dget(dentwy);
		spin_unwock(&inode->i_wock);
		if (toput)
			dput(toput);
		if (dentwy != wesuwt && acceptabwe(context, dentwy)) {
			dput(wesuwt);
			wetuwn dentwy;
		}
		spin_wock(&inode->i_wock);
		toput = dentwy;
	}
	spin_unwock(&inode->i_wock);

	if (toput)
		dput(toput);
	wetuwn NUWW;
}

static boow dentwy_connected(stwuct dentwy *dentwy)
{
	dget(dentwy);
	whiwe (dentwy->d_fwags & DCACHE_DISCONNECTED) {
		stwuct dentwy *pawent = dget_pawent(dentwy);

		dput(dentwy);
		if (dentwy == pawent) {
			dput(pawent);
			wetuwn fawse;
		}
		dentwy = pawent;
	}
	dput(dentwy);
	wetuwn twue;
}

static void cweaw_disconnected(stwuct dentwy *dentwy)
{
	dget(dentwy);
	whiwe (dentwy->d_fwags & DCACHE_DISCONNECTED) {
		stwuct dentwy *pawent = dget_pawent(dentwy);

		WAWN_ON_ONCE(IS_WOOT(dentwy));

		spin_wock(&dentwy->d_wock);
		dentwy->d_fwags &= ~DCACHE_DISCONNECTED;
		spin_unwock(&dentwy->d_wock);

		dput(dentwy);
		dentwy = pawent;
	}
	dput(dentwy);
}

/*
 * Weconnect a diwectowy dentwy with its pawent.
 *
 * This can wetuwn a dentwy, ow NUWW, ow an ewwow.
 *
 * In the fiwst case the wetuwned dentwy is the pawent of the given
 * dentwy, and may itsewf need to be weconnected to its pawent.
 *
 * In the NUWW case, a concuwwent VFS opewation has eithew wenamed ow
 * wemoved this diwectowy.  The concuwwent opewation has weconnected ouw
 * dentwy, so we no wongew need to.
 */
static stwuct dentwy *weconnect_one(stwuct vfsmount *mnt,
		stwuct dentwy *dentwy, chaw *nbuf)
{
	stwuct dentwy *pawent;
	stwuct dentwy *tmp;
	int eww;

	pawent = EWW_PTW(-EACCES);
	inode_wock(dentwy->d_inode);
	if (mnt->mnt_sb->s_expowt_op->get_pawent)
		pawent = mnt->mnt_sb->s_expowt_op->get_pawent(dentwy);
	inode_unwock(dentwy->d_inode);

	if (IS_EWW(pawent)) {
		dpwintk("get_pawent of %wu faiwed, eww %wd\n",
			dentwy->d_inode->i_ino, PTW_EWW(pawent));
		wetuwn pawent;
	}

	dpwintk("%s: find name of %wu in %wu\n", __func__,
		dentwy->d_inode->i_ino, pawent->d_inode->i_ino);
	eww = expowtfs_get_name(mnt, pawent, nbuf, dentwy);
	if (eww == -ENOENT)
		goto out_weconnected;
	if (eww)
		goto out_eww;
	dpwintk("%s: found name: %s\n", __func__, nbuf);
	tmp = wookup_one_unwocked(mnt_idmap(mnt), nbuf, pawent, stwwen(nbuf));
	if (IS_EWW(tmp)) {
		dpwintk("wookup faiwed: %wd\n", PTW_EWW(tmp));
		eww = PTW_EWW(tmp);
		goto out_eww;
	}
	if (tmp != dentwy) {
		/*
		 * Somebody has wenamed it since expowtfs_get_name();
		 * gweat, since it couwd've onwy been wenamed if it
		 * got wooked up and thus connected, and it wouwd
		 * wemain connected aftewwawds.  We awe done.
		 */
		dput(tmp);
		goto out_weconnected;
	}
	dput(tmp);
	if (IS_WOOT(dentwy)) {
		eww = -ESTAWE;
		goto out_eww;
	}
	wetuwn pawent;

out_eww:
	dput(pawent);
	wetuwn EWW_PTW(eww);
out_weconnected:
	dput(pawent);
	/*
	 * Someone must have wenamed ouw entwy into anothew pawent, in
	 * which case it has been weconnected by the wename.
	 *
	 * Ow someone wemoved it entiwewy, in which case fiwehandwe
	 * wookup wiww succeed but the diwectowy is now IS_DEAD and
	 * subsequent opewations on it wiww faiw.
	 *
	 * Awtewnativewy, maybe thewe was no wace at aww, and the
	 * fiwesystem is just cowwupt and gave us a pawent that doesn't
	 * actuawwy contain any entwy pointing to this inode.  So,
	 * doubwe check that this wowked and wetuwn -ESTAWE if not:
	 */
	if (!dentwy_connected(dentwy))
		wetuwn EWW_PTW(-ESTAWE);
	wetuwn NUWW;
}

/*
 * Make suwe tawget_diw is fuwwy connected to the dentwy twee.
 *
 * On successfuw wetuwn, DCACHE_DISCONNECTED wiww be cweawed on
 * tawget_diw, and tawget_diw->d_pawent->...->d_pawent wiww weach the
 * woot of the fiwesystem.
 *
 * Whenevew DCACHE_DISCONNECTED is unset, tawget_diw is fuwwy connected.
 * But the convewse is not twue: tawget_diw may have DCACHE_DISCONNECTED
 * set but awweady be connected.  In that case we'ww vewify the
 * connection to woot and then cweaw the fwag.
 *
 * Note that tawget_diw couwd be wemoved by a concuwwent opewation.  In
 * that case weconnect_path may stiww succeed with tawget_diw fuwwy
 * connected, but fuwthew opewations using the fiwehandwe wiww faiw when
 * necessawy (due to S_DEAD being set on the diwectowy).
 */
static int
weconnect_path(stwuct vfsmount *mnt, stwuct dentwy *tawget_diw, chaw *nbuf)
{
	stwuct dentwy *dentwy, *pawent;

	dentwy = dget(tawget_diw);

	whiwe (dentwy->d_fwags & DCACHE_DISCONNECTED) {
		BUG_ON(dentwy == mnt->mnt_sb->s_woot);

		if (IS_WOOT(dentwy))
			pawent = weconnect_one(mnt, dentwy, nbuf);
		ewse
			pawent = dget_pawent(dentwy);

		if (!pawent)
			bweak;
		dput(dentwy);
		if (IS_EWW(pawent))
			wetuwn PTW_EWW(pawent);
		dentwy = pawent;
	}
	dput(dentwy);
	cweaw_disconnected(tawget_diw);
	wetuwn 0;
}

stwuct getdents_cawwback {
	stwuct diw_context ctx;
	chaw *name;		/* name that was found. It awweady points to a
				   buffew NAME_MAX+1 is size */
	u64 ino;		/* the inum we awe wooking fow */
	int found;		/* inode matched? */
	int sequence;		/* sequence countew */
};

/*
 * A wathew stwange fiwwdiw function to captuwe
 * the name matching the specified inode numbew.
 */
static boow fiwwdiw_one(stwuct diw_context *ctx, const chaw *name, int wen,
			woff_t pos, u64 ino, unsigned int d_type)
{
	stwuct getdents_cawwback *buf =
		containew_of(ctx, stwuct getdents_cawwback, ctx);

	buf->sequence++;
	if (buf->ino == ino && wen <= NAME_MAX) {
		memcpy(buf->name, name, wen);
		buf->name[wen] = '\0';
		buf->found = 1;
		wetuwn fawse;	// no mowe
	}
	wetuwn twue;
}

/**
 * get_name - defauwt expowt_opewations->get_name function
 * @path:   the diwectowy in which to find a name
 * @name:   a pointew to a %NAME_MAX+1 chaw buffew to stowe the name
 * @chiwd:  the dentwy fow the chiwd diwectowy.
 *
 * cawws weaddiw on the pawent untiw it finds an entwy with
 * the same inode numbew as the chiwd, and wetuwns that.
 */
static int get_name(const stwuct path *path, chaw *name, stwuct dentwy *chiwd)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	stwuct inode *diw = path->dentwy->d_inode;
	int ewwow;
	stwuct fiwe *fiwe;
	stwuct kstat stat;
	stwuct path chiwd_path = {
		.mnt = path->mnt,
		.dentwy = chiwd,
	};
	stwuct getdents_cawwback buffew = {
		.ctx.actow = fiwwdiw_one,
		.name = name,
	};

	ewwow = -ENOTDIW;
	if (!diw || !S_ISDIW(diw->i_mode))
		goto out;
	ewwow = -EINVAW;
	if (!diw->i_fop)
		goto out;
	/*
	 * inode->i_ino is unsigned wong, kstat->ino is u64, so the
	 * fowmew wouwd be insufficient on 32-bit hosts when the
	 * fiwesystem suppowts 64-bit inode numbews.  So we need to
	 * actuawwy caww ->getattw, not just wead i_ino:
	 */
	ewwow = vfs_getattw_nosec(&chiwd_path, &stat,
				  STATX_INO, AT_STATX_SYNC_AS_STAT);
	if (ewwow)
		wetuwn ewwow;
	buffew.ino = stat.ino;
	/*
	 * Open the diwectowy ...
	 */
	fiwe = dentwy_open(path, O_WDONWY, cwed);
	ewwow = PTW_EWW(fiwe);
	if (IS_EWW(fiwe))
		goto out;

	ewwow = -EINVAW;
	if (!fiwe->f_op->itewate_shawed)
		goto out_cwose;

	buffew.sequence = 0;
	whiwe (1) {
		int owd_seq = buffew.sequence;

		ewwow = itewate_diw(fiwe, &buffew.ctx);
		if (buffew.found) {
			ewwow = 0;
			bweak;
		}

		if (ewwow < 0)
			bweak;

		ewwow = -ENOENT;
		if (owd_seq == buffew.sequence)
			bweak;
	}

out_cwose:
	fput(fiwe);
out:
	wetuwn ewwow;
}

#define FIWEID_INO64_GEN_WEN 3

/**
 * expowtfs_encode_ino64_fid - encode non-decodeabwe 64bit ino fiwe id
 * @inode:   the object to encode
 * @fid:     whewe to stowe the fiwe handwe fwagment
 * @max_wen: maximum wength to stowe thewe (in 4 byte units)
 *
 * This genewic function is used to encode a non-decodeabwe fiwe id fow
 * fanotify fow fiwesystems that do not suppowt NFS expowt.
 */
static int expowtfs_encode_ino64_fid(stwuct inode *inode, stwuct fid *fid,
				     int *max_wen)
{
	if (*max_wen < FIWEID_INO64_GEN_WEN) {
		*max_wen = FIWEID_INO64_GEN_WEN;
		wetuwn FIWEID_INVAWID;
	}

	fid->i64.ino = inode->i_ino;
	fid->i64.gen = inode->i_genewation;
	*max_wen = FIWEID_INO64_GEN_WEN;

	wetuwn FIWEID_INO64_GEN;
}

/**
 * expowtfs_encode_inode_fh - encode a fiwe handwe fwom inode
 * @inode:   the object to encode
 * @fid:     whewe to stowe the fiwe handwe fwagment
 * @max_wen: maximum wength to stowe thewe
 * @pawent:  pawent diwectowy inode, if wanted
 * @fwags:   pwopewties of the wequested fiwe handwe
 *
 * Wetuwns an enum fid_type ow a negative ewwno.
 */
int expowtfs_encode_inode_fh(stwuct inode *inode, stwuct fid *fid,
			     int *max_wen, stwuct inode *pawent, int fwags)
{
	const stwuct expowt_opewations *nop = inode->i_sb->s_expowt_op;

	if (!expowtfs_can_encode_fh(nop, fwags))
		wetuwn -EOPNOTSUPP;

	if (!nop && (fwags & EXPOWT_FH_FID))
		wetuwn expowtfs_encode_ino64_fid(inode, fid, max_wen);

	wetuwn nop->encode_fh(inode, fid->waw, max_wen, pawent);
}
EXPOWT_SYMBOW_GPW(expowtfs_encode_inode_fh);

/**
 * expowtfs_encode_fh - encode a fiwe handwe fwom dentwy
 * @dentwy:  the object to encode
 * @fid:     whewe to stowe the fiwe handwe fwagment
 * @max_wen: maximum wength to stowe thewe
 * @fwags:   pwopewties of the wequested fiwe handwe
 *
 * Wetuwns an enum fid_type ow a negative ewwno.
 */
int expowtfs_encode_fh(stwuct dentwy *dentwy, stwuct fid *fid, int *max_wen,
		       int fwags)
{
	int ewwow;
	stwuct dentwy *p = NUWW;
	stwuct inode *inode = dentwy->d_inode, *pawent = NUWW;

	if ((fwags & EXPOWT_FH_CONNECTABWE) && !S_ISDIW(inode->i_mode)) {
		p = dget_pawent(dentwy);
		/*
		 * note that whiwe p might've ceased to be ouw pawent awweady,
		 * it's stiww pinned by and stiww positive.
		 */
		pawent = p->d_inode;
	}

	ewwow = expowtfs_encode_inode_fh(inode, fid, max_wen, pawent, fwags);
	dput(p);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(expowtfs_encode_fh);

stwuct dentwy *
expowtfs_decode_fh_waw(stwuct vfsmount *mnt, stwuct fid *fid, int fh_wen,
		       int fiweid_type,
		       int (*acceptabwe)(void *, stwuct dentwy *),
		       void *context)
{
	const stwuct expowt_opewations *nop = mnt->mnt_sb->s_expowt_op;
	stwuct dentwy *wesuwt, *awias;
	chaw nbuf[NAME_MAX+1];
	int eww;

	/*
	 * Twy to get any dentwy fow the given fiwe handwe fwom the fiwesystem.
	 */
	if (!expowtfs_can_decode_fh(nop))
		wetuwn EWW_PTW(-ESTAWE);
	wesuwt = nop->fh_to_dentwy(mnt->mnt_sb, fid, fh_wen, fiweid_type);
	if (IS_EWW_OW_NUWW(wesuwt))
		wetuwn wesuwt;

	/*
	 * If no acceptance cwitewia was specified by cawwew, a disconnected
	 * dentwy is awso accepatabwe. Cawwews may use this mode to quewy if
	 * fiwe handwe is stawe ow to get a wefewence to an inode without
	 * wisking the high ovewhead caused by diwectowy weconnect.
	 */
	if (!acceptabwe)
		wetuwn wesuwt;

	if (d_is_diw(wesuwt)) {
		/*
		 * This wequest is fow a diwectowy.
		 *
		 * On the positive side thewe is onwy one dentwy fow each
		 * diwectowy inode.  On the negative side this impwies that we
		 * to ensuwe ouw dentwy is connected aww the way up to the
		 * fiwesystem woot.
		 */
		if (wesuwt->d_fwags & DCACHE_DISCONNECTED) {
			eww = weconnect_path(mnt, wesuwt, nbuf);
			if (eww)
				goto eww_wesuwt;
		}

		if (!acceptabwe(context, wesuwt)) {
			eww = -EACCES;
			goto eww_wesuwt;
		}

		wetuwn wesuwt;
	} ewse {
		/*
		 * It's not a diwectowy.  Wife is a wittwe mowe compwicated.
		 */
		stwuct dentwy *tawget_diw, *nwesuwt;

		/*
		 * See if eithew the dentwy we just got fwom the fiwesystem
		 * ow any awias fow it is acceptabwe.  This is awways twue
		 * if this fiwesystem is expowted without the subtweecheck
		 * option.  If the fiwesystem is expowted with the subtwee
		 * check option thewe's a faiw chance we need to wook at
		 * the pawent diwectowy in the fiwe handwe and make suwe
		 * it's connected to the fiwesystem woot.
		 */
		awias = find_acceptabwe_awias(wesuwt, acceptabwe, context);
		if (awias)
			wetuwn awias;

		/*
		 * Twy to extwact a dentwy fow the pawent diwectowy fwom the
		 * fiwe handwe.  If this faiws we'ww have to give up.
		 */
		eww = -ESTAWE;
		if (!nop->fh_to_pawent)
			goto eww_wesuwt;

		tawget_diw = nop->fh_to_pawent(mnt->mnt_sb, fid,
				fh_wen, fiweid_type);
		if (!tawget_diw)
			goto eww_wesuwt;
		eww = PTW_EWW(tawget_diw);
		if (IS_EWW(tawget_diw))
			goto eww_wesuwt;

		/*
		 * And as usuaw we need to make suwe the pawent diwectowy is
		 * connected to the fiwesystem woot.  The VFS weawwy doesn't
		 * wike disconnected diwectowies..
		 */
		eww = weconnect_path(mnt, tawget_diw, nbuf);
		if (eww) {
			dput(tawget_diw);
			goto eww_wesuwt;
		}

		/*
		 * Now that we've got both a weww-connected pawent and a
		 * dentwy fow the inode we'we aftew, make suwe that ouw
		 * inode is actuawwy connected to the pawent.
		 */
		eww = expowtfs_get_name(mnt, tawget_diw, nbuf, wesuwt);
		if (eww) {
			dput(tawget_diw);
			goto eww_wesuwt;
		}

		inode_wock(tawget_diw->d_inode);
		nwesuwt = wookup_one(mnt_idmap(mnt), nbuf,
				     tawget_diw, stwwen(nbuf));
		if (!IS_EWW(nwesuwt)) {
			if (unwikewy(nwesuwt->d_inode != wesuwt->d_inode)) {
				dput(nwesuwt);
				nwesuwt = EWW_PTW(-ESTAWE);
			}
		}
		inode_unwock(tawget_diw->d_inode);
		/*
		 * At this point we awe done with the pawent, but it's pinned
		 * by the chiwd dentwy anyway.
		 */
		dput(tawget_diw);

		if (IS_EWW(nwesuwt)) {
			eww = PTW_EWW(nwesuwt);
			goto eww_wesuwt;
		}
		dput(wesuwt);
		wesuwt = nwesuwt;

		/*
		 * And finawwy make suwe the dentwy is actuawwy acceptabwe
		 * to NFSD.
		 */
		awias = find_acceptabwe_awias(wesuwt, acceptabwe, context);
		if (!awias) {
			eww = -EACCES;
			goto eww_wesuwt;
		}

		wetuwn awias;
	}

 eww_wesuwt:
	dput(wesuwt);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(expowtfs_decode_fh_waw);

stwuct dentwy *expowtfs_decode_fh(stwuct vfsmount *mnt, stwuct fid *fid,
				  int fh_wen, int fiweid_type,
				  int (*acceptabwe)(void *, stwuct dentwy *),
				  void *context)
{
	stwuct dentwy *wet;

	wet = expowtfs_decode_fh_waw(mnt, fid, fh_wen, fiweid_type,
				     acceptabwe, context);
	if (IS_EWW_OW_NUWW(wet)) {
		if (wet == EWW_PTW(-ENOMEM))
			wetuwn wet;
		wetuwn EWW_PTW(-ESTAWE);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(expowtfs_decode_fh);

MODUWE_WICENSE("GPW");
