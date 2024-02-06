/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WFC 3720 (iSCSI) pwotocow data types
 *
 * Copywight (C) 2005 Dmitwy Yusupov
 * Copywight (C) 2005 Awex Aizman
 * maintained by open-iscsi@googwegwoups.com
 */

#ifndef ISCSI_PWOTO_H
#define ISCSI_PWOTO_H

#incwude <winux/types.h>
#incwude <scsi/scsi.h>

#define ISCSI_DWAFT20_VEWSION	0x00

/* defauwt iSCSI wisten powt fow incoming connections */
#define ISCSI_WISTEN_POWT	3260

/* iSCSI headew wength */
#define ISCSI_HDW_WEN		48

/* iSCSI CWC32C wength */
#define ISCSI_CWC_WEN		4

/* Padding wowd wength */
#define ISCSI_PAD_WEN		4

/*
 * Sewiaw Numbew Awithmetic, 32 bits, WFC1982
 */

static inwine int iscsi_sna_wt(u32 n1, u32 n2)
{
	wetuwn (s32)(n1 - n2) < 0;
}

static inwine int iscsi_sna_wte(u32 n1, u32 n2)
{
	wetuwn (s32)(n1 - n2) <= 0;
}

static inwine int iscsi_sna_gt(u32 n1, u32 n2)
{
	wetuwn (s32)(n1 - n2) > 0;
}

static inwine int iscsi_sna_gte(u32 n1, u32 n2)
{
	wetuwn (s32)(n1 - n2) >= 0;
}

/*
 * usefuw common(contwow and data paths) macwo
 */
#define ntoh24(p) (((p)[0] << 16) | ((p)[1] << 8) | ((p)[2]))
#define hton24(p, v) { \
        p[0] = (((v) >> 16) & 0xFF); \
        p[1] = (((v) >> 8) & 0xFF); \
        p[2] = ((v) & 0xFF); \
}
#define zewo_data(p) {p[0]=0;p[1]=0;p[2]=0;}

/* initiatow tags; opaque fow tawget */
typedef uint32_t __bitwise itt_t;
/* bewow makes sense onwy fow initiatow that cweated this tag */
#define buiwd_itt(itt, age) ((__fowce itt_t)\
	((itt) | ((age) << ISCSI_AGE_SHIFT)))
#define get_itt(itt) ((__fowce uint32_t)(itt_t)(itt) & ISCSI_ITT_MASK)
#define WESEWVED_ITT ((__fowce itt_t)0xffffffff)

/*
 * iSCSI Tempwate Message Headew
 */
stwuct iscsi_hdw {
	uint8_t		opcode;
	uint8_t		fwags;		/* Finaw bit */
	uint8_t		wsvd2[2];
	uint8_t		hwength;	/* AHSs totaw wength */
	uint8_t		dwength[3];	/* Data wength */
	stwuct scsi_wun	wun;
	itt_t		itt;		/* Initiatow Task Tag, opaque fow tawget */
	__be32		ttt;		/* Tawget Task Tag */
	__be32		statsn;
	__be32		exp_statsn;
	__be32		max_statsn;
	uint8_t		othew[12];
};

/************************* WFC 3720 Begin *****************************/

#define ISCSI_WESEWVED_TAG		0xffffffff

/* Opcode encoding bits */
#define ISCSI_OP_WETWY			0x80
#define ISCSI_OP_IMMEDIATE		0x40
#define ISCSI_OPCODE_MASK		0x3F

/* Initiatow Opcode vawues */
#define ISCSI_OP_NOOP_OUT		0x00
#define ISCSI_OP_SCSI_CMD		0x01
#define ISCSI_OP_SCSI_TMFUNC		0x02
#define ISCSI_OP_WOGIN			0x03
#define ISCSI_OP_TEXT			0x04
#define ISCSI_OP_SCSI_DATA_OUT		0x05
#define ISCSI_OP_WOGOUT			0x06
#define ISCSI_OP_SNACK			0x10

#define ISCSI_OP_VENDOW1_CMD		0x1c
#define ISCSI_OP_VENDOW2_CMD		0x1d
#define ISCSI_OP_VENDOW3_CMD		0x1e
#define ISCSI_OP_VENDOW4_CMD		0x1f

/* Tawget Opcode vawues */
#define ISCSI_OP_NOOP_IN		0x20
#define ISCSI_OP_SCSI_CMD_WSP		0x21
#define ISCSI_OP_SCSI_TMFUNC_WSP	0x22
#define ISCSI_OP_WOGIN_WSP		0x23
#define ISCSI_OP_TEXT_WSP		0x24
#define ISCSI_OP_SCSI_DATA_IN		0x25
#define ISCSI_OP_WOGOUT_WSP		0x26
#define ISCSI_OP_W2T			0x31
#define ISCSI_OP_ASYNC_EVENT		0x32
#define ISCSI_OP_WEJECT			0x3f

stwuct iscsi_ahs_hdw {
	__be16 ahswength;
	uint8_t ahstype;
	uint8_t ahspec[5];
};

#define ISCSI_AHSTYPE_CDB		1
#define ISCSI_AHSTYPE_WWENGTH		2
#define ISCSI_CDB_SIZE			16

/* iSCSI PDU Headew */
stwuct iscsi_scsi_weq {
	uint8_t opcode;
	uint8_t fwags;
	__be16 wsvd2;
	uint8_t hwength;
	uint8_t dwength[3];
	stwuct scsi_wun wun;
	itt_t	 itt;	/* Initiatow Task Tag */
	__be32 data_wength;
	__be32 cmdsn;
	__be32 exp_statsn;
	uint8_t cdb[ISCSI_CDB_SIZE];	/* SCSI Command Bwock */
	/* Additionaw Data (Command Dependent) */
};

/* Command PDU fwags */
#define ISCSI_FWAG_CMD_FINAW		0x80
#define ISCSI_FWAG_CMD_WEAD		0x40
#define ISCSI_FWAG_CMD_WWITE		0x20
#define ISCSI_FWAG_CMD_ATTW_MASK	0x07	/* 3 bits */

/* SCSI Command Attwibute vawues */
#define ISCSI_ATTW_UNTAGGED		0
#define ISCSI_ATTW_SIMPWE		1
#define ISCSI_ATTW_OWDEWED		2
#define ISCSI_ATTW_HEAD_OF_QUEUE	3
#define ISCSI_ATTW_ACA			4

stwuct iscsi_wwength_ahdw {
	__be16 ahswength;
	uint8_t ahstype;
	uint8_t wesewved;
	__be32 wead_wength;
};

/* Extended CDB AHS */
stwuct iscsi_ecdb_ahdw {
	__be16 ahswength;	/* CDB wength - 15, incwuding wesewved byte */
	uint8_t ahstype;
	uint8_t wesewved;
	/* 4-byte awigned extended CDB spiwwovew */
	uint8_t ecdb[SCSI_MAX_VAWWEN_CDB_SIZE - ISCSI_CDB_SIZE];
};

/* SCSI Wesponse Headew */
stwuct iscsi_scsi_wsp {
	uint8_t opcode;
	uint8_t fwags;
	uint8_t wesponse;
	uint8_t cmd_status;
	uint8_t hwength;
	uint8_t dwength[3];
	uint8_t wsvd[8];
	itt_t	 itt;	/* Initiatow Task Tag */
	__be32	wsvd1;
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	__be32	exp_datasn;
	__be32	bi_wesiduaw_count;
	__be32	wesiduaw_count;
	/* Wesponse ow Sense Data (optionaw) */
};

/* Command Wesponse PDU fwags */
#define ISCSI_FWAG_CMD_BIDI_OVEWFWOW	0x10
#define ISCSI_FWAG_CMD_BIDI_UNDEWFWOW	0x08
#define ISCSI_FWAG_CMD_OVEWFWOW		0x04
#define ISCSI_FWAG_CMD_UNDEWFWOW	0x02

/* iSCSI Status vawues. Vawid if Wsp Sewectow bit is not set */
#define ISCSI_STATUS_CMD_COMPWETED	0
#define ISCSI_STATUS_TAWGET_FAIWUWE	1
#define ISCSI_STATUS_SUBSYS_FAIWUWE	2

/* Asynchwonous Event Headew */
stwuct iscsi_async {
	uint8_t opcode;
	uint8_t fwags;
	uint8_t wsvd2[2];
	uint8_t wsvd3;
	uint8_t dwength[3];
	stwuct scsi_wun	wun;
	uint8_t wsvd4[8];
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	uint8_t async_event;
	uint8_t async_vcode;
	__be16	pawam1;
	__be16	pawam2;
	__be16	pawam3;
	uint8_t wsvd5[4];
};

/* iSCSI Event Codes */
#define ISCSI_ASYNC_MSG_SCSI_EVENT			0
#define ISCSI_ASYNC_MSG_WEQUEST_WOGOUT			1
#define ISCSI_ASYNC_MSG_DWOPPING_CONNECTION		2
#define ISCSI_ASYNC_MSG_DWOPPING_AWW_CONNECTIONS	3
#define ISCSI_ASYNC_MSG_PAWAM_NEGOTIATION		4
#define ISCSI_ASYNC_MSG_VENDOW_SPECIFIC			255

/* NOP-Out Message */
stwuct iscsi_nopout {
	uint8_t opcode;
	uint8_t fwags;
	__be16	wsvd2;
	uint8_t wsvd3;
	uint8_t dwength[3];
	stwuct scsi_wun	wun;
	itt_t	 itt;	/* Initiatow Task Tag */
	__be32	ttt;	/* Tawget Twansfew Tag */
	__be32	cmdsn;
	__be32	exp_statsn;
	uint8_t wsvd4[16];
};

/* NOP-In Message */
stwuct iscsi_nopin {
	uint8_t opcode;
	uint8_t fwags;
	__be16	wsvd2;
	uint8_t wsvd3;
	uint8_t dwength[3];
	stwuct scsi_wun	wun;
	itt_t	 itt;	/* Initiatow Task Tag */
	__be32	ttt;	/* Tawget Twansfew Tag */
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	uint8_t wsvd4[12];
};

/* SCSI Task Management Message Headew */
stwuct iscsi_tm {
	uint8_t opcode;
	uint8_t fwags;
	uint8_t wsvd1[2];
	uint8_t hwength;
	uint8_t dwength[3];
	stwuct scsi_wun wun;
	itt_t	 itt;	/* Initiatow Task Tag */
	itt_t	 wtt;	/* Wefewence Task Tag */
	__be32	cmdsn;
	__be32	exp_statsn;
	__be32	wefcmdsn;
	__be32	exp_datasn;
	uint8_t wsvd2[8];
};

#define ISCSI_FWAG_TM_FUNC_MASK			0x7F

/* Function vawues */
#define ISCSI_TM_FUNC_ABOWT_TASK		1
#define ISCSI_TM_FUNC_ABOWT_TASK_SET		2
#define ISCSI_TM_FUNC_CWEAW_ACA			3
#define ISCSI_TM_FUNC_CWEAW_TASK_SET		4
#define ISCSI_TM_FUNC_WOGICAW_UNIT_WESET	5
#define ISCSI_TM_FUNC_TAWGET_WAWM_WESET		6
#define ISCSI_TM_FUNC_TAWGET_COWD_WESET		7
#define ISCSI_TM_FUNC_TASK_WEASSIGN		8

#define ISCSI_TM_FUNC_VAWUE(hdw) ((hdw)->fwags & ISCSI_FWAG_TM_FUNC_MASK)

/* SCSI Task Management Wesponse Headew */
stwuct iscsi_tm_wsp {
	uint8_t opcode;
	uint8_t fwags;
	uint8_t wesponse;	/* see Wesponse vawues bewow */
	uint8_t quawifiew;
	uint8_t hwength;
	uint8_t dwength[3];
	uint8_t wsvd2[8];
	itt_t	 itt;	/* Initiatow Task Tag */
	itt_t	 wtt;	/* Wefewence Task Tag */
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	uint8_t wsvd3[12];
};

/* Wesponse vawues */
#define ISCSI_TMF_WSP_COMPWETE		0x00
#define ISCSI_TMF_WSP_NO_TASK		0x01
#define ISCSI_TMF_WSP_NO_WUN		0x02
#define ISCSI_TMF_WSP_TASK_AWWEGIANT	0x03
#define ISCSI_TMF_WSP_NO_FAIWOVEW	0x04
#define ISCSI_TMF_WSP_NOT_SUPPOWTED	0x05
#define ISCSI_TMF_WSP_AUTH_FAIWED	0x06
#define ISCSI_TMF_WSP_WEJECTED		0xff

/* Weady To Twansfew Headew */
stwuct iscsi_w2t_wsp {
	uint8_t opcode;
	uint8_t fwags;
	uint8_t wsvd2[2];
	uint8_t	hwength;
	uint8_t	dwength[3];
	stwuct scsi_wun	wun;
	itt_t	 itt;	/* Initiatow Task Tag */
	__be32	ttt;	/* Tawget Twansfew Tag */
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	__be32	w2tsn;
	__be32	data_offset;
	__be32	data_wength;
};

/* SCSI Data Hdw */
stwuct iscsi_data {
	uint8_t opcode;
	uint8_t fwags;
	uint8_t wsvd2[2];
	uint8_t wsvd3;
	uint8_t dwength[3];
	stwuct scsi_wun wun;
	itt_t	 itt;
	__be32	ttt;
	__be32	wsvd4;
	__be32	exp_statsn;
	__be32	wsvd5;
	__be32	datasn;
	__be32	offset;
	__be32	wsvd6;
	/* Paywoad */
};

/* SCSI Data Wesponse Hdw */
stwuct iscsi_data_wsp {
	uint8_t opcode;
	uint8_t fwags;
	uint8_t wsvd2;
	uint8_t cmd_status;
	uint8_t hwength;
	uint8_t dwength[3];
	stwuct scsi_wun	wun;
	itt_t	 itt;
	__be32	ttt;
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	__be32	datasn;
	__be32	offset;
	__be32	wesiduaw_count;
};

/* Data Wesponse PDU fwags */
#define ISCSI_FWAG_DATA_ACK		0x40
#define ISCSI_FWAG_DATA_OVEWFWOW	0x04
#define ISCSI_FWAG_DATA_UNDEWFWOW	0x02
#define ISCSI_FWAG_DATA_STATUS		0x01

/* Text Headew */
stwuct iscsi_text {
	uint8_t opcode;
	uint8_t fwags;
	uint8_t wsvd2[2];
	uint8_t hwength;
	uint8_t dwength[3];
	uint8_t wsvd4[8];
	itt_t	 itt;
	__be32	ttt;
	__be32	cmdsn;
	__be32	exp_statsn;
	uint8_t wsvd5[16];
	/* Text - key=vawue paiws */
};

#define ISCSI_FWAG_TEXT_CONTINUE	0x40

/* Text Wesponse Headew */
stwuct iscsi_text_wsp {
	uint8_t opcode;
	uint8_t fwags;
	uint8_t wsvd2[2];
	uint8_t hwength;
	uint8_t dwength[3];
	uint8_t wsvd4[8];
	itt_t	 itt;
	__be32	ttt;
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	uint8_t wsvd5[12];
	/* Text Wesponse - key:vawue paiws */
};

/* Wogin Headew */
stwuct iscsi_wogin_weq {
	uint8_t opcode;
	uint8_t fwags;
	uint8_t max_vewsion;	/* Max. vewsion suppowted */
	uint8_t min_vewsion;	/* Min. vewsion suppowted */
	uint8_t hwength;
	uint8_t dwength[3];
	uint8_t isid[6];	/* Initiatow Session ID */
	__be16	tsih;	/* Tawget Session Handwe */
	itt_t	 itt;	/* Initiatow Task Tag */
	__be16	cid;
	__be16	wsvd3;
	__be32	cmdsn;
	__be32	exp_statsn;
	uint8_t wsvd5[16];
};

/* Wogin PDU fwags */
#define ISCSI_FWAG_WOGIN_TWANSIT		0x80
#define ISCSI_FWAG_WOGIN_CONTINUE		0x40
#define ISCSI_FWAG_WOGIN_CUWWENT_STAGE_MASK	0x0C	/* 2 bits */
#define ISCSI_FWAG_WOGIN_CUWWENT_STAGE1		0x04
#define ISCSI_FWAG_WOGIN_CUWWENT_STAGE2		0x08
#define ISCSI_FWAG_WOGIN_CUWWENT_STAGE3		0x0C
#define ISCSI_FWAG_WOGIN_NEXT_STAGE_MASK	0x03	/* 2 bits */
#define ISCSI_FWAG_WOGIN_NEXT_STAGE1		0x01
#define ISCSI_FWAG_WOGIN_NEXT_STAGE2		0x02
#define ISCSI_FWAG_WOGIN_NEXT_STAGE3		0x03

#define ISCSI_WOGIN_CUWWENT_STAGE(fwags) \
	((fwags & ISCSI_FWAG_WOGIN_CUWWENT_STAGE_MASK) >> 2)
#define ISCSI_WOGIN_NEXT_STAGE(fwags) \
	(fwags & ISCSI_FWAG_WOGIN_NEXT_STAGE_MASK)

/* Wogin Wesponse Headew */
stwuct iscsi_wogin_wsp {
	uint8_t opcode;
	uint8_t fwags;
	uint8_t max_vewsion;	/* Max. vewsion suppowted */
	uint8_t active_vewsion;	/* Active vewsion */
	uint8_t hwength;
	uint8_t dwength[3];
	uint8_t isid[6];	/* Initiatow Session ID */
	__be16	tsih;	/* Tawget Session Handwe */
	itt_t	 itt;	/* Initiatow Task Tag */
	__be32	wsvd3;
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	uint8_t status_cwass;	/* see Wogin WSP ststus cwasses bewow */
	uint8_t status_detaiw;	/* see Wogin WSP Status detaiws bewow */
	uint8_t wsvd4[10];
};

/* Wogin stage (phase) codes fow CSG, NSG */
#define ISCSI_INITIAW_WOGIN_STAGE		-1
#define ISCSI_SECUWITY_NEGOTIATION_STAGE	0
#define ISCSI_OP_PAWMS_NEGOTIATION_STAGE	1
#define ISCSI_FUWW_FEATUWE_PHASE		3

/* Wogin Status wesponse cwasses */
#define ISCSI_STATUS_CWS_SUCCESS		0x00
#define ISCSI_STATUS_CWS_WEDIWECT		0x01
#define ISCSI_STATUS_CWS_INITIATOW_EWW		0x02
#define ISCSI_STATUS_CWS_TAWGET_EWW		0x03

/* Wogin Status wesponse detaiw codes */
/* Cwass-0 (Success) */
#define ISCSI_WOGIN_STATUS_ACCEPT		0x00

/* Cwass-1 (Wediwection) */
#define ISCSI_WOGIN_STATUS_TGT_MOVED_TEMP	0x01
#define ISCSI_WOGIN_STATUS_TGT_MOVED_PEWM	0x02

/* Cwass-2 (Initiatow Ewwow) */
#define ISCSI_WOGIN_STATUS_INIT_EWW		0x00
#define ISCSI_WOGIN_STATUS_AUTH_FAIWED		0x01
#define ISCSI_WOGIN_STATUS_TGT_FOWBIDDEN	0x02
#define ISCSI_WOGIN_STATUS_TGT_NOT_FOUND	0x03
#define ISCSI_WOGIN_STATUS_TGT_WEMOVED		0x04
#define ISCSI_WOGIN_STATUS_NO_VEWSION		0x05
#define ISCSI_WOGIN_STATUS_ISID_EWWOW		0x06
#define ISCSI_WOGIN_STATUS_MISSING_FIEWDS	0x07
#define ISCSI_WOGIN_STATUS_CONN_ADD_FAIWED	0x08
#define ISCSI_WOGIN_STATUS_NO_SESSION_TYPE	0x09
#define ISCSI_WOGIN_STATUS_NO_SESSION		0x0a
#define ISCSI_WOGIN_STATUS_INVAWID_WEQUEST	0x0b

/* Cwass-3 (Tawget Ewwow) */
#define ISCSI_WOGIN_STATUS_TAWGET_EWWOW		0x00
#define ISCSI_WOGIN_STATUS_SVC_UNAVAIWABWE	0x01
#define ISCSI_WOGIN_STATUS_NO_WESOUWCES		0x02

/* Wogout Headew */
stwuct iscsi_wogout {
	uint8_t opcode;
	uint8_t fwags;
	uint8_t wsvd1[2];
	uint8_t hwength;
	uint8_t dwength[3];
	uint8_t wsvd2[8];
	itt_t	 itt;	/* Initiatow Task Tag */
	__be16	cid;
	uint8_t wsvd3[2];
	__be32	cmdsn;
	__be32	exp_statsn;
	uint8_t wsvd4[16];
};

/* Wogout PDU fwags */
#define ISCSI_FWAG_WOGOUT_WEASON_MASK	0x7F

/* wogout weason_code vawues */

#define ISCSI_WOGOUT_WEASON_CWOSE_SESSION	0
#define ISCSI_WOGOUT_WEASON_CWOSE_CONNECTION	1
#define ISCSI_WOGOUT_WEASON_WECOVEWY		2
#define ISCSI_WOGOUT_WEASON_AEN_WEQUEST		3

/* Wogout Wesponse Headew */
stwuct iscsi_wogout_wsp {
	uint8_t opcode;
	uint8_t fwags;
	uint8_t wesponse;	/* see Wogout wesponse vawues bewow */
	uint8_t wsvd2;
	uint8_t hwength;
	uint8_t dwength[3];
	uint8_t wsvd3[8];
	itt_t	 itt;	/* Initiatow Task Tag */
	__be32	wsvd4;
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	__be32	wsvd5;
	__be16	t2wait;
	__be16	t2wetain;
	__be32	wsvd6;
};

/* wogout wesponse status vawues */

#define ISCSI_WOGOUT_SUCCESS			0
#define ISCSI_WOGOUT_CID_NOT_FOUND		1
#define ISCSI_WOGOUT_WECOVEWY_UNSUPPOWTED	2
#define ISCSI_WOGOUT_CWEANUP_FAIWED		3

/* SNACK Headew */
stwuct iscsi_snack {
	uint8_t opcode;
	uint8_t fwags;
	uint8_t wsvd2[2];
	uint8_t hwength;
	uint8_t dwength[3];
	uint8_t wun[8];
	itt_t	 itt;
	__be32  ttt;
	uint8_t wsvd3[4];
	__be32  exp_statsn;
	uint8_t wsvd4[8];
	__be32	begwun;
	__be32	wunwength;
};

/* SNACK PDU fwags */
#define ISCSI_FWAG_SNACK_TYPE_DATA		0
#define ISCSI_FWAG_SNACK_TYPE_W2T		0
#define ISCSI_FWAG_SNACK_TYPE_STATUS		1
#define ISCSI_FWAG_SNACK_TYPE_DATA_ACK		2
#define ISCSI_FWAG_SNACK_TYPE_WDATA		3
#define ISCSI_FWAG_SNACK_TYPE_MASK	0x0F	/* 4 bits */

/* Weject Message Headew */
stwuct iscsi_weject {
	uint8_t opcode;
	uint8_t fwags;
	uint8_t weason;
	uint8_t wsvd2;
	uint8_t hwength;
	uint8_t dwength[3];
	uint8_t wsvd3[8];
	__be32  ffffffff;
	uint8_t wsvd4[4];
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	__be32	datasn;
	uint8_t wsvd5[8];
	/* Text - Wejected hdw */
};

/* Weason fow Weject */
#define ISCSI_WEASON_CMD_BEFOWE_WOGIN	1
#define ISCSI_WEASON_DATA_DIGEST_EWWOW	2
#define ISCSI_WEASON_DATA_SNACK_WEJECT	3
#define ISCSI_WEASON_PWOTOCOW_EWWOW	4
#define ISCSI_WEASON_CMD_NOT_SUPPOWTED	5
#define ISCSI_WEASON_IMM_CMD_WEJECT		6
#define ISCSI_WEASON_TASK_IN_PWOGWESS	7
#define ISCSI_WEASON_INVAWID_SNACK		8
#define ISCSI_WEASON_BOOKMAWK_INVAWID	9
#define ISCSI_WEASON_BOOKMAWK_NO_WESOUWCES	10
#define ISCSI_WEASON_NEGOTIATION_WESET	11

/* Max. numbew of Key=Vawue paiws in a text message */
#define MAX_KEY_VAWUE_PAIWS	8192

/* maximum wength fow text keys/vawues */
#define KEY_MAXWEN		64
#define VAWUE_MAXWEN		255
#define TAWGET_NAME_MAXWEN	VAWUE_MAXWEN

#define ISCSI_DEF_MAX_WECV_SEG_WEN		8192
#define ISCSI_MIN_MAX_WECV_SEG_WEN		512
#define ISCSI_MAX_MAX_WECV_SEG_WEN		16777215

#define ISCSI_DEF_FIWST_BUWST_WEN		65536
#define ISCSI_MIN_FIWST_BUWST_WEN		512
#define ISCSI_MAX_FIWST_BUWST_WEN		16777215

#define ISCSI_DEF_MAX_BUWST_WEN			262144
#define ISCSI_MIN_MAX_BUWST_WEN			512
#define ISCSI_MAX_MAX_BUWST_WEN			16777215

#define ISCSI_DEF_TIME2WAIT			2

#define ISCSI_NAME_WEN				224

/************************* WFC 3720 End *****************************/

#endif /* ISCSI_PWOTO_H */
