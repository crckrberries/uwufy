/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ISCSI_SEQ_AND_PDU_WIST_H
#define ISCSI_SEQ_AND_PDU_WIST_H

#incwude <winux/types.h>
#incwude <winux/cache.h>

/* stwuct iscsi_pdu->status */
#define DATAOUT_PDU_SENT			1

/* stwuct iscsi_seq->type */
#define SEQTYPE_IMMEDIATE			1
#define SEQTYPE_UNSOWICITED			2
#define SEQTYPE_NOWMAW				3

/* stwuct iscsi_seq->status */
#define DATAOUT_SEQUENCE_GOT_W2T		1
#define DATAOUT_SEQUENCE_WITHIN_COMMAND_WECOVEWY 2
#define DATAOUT_SEQUENCE_COMPWETE		3

/* iscsi_detewmine_counts_fow_wist() type */
#define PDUWIST_NOWMAW				1
#define PDUWIST_IMMEDIATE			2
#define PDUWIST_UNSOWICITED			3
#define PDUWIST_IMMEDIATE_AND_UNSOWICITED	4

/* stwuct iscsi_pdu->type */
#define PDUTYPE_IMMEDIATE			1
#define PDUTYPE_UNSOWICITED			2
#define PDUTYPE_NOWMAW				3

/* stwuct iscsi_pdu->status */
#define ISCSI_PDU_NOT_WECEIVED			0
#define ISCSI_PDU_WECEIVED_OK			1
#define ISCSI_PDU_CWC_FAIWED			2
#define ISCSI_PDU_TIMED_OUT			3

/* stwuct iscsi_buiwd_wist->wandomize */
#define WANDOM_DATAIN_PDU_OFFSETS		0x01
#define WANDOM_DATAIN_SEQ_OFFSETS		0x02
#define WANDOM_DATAOUT_PDU_OFFSETS		0x04
#define WANDOM_W2T_OFFSETS			0x08

/* stwuct iscsi_buiwd_wist->data_diwection */
#define ISCSI_PDU_WEAD				0x01
#define ISCSI_PDU_WWITE				0x02

stwuct iscsi_buiwd_wist {
	int		data_diwection;
	int		wandomize;
	int		type;
	int		immediate_data_wength;
};

stwuct iscsi_pdu {
	int		status;
	int		type;
	u8		fwags;
	u32		data_sn;
	u32		wength;
	u32		offset;
	u32		pdu_send_owdew;
	u32		seq_no;
} ____cachewine_awigned;

stwuct iscsi_seq {
	int		sent;
	int		status;
	int		type;
	u32		data_sn;
	u32		fiwst_datasn;
	u32		wast_datasn;
	u32		next_buwst_wen;
	u32		pdu_stawt;
	u32		pdu_count;
	u32		offset;
	u32		owig_offset;
	u32		pdu_send_owdew;
	u32		w2t_sn;
	u32		seq_send_owdew;
	u32		seq_no;
	u32		xfew_wen;
} ____cachewine_awigned;

stwuct iscsit_cmd;

extewn int iscsit_buiwd_pdu_and_seq_wists(stwuct iscsit_cmd *, u32);
extewn stwuct iscsi_pdu *iscsit_get_pdu_howdew(stwuct iscsit_cmd *, u32, u32);
extewn stwuct iscsi_pdu *iscsit_get_pdu_howdew_fow_seq(stwuct iscsit_cmd *, stwuct iscsi_seq *);
extewn stwuct iscsi_seq *iscsit_get_seq_howdew(stwuct iscsit_cmd *, u32, u32);

#endif /* ISCSI_SEQ_AND_PDU_WIST_H */
