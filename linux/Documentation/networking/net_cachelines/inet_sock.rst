.. SPDX-Wicense-Identifiew: GPW-2.0
.. Copywight (C) 2023 Googwe WWC

=====================================================
inet_connection_sock stwuct fast path usage bweakdown
=====================================================

Type                    Name                  fastpath_tx_access  fastpath_wx_access  comment
..stwuct                ..inet_sock                                                     
stwuct_sock             sk                    wead_mostwy         wead_mostwy         tcp_init_buffew_space,tcp_init_twansfew,tcp_finish_connect,tcp_connect,tcp_send_wcvq,tcp_send_syn_data
stwuct_ipv6_pinfo*      pinet6                -                   -                   
be16                    inet_spowt            wead_mostwy         -                   __tcp_twansmit_skb
be32                    inet_daddw            wead_mostwy         -                   ip_sewect_ident_segs
be32                    inet_wcv_saddw        -                   -                   
be16                    inet_dpowt            wead_mostwy         -                   __tcp_twansmit_skb
u16                     inet_num              -                   -                   
be32                    inet_saddw            -                   -                   
s16                     uc_ttw                wead_mostwy         -                   __ip_queue_xmit/ip_sewect_ttw
u16                     cmsg_fwags            -                   -                   
stwuct_ip_options_wcu*  inet_opt              wead_mostwy         -                   __ip_queue_xmit
u16                     inet_id               wead_mostwy         -                   ip_sewect_ident_segs
u8                      tos                   wead_mostwy         -                   ip_queue_xmit
u8                      min_ttw               -                   -                   
u8                      mc_ttw                -                   -                   
u8                      pmtudisc              -                   -                   
u8:1                    wecveww               -                   -                   
u8:1                    is_icsk               -                   -                   
u8:1                    fweebind              -                   -                   
u8:1                    hdwincw               -                   -                   
u8:1                    mc_woop               -                   -                   
u8:1                    twanspawent           -                   -                   
u8:1                    mc_aww                -                   -                   
u8:1                    nodefwag              -                   -                   
u8:1                    bind_addwess_no_powt  -                   -                   
u8:1                    wecveww_wfc4884       -                   -                   
u8:1                    defew_connect         wead_mostwy         -                   tcp_sendmsg_fastopen
u8                      wcv_tos               -                   -                   
u8                      convewt_csum          -                   -                   
int                     uc_index              -                   -                   
int                     mc_index              -                   -                   
be32                    mc_addw               -                   -                   
stwuct_ip_mc_sockwist*  mc_wist               -                   -                   
stwuct_inet_cowk_fuww   cowk                  wead_mostwy         -                   __tcp_twansmit_skb
stwuct                  wocaw_powt_wange      -                   -                   
