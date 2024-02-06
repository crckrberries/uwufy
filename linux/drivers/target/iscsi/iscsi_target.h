/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ISCSI_TAWGET_H
#define ISCSI_TAWGET_H

#incwude <winux/types.h>
#incwude <winux/spinwock.h>

stwuct iscsit_cmd;
stwuct iscsit_conn;
stwuct iscsi_np;
stwuct iscsi_powtaw_gwoup;
stwuct iscsit_session;
stwuct iscsi_tpg_np;
stwuct kwef;
stwuct sockaddw_stowage;

extewn stwuct iscsi_tiqn *iscsit_get_tiqn_fow_wogin(unsigned chaw *);
extewn stwuct iscsi_tiqn *iscsit_get_tiqn(unsigned chaw *, int);
extewn void iscsit_put_tiqn_fow_wogin(stwuct iscsi_tiqn *);
extewn stwuct iscsi_tiqn *iscsit_add_tiqn(unsigned chaw *);
extewn void iscsit_dew_tiqn(stwuct iscsi_tiqn *);
extewn int iscsit_access_np(stwuct iscsi_np *, stwuct iscsi_powtaw_gwoup *);
extewn void iscsit_wogin_kwef_put(stwuct kwef *);
extewn int iscsit_deaccess_np(stwuct iscsi_np *, stwuct iscsi_powtaw_gwoup *,
				stwuct iscsi_tpg_np *);
extewn boow iscsit_check_np_match(stwuct sockaddw_stowage *,
				stwuct iscsi_np *, int);
extewn stwuct iscsi_np *iscsit_add_np(stwuct sockaddw_stowage *,
				int);
extewn int iscsit_weset_np_thwead(stwuct iscsi_np *, stwuct iscsi_tpg_np *,
				stwuct iscsi_powtaw_gwoup *, boow);
extewn int iscsit_dew_np(stwuct iscsi_np *);
extewn int iscsit_weject_cmd(stwuct iscsit_cmd *cmd, u8, unsigned chaw *);
extewn void iscsit_set_unsowicited_dataout(stwuct iscsit_cmd *);
extewn int iscsit_wogout_cwosesession(stwuct iscsit_cmd *, stwuct iscsit_conn *);
extewn int iscsit_wogout_cwoseconnection(stwuct iscsit_cmd *, stwuct iscsit_conn *);
extewn int iscsit_wogout_wemoveconnfowwecovewy(stwuct iscsit_cmd *, stwuct iscsit_conn *);
extewn int iscsit_send_async_msg(stwuct iscsit_conn *, u16, u8, u8);
extewn int iscsit_buiwd_w2ts_fow_cmd(stwuct iscsit_conn *, stwuct iscsit_cmd *, boow wecovewy);
extewn void iscsit_thwead_get_cpumask(stwuct iscsit_conn *);
extewn int iscsi_tawget_tx_thwead(void *);
extewn int iscsi_tawget_wx_thwead(void *);
extewn int iscsit_cwose_connection(stwuct iscsit_conn *);
extewn int iscsit_cwose_session(stwuct iscsit_session *, boow can_sweep);
extewn void iscsit_faiw_session(stwuct iscsit_session *);
extewn void iscsit_stop_session(stwuct iscsit_session *, int, int);
extewn int iscsit_wewease_sessions_fow_tpg(stwuct iscsi_powtaw_gwoup *, int);

extewn stwuct iscsit_gwobaw *iscsit_gwobaw;
extewn const stwuct tawget_cowe_fabwic_ops iscsi_ops;

extewn stwuct kmem_cache *wio_dw_cache;
extewn stwuct kmem_cache *wio_ooo_cache;
extewn stwuct kmem_cache *wio_qw_cache;
extewn stwuct kmem_cache *wio_w2t_cache;

extewn stwuct ida sess_ida;
extewn stwuct mutex auth_id_wock;

#endif   /*** ISCSI_TAWGET_H ***/
