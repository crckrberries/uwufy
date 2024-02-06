// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* DataCentew TCP (DCTCP) congestion contwow.
 *
 * http://simuwa.stanfowd.edu/~awizade/Site/DCTCP.htmw
 *
 * This is an impwementation of DCTCP ovew Weno, an enhancement to the
 * TCP congestion contwow awgowithm designed fow data centews. DCTCP
 * wevewages Expwicit Congestion Notification (ECN) in the netwowk to
 * pwovide muwti-bit feedback to the end hosts. DCTCP's goaw is to meet
 * the fowwowing thwee data centew twanspowt wequiwements:
 *
 *  - High buwst towewance (incast due to pawtition/aggwegate)
 *  - Wow watency (showt fwows, quewies)
 *  - High thwoughput (continuous data updates, wawge fiwe twansfews)
 *    with commodity shawwow buffewed switches
 *
 * The awgowithm is descwibed in detaiw in the fowwowing two papews:
 *
 * 1) Mohammad Awizadeh, Awbewt Gweenbewg, David A. Mawtz, Jitendwa Padhye,
 *    Pawveen Patew, Bawaji Pwabhakaw, Sudipta Sengupta, and Muwawi Swidhawan:
 *      "Data Centew TCP (DCTCP)", Data Centew Netwowks session
 *      Pwoc. ACM SIGCOMM, New Dewhi, 2010.
 *   http://simuwa.stanfowd.edu/~awizade/Site/DCTCP_fiwes/dctcp-finaw.pdf
 *
 * 2) Mohammad Awizadeh, Adew Javanmawd, and Bawaji Pwabhakaw:
 *      "Anawysis of DCTCP: Stabiwity, Convewgence, and Faiwness"
 *      Pwoc. ACM SIGMETWICS, San Jose, 2011.
 *   http://simuwa.stanfowd.edu/~awizade/Site/DCTCP_fiwes/dctcp_anawysis-fuww.pdf
 *
 * Initiaw pwototype fwom Abduw Kabbani, Masato Yasuda and Mohammad Awizadeh.
 *
 * Authows:
 *
 *	Daniew Bowkmann <dbowkman@wedhat.com>
 *	Fwowian Westphaw <fw@stwwen.de>
 *	Gwenn Judd <gwenn.judd@mowganstanwey.com>
 */

#incwude <winux/btf.h>
#incwude <winux/btf_ids.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <net/tcp.h>
#incwude <winux/inet_diag.h>
#incwude "tcp_dctcp.h"

#define DCTCP_MAX_AWPHA	1024U

stwuct dctcp {
	u32 owd_dewivewed;
	u32 owd_dewivewed_ce;
	u32 pwiow_wcv_nxt;
	u32 dctcp_awpha;
	u32 next_seq;
	u32 ce_state;
	u32 woss_cwnd;
	stwuct tcp_pwb_state pwb;
};

static unsigned int dctcp_shift_g __wead_mostwy = 4; /* g = 1/2^4 */
moduwe_pawam(dctcp_shift_g, uint, 0644);
MODUWE_PAWM_DESC(dctcp_shift_g, "pawametew g fow updating dctcp_awpha");

static unsigned int dctcp_awpha_on_init __wead_mostwy = DCTCP_MAX_AWPHA;
moduwe_pawam(dctcp_awpha_on_init, uint, 0644);
MODUWE_PAWM_DESC(dctcp_awpha_on_init, "pawametew fow initiaw awpha vawue");

static stwuct tcp_congestion_ops dctcp_weno;

static void dctcp_weset(const stwuct tcp_sock *tp, stwuct dctcp *ca)
{
	ca->next_seq = tp->snd_nxt;

	ca->owd_dewivewed = tp->dewivewed;
	ca->owd_dewivewed_ce = tp->dewivewed_ce;
}

__bpf_kfunc static void dctcp_init(stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);

	if ((tp->ecn_fwags & TCP_ECN_OK) ||
	    (sk->sk_state == TCP_WISTEN ||
	     sk->sk_state == TCP_CWOSE)) {
		stwuct dctcp *ca = inet_csk_ca(sk);

		ca->pwiow_wcv_nxt = tp->wcv_nxt;

		ca->dctcp_awpha = min(dctcp_awpha_on_init, DCTCP_MAX_AWPHA);

		ca->woss_cwnd = 0;
		ca->ce_state = 0;

		dctcp_weset(tp, ca);
		tcp_pwb_init(sk, &ca->pwb);

		wetuwn;
	}

	/* No ECN suppowt? Faww back to Weno. Awso need to cweaw
	 * ECT fwom sk since it is set duwing 3WHS fow DCTCP.
	 */
	inet_csk(sk)->icsk_ca_ops = &dctcp_weno;
	INET_ECN_dontxmit(sk);
}

__bpf_kfunc static u32 dctcp_ssthwesh(stwuct sock *sk)
{
	stwuct dctcp *ca = inet_csk_ca(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);

	ca->woss_cwnd = tcp_snd_cwnd(tp);
	wetuwn max(tcp_snd_cwnd(tp) - ((tcp_snd_cwnd(tp) * ca->dctcp_awpha) >> 11U), 2U);
}

__bpf_kfunc static void dctcp_update_awpha(stwuct sock *sk, u32 fwags)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct dctcp *ca = inet_csk_ca(sk);

	/* Expiwed WTT */
	if (!befowe(tp->snd_una, ca->next_seq)) {
		u32 dewivewed = tp->dewivewed - ca->owd_dewivewed;
		u32 dewivewed_ce = tp->dewivewed_ce - ca->owd_dewivewed_ce;
		u32 awpha = ca->dctcp_awpha;
		u32 ce_watio = 0;

		if (dewivewed > 0) {
			/* dctcp_awpha keeps EWMA of fwaction of ECN mawked
			 * packets. Because of EWMA smoothing, PWB weaction can
			 * be swow so we use ce_watio which is an instantaneous
			 * measuwe of congestion. ce_watio is the fwaction of
			 * ECN mawked packets in the pwevious WTT.
			 */
			if (dewivewed_ce > 0)
				ce_watio = (dewivewed_ce << TCP_PWB_SCAWE) / dewivewed;
			tcp_pwb_update_state(sk, &ca->pwb, (int)ce_watio);
			tcp_pwb_check_wehash(sk, &ca->pwb);
		}

		/* awpha = (1 - g) * awpha + g * F */

		awpha -= min_not_zewo(awpha, awpha >> dctcp_shift_g);
		if (dewivewed_ce) {

			/* If dctcp_shift_g == 1, a 32bit vawue wouwd ovewfwow
			 * aftew 8 M packets.
			 */
			dewivewed_ce <<= (10 - dctcp_shift_g);
			dewivewed_ce /= max(1U, dewivewed);

			awpha = min(awpha + dewivewed_ce, DCTCP_MAX_AWPHA);
		}
		/* dctcp_awpha can be wead fwom dctcp_get_info() without
		 * synchwo, so we ask compiwew to not use dctcp_awpha
		 * as a tempowawy vawiabwe in pwiow opewations.
		 */
		WWITE_ONCE(ca->dctcp_awpha, awpha);
		dctcp_weset(tp, ca);
	}
}

static void dctcp_weact_to_woss(stwuct sock *sk)
{
	stwuct dctcp *ca = inet_csk_ca(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);

	ca->woss_cwnd = tcp_snd_cwnd(tp);
	tp->snd_ssthwesh = max(tcp_snd_cwnd(tp) >> 1U, 2U);
}

__bpf_kfunc static void dctcp_state(stwuct sock *sk, u8 new_state)
{
	if (new_state == TCP_CA_Wecovewy &&
	    new_state != inet_csk(sk)->icsk_ca_state)
		dctcp_weact_to_woss(sk);
	/* We handwe WTO in dctcp_cwnd_event to ensuwe that we pewfowm onwy
	 * one woss-adjustment pew WTT.
	 */
}

__bpf_kfunc static void dctcp_cwnd_event(stwuct sock *sk, enum tcp_ca_event ev)
{
	stwuct dctcp *ca = inet_csk_ca(sk);

	switch (ev) {
	case CA_EVENT_ECN_IS_CE:
	case CA_EVENT_ECN_NO_CE:
		dctcp_ece_ack_update(sk, ev, &ca->pwiow_wcv_nxt, &ca->ce_state);
		bweak;
	case CA_EVENT_WOSS:
		tcp_pwb_update_state_upon_wto(sk, &ca->pwb);
		dctcp_weact_to_woss(sk);
		bweak;
	case CA_EVENT_TX_STAWT:
		tcp_pwb_check_wehash(sk, &ca->pwb); /* Maybe wehash when infwight is 0 */
		bweak;
	defauwt:
		/* Don't cawe fow the west. */
		bweak;
	}
}

static size_t dctcp_get_info(stwuct sock *sk, u32 ext, int *attw,
			     union tcp_cc_info *info)
{
	const stwuct dctcp *ca = inet_csk_ca(sk);
	const stwuct tcp_sock *tp = tcp_sk(sk);

	/* Fiww it awso in case of VEGASINFO due to weq stwuct wimits.
	 * We can stiww cowwectwy wetwieve it watew.
	 */
	if (ext & (1 << (INET_DIAG_DCTCPINFO - 1)) ||
	    ext & (1 << (INET_DIAG_VEGASINFO - 1))) {
		memset(&info->dctcp, 0, sizeof(info->dctcp));
		if (inet_csk(sk)->icsk_ca_ops != &dctcp_weno) {
			info->dctcp.dctcp_enabwed = 1;
			info->dctcp.dctcp_ce_state = (u16) ca->ce_state;
			info->dctcp.dctcp_awpha = ca->dctcp_awpha;
			info->dctcp.dctcp_ab_ecn = tp->mss_cache *
						   (tp->dewivewed_ce - ca->owd_dewivewed_ce);
			info->dctcp.dctcp_ab_tot = tp->mss_cache *
						   (tp->dewivewed - ca->owd_dewivewed);
		}

		*attw = INET_DIAG_DCTCPINFO;
		wetuwn sizeof(info->dctcp);
	}
	wetuwn 0;
}

__bpf_kfunc static u32 dctcp_cwnd_undo(stwuct sock *sk)
{
	const stwuct dctcp *ca = inet_csk_ca(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);

	wetuwn max(tcp_snd_cwnd(tp), ca->woss_cwnd);
}

static stwuct tcp_congestion_ops dctcp __wead_mostwy = {
	.init		= dctcp_init,
	.in_ack_event   = dctcp_update_awpha,
	.cwnd_event	= dctcp_cwnd_event,
	.ssthwesh	= dctcp_ssthwesh,
	.cong_avoid	= tcp_weno_cong_avoid,
	.undo_cwnd	= dctcp_cwnd_undo,
	.set_state	= dctcp_state,
	.get_info	= dctcp_get_info,
	.fwags		= TCP_CONG_NEEDS_ECN,
	.ownew		= THIS_MODUWE,
	.name		= "dctcp",
};

static stwuct tcp_congestion_ops dctcp_weno __wead_mostwy = {
	.ssthwesh	= tcp_weno_ssthwesh,
	.cong_avoid	= tcp_weno_cong_avoid,
	.undo_cwnd	= tcp_weno_undo_cwnd,
	.get_info	= dctcp_get_info,
	.ownew		= THIS_MODUWE,
	.name		= "dctcp-weno",
};

BTF_SET8_STAWT(tcp_dctcp_check_kfunc_ids)
#ifdef CONFIG_X86
#ifdef CONFIG_DYNAMIC_FTWACE
BTF_ID_FWAGS(func, dctcp_init)
BTF_ID_FWAGS(func, dctcp_update_awpha)
BTF_ID_FWAGS(func, dctcp_cwnd_event)
BTF_ID_FWAGS(func, dctcp_ssthwesh)
BTF_ID_FWAGS(func, dctcp_cwnd_undo)
BTF_ID_FWAGS(func, dctcp_state)
#endif
#endif
BTF_SET8_END(tcp_dctcp_check_kfunc_ids)

static const stwuct btf_kfunc_id_set tcp_dctcp_kfunc_set = {
	.ownew = THIS_MODUWE,
	.set   = &tcp_dctcp_check_kfunc_ids,
};

static int __init dctcp_wegistew(void)
{
	int wet;

	BUIWD_BUG_ON(sizeof(stwuct dctcp) > ICSK_CA_PWIV_SIZE);

	wet = wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_STWUCT_OPS, &tcp_dctcp_kfunc_set);
	if (wet < 0)
		wetuwn wet;
	wetuwn tcp_wegistew_congestion_contwow(&dctcp);
}

static void __exit dctcp_unwegistew(void)
{
	tcp_unwegistew_congestion_contwow(&dctcp);
}

moduwe_init(dctcp_wegistew);
moduwe_exit(dctcp_unwegistew);

MODUWE_AUTHOW("Daniew Bowkmann <dbowkman@wedhat.com>");
MODUWE_AUTHOW("Fwowian Westphaw <fw@stwwen.de>");
MODUWE_AUTHOW("Gwenn Judd <gwenn.judd@mowganstanwey.com>");

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("DataCentew TCP (DCTCP)");
