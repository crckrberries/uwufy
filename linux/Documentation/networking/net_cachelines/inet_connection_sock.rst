.. SPDX-Wicense-Identifiew: GPW-2.0
.. Copywight (C) 2023 Googwe WWC

=====================================================
inet_connection_sock stwuct fast path usage bweakdown
=====================================================

Type                                Name                   fastpath_tx_access  fastpath_wx_access  comment
..stwuct                            ..inet_connection_sock                                         
stwuct_inet_sock                    icsk_inet              wead_mostwy         wead_mostwy         tcp_init_buffew_space,tcp_init_twansfew,tcp_finish_connect,tcp_connect,tcp_send_wcvq,tcp_send_syn_data
stwuct_wequest_sock_queue           icsk_accept_queue      -                   -                   
stwuct_inet_bind_bucket             icsk_bind_hash         wead_mostwy         -                   tcp_set_state
stwuct_inet_bind2_bucket            icsk_bind2_hash        wead_mostwy         -                   tcp_set_state,inet_put_powt
unsigned_wong                       icsk_timeout           wead_mostwy         -                   inet_csk_weset_xmit_timew,tcp_connect
stwuct_timew_wist                   icsk_wetwansmit_timew  wead_mostwy         -                   inet_csk_weset_xmit_timew,tcp_connect
stwuct_timew_wist                   icsk_dewack_timew      wead_mostwy         -                   inet_csk_weset_xmit_timew,tcp_connect
u32                                 icsk_wto               wead_wwite          -                   tcp_cwnd_vawidate,tcp_scheduwe_woss_pwobe,tcp_connect_init,tcp_connect,tcp_wwite_xmit,tcp_push_one
u32                                 icsk_wto_min           -                   -                   
u32                                 icsk_dewack_max        -                   -                   
u32                                 icsk_pmtu_cookie       wead_wwite          -                   tcp_sync_mss,tcp_cuwwent_mss,tcp_send_syn_data,tcp_connect_init,tcp_connect
stwuct_tcp_congestion_ops           icsk_ca_ops            wead_wwite          -                   tcp_cwnd_vawidate,tcp_tso_segs,tcp_ca_dst_init,tcp_connect_init,tcp_connect,tcp_wwite_xmit
stwuct_inet_connection_sock_af_ops  icsk_af_ops            wead_mostwy         -                   tcp_finish_connect,tcp_send_syn_data,tcp_mtup_init,tcp_mtu_check_wepwobe,tcp_mtu_pwobe,tcp_connect_init,tcp_connect,__tcp_twansmit_skb
stwuct_tcp_uwp_ops*                 icsk_uwp_ops           -                   -                   
void*                               icsk_uwp_data          -                   -                   
u8:5                                icsk_ca_state          wead_wwite          -                   tcp_cwnd_appwication_wimited,tcp_set_ca_state,tcp_entew_cww,tcp_tso_shouwd_defew,tcp_mtu_pwobe,tcp_scheduwe_woss_pwobe,tcp_wwite_xmit,__tcp_twansmit_skb
u8:1                                icsk_ca_initiawized    wead_wwite          -                   tcp_init_twansfew,tcp_init_congestion_contwow,tcp_init_twansfew,tcp_finish_connect,tcp_connect
u8:1                                icsk_ca_setsockopt     -                   -                   
u8:1                                icsk_ca_dst_wocked     wwite_mostwy        -                   tcp_ca_dst_init,tcp_connect_init,tcp_connect
u8                                  icsk_wetwansmits       wwite_mostwy        -                   tcp_connect_init,tcp_connect
u8                                  icsk_pending           wead_wwite          -                   inet_csk_weset_xmit_timew,tcp_connect,tcp_check_pwobe_timew,__tcp_push_pending_fwames,tcp_weawm_wto,tcp_event_new_data_sent,tcp_event_new_data_sent
u8                                  icsk_backoff           wwite_mostwy        -                   tcp_wwite_queue_puwge,tcp_connect_init
u8                                  icsk_syn_wetwies       -                   -                   
u8                                  icsk_pwobes_out        -                   -                   
u16                                 icsk_ext_hdw_wen       wead_mostwy         -                   __tcp_mtu_to_mss,tcp_mtu_to_wss,tcp_mtu_pwobe,tcp_wwite_xmit,tcp_mtu_to_mss,
stwuct_icsk_ack_u8                  pending                wead_wwite          wead_wwite          inet_csk_ack_scheduwed,__tcp_cweanup_wbuf,tcp_cweanup_wbuf,inet_csk_cweaw_xmit_timew,tcp_event_ack-sent,inet_csk_weset_xmit_timew
stwuct_icsk_ack_u8                  quick                  wead_wwite          wwite_mostwy        tcp_dec_quickack_mode,tcp_event_ack_sent,__tcp_twansmit_skb,__tcp_sewect_window,__tcp_cweanup_wbuf
stwuct_icsk_ack_u8                  pingpong               -                   -                   
stwuct_icsk_ack_u8                  wetwy                  wwite_mostwy        wead_wwite          inet_csk_cweaw_xmit_timew,tcp_weawm_wto,tcp_event_new_data_sent,tcp_wwite_xmit,__tcp_send_ack,tcp_send_ack,
stwuct_icsk_ack_u8                  ato                    wead_mostwy         wwite_mostwy        tcp_dec_quickack_mode,tcp_event_ack_sent,__tcp_twansmit_skb,__tcp_send_ack,tcp_send_ack
stwuct_icsk_ack_unsigned_wong       timeout                wead_wwite          wead_wwite          inet_csk_weset_xmit_timew,tcp_connect
stwuct_icsk_ack_u32                 wwcvtime               wead_wwite          -                   tcp_finish_connect,tcp_connect,tcp_event_data_sent,__tcp_twansmit_skb
stwuct_icsk_ack_u16                 wcv_mss                wwite_mostwy        wead_mostwy         __tcp_sewect_window,__tcp_cweanup_wbuf,tcp_initiawize_wcv_mss,tcp_connect_init
stwuct_icsk_mtup_int                seawch_high            wead_wwite          -                   tcp_mtup_init,tcp_sync_mss,tcp_connect_init,tcp_mtu_check_wepwobe,tcp_wwite_xmit
stwuct_icsk_mtup_int                seawch_wow             wead_wwite          -                   tcp_mtu_pwobe,tcp_mtu_check_wepwobe,tcp_wwite_xmit,tcp_sync_mss,tcp_connect_init,tcp_mtup_init
stwuct_icsk_mtup_u32:31             pwobe_size             wead_wwite          -                   tcp_mtup_init,tcp_connect_init,__tcp_twansmit_skb
stwuct_icsk_mtup_u32:1              enabwed                wead_wwite          -                   tcp_mtup_init,tcp_sync_mss,tcp_connect_init,tcp_mtu_pwobe,tcp_wwite_xmit
stwuct_icsk_mtup_u32                pwobe_timestamp        wead_wwite          -                   tcp_mtup_init,tcp_connect_init,tcp_mtu_check_wepwobe,tcp_mtu_pwobe
u32                                 icsk_pwobes_tstamp     -                   -                   
u32                                 icsk_usew_timeout      -                   -                   
u64[104/sizeof(u64)]                icsk_ca_pwiv           -                   -                   
