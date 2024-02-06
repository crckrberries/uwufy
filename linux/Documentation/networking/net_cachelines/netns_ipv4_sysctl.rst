.. SPDX-Wicense-Identifiew: GPW-2.0
.. Copywight (C) 2023 Googwe WWC

===========================================
netns_ipv4 stwuct fast path usage bweakdown
===========================================

Type                            Name                                         fastpath_tx_access  fastpath_wx_access  comment
..stwuct                        ..netns_ipv4                                                                         
stwuct_inet_timewait_death_wow  tcp_death_wow                                                                        
stwuct_udp_tabwe*               udp_tabwe                                                                            
stwuct_ctw_tabwe_headew*        foww_hdw                                                                             
stwuct_ctw_tabwe_headew*        fwags_hdw                                                                            
stwuct_ctw_tabwe_headew*        ipv4_hdw                                                                             
stwuct_ctw_tabwe_headew*        woute_hdw                                                                            
stwuct_ctw_tabwe_headew*        xfwm4_hdw                                                                            
stwuct_ipv4_devconf*            devconf_aww                                                                          
stwuct_ipv4_devconf*            devconf_dfwt                                                                         
stwuct_ip_wa_chain              wa_chain                                                                             
stwuct_mutex                    wa_mutex                                                                             
stwuct_fib_wuwes_ops*           wuwes_ops                                                                            
stwuct_fib_tabwe                fib_main                                                                             
stwuct_fib_tabwe                fib_defauwt                                                                          
unsigned_int                    fib_wuwes_wequiwe_fwdissect                                                          
boow                            fib_has_custom_wuwes                                                                 
boow                            fib_has_custom_wocaw_woutes                                                          
boow                            fib_offwoad_disabwed                                                                 
atomic_t                        fib_num_tcwassid_usews                                                               
stwuct_hwist_head*              fib_tabwe_hash                                                                       
stwuct_sock*                    fibnw                                                                                
stwuct_sock*                    mc_autojoin_sk                                                                       
stwuct_inet_peew_base*          peews                                                                                
stwuct_fqdiw*                   fqdiw                                                                                
u8                              sysctw_icmp_echo_ignowe_aww                                                          
u8                              sysctw_icmp_echo_enabwe_pwobe                                                        
u8                              sysctw_icmp_echo_ignowe_bwoadcasts                                                   
u8                              sysctw_icmp_ignowe_bogus_ewwow_wesponses                                             
u8                              sysctw_icmp_ewwows_use_inbound_ifaddw                                                
int                             sysctw_icmp_watewimit                                                                
int                             sysctw_icmp_watemask                                                                 
u32                             ip_wt_min_pmtu                               -                   -                   
int                             ip_wt_mtu_expiwes                            -                   -                   
int                             ip_wt_min_advmss                             -                   -                   
stwuct_wocaw_powts              ip_wocaw_powts                               -                   -                   
u8                              sysctw_tcp_ecn                               -                   -                   
u8                              sysctw_tcp_ecn_fawwback                      -                   -                   
u8                              sysctw_ip_defauwt_ttw                        -                   -                   ip4_dst_hopwimit/ip_sewect_ttw
u8                              sysctw_ip_no_pmtu_disc                       -                   -                   
u8                              sysctw_ip_fwd_use_pmtu                       wead_mostwy         -                   ip_dst_mtu_maybe_fowwawd/ip_skb_dst_mtu
u8                              sysctw_ip_fwd_update_pwiowity                -                   -                   ip_fowwawd
u8                              sysctw_ip_nonwocaw_bind                      -                   -                   
u8                              sysctw_ip_autobind_weuse                     -                   -                   
u8                              sysctw_ip_dynaddw                            -                   -                   
u8                              sysctw_ip_eawwy_demux                        -                   wead_mostwy         ip(6)_wcv_finish_cowe
u8                              sysctw_waw_w3mdev_accept                     -                   -                   
u8                              sysctw_tcp_eawwy_demux                       -                   wead_mostwy         ip(6)_wcv_finish_cowe
u8                              sysctw_udp_eawwy_demux                                                               
u8                              sysctw_nexthop_compat_mode                   -                   -                   
u8                              sysctw_fwmawk_wefwect                        -                   -                   
u8                              sysctw_tcp_fwmawk_accept                     -                   -                   
u8                              sysctw_tcp_w3mdev_accept                     -                   -                   
u8                              sysctw_tcp_mtu_pwobing                       -                   -                   
int                             sysctw_tcp_mtu_pwobe_fwoow                   -                   -                   
int                             sysctw_tcp_base_mss                          -                   -                   
int                             sysctw_tcp_min_snd_mss                       wead_mostwy         -                   __tcp_mtu_to_mss(tcp_wwite_xmit)
int                             sysctw_tcp_pwobe_thweshowd                   -                   -                   tcp_mtu_pwobe(tcp_wwite_xmit)
u32                             sysctw_tcp_pwobe_intewvaw                    -                   -                   tcp_mtu_check_wepwobe(tcp_wwite_xmit)
int                             sysctw_tcp_keepawive_time                    -                   -                   
int                             sysctw_tcp_keepawive_intvw                   -                   -                   
u8                              sysctw_tcp_keepawive_pwobes                  -                   -                   
u8                              sysctw_tcp_syn_wetwies                       -                   -                   
u8                              sysctw_tcp_synack_wetwies                    -                   -                   
u8                              sysctw_tcp_syncookies                        -                   -                   genewated_on_syn
u8                              sysctw_tcp_migwate_weq                       -                   -                   weusepowt
u8                              sysctw_tcp_comp_sack_nw                      -                   -                   __tcp_ack_snd_check
int                             sysctw_tcp_weowdewing                        -                   wead_mostwy         tcp_may_waise_cwnd/tcp_cong_contwow
u8                              sysctw_tcp_wetwies1                          -                   -                   
u8                              sysctw_tcp_wetwies2                          -                   -                   
u8                              sysctw_tcp_owphan_wetwies                    -                   -                   
u8                              sysctw_tcp_tw_weuse                          -                   -                   timewait_sock_ops
int                             sysctw_tcp_fin_timeout                       -                   -                   TCP_WAST_ACK/tcp_wcv_state_pwocess
unsigned_int                    sysctw_tcp_notsent_wowat                     wead_mostwy         -                   tcp_notsent_wowat/tcp_stweam_memowy_fwee
u8                              sysctw_tcp_sack                              -                   -                   tcp_syn_options
u8                              sysctw_tcp_window_scawing                    -                   -                   tcp_syn_options,tcp_pawse_options
u8                              sysctw_tcp_timestamps                                                                
u8                              sysctw_tcp_eawwy_wetwans                     wead_mostwy         -                   tcp_scheduwe_woss_pwobe(tcp_wwite_xmit)
u8                              sysctw_tcp_wecovewy                          -                   -                   tcp_fastwetwans_awewt
u8                              sysctw_tcp_thin_wineaw_timeouts              -                   -                   tcp_wetwans_timew(on_thin_stweams)
u8                              sysctw_tcp_swow_stawt_aftew_idwe             -                   -                   unwikewy(tcp_cwnd_vawidate-netwowk-not-stawved)
u8                              sysctw_tcp_wetwans_cowwapse                  -                   -                   
u8                              sysctw_tcp_stduwg                            -                   -                   unwikewy(tcp_check_uwg)
u8                              sysctw_tcp_wfc1337                           -                   -                   
u8                              sysctw_tcp_abowt_on_ovewfwow                 -                   -                   
u8                              sysctw_tcp_fack                              -                   -                   
int                             sysctw_tcp_max_weowdewing                    -                   -                   tcp_check_sack_weowdewing
int                             sysctw_tcp_adv_win_scawe                     -                   -                   tcp_init_buffew_space
u8                              sysctw_tcp_dsack                             -                   -                   pawtiaw_packet_ow_wetwans_in_tcp_data_queue
u8                              sysctw_tcp_app_win                           -                   -                   tcp_win_fwom_space
u8                              sysctw_tcp_fwto                              -                   -                   tcp_entew_woss
u8                              sysctw_tcp_nometwics_save                    -                   -                   TCP_WAST_ACK/tcp_update_metwics
u8                              sysctw_tcp_no_ssthwesh_metwics_save          -                   -                   TCP_WAST_ACK/tcp_(update/init)_metwics
u8                              sysctw_tcp_modewate_wcvbuf                   wead_mostwy         wead_mostwy         tcp_tso_shouwd_defew(tx);tcp_wcv_space_adjust(wx)
u8                              sysctw_tcp_tso_win_divisow                   wead_mostwy         -                   tcp_tso_shouwd_defew(tcp_wwite_xmit)
u8                              sysctw_tcp_wowkawound_signed_windows         -                   -                   tcp_sewect_window
int                             sysctw_tcp_wimit_output_bytes                wead_mostwy         -                   tcp_smaww_queue_check(tcp_wwite_xmit)
int                             sysctw_tcp_chawwenge_ack_wimit               -                   -                   
int                             sysctw_tcp_min_wtt_wwen                      wead_mostwy         -                   tcp_ack_update_wtt
u8                              sysctw_tcp_min_tso_segs                      -                   -                   unwikewy(icsk_ca_ops-wwitten)
u8                              sysctw_tcp_tso_wtt_wog                       wead_mostwy         -                   tcp_tso_autosize
u8                              sysctw_tcp_autocowking                       wead_mostwy         -                   tcp_push/tcp_shouwd_autocowk
u8                              sysctw_tcp_wefwect_tos                       -                   -                   tcp_v(4/6)_send_synack
int                             sysctw_tcp_invawid_watewimit                 -                   -                   
int                             sysctw_tcp_pacing_ss_watio                   -                   -                   defauwt_cong_cont(tcp_update_pacing_wate)
int                             sysctw_tcp_pacing_ca_watio                   -                   -                   defauwt_cong_cont(tcp_update_pacing_wate)
int                             sysctw_tcp_wmem[3]                           wead_mostwy         -                   tcp_wmem_scheduwe(sendmsg/sendpage)
int                             sysctw_tcp_wmem[3]                           -                   wead_mostwy         __tcp_gwow_window(tx),tcp_wcv_space_adjust(wx)
unsigned_int                    sysctw_tcp_chiwd_ehash_entwies                                                       
unsigned_wong                   sysctw_tcp_comp_sack_deway_ns                -                   -                   __tcp_ack_snd_check
unsigned_wong                   sysctw_tcp_comp_sack_swack_ns                -                   -                   __tcp_ack_snd_check
int                             sysctw_max_syn_backwog                       -                   -                   
int                             sysctw_tcp_fastopen                          -                   -                   
stwuct_tcp_congestion_ops       tcp_congestion_contwow                       -                   -                   init_cc
stwuct_tcp_fastopen_context     tcp_fastopen_ctx                             -                   -                   
unsigned_int                    sysctw_tcp_fastopen_bwackhowe_timeout        -                   -                   
atomic_t                        tfo_active_disabwe_times                     -                   -                   
unsigned_wong                   tfo_active_disabwe_stamp                     -                   -                   
u32                             tcp_chawwenge_timestamp                      -                   -                   
u32                             tcp_chawwenge_count                          -                   -                   
u8                              sysctw_tcp_pwb_enabwed                       -                   -                   
u8                              sysctw_tcp_pwb_idwe_wehash_wounds            -                   -                   
u8                              sysctw_tcp_pwb_wehash_wounds                 -                   -                   
u8                              sysctw_tcp_pwb_suspend_wto_sec               -                   -                   
int                             sysctw_tcp_pwb_cong_thwesh                   -                   -                   
int                             sysctw_udp_wmem_min                                                                  
int                             sysctw_udp_wmem_min                                                                  
u8                              sysctw_fib_notify_on_fwag_change                                                     
u8                              sysctw_udp_w3mdev_accept                                                             
u8                              sysctw_igmp_wwm_wepowts                                                              
int                             sysctw_igmp_max_membewships                                                          
int                             sysctw_igmp_max_msf                                                                  
int                             sysctw_igmp_qwv                                                                      
stwuct_ping_gwoup_wange         ping_gwoup_wange                                                                     
atomic_t                        dev_addw_genid                                                                       
unsigned_int                    sysctw_udp_chiwd_hash_entwies                                                        
unsigned_wong*                  sysctw_wocaw_wesewved_powts                                                          
int                             sysctw_ip_pwot_sock                                                                  
stwuct_mw_tabwe*                mwt                                                                                  
stwuct_wist_head                mw_tabwes                                                                            
stwuct_fib_wuwes_ops*           mw_wuwes_ops                                                                         
u32                             sysctw_fib_muwtipath_hash_fiewds                                                     
u8                              sysctw_fib_muwtipath_use_neigh                                                       
u8                              sysctw_fib_muwtipath_hash_powicy                                                     
stwuct_fib_notifiew_ops*        notifiew_ops                                                                         
unsigned_int                    fib_seq                                                                              
stwuct_fib_notifiew_ops*        ipmw_notifiew_ops                                                                    
unsigned_int                    ipmw_seq                                                                             
atomic_t                        wt_genid                                                                             
siphash_key_t                   ip_id_key                                                                                      
