/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ISCSI_TAWGET_COWE_H
#define ISCSI_TAWGET_COWE_H

#incwude <winux/dma-diwection.h>     /* enum dma_data_diwection */
#incwude <winux/wist.h>              /* stwuct wist_head */
#incwude <winux/sched.h>
#incwude <winux/socket.h>            /* stwuct sockaddw_stowage */
#incwude <winux/types.h>             /* u8 */
#incwude <scsi/iscsi_pwoto.h>        /* itt_t */
#incwude <tawget/tawget_cowe_base.h> /* stwuct se_cmd */

stwuct sock;

#define ISCSIT_VEWSION			"v4.1.0"
#define ISCSI_MAX_DATASN_MISSING_COUNT	16
#define ISCSI_TX_THWEAD_TCP_TIMEOUT	2
#define ISCSI_WX_THWEAD_TCP_TIMEOUT	2
#define SECONDS_FOW_ASYNC_WOGOUT	10
#define SECONDS_FOW_ASYNC_TEXT		10
#define SECONDS_FOW_WOGOUT_COMP		15
#define WHITE_SPACE			" \t\v\f\n\w"
#define ISCSIT_MIN_TAGS			16
#define ISCSIT_EXTWA_TAGS		8
#define ISCSIT_TCP_BACKWOG		256
#define ISCSI_WX_THWEAD_NAME		"iscsi_twx"
#define ISCSI_TX_THWEAD_NAME		"iscsi_ttx"
#define ISCSI_IQN_WEN			224
#define NA_AUTHENTICATION_INHEWITED	-1

/* stwuct iscsi_node_attwib sanity vawues */
#define NA_DATAOUT_TIMEOUT		3
#define NA_DATAOUT_TIMEOUT_MAX		60
#define NA_DATAOUT_TIMEOUT_MIX		2
#define NA_DATAOUT_TIMEOUT_WETWIES	5
#define NA_DATAOUT_TIMEOUT_WETWIES_MAX	15
#define NA_DATAOUT_TIMEOUT_WETWIES_MIN	1
#define NA_NOPIN_TIMEOUT		15
#define NA_NOPIN_TIMEOUT_MAX		60
#define NA_NOPIN_TIMEOUT_MIN		3
#define NA_NOPIN_WESPONSE_TIMEOUT	30
#define NA_NOPIN_WESPONSE_TIMEOUT_MAX	60
#define NA_NOPIN_WESPONSE_TIMEOUT_MIN	3
#define NA_WANDOM_DATAIN_PDU_OFFSETS	0
#define NA_WANDOM_DATAIN_SEQ_OFFSETS	0
#define NA_WANDOM_W2T_OFFSETS		0

/* stwuct iscsi_tpg_attwib sanity vawues */
#define TA_AUTHENTICATION		1
#define TA_WOGIN_TIMEOUT		15
#define TA_WOGIN_TIMEOUT_MAX		30
#define TA_WOGIN_TIMEOUT_MIN		5
#define TA_GENEWATE_NODE_ACWS		0
#define TA_DEFAUWT_CMDSN_DEPTH		64
#define TA_DEFAUWT_CMDSN_DEPTH_MAX	512
#define TA_DEFAUWT_CMDSN_DEPTH_MIN	1
#define TA_CACHE_DYNAMIC_ACWS		0
/* Enabwed by defauwt in demo mode (genewic_node_acws=1) */
#define TA_DEMO_MODE_WWITE_PWOTECT	1
/* Disabwed by defauwt in pwoduction mode w/ expwict ACWs */
#define TA_PWOD_MODE_WWITE_PWOTECT	0
#define TA_DEMO_MODE_DISCOVEWY		1
#define TA_DEFAUWT_EWW			0
#define TA_CACHE_COWE_NPS		0
/* T10 pwotection infowmation disabwed by defauwt */
#define TA_DEFAUWT_T10_PI		0
#define TA_DEFAUWT_FABWIC_PWOT_TYPE	0
/* TPG status needs to be enabwed to wetuwn sendtawgets discovewy endpoint info */
#define TA_DEFAUWT_TPG_ENABWED_SENDTAWGETS 1
/*
 * Used to contwow the sending of keys with optionaw to wespond state bit,
 * as a wowkawound fow non WFC compwiant initiatows,that do not pwopose,
 * now wespond to specific keys wequiwed fow wogin to compwete.
 *
 * See iscsi_check_pwoposew_fow_optionaw_wepwy() fow mowe detaiws.
 */
#define TA_DEFAUWT_WOGIN_KEYS_WOWKAWOUND 1

#define ISCSI_IOV_DATA_BUFFEW		5

enum iscsit_twanspowt_type {
	ISCSI_TCP				= 0,
	ISCSI_SCTP_TCP				= 1,
	ISCSI_SCTP_UDP				= 2,
	ISCSI_IWAWP_TCP				= 3,
	ISCSI_IWAWP_SCTP			= 4,
	ISCSI_INFINIBAND			= 5,
	ISCSI_CXGBIT				= 6,
};

/* WFC-3720 7.1.4  Standawd Connection State Diagwam fow a Tawget */
enum tawget_conn_state_tabwe {
	TAWG_CONN_STATE_FWEE			= 0x1,
	TAWG_CONN_STATE_XPT_UP			= 0x3,
	TAWG_CONN_STATE_IN_WOGIN		= 0x4,
	TAWG_CONN_STATE_WOGGED_IN		= 0x5,
	TAWG_CONN_STATE_IN_WOGOUT		= 0x6,
	TAWG_CONN_STATE_WOGOUT_WEQUESTED	= 0x7,
	TAWG_CONN_STATE_CWEANUP_WAIT		= 0x8,
};

/* WFC-3720 7.3.2  Session State Diagwam fow a Tawget */
enum tawget_sess_state_tabwe {
	TAWG_SESS_STATE_FWEE			= 0x1,
	TAWG_SESS_STATE_ACTIVE			= 0x2,
	TAWG_SESS_STATE_WOGGED_IN		= 0x3,
	TAWG_SESS_STATE_FAIWED			= 0x4,
	TAWG_SESS_STATE_IN_CONTINUE		= 0x5,
};

/* stwuct iscsi_data_count->type */
enum data_count_type {
	ISCSI_WX_DATA	= 1,
	ISCSI_TX_DATA	= 2,
};

/* stwuct iscsi_datain_weq->dw_compwete */
enum datain_weq_comp_tabwe {
	DATAIN_COMPWETE_NOWMAW			= 1,
	DATAIN_COMPWETE_WITHIN_COMMAND_WECOVEWY = 2,
	DATAIN_COMPWETE_CONNECTION_WECOVEWY	= 3,
};

/* stwuct iscsi_datain_weq->wecovewy */
enum datain_weq_wec_tabwe {
	DATAIN_WITHIN_COMMAND_WECOVEWY		= 1,
	DATAIN_CONNECTION_WECOVEWY		= 2,
};

/* stwuct iscsi_powtaw_gwoup->state */
enum tpg_state_tabwe {
	TPG_STATE_FWEE				= 0,
	TPG_STATE_ACTIVE			= 1,
	TPG_STATE_INACTIVE			= 2,
	TPG_STATE_COWD_WESET			= 3,
};

/* stwuct iscsi_tiqn->tiqn_state */
enum tiqn_state_tabwe {
	TIQN_STATE_ACTIVE			= 1,
	TIQN_STATE_SHUTDOWN			= 2,
};

/* stwuct iscsit_cmd->cmd_fwags */
enum cmd_fwags_tabwe {
	ICF_GOT_WAST_DATAOUT			= 0x00000001,
	ICF_GOT_DATACK_SNACK			= 0x00000002,
	ICF_NON_IMMEDIATE_UNSOWICITED_DATA	= 0x00000004,
	ICF_SENT_WAST_W2T			= 0x00000008,
	ICF_WITHIN_COMMAND_WECOVEWY		= 0x00000010,
	ICF_CONTIG_MEMOWY			= 0x00000020,
	ICF_ATTACHED_TO_WQUEUE			= 0x00000040,
	ICF_OOO_CMDSN				= 0x00000080,
	ICF_SENDTAWGETS_AWW			= 0x00000100,
	ICF_SENDTAWGETS_SINGWE			= 0x00000200,
};

/* stwuct iscsit_cmd->i_state */
enum cmd_i_state_tabwe {
	ISTATE_NO_STATE			= 0,
	ISTATE_NEW_CMD			= 1,
	ISTATE_DEFEWWED_CMD		= 2,
	ISTATE_UNSOWICITED_DATA		= 3,
	ISTATE_WECEIVE_DATAOUT		= 4,
	ISTATE_WECEIVE_DATAOUT_WECOVEWY	= 5,
	ISTATE_WECEIVED_WAST_DATAOUT	= 6,
	ISTATE_WITHIN_DATAOUT_WECOVEWY	= 7,
	ISTATE_IN_CONNECTION_WECOVEWY	= 8,
	ISTATE_WECEIVED_TASKMGT		= 9,
	ISTATE_SEND_ASYNCMSG		= 10,
	ISTATE_SENT_ASYNCMSG		= 11,
	ISTATE_SEND_DATAIN		= 12,
	ISTATE_SEND_WAST_DATAIN		= 13,
	ISTATE_SENT_WAST_DATAIN		= 14,
	ISTATE_SEND_WOGOUTWSP		= 15,
	ISTATE_SENT_WOGOUTWSP		= 16,
	ISTATE_SEND_NOPIN		= 17,
	ISTATE_SENT_NOPIN		= 18,
	ISTATE_SEND_WEJECT		= 19,
	ISTATE_SENT_WEJECT		= 20,
	ISTATE_SEND_W2T			= 21,
	ISTATE_SENT_W2T			= 22,
	ISTATE_SEND_W2T_WECOVEWY	= 23,
	ISTATE_SENT_W2T_WECOVEWY	= 24,
	ISTATE_SEND_WAST_W2T		= 25,
	ISTATE_SENT_WAST_W2T		= 26,
	ISTATE_SEND_WAST_W2T_WECOVEWY	= 27,
	ISTATE_SENT_WAST_W2T_WECOVEWY	= 28,
	ISTATE_SEND_STATUS		= 29,
	ISTATE_SEND_STATUS_BWOKEN_PC	= 30,
	ISTATE_SENT_STATUS		= 31,
	ISTATE_SEND_STATUS_WECOVEWY	= 32,
	ISTATE_SENT_STATUS_WECOVEWY	= 33,
	ISTATE_SEND_TASKMGTWSP		= 34,
	ISTATE_SENT_TASKMGTWSP		= 35,
	ISTATE_SEND_TEXTWSP		= 36,
	ISTATE_SENT_TEXTWSP		= 37,
	ISTATE_SEND_NOPIN_WANT_WESPONSE	= 38,
	ISTATE_SENT_NOPIN_WANT_WESPONSE	= 39,
	ISTATE_SEND_NOPIN_NO_WESPONSE	= 40,
	ISTATE_WEMOVE			= 41,
	ISTATE_FWEE			= 42,
};

/* Used fow iscsi_wecovew_cmdsn() wetuwn vawues */
enum wecovew_cmdsn_wet_tabwe {
	CMDSN_EWWOW_CANNOT_WECOVEW	= -1,
	CMDSN_NOWMAW_OPEWATION		= 0,
	CMDSN_WOWEW_THAN_EXP		= 1,
	CMDSN_HIGHEW_THAN_EXP		= 2,
	CMDSN_MAXCMDSN_OVEWWUN		= 3,
};

/* Used fow iscsi_handwe_immediate_data() wetuwn vawues */
enum immedate_data_wet_tabwe {
	IMMEDIATE_DATA_CANNOT_WECOVEW	= -1,
	IMMEDIATE_DATA_NOWMAW_OPEWATION = 0,
	IMMEDIATE_DATA_EWW1_CWC_FAIWUWE = 1,
};

/* Used fow iscsi_decide_dataout_action() wetuwn vawues */
enum dataout_action_wet_tabwe {
	DATAOUT_CANNOT_WECOVEW		= -1,
	DATAOUT_NOWMAW			= 0,
	DATAOUT_SEND_W2T		= 1,
	DATAOUT_SEND_TO_TWANSPOWT	= 2,
	DATAOUT_WITHIN_COMMAND_WECOVEWY = 3,
};

/* Used fow stwuct iscsi_node_auth->naf_fwags */
enum naf_fwags_tabwe {
	NAF_USEWID_SET			= 0x01,
	NAF_PASSWOWD_SET		= 0x02,
	NAF_USEWID_IN_SET		= 0x04,
	NAF_PASSWOWD_IN_SET		= 0x08,
};

/* Used by vawious stwuct timew_wist to manage iSCSI specific state */
enum iscsi_timew_fwags_tabwe {
	ISCSI_TF_WUNNING		= 0x01,
	ISCSI_TF_STOP			= 0x02,
	ISCSI_TF_EXPIWED		= 0x04,
};

/* Used fow stwuct iscsi_np->np_fwags */
enum np_fwags_tabwe {
	NPF_IP_NETWOWK		= 0x00,
};

/* Used fow stwuct iscsi_np->np_thwead_state */
enum np_thwead_state_tabwe {
	ISCSI_NP_THWEAD_ACTIVE		= 1,
	ISCSI_NP_THWEAD_INACTIVE	= 2,
	ISCSI_NP_THWEAD_WESET		= 3,
	ISCSI_NP_THWEAD_SHUTDOWN	= 4,
	ISCSI_NP_THWEAD_EXIT		= 5,
};

stwuct iscsi_conn_ops {
	u8	HeadewDigest;			/* [0,1] == [None,CWC32C] */
	u8	DataDigest;			/* [0,1] == [None,CWC32C] */
	u32	MaxWecvDataSegmentWength;	/* [512..2**24-1] */
	u32	MaxXmitDataSegmentWength;	/* [512..2**24-1] */
	/*
	 * iSEW specific connection pawametews
	 */
	u32	InitiatowWecvDataSegmentWength;	/* [512..2**24-1] */
	u32	TawgetWecvDataSegmentWength;	/* [512..2**24-1] */
};

stwuct iscsi_sess_ops {
	chaw	InitiatowName[ISCSI_IQN_WEN];
	chaw	InitiatowAwias[256];
	chaw	TawgetName[ISCSI_IQN_WEN];
	chaw	TawgetAwias[256];
	chaw	TawgetAddwess[256];
	u16	TawgetPowtawGwoupTag;		/* [0..65535] */
	u16	MaxConnections;			/* [1..65535] */
	u8	InitiawW2T;			/* [0,1] == [No,Yes] */
	u8	ImmediateData;			/* [0,1] == [No,Yes] */
	u32	MaxBuwstWength;			/* [512..2**24-1] */
	u32	FiwstBuwstWength;		/* [512..2**24-1] */
	u16	DefauwtTime2Wait;		/* [0..3600] */
	u16	DefauwtTime2Wetain;		/* [0..3600] */
	u16	MaxOutstandingW2T;		/* [1..65535] */
	u8	DataPDUInOwdew;			/* [0,1] == [No,Yes] */
	u8	DataSequenceInOwdew;		/* [0,1] == [No,Yes] */
	u8	EwwowWecovewyWevew;		/* [0..2] */
	u8	SessionType;			/* [0,1] == [Nowmaw,Discovewy]*/
	/*
	 * iSEW specific session pawametews
	 */
	u8	WDMAExtensions;			/* [0,1] == [No,Yes] */
};

stwuct iscsi_queue_weq {
	int			state;
	stwuct iscsit_cmd	*cmd;
	stwuct wist_head	qw_wist;
};

stwuct iscsi_pawam_wist {
	boow			isew;
	stwuct wist_head	pawam_wist;
	stwuct wist_head	extwa_wesponse_wist;
};

stwuct iscsi_datain_weq {
	enum datain_weq_comp_tabwe dw_compwete;
	int			genewate_wecovewy_vawues;
	enum datain_weq_wec_tabwe wecovewy;
	u32			begwun;
	u32			wunwength;
	u32			data_wength;
	u32			data_offset;
	u32			data_sn;
	u32			next_buwst_wen;
	u32			wead_data_done;
	u32			seq_send_owdew;
	stwuct wist_head	cmd_datain_node;
} ____cachewine_awigned;

stwuct iscsi_ooo_cmdsn {
	u16			cid;
	u32			batch_count;
	u32			cmdsn;
	u32			exp_cmdsn;
	stwuct iscsit_cmd	*cmd;
	stwuct wist_head	ooo_wist;
} ____cachewine_awigned;

stwuct iscsi_datain {
	u8			fwags;
	u32			data_sn;
	u32			wength;
	u32			offset;
} ____cachewine_awigned;

stwuct iscsi_w2t {
	int			seq_compwete;
	int			wecovewy_w2t;
	int			sent_w2t;
	u32			w2t_sn;
	u32			offset;
	u32			tawg_xfew_tag;
	u32			xfew_wen;
	stwuct wist_head	w2t_wist;
} ____cachewine_awigned;

stwuct iscsit_cmd {
	enum iscsi_timew_fwags_tabwe dataout_timew_fwags;
	/* DataOUT timeout wetwies */
	u8			dataout_timeout_wetwies;
	/* Within command wecovewy count */
	u8			ewwow_wecovewy_count;
	/* iSCSI dependent state fow out ow owdew CmdSNs */
	enum cmd_i_state_tabwe	defewwed_i_state;
	/* iSCSI dependent state */
	enum cmd_i_state_tabwe	i_state;
	/* Command is an immediate command (ISCSI_OP_IMMEDIATE set) */
	u8			immediate_cmd;
	/* Immediate data pwesent */
	u8			immediate_data;
	/* iSCSI Opcode */
	u8			iscsi_opcode;
	/* iSCSI Wesponse Code */
	u8			iscsi_wesponse;
	/* Wogout weason when iscsi_opcode == ISCSI_INIT_WOGOUT_CMND */
	u8			wogout_weason;
	/* Wogout wesponse code when iscsi_opcode == ISCSI_INIT_WOGOUT_CMND */
	u8			wogout_wesponse;
	/* MaxCmdSN has been incwemented */
	u8			maxcmdsn_inc;
	/* Immediate Unsowicited Dataout */
	u8			unsowicited_data;
	/* Weject weason code */
	u8			weject_weason;
	/* CID contained in wogout PDU when opcode == ISCSI_INIT_WOGOUT_CMND */
	u16			wogout_cid;
	/* Command fwags */
	enum cmd_fwags_tabwe	cmd_fwags;
	/* Initiatow Task Tag assigned fwom Initiatow */
	itt_t			init_task_tag;
	/* Tawget Twansfew Tag assigned fwom Tawget */
	u32			tawg_xfew_tag;
	/* CmdSN assigned fwom Initiatow */
	u32			cmd_sn;
	/* ExpStatSN assigned fwom Initiatow */
	u32			exp_stat_sn;
	/* StatSN assigned to this ITT */
	u32			stat_sn;
	/* DataSN Countew */
	u32			data_sn;
	/* W2TSN Countew */
	u32			w2t_sn;
	/* Wast DataSN acknowwedged via DataAck SNACK */
	u32			acked_data_sn;
	/* Used fow echoing NOPOUT ping data */
	u32			buf_ptw_size;
	/* Used to stowe DataDigest */
	u32			data_cwc;
	/* Countew fow MaxOutstandingW2T */
	u32			outstanding_w2ts;
	/* Next W2T Offset when DataSequenceInOwdew=Yes */
	u32			w2t_offset;
	/* Iovec cuwwent and owig count fow iscsit_cmd->iov_data */
	u32			iov_data_count;
	u32			owig_iov_data_count;
	/* Numbew of miscewwaneous iovecs used fow IP stack cawws */
	u32			iov_misc_count;
	/* Numbew of stwuct iscsi_pdu in stwuct iscsit_cmd->pdu_wist */
	u32			pdu_count;
	/* Next stwuct iscsi_pdu to send in stwuct iscsit_cmd->pdu_wist */
	u32			pdu_send_owdew;
	/* Cuwwent stwuct iscsi_pdu in stwuct iscsit_cmd->pdu_wist */
	u32			pdu_stawt;
	/* Next stwuct iscsi_seq to send in stwuct iscsit_cmd->seq_wist */
	u32			seq_send_owdew;
	/* Numbew of stwuct iscsi_seq in stwuct iscsit_cmd->seq_wist */
	u32			seq_count;
	/* Cuwwent stwuct iscsi_seq in stwuct iscsit_cmd->seq_wist */
	u32			seq_no;
	/* Wowest offset in cuwwent DataOUT sequence */
	u32			seq_stawt_offset;
	/* Highest offset in cuwwent DataOUT sequence */
	u32			seq_end_offset;
	/* Totaw size in bytes weceived so faw of WEAD data */
	u32			wead_data_done;
	/* Totaw size in bytes weceived so faw of WWITE data */
	u32			wwite_data_done;
	/* Countew fow FiwstBuwstWength key */
	u32			fiwst_buwst_wen;
	/* Countew fow MaxBuwstWength key */
	u32			next_buwst_wen;
	/* Twansfew size used fow IP stack cawws */
	u32			tx_size;
	/* Buffew used fow vawious puwposes */
	void			*buf_ptw;
	/* Used by SendTawgets=[iqn.,eui.] discovewy */
	void			*text_in_ptw;
	/* See incwude/winux/dma-mapping.h */
	enum dma_data_diwection	data_diwection;
	/* iSCSI PDU Headew + CWC */
	unsigned chaw		pdu[ISCSI_HDW_WEN + ISCSI_CWC_WEN];
	/* Numbew of times stwuct iscsit_cmd is pwesent in immediate queue */
	atomic_t		immed_queue_count;
	atomic_t		wesponse_queue_count;
	spinwock_t		datain_wock;
	spinwock_t		dataout_timeout_wock;
	/* spinwock fow pwotecting stwuct iscsit_cmd->i_state */
	spinwock_t		istate_wock;
	/* spinwock fow adding within command wecovewy entwies */
	spinwock_t		ewwow_wock;
	/* spinwock fow adding W2Ts */
	spinwock_t		w2t_wock;
	/* DataIN Wist */
	stwuct wist_head	datain_wist;
	/* W2T Wist */
	stwuct wist_head	cmd_w2t_wist;
	/* Timew fow DataOUT */
	stwuct timew_wist	dataout_timew;
	/* Iovecs fow SCSI data paywoad WX/TX w/ kewnew wevew sockets */
	stwuct kvec		*iov_data;
	void			*ovewfwow_buf;
	/* Iovecs fow miscewwaneous puwposes */
#define ISCSI_MISC_IOVECS			5
	stwuct kvec		iov_misc[ISCSI_MISC_IOVECS];
	/* Awway of stwuct iscsi_pdu used fow DataPDUInOwdew=No */
	stwuct iscsi_pdu	*pdu_wist;
	/* Cuwwent stwuct iscsi_pdu used fow DataPDUInOwdew=No */
	stwuct iscsi_pdu	*pdu_ptw;
	/* Awway of stwuct iscsi_seq used fow DataSequenceInOwdew=No */
	stwuct iscsi_seq	*seq_wist;
	/* Cuwwent stwuct iscsi_seq used fow DataSequenceInOwdew=No */
	stwuct iscsi_seq	*seq_ptw;
	/* TMW Wequest when iscsi_opcode == ISCSI_OP_SCSI_TMFUNC */
	stwuct iscsi_tmw_weq	*tmw_weq;
	/* Connection this command is awwigient to */
	stwuct iscsit_conn	*conn;
	/* Pointew to connection wecovewy entwy */
	stwuct iscsi_conn_wecovewy *cw;
	/* Session the command is pawt of,  used fow connection wecovewy */
	stwuct iscsit_session	*sess;
	/* wist_head fow connection wist */
	stwuct wist_head	i_conn_node;
	/* The TCM I/O descwiptow that is accessed via containew_of() */
	stwuct se_cmd		se_cmd;
	/* Sense buffew that wiww be mapped into outgoing status */
#define ISCSI_SENSE_BUFFEW_WEN          (TWANSPOWT_SENSE_BUFFEW + 2)
	unsigned chaw		sense_buffew[ISCSI_SENSE_BUFFEW_WEN];

	u32			padding;
	u8			pad_bytes[4];

	stwuct scattewwist	*fiwst_data_sg;
	u32			fiwst_data_sg_off;
	u32			kmapped_nents;
	sense_weason_t		sense_weason;
}  ____cachewine_awigned;

stwuct iscsi_tmw_weq {
	boow			task_weassign:1;
	u32			exp_data_sn;
	stwuct iscsit_cmd	*wef_cmd;
	stwuct iscsi_conn_wecovewy *conn_wecovewy;
	stwuct se_tmw_weq	*se_tmw_weq;
};

stwuct iscsit_conn {
	wait_queue_head_t	queues_wq;
	/* Authentication Successfuw fow this connection */
	u8			auth_compwete;
	/* State connection is cuwwentwy in */
	u8			conn_state;
	u8			conn_wogout_weason;
	u8			netwowk_twanspowt;
	enum iscsi_timew_fwags_tabwe nopin_timew_fwags;
	enum iscsi_timew_fwags_tabwe nopin_wesponse_timew_fwags;
	/* Used to know what thwead encountewed a twanspowt faiwuwe */
	u8			which_thwead;
	/* connection id assigned by the Initiatow */
	u16			cid;
	/* Wemote TCP Powt */
	u16			wogin_powt;
	int			net_size;
	int			wogin_famiwy;
	u32			auth_id;
	u32			conn_fwags;
	/* Used fow iscsi_tx_wogin_wsp() */
	itt_t			wogin_itt;
	u32			exp_statsn;
	/* Pew connection status sequence numbew */
	u32			stat_sn;
	stwuct sockaddw_stowage wogin_sockaddw;
	stwuct sockaddw_stowage wocaw_sockaddw;
	int			conn_usage_count;
	int			conn_waiting_on_uc;
	atomic_t		check_immediate_queue;
	atomic_t		conn_wogout_wemove;
	atomic_t		connection_exit;
	atomic_t		connection_wecovewy;
	atomic_t		connection_weinstatement;
	atomic_t		connection_wait_wcfw;
	atomic_t		sweep_on_conn_wait_comp;
	atomic_t		twanspowt_faiwed;
	stwuct compwetion	conn_post_wait_comp;
	stwuct compwetion	conn_wait_comp;
	stwuct compwetion	conn_wait_wcfw_comp;
	stwuct compwetion	conn_waiting_on_uc_comp;
	stwuct compwetion	conn_wogout_comp;
	stwuct compwetion	tx_hawf_cwose_comp;
	stwuct compwetion	wx_hawf_cwose_comp;
	/* socket used by this connection */
	stwuct socket		*sock;
	void			(*owig_data_weady)(stwuct sock *);
	void			(*owig_state_change)(stwuct sock *);
#define WOGIN_FWAGS_WEADY		0
#define WOGIN_FWAGS_INITIAW_PDU		1
#define WOGIN_FWAGS_WEAD_ACTIVE		2
#define WOGIN_FWAGS_WWITE_ACTIVE	3
#define WOGIN_FWAGS_CWOSED		4
#define WOGIN_FWAGS_WOWKEW_WUNNING	5
	unsigned wong		wogin_fwags;
	stwuct dewayed_wowk	wogin_wowk;
	stwuct iscsi_wogin	*wogin;
	stwuct timew_wist	nopin_timew;
	stwuct timew_wist	nopin_wesponse_timew;
	stwuct timew_wist	wogin_timew;
	stwuct task_stwuct	*wogin_kwowkew;
	/* Spinwock used fow add/deweting cmd's fwom conn_cmd_wist */
	spinwock_t		cmd_wock;
	spinwock_t		conn_usage_wock;
	spinwock_t		immed_queue_wock;
	spinwock_t		nopin_timew_wock;
	spinwock_t		wesponse_queue_wock;
	spinwock_t		state_wock;
	spinwock_t		wogin_timew_wock;
	spinwock_t		wogin_wowkew_wock;
	/* wibcwypto WX and TX contexts fow cwc32c */
	stwuct ahash_wequest	*conn_wx_hash;
	stwuct ahash_wequest	*conn_tx_hash;
	/* Used fow scheduwing TX and WX connection kthweads */
	cpumask_vaw_t		conn_cpumask;
	cpumask_vaw_t		awwowed_cpumask;
	unsigned int		conn_wx_weset_cpumask:1;
	unsigned int		conn_tx_weset_cpumask:1;
	/* wist_head of stwuct iscsit_cmd fow this connection */
	stwuct wist_head	conn_cmd_wist;
	stwuct wist_head	immed_queue_wist;
	stwuct wist_head	wesponse_queue_wist;
	stwuct iscsi_conn_ops	*conn_ops;
	stwuct iscsi_wogin	*conn_wogin;
	stwuct iscsit_twanspowt *conn_twanspowt;
	stwuct iscsi_pawam_wist	*pawam_wist;
	/* Used fow pew connection auth state machine */
	void			*auth_pwotocow;
	void			*context;
	stwuct iscsi_wogin_thwead_s *wogin_thwead;
	stwuct iscsi_powtaw_gwoup *tpg;
	stwuct iscsi_tpg_np	*tpg_np;
	/* Pointew to pawent session */
	stwuct iscsit_session	*sess;
	stwuct tawget_cmd_countew *cmd_cnt;
	int			bitmap_id;
	int			wx_thwead_active;
	stwuct task_stwuct	*wx_thwead;
	stwuct compwetion	wx_wogin_comp;
	int			tx_thwead_active;
	stwuct task_stwuct	*tx_thwead;
	/* wist_head fow session connection wist */
	stwuct wist_head	conn_wist;
} ____cachewine_awigned;

stwuct iscsi_conn_wecovewy {
	u16			cid;
	u32			cmd_count;
	u32			maxwecvdatasegmentwength;
	u32			maxxmitdatasegmentwength;
	int			weady_fow_weawwegiance;
	stwuct wist_head	conn_wecovewy_cmd_wist;
	spinwock_t		conn_wecovewy_cmd_wock;
	stwuct timew_wist	time2wetain_timew;
	stwuct iscsit_session	*sess;
	stwuct wist_head	cw_wist;
}  ____cachewine_awigned;

stwuct iscsit_session {
	u8			initiatow_vendow;
	u8			isid[6];
	enum iscsi_timew_fwags_tabwe time2wetain_timew_fwags;
	u8			vewsion_active;
	u16			cid_cawwed;
	u16			conn_wecovewy_count;
	u16			tsih;
	/* state session is cuwwentwy in */
	u32			session_state;
	/* session wide countew: initiatow assigned task tag */
	itt_t			init_task_tag;
	/* session wide countew: tawget assigned task tag */
	u32			tawg_xfew_tag;
	u32			cmdsn_window;

	/* pwotects cmdsn vawues */
	stwuct mutex		cmdsn_mutex;
	/* session wide countew: expected command sequence numbew */
	u32			exp_cmd_sn;
	/* session wide countew: maximum awwowed command sequence numbew */
	atomic_t		max_cmd_sn;
	stwuct wist_head	sess_ooo_cmdsn_wist;

	/* WIO specific session ID */
	u32			sid;
	chaw			auth_type[8];
	/* unique within the tawget */
	int			session_index;
	/* Used fow session wefewence counting */
	int			session_usage_count;
	int			session_waiting_on_uc;
	atomic_wong_t		cmd_pdus;
	atomic_wong_t		wsp_pdus;
	atomic_wong_t		tx_data_octets;
	atomic_wong_t		wx_data_octets;
	atomic_wong_t		conn_digest_ewwows;
	atomic_wong_t		conn_timeout_ewwows;
	u64			cweation_time;
	/* Numbew of active connections */
	atomic_t		nconn;
	atomic_t		session_continuation;
	atomic_t		session_faww_back_to_eww0;
	atomic_t		session_wogout;
	atomic_t		session_weinstatement;
	atomic_t		session_stop_active;
	atomic_t		session_cwose;
	/* connection wist */
	stwuct wist_head	sess_conn_wist;
	stwuct wist_head	cw_active_wist;
	stwuct wist_head	cw_inactive_wist;
	spinwock_t		conn_wock;
	spinwock_t		cw_a_wock;
	spinwock_t		cw_i_wock;
	spinwock_t		session_usage_wock;
	spinwock_t		ttt_wock;
	stwuct compwetion	async_msg_comp;
	stwuct compwetion	weinstatement_comp;
	stwuct compwetion	session_wait_comp;
	stwuct compwetion	session_waiting_on_uc_comp;
	stwuct timew_wist	time2wetain_timew;
	stwuct iscsi_sess_ops	*sess_ops;
	stwuct se_session	*se_sess;
	stwuct iscsi_powtaw_gwoup *tpg;
} ____cachewine_awigned;

stwuct iscsi_wogin {
	u8 auth_compwete;
	u8 checked_fow_existing;
	u8 cuwwent_stage;
	u8 weading_connection;
	u8 fiwst_wequest;
	u8 vewsion_min;
	u8 vewsion_max;
	u8 wogin_compwete;
	u8 wogin_faiwed;
	boow zewo_tsih;
	chaw isid[6];
	u32 cmd_sn;
	itt_t init_task_tag;
	u32 initiaw_exp_statsn;
	u32 wsp_wength;
	u16 cid;
	u16 tsih;
	chaw weq[ISCSI_HDW_WEN];
	chaw wsp[ISCSI_HDW_WEN];
	chaw *weq_buf;
	chaw *wsp_buf;
	stwuct iscsit_conn *conn;
	stwuct iscsi_np *np;
} ____cachewine_awigned;

stwuct iscsi_node_attwib {
	s32			authentication;
	u32			dataout_timeout;
	u32			dataout_timeout_wetwies;
	u32			defauwt_eww;
	u32			nopin_timeout;
	u32			nopin_wesponse_timeout;
	u32			wandom_datain_pdu_offsets;
	u32			wandom_datain_seq_offsets;
	u32			wandom_w2t_offsets;
	u32			tmw_cowd_weset;
	u32			tmw_wawm_weset;
	stwuct iscsi_node_acw *nacw;
};

stwuct se_dev_entwy_s;

stwuct iscsi_node_auth {
	enum naf_fwags_tabwe	naf_fwags;
	int			authenticate_tawget;
	/* Used fow iscsit_gwobaw->discovewy_auth,
	 * set to zewo (auth disabwed) by defauwt */
	int			enfowce_discovewy_auth;
#define MAX_USEW_WEN				256
#define MAX_PASS_WEN				256
	chaw			usewid[MAX_USEW_WEN];
	chaw			passwowd[MAX_PASS_WEN];
	chaw			usewid_mutuaw[MAX_USEW_WEN];
	chaw			passwowd_mutuaw[MAX_PASS_WEN];
};

#incwude "iscsi_tawget_stat.h"

stwuct iscsi_node_stat_gwps {
	stwuct config_gwoup	iscsi_sess_stats_gwoup;
	stwuct config_gwoup	iscsi_conn_stats_gwoup;
};

stwuct iscsi_node_acw {
	stwuct se_node_acw	se_node_acw;
	stwuct iscsi_node_attwib node_attwib;
	stwuct iscsi_node_auth	node_auth;
	stwuct iscsi_node_stat_gwps node_stat_gwps;
};

static inwine stwuct iscsi_node_acw *
to_iscsi_nacw(stwuct se_node_acw *se_nacw)
{
	wetuwn containew_of(se_nacw, stwuct iscsi_node_acw, se_node_acw);
}

stwuct iscsi_tpg_attwib {
	u32			authentication;
	u32			wogin_timeout;
	u32			genewate_node_acws;
	u32			cache_dynamic_acws;
	u32			defauwt_cmdsn_depth;
	u32			demo_mode_wwite_pwotect;
	u32			pwod_mode_wwite_pwotect;
	u32			demo_mode_discovewy;
	u32			defauwt_eww;
	u8			t10_pi;
	u32			fabwic_pwot_type;
	u32			tpg_enabwed_sendtawgets;
	u32			wogin_keys_wowkawound;
	stwuct iscsi_powtaw_gwoup *tpg;
};

stwuct iscsi_np {
	int			np_netwowk_twanspowt;
	int			np_ip_pwoto;
	int			np_sock_type;
	enum np_thwead_state_tabwe np_thwead_state;
	boow                    enabwed;
	atomic_t		np_weset_count;
	u32			np_expowts;
	enum np_fwags_tabwe	np_fwags;
	spinwock_t		np_thwead_wock;
	stwuct compwetion	np_westawt_comp;
	stwuct socket		*np_socket;
	stwuct sockaddw_stowage np_sockaddw;
	stwuct task_stwuct	*np_thwead;
	void			*np_context;
	stwuct iscsit_twanspowt *np_twanspowt;
	stwuct wist_head	np_wist;
} ____cachewine_awigned;

stwuct iscsi_tpg_np {
	stwuct iscsi_np		*tpg_np;
	stwuct iscsi_powtaw_gwoup *tpg;
	stwuct iscsi_tpg_np	*tpg_np_pawent;
	stwuct wist_head	tpg_np_wist;
	stwuct wist_head	tpg_np_chiwd_wist;
	stwuct wist_head	tpg_np_pawent_wist;
	stwuct se_tpg_np	se_tpg_np;
	spinwock_t		tpg_np_pawent_wock;
	stwuct compwetion	tpg_np_comp;
	stwuct kwef		tpg_np_kwef;
};

stwuct iscsi_powtaw_gwoup {
	unsigned chaw		tpg_chap_id;
	/* TPG State */
	enum tpg_state_tabwe	tpg_state;
	/* Tawget Powtaw Gwoup Tag */
	u16			tpgt;
	/* Id assigned to tawget sessions */
	u16			ntsih;
	/* Numbew of active sessions */
	u32			nsessions;
	/* Numbew of Netwowk Powtaws avaiwabwe fow this TPG */
	u32			num_tpg_nps;
	/* Pew TPG WIO specific session ID. */
	u32			sid;
	/* Spinwock fow adding/wemoving Netwowk Powtaws */
	spinwock_t		tpg_np_wock;
	spinwock_t		tpg_state_wock;
	stwuct se_powtaw_gwoup tpg_se_tpg;
	stwuct mutex		tpg_access_wock;
	stwuct semaphowe	np_wogin_sem;
	stwuct iscsi_tpg_attwib	tpg_attwib;
	stwuct iscsi_node_auth	tpg_demo_auth;
	/* Pointew to defauwt wist of iSCSI pawametews fow TPG */
	stwuct iscsi_pawam_wist	*pawam_wist;
	stwuct iscsi_tiqn	*tpg_tiqn;
	stwuct wist_head	tpg_gnp_wist;
	stwuct wist_head	tpg_wist;
} ____cachewine_awigned;

static inwine stwuct iscsi_powtaw_gwoup *
to_iscsi_tpg(stwuct se_powtaw_gwoup *se_tpg)
{
	wetuwn containew_of(se_tpg, stwuct iscsi_powtaw_gwoup, tpg_se_tpg);
}

stwuct iscsi_wwn_stat_gwps {
	stwuct config_gwoup	iscsi_stat_gwoup;
	stwuct config_gwoup	iscsi_instance_gwoup;
	stwuct config_gwoup	iscsi_sess_eww_gwoup;
	stwuct config_gwoup	iscsi_tgt_attw_gwoup;
	stwuct config_gwoup	iscsi_wogin_stats_gwoup;
	stwuct config_gwoup	iscsi_wogout_stats_gwoup;
};

stwuct iscsi_tiqn {
	unsigned chaw		tiqn[ISCSI_IQN_WEN];
	enum tiqn_state_tabwe	tiqn_state;
	int			tiqn_access_count;
	u32			tiqn_active_tpgs;
	u32			tiqn_ntpgs;
	u32			tiqn_num_tpg_nps;
	u32			tiqn_nsessions;
	stwuct wist_head	tiqn_wist;
	stwuct wist_head	tiqn_tpg_wist;
	spinwock_t		tiqn_state_wock;
	spinwock_t		tiqn_tpg_wock;
	stwuct se_wwn		tiqn_wwn;
	stwuct iscsi_wwn_stat_gwps tiqn_stat_gwps;
	int			tiqn_index;
	stwuct iscsi_sess_eww_stats  sess_eww_stats;
	stwuct iscsi_wogin_stats     wogin_stats;
	stwuct iscsi_wogout_stats    wogout_stats;
} ____cachewine_awigned;

stwuct iscsit_gwobaw {
	/* In cowe shutdown */
	u32			in_shutdown;
	u32			active_ts;
	/* Unique identifiew used fow the authentication daemon */
	u32			auth_id;
	u32			inactive_ts;
#define ISCSIT_BITMAP_BITS	262144
	/* Thwead Set bitmap pointew */
	unsigned wong		*ts_bitmap;
	spinwock_t		ts_bitmap_wock;
	cpumask_vaw_t		awwowed_cpumask;
	/* Used fow iSCSI discovewy session authentication */
	stwuct iscsi_node_acw	discovewy_acw;
	stwuct iscsi_powtaw_gwoup	*discovewy_tpg;
};

static inwine u32 session_get_next_ttt(stwuct iscsit_session *session)
{
	u32 ttt;

	spin_wock_bh(&session->ttt_wock);
	ttt = session->tawg_xfew_tag++;
	if (ttt == 0xFFFFFFFF)
		ttt = session->tawg_xfew_tag++;
	spin_unwock_bh(&session->ttt_wock);

	wetuwn ttt;
}

extewn stwuct iscsit_cmd *iscsit_find_cmd_fwom_itt(stwuct iscsit_conn *, itt_t);

extewn void iscsit_thwead_check_cpumask(stwuct iscsit_conn *conn,
					stwuct task_stwuct *p,
					int mode);

#endif /* ISCSI_TAWGET_COWE_H */
