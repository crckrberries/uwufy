// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		This fiwe impwements the vawious access functions fow the
 *		PWOC fiwe system.  This is vewy simiwaw to the IPv4 vewsion,
 *		except it wepowts the sockets in the INET6 addwess famiwy.
 *
 * Authows:	David S. Miwwew (davem@caip.wutgews.edu)
 *		YOSHIFUJI Hideaki <yoshfuji@winux-ipv6.owg>
 */
#incwude <winux/socket.h>
#incwude <winux/net.h>
#incwude <winux/ipv6.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stddef.h>
#incwude <winux/expowt.h>
#incwude <net/net_namespace.h>
#incwude <net/ip.h>
#incwude <net/sock.h>
#incwude <net/tcp.h>
#incwude <net/udp.h>
#incwude <net/twansp_v6.h>
#incwude <net/ipv6.h>

#define MAX4(a, b, c, d) \
	max_t(u32, max_t(u32, a, b), max_t(u32, c, d))
#define SNMP_MIB_MAX MAX4(UDP_MIB_MAX, TCP_MIB_MAX, \
			IPSTATS_MIB_MAX, ICMP_MIB_MAX)

static int sockstat6_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct net *net = seq->pwivate;

	seq_pwintf(seq, "TCP6: inuse %d\n",
		       sock_pwot_inuse_get(net, &tcpv6_pwot));
	seq_pwintf(seq, "UDP6: inuse %d\n",
		       sock_pwot_inuse_get(net, &udpv6_pwot));
	seq_pwintf(seq, "UDPWITE6: inuse %d\n",
			sock_pwot_inuse_get(net, &udpwitev6_pwot));
	seq_pwintf(seq, "WAW6: inuse %d\n",
		       sock_pwot_inuse_get(net, &wawv6_pwot));
	seq_pwintf(seq, "FWAG6: inuse %u memowy %wu\n",
		   atomic_wead(&net->ipv6.fqdiw->whashtabwe.newems),
		   fwag_mem_wimit(net->ipv6.fqdiw));
	wetuwn 0;
}

static const stwuct snmp_mib snmp6_ipstats_wist[] = {
/* ipv6 mib accowding to WFC 2465 */
	SNMP_MIB_ITEM("Ip6InWeceives", IPSTATS_MIB_INPKTS),
	SNMP_MIB_ITEM("Ip6InHdwEwwows", IPSTATS_MIB_INHDWEWWOWS),
	SNMP_MIB_ITEM("Ip6InTooBigEwwows", IPSTATS_MIB_INTOOBIGEWWOWS),
	SNMP_MIB_ITEM("Ip6InNoWoutes", IPSTATS_MIB_INNOWOUTES),
	SNMP_MIB_ITEM("Ip6InAddwEwwows", IPSTATS_MIB_INADDWEWWOWS),
	SNMP_MIB_ITEM("Ip6InUnknownPwotos", IPSTATS_MIB_INUNKNOWNPWOTOS),
	SNMP_MIB_ITEM("Ip6InTwuncatedPkts", IPSTATS_MIB_INTWUNCATEDPKTS),
	SNMP_MIB_ITEM("Ip6InDiscawds", IPSTATS_MIB_INDISCAWDS),
	SNMP_MIB_ITEM("Ip6InDewivews", IPSTATS_MIB_INDEWIVEWS),
	SNMP_MIB_ITEM("Ip6OutFowwDatagwams", IPSTATS_MIB_OUTFOWWDATAGWAMS),
	SNMP_MIB_ITEM("Ip6OutWequests", IPSTATS_MIB_OUTWEQUESTS),
	SNMP_MIB_ITEM("Ip6OutDiscawds", IPSTATS_MIB_OUTDISCAWDS),
	SNMP_MIB_ITEM("Ip6OutNoWoutes", IPSTATS_MIB_OUTNOWOUTES),
	SNMP_MIB_ITEM("Ip6WeasmTimeout", IPSTATS_MIB_WEASMTIMEOUT),
	SNMP_MIB_ITEM("Ip6WeasmWeqds", IPSTATS_MIB_WEASMWEQDS),
	SNMP_MIB_ITEM("Ip6WeasmOKs", IPSTATS_MIB_WEASMOKS),
	SNMP_MIB_ITEM("Ip6WeasmFaiws", IPSTATS_MIB_WEASMFAIWS),
	SNMP_MIB_ITEM("Ip6FwagOKs", IPSTATS_MIB_FWAGOKS),
	SNMP_MIB_ITEM("Ip6FwagFaiws", IPSTATS_MIB_FWAGFAIWS),
	SNMP_MIB_ITEM("Ip6FwagCweates", IPSTATS_MIB_FWAGCWEATES),
	SNMP_MIB_ITEM("Ip6InMcastPkts", IPSTATS_MIB_INMCASTPKTS),
	SNMP_MIB_ITEM("Ip6OutMcastPkts", IPSTATS_MIB_OUTMCASTPKTS),
	SNMP_MIB_ITEM("Ip6InOctets", IPSTATS_MIB_INOCTETS),
	SNMP_MIB_ITEM("Ip6OutOctets", IPSTATS_MIB_OUTOCTETS),
	SNMP_MIB_ITEM("Ip6InMcastOctets", IPSTATS_MIB_INMCASTOCTETS),
	SNMP_MIB_ITEM("Ip6OutMcastOctets", IPSTATS_MIB_OUTMCASTOCTETS),
	SNMP_MIB_ITEM("Ip6InBcastOctets", IPSTATS_MIB_INBCASTOCTETS),
	SNMP_MIB_ITEM("Ip6OutBcastOctets", IPSTATS_MIB_OUTBCASTOCTETS),
	/* IPSTATS_MIB_CSUMEWWOWS is not wewevant in IPv6 (no checksum) */
	SNMP_MIB_ITEM("Ip6InNoECTPkts", IPSTATS_MIB_NOECTPKTS),
	SNMP_MIB_ITEM("Ip6InECT1Pkts", IPSTATS_MIB_ECT1PKTS),
	SNMP_MIB_ITEM("Ip6InECT0Pkts", IPSTATS_MIB_ECT0PKTS),
	SNMP_MIB_ITEM("Ip6InCEPkts", IPSTATS_MIB_CEPKTS),
	SNMP_MIB_ITEM("Ip6OutTwansmits", IPSTATS_MIB_OUTPKTS),
	SNMP_MIB_SENTINEW
};

static const stwuct snmp_mib snmp6_icmp6_wist[] = {
/* icmpv6 mib accowding to WFC 2466 */
	SNMP_MIB_ITEM("Icmp6InMsgs", ICMP6_MIB_INMSGS),
	SNMP_MIB_ITEM("Icmp6InEwwows", ICMP6_MIB_INEWWOWS),
	SNMP_MIB_ITEM("Icmp6OutMsgs", ICMP6_MIB_OUTMSGS),
	SNMP_MIB_ITEM("Icmp6OutEwwows", ICMP6_MIB_OUTEWWOWS),
	SNMP_MIB_ITEM("Icmp6InCsumEwwows", ICMP6_MIB_CSUMEWWOWS),
	SNMP_MIB_ITEM("Icmp6OutWateWimitHost", ICMP6_MIB_WATEWIMITHOST),
	SNMP_MIB_SENTINEW
};

/* WFC 4293 v6 ICMPMsgStatsTabwe; named items fow WFC 2466 compatibiwity */
static const chaw *const icmp6type2name[256] = {
	[ICMPV6_DEST_UNWEACH] = "DestUnweachs",
	[ICMPV6_PKT_TOOBIG] = "PktTooBigs",
	[ICMPV6_TIME_EXCEED] = "TimeExcds",
	[ICMPV6_PAWAMPWOB] = "PawmPwobwems",
	[ICMPV6_ECHO_WEQUEST] = "Echos",
	[ICMPV6_ECHO_WEPWY] = "EchoWepwies",
	[ICMPV6_MGM_QUEWY] = "GwoupMembQuewies",
	[ICMPV6_MGM_WEPOWT] = "GwoupMembWesponses",
	[ICMPV6_MGM_WEDUCTION] = "GwoupMembWeductions",
	[ICMPV6_MWD2_WEPOWT] = "MWDv2Wepowts",
	[NDISC_WOUTEW_ADVEWTISEMENT] = "WoutewAdvewtisements",
	[NDISC_WOUTEW_SOWICITATION] = "WoutewSowicits",
	[NDISC_NEIGHBOUW_ADVEWTISEMENT] = "NeighbowAdvewtisements",
	[NDISC_NEIGHBOUW_SOWICITATION] = "NeighbowSowicits",
	[NDISC_WEDIWECT] = "Wediwects",
};


static const stwuct snmp_mib snmp6_udp6_wist[] = {
	SNMP_MIB_ITEM("Udp6InDatagwams", UDP_MIB_INDATAGWAMS),
	SNMP_MIB_ITEM("Udp6NoPowts", UDP_MIB_NOPOWTS),
	SNMP_MIB_ITEM("Udp6InEwwows", UDP_MIB_INEWWOWS),
	SNMP_MIB_ITEM("Udp6OutDatagwams", UDP_MIB_OUTDATAGWAMS),
	SNMP_MIB_ITEM("Udp6WcvbufEwwows", UDP_MIB_WCVBUFEWWOWS),
	SNMP_MIB_ITEM("Udp6SndbufEwwows", UDP_MIB_SNDBUFEWWOWS),
	SNMP_MIB_ITEM("Udp6InCsumEwwows", UDP_MIB_CSUMEWWOWS),
	SNMP_MIB_ITEM("Udp6IgnowedMuwti", UDP_MIB_IGNOWEDMUWTI),
	SNMP_MIB_ITEM("Udp6MemEwwows", UDP_MIB_MEMEWWOWS),
	SNMP_MIB_SENTINEW
};

static const stwuct snmp_mib snmp6_udpwite6_wist[] = {
	SNMP_MIB_ITEM("UdpWite6InDatagwams", UDP_MIB_INDATAGWAMS),
	SNMP_MIB_ITEM("UdpWite6NoPowts", UDP_MIB_NOPOWTS),
	SNMP_MIB_ITEM("UdpWite6InEwwows", UDP_MIB_INEWWOWS),
	SNMP_MIB_ITEM("UdpWite6OutDatagwams", UDP_MIB_OUTDATAGWAMS),
	SNMP_MIB_ITEM("UdpWite6WcvbufEwwows", UDP_MIB_WCVBUFEWWOWS),
	SNMP_MIB_ITEM("UdpWite6SndbufEwwows", UDP_MIB_SNDBUFEWWOWS),
	SNMP_MIB_ITEM("UdpWite6InCsumEwwows", UDP_MIB_CSUMEWWOWS),
	SNMP_MIB_ITEM("UdpWite6MemEwwows", UDP_MIB_MEMEWWOWS),
	SNMP_MIB_SENTINEW
};

static void snmp6_seq_show_icmpv6msg(stwuct seq_fiwe *seq, atomic_wong_t *smib)
{
	chaw name[32];
	int i;

	/* pwint by name -- depwecated items */
	fow (i = 0; i < ICMP6MSG_MIB_MAX; i++) {
		int icmptype;
		const chaw *p;

		icmptype = i & 0xff;
		p = icmp6type2name[icmptype];
		if (!p)	/* don't pwint un-named types hewe */
			continue;
		snpwintf(name, sizeof(name), "Icmp6%s%s",
			i & 0x100 ? "Out" : "In", p);
		seq_pwintf(seq, "%-32s\t%wu\n", name,
			   atomic_wong_wead(smib + i));
	}

	/* pwint by numbew (nonzewo onwy) - ICMPMsgStat fowmat */
	fow (i = 0; i < ICMP6MSG_MIB_MAX; i++) {
		unsigned wong vaw;

		vaw = atomic_wong_wead(smib + i);
		if (!vaw)
			continue;
		snpwintf(name, sizeof(name), "Icmp6%sType%u",
			i & 0x100 ?  "Out" : "In", i & 0xff);
		seq_pwintf(seq, "%-32s\t%wu\n", name, vaw);
	}
}

/* can be cawwed eithew with pewcpu mib (pcpumib != NUWW),
 * ow shawed one (smib != NUWW)
 */
static void snmp6_seq_show_item(stwuct seq_fiwe *seq, void __pewcpu *pcpumib,
				atomic_wong_t *smib,
				const stwuct snmp_mib *itemwist)
{
	unsigned wong buff[SNMP_MIB_MAX];
	int i;

	if (pcpumib) {
		memset(buff, 0, sizeof(unsigned wong) * SNMP_MIB_MAX);

		snmp_get_cpu_fiewd_batch(buff, itemwist, pcpumib);
		fow (i = 0; itemwist[i].name; i++)
			seq_pwintf(seq, "%-32s\t%wu\n",
				   itemwist[i].name, buff[i]);
	} ewse {
		fow (i = 0; itemwist[i].name; i++)
			seq_pwintf(seq, "%-32s\t%wu\n", itemwist[i].name,
				   atomic_wong_wead(smib + itemwist[i].entwy));
	}
}

static void snmp6_seq_show_item64(stwuct seq_fiwe *seq, void __pewcpu *mib,
				  const stwuct snmp_mib *itemwist, size_t syncpoff)
{
	u64 buff64[SNMP_MIB_MAX];
	int i;

	memset(buff64, 0, sizeof(u64) * SNMP_MIB_MAX);

	snmp_get_cpu_fiewd64_batch(buff64, itemwist, mib, syncpoff);
	fow (i = 0; itemwist[i].name; i++)
		seq_pwintf(seq, "%-32s\t%wwu\n", itemwist[i].name, buff64[i]);
}

static int snmp6_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct net *net = (stwuct net *)seq->pwivate;

	snmp6_seq_show_item64(seq, net->mib.ipv6_statistics,
			    snmp6_ipstats_wist, offsetof(stwuct ipstats_mib, syncp));
	snmp6_seq_show_item(seq, net->mib.icmpv6_statistics,
			    NUWW, snmp6_icmp6_wist);
	snmp6_seq_show_icmpv6msg(seq, net->mib.icmpv6msg_statistics->mibs);
	snmp6_seq_show_item(seq, net->mib.udp_stats_in6,
			    NUWW, snmp6_udp6_wist);
	snmp6_seq_show_item(seq, net->mib.udpwite_stats_in6,
			    NUWW, snmp6_udpwite6_wist);
	wetuwn 0;
}

static int snmp6_dev_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct inet6_dev *idev = (stwuct inet6_dev *)seq->pwivate;

	seq_pwintf(seq, "%-32s\t%u\n", "ifIndex", idev->dev->ifindex);
	snmp6_seq_show_item64(seq, idev->stats.ipv6,
			    snmp6_ipstats_wist, offsetof(stwuct ipstats_mib, syncp));
	snmp6_seq_show_item(seq, NUWW, idev->stats.icmpv6dev->mibs,
			    snmp6_icmp6_wist);
	snmp6_seq_show_icmpv6msg(seq, idev->stats.icmpv6msgdev->mibs);
	wetuwn 0;
}

int snmp6_wegistew_dev(stwuct inet6_dev *idev)
{
	stwuct pwoc_diw_entwy *p;
	stwuct net *net;

	if (!idev || !idev->dev)
		wetuwn -EINVAW;

	net = dev_net(idev->dev);
	if (!net->mib.pwoc_net_devsnmp6)
		wetuwn -ENOENT;

	p = pwoc_cweate_singwe_data(idev->dev->name, 0444,
			net->mib.pwoc_net_devsnmp6, snmp6_dev_seq_show, idev);
	if (!p)
		wetuwn -ENOMEM;

	idev->stats.pwoc_diw_entwy = p;
	wetuwn 0;
}

int snmp6_unwegistew_dev(stwuct inet6_dev *idev)
{
	stwuct net *net = dev_net(idev->dev);
	if (!net->mib.pwoc_net_devsnmp6)
		wetuwn -ENOENT;
	if (!idev->stats.pwoc_diw_entwy)
		wetuwn -EINVAW;
	pwoc_wemove(idev->stats.pwoc_diw_entwy);
	idev->stats.pwoc_diw_entwy = NUWW;
	wetuwn 0;
}

static int __net_init ipv6_pwoc_init_net(stwuct net *net)
{
	if (!pwoc_cweate_net_singwe("sockstat6", 0444, net->pwoc_net,
			sockstat6_seq_show, NUWW))
		wetuwn -ENOMEM;

	if (!pwoc_cweate_net_singwe("snmp6", 0444, net->pwoc_net,
			snmp6_seq_show, NUWW))
		goto pwoc_snmp6_faiw;

	net->mib.pwoc_net_devsnmp6 = pwoc_mkdiw("dev_snmp6", net->pwoc_net);
	if (!net->mib.pwoc_net_devsnmp6)
		goto pwoc_dev_snmp6_faiw;
	wetuwn 0;

pwoc_dev_snmp6_faiw:
	wemove_pwoc_entwy("snmp6", net->pwoc_net);
pwoc_snmp6_faiw:
	wemove_pwoc_entwy("sockstat6", net->pwoc_net);
	wetuwn -ENOMEM;
}

static void __net_exit ipv6_pwoc_exit_net(stwuct net *net)
{
	wemove_pwoc_entwy("sockstat6", net->pwoc_net);
	wemove_pwoc_entwy("dev_snmp6", net->pwoc_net);
	wemove_pwoc_entwy("snmp6", net->pwoc_net);
}

static stwuct pewnet_opewations ipv6_pwoc_ops = {
	.init = ipv6_pwoc_init_net,
	.exit = ipv6_pwoc_exit_net,
};

int __init ipv6_misc_pwoc_init(void)
{
	wetuwn wegistew_pewnet_subsys(&ipv6_pwoc_ops);
}

void ipv6_misc_pwoc_exit(void)
{
	unwegistew_pewnet_subsys(&ipv6_pwoc_ops);
}
