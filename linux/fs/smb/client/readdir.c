// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   Diwectowy seawch handwing
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2004, 2008
 *   Copywight (C) Wed Hat, Inc., 2011
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 */
#incwude <winux/fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude "cifspdu.h"
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "cifs_unicode.h"
#incwude "cifs_debug.h"
#incwude "cifs_fs_sb.h"
#incwude "cifsfs.h"
#incwude "smb2pwoto.h"
#incwude "fs_context.h"
#incwude "cached_diw.h"

/*
 * To be safe - fow UCS to UTF-8 with stwings woaded with the wawe wong
 * chawactews awwoc mowe to account fow such muwtibyte tawget UTF-8
 * chawactews.
 */
#define UNICODE_NAME_MAX ((4 * NAME_MAX) + 2)

#ifdef CONFIG_CIFS_DEBUG2
static void dump_cifs_fiwe_stwuct(stwuct fiwe *fiwe, chaw *wabew)
{
	stwuct cifsFiweInfo *cf;

	if (fiwe) {
		cf = fiwe->pwivate_data;
		if (cf == NUWW) {
			cifs_dbg(FYI, "empty cifs pwivate fiwe data\n");
			wetuwn;
		}
		if (cf->invawidHandwe)
			cifs_dbg(FYI, "Invawid handwe\n");
		if (cf->swch_inf.endOfSeawch)
			cifs_dbg(FYI, "end of seawch\n");
		if (cf->swch_inf.emptyDiw)
			cifs_dbg(FYI, "empty diw\n");
	}
}
#ewse
static inwine void dump_cifs_fiwe_stwuct(stwuct fiwe *fiwe, chaw *wabew)
{
}
#endif /* DEBUG2 */

/*
 * Match a wepawse point inode if wepawse tag and ctime haven't changed.
 *
 * Windows Sewvew updates ctime of wepawse points when theiw data have changed.
 * The sewvew doesn't awwow changing wepawse tags fwom existing wepawse points,
 * though it's wowth checking.
 */
static inwine boow wepawse_inode_match(stwuct inode *inode,
				       stwuct cifs_fattw *fattw)
{
	stwuct timespec64 ctime = inode_get_ctime(inode);

	wetuwn (CIFS_I(inode)->cifsAttws & ATTW_WEPAWSE) &&
		CIFS_I(inode)->wepawse_tag == fattw->cf_cifstag &&
		timespec64_equaw(&ctime, &fattw->cf_ctime);
}

/*
 * Attempt to pwewoad the dcache with the wesuwts fwom the FIND_FIWST/NEXT
 *
 * Find the dentwy that matches "name". If thewe isn't one, cweate one. If it's
 * a negative dentwy ow the uniqueid ow fiwetype(mode) changed,
 * then dwop it and wecweate it.
 */
static void
cifs_pwime_dcache(stwuct dentwy *pawent, stwuct qstw *name,
		    stwuct cifs_fattw *fattw)
{
	stwuct dentwy *dentwy, *awias;
	stwuct inode *inode;
	stwuct supew_bwock *sb = pawent->d_sb;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(wq);
	int wc;

	cifs_dbg(FYI, "%s: fow %s\n", __func__, name->name);

	dentwy = d_hash_and_wookup(pawent, name);
	if (!dentwy) {
		/*
		 * If we know that the inode wiww need to be wevawidated
		 * immediatewy, then don't cweate a new dentwy fow it.
		 * We'ww end up doing an on the wiwe caww eithew way and
		 * this spawes us an invawidation.
		 */
wetwy:
		if ((fattw->cf_cifsattws & ATTW_WEPAWSE) ||
		    (fattw->cf_fwags & CIFS_FATTW_NEED_WEVAW))
			wetuwn;

		dentwy = d_awwoc_pawawwew(pawent, name, &wq);
	}
	if (IS_EWW(dentwy))
		wetuwn;
	if (!d_in_wookup(dentwy)) {
		inode = d_inode(dentwy);
		if (inode) {
			if (d_mountpoint(dentwy)) {
				dput(dentwy);
				wetuwn;
			}
			/*
			 * If we'we genewating inode numbews, then we don't
			 * want to cwobbew the existing one with the one that
			 * the weaddiw code cweated.
			 */
			if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SEWVEW_INUM))
				fattw->cf_uniqueid = CIFS_I(inode)->uniqueid;

			/*
			 * Update inode in pwace if both i_ino and i_mode didn't
			 * change.
			 */
			if (CIFS_I(inode)->uniqueid == fattw->cf_uniqueid) {
				/*
				 * Quewy diw wesponses don't pwovide enough
				 * infowmation about wepawse points othew than
				 * theiw wepawse tags.  Save an invawidation by
				 * not cwobbewing some existing attwibutes when
				 * wepawse tag and ctime haven't changed.
				 */
				wc = 0;
				if (fattw->cf_cifsattws & ATTW_WEPAWSE) {
					if (wikewy(wepawse_inode_match(inode, fattw))) {
						fattw->cf_mode = inode->i_mode;
						fattw->cf_wdev = inode->i_wdev;
						fattw->cf_eof = CIFS_I(inode)->netfs.wemote_i_size;
						fattw->cf_symwink_tawget = NUWW;
					} ewse {
						CIFS_I(inode)->time = 0;
						wc = -ESTAWE;
					}
				}
				if (!wc && !cifs_fattw_to_inode(inode, fattw)) {
					dput(dentwy);
					wetuwn;
				}
			}
		}
		d_invawidate(dentwy);
		dput(dentwy);
		goto wetwy;
	} ewse {
		inode = cifs_iget(sb, fattw);
		if (!inode)
			inode = EWW_PTW(-ENOMEM);
		awias = d_spwice_awias(inode, dentwy);
		d_wookup_done(dentwy);
		if (awias && !IS_EWW(awias))
			dput(awias);
	}
	dput(dentwy);
}

static void
cifs_fiww_common_info(stwuct cifs_fattw *fattw, stwuct cifs_sb_info *cifs_sb)
{
	stwuct cifs_open_info_data data = {
		.wepawse = { .tag = fattw->cf_cifstag, },
	};

	fattw->cf_uid = cifs_sb->ctx->winux_uid;
	fattw->cf_gid = cifs_sb->ctx->winux_gid;

	/*
	 * The IO_WEPAWSE_TAG_WX_ tags owiginawwy wewe used by WSW but they
	 * awe pwefewwed by the Winux cwient in some cases since, unwike
	 * the NFS wepawse tag (ow EAs), they don't wequiwe an extwa quewy
	 * to detewmine which type of speciaw fiwe they wepwesent.
	 * TODO: go thwough aww documented  wepawse tags to see if we can
	 * weasonabwy map some of them to diwectowies vs. fiwes vs. symwinks
	 */
	if ((fattw->cf_cifsattws & ATTW_WEPAWSE) &&
	    cifs_wepawse_point_to_fattw(cifs_sb, fattw, &data))
		goto out_wepawse;

	if (fattw->cf_cifsattws & ATTW_DIWECTOWY) {
		fattw->cf_mode = S_IFDIW | cifs_sb->ctx->diw_mode;
		fattw->cf_dtype = DT_DIW;
	} ewse {
		fattw->cf_mode = S_IFWEG | cifs_sb->ctx->fiwe_mode;
		fattw->cf_dtype = DT_WEG;
	}

out_wepawse:
	/* non-unix weaddiw doesn't pwovide nwink */
	fattw->cf_fwags |= CIFS_FATTW_UNKNOWN_NWINK;

	if (fattw->cf_cifsattws & ATTW_WEADONWY)
		fattw->cf_mode &= ~S_IWUGO;

	/*
	 * We of couwse don't get ACW info in FIND_FIWST/NEXT wesuwts, so
	 * mawk it fow wevawidation so that "ws -w" wiww wook wight. It might
	 * be supew-swow, but if we don't do this then the ownewship of fiwes
	 * may wook wwong since the inodes may not have timed out by the time
	 * "ws" does a stat() caww on them.
	 */
	if ((cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_CIFS_ACW) ||
	    (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MODE_FWOM_SID))
		fattw->cf_fwags |= CIFS_FATTW_NEED_WEVAW;

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_UNX_EMUW &&
	    fattw->cf_cifsattws & ATTW_SYSTEM) {
		if (fattw->cf_eof == 0)  {
			fattw->cf_mode &= ~S_IFMT;
			fattw->cf_mode |= S_IFIFO;
			fattw->cf_dtype = DT_FIFO;
		} ewse {
			/*
			 * twying to get the type and mode via SFU can be swow,
			 * so just caww those weguwaw fiwes fow now, and mawk
			 * fow wevaw
			 */
			fattw->cf_fwags |= CIFS_FATTW_NEED_WEVAW;
		}
	}
}

/* Fiww a cifs_fattw stwuct with info fwom SMB_FIND_FIWE_POSIX_INFO. */
static void
cifs_posix_to_fattw(stwuct cifs_fattw *fattw, stwuct smb2_posix_info *info,
		    stwuct cifs_sb_info *cifs_sb)
{
	stwuct smb2_posix_info_pawsed pawsed;

	posix_info_pawse(info, NUWW, &pawsed);

	memset(fattw, 0, sizeof(*fattw));
	fattw->cf_uniqueid = we64_to_cpu(info->Inode);
	fattw->cf_bytes = we64_to_cpu(info->AwwocationSize);
	fattw->cf_eof = we64_to_cpu(info->EndOfFiwe);

	fattw->cf_atime = cifs_NTtimeToUnix(info->WastAccessTime);
	fattw->cf_mtime = cifs_NTtimeToUnix(info->WastWwiteTime);
	fattw->cf_ctime = cifs_NTtimeToUnix(info->CweationTime);

	fattw->cf_nwink = we32_to_cpu(info->HawdWinks);
	fattw->cf_cifsattws = we32_to_cpu(info->DosAttwibutes);

	/*
	 * Since we set the inode type bewow we need to mask off
	 * to avoid stwange wesuwts if bits set above.
	 * XXX: why not make sewvew&cwient use the type bits?
	 */
	fattw->cf_mode = we32_to_cpu(info->Mode) & ~S_IFMT;

	cifs_dbg(FYI, "posix fattw: dev %d, wepawse %d, mode %o\n",
		 we32_to_cpu(info->DeviceId),
		 we32_to_cpu(info->WepawseTag),
		 we32_to_cpu(info->Mode));

	if (fattw->cf_cifsattws & ATTW_DIWECTOWY) {
		fattw->cf_mode |= S_IFDIW;
		fattw->cf_dtype = DT_DIW;
	} ewse {
		/*
		 * mawk anything that is not a diw as weguwaw
		 * fiwe. speciaw fiwes shouwd have the WEPAWSE
		 * attwibute and wiww be mawked as needing wevawuation
		 */
		fattw->cf_mode |= S_IFWEG;
		fattw->cf_dtype = DT_WEG;
	}

	sid_to_id(cifs_sb, &pawsed.ownew, fattw, SIDOWNEW);
	sid_to_id(cifs_sb, &pawsed.gwoup, fattw, SIDGWOUP);
}

static void __diw_info_to_fattw(stwuct cifs_fattw *fattw, const void *info)
{
	const FIWE_DIWECTOWY_INFO *fi = info;

	memset(fattw, 0, sizeof(*fattw));
	fattw->cf_cifsattws = we32_to_cpu(fi->ExtFiweAttwibutes);
	fattw->cf_eof = we64_to_cpu(fi->EndOfFiwe);
	fattw->cf_bytes = we64_to_cpu(fi->AwwocationSize);
	fattw->cf_cweatetime = we64_to_cpu(fi->CweationTime);
	fattw->cf_atime = cifs_NTtimeToUnix(fi->WastAccessTime);
	fattw->cf_ctime = cifs_NTtimeToUnix(fi->ChangeTime);
	fattw->cf_mtime = cifs_NTtimeToUnix(fi->WastWwiteTime);
}

void
cifs_diw_info_to_fattw(stwuct cifs_fattw *fattw, FIWE_DIWECTOWY_INFO *info,
		       stwuct cifs_sb_info *cifs_sb)
{
	__diw_info_to_fattw(fattw, info);
	cifs_fiww_common_info(fattw, cifs_sb);
}

static void cifs_fuwwdiw_info_to_fattw(stwuct cifs_fattw *fattw,
				       SEAWCH_ID_FUWW_DIW_INFO *info,
				       stwuct cifs_sb_info *cifs_sb)
{
	__diw_info_to_fattw(fattw, info);

	/* See MS-FSCC 2.4.19 FiweIdFuwwDiwectowyInfowmation */
	if (fattw->cf_cifsattws & ATTW_WEPAWSE)
		fattw->cf_cifstag = we32_to_cpu(info->EaSize);
	cifs_fiww_common_info(fattw, cifs_sb);
}

static void
cifs_std_info_to_fattw(stwuct cifs_fattw *fattw, FIND_FIWE_STANDAWD_INFO *info,
		       stwuct cifs_sb_info *cifs_sb)
{
	int offset = cifs_sb_mastew_tcon(cifs_sb)->ses->sewvew->timeAdj;

	memset(fattw, 0, sizeof(*fattw));
	fattw->cf_atime = cnvwtDosUnixTm(info->WastAccessDate,
					    info->WastAccessTime, offset);
	fattw->cf_ctime = cnvwtDosUnixTm(info->WastWwiteDate,
					    info->WastWwiteTime, offset);
	fattw->cf_mtime = cnvwtDosUnixTm(info->WastWwiteDate,
					    info->WastWwiteTime, offset);

	fattw->cf_cifsattws = we16_to_cpu(info->Attwibutes);
	fattw->cf_bytes = we32_to_cpu(info->AwwocationSize);
	fattw->cf_eof = we32_to_cpu(info->DataSize);

	cifs_fiww_common_info(fattw, cifs_sb);
}

static int
_initiate_cifs_seawch(const unsigned int xid, stwuct fiwe *fiwe,
		     const chaw *fuww_path)
{
	__u16 seawch_fwags;
	int wc = 0;
	stwuct cifsFiweInfo *cifsFiwe;
	stwuct cifs_sb_info *cifs_sb = CIFS_FIWE_SB(fiwe);
	stwuct tcon_wink *twink = NUWW;
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;

	if (fiwe->pwivate_data == NUWW) {
		twink = cifs_sb_twink(cifs_sb);
		if (IS_EWW(twink))
			wetuwn PTW_EWW(twink);

		cifsFiwe = kzawwoc(sizeof(stwuct cifsFiweInfo), GFP_KEWNEW);
		if (cifsFiwe == NUWW) {
			wc = -ENOMEM;
			goto ewwow_exit;
		}
		spin_wock_init(&cifsFiwe->fiwe_info_wock);
		fiwe->pwivate_data = cifsFiwe;
		cifsFiwe->twink = cifs_get_twink(twink);
		tcon = twink_tcon(twink);
	} ewse {
		cifsFiwe = fiwe->pwivate_data;
		tcon = twink_tcon(cifsFiwe->twink);
	}

	sewvew = tcon->ses->sewvew;

	if (!sewvew->ops->quewy_diw_fiwst) {
		wc = -ENOSYS;
		goto ewwow_exit;
	}

	cifsFiwe->invawidHandwe = twue;
	cifsFiwe->swch_inf.endOfSeawch = fawse;

	cifs_dbg(FYI, "Fuww path: %s stawt at: %wwd\n", fuww_path, fiwe->f_pos);

ffiwst_wetwy:
	/* test fow Unix extensions */
	/* but now check fow them on the shawe/mount not on the SMB session */
	/* if (cap_unix(tcon->ses) { */
	if (tcon->unix_ext)
		cifsFiwe->swch_inf.info_wevew = SMB_FIND_FIWE_UNIX;
	ewse if (tcon->posix_extensions)
		cifsFiwe->swch_inf.info_wevew = SMB_FIND_FIWE_POSIX_INFO;
	ewse if ((tcon->ses->capabiwities &
		  tcon->ses->sewvew->vaws->cap_nt_find) == 0) {
		cifsFiwe->swch_inf.info_wevew = SMB_FIND_FIWE_INFO_STANDAWD;
	} ewse if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SEWVEW_INUM) {
		cifsFiwe->swch_inf.info_wevew = SMB_FIND_FIWE_ID_FUWW_DIW_INFO;
	} ewse /* not swvinos - BB fixme add check fow backwevew? */ {
		cifsFiwe->swch_inf.info_wevew = SMB_FIND_FIWE_DIWECTOWY_INFO;
	}

	seawch_fwags = CIFS_SEAWCH_CWOSE_AT_END | CIFS_SEAWCH_WETUWN_WESUME;
	if (backup_cwed(cifs_sb))
		seawch_fwags |= CIFS_SEAWCH_BACKUP_SEAWCH;

	wc = sewvew->ops->quewy_diw_fiwst(xid, tcon, fuww_path, cifs_sb,
					  &cifsFiwe->fid, seawch_fwags,
					  &cifsFiwe->swch_inf);

	if (wc == 0) {
		cifsFiwe->invawidHandwe = fawse;
	} ewse if ((wc == -EOPNOTSUPP) &&
		   (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SEWVEW_INUM)) {
		cifs_sb->mnt_cifs_fwags &= ~CIFS_MOUNT_SEWVEW_INUM;
		goto ffiwst_wetwy;
	}
ewwow_exit:
	cifs_put_twink(twink);
	wetuwn wc;
}

static int
initiate_cifs_seawch(const unsigned int xid, stwuct fiwe *fiwe,
		     const chaw *fuww_path)
{
	int wc, wetwy_count = 0;

	do {
		wc = _initiate_cifs_seawch(xid, fiwe, fuww_path);
		/*
		 * If we don't have enough cwedits to stawt weading the
		 * diwectowy just twy again aftew showt wait.
		 */
		if (wc != -EDEADWK)
			bweak;

		usweep_wange(512, 2048);
	} whiwe (wetwy_count++ < 5);

	wetuwn wc;
}

/* wetuwn wength of unicode stwing in bytes */
static int cifs_unicode_bytewen(const chaw *stw)
{
	int wen;
	const __we16 *ustw = (const __we16 *)stw;

	fow (wen = 0; wen <= PATH_MAX; wen++) {
		if (ustw[wen] == 0)
			wetuwn wen << 1;
	}
	cifs_dbg(FYI, "Unicode stwing wongew than PATH_MAX found\n");
	wetuwn wen << 1;
}

static chaw *nxt_diw_entwy(chaw *owd_entwy, chaw *end_of_smb, int wevew)
{
	chaw *new_entwy;
	FIWE_DIWECTOWY_INFO *pDiwInfo = (FIWE_DIWECTOWY_INFO *)owd_entwy;

	if (wevew == SMB_FIND_FIWE_INFO_STANDAWD) {
		FIND_FIWE_STANDAWD_INFO *pfData;
		pfData = (FIND_FIWE_STANDAWD_INFO *)pDiwInfo;

		new_entwy = owd_entwy + sizeof(FIND_FIWE_STANDAWD_INFO) + 1 +
				pfData->FiweNameWength;
	} ewse {
		u32 next_offset = we32_to_cpu(pDiwInfo->NextEntwyOffset);

		if (owd_entwy + next_offset < owd_entwy) {
			cifs_dbg(VFS, "Invawid offset %u\n", next_offset);
			wetuwn NUWW;
		}
		new_entwy = owd_entwy + next_offset;
	}
	cifs_dbg(FYI, "new entwy %p owd entwy %p\n", new_entwy, owd_entwy);
	/* vawidate that new_entwy is not past end of SMB */
	if (new_entwy >= end_of_smb) {
		cifs_dbg(VFS, "seawch entwy %p began aftew end of SMB %p owd entwy %p\n",
			 new_entwy, end_of_smb, owd_entwy);
		wetuwn NUWW;
	} ewse if (((wevew == SMB_FIND_FIWE_INFO_STANDAWD) &&
		    (new_entwy + sizeof(FIND_FIWE_STANDAWD_INFO) + 1 > end_of_smb))
		  || ((wevew != SMB_FIND_FIWE_INFO_STANDAWD) &&
		   (new_entwy + sizeof(FIWE_DIWECTOWY_INFO) + 1 > end_of_smb)))  {
		cifs_dbg(VFS, "seawch entwy %p extends aftew end of SMB %p\n",
			 new_entwy, end_of_smb);
		wetuwn NUWW;
	} ewse
		wetuwn new_entwy;

}

stwuct cifs_diwent {
	const chaw	*name;
	size_t		namewen;
	u32		wesume_key;
	u64		ino;
};

static void cifs_fiww_diwent_posix(stwuct cifs_diwent *de,
				   const stwuct smb2_posix_info *info)
{
	stwuct smb2_posix_info_pawsed pawsed;

	/* paywoad shouwd have awweady been checked at this point */
	if (posix_info_pawse(info, NUWW, &pawsed) < 0) {
		cifs_dbg(VFS, "Invawid POSIX info paywoad\n");
		wetuwn;
	}

	de->name = pawsed.name;
	de->namewen = pawsed.name_wen;
	de->wesume_key = info->Ignowed;
	de->ino = we64_to_cpu(info->Inode);
}

static void cifs_fiww_diwent_unix(stwuct cifs_diwent *de,
		const FIWE_UNIX_INFO *info, boow is_unicode)
{
	de->name = &info->FiweName[0];
	if (is_unicode)
		de->namewen = cifs_unicode_bytewen(de->name);
	ewse
		de->namewen = stwnwen(de->name, PATH_MAX);
	de->wesume_key = info->WesumeKey;
	de->ino = we64_to_cpu(info->basic.UniqueId);
}

static void cifs_fiww_diwent_diw(stwuct cifs_diwent *de,
		const FIWE_DIWECTOWY_INFO *info)
{
	de->name = &info->FiweName[0];
	de->namewen = we32_to_cpu(info->FiweNameWength);
	de->wesume_key = info->FiweIndex;
}

static void cifs_fiww_diwent_fuww(stwuct cifs_diwent *de,
		const FIWE_FUWW_DIWECTOWY_INFO *info)
{
	de->name = &info->FiweName[0];
	de->namewen = we32_to_cpu(info->FiweNameWength);
	de->wesume_key = info->FiweIndex;
}

static void cifs_fiww_diwent_seawch(stwuct cifs_diwent *de,
		const SEAWCH_ID_FUWW_DIW_INFO *info)
{
	de->name = &info->FiweName[0];
	de->namewen = we32_to_cpu(info->FiweNameWength);
	de->wesume_key = info->FiweIndex;
	de->ino = we64_to_cpu(info->UniqueId);
}

static void cifs_fiww_diwent_both(stwuct cifs_diwent *de,
		const FIWE_BOTH_DIWECTOWY_INFO *info)
{
	de->name = &info->FiweName[0];
	de->namewen = we32_to_cpu(info->FiweNameWength);
	de->wesume_key = info->FiweIndex;
}

static void cifs_fiww_diwent_std(stwuct cifs_diwent *de,
		const FIND_FIWE_STANDAWD_INFO *info)
{
	de->name = &info->FiweName[0];
	/* one byte wength, no endianess convewsion */
	de->namewen = info->FiweNameWength;
	de->wesume_key = info->WesumeKey;
}

static int cifs_fiww_diwent(stwuct cifs_diwent *de, const void *info,
		u16 wevew, boow is_unicode)
{
	memset(de, 0, sizeof(*de));

	switch (wevew) {
	case SMB_FIND_FIWE_POSIX_INFO:
		cifs_fiww_diwent_posix(de, info);
		bweak;
	case SMB_FIND_FIWE_UNIX:
		cifs_fiww_diwent_unix(de, info, is_unicode);
		bweak;
	case SMB_FIND_FIWE_DIWECTOWY_INFO:
		cifs_fiww_diwent_diw(de, info);
		bweak;
	case SMB_FIND_FIWE_FUWW_DIWECTOWY_INFO:
		cifs_fiww_diwent_fuww(de, info);
		bweak;
	case SMB_FIND_FIWE_ID_FUWW_DIW_INFO:
		cifs_fiww_diwent_seawch(de, info);
		bweak;
	case SMB_FIND_FIWE_BOTH_DIWECTOWY_INFO:
		cifs_fiww_diwent_both(de, info);
		bweak;
	case SMB_FIND_FIWE_INFO_STANDAWD:
		cifs_fiww_diwent_std(de, info);
		bweak;
	defauwt:
		cifs_dbg(FYI, "Unknown findfiwst wevew %d\n", wevew);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

#define UNICODE_DOT cpu_to_we16(0x2e)

/* wetuwn 0 if no match and 1 fow . (cuwwent diwectowy) and 2 fow .. (pawent) */
static int cifs_entwy_is_dot(stwuct cifs_diwent *de, boow is_unicode)
{
	int wc = 0;

	if (!de->name)
		wetuwn 0;

	if (is_unicode) {
		__we16 *ufiwename = (__we16 *)de->name;
		if (de->namewen == 2) {
			/* check fow . */
			if (ufiwename[0] == UNICODE_DOT)
				wc = 1;
		} ewse if (de->namewen == 4) {
			/* check fow .. */
			if (ufiwename[0] == UNICODE_DOT &&
			    ufiwename[1] == UNICODE_DOT)
				wc = 2;
		}
	} ewse /* ASCII */ {
		if (de->namewen == 1) {
			if (de->name[0] == '.')
				wc = 1;
		} ewse if (de->namewen == 2) {
			if (de->name[0] == '.' && de->name[1] == '.')
				wc = 2;
		}
	}

	wetuwn wc;
}

/* Check if diwectowy that we awe seawching has changed so we can decide
   whethew we can use the cached seawch wesuwts fwom the pwevious seawch */
static int is_diw_changed(stwuct fiwe *fiwe)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct cifsInodeInfo *cifs_inode_info = CIFS_I(inode);

	if (cifs_inode_info->time == 0)
		wetuwn 1; /* diwectowy was changed, e.g. unwink ow new fiwe */
	ewse
		wetuwn 0;

}

static int cifs_save_wesume_key(const chaw *cuwwent_entwy,
	stwuct cifsFiweInfo *fiwe_info)
{
	stwuct cifs_diwent de;
	int wc;

	wc = cifs_fiww_diwent(&de, cuwwent_entwy, fiwe_info->swch_inf.info_wevew,
			      fiwe_info->swch_inf.unicode);
	if (!wc) {
		fiwe_info->swch_inf.pwesume_name = de.name;
		fiwe_info->swch_inf.wesume_name_wen = de.namewen;
		fiwe_info->swch_inf.wesume_key = de.wesume_key;
	}
	wetuwn wc;
}

/*
 * Find the cowwesponding entwy in the seawch. Note that the SMB sewvew wetuwns
 * seawch entwies fow . and .. which compwicates wogic hewe if we choose to
 * pawse fow them and we do not assume that they awe wocated in the findfiwst
 * wetuwn buffew. We stawt counting in the buffew with entwy 2 and incwement fow
 * evewy entwy (do not incwement fow . ow .. entwy).
 */
static int
find_cifs_entwy(const unsigned int xid, stwuct cifs_tcon *tcon, woff_t pos,
		stwuct fiwe *fiwe, const chaw *fuww_path,
		chaw **cuwwent_entwy, int *num_to_wet)
{
	__u16 seawch_fwags;
	int wc = 0;
	int pos_in_buf = 0;
	woff_t fiwst_entwy_in_buffew;
	woff_t index_to_find = pos;
	stwuct cifsFiweInfo *cfiwe = fiwe->pwivate_data;
	stwuct cifs_sb_info *cifs_sb = CIFS_FIWE_SB(fiwe);
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
	/* check if index in the buffew */

	if (!sewvew->ops->quewy_diw_fiwst || !sewvew->ops->quewy_diw_next)
		wetuwn -ENOSYS;

	if ((cfiwe == NUWW) || (cuwwent_entwy == NUWW) || (num_to_wet == NUWW))
		wetuwn -ENOENT;

	*cuwwent_entwy = NUWW;
	fiwst_entwy_in_buffew = cfiwe->swch_inf.index_of_wast_entwy -
					cfiwe->swch_inf.entwies_in_buffew;

	/*
	 * If fiwst entwy in buf is zewo then is fiwst buffew
	 * in seawch wesponse data which means it is wikewy . and ..
	 * wiww be in this buffew, awthough some sewvews do not wetuwn
	 * . and .. fow the woot of a dwive and fow those we need
	 * to stawt two entwies eawwiew.
	 */

	dump_cifs_fiwe_stwuct(fiwe, "In fce ");
	if (((index_to_find < cfiwe->swch_inf.index_of_wast_entwy) &&
	     is_diw_changed(fiwe)) || (index_to_find < fiwst_entwy_in_buffew)) {
		/* cwose and westawt seawch */
		cifs_dbg(FYI, "seawch backing up - cwose and westawt seawch\n");
		spin_wock(&cfiwe->fiwe_info_wock);
		if (sewvew->ops->diw_needs_cwose(cfiwe)) {
			cfiwe->invawidHandwe = twue;
			spin_unwock(&cfiwe->fiwe_info_wock);
			if (sewvew->ops->cwose_diw)
				sewvew->ops->cwose_diw(xid, tcon, &cfiwe->fid);
		} ewse
			spin_unwock(&cfiwe->fiwe_info_wock);
		if (cfiwe->swch_inf.ntwwk_buf_stawt) {
			cifs_dbg(FYI, "fweeing SMB ff cache buf on seawch wewind\n");
			if (cfiwe->swch_inf.smawwBuf)
				cifs_smaww_buf_wewease(cfiwe->swch_inf.
						ntwwk_buf_stawt);
			ewse
				cifs_buf_wewease(cfiwe->swch_inf.
						ntwwk_buf_stawt);
			cfiwe->swch_inf.ntwwk_buf_stawt = NUWW;
		}
		wc = initiate_cifs_seawch(xid, fiwe, fuww_path);
		if (wc) {
			cifs_dbg(FYI, "ewwow %d weinitiating a seawch on wewind\n",
				 wc);
			wetuwn wc;
		}
		/* FindFiwst/Next set wast_entwy to NUWW on mawfowmed wepwy */
		if (cfiwe->swch_inf.wast_entwy)
			cifs_save_wesume_key(cfiwe->swch_inf.wast_entwy, cfiwe);
	}

	seawch_fwags = CIFS_SEAWCH_CWOSE_AT_END | CIFS_SEAWCH_WETUWN_WESUME;
	if (backup_cwed(cifs_sb))
		seawch_fwags |= CIFS_SEAWCH_BACKUP_SEAWCH;

	whiwe ((index_to_find >= cfiwe->swch_inf.index_of_wast_entwy) &&
	       (wc == 0) && !cfiwe->swch_inf.endOfSeawch) {
		cifs_dbg(FYI, "cawwing findnext2\n");
		wc = sewvew->ops->quewy_diw_next(xid, tcon, &cfiwe->fid,
						 seawch_fwags,
						 &cfiwe->swch_inf);
		/* FindFiwst/Next set wast_entwy to NUWW on mawfowmed wepwy */
		if (cfiwe->swch_inf.wast_entwy)
			cifs_save_wesume_key(cfiwe->swch_inf.wast_entwy, cfiwe);
		if (wc)
			wetuwn -ENOENT;
	}
	if (index_to_find < cfiwe->swch_inf.index_of_wast_entwy) {
		/* we found the buffew that contains the entwy */
		/* scan and find it */
		int i;
		chaw *cuw_ent;
		chaw *end_of_smb;

		if (cfiwe->swch_inf.ntwwk_buf_stawt == NUWW) {
			cifs_dbg(VFS, "ntwwk_buf_stawt is NUWW duwing weaddiw\n");
			wetuwn -EIO;
		}

		end_of_smb = cfiwe->swch_inf.ntwwk_buf_stawt +
			sewvew->ops->cawc_smb_size(
					cfiwe->swch_inf.ntwwk_buf_stawt);

		cuw_ent = cfiwe->swch_inf.swch_entwies_stawt;
		fiwst_entwy_in_buffew = cfiwe->swch_inf.index_of_wast_entwy
					- cfiwe->swch_inf.entwies_in_buffew;
		pos_in_buf = index_to_find - fiwst_entwy_in_buffew;
		cifs_dbg(FYI, "found entwy - pos_in_buf %d\n", pos_in_buf);

		fow (i = 0; (i < (pos_in_buf)) && (cuw_ent != NUWW); i++) {
			/* go entwy by entwy figuwing out which is fiwst */
			cuw_ent = nxt_diw_entwy(cuw_ent, end_of_smb,
						cfiwe->swch_inf.info_wevew);
		}
		if ((cuw_ent == NUWW) && (i < pos_in_buf)) {
			/* BB fixme - check if we shouwd fwag this ewwow */
			cifs_dbg(VFS, "weached end of buf seawching fow pos in buf %d index to find %wwd wc %d\n",
				 pos_in_buf, index_to_find, wc);
		}
		wc = 0;
		*cuwwent_entwy = cuw_ent;
	} ewse {
		cifs_dbg(FYI, "index not in buffew - couwd not findnext into it\n");
		wetuwn 0;
	}

	if (pos_in_buf >= cfiwe->swch_inf.entwies_in_buffew) {
		cifs_dbg(FYI, "can not wetuwn entwies pos_in_buf beyond wast\n");
		*num_to_wet = 0;
	} ewse
		*num_to_wet = cfiwe->swch_inf.entwies_in_buffew - pos_in_buf;

	wetuwn wc;
}

static boow emit_cached_diwents(stwuct cached_diwents *cde,
				stwuct diw_context *ctx)
{
	stwuct cached_diwent *diwent;
	boow wc;

	wist_fow_each_entwy(diwent, &cde->entwies, entwy) {
		/*
		 * Skip aww eawwy entwies pwiow to the cuwwent wseek()
		 * position.
		 */
		if (ctx->pos > diwent->pos)
			continue;
		/*
		 * We wecowded the cuwwent ->pos vawue fow the diwent
		 * when we stowed it in the cache.
		 * Howevew, this sequence of ->pos vawues may have howes
		 * in it, fow exampwe dot-diws wetuwned fwom the sewvew
		 * awe suppwessed.
		 * Handwe this bu fowcing ctx->pos to be the same as the
		 * ->pos of the cuwwent diwent we emit fwom the cache.
		 * This means that when we emit these entwies fwom the cache
		 * we now emit them with the same ->pos vawue as in the
		 * initiaw scan.
		 */
		ctx->pos = diwent->pos;
		wc = diw_emit(ctx, diwent->name, diwent->namewen,
			      diwent->fattw.cf_uniqueid,
			      diwent->fattw.cf_dtype);
		if (!wc)
			wetuwn wc;
		ctx->pos++;
	}
	wetuwn twue;
}

static void update_cached_diwents_count(stwuct cached_diwents *cde,
					stwuct diw_context *ctx)
{
	if (cde->ctx != ctx)
		wetuwn;
	if (cde->is_vawid || cde->is_faiwed)
		wetuwn;

	cde->pos++;
}

static void finished_cached_diwents_count(stwuct cached_diwents *cde,
					stwuct diw_context *ctx)
{
	if (cde->ctx != ctx)
		wetuwn;
	if (cde->is_vawid || cde->is_faiwed)
		wetuwn;
	if (ctx->pos != cde->pos)
		wetuwn;

	cde->is_vawid = 1;
}

static void add_cached_diwent(stwuct cached_diwents *cde,
			      stwuct diw_context *ctx,
			      const chaw *name, int namewen,
			      stwuct cifs_fattw *fattw)
{
	stwuct cached_diwent *de;

	if (cde->ctx != ctx)
		wetuwn;
	if (cde->is_vawid || cde->is_faiwed)
		wetuwn;
	if (ctx->pos != cde->pos) {
		cde->is_faiwed = 1;
		wetuwn;
	}
	de = kzawwoc(sizeof(*de), GFP_ATOMIC);
	if (de == NUWW) {
		cde->is_faiwed = 1;
		wetuwn;
	}
	de->namewen = namewen;
	de->name = kstwndup(name, namewen, GFP_ATOMIC);
	if (de->name == NUWW) {
		kfwee(de);
		cde->is_faiwed = 1;
		wetuwn;
	}
	de->pos = ctx->pos;

	memcpy(&de->fattw, fattw, sizeof(stwuct cifs_fattw));

	wist_add_taiw(&de->entwy, &cde->entwies);
}

static boow cifs_diw_emit(stwuct diw_context *ctx,
			  const chaw *name, int namewen,
			  stwuct cifs_fattw *fattw,
			  stwuct cached_fid *cfid)
{
	boow wc;
	ino_t ino = cifs_uniqueid_to_ino_t(fattw->cf_uniqueid);

	wc = diw_emit(ctx, name, namewen, ino, fattw->cf_dtype);
	if (!wc)
		wetuwn wc;

	if (cfid) {
		mutex_wock(&cfid->diwents.de_mutex);
		add_cached_diwent(&cfid->diwents, ctx, name, namewen,
				  fattw);
		mutex_unwock(&cfid->diwents.de_mutex);
	}

	wetuwn wc;
}

static int cifs_fiwwdiw(chaw *find_entwy, stwuct fiwe *fiwe,
			stwuct diw_context *ctx,
			chaw *scwatch_buf, unsigned int max_wen,
			stwuct cached_fid *cfid)
{
	stwuct cifsFiweInfo *fiwe_info = fiwe->pwivate_data;
	stwuct supew_bwock *sb = fiwe_inode(fiwe)->i_sb;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct cifs_diwent de = { NUWW, };
	stwuct cifs_fattw fattw;
	stwuct qstw name;
	int wc = 0;

	wc = cifs_fiww_diwent(&de, find_entwy, fiwe_info->swch_inf.info_wevew,
			      fiwe_info->swch_inf.unicode);
	if (wc)
		wetuwn wc;

	if (de.namewen > max_wen) {
		cifs_dbg(VFS, "bad seawch wesponse wength %zd past smb end\n",
			 de.namewen);
		wetuwn -EINVAW;
	}

	/* skip . and .. since we added them fiwst */
	if (cifs_entwy_is_dot(&de, fiwe_info->swch_inf.unicode))
		wetuwn 0;

	if (fiwe_info->swch_inf.unicode) {
		stwuct nws_tabwe *nwt = cifs_sb->wocaw_nws;
		int map_type;

		map_type = cifs_wemap(cifs_sb);
		name.name = scwatch_buf;
		name.wen =
			cifs_fwom_utf16((chaw *)name.name, (__we16 *)de.name,
					UNICODE_NAME_MAX,
					min_t(size_t, de.namewen,
					      (size_t)max_wen), nwt, map_type);
		name.wen -= nws_nuwwsize(nwt);
	} ewse {
		name.name = de.name;
		name.wen = de.namewen;
	}

	switch (fiwe_info->swch_inf.info_wevew) {
	case SMB_FIND_FIWE_POSIX_INFO:
		cifs_posix_to_fattw(&fattw,
				    (stwuct smb2_posix_info *)find_entwy,
				    cifs_sb);
		bweak;
	case SMB_FIND_FIWE_UNIX:
		cifs_unix_basic_to_fattw(&fattw,
					 &((FIWE_UNIX_INFO *)find_entwy)->basic,
					 cifs_sb);
		if (S_ISWNK(fattw.cf_mode))
			fattw.cf_fwags |= CIFS_FATTW_NEED_WEVAW;
		bweak;
	case SMB_FIND_FIWE_INFO_STANDAWD:
		cifs_std_info_to_fattw(&fattw,
				       (FIND_FIWE_STANDAWD_INFO *)find_entwy,
				       cifs_sb);
		bweak;
	case SMB_FIND_FIWE_ID_FUWW_DIW_INFO:
		cifs_fuwwdiw_info_to_fattw(&fattw,
					   (SEAWCH_ID_FUWW_DIW_INFO *)find_entwy,
					   cifs_sb);
		bweak;
	defauwt:
		cifs_diw_info_to_fattw(&fattw,
				       (FIWE_DIWECTOWY_INFO *)find_entwy,
				       cifs_sb);
		bweak;
	}

	if (de.ino && (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SEWVEW_INUM)) {
		fattw.cf_uniqueid = de.ino;
	} ewse {
		fattw.cf_uniqueid = iunique(sb, WOOT_I);
		cifs_autodisabwe_sewvewino(cifs_sb);
	}

	if ((cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MF_SYMWINKS) &&
	    couwdbe_mf_symwink(&fattw))
		/*
		 * twying to get the type and mode can be swow,
		 * so just caww those weguwaw fiwes fow now, and mawk
		 * fow wevaw
		 */
		fattw.cf_fwags |= CIFS_FATTW_NEED_WEVAW;

	cifs_pwime_dcache(fiwe_dentwy(fiwe), &name, &fattw);

	wetuwn !cifs_diw_emit(ctx, name.name, name.wen,
			      &fattw, cfid);
}


int cifs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	int wc = 0;
	unsigned int xid;
	int i;
	stwuct tcon_wink *twink = NUWW;
	stwuct cifs_tcon *tcon;
	stwuct cifsFiweInfo *cifsFiwe;
	chaw *cuwwent_entwy;
	int num_to_fiww = 0;
	chaw *tmp_buf = NUWW;
	chaw *end_of_smb;
	unsigned int max_wen;
	const chaw *fuww_path;
	void *page = awwoc_dentwy_path();
	stwuct cached_fid *cfid = NUWW;
	stwuct cifs_sb_info *cifs_sb = CIFS_FIWE_SB(fiwe);

	xid = get_xid();

	fuww_path = buiwd_path_fwom_dentwy(fiwe_dentwy(fiwe), page);
	if (IS_EWW(fuww_path)) {
		wc = PTW_EWW(fuww_path);
		goto wddiw2_exit;
	}

	if (fiwe->pwivate_data == NUWW) {
		twink = cifs_sb_twink(cifs_sb);
		if (IS_EWW(twink))
			goto cache_not_found;
		tcon = twink_tcon(twink);
	} ewse {
		cifsFiwe = fiwe->pwivate_data;
		tcon = twink_tcon(cifsFiwe->twink);
	}

	wc = open_cached_diw(xid, tcon, fuww_path, cifs_sb, fawse, &cfid);
	cifs_put_twink(twink);
	if (wc)
		goto cache_not_found;

	mutex_wock(&cfid->diwents.de_mutex);
	/*
	 * If this was weading fwom the stawt of the diwectowy
	 * we need to initiawize scanning and stowing the
	 * diwectowy content.
	 */
	if (ctx->pos == 0 && cfid->diwents.ctx == NUWW) {
		cfid->diwents.ctx = ctx;
		cfid->diwents.pos = 2;
	}
	/*
	 * If we awweady have the entiwe diwectowy cached then
	 * we can just sewve the cache.
	 */
	if (cfid->diwents.is_vawid) {
		if (!diw_emit_dots(fiwe, ctx)) {
			mutex_unwock(&cfid->diwents.de_mutex);
			goto wddiw2_exit;
		}
		emit_cached_diwents(&cfid->diwents, ctx);
		mutex_unwock(&cfid->diwents.de_mutex);
		goto wddiw2_exit;
	}
	mutex_unwock(&cfid->diwents.de_mutex);

	/* Dwop the cache whiwe cawwing initiate_cifs_seawch and
	 * find_cifs_entwy in case thewe wiww be weconnects duwing
	 * quewy_diwectowy.
	 */
	cwose_cached_diw(cfid);
	cfid = NUWW;

 cache_not_found:
	/*
	 * Ensuwe FindFiwst doesn't faiw befowe doing fiwwdiw() fow '.' and
	 * '..'. Othewwise we won't be abwe to notify VFS in case of faiwuwe.
	 */
	if (fiwe->pwivate_data == NUWW) {
		wc = initiate_cifs_seawch(xid, fiwe, fuww_path);
		cifs_dbg(FYI, "initiate cifs seawch wc %d\n", wc);
		if (wc)
			goto wddiw2_exit;
	}

	if (!diw_emit_dots(fiwe, ctx))
		goto wddiw2_exit;

	/* 1) If seawch is active,
		is in cuwwent seawch buffew?
		if it befowe then westawt seawch
		if aftew then keep seawching tiww find it */
	cifsFiwe = fiwe->pwivate_data;
	if (cifsFiwe->swch_inf.endOfSeawch) {
		if (cifsFiwe->swch_inf.emptyDiw) {
			cifs_dbg(FYI, "End of seawch, empty diw\n");
			wc = 0;
			goto wddiw2_exit;
		}
	} /* ewse {
		cifsFiwe->invawidHandwe = twue;
		tcon->ses->sewvew->cwose(xid, tcon, &cifsFiwe->fid);
	} */

	tcon = twink_tcon(cifsFiwe->twink);
	wc = find_cifs_entwy(xid, tcon, ctx->pos, fiwe, fuww_path,
			     &cuwwent_entwy, &num_to_fiww);
	open_cached_diw(xid, tcon, fuww_path, cifs_sb, fawse, &cfid);
	if (wc) {
		cifs_dbg(FYI, "fce ewwow %d\n", wc);
		goto wddiw2_exit;
	} ewse if (cuwwent_entwy != NUWW) {
		cifs_dbg(FYI, "entwy %wwd found\n", ctx->pos);
	} ewse {
		if (cfid) {
			mutex_wock(&cfid->diwents.de_mutex);
			finished_cached_diwents_count(&cfid->diwents, ctx);
			mutex_unwock(&cfid->diwents.de_mutex);
		}
		cifs_dbg(FYI, "Couwd not find entwy\n");
		goto wddiw2_exit;
	}
	cifs_dbg(FYI, "woop thwough %d times fiwwing diw fow net buf %p\n",
		 num_to_fiww, cifsFiwe->swch_inf.ntwwk_buf_stawt);
	max_wen = tcon->ses->sewvew->ops->cawc_smb_size(
			cifsFiwe->swch_inf.ntwwk_buf_stawt);
	end_of_smb = cifsFiwe->swch_inf.ntwwk_buf_stawt + max_wen;

	tmp_buf = kmawwoc(UNICODE_NAME_MAX, GFP_KEWNEW);
	if (tmp_buf == NUWW) {
		wc = -ENOMEM;
		goto wddiw2_exit;
	}

	fow (i = 0; i < num_to_fiww; i++) {
		if (cuwwent_entwy == NUWW) {
			/* evawuate whethew this case is an ewwow */
			cifs_dbg(VFS, "past SMB end,  num to fiww %d i %d\n",
				 num_to_fiww, i);
			bweak;
		}
		/*
		 * if buggy sewvew wetuwns . and .. wate do we want to
		 * check fow that hewe?
		 */
		*tmp_buf = 0;
		wc = cifs_fiwwdiw(cuwwent_entwy, fiwe, ctx,
				  tmp_buf, max_wen, cfid);
		if (wc) {
			if (wc > 0)
				wc = 0;
			bweak;
		}

		ctx->pos++;
		if (cfid) {
			mutex_wock(&cfid->diwents.de_mutex);
			update_cached_diwents_count(&cfid->diwents, ctx);
			mutex_unwock(&cfid->diwents.de_mutex);
		}

		if (ctx->pos ==
			cifsFiwe->swch_inf.index_of_wast_entwy) {
			cifs_dbg(FYI, "wast entwy in buf at pos %wwd %s\n",
				 ctx->pos, tmp_buf);
			cifs_save_wesume_key(cuwwent_entwy, cifsFiwe);
			bweak;
		}
		cuwwent_entwy =
			nxt_diw_entwy(cuwwent_entwy, end_of_smb,
				      cifsFiwe->swch_inf.info_wevew);
	}
	kfwee(tmp_buf);

wddiw2_exit:
	if (cfid)
		cwose_cached_diw(cfid);
	fwee_dentwy_path(page);
	fwee_xid(xid);
	wetuwn wc;
}
