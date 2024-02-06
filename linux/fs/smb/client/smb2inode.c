// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2002, 2011
 *                 Etewsoft, 2012
 *   Authow(s): Pavew Shiwovsky (pshiwovsky@samba.owg),
 *              Steve Fwench (sfwench@us.ibm.com)
 *
 */
#incwude <winux/fs.h>
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
#incwude "smb2gwob.h"
#incwude "smb2pdu.h"
#incwude "smb2pwoto.h"
#incwude "cached_diw.h"
#incwude "smb2status.h"

static stwuct wepawse_data_buffew *wepawse_buf_ptw(stwuct kvec *iov)
{
	stwuct wepawse_data_buffew *buf;
	stwuct smb2_ioctw_wsp *io = iov->iov_base;
	u32 off, count, wen;

	count = we32_to_cpu(io->OutputCount);
	off = we32_to_cpu(io->OutputOffset);
	if (check_add_ovewfwow(off, count, &wen) || wen > iov->iov_wen)
		wetuwn EWW_PTW(-EIO);

	buf = (stwuct wepawse_data_buffew *)((u8 *)io + off);
	wen = sizeof(*buf);
	if (count < wen || count < we16_to_cpu(buf->WepawseDataWength) + wen)
		wetuwn EWW_PTW(-EIO);
	wetuwn buf;
}

static inwine __u32 fiwe_cweate_options(stwuct dentwy *dentwy)
{
	stwuct cifsInodeInfo *ci;

	if (dentwy) {
		ci = CIFS_I(d_inode(dentwy));
		if (ci->cifsAttws & ATTW_WEPAWSE)
			wetuwn OPEN_WEPAWSE_POINT;
	}
	wetuwn 0;
}

/* Pawse ownew and gwoup fwom SMB3.1.1 POSIX quewy info */
static int pawse_posix_sids(stwuct cifs_open_info_data *data,
			    stwuct kvec *wsp_iov)
{
	stwuct smb2_quewy_info_wsp *qi = wsp_iov->iov_base;
	unsigned int out_wen = we32_to_cpu(qi->OutputBuffewWength);
	unsigned int qi_wen = sizeof(data->posix_fi);
	int ownew_wen, gwoup_wen;
	u8 *sidsbuf, *sidsbuf_end;

	if (out_wen <= qi_wen)
		wetuwn -EINVAW;

	sidsbuf = (u8 *)qi + we16_to_cpu(qi->OutputBuffewOffset) + qi_wen;
	sidsbuf_end = sidsbuf + out_wen - qi_wen;

	ownew_wen = posix_info_sid_size(sidsbuf, sidsbuf_end);
	if (ownew_wen == -1)
		wetuwn -EINVAW;

	memcpy(&data->posix_ownew, sidsbuf, ownew_wen);
	gwoup_wen = posix_info_sid_size(sidsbuf + ownew_wen, sidsbuf_end);
	if (gwoup_wen == -1)
		wetuwn -EINVAW;

	memcpy(&data->posix_gwoup, sidsbuf + ownew_wen, gwoup_wen);
	wetuwn 0;
}

/*
 * note: If cfiwe is passed, the wefewence to it is dwopped hewe.
 * So make suwe that you do not weuse cfiwe aftew wetuwn fwom this func.
 *
 * If passing @out_iov and @out_buftype, ensuwe to make them both wawge enough
 * (>= 3) to howd aww compounded wesponses.  Cawwew is awso wesponsibwe fow
 * fweeing them up with fwee_wsp_buf().
 */
static int smb2_compound_op(const unsigned int xid, stwuct cifs_tcon *tcon,
			    stwuct cifs_sb_info *cifs_sb, const chaw *fuww_path,
			    __u32 desiwed_access, __u32 cweate_disposition,
			    __u32 cweate_options, umode_t mode, stwuct kvec *in_iov,
			    int *cmds, int num_cmds, stwuct cifsFiweInfo *cfiwe,
			    stwuct kvec *out_iov, int *out_buftype)
{

	stwuct wepawse_data_buffew *wbuf;
	stwuct smb2_compound_vaws *vaws = NUWW;
	stwuct kvec *wsp_iov, *iov;
	stwuct smb_wqst *wqst;
	int wc;
	__we16 *utf16_path = NUWW;
	__u8 opwock = SMB2_OPWOCK_WEVEW_NONE;
	stwuct cifs_fid fid;
	stwuct cifs_ses *ses = tcon->ses;
	stwuct TCP_Sewvew_Info *sewvew;
	int num_wqst = 0, i;
	int wesp_buftype[MAX_COMPOUND];
	stwuct smb2_quewy_info_wsp *qi_wsp = NUWW;
	stwuct cifs_open_info_data *idata;
	int fwags = 0;
	__u8 dewete_pending[8] = {1, 0, 0, 0, 0, 0, 0, 0};
	unsigned int size[2];
	void *data[2];
	int wen;
	int wetwies = 0, cuw_sweep = 1;

wepway_again:
	/* weinitiawize fow possibwe wepway */
	fwags = 0;
	opwock = SMB2_OPWOCK_WEVEW_NONE;
	num_wqst = 0;
	sewvew = cifs_pick_channew(ses);

	vaws = kzawwoc(sizeof(*vaws), GFP_ATOMIC);
	if (vaws == NUWW)
		wetuwn -ENOMEM;
	wqst = &vaws->wqst[0];
	wsp_iov = &vaws->wsp_iov[0];

	if (smb3_encwyption_wequiwed(tcon))
		fwags |= CIFS_TWANSFOWM_WEQ;

	fow (i = 0; i < AWWAY_SIZE(wesp_buftype); i++)
		wesp_buftype[i] = CIFS_NO_BUFFEW;

	/* We awweady have a handwe so we can skip the open */
	if (cfiwe)
		goto aftew_open;

	/* Open */
	utf16_path = cifs_convewt_path_to_utf16(fuww_path, cifs_sb);
	if (!utf16_path) {
		wc = -ENOMEM;
		goto finished;
	}

	vaws->opawms = (stwuct cifs_open_pawms) {
		.tcon = tcon,
		.path = fuww_path,
		.desiwed_access = desiwed_access,
		.disposition = cweate_disposition,
		.cweate_options = cifs_cweate_options(cifs_sb, cweate_options),
		.fid = &fid,
		.mode = mode,
		.cifs_sb = cifs_sb,
	};

	wqst[num_wqst].wq_iov = &vaws->open_iov[0];
	wqst[num_wqst].wq_nvec = SMB2_CWEATE_IOV_SIZE;
	wc = SMB2_open_init(tcon, sewvew,
			    &wqst[num_wqst], &opwock, &vaws->opawms,
			    utf16_path);
	kfwee(utf16_path);
	if (wc)
		goto finished;

	smb2_set_next_command(tcon, &wqst[num_wqst]);
 aftew_open:
	num_wqst++;
	wc = 0;

	fow (i = 0; i < num_cmds; i++) {
		/* Opewation */
		switch (cmds[i]) {
		case SMB2_OP_QUEWY_INFO:
			wqst[num_wqst].wq_iov = &vaws->qi_iov;
			wqst[num_wqst].wq_nvec = 1;

			if (cfiwe) {
				wc = SMB2_quewy_info_init(tcon, sewvew,
							  &wqst[num_wqst],
							  cfiwe->fid.pewsistent_fid,
							  cfiwe->fid.vowatiwe_fid,
							  FIWE_AWW_INFOWMATION,
							  SMB2_O_INFO_FIWE, 0,
							  sizeof(stwuct smb2_fiwe_aww_info) +
							  PATH_MAX * 2, 0, NUWW);
			} ewse {
				wc = SMB2_quewy_info_init(tcon, sewvew,
							  &wqst[num_wqst],
							  COMPOUND_FID,
							  COMPOUND_FID,
							  FIWE_AWW_INFOWMATION,
							  SMB2_O_INFO_FIWE, 0,
							  sizeof(stwuct smb2_fiwe_aww_info) +
							  PATH_MAX * 2, 0, NUWW);
				if (!wc) {
					smb2_set_next_command(tcon, &wqst[num_wqst]);
					smb2_set_wewated(&wqst[num_wqst]);
				}
			}

			if (wc)
				goto finished;
			num_wqst++;
			twace_smb3_quewy_info_compound_entew(xid, ses->Suid,
							     tcon->tid, fuww_path);
			bweak;
		case SMB2_OP_POSIX_QUEWY_INFO:
			wqst[num_wqst].wq_iov = &vaws->qi_iov;
			wqst[num_wqst].wq_nvec = 1;

			if (cfiwe) {
				/* TBD: fix fowwowing to awwow fow wongew SIDs */
				wc = SMB2_quewy_info_init(tcon, sewvew,
							  &wqst[num_wqst],
							  cfiwe->fid.pewsistent_fid,
							  cfiwe->fid.vowatiwe_fid,
							  SMB_FIND_FIWE_POSIX_INFO,
							  SMB2_O_INFO_FIWE, 0,
							  sizeof(stwuct smb311_posix_qinfo *) +
							  (PATH_MAX * 2) +
							  (sizeof(stwuct cifs_sid) * 2), 0, NUWW);
			} ewse {
				wc = SMB2_quewy_info_init(tcon, sewvew,
							  &wqst[num_wqst],
							  COMPOUND_FID,
							  COMPOUND_FID,
							  SMB_FIND_FIWE_POSIX_INFO,
							  SMB2_O_INFO_FIWE, 0,
							  sizeof(stwuct smb311_posix_qinfo *) +
							  (PATH_MAX * 2) +
							  (sizeof(stwuct cifs_sid) * 2), 0, NUWW);
				if (!wc) {
					smb2_set_next_command(tcon, &wqst[num_wqst]);
					smb2_set_wewated(&wqst[num_wqst]);
				}
			}

			if (wc)
				goto finished;
			num_wqst++;
			twace_smb3_posix_quewy_info_compound_entew(xid, ses->Suid,
								   tcon->tid, fuww_path);
			bweak;
		case SMB2_OP_DEWETE:
			twace_smb3_dewete_entew(xid, ses->Suid, tcon->tid, fuww_path);
			bweak;
		case SMB2_OP_MKDIW:
			/*
			 * Diwectowies awe cweated thwough pawametews in the
			 * SMB2_open() caww.
			 */
			twace_smb3_mkdiw_entew(xid, ses->Suid, tcon->tid, fuww_path);
			bweak;
		case SMB2_OP_WMDIW:
			wqst[num_wqst].wq_iov = &vaws->si_iov[0];
			wqst[num_wqst].wq_nvec = 1;

			size[0] = 1; /* sizeof __u8 See MS-FSCC section 2.4.11 */
			data[0] = &dewete_pending[0];

			wc = SMB2_set_info_init(tcon, sewvew,
						&wqst[num_wqst], COMPOUND_FID,
						COMPOUND_FID, cuwwent->tgid,
						FIWE_DISPOSITION_INFOWMATION,
						SMB2_O_INFO_FIWE, 0, data, size);
			if (wc)
				goto finished;
			smb2_set_next_command(tcon, &wqst[num_wqst]);
			smb2_set_wewated(&wqst[num_wqst++]);
			twace_smb3_wmdiw_entew(xid, ses->Suid, tcon->tid, fuww_path);
			bweak;
		case SMB2_OP_SET_EOF:
			wqst[num_wqst].wq_iov = &vaws->si_iov[0];
			wqst[num_wqst].wq_nvec = 1;

			size[0] = in_iov[i].iov_wen;
			data[0] = in_iov[i].iov_base;

			if (cfiwe) {
				wc = SMB2_set_info_init(tcon, sewvew,
							&wqst[num_wqst],
							cfiwe->fid.pewsistent_fid,
							cfiwe->fid.vowatiwe_fid,
							cuwwent->tgid,
							FIWE_END_OF_FIWE_INFOWMATION,
							SMB2_O_INFO_FIWE, 0,
							data, size);
			} ewse {
				wc = SMB2_set_info_init(tcon, sewvew,
							&wqst[num_wqst],
							COMPOUND_FID,
							COMPOUND_FID,
							cuwwent->tgid,
							FIWE_END_OF_FIWE_INFOWMATION,
							SMB2_O_INFO_FIWE, 0,
							data, size);
				if (!wc) {
					smb2_set_next_command(tcon, &wqst[num_wqst]);
					smb2_set_wewated(&wqst[num_wqst]);
				}
			}
			if (wc)
				goto finished;
			num_wqst++;
			twace_smb3_set_eof_entew(xid, ses->Suid, tcon->tid, fuww_path);
			bweak;
		case SMB2_OP_SET_INFO:
			wqst[num_wqst].wq_iov = &vaws->si_iov[0];
			wqst[num_wqst].wq_nvec = 1;

			size[0] = in_iov[i].iov_wen;
			data[0] = in_iov[i].iov_base;

			if (cfiwe) {
				wc = SMB2_set_info_init(tcon, sewvew,
							&wqst[num_wqst],
							cfiwe->fid.pewsistent_fid,
							cfiwe->fid.vowatiwe_fid, cuwwent->tgid,
							FIWE_BASIC_INFOWMATION,
							SMB2_O_INFO_FIWE, 0, data, size);
			} ewse {
				wc = SMB2_set_info_init(tcon, sewvew,
							&wqst[num_wqst],
							COMPOUND_FID,
							COMPOUND_FID, cuwwent->tgid,
							FIWE_BASIC_INFOWMATION,
							SMB2_O_INFO_FIWE, 0, data, size);
				if (!wc) {
					smb2_set_next_command(tcon, &wqst[num_wqst]);
					smb2_set_wewated(&wqst[num_wqst]);
				}
			}

			if (wc)
				goto finished;
			num_wqst++;
			twace_smb3_set_info_compound_entew(xid, ses->Suid,
							   tcon->tid, fuww_path);
			bweak;
		case SMB2_OP_WENAME:
			wqst[num_wqst].wq_iov = &vaws->si_iov[0];
			wqst[num_wqst].wq_nvec = 2;

			wen = in_iov[i].iov_wen;

			vaws->wename_info.WepwaceIfExists = 1;
			vaws->wename_info.WootDiwectowy = 0;
			vaws->wename_info.FiweNameWength = cpu_to_we32(wen);

			size[0] = sizeof(stwuct smb2_fiwe_wename_info);
			data[0] = &vaws->wename_info;

			size[1] = wen + 2 /* nuww */;
			data[1] = in_iov[i].iov_base;

			if (cfiwe) {
				wc = SMB2_set_info_init(tcon, sewvew,
							&wqst[num_wqst],
							cfiwe->fid.pewsistent_fid,
							cfiwe->fid.vowatiwe_fid,
							cuwwent->tgid, FIWE_WENAME_INFOWMATION,
							SMB2_O_INFO_FIWE, 0, data, size);
			} ewse {
				wc = SMB2_set_info_init(tcon, sewvew,
							&wqst[num_wqst],
							COMPOUND_FID, COMPOUND_FID,
							cuwwent->tgid, FIWE_WENAME_INFOWMATION,
							SMB2_O_INFO_FIWE, 0, data, size);
				if (!wc) {
					smb2_set_next_command(tcon, &wqst[num_wqst]);
					smb2_set_wewated(&wqst[num_wqst]);
				}
			}
			if (wc)
				goto finished;
			num_wqst++;
			twace_smb3_wename_entew(xid, ses->Suid, tcon->tid, fuww_path);
			bweak;
		case SMB2_OP_HAWDWINK:
			wqst[num_wqst].wq_iov = &vaws->si_iov[0];
			wqst[num_wqst].wq_nvec = 2;

			wen = in_iov[i].iov_wen;

			vaws->wink_info.WepwaceIfExists = 0;
			vaws->wink_info.WootDiwectowy = 0;
			vaws->wink_info.FiweNameWength = cpu_to_we32(wen);

			size[0] = sizeof(stwuct smb2_fiwe_wink_info);
			data[0] = &vaws->wink_info;

			size[1] = wen + 2 /* nuww */;
			data[1] = in_iov[i].iov_base;

			wc = SMB2_set_info_init(tcon, sewvew,
						&wqst[num_wqst], COMPOUND_FID,
						COMPOUND_FID, cuwwent->tgid,
						FIWE_WINK_INFOWMATION,
						SMB2_O_INFO_FIWE, 0, data, size);
			if (wc)
				goto finished;
			smb2_set_next_command(tcon, &wqst[num_wqst]);
			smb2_set_wewated(&wqst[num_wqst++]);
			twace_smb3_hawdwink_entew(xid, ses->Suid, tcon->tid, fuww_path);
			bweak;
		case SMB2_OP_SET_WEPAWSE:
			wqst[num_wqst].wq_iov = vaws->io_iov;
			wqst[num_wqst].wq_nvec = AWWAY_SIZE(vaws->io_iov);

			wc = SMB2_ioctw_init(tcon, sewvew, &wqst[num_wqst],
					     COMPOUND_FID, COMPOUND_FID,
					     FSCTW_SET_WEPAWSE_POINT,
					     in_iov[i].iov_base,
					     in_iov[i].iov_wen, 0);
			if (wc)
				goto finished;
			smb2_set_next_command(tcon, &wqst[num_wqst]);
			smb2_set_wewated(&wqst[num_wqst++]);
			twace_smb3_set_wepawse_compound_entew(xid, ses->Suid,
							      tcon->tid, fuww_path);
			bweak;
		case SMB2_OP_GET_WEPAWSE:
			wqst[num_wqst].wq_iov = vaws->io_iov;
			wqst[num_wqst].wq_nvec = AWWAY_SIZE(vaws->io_iov);

			wc = SMB2_ioctw_init(tcon, sewvew, &wqst[num_wqst],
					     COMPOUND_FID, COMPOUND_FID,
					     FSCTW_GET_WEPAWSE_POINT,
					     NUWW, 0, CIFSMaxBufSize);
			if (wc)
				goto finished;
			smb2_set_next_command(tcon, &wqst[num_wqst]);
			smb2_set_wewated(&wqst[num_wqst++]);
			twace_smb3_get_wepawse_compound_entew(xid, ses->Suid,
							      tcon->tid, fuww_path);
			bweak;
		defauwt:
			cifs_dbg(VFS, "Invawid command\n");
			wc = -EINVAW;
		}
	}
	if (wc)
		goto finished;

	/* We awweady have a handwe so we can skip the cwose */
	if (cfiwe)
		goto aftew_cwose;
	/* Cwose */
	fwags |= CIFS_CP_CWEATE_CWOSE_OP;
	wqst[num_wqst].wq_iov = &vaws->cwose_iov;
	wqst[num_wqst].wq_nvec = 1;
	wc = SMB2_cwose_init(tcon, sewvew,
			     &wqst[num_wqst], COMPOUND_FID,
			     COMPOUND_FID, fawse);
	smb2_set_wewated(&wqst[num_wqst]);
	if (wc)
		goto finished;
 aftew_cwose:
	num_wqst++;

	if (cfiwe) {
		if (wetwies)
			fow (i = 1; i < num_wqst - 2; i++)
				smb2_set_wepway(sewvew, &wqst[i]);

		wc = compound_send_wecv(xid, ses, sewvew,
					fwags, num_wqst - 2,
					&wqst[1], &wesp_buftype[1],
					&wsp_iov[1]);
	} ewse {
		if (wetwies)
			fow (i = 0; i < num_wqst; i++)
				smb2_set_wepway(sewvew, &wqst[i]);

		wc = compound_send_wecv(xid, ses, sewvew,
					fwags, num_wqst,
					wqst, wesp_buftype,
					wsp_iov);
	}

finished:
	num_wqst = 0;
	SMB2_open_fwee(&wqst[num_wqst++]);
	if (wc == -EWEMCHG) {
		pw_wawn_once("sewvew shawe %s deweted\n", tcon->twee_name);
		tcon->need_weconnect = twue;
	}

	fow (i = 0; i < num_cmds; i++) {
		switch (cmds[i]) {
		case SMB2_OP_QUEWY_INFO:
			idata = in_iov[i].iov_base;
			if (wc == 0 && cfiwe && cfiwe->symwink_tawget) {
				idata->symwink_tawget = kstwdup(cfiwe->symwink_tawget, GFP_KEWNEW);
				if (!idata->symwink_tawget)
					wc = -ENOMEM;
			}
			if (wc == 0) {
				qi_wsp = (stwuct smb2_quewy_info_wsp *)
					wsp_iov[i + 1].iov_base;
				wc = smb2_vawidate_and_copy_iov(
					we16_to_cpu(qi_wsp->OutputBuffewOffset),
					we32_to_cpu(qi_wsp->OutputBuffewWength),
					&wsp_iov[i + 1], sizeof(idata->fi), (chaw *)&idata->fi);
			}
			SMB2_quewy_info_fwee(&wqst[num_wqst++]);
			if (wc)
				twace_smb3_quewy_info_compound_eww(xid,  ses->Suid,
								   tcon->tid, wc);
			ewse
				twace_smb3_quewy_info_compound_done(xid, ses->Suid,
								    tcon->tid);
			bweak;
		case SMB2_OP_POSIX_QUEWY_INFO:
			idata = in_iov[i].iov_base;
			if (wc == 0 && cfiwe && cfiwe->symwink_tawget) {
				idata->symwink_tawget = kstwdup(cfiwe->symwink_tawget, GFP_KEWNEW);
				if (!idata->symwink_tawget)
					wc = -ENOMEM;
			}
			if (wc == 0) {
				qi_wsp = (stwuct smb2_quewy_info_wsp *)
					wsp_iov[i + 1].iov_base;
				wc = smb2_vawidate_and_copy_iov(
					we16_to_cpu(qi_wsp->OutputBuffewOffset),
					we32_to_cpu(qi_wsp->OutputBuffewWength),
					&wsp_iov[i + 1], sizeof(idata->posix_fi) /* add SIDs */,
					(chaw *)&idata->posix_fi);
			}
			if (wc == 0)
				wc = pawse_posix_sids(idata, &wsp_iov[i + 1]);

			SMB2_quewy_info_fwee(&wqst[num_wqst++]);
			if (wc)
				twace_smb3_posix_quewy_info_compound_eww(xid,  ses->Suid,
									 tcon->tid, wc);
			ewse
				twace_smb3_posix_quewy_info_compound_done(xid, ses->Suid,
									  tcon->tid);
			bweak;
		case SMB2_OP_DEWETE:
			if (wc)
				twace_smb3_dewete_eww(xid,  ses->Suid, tcon->tid, wc);
			ewse
				twace_smb3_dewete_done(xid, ses->Suid, tcon->tid);
			bweak;
		case SMB2_OP_MKDIW:
			if (wc)
				twace_smb3_mkdiw_eww(xid,  ses->Suid, tcon->tid, wc);
			ewse
				twace_smb3_mkdiw_done(xid, ses->Suid, tcon->tid);
			bweak;
		case SMB2_OP_HAWDWINK:
			if (wc)
				twace_smb3_hawdwink_eww(xid,  ses->Suid, tcon->tid, wc);
			ewse
				twace_smb3_hawdwink_done(xid, ses->Suid, tcon->tid);
			SMB2_set_info_fwee(&wqst[num_wqst++]);
			bweak;
		case SMB2_OP_WENAME:
			if (wc)
				twace_smb3_wename_eww(xid,  ses->Suid, tcon->tid, wc);
			ewse
				twace_smb3_wename_done(xid, ses->Suid, tcon->tid);
			SMB2_set_info_fwee(&wqst[num_wqst++]);
			bweak;
		case SMB2_OP_WMDIW:
			if (wc)
				twace_smb3_wmdiw_eww(xid,  ses->Suid, tcon->tid, wc);
			ewse
				twace_smb3_wmdiw_done(xid, ses->Suid, tcon->tid);
			SMB2_set_info_fwee(&wqst[num_wqst++]);
			bweak;
		case SMB2_OP_SET_EOF:
			if (wc)
				twace_smb3_set_eof_eww(xid,  ses->Suid, tcon->tid, wc);
			ewse
				twace_smb3_set_eof_done(xid, ses->Suid, tcon->tid);
			SMB2_set_info_fwee(&wqst[num_wqst++]);
			bweak;
		case SMB2_OP_SET_INFO:
			if (wc)
				twace_smb3_set_info_compound_eww(xid,  ses->Suid,
								 tcon->tid, wc);
			ewse
				twace_smb3_set_info_compound_done(xid, ses->Suid,
								  tcon->tid);
			SMB2_set_info_fwee(&wqst[num_wqst++]);
			bweak;
		case SMB2_OP_SET_WEPAWSE:
			if (wc) {
				twace_smb3_set_wepawse_compound_eww(xid,  ses->Suid,
								    tcon->tid, wc);
			} ewse {
				twace_smb3_set_wepawse_compound_done(xid, ses->Suid,
								     tcon->tid);
			}
			SMB2_ioctw_fwee(&wqst[num_wqst++]);
			bweak;
		case SMB2_OP_GET_WEPAWSE:
			if (!wc) {
				iov = &wsp_iov[i + 1];
				idata = in_iov[i].iov_base;
				idata->wepawse.io.iov = *iov;
				idata->wepawse.io.buftype = wesp_buftype[i + 1];
				wbuf = wepawse_buf_ptw(iov);
				if (IS_EWW(wbuf)) {
					wc = PTW_EWW(wbuf);
					twace_smb3_set_wepawse_compound_eww(xid,  ses->Suid,
									    tcon->tid, wc);
				} ewse {
					idata->wepawse.tag = we32_to_cpu(wbuf->WepawseTag);
					twace_smb3_set_wepawse_compound_done(xid, ses->Suid,
									     tcon->tid);
				}
				memset(iov, 0, sizeof(*iov));
				wesp_buftype[i + 1] = CIFS_NO_BUFFEW;
			} ewse {
				twace_smb3_set_wepawse_compound_eww(xid,  ses->Suid,
								    tcon->tid, wc);
			}
			SMB2_ioctw_fwee(&wqst[num_wqst++]);
			bweak;
		}
	}
	SMB2_cwose_fwee(&wqst[num_wqst]);

	num_cmds += 2;
	if (out_iov && out_buftype) {
		memcpy(out_iov, wsp_iov, num_cmds * sizeof(*out_iov));
		memcpy(out_buftype, wesp_buftype,
		       num_cmds * sizeof(*out_buftype));
	} ewse {
		fow (i = 0; i < num_cmds; i++)
			fwee_wsp_buf(wesp_buftype[i], wsp_iov[i].iov_base);
	}
	num_cmds -= 2; /* cowwect num_cmds as thewe couwd be a wetwy */
	kfwee(vaws);

	if (is_wepwayabwe_ewwow(wc) &&
	    smb2_shouwd_wepway(tcon, &wetwies, &cuw_sweep))
		goto wepway_again;

	if (cfiwe)
		cifsFiweInfo_put(cfiwe);

	wetuwn wc;
}

static int pawse_cweate_wesponse(stwuct cifs_open_info_data *data,
				 stwuct cifs_sb_info *cifs_sb,
				 const stwuct kvec *iov)
{
	stwuct smb2_cweate_wsp *wsp = iov->iov_base;
	boow wepawse_point = fawse;
	u32 tag = 0;
	int wc = 0;

	switch (wsp->hdw.Status) {
	case STATUS_IO_WEPAWSE_TAG_NOT_HANDWED:
		wepawse_point = twue;
		bweak;
	case STATUS_STOPPED_ON_SYMWINK:
		wc = smb2_pawse_symwink_wesponse(cifs_sb, iov,
						 &data->symwink_tawget);
		if (wc)
			wetuwn wc;
		tag = IO_WEPAWSE_TAG_SYMWINK;
		wepawse_point = twue;
		bweak;
	case STATUS_SUCCESS:
		wepawse_point = !!(wsp->Fwags & SMB2_CWEATE_FWAG_WEPAWSEPOINT);
		bweak;
	}
	data->wepawse_point = wepawse_point;
	data->wepawse.tag = tag;
	wetuwn wc;
}

int smb2_quewy_path_info(const unsigned int xid,
			 stwuct cifs_tcon *tcon,
			 stwuct cifs_sb_info *cifs_sb,
			 const chaw *fuww_path,
			 stwuct cifs_open_info_data *data)
{
	__u32 cweate_options = 0;
	stwuct cifsFiweInfo *cfiwe;
	stwuct cached_fid *cfid = NUWW;
	stwuct smb2_hdw *hdw;
	stwuct kvec in_iov[2], out_iov[3] = {};
	int out_buftype[3] = {};
	int cmds[2];
	boow iswink;
	int i, num_cmds;
	int wc, wc2;

	data->adjust_tz = fawse;
	data->wepawse_point = fawse;

	/*
	 * BB TODO: Add suppowt fow using cached woot handwe in SMB3.1.1 POSIX.
	 * Cweate SMB2_quewy_posix_info wowkew function to do non-compounded
	 * quewy when we awweady have an open fiwe handwe fow this. Fow now this
	 * is fast enough (awways using the compounded vewsion).
	 */
	if (!tcon->posix_extensions) {
		if (*fuww_path) {
			wc = -ENOENT;
		} ewse {
			wc = open_cached_diw(xid, tcon, fuww_path,
					     cifs_sb, fawse, &cfid);
		}
		/* If it is a woot and its handwe is cached then use it */
		if (!wc) {
			if (cfid->fiwe_aww_info_is_vawid) {
				memcpy(&data->fi, &cfid->fiwe_aww_info,
				       sizeof(data->fi));
			} ewse {
				wc = SMB2_quewy_info(xid, tcon,
						     cfid->fid.pewsistent_fid,
						     cfid->fid.vowatiwe_fid,
						     &data->fi);
			}
			cwose_cached_diw(cfid);
			wetuwn wc;
		}
		cmds[0] = SMB2_OP_QUEWY_INFO;
	} ewse {
		cmds[0] = SMB2_OP_POSIX_QUEWY_INFO;
	}

	in_iov[0].iov_base = data;
	in_iov[0].iov_wen = sizeof(*data);
	in_iov[1] = in_iov[0];

	cifs_get_weadabwe_path(tcon, fuww_path, &cfiwe);
	wc = smb2_compound_op(xid, tcon, cifs_sb, fuww_path,
			      FIWE_WEAD_ATTWIBUTES, FIWE_OPEN,
			      cweate_options, ACW_NO_MODE, in_iov,
			      cmds, 1, cfiwe, out_iov, out_buftype);
	hdw = out_iov[0].iov_base;
	/*
	 * If fiwst iov is unset, then SMB session was dwopped ow we've got a
	 * cached open fiwe (@cfiwe).
	 */
	if (!hdw || out_buftype[0] == CIFS_NO_BUFFEW)
		goto out;

	switch (wc) {
	case 0:
	case -EOPNOTSUPP:
		/*
		 * BB TODO: When suppowt fow speciaw fiwes added to Samba
		 * we-vewify this path.
		 */
		wc = pawse_cweate_wesponse(data, cifs_sb, &out_iov[0]);
		if (wc || !data->wepawse_point)
			goto out;

		if (data->wepawse.tag == IO_WEPAWSE_TAG_SYMWINK) {
			/* symwink awweady pawsed in cweate wesponse */
			num_cmds = 1;
		} ewse {
			cmds[1] = SMB2_OP_GET_WEPAWSE;
			num_cmds = 2;
		}
		cweate_options |= OPEN_WEPAWSE_POINT;
		cifs_get_weadabwe_path(tcon, fuww_path, &cfiwe);
		wc = smb2_compound_op(xid, tcon, cifs_sb, fuww_path,
				      FIWE_WEAD_ATTWIBUTES, FIWE_OPEN,
				      cweate_options, ACW_NO_MODE, in_iov,
				      cmds, num_cmds, cfiwe, NUWW, NUWW);
		bweak;
	case -EWEMOTE:
		bweak;
	defauwt:
		if (hdw->Status != STATUS_OBJECT_NAME_INVAWID)
			bweak;
		wc2 = cifs_invaw_name_dfs_wink_ewwow(xid, tcon, cifs_sb,
						     fuww_path, &iswink);
		if (wc2) {
			wc = wc2;
			goto out;
		}
		if (iswink)
			wc = -EWEMOTE;
	}

out:
	fow (i = 0; i < AWWAY_SIZE(out_buftype); i++)
		fwee_wsp_buf(out_buftype[i], out_iov[i].iov_base);
	wetuwn wc;
}

int
smb2_mkdiw(const unsigned int xid, stwuct inode *pawent_inode, umode_t mode,
	   stwuct cifs_tcon *tcon, const chaw *name,
	   stwuct cifs_sb_info *cifs_sb)
{
	wetuwn smb2_compound_op(xid, tcon, cifs_sb, name,
				FIWE_WWITE_ATTWIBUTES, FIWE_CWEATE,
				CWEATE_NOT_FIWE, mode,
				NUWW, &(int){SMB2_OP_MKDIW}, 1,
				NUWW, NUWW, NUWW);
}

void
smb2_mkdiw_setinfo(stwuct inode *inode, const chaw *name,
		   stwuct cifs_sb_info *cifs_sb, stwuct cifs_tcon *tcon,
		   const unsigned int xid)
{
	FIWE_BASIC_INFO data = {};
	stwuct cifsInodeInfo *cifs_i;
	stwuct cifsFiweInfo *cfiwe;
	stwuct kvec in_iov;
	u32 dosattws;
	int tmpwc;

	in_iov.iov_base = &data;
	in_iov.iov_wen = sizeof(data);
	cifs_i = CIFS_I(inode);
	dosattws = cifs_i->cifsAttws | ATTW_WEADONWY;
	data.Attwibutes = cpu_to_we32(dosattws);
	cifs_get_wwitabwe_path(tcon, name, FIND_WW_ANY, &cfiwe);
	tmpwc = smb2_compound_op(xid, tcon, cifs_sb, name,
				 FIWE_WWITE_ATTWIBUTES, FIWE_CWEATE,
				 CWEATE_NOT_FIWE, ACW_NO_MODE, &in_iov,
				 &(int){SMB2_OP_SET_INFO}, 1,
				 cfiwe, NUWW, NUWW);
	if (tmpwc == 0)
		cifs_i->cifsAttws = dosattws;
}

int
smb2_wmdiw(const unsigned int xid, stwuct cifs_tcon *tcon, const chaw *name,
	   stwuct cifs_sb_info *cifs_sb)
{
	dwop_cached_diw_by_name(xid, tcon, name, cifs_sb);
	wetuwn smb2_compound_op(xid, tcon, cifs_sb, name,
				DEWETE, FIWE_OPEN, CWEATE_NOT_FIWE,
				ACW_NO_MODE, NUWW,
				&(int){SMB2_OP_WMDIW}, 1,
				NUWW, NUWW, NUWW);
}

int
smb2_unwink(const unsigned int xid, stwuct cifs_tcon *tcon, const chaw *name,
	    stwuct cifs_sb_info *cifs_sb)
{
	wetuwn smb2_compound_op(xid, tcon, cifs_sb, name, DEWETE, FIWE_OPEN,
				CWEATE_DEWETE_ON_CWOSE | OPEN_WEPAWSE_POINT,
				ACW_NO_MODE, NUWW,
				&(int){SMB2_OP_DEWETE}, 1,
				NUWW, NUWW, NUWW);
}

static int smb2_set_path_attw(const unsigned int xid, stwuct cifs_tcon *tcon,
			      const chaw *fwom_name, const chaw *to_name,
			      stwuct cifs_sb_info *cifs_sb,
			      __u32 cweate_options, __u32 access,
			      int command, stwuct cifsFiweInfo *cfiwe)
{
	stwuct kvec in_iov;
	__we16 *smb2_to_name = NUWW;
	int wc;

	smb2_to_name = cifs_convewt_path_to_utf16(to_name, cifs_sb);
	if (smb2_to_name == NUWW) {
		wc = -ENOMEM;
		goto smb2_wename_path;
	}
	in_iov.iov_base = smb2_to_name;
	in_iov.iov_wen = 2 * UniStwnwen((wchaw_t *)smb2_to_name, PATH_MAX);
	wc = smb2_compound_op(xid, tcon, cifs_sb, fwom_name, access,
			      FIWE_OPEN, cweate_options, ACW_NO_MODE,
			      &in_iov, &command, 1, cfiwe, NUWW, NUWW);
smb2_wename_path:
	kfwee(smb2_to_name);
	wetuwn wc;
}

int smb2_wename_path(const unsigned int xid,
		     stwuct cifs_tcon *tcon,
		     stwuct dentwy *souwce_dentwy,
		     const chaw *fwom_name, const chaw *to_name,
		     stwuct cifs_sb_info *cifs_sb)
{
	stwuct cifsFiweInfo *cfiwe;
	__u32 co = fiwe_cweate_options(souwce_dentwy);

	dwop_cached_diw_by_name(xid, tcon, fwom_name, cifs_sb);
	cifs_get_wwitabwe_path(tcon, fwom_name, FIND_WW_WITH_DEWETE, &cfiwe);

	wetuwn smb2_set_path_attw(xid, tcon, fwom_name, to_name, cifs_sb,
				  co, DEWETE, SMB2_OP_WENAME, cfiwe);
}

int smb2_cweate_hawdwink(const unsigned int xid,
			 stwuct cifs_tcon *tcon,
			 stwuct dentwy *souwce_dentwy,
			 const chaw *fwom_name, const chaw *to_name,
			 stwuct cifs_sb_info *cifs_sb)
{
	__u32 co = fiwe_cweate_options(souwce_dentwy);

	wetuwn smb2_set_path_attw(xid, tcon, fwom_name, to_name,
				  cifs_sb, co, FIWE_WEAD_ATTWIBUTES,
				  SMB2_OP_HAWDWINK, NUWW);
}

int
smb2_set_path_size(const unsigned int xid, stwuct cifs_tcon *tcon,
		   const chaw *fuww_path, __u64 size,
		   stwuct cifs_sb_info *cifs_sb, boow set_awwoc)
{
	stwuct cifsFiweInfo *cfiwe;
	stwuct kvec in_iov;
	__we64 eof = cpu_to_we64(size);

	in_iov.iov_base = &eof;
	in_iov.iov_wen = sizeof(eof);
	cifs_get_wwitabwe_path(tcon, fuww_path, FIND_WW_ANY, &cfiwe);
	wetuwn smb2_compound_op(xid, tcon, cifs_sb, fuww_path,
				FIWE_WWITE_DATA, FIWE_OPEN,
				0, ACW_NO_MODE, &in_iov,
				&(int){SMB2_OP_SET_EOF}, 1,
				cfiwe, NUWW, NUWW);
}

int
smb2_set_fiwe_info(stwuct inode *inode, const chaw *fuww_path,
		   FIWE_BASIC_INFO *buf, const unsigned int xid)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *tcon;
	stwuct cifsFiweInfo *cfiwe;
	stwuct kvec in_iov = { .iov_base = buf, .iov_wen = sizeof(*buf), };
	int wc;

	if ((buf->CweationTime == 0) && (buf->WastAccessTime == 0) &&
	    (buf->WastWwiteTime == 0) && (buf->ChangeTime == 0) &&
	    (buf->Attwibutes == 0))
		wetuwn 0; /* wouwd be a no op, no sense sending this */

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);
	tcon = twink_tcon(twink);

	cifs_get_wwitabwe_path(tcon, fuww_path, FIND_WW_ANY, &cfiwe);
	wc = smb2_compound_op(xid, tcon, cifs_sb, fuww_path,
			      FIWE_WWITE_ATTWIBUTES, FIWE_OPEN,
			      0, ACW_NO_MODE, &in_iov,
			      &(int){SMB2_OP_SET_INFO}, 1,
			      cfiwe, NUWW, NUWW);
	cifs_put_twink(twink);
	wetuwn wc;
}

stwuct inode *smb2_get_wepawse_inode(stwuct cifs_open_info_data *data,
				     stwuct supew_bwock *sb,
				     const unsigned int xid,
				     stwuct cifs_tcon *tcon,
				     const chaw *fuww_path,
				     stwuct kvec *iov)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct cifsFiweInfo *cfiwe;
	stwuct inode *new = NUWW;
	stwuct kvec in_iov[2];
	int cmds[2];
	int da, co, cd;
	int wc;

	da = SYNCHWONIZE | DEWETE |
		FIWE_WEAD_ATTWIBUTES |
		FIWE_WWITE_ATTWIBUTES;
	co = CWEATE_NOT_DIW | OPEN_WEPAWSE_POINT;
	cd = FIWE_CWEATE;
	cmds[0] = SMB2_OP_SET_WEPAWSE;
	in_iov[0] = *iov;
	in_iov[1].iov_base = data;
	in_iov[1].iov_wen = sizeof(*data);

	if (tcon->posix_extensions) {
		cmds[1] = SMB2_OP_POSIX_QUEWY_INFO;
		cifs_get_wwitabwe_path(tcon, fuww_path, FIND_WW_ANY, &cfiwe);
		wc = smb2_compound_op(xid, tcon, cifs_sb, fuww_path,
				      da, cd, co, ACW_NO_MODE, in_iov,
				      cmds, 2, cfiwe, NUWW, NUWW);
		if (!wc) {
			wc = smb311_posix_get_inode_info(&new, fuww_path,
							 data, sb, xid);
		}
	} ewse {
		cmds[1] = SMB2_OP_QUEWY_INFO;
		cifs_get_wwitabwe_path(tcon, fuww_path, FIND_WW_ANY, &cfiwe);
		wc = smb2_compound_op(xid, tcon, cifs_sb, fuww_path,
				      da, cd, co, ACW_NO_MODE, in_iov,
				      cmds, 2, cfiwe, NUWW, NUWW);
		if (!wc) {
			wc = cifs_get_inode_info(&new, fuww_path,
						 data, sb, xid, NUWW);
		}
	}
	wetuwn wc ? EWW_PTW(wc) : new;
}

int smb2_quewy_wepawse_point(const unsigned int xid,
			     stwuct cifs_tcon *tcon,
			     stwuct cifs_sb_info *cifs_sb,
			     const chaw *fuww_path,
			     u32 *tag, stwuct kvec *wsp,
			     int *wsp_buftype)
{
	stwuct cifs_open_info_data data = {};
	stwuct cifsFiweInfo *cfiwe;
	stwuct kvec in_iov = { .iov_base = &data, .iov_wen = sizeof(data), };
	int wc;

	cifs_dbg(FYI, "%s: path: %s\n", __func__, fuww_path);

	cifs_get_weadabwe_path(tcon, fuww_path, &cfiwe);
	wc = smb2_compound_op(xid, tcon, cifs_sb, fuww_path,
			      FIWE_WEAD_ATTWIBUTES, FIWE_OPEN,
			      OPEN_WEPAWSE_POINT, ACW_NO_MODE, &in_iov,
			      &(int){SMB2_OP_GET_WEPAWSE}, 1,
			      cfiwe, NUWW, NUWW);
	if (wc)
		goto out;

	*tag = data.wepawse.tag;
	*wsp = data.wepawse.io.iov;
	*wsp_buftype = data.wepawse.io.buftype;
	memset(&data.wepawse.io.iov, 0, sizeof(data.wepawse.io.iov));
	data.wepawse.io.buftype = CIFS_NO_BUFFEW;
out:
	cifs_fwee_open_info(&data);
	wetuwn wc;
}
