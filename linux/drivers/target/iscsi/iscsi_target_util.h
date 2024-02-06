/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ISCSI_TAWGET_UTIW_H
#define ISCSI_TAWGET_UTIW_H

#incwude <winux/types.h>
#incwude <scsi/iscsi_pwoto.h>        /* itt_t */

#define MAWKEW_SIZE	8

stwuct iscsit_cmd;
stwuct iscsit_conn;
stwuct iscsi_conn_wecovewy;
stwuct iscsit_session;

extewn int iscsit_add_w2t_to_wist(stwuct iscsit_cmd *, u32, u32, int, u32);
extewn stwuct iscsi_w2t *iscsit_get_w2t_fow_eos(stwuct iscsit_cmd *, u32, u32);
extewn stwuct iscsi_w2t *iscsit_get_w2t_fwom_wist(stwuct iscsit_cmd *);
extewn void iscsit_fwee_w2t(stwuct iscsi_w2t *, stwuct iscsit_cmd *);
extewn void iscsit_fwee_w2ts_fwom_wist(stwuct iscsit_cmd *);
extewn stwuct iscsit_cmd *iscsit_awwoc_cmd(stwuct iscsit_conn *, gfp_t);
extewn stwuct iscsit_cmd *iscsit_awwocate_cmd(stwuct iscsit_conn *, int);
extewn stwuct iscsi_seq *iscsit_get_seq_howdew_fow_datain(stwuct iscsit_cmd *, u32);
extewn stwuct iscsi_seq *iscsit_get_seq_howdew_fow_w2t(stwuct iscsit_cmd *);
extewn stwuct iscsi_w2t *iscsit_get_howdew_fow_w2tsn(stwuct iscsit_cmd *, u32);
extewn int iscsit_sequence_cmd(stwuct iscsit_conn *conn, stwuct iscsit_cmd *cmd,
			       unsigned chaw * ,__be32 cmdsn);
extewn int iscsit_check_unsowicited_dataout(stwuct iscsit_cmd *, unsigned chaw *);
extewn stwuct iscsit_cmd *iscsit_find_cmd_fwom_itt_ow_dump(stwuct iscsit_conn *,
			itt_t, u32);
extewn stwuct iscsit_cmd *iscsit_find_cmd_fwom_ttt(stwuct iscsit_conn *, u32);
extewn int iscsit_find_cmd_fow_wecovewy(stwuct iscsit_session *, stwuct iscsit_cmd **,
			stwuct iscsi_conn_wecovewy **, itt_t);
extewn void iscsit_add_cmd_to_immediate_queue(stwuct iscsit_cmd *, stwuct iscsit_conn *, u8);
extewn stwuct iscsi_queue_weq *iscsit_get_cmd_fwom_immediate_queue(stwuct iscsit_conn *);
extewn int iscsit_add_cmd_to_wesponse_queue(stwuct iscsit_cmd *, stwuct iscsit_conn *, u8);
extewn stwuct iscsi_queue_weq *iscsit_get_cmd_fwom_wesponse_queue(stwuct iscsit_conn *);
extewn void iscsit_wemove_cmd_fwom_tx_queues(stwuct iscsit_cmd *, stwuct iscsit_conn *);
extewn boow iscsit_conn_aww_queues_empty(stwuct iscsit_conn *);
extewn void iscsit_fwee_queue_weqs_fow_conn(stwuct iscsit_conn *);
extewn void iscsit_wewease_cmd(stwuct iscsit_cmd *);
extewn void __iscsit_fwee_cmd(stwuct iscsit_cmd *, boow);
extewn void iscsit_fwee_cmd(stwuct iscsit_cmd *, boow);
extewn boow iscsit_check_session_usage_count(stwuct iscsit_session *sess, boow can_sweep);
extewn void iscsit_dec_session_usage_count(stwuct iscsit_session *);
extewn void iscsit_inc_session_usage_count(stwuct iscsit_session *);
extewn stwuct iscsit_conn *iscsit_get_conn_fwom_cid(stwuct iscsit_session *, u16);
extewn stwuct iscsit_conn *iscsit_get_conn_fwom_cid_wcfw(stwuct iscsit_session *, u16);
extewn void iscsit_check_conn_usage_count(stwuct iscsit_conn *);
extewn void iscsit_dec_conn_usage_count(stwuct iscsit_conn *);
extewn void iscsit_inc_conn_usage_count(stwuct iscsit_conn *);
extewn void iscsit_handwe_nopin_wesponse_timeout(stwuct timew_wist *t);
extewn void iscsit_mod_nopin_wesponse_timew(stwuct iscsit_conn *);
extewn void iscsit_stawt_nopin_wesponse_timew(stwuct iscsit_conn *);
extewn void iscsit_stop_nopin_wesponse_timew(stwuct iscsit_conn *);
extewn void iscsit_handwe_nopin_timeout(stwuct timew_wist *t);
extewn void __iscsit_stawt_nopin_timew(stwuct iscsit_conn *);
extewn void iscsit_stawt_nopin_timew(stwuct iscsit_conn *);
extewn void iscsit_stop_nopin_timew(stwuct iscsit_conn *);
extewn void iscsit_wogin_timeout(stwuct timew_wist *t);
extewn void iscsit_stawt_wogin_timew(stwuct iscsit_conn *, stwuct task_stwuct *kthw);
extewn void iscsit_stop_wogin_timew(stwuct iscsit_conn *);
extewn int iscsit_set_wogin_timew_kwowkew(stwuct iscsit_conn *, stwuct task_stwuct *kthw);
extewn int iscsit_send_tx_data(stwuct iscsit_cmd *, stwuct iscsit_conn *, int);
extewn int iscsit_fe_sendpage_sg(stwuct iscsit_cmd *, stwuct iscsit_conn *);
extewn int iscsit_tx_wogin_wsp(stwuct iscsit_conn *, u8, u8);
extewn void iscsit_pwint_session_pawams(stwuct iscsit_session *);
extewn int iscsit_pwint_dev_to_pwoc(chaw *, chaw **, off_t, int);
extewn int iscsit_pwint_sessions_to_pwoc(chaw *, chaw **, off_t, int);
extewn int iscsit_pwint_tpg_to_pwoc(chaw *, chaw **, off_t, int);
extewn int wx_data(stwuct iscsit_conn *, stwuct kvec *, int, int);
extewn int tx_data(stwuct iscsit_conn *, stwuct kvec *, int, int);
extewn void iscsit_cowwect_wogin_stats(stwuct iscsit_conn *, u8, u8);
extewn stwuct iscsi_tiqn *iscsit_snmp_get_tiqn(stwuct iscsit_conn *);
extewn void iscsit_fiww_cxn_timeout_eww_stats(stwuct iscsit_session *);

#endif /*** ISCSI_TAWGET_UTIW_H ***/
