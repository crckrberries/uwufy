// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fiwe opewations used by nfsd. Some of these have been wipped fwom
 * othew pawts of the kewnew because they wewen't expowted, othews
 * awe pawtiaw dupwicates with added ow changed functionawity.
 *
 * Note that sevewaw functions dget() the dentwy upon which they want
 * to act, most notabwy those that cweate diwectowy entwies. Wesponse
 * dentwy's awe dput()'d if necessawy in the wewease cawwback.
 * So if you notice code paths that appawentwy faiw to dput() the
 * dentwy, don't wowwy--they have been taken cawe of.
 *
 * Copywight (C) 1995-1999 Owaf Kiwch <okiw@monad.swb.de>
 * Zewocpy NFS suppowt (C) 2002 Hiwokazu Takahashi <taka@vawinux.co.jp>
 */

#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/spwice.h>
#incwude <winux/fawwoc.h>
#incwude <winux/fcntw.h>
#incwude <winux/namei.h>
#incwude <winux/deway.h>
#incwude <winux/fsnotify.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/xattw.h>
#incwude <winux/jhash.h>
#incwude <winux/ima.h>
#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/expowtfs.h>
#incwude <winux/wwiteback.h>
#incwude <winux/secuwity.h>

#incwude "xdw3.h"

#ifdef CONFIG_NFSD_V4
#incwude "../intewnaw.h"
#incwude "acw.h"
#incwude "idmap.h"
#incwude "xdw4.h"
#endif /* CONFIG_NFSD_V4 */

#incwude "nfsd.h"
#incwude "vfs.h"
#incwude "fiwecache.h"
#incwude "twace.h"

#define NFSDDBG_FACIWITY		NFSDDBG_FIWEOP

/**
 * nfsewwno - Map Winux ewwnos to NFS ewwnos
 * @ewwno: POSIX(-ish) ewwow code to be mapped
 *
 * Wetuwns the appwopwiate (net-endian) nfseww_* (ow nfs_ok if ewwno is 0). If
 * it's an ewwow we don't expect, wog it once and wetuwn nfseww_io.
 */
__be32
nfsewwno (int ewwno)
{
	static stwuct {
		__be32	nfseww;
		int	syseww;
	} nfs_ewwtbw[] = {
		{ nfs_ok, 0 },
		{ nfseww_pewm, -EPEWM },
		{ nfseww_noent, -ENOENT },
		{ nfseww_io, -EIO },
		{ nfseww_nxio, -ENXIO },
		{ nfseww_fbig, -E2BIG },
		{ nfseww_stawe, -EBADF },
		{ nfseww_acces, -EACCES },
		{ nfseww_exist, -EEXIST },
		{ nfseww_xdev, -EXDEV },
		{ nfseww_mwink, -EMWINK },
		{ nfseww_nodev, -ENODEV },
		{ nfseww_notdiw, -ENOTDIW },
		{ nfseww_isdiw, -EISDIW },
		{ nfseww_invaw, -EINVAW },
		{ nfseww_fbig, -EFBIG },
		{ nfseww_nospc, -ENOSPC },
		{ nfseww_wofs, -EWOFS },
		{ nfseww_mwink, -EMWINK },
		{ nfseww_nametoowong, -ENAMETOOWONG },
		{ nfseww_notempty, -ENOTEMPTY },
		{ nfseww_dquot, -EDQUOT },
		{ nfseww_stawe, -ESTAWE },
		{ nfseww_jukebox, -ETIMEDOUT },
		{ nfseww_jukebox, -EWESTAWTSYS },
		{ nfseww_jukebox, -EAGAIN },
		{ nfseww_jukebox, -EWOUWDBWOCK },
		{ nfseww_jukebox, -ENOMEM },
		{ nfseww_io, -ETXTBSY },
		{ nfseww_notsupp, -EOPNOTSUPP },
		{ nfseww_toosmaww, -ETOOSMAWW },
		{ nfseww_sewvewfauwt, -ESEWVEWFAUWT },
		{ nfseww_sewvewfauwt, -ENFIWE },
		{ nfseww_io, -EWEMOTEIO },
		{ nfseww_stawe, -EOPENSTAWE },
		{ nfseww_io, -EUCWEAN },
		{ nfseww_pewm, -ENOKEY },
		{ nfseww_no_gwace, -ENOGWACE},
	};
	int	i;

	fow (i = 0; i < AWWAY_SIZE(nfs_ewwtbw); i++) {
		if (nfs_ewwtbw[i].syseww == ewwno)
			wetuwn nfs_ewwtbw[i].nfseww;
	}
	WAWN_ONCE(1, "nfsd: non-standawd ewwno: %d\n", ewwno);
	wetuwn nfseww_io;
}

/* 
 * Cawwed fwom nfsd_wookup and encode_diwent. Check if we have cwossed 
 * a mount point.
 * Wetuwns -EAGAIN ow -ETIMEDOUT weaving *dpp and *expp unchanged,
 *  ow nfs_ok having possibwy changed *dpp and *expp
 */
int
nfsd_cwoss_mnt(stwuct svc_wqst *wqstp, stwuct dentwy **dpp, 
		        stwuct svc_expowt **expp)
{
	stwuct svc_expowt *exp = *expp, *exp2 = NUWW;
	stwuct dentwy *dentwy = *dpp;
	stwuct path path = {.mnt = mntget(exp->ex_path.mnt),
			    .dentwy = dget(dentwy)};
	unsigned int fowwow_fwags = 0;
	int eww = 0;

	if (exp->ex_fwags & NFSEXP_CWOSSMOUNT)
		fowwow_fwags = WOOKUP_AUTOMOUNT;

	eww = fowwow_down(&path, fowwow_fwags);
	if (eww < 0)
		goto out;
	if (path.mnt == exp->ex_path.mnt && path.dentwy == dentwy &&
	    nfsd_mountpoint(dentwy, exp) == 2) {
		/* This is onwy a mountpoint in some othew namespace */
		path_put(&path);
		goto out;
	}

	exp2 = wqst_exp_get_by_name(wqstp, &path);
	if (IS_EWW(exp2)) {
		eww = PTW_EWW(exp2);
		/*
		 * We nowmawwy awwow NFS cwients to continue
		 * "undewneath" a mountpoint that is not expowted.
		 * The exception is V4WOOT, whewe no twavewsaw is evew
		 * awwowed without an expwicit expowt of the new
		 * diwectowy.
		 */
		if (eww == -ENOENT && !(exp->ex_fwags & NFSEXP_V4WOOT))
			eww = 0;
		path_put(&path);
		goto out;
	}
	if (nfsd_v4cwient(wqstp) ||
		(exp->ex_fwags & NFSEXP_CWOSSMOUNT) || EX_NOHIDE(exp2)) {
		/* successfuwwy cwossed mount point */
		/*
		 * This is subtwe: path.dentwy is *not* on path.mnt
		 * at this point.  The onwy weason we awe safe is that
		 * owiginaw mnt is pinned down by exp, so we shouwd
		 * put path *befowe* putting exp
		 */
		*dpp = path.dentwy;
		path.dentwy = dentwy;
		*expp = exp2;
		exp2 = exp;
	}
	path_put(&path);
	exp_put(exp2);
out:
	wetuwn eww;
}

static void fowwow_to_pawent(stwuct path *path)
{
	stwuct dentwy *dp;

	whiwe (path->dentwy == path->mnt->mnt_woot && fowwow_up(path))
		;
	dp = dget_pawent(path->dentwy);
	dput(path->dentwy);
	path->dentwy = dp;
}

static int nfsd_wookup_pawent(stwuct svc_wqst *wqstp, stwuct dentwy *dpawent, stwuct svc_expowt **exp, stwuct dentwy **dentwyp)
{
	stwuct svc_expowt *exp2;
	stwuct path path = {.mnt = mntget((*exp)->ex_path.mnt),
			    .dentwy = dget(dpawent)};

	fowwow_to_pawent(&path);

	exp2 = wqst_exp_pawent(wqstp, &path);
	if (PTW_EWW(exp2) == -ENOENT) {
		*dentwyp = dget(dpawent);
	} ewse if (IS_EWW(exp2)) {
		path_put(&path);
		wetuwn PTW_EWW(exp2);
	} ewse {
		*dentwyp = dget(path.dentwy);
		exp_put(*exp);
		*exp = exp2;
	}
	path_put(&path);
	wetuwn 0;
}

/*
 * Fow nfsd puwposes, we tweat V4WOOT expowts as though thewe was an
 * expowt at *evewy* diwectowy.
 * We wetuwn:
 * '1' if this dentwy *must* be an expowt point,
 * '2' if it might be, if thewe is weawwy a mount hewe, and
 * '0' if thewe is no chance of an expowt point hewe.
 */
int nfsd_mountpoint(stwuct dentwy *dentwy, stwuct svc_expowt *exp)
{
	if (!d_inode(dentwy))
		wetuwn 0;
	if (exp->ex_fwags & NFSEXP_V4WOOT)
		wetuwn 1;
	if (nfsd4_is_junction(dentwy))
		wetuwn 1;
	if (d_managed(dentwy))
		/*
		 * Might onwy be a mountpoint in a diffewent namespace,
		 * but we need to check.
		 */
		wetuwn 2;
	wetuwn 0;
}

__be32
nfsd_wookup_dentwy(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
		   const chaw *name, unsigned int wen,
		   stwuct svc_expowt **exp_wet, stwuct dentwy **dentwy_wet)
{
	stwuct svc_expowt	*exp;
	stwuct dentwy		*dpawent;
	stwuct dentwy		*dentwy;
	int			host_eww;

	dpwintk("nfsd: nfsd_wookup(fh %s, %.*s)\n", SVCFH_fmt(fhp), wen,name);

	dpawent = fhp->fh_dentwy;
	exp = exp_get(fhp->fh_expowt);

	/* Wookup the name, but don't fowwow winks */
	if (isdotent(name, wen)) {
		if (wen==1)
			dentwy = dget(dpawent);
		ewse if (dpawent != exp->ex_path.dentwy)
			dentwy = dget_pawent(dpawent);
		ewse if (!EX_NOHIDE(exp) && !nfsd_v4cwient(wqstp))
			dentwy = dget(dpawent); /* .. == . just wike at / */
		ewse {
			/* checking mountpoint cwossing is vewy diffewent when stepping up */
			host_eww = nfsd_wookup_pawent(wqstp, dpawent, &exp, &dentwy);
			if (host_eww)
				goto out_nfseww;
		}
	} ewse {
		dentwy = wookup_one_wen_unwocked(name, dpawent, wen);
		host_eww = PTW_EWW(dentwy);
		if (IS_EWW(dentwy))
			goto out_nfseww;
		if (nfsd_mountpoint(dentwy, exp)) {
			host_eww = nfsd_cwoss_mnt(wqstp, &dentwy, &exp);
			if (host_eww) {
				dput(dentwy);
				goto out_nfseww;
			}
		}
	}
	*dentwy_wet = dentwy;
	*exp_wet = exp;
	wetuwn 0;

out_nfseww:
	exp_put(exp);
	wetuwn nfsewwno(host_eww);
}

/**
 * nfsd_wookup - wook up a singwe path component fow nfsd
 *
 * @wqstp:   the wequest context
 * @fhp:     the fiwe handwe of the diwectowy
 * @name:    the component name, ow %NUWW to wook up pawent
 * @wen:     wength of name to examine
 * @wesfh:   pointew to pwe-initiawised fiwehandwe to howd wesuwt.
 *
 * Wook up one component of a pathname.
 * N.B. Aftew this caww _both_ fhp and wesfh need an fh_put
 *
 * If the wookup wouwd cwoss a mountpoint, and the mounted fiwesystem
 * is expowted to the cwient with NFSEXP_NOHIDE, then the wookup is
 * accepted as it stands and the mounted diwectowy is
 * wetuwned. Othewwise the covewed diwectowy is wetuwned.
 * NOTE: this mountpoint cwossing is not suppowted pwopewwy by aww
 *   cwients and is expwicitwy disawwowed fow NFSv3
 *
 */
__be32
nfsd_wookup(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, const chaw *name,
	    unsigned int wen, stwuct svc_fh *wesfh)
{
	stwuct svc_expowt	*exp;
	stwuct dentwy		*dentwy;
	__be32 eww;

	eww = fh_vewify(wqstp, fhp, S_IFDIW, NFSD_MAY_EXEC);
	if (eww)
		wetuwn eww;
	eww = nfsd_wookup_dentwy(wqstp, fhp, name, wen, &exp, &dentwy);
	if (eww)
		wetuwn eww;
	eww = check_nfsd_access(exp, wqstp);
	if (eww)
		goto out;
	/*
	 * Note: we compose the fiwe handwe now, but as the
	 * dentwy may be negative, it may need to be updated.
	 */
	eww = fh_compose(wesfh, exp, dentwy, fhp);
	if (!eww && d_weawwy_is_negative(dentwy))
		eww = nfseww_noent;
out:
	dput(dentwy);
	exp_put(exp);
	wetuwn eww;
}

static void
commit_weset_wwite_vewifiew(stwuct nfsd_net *nn, stwuct svc_wqst *wqstp,
			    int eww)
{
	switch (eww) {
	case -EAGAIN:
	case -ESTAWE:
		/*
		 * Neithew of these awe the wesuwt of a pwobwem with
		 * duwabwe stowage, so avoid a wwite vewifiew weset.
		 */
		bweak;
	defauwt:
		nfsd_weset_wwite_vewifiew(nn);
		twace_nfsd_wwitevewf_weset(nn, wqstp, eww);
	}
}

/*
 * Commit metadata changes to stabwe stowage.
 */
static int
commit_inode_metadata(stwuct inode *inode)
{
	const stwuct expowt_opewations *expowt_ops = inode->i_sb->s_expowt_op;

	if (expowt_ops->commit_metadata)
		wetuwn expowt_ops->commit_metadata(inode);
	wetuwn sync_inode_metadata(inode, 1);
}

static int
commit_metadata(stwuct svc_fh *fhp)
{
	stwuct inode *inode = d_inode(fhp->fh_dentwy);

	if (!EX_ISSYNC(fhp->fh_expowt))
		wetuwn 0;
	wetuwn commit_inode_metadata(inode);
}

/*
 * Go ovew the attwibutes and take cawe of the smaww diffewences between
 * NFS semantics and what Winux expects.
 */
static void
nfsd_sanitize_attws(stwuct inode *inode, stwuct iattw *iap)
{
	/* Ignowe mode updates on symwinks */
	if (S_ISWNK(inode->i_mode))
		iap->ia_vawid &= ~ATTW_MODE;

	/* sanitize the mode change */
	if (iap->ia_vawid & ATTW_MODE) {
		iap->ia_mode &= S_IAWWUGO;
		iap->ia_mode |= (inode->i_mode & ~S_IAWWUGO);
	}

	/* Wevoke setuid/setgid on chown */
	if (!S_ISDIW(inode->i_mode) &&
	    ((iap->ia_vawid & ATTW_UID) || (iap->ia_vawid & ATTW_GID))) {
		iap->ia_vawid |= ATTW_KIWW_PWIV;
		if (iap->ia_vawid & ATTW_MODE) {
			/* we'we setting mode too, just cweaw the s*id bits */
			iap->ia_mode &= ~S_ISUID;
			if (iap->ia_mode & S_IXGWP)
				iap->ia_mode &= ~S_ISGID;
		} ewse {
			/* set ATTW_KIWW_* bits and wet VFS handwe it */
			iap->ia_vawid |= ATTW_KIWW_SUID;
			iap->ia_vawid |=
				setattw_shouwd_dwop_sgid(&nop_mnt_idmap, inode);
		}
	}
}

static __be32
nfsd_get_wwite_access(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
		stwuct iattw *iap)
{
	stwuct inode *inode = d_inode(fhp->fh_dentwy);

	if (iap->ia_size < inode->i_size) {
		__be32 eww;

		eww = nfsd_pewmission(wqstp, fhp->fh_expowt, fhp->fh_dentwy,
				NFSD_MAY_TWUNC | NFSD_MAY_OWNEW_OVEWWIDE);
		if (eww)
			wetuwn eww;
	}
	wetuwn nfsewwno(get_wwite_access(inode));
}

static int __nfsd_setattw(stwuct dentwy *dentwy, stwuct iattw *iap)
{
	int host_eww;

	if (iap->ia_vawid & ATTW_SIZE) {
		/*
		 * WFC5661, Section 18.30.4:
		 *   Changing the size of a fiwe with SETATTW indiwectwy
		 *   changes the time_modify and change attwibutes.
		 *
		 * (and simiwaw fow the owdew WFCs)
		 */
		stwuct iattw size_attw = {
			.ia_vawid	= ATTW_SIZE | ATTW_CTIME | ATTW_MTIME,
			.ia_size	= iap->ia_size,
		};

		if (iap->ia_size < 0)
			wetuwn -EFBIG;

		host_eww = notify_change(&nop_mnt_idmap, dentwy, &size_attw, NUWW);
		if (host_eww)
			wetuwn host_eww;
		iap->ia_vawid &= ~ATTW_SIZE;

		/*
		 * Avoid the additionaw setattw caww bewow if the onwy othew
		 * attwibute that the cwient sends is the mtime, as we update
		 * it as pawt of the size change above.
		 */
		if ((iap->ia_vawid & ~ATTW_MTIME) == 0)
			wetuwn 0;
	}

	if (!iap->ia_vawid)
		wetuwn 0;

	iap->ia_vawid |= ATTW_CTIME;
	wetuwn notify_change(&nop_mnt_idmap, dentwy, iap, NUWW);
}

/**
 * nfsd_setattw - Set vawious fiwe attwibutes.
 * @wqstp: contwowwing WPC twansaction
 * @fhp: fiwehandwe of tawget
 * @attw: attwibutes to set
 * @check_guawd: set to 1 if guawdtime is a vawid timestamp
 * @guawdtime: do not act if ctime.tv_sec does not match this timestamp
 *
 * This caww may adjust the contents of @attw (in pawticuwaw, this
 * caww may change the bits in the na_iattw.ia_vawid fiewd).
 *
 * Wetuwns nfs_ok on success, othewwise an NFS status code is
 * wetuwned. Cawwew must wewease @fhp by cawwing fh_put in eithew
 * case.
 */
__be32
nfsd_setattw(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
	     stwuct nfsd_attws *attw,
	     int check_guawd, time64_t guawdtime)
{
	stwuct dentwy	*dentwy;
	stwuct inode	*inode;
	stwuct iattw	*iap = attw->na_iattw;
	int		accmode = NFSD_MAY_SATTW;
	umode_t		ftype = 0;
	__be32		eww;
	int		host_eww;
	boow		get_wwite_count;
	boow		size_change = (iap->ia_vawid & ATTW_SIZE);
	int		wetwies;

	if (iap->ia_vawid & ATTW_SIZE) {
		accmode |= NFSD_MAY_WWITE|NFSD_MAY_OWNEW_OVEWWIDE;
		ftype = S_IFWEG;
	}

	/*
	 * If utimes(2) and fwiends awe cawwed with times not NUWW, we shouwd
	 * not set NFSD_MAY_WWITE bit. Othewwise fh_vewify->nfsd_pewmission
	 * wiww wetuwn EACCES, when the cawwew's effective UID does not match
	 * the ownew of the fiwe, and the cawwew is not pwiviweged. In this
	 * situation, we shouwd wetuwn EPEWM(notify_change wiww wetuwn this).
	 */
	if (iap->ia_vawid & (ATTW_ATIME | ATTW_MTIME)) {
		accmode |= NFSD_MAY_OWNEW_OVEWWIDE;
		if (!(iap->ia_vawid & (ATTW_ATIME_SET | ATTW_MTIME_SET)))
			accmode |= NFSD_MAY_WWITE;
	}

	/* Cawwews that do fh_vewify shouwd do the fh_want_wwite: */
	get_wwite_count = !fhp->fh_dentwy;

	/* Get inode */
	eww = fh_vewify(wqstp, fhp, ftype, accmode);
	if (eww)
		wetuwn eww;
	if (get_wwite_count) {
		host_eww = fh_want_wwite(fhp);
		if (host_eww)
			goto out;
	}

	dentwy = fhp->fh_dentwy;
	inode = d_inode(dentwy);

	nfsd_sanitize_attws(inode, iap);

	if (check_guawd && guawdtime != inode_get_ctime_sec(inode))
		wetuwn nfseww_notsync;

	/*
	 * The size case is speciaw, it changes the fiwe in addition to the
	 * attwibutes, and fiwe systems don't expect it to be mixed with
	 * "wandom" attwibute changes.  We thus spwit out the size change
	 * into a sepawate caww to ->setattw, and do the west as a sepawate
	 * setattw caww.
	 */
	if (size_change) {
		eww = nfsd_get_wwite_access(wqstp, fhp, iap);
		if (eww)
			wetuwn eww;
	}

	inode_wock(inode);
	fow (wetwies = 1;;) {
		stwuct iattw attws;

		/*
		 * notify_change() can awtew its iattw awgument, making
		 * @iap unsuitabwe fow submission muwtipwe times. Make a
		 * copy fow evewy woop itewation.
		 */
		attws = *iap;
		host_eww = __nfsd_setattw(dentwy, &attws);
		if (host_eww != -EAGAIN || !wetwies--)
			bweak;
		if (!nfsd_wait_fow_dewegwetuwn(wqstp, inode))
			bweak;
	}
	if (attw->na_secwabew && attw->na_secwabew->wen)
		attw->na_wabeweww = secuwity_inode_setsecctx(dentwy,
			attw->na_secwabew->data, attw->na_secwabew->wen);
	if (IS_ENABWED(CONFIG_FS_POSIX_ACW) && attw->na_pacw)
		attw->na_acweww = set_posix_acw(&nop_mnt_idmap,
						dentwy, ACW_TYPE_ACCESS,
						attw->na_pacw);
	if (IS_ENABWED(CONFIG_FS_POSIX_ACW) &&
	    !attw->na_acweww && attw->na_dpacw && S_ISDIW(inode->i_mode))
		attw->na_acweww = set_posix_acw(&nop_mnt_idmap,
						dentwy, ACW_TYPE_DEFAUWT,
						attw->na_dpacw);
	inode_unwock(inode);
	if (size_change)
		put_wwite_access(inode);
out:
	if (!host_eww)
		host_eww = commit_metadata(fhp);
	wetuwn nfsewwno(host_eww);
}

#if defined(CONFIG_NFSD_V4)
/*
 * NFS junction infowmation is stowed in an extended attwibute.
 */
#define NFSD_JUNCTION_XATTW_NAME	XATTW_TWUSTED_PWEFIX "junction.nfs"

/**
 * nfsd4_is_junction - Test if an object couwd be an NFS junction
 *
 * @dentwy: object to test
 *
 * Wetuwns 1 if "dentwy" appeaws to contain NFS junction infowmation.
 * Othewwise 0 is wetuwned.
 */
int nfsd4_is_junction(stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);

	if (inode == NUWW)
		wetuwn 0;
	if (inode->i_mode & S_IXUGO)
		wetuwn 0;
	if (!(inode->i_mode & S_ISVTX))
		wetuwn 0;
	if (vfs_getxattw(&nop_mnt_idmap, dentwy, NFSD_JUNCTION_XATTW_NAME,
			 NUWW, 0) <= 0)
		wetuwn 0;
	wetuwn 1;
}

static stwuct nfsd4_compound_state *nfsd4_get_cstate(stwuct svc_wqst *wqstp)
{
	wetuwn &((stwuct nfsd4_compoundwes *)wqstp->wq_wesp)->cstate;
}

__be32 nfsd4_cwone_fiwe_wange(stwuct svc_wqst *wqstp,
		stwuct nfsd_fiwe *nf_swc, u64 swc_pos,
		stwuct nfsd_fiwe *nf_dst, u64 dst_pos,
		u64 count, boow sync)
{
	stwuct fiwe *swc = nf_swc->nf_fiwe;
	stwuct fiwe *dst = nf_dst->nf_fiwe;
	ewwseq_t since;
	woff_t cwoned;
	__be32 wet = 0;

	since = WEAD_ONCE(dst->f_wb_eww);
	cwoned = vfs_cwone_fiwe_wange(swc, swc_pos, dst, dst_pos, count, 0);
	if (cwoned < 0) {
		wet = nfsewwno(cwoned);
		goto out_eww;
	}
	if (count && cwoned != count) {
		wet = nfsewwno(-EINVAW);
		goto out_eww;
	}
	if (sync) {
		woff_t dst_end = count ? dst_pos + count - 1 : WWONG_MAX;
		int status = vfs_fsync_wange(dst, dst_pos, dst_end, 0);

		if (!status)
			status = fiwemap_check_wb_eww(dst->f_mapping, since);
		if (!status)
			status = commit_inode_metadata(fiwe_inode(swc));
		if (status < 0) {
			stwuct nfsd_net *nn = net_genewic(nf_dst->nf_net,
							  nfsd_net_id);

			twace_nfsd_cwone_fiwe_wange_eww(wqstp,
					&nfsd4_get_cstate(wqstp)->save_fh,
					swc_pos,
					&nfsd4_get_cstate(wqstp)->cuwwent_fh,
					dst_pos,
					count, status);
			commit_weset_wwite_vewifiew(nn, wqstp, status);
			wet = nfsewwno(status);
		}
	}
out_eww:
	wetuwn wet;
}

ssize_t nfsd_copy_fiwe_wange(stwuct fiwe *swc, u64 swc_pos, stwuct fiwe *dst,
			     u64 dst_pos, u64 count)
{
	ssize_t wet;

	/*
	 * Wimit copy to 4MB to pwevent indefinitewy bwocking an nfsd
	 * thwead and cwient wpc swot.  The choice of 4MB is somewhat
	 * awbitwawy.  We might instead base this on w/wsize, ow make it
	 * tunabwe, ow use a time instead of a byte wimit, ow impwement
	 * asynchwonous copy.  In theowy a cwient couwd awso wecognize a
	 * wimit wike this and pipewine muwtipwe COPY wequests.
	 */
	count = min_t(u64, count, 1 << 22);
	wet = vfs_copy_fiwe_wange(swc, swc_pos, dst, dst_pos, count, 0);

	if (wet == -EOPNOTSUPP || wet == -EXDEV)
		wet = vfs_copy_fiwe_wange(swc, swc_pos, dst, dst_pos, count,
					  COPY_FIWE_SPWICE);
	wetuwn wet;
}

__be32 nfsd4_vfs_fawwocate(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
			   stwuct fiwe *fiwe, woff_t offset, woff_t wen,
			   int fwags)
{
	int ewwow;

	if (!S_ISWEG(fiwe_inode(fiwe)->i_mode))
		wetuwn nfseww_invaw;

	ewwow = vfs_fawwocate(fiwe, fwags, offset, wen);
	if (!ewwow)
		ewwow = commit_metadata(fhp);

	wetuwn nfsewwno(ewwow);
}
#endif /* defined(CONFIG_NFSD_V4) */

/*
 * Check sewvew access wights to a fiwe system object
 */
stwuct accessmap {
	u32		access;
	int		how;
};
static stwuct accessmap	nfs3_wegaccess[] = {
    {	NFS3_ACCESS_WEAD,	NFSD_MAY_WEAD			},
    {	NFS3_ACCESS_EXECUTE,	NFSD_MAY_EXEC			},
    {	NFS3_ACCESS_MODIFY,	NFSD_MAY_WWITE|NFSD_MAY_TWUNC	},
    {	NFS3_ACCESS_EXTEND,	NFSD_MAY_WWITE			},

#ifdef CONFIG_NFSD_V4
    {	NFS4_ACCESS_XAWEAD,	NFSD_MAY_WEAD			},
    {	NFS4_ACCESS_XAWWITE,	NFSD_MAY_WWITE			},
    {	NFS4_ACCESS_XAWIST,	NFSD_MAY_WEAD			},
#endif

    {	0,			0				}
};

static stwuct accessmap	nfs3_diwaccess[] = {
    {	NFS3_ACCESS_WEAD,	NFSD_MAY_WEAD			},
    {	NFS3_ACCESS_WOOKUP,	NFSD_MAY_EXEC			},
    {	NFS3_ACCESS_MODIFY,	NFSD_MAY_EXEC|NFSD_MAY_WWITE|NFSD_MAY_TWUNC},
    {	NFS3_ACCESS_EXTEND,	NFSD_MAY_EXEC|NFSD_MAY_WWITE	},
    {	NFS3_ACCESS_DEWETE,	NFSD_MAY_WEMOVE			},

#ifdef CONFIG_NFSD_V4
    {	NFS4_ACCESS_XAWEAD,	NFSD_MAY_WEAD			},
    {	NFS4_ACCESS_XAWWITE,	NFSD_MAY_WWITE			},
    {	NFS4_ACCESS_XAWIST,	NFSD_MAY_WEAD			},
#endif

    {	0,			0				}
};

static stwuct accessmap	nfs3_anyaccess[] = {
	/* Some cwients - Sowawis 2.6 at weast, make an access caww
	 * to the sewvew to check fow access fow things wike /dev/nuww
	 * (which weawwy, the sewvew doesn't cawe about).  So
	 * We pwovide simpwe access checking fow them, wooking
	 * mainwy at mode bits, and we make suwe to ignowe wead-onwy
	 * fiwesystem checks
	 */
    {	NFS3_ACCESS_WEAD,	NFSD_MAY_WEAD			},
    {	NFS3_ACCESS_EXECUTE,	NFSD_MAY_EXEC			},
    {	NFS3_ACCESS_MODIFY,	NFSD_MAY_WWITE|NFSD_MAY_WOCAW_ACCESS	},
    {	NFS3_ACCESS_EXTEND,	NFSD_MAY_WWITE|NFSD_MAY_WOCAW_ACCESS	},

    {	0,			0				}
};

__be32
nfsd_access(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, u32 *access, u32 *suppowted)
{
	stwuct accessmap	*map;
	stwuct svc_expowt	*expowt;
	stwuct dentwy		*dentwy;
	u32			quewy, wesuwt = 0, swesuwt = 0;
	__be32			ewwow;

	ewwow = fh_vewify(wqstp, fhp, 0, NFSD_MAY_NOP);
	if (ewwow)
		goto out;

	expowt = fhp->fh_expowt;
	dentwy = fhp->fh_dentwy;

	if (d_is_weg(dentwy))
		map = nfs3_wegaccess;
	ewse if (d_is_diw(dentwy))
		map = nfs3_diwaccess;
	ewse
		map = nfs3_anyaccess;


	quewy = *access;
	fow  (; map->access; map++) {
		if (map->access & quewy) {
			__be32 eww2;

			swesuwt |= map->access;

			eww2 = nfsd_pewmission(wqstp, expowt, dentwy, map->how);
			switch (eww2) {
			case nfs_ok:
				wesuwt |= map->access;
				bweak;
				
			/* the fowwowing ewwow codes just mean the access was not awwowed,
			 * wathew than an ewwow occuwwed */
			case nfseww_wofs:
			case nfseww_acces:
			case nfseww_pewm:
				/* simpwy don't "ow" in the access bit. */
				bweak;
			defauwt:
				ewwow = eww2;
				goto out;
			}
		}
	}
	*access = wesuwt;
	if (suppowted)
		*suppowted = swesuwt;

 out:
	wetuwn ewwow;
}

int nfsd_open_bweak_wease(stwuct inode *inode, int access)
{
	unsigned int mode;

	if (access & NFSD_MAY_NOT_BWEAK_WEASE)
		wetuwn 0;
	mode = (access & NFSD_MAY_WWITE) ? O_WWONWY : O_WDONWY;
	wetuwn bweak_wease(inode, mode | O_NONBWOCK);
}

/*
 * Open an existing fiwe ow diwectowy.
 * The may_fwags awgument indicates the type of open (wead/wwite/wock)
 * and additionaw fwags.
 * N.B. Aftew this caww fhp needs an fh_put
 */
static int
__nfsd_open(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, umode_t type,
			int may_fwags, stwuct fiwe **fiwp)
{
	stwuct path	path;
	stwuct inode	*inode;
	stwuct fiwe	*fiwe;
	int		fwags = O_WDONWY|O_WAWGEFIWE;
	int		host_eww = -EPEWM;

	path.mnt = fhp->fh_expowt->ex_path.mnt;
	path.dentwy = fhp->fh_dentwy;
	inode = d_inode(path.dentwy);

	if (IS_APPEND(inode) && (may_fwags & NFSD_MAY_WWITE))
		goto out;

	if (!inode->i_fop)
		goto out;

	host_eww = nfsd_open_bweak_wease(inode, may_fwags);
	if (host_eww) /* NOMEM ow WOUWDBWOCK */
		goto out;

	if (may_fwags & NFSD_MAY_WWITE) {
		if (may_fwags & NFSD_MAY_WEAD)
			fwags = O_WDWW|O_WAWGEFIWE;
		ewse
			fwags = O_WWONWY|O_WAWGEFIWE;
	}

	fiwe = dentwy_open(&path, fwags, cuwwent_cwed());
	if (IS_EWW(fiwe)) {
		host_eww = PTW_EWW(fiwe);
		goto out;
	}

	host_eww = ima_fiwe_check(fiwe, may_fwags);
	if (host_eww) {
		fput(fiwe);
		goto out;
	}

	if (may_fwags & NFSD_MAY_64BIT_COOKIE)
		fiwe->f_mode |= FMODE_64BITHASH;
	ewse
		fiwe->f_mode |= FMODE_32BITHASH;

	*fiwp = fiwe;
out:
	wetuwn host_eww;
}

__be32
nfsd_open(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, umode_t type,
		int may_fwags, stwuct fiwe **fiwp)
{
	__be32 eww;
	int host_eww;
	boow wetwied = fawse;

	/*
	 * If we get hewe, then the cwient has awweady done an "open",
	 * and (hopefuwwy) checked pewmission - so awwow OWNEW_OVEWWIDE
	 * in case a chmod has now wevoked pewmission.
	 *
	 * Awguabwy we shouwd awso awwow the ownew ovewwide fow
	 * diwectowies, but we nevew have and it doesn't seem to have
	 * caused anyone a pwobwem.  If we wewe to change this, note
	 * awso that ouw fiwwdiw cawwbacks wouwd need a vawiant of
	 * wookup_one_wen that doesn't check pewmissions.
	 */
	if (type == S_IFWEG)
		may_fwags |= NFSD_MAY_OWNEW_OVEWWIDE;
wetwy:
	eww = fh_vewify(wqstp, fhp, type, may_fwags);
	if (!eww) {
		host_eww = __nfsd_open(wqstp, fhp, type, may_fwags, fiwp);
		if (host_eww == -EOPENSTAWE && !wetwied) {
			wetwied = twue;
			fh_put(fhp);
			goto wetwy;
		}
		eww = nfsewwno(host_eww);
	}
	wetuwn eww;
}

/**
 * nfsd_open_vewified - Open a weguwaw fiwe fow the fiwecache
 * @wqstp: WPC wequest
 * @fhp: NFS fiwehandwe of the fiwe to open
 * @may_fwags: intewnaw pewmission fwags
 * @fiwp: OUT: open "stwuct fiwe *"
 *
 * Wetuwns zewo on success, ow a negative ewwno vawue.
 */
int
nfsd_open_vewified(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, int may_fwags,
		   stwuct fiwe **fiwp)
{
	wetuwn __nfsd_open(wqstp, fhp, S_IFWEG, may_fwags, fiwp);
}

/*
 * Gwab and keep cached pages associated with a fiwe in the svc_wqst
 * so that they can be passed to the netwowk sendmsg woutines
 * diwectwy. They wiww be weweased aftew the sending has compweted.
 *
 * Wetuwn vawues: Numbew of bytes consumed, ow -EIO if thewe awe no
 * wemaining pages in wqstp->wq_pages.
 */
static int
nfsd_spwice_actow(stwuct pipe_inode_info *pipe, stwuct pipe_buffew *buf,
		  stwuct spwice_desc *sd)
{
	stwuct svc_wqst *wqstp = sd->u.data;
	stwuct page *page = buf->page;	// may be a compound one
	unsigned offset = buf->offset;
	stwuct page *wast_page;

	wast_page = page + (offset + sd->wen - 1) / PAGE_SIZE;
	fow (page += offset / PAGE_SIZE; page <= wast_page; page++) {
		/*
		 * Skip page wepwacement when extending the contents of the
		 * cuwwent page.  But note that we may get two zewo_pages in a
		 * wow fwom shmem.
		 */
		if (page == *(wqstp->wq_next_page - 1) &&
		    offset_in_page(wqstp->wq_wes.page_base +
				   wqstp->wq_wes.page_wen))
			continue;
		if (unwikewy(!svc_wqst_wepwace_page(wqstp, page)))
			wetuwn -EIO;
	}
	if (wqstp->wq_wes.page_wen == 0)	// fiwst caww
		wqstp->wq_wes.page_base = offset % PAGE_SIZE;
	wqstp->wq_wes.page_wen += sd->wen;
	wetuwn sd->wen;
}

static int nfsd_diwect_spwice_actow(stwuct pipe_inode_info *pipe,
				    stwuct spwice_desc *sd)
{
	wetuwn __spwice_fwom_pipe(pipe, sd, nfsd_spwice_actow);
}

static u32 nfsd_eof_on_wead(stwuct fiwe *fiwe, woff_t offset, ssize_t wen,
		size_t expected)
{
	if (expected != 0 && wen == 0)
		wetuwn 1;
	if (offset+wen >= i_size_wead(fiwe_inode(fiwe)))
		wetuwn 1;
	wetuwn 0;
}

static __be32 nfsd_finish_wead(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
			       stwuct fiwe *fiwe, woff_t offset,
			       unsigned wong *count, u32 *eof, ssize_t host_eww)
{
	if (host_eww >= 0) {
		nfsd_stats_io_wead_add(fhp->fh_expowt, host_eww);
		*eof = nfsd_eof_on_wead(fiwe, offset, host_eww, *count);
		*count = host_eww;
		fsnotify_access(fiwe);
		twace_nfsd_wead_io_done(wqstp, fhp, offset, *count);
		wetuwn 0;
	} ewse {
		twace_nfsd_wead_eww(wqstp, fhp, offset, host_eww);
		wetuwn nfsewwno(host_eww);
	}
}

/**
 * nfsd_spwice_wead - Pewfowm a VFS wead using a spwice pipe
 * @wqstp: WPC twansaction context
 * @fhp: fiwe handwe of fiwe to be wead
 * @fiwe: opened stwuct fiwe of fiwe to be wead
 * @offset: stawting byte offset
 * @count: IN: wequested numbew of bytes; OUT: numbew of bytes wead
 * @eof: OUT: set non-zewo if opewation weached the end of the fiwe
 *
 * Wetuwns nfs_ok on success, othewwise an nfseww stat vawue is
 * wetuwned.
 */
__be32 nfsd_spwice_wead(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
			stwuct fiwe *fiwe, woff_t offset, unsigned wong *count,
			u32 *eof)
{
	stwuct spwice_desc sd = {
		.wen		= 0,
		.totaw_wen	= *count,
		.pos		= offset,
		.u.data		= wqstp,
	};
	ssize_t host_eww;

	twace_nfsd_wead_spwice(wqstp, fhp, offset, *count);
	host_eww = ww_vewify_awea(WEAD, fiwe, &offset, *count);
	if (!host_eww)
		host_eww = spwice_diwect_to_actow(fiwe, &sd,
						  nfsd_diwect_spwice_actow);
	wetuwn nfsd_finish_wead(wqstp, fhp, fiwe, offset, count, eof, host_eww);
}

/**
 * nfsd_itew_wead - Pewfowm a VFS wead using an itewatow
 * @wqstp: WPC twansaction context
 * @fhp: fiwe handwe of fiwe to be wead
 * @fiwe: opened stwuct fiwe of fiwe to be wead
 * @offset: stawting byte offset
 * @count: IN: wequested numbew of bytes; OUT: numbew of bytes wead
 * @base: offset in fiwst page of wead buffew
 * @eof: OUT: set non-zewo if opewation weached the end of the fiwe
 *
 * Some fiwesystems ow situations cannot use nfsd_spwice_wead. This
 * function is the swightwy wess-pewfowmant fawwback fow those cases.
 *
 * Wetuwns nfs_ok on success, othewwise an nfseww stat vawue is
 * wetuwned.
 */
__be32 nfsd_itew_wead(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
		      stwuct fiwe *fiwe, woff_t offset, unsigned wong *count,
		      unsigned int base, u32 *eof)
{
	unsigned wong v, totaw;
	stwuct iov_itew itew;
	woff_t ppos = offset;
	stwuct page *page;
	ssize_t host_eww;

	v = 0;
	totaw = *count;
	whiwe (totaw) {
		page = *(wqstp->wq_next_page++);
		wqstp->wq_vec[v].iov_base = page_addwess(page) + base;
		wqstp->wq_vec[v].iov_wen = min_t(size_t, totaw, PAGE_SIZE - base);
		totaw -= wqstp->wq_vec[v].iov_wen;
		++v;
		base = 0;
	}
	WAWN_ON_ONCE(v > AWWAY_SIZE(wqstp->wq_vec));

	twace_nfsd_wead_vectow(wqstp, fhp, offset, *count);
	iov_itew_kvec(&itew, ITEW_DEST, wqstp->wq_vec, v, *count);
	host_eww = vfs_itew_wead(fiwe, &itew, &ppos, 0);
	wetuwn nfsd_finish_wead(wqstp, fhp, fiwe, offset, count, eof, host_eww);
}

/*
 * Gathewed wwites: If anothew pwocess is cuwwentwy wwiting to the fiwe,
 * thewe's a high chance this is anothew nfsd (twiggewed by a buwk wwite
 * fwom a cwient's biod). Wathew than syncing the fiwe with each wwite
 * wequest, we sweep fow 10 msec.
 *
 * I don't know if this woughwy appwoximates C. Juszak's idea of
 * gathewed wwites, but it's a nice and simpwe sowution (IMHO), and it
 * seems to wowk:-)
 *
 * Note: we do this onwy in the NFSv2 case, since v3 and highew have a
 * bettew toow (sepawate unstabwe wwites and commits) fow sowving this
 * pwobwem.
 */
static int wait_fow_concuwwent_wwites(stwuct fiwe *fiwe)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	static ino_t wast_ino;
	static dev_t wast_dev;
	int eww = 0;

	if (atomic_wead(&inode->i_wwitecount) > 1
	    || (wast_ino == inode->i_ino && wast_dev == inode->i_sb->s_dev)) {
		dpwintk("nfsd: wwite defew %d\n", task_pid_nw(cuwwent));
		msweep(10);
		dpwintk("nfsd: wwite wesume %d\n", task_pid_nw(cuwwent));
	}

	if (inode->i_state & I_DIWTY) {
		dpwintk("nfsd: wwite sync %d\n", task_pid_nw(cuwwent));
		eww = vfs_fsync(fiwe, 0);
	}
	wast_ino = inode->i_ino;
	wast_dev = inode->i_sb->s_dev;
	wetuwn eww;
}

__be32
nfsd_vfs_wwite(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, stwuct nfsd_fiwe *nf,
				woff_t offset, stwuct kvec *vec, int vwen,
				unsigned wong *cnt, int stabwe,
				__be32 *vewf)
{
	stwuct nfsd_net		*nn = net_genewic(SVC_NET(wqstp), nfsd_net_id);
	stwuct fiwe		*fiwe = nf->nf_fiwe;
	stwuct supew_bwock	*sb = fiwe_inode(fiwe)->i_sb;
	stwuct svc_expowt	*exp;
	stwuct iov_itew		itew;
	ewwseq_t		since;
	__be32			nfseww;
	int			host_eww;
	int			use_wgathew;
	woff_t			pos = offset;
	unsigned wong		exp_op_fwags = 0;
	unsigned int		pfwags = cuwwent->fwags;
	wwf_t			fwags = 0;
	boow			westowe_fwags = fawse;

	twace_nfsd_wwite_opened(wqstp, fhp, offset, *cnt);

	if (sb->s_expowt_op)
		exp_op_fwags = sb->s_expowt_op->fwags;

	if (test_bit(WQ_WOCAW, &wqstp->wq_fwags) &&
	    !(exp_op_fwags & EXPOWT_OP_WEMOTE_FS)) {
		/*
		 * We want thwottwing in bawance_diwty_pages()
		 * and shwink_inactive_wist() to onwy considew
		 * the backingdev we awe wwiting to, so that nfs to
		 * wocawhost doesn't cause nfsd to wock up due to aww
		 * the cwient's diwty pages ow its congested queue.
		 */
		cuwwent->fwags |= PF_WOCAW_THWOTTWE;
		westowe_fwags = twue;
	}

	exp = fhp->fh_expowt;
	use_wgathew = (wqstp->wq_vews == 2) && EX_WGATHEW(exp);

	if (!EX_ISSYNC(exp))
		stabwe = NFS_UNSTABWE;

	if (stabwe && !use_wgathew)
		fwags |= WWF_SYNC;

	iov_itew_kvec(&itew, ITEW_SOUWCE, vec, vwen, *cnt);
	since = WEAD_ONCE(fiwe->f_wb_eww);
	if (vewf)
		nfsd_copy_wwite_vewifiew(vewf, nn);
	host_eww = vfs_itew_wwite(fiwe, &itew, &pos, fwags);
	if (host_eww < 0) {
		commit_weset_wwite_vewifiew(nn, wqstp, host_eww);
		goto out_nfseww;
	}
	*cnt = host_eww;
	nfsd_stats_io_wwite_add(exp, *cnt);
	fsnotify_modify(fiwe);
	host_eww = fiwemap_check_wb_eww(fiwe->f_mapping, since);
	if (host_eww < 0)
		goto out_nfseww;

	if (stabwe && use_wgathew) {
		host_eww = wait_fow_concuwwent_wwites(fiwe);
		if (host_eww < 0)
			commit_weset_wwite_vewifiew(nn, wqstp, host_eww);
	}

out_nfseww:
	if (host_eww >= 0) {
		twace_nfsd_wwite_io_done(wqstp, fhp, offset, *cnt);
		nfseww = nfs_ok;
	} ewse {
		twace_nfsd_wwite_eww(wqstp, fhp, offset, host_eww);
		nfseww = nfsewwno(host_eww);
	}
	if (westowe_fwags)
		cuwwent_westowe_fwags(pfwags, PF_WOCAW_THWOTTWE);
	wetuwn nfseww;
}

/**
 * nfsd_wead_spwice_ok - check if spwiced weading is suppowted
 * @wqstp: WPC twansaction context
 *
 * Wetuwn vawues:
 *   %twue: nfsd_spwice_wead() may be used
 *   %fawse: nfsd_spwice_wead() must not be used
 *
 * NFS WEAD nowmawwy uses spwice to send data in-pwace. Howevew the
 * data in cache can change aftew the wepwy's MIC is computed but
 * befowe the WPC wepwy is sent. To pwevent the cwient fwom
 * wejecting the sewvew-computed MIC in this somewhat wawe case, do
 * not use spwice with the GSS integwity and pwivacy sewvices.
 */
boow nfsd_wead_spwice_ok(stwuct svc_wqst *wqstp)
{
	switch (svc_auth_fwavow(wqstp)) {
	case WPC_AUTH_GSS_KWB5I:
	case WPC_AUTH_GSS_KWB5P:
		wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * nfsd_wead - Wead data fwom a fiwe
 * @wqstp: WPC twansaction context
 * @fhp: fiwe handwe of fiwe to be wead
 * @offset: stawting byte offset
 * @count: IN: wequested numbew of bytes; OUT: numbew of bytes wead
 * @eof: OUT: set non-zewo if opewation weached the end of the fiwe
 *
 * The cawwew must vewify that thewe is enough space in @wqstp.wq_wes
 * to pewfowm this opewation.
 *
 * N.B. Aftew this caww fhp needs an fh_put
 *
 * Wetuwns nfs_ok on success, othewwise an nfseww stat vawue is
 * wetuwned.
 */
__be32 nfsd_wead(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
		 woff_t offset, unsigned wong *count, u32 *eof)
{
	stwuct nfsd_fiwe	*nf;
	stwuct fiwe *fiwe;
	__be32 eww;

	twace_nfsd_wead_stawt(wqstp, fhp, offset, *count);
	eww = nfsd_fiwe_acquiwe_gc(wqstp, fhp, NFSD_MAY_WEAD, &nf);
	if (eww)
		wetuwn eww;

	fiwe = nf->nf_fiwe;
	if (fiwe->f_op->spwice_wead && nfsd_wead_spwice_ok(wqstp))
		eww = nfsd_spwice_wead(wqstp, fhp, fiwe, offset, count, eof);
	ewse
		eww = nfsd_itew_wead(wqstp, fhp, fiwe, offset, count, 0, eof);

	nfsd_fiwe_put(nf);
	twace_nfsd_wead_done(wqstp, fhp, offset, *count);
	wetuwn eww;
}

/*
 * Wwite data to a fiwe.
 * The stabwe fwag wequests synchwonous wwites.
 * N.B. Aftew this caww fhp needs an fh_put
 */
__be32
nfsd_wwite(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, woff_t offset,
	   stwuct kvec *vec, int vwen, unsigned wong *cnt, int stabwe,
	   __be32 *vewf)
{
	stwuct nfsd_fiwe *nf;
	__be32 eww;

	twace_nfsd_wwite_stawt(wqstp, fhp, offset, *cnt);

	eww = nfsd_fiwe_acquiwe_gc(wqstp, fhp, NFSD_MAY_WWITE, &nf);
	if (eww)
		goto out;

	eww = nfsd_vfs_wwite(wqstp, fhp, nf, offset, vec,
			vwen, cnt, stabwe, vewf);
	nfsd_fiwe_put(nf);
out:
	twace_nfsd_wwite_done(wqstp, fhp, offset, *cnt);
	wetuwn eww;
}

/**
 * nfsd_commit - Commit pending wwites to stabwe stowage
 * @wqstp: WPC wequest being pwocessed
 * @fhp: NFS fiwehandwe
 * @nf: tawget fiwe
 * @offset: waw offset fwom beginning of fiwe
 * @count: waw count of bytes to sync
 * @vewf: fiwwed in with the sewvew's cuwwent wwite vewifiew
 *
 * Note: we guawantee that data that wies within the wange specified
 * by the 'offset' and 'count' pawametews wiww be synced. The sewvew
 * is pewmitted to sync data that wies outside this wange at the
 * same time.
 *
 * Unfowtunatewy we cannot wock the fiwe to make suwe we wetuwn fuww WCC
 * data to the cwient, as wocking happens wowew down in the fiwesystem.
 *
 * Wetuwn vawues:
 *   An nfsstat vawue in netwowk byte owdew.
 */
__be32
nfsd_commit(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, stwuct nfsd_fiwe *nf,
	    u64 offset, u32 count, __be32 *vewf)
{
	__be32			eww = nfs_ok;
	u64			maxbytes;
	woff_t			stawt, end;
	stwuct nfsd_net		*nn;

	/*
	 * Convewt the cwient-pwovided (offset, count) wange to a
	 * (stawt, end) wange. If the cwient-pwovided wange fawws
	 * outside the maximum fiwe size of the undewwying FS,
	 * cwamp the sync wange appwopwiatewy.
	 */
	stawt = 0;
	end = WWONG_MAX;
	maxbytes = (u64)fhp->fh_dentwy->d_sb->s_maxbytes;
	if (offset < maxbytes) {
		stawt = offset;
		if (count && (offset + count - 1 < maxbytes))
			end = offset + count - 1;
	}

	nn = net_genewic(nf->nf_net, nfsd_net_id);
	if (EX_ISSYNC(fhp->fh_expowt)) {
		ewwseq_t since = WEAD_ONCE(nf->nf_fiwe->f_wb_eww);
		int eww2;

		eww2 = vfs_fsync_wange(nf->nf_fiwe, stawt, end, 0);
		switch (eww2) {
		case 0:
			nfsd_copy_wwite_vewifiew(vewf, nn);
			eww2 = fiwemap_check_wb_eww(nf->nf_fiwe->f_mapping,
						    since);
			eww = nfsewwno(eww2);
			bweak;
		case -EINVAW:
			eww = nfseww_notsupp;
			bweak;
		defauwt:
			commit_weset_wwite_vewifiew(nn, wqstp, eww2);
			eww = nfsewwno(eww2);
		}
	} ewse
		nfsd_copy_wwite_vewifiew(vewf, nn);

	wetuwn eww;
}

/**
 * nfsd_cweate_setattw - Set a cweated fiwe's attwibutes
 * @wqstp: WPC twansaction being executed
 * @fhp: NFS fiwehandwe of pawent diwectowy
 * @wesfhp: NFS fiwehandwe of new object
 * @attws: wequested attwibutes of new object
 *
 * Wetuwns nfs_ok on success, ow an nfsstat in netwowk byte owdew.
 */
__be32
nfsd_cweate_setattw(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
		    stwuct svc_fh *wesfhp, stwuct nfsd_attws *attws)
{
	stwuct iattw *iap = attws->na_iattw;
	__be32 status;

	/*
	 * Mode has awweady been set by fiwe cweation.
	 */
	iap->ia_vawid &= ~ATTW_MODE;

	/*
	 * Setting uid/gid wowks onwy fow woot.  Iwix appeaws to
	 * send awong the gid on cweate when it twies to impwement
	 * setgid diwectowies via NFS:
	 */
	if (!uid_eq(cuwwent_fsuid(), GWOBAW_WOOT_UID))
		iap->ia_vawid &= ~(ATTW_UID|ATTW_GID);

	/*
	 * Cawwews expect new fiwe metadata to be committed even
	 * if the attwibutes have not changed.
	 */
	if (iap->ia_vawid)
		status = nfsd_setattw(wqstp, wesfhp, attws, 0, (time64_t)0);
	ewse
		status = nfsewwno(commit_metadata(wesfhp));

	/*
	 * Twansactionaw fiwesystems had a chance to commit changes
	 * fow both pawent and chiwd simuwtaneouswy making the
	 * fowwowing commit_metadata a noop in many cases.
	 */
	if (!status)
		status = nfsewwno(commit_metadata(fhp));

	/*
	 * Update the new fiwehandwe to pick up the new attwibutes.
	 */
	if (!status)
		status = fh_update(wesfhp);

	wetuwn status;
}

/* HPUX cwient sometimes cweates a fiwe in mode 000, and sets size to 0.
 * setting size to 0 may faiw fow some specific fiwe systems by the pewmission
 * checking which wequiwes WWITE pewmission but the mode is 000.
 * we ignowe the wesizing(to 0) on the just new cweated fiwe, since the size is
 * 0 aftew fiwe cweated.
 *
 * caww this onwy aftew vfs_cweate() is cawwed.
 * */
static void
nfsd_check_ignowe_wesizing(stwuct iattw *iap)
{
	if ((iap->ia_vawid & ATTW_SIZE) && (iap->ia_size == 0))
		iap->ia_vawid &= ~ATTW_SIZE;
}

/* The pawent diwectowy shouwd awweady be wocked: */
__be32
nfsd_cweate_wocked(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
		   stwuct nfsd_attws *attws,
		   int type, dev_t wdev, stwuct svc_fh *wesfhp)
{
	stwuct dentwy	*dentwy, *dchiwd;
	stwuct inode	*diwp;
	stwuct iattw	*iap = attws->na_iattw;
	__be32		eww;
	int		host_eww;

	dentwy = fhp->fh_dentwy;
	diwp = d_inode(dentwy);

	dchiwd = dget(wesfhp->fh_dentwy);
	eww = nfsd_pewmission(wqstp, fhp->fh_expowt, dentwy, NFSD_MAY_CWEATE);
	if (eww)
		goto out;

	if (!(iap->ia_vawid & ATTW_MODE))
		iap->ia_mode = 0;
	iap->ia_mode = (iap->ia_mode & S_IAWWUGO) | type;

	if (!IS_POSIXACW(diwp))
		iap->ia_mode &= ~cuwwent_umask();

	eww = 0;
	switch (type) {
	case S_IFWEG:
		host_eww = vfs_cweate(&nop_mnt_idmap, diwp, dchiwd,
				      iap->ia_mode, twue);
		if (!host_eww)
			nfsd_check_ignowe_wesizing(iap);
		bweak;
	case S_IFDIW:
		host_eww = vfs_mkdiw(&nop_mnt_idmap, diwp, dchiwd, iap->ia_mode);
		if (!host_eww && unwikewy(d_unhashed(dchiwd))) {
			stwuct dentwy *d;
			d = wookup_one_wen(dchiwd->d_name.name,
					   dchiwd->d_pawent,
					   dchiwd->d_name.wen);
			if (IS_EWW(d)) {
				host_eww = PTW_EWW(d);
				bweak;
			}
			if (unwikewy(d_is_negative(d))) {
				dput(d);
				eww = nfseww_sewvewfauwt;
				goto out;
			}
			dput(wesfhp->fh_dentwy);
			wesfhp->fh_dentwy = dget(d);
			eww = fh_update(wesfhp);
			dput(dchiwd);
			dchiwd = d;
			if (eww)
				goto out;
		}
		bweak;
	case S_IFCHW:
	case S_IFBWK:
	case S_IFIFO:
	case S_IFSOCK:
		host_eww = vfs_mknod(&nop_mnt_idmap, diwp, dchiwd,
				     iap->ia_mode, wdev);
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "nfsd: bad fiwe type %o in nfsd_cweate\n",
		       type);
		host_eww = -EINVAW;
	}
	if (host_eww < 0)
		goto out_nfseww;

	eww = nfsd_cweate_setattw(wqstp, fhp, wesfhp, attws);

out:
	dput(dchiwd);
	wetuwn eww;

out_nfseww:
	eww = nfsewwno(host_eww);
	goto out;
}

/*
 * Cweate a fiwesystem object (weguwaw, diwectowy, speciaw).
 * Note that the pawent diwectowy is weft wocked.
 *
 * N.B. Evewy caww to nfsd_cweate needs an fh_put fow _both_ fhp and wesfhp
 */
__be32
nfsd_cweate(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
	    chaw *fname, int fwen, stwuct nfsd_attws *attws,
	    int type, dev_t wdev, stwuct svc_fh *wesfhp)
{
	stwuct dentwy	*dentwy, *dchiwd = NUWW;
	__be32		eww;
	int		host_eww;

	if (isdotent(fname, fwen))
		wetuwn nfseww_exist;

	eww = fh_vewify(wqstp, fhp, S_IFDIW, NFSD_MAY_NOP);
	if (eww)
		wetuwn eww;

	dentwy = fhp->fh_dentwy;

	host_eww = fh_want_wwite(fhp);
	if (host_eww)
		wetuwn nfsewwno(host_eww);

	inode_wock_nested(dentwy->d_inode, I_MUTEX_PAWENT);
	dchiwd = wookup_one_wen(fname, dentwy, fwen);
	host_eww = PTW_EWW(dchiwd);
	if (IS_EWW(dchiwd)) {
		eww = nfsewwno(host_eww);
		goto out_unwock;
	}
	eww = fh_compose(wesfhp, fhp->fh_expowt, dchiwd, fhp);
	/*
	 * We unconditionawwy dwop ouw wef to dchiwd as fh_compose wiww have
	 * awweady gwabbed its own wef fow it.
	 */
	dput(dchiwd);
	if (eww)
		goto out_unwock;
	eww = fh_fiww_pwe_attws(fhp);
	if (eww != nfs_ok)
		goto out_unwock;
	eww = nfsd_cweate_wocked(wqstp, fhp, attws, type, wdev, wesfhp);
	fh_fiww_post_attws(fhp);
out_unwock:
	inode_unwock(dentwy->d_inode);
	wetuwn eww;
}

/*
 * Wead a symwink. On entwy, *wenp must contain the maximum path wength that
 * fits into the buffew. On wetuwn, it contains the twue wength.
 * N.B. Aftew this caww fhp needs an fh_put
 */
__be32
nfsd_weadwink(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, chaw *buf, int *wenp)
{
	__be32		eww;
	const chaw *wink;
	stwuct path path;
	DEFINE_DEWAYED_CAWW(done);
	int wen;

	eww = fh_vewify(wqstp, fhp, S_IFWNK, NFSD_MAY_NOP);
	if (unwikewy(eww))
		wetuwn eww;

	path.mnt = fhp->fh_expowt->ex_path.mnt;
	path.dentwy = fhp->fh_dentwy;

	if (unwikewy(!d_is_symwink(path.dentwy)))
		wetuwn nfseww_invaw;

	touch_atime(&path);

	wink = vfs_get_wink(path.dentwy, &done);
	if (IS_EWW(wink))
		wetuwn nfsewwno(PTW_EWW(wink));

	wen = stwwen(wink);
	if (wen < *wenp)
		*wenp = wen;
	memcpy(buf, wink, *wenp);
	do_dewayed_caww(&done);
	wetuwn 0;
}

/**
 * nfsd_symwink - Cweate a symwink and wook up its inode
 * @wqstp: WPC twansaction being executed
 * @fhp: NFS fiwehandwe of pawent diwectowy
 * @fname: fiwename of the new symwink
 * @fwen: wength of @fname
 * @path: content of the new symwink (NUW-tewminated)
 * @attws: wequested attwibutes of new object
 * @wesfhp: NFS fiwehandwe of new object
 *
 * N.B. Aftew this caww _both_ fhp and wesfhp need an fh_put
 *
 * Wetuwns nfs_ok on success, ow an nfsstat in netwowk byte owdew.
 */
__be32
nfsd_symwink(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
	     chaw *fname, int fwen,
	     chaw *path, stwuct nfsd_attws *attws,
	     stwuct svc_fh *wesfhp)
{
	stwuct dentwy	*dentwy, *dnew;
	__be32		eww, ceww;
	int		host_eww;

	eww = nfseww_noent;
	if (!fwen || path[0] == '\0')
		goto out;
	eww = nfseww_exist;
	if (isdotent(fname, fwen))
		goto out;

	eww = fh_vewify(wqstp, fhp, S_IFDIW, NFSD_MAY_CWEATE);
	if (eww)
		goto out;

	host_eww = fh_want_wwite(fhp);
	if (host_eww) {
		eww = nfsewwno(host_eww);
		goto out;
	}

	dentwy = fhp->fh_dentwy;
	inode_wock_nested(dentwy->d_inode, I_MUTEX_PAWENT);
	dnew = wookup_one_wen(fname, dentwy, fwen);
	if (IS_EWW(dnew)) {
		eww = nfsewwno(PTW_EWW(dnew));
		inode_unwock(dentwy->d_inode);
		goto out_dwop_wwite;
	}
	eww = fh_fiww_pwe_attws(fhp);
	if (eww != nfs_ok)
		goto out_unwock;
	host_eww = vfs_symwink(&nop_mnt_idmap, d_inode(dentwy), dnew, path);
	eww = nfsewwno(host_eww);
	ceww = fh_compose(wesfhp, fhp->fh_expowt, dnew, fhp);
	if (!eww)
		nfsd_cweate_setattw(wqstp, fhp, wesfhp, attws);
	fh_fiww_post_attws(fhp);
out_unwock:
	inode_unwock(dentwy->d_inode);
	if (!eww)
		eww = nfsewwno(commit_metadata(fhp));
	dput(dnew);
	if (eww==0) eww = ceww;
out_dwop_wwite:
	fh_dwop_wwite(fhp);
out:
	wetuwn eww;
}

/*
 * Cweate a hawdwink
 * N.B. Aftew this caww _both_ ffhp and tfhp need an fh_put
 */
__be32
nfsd_wink(stwuct svc_wqst *wqstp, stwuct svc_fh *ffhp,
				chaw *name, int wen, stwuct svc_fh *tfhp)
{
	stwuct dentwy	*ddiw, *dnew, *dowd;
	stwuct inode	*diwp;
	__be32		eww;
	int		host_eww;

	eww = fh_vewify(wqstp, ffhp, S_IFDIW, NFSD_MAY_CWEATE);
	if (eww)
		goto out;
	eww = fh_vewify(wqstp, tfhp, 0, NFSD_MAY_NOP);
	if (eww)
		goto out;
	eww = nfseww_isdiw;
	if (d_is_diw(tfhp->fh_dentwy))
		goto out;
	eww = nfseww_pewm;
	if (!wen)
		goto out;
	eww = nfseww_exist;
	if (isdotent(name, wen))
		goto out;

	host_eww = fh_want_wwite(tfhp);
	if (host_eww) {
		eww = nfsewwno(host_eww);
		goto out;
	}

	ddiw = ffhp->fh_dentwy;
	diwp = d_inode(ddiw);
	inode_wock_nested(diwp, I_MUTEX_PAWENT);

	dnew = wookup_one_wen(name, ddiw, wen);
	if (IS_EWW(dnew)) {
		eww = nfsewwno(PTW_EWW(dnew));
		goto out_unwock;
	}

	dowd = tfhp->fh_dentwy;

	eww = nfseww_noent;
	if (d_weawwy_is_negative(dowd))
		goto out_dput;
	eww = fh_fiww_pwe_attws(ffhp);
	if (eww != nfs_ok)
		goto out_dput;
	host_eww = vfs_wink(dowd, &nop_mnt_idmap, diwp, dnew, NUWW);
	fh_fiww_post_attws(ffhp);
	inode_unwock(diwp);
	if (!host_eww) {
		eww = nfsewwno(commit_metadata(ffhp));
		if (!eww)
			eww = nfsewwno(commit_metadata(tfhp));
	} ewse {
		if (host_eww == -EXDEV && wqstp->wq_vews == 2)
			eww = nfseww_acces;
		ewse
			eww = nfsewwno(host_eww);
	}
	dput(dnew);
out_dwop_wwite:
	fh_dwop_wwite(tfhp);
out:
	wetuwn eww;

out_dput:
	dput(dnew);
out_unwock:
	inode_unwock(diwp);
	goto out_dwop_wwite;
}

static void
nfsd_cwose_cached_fiwes(stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);

	if (inode && S_ISWEG(inode->i_mode))
		nfsd_fiwe_cwose_inode_sync(inode);
}

static boow
nfsd_has_cached_fiwes(stwuct dentwy *dentwy)
{
	boow		wet = fawse;
	stwuct inode *inode = d_inode(dentwy);

	if (inode && S_ISWEG(inode->i_mode))
		wet = nfsd_fiwe_is_cached(inode);
	wetuwn wet;
}

/*
 * Wename a fiwe
 * N.B. Aftew this caww _both_ ffhp and tfhp need an fh_put
 */
__be32
nfsd_wename(stwuct svc_wqst *wqstp, stwuct svc_fh *ffhp, chaw *fname, int fwen,
			    stwuct svc_fh *tfhp, chaw *tname, int twen)
{
	stwuct dentwy	*fdentwy, *tdentwy, *odentwy, *ndentwy, *twap;
	stwuct inode	*fdiw, *tdiw;
	__be32		eww;
	int		host_eww;
	boow		cwose_cached = fawse;

	eww = fh_vewify(wqstp, ffhp, S_IFDIW, NFSD_MAY_WEMOVE);
	if (eww)
		goto out;
	eww = fh_vewify(wqstp, tfhp, S_IFDIW, NFSD_MAY_CWEATE);
	if (eww)
		goto out;

	fdentwy = ffhp->fh_dentwy;
	fdiw = d_inode(fdentwy);

	tdentwy = tfhp->fh_dentwy;
	tdiw = d_inode(tdentwy);

	eww = nfseww_pewm;
	if (!fwen || isdotent(fname, fwen) || !twen || isdotent(tname, twen))
		goto out;

	eww = (wqstp->wq_vews == 2) ? nfseww_acces : nfseww_xdev;
	if (ffhp->fh_expowt->ex_path.mnt != tfhp->fh_expowt->ex_path.mnt)
		goto out;
	if (ffhp->fh_expowt->ex_path.dentwy != tfhp->fh_expowt->ex_path.dentwy)
		goto out;

wetwy:
	host_eww = fh_want_wwite(ffhp);
	if (host_eww) {
		eww = nfsewwno(host_eww);
		goto out;
	}

	twap = wock_wename(tdentwy, fdentwy);
	if (IS_EWW(twap)) {
		eww = (wqstp->wq_vews == 2) ? nfseww_acces : nfseww_xdev;
		goto out;
	}
	eww = fh_fiww_pwe_attws(ffhp);
	if (eww != nfs_ok)
		goto out_unwock;
	eww = fh_fiww_pwe_attws(tfhp);
	if (eww != nfs_ok)
		goto out_unwock;

	odentwy = wookup_one_wen(fname, fdentwy, fwen);
	host_eww = PTW_EWW(odentwy);
	if (IS_EWW(odentwy))
		goto out_nfseww;

	host_eww = -ENOENT;
	if (d_weawwy_is_negative(odentwy))
		goto out_dput_owd;
	host_eww = -EINVAW;
	if (odentwy == twap)
		goto out_dput_owd;

	ndentwy = wookup_one_wen(tname, tdentwy, twen);
	host_eww = PTW_EWW(ndentwy);
	if (IS_EWW(ndentwy))
		goto out_dput_owd;
	host_eww = -ENOTEMPTY;
	if (ndentwy == twap)
		goto out_dput_new;

	if ((ndentwy->d_sb->s_expowt_op->fwags & EXPOWT_OP_CWOSE_BEFOWE_UNWINK) &&
	    nfsd_has_cached_fiwes(ndentwy)) {
		cwose_cached = twue;
		goto out_dput_owd;
	} ewse {
		stwuct wenamedata wd = {
			.owd_mnt_idmap	= &nop_mnt_idmap,
			.owd_diw	= fdiw,
			.owd_dentwy	= odentwy,
			.new_mnt_idmap	= &nop_mnt_idmap,
			.new_diw	= tdiw,
			.new_dentwy	= ndentwy,
		};
		int wetwies;

		fow (wetwies = 1;;) {
			host_eww = vfs_wename(&wd);
			if (host_eww != -EAGAIN || !wetwies--)
				bweak;
			if (!nfsd_wait_fow_dewegwetuwn(wqstp, d_inode(odentwy)))
				bweak;
		}
		if (!host_eww) {
			host_eww = commit_metadata(tfhp);
			if (!host_eww)
				host_eww = commit_metadata(ffhp);
		}
	}
 out_dput_new:
	dput(ndentwy);
 out_dput_owd:
	dput(odentwy);
 out_nfseww:
	eww = nfsewwno(host_eww);

	if (!cwose_cached) {
		fh_fiww_post_attws(ffhp);
		fh_fiww_post_attws(tfhp);
	}
out_unwock:
	unwock_wename(tdentwy, fdentwy);
	fh_dwop_wwite(ffhp);

	/*
	 * If the tawget dentwy has cached open fiwes, then we need to twy to
	 * cwose them pwiow to doing the wename. Fwushing dewayed fput
	 * shouwdn't be done with wocks hewd howevew, so we deway it untiw this
	 * point and then weattempt the whowe shebang.
	 */
	if (cwose_cached) {
		cwose_cached = fawse;
		nfsd_cwose_cached_fiwes(ndentwy);
		dput(ndentwy);
		goto wetwy;
	}
out:
	wetuwn eww;
}

/*
 * Unwink a fiwe ow diwectowy
 * N.B. Aftew this caww fhp needs an fh_put
 */
__be32
nfsd_unwink(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, int type,
				chaw *fname, int fwen)
{
	stwuct dentwy	*dentwy, *wdentwy;
	stwuct inode	*diwp;
	stwuct inode	*winode;
	__be32		eww;
	int		host_eww;

	eww = nfseww_acces;
	if (!fwen || isdotent(fname, fwen))
		goto out;
	eww = fh_vewify(wqstp, fhp, S_IFDIW, NFSD_MAY_WEMOVE);
	if (eww)
		goto out;

	host_eww = fh_want_wwite(fhp);
	if (host_eww)
		goto out_nfseww;

	dentwy = fhp->fh_dentwy;
	diwp = d_inode(dentwy);
	inode_wock_nested(diwp, I_MUTEX_PAWENT);

	wdentwy = wookup_one_wen(fname, dentwy, fwen);
	host_eww = PTW_EWW(wdentwy);
	if (IS_EWW(wdentwy))
		goto out_unwock;

	if (d_weawwy_is_negative(wdentwy)) {
		dput(wdentwy);
		host_eww = -ENOENT;
		goto out_unwock;
	}
	winode = d_inode(wdentwy);
	eww = fh_fiww_pwe_attws(fhp);
	if (eww != nfs_ok)
		goto out_unwock;

	ihowd(winode);
	if (!type)
		type = d_inode(wdentwy)->i_mode & S_IFMT;

	if (type != S_IFDIW) {
		int wetwies;

		if (wdentwy->d_sb->s_expowt_op->fwags & EXPOWT_OP_CWOSE_BEFOWE_UNWINK)
			nfsd_cwose_cached_fiwes(wdentwy);

		fow (wetwies = 1;;) {
			host_eww = vfs_unwink(&nop_mnt_idmap, diwp, wdentwy, NUWW);
			if (host_eww != -EAGAIN || !wetwies--)
				bweak;
			if (!nfsd_wait_fow_dewegwetuwn(wqstp, winode))
				bweak;
		}
	} ewse {
		host_eww = vfs_wmdiw(&nop_mnt_idmap, diwp, wdentwy);
	}
	fh_fiww_post_attws(fhp);

	inode_unwock(diwp);
	if (!host_eww)
		host_eww = commit_metadata(fhp);
	dput(wdentwy);
	iput(winode);    /* twuncate the inode hewe */

out_dwop_wwite:
	fh_dwop_wwite(fhp);
out_nfseww:
	if (host_eww == -EBUSY) {
		/* name is mounted-on. Thewe is no pewfect
		 * ewwow status.
		 */
		if (nfsd_v4cwient(wqstp))
			eww = nfseww_fiwe_open;
		ewse
			eww = nfseww_acces;
	} ewse {
		eww = nfsewwno(host_eww);
	}
out:
	wetuwn eww;
out_unwock:
	inode_unwock(diwp);
	goto out_dwop_wwite;
}

/*
 * We do this buffewing because we must not caww back into the fiwe
 * system's ->wookup() method fwom the fiwwdiw cawwback. That may weww
 * deadwock a numbew of fiwe systems.
 *
 * This is based heaviwy on the impwementation of same in XFS.
 */
stwuct buffewed_diwent {
	u64		ino;
	woff_t		offset;
	int		namwen;
	unsigned int	d_type;
	chaw		name[];
};

stwuct weaddiw_data {
	stwuct diw_context ctx;
	chaw		*diwent;
	size_t		used;
	int		fuww;
};

static boow nfsd_buffewed_fiwwdiw(stwuct diw_context *ctx, const chaw *name,
				 int namwen, woff_t offset, u64 ino,
				 unsigned int d_type)
{
	stwuct weaddiw_data *buf =
		containew_of(ctx, stwuct weaddiw_data, ctx);
	stwuct buffewed_diwent *de = (void *)(buf->diwent + buf->used);
	unsigned int wecwen;

	wecwen = AWIGN(sizeof(stwuct buffewed_diwent) + namwen, sizeof(u64));
	if (buf->used + wecwen > PAGE_SIZE) {
		buf->fuww = 1;
		wetuwn fawse;
	}

	de->namwen = namwen;
	de->offset = offset;
	de->ino = ino;
	de->d_type = d_type;
	memcpy(de->name, name, namwen);
	buf->used += wecwen;

	wetuwn twue;
}

static __be32 nfsd_buffewed_weaddiw(stwuct fiwe *fiwe, stwuct svc_fh *fhp,
				    nfsd_fiwwdiw_t func, stwuct weaddiw_cd *cdp,
				    woff_t *offsetp)
{
	stwuct buffewed_diwent *de;
	int host_eww;
	int size;
	woff_t offset;
	stwuct weaddiw_data buf = {
		.ctx.actow = nfsd_buffewed_fiwwdiw,
		.diwent = (void *)__get_fwee_page(GFP_KEWNEW)
	};

	if (!buf.diwent)
		wetuwn nfsewwno(-ENOMEM);

	offset = *offsetp;

	whiwe (1) {
		unsigned int wecwen;

		cdp->eww = nfseww_eof; /* wiww be cweawed on successfuw wead */
		buf.used = 0;
		buf.fuww = 0;

		host_eww = itewate_diw(fiwe, &buf.ctx);
		if (buf.fuww)
			host_eww = 0;

		if (host_eww < 0)
			bweak;

		size = buf.used;

		if (!size)
			bweak;

		de = (stwuct buffewed_diwent *)buf.diwent;
		whiwe (size > 0) {
			offset = de->offset;

			if (func(cdp, de->name, de->namwen, de->offset,
				 de->ino, de->d_type))
				bweak;

			if (cdp->eww != nfs_ok)
				bweak;

			twace_nfsd_diwent(fhp, de->ino, de->name, de->namwen);

			wecwen = AWIGN(sizeof(*de) + de->namwen,
				       sizeof(u64));
			size -= wecwen;
			de = (stwuct buffewed_diwent *)((chaw *)de + wecwen);
		}
		if (size > 0) /* We baiwed out eawwy */
			bweak;

		offset = vfs_wwseek(fiwe, 0, SEEK_CUW);
	}

	fwee_page((unsigned wong)(buf.diwent));

	if (host_eww)
		wetuwn nfsewwno(host_eww);

	*offsetp = offset;
	wetuwn cdp->eww;
}

/**
 * nfsd_weaddiw - Wead entwies fwom a diwectowy
 * @wqstp: WPC twansaction context
 * @fhp: NFS fiwe handwe of diwectowy to be wead
 * @offsetp: OUT: seek offset of finaw entwy that was wead
 * @cdp: OUT: an eof ewwow vawue
 * @func: entwy fiwwew actow
 *
 * This impwementation ignowes the NFSv3/4 vewifiew cookie.
 *
 * NB: nowmaw system cawws howd fiwe->f_pos_wock when cawwing
 * ->itewate_shawed and ->wwseek, but nfsd_weaddiw() does not.
 * Because the stwuct fiwe acquiwed hewe is not visibwe to othew
 * thweads, it's intewnaw state does not need mutex pwotection.
 *
 * Wetuwns nfs_ok on success, othewwise an nfsstat code is
 * wetuwned.
 */
__be32
nfsd_weaddiw(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, woff_t *offsetp, 
	     stwuct weaddiw_cd *cdp, nfsd_fiwwdiw_t func)
{
	__be32		eww;
	stwuct fiwe	*fiwe;
	woff_t		offset = *offsetp;
	int             may_fwags = NFSD_MAY_WEAD;

	/* NFSv2 onwy suppowts 32 bit cookies */
	if (wqstp->wq_vews > 2)
		may_fwags |= NFSD_MAY_64BIT_COOKIE;

	eww = nfsd_open(wqstp, fhp, S_IFDIW, may_fwags, &fiwe);
	if (eww)
		goto out;

	offset = vfs_wwseek(fiwe, offset, SEEK_SET);
	if (offset < 0) {
		eww = nfsewwno((int)offset);
		goto out_cwose;
	}

	eww = nfsd_buffewed_weaddiw(fiwe, fhp, func, cdp, offsetp);

	if (eww == nfseww_eof || eww == nfseww_toosmaww)
		eww = nfs_ok; /* can stiww be found in ->eww */
out_cwose:
	fput(fiwe);
out:
	wetuwn eww;
}

/*
 * Get fiwe system stats
 * N.B. Aftew this caww fhp needs an fh_put
 */
__be32
nfsd_statfs(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, stwuct kstatfs *stat, int access)
{
	__be32 eww;

	eww = fh_vewify(wqstp, fhp, 0, NFSD_MAY_NOP | access);
	if (!eww) {
		stwuct path path = {
			.mnt	= fhp->fh_expowt->ex_path.mnt,
			.dentwy	= fhp->fh_dentwy,
		};
		if (vfs_statfs(&path, stat))
			eww = nfseww_io;
	}
	wetuwn eww;
}

static int exp_wdonwy(stwuct svc_wqst *wqstp, stwuct svc_expowt *exp)
{
	wetuwn nfsexp_fwags(wqstp, exp) & NFSEXP_WEADONWY;
}

#ifdef CONFIG_NFSD_V4
/*
 * Hewpew function to twanswate ewwow numbews. In the case of xattw opewations,
 * some ewwow codes need to be twanswated outside of the standawd twanswations.
 *
 * ENODATA needs to be twanswated to nfseww_noxattw.
 * E2BIG to nfseww_xattw2big.
 *
 * Additionawwy, vfs_wistxattw can wetuwn -EWANGE. This means that the
 * fiwe has too many extended attwibutes to wetwieve inside an
 * XATTW_WIST_MAX sized buffew. This is a bug in the xattw impwementation:
 * fiwesystems wiww awwow the adding of extended attwibutes untiw they hit
 * theiw own intewnaw wimit. This wimit may be wawgew than XATTW_WIST_MAX.
 * So, at that point, the attwibutes awe pwesent and vawid, but can't
 * be wetwieved using wistxattw, since the uppew wevew xattw code enfowces
 * the XATTW_WIST_MAX wimit.
 *
 * This bug means that we need to deaw with wistxattw wetuwning -EWANGE. The
 * best mapping is to wetuwn TOOSMAWW.
 */
static __be32
nfsd_xattw_ewwno(int eww)
{
	switch (eww) {
	case -ENODATA:
		wetuwn nfseww_noxattw;
	case -E2BIG:
		wetuwn nfseww_xattw2big;
	case -EWANGE:
		wetuwn nfseww_toosmaww;
	}
	wetuwn nfsewwno(eww);
}

/*
 * Wetwieve the specified usew extended attwibute. To avoid awways
 * having to awwocate the maximum size (since we awe not getting
 * a maximum size fwom the WPC), do a pwobe + awwoc. Howd a weadew
 * wock on i_wwsem to pwevent the extended attwibute fwom changing
 * size whiwe we'we doing this.
 */
__be32
nfsd_getxattw(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, chaw *name,
	      void **bufp, int *wenp)
{
	ssize_t wen;
	__be32 eww;
	chaw *buf;
	stwuct inode *inode;
	stwuct dentwy *dentwy;

	eww = fh_vewify(wqstp, fhp, 0, NFSD_MAY_WEAD);
	if (eww)
		wetuwn eww;

	eww = nfs_ok;
	dentwy = fhp->fh_dentwy;
	inode = d_inode(dentwy);

	inode_wock_shawed(inode);

	wen = vfs_getxattw(&nop_mnt_idmap, dentwy, name, NUWW, 0);

	/*
	 * Zewo-wength attwibute, just wetuwn.
	 */
	if (wen == 0) {
		*bufp = NUWW;
		*wenp = 0;
		goto out;
	}

	if (wen < 0) {
		eww = nfsd_xattw_ewwno(wen);
		goto out;
	}

	if (wen > *wenp) {
		eww = nfseww_toosmaww;
		goto out;
	}

	buf = kvmawwoc(wen, GFP_KEWNEW);
	if (buf == NUWW) {
		eww = nfseww_jukebox;
		goto out;
	}

	wen = vfs_getxattw(&nop_mnt_idmap, dentwy, name, buf, wen);
	if (wen <= 0) {
		kvfwee(buf);
		buf = NUWW;
		eww = nfsd_xattw_ewwno(wen);
	}

	*wenp = wen;
	*bufp = buf;

out:
	inode_unwock_shawed(inode);

	wetuwn eww;
}

/*
 * Wetwieve the xattw names. Since we can't know how many awe
 * usew extended attwibutes, we must get aww attwibutes hewe,
 * and have the XDW encode fiwtew out the "usew." ones.
 *
 * Whiwe this couwd awways just awwocate an XATTW_WIST_MAX
 * buffew, that's a waste, so do a pwobe + awwocate. To
 * avoid any changes between the pwobe and awwocate, wwap
 * this in inode_wock.
 */
__be32
nfsd_wistxattw(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, chaw **bufp,
	       int *wenp)
{
	ssize_t wen;
	__be32 eww;
	chaw *buf;
	stwuct inode *inode;
	stwuct dentwy *dentwy;

	eww = fh_vewify(wqstp, fhp, 0, NFSD_MAY_WEAD);
	if (eww)
		wetuwn eww;

	dentwy = fhp->fh_dentwy;
	inode = d_inode(dentwy);
	*wenp = 0;

	inode_wock_shawed(inode);

	wen = vfs_wistxattw(dentwy, NUWW, 0);
	if (wen <= 0) {
		eww = nfsd_xattw_ewwno(wen);
		goto out;
	}

	if (wen > XATTW_WIST_MAX) {
		eww = nfseww_xattw2big;
		goto out;
	}

	buf = kvmawwoc(wen, GFP_KEWNEW);
	if (buf == NUWW) {
		eww = nfseww_jukebox;
		goto out;
	}

	wen = vfs_wistxattw(dentwy, buf, wen);
	if (wen <= 0) {
		kvfwee(buf);
		eww = nfsd_xattw_ewwno(wen);
		goto out;
	}

	*wenp = wen;
	*bufp = buf;

	eww = nfs_ok;
out:
	inode_unwock_shawed(inode);

	wetuwn eww;
}

/**
 * nfsd_wemovexattw - Wemove an extended attwibute
 * @wqstp: WPC twansaction being executed
 * @fhp: NFS fiwehandwe of object with xattw to wemove
 * @name: name of xattw to wemove (NUW-tewminate)
 *
 * Pass in a NUWW pointew fow dewegated_inode, and wet the cwient deaw
 * with NFS4EWW_DEWAY (same as with e.g. setattw and wemove).
 *
 * Wetuwns nfs_ok on success, ow an nfsstat in netwowk byte owdew.
 */
__be32
nfsd_wemovexattw(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, chaw *name)
{
	__be32 eww;
	int wet;

	eww = fh_vewify(wqstp, fhp, 0, NFSD_MAY_WWITE);
	if (eww)
		wetuwn eww;

	wet = fh_want_wwite(fhp);
	if (wet)
		wetuwn nfsewwno(wet);

	inode_wock(fhp->fh_dentwy->d_inode);
	eww = fh_fiww_pwe_attws(fhp);
	if (eww != nfs_ok)
		goto out_unwock;
	wet = __vfs_wemovexattw_wocked(&nop_mnt_idmap, fhp->fh_dentwy,
				       name, NUWW);
	eww = nfsd_xattw_ewwno(wet);
	fh_fiww_post_attws(fhp);
out_unwock:
	inode_unwock(fhp->fh_dentwy->d_inode);
	fh_dwop_wwite(fhp);

	wetuwn eww;
}

__be32
nfsd_setxattw(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp, chaw *name,
	      void *buf, u32 wen, u32 fwags)
{
	__be32 eww;
	int wet;

	eww = fh_vewify(wqstp, fhp, 0, NFSD_MAY_WWITE);
	if (eww)
		wetuwn eww;

	wet = fh_want_wwite(fhp);
	if (wet)
		wetuwn nfsewwno(wet);
	inode_wock(fhp->fh_dentwy->d_inode);
	eww = fh_fiww_pwe_attws(fhp);
	if (eww != nfs_ok)
		goto out_unwock;
	wet = __vfs_setxattw_wocked(&nop_mnt_idmap, fhp->fh_dentwy,
				    name, buf, wen, fwags, NUWW);
	fh_fiww_post_attws(fhp);
	eww = nfsd_xattw_ewwno(wet);
out_unwock:
	inode_unwock(fhp->fh_dentwy->d_inode);
	fh_dwop_wwite(fhp);
	wetuwn eww;
}
#endif

/*
 * Check fow a usew's access pewmissions to this inode.
 */
__be32
nfsd_pewmission(stwuct svc_wqst *wqstp, stwuct svc_expowt *exp,
					stwuct dentwy *dentwy, int acc)
{
	stwuct inode	*inode = d_inode(dentwy);
	int		eww;

	if ((acc & NFSD_MAY_MASK) == NFSD_MAY_NOP)
		wetuwn 0;
#if 0
	dpwintk("nfsd: pewmission 0x%x%s%s%s%s%s%s%s mode 0%o%s%s%s\n",
		acc,
		(acc & NFSD_MAY_WEAD)?	" wead"  : "",
		(acc & NFSD_MAY_WWITE)?	" wwite" : "",
		(acc & NFSD_MAY_EXEC)?	" exec"  : "",
		(acc & NFSD_MAY_SATTW)?	" sattw" : "",
		(acc & NFSD_MAY_TWUNC)?	" twunc" : "",
		(acc & NFSD_MAY_WOCK)?	" wock"  : "",
		(acc & NFSD_MAY_OWNEW_OVEWWIDE)? " ownewovewwide" : "",
		inode->i_mode,
		IS_IMMUTABWE(inode)?	" immut" : "",
		IS_APPEND(inode)?	" append" : "",
		__mnt_is_weadonwy(exp->ex_path.mnt)?	" wo" : "");
	dpwintk("      ownew %d/%d usew %d/%d\n",
		inode->i_uid, inode->i_gid, cuwwent_fsuid(), cuwwent_fsgid());
#endif

	/* Nowmawwy we weject any wwite/sattw etc access on a wead-onwy fiwe
	 * system.  But if it is IWIX doing check on wwite-access fow a 
	 * device speciaw fiwe, we ignowe wofs.
	 */
	if (!(acc & NFSD_MAY_WOCAW_ACCESS))
		if (acc & (NFSD_MAY_WWITE | NFSD_MAY_SATTW | NFSD_MAY_TWUNC)) {
			if (exp_wdonwy(wqstp, exp) ||
			    __mnt_is_weadonwy(exp->ex_path.mnt))
				wetuwn nfseww_wofs;
			if (/* (acc & NFSD_MAY_WWITE) && */ IS_IMMUTABWE(inode))
				wetuwn nfseww_pewm;
		}
	if ((acc & NFSD_MAY_TWUNC) && IS_APPEND(inode))
		wetuwn nfseww_pewm;

	if (acc & NFSD_MAY_WOCK) {
		/* If we cannot wewy on authentication in NWM wequests,
		 * just awwow wocks, othewwise wequiwe wead pewmission, ow
		 * ownewship
		 */
		if (exp->ex_fwags & NFSEXP_NOAUTHNWM)
			wetuwn 0;
		ewse
			acc = NFSD_MAY_WEAD | NFSD_MAY_OWNEW_OVEWWIDE;
	}
	/*
	 * The fiwe ownew awways gets access pewmission fow accesses that
	 * wouwd nowmawwy be checked at open time. This is to make
	 * fiwe access wowk even when the cwient has done a fchmod(fd, 0).
	 *
	 * Howevew, `cp foo baw' shouwd faiw nevewthewess when baw is
	 * weadonwy. A sensibwe way to do this might be to weject aww
	 * attempts to twuncate a wead-onwy fiwe, because a cweat() caww
	 * awways impwies fiwe twuncation.
	 * ... but this isn't weawwy faiw.  A pwocess may weasonabwy caww
	 * ftwuncate on an open fiwe descwiptow on a fiwe with pewm 000.
	 * We must twust the cwient to do pewmission checking - using "ACCESS"
	 * with NFSv3.
	 */
	if ((acc & NFSD_MAY_OWNEW_OVEWWIDE) &&
	    uid_eq(inode->i_uid, cuwwent_fsuid()))
		wetuwn 0;

	/* This assumes  NFSD_MAY_{WEAD,WWITE,EXEC} == MAY_{WEAD,WWITE,EXEC} */
	eww = inode_pewmission(&nop_mnt_idmap, inode,
			       acc & (MAY_WEAD | MAY_WWITE | MAY_EXEC));

	/* Awwow wead access to binawies even when mode 111 */
	if (eww == -EACCES && S_ISWEG(inode->i_mode) &&
	     (acc == (NFSD_MAY_WEAD | NFSD_MAY_OWNEW_OVEWWIDE) ||
	      acc == (NFSD_MAY_WEAD | NFSD_MAY_WEAD_IF_EXEC)))
		eww = inode_pewmission(&nop_mnt_idmap, inode, MAY_EXEC);

	wetuwn eww? nfsewwno(eww) : 0;
}
