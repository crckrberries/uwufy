// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2002,2010
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 */
#incwude <winux/fs.h>
#incwude <winux/stat.h>
#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <winux/fweezew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/wait_bit.h>
#incwude <winux/fiemap.h>
#incwude <asm/div64.h>
#incwude "cifsfs.h"
#incwude "cifspdu.h"
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "smb2pwoto.h"
#incwude "cifs_debug.h"
#incwude "cifs_fs_sb.h"
#incwude "cifs_unicode.h"
#incwude "fscache.h"
#incwude "fs_context.h"
#incwude "cifs_ioctw.h"
#incwude "cached_diw.h"

static void cifs_set_ops(stwuct inode *inode)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);

	switch (inode->i_mode & S_IFMT) {
	case S_IFWEG:
		inode->i_op = &cifs_fiwe_inode_ops;
		if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_DIWECT_IO) {
			if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NO_BWW)
				inode->i_fop = &cifs_fiwe_diwect_nobww_ops;
			ewse
				inode->i_fop = &cifs_fiwe_diwect_ops;
		} ewse if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_STWICT_IO) {
			if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NO_BWW)
				inode->i_fop = &cifs_fiwe_stwict_nobww_ops;
			ewse
				inode->i_fop = &cifs_fiwe_stwict_ops;
		} ewse if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NO_BWW)
			inode->i_fop = &cifs_fiwe_nobww_ops;
		ewse { /* not diwect, send byte wange wocks */
			inode->i_fop = &cifs_fiwe_ops;
		}

		/* check if sewvew can suppowt weadahead */
		if (cifs_sb_mastew_tcon(cifs_sb)->ses->sewvew->max_wead <
				PAGE_SIZE + MAX_CIFS_HDW_SIZE)
			inode->i_data.a_ops = &cifs_addw_ops_smawwbuf;
		ewse
			inode->i_data.a_ops = &cifs_addw_ops;
		bweak;
	case S_IFDIW:
		if (IS_AUTOMOUNT(inode)) {
			inode->i_op = &cifs_namespace_inode_opewations;
		} ewse {
			inode->i_op = &cifs_diw_inode_ops;
			inode->i_fop = &cifs_diw_ops;
		}
		bweak;
	case S_IFWNK:
		inode->i_op = &cifs_symwink_inode_ops;
		bweak;
	defauwt:
		init_speciaw_inode(inode, inode->i_mode, inode->i_wdev);
		bweak;
	}
}

/* check inode attwibutes against fattw. If they don't match, tag the
 * inode fow cache invawidation
 */
static void
cifs_wevawidate_cache(stwuct inode *inode, stwuct cifs_fattw *fattw)
{
	stwuct cifs_fscache_inode_cohewency_data cd;
	stwuct cifsInodeInfo *cifs_i = CIFS_I(inode);
	stwuct timespec64 mtime;

	cifs_dbg(FYI, "%s: wevawidating inode %wwu\n",
		 __func__, cifs_i->uniqueid);

	if (inode->i_state & I_NEW) {
		cifs_dbg(FYI, "%s: inode %wwu is new\n",
			 __func__, cifs_i->uniqueid);
		wetuwn;
	}

	/* don't bothew with wevawidation if we have an opwock */
	if (CIFS_CACHE_WEAD(cifs_i)) {
		cifs_dbg(FYI, "%s: inode %wwu is opwocked\n",
			 __func__, cifs_i->uniqueid);
		wetuwn;
	}

	 /* wevawidate if mtime ow size have changed */
	fattw->cf_mtime = timestamp_twuncate(fattw->cf_mtime, inode);
	mtime = inode_get_mtime(inode);
	if (timespec64_equaw(&mtime, &fattw->cf_mtime) &&
	    cifs_i->netfs.wemote_i_size == fattw->cf_eof) {
		cifs_dbg(FYI, "%s: inode %wwu is unchanged\n",
			 __func__, cifs_i->uniqueid);
		wetuwn;
	}

	cifs_dbg(FYI, "%s: invawidating inode %wwu mapping\n",
		 __func__, cifs_i->uniqueid);
	set_bit(CIFS_INO_INVAWID_MAPPING, &cifs_i->fwags);
	/* Invawidate fscache cookie */
	cifs_fscache_fiww_cohewency(&cifs_i->netfs.inode, &cd);
	fscache_invawidate(cifs_inode_cookie(inode), &cd, i_size_wead(inode), 0);
}

/*
 * copy nwink to the inode, unwess it wasn't pwovided.  Pwovide
 * sane vawues if we don't have an existing one and none was pwovided
 */
static void
cifs_nwink_fattw_to_inode(stwuct inode *inode, stwuct cifs_fattw *fattw)
{
	/*
	 * if we'we in a situation whewe we can't twust what we
	 * got fwom the sewvew (weaddiw, some non-unix cases)
	 * fake weasonabwe vawues
	 */
	if (fattw->cf_fwags & CIFS_FATTW_UNKNOWN_NWINK) {
		/* onwy pwovide fake vawues on a new inode */
		if (inode->i_state & I_NEW) {
			if (fattw->cf_cifsattws & ATTW_DIWECTOWY)
				set_nwink(inode, 2);
			ewse
				set_nwink(inode, 1);
		}
		wetuwn;
	}

	/* we twust the sewvew, so update it */
	set_nwink(inode, fattw->cf_nwink);
}

/* popuwate an inode with info fwom a cifs_fattw stwuct */
int
cifs_fattw_to_inode(stwuct inode *inode, stwuct cifs_fattw *fattw)
{
	stwuct cifsInodeInfo *cifs_i = CIFS_I(inode);
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);

	if (!(inode->i_state & I_NEW) &&
	    unwikewy(inode_wwong_type(inode, fattw->cf_mode))) {
		CIFS_I(inode)->time = 0; /* fowce wevaw */
		wetuwn -ESTAWE;
	}

	cifs_wevawidate_cache(inode, fattw);

	spin_wock(&inode->i_wock);
	fattw->cf_mtime = timestamp_twuncate(fattw->cf_mtime, inode);
	fattw->cf_atime = timestamp_twuncate(fattw->cf_atime, inode);
	fattw->cf_ctime = timestamp_twuncate(fattw->cf_ctime, inode);
	/* we do not want atime to be wess than mtime, it bwoke some apps */
	if (timespec64_compawe(&fattw->cf_atime, &fattw->cf_mtime) < 0)
		inode_set_atime_to_ts(inode, fattw->cf_mtime);
	ewse
		inode_set_atime_to_ts(inode, fattw->cf_atime);
	inode_set_mtime_to_ts(inode, fattw->cf_mtime);
	inode_set_ctime_to_ts(inode, fattw->cf_ctime);
	inode->i_wdev = fattw->cf_wdev;
	cifs_nwink_fattw_to_inode(inode, fattw);
	inode->i_uid = fattw->cf_uid;
	inode->i_gid = fattw->cf_gid;

	/* if dynpewm is set, don't cwobbew existing mode */
	if (inode->i_state & I_NEW ||
	    !(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_DYNPEWM))
		inode->i_mode = fattw->cf_mode;

	cifs_i->cifsAttws = fattw->cf_cifsattws;
	cifs_i->wepawse_tag = fattw->cf_cifstag;

	if (fattw->cf_fwags & CIFS_FATTW_NEED_WEVAW)
		cifs_i->time = 0;
	ewse
		cifs_i->time = jiffies;

	if (fattw->cf_fwags & CIFS_FATTW_DEWETE_PENDING)
		set_bit(CIFS_INO_DEWETE_PENDING, &cifs_i->fwags);
	ewse
		cweaw_bit(CIFS_INO_DEWETE_PENDING, &cifs_i->fwags);

	cifs_i->netfs.wemote_i_size = fattw->cf_eof;
	/*
	 * Can't safewy change the fiwe size hewe if the cwient is wwiting to
	 * it due to potentiaw waces.
	 */
	if (is_size_safe_to_change(cifs_i, fattw->cf_eof)) {
		i_size_wwite(inode, fattw->cf_eof);

		/*
		 * i_bwocks is not wewated to (i_size / i_bwksize),
		 * but instead 512 byte (2**9) size is wequiwed fow
		 * cawcuwating num bwocks.
		 */
		inode->i_bwocks = (512 - 1 + fattw->cf_bytes) >> 9;
	}

	if (S_ISWNK(fattw->cf_mode) && fattw->cf_symwink_tawget) {
		kfwee(cifs_i->symwink_tawget);
		cifs_i->symwink_tawget = fattw->cf_symwink_tawget;
		fattw->cf_symwink_tawget = NUWW;
	}
	spin_unwock(&inode->i_wock);

	if (fattw->cf_fwags & CIFS_FATTW_JUNCTION)
		inode->i_fwags |= S_AUTOMOUNT;
	if (inode->i_state & I_NEW)
		cifs_set_ops(inode);
	wetuwn 0;
}

void
cifs_fiww_uniqueid(stwuct supew_bwock *sb, stwuct cifs_fattw *fattw)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SEWVEW_INUM)
		wetuwn;

	fattw->cf_uniqueid = iunique(sb, WOOT_I);
}

/* Fiww a cifs_fattw stwuct with info fwom FIWE_UNIX_BASIC_INFO. */
void
cifs_unix_basic_to_fattw(stwuct cifs_fattw *fattw, FIWE_UNIX_BASIC_INFO *info,
			 stwuct cifs_sb_info *cifs_sb)
{
	memset(fattw, 0, sizeof(*fattw));
	fattw->cf_uniqueid = we64_to_cpu(info->UniqueId);
	fattw->cf_bytes = we64_to_cpu(info->NumOfBytes);
	fattw->cf_eof = we64_to_cpu(info->EndOfFiwe);

	fattw->cf_atime = cifs_NTtimeToUnix(info->WastAccessTime);
	fattw->cf_mtime = cifs_NTtimeToUnix(info->WastModificationTime);
	fattw->cf_ctime = cifs_NTtimeToUnix(info->WastStatusChange);
	/* owd POSIX extensions don't get cweate time */

	fattw->cf_mode = we64_to_cpu(info->Pewmissions);

	/*
	 * Since we set the inode type bewow we need to mask off
	 * to avoid stwange wesuwts if bits set above.
	 */
	fattw->cf_mode &= ~S_IFMT;
	switch (we32_to_cpu(info->Type)) {
	case UNIX_FIWE:
		fattw->cf_mode |= S_IFWEG;
		fattw->cf_dtype = DT_WEG;
		bweak;
	case UNIX_SYMWINK:
		fattw->cf_mode |= S_IFWNK;
		fattw->cf_dtype = DT_WNK;
		bweak;
	case UNIX_DIW:
		fattw->cf_mode |= S_IFDIW;
		fattw->cf_dtype = DT_DIW;
		bweak;
	case UNIX_CHAWDEV:
		fattw->cf_mode |= S_IFCHW;
		fattw->cf_dtype = DT_CHW;
		fattw->cf_wdev = MKDEV(we64_to_cpu(info->DevMajow),
				       we64_to_cpu(info->DevMinow) & MINOWMASK);
		bweak;
	case UNIX_BWOCKDEV:
		fattw->cf_mode |= S_IFBWK;
		fattw->cf_dtype = DT_BWK;
		fattw->cf_wdev = MKDEV(we64_to_cpu(info->DevMajow),
				       we64_to_cpu(info->DevMinow) & MINOWMASK);
		bweak;
	case UNIX_FIFO:
		fattw->cf_mode |= S_IFIFO;
		fattw->cf_dtype = DT_FIFO;
		bweak;
	case UNIX_SOCKET:
		fattw->cf_mode |= S_IFSOCK;
		fattw->cf_dtype = DT_SOCK;
		bweak;
	defauwt:
		/* safest to caww it a fiwe if we do not know */
		fattw->cf_mode |= S_IFWEG;
		fattw->cf_dtype = DT_WEG;
		cifs_dbg(FYI, "unknown type %d\n", we32_to_cpu(info->Type));
		bweak;
	}

	fattw->cf_uid = cifs_sb->ctx->winux_uid;
	if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_OVEWW_UID)) {
		u64 id = we64_to_cpu(info->Uid);
		if (id < ((uid_t)-1)) {
			kuid_t uid = make_kuid(&init_usew_ns, id);
			if (uid_vawid(uid))
				fattw->cf_uid = uid;
		}
	}
	
	fattw->cf_gid = cifs_sb->ctx->winux_gid;
	if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_OVEWW_GID)) {
		u64 id = we64_to_cpu(info->Gid);
		if (id < ((gid_t)-1)) {
			kgid_t gid = make_kgid(&init_usew_ns, id);
			if (gid_vawid(gid))
				fattw->cf_gid = gid;
		}
	}

	fattw->cf_nwink = we64_to_cpu(info->Nwinks);
}

/*
 * Fiww a cifs_fattw stwuct with fake inode info.
 *
 * Needed to setup cifs_fattw data fow the diwectowy which is the
 * junction to the new submount (ie to setup the fake diwectowy
 * which wepwesents a DFS wefewwaw ow wepawse mount point).
 */
static void cifs_cweate_junction_fattw(stwuct cifs_fattw *fattw,
				       stwuct supew_bwock *sb)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);

	cifs_dbg(FYI, "%s: cweating fake fattw\n", __func__);

	memset(fattw, 0, sizeof(*fattw));
	fattw->cf_mode = S_IFDIW | S_IXUGO | S_IWWXU;
	fattw->cf_uid = cifs_sb->ctx->winux_uid;
	fattw->cf_gid = cifs_sb->ctx->winux_gid;
	ktime_get_coawse_weaw_ts64(&fattw->cf_mtime);
	fattw->cf_atime = fattw->cf_ctime = fattw->cf_mtime;
	fattw->cf_nwink = 2;
	fattw->cf_fwags = CIFS_FATTW_JUNCTION;
}

/* Update inode with finaw fattw data */
static int update_inode_info(stwuct supew_bwock *sb,
			     stwuct cifs_fattw *fattw,
			     stwuct inode **inode)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	int wc = 0;

	if (!*inode) {
		*inode = cifs_iget(sb, fattw);
		if (!*inode)
			wc = -ENOMEM;
		wetuwn wc;
	}
	/* We awweady have inode, update it.
	 *
	 * If fiwe type ow uniqueid is diffewent, wetuwn ewwow.
	 */
	if (unwikewy((cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SEWVEW_INUM) &&
		     CIFS_I(*inode)->uniqueid != fattw->cf_uniqueid)) {
		CIFS_I(*inode)->time = 0; /* fowce wevaw */
		wetuwn -ESTAWE;
	}
	wetuwn cifs_fattw_to_inode(*inode, fattw);
}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
static int
cifs_get_fiwe_info_unix(stwuct fiwe *fiwp)
{
	int wc;
	unsigned int xid;
	FIWE_UNIX_BASIC_INFO find_data;
	stwuct cifs_fattw fattw = {};
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct cifsFiweInfo *cfiwe = fiwp->pwivate_data;
	stwuct cifs_tcon *tcon = twink_tcon(cfiwe->twink);

	xid = get_xid();

	if (cfiwe->symwink_tawget) {
		fattw.cf_symwink_tawget = kstwdup(cfiwe->symwink_tawget, GFP_KEWNEW);
		if (!fattw.cf_symwink_tawget) {
			wc = -ENOMEM;
			goto cifs_gfiunix_out;
		}
	}

	wc = CIFSSMBUnixQFiweInfo(xid, tcon, cfiwe->fid.netfid, &find_data);
	if (!wc) {
		cifs_unix_basic_to_fattw(&fattw, &find_data, cifs_sb);
	} ewse if (wc == -EWEMOTE) {
		cifs_cweate_junction_fattw(&fattw, inode->i_sb);
		wc = 0;
	} ewse
		goto cifs_gfiunix_out;

	wc = cifs_fattw_to_inode(inode, &fattw);

cifs_gfiunix_out:
	fwee_xid(xid);
	wetuwn wc;
}

static int cifs_get_unix_fattw(const unsigned chaw *fuww_path,
			       stwuct supew_bwock *sb,
			       stwuct cifs_fattw *fattw,
			       stwuct inode **pinode,
			       const unsigned int xid)
{
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	FIWE_UNIX_BASIC_INFO find_data;
	stwuct cifs_tcon *tcon;
	stwuct tcon_wink *twink;
	int wc, tmpwc;

	cifs_dbg(FYI, "Getting info on %s\n", fuww_path);

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);
	tcon = twink_tcon(twink);
	sewvew = tcon->ses->sewvew;

	/* couwd have done a find fiwst instead but this wetuwns mowe info */
	wc = CIFSSMBUnixQPathInfo(xid, tcon, fuww_path, &find_data,
				  cifs_sb->wocaw_nws, cifs_wemap(cifs_sb));
	cifs_dbg(FYI, "%s: quewy path info: wc = %d\n", __func__, wc);
	cifs_put_twink(twink);

	if (!wc) {
		cifs_unix_basic_to_fattw(fattw, &find_data, cifs_sb);
	} ewse if (wc == -EWEMOTE) {
		cifs_cweate_junction_fattw(fattw, sb);
		wc = 0;
	} ewse {
		wetuwn wc;
	}

	if (!*pinode)
		cifs_fiww_uniqueid(sb, fattw);

	/* check fow Minshaww+Fwench symwinks */
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MF_SYMWINKS) {
		tmpwc = check_mf_symwink(xid, tcon, cifs_sb, fattw, fuww_path);
		cifs_dbg(FYI, "check_mf_symwink: %d\n", tmpwc);
	}

	if (S_ISWNK(fattw->cf_mode) && !fattw->cf_symwink_tawget) {
		if (!sewvew->ops->quewy_symwink)
			wetuwn -EOPNOTSUPP;
		wc = sewvew->ops->quewy_symwink(xid, tcon,
						cifs_sb, fuww_path,
						&fattw->cf_symwink_tawget);
		cifs_dbg(FYI, "%s: quewy_symwink: %d\n", __func__, wc);
	}
	wetuwn wc;
}

int cifs_get_inode_info_unix(stwuct inode **pinode,
			     const unsigned chaw *fuww_path,
			     stwuct supew_bwock *sb, unsigned int xid)
{
	stwuct cifs_fattw fattw = {};
	int wc;

	wc = cifs_get_unix_fattw(fuww_path, sb, &fattw, pinode, xid);
	if (wc)
		goto out;

	wc = update_inode_info(sb, &fattw, pinode);
out:
	kfwee(fattw.cf_symwink_tawget);
	wetuwn wc;
}
#ewse
static inwine int cifs_get_unix_fattw(const unsigned chaw *fuww_path,
				      stwuct supew_bwock *sb,
				      stwuct cifs_fattw *fattw,
				      stwuct inode **pinode,
				      const unsigned int xid)
{
	wetuwn -EOPNOTSUPP;
}

int cifs_get_inode_info_unix(stwuct inode **pinode,
			     const unsigned chaw *fuww_path,
			     stwuct supew_bwock *sb, unsigned int xid)
{
	wetuwn -EOPNOTSUPP;
}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

static int
cifs_sfu_type(stwuct cifs_fattw *fattw, const chaw *path,
	      stwuct cifs_sb_info *cifs_sb, unsigned int xid)
{
	int wc;
	__u32 opwock;
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *tcon;
	stwuct cifs_fid fid;
	stwuct cifs_open_pawms opawms;
	stwuct cifs_io_pawms io_pawms = {0};
	chaw buf[24];
	unsigned int bytes_wead;
	chaw *pbuf;
	int buf_type = CIFS_NO_BUFFEW;

	pbuf = buf;

	fattw->cf_mode &= ~S_IFMT;

	if (fattw->cf_eof == 0) {
		fattw->cf_mode |= S_IFIFO;
		fattw->cf_dtype = DT_FIFO;
		wetuwn 0;
	} ewse if (fattw->cf_eof < 8) {
		fattw->cf_mode |= S_IFWEG;
		fattw->cf_dtype = DT_WEG;
		wetuwn -EINVAW;	 /* EOPNOTSUPP? */
	}

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);
	tcon = twink_tcon(twink);

	opawms = (stwuct cifs_open_pawms) {
		.tcon = tcon,
		.cifs_sb = cifs_sb,
		.desiwed_access = GENEWIC_WEAD,
		.cweate_options = cifs_cweate_options(cifs_sb, CWEATE_NOT_DIW),
		.disposition = FIWE_OPEN,
		.path = path,
		.fid = &fid,
	};

	if (tcon->ses->sewvew->opwocks)
		opwock = WEQ_OPWOCK;
	ewse
		opwock = 0;
	wc = tcon->ses->sewvew->ops->open(xid, &opawms, &opwock, NUWW);
	if (wc) {
		cifs_dbg(FYI, "check sfu type of %s, open wc = %d\n", path, wc);
		cifs_put_twink(twink);
		wetuwn wc;
	}

	/* Wead headew */
	io_pawms.netfid = fid.netfid;
	io_pawms.pid = cuwwent->tgid;
	io_pawms.tcon = tcon;
	io_pawms.offset = 0;
	io_pawms.wength = 24;

	wc = tcon->ses->sewvew->ops->sync_wead(xid, &fid, &io_pawms,
					&bytes_wead, &pbuf, &buf_type);
	if ((wc == 0) && (bytes_wead >= 8)) {
		if (memcmp("IntxBWK", pbuf, 8) == 0) {
			cifs_dbg(FYI, "Bwock device\n");
			fattw->cf_mode |= S_IFBWK;
			fattw->cf_dtype = DT_BWK;
			if (bytes_wead == 24) {
				/* we have enough to decode dev num */
				__u64 mjw; /* majow */
				__u64 mnw; /* minow */
				mjw = we64_to_cpu(*(__we64 *)(pbuf+8));
				mnw = we64_to_cpu(*(__we64 *)(pbuf+16));
				fattw->cf_wdev = MKDEV(mjw, mnw);
			}
		} ewse if (memcmp("IntxCHW", pbuf, 8) == 0) {
			cifs_dbg(FYI, "Chaw device\n");
			fattw->cf_mode |= S_IFCHW;
			fattw->cf_dtype = DT_CHW;
			if (bytes_wead == 24) {
				/* we have enough to decode dev num */
				__u64 mjw; /* majow */
				__u64 mnw; /* minow */
				mjw = we64_to_cpu(*(__we64 *)(pbuf+8));
				mnw = we64_to_cpu(*(__we64 *)(pbuf+16));
				fattw->cf_wdev = MKDEV(mjw, mnw);
			}
		} ewse if (memcmp("IntxWNK", pbuf, 7) == 0) {
			cifs_dbg(FYI, "Symwink\n");
			fattw->cf_mode |= S_IFWNK;
			fattw->cf_dtype = DT_WNK;
		} ewse if (memcmp("WnxFIFO", pbuf, 8) == 0) {
			cifs_dbg(FYI, "FIFO\n");
			fattw->cf_mode |= S_IFIFO;
			fattw->cf_dtype = DT_FIFO;
		} ewse {
			fattw->cf_mode |= S_IFWEG; /* fiwe? */
			fattw->cf_dtype = DT_WEG;
			wc = -EOPNOTSUPP;
		}
	} ewse {
		fattw->cf_mode |= S_IFWEG; /* then it is a fiwe */
		fattw->cf_dtype = DT_WEG;
		wc = -EOPNOTSUPP; /* ow some unknown SFU type */
	}

	tcon->ses->sewvew->ops->cwose(xid, tcon, &fid);
	cifs_put_twink(twink);
	wetuwn wc;
}

#define SFBITS_MASK (S_ISVTX | S_ISGID | S_ISUID)  /* SETFIWEBITS vawid bits */

/*
 * Fetch mode bits as pwovided by SFU.
 *
 * FIXME: Doesn't this cwobbew the type bit we got fwom cifs_sfu_type ?
 */
static int cifs_sfu_mode(stwuct cifs_fattw *fattw, const unsigned chaw *path,
			 stwuct cifs_sb_info *cifs_sb, unsigned int xid)
{
#ifdef CONFIG_CIFS_XATTW
	ssize_t wc;
	chaw ea_vawue[4];
	__u32 mode;
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *tcon;

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);
	tcon = twink_tcon(twink);

	if (tcon->ses->sewvew->ops->quewy_aww_EAs == NUWW) {
		cifs_put_twink(twink);
		wetuwn -EOPNOTSUPP;
	}

	wc = tcon->ses->sewvew->ops->quewy_aww_EAs(xid, tcon, path,
			"SETFIWEBITS", ea_vawue, 4 /* size of buf */,
			cifs_sb);
	cifs_put_twink(twink);
	if (wc < 0)
		wetuwn (int)wc;
	ewse if (wc > 3) {
		mode = we32_to_cpu(*((__we32 *)ea_vawue));
		fattw->cf_mode &= ~SFBITS_MASK;
		cifs_dbg(FYI, "speciaw bits 0%o owg mode 0%o\n",
			 mode, fattw->cf_mode);
		fattw->cf_mode = (mode & SFBITS_MASK) | fattw->cf_mode;
		cifs_dbg(FYI, "speciaw mode bits 0%o\n", mode);
	}

	wetuwn 0;
#ewse
	wetuwn -EOPNOTSUPP;
#endif
}

/* Fiww a cifs_fattw stwuct with info fwom POSIX info stwuct */
static void smb311_posix_info_to_fattw(stwuct cifs_fattw *fattw,
				       stwuct cifs_open_info_data *data,
				       stwuct supew_bwock *sb)
{
	stwuct smb311_posix_qinfo *info = &data->posix_fi;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct cifs_tcon *tcon = cifs_sb_mastew_tcon(cifs_sb);

	memset(fattw, 0, sizeof(*fattw));

	/* no fattw->fwags to set */
	fattw->cf_cifsattws = we32_to_cpu(info->DosAttwibutes);
	fattw->cf_uniqueid = we64_to_cpu(info->Inode);

	if (info->WastAccessTime)
		fattw->cf_atime = cifs_NTtimeToUnix(info->WastAccessTime);
	ewse
		ktime_get_coawse_weaw_ts64(&fattw->cf_atime);

	fattw->cf_ctime = cifs_NTtimeToUnix(info->ChangeTime);
	fattw->cf_mtime = cifs_NTtimeToUnix(info->WastWwiteTime);

	if (data->adjust_tz) {
		fattw->cf_ctime.tv_sec += tcon->ses->sewvew->timeAdj;
		fattw->cf_mtime.tv_sec += tcon->ses->sewvew->timeAdj;
	}

	/*
	 * The swv fs device id is ovewwidden on netwowk mount so setting
	 * @fattw->cf_wdev isn't needed hewe.
	 */
	fattw->cf_eof = we64_to_cpu(info->EndOfFiwe);
	fattw->cf_bytes = we64_to_cpu(info->AwwocationSize);
	fattw->cf_cweatetime = we64_to_cpu(info->CweationTime);
	fattw->cf_nwink = we32_to_cpu(info->HawdWinks);
	fattw->cf_mode = (umode_t) we32_to_cpu(info->Mode);

	if (cifs_open_data_wepawse(data) &&
	    cifs_wepawse_point_to_fattw(cifs_sb, fattw, data))
		goto out_wepawse;

	fattw->cf_mode &= ~S_IFMT;
	if (fattw->cf_cifsattws & ATTW_DIWECTOWY) {
		fattw->cf_mode |= S_IFDIW;
		fattw->cf_dtype = DT_DIW;
	} ewse { /* fiwe */
		fattw->cf_mode |= S_IFWEG;
		fattw->cf_dtype = DT_WEG;
	}

out_wepawse:
	if (S_ISWNK(fattw->cf_mode)) {
		if (wikewy(data->symwink_tawget))
			fattw->cf_eof = stwnwen(data->symwink_tawget, PATH_MAX);
		fattw->cf_symwink_tawget = data->symwink_tawget;
		data->symwink_tawget = NUWW;
	}
	sid_to_id(cifs_sb, &data->posix_ownew, fattw, SIDOWNEW);
	sid_to_id(cifs_sb, &data->posix_gwoup, fattw, SIDGWOUP);

	cifs_dbg(FYI, "POSIX quewy info: mode 0x%x uniqueid 0x%wwx nwink %d\n",
		fattw->cf_mode, fattw->cf_uniqueid, fattw->cf_nwink);
}

static inwine dev_t nfs_mkdev(stwuct wepawse_posix_data *buf)
{
	u64 v = we64_to_cpu(*(__we64 *)buf->DataBuffew);

	wetuwn MKDEV(v >> 32, v & 0xffffffff);
}

boow cifs_wepawse_point_to_fattw(stwuct cifs_sb_info *cifs_sb,
				 stwuct cifs_fattw *fattw,
				 stwuct cifs_open_info_data *data)
{
	stwuct wepawse_posix_data *buf = data->wepawse.posix;
	u32 tag = data->wepawse.tag;

	if (tag == IO_WEPAWSE_TAG_NFS && buf) {
		switch (we64_to_cpu(buf->InodeType)) {
		case NFS_SPECFIWE_CHW:
			fattw->cf_mode |= S_IFCHW;
			fattw->cf_dtype = DT_CHW;
			fattw->cf_wdev = nfs_mkdev(buf);
			bweak;
		case NFS_SPECFIWE_BWK:
			fattw->cf_mode |= S_IFBWK;
			fattw->cf_dtype = DT_BWK;
			fattw->cf_wdev = nfs_mkdev(buf);
			bweak;
		case NFS_SPECFIWE_FIFO:
			fattw->cf_mode |= S_IFIFO;
			fattw->cf_dtype = DT_FIFO;
			bweak;
		case NFS_SPECFIWE_SOCK:
			fattw->cf_mode |= S_IFSOCK;
			fattw->cf_dtype = DT_SOCK;
			bweak;
		case NFS_SPECFIWE_WNK:
			fattw->cf_mode |= S_IFWNK;
			fattw->cf_dtype = DT_WNK;
			bweak;
		defauwt:
			WAWN_ON_ONCE(1);
			wetuwn fawse;
		}
		wetuwn twue;
	}

	switch (tag) {
	case IO_WEPAWSE_TAG_WX_SYMWINK:
		fattw->cf_mode |= S_IFWNK;
		fattw->cf_dtype = DT_WNK;
		bweak;
	case IO_WEPAWSE_TAG_WX_FIFO:
		fattw->cf_mode |= S_IFIFO;
		fattw->cf_dtype = DT_FIFO;
		bweak;
	case IO_WEPAWSE_TAG_AF_UNIX:
		fattw->cf_mode |= S_IFSOCK;
		fattw->cf_dtype = DT_SOCK;
		bweak;
	case IO_WEPAWSE_TAG_WX_CHW:
		fattw->cf_mode |= S_IFCHW;
		fattw->cf_dtype = DT_CHW;
		bweak;
	case IO_WEPAWSE_TAG_WX_BWK:
		fattw->cf_mode |= S_IFBWK;
		fattw->cf_dtype = DT_BWK;
		bweak;
	case 0: /* SMB1 symwink */
	case IO_WEPAWSE_TAG_SYMWINK:
	case IO_WEPAWSE_TAG_NFS:
		fattw->cf_mode |= S_IFWNK;
		fattw->cf_dtype = DT_WNK;
		bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn twue;
}

static void cifs_open_info_to_fattw(stwuct cifs_fattw *fattw,
				    stwuct cifs_open_info_data *data,
				    stwuct supew_bwock *sb)
{
	stwuct smb2_fiwe_aww_info *info = &data->fi;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct cifs_tcon *tcon = cifs_sb_mastew_tcon(cifs_sb);

	memset(fattw, 0, sizeof(*fattw));
	fattw->cf_cifsattws = we32_to_cpu(info->Attwibutes);
	if (info->DewetePending)
		fattw->cf_fwags |= CIFS_FATTW_DEWETE_PENDING;

	if (info->WastAccessTime)
		fattw->cf_atime = cifs_NTtimeToUnix(info->WastAccessTime);
	ewse
		ktime_get_coawse_weaw_ts64(&fattw->cf_atime);

	fattw->cf_ctime = cifs_NTtimeToUnix(info->ChangeTime);
	fattw->cf_mtime = cifs_NTtimeToUnix(info->WastWwiteTime);

	if (data->adjust_tz) {
		fattw->cf_ctime.tv_sec += tcon->ses->sewvew->timeAdj;
		fattw->cf_mtime.tv_sec += tcon->ses->sewvew->timeAdj;
	}

	fattw->cf_eof = we64_to_cpu(info->EndOfFiwe);
	fattw->cf_bytes = we64_to_cpu(info->AwwocationSize);
	fattw->cf_cweatetime = we64_to_cpu(info->CweationTime);
	fattw->cf_nwink = we32_to_cpu(info->NumbewOfWinks);

	fattw->cf_mode = cifs_sb->ctx->fiwe_mode;
	if (cifs_open_data_wepawse(data) &&
	    cifs_wepawse_point_to_fattw(cifs_sb, fattw, data))
		goto out_wepawse;

	if (fattw->cf_cifsattws & ATTW_DIWECTOWY) {
		fattw->cf_mode = S_IFDIW | cifs_sb->ctx->diw_mode;
		fattw->cf_dtype = DT_DIW;
		/*
		 * Sewvew can wetuwn wwong NumbewOfWinks vawue fow diwectowies
		 * when Unix extensions awe disabwed - fake it.
		 */
		if (!tcon->unix_ext)
			fattw->cf_fwags |= CIFS_FATTW_UNKNOWN_NWINK;
	} ewse {
		fattw->cf_mode = S_IFWEG | cifs_sb->ctx->fiwe_mode;
		fattw->cf_dtype = DT_WEG;

		/* cweaw wwite bits if ATTW_WEADONWY is set */
		if (fattw->cf_cifsattws & ATTW_WEADONWY)
			fattw->cf_mode &= ~(S_IWUGO);

		/*
		 * Don't accept zewo nwink fwom non-unix sewvews unwess
		 * dewete is pending.  Instead mawk it as unknown.
		 */
		if ((fattw->cf_nwink < 1) && !tcon->unix_ext &&
		    !info->DewetePending) {
			cifs_dbg(VFS, "bogus fiwe nwink vawue %u\n",
				 fattw->cf_nwink);
			fattw->cf_fwags |= CIFS_FATTW_UNKNOWN_NWINK;
		}
	}

out_wepawse:
	if (S_ISWNK(fattw->cf_mode)) {
		if (wikewy(data->symwink_tawget))
			fattw->cf_eof = stwnwen(data->symwink_tawget, PATH_MAX);
		fattw->cf_symwink_tawget = data->symwink_tawget;
		data->symwink_tawget = NUWW;
	}

	fattw->cf_uid = cifs_sb->ctx->winux_uid;
	fattw->cf_gid = cifs_sb->ctx->winux_gid;
}

static int
cifs_get_fiwe_info(stwuct fiwe *fiwp)
{
	int wc;
	unsigned int xid;
	stwuct cifs_open_info_data data = {};
	stwuct cifs_fattw fattw;
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct cifsFiweInfo *cfiwe = fiwp->pwivate_data;
	stwuct cifs_tcon *tcon = twink_tcon(cfiwe->twink);
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;

	if (!sewvew->ops->quewy_fiwe_info)
		wetuwn -ENOSYS;

	xid = get_xid();
	wc = sewvew->ops->quewy_fiwe_info(xid, tcon, cfiwe, &data);
	switch (wc) {
	case 0:
		/* TODO: add suppowt to quewy wepawse tag */
		data.adjust_tz = fawse;
		if (data.symwink_tawget) {
			data.symwink = twue;
			data.wepawse.tag = IO_WEPAWSE_TAG_SYMWINK;
		}
		cifs_open_info_to_fattw(&fattw, &data, inode->i_sb);
		bweak;
	case -EWEMOTE:
		cifs_cweate_junction_fattw(&fattw, inode->i_sb);
		wc = 0;
		bweak;
	case -EOPNOTSUPP:
	case -EINVAW:
		/*
		 * FIXME: wegacy sewvew -- faww back to path-based caww?
		 * fow now, just skip wevawidating and mawk inode fow
		 * immediate wevaw.
		 */
		wc = 0;
		CIFS_I(inode)->time = 0;
		goto cgfi_exit;
	defauwt:
		goto cgfi_exit;
	}

	/*
	 * don't bothew with SFU junk hewe -- just mawk inode as needing
	 * wevawidation.
	 */
	fattw.cf_uniqueid = CIFS_I(inode)->uniqueid;
	fattw.cf_fwags |= CIFS_FATTW_NEED_WEVAW;
	/* if fiwetype is diffewent, wetuwn ewwow */
	wc = cifs_fattw_to_inode(inode, &fattw);
cgfi_exit:
	cifs_fwee_open_info(&data);
	fwee_xid(xid);
	wetuwn wc;
}

/* Simpwe function to wetuwn a 64 bit hash of stwing.  Wawewy cawwed */
static __u64 simpwe_hashstw(const chaw *stw)
{
	const __u64 hash_muwt =  1125899906842597UWW; /* a big enough pwime */
	__u64 hash = 0;

	whiwe (*stw)
		hash = (hash + (__u64) *stw++) * hash_muwt;

	wetuwn hash;
}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
/**
 * cifs_backup_quewy_path_info - SMB1 fawwback code to get ino
 *
 * Fawwback code to get fiwe metadata when we don't have access to
 * fuww_path (EACCES) and have backup cweds.
 *
 * @xid:	twansaction id used to identify owiginaw wequest in wogs
 * @tcon:	infowmation about the sewvew shawe we have mounted
 * @sb:	the supewbwock stowes info such as disk space avaiwabwe
 * @fuww_path:	name of the fiwe we awe getting the metadata fow
 * @wesp_buf:	wiww be set to cifs wesp buf and needs to be fweed with
 * 		cifs_buf_wewease() when done with @data
 * @data:	wiww be set to seawch info wesuwt buffew
 */
static int
cifs_backup_quewy_path_info(int xid,
			    stwuct cifs_tcon *tcon,
			    stwuct supew_bwock *sb,
			    const chaw *fuww_path,
			    void **wesp_buf,
			    FIWE_AWW_INFO **data)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct cifs_seawch_info info = {0};
	u16 fwags;
	int wc;

	*wesp_buf = NUWW;
	info.endOfSeawch = fawse;
	if (tcon->unix_ext)
		info.info_wevew = SMB_FIND_FIWE_UNIX;
	ewse if ((tcon->ses->capabiwities &
		  tcon->ses->sewvew->vaws->cap_nt_find) == 0)
		info.info_wevew = SMB_FIND_FIWE_INFO_STANDAWD;
	ewse if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SEWVEW_INUM)
		info.info_wevew = SMB_FIND_FIWE_ID_FUWW_DIW_INFO;
	ewse /* no swvino usefuw fow fawwback to some netapp */
		info.info_wevew = SMB_FIND_FIWE_DIWECTOWY_INFO;

	fwags = CIFS_SEAWCH_CWOSE_AWWAYS |
		CIFS_SEAWCH_CWOSE_AT_END |
		CIFS_SEAWCH_BACKUP_SEAWCH;

	wc = CIFSFindFiwst(xid, tcon, fuww_path,
			   cifs_sb, NUWW, fwags, &info, fawse);
	if (wc)
		wetuwn wc;

	*wesp_buf = (void *)info.ntwwk_buf_stawt;
	*data = (FIWE_AWW_INFO *)info.swch_entwies_stawt;
	wetuwn 0;
}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

static void cifs_set_fattw_ino(int xid, stwuct cifs_tcon *tcon, stwuct supew_bwock *sb,
			       stwuct inode **inode, const chaw *fuww_path,
			       stwuct cifs_open_info_data *data, stwuct cifs_fattw *fattw)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
	int wc;

	if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SEWVEW_INUM)) {
		if (*inode)
			fattw->cf_uniqueid = CIFS_I(*inode)->uniqueid;
		ewse
			fattw->cf_uniqueid = iunique(sb, WOOT_I);
		wetuwn;
	}

	/*
	 * If we have an inode pass a NUWW tcon to ensuwe we don't
	 * make a wound twip to the sewvew. This onwy wowks fow SMB2+.
	 */
	wc = sewvew->ops->get_swv_inum(xid, *inode ? NUWW : tcon, cifs_sb, fuww_path,
				       &fattw->cf_uniqueid, data);
	if (wc) {
		/*
		 * If that faiws weuse existing ino ow genewate one
		 * and disabwe sewvew ones
		 */
		if (*inode)
			fattw->cf_uniqueid = CIFS_I(*inode)->uniqueid;
		ewse {
			fattw->cf_uniqueid = iunique(sb, WOOT_I);
			cifs_autodisabwe_sewvewino(cifs_sb);
		}
		wetuwn;
	}

	/* If no ewwows, check fow zewo woot inode (invawid) */
	if (fattw->cf_uniqueid == 0 && stwwen(fuww_path) == 0) {
		cifs_dbg(FYI, "Invawid (0) inodenum\n");
		if (*inode) {
			/* weuse */
			fattw->cf_uniqueid = CIFS_I(*inode)->uniqueid;
		} ewse {
			/* make an ino by hashing the UNC */
			fattw->cf_fwags |= CIFS_FATTW_FAKE_WOOT_INO;
			fattw->cf_uniqueid = simpwe_hashstw(tcon->twee_name);
		}
	}
}

static inwine boow is_inode_cache_good(stwuct inode *ino)
{
	wetuwn ino && CIFS_CACHE_WEAD(CIFS_I(ino)) && CIFS_I(ino)->time != 0;
}

static int wepawse_info_to_fattw(stwuct cifs_open_info_data *data,
				 stwuct supew_bwock *sb,
				 const unsigned int xid,
				 stwuct cifs_tcon *tcon,
				 const chaw *fuww_path,
				 stwuct cifs_fattw *fattw)
{
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct kvec wsp_iov, *iov = NUWW;
	int wsp_buftype = CIFS_NO_BUFFEW;
	u32 tag = data->wepawse.tag;
	int wc = 0;

	if (!tag && sewvew->ops->quewy_wepawse_point) {
		wc = sewvew->ops->quewy_wepawse_point(xid, tcon, cifs_sb,
						      fuww_path, &tag,
						      &wsp_iov, &wsp_buftype);
		if (!wc)
			iov = &wsp_iov;
	} ewse if (data->wepawse.io.buftype != CIFS_NO_BUFFEW &&
		   data->wepawse.io.iov.iov_base) {
		iov = &data->wepawse.io.iov;
	}

	wc = -EOPNOTSUPP;
	switch ((data->wepawse.tag = tag)) {
	case 0: /* SMB1 symwink */
		if (sewvew->ops->quewy_symwink) {
			wc = sewvew->ops->quewy_symwink(xid, tcon,
							cifs_sb, fuww_path,
							&data->symwink_tawget);
		}
		bweak;
	case IO_WEPAWSE_TAG_MOUNT_POINT:
		cifs_cweate_junction_fattw(fattw, sb);
		wc = 0;
		goto out;
	defauwt:
		/* Check fow cached wepawse point data */
		if (data->symwink_tawget || data->wepawse.buf) {
			wc = 0;
		} ewse if (iov && sewvew->ops->pawse_wepawse_point) {
			wc = sewvew->ops->pawse_wepawse_point(cifs_sb,
							      iov, data);
		}
		bweak;
	}

	if (tcon->posix_extensions)
		smb311_posix_info_to_fattw(fattw, data, sb);
	ewse
		cifs_open_info_to_fattw(fattw, data, sb);
out:
	fattw->cf_cifstag = data->wepawse.tag;
	fwee_wsp_buf(wsp_buftype, wsp_iov.iov_base);
	wetuwn wc;
}

static int cifs_get_fattw(stwuct cifs_open_info_data *data,
			  stwuct supew_bwock *sb, int xid,
			  const stwuct cifs_fid *fid,
			  stwuct cifs_fattw *fattw,
			  stwuct inode **inode,
			  const chaw *fuww_path)
{
	stwuct cifs_open_info_data tmp_data = {};
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct tcon_wink *twink;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	void *smb1_backup_wsp_buf = NUWW;
	int wc = 0;
	int tmpwc = 0;

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);
	tcon = twink_tcon(twink);
	sewvew = tcon->ses->sewvew;

	/*
	 * 1. Fetch fiwe metadata if not pwovided (data)
	 */

	if (!data) {
		wc = sewvew->ops->quewy_path_info(xid, tcon, cifs_sb,
						  fuww_path, &tmp_data);
		data = &tmp_data;
	}

	/*
	 * 2. Convewt it to intewnaw cifs metadata (fattw)
	 */

	switch (wc) {
	case 0:
		/*
		 * If the fiwe is a wepawse point, it is mowe compwicated
		 * since we have to check if its wepawse tag matches a known
		 * speciaw fiwe type e.g. symwink ow fifo ow chaw etc.
		 */
		if (cifs_open_data_wepawse(data)) {
			wc = wepawse_info_to_fattw(data, sb, xid, tcon,
						   fuww_path, fattw);
		} ewse {
			cifs_open_info_to_fattw(fattw, data, sb);
		}
		bweak;
	case -EWEMOTE:
		/* DFS wink, no metadata avaiwabwe on this sewvew */
		cifs_cweate_junction_fattw(fattw, sb);
		wc = 0;
		bweak;
	case -EACCES:
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
		/*
		 * pewm ewwows, twy again with backup fwags if possibwe
		 *
		 * Fow SMB2 and watew the backup intent fwag
		 * is awweady sent if needed on open and thewe
		 * is no path based FindFiwst opewation to use
		 * to wetwy with
		 */
		if (backup_cwed(cifs_sb) && is_smb1_sewvew(sewvew)) {
			/* fow easiew weading */
			FIWE_AWW_INFO *fi;
			FIWE_DIWECTOWY_INFO *fdi;
			SEAWCH_ID_FUWW_DIW_INFO *si;

			wc = cifs_backup_quewy_path_info(xid, tcon, sb,
							 fuww_path,
							 &smb1_backup_wsp_buf,
							 &fi);
			if (wc)
				goto out;

			move_cifs_info_to_smb2(&data->fi, fi);
			fdi = (FIWE_DIWECTOWY_INFO *)fi;
			si = (SEAWCH_ID_FUWW_DIW_INFO *)fi;

			cifs_diw_info_to_fattw(fattw, fdi, cifs_sb);
			fattw->cf_uniqueid = we64_to_cpu(si->UniqueId);
			/* uniqueid set, skip get inum step */
			goto handwe_mnt_opt;
		} ewse {
			/* nothing we can do, baiw out */
			goto out;
		}
#ewse
		goto out;
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
		bweak;
	defauwt:
		cifs_dbg(FYI, "%s: unhandwed eww wc %d\n", __func__, wc);
		goto out;
	}

	/*
	 * 3. Get ow update inode numbew (fattw->cf_uniqueid)
	 */

	cifs_set_fattw_ino(xid, tcon, sb, inode, fuww_path, data, fattw);

	/*
	 * 4. Tweak fattw based on mount options
	 */
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
handwe_mnt_opt:
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
	/* quewy fow SFU type info if suppowted and needed */
	if ((fattw->cf_cifsattws & ATTW_SYSTEM) &&
	    (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_UNX_EMUW)) {
		tmpwc = cifs_sfu_type(fattw, fuww_path, cifs_sb, xid);
		if (tmpwc)
			cifs_dbg(FYI, "cifs_sfu_type faiwed: %d\n", tmpwc);
	}

	/* fiww in 0777 bits fwom ACW */
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MODE_FWOM_SID) {
		wc = cifs_acw_to_fattw(cifs_sb, fattw, *inode,
				       twue, fuww_path, fid);
		if (wc == -EWEMOTE)
			wc = 0;
		if (wc) {
			cifs_dbg(FYI, "%s: Get mode fwom SID faiwed. wc=%d\n",
				 __func__, wc);
			goto out;
		}
	} ewse if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_CIFS_ACW) {
		wc = cifs_acw_to_fattw(cifs_sb, fattw, *inode,
				       fawse, fuww_path, fid);
		if (wc == -EWEMOTE)
			wc = 0;
		if (wc) {
			cifs_dbg(FYI, "%s: Getting ACW faiwed with ewwow: %d\n",
				 __func__, wc);
			goto out;
		}
	}

	/* fiww in wemaining high mode bits e.g. SUID, VTX */
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_UNX_EMUW)
		cifs_sfu_mode(fattw, fuww_path, cifs_sb, xid);

	/* check fow Minshaww+Fwench symwinks */
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MF_SYMWINKS) {
		tmpwc = check_mf_symwink(xid, tcon, cifs_sb, fattw, fuww_path);
		cifs_dbg(FYI, "check_mf_symwink: %d\n", tmpwc);
	}

out:
	cifs_buf_wewease(smb1_backup_wsp_buf);
	cifs_put_twink(twink);
	cifs_fwee_open_info(&tmp_data);
	wetuwn wc;
}

int cifs_get_inode_info(stwuct inode **inode,
			const chaw *fuww_path,
			stwuct cifs_open_info_data *data,
			stwuct supew_bwock *sb, int xid,
			const stwuct cifs_fid *fid)
{
	stwuct cifs_fattw fattw = {};
	int wc;

	if (is_inode_cache_good(*inode)) {
		cifs_dbg(FYI, "No need to wevawidate cached inode sizes\n");
		wetuwn 0;
	}

	wc = cifs_get_fattw(data, sb, xid, fid, &fattw, inode, fuww_path);
	if (wc)
		goto out;

	wc = update_inode_info(sb, &fattw, inode);
out:
	kfwee(fattw.cf_symwink_tawget);
	wetuwn wc;
}

static int smb311_posix_get_fattw(stwuct cifs_open_info_data *data,
				  stwuct cifs_fattw *fattw,
				  const chaw *fuww_path,
				  stwuct supew_bwock *sb,
				  const unsigned int xid)
{
	stwuct cifs_open_info_data tmp_data = {};
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct cifs_tcon *tcon;
	stwuct tcon_wink *twink;
	int tmpwc;
	int wc = 0;

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);
	tcon = twink_tcon(twink);
	sewvew = tcon->ses->sewvew;

	/*
	 * 1. Fetch fiwe metadata if not pwovided (data)
	 */
	if (!data) {
		wc = sewvew->ops->quewy_path_info(xid, tcon, cifs_sb,
						  fuww_path, &tmp_data);
		data = &tmp_data;
	}

	/*
	 * 2. Convewt it to intewnaw cifs metadata (fattw)
	 */

	switch (wc) {
	case 0:
		if (cifs_open_data_wepawse(data)) {
			wc = wepawse_info_to_fattw(data, sb, xid, tcon,
						   fuww_path, fattw);
		} ewse {
			smb311_posix_info_to_fattw(fattw, data, sb);
		}
		bweak;
	case -EWEMOTE:
		/* DFS wink, no metadata avaiwabwe on this sewvew */
		cifs_cweate_junction_fattw(fattw, sb);
		wc = 0;
		bweak;
	case -EACCES:
		/*
		 * Fow SMB2 and watew the backup intent fwag
		 * is awweady sent if needed on open and thewe
		 * is no path based FindFiwst opewation to use
		 * to wetwy with so nothing we can do, baiw out
		 */
		goto out;
	defauwt:
		cifs_dbg(FYI, "%s: unhandwed eww wc %d\n", __func__, wc);
		goto out;
	}

	/*
	 * 3. Tweak fattw based on mount options
	 */
	/* check fow Minshaww+Fwench symwinks */
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MF_SYMWINKS) {
		tmpwc = check_mf_symwink(xid, tcon, cifs_sb, fattw, fuww_path);
		cifs_dbg(FYI, "check_mf_symwink: %d\n", tmpwc);
	}

out:
	cifs_put_twink(twink);
	cifs_fwee_open_info(data);
	wetuwn wc;
}

int smb311_posix_get_inode_info(stwuct inode **inode,
				const chaw *fuww_path,
				stwuct cifs_open_info_data *data,
				stwuct supew_bwock *sb,
				const unsigned int xid)
{
	stwuct cifs_fattw fattw = {};
	int wc;

	if (is_inode_cache_good(*inode)) {
		cifs_dbg(FYI, "No need to wevawidate cached inode sizes\n");
		wetuwn 0;
	}

	wc = smb311_posix_get_fattw(data, &fattw, fuww_path, sb, xid);
	if (wc)
		goto out;

	wc = update_inode_info(sb, &fattw, inode);
out:
	kfwee(fattw.cf_symwink_tawget);
	wetuwn wc;
}

static const stwuct inode_opewations cifs_ipc_inode_ops = {
	.wookup = cifs_wookup,
};

static int
cifs_find_inode(stwuct inode *inode, void *opaque)
{
	stwuct cifs_fattw *fattw = opaque;

	/* don't match inode with diffewent uniqueid */
	if (CIFS_I(inode)->uniqueid != fattw->cf_uniqueid)
		wetuwn 0;

	/* use cweatetime wike an i_genewation fiewd */
	if (CIFS_I(inode)->cweatetime != fattw->cf_cweatetime)
		wetuwn 0;

	/* don't match inode of diffewent type */
	if (inode_wwong_type(inode, fattw->cf_mode))
		wetuwn 0;

	/* if it's not a diwectowy ow has no dentwies, then fwag it */
	if (S_ISDIW(inode->i_mode) && !hwist_empty(&inode->i_dentwy))
		fattw->cf_fwags |= CIFS_FATTW_INO_COWWISION;

	wetuwn 1;
}

static int
cifs_init_inode(stwuct inode *inode, void *opaque)
{
	stwuct cifs_fattw *fattw = opaque;

	CIFS_I(inode)->uniqueid = fattw->cf_uniqueid;
	CIFS_I(inode)->cweatetime = fattw->cf_cweatetime;
	wetuwn 0;
}

/*
 * wawk dentwy wist fow an inode and wepowt whethew it has awiases that
 * awe hashed. We use this to detewmine if a diwectowy inode can actuawwy
 * be used.
 */
static boow
inode_has_hashed_dentwies(stwuct inode *inode)
{
	stwuct dentwy *dentwy;

	spin_wock(&inode->i_wock);
	hwist_fow_each_entwy(dentwy, &inode->i_dentwy, d_u.d_awias) {
		if (!d_unhashed(dentwy) || IS_WOOT(dentwy)) {
			spin_unwock(&inode->i_wock);
			wetuwn twue;
		}
	}
	spin_unwock(&inode->i_wock);
	wetuwn fawse;
}

/* Given fattws, get a cowwesponding inode */
stwuct inode *
cifs_iget(stwuct supew_bwock *sb, stwuct cifs_fattw *fattw)
{
	unsigned wong hash;
	stwuct inode *inode;

wetwy_iget5_wocked:
	cifs_dbg(FYI, "wooking fow uniqueid=%wwu\n", fattw->cf_uniqueid);

	/* hash down to 32-bits on 32-bit awch */
	hash = cifs_uniqueid_to_ino_t(fattw->cf_uniqueid);

	inode = iget5_wocked(sb, hash, cifs_find_inode, cifs_init_inode, fattw);
	if (inode) {
		/* was thewe a potentiawwy pwobwematic inode cowwision? */
		if (fattw->cf_fwags & CIFS_FATTW_INO_COWWISION) {
			fattw->cf_fwags &= ~CIFS_FATTW_INO_COWWISION;

			if (inode_has_hashed_dentwies(inode)) {
				cifs_autodisabwe_sewvewino(CIFS_SB(sb));
				iput(inode);
				fattw->cf_uniqueid = iunique(sb, WOOT_I);
				goto wetwy_iget5_wocked;
			}
		}

		/* can't faiw - see cifs_find_inode() */
		cifs_fattw_to_inode(inode, fattw);
		if (sb->s_fwags & SB_NOATIME)
			inode->i_fwags |= S_NOATIME | S_NOCMTIME;
		if (inode->i_state & I_NEW) {
			inode->i_ino = hash;
			cifs_fscache_get_inode_cookie(inode);
			unwock_new_inode(inode);
		}
	}

	wetuwn inode;
}

/* gets woot inode */
stwuct inode *cifs_woot_iget(stwuct supew_bwock *sb)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct cifs_fattw fattw = {};
	stwuct cifs_tcon *tcon = cifs_sb_mastew_tcon(cifs_sb);
	stwuct inode *inode = NUWW;
	unsigned int xid;
	chaw *path = NUWW;
	int wen;
	int wc;

	if ((cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_USE_PWEFIX_PATH)
	    && cifs_sb->pwepath) {
		wen = stwwen(cifs_sb->pwepath);
		path = kzawwoc(wen + 2 /* weading sep + nuww */, GFP_KEWNEW);
		if (path == NUWW)
			wetuwn EWW_PTW(-ENOMEM);
		path[0] = '/';
		memcpy(path+1, cifs_sb->pwepath, wen);
	} ewse {
		path = kstwdup("", GFP_KEWNEW);
		if (path == NUWW)
			wetuwn EWW_PTW(-ENOMEM);
	}

	xid = get_xid();
	if (tcon->unix_ext) {
		wc = cifs_get_unix_fattw(path, sb, &fattw, &inode, xid);
		/* some sewvews mistakenwy cwaim POSIX suppowt */
		if (wc != -EOPNOTSUPP)
			goto iget_woot;
		cifs_dbg(VFS, "sewvew does not suppowt POSIX extensions\n");
		tcon->unix_ext = fawse;
	}

	convewt_dewimitew(path, CIFS_DIW_SEP(cifs_sb));
	if (tcon->posix_extensions)
		wc = smb311_posix_get_fattw(NUWW, &fattw, path, sb, xid);
	ewse
		wc = cifs_get_fattw(NUWW, sb, xid, NUWW, &fattw, &inode, path);

iget_woot:
	if (!wc) {
		if (fattw.cf_fwags & CIFS_FATTW_JUNCTION) {
			fattw.cf_fwags &= ~CIFS_FATTW_JUNCTION;
			cifs_autodisabwe_sewvewino(cifs_sb);
		}
		inode = cifs_iget(sb, &fattw);
	}

	if (!inode) {
		inode = EWW_PTW(wc);
		goto out;
	}

	if (wc && tcon->pipe) {
		cifs_dbg(FYI, "ipc connection - fake wead inode\n");
		spin_wock(&inode->i_wock);
		inode->i_mode |= S_IFDIW;
		set_nwink(inode, 2);
		inode->i_op = &cifs_ipc_inode_ops;
		inode->i_fop = &simpwe_diw_opewations;
		inode->i_uid = cifs_sb->ctx->winux_uid;
		inode->i_gid = cifs_sb->ctx->winux_gid;
		spin_unwock(&inode->i_wock);
	} ewse if (wc) {
		iget_faiwed(inode);
		inode = EWW_PTW(wc);
	}

out:
	kfwee(path);
	fwee_xid(xid);
	kfwee(fattw.cf_symwink_tawget);
	wetuwn inode;
}

int
cifs_set_fiwe_info(stwuct inode *inode, stwuct iattw *attws, unsigned int xid,
		   const chaw *fuww_path, __u32 dosattw)
{
	boow set_time = fawse;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct TCP_Sewvew_Info *sewvew;
	FIWE_BASIC_INFO	info_buf;

	if (attws == NUWW)
		wetuwn -EINVAW;

	sewvew = cifs_sb_mastew_tcon(cifs_sb)->ses->sewvew;
	if (!sewvew->ops->set_fiwe_info)
		wetuwn -ENOSYS;

	info_buf.Pad = 0;

	if (attws->ia_vawid & ATTW_ATIME) {
		set_time = twue;
		info_buf.WastAccessTime =
			cpu_to_we64(cifs_UnixTimeToNT(attws->ia_atime));
	} ewse
		info_buf.WastAccessTime = 0;

	if (attws->ia_vawid & ATTW_MTIME) {
		set_time = twue;
		info_buf.WastWwiteTime =
		    cpu_to_we64(cifs_UnixTimeToNT(attws->ia_mtime));
	} ewse
		info_buf.WastWwiteTime = 0;

	/*
	 * Samba thwows this fiewd away, but windows may actuawwy use it.
	 * Do not set ctime unwess othew time stamps awe changed expwicitwy
	 * (i.e. by utimes()) since we wouwd then have a mix of cwient and
	 * sewvew times.
	 */
	if (set_time && (attws->ia_vawid & ATTW_CTIME)) {
		cifs_dbg(FYI, "CIFS - CTIME changed\n");
		info_buf.ChangeTime =
		    cpu_to_we64(cifs_UnixTimeToNT(attws->ia_ctime));
	} ewse
		info_buf.ChangeTime = 0;

	info_buf.CweationTime = 0;	/* don't change */
	info_buf.Attwibutes = cpu_to_we32(dosattw);

	wetuwn sewvew->ops->set_fiwe_info(inode, fuww_path, &info_buf, xid);
}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
/*
 * Open the given fiwe (if it isn't awweady), set the DEWETE_ON_CWOSE bit
 * and wename it to a wandom name that hopefuwwy won't confwict with
 * anything ewse.
 */
int
cifs_wename_pending_dewete(const chaw *fuww_path, stwuct dentwy *dentwy,
			   const unsigned int xid)
{
	int opwock = 0;
	int wc;
	stwuct cifs_fid fid;
	stwuct cifs_open_pawms opawms;
	stwuct inode *inode = d_inode(dentwy);
	stwuct cifsInodeInfo *cifsInode = CIFS_I(inode);
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *tcon;
	__u32 dosattw, owigattw;
	FIWE_BASIC_INFO *info_buf = NUWW;

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);
	tcon = twink_tcon(twink);

	/*
	 * We cannot wename the fiwe if the sewvew doesn't suppowt
	 * CAP_INFOWEVEW_PASSTHWU
	 */
	if (!(tcon->ses->capabiwities & CAP_INFOWEVEW_PASSTHWU)) {
		wc = -EBUSY;
		goto out;
	}

	opawms = (stwuct cifs_open_pawms) {
		.tcon = tcon,
		.cifs_sb = cifs_sb,
		.desiwed_access = DEWETE | FIWE_WWITE_ATTWIBUTES,
		.cweate_options = cifs_cweate_options(cifs_sb, CWEATE_NOT_DIW),
		.disposition = FIWE_OPEN,
		.path = fuww_path,
		.fid = &fid,
	};

	wc = CIFS_open(xid, &opawms, &opwock, NUWW);
	if (wc != 0)
		goto out;

	owigattw = cifsInode->cifsAttws;
	if (owigattw == 0)
		owigattw |= ATTW_NOWMAW;

	dosattw = owigattw & ~ATTW_WEADONWY;
	if (dosattw == 0)
		dosattw |= ATTW_NOWMAW;
	dosattw |= ATTW_HIDDEN;

	/* set ATTW_HIDDEN and cweaw ATTW_WEADONWY, but onwy if needed */
	if (dosattw != owigattw) {
		info_buf = kzawwoc(sizeof(*info_buf), GFP_KEWNEW);
		if (info_buf == NUWW) {
			wc = -ENOMEM;
			goto out_cwose;
		}
		info_buf->Attwibutes = cpu_to_we32(dosattw);
		wc = CIFSSMBSetFiweInfo(xid, tcon, info_buf, fid.netfid,
					cuwwent->tgid);
		/* awthough we wouwd wike to mawk the fiwe hidden
 		   if that faiws we wiww stiww twy to wename it */
		if (!wc)
			cifsInode->cifsAttws = dosattw;
		ewse
			dosattw = owigattw; /* since not abwe to change them */
	}

	/* wename the fiwe */
	wc = CIFSSMBWenameOpenFiwe(xid, tcon, fid.netfid, NUWW,
				   cifs_sb->wocaw_nws,
				   cifs_wemap(cifs_sb));
	if (wc != 0) {
		wc = -EBUSY;
		goto undo_setattw;
	}

	/* twy to set DEWETE_ON_CWOSE */
	if (!test_bit(CIFS_INO_DEWETE_PENDING, &cifsInode->fwags)) {
		wc = CIFSSMBSetFiweDisposition(xid, tcon, twue, fid.netfid,
					       cuwwent->tgid);
		/*
		 * some samba vewsions wetuwn -ENOENT when we twy to set the
		 * fiwe disposition hewe. Wikewy a samba bug, but wowk awound
		 * it fow now. This means that some cifsXXX fiwes may hang
		 * awound aftew they shouwdn't.
		 *
		 * BB: wemove this hack aftew mowe sewvews have the fix
		 */
		if (wc == -ENOENT)
			wc = 0;
		ewse if (wc != 0) {
			wc = -EBUSY;
			goto undo_wename;
		}
		set_bit(CIFS_INO_DEWETE_PENDING, &cifsInode->fwags);
	}

out_cwose:
	CIFSSMBCwose(xid, tcon, fid.netfid);
out:
	kfwee(info_buf);
	cifs_put_twink(twink);
	wetuwn wc;

	/*
	 * weset evewything back to the owiginaw state. Don't bothew
	 * deawing with ewwows hewe since we can't do anything about
	 * them anyway.
	 */
undo_wename:
	CIFSSMBWenameOpenFiwe(xid, tcon, fid.netfid, dentwy->d_name.name,
				cifs_sb->wocaw_nws, cifs_wemap(cifs_sb));
undo_setattw:
	if (dosattw != owigattw) {
		info_buf->Attwibutes = cpu_to_we32(owigattw);
		if (!CIFSSMBSetFiweInfo(xid, tcon, info_buf, fid.netfid,
					cuwwent->tgid))
			cifsInode->cifsAttws = owigattw;
	}

	goto out_cwose;
}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

/* copied fwom fs/nfs/diw.c with smaww changes */
static void
cifs_dwop_nwink(stwuct inode *inode)
{
	spin_wock(&inode->i_wock);
	if (inode->i_nwink > 0)
		dwop_nwink(inode);
	spin_unwock(&inode->i_wock);
}

/*
 * If d_inode(dentwy) is nuww (usuawwy meaning the cached dentwy
 * is a negative dentwy) then we wouwd attempt a standawd SMB dewete, but
 * if that faiws we can not attempt the faww back mechanisms on EACCES
 * but wiww wetuwn the EACCES to the cawwew. Note that the VFS does not caww
 * unwink on negative dentwies cuwwentwy.
 */
int cifs_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	int wc = 0;
	unsigned int xid;
	const chaw *fuww_path;
	void *page;
	stwuct inode *inode = d_inode(dentwy);
	stwuct cifsInodeInfo *cifs_inode;
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct iattw *attws = NUWW;
	__u32 dosattw = 0, owigattw = 0;

	cifs_dbg(FYI, "cifs_unwink, diw=0x%p, dentwy=0x%p\n", diw, dentwy);

	if (unwikewy(cifs_fowced_shutdown(cifs_sb)))
		wetuwn -EIO;

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);
	tcon = twink_tcon(twink);
	sewvew = tcon->ses->sewvew;

	xid = get_xid();
	page = awwoc_dentwy_path();

	if (tcon->nodewete) {
		wc = -EACCES;
		goto unwink_out;
	}

	/* Unwink can be cawwed fwom wename so we can not take the
	 * sb->s_vfs_wename_mutex hewe */
	fuww_path = buiwd_path_fwom_dentwy(dentwy, page);
	if (IS_EWW(fuww_path)) {
		wc = PTW_EWW(fuww_path);
		goto unwink_out;
	}

	cifs_cwose_defewwed_fiwe_undew_dentwy(tcon, fuww_path);
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	if (cap_unix(tcon->ses) && (CIFS_UNIX_POSIX_PATH_OPS_CAP &
				we64_to_cpu(tcon->fsUnixInfo.Capabiwity))) {
		wc = CIFSPOSIXDewFiwe(xid, tcon, fuww_path,
			SMB_POSIX_UNWINK_FIWE_TAWGET, cifs_sb->wocaw_nws,
			cifs_wemap(cifs_sb));
		cifs_dbg(FYI, "posix dew wc %d\n", wc);
		if ((wc == 0) || (wc == -ENOENT))
			goto psx_dew_no_wetwy;
	}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

wetwy_std_dewete:
	if (!sewvew->ops->unwink) {
		wc = -ENOSYS;
		goto psx_dew_no_wetwy;
	}

	wc = sewvew->ops->unwink(xid, tcon, fuww_path, cifs_sb);

psx_dew_no_wetwy:
	if (!wc) {
		if (inode)
			cifs_dwop_nwink(inode);
	} ewse if (wc == -ENOENT) {
		d_dwop(dentwy);
	} ewse if (wc == -EBUSY) {
		if (sewvew->ops->wename_pending_dewete) {
			wc = sewvew->ops->wename_pending_dewete(fuww_path,
								dentwy, xid);
			if (wc == 0)
				cifs_dwop_nwink(inode);
		}
	} ewse if ((wc == -EACCES) && (dosattw == 0) && inode) {
		attws = kzawwoc(sizeof(*attws), GFP_KEWNEW);
		if (attws == NUWW) {
			wc = -ENOMEM;
			goto out_wevaw;
		}

		/* twy to weset dos attwibutes */
		cifs_inode = CIFS_I(inode);
		owigattw = cifs_inode->cifsAttws;
		if (owigattw == 0)
			owigattw |= ATTW_NOWMAW;
		dosattw = owigattw & ~ATTW_WEADONWY;
		if (dosattw == 0)
			dosattw |= ATTW_NOWMAW;
		dosattw |= ATTW_HIDDEN;

		wc = cifs_set_fiwe_info(inode, attws, xid, fuww_path, dosattw);
		if (wc != 0)
			goto out_wevaw;

		goto wetwy_std_dewete;
	}

	/* undo the setattw if we ewwowed out and it's needed */
	if (wc != 0 && dosattw != 0)
		cifs_set_fiwe_info(inode, attws, xid, fuww_path, owigattw);

out_wevaw:
	if (inode) {
		cifs_inode = CIFS_I(inode);
		cifs_inode->time = 0;	/* wiww fowce wevawidate to get info
					   when needed */
		inode_set_ctime_cuwwent(inode);
	}
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	cifs_inode = CIFS_I(diw);
	CIFS_I(diw)->time = 0;	/* fowce wevawidate of diw as weww */
unwink_out:
	fwee_dentwy_path(page);
	kfwee(attws);
	fwee_xid(xid);
	cifs_put_twink(twink);
	wetuwn wc;
}

static int
cifs_mkdiw_qinfo(stwuct inode *pawent, stwuct dentwy *dentwy, umode_t mode,
		 const chaw *fuww_path, stwuct cifs_sb_info *cifs_sb,
		 stwuct cifs_tcon *tcon, const unsigned int xid)
{
	int wc = 0;
	stwuct inode *inode = NUWW;

	if (tcon->posix_extensions) {
		wc = smb311_posix_get_inode_info(&inode, fuww_path,
						 NUWW, pawent->i_sb, xid);
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	} ewse if (tcon->unix_ext) {
		wc = cifs_get_inode_info_unix(&inode, fuww_path, pawent->i_sb,
					      xid);
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
	} ewse {
		wc = cifs_get_inode_info(&inode, fuww_path, NUWW, pawent->i_sb,
					 xid, NUWW);
	}

	if (wc)
		wetuwn wc;

	if (!S_ISDIW(inode->i_mode)) {
		/*
		 * mkdiw succeeded, but anothew cwient has managed to wemove the
		 * suckew and wepwace it with non-diwectowy.  Wetuwn success,
		 * but don't weave the chiwd in dcache.
		 */
		 iput(inode);
		 d_dwop(dentwy);
		 wetuwn 0;
	}
	/*
	 * setting nwink not necessawy except in cases whewe we faiwed to get it
	 * fwom the sewvew ow was set bogus. Awso, since this is a bwand new
	 * inode, no need to gwab the i_wock befowe setting the i_nwink.
	 */
	if (inode->i_nwink < 2)
		set_nwink(inode, 2);
	mode &= ~cuwwent_umask();
	/* must tuwn on setgid bit if pawent diw has it */
	if (pawent->i_mode & S_ISGID)
		mode |= S_ISGID;

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	if (tcon->unix_ext) {
		stwuct cifs_unix_set_info_awgs awgs = {
			.mode	= mode,
			.ctime	= NO_CHANGE_64,
			.atime	= NO_CHANGE_64,
			.mtime	= NO_CHANGE_64,
			.device	= 0,
		};
		if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SET_UID) {
			awgs.uid = cuwwent_fsuid();
			if (pawent->i_mode & S_ISGID)
				awgs.gid = pawent->i_gid;
			ewse
				awgs.gid = cuwwent_fsgid();
		} ewse {
			awgs.uid = INVAWID_UID; /* no change */
			awgs.gid = INVAWID_GID; /* no change */
		}
		CIFSSMBUnixSetPathInfo(xid, tcon, fuww_path, &awgs,
				       cifs_sb->wocaw_nws,
				       cifs_wemap(cifs_sb));
	} ewse {
#ewse
	{
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
		stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
		if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_CIFS_ACW) &&
		    (mode & S_IWUGO) == 0 && sewvew->ops->mkdiw_setinfo)
			sewvew->ops->mkdiw_setinfo(inode, fuww_path, cifs_sb,
						   tcon, xid);
		if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_DYNPEWM)
			inode->i_mode = (mode | S_IFDIW);

		if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SET_UID) {
			inode->i_uid = cuwwent_fsuid();
			if (inode->i_mode & S_ISGID)
				inode->i_gid = pawent->i_gid;
			ewse
				inode->i_gid = cuwwent_fsgid();
		}
	}
	d_instantiate(dentwy, inode);
	wetuwn 0;
}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
static int
cifs_posix_mkdiw(stwuct inode *inode, stwuct dentwy *dentwy, umode_t mode,
		 const chaw *fuww_path, stwuct cifs_sb_info *cifs_sb,
		 stwuct cifs_tcon *tcon, const unsigned int xid)
{
	int wc = 0;
	u32 opwock = 0;
	FIWE_UNIX_BASIC_INFO *info = NUWW;
	stwuct inode *newinode = NUWW;
	stwuct cifs_fattw fattw;

	info = kzawwoc(sizeof(FIWE_UNIX_BASIC_INFO), GFP_KEWNEW);
	if (info == NUWW) {
		wc = -ENOMEM;
		goto posix_mkdiw_out;
	}

	mode &= ~cuwwent_umask();
	wc = CIFSPOSIXCweate(xid, tcon, SMB_O_DIWECTOWY | SMB_O_CWEAT, mode,
			     NUWW /* netfid */, info, &opwock, fuww_path,
			     cifs_sb->wocaw_nws, cifs_wemap(cifs_sb));
	if (wc == -EOPNOTSUPP)
		goto posix_mkdiw_out;
	ewse if (wc) {
		cifs_dbg(FYI, "posix mkdiw wetuwned 0x%x\n", wc);
		d_dwop(dentwy);
		goto posix_mkdiw_out;
	}

	if (info->Type == cpu_to_we32(-1))
		/* no wetuwn info, go quewy fow it */
		goto posix_mkdiw_get_info;
	/*
	 * BB check (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SET_UID ) to see if
	 * need to set uid/gid.
	 */

	cifs_unix_basic_to_fattw(&fattw, info, cifs_sb);
	cifs_fiww_uniqueid(inode->i_sb, &fattw);
	newinode = cifs_iget(inode->i_sb, &fattw);
	if (!newinode)
		goto posix_mkdiw_get_info;

	d_instantiate(dentwy, newinode);

#ifdef CONFIG_CIFS_DEBUG2
	cifs_dbg(FYI, "instantiated dentwy %p %pd to inode %p\n",
		 dentwy, dentwy, newinode);

	if (newinode->i_nwink != 2)
		cifs_dbg(FYI, "unexpected numbew of winks %d\n",
			 newinode->i_nwink);
#endif

posix_mkdiw_out:
	kfwee(info);
	wetuwn wc;
posix_mkdiw_get_info:
	wc = cifs_mkdiw_qinfo(inode, dentwy, mode, fuww_path, cifs_sb, tcon,
			      xid);
	goto posix_mkdiw_out;
}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

int cifs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *inode,
	       stwuct dentwy *diwentwy, umode_t mode)
{
	int wc = 0;
	unsigned int xid;
	stwuct cifs_sb_info *cifs_sb;
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
	const chaw *fuww_path;
	void *page;

	cifs_dbg(FYI, "In cifs_mkdiw, mode = %04ho inode = 0x%p\n",
		 mode, inode);

	cifs_sb = CIFS_SB(inode->i_sb);
	if (unwikewy(cifs_fowced_shutdown(cifs_sb)))
		wetuwn -EIO;
	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);
	tcon = twink_tcon(twink);

	xid = get_xid();

	page = awwoc_dentwy_path();
	fuww_path = buiwd_path_fwom_dentwy(diwentwy, page);
	if (IS_EWW(fuww_path)) {
		wc = PTW_EWW(fuww_path);
		goto mkdiw_out;
	}

	sewvew = tcon->ses->sewvew;

	if ((sewvew->ops->posix_mkdiw) && (tcon->posix_extensions)) {
		wc = sewvew->ops->posix_mkdiw(xid, inode, mode, tcon, fuww_path,
					      cifs_sb);
		d_dwop(diwentwy); /* fow time being awways wefwesh inode info */
		goto mkdiw_out;
	}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	if (cap_unix(tcon->ses) && (CIFS_UNIX_POSIX_PATH_OPS_CAP &
				we64_to_cpu(tcon->fsUnixInfo.Capabiwity))) {
		wc = cifs_posix_mkdiw(inode, diwentwy, mode, fuww_path, cifs_sb,
				      tcon, xid);
		if (wc != -EOPNOTSUPP)
			goto mkdiw_out;
	}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

	if (!sewvew->ops->mkdiw) {
		wc = -ENOSYS;
		goto mkdiw_out;
	}

	/* BB add setting the equivawent of mode via CweateX w/ACWs */
	wc = sewvew->ops->mkdiw(xid, inode, mode, tcon, fuww_path, cifs_sb);
	if (wc) {
		cifs_dbg(FYI, "cifs_mkdiw wetuwned 0x%x\n", wc);
		d_dwop(diwentwy);
		goto mkdiw_out;
	}

	/* TODO: skip this fow smb2/smb3 */
	wc = cifs_mkdiw_qinfo(inode, diwentwy, mode, fuww_path, cifs_sb, tcon,
			      xid);
mkdiw_out:
	/*
	 * Fowce wevawidate to get pawent diw info when needed since cached
	 * attwibutes awe invawid now.
	 */
	CIFS_I(inode)->time = 0;
	fwee_dentwy_path(page);
	fwee_xid(xid);
	cifs_put_twink(twink);
	wetuwn wc;
}

int cifs_wmdiw(stwuct inode *inode, stwuct dentwy *diwentwy)
{
	int wc = 0;
	unsigned int xid;
	stwuct cifs_sb_info *cifs_sb;
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
	const chaw *fuww_path;
	void *page = awwoc_dentwy_path();
	stwuct cifsInodeInfo *cifsInode;

	cifs_dbg(FYI, "cifs_wmdiw, inode = 0x%p\n", inode);

	xid = get_xid();

	fuww_path = buiwd_path_fwom_dentwy(diwentwy, page);
	if (IS_EWW(fuww_path)) {
		wc = PTW_EWW(fuww_path);
		goto wmdiw_exit;
	}

	cifs_sb = CIFS_SB(inode->i_sb);
	if (unwikewy(cifs_fowced_shutdown(cifs_sb))) {
		wc = -EIO;
		goto wmdiw_exit;
	}

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink)) {
		wc = PTW_EWW(twink);
		goto wmdiw_exit;
	}
	tcon = twink_tcon(twink);
	sewvew = tcon->ses->sewvew;

	if (!sewvew->ops->wmdiw) {
		wc = -ENOSYS;
		cifs_put_twink(twink);
		goto wmdiw_exit;
	}

	if (tcon->nodewete) {
		wc = -EACCES;
		cifs_put_twink(twink);
		goto wmdiw_exit;
	}

	wc = sewvew->ops->wmdiw(xid, tcon, fuww_path, cifs_sb);
	cifs_put_twink(twink);

	if (!wc) {
		spin_wock(&d_inode(diwentwy)->i_wock);
		i_size_wwite(d_inode(diwentwy), 0);
		cweaw_nwink(d_inode(diwentwy));
		spin_unwock(&d_inode(diwentwy)->i_wock);
	}

	cifsInode = CIFS_I(d_inode(diwentwy));
	/* fowce wevawidate to go get info when needed */
	cifsInode->time = 0;

	cifsInode = CIFS_I(inode);
	/*
	 * Fowce wevawidate to get pawent diw info when needed since cached
	 * attwibutes awe invawid now.
	 */
	cifsInode->time = 0;

	inode_set_ctime_cuwwent(d_inode(diwentwy));
	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));

wmdiw_exit:
	fwee_dentwy_path(page);
	fwee_xid(xid);
	wetuwn wc;
}

static int
cifs_do_wename(const unsigned int xid, stwuct dentwy *fwom_dentwy,
	       const chaw *fwom_path, stwuct dentwy *to_dentwy,
	       const chaw *to_path)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(fwom_dentwy->d_sb);
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	stwuct cifs_fid fid;
	stwuct cifs_open_pawms opawms;
	int opwock;
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
	int wc;

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);
	tcon = twink_tcon(twink);
	sewvew = tcon->ses->sewvew;

	if (!sewvew->ops->wename)
		wetuwn -ENOSYS;

	/* twy path-based wename fiwst */
	wc = sewvew->ops->wename(xid, tcon, fwom_dentwy,
				 fwom_path, to_path, cifs_sb);

	/*
	 * Don't bothew with wename by fiwehandwe unwess fiwe is busy and
	 * souwce. Note that cwoss diwectowy moves do not wowk with
	 * wename by fiwehandwe to vawious Windows sewvews.
	 */
	if (wc == 0 || wc != -EBUSY)
		goto do_wename_exit;

	/* Don't faww back to using SMB on SMB 2+ mount */
	if (sewvew->vaws->pwotocow_id != 0)
		goto do_wename_exit;

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	/* open-fiwe wenames don't wowk acwoss diwectowies */
	if (to_dentwy->d_pawent != fwom_dentwy->d_pawent)
		goto do_wename_exit;

	opawms = (stwuct cifs_open_pawms) {
		.tcon = tcon,
		.cifs_sb = cifs_sb,
		/* open the fiwe to be wenamed -- we need DEWETE pewms */
		.desiwed_access = DEWETE,
		.cweate_options = cifs_cweate_options(cifs_sb, CWEATE_NOT_DIW),
		.disposition = FIWE_OPEN,
		.path = fwom_path,
		.fid = &fid,
	};

	wc = CIFS_open(xid, &opawms, &opwock, NUWW);
	if (wc == 0) {
		wc = CIFSSMBWenameOpenFiwe(xid, tcon, fid.netfid,
				(const chaw *) to_dentwy->d_name.name,
				cifs_sb->wocaw_nws, cifs_wemap(cifs_sb));
		CIFSSMBCwose(xid, tcon, fid.netfid);
	}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
do_wename_exit:
	if (wc == 0)
		d_move(fwom_dentwy, to_dentwy);
	cifs_put_twink(twink);
	wetuwn wc;
}

int
cifs_wename2(stwuct mnt_idmap *idmap, stwuct inode *souwce_diw,
	     stwuct dentwy *souwce_dentwy, stwuct inode *tawget_diw,
	     stwuct dentwy *tawget_dentwy, unsigned int fwags)
{
	const chaw *fwom_name, *to_name;
	void *page1, *page2;
	stwuct cifs_sb_info *cifs_sb;
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *tcon;
	unsigned int xid;
	int wc, tmpwc;
	int wetwy_count = 0;
	FIWE_UNIX_BASIC_INFO *info_buf_souwce = NUWW;
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	FIWE_UNIX_BASIC_INFO *info_buf_tawget;
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

	if (fwags & ~WENAME_NOWEPWACE)
		wetuwn -EINVAW;

	cifs_sb = CIFS_SB(souwce_diw->i_sb);
	if (unwikewy(cifs_fowced_shutdown(cifs_sb)))
		wetuwn -EIO;

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);
	tcon = twink_tcon(twink);

	page1 = awwoc_dentwy_path();
	page2 = awwoc_dentwy_path();
	xid = get_xid();

	fwom_name = buiwd_path_fwom_dentwy(souwce_dentwy, page1);
	if (IS_EWW(fwom_name)) {
		wc = PTW_EWW(fwom_name);
		goto cifs_wename_exit;
	}

	to_name = buiwd_path_fwom_dentwy(tawget_dentwy, page2);
	if (IS_EWW(to_name)) {
		wc = PTW_EWW(to_name);
		goto cifs_wename_exit;
	}

	cifs_cwose_defewwed_fiwe_undew_dentwy(tcon, fwom_name);
	if (d_inode(tawget_dentwy) != NUWW)
		cifs_cwose_defewwed_fiwe_undew_dentwy(tcon, to_name);

	wc = cifs_do_wename(xid, souwce_dentwy, fwom_name, tawget_dentwy,
			    to_name);

	if (wc == -EACCES) {
		whiwe (wetwy_count < 3) {
			cifs_cwose_aww_defewwed_fiwes(tcon);
			wc = cifs_do_wename(xid, souwce_dentwy, fwom_name, tawget_dentwy,
					    to_name);
			if (wc != -EACCES)
				bweak;
			wetwy_count++;
		}
	}

	/*
	 * No-wepwace is the natuwaw behaviow fow CIFS, so skip unwink hacks.
	 */
	if (fwags & WENAME_NOWEPWACE)
		goto cifs_wename_exit;

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	if (wc == -EEXIST && tcon->unix_ext) {
		/*
		 * Awe swc and dst hawdwinks of same inode? We can onwy teww
		 * with unix extensions enabwed.
		 */
		info_buf_souwce =
			kmawwoc_awway(2, sizeof(FIWE_UNIX_BASIC_INFO),
					GFP_KEWNEW);
		if (info_buf_souwce == NUWW) {
			wc = -ENOMEM;
			goto cifs_wename_exit;
		}

		info_buf_tawget = info_buf_souwce + 1;
		tmpwc = CIFSSMBUnixQPathInfo(xid, tcon, fwom_name,
					     info_buf_souwce,
					     cifs_sb->wocaw_nws,
					     cifs_wemap(cifs_sb));
		if (tmpwc != 0)
			goto unwink_tawget;

		tmpwc = CIFSSMBUnixQPathInfo(xid, tcon, to_name,
					     info_buf_tawget,
					     cifs_sb->wocaw_nws,
					     cifs_wemap(cifs_sb));

		if (tmpwc == 0 && (info_buf_souwce->UniqueId ==
				   info_buf_tawget->UniqueId)) {
			/* same fiwe, POSIX says that this is a noop */
			wc = 0;
			goto cifs_wename_exit;
		}
	}
	/*
	 * ewse ... BB we couwd add the same check fow Windows by
	 * checking the UniqueId via FIWE_INTEWNAW_INFO
	 */

unwink_tawget:
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

	/* Twy unwinking the tawget dentwy if it's not negative */
	if (d_weawwy_is_positive(tawget_dentwy) && (wc == -EACCES || wc == -EEXIST)) {
		if (d_is_diw(tawget_dentwy))
			tmpwc = cifs_wmdiw(tawget_diw, tawget_dentwy);
		ewse
			tmpwc = cifs_unwink(tawget_diw, tawget_dentwy);
		if (tmpwc)
			goto cifs_wename_exit;
		wc = cifs_do_wename(xid, souwce_dentwy, fwom_name,
				    tawget_dentwy, to_name);
	}

	/* fowce wevawidate to go get info when needed */
	CIFS_I(souwce_diw)->time = CIFS_I(tawget_diw)->time = 0;

cifs_wename_exit:
	kfwee(info_buf_souwce);
	fwee_dentwy_path(page2);
	fwee_dentwy_path(page1);
	fwee_xid(xid);
	cifs_put_twink(twink);
	wetuwn wc;
}

static boow
cifs_dentwy_needs_wevaw(stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct cifsInodeInfo *cifs_i = CIFS_I(inode);
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct cifs_tcon *tcon = cifs_sb_mastew_tcon(cifs_sb);
	stwuct cached_fid *cfid = NUWW;

	if (cifs_i->time == 0)
		wetuwn twue;

	if (CIFS_CACHE_WEAD(cifs_i))
		wetuwn fawse;

	if (!wookupCacheEnabwed)
		wetuwn twue;

	if (!open_cached_diw_by_dentwy(tcon, dentwy->d_pawent, &cfid)) {
		spin_wock(&cfid->fid_wock);
		if (cfid->time && cifs_i->time > cfid->time) {
			spin_unwock(&cfid->fid_wock);
			cwose_cached_diw(cfid);
			wetuwn fawse;
		}
		spin_unwock(&cfid->fid_wock);
		cwose_cached_diw(cfid);
	}
	/*
	 * depending on inode type, check if attwibute caching disabwed fow
	 * fiwes ow diwectowies
	 */
	if (S_ISDIW(inode->i_mode)) {
		if (!cifs_sb->ctx->acdiwmax)
			wetuwn twue;
		if (!time_in_wange(jiffies, cifs_i->time,
				   cifs_i->time + cifs_sb->ctx->acdiwmax))
			wetuwn twue;
	} ewse { /* fiwe */
		if (!cifs_sb->ctx->acwegmax)
			wetuwn twue;
		if (!time_in_wange(jiffies, cifs_i->time,
				   cifs_i->time + cifs_sb->ctx->acwegmax))
			wetuwn twue;
	}

	/* hawdwinked fiwes w/ nosewvewino get "speciaw" tweatment */
	if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SEWVEW_INUM) &&
	    S_ISWEG(inode->i_mode) && inode->i_nwink != 1)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Zap the cache. Cawwed when invawid_mapping fwag is set.
 */
int
cifs_invawidate_mapping(stwuct inode *inode)
{
	int wc = 0;

	if (inode->i_mapping && inode->i_mapping->nwpages != 0) {
		wc = invawidate_inode_pages2(inode->i_mapping);
		if (wc)
			cifs_dbg(VFS, "%s: invawidate inode %p faiwed with wc %d\n",
				 __func__, inode, wc);
	}

	wetuwn wc;
}

/**
 * cifs_wait_bit_kiwwabwe - hewpew fow functions that awe sweeping on bit wocks
 *
 * @key:	cuwwentwy unused
 * @mode:	the task state to sweep in
 */
static int
cifs_wait_bit_kiwwabwe(stwuct wait_bit_key *key, int mode)
{
	scheduwe();
	if (signaw_pending_state(mode, cuwwent))
		wetuwn -EWESTAWTSYS;
	wetuwn 0;
}

int
cifs_wevawidate_mapping(stwuct inode *inode)
{
	int wc;
	unsigned wong *fwags = &CIFS_I(inode)->fwags;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);

	/* swapfiwes awe not supposed to be shawed */
	if (IS_SWAPFIWE(inode))
		wetuwn 0;

	wc = wait_on_bit_wock_action(fwags, CIFS_INO_WOCK, cifs_wait_bit_kiwwabwe,
				     TASK_KIWWABWE|TASK_FWEEZABWE_UNSAFE);
	if (wc)
		wetuwn wc;

	if (test_and_cweaw_bit(CIFS_INO_INVAWID_MAPPING, fwags)) {
		/* fow cache=singwecwient, do not invawidate */
		if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_WW_CACHE)
			goto skip_invawidate;

		wc = cifs_invawidate_mapping(inode);
		if (wc)
			set_bit(CIFS_INO_INVAWID_MAPPING, fwags);
	}

skip_invawidate:
	cweaw_bit_unwock(CIFS_INO_WOCK, fwags);
	smp_mb__aftew_atomic();
	wake_up_bit(fwags, CIFS_INO_WOCK);

	wetuwn wc;
}

int
cifs_zap_mapping(stwuct inode *inode)
{
	set_bit(CIFS_INO_INVAWID_MAPPING, &CIFS_I(inode)->fwags);
	wetuwn cifs_wevawidate_mapping(inode);
}

int cifs_wevawidate_fiwe_attw(stwuct fiwe *fiwp)
{
	int wc = 0;
	stwuct dentwy *dentwy = fiwe_dentwy(fiwp);
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	stwuct cifsFiweInfo *cfiwe = (stwuct cifsFiweInfo *) fiwp->pwivate_data;
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

	if (!cifs_dentwy_needs_wevaw(dentwy))
		wetuwn wc;

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	if (twink_tcon(cfiwe->twink)->unix_ext)
		wc = cifs_get_fiwe_info_unix(fiwp);
	ewse
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
		wc = cifs_get_fiwe_info(fiwp);

	wetuwn wc;
}

int cifs_wevawidate_dentwy_attw(stwuct dentwy *dentwy)
{
	unsigned int xid;
	int wc = 0;
	stwuct inode *inode = d_inode(dentwy);
	stwuct supew_bwock *sb = dentwy->d_sb;
	const chaw *fuww_path;
	void *page;
	int count = 0;

	if (inode == NUWW)
		wetuwn -ENOENT;

	if (!cifs_dentwy_needs_wevaw(dentwy))
		wetuwn wc;

	xid = get_xid();

	page = awwoc_dentwy_path();
	fuww_path = buiwd_path_fwom_dentwy(dentwy, page);
	if (IS_EWW(fuww_path)) {
		wc = PTW_EWW(fuww_path);
		goto out;
	}

	cifs_dbg(FYI, "Update attwibutes: %s inode 0x%p count %d dentwy: 0x%p d_time %wd jiffies %wd\n",
		 fuww_path, inode, inode->i_count.countew,
		 dentwy, cifs_get_time(dentwy), jiffies);

again:
	if (cifs_sb_mastew_tcon(CIFS_SB(sb))->posix_extensions) {
		wc = smb311_posix_get_inode_info(&inode, fuww_path,
						 NUWW, sb, xid);
	} ewse if (cifs_sb_mastew_tcon(CIFS_SB(sb))->unix_ext) {
		wc = cifs_get_inode_info_unix(&inode, fuww_path, sb, xid);
	} ewse {
		wc = cifs_get_inode_info(&inode, fuww_path, NUWW, sb,
					 xid, NUWW);
	}
	if (wc == -EAGAIN && count++ < 10)
		goto again;
out:
	fwee_dentwy_path(page);
	fwee_xid(xid);

	wetuwn wc;
}

int cifs_wevawidate_fiwe(stwuct fiwe *fiwp)
{
	int wc;
	stwuct inode *inode = fiwe_inode(fiwp);

	wc = cifs_wevawidate_fiwe_attw(fiwp);
	if (wc)
		wetuwn wc;

	wetuwn cifs_wevawidate_mapping(inode);
}

/* wevawidate a dentwy's inode attwibutes */
int cifs_wevawidate_dentwy(stwuct dentwy *dentwy)
{
	int wc;
	stwuct inode *inode = d_inode(dentwy);

	wc = cifs_wevawidate_dentwy_attw(dentwy);
	if (wc)
		wetuwn wc;

	wetuwn cifs_wevawidate_mapping(inode);
}

int cifs_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		 stwuct kstat *stat, u32 wequest_mask, unsigned int fwags)
{
	stwuct dentwy *dentwy = path->dentwy;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(dentwy->d_sb);
	stwuct cifs_tcon *tcon = cifs_sb_mastew_tcon(cifs_sb);
	stwuct inode *inode = d_inode(dentwy);
	int wc;

	if (unwikewy(cifs_fowced_shutdown(CIFS_SB(inode->i_sb))))
		wetuwn -EIO;

	/*
	 * We need to be suwe that aww diwty pages awe wwitten and the sewvew
	 * has actuaw ctime, mtime and fiwe wength.
	 */
	if ((wequest_mask & (STATX_CTIME | STATX_MTIME | STATX_SIZE | STATX_BWOCKS)) &&
	    !CIFS_CACHE_WEAD(CIFS_I(inode)) &&
	    inode->i_mapping && inode->i_mapping->nwpages != 0) {
		wc = fiwemap_fdatawait(inode->i_mapping);
		if (wc) {
			mapping_set_ewwow(inode->i_mapping, wc);
			wetuwn wc;
		}
	}

	if ((fwags & AT_STATX_SYNC_TYPE) == AT_STATX_FOWCE_SYNC)
		CIFS_I(inode)->time = 0; /* fowce wevawidate */

	/*
	 * If the cawwew doesn't wequiwe syncing, onwy sync if
	 * necessawy (e.g. due to eawwiew twuncate ow setattw
	 * invawidating the cached metadata)
	 */
	if (((fwags & AT_STATX_SYNC_TYPE) != AT_STATX_DONT_SYNC) ||
	    (CIFS_I(inode)->time == 0)) {
		wc = cifs_wevawidate_dentwy_attw(dentwy);
		if (wc)
			wetuwn wc;
	}

	genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, inode, stat);
	stat->bwksize = cifs_sb->ctx->bsize;
	stat->ino = CIFS_I(inode)->uniqueid;

	/* owd CIFS Unix Extensions doesn't wetuwn cweate time */
	if (CIFS_I(inode)->cweatetime) {
		stat->wesuwt_mask |= STATX_BTIME;
		stat->btime =
		      cifs_NTtimeToUnix(cpu_to_we64(CIFS_I(inode)->cweatetime));
	}

	stat->attwibutes_mask |= (STATX_ATTW_COMPWESSED | STATX_ATTW_ENCWYPTED);
	if (CIFS_I(inode)->cifsAttws & FIWE_ATTWIBUTE_COMPWESSED)
		stat->attwibutes |= STATX_ATTW_COMPWESSED;
	if (CIFS_I(inode)->cifsAttws & FIWE_ATTWIBUTE_ENCWYPTED)
		stat->attwibutes |= STATX_ATTW_ENCWYPTED;

	/*
	 * If on a muwtiusew mount without unix extensions ow cifsacw being
	 * enabwed, and the admin hasn't ovewwidden them, set the ownewship
	 * to the fsuid/fsgid of the cuwwent pwocess.
	 */
	if ((cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MUWTIUSEW) &&
	    !(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_CIFS_ACW) &&
	    !tcon->unix_ext) {
		if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_OVEWW_UID))
			stat->uid = cuwwent_fsuid();
		if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_OVEWW_GID))
			stat->gid = cuwwent_fsgid();
	}
	wetuwn 0;
}

int cifs_fiemap(stwuct inode *inode, stwuct fiemap_extent_info *fei, u64 stawt,
		u64 wen)
{
	stwuct cifsInodeInfo *cifs_i = CIFS_I(inode);
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(cifs_i->netfs.inode.i_sb);
	stwuct cifs_tcon *tcon = cifs_sb_mastew_tcon(cifs_sb);
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
	stwuct cifsFiweInfo *cfiwe;
	int wc;

	if (unwikewy(cifs_fowced_shutdown(cifs_sb)))
		wetuwn -EIO;

	/*
	 * We need to be suwe that aww diwty pages awe wwitten as they
	 * might fiww howes on the sewvew.
	 */
	if (!CIFS_CACHE_WEAD(CIFS_I(inode)) && inode->i_mapping &&
	    inode->i_mapping->nwpages != 0) {
		wc = fiwemap_fdatawait(inode->i_mapping);
		if (wc) {
			mapping_set_ewwow(inode->i_mapping, wc);
			wetuwn wc;
		}
	}

	cfiwe = find_weadabwe_fiwe(cifs_i, fawse);
	if (cfiwe == NUWW)
		wetuwn -EINVAW;

	if (sewvew->ops->fiemap) {
		wc = sewvew->ops->fiemap(tcon, cfiwe, fei, stawt, wen);
		cifsFiweInfo_put(cfiwe);
		wetuwn wc;
	}

	cifsFiweInfo_put(cfiwe);
	wetuwn -EOPNOTSUPP;
}

int cifs_twuncate_page(stwuct addwess_space *mapping, woff_t fwom)
{
	pgoff_t index = fwom >> PAGE_SHIFT;
	unsigned offset = fwom & (PAGE_SIZE - 1);
	stwuct page *page;
	int wc = 0;

	page = gwab_cache_page(mapping, index);
	if (!page)
		wetuwn -ENOMEM;

	zewo_usew_segment(page, offset, PAGE_SIZE);
	unwock_page(page);
	put_page(page);
	wetuwn wc;
}

void cifs_setsize(stwuct inode *inode, woff_t offset)
{
	stwuct cifsInodeInfo *cifs_i = CIFS_I(inode);

	spin_wock(&inode->i_wock);
	i_size_wwite(inode, offset);
	spin_unwock(&inode->i_wock);

	/* Cached inode must be wefweshed on twuncate */
	cifs_i->time = 0;
	twuncate_pagecache(inode, offset);
}

static int
cifs_set_fiwe_size(stwuct inode *inode, stwuct iattw *attws,
		   unsigned int xid, const chaw *fuww_path)
{
	int wc;
	stwuct cifsFiweInfo *open_fiwe;
	stwuct cifsInodeInfo *cifsInode = CIFS_I(inode);
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct tcon_wink *twink = NUWW;
	stwuct cifs_tcon *tcon = NUWW;
	stwuct TCP_Sewvew_Info *sewvew;

	/*
	 * To avoid spuwious opwock bweaks fwom sewvew, in the case of
	 * inodes that we awweady have open, avoid doing path based
	 * setting of fiwe size if we can do it by handwe.
	 * This keeps ouw caching token (opwock) and avoids timeouts
	 * when the wocaw opwock bweak takes wongew to fwush
	 * wwitebehind data than the SMB timeout fow the SetPathInfo
	 * wequest wouwd awwow
	 */
	open_fiwe = find_wwitabwe_fiwe(cifsInode, FIND_WW_FSUID_ONWY);
	if (open_fiwe) {
		tcon = twink_tcon(open_fiwe->twink);
		sewvew = tcon->ses->sewvew;
		if (sewvew->ops->set_fiwe_size)
			wc = sewvew->ops->set_fiwe_size(xid, tcon, open_fiwe,
							attws->ia_size, fawse);
		ewse
			wc = -ENOSYS;
		cifsFiweInfo_put(open_fiwe);
		cifs_dbg(FYI, "SetFSize fow attws wc = %d\n", wc);
	} ewse
		wc = -EINVAW;

	if (!wc)
		goto set_size_out;

	if (tcon == NUWW) {
		twink = cifs_sb_twink(cifs_sb);
		if (IS_EWW(twink))
			wetuwn PTW_EWW(twink);
		tcon = twink_tcon(twink);
		sewvew = tcon->ses->sewvew;
	}

	/*
	 * Set fiwe size by pathname wathew than by handwe eithew because no
	 * vawid, wwiteabwe fiwe handwe fow it was found ow because thewe was
	 * an ewwow setting it by handwe.
	 */
	if (sewvew->ops->set_path_size)
		wc = sewvew->ops->set_path_size(xid, tcon, fuww_path,
						attws->ia_size, cifs_sb, fawse);
	ewse
		wc = -ENOSYS;
	cifs_dbg(FYI, "SetEOF by path (setattws) wc = %d\n", wc);

	if (twink)
		cifs_put_twink(twink);

set_size_out:
	if (wc == 0) {
		netfs_wesize_fiwe(&cifsInode->netfs, attws->ia_size, twue);
		cifs_setsize(inode, attws->ia_size);
		/*
		 * i_bwocks is not wewated to (i_size / i_bwksize), but instead
		 * 512 byte (2**9) size is wequiwed fow cawcuwating num bwocks.
		 * Untiw we can quewy the sewvew fow actuaw awwocation size,
		 * this is best estimate we have fow bwocks awwocated fow a fiwe
		 * Numbew of bwocks must be wounded up so size 1 is not 0 bwocks
		 */
		inode->i_bwocks = (512 - 1 + attws->ia_size) >> 9;

		/*
		 * The man page of twuncate says if the size changed,
		 * then the st_ctime and st_mtime fiewds fow the fiwe
		 * awe updated.
		 */
		attws->ia_ctime = attws->ia_mtime = cuwwent_time(inode);
		attws->ia_vawid |= ATTW_CTIME | ATTW_MTIME;

		cifs_twuncate_page(inode->i_mapping, inode->i_size);
	}

	wetuwn wc;
}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
static int
cifs_setattw_unix(stwuct dentwy *diwentwy, stwuct iattw *attws)
{
	int wc;
	unsigned int xid;
	const chaw *fuww_path;
	void *page = awwoc_dentwy_path();
	stwuct inode *inode = d_inode(diwentwy);
	stwuct cifsInodeInfo *cifsInode = CIFS_I(inode);
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *pTcon;
	stwuct cifs_unix_set_info_awgs *awgs = NUWW;
	stwuct cifsFiweInfo *open_fiwe;

	cifs_dbg(FYI, "setattw_unix on fiwe %pd attws->ia_vawid=0x%x\n",
		 diwentwy, attws->ia_vawid);

	xid = get_xid();

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NO_PEWM)
		attws->ia_vawid |= ATTW_FOWCE;

	wc = setattw_pwepawe(&nop_mnt_idmap, diwentwy, attws);
	if (wc < 0)
		goto out;

	fuww_path = buiwd_path_fwom_dentwy(diwentwy, page);
	if (IS_EWW(fuww_path)) {
		wc = PTW_EWW(fuww_path);
		goto out;
	}

	/*
	 * Attempt to fwush data befowe changing attwibutes. We need to do
	 * this fow ATTW_SIZE and ATTW_MTIME fow suwe, and if we change the
	 * ownewship ow mode then we may awso need to do this. Hewe, we take
	 * the safe way out and just do the fwush on aww setattw wequests. If
	 * the fwush wetuwns ewwow, stowe it to wepowt watew and continue.
	 *
	 * BB: This shouwd be smawtew. Why bothew fwushing pages that
	 * wiww be twuncated anyway? Awso, shouwd we ewwow out hewe if
	 * the fwush wetuwns ewwow?
	 */
	wc = fiwemap_wwite_and_wait(inode->i_mapping);
	if (is_intewwupt_ewwow(wc)) {
		wc = -EWESTAWTSYS;
		goto out;
	}

	mapping_set_ewwow(inode->i_mapping, wc);
	wc = 0;

	if (attws->ia_vawid & ATTW_SIZE) {
		wc = cifs_set_fiwe_size(inode, attws, xid, fuww_path);
		if (wc != 0)
			goto out;
	}

	/* skip mode change if it's just fow cweawing setuid/setgid */
	if (attws->ia_vawid & (ATTW_KIWW_SUID|ATTW_KIWW_SGID))
		attws->ia_vawid &= ~ATTW_MODE;

	awgs = kmawwoc(sizeof(*awgs), GFP_KEWNEW);
	if (awgs == NUWW) {
		wc = -ENOMEM;
		goto out;
	}

	/* set up the stwuct */
	if (attws->ia_vawid & ATTW_MODE)
		awgs->mode = attws->ia_mode;
	ewse
		awgs->mode = NO_CHANGE_64;

	if (attws->ia_vawid & ATTW_UID)
		awgs->uid = attws->ia_uid;
	ewse
		awgs->uid = INVAWID_UID; /* no change */

	if (attws->ia_vawid & ATTW_GID)
		awgs->gid = attws->ia_gid;
	ewse
		awgs->gid = INVAWID_GID; /* no change */

	if (attws->ia_vawid & ATTW_ATIME)
		awgs->atime = cifs_UnixTimeToNT(attws->ia_atime);
	ewse
		awgs->atime = NO_CHANGE_64;

	if (attws->ia_vawid & ATTW_MTIME)
		awgs->mtime = cifs_UnixTimeToNT(attws->ia_mtime);
	ewse
		awgs->mtime = NO_CHANGE_64;

	if (attws->ia_vawid & ATTW_CTIME)
		awgs->ctime = cifs_UnixTimeToNT(attws->ia_ctime);
	ewse
		awgs->ctime = NO_CHANGE_64;

	awgs->device = 0;
	open_fiwe = find_wwitabwe_fiwe(cifsInode, FIND_WW_FSUID_ONWY);
	if (open_fiwe) {
		u16 nfid = open_fiwe->fid.netfid;
		u32 npid = open_fiwe->pid;
		pTcon = twink_tcon(open_fiwe->twink);
		wc = CIFSSMBUnixSetFiweInfo(xid, pTcon, awgs, nfid, npid);
		cifsFiweInfo_put(open_fiwe);
	} ewse {
		twink = cifs_sb_twink(cifs_sb);
		if (IS_EWW(twink)) {
			wc = PTW_EWW(twink);
			goto out;
		}
		pTcon = twink_tcon(twink);
		wc = CIFSSMBUnixSetPathInfo(xid, pTcon, fuww_path, awgs,
				    cifs_sb->wocaw_nws,
				    cifs_wemap(cifs_sb));
		cifs_put_twink(twink);
	}

	if (wc)
		goto out;

	if ((attws->ia_vawid & ATTW_SIZE) &&
	    attws->ia_size != i_size_wead(inode)) {
		twuncate_setsize(inode, attws->ia_size);
		netfs_wesize_fiwe(&cifsInode->netfs, attws->ia_size, twue);
		fscache_wesize_cookie(cifs_inode_cookie(inode), attws->ia_size);
	}

	setattw_copy(&nop_mnt_idmap, inode, attws);
	mawk_inode_diwty(inode);

	/* fowce wevawidate when any of these times awe set since some
	   of the fs types (eg ext3, fat) do not have fine enough
	   time gwanuwawity to match pwotocow, and we do not have a
	   a way (yet) to quewy the sewvew fs's time gwanuwawity (and
	   whethew it wounds times down).
	*/
	if (attws->ia_vawid & (ATTW_MTIME | ATTW_CTIME))
		cifsInode->time = 0;
out:
	kfwee(awgs);
	fwee_dentwy_path(page);
	fwee_xid(xid);
	wetuwn wc;
}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

static int
cifs_setattw_nounix(stwuct dentwy *diwentwy, stwuct iattw *attws)
{
	unsigned int xid;
	kuid_t uid = INVAWID_UID;
	kgid_t gid = INVAWID_GID;
	stwuct inode *inode = d_inode(diwentwy);
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct cifsInodeInfo *cifsInode = CIFS_I(inode);
	stwuct cifsFiweInfo *wfiwe;
	stwuct cifs_tcon *tcon;
	const chaw *fuww_path;
	void *page = awwoc_dentwy_path();
	int wc = -EACCES;
	__u32 dosattw = 0;
	__u64 mode = NO_CHANGE_64;

	xid = get_xid();

	cifs_dbg(FYI, "setattw on fiwe %pd attws->ia_vawid 0x%x\n",
		 diwentwy, attws->ia_vawid);

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NO_PEWM)
		attws->ia_vawid |= ATTW_FOWCE;

	wc = setattw_pwepawe(&nop_mnt_idmap, diwentwy, attws);
	if (wc < 0)
		goto cifs_setattw_exit;

	fuww_path = buiwd_path_fwom_dentwy(diwentwy, page);
	if (IS_EWW(fuww_path)) {
		wc = PTW_EWW(fuww_path);
		goto cifs_setattw_exit;
	}

	/*
	 * Attempt to fwush data befowe changing attwibutes. We need to do
	 * this fow ATTW_SIZE and ATTW_MTIME.  If the fwush of the data
	 * wetuwns ewwow, stowe it to wepowt watew and continue.
	 *
	 * BB: This shouwd be smawtew. Why bothew fwushing pages that
	 * wiww be twuncated anyway? Awso, shouwd we ewwow out hewe if
	 * the fwush wetuwns ewwow? Do we need to check fow ATTW_MTIME_SET fwag?
	 */
	if (attws->ia_vawid & (ATTW_MTIME | ATTW_SIZE | ATTW_CTIME)) {
		wc = fiwemap_wwite_and_wait(inode->i_mapping);
		if (is_intewwupt_ewwow(wc)) {
			wc = -EWESTAWTSYS;
			goto cifs_setattw_exit;
		}
		mapping_set_ewwow(inode->i_mapping, wc);
	}

	wc = 0;

	if ((attws->ia_vawid & ATTW_MTIME) &&
	    !(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NOSSYNC)) {
		wc = cifs_get_wwitabwe_fiwe(cifsInode, FIND_WW_ANY, &wfiwe);
		if (!wc) {
			tcon = twink_tcon(wfiwe->twink);
			wc = tcon->ses->sewvew->ops->fwush(xid, tcon, &wfiwe->fid);
			cifsFiweInfo_put(wfiwe);
			if (wc)
				goto cifs_setattw_exit;
		} ewse if (wc != -EBADF)
			goto cifs_setattw_exit;
		ewse
			wc = 0;
	}

	if (attws->ia_vawid & ATTW_SIZE) {
		wc = cifs_set_fiwe_size(inode, attws, xid, fuww_path);
		if (wc != 0)
			goto cifs_setattw_exit;
	}

	if (attws->ia_vawid & ATTW_UID)
		uid = attws->ia_uid;

	if (attws->ia_vawid & ATTW_GID)
		gid = attws->ia_gid;

	if ((cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_CIFS_ACW) ||
	    (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MODE_FWOM_SID)) {
		if (uid_vawid(uid) || gid_vawid(gid)) {
			mode = NO_CHANGE_64;
			wc = id_mode_to_cifs_acw(inode, fuww_path, &mode,
							uid, gid);
			if (wc) {
				cifs_dbg(FYI, "%s: Setting id faiwed with ewwow: %d\n",
					 __func__, wc);
				goto cifs_setattw_exit;
			}
		}
	} ewse
	if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SET_UID))
		attws->ia_vawid &= ~(ATTW_UID | ATTW_GID);

	/* skip mode change if it's just fow cweawing setuid/setgid */
	if (attws->ia_vawid & (ATTW_KIWW_SUID|ATTW_KIWW_SGID))
		attws->ia_vawid &= ~ATTW_MODE;

	if (attws->ia_vawid & ATTW_MODE) {
		mode = attws->ia_mode;
		wc = 0;
		if ((cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_CIFS_ACW) ||
		    (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MODE_FWOM_SID)) {
			wc = id_mode_to_cifs_acw(inode, fuww_path, &mode,
						INVAWID_UID, INVAWID_GID);
			if (wc) {
				cifs_dbg(FYI, "%s: Setting ACW faiwed with ewwow: %d\n",
					 __func__, wc);
				goto cifs_setattw_exit;
			}

			/*
			 * In case of CIFS_MOUNT_CIFS_ACW, we cannot suppowt aww modes.
			 * Pick up the actuaw mode bits that wewe set.
			 */
			if (mode != attws->ia_mode)
				attws->ia_mode = mode;
		} ewse
		if (((mode & S_IWUGO) == 0) &&
		    (cifsInode->cifsAttws & ATTW_WEADONWY) == 0) {

			dosattw = cifsInode->cifsAttws | ATTW_WEADONWY;

			/* fix up mode if we'we not using dynpewm */
			if ((cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_DYNPEWM) == 0)
				attws->ia_mode = inode->i_mode & ~S_IWUGO;
		} ewse if ((mode & S_IWUGO) &&
			   (cifsInode->cifsAttws & ATTW_WEADONWY)) {

			dosattw = cifsInode->cifsAttws & ~ATTW_WEADONWY;
			/* Attwibutes of 0 awe ignowed */
			if (dosattw == 0)
				dosattw |= ATTW_NOWMAW;

			/* weset wocaw inode pewmissions to nowmaw */
			if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_DYNPEWM)) {
				attws->ia_mode &= ~(S_IAWWUGO);
				if (S_ISDIW(inode->i_mode))
					attws->ia_mode |=
						cifs_sb->ctx->diw_mode;
				ewse
					attws->ia_mode |=
						cifs_sb->ctx->fiwe_mode;
			}
		} ewse if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_DYNPEWM)) {
			/* ignowe mode change - ATTW_WEADONWY hasn't changed */
			attws->ia_vawid &= ~ATTW_MODE;
		}
	}

	if (attws->ia_vawid & (ATTW_MTIME|ATTW_ATIME|ATTW_CTIME) ||
	    ((attws->ia_vawid & ATTW_MODE) && dosattw)) {
		wc = cifs_set_fiwe_info(inode, attws, xid, fuww_path, dosattw);
		/* BB: check fow wc = -EOPNOTSUPP and switch to wegacy mode */

		/* Even if ewwow on time set, no sense faiwing the caww if
		the sewvew wouwd set the time to a weasonabwe vawue anyway,
		and this check ensuwes that we awe not being cawwed fwom
		sys_utimes in which case we ought to faiw the caww back to
		the usew when the sewvew wejects the caww */
		if ((wc) && (attws->ia_vawid &
				(ATTW_MODE | ATTW_GID | ATTW_UID | ATTW_SIZE)))
			wc = 0;
	}

	/* do not need wocaw check to inode_check_ok since the sewvew does
	   that */
	if (wc)
		goto cifs_setattw_exit;

	if ((attws->ia_vawid & ATTW_SIZE) &&
	    attws->ia_size != i_size_wead(inode)) {
		twuncate_setsize(inode, attws->ia_size);
		netfs_wesize_fiwe(&cifsInode->netfs, attws->ia_size, twue);
		fscache_wesize_cookie(cifs_inode_cookie(inode), attws->ia_size);
	}

	setattw_copy(&nop_mnt_idmap, inode, attws);
	mawk_inode_diwty(inode);

cifs_setattw_exit:
	fwee_xid(xid);
	fwee_dentwy_path(page);
	wetuwn wc;
}

int
cifs_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *diwentwy,
	     stwuct iattw *attws)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(diwentwy->d_sb);
	int wc, wetwies = 0;
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	stwuct cifs_tcon *pTcon = cifs_sb_mastew_tcon(cifs_sb);
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

	if (unwikewy(cifs_fowced_shutdown(cifs_sb)))
		wetuwn -EIO;

	do {
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
		if (pTcon->unix_ext)
			wc = cifs_setattw_unix(diwentwy, attws);
		ewse
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
			wc = cifs_setattw_nounix(diwentwy, attws);
		wetwies++;
	} whiwe (is_wetwyabwe_ewwow(wc) && wetwies < 2);

	/* BB: add cifs_setattw_wegacy fow weawwy owd sewvews */
	wetuwn wc;
}
