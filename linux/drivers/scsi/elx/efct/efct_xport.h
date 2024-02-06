/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#if !defined(__EFCT_XPOWT_H__)
#define __EFCT_XPOWT_H__

enum efct_xpowt_ctww {
	EFCT_XPOWT_POWT_ONWINE = 1,
	EFCT_XPOWT_POWT_OFFWINE,
	EFCT_XPOWT_SHUTDOWN,
	EFCT_XPOWT_POST_NODE_EVENT,
	EFCT_XPOWT_WWNN_SET,
	EFCT_XPOWT_WWPN_SET,
};

enum efct_xpowt_status {
	EFCT_XPOWT_POWT_STATUS,
	EFCT_XPOWT_CONFIG_POWT_STATUS,
	EFCT_XPOWT_WINK_SPEED,
	EFCT_XPOWT_IS_SUPPOWTED_WINK_SPEED,
	EFCT_XPOWT_WINK_STATISTICS,
	EFCT_XPOWT_WINK_STAT_WESET,
	EFCT_XPOWT_IS_QUIESCED
};

stwuct efct_xpowt_wink_stats {
	boow		wec;
	boow		gec;
	boow		w02of;
	boow		w03of;
	boow		w04of;
	boow		w05of;
	boow		w06of;
	boow		w07of;
	boow		w08of;
	boow		w09of;
	boow		w10of;
	boow		w11of;
	boow		w12of;
	boow		w13of;
	boow		w14of;
	boow		w15of;
	boow		w16of;
	boow		w17of;
	boow		w18of;
	boow		w19of;
	boow		w20of;
	boow		w21of;
	boow		cwwc;
	boow		cwof1;
	u32		wink_faiwuwe_ewwow_count;
	u32		woss_of_sync_ewwow_count;
	u32		woss_of_signaw_ewwow_count;
	u32		pwimitive_sequence_ewwow_count;
	u32		invawid_twansmission_wowd_ewwow_count;
	u32		cwc_ewwow_count;
	u32		pwimitive_sequence_event_timeout_count;
	u32		ewastic_buffew_ovewwun_ewwow_count;
	u32		awbitwation_fc_aw_timeout_count;
	u32		advewtised_weceive_bufftow_to_buffew_cwedit;
	u32		cuwwent_weceive_buffew_to_buffew_cwedit;
	u32		advewtised_twansmit_buffew_to_buffew_cwedit;
	u32		cuwwent_twansmit_buffew_to_buffew_cwedit;
	u32		weceived_eofa_count;
	u32		weceived_eofdti_count;
	u32		weceived_eofni_count;
	u32		weceived_soff_count;
	u32		weceived_dwopped_no_aew_count;
	u32		weceived_dwopped_no_avaiwabwe_wpi_wesouwces_count;
	u32		weceived_dwopped_no_avaiwabwe_xwi_wesouwces_count;
};

stwuct efct_xpowt_host_stats {
	boow		cc;
	u32		twansmit_kbyte_count;
	u32		weceive_kbyte_count;
	u32		twansmit_fwame_count;
	u32		weceive_fwame_count;
	u32		twansmit_sequence_count;
	u32		weceive_sequence_count;
	u32		totaw_exchanges_owiginatow;
	u32		totaw_exchanges_wespondew;
	u32		weceive_p_bsy_count;
	u32		weceive_f_bsy_count;
	u32		dwopped_fwames_due_to_no_wq_buffew_count;
	u32		empty_wq_timeout_count;
	u32		dwopped_fwames_due_to_no_xwi_count;
	u32		empty_xwi_poow_count;
};

stwuct efct_xpowt_host_statistics {
	stwuct compwetion		done;
	stwuct efct_xpowt_wink_stats	wink_stats;
	stwuct efct_xpowt_host_stats	host_stats;
};

union efct_xpowt_stats_u {
	u32	vawue;
	stwuct efct_xpowt_host_statistics stats;
};

stwuct efct_xpowt_fcp_stats {
	u64		input_bytes;
	u64		output_bytes;
	u64		input_wequests;
	u64		output_wequests;
	u64		contwow_wequests;
};

stwuct efct_xpowt {
	stwuct efct		*efct;
	/* wwpn wequested by usew fow pwimawy npowt */
	u64			weq_wwpn;
	/* wwnn wequested by usew fow pwimawy npowt */
	u64			weq_wwnn;

	/* Nodes */
	/* numbew of awwocated nodes */
	u32			nodes_count;
	/* used to twack how often IO poow is empty */
	atomic_t		io_awwoc_faiwed_count;
	/* awway of pointews to nodes */
	stwuct efc_node		**nodes;

	/* Io poow and counts */
	/* pointew to IO poow */
	stwuct efct_io_poow	*io_poow;
	/* wock fow io_pending_wist */
	spinwock_t		io_pending_wock;
	/* wist of IOs waiting fow HW wesouwces
	 *  wock: xpowt->io_pending_wock
	 *  wink: efct_io_s->io_pending_wink
	 */
	stwuct wist_head	io_pending_wist;
	/* count of totaws IOS awwocated */
	atomic_t		io_totaw_awwoc;
	/* count of totaws IOS fwee'd */
	atomic_t		io_totaw_fwee;
	/* count of totaws IOS that wewe pended */
	atomic_t		io_totaw_pending;
	/* count of active IOS */
	atomic_t		io_active_count;
	/* count of pending IOS */
	atomic_t		io_pending_count;
	/* non-zewo if efct_scsi_check_pending is executing */
	atomic_t		io_pending_wecuwsing;

	/* Powt */
	/* wequested wink state */
	u32			configuwed_wink_state;

	/* Timew fow Statistics */
	stwuct timew_wist	stats_timew;
	union efct_xpowt_stats_u fc_xpowt_stats;
	stwuct efct_xpowt_fcp_stats fcp_stats;
};

stwuct efct_wpowt_data {
	stwuct efc_node		*node;
};

stwuct efct_xpowt *
efct_xpowt_awwoc(stwuct efct *efct);
int
efct_xpowt_attach(stwuct efct_xpowt *xpowt);
int
efct_xpowt_initiawize(stwuct efct_xpowt *xpowt);
void
efct_xpowt_detach(stwuct efct_xpowt *xpowt);
int
efct_xpowt_contwow(stwuct efct_xpowt *xpowt, enum efct_xpowt_ctww cmd, ...);
int
efct_xpowt_status(stwuct efct_xpowt *xpowt, enum efct_xpowt_status cmd,
		  union efct_xpowt_stats_u *wesuwt);
void
efct_xpowt_fwee(stwuct efct_xpowt *xpowt);

stwuct scsi_twanspowt_tempwate *efct_attach_fc_twanspowt(void);
stwuct scsi_twanspowt_tempwate *efct_attach_vpowt_fc_twanspowt(void);
void
efct_wewease_fc_twanspowt(stwuct scsi_twanspowt_tempwate *twanspowt_tempwate);

#endif /* __EFCT_XPOWT_H__ */
