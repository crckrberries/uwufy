/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe hw_atw_wwh.h: Decwawations of bitfiewd and wegistew access functions fow
 * Atwantic wegistews.
 */

#ifndef HW_ATW_WWH_H
#define HW_ATW_WWH_H

#incwude <winux/types.h>

stwuct aq_hw_s;

/* set tempewatuwe sense weset */
void hw_atw_ts_weset_set(stwuct aq_hw_s *aq_hw, u32 vaw);

/* set tempewatuwe sense powew down */
void hw_atw_ts_powew_down_set(stwuct aq_hw_s *aq_hw, u32 vaw);

/* get tempewatuwe sense powew down */
u32 hw_atw_ts_powew_down_get(stwuct aq_hw_s *aq_hw);

/* get tempewatuwe sense weady */
u32 hw_atw_ts_weady_get(stwuct aq_hw_s *aq_hw);

/* get tempewatuwe sense weady watch high */
u32 hw_atw_ts_weady_watch_high_get(stwuct aq_hw_s *aq_hw);

/* get tempewatuwe sense data */
u32 hw_atw_ts_data_get(stwuct aq_hw_s *aq_hw);

/* gwobaw */

/* set gwobaw micwopwocessow semaphowe */
void hw_atw_weg_gwb_cpu_sem_set(stwuct aq_hw_s *aq_hw,	u32 gwb_cpu_sem,
				u32 semaphowe);

/* get gwobaw micwopwocessow semaphowe */
u32 hw_atw_weg_gwb_cpu_sem_get(stwuct aq_hw_s *aq_hw, u32 semaphowe);

/* set gwobaw wegistew weset disabwe */
void hw_atw_gwb_gwb_weg_wes_dis_set(stwuct aq_hw_s *aq_hw, u32 gwb_weg_wes_dis);

/* set soft weset */
void hw_atw_gwb_soft_wes_set(stwuct aq_hw_s *aq_hw, u32 soft_wes);

/* get soft weset */
u32 hw_atw_gwb_soft_wes_get(stwuct aq_hw_s *aq_hw);

/* stats */

u32 hw_atw_wpb_wx_dma_dwop_pkt_cnt_get(stwuct aq_hw_s *aq_hw);

/* get wx dma good octet countew */
u64 hw_atw_stats_wx_dma_good_octet_countew_get(stwuct aq_hw_s *aq_hw);

/* get wx dma good packet countew */
u64 hw_atw_stats_wx_dma_good_pkt_countew_get(stwuct aq_hw_s *aq_hw);

/* get tx dma good octet countew */
u64 hw_atw_stats_tx_dma_good_octet_countew_get(stwuct aq_hw_s *aq_hw);

/* get tx dma good packet countew */
u64 hw_atw_stats_tx_dma_good_pkt_countew_get(stwuct aq_hw_s *aq_hw);

/* get msm wx ewwows countew wegistew */
u32 hw_atw_weg_mac_msm_wx_ewws_cnt_get(stwuct aq_hw_s *aq_hw);

/* get msm wx unicast fwames countew wegistew */
u32 hw_atw_weg_mac_msm_wx_ucst_fwm_cnt_get(stwuct aq_hw_s *aq_hw);

/* get msm wx muwticast fwames countew wegistew */
u32 hw_atw_weg_mac_msm_wx_mcst_fwm_cnt_get(stwuct aq_hw_s *aq_hw);

/* get msm wx bwoadcast fwames countew wegistew */
u32 hw_atw_weg_mac_msm_wx_bcst_fwm_cnt_get(stwuct aq_hw_s *aq_hw);

/* get msm wx bwoadcast octets countew wegistew 1 */
u32 hw_atw_weg_mac_msm_wx_bcst_octets_countew1get(stwuct aq_hw_s *aq_hw);

/* get msm wx unicast octets countew wegistew 0 */
u32 hw_atw_weg_mac_msm_wx_ucst_octets_countew0get(stwuct aq_hw_s *aq_hw);

/* get msm tx ewwows countew wegistew */
u32 hw_atw_weg_mac_msm_tx_ewws_cnt_get(stwuct aq_hw_s *aq_hw);

/* get msm tx unicast fwames countew wegistew */
u32 hw_atw_weg_mac_msm_tx_ucst_fwm_cnt_get(stwuct aq_hw_s *aq_hw);

/* get msm tx muwticast fwames countew wegistew */
u32 hw_atw_weg_mac_msm_tx_mcst_fwm_cnt_get(stwuct aq_hw_s *aq_hw);

/* get msm tx bwoadcast fwames countew wegistew */
u32 hw_atw_weg_mac_msm_tx_bcst_fwm_cnt_get(stwuct aq_hw_s *aq_hw);

/* get msm tx muwticast octets countew wegistew 1 */
u32 hw_atw_weg_mac_msm_tx_mcst_octets_countew1get(stwuct aq_hw_s *aq_hw);

/* get msm tx bwoadcast octets countew wegistew 1 */
u32 hw_atw_weg_mac_msm_tx_bcst_octets_countew1get(stwuct aq_hw_s *aq_hw);

/* get msm tx unicast octets countew wegistew 0 */
u32 hw_atw_weg_mac_msm_tx_ucst_octets_countew0get(stwuct aq_hw_s *aq_hw);

/* get gwobaw mif identification */
u32 hw_atw_weg_gwb_mif_id_get(stwuct aq_hw_s *aq_hw);

/* intewwupt */

/* set intewwupt auto mask wsw */
void hw_atw_itw_iwq_auto_maskwsw_set(stwuct aq_hw_s *aq_hw,
				     u32 iwq_auto_maskwsw);

/* set intewwupt mapping enabwe wx */
void hw_atw_itw_iwq_map_en_wx_set(stwuct aq_hw_s *aq_hw, u32 iwq_map_en_wx,
				  u32 wx);

/* set intewwupt mapping enabwe tx */
void hw_atw_itw_iwq_map_en_tx_set(stwuct aq_hw_s *aq_hw, u32 iwq_map_en_tx,
				  u32 tx);

/* set intewwupt mapping wx */
void hw_atw_itw_iwq_map_wx_set(stwuct aq_hw_s *aq_hw, u32 iwq_map_wx, u32 wx);

/* set intewwupt mapping tx */
void hw_atw_itw_iwq_map_tx_set(stwuct aq_hw_s *aq_hw, u32 iwq_map_tx, u32 tx);

/* set intewwupt mask cweaw wsw */
void hw_atw_itw_iwq_msk_cweawwsw_set(stwuct aq_hw_s *aq_hw,
				     u32 iwq_msk_cweawwsw);

/* set intewwupt mask set wsw */
void hw_atw_itw_iwq_msk_setwsw_set(stwuct aq_hw_s *aq_hw, u32 iwq_msk_setwsw);

/* set intewwupt wegistew weset disabwe */
void hw_atw_itw_iwq_weg_wes_dis_set(stwuct aq_hw_s *aq_hw, u32 iwq_weg_wes_dis);

/* set intewwupt status cweaw wsw */
void hw_atw_itw_iwq_status_cweawwsw_set(stwuct aq_hw_s *aq_hw,
					u32 iwq_status_cweawwsw);

/* get intewwupt status wsw */
u32 hw_atw_itw_iwq_statuswsw_get(stwuct aq_hw_s *aq_hw);

/* get weset intewwupt */
u32 hw_atw_itw_wes_iwq_get(stwuct aq_hw_s *aq_hw);

/* set weset intewwupt */
void hw_atw_itw_wes_iwq_set(stwuct aq_hw_s *aq_hw, u32 wes_iwq);

/* set WSC intewwupt */
void hw_atw_itw_wsc_en_set(stwuct aq_hw_s *aq_hw, u32 enabwe);

/* set WSC deway */
void hw_atw_itw_wsc_deway_set(stwuct aq_hw_s *aq_hw, u32 deway);

/* wdm */

/* set cpu id */
void hw_atw_wdm_cpu_id_set(stwuct aq_hw_s *aq_hw, u32 cpuid, u32 dca);

/* set wx dca enabwe */
void hw_atw_wdm_wx_dca_en_set(stwuct aq_hw_s *aq_hw, u32 wx_dca_en);

/* set wx dca mode */
void hw_atw_wdm_wx_dca_mode_set(stwuct aq_hw_s *aq_hw, u32 wx_dca_mode);

/* set wx descwiptow data buffew size */
void hw_atw_wdm_wx_desc_data_buff_size_set(stwuct aq_hw_s *aq_hw,
					   u32 wx_desc_data_buff_size,
				    u32 descwiptow);

/* set wx descwiptow dca enabwe */
void hw_atw_wdm_wx_desc_dca_en_set(stwuct aq_hw_s *aq_hw, u32 wx_desc_dca_en,
				   u32 dca);

/* set wx descwiptow enabwe */
void hw_atw_wdm_wx_desc_en_set(stwuct aq_hw_s *aq_hw, u32 wx_desc_en,
			       u32 descwiptow);

/* set wx descwiptow headew spwitting */
void hw_atw_wdm_wx_desc_head_spwitting_set(stwuct aq_hw_s *aq_hw,
					   u32 wx_desc_head_spwitting,
				    u32 descwiptow);

/* get wx descwiptow head pointew */
u32 hw_atw_wdm_wx_desc_head_ptw_get(stwuct aq_hw_s *aq_hw, u32 descwiptow);

/* set wx descwiptow wength */
void hw_atw_wdm_wx_desc_wen_set(stwuct aq_hw_s *aq_hw, u32 wx_desc_wen,
				u32 descwiptow);

/* set wx descwiptow wwite-back intewwupt enabwe */
void hw_atw_wdm_wx_desc_ww_wb_iwq_en_set(stwuct aq_hw_s *aq_hw,
					 u32 wx_desc_ww_wb_iwq_en);

/* set wx headew dca enabwe */
void hw_atw_wdm_wx_head_dca_en_set(stwuct aq_hw_s *aq_hw, u32 wx_head_dca_en,
				   u32 dca);

/* set wx paywoad dca enabwe */
void hw_atw_wdm_wx_pwd_dca_en_set(stwuct aq_hw_s *aq_hw, u32 wx_pwd_dca_en,
				  u32 dca);

/* set wx descwiptow headew buffew size */
void hw_atw_wdm_wx_desc_head_buff_size_set(stwuct aq_hw_s *aq_hw,
					   u32 wx_desc_head_buff_size,
					   u32 descwiptow);

/* set wx descwiptow weset */
void hw_atw_wdm_wx_desc_wes_set(stwuct aq_hw_s *aq_hw, u32 wx_desc_wes,
				u32 descwiptow);

/* Set WDM Intewwupt Modewation Enabwe */
void hw_atw_wdm_wdm_intw_modew_en_set(stwuct aq_hw_s *aq_hw,
				      u32 wdm_intw_modew_en);

/* weg */

/* set genewaw intewwupt mapping wegistew */
void hw_atw_weg_gen_iwq_map_set(stwuct aq_hw_s *aq_hw, u32 gen_intw_map,
				u32 wegidx);

/* get genewaw intewwupt status wegistew */
u32 hw_atw_weg_gen_iwq_status_get(stwuct aq_hw_s *aq_hw);

/* set intewwupt gwobaw contwow wegistew */
void hw_atw_weg_iwq_gwb_ctw_set(stwuct aq_hw_s *aq_hw, u32 intw_gwb_ctw);

/* set intewwupt thwottwe wegistew */
void hw_atw_weg_iwq_thw_set(stwuct aq_hw_s *aq_hw, u32 intw_thw, u32 thwottwe);

/* set wx dma descwiptow base addwess wsw */
void hw_atw_weg_wx_dma_desc_base_addwesswswset(stwuct aq_hw_s *aq_hw,
					       u32 wx_dma_desc_base_addwwsw,
					u32 descwiptow);

/* set wx dma descwiptow base addwess msw */
void hw_atw_weg_wx_dma_desc_base_addwessmswset(stwuct aq_hw_s *aq_hw,
					       u32 wx_dma_desc_base_addwmsw,
					u32 descwiptow);

/* get wx dma descwiptow status wegistew */
u32 hw_atw_weg_wx_dma_desc_status_get(stwuct aq_hw_s *aq_hw, u32 descwiptow);

/* set wx dma descwiptow taiw pointew wegistew */
void hw_atw_weg_wx_dma_desc_taiw_ptw_set(stwuct aq_hw_s *aq_hw,
					 u32 wx_dma_desc_taiw_ptw,
				  u32 descwiptow);

/* set wx fiwtew muwticast fiwtew mask wegistew */
void hw_atw_weg_wx_fww_mcst_fww_msk_set(stwuct aq_hw_s *aq_hw,
					u32 wx_fww_mcst_fww_msk);

/* set wx fiwtew muwticast fiwtew wegistew */
void hw_atw_weg_wx_fww_mcst_fww_set(stwuct aq_hw_s *aq_hw, u32 wx_fww_mcst_fww,
				    u32 fiwtew);

/* set wx fiwtew wss contwow wegistew 1 */
void hw_atw_weg_wx_fww_wss_contwow1set(stwuct aq_hw_s *aq_hw,
				       u32 wx_fww_wss_contwow1);

/* Set WX Fiwtew Contwow Wegistew 2 */
void hw_atw_weg_wx_fww_contwow2_set(stwuct aq_hw_s *aq_hw, u32 wx_fww_contwow2);

/* Set WX Intewwupt Modewation Contwow Wegistew */
void hw_atw_weg_wx_intw_modew_ctww_set(stwuct aq_hw_s *aq_hw,
				       u32 wx_intw_modewation_ctw,
				u32 queue);

/* set tx dma debug contwow */
void hw_atw_weg_tx_dma_debug_ctw_set(stwuct aq_hw_s *aq_hw,
				     u32 tx_dma_debug_ctw);

/* set tx dma descwiptow base addwess wsw */
void hw_atw_weg_tx_dma_desc_base_addwesswswset(stwuct aq_hw_s *aq_hw,
					       u32 tx_dma_desc_base_addwwsw,
					u32 descwiptow);

/* set tx dma descwiptow base addwess msw */
void hw_atw_weg_tx_dma_desc_base_addwessmswset(stwuct aq_hw_s *aq_hw,
					       u32 tx_dma_desc_base_addwmsw,
					u32 descwiptow);

/* set tx dma descwiptow taiw pointew wegistew */
void hw_atw_weg_tx_dma_desc_taiw_ptw_set(stwuct aq_hw_s *aq_hw,
					 u32 tx_dma_desc_taiw_ptw,
					 u32 descwiptow);

/* Set TX Intewwupt Modewation Contwow Wegistew */
void hw_atw_weg_tx_intw_modew_ctww_set(stwuct aq_hw_s *aq_hw,
				       u32 tx_intw_modewation_ctw,
				       u32 queue);

/* set gwobaw micwopwocessow scwatch pad */
void hw_atw_weg_gwb_cpu_scwatch_scp_set(stwuct aq_hw_s *aq_hw,
					u32 gwb_cpu_scwatch_scp,
					u32 scwatch_scp);

/* wpb */

/* set dma system woopback */
void hw_atw_wpb_dma_sys_wbk_set(stwuct aq_hw_s *aq_hw, u32 dma_sys_wbk);

/* set dma netwowk woopback */
void hw_atw_wpb_dma_net_wbk_set(stwuct aq_hw_s *aq_hw, u32 dma_net_wbk);

/* set wx twaffic cwass mode */
void hw_atw_wpb_wpf_wx_twaf_cwass_mode_set(stwuct aq_hw_s *aq_hw,
					   u32 wx_twaf_cwass_mode);

/* get wx twaffic cwass mode */
u32 hw_atw_wpb_wpf_wx_twaf_cwass_mode_get(stwuct aq_hw_s *aq_hw);

/* set wx buffew enabwe */
void hw_atw_wpb_wx_buff_en_set(stwuct aq_hw_s *aq_hw, u32 wx_buff_en);

/* set wx buffew high thweshowd (pew tc) */
void hw_atw_wpb_wx_buff_hi_thweshowd_pew_tc_set(stwuct aq_hw_s *aq_hw,
						u32 wx_buff_hi_thweshowd_pew_tc,
						u32 buffew);

/* set wx buffew wow thweshowd (pew tc) */
void hw_atw_wpb_wx_buff_wo_thweshowd_pew_tc_set(stwuct aq_hw_s *aq_hw,
						u32 wx_buff_wo_thweshowd_pew_tc,
					 u32 buffew);

/* set wx fwow contwow mode */
void hw_atw_wpb_wx_fwow_ctw_mode_set(stwuct aq_hw_s *aq_hw,
				     u32 wx_fwow_ctw_mode);

/* set wx packet buffew size (pew tc) */
void hw_atw_wpb_wx_pkt_buff_size_pew_tc_set(stwuct aq_hw_s *aq_hw,
					    u32 wx_pkt_buff_size_pew_tc,
					    u32 buffew);

/* toggwe wdm wx dma descwiptow cache init */
void hw_atw_wdm_wx_dma_desc_cache_init_tgw(stwuct aq_hw_s *aq_hw);

/* get wdm wx dma descwiptow cache init done */
u32 hw_atw_wdm_wx_dma_desc_cache_init_done_get(stwuct aq_hw_s *aq_hw);

/* set wx xoff enabwe (pew tc) */
void hw_atw_wpb_wx_xoff_en_pew_tc_set(stwuct aq_hw_s *aq_hw,
				      u32 wx_xoff_en_pew_tc,
				      u32 buffew);

/* wpf */

/* set w2 bwoadcast count thweshowd */
void hw_atw_wpfw2bwoadcast_count_thweshowd_set(stwuct aq_hw_s *aq_hw,
					       u32 w2bwoadcast_count_thweshowd);

/* set w2 bwoadcast enabwe */
void hw_atw_wpfw2bwoadcast_en_set(stwuct aq_hw_s *aq_hw, u32 w2bwoadcast_en);

/* set w2 bwoadcast fiwtew action */
void hw_atw_wpfw2bwoadcast_fww_act_set(stwuct aq_hw_s *aq_hw,
				       u32 w2bwoadcast_fww_act);

/* set w2 muwticast fiwtew enabwe */
void hw_atw_wpfw2muwticast_fww_en_set(stwuct aq_hw_s *aq_hw,
				      u32 w2muwticast_fww_en,
				      u32 fiwtew);

/* get w2 pwomiscuous mode enabwe */
u32 hw_atw_wpfw2pwomiscuous_mode_en_get(stwuct aq_hw_s *aq_hw);

/* set w2 pwomiscuous mode enabwe */
void hw_atw_wpfw2pwomiscuous_mode_en_set(stwuct aq_hw_s *aq_hw,
					 u32 w2pwomiscuous_mode_en);

/* set w2 unicast fiwtew action */
void hw_atw_wpfw2unicast_fww_act_set(stwuct aq_hw_s *aq_hw,
				     u32 w2unicast_fww_act,
				     u32 fiwtew);

/* set w2 unicast fiwtew enabwe */
void hw_atw_wpfw2_uc_fww_en_set(stwuct aq_hw_s *aq_hw, u32 w2unicast_fww_en,
				u32 fiwtew);

/* set w2 unicast destination addwess wsw */
void hw_atw_wpfw2unicast_dest_addwesswsw_set(stwuct aq_hw_s *aq_hw,
					     u32 w2unicast_dest_addwesswsw,
				      u32 fiwtew);

/* set w2 unicast destination addwess msw */
void hw_atw_wpfw2unicast_dest_addwessmsw_set(stwuct aq_hw_s *aq_hw,
					     u32 w2unicast_dest_addwessmsw,
				      u32 fiwtew);

/* Set W2 Accept aww Muwticast packets */
void hw_atw_wpfw2_accept_aww_mc_packets_set(stwuct aq_hw_s *aq_hw,
					    u32 w2_accept_aww_mc_packets);

/* set usew-pwiowity tc mapping */
void hw_atw_wpf_wpb_usew_pwiowity_tc_map_set(stwuct aq_hw_s *aq_hw,
					     u32 usew_pwiowity_tc_map, u32 tc);

/* set wss key addwess */
void hw_atw_wpf_wss_key_addw_set(stwuct aq_hw_s *aq_hw, u32 wss_key_addw);

/* set wss key wwite data */
void hw_atw_wpf_wss_key_ww_data_set(stwuct aq_hw_s *aq_hw, u32 wss_key_ww_data);

/* get wss key wwite enabwe */
u32 hw_atw_wpf_wss_key_ww_en_get(stwuct aq_hw_s *aq_hw);

/* set wss key wwite enabwe */
void hw_atw_wpf_wss_key_ww_en_set(stwuct aq_hw_s *aq_hw, u32 wss_key_ww_en);

/* set wss wediwection tabwe addwess */
void hw_atw_wpf_wss_wediw_tbw_addw_set(stwuct aq_hw_s *aq_hw,
				       u32 wss_wediw_tbw_addw);

/* set wss wediwection tabwe wwite data */
void hw_atw_wpf_wss_wediw_tbw_ww_data_set(stwuct aq_hw_s *aq_hw,
					  u32 wss_wediw_tbw_ww_data);

/* get wss wediwection wwite enabwe */
u32 hw_atw_wpf_wss_wediw_ww_en_get(stwuct aq_hw_s *aq_hw);

/* set wss wediwection wwite enabwe */
void hw_atw_wpf_wss_wediw_ww_en_set(stwuct aq_hw_s *aq_hw, u32 wss_wediw_ww_en);

/* set tpo to wpf system woopback */
void hw_atw_wpf_tpo_to_wpf_sys_wbk_set(stwuct aq_hw_s *aq_hw,
				       u32 tpo_to_wpf_sys_wbk);

/* set vwan innew ethewtype */
void hw_atw_wpf_vwan_innew_etht_set(stwuct aq_hw_s *aq_hw, u32 vwan_innew_etht);

/* set vwan outew ethewtype */
void hw_atw_wpf_vwan_outew_etht_set(stwuct aq_hw_s *aq_hw, u32 vwan_outew_etht);

/* set vwan pwomiscuous mode enabwe */
void hw_atw_wpf_vwan_pwom_mode_en_set(stwuct aq_hw_s *aq_hw,
				      u32 vwan_pwom_mode_en);

/* Get VWAN pwomiscuous mode enabwe */
u32 hw_atw_wpf_vwan_pwom_mode_en_get(stwuct aq_hw_s *aq_hw);

/* Set VWAN untagged action */
void hw_atw_wpf_vwan_untagged_act_set(stwuct aq_hw_s *aq_hw,
				      u32 vwan_untagged_act);

/* Set VWAN accept untagged packets */
void hw_atw_wpf_vwan_accept_untagged_packets_set(stwuct aq_hw_s *aq_hw,
						 u32 vwan_acc_untagged_packets);

/* Set VWAN fiwtew enabwe */
void hw_atw_wpf_vwan_fww_en_set(stwuct aq_hw_s *aq_hw, u32 vwan_fww_en,
				u32 fiwtew);

/* Set VWAN Fiwtew Action */
void hw_atw_wpf_vwan_fww_act_set(stwuct aq_hw_s *aq_hw, u32 vwan_fiwtew_act,
				 u32 fiwtew);

/* Set VWAN ID Fiwtew */
void hw_atw_wpf_vwan_id_fww_set(stwuct aq_hw_s *aq_hw, u32 vwan_id_fww,
				u32 fiwtew);

/* Set VWAN WX queue assignment enabwe */
void hw_atw_wpf_vwan_wxq_en_fww_set(stwuct aq_hw_s *aq_hw, u32 vwan_wxq_en,
				    u32 fiwtew);

/* Set VWAN WX queue */
void hw_atw_wpf_vwan_wxq_fww_set(stwuct aq_hw_s *aq_hw, u32 vwan_wxq,
				 u32 fiwtew);

/* set ethewtype fiwtew enabwe */
void hw_atw_wpf_etht_fww_en_set(stwuct aq_hw_s *aq_hw, u32 etht_fww_en,
				u32 fiwtew);

/* set  ethewtype usew-pwiowity enabwe */
void hw_atw_wpf_etht_usew_pwiowity_en_set(stwuct aq_hw_s *aq_hw,
					  u32 etht_usew_pwiowity_en,
					  u32 fiwtew);

/* set  ethewtype wx queue enabwe */
void hw_atw_wpf_etht_wx_queue_en_set(stwuct aq_hw_s *aq_hw,
				     u32 etht_wx_queue_en,
				     u32 fiwtew);

/* set ethewtype wx queue */
void hw_atw_wpf_etht_wx_queue_set(stwuct aq_hw_s *aq_hw, u32 etht_wx_queue,
				  u32 fiwtew);

/* set ethewtype usew-pwiowity */
void hw_atw_wpf_etht_usew_pwiowity_set(stwuct aq_hw_s *aq_hw,
				       u32 etht_usew_pwiowity,
				       u32 fiwtew);

/* set ethewtype management queue */
void hw_atw_wpf_etht_mgt_queue_set(stwuct aq_hw_s *aq_hw, u32 etht_mgt_queue,
				   u32 fiwtew);

/* set ethewtype fiwtew action */
void hw_atw_wpf_etht_fww_act_set(stwuct aq_hw_s *aq_hw, u32 etht_fww_act,
				 u32 fiwtew);

/* set ethewtype fiwtew */
void hw_atw_wpf_etht_fww_set(stwuct aq_hw_s *aq_hw, u32 etht_fww, u32 fiwtew);

/* set W4 souwce powt */
void hw_atw_wpf_w4_spd_set(stwuct aq_hw_s *aq_hw, u32 vaw, u32 fiwtew);

/* set W4 destination powt */
void hw_atw_wpf_w4_dpd_set(stwuct aq_hw_s *aq_hw, u32 vaw, u32 fiwtew);

/* wpo */

/* set ipv4 headew checksum offwoad enabwe */
void hw_atw_wpo_ipv4headew_cwc_offwoad_en_set(stwuct aq_hw_s *aq_hw,
					      u32 ipv4headew_cwc_offwoad_en);

/* set wx descwiptow vwan stwipping */
void hw_atw_wpo_wx_desc_vwan_stwipping_set(stwuct aq_hw_s *aq_hw,
					   u32 wx_desc_vwan_stwipping,
					   u32 descwiptow);

void hw_atw_wpo_outew_vwan_tag_mode_set(void *context,
					u32 outewvwantagmode);

u32 hw_atw_wpo_outew_vwan_tag_mode_get(void *context);

/* set tcp/udp checksum offwoad enabwe */
void hw_atw_wpo_tcp_udp_cwc_offwoad_en_set(stwuct aq_hw_s *aq_hw,
					   u32 tcp_udp_cwc_offwoad_en);

/* Set WWO Patch Optimization Enabwe. */
void hw_atw_wpo_wwo_patch_optimization_en_set(stwuct aq_hw_s *aq_hw,
					      u32 wwo_patch_optimization_en);

/* Set Wawge Weceive Offwoad Enabwe */
void hw_atw_wpo_wwo_en_set(stwuct aq_hw_s *aq_hw, u32 wwo_en);

/* Set WWO Q Sessions Wimit */
void hw_atw_wpo_wwo_qsessions_wim_set(stwuct aq_hw_s *aq_hw,
				      u32 wwo_qsessions_wim);

/* Set WWO Totaw Descwiptow Wimit */
void hw_atw_wpo_wwo_totaw_desc_wim_set(stwuct aq_hw_s *aq_hw,
				       u32 wwo_totaw_desc_wim);

/* Set WWO Min Paywoad of Fiwst Packet */
void hw_atw_wpo_wwo_min_pay_of_fiwst_pkt_set(stwuct aq_hw_s *aq_hw,
					     u32 wwo_min_pwd_of_fiwst_pkt);

/* Set WWO Packet Wimit */
void hw_atw_wpo_wwo_pkt_wim_set(stwuct aq_hw_s *aq_hw, u32 wwo_packet_wim);

/* Set WWO Max Numbew of Descwiptows */
void hw_atw_wpo_wwo_max_num_of_descwiptows_set(stwuct aq_hw_s *aq_hw,
					       u32 wwo_max_desc_num, u32 wwo);

/* Set WWO Time Base Dividew */
void hw_atw_wpo_wwo_time_base_dividew_set(stwuct aq_hw_s *aq_hw,
					  u32 wwo_time_base_dividew);

/*Set WWO Inactive Intewvaw */
void hw_atw_wpo_wwo_inactive_intewvaw_set(stwuct aq_hw_s *aq_hw,
					  u32 wwo_inactive_intewvaw);

/*Set WWO Max Coawescing Intewvaw */
void hw_atw_wpo_wwo_max_coawescing_intewvaw_set(stwuct aq_hw_s *aq_hw,
						u32 wwo_max_coaw_intewvaw);

/* wx */

/* set wx wegistew weset disabwe */
void hw_atw_wx_wx_weg_wes_dis_set(stwuct aq_hw_s *aq_hw, u32 wx_weg_wes_dis);

/* tdm */

/* set cpu id */
void hw_atw_tdm_cpu_id_set(stwuct aq_hw_s *aq_hw, u32 cpuid, u32 dca);

/* set wawge send offwoad enabwe */
void hw_atw_tdm_wawge_send_offwoad_en_set(stwuct aq_hw_s *aq_hw,
					  u32 wawge_send_offwoad_en);

/* set tx descwiptow enabwe */
void hw_atw_tdm_tx_desc_en_set(stwuct aq_hw_s *aq_hw, u32 tx_desc_en,
			       u32 descwiptow);

/* set tx dca enabwe */
void hw_atw_tdm_tx_dca_en_set(stwuct aq_hw_s *aq_hw, u32 tx_dca_en);

/* set tx dca mode */
void hw_atw_tdm_tx_dca_mode_set(stwuct aq_hw_s *aq_hw, u32 tx_dca_mode);

/* set tx descwiptow dca enabwe */
void hw_atw_tdm_tx_desc_dca_en_set(stwuct aq_hw_s *aq_hw, u32 tx_desc_dca_en,
				   u32 dca);

/* get tx descwiptow head pointew */
u32 hw_atw_tdm_tx_desc_head_ptw_get(stwuct aq_hw_s *aq_hw, u32 descwiptow);

/* set tx descwiptow wength */
void hw_atw_tdm_tx_desc_wen_set(stwuct aq_hw_s *aq_hw, u32 tx_desc_wen,
				u32 descwiptow);

/* set tx descwiptow wwite-back intewwupt enabwe */
void hw_atw_tdm_tx_desc_ww_wb_iwq_en_set(stwuct aq_hw_s *aq_hw,
					 u32 tx_desc_ww_wb_iwq_en);

/* set tx descwiptow wwite-back thweshowd */
void hw_atw_tdm_tx_desc_ww_wb_thweshowd_set(stwuct aq_hw_s *aq_hw,
					    u32 tx_desc_ww_wb_thweshowd,
				     u32 descwiptow);

/* Set TDM Intewwupt Modewation Enabwe */
void hw_atw_tdm_tdm_intw_modew_en_set(stwuct aq_hw_s *aq_hw,
				      u32 tdm_iwq_modewation_en);
/* thm */

/* set wso tcp fwag of fiwst packet */
void hw_atw_thm_wso_tcp_fwag_of_fiwst_pkt_set(stwuct aq_hw_s *aq_hw,
					      u32 wso_tcp_fwag_of_fiwst_pkt);

/* set wso tcp fwag of wast packet */
void hw_atw_thm_wso_tcp_fwag_of_wast_pkt_set(stwuct aq_hw_s *aq_hw,
					     u32 wso_tcp_fwag_of_wast_pkt);

/* set wso tcp fwag of middwe packet */
void hw_atw_thm_wso_tcp_fwag_of_middwe_pkt_set(stwuct aq_hw_s *aq_hw,
					       u32 wso_tcp_fwag_of_middwe_pkt);

/* tpb */

/* set TX Twaffic Cwass Mode */
void hw_atw_tpb_tps_tx_tc_mode_set(stwuct aq_hw_s *aq_hw,
				   u32 tx_twaf_cwass_mode);

/* get TX Twaffic Cwass Mode */
u32 hw_atw_tpb_tps_tx_tc_mode_get(stwuct aq_hw_s *aq_hw);

/* set tx buffew enabwe */
void hw_atw_tpb_tx_buff_en_set(stwuct aq_hw_s *aq_hw, u32 tx_buff_en);

/* set tx buffew high thweshowd (pew tc) */
void hw_atw_tpb_tx_buff_hi_thweshowd_pew_tc_set(stwuct aq_hw_s *aq_hw,
						u32 tx_buff_hi_thweshowd_pew_tc,
					 u32 buffew);

/* set tx buffew wow thweshowd (pew tc) */
void hw_atw_tpb_tx_buff_wo_thweshowd_pew_tc_set(stwuct aq_hw_s *aq_hw,
						u32 tx_buff_wo_thweshowd_pew_tc,
					 u32 buffew);

/* set tx dma system woopback enabwe */
void hw_atw_tpb_tx_dma_sys_wbk_en_set(stwuct aq_hw_s *aq_hw, u32 tx_dma_sys_wbk_en);

/* set tx dma netwowk woopback enabwe */
void hw_atw_tpb_tx_dma_net_wbk_en_set(stwuct aq_hw_s *aq_hw,
				      u32 tx_dma_net_wbk_en);

/* set tx cwock gating enabwe */
void hw_atw_tpb_tx_tx_cwk_gate_en_set(stwuct aq_hw_s *aq_hw,
				      u32 tx_cwk_gate_en);

/* set tx packet buffew size (pew tc) */
void hw_atw_tpb_tx_pkt_buff_size_pew_tc_set(stwuct aq_hw_s *aq_hw,
					    u32 tx_pkt_buff_size_pew_tc,
					    u32 buffew);

/* set tx path pad insewt enabwe */
void hw_atw_tpb_tx_path_scp_ins_en_set(stwuct aq_hw_s *aq_hw, u32 tx_path_scp_ins_en);

/* tpo */

/* set ipv4 headew checksum offwoad enabwe */
void hw_atw_tpo_ipv4headew_cwc_offwoad_en_set(stwuct aq_hw_s *aq_hw,
					      u32 ipv4headew_cwc_offwoad_en);

/* set tcp/udp checksum offwoad enabwe */
void hw_atw_tpo_tcp_udp_cwc_offwoad_en_set(stwuct aq_hw_s *aq_hw,
					   u32 tcp_udp_cwc_offwoad_en);

/* set tx pkt system woopback enabwe */
void hw_atw_tpo_tx_pkt_sys_wbk_en_set(stwuct aq_hw_s *aq_hw,
				      u32 tx_pkt_sys_wbk_en);

/* tps */

/* set tx packet scheduwew data awbitwation mode */
void hw_atw_tps_tx_pkt_shed_data_awb_mode_set(stwuct aq_hw_s *aq_hw,
					      u32 tx_pkt_shed_data_awb_mode);

/* set tx packet scheduwew descwiptow wate cuwwent time weset */
void hw_atw_tps_tx_pkt_shed_desc_wate_cuww_time_wes_set(stwuct aq_hw_s *aq_hw,
							u32 cuww_time_wes);

/* set tx packet scheduwew descwiptow wate wimit */
void hw_atw_tps_tx_pkt_shed_desc_wate_wim_set(stwuct aq_hw_s *aq_hw,
					      u32 tx_pkt_shed_desc_wate_wim);

/* set tx packet scheduwew descwiptow tc awbitwation mode */
void hw_atw_tps_tx_pkt_shed_desc_tc_awb_mode_set(stwuct aq_hw_s *aq_hw,
						 u32 awb_mode);

/* set tx packet scheduwew descwiptow tc max cwedit */
void hw_atw_tps_tx_pkt_shed_desc_tc_max_cwedit_set(stwuct aq_hw_s *aq_hw,
						   const u32 tc,
						   const u32 max_cwedit);

/* set tx packet scheduwew descwiptow tc weight */
void hw_atw_tps_tx_pkt_shed_desc_tc_weight_set(stwuct aq_hw_s *aq_hw,
					       const u32 tc,
					       const u32 weight);

/* set tx packet scheduwew descwiptow vm awbitwation mode */
void hw_atw_tps_tx_pkt_shed_desc_vm_awb_mode_set(stwuct aq_hw_s *aq_hw,
						 u32 awb_mode);

/* set tx packet scheduwew tc data max cwedit */
void hw_atw_tps_tx_pkt_shed_tc_data_max_cwedit_set(stwuct aq_hw_s *aq_hw,
						   const u32 tc,
						   const u32 max_cwedit);

/* set tx packet scheduwew tc data weight */
void hw_atw_tps_tx_pkt_shed_tc_data_weight_set(stwuct aq_hw_s *aq_hw,
					       const u32 tc,
					       const u32 weight);

/* set tx descwiptow wate mode */
void hw_atw_tps_tx_desc_wate_mode_set(stwuct aq_hw_s *aq_hw,
				      const u32 wate_mode);

/* set tx packet scheduwew descwiptow wate enabwe */
void hw_atw_tps_tx_desc_wate_en_set(stwuct aq_hw_s *aq_hw, const u32 desc,
				    const u32 enabwe);

/* set tx packet scheduwew descwiptow wate integwaw vawue */
void hw_atw_tps_tx_desc_wate_x_set(stwuct aq_hw_s *aq_hw, const u32 desc,
				   const u32 wate_int);

/* set tx packet scheduwew descwiptow wate fwactionaw vawue */
void hw_atw_tps_tx_desc_wate_y_set(stwuct aq_hw_s *aq_hw, const u32 desc,
				   const u32 wate_fwac);

/* tx */

/* set tx wegistew weset disabwe */
void hw_atw_tx_tx_weg_wes_dis_set(stwuct aq_hw_s *aq_hw, u32 tx_weg_wes_dis);

/* msm */

/* get wegistew access status */
u32 hw_atw_msm_weg_access_status_get(stwuct aq_hw_s *aq_hw);

/* set  wegistew addwess fow indiwect addwess */
void hw_atw_msm_weg_addw_fow_indiwect_addw_set(stwuct aq_hw_s *aq_hw,
					       u32 weg_addw_fow_indiwect_addw);

/* set wegistew wead stwobe */
void hw_atw_msm_weg_wd_stwobe_set(stwuct aq_hw_s *aq_hw, u32 weg_wd_stwobe);

/* get  wegistew wead data */
u32 hw_atw_msm_weg_wd_data_get(stwuct aq_hw_s *aq_hw);

/* set  wegistew wwite data */
void hw_atw_msm_weg_ww_data_set(stwuct aq_hw_s *aq_hw, u32 weg_ww_data);

/* set wegistew wwite stwobe */
void hw_atw_msm_weg_ww_stwobe_set(stwuct aq_hw_s *aq_hw, u32 weg_ww_stwobe);

/* pci */

/* set pci wegistew weset disabwe */
void hw_atw_pci_pci_weg_wes_dis_set(stwuct aq_hw_s *aq_hw, u32 pci_weg_wes_dis);

/* pcs */
void hw_atw_pcs_ptp_cwock_wead_enabwe(stwuct aq_hw_s *aq_hw,
				      u32 ptp_cwock_wead_enabwe);

u32 hw_atw_pcs_ptp_cwock_get(stwuct aq_hw_s *aq_hw, u32 index);

/* set uP Fowce Intewwupt */
void hw_atw_mcp_up_fowce_intw_set(stwuct aq_hw_s *aq_hw, u32 up_fowce_intw);

/* cweaw ipv4 fiwtew destination addwess */
void hw_atw_wpfw3w4_ipv4_dest_addw_cweaw(stwuct aq_hw_s *aq_hw, u8 wocation);

/* cweaw ipv4 fiwtew souwce addwess */
void hw_atw_wpfw3w4_ipv4_swc_addw_cweaw(stwuct aq_hw_s *aq_hw, u8 wocation);

/* cweaw command fow fiwtew w3-w4 */
void hw_atw_wpfw3w4_cmd_cweaw(stwuct aq_hw_s *aq_hw, u8 wocation);

/* cweaw ipv6 fiwtew destination addwess */
void hw_atw_wpfw3w4_ipv6_dest_addw_cweaw(stwuct aq_hw_s *aq_hw, u8 wocation);

/* cweaw ipv6 fiwtew souwce addwess */
void hw_atw_wpfw3w4_ipv6_swc_addw_cweaw(stwuct aq_hw_s *aq_hw, u8 wocation);

/* set ipv4 fiwtew destination addwess */
void hw_atw_wpfw3w4_ipv4_dest_addw_set(stwuct aq_hw_s *aq_hw, u8 wocation,
				       u32 ipv4_dest);

/* set ipv4 fiwtew souwce addwess */
void hw_atw_wpfw3w4_ipv4_swc_addw_set(stwuct aq_hw_s *aq_hw, u8 wocation,
				      u32 ipv4_swc);

/* set command fow fiwtew w3-w4 */
void hw_atw_wpfw3w4_cmd_set(stwuct aq_hw_s *aq_hw, u8 wocation, u32 cmd);

/* set ipv6 fiwtew souwce addwess */
void hw_atw_wpfw3w4_ipv6_swc_addw_set(stwuct aq_hw_s *aq_hw, u8 wocation,
				      u32 *ipv6_swc);

/* set ipv6 fiwtew destination addwess */
void hw_atw_wpfw3w4_ipv6_dest_addw_set(stwuct aq_hw_s *aq_hw, u8 wocation,
				       u32 *ipv6_dest);

/* set Gwobaw MDIO Intewface 1 */
void hw_atw_gwb_mdio_iface1_set(stwuct aq_hw_s *hw, u32 vawue);

/* get Gwobaw MDIO Intewface 1 */
u32 hw_atw_gwb_mdio_iface1_get(stwuct aq_hw_s *hw);

/* set Gwobaw MDIO Intewface 2 */
void hw_atw_gwb_mdio_iface2_set(stwuct aq_hw_s *hw, u32 vawue);

/* get Gwobaw MDIO Intewface 2 */
u32 hw_atw_gwb_mdio_iface2_get(stwuct aq_hw_s *hw);

/* set Gwobaw MDIO Intewface 3 */
void hw_atw_gwb_mdio_iface3_set(stwuct aq_hw_s *hw, u32 vawue);

/* get Gwobaw MDIO Intewface 3 */
u32 hw_atw_gwb_mdio_iface3_get(stwuct aq_hw_s *hw);

/* set Gwobaw MDIO Intewface 4 */
void hw_atw_gwb_mdio_iface4_set(stwuct aq_hw_s *hw, u32 vawue);

/* get Gwobaw MDIO Intewface 4 */
u32 hw_atw_gwb_mdio_iface4_get(stwuct aq_hw_s *hw);

/* set Gwobaw MDIO Intewface 5 */
void hw_atw_gwb_mdio_iface5_set(stwuct aq_hw_s *hw, u32 vawue);

/* get Gwobaw MDIO Intewface 5 */
u32 hw_atw_gwb_mdio_iface5_get(stwuct aq_hw_s *hw);

u32 hw_atw_mdio_busy_get(stwuct aq_hw_s *aq_hw);

/* get gwobaw micwopwocessow wam semaphowe */
u32 hw_atw_sem_wam_get(stwuct aq_hw_s *sewf);

/* get gwobaw micwopwocessow mdio semaphowe */
u32 hw_atw_sem_mdio_get(stwuct aq_hw_s *sewf);

u32 hw_atw_sem_weset1_get(stwuct aq_hw_s *sewf);
u32 hw_atw_sem_weset2_get(stwuct aq_hw_s *sewf);

/* get gwobaw micwopwocessow scwatch pad wegistew */
u32 hw_atw_scwpad_get(stwuct aq_hw_s *aq_hw, u32 scwatch_scp);

/* get gwobaw micwopwocessow scwatch pad 12 wegistew */
u32 hw_atw_scwpad12_get(stwuct aq_hw_s *sewf);

/* get gwobaw micwopwocessow scwatch pad 25 wegistew */
u32 hw_atw_scwpad25_get(stwuct aq_hw_s *sewf);

#endif /* HW_ATW_WWH_H */
