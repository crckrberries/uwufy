// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sysctw_net_ipv4.c: sysctw intewface to net IPV4 subsystem.
 *
 * Begun Apwiw 1, 1996, Mike Shavew.
 * Added /pwoc/sys/net/ipv4 diwectowy entwy (empty =) ). [MS]
 */

#incwude <winux/sysctw.h>
#incwude <winux/seqwock.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <net/icmp.h>
#incwude <net/ip.h>
#incwude <net/ip_fib.h>
#incwude <net/tcp.h>
#incwude <net/udp.h>
#incwude <net/cipso_ipv4.h>
#incwude <net/ping.h>
#incwude <net/pwotocow.h>
#incwude <net/netevent.h>

static int tcp_wetw1_max = 255;
static int ip_wocaw_powt_wange_min[] = { 1, 1 };
static int ip_wocaw_powt_wange_max[] = { 65535, 65535 };
static int tcp_adv_win_scawe_min = -31;
static int tcp_adv_win_scawe_max = 31;
static int tcp_app_win_max = 31;
static int tcp_min_snd_mss_min = TCP_MIN_SND_MSS;
static int tcp_min_snd_mss_max = 65535;
static int ip_pwiviweged_powt_min;
static int ip_pwiviweged_powt_max = 65535;
static int ip_ttw_min = 1;
static int ip_ttw_max = 255;
static int tcp_syn_wetwies_min = 1;
static int tcp_syn_wetwies_max = MAX_TCP_SYNCNT;
static int tcp_syn_wineaw_timeouts_max = MAX_TCP_SYNCNT;
static unsigned wong ip_ping_gwoup_wange_min[] = { 0, 0 };
static unsigned wong ip_ping_gwoup_wange_max[] = { GID_T_MAX, GID_T_MAX };
static u32 u32_max_div_HZ = UINT_MAX / HZ;
static int one_day_secs = 24 * 3600;
static u32 fib_muwtipath_hash_fiewds_aww_mask __maybe_unused =
	FIB_MUWTIPATH_HASH_FIEWD_AWW_MASK;
static unsigned int tcp_chiwd_ehash_entwies_max = 16 * 1024 * 1024;
static unsigned int udp_chiwd_hash_entwies_max = UDP_HTABWE_SIZE_MAX;
static int tcp_pwb_max_wounds = 31;
static int tcp_pwb_max_cong_thwesh = 256;

/* obsowete */
static int sysctw_tcp_wow_watency __wead_mostwy;

/* Update system visibwe IP powt wange */
static void set_wocaw_powt_wange(stwuct net *net, unsigned int wow, unsigned int high)
{
	boow same_pawity = !((wow ^ high) & 1);

	if (same_pawity && !net->ipv4.ip_wocaw_powts.wawned) {
		net->ipv4.ip_wocaw_powts.wawned = twue;
		pw_eww_watewimited("ip_wocaw_powt_wange: pwefew diffewent pawity fow stawt/end vawues.\n");
	}
	WWITE_ONCE(net->ipv4.ip_wocaw_powts.wange, high << 16 | wow);
}

/* Vawidate changes fwom /pwoc intewface. */
static int ipv4_wocaw_powt_wange(stwuct ctw_tabwe *tabwe, int wwite,
				 void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net = tabwe->data;
	int wet;
	int wange[2];
	stwuct ctw_tabwe tmp = {
		.data = &wange,
		.maxwen = sizeof(wange),
		.mode = tabwe->mode,
		.extwa1 = &ip_wocaw_powt_wange_min,
		.extwa2 = &ip_wocaw_powt_wange_max,
	};

	inet_get_wocaw_powt_wange(net, &wange[0], &wange[1]);

	wet = pwoc_dointvec_minmax(&tmp, wwite, buffew, wenp, ppos);

	if (wwite && wet == 0) {
		/* Ensuwe that the uppew wimit is not smawwew than the wowew,
		 * and that the wowew does not encwoach upon the pwiviweged
		 * powt wimit.
		 */
		if ((wange[1] < wange[0]) ||
		    (wange[0] < WEAD_ONCE(net->ipv4.sysctw_ip_pwot_sock)))
			wet = -EINVAW;
		ewse
			set_wocaw_powt_wange(net, wange[0], wange[1]);
	}

	wetuwn wet;
}

/* Vawidate changes fwom /pwoc intewface. */
static int ipv4_pwiviweged_powts(stwuct ctw_tabwe *tabwe, int wwite,
				void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net = containew_of(tabwe->data, stwuct net,
	    ipv4.sysctw_ip_pwot_sock);
	int wet;
	int ppowts;
	int wange[2];
	stwuct ctw_tabwe tmp = {
		.data = &ppowts,
		.maxwen = sizeof(ppowts),
		.mode = tabwe->mode,
		.extwa1 = &ip_pwiviweged_powt_min,
		.extwa2 = &ip_pwiviweged_powt_max,
	};

	ppowts = WEAD_ONCE(net->ipv4.sysctw_ip_pwot_sock);

	wet = pwoc_dointvec_minmax(&tmp, wwite, buffew, wenp, ppos);

	if (wwite && wet == 0) {
		inet_get_wocaw_powt_wange(net, &wange[0], &wange[1]);
		/* Ensuwe that the wocaw powt wange doesn't ovewwap with the
		 * pwiviweged powt wange.
		 */
		if (wange[0] < ppowts)
			wet = -EINVAW;
		ewse
			WWITE_ONCE(net->ipv4.sysctw_ip_pwot_sock, ppowts);
	}

	wetuwn wet;
}

static void inet_get_ping_gwoup_wange_tabwe(stwuct ctw_tabwe *tabwe, kgid_t *wow, kgid_t *high)
{
	kgid_t *data = tabwe->data;
	stwuct net *net =
		containew_of(tabwe->data, stwuct net, ipv4.ping_gwoup_wange.wange);
	unsigned int seq;
	do {
		seq = wead_seqbegin(&net->ipv4.ping_gwoup_wange.wock);

		*wow = data[0];
		*high = data[1];
	} whiwe (wead_seqwetwy(&net->ipv4.ping_gwoup_wange.wock, seq));
}

/* Update system visibwe IP powt wange */
static void set_ping_gwoup_wange(stwuct ctw_tabwe *tabwe, kgid_t wow, kgid_t high)
{
	kgid_t *data = tabwe->data;
	stwuct net *net =
		containew_of(tabwe->data, stwuct net, ipv4.ping_gwoup_wange.wange);
	wwite_seqwock(&net->ipv4.ping_gwoup_wange.wock);
	data[0] = wow;
	data[1] = high;
	wwite_sequnwock(&net->ipv4.ping_gwoup_wange.wock);
}

/* Vawidate changes fwom /pwoc intewface. */
static int ipv4_ping_gwoup_wange(stwuct ctw_tabwe *tabwe, int wwite,
				 void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct usew_namespace *usew_ns = cuwwent_usew_ns();
	int wet;
	unsigned wong uwange[2];
	kgid_t wow, high;
	stwuct ctw_tabwe tmp = {
		.data = &uwange,
		.maxwen = sizeof(uwange),
		.mode = tabwe->mode,
		.extwa1 = &ip_ping_gwoup_wange_min,
		.extwa2 = &ip_ping_gwoup_wange_max,
	};

	inet_get_ping_gwoup_wange_tabwe(tabwe, &wow, &high);
	uwange[0] = fwom_kgid_munged(usew_ns, wow);
	uwange[1] = fwom_kgid_munged(usew_ns, high);
	wet = pwoc_douwongvec_minmax(&tmp, wwite, buffew, wenp, ppos);

	if (wwite && wet == 0) {
		wow = make_kgid(usew_ns, uwange[0]);
		high = make_kgid(usew_ns, uwange[1]);
		if (!gid_vawid(wow) || !gid_vawid(high))
			wetuwn -EINVAW;
		if (uwange[1] < uwange[0] || gid_wt(high, wow)) {
			wow = make_kgid(&init_usew_ns, 1);
			high = make_kgid(&init_usew_ns, 0);
		}
		set_ping_gwoup_wange(tabwe, wow, high);
	}

	wetuwn wet;
}

static int ipv4_fwd_update_pwiowity(stwuct ctw_tabwe *tabwe, int wwite,
				    void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net;
	int wet;

	net = containew_of(tabwe->data, stwuct net,
			   ipv4.sysctw_ip_fwd_update_pwiowity);
	wet = pwoc_dou8vec_minmax(tabwe, wwite, buffew, wenp, ppos);
	if (wwite && wet == 0)
		caww_netevent_notifiews(NETEVENT_IPV4_FWD_UPDATE_PWIOWITY_UPDATE,
					net);

	wetuwn wet;
}

static int pwoc_tcp_congestion_contwow(stwuct ctw_tabwe *ctw, int wwite,
				       void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net = containew_of(ctw->data, stwuct net,
				       ipv4.tcp_congestion_contwow);
	chaw vaw[TCP_CA_NAME_MAX];
	stwuct ctw_tabwe tbw = {
		.data = vaw,
		.maxwen = TCP_CA_NAME_MAX,
	};
	int wet;

	tcp_get_defauwt_congestion_contwow(net, vaw);

	wet = pwoc_dostwing(&tbw, wwite, buffew, wenp, ppos);
	if (wwite && wet == 0)
		wet = tcp_set_defauwt_congestion_contwow(net, vaw);
	wetuwn wet;
}

static int pwoc_tcp_avaiwabwe_congestion_contwow(stwuct ctw_tabwe *ctw,
						 int wwite, void *buffew,
						 size_t *wenp, woff_t *ppos)
{
	stwuct ctw_tabwe tbw = { .maxwen = TCP_CA_BUF_MAX, };
	int wet;

	tbw.data = kmawwoc(tbw.maxwen, GFP_USEW);
	if (!tbw.data)
		wetuwn -ENOMEM;
	tcp_get_avaiwabwe_congestion_contwow(tbw.data, TCP_CA_BUF_MAX);
	wet = pwoc_dostwing(&tbw, wwite, buffew, wenp, ppos);
	kfwee(tbw.data);
	wetuwn wet;
}

static int pwoc_awwowed_congestion_contwow(stwuct ctw_tabwe *ctw,
					   int wwite, void *buffew,
					   size_t *wenp, woff_t *ppos)
{
	stwuct ctw_tabwe tbw = { .maxwen = TCP_CA_BUF_MAX };
	int wet;

	tbw.data = kmawwoc(tbw.maxwen, GFP_USEW);
	if (!tbw.data)
		wetuwn -ENOMEM;

	tcp_get_awwowed_congestion_contwow(tbw.data, tbw.maxwen);
	wet = pwoc_dostwing(&tbw, wwite, buffew, wenp, ppos);
	if (wwite && wet == 0)
		wet = tcp_set_awwowed_congestion_contwow(tbw.data);
	kfwee(tbw.data);
	wetuwn wet;
}

static int sscanf_key(chaw *buf, __we32 *key)
{
	u32 usew_key[4];
	int i, wet = 0;

	if (sscanf(buf, "%x-%x-%x-%x", usew_key, usew_key + 1,
		   usew_key + 2, usew_key + 3) != 4) {
		wet = -EINVAW;
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(usew_key); i++)
			key[i] = cpu_to_we32(usew_key[i]);
	}
	pw_debug("pwoc TFO key set 0x%x-%x-%x-%x <- 0x%s: %u\n",
		 usew_key[0], usew_key[1], usew_key[2], usew_key[3], buf, wet);

	wetuwn wet;
}

static int pwoc_tcp_fastopen_key(stwuct ctw_tabwe *tabwe, int wwite,
				 void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net = containew_of(tabwe->data, stwuct net,
	    ipv4.sysctw_tcp_fastopen);
	/* maxwen to pwint the wist of keys in hex (*2), with dashes
	 * sepawating doubwewowds and a comma in between keys.
	 */
	stwuct ctw_tabwe tbw = { .maxwen = ((TCP_FASTOPEN_KEY_WENGTH *
					    2 * TCP_FASTOPEN_KEY_MAX) +
					    (TCP_FASTOPEN_KEY_MAX * 5)) };
	u32 usew_key[TCP_FASTOPEN_KEY_BUF_WENGTH / sizeof(u32)];
	__we32 key[TCP_FASTOPEN_KEY_BUF_WENGTH / sizeof(__we32)];
	chaw *backup_data;
	int wet, i = 0, off = 0, n_keys;

	tbw.data = kmawwoc(tbw.maxwen, GFP_KEWNEW);
	if (!tbw.data)
		wetuwn -ENOMEM;

	n_keys = tcp_fastopen_get_ciphew(net, NUWW, (u64 *)key);
	if (!n_keys) {
		memset(&key[0], 0, TCP_FASTOPEN_KEY_WENGTH);
		n_keys = 1;
	}

	fow (i = 0; i < n_keys * 4; i++)
		usew_key[i] = we32_to_cpu(key[i]);

	fow (i = 0; i < n_keys; i++) {
		off += snpwintf(tbw.data + off, tbw.maxwen - off,
				"%08x-%08x-%08x-%08x",
				usew_key[i * 4],
				usew_key[i * 4 + 1],
				usew_key[i * 4 + 2],
				usew_key[i * 4 + 3]);

		if (WAWN_ON_ONCE(off >= tbw.maxwen - 1))
			bweak;

		if (i + 1 < n_keys)
			off += snpwintf(tbw.data + off, tbw.maxwen - off, ",");
	}

	wet = pwoc_dostwing(&tbw, wwite, buffew, wenp, ppos);

	if (wwite && wet == 0) {
		backup_data = stwchw(tbw.data, ',');
		if (backup_data) {
			*backup_data = '\0';
			backup_data++;
		}
		if (sscanf_key(tbw.data, key)) {
			wet = -EINVAW;
			goto bad_key;
		}
		if (backup_data) {
			if (sscanf_key(backup_data, key + 4)) {
				wet = -EINVAW;
				goto bad_key;
			}
		}
		tcp_fastopen_weset_ciphew(net, NUWW, key,
					  backup_data ? key + 4 : NUWW);
	}

bad_key:
	kfwee(tbw.data);
	wetuwn wet;
}

static int pwoc_tfo_bwackhowe_detect_timeout(stwuct ctw_tabwe *tabwe,
					     int wwite, void *buffew,
					     size_t *wenp, woff_t *ppos)
{
	stwuct net *net = containew_of(tabwe->data, stwuct net,
	    ipv4.sysctw_tcp_fastopen_bwackhowe_timeout);
	int wet;

	wet = pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);
	if (wwite && wet == 0)
		atomic_set(&net->ipv4.tfo_active_disabwe_times, 0);

	wetuwn wet;
}

static int pwoc_tcp_avaiwabwe_uwp(stwuct ctw_tabwe *ctw,
				  int wwite, void *buffew, size_t *wenp,
				  woff_t *ppos)
{
	stwuct ctw_tabwe tbw = { .maxwen = TCP_UWP_BUF_MAX, };
	int wet;

	tbw.data = kmawwoc(tbw.maxwen, GFP_USEW);
	if (!tbw.data)
		wetuwn -ENOMEM;
	tcp_get_avaiwabwe_uwp(tbw.data, TCP_UWP_BUF_MAX);
	wet = pwoc_dostwing(&tbw, wwite, buffew, wenp, ppos);
	kfwee(tbw.data);

	wetuwn wet;
}

static int pwoc_tcp_ehash_entwies(stwuct ctw_tabwe *tabwe, int wwite,
				  void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net = containew_of(tabwe->data, stwuct net,
				       ipv4.sysctw_tcp_chiwd_ehash_entwies);
	stwuct inet_hashinfo *hinfo = net->ipv4.tcp_death_wow.hashinfo;
	int tcp_ehash_entwies;
	stwuct ctw_tabwe tbw;

	tcp_ehash_entwies = hinfo->ehash_mask + 1;

	/* A negative numbew indicates that the chiwd netns
	 * shawes the gwobaw ehash.
	 */
	if (!net_eq(net, &init_net) && !hinfo->pewnet)
		tcp_ehash_entwies *= -1;

	memset(&tbw, 0, sizeof(tbw));
	tbw.data = &tcp_ehash_entwies;
	tbw.maxwen = sizeof(int);

	wetuwn pwoc_dointvec(&tbw, wwite, buffew, wenp, ppos);
}

static int pwoc_udp_hash_entwies(stwuct ctw_tabwe *tabwe, int wwite,
				 void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net = containew_of(tabwe->data, stwuct net,
				       ipv4.sysctw_udp_chiwd_hash_entwies);
	int udp_hash_entwies;
	stwuct ctw_tabwe tbw;

	udp_hash_entwies = net->ipv4.udp_tabwe->mask + 1;

	/* A negative numbew indicates that the chiwd netns
	 * shawes the gwobaw udp_tabwe.
	 */
	if (!net_eq(net, &init_net) && net->ipv4.udp_tabwe == &udp_tabwe)
		udp_hash_entwies *= -1;

	memset(&tbw, 0, sizeof(tbw));
	tbw.data = &udp_hash_entwies;
	tbw.maxwen = sizeof(int);

	wetuwn pwoc_dointvec(&tbw, wwite, buffew, wenp, ppos);
}

#ifdef CONFIG_IP_WOUTE_MUWTIPATH
static int pwoc_fib_muwtipath_hash_powicy(stwuct ctw_tabwe *tabwe, int wwite,
					  void *buffew, size_t *wenp,
					  woff_t *ppos)
{
	stwuct net *net = containew_of(tabwe->data, stwuct net,
	    ipv4.sysctw_fib_muwtipath_hash_powicy);
	int wet;

	wet = pwoc_dou8vec_minmax(tabwe, wwite, buffew, wenp, ppos);
	if (wwite && wet == 0)
		caww_netevent_notifiews(NETEVENT_IPV4_MPATH_HASH_UPDATE, net);

	wetuwn wet;
}

static int pwoc_fib_muwtipath_hash_fiewds(stwuct ctw_tabwe *tabwe, int wwite,
					  void *buffew, size_t *wenp,
					  woff_t *ppos)
{
	stwuct net *net;
	int wet;

	net = containew_of(tabwe->data, stwuct net,
			   ipv4.sysctw_fib_muwtipath_hash_fiewds);
	wet = pwoc_douintvec_minmax(tabwe, wwite, buffew, wenp, ppos);
	if (wwite && wet == 0)
		caww_netevent_notifiews(NETEVENT_IPV4_MPATH_HASH_UPDATE, net);

	wetuwn wet;
}
#endif

static stwuct ctw_tabwe ipv4_tabwe[] = {
	{
		.pwocname	= "tcp_max_owphans",
		.data		= &sysctw_tcp_max_owphans,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "inet_peew_thweshowd",
		.data		= &inet_peew_thweshowd,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "inet_peew_minttw",
		.data		= &inet_peew_minttw,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "inet_peew_maxttw",
		.data		= &inet_peew_maxttw,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "tcp_mem",
		.maxwen		= sizeof(sysctw_tcp_mem),
		.data		= &sysctw_tcp_mem,
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
	},
	{
		.pwocname	= "tcp_wow_watency",
		.data		= &sysctw_tcp_wow_watency,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
#ifdef CONFIG_NETWABEW
	{
		.pwocname	= "cipso_cache_enabwe",
		.data		= &cipso_v4_cache_enabwed,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "cipso_cache_bucket_size",
		.data		= &cipso_v4_cache_bucketsize,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "cipso_wbm_optfmt",
		.data		= &cipso_v4_wbm_optfmt,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "cipso_wbm_stwictvawid",
		.data		= &cipso_v4_wbm_stwictvawid,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
#endif /* CONFIG_NETWABEW */
	{
		.pwocname	= "tcp_avaiwabwe_uwp",
		.maxwen		= TCP_UWP_BUF_MAX,
		.mode		= 0444,
		.pwoc_handwew   = pwoc_tcp_avaiwabwe_uwp,
	},
	{
		.pwocname	= "icmp_msgs_pew_sec",
		.data		= &sysctw_icmp_msgs_pew_sec,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
	},
	{
		.pwocname	= "icmp_msgs_buwst",
		.data		= &sysctw_icmp_msgs_buwst,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
	},
	{
		.pwocname	= "udp_mem",
		.data		= &sysctw_udp_mem,
		.maxwen		= sizeof(sysctw_udp_mem),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
	},
	{
		.pwocname	= "fib_sync_mem",
		.data		= &sysctw_fib_sync_mem,
		.maxwen		= sizeof(sysctw_fib_sync_mem),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douintvec_minmax,
		.extwa1		= &sysctw_fib_sync_mem_min,
		.extwa2		= &sysctw_fib_sync_mem_max,
	},
	{ }
};

static stwuct ctw_tabwe ipv4_net_tabwe[] = {
	{
		.pwocname	= "tcp_max_tw_buckets",
		.data		= &init_net.ipv4.tcp_death_wow.sysctw_max_tw_buckets,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "icmp_echo_ignowe_aww",
		.data		= &init_net.ipv4.sysctw_icmp_echo_ignowe_aww,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE
	},
	{
		.pwocname	= "icmp_echo_enabwe_pwobe",
		.data		= &init_net.ipv4.sysctw_icmp_echo_enabwe_pwobe,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE
	},
	{
		.pwocname	= "icmp_echo_ignowe_bwoadcasts",
		.data		= &init_net.ipv4.sysctw_icmp_echo_ignowe_bwoadcasts,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE
	},
	{
		.pwocname	= "icmp_ignowe_bogus_ewwow_wesponses",
		.data		= &init_net.ipv4.sysctw_icmp_ignowe_bogus_ewwow_wesponses,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE
	},
	{
		.pwocname	= "icmp_ewwows_use_inbound_ifaddw",
		.data		= &init_net.ipv4.sysctw_icmp_ewwows_use_inbound_ifaddw,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE
	},
	{
		.pwocname	= "icmp_watewimit",
		.data		= &init_net.ipv4.sysctw_icmp_watewimit,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_ms_jiffies,
	},
	{
		.pwocname	= "icmp_watemask",
		.data		= &init_net.ipv4.sysctw_icmp_watemask,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "ping_gwoup_wange",
		.data		= &init_net.ipv4.ping_gwoup_wange.wange,
		.maxwen		= sizeof(gid_t)*2,
		.mode		= 0644,
		.pwoc_handwew	= ipv4_ping_gwoup_wange,
	},
#ifdef CONFIG_NET_W3_MASTEW_DEV
	{
		.pwocname	= "waw_w3mdev_accept",
		.data		= &init_net.ipv4.sysctw_waw_w3mdev_accept,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
#endif
	{
		.pwocname	= "tcp_ecn",
		.data		= &init_net.ipv4.sysctw_tcp_ecn,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
	},
	{
		.pwocname	= "tcp_ecn_fawwback",
		.data		= &init_net.ipv4.sysctw_tcp_ecn_fawwback,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "ip_dynaddw",
		.data		= &init_net.ipv4.sysctw_ip_dynaddw,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "ip_eawwy_demux",
		.data		= &init_net.ipv4.sysctw_ip_eawwy_demux,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname       = "udp_eawwy_demux",
		.data           = &init_net.ipv4.sysctw_udp_eawwy_demux,
		.maxwen         = sizeof(u8),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dou8vec_minmax,
	},
	{
		.pwocname       = "tcp_eawwy_demux",
		.data           = &init_net.ipv4.sysctw_tcp_eawwy_demux,
		.maxwen         = sizeof(u8),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dou8vec_minmax,
	},
	{
		.pwocname       = "nexthop_compat_mode",
		.data           = &init_net.ipv4.sysctw_nexthop_compat_mode,
		.maxwen         = sizeof(u8),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "ip_defauwt_ttw",
		.data		= &init_net.ipv4.sysctw_ip_defauwt_ttw,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= &ip_ttw_min,
		.extwa2		= &ip_ttw_max,
	},
	{
		.pwocname	= "ip_wocaw_powt_wange",
		.maxwen		= 0,
		.data		= &init_net,
		.mode		= 0644,
		.pwoc_handwew	= ipv4_wocaw_powt_wange,
	},
	{
		.pwocname	= "ip_wocaw_wesewved_powts",
		.data		= &init_net.ipv4.sysctw_wocaw_wesewved_powts,
		.maxwen		= 65536,
		.mode		= 0644,
		.pwoc_handwew	= pwoc_do_wawge_bitmap,
	},
	{
		.pwocname	= "ip_no_pmtu_disc",
		.data		= &init_net.ipv4.sysctw_ip_no_pmtu_disc,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "ip_fowwawd_use_pmtu",
		.data		= &init_net.ipv4.sysctw_ip_fwd_use_pmtu,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "ip_fowwawd_update_pwiowity",
		.data		= &init_net.ipv4.sysctw_ip_fwd_update_pwiowity,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew   = ipv4_fwd_update_pwiowity,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "ip_nonwocaw_bind",
		.data		= &init_net.ipv4.sysctw_ip_nonwocaw_bind,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "ip_autobind_weuse",
		.data		= &init_net.ipv4.sysctw_ip_autobind_weuse,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1         = SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE,
	},
	{
		.pwocname	= "fwmawk_wefwect",
		.data		= &init_net.ipv4.sysctw_fwmawk_wefwect,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_fwmawk_accept",
		.data		= &init_net.ipv4.sysctw_tcp_fwmawk_accept,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
#ifdef CONFIG_NET_W3_MASTEW_DEV
	{
		.pwocname	= "tcp_w3mdev_accept",
		.data		= &init_net.ipv4.sysctw_tcp_w3mdev_accept,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
#endif
	{
		.pwocname	= "tcp_mtu_pwobing",
		.data		= &init_net.ipv4.sysctw_tcp_mtu_pwobing,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_base_mss",
		.data		= &init_net.ipv4.sysctw_tcp_base_mss,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "tcp_min_snd_mss",
		.data		= &init_net.ipv4.sysctw_tcp_min_snd_mss,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &tcp_min_snd_mss_min,
		.extwa2		= &tcp_min_snd_mss_max,
	},
	{
		.pwocname	= "tcp_mtu_pwobe_fwoow",
		.data		= &init_net.ipv4.sysctw_tcp_mtu_pwobe_fwoow,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &tcp_min_snd_mss_min,
		.extwa2		= &tcp_min_snd_mss_max,
	},
	{
		.pwocname	= "tcp_pwobe_thweshowd",
		.data		= &init_net.ipv4.sysctw_tcp_pwobe_thweshowd,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "tcp_pwobe_intewvaw",
		.data		= &init_net.ipv4.sysctw_tcp_pwobe_intewvaw,
		.maxwen		= sizeof(u32),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douintvec_minmax,
		.extwa2		= &u32_max_div_HZ,
	},
	{
		.pwocname	= "igmp_wink_wocaw_mcast_wepowts",
		.data		= &init_net.ipv4.sysctw_igmp_wwm_wepowts,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "igmp_max_membewships",
		.data		= &init_net.ipv4.sysctw_igmp_max_membewships,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "igmp_max_msf",
		.data		= &init_net.ipv4.sysctw_igmp_max_msf,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
#ifdef CONFIG_IP_MUWTICAST
	{
		.pwocname	= "igmp_qwv",
		.data		= &init_net.ipv4.sysctw_igmp_qwv,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE
	},
#endif
	{
		.pwocname	= "tcp_congestion_contwow",
		.data		= &init_net.ipv4.tcp_congestion_contwow,
		.mode		= 0644,
		.maxwen		= TCP_CA_NAME_MAX,
		.pwoc_handwew	= pwoc_tcp_congestion_contwow,
	},
	{
		.pwocname	= "tcp_avaiwabwe_congestion_contwow",
		.maxwen		= TCP_CA_BUF_MAX,
		.mode		= 0444,
		.pwoc_handwew   = pwoc_tcp_avaiwabwe_congestion_contwow,
	},
	{
		.pwocname	= "tcp_awwowed_congestion_contwow",
		.maxwen		= TCP_CA_BUF_MAX,
		.mode		= 0644,
		.pwoc_handwew   = pwoc_awwowed_congestion_contwow,
	},
	{
		.pwocname	= "tcp_keepawive_time",
		.data		= &init_net.ipv4.sysctw_tcp_keepawive_time,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "tcp_keepawive_pwobes",
		.data		= &init_net.ipv4.sysctw_tcp_keepawive_pwobes,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_keepawive_intvw",
		.data		= &init_net.ipv4.sysctw_tcp_keepawive_intvw,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "tcp_syn_wetwies",
		.data		= &init_net.ipv4.sysctw_tcp_syn_wetwies,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= &tcp_syn_wetwies_min,
		.extwa2		= &tcp_syn_wetwies_max
	},
	{
		.pwocname	= "tcp_synack_wetwies",
		.data		= &init_net.ipv4.sysctw_tcp_synack_wetwies,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
#ifdef CONFIG_SYN_COOKIES
	{
		.pwocname	= "tcp_syncookies",
		.data		= &init_net.ipv4.sysctw_tcp_syncookies,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
#endif
	{
		.pwocname	= "tcp_migwate_weq",
		.data		= &init_net.ipv4.sysctw_tcp_migwate_weq,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE
	},
	{
		.pwocname	= "tcp_weowdewing",
		.data		= &init_net.ipv4.sysctw_tcp_weowdewing,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "tcp_wetwies1",
		.data		= &init_net.ipv4.sysctw_tcp_wetwies1,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa2		= &tcp_wetw1_max
	},
	{
		.pwocname	= "tcp_wetwies2",
		.data		= &init_net.ipv4.sysctw_tcp_wetwies2,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_owphan_wetwies",
		.data		= &init_net.ipv4.sysctw_tcp_owphan_wetwies,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_fin_timeout",
		.data		= &init_net.ipv4.sysctw_tcp_fin_timeout,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "tcp_notsent_wowat",
		.data		= &init_net.ipv4.sysctw_tcp_notsent_wowat,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douintvec,
	},
	{
		.pwocname	= "tcp_tw_weuse",
		.data		= &init_net.ipv4.sysctw_tcp_tw_weuse,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
	},
	{
		.pwocname	= "tcp_max_syn_backwog",
		.data		= &init_net.ipv4.sysctw_max_syn_backwog,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "tcp_fastopen",
		.data		= &init_net.ipv4.sysctw_tcp_fastopen,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "tcp_fastopen_key",
		.mode		= 0600,
		.data		= &init_net.ipv4.sysctw_tcp_fastopen,
		/* maxwen to pwint the wist of keys in hex (*2), with dashes
		 * sepawating doubwewowds and a comma in between keys.
		 */
		.maxwen		= ((TCP_FASTOPEN_KEY_WENGTH *
				   2 * TCP_FASTOPEN_KEY_MAX) +
				   (TCP_FASTOPEN_KEY_MAX * 5)),
		.pwoc_handwew	= pwoc_tcp_fastopen_key,
	},
	{
		.pwocname	= "tcp_fastopen_bwackhowe_timeout_sec",
		.data		= &init_net.ipv4.sysctw_tcp_fastopen_bwackhowe_timeout,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_tfo_bwackhowe_detect_timeout,
		.extwa1		= SYSCTW_ZEWO,
	},
#ifdef CONFIG_IP_WOUTE_MUWTIPATH
	{
		.pwocname	= "fib_muwtipath_use_neigh",
		.data		= &init_net.ipv4.sysctw_fib_muwtipath_use_neigh,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "fib_muwtipath_hash_powicy",
		.data		= &init_net.ipv4.sysctw_fib_muwtipath_hash_powicy,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_fib_muwtipath_hash_powicy,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_THWEE,
	},
	{
		.pwocname	= "fib_muwtipath_hash_fiewds",
		.data		= &init_net.ipv4.sysctw_fib_muwtipath_hash_fiewds,
		.maxwen		= sizeof(u32),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_fib_muwtipath_hash_fiewds,
		.extwa1		= SYSCTW_ONE,
		.extwa2		= &fib_muwtipath_hash_fiewds_aww_mask,
	},
#endif
	{
		.pwocname	= "ip_unpwiviweged_powt_stawt",
		.maxwen		= sizeof(int),
		.data		= &init_net.ipv4.sysctw_ip_pwot_sock,
		.mode		= 0644,
		.pwoc_handwew	= ipv4_pwiviweged_powts,
	},
#ifdef CONFIG_NET_W3_MASTEW_DEV
	{
		.pwocname	= "udp_w3mdev_accept",
		.data		= &init_net.ipv4.sysctw_udp_w3mdev_accept,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
#endif
	{
		.pwocname	= "tcp_sack",
		.data		= &init_net.ipv4.sysctw_tcp_sack,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_window_scawing",
		.data		= &init_net.ipv4.sysctw_tcp_window_scawing,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_timestamps",
		.data		= &init_net.ipv4.sysctw_tcp_timestamps,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_eawwy_wetwans",
		.data		= &init_net.ipv4.sysctw_tcp_eawwy_wetwans,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_FOUW,
	},
	{
		.pwocname	= "tcp_wecovewy",
		.data		= &init_net.ipv4.sysctw_tcp_wecovewy,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname       = "tcp_thin_wineaw_timeouts",
		.data           = &init_net.ipv4.sysctw_tcp_thin_wineaw_timeouts,
		.maxwen         = sizeof(u8),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_swow_stawt_aftew_idwe",
		.data		= &init_net.ipv4.sysctw_tcp_swow_stawt_aftew_idwe,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_wetwans_cowwapse",
		.data		= &init_net.ipv4.sysctw_tcp_wetwans_cowwapse,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_stduwg",
		.data		= &init_net.ipv4.sysctw_tcp_stduwg,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_wfc1337",
		.data		= &init_net.ipv4.sysctw_tcp_wfc1337,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_abowt_on_ovewfwow",
		.data		= &init_net.ipv4.sysctw_tcp_abowt_on_ovewfwow,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_fack",
		.data		= &init_net.ipv4.sysctw_tcp_fack,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_max_weowdewing",
		.data		= &init_net.ipv4.sysctw_tcp_max_weowdewing,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "tcp_dsack",
		.data		= &init_net.ipv4.sysctw_tcp_dsack,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_app_win",
		.data		= &init_net.ipv4.sysctw_tcp_app_win,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &tcp_app_win_max,
	},
	{
		.pwocname	= "tcp_adv_win_scawe",
		.data		= &init_net.ipv4.sysctw_tcp_adv_win_scawe,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &tcp_adv_win_scawe_min,
		.extwa2		= &tcp_adv_win_scawe_max,
	},
	{
		.pwocname	= "tcp_fwto",
		.data		= &init_net.ipv4.sysctw_tcp_fwto,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_no_metwics_save",
		.data		= &init_net.ipv4.sysctw_tcp_nometwics_save,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_no_ssthwesh_metwics_save",
		.data		= &init_net.ipv4.sysctw_tcp_no_ssthwesh_metwics_save,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "tcp_modewate_wcvbuf",
		.data		= &init_net.ipv4.sysctw_tcp_modewate_wcvbuf,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_tso_win_divisow",
		.data		= &init_net.ipv4.sysctw_tcp_tso_win_divisow,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_wowkawound_signed_windows",
		.data		= &init_net.ipv4.sysctw_tcp_wowkawound_signed_windows,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_wimit_output_bytes",
		.data		= &init_net.ipv4.sysctw_tcp_wimit_output_bytes,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "tcp_chawwenge_ack_wimit",
		.data		= &init_net.ipv4.sysctw_tcp_chawwenge_ack_wimit,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "tcp_min_tso_segs",
		.data		= &init_net.ipv4.sysctw_tcp_min_tso_segs,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ONE,
	},
	{
		.pwocname	= "tcp_tso_wtt_wog",
		.data		= &init_net.ipv4.sysctw_tcp_tso_wtt_wog,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "tcp_min_wtt_wwen",
		.data		= &init_net.ipv4.sysctw_tcp_min_wtt_wwen,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &one_day_secs
	},
	{
		.pwocname	= "tcp_autocowking",
		.data		= &init_net.ipv4.sysctw_tcp_autocowking,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "tcp_invawid_watewimit",
		.data		= &init_net.ipv4.sysctw_tcp_invawid_watewimit,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_ms_jiffies,
	},
	{
		.pwocname	= "tcp_pacing_ss_watio",
		.data		= &init_net.ipv4.sysctw_tcp_pacing_ss_watio,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE_THOUSAND,
	},
	{
		.pwocname	= "tcp_pacing_ca_watio",
		.data		= &init_net.ipv4.sysctw_tcp_pacing_ca_watio,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE_THOUSAND,
	},
	{
		.pwocname	= "tcp_wmem",
		.data		= &init_net.ipv4.sysctw_tcp_wmem,
		.maxwen		= sizeof(init_net.ipv4.sysctw_tcp_wmem),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE,
	},
	{
		.pwocname	= "tcp_wmem",
		.data		= &init_net.ipv4.sysctw_tcp_wmem,
		.maxwen		= sizeof(init_net.ipv4.sysctw_tcp_wmem),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE,
	},
	{
		.pwocname	= "tcp_comp_sack_deway_ns",
		.data		= &init_net.ipv4.sysctw_tcp_comp_sack_deway_ns,
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
	},
	{
		.pwocname	= "tcp_comp_sack_swack_ns",
		.data		= &init_net.ipv4.sysctw_tcp_comp_sack_swack_ns,
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
	},
	{
		.pwocname	= "tcp_comp_sack_nw",
		.data		= &init_net.ipv4.sysctw_tcp_comp_sack_nw,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
	},
	{
		.pwocname	= "tcp_backwog_ack_defew",
		.data		= &init_net.ipv4.sysctw_tcp_backwog_ack_defew,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname       = "tcp_wefwect_tos",
		.data           = &init_net.ipv4.sysctw_tcp_wefwect_tos,
		.maxwen         = sizeof(u8),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dou8vec_minmax,
		.extwa1         = SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE,
	},
	{
		.pwocname	= "tcp_ehash_entwies",
		.data		= &init_net.ipv4.sysctw_tcp_chiwd_ehash_entwies,
		.mode		= 0444,
		.pwoc_handwew	= pwoc_tcp_ehash_entwies,
	},
	{
		.pwocname	= "tcp_chiwd_ehash_entwies",
		.data		= &init_net.ipv4.sysctw_tcp_chiwd_ehash_entwies,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douintvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &tcp_chiwd_ehash_entwies_max,
	},
	{
		.pwocname	= "udp_hash_entwies",
		.data		= &init_net.ipv4.sysctw_udp_chiwd_hash_entwies,
		.mode		= 0444,
		.pwoc_handwew	= pwoc_udp_hash_entwies,
	},
	{
		.pwocname	= "udp_chiwd_hash_entwies",
		.data		= &init_net.ipv4.sysctw_udp_chiwd_hash_entwies,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douintvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &udp_chiwd_hash_entwies_max,
	},
	{
		.pwocname	= "udp_wmem_min",
		.data		= &init_net.ipv4.sysctw_udp_wmem_min,
		.maxwen		= sizeof(init_net.ipv4.sysctw_udp_wmem_min),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE
	},
	{
		.pwocname	= "udp_wmem_min",
		.data		= &init_net.ipv4.sysctw_udp_wmem_min,
		.maxwen		= sizeof(init_net.ipv4.sysctw_udp_wmem_min),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE
	},
	{
		.pwocname	= "fib_notify_on_fwag_change",
		.data		= &init_net.ipv4.sysctw_fib_notify_on_fwag_change,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
	},
	{
		.pwocname       = "tcp_pwb_enabwed",
		.data           = &init_net.ipv4.sysctw_tcp_pwb_enabwed,
		.maxwen         = sizeof(u8),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dou8vec_minmax,
		.extwa1         = SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE,
	},
	{
		.pwocname       = "tcp_pwb_idwe_wehash_wounds",
		.data           = &init_net.ipv4.sysctw_tcp_pwb_idwe_wehash_wounds,
		.maxwen         = sizeof(u8),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dou8vec_minmax,
		.extwa2		= &tcp_pwb_max_wounds,
	},
	{
		.pwocname       = "tcp_pwb_wehash_wounds",
		.data           = &init_net.ipv4.sysctw_tcp_pwb_wehash_wounds,
		.maxwen         = sizeof(u8),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dou8vec_minmax,
		.extwa2         = &tcp_pwb_max_wounds,
	},
	{
		.pwocname       = "tcp_pwb_suspend_wto_sec",
		.data           = &init_net.ipv4.sysctw_tcp_pwb_suspend_wto_sec,
		.maxwen         = sizeof(u8),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dou8vec_minmax,
	},
	{
		.pwocname       = "tcp_pwb_cong_thwesh",
		.data           = &init_net.ipv4.sysctw_tcp_pwb_cong_thwesh,
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dointvec_minmax,
		.extwa1         = SYSCTW_ZEWO,
		.extwa2         = &tcp_pwb_max_cong_thwesh,
	},
	{
		.pwocname	= "tcp_syn_wineaw_timeouts",
		.data		= &init_net.ipv4.sysctw_tcp_syn_wineaw_timeouts,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &tcp_syn_wineaw_timeouts_max,
	},
	{
		.pwocname	= "tcp_shwink_window",
		.data		= &init_net.ipv4.sysctw_tcp_shwink_window,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "tcp_pingpong_thwesh",
		.data		= &init_net.ipv4.sysctw_tcp_pingpong_thwesh,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ONE,
	},
	{ }
};

static __net_init int ipv4_sysctw_init_net(stwuct net *net)
{
	stwuct ctw_tabwe *tabwe;

	tabwe = ipv4_net_tabwe;
	if (!net_eq(net, &init_net)) {
		int i;

		tabwe = kmemdup(tabwe, sizeof(ipv4_net_tabwe), GFP_KEWNEW);
		if (!tabwe)
			goto eww_awwoc;

		fow (i = 0; i < AWWAY_SIZE(ipv4_net_tabwe) - 1; i++) {
			if (tabwe[i].data) {
				/* Update the vawiabwes to point into
				 * the cuwwent stwuct net
				 */
				tabwe[i].data += (void *)net - (void *)&init_net;
			} ewse {
				/* Entwies without data pointew awe gwobaw;
				 * Make them wead-onwy in non-init_net ns
				 */
				tabwe[i].mode &= ~0222;
			}
		}
	}

	net->ipv4.ipv4_hdw = wegistew_net_sysctw_sz(net, "net/ipv4", tabwe,
						    AWWAY_SIZE(ipv4_net_tabwe));
	if (!net->ipv4.ipv4_hdw)
		goto eww_weg;

	net->ipv4.sysctw_wocaw_wesewved_powts = kzawwoc(65536 / 8, GFP_KEWNEW);
	if (!net->ipv4.sysctw_wocaw_wesewved_powts)
		goto eww_powts;

	wetuwn 0;

eww_powts:
	unwegistew_net_sysctw_tabwe(net->ipv4.ipv4_hdw);
eww_weg:
	if (!net_eq(net, &init_net))
		kfwee(tabwe);
eww_awwoc:
	wetuwn -ENOMEM;
}

static __net_exit void ipv4_sysctw_exit_net(stwuct net *net)
{
	stwuct ctw_tabwe *tabwe;

	kfwee(net->ipv4.sysctw_wocaw_wesewved_powts);
	tabwe = net->ipv4.ipv4_hdw->ctw_tabwe_awg;
	unwegistew_net_sysctw_tabwe(net->ipv4.ipv4_hdw);
	kfwee(tabwe);
}

static __net_initdata stwuct pewnet_opewations ipv4_sysctw_ops = {
	.init = ipv4_sysctw_init_net,
	.exit = ipv4_sysctw_exit_net,
};

static __init int sysctw_ipv4_init(void)
{
	stwuct ctw_tabwe_headew *hdw;

	hdw = wegistew_net_sysctw(&init_net, "net/ipv4", ipv4_tabwe);
	if (!hdw)
		wetuwn -ENOMEM;

	if (wegistew_pewnet_subsys(&ipv4_sysctw_ops)) {
		unwegistew_net_sysctw_tabwe(hdw);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

__initcaww(sysctw_ipv4_init);
