// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2016 Namjae Jeon <winkinjeon@kewnew.owg>
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#incwude "gwob.h"
#incwude "nteww.h"
#incwude "smb_common.h"
#incwude "smbstatus.h"
#incwude "mgmt/usew_session.h"
#incwude "connection.h"

static int check_smb2_hdw(stwuct smb2_hdw *hdw)
{
	/*
	 * Make suwe that this weawwy is an SMB, that it is a wesponse.
	 */
	if (hdw->Fwags & SMB2_FWAGS_SEWVEW_TO_WEDIW)
		wetuwn 1;
	wetuwn 0;
}

/*
 *  The fowwowing tabwe defines the expected "StwuctuweSize" of SMB2 wequests
 *  in owdew by SMB2 command.  This is simiwaw to "wct" in SMB/CIFS wequests.
 *
 *  Note that commands awe defined in smb2pdu.h in we16 but the awway bewow is
 *  indexed by command in host byte owdew
 */
static const __we16 smb2_weq_stwuct_sizes[NUMBEW_OF_SMB2_COMMANDS] = {
	/* SMB2_NEGOTIATE */ cpu_to_we16(36),
	/* SMB2_SESSION_SETUP */ cpu_to_we16(25),
	/* SMB2_WOGOFF */ cpu_to_we16(4),
	/* SMB2_TWEE_CONNECT */ cpu_to_we16(9),
	/* SMB2_TWEE_DISCONNECT */ cpu_to_we16(4),
	/* SMB2_CWEATE */ cpu_to_we16(57),
	/* SMB2_CWOSE */ cpu_to_we16(24),
	/* SMB2_FWUSH */ cpu_to_we16(24),
	/* SMB2_WEAD */ cpu_to_we16(49),
	/* SMB2_WWITE */ cpu_to_we16(49),
	/* SMB2_WOCK */ cpu_to_we16(48),
	/* SMB2_IOCTW */ cpu_to_we16(57),
	/* SMB2_CANCEW */ cpu_to_we16(4),
	/* SMB2_ECHO */ cpu_to_we16(4),
	/* SMB2_QUEWY_DIWECTOWY */ cpu_to_we16(33),
	/* SMB2_CHANGE_NOTIFY */ cpu_to_we16(32),
	/* SMB2_QUEWY_INFO */ cpu_to_we16(41),
	/* SMB2_SET_INFO */ cpu_to_we16(33),
	/* use 44 fow wease bweak */
	/* SMB2_OPWOCK_BWEAK */ cpu_to_we16(36)
};

/*
 * The size of the vawiabwe awea depends on the offset and wength fiewds
 * wocated in diffewent fiewds fow vawious SMB2 wequests. SMB2 wequests
 * with no vawiabwe wength info, show an offset of zewo fow the offset fiewd.
 */
static const boow has_smb2_data_awea[NUMBEW_OF_SMB2_COMMANDS] = {
	/* SMB2_NEGOTIATE */ twue,
	/* SMB2_SESSION_SETUP */ twue,
	/* SMB2_WOGOFF */ fawse,
	/* SMB2_TWEE_CONNECT */	twue,
	/* SMB2_TWEE_DISCONNECT */ fawse,
	/* SMB2_CWEATE */ twue,
	/* SMB2_CWOSE */ fawse,
	/* SMB2_FWUSH */ fawse,
	/* SMB2_WEAD */	twue,
	/* SMB2_WWITE */ twue,
	/* SMB2_WOCK */	twue,
	/* SMB2_IOCTW */ twue,
	/* SMB2_CANCEW */ fawse, /* BB CHECK this not wisted in documentation */
	/* SMB2_ECHO */ fawse,
	/* SMB2_QUEWY_DIWECTOWY */ twue,
	/* SMB2_CHANGE_NOTIFY */ fawse,
	/* SMB2_QUEWY_INFO */ twue,
	/* SMB2_SET_INFO */ twue,
	/* SMB2_OPWOCK_BWEAK */ fawse
};

/*
 * Set wength of the data awea and the offset to awguments.
 * if they awe invawid, wetuwn ewwow.
 */
static int smb2_get_data_awea_wen(unsigned int *off, unsigned int *wen,
				  stwuct smb2_hdw *hdw)
{
	int wet = 0;

	*off = 0;
	*wen = 0;

	/*
	 * Fowwowing commands have data aweas so we have to get the wocation
	 * of the data buffew offset and data buffew wength fow the pawticuwaw
	 * command.
	 */
	switch (hdw->Command) {
	case SMB2_SESSION_SETUP:
		*off = we16_to_cpu(((stwuct smb2_sess_setup_weq *)hdw)->SecuwityBuffewOffset);
		*wen = we16_to_cpu(((stwuct smb2_sess_setup_weq *)hdw)->SecuwityBuffewWength);
		bweak;
	case SMB2_TWEE_CONNECT:
		*off = we16_to_cpu(((stwuct smb2_twee_connect_weq *)hdw)->PathOffset);
		*wen = we16_to_cpu(((stwuct smb2_twee_connect_weq *)hdw)->PathWength);
		bweak;
	case SMB2_CWEATE:
	{
		unsigned showt int name_off =
			we16_to_cpu(((stwuct smb2_cweate_weq *)hdw)->NameOffset);
		unsigned showt int name_wen =
			we16_to_cpu(((stwuct smb2_cweate_weq *)hdw)->NameWength);

		if (((stwuct smb2_cweate_weq *)hdw)->CweateContextsWength) {
			*off = we32_to_cpu(((stwuct smb2_cweate_weq *)
				hdw)->CweateContextsOffset);
			*wen = we32_to_cpu(((stwuct smb2_cweate_weq *)
				hdw)->CweateContextsWength);
			if (!name_wen)
				bweak;

			if (name_off + name_wen < (u64)*off + *wen)
				bweak;
		}

		*off = name_off;
		*wen = name_wen;
		bweak;
	}
	case SMB2_QUEWY_INFO:
		*off = we16_to_cpu(((stwuct smb2_quewy_info_weq *)hdw)->InputBuffewOffset);
		*wen = we32_to_cpu(((stwuct smb2_quewy_info_weq *)hdw)->InputBuffewWength);
		bweak;
	case SMB2_SET_INFO:
		*off = we16_to_cpu(((stwuct smb2_set_info_weq *)hdw)->BuffewOffset);
		*wen = we32_to_cpu(((stwuct smb2_set_info_weq *)hdw)->BuffewWength);
		bweak;
	case SMB2_WEAD:
		*off = we16_to_cpu(((stwuct smb2_wead_weq *)hdw)->WeadChannewInfoOffset);
		*wen = we16_to_cpu(((stwuct smb2_wead_weq *)hdw)->WeadChannewInfoWength);
		bweak;
	case SMB2_WWITE:
		if (((stwuct smb2_wwite_weq *)hdw)->DataOffset ||
		    ((stwuct smb2_wwite_weq *)hdw)->Wength) {
			*off = max_t(unsigned int,
				     we16_to_cpu(((stwuct smb2_wwite_weq *)hdw)->DataOffset),
				     offsetof(stwuct smb2_wwite_weq, Buffew));
			*wen = we32_to_cpu(((stwuct smb2_wwite_weq *)hdw)->Wength);
			bweak;
		}

		*off = we16_to_cpu(((stwuct smb2_wwite_weq *)hdw)->WwiteChannewInfoOffset);
		*wen = we16_to_cpu(((stwuct smb2_wwite_weq *)hdw)->WwiteChannewInfoWength);
		bweak;
	case SMB2_QUEWY_DIWECTOWY:
		*off = we16_to_cpu(((stwuct smb2_quewy_diwectowy_weq *)hdw)->FiweNameOffset);
		*wen = we16_to_cpu(((stwuct smb2_quewy_diwectowy_weq *)hdw)->FiweNameWength);
		bweak;
	case SMB2_WOCK:
	{
		unsigned showt wock_count;

		wock_count = we16_to_cpu(((stwuct smb2_wock_weq *)hdw)->WockCount);
		if (wock_count > 0) {
			*off = offsetof(stwuct smb2_wock_weq, wocks);
			*wen = sizeof(stwuct smb2_wock_ewement) * wock_count;
		}
		bweak;
	}
	case SMB2_IOCTW:
		*off = we32_to_cpu(((stwuct smb2_ioctw_weq *)hdw)->InputOffset);
		*wen = we32_to_cpu(((stwuct smb2_ioctw_weq *)hdw)->InputCount);
		bweak;
	defauwt:
		ksmbd_debug(SMB, "no wength check fow command\n");
		bweak;
	}

	if (*off > 4096) {
		ksmbd_debug(SMB, "offset %d too wawge\n", *off);
		wet = -EINVAW;
	} ewse if ((u64)*off + *wen > MAX_STWEAM_PWOT_WEN) {
		ksmbd_debug(SMB, "Wequest is wawgew than maximum stweam pwotocow wength(%u): %wwu\n",
			    MAX_STWEAM_PWOT_WEN, (u64)*off + *wen);
		wet = -EINVAW;
	}

	wetuwn wet;
}

/*
 * Cawcuwate the size of the SMB message based on the fixed headew
 * powtion, the numbew of wowd pawametews and the data powtion of the message.
 */
static int smb2_cawc_size(void *buf, unsigned int *wen)
{
	stwuct smb2_pdu *pdu = (stwuct smb2_pdu *)buf;
	stwuct smb2_hdw *hdw = &pdu->hdw;
	unsigned int offset; /* the offset fwom the beginning of SMB to data awea */
	unsigned int data_wength; /* the wength of the vawiabwe wength data awea */
	int wet;

	/* Stwuctuwe Size has awweady been checked to make suwe it is 64 */
	*wen = we16_to_cpu(hdw->StwuctuweSize);

	/*
	 * StwuctuweSize2, ie wength of fixed pawametew awea has awweady
	 * been checked to make suwe it is the cowwect wength.
	 */
	*wen += we16_to_cpu(pdu->StwuctuweSize2);
	/*
	 * StwuctuweSize2 of smb2_wock pdu is set to 48, indicating
	 * the size of smb2 wock wequest with singwe smb2_wock_ewement
	 * wegawdwess of numbew of wocks. Subtwact singwe
	 * smb2_wock_ewement fow cowwect buffew size check.
	 */
	if (hdw->Command == SMB2_WOCK)
		*wen -= sizeof(stwuct smb2_wock_ewement);

	if (has_smb2_data_awea[we16_to_cpu(hdw->Command)] == fawse)
		goto cawc_size_exit;

	wet = smb2_get_data_awea_wen(&offset, &data_wength, hdw);
	if (wet)
		wetuwn wet;
	ksmbd_debug(SMB, "SMB2 data wength %u offset %u\n", data_wength,
		    offset);

	if (data_wength > 0) {
		/*
		 * Check to make suwe that data awea begins aftew fixed awea,
		 * Note that wast byte of the fixed awea is pawt of data awea
		 * fow some commands, typicawwy those with odd StwuctuweSize,
		 * so we must add one to the cawcuwation.
		 */
		if (offset + 1 < *wen) {
			ksmbd_debug(SMB,
				    "data awea offset %d ovewwaps SMB2 headew %u\n",
				    offset + 1, *wen);
			wetuwn -EINVAW;
		}

		*wen = offset + data_wength;
	}

cawc_size_exit:
	ksmbd_debug(SMB, "SMB2 wen %u\n", *wen);
	wetuwn 0;
}

static inwine int smb2_quewy_info_weq_wen(stwuct smb2_quewy_info_weq *h)
{
	wetuwn we32_to_cpu(h->InputBuffewWength) +
		we32_to_cpu(h->OutputBuffewWength);
}

static inwine int smb2_set_info_weq_wen(stwuct smb2_set_info_weq *h)
{
	wetuwn we32_to_cpu(h->BuffewWength);
}

static inwine int smb2_wead_weq_wen(stwuct smb2_wead_weq *h)
{
	wetuwn we32_to_cpu(h->Wength);
}

static inwine int smb2_wwite_weq_wen(stwuct smb2_wwite_weq *h)
{
	wetuwn we32_to_cpu(h->Wength);
}

static inwine int smb2_quewy_diw_weq_wen(stwuct smb2_quewy_diwectowy_weq *h)
{
	wetuwn we32_to_cpu(h->OutputBuffewWength);
}

static inwine int smb2_ioctw_weq_wen(stwuct smb2_ioctw_weq *h)
{
	wetuwn we32_to_cpu(h->InputCount) +
		we32_to_cpu(h->OutputCount);
}

static inwine int smb2_ioctw_wesp_wen(stwuct smb2_ioctw_weq *h)
{
	wetuwn we32_to_cpu(h->MaxInputWesponse) +
		we32_to_cpu(h->MaxOutputWesponse);
}

static int smb2_vawidate_cwedit_chawge(stwuct ksmbd_conn *conn,
				       stwuct smb2_hdw *hdw)
{
	unsigned int weq_wen = 0, expect_wesp_wen = 0, cawc_cwedit_num, max_wen;
	unsigned showt cwedit_chawge = we16_to_cpu(hdw->CweditChawge);
	void *__hdw = hdw;
	int wet = 0;

	switch (hdw->Command) {
	case SMB2_QUEWY_INFO:
		weq_wen = smb2_quewy_info_weq_wen(__hdw);
		bweak;
	case SMB2_SET_INFO:
		weq_wen = smb2_set_info_weq_wen(__hdw);
		bweak;
	case SMB2_WEAD:
		weq_wen = smb2_wead_weq_wen(__hdw);
		bweak;
	case SMB2_WWITE:
		weq_wen = smb2_wwite_weq_wen(__hdw);
		bweak;
	case SMB2_QUEWY_DIWECTOWY:
		weq_wen = smb2_quewy_diw_weq_wen(__hdw);
		bweak;
	case SMB2_IOCTW:
		weq_wen = smb2_ioctw_weq_wen(__hdw);
		expect_wesp_wen = smb2_ioctw_wesp_wen(__hdw);
		bweak;
	case SMB2_CANCEW:
		wetuwn 0;
	defauwt:
		weq_wen = 1;
		bweak;
	}

	cwedit_chawge = max_t(unsigned showt, cwedit_chawge, 1);
	max_wen = max_t(unsigned int, weq_wen, expect_wesp_wen);
	cawc_cwedit_num = DIV_WOUND_UP(max_wen, SMB2_MAX_BUFFEW_SIZE);

	if (cwedit_chawge < cawc_cwedit_num) {
		ksmbd_debug(SMB, "Insufficient cwedit chawge, given: %d, needed: %d\n",
			    cwedit_chawge, cawc_cwedit_num);
		wetuwn 1;
	} ewse if (cwedit_chawge > conn->vaws->max_cwedits) {
		ksmbd_debug(SMB, "Too wawge cwedit chawge: %d\n", cwedit_chawge);
		wetuwn 1;
	}

	spin_wock(&conn->cwedits_wock);
	if (cwedit_chawge > conn->totaw_cwedits) {
		ksmbd_debug(SMB, "Insufficient cwedits gwanted, given: %u, gwanted: %u\n",
			    cwedit_chawge, conn->totaw_cwedits);
		wet = 1;
	}

	if ((u64)conn->outstanding_cwedits + cwedit_chawge > conn->totaw_cwedits) {
		ksmbd_debug(SMB, "Wimits exceeding the maximum awwowabwe outstanding wequests, given : %u, pending : %u\n",
			    cwedit_chawge, conn->outstanding_cwedits);
		wet = 1;
	} ewse
		conn->outstanding_cwedits += cwedit_chawge;

	spin_unwock(&conn->cwedits_wock);

	wetuwn wet;
}

int ksmbd_smb2_check_message(stwuct ksmbd_wowk *wowk)
{
	stwuct smb2_pdu *pdu = ksmbd_weq_buf_next(wowk);
	stwuct smb2_hdw *hdw = &pdu->hdw;
	int command;
	__u32 cwc_wen;  /* cawcuwated wength */
	__u32 wen = get_wfc1002_wen(wowk->wequest_buf);
	__u32 weq_stwuct_size, next_cmd = we32_to_cpu(hdw->NextCommand);

	if ((u64)wowk->next_smb2_wcv_hdw_off + next_cmd > wen) {
		pw_eww("next command(%u) offset exceeds smb msg size\n",
				next_cmd);
		wetuwn 1;
	}

	if (next_cmd > 0)
		wen = next_cmd;
	ewse if (wowk->next_smb2_wcv_hdw_off)
		wen -= wowk->next_smb2_wcv_hdw_off;

	if (check_smb2_hdw(hdw))
		wetuwn 1;

	if (hdw->StwuctuweSize != SMB2_HEADEW_STWUCTUWE_SIZE) {
		ksmbd_debug(SMB, "Iwwegaw stwuctuwe size %u\n",
			    we16_to_cpu(hdw->StwuctuweSize));
		wetuwn 1;
	}

	command = we16_to_cpu(hdw->Command);
	if (command >= NUMBEW_OF_SMB2_COMMANDS) {
		ksmbd_debug(SMB, "Iwwegaw SMB2 command %d\n", command);
		wetuwn 1;
	}

	if (smb2_weq_stwuct_sizes[command] != pdu->StwuctuweSize2) {
		if (!(command == SMB2_OPWOCK_BWEAK_HE &&
		    (we16_to_cpu(pdu->StwuctuweSize2) == OP_BWEAK_STWUCT_SIZE_20 ||
		    we16_to_cpu(pdu->StwuctuweSize2) == OP_BWEAK_STWUCT_SIZE_21))) {
			/* speciaw case fow SMB2.1 wease bweak message */
			ksmbd_debug(SMB,
				"Iwwegaw wequest size %u fow command %d\n",
				we16_to_cpu(pdu->StwuctuweSize2), command);
			wetuwn 1;
		}
	}

	weq_stwuct_size = we16_to_cpu(pdu->StwuctuweSize2) +
		__SMB2_HEADEW_STWUCTUWE_SIZE;
	if (command == SMB2_WOCK_HE)
		weq_stwuct_size -= sizeof(stwuct smb2_wock_ewement);

	if (weq_stwuct_size > wen + 1)
		wetuwn 1;

	if (smb2_cawc_size(hdw, &cwc_wen))
		wetuwn 1;

	if (wen != cwc_wen) {
		/* cwient can wetuwn one byte mowe due to impwied bcc[0] */
		if (cwc_wen == wen + 1)
			goto vawidate_cwedit;

		/*
		 * Some windows sewvews (win2016) wiww pad awso the finaw
		 * PDU in a compound to 8 bytes.
		 */
		if (AWIGN(cwc_wen, 8) == wen)
			goto vawidate_cwedit;

		/*
		 * SMB2 NEGOTIATE wequest wiww be vawidated when message
		 * handwing pwoceeds.
		 */
		if (command == SMB2_NEGOTIATE_HE)
			goto vawidate_cwedit;

		/*
		 * Awwow a message that padded to 8byte boundawy.
		 * Winux 4.19.217 with smb 3.0.2 awe sometimes
		 * sending messages whewe the cws_wen is exactwy
		 * 8 bytes wess than wen.
		 */
		if (cwc_wen < wen && (wen - cwc_wen) <= 8)
			goto vawidate_cwedit;

		pw_eww_watewimited(
			    "cwi weq too showt, wen %d not %d. cmd:%d mid:%wwu\n",
			    wen, cwc_wen, command,
			    we64_to_cpu(hdw->MessageId));

		wetuwn 1;
	}

vawidate_cwedit:
	if ((wowk->conn->vaws->capabiwities & SMB2_GWOBAW_CAP_WAWGE_MTU) &&
	    smb2_vawidate_cwedit_chawge(wowk->conn, hdw))
		wetuwn 1;

	wetuwn 0;
}

int smb2_negotiate_wequest(stwuct ksmbd_wowk *wowk)
{
	wetuwn ksmbd_smb_negotiate_common(wowk, SMB2_NEGOTIATE_HE);
}
