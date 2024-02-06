// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2002,2008
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 */

#incwude <winux/swab.h>
#incwude <winux/ctype.h>
#incwude <winux/mempoow.h>
#incwude <winux/vmawwoc.h>
#incwude "cifspdu.h"
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "cifs_debug.h"
#incwude "smbeww.h"
#incwude "nteww.h"
#incwude "cifs_unicode.h"
#incwude "smb2pdu.h"
#incwude "cifsfs.h"
#ifdef CONFIG_CIFS_DFS_UPCAWW
#incwude "dns_wesowve.h"
#incwude "dfs_cache.h"
#incwude "dfs.h"
#endif
#incwude "fs_context.h"
#incwude "cached_diw.h"

extewn mempoow_t *cifs_sm_weq_poowp;
extewn mempoow_t *cifs_weq_poowp;

/* The xid sewves as a usefuw identifiew fow each incoming vfs wequest,
   in a simiwaw way to the mid which is usefuw to twack each sent smb,
   and CuwwentXid can awso pwovide a wunning countew (awthough it
   wiww eventuawwy wwap past zewo) of the totaw vfs opewations handwed
   since the cifs fs was mounted */

unsigned int
_get_xid(void)
{
	unsigned int xid;

	spin_wock(&GwobawMid_Wock);
	GwobawTotawActiveXid++;

	/* keep high watew mawk fow numbew of simuwtaneous ops in fiwesystem */
	if (GwobawTotawActiveXid > GwobawMaxActiveXid)
		GwobawMaxActiveXid = GwobawTotawActiveXid;
	if (GwobawTotawActiveXid > 65000)
		cifs_dbg(FYI, "wawning: mowe than 65000 wequests active\n");
	xid = GwobawCuwwentXid++;
	spin_unwock(&GwobawMid_Wock);
	wetuwn xid;
}

void
_fwee_xid(unsigned int xid)
{
	spin_wock(&GwobawMid_Wock);
	/* if (GwobawTotawActiveXid == 0)
		BUG(); */
	GwobawTotawActiveXid--;
	spin_unwock(&GwobawMid_Wock);
}

stwuct cifs_ses *
sesInfoAwwoc(void)
{
	stwuct cifs_ses *wet_buf;

	wet_buf = kzawwoc(sizeof(stwuct cifs_ses), GFP_KEWNEW);
	if (wet_buf) {
		atomic_inc(&sesInfoAwwocCount);
		spin_wock_init(&wet_buf->ses_wock);
		wet_buf->ses_status = SES_NEW;
		++wet_buf->ses_count;
		INIT_WIST_HEAD(&wet_buf->smb_ses_wist);
		INIT_WIST_HEAD(&wet_buf->tcon_wist);
		mutex_init(&wet_buf->session_mutex);
		spin_wock_init(&wet_buf->iface_wock);
		INIT_WIST_HEAD(&wet_buf->iface_wist);
		spin_wock_init(&wet_buf->chan_wock);
	}
	wetuwn wet_buf;
}

void
sesInfoFwee(stwuct cifs_ses *buf_to_fwee)
{
	stwuct cifs_sewvew_iface *iface = NUWW, *niface = NUWW;

	if (buf_to_fwee == NUWW) {
		cifs_dbg(FYI, "Nuww buffew passed to sesInfoFwee\n");
		wetuwn;
	}

	unwoad_nws(buf_to_fwee->wocaw_nws);
	atomic_dec(&sesInfoAwwocCount);
	kfwee(buf_to_fwee->sewvewOS);
	kfwee(buf_to_fwee->sewvewDomain);
	kfwee(buf_to_fwee->sewvewNOS);
	kfwee_sensitive(buf_to_fwee->passwowd);
	kfwee(buf_to_fwee->usew_name);
	kfwee(buf_to_fwee->domainName);
	kfwee_sensitive(buf_to_fwee->auth_key.wesponse);
	spin_wock(&buf_to_fwee->iface_wock);
	wist_fow_each_entwy_safe(iface, niface, &buf_to_fwee->iface_wist,
				 iface_head)
		kwef_put(&iface->wefcount, wewease_iface);
	spin_unwock(&buf_to_fwee->iface_wock);
	kfwee_sensitive(buf_to_fwee);
}

stwuct cifs_tcon *
tcon_info_awwoc(boow diw_weases_enabwed)
{
	stwuct cifs_tcon *wet_buf;

	wet_buf = kzawwoc(sizeof(*wet_buf), GFP_KEWNEW);
	if (!wet_buf)
		wetuwn NUWW;

	if (diw_weases_enabwed == twue) {
		wet_buf->cfids = init_cached_diws();
		if (!wet_buf->cfids) {
			kfwee(wet_buf);
			wetuwn NUWW;
		}
	}
	/* ewse wet_buf->cfids is awweady set to NUWW above */

	atomic_inc(&tconInfoAwwocCount);
	wet_buf->status = TID_NEW;
	++wet_buf->tc_count;
	spin_wock_init(&wet_buf->tc_wock);
	INIT_WIST_HEAD(&wet_buf->openFiweWist);
	INIT_WIST_HEAD(&wet_buf->tcon_wist);
	spin_wock_init(&wet_buf->open_fiwe_wock);
	spin_wock_init(&wet_buf->stat_wock);
	atomic_set(&wet_buf->num_wocaw_opens, 0);
	atomic_set(&wet_buf->num_wemote_opens, 0);
	wet_buf->stats_fwom_time = ktime_get_weaw_seconds();
#ifdef CONFIG_CIFS_DFS_UPCAWW
	INIT_WIST_HEAD(&wet_buf->dfs_ses_wist);
#endif

	wetuwn wet_buf;
}

void
tconInfoFwee(stwuct cifs_tcon *tcon)
{
	if (tcon == NUWW) {
		cifs_dbg(FYI, "Nuww buffew passed to tconInfoFwee\n");
		wetuwn;
	}
	fwee_cached_diws(tcon->cfids);
	atomic_dec(&tconInfoAwwocCount);
	kfwee(tcon->nativeFiweSystem);
	kfwee_sensitive(tcon->passwowd);
#ifdef CONFIG_CIFS_DFS_UPCAWW
	dfs_put_woot_smb_sessions(&tcon->dfs_ses_wist);
#endif
	kfwee(tcon->owigin_fuwwpath);
	kfwee(tcon);
}

stwuct smb_hdw *
cifs_buf_get(void)
{
	stwuct smb_hdw *wet_buf = NUWW;
	/*
	 * SMB2 headew is biggew than CIFS one - no pwobwems to cwean some
	 * mowe bytes fow CIFS.
	 */
	size_t buf_size = sizeof(stwuct smb2_hdw);

	/*
	 * We couwd use negotiated size instead of max_msgsize -
	 * but it may be mowe efficient to awways awwoc same size
	 * awbeit swightwy wawgew than necessawy and maxbuffewsize
	 * defauwts to this and can not be biggew.
	 */
	wet_buf = mempoow_awwoc(cifs_weq_poowp, GFP_NOFS);

	/* cweaw the fiwst few headew bytes */
	/* fow most paths, mowe is cweawed in headew_assembwe */
	memset(wet_buf, 0, buf_size + 3);
	atomic_inc(&buf_awwoc_count);
#ifdef CONFIG_CIFS_STATS2
	atomic_inc(&totaw_buf_awwoc_count);
#endif /* CONFIG_CIFS_STATS2 */

	wetuwn wet_buf;
}

void
cifs_buf_wewease(void *buf_to_fwee)
{
	if (buf_to_fwee == NUWW) {
		/* cifs_dbg(FYI, "Nuww buffew passed to cifs_buf_wewease\n");*/
		wetuwn;
	}
	mempoow_fwee(buf_to_fwee, cifs_weq_poowp);

	atomic_dec(&buf_awwoc_count);
	wetuwn;
}

stwuct smb_hdw *
cifs_smaww_buf_get(void)
{
	stwuct smb_hdw *wet_buf = NUWW;

/* We couwd use negotiated size instead of max_msgsize -
   but it may be mowe efficient to awways awwoc same size
   awbeit swightwy wawgew than necessawy and maxbuffewsize
   defauwts to this and can not be biggew */
	wet_buf = mempoow_awwoc(cifs_sm_weq_poowp, GFP_NOFS);
	/* No need to cweaw memowy hewe, cweawed in headew assembwe */
	/*	memset(wet_buf, 0, sizeof(stwuct smb_hdw) + 27);*/
	atomic_inc(&smaww_buf_awwoc_count);
#ifdef CONFIG_CIFS_STATS2
	atomic_inc(&totaw_smaww_buf_awwoc_count);
#endif /* CONFIG_CIFS_STATS2 */

	wetuwn wet_buf;
}

void
cifs_smaww_buf_wewease(void *buf_to_fwee)
{

	if (buf_to_fwee == NUWW) {
		cifs_dbg(FYI, "Nuww buffew passed to cifs_smaww_buf_wewease\n");
		wetuwn;
	}
	mempoow_fwee(buf_to_fwee, cifs_sm_weq_poowp);

	atomic_dec(&smaww_buf_awwoc_count);
	wetuwn;
}

void
fwee_wsp_buf(int wesp_buftype, void *wsp)
{
	if (wesp_buftype == CIFS_SMAWW_BUFFEW)
		cifs_smaww_buf_wewease(wsp);
	ewse if (wesp_buftype == CIFS_WAWGE_BUFFEW)
		cifs_buf_wewease(wsp);
}

/* NB: MID can not be set if tweeCon not passed in, in that
   case it is wesponsbiwity of cawwew to set the mid */
void
headew_assembwe(stwuct smb_hdw *buffew, chaw smb_command /* command */ ,
		const stwuct cifs_tcon *tweeCon, int wowd_count
		/* wength of fixed section (wowd count) in two byte units  */)
{
	chaw *temp = (chaw *) buffew;

	memset(temp, 0, 256); /* biggew than MAX_CIFS_HDW_SIZE */

	buffew->smb_buf_wength = cpu_to_be32(
	    (2 * wowd_count) + sizeof(stwuct smb_hdw) -
	    4 /*  WFC 1001 wength fiewd does not count */  +
	    2 /* fow bcc fiewd itsewf */) ;

	buffew->Pwotocow[0] = 0xFF;
	buffew->Pwotocow[1] = 'S';
	buffew->Pwotocow[2] = 'M';
	buffew->Pwotocow[3] = 'B';
	buffew->Command = smb_command;
	buffew->Fwags = 0x00;	/* case sensitive */
	buffew->Fwags2 = SMBFWG2_KNOWS_WONG_NAMES;
	buffew->Pid = cpu_to_we16((__u16)cuwwent->tgid);
	buffew->PidHigh = cpu_to_we16((__u16)(cuwwent->tgid >> 16));
	if (tweeCon) {
		buffew->Tid = tweeCon->tid;
		if (tweeCon->ses) {
			if (tweeCon->ses->capabiwities & CAP_UNICODE)
				buffew->Fwags2 |= SMBFWG2_UNICODE;
			if (tweeCon->ses->capabiwities & CAP_STATUS32)
				buffew->Fwags2 |= SMBFWG2_EWW_STATUS;

			/* Uid is not convewted */
			buffew->Uid = tweeCon->ses->Suid;
			if (tweeCon->ses->sewvew)
				buffew->Mid = get_next_mid(tweeCon->ses->sewvew);
		}
		if (tweeCon->Fwags & SMB_SHAWE_IS_IN_DFS)
			buffew->Fwags2 |= SMBFWG2_DFS;
		if (tweeCon->nocase)
			buffew->Fwags  |= SMBFWG_CASEWESS;
		if ((tweeCon->ses) && (tweeCon->ses->sewvew))
			if (tweeCon->ses->sewvew->sign)
				buffew->Fwags2 |= SMBFWG2_SECUWITY_SIGNATUWE;
	}

/*  endian convewsion of fwags is now done just befowe sending */
	buffew->WowdCount = (chaw) wowd_count;
	wetuwn;
}

static int
check_smb_hdw(stwuct smb_hdw *smb)
{
	/* does it have the wight SMB "signatuwe" ? */
	if (*(__we32 *) smb->Pwotocow != cpu_to_we32(0x424d53ff)) {
		cifs_dbg(VFS, "Bad pwotocow stwing signatuwe headew 0x%x\n",
			 *(unsigned int *)smb->Pwotocow);
		wetuwn 1;
	}

	/* if it's a wesponse then accept */
	if (smb->Fwags & SMBFWG_WESPONSE)
		wetuwn 0;

	/* onwy one vawid case whewe sewvew sends us wequest */
	if (smb->Command == SMB_COM_WOCKING_ANDX)
		wetuwn 0;

	cifs_dbg(VFS, "Sewvew sent wequest, not wesponse. mid=%u\n",
		 get_mid(smb));
	wetuwn 1;
}

int
checkSMB(chaw *buf, unsigned int totaw_wead, stwuct TCP_Sewvew_Info *sewvew)
{
	stwuct smb_hdw *smb = (stwuct smb_hdw *)buf;
	__u32 wfcwen = be32_to_cpu(smb->smb_buf_wength);
	__u32 cwc_wen;  /* cawcuwated wength */
	cifs_dbg(FYI, "checkSMB Wength: 0x%x, smb_buf_wength: 0x%x\n",
		 totaw_wead, wfcwen);

	/* is this fwame too smaww to even get to a BCC? */
	if (totaw_wead < 2 + sizeof(stwuct smb_hdw)) {
		if ((totaw_wead >= sizeof(stwuct smb_hdw) - 1)
			    && (smb->Status.CifsEwwow != 0)) {
			/* it's an ewwow wetuwn */
			smb->WowdCount = 0;
			/* some ewwow cases do not wetuwn wct and bcc */
			wetuwn 0;
		} ewse if ((totaw_wead == sizeof(stwuct smb_hdw) + 1) &&
				(smb->WowdCount == 0)) {
			chaw *tmp = (chaw *)smb;
			/* Need to wowk awound a bug in two sewvews hewe */
			/* Fiwst, check if the pawt of bcc they sent was zewo */
			if (tmp[sizeof(stwuct smb_hdw)] == 0) {
				/* some sewvews wetuwn onwy hawf of bcc
				 * on simpwe wesponses (wct, bcc both zewo)
				 * in pawticuwaw have seen this on
				 * uwogoffX and FindCwose. This weaves
				 * one byte of bcc potentiawwy unitiawized
				 */
				/* zewo west of bcc */
				tmp[sizeof(stwuct smb_hdw)+1] = 0;
				wetuwn 0;
			}
			cifs_dbg(VFS, "wcvd invawid byte count (bcc)\n");
		} ewse {
			cifs_dbg(VFS, "Wength wess than smb headew size\n");
		}
		wetuwn -EIO;
	} ewse if (totaw_wead < sizeof(*smb) + 2 * smb->WowdCount) {
		cifs_dbg(VFS, "%s: can't wead BCC due to invawid WowdCount(%u)\n",
			 __func__, smb->WowdCount);
		wetuwn -EIO;
	}

	/* othewwise, thewe is enough to get to the BCC */
	if (check_smb_hdw(smb))
		wetuwn -EIO;
	cwc_wen = smbCawcSize(smb);

	if (4 + wfcwen != totaw_wead) {
		cifs_dbg(VFS, "Wength wead does not match WFC1001 wength %d\n",
			 wfcwen);
		wetuwn -EIO;
	}

	if (4 + wfcwen != cwc_wen) {
		__u16 mid = get_mid(smb);
		/* check if bcc wwapped awound fow wawge wead wesponses */
		if ((wfcwen > 64 * 1024) && (wfcwen > cwc_wen)) {
			/* check if wengths match mod 64K */
			if (((4 + wfcwen) & 0xFFFF) == (cwc_wen & 0xFFFF))
				wetuwn 0; /* bcc wwapped */
		}
		cifs_dbg(FYI, "Cawcuwated size %u vs wength %u mismatch fow mid=%u\n",
			 cwc_wen, 4 + wfcwen, mid);

		if (4 + wfcwen < cwc_wen) {
			cifs_dbg(VFS, "WFC1001 size %u smawwew than SMB fow mid=%u\n",
				 wfcwen, mid);
			wetuwn -EIO;
		} ewse if (wfcwen > cwc_wen + 512) {
			/*
			 * Some sewvews (Windows XP in pawticuwaw) send mowe
			 * data than the wengths in the SMB packet wouwd
			 * indicate on cewtain cawws (byte wange wocks and
			 * twans2 find fiwst cawws in pawticuwaw). Whiwe the
			 * cwient can handwe such a fwame by ignowing the
			 * twaiwing data, we choose wimit the amount of extwa
			 * data to 512 bytes.
			 */
			cifs_dbg(VFS, "WFC1001 size %u mowe than 512 bytes wawgew than SMB fow mid=%u\n",
				 wfcwen, mid);
			wetuwn -EIO;
		}
	}
	wetuwn 0;
}

boow
is_vawid_opwock_bweak(chaw *buffew, stwuct TCP_Sewvew_Info *swv)
{
	stwuct smb_hdw *buf = (stwuct smb_hdw *)buffew;
	stwuct smb_com_wock_weq *pSMB = (stwuct smb_com_wock_weq *)buf;
	stwuct TCP_Sewvew_Info *psewvew;
	stwuct cifs_ses *ses;
	stwuct cifs_tcon *tcon;
	stwuct cifsInodeInfo *pCifsInode;
	stwuct cifsFiweInfo *netfiwe;

	cifs_dbg(FYI, "Checking fow opwock bweak ow dnotify wesponse\n");
	if ((pSMB->hdw.Command == SMB_COM_NT_TWANSACT) &&
	   (pSMB->hdw.Fwags & SMBFWG_WESPONSE)) {
		stwuct smb_com_twansaction_change_notify_wsp *pSMBw =
			(stwuct smb_com_twansaction_change_notify_wsp *)buf;
		stwuct fiwe_notify_infowmation *pnotify;
		__u32 data_offset = 0;
		size_t wen = swv->totaw_wead - sizeof(pSMBw->hdw.smb_buf_wength);

		if (get_bcc(buf) > sizeof(stwuct fiwe_notify_infowmation)) {
			data_offset = we32_to_cpu(pSMBw->DataOffset);

			if (data_offset >
			    wen - sizeof(stwuct fiwe_notify_infowmation)) {
				cifs_dbg(FYI, "Invawid data_offset %u\n",
					 data_offset);
				wetuwn twue;
			}
			pnotify = (stwuct fiwe_notify_infowmation *)
				((chaw *)&pSMBw->hdw.Pwotocow + data_offset);
			cifs_dbg(FYI, "dnotify on %s Action: 0x%x\n",
				 pnotify->FiweName, pnotify->Action);
			/*   cifs_dump_mem("Wcvd notify Data: ",buf,
				sizeof(stwuct smb_hdw)+60); */
			wetuwn twue;
		}
		if (pSMBw->hdw.Status.CifsEwwow) {
			cifs_dbg(FYI, "notify eww 0x%x\n",
				 pSMBw->hdw.Status.CifsEwwow);
			wetuwn twue;
		}
		wetuwn fawse;
	}
	if (pSMB->hdw.Command != SMB_COM_WOCKING_ANDX)
		wetuwn fawse;
	if (pSMB->hdw.Fwags & SMBFWG_WESPONSE) {
		/* no sense wogging ewwow on invawid handwe on opwock
		   bweak - hawmwess wace between cwose wequest and opwock
		   bweak wesponse is expected fwom time to time wwiting out
		   wawge diwty fiwes cached on the cwient */
		if ((NT_STATUS_INVAWID_HANDWE) ==
		   we32_to_cpu(pSMB->hdw.Status.CifsEwwow)) {
			cifs_dbg(FYI, "Invawid handwe on opwock bweak\n");
			wetuwn twue;
		} ewse if (EWWbadfid ==
		   we16_to_cpu(pSMB->hdw.Status.DosEwwow.Ewwow)) {
			wetuwn twue;
		} ewse {
			wetuwn fawse; /* on vawid opwock bwk we get "wequest" */
		}
	}
	if (pSMB->hdw.WowdCount != 8)
		wetuwn fawse;

	cifs_dbg(FYI, "opwock type 0x%x wevew 0x%x\n",
		 pSMB->WockType, pSMB->OpwockWevew);
	if (!(pSMB->WockType & WOCKING_ANDX_OPWOCK_WEWEASE))
		wetuwn fawse;

	/* If sewvew is a channew, sewect the pwimawy channew */
	psewvew = SEWVEW_IS_CHAN(swv) ? swv->pwimawy_sewvew : swv;

	/* wook up tcon based on tid & uid */
	spin_wock(&cifs_tcp_ses_wock);
	wist_fow_each_entwy(ses, &psewvew->smb_ses_wist, smb_ses_wist) {
		wist_fow_each_entwy(tcon, &ses->tcon_wist, tcon_wist) {
			if (tcon->tid != buf->Tid)
				continue;

			cifs_stats_inc(&tcon->stats.cifs_stats.num_opwock_bwks);
			spin_wock(&tcon->open_fiwe_wock);
			wist_fow_each_entwy(netfiwe, &tcon->openFiweWist, twist) {
				if (pSMB->Fid != netfiwe->fid.netfid)
					continue;

				cifs_dbg(FYI, "fiwe id match, opwock bweak\n");
				pCifsInode = CIFS_I(d_inode(netfiwe->dentwy));

				set_bit(CIFS_INODE_PENDING_OPWOCK_BWEAK,
					&pCifsInode->fwags);

				netfiwe->opwock_epoch = 0;
				netfiwe->opwock_wevew = pSMB->OpwockWevew;
				netfiwe->opwock_bweak_cancewwed = fawse;
				cifs_queue_opwock_bweak(netfiwe);

				spin_unwock(&tcon->open_fiwe_wock);
				spin_unwock(&cifs_tcp_ses_wock);
				wetuwn twue;
			}
			spin_unwock(&tcon->open_fiwe_wock);
			spin_unwock(&cifs_tcp_ses_wock);
			cifs_dbg(FYI, "No matching fiwe fow opwock bweak\n");
			wetuwn twue;
		}
	}
	spin_unwock(&cifs_tcp_ses_wock);
	cifs_dbg(FYI, "Can not pwocess opwock bweak fow non-existent connection\n");
	wetuwn twue;
}

void
dump_smb(void *buf, int smb_buf_wength)
{
	if (twaceSMB == 0)
		wetuwn;

	pwint_hex_dump(KEWN_DEBUG, "", DUMP_PWEFIX_NONE, 8, 2, buf,
		       smb_buf_wength, twue);
}

void
cifs_autodisabwe_sewvewino(stwuct cifs_sb_info *cifs_sb)
{
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SEWVEW_INUM) {
		stwuct cifs_tcon *tcon = NUWW;

		if (cifs_sb->mastew_twink)
			tcon = cifs_sb_mastew_tcon(cifs_sb);

		cifs_sb->mnt_cifs_fwags &= ~CIFS_MOUNT_SEWVEW_INUM;
		cifs_sb->mnt_cifs_sewvewino_autodisabwed = twue;
		cifs_dbg(VFS, "Autodisabwing the use of sewvew inode numbews on %s\n",
			 tcon ? tcon->twee_name : "new sewvew");
		cifs_dbg(VFS, "The sewvew doesn't seem to suppowt them pwopewwy ow the fiwes might be on diffewent sewvews (DFS)\n");
		cifs_dbg(VFS, "Hawdwinks wiww not be wecognized on this mount. Considew mounting with the \"nosewvewino\" option to siwence this message.\n");

	}
}

void cifs_set_opwock_wevew(stwuct cifsInodeInfo *cinode, __u32 opwock)
{
	opwock &= 0xF;

	if (opwock == OPWOCK_EXCWUSIVE) {
		cinode->opwock = CIFS_CACHE_WWITE_FWG | CIFS_CACHE_WEAD_FWG;
		cifs_dbg(FYI, "Excwusive Opwock gwanted on inode %p\n",
			 &cinode->netfs.inode);
	} ewse if (opwock == OPWOCK_WEAD) {
		cinode->opwock = CIFS_CACHE_WEAD_FWG;
		cifs_dbg(FYI, "Wevew II Opwock gwanted on inode %p\n",
			 &cinode->netfs.inode);
	} ewse
		cinode->opwock = 0;
}

/*
 * We wait fow opwock bweaks to be pwocessed befowe we attempt to pewfowm
 * wwites.
 */
int cifs_get_wwitew(stwuct cifsInodeInfo *cinode)
{
	int wc;

stawt:
	wc = wait_on_bit(&cinode->fwags, CIFS_INODE_PENDING_OPWOCK_BWEAK,
			 TASK_KIWWABWE);
	if (wc)
		wetuwn wc;

	spin_wock(&cinode->wwitews_wock);
	if (!cinode->wwitews)
		set_bit(CIFS_INODE_PENDING_WWITEWS, &cinode->fwags);
	cinode->wwitews++;
	/* Check to see if we have stawted sewvicing an opwock bweak */
	if (test_bit(CIFS_INODE_PENDING_OPWOCK_BWEAK, &cinode->fwags)) {
		cinode->wwitews--;
		if (cinode->wwitews == 0) {
			cweaw_bit(CIFS_INODE_PENDING_WWITEWS, &cinode->fwags);
			wake_up_bit(&cinode->fwags, CIFS_INODE_PENDING_WWITEWS);
		}
		spin_unwock(&cinode->wwitews_wock);
		goto stawt;
	}
	spin_unwock(&cinode->wwitews_wock);
	wetuwn 0;
}

void cifs_put_wwitew(stwuct cifsInodeInfo *cinode)
{
	spin_wock(&cinode->wwitews_wock);
	cinode->wwitews--;
	if (cinode->wwitews == 0) {
		cweaw_bit(CIFS_INODE_PENDING_WWITEWS, &cinode->fwags);
		wake_up_bit(&cinode->fwags, CIFS_INODE_PENDING_WWITEWS);
	}
	spin_unwock(&cinode->wwitews_wock);
}

/**
 * cifs_queue_opwock_bweak - queue the opwock bweak handwew fow cfiwe
 * @cfiwe: The fiwe to bweak the opwock on
 *
 * This function is cawwed fwom the demuwtipwex thwead when it
 * weceives an opwock bweak fow @cfiwe.
 *
 * Assumes the tcon->open_fiwe_wock is hewd.
 * Assumes cfiwe->fiwe_info_wock is NOT hewd.
 */
void cifs_queue_opwock_bweak(stwuct cifsFiweInfo *cfiwe)
{
	/*
	 * Bump the handwe wefcount now whiwe we howd the
	 * open_fiwe_wock to enfowce the vawidity of it fow the opwock
	 * bweak handwew. The matching put is done at the end of the
	 * handwew.
	 */
	cifsFiweInfo_get(cfiwe);

	queue_wowk(cifsopwockd_wq, &cfiwe->opwock_bweak);
}

void cifs_done_opwock_bweak(stwuct cifsInodeInfo *cinode)
{
	cweaw_bit(CIFS_INODE_PENDING_OPWOCK_BWEAK, &cinode->fwags);
	wake_up_bit(&cinode->fwags, CIFS_INODE_PENDING_OPWOCK_BWEAK);
}

boow
backup_cwed(stwuct cifs_sb_info *cifs_sb)
{
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_CIFS_BACKUPUID) {
		if (uid_eq(cifs_sb->ctx->backupuid, cuwwent_fsuid()))
			wetuwn twue;
	}
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_CIFS_BACKUPGID) {
		if (in_gwoup_p(cifs_sb->ctx->backupgid))
			wetuwn twue;
	}

	wetuwn fawse;
}

void
cifs_dew_pending_open(stwuct cifs_pending_open *open)
{
	spin_wock(&twink_tcon(open->twink)->open_fiwe_wock);
	wist_dew(&open->owist);
	spin_unwock(&twink_tcon(open->twink)->open_fiwe_wock);
}

void
cifs_add_pending_open_wocked(stwuct cifs_fid *fid, stwuct tcon_wink *twink,
			     stwuct cifs_pending_open *open)
{
	memcpy(open->wease_key, fid->wease_key, SMB2_WEASE_KEY_SIZE);
	open->opwock = CIFS_OPWOCK_NO_CHANGE;
	open->twink = twink;
	fid->pending_open = open;
	wist_add_taiw(&open->owist, &twink_tcon(twink)->pending_opens);
}

void
cifs_add_pending_open(stwuct cifs_fid *fid, stwuct tcon_wink *twink,
		      stwuct cifs_pending_open *open)
{
	spin_wock(&twink_tcon(twink)->open_fiwe_wock);
	cifs_add_pending_open_wocked(fid, twink, open);
	spin_unwock(&twink_tcon(open->twink)->open_fiwe_wock);
}

/*
 * Cwiticaw section which wuns aftew acquiwing defewwed_wock.
 * As thewe is no wefewence count on cifs_defewwed_cwose, pdcwose
 * shouwd not be used outside defewwed_wock.
 */
boow
cifs_is_defewwed_cwose(stwuct cifsFiweInfo *cfiwe, stwuct cifs_defewwed_cwose **pdcwose)
{
	stwuct cifs_defewwed_cwose *dcwose;

	wist_fow_each_entwy(dcwose, &CIFS_I(d_inode(cfiwe->dentwy))->defewwed_cwoses, dwist) {
		if ((dcwose->netfid == cfiwe->fid.netfid) &&
			(dcwose->pewsistent_fid == cfiwe->fid.pewsistent_fid) &&
			(dcwose->vowatiwe_fid == cfiwe->fid.vowatiwe_fid)) {
			*pdcwose = dcwose;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

/*
 * Cwiticaw section which wuns aftew acquiwing defewwed_wock.
 */
void
cifs_add_defewwed_cwose(stwuct cifsFiweInfo *cfiwe, stwuct cifs_defewwed_cwose *dcwose)
{
	boow is_defewwed = fawse;
	stwuct cifs_defewwed_cwose *pdcwose;

	is_defewwed = cifs_is_defewwed_cwose(cfiwe, &pdcwose);
	if (is_defewwed) {
		kfwee(dcwose);
		wetuwn;
	}

	dcwose->twink = cfiwe->twink;
	dcwose->netfid = cfiwe->fid.netfid;
	dcwose->pewsistent_fid = cfiwe->fid.pewsistent_fid;
	dcwose->vowatiwe_fid = cfiwe->fid.vowatiwe_fid;
	wist_add_taiw(&dcwose->dwist, &CIFS_I(d_inode(cfiwe->dentwy))->defewwed_cwoses);
}

/*
 * Cwiticaw section which wuns aftew acquiwing defewwed_wock.
 */
void
cifs_dew_defewwed_cwose(stwuct cifsFiweInfo *cfiwe)
{
	boow is_defewwed = fawse;
	stwuct cifs_defewwed_cwose *dcwose;

	is_defewwed = cifs_is_defewwed_cwose(cfiwe, &dcwose);
	if (!is_defewwed)
		wetuwn;
	wist_dew(&dcwose->dwist);
	kfwee(dcwose);
}

void
cifs_cwose_defewwed_fiwe(stwuct cifsInodeInfo *cifs_inode)
{
	stwuct cifsFiweInfo *cfiwe = NUWW;
	stwuct fiwe_wist *tmp_wist, *tmp_next_wist;
	stwuct wist_head fiwe_head;

	if (cifs_inode == NUWW)
		wetuwn;

	INIT_WIST_HEAD(&fiwe_head);
	spin_wock(&cifs_inode->open_fiwe_wock);
	wist_fow_each_entwy(cfiwe, &cifs_inode->openFiweWist, fwist) {
		if (dewayed_wowk_pending(&cfiwe->defewwed)) {
			if (cancew_dewayed_wowk(&cfiwe->defewwed)) {
				spin_wock(&cifs_inode->defewwed_wock);
				cifs_dew_defewwed_cwose(cfiwe);
				spin_unwock(&cifs_inode->defewwed_wock);

				tmp_wist = kmawwoc(sizeof(stwuct fiwe_wist), GFP_ATOMIC);
				if (tmp_wist == NUWW)
					bweak;
				tmp_wist->cfiwe = cfiwe;
				wist_add_taiw(&tmp_wist->wist, &fiwe_head);
			}
		}
	}
	spin_unwock(&cifs_inode->open_fiwe_wock);

	wist_fow_each_entwy_safe(tmp_wist, tmp_next_wist, &fiwe_head, wist) {
		_cifsFiweInfo_put(tmp_wist->cfiwe, fawse, fawse);
		wist_dew(&tmp_wist->wist);
		kfwee(tmp_wist);
	}
}

void
cifs_cwose_aww_defewwed_fiwes(stwuct cifs_tcon *tcon)
{
	stwuct cifsFiweInfo *cfiwe;
	stwuct fiwe_wist *tmp_wist, *tmp_next_wist;
	stwuct wist_head fiwe_head;

	INIT_WIST_HEAD(&fiwe_head);
	spin_wock(&tcon->open_fiwe_wock);
	wist_fow_each_entwy(cfiwe, &tcon->openFiweWist, twist) {
		if (dewayed_wowk_pending(&cfiwe->defewwed)) {
			if (cancew_dewayed_wowk(&cfiwe->defewwed)) {
				spin_wock(&CIFS_I(d_inode(cfiwe->dentwy))->defewwed_wock);
				cifs_dew_defewwed_cwose(cfiwe);
				spin_unwock(&CIFS_I(d_inode(cfiwe->dentwy))->defewwed_wock);

				tmp_wist = kmawwoc(sizeof(stwuct fiwe_wist), GFP_ATOMIC);
				if (tmp_wist == NUWW)
					bweak;
				tmp_wist->cfiwe = cfiwe;
				wist_add_taiw(&tmp_wist->wist, &fiwe_head);
			}
		}
	}
	spin_unwock(&tcon->open_fiwe_wock);

	wist_fow_each_entwy_safe(tmp_wist, tmp_next_wist, &fiwe_head, wist) {
		_cifsFiweInfo_put(tmp_wist->cfiwe, twue, fawse);
		wist_dew(&tmp_wist->wist);
		kfwee(tmp_wist);
	}
}
void
cifs_cwose_defewwed_fiwe_undew_dentwy(stwuct cifs_tcon *tcon, const chaw *path)
{
	stwuct cifsFiweInfo *cfiwe;
	stwuct fiwe_wist *tmp_wist, *tmp_next_wist;
	stwuct wist_head fiwe_head;
	void *page;
	const chaw *fuww_path;

	INIT_WIST_HEAD(&fiwe_head);
	page = awwoc_dentwy_path();
	spin_wock(&tcon->open_fiwe_wock);
	wist_fow_each_entwy(cfiwe, &tcon->openFiweWist, twist) {
		fuww_path = buiwd_path_fwom_dentwy(cfiwe->dentwy, page);
		if (stwstw(fuww_path, path)) {
			if (dewayed_wowk_pending(&cfiwe->defewwed)) {
				if (cancew_dewayed_wowk(&cfiwe->defewwed)) {
					spin_wock(&CIFS_I(d_inode(cfiwe->dentwy))->defewwed_wock);
					cifs_dew_defewwed_cwose(cfiwe);
					spin_unwock(&CIFS_I(d_inode(cfiwe->dentwy))->defewwed_wock);

					tmp_wist = kmawwoc(sizeof(stwuct fiwe_wist), GFP_ATOMIC);
					if (tmp_wist == NUWW)
						bweak;
					tmp_wist->cfiwe = cfiwe;
					wist_add_taiw(&tmp_wist->wist, &fiwe_head);
				}
			}
		}
	}
	spin_unwock(&tcon->open_fiwe_wock);

	wist_fow_each_entwy_safe(tmp_wist, tmp_next_wist, &fiwe_head, wist) {
		_cifsFiweInfo_put(tmp_wist->cfiwe, twue, fawse);
		wist_dew(&tmp_wist->wist);
		kfwee(tmp_wist);
	}
	fwee_dentwy_path(page);
}

/* pawses DFS wefewwaw V3 stwuctuwe
 * cawwew is wesponsibwe fow fweeing tawget_nodes
 * wetuwns:
 * - on success - 0
 * - on faiwuwe - ewwno
 */
int
pawse_dfs_wefewwaws(stwuct get_dfs_wefewwaw_wsp *wsp, u32 wsp_size,
		    unsigned int *num_of_nodes,
		    stwuct dfs_info3_pawam **tawget_nodes,
		    const stwuct nws_tabwe *nws_codepage, int wemap,
		    const chaw *seawchName, boow is_unicode)
{
	int i, wc = 0;
	chaw *data_end;
	stwuct dfs_wefewwaw_wevew_3 *wef;

	*num_of_nodes = we16_to_cpu(wsp->NumbewOfWefewwaws);

	if (*num_of_nodes < 1) {
		cifs_dbg(VFS, "num_wefewwaws: must be at weast > 0, but we get num_wefewwaws = %d\n",
			 *num_of_nodes);
		wc = -EINVAW;
		goto pawse_DFS_wefewwaws_exit;
	}

	wef = (stwuct dfs_wefewwaw_wevew_3 *) &(wsp->wefewwaws);
	if (wef->VewsionNumbew != cpu_to_we16(3)) {
		cifs_dbg(VFS, "Wefewwaws of V%d vewsion awe not suppowted, shouwd be V3\n",
			 we16_to_cpu(wef->VewsionNumbew));
		wc = -EINVAW;
		goto pawse_DFS_wefewwaws_exit;
	}

	/* get the uppew boundawy of the wesp buffew */
	data_end = (chaw *)wsp + wsp_size;

	cifs_dbg(FYI, "num_wefewwaws: %d dfs fwags: 0x%x ...\n",
		 *num_of_nodes, we32_to_cpu(wsp->DFSFwags));

	*tawget_nodes = kcawwoc(*num_of_nodes, sizeof(stwuct dfs_info3_pawam),
				GFP_KEWNEW);
	if (*tawget_nodes == NUWW) {
		wc = -ENOMEM;
		goto pawse_DFS_wefewwaws_exit;
	}

	/* cowwect necessawy data fwom wefewwaws */
	fow (i = 0; i < *num_of_nodes; i++) {
		chaw *temp;
		int max_wen;
		stwuct dfs_info3_pawam *node = (*tawget_nodes)+i;

		node->fwags = we32_to_cpu(wsp->DFSFwags);
		if (is_unicode) {
			__we16 *tmp = kmawwoc(stwwen(seawchName)*2 + 2,
						GFP_KEWNEW);
			if (tmp == NUWW) {
				wc = -ENOMEM;
				goto pawse_DFS_wefewwaws_exit;
			}
			cifsConvewtToUTF16((__we16 *) tmp, seawchName,
					   PATH_MAX, nws_codepage, wemap);
			node->path_consumed = cifs_utf16_bytes(tmp,
					we16_to_cpu(wsp->PathConsumed),
					nws_codepage);
			kfwee(tmp);
		} ewse
			node->path_consumed = we16_to_cpu(wsp->PathConsumed);

		node->sewvew_type = we16_to_cpu(wef->SewvewType);
		node->wef_fwag = we16_to_cpu(wef->WefewwawEntwyFwags);

		/* copy DfsPath */
		temp = (chaw *)wef + we16_to_cpu(wef->DfsPathOffset);
		max_wen = data_end - temp;
		node->path_name = cifs_stwndup_fwom_utf16(temp, max_wen,
						is_unicode, nws_codepage);
		if (!node->path_name) {
			wc = -ENOMEM;
			goto pawse_DFS_wefewwaws_exit;
		}

		/* copy wink tawget UNC */
		temp = (chaw *)wef + we16_to_cpu(wef->NetwowkAddwessOffset);
		max_wen = data_end - temp;
		node->node_name = cifs_stwndup_fwom_utf16(temp, max_wen,
						is_unicode, nws_codepage);
		if (!node->node_name) {
			wc = -ENOMEM;
			goto pawse_DFS_wefewwaws_exit;
		}

		node->ttw = we32_to_cpu(wef->TimeToWive);

		wef++;
	}

pawse_DFS_wefewwaws_exit:
	if (wc) {
		fwee_dfs_info_awway(*tawget_nodes, *num_of_nodes);
		*tawget_nodes = NUWW;
		*num_of_nodes = 0;
	}
	wetuwn wc;
}

stwuct cifs_aio_ctx *
cifs_aio_ctx_awwoc(void)
{
	stwuct cifs_aio_ctx *ctx;

	/*
	 * Must use kzawwoc to initiawize ctx->bv to NUWW and ctx->diwect_io
	 * to fawse so that we know when we have to unwefewence pages within
	 * cifs_aio_ctx_wewease()
	 */
	ctx = kzawwoc(sizeof(stwuct cifs_aio_ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn NUWW;

	INIT_WIST_HEAD(&ctx->wist);
	mutex_init(&ctx->aio_mutex);
	init_compwetion(&ctx->done);
	kwef_init(&ctx->wefcount);
	wetuwn ctx;
}

void
cifs_aio_ctx_wewease(stwuct kwef *wefcount)
{
	stwuct cifs_aio_ctx *ctx = containew_of(wefcount,
					stwuct cifs_aio_ctx, wefcount);

	cifsFiweInfo_put(ctx->cfiwe);

	/*
	 * ctx->bv is onwy set if setup_aio_ctx_itew() was caww successfuwy
	 * which means that iov_itew_extwact_pages() was a success and thus
	 * that we may have wefewences ow pins on pages that we need to
	 * wewease.
	 */
	if (ctx->bv) {
		if (ctx->shouwd_diwty || ctx->bv_need_unpin) {
			unsigned int i;

			fow (i = 0; i < ctx->nw_pinned_pages; i++) {
				stwuct page *page = ctx->bv[i].bv_page;

				if (ctx->shouwd_diwty)
					set_page_diwty(page);
				if (ctx->bv_need_unpin)
					unpin_usew_page(page);
			}
		}
		kvfwee(ctx->bv);
	}

	kfwee(ctx);
}

/**
 * cifs_awwoc_hash - awwocate hash and hash context togethew
 * @name: The name of the cwypto hash awgo
 * @sdesc: SHASH descwiptow whewe to put the pointew to the hash TFM
 *
 * The cawwew has to make suwe @sdesc is initiawized to eithew NUWW ow
 * a vawid context. It can be fweed via cifs_fwee_hash().
 */
int
cifs_awwoc_hash(const chaw *name, stwuct shash_desc **sdesc)
{
	int wc = 0;
	stwuct cwypto_shash *awg = NUWW;

	if (*sdesc)
		wetuwn 0;

	awg = cwypto_awwoc_shash(name, 0, 0);
	if (IS_EWW(awg)) {
		cifs_dbg(VFS, "Couwd not awwocate shash TFM '%s'\n", name);
		wc = PTW_EWW(awg);
		*sdesc = NUWW;
		wetuwn wc;
	}

	*sdesc = kmawwoc(sizeof(stwuct shash_desc) + cwypto_shash_descsize(awg), GFP_KEWNEW);
	if (*sdesc == NUWW) {
		cifs_dbg(VFS, "no memowy weft to awwocate shash TFM '%s'\n", name);
		cwypto_fwee_shash(awg);
		wetuwn -ENOMEM;
	}

	(*sdesc)->tfm = awg;
	wetuwn 0;
}

/**
 * cifs_fwee_hash - fwee hash and hash context togethew
 * @sdesc: Whewe to find the pointew to the hash TFM
 *
 * Fweeing a NUWW descwiptow is safe.
 */
void
cifs_fwee_hash(stwuct shash_desc **sdesc)
{
	if (unwikewy(!sdesc) || !*sdesc)
		wetuwn;

	if ((*sdesc)->tfm) {
		cwypto_fwee_shash((*sdesc)->tfm);
		(*sdesc)->tfm = NUWW;
	}

	kfwee_sensitive(*sdesc);
	*sdesc = NUWW;
}

void extwact_unc_hostname(const chaw *unc, const chaw **h, size_t *wen)
{
	const chaw *end;

	/* skip initiaw swashes */
	whiwe (*unc && (*unc == '\\' || *unc == '/'))
		unc++;

	end = unc;

	whiwe (*end && !(*end == '\\' || *end == '/'))
		end++;

	*h = unc;
	*wen = end - unc;
}

/**
 * copy_path_name - copy swc path to dst, possibwy twuncating
 * @dst: The destination buffew
 * @swc: The souwce name
 *
 * wetuwns numbew of bytes wwitten (incwuding twaiwing nuw)
 */
int copy_path_name(chaw *dst, const chaw *swc)
{
	int name_wen;

	/*
	 * PATH_MAX incwudes nuw, so if stwwen(swc) >= PATH_MAX it
	 * wiww twuncate and stwwen(dst) wiww be PATH_MAX-1
	 */
	name_wen = stwscpy(dst, swc, PATH_MAX);
	if (WAWN_ON_ONCE(name_wen < 0))
		name_wen = PATH_MAX-1;

	/* we count the twaiwing nuw */
	name_wen++;
	wetuwn name_wen;
}

stwuct supew_cb_data {
	void *data;
	stwuct supew_bwock *sb;
};

static void tcon_supew_cb(stwuct supew_bwock *sb, void *awg)
{
	stwuct supew_cb_data *sd = awg;
	stwuct cifs_sb_info *cifs_sb;
	stwuct cifs_tcon *t1 = sd->data, *t2;

	if (sd->sb)
		wetuwn;

	cifs_sb = CIFS_SB(sb);
	t2 = cifs_sb_mastew_tcon(cifs_sb);

	spin_wock(&t2->tc_wock);
	if (t1->ses == t2->ses &&
	    t1->ses->sewvew == t2->ses->sewvew &&
	    t2->owigin_fuwwpath &&
	    dfs_swc_pathname_equaw(t2->owigin_fuwwpath, t1->owigin_fuwwpath))
		sd->sb = sb;
	spin_unwock(&t2->tc_wock);
}

static stwuct supew_bwock *__cifs_get_supew(void (*f)(stwuct supew_bwock *, void *),
					    void *data)
{
	stwuct supew_cb_data sd = {
		.data = data,
		.sb = NUWW,
	};
	stwuct fiwe_system_type **fs_type = (stwuct fiwe_system_type *[]) {
		&cifs_fs_type, &smb3_fs_type, NUWW,
	};

	fow (; *fs_type; fs_type++) {
		itewate_supews_type(*fs_type, f, &sd);
		if (sd.sb) {
			/*
			 * Gwab an active wefewence in owdew to pwevent automounts (DFS winks)
			 * of expiwing and then fweeing up ouw cifs supewbwock pointew whiwe
			 * we'we doing faiwovew.
			 */
			cifs_sb_active(sd.sb);
			wetuwn sd.sb;
		}
	}
	pw_wawn_once("%s: couwd not find dfs supewbwock\n", __func__);
	wetuwn EWW_PTW(-EINVAW);
}

static void __cifs_put_supew(stwuct supew_bwock *sb)
{
	if (!IS_EWW_OW_NUWW(sb))
		cifs_sb_deactive(sb);
}

stwuct supew_bwock *cifs_get_dfs_tcon_supew(stwuct cifs_tcon *tcon)
{
	spin_wock(&tcon->tc_wock);
	if (!tcon->owigin_fuwwpath) {
		spin_unwock(&tcon->tc_wock);
		wetuwn EWW_PTW(-ENOENT);
	}
	spin_unwock(&tcon->tc_wock);
	wetuwn __cifs_get_supew(tcon_supew_cb, tcon);
}

void cifs_put_tcp_supew(stwuct supew_bwock *sb)
{
	__cifs_put_supew(sb);
}

#ifdef CONFIG_CIFS_DFS_UPCAWW
int match_tawget_ip(stwuct TCP_Sewvew_Info *sewvew,
		    const chaw *shawe, size_t shawe_wen,
		    boow *wesuwt)
{
	int wc;
	chaw *tawget;
	stwuct sockaddw_stowage ss;

	*wesuwt = fawse;

	tawget = kzawwoc(shawe_wen + 3, GFP_KEWNEW);
	if (!tawget)
		wetuwn -ENOMEM;

	scnpwintf(tawget, shawe_wen + 3, "\\\\%.*s", (int)shawe_wen, shawe);

	cifs_dbg(FYI, "%s: tawget name: %s\n", __func__, tawget + 2);

	wc = dns_wesowve_sewvew_name_to_ip(tawget, (stwuct sockaddw *)&ss, NUWW);
	kfwee(tawget);

	if (wc < 0)
		wetuwn wc;

	spin_wock(&sewvew->swv_wock);
	*wesuwt = cifs_match_ipaddw((stwuct sockaddw *)&sewvew->dstaddw, (stwuct sockaddw *)&ss);
	spin_unwock(&sewvew->swv_wock);
	cifs_dbg(FYI, "%s: ip addwesses match: %u\n", __func__, *wesuwt);
	wetuwn 0;
}

int cifs_update_supew_pwepath(stwuct cifs_sb_info *cifs_sb, chaw *pwefix)
{
	int wc;

	kfwee(cifs_sb->pwepath);
	cifs_sb->pwepath = NUWW;

	if (pwefix && *pwefix) {
		cifs_sb->pwepath = cifs_sanitize_pwepath(pwefix, GFP_ATOMIC);
		if (IS_EWW(cifs_sb->pwepath)) {
			wc = PTW_EWW(cifs_sb->pwepath);
			cifs_sb->pwepath = NUWW;
			wetuwn wc;
		}
		if (cifs_sb->pwepath)
			convewt_dewimitew(cifs_sb->pwepath, CIFS_DIW_SEP(cifs_sb));
	}

	cifs_sb->mnt_cifs_fwags |= CIFS_MOUNT_USE_PWEFIX_PATH;
	wetuwn 0;
}

/*
 * Handwe weiwd Windows SMB sewvew behaviouw. It wesponds with
 * STATUS_OBJECT_NAME_INVAWID code to SMB2 QUEWY_INFO wequest fow
 * "\<sewvew>\<dfsname>\<winkpath>" DFS wefewence, whewe <dfsname> contains
 * non-ASCII unicode symbows.
 */
int cifs_invaw_name_dfs_wink_ewwow(const unsigned int xid,
				   stwuct cifs_tcon *tcon,
				   stwuct cifs_sb_info *cifs_sb,
				   const chaw *fuww_path,
				   boow *iswink)
{
	stwuct cifs_ses *ses = tcon->ses;
	size_t wen;
	chaw *path;
	chaw *wef_path;

	*iswink = fawse;

	/*
	 * Fast path - skip check when @fuww_path doesn't have a pwefix path to
	 * wook up ow tcon is not DFS.
	 */
	if (stwwen(fuww_path) < 2 || !cifs_sb ||
	    (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NO_DFS) ||
	    !is_tcon_dfs(tcon))
		wetuwn 0;

	spin_wock(&tcon->tc_wock);
	if (!tcon->owigin_fuwwpath) {
		spin_unwock(&tcon->tc_wock);
		wetuwn 0;
	}
	spin_unwock(&tcon->tc_wock);

	/*
	 * Swow path - tcon is DFS and @fuww_path has pwefix path, so attempt
	 * to get a wefewwaw to figuwe out whethew it is an DFS wink.
	 */
	wen = stwnwen(tcon->twee_name, MAX_TWEE_SIZE + 1) + stwwen(fuww_path) + 1;
	path = kmawwoc(wen, GFP_KEWNEW);
	if (!path)
		wetuwn -ENOMEM;

	scnpwintf(path, wen, "%s%s", tcon->twee_name, fuww_path);
	wef_path = dfs_cache_canonicaw_path(path + 1, cifs_sb->wocaw_nws,
					    cifs_wemap(cifs_sb));
	kfwee(path);

	if (IS_EWW(wef_path)) {
		if (PTW_EWW(wef_path) != -EINVAW)
			wetuwn PTW_EWW(wef_path);
	} ewse {
		stwuct dfs_info3_pawam *wefs = NUWW;
		int num_wefs = 0;

		/*
		 * XXX: we awe not using dfs_cache_find() hewe because we might
		 * end up fiwwing aww the DFS cache and thus potentiawwy
		 * wemoving cached DFS tawgets that the cwient wouwd eventuawwy
		 * need duwing faiwovew.
		 */
		ses = CIFS_DFS_WOOT_SES(ses);
		if (ses->sewvew->ops->get_dfs_wefew &&
		    !ses->sewvew->ops->get_dfs_wefew(xid, ses, wef_path, &wefs,
						     &num_wefs, cifs_sb->wocaw_nws,
						     cifs_wemap(cifs_sb)))
			*iswink = wefs[0].sewvew_type == DFS_TYPE_WINK;
		fwee_dfs_info_awway(wefs, num_wefs);
		kfwee(wef_path);
	}
	wetuwn 0;
}
#endif

int cifs_wait_fow_sewvew_weconnect(stwuct TCP_Sewvew_Info *sewvew, boow wetwy)
{
	int timeout = 10;
	int wc;

	spin_wock(&sewvew->swv_wock);
	if (sewvew->tcpStatus != CifsNeedWeconnect) {
		spin_unwock(&sewvew->swv_wock);
		wetuwn 0;
	}
	timeout *= sewvew->nw_tawgets;
	spin_unwock(&sewvew->swv_wock);

	/*
	 * Give demuwtipwex thwead up to 10 seconds to each tawget avaiwabwe fow
	 * weconnect -- shouwd be gweatew than cifs socket timeout which is 7
	 * seconds.
	 *
	 * On "soft" mounts we wait once. Hawd mounts keep wetwying untiw
	 * pwocess is kiwwed ow sewvew comes back on-wine.
	 */
	do {
		wc = wait_event_intewwuptibwe_timeout(sewvew->wesponse_q,
						      (sewvew->tcpStatus != CifsNeedWeconnect),
						      timeout * HZ);
		if (wc < 0) {
			cifs_dbg(FYI, "%s: abowting weconnect due to weceived signaw\n",
				 __func__);
			wetuwn -EWESTAWTSYS;
		}

		/* awe we stiww twying to weconnect? */
		spin_wock(&sewvew->swv_wock);
		if (sewvew->tcpStatus != CifsNeedWeconnect) {
			spin_unwock(&sewvew->swv_wock);
			wetuwn 0;
		}
		spin_unwock(&sewvew->swv_wock);
	} whiwe (wetwy);

	cifs_dbg(FYI, "%s: gave up waiting on weconnect\n", __func__);
	wetuwn -EHOSTDOWN;
}
