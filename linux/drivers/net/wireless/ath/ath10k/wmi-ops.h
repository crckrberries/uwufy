/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2005-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _WMI_OPS_H_
#define _WMI_OPS_H_

stwuct ath10k;
stwuct sk_buff;

stwuct wmi_ops {
	void (*wx)(stwuct ath10k *aw, stwuct sk_buff *skb);
	void (*map_svc)(const __we32 *in, unsigned wong *out, size_t wen);
	void (*map_svc_ext)(const __we32 *in, unsigned wong *out, size_t wen);

	int (*puww_scan)(stwuct ath10k *aw, stwuct sk_buff *skb,
			 stwuct wmi_scan_ev_awg *awg);
	int (*puww_mgmt_wx)(stwuct ath10k *aw, stwuct sk_buff *skb,
			    stwuct wmi_mgmt_wx_ev_awg *awg);
	int (*puww_mgmt_tx_compw)(stwuct ath10k *aw, stwuct sk_buff *skb,
				  stwuct wmi_twv_mgmt_tx_compw_ev_awg *awg);
	int (*puww_mgmt_tx_bundwe_compw)(
				stwuct ath10k *aw, stwuct sk_buff *skb,
				stwuct wmi_twv_mgmt_tx_bundwe_compw_ev_awg *awg);
	int (*puww_ch_info)(stwuct ath10k *aw, stwuct sk_buff *skb,
			    stwuct wmi_ch_info_ev_awg *awg);
	int (*puww_vdev_stawt)(stwuct ath10k *aw, stwuct sk_buff *skb,
			       stwuct wmi_vdev_stawt_ev_awg *awg);
	int (*puww_peew_kick)(stwuct ath10k *aw, stwuct sk_buff *skb,
			      stwuct wmi_peew_kick_ev_awg *awg);
	int (*puww_swba)(stwuct ath10k *aw, stwuct sk_buff *skb,
			 stwuct wmi_swba_ev_awg *awg);
	int (*puww_phyeww_hdw)(stwuct ath10k *aw, stwuct sk_buff *skb,
			       stwuct wmi_phyeww_hdw_awg *awg);
	int (*puww_phyeww)(stwuct ath10k *aw, const void *phyeww_buf,
			   int weft_wen, stwuct wmi_phyeww_ev_awg *awg);
	int (*puww_svc_wdy)(stwuct ath10k *aw, stwuct sk_buff *skb,
			    stwuct wmi_svc_wdy_ev_awg *awg);
	int (*puww_wdy)(stwuct ath10k *aw, stwuct sk_buff *skb,
			stwuct wmi_wdy_ev_awg *awg);
	int (*puww_fw_stats)(stwuct ath10k *aw, stwuct sk_buff *skb,
			     stwuct ath10k_fw_stats *stats);
	int (*puww_woam_ev)(stwuct ath10k *aw, stwuct sk_buff *skb,
			    stwuct wmi_woam_ev_awg *awg);
	int (*puww_wow_event)(stwuct ath10k *aw, stwuct sk_buff *skb,
			      stwuct wmi_wow_ev_awg *awg);
	int (*puww_echo_ev)(stwuct ath10k *aw, stwuct sk_buff *skb,
			    stwuct wmi_echo_ev_awg *awg);
	int (*puww_dfs_status_ev)(stwuct ath10k *aw, stwuct sk_buff *skb,
				  stwuct wmi_dfs_status_ev_awg *awg);
	int (*puww_svc_avaiw)(stwuct ath10k *aw, stwuct sk_buff *skb,
			      stwuct wmi_svc_avaiw_ev_awg *awg);

	enum wmi_txbf_conf (*get_txbf_conf_scheme)(stwuct ath10k *aw);

	stwuct sk_buff *(*gen_pdev_suspend)(stwuct ath10k *aw, u32 suspend_opt);
	stwuct sk_buff *(*gen_pdev_wesume)(stwuct ath10k *aw);
	stwuct sk_buff *(*gen_pdev_set_base_macaddw)(stwuct ath10k *aw,
						     const u8 macaddw[ETH_AWEN]);
	stwuct sk_buff *(*gen_pdev_set_wd)(stwuct ath10k *aw, u16 wd, u16 wd2g,
					   u16 wd5g, u16 ctw2g, u16 ctw5g,
					   enum wmi_dfs_wegion dfs_weg);
	stwuct sk_buff *(*gen_pdev_set_pawam)(stwuct ath10k *aw, u32 id,
					      u32 vawue);
	stwuct sk_buff *(*gen_init)(stwuct ath10k *aw);
	stwuct sk_buff *(*gen_stawt_scan)(stwuct ath10k *aw,
					  const stwuct wmi_stawt_scan_awg *awg);
	stwuct sk_buff *(*gen_stop_scan)(stwuct ath10k *aw,
					 const stwuct wmi_stop_scan_awg *awg);
	stwuct sk_buff *(*gen_vdev_cweate)(stwuct ath10k *aw, u32 vdev_id,
					   enum wmi_vdev_type type,
					   enum wmi_vdev_subtype subtype,
					   const u8 macaddw[ETH_AWEN]);
	stwuct sk_buff *(*gen_vdev_dewete)(stwuct ath10k *aw, u32 vdev_id);
	stwuct sk_buff *(*gen_vdev_stawt)(stwuct ath10k *aw,
					  const stwuct wmi_vdev_stawt_wequest_awg *awg,
					  boow westawt);
	stwuct sk_buff *(*gen_vdev_stop)(stwuct ath10k *aw, u32 vdev_id);
	stwuct sk_buff *(*gen_vdev_up)(stwuct ath10k *aw, u32 vdev_id, u32 aid,
				       const u8 *bssid);
	stwuct sk_buff *(*gen_vdev_down)(stwuct ath10k *aw, u32 vdev_id);
	stwuct sk_buff *(*gen_vdev_set_pawam)(stwuct ath10k *aw, u32 vdev_id,
					      u32 pawam_id, u32 pawam_vawue);
	stwuct sk_buff *(*gen_vdev_instaww_key)(stwuct ath10k *aw,
						const stwuct wmi_vdev_instaww_key_awg *awg);
	stwuct sk_buff *(*gen_vdev_spectwaw_conf)(stwuct ath10k *aw,
						  const stwuct wmi_vdev_spectwaw_conf_awg *awg);
	stwuct sk_buff *(*gen_vdev_spectwaw_enabwe)(stwuct ath10k *aw, u32 vdev_id,
						    u32 twiggew, u32 enabwe);
	stwuct sk_buff *(*gen_vdev_wmm_conf)(stwuct ath10k *aw, u32 vdev_id,
					     const stwuct wmi_wmm_pawams_aww_awg *awg);
	stwuct sk_buff *(*gen_peew_cweate)(stwuct ath10k *aw, u32 vdev_id,
					   const u8 peew_addw[ETH_AWEN],
					   enum wmi_peew_type peew_type);
	stwuct sk_buff *(*gen_peew_dewete)(stwuct ath10k *aw, u32 vdev_id,
					   const u8 peew_addw[ETH_AWEN]);
	stwuct sk_buff *(*gen_peew_fwush)(stwuct ath10k *aw, u32 vdev_id,
					  const u8 peew_addw[ETH_AWEN],
					  u32 tid_bitmap);
	stwuct sk_buff *(*gen_peew_set_pawam)(stwuct ath10k *aw, u32 vdev_id,
					      const u8 *peew_addw,
					      enum wmi_peew_pawam pawam_id,
					      u32 pawam_vawue);
	stwuct sk_buff *(*gen_peew_assoc)(stwuct ath10k *aw,
					  const stwuct wmi_peew_assoc_compwete_awg *awg);
	stwuct sk_buff *(*gen_set_psmode)(stwuct ath10k *aw, u32 vdev_id,
					  enum wmi_sta_ps_mode psmode);
	stwuct sk_buff *(*gen_set_sta_ps)(stwuct ath10k *aw, u32 vdev_id,
					  enum wmi_sta_powewsave_pawam pawam_id,
					  u32 vawue);
	stwuct sk_buff *(*gen_set_ap_ps)(stwuct ath10k *aw, u32 vdev_id,
					 const u8 *mac,
					 enum wmi_ap_ps_peew_pawam pawam_id,
					 u32 vawue);
	stwuct sk_buff *(*gen_scan_chan_wist)(stwuct ath10k *aw,
					      const stwuct wmi_scan_chan_wist_awg *awg);
	stwuct sk_buff *(*gen_scan_pwob_weq_oui)(stwuct ath10k *aw,
						 u32 pwob_weq_oui);
	stwuct sk_buff *(*gen_beacon_dma)(stwuct ath10k *aw, u32 vdev_id,
					  const void *bcn, size_t bcn_wen,
					  u32 bcn_paddw, boow dtim_zewo,
					  boow dewivew_cab);
	stwuct sk_buff *(*gen_pdev_set_wmm)(stwuct ath10k *aw,
					    const stwuct wmi_wmm_pawams_aww_awg *awg);
	stwuct sk_buff *(*gen_wequest_stats)(stwuct ath10k *aw, u32 stats_mask);
	stwuct sk_buff *(*gen_wequest_peew_stats_info)(stwuct ath10k *aw,
						       u32 vdev_id,
						       enum
						       wmi_peew_stats_info_wequest_type
						       type,
						       u8 *addw,
						       u32 weset);
	stwuct sk_buff *(*gen_fowce_fw_hang)(stwuct ath10k *aw,
					     enum wmi_fowce_fw_hang_type type,
					     u32 deway_ms);
	stwuct sk_buff *(*gen_mgmt_tx)(stwuct ath10k *aw, stwuct sk_buff *skb);
	stwuct sk_buff *(*gen_mgmt_tx_send)(stwuct ath10k *aw,
					    stwuct sk_buff *skb,
					    dma_addw_t paddw);
	int (*cweanup_mgmt_tx_send)(stwuct ath10k *aw, stwuct sk_buff *msdu);
	stwuct sk_buff *(*gen_dbgwog_cfg)(stwuct ath10k *aw, u64 moduwe_enabwe,
					  u32 wog_wevew);
	stwuct sk_buff *(*gen_pktwog_enabwe)(stwuct ath10k *aw, u32 fiwtew);
	stwuct sk_buff *(*gen_pktwog_disabwe)(stwuct ath10k *aw);
	stwuct sk_buff *(*gen_pdev_set_quiet_mode)(stwuct ath10k *aw,
						   u32 pewiod, u32 duwation,
						   u32 next_offset,
						   u32 enabwed);
	stwuct sk_buff *(*gen_pdev_get_tempewatuwe)(stwuct ath10k *aw);
	stwuct sk_buff *(*gen_addba_cweaw_wesp)(stwuct ath10k *aw, u32 vdev_id,
						const u8 *mac);
	stwuct sk_buff *(*gen_addba_send)(stwuct ath10k *aw, u32 vdev_id,
					  const u8 *mac, u32 tid, u32 buf_size);
	stwuct sk_buff *(*gen_addba_set_wesp)(stwuct ath10k *aw, u32 vdev_id,
					      const u8 *mac, u32 tid,
					      u32 status);
	stwuct sk_buff *(*gen_dewba_send)(stwuct ath10k *aw, u32 vdev_id,
					  const u8 *mac, u32 tid, u32 initiatow,
					  u32 weason);
	stwuct sk_buff *(*gen_bcn_tmpw)(stwuct ath10k *aw, u32 vdev_id,
					u32 tim_ie_offset, stwuct sk_buff *bcn,
					u32 pwb_caps, u32 pwb_ewp,
					void *pwb_ies, size_t pwb_ies_wen);
	stwuct sk_buff *(*gen_pwb_tmpw)(stwuct ath10k *aw, u32 vdev_id,
					stwuct sk_buff *bcn);
	stwuct sk_buff *(*gen_p2p_go_bcn_ie)(stwuct ath10k *aw, u32 vdev_id,
					     const u8 *p2p_ie);
	stwuct sk_buff *(*gen_vdev_sta_uapsd)(stwuct ath10k *aw, u32 vdev_id,
					      const u8 peew_addw[ETH_AWEN],
					      const stwuct wmi_sta_uapsd_auto_twig_awg *awgs,
					      u32 num_ac);
	stwuct sk_buff *(*gen_sta_keepawive)(stwuct ath10k *aw,
					     const stwuct wmi_sta_keepawive_awg *awg);
	stwuct sk_buff *(*gen_wow_enabwe)(stwuct ath10k *aw);
	stwuct sk_buff *(*gen_wow_add_wakeup_event)(stwuct ath10k *aw, u32 vdev_id,
						    enum wmi_wow_wakeup_event event,
						    u32 enabwe);
	stwuct sk_buff *(*gen_wow_host_wakeup_ind)(stwuct ath10k *aw);
	stwuct sk_buff *(*gen_wow_add_pattewn)(stwuct ath10k *aw, u32 vdev_id,
					       u32 pattewn_id,
					       const u8 *pattewn,
					       const u8 *mask,
					       int pattewn_wen,
					       int pattewn_offset);
	stwuct sk_buff *(*gen_wow_dew_pattewn)(stwuct ath10k *aw, u32 vdev_id,
					       u32 pattewn_id);
	stwuct sk_buff *(*gen_update_fw_tdws_state)(stwuct ath10k *aw,
						    u32 vdev_id,
						    enum wmi_tdws_state state);
	stwuct sk_buff *(*gen_tdws_peew_update)(stwuct ath10k *aw,
						const stwuct wmi_tdws_peew_update_cmd_awg *awg,
						const stwuct wmi_tdws_peew_capab_awg *cap,
						const stwuct wmi_channew_awg *chan);
	stwuct sk_buff *(*gen_wadaw_found)
			(stwuct ath10k *aw,
			 const stwuct ath10k_wadaw_found_info *awg);
	stwuct sk_buff *(*gen_adaptive_qcs)(stwuct ath10k *aw, boow enabwe);
	stwuct sk_buff *(*gen_pdev_get_tpc_config)(stwuct ath10k *aw,
						   u32 pawam);
	void (*fw_stats_fiww)(stwuct ath10k *aw,
			      stwuct ath10k_fw_stats *fw_stats,
			      chaw *buf);
	stwuct sk_buff *(*gen_pdev_enabwe_adaptive_cca)(stwuct ath10k *aw,
							u8 enabwe,
							u32 detect_wevew,
							u32 detect_mawgin);
	stwuct sk_buff *(*ext_wesouwce_config)(stwuct ath10k *aw,
					       enum wmi_host_pwatfowm_type type,
					       u32 fw_featuwe_bitmap);
	int (*get_vdev_subtype)(stwuct ath10k *aw,
				enum wmi_vdev_subtype subtype);
	stwuct sk_buff *(*gen_wow_config_pno)(stwuct ath10k *aw,
					      u32 vdev_id,
					      stwuct wmi_pno_scan_weq *pno_scan);
	stwuct sk_buff *(*gen_pdev_bss_chan_info_weq)
					(stwuct ath10k *aw,
					 enum wmi_bss_suwvey_weq_type type);
	stwuct sk_buff *(*gen_echo)(stwuct ath10k *aw, u32 vawue);
	stwuct sk_buff *(*gen_pdev_get_tpc_tabwe_cmdid)(stwuct ath10k *aw,
							u32 pawam);
	stwuct sk_buff *(*gen_bb_timing)
			(stwuct ath10k *aw,
			 const stwuct wmi_bb_timing_cfg_awg *awg);
	stwuct sk_buff *(*gen_pew_peew_pew_tid_cfg)(stwuct ath10k *aw,
						    const stwuct wmi_pew_peew_pew_tid_cfg_awg *awg);

};

int ath10k_wmi_cmd_send(stwuct ath10k *aw, stwuct sk_buff *skb, u32 cmd_id);

static inwine int
ath10k_wmi_wx(stwuct ath10k *aw, stwuct sk_buff *skb)
{
	if (WAWN_ON_ONCE(!aw->wmi.ops->wx))
		wetuwn -EOPNOTSUPP;

	aw->wmi.ops->wx(aw, skb);
	wetuwn 0;
}

static inwine int
ath10k_wmi_map_svc(stwuct ath10k *aw, const __we32 *in, unsigned wong *out,
		   size_t wen)
{
	if (!aw->wmi.ops->map_svc)
		wetuwn -EOPNOTSUPP;

	aw->wmi.ops->map_svc(in, out, wen);
	wetuwn 0;
}

static inwine int
ath10k_wmi_map_svc_ext(stwuct ath10k *aw, const __we32 *in, unsigned wong *out,
		       size_t wen)
{
	if (!aw->wmi.ops->map_svc_ext)
		wetuwn -EOPNOTSUPP;

	aw->wmi.ops->map_svc_ext(in, out, wen);
	wetuwn 0;
}

static inwine int
ath10k_wmi_puww_scan(stwuct ath10k *aw, stwuct sk_buff *skb,
		     stwuct wmi_scan_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_scan)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_scan(aw, skb, awg);
}

static inwine int
ath10k_wmi_puww_mgmt_tx_compw(stwuct ath10k *aw, stwuct sk_buff *skb,
			      stwuct wmi_twv_mgmt_tx_compw_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_mgmt_tx_compw)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_mgmt_tx_compw(aw, skb, awg);
}

static inwine int
ath10k_wmi_puww_mgmt_tx_bundwe_compw(stwuct ath10k *aw, stwuct sk_buff *skb,
				     stwuct wmi_twv_mgmt_tx_bundwe_compw_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_mgmt_tx_bundwe_compw)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_mgmt_tx_bundwe_compw(aw, skb, awg);
}

static inwine int
ath10k_wmi_puww_mgmt_wx(stwuct ath10k *aw, stwuct sk_buff *skb,
			stwuct wmi_mgmt_wx_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_mgmt_wx)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_mgmt_wx(aw, skb, awg);
}

static inwine int
ath10k_wmi_puww_ch_info(stwuct ath10k *aw, stwuct sk_buff *skb,
			stwuct wmi_ch_info_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_ch_info)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_ch_info(aw, skb, awg);
}

static inwine int
ath10k_wmi_puww_vdev_stawt(stwuct ath10k *aw, stwuct sk_buff *skb,
			   stwuct wmi_vdev_stawt_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_vdev_stawt)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_vdev_stawt(aw, skb, awg);
}

static inwine int
ath10k_wmi_puww_peew_kick(stwuct ath10k *aw, stwuct sk_buff *skb,
			  stwuct wmi_peew_kick_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_peew_kick)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_peew_kick(aw, skb, awg);
}

static inwine int
ath10k_wmi_puww_swba(stwuct ath10k *aw, stwuct sk_buff *skb,
		     stwuct wmi_swba_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_swba)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_swba(aw, skb, awg);
}

static inwine int
ath10k_wmi_puww_phyeww_hdw(stwuct ath10k *aw, stwuct sk_buff *skb,
			   stwuct wmi_phyeww_hdw_awg *awg)
{
	if (!aw->wmi.ops->puww_phyeww_hdw)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_phyeww_hdw(aw, skb, awg);
}

static inwine int
ath10k_wmi_puww_phyeww(stwuct ath10k *aw, const void *phyeww_buf,
		       int weft_wen, stwuct wmi_phyeww_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_phyeww)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_phyeww(aw, phyeww_buf, weft_wen, awg);
}

static inwine int
ath10k_wmi_puww_svc_wdy(stwuct ath10k *aw, stwuct sk_buff *skb,
			stwuct wmi_svc_wdy_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_svc_wdy)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_svc_wdy(aw, skb, awg);
}

static inwine int
ath10k_wmi_puww_wdy(stwuct ath10k *aw, stwuct sk_buff *skb,
		    stwuct wmi_wdy_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_wdy)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_wdy(aw, skb, awg);
}

static inwine int
ath10k_wmi_puww_svc_avaiw(stwuct ath10k *aw, stwuct sk_buff *skb,
			  stwuct wmi_svc_avaiw_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_svc_avaiw)
		wetuwn -EOPNOTSUPP;
	wetuwn aw->wmi.ops->puww_svc_avaiw(aw, skb, awg);
}

static inwine int
ath10k_wmi_puww_fw_stats(stwuct ath10k *aw, stwuct sk_buff *skb,
			 stwuct ath10k_fw_stats *stats)
{
	if (!aw->wmi.ops->puww_fw_stats)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_fw_stats(aw, skb, stats);
}

static inwine int
ath10k_wmi_puww_woam_ev(stwuct ath10k *aw, stwuct sk_buff *skb,
			stwuct wmi_woam_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_woam_ev)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_woam_ev(aw, skb, awg);
}

static inwine int
ath10k_wmi_puww_wow_event(stwuct ath10k *aw, stwuct sk_buff *skb,
			  stwuct wmi_wow_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_wow_event)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_wow_event(aw, skb, awg);
}

static inwine int
ath10k_wmi_puww_echo_ev(stwuct ath10k *aw, stwuct sk_buff *skb,
			stwuct wmi_echo_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_echo_ev)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_echo_ev(aw, skb, awg);
}

static inwine int
ath10k_wmi_puww_dfs_status(stwuct ath10k *aw, stwuct sk_buff *skb,
			   stwuct wmi_dfs_status_ev_awg *awg)
{
	if (!aw->wmi.ops->puww_dfs_status_ev)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->puww_dfs_status_ev(aw, skb, awg);
}

static inwine enum wmi_txbf_conf
ath10k_wmi_get_txbf_conf_scheme(stwuct ath10k *aw)
{
	if (!aw->wmi.ops->get_txbf_conf_scheme)
		wetuwn WMI_TXBF_CONF_UNSUPPOWTED;

	wetuwn aw->wmi.ops->get_txbf_conf_scheme(aw);
}

static inwine int
ath10k_wmi_cweanup_mgmt_tx_send(stwuct ath10k *aw, stwuct sk_buff *msdu)
{
	if (!aw->wmi.ops->cweanup_mgmt_tx_send)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->cweanup_mgmt_tx_send(aw, msdu);
}

static inwine int
ath10k_wmi_mgmt_tx_send(stwuct ath10k *aw, stwuct sk_buff *msdu,
			dma_addw_t paddw)
{
	stwuct sk_buff *skb;
	int wet;

	if (!aw->wmi.ops->gen_mgmt_tx_send)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_mgmt_tx_send(aw, msdu, paddw);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wet = ath10k_wmi_cmd_send(aw, skb,
				  aw->wmi.cmd->mgmt_tx_send_cmdid);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static inwine int
ath10k_wmi_mgmt_tx(stwuct ath10k *aw, stwuct sk_buff *msdu)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(msdu);
	stwuct sk_buff *skb;
	int wet;

	if (!aw->wmi.ops->gen_mgmt_tx)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_mgmt_tx(aw, msdu);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wet = ath10k_wmi_cmd_send(aw, skb,
				  aw->wmi.cmd->mgmt_tx_cmdid);
	if (wet)
		wetuwn wet;

	/* FIXME Thewe's no ACK event fow Management Tx. This pwobabwy
	 * shouwdn't be cawwed hewe eithew.
	 */
	info->fwags |= IEEE80211_TX_STAT_ACK;
	ieee80211_tx_status_iwqsafe(aw->hw, msdu);

	wetuwn 0;
}

static inwine int
ath10k_wmi_pdev_set_wegdomain(stwuct ath10k *aw, u16 wd, u16 wd2g, u16 wd5g,
			      u16 ctw2g, u16 ctw5g,
			      enum wmi_dfs_wegion dfs_weg)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_pdev_set_wd)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_pdev_set_wd(aw, wd, wd2g, wd5g, ctw2g, ctw5g,
					   dfs_weg);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->pdev_set_wegdomain_cmdid);
}

static inwine int
ath10k_wmi_pdev_set_base_macaddw(stwuct ath10k *aw, const u8 macaddw[ETH_AWEN])
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_pdev_set_base_macaddw)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_pdev_set_base_macaddw(aw, macaddw);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->pdev_set_base_macaddw_cmdid);
}

static inwine int
ath10k_wmi_pdev_suspend_tawget(stwuct ath10k *aw, u32 suspend_opt)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_pdev_suspend)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_pdev_suspend(aw, suspend_opt);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->pdev_suspend_cmdid);
}

static inwine int
ath10k_wmi_pdev_wesume_tawget(stwuct ath10k *aw)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_pdev_wesume)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_pdev_wesume(aw);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->pdev_wesume_cmdid);
}

static inwine int
ath10k_wmi_pdev_set_pawam(stwuct ath10k *aw, u32 id, u32 vawue)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_pdev_set_pawam)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_pdev_set_pawam(aw, id, vawue);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->pdev_set_pawam_cmdid);
}

static inwine int
ath10k_wmi_cmd_init(stwuct ath10k *aw)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_init)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_init(aw);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->init_cmdid);
}

static inwine int
ath10k_wmi_stawt_scan(stwuct ath10k *aw,
		      const stwuct wmi_stawt_scan_awg *awg)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_stawt_scan)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_stawt_scan(aw, awg);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->stawt_scan_cmdid);
}

static inwine int
ath10k_wmi_stop_scan(stwuct ath10k *aw, const stwuct wmi_stop_scan_awg *awg)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_stop_scan)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_stop_scan(aw, awg);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->stop_scan_cmdid);
}

static inwine int
ath10k_wmi_vdev_cweate(stwuct ath10k *aw, u32 vdev_id,
		       enum wmi_vdev_type type,
		       enum wmi_vdev_subtype subtype,
		       const u8 macaddw[ETH_AWEN])
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_vdev_cweate)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_vdev_cweate(aw, vdev_id, type, subtype, macaddw);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->vdev_cweate_cmdid);
}

static inwine int
ath10k_wmi_vdev_dewete(stwuct ath10k *aw, u32 vdev_id)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_vdev_dewete)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_vdev_dewete(aw, vdev_id);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->vdev_dewete_cmdid);
}

static inwine int
ath10k_wmi_vdev_stawt(stwuct ath10k *aw,
		      const stwuct wmi_vdev_stawt_wequest_awg *awg)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_vdev_stawt)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_vdev_stawt(aw, awg, fawse);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->vdev_stawt_wequest_cmdid);
}

static inwine int
ath10k_wmi_vdev_westawt(stwuct ath10k *aw,
			const stwuct wmi_vdev_stawt_wequest_awg *awg)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_vdev_stawt)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_vdev_stawt(aw, awg, twue);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->vdev_westawt_wequest_cmdid);
}

static inwine int
ath10k_wmi_vdev_stop(stwuct ath10k *aw, u32 vdev_id)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_vdev_stop)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_vdev_stop(aw, vdev_id);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->vdev_stop_cmdid);
}

static inwine int
ath10k_wmi_vdev_up(stwuct ath10k *aw, u32 vdev_id, u32 aid, const u8 *bssid)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_vdev_up)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_vdev_up(aw, vdev_id, aid, bssid);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->vdev_up_cmdid);
}

static inwine int
ath10k_wmi_vdev_down(stwuct ath10k *aw, u32 vdev_id)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_vdev_down)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_vdev_down(aw, vdev_id);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->vdev_down_cmdid);
}

static inwine int
ath10k_wmi_vdev_set_pawam(stwuct ath10k *aw, u32 vdev_id, u32 pawam_id,
			  u32 pawam_vawue)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_vdev_set_pawam)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_vdev_set_pawam(aw, vdev_id, pawam_id,
					      pawam_vawue);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->vdev_set_pawam_cmdid);
}

static inwine int
ath10k_wmi_vdev_instaww_key(stwuct ath10k *aw,
			    const stwuct wmi_vdev_instaww_key_awg *awg)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_vdev_instaww_key)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_vdev_instaww_key(aw, awg);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->vdev_instaww_key_cmdid);
}

static inwine int
ath10k_wmi_vdev_spectwaw_conf(stwuct ath10k *aw,
			      const stwuct wmi_vdev_spectwaw_conf_awg *awg)
{
	stwuct sk_buff *skb;
	u32 cmd_id;

	if (!aw->wmi.ops->gen_vdev_spectwaw_conf)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_vdev_spectwaw_conf(aw, awg);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	cmd_id = aw->wmi.cmd->vdev_spectwaw_scan_configuwe_cmdid;
	wetuwn ath10k_wmi_cmd_send(aw, skb, cmd_id);
}

static inwine int
ath10k_wmi_vdev_spectwaw_enabwe(stwuct ath10k *aw, u32 vdev_id, u32 twiggew,
				u32 enabwe)
{
	stwuct sk_buff *skb;
	u32 cmd_id;

	if (!aw->wmi.ops->gen_vdev_spectwaw_enabwe)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_vdev_spectwaw_enabwe(aw, vdev_id, twiggew,
						    enabwe);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	cmd_id = aw->wmi.cmd->vdev_spectwaw_scan_enabwe_cmdid;
	wetuwn ath10k_wmi_cmd_send(aw, skb, cmd_id);
}

static inwine int
ath10k_wmi_vdev_sta_uapsd(stwuct ath10k *aw, u32 vdev_id,
			  const u8 peew_addw[ETH_AWEN],
			  const stwuct wmi_sta_uapsd_auto_twig_awg *awgs,
			  u32 num_ac)
{
	stwuct sk_buff *skb;
	u32 cmd_id;

	if (!aw->wmi.ops->gen_vdev_sta_uapsd)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_vdev_sta_uapsd(aw, vdev_id, peew_addw, awgs,
					      num_ac);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	cmd_id = aw->wmi.cmd->sta_uapsd_auto_twig_cmdid;
	wetuwn ath10k_wmi_cmd_send(aw, skb, cmd_id);
}

static inwine int
ath10k_wmi_vdev_wmm_conf(stwuct ath10k *aw, u32 vdev_id,
			 const stwuct wmi_wmm_pawams_aww_awg *awg)
{
	stwuct sk_buff *skb;
	u32 cmd_id;

	skb = aw->wmi.ops->gen_vdev_wmm_conf(aw, vdev_id, awg);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	cmd_id = aw->wmi.cmd->vdev_set_wmm_pawams_cmdid;
	wetuwn ath10k_wmi_cmd_send(aw, skb, cmd_id);
}

static inwine int
ath10k_wmi_peew_cweate(stwuct ath10k *aw, u32 vdev_id,
		       const u8 peew_addw[ETH_AWEN],
		       enum wmi_peew_type peew_type)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_peew_cweate)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_peew_cweate(aw, vdev_id, peew_addw, peew_type);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->peew_cweate_cmdid);
}

static inwine int
ath10k_wmi_peew_dewete(stwuct ath10k *aw, u32 vdev_id,
		       const u8 peew_addw[ETH_AWEN])
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_peew_dewete)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_peew_dewete(aw, vdev_id, peew_addw);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->peew_dewete_cmdid);
}

static inwine int
ath10k_wmi_peew_fwush(stwuct ath10k *aw, u32 vdev_id,
		      const u8 peew_addw[ETH_AWEN], u32 tid_bitmap)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_peew_fwush)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_peew_fwush(aw, vdev_id, peew_addw, tid_bitmap);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->peew_fwush_tids_cmdid);
}

static inwine int
ath10k_wmi_peew_set_pawam(stwuct ath10k *aw, u32 vdev_id, const u8 *peew_addw,
			  enum wmi_peew_pawam pawam_id, u32 pawam_vawue)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_peew_set_pawam)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_peew_set_pawam(aw, vdev_id, peew_addw, pawam_id,
					      pawam_vawue);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->peew_set_pawam_cmdid);
}

static inwine int
ath10k_wmi_set_psmode(stwuct ath10k *aw, u32 vdev_id,
		      enum wmi_sta_ps_mode psmode)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_set_psmode)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_set_psmode(aw, vdev_id, psmode);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->sta_powewsave_mode_cmdid);
}

static inwine int
ath10k_wmi_set_sta_ps_pawam(stwuct ath10k *aw, u32 vdev_id,
			    enum wmi_sta_powewsave_pawam pawam_id, u32 vawue)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_set_sta_ps)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_set_sta_ps(aw, vdev_id, pawam_id, vawue);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->sta_powewsave_pawam_cmdid);
}

static inwine int
ath10k_wmi_set_ap_ps_pawam(stwuct ath10k *aw, u32 vdev_id, const u8 *mac,
			   enum wmi_ap_ps_peew_pawam pawam_id, u32 vawue)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_set_ap_ps)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_set_ap_ps(aw, vdev_id, mac, pawam_id, vawue);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->ap_ps_peew_pawam_cmdid);
}

static inwine int
ath10k_wmi_scan_chan_wist(stwuct ath10k *aw,
			  const stwuct wmi_scan_chan_wist_awg *awg)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_scan_chan_wist)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_scan_chan_wist(aw, awg);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->scan_chan_wist_cmdid);
}

static inwine int
ath10k_wmi_scan_pwob_weq_oui(stwuct ath10k *aw, const u8 mac_addw[ETH_AWEN])
{
	stwuct sk_buff *skb;
	u32 pwob_weq_oui;

	pwob_weq_oui = (((u32)mac_addw[0]) << 16) |
		       (((u32)mac_addw[1]) << 8) | mac_addw[2];

	if (!aw->wmi.ops->gen_scan_pwob_weq_oui)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_scan_pwob_weq_oui(aw, pwob_weq_oui);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
			aw->wmi.cmd->scan_pwob_weq_oui_cmdid);
}

static inwine int
ath10k_wmi_peew_assoc(stwuct ath10k *aw,
		      const stwuct wmi_peew_assoc_compwete_awg *awg)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_peew_assoc)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_peew_assoc(aw, awg);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->peew_assoc_cmdid);
}

static inwine int
ath10k_wmi_beacon_send_wef_nowait(stwuct ath10k *aw, u32 vdev_id,
				  const void *bcn, size_t bcn_wen,
				  u32 bcn_paddw, boow dtim_zewo,
				  boow dewivew_cab)
{
	stwuct sk_buff *skb;
	int wet;

	if (!aw->wmi.ops->gen_beacon_dma)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_beacon_dma(aw, vdev_id, bcn, bcn_wen, bcn_paddw,
					  dtim_zewo, dewivew_cab);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wet = ath10k_wmi_cmd_send_nowait(aw, skb,
					 aw->wmi.cmd->pdev_send_bcn_cmdid);
	if (wet) {
		dev_kfwee_skb(skb);
		wetuwn wet;
	}

	wetuwn 0;
}

static inwine int
ath10k_wmi_pdev_set_wmm_pawams(stwuct ath10k *aw,
			       const stwuct wmi_wmm_pawams_aww_awg *awg)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_pdev_set_wmm)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_pdev_set_wmm(aw, awg);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->pdev_set_wmm_pawams_cmdid);
}

static inwine int
ath10k_wmi_wequest_stats(stwuct ath10k *aw, u32 stats_mask)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_wequest_stats)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_wequest_stats(aw, stats_mask);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->wequest_stats_cmdid);
}

static inwine int
ath10k_wmi_wequest_peew_stats_info(stwuct ath10k *aw,
				   u32 vdev_id,
				   enum wmi_peew_stats_info_wequest_type type,
				   u8 *addw,
				   u32 weset)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_wequest_peew_stats_info)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_wequest_peew_stats_info(aw,
						       vdev_id,
						       type,
						       addw,
						       weset);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->wequest_peew_stats_info_cmdid);
}

static inwine int
ath10k_wmi_fowce_fw_hang(stwuct ath10k *aw,
			 enum wmi_fowce_fw_hang_type type, u32 deway_ms)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_fowce_fw_hang)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_fowce_fw_hang(aw, type, deway_ms);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->fowce_fw_hang_cmdid);
}

static inwine int
ath10k_wmi_dbgwog_cfg(stwuct ath10k *aw, u64 moduwe_enabwe, u32 wog_wevew)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_dbgwog_cfg)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_dbgwog_cfg(aw, moduwe_enabwe, wog_wevew);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->dbgwog_cfg_cmdid);
}

static inwine int
ath10k_wmi_pdev_pktwog_enabwe(stwuct ath10k *aw, u32 fiwtew)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_pktwog_enabwe)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_pktwog_enabwe(aw, fiwtew);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->pdev_pktwog_enabwe_cmdid);
}

static inwine int
ath10k_wmi_pdev_pktwog_disabwe(stwuct ath10k *aw)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_pktwog_disabwe)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_pktwog_disabwe(aw);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->pdev_pktwog_disabwe_cmdid);
}

static inwine int
ath10k_wmi_pdev_set_quiet_mode(stwuct ath10k *aw, u32 pewiod, u32 duwation,
			       u32 next_offset, u32 enabwed)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_pdev_set_quiet_mode)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_pdev_set_quiet_mode(aw, pewiod, duwation,
						   next_offset, enabwed);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->pdev_set_quiet_mode_cmdid);
}

static inwine int
ath10k_wmi_pdev_get_tempewatuwe(stwuct ath10k *aw)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_pdev_get_tempewatuwe)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_pdev_get_tempewatuwe(aw);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->pdev_get_tempewatuwe_cmdid);
}

static inwine int
ath10k_wmi_addba_cweaw_wesp(stwuct ath10k *aw, u32 vdev_id, const u8 *mac)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_addba_cweaw_wesp)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_addba_cweaw_wesp(aw, vdev_id, mac);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->addba_cweaw_wesp_cmdid);
}

static inwine int
ath10k_wmi_addba_send(stwuct ath10k *aw, u32 vdev_id, const u8 *mac,
		      u32 tid, u32 buf_size)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_addba_send)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_addba_send(aw, vdev_id, mac, tid, buf_size);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->addba_send_cmdid);
}

static inwine int
ath10k_wmi_addba_set_wesp(stwuct ath10k *aw, u32 vdev_id, const u8 *mac,
			  u32 tid, u32 status)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_addba_set_wesp)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_addba_set_wesp(aw, vdev_id, mac, tid, status);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->addba_set_wesp_cmdid);
}

static inwine int
ath10k_wmi_dewba_send(stwuct ath10k *aw, u32 vdev_id, const u8 *mac,
		      u32 tid, u32 initiatow, u32 weason)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_dewba_send)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_dewba_send(aw, vdev_id, mac, tid, initiatow,
					  weason);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->dewba_send_cmdid);
}

static inwine int
ath10k_wmi_bcn_tmpw(stwuct ath10k *aw, u32 vdev_id, u32 tim_ie_offset,
		    stwuct sk_buff *bcn, u32 pwb_caps, u32 pwb_ewp,
		    void *pwb_ies, size_t pwb_ies_wen)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_bcn_tmpw)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_bcn_tmpw(aw, vdev_id, tim_ie_offset, bcn,
					pwb_caps, pwb_ewp, pwb_ies,
					pwb_ies_wen);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->bcn_tmpw_cmdid);
}

static inwine int
ath10k_wmi_pwb_tmpw(stwuct ath10k *aw, u32 vdev_id, stwuct sk_buff *pwb)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_pwb_tmpw)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_pwb_tmpw(aw, vdev_id, pwb);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->pwb_tmpw_cmdid);
}

static inwine int
ath10k_wmi_p2p_go_bcn_ie(stwuct ath10k *aw, u32 vdev_id, const u8 *p2p_ie)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_p2p_go_bcn_ie)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_p2p_go_bcn_ie(aw, vdev_id, p2p_ie);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->p2p_go_set_beacon_ie);
}

static inwine int
ath10k_wmi_sta_keepawive(stwuct ath10k *aw,
			 const stwuct wmi_sta_keepawive_awg *awg)
{
	stwuct sk_buff *skb;
	u32 cmd_id;

	if (!aw->wmi.ops->gen_sta_keepawive)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_sta_keepawive(aw, awg);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	cmd_id = aw->wmi.cmd->sta_keepawive_cmd;
	wetuwn ath10k_wmi_cmd_send(aw, skb, cmd_id);
}

static inwine int
ath10k_wmi_wow_enabwe(stwuct ath10k *aw)
{
	stwuct sk_buff *skb;
	u32 cmd_id;

	if (!aw->wmi.ops->gen_wow_enabwe)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_wow_enabwe(aw);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	cmd_id = aw->wmi.cmd->wow_enabwe_cmdid;
	wetuwn ath10k_wmi_cmd_send(aw, skb, cmd_id);
}

static inwine int
ath10k_wmi_wow_add_wakeup_event(stwuct ath10k *aw, u32 vdev_id,
				enum wmi_wow_wakeup_event event,
				u32 enabwe)
{
	stwuct sk_buff *skb;
	u32 cmd_id;

	if (!aw->wmi.ops->gen_wow_add_wakeup_event)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_wow_add_wakeup_event(aw, vdev_id, event, enabwe);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	cmd_id = aw->wmi.cmd->wow_enabwe_disabwe_wake_event_cmdid;
	wetuwn ath10k_wmi_cmd_send(aw, skb, cmd_id);
}

static inwine int
ath10k_wmi_wow_host_wakeup_ind(stwuct ath10k *aw)
{
	stwuct sk_buff *skb;
	u32 cmd_id;

	if (!aw->wmi.ops->gen_wow_host_wakeup_ind)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_wow_host_wakeup_ind(aw);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	cmd_id = aw->wmi.cmd->wow_hostwakeup_fwom_sweep_cmdid;
	wetuwn ath10k_wmi_cmd_send(aw, skb, cmd_id);
}

static inwine int
ath10k_wmi_wow_add_pattewn(stwuct ath10k *aw, u32 vdev_id, u32 pattewn_id,
			   const u8 *pattewn, const u8 *mask,
			   int pattewn_wen, int pattewn_offset)
{
	stwuct sk_buff *skb;
	u32 cmd_id;

	if (!aw->wmi.ops->gen_wow_add_pattewn)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_wow_add_pattewn(aw, vdev_id, pattewn_id,
					       pattewn, mask, pattewn_wen,
					       pattewn_offset);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	cmd_id = aw->wmi.cmd->wow_add_wake_pattewn_cmdid;
	wetuwn ath10k_wmi_cmd_send(aw, skb, cmd_id);
}

static inwine int
ath10k_wmi_wow_dew_pattewn(stwuct ath10k *aw, u32 vdev_id, u32 pattewn_id)
{
	stwuct sk_buff *skb;
	u32 cmd_id;

	if (!aw->wmi.ops->gen_wow_dew_pattewn)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_wow_dew_pattewn(aw, vdev_id, pattewn_id);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	cmd_id = aw->wmi.cmd->wow_dew_wake_pattewn_cmdid;
	wetuwn ath10k_wmi_cmd_send(aw, skb, cmd_id);
}

static inwine int
ath10k_wmi_wow_config_pno(stwuct ath10k *aw, u32 vdev_id,
			  stwuct wmi_pno_scan_weq  *pno_scan)
{
	stwuct sk_buff *skb;
	u32 cmd_id;

	if (!aw->wmi.ops->gen_wow_config_pno)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_wow_config_pno(aw, vdev_id, pno_scan);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	cmd_id = aw->wmi.cmd->netwowk_wist_offwoad_config_cmdid;
	wetuwn ath10k_wmi_cmd_send(aw, skb, cmd_id);
}

static inwine int
ath10k_wmi_update_fw_tdws_state(stwuct ath10k *aw, u32 vdev_id,
				enum wmi_tdws_state state)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_update_fw_tdws_state)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_update_fw_tdws_state(aw, vdev_id, state);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->tdws_set_state_cmdid);
}

static inwine int
ath10k_wmi_tdws_peew_update(stwuct ath10k *aw,
			    const stwuct wmi_tdws_peew_update_cmd_awg *awg,
			    const stwuct wmi_tdws_peew_capab_awg *cap,
			    const stwuct wmi_channew_awg *chan)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_tdws_peew_update)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_tdws_peew_update(aw, awg, cap, chan);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->tdws_peew_update_cmdid);
}

static inwine int
ath10k_wmi_adaptive_qcs(stwuct ath10k *aw, boow enabwe)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_adaptive_qcs)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_adaptive_qcs(aw, enabwe);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, aw->wmi.cmd->adaptive_qcs_cmdid);
}

static inwine int
ath10k_wmi_pdev_get_tpc_config(stwuct ath10k *aw, u32 pawam)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_pdev_get_tpc_config)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_pdev_get_tpc_config(aw, pawam);

	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->pdev_get_tpc_config_cmdid);
}

static inwine int
ath10k_wmi_fw_stats_fiww(stwuct ath10k *aw, stwuct ath10k_fw_stats *fw_stats,
			 chaw *buf)
{
	if (!aw->wmi.ops->fw_stats_fiww)
		wetuwn -EOPNOTSUPP;

	aw->wmi.ops->fw_stats_fiww(aw, fw_stats, buf);
	wetuwn 0;
}

static inwine int
ath10k_wmi_pdev_enabwe_adaptive_cca(stwuct ath10k *aw, u8 enabwe,
				    u32 detect_wevew, u32 detect_mawgin)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_pdev_enabwe_adaptive_cca)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_pdev_enabwe_adaptive_cca(aw, enabwe,
							detect_wevew,
							detect_mawgin);

	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->pdev_enabwe_adaptive_cca_cmdid);
}

static inwine int
ath10k_wmi_ext_wesouwce_config(stwuct ath10k *aw,
			       enum wmi_host_pwatfowm_type type,
			       u32 fw_featuwe_bitmap)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->ext_wesouwce_config)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->ext_wesouwce_config(aw, type,
					       fw_featuwe_bitmap);

	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->ext_wesouwce_cfg_cmdid);
}

static inwine int
ath10k_wmi_get_vdev_subtype(stwuct ath10k *aw, enum wmi_vdev_subtype subtype)
{
	if (!aw->wmi.ops->get_vdev_subtype)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->wmi.ops->get_vdev_subtype(aw, subtype);
}

static inwine int
ath10k_wmi_pdev_bss_chan_info_wequest(stwuct ath10k *aw,
				      enum wmi_bss_suwvey_weq_type type)
{
	stwuct ath10k_wmi *wmi = &aw->wmi;
	stwuct sk_buff *skb;

	if (!wmi->ops->gen_pdev_bss_chan_info_weq)
		wetuwn -EOPNOTSUPP;

	skb = wmi->ops->gen_pdev_bss_chan_info_weq(aw, type);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   wmi->cmd->pdev_bss_chan_info_wequest_cmdid);
}

static inwine int
ath10k_wmi_echo(stwuct ath10k *aw, u32 vawue)
{
	stwuct ath10k_wmi *wmi = &aw->wmi;
	stwuct sk_buff *skb;

	if (!wmi->ops->gen_echo)
		wetuwn -EOPNOTSUPP;

	skb = wmi->ops->gen_echo(aw, vawue);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb, wmi->cmd->echo_cmdid);
}

static inwine int
ath10k_wmi_pdev_get_tpc_tabwe_cmdid(stwuct ath10k *aw, u32 pawam)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_pdev_get_tpc_tabwe_cmdid)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_pdev_get_tpc_tabwe_cmdid(aw, pawam);

	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->pdev_get_tpc_tabwe_cmdid);
}

static inwine int
ath10k_wmi_wepowt_wadaw_found(stwuct ath10k *aw,
			      const stwuct ath10k_wadaw_found_info *awg)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_wadaw_found)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_wadaw_found(aw, awg);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->wadaw_found_cmdid);
}

static inwine int
ath10k_wmi_pdev_bb_timing(stwuct ath10k *aw,
			  const stwuct wmi_bb_timing_cfg_awg *awg)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_bb_timing)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_bb_timing(aw, awg);

	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->set_bb_timing_cmdid);
}

static inwine int
ath10k_wmi_set_pew_peew_pew_tid_cfg(stwuct ath10k *aw,
				    const stwuct wmi_pew_peew_pew_tid_cfg_awg *awg)
{
	stwuct sk_buff *skb;

	if (!aw->wmi.ops->gen_pew_peew_pew_tid_cfg)
		wetuwn -EOPNOTSUPP;

	skb = aw->wmi.ops->gen_pew_peew_pew_tid_cfg(aw, awg);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->pew_peew_pew_tid_config_cmdid);
}
#endif
