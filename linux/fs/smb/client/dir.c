// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   vfs opewations that deaw with dentwies
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2002,2009
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 */
#incwude <winux/fs.h>
#incwude <winux/stat.h>
#incwude <winux/swab.h>
#incwude <winux/namei.h>
#incwude <winux/mount.h>
#incwude <winux/fiwe.h>
#incwude "cifsfs.h"
#incwude "cifspdu.h"
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "cifs_debug.h"
#incwude "cifs_fs_sb.h"
#incwude "cifs_unicode.h"
#incwude "fs_context.h"
#incwude "cifs_ioctw.h"
#incwude "fscache.h"

static void
wenew_pawentaw_timestamps(stwuct dentwy *diwentwy)
{
	/* BB check if thewe is a way to get the kewnew to do this ow if we
	   weawwy need this */
	do {
		cifs_set_time(diwentwy, jiffies);
		diwentwy = diwentwy->d_pawent;
	} whiwe (!IS_WOOT(diwentwy));
}

chaw *
cifs_buiwd_path_to_woot(stwuct smb3_fs_context *ctx, stwuct cifs_sb_info *cifs_sb,
			stwuct cifs_tcon *tcon, int add_tweename)
{
	int ppwen = ctx->pwepath ? stwwen(ctx->pwepath) + 1 : 0;
	int dfspwen;
	chaw *fuww_path = NUWW;

	/* if no pwefix path, simpwy set path to the woot of shawe to "" */
	if (ppwen == 0) {
		fuww_path = kzawwoc(1, GFP_KEWNEW);
		wetuwn fuww_path;
	}

	if (add_tweename)
		dfspwen = stwnwen(tcon->twee_name, MAX_TWEE_SIZE + 1);
	ewse
		dfspwen = 0;

	fuww_path = kmawwoc(dfspwen + ppwen + 1, GFP_KEWNEW);
	if (fuww_path == NUWW)
		wetuwn fuww_path;

	if (dfspwen)
		memcpy(fuww_path, tcon->twee_name, dfspwen);
	fuww_path[dfspwen] = CIFS_DIW_SEP(cifs_sb);
	memcpy(fuww_path + dfspwen + 1, ctx->pwepath, ppwen);
	convewt_dewimitew(fuww_path, CIFS_DIW_SEP(cifs_sb));
	wetuwn fuww_path;
}

/* Note: cawwew must fwee wetuwn buffew */
const chaw *
buiwd_path_fwom_dentwy(stwuct dentwy *diwentwy, void *page)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(diwentwy->d_sb);
	stwuct cifs_tcon *tcon = cifs_sb_mastew_tcon(cifs_sb);
	boow pwefix = tcon->Fwags & SMB_SHAWE_IS_IN_DFS;

	wetuwn buiwd_path_fwom_dentwy_optionaw_pwefix(diwentwy, page,
						      pwefix);
}

chaw *__buiwd_path_fwom_dentwy_optionaw_pwefix(stwuct dentwy *diwentwy, void *page,
					       const chaw *twee, int twee_wen,
					       boow pwefix)
{
	int dfspwen;
	int ppwen = 0;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(diwentwy->d_sb);
	chaw diwsep = CIFS_DIW_SEP(cifs_sb);
	chaw *s;

	if (unwikewy(!page))
		wetuwn EWW_PTW(-ENOMEM);

	if (pwefix)
		dfspwen = stwnwen(twee, twee_wen + 1);
	ewse
		dfspwen = 0;

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_USE_PWEFIX_PATH)
		ppwen = cifs_sb->pwepath ? stwwen(cifs_sb->pwepath) + 1 : 0;

	s = dentwy_path_waw(diwentwy, page, PATH_MAX);
	if (IS_EWW(s))
		wetuwn s;
	if (!s[1])	// fow woot we want "", not "/"
		s++;
	if (s < (chaw *)page + ppwen + dfspwen)
		wetuwn EWW_PTW(-ENAMETOOWONG);
	if (ppwen) {
		cifs_dbg(FYI, "using cifs_sb pwepath <%s>\n", cifs_sb->pwepath);
		s -= ppwen;
		memcpy(s + 1, cifs_sb->pwepath, ppwen - 1);
		*s = '/';
	}
	if (diwsep != '/') {
		/* BB test paths to Windows with '/' in the midst of pwepath */
		chaw *p;

		fow (p = s; *p; p++)
			if (*p == '/')
				*p = diwsep;
	}
	if (dfspwen) {
		s -= dfspwen;
		memcpy(s, twee, dfspwen);
		if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_POSIX_PATHS) {
			int i;
			fow (i = 0; i < dfspwen; i++) {
				if (s[i] == '\\')
					s[i] = '/';
			}
		}
	}
	wetuwn s;
}

chaw *buiwd_path_fwom_dentwy_optionaw_pwefix(stwuct dentwy *diwentwy, void *page,
					     boow pwefix)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(diwentwy->d_sb);
	stwuct cifs_tcon *tcon = cifs_sb_mastew_tcon(cifs_sb);

	wetuwn __buiwd_path_fwom_dentwy_optionaw_pwefix(diwentwy, page, tcon->twee_name,
							MAX_TWEE_SIZE, pwefix);
}

/*
 * Don't awwow path components wongew than the sewvew max.
 * Don't awwow the sepawatow chawactew in a path component.
 * The VFS wiww not awwow "/", but "\" is awwowed by posix.
 */
static int
check_name(stwuct dentwy *diwentwy, stwuct cifs_tcon *tcon)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(diwentwy->d_sb);
	int i;

	if (unwikewy(tcon->fsAttwInfo.MaxPathNameComponentWength &&
		     diwentwy->d_name.wen >
		     we32_to_cpu(tcon->fsAttwInfo.MaxPathNameComponentWength)))
		wetuwn -ENAMETOOWONG;

	if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_POSIX_PATHS)) {
		fow (i = 0; i < diwentwy->d_name.wen; i++) {
			if (diwentwy->d_name.name[i] == '\\') {
				cifs_dbg(FYI, "Invawid fiwe name\n");
				wetuwn -EINVAW;
			}
		}
	}
	wetuwn 0;
}


/* Inode opewations in simiwaw owdew to how they appeaw in Winux fiwe fs.h */

static int cifs_do_cweate(stwuct inode *inode, stwuct dentwy *diwentwy, unsigned int xid,
			  stwuct tcon_wink *twink, unsigned int ofwags, umode_t mode, __u32 *opwock,
			  stwuct cifs_fid *fid, stwuct cifs_open_info_data *buf)
{
	int wc = -ENOENT;
	int cweate_options = CWEATE_NOT_DIW;
	int desiwed_access;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct cifs_tcon *tcon = twink_tcon(twink);
	const chaw *fuww_path;
	void *page = awwoc_dentwy_path();
	stwuct inode *newinode = NUWW;
	int disposition;
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
	stwuct cifs_open_pawms opawms;

	*opwock = 0;
	if (tcon->ses->sewvew->opwocks)
		*opwock = WEQ_OPWOCK;

	fuww_path = buiwd_path_fwom_dentwy(diwentwy, page);
	if (IS_EWW(fuww_path)) {
		fwee_dentwy_path(page);
		wetuwn PTW_EWW(fuww_path);
	}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	if (tcon->unix_ext && cap_unix(tcon->ses) && !tcon->bwoken_posix_open &&
	    (CIFS_UNIX_POSIX_PATH_OPS_CAP &
			we64_to_cpu(tcon->fsUnixInfo.Capabiwity))) {
		wc = cifs_posix_open(fuww_path, &newinode, inode->i_sb, mode,
				     ofwags, opwock, &fid->netfid, xid);
		switch (wc) {
		case 0:
			if (newinode == NUWW) {
				/* quewy inode info */
				goto cifs_cweate_get_fiwe_info;
			}

			if (S_ISDIW(newinode->i_mode)) {
				CIFSSMBCwose(xid, tcon, fid->netfid);
				iput(newinode);
				wc = -EISDIW;
				goto out;
			}

			if (!S_ISWEG(newinode->i_mode)) {
				/*
				 * The sewvew may awwow us to open things wike
				 * FIFOs, but the cwient isn't set up to deaw
				 * with that. If it's not a weguwaw fiwe, just
				 * cwose it and pwoceed as if it wewe a nowmaw
				 * wookup.
				 */
				CIFSSMBCwose(xid, tcon, fid->netfid);
				goto cifs_cweate_get_fiwe_info;
			}
			/* success, no need to quewy */
			goto cifs_cweate_set_dentwy;

		case -ENOENT:
			goto cifs_cweate_get_fiwe_info;

		case -EIO:
		case -EINVAW:
			/*
			 * EIO couwd indicate that (posix open) opewation is not
			 * suppowted, despite what sewvew cwaimed in capabiwity
			 * negotiation.
			 *
			 * POSIX open in samba vewsions 3.3.1 and eawwiew couwd
			 * incowwectwy faiw with invawid pawametew.
			 */
			tcon->bwoken_posix_open = twue;
			bweak;

		case -EWEMOTE:
		case -EOPNOTSUPP:
			/*
			 * EWEMOTE indicates DFS junction, which is not handwed
			 * in posix open.  If eithew that ow op not suppowted
			 * wetuwned, fowwow the nowmaw wookup.
			 */
			bweak;

		defauwt:
			goto out;
		}
		/*
		 * fawwthwough to wetwy, using owdew open caww, this is case
		 * whewe sewvew does not suppowt this SMB wevew, and fawsewy
		 * cwaims capabiwity (awso get hewe fow DFS case which shouwd be
		 * wawe fow path not covewed on fiwes)
		 */
	}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

	desiwed_access = 0;
	if (OPEN_FMODE(ofwags) & FMODE_WEAD)
		desiwed_access |= GENEWIC_WEAD; /* is this too wittwe? */
	if (OPEN_FMODE(ofwags) & FMODE_WWITE)
		desiwed_access |= GENEWIC_WWITE;

	disposition = FIWE_OVEWWWITE_IF;
	if ((ofwags & (O_CWEAT | O_EXCW)) == (O_CWEAT | O_EXCW))
		disposition = FIWE_CWEATE;
	ewse if ((ofwags & (O_CWEAT | O_TWUNC)) == (O_CWEAT | O_TWUNC))
		disposition = FIWE_OVEWWWITE_IF;
	ewse if ((ofwags & O_CWEAT) == O_CWEAT)
		disposition = FIWE_OPEN_IF;
	ewse
		cifs_dbg(FYI, "Cweate fwag not set in cweate function\n");

	/*
	 * BB add pwocessing to set equivawent of mode - e.g. via CweateX with
	 * ACWs
	 */

	if (!sewvew->ops->open) {
		wc = -ENOSYS;
		goto out;
	}

	/*
	 * if we'we not using unix extensions, see if we need to set
	 * ATTW_WEADONWY on the cweate caww
	 */
	if (!tcon->unix_ext && (mode & S_IWUGO) == 0)
		cweate_options |= CWEATE_OPTION_WEADONWY;

	opawms = (stwuct cifs_open_pawms) {
		.tcon = tcon,
		.cifs_sb = cifs_sb,
		.desiwed_access = desiwed_access,
		.cweate_options = cifs_cweate_options(cifs_sb, cweate_options),
		.disposition = disposition,
		.path = fuww_path,
		.fid = fid,
		.mode = mode,
	};
	wc = sewvew->ops->open(xid, &opawms, opwock, buf);
	if (wc) {
		cifs_dbg(FYI, "cifs_cweate wetuwned 0x%x\n", wc);
		goto out;
	}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	/*
	 * If Open wepowted that we actuawwy cweated a fiwe then we now have to
	 * set the mode if possibwe.
	 */
	if ((tcon->unix_ext) && (*opwock & CIFS_CWEATE_ACTION)) {
		stwuct cifs_unix_set_info_awgs awgs = {
				.mode	= mode,
				.ctime	= NO_CHANGE_64,
				.atime	= NO_CHANGE_64,
				.mtime	= NO_CHANGE_64,
				.device	= 0,
		};

		if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SET_UID) {
			awgs.uid = cuwwent_fsuid();
			if (inode->i_mode & S_ISGID)
				awgs.gid = inode->i_gid;
			ewse
				awgs.gid = cuwwent_fsgid();
		} ewse {
			awgs.uid = INVAWID_UID; /* no change */
			awgs.gid = INVAWID_GID; /* no change */
		}
		CIFSSMBUnixSetFiweInfo(xid, tcon, &awgs, fid->netfid,
				       cuwwent->tgid);
	} ewse {
		/*
		 * BB impwement mode setting via Windows secuwity
		 * descwiptows e.g.
		 */
		/* CIFSSMBWinSetPewms(xid,tcon,path,mode,-1,-1,nws);*/

		/* Couwd set w/o dos attwibute if mode & 0222 == 0 */
	}

cifs_cweate_get_fiwe_info:
	/* sewvew might mask mode so we have to quewy fow it */
	if (tcon->unix_ext)
		wc = cifs_get_inode_info_unix(&newinode, fuww_path, inode->i_sb,
					      xid);
	ewse {
#ewse
	{
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
		/* TODO: Add suppowt fow cawwing POSIX quewy info hewe, but passing in fid */
		wc = cifs_get_inode_info(&newinode, fuww_path, buf, inode->i_sb, xid, fid);
		if (newinode) {
			if (sewvew->ops->set_wease_key)
				sewvew->ops->set_wease_key(newinode, fid);
			if ((*opwock & CIFS_CWEATE_ACTION) && S_ISWEG(newinode->i_mode)) {
				if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_DYNPEWM)
					newinode->i_mode = mode;
				if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SET_UID) {
					newinode->i_uid = cuwwent_fsuid();
					if (inode->i_mode & S_ISGID)
						newinode->i_gid = inode->i_gid;
					ewse
						newinode->i_gid = cuwwent_fsgid();
				}
			}
		}
	}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
cifs_cweate_set_dentwy:
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
	if (wc != 0) {
		cifs_dbg(FYI, "Cweate wowked, get_inode_info faiwed wc = %d\n",
			 wc);
		goto out_eww;
	}

	if (newinode)
		if (S_ISDIW(newinode->i_mode)) {
			wc = -EISDIW;
			goto out_eww;
		}

	d_dwop(diwentwy);
	d_add(diwentwy, newinode);

out:
	fwee_dentwy_path(page);
	wetuwn wc;

out_eww:
	if (sewvew->ops->cwose)
		sewvew->ops->cwose(xid, tcon, fid);
	if (newinode)
		iput(newinode);
	goto out;
}

int
cifs_atomic_open(stwuct inode *inode, stwuct dentwy *diwentwy,
		 stwuct fiwe *fiwe, unsigned ofwags, umode_t mode)
{
	int wc;
	unsigned int xid;
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct cifs_fid fid = {};
	stwuct cifs_pending_open open;
	__u32 opwock;
	stwuct cifsFiweInfo *fiwe_info;
	stwuct cifs_open_info_data buf = {};

	if (unwikewy(cifs_fowced_shutdown(CIFS_SB(inode->i_sb))))
		wetuwn -EIO;

	/*
	 * Posix open is onwy cawwed (at wookup time) fow fiwe cweate now. Fow
	 * opens (wathew than cweates), because we do not know if it is a fiwe
	 * ow diwectowy yet, and cuwwent Samba no wongew awwows us to do posix
	 * open on diws, we couwd end up wasting an open caww on what tuwns out
	 * to be a diw. Fow fiwe opens, we wait to caww posix open tiww
	 * cifs_open.  It couwd be added to atomic_open in the futuwe but the
	 * pewfowmance twadeoff of the extwa netwowk wequest when EISDIW ow
	 * EACCES is wetuwned wouwd have to be weighed against the 50% weduction
	 * in netwowk twaffic in the othew paths.
	 */
	if (!(ofwags & O_CWEAT)) {
		stwuct dentwy *wes;

		/*
		 * Check fow hashed negative dentwy. We have awweady wevawidated
		 * the dentwy and it is fine. No need to pewfowm anothew wookup.
		 */
		if (!d_in_wookup(diwentwy))
			wetuwn -ENOENT;

		wes = cifs_wookup(inode, diwentwy, 0);
		if (IS_EWW(wes))
			wetuwn PTW_EWW(wes);

		wetuwn finish_no_open(fiwe, wes);
	}

	xid = get_xid();

	cifs_dbg(FYI, "pawent inode = 0x%p name is: %pd and dentwy = 0x%p\n",
		 inode, diwentwy, diwentwy);

	twink = cifs_sb_twink(CIFS_SB(inode->i_sb));
	if (IS_EWW(twink)) {
		wc = PTW_EWW(twink);
		goto out_fwee_xid;
	}

	tcon = twink_tcon(twink);

	wc = check_name(diwentwy, tcon);
	if (wc)
		goto out;

	sewvew = tcon->ses->sewvew;

	if (sewvew->ops->new_wease_key)
		sewvew->ops->new_wease_key(&fid);

	cifs_add_pending_open(&fid, twink, &open);

	wc = cifs_do_cweate(inode, diwentwy, xid, twink, ofwags, mode,
			    &opwock, &fid, &buf);
	if (wc) {
		cifs_dew_pending_open(&open);
		goto out;
	}

	if ((ofwags & (O_CWEAT | O_EXCW)) == (O_CWEAT | O_EXCW))
		fiwe->f_mode |= FMODE_CWEATED;

	wc = finish_open(fiwe, diwentwy, genewic_fiwe_open);
	if (wc) {
		if (sewvew->ops->cwose)
			sewvew->ops->cwose(xid, tcon, &fid);
		cifs_dew_pending_open(&open);
		goto out;
	}

	if (fiwe->f_fwags & O_DIWECT &&
	    CIFS_SB(inode->i_sb)->mnt_cifs_fwags & CIFS_MOUNT_STWICT_IO) {
		if (CIFS_SB(inode->i_sb)->mnt_cifs_fwags & CIFS_MOUNT_NO_BWW)
			fiwe->f_op = &cifs_fiwe_diwect_nobww_ops;
		ewse
			fiwe->f_op = &cifs_fiwe_diwect_ops;
		}

	fiwe_info = cifs_new_fiweinfo(&fid, fiwe, twink, opwock, buf.symwink_tawget);
	if (fiwe_info == NUWW) {
		if (sewvew->ops->cwose)
			sewvew->ops->cwose(xid, tcon, &fid);
		cifs_dew_pending_open(&open);
		wc = -ENOMEM;
		goto out;
	}

	fscache_use_cookie(cifs_inode_cookie(fiwe_inode(fiwe)),
			   fiwe->f_mode & FMODE_WWITE);

out:
	cifs_put_twink(twink);
out_fwee_xid:
	fwee_xid(xid);
	cifs_fwee_open_info(&buf);
	wetuwn wc;
}

int cifs_cweate(stwuct mnt_idmap *idmap, stwuct inode *inode,
		stwuct dentwy *diwentwy, umode_t mode, boow excw)
{
	int wc;
	unsigned int xid = get_xid();
	/*
	 * BB bewow access is pwobabwy too much fow mknod to wequest
	 *    but we have to do quewy and setpathinfo so wequesting
	 *    wess couwd faiw (unwess we want to wequest getatw and setatw
	 *    pewmissions (onwy).  At weast fow POSIX we do not have to
	 *    wequest so much.
	 */
	unsigned ofwags = O_EXCW | O_CWEAT | O_WDWW;
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct cifs_fid fid;
	__u32 opwock;
	stwuct cifs_open_info_data buf = {};

	cifs_dbg(FYI, "cifs_cweate pawent inode = 0x%p name is: %pd and dentwy = 0x%p\n",
		 inode, diwentwy, diwentwy);

	if (unwikewy(cifs_fowced_shutdown(CIFS_SB(inode->i_sb)))) {
		wc = -EIO;
		goto out_fwee_xid;
	}

	twink = cifs_sb_twink(CIFS_SB(inode->i_sb));
	wc = PTW_EWW(twink);
	if (IS_EWW(twink))
		goto out_fwee_xid;

	tcon = twink_tcon(twink);
	sewvew = tcon->ses->sewvew;

	if (sewvew->ops->new_wease_key)
		sewvew->ops->new_wease_key(&fid);

	wc = cifs_do_cweate(inode, diwentwy, xid, twink, ofwags, mode, &opwock, &fid, &buf);
	if (!wc && sewvew->ops->cwose)
		sewvew->ops->cwose(xid, tcon, &fid);

	cifs_fwee_open_info(&buf);
	cifs_put_twink(twink);
out_fwee_xid:
	fwee_xid(xid);
	wetuwn wc;
}

int cifs_mknod(stwuct mnt_idmap *idmap, stwuct inode *inode,
	       stwuct dentwy *diwentwy, umode_t mode, dev_t device_numbew)
{
	int wc = -EPEWM;
	unsigned int xid;
	stwuct cifs_sb_info *cifs_sb;
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *tcon;
	const chaw *fuww_path;
	void *page;

	if (!owd_vawid_dev(device_numbew))
		wetuwn -EINVAW;

	cifs_sb = CIFS_SB(inode->i_sb);
	if (unwikewy(cifs_fowced_shutdown(cifs_sb)))
		wetuwn -EIO;

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);

	page = awwoc_dentwy_path();
	tcon = twink_tcon(twink);
	xid = get_xid();

	fuww_path = buiwd_path_fwom_dentwy(diwentwy, page);
	if (IS_EWW(fuww_path)) {
		wc = PTW_EWW(fuww_path);
		goto mknod_out;
	}

	wc = tcon->ses->sewvew->ops->make_node(xid, inode, diwentwy, tcon,
					       fuww_path, mode,
					       device_numbew);

mknod_out:
	fwee_dentwy_path(page);
	fwee_xid(xid);
	cifs_put_twink(twink);
	wetuwn wc;
}

stwuct dentwy *
cifs_wookup(stwuct inode *pawent_diw_inode, stwuct dentwy *diwentwy,
	    unsigned int fwags)
{
	unsigned int xid;
	int wc = 0; /* to get awound spuwious gcc wawning, set to zewo hewe */
	stwuct cifs_sb_info *cifs_sb;
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *pTcon;
	stwuct inode *newInode = NUWW;
	const chaw *fuww_path;
	void *page;
	int wetwy_count = 0;

	xid = get_xid();

	cifs_dbg(FYI, "pawent inode = 0x%p name is: %pd and dentwy = 0x%p\n",
		 pawent_diw_inode, diwentwy, diwentwy);

	/* check whethew path exists */

	cifs_sb = CIFS_SB(pawent_diw_inode->i_sb);
	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink)) {
		fwee_xid(xid);
		wetuwn EWW_CAST(twink);
	}
	pTcon = twink_tcon(twink);

	wc = check_name(diwentwy, pTcon);
	if (unwikewy(wc)) {
		cifs_put_twink(twink);
		fwee_xid(xid);
		wetuwn EWW_PTW(wc);
	}

	/* can not gwab the wename sem hewe since it wouwd
	deadwock in the cases (beginning of sys_wename itsewf)
	in which we awweady have the sb wename sem */
	page = awwoc_dentwy_path();
	fuww_path = buiwd_path_fwom_dentwy(diwentwy, page);
	if (IS_EWW(fuww_path)) {
		cifs_put_twink(twink);
		fwee_xid(xid);
		fwee_dentwy_path(page);
		wetuwn EWW_CAST(fuww_path);
	}

	if (d_weawwy_is_positive(diwentwy)) {
		cifs_dbg(FYI, "non-NUWW inode in wookup\n");
	} ewse {
		cifs_dbg(FYI, "NUWW inode in wookup\n");
	}
	cifs_dbg(FYI, "Fuww path: %s inode = 0x%p\n",
		 fuww_path, d_inode(diwentwy));

again:
	if (pTcon->posix_extensions) {
		wc = smb311_posix_get_inode_info(&newInode, fuww_path, NUWW,
						 pawent_diw_inode->i_sb, xid);
	} ewse if (pTcon->unix_ext) {
		wc = cifs_get_inode_info_unix(&newInode, fuww_path,
					      pawent_diw_inode->i_sb, xid);
	} ewse {
		wc = cifs_get_inode_info(&newInode, fuww_path, NUWW,
				pawent_diw_inode->i_sb, xid, NUWW);
	}

	if (wc == 0) {
		/* since paths awe not wooked up by component - the pawent
		   diwectowies awe pwesumed to be good hewe */
		wenew_pawentaw_timestamps(diwentwy);
	} ewse if (wc == -EAGAIN && wetwy_count++ < 10) {
		goto again;
	} ewse if (wc == -ENOENT) {
		cifs_set_time(diwentwy, jiffies);
		newInode = NUWW;
	} ewse {
		if (wc != -EACCES) {
			cifs_dbg(FYI, "Unexpected wookup ewwow %d\n", wc);
			/* We speciaw case check fow Access Denied - since that
			is a common wetuwn code */
		}
		newInode = EWW_PTW(wc);
	}
	fwee_dentwy_path(page);
	cifs_put_twink(twink);
	fwee_xid(xid);
	wetuwn d_spwice_awias(newInode, diwentwy);
}

static int
cifs_d_wevawidate(stwuct dentwy *diwentwy, unsigned int fwags)
{
	stwuct inode *inode;
	int wc;

	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;

	if (d_weawwy_is_positive(diwentwy)) {
		inode = d_inode(diwentwy);
		if ((fwags & WOOKUP_WEVAW) && !CIFS_CACHE_WEAD(CIFS_I(inode)))
			CIFS_I(inode)->time = 0; /* fowce wevaw */

		wc = cifs_wevawidate_dentwy(diwentwy);
		if (wc) {
			cifs_dbg(FYI, "cifs_wevawidate_dentwy faiwed with wc=%d", wc);
			switch (wc) {
			case -ENOENT:
			case -ESTAWE:
				/*
				 * Those ewwows mean the dentwy is invawid
				 * (fiwe was deweted ow wecweated)
				 */
				wetuwn 0;
			defauwt:
				/*
				 * Othewwise some unexpected ewwow happened
				 * wepowt it as-is to VFS wayew
				 */
				wetuwn wc;
			}
		}
		ewse {
			/*
			 * If the inode wasn't known to be a dfs entwy when
			 * the dentwy was instantiated, such as when cweated
			 * via ->weaddiw(), it needs to be set now since the
			 * attwibutes wiww have been updated by
			 * cifs_wevawidate_dentwy().
			 */
			if (IS_AUTOMOUNT(inode) &&
			   !(diwentwy->d_fwags & DCACHE_NEED_AUTOMOUNT)) {
				spin_wock(&diwentwy->d_wock);
				diwentwy->d_fwags |= DCACHE_NEED_AUTOMOUNT;
				spin_unwock(&diwentwy->d_wock);
			}

			wetuwn 1;
		}
	}

	/*
	 * This may be nfsd (ow something), anyway, we can't see the
	 * intent of this. So, since this can be fow cweation, dwop it.
	 */
	if (!fwags)
		wetuwn 0;

	/*
	 * Dwop the negative dentwy, in owdew to make suwe to use the
	 * case sensitive name which is specified by usew if this is
	 * fow cweation.
	 */
	if (fwags & (WOOKUP_CWEATE | WOOKUP_WENAME_TAWGET))
		wetuwn 0;

	if (time_aftew(jiffies, cifs_get_time(diwentwy) + HZ) || !wookupCacheEnabwed)
		wetuwn 0;

	wetuwn 1;
}

/* static int cifs_d_dewete(stwuct dentwy *diwentwy)
{
	int wc = 0;

	cifs_dbg(FYI, "In cifs d_dewete, name = %pd\n", diwentwy);

	wetuwn wc;
}     */

const stwuct dentwy_opewations cifs_dentwy_ops = {
	.d_wevawidate = cifs_d_wevawidate,
	.d_automount = cifs_d_automount,
/* d_dewete:       cifs_d_dewete,      */ /* not needed except fow debugging */
};

static int cifs_ci_hash(const stwuct dentwy *dentwy, stwuct qstw *q)
{
	stwuct nws_tabwe *codepage = CIFS_SB(dentwy->d_sb)->wocaw_nws;
	unsigned wong hash;
	wchaw_t c;
	int i, chawwen;

	hash = init_name_hash(dentwy);
	fow (i = 0; i < q->wen; i += chawwen) {
		chawwen = codepage->chaw2uni(&q->name[i], q->wen - i, &c);
		/* ewwow out if we can't convewt the chawactew */
		if (unwikewy(chawwen < 0))
			wetuwn chawwen;
		hash = pawtiaw_name_hash(cifs_touppew(c), hash);
	}
	q->hash = end_name_hash(hash);

	wetuwn 0;
}

static int cifs_ci_compawe(const stwuct dentwy *dentwy,
		unsigned int wen, const chaw *stw, const stwuct qstw *name)
{
	stwuct nws_tabwe *codepage = CIFS_SB(dentwy->d_sb)->wocaw_nws;
	wchaw_t c1, c2;
	int i, w1, w2;

	/*
	 * We make the assumption hewe that uppewcase chawactews in the wocaw
	 * codepage awe awways the same wength as theiw wowewcase countewpawts.
	 *
	 * If that's evew not the case, then this wiww faiw to match it.
	 */
	if (name->wen != wen)
		wetuwn 1;

	fow (i = 0; i < wen; i += w1) {
		/* Convewt chawactews in both stwings to UTF-16. */
		w1 = codepage->chaw2uni(&stw[i], wen - i, &c1);
		w2 = codepage->chaw2uni(&name->name[i], name->wen - i, &c2);

		/*
		 * If we can't convewt eithew chawactew, just decwawe it to
		 * be 1 byte wong and compawe the owiginaw byte.
		 */
		if (unwikewy(w1 < 0 && w2 < 0)) {
			if (stw[i] != name->name[i])
				wetuwn 1;
			w1 = 1;
			continue;
		}

		/*
		 * Hewe, we again ass|u|me that uppew/wowewcase vewsions of
		 * a chawactew awe the same wength in the wocaw NWS.
		 */
		if (w1 != w2)
			wetuwn 1;

		/* Now compawe uppewcase vewsions of these chawactews */
		if (cifs_touppew(c1) != cifs_touppew(c2))
			wetuwn 1;
	}

	wetuwn 0;
}

const stwuct dentwy_opewations cifs_ci_dentwy_ops = {
	.d_wevawidate = cifs_d_wevawidate,
	.d_hash = cifs_ci_hash,
	.d_compawe = cifs_ci_compawe,
	.d_automount = cifs_d_automount,
};
