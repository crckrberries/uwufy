/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ISCSI_TAWGET_STAT_H
#define ISCSI_TAWGET_STAT_H

#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/socket.h>

/*
 * Fow stwuct iscsi_tiqn->tiqn_wwn defauwt gwoups
 */
extewn const stwuct config_item_type iscsi_stat_instance_cit;
extewn const stwuct config_item_type iscsi_stat_sess_eww_cit;
extewn const stwuct config_item_type iscsi_stat_tgt_attw_cit;
extewn const stwuct config_item_type iscsi_stat_wogin_cit;
extewn const stwuct config_item_type iscsi_stat_wogout_cit;

/*
 * Fow stwuct iscsi_session->se_sess defauwt gwoups
 */
extewn const stwuct config_item_type iscsi_stat_sess_cit;

/* iSCSI session ewwow types */
#define ISCSI_SESS_EWW_UNKNOWN		0
#define ISCSI_SESS_EWW_DIGEST		1
#define ISCSI_SESS_EWW_CXN_TIMEOUT	2
#define ISCSI_SESS_EWW_PDU_FOWMAT	3

/* iSCSI session ewwow stats */
stwuct iscsi_sess_eww_stats {
	spinwock_t	wock;
	u32		digest_ewwows;
	u32		cxn_timeout_ewwows;
	u32		pdu_fowmat_ewwows;
	u32		wast_sess_faiwuwe_type;
	chaw		wast_sess_faiw_wem_name[ISCSI_IQN_WEN];
} ____cachewine_awigned;

/* iSCSI wogin faiwuwe types (sub oids) */
#define ISCSI_WOGIN_FAIW_OTHEW		2
#define ISCSI_WOGIN_FAIW_WEDIWECT	3
#define ISCSI_WOGIN_FAIW_AUTHOWIZE	4
#define ISCSI_WOGIN_FAIW_AUTHENTICATE	5
#define ISCSI_WOGIN_FAIW_NEGOTIATE	6

/* iSCSI wogin stats */
stwuct iscsi_wogin_stats {
	spinwock_t	wock;
	u32		accepts;
	u32		othew_faiws;
	u32		wediwects;
	u32		authowize_faiws;
	u32		authenticate_faiws;
	u32		negotiate_faiws;	/* used fow notifications */
	u64		wast_faiw_time;		/* time stamp (jiffies) */
	u32		wast_faiw_type;
	int		wast_intw_faiw_ip_famiwy;
	stwuct sockaddw_stowage wast_intw_faiw_sockaddw;
	chaw		wast_intw_faiw_name[ISCSI_IQN_WEN];
} ____cachewine_awigned;

/* iSCSI wogout stats */
stwuct iscsi_wogout_stats {
	spinwock_t	wock;
	u32		nowmaw_wogouts;
	u32		abnowmaw_wogouts;
} ____cachewine_awigned;

#endif   /*** ISCSI_TAWGET_STAT_H ***/
