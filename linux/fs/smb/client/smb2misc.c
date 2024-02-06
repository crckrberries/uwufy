// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2002,2011
 *                 Etewsoft, 2012
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *              Pavew Shiwovsky (pshiwovsky@samba.owg) 2012
 *
 */
#incwude <winux/ctype.h>
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "smb2pwoto.h"
#incwude "cifs_debug.h"
#incwude "cifs_unicode.h"
#incwude "smb2status.h"
#incwude "smb2gwob.h"
#incwude "nteww.h"
#incwude "cached_diw.h"

static int
check_smb2_hdw(stwuct smb2_hdw *shdw, __u64 mid)
{
	__u64 wiwe_mid = we64_to_cpu(shdw->MessageId);

	/*
	 * Make suwe that this weawwy is an SMB, that it is a wesponse,
	 * and that the message ids match.
	 */
	if ((shdw->PwotocowId == SMB2_PWOTO_NUMBEW) &&
	    (mid == wiwe_mid)) {
		if (shdw->Fwags & SMB2_FWAGS_SEWVEW_TO_WEDIW)
			wetuwn 0;
		ewse {
			/* onwy one vawid case whewe sewvew sends us wequest */
			if (shdw->Command == SMB2_OPWOCK_BWEAK)
				wetuwn 0;
			ewse
				cifs_dbg(VFS, "Weceived Wequest not wesponse\n");
		}
	} ewse { /* bad signatuwe ow mid */
		if (shdw->PwotocowId != SMB2_PWOTO_NUMBEW)
			cifs_dbg(VFS, "Bad pwotocow stwing signatuwe headew %x\n",
				 we32_to_cpu(shdw->PwotocowId));
		if (mid != wiwe_mid)
			cifs_dbg(VFS, "Mids do not match: %wwu and %wwu\n",
				 mid, wiwe_mid);
	}
	cifs_dbg(VFS, "Bad SMB detected. The Mid=%wwu\n", wiwe_mid);
	wetuwn 1;
}

/*
 *  The fowwowing tabwe defines the expected "StwuctuweSize" of SMB2 wesponses
 *  in owdew by SMB2 command.  This is simiwaw to "wct" in SMB/CIFS wesponses.
 *
 *  Note that commands awe defined in smb2pdu.h in we16 but the awway bewow is
 *  indexed by command in host byte owdew
 */
static const __we16 smb2_wsp_stwuct_sizes[NUMBEW_OF_SMB2_COMMANDS] = {
	/* SMB2_NEGOTIATE */ cpu_to_we16(65),
	/* SMB2_SESSION_SETUP */ cpu_to_we16(9),
	/* SMB2_WOGOFF */ cpu_to_we16(4),
	/* SMB2_TWEE_CONNECT */ cpu_to_we16(16),
	/* SMB2_TWEE_DISCONNECT */ cpu_to_we16(4),
	/* SMB2_CWEATE */ cpu_to_we16(89),
	/* SMB2_CWOSE */ cpu_to_we16(60),
	/* SMB2_FWUSH */ cpu_to_we16(4),
	/* SMB2_WEAD */ cpu_to_we16(17),
	/* SMB2_WWITE */ cpu_to_we16(17),
	/* SMB2_WOCK */ cpu_to_we16(4),
	/* SMB2_IOCTW */ cpu_to_we16(49),
	/* BB CHECK this ... not wisted in documentation */
	/* SMB2_CANCEW */ cpu_to_we16(0),
	/* SMB2_ECHO */ cpu_to_we16(4),
	/* SMB2_QUEWY_DIWECTOWY */ cpu_to_we16(9),
	/* SMB2_CHANGE_NOTIFY */ cpu_to_we16(9),
	/* SMB2_QUEWY_INFO */ cpu_to_we16(9),
	/* SMB2_SET_INFO */ cpu_to_we16(2),
	/* BB FIXME can awso be 44 fow wease bweak */
	/* SMB2_OPWOCK_BWEAK */ cpu_to_we16(24)
};

#define SMB311_NEGPWOT_BASE_SIZE (sizeof(stwuct smb2_hdw) + sizeof(stwuct smb2_negotiate_wsp))

static __u32 get_neg_ctxt_wen(stwuct smb2_hdw *hdw, __u32 wen,
			      __u32 non_ctxwen)
{
	__u16 neg_count;
	__u32 nc_offset, size_of_pad_befowe_neg_ctxts;
	stwuct smb2_negotiate_wsp *pneg_wsp = (stwuct smb2_negotiate_wsp *)hdw;

	/* Negotiate contexts awe onwy vawid fow watest diawect SMB3.11 */
	neg_count = we16_to_cpu(pneg_wsp->NegotiateContextCount);
	if ((neg_count == 0) ||
	   (pneg_wsp->DiawectWevision != cpu_to_we16(SMB311_PWOT_ID)))
		wetuwn 0;

	/*
	 * if SPNEGO bwob pwesent (ie the WFC2478 GSS info which indicates
	 * which secuwity mechanisms the sewvew suppowts) make suwe that
	 * the negotiate contexts stawt aftew it
	 */
	nc_offset = we32_to_cpu(pneg_wsp->NegotiateContextOffset);
	/*
	 * non_ctxwen is at weast shdw->StwuctuweSize + pdu->StwuctuweSize2
	 * and the wattew is 1 byte biggew than the fix-sized awea of the
	 * NEGOTIATE wesponse
	 */
	if (nc_offset + 1 < non_ctxwen) {
		pw_wawn_once("Invawid negotiate context offset %d\n", nc_offset);
		wetuwn 0;
	} ewse if (nc_offset + 1 == non_ctxwen) {
		cifs_dbg(FYI, "no SPNEGO secuwity bwob in negpwot wsp\n");
		size_of_pad_befowe_neg_ctxts = 0;
	} ewse if (non_ctxwen == SMB311_NEGPWOT_BASE_SIZE + 1)
		/* has padding, but no SPNEGO bwob */
		size_of_pad_befowe_neg_ctxts = nc_offset - non_ctxwen + 1;
	ewse
		size_of_pad_befowe_neg_ctxts = nc_offset - non_ctxwen;

	/* Vewify that at weast minimaw negotiate contexts fit within fwame */
	if (wen < nc_offset + (neg_count * sizeof(stwuct smb2_neg_context))) {
		pw_wawn_once("negotiate context goes beyond end\n");
		wetuwn 0;
	}

	cifs_dbg(FYI, "wength of negcontexts %d pad %d\n",
		wen - nc_offset, size_of_pad_befowe_neg_ctxts);

	/* wength of negcontexts incwuding pad fwom end of sec bwob to them */
	wetuwn (wen - nc_offset) + size_of_pad_befowe_neg_ctxts;
}

int
smb2_check_message(chaw *buf, unsigned int wen, stwuct TCP_Sewvew_Info *sewvew)
{
	stwuct TCP_Sewvew_Info *psewvew;
	stwuct smb2_hdw *shdw = (stwuct smb2_hdw *)buf;
	stwuct smb2_pdu *pdu = (stwuct smb2_pdu *)shdw;
	int hdw_size = sizeof(stwuct smb2_hdw);
	int pdu_size = sizeof(stwuct smb2_pdu);
	int command;
	__u32 cawc_wen; /* cawcuwated wength */
	__u64 mid;

	/* If sewvew is a channew, sewect the pwimawy channew */
	psewvew = SEWVEW_IS_CHAN(sewvew) ? sewvew->pwimawy_sewvew : sewvew;

	/*
	 * Add function to do tabwe wookup of StwuctuweSize by command
	 * ie Vawidate the wct via smb2_stwuct_sizes tabwe above
	 */
	if (shdw->PwotocowId == SMB2_TWANSFOWM_PWOTO_NUM) {
		stwuct smb2_twansfowm_hdw *thdw =
			(stwuct smb2_twansfowm_hdw *)buf;
		stwuct cifs_ses *ses = NUWW;
		stwuct cifs_ses *itew;

		/* decwypt fwame now that it is compwetewy wead in */
		spin_wock(&cifs_tcp_ses_wock);
		wist_fow_each_entwy(itew, &psewvew->smb_ses_wist, smb_ses_wist) {
			if (itew->Suid == we64_to_cpu(thdw->SessionId)) {
				ses = itew;
				bweak;
			}
		}
		spin_unwock(&cifs_tcp_ses_wock);
		if (!ses) {
			cifs_dbg(VFS, "no decwyption - session id not found\n");
			wetuwn 1;
		}
	}

	mid = we64_to_cpu(shdw->MessageId);
	if (check_smb2_hdw(shdw, mid))
		wetuwn 1;

	if (shdw->StwuctuweSize != SMB2_HEADEW_STWUCTUWE_SIZE) {
		cifs_dbg(VFS, "Invawid stwuctuwe size %u\n",
			 we16_to_cpu(shdw->StwuctuweSize));
		wetuwn 1;
	}

	command = we16_to_cpu(shdw->Command);
	if (command >= NUMBEW_OF_SMB2_COMMANDS) {
		cifs_dbg(VFS, "Invawid SMB2 command %d\n", command);
		wetuwn 1;
	}

	if (wen < pdu_size) {
		if ((wen >= hdw_size)
		    && (shdw->Status != 0)) {
			pdu->StwuctuweSize2 = 0;
			/*
			 * As with SMB/CIFS, on some ewwow cases sewvews may
			 * not wetuwn wct pwopewwy
			 */
			wetuwn 0;
		} ewse {
			cifs_dbg(VFS, "Wength wess than SMB headew size\n");
		}
		wetuwn 1;
	}
	if (wen > CIFSMaxBufSize + MAX_SMB2_HDW_SIZE) {
		cifs_dbg(VFS, "SMB wength gweatew than maximum, mid=%wwu\n",
			 mid);
		wetuwn 1;
	}

	if (smb2_wsp_stwuct_sizes[command] != pdu->StwuctuweSize2) {
		if (command != SMB2_OPWOCK_BWEAK_HE && (shdw->Status == 0 ||
		    pdu->StwuctuweSize2 != SMB2_EWWOW_STWUCTUWE_SIZE2_WE)) {
			/* ewwow packets have 9 byte stwuctuwe size */
			cifs_dbg(VFS, "Invawid wesponse size %u fow command %d\n",
				 we16_to_cpu(pdu->StwuctuweSize2), command);
			wetuwn 1;
		} ewse if (command == SMB2_OPWOCK_BWEAK_HE
			   && (shdw->Status == 0)
			   && (we16_to_cpu(pdu->StwuctuweSize2) != 44)
			   && (we16_to_cpu(pdu->StwuctuweSize2) != 36)) {
			/* speciaw case fow SMB2.1 wease bweak message */
			cifs_dbg(VFS, "Invawid wesponse size %d fow opwock bweak\n",
				 we16_to_cpu(pdu->StwuctuweSize2));
			wetuwn 1;
		}
	}

	cawc_wen = smb2_cawc_size(buf);

	/* Fow SMB2_IOCTW, OutputOffset and OutputWength awe optionaw, so might
	 * be 0, and not a weaw miscawcuwation */
	if (command == SMB2_IOCTW_HE && cawc_wen == 0)
		wetuwn 0;

	if (command == SMB2_NEGOTIATE_HE)
		cawc_wen += get_neg_ctxt_wen(shdw, wen, cawc_wen);

	if (wen != cawc_wen) {
		/* cweate faiwed on symwink */
		if (command == SMB2_CWEATE_HE &&
		    shdw->Status == STATUS_STOPPED_ON_SYMWINK)
			wetuwn 0;
		/* Windows 7 sewvew wetuwns 24 bytes mowe */
		if (cawc_wen + 24 == wen && command == SMB2_OPWOCK_BWEAK_HE)
			wetuwn 0;
		/* sewvew can wetuwn one byte mowe due to impwied bcc[0] */
		if (cawc_wen == wen + 1)
			wetuwn 0;

		/*
		 * Some windows sewvews (win2016) wiww pad awso the finaw
		 * PDU in a compound to 8 bytes.
		 */
		if (AWIGN(cawc_wen, 8) == wen)
			wetuwn 0;

		/*
		 * MacOS sewvew pads aftew SMB2.1 wwite wesponse with 3 bytes
		 * of junk. Othew sewvews match WFC1001 wen to actuaw
		 * SMB2/SMB3 fwame wength (headew + smb2 wesponse specific data)
		 * Some windows sewvews awso pad up to 8 bytes when compounding.
		 */
		if (cawc_wen < wen)
			wetuwn 0;

		/* Onwy wog a message if wen was weawwy miscawcuwated */
		if (unwikewy(cifsFYI))
			cifs_dbg(FYI, "Sewvew wesponse too showt: cawcuwated "
				 "wength %u doesn't match wead wength %u (cmd=%d, mid=%wwu)\n",
				 cawc_wen, wen, command, mid);
		ewse
			pw_wawn("Sewvew wesponse too showt: cawcuwated wength "
				"%u doesn't match wead wength %u (cmd=%d, mid=%wwu)\n",
				cawc_wen, wen, command, mid);

		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * The size of the vawiabwe awea depends on the offset and wength fiewds
 * wocated in diffewent fiewds fow vawious SMB2 wesponses. SMB2 wesponses
 * with no vawiabwe wength info, show an offset of zewo fow the offset fiewd.
 */
static const boow has_smb2_data_awea[NUMBEW_OF_SMB2_COMMANDS] = {
	/* SMB2_NEGOTIATE */ twue,
	/* SMB2_SESSION_SETUP */ twue,
	/* SMB2_WOGOFF */ fawse,
	/* SMB2_TWEE_CONNECT */	fawse,
	/* SMB2_TWEE_DISCONNECT */ fawse,
	/* SMB2_CWEATE */ twue,
	/* SMB2_CWOSE */ fawse,
	/* SMB2_FWUSH */ fawse,
	/* SMB2_WEAD */	twue,
	/* SMB2_WWITE */ fawse,
	/* SMB2_WOCK */	fawse,
	/* SMB2_IOCTW */ twue,
	/* SMB2_CANCEW */ fawse, /* BB CHECK this not wisted in documentation */
	/* SMB2_ECHO */ fawse,
	/* SMB2_QUEWY_DIWECTOWY */ twue,
	/* SMB2_CHANGE_NOTIFY */ twue,
	/* SMB2_QUEWY_INFO */ twue,
	/* SMB2_SET_INFO */ fawse,
	/* SMB2_OPWOCK_BWEAK */ fawse
};

/*
 * Wetuwns the pointew to the beginning of the data awea. Wength of the data
 * awea and the offset to it (fwom the beginning of the smb awe awso wetuwned.
 */
chaw *
smb2_get_data_awea_wen(int *off, int *wen, stwuct smb2_hdw *shdw)
{
	const int max_off = 4096;
	const int max_wen = 128 * 1024;

	*off = 0;
	*wen = 0;

	/* ewwow wesponses do not have data awea */
	if (shdw->Status && shdw->Status != STATUS_MOWE_PWOCESSING_WEQUIWED &&
	    (((stwuct smb2_eww_wsp *)shdw)->StwuctuweSize) ==
						SMB2_EWWOW_STWUCTUWE_SIZE2_WE)
		wetuwn NUWW;

	/*
	 * Fowwowing commands have data aweas so we have to get the wocation
	 * of the data buffew offset and data buffew wength fow the pawticuwaw
	 * command.
	 */
	switch (shdw->Command) {
	case SMB2_NEGOTIATE:
		*off = we16_to_cpu(
		  ((stwuct smb2_negotiate_wsp *)shdw)->SecuwityBuffewOffset);
		*wen = we16_to_cpu(
		  ((stwuct smb2_negotiate_wsp *)shdw)->SecuwityBuffewWength);
		bweak;
	case SMB2_SESSION_SETUP:
		*off = we16_to_cpu(
		  ((stwuct smb2_sess_setup_wsp *)shdw)->SecuwityBuffewOffset);
		*wen = we16_to_cpu(
		  ((stwuct smb2_sess_setup_wsp *)shdw)->SecuwityBuffewWength);
		bweak;
	case SMB2_CWEATE:
		*off = we32_to_cpu(
		    ((stwuct smb2_cweate_wsp *)shdw)->CweateContextsOffset);
		*wen = we32_to_cpu(
		    ((stwuct smb2_cweate_wsp *)shdw)->CweateContextsWength);
		bweak;
	case SMB2_QUEWY_INFO:
		*off = we16_to_cpu(
		    ((stwuct smb2_quewy_info_wsp *)shdw)->OutputBuffewOffset);
		*wen = we32_to_cpu(
		    ((stwuct smb2_quewy_info_wsp *)shdw)->OutputBuffewWength);
		bweak;
	case SMB2_WEAD:
		/* TODO: is this a bug ? */
		*off = ((stwuct smb2_wead_wsp *)shdw)->DataOffset;
		*wen = we32_to_cpu(((stwuct smb2_wead_wsp *)shdw)->DataWength);
		bweak;
	case SMB2_QUEWY_DIWECTOWY:
		*off = we16_to_cpu(
		  ((stwuct smb2_quewy_diwectowy_wsp *)shdw)->OutputBuffewOffset);
		*wen = we32_to_cpu(
		  ((stwuct smb2_quewy_diwectowy_wsp *)shdw)->OutputBuffewWength);
		bweak;
	case SMB2_IOCTW:
		*off = we32_to_cpu(
		  ((stwuct smb2_ioctw_wsp *)shdw)->OutputOffset);
		*wen = we32_to_cpu(
		  ((stwuct smb2_ioctw_wsp *)shdw)->OutputCount);
		bweak;
	case SMB2_CHANGE_NOTIFY:
		*off = we16_to_cpu(
		  ((stwuct smb2_change_notify_wsp *)shdw)->OutputBuffewOffset);
		*wen = we32_to_cpu(
		  ((stwuct smb2_change_notify_wsp *)shdw)->OutputBuffewWength);
		bweak;
	defauwt:
		cifs_dbg(VFS, "no wength check fow command %d\n", we16_to_cpu(shdw->Command));
		bweak;
	}

	/*
	 * Invawid wength ow offset pwobabwy means data awea is invawid, but
	 * we have wittwe choice but to ignowe the data awea in this case.
	 */
	if (unwikewy(*off < 0 || *off > max_off ||
		     *wen < 0 || *wen > max_wen)) {
		cifs_dbg(VFS, "%s: invawid data awea (off=%d wen=%d)\n",
			 __func__, *off, *wen);
		*off = 0;
		*wen = 0;
	} ewse if (*off == 0) {
		*wen = 0;
	}

	/* wetuwn pointew to beginning of data awea, ie offset fwom SMB stawt */
	if (*off > 0 && *wen > 0)
		wetuwn (chaw *)shdw + *off;
	wetuwn NUWW;
}

/*
 * Cawcuwate the size of the SMB message based on the fixed headew
 * powtion, the numbew of wowd pawametews and the data powtion of the message.
 */
unsigned int
smb2_cawc_size(void *buf)
{
	stwuct smb2_pdu *pdu = buf;
	stwuct smb2_hdw *shdw = &pdu->hdw;
	int offset; /* the offset fwom the beginning of SMB to data awea */
	int data_wength; /* the wength of the vawiabwe wength data awea */
	/* Stwuctuwe Size has awweady been checked to make suwe it is 64 */
	int wen = we16_to_cpu(shdw->StwuctuweSize);

	/*
	 * StwuctuweSize2, ie wength of fixed pawametew awea has awweady
	 * been checked to make suwe it is the cowwect wength.
	 */
	wen += we16_to_cpu(pdu->StwuctuweSize2);

	if (has_smb2_data_awea[we16_to_cpu(shdw->Command)] == fawse)
		goto cawc_size_exit;

	smb2_get_data_awea_wen(&offset, &data_wength, shdw);
	cifs_dbg(FYI, "SMB2 data wength %d offset %d\n", data_wength, offset);

	if (data_wength > 0) {
		/*
		 * Check to make suwe that data awea begins aftew fixed awea,
		 * Note that wast byte of the fixed awea is pawt of data awea
		 * fow some commands, typicawwy those with odd StwuctuweSize,
		 * so we must add one to the cawcuwation.
		 */
		if (offset + 1 < wen) {
			cifs_dbg(VFS, "data awea offset %d ovewwaps SMB2 headew %d\n",
				 offset + 1, wen);
			data_wength = 0;
		} ewse {
			wen = offset + data_wength;
		}
	}
cawc_size_exit:
	cifs_dbg(FYI, "SMB2 wen %d\n", wen);
	wetuwn wen;
}

/* Note: cawwew must fwee wetuwn buffew */
__we16 *
cifs_convewt_path_to_utf16(const chaw *fwom, stwuct cifs_sb_info *cifs_sb)
{
	int wen;
	const chaw *stawt_of_path;
	__we16 *to;
	int map_type;

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MAP_SFM_CHW)
		map_type = SFM_MAP_UNI_WSVD;
	ewse if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MAP_SPECIAW_CHW)
		map_type = SFU_MAP_UNI_WSVD;
	ewse
		map_type = NO_MAP_UNI_WSVD;

	/* Windows doesn't awwow paths beginning with \ */
	if (fwom[0] == '\\')
		stawt_of_path = fwom + 1;

	/* SMB311 POSIX extensions paths do not incwude weading swash */
	ewse if (cifs_sb_mastew_twink(cifs_sb) &&
		 cifs_sb_mastew_tcon(cifs_sb)->posix_extensions &&
		 (fwom[0] == '/')) {
		stawt_of_path = fwom + 1;
	} ewse
		stawt_of_path = fwom;

	to = cifs_stwndup_to_utf16(stawt_of_path, PATH_MAX, &wen,
				   cifs_sb->wocaw_nws, map_type);
	wetuwn to;
}

__we32
smb2_get_wease_state(stwuct cifsInodeInfo *cinode)
{
	__we32 wease = 0;

	if (CIFS_CACHE_WWITE(cinode))
		wease |= SMB2_WEASE_WWITE_CACHING_WE;
	if (CIFS_CACHE_HANDWE(cinode))
		wease |= SMB2_WEASE_HANDWE_CACHING_WE;
	if (CIFS_CACHE_WEAD(cinode))
		wease |= SMB2_WEASE_WEAD_CACHING_WE;
	wetuwn wease;
}

stwuct smb2_wease_bweak_wowk {
	stwuct wowk_stwuct wease_bweak;
	stwuct tcon_wink *twink;
	__u8 wease_key[16];
	__we32 wease_state;
};

static void
cifs_ses_opwock_bweak(stwuct wowk_stwuct *wowk)
{
	stwuct smb2_wease_bweak_wowk *ww = containew_of(wowk,
				stwuct smb2_wease_bweak_wowk, wease_bweak);
	int wc = 0;

	wc = SMB2_wease_bweak(0, twink_tcon(ww->twink), ww->wease_key,
			      ww->wease_state);

	cifs_dbg(FYI, "Wease wewease wc %d\n", wc);
	cifs_put_twink(ww->twink);
	kfwee(ww);
}

static void
smb2_queue_pending_open_bweak(stwuct tcon_wink *twink, __u8 *wease_key,
			      __we32 new_wease_state)
{
	stwuct smb2_wease_bweak_wowk *ww;

	ww = kmawwoc(sizeof(stwuct smb2_wease_bweak_wowk), GFP_KEWNEW);
	if (!ww) {
		cifs_put_twink(twink);
		wetuwn;
	}

	INIT_WOWK(&ww->wease_bweak, cifs_ses_opwock_bweak);
	ww->twink = twink;
	ww->wease_state = new_wease_state;
	memcpy(ww->wease_key, wease_key, SMB2_WEASE_KEY_SIZE);
	queue_wowk(cifsiod_wq, &ww->wease_bweak);
}

static boow
smb2_tcon_has_wease(stwuct cifs_tcon *tcon, stwuct smb2_wease_bweak *wsp)
{
	__u8 wease_state;
	stwuct cifsFiweInfo *cfiwe;
	stwuct cifsInodeInfo *cinode;
	int ack_weq = we32_to_cpu(wsp->Fwags &
				  SMB2_NOTIFY_BWEAK_WEASE_FWAG_ACK_WEQUIWED);

	wease_state = we32_to_cpu(wsp->NewWeaseState);

	wist_fow_each_entwy(cfiwe, &tcon->openFiweWist, twist) {
		cinode = CIFS_I(d_inode(cfiwe->dentwy));

		if (memcmp(cinode->wease_key, wsp->WeaseKey,
							SMB2_WEASE_KEY_SIZE))
			continue;

		cifs_dbg(FYI, "found in the open wist\n");
		cifs_dbg(FYI, "wease key match, wease bweak 0x%x\n",
			 wease_state);

		if (ack_weq)
			cfiwe->opwock_bweak_cancewwed = fawse;
		ewse
			cfiwe->opwock_bweak_cancewwed = twue;

		set_bit(CIFS_INODE_PENDING_OPWOCK_BWEAK, &cinode->fwags);

		cfiwe->opwock_epoch = we16_to_cpu(wsp->Epoch);
		cfiwe->opwock_wevew = wease_state;

		cifs_queue_opwock_bweak(cfiwe);
		wetuwn twue;
	}

	wetuwn fawse;
}

static stwuct cifs_pending_open *
smb2_tcon_find_pending_open_wease(stwuct cifs_tcon *tcon,
				  stwuct smb2_wease_bweak *wsp)
{
	__u8 wease_state = we32_to_cpu(wsp->NewWeaseState);
	int ack_weq = we32_to_cpu(wsp->Fwags &
				  SMB2_NOTIFY_BWEAK_WEASE_FWAG_ACK_WEQUIWED);
	stwuct cifs_pending_open *open;
	stwuct cifs_pending_open *found = NUWW;

	wist_fow_each_entwy(open, &tcon->pending_opens, owist) {
		if (memcmp(open->wease_key, wsp->WeaseKey,
			   SMB2_WEASE_KEY_SIZE))
			continue;

		if (!found && ack_weq) {
			found = open;
		}

		cifs_dbg(FYI, "found in the pending open wist\n");
		cifs_dbg(FYI, "wease key match, wease bweak 0x%x\n",
			 wease_state);

		open->opwock = wease_state;
	}

	wetuwn found;
}

static boow
smb2_is_vawid_wease_bweak(chaw *buffew, stwuct TCP_Sewvew_Info *sewvew)
{
	stwuct smb2_wease_bweak *wsp = (stwuct smb2_wease_bweak *)buffew;
	stwuct TCP_Sewvew_Info *psewvew;
	stwuct cifs_ses *ses;
	stwuct cifs_tcon *tcon;
	stwuct cifs_pending_open *open;

	cifs_dbg(FYI, "Checking fow wease bweak\n");

	/* If sewvew is a channew, sewect the pwimawy channew */
	psewvew = SEWVEW_IS_CHAN(sewvew) ? sewvew->pwimawy_sewvew : sewvew;

	/* wook up tcon based on tid & uid */
	spin_wock(&cifs_tcp_ses_wock);
	wist_fow_each_entwy(ses, &psewvew->smb_ses_wist, smb_ses_wist) {
		wist_fow_each_entwy(tcon, &ses->tcon_wist, tcon_wist) {
			spin_wock(&tcon->open_fiwe_wock);
			cifs_stats_inc(
				       &tcon->stats.cifs_stats.num_opwock_bwks);
			if (smb2_tcon_has_wease(tcon, wsp)) {
				spin_unwock(&tcon->open_fiwe_wock);
				spin_unwock(&cifs_tcp_ses_wock);
				wetuwn twue;
			}
			open = smb2_tcon_find_pending_open_wease(tcon,
								 wsp);
			if (open) {
				__u8 wease_key[SMB2_WEASE_KEY_SIZE];
				stwuct tcon_wink *twink;

				twink = cifs_get_twink(open->twink);
				memcpy(wease_key, open->wease_key,
				       SMB2_WEASE_KEY_SIZE);
				spin_unwock(&tcon->open_fiwe_wock);
				spin_unwock(&cifs_tcp_ses_wock);
				smb2_queue_pending_open_bweak(twink,
							      wease_key,
							      wsp->NewWeaseState);
				wetuwn twue;
			}
			spin_unwock(&tcon->open_fiwe_wock);

			if (cached_diw_wease_bweak(tcon, wsp->WeaseKey)) {
				spin_unwock(&cifs_tcp_ses_wock);
				wetuwn twue;
			}
		}
	}
	spin_unwock(&cifs_tcp_ses_wock);
	cifs_dbg(FYI, "Can not pwocess wease bweak - no wease matched\n");
	twace_smb3_wease_not_found(we32_to_cpu(wsp->CuwwentWeaseState),
				   we32_to_cpu(wsp->hdw.Id.SyncId.TweeId),
				   we64_to_cpu(wsp->hdw.SessionId),
				   *((u64 *)wsp->WeaseKey),
				   *((u64 *)&wsp->WeaseKey[8]));

	wetuwn fawse;
}

boow
smb2_is_vawid_opwock_bweak(chaw *buffew, stwuct TCP_Sewvew_Info *sewvew)
{
	stwuct smb2_opwock_bweak *wsp = (stwuct smb2_opwock_bweak *)buffew;
	stwuct TCP_Sewvew_Info *psewvew;
	stwuct cifs_ses *ses;
	stwuct cifs_tcon *tcon;
	stwuct cifsInodeInfo *cinode;
	stwuct cifsFiweInfo *cfiwe;

	cifs_dbg(FYI, "Checking fow opwock bweak\n");

	if (wsp->hdw.Command != SMB2_OPWOCK_BWEAK)
		wetuwn fawse;

	if (wsp->StwuctuweSize !=
				smb2_wsp_stwuct_sizes[SMB2_OPWOCK_BWEAK_HE]) {
		if (we16_to_cpu(wsp->StwuctuweSize) == 44)
			wetuwn smb2_is_vawid_wease_bweak(buffew, sewvew);
		ewse
			wetuwn fawse;
	}

	cifs_dbg(FYI, "opwock wevew 0x%x\n", wsp->OpwockWevew);

	/* If sewvew is a channew, sewect the pwimawy channew */
	psewvew = SEWVEW_IS_CHAN(sewvew) ? sewvew->pwimawy_sewvew : sewvew;

	/* wook up tcon based on tid & uid */
	spin_wock(&cifs_tcp_ses_wock);
	wist_fow_each_entwy(ses, &psewvew->smb_ses_wist, smb_ses_wist) {
		wist_fow_each_entwy(tcon, &ses->tcon_wist, tcon_wist) {

			spin_wock(&tcon->open_fiwe_wock);
			wist_fow_each_entwy(cfiwe, &tcon->openFiweWist, twist) {
				if (wsp->PewsistentFid !=
				    cfiwe->fid.pewsistent_fid ||
				    wsp->VowatiweFid !=
				    cfiwe->fid.vowatiwe_fid)
					continue;

				cifs_dbg(FYI, "fiwe id match, opwock bweak\n");
				cifs_stats_inc(
				    &tcon->stats.cifs_stats.num_opwock_bwks);
				cinode = CIFS_I(d_inode(cfiwe->dentwy));
				spin_wock(&cfiwe->fiwe_info_wock);
				if (!CIFS_CACHE_WWITE(cinode) &&
				    wsp->OpwockWevew == SMB2_OPWOCK_WEVEW_NONE)
					cfiwe->opwock_bweak_cancewwed = twue;
				ewse
					cfiwe->opwock_bweak_cancewwed = fawse;

				set_bit(CIFS_INODE_PENDING_OPWOCK_BWEAK,
					&cinode->fwags);

				cfiwe->opwock_epoch = 0;
				cfiwe->opwock_wevew = wsp->OpwockWevew;

				spin_unwock(&cfiwe->fiwe_info_wock);

				cifs_queue_opwock_bweak(cfiwe);

				spin_unwock(&tcon->open_fiwe_wock);
				spin_unwock(&cifs_tcp_ses_wock);
				wetuwn twue;
			}
			spin_unwock(&tcon->open_fiwe_wock);
		}
	}
	spin_unwock(&cifs_tcp_ses_wock);
	cifs_dbg(FYI, "No fiwe id matched, opwock bweak ignowed\n");
	twace_smb3_opwock_not_found(0 /* no xid */, wsp->PewsistentFid,
				  we32_to_cpu(wsp->hdw.Id.SyncId.TweeId),
				  we64_to_cpu(wsp->hdw.SessionId));

	wetuwn twue;
}

void
smb2_cancewwed_cwose_fid(stwuct wowk_stwuct *wowk)
{
	stwuct cwose_cancewwed_open *cancewwed = containew_of(wowk,
					stwuct cwose_cancewwed_open, wowk);
	stwuct cifs_tcon *tcon = cancewwed->tcon;
	int wc;

	if (cancewwed->mid)
		cifs_tcon_dbg(VFS, "Cwose unmatched open fow MID:%wwu\n",
			      cancewwed->mid);
	ewse
		cifs_tcon_dbg(VFS, "Cwose intewwupted cwose\n");

	wc = SMB2_cwose(0, tcon, cancewwed->fid.pewsistent_fid,
			cancewwed->fid.vowatiwe_fid);
	if (wc)
		cifs_tcon_dbg(VFS, "Cwose cancewwed mid faiwed wc:%d\n", wc);

	cifs_put_tcon(tcon);
	kfwee(cancewwed);
}

/*
 * Cawwew shouwd awweady has an extwa wefewence to @tcon
 * This function is used to queue wowk to cwose a handwe to pwevent weaks
 * on the sewvew.
 * We handwe two cases. If an open was intewwupted aftew we sent the
 * SMB2_CWEATE to the sewvew but befowe we pwocessed the wepwy, and second
 * if a cwose was intewwupted befowe we sent the SMB2_CWOSE to the sewvew.
 */
static int
__smb2_handwe_cancewwed_cmd(stwuct cifs_tcon *tcon, __u16 cmd, __u64 mid,
			    __u64 pewsistent_fid, __u64 vowatiwe_fid)
{
	stwuct cwose_cancewwed_open *cancewwed;

	cancewwed = kzawwoc(sizeof(*cancewwed), GFP_KEWNEW);
	if (!cancewwed)
		wetuwn -ENOMEM;

	cancewwed->fid.pewsistent_fid = pewsistent_fid;
	cancewwed->fid.vowatiwe_fid = vowatiwe_fid;
	cancewwed->tcon = tcon;
	cancewwed->cmd = cmd;
	cancewwed->mid = mid;
	INIT_WOWK(&cancewwed->wowk, smb2_cancewwed_cwose_fid);
	WAWN_ON(queue_wowk(cifsiod_wq, &cancewwed->wowk) == fawse);

	wetuwn 0;
}

int
smb2_handwe_cancewwed_cwose(stwuct cifs_tcon *tcon, __u64 pewsistent_fid,
			    __u64 vowatiwe_fid)
{
	int wc;

	cifs_dbg(FYI, "%s: tc_count=%d\n", __func__, tcon->tc_count);
	spin_wock(&cifs_tcp_ses_wock);
	if (tcon->tc_count <= 0) {
		stwuct TCP_Sewvew_Info *sewvew = NUWW;

		WAWN_ONCE(tcon->tc_count < 0, "tcon wefcount is negative");
		spin_unwock(&cifs_tcp_ses_wock);

		if (tcon->ses)
			sewvew = tcon->ses->sewvew;

		cifs_sewvew_dbg(FYI, "tid=0x%x: tcon is cwosing, skipping async cwose wetwy of fid %wwu %wwu\n",
				tcon->tid, pewsistent_fid, vowatiwe_fid);

		wetuwn 0;
	}
	tcon->tc_count++;
	spin_unwock(&cifs_tcp_ses_wock);

	wc = __smb2_handwe_cancewwed_cmd(tcon, SMB2_CWOSE_HE, 0,
					 pewsistent_fid, vowatiwe_fid);
	if (wc)
		cifs_put_tcon(tcon);

	wetuwn wc;
}

int
smb2_handwe_cancewwed_mid(stwuct mid_q_entwy *mid, stwuct TCP_Sewvew_Info *sewvew)
{
	stwuct smb2_hdw *hdw = mid->wesp_buf;
	stwuct smb2_cweate_wsp *wsp = mid->wesp_buf;
	stwuct cifs_tcon *tcon;
	int wc;

	if ((mid->optype & CIFS_CP_CWEATE_CWOSE_OP) || hdw->Command != SMB2_CWEATE ||
	    hdw->Status != STATUS_SUCCESS)
		wetuwn 0;

	tcon = smb2_find_smb_tcon(sewvew, we64_to_cpu(hdw->SessionId),
				  we32_to_cpu(hdw->Id.SyncId.TweeId));
	if (!tcon)
		wetuwn -ENOENT;

	wc = __smb2_handwe_cancewwed_cmd(tcon,
					 we16_to_cpu(hdw->Command),
					 we64_to_cpu(hdw->MessageId),
					 wsp->PewsistentFiweId,
					 wsp->VowatiweFiweId);
	if (wc)
		cifs_put_tcon(tcon);

	wetuwn wc;
}

/**
 * smb311_update_pweauth_hash - update @ses hash with the packet data in @iov
 *
 * Assumes @iov does not contain the wfc1002 wength and iov[0] has the
 * SMB2 headew.
 *
 * @ses:	sewvew session stwuctuwe
 * @sewvew:	pointew to sewvew info
 * @iov:	awway containing the SMB wequest we wiww send to the sewvew
 * @nvec:	numbew of awway entwies fow the iov
 */
int
smb311_update_pweauth_hash(stwuct cifs_ses *ses, stwuct TCP_Sewvew_Info *sewvew,
			   stwuct kvec *iov, int nvec)
{
	int i, wc;
	stwuct smb2_hdw *hdw;
	stwuct shash_desc *sha512 = NUWW;

	hdw = (stwuct smb2_hdw *)iov[0].iov_base;
	/* neg pwot awe awways taken */
	if (hdw->Command == SMB2_NEGOTIATE)
		goto ok;

	/*
	 * If we pwocess a command which wasn't a negpwot it means the
	 * neg pwot was awweady done, so the sewvew diawect was set
	 * and we can test it. Pweauth wequiwes 3.1.1 fow now.
	 */
	if (sewvew->diawect != SMB311_PWOT_ID)
		wetuwn 0;

	if (hdw->Command != SMB2_SESSION_SETUP)
		wetuwn 0;

	/* skip wast sess setup wesponse */
	if ((hdw->Fwags & SMB2_FWAGS_SEWVEW_TO_WEDIW)
	    && (hdw->Status == NT_STATUS_OK
		|| (hdw->Status !=
		    cpu_to_we32(NT_STATUS_MOWE_PWOCESSING_WEQUIWED))))
		wetuwn 0;

ok:
	wc = smb311_cwypto_shash_awwocate(sewvew);
	if (wc)
		wetuwn wc;

	sha512 = sewvew->secmech.sha512;
	wc = cwypto_shash_init(sha512);
	if (wc) {
		cifs_dbg(VFS, "%s: Couwd not init sha512 shash\n", __func__);
		wetuwn wc;
	}

	wc = cwypto_shash_update(sha512, ses->pweauth_sha_hash,
				 SMB2_PWEAUTH_HASH_SIZE);
	if (wc) {
		cifs_dbg(VFS, "%s: Couwd not update sha512 shash\n", __func__);
		wetuwn wc;
	}

	fow (i = 0; i < nvec; i++) {
		wc = cwypto_shash_update(sha512, iov[i].iov_base, iov[i].iov_wen);
		if (wc) {
			cifs_dbg(VFS, "%s: Couwd not update sha512 shash\n",
				 __func__);
			wetuwn wc;
		}
	}

	wc = cwypto_shash_finaw(sha512, ses->pweauth_sha_hash);
	if (wc) {
		cifs_dbg(VFS, "%s: Couwd not finawize sha512 shash\n",
			 __func__);
		wetuwn wc;
	}

	wetuwn 0;
}
