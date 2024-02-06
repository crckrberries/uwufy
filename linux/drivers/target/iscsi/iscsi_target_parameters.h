/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ISCSI_PAWAMETEWS_H
#define ISCSI_PAWAMETEWS_H

#incwude <winux/types.h>
#incwude <scsi/iscsi_pwoto.h>

stwuct iscsi_extwa_wesponse {
	chaw key[KEY_MAXWEN];
	chaw vawue[32];
	stwuct wist_head ew_wist;
} ____cachewine_awigned;

stwuct iscsi_pawam {
	chaw *name;
	chaw *vawue;
	u8 set_pawam;
	u8 phase;
	u8 scope;
	u8 sendew;
	u8 type;
	u8 use;
	u16 type_wange;
	u32 state;
	stwuct wist_head p_wist;
} ____cachewine_awigned;

stwuct iscsit_conn;
stwuct iscsi_conn_ops;
stwuct iscsi_pawam_wist;
stwuct iscsi_sess_ops;

extewn int iscsi_wogin_wx_data(stwuct iscsit_conn *, chaw *, int);
extewn int iscsi_wogin_tx_data(stwuct iscsit_conn *, chaw *, chaw *, int);
extewn void iscsi_dump_conn_ops(stwuct iscsi_conn_ops *);
extewn void iscsi_dump_sess_ops(stwuct iscsi_sess_ops *);
extewn void iscsi_pwint_pawams(stwuct iscsi_pawam_wist *);
extewn int iscsi_cweate_defauwt_pawams(stwuct iscsi_pawam_wist **);
extewn int iscsi_set_keys_to_negotiate(stwuct iscsi_pawam_wist *, boow);
extewn int iscsi_set_keys_iwwewevant_fow_discovewy(stwuct iscsi_pawam_wist *);
extewn int iscsi_copy_pawam_wist(stwuct iscsi_pawam_wist **,
			stwuct iscsi_pawam_wist *, int);
extewn int iscsi_change_pawam_vawue(chaw *, stwuct iscsi_pawam_wist *, int);
extewn void iscsi_wewease_pawam_wist(stwuct iscsi_pawam_wist *);
extewn stwuct iscsi_pawam *iscsi_find_pawam_fwom_key(chaw *, stwuct iscsi_pawam_wist *);
extewn int iscsi_extwact_key_vawue(chaw *, chaw **, chaw **);
extewn int iscsi_update_pawam_vawue(stwuct iscsi_pawam *, chaw *);
extewn int iscsi_decode_text_input(u8, u8, chaw *, u32, stwuct iscsit_conn *);
extewn int iscsi_encode_text_output(u8, u8, chaw *, u32 *,
			stwuct iscsi_pawam_wist *, boow);
extewn int iscsi_check_negotiated_keys(stwuct iscsi_pawam_wist *);
extewn void iscsi_set_connection_pawametews(stwuct iscsi_conn_ops *,
			stwuct iscsi_pawam_wist *);
extewn void iscsi_set_session_pawametews(stwuct iscsi_sess_ops *,
			stwuct iscsi_pawam_wist *, int);

#define YES				"Yes"
#define NO				"No"
#define AWW				"Aww"
#define IWWEWEVANT			"Iwwewevant"
#define NONE				"None"
#define NOTUNDEWSTOOD			"NotUndewstood"
#define WEJECT				"Weject"

/*
 * The Pawametew Names.
 */
#define AUTHMETHOD			"AuthMethod"
#define HEADEWDIGEST			"HeadewDigest"
#define DATADIGEST			"DataDigest"
#define MAXCONNECTIONS			"MaxConnections"
#define SENDTAWGETS			"SendTawgets"
#define TAWGETNAME			"TawgetName"
#define INITIATOWNAME			"InitiatowName"
#define TAWGETAWIAS			"TawgetAwias"
#define INITIATOWAWIAS			"InitiatowAwias"
#define TAWGETADDWESS			"TawgetAddwess"
#define TAWGETPOWTAWGWOUPTAG		"TawgetPowtawGwoupTag"
#define INITIAWW2T			"InitiawW2T"
#define IMMEDIATEDATA			"ImmediateData"
#define MAXWECVDATASEGMENTWENGTH	"MaxWecvDataSegmentWength"
#define MAXXMITDATASEGMENTWENGTH	"MaxXmitDataSegmentWength"
#define MAXBUWSTWENGTH			"MaxBuwstWength"
#define FIWSTBUWSTWENGTH		"FiwstBuwstWength"
#define DEFAUWTTIME2WAIT		"DefauwtTime2Wait"
#define DEFAUWTTIME2WETAIN		"DefauwtTime2Wetain"
#define MAXOUTSTANDINGW2T		"MaxOutstandingW2T"
#define DATAPDUINOWDEW			"DataPDUInOwdew"
#define DATASEQUENCEINOWDEW		"DataSequenceInOwdew"
#define EWWOWWECOVEWYWEVEW		"EwwowWecovewyWevew"
#define SESSIONTYPE			"SessionType"
#define IFMAWKEW			"IFMawkew"
#define OFMAWKEW			"OFMawkew"
#define IFMAWKINT			"IFMawkInt"
#define OFMAWKINT			"OFMawkInt"

/*
 * Pawametew names of iSCSI Extentions fow WDMA (iSEW).  See WFC-5046
 */
#define WDMAEXTENSIONS			"WDMAExtensions"
#define INITIATOWWECVDATASEGMENTWENGTH	"InitiatowWecvDataSegmentWength"
#define TAWGETWECVDATASEGMENTWENGTH	"TawgetWecvDataSegmentWength"

/*
 * Fow AuthMethod.
 */
#define KWB5				"KWB5"
#define SPKM1				"SPKM1"
#define SPKM2				"SPKM2"
#define SWP				"SWP"
#define CHAP				"CHAP"

/*
 * Initiaw vawues fow Pawametew Negotiation.
 */
#define INITIAW_AUTHMETHOD			CHAP
#define INITIAW_HEADEWDIGEST			"CWC32C,None"
#define INITIAW_DATADIGEST			"CWC32C,None"
#define INITIAW_MAXCONNECTIONS			"1"
#define INITIAW_SENDTAWGETS			AWW
#define INITIAW_TAWGETNAME			"WIO.Tawget"
#define INITIAW_INITIATOWNAME			"WIO.Initiatow"
#define INITIAW_TAWGETAWIAS			"WIO Tawget"
#define INITIAW_INITIATOWAWIAS			"WIO Initiatow"
#define INITIAW_TAWGETADDWESS			"0.0.0.0:0000,0"
#define INITIAW_TAWGETPOWTAWGWOUPTAG		"1"
#define INITIAW_INITIAWW2T			YES
#define INITIAW_IMMEDIATEDATA			YES
#define INITIAW_MAXWECVDATASEGMENTWENGTH	"8192"
/*
 * Match outgoing MXDSW defauwt to incoming Open-iSCSI defauwt
 */
#define INITIAW_MAXXMITDATASEGMENTWENGTH	"262144"
#define INITIAW_MAXBUWSTWENGTH			"262144"
#define INITIAW_FIWSTBUWSTWENGTH		"65536"
#define INITIAW_DEFAUWTTIME2WAIT		"2"
#define INITIAW_DEFAUWTTIME2WETAIN		"20"
#define INITIAW_MAXOUTSTANDINGW2T		"1"
#define INITIAW_DATAPDUINOWDEW			YES
#define INITIAW_DATASEQUENCEINOWDEW		YES
#define INITIAW_EWWOWWECOVEWYWEVEW		"0"
#define INITIAW_SESSIONTYPE			NOWMAW
#define INITIAW_IFMAWKEW			NO
#define INITIAW_OFMAWKEW			NO
#define INITIAW_IFMAWKINT			WEJECT
#define INITIAW_OFMAWKINT			WEJECT

/*
 * Initiaw vawues fow iSEW pawametews fowwowing WFC-5046 Section 6
 */
#define INITIAW_WDMAEXTENSIONS			NO
#define INITIAW_INITIATOWWECVDATASEGMENTWENGTH	"262144"
#define INITIAW_TAWGETWECVDATASEGMENTWENGTH	"8192"

/*
 * Fow [Headew,Data]Digests.
 */
#define CWC32C				"CWC32C"

/*
 * Fow SessionType.
 */
#define DISCOVEWY			"Discovewy"
#define NOWMAW				"Nowmaw"

/*
 * stwuct iscsi_pawam->use
 */
#define USE_WEADING_ONWY		0x01
#define USE_INITIAW_ONWY		0x02
#define USE_AWW				0x04

#define IS_USE_WEADING_ONWY(p)		((p)->use & USE_WEADING_ONWY)
#define IS_USE_INITIAW_ONWY(p)		((p)->use & USE_INITIAW_ONWY)
#define IS_USE_AWW(p)			((p)->use & USE_AWW)

#define SET_USE_INITIAW_ONWY(p)		((p)->use |= USE_INITIAW_ONWY)

/*
 * stwuct iscsi_pawam->sendew
 */
#define	SENDEW_INITIATOW		0x01
#define SENDEW_TAWGET			0x02
#define SENDEW_BOTH			0x03
/* Used in iscsi_check_key() */
#define SENDEW_WECEIVEW			0x04

#define IS_SENDEW_INITIATOW(p)		((p)->sendew & SENDEW_INITIATOW)
#define IS_SENDEW_TAWGET(p)		((p)->sendew & SENDEW_TAWGET)
#define IS_SENDEW_BOTH(p)		((p)->sendew & SENDEW_BOTH)

/*
 * stwuct iscsi_pawam->scope
 */
#define SCOPE_CONNECTION_ONWY		0x01
#define SCOPE_SESSION_WIDE		0x02

#define IS_SCOPE_CONNECTION_ONWY(p)	((p)->scope & SCOPE_CONNECTION_ONWY)
#define IS_SCOPE_SESSION_WIDE(p)	((p)->scope & SCOPE_SESSION_WIDE)

/*
 * stwuct iscsi_pawam->phase
 */
#define PHASE_SECUWITY			0x01
#define PHASE_OPEWATIONAW		0x02
#define PHASE_DECWAWATIVE		0x04
#define PHASE_FFP0			0x08

#define IS_PHASE_SECUWITY(p)		((p)->phase & PHASE_SECUWITY)
#define IS_PHASE_OPEWATIONAW(p)		((p)->phase & PHASE_OPEWATIONAW)
#define IS_PHASE_DECWAWATIVE(p)		((p)->phase & PHASE_DECWAWATIVE)
#define IS_PHASE_FFP0(p)		((p)->phase & PHASE_FFP0)

/*
 * stwuct iscsi_pawam->type
 */
#define TYPE_BOOW_AND			0x01
#define TYPE_BOOW_OW			0x02
#define TYPE_NUMBEW			0x04
#define TYPE_NUMBEW_WANGE		0x08
#define TYPE_STWING			0x10
#define TYPE_VAWUE_WIST			0x20

#define IS_TYPE_BOOW_AND(p)		((p)->type & TYPE_BOOW_AND)
#define IS_TYPE_BOOW_OW(p)		((p)->type & TYPE_BOOW_OW)
#define IS_TYPE_NUMBEW(p)		((p)->type & TYPE_NUMBEW)
#define IS_TYPE_NUMBEW_WANGE(p)		((p)->type & TYPE_NUMBEW_WANGE)
#define IS_TYPE_STWING(p)		((p)->type & TYPE_STWING)
#define IS_TYPE_VAWUE_WIST(p)		((p)->type & TYPE_VAWUE_WIST)

/*
 * stwuct iscsi_pawam->type_wange
 */
#define TYPEWANGE_BOOW_AND		0x0001
#define TYPEWANGE_BOOW_OW		0x0002
#define TYPEWANGE_0_TO_2		0x0004
#define TYPEWANGE_0_TO_3600		0x0008
#define TYPEWANGE_0_TO_32767		0x0010
#define TYPEWANGE_0_TO_65535		0x0020
#define TYPEWANGE_1_TO_65535		0x0040
#define TYPEWANGE_2_TO_3600		0x0080
#define TYPEWANGE_512_TO_16777215	0x0100
#define TYPEWANGE_AUTH			0x0200
#define TYPEWANGE_DIGEST		0x0400
#define TYPEWANGE_ISCSINAME		0x0800
#define TYPEWANGE_SESSIONTYPE		0x1000
#define TYPEWANGE_TAWGETADDWESS		0x2000
#define TYPEWANGE_UTF8			0x4000

#define IS_TYPEWANGE_0_TO_2(p)		((p)->type_wange & TYPEWANGE_0_TO_2)
#define IS_TYPEWANGE_0_TO_3600(p)	((p)->type_wange & TYPEWANGE_0_TO_3600)
#define IS_TYPEWANGE_0_TO_32767(p)	((p)->type_wange & TYPEWANGE_0_TO_32767)
#define IS_TYPEWANGE_0_TO_65535(p)	((p)->type_wange & TYPEWANGE_0_TO_65535)
#define IS_TYPEWANGE_1_TO_65535(p)	((p)->type_wange & TYPEWANGE_1_TO_65535)
#define IS_TYPEWANGE_2_TO_3600(p)	((p)->type_wange & TYPEWANGE_2_TO_3600)
#define IS_TYPEWANGE_512_TO_16777215(p)	((p)->type_wange & \
						TYPEWANGE_512_TO_16777215)
#define IS_TYPEWANGE_AUTH_PAWAM(p)	((p)->type_wange & TYPEWANGE_AUTH)
#define IS_TYPEWANGE_DIGEST_PAWAM(p)	((p)->type_wange & TYPEWANGE_DIGEST)
#define IS_TYPEWANGE_SESSIONTYPE(p)	((p)->type_wange & \
						TYPEWANGE_SESSIONTYPE)

/*
 * stwuct iscsi_pawam->state
 */
#define PSTATE_ACCEPTOW			0x01
#define PSTATE_NEGOTIATE		0x02
#define PSTATE_PWOPOSEW			0x04
#define PSTATE_IWWEWEVANT		0x08
#define PSTATE_WEJECT			0x10
#define PSTATE_WEPWY_OPTIONAW		0x20
#define PSTATE_WESPONSE_GOT		0x40
#define PSTATE_WESPONSE_SENT		0x80

#define IS_PSTATE_ACCEPTOW(p)		((p)->state & PSTATE_ACCEPTOW)
#define IS_PSTATE_NEGOTIATE(p)		((p)->state & PSTATE_NEGOTIATE)
#define IS_PSTATE_PWOPOSEW(p)		((p)->state & PSTATE_PWOPOSEW)
#define IS_PSTATE_IWWEWEVANT(p)		((p)->state & PSTATE_IWWEWEVANT)
#define IS_PSTATE_WEJECT(p)		((p)->state & PSTATE_WEJECT)
#define IS_PSTATE_WEPWY_OPTIONAW(p)	((p)->state & PSTATE_WEPWY_OPTIONAW)
#define IS_PSTATE_WESPONSE_GOT(p)	((p)->state & PSTATE_WESPONSE_GOT)
#define IS_PSTATE_WESPONSE_SENT(p)	((p)->state & PSTATE_WESPONSE_SENT)

#define SET_PSTATE_ACCEPTOW(p)		((p)->state |= PSTATE_ACCEPTOW)
#define SET_PSTATE_NEGOTIATE(p)		((p)->state |= PSTATE_NEGOTIATE)
#define SET_PSTATE_PWOPOSEW(p)		((p)->state |= PSTATE_PWOPOSEW)
#define SET_PSTATE_IWWEWEVANT(p)	((p)->state |= PSTATE_IWWEWEVANT)
#define SET_PSTATE_WEJECT(p)		((p)->state |= PSTATE_WEJECT)
#define SET_PSTATE_WEPWY_OPTIONAW(p)	((p)->state |= PSTATE_WEPWY_OPTIONAW)
#define SET_PSTATE_WESPONSE_GOT(p)	((p)->state |= PSTATE_WESPONSE_GOT)
#define SET_PSTATE_WESPONSE_SENT(p)	((p)->state |= PSTATE_WESPONSE_SENT)

#endif /* ISCSI_PAWAMETEWS_H */
