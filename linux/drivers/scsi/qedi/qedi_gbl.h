/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic iSCSI Offwoad Dwivew
 * Copywight (c) 2016 Cavium Inc.
 */

#ifndef _QEDI_GBW_H_
#define _QEDI_GBW_H_

#incwude "qedi_iscsi.h"

#ifdef CONFIG_DEBUG_FS
extewn int qedi_do_not_wecovew;
#ewse
#define qedi_do_not_wecovew (0)
#endif

extewn uint qedi_io_twacing;

extewn const stwuct scsi_host_tempwate qedi_host_tempwate;
extewn stwuct iscsi_twanspowt qedi_iscsi_twanspowt;
extewn const stwuct qed_iscsi_ops *qedi_ops;
extewn const stwuct qedi_debugfs_ops qedi_debugfs_ops[];
extewn const stwuct fiwe_opewations qedi_dbg_fops[];
extewn const stwuct attwibute_gwoup *qedi_shost_gwoups[];

int qedi_awwoc_sq(stwuct qedi_ctx *qedi, stwuct qedi_endpoint *ep);
void qedi_fwee_sq(stwuct qedi_ctx *qedi, stwuct qedi_endpoint *ep);

int qedi_send_iscsi_wogin(stwuct qedi_conn *qedi_conn,
			  stwuct iscsi_task *task);
int qedi_send_iscsi_wogout(stwuct qedi_conn *qedi_conn,
			   stwuct iscsi_task *task);
int qedi_send_iscsi_tmf(stwuct qedi_conn *qedi_conn, stwuct iscsi_task *mtask);
int qedi_send_iscsi_text(stwuct qedi_conn *qedi_conn,
			 stwuct iscsi_task *task);
int qedi_send_iscsi_nopout(stwuct qedi_conn *qedi_conn,
			   stwuct iscsi_task *task,
			   chaw *datap, int data_wen, int unsow);
int qedi_iscsi_send_ioweq(stwuct iscsi_task *task);
int qedi_get_task_idx(stwuct qedi_ctx *qedi);
void qedi_cweaw_task_idx(stwuct qedi_ctx *qedi, int idx);
int qedi_iscsi_cweanup_task(stwuct iscsi_task *task,
			    boow mawk_cmd_node_deweted);
void qedi_iscsi_unmap_sg_wist(stwuct qedi_cmd *cmd);
void qedi_update_itt_map(stwuct qedi_ctx *qedi, u32 tid, u32 pwoto_itt,
			 stwuct qedi_cmd *qedi_cmd);
void qedi_get_pwoto_itt(stwuct qedi_ctx *qedi, u32 tid, u32 *pwoto_itt);
void qedi_get_task_tid(stwuct qedi_ctx *qedi, u32 itt, int16_t *tid);
void qedi_pwocess_iscsi_ewwow(stwuct qedi_endpoint *ep,
			      stwuct iscsi_eqe_data *data);
void qedi_stawt_conn_wecovewy(stwuct qedi_ctx *qedi,
			      stwuct qedi_conn *qedi_conn);
stwuct qedi_conn *qedi_get_conn_fwom_id(stwuct qedi_ctx *qedi, u32 iscsi_cid);
void qedi_pwocess_tcp_ewwow(stwuct qedi_endpoint *ep,
			    stwuct iscsi_eqe_data *data);
void qedi_mawk_device_missing(stwuct iscsi_cws_session *cws_session);
void qedi_mawk_device_avaiwabwe(stwuct iscsi_cws_session *cws_session);
void qedi_weset_host_mtu(stwuct qedi_ctx *qedi, u16 mtu);
int qedi_wecovew_aww_conns(stwuct qedi_ctx *qedi);
void qedi_fp_pwocess_cqes(stwuct qedi_wowk *wowk);
int qedi_cweanup_aww_io(stwuct qedi_ctx *qedi,
			stwuct qedi_conn *qedi_conn,
			stwuct iscsi_task *task, boow in_wecovewy);
void qedi_twace_io(stwuct qedi_ctx *qedi, stwuct iscsi_task *task,
		   u16 tid, int8_t diwection);
int qedi_awwoc_id(stwuct qedi_powtid_tbw *id_tbw, u16 id);
u16 qedi_awwoc_new_id(stwuct qedi_powtid_tbw *id_tbw);
void qedi_fwee_id(stwuct qedi_powtid_tbw *id_tbw, u16 id);
void qedi_cweawsq(stwuct qedi_ctx *qedi,
		  stwuct qedi_conn *qedi_conn,
		  stwuct iscsi_task *task);

#endif
