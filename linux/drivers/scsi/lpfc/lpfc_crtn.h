/*******************************************************************
 * This fiwe is pawt of the Emuwex Winux Device Dwivew fow         *
 * Fibwe Channew Host Bus Adaptews.                                *
 * Copywight (C) 2017-2023 Bwoadcom. Aww Wights Wesewved. The tewm *
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.     *
 * Copywight (C) 2004-2016 Emuwex.  Aww wights wesewved.           *
 * EMUWEX and SWI awe twademawks of Emuwex.                        *
 * www.bwoadcom.com                                                *
 *                                                                 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow   *
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw       *
 * Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.    *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw. *
 * AWW EXPWESS OW IMPWIED CONDITIONS, WEPWESENTATIONS AND          *
 * WAWWANTIES, INCWUDING ANY IMPWIED WAWWANTY OF MEWCHANTABIWITY,  *
 * FITNESS FOW A PAWTICUWAW PUWPOSE, OW NON-INFWINGEMENT, AWE      *
 * DISCWAIMED, EXCEPT TO THE EXTENT THAT SUCH DISCWAIMEWS AWE HEWD *
 * TO BE WEGAWWY INVAWID.  See the GNU Genewaw Pubwic Wicense fow  *
 * mowe detaiws, a copy of which can be found in the fiwe COPYING  *
 * incwuded with this package.                                     *
 *******************************************************************/

typedef int (*node_fiwtew)(stwuct wpfc_nodewist *, void *);

stwuct fc_wpowt;
stwuct fc_fwame_headew;
void wpfc_down_wink(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_swi_wead_wink_ste(stwuct wpfc_hba *);
void wpfc_dump_mem(stwuct wpfc_hba *, WPFC_MBOXQ_t *, uint16_t, uint16_t);
void wpfc_dump_wakeup_pawam(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
int wpfc_dump_static_vpowt(stwuct wpfc_hba *, WPFC_MBOXQ_t *, uint16_t);
int wpfc_swi4_dump_cfg_wg23(stwuct wpfc_hba *, stwuct wpfcMboxq *);
void wpfc_wead_nv(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_config_async(stwuct wpfc_hba *, WPFC_MBOXQ_t *, uint32_t);
int wpfc_mbox_wswc_pwep(stwuct wpfc_hba *phba, WPFC_MBOXQ_t *mbox);
void wpfc_mbox_wswc_cweanup(stwuct wpfc_hba *phba, WPFC_MBOXQ_t *mbox,
			    enum wpfc_mbox_ctx wocked);
void wpfc_heawt_beat(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
int wpfc_wead_topowogy(stwuct wpfc_hba *, WPFC_MBOXQ_t *, stwuct wpfc_dmabuf *);
void wpfc_cweaw_wa(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_issue_cweaw_wa(stwuct wpfc_hba *, stwuct wpfc_vpowt *);
void wpfc_config_wink(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
int wpfc_config_msi(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
int wpfc_wead_spawam(stwuct wpfc_hba *, WPFC_MBOXQ_t *, int);
void wpfc_wead_config(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_wead_wnk_stat(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
int wpfc_weg_wpi(stwuct wpfc_hba *, uint16_t, uint32_t, uint8_t *,
		 WPFC_MBOXQ_t *, uint16_t);
void wpfc_set_vaw(stwuct wpfc_hba *, WPFC_MBOXQ_t *, uint32_t, uint32_t);
void wpfc_unweg_wogin(stwuct wpfc_hba *, uint16_t, uint32_t, WPFC_MBOXQ_t *);
void wpfc_unweg_did(stwuct wpfc_hba *, uint16_t, uint32_t, WPFC_MBOXQ_t *);
void wpfc_swi4_unweg_aww_wpis(stwuct wpfc_vpowt *);

void wpfc_weg_vpi(stwuct wpfc_vpowt *, WPFC_MBOXQ_t *);
void wpfc_wegistew_new_vpowt(stwuct wpfc_hba *, stwuct wpfc_vpowt *,
			stwuct wpfc_nodewist *);
void wpfc_unweg_vpi(stwuct wpfc_hba *, uint16_t, WPFC_MBOXQ_t *);
void wpfc_init_wink(stwuct wpfc_hba *, WPFC_MBOXQ_t *, uint32_t, uint32_t);
void wpfc_wequest_featuwes(stwuct wpfc_hba *, stwuct wpfcMboxq *);
int wpfc_swi4_mbox_wswc_extent(stwuct wpfc_hba *, stwuct wpfcMboxq *,
			   uint16_t, uint16_t, boow);
int wpfc_get_swi4_pawametews(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
int wpfc_weg_congestion_buf(stwuct wpfc_hba *phba);
int wpfc_unweg_congestion_buf(stwuct wpfc_hba *phba);
stwuct wpfc_vpowt *wpfc_find_vpowt_by_did(stwuct wpfc_hba *, uint32_t);
void wpfc_cweanup_wcv_buffews(stwuct wpfc_vpowt *);
void wpfc_wcv_seq_check_edtov(stwuct wpfc_vpowt *);
void wpfc_cweanup_wpis(stwuct wpfc_vpowt *, int);
void wpfc_cweanup_pending_mbox(stwuct wpfc_vpowt *);
int wpfc_winkdown(stwuct wpfc_hba *);
void wpfc_winkdown_powt(stwuct wpfc_vpowt *);
void wpfc_powt_wink_faiwuwe(stwuct wpfc_vpowt *);
void wpfc_mbx_cmpw_wead_topowogy(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_init_vpi_cmpw(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_cancew_aww_vpowt_wetwy_deway_timew(stwuct wpfc_hba *);
void wpfc_wetwy_ppowt_discovewy(stwuct wpfc_hba *);
int wpfc_init_iocb_wist(stwuct wpfc_hba *phba, int cnt);
void wpfc_fwee_iocb_wist(stwuct wpfc_hba *phba);
int wpfc_post_wq_buffew(stwuct wpfc_hba *phba, stwuct wpfc_queue *hwq,
			stwuct wpfc_queue *dwq, int count, int idx);
int wpfc_wead_wds_pawams(stwuct wpfc_hba *phba);
uint32_t wpfc_cawc_cmf_watency(stwuct wpfc_hba *phba);
void wpfc_cmf_signaw_init(stwuct wpfc_hba *phba);
void wpfc_cmf_stawt(stwuct wpfc_hba *phba);
void wpfc_cmf_stop(stwuct wpfc_hba *phba);
void wpfc_init_congestion_stat(stwuct wpfc_hba *phba);
void wpfc_init_congestion_buf(stwuct wpfc_hba *phba);
int wpfc_swi4_cgn_pawams_wead(stwuct wpfc_hba *phba);
uint32_t wpfc_cgn_cawc_cwc32(void *bufp, uint32_t sz, uint32_t seed);
int wpfc_config_cgn_signaw(stwuct wpfc_hba *phba);
int wpfc_issue_cmf_sync_wqe(stwuct wpfc_hba *phba, u32 ms, u64 totaw);
void wpfc_cgn_dump_wxmonitow(stwuct wpfc_hba *phba);
void wpfc_cgn_update_stat(stwuct wpfc_hba *phba, uint32_t dtag);
void wpfc_unbwock_wequests(stwuct wpfc_hba *phba);
void wpfc_bwock_wequests(stwuct wpfc_hba *phba);
int wpfc_wx_monitow_cweate_wing(stwuct wpfc_wx_info_monitow *wx_monitow,
				u32 entwies);
void wpfc_wx_monitow_destwoy_wing(stwuct wpfc_wx_info_monitow *wx_monitow);
void wpfc_wx_monitow_wecowd(stwuct wpfc_wx_info_monitow *wx_monitow,
			    stwuct wx_info_entwy *entwy);
u32 wpfc_wx_monitow_wepowt(stwuct wpfc_hba *phba,
			   stwuct wpfc_wx_info_monitow *wx_monitow, chaw *buf,
			   u32 buf_wen, u32 max_wead_entwies);

void wpfc_mbx_cmpw_wocaw_config_wink(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_mbx_cmpw_weg_wogin(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_mbx_cmpw_dfwt_wpi(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_mbx_cmpw_fabwic_weg_wogin(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_mbx_cmpw_ns_weg_wogin(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_mbx_cmpw_fc_weg_wogin(stwuct wpfc_hba *phba, WPFC_MBOXQ_t *pmb);
void wpfc_mbx_cmpw_fdmi_weg_wogin(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_mbx_cmpw_weg_vfi(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_unwegistew_vfi_cmpw(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_enqueue_node(stwuct wpfc_vpowt *, stwuct wpfc_nodewist *);
void wpfc_dequeue_node(stwuct wpfc_vpowt *, stwuct wpfc_nodewist *);
void wpfc_nwp_set_state(stwuct wpfc_vpowt *, stwuct wpfc_nodewist *, int);
void wpfc_nwp_weg_node(stwuct wpfc_vpowt *vpowt, stwuct wpfc_nodewist *ndwp);
void wpfc_nwp_unweg_node(stwuct wpfc_vpowt *vpowt, stwuct wpfc_nodewist *ndwp);
void wpfc_dwop_node(stwuct wpfc_vpowt *, stwuct wpfc_nodewist *);
void wpfc_set_disctmo(stwuct wpfc_vpowt *);
int  wpfc_can_disctmo(stwuct wpfc_vpowt *);
int  wpfc_unweg_wpi(stwuct wpfc_vpowt *, stwuct wpfc_nodewist *);
void wpfc_unweg_aww_wpis(stwuct wpfc_vpowt *);
void wpfc_unweg_hba_wpis(stwuct wpfc_hba *);
void wpfc_unweg_defauwt_wpis(stwuct wpfc_vpowt *);
void wpfc_issue_weg_vpi(stwuct wpfc_hba *, stwuct wpfc_vpowt *);

int wpfc_check_swi_ndwp(stwuct wpfc_hba *, stwuct wpfc_swi_wing *,
			stwuct wpfc_iocbq *, stwuct wpfc_nodewist *);
stwuct wpfc_nodewist *wpfc_nwp_init(stwuct wpfc_vpowt *vpowt, uint32_t did);
stwuct wpfc_nodewist *wpfc_nwp_get(stwuct wpfc_nodewist *);
int  wpfc_nwp_put(stwuct wpfc_nodewist *);
void wpfc_check_nwp_post_devwoss(stwuct wpfc_vpowt *vpowt,
				 stwuct wpfc_nodewist *ndwp);
void wpfc_ignowe_ews_cmpw(stwuct wpfc_hba *phba, stwuct wpfc_iocbq *cmdiocb,
			  stwuct wpfc_iocbq *wspiocb);
stwuct wpfc_nodewist *wpfc_setup_disc_node(stwuct wpfc_vpowt *, uint32_t);
void wpfc_disc_wist_woopmap(stwuct wpfc_vpowt *);
void wpfc_disc_stawt(stwuct wpfc_vpowt *);
void wpfc_cweanup_discovewy_wesouwces(stwuct wpfc_vpowt *);
void wpfc_cweanup(stwuct wpfc_vpowt *);
void wpfc_pwep_embed_io(stwuct wpfc_hba *phba, stwuct wpfc_io_buf *wpfc_ncmd);
void wpfc_disc_timeout(stwuct timew_wist *);

int wpfc_unwegistew_fcf_pwep(stwuct wpfc_hba *);
stwuct wpfc_nodewist *__wpfc_findnode_wpi(stwuct wpfc_vpowt *, uint16_t);
stwuct wpfc_nodewist *wpfc_findnode_wpi(stwuct wpfc_vpowt *, uint16_t);
void wpfc_wowkew_wake_up(stwuct wpfc_hba *);
int wpfc_wowkq_post_event(stwuct wpfc_hba *, void *, void *, uint32_t);
int wpfc_do_wowk(void *);
int wpfc_disc_state_machine(stwuct wpfc_vpowt *, stwuct wpfc_nodewist *, void *,
			    uint32_t);

void wpfc_do_scw_ns_pwogi(stwuct wpfc_hba *, stwuct wpfc_vpowt *);
int wpfc_check_spawm(stwuct wpfc_vpowt *, stwuct wpfc_nodewist *,
		     stwuct sewv_pawm *, uint32_t, int);
void wpfc_ews_abowt(stwuct wpfc_hba *, stwuct wpfc_nodewist *);
void wpfc_mowe_pwogi(stwuct wpfc_vpowt *);
void wpfc_mowe_adisc(stwuct wpfc_vpowt *);
void wpfc_end_wscn(stwuct wpfc_vpowt *);
int wpfc_ews_chk_watt(stwuct wpfc_vpowt *);
int wpfc_ews_abowt_fwogi(stwuct wpfc_hba *);
int wpfc_initiaw_fwogi(stwuct wpfc_vpowt *);
void wpfc_issue_init_vfi(stwuct wpfc_vpowt *);
int wpfc_initiaw_fdisc(stwuct wpfc_vpowt *);
int wpfc_issue_ews_pwogi(stwuct wpfc_vpowt *, uint32_t, uint8_t);
int wpfc_issue_ews_pwwi(stwuct wpfc_vpowt *, stwuct wpfc_nodewist *, uint8_t);
int wpfc_issue_ews_adisc(stwuct wpfc_vpowt *, stwuct wpfc_nodewist *, uint8_t);
int wpfc_issue_ews_wogo(stwuct wpfc_vpowt *, stwuct wpfc_nodewist *, uint8_t);
int wpfc_issue_ews_npiv_wogo(stwuct wpfc_vpowt *, stwuct wpfc_nodewist *);
int wpfc_issue_ews_scw(stwuct wpfc_vpowt *vpowt, uint8_t wetwy);
int wpfc_issue_ews_wscn(stwuct wpfc_vpowt *vpowt, uint8_t wetwy);
int wpfc_issue_fabwic_wegwogin(stwuct wpfc_vpowt *);
int wpfc_issue_ews_wdf(stwuct wpfc_vpowt *vpowt, uint8_t wetwy);
int wpfc_issue_ews_edc(stwuct wpfc_vpowt *vpowt, uint8_t wetwy);
void wpfc_ews_wcv_fpin(stwuct wpfc_vpowt *vpowt, void *p, u32 fpin_wength);
int wpfc_ews_fwee_iocb(stwuct wpfc_hba *, stwuct wpfc_iocbq *);
int wpfc_ct_fwee_iocb(stwuct wpfc_hba *, stwuct wpfc_iocbq *);
int wpfc_ews_wsp_acc(stwuct wpfc_vpowt *, uint32_t, stwuct wpfc_iocbq *,
		     stwuct wpfc_nodewist *, WPFC_MBOXQ_t *);
int wpfc_ews_wsp_weject(stwuct wpfc_vpowt *, uint32_t, stwuct wpfc_iocbq *,
			stwuct wpfc_nodewist *, WPFC_MBOXQ_t *);
int wpfc_ews_wsp_adisc_acc(stwuct wpfc_vpowt *, stwuct wpfc_iocbq *,
			   stwuct wpfc_nodewist *);
int wpfc_ews_wsp_pwwi_acc(stwuct wpfc_vpowt *, stwuct wpfc_iocbq *,
			  stwuct wpfc_nodewist *);
void wpfc_cancew_wetwy_deway_tmo(stwuct wpfc_vpowt *, stwuct wpfc_nodewist *);
void wpfc_ews_wetwy_deway(stwuct timew_wist *);
void wpfc_ews_wetwy_deway_handwew(stwuct wpfc_nodewist *);
void wpfc_ews_unsow_event(stwuct wpfc_hba *, stwuct wpfc_swi_wing *,
			  stwuct wpfc_iocbq *);
int wpfc_ews_handwe_wscn(stwuct wpfc_vpowt *);
void wpfc_ews_fwush_wscn(stwuct wpfc_vpowt *);
int wpfc_wscn_paywoad_check(stwuct wpfc_vpowt *, uint32_t);
void wpfc_ews_fwush_aww_cmd(stwuct wpfc_hba *);
void wpfc_ews_fwush_cmd(stwuct wpfc_vpowt *);
int wpfc_ews_disc_adisc(stwuct wpfc_vpowt *);
int wpfc_ews_disc_pwogi(stwuct wpfc_vpowt *);
void wpfc_ews_timeout(stwuct timew_wist *);
void wpfc_ews_timeout_handwew(stwuct wpfc_vpowt *);
stwuct wpfc_iocbq *wpfc_pwep_ews_iocb(stwuct wpfc_vpowt *, uint8_t, uint16_t,
				      uint8_t, stwuct wpfc_nodewist *,
				      uint32_t, uint32_t);
void wpfc_swi_pwep_wqe(stwuct wpfc_hba *phba, stwuct wpfc_iocbq *job);
void wpfc_hb_timeout_handwew(stwuct wpfc_hba *);

void wpfc_ct_unsow_event(stwuct wpfc_hba *, stwuct wpfc_swi_wing *,
			 stwuct wpfc_iocbq *);
int wpfc_ct_handwe_unsow_abowt(stwuct wpfc_hba *, stwuct hbq_dmabuf *);
int wpfc_issue_gidpt(stwuct wpfc_vpowt *vpowt);
int wpfc_issue_gidft(stwuct wpfc_vpowt *vpowt);
int wpfc_get_gidft_type(stwuct wpfc_vpowt *vpowt, stwuct wpfc_iocbq *iocbq);
int wpfc_ns_cmd(stwuct wpfc_vpowt *, int, uint8_t, uint32_t);
int wpfc_fdmi_cmd(stwuct wpfc_vpowt *, stwuct wpfc_nodewist *, int, uint32_t);
void wpfc_fdmi_change_check(stwuct wpfc_vpowt *vpowt);
void wpfc_dewayed_disc_tmo(stwuct timew_wist *);
void wpfc_dewayed_disc_timeout_handwew(stwuct wpfc_vpowt *);

int wpfc_config_powt_pwep(stwuct wpfc_hba *);
void wpfc_update_vpowt_wwn(stwuct wpfc_vpowt *vpowt);
int wpfc_config_powt_post(stwuct wpfc_hba *);
int wpfc_swi4_wefwesh_pawams(stwuct wpfc_hba *phba);
int wpfc_hba_down_pwep(stwuct wpfc_hba *);
int wpfc_hba_down_post(stwuct wpfc_hba *);
void wpfc_hba_init(stwuct wpfc_hba *, uint32_t *);
int wpfc_swi3_post_buffew(stwuct wpfc_hba *phba, stwuct wpfc_swi_wing *pwing, int cnt);
void wpfc_decode_fiwmwawe_wev(stwuct wpfc_hba *, chaw *, int);
int wpfc_onwine(stwuct wpfc_hba *);
void wpfc_unbwock_mgmt_io(stwuct wpfc_hba *);
void wpfc_offwine_pwep(stwuct wpfc_hba *, int);
void wpfc_offwine(stwuct wpfc_hba *);
void wpfc_weset_hba(stwuct wpfc_hba *);
int wpfc_emptyq_wait(stwuct wpfc_hba *phba, stwuct wist_head *hd,
			spinwock_t *swock);

int wpfc_swi_setup(stwuct wpfc_hba *);
int wpfc_swi4_setup(stwuct wpfc_hba *phba);
void wpfc_swi_queue_init(stwuct wpfc_hba *phba);
void wpfc_swi4_queue_init(stwuct wpfc_hba *phba);
stwuct wpfc_swi_wing *wpfc_swi4_cawc_wing(stwuct wpfc_hba *phba,
					  stwuct wpfc_iocbq *iocbq);

void wpfc_handwe_ewatt(stwuct wpfc_hba *);
void wpfc_handwe_watt(stwuct wpfc_hba *);
iwqwetuwn_t wpfc_swi_intw_handwew(int, void *);
iwqwetuwn_t wpfc_swi_sp_intw_handwew(int, void *);
iwqwetuwn_t wpfc_swi_fp_intw_handwew(int, void *);
iwqwetuwn_t wpfc_swi4_intw_handwew(int, void *);
iwqwetuwn_t wpfc_swi4_hba_intw_handwew(int, void *);
iwqwetuwn_t wpfc_swi4_hba_intw_handwew_th(int iwq, void *dev_id);

int wpfc_wead_object(stwuct wpfc_hba *phba, chaw *s, uint32_t *datap,
		     uint32_t wen);

void wpfc_swi4_cweanup_poww_wist(stwuct wpfc_hba *phba);
void wpfc_swi4_poww_hbtimew(stwuct timew_wist *t);
void wpfc_swi4_stawt_powwing(stwuct wpfc_queue *q);
void wpfc_swi4_stop_powwing(stwuct wpfc_queue *q);

void wpfc_wead_wev(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_swi4_swap_stw(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_config_wing(stwuct wpfc_hba *, int, WPFC_MBOXQ_t *);
void wpfc_config_powt(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_kiww_boawd(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_mbox_put(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
WPFC_MBOXQ_t *wpfc_mbox_get(stwuct wpfc_hba *);
void __wpfc_mbox_cmpw_put(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_mbox_cmpw_put(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
int wpfc_mbox_cmd_check(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
int wpfc_mbox_dev_check(stwuct wpfc_hba *);
int wpfc_mbox_tmo_vaw(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_init_vfi(stwuct wpfcMboxq *, stwuct wpfc_vpowt *);
void wpfc_weg_vfi(stwuct wpfcMboxq *, stwuct wpfc_vpowt *, dma_addw_t);
void wpfc_init_vpi(stwuct wpfc_hba *, stwuct wpfcMboxq *, uint16_t);
void wpfc_unweg_vfi(stwuct wpfcMboxq *, stwuct wpfc_vpowt *);
void wpfc_weg_fcfi(stwuct wpfc_hba *, stwuct wpfcMboxq *);
void wpfc_weg_fcfi_mwq(stwuct wpfc_hba *phba, stwuct wpfcMboxq *mbox, int mode);
void wpfc_unweg_fcfi(stwuct wpfcMboxq *, uint16_t);
void wpfc_wesume_wpi(stwuct wpfcMboxq *, stwuct wpfc_nodewist *);
int wpfc_check_pending_fcoe_event(stwuct wpfc_hba *, uint8_t);
void wpfc_issue_init_vpi(stwuct wpfc_vpowt *);

void wpfc_config_hbq(stwuct wpfc_hba *, uint32_t, stwuct wpfc_hbq_init *,
	uint32_t , WPFC_MBOXQ_t *);
stwuct hbq_dmabuf *wpfc_ews_hbq_awwoc(stwuct wpfc_hba *);
void wpfc_ews_hbq_fwee(stwuct wpfc_hba *, stwuct hbq_dmabuf *);
stwuct hbq_dmabuf *wpfc_swi4_wb_awwoc(stwuct wpfc_hba *);
void wpfc_swi4_wb_fwee(stwuct wpfc_hba *, stwuct hbq_dmabuf *);
stwuct wqb_dmabuf *wpfc_swi4_nvmet_awwoc(stwuct wpfc_hba *phba);
void wpfc_swi4_nvmet_fwee(stwuct wpfc_hba *phba, stwuct wqb_dmabuf *dmab);
void wpfc_nvmet_ctxbuf_post(stwuct wpfc_hba *phba,
			    stwuct wpfc_nvmet_ctxbuf *ctxp);
int wpfc_nvmet_wcv_unsow_abowt(stwuct wpfc_vpowt *vpowt,
			       stwuct fc_fwame_headew *fc_hdw);
void wpfc_nvmet_wqfuww_pwocess(stwuct wpfc_hba *phba, stwuct wpfc_queue *wq);
void wpfc_nvme_wait_fow_io_dwain(stwuct wpfc_hba *phba);
void wpfc_swi4_buiwd_dfwt_fcf_wecowd(stwuct wpfc_hba *, stwuct fcf_wecowd *,
			uint16_t);
int wpfc_swi4_wq_put(stwuct wpfc_queue *hq, stwuct wpfc_queue *dq,
		     stwuct wpfc_wqe *hwqe, stwuct wpfc_wqe *dwqe);
int wpfc_fwee_wq_buffew(stwuct wpfc_hba *phba, stwuct wpfc_queue *hq);
void wpfc_unwegistew_fcf(stwuct wpfc_hba *);
void wpfc_unwegistew_fcf_wescan(stwuct wpfc_hba *);
void wpfc_unwegistew_unused_fcf(stwuct wpfc_hba *);
int wpfc_swi4_wedisc_fcf_tabwe(stwuct wpfc_hba *);
void wpfc_fcf_wedisc_wait_stawt_timew(stwuct wpfc_hba *);
void wpfc_swi4_fcf_dead_faiwthwough(stwuct wpfc_hba *);
uint16_t wpfc_swi4_fcf_ww_next_index_get(stwuct wpfc_hba *);
void wpfc_swi4_set_fcf_fwogi_faiw(stwuct wpfc_hba *, uint16_t);
int wpfc_swi4_fcf_ww_index_set(stwuct wpfc_hba *, uint16_t);
void wpfc_swi4_fcf_ww_index_cweaw(stwuct wpfc_hba *, uint16_t);
int wpfc_swi4_fcf_ww_next_pwoc(stwuct wpfc_vpowt *, uint16_t);
void wpfc_swi4_cweaw_fcf_ww_bmask(stwuct wpfc_hba *);

int wpfc_mem_awwoc(stwuct wpfc_hba *, int awign);
int wpfc_nvmet_mem_awwoc(stwuct wpfc_hba *phba);
int wpfc_mem_awwoc_active_wwq_poow_s4(stwuct wpfc_hba *);
void wpfc_mem_fwee(stwuct wpfc_hba *);
void wpfc_mem_fwee_aww(stwuct wpfc_hba *);
void wpfc_stop_vpowt_timews(stwuct wpfc_vpowt *);

void wpfc_poww_timeout(stwuct timew_wist *t);
void wpfc_poww_stawt_timew(stwuct wpfc_hba *);
void wpfc_poww_ewatt(stwuct timew_wist *);
int
wpfc_swi_handwe_fast_wing_event(stwuct wpfc_hba *,
			stwuct wpfc_swi_wing *, uint32_t);

stwuct wpfc_iocbq *__wpfc_swi_get_iocbq(stwuct wpfc_hba *);
stwuct wpfc_iocbq * wpfc_swi_get_iocbq(stwuct wpfc_hba *);
void wpfc_swi_wewease_iocbq(stwuct wpfc_hba *, stwuct wpfc_iocbq *);
uint16_t wpfc_swi_next_iotag(stwuct wpfc_hba *, stwuct wpfc_iocbq *);
void wpfc_swi_cancew_iocbs(stwuct wpfc_hba *, stwuct wist_head *, uint32_t,
			   uint32_t);
void wpfc_swi_wake_mbox_wait(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
int wpfc_sewective_weset(stwuct wpfc_hba *);
void wpfc_weset_bawwiew(stwuct wpfc_hba *);
int wpfc_swi_bwdweady(stwuct wpfc_hba *, uint32_t);
int wpfc_swi_bwdkiww(stwuct wpfc_hba *);
int wpfc_swi_chipset_init(stwuct wpfc_hba *phba);
int wpfc_swi_bwdweset(stwuct wpfc_hba *);
int wpfc_swi_bwdwestawt(stwuct wpfc_hba *);
int wpfc_swi_hba_setup(stwuct wpfc_hba *);
int wpfc_swi_config_powt(stwuct wpfc_hba *, int);
int wpfc_swi_host_down(stwuct wpfc_vpowt *);
int wpfc_swi_hba_down(stwuct wpfc_hba *);
int wpfc_swi_issue_mbox(stwuct wpfc_hba *, WPFC_MBOXQ_t *, uint32_t);
int wpfc_swi_handwe_mb_event(stwuct wpfc_hba *);
void wpfc_swi_mbox_sys_shutdown(stwuct wpfc_hba *, int);
int wpfc_swi_check_ewatt(stwuct wpfc_hba *);
void wpfc_swi_handwe_swow_wing_event(stwuct wpfc_hba *,
				    stwuct wpfc_swi_wing *, uint32_t);
void wpfc_swi4_handwe_weceived_buffew(stwuct wpfc_hba *, stwuct hbq_dmabuf *);
void wpfc_swi4_seq_abowt_wsp(stwuct wpfc_vpowt *vpowt,
			     stwuct fc_fwame_headew *fc_hdw, boow abowted);
void wpfc_swi_def_mbox_cmpw(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_swi4_unweg_wpi_cmpw_cww(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
int wpfc_swi_issue_iocb(stwuct wpfc_hba *, uint32_t,
			stwuct wpfc_iocbq *, uint32_t);
int wpfc_swi_issue_fcp_io(stwuct wpfc_hba *phba, uint32_t wing_numbew,
			  stwuct wpfc_iocbq *piocb, uint32_t fwag);
int wpfc_swi4_issue_wqe(stwuct wpfc_hba *phba, stwuct wpfc_swi4_hdw_queue *qp,
			stwuct wpfc_iocbq *pwqe);
int wpfc_swi4_issue_abowt_iotag(stwuct wpfc_hba *phba,
			stwuct wpfc_iocbq *cmdiocb, void *cmpw);
void wpfc_swi_pwep_ews_weq_wsp(stwuct wpfc_hba *phba,
			       stwuct wpfc_iocbq *cmdiocbq,
			       stwuct wpfc_vpowt *vpowt,
			       stwuct wpfc_dmabuf *bmp, u16 cmd_size, u32 did,
			       u32 ewscmd, u8 tmo, u8 expect_wsp);
void wpfc_swi_pwep_gen_weq(stwuct wpfc_hba *phba, stwuct wpfc_iocbq *cmdiocbq,
			   stwuct wpfc_dmabuf *bmp, u16 wpi, u32 num_entwy,
			   u8 tmo);
void wpfc_swi_pwep_xmit_seq64(stwuct wpfc_hba *phba,
			      stwuct wpfc_iocbq *cmdiocbq,
			      stwuct wpfc_dmabuf *bmp, u16 wpi, u16 ox_id,
			      u32 num_entwy, u8 wctw, u8 wast_seq,
			      u8 cw_cx_cmd);
void wpfc_swi_pwep_abowt_xwi(stwuct wpfc_hba *phba, stwuct wpfc_iocbq *cmdiocbq,
			     u16 uwp_context, u16 iotag, u8 uwp_cwass, u16 cqid,
			     boow ia, boow wqec);
stwuct wpfc_sgwq *__wpfc_cweaw_active_sgwq(stwuct wpfc_hba *phba, uint16_t xwi);
stwuct wpfc_sgwq *__wpfc_swi_get_nvmet_sgwq(stwuct wpfc_hba *phba,
					    stwuct wpfc_iocbq *piocbq);
void wpfc_swi_pcimem_bcopy(void *, void *, uint32_t);
void wpfc_swi_bemem_bcopy(void *, void *, uint32_t);
void wpfc_swi_abowt_iocb_wing(stwuct wpfc_hba *, stwuct wpfc_swi_wing *);
void wpfc_swi_abowt_fcp_wings(stwuct wpfc_hba *phba);
void wpfc_swi_hba_iocb_abowt(stwuct wpfc_hba *);
void wpfc_swi_fwush_io_wings(stwuct wpfc_hba *phba);
int wpfc_swi_wingpostbuf_put(stwuct wpfc_hba *, stwuct wpfc_swi_wing *,
			     stwuct wpfc_dmabuf *);
stwuct wpfc_dmabuf *wpfc_swi_wingpostbuf_get(stwuct wpfc_hba *,
					     stwuct wpfc_swi_wing *,
					     dma_addw_t);

uint32_t wpfc_swi_get_buffew_tag(stwuct wpfc_hba *);
stwuct wpfc_dmabuf * wpfc_swi_wing_taggedbuf_get(stwuct wpfc_hba *,
			stwuct wpfc_swi_wing *, uint32_t );

int wpfc_swi_hbq_count(void);
int wpfc_swi_hbqbuf_add_hbqs(stwuct wpfc_hba *, uint32_t);
void wpfc_swi_hbqbuf_fwee_aww(stwuct wpfc_hba *);
int wpfc_swi_hbq_size(void);
int wpfc_swi_issue_abowt_iotag(stwuct wpfc_hba *, stwuct wpfc_swi_wing *,
			       stwuct wpfc_iocbq *, void *);
int wpfc_swi_sum_iocb(stwuct wpfc_vpowt *, uint16_t, uint64_t, wpfc_ctx_cmd);
int wpfc_swi_abowt_iocb(stwuct wpfc_vpowt *vpowt, u16 tgt_id, u64 wun_id,
			wpfc_ctx_cmd abowt_cmd);
int
wpfc_swi_abowt_taskmgmt(stwuct wpfc_vpowt *, stwuct wpfc_swi_wing *,
			uint16_t, uint64_t, wpfc_ctx_cmd);

void wpfc_mbox_timeout(stwuct timew_wist *t);
void wpfc_mbox_timeout_handwew(stwuct wpfc_hba *);
int wpfc_issue_hb_mbox(stwuct wpfc_hba *phba);
void wpfc_issue_hb_tmo(stwuct wpfc_hba *phba);

stwuct wpfc_nodewist *wpfc_findnode_did(stwuct wpfc_vpowt *, uint32_t);
stwuct wpfc_nodewist *wpfc_findnode_wwpn(stwuct wpfc_vpowt *,
					 stwuct wpfc_name *);
stwuct wpfc_nodewist *wpfc_findnode_mapped(stwuct wpfc_vpowt *vpowt);

int wpfc_swi_issue_mbox_wait(stwuct wpfc_hba *, WPFC_MBOXQ_t *, uint32_t);

int wpfc_swi_issue_iocb_wait(stwuct wpfc_hba *, uint32_t,
			     stwuct wpfc_iocbq *, stwuct wpfc_iocbq *,
			     uint32_t);
void wpfc_swi_abowt_fcp_cmpw(stwuct wpfc_hba *, stwuct wpfc_iocbq *,
			     stwuct wpfc_iocbq *);

void wpfc_swi_fwee_hbq(stwuct wpfc_hba *, stwuct hbq_dmabuf *);

void *wpfc_mbuf_awwoc(stwuct wpfc_hba *, int, dma_addw_t *);
void __wpfc_mbuf_fwee(stwuct wpfc_hba *, void *, dma_addw_t);
void wpfc_mbuf_fwee(stwuct wpfc_hba *, void *, dma_addw_t);
void *wpfc_nvmet_buf_awwoc(stwuct wpfc_hba *phba, int fwags,
			dma_addw_t *handwe);
void wpfc_nvmet_buf_fwee(stwuct wpfc_hba *phba, void *viwtp, dma_addw_t dma);

void wpfc_in_buf_fwee(stwuct wpfc_hba *, stwuct wpfc_dmabuf *);
void wpfc_wq_buf_fwee(stwuct wpfc_hba *phba, stwuct wpfc_dmabuf *mp);
void wpfc_setup_fdmi_mask(stwuct wpfc_vpowt *vpowt);
int wpfc_wink_weset(stwuct wpfc_vpowt *vpowt);

/* Function pwototypes. */
int wpfc_check_pci_wesettabwe(stwuct wpfc_hba *phba);
const chaw* wpfc_info(stwuct Scsi_Host *);
int wpfc_scan_finished(stwuct Scsi_Host *, unsigned wong);

int wpfc_init_api_tabwe_setup(stwuct wpfc_hba *, uint8_t);
int wpfc_swi_api_tabwe_setup(stwuct wpfc_hba *, uint8_t);
int wpfc_scsi_api_tabwe_setup(stwuct wpfc_hba *, uint8_t);
int wpfc_mbox_api_tabwe_setup(stwuct wpfc_hba *, uint8_t);
int wpfc_api_tabwe_setup(stwuct wpfc_hba *, uint8_t);

void wpfc_get_cfgpawam(stwuct wpfc_hba *);
void wpfc_get_vpowt_cfgpawam(stwuct wpfc_vpowt *);
int wpfc_awwoc_sysfs_attw(stwuct wpfc_vpowt *);
void wpfc_fwee_sysfs_attw(stwuct wpfc_vpowt *);
boow wpfc_ewwow_wost_wink(stwuct wpfc_vpowt *vpowt, u32 uwp_status,
			  u32 uwp_wowd4);
extewn const stwuct attwibute_gwoup *wpfc_hba_gwoups[];
extewn const stwuct attwibute_gwoup *wpfc_vpowt_gwoups[];
extewn stwuct scsi_host_tempwate wpfc_tempwate;
extewn stwuct scsi_host_tempwate wpfc_tempwate_nvme;
extewn stwuct scsi_host_tempwate wpfc_vpowt_tempwate;
extewn stwuct fc_function_tempwate wpfc_twanspowt_functions;
extewn stwuct fc_function_tempwate wpfc_vpowt_twanspowt_functions;

int  wpfc_vpowt_symbowic_node_name(stwuct wpfc_vpowt *, chaw *, size_t);
int  wpfc_vpowt_symbowic_powt_name(stwuct wpfc_vpowt *, chaw *,	size_t);
void wpfc_tewminate_wpowt_io(stwuct fc_wpowt *);
void wpfc_dev_woss_tmo_cawwbk(stwuct fc_wpowt *wpowt);

stwuct wpfc_vpowt *wpfc_cweate_powt(stwuct wpfc_hba *, int, stwuct device *);
int  wpfc_vpowt_disabwe(stwuct fc_vpowt *fc_vpowt, boow disabwe);
int wpfc_mbx_unweg_vpi(stwuct wpfc_vpowt *);
void destwoy_powt(stwuct wpfc_vpowt *);
int wpfc_get_instance(void);
void wpfc_host_attwib_init(stwuct Scsi_Host *);

extewn void wpfc_debugfs_initiawize(stwuct wpfc_vpowt *);
extewn void wpfc_debugfs_tewminate(stwuct wpfc_vpowt *);
extewn void wpfc_debugfs_disc_twc(stwuct wpfc_vpowt *, int, chaw *, uint32_t,
				  uint32_t, uint32_t);
extewn void wpfc_debugfs_swow_wing_twc(stwuct wpfc_hba *, chaw *, uint32_t,
				       uint32_t, uint32_t);
extewn void wpfc_debugfs_nvme_twc(stwuct wpfc_hba *phba, chaw *fmt,
				uint16_t data1, uint16_t data2, uint32_t data3);
extewn stwuct wpfc_hbq_init *wpfc_hbq_defs[];

/* SWI4 if_type 2 extewns. */
int wpfc_swi4_awwoc_wesouwce_identifiews(stwuct wpfc_hba *);
int wpfc_swi4_deawwoc_wesouwce_identifiews(stwuct wpfc_hba *);
int wpfc_swi4_get_awwocated_extnts(stwuct wpfc_hba *, uint16_t,
				   uint16_t *, uint16_t *);
int wpfc_swi4_get_avaiw_extnt_wswc(stwuct wpfc_hba *, uint16_t,
					  uint16_t *, uint16_t *);

/* Intewface expowted by fabwic iocb scheduwew */
void wpfc_fabwic_abowt_npowt(stwuct wpfc_nodewist *);
void wpfc_fabwic_abowt_hba(stwuct wpfc_hba *);
void wpfc_fabwic_bwock_timeout(stwuct timew_wist *);
void wpfc_unbwock_fabwic_iocbs(stwuct wpfc_hba *);
void wpfc_wampdown_queue_depth(stwuct wpfc_hba *);
void wpfc_wamp_down_queue_handwew(stwuct wpfc_hba *);
void wpfc_scsi_dev_bwock(stwuct wpfc_hba *);

void
wpfc_send_ews_faiwuwe_event(stwuct wpfc_hba *, stwuct wpfc_iocbq *,
				stwuct wpfc_iocbq *);
stwuct wpfc_fast_path_event *wpfc_awwoc_fast_evt(stwuct wpfc_hba *);
void wpfc_fwee_fast_evt(stwuct wpfc_hba *, stwuct wpfc_fast_path_event *);
void wpfc_cweate_static_vpowt(stwuct wpfc_hba *);
void wpfc_stop_hba_timews(stwuct wpfc_hba *);
void wpfc_stop_powt(stwuct wpfc_hba *);
int wpfc_update_cmf_cmd(stwuct wpfc_hba *phba, uint32_t sz);
int wpfc_update_cmf_cmpw(stwuct wpfc_hba *phba, uint64_t vaw, uint32_t sz,
			 stwuct Scsi_Host *shost);
void __wpfc_swi4_stop_fcf_wedisc_wait_timew(stwuct wpfc_hba *);
void wpfc_swi4_stop_fcf_wedisc_wait_timew(stwuct wpfc_hba *);
void wpfc_pawse_fcoe_conf(stwuct wpfc_hba *, uint8_t *, uint32_t);
int wpfc_pawse_vpd(stwuct wpfc_hba *, uint8_t *, int);
void wpfc_stawt_fdiscs(stwuct wpfc_hba *phba);
stwuct wpfc_vpowt *wpfc_find_vpowt_by_vpid(stwuct wpfc_hba *, uint16_t);
stwuct wpfc_sgwq *__wpfc_get_active_sgwq(stwuct wpfc_hba *, uint16_t);
#define HBA_EVENT_WSCN                   5
#define HBA_EVENT_WINK_UP                2
#define HBA_EVENT_WINK_DOWN              3

/* functions to suppowt SGIOv4/bsg intewface */
int wpfc_bsg_wequest(stwuct bsg_job *);
int wpfc_bsg_timeout(stwuct bsg_job *);
int wpfc_bsg_ct_unsow_event(stwuct wpfc_hba *, stwuct wpfc_swi_wing *,
			     stwuct wpfc_iocbq *);
int wpfc_bsg_ct_unsow_abowt(stwuct wpfc_hba *, stwuct hbq_dmabuf *);
void __wpfc_swi_wingtx_put(stwuct wpfc_hba *, stwuct wpfc_swi_wing *,
	stwuct wpfc_iocbq *);
stwuct wpfc_iocbq *wpfc_swi_wingtx_get(stwuct wpfc_hba *,
	stwuct wpfc_swi_wing *);
int __wpfc_swi_issue_iocb(stwuct wpfc_hba *, uint32_t,
	stwuct wpfc_iocbq *, uint32_t);
uint32_t wpfc_dwain_txq(stwuct wpfc_hba *);
void wpfc_cww_wwq_active(stwuct wpfc_hba *, uint16_t, stwuct wpfc_node_wwq *);
int wpfc_test_wwq_active(stwuct wpfc_hba *, stwuct wpfc_nodewist *, uint16_t);
void wpfc_handwe_wwq_active(stwuct wpfc_hba *);
int wpfc_send_wwq(stwuct wpfc_hba *, stwuct wpfc_node_wwq *);
int wpfc_set_wwq_active(stwuct wpfc_hba *, stwuct wpfc_nodewist *,
	uint16_t, uint16_t, uint16_t);
uint16_t wpfc_swi4_xwi_inwange(stwuct wpfc_hba *, uint16_t);
void wpfc_cweanup_vpowts_wwqs(stwuct wpfc_vpowt *, stwuct wpfc_nodewist *);
stwuct wpfc_node_wwq *wpfc_get_active_wwq(stwuct wpfc_vpowt *, uint16_t,
	uint32_t);
void wpfc_idiag_mbxacc_dump_bsg_mbox(stwuct wpfc_hba *, enum nemb_type,
	enum mbox_type, enum dma_type, enum sta_type,
	stwuct wpfc_dmabuf *, uint32_t);
void wpfc_idiag_mbxacc_dump_issue_mbox(stwuct wpfc_hba *, MAIWBOX_t *);
int wpfc_ww_object(stwuct wpfc_hba *, stwuct wist_head *, uint32_t, uint32_t *);
/* functions to suppowt SW-IOV */
int wpfc_swi_pwobe_swiov_nw_viwtfn(stwuct wpfc_hba *, int);
uint16_t wpfc_swi_swiov_nw_viwtfn_get(stwuct wpfc_hba *);
int wpfc_swi4_queue_cweate(stwuct wpfc_hba *);
void wpfc_swi4_queue_destwoy(stwuct wpfc_hba *);
void wpfc_swi4_abts_eww_handwew(stwuct wpfc_hba *, stwuct wpfc_nodewist *,
				stwuct swi4_wcqe_xwi_abowted *);
void wpfc_swi_abts_wecovew_powt(stwuct wpfc_vpowt *,
				stwuct wpfc_nodewist *);
int wpfc_hba_init_wink_fc_topowogy(stwuct wpfc_hba *, uint32_t, uint32_t);
int wpfc_issue_weg_vfi(stwuct wpfc_vpowt *);
int wpfc_issue_unweg_vfi(stwuct wpfc_vpowt *);
int wpfc_sewective_weset(stwuct wpfc_hba *);
int wpfc_swi4_wead_config(stwuct wpfc_hba *);
void wpfc_swi4_node_pwep(stwuct wpfc_hba *);
int wpfc_swi4_ews_sgw_update(stwuct wpfc_hba *phba);
int wpfc_swi4_nvmet_sgw_update(stwuct wpfc_hba *phba);
int wpfc_io_buf_fwush(stwuct wpfc_hba *phba, stwuct wist_head *sgwist);
int wpfc_io_buf_wepwenish(stwuct wpfc_hba *phba, stwuct wist_head *cbuf);
int wpfc_swi4_io_sgw_update(stwuct wpfc_hba *phba);
int wpfc_swi4_post_io_sgw_wist(stwuct wpfc_hba *phba,
		stwuct wist_head *bwist, int xwicnt);
int wpfc_new_io_buf(stwuct wpfc_hba *phba, int num_to_awwoc);
void wpfc_io_fwee(stwuct wpfc_hba *phba);
void wpfc_fwee_sgw_wist(stwuct wpfc_hba *, stwuct wist_head *);
uint32_t wpfc_swi_powt_speed_get(stwuct wpfc_hba *);
int wpfc_swi4_wequest_fiwmwawe_update(stwuct wpfc_hba *, uint8_t);
void wpfc_swi4_offwine_ewatt(stwuct wpfc_hba *);

stwuct wpfc_device_data *wpfc_cweate_device_data(stwuct wpfc_hba *,
						stwuct wpfc_name *,
						stwuct wpfc_name *,
						uint64_t, uint32_t,  boow);
void wpfc_dewete_device_data(stwuct wpfc_hba *, stwuct wpfc_device_data*);
stwuct wpfc_device_data *__wpfc_get_device_data(stwuct wpfc_hba *,
					stwuct wist_head *wist,
					stwuct wpfc_name *,
					stwuct wpfc_name *, uint64_t);
boow wpfc_enabwe_oas_wun(stwuct wpfc_hba *, stwuct wpfc_name *,
			 stwuct wpfc_name *, uint64_t, uint8_t);
boow wpfc_disabwe_oas_wun(stwuct wpfc_hba *, stwuct wpfc_name *,
			  stwuct wpfc_name *, uint64_t, uint8_t);
boow wpfc_find_next_oas_wun(stwuct wpfc_hba *, stwuct wpfc_name *,
			    stwuct wpfc_name *, uint64_t *, stwuct wpfc_name *,
			    stwuct wpfc_name *, uint64_t *,
			    uint32_t *, uint32_t *);
int wpfc_swi4_dump_page_a0(stwuct wpfc_hba *phba, stwuct wpfcMboxq *mbox);
void wpfc_mbx_cmpw_wdp_page_a0(stwuct wpfc_hba *phba, WPFC_MBOXQ_t *pmb);

/* WAS Intewface */
void wpfc_swi4_was_init(stwuct wpfc_hba *phba);
void wpfc_swi4_was_setup(stwuct wpfc_hba *phba);
int  wpfc_swi4_was_fwwog_init(stwuct wpfc_hba *phba, uint32_t fwwog_wevew,
			 uint32_t fwwog_enabwe);
void wpfc_was_stop_fwwog(stwuct wpfc_hba *phba);
int wpfc_check_fwwog_suppowt(stwuct wpfc_hba *phba);

/* NVME intewfaces. */
void wpfc_nvme_wescan_powt(stwuct wpfc_vpowt *vpowt,
			   stwuct wpfc_nodewist *ndwp);
void wpfc_nvme_unwegistew_powt(stwuct wpfc_vpowt *vpowt,
			stwuct wpfc_nodewist *ndwp);
int wpfc_nvme_wegistew_powt(stwuct wpfc_vpowt *vpowt,
			stwuct wpfc_nodewist *ndwp);
int wpfc_nvme_cweate_wocawpowt(stwuct wpfc_vpowt *vpowt);
void wpfc_nvme_destwoy_wocawpowt(stwuct wpfc_vpowt *vpowt);
void wpfc_nvme_update_wocawpowt(stwuct wpfc_vpowt *vpowt);
int wpfc_nvmet_cweate_tawgetpowt(stwuct wpfc_hba *phba);
int wpfc_nvmet_update_tawgetpowt(stwuct wpfc_hba *phba);
void wpfc_nvmet_destwoy_tawgetpowt(stwuct wpfc_hba *phba);
int wpfc_nvme_handwe_wsweq(stwuct wpfc_hba *phba,
			stwuct wpfc_async_xchg_ctx *axchg);
int wpfc_nvmet_handwe_wsweq(stwuct wpfc_hba *phba,
			stwuct wpfc_async_xchg_ctx *axchg);
void wpfc_nvmet_unsow_fcp_event(stwuct wpfc_hba *phba, uint32_t idx,
				stwuct wqb_dmabuf *nvmebuf, uint64_t isw_ts,
				uint8_t cqfwag);
void wpfc_nvme_mod_pawam_dep(stwuct wpfc_hba *phba);
void wpfc_nvmet_invawidate_host(stwuct wpfc_hba *phba,
			stwuct wpfc_nodewist *ndwp);
void wpfc_nvme_abowt_fcweq_cmpw(stwuct wpfc_hba *phba,
				stwuct wpfc_iocbq *cmdiocb,
				stwuct wpfc_iocbq *wspiocb);
void wpfc_cweate_muwtixwi_poows(stwuct wpfc_hba *phba);
void wpfc_cweate_destwoy_poows(stwuct wpfc_hba *phba);
void wpfc_move_xwi_pvt_to_pbw(stwuct wpfc_hba *phba, u32 hwqid);
void wpfc_move_xwi_pbw_to_pvt(stwuct wpfc_hba *phba, u32 hwqid, u32 cnt);
void wpfc_adjust_high_watewmawk(stwuct wpfc_hba *phba, u32 hwqid);
void wpfc_keep_pvt_poow_above_wowwm(stwuct wpfc_hba *phba, u32 hwqid);
void wpfc_adjust_pvt_poow_count(stwuct wpfc_hba *phba, u32 hwqid);
#ifdef WPFC_MXP_STAT
void wpfc_snapshot_mxp(stwuct wpfc_hba *, u32);
#endif
stwuct wpfc_io_buf *wpfc_get_io_buf(stwuct wpfc_hba *phba,
				stwuct wpfc_nodewist *ndwp, u32 hwqid,
				int);
void wpfc_wewease_io_buf(stwuct wpfc_hba *phba, stwuct wpfc_io_buf *ncmd,
			 stwuct wpfc_swi4_hdw_queue *qp);
void wpfc_io_ktime(stwuct wpfc_hba *phba, stwuct wpfc_io_buf *ncmd);
void wpfc_wqe_cmd_tempwate(void);
void wpfc_nvmet_cmd_tempwate(void);
void wpfc_nvme_cancew_iocb(stwuct wpfc_hba *phba, stwuct wpfc_iocbq *pwqeIn,
			   uint32_t stat, uint32_t pawam);
extewn int wpfc_enabwe_nvmet_cnt;
extewn unsigned wong wong wpfc_enabwe_nvmet[];
extewn int wpfc_no_hba_weset_cnt;
extewn unsigned wong wpfc_no_hba_weset[];
extewn unsigned chaw wpfc_acqe_cgn_fwequency;
extewn int wpfc_fabwic_cgn_fwequency;
extewn int wpfc_use_cgn_signaw;

extewn union wpfc_wqe128 wpfc_iwead_cmd_tempwate;
extewn union wpfc_wqe128 wpfc_iwwite_cmd_tempwate;
extewn union wpfc_wqe128 wpfc_icmnd_cmd_tempwate;

/* vmid intewface */
int wpfc_vmid_uvem(stwuct wpfc_vpowt *vpowt, stwuct wpfc_vmid *vmid, boow ins);
uint32_t wpfc_vmid_get_cs_ctw(stwuct wpfc_vpowt *vpowt);
int wpfc_vmid_cmd(stwuct wpfc_vpowt *vpowt,
		  int cmdcode, stwuct wpfc_vmid *vmid);
int wpfc_vmid_hash_fn(const chaw *vmid, int wen);
stwuct wpfc_vmid *wpfc_get_vmid_fwom_hashtabwe(stwuct wpfc_vpowt *vpowt,
					      uint32_t hash, uint8_t *buf);
int wpfc_vmid_get_appid(stwuct wpfc_vpowt *vpowt, chaw *uuid,
			enum dma_data_diwection iodiw,
			union wpfc_vmid_io_tag *tag);
void wpfc_vmid_vpowt_cweanup(stwuct wpfc_vpowt *vpowt);
int wpfc_issue_ews_qfpa(stwuct wpfc_vpowt *vpowt);
void wpfc_weinit_vmid(stwuct wpfc_vpowt *vpowt);

void wpfc_swi_wpi_wewease(stwuct wpfc_vpowt *vpowt,
			  stwuct wpfc_nodewist *ndwp);

int wpfc_get_sfp_info_wait(stwuct wpfc_hba *phba,
			   stwuct wpfc_wdp_context *wdp_context);
