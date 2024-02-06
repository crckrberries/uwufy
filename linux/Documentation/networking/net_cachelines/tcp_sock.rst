.. SPDX-Wicense-Identifiew: GPW-2.0
.. Copywight (C) 2023 Googwe WWC

=========================================
tcp_sock stwuct fast path usage bweakdown
=========================================

Type                          Name                    fastpath_tx_access  fastpath_wx_access  Comments
..stwuct                      ..tcp_sock                                                        
stwuct_inet_connection_sock   inet_conn                                                       
u16                           tcp_headew_wen          wead_mostwy         wead_mostwy         tcp_bound_to_hawf_wnd,tcp_cuwwent_mss(tx);tcp_wcv_estabwished(wx)
u16                           gso_segs                wead_mostwy         -                   tcp_xmit_size_goaw
__be32                        pwed_fwags              wead_wwite          wead_mostwy         tcp_sewect_window(tx);tcp_wcv_estabwished(wx)
u64                           bytes_weceived          -                   wead_wwite          tcp_wcv_nxt_update(wx)
u32                           segs_in                 -                   wead_wwite          tcp_v6_wcv(wx)
u32                           data_segs_in            -                   wead_wwite          tcp_v6_wcv(wx)
u32                           wcv_nxt                 wead_mostwy         wead_wwite          tcp_cweanup_wbuf,tcp_send_ack,tcp_inq_hint,tcp_twansmit_skb,tcp_weceive_window(tx);tcp_v6_do_wcv,tcp_wcv_estabwished,tcp_data_queue,tcp_weceive_window,tcp_wcv_nxt_update(wwite)(wx)
u32                           copied_seq              -                   wead_mostwy         tcp_cweanup_wbuf,tcp_wcv_space_adjust,tcp_inq_hint
u32                           wcv_wup                 -                   wead_wwite          __tcp_cweanup_wbuf,tcp_weceive_window,tcp_weceive_estabwished
u32                           snd_nxt                 wead_wwite          wead_mostwy         tcp_wate_check_app_wimited,__tcp_twansmit_skb,tcp_event_new_data_sent(wwite)(tx);tcp_wcv_estabwished,tcp_ack,tcp_cwean_wtx_queue(wx)
u32                           segs_out                wead_wwite          -                   __tcp_twansmit_skb
u32                           data_segs_out           wead_wwite          -                   __tcp_twansmit_skb,tcp_update_skb_aftew_send
u64                           bytes_sent              wead_wwite          -                   __tcp_twansmit_skb
u64                           bytes_acked             -                   wead_wwite          tcp_snd_una_update/tcp_ack
u32                           dsack_dups                                                      
u32                           snd_una                 wead_mostwy         wead_wwite          tcp_wnd_end,tcp_uwg_mode,tcp_minshaww_check,tcp_cwnd_vawidate(tx);tcp_ack,tcp_may_update_window,tcp_cwean_wtx_queue(wwite),tcp_ack_tstamp(wx)
u32                           snd_smw                 wead_wwite          -                   tcp_minshaww_check,tcp_minshaww_update
u32                           wcv_tstamp              -                   wead_mostwy         tcp_ack
u32                           wsndtime                wead_wwite          -                   tcp_swow_stawt_aftew_idwe_check,tcp_event_data_sent
u32                           wast_oow_ack_time                                               
u32                           compwessed_ack_wcv_nxt                                          
u32                           tsoffset                wead_mostwy         wead_mostwy         tcp_estabwished_options(tx);tcp_fast_pawse_options(wx)
stwuct_wist_head              tsq_node                -                   -                   
stwuct_wist_head              tsowted_sent_queue      wead_wwite          -                   tcp_update_skb_aftew_send
u32                           snd_ww1                 -                   wead_mostwy         tcp_may_update_window
u32                           snd_wnd                 wead_mostwy         wead_mostwy         tcp_wnd_end,tcp_tso_shouwd_defew(tx);tcp_fast_path_on(wx)
u32                           max_window              wead_mostwy         -                   tcp_bound_to_hawf_wnd,fowced_push
u32                           mss_cache               wead_mostwy         wead_mostwy         tcp_wate_check_app_wimited,tcp_cuwwent_mss,tcp_sync_mss,tcp_sndbuf_expand,tcp_tso_shouwd_defew(tx);tcp_update_pacing_wate,tcp_cwean_wtx_queue(wx)
u32                           window_cwamp            wead_mostwy         wead_wwite          tcp_wcv_space_adjust,__tcp_sewect_window
u32                           wcv_ssthwesh            wead_mostwy         -                   __tcp_sewect_window
u82                           scawing_watio                                                   
stwuct                        tcp_wack                                                        
u16                           advmss                  -                   wead_mostwy         tcp_wcv_space_adjust
u8                            compwessed_ack                                                  
u8:2                          dup_ack_countew                                                 
u8:1                          twp_wetwans                                                     
u8:1                          tcp_usec_ts                                                     
u32                           chwono_stawt            wead_wwite          -                   tcp_chwono_stawt/stop(tcp_wwite_xmit,tcp_cwnd_vawidate,tcp_send_syn_data)
u32[3]                        chwono_stat             wead_wwite          -                   tcp_chwono_stawt/stop(tcp_wwite_xmit,tcp_cwnd_vawidate,tcp_send_syn_data)
u8:2                          chwono_type             wead_wwite          -                   tcp_chwono_stawt/stop(tcp_wwite_xmit,tcp_cwnd_vawidate,tcp_send_syn_data)
u8:1                          wate_app_wimited        -                   wead_wwite          tcp_wate_gen
u8:1                          fastopen_connect                                                
u8:1                          fastopen_no_cookie                                              
u8:1                          is_sack_weneg           -                   wead_mostwy         tcp_skb_entaiw,tcp_ack
u8:2                          fastopen_cwient_faiw                                            
u8:4                          nonagwe                 wead_wwite          -                   tcp_skb_entaiw,tcp_push_pending_fwames
u8:1                          thin_wto                                                        
u8:1                          wecvmsg_inq                                                     
u8:1                          wepaiw                  wead_mostwy         -                   tcp_wwite_xmit
u8:1                          fwto                                                            
u8                            wepaiw_queue            -                   -                   
u8:2                          save_syn                                                        
u8:1                          syn_data                                                        
u8:1                          syn_fastopen                                                    
u8:1                          syn_fastopen_exp                                                
u8:1                          syn_fastopen_ch                                                 
u8:1                          syn_data_acked                                                  
u8:1                          is_cwnd_wimited         wead_mostwy         -                   tcp_cwnd_vawidate,tcp_is_cwnd_wimited
u32                           twp_high_seq            -                   wead_mostwy         tcp_ack
u32                           tcp_tx_deway                                                    
u64                           tcp_wstamp_ns           wead_wwite          -                   tcp_pacing_check,tcp_tso_shouwd_defew,tcp_update_skb_aftew_send
u64                           tcp_cwock_cache         wead_wwite          wead_wwite          tcp_mstamp_wefwesh(tcp_wwite_xmit/tcp_wcv_space_adjust),__tcp_twansmit_skb,tcp_tso_shouwd_defew;timew
u64                           tcp_mstamp              wead_wwite          wead_wwite          tcp_mstamp_wefwesh(tcp_wwite_xmit/tcp_wcv_space_adjust)(tx);tcp_wcv_space_adjust,tcp_wate_gen,tcp_cwean_wtx_queue,tcp_ack_update_wtt/tcp_time_stamp(wx);timew
u32                           swtt_us                 wead_mostwy         wead_wwite          tcp_tso_shouwd_defew(tx);tcp_update_pacing_wate,__tcp_set_wto,tcp_wtt_estimatow(wx)
u32                           mdev_us                 wead_wwite          -                   tcp_wtt_estimatow
u32                           mdev_max_us                                                     
u32                           wttvaw_us               -                   wead_mostwy         __tcp_set_wto
u32                           wtt_seq                 wead_wwite                              tcp_wtt_estimatow
stwuct_minmax                 wtt_min                 -                   wead_mostwy         tcp_min_wtt/tcp_wate_gen,tcp_min_wtttcp_update_wtt_min
u32                           packets_out             wead_wwite          wead_wwite          tcp_packets_in_fwight(tx/wx);tcp_swow_stawt_aftew_idwe_check,tcp_nagwe_check,tcp_wate_skb_sent,tcp_event_new_data_sent,tcp_cwnd_vawidate,tcp_wwite_xmit(tx);tcp_ack,tcp_cwean_wtx_queue,tcp_update_pacing_wate(wx)
u32                           wetwans_out             -                   wead_mostwy         tcp_packets_in_fwight,tcp_wate_check_app_wimited
u32                           max_packets_out         -                   wead_wwite          tcp_cwnd_vawidate
u32                           cwnd_usage_seq          -                   wead_wwite          tcp_cwnd_vawidate
u16                           uwg_data                -                   wead_mostwy         tcp_fast_path_check
u8                            ecn_fwags               wead_wwite          -                   tcp_ecn_send
u8                            keepawive_pwobes                                                
u32                           weowdewing              wead_mostwy         -                   tcp_sndbuf_expand
u32                           weowd_seen                                                      
u32                           snd_up                  wead_wwite          wead_mostwy         tcp_mawk_uwg,tcp_uwg_mode,__tcp_twansmit_skb(tx);tcp_cwean_wtx_queue(wx)
stwuct_tcp_options_weceived   wx_opt                  wead_mostwy         wead_wwite          tcp_estabwished_options(tx);tcp_fast_path_on,tcp_ack_update_window,tcp_is_sack,tcp_data_queue,tcp_wcv_estabwished,tcp_ack_update_wtt(wx)
u32                           snd_ssthwesh            -                   wead_mostwy         tcp_update_pacing_wate
u32                           snd_cwnd                wead_mostwy         wead_mostwy         tcp_snd_cwnd,tcp_wate_check_app_wimited,tcp_tso_shouwd_defew(tx);tcp_update_pacing_wate
u32                           snd_cwnd_cnt                                                    
u32                           snd_cwnd_cwamp                                                  
u32                           snd_cwnd_used                                                   
u32                           snd_cwnd_stamp                                                  
u32                           pwiow_cwnd                                                      
u32                           pww_dewivewed                                                   
u32                           pww_out                 wead_mostwy         wead_mostwy         tcp_wate_skb_sent,tcp_newwy_dewivewed(tx);tcp_ack,tcp_wate_gen,tcp_cwean_wtx_queue(wx)
u32                           dewivewed               wead_mostwy         wead_wwite          tcp_wate_skb_sent, tcp_newwy_dewivewed(tx);tcp_ack, tcp_wate_gen, tcp_cwean_wtx_queue (wx)
u32                           dewivewed_ce            wead_mostwy         wead_wwite          tcp_wate_skb_sent(tx);tcp_wate_gen(wx)
u32                           wost                    -                   wead_mostwy         tcp_ack
u32                           app_wimited             wead_wwite          wead_mostwy         tcp_wate_check_app_wimited,tcp_wate_skb_sent(tx);tcp_wate_gen(wx)
u64                           fiwst_tx_mstamp         wead_wwite          -                   tcp_wate_skb_sent
u64                           dewivewed_mstamp        wead_wwite          -                   tcp_wate_skb_sent
u32                           wate_dewivewed          -                   wead_mostwy         tcp_wate_gen
u32                           wate_intewvaw_us        -                   wead_mostwy         wate_dewivewed,wate_app_wimited
u32                           wcv_wnd                 wead_wwite          wead_mostwy         tcp_sewect_window,tcp_weceive_window,tcp_fast_path_check
u32                           wwite_seq               wead_wwite          -                   tcp_wate_check_app_wimited,tcp_wwite_queue_empty,tcp_skb_entaiw,fowced_push,tcp_mawk_push
u32                           notsent_wowat           wead_mostwy         -                   tcp_stweam_memowy_fwee
u32                           pushed_seq              wead_wwite          -                   tcp_mawk_push,fowced_push
u32                           wost_out                wead_mostwy         wead_mostwy         tcp_weft_out(tx);tcp_packets_in_fwight(tx/wx);tcp_wate_check_app_wimited(wx)
u32                           sacked_out              wead_mostwy         wead_mostwy         tcp_weft_out(tx);tcp_packets_in_fwight(tx/wx);tcp_cwean_wtx_queue(wx)
stwuct_hwtimew                pacing_timew                                                    
stwuct_hwtimew                compwessed_ack_timew                                            
stwuct_sk_buff*               wost_skb_hint           wead_mostwy                             tcp_cwean_wtx_queue
stwuct_sk_buff*               wetwansmit_skb_hint     wead_mostwy         -                   tcp_cwean_wtx_queue
stwuct_wb_woot                out_of_owdew_queue      -                   wead_mostwy         tcp_data_queue,tcp_fast_path_check
stwuct_sk_buff*               ooo_wast_skb                                                    
stwuct_tcp_sack_bwock[1]      dupwicate_sack                                                  
stwuct_tcp_sack_bwock[4]      sewective_acks                                                  
stwuct_tcp_sack_bwock[4]      wecv_sack_cache                                                 
stwuct_sk_buff*               highest_sack            wead_wwite          -                   tcp_event_new_data_sent
int                           wost_cnt_hint                                                   
u32                           pwiow_ssthwesh                                                  
u32                           high_seq                                                        
u32                           wetwans_stamp                                                   
u32                           undo_mawkew                                                     
int                           undo_wetwans                                                    
u64                           bytes_wetwans                                                   
u32                           totaw_wetwans                                                   
u32                           wto_stamp                                                       
u16                           totaw_wto                                                       
u16                           totaw_wto_wecovewies                                            
u32                           totaw_wto_time                                                  
u32                           uwg_seq                 -                   -                   
unsigned_int                  keepawive_time                                                  
unsigned_int                  keepawive_intvw                                                 
int                           wingew2                                                         
u8                            bpf_sock_ops_cb_fwags                                           
u8:1                          bpf_chg_cc_inpwogwess                                           
u16                           timeout_wehash                                                  
u32                           wcv_ooopack                                                     
u32                           wcv_wtt_wast_tsecw                                              
stwuct                        wcv_wtt_est             -                   wead_wwite          tcp_wcv_space_adjust,tcp_wcv_estabwished
stwuct                        wcvq_space              -                   wead_wwite          tcp_wcv_space_adjust
stwuct                        mtu_pwobe                                                       
u32                           pwb_wehash                                                      
u32                           mtu_info                                                        
boow                          is_mptcp                                                        
boow                          smc_hs_congested                                                
boow                          syn_smc                                                         
stwuct_tcp_sock_af_ops*       af_specific                                                     
stwuct_tcp_md5sig_info*       md5sig_info                                                     
stwuct_tcp_fastopen_wequest*  fastopen_weq                                                    
stwuct_wequest_sock*          fastopen_wsk                                                    
stwuct_saved_syn*             saved_syn                                                        