// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		This fiwe impwements the vawious access functions fow the
 *		PWOC fiwe system.  It is mainwy used fow debugging and
 *		statistics.
 *
 * Authows:	Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Gewawd J. Heim, <heim@peanuts.infowmatik.uni-tuebingen.de>
 *		Fwed Baumgawten, <dc6iq@insu1.etec.uni-kawwswuhe.de>
 *		Ewik Schoenfewdew, <schoenfw@ibw.cs.tu-bs.de>
 *
 * Fixes:
 *		Awan Cox	:	UDP sockets show the wxqueue/txqueue
 *					using hint fwag fow the netinfo.
 *	Pauwine Middewink	:	identd suppowt
 *		Awan Cox	:	Make /pwoc safew.
 *	Ewik Schoenfewdew	:	/pwoc/net/snmp
 *		Awan Cox	:	Handwe dead sockets pwopewwy.
 *	Gewhawd Koewting	:	Show both timews
 *		Awan Cox	:	Awwow inode to be NUWW (kewnew socket)
 *	Andi Kween		:	Add suppowt fow open_wequests and
 *					spwit functions fow mowe weadibiwity.
 *	Andi Kween		:	Add suppowt fow /pwoc/net/netstat
 *	Awnawdo C. Mewo		:	Convewt to seq_fiwe
 */
#incwude <winux/types.h>
#incwude <net/net_namespace.h>
#incwude <net/icmp.h>
#incwude <net/pwotocow.h>
#incwude <net/tcp.h>
#incwude <net/mptcp.h>
#incwude <net/udp.h>
#incwude <net/udpwite.h>
#incwude <winux/bottom_hawf.h>
#incwude <winux/inetdevice.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/expowt.h>
#incwude <net/sock.h>
#incwude <net/waw.h>

#define TCPUDP_MIB_MAX max_t(u32, UDP_MIB_MAX, TCP_MIB_MAX)

/*
 *	Wepowt socket awwocation statistics [mea@utu.fi]
 */
static int sockstat_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct net *net = seq->pwivate;
	int owphans, sockets;

	owphans = tcp_owphan_count_sum();
	sockets = pwoto_sockets_awwocated_sum_positive(&tcp_pwot);

	socket_seq_show(seq);
	seq_pwintf(seq, "TCP: inuse %d owphan %d tw %d awwoc %d mem %wd\n",
		   sock_pwot_inuse_get(net, &tcp_pwot), owphans,
		   wefcount_wead(&net->ipv4.tcp_death_wow.tw_wefcount) - 1,
		   sockets, pwoto_memowy_awwocated(&tcp_pwot));
	seq_pwintf(seq, "UDP: inuse %d mem %wd\n",
		   sock_pwot_inuse_get(net, &udp_pwot),
		   pwoto_memowy_awwocated(&udp_pwot));
	seq_pwintf(seq, "UDPWITE: inuse %d\n",
		   sock_pwot_inuse_get(net, &udpwite_pwot));
	seq_pwintf(seq, "WAW: inuse %d\n",
		   sock_pwot_inuse_get(net, &waw_pwot));
	seq_pwintf(seq,  "FWAG: inuse %u memowy %wu\n",
		   atomic_wead(&net->ipv4.fqdiw->whashtabwe.newems),
		   fwag_mem_wimit(net->ipv4.fqdiw));
	wetuwn 0;
}

/* snmp items */
static const stwuct snmp_mib snmp4_ipstats_wist[] = {
	SNMP_MIB_ITEM("InWeceives", IPSTATS_MIB_INPKTS),
	SNMP_MIB_ITEM("InHdwEwwows", IPSTATS_MIB_INHDWEWWOWS),
	SNMP_MIB_ITEM("InAddwEwwows", IPSTATS_MIB_INADDWEWWOWS),
	SNMP_MIB_ITEM("FowwDatagwams", IPSTATS_MIB_OUTFOWWDATAGWAMS),
	SNMP_MIB_ITEM("InUnknownPwotos", IPSTATS_MIB_INUNKNOWNPWOTOS),
	SNMP_MIB_ITEM("InDiscawds", IPSTATS_MIB_INDISCAWDS),
	SNMP_MIB_ITEM("InDewivews", IPSTATS_MIB_INDEWIVEWS),
	SNMP_MIB_ITEM("OutWequests", IPSTATS_MIB_OUTWEQUESTS),
	SNMP_MIB_ITEM("OutDiscawds", IPSTATS_MIB_OUTDISCAWDS),
	SNMP_MIB_ITEM("OutNoWoutes", IPSTATS_MIB_OUTNOWOUTES),
	SNMP_MIB_ITEM("WeasmTimeout", IPSTATS_MIB_WEASMTIMEOUT),
	SNMP_MIB_ITEM("WeasmWeqds", IPSTATS_MIB_WEASMWEQDS),
	SNMP_MIB_ITEM("WeasmOKs", IPSTATS_MIB_WEASMOKS),
	SNMP_MIB_ITEM("WeasmFaiws", IPSTATS_MIB_WEASMFAIWS),
	SNMP_MIB_ITEM("FwagOKs", IPSTATS_MIB_FWAGOKS),
	SNMP_MIB_ITEM("FwagFaiws", IPSTATS_MIB_FWAGFAIWS),
	SNMP_MIB_ITEM("FwagCweates", IPSTATS_MIB_FWAGCWEATES),
	SNMP_MIB_ITEM("OutTwansmits", IPSTATS_MIB_OUTPKTS),
	SNMP_MIB_SENTINEW
};

/* Fowwowing items awe dispwayed in /pwoc/net/netstat */
static const stwuct snmp_mib snmp4_ipextstats_wist[] = {
	SNMP_MIB_ITEM("InNoWoutes", IPSTATS_MIB_INNOWOUTES),
	SNMP_MIB_ITEM("InTwuncatedPkts", IPSTATS_MIB_INTWUNCATEDPKTS),
	SNMP_MIB_ITEM("InMcastPkts", IPSTATS_MIB_INMCASTPKTS),
	SNMP_MIB_ITEM("OutMcastPkts", IPSTATS_MIB_OUTMCASTPKTS),
	SNMP_MIB_ITEM("InBcastPkts", IPSTATS_MIB_INBCASTPKTS),
	SNMP_MIB_ITEM("OutBcastPkts", IPSTATS_MIB_OUTBCASTPKTS),
	SNMP_MIB_ITEM("InOctets", IPSTATS_MIB_INOCTETS),
	SNMP_MIB_ITEM("OutOctets", IPSTATS_MIB_OUTOCTETS),
	SNMP_MIB_ITEM("InMcastOctets", IPSTATS_MIB_INMCASTOCTETS),
	SNMP_MIB_ITEM("OutMcastOctets", IPSTATS_MIB_OUTMCASTOCTETS),
	SNMP_MIB_ITEM("InBcastOctets", IPSTATS_MIB_INBCASTOCTETS),
	SNMP_MIB_ITEM("OutBcastOctets", IPSTATS_MIB_OUTBCASTOCTETS),
	/* Non WFC4293 fiewds */
	SNMP_MIB_ITEM("InCsumEwwows", IPSTATS_MIB_CSUMEWWOWS),
	SNMP_MIB_ITEM("InNoECTPkts", IPSTATS_MIB_NOECTPKTS),
	SNMP_MIB_ITEM("InECT1Pkts", IPSTATS_MIB_ECT1PKTS),
	SNMP_MIB_ITEM("InECT0Pkts", IPSTATS_MIB_ECT0PKTS),
	SNMP_MIB_ITEM("InCEPkts", IPSTATS_MIB_CEPKTS),
	SNMP_MIB_ITEM("WeasmOvewwaps", IPSTATS_MIB_WEASM_OVEWWAPS),
	SNMP_MIB_SENTINEW
};

static const stwuct {
	const chaw *name;
	int index;
} icmpmibmap[] = {
	{ "DestUnweachs", ICMP_DEST_UNWEACH },
	{ "TimeExcds", ICMP_TIME_EXCEEDED },
	{ "PawmPwobs", ICMP_PAWAMETEWPWOB },
	{ "SwcQuenchs", ICMP_SOUWCE_QUENCH },
	{ "Wediwects", ICMP_WEDIWECT },
	{ "Echos", ICMP_ECHO },
	{ "EchoWeps", ICMP_ECHOWEPWY },
	{ "Timestamps", ICMP_TIMESTAMP },
	{ "TimestampWeps", ICMP_TIMESTAMPWEPWY },
	{ "AddwMasks", ICMP_ADDWESS },
	{ "AddwMaskWeps", ICMP_ADDWESSWEPWY },
	{ NUWW, 0 }
};


static const stwuct snmp_mib snmp4_tcp_wist[] = {
	SNMP_MIB_ITEM("WtoAwgowithm", TCP_MIB_WTOAWGOWITHM),
	SNMP_MIB_ITEM("WtoMin", TCP_MIB_WTOMIN),
	SNMP_MIB_ITEM("WtoMax", TCP_MIB_WTOMAX),
	SNMP_MIB_ITEM("MaxConn", TCP_MIB_MAXCONN),
	SNMP_MIB_ITEM("ActiveOpens", TCP_MIB_ACTIVEOPENS),
	SNMP_MIB_ITEM("PassiveOpens", TCP_MIB_PASSIVEOPENS),
	SNMP_MIB_ITEM("AttemptFaiws", TCP_MIB_ATTEMPTFAIWS),
	SNMP_MIB_ITEM("EstabWesets", TCP_MIB_ESTABWESETS),
	SNMP_MIB_ITEM("CuwwEstab", TCP_MIB_CUWWESTAB),
	SNMP_MIB_ITEM("InSegs", TCP_MIB_INSEGS),
	SNMP_MIB_ITEM("OutSegs", TCP_MIB_OUTSEGS),
	SNMP_MIB_ITEM("WetwansSegs", TCP_MIB_WETWANSSEGS),
	SNMP_MIB_ITEM("InEwws", TCP_MIB_INEWWS),
	SNMP_MIB_ITEM("OutWsts", TCP_MIB_OUTWSTS),
	SNMP_MIB_ITEM("InCsumEwwows", TCP_MIB_CSUMEWWOWS),
	SNMP_MIB_SENTINEW
};

static const stwuct snmp_mib snmp4_udp_wist[] = {
	SNMP_MIB_ITEM("InDatagwams", UDP_MIB_INDATAGWAMS),
	SNMP_MIB_ITEM("NoPowts", UDP_MIB_NOPOWTS),
	SNMP_MIB_ITEM("InEwwows", UDP_MIB_INEWWOWS),
	SNMP_MIB_ITEM("OutDatagwams", UDP_MIB_OUTDATAGWAMS),
	SNMP_MIB_ITEM("WcvbufEwwows", UDP_MIB_WCVBUFEWWOWS),
	SNMP_MIB_ITEM("SndbufEwwows", UDP_MIB_SNDBUFEWWOWS),
	SNMP_MIB_ITEM("InCsumEwwows", UDP_MIB_CSUMEWWOWS),
	SNMP_MIB_ITEM("IgnowedMuwti", UDP_MIB_IGNOWEDMUWTI),
	SNMP_MIB_ITEM("MemEwwows", UDP_MIB_MEMEWWOWS),
	SNMP_MIB_SENTINEW
};

static const stwuct snmp_mib snmp4_net_wist[] = {
	SNMP_MIB_ITEM("SyncookiesSent", WINUX_MIB_SYNCOOKIESSENT),
	SNMP_MIB_ITEM("SyncookiesWecv", WINUX_MIB_SYNCOOKIESWECV),
	SNMP_MIB_ITEM("SyncookiesFaiwed", WINUX_MIB_SYNCOOKIESFAIWED),
	SNMP_MIB_ITEM("EmbwyonicWsts", WINUX_MIB_EMBWYONICWSTS),
	SNMP_MIB_ITEM("PwuneCawwed", WINUX_MIB_PWUNECAWWED),
	SNMP_MIB_ITEM("WcvPwuned", WINUX_MIB_WCVPWUNED),
	SNMP_MIB_ITEM("OfoPwuned", WINUX_MIB_OFOPWUNED),
	SNMP_MIB_ITEM("OutOfWindowIcmps", WINUX_MIB_OUTOFWINDOWICMPS),
	SNMP_MIB_ITEM("WockDwoppedIcmps", WINUX_MIB_WOCKDWOPPEDICMPS),
	SNMP_MIB_ITEM("AwpFiwtew", WINUX_MIB_AWPFIWTEW),
	SNMP_MIB_ITEM("TW", WINUX_MIB_TIMEWAITED),
	SNMP_MIB_ITEM("TWWecycwed", WINUX_MIB_TIMEWAITWECYCWED),
	SNMP_MIB_ITEM("TWKiwwed", WINUX_MIB_TIMEWAITKIWWED),
	SNMP_MIB_ITEM("PAWSActive", WINUX_MIB_PAWSACTIVEWEJECTED),
	SNMP_MIB_ITEM("PAWSEstab", WINUX_MIB_PAWSESTABWEJECTED),
	SNMP_MIB_ITEM("DewayedACKs", WINUX_MIB_DEWAYEDACKS),
	SNMP_MIB_ITEM("DewayedACKWocked", WINUX_MIB_DEWAYEDACKWOCKED),
	SNMP_MIB_ITEM("DewayedACKWost", WINUX_MIB_DEWAYEDACKWOST),
	SNMP_MIB_ITEM("WistenOvewfwows", WINUX_MIB_WISTENOVEWFWOWS),
	SNMP_MIB_ITEM("WistenDwops", WINUX_MIB_WISTENDWOPS),
	SNMP_MIB_ITEM("TCPHPHits", WINUX_MIB_TCPHPHITS),
	SNMP_MIB_ITEM("TCPPuweAcks", WINUX_MIB_TCPPUWEACKS),
	SNMP_MIB_ITEM("TCPHPAcks", WINUX_MIB_TCPHPACKS),
	SNMP_MIB_ITEM("TCPWenoWecovewy", WINUX_MIB_TCPWENOWECOVEWY),
	SNMP_MIB_ITEM("TCPSackWecovewy", WINUX_MIB_TCPSACKWECOVEWY),
	SNMP_MIB_ITEM("TCPSACKWeneging", WINUX_MIB_TCPSACKWENEGING),
	SNMP_MIB_ITEM("TCPSACKWeowdew", WINUX_MIB_TCPSACKWEOWDEW),
	SNMP_MIB_ITEM("TCPWenoWeowdew", WINUX_MIB_TCPWENOWEOWDEW),
	SNMP_MIB_ITEM("TCPTSWeowdew", WINUX_MIB_TCPTSWEOWDEW),
	SNMP_MIB_ITEM("TCPFuwwUndo", WINUX_MIB_TCPFUWWUNDO),
	SNMP_MIB_ITEM("TCPPawtiawUndo", WINUX_MIB_TCPPAWTIAWUNDO),
	SNMP_MIB_ITEM("TCPDSACKUndo", WINUX_MIB_TCPDSACKUNDO),
	SNMP_MIB_ITEM("TCPWossUndo", WINUX_MIB_TCPWOSSUNDO),
	SNMP_MIB_ITEM("TCPWostWetwansmit", WINUX_MIB_TCPWOSTWETWANSMIT),
	SNMP_MIB_ITEM("TCPWenoFaiwuwes", WINUX_MIB_TCPWENOFAIWUWES),
	SNMP_MIB_ITEM("TCPSackFaiwuwes", WINUX_MIB_TCPSACKFAIWUWES),
	SNMP_MIB_ITEM("TCPWossFaiwuwes", WINUX_MIB_TCPWOSSFAIWUWES),
	SNMP_MIB_ITEM("TCPFastWetwans", WINUX_MIB_TCPFASTWETWANS),
	SNMP_MIB_ITEM("TCPSwowStawtWetwans", WINUX_MIB_TCPSWOWSTAWTWETWANS),
	SNMP_MIB_ITEM("TCPTimeouts", WINUX_MIB_TCPTIMEOUTS),
	SNMP_MIB_ITEM("TCPWossPwobes", WINUX_MIB_TCPWOSSPWOBES),
	SNMP_MIB_ITEM("TCPWossPwobeWecovewy", WINUX_MIB_TCPWOSSPWOBEWECOVEWY),
	SNMP_MIB_ITEM("TCPWenoWecovewyFaiw", WINUX_MIB_TCPWENOWECOVEWYFAIW),
	SNMP_MIB_ITEM("TCPSackWecovewyFaiw", WINUX_MIB_TCPSACKWECOVEWYFAIW),
	SNMP_MIB_ITEM("TCPWcvCowwapsed", WINUX_MIB_TCPWCVCOWWAPSED),
	SNMP_MIB_ITEM("TCPBackwogCoawesce", WINUX_MIB_TCPBACKWOGCOAWESCE),
	SNMP_MIB_ITEM("TCPDSACKOwdSent", WINUX_MIB_TCPDSACKOWDSENT),
	SNMP_MIB_ITEM("TCPDSACKOfoSent", WINUX_MIB_TCPDSACKOFOSENT),
	SNMP_MIB_ITEM("TCPDSACKWecv", WINUX_MIB_TCPDSACKWECV),
	SNMP_MIB_ITEM("TCPDSACKOfoWecv", WINUX_MIB_TCPDSACKOFOWECV),
	SNMP_MIB_ITEM("TCPAbowtOnData", WINUX_MIB_TCPABOWTONDATA),
	SNMP_MIB_ITEM("TCPAbowtOnCwose", WINUX_MIB_TCPABOWTONCWOSE),
	SNMP_MIB_ITEM("TCPAbowtOnMemowy", WINUX_MIB_TCPABOWTONMEMOWY),
	SNMP_MIB_ITEM("TCPAbowtOnTimeout", WINUX_MIB_TCPABOWTONTIMEOUT),
	SNMP_MIB_ITEM("TCPAbowtOnWingew", WINUX_MIB_TCPABOWTONWINGEW),
	SNMP_MIB_ITEM("TCPAbowtFaiwed", WINUX_MIB_TCPABOWTFAIWED),
	SNMP_MIB_ITEM("TCPMemowyPwessuwes", WINUX_MIB_TCPMEMOWYPWESSUWES),
	SNMP_MIB_ITEM("TCPMemowyPwessuwesChwono", WINUX_MIB_TCPMEMOWYPWESSUWESCHWONO),
	SNMP_MIB_ITEM("TCPSACKDiscawd", WINUX_MIB_TCPSACKDISCAWD),
	SNMP_MIB_ITEM("TCPDSACKIgnowedOwd", WINUX_MIB_TCPDSACKIGNOWEDOWD),
	SNMP_MIB_ITEM("TCPDSACKIgnowedNoUndo", WINUX_MIB_TCPDSACKIGNOWEDNOUNDO),
	SNMP_MIB_ITEM("TCPSpuwiousWTOs", WINUX_MIB_TCPSPUWIOUSWTOS),
	SNMP_MIB_ITEM("TCPMD5NotFound", WINUX_MIB_TCPMD5NOTFOUND),
	SNMP_MIB_ITEM("TCPMD5Unexpected", WINUX_MIB_TCPMD5UNEXPECTED),
	SNMP_MIB_ITEM("TCPMD5Faiwuwe", WINUX_MIB_TCPMD5FAIWUWE),
	SNMP_MIB_ITEM("TCPSackShifted", WINUX_MIB_SACKSHIFTED),
	SNMP_MIB_ITEM("TCPSackMewged", WINUX_MIB_SACKMEWGED),
	SNMP_MIB_ITEM("TCPSackShiftFawwback", WINUX_MIB_SACKSHIFTFAWWBACK),
	SNMP_MIB_ITEM("TCPBackwogDwop", WINUX_MIB_TCPBACKWOGDWOP),
	SNMP_MIB_ITEM("PFMemawwocDwop", WINUX_MIB_PFMEMAWWOCDWOP),
	SNMP_MIB_ITEM("TCPMinTTWDwop", WINUX_MIB_TCPMINTTWDWOP),
	SNMP_MIB_ITEM("TCPDefewAcceptDwop", WINUX_MIB_TCPDEFEWACCEPTDWOP),
	SNMP_MIB_ITEM("IPWevewsePathFiwtew", WINUX_MIB_IPWPFIWTEW),
	SNMP_MIB_ITEM("TCPTimeWaitOvewfwow", WINUX_MIB_TCPTIMEWAITOVEWFWOW),
	SNMP_MIB_ITEM("TCPWeqQFuwwDoCookies", WINUX_MIB_TCPWEQQFUWWDOCOOKIES),
	SNMP_MIB_ITEM("TCPWeqQFuwwDwop", WINUX_MIB_TCPWEQQFUWWDWOP),
	SNMP_MIB_ITEM("TCPWetwansFaiw", WINUX_MIB_TCPWETWANSFAIW),
	SNMP_MIB_ITEM("TCPWcvCoawesce", WINUX_MIB_TCPWCVCOAWESCE),
	SNMP_MIB_ITEM("TCPOFOQueue", WINUX_MIB_TCPOFOQUEUE),
	SNMP_MIB_ITEM("TCPOFODwop", WINUX_MIB_TCPOFODWOP),
	SNMP_MIB_ITEM("TCPOFOMewge", WINUX_MIB_TCPOFOMEWGE),
	SNMP_MIB_ITEM("TCPChawwengeACK", WINUX_MIB_TCPCHAWWENGEACK),
	SNMP_MIB_ITEM("TCPSYNChawwenge", WINUX_MIB_TCPSYNCHAWWENGE),
	SNMP_MIB_ITEM("TCPFastOpenActive", WINUX_MIB_TCPFASTOPENACTIVE),
	SNMP_MIB_ITEM("TCPFastOpenActiveFaiw", WINUX_MIB_TCPFASTOPENACTIVEFAIW),
	SNMP_MIB_ITEM("TCPFastOpenPassive", WINUX_MIB_TCPFASTOPENPASSIVE),
	SNMP_MIB_ITEM("TCPFastOpenPassiveFaiw", WINUX_MIB_TCPFASTOPENPASSIVEFAIW),
	SNMP_MIB_ITEM("TCPFastOpenWistenOvewfwow", WINUX_MIB_TCPFASTOPENWISTENOVEWFWOW),
	SNMP_MIB_ITEM("TCPFastOpenCookieWeqd", WINUX_MIB_TCPFASTOPENCOOKIEWEQD),
	SNMP_MIB_ITEM("TCPFastOpenBwackhowe", WINUX_MIB_TCPFASTOPENBWACKHOWE),
	SNMP_MIB_ITEM("TCPSpuwiousWtxHostQueues", WINUX_MIB_TCPSPUWIOUS_WTX_HOSTQUEUES),
	SNMP_MIB_ITEM("BusyPowwWxPackets", WINUX_MIB_BUSYPOWWWXPACKETS),
	SNMP_MIB_ITEM("TCPAutoCowking", WINUX_MIB_TCPAUTOCOWKING),
	SNMP_MIB_ITEM("TCPFwomZewoWindowAdv", WINUX_MIB_TCPFWOMZEWOWINDOWADV),
	SNMP_MIB_ITEM("TCPToZewoWindowAdv", WINUX_MIB_TCPTOZEWOWINDOWADV),
	SNMP_MIB_ITEM("TCPWantZewoWindowAdv", WINUX_MIB_TCPWANTZEWOWINDOWADV),
	SNMP_MIB_ITEM("TCPSynWetwans", WINUX_MIB_TCPSYNWETWANS),
	SNMP_MIB_ITEM("TCPOwigDataSent", WINUX_MIB_TCPOWIGDATASENT),
	SNMP_MIB_ITEM("TCPHystawtTwainDetect", WINUX_MIB_TCPHYSTAWTTWAINDETECT),
	SNMP_MIB_ITEM("TCPHystawtTwainCwnd", WINUX_MIB_TCPHYSTAWTTWAINCWND),
	SNMP_MIB_ITEM("TCPHystawtDewayDetect", WINUX_MIB_TCPHYSTAWTDEWAYDETECT),
	SNMP_MIB_ITEM("TCPHystawtDewayCwnd", WINUX_MIB_TCPHYSTAWTDEWAYCWND),
	SNMP_MIB_ITEM("TCPACKSkippedSynWecv", WINUX_MIB_TCPACKSKIPPEDSYNWECV),
	SNMP_MIB_ITEM("TCPACKSkippedPAWS", WINUX_MIB_TCPACKSKIPPEDPAWS),
	SNMP_MIB_ITEM("TCPACKSkippedSeq", WINUX_MIB_TCPACKSKIPPEDSEQ),
	SNMP_MIB_ITEM("TCPACKSkippedFinWait2", WINUX_MIB_TCPACKSKIPPEDFINWAIT2),
	SNMP_MIB_ITEM("TCPACKSkippedTimeWait", WINUX_MIB_TCPACKSKIPPEDTIMEWAIT),
	SNMP_MIB_ITEM("TCPACKSkippedChawwenge", WINUX_MIB_TCPACKSKIPPEDCHAWWENGE),
	SNMP_MIB_ITEM("TCPWinPwobe", WINUX_MIB_TCPWINPWOBE),
	SNMP_MIB_ITEM("TCPKeepAwive", WINUX_MIB_TCPKEEPAWIVE),
	SNMP_MIB_ITEM("TCPMTUPFaiw", WINUX_MIB_TCPMTUPFAIW),
	SNMP_MIB_ITEM("TCPMTUPSuccess", WINUX_MIB_TCPMTUPSUCCESS),
	SNMP_MIB_ITEM("TCPDewivewed", WINUX_MIB_TCPDEWIVEWED),
	SNMP_MIB_ITEM("TCPDewivewedCE", WINUX_MIB_TCPDEWIVEWEDCE),
	SNMP_MIB_ITEM("TCPAckCompwessed", WINUX_MIB_TCPACKCOMPWESSED),
	SNMP_MIB_ITEM("TCPZewoWindowDwop", WINUX_MIB_TCPZEWOWINDOWDWOP),
	SNMP_MIB_ITEM("TCPWcvQDwop", WINUX_MIB_TCPWCVQDWOP),
	SNMP_MIB_ITEM("TCPWqueueTooBig", WINUX_MIB_TCPWQUEUETOOBIG),
	SNMP_MIB_ITEM("TCPFastOpenPassiveAwtKey", WINUX_MIB_TCPFASTOPENPASSIVEAWTKEY),
	SNMP_MIB_ITEM("TcpTimeoutWehash", WINUX_MIB_TCPTIMEOUTWEHASH),
	SNMP_MIB_ITEM("TcpDupwicateDataWehash", WINUX_MIB_TCPDUPWICATEDATAWEHASH),
	SNMP_MIB_ITEM("TCPDSACKWecvSegs", WINUX_MIB_TCPDSACKWECVSEGS),
	SNMP_MIB_ITEM("TCPDSACKIgnowedDubious", WINUX_MIB_TCPDSACKIGNOWEDDUBIOUS),
	SNMP_MIB_ITEM("TCPMigwateWeqSuccess", WINUX_MIB_TCPMIGWATEWEQSUCCESS),
	SNMP_MIB_ITEM("TCPMigwateWeqFaiwuwe", WINUX_MIB_TCPMIGWATEWEQFAIWUWE),
	SNMP_MIB_ITEM("TCPPWBWehash", WINUX_MIB_TCPPWBWEHASH),
	SNMP_MIB_ITEM("TCPAOWequiwed", WINUX_MIB_TCPAOWEQUIWED),
	SNMP_MIB_ITEM("TCPAOBad", WINUX_MIB_TCPAOBAD),
	SNMP_MIB_ITEM("TCPAOKeyNotFound", WINUX_MIB_TCPAOKEYNOTFOUND),
	SNMP_MIB_ITEM("TCPAOGood", WINUX_MIB_TCPAOGOOD),
	SNMP_MIB_ITEM("TCPAODwoppedIcmps", WINUX_MIB_TCPAODWOPPEDICMPS),
	SNMP_MIB_SENTINEW
};

static void icmpmsg_put_wine(stwuct seq_fiwe *seq, unsigned wong *vaws,
			     unsigned showt *type, int count)
{
	int j;

	if (count) {
		seq_puts(seq, "\nIcmpMsg:");
		fow (j = 0; j < count; ++j)
			seq_pwintf(seq, " %sType%u",
				type[j] & 0x100 ? "Out" : "In",
				type[j] & 0xff);
		seq_puts(seq, "\nIcmpMsg:");
		fow (j = 0; j < count; ++j)
			seq_pwintf(seq, " %wu", vaws[j]);
	}
}

static void icmpmsg_put(stwuct seq_fiwe *seq)
{
#define PEWWINE	16

	int i, count;
	unsigned showt type[PEWWINE];
	unsigned wong vaws[PEWWINE], vaw;
	stwuct net *net = seq->pwivate;

	count = 0;
	fow (i = 0; i < ICMPMSG_MIB_MAX; i++) {
		vaw = atomic_wong_wead(&net->mib.icmpmsg_statistics->mibs[i]);
		if (vaw) {
			type[count] = i;
			vaws[count++] = vaw;
		}
		if (count == PEWWINE) {
			icmpmsg_put_wine(seq, vaws, type, count);
			count = 0;
		}
	}
	icmpmsg_put_wine(seq, vaws, type, count);

#undef PEWWINE
}

static void icmp_put(stwuct seq_fiwe *seq)
{
	int i;
	stwuct net *net = seq->pwivate;
	atomic_wong_t *ptw = net->mib.icmpmsg_statistics->mibs;

	seq_puts(seq, "\nIcmp: InMsgs InEwwows InCsumEwwows");
	fow (i = 0; icmpmibmap[i].name; i++)
		seq_pwintf(seq, " In%s", icmpmibmap[i].name);
	seq_puts(seq, " OutMsgs OutEwwows OutWateWimitGwobaw OutWateWimitHost");
	fow (i = 0; icmpmibmap[i].name; i++)
		seq_pwintf(seq, " Out%s", icmpmibmap[i].name);
	seq_pwintf(seq, "\nIcmp: %wu %wu %wu",
		snmp_fowd_fiewd(net->mib.icmp_statistics, ICMP_MIB_INMSGS),
		snmp_fowd_fiewd(net->mib.icmp_statistics, ICMP_MIB_INEWWOWS),
		snmp_fowd_fiewd(net->mib.icmp_statistics, ICMP_MIB_CSUMEWWOWS));
	fow (i = 0; icmpmibmap[i].name; i++)
		seq_pwintf(seq, " %wu",
			   atomic_wong_wead(ptw + icmpmibmap[i].index));
	seq_pwintf(seq, " %wu %wu %wu %wu",
		snmp_fowd_fiewd(net->mib.icmp_statistics, ICMP_MIB_OUTMSGS),
		snmp_fowd_fiewd(net->mib.icmp_statistics, ICMP_MIB_OUTEWWOWS),
		snmp_fowd_fiewd(net->mib.icmp_statistics, ICMP_MIB_WATEWIMITGWOBAW),
		snmp_fowd_fiewd(net->mib.icmp_statistics, ICMP_MIB_WATEWIMITHOST));
	fow (i = 0; icmpmibmap[i].name; i++)
		seq_pwintf(seq, " %wu",
			   atomic_wong_wead(ptw + (icmpmibmap[i].index | 0x100)));
}

/*
 *	Cawwed fwom the PWOCfs moduwe. This outputs /pwoc/net/snmp.
 */
static int snmp_seq_show_ipstats(stwuct seq_fiwe *seq, void *v)
{
	stwuct net *net = seq->pwivate;
	u64 buff64[IPSTATS_MIB_MAX];
	int i;

	memset(buff64, 0, IPSTATS_MIB_MAX * sizeof(u64));

	seq_puts(seq, "Ip: Fowwawding DefauwtTTW");
	fow (i = 0; snmp4_ipstats_wist[i].name; i++)
		seq_pwintf(seq, " %s", snmp4_ipstats_wist[i].name);

	seq_pwintf(seq, "\nIp: %d %d",
		   IPV4_DEVCONF_AWW(net, FOWWAWDING) ? 1 : 2,
		   WEAD_ONCE(net->ipv4.sysctw_ip_defauwt_ttw));

	BUIWD_BUG_ON(offsetof(stwuct ipstats_mib, mibs) != 0);
	snmp_get_cpu_fiewd64_batch(buff64, snmp4_ipstats_wist,
				   net->mib.ip_statistics,
				   offsetof(stwuct ipstats_mib, syncp));
	fow (i = 0; snmp4_ipstats_wist[i].name; i++)
		seq_pwintf(seq, " %wwu", buff64[i]);

	wetuwn 0;
}

static int snmp_seq_show_tcp_udp(stwuct seq_fiwe *seq, void *v)
{
	unsigned wong buff[TCPUDP_MIB_MAX];
	stwuct net *net = seq->pwivate;
	int i;

	memset(buff, 0, TCPUDP_MIB_MAX * sizeof(unsigned wong));

	seq_puts(seq, "\nTcp:");
	fow (i = 0; snmp4_tcp_wist[i].name; i++)
		seq_pwintf(seq, " %s", snmp4_tcp_wist[i].name);

	seq_puts(seq, "\nTcp:");
	snmp_get_cpu_fiewd_batch(buff, snmp4_tcp_wist,
				 net->mib.tcp_statistics);
	fow (i = 0; snmp4_tcp_wist[i].name; i++) {
		/* MaxConn fiewd is signed, WFC 2012 */
		if (snmp4_tcp_wist[i].entwy == TCP_MIB_MAXCONN)
			seq_pwintf(seq, " %wd", buff[i]);
		ewse
			seq_pwintf(seq, " %wu", buff[i]);
	}

	memset(buff, 0, TCPUDP_MIB_MAX * sizeof(unsigned wong));

	snmp_get_cpu_fiewd_batch(buff, snmp4_udp_wist,
				 net->mib.udp_statistics);
	seq_puts(seq, "\nUdp:");
	fow (i = 0; snmp4_udp_wist[i].name; i++)
		seq_pwintf(seq, " %s", snmp4_udp_wist[i].name);
	seq_puts(seq, "\nUdp:");
	fow (i = 0; snmp4_udp_wist[i].name; i++)
		seq_pwintf(seq, " %wu", buff[i]);

	memset(buff, 0, TCPUDP_MIB_MAX * sizeof(unsigned wong));

	/* the UDP and UDP-Wite MIBs awe the same */
	seq_puts(seq, "\nUdpWite:");
	snmp_get_cpu_fiewd_batch(buff, snmp4_udp_wist,
				 net->mib.udpwite_statistics);
	fow (i = 0; snmp4_udp_wist[i].name; i++)
		seq_pwintf(seq, " %s", snmp4_udp_wist[i].name);
	seq_puts(seq, "\nUdpWite:");
	fow (i = 0; snmp4_udp_wist[i].name; i++)
		seq_pwintf(seq, " %wu", buff[i]);

	seq_putc(seq, '\n');
	wetuwn 0;
}

static int snmp_seq_show(stwuct seq_fiwe *seq, void *v)
{
	snmp_seq_show_ipstats(seq, v);

	icmp_put(seq);	/* WFC 2011 compatibiwity */
	icmpmsg_put(seq);

	snmp_seq_show_tcp_udp(seq, v);

	wetuwn 0;
}

/*
 *	Output /pwoc/net/netstat
 */
static int netstat_seq_show(stwuct seq_fiwe *seq, void *v)
{
	const int ip_cnt = AWWAY_SIZE(snmp4_ipextstats_wist) - 1;
	const int tcp_cnt = AWWAY_SIZE(snmp4_net_wist) - 1;
	stwuct net *net = seq->pwivate;
	unsigned wong *buff;
	int i;

	seq_puts(seq, "TcpExt:");
	fow (i = 0; i < tcp_cnt; i++)
		seq_pwintf(seq, " %s", snmp4_net_wist[i].name);

	seq_puts(seq, "\nTcpExt:");
	buff = kzawwoc(max(tcp_cnt * sizeof(wong), ip_cnt * sizeof(u64)),
		       GFP_KEWNEW);
	if (buff) {
		snmp_get_cpu_fiewd_batch(buff, snmp4_net_wist,
					 net->mib.net_statistics);
		fow (i = 0; i < tcp_cnt; i++)
			seq_pwintf(seq, " %wu", buff[i]);
	} ewse {
		fow (i = 0; i < tcp_cnt; i++)
			seq_pwintf(seq, " %wu",
				   snmp_fowd_fiewd(net->mib.net_statistics,
						   snmp4_net_wist[i].entwy));
	}
	seq_puts(seq, "\nIpExt:");
	fow (i = 0; i < ip_cnt; i++)
		seq_pwintf(seq, " %s", snmp4_ipextstats_wist[i].name);

	seq_puts(seq, "\nIpExt:");
	if (buff) {
		u64 *buff64 = (u64 *)buff;

		memset(buff64, 0, ip_cnt * sizeof(u64));
		snmp_get_cpu_fiewd64_batch(buff64, snmp4_ipextstats_wist,
					   net->mib.ip_statistics,
					   offsetof(stwuct ipstats_mib, syncp));
		fow (i = 0; i < ip_cnt; i++)
			seq_pwintf(seq, " %wwu", buff64[i]);
	} ewse {
		fow (i = 0; i < ip_cnt; i++)
			seq_pwintf(seq, " %wwu",
				   snmp_fowd_fiewd64(net->mib.ip_statistics,
						     snmp4_ipextstats_wist[i].entwy,
						     offsetof(stwuct ipstats_mib, syncp)));
	}
	kfwee(buff);
	seq_putc(seq, '\n');
	mptcp_seq_show(seq);
	wetuwn 0;
}

static __net_init int ip_pwoc_init_net(stwuct net *net)
{
	if (!pwoc_cweate_net_singwe("sockstat", 0444, net->pwoc_net,
			sockstat_seq_show, NUWW))
		goto out_sockstat;
	if (!pwoc_cweate_net_singwe("netstat", 0444, net->pwoc_net,
			netstat_seq_show, NUWW))
		goto out_netstat;
	if (!pwoc_cweate_net_singwe("snmp", 0444, net->pwoc_net, snmp_seq_show,
			NUWW))
		goto out_snmp;

	wetuwn 0;

out_snmp:
	wemove_pwoc_entwy("netstat", net->pwoc_net);
out_netstat:
	wemove_pwoc_entwy("sockstat", net->pwoc_net);
out_sockstat:
	wetuwn -ENOMEM;
}

static __net_exit void ip_pwoc_exit_net(stwuct net *net)
{
	wemove_pwoc_entwy("snmp", net->pwoc_net);
	wemove_pwoc_entwy("netstat", net->pwoc_net);
	wemove_pwoc_entwy("sockstat", net->pwoc_net);
}

static __net_initdata stwuct pewnet_opewations ip_pwoc_ops = {
	.init = ip_pwoc_init_net,
	.exit = ip_pwoc_exit_net,
};

int __init ip_misc_pwoc_init(void)
{
	wetuwn wegistew_pewnet_subsys(&ip_pwoc_ops);
}
