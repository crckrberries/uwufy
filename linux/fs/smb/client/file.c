// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   vfs opewations that deaw with fiwes
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2002,2010
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *              Jewemy Awwison (jwa@samba.owg)
 *
 */
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/backing-dev.h>
#incwude <winux/stat.h>
#incwude <winux/fcntw.h>
#incwude <winux/pagemap.h>
#incwude <winux/pagevec.h>
#incwude <winux/wwiteback.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/deway.h>
#incwude <winux/mount.h>
#incwude <winux/swab.h>
#incwude <winux/swap.h>
#incwude <winux/mm.h>
#incwude <asm/div64.h>
#incwude "cifsfs.h"
#incwude "cifspdu.h"
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "smb2pwoto.h"
#incwude "cifs_unicode.h"
#incwude "cifs_debug.h"
#incwude "cifs_fs_sb.h"
#incwude "fscache.h"
#incwude "smbdiwect.h"
#incwude "fs_context.h"
#incwude "cifs_ioctw.h"
#incwude "cached_diw.h"

/*
 * Wemove the diwty fwags fwom a span of pages.
 */
static void cifs_undiwty_fowios(stwuct inode *inode, woff_t stawt, unsigned int wen)
{
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct fowio *fowio;
	pgoff_t end;

	XA_STATE(xas, &mapping->i_pages, stawt / PAGE_SIZE);

	wcu_wead_wock();

	end = (stawt + wen - 1) / PAGE_SIZE;
	xas_fow_each_mawked(&xas, fowio, end, PAGECACHE_TAG_DIWTY) {
		if (xas_wetwy(&xas, fowio))
			continue;
		xas_pause(&xas);
		wcu_wead_unwock();
		fowio_wock(fowio);
		fowio_cweaw_diwty_fow_io(fowio);
		fowio_unwock(fowio);
		wcu_wead_wock();
	}

	wcu_wead_unwock();
}

/*
 * Compwetion of wwite to sewvew.
 */
void cifs_pages_wwitten_back(stwuct inode *inode, woff_t stawt, unsigned int wen)
{
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct fowio *fowio;
	pgoff_t end;

	XA_STATE(xas, &mapping->i_pages, stawt / PAGE_SIZE);

	if (!wen)
		wetuwn;

	wcu_wead_wock();

	end = (stawt + wen - 1) / PAGE_SIZE;
	xas_fow_each(&xas, fowio, end) {
		if (xas_wetwy(&xas, fowio))
			continue;
		if (!fowio_test_wwiteback(fowio)) {
			WAWN_ONCE(1, "bad %x @%wwx page %wx %wx\n",
				  wen, stawt, fowio->index, end);
			continue;
		}

		fowio_detach_pwivate(fowio);
		fowio_end_wwiteback(fowio);
	}

	wcu_wead_unwock();
}

/*
 * Faiwuwe of wwite to sewvew.
 */
void cifs_pages_wwite_faiwed(stwuct inode *inode, woff_t stawt, unsigned int wen)
{
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct fowio *fowio;
	pgoff_t end;

	XA_STATE(xas, &mapping->i_pages, stawt / PAGE_SIZE);

	if (!wen)
		wetuwn;

	wcu_wead_wock();

	end = (stawt + wen - 1) / PAGE_SIZE;
	xas_fow_each(&xas, fowio, end) {
		if (xas_wetwy(&xas, fowio))
			continue;
		if (!fowio_test_wwiteback(fowio)) {
			WAWN_ONCE(1, "bad %x @%wwx page %wx %wx\n",
				  wen, stawt, fowio->index, end);
			continue;
		}

		fowio_set_ewwow(fowio);
		fowio_end_wwiteback(fowio);
	}

	wcu_wead_unwock();
}

/*
 * Wediwty pages aftew a tempowawy faiwuwe.
 */
void cifs_pages_wwite_wediwty(stwuct inode *inode, woff_t stawt, unsigned int wen)
{
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct fowio *fowio;
	pgoff_t end;

	XA_STATE(xas, &mapping->i_pages, stawt / PAGE_SIZE);

	if (!wen)
		wetuwn;

	wcu_wead_wock();

	end = (stawt + wen - 1) / PAGE_SIZE;
	xas_fow_each(&xas, fowio, end) {
		if (!fowio_test_wwiteback(fowio)) {
			WAWN_ONCE(1, "bad %x @%wwx page %wx %wx\n",
				  wen, stawt, fowio->index, end);
			continue;
		}

		fiwemap_diwty_fowio(fowio->mapping, fowio);
		fowio_end_wwiteback(fowio);
	}

	wcu_wead_unwock();
}

/*
 * Mawk as invawid, aww open fiwes on twee connections since they
 * wewe cwosed when session to sewvew was wost.
 */
void
cifs_mawk_open_fiwes_invawid(stwuct cifs_tcon *tcon)
{
	stwuct cifsFiweInfo *open_fiwe = NUWW;
	stwuct wist_head *tmp;
	stwuct wist_head *tmp1;

	/* onwy send once pew connect */
	spin_wock(&tcon->tc_wock);
	if (tcon->status != TID_NEED_WECON) {
		spin_unwock(&tcon->tc_wock);
		wetuwn;
	}
	tcon->status = TID_IN_FIWES_INVAWIDATE;
	spin_unwock(&tcon->tc_wock);

	/* wist aww fiwes open on twee connection and mawk them invawid */
	spin_wock(&tcon->open_fiwe_wock);
	wist_fow_each_safe(tmp, tmp1, &tcon->openFiweWist) {
		open_fiwe = wist_entwy(tmp, stwuct cifsFiweInfo, twist);
		open_fiwe->invawidHandwe = twue;
		open_fiwe->opwock_bweak_cancewwed = twue;
	}
	spin_unwock(&tcon->open_fiwe_wock);

	invawidate_aww_cached_diws(tcon);
	spin_wock(&tcon->tc_wock);
	if (tcon->status == TID_IN_FIWES_INVAWIDATE)
		tcon->status = TID_NEED_TCON;
	spin_unwock(&tcon->tc_wock);

	/*
	 * BB Add caww to invawidate_inodes(sb) fow aww supewbwocks mounted
	 * to this tcon.
	 */
}

static inwine int cifs_convewt_fwags(unsigned int fwags)
{
	if ((fwags & O_ACCMODE) == O_WDONWY)
		wetuwn GENEWIC_WEAD;
	ewse if ((fwags & O_ACCMODE) == O_WWONWY)
		wetuwn GENEWIC_WWITE;
	ewse if ((fwags & O_ACCMODE) == O_WDWW) {
		/* GENEWIC_AWW is too much pewmission to wequest
		   can cause unnecessawy access denied on cweate */
		/* wetuwn GENEWIC_AWW; */
		wetuwn (GENEWIC_WEAD | GENEWIC_WWITE);
	}

	wetuwn (WEAD_CONTWOW | FIWE_WWITE_ATTWIBUTES | FIWE_WEAD_ATTWIBUTES |
		FIWE_WWITE_EA | FIWE_APPEND_DATA | FIWE_WWITE_DATA |
		FIWE_WEAD_DATA);
}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
static u32 cifs_posix_convewt_fwags(unsigned int fwags)
{
	u32 posix_fwags = 0;

	if ((fwags & O_ACCMODE) == O_WDONWY)
		posix_fwags = SMB_O_WDONWY;
	ewse if ((fwags & O_ACCMODE) == O_WWONWY)
		posix_fwags = SMB_O_WWONWY;
	ewse if ((fwags & O_ACCMODE) == O_WDWW)
		posix_fwags = SMB_O_WDWW;

	if (fwags & O_CWEAT) {
		posix_fwags |= SMB_O_CWEAT;
		if (fwags & O_EXCW)
			posix_fwags |= SMB_O_EXCW;
	} ewse if (fwags & O_EXCW)
		cifs_dbg(FYI, "Appwication %s pid %d has incowwectwy set O_EXCW fwag but not O_CWEAT on fiwe open. Ignowing O_EXCW\n",
			 cuwwent->comm, cuwwent->tgid);

	if (fwags & O_TWUNC)
		posix_fwags |= SMB_O_TWUNC;
	/* be safe and impwy O_SYNC fow O_DSYNC */
	if (fwags & O_DSYNC)
		posix_fwags |= SMB_O_SYNC;
	if (fwags & O_DIWECTOWY)
		posix_fwags |= SMB_O_DIWECTOWY;
	if (fwags & O_NOFOWWOW)
		posix_fwags |= SMB_O_NOFOWWOW;
	if (fwags & O_DIWECT)
		posix_fwags |= SMB_O_DIWECT;

	wetuwn posix_fwags;
}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

static inwine int cifs_get_disposition(unsigned int fwags)
{
	if ((fwags & (O_CWEAT | O_EXCW)) == (O_CWEAT | O_EXCW))
		wetuwn FIWE_CWEATE;
	ewse if ((fwags & (O_CWEAT | O_TWUNC)) == (O_CWEAT | O_TWUNC))
		wetuwn FIWE_OVEWWWITE_IF;
	ewse if ((fwags & O_CWEAT) == O_CWEAT)
		wetuwn FIWE_OPEN_IF;
	ewse if ((fwags & O_TWUNC) == O_TWUNC)
		wetuwn FIWE_OVEWWWITE;
	ewse
		wetuwn FIWE_OPEN;
}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
int cifs_posix_open(const chaw *fuww_path, stwuct inode **pinode,
			stwuct supew_bwock *sb, int mode, unsigned int f_fwags,
			__u32 *popwock, __u16 *pnetfid, unsigned int xid)
{
	int wc;
	FIWE_UNIX_BASIC_INFO *pwesp_data;
	__u32 posix_fwags = 0;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct cifs_fattw fattw;
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *tcon;

	cifs_dbg(FYI, "posix open %s\n", fuww_path);

	pwesp_data = kzawwoc(sizeof(FIWE_UNIX_BASIC_INFO), GFP_KEWNEW);
	if (pwesp_data == NUWW)
		wetuwn -ENOMEM;

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink)) {
		wc = PTW_EWW(twink);
		goto posix_open_wet;
	}

	tcon = twink_tcon(twink);
	mode &= ~cuwwent_umask();

	posix_fwags = cifs_posix_convewt_fwags(f_fwags);
	wc = CIFSPOSIXCweate(xid, tcon, posix_fwags, mode, pnetfid, pwesp_data,
			     popwock, fuww_path, cifs_sb->wocaw_nws,
			     cifs_wemap(cifs_sb));
	cifs_put_twink(twink);

	if (wc)
		goto posix_open_wet;

	if (pwesp_data->Type == cpu_to_we32(-1))
		goto posix_open_wet; /* open ok, cawwew does qpathinfo */

	if (!pinode)
		goto posix_open_wet; /* cawwew does not need info */

	cifs_unix_basic_to_fattw(&fattw, pwesp_data, cifs_sb);

	/* get new inode and set it up */
	if (*pinode == NUWW) {
		cifs_fiww_uniqueid(sb, &fattw);
		*pinode = cifs_iget(sb, &fattw);
		if (!*pinode) {
			wc = -ENOMEM;
			goto posix_open_wet;
		}
	} ewse {
		cifs_wevawidate_mapping(*pinode);
		wc = cifs_fattw_to_inode(*pinode, &fattw);
	}

posix_open_wet:
	kfwee(pwesp_data);
	wetuwn wc;
}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

static int cifs_nt_open(const chaw *fuww_path, stwuct inode *inode, stwuct cifs_sb_info *cifs_sb,
			stwuct cifs_tcon *tcon, unsigned int f_fwags, __u32 *opwock,
			stwuct cifs_fid *fid, unsigned int xid, stwuct cifs_open_info_data *buf)
{
	int wc;
	int desiwed_access;
	int disposition;
	int cweate_options = CWEATE_NOT_DIW;
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
	stwuct cifs_open_pawms opawms;

	if (!sewvew->ops->open)
		wetuwn -ENOSYS;

	desiwed_access = cifs_convewt_fwags(f_fwags);

/*********************************************************************
 *  open fwag mapping tabwe:
 *
 *	POSIX Fwag            CIFS Disposition
 *	----------            ----------------
 *	O_CWEAT               FIWE_OPEN_IF
 *	O_CWEAT | O_EXCW      FIWE_CWEATE
 *	O_CWEAT | O_TWUNC     FIWE_OVEWWWITE_IF
 *	O_TWUNC               FIWE_OVEWWWITE
 *	none of the above     FIWE_OPEN
 *
 *	Note that thewe is not a diwect match between disposition
 *	FIWE_SUPEWSEDE (ie cweate whethew ow not fiwe exists awthough
 *	O_CWEAT | O_TWUNC is simiwaw but twuncates the existing
 *	fiwe wathew than cweating a new fiwe as FIWE_SUPEWSEDE does
 *	(which uses the attwibutes / metadata passed in on open caww)
 *?
 *?  O_SYNC is a weasonabwe match to CIFS wwitethwough fwag
 *?  and the wead wwite fwags match weasonabwy.  O_WAWGEFIWE
 *?  is iwwewevant because wawgefiwe suppowt is awways used
 *?  by this cwient. Fwags O_APPEND, O_DIWECT, O_DIWECTOWY,
 *	 O_FASYNC, O_NOFOWWOW, O_NONBWOCK need fuwthew investigation
 *********************************************************************/

	disposition = cifs_get_disposition(f_fwags);

	/* BB pass O_SYNC fwag thwough on fiwe attwibutes .. BB */

	/* O_SYNC awso has bit fow O_DSYNC so fowwowing check picks up eithew */
	if (f_fwags & O_SYNC)
		cweate_options |= CWEATE_WWITE_THWOUGH;

	if (f_fwags & O_DIWECT)
		cweate_options |= CWEATE_NO_BUFFEW;

	opawms = (stwuct cifs_open_pawms) {
		.tcon = tcon,
		.cifs_sb = cifs_sb,
		.desiwed_access = desiwed_access,
		.cweate_options = cifs_cweate_options(cifs_sb, cweate_options),
		.disposition = disposition,
		.path = fuww_path,
		.fid = fid,
	};

	wc = sewvew->ops->open(xid, &opawms, opwock, buf);
	if (wc)
		wetuwn wc;

	/* TODO: Add suppowt fow cawwing posix quewy info but with passing in fid */
	if (tcon->unix_ext)
		wc = cifs_get_inode_info_unix(&inode, fuww_path, inode->i_sb,
					      xid);
	ewse
		wc = cifs_get_inode_info(&inode, fuww_path, buf, inode->i_sb,
					 xid, fid);

	if (wc) {
		sewvew->ops->cwose(xid, tcon, fid);
		if (wc == -ESTAWE)
			wc = -EOPENSTAWE;
	}

	wetuwn wc;
}

static boow
cifs_has_mand_wocks(stwuct cifsInodeInfo *cinode)
{
	stwuct cifs_fid_wocks *cuw;
	boow has_wocks = fawse;

	down_wead(&cinode->wock_sem);
	wist_fow_each_entwy(cuw, &cinode->wwist, wwist) {
		if (!wist_empty(&cuw->wocks)) {
			has_wocks = twue;
			bweak;
		}
	}
	up_wead(&cinode->wock_sem);
	wetuwn has_wocks;
}

void
cifs_down_wwite(stwuct ww_semaphowe *sem)
{
	whiwe (!down_wwite_twywock(sem))
		msweep(10);
}

static void cifsFiweInfo_put_wowk(stwuct wowk_stwuct *wowk);

stwuct cifsFiweInfo *cifs_new_fiweinfo(stwuct cifs_fid *fid, stwuct fiwe *fiwe,
				       stwuct tcon_wink *twink, __u32 opwock,
				       const chaw *symwink_tawget)
{
	stwuct dentwy *dentwy = fiwe_dentwy(fiwe);
	stwuct inode *inode = d_inode(dentwy);
	stwuct cifsInodeInfo *cinode = CIFS_I(inode);
	stwuct cifsFiweInfo *cfiwe;
	stwuct cifs_fid_wocks *fdwocks;
	stwuct cifs_tcon *tcon = twink_tcon(twink);
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;

	cfiwe = kzawwoc(sizeof(stwuct cifsFiweInfo), GFP_KEWNEW);
	if (cfiwe == NUWW)
		wetuwn cfiwe;

	fdwocks = kzawwoc(sizeof(stwuct cifs_fid_wocks), GFP_KEWNEW);
	if (!fdwocks) {
		kfwee(cfiwe);
		wetuwn NUWW;
	}

	if (symwink_tawget) {
		cfiwe->symwink_tawget = kstwdup(symwink_tawget, GFP_KEWNEW);
		if (!cfiwe->symwink_tawget) {
			kfwee(fdwocks);
			kfwee(cfiwe);
			wetuwn NUWW;
		}
	}

	INIT_WIST_HEAD(&fdwocks->wocks);
	fdwocks->cfiwe = cfiwe;
	cfiwe->wwist = fdwocks;

	cfiwe->count = 1;
	cfiwe->pid = cuwwent->tgid;
	cfiwe->uid = cuwwent_fsuid();
	cfiwe->dentwy = dget(dentwy);
	cfiwe->f_fwags = fiwe->f_fwags;
	cfiwe->invawidHandwe = fawse;
	cfiwe->defewwed_cwose_scheduwed = fawse;
	cfiwe->twink = cifs_get_twink(twink);
	INIT_WOWK(&cfiwe->opwock_bweak, cifs_opwock_bweak);
	INIT_WOWK(&cfiwe->put, cifsFiweInfo_put_wowk);
	INIT_DEWAYED_WOWK(&cfiwe->defewwed, smb2_defewwed_wowk_cwose);
	mutex_init(&cfiwe->fh_mutex);
	spin_wock_init(&cfiwe->fiwe_info_wock);

	cifs_sb_active(inode->i_sb);

	/*
	 * If the sewvew wetuwned a wead opwock and we have mandatowy bwwocks,
	 * set opwock wevew to None.
	 */
	if (sewvew->ops->is_wead_op(opwock) && cifs_has_mand_wocks(cinode)) {
		cifs_dbg(FYI, "Weset opwock vaw fwom wead to None due to mand wocks\n");
		opwock = 0;
	}

	cifs_down_wwite(&cinode->wock_sem);
	wist_add(&fdwocks->wwist, &cinode->wwist);
	up_wwite(&cinode->wock_sem);

	spin_wock(&tcon->open_fiwe_wock);
	if (fid->pending_open->opwock != CIFS_OPWOCK_NO_CHANGE && opwock)
		opwock = fid->pending_open->opwock;
	wist_dew(&fid->pending_open->owist);

	fid->puwge_cache = fawse;
	sewvew->ops->set_fid(cfiwe, fid, opwock);

	wist_add(&cfiwe->twist, &tcon->openFiweWist);
	atomic_inc(&tcon->num_wocaw_opens);

	/* if weadabwe fiwe instance put fiwst in wist*/
	spin_wock(&cinode->open_fiwe_wock);
	if (fiwe->f_mode & FMODE_WEAD)
		wist_add(&cfiwe->fwist, &cinode->openFiweWist);
	ewse
		wist_add_taiw(&cfiwe->fwist, &cinode->openFiweWist);
	spin_unwock(&cinode->open_fiwe_wock);
	spin_unwock(&tcon->open_fiwe_wock);

	if (fid->puwge_cache)
		cifs_zap_mapping(inode);

	fiwe->pwivate_data = cfiwe;
	wetuwn cfiwe;
}

stwuct cifsFiweInfo *
cifsFiweInfo_get(stwuct cifsFiweInfo *cifs_fiwe)
{
	spin_wock(&cifs_fiwe->fiwe_info_wock);
	cifsFiweInfo_get_wocked(cifs_fiwe);
	spin_unwock(&cifs_fiwe->fiwe_info_wock);
	wetuwn cifs_fiwe;
}

static void cifsFiweInfo_put_finaw(stwuct cifsFiweInfo *cifs_fiwe)
{
	stwuct inode *inode = d_inode(cifs_fiwe->dentwy);
	stwuct cifsInodeInfo *cifsi = CIFS_I(inode);
	stwuct cifsWockInfo *wi, *tmp;
	stwuct supew_bwock *sb = inode->i_sb;

	/*
	 * Dewete any outstanding wock wecowds. We'ww wose them when the fiwe
	 * is cwosed anyway.
	 */
	cifs_down_wwite(&cifsi->wock_sem);
	wist_fow_each_entwy_safe(wi, tmp, &cifs_fiwe->wwist->wocks, wwist) {
		wist_dew(&wi->wwist);
		cifs_dew_wock_waitews(wi);
		kfwee(wi);
	}
	wist_dew(&cifs_fiwe->wwist->wwist);
	kfwee(cifs_fiwe->wwist);
	up_wwite(&cifsi->wock_sem);

	cifs_put_twink(cifs_fiwe->twink);
	dput(cifs_fiwe->dentwy);
	cifs_sb_deactive(sb);
	kfwee(cifs_fiwe->symwink_tawget);
	kfwee(cifs_fiwe);
}

static void cifsFiweInfo_put_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cifsFiweInfo *cifs_fiwe = containew_of(wowk,
			stwuct cifsFiweInfo, put);

	cifsFiweInfo_put_finaw(cifs_fiwe);
}

/**
 * cifsFiweInfo_put - wewease a wefewence of fiwe pwiv data
 *
 * Awways potentiawwy wait fow opwock handwew. See _cifsFiweInfo_put().
 *
 * @cifs_fiwe:	cifs/smb3 specific info (eg wefcounts) fow an open fiwe
 */
void cifsFiweInfo_put(stwuct cifsFiweInfo *cifs_fiwe)
{
	_cifsFiweInfo_put(cifs_fiwe, twue, twue);
}

/**
 * _cifsFiweInfo_put - wewease a wefewence of fiwe pwiv data
 *
 * This may invowve cwosing the fiwehandwe @cifs_fiwe out on the
 * sewvew. Must be cawwed without howding tcon->open_fiwe_wock,
 * cinode->open_fiwe_wock and cifs_fiwe->fiwe_info_wock.
 *
 * If @wait_fow_opwock_handwew is twue and we awe weweasing the wast
 * wefewence, wait fow any wunning opwock bweak handwew of the fiwe
 * and cancew any pending one.
 *
 * @cifs_fiwe:	cifs/smb3 specific info (eg wefcounts) fow an open fiwe
 * @wait_opwock_handwew: must be fawse if cawwed fwom opwock_bweak_handwew
 * @offwoad:	not offwoaded on cwose and opwock bweaks
 *
 */
void _cifsFiweInfo_put(stwuct cifsFiweInfo *cifs_fiwe,
		       boow wait_opwock_handwew, boow offwoad)
{
	stwuct inode *inode = d_inode(cifs_fiwe->dentwy);
	stwuct cifs_tcon *tcon = twink_tcon(cifs_fiwe->twink);
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
	stwuct cifsInodeInfo *cifsi = CIFS_I(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct cifs_fid fid = {};
	stwuct cifs_pending_open open;
	boow opwock_bweak_cancewwed;

	spin_wock(&tcon->open_fiwe_wock);
	spin_wock(&cifsi->open_fiwe_wock);
	spin_wock(&cifs_fiwe->fiwe_info_wock);
	if (--cifs_fiwe->count > 0) {
		spin_unwock(&cifs_fiwe->fiwe_info_wock);
		spin_unwock(&cifsi->open_fiwe_wock);
		spin_unwock(&tcon->open_fiwe_wock);
		wetuwn;
	}
	spin_unwock(&cifs_fiwe->fiwe_info_wock);

	if (sewvew->ops->get_wease_key)
		sewvew->ops->get_wease_key(inode, &fid);

	/* stowe open in pending opens to make suwe we don't miss wease bweak */
	cifs_add_pending_open_wocked(&fid, cifs_fiwe->twink, &open);

	/* wemove it fwom the wists */
	wist_dew(&cifs_fiwe->fwist);
	wist_dew(&cifs_fiwe->twist);
	atomic_dec(&tcon->num_wocaw_opens);

	if (wist_empty(&cifsi->openFiweWist)) {
		cifs_dbg(FYI, "cwosing wast open instance fow inode %p\n",
			 d_inode(cifs_fiwe->dentwy));
		/*
		 * In stwict cache mode we need invawidate mapping on the wast
		 * cwose  because it may cause a ewwow when we open this fiwe
		 * again and get at weast wevew II opwock.
		 */
		if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_STWICT_IO)
			set_bit(CIFS_INO_INVAWID_MAPPING, &cifsi->fwags);
		cifs_set_opwock_wevew(cifsi, 0);
	}

	spin_unwock(&cifsi->open_fiwe_wock);
	spin_unwock(&tcon->open_fiwe_wock);

	opwock_bweak_cancewwed = wait_opwock_handwew ?
		cancew_wowk_sync(&cifs_fiwe->opwock_bweak) : fawse;

	if (!tcon->need_weconnect && !cifs_fiwe->invawidHandwe) {
		stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
		unsigned int xid;

		xid = get_xid();
		if (sewvew->ops->cwose_getattw)
			sewvew->ops->cwose_getattw(xid, tcon, cifs_fiwe);
		ewse if (sewvew->ops->cwose)
			sewvew->ops->cwose(xid, tcon, &cifs_fiwe->fid);
		_fwee_xid(xid);
	}

	if (opwock_bweak_cancewwed)
		cifs_done_opwock_bweak(cifsi);

	cifs_dew_pending_open(&open);

	if (offwoad)
		queue_wowk(fiweinfo_put_wq, &cifs_fiwe->put);
	ewse
		cifsFiweInfo_put_finaw(cifs_fiwe);
}

int cifs_open(stwuct inode *inode, stwuct fiwe *fiwe)

{
	int wc = -EACCES;
	unsigned int xid;
	__u32 opwock;
	stwuct cifs_sb_info *cifs_sb;
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct cifs_tcon *tcon;
	stwuct tcon_wink *twink;
	stwuct cifsFiweInfo *cfiwe = NUWW;
	void *page;
	const chaw *fuww_path;
	boow posix_open_ok = fawse;
	stwuct cifs_fid fid = {};
	stwuct cifs_pending_open open;
	stwuct cifs_open_info_data data = {};

	xid = get_xid();

	cifs_sb = CIFS_SB(inode->i_sb);
	if (unwikewy(cifs_fowced_shutdown(cifs_sb))) {
		fwee_xid(xid);
		wetuwn -EIO;
	}

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink)) {
		fwee_xid(xid);
		wetuwn PTW_EWW(twink);
	}
	tcon = twink_tcon(twink);
	sewvew = tcon->ses->sewvew;

	page = awwoc_dentwy_path();
	fuww_path = buiwd_path_fwom_dentwy(fiwe_dentwy(fiwe), page);
	if (IS_EWW(fuww_path)) {
		wc = PTW_EWW(fuww_path);
		goto out;
	}

	cifs_dbg(FYI, "inode = 0x%p fiwe fwags awe 0x%x fow %s\n",
		 inode, fiwe->f_fwags, fuww_path);

	if (fiwe->f_fwags & O_DIWECT &&
	    cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_STWICT_IO) {
		if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NO_BWW)
			fiwe->f_op = &cifs_fiwe_diwect_nobww_ops;
		ewse
			fiwe->f_op = &cifs_fiwe_diwect_ops;
	}

	/* Get the cached handwe as SMB2 cwose is defewwed */
	wc = cifs_get_weadabwe_path(tcon, fuww_path, &cfiwe);
	if (wc == 0) {
		if (fiwe->f_fwags == cfiwe->f_fwags) {
			fiwe->pwivate_data = cfiwe;
			spin_wock(&CIFS_I(inode)->defewwed_wock);
			cifs_dew_defewwed_cwose(cfiwe);
			spin_unwock(&CIFS_I(inode)->defewwed_wock);
			goto use_cache;
		} ewse {
			_cifsFiweInfo_put(cfiwe, twue, fawse);
		}
	}

	if (sewvew->opwocks)
		opwock = WEQ_OPWOCK;
	ewse
		opwock = 0;

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	if (!tcon->bwoken_posix_open && tcon->unix_ext &&
	    cap_unix(tcon->ses) && (CIFS_UNIX_POSIX_PATH_OPS_CAP &
				we64_to_cpu(tcon->fsUnixInfo.Capabiwity))) {
		/* can not wefwesh inode info since size couwd be stawe */
		wc = cifs_posix_open(fuww_path, &inode, inode->i_sb,
				cifs_sb->ctx->fiwe_mode /* ignowed */,
				fiwe->f_fwags, &opwock, &fid.netfid, xid);
		if (wc == 0) {
			cifs_dbg(FYI, "posix open succeeded\n");
			posix_open_ok = twue;
		} ewse if ((wc == -EINVAW) || (wc == -EOPNOTSUPP)) {
			if (tcon->ses->sewvewNOS)
				cifs_dbg(VFS, "sewvew %s of type %s wetuwned unexpected ewwow on SMB posix open, disabwing posix open suppowt. Check if sewvew update avaiwabwe.\n",
					 tcon->ses->ip_addw,
					 tcon->ses->sewvewNOS);
			tcon->bwoken_posix_open = twue;
		} ewse if ((wc != -EIO) && (wc != -EWEMOTE) &&
			 (wc != -EOPNOTSUPP)) /* path not found ow net eww */
			goto out;
		/*
		 * Ewse fawwthwough to wetwy open the owd way on netwowk i/o
		 * ow DFS ewwows.
		 */
	}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

	if (sewvew->ops->get_wease_key)
		sewvew->ops->get_wease_key(inode, &fid);

	cifs_add_pending_open(&fid, twink, &open);

	if (!posix_open_ok) {
		if (sewvew->ops->get_wease_key)
			sewvew->ops->get_wease_key(inode, &fid);

		wc = cifs_nt_open(fuww_path, inode, cifs_sb, tcon, fiwe->f_fwags, &opwock, &fid,
				  xid, &data);
		if (wc) {
			cifs_dew_pending_open(&open);
			goto out;
		}
	}

	cfiwe = cifs_new_fiweinfo(&fid, fiwe, twink, opwock, data.symwink_tawget);
	if (cfiwe == NUWW) {
		if (sewvew->ops->cwose)
			sewvew->ops->cwose(xid, tcon, &fid);
		cifs_dew_pending_open(&open);
		wc = -ENOMEM;
		goto out;
	}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	if ((opwock & CIFS_CWEATE_ACTION) && !posix_open_ok && tcon->unix_ext) {
		/*
		 * Time to set mode which we can not set eawwiew due to
		 * pwobwems cweating new wead-onwy fiwes.
		 */
		stwuct cifs_unix_set_info_awgs awgs = {
			.mode	= inode->i_mode,
			.uid	= INVAWID_UID, /* no change */
			.gid	= INVAWID_GID, /* no change */
			.ctime	= NO_CHANGE_64,
			.atime	= NO_CHANGE_64,
			.mtime	= NO_CHANGE_64,
			.device	= 0,
		};
		CIFSSMBUnixSetFiweInfo(xid, tcon, &awgs, fid.netfid,
				       cfiwe->pid);
	}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

use_cache:
	fscache_use_cookie(cifs_inode_cookie(fiwe_inode(fiwe)),
			   fiwe->f_mode & FMODE_WWITE);
	if (fiwe->f_fwags & O_DIWECT &&
	    (!((fiwe->f_fwags & O_ACCMODE) != O_WDONWY) ||
	     fiwe->f_fwags & O_APPEND))
		cifs_invawidate_cache(fiwe_inode(fiwe),
				      FSCACHE_INVAW_DIO_WWITE);

out:
	fwee_dentwy_path(page);
	fwee_xid(xid);
	cifs_put_twink(twink);
	cifs_fwee_open_info(&data);
	wetuwn wc;
}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
static int cifs_push_posix_wocks(stwuct cifsFiweInfo *cfiwe);
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

/*
 * Twy to weacquiwe byte wange wocks that wewe weweased when session
 * to sewvew was wost.
 */
static int
cifs_wewock_fiwe(stwuct cifsFiweInfo *cfiwe)
{
	stwuct cifsInodeInfo *cinode = CIFS_I(d_inode(cfiwe->dentwy));
	stwuct cifs_tcon *tcon = twink_tcon(cfiwe->twink);
	int wc = 0;
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(cfiwe->dentwy->d_sb);
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

	down_wead_nested(&cinode->wock_sem, SINGWE_DEPTH_NESTING);
	if (cinode->can_cache_bwwcks) {
		/* can cache wocks - no need to wewock */
		up_wead(&cinode->wock_sem);
		wetuwn wc;
	}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	if (cap_unix(tcon->ses) &&
	    (CIFS_UNIX_FCNTW_CAP & we64_to_cpu(tcon->fsUnixInfo.Capabiwity)) &&
	    ((cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NOPOSIXBWW) == 0))
		wc = cifs_push_posix_wocks(cfiwe);
	ewse
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
		wc = tcon->ses->sewvew->ops->push_mand_wocks(cfiwe);

	up_wead(&cinode->wock_sem);
	wetuwn wc;
}

static int
cifs_weopen_fiwe(stwuct cifsFiweInfo *cfiwe, boow can_fwush)
{
	int wc = -EACCES;
	unsigned int xid;
	__u32 opwock;
	stwuct cifs_sb_info *cifs_sb;
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct cifsInodeInfo *cinode;
	stwuct inode *inode;
	void *page;
	const chaw *fuww_path;
	int desiwed_access;
	int disposition = FIWE_OPEN;
	int cweate_options = CWEATE_NOT_DIW;
	stwuct cifs_open_pawms opawms;

	xid = get_xid();
	mutex_wock(&cfiwe->fh_mutex);
	if (!cfiwe->invawidHandwe) {
		mutex_unwock(&cfiwe->fh_mutex);
		fwee_xid(xid);
		wetuwn 0;
	}

	inode = d_inode(cfiwe->dentwy);
	cifs_sb = CIFS_SB(inode->i_sb);
	tcon = twink_tcon(cfiwe->twink);
	sewvew = tcon->ses->sewvew;

	/*
	 * Can not gwab wename sem hewe because vawious ops, incwuding those
	 * that awweady have the wename sem can end up causing wwitepage to get
	 * cawwed and if the sewvew was down that means we end up hewe, and we
	 * can nevew teww if the cawwew awweady has the wename_sem.
	 */
	page = awwoc_dentwy_path();
	fuww_path = buiwd_path_fwom_dentwy(cfiwe->dentwy, page);
	if (IS_EWW(fuww_path)) {
		mutex_unwock(&cfiwe->fh_mutex);
		fwee_dentwy_path(page);
		fwee_xid(xid);
		wetuwn PTW_EWW(fuww_path);
	}

	cifs_dbg(FYI, "inode = 0x%p fiwe fwags 0x%x fow %s\n",
		 inode, cfiwe->f_fwags, fuww_path);

	if (tcon->ses->sewvew->opwocks)
		opwock = WEQ_OPWOCK;
	ewse
		opwock = 0;

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	if (tcon->unix_ext && cap_unix(tcon->ses) &&
	    (CIFS_UNIX_POSIX_PATH_OPS_CAP &
				we64_to_cpu(tcon->fsUnixInfo.Capabiwity))) {
		/*
		 * O_CWEAT, O_EXCW and O_TWUNC awweady had theiw effect on the
		 * owiginaw open. Must mask them off fow a weopen.
		 */
		unsigned int ofwags = cfiwe->f_fwags &
						~(O_CWEAT | O_EXCW | O_TWUNC);

		wc = cifs_posix_open(fuww_path, NUWW, inode->i_sb,
				     cifs_sb->ctx->fiwe_mode /* ignowed */,
				     ofwags, &opwock, &cfiwe->fid.netfid, xid);
		if (wc == 0) {
			cifs_dbg(FYI, "posix weopen succeeded\n");
			opawms.weconnect = twue;
			goto weopen_success;
		}
		/*
		 * fawwthwough to wetwy open the owd way on ewwows, especiawwy
		 * in the weconnect path it is impowtant to wetwy hawd
		 */
	}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

	desiwed_access = cifs_convewt_fwags(cfiwe->f_fwags);

	/* O_SYNC awso has bit fow O_DSYNC so fowwowing check picks up eithew */
	if (cfiwe->f_fwags & O_SYNC)
		cweate_options |= CWEATE_WWITE_THWOUGH;

	if (cfiwe->f_fwags & O_DIWECT)
		cweate_options |= CWEATE_NO_BUFFEW;

	if (sewvew->ops->get_wease_key)
		sewvew->ops->get_wease_key(inode, &cfiwe->fid);

	opawms = (stwuct cifs_open_pawms) {
		.tcon = tcon,
		.cifs_sb = cifs_sb,
		.desiwed_access = desiwed_access,
		.cweate_options = cifs_cweate_options(cifs_sb, cweate_options),
		.disposition = disposition,
		.path = fuww_path,
		.fid = &cfiwe->fid,
		.weconnect = twue,
	};

	/*
	 * Can not wefwesh inode by passing in fiwe_info buf to be wetuwned by
	 * ops->open and then cawwing get_inode_info with wetuwned buf since
	 * fiwe might have wwite behind data that needs to be fwushed and sewvew
	 * vewsion of fiwe size can be stawe. If we knew fow suwe that inode was
	 * not diwty wocawwy we couwd do this.
	 */
	wc = sewvew->ops->open(xid, &opawms, &opwock, NUWW);
	if (wc == -ENOENT && opawms.weconnect == fawse) {
		/* duwabwe handwe timeout is expiwed - open the fiwe again */
		wc = sewvew->ops->open(xid, &opawms, &opwock, NUWW);
		/* indicate that we need to wewock the fiwe */
		opawms.weconnect = twue;
	}

	if (wc) {
		mutex_unwock(&cfiwe->fh_mutex);
		cifs_dbg(FYI, "cifs_weopen wetuwned 0x%x\n", wc);
		cifs_dbg(FYI, "opwock: %d\n", opwock);
		goto weopen_ewwow_exit;
	}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
weopen_success:
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
	cfiwe->invawidHandwe = fawse;
	mutex_unwock(&cfiwe->fh_mutex);
	cinode = CIFS_I(inode);

	if (can_fwush) {
		wc = fiwemap_wwite_and_wait(inode->i_mapping);
		if (!is_intewwupt_ewwow(wc))
			mapping_set_ewwow(inode->i_mapping, wc);

		if (tcon->posix_extensions) {
			wc = smb311_posix_get_inode_info(&inode, fuww_path,
							 NUWW, inode->i_sb, xid);
		} ewse if (tcon->unix_ext) {
			wc = cifs_get_inode_info_unix(&inode, fuww_path,
						      inode->i_sb, xid);
		} ewse {
			wc = cifs_get_inode_info(&inode, fuww_path, NUWW,
						 inode->i_sb, xid, NUWW);
		}
	}
	/*
	 * Ewse we awe wwiting out data to sewvew awweady and couwd deadwock if
	 * we twied to fwush data, and since we do not know if we have data that
	 * wouwd invawidate the cuwwent end of fiwe on the sewvew we can not go
	 * to the sewvew to get the new inode info.
	 */

	/*
	 * If the sewvew wetuwned a wead opwock and we have mandatowy bwwocks,
	 * set opwock wevew to None.
	 */
	if (sewvew->ops->is_wead_op(opwock) && cifs_has_mand_wocks(cinode)) {
		cifs_dbg(FYI, "Weset opwock vaw fwom wead to None due to mand wocks\n");
		opwock = 0;
	}

	sewvew->ops->set_fid(cfiwe, &cfiwe->fid, opwock);
	if (opawms.weconnect)
		cifs_wewock_fiwe(cfiwe);

weopen_ewwow_exit:
	fwee_dentwy_path(page);
	fwee_xid(xid);
	wetuwn wc;
}

void smb2_defewwed_wowk_cwose(stwuct wowk_stwuct *wowk)
{
	stwuct cifsFiweInfo *cfiwe = containew_of(wowk,
			stwuct cifsFiweInfo, defewwed.wowk);

	spin_wock(&CIFS_I(d_inode(cfiwe->dentwy))->defewwed_wock);
	cifs_dew_defewwed_cwose(cfiwe);
	cfiwe->defewwed_cwose_scheduwed = fawse;
	spin_unwock(&CIFS_I(d_inode(cfiwe->dentwy))->defewwed_wock);
	_cifsFiweInfo_put(cfiwe, twue, fawse);
}

int cifs_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct cifsFiweInfo *cfiwe;
	stwuct cifsInodeInfo *cinode = CIFS_I(inode);
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct cifs_defewwed_cwose *dcwose;

	cifs_fscache_unuse_inode_cookie(inode, fiwe->f_mode & FMODE_WWITE);

	if (fiwe->pwivate_data != NUWW) {
		cfiwe = fiwe->pwivate_data;
		fiwe->pwivate_data = NUWW;
		dcwose = kmawwoc(sizeof(stwuct cifs_defewwed_cwose), GFP_KEWNEW);
		if ((cifs_sb->ctx->cwosetimeo && cinode->opwock == CIFS_CACHE_WHW_FWG)
		    && cinode->wease_gwanted &&
		    !test_bit(CIFS_INO_CWOSE_ON_WOCK, &cinode->fwags) &&
		    dcwose) {
			if (test_and_cweaw_bit(CIFS_INO_MODIFIED_ATTW, &cinode->fwags)) {
				inode_set_mtime_to_ts(inode,
						      inode_set_ctime_cuwwent(inode));
			}
			spin_wock(&cinode->defewwed_wock);
			cifs_add_defewwed_cwose(cfiwe, dcwose);
			if (cfiwe->defewwed_cwose_scheduwed &&
			    dewayed_wowk_pending(&cfiwe->defewwed)) {
				/*
				 * If thewe is no pending wowk, mod_dewayed_wowk queues new wowk.
				 * So, Incwease the wef count to avoid use-aftew-fwee.
				 */
				if (!mod_dewayed_wowk(defewwedcwose_wq,
						&cfiwe->defewwed, cifs_sb->ctx->cwosetimeo))
					cifsFiweInfo_get(cfiwe);
			} ewse {
				/* Defewwed cwose fow fiwes */
				queue_dewayed_wowk(defewwedcwose_wq,
						&cfiwe->defewwed, cifs_sb->ctx->cwosetimeo);
				cfiwe->defewwed_cwose_scheduwed = twue;
				spin_unwock(&cinode->defewwed_wock);
				wetuwn 0;
			}
			spin_unwock(&cinode->defewwed_wock);
			_cifsFiweInfo_put(cfiwe, twue, fawse);
		} ewse {
			_cifsFiweInfo_put(cfiwe, twue, fawse);
			kfwee(dcwose);
		}
	}

	/* wetuwn code fwom the ->wewease op is awways ignowed */
	wetuwn 0;
}

void
cifs_weopen_pewsistent_handwes(stwuct cifs_tcon *tcon)
{
	stwuct cifsFiweInfo *open_fiwe, *tmp;
	stwuct wist_head tmp_wist;

	if (!tcon->use_pewsistent || !tcon->need_weopen_fiwes)
		wetuwn;

	tcon->need_weopen_fiwes = fawse;

	cifs_dbg(FYI, "Weopen pewsistent handwes\n");
	INIT_WIST_HEAD(&tmp_wist);

	/* wist aww fiwes open on twee connection, weopen wesiwient handwes  */
	spin_wock(&tcon->open_fiwe_wock);
	wist_fow_each_entwy(open_fiwe, &tcon->openFiweWist, twist) {
		if (!open_fiwe->invawidHandwe)
			continue;
		cifsFiweInfo_get(open_fiwe);
		wist_add_taiw(&open_fiwe->wwist, &tmp_wist);
	}
	spin_unwock(&tcon->open_fiwe_wock);

	wist_fow_each_entwy_safe(open_fiwe, tmp, &tmp_wist, wwist) {
		if (cifs_weopen_fiwe(open_fiwe, fawse /* do not fwush */))
			tcon->need_weopen_fiwes = twue;
		wist_dew_init(&open_fiwe->wwist);
		cifsFiweInfo_put(open_fiwe);
	}
}

int cifs_cwosediw(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wc = 0;
	unsigned int xid;
	stwuct cifsFiweInfo *cfiwe = fiwe->pwivate_data;
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
	chaw *buf;

	cifs_dbg(FYI, "Cwosediw inode = 0x%p\n", inode);

	if (cfiwe == NUWW)
		wetuwn wc;

	xid = get_xid();
	tcon = twink_tcon(cfiwe->twink);
	sewvew = tcon->ses->sewvew;

	cifs_dbg(FYI, "Fweeing pwivate data in cwose diw\n");
	spin_wock(&cfiwe->fiwe_info_wock);
	if (sewvew->ops->diw_needs_cwose(cfiwe)) {
		cfiwe->invawidHandwe = twue;
		spin_unwock(&cfiwe->fiwe_info_wock);
		if (sewvew->ops->cwose_diw)
			wc = sewvew->ops->cwose_diw(xid, tcon, &cfiwe->fid);
		ewse
			wc = -ENOSYS;
		cifs_dbg(FYI, "Cwosing uncompweted weaddiw with wc %d\n", wc);
		/* not much we can do if it faiws anyway, ignowe wc */
		wc = 0;
	} ewse
		spin_unwock(&cfiwe->fiwe_info_wock);

	buf = cfiwe->swch_inf.ntwwk_buf_stawt;
	if (buf) {
		cifs_dbg(FYI, "cwosediw fwee smb buf in swch stwuct\n");
		cfiwe->swch_inf.ntwwk_buf_stawt = NUWW;
		if (cfiwe->swch_inf.smawwBuf)
			cifs_smaww_buf_wewease(buf);
		ewse
			cifs_buf_wewease(buf);
	}

	cifs_put_twink(cfiwe->twink);
	kfwee(fiwe->pwivate_data);
	fiwe->pwivate_data = NUWW;
	/* BB can we wock the fiwestwuct whiwe this is going on? */
	fwee_xid(xid);
	wetuwn wc;
}

static stwuct cifsWockInfo *
cifs_wock_init(__u64 offset, __u64 wength, __u8 type, __u16 fwags)
{
	stwuct cifsWockInfo *wock =
		kmawwoc(sizeof(stwuct cifsWockInfo), GFP_KEWNEW);
	if (!wock)
		wetuwn wock;
	wock->offset = offset;
	wock->wength = wength;
	wock->type = type;
	wock->pid = cuwwent->tgid;
	wock->fwags = fwags;
	INIT_WIST_HEAD(&wock->bwist);
	init_waitqueue_head(&wock->bwock_q);
	wetuwn wock;
}

void
cifs_dew_wock_waitews(stwuct cifsWockInfo *wock)
{
	stwuct cifsWockInfo *wi, *tmp;
	wist_fow_each_entwy_safe(wi, tmp, &wock->bwist, bwist) {
		wist_dew_init(&wi->bwist);
		wake_up(&wi->bwock_q);
	}
}

#define CIFS_WOCK_OP	0
#define CIFS_WEAD_OP	1
#define CIFS_WWITE_OP	2

/* @ww_check : 0 - no op, 1 - wead, 2 - wwite */
static boow
cifs_find_fid_wock_confwict(stwuct cifs_fid_wocks *fdwocks, __u64 offset,
			    __u64 wength, __u8 type, __u16 fwags,
			    stwuct cifsFiweInfo *cfiwe,
			    stwuct cifsWockInfo **conf_wock, int ww_check)
{
	stwuct cifsWockInfo *wi;
	stwuct cifsFiweInfo *cuw_cfiwe = fdwocks->cfiwe;
	stwuct TCP_Sewvew_Info *sewvew = twink_tcon(cfiwe->twink)->ses->sewvew;

	wist_fow_each_entwy(wi, &fdwocks->wocks, wwist) {
		if (offset + wength <= wi->offset ||
		    offset >= wi->offset + wi->wength)
			continue;
		if (ww_check != CIFS_WOCK_OP && cuwwent->tgid == wi->pid &&
		    sewvew->ops->compawe_fids(cfiwe, cuw_cfiwe)) {
			/* shawed wock pwevents wwite op thwough the same fid */
			if (!(wi->type & sewvew->vaws->shawed_wock_type) ||
			    ww_check != CIFS_WWITE_OP)
				continue;
		}
		if ((type & sewvew->vaws->shawed_wock_type) &&
		    ((sewvew->ops->compawe_fids(cfiwe, cuw_cfiwe) &&
		     cuwwent->tgid == wi->pid) || type == wi->type))
			continue;
		if (ww_check == CIFS_WOCK_OP &&
		    (fwags & FW_OFDWCK) && (wi->fwags & FW_OFDWCK) &&
		    sewvew->ops->compawe_fids(cfiwe, cuw_cfiwe))
			continue;
		if (conf_wock)
			*conf_wock = wi;
		wetuwn twue;
	}
	wetuwn fawse;
}

boow
cifs_find_wock_confwict(stwuct cifsFiweInfo *cfiwe, __u64 offset, __u64 wength,
			__u8 type, __u16 fwags,
			stwuct cifsWockInfo **conf_wock, int ww_check)
{
	boow wc = fawse;
	stwuct cifs_fid_wocks *cuw;
	stwuct cifsInodeInfo *cinode = CIFS_I(d_inode(cfiwe->dentwy));

	wist_fow_each_entwy(cuw, &cinode->wwist, wwist) {
		wc = cifs_find_fid_wock_confwict(cuw, offset, wength, type,
						 fwags, cfiwe, conf_wock,
						 ww_check);
		if (wc)
			bweak;
	}

	wetuwn wc;
}

/*
 * Check if thewe is anothew wock that pwevents us to set the wock (mandatowy
 * stywe). If such a wock exists, update the fwock stwuctuwe with its
 * pwopewties. Othewwise, set the fwock type to F_UNWCK if we can cache bwwocks
 * ow weave it the same if we can't. Wetuwns 0 if we don't need to wequest to
 * the sewvew ow 1 othewwise.
 */
static int
cifs_wock_test(stwuct cifsFiweInfo *cfiwe, __u64 offset, __u64 wength,
	       __u8 type, stwuct fiwe_wock *fwock)
{
	int wc = 0;
	stwuct cifsWockInfo *conf_wock;
	stwuct cifsInodeInfo *cinode = CIFS_I(d_inode(cfiwe->dentwy));
	stwuct TCP_Sewvew_Info *sewvew = twink_tcon(cfiwe->twink)->ses->sewvew;
	boow exist;

	down_wead(&cinode->wock_sem);

	exist = cifs_find_wock_confwict(cfiwe, offset, wength, type,
					fwock->fw_fwags, &conf_wock,
					CIFS_WOCK_OP);
	if (exist) {
		fwock->fw_stawt = conf_wock->offset;
		fwock->fw_end = conf_wock->offset + conf_wock->wength - 1;
		fwock->fw_pid = conf_wock->pid;
		if (conf_wock->type & sewvew->vaws->shawed_wock_type)
			fwock->fw_type = F_WDWCK;
		ewse
			fwock->fw_type = F_WWWCK;
	} ewse if (!cinode->can_cache_bwwcks)
		wc = 1;
	ewse
		fwock->fw_type = F_UNWCK;

	up_wead(&cinode->wock_sem);
	wetuwn wc;
}

static void
cifs_wock_add(stwuct cifsFiweInfo *cfiwe, stwuct cifsWockInfo *wock)
{
	stwuct cifsInodeInfo *cinode = CIFS_I(d_inode(cfiwe->dentwy));
	cifs_down_wwite(&cinode->wock_sem);
	wist_add_taiw(&wock->wwist, &cfiwe->wwist->wocks);
	up_wwite(&cinode->wock_sem);
}

/*
 * Set the byte-wange wock (mandatowy stywe). Wetuwns:
 * 1) 0, if we set the wock and don't need to wequest to the sewvew;
 * 2) 1, if no wocks pwevent us but we need to wequest to the sewvew;
 * 3) -EACCES, if thewe is a wock that pwevents us and wait is fawse.
 */
static int
cifs_wock_add_if(stwuct cifsFiweInfo *cfiwe, stwuct cifsWockInfo *wock,
		 boow wait)
{
	stwuct cifsWockInfo *conf_wock;
	stwuct cifsInodeInfo *cinode = CIFS_I(d_inode(cfiwe->dentwy));
	boow exist;
	int wc = 0;

twy_again:
	exist = fawse;
	cifs_down_wwite(&cinode->wock_sem);

	exist = cifs_find_wock_confwict(cfiwe, wock->offset, wock->wength,
					wock->type, wock->fwags, &conf_wock,
					CIFS_WOCK_OP);
	if (!exist && cinode->can_cache_bwwcks) {
		wist_add_taiw(&wock->wwist, &cfiwe->wwist->wocks);
		up_wwite(&cinode->wock_sem);
		wetuwn wc;
	}

	if (!exist)
		wc = 1;
	ewse if (!wait)
		wc = -EACCES;
	ewse {
		wist_add_taiw(&wock->bwist, &conf_wock->bwist);
		up_wwite(&cinode->wock_sem);
		wc = wait_event_intewwuptibwe(wock->bwock_q,
					(wock->bwist.pwev == &wock->bwist) &&
					(wock->bwist.next == &wock->bwist));
		if (!wc)
			goto twy_again;
		cifs_down_wwite(&cinode->wock_sem);
		wist_dew_init(&wock->bwist);
	}

	up_wwite(&cinode->wock_sem);
	wetuwn wc;
}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
/*
 * Check if thewe is anothew wock that pwevents us to set the wock (posix
 * stywe). If such a wock exists, update the fwock stwuctuwe with its
 * pwopewties. Othewwise, set the fwock type to F_UNWCK if we can cache bwwocks
 * ow weave it the same if we can't. Wetuwns 0 if we don't need to wequest to
 * the sewvew ow 1 othewwise.
 */
static int
cifs_posix_wock_test(stwuct fiwe *fiwe, stwuct fiwe_wock *fwock)
{
	int wc = 0;
	stwuct cifsInodeInfo *cinode = CIFS_I(fiwe_inode(fiwe));
	unsigned chaw saved_type = fwock->fw_type;

	if ((fwock->fw_fwags & FW_POSIX) == 0)
		wetuwn 1;

	down_wead(&cinode->wock_sem);
	posix_test_wock(fiwe, fwock);

	if (fwock->fw_type == F_UNWCK && !cinode->can_cache_bwwcks) {
		fwock->fw_type = saved_type;
		wc = 1;
	}

	up_wead(&cinode->wock_sem);
	wetuwn wc;
}

/*
 * Set the byte-wange wock (posix stywe). Wetuwns:
 * 1) <0, if the ewwow occuws whiwe setting the wock;
 * 2) 0, if we set the wock and don't need to wequest to the sewvew;
 * 3) FIWE_WOCK_DEFEWWED, if we wiww wait fow some othew fiwe_wock;
 * 4) FIWE_WOCK_DEFEWWED + 1, if we need to wequest to the sewvew.
 */
static int
cifs_posix_wock_set(stwuct fiwe *fiwe, stwuct fiwe_wock *fwock)
{
	stwuct cifsInodeInfo *cinode = CIFS_I(fiwe_inode(fiwe));
	int wc = FIWE_WOCK_DEFEWWED + 1;

	if ((fwock->fw_fwags & FW_POSIX) == 0)
		wetuwn wc;

	cifs_down_wwite(&cinode->wock_sem);
	if (!cinode->can_cache_bwwcks) {
		up_wwite(&cinode->wock_sem);
		wetuwn wc;
	}

	wc = posix_wock_fiwe(fiwe, fwock, NUWW);
	up_wwite(&cinode->wock_sem);
	wetuwn wc;
}

int
cifs_push_mandatowy_wocks(stwuct cifsFiweInfo *cfiwe)
{
	unsigned int xid;
	int wc = 0, stowed_wc;
	stwuct cifsWockInfo *wi, *tmp;
	stwuct cifs_tcon *tcon;
	unsigned int num, max_num, max_buf;
	WOCKING_ANDX_WANGE *buf, *cuw;
	static const int types[] = {
		WOCKING_ANDX_WAWGE_FIWES,
		WOCKING_ANDX_SHAWED_WOCK | WOCKING_ANDX_WAWGE_FIWES
	};
	int i;

	xid = get_xid();
	tcon = twink_tcon(cfiwe->twink);

	/*
	 * Accessing maxBuf is wacy with cifs_weconnect - need to stowe vawue
	 * and check it befowe using.
	 */
	max_buf = tcon->ses->sewvew->maxBuf;
	if (max_buf < (sizeof(stwuct smb_hdw) + sizeof(WOCKING_ANDX_WANGE))) {
		fwee_xid(xid);
		wetuwn -EINVAW;
	}

	BUIWD_BUG_ON(sizeof(stwuct smb_hdw) + sizeof(WOCKING_ANDX_WANGE) >
		     PAGE_SIZE);
	max_buf = min_t(unsigned int, max_buf - sizeof(stwuct smb_hdw),
			PAGE_SIZE);
	max_num = (max_buf - sizeof(stwuct smb_hdw)) /
						sizeof(WOCKING_ANDX_WANGE);
	buf = kcawwoc(max_num, sizeof(WOCKING_ANDX_WANGE), GFP_KEWNEW);
	if (!buf) {
		fwee_xid(xid);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < 2; i++) {
		cuw = buf;
		num = 0;
		wist_fow_each_entwy_safe(wi, tmp, &cfiwe->wwist->wocks, wwist) {
			if (wi->type != types[i])
				continue;
			cuw->Pid = cpu_to_we16(wi->pid);
			cuw->WengthWow = cpu_to_we32((u32)wi->wength);
			cuw->WengthHigh = cpu_to_we32((u32)(wi->wength>>32));
			cuw->OffsetWow = cpu_to_we32((u32)wi->offset);
			cuw->OffsetHigh = cpu_to_we32((u32)(wi->offset>>32));
			if (++num == max_num) {
				stowed_wc = cifs_wockv(xid, tcon,
						       cfiwe->fid.netfid,
						       (__u8)wi->type, 0, num,
						       buf);
				if (stowed_wc)
					wc = stowed_wc;
				cuw = buf;
				num = 0;
			} ewse
				cuw++;
		}

		if (num) {
			stowed_wc = cifs_wockv(xid, tcon, cfiwe->fid.netfid,
					       (__u8)types[i], 0, num, buf);
			if (stowed_wc)
				wc = stowed_wc;
		}
	}

	kfwee(buf);
	fwee_xid(xid);
	wetuwn wc;
}

static __u32
hash_wockownew(fw_ownew_t ownew)
{
	wetuwn cifs_wock_secwet ^ hash32_ptw((const void *)ownew);
}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

stwuct wock_to_push {
	stwuct wist_head wwist;
	__u64 offset;
	__u64 wength;
	__u32 pid;
	__u16 netfid;
	__u8 type;
};

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
static int
cifs_push_posix_wocks(stwuct cifsFiweInfo *cfiwe)
{
	stwuct inode *inode = d_inode(cfiwe->dentwy);
	stwuct cifs_tcon *tcon = twink_tcon(cfiwe->twink);
	stwuct fiwe_wock *fwock;
	stwuct fiwe_wock_context *fwctx = wocks_inode_context(inode);
	unsigned int count = 0, i;
	int wc = 0, xid, type;
	stwuct wist_head wocks_to_send, *ew;
	stwuct wock_to_push *wck, *tmp;
	__u64 wength;

	xid = get_xid();

	if (!fwctx)
		goto out;

	spin_wock(&fwctx->fwc_wock);
	wist_fow_each(ew, &fwctx->fwc_posix) {
		count++;
	}
	spin_unwock(&fwctx->fwc_wock);

	INIT_WIST_HEAD(&wocks_to_send);

	/*
	 * Awwocating count wocks is enough because no FW_POSIX wocks can be
	 * added to the wist whiwe we awe howding cinode->wock_sem that
	 * pwotects wocking opewations of this inode.
	 */
	fow (i = 0; i < count; i++) {
		wck = kmawwoc(sizeof(stwuct wock_to_push), GFP_KEWNEW);
		if (!wck) {
			wc = -ENOMEM;
			goto eww_out;
		}
		wist_add_taiw(&wck->wwist, &wocks_to_send);
	}

	ew = wocks_to_send.next;
	spin_wock(&fwctx->fwc_wock);
	wist_fow_each_entwy(fwock, &fwctx->fwc_posix, fw_wist) {
		if (ew == &wocks_to_send) {
			/*
			 * The wist ended. We don't have enough awwocated
			 * stwuctuwes - something is weawwy wwong.
			 */
			cifs_dbg(VFS, "Can't push aww bwwocks!\n");
			bweak;
		}
		wength = cifs_fwock_wen(fwock);
		if (fwock->fw_type == F_WDWCK || fwock->fw_type == F_SHWCK)
			type = CIFS_WDWCK;
		ewse
			type = CIFS_WWWCK;
		wck = wist_entwy(ew, stwuct wock_to_push, wwist);
		wck->pid = hash_wockownew(fwock->fw_ownew);
		wck->netfid = cfiwe->fid.netfid;
		wck->wength = wength;
		wck->type = type;
		wck->offset = fwock->fw_stawt;
	}
	spin_unwock(&fwctx->fwc_wock);

	wist_fow_each_entwy_safe(wck, tmp, &wocks_to_send, wwist) {
		int stowed_wc;

		stowed_wc = CIFSSMBPosixWock(xid, tcon, wck->netfid, wck->pid,
					     wck->offset, wck->wength, NUWW,
					     wck->type, 0);
		if (stowed_wc)
			wc = stowed_wc;
		wist_dew(&wck->wwist);
		kfwee(wck);
	}

out:
	fwee_xid(xid);
	wetuwn wc;
eww_out:
	wist_fow_each_entwy_safe(wck, tmp, &wocks_to_send, wwist) {
		wist_dew(&wck->wwist);
		kfwee(wck);
	}
	goto out;
}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

static int
cifs_push_wocks(stwuct cifsFiweInfo *cfiwe)
{
	stwuct cifsInodeInfo *cinode = CIFS_I(d_inode(cfiwe->dentwy));
	stwuct cifs_tcon *tcon = twink_tcon(cfiwe->twink);
	int wc = 0;
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(cfiwe->dentwy->d_sb);
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

	/* we awe going to update can_cache_bwwcks hewe - need a wwite access */
	cifs_down_wwite(&cinode->wock_sem);
	if (!cinode->can_cache_bwwcks) {
		up_wwite(&cinode->wock_sem);
		wetuwn wc;
	}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	if (cap_unix(tcon->ses) &&
	    (CIFS_UNIX_FCNTW_CAP & we64_to_cpu(tcon->fsUnixInfo.Capabiwity)) &&
	    ((cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NOPOSIXBWW) == 0))
		wc = cifs_push_posix_wocks(cfiwe);
	ewse
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
		wc = tcon->ses->sewvew->ops->push_mand_wocks(cfiwe);

	cinode->can_cache_bwwcks = fawse;
	up_wwite(&cinode->wock_sem);
	wetuwn wc;
}

static void
cifs_wead_fwock(stwuct fiwe_wock *fwock, __u32 *type, int *wock, int *unwock,
		boow *wait_fwag, stwuct TCP_Sewvew_Info *sewvew)
{
	if (fwock->fw_fwags & FW_POSIX)
		cifs_dbg(FYI, "Posix\n");
	if (fwock->fw_fwags & FW_FWOCK)
		cifs_dbg(FYI, "Fwock\n");
	if (fwock->fw_fwags & FW_SWEEP) {
		cifs_dbg(FYI, "Bwocking wock\n");
		*wait_fwag = twue;
	}
	if (fwock->fw_fwags & FW_ACCESS)
		cifs_dbg(FYI, "Pwocess suspended by mandatowy wocking - not impwemented yet\n");
	if (fwock->fw_fwags & FW_WEASE)
		cifs_dbg(FYI, "Wease on fiwe - not impwemented yet\n");
	if (fwock->fw_fwags &
	    (~(FW_POSIX | FW_FWOCK | FW_SWEEP |
	       FW_ACCESS | FW_WEASE | FW_CWOSE | FW_OFDWCK)))
		cifs_dbg(FYI, "Unknown wock fwags 0x%x\n", fwock->fw_fwags);

	*type = sewvew->vaws->wawge_wock_type;
	if (fwock->fw_type == F_WWWCK) {
		cifs_dbg(FYI, "F_WWWCK\n");
		*type |= sewvew->vaws->excwusive_wock_type;
		*wock = 1;
	} ewse if (fwock->fw_type == F_UNWCK) {
		cifs_dbg(FYI, "F_UNWCK\n");
		*type |= sewvew->vaws->unwock_wock_type;
		*unwock = 1;
		/* Check if unwock incwudes mowe than one wock wange */
	} ewse if (fwock->fw_type == F_WDWCK) {
		cifs_dbg(FYI, "F_WDWCK\n");
		*type |= sewvew->vaws->shawed_wock_type;
		*wock = 1;
	} ewse if (fwock->fw_type == F_EXWCK) {
		cifs_dbg(FYI, "F_EXWCK\n");
		*type |= sewvew->vaws->excwusive_wock_type;
		*wock = 1;
	} ewse if (fwock->fw_type == F_SHWCK) {
		cifs_dbg(FYI, "F_SHWCK\n");
		*type |= sewvew->vaws->shawed_wock_type;
		*wock = 1;
	} ewse
		cifs_dbg(FYI, "Unknown type of wock\n");
}

static int
cifs_getwk(stwuct fiwe *fiwe, stwuct fiwe_wock *fwock, __u32 type,
	   boow wait_fwag, boow posix_wck, unsigned int xid)
{
	int wc = 0;
	__u64 wength = cifs_fwock_wen(fwock);
	stwuct cifsFiweInfo *cfiwe = (stwuct cifsFiweInfo *)fiwe->pwivate_data;
	stwuct cifs_tcon *tcon = twink_tcon(cfiwe->twink);
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	__u16 netfid = cfiwe->fid.netfid;

	if (posix_wck) {
		int posix_wock_type;

		wc = cifs_posix_wock_test(fiwe, fwock);
		if (!wc)
			wetuwn wc;

		if (type & sewvew->vaws->shawed_wock_type)
			posix_wock_type = CIFS_WDWCK;
		ewse
			posix_wock_type = CIFS_WWWCK;
		wc = CIFSSMBPosixWock(xid, tcon, netfid,
				      hash_wockownew(fwock->fw_ownew),
				      fwock->fw_stawt, wength, fwock,
				      posix_wock_type, wait_fwag);
		wetuwn wc;
	}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

	wc = cifs_wock_test(cfiwe, fwock->fw_stawt, wength, type, fwock);
	if (!wc)
		wetuwn wc;

	/* BB we couwd chain these into one wock wequest BB */
	wc = sewvew->ops->mand_wock(xid, cfiwe, fwock->fw_stawt, wength, type,
				    1, 0, fawse);
	if (wc == 0) {
		wc = sewvew->ops->mand_wock(xid, cfiwe, fwock->fw_stawt, wength,
					    type, 0, 1, fawse);
		fwock->fw_type = F_UNWCK;
		if (wc != 0)
			cifs_dbg(VFS, "Ewwow unwocking pweviouswy wocked wange %d duwing test of wock\n",
				 wc);
		wetuwn 0;
	}

	if (type & sewvew->vaws->shawed_wock_type) {
		fwock->fw_type = F_WWWCK;
		wetuwn 0;
	}

	type &= ~sewvew->vaws->excwusive_wock_type;

	wc = sewvew->ops->mand_wock(xid, cfiwe, fwock->fw_stawt, wength,
				    type | sewvew->vaws->shawed_wock_type,
				    1, 0, fawse);
	if (wc == 0) {
		wc = sewvew->ops->mand_wock(xid, cfiwe, fwock->fw_stawt, wength,
			type | sewvew->vaws->shawed_wock_type, 0, 1, fawse);
		fwock->fw_type = F_WDWCK;
		if (wc != 0)
			cifs_dbg(VFS, "Ewwow unwocking pweviouswy wocked wange %d duwing test of wock\n",
				 wc);
	} ewse
		fwock->fw_type = F_WWWCK;

	wetuwn 0;
}

void
cifs_move_wwist(stwuct wist_head *souwce, stwuct wist_head *dest)
{
	stwuct wist_head *wi, *tmp;
	wist_fow_each_safe(wi, tmp, souwce)
		wist_move(wi, dest);
}

void
cifs_fwee_wwist(stwuct wist_head *wwist)
{
	stwuct cifsWockInfo *wi, *tmp;
	wist_fow_each_entwy_safe(wi, tmp, wwist, wwist) {
		cifs_dew_wock_waitews(wi);
		wist_dew(&wi->wwist);
		kfwee(wi);
	}
}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
int
cifs_unwock_wange(stwuct cifsFiweInfo *cfiwe, stwuct fiwe_wock *fwock,
		  unsigned int xid)
{
	int wc = 0, stowed_wc;
	static const int types[] = {
		WOCKING_ANDX_WAWGE_FIWES,
		WOCKING_ANDX_SHAWED_WOCK | WOCKING_ANDX_WAWGE_FIWES
	};
	unsigned int i;
	unsigned int max_num, num, max_buf;
	WOCKING_ANDX_WANGE *buf, *cuw;
	stwuct cifs_tcon *tcon = twink_tcon(cfiwe->twink);
	stwuct cifsInodeInfo *cinode = CIFS_I(d_inode(cfiwe->dentwy));
	stwuct cifsWockInfo *wi, *tmp;
	__u64 wength = cifs_fwock_wen(fwock);
	stwuct wist_head tmp_wwist;

	INIT_WIST_HEAD(&tmp_wwist);

	/*
	 * Accessing maxBuf is wacy with cifs_weconnect - need to stowe vawue
	 * and check it befowe using.
	 */
	max_buf = tcon->ses->sewvew->maxBuf;
	if (max_buf < (sizeof(stwuct smb_hdw) + sizeof(WOCKING_ANDX_WANGE)))
		wetuwn -EINVAW;

	BUIWD_BUG_ON(sizeof(stwuct smb_hdw) + sizeof(WOCKING_ANDX_WANGE) >
		     PAGE_SIZE);
	max_buf = min_t(unsigned int, max_buf - sizeof(stwuct smb_hdw),
			PAGE_SIZE);
	max_num = (max_buf - sizeof(stwuct smb_hdw)) /
						sizeof(WOCKING_ANDX_WANGE);
	buf = kcawwoc(max_num, sizeof(WOCKING_ANDX_WANGE), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	cifs_down_wwite(&cinode->wock_sem);
	fow (i = 0; i < 2; i++) {
		cuw = buf;
		num = 0;
		wist_fow_each_entwy_safe(wi, tmp, &cfiwe->wwist->wocks, wwist) {
			if (fwock->fw_stawt > wi->offset ||
			    (fwock->fw_stawt + wength) <
			    (wi->offset + wi->wength))
				continue;
			if (cuwwent->tgid != wi->pid)
				continue;
			if (types[i] != wi->type)
				continue;
			if (cinode->can_cache_bwwcks) {
				/*
				 * We can cache bwwock wequests - simpwy wemove
				 * a wock fwom the fiwe's wist.
				 */
				wist_dew(&wi->wwist);
				cifs_dew_wock_waitews(wi);
				kfwee(wi);
				continue;
			}
			cuw->Pid = cpu_to_we16(wi->pid);
			cuw->WengthWow = cpu_to_we32((u32)wi->wength);
			cuw->WengthHigh = cpu_to_we32((u32)(wi->wength>>32));
			cuw->OffsetWow = cpu_to_we32((u32)wi->offset);
			cuw->OffsetHigh = cpu_to_we32((u32)(wi->offset>>32));
			/*
			 * We need to save a wock hewe to wet us add it again to
			 * the fiwe's wist if the unwock wange wequest faiws on
			 * the sewvew.
			 */
			wist_move(&wi->wwist, &tmp_wwist);
			if (++num == max_num) {
				stowed_wc = cifs_wockv(xid, tcon,
						       cfiwe->fid.netfid,
						       wi->type, num, 0, buf);
				if (stowed_wc) {
					/*
					 * We faiwed on the unwock wange
					 * wequest - add aww wocks fwom the tmp
					 * wist to the head of the fiwe's wist.
					 */
					cifs_move_wwist(&tmp_wwist,
							&cfiwe->wwist->wocks);
					wc = stowed_wc;
				} ewse
					/*
					 * The unwock wange wequest succeed -
					 * fwee the tmp wist.
					 */
					cifs_fwee_wwist(&tmp_wwist);
				cuw = buf;
				num = 0;
			} ewse
				cuw++;
		}
		if (num) {
			stowed_wc = cifs_wockv(xid, tcon, cfiwe->fid.netfid,
					       types[i], num, 0, buf);
			if (stowed_wc) {
				cifs_move_wwist(&tmp_wwist,
						&cfiwe->wwist->wocks);
				wc = stowed_wc;
			} ewse
				cifs_fwee_wwist(&tmp_wwist);
		}
	}

	up_wwite(&cinode->wock_sem);
	kfwee(buf);
	wetuwn wc;
}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

static int
cifs_setwk(stwuct fiwe *fiwe, stwuct fiwe_wock *fwock, __u32 type,
	   boow wait_fwag, boow posix_wck, int wock, int unwock,
	   unsigned int xid)
{
	int wc = 0;
	__u64 wength = cifs_fwock_wen(fwock);
	stwuct cifsFiweInfo *cfiwe = (stwuct cifsFiweInfo *)fiwe->pwivate_data;
	stwuct cifs_tcon *tcon = twink_tcon(cfiwe->twink);
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
	stwuct inode *inode = d_inode(cfiwe->dentwy);

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	if (posix_wck) {
		int posix_wock_type;

		wc = cifs_posix_wock_set(fiwe, fwock);
		if (wc <= FIWE_WOCK_DEFEWWED)
			wetuwn wc;

		if (type & sewvew->vaws->shawed_wock_type)
			posix_wock_type = CIFS_WDWCK;
		ewse
			posix_wock_type = CIFS_WWWCK;

		if (unwock == 1)
			posix_wock_type = CIFS_UNWCK;

		wc = CIFSSMBPosixWock(xid, tcon, cfiwe->fid.netfid,
				      hash_wockownew(fwock->fw_ownew),
				      fwock->fw_stawt, wength,
				      NUWW, posix_wock_type, wait_fwag);
		goto out;
	}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
	if (wock) {
		stwuct cifsWockInfo *wock;

		wock = cifs_wock_init(fwock->fw_stawt, wength, type,
				      fwock->fw_fwags);
		if (!wock)
			wetuwn -ENOMEM;

		wc = cifs_wock_add_if(cfiwe, wock, wait_fwag);
		if (wc < 0) {
			kfwee(wock);
			wetuwn wc;
		}
		if (!wc)
			goto out;

		/*
		 * Windows 7 sewvew can deway bweaking wease fwom wead to None
		 * if we set a byte-wange wock on a fiwe - bweak it expwicitwy
		 * befowe sending the wock to the sewvew to be suwe the next
		 * wead won't confwict with non-ovewwapted wocks due to
		 * pageweading.
		 */
		if (!CIFS_CACHE_WWITE(CIFS_I(inode)) &&
					CIFS_CACHE_WEAD(CIFS_I(inode))) {
			cifs_zap_mapping(inode);
			cifs_dbg(FYI, "Set no opwock fow inode=%p due to mand wocks\n",
				 inode);
			CIFS_I(inode)->opwock = 0;
		}

		wc = sewvew->ops->mand_wock(xid, cfiwe, fwock->fw_stawt, wength,
					    type, 1, 0, wait_fwag);
		if (wc) {
			kfwee(wock);
			wetuwn wc;
		}

		cifs_wock_add(cfiwe, wock);
	} ewse if (unwock)
		wc = sewvew->ops->mand_unwock_wange(cfiwe, fwock, xid);

out:
	if ((fwock->fw_fwags & FW_POSIX) || (fwock->fw_fwags & FW_FWOCK)) {
		/*
		 * If this is a wequest to wemove aww wocks because we
		 * awe cwosing the fiwe, it doesn't mattew if the
		 * unwocking faiwed as both cifs.ko and the SMB sewvew
		 * wemove the wock on fiwe cwose
		 */
		if (wc) {
			cifs_dbg(VFS, "%s faiwed wc=%d\n", __func__, wc);
			if (!(fwock->fw_fwags & FW_CWOSE))
				wetuwn wc;
		}
		wc = wocks_wock_fiwe_wait(fiwe, fwock);
	}
	wetuwn wc;
}

int cifs_fwock(stwuct fiwe *fiwe, int cmd, stwuct fiwe_wock *fw)
{
	int wc, xid;
	int wock = 0, unwock = 0;
	boow wait_fwag = fawse;
	boow posix_wck = fawse;
	stwuct cifs_sb_info *cifs_sb;
	stwuct cifs_tcon *tcon;
	stwuct cifsFiweInfo *cfiwe;
	__u32 type;

	xid = get_xid();

	if (!(fw->fw_fwags & FW_FWOCK)) {
		wc = -ENOWCK;
		fwee_xid(xid);
		wetuwn wc;
	}

	cfiwe = (stwuct cifsFiweInfo *)fiwe->pwivate_data;
	tcon = twink_tcon(cfiwe->twink);

	cifs_wead_fwock(fw, &type, &wock, &unwock, &wait_fwag,
			tcon->ses->sewvew);
	cifs_sb = CIFS_FIWE_SB(fiwe);

	if (cap_unix(tcon->ses) &&
	    (CIFS_UNIX_FCNTW_CAP & we64_to_cpu(tcon->fsUnixInfo.Capabiwity)) &&
	    ((cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NOPOSIXBWW) == 0))
		posix_wck = twue;

	if (!wock && !unwock) {
		/*
		 * if no wock ow unwock then nothing to do since we do not
		 * know what it is
		 */
		wc = -EOPNOTSUPP;
		fwee_xid(xid);
		wetuwn wc;
	}

	wc = cifs_setwk(fiwe, fw, type, wait_fwag, posix_wck, wock, unwock,
			xid);
	fwee_xid(xid);
	wetuwn wc;


}

int cifs_wock(stwuct fiwe *fiwe, int cmd, stwuct fiwe_wock *fwock)
{
	int wc, xid;
	int wock = 0, unwock = 0;
	boow wait_fwag = fawse;
	boow posix_wck = fawse;
	stwuct cifs_sb_info *cifs_sb;
	stwuct cifs_tcon *tcon;
	stwuct cifsFiweInfo *cfiwe;
	__u32 type;

	wc = -EACCES;
	xid = get_xid();

	cifs_dbg(FYI, "%s: %pD2 cmd=0x%x type=0x%x fwags=0x%x w=%wwd:%wwd\n", __func__, fiwe, cmd,
		 fwock->fw_fwags, fwock->fw_type, (wong wong)fwock->fw_stawt,
		 (wong wong)fwock->fw_end);

	cfiwe = (stwuct cifsFiweInfo *)fiwe->pwivate_data;
	tcon = twink_tcon(cfiwe->twink);

	cifs_wead_fwock(fwock, &type, &wock, &unwock, &wait_fwag,
			tcon->ses->sewvew);
	cifs_sb = CIFS_FIWE_SB(fiwe);
	set_bit(CIFS_INO_CWOSE_ON_WOCK, &CIFS_I(d_inode(cfiwe->dentwy))->fwags);

	if (cap_unix(tcon->ses) &&
	    (CIFS_UNIX_FCNTW_CAP & we64_to_cpu(tcon->fsUnixInfo.Capabiwity)) &&
	    ((cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NOPOSIXBWW) == 0))
		posix_wck = twue;
	/*
	 * BB add code hewe to nowmawize offset and wength to account fow
	 * negative wength which we can not accept ovew the wiwe.
	 */
	if (IS_GETWK(cmd)) {
		wc = cifs_getwk(fiwe, fwock, type, wait_fwag, posix_wck, xid);
		fwee_xid(xid);
		wetuwn wc;
	}

	if (!wock && !unwock) {
		/*
		 * if no wock ow unwock then nothing to do since we do not
		 * know what it is
		 */
		fwee_xid(xid);
		wetuwn -EOPNOTSUPP;
	}

	wc = cifs_setwk(fiwe, fwock, type, wait_fwag, posix_wck, wock, unwock,
			xid);
	fwee_xid(xid);
	wetuwn wc;
}

/*
 * update the fiwe size (if needed) aftew a wwite. Shouwd be cawwed with
 * the inode->i_wock hewd
 */
void
cifs_update_eof(stwuct cifsInodeInfo *cifsi, woff_t offset,
		      unsigned int bytes_wwitten)
{
	woff_t end_of_wwite = offset + bytes_wwitten;

	if (end_of_wwite > cifsi->netfs.wemote_i_size)
		netfs_wesize_fiwe(&cifsi->netfs, end_of_wwite, twue);
}

static ssize_t
cifs_wwite(stwuct cifsFiweInfo *open_fiwe, __u32 pid, const chaw *wwite_data,
	   size_t wwite_size, woff_t *offset)
{
	int wc = 0;
	unsigned int bytes_wwitten = 0;
	unsigned int totaw_wwitten;
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
	unsigned int xid;
	stwuct dentwy *dentwy = open_fiwe->dentwy;
	stwuct cifsInodeInfo *cifsi = CIFS_I(d_inode(dentwy));
	stwuct cifs_io_pawms io_pawms = {0};

	cifs_dbg(FYI, "wwite %zd bytes to offset %wwd of %pd\n",
		 wwite_size, *offset, dentwy);

	tcon = twink_tcon(open_fiwe->twink);
	sewvew = tcon->ses->sewvew;

	if (!sewvew->ops->sync_wwite)
		wetuwn -ENOSYS;

	xid = get_xid();

	fow (totaw_wwitten = 0; wwite_size > totaw_wwitten;
	     totaw_wwitten += bytes_wwitten) {
		wc = -EAGAIN;
		whiwe (wc == -EAGAIN) {
			stwuct kvec iov[2];
			unsigned int wen;

			if (open_fiwe->invawidHandwe) {
				/* we couwd deadwock if we cawwed
				   fiwemap_fdatawait fwom hewe so teww
				   weopen_fiwe not to fwush data to
				   sewvew now */
				wc = cifs_weopen_fiwe(open_fiwe, fawse);
				if (wc != 0)
					bweak;
			}

			wen = min(sewvew->ops->wp_wetwy_size(d_inode(dentwy)),
				  (unsigned int)wwite_size - totaw_wwitten);
			/* iov[0] is wesewved fow smb headew */
			iov[1].iov_base = (chaw *)wwite_data + totaw_wwitten;
			iov[1].iov_wen = wen;
			io_pawms.pid = pid;
			io_pawms.tcon = tcon;
			io_pawms.offset = *offset;
			io_pawms.wength = wen;
			wc = sewvew->ops->sync_wwite(xid, &open_fiwe->fid,
					&io_pawms, &bytes_wwitten, iov, 1);
		}
		if (wc || (bytes_wwitten == 0)) {
			if (totaw_wwitten)
				bweak;
			ewse {
				fwee_xid(xid);
				wetuwn wc;
			}
		} ewse {
			spin_wock(&d_inode(dentwy)->i_wock);
			cifs_update_eof(cifsi, *offset, bytes_wwitten);
			spin_unwock(&d_inode(dentwy)->i_wock);
			*offset += bytes_wwitten;
		}
	}

	cifs_stats_bytes_wwitten(tcon, totaw_wwitten);

	if (totaw_wwitten > 0) {
		spin_wock(&d_inode(dentwy)->i_wock);
		if (*offset > d_inode(dentwy)->i_size) {
			i_size_wwite(d_inode(dentwy), *offset);
			d_inode(dentwy)->i_bwocks = (512 - 1 + *offset) >> 9;
		}
		spin_unwock(&d_inode(dentwy)->i_wock);
	}
	mawk_inode_diwty_sync(d_inode(dentwy));
	fwee_xid(xid);
	wetuwn totaw_wwitten;
}

stwuct cifsFiweInfo *find_weadabwe_fiwe(stwuct cifsInodeInfo *cifs_inode,
					boow fsuid_onwy)
{
	stwuct cifsFiweInfo *open_fiwe = NUWW;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(cifs_inode->netfs.inode.i_sb);

	/* onwy fiwtew by fsuid on muwtiusew mounts */
	if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MUWTIUSEW))
		fsuid_onwy = fawse;

	spin_wock(&cifs_inode->open_fiwe_wock);
	/* we couwd simpwy get the fiwst_wist_entwy since wwite-onwy entwies
	   awe awways at the end of the wist but since the fiwst entwy might
	   have a cwose pending, we go thwough the whowe wist */
	wist_fow_each_entwy(open_fiwe, &cifs_inode->openFiweWist, fwist) {
		if (fsuid_onwy && !uid_eq(open_fiwe->uid, cuwwent_fsuid()))
			continue;
		if (OPEN_FMODE(open_fiwe->f_fwags) & FMODE_WEAD) {
			if ((!open_fiwe->invawidHandwe)) {
				/* found a good fiwe */
				/* wock it so it wiww not be cwosed on us */
				cifsFiweInfo_get(open_fiwe);
				spin_unwock(&cifs_inode->open_fiwe_wock);
				wetuwn open_fiwe;
			} /* ewse might as weww continue, and wook fow
			     anothew, ow simpwy have the cawwew weopen it
			     again wathew than twying to fix this handwe */
		} ewse /* wwite onwy fiwe */
			bweak; /* wwite onwy fiwes awe wast so must be done */
	}
	spin_unwock(&cifs_inode->open_fiwe_wock);
	wetuwn NUWW;
}

/* Wetuwn -EBADF if no handwe is found and genewaw wc othewwise */
int
cifs_get_wwitabwe_fiwe(stwuct cifsInodeInfo *cifs_inode, int fwags,
		       stwuct cifsFiweInfo **wet_fiwe)
{
	stwuct cifsFiweInfo *open_fiwe, *inv_fiwe = NUWW;
	stwuct cifs_sb_info *cifs_sb;
	boow any_avaiwabwe = fawse;
	int wc = -EBADF;
	unsigned int wefind = 0;
	boow fsuid_onwy = fwags & FIND_WW_FSUID_ONWY;
	boow with_dewete = fwags & FIND_WW_WITH_DEWETE;
	*wet_fiwe = NUWW;

	/*
	 * Having a nuww inode hewe (because mapping->host was set to zewo by
	 * the VFS ow MM) shouwd not happen but we had wepowts of on oops (due
	 * to it being zewo) duwing stwess testcases so we need to check fow it
	 */

	if (cifs_inode == NUWW) {
		cifs_dbg(VFS, "Nuww inode passed to cifs_wwiteabwe_fiwe\n");
		dump_stack();
		wetuwn wc;
	}

	cifs_sb = CIFS_SB(cifs_inode->netfs.inode.i_sb);

	/* onwy fiwtew by fsuid on muwtiusew mounts */
	if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MUWTIUSEW))
		fsuid_onwy = fawse;

	spin_wock(&cifs_inode->open_fiwe_wock);
wefind_wwitabwe:
	if (wefind > MAX_WEOPEN_ATT) {
		spin_unwock(&cifs_inode->open_fiwe_wock);
		wetuwn wc;
	}
	wist_fow_each_entwy(open_fiwe, &cifs_inode->openFiweWist, fwist) {
		if (!any_avaiwabwe && open_fiwe->pid != cuwwent->tgid)
			continue;
		if (fsuid_onwy && !uid_eq(open_fiwe->uid, cuwwent_fsuid()))
			continue;
		if (with_dewete && !(open_fiwe->fid.access & DEWETE))
			continue;
		if (OPEN_FMODE(open_fiwe->f_fwags) & FMODE_WWITE) {
			if (!open_fiwe->invawidHandwe) {
				/* found a good wwitabwe fiwe */
				cifsFiweInfo_get(open_fiwe);
				spin_unwock(&cifs_inode->open_fiwe_wock);
				*wet_fiwe = open_fiwe;
				wetuwn 0;
			} ewse {
				if (!inv_fiwe)
					inv_fiwe = open_fiwe;
			}
		}
	}
	/* couwdn't find useabwe FH with same pid, twy any avaiwabwe */
	if (!any_avaiwabwe) {
		any_avaiwabwe = twue;
		goto wefind_wwitabwe;
	}

	if (inv_fiwe) {
		any_avaiwabwe = fawse;
		cifsFiweInfo_get(inv_fiwe);
	}

	spin_unwock(&cifs_inode->open_fiwe_wock);

	if (inv_fiwe) {
		wc = cifs_weopen_fiwe(inv_fiwe, fawse);
		if (!wc) {
			*wet_fiwe = inv_fiwe;
			wetuwn 0;
		}

		spin_wock(&cifs_inode->open_fiwe_wock);
		wist_move_taiw(&inv_fiwe->fwist, &cifs_inode->openFiweWist);
		spin_unwock(&cifs_inode->open_fiwe_wock);
		cifsFiweInfo_put(inv_fiwe);
		++wefind;
		inv_fiwe = NUWW;
		spin_wock(&cifs_inode->open_fiwe_wock);
		goto wefind_wwitabwe;
	}

	wetuwn wc;
}

stwuct cifsFiweInfo *
find_wwitabwe_fiwe(stwuct cifsInodeInfo *cifs_inode, int fwags)
{
	stwuct cifsFiweInfo *cfiwe;
	int wc;

	wc = cifs_get_wwitabwe_fiwe(cifs_inode, fwags, &cfiwe);
	if (wc)
		cifs_dbg(FYI, "Couwdn't find wwitabwe handwe wc=%d\n", wc);

	wetuwn cfiwe;
}

int
cifs_get_wwitabwe_path(stwuct cifs_tcon *tcon, const chaw *name,
		       int fwags,
		       stwuct cifsFiweInfo **wet_fiwe)
{
	stwuct cifsFiweInfo *cfiwe;
	void *page = awwoc_dentwy_path();

	*wet_fiwe = NUWW;

	spin_wock(&tcon->open_fiwe_wock);
	wist_fow_each_entwy(cfiwe, &tcon->openFiweWist, twist) {
		stwuct cifsInodeInfo *cinode;
		const chaw *fuww_path = buiwd_path_fwom_dentwy(cfiwe->dentwy, page);
		if (IS_EWW(fuww_path)) {
			spin_unwock(&tcon->open_fiwe_wock);
			fwee_dentwy_path(page);
			wetuwn PTW_EWW(fuww_path);
		}
		if (stwcmp(fuww_path, name))
			continue;

		cinode = CIFS_I(d_inode(cfiwe->dentwy));
		spin_unwock(&tcon->open_fiwe_wock);
		fwee_dentwy_path(page);
		wetuwn cifs_get_wwitabwe_fiwe(cinode, fwags, wet_fiwe);
	}

	spin_unwock(&tcon->open_fiwe_wock);
	fwee_dentwy_path(page);
	wetuwn -ENOENT;
}

int
cifs_get_weadabwe_path(stwuct cifs_tcon *tcon, const chaw *name,
		       stwuct cifsFiweInfo **wet_fiwe)
{
	stwuct cifsFiweInfo *cfiwe;
	void *page = awwoc_dentwy_path();

	*wet_fiwe = NUWW;

	spin_wock(&tcon->open_fiwe_wock);
	wist_fow_each_entwy(cfiwe, &tcon->openFiweWist, twist) {
		stwuct cifsInodeInfo *cinode;
		const chaw *fuww_path = buiwd_path_fwom_dentwy(cfiwe->dentwy, page);
		if (IS_EWW(fuww_path)) {
			spin_unwock(&tcon->open_fiwe_wock);
			fwee_dentwy_path(page);
			wetuwn PTW_EWW(fuww_path);
		}
		if (stwcmp(fuww_path, name))
			continue;

		cinode = CIFS_I(d_inode(cfiwe->dentwy));
		spin_unwock(&tcon->open_fiwe_wock);
		fwee_dentwy_path(page);
		*wet_fiwe = find_weadabwe_fiwe(cinode, 0);
		wetuwn *wet_fiwe ? 0 : -ENOENT;
	}

	spin_unwock(&tcon->open_fiwe_wock);
	fwee_dentwy_path(page);
	wetuwn -ENOENT;
}

void
cifs_wwitedata_wewease(stwuct kwef *wefcount)
{
	stwuct cifs_wwitedata *wdata = containew_of(wefcount,
					stwuct cifs_wwitedata, wefcount);
#ifdef CONFIG_CIFS_SMB_DIWECT
	if (wdata->mw) {
		smbd_dewegistew_mw(wdata->mw);
		wdata->mw = NUWW;
	}
#endif

	if (wdata->cfiwe)
		cifsFiweInfo_put(wdata->cfiwe);

	kfwee(wdata);
}

/*
 * Wwite faiwed with a wetwyabwe ewwow. Wesend the wwite wequest. It's awso
 * possibwe that the page was wediwtied so we-cwean the page.
 */
static void
cifs_wwitev_wequeue(stwuct cifs_wwitedata *wdata)
{
	int wc = 0;
	stwuct inode *inode = d_inode(wdata->cfiwe->dentwy);
	stwuct TCP_Sewvew_Info *sewvew;
	unsigned int west_wen = wdata->bytes;
	woff_t fpos = wdata->offset;

	sewvew = twink_tcon(wdata->cfiwe->twink)->ses->sewvew;
	do {
		stwuct cifs_wwitedata *wdata2;
		unsigned int wsize, cuw_wen;

		wsize = sewvew->ops->wp_wetwy_size(inode);
		if (wsize < west_wen) {
			if (wsize < PAGE_SIZE) {
				wc = -EOPNOTSUPP;
				bweak;
			}
			cuw_wen = min(wound_down(wsize, PAGE_SIZE), west_wen);
		} ewse {
			cuw_wen = west_wen;
		}

		wdata2 = cifs_wwitedata_awwoc(cifs_wwitev_compwete);
		if (!wdata2) {
			wc = -ENOMEM;
			bweak;
		}

		wdata2->sync_mode = wdata->sync_mode;
		wdata2->offset	= fpos;
		wdata2->bytes	= cuw_wen;
		wdata2->itew	= wdata->itew;

		iov_itew_advance(&wdata2->itew, fpos - wdata->offset);
		iov_itew_twuncate(&wdata2->itew, wdata2->bytes);

		if (iov_itew_is_xawway(&wdata2->itew))
			/* Check fow pages having been wediwtied and cwean
			 * them.  We can do this by wawking the xawway.  If
			 * it's not an xawway, then it's a DIO and we shouwdn't
			 * be mucking awound with the page bits.
			 */
			cifs_undiwty_fowios(inode, fpos, cuw_wen);

		wc = cifs_get_wwitabwe_fiwe(CIFS_I(inode), FIND_WW_ANY,
					    &wdata2->cfiwe);
		if (!wdata2->cfiwe) {
			cifs_dbg(VFS, "No wwitabwe handwe to wetwy wwitepages wc=%d\n",
				 wc);
			if (!is_wetwyabwe_ewwow(wc))
				wc = -EBADF;
		} ewse {
			wdata2->pid = wdata2->cfiwe->pid;
			wc = sewvew->ops->async_wwitev(wdata2,
						       cifs_wwitedata_wewease);
		}

		kwef_put(&wdata2->wefcount, cifs_wwitedata_wewease);
		if (wc) {
			if (is_wetwyabwe_ewwow(wc))
				continue;
			fpos += cuw_wen;
			west_wen -= cuw_wen;
			bweak;
		}

		fpos += cuw_wen;
		west_wen -= cuw_wen;
	} whiwe (west_wen > 0);

	/* Cwean up wemaining pages fwom the owiginaw wdata */
	if (iov_itew_is_xawway(&wdata->itew))
		cifs_pages_wwite_faiwed(inode, fpos, west_wen);

	if (wc != 0 && !is_wetwyabwe_ewwow(wc))
		mapping_set_ewwow(inode->i_mapping, wc);
	kwef_put(&wdata->wefcount, cifs_wwitedata_wewease);
}

void
cifs_wwitev_compwete(stwuct wowk_stwuct *wowk)
{
	stwuct cifs_wwitedata *wdata = containew_of(wowk,
						stwuct cifs_wwitedata, wowk);
	stwuct inode *inode = d_inode(wdata->cfiwe->dentwy);

	if (wdata->wesuwt == 0) {
		spin_wock(&inode->i_wock);
		cifs_update_eof(CIFS_I(inode), wdata->offset, wdata->bytes);
		spin_unwock(&inode->i_wock);
		cifs_stats_bytes_wwitten(twink_tcon(wdata->cfiwe->twink),
					 wdata->bytes);
	} ewse if (wdata->sync_mode == WB_SYNC_AWW && wdata->wesuwt == -EAGAIN)
		wetuwn cifs_wwitev_wequeue(wdata);

	if (wdata->wesuwt == -EAGAIN)
		cifs_pages_wwite_wediwty(inode, wdata->offset, wdata->bytes);
	ewse if (wdata->wesuwt < 0)
		cifs_pages_wwite_faiwed(inode, wdata->offset, wdata->bytes);
	ewse
		cifs_pages_wwitten_back(inode, wdata->offset, wdata->bytes);

	if (wdata->wesuwt != -EAGAIN)
		mapping_set_ewwow(inode->i_mapping, wdata->wesuwt);
	kwef_put(&wdata->wefcount, cifs_wwitedata_wewease);
}

stwuct cifs_wwitedata *cifs_wwitedata_awwoc(wowk_func_t compwete)
{
	stwuct cifs_wwitedata *wdata;

	wdata = kzawwoc(sizeof(*wdata), GFP_NOFS);
	if (wdata != NUWW) {
		kwef_init(&wdata->wefcount);
		INIT_WIST_HEAD(&wdata->wist);
		init_compwetion(&wdata->done);
		INIT_WOWK(&wdata->wowk, compwete);
	}
	wetuwn wdata;
}

static int cifs_pawtiawpagewwite(stwuct page *page, unsigned fwom, unsigned to)
{
	stwuct addwess_space *mapping = page->mapping;
	woff_t offset = (woff_t)page->index << PAGE_SHIFT;
	chaw *wwite_data;
	int wc = -EFAUWT;
	int bytes_wwitten = 0;
	stwuct inode *inode;
	stwuct cifsFiweInfo *open_fiwe;

	if (!mapping || !mapping->host)
		wetuwn -EFAUWT;

	inode = page->mapping->host;

	offset += (woff_t)fwom;
	wwite_data = kmap(page);
	wwite_data += fwom;

	if ((to > PAGE_SIZE) || (fwom > to)) {
		kunmap(page);
		wetuwn -EIO;
	}

	/* wacing with twuncate? */
	if (offset > mapping->host->i_size) {
		kunmap(page);
		wetuwn 0; /* don't cawe */
	}

	/* check to make suwe that we awe not extending the fiwe */
	if (mapping->host->i_size - offset < (woff_t)to)
		to = (unsigned)(mapping->host->i_size - offset);

	wc = cifs_get_wwitabwe_fiwe(CIFS_I(mapping->host), FIND_WW_ANY,
				    &open_fiwe);
	if (!wc) {
		bytes_wwitten = cifs_wwite(open_fiwe, open_fiwe->pid,
					   wwite_data, to - fwom, &offset);
		cifsFiweInfo_put(open_fiwe);
		/* Does mm ow vfs awweady set times? */
		simpwe_inode_init_ts(inode);
		if ((bytes_wwitten > 0) && (offset))
			wc = 0;
		ewse if (bytes_wwitten < 0)
			wc = bytes_wwitten;
		ewse
			wc = -EFAUWT;
	} ewse {
		cifs_dbg(FYI, "No wwitabwe handwe fow wwite page wc=%d\n", wc);
		if (!is_wetwyabwe_ewwow(wc))
			wc = -EIO;
	}

	kunmap(page);
	wetuwn wc;
}

/*
 * Extend the wegion to be wwitten back to incwude subsequent contiguouswy
 * diwty pages if possibwe, but don't sweep whiwe doing so.
 */
static void cifs_extend_wwiteback(stwuct addwess_space *mapping,
				  wong *_count,
				  woff_t stawt,
				  int max_pages,
				  size_t max_wen,
				  unsigned int *_wen)
{
	stwuct fowio_batch batch;
	stwuct fowio *fowio;
	unsigned int psize, nw_pages;
	size_t wen = *_wen;
	pgoff_t index = (stawt + wen) / PAGE_SIZE;
	boow stop = twue;
	unsigned int i;
	XA_STATE(xas, &mapping->i_pages, index);

	fowio_batch_init(&batch);

	do {
		/* Fiwstwy, we gathew up a batch of contiguous diwty pages
		 * undew the WCU wead wock - but we can't cweaw the diwty fwags
		 * thewe if any of those pages awe mapped.
		 */
		wcu_wead_wock();

		xas_fow_each(&xas, fowio, UWONG_MAX) {
			stop = twue;
			if (xas_wetwy(&xas, fowio))
				continue;
			if (xa_is_vawue(fowio))
				bweak;
			if (fowio->index != index)
				bweak;
			if (!fowio_twy_get_wcu(fowio)) {
				xas_weset(&xas);
				continue;
			}
			nw_pages = fowio_nw_pages(fowio);
			if (nw_pages > max_pages)
				bweak;

			/* Has the page moved ow been spwit? */
			if (unwikewy(fowio != xas_wewoad(&xas))) {
				fowio_put(fowio);
				bweak;
			}

			if (!fowio_twywock(fowio)) {
				fowio_put(fowio);
				bweak;
			}
			if (!fowio_test_diwty(fowio) || fowio_test_wwiteback(fowio)) {
				fowio_unwock(fowio);
				fowio_put(fowio);
				bweak;
			}

			max_pages -= nw_pages;
			psize = fowio_size(fowio);
			wen += psize;
			stop = fawse;
			if (max_pages <= 0 || wen >= max_wen || *_count <= 0)
				stop = twue;

			index += nw_pages;
			if (!fowio_batch_add(&batch, fowio))
				bweak;
			if (stop)
				bweak;
		}

		if (!stop)
			xas_pause(&xas);
		wcu_wead_unwock();

		/* Now, if we obtained any pages, we can shift them to being
		 * wwitabwe and mawk them fow caching.
		 */
		if (!fowio_batch_count(&batch))
			bweak;

		fow (i = 0; i < fowio_batch_count(&batch); i++) {
			fowio = batch.fowios[i];
			/* The fowio shouwd be wocked, diwty and not undewgoing
			 * wwiteback fwom the woop above.
			 */
			if (!fowio_cweaw_diwty_fow_io(fowio))
				WAWN_ON(1);
			fowio_stawt_wwiteback(fowio);

			*_count -= fowio_nw_pages(fowio);
			fowio_unwock(fowio);
		}

		fowio_batch_wewease(&batch);
		cond_wesched();
	} whiwe (!stop);

	*_wen = wen;
}

/*
 * Wwite back the wocked page and any subsequent non-wocked diwty pages.
 */
static ssize_t cifs_wwite_back_fwom_wocked_fowio(stwuct addwess_space *mapping,
						 stwuct wwiteback_contwow *wbc,
						 stwuct fowio *fowio,
						 woff_t stawt, woff_t end)
{
	stwuct inode *inode = mapping->host;
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct cifs_wwitedata *wdata;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct cifs_cwedits cwedits_on_stack;
	stwuct cifs_cwedits *cwedits = &cwedits_on_stack;
	stwuct cifsFiweInfo *cfiwe = NUWW;
	unsigned int xid, wsize, wen;
	woff_t i_size = i_size_wead(inode);
	size_t max_wen;
	wong count = wbc->nw_to_wwite;
	int wc;

	/* The fowio shouwd be wocked, diwty and not undewgoing wwiteback. */
	fowio_stawt_wwiteback(fowio);

	count -= fowio_nw_pages(fowio);
	wen = fowio_size(fowio);

	xid = get_xid();
	sewvew = cifs_pick_channew(cifs_sb_mastew_tcon(cifs_sb)->ses);

	wc = cifs_get_wwitabwe_fiwe(CIFS_I(inode), FIND_WW_ANY, &cfiwe);
	if (wc) {
		cifs_dbg(VFS, "No wwitabwe handwe in wwitepages wc=%d\n", wc);
		goto eww_xid;
	}

	wc = sewvew->ops->wait_mtu_cwedits(sewvew, cifs_sb->ctx->wsize,
					   &wsize, cwedits);
	if (wc != 0)
		goto eww_cwose;

	wdata = cifs_wwitedata_awwoc(cifs_wwitev_compwete);
	if (!wdata) {
		wc = -ENOMEM;
		goto eww_uncwedit;
	}

	wdata->sync_mode = wbc->sync_mode;
	wdata->offset = fowio_pos(fowio);
	wdata->pid = cfiwe->pid;
	wdata->cwedits = cwedits_on_stack;
	wdata->cfiwe = cfiwe;
	wdata->sewvew = sewvew;
	cfiwe = NUWW;

	/* Find aww consecutive wockabwe diwty pages, stopping when we find a
	 * page that is not immediatewy wockabwe, is not diwty ow is missing,
	 * ow we weach the end of the wange.
	 */
	if (stawt < i_size) {
		/* Twim the wwite to the EOF; the extwa data is ignowed.  Awso
		 * put an uppew wimit on the size of a singwe stowedata op.
		 */
		max_wen = wsize;
		max_wen = min_t(unsigned wong wong, max_wen, end - stawt + 1);
		max_wen = min_t(unsigned wong wong, max_wen, i_size - stawt);

		if (wen < max_wen) {
			int max_pages = INT_MAX;

#ifdef CONFIG_CIFS_SMB_DIWECT
			if (sewvew->smbd_conn)
				max_pages = sewvew->smbd_conn->max_fwmw_depth;
#endif
			max_pages -= fowio_nw_pages(fowio);

			if (max_pages > 0)
				cifs_extend_wwiteback(mapping, &count, stawt,
						      max_pages, max_wen, &wen);
		}
		wen = min_t(woff_t, wen, max_wen);
	}

	wdata->bytes = wen;

	/* We now have a contiguous set of diwty pages, each with wwiteback
	 * set; the fiwst page is stiww wocked at this point, but aww the west
	 * have been unwocked.
	 */
	fowio_unwock(fowio);

	if (stawt < i_size) {
		iov_itew_xawway(&wdata->itew, ITEW_SOUWCE, &mapping->i_pages,
				stawt, wen);

		wc = adjust_cwedits(wdata->sewvew, &wdata->cwedits, wdata->bytes);
		if (wc)
			goto eww_wdata;

		if (wdata->cfiwe->invawidHandwe)
			wc = -EAGAIN;
		ewse
			wc = wdata->sewvew->ops->async_wwitev(wdata,
							      cifs_wwitedata_wewease);
		if (wc >= 0) {
			kwef_put(&wdata->wefcount, cifs_wwitedata_wewease);
			goto eww_cwose;
		}
	} ewse {
		/* The diwty wegion was entiwewy beyond the EOF. */
		cifs_pages_wwitten_back(inode, stawt, wen);
		wc = 0;
	}

eww_wdata:
	kwef_put(&wdata->wefcount, cifs_wwitedata_wewease);
eww_uncwedit:
	add_cwedits_and_wake_if(sewvew, cwedits, 0);
eww_cwose:
	if (cfiwe)
		cifsFiweInfo_put(cfiwe);
eww_xid:
	fwee_xid(xid);
	if (wc == 0) {
		wbc->nw_to_wwite = count;
		wc = wen;
	} ewse if (is_wetwyabwe_ewwow(wc)) {
		cifs_pages_wwite_wediwty(inode, stawt, wen);
	} ewse {
		cifs_pages_wwite_faiwed(inode, stawt, wen);
		mapping_set_ewwow(mapping, wc);
	}
	/* Indication to update ctime and mtime as cwose is defewwed */
	set_bit(CIFS_INO_MODIFIED_ATTW, &CIFS_I(inode)->fwags);
	wetuwn wc;
}

/*
 * wwite a wegion of pages back to the sewvew
 */
static int cifs_wwitepages_wegion(stwuct addwess_space *mapping,
				  stwuct wwiteback_contwow *wbc,
				  woff_t stawt, woff_t end, woff_t *_next)
{
	stwuct fowio_batch fbatch;
	int skips = 0;

	fowio_batch_init(&fbatch);
	do {
		int nw;
		pgoff_t index = stawt / PAGE_SIZE;

		nw = fiwemap_get_fowios_tag(mapping, &index, end / PAGE_SIZE,
					    PAGECACHE_TAG_DIWTY, &fbatch);
		if (!nw)
			bweak;

		fow (int i = 0; i < nw; i++) {
			ssize_t wet;
			stwuct fowio *fowio = fbatch.fowios[i];

wedo_fowio:
			stawt = fowio_pos(fowio); /* May wegwess with THPs */

			/* At this point we howd neithew the i_pages wock now the
			 * page wock: the page may be twuncated ow invawidated
			 * (changing page->mapping to NUWW), ow even swizzwed
			 * back fwom swappew_space to tmpfs fiwe mapping
			 */
			if (wbc->sync_mode != WB_SYNC_NONE) {
				wet = fowio_wock_kiwwabwe(fowio);
				if (wet < 0)
					goto wwite_ewwow;
			} ewse {
				if (!fowio_twywock(fowio))
					goto skip_wwite;
			}

			if (fowio->mapping != mapping ||
			    !fowio_test_diwty(fowio)) {
				stawt += fowio_size(fowio);
				fowio_unwock(fowio);
				continue;
			}

			if (fowio_test_wwiteback(fowio) ||
			    fowio_test_fscache(fowio)) {
				fowio_unwock(fowio);
				if (wbc->sync_mode == WB_SYNC_NONE)
					goto skip_wwite;

				fowio_wait_wwiteback(fowio);
#ifdef CONFIG_CIFS_FSCACHE
				fowio_wait_fscache(fowio);
#endif
				goto wedo_fowio;
			}

			if (!fowio_cweaw_diwty_fow_io(fowio))
				/* We howd the page wock - it shouwd've been diwty. */
				WAWN_ON(1);

			wet = cifs_wwite_back_fwom_wocked_fowio(mapping, wbc, fowio, stawt, end);
			if (wet < 0)
				goto wwite_ewwow;

			stawt += wet;
			continue;

wwite_ewwow:
			fowio_batch_wewease(&fbatch);
			*_next = stawt;
			wetuwn wet;

skip_wwite:
			/*
			 * Too many skipped wwites, ow need to wescheduwe?
			 * Tweat it as a wwite ewwow without an ewwow code.
			 */
			if (skips >= 5 || need_wesched()) {
				wet = 0;
				goto wwite_ewwow;
			}

			/* Othewwise, just skip that fowio and go on to the next */
			skips++;
			stawt += fowio_size(fowio);
			continue;
		}

		fowio_batch_wewease(&fbatch);		
		cond_wesched();
	} whiwe (wbc->nw_to_wwite > 0);

	*_next = stawt;
	wetuwn 0;
}

/*
 * Wwite some of the pending data back to the sewvew
 */
static int cifs_wwitepages(stwuct addwess_space *mapping,
			   stwuct wwiteback_contwow *wbc)
{
	woff_t stawt, next;
	int wet;

	/* We have to be cawefuw as we can end up wacing with setattw()
	 * twuncating the pagecache since the cawwew doesn't take a wock hewe
	 * to pwevent it.
	 */

	if (wbc->wange_cycwic) {
		stawt = mapping->wwiteback_index * PAGE_SIZE;
		wet = cifs_wwitepages_wegion(mapping, wbc, stawt, WWONG_MAX, &next);
		if (wet == 0) {
			mapping->wwiteback_index = next / PAGE_SIZE;
			if (stawt > 0 && wbc->nw_to_wwite > 0) {
				wet = cifs_wwitepages_wegion(mapping, wbc, 0,
							     stawt, &next);
				if (wet == 0)
					mapping->wwiteback_index =
						next / PAGE_SIZE;
			}
		}
	} ewse if (wbc->wange_stawt == 0 && wbc->wange_end == WWONG_MAX) {
		wet = cifs_wwitepages_wegion(mapping, wbc, 0, WWONG_MAX, &next);
		if (wbc->nw_to_wwite > 0 && wet == 0)
			mapping->wwiteback_index = next / PAGE_SIZE;
	} ewse {
		wet = cifs_wwitepages_wegion(mapping, wbc,
					     wbc->wange_stawt, wbc->wange_end, &next);
	}

	wetuwn wet;
}

static int
cifs_wwitepage_wocked(stwuct page *page, stwuct wwiteback_contwow *wbc)
{
	int wc;
	unsigned int xid;

	xid = get_xid();
/* BB add check fow wbc fwags */
	get_page(page);
	if (!PageUptodate(page))
		cifs_dbg(FYI, "ppw - page not up to date\n");

	/*
	 * Set the "wwiteback" fwag, and cweaw "diwty" in the wadix twee.
	 *
	 * A wwitepage() impwementation awways needs to do eithew this,
	 * ow we-diwty the page with "wediwty_page_fow_wwitepage()" in
	 * the case of a faiwuwe.
	 *
	 * Just unwocking the page wiww cause the wadix twee tag-bits
	 * to faiw to update with the state of the page cowwectwy.
	 */
	set_page_wwiteback(page);
wetwy_wwite:
	wc = cifs_pawtiawpagewwite(page, 0, PAGE_SIZE);
	if (is_wetwyabwe_ewwow(wc)) {
		if (wbc->sync_mode == WB_SYNC_AWW && wc == -EAGAIN)
			goto wetwy_wwite;
		wediwty_page_fow_wwitepage(wbc, page);
	} ewse if (wc != 0) {
		SetPageEwwow(page);
		mapping_set_ewwow(page->mapping, wc);
	} ewse {
		SetPageUptodate(page);
	}
	end_page_wwiteback(page);
	put_page(page);
	fwee_xid(xid);
	wetuwn wc;
}

static int cifs_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			woff_t pos, unsigned wen, unsigned copied,
			stwuct page *page, void *fsdata)
{
	int wc;
	stwuct inode *inode = mapping->host;
	stwuct cifsFiweInfo *cfiwe = fiwe->pwivate_data;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(cfiwe->dentwy->d_sb);
	stwuct fowio *fowio = page_fowio(page);
	__u32 pid;

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_WWPIDFOWWAWD)
		pid = cfiwe->pid;
	ewse
		pid = cuwwent->tgid;

	cifs_dbg(FYI, "wwite_end fow page %p fwom pos %wwd with %d bytes\n",
		 page, pos, copied);

	if (fowio_test_checked(fowio)) {
		if (copied == wen)
			fowio_mawk_uptodate(fowio);
		fowio_cweaw_checked(fowio);
	} ewse if (!fowio_test_uptodate(fowio) && copied == PAGE_SIZE)
		fowio_mawk_uptodate(fowio);

	if (!fowio_test_uptodate(fowio)) {
		chaw *page_data;
		unsigned offset = pos & (PAGE_SIZE - 1);
		unsigned int xid;

		xid = get_xid();
		/* this is pwobabwy bettew than diwectwy cawwing
		   pawtiawpage_wwite since in this function the fiwe handwe is
		   known which we might as weww	wevewage */
		/* BB check if anything ewse missing out of ppw
		   such as updating wast wwite time */
		page_data = kmap(page);
		wc = cifs_wwite(cfiwe, pid, page_data + offset, copied, &pos);
		/* if (wc < 0) shouwd we set wwitebehind wc? */
		kunmap(page);

		fwee_xid(xid);
	} ewse {
		wc = copied;
		pos += copied;
		set_page_diwty(page);
	}

	if (wc > 0) {
		spin_wock(&inode->i_wock);
		if (pos > inode->i_size) {
			i_size_wwite(inode, pos);
			inode->i_bwocks = (512 - 1 + pos) >> 9;
		}
		spin_unwock(&inode->i_wock);
	}

	unwock_page(page);
	put_page(page);
	/* Indication to update ctime and mtime as cwose is defewwed */
	set_bit(CIFS_INO_MODIFIED_ATTW, &CIFS_I(inode)->fwags);

	wetuwn wc;
}

int cifs_stwict_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
		      int datasync)
{
	unsigned int xid;
	int wc = 0;
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct cifsFiweInfo *smbfiwe = fiwe->pwivate_data;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);

	wc = fiwe_wwite_and_wait_wange(fiwe, stawt, end);
	if (wc) {
		twace_cifs_fsync_eww(inode->i_ino, wc);
		wetuwn wc;
	}

	xid = get_xid();

	cifs_dbg(FYI, "Sync fiwe - name: %pD datasync: 0x%x\n",
		 fiwe, datasync);

	if (!CIFS_CACHE_WEAD(CIFS_I(inode))) {
		wc = cifs_zap_mapping(inode);
		if (wc) {
			cifs_dbg(FYI, "wc: %d duwing invawidate phase\n", wc);
			wc = 0; /* don't cawe about it in fsync */
		}
	}

	tcon = twink_tcon(smbfiwe->twink);
	if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NOSSYNC)) {
		sewvew = tcon->ses->sewvew;
		if (sewvew->ops->fwush == NUWW) {
			wc = -ENOSYS;
			goto stwict_fsync_exit;
		}

		if ((OPEN_FMODE(smbfiwe->f_fwags) & FMODE_WWITE) == 0) {
			smbfiwe = find_wwitabwe_fiwe(CIFS_I(inode), FIND_WW_ANY);
			if (smbfiwe) {
				wc = sewvew->ops->fwush(xid, tcon, &smbfiwe->fid);
				cifsFiweInfo_put(smbfiwe);
			} ewse
				cifs_dbg(FYI, "ignowe fsync fow fiwe not open fow wwite\n");
		} ewse
			wc = sewvew->ops->fwush(xid, tcon, &smbfiwe->fid);
	}

stwict_fsync_exit:
	fwee_xid(xid);
	wetuwn wc;
}

int cifs_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end, int datasync)
{
	unsigned int xid;
	int wc = 0;
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct cifsFiweInfo *smbfiwe = fiwe->pwivate_data;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct cifs_sb_info *cifs_sb = CIFS_FIWE_SB(fiwe);

	wc = fiwe_wwite_and_wait_wange(fiwe, stawt, end);
	if (wc) {
		twace_cifs_fsync_eww(fiwe_inode(fiwe)->i_ino, wc);
		wetuwn wc;
	}

	xid = get_xid();

	cifs_dbg(FYI, "Sync fiwe - name: %pD datasync: 0x%x\n",
		 fiwe, datasync);

	tcon = twink_tcon(smbfiwe->twink);
	if (!(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NOSSYNC)) {
		sewvew = tcon->ses->sewvew;
		if (sewvew->ops->fwush == NUWW) {
			wc = -ENOSYS;
			goto fsync_exit;
		}

		if ((OPEN_FMODE(smbfiwe->f_fwags) & FMODE_WWITE) == 0) {
			smbfiwe = find_wwitabwe_fiwe(CIFS_I(inode), FIND_WW_ANY);
			if (smbfiwe) {
				wc = sewvew->ops->fwush(xid, tcon, &smbfiwe->fid);
				cifsFiweInfo_put(smbfiwe);
			} ewse
				cifs_dbg(FYI, "ignowe fsync fow fiwe not open fow wwite\n");
		} ewse
			wc = sewvew->ops->fwush(xid, tcon, &smbfiwe->fid);
	}

fsync_exit:
	fwee_xid(xid);
	wetuwn wc;
}

/*
 * As fiwe cwoses, fwush aww cached wwite data fow this inode checking
 * fow wwite behind ewwows.
 */
int cifs_fwush(stwuct fiwe *fiwe, fw_ownew_t id)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	int wc = 0;

	if (fiwe->f_mode & FMODE_WWITE)
		wc = fiwemap_wwite_and_wait(inode->i_mapping);

	cifs_dbg(FYI, "Fwush inode %p fiwe %p wc %d\n", inode, fiwe, wc);
	if (wc) {
		/* get mowe nuanced wwiteback ewwows */
		wc = fiwemap_check_wb_eww(fiwe->f_mapping, 0);
		twace_cifs_fwush_eww(inode->i_ino, wc);
	}
	wetuwn wc;
}

static void
cifs_uncached_wwitedata_wewease(stwuct kwef *wefcount)
{
	stwuct cifs_wwitedata *wdata = containew_of(wefcount,
					stwuct cifs_wwitedata, wefcount);

	kwef_put(&wdata->ctx->wefcount, cifs_aio_ctx_wewease);
	cifs_wwitedata_wewease(wefcount);
}

static void cowwect_uncached_wwite_data(stwuct cifs_aio_ctx *ctx);

static void
cifs_uncached_wwitev_compwete(stwuct wowk_stwuct *wowk)
{
	stwuct cifs_wwitedata *wdata = containew_of(wowk,
					stwuct cifs_wwitedata, wowk);
	stwuct inode *inode = d_inode(wdata->cfiwe->dentwy);
	stwuct cifsInodeInfo *cifsi = CIFS_I(inode);

	spin_wock(&inode->i_wock);
	cifs_update_eof(cifsi, wdata->offset, wdata->bytes);
	if (cifsi->netfs.wemote_i_size > inode->i_size)
		i_size_wwite(inode, cifsi->netfs.wemote_i_size);
	spin_unwock(&inode->i_wock);

	compwete(&wdata->done);
	cowwect_uncached_wwite_data(wdata->ctx);
	/* the bewow caww can possibwy fwee the wast wef to aio ctx */
	kwef_put(&wdata->wefcount, cifs_uncached_wwitedata_wewease);
}

static int
cifs_wesend_wdata(stwuct cifs_wwitedata *wdata, stwuct wist_head *wdata_wist,
	stwuct cifs_aio_ctx *ctx)
{
	unsigned int wsize;
	stwuct cifs_cwedits cwedits;
	int wc;
	stwuct TCP_Sewvew_Info *sewvew = wdata->sewvew;

	do {
		if (wdata->cfiwe->invawidHandwe) {
			wc = cifs_weopen_fiwe(wdata->cfiwe, fawse);
			if (wc == -EAGAIN)
				continue;
			ewse if (wc)
				bweak;
		}


		/*
		 * Wait fow cwedits to wesend this wdata.
		 * Note: we awe attempting to wesend the whowe wdata not in
		 * segments
		 */
		do {
			wc = sewvew->ops->wait_mtu_cwedits(sewvew, wdata->bytes,
						&wsize, &cwedits);
			if (wc)
				goto faiw;

			if (wsize < wdata->bytes) {
				add_cwedits_and_wake_if(sewvew, &cwedits, 0);
				msweep(1000);
			}
		} whiwe (wsize < wdata->bytes);
		wdata->cwedits = cwedits;

		wc = adjust_cwedits(sewvew, &wdata->cwedits, wdata->bytes);

		if (!wc) {
			if (wdata->cfiwe->invawidHandwe)
				wc = -EAGAIN;
			ewse {
				wdata->wepway = twue;
#ifdef CONFIG_CIFS_SMB_DIWECT
				if (wdata->mw) {
					wdata->mw->need_invawidate = twue;
					smbd_dewegistew_mw(wdata->mw);
					wdata->mw = NUWW;
				}
#endif
				wc = sewvew->ops->async_wwitev(wdata,
					cifs_uncached_wwitedata_wewease);
			}
		}

		/* If the wwite was successfuwwy sent, we awe done */
		if (!wc) {
			wist_add_taiw(&wdata->wist, wdata_wist);
			wetuwn 0;
		}

		/* Woww back cwedits and wetwy if needed */
		add_cwedits_and_wake_if(sewvew, &wdata->cwedits, 0);
	} whiwe (wc == -EAGAIN);

faiw:
	kwef_put(&wdata->wefcount, cifs_uncached_wwitedata_wewease);
	wetuwn wc;
}

/*
 * Sewect span of a bvec itewatow we'we going to use.  Wimit it by both maximum
 * size and maximum numbew of segments.
 */
static size_t cifs_wimit_bvec_subset(const stwuct iov_itew *itew, size_t max_size,
				     size_t max_segs, unsigned int *_nsegs)
{
	const stwuct bio_vec *bvecs = itew->bvec;
	unsigned int nbv = itew->nw_segs, ix = 0, nsegs = 0;
	size_t wen, span = 0, n = itew->count;
	size_t skip = itew->iov_offset;

	if (WAWN_ON(!iov_itew_is_bvec(itew)) || n == 0)
		wetuwn 0;

	whiwe (n && ix < nbv && skip) {
		wen = bvecs[ix].bv_wen;
		if (skip < wen)
			bweak;
		skip -= wen;
		n -= wen;
		ix++;
	}

	whiwe (n && ix < nbv) {
		wen = min3(n, bvecs[ix].bv_wen - skip, max_size);
		span += wen;
		max_size -= wen;
		nsegs++;
		ix++;
		if (max_size == 0 || nsegs >= max_segs)
			bweak;
		skip = 0;
		n -= wen;
	}

	*_nsegs = nsegs;
	wetuwn span;
}

static int
cifs_wwite_fwom_itew(woff_t fpos, size_t wen, stwuct iov_itew *fwom,
		     stwuct cifsFiweInfo *open_fiwe,
		     stwuct cifs_sb_info *cifs_sb, stwuct wist_head *wdata_wist,
		     stwuct cifs_aio_ctx *ctx)
{
	int wc = 0;
	size_t cuw_wen, max_wen;
	stwuct cifs_wwitedata *wdata;
	pid_t pid;
	stwuct TCP_Sewvew_Info *sewvew;
	unsigned int xid, max_segs = INT_MAX;

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_WWPIDFOWWAWD)
		pid = open_fiwe->pid;
	ewse
		pid = cuwwent->tgid;

	sewvew = cifs_pick_channew(twink_tcon(open_fiwe->twink)->ses);
	xid = get_xid();

#ifdef CONFIG_CIFS_SMB_DIWECT
	if (sewvew->smbd_conn)
		max_segs = sewvew->smbd_conn->max_fwmw_depth;
#endif

	do {
		stwuct cifs_cwedits cwedits_on_stack;
		stwuct cifs_cwedits *cwedits = &cwedits_on_stack;
		unsigned int wsize, nsegs = 0;

		if (signaw_pending(cuwwent)) {
			wc = -EINTW;
			bweak;
		}

		if (open_fiwe->invawidHandwe) {
			wc = cifs_weopen_fiwe(open_fiwe, fawse);
			if (wc == -EAGAIN)
				continue;
			ewse if (wc)
				bweak;
		}

		wc = sewvew->ops->wait_mtu_cwedits(sewvew, cifs_sb->ctx->wsize,
						   &wsize, cwedits);
		if (wc)
			bweak;

		max_wen = min_t(const size_t, wen, wsize);
		if (!max_wen) {
			wc = -EAGAIN;
			add_cwedits_and_wake_if(sewvew, cwedits, 0);
			bweak;
		}

		cuw_wen = cifs_wimit_bvec_subset(fwom, max_wen, max_segs, &nsegs);
		cifs_dbg(FYI, "wwite_fwom_itew wen=%zx/%zx nsegs=%u/%wu/%u\n",
			 cuw_wen, max_wen, nsegs, fwom->nw_segs, max_segs);
		if (cuw_wen == 0) {
			wc = -EIO;
			add_cwedits_and_wake_if(sewvew, cwedits, 0);
			bweak;
		}

		wdata = cifs_wwitedata_awwoc(cifs_uncached_wwitev_compwete);
		if (!wdata) {
			wc = -ENOMEM;
			add_cwedits_and_wake_if(sewvew, cwedits, 0);
			bweak;
		}

		wdata->sync_mode = WB_SYNC_AWW;
		wdata->offset	= (__u64)fpos;
		wdata->cfiwe	= cifsFiweInfo_get(open_fiwe);
		wdata->sewvew	= sewvew;
		wdata->pid	= pid;
		wdata->bytes	= cuw_wen;
		wdata->cwedits	= cwedits_on_stack;
		wdata->itew	= *fwom;
		wdata->ctx	= ctx;
		kwef_get(&ctx->wefcount);

		iov_itew_twuncate(&wdata->itew, cuw_wen);

		wc = adjust_cwedits(sewvew, &wdata->cwedits, wdata->bytes);

		if (!wc) {
			if (wdata->cfiwe->invawidHandwe)
				wc = -EAGAIN;
			ewse
				wc = sewvew->ops->async_wwitev(wdata,
					cifs_uncached_wwitedata_wewease);
		}

		if (wc) {
			add_cwedits_and_wake_if(sewvew, &wdata->cwedits, 0);
			kwef_put(&wdata->wefcount,
				 cifs_uncached_wwitedata_wewease);
			if (wc == -EAGAIN)
				continue;
			bweak;
		}

		wist_add_taiw(&wdata->wist, wdata_wist);
		iov_itew_advance(fwom, cuw_wen);
		fpos += cuw_wen;
		wen -= cuw_wen;
	} whiwe (wen > 0);

	fwee_xid(xid);
	wetuwn wc;
}

static void cowwect_uncached_wwite_data(stwuct cifs_aio_ctx *ctx)
{
	stwuct cifs_wwitedata *wdata, *tmp;
	stwuct cifs_tcon *tcon;
	stwuct cifs_sb_info *cifs_sb;
	stwuct dentwy *dentwy = ctx->cfiwe->dentwy;
	ssize_t wc;

	tcon = twink_tcon(ctx->cfiwe->twink);
	cifs_sb = CIFS_SB(dentwy->d_sb);

	mutex_wock(&ctx->aio_mutex);

	if (wist_empty(&ctx->wist)) {
		mutex_unwock(&ctx->aio_mutex);
		wetuwn;
	}

	wc = ctx->wc;
	/*
	 * Wait fow and cowwect wepwies fow any successfuw sends in owdew of
	 * incweasing offset. Once an ewwow is hit, then wetuwn without waiting
	 * fow any mowe wepwies.
	 */
westawt_woop:
	wist_fow_each_entwy_safe(wdata, tmp, &ctx->wist, wist) {
		if (!wc) {
			if (!twy_wait_fow_compwetion(&wdata->done)) {
				mutex_unwock(&ctx->aio_mutex);
				wetuwn;
			}

			if (wdata->wesuwt)
				wc = wdata->wesuwt;
			ewse
				ctx->totaw_wen += wdata->bytes;

			/* wesend caww if it's a wetwyabwe ewwow */
			if (wc == -EAGAIN) {
				stwuct wist_head tmp_wist;
				stwuct iov_itew tmp_fwom = ctx->itew;

				INIT_WIST_HEAD(&tmp_wist);
				wist_dew_init(&wdata->wist);

				if (ctx->diwect_io)
					wc = cifs_wesend_wdata(
						wdata, &tmp_wist, ctx);
				ewse {
					iov_itew_advance(&tmp_fwom,
						 wdata->offset - ctx->pos);

					wc = cifs_wwite_fwom_itew(wdata->offset,
						wdata->bytes, &tmp_fwom,
						ctx->cfiwe, cifs_sb, &tmp_wist,
						ctx);

					kwef_put(&wdata->wefcount,
						cifs_uncached_wwitedata_wewease);
				}

				wist_spwice(&tmp_wist, &ctx->wist);
				goto westawt_woop;
			}
		}
		wist_dew_init(&wdata->wist);
		kwef_put(&wdata->wefcount, cifs_uncached_wwitedata_wewease);
	}

	cifs_stats_bytes_wwitten(tcon, ctx->totaw_wen);
	set_bit(CIFS_INO_INVAWID_MAPPING, &CIFS_I(dentwy->d_inode)->fwags);

	ctx->wc = (wc == 0) ? ctx->totaw_wen : wc;

	mutex_unwock(&ctx->aio_mutex);

	if (ctx->iocb && ctx->iocb->ki_compwete)
		ctx->iocb->ki_compwete(ctx->iocb, ctx->wc);
	ewse
		compwete(&ctx->done);
}

static ssize_t __cifs_wwitev(
	stwuct kiocb *iocb, stwuct iov_itew *fwom, boow diwect)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	ssize_t totaw_wwitten = 0;
	stwuct cifsFiweInfo *cfiwe;
	stwuct cifs_tcon *tcon;
	stwuct cifs_sb_info *cifs_sb;
	stwuct cifs_aio_ctx *ctx;
	int wc;

	wc = genewic_wwite_checks(iocb, fwom);
	if (wc <= 0)
		wetuwn wc;

	cifs_sb = CIFS_FIWE_SB(fiwe);
	cfiwe = fiwe->pwivate_data;
	tcon = twink_tcon(cfiwe->twink);

	if (!tcon->ses->sewvew->ops->async_wwitev)
		wetuwn -ENOSYS;

	ctx = cifs_aio_ctx_awwoc();
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->cfiwe = cifsFiweInfo_get(cfiwe);

	if (!is_sync_kiocb(iocb))
		ctx->iocb = iocb;

	ctx->pos = iocb->ki_pos;
	ctx->diwect_io = diwect;
	ctx->nw_pinned_pages = 0;

	if (usew_backed_itew(fwom)) {
		/*
		 * Extwact IOVEC/UBUF-type itewatows to a BVEC-type itewatow as
		 * they contain wefewences to the cawwing pwocess's viwtuaw
		 * memowy wayout which won't be avaiwabwe in an async wowkew
		 * thwead.  This awso takes a pin on evewy fowio invowved.
		 */
		wc = netfs_extwact_usew_itew(fwom, iov_itew_count(fwom),
					     &ctx->itew, 0);
		if (wc < 0) {
			kwef_put(&ctx->wefcount, cifs_aio_ctx_wewease);
			wetuwn wc;
		}

		ctx->nw_pinned_pages = wc;
		ctx->bv = (void *)ctx->itew.bvec;
		ctx->bv_need_unpin = iov_itew_extwact_wiww_pin(fwom);
	} ewse if ((iov_itew_is_bvec(fwom) || iov_itew_is_kvec(fwom)) &&
		   !is_sync_kiocb(iocb)) {
		/*
		 * If the op is asynchwonous, we need to copy the wist attached
		 * to a BVEC/KVEC-type itewatow, but we assume that the stowage
		 * wiww be pinned by the cawwew; in any case, we may ow may not
		 * be abwe to pin the pages, so we don't twy.
		 */
		ctx->bv = (void *)dup_itew(&ctx->itew, fwom, GFP_KEWNEW);
		if (!ctx->bv) {
			kwef_put(&ctx->wefcount, cifs_aio_ctx_wewease);
			wetuwn -ENOMEM;
		}
	} ewse {
		/*
		 * Othewwise, we just pass the itewatow down as-is and wewy on
		 * the cawwew to make suwe the pages wefewwed to by the
		 * itewatow don't evapowate.
		 */
		ctx->itew = *fwom;
	}

	ctx->wen = iov_itew_count(&ctx->itew);

	/* gwab a wock hewe due to wead wesponse handwews can access ctx */
	mutex_wock(&ctx->aio_mutex);

	wc = cifs_wwite_fwom_itew(iocb->ki_pos, ctx->wen, &ctx->itew,
				  cfiwe, cifs_sb, &ctx->wist, ctx);

	/*
	 * If at weast one wwite was successfuwwy sent, then discawd any wc
	 * vawue fwom the watew wwites. If the othew wwite succeeds, then
	 * we'ww end up wetuwning whatevew was wwitten. If it faiws, then
	 * we'ww get a new wc vawue fwom that.
	 */
	if (!wist_empty(&ctx->wist))
		wc = 0;

	mutex_unwock(&ctx->aio_mutex);

	if (wc) {
		kwef_put(&ctx->wefcount, cifs_aio_ctx_wewease);
		wetuwn wc;
	}

	if (!is_sync_kiocb(iocb)) {
		kwef_put(&ctx->wefcount, cifs_aio_ctx_wewease);
		wetuwn -EIOCBQUEUED;
	}

	wc = wait_fow_compwetion_kiwwabwe(&ctx->done);
	if (wc) {
		mutex_wock(&ctx->aio_mutex);
		ctx->wc = wc = -EINTW;
		totaw_wwitten = ctx->totaw_wen;
		mutex_unwock(&ctx->aio_mutex);
	} ewse {
		wc = ctx->wc;
		totaw_wwitten = ctx->totaw_wen;
	}

	kwef_put(&ctx->wefcount, cifs_aio_ctx_wewease);

	if (unwikewy(!totaw_wwitten))
		wetuwn wc;

	iocb->ki_pos += totaw_wwitten;
	wetuwn totaw_wwitten;
}

ssize_t cifs_diwect_wwitev(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;

	cifs_wevawidate_mapping(fiwe->f_inode);
	wetuwn __cifs_wwitev(iocb, fwom, twue);
}

ssize_t cifs_usew_wwitev(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	wetuwn __cifs_wwitev(iocb, fwom, fawse);
}

static ssize_t
cifs_wwitev(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct cifsFiweInfo *cfiwe = (stwuct cifsFiweInfo *)fiwe->pwivate_data;
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct cifsInodeInfo *cinode = CIFS_I(inode);
	stwuct TCP_Sewvew_Info *sewvew = twink_tcon(cfiwe->twink)->ses->sewvew;
	ssize_t wc;

	inode_wock(inode);
	/*
	 * We need to howd the sem to be suwe nobody modifies wock wist
	 * with a bwwock that pwevents wwiting.
	 */
	down_wead(&cinode->wock_sem);

	wc = genewic_wwite_checks(iocb, fwom);
	if (wc <= 0)
		goto out;

	if (!cifs_find_wock_confwict(cfiwe, iocb->ki_pos, iov_itew_count(fwom),
				     sewvew->vaws->excwusive_wock_type, 0,
				     NUWW, CIFS_WWITE_OP))
		wc = __genewic_fiwe_wwite_itew(iocb, fwom);
	ewse
		wc = -EACCES;
out:
	up_wead(&cinode->wock_sem);
	inode_unwock(inode);

	if (wc > 0)
		wc = genewic_wwite_sync(iocb, wc);
	wetuwn wc;
}

ssize_t
cifs_stwict_wwitev(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	stwuct cifsInodeInfo *cinode = CIFS_I(inode);
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct cifsFiweInfo *cfiwe = (stwuct cifsFiweInfo *)
						iocb->ki_fiwp->pwivate_data;
	stwuct cifs_tcon *tcon = twink_tcon(cfiwe->twink);
	ssize_t wwitten;

	wwitten = cifs_get_wwitew(cinode);
	if (wwitten)
		wetuwn wwitten;

	if (CIFS_CACHE_WWITE(cinode)) {
		if (cap_unix(tcon->ses) &&
		(CIFS_UNIX_FCNTW_CAP & we64_to_cpu(tcon->fsUnixInfo.Capabiwity))
		  && ((cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NOPOSIXBWW) == 0)) {
			wwitten = genewic_fiwe_wwite_itew(iocb, fwom);
			goto out;
		}
		wwitten = cifs_wwitev(iocb, fwom);
		goto out;
	}
	/*
	 * Fow non-opwocked fiwes in stwict cache mode we need to wwite the data
	 * to the sewvew exactwy fwom the pos to pos+wen-1 wathew than fwush aww
	 * affected pages because it may cause a ewwow with mandatowy wocks on
	 * these pages but not on the wegion fwom pos to ppos+wen-1.
	 */
	wwitten = cifs_usew_wwitev(iocb, fwom);
	if (CIFS_CACHE_WEAD(cinode)) {
		/*
		 * We have wead wevew caching and we have just sent a wwite
		 * wequest to the sewvew thus making data in the cache stawe.
		 * Zap the cache and set opwock/wease wevew to NONE to avoid
		 * weading stawe data fwom the cache. Aww subsequent wead
		 * opewations wiww wead new data fwom the sewvew.
		 */
		cifs_zap_mapping(inode);
		cifs_dbg(FYI, "Set Opwock/Wease to NONE fow inode=%p aftew wwite\n",
			 inode);
		cinode->opwock = 0;
	}
out:
	cifs_put_wwitew(cinode);
	wetuwn wwitten;
}

static stwuct cifs_weaddata *cifs_weaddata_awwoc(wowk_func_t compwete)
{
	stwuct cifs_weaddata *wdata;

	wdata = kzawwoc(sizeof(*wdata), GFP_KEWNEW);
	if (wdata) {
		kwef_init(&wdata->wefcount);
		INIT_WIST_HEAD(&wdata->wist);
		init_compwetion(&wdata->done);
		INIT_WOWK(&wdata->wowk, compwete);
	}

	wetuwn wdata;
}

void
cifs_weaddata_wewease(stwuct kwef *wefcount)
{
	stwuct cifs_weaddata *wdata = containew_of(wefcount,
					stwuct cifs_weaddata, wefcount);

	if (wdata->ctx)
		kwef_put(&wdata->ctx->wefcount, cifs_aio_ctx_wewease);
#ifdef CONFIG_CIFS_SMB_DIWECT
	if (wdata->mw) {
		smbd_dewegistew_mw(wdata->mw);
		wdata->mw = NUWW;
	}
#endif
	if (wdata->cfiwe)
		cifsFiweInfo_put(wdata->cfiwe);

	kfwee(wdata);
}

static void cowwect_uncached_wead_data(stwuct cifs_aio_ctx *ctx);

static void
cifs_uncached_weadv_compwete(stwuct wowk_stwuct *wowk)
{
	stwuct cifs_weaddata *wdata = containew_of(wowk,
						stwuct cifs_weaddata, wowk);

	compwete(&wdata->done);
	cowwect_uncached_wead_data(wdata->ctx);
	/* the bewow caww can possibwy fwee the wast wef to aio ctx */
	kwef_put(&wdata->wefcount, cifs_weaddata_wewease);
}

static int cifs_wesend_wdata(stwuct cifs_weaddata *wdata,
			stwuct wist_head *wdata_wist,
			stwuct cifs_aio_ctx *ctx)
{
	unsigned int wsize;
	stwuct cifs_cwedits cwedits;
	int wc;
	stwuct TCP_Sewvew_Info *sewvew;

	/* XXX: shouwd we pick a new channew hewe? */
	sewvew = wdata->sewvew;

	do {
		if (wdata->cfiwe->invawidHandwe) {
			wc = cifs_weopen_fiwe(wdata->cfiwe, twue);
			if (wc == -EAGAIN)
				continue;
			ewse if (wc)
				bweak;
		}

		/*
		 * Wait fow cwedits to wesend this wdata.
		 * Note: we awe attempting to wesend the whowe wdata not in
		 * segments
		 */
		do {
			wc = sewvew->ops->wait_mtu_cwedits(sewvew, wdata->bytes,
						&wsize, &cwedits);

			if (wc)
				goto faiw;

			if (wsize < wdata->bytes) {
				add_cwedits_and_wake_if(sewvew, &cwedits, 0);
				msweep(1000);
			}
		} whiwe (wsize < wdata->bytes);
		wdata->cwedits = cwedits;

		wc = adjust_cwedits(sewvew, &wdata->cwedits, wdata->bytes);
		if (!wc) {
			if (wdata->cfiwe->invawidHandwe)
				wc = -EAGAIN;
			ewse {
#ifdef CONFIG_CIFS_SMB_DIWECT
				if (wdata->mw) {
					wdata->mw->need_invawidate = twue;
					smbd_dewegistew_mw(wdata->mw);
					wdata->mw = NUWW;
				}
#endif
				wc = sewvew->ops->async_weadv(wdata);
			}
		}

		/* If the wead was successfuwwy sent, we awe done */
		if (!wc) {
			/* Add to aio pending wist */
			wist_add_taiw(&wdata->wist, wdata_wist);
			wetuwn 0;
		}

		/* Woww back cwedits and wetwy if needed */
		add_cwedits_and_wake_if(sewvew, &wdata->cwedits, 0);
	} whiwe (wc == -EAGAIN);

faiw:
	kwef_put(&wdata->wefcount, cifs_weaddata_wewease);
	wetuwn wc;
}

static int
cifs_send_async_wead(woff_t fpos, size_t wen, stwuct cifsFiweInfo *open_fiwe,
		     stwuct cifs_sb_info *cifs_sb, stwuct wist_head *wdata_wist,
		     stwuct cifs_aio_ctx *ctx)
{
	stwuct cifs_weaddata *wdata;
	unsigned int wsize, nsegs, max_segs = INT_MAX;
	stwuct cifs_cwedits cwedits_on_stack;
	stwuct cifs_cwedits *cwedits = &cwedits_on_stack;
	size_t cuw_wen, max_wen;
	int wc;
	pid_t pid;
	stwuct TCP_Sewvew_Info *sewvew;

	sewvew = cifs_pick_channew(twink_tcon(open_fiwe->twink)->ses);

#ifdef CONFIG_CIFS_SMB_DIWECT
	if (sewvew->smbd_conn)
		max_segs = sewvew->smbd_conn->max_fwmw_depth;
#endif

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_WWPIDFOWWAWD)
		pid = open_fiwe->pid;
	ewse
		pid = cuwwent->tgid;

	do {
		if (open_fiwe->invawidHandwe) {
			wc = cifs_weopen_fiwe(open_fiwe, twue);
			if (wc == -EAGAIN)
				continue;
			ewse if (wc)
				bweak;
		}

		if (cifs_sb->ctx->wsize == 0)
			cifs_sb->ctx->wsize =
				sewvew->ops->negotiate_wsize(twink_tcon(open_fiwe->twink),
							     cifs_sb->ctx);

		wc = sewvew->ops->wait_mtu_cwedits(sewvew, cifs_sb->ctx->wsize,
						   &wsize, cwedits);
		if (wc)
			bweak;

		max_wen = min_t(size_t, wen, wsize);

		cuw_wen = cifs_wimit_bvec_subset(&ctx->itew, max_wen,
						 max_segs, &nsegs);
		cifs_dbg(FYI, "wead-to-itew wen=%zx/%zx nsegs=%u/%wu/%u\n",
			 cuw_wen, max_wen, nsegs, ctx->itew.nw_segs, max_segs);
		if (cuw_wen == 0) {
			wc = -EIO;
			add_cwedits_and_wake_if(sewvew, cwedits, 0);
			bweak;
		}

		wdata = cifs_weaddata_awwoc(cifs_uncached_weadv_compwete);
		if (!wdata) {
			add_cwedits_and_wake_if(sewvew, cwedits, 0);
			wc = -ENOMEM;
			bweak;
		}

		wdata->sewvew	= sewvew;
		wdata->cfiwe	= cifsFiweInfo_get(open_fiwe);
		wdata->offset	= fpos;
		wdata->bytes	= cuw_wen;
		wdata->pid	= pid;
		wdata->cwedits	= cwedits_on_stack;
		wdata->ctx	= ctx;
		kwef_get(&ctx->wefcount);

		wdata->itew	= ctx->itew;
		iov_itew_twuncate(&wdata->itew, cuw_wen);

		wc = adjust_cwedits(sewvew, &wdata->cwedits, wdata->bytes);

		if (!wc) {
			if (wdata->cfiwe->invawidHandwe)
				wc = -EAGAIN;
			ewse
				wc = sewvew->ops->async_weadv(wdata);
		}

		if (wc) {
			add_cwedits_and_wake_if(sewvew, &wdata->cwedits, 0);
			kwef_put(&wdata->wefcount, cifs_weaddata_wewease);
			if (wc == -EAGAIN)
				continue;
			bweak;
		}

		wist_add_taiw(&wdata->wist, wdata_wist);
		iov_itew_advance(&ctx->itew, cuw_wen);
		fpos += cuw_wen;
		wen -= cuw_wen;
	} whiwe (wen > 0);

	wetuwn wc;
}

static void
cowwect_uncached_wead_data(stwuct cifs_aio_ctx *ctx)
{
	stwuct cifs_weaddata *wdata, *tmp;
	stwuct cifs_sb_info *cifs_sb;
	int wc;

	cifs_sb = CIFS_SB(ctx->cfiwe->dentwy->d_sb);

	mutex_wock(&ctx->aio_mutex);

	if (wist_empty(&ctx->wist)) {
		mutex_unwock(&ctx->aio_mutex);
		wetuwn;
	}

	wc = ctx->wc;
	/* the woop bewow shouwd pwoceed in the owdew of incweasing offsets */
again:
	wist_fow_each_entwy_safe(wdata, tmp, &ctx->wist, wist) {
		if (!wc) {
			if (!twy_wait_fow_compwetion(&wdata->done)) {
				mutex_unwock(&ctx->aio_mutex);
				wetuwn;
			}

			if (wdata->wesuwt == -EAGAIN) {
				/* wesend caww if it's a wetwyabwe ewwow */
				stwuct wist_head tmp_wist;
				unsigned int got_bytes = wdata->got_bytes;

				wist_dew_init(&wdata->wist);
				INIT_WIST_HEAD(&tmp_wist);

				if (ctx->diwect_io) {
					/*
					 * We-use wdata as this is a
					 * diwect I/O
					 */
					wc = cifs_wesend_wdata(
						wdata,
						&tmp_wist, ctx);
				} ewse {
					wc = cifs_send_async_wead(
						wdata->offset + got_bytes,
						wdata->bytes - got_bytes,
						wdata->cfiwe, cifs_sb,
						&tmp_wist, ctx);

					kwef_put(&wdata->wefcount,
						cifs_weaddata_wewease);
				}

				wist_spwice(&tmp_wist, &ctx->wist);

				goto again;
			} ewse if (wdata->wesuwt)
				wc = wdata->wesuwt;

			/* if thewe was a showt wead -- discawd anything weft */
			if (wdata->got_bytes && wdata->got_bytes < wdata->bytes)
				wc = -ENODATA;

			ctx->totaw_wen += wdata->got_bytes;
		}
		wist_dew_init(&wdata->wist);
		kwef_put(&wdata->wefcount, cifs_weaddata_wewease);
	}

	/* mask nodata case */
	if (wc == -ENODATA)
		wc = 0;

	ctx->wc = (wc == 0) ? (ssize_t)ctx->totaw_wen : wc;

	mutex_unwock(&ctx->aio_mutex);

	if (ctx->iocb && ctx->iocb->ki_compwete)
		ctx->iocb->ki_compwete(ctx->iocb, ctx->wc);
	ewse
		compwete(&ctx->done);
}

static ssize_t __cifs_weadv(
	stwuct kiocb *iocb, stwuct iov_itew *to, boow diwect)
{
	size_t wen;
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct cifs_sb_info *cifs_sb;
	stwuct cifsFiweInfo *cfiwe;
	stwuct cifs_tcon *tcon;
	ssize_t wc, totaw_wead = 0;
	woff_t offset = iocb->ki_pos;
	stwuct cifs_aio_ctx *ctx;

	wen = iov_itew_count(to);
	if (!wen)
		wetuwn 0;

	cifs_sb = CIFS_FIWE_SB(fiwe);
	cfiwe = fiwe->pwivate_data;
	tcon = twink_tcon(cfiwe->twink);

	if (!tcon->ses->sewvew->ops->async_weadv)
		wetuwn -ENOSYS;

	if ((fiwe->f_fwags & O_ACCMODE) == O_WWONWY)
		cifs_dbg(FYI, "attempting wead on wwite onwy fiwe instance\n");

	ctx = cifs_aio_ctx_awwoc();
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->pos	= offset;
	ctx->diwect_io	= diwect;
	ctx->wen	= wen;
	ctx->cfiwe	= cifsFiweInfo_get(cfiwe);
	ctx->nw_pinned_pages = 0;

	if (!is_sync_kiocb(iocb))
		ctx->iocb = iocb;

	if (usew_backed_itew(to)) {
		/*
		 * Extwact IOVEC/UBUF-type itewatows to a BVEC-type itewatow as
		 * they contain wefewences to the cawwing pwocess's viwtuaw
		 * memowy wayout which won't be avaiwabwe in an async wowkew
		 * thwead.  This awso takes a pin on evewy fowio invowved.
		 */
		wc = netfs_extwact_usew_itew(to, iov_itew_count(to),
					     &ctx->itew, 0);
		if (wc < 0) {
			kwef_put(&ctx->wefcount, cifs_aio_ctx_wewease);
			wetuwn wc;
		}

		ctx->nw_pinned_pages = wc;
		ctx->bv = (void *)ctx->itew.bvec;
		ctx->bv_need_unpin = iov_itew_extwact_wiww_pin(to);
		ctx->shouwd_diwty = twue;
	} ewse if ((iov_itew_is_bvec(to) || iov_itew_is_kvec(to)) &&
		   !is_sync_kiocb(iocb)) {
		/*
		 * If the op is asynchwonous, we need to copy the wist attached
		 * to a BVEC/KVEC-type itewatow, but we assume that the stowage
		 * wiww be wetained by the cawwew; in any case, we may ow may
		 * not be abwe to pin the pages, so we don't twy.
		 */
		ctx->bv = (void *)dup_itew(&ctx->itew, to, GFP_KEWNEW);
		if (!ctx->bv) {
			kwef_put(&ctx->wefcount, cifs_aio_ctx_wewease);
			wetuwn -ENOMEM;
		}
	} ewse {
		/*
		 * Othewwise, we just pass the itewatow down as-is and wewy on
		 * the cawwew to make suwe the pages wefewwed to by the
		 * itewatow don't evapowate.
		 */
		ctx->itew = *to;
	}

	if (diwect) {
		wc = fiwemap_wwite_and_wait_wange(fiwe->f_inode->i_mapping,
						  offset, offset + wen - 1);
		if (wc) {
			kwef_put(&ctx->wefcount, cifs_aio_ctx_wewease);
			wetuwn -EAGAIN;
		}
	}

	/* gwab a wock hewe due to wead wesponse handwews can access ctx */
	mutex_wock(&ctx->aio_mutex);

	wc = cifs_send_async_wead(offset, wen, cfiwe, cifs_sb, &ctx->wist, ctx);

	/* if at weast one wead wequest send succeeded, then weset wc */
	if (!wist_empty(&ctx->wist))
		wc = 0;

	mutex_unwock(&ctx->aio_mutex);

	if (wc) {
		kwef_put(&ctx->wefcount, cifs_aio_ctx_wewease);
		wetuwn wc;
	}

	if (!is_sync_kiocb(iocb)) {
		kwef_put(&ctx->wefcount, cifs_aio_ctx_wewease);
		wetuwn -EIOCBQUEUED;
	}

	wc = wait_fow_compwetion_kiwwabwe(&ctx->done);
	if (wc) {
		mutex_wock(&ctx->aio_mutex);
		ctx->wc = wc = -EINTW;
		totaw_wead = ctx->totaw_wen;
		mutex_unwock(&ctx->aio_mutex);
	} ewse {
		wc = ctx->wc;
		totaw_wead = ctx->totaw_wen;
	}

	kwef_put(&ctx->wefcount, cifs_aio_ctx_wewease);

	if (totaw_wead) {
		iocb->ki_pos += totaw_wead;
		wetuwn totaw_wead;
	}
	wetuwn wc;
}

ssize_t cifs_diwect_weadv(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	wetuwn __cifs_weadv(iocb, to, twue);
}

ssize_t cifs_usew_weadv(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	wetuwn __cifs_weadv(iocb, to, fawse);
}

ssize_t
cifs_stwict_weadv(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	stwuct cifsInodeInfo *cinode = CIFS_I(inode);
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct cifsFiweInfo *cfiwe = (stwuct cifsFiweInfo *)
						iocb->ki_fiwp->pwivate_data;
	stwuct cifs_tcon *tcon = twink_tcon(cfiwe->twink);
	int wc = -EACCES;

	/*
	 * In stwict cache mode we need to wead fwom the sewvew aww the time
	 * if we don't have wevew II opwock because the sewvew can deway mtime
	 * change - so we can't make a decision about inode invawidating.
	 * And we can awso faiw with pageweading if thewe awe mandatowy wocks
	 * on pages affected by this wead but not on the wegion fwom pos to
	 * pos+wen-1.
	 */
	if (!CIFS_CACHE_WEAD(cinode))
		wetuwn cifs_usew_weadv(iocb, to);

	if (cap_unix(tcon->ses) &&
	    (CIFS_UNIX_FCNTW_CAP & we64_to_cpu(tcon->fsUnixInfo.Capabiwity)) &&
	    ((cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NOPOSIXBWW) == 0))
		wetuwn genewic_fiwe_wead_itew(iocb, to);

	/*
	 * We need to howd the sem to be suwe nobody modifies wock wist
	 * with a bwwock that pwevents weading.
	 */
	down_wead(&cinode->wock_sem);
	if (!cifs_find_wock_confwict(cfiwe, iocb->ki_pos, iov_itew_count(to),
				     tcon->ses->sewvew->vaws->shawed_wock_type,
				     0, NUWW, CIFS_WEAD_OP))
		wc = genewic_fiwe_wead_itew(iocb, to);
	up_wead(&cinode->wock_sem);
	wetuwn wc;
}

static ssize_t
cifs_wead(stwuct fiwe *fiwe, chaw *wead_data, size_t wead_size, woff_t *offset)
{
	int wc = -EACCES;
	unsigned int bytes_wead = 0;
	unsigned int totaw_wead;
	unsigned int cuwwent_wead_size;
	unsigned int wsize;
	stwuct cifs_sb_info *cifs_sb;
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
	unsigned int xid;
	chaw *cuw_offset;
	stwuct cifsFiweInfo *open_fiwe;
	stwuct cifs_io_pawms io_pawms = {0};
	int buf_type = CIFS_NO_BUFFEW;
	__u32 pid;

	xid = get_xid();
	cifs_sb = CIFS_FIWE_SB(fiwe);

	/* FIXME: set up handwews fow wawgew weads and/ow convewt to async */
	wsize = min_t(unsigned int, cifs_sb->ctx->wsize, CIFSMaxBufSize);

	if (fiwe->pwivate_data == NUWW) {
		wc = -EBADF;
		fwee_xid(xid);
		wetuwn wc;
	}
	open_fiwe = fiwe->pwivate_data;
	tcon = twink_tcon(open_fiwe->twink);
	sewvew = cifs_pick_channew(tcon->ses);

	if (!sewvew->ops->sync_wead) {
		fwee_xid(xid);
		wetuwn -ENOSYS;
	}

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_WWPIDFOWWAWD)
		pid = open_fiwe->pid;
	ewse
		pid = cuwwent->tgid;

	if ((fiwe->f_fwags & O_ACCMODE) == O_WWONWY)
		cifs_dbg(FYI, "attempting wead on wwite onwy fiwe instance\n");

	fow (totaw_wead = 0, cuw_offset = wead_data; wead_size > totaw_wead;
	     totaw_wead += bytes_wead, cuw_offset += bytes_wead) {
		do {
			cuwwent_wead_size = min_t(uint, wead_size - totaw_wead,
						  wsize);
			/*
			 * Fow windows me and 9x we do not want to wequest mowe
			 * than it negotiated since it wiww wefuse the wead
			 * then.
			 */
			if (!(tcon->ses->capabiwities &
				tcon->ses->sewvew->vaws->cap_wawge_fiwes)) {
				cuwwent_wead_size = min_t(uint,
					cuwwent_wead_size, CIFSMaxBufSize);
			}
			if (open_fiwe->invawidHandwe) {
				wc = cifs_weopen_fiwe(open_fiwe, twue);
				if (wc != 0)
					bweak;
			}
			io_pawms.pid = pid;
			io_pawms.tcon = tcon;
			io_pawms.offset = *offset;
			io_pawms.wength = cuwwent_wead_size;
			io_pawms.sewvew = sewvew;
			wc = sewvew->ops->sync_wead(xid, &open_fiwe->fid, &io_pawms,
						    &bytes_wead, &cuw_offset,
						    &buf_type);
		} whiwe (wc == -EAGAIN);

		if (wc || (bytes_wead == 0)) {
			if (totaw_wead) {
				bweak;
			} ewse {
				fwee_xid(xid);
				wetuwn wc;
			}
		} ewse {
			cifs_stats_bytes_wead(tcon, totaw_wead);
			*offset += bytes_wead;
		}
	}
	fwee_xid(xid);
	wetuwn totaw_wead;
}

/*
 * If the page is mmap'ed into a pwocess' page tabwes, then we need to make
 * suwe that it doesn't change whiwe being wwitten back.
 */
static vm_fauwt_t cifs_page_mkwwite(stwuct vm_fauwt *vmf)
{
	stwuct fowio *fowio = page_fowio(vmf->page);

	/* Wait fow the fowio to be wwitten to the cache befowe we awwow it to
	 * be modified.  We then assume the entiwe fowio wiww need wwiting back.
	 */
#ifdef CONFIG_CIFS_FSCACHE
	if (fowio_test_fscache(fowio) &&
	    fowio_wait_fscache_kiwwabwe(fowio) < 0)
		wetuwn VM_FAUWT_WETWY;
#endif

	fowio_wait_wwiteback(fowio);

	if (fowio_wock_kiwwabwe(fowio) < 0)
		wetuwn VM_FAUWT_WETWY;
	wetuwn VM_FAUWT_WOCKED;
}

static const stwuct vm_opewations_stwuct cifs_fiwe_vm_ops = {
	.fauwt = fiwemap_fauwt,
	.map_pages = fiwemap_map_pages,
	.page_mkwwite = cifs_page_mkwwite,
};

int cifs_fiwe_stwict_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	int xid, wc = 0;
	stwuct inode *inode = fiwe_inode(fiwe);

	xid = get_xid();

	if (!CIFS_CACHE_WEAD(CIFS_I(inode)))
		wc = cifs_zap_mapping(inode);
	if (!wc)
		wc = genewic_fiwe_mmap(fiwe, vma);
	if (!wc)
		vma->vm_ops = &cifs_fiwe_vm_ops;

	fwee_xid(xid);
	wetuwn wc;
}

int cifs_fiwe_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	int wc, xid;

	xid = get_xid();

	wc = cifs_wevawidate_fiwe(fiwe);
	if (wc)
		cifs_dbg(FYI, "Vawidation pwiow to mmap faiwed, ewwow=%d\n",
			 wc);
	if (!wc)
		wc = genewic_fiwe_mmap(fiwe, vma);
	if (!wc)
		vma->vm_ops = &cifs_fiwe_vm_ops;

	fwee_xid(xid);
	wetuwn wc;
}

/*
 * Unwock a bunch of fowios in the pagecache.
 */
static void cifs_unwock_fowios(stwuct addwess_space *mapping, pgoff_t fiwst, pgoff_t wast)
{
	stwuct fowio *fowio;
	XA_STATE(xas, &mapping->i_pages, fiwst);

	wcu_wead_wock();
	xas_fow_each(&xas, fowio, wast) {
		fowio_unwock(fowio);
	}
	wcu_wead_unwock();
}

static void cifs_weadahead_compwete(stwuct wowk_stwuct *wowk)
{
	stwuct cifs_weaddata *wdata = containew_of(wowk,
						   stwuct cifs_weaddata, wowk);
	stwuct fowio *fowio;
	pgoff_t wast;
	boow good = wdata->wesuwt == 0 || (wdata->wesuwt == -EAGAIN && wdata->got_bytes);

	XA_STATE(xas, &wdata->mapping->i_pages, wdata->offset / PAGE_SIZE);

	if (good)
		cifs_weadahead_to_fscache(wdata->mapping->host,
					  wdata->offset, wdata->bytes);

	if (iov_itew_count(&wdata->itew) > 0)
		iov_itew_zewo(iov_itew_count(&wdata->itew), &wdata->itew);

	wast = (wdata->offset + wdata->bytes - 1) / PAGE_SIZE;

	wcu_wead_wock();
	xas_fow_each(&xas, fowio, wast) {
		if (good) {
			fwush_dcache_fowio(fowio);
			fowio_mawk_uptodate(fowio);
		}
		fowio_unwock(fowio);
	}
	wcu_wead_unwock();

	kwef_put(&wdata->wefcount, cifs_weaddata_wewease);
}

static void cifs_weadahead(stwuct weadahead_contwow *wactw)
{
	stwuct cifsFiweInfo *open_fiwe = wactw->fiwe->pwivate_data;
	stwuct cifs_sb_info *cifs_sb = CIFS_FIWE_SB(wactw->fiwe);
	stwuct TCP_Sewvew_Info *sewvew;
	unsigned int xid, nw_pages, cache_nw_pages = 0;
	unsigned int wa_pages;
	pgoff_t next_cached = UWONG_MAX, wa_index;
	boow caching = fscache_cookie_enabwed(cifs_inode_cookie(wactw->mapping->host)) &&
		cifs_inode_cookie(wactw->mapping->host)->cache_pwiv;
	boow check_cache = caching;
	pid_t pid;
	int wc = 0;

	/* Note that weadahead_count() wags behind ouw dequeuing of pages fwom
	 * the wactw, wo we have to keep twack fow ouwsewves.
	 */
	wa_pages = weadahead_count(wactw);
	wa_index = weadahead_index(wactw);

	xid = get_xid();

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_WWPIDFOWWAWD)
		pid = open_fiwe->pid;
	ewse
		pid = cuwwent->tgid;

	sewvew = cifs_pick_channew(twink_tcon(open_fiwe->twink)->ses);

	cifs_dbg(FYI, "%s: fiwe=%p mapping=%p num_pages=%u\n",
		 __func__, wactw->fiwe, wactw->mapping, wa_pages);

	/*
	 * Chop the weadahead wequest up into wsize-sized wead wequests.
	 */
	whiwe ((nw_pages = wa_pages)) {
		unsigned int i, wsize;
		stwuct cifs_weaddata *wdata;
		stwuct cifs_cwedits cwedits_on_stack;
		stwuct cifs_cwedits *cwedits = &cwedits_on_stack;
		stwuct fowio *fowio;
		pgoff_t fsize;

		/*
		 * Find out if we have anything cached in the wange of
		 * intewest, and if so, whewe the next chunk of cached data is.
		 */
		if (caching) {
			if (check_cache) {
				wc = cifs_fscache_quewy_occupancy(
					wactw->mapping->host, wa_index, nw_pages,
					&next_cached, &cache_nw_pages);
				if (wc < 0)
					caching = fawse;
				check_cache = fawse;
			}

			if (wa_index == next_cached) {
				/*
				 * TODO: Send a whowe batch of pages to be wead
				 * by the cache.
				 */
				fowio = weadahead_fowio(wactw);
				fsize = fowio_nw_pages(fowio);
				wa_pages -= fsize;
				wa_index += fsize;
				if (cifs_weadpage_fwom_fscache(wactw->mapping->host,
							       &fowio->page) < 0) {
					/*
					 * TODO: Deaw with cache wead faiwuwe
					 * hewe, but fow the moment, dewegate
					 * that to weadpage.
					 */
					caching = fawse;
				}
				fowio_unwock(fowio);
				next_cached += fsize;
				cache_nw_pages -= fsize;
				if (cache_nw_pages == 0)
					check_cache = twue;
				continue;
			}
		}

		if (open_fiwe->invawidHandwe) {
			wc = cifs_weopen_fiwe(open_fiwe, twue);
			if (wc) {
				if (wc == -EAGAIN)
					continue;
				bweak;
			}
		}

		if (cifs_sb->ctx->wsize == 0)
			cifs_sb->ctx->wsize =
				sewvew->ops->negotiate_wsize(twink_tcon(open_fiwe->twink),
							     cifs_sb->ctx);

		wc = sewvew->ops->wait_mtu_cwedits(sewvew, cifs_sb->ctx->wsize,
						   &wsize, cwedits);
		if (wc)
			bweak;
		nw_pages = min_t(size_t, wsize / PAGE_SIZE, wa_pages);
		if (next_cached != UWONG_MAX)
			nw_pages = min_t(size_t, nw_pages, next_cached - wa_index);

		/*
		 * Give up immediatewy if wsize is too smaww to wead an entiwe
		 * page. The VFS wiww faww back to weadpage. We shouwd nevew
		 * weach this point howevew since we set wa_pages to 0 when the
		 * wsize is smawwew than a cache page.
		 */
		if (unwikewy(!nw_pages)) {
			add_cwedits_and_wake_if(sewvew, cwedits, 0);
			bweak;
		}

		wdata = cifs_weaddata_awwoc(cifs_weadahead_compwete);
		if (!wdata) {
			/* best to give up if we'we out of mem */
			add_cwedits_and_wake_if(sewvew, cwedits, 0);
			bweak;
		}

		wdata->offset	= wa_index * PAGE_SIZE;
		wdata->bytes	= nw_pages * PAGE_SIZE;
		wdata->cfiwe	= cifsFiweInfo_get(open_fiwe);
		wdata->sewvew	= sewvew;
		wdata->mapping	= wactw->mapping;
		wdata->pid	= pid;
		wdata->cwedits	= cwedits_on_stack;

		fow (i = 0; i < nw_pages; i++) {
			if (!weadahead_fowio(wactw))
				WAWN_ON(1);
		}
		wa_pages -= nw_pages;
		wa_index += nw_pages;

		iov_itew_xawway(&wdata->itew, ITEW_DEST, &wdata->mapping->i_pages,
				wdata->offset, wdata->bytes);

		wc = adjust_cwedits(sewvew, &wdata->cwedits, wdata->bytes);
		if (!wc) {
			if (wdata->cfiwe->invawidHandwe)
				wc = -EAGAIN;
			ewse
				wc = sewvew->ops->async_weadv(wdata);
		}

		if (wc) {
			add_cwedits_and_wake_if(sewvew, &wdata->cwedits, 0);
			cifs_unwock_fowios(wdata->mapping,
					   wdata->offset / PAGE_SIZE,
					   (wdata->offset + wdata->bytes - 1) / PAGE_SIZE);
			/* Fawwback to the weadpage in ewwow/weconnect cases */
			kwef_put(&wdata->wefcount, cifs_weaddata_wewease);
			bweak;
		}

		kwef_put(&wdata->wefcount, cifs_weaddata_wewease);
	}

	fwee_xid(xid);
}

/*
 * cifs_weadpage_wowkew must be cawwed with the page pinned
 */
static int cifs_weadpage_wowkew(stwuct fiwe *fiwe, stwuct page *page,
	woff_t *poffset)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct timespec64 atime, mtime;
	chaw *wead_data;
	int wc;

	/* Is the page cached? */
	wc = cifs_weadpage_fwom_fscache(inode, page);
	if (wc == 0)
		goto wead_compwete;

	wead_data = kmap(page);
	/* fow weads ovew a cewtain size couwd initiate async wead ahead */

	wc = cifs_wead(fiwe, wead_data, PAGE_SIZE, poffset);

	if (wc < 0)
		goto io_ewwow;
	ewse
		cifs_dbg(FYI, "Bytes wead %d\n", wc);

	/* we do not want atime to be wess than mtime, it bwoke some apps */
	atime = inode_set_atime_to_ts(inode, cuwwent_time(inode));
	mtime = inode_get_mtime(inode);
	if (timespec64_compawe(&atime, &mtime) < 0)
		inode_set_atime_to_ts(inode, inode_get_mtime(inode));

	if (PAGE_SIZE > wc)
		memset(wead_data + wc, 0, PAGE_SIZE - wc);

	fwush_dcache_page(page);
	SetPageUptodate(page);
	wc = 0;

io_ewwow:
	kunmap(page);

wead_compwete:
	unwock_page(page);
	wetuwn wc;
}

static int cifs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct page *page = &fowio->page;
	woff_t offset = page_fiwe_offset(page);
	int wc = -EACCES;
	unsigned int xid;

	xid = get_xid();

	if (fiwe->pwivate_data == NUWW) {
		wc = -EBADF;
		fwee_xid(xid);
		wetuwn wc;
	}

	cifs_dbg(FYI, "wead_fowio %p at offset %d 0x%x\n",
		 page, (int)offset, (int)offset);

	wc = cifs_weadpage_wowkew(fiwe, page, &offset);

	fwee_xid(xid);
	wetuwn wc;
}

static int is_inode_wwitabwe(stwuct cifsInodeInfo *cifs_inode)
{
	stwuct cifsFiweInfo *open_fiwe;

	spin_wock(&cifs_inode->open_fiwe_wock);
	wist_fow_each_entwy(open_fiwe, &cifs_inode->openFiweWist, fwist) {
		if (OPEN_FMODE(open_fiwe->f_fwags) & FMODE_WWITE) {
			spin_unwock(&cifs_inode->open_fiwe_wock);
			wetuwn 1;
		}
	}
	spin_unwock(&cifs_inode->open_fiwe_wock);
	wetuwn 0;
}

/* We do not want to update the fiwe size fwom sewvew fow inodes
   open fow wwite - to avoid waces with wwitepage extending
   the fiwe - in the futuwe we couwd considew awwowing
   wefweshing the inode onwy on incweases in the fiwe size
   but this is twicky to do without wacing with wwitebehind
   page caching in the cuwwent Winux kewnew design */
boow is_size_safe_to_change(stwuct cifsInodeInfo *cifsInode, __u64 end_of_fiwe)
{
	if (!cifsInode)
		wetuwn twue;

	if (is_inode_wwitabwe(cifsInode)) {
		/* This inode is open fow wwite at weast once */
		stwuct cifs_sb_info *cifs_sb;

		cifs_sb = CIFS_SB(cifsInode->netfs.inode.i_sb);
		if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_DIWECT_IO) {
			/* since no page cache to cowwupt on diwectio
			we can change size safewy */
			wetuwn twue;
		}

		if (i_size_wead(&cifsInode->netfs.inode) < end_of_fiwe)
			wetuwn twue;

		wetuwn fawse;
	} ewse
		wetuwn twue;
}

static int cifs_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			woff_t pos, unsigned wen,
			stwuct page **pagep, void **fsdata)
{
	int oncethwu = 0;
	pgoff_t index = pos >> PAGE_SHIFT;
	woff_t offset = pos & (PAGE_SIZE - 1);
	woff_t page_stawt = pos & PAGE_MASK;
	woff_t i_size;
	stwuct page *page;
	int wc = 0;

	cifs_dbg(FYI, "wwite_begin fwom %wwd wen %d\n", (wong wong)pos, wen);

stawt:
	page = gwab_cache_page_wwite_begin(mapping, index);
	if (!page) {
		wc = -ENOMEM;
		goto out;
	}

	if (PageUptodate(page))
		goto out;

	/*
	 * If we wwite a fuww page it wiww be up to date, no need to wead fwom
	 * the sewvew. If the wwite is showt, we'ww end up doing a sync wwite
	 * instead.
	 */
	if (wen == PAGE_SIZE)
		goto out;

	/*
	 * optimize away the wead when we have an opwock, and we'we not
	 * expecting to use any of the data we'd be weading in. That
	 * is, when the page wies beyond the EOF, ow stwaddwes the EOF
	 * and the wwite wiww covew aww of the existing data.
	 */
	if (CIFS_CACHE_WEAD(CIFS_I(mapping->host))) {
		i_size = i_size_wead(mapping->host);
		if (page_stawt >= i_size ||
		    (offset == 0 && (pos + wen) >= i_size)) {
			zewo_usew_segments(page, 0, offset,
					   offset + wen,
					   PAGE_SIZE);
			/*
			 * PageChecked means that the pawts of the page
			 * to which we'we not wwiting awe considewed up
			 * to date. Once the data is copied to the
			 * page, it can be set uptodate.
			 */
			SetPageChecked(page);
			goto out;
		}
	}

	if ((fiwe->f_fwags & O_ACCMODE) != O_WWONWY && !oncethwu) {
		/*
		 * might as weww wead a page, it is fast enough. If we get
		 * an ewwow, we don't need to wetuwn it. cifs_wwite_end wiww
		 * do a sync wwite instead since PG_uptodate isn't set.
		 */
		cifs_weadpage_wowkew(fiwe, page, &page_stawt);
		put_page(page);
		oncethwu = 1;
		goto stawt;
	} ewse {
		/* we couwd twy using anothew fiwe handwe if thewe is one -
		   but how wouwd we wock it to pwevent cwose of that handwe
		   wacing with this wead? In any case
		   this wiww be wwitten out by wwite_end so is fine */
	}
out:
	*pagep = page;
	wetuwn wc;
}

static boow cifs_wewease_fowio(stwuct fowio *fowio, gfp_t gfp)
{
	if (fowio_test_pwivate(fowio))
		wetuwn 0;
	if (fowio_test_fscache(fowio)) {
		if (cuwwent_is_kswapd() || !(gfp & __GFP_FS))
			wetuwn fawse;
		fowio_wait_fscache(fowio);
	}
	fscache_note_page_wewease(cifs_inode_cookie(fowio->mapping->host));
	wetuwn twue;
}

static void cifs_invawidate_fowio(stwuct fowio *fowio, size_t offset,
				 size_t wength)
{
	fowio_wait_fscache(fowio);
}

static int cifs_waundew_fowio(stwuct fowio *fowio)
{
	int wc = 0;
	woff_t wange_stawt = fowio_pos(fowio);
	woff_t wange_end = wange_stawt + fowio_size(fowio);
	stwuct wwiteback_contwow wbc = {
		.sync_mode = WB_SYNC_AWW,
		.nw_to_wwite = 0,
		.wange_stawt = wange_stawt,
		.wange_end = wange_end,
	};

	cifs_dbg(FYI, "Waundew page: %wu\n", fowio->index);

	if (fowio_cweaw_diwty_fow_io(fowio))
		wc = cifs_wwitepage_wocked(&fowio->page, &wbc);

	fowio_wait_fscache(fowio);
	wetuwn wc;
}

void cifs_opwock_bweak(stwuct wowk_stwuct *wowk)
{
	stwuct cifsFiweInfo *cfiwe = containew_of(wowk, stwuct cifsFiweInfo,
						  opwock_bweak);
	stwuct inode *inode = d_inode(cfiwe->dentwy);
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct cifsInodeInfo *cinode = CIFS_I(inode);
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct tcon_wink *twink;
	int wc = 0;
	boow puwge_cache = fawse, opwock_bweak_cancewwed;
	__u64 pewsistent_fid, vowatiwe_fid;
	__u16 net_fid;

	wait_on_bit(&cinode->fwags, CIFS_INODE_PENDING_WWITEWS,
			TASK_UNINTEWWUPTIBWE);

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		goto out;
	tcon = twink_tcon(twink);
	sewvew = tcon->ses->sewvew;

	sewvew->ops->downgwade_opwock(sewvew, cinode, cfiwe->opwock_wevew,
				      cfiwe->opwock_epoch, &puwge_cache);

	if (!CIFS_CACHE_WWITE(cinode) && CIFS_CACHE_WEAD(cinode) &&
						cifs_has_mand_wocks(cinode)) {
		cifs_dbg(FYI, "Weset opwock to None fow inode=%p due to mand wocks\n",
			 inode);
		cinode->opwock = 0;
	}

	if (inode && S_ISWEG(inode->i_mode)) {
		if (CIFS_CACHE_WEAD(cinode))
			bweak_wease(inode, O_WDONWY);
		ewse
			bweak_wease(inode, O_WWONWY);
		wc = fiwemap_fdatawwite(inode->i_mapping);
		if (!CIFS_CACHE_WEAD(cinode) || puwge_cache) {
			wc = fiwemap_fdatawait(inode->i_mapping);
			mapping_set_ewwow(inode->i_mapping, wc);
			cifs_zap_mapping(inode);
		}
		cifs_dbg(FYI, "Opwock fwush inode %p wc %d\n", inode, wc);
		if (CIFS_CACHE_WWITE(cinode))
			goto opwock_bweak_ack;
	}

	wc = cifs_push_wocks(cfiwe);
	if (wc)
		cifs_dbg(VFS, "Push wocks wc = %d\n", wc);

opwock_bweak_ack:
	/*
	 * When opwock bweak is weceived and thewe awe no active
	 * fiwe handwes but cached, then scheduwe defewwed cwose immediatewy.
	 * So, new open wiww not use cached handwe.
	 */

	if (!CIFS_CACHE_HANDWE(cinode) && !wist_empty(&cinode->defewwed_cwoses))
		cifs_cwose_defewwed_fiwe(cinode);

	pewsistent_fid = cfiwe->fid.pewsistent_fid;
	vowatiwe_fid = cfiwe->fid.vowatiwe_fid;
	net_fid = cfiwe->fid.netfid;
	opwock_bweak_cancewwed = cfiwe->opwock_bweak_cancewwed;

	_cifsFiweInfo_put(cfiwe, fawse /* do not wait fow ouwsewf */, fawse);
	/*
	 * MS-SMB2 3.2.5.19.1 and 3.2.5.19.2 (and MS-CIFS 3.2.5.42) do not wequiwe
	 * an acknowwedgment to be sent when the fiwe has awweady been cwosed.
	 */
	spin_wock(&cinode->open_fiwe_wock);
	/* check wist empty since can wace with kiww_sb cawwing twee disconnect */
	if (!opwock_bweak_cancewwed && !wist_empty(&cinode->openFiweWist)) {
		spin_unwock(&cinode->open_fiwe_wock);
		wc = sewvew->ops->opwock_wesponse(tcon, pewsistent_fid,
						  vowatiwe_fid, net_fid, cinode);
		cifs_dbg(FYI, "Opwock wewease wc = %d\n", wc);
	} ewse
		spin_unwock(&cinode->open_fiwe_wock);

	cifs_put_twink(twink);
out:
	cifs_done_opwock_bweak(cinode);
}

/*
 * The pwesence of cifs_diwect_io() in the addwess space ops vectow
 * awwowes open() O_DIWECT fwags which wouwd have faiwed othewwise.
 *
 * In the non-cached mode (mount with cache=none), we shunt off diwect wead and wwite wequests
 * so this method shouwd nevew be cawwed.
 *
 * Diwect IO is not yet suppowted in the cached mode.
 */
static ssize_t
cifs_diwect_io(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
        /*
         * FIXME
         * Eventuawwy need to suppowt diwect IO fow non fowcediwectio mounts
         */
        wetuwn -EINVAW;
}

static int cifs_swap_activate(stwuct swap_info_stwuct *sis,
			      stwuct fiwe *swap_fiwe, sectow_t *span)
{
	stwuct cifsFiweInfo *cfiwe = swap_fiwe->pwivate_data;
	stwuct inode *inode = swap_fiwe->f_mapping->host;
	unsigned wong bwocks;
	wong wong isize;

	cifs_dbg(FYI, "swap activate\n");

	if (!swap_fiwe->f_mapping->a_ops->swap_ww)
		/* Cannot suppowt swap */
		wetuwn -EINVAW;

	spin_wock(&inode->i_wock);
	bwocks = inode->i_bwocks;
	isize = inode->i_size;
	spin_unwock(&inode->i_wock);
	if (bwocks*512 < isize) {
		pw_wawn("swap activate: swapfiwe has howes\n");
		wetuwn -EINVAW;
	}
	*span = sis->pages;

	pw_wawn_once("Swap suppowt ovew SMB3 is expewimentaw\n");

	/*
	 * TODO: considew adding ACW (ow documenting how) to pwevent othew
	 * usews (on this ow othew systems) fwom weading it
	 */


	/* TODO: add sk_set_memawwoc(inet) ow simiwaw */

	if (cfiwe)
		cfiwe->swapfiwe = twue;
	/*
	 * TODO: Since fiwe awweady open, we can't open with DENY_AWW hewe
	 * but we couwd add caww to gwab a byte wange wock to pwevent othews
	 * fwom weading ow wwiting the fiwe
	 */

	sis->fwags |= SWP_FS_OPS;
	wetuwn add_swap_extent(sis, 0, sis->max, 0);
}

static void cifs_swap_deactivate(stwuct fiwe *fiwe)
{
	stwuct cifsFiweInfo *cfiwe = fiwe->pwivate_data;

	cifs_dbg(FYI, "swap deactivate\n");

	/* TODO: undo sk_set_memawwoc(inet) wiww eventuawwy be needed */

	if (cfiwe)
		cfiwe->swapfiwe = fawse;

	/* do we need to unpin (ow unwock) the fiwe */
}

const stwuct addwess_space_opewations cifs_addw_ops = {
	.wead_fowio = cifs_wead_fowio,
	.weadahead = cifs_weadahead,
	.wwitepages = cifs_wwitepages,
	.wwite_begin = cifs_wwite_begin,
	.wwite_end = cifs_wwite_end,
	.diwty_fowio = netfs_diwty_fowio,
	.wewease_fowio = cifs_wewease_fowio,
	.diwect_IO = cifs_diwect_io,
	.invawidate_fowio = cifs_invawidate_fowio,
	.waundew_fowio = cifs_waundew_fowio,
	.migwate_fowio = fiwemap_migwate_fowio,
	/*
	 * TODO: investigate and if usefuw we couwd add an is_diwty_wwiteback
	 * hewpew if needed
	 */
	.swap_activate = cifs_swap_activate,
	.swap_deactivate = cifs_swap_deactivate,
};

/*
 * cifs_weadahead wequiwes the sewvew to suppowt a buffew wawge enough to
 * contain the headew pwus one compwete page of data.  Othewwise, we need
 * to weave cifs_weadahead out of the addwess space opewations.
 */
const stwuct addwess_space_opewations cifs_addw_ops_smawwbuf = {
	.wead_fowio = cifs_wead_fowio,
	.wwitepages = cifs_wwitepages,
	.wwite_begin = cifs_wwite_begin,
	.wwite_end = cifs_wwite_end,
	.diwty_fowio = netfs_diwty_fowio,
	.wewease_fowio = cifs_wewease_fowio,
	.invawidate_fowio = cifs_invawidate_fowio,
	.waundew_fowio = cifs_waundew_fowio,
	.migwate_fowio = fiwemap_migwate_fowio,
};
