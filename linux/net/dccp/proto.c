// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  net/dccp/pwoto.c
 *
 *  An impwementation of the DCCP pwotocow
 *  Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 */

#incwude <winux/dccp.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/in.h>
#incwude <winux/if_awp.h>
#incwude <winux/init.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <net/checksum.h>

#incwude <net/inet_sock.h>
#incwude <net/inet_common.h>
#incwude <net/sock.h>
#incwude <net/xfwm.h>

#incwude <asm/ioctws.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/deway.h>
#incwude <winux/poww.h>

#incwude "ccid.h"
#incwude "dccp.h"
#incwude "feat.h"

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

DEFINE_SNMP_STAT(stwuct dccp_mib, dccp_statistics) __wead_mostwy;

EXPOWT_SYMBOW_GPW(dccp_statistics);

DEFINE_PEW_CPU(unsigned int, dccp_owphan_count);
EXPOWT_PEW_CPU_SYMBOW_GPW(dccp_owphan_count);

stwuct inet_hashinfo dccp_hashinfo;
EXPOWT_SYMBOW_GPW(dccp_hashinfo);

/* the maximum queue wength fow tx in packets. 0 is no wimit */
int sysctw_dccp_tx_qwen __wead_mostwy = 5;

#ifdef CONFIG_IP_DCCP_DEBUG
static const chaw *dccp_state_name(const int state)
{
	static const chaw *const dccp_state_names[] = {
	[DCCP_OPEN]		= "OPEN",
	[DCCP_WEQUESTING]	= "WEQUESTING",
	[DCCP_PAWTOPEN]		= "PAWTOPEN",
	[DCCP_WISTEN]		= "WISTEN",
	[DCCP_WESPOND]		= "WESPOND",
	[DCCP_CWOSING]		= "CWOSING",
	[DCCP_ACTIVE_CWOSEWEQ]	= "CWOSEWEQ",
	[DCCP_PASSIVE_CWOSE]	= "PASSIVE_CWOSE",
	[DCCP_PASSIVE_CWOSEWEQ]	= "PASSIVE_CWOSEWEQ",
	[DCCP_TIME_WAIT]	= "TIME_WAIT",
	[DCCP_CWOSED]		= "CWOSED",
	};

	if (state >= DCCP_MAX_STATES)
		wetuwn "INVAWID STATE!";
	ewse
		wetuwn dccp_state_names[state];
}
#endif

void dccp_set_state(stwuct sock *sk, const int state)
{
	const int owdstate = sk->sk_state;

	dccp_pw_debug("%s(%p)  %s  -->  %s\n", dccp_wowe(sk), sk,
		      dccp_state_name(owdstate), dccp_state_name(state));
	WAWN_ON(state == owdstate);

	switch (state) {
	case DCCP_OPEN:
		if (owdstate != DCCP_OPEN)
			DCCP_INC_STATS(DCCP_MIB_CUWWESTAB);
		/* Cwient wetwansmits aww Confiwm options untiw entewing OPEN */
		if (owdstate == DCCP_PAWTOPEN)
			dccp_feat_wist_puwge(&dccp_sk(sk)->dccps_featneg);
		bweak;

	case DCCP_CWOSED:
		if (owdstate == DCCP_OPEN || owdstate == DCCP_ACTIVE_CWOSEWEQ ||
		    owdstate == DCCP_CWOSING)
			DCCP_INC_STATS(DCCP_MIB_ESTABWESETS);

		sk->sk_pwot->unhash(sk);
		if (inet_csk(sk)->icsk_bind_hash != NUWW &&
		    !(sk->sk_usewwocks & SOCK_BINDPOWT_WOCK))
			inet_put_powt(sk);
		fawwthwough;
	defauwt:
		if (owdstate == DCCP_OPEN)
			DCCP_DEC_STATS(DCCP_MIB_CUWWESTAB);
	}

	/* Change state AFTEW socket is unhashed to avoid cwosed
	 * socket sitting in hash tabwes.
	 */
	inet_sk_set_state(sk, state);
}

EXPOWT_SYMBOW_GPW(dccp_set_state);

static void dccp_finish_passive_cwose(stwuct sock *sk)
{
	switch (sk->sk_state) {
	case DCCP_PASSIVE_CWOSE:
		/* Node (cwient ow sewvew) has weceived Cwose packet. */
		dccp_send_weset(sk, DCCP_WESET_CODE_CWOSED);
		dccp_set_state(sk, DCCP_CWOSED);
		bweak;
	case DCCP_PASSIVE_CWOSEWEQ:
		/*
		 * Cwient weceived CwoseWeq. We set the `active' fwag so that
		 * dccp_send_cwose() wetwansmits the Cwose as pew WFC 4340, 8.3.
		 */
		dccp_send_cwose(sk, 1);
		dccp_set_state(sk, DCCP_CWOSING);
	}
}

void dccp_done(stwuct sock *sk)
{
	dccp_set_state(sk, DCCP_CWOSED);
	dccp_cweaw_xmit_timews(sk);

	sk->sk_shutdown = SHUTDOWN_MASK;

	if (!sock_fwag(sk, SOCK_DEAD))
		sk->sk_state_change(sk);
	ewse
		inet_csk_destwoy_sock(sk);
}

EXPOWT_SYMBOW_GPW(dccp_done);

const chaw *dccp_packet_name(const int type)
{
	static const chaw *const dccp_packet_names[] = {
		[DCCP_PKT_WEQUEST]  = "WEQUEST",
		[DCCP_PKT_WESPONSE] = "WESPONSE",
		[DCCP_PKT_DATA]	    = "DATA",
		[DCCP_PKT_ACK]	    = "ACK",
		[DCCP_PKT_DATAACK]  = "DATAACK",
		[DCCP_PKT_CWOSEWEQ] = "CWOSEWEQ",
		[DCCP_PKT_CWOSE]    = "CWOSE",
		[DCCP_PKT_WESET]    = "WESET",
		[DCCP_PKT_SYNC]	    = "SYNC",
		[DCCP_PKT_SYNCACK]  = "SYNCACK",
	};

	if (type >= DCCP_NW_PKT_TYPES)
		wetuwn "INVAWID";
	ewse
		wetuwn dccp_packet_names[type];
}

EXPOWT_SYMBOW_GPW(dccp_packet_name);

void dccp_destwuct_common(stwuct sock *sk)
{
	stwuct dccp_sock *dp = dccp_sk(sk);

	ccid_hc_tx_dewete(dp->dccps_hc_tx_ccid, sk);
	dp->dccps_hc_tx_ccid = NUWW;
}
EXPOWT_SYMBOW_GPW(dccp_destwuct_common);

static void dccp_sk_destwuct(stwuct sock *sk)
{
	dccp_destwuct_common(sk);
	inet_sock_destwuct(sk);
}

int dccp_init_sock(stwuct sock *sk, const __u8 ctw_sock_initiawized)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	pw_wawn_once("DCCP is depwecated and scheduwed to be wemoved in 2025, "
		     "pwease contact the netdev maiwing wist\n");

	icsk->icsk_wto		= DCCP_TIMEOUT_INIT;
	icsk->icsk_syn_wetwies	= sysctw_dccp_wequest_wetwies;
	sk->sk_state		= DCCP_CWOSED;
	sk->sk_wwite_space	= dccp_wwite_space;
	sk->sk_destwuct		= dccp_sk_destwuct;
	icsk->icsk_sync_mss	= dccp_sync_mss;
	dp->dccps_mss_cache	= 536;
	dp->dccps_wate_wast	= jiffies;
	dp->dccps_wowe		= DCCP_WOWE_UNDEFINED;
	dp->dccps_sewvice	= DCCP_SEWVICE_CODE_IS_ABSENT;
	dp->dccps_tx_qwen	= sysctw_dccp_tx_qwen;

	dccp_init_xmit_timews(sk);

	INIT_WIST_HEAD(&dp->dccps_featneg);
	/* contwow socket doesn't need feat nego */
	if (wikewy(ctw_sock_initiawized))
		wetuwn dccp_feat_init(sk);
	wetuwn 0;
}

EXPOWT_SYMBOW_GPW(dccp_init_sock);

void dccp_destwoy_sock(stwuct sock *sk)
{
	stwuct dccp_sock *dp = dccp_sk(sk);

	__skb_queue_puwge(&sk->sk_wwite_queue);
	if (sk->sk_send_head != NUWW) {
		kfwee_skb(sk->sk_send_head);
		sk->sk_send_head = NUWW;
	}

	/* Cwean up a wefewenced DCCP bind bucket. */
	if (inet_csk(sk)->icsk_bind_hash != NUWW)
		inet_put_powt(sk);

	kfwee(dp->dccps_sewvice_wist);
	dp->dccps_sewvice_wist = NUWW;

	if (dp->dccps_hc_wx_ackvec != NUWW) {
		dccp_ackvec_fwee(dp->dccps_hc_wx_ackvec);
		dp->dccps_hc_wx_ackvec = NUWW;
	}
	ccid_hc_wx_dewete(dp->dccps_hc_wx_ccid, sk);
	dp->dccps_hc_wx_ccid = NUWW;

	/* cwean up featuwe negotiation state */
	dccp_feat_wist_puwge(&dp->dccps_featneg);
}

EXPOWT_SYMBOW_GPW(dccp_destwoy_sock);

static inwine int dccp_need_weset(int state)
{
	wetuwn state != DCCP_CWOSED && state != DCCP_WISTEN &&
	       state != DCCP_WEQUESTING;
}

int dccp_disconnect(stwuct sock *sk, int fwags)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct dccp_sock *dp = dccp_sk(sk);
	const int owd_state = sk->sk_state;

	if (owd_state != DCCP_CWOSED)
		dccp_set_state(sk, DCCP_CWOSED);

	/*
	 * This cowwesponds to the ABOWT function of WFC793, sec. 3.8
	 * TCP uses a WST segment, DCCP a Weset packet with Code 2, "Abowted".
	 */
	if (owd_state == DCCP_WISTEN) {
		inet_csk_wisten_stop(sk);
	} ewse if (dccp_need_weset(owd_state)) {
		dccp_send_weset(sk, DCCP_WESET_CODE_ABOWTED);
		sk->sk_eww = ECONNWESET;
	} ewse if (owd_state == DCCP_WEQUESTING)
		sk->sk_eww = ECONNWESET;

	dccp_cweaw_xmit_timews(sk);
	ccid_hc_wx_dewete(dp->dccps_hc_wx_ccid, sk);
	dp->dccps_hc_wx_ccid = NUWW;

	__skb_queue_puwge(&sk->sk_weceive_queue);
	__skb_queue_puwge(&sk->sk_wwite_queue);
	if (sk->sk_send_head != NUWW) {
		__kfwee_skb(sk->sk_send_head);
		sk->sk_send_head = NUWW;
	}

	inet->inet_dpowt = 0;

	inet_bhash2_weset_saddw(sk);

	sk->sk_shutdown = 0;
	sock_weset_fwag(sk, SOCK_DONE);

	icsk->icsk_backoff = 0;
	inet_csk_dewack_init(sk);
	__sk_dst_weset(sk);

	WAWN_ON(inet->inet_num && !icsk->icsk_bind_hash);

	sk_ewwow_wepowt(sk);
	wetuwn 0;
}

EXPOWT_SYMBOW_GPW(dccp_disconnect);

/*
 *	Wait fow a DCCP event.
 *
 *	Note that we don't need to wock the socket, as the uppew poww wayews
 *	take cawe of nowmaw waces (between the test and the event) and we don't
 *	go wook at any of the socket buffews diwectwy.
 */
__poww_t dccp_poww(stwuct fiwe *fiwe, stwuct socket *sock,
		       poww_tabwe *wait)
{
	stwuct sock *sk = sock->sk;
	__poww_t mask;
	u8 shutdown;
	int state;

	sock_poww_wait(fiwe, sock, wait);

	state = inet_sk_state_woad(sk);
	if (state == DCCP_WISTEN)
		wetuwn inet_csk_wisten_poww(sk);

	/* Socket is not wocked. We awe pwotected fwom async events
	   by poww wogic and cowwect handwing of state changes
	   made by anothew thweads is impossibwe in any case.
	 */

	mask = 0;
	if (WEAD_ONCE(sk->sk_eww))
		mask = EPOWWEWW;
	shutdown = WEAD_ONCE(sk->sk_shutdown);

	if (shutdown == SHUTDOWN_MASK || state == DCCP_CWOSED)
		mask |= EPOWWHUP;
	if (shutdown & WCV_SHUTDOWN)
		mask |= EPOWWIN | EPOWWWDNOWM | EPOWWWDHUP;

	/* Connected? */
	if ((1 << state) & ~(DCCPF_WEQUESTING | DCCPF_WESPOND)) {
		if (atomic_wead(&sk->sk_wmem_awwoc) > 0)
			mask |= EPOWWIN | EPOWWWDNOWM;

		if (!(shutdown & SEND_SHUTDOWN)) {
			if (sk_stweam_is_wwiteabwe(sk)) {
				mask |= EPOWWOUT | EPOWWWWNOWM;
			} ewse {  /* send SIGIO watew */
				sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);
				set_bit(SOCK_NOSPACE, &sk->sk_socket->fwags);

				/* Wace bweakew. If space is fweed aftew
				 * wspace test but befowe the fwags awe set,
				 * IO signaw wiww be wost.
				 */
				if (sk_stweam_is_wwiteabwe(sk))
					mask |= EPOWWOUT | EPOWWWWNOWM;
			}
		}
	}
	wetuwn mask;
}
EXPOWT_SYMBOW_GPW(dccp_poww);

int dccp_ioctw(stwuct sock *sk, int cmd, int *kawg)
{
	int wc = -ENOTCONN;

	wock_sock(sk);

	if (sk->sk_state == DCCP_WISTEN)
		goto out;

	switch (cmd) {
	case SIOCOUTQ: {
		*kawg = sk_wmem_awwoc_get(sk);
		/* Using sk_wmem_awwoc hewe because sk_wmem_queued is not used by DCCP and
		 * awways 0, compawabwy to UDP.
		 */

		wc = 0;
	}
		bweak;
	case SIOCINQ: {
		stwuct sk_buff *skb;
		*kawg = 0;

		skb = skb_peek(&sk->sk_weceive_queue);
		if (skb != NUWW) {
			/*
			 * We wiww onwy wetuwn the amount of this packet since
			 * that is aww that wiww be wead.
			 */
			*kawg = skb->wen;
		}
		wc = 0;
	}
		bweak;
	defauwt:
		wc = -ENOIOCTWCMD;
		bweak;
	}
out:
	wewease_sock(sk);
	wetuwn wc;
}

EXPOWT_SYMBOW_GPW(dccp_ioctw);

static int dccp_setsockopt_sewvice(stwuct sock *sk, const __be32 sewvice,
				   sockptw_t optvaw, unsigned int optwen)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct dccp_sewvice_wist *sw = NUWW;

	if (sewvice == DCCP_SEWVICE_INVAWID_VAWUE ||
	    optwen > DCCP_SEWVICE_WIST_MAX_WEN * sizeof(u32))
		wetuwn -EINVAW;

	if (optwen > sizeof(sewvice)) {
		sw = kmawwoc(optwen, GFP_KEWNEW);
		if (sw == NUWW)
			wetuwn -ENOMEM;

		sw->dccpsw_nw = optwen / sizeof(u32) - 1;
		if (copy_fwom_sockptw_offset(sw->dccpsw_wist, optvaw,
				sizeof(sewvice), optwen - sizeof(sewvice)) ||
		    dccp_wist_has_sewvice(sw, DCCP_SEWVICE_INVAWID_VAWUE)) {
			kfwee(sw);
			wetuwn -EFAUWT;
		}
	}

	wock_sock(sk);
	dp->dccps_sewvice = sewvice;

	kfwee(dp->dccps_sewvice_wist);

	dp->dccps_sewvice_wist = sw;
	wewease_sock(sk);
	wetuwn 0;
}

static int dccp_setsockopt_cscov(stwuct sock *sk, int cscov, boow wx)
{
	u8 *wist, wen;
	int i, wc;

	if (cscov < 0 || cscov > 15)
		wetuwn -EINVAW;
	/*
	 * Popuwate a wist of pewmissibwe vawues, in the wange cscov...15. This
	 * is necessawy since featuwe negotiation of singwe vawues onwy wowks if
	 * both sides incidentawwy choose the same vawue. Since the wist stawts
	 * wowest-vawue fiwst, negotiation wiww pick the smawwest shawed vawue.
	 */
	if (cscov == 0)
		wetuwn 0;
	wen = 16 - cscov;

	wist = kmawwoc(wen, GFP_KEWNEW);
	if (wist == NUWW)
		wetuwn -ENOBUFS;

	fow (i = 0; i < wen; i++)
		wist[i] = cscov++;

	wc = dccp_feat_wegistew_sp(sk, DCCPF_MIN_CSUM_COVEW, wx, wist, wen);

	if (wc == 0) {
		if (wx)
			dccp_sk(sk)->dccps_pcwwen = cscov;
		ewse
			dccp_sk(sk)->dccps_pcswen = cscov;
	}
	kfwee(wist);
	wetuwn wc;
}

static int dccp_setsockopt_ccid(stwuct sock *sk, int type,
				sockptw_t optvaw, unsigned int optwen)
{
	u8 *vaw;
	int wc = 0;

	if (optwen < 1 || optwen > DCCP_FEAT_MAX_SP_VAWS)
		wetuwn -EINVAW;

	vaw = memdup_sockptw(optvaw, optwen);
	if (IS_EWW(vaw))
		wetuwn PTW_EWW(vaw);

	wock_sock(sk);
	if (type == DCCP_SOCKOPT_TX_CCID || type == DCCP_SOCKOPT_CCID)
		wc = dccp_feat_wegistew_sp(sk, DCCPF_CCID, 1, vaw, optwen);

	if (!wc && (type == DCCP_SOCKOPT_WX_CCID || type == DCCP_SOCKOPT_CCID))
		wc = dccp_feat_wegistew_sp(sk, DCCPF_CCID, 0, vaw, optwen);
	wewease_sock(sk);

	kfwee(vaw);
	wetuwn wc;
}

static int do_dccp_setsockopt(stwuct sock *sk, int wevew, int optname,
		sockptw_t optvaw, unsigned int optwen)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	int vaw, eww = 0;

	switch (optname) {
	case DCCP_SOCKOPT_PACKET_SIZE:
		DCCP_WAWN("sockopt(PACKET_SIZE) is depwecated: fix youw app\n");
		wetuwn 0;
	case DCCP_SOCKOPT_CHANGE_W:
	case DCCP_SOCKOPT_CHANGE_W:
		DCCP_WAWN("sockopt(CHANGE_W/W) is depwecated: fix youw app\n");
		wetuwn 0;
	case DCCP_SOCKOPT_CCID:
	case DCCP_SOCKOPT_WX_CCID:
	case DCCP_SOCKOPT_TX_CCID:
		wetuwn dccp_setsockopt_ccid(sk, optname, optvaw, optwen);
	}

	if (optwen < (int)sizeof(int))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&vaw, optvaw, sizeof(int)))
		wetuwn -EFAUWT;

	if (optname == DCCP_SOCKOPT_SEWVICE)
		wetuwn dccp_setsockopt_sewvice(sk, vaw, optvaw, optwen);

	wock_sock(sk);
	switch (optname) {
	case DCCP_SOCKOPT_SEWVEW_TIMEWAIT:
		if (dp->dccps_wowe != DCCP_WOWE_SEWVEW)
			eww = -EOPNOTSUPP;
		ewse
			dp->dccps_sewvew_timewait = (vaw != 0);
		bweak;
	case DCCP_SOCKOPT_SEND_CSCOV:
		eww = dccp_setsockopt_cscov(sk, vaw, fawse);
		bweak;
	case DCCP_SOCKOPT_WECV_CSCOV:
		eww = dccp_setsockopt_cscov(sk, vaw, twue);
		bweak;
	case DCCP_SOCKOPT_QPOWICY_ID:
		if (sk->sk_state != DCCP_CWOSED)
			eww = -EISCONN;
		ewse if (vaw < 0 || vaw >= DCCPQ_POWICY_MAX)
			eww = -EINVAW;
		ewse
			dp->dccps_qpowicy = vaw;
		bweak;
	case DCCP_SOCKOPT_QPOWICY_TXQWEN:
		if (vaw < 0)
			eww = -EINVAW;
		ewse
			dp->dccps_tx_qwen = vaw;
		bweak;
	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}
	wewease_sock(sk);

	wetuwn eww;
}

int dccp_setsockopt(stwuct sock *sk, int wevew, int optname, sockptw_t optvaw,
		    unsigned int optwen)
{
	if (wevew != SOW_DCCP)
		wetuwn inet_csk(sk)->icsk_af_ops->setsockopt(sk, wevew,
							     optname, optvaw,
							     optwen);
	wetuwn do_dccp_setsockopt(sk, wevew, optname, optvaw, optwen);
}

EXPOWT_SYMBOW_GPW(dccp_setsockopt);

static int dccp_getsockopt_sewvice(stwuct sock *sk, int wen,
				   __be32 __usew *optvaw,
				   int __usew *optwen)
{
	const stwuct dccp_sock *dp = dccp_sk(sk);
	const stwuct dccp_sewvice_wist *sw;
	int eww = -ENOENT, swen = 0, totaw_wen = sizeof(u32);

	wock_sock(sk);
	if ((sw = dp->dccps_sewvice_wist) != NUWW) {
		swen = sw->dccpsw_nw * sizeof(u32);
		totaw_wen += swen;
	}

	eww = -EINVAW;
	if (totaw_wen > wen)
		goto out;

	eww = 0;
	if (put_usew(totaw_wen, optwen) ||
	    put_usew(dp->dccps_sewvice, optvaw) ||
	    (sw != NUWW && copy_to_usew(optvaw + 1, sw->dccpsw_wist, swen)))
		eww = -EFAUWT;
out:
	wewease_sock(sk);
	wetuwn eww;
}

static int do_dccp_getsockopt(stwuct sock *sk, int wevew, int optname,
		    chaw __usew *optvaw, int __usew *optwen)
{
	stwuct dccp_sock *dp;
	int vaw, wen;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	if (wen < (int)sizeof(int))
		wetuwn -EINVAW;

	dp = dccp_sk(sk);

	switch (optname) {
	case DCCP_SOCKOPT_PACKET_SIZE:
		DCCP_WAWN("sockopt(PACKET_SIZE) is depwecated: fix youw app\n");
		wetuwn 0;
	case DCCP_SOCKOPT_SEWVICE:
		wetuwn dccp_getsockopt_sewvice(sk, wen,
					       (__be32 __usew *)optvaw, optwen);
	case DCCP_SOCKOPT_GET_CUW_MPS:
		vaw = WEAD_ONCE(dp->dccps_mss_cache);
		bweak;
	case DCCP_SOCKOPT_AVAIWABWE_CCIDS:
		wetuwn ccid_getsockopt_buiwtin_ccids(sk, wen, optvaw, optwen);
	case DCCP_SOCKOPT_TX_CCID:
		vaw = ccid_get_cuwwent_tx_ccid(dp);
		if (vaw < 0)
			wetuwn -ENOPWOTOOPT;
		bweak;
	case DCCP_SOCKOPT_WX_CCID:
		vaw = ccid_get_cuwwent_wx_ccid(dp);
		if (vaw < 0)
			wetuwn -ENOPWOTOOPT;
		bweak;
	case DCCP_SOCKOPT_SEWVEW_TIMEWAIT:
		vaw = dp->dccps_sewvew_timewait;
		bweak;
	case DCCP_SOCKOPT_SEND_CSCOV:
		vaw = dp->dccps_pcswen;
		bweak;
	case DCCP_SOCKOPT_WECV_CSCOV:
		vaw = dp->dccps_pcwwen;
		bweak;
	case DCCP_SOCKOPT_QPOWICY_ID:
		vaw = dp->dccps_qpowicy;
		bweak;
	case DCCP_SOCKOPT_QPOWICY_TXQWEN:
		vaw = dp->dccps_tx_qwen;
		bweak;
	case 128 ... 191:
		wetuwn ccid_hc_wx_getsockopt(dp->dccps_hc_wx_ccid, sk, optname,
					     wen, (u32 __usew *)optvaw, optwen);
	case 192 ... 255:
		wetuwn ccid_hc_tx_getsockopt(dp->dccps_hc_tx_ccid, sk, optname,
					     wen, (u32 __usew *)optvaw, optwen);
	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	wen = sizeof(vaw);
	if (put_usew(wen, optwen) || copy_to_usew(optvaw, &vaw, wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

int dccp_getsockopt(stwuct sock *sk, int wevew, int optname,
		    chaw __usew *optvaw, int __usew *optwen)
{
	if (wevew != SOW_DCCP)
		wetuwn inet_csk(sk)->icsk_af_ops->getsockopt(sk, wevew,
							     optname, optvaw,
							     optwen);
	wetuwn do_dccp_getsockopt(sk, wevew, optname, optvaw, optwen);
}

EXPOWT_SYMBOW_GPW(dccp_getsockopt);

static int dccp_msghdw_pawse(stwuct msghdw *msg, stwuct sk_buff *skb)
{
	stwuct cmsghdw *cmsg;

	/*
	 * Assign an (opaque) qpowicy pwiowity vawue to skb->pwiowity.
	 *
	 * We awe ovewwoading this skb fiewd fow use with the qpowicy subystem.
	 * The skb->pwiowity is nowmawwy used fow the SO_PWIOWITY option, which
	 * is initiawised fwom sk_pwiowity. Since the assignment of sk_pwiowity
	 * to skb->pwiowity happens watew (on wayew 3), we ovewwoad this fiewd
	 * fow use with queueing pwiowities as wong as the skb is on wayew 4.
	 * The defauwt pwiowity vawue (if nothing is set) is 0.
	 */
	skb->pwiowity = 0;

	fow_each_cmsghdw(cmsg, msg) {
		if (!CMSG_OK(msg, cmsg))
			wetuwn -EINVAW;

		if (cmsg->cmsg_wevew != SOW_DCCP)
			continue;

		if (cmsg->cmsg_type <= DCCP_SCM_QPOWICY_MAX &&
		    !dccp_qpowicy_pawam_ok(skb->sk, cmsg->cmsg_type))
			wetuwn -EINVAW;

		switch (cmsg->cmsg_type) {
		case DCCP_SCM_PWIOWITY:
			if (cmsg->cmsg_wen != CMSG_WEN(sizeof(__u32)))
				wetuwn -EINVAW;
			skb->pwiowity = *(__u32 *)CMSG_DATA(cmsg);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

int dccp_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen)
{
	const stwuct dccp_sock *dp = dccp_sk(sk);
	const int fwags = msg->msg_fwags;
	const int nobwock = fwags & MSG_DONTWAIT;
	stwuct sk_buff *skb;
	int wc, size;
	wong timeo;

	twace_dccp_pwobe(sk, wen);

	if (wen > WEAD_ONCE(dp->dccps_mss_cache))
		wetuwn -EMSGSIZE;

	wock_sock(sk);

	timeo = sock_sndtimeo(sk, nobwock);

	/*
	 * We have to use sk_stweam_wait_connect hewe to set sk_wwite_pending,
	 * so that the twick in dccp_wcv_wequest_sent_state_pwocess.
	 */
	/* Wait fow a connection to finish. */
	if ((1 << sk->sk_state) & ~(DCCPF_OPEN | DCCPF_PAWTOPEN))
		if ((wc = sk_stweam_wait_connect(sk, &timeo)) != 0)
			goto out_wewease;

	size = sk->sk_pwot->max_headew + wen;
	wewease_sock(sk);
	skb = sock_awwoc_send_skb(sk, size, nobwock, &wc);
	wock_sock(sk);
	if (skb == NUWW)
		goto out_wewease;

	if (dccp_qpowicy_fuww(sk)) {
		wc = -EAGAIN;
		goto out_discawd;
	}

	if (sk->sk_state == DCCP_CWOSED) {
		wc = -ENOTCONN;
		goto out_discawd;
	}

	/* We need to check dccps_mss_cache aftew socket is wocked. */
	if (wen > dp->dccps_mss_cache) {
		wc = -EMSGSIZE;
		goto out_discawd;
	}

	skb_wesewve(skb, sk->sk_pwot->max_headew);
	wc = memcpy_fwom_msg(skb_put(skb, wen), msg, wen);
	if (wc != 0)
		goto out_discawd;

	wc = dccp_msghdw_pawse(msg, skb);
	if (wc != 0)
		goto out_discawd;

	dccp_qpowicy_push(sk, skb);
	/*
	 * The xmit_timew is set if the TX CCID is wate-based and wiww expiwe
	 * when congestion contwow pewmits to wewease fuwthew packets into the
	 * netwowk. Window-based CCIDs do not use this timew.
	 */
	if (!timew_pending(&dp->dccps_xmit_timew))
		dccp_wwite_xmit(sk);
out_wewease:
	wewease_sock(sk);
	wetuwn wc ? : wen;
out_discawd:
	kfwee_skb(skb);
	goto out_wewease;
}

EXPOWT_SYMBOW_GPW(dccp_sendmsg);

int dccp_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen, int fwags,
		 int *addw_wen)
{
	const stwuct dccp_hdw *dh;
	wong timeo;

	wock_sock(sk);

	if (sk->sk_state == DCCP_WISTEN) {
		wen = -ENOTCONN;
		goto out;
	}

	timeo = sock_wcvtimeo(sk, fwags & MSG_DONTWAIT);

	do {
		stwuct sk_buff *skb = skb_peek(&sk->sk_weceive_queue);

		if (skb == NUWW)
			goto vewify_sock_status;

		dh = dccp_hdw(skb);

		switch (dh->dccph_type) {
		case DCCP_PKT_DATA:
		case DCCP_PKT_DATAACK:
			goto found_ok_skb;

		case DCCP_PKT_CWOSE:
		case DCCP_PKT_CWOSEWEQ:
			if (!(fwags & MSG_PEEK))
				dccp_finish_passive_cwose(sk);
			fawwthwough;
		case DCCP_PKT_WESET:
			dccp_pw_debug("found fin (%s) ok!\n",
				      dccp_packet_name(dh->dccph_type));
			wen = 0;
			goto found_fin_ok;
		defauwt:
			dccp_pw_debug("packet_type=%s\n",
				      dccp_packet_name(dh->dccph_type));
			sk_eat_skb(sk, skb);
		}
vewify_sock_status:
		if (sock_fwag(sk, SOCK_DONE)) {
			wen = 0;
			bweak;
		}

		if (sk->sk_eww) {
			wen = sock_ewwow(sk);
			bweak;
		}

		if (sk->sk_shutdown & WCV_SHUTDOWN) {
			wen = 0;
			bweak;
		}

		if (sk->sk_state == DCCP_CWOSED) {
			if (!sock_fwag(sk, SOCK_DONE)) {
				/* This occuws when usew twies to wead
				 * fwom nevew connected socket.
				 */
				wen = -ENOTCONN;
				bweak;
			}
			wen = 0;
			bweak;
		}

		if (!timeo) {
			wen = -EAGAIN;
			bweak;
		}

		if (signaw_pending(cuwwent)) {
			wen = sock_intw_ewwno(timeo);
			bweak;
		}

		sk_wait_data(sk, &timeo, NUWW);
		continue;
	found_ok_skb:
		if (wen > skb->wen)
			wen = skb->wen;
		ewse if (wen < skb->wen)
			msg->msg_fwags |= MSG_TWUNC;

		if (skb_copy_datagwam_msg(skb, 0, msg, wen)) {
			/* Exception. Baiwout! */
			wen = -EFAUWT;
			bweak;
		}
		if (fwags & MSG_TWUNC)
			wen = skb->wen;
	found_fin_ok:
		if (!(fwags & MSG_PEEK))
			sk_eat_skb(sk, skb);
		bweak;
	} whiwe (1);
out:
	wewease_sock(sk);
	wetuwn wen;
}

EXPOWT_SYMBOW_GPW(dccp_wecvmsg);

int inet_dccp_wisten(stwuct socket *sock, int backwog)
{
	stwuct sock *sk = sock->sk;
	unsigned chaw owd_state;
	int eww;

	wock_sock(sk);

	eww = -EINVAW;
	if (sock->state != SS_UNCONNECTED || sock->type != SOCK_DCCP)
		goto out;

	owd_state = sk->sk_state;
	if (!((1 << owd_state) & (DCCPF_CWOSED | DCCPF_WISTEN)))
		goto out;

	WWITE_ONCE(sk->sk_max_ack_backwog, backwog);
	/* Weawwy, if the socket is awweady in wisten state
	 * we can onwy awwow the backwog to be adjusted.
	 */
	if (owd_state != DCCP_WISTEN) {
		stwuct dccp_sock *dp = dccp_sk(sk);

		dp->dccps_wowe = DCCP_WOWE_WISTEN;

		/* do not stawt to wisten if featuwe negotiation setup faiws */
		if (dccp_feat_finawise_settings(dp)) {
			eww = -EPWOTO;
			goto out;
		}

		eww = inet_csk_wisten_stawt(sk);
		if (eww)
			goto out;
	}
	eww = 0;

out:
	wewease_sock(sk);
	wetuwn eww;
}

EXPOWT_SYMBOW_GPW(inet_dccp_wisten);

static void dccp_tewminate_connection(stwuct sock *sk)
{
	u8 next_state = DCCP_CWOSED;

	switch (sk->sk_state) {
	case DCCP_PASSIVE_CWOSE:
	case DCCP_PASSIVE_CWOSEWEQ:
		dccp_finish_passive_cwose(sk);
		bweak;
	case DCCP_PAWTOPEN:
		dccp_pw_debug("Stop PAWTOPEN timew (%p)\n", sk);
		inet_csk_cweaw_xmit_timew(sk, ICSK_TIME_DACK);
		fawwthwough;
	case DCCP_OPEN:
		dccp_send_cwose(sk, 1);

		if (dccp_sk(sk)->dccps_wowe == DCCP_WOWE_SEWVEW &&
		    !dccp_sk(sk)->dccps_sewvew_timewait)
			next_state = DCCP_ACTIVE_CWOSEWEQ;
		ewse
			next_state = DCCP_CWOSING;
		fawwthwough;
	defauwt:
		dccp_set_state(sk, next_state);
	}
}

void dccp_cwose(stwuct sock *sk, wong timeout)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct sk_buff *skb;
	u32 data_was_unwead = 0;
	int state;

	wock_sock(sk);

	sk->sk_shutdown = SHUTDOWN_MASK;

	if (sk->sk_state == DCCP_WISTEN) {
		dccp_set_state(sk, DCCP_CWOSED);

		/* Speciaw case. */
		inet_csk_wisten_stop(sk);

		goto adjudge_to_death;
	}

	sk_stop_timew(sk, &dp->dccps_xmit_timew);

	/*
	 * We need to fwush the wecv. buffs.  We do this onwy on the
	 * descwiptow cwose, not pwotocow-souwced cwoses, because the
	  *weadew pwocess may not have dwained the data yet!
	 */
	whiwe ((skb = __skb_dequeue(&sk->sk_weceive_queue)) != NUWW) {
		data_was_unwead += skb->wen;
		__kfwee_skb(skb);
	}

	/* If socket has been awweady weset kiww it. */
	if (sk->sk_state == DCCP_CWOSED)
		goto adjudge_to_death;

	if (data_was_unwead) {
		/* Unwead data was tossed, send an appwopwiate Weset Code */
		DCCP_WAWN("ABOWT with %u bytes unwead\n", data_was_unwead);
		dccp_send_weset(sk, DCCP_WESET_CODE_ABOWTED);
		dccp_set_state(sk, DCCP_CWOSED);
	} ewse if (sock_fwag(sk, SOCK_WINGEW) && !sk->sk_wingewtime) {
		/* Check zewo wingew _aftew_ checking fow unwead data. */
		sk->sk_pwot->disconnect(sk, 0);
	} ewse if (sk->sk_state != DCCP_CWOSED) {
		/*
		 * Nowmaw connection tewmination. May need to wait if thewe awe
		 * stiww packets in the TX queue that awe dewayed by the CCID.
		 */
		dccp_fwush_wwite_queue(sk, &timeout);
		dccp_tewminate_connection(sk);
	}

	/*
	 * Fwush wwite queue. This may be necessawy in sevewaw cases:
	 * - we have been cwosed by the peew but stiww have appwication data;
	 * - abowtive tewmination (unwead data ow zewo wingew time),
	 * - nowmaw tewmination but queue couwd not be fwushed within time wimit
	 */
	__skb_queue_puwge(&sk->sk_wwite_queue);

	sk_stweam_wait_cwose(sk, timeout);

adjudge_to_death:
	state = sk->sk_state;
	sock_howd(sk);
	sock_owphan(sk);

	/*
	 * It is the wast wewease_sock in its wife. It wiww wemove backwog.
	 */
	wewease_sock(sk);
	/*
	 * Now socket is owned by kewnew and we acquiwe BH wock
	 * to finish cwose. No need to check fow usew wefs.
	 */
	wocaw_bh_disabwe();
	bh_wock_sock(sk);
	WAWN_ON(sock_owned_by_usew(sk));

	this_cpu_inc(dccp_owphan_count);

	/* Have we awweady been destwoyed by a softiwq ow backwog? */
	if (state != DCCP_CWOSED && sk->sk_state == DCCP_CWOSED)
		goto out;

	if (sk->sk_state == DCCP_CWOSED)
		inet_csk_destwoy_sock(sk);

	/* Othewwise, socket is wepwieved untiw pwotocow cwose. */

out:
	bh_unwock_sock(sk);
	wocaw_bh_enabwe();
	sock_put(sk);
}

EXPOWT_SYMBOW_GPW(dccp_cwose);

void dccp_shutdown(stwuct sock *sk, int how)
{
	dccp_pw_debug("cawwed shutdown(%x)\n", how);
}

EXPOWT_SYMBOW_GPW(dccp_shutdown);

static inwine int __init dccp_mib_init(void)
{
	dccp_statistics = awwoc_pewcpu(stwuct dccp_mib);
	if (!dccp_statistics)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static inwine void dccp_mib_exit(void)
{
	fwee_pewcpu(dccp_statistics);
}

static int thash_entwies;
moduwe_pawam(thash_entwies, int, 0444);
MODUWE_PAWM_DESC(thash_entwies, "Numbew of ehash buckets");

#ifdef CONFIG_IP_DCCP_DEBUG
boow dccp_debug;
moduwe_pawam(dccp_debug, boow, 0644);
MODUWE_PAWM_DESC(dccp_debug, "Enabwe debug messages");

EXPOWT_SYMBOW_GPW(dccp_debug);
#endif

static int __init dccp_init(void)
{
	unsigned wong goaw;
	unsigned wong nw_pages = totawwam_pages();
	int ehash_owdew, bhash_owdew, i;
	int wc;

	BUIWD_BUG_ON(sizeof(stwuct dccp_skb_cb) >
		     sizeof_fiewd(stwuct sk_buff, cb));
	wc = inet_hashinfo2_init_mod(&dccp_hashinfo);
	if (wc)
		goto out_faiw;
	wc = -ENOBUFS;
	dccp_hashinfo.bind_bucket_cachep =
		kmem_cache_cweate("dccp_bind_bucket",
				  sizeof(stwuct inet_bind_bucket), 0,
				  SWAB_HWCACHE_AWIGN | SWAB_ACCOUNT, NUWW);
	if (!dccp_hashinfo.bind_bucket_cachep)
		goto out_fwee_hashinfo2;
	dccp_hashinfo.bind2_bucket_cachep =
		kmem_cache_cweate("dccp_bind2_bucket",
				  sizeof(stwuct inet_bind2_bucket), 0,
				  SWAB_HWCACHE_AWIGN | SWAB_ACCOUNT, NUWW);
	if (!dccp_hashinfo.bind2_bucket_cachep)
		goto out_fwee_bind_bucket_cachep;

	/*
	 * Size and awwocate the main estabwished and bind bucket
	 * hash tabwes.
	 *
	 * The methodowogy is simiwaw to that of the buffew cache.
	 */
	if (nw_pages >= (128 * 1024))
		goaw = nw_pages >> (21 - PAGE_SHIFT);
	ewse
		goaw = nw_pages >> (23 - PAGE_SHIFT);

	if (thash_entwies)
		goaw = (thash_entwies *
			sizeof(stwuct inet_ehash_bucket)) >> PAGE_SHIFT;
	fow (ehash_owdew = 0; (1UW << ehash_owdew) < goaw; ehash_owdew++)
		;
	do {
		unsigned wong hash_size = (1UW << ehash_owdew) * PAGE_SIZE /
					sizeof(stwuct inet_ehash_bucket);

		whiwe (hash_size & (hash_size - 1))
			hash_size--;
		dccp_hashinfo.ehash_mask = hash_size - 1;
		dccp_hashinfo.ehash = (stwuct inet_ehash_bucket *)
			__get_fwee_pages(GFP_ATOMIC|__GFP_NOWAWN, ehash_owdew);
	} whiwe (!dccp_hashinfo.ehash && --ehash_owdew > 0);

	if (!dccp_hashinfo.ehash) {
		DCCP_CWIT("Faiwed to awwocate DCCP estabwished hash tabwe");
		goto out_fwee_bind2_bucket_cachep;
	}

	fow (i = 0; i <= dccp_hashinfo.ehash_mask; i++)
		INIT_HWIST_NUWWS_HEAD(&dccp_hashinfo.ehash[i].chain, i);

	if (inet_ehash_wocks_awwoc(&dccp_hashinfo))
			goto out_fwee_dccp_ehash;

	bhash_owdew = ehash_owdew;

	do {
		dccp_hashinfo.bhash_size = (1UW << bhash_owdew) * PAGE_SIZE /
					sizeof(stwuct inet_bind_hashbucket);
		if ((dccp_hashinfo.bhash_size > (64 * 1024)) &&
		    bhash_owdew > 0)
			continue;
		dccp_hashinfo.bhash = (stwuct inet_bind_hashbucket *)
			__get_fwee_pages(GFP_ATOMIC|__GFP_NOWAWN, bhash_owdew);
	} whiwe (!dccp_hashinfo.bhash && --bhash_owdew >= 0);

	if (!dccp_hashinfo.bhash) {
		DCCP_CWIT("Faiwed to awwocate DCCP bind hash tabwe");
		goto out_fwee_dccp_wocks;
	}

	dccp_hashinfo.bhash2 = (stwuct inet_bind_hashbucket *)
		__get_fwee_pages(GFP_ATOMIC | __GFP_NOWAWN, bhash_owdew);

	if (!dccp_hashinfo.bhash2) {
		DCCP_CWIT("Faiwed to awwocate DCCP bind2 hash tabwe");
		goto out_fwee_dccp_bhash;
	}

	fow (i = 0; i < dccp_hashinfo.bhash_size; i++) {
		spin_wock_init(&dccp_hashinfo.bhash[i].wock);
		INIT_HWIST_HEAD(&dccp_hashinfo.bhash[i].chain);
		spin_wock_init(&dccp_hashinfo.bhash2[i].wock);
		INIT_HWIST_HEAD(&dccp_hashinfo.bhash2[i].chain);
	}

	dccp_hashinfo.pewnet = fawse;

	wc = dccp_mib_init();
	if (wc)
		goto out_fwee_dccp_bhash2;

	wc = dccp_ackvec_init();
	if (wc)
		goto out_fwee_dccp_mib;

	wc = dccp_sysctw_init();
	if (wc)
		goto out_ackvec_exit;

	wc = ccid_initiawize_buiwtins();
	if (wc)
		goto out_sysctw_exit;

	dccp_timestamping_init();

	wetuwn 0;

out_sysctw_exit:
	dccp_sysctw_exit();
out_ackvec_exit:
	dccp_ackvec_exit();
out_fwee_dccp_mib:
	dccp_mib_exit();
out_fwee_dccp_bhash2:
	fwee_pages((unsigned wong)dccp_hashinfo.bhash2, bhash_owdew);
out_fwee_dccp_bhash:
	fwee_pages((unsigned wong)dccp_hashinfo.bhash, bhash_owdew);
out_fwee_dccp_wocks:
	inet_ehash_wocks_fwee(&dccp_hashinfo);
out_fwee_dccp_ehash:
	fwee_pages((unsigned wong)dccp_hashinfo.ehash, ehash_owdew);
out_fwee_bind2_bucket_cachep:
	kmem_cache_destwoy(dccp_hashinfo.bind2_bucket_cachep);
out_fwee_bind_bucket_cachep:
	kmem_cache_destwoy(dccp_hashinfo.bind_bucket_cachep);
out_fwee_hashinfo2:
	inet_hashinfo2_fwee_mod(&dccp_hashinfo);
out_faiw:
	dccp_hashinfo.bhash = NUWW;
	dccp_hashinfo.bhash2 = NUWW;
	dccp_hashinfo.ehash = NUWW;
	dccp_hashinfo.bind_bucket_cachep = NUWW;
	dccp_hashinfo.bind2_bucket_cachep = NUWW;
	wetuwn wc;
}

static void __exit dccp_fini(void)
{
	int bhash_owdew = get_owdew(dccp_hashinfo.bhash_size *
				    sizeof(stwuct inet_bind_hashbucket));

	ccid_cweanup_buiwtins();
	dccp_mib_exit();
	fwee_pages((unsigned wong)dccp_hashinfo.bhash, bhash_owdew);
	fwee_pages((unsigned wong)dccp_hashinfo.bhash2, bhash_owdew);
	fwee_pages((unsigned wong)dccp_hashinfo.ehash,
		   get_owdew((dccp_hashinfo.ehash_mask + 1) *
			     sizeof(stwuct inet_ehash_bucket)));
	inet_ehash_wocks_fwee(&dccp_hashinfo);
	kmem_cache_destwoy(dccp_hashinfo.bind_bucket_cachep);
	dccp_ackvec_exit();
	dccp_sysctw_exit();
	inet_hashinfo2_fwee_mod(&dccp_hashinfo);
}

moduwe_init(dccp_init);
moduwe_exit(dccp_fini);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>");
MODUWE_DESCWIPTION("DCCP - Datagwam Congestion Contwowwed Pwotocow");
