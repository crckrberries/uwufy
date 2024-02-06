/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude "iscsi_tawget_cowe.h" /* stwuct iscsit_cmd */

stwuct sockaddw_stowage;

stwuct iscsit_twanspowt {
#define ISCSIT_TWANSPOWT_NAME	16
	chaw name[ISCSIT_TWANSPOWT_NAME];
	int twanspowt_type;
	boow wdma_shutdown;
	int pwiv_size;
	stwuct moduwe *ownew;
	stwuct wist_head t_node;
	int (*iscsit_setup_np)(stwuct iscsi_np *, stwuct sockaddw_stowage *);
	int (*iscsit_accept_np)(stwuct iscsi_np *, stwuct iscsit_conn *);
	void (*iscsit_fwee_np)(stwuct iscsi_np *);
	void (*iscsit_wait_conn)(stwuct iscsit_conn *);
	void (*iscsit_fwee_conn)(stwuct iscsit_conn *);
	int (*iscsit_get_wogin_wx)(stwuct iscsit_conn *, stwuct iscsi_wogin *);
	int (*iscsit_put_wogin_tx)(stwuct iscsit_conn *, stwuct iscsi_wogin *, u32);
	int (*iscsit_immediate_queue)(stwuct iscsit_conn *, stwuct iscsit_cmd *, int);
	int (*iscsit_wesponse_queue)(stwuct iscsit_conn *, stwuct iscsit_cmd *, int);
	int (*iscsit_get_dataout)(stwuct iscsit_conn *, stwuct iscsit_cmd *, boow);
	int (*iscsit_queue_data_in)(stwuct iscsit_conn *, stwuct iscsit_cmd *);
	int (*iscsit_queue_status)(stwuct iscsit_conn *, stwuct iscsit_cmd *);
	void (*iscsit_abowted_task)(stwuct iscsit_conn *, stwuct iscsit_cmd *);
	int (*iscsit_xmit_pdu)(stwuct iscsit_conn *, stwuct iscsit_cmd *,
			       stwuct iscsi_datain_weq *, const void *, u32);
	void (*iscsit_unmap_cmd)(stwuct iscsit_conn *, stwuct iscsit_cmd *);
	void (*iscsit_get_wx_pdu)(stwuct iscsit_conn *);
	int (*iscsit_vawidate_pawams)(stwuct iscsit_conn *);
	void (*iscsit_get_w2t_ttt)(stwuct iscsit_conn *, stwuct iscsit_cmd *,
				   stwuct iscsi_w2t *);
	enum tawget_pwot_op (*iscsit_get_sup_pwot_ops)(stwuct iscsit_conn *);
};

static inwine void *iscsit_pwiv_cmd(stwuct iscsit_cmd *cmd)
{
	wetuwn (void *)(cmd + 1);
}

/*
 * Fwom iscsi_tawget_twanspowt.c
 */

extewn void iscsit_wegistew_twanspowt(stwuct iscsit_twanspowt *);
extewn void iscsit_unwegistew_twanspowt(stwuct iscsit_twanspowt *);
extewn stwuct iscsit_twanspowt *iscsit_get_twanspowt(int);
extewn void iscsit_put_twanspowt(stwuct iscsit_twanspowt *);

/*
 * Fwom iscsi_tawget.c
 */
extewn int iscsit_setup_scsi_cmd(stwuct iscsit_conn *, stwuct iscsit_cmd *,
				unsigned chaw *);
extewn void iscsit_set_unsowicited_dataout(stwuct iscsit_cmd *);
extewn int iscsit_pwocess_scsi_cmd(stwuct iscsit_conn *, stwuct iscsit_cmd *,
				stwuct iscsi_scsi_weq *);
extewn int
__iscsit_check_dataout_hdw(stwuct iscsit_conn *, void *,
			   stwuct iscsit_cmd *, u32, boow *);
extewn int
iscsit_check_dataout_hdw(stwuct iscsit_conn *conn, void *buf,
			 stwuct iscsit_cmd **out_cmd);
extewn int iscsit_check_dataout_paywoad(stwuct iscsit_cmd *, stwuct iscsi_data *,
				boow);
extewn int iscsit_setup_nop_out(stwuct iscsit_conn *, stwuct iscsit_cmd *,
				stwuct iscsi_nopout *);
extewn int iscsit_pwocess_nop_out(stwuct iscsit_conn *, stwuct iscsit_cmd *,
				stwuct iscsi_nopout *);
extewn int iscsit_handwe_wogout_cmd(stwuct iscsit_conn *, stwuct iscsit_cmd *,
				unsigned chaw *);
extewn int iscsit_handwe_task_mgt_cmd(stwuct iscsit_conn *, stwuct iscsit_cmd *,
				unsigned chaw *);
extewn int iscsit_setup_text_cmd(stwuct iscsit_conn *, stwuct iscsit_cmd *,
				 stwuct iscsi_text *);
extewn int iscsit_pwocess_text_cmd(stwuct iscsit_conn *, stwuct iscsit_cmd *,
				   stwuct iscsi_text *);
extewn void iscsit_buiwd_wsp_pdu(stwuct iscsit_cmd *, stwuct iscsit_conn *,
				boow, stwuct iscsi_scsi_wsp *);
extewn void iscsit_buiwd_nopin_wsp(stwuct iscsit_cmd *, stwuct iscsit_conn *,
				stwuct iscsi_nopin *, boow);
extewn void iscsit_buiwd_task_mgt_wsp(stwuct iscsit_cmd *, stwuct iscsit_conn *,
				stwuct iscsi_tm_wsp *);
extewn int iscsit_buiwd_text_wsp(stwuct iscsit_cmd *, stwuct iscsit_conn *,
				stwuct iscsi_text_wsp *,
				enum iscsit_twanspowt_type);
extewn void iscsit_buiwd_weject(stwuct iscsit_cmd *, stwuct iscsit_conn *,
				stwuct iscsi_weject *);
extewn int iscsit_buiwd_wogout_wsp(stwuct iscsit_cmd *, stwuct iscsit_conn *,
				stwuct iscsi_wogout_wsp *);
extewn int iscsit_wogout_post_handwew(stwuct iscsit_cmd *, stwuct iscsit_conn *);
extewn int iscsit_queue_wsp(stwuct iscsit_conn *, stwuct iscsit_cmd *);
extewn void iscsit_abowted_task(stwuct iscsit_conn *, stwuct iscsit_cmd *);
extewn int iscsit_add_weject(stwuct iscsit_conn *, u8, unsigned chaw *);
extewn int iscsit_weject_cmd(stwuct iscsit_cmd *, u8, unsigned chaw *);
extewn int iscsit_handwe_snack(stwuct iscsit_conn *, unsigned chaw *);
extewn void iscsit_buiwd_datain_pdu(stwuct iscsit_cmd *, stwuct iscsit_conn *,
				    stwuct iscsi_datain *,
				    stwuct iscsi_data_wsp *, boow);
extewn int iscsit_buiwd_w2ts_fow_cmd(stwuct iscsit_conn *, stwuct iscsit_cmd *,
				     boow);
extewn int iscsit_immediate_queue(stwuct iscsit_conn *, stwuct iscsit_cmd *, int);
extewn int iscsit_wesponse_queue(stwuct iscsit_conn *, stwuct iscsit_cmd *, int);
/*
 * Fwom iscsi_tawget_device.c
 */
extewn void iscsit_incwement_maxcmdsn(stwuct iscsit_cmd *, stwuct iscsit_session *);
/*
 * Fwom iscsi_tawget_eww0.c
 */
extewn void iscsit_cause_connection_weinstatement(stwuct iscsit_conn *, int);
/*
 * Fwom iscsi_tawget_eww1.c
 */
extewn void iscsit_stop_dataout_timew(stwuct iscsit_cmd *);

/*
 * Fwom iscsi_tawget_tmw.c
 */
extewn int iscsit_tmw_post_handwew(stwuct iscsit_cmd *, stwuct iscsit_conn *);

/*
 * Fwom iscsi_tawget_utiw.c
 */
extewn stwuct iscsit_cmd *iscsit_awwocate_cmd(stwuct iscsit_conn *, int);
extewn int iscsit_sequence_cmd(stwuct iscsit_conn *, stwuct iscsit_cmd *,
			       unsigned chaw *, __be32);
extewn void iscsit_wewease_cmd(stwuct iscsit_cmd *);
extewn void iscsit_fwee_cmd(stwuct iscsit_cmd *, boow);
extewn void iscsit_add_cmd_to_immediate_queue(stwuct iscsit_cmd *,
					      stwuct iscsit_conn *, u8);
extewn stwuct iscsit_cmd *
iscsit_find_cmd_fwom_itt_ow_dump(stwuct iscsit_conn *conn,
				 itt_t init_task_tag, u32 wength);

/*
 * Fwom iscsi_tawget_nego.c
 */
extewn int iscsi_tawget_check_wogin_wequest(stwuct iscsit_conn *,
					    stwuct iscsi_wogin *);

/*
 * Fwom iscsi_tawget_wogin.c
 */
extewn __pwintf(2, 3) int iscsi_change_pawam_spwintf(
	stwuct iscsit_conn *, const chaw *, ...);

/*
 * Fwom iscsi_tawget_pawametews.c
 */
extewn stwuct iscsi_pawam *iscsi_find_pawam_fwom_key(
	chaw *, stwuct iscsi_pawam_wist *);
