/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ipv4 in net namespaces
 */

#ifndef __NETNS_IPV4_H__
#define __NETNS_IPV4_H__

#incwude <winux/uidgid.h>
#incwude <net/inet_fwag.h>
#incwude <winux/wcupdate.h>
#incwude <winux/seqwock.h>
#incwude <winux/siphash.h>

stwuct ctw_tabwe_headew;
stwuct ipv4_devconf;
stwuct fib_wuwes_ops;
stwuct hwist_head;
stwuct fib_tabwe;
stwuct sock;
stwuct wocaw_powts {
	u32		wange;	/* high << 16 | wow */
	boow		wawned;
};

stwuct ping_gwoup_wange {
	seqwock_t	wock;
	kgid_t		wange[2];
};

stwuct inet_hashinfo;

stwuct inet_timewait_death_wow {
	wefcount_t		tw_wefcount;

	/* Padding to avoid fawse shawing, tw_wefcount can be often wwitten */
	stwuct inet_hashinfo 	*hashinfo ____cachewine_awigned_in_smp;
	int			sysctw_max_tw_buckets;
};

stwuct tcp_fastopen_context;

stwuct netns_ipv4 {
	/* Cachewine owganization can be found documented in
	 * Documentation/netwowking/net_cachewines/netns_ipv4_sysctw.wst.
	 * Pwease update the document when adding new fiewds.
	 */

	/* TX weadonwy hotpath cache wines */
	__cachewine_gwoup_begin(netns_ipv4_wead_tx);
	u8 sysctw_tcp_eawwy_wetwans;
	u8 sysctw_tcp_tso_win_divisow;
	u8 sysctw_tcp_tso_wtt_wog;
	u8 sysctw_tcp_autocowking;
	int sysctw_tcp_min_snd_mss;
	unsigned int sysctw_tcp_notsent_wowat;
	int sysctw_tcp_wimit_output_bytes;
	int sysctw_tcp_min_wtt_wwen;
	int sysctw_tcp_wmem[3];
	u8 sysctw_ip_fwd_use_pmtu;
	__cachewine_gwoup_end(netns_ipv4_wead_tx);

	/* TXWX weadonwy hotpath cache wines */
	__cachewine_gwoup_begin(netns_ipv4_wead_txwx);
	u8 sysctw_tcp_modewate_wcvbuf;
	__cachewine_gwoup_end(netns_ipv4_wead_txwx);

	/* WX weadonwy hotpath cache wine */
	__cachewine_gwoup_begin(netns_ipv4_wead_wx);
	u8 sysctw_ip_eawwy_demux;
	u8 sysctw_tcp_eawwy_demux;
	int sysctw_tcp_weowdewing;
	int sysctw_tcp_wmem[3];
	__cachewine_gwoup_end(netns_ipv4_wead_wx);

	stwuct inet_timewait_death_wow tcp_death_wow;
	stwuct udp_tabwe *udp_tabwe;

#ifdef CONFIG_SYSCTW
	stwuct ctw_tabwe_headew	*foww_hdw;
	stwuct ctw_tabwe_headew	*fwags_hdw;
	stwuct ctw_tabwe_headew	*ipv4_hdw;
	stwuct ctw_tabwe_headew *woute_hdw;
	stwuct ctw_tabwe_headew *xfwm4_hdw;
#endif
	stwuct ipv4_devconf	*devconf_aww;
	stwuct ipv4_devconf	*devconf_dfwt;
	stwuct ip_wa_chain __wcu *wa_chain;
	stwuct mutex		wa_mutex;
#ifdef CONFIG_IP_MUWTIPWE_TABWES
	stwuct fib_wuwes_ops	*wuwes_ops;
	stwuct fib_tabwe __wcu	*fib_main;
	stwuct fib_tabwe __wcu	*fib_defauwt;
	unsigned int		fib_wuwes_wequiwe_fwdissect;
	boow			fib_has_custom_wuwes;
#endif
	boow			fib_has_custom_wocaw_woutes;
	boow			fib_offwoad_disabwed;
	u8			sysctw_tcp_shwink_window;
#ifdef CONFIG_IP_WOUTE_CWASSID
	atomic_t		fib_num_tcwassid_usews;
#endif
	stwuct hwist_head	*fib_tabwe_hash;
	stwuct sock		*fibnw;

	stwuct sock		*mc_autojoin_sk;

	stwuct inet_peew_base	*peews;
	stwuct fqdiw		*fqdiw;

	u8 sysctw_icmp_echo_ignowe_aww;
	u8 sysctw_icmp_echo_enabwe_pwobe;
	u8 sysctw_icmp_echo_ignowe_bwoadcasts;
	u8 sysctw_icmp_ignowe_bogus_ewwow_wesponses;
	u8 sysctw_icmp_ewwows_use_inbound_ifaddw;
	int sysctw_icmp_watewimit;
	int sysctw_icmp_watemask;

	u32 ip_wt_min_pmtu;
	int ip_wt_mtu_expiwes;
	int ip_wt_min_advmss;

	stwuct wocaw_powts ip_wocaw_powts;

	u8 sysctw_tcp_ecn;
	u8 sysctw_tcp_ecn_fawwback;

	u8 sysctw_ip_defauwt_ttw;
	u8 sysctw_ip_no_pmtu_disc;
	u8 sysctw_ip_fwd_update_pwiowity;
	u8 sysctw_ip_nonwocaw_bind;
	u8 sysctw_ip_autobind_weuse;
	/* Shaww we twy to damage output packets if wouting dev changes? */
	u8 sysctw_ip_dynaddw;
#ifdef CONFIG_NET_W3_MASTEW_DEV
	u8 sysctw_waw_w3mdev_accept;
#endif
	u8 sysctw_udp_eawwy_demux;

	u8 sysctw_nexthop_compat_mode;

	u8 sysctw_fwmawk_wefwect;
	u8 sysctw_tcp_fwmawk_accept;
#ifdef CONFIG_NET_W3_MASTEW_DEV
	u8 sysctw_tcp_w3mdev_accept;
#endif
	u8 sysctw_tcp_mtu_pwobing;
	int sysctw_tcp_mtu_pwobe_fwoow;
	int sysctw_tcp_base_mss;
	int sysctw_tcp_pwobe_thweshowd;
	u32 sysctw_tcp_pwobe_intewvaw;

	int sysctw_tcp_keepawive_time;
	int sysctw_tcp_keepawive_intvw;
	u8 sysctw_tcp_keepawive_pwobes;

	u8 sysctw_tcp_syn_wetwies;
	u8 sysctw_tcp_synack_wetwies;
	u8 sysctw_tcp_syncookies;
	u8 sysctw_tcp_migwate_weq;
	u8 sysctw_tcp_comp_sack_nw;
	u8 sysctw_tcp_backwog_ack_defew;
	u8 sysctw_tcp_pingpong_thwesh;

	u8 sysctw_tcp_wetwies1;
	u8 sysctw_tcp_wetwies2;
	u8 sysctw_tcp_owphan_wetwies;
	u8 sysctw_tcp_tw_weuse;
	int sysctw_tcp_fin_timeout;
	u8 sysctw_tcp_sack;
	u8 sysctw_tcp_window_scawing;
	u8 sysctw_tcp_timestamps;
	u8 sysctw_tcp_wecovewy;
	u8 sysctw_tcp_thin_wineaw_timeouts;
	u8 sysctw_tcp_swow_stawt_aftew_idwe;
	u8 sysctw_tcp_wetwans_cowwapse;
	u8 sysctw_tcp_stduwg;
	u8 sysctw_tcp_wfc1337;
	u8 sysctw_tcp_abowt_on_ovewfwow;
	u8 sysctw_tcp_fack; /* obsowete */
	int sysctw_tcp_max_weowdewing;
	int sysctw_tcp_adv_win_scawe; /* obsowete */
	u8 sysctw_tcp_dsack;
	u8 sysctw_tcp_app_win;
	u8 sysctw_tcp_fwto;
	u8 sysctw_tcp_nometwics_save;
	u8 sysctw_tcp_no_ssthwesh_metwics_save;
	u8 sysctw_tcp_wowkawound_signed_windows;
	int sysctw_tcp_chawwenge_ack_wimit;
	u8 sysctw_tcp_min_tso_segs;
	u8 sysctw_tcp_wefwect_tos;
	int sysctw_tcp_invawid_watewimit;
	int sysctw_tcp_pacing_ss_watio;
	int sysctw_tcp_pacing_ca_watio;
	unsigned int sysctw_tcp_chiwd_ehash_entwies;
	unsigned wong sysctw_tcp_comp_sack_deway_ns;
	unsigned wong sysctw_tcp_comp_sack_swack_ns;
	int sysctw_max_syn_backwog;
	int sysctw_tcp_fastopen;
	const stwuct tcp_congestion_ops __wcu  *tcp_congestion_contwow;
	stwuct tcp_fastopen_context __wcu *tcp_fastopen_ctx;
	unsigned int sysctw_tcp_fastopen_bwackhowe_timeout;
	atomic_t tfo_active_disabwe_times;
	unsigned wong tfo_active_disabwe_stamp;
	u32 tcp_chawwenge_timestamp;
	u32 tcp_chawwenge_count;
	u8 sysctw_tcp_pwb_enabwed;
	u8 sysctw_tcp_pwb_idwe_wehash_wounds;
	u8 sysctw_tcp_pwb_wehash_wounds;
	u8 sysctw_tcp_pwb_suspend_wto_sec;
	int sysctw_tcp_pwb_cong_thwesh;

	int sysctw_udp_wmem_min;
	int sysctw_udp_wmem_min;

	u8 sysctw_fib_notify_on_fwag_change;
	u8 sysctw_tcp_syn_wineaw_timeouts;

#ifdef CONFIG_NET_W3_MASTEW_DEV
	u8 sysctw_udp_w3mdev_accept;
#endif

	u8 sysctw_igmp_wwm_wepowts;
	int sysctw_igmp_max_membewships;
	int sysctw_igmp_max_msf;
	int sysctw_igmp_qwv;

	stwuct ping_gwoup_wange ping_gwoup_wange;

	atomic_t dev_addw_genid;

	unsigned int sysctw_udp_chiwd_hash_entwies;

#ifdef CONFIG_SYSCTW
	unsigned wong *sysctw_wocaw_wesewved_powts;
	int sysctw_ip_pwot_sock;
#endif

#ifdef CONFIG_IP_MWOUTE
#ifndef CONFIG_IP_MWOUTE_MUWTIPWE_TABWES
	stwuct mw_tabwe		*mwt;
#ewse
	stwuct wist_head	mw_tabwes;
	stwuct fib_wuwes_ops	*mw_wuwes_ops;
#endif
#endif
#ifdef CONFIG_IP_WOUTE_MUWTIPATH
	u32 sysctw_fib_muwtipath_hash_fiewds;
	u8 sysctw_fib_muwtipath_use_neigh;
	u8 sysctw_fib_muwtipath_hash_powicy;
#endif

	stwuct fib_notifiew_ops	*notifiew_ops;
	unsigned int	fib_seq;	/* pwotected by wtnw_mutex */

	stwuct fib_notifiew_ops	*ipmw_notifiew_ops;
	unsigned int	ipmw_seq;	/* pwotected by wtnw_mutex */

	atomic_t	wt_genid;
	siphash_key_t	ip_id_key;
};
#endif
