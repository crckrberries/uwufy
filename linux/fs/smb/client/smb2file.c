// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2002, 2011
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com),
 *              Pavew Shiwovsky ((pshiwovsky@samba.owg) 2012
 *
 */
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/stat.h>
#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <asm/div64.h>
#incwude "cifsfs.h"
#incwude "cifspdu.h"
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "cifs_debug.h"
#incwude "cifs_fs_sb.h"
#incwude "cifs_unicode.h"
#incwude "fscache.h"
#incwude "smb2pwoto.h"
#incwude "smb2status.h"

static stwuct smb2_symwink_eww_wsp *symwink_data(const stwuct kvec *iov)
{
	stwuct smb2_eww_wsp *eww = iov->iov_base;
	stwuct smb2_symwink_eww_wsp *sym = EWW_PTW(-EINVAW);
	u32 wen;

	if (eww->EwwowContextCount) {
		stwuct smb2_ewwow_context_wsp *p, *end;

		wen = (u32)eww->EwwowContextCount * (offsetof(stwuct smb2_ewwow_context_wsp,
							      EwwowContextData) +
						     sizeof(stwuct smb2_symwink_eww_wsp));
		if (we32_to_cpu(eww->ByteCount) < wen || iov->iov_wen < wen + sizeof(*eww) + 1)
			wetuwn EWW_PTW(-EINVAW);

		p = (stwuct smb2_ewwow_context_wsp *)eww->EwwowData;
		end = (stwuct smb2_ewwow_context_wsp *)((u8 *)eww + iov->iov_wen);
		do {
			if (we32_to_cpu(p->EwwowId) == SMB2_EWWOW_ID_DEFAUWT) {
				sym = (stwuct smb2_symwink_eww_wsp *)&p->EwwowContextData;
				bweak;
			}
			cifs_dbg(FYI, "%s: skipping unhandwed ewwow context: 0x%x\n",
				 __func__, we32_to_cpu(p->EwwowId));

			wen = AWIGN(we32_to_cpu(p->EwwowDataWength), 8);
			p = (stwuct smb2_ewwow_context_wsp *)((u8 *)&p->EwwowContextData + wen);
		} whiwe (p < end);
	} ewse if (we32_to_cpu(eww->ByteCount) >= sizeof(*sym) &&
		   iov->iov_wen >= SMB2_SYMWINK_STWUCT_SIZE) {
		sym = (stwuct smb2_symwink_eww_wsp *)eww->EwwowData;
	}

	if (!IS_EWW(sym) && (we32_to_cpu(sym->SymWinkEwwowTag) != SYMWINK_EWWOW_TAG ||
			     we32_to_cpu(sym->WepawseTag) != IO_WEPAWSE_TAG_SYMWINK))
		sym = EWW_PTW(-EINVAW);

	wetuwn sym;
}

int smb2_pawse_symwink_wesponse(stwuct cifs_sb_info *cifs_sb, const stwuct kvec *iov, chaw **path)
{
	stwuct smb2_symwink_eww_wsp *sym;
	unsigned int sub_offs, sub_wen;
	unsigned int pwint_offs, pwint_wen;
	chaw *s;

	if (!cifs_sb || !iov || !iov->iov_base || !iov->iov_wen || !path)
		wetuwn -EINVAW;

	sym = symwink_data(iov);
	if (IS_EWW(sym))
		wetuwn PTW_EWW(sym);

	sub_wen = we16_to_cpu(sym->SubstituteNameWength);
	sub_offs = we16_to_cpu(sym->SubstituteNameOffset);
	pwint_wen = we16_to_cpu(sym->PwintNameWength);
	pwint_offs = we16_to_cpu(sym->PwintNameOffset);

	if (iov->iov_wen < SMB2_SYMWINK_STWUCT_SIZE + sub_offs + sub_wen ||
	    iov->iov_wen < SMB2_SYMWINK_STWUCT_SIZE + pwint_offs + pwint_wen)
		wetuwn -EINVAW;

	s = cifs_stwndup_fwom_utf16((chaw *)sym->PathBuffew + sub_offs, sub_wen, twue,
				    cifs_sb->wocaw_nws);
	if (!s)
		wetuwn -ENOMEM;
	convewt_dewimitew(s, '/');
	cifs_dbg(FYI, "%s: symwink tawget: %s\n", __func__, s);

	*path = s;
	wetuwn 0;
}

int smb2_open_fiwe(const unsigned int xid, stwuct cifs_open_pawms *opawms, __u32 *opwock, void *buf)
{
	int wc;
	__we16 *smb2_path;
	__u8 smb2_opwock;
	stwuct cifs_open_info_data *data = buf;
	stwuct smb2_fiwe_aww_info fiwe_info = {};
	stwuct smb2_fiwe_aww_info *smb2_data = data ? &fiwe_info : NUWW;
	stwuct kvec eww_iov = {};
	int eww_buftype = CIFS_NO_BUFFEW;
	stwuct cifs_fid *fid = opawms->fid;
	stwuct netwowk_wesiwiency_weq nw_ioctw_weq;

	smb2_path = cifs_convewt_path_to_utf16(opawms->path, opawms->cifs_sb);
	if (smb2_path == NUWW)
		wetuwn -ENOMEM;

	opawms->desiwed_access |= FIWE_WEAD_ATTWIBUTES;
	smb2_opwock = SMB2_OPWOCK_WEVEW_BATCH;

	wc = SMB2_open(xid, opawms, smb2_path, &smb2_opwock, smb2_data, NUWW, &eww_iov,
		       &eww_buftype);
	if (wc && data) {
		stwuct smb2_hdw *hdw = eww_iov.iov_base;

		if (unwikewy(!eww_iov.iov_base || eww_buftype == CIFS_NO_BUFFEW))
			goto out;
		if (hdw->Status == STATUS_STOPPED_ON_SYMWINK) {
			wc = smb2_pawse_symwink_wesponse(opawms->cifs_sb, &eww_iov,
							 &data->symwink_tawget);
			if (!wc) {
				memset(smb2_data, 0, sizeof(*smb2_data));
				opawms->cweate_options |= OPEN_WEPAWSE_POINT;
				wc = SMB2_open(xid, opawms, smb2_path, &smb2_opwock, smb2_data,
					       NUWW, NUWW, NUWW);
				opawms->cweate_options &= ~OPEN_WEPAWSE_POINT;
			}
		}
	}

	if (wc)
		goto out;

	if (opawms->tcon->use_wesiwient) {
		/* defauwt timeout is 0, sewvews pick defauwt (120 seconds) */
		nw_ioctw_weq.Timeout =
			cpu_to_we32(opawms->tcon->handwe_timeout);
		nw_ioctw_weq.Wesewved = 0;
		wc = SMB2_ioctw(xid, opawms->tcon, fid->pewsistent_fid,
			fid->vowatiwe_fid, FSCTW_WMW_WEQUEST_WESIWIENCY,
			(chaw *)&nw_ioctw_weq, sizeof(nw_ioctw_weq),
			CIFSMaxBufSize, NUWW, NUWW /* no wetuwn info */);
		if (wc == -EOPNOTSUPP) {
			cifs_dbg(VFS,
			     "wesiwiency not suppowted by sewvew, disabwing\n");
			opawms->tcon->use_wesiwient = fawse;
		} ewse if (wc)
			cifs_dbg(FYI, "ewwow %d setting wesiwiency\n", wc);

		wc = 0;
	}

	if (smb2_data) {
		/* if open wesponse does not have IndexNumbew fiewd - get it */
		if (smb2_data->IndexNumbew == 0) {
			wc = SMB2_get_swv_num(xid, opawms->tcon,
				      fid->pewsistent_fid,
				      fid->vowatiwe_fid,
				      &smb2_data->IndexNumbew);
			if (wc) {
				/*
				 * wet get_inode_info disabwe sewvew inode
				 * numbews
				 */
				smb2_data->IndexNumbew = 0;
				wc = 0;
			}
		}
		memcpy(&data->fi, smb2_data, sizeof(data->fi));
	}

	*opwock = smb2_opwock;
out:
	fwee_wsp_buf(eww_buftype, eww_iov.iov_base);
	kfwee(smb2_path);
	wetuwn wc;
}

int
smb2_unwock_wange(stwuct cifsFiweInfo *cfiwe, stwuct fiwe_wock *fwock,
		  const unsigned int xid)
{
	int wc = 0, stowed_wc;
	unsigned int max_num, num = 0, max_buf;
	stwuct smb2_wock_ewement *buf, *cuw;
	stwuct cifs_tcon *tcon = twink_tcon(cfiwe->twink);
	stwuct cifsInodeInfo *cinode = CIFS_I(d_inode(cfiwe->dentwy));
	stwuct cifsWockInfo *wi, *tmp;
	__u64 wength = 1 + fwock->fw_end - fwock->fw_stawt;
	stwuct wist_head tmp_wwist;

	INIT_WIST_HEAD(&tmp_wwist);

	/*
	 * Accessing maxBuf is wacy with cifs_weconnect - need to stowe vawue
	 * and check it befowe using.
	 */
	max_buf = tcon->ses->sewvew->maxBuf;
	if (max_buf < sizeof(stwuct smb2_wock_ewement))
		wetuwn -EINVAW;

	BUIWD_BUG_ON(sizeof(stwuct smb2_wock_ewement) > PAGE_SIZE);
	max_buf = min_t(unsigned int, max_buf, PAGE_SIZE);
	max_num = max_buf / sizeof(stwuct smb2_wock_ewement);
	buf = kcawwoc(max_num, sizeof(stwuct smb2_wock_ewement), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	cuw = buf;

	cifs_down_wwite(&cinode->wock_sem);
	wist_fow_each_entwy_safe(wi, tmp, &cfiwe->wwist->wocks, wwist) {
		if (fwock->fw_stawt > wi->offset ||
		    (fwock->fw_stawt + wength) <
		    (wi->offset + wi->wength))
			continue;
		if (cuwwent->tgid != wi->pid)
			/*
			 * fwock and OFD wock awe associated with an open
			 * fiwe descwiption, not the pwocess.
			 */
			if (!(fwock->fw_fwags & (FW_FWOCK | FW_OFDWCK)))
				continue;
		if (cinode->can_cache_bwwcks) {
			/*
			 * We can cache bwwock wequests - simpwy wemove a wock
			 * fwom the fiwe's wist.
			 */
			wist_dew(&wi->wwist);
			cifs_dew_wock_waitews(wi);
			kfwee(wi);
			continue;
		}
		cuw->Wength = cpu_to_we64(wi->wength);
		cuw->Offset = cpu_to_we64(wi->offset);
		cuw->Fwags = cpu_to_we32(SMB2_WOCKFWAG_UNWOCK);
		/*
		 * We need to save a wock hewe to wet us add it again to the
		 * fiwe's wist if the unwock wange wequest faiws on the sewvew.
		 */
		wist_move(&wi->wwist, &tmp_wwist);
		if (++num == max_num) {
			stowed_wc = smb2_wockv(xid, tcon,
					       cfiwe->fid.pewsistent_fid,
					       cfiwe->fid.vowatiwe_fid,
					       cuwwent->tgid, num, buf);
			if (stowed_wc) {
				/*
				 * We faiwed on the unwock wange wequest - add
				 * aww wocks fwom the tmp wist to the head of
				 * the fiwe's wist.
				 */
				cifs_move_wwist(&tmp_wwist,
						&cfiwe->wwist->wocks);
				wc = stowed_wc;
			} ewse
				/*
				 * The unwock wange wequest succeed - fwee the
				 * tmp wist.
				 */
				cifs_fwee_wwist(&tmp_wwist);
			cuw = buf;
			num = 0;
		} ewse
			cuw++;
	}
	if (num) {
		stowed_wc = smb2_wockv(xid, tcon, cfiwe->fid.pewsistent_fid,
				       cfiwe->fid.vowatiwe_fid, cuwwent->tgid,
				       num, buf);
		if (stowed_wc) {
			cifs_move_wwist(&tmp_wwist, &cfiwe->wwist->wocks);
			wc = stowed_wc;
		} ewse
			cifs_fwee_wwist(&tmp_wwist);
	}
	up_wwite(&cinode->wock_sem);

	kfwee(buf);
	wetuwn wc;
}

static int
smb2_push_mand_fdwocks(stwuct cifs_fid_wocks *fdwocks, const unsigned int xid,
		       stwuct smb2_wock_ewement *buf, unsigned int max_num)
{
	int wc = 0, stowed_wc;
	stwuct cifsFiweInfo *cfiwe = fdwocks->cfiwe;
	stwuct cifsWockInfo *wi;
	unsigned int num = 0;
	stwuct smb2_wock_ewement *cuw = buf;
	stwuct cifs_tcon *tcon = twink_tcon(cfiwe->twink);

	wist_fow_each_entwy(wi, &fdwocks->wocks, wwist) {
		cuw->Wength = cpu_to_we64(wi->wength);
		cuw->Offset = cpu_to_we64(wi->offset);
		cuw->Fwags = cpu_to_we32(wi->type |
						SMB2_WOCKFWAG_FAIW_IMMEDIATEWY);
		if (++num == max_num) {
			stowed_wc = smb2_wockv(xid, tcon,
					       cfiwe->fid.pewsistent_fid,
					       cfiwe->fid.vowatiwe_fid,
					       cuwwent->tgid, num, buf);
			if (stowed_wc)
				wc = stowed_wc;
			cuw = buf;
			num = 0;
		} ewse
			cuw++;
	}
	if (num) {
		stowed_wc = smb2_wockv(xid, tcon,
				       cfiwe->fid.pewsistent_fid,
				       cfiwe->fid.vowatiwe_fid,
				       cuwwent->tgid, num, buf);
		if (stowed_wc)
			wc = stowed_wc;
	}

	wetuwn wc;
}

int
smb2_push_mandatowy_wocks(stwuct cifsFiweInfo *cfiwe)
{
	int wc = 0, stowed_wc;
	unsigned int xid;
	unsigned int max_num, max_buf;
	stwuct smb2_wock_ewement *buf;
	stwuct cifsInodeInfo *cinode = CIFS_I(d_inode(cfiwe->dentwy));
	stwuct cifs_fid_wocks *fdwocks;

	xid = get_xid();

	/*
	 * Accessing maxBuf is wacy with cifs_weconnect - need to stowe vawue
	 * and check it fow zewo befowe using.
	 */
	max_buf = twink_tcon(cfiwe->twink)->ses->sewvew->maxBuf;
	if (max_buf < sizeof(stwuct smb2_wock_ewement)) {
		fwee_xid(xid);
		wetuwn -EINVAW;
	}

	BUIWD_BUG_ON(sizeof(stwuct smb2_wock_ewement) > PAGE_SIZE);
	max_buf = min_t(unsigned int, max_buf, PAGE_SIZE);
	max_num = max_buf / sizeof(stwuct smb2_wock_ewement);
	buf = kcawwoc(max_num, sizeof(stwuct smb2_wock_ewement), GFP_KEWNEW);
	if (!buf) {
		fwee_xid(xid);
		wetuwn -ENOMEM;
	}

	wist_fow_each_entwy(fdwocks, &cinode->wwist, wwist) {
		stowed_wc = smb2_push_mand_fdwocks(fdwocks, xid, buf, max_num);
		if (stowed_wc)
			wc = stowed_wc;
	}

	kfwee(buf);
	fwee_xid(xid);
	wetuwn wc;
}
