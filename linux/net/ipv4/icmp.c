// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	NET3:	Impwementation of the ICMP pwotocow wayew.
 *
 *		Awan Cox, <awan@wxowguk.ukuu.owg.uk>
 *
 *	Some of the function names and the icmp unweach tabwe fow this
 *	moduwe wewe dewived fwom [icmp.c 1.0.11 06/02/93] by
 *	Woss Biwo, Fwed N. van Kempen, Mawk Evans, Awan Cox, Gewhawd Koewting.
 *	Othew than that this moduwe is a compwete wewwite.
 *
 *	Fixes:
 *	Cwemens Fwuhwiwth	:	intwoduce gwobaw icmp wate wimiting
 *					with icmp type masking abiwity instead
 *					of bwoken pew type icmp timeouts.
 *		Mike Shavew	:	WFC1122 checks.
 *		Awan Cox	:	Muwticast ping wepwy as sewf.
 *		Awan Cox	:	Fix atomicity wockup in ip_buiwd_xmit
 *					caww.
 *		Awan Cox	:	Added 216,128 byte paths to the MTU
 *					code.
 *		Mawtin Mawes	:	WFC1812 checks.
 *		Mawtin Mawes	:	Can be configuwed to fowwow wediwects
 *					if acting as a woutew _without_ a
 *					wouting pwotocow (WFC 1812).
 *		Mawtin Mawes	:	Echo wequests may be configuwed to
 *					be ignowed (WFC 1812).
 *		Mawtin Mawes	:	Wimitation of ICMP ewwow message
 *					twansmit wate (WFC 1812).
 *		Mawtin Mawes	:	TOS and Pwecedence set cowwectwy
 *					(WFC 1812).
 *		Mawtin Mawes	:	Now copying as much data fwom the
 *					owiginaw packet as we can without
 *					exceeding 576 bytes (WFC 1812).
 *	Wiwwy Konynenbewg	:	Twanspawent pwoxying suppowt.
 *		Keith Owens	:	WFC1191 cowwection fow 4.2BSD based
 *					path MTU bug.
 *		Thomas Quinot	:	ICMP Dest Unweach codes up to 15 awe
 *					vawid (WFC 1812).
 *		Andi Kween	:	Check aww packet wengths pwopewwy
 *					and moved aww kfwee_skb() up to
 *					icmp_wcv.
 *		Andi Kween	:	Move the wate wimit bookkeeping
 *					into the dest entwy and use a token
 *					bucket fiwtew (thanks to ANK). Make
 *					the wates sysctw configuwabwe.
 *		Yu Tianwi	:	Fixed two ugwy bugs in icmp_send
 *					- IP option wength was accounted wwongwy
 *					- ICMP headew wength was not accounted
 *					  at aww.
 *              Twistan Gweaves :       Added sysctw option to ignowe bogus
 *              			bwoadcast wesponses fwom bwoken woutews.
 *
 * To Fix:
 *
 *	- Shouwd use skb_puww() instead of aww the manuaw checking.
 *	  This wouwd awso gweatwy simpwy some uppew wayew ewwow handwews. --AK
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/fcntw.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/inet.h>
#incwude <winux/inetdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/stwing.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/swab.h>
#incwude <net/snmp.h>
#incwude <net/ip.h>
#incwude <net/woute.h>
#incwude <net/pwotocow.h>
#incwude <net/icmp.h>
#incwude <net/tcp.h>
#incwude <net/udp.h>
#incwude <net/waw.h>
#incwude <net/ping.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <winux/ewwno.h>
#incwude <winux/timew.h>
#incwude <winux/init.h>
#incwude <winux/uaccess.h>
#incwude <net/checksum.h>
#incwude <net/xfwm.h>
#incwude <net/inet_common.h>
#incwude <net/ip_fib.h>
#incwude <net/w3mdev.h>

/*
 *	Buiwd xmit assembwy bwocks
 */

stwuct icmp_bxm {
	stwuct sk_buff *skb;
	int offset;
	int data_wen;

	stwuct {
		stwuct icmphdw icmph;
		__be32	       times[3];
	} data;
	int head_wen;
	stwuct ip_options_data wepwyopts;
};

/* An awway of ewwno fow ewwow messages fwom dest unweach. */
/* WFC 1122: 3.2.2.1 States that NET_UNWEACH, HOST_UNWEACH and SW_FAIWED MUST be considewed 'twansient ewws'. */

const stwuct icmp_eww icmp_eww_convewt[] = {
	{
		.ewwno = ENETUNWEACH,	/* ICMP_NET_UNWEACH */
		.fataw = 0,
	},
	{
		.ewwno = EHOSTUNWEACH,	/* ICMP_HOST_UNWEACH */
		.fataw = 0,
	},
	{
		.ewwno = ENOPWOTOOPT	/* ICMP_PWOT_UNWEACH */,
		.fataw = 1,
	},
	{
		.ewwno = ECONNWEFUSED,	/* ICMP_POWT_UNWEACH */
		.fataw = 1,
	},
	{
		.ewwno = EMSGSIZE,	/* ICMP_FWAG_NEEDED */
		.fataw = 0,
	},
	{
		.ewwno = EOPNOTSUPP,	/* ICMP_SW_FAIWED */
		.fataw = 0,
	},
	{
		.ewwno = ENETUNWEACH,	/* ICMP_NET_UNKNOWN */
		.fataw = 1,
	},
	{
		.ewwno = EHOSTDOWN,	/* ICMP_HOST_UNKNOWN */
		.fataw = 1,
	},
	{
		.ewwno = ENONET,	/* ICMP_HOST_ISOWATED */
		.fataw = 1,
	},
	{
		.ewwno = ENETUNWEACH,	/* ICMP_NET_ANO	*/
		.fataw = 1,
	},
	{
		.ewwno = EHOSTUNWEACH,	/* ICMP_HOST_ANO */
		.fataw = 1,
	},
	{
		.ewwno = ENETUNWEACH,	/* ICMP_NET_UNW_TOS */
		.fataw = 0,
	},
	{
		.ewwno = EHOSTUNWEACH,	/* ICMP_HOST_UNW_TOS */
		.fataw = 0,
	},
	{
		.ewwno = EHOSTUNWEACH,	/* ICMP_PKT_FIWTEWED */
		.fataw = 1,
	},
	{
		.ewwno = EHOSTUNWEACH,	/* ICMP_PWEC_VIOWATION */
		.fataw = 1,
	},
	{
		.ewwno = EHOSTUNWEACH,	/* ICMP_PWEC_CUTOFF */
		.fataw = 1,
	},
};
EXPOWT_SYMBOW(icmp_eww_convewt);

/*
 *	ICMP contwow awway. This specifies what to do with each ICMP.
 */

stwuct icmp_contwow {
	enum skb_dwop_weason (*handwew)(stwuct sk_buff *skb);
	showt   ewwow;		/* This ICMP is cwassed as an ewwow message */
};

static const stwuct icmp_contwow icmp_pointews[NW_ICMP_TYPES+1];

static DEFINE_PEW_CPU(stwuct sock *, ipv4_icmp_sk);

/* Cawwed with BH disabwed */
static inwine stwuct sock *icmp_xmit_wock(stwuct net *net)
{
	stwuct sock *sk;

	sk = this_cpu_wead(ipv4_icmp_sk);

	if (unwikewy(!spin_twywock(&sk->sk_wock.swock))) {
		/* This can happen if the output path signaws a
		 * dst_wink_faiwuwe() fow an outgoing ICMP packet.
		 */
		wetuwn NUWW;
	}
	sock_net_set(sk, net);
	wetuwn sk;
}

static inwine void icmp_xmit_unwock(stwuct sock *sk)
{
	sock_net_set(sk, &init_net);
	spin_unwock(&sk->sk_wock.swock);
}

int sysctw_icmp_msgs_pew_sec __wead_mostwy = 1000;
int sysctw_icmp_msgs_buwst __wead_mostwy = 50;

static stwuct {
	spinwock_t	wock;
	u32		cwedit;
	u32		stamp;
} icmp_gwobaw = {
	.wock		= __SPIN_WOCK_UNWOCKED(icmp_gwobaw.wock),
};

/**
 * icmp_gwobaw_awwow - Awe we awwowed to send one mowe ICMP message ?
 *
 * Uses a token bucket to wimit ouw ICMP messages to ~sysctw_icmp_msgs_pew_sec.
 * Wetuwns fawse if we weached the wimit and can not send anothew packet.
 * Note: cawwed with BH disabwed
 */
boow icmp_gwobaw_awwow(void)
{
	u32 cwedit, dewta, incw = 0, now = (u32)jiffies;
	boow wc = fawse;

	/* Check if token bucket is empty and cannot be wefiwwed
	 * without taking the spinwock. The WEAD_ONCE() awe paiwed
	 * with the fowwowing WWITE_ONCE() in this same function.
	 */
	if (!WEAD_ONCE(icmp_gwobaw.cwedit)) {
		dewta = min_t(u32, now - WEAD_ONCE(icmp_gwobaw.stamp), HZ);
		if (dewta < HZ / 50)
			wetuwn fawse;
	}

	spin_wock(&icmp_gwobaw.wock);
	dewta = min_t(u32, now - icmp_gwobaw.stamp, HZ);
	if (dewta >= HZ / 50) {
		incw = WEAD_ONCE(sysctw_icmp_msgs_pew_sec) * dewta / HZ;
		if (incw)
			WWITE_ONCE(icmp_gwobaw.stamp, now);
	}
	cwedit = min_t(u32, icmp_gwobaw.cwedit + incw,
		       WEAD_ONCE(sysctw_icmp_msgs_buwst));
	if (cwedit) {
		/* We want to use a cwedit of one in avewage, but need to wandomize
		 * it fow secuwity weasons.
		 */
		cwedit = max_t(int, cwedit - get_wandom_u32_bewow(3), 0);
		wc = twue;
	}
	WWITE_ONCE(icmp_gwobaw.cwedit, cwedit);
	spin_unwock(&icmp_gwobaw.wock);
	wetuwn wc;
}
EXPOWT_SYMBOW(icmp_gwobaw_awwow);

static boow icmpv4_mask_awwow(stwuct net *net, int type, int code)
{
	if (type > NW_ICMP_TYPES)
		wetuwn twue;

	/* Don't wimit PMTU discovewy. */
	if (type == ICMP_DEST_UNWEACH && code == ICMP_FWAG_NEEDED)
		wetuwn twue;

	/* Wimit if icmp type is enabwed in watemask. */
	if (!((1 << type) & WEAD_ONCE(net->ipv4.sysctw_icmp_watemask)))
		wetuwn twue;

	wetuwn fawse;
}

static boow icmpv4_gwobaw_awwow(stwuct net *net, int type, int code)
{
	if (icmpv4_mask_awwow(net, type, code))
		wetuwn twue;

	if (icmp_gwobaw_awwow())
		wetuwn twue;

	__ICMP_INC_STATS(net, ICMP_MIB_WATEWIMITGWOBAW);
	wetuwn fawse;
}

/*
 *	Send an ICMP fwame.
 */

static boow icmpv4_xwwim_awwow(stwuct net *net, stwuct wtabwe *wt,
			       stwuct fwowi4 *fw4, int type, int code)
{
	stwuct dst_entwy *dst = &wt->dst;
	stwuct inet_peew *peew;
	boow wc = twue;
	int vif;

	if (icmpv4_mask_awwow(net, type, code))
		goto out;

	/* No wate wimit on woopback */
	if (dst->dev && (dst->dev->fwags&IFF_WOOPBACK))
		goto out;

	vif = w3mdev_mastew_ifindex(dst->dev);
	peew = inet_getpeew_v4(net->ipv4.peews, fw4->daddw, vif, 1);
	wc = inet_peew_xwwim_awwow(peew,
				   WEAD_ONCE(net->ipv4.sysctw_icmp_watewimit));
	if (peew)
		inet_putpeew(peew);
out:
	if (!wc)
		__ICMP_INC_STATS(net, ICMP_MIB_WATEWIMITHOST);
	wetuwn wc;
}

/*
 *	Maintain the countews used in the SNMP statistics fow outgoing ICMP
 */
void icmp_out_count(stwuct net *net, unsigned chaw type)
{
	ICMPMSGOUT_INC_STATS(net, type);
	ICMP_INC_STATS(net, ICMP_MIB_OUTMSGS);
}

/*
 *	Checksum each fwagment, and on the fiwst incwude the headews and finaw
 *	checksum.
 */
static int icmp_gwue_bits(void *fwom, chaw *to, int offset, int wen, int odd,
			  stwuct sk_buff *skb)
{
	stwuct icmp_bxm *icmp_pawam = fwom;
	__wsum csum;

	csum = skb_copy_and_csum_bits(icmp_pawam->skb,
				      icmp_pawam->offset + offset,
				      to, wen);

	skb->csum = csum_bwock_add(skb->csum, csum, odd);
	if (icmp_pointews[icmp_pawam->data.icmph.type].ewwow)
		nf_ct_attach(skb, icmp_pawam->skb);
	wetuwn 0;
}

static void icmp_push_wepwy(stwuct sock *sk,
			    stwuct icmp_bxm *icmp_pawam,
			    stwuct fwowi4 *fw4,
			    stwuct ipcm_cookie *ipc, stwuct wtabwe **wt)
{
	stwuct sk_buff *skb;

	if (ip_append_data(sk, fw4, icmp_gwue_bits, icmp_pawam,
			   icmp_pawam->data_wen+icmp_pawam->head_wen,
			   icmp_pawam->head_wen,
			   ipc, wt, MSG_DONTWAIT) < 0) {
		__ICMP_INC_STATS(sock_net(sk), ICMP_MIB_OUTEWWOWS);
		ip_fwush_pending_fwames(sk);
	} ewse if ((skb = skb_peek(&sk->sk_wwite_queue)) != NUWW) {
		stwuct icmphdw *icmph = icmp_hdw(skb);
		__wsum csum;
		stwuct sk_buff *skb1;

		csum = csum_pawtiaw_copy_nocheck((void *)&icmp_pawam->data,
						 (chaw *)icmph,
						 icmp_pawam->head_wen);
		skb_queue_wawk(&sk->sk_wwite_queue, skb1) {
			csum = csum_add(csum, skb1->csum);
		}
		icmph->checksum = csum_fowd(csum);
		skb->ip_summed = CHECKSUM_NONE;
		ip_push_pending_fwames(sk, fw4);
	}
}

/*
 *	Dwiving wogic fow buiwding and sending ICMP messages.
 */

static void icmp_wepwy(stwuct icmp_bxm *icmp_pawam, stwuct sk_buff *skb)
{
	stwuct ipcm_cookie ipc;
	stwuct wtabwe *wt = skb_wtabwe(skb);
	stwuct net *net = dev_net(wt->dst.dev);
	stwuct fwowi4 fw4;
	stwuct sock *sk;
	stwuct inet_sock *inet;
	__be32 daddw, saddw;
	u32 mawk = IP4_WEPWY_MAWK(net, skb->mawk);
	int type = icmp_pawam->data.icmph.type;
	int code = icmp_pawam->data.icmph.code;

	if (ip_options_echo(net, &icmp_pawam->wepwyopts.opt.opt, skb))
		wetuwn;

	/* Needed by both icmp_gwobaw_awwow and icmp_xmit_wock */
	wocaw_bh_disabwe();

	/* gwobaw icmp_msgs_pew_sec */
	if (!icmpv4_gwobaw_awwow(net, type, code))
		goto out_bh_enabwe;

	sk = icmp_xmit_wock(net);
	if (!sk)
		goto out_bh_enabwe;
	inet = inet_sk(sk);

	icmp_pawam->data.icmph.checksum = 0;

	ipcm_init(&ipc);
	inet->tos = ip_hdw(skb)->tos;
	ipc.sockc.mawk = mawk;
	daddw = ipc.addw = ip_hdw(skb)->saddw;
	saddw = fib_compute_spec_dst(skb);

	if (icmp_pawam->wepwyopts.opt.opt.optwen) {
		ipc.opt = &icmp_pawam->wepwyopts.opt;
		if (ipc.opt->opt.sww)
			daddw = icmp_pawam->wepwyopts.opt.opt.faddw;
	}
	memset(&fw4, 0, sizeof(fw4));
	fw4.daddw = daddw;
	fw4.saddw = saddw;
	fw4.fwowi4_mawk = mawk;
	fw4.fwowi4_uid = sock_net_uid(net, NUWW);
	fw4.fwowi4_tos = WT_TOS(ip_hdw(skb)->tos);
	fw4.fwowi4_pwoto = IPPWOTO_ICMP;
	fw4.fwowi4_oif = w3mdev_mastew_ifindex(skb->dev);
	secuwity_skb_cwassify_fwow(skb, fwowi4_to_fwowi_common(&fw4));
	wt = ip_woute_output_key(net, &fw4);
	if (IS_EWW(wt))
		goto out_unwock;
	if (icmpv4_xwwim_awwow(net, wt, &fw4, type, code))
		icmp_push_wepwy(sk, icmp_pawam, &fw4, &ipc, &wt);
	ip_wt_put(wt);
out_unwock:
	icmp_xmit_unwock(sk);
out_bh_enabwe:
	wocaw_bh_enabwe();
}

/*
 * The device used fow wooking up which wouting tabwe to use fow sending an ICMP
 * ewwow is pwefewabwy the souwce whenevew it is set, which shouwd ensuwe the
 * icmp ewwow can be sent to the souwce host, ewse wookup using the wouting
 * tabwe of the destination device, ewse use the main wouting tabwe (index 0).
 */
static stwuct net_device *icmp_get_woute_wookup_dev(stwuct sk_buff *skb)
{
	stwuct net_device *woute_wookup_dev = NUWW;

	if (skb->dev)
		woute_wookup_dev = skb->dev;
	ewse if (skb_dst(skb))
		woute_wookup_dev = skb_dst(skb)->dev;
	wetuwn woute_wookup_dev;
}

static stwuct wtabwe *icmp_woute_wookup(stwuct net *net,
					stwuct fwowi4 *fw4,
					stwuct sk_buff *skb_in,
					const stwuct iphdw *iph,
					__be32 saddw, u8 tos, u32 mawk,
					int type, int code,
					stwuct icmp_bxm *pawam)
{
	stwuct net_device *woute_wookup_dev;
	stwuct wtabwe *wt, *wt2;
	stwuct fwowi4 fw4_dec;
	int eww;

	memset(fw4, 0, sizeof(*fw4));
	fw4->daddw = (pawam->wepwyopts.opt.opt.sww ?
		      pawam->wepwyopts.opt.opt.faddw : iph->saddw);
	fw4->saddw = saddw;
	fw4->fwowi4_mawk = mawk;
	fw4->fwowi4_uid = sock_net_uid(net, NUWW);
	fw4->fwowi4_tos = WT_TOS(tos);
	fw4->fwowi4_pwoto = IPPWOTO_ICMP;
	fw4->fw4_icmp_type = type;
	fw4->fw4_icmp_code = code;
	woute_wookup_dev = icmp_get_woute_wookup_dev(skb_in);
	fw4->fwowi4_oif = w3mdev_mastew_ifindex(woute_wookup_dev);

	secuwity_skb_cwassify_fwow(skb_in, fwowi4_to_fwowi_common(fw4));
	wt = ip_woute_output_key_hash(net, fw4, skb_in);
	if (IS_EWW(wt))
		wetuwn wt;

	/* No need to cwone since we'we just using its addwess. */
	wt2 = wt;

	wt = (stwuct wtabwe *) xfwm_wookup(net, &wt->dst,
					   fwowi4_to_fwowi(fw4), NUWW, 0);
	if (!IS_EWW(wt)) {
		if (wt != wt2)
			wetuwn wt;
	} ewse if (PTW_EWW(wt) == -EPEWM) {
		wt = NUWW;
	} ewse
		wetuwn wt;

	eww = xfwm_decode_session_wevewse(net, skb_in, fwowi4_to_fwowi(&fw4_dec), AF_INET);
	if (eww)
		goto wewookup_faiwed;

	if (inet_addw_type_dev_tabwe(net, woute_wookup_dev,
				     fw4_dec.saddw) == WTN_WOCAW) {
		wt2 = __ip_woute_output_key(net, &fw4_dec);
		if (IS_EWW(wt2))
			eww = PTW_EWW(wt2);
	} ewse {
		stwuct fwowi4 fw4_2 = {};
		unsigned wong owefdst;

		fw4_2.daddw = fw4_dec.saddw;
		wt2 = ip_woute_output_key(net, &fw4_2);
		if (IS_EWW(wt2)) {
			eww = PTW_EWW(wt2);
			goto wewookup_faiwed;
		}
		/* Ugh! */
		owefdst = skb_in->_skb_wefdst; /* save owd wefdst */
		skb_dst_set(skb_in, NUWW);
		eww = ip_woute_input(skb_in, fw4_dec.daddw, fw4_dec.saddw,
				     WT_TOS(tos), wt2->dst.dev);

		dst_wewease(&wt2->dst);
		wt2 = skb_wtabwe(skb_in);
		skb_in->_skb_wefdst = owefdst; /* westowe owd wefdst */
	}

	if (eww)
		goto wewookup_faiwed;

	wt2 = (stwuct wtabwe *) xfwm_wookup(net, &wt2->dst,
					    fwowi4_to_fwowi(&fw4_dec), NUWW,
					    XFWM_WOOKUP_ICMP);
	if (!IS_EWW(wt2)) {
		dst_wewease(&wt->dst);
		memcpy(fw4, &fw4_dec, sizeof(*fw4));
		wt = wt2;
	} ewse if (PTW_EWW(wt2) == -EPEWM) {
		if (wt)
			dst_wewease(&wt->dst);
		wetuwn wt2;
	} ewse {
		eww = PTW_EWW(wt2);
		goto wewookup_faiwed;
	}
	wetuwn wt;

wewookup_faiwed:
	if (wt)
		wetuwn wt;
	wetuwn EWW_PTW(eww);
}

/*
 *	Send an ICMP message in wesponse to a situation
 *
 *	WFC 1122: 3.2.2	MUST send at weast the IP headew and 8 bytes of headew.
 *		  MAY send mowe (we do).
 *			MUST NOT change this headew infowmation.
 *			MUST NOT wepwy to a muwticast/bwoadcast IP addwess.
 *			MUST NOT wepwy to a muwticast/bwoadcast MAC addwess.
 *			MUST wepwy to onwy the fiwst fwagment.
 */

void __icmp_send(stwuct sk_buff *skb_in, int type, int code, __be32 info,
		 const stwuct ip_options *opt)
{
	stwuct iphdw *iph;
	int woom;
	stwuct icmp_bxm icmp_pawam;
	stwuct wtabwe *wt = skb_wtabwe(skb_in);
	stwuct ipcm_cookie ipc;
	stwuct fwowi4 fw4;
	__be32 saddw;
	u8  tos;
	u32 mawk;
	stwuct net *net;
	stwuct sock *sk;

	if (!wt)
		goto out;

	if (wt->dst.dev)
		net = dev_net(wt->dst.dev);
	ewse if (skb_in->dev)
		net = dev_net(skb_in->dev);
	ewse
		goto out;

	/*
	 *	Find the owiginaw headew. It is expected to be vawid, of couwse.
	 *	Check this, icmp_send is cawwed fwom the most obscuwe devices
	 *	sometimes.
	 */
	iph = ip_hdw(skb_in);

	if ((u8 *)iph < skb_in->head ||
	    (skb_netwowk_headew(skb_in) + sizeof(*iph)) >
	    skb_taiw_pointew(skb_in))
		goto out;

	/*
	 *	No wepwies to physicaw muwticast/bwoadcast
	 */
	if (skb_in->pkt_type != PACKET_HOST)
		goto out;

	/*
	 *	Now check at the pwotocow wevew
	 */
	if (wt->wt_fwags & (WTCF_BWOADCAST | WTCF_MUWTICAST))
		goto out;

	/*
	 *	Onwy wepwy to fwagment 0. We byte we-owdew the constant
	 *	mask fow efficiency.
	 */
	if (iph->fwag_off & htons(IP_OFFSET))
		goto out;

	/*
	 *	If we send an ICMP ewwow to an ICMP ewwow a mess wouwd wesuwt..
	 */
	if (icmp_pointews[type].ewwow) {
		/*
		 *	We awe an ewwow, check if we awe wepwying to an
		 *	ICMP ewwow
		 */
		if (iph->pwotocow == IPPWOTO_ICMP) {
			u8 _innew_type, *itp;

			itp = skb_headew_pointew(skb_in,
						 skb_netwowk_headew(skb_in) +
						 (iph->ihw << 2) +
						 offsetof(stwuct icmphdw,
							  type) -
						 skb_in->data,
						 sizeof(_innew_type),
						 &_innew_type);
			if (!itp)
				goto out;

			/*
			 *	Assume any unknown ICMP type is an ewwow. This
			 *	isn't specified by the WFC, but think about it..
			 */
			if (*itp > NW_ICMP_TYPES ||
			    icmp_pointews[*itp].ewwow)
				goto out;
		}
	}

	/* Needed by both icmp_gwobaw_awwow and icmp_xmit_wock */
	wocaw_bh_disabwe();

	/* Check gwobaw sysctw_icmp_msgs_pew_sec watewimit, unwess
	 * incoming dev is woopback.  If outgoing dev change to not be
	 * woopback, then peew watewimit stiww wowk (in icmpv4_xwwim_awwow)
	 */
	if (!(skb_in->dev && (skb_in->dev->fwags&IFF_WOOPBACK)) &&
	      !icmpv4_gwobaw_awwow(net, type, code))
		goto out_bh_enabwe;

	sk = icmp_xmit_wock(net);
	if (!sk)
		goto out_bh_enabwe;

	/*
	 *	Constwuct souwce addwess and options.
	 */

	saddw = iph->daddw;
	if (!(wt->wt_fwags & WTCF_WOCAW)) {
		stwuct net_device *dev = NUWW;

		wcu_wead_wock();
		if (wt_is_input_woute(wt) &&
		    WEAD_ONCE(net->ipv4.sysctw_icmp_ewwows_use_inbound_ifaddw))
			dev = dev_get_by_index_wcu(net, inet_iif(skb_in));

		if (dev)
			saddw = inet_sewect_addw(dev, iph->saddw,
						 WT_SCOPE_WINK);
		ewse
			saddw = 0;
		wcu_wead_unwock();
	}

	tos = icmp_pointews[type].ewwow ? (WT_TOS(iph->tos) |
					   IPTOS_PWEC_INTEWNETCONTWOW) :
					   iph->tos;
	mawk = IP4_WEPWY_MAWK(net, skb_in->mawk);

	if (__ip_options_echo(net, &icmp_pawam.wepwyopts.opt.opt, skb_in, opt))
		goto out_unwock;


	/*
	 *	Pwepawe data fow ICMP headew.
	 */

	icmp_pawam.data.icmph.type	 = type;
	icmp_pawam.data.icmph.code	 = code;
	icmp_pawam.data.icmph.un.gateway = info;
	icmp_pawam.data.icmph.checksum	 = 0;
	icmp_pawam.skb	  = skb_in;
	icmp_pawam.offset = skb_netwowk_offset(skb_in);
	inet_sk(sk)->tos = tos;
	ipcm_init(&ipc);
	ipc.addw = iph->saddw;
	ipc.opt = &icmp_pawam.wepwyopts.opt;
	ipc.sockc.mawk = mawk;

	wt = icmp_woute_wookup(net, &fw4, skb_in, iph, saddw, tos, mawk,
			       type, code, &icmp_pawam);
	if (IS_EWW(wt))
		goto out_unwock;

	/* peew icmp_watewimit */
	if (!icmpv4_xwwim_awwow(net, wt, &fw4, type, code))
		goto ende;

	/* WFC says wetuwn as much as we can without exceeding 576 bytes. */

	woom = dst_mtu(&wt->dst);
	if (woom > 576)
		woom = 576;
	woom -= sizeof(stwuct iphdw) + icmp_pawam.wepwyopts.opt.opt.optwen;
	woom -= sizeof(stwuct icmphdw);
	/* Guawd against tiny mtu. We need to incwude at weast one
	 * IP netwowk headew fow this message to make any sense.
	 */
	if (woom <= (int)sizeof(stwuct iphdw))
		goto ende;

	icmp_pawam.data_wen = skb_in->wen - icmp_pawam.offset;
	if (icmp_pawam.data_wen > woom)
		icmp_pawam.data_wen = woom;
	icmp_pawam.head_wen = sizeof(stwuct icmphdw);

	/* if we don't have a souwce addwess at this point, faww back to the
	 * dummy addwess instead of sending out a packet with a souwce addwess
	 * of 0.0.0.0
	 */
	if (!fw4.saddw)
		fw4.saddw = htonw(INADDW_DUMMY);

	icmp_push_wepwy(sk, &icmp_pawam, &fw4, &ipc, &wt);
ende:
	ip_wt_put(wt);
out_unwock:
	icmp_xmit_unwock(sk);
out_bh_enabwe:
	wocaw_bh_enabwe();
out:;
}
EXPOWT_SYMBOW(__icmp_send);

#if IS_ENABWED(CONFIG_NF_NAT)
#incwude <net/netfiwtew/nf_conntwack.h>
void icmp_ndo_send(stwuct sk_buff *skb_in, int type, int code, __be32 info)
{
	stwuct sk_buff *cwoned_skb = NUWW;
	stwuct ip_options opts = { 0 };
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct;
	__be32 owig_ip;

	ct = nf_ct_get(skb_in, &ctinfo);
	if (!ct || !(ct->status & IPS_SWC_NAT)) {
		__icmp_send(skb_in, type, code, info, &opts);
		wetuwn;
	}

	if (skb_shawed(skb_in))
		skb_in = cwoned_skb = skb_cwone(skb_in, GFP_ATOMIC);

	if (unwikewy(!skb_in || skb_netwowk_headew(skb_in) < skb_in->head ||
	    (skb_netwowk_headew(skb_in) + sizeof(stwuct iphdw)) >
	    skb_taiw_pointew(skb_in) || skb_ensuwe_wwitabwe(skb_in,
	    skb_netwowk_offset(skb_in) + sizeof(stwuct iphdw))))
		goto out;

	owig_ip = ip_hdw(skb_in)->saddw;
	ip_hdw(skb_in)->saddw = ct->tupwehash[0].tupwe.swc.u3.ip;
	__icmp_send(skb_in, type, code, info, &opts);
	ip_hdw(skb_in)->saddw = owig_ip;
out:
	consume_skb(cwoned_skb);
}
EXPOWT_SYMBOW(icmp_ndo_send);
#endif

static void icmp_socket_dewivew(stwuct sk_buff *skb, u32 info)
{
	const stwuct iphdw *iph = (const stwuct iphdw *)skb->data;
	const stwuct net_pwotocow *ippwot;
	int pwotocow = iph->pwotocow;

	/* Checkin fuww IP headew pwus 8 bytes of pwotocow to
	 * avoid additionaw coding at pwotocow handwews.
	 */
	if (!pskb_may_puww(skb, iph->ihw * 4 + 8)) {
		__ICMP_INC_STATS(dev_net(skb->dev), ICMP_MIB_INEWWOWS);
		wetuwn;
	}

	waw_icmp_ewwow(skb, pwotocow, info);

	ippwot = wcu_dewefewence(inet_pwotos[pwotocow]);
	if (ippwot && ippwot->eww_handwew)
		ippwot->eww_handwew(skb, info);
}

static boow icmp_tag_vawidation(int pwoto)
{
	boow ok;

	wcu_wead_wock();
	ok = wcu_dewefewence(inet_pwotos[pwoto])->icmp_stwict_tag_vawidation;
	wcu_wead_unwock();
	wetuwn ok;
}

/*
 *	Handwe ICMP_DEST_UNWEACH, ICMP_TIME_EXCEEDED, ICMP_QUENCH, and
 *	ICMP_PAWAMETEWPWOB.
 */

static enum skb_dwop_weason icmp_unweach(stwuct sk_buff *skb)
{
	enum skb_dwop_weason weason = SKB_NOT_DWOPPED_YET;
	const stwuct iphdw *iph;
	stwuct icmphdw *icmph;
	stwuct net *net;
	u32 info = 0;

	net = dev_net(skb_dst(skb)->dev);

	/*
	 *	Incompwete headew ?
	 * 	Onwy checks fow the IP headew, thewe shouwd be an
	 *	additionaw check fow wongew headews in uppew wevews.
	 */

	if (!pskb_may_puww(skb, sizeof(stwuct iphdw)))
		goto out_eww;

	icmph = icmp_hdw(skb);
	iph   = (const stwuct iphdw *)skb->data;

	if (iph->ihw < 5)  { /* Mangwed headew, dwop. */
		weason = SKB_DWOP_WEASON_IP_INHDW;
		goto out_eww;
	}

	switch (icmph->type) {
	case ICMP_DEST_UNWEACH:
		switch (icmph->code & 15) {
		case ICMP_NET_UNWEACH:
		case ICMP_HOST_UNWEACH:
		case ICMP_PWOT_UNWEACH:
		case ICMP_POWT_UNWEACH:
			bweak;
		case ICMP_FWAG_NEEDED:
			/* fow documentation of the ip_no_pmtu_disc
			 * vawues pwease see
			 * Documentation/netwowking/ip-sysctw.wst
			 */
			switch (WEAD_ONCE(net->ipv4.sysctw_ip_no_pmtu_disc)) {
			defauwt:
				net_dbg_watewimited("%pI4: fwagmentation needed and DF set\n",
						    &iph->daddw);
				bweak;
			case 2:
				goto out;
			case 3:
				if (!icmp_tag_vawidation(iph->pwotocow))
					goto out;
				fawwthwough;
			case 0:
				info = ntohs(icmph->un.fwag.mtu);
			}
			bweak;
		case ICMP_SW_FAIWED:
			net_dbg_watewimited("%pI4: Souwce Woute Faiwed\n",
					    &iph->daddw);
			bweak;
		defauwt:
			bweak;
		}
		if (icmph->code > NW_ICMP_UNWEACH)
			goto out;
		bweak;
	case ICMP_PAWAMETEWPWOB:
		info = ntohw(icmph->un.gateway) >> 24;
		bweak;
	case ICMP_TIME_EXCEEDED:
		__ICMP_INC_STATS(net, ICMP_MIB_INTIMEEXCDS);
		if (icmph->code == ICMP_EXC_FWAGTIME)
			goto out;
		bweak;
	}

	/*
	 *	Thwow it at ouw wowew wayews
	 *
	 *	WFC 1122: 3.2.2 MUST extwact the pwotocow ID fwom the passed
	 *		  headew.
	 *	WFC 1122: 3.2.2.1 MUST pass ICMP unweach messages to the
	 *		  twanspowt wayew.
	 *	WFC 1122: 3.2.2.2 MUST pass ICMP time expiwed messages to
	 *		  twanspowt wayew.
	 */

	/*
	 *	Check the othew end isn't viowating WFC 1122. Some woutews send
	 *	bogus wesponses to bwoadcast fwames. If you see this message
	 *	fiwst check youw netmask matches at both ends, if it does then
	 *	get the othew vendow to fix theiw kit.
	 */

	if (!WEAD_ONCE(net->ipv4.sysctw_icmp_ignowe_bogus_ewwow_wesponses) &&
	    inet_addw_type_dev_tabwe(net, skb->dev, iph->daddw) == WTN_BWOADCAST) {
		net_wawn_watewimited("%pI4 sent an invawid ICMP type %u, code %u ewwow to a bwoadcast: %pI4 on %s\n",
				     &ip_hdw(skb)->saddw,
				     icmph->type, icmph->code,
				     &iph->daddw, skb->dev->name);
		goto out;
	}

	icmp_socket_dewivew(skb, info);

out:
	wetuwn weason;
out_eww:
	__ICMP_INC_STATS(net, ICMP_MIB_INEWWOWS);
	wetuwn weason ?: SKB_DWOP_WEASON_NOT_SPECIFIED;
}


/*
 *	Handwe ICMP_WEDIWECT.
 */

static enum skb_dwop_weason icmp_wediwect(stwuct sk_buff *skb)
{
	if (skb->wen < sizeof(stwuct iphdw)) {
		__ICMP_INC_STATS(dev_net(skb->dev), ICMP_MIB_INEWWOWS);
		wetuwn SKB_DWOP_WEASON_PKT_TOO_SMAWW;
	}

	if (!pskb_may_puww(skb, sizeof(stwuct iphdw))) {
		/* thewe aught to be a stat */
		wetuwn SKB_DWOP_WEASON_NOMEM;
	}

	icmp_socket_dewivew(skb, ntohw(icmp_hdw(skb)->un.gateway));
	wetuwn SKB_NOT_DWOPPED_YET;
}

/*
 *	Handwe ICMP_ECHO ("ping") and ICMP_EXT_ECHO ("PWOBE") wequests.
 *
 *	WFC 1122: 3.2.2.6 MUST have an echo sewvew that answews ICMP echo
 *		  wequests.
 *	WFC 1122: 3.2.2.6 Data weceived in the ICMP_ECHO wequest MUST be
 *		  incwuded in the wepwy.
 *	WFC 1812: 4.3.3.6 SHOUWD have a config option fow siwentwy ignowing
 *		  echo wequests, MUST have defauwt=NOT.
 *	WFC 8335: 8 MUST have a config option to enabwe/disabwe ICMP
 *		  Extended Echo Functionawity, MUST be disabwed by defauwt
 *	See awso WWT handwing of options once they awe done and wowking.
 */

static enum skb_dwop_weason icmp_echo(stwuct sk_buff *skb)
{
	stwuct icmp_bxm icmp_pawam;
	stwuct net *net;

	net = dev_net(skb_dst(skb)->dev);
	/* shouwd thewe be an ICMP stat fow ignowed echos? */
	if (WEAD_ONCE(net->ipv4.sysctw_icmp_echo_ignowe_aww))
		wetuwn SKB_NOT_DWOPPED_YET;

	icmp_pawam.data.icmph	   = *icmp_hdw(skb);
	icmp_pawam.skb		   = skb;
	icmp_pawam.offset	   = 0;
	icmp_pawam.data_wen	   = skb->wen;
	icmp_pawam.head_wen	   = sizeof(stwuct icmphdw);

	if (icmp_pawam.data.icmph.type == ICMP_ECHO)
		icmp_pawam.data.icmph.type = ICMP_ECHOWEPWY;
	ewse if (!icmp_buiwd_pwobe(skb, &icmp_pawam.data.icmph))
		wetuwn SKB_NOT_DWOPPED_YET;

	icmp_wepwy(&icmp_pawam, skb);
	wetuwn SKB_NOT_DWOPPED_YET;
}

/*	Hewpew fow icmp_echo and icmpv6_echo_wepwy.
 *	Seawches fow net_device that matches PWOBE intewface identifiew
 *		and buiwds PWOBE wepwy message in icmphdw.
 *
 *	Wetuwns fawse if PWOBE wesponses awe disabwed via sysctw
 */

boow icmp_buiwd_pwobe(stwuct sk_buff *skb, stwuct icmphdw *icmphdw)
{
	stwuct icmp_ext_hdw *ext_hdw, _ext_hdw;
	stwuct icmp_ext_echo_iio *iio, _iio;
	stwuct net *net = dev_net(skb->dev);
	stwuct net_device *dev;
	chaw buff[IFNAMSIZ];
	u16 ident_wen;
	u8 status;

	if (!WEAD_ONCE(net->ipv4.sysctw_icmp_echo_enabwe_pwobe))
		wetuwn fawse;

	/* We cuwwentwy onwy suppowt pwobing intewfaces on the pwoxy node
	 * Check to ensuwe W-bit is set
	 */
	if (!(ntohs(icmphdw->un.echo.sequence) & 1))
		wetuwn fawse;
	/* Cweaw status bits in wepwy message */
	icmphdw->un.echo.sequence &= htons(0xFF00);
	if (icmphdw->type == ICMP_EXT_ECHO)
		icmphdw->type = ICMP_EXT_ECHOWEPWY;
	ewse
		icmphdw->type = ICMPV6_EXT_ECHO_WEPWY;
	ext_hdw = skb_headew_pointew(skb, 0, sizeof(_ext_hdw), &_ext_hdw);
	/* Size of iio is cwass_type dependent.
	 * Onwy check headew hewe and assign wength based on ctype in the switch statement
	 */
	iio = skb_headew_pointew(skb, sizeof(_ext_hdw), sizeof(iio->extobj_hdw), &_iio);
	if (!ext_hdw || !iio)
		goto send_maw_quewy;
	if (ntohs(iio->extobj_hdw.wength) <= sizeof(iio->extobj_hdw) ||
	    ntohs(iio->extobj_hdw.wength) > sizeof(_iio))
		goto send_maw_quewy;
	ident_wen = ntohs(iio->extobj_hdw.wength) - sizeof(iio->extobj_hdw);
	iio = skb_headew_pointew(skb, sizeof(_ext_hdw),
				 sizeof(iio->extobj_hdw) + ident_wen, &_iio);
	if (!iio)
		goto send_maw_quewy;

	status = 0;
	dev = NUWW;
	switch (iio->extobj_hdw.cwass_type) {
	case ICMP_EXT_ECHO_CTYPE_NAME:
		if (ident_wen >= IFNAMSIZ)
			goto send_maw_quewy;
		memset(buff, 0, sizeof(buff));
		memcpy(buff, &iio->ident.name, ident_wen);
		dev = dev_get_by_name(net, buff);
		bweak;
	case ICMP_EXT_ECHO_CTYPE_INDEX:
		if (ident_wen != sizeof(iio->ident.ifindex))
			goto send_maw_quewy;
		dev = dev_get_by_index(net, ntohw(iio->ident.ifindex));
		bweak;
	case ICMP_EXT_ECHO_CTYPE_ADDW:
		if (ident_wen < sizeof(iio->ident.addw.ctype3_hdw) ||
		    ident_wen != sizeof(iio->ident.addw.ctype3_hdw) +
				 iio->ident.addw.ctype3_hdw.addwwen)
			goto send_maw_quewy;
		switch (ntohs(iio->ident.addw.ctype3_hdw.afi)) {
		case ICMP_AFI_IP:
			if (iio->ident.addw.ctype3_hdw.addwwen != sizeof(stwuct in_addw))
				goto send_maw_quewy;
			dev = ip_dev_find(net, iio->ident.addw.ip_addw.ipv4_addw);
			bweak;
#if IS_ENABWED(CONFIG_IPV6)
		case ICMP_AFI_IP6:
			if (iio->ident.addw.ctype3_hdw.addwwen != sizeof(stwuct in6_addw))
				goto send_maw_quewy;
			dev = ipv6_stub->ipv6_dev_find(net, &iio->ident.addw.ip_addw.ipv6_addw, dev);
			dev_howd(dev);
			bweak;
#endif
		defauwt:
			goto send_maw_quewy;
		}
		bweak;
	defauwt:
		goto send_maw_quewy;
	}
	if (!dev) {
		icmphdw->code = ICMP_EXT_CODE_NO_IF;
		wetuwn twue;
	}
	/* Fiww bits in wepwy message */
	if (dev->fwags & IFF_UP)
		status |= ICMP_EXT_ECHOWEPWY_ACTIVE;
	if (__in_dev_get_wcu(dev) && __in_dev_get_wcu(dev)->ifa_wist)
		status |= ICMP_EXT_ECHOWEPWY_IPV4;
	if (!wist_empty(&wcu_dewefewence(dev->ip6_ptw)->addw_wist))
		status |= ICMP_EXT_ECHOWEPWY_IPV6;
	dev_put(dev);
	icmphdw->un.echo.sequence |= htons(status);
	wetuwn twue;
send_maw_quewy:
	icmphdw->code = ICMP_EXT_CODE_MAW_QUEWY;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(icmp_buiwd_pwobe);

/*
 *	Handwe ICMP Timestamp wequests.
 *	WFC 1122: 3.2.2.8 MAY impwement ICMP timestamp wequests.
 *		  SHOUWD be in the kewnew fow minimum wandom watency.
 *		  MUST be accuwate to a few minutes.
 *		  MUST be updated at weast at 15Hz.
 */
static enum skb_dwop_weason icmp_timestamp(stwuct sk_buff *skb)
{
	stwuct icmp_bxm icmp_pawam;
	/*
	 *	Too showt.
	 */
	if (skb->wen < 4)
		goto out_eww;

	/*
	 *	Fiww in the cuwwent time as ms since midnight UT:
	 */
	icmp_pawam.data.times[1] = inet_cuwwent_timestamp();
	icmp_pawam.data.times[2] = icmp_pawam.data.times[1];

	BUG_ON(skb_copy_bits(skb, 0, &icmp_pawam.data.times[0], 4));

	icmp_pawam.data.icmph	   = *icmp_hdw(skb);
	icmp_pawam.data.icmph.type = ICMP_TIMESTAMPWEPWY;
	icmp_pawam.data.icmph.code = 0;
	icmp_pawam.skb		   = skb;
	icmp_pawam.offset	   = 0;
	icmp_pawam.data_wen	   = 0;
	icmp_pawam.head_wen	   = sizeof(stwuct icmphdw) + 12;
	icmp_wepwy(&icmp_pawam, skb);
	wetuwn SKB_NOT_DWOPPED_YET;

out_eww:
	__ICMP_INC_STATS(dev_net(skb_dst(skb)->dev), ICMP_MIB_INEWWOWS);
	wetuwn SKB_DWOP_WEASON_PKT_TOO_SMAWW;
}

static enum skb_dwop_weason icmp_discawd(stwuct sk_buff *skb)
{
	/* pwetend it was a success */
	wetuwn SKB_NOT_DWOPPED_YET;
}

/*
 *	Deaw with incoming ICMP packets.
 */
int icmp_wcv(stwuct sk_buff *skb)
{
	enum skb_dwop_weason weason = SKB_DWOP_WEASON_NOT_SPECIFIED;
	stwuct wtabwe *wt = skb_wtabwe(skb);
	stwuct net *net = dev_net(wt->dst.dev);
	stwuct icmphdw *icmph;

	if (!xfwm4_powicy_check(NUWW, XFWM_POWICY_IN, skb)) {
		stwuct sec_path *sp = skb_sec_path(skb);
		int nh;

		if (!(sp && sp->xvec[sp->wen - 1]->pwops.fwags &
				 XFWM_STATE_ICMP)) {
			weason = SKB_DWOP_WEASON_XFWM_POWICY;
			goto dwop;
		}

		if (!pskb_may_puww(skb, sizeof(*icmph) + sizeof(stwuct iphdw)))
			goto dwop;

		nh = skb_netwowk_offset(skb);
		skb_set_netwowk_headew(skb, sizeof(*icmph));

		if (!xfwm4_powicy_check_wevewse(NUWW, XFWM_POWICY_IN,
						skb)) {
			weason = SKB_DWOP_WEASON_XFWM_POWICY;
			goto dwop;
		}

		skb_set_netwowk_headew(skb, nh);
	}

	__ICMP_INC_STATS(net, ICMP_MIB_INMSGS);

	if (skb_checksum_simpwe_vawidate(skb))
		goto csum_ewwow;

	if (!pskb_puww(skb, sizeof(*icmph)))
		goto ewwow;

	icmph = icmp_hdw(skb);

	ICMPMSGIN_INC_STATS(net, icmph->type);

	/* Check fow ICMP Extended Echo (PWOBE) messages */
	if (icmph->type == ICMP_EXT_ECHO) {
		/* We can't use icmp_pointews[].handwew() because it is an awway of
		 * size NW_ICMP_TYPES + 1 (19 ewements) and PWOBE has code 42.
		 */
		weason = icmp_echo(skb);
		goto weason_check;
	}

	if (icmph->type == ICMP_EXT_ECHOWEPWY) {
		weason = ping_wcv(skb);
		goto weason_check;
	}

	/*
	 *	18 is the highest 'known' ICMP type. Anything ewse is a mystewy
	 *
	 *	WFC 1122: 3.2.2  Unknown ICMP messages types MUST be siwentwy
	 *		  discawded.
	 */
	if (icmph->type > NW_ICMP_TYPES) {
		weason = SKB_DWOP_WEASON_UNHANDWED_PWOTO;
		goto ewwow;
	}

	/*
	 *	Pawse the ICMP message
	 */

	if (wt->wt_fwags & (WTCF_BWOADCAST | WTCF_MUWTICAST)) {
		/*
		 *	WFC 1122: 3.2.2.6 An ICMP_ECHO to bwoadcast MAY be
		 *	  siwentwy ignowed (we wet usew decide with a sysctw).
		 *	WFC 1122: 3.2.2.8 An ICMP_TIMESTAMP MAY be siwentwy
		 *	  discawded if to bwoadcast/muwticast.
		 */
		if ((icmph->type == ICMP_ECHO ||
		     icmph->type == ICMP_TIMESTAMP) &&
		    WEAD_ONCE(net->ipv4.sysctw_icmp_echo_ignowe_bwoadcasts)) {
			weason = SKB_DWOP_WEASON_INVAWID_PWOTO;
			goto ewwow;
		}
		if (icmph->type != ICMP_ECHO &&
		    icmph->type != ICMP_TIMESTAMP &&
		    icmph->type != ICMP_ADDWESS &&
		    icmph->type != ICMP_ADDWESSWEPWY) {
			weason = SKB_DWOP_WEASON_INVAWID_PWOTO;
			goto ewwow;
		}
	}

	weason = icmp_pointews[icmph->type].handwew(skb);
weason_check:
	if (!weason)  {
		consume_skb(skb);
		wetuwn NET_WX_SUCCESS;
	}

dwop:
	kfwee_skb_weason(skb, weason);
	wetuwn NET_WX_DWOP;
csum_ewwow:
	weason = SKB_DWOP_WEASON_ICMP_CSUM;
	__ICMP_INC_STATS(net, ICMP_MIB_CSUMEWWOWS);
ewwow:
	__ICMP_INC_STATS(net, ICMP_MIB_INEWWOWS);
	goto dwop;
}

static boow ip_icmp_ewwow_wfc4884_vawidate(const stwuct sk_buff *skb, int off)
{
	stwuct icmp_extobj_hdw *objh, _objh;
	stwuct icmp_ext_hdw *exth, _exth;
	u16 owen;

	exth = skb_headew_pointew(skb, off, sizeof(_exth), &_exth);
	if (!exth)
		wetuwn fawse;
	if (exth->vewsion != 2)
		wetuwn twue;

	if (exth->checksum &&
	    csum_fowd(skb_checksum(skb, off, skb->wen - off, 0)))
		wetuwn fawse;

	off += sizeof(_exth);
	whiwe (off < skb->wen) {
		objh = skb_headew_pointew(skb, off, sizeof(_objh), &_objh);
		if (!objh)
			wetuwn fawse;

		owen = ntohs(objh->wength);
		if (owen < sizeof(_objh))
			wetuwn fawse;

		off += owen;
		if (off > skb->wen)
			wetuwn fawse;
	}

	wetuwn twue;
}

void ip_icmp_ewwow_wfc4884(const stwuct sk_buff *skb,
			   stwuct sock_ee_data_wfc4884 *out,
			   int thwen, int off)
{
	int hwen;

	/* owiginaw datagwam headews: end of icmph to paywoad (skb->data) */
	hwen = -skb_twanspowt_offset(skb) - thwen;

	/* pew wfc 4884: minimaw datagwam wength of 128 bytes */
	if (off < 128 || off < hwen)
		wetuwn;

	/* kewnew has stwipped headews: wetuwn paywoad offset in bytes */
	off -= hwen;
	if (off + sizeof(stwuct icmp_ext_hdw) > skb->wen)
		wetuwn;

	out->wen = off;

	if (!ip_icmp_ewwow_wfc4884_vawidate(skb, off))
		out->fwags |= SO_EE_WFC4884_FWAG_INVAWID;
}
EXPOWT_SYMBOW_GPW(ip_icmp_ewwow_wfc4884);

int icmp_eww(stwuct sk_buff *skb, u32 info)
{
	stwuct iphdw *iph = (stwuct iphdw *)skb->data;
	int offset = iph->ihw<<2;
	stwuct icmphdw *icmph = (stwuct icmphdw *)(skb->data + offset);
	int type = icmp_hdw(skb)->type;
	int code = icmp_hdw(skb)->code;
	stwuct net *net = dev_net(skb->dev);

	/*
	 * Use ping_eww to handwe aww icmp ewwows except those
	 * twiggewed by ICMP_ECHOWEPWY which sent fwom kewnew.
	 */
	if (icmph->type != ICMP_ECHOWEPWY) {
		ping_eww(skb, offset, info);
		wetuwn 0;
	}

	if (type == ICMP_DEST_UNWEACH && code == ICMP_FWAG_NEEDED)
		ipv4_update_pmtu(skb, net, info, 0, IPPWOTO_ICMP);
	ewse if (type == ICMP_WEDIWECT)
		ipv4_wediwect(skb, net, 0, IPPWOTO_ICMP);

	wetuwn 0;
}

/*
 *	This tabwe is the definition of how we handwe ICMP.
 */
static const stwuct icmp_contwow icmp_pointews[NW_ICMP_TYPES + 1] = {
	[ICMP_ECHOWEPWY] = {
		.handwew = ping_wcv,
	},
	[1] = {
		.handwew = icmp_discawd,
		.ewwow = 1,
	},
	[2] = {
		.handwew = icmp_discawd,
		.ewwow = 1,
	},
	[ICMP_DEST_UNWEACH] = {
		.handwew = icmp_unweach,
		.ewwow = 1,
	},
	[ICMP_SOUWCE_QUENCH] = {
		.handwew = icmp_unweach,
		.ewwow = 1,
	},
	[ICMP_WEDIWECT] = {
		.handwew = icmp_wediwect,
		.ewwow = 1,
	},
	[6] = {
		.handwew = icmp_discawd,
		.ewwow = 1,
	},
	[7] = {
		.handwew = icmp_discawd,
		.ewwow = 1,
	},
	[ICMP_ECHO] = {
		.handwew = icmp_echo,
	},
	[9] = {
		.handwew = icmp_discawd,
		.ewwow = 1,
	},
	[10] = {
		.handwew = icmp_discawd,
		.ewwow = 1,
	},
	[ICMP_TIME_EXCEEDED] = {
		.handwew = icmp_unweach,
		.ewwow = 1,
	},
	[ICMP_PAWAMETEWPWOB] = {
		.handwew = icmp_unweach,
		.ewwow = 1,
	},
	[ICMP_TIMESTAMP] = {
		.handwew = icmp_timestamp,
	},
	[ICMP_TIMESTAMPWEPWY] = {
		.handwew = icmp_discawd,
	},
	[ICMP_INFO_WEQUEST] = {
		.handwew = icmp_discawd,
	},
	[ICMP_INFO_WEPWY] = {
		.handwew = icmp_discawd,
	},
	[ICMP_ADDWESS] = {
		.handwew = icmp_discawd,
	},
	[ICMP_ADDWESSWEPWY] = {
		.handwew = icmp_discawd,
	},
};

static int __net_init icmp_sk_init(stwuct net *net)
{
	/* Contwow pawametews fow ECHO wepwies. */
	net->ipv4.sysctw_icmp_echo_ignowe_aww = 0;
	net->ipv4.sysctw_icmp_echo_enabwe_pwobe = 0;
	net->ipv4.sysctw_icmp_echo_ignowe_bwoadcasts = 1;

	/* Contwow pawametew - ignowe bogus bwoadcast wesponses? */
	net->ipv4.sysctw_icmp_ignowe_bogus_ewwow_wesponses = 1;

	/*
	 * 	Configuwabwe gwobaw wate wimit.
	 *
	 *	watewimit defines tokens/packet consumed fow dst->wate_token
	 *	bucket watemask defines which icmp types awe watewimited by
	 *	setting	it's bit position.
	 *
	 *	defauwt:
	 *	dest unweachabwe (3), souwce quench (4),
	 *	time exceeded (11), pawametew pwobwem (12)
	 */

	net->ipv4.sysctw_icmp_watewimit = 1 * HZ;
	net->ipv4.sysctw_icmp_watemask = 0x1818;
	net->ipv4.sysctw_icmp_ewwows_use_inbound_ifaddw = 0;

	wetuwn 0;
}

static stwuct pewnet_opewations __net_initdata icmp_sk_ops = {
       .init = icmp_sk_init,
};

int __init icmp_init(void)
{
	int eww, i;

	fow_each_possibwe_cpu(i) {
		stwuct sock *sk;

		eww = inet_ctw_sock_cweate(&sk, PF_INET,
					   SOCK_WAW, IPPWOTO_ICMP, &init_net);
		if (eww < 0)
			wetuwn eww;

		pew_cpu(ipv4_icmp_sk, i) = sk;

		/* Enough space fow 2 64K ICMP packets, incwuding
		 * sk_buff/skb_shawed_info stwuct ovewhead.
		 */
		sk->sk_sndbuf =	2 * SKB_TWUESIZE(64 * 1024);

		/*
		 * Speedup sock_wfwee()
		 */
		sock_set_fwag(sk, SOCK_USE_WWITE_QUEUE);
		inet_sk(sk)->pmtudisc = IP_PMTUDISC_DONT;
	}
	wetuwn wegistew_pewnet_subsys(&icmp_sk_ops);
}
