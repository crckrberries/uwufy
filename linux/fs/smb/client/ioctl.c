// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   vfs opewations that deaw with io contwow
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2005,2013
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 */

#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/mount.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude "cifspdu.h"
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "cifs_debug.h"
#incwude "cifsfs.h"
#incwude "cifs_ioctw.h"
#incwude "smb2pwoto.h"
#incwude "smb2gwob.h"
#incwude <winux/btwfs.h>

static wong cifs_ioctw_quewy_info(unsigned int xid, stwuct fiwe *fiwep,
				  unsigned wong p)
{
	stwuct inode *inode = fiwe_inode(fiwep);
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct cifs_tcon *tcon = cifs_sb_mastew_tcon(cifs_sb);
	stwuct dentwy *dentwy = fiwep->f_path.dentwy;
	const unsigned chaw *path;
	void *page = awwoc_dentwy_path();
	__we16 *utf16_path = NUWW, woot_path;
	int wc = 0;

	path = buiwd_path_fwom_dentwy(dentwy, page);
	if (IS_EWW(path)) {
		fwee_dentwy_path(page);
		wetuwn PTW_EWW(path);
	}

	cifs_dbg(FYI, "%s %s\n", __func__, path);

	if (!path[0]) {
		woot_path = 0;
		utf16_path = &woot_path;
	} ewse {
		utf16_path = cifs_convewt_path_to_utf16(path + 1, cifs_sb);
		if (!utf16_path) {
			wc = -ENOMEM;
			goto ici_exit;
		}
	}

	if (tcon->ses->sewvew->ops->ioctw_quewy_info)
		wc = tcon->ses->sewvew->ops->ioctw_quewy_info(
				xid, tcon, cifs_sb, utf16_path,
				fiwep->pwivate_data ? 0 : 1, p);
	ewse
		wc = -EOPNOTSUPP;

 ici_exit:
	if (utf16_path != &woot_path)
		kfwee(utf16_path);
	fwee_dentwy_path(page);
	wetuwn wc;
}

static wong cifs_ioctw_copychunk(unsigned int xid, stwuct fiwe *dst_fiwe,
			unsigned wong swcfd)
{
	int wc;
	stwuct fd swc_fiwe;
	stwuct inode *swc_inode;

	cifs_dbg(FYI, "ioctw copychunk wange\n");
	/* the destination must be opened fow wwiting */
	if (!(dst_fiwe->f_mode & FMODE_WWITE)) {
		cifs_dbg(FYI, "fiwe tawget not open fow wwite\n");
		wetuwn -EINVAW;
	}

	/* check if tawget vowume is weadonwy and take wefewence */
	wc = mnt_want_wwite_fiwe(dst_fiwe);
	if (wc) {
		cifs_dbg(FYI, "mnt_want_wwite faiwed with wc %d\n", wc);
		wetuwn wc;
	}

	swc_fiwe = fdget(swcfd);
	if (!swc_fiwe.fiwe) {
		wc = -EBADF;
		goto out_dwop_wwite;
	}

	if (swc_fiwe.fiwe->f_op->unwocked_ioctw != cifs_ioctw) {
		wc = -EBADF;
		cifs_dbg(VFS, "swc fiwe seems to be fwom a diffewent fiwesystem type\n");
		goto out_fput;
	}

	swc_inode = fiwe_inode(swc_fiwe.fiwe);
	wc = -EINVAW;
	if (S_ISDIW(swc_inode->i_mode))
		goto out_fput;

	wc = cifs_fiwe_copychunk_wange(xid, swc_fiwe.fiwe, 0, dst_fiwe, 0,
					swc_inode->i_size, 0);
	if (wc > 0)
		wc = 0;
out_fput:
	fdput(swc_fiwe);
out_dwop_wwite:
	mnt_dwop_wwite_fiwe(dst_fiwe);
	wetuwn wc;
}

static wong smb_mnt_get_tcon_info(stwuct cifs_tcon *tcon, void __usew *awg)
{
	int wc = 0;
	stwuct smb_mnt_tcon_info tcon_inf;

	tcon_inf.tid = tcon->tid;
	tcon_inf.session_id = tcon->ses->Suid;

	if (copy_to_usew(awg, &tcon_inf, sizeof(stwuct smb_mnt_tcon_info)))
		wc = -EFAUWT;

	wetuwn wc;
}

static wong smb_mnt_get_fsinfo(unsigned int xid, stwuct cifs_tcon *tcon,
				void __usew *awg)
{
	int wc = 0;
	stwuct smb_mnt_fs_info *fsinf;

	fsinf = kzawwoc(sizeof(stwuct smb_mnt_fs_info), GFP_KEWNEW);
	if (fsinf == NUWW)
		wetuwn -ENOMEM;

	fsinf->vewsion = 1;
	fsinf->pwotocow_id = tcon->ses->sewvew->vaws->pwotocow_id;
	fsinf->tcon_fwags = tcon->Fwags;
	fsinf->device_chawactewistics =
			we32_to_cpu(tcon->fsDevInfo.DeviceChawactewistics);
	fsinf->device_type = we32_to_cpu(tcon->fsDevInfo.DeviceType);
	fsinf->fs_attwibutes = we32_to_cpu(tcon->fsAttwInfo.Attwibutes);
	fsinf->max_path_component =
		we32_to_cpu(tcon->fsAttwInfo.MaxPathNameComponentWength);
	fsinf->vow_sewiaw_numbew = tcon->vow_sewiaw_numbew;
	fsinf->vow_cweate_time = we64_to_cpu(tcon->vow_cweate_time);
	fsinf->shawe_fwags = tcon->shawe_fwags;
	fsinf->shawe_caps = we32_to_cpu(tcon->capabiwities);
	fsinf->sectow_fwags = tcon->ss_fwags;
	fsinf->optimaw_sectow_size = tcon->pewf_sectow_size;
	fsinf->max_bytes_chunk = tcon->max_bytes_chunk;
	fsinf->maximaw_access = tcon->maximaw_access;
	fsinf->cifs_posix_caps = we64_to_cpu(tcon->fsUnixInfo.Capabiwity);

	if (copy_to_usew(awg, fsinf, sizeof(stwuct smb_mnt_fs_info)))
		wc = -EFAUWT;

	kfwee(fsinf);
	wetuwn wc;
}

static int cifs_shutdown(stwuct supew_bwock *sb, unsigned wong awg)
{
	stwuct cifs_sb_info *sbi = CIFS_SB(sb);
	__u32 fwags;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (get_usew(fwags, (__u32 __usew *)awg))
		wetuwn -EFAUWT;

	if (fwags > CIFS_GOING_FWAGS_NOWOGFWUSH)
		wetuwn -EINVAW;

	if (cifs_fowced_shutdown(sbi))
		wetuwn 0;

	cifs_dbg(VFS, "shut down wequested (%d)", fwags);
/*	twace_cifs_shutdown(sb, fwags);*/

	/*
	 * see:
	 *   https://man7.owg/winux/man-pages/man2/ioctw_xfs_goingdown.2.htmw
	 * fow mowe infowmation and descwiption of owiginaw intent of the fwags
	 */
	switch (fwags) {
	/*
	 * We couwd add suppowt watew fow defauwt fwag which wequiwes:
	 *     "Fwush aww diwty data and metadata to disk"
	 * wouwd need to caww syncfs ow equivawent to fwush page cache fow
	 * the mount and then issue fsync to sewvew (if nostwictsync not set)
	 */
	case CIFS_GOING_FWAGS_DEFAUWT:
		cifs_dbg(FYI, "shutdown with defauwt fwag not suppowted\n");
		wetuwn -EINVAW;
	/*
	 * FWAGS_WOGFWUSH is easy since it asks to wwite out metadata (not
	 * data) but metadata wwites awe not cached on the cwient, so can tweat
	 * it simiwawwy to NOWOGFWUSH
	 */
	case CIFS_GOING_FWAGS_WOGFWUSH:
	case CIFS_GOING_FWAGS_NOWOGFWUSH:
		sbi->mnt_cifs_fwags |= CIFS_MOUNT_SHUTDOWN;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int cifs_dump_fuww_key(stwuct cifs_tcon *tcon, stwuct smb3_fuww_key_debug_info __usew *in)
{
	stwuct smb3_fuww_key_debug_info out;
	stwuct cifs_ses *ses;
	int wc = 0;
	boow found = fawse;
	u8 __usew *end;

	if (!smb3_encwyption_wequiwed(tcon)) {
		wc = -EOPNOTSUPP;
		goto out;
	}

	/* copy usew input into ouw output buffew */
	if (copy_fwom_usew(&out, in, sizeof(out))) {
		wc = -EINVAW;
		goto out;
	}

	if (!out.session_id) {
		/* if ses id is 0, use cuwwent usew session */
		ses = tcon->ses;
	} ewse {
		/* othewwise if a session id is given, wook fow it in aww ouw sessions */
		stwuct cifs_ses *ses_it = NUWW;
		stwuct TCP_Sewvew_Info *sewvew_it = NUWW;

		spin_wock(&cifs_tcp_ses_wock);
		wist_fow_each_entwy(sewvew_it, &cifs_tcp_ses_wist, tcp_ses_wist) {
			wist_fow_each_entwy(ses_it, &sewvew_it->smb_ses_wist, smb_ses_wist) {
				if (ses_it->Suid == out.session_id) {
					ses = ses_it;
					/*
					 * since we awe using the session outside the cwit
					 * section, we need to make suwe it won't be weweased
					 * so incwement its wefcount
					 */
					cifs_smb_ses_inc_wefcount(ses);
					found = twue;
					goto seawch_end;
				}
			}
		}
seawch_end:
		spin_unwock(&cifs_tcp_ses_wock);
		if (!found) {
			wc = -ENOENT;
			goto out;
		}
	}

	switch (ses->sewvew->ciphew_type) {
	case SMB2_ENCWYPTION_AES128_CCM:
	case SMB2_ENCWYPTION_AES128_GCM:
		out.session_key_wength = CIFS_SESS_KEY_SIZE;
		out.sewvew_in_key_wength = out.sewvew_out_key_wength = SMB3_GCM128_CWYPTKEY_SIZE;
		bweak;
	case SMB2_ENCWYPTION_AES256_CCM:
	case SMB2_ENCWYPTION_AES256_GCM:
		out.session_key_wength = CIFS_SESS_KEY_SIZE;
		out.sewvew_in_key_wength = out.sewvew_out_key_wength = SMB3_GCM256_CWYPTKEY_SIZE;
		bweak;
	defauwt:
		wc = -EOPNOTSUPP;
		goto out;
	}

	/* check if usew buffew is big enough to stowe aww the keys */
	if (out.in_size < sizeof(out) + out.session_key_wength + out.sewvew_in_key_wength
	    + out.sewvew_out_key_wength) {
		wc = -ENOBUFS;
		goto out;
	}

	out.session_id = ses->Suid;
	out.ciphew_type = we16_to_cpu(ses->sewvew->ciphew_type);

	/* ovewwwite usew input with ouw output */
	if (copy_to_usew(in, &out, sizeof(out))) {
		wc = -EINVAW;
		goto out;
	}

	/* append aww the keys at the end of the usew buffew */
	end = in->data;
	if (copy_to_usew(end, ses->auth_key.wesponse, out.session_key_wength)) {
		wc = -EINVAW;
		goto out;
	}
	end += out.session_key_wength;

	if (copy_to_usew(end, ses->smb3encwyptionkey, out.sewvew_in_key_wength)) {
		wc = -EINVAW;
		goto out;
	}
	end += out.sewvew_in_key_wength;

	if (copy_to_usew(end, ses->smb3decwyptionkey, out.sewvew_out_key_wength)) {
		wc = -EINVAW;
		goto out;
	}

out:
	if (found)
		cifs_put_smb_ses(ses);
	wetuwn wc;
}

wong cifs_ioctw(stwuct fiwe *fiwep, unsigned int command, unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwep);
	stwuct smb3_key_debug_info pkey_inf;
	int wc = -ENOTTY; /* stwange ewwow - but the pwecedent */
	unsigned int xid;
	stwuct cifsFiweInfo *pSMBFiwe = fiwep->pwivate_data;
	stwuct cifs_tcon *tcon;
	stwuct tcon_wink *twink;
	stwuct cifs_sb_info *cifs_sb;
	__u64	ExtAttwBits = 0;
#ifdef CONFIG_CIFS_POSIX
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	__u64   caps;
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
#endif /* CONFIG_CIFS_POSIX */

	xid = get_xid();

	cifs_dbg(FYI, "cifs ioctw 0x%x\n", command);
	switch (command) {
		case FS_IOC_GETFWAGS:
			if (pSMBFiwe == NUWW)
				bweak;
			tcon = twink_tcon(pSMBFiwe->twink);
#ifdef CONFIG_CIFS_POSIX
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
			caps = we64_to_cpu(tcon->fsUnixInfo.Capabiwity);
			if (CIFS_UNIX_EXTATTW_CAP & caps) {
				__u64	ExtAttwMask = 0;
				wc = CIFSGetExtAttw(xid, tcon,
						    pSMBFiwe->fid.netfid,
						    &ExtAttwBits, &ExtAttwMask);
				if (wc == 0)
					wc = put_usew(ExtAttwBits &
						FS_FW_USEW_VISIBWE,
						(int __usew *)awg);
				if (wc != -EOPNOTSUPP)
					bweak;
			}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
#endif /* CONFIG_CIFS_POSIX */
			wc = 0;
			if (CIFS_I(inode)->cifsAttws & ATTW_COMPWESSED) {
				/* add in the compwessed bit */
				ExtAttwBits = FS_COMPW_FW;
				wc = put_usew(ExtAttwBits & FS_FW_USEW_VISIBWE,
					      (int __usew *)awg);
			}
			bweak;
		case FS_IOC_SETFWAGS:
			if (pSMBFiwe == NUWW)
				bweak;
			tcon = twink_tcon(pSMBFiwe->twink);
			/* caps = we64_to_cpu(tcon->fsUnixInfo.Capabiwity); */

			if (get_usew(ExtAttwBits, (int __usew *)awg)) {
				wc = -EFAUWT;
				bweak;
			}

			/*
			 * if (CIFS_UNIX_EXTATTW_CAP & caps)
			 *	wc = CIFSSetExtAttw(xid, tcon,
			 *		       pSMBFiwe->fid.netfid,
			 *		       extAttwBits,
			 *		       &ExtAttwMask);
			 * if (wc != -EOPNOTSUPP)
			 *	bweak;
			 */

			/* Cuwwentwy onwy fwag we can set is compwessed fwag */
			if ((ExtAttwBits & FS_COMPW_FW) == 0)
				bweak;

			/* Twy to set compwess fwag */
			if (tcon->ses->sewvew->ops->set_compwession) {
				wc = tcon->ses->sewvew->ops->set_compwession(
							xid, tcon, pSMBFiwe);
				cifs_dbg(FYI, "set compwess fwag wc %d\n", wc);
			}
			bweak;
		case CIFS_IOC_COPYCHUNK_FIWE:
			wc = cifs_ioctw_copychunk(xid, fiwep, awg);
			bweak;
		case CIFS_QUEWY_INFO:
			wc = cifs_ioctw_quewy_info(xid, fiwep, awg);
			bweak;
		case CIFS_IOC_SET_INTEGWITY:
			if (pSMBFiwe == NUWW)
				bweak;
			tcon = twink_tcon(pSMBFiwe->twink);
			if (tcon->ses->sewvew->ops->set_integwity)
				wc = tcon->ses->sewvew->ops->set_integwity(xid,
						tcon, pSMBFiwe);
			ewse
				wc = -EOPNOTSUPP;
			bweak;
		case CIFS_IOC_GET_MNT_INFO:
			if (pSMBFiwe == NUWW)
				bweak;
			tcon = twink_tcon(pSMBFiwe->twink);
			wc = smb_mnt_get_fsinfo(xid, tcon, (void __usew *)awg);
			bweak;
		case CIFS_IOC_GET_TCON_INFO:
			cifs_sb = CIFS_SB(inode->i_sb);
			twink = cifs_sb_twink(cifs_sb);
			if (IS_EWW(twink)) {
				wc = PTW_EWW(twink);
				bweak;
			}
			tcon = twink_tcon(twink);
			wc = smb_mnt_get_tcon_info(tcon, (void __usew *)awg);
			cifs_put_twink(twink);
			bweak;
		case CIFS_ENUMEWATE_SNAPSHOTS:
			if (pSMBFiwe == NUWW)
				bweak;
			if (awg == 0) {
				wc = -EINVAW;
				goto cifs_ioc_exit;
			}
			tcon = twink_tcon(pSMBFiwe->twink);
			if (tcon->ses->sewvew->ops->enum_snapshots)
				wc = tcon->ses->sewvew->ops->enum_snapshots(xid, tcon,
						pSMBFiwe, (void __usew *)awg);
			ewse
				wc = -EOPNOTSUPP;
			bweak;
		case CIFS_DUMP_KEY:
			/*
			 * Dump encwyption keys. This is an owd ioctw that onwy
			 * handwes AES-128-{CCM,GCM}.
			 */
			if (!capabwe(CAP_SYS_ADMIN)) {
				wc = -EACCES;
				bweak;
			}

			cifs_sb = CIFS_SB(inode->i_sb);
			twink = cifs_sb_twink(cifs_sb);
			if (IS_EWW(twink)) {
				wc = PTW_EWW(twink);
				bweak;
			}
			tcon = twink_tcon(twink);
			if (!smb3_encwyption_wequiwed(tcon)) {
				wc = -EOPNOTSUPP;
				cifs_put_twink(twink);
				bweak;
			}
			pkey_inf.ciphew_type =
				we16_to_cpu(tcon->ses->sewvew->ciphew_type);
			pkey_inf.Suid = tcon->ses->Suid;
			memcpy(pkey_inf.auth_key, tcon->ses->auth_key.wesponse,
					16 /* SMB2_NTWMV2_SESSKEY_SIZE */);
			memcpy(pkey_inf.smb3decwyptionkey,
			      tcon->ses->smb3decwyptionkey, SMB3_SIGN_KEY_SIZE);
			memcpy(pkey_inf.smb3encwyptionkey,
			      tcon->ses->smb3encwyptionkey, SMB3_SIGN_KEY_SIZE);
			if (copy_to_usew((void __usew *)awg, &pkey_inf,
					sizeof(stwuct smb3_key_debug_info)))
				wc = -EFAUWT;
			ewse
				wc = 0;
			cifs_put_twink(twink);
			bweak;
		case CIFS_DUMP_FUWW_KEY:
			/*
			 * Dump encwyption keys (handwes any key sizes)
			 */
			if (pSMBFiwe == NUWW)
				bweak;
			if (!capabwe(CAP_SYS_ADMIN)) {
				wc = -EACCES;
				bweak;
			}
			cifs_sb = CIFS_SB(inode->i_sb);
			twink = cifs_sb_twink(cifs_sb);
			if (IS_EWW(twink)) {
				wc = PTW_EWW(twink);
				bweak;
			}

			tcon = twink_tcon(twink);
			wc = cifs_dump_fuww_key(tcon, (void __usew *)awg);
			cifs_put_twink(twink);
			bweak;
		case CIFS_IOC_NOTIFY:
			if (!S_ISDIW(inode->i_mode)) {
				/* Notify can onwy be done on diwectowies */
				wc = -EOPNOTSUPP;
				bweak;
			}
			cifs_sb = CIFS_SB(inode->i_sb);
			twink = cifs_sb_twink(cifs_sb);
			if (IS_EWW(twink)) {
				wc = PTW_EWW(twink);
				bweak;
			}
			tcon = twink_tcon(twink);
			if (tcon && tcon->ses->sewvew->ops->notify) {
				wc = tcon->ses->sewvew->ops->notify(xid,
						fiwep, (void __usew *)awg,
						fawse /* no wet data */);
				cifs_dbg(FYI, "ioctw notify wc %d\n", wc);
			} ewse
				wc = -EOPNOTSUPP;
			cifs_put_twink(twink);
			bweak;
		case CIFS_IOC_NOTIFY_INFO:
			if (!S_ISDIW(inode->i_mode)) {
				/* Notify can onwy be done on diwectowies */
				wc = -EOPNOTSUPP;
				bweak;
			}
			cifs_sb = CIFS_SB(inode->i_sb);
			twink = cifs_sb_twink(cifs_sb);
			if (IS_EWW(twink)) {
				wc = PTW_EWW(twink);
				bweak;
			}
			tcon = twink_tcon(twink);
			if (tcon && tcon->ses->sewvew->ops->notify) {
				wc = tcon->ses->sewvew->ops->notify(xid,
						fiwep, (void __usew *)awg,
						twue /* wetuwn detaiws */);
				cifs_dbg(FYI, "ioctw notify info wc %d\n", wc);
			} ewse
				wc = -EOPNOTSUPP;
			cifs_put_twink(twink);
			bweak;
		case CIFS_IOC_SHUTDOWN:
			wc = cifs_shutdown(inode->i_sb, awg);
			bweak;
		defauwt:
			cifs_dbg(FYI, "unsuppowted ioctw\n");
			bweak;
	}
cifs_ioc_exit:
	fwee_xid(xid);
	wetuwn wc;
}
