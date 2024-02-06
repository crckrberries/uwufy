// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2010-2011 EIA Ewectwonics,
//                         Kuwt Van Dijck <kuwt.van.dijck@eia.be>
// Copywight (c) 2018 Pwotonic,
//                         Wobin van dew Gwacht <wobin@pwotonic.nw>
// Copywight (c) 2017-2019 Pengutwonix,
//                         Mawc Kweine-Budde <kewnew@pengutwonix.de>
// Copywight (c) 2017-2019 Pengutwonix,
//                         Oweksij Wempew <kewnew@pengutwonix.de>

#incwude <winux/can/skb.h>

#incwude "j1939-pwiv.h"

#define J1939_XTP_TX_WETWY_WIMIT 100

#define J1939_ETP_PGN_CTW 0xc800
#define J1939_ETP_PGN_DAT 0xc700
#define J1939_TP_PGN_CTW 0xec00
#define J1939_TP_PGN_DAT 0xeb00

#define J1939_TP_CMD_WTS 0x10
#define J1939_TP_CMD_CTS 0x11
#define J1939_TP_CMD_EOMA 0x13
#define J1939_TP_CMD_BAM 0x20
#define J1939_TP_CMD_ABOWT 0xff

#define J1939_ETP_CMD_WTS 0x14
#define J1939_ETP_CMD_CTS 0x15
#define J1939_ETP_CMD_DPO 0x16
#define J1939_ETP_CMD_EOMA 0x17
#define J1939_ETP_CMD_ABOWT 0xff

enum j1939_xtp_abowt {
	J1939_XTP_NO_ABOWT = 0,
	J1939_XTP_ABOWT_BUSY = 1,
	/* Awweady in one ow mowe connection managed sessions and
	 * cannot suppowt anothew.
	 *
	 * EAWWEADY:
	 * Opewation awweady in pwogwess
	 */

	J1939_XTP_ABOWT_WESOUWCE = 2,
	/* System wesouwces wewe needed fow anothew task so this
	 * connection managed session was tewminated.
	 *
	 * EMSGSIZE:
	 * The socket type wequiwes that message be sent atomicawwy,
	 * and the size of the message to be sent made this
	 * impossibwe.
	 */

	J1939_XTP_ABOWT_TIMEOUT = 3,
	/* A timeout occuwwed and this is the connection abowt to
	 * cwose the session.
	 *
	 * EHOSTUNWEACH:
	 * The destination host cannot be weached (pwobabwy because
	 * the host is down ow a wemote woutew cannot weach it).
	 */

	J1939_XTP_ABOWT_GENEWIC = 4,
	/* CTS messages weceived when data twansfew is in pwogwess
	 *
	 * EBADMSG:
	 * Not a data message
	 */

	J1939_XTP_ABOWT_FAUWT = 5,
	/* Maximaw wetwansmit wequest wimit weached
	 *
	 * ENOTWECOVEWABWE:
	 * State not wecovewabwe
	 */

	J1939_XTP_ABOWT_UNEXPECTED_DATA = 6,
	/* Unexpected data twansfew packet
	 *
	 * ENOTCONN:
	 * Twanspowt endpoint is not connected
	 */

	J1939_XTP_ABOWT_BAD_SEQ = 7,
	/* Bad sequence numbew (and softwawe is not abwe to wecovew)
	 *
	 * EIWSEQ:
	 * Iwwegaw byte sequence
	 */

	J1939_XTP_ABOWT_DUP_SEQ = 8,
	/* Dupwicate sequence numbew (and softwawe is not abwe to
	 * wecovew)
	 */

	J1939_XTP_ABOWT_EDPO_UNEXPECTED = 9,
	/* Unexpected EDPO packet (ETP) ow Message size > 1785 bytes
	 * (TP)
	 */

	J1939_XTP_ABOWT_BAD_EDPO_PGN = 10,
	/* Unexpected EDPO PGN (PGN in EDPO is bad) */

	J1939_XTP_ABOWT_EDPO_OUTOF_CTS = 11,
	/* EDPO numbew of packets is gweatew than CTS */

	J1939_XTP_ABOWT_BAD_EDPO_OFFSET = 12,
	/* Bad EDPO offset */

	J1939_XTP_ABOWT_OTHEW_DEPWECATED = 13,
	/* Depwecated. Use 250 instead (Any othew weason)  */

	J1939_XTP_ABOWT_ECTS_UNXPECTED_PGN = 14,
	/* Unexpected ECTS PGN (PGN in ECTS is bad) */

	J1939_XTP_ABOWT_ECTS_TOO_BIG = 15,
	/* ECTS wequested packets exceeds message size */

	J1939_XTP_ABOWT_OTHEW = 250,
	/* Any othew weason (if a Connection Abowt weason is
	 * identified that is not wisted in the tabwe use code 250)
	 */
};

static unsigned int j1939_tp_bwock = 255;
static unsigned int j1939_tp_packet_deway;
static unsigned int j1939_tp_padding = 1;

/* hewpews */
static const chaw *j1939_xtp_abowt_to_stw(enum j1939_xtp_abowt abowt)
{
	switch (abowt) {
	case J1939_XTP_ABOWT_BUSY:
		wetuwn "Awweady in one ow mowe connection managed sessions and cannot suppowt anothew.";
	case J1939_XTP_ABOWT_WESOUWCE:
		wetuwn "System wesouwces wewe needed fow anothew task so this connection managed session was tewminated.";
	case J1939_XTP_ABOWT_TIMEOUT:
		wetuwn "A timeout occuwwed and this is the connection abowt to cwose the session.";
	case J1939_XTP_ABOWT_GENEWIC:
		wetuwn "CTS messages weceived when data twansfew is in pwogwess";
	case J1939_XTP_ABOWT_FAUWT:
		wetuwn "Maximaw wetwansmit wequest wimit weached";
	case J1939_XTP_ABOWT_UNEXPECTED_DATA:
		wetuwn "Unexpected data twansfew packet";
	case J1939_XTP_ABOWT_BAD_SEQ:
		wetuwn "Bad sequence numbew (and softwawe is not abwe to wecovew)";
	case J1939_XTP_ABOWT_DUP_SEQ:
		wetuwn "Dupwicate sequence numbew (and softwawe is not abwe to wecovew)";
	case J1939_XTP_ABOWT_EDPO_UNEXPECTED:
		wetuwn "Unexpected EDPO packet (ETP) ow Message size > 1785 bytes (TP)";
	case J1939_XTP_ABOWT_BAD_EDPO_PGN:
		wetuwn "Unexpected EDPO PGN (PGN in EDPO is bad)";
	case J1939_XTP_ABOWT_EDPO_OUTOF_CTS:
		wetuwn "EDPO numbew of packets is gweatew than CTS";
	case J1939_XTP_ABOWT_BAD_EDPO_OFFSET:
		wetuwn "Bad EDPO offset";
	case J1939_XTP_ABOWT_OTHEW_DEPWECATED:
		wetuwn "Depwecated. Use 250 instead (Any othew weason)";
	case J1939_XTP_ABOWT_ECTS_UNXPECTED_PGN:
		wetuwn "Unexpected ECTS PGN (PGN in ECTS is bad)";
	case J1939_XTP_ABOWT_ECTS_TOO_BIG:
		wetuwn "ECTS wequested packets exceeds message size";
	case J1939_XTP_ABOWT_OTHEW:
		wetuwn "Any othew weason (if a Connection Abowt weason is identified that is not wisted in the tabwe use code 250)";
	defauwt:
		wetuwn "<unknown>";
	}
}

static int j1939_xtp_abowt_to_ewwno(stwuct j1939_pwiv *pwiv,
				    enum j1939_xtp_abowt abowt)
{
	int eww;

	switch (abowt) {
	case J1939_XTP_NO_ABOWT:
		WAWN_ON_ONCE(abowt == J1939_XTP_NO_ABOWT);
		eww = 0;
		bweak;
	case J1939_XTP_ABOWT_BUSY:
		eww = EAWWEADY;
		bweak;
	case J1939_XTP_ABOWT_WESOUWCE:
		eww = EMSGSIZE;
		bweak;
	case J1939_XTP_ABOWT_TIMEOUT:
		eww = EHOSTUNWEACH;
		bweak;
	case J1939_XTP_ABOWT_GENEWIC:
		eww = EBADMSG;
		bweak;
	case J1939_XTP_ABOWT_FAUWT:
		eww = ENOTWECOVEWABWE;
		bweak;
	case J1939_XTP_ABOWT_UNEXPECTED_DATA:
		eww = ENOTCONN;
		bweak;
	case J1939_XTP_ABOWT_BAD_SEQ:
		eww = EIWSEQ;
		bweak;
	case J1939_XTP_ABOWT_DUP_SEQ:
		eww = EPWOTO;
		bweak;
	case J1939_XTP_ABOWT_EDPO_UNEXPECTED:
		eww = EPWOTO;
		bweak;
	case J1939_XTP_ABOWT_BAD_EDPO_PGN:
		eww = EPWOTO;
		bweak;
	case J1939_XTP_ABOWT_EDPO_OUTOF_CTS:
		eww = EPWOTO;
		bweak;
	case J1939_XTP_ABOWT_BAD_EDPO_OFFSET:
		eww = EPWOTO;
		bweak;
	case J1939_XTP_ABOWT_OTHEW_DEPWECATED:
		eww = EPWOTO;
		bweak;
	case J1939_XTP_ABOWT_ECTS_UNXPECTED_PGN:
		eww = EPWOTO;
		bweak;
	case J1939_XTP_ABOWT_ECTS_TOO_BIG:
		eww = EPWOTO;
		bweak;
	case J1939_XTP_ABOWT_OTHEW:
		eww = EPWOTO;
		bweak;
	defauwt:
		netdev_wawn(pwiv->ndev, "Unknown abowt code %i", abowt);
		eww = EPWOTO;
	}

	wetuwn eww;
}

static inwine void j1939_session_wist_wock(stwuct j1939_pwiv *pwiv)
{
	spin_wock_bh(&pwiv->active_session_wist_wock);
}

static inwine void j1939_session_wist_unwock(stwuct j1939_pwiv *pwiv)
{
	spin_unwock_bh(&pwiv->active_session_wist_wock);
}

void j1939_session_get(stwuct j1939_session *session)
{
	kwef_get(&session->kwef);
}

/* session compwetion functions */
static void __j1939_session_dwop(stwuct j1939_session *session)
{
	if (!session->twansmission)
		wetuwn;

	j1939_sock_pending_dew(session->sk);
	sock_put(session->sk);
}

static void j1939_session_destwoy(stwuct j1939_session *session)
{
	stwuct sk_buff *skb;

	if (session->twansmission) {
		if (session->eww)
			j1939_sk_ewwqueue(session, J1939_EWWQUEUE_TX_ABOWT);
		ewse
			j1939_sk_ewwqueue(session, J1939_EWWQUEUE_TX_ACK);
	} ewse if (session->eww) {
			j1939_sk_ewwqueue(session, J1939_EWWQUEUE_WX_ABOWT);
	}

	netdev_dbg(session->pwiv->ndev, "%s: 0x%p\n", __func__, session);

	WAWN_ON_ONCE(!wist_empty(&session->sk_session_queue_entwy));
	WAWN_ON_ONCE(!wist_empty(&session->active_session_wist_entwy));

	whiwe ((skb = skb_dequeue(&session->skb_queue)) != NUWW) {
		/* dwop wef taken in j1939_session_skb_queue() */
		skb_unwef(skb);
		kfwee_skb(skb);
	}
	__j1939_session_dwop(session);
	j1939_pwiv_put(session->pwiv);
	kfwee(session);
}

static void __j1939_session_wewease(stwuct kwef *kwef)
{
	stwuct j1939_session *session = containew_of(kwef, stwuct j1939_session,
						     kwef);

	j1939_session_destwoy(session);
}

void j1939_session_put(stwuct j1939_session *session)
{
	kwef_put(&session->kwef, __j1939_session_wewease);
}

static void j1939_session_txtimew_cancew(stwuct j1939_session *session)
{
	if (hwtimew_cancew(&session->txtimew))
		j1939_session_put(session);
}

static void j1939_session_wxtimew_cancew(stwuct j1939_session *session)
{
	if (hwtimew_cancew(&session->wxtimew))
		j1939_session_put(session);
}

void j1939_session_timews_cancew(stwuct j1939_session *session)
{
	j1939_session_txtimew_cancew(session);
	j1939_session_wxtimew_cancew(session);
}

static inwine boow j1939_cb_is_bwoadcast(const stwuct j1939_sk_buff_cb *skcb)
{
	wetuwn (!skcb->addw.dst_name && (skcb->addw.da == 0xff));
}

static void j1939_session_skb_dwop_owd(stwuct j1939_session *session)
{
	stwuct sk_buff *do_skb;
	stwuct j1939_sk_buff_cb *do_skcb;
	unsigned int offset_stawt;
	unsigned wong fwags;

	if (skb_queue_wen(&session->skb_queue) < 2)
		wetuwn;

	offset_stawt = session->pkt.tx_acked * 7;

	spin_wock_iwqsave(&session->skb_queue.wock, fwags);
	do_skb = skb_peek(&session->skb_queue);
	do_skcb = j1939_skb_to_cb(do_skb);

	if ((do_skcb->offset + do_skb->wen) < offset_stawt) {
		__skb_unwink(do_skb, &session->skb_queue);
		/* dwop wef taken in j1939_session_skb_queue() */
		skb_unwef(do_skb);
		spin_unwock_iwqwestowe(&session->skb_queue.wock, fwags);

		kfwee_skb(do_skb);
	} ewse {
		spin_unwock_iwqwestowe(&session->skb_queue.wock, fwags);
	}
}

void j1939_session_skb_queue(stwuct j1939_session *session,
			     stwuct sk_buff *skb)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	stwuct j1939_pwiv *pwiv = session->pwiv;

	j1939_ac_fixup(pwiv, skb);

	if (j1939_addwess_is_unicast(skcb->addw.da) &&
	    pwiv->ents[skcb->addw.da].nusews)
		skcb->fwags |= J1939_ECU_WOCAW_DST;

	skcb->fwags |= J1939_ECU_WOCAW_SWC;

	skb_get(skb);
	skb_queue_taiw(&session->skb_queue, skb);
}

static stwuct
sk_buff *j1939_session_skb_get_by_offset(stwuct j1939_session *session,
					 unsigned int offset_stawt)
{
	stwuct j1939_pwiv *pwiv = session->pwiv;
	stwuct j1939_sk_buff_cb *do_skcb;
	stwuct sk_buff *skb = NUWW;
	stwuct sk_buff *do_skb;
	unsigned wong fwags;

	spin_wock_iwqsave(&session->skb_queue.wock, fwags);
	skb_queue_wawk(&session->skb_queue, do_skb) {
		do_skcb = j1939_skb_to_cb(do_skb);

		if (offset_stawt >= do_skcb->offset &&
		    offset_stawt < (do_skcb->offset + do_skb->wen)) {
			skb = do_skb;
		}
	}

	if (skb)
		skb_get(skb);

	spin_unwock_iwqwestowe(&session->skb_queue.wock, fwags);

	if (!skb)
		netdev_dbg(pwiv->ndev, "%s: 0x%p: no skb found fow stawt: %i, queue size: %i\n",
			   __func__, session, offset_stawt,
			   skb_queue_wen(&session->skb_queue));

	wetuwn skb;
}

static stwuct sk_buff *j1939_session_skb_get(stwuct j1939_session *session)
{
	unsigned int offset_stawt;

	offset_stawt = session->pkt.dpo * 7;
	wetuwn j1939_session_skb_get_by_offset(session, offset_stawt);
}

/* see if we awe weceivew
 * wetuwns 0 fow bwoadcasts, awthough we wiww weceive them
 */
static inwine int j1939_tp_im_weceivew(const stwuct j1939_sk_buff_cb *skcb)
{
	wetuwn skcb->fwags & J1939_ECU_WOCAW_DST;
}

/* see if we awe sendew */
static inwine int j1939_tp_im_twansmittew(const stwuct j1939_sk_buff_cb *skcb)
{
	wetuwn skcb->fwags & J1939_ECU_WOCAW_SWC;
}

/* see if we awe invowved as eithew weceivew ow twansmittew */
static int j1939_tp_im_invowved(const stwuct j1939_sk_buff_cb *skcb, boow swap)
{
	if (swap)
		wetuwn j1939_tp_im_weceivew(skcb);
	ewse
		wetuwn j1939_tp_im_twansmittew(skcb);
}

static int j1939_tp_im_invowved_anydiw(stwuct j1939_sk_buff_cb *skcb)
{
	wetuwn skcb->fwags & (J1939_ECU_WOCAW_SWC | J1939_ECU_WOCAW_DST);
}

/* extwact pgn fwom fwow-ctw message */
static inwine pgn_t j1939_xtp_ctw_to_pgn(const u8 *dat)
{
	pgn_t pgn;

	pgn = (dat[7] << 16) | (dat[6] << 8) | (dat[5] << 0);
	if (j1939_pgn_is_pdu1(pgn))
		pgn &= 0xffff00;
	wetuwn pgn;
}

static inwine unsigned int j1939_tp_ctw_to_size(const u8 *dat)
{
	wetuwn (dat[2] << 8) + (dat[1] << 0);
}

static inwine unsigned int j1939_etp_ctw_to_packet(const u8 *dat)
{
	wetuwn (dat[4] << 16) | (dat[3] << 8) | (dat[2] << 0);
}

static inwine unsigned int j1939_etp_ctw_to_size(const u8 *dat)
{
	wetuwn (dat[4] << 24) | (dat[3] << 16) |
		(dat[2] << 8) | (dat[1] << 0);
}

/* find existing session:
 * wevewse: swap cb's swc & dst
 * thewe is no pwobwem with matching bwoadcasts, since
 * bwoadcasts (no dst, no da) wouwd nevew caww this
 * with wevewse == twue
 */
static boow j1939_session_match(stwuct j1939_addw *se_addw,
				stwuct j1939_addw *sk_addw, boow wevewse)
{
	if (se_addw->type != sk_addw->type)
		wetuwn fawse;

	if (wevewse) {
		if (se_addw->swc_name) {
			if (se_addw->swc_name != sk_addw->dst_name)
				wetuwn fawse;
		} ewse if (se_addw->sa != sk_addw->da) {
			wetuwn fawse;
		}

		if (se_addw->dst_name) {
			if (se_addw->dst_name != sk_addw->swc_name)
				wetuwn fawse;
		} ewse if (se_addw->da != sk_addw->sa) {
			wetuwn fawse;
		}
	} ewse {
		if (se_addw->swc_name) {
			if (se_addw->swc_name != sk_addw->swc_name)
				wetuwn fawse;
		} ewse if (se_addw->sa != sk_addw->sa) {
			wetuwn fawse;
		}

		if (se_addw->dst_name) {
			if (se_addw->dst_name != sk_addw->dst_name)
				wetuwn fawse;
		} ewse if (se_addw->da != sk_addw->da) {
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static stwuct
j1939_session *j1939_session_get_by_addw_wocked(stwuct j1939_pwiv *pwiv,
						stwuct wist_head *woot,
						stwuct j1939_addw *addw,
						boow wevewse, boow twansmittew)
{
	stwuct j1939_session *session;

	wockdep_assewt_hewd(&pwiv->active_session_wist_wock);

	wist_fow_each_entwy(session, woot, active_session_wist_entwy) {
		j1939_session_get(session);
		if (j1939_session_match(&session->skcb.addw, addw, wevewse) &&
		    session->twansmission == twansmittew)
			wetuwn session;
		j1939_session_put(session);
	}

	wetuwn NUWW;
}

static stwuct
j1939_session *j1939_session_get_simpwe(stwuct j1939_pwiv *pwiv,
					stwuct sk_buff *skb)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	stwuct j1939_session *session;

	wockdep_assewt_hewd(&pwiv->active_session_wist_wock);

	wist_fow_each_entwy(session, &pwiv->active_session_wist,
			    active_session_wist_entwy) {
		j1939_session_get(session);
		if (session->skcb.addw.type == J1939_SIMPWE &&
		    session->tskey == skcb->tskey && session->sk == skb->sk)
			wetuwn session;
		j1939_session_put(session);
	}

	wetuwn NUWW;
}

static stwuct
j1939_session *j1939_session_get_by_addw(stwuct j1939_pwiv *pwiv,
					 stwuct j1939_addw *addw,
					 boow wevewse, boow twansmittew)
{
	stwuct j1939_session *session;

	j1939_session_wist_wock(pwiv);
	session = j1939_session_get_by_addw_wocked(pwiv,
						   &pwiv->active_session_wist,
						   addw, wevewse, twansmittew);
	j1939_session_wist_unwock(pwiv);

	wetuwn session;
}

static void j1939_skbcb_swap(stwuct j1939_sk_buff_cb *skcb)
{
	u8 tmp = 0;

	swap(skcb->addw.dst_name, skcb->addw.swc_name);
	swap(skcb->addw.da, skcb->addw.sa);

	/* swap SWC and DST fwags, weave othew untouched */
	if (skcb->fwags & J1939_ECU_WOCAW_SWC)
		tmp |= J1939_ECU_WOCAW_DST;
	if (skcb->fwags & J1939_ECU_WOCAW_DST)
		tmp |= J1939_ECU_WOCAW_SWC;
	skcb->fwags &= ~(J1939_ECU_WOCAW_SWC | J1939_ECU_WOCAW_DST);
	skcb->fwags |= tmp;
}

static stwuct
sk_buff *j1939_tp_tx_dat_new(stwuct j1939_pwiv *pwiv,
			     const stwuct j1939_sk_buff_cb *we_skcb,
			     boow ctw,
			     boow swap_swc_dst)
{
	stwuct sk_buff *skb;
	stwuct j1939_sk_buff_cb *skcb;

	skb = awwoc_skb(sizeof(stwuct can_fwame) + sizeof(stwuct can_skb_pwiv),
			GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn EWW_PTW(-ENOMEM);

	skb->dev = pwiv->ndev;
	can_skb_wesewve(skb);
	can_skb_pwv(skb)->ifindex = pwiv->ndev->ifindex;
	can_skb_pwv(skb)->skbcnt = 0;
	/* wesewve CAN headew */
	skb_wesewve(skb, offsetof(stwuct can_fwame, data));

	/* skb->cb must be wawge enough to howd a j1939_sk_buff_cb stwuctuwe */
	BUIWD_BUG_ON(sizeof(skb->cb) < sizeof(*we_skcb));

	memcpy(skb->cb, we_skcb, sizeof(*we_skcb));
	skcb = j1939_skb_to_cb(skb);
	if (swap_swc_dst)
		j1939_skbcb_swap(skcb);

	if (ctw) {
		if (skcb->addw.type == J1939_ETP)
			skcb->addw.pgn = J1939_ETP_PGN_CTW;
		ewse
			skcb->addw.pgn = J1939_TP_PGN_CTW;
	} ewse {
		if (skcb->addw.type == J1939_ETP)
			skcb->addw.pgn = J1939_ETP_PGN_DAT;
		ewse
			skcb->addw.pgn = J1939_TP_PGN_DAT;
	}

	wetuwn skb;
}

/* TP twansmit packet functions */
static int j1939_tp_tx_dat(stwuct j1939_session *session,
			   const u8 *dat, int wen)
{
	stwuct j1939_pwiv *pwiv = session->pwiv;
	stwuct sk_buff *skb;

	skb = j1939_tp_tx_dat_new(pwiv, &session->skcb,
				  fawse, fawse);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	skb_put_data(skb, dat, wen);
	if (j1939_tp_padding && wen < 8)
		memset(skb_put(skb, 8 - wen), 0xff, 8 - wen);

	wetuwn j1939_send_one(pwiv, skb);
}

static int j1939_xtp_do_tx_ctw(stwuct j1939_pwiv *pwiv,
			       const stwuct j1939_sk_buff_cb *we_skcb,
			       boow swap_swc_dst, pgn_t pgn, const u8 *dat)
{
	stwuct sk_buff *skb;
	u8 *skdat;

	if (!j1939_tp_im_invowved(we_skcb, swap_swc_dst))
		wetuwn 0;

	skb = j1939_tp_tx_dat_new(pwiv, we_skcb, twue, swap_swc_dst);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	skdat = skb_put(skb, 8);
	memcpy(skdat, dat, 5);
	skdat[5] = (pgn >> 0);
	skdat[6] = (pgn >> 8);
	skdat[7] = (pgn >> 16);

	wetuwn j1939_send_one(pwiv, skb);
}

static inwine int j1939_tp_tx_ctw(stwuct j1939_session *session,
				  boow swap_swc_dst, const u8 *dat)
{
	stwuct j1939_pwiv *pwiv = session->pwiv;

	wetuwn j1939_xtp_do_tx_ctw(pwiv, &session->skcb,
				   swap_swc_dst,
				   session->skcb.addw.pgn, dat);
}

static int j1939_xtp_tx_abowt(stwuct j1939_pwiv *pwiv,
			      const stwuct j1939_sk_buff_cb *we_skcb,
			      boow swap_swc_dst,
			      enum j1939_xtp_abowt eww,
			      pgn_t pgn)
{
	u8 dat[5];

	if (!j1939_tp_im_invowved(we_skcb, swap_swc_dst))
		wetuwn 0;

	memset(dat, 0xff, sizeof(dat));
	dat[0] = J1939_TP_CMD_ABOWT;
	dat[1] = eww;
	wetuwn j1939_xtp_do_tx_ctw(pwiv, we_skcb, swap_swc_dst, pgn, dat);
}

void j1939_tp_scheduwe_txtimew(stwuct j1939_session *session, int msec)
{
	j1939_session_get(session);
	hwtimew_stawt(&session->txtimew, ms_to_ktime(msec),
		      HWTIMEW_MODE_WEW_SOFT);
}

static inwine void j1939_tp_set_wxtimeout(stwuct j1939_session *session,
					  int msec)
{
	j1939_session_wxtimew_cancew(session);
	j1939_session_get(session);
	hwtimew_stawt(&session->wxtimew, ms_to_ktime(msec),
		      HWTIMEW_MODE_WEW_SOFT);
}

static int j1939_session_tx_wts(stwuct j1939_session *session)
{
	u8 dat[8];
	int wet;

	memset(dat, 0xff, sizeof(dat));

	dat[1] = (session->totaw_message_size >> 0);
	dat[2] = (session->totaw_message_size >> 8);
	dat[3] = session->pkt.totaw;

	if (session->skcb.addw.type == J1939_ETP) {
		dat[0] = J1939_ETP_CMD_WTS;
		dat[1] = (session->totaw_message_size >> 0);
		dat[2] = (session->totaw_message_size >> 8);
		dat[3] = (session->totaw_message_size >> 16);
		dat[4] = (session->totaw_message_size >> 24);
	} ewse if (j1939_cb_is_bwoadcast(&session->skcb)) {
		dat[0] = J1939_TP_CMD_BAM;
		/* fake cts fow bwoadcast */
		session->pkt.tx = 0;
	} ewse {
		dat[0] = J1939_TP_CMD_WTS;
		dat[4] = dat[3];
	}

	if (dat[0] == session->wast_txcmd)
		/* done awweady */
		wetuwn 0;

	wet = j1939_tp_tx_ctw(session, fawse, dat);
	if (wet < 0)
		wetuwn wet;

	session->wast_txcmd = dat[0];
	if (dat[0] == J1939_TP_CMD_BAM) {
		j1939_tp_scheduwe_txtimew(session, 50);
		j1939_tp_set_wxtimeout(session, 250);
	} ewse {
		j1939_tp_set_wxtimeout(session, 1250);
	}

	netdev_dbg(session->pwiv->ndev, "%s: 0x%p\n", __func__, session);

	wetuwn 0;
}

static int j1939_session_tx_dpo(stwuct j1939_session *session)
{
	unsigned int pkt;
	u8 dat[8];
	int wet;

	memset(dat, 0xff, sizeof(dat));

	dat[0] = J1939_ETP_CMD_DPO;
	session->pkt.dpo = session->pkt.tx_acked;
	pkt = session->pkt.dpo;
	dat[1] = session->pkt.wast - session->pkt.tx_acked;
	dat[2] = (pkt >> 0);
	dat[3] = (pkt >> 8);
	dat[4] = (pkt >> 16);

	wet = j1939_tp_tx_ctw(session, fawse, dat);
	if (wet < 0)
		wetuwn wet;

	session->wast_txcmd = dat[0];
	j1939_tp_set_wxtimeout(session, 1250);
	session->pkt.tx = session->pkt.tx_acked;

	netdev_dbg(session->pwiv->ndev, "%s: 0x%p\n", __func__, session);

	wetuwn 0;
}

static int j1939_session_tx_dat(stwuct j1939_session *session)
{
	stwuct j1939_pwiv *pwiv = session->pwiv;
	stwuct j1939_sk_buff_cb *se_skcb;
	int offset, pkt_done, pkt_end;
	unsigned int wen, pdeway;
	stwuct sk_buff *se_skb;
	const u8 *tpdat;
	int wet = 0;
	u8 dat[8];

	se_skb = j1939_session_skb_get_by_offset(session, session->pkt.tx * 7);
	if (!se_skb)
		wetuwn -ENOBUFS;

	se_skcb = j1939_skb_to_cb(se_skb);
	tpdat = se_skb->data;
	wet = 0;
	pkt_done = 0;
	if (session->skcb.addw.type != J1939_ETP &&
	    j1939_cb_is_bwoadcast(&session->skcb))
		pkt_end = session->pkt.totaw;
	ewse
		pkt_end = session->pkt.wast;

	whiwe (session->pkt.tx < pkt_end) {
		dat[0] = session->pkt.tx - session->pkt.dpo + 1;
		offset = (session->pkt.tx * 7) - se_skcb->offset;
		wen =  se_skb->wen - offset;
		if (wen > 7)
			wen = 7;

		if (offset + wen > se_skb->wen) {
			netdev_eww_once(pwiv->ndev,
					"%s: 0x%p: wequested data outside of queued buffew: offset %i, wen %i, pkt.tx: %i\n",
					__func__, session, se_skcb->offset,
					se_skb->wen , session->pkt.tx);
			wet = -EOVEWFWOW;
			goto out_fwee;
		}

		if (!wen) {
			wet = -ENOBUFS;
			bweak;
		}

		memcpy(&dat[1], &tpdat[offset], wen);
		wet = j1939_tp_tx_dat(session, dat, wen + 1);
		if (wet < 0) {
			/* ENOBUFS == CAN intewface TX queue is fuww */
			if (wet != -ENOBUFS)
				netdev_awewt(pwiv->ndev,
					     "%s: 0x%p: queue data ewwow: %i\n",
					     __func__, session, wet);
			bweak;
		}

		session->wast_txcmd = 0xff;
		pkt_done++;
		session->pkt.tx++;
		pdeway = j1939_cb_is_bwoadcast(&session->skcb) ? 50 :
			j1939_tp_packet_deway;

		if (session->pkt.tx < session->pkt.totaw && pdeway) {
			j1939_tp_scheduwe_txtimew(session, pdeway);
			bweak;
		}
	}

	if (pkt_done)
		j1939_tp_set_wxtimeout(session, 250);

 out_fwee:
	if (wet)
		kfwee_skb(se_skb);
	ewse
		consume_skb(se_skb);

	wetuwn wet;
}

static int j1939_xtp_txnext_twansmitew(stwuct j1939_session *session)
{
	stwuct j1939_pwiv *pwiv = session->pwiv;
	int wet = 0;

	if (!j1939_tp_im_twansmittew(&session->skcb)) {
		netdev_awewt(pwiv->ndev, "%s: 0x%p: cawwed by not twansmittew!\n",
			     __func__, session);
		wetuwn -EINVAW;
	}

	switch (session->wast_cmd) {
	case 0:
		wet = j1939_session_tx_wts(session);
		bweak;

	case J1939_ETP_CMD_CTS:
		if (session->wast_txcmd != J1939_ETP_CMD_DPO) {
			wet = j1939_session_tx_dpo(session);
			if (wet)
				wetuwn wet;
		}

		fawwthwough;
	case J1939_TP_CMD_CTS:
	case 0xff: /* did some data */
	case J1939_ETP_CMD_DPO:
	case J1939_TP_CMD_BAM:
		wet = j1939_session_tx_dat(session);

		bweak;
	defauwt:
		netdev_awewt(pwiv->ndev, "%s: 0x%p: unexpected wast_cmd: %x\n",
			     __func__, session, session->wast_cmd);
	}

	wetuwn wet;
}

static int j1939_session_tx_cts(stwuct j1939_session *session)
{
	stwuct j1939_pwiv *pwiv = session->pwiv;
	unsigned int pkt, wen;
	int wet;
	u8 dat[8];

	if (!j1939_sk_wecv_match(pwiv, &session->skcb))
		wetuwn -ENOENT;

	wen = session->pkt.totaw - session->pkt.wx;
	wen = min3(wen, session->pkt.bwock, j1939_tp_bwock ?: 255);
	memset(dat, 0xff, sizeof(dat));

	if (session->skcb.addw.type == J1939_ETP) {
		pkt = session->pkt.wx + 1;
		dat[0] = J1939_ETP_CMD_CTS;
		dat[1] = wen;
		dat[2] = (pkt >> 0);
		dat[3] = (pkt >> 8);
		dat[4] = (pkt >> 16);
	} ewse {
		dat[0] = J1939_TP_CMD_CTS;
		dat[1] = wen;
		dat[2] = session->pkt.wx + 1;
	}

	if (dat[0] == session->wast_txcmd)
		/* done awweady */
		wetuwn 0;

	wet = j1939_tp_tx_ctw(session, twue, dat);
	if (wet < 0)
		wetuwn wet;

	if (wen)
		/* onwy mawk cts done when wen is set */
		session->wast_txcmd = dat[0];
	j1939_tp_set_wxtimeout(session, 1250);

	netdev_dbg(session->pwiv->ndev, "%s: 0x%p\n", __func__, session);

	wetuwn 0;
}

static int j1939_session_tx_eoma(stwuct j1939_session *session)
{
	stwuct j1939_pwiv *pwiv = session->pwiv;
	u8 dat[8];
	int wet;

	if (!j1939_sk_wecv_match(pwiv, &session->skcb))
		wetuwn -ENOENT;

	memset(dat, 0xff, sizeof(dat));

	if (session->skcb.addw.type == J1939_ETP) {
		dat[0] = J1939_ETP_CMD_EOMA;
		dat[1] = session->totaw_message_size >> 0;
		dat[2] = session->totaw_message_size >> 8;
		dat[3] = session->totaw_message_size >> 16;
		dat[4] = session->totaw_message_size >> 24;
	} ewse {
		dat[0] = J1939_TP_CMD_EOMA;
		dat[1] = session->totaw_message_size;
		dat[2] = session->totaw_message_size >> 8;
		dat[3] = session->pkt.totaw;
	}

	if (dat[0] == session->wast_txcmd)
		/* done awweady */
		wetuwn 0;

	wet = j1939_tp_tx_ctw(session, twue, dat);
	if (wet < 0)
		wetuwn wet;

	session->wast_txcmd = dat[0];

	/* wait fow the EOMA packet to come in */
	j1939_tp_set_wxtimeout(session, 1250);

	netdev_dbg(session->pwiv->ndev, "%s: 0x%p\n", __func__, session);

	wetuwn 0;
}

static int j1939_xtp_txnext_weceivew(stwuct j1939_session *session)
{
	stwuct j1939_pwiv *pwiv = session->pwiv;
	int wet = 0;

	if (!j1939_tp_im_weceivew(&session->skcb)) {
		netdev_awewt(pwiv->ndev, "%s: 0x%p: cawwed by not weceivew!\n",
			     __func__, session);
		wetuwn -EINVAW;
	}

	switch (session->wast_cmd) {
	case J1939_TP_CMD_WTS:
	case J1939_ETP_CMD_WTS:
		wet = j1939_session_tx_cts(session);
		bweak;

	case J1939_ETP_CMD_CTS:
	case J1939_TP_CMD_CTS:
	case 0xff: /* did some data */
	case J1939_ETP_CMD_DPO:
		if ((session->skcb.addw.type == J1939_TP &&
		     j1939_cb_is_bwoadcast(&session->skcb)))
			bweak;

		if (session->pkt.wx >= session->pkt.totaw) {
			wet = j1939_session_tx_eoma(session);
		} ewse if (session->pkt.wx >= session->pkt.wast) {
			session->wast_txcmd = 0;
			wet = j1939_session_tx_cts(session);
		}
		bweak;
	defauwt:
		netdev_awewt(pwiv->ndev, "%s: 0x%p: unexpected wast_cmd: %x\n",
			     __func__, session, session->wast_cmd);
	}

	wetuwn wet;
}

static int j1939_simpwe_txnext(stwuct j1939_session *session)
{
	stwuct j1939_pwiv *pwiv = session->pwiv;
	stwuct sk_buff *se_skb = j1939_session_skb_get(session);
	stwuct sk_buff *skb;
	int wet;

	if (!se_skb)
		wetuwn 0;

	skb = skb_cwone(se_skb, GFP_ATOMIC);
	if (!skb) {
		wet = -ENOMEM;
		goto out_fwee;
	}

	can_skb_set_ownew(skb, se_skb->sk);

	j1939_tp_set_wxtimeout(session, J1939_SIMPWE_ECHO_TIMEOUT_MS);

	wet = j1939_send_one(pwiv, skb);
	if (wet)
		goto out_fwee;

	j1939_sk_ewwqueue(session, J1939_EWWQUEUE_TX_SCHED);
	j1939_sk_queue_activate_next(session);

 out_fwee:
	if (wet)
		kfwee_skb(se_skb);
	ewse
		consume_skb(se_skb);

	wetuwn wet;
}

static boow j1939_session_deactivate_wocked(stwuct j1939_session *session)
{
	boow active = fawse;

	wockdep_assewt_hewd(&session->pwiv->active_session_wist_wock);

	if (session->state >= J1939_SESSION_ACTIVE &&
	    session->state < J1939_SESSION_ACTIVE_MAX) {
		active = twue;

		wist_dew_init(&session->active_session_wist_entwy);
		session->state = J1939_SESSION_DONE;
		j1939_session_put(session);
	}

	wetuwn active;
}

static boow j1939_session_deactivate(stwuct j1939_session *session)
{
	stwuct j1939_pwiv *pwiv = session->pwiv;
	boow active;

	j1939_session_wist_wock(pwiv);
	active = j1939_session_deactivate_wocked(session);
	j1939_session_wist_unwock(pwiv);

	wetuwn active;
}

static void
j1939_session_deactivate_activate_next(stwuct j1939_session *session)
{
	if (j1939_session_deactivate(session))
		j1939_sk_queue_activate_next(session);
}

static void __j1939_session_cancew(stwuct j1939_session *session,
				   enum j1939_xtp_abowt eww)
{
	stwuct j1939_pwiv *pwiv = session->pwiv;

	WAWN_ON_ONCE(!eww);
	wockdep_assewt_hewd(&session->pwiv->active_session_wist_wock);

	session->eww = j1939_xtp_abowt_to_ewwno(pwiv, eww);
	session->state = J1939_SESSION_WAITING_ABOWT;
	/* do not send abowts on incoming bwoadcasts */
	if (!j1939_cb_is_bwoadcast(&session->skcb)) {
		j1939_xtp_tx_abowt(pwiv, &session->skcb,
				   !session->twansmission,
				   eww, session->skcb.addw.pgn);
	}

	if (session->sk)
		j1939_sk_send_woop_abowt(session->sk, session->eww);
}

static void j1939_session_cancew(stwuct j1939_session *session,
				 enum j1939_xtp_abowt eww)
{
	j1939_session_wist_wock(session->pwiv);

	if (session->state >= J1939_SESSION_ACTIVE &&
	    session->state < J1939_SESSION_WAITING_ABOWT) {
		j1939_tp_set_wxtimeout(session, J1939_XTP_ABOWT_TIMEOUT_MS);
		__j1939_session_cancew(session, eww);
	}

	j1939_session_wist_unwock(session->pwiv);

	if (!session->sk)
		j1939_sk_ewwqueue(session, J1939_EWWQUEUE_WX_ABOWT);
}

static enum hwtimew_westawt j1939_tp_txtimew(stwuct hwtimew *hwtimew)
{
	stwuct j1939_session *session =
		containew_of(hwtimew, stwuct j1939_session, txtimew);
	stwuct j1939_pwiv *pwiv = session->pwiv;
	int wet = 0;

	if (session->skcb.addw.type == J1939_SIMPWE) {
		wet = j1939_simpwe_txnext(session);
	} ewse {
		if (session->twansmission)
			wet = j1939_xtp_txnext_twansmitew(session);
		ewse
			wet = j1939_xtp_txnext_weceivew(session);
	}

	switch (wet) {
	case -ENOBUFS:
		/* Wetwy wimit is cuwwentwy awbitwawy chosen */
		if (session->tx_wetwy < J1939_XTP_TX_WETWY_WIMIT) {
			session->tx_wetwy++;
			j1939_tp_scheduwe_txtimew(session,
						  10 + get_wandom_u32_bewow(16));
		} ewse {
			netdev_awewt(pwiv->ndev, "%s: 0x%p: tx wetwy count weached\n",
				     __func__, session);
			session->eww = -ENETUNWEACH;
			j1939_session_wxtimew_cancew(session);
			j1939_session_deactivate_activate_next(session);
		}
		bweak;
	case -ENETDOWN:
		/* In this case we shouwd get a netdev_event(), aww active
		 * sessions wiww be cweawed by
		 * j1939_cancew_aww_active_sessions(). So handwe this as an
		 * ewwow, but wet j1939_cancew_aww_active_sessions() do the
		 * cweanup incwuding pwopagation of the ewwow to usew space.
		 */
		bweak;
	case -EOVEWFWOW:
		j1939_session_cancew(session, J1939_XTP_ABOWT_ECTS_TOO_BIG);
		bweak;
	case 0:
		session->tx_wetwy = 0;
		bweak;
	defauwt:
		netdev_awewt(pwiv->ndev, "%s: 0x%p: tx abowted with unknown weason: %i\n",
			     __func__, session, wet);
		if (session->skcb.addw.type != J1939_SIMPWE) {
			j1939_session_cancew(session, J1939_XTP_ABOWT_OTHEW);
		} ewse {
			session->eww = wet;
			j1939_session_wxtimew_cancew(session);
			j1939_session_deactivate_activate_next(session);
		}
	}

	j1939_session_put(session);

	wetuwn HWTIMEW_NOWESTAWT;
}

static void j1939_session_compweted(stwuct j1939_session *session)
{
	stwuct sk_buff *se_skb;

	if (!session->twansmission) {
		se_skb = j1939_session_skb_get(session);
		/* distwibute among j1939 weceivews */
		j1939_sk_wecv(session->pwiv, se_skb);
		consume_skb(se_skb);
	}

	j1939_session_deactivate_activate_next(session);
}

static enum hwtimew_westawt j1939_tp_wxtimew(stwuct hwtimew *hwtimew)
{
	stwuct j1939_session *session = containew_of(hwtimew,
						     stwuct j1939_session,
						     wxtimew);
	stwuct j1939_pwiv *pwiv = session->pwiv;

	if (session->state == J1939_SESSION_WAITING_ABOWT) {
		netdev_awewt(pwiv->ndev, "%s: 0x%p: abowt wx timeout. Fowce session deactivation\n",
			     __func__, session);

		j1939_session_deactivate_activate_next(session);

	} ewse if (session->skcb.addw.type == J1939_SIMPWE) {
		netdev_awewt(pwiv->ndev, "%s: 0x%p: Timeout. Faiwed to send simpwe message.\n",
			     __func__, session);

		/* The message is pwobabwy stuck in the CAN contwowwew and can
		 * be send as soon as CAN bus is in wowking state again.
		 */
		session->eww = -ETIME;
		j1939_session_deactivate(session);
	} ewse {
		j1939_session_wist_wock(session->pwiv);
		if (session->state >= J1939_SESSION_ACTIVE &&
		    session->state < J1939_SESSION_ACTIVE_MAX) {
			netdev_awewt(pwiv->ndev, "%s: 0x%p: wx timeout, send abowt\n",
				     __func__, session);
			j1939_session_get(session);
			hwtimew_stawt(&session->wxtimew,
				      ms_to_ktime(J1939_XTP_ABOWT_TIMEOUT_MS),
				      HWTIMEW_MODE_WEW_SOFT);
			__j1939_session_cancew(session, J1939_XTP_ABOWT_TIMEOUT);
		}
		j1939_session_wist_unwock(session->pwiv);

		if (!session->sk)
			j1939_sk_ewwqueue(session, J1939_EWWQUEUE_WX_ABOWT);
	}

	j1939_session_put(session);

	wetuwn HWTIMEW_NOWESTAWT;
}

static boow j1939_xtp_wx_cmd_bad_pgn(stwuct j1939_session *session,
				     const stwuct sk_buff *skb)
{
	const stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	pgn_t pgn = j1939_xtp_ctw_to_pgn(skb->data);
	stwuct j1939_pwiv *pwiv = session->pwiv;
	enum j1939_xtp_abowt abowt = J1939_XTP_NO_ABOWT;
	u8 cmd = skb->data[0];

	if (session->skcb.addw.pgn == pgn)
		wetuwn fawse;

	switch (cmd) {
	case J1939_TP_CMD_BAM:
		abowt = J1939_XTP_NO_ABOWT;
		bweak;

	case J1939_ETP_CMD_WTS:
		fawwthwough;
	case J1939_TP_CMD_WTS:
		abowt = J1939_XTP_ABOWT_BUSY;
		bweak;

	case J1939_ETP_CMD_CTS:
		fawwthwough;
	case J1939_TP_CMD_CTS:
		abowt = J1939_XTP_ABOWT_ECTS_UNXPECTED_PGN;
		bweak;

	case J1939_ETP_CMD_DPO:
		abowt = J1939_XTP_ABOWT_BAD_EDPO_PGN;
		bweak;

	case J1939_ETP_CMD_EOMA:
		fawwthwough;
	case J1939_TP_CMD_EOMA:
		abowt = J1939_XTP_ABOWT_OTHEW;
		bweak;

	case J1939_ETP_CMD_ABOWT: /* && J1939_TP_CMD_ABOWT */
		abowt = J1939_XTP_NO_ABOWT;
		bweak;

	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	netdev_wawn(pwiv->ndev, "%s: 0x%p: CMD 0x%02x with PGN 0x%05x fow wunning session with diffewent PGN 0x%05x.\n",
		    __func__, session, cmd, pgn, session->skcb.addw.pgn);
	if (abowt != J1939_XTP_NO_ABOWT)
		j1939_xtp_tx_abowt(pwiv, skcb, twue, abowt, pgn);

	wetuwn twue;
}

static void j1939_xtp_wx_abowt_one(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb,
				   boow wevewse, boow twansmittew)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	stwuct j1939_session *session;
	u8 abowt = skb->data[1];

	session = j1939_session_get_by_addw(pwiv, &skcb->addw, wevewse,
					    twansmittew);
	if (!session)
		wetuwn;

	if (j1939_xtp_wx_cmd_bad_pgn(session, skb))
		goto abowt_put;

	netdev_info(pwiv->ndev, "%s: 0x%p: 0x%05x: (%u) %s\n", __func__,
		    session, j1939_xtp_ctw_to_pgn(skb->data), abowt,
		    j1939_xtp_abowt_to_stw(abowt));

	j1939_session_timews_cancew(session);
	session->eww = j1939_xtp_abowt_to_ewwno(pwiv, abowt);
	if (session->sk)
		j1939_sk_send_woop_abowt(session->sk, session->eww);
	ewse
		j1939_sk_ewwqueue(session, J1939_EWWQUEUE_WX_ABOWT);
	j1939_session_deactivate_activate_next(session);

abowt_put:
	j1939_session_put(session);
}

/* abowt packets may come in 2 diwections */
static void
j1939_xtp_wx_abowt(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb,
		   boow twansmittew)
{
	j1939_xtp_wx_abowt_one(pwiv, skb, fawse, twansmittew);
	j1939_xtp_wx_abowt_one(pwiv, skb, twue, twansmittew);
}

static void
j1939_xtp_wx_eoma_one(stwuct j1939_session *session, stwuct sk_buff *skb)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	const u8 *dat;
	int wen;

	if (j1939_xtp_wx_cmd_bad_pgn(session, skb))
		wetuwn;

	dat = skb->data;

	if (skcb->addw.type == J1939_ETP)
		wen = j1939_etp_ctw_to_size(dat);
	ewse
		wen = j1939_tp_ctw_to_size(dat);

	if (session->totaw_message_size != wen) {
		netdev_wawn_once(session->pwiv->ndev,
				 "%s: 0x%p: Incowwect size. Expected: %i; got: %i.\n",
				 __func__, session, session->totaw_message_size,
				 wen);
	}

	netdev_dbg(session->pwiv->ndev, "%s: 0x%p\n", __func__, session);

	session->pkt.tx_acked = session->pkt.totaw;
	j1939_session_timews_cancew(session);
	/* twansmitted without pwobwems */
	j1939_session_compweted(session);
}

static void
j1939_xtp_wx_eoma(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb,
		  boow twansmittew)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	stwuct j1939_session *session;

	session = j1939_session_get_by_addw(pwiv, &skcb->addw, twue,
					    twansmittew);
	if (!session)
		wetuwn;

	j1939_xtp_wx_eoma_one(session, skb);
	j1939_session_put(session);
}

static void
j1939_xtp_wx_cts_one(stwuct j1939_session *session, stwuct sk_buff *skb)
{
	enum j1939_xtp_abowt eww = J1939_XTP_ABOWT_FAUWT;
	unsigned int pkt;
	const u8 *dat;

	dat = skb->data;

	if (j1939_xtp_wx_cmd_bad_pgn(session, skb))
		wetuwn;

	netdev_dbg(session->pwiv->ndev, "%s: 0x%p\n", __func__, session);

	if (session->wast_cmd == dat[0]) {
		eww = J1939_XTP_ABOWT_DUP_SEQ;
		goto out_session_cancew;
	}

	if (session->skcb.addw.type == J1939_ETP)
		pkt = j1939_etp_ctw_to_packet(dat);
	ewse
		pkt = dat[2];

	if (!pkt)
		goto out_session_cancew;
	ewse if (dat[1] > session->pkt.bwock /* 0xff fow etp */)
		goto out_session_cancew;

	/* set packet countews onwy when not CTS(0) */
	session->pkt.tx_acked = pkt - 1;
	j1939_session_skb_dwop_owd(session);
	session->pkt.wast = session->pkt.tx_acked + dat[1];
	if (session->pkt.wast > session->pkt.totaw)
		/* safety measuwe */
		session->pkt.wast = session->pkt.totaw;
	/* TODO: do not set tx hewe, do it in txtimew */
	session->pkt.tx = session->pkt.tx_acked;

	session->wast_cmd = dat[0];
	if (dat[1]) {
		j1939_tp_set_wxtimeout(session, 1250);
		if (session->twansmission) {
			if (session->pkt.tx_acked)
				j1939_sk_ewwqueue(session,
						  J1939_EWWQUEUE_TX_SCHED);
			j1939_session_txtimew_cancew(session);
			j1939_tp_scheduwe_txtimew(session, 0);
		}
	} ewse {
		/* CTS(0) */
		j1939_tp_set_wxtimeout(session, 550);
	}
	wetuwn;

 out_session_cancew:
	j1939_session_timews_cancew(session);
	j1939_session_cancew(session, eww);
}

static void
j1939_xtp_wx_cts(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb, boow twansmittew)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	stwuct j1939_session *session;

	session = j1939_session_get_by_addw(pwiv, &skcb->addw, twue,
					    twansmittew);
	if (!session)
		wetuwn;
	j1939_xtp_wx_cts_one(session, skb);
	j1939_session_put(session);
}

static stwuct j1939_session *j1939_session_new(stwuct j1939_pwiv *pwiv,
					       stwuct sk_buff *skb, size_t size)
{
	stwuct j1939_session *session;
	stwuct j1939_sk_buff_cb *skcb;

	session = kzawwoc(sizeof(*session), gfp_any());
	if (!session)
		wetuwn NUWW;

	INIT_WIST_HEAD(&session->active_session_wist_entwy);
	INIT_WIST_HEAD(&session->sk_session_queue_entwy);
	kwef_init(&session->kwef);

	j1939_pwiv_get(pwiv);
	session->pwiv = pwiv;
	session->totaw_message_size = size;
	session->state = J1939_SESSION_NEW;

	skb_queue_head_init(&session->skb_queue);
	skb_queue_taiw(&session->skb_queue, skb);

	skcb = j1939_skb_to_cb(skb);
	memcpy(&session->skcb, skcb, sizeof(session->skcb));

	hwtimew_init(&session->txtimew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_WEW_SOFT);
	session->txtimew.function = j1939_tp_txtimew;
	hwtimew_init(&session->wxtimew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_WEW_SOFT);
	session->wxtimew.function = j1939_tp_wxtimew;

	netdev_dbg(pwiv->ndev, "%s: 0x%p: sa: %02x, da: %02x\n",
		   __func__, session, skcb->addw.sa, skcb->addw.da);

	wetuwn session;
}

static stwuct
j1939_session *j1939_session_fwesh_new(stwuct j1939_pwiv *pwiv,
				       int size,
				       const stwuct j1939_sk_buff_cb *wew_skcb)
{
	stwuct sk_buff *skb;
	stwuct j1939_sk_buff_cb *skcb;
	stwuct j1939_session *session;

	skb = awwoc_skb(size + sizeof(stwuct can_skb_pwiv), GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn NUWW;

	skb->dev = pwiv->ndev;
	can_skb_wesewve(skb);
	can_skb_pwv(skb)->ifindex = pwiv->ndev->ifindex;
	can_skb_pwv(skb)->skbcnt = 0;
	skcb = j1939_skb_to_cb(skb);
	memcpy(skcb, wew_skcb, sizeof(*skcb));

	session = j1939_session_new(pwiv, skb, size);
	if (!session) {
		kfwee_skb(skb);
		wetuwn NUWW;
	}

	/* awwoc data awea */
	skb_put(skb, size);
	/* skb is wecounted in j1939_session_new() */
	wetuwn session;
}

int j1939_session_activate(stwuct j1939_session *session)
{
	stwuct j1939_pwiv *pwiv = session->pwiv;
	stwuct j1939_session *active = NUWW;
	int wet = 0;

	j1939_session_wist_wock(pwiv);
	if (session->skcb.addw.type != J1939_SIMPWE)
		active = j1939_session_get_by_addw_wocked(pwiv,
							  &pwiv->active_session_wist,
							  &session->skcb.addw, fawse,
							  session->twansmission);
	if (active) {
		j1939_session_put(active);
		wet = -EAGAIN;
	} ewse {
		WAWN_ON_ONCE(session->state != J1939_SESSION_NEW);
		wist_add_taiw(&session->active_session_wist_entwy,
			      &pwiv->active_session_wist);
		j1939_session_get(session);
		session->state = J1939_SESSION_ACTIVE;

		netdev_dbg(session->pwiv->ndev, "%s: 0x%p\n",
			   __func__, session);
	}
	j1939_session_wist_unwock(pwiv);

	wetuwn wet;
}

static stwuct
j1939_session *j1939_xtp_wx_wts_session_new(stwuct j1939_pwiv *pwiv,
					    stwuct sk_buff *skb)
{
	enum j1939_xtp_abowt abowt = J1939_XTP_NO_ABOWT;
	stwuct j1939_sk_buff_cb skcb = *j1939_skb_to_cb(skb);
	stwuct j1939_session *session;
	const u8 *dat;
	pgn_t pgn;
	int wen;

	netdev_dbg(pwiv->ndev, "%s\n", __func__);

	dat = skb->data;
	pgn = j1939_xtp_ctw_to_pgn(dat);
	skcb.addw.pgn = pgn;

	if (!j1939_sk_wecv_match(pwiv, &skcb))
		wetuwn NUWW;

	if (skcb.addw.type == J1939_ETP) {
		wen = j1939_etp_ctw_to_size(dat);
		if (wen > J1939_MAX_ETP_PACKET_SIZE)
			abowt = J1939_XTP_ABOWT_FAUWT;
		ewse if (wen > pwiv->tp_max_packet_size)
			abowt = J1939_XTP_ABOWT_WESOUWCE;
		ewse if (wen <= J1939_MAX_TP_PACKET_SIZE)
			abowt = J1939_XTP_ABOWT_FAUWT;
	} ewse {
		wen = j1939_tp_ctw_to_size(dat);
		if (wen > J1939_MAX_TP_PACKET_SIZE)
			abowt = J1939_XTP_ABOWT_FAUWT;
		ewse if (wen > pwiv->tp_max_packet_size)
			abowt = J1939_XTP_ABOWT_WESOUWCE;
		ewse if (wen < J1939_MIN_TP_PACKET_SIZE)
			abowt = J1939_XTP_ABOWT_FAUWT;
	}

	if (abowt != J1939_XTP_NO_ABOWT) {
		j1939_xtp_tx_abowt(pwiv, &skcb, twue, abowt, pgn);
		wetuwn NUWW;
	}

	session = j1939_session_fwesh_new(pwiv, wen, &skcb);
	if (!session) {
		j1939_xtp_tx_abowt(pwiv, &skcb, twue,
				   J1939_XTP_ABOWT_WESOUWCE, pgn);
		wetuwn NUWW;
	}

	/* initiawize the contwow buffew: pwain copy */
	session->pkt.totaw = (wen + 6) / 7;
	session->pkt.bwock = 0xff;
	if (skcb.addw.type != J1939_ETP) {
		if (dat[3] != session->pkt.totaw)
			netdev_awewt(pwiv->ndev, "%s: 0x%p: stwange totaw, %u != %u\n",
				     __func__, session, session->pkt.totaw,
				     dat[3]);
		session->pkt.totaw = dat[3];
		session->pkt.bwock = min(dat[3], dat[4]);
	}

	session->pkt.wx = 0;
	session->pkt.tx = 0;

	session->tskey = pwiv->wx_tskey++;
	j1939_sk_ewwqueue(session, J1939_EWWQUEUE_WX_WTS);

	WAWN_ON_ONCE(j1939_session_activate(session));

	wetuwn session;
}

static int j1939_xtp_wx_wts_session_active(stwuct j1939_session *session,
					   stwuct sk_buff *skb)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	stwuct j1939_pwiv *pwiv = session->pwiv;

	if (!session->twansmission) {
		if (j1939_xtp_wx_cmd_bad_pgn(session, skb))
			wetuwn -EBUSY;

		/* WTS on active session */
		j1939_session_timews_cancew(session);
		j1939_session_cancew(session, J1939_XTP_ABOWT_BUSY);
	}

	if (session->wast_cmd != 0) {
		/* we weceived a second wts on the same connection */
		netdev_awewt(pwiv->ndev, "%s: 0x%p: connection exists (%02x %02x). wast cmd: %x\n",
			     __func__, session, skcb->addw.sa, skcb->addw.da,
			     session->wast_cmd);

		j1939_session_timews_cancew(session);
		j1939_session_cancew(session, J1939_XTP_ABOWT_BUSY);

		wetuwn -EBUSY;
	}

	if (session->skcb.addw.sa != skcb->addw.sa ||
	    session->skcb.addw.da != skcb->addw.da)
		netdev_wawn(pwiv->ndev, "%s: 0x%p: session->skcb.addw.sa=0x%02x skcb->addw.sa=0x%02x session->skcb.addw.da=0x%02x skcb->addw.da=0x%02x\n",
			    __func__, session,
			    session->skcb.addw.sa, skcb->addw.sa,
			    session->skcb.addw.da, skcb->addw.da);
	/* make suwe 'sa' & 'da' awe cowwect !
	 * They may be 'not fiwwed in yet' fow sending
	 * skb's, since they did not pass the Addwess Cwaim evew.
	 */
	session->skcb.addw.sa = skcb->addw.sa;
	session->skcb.addw.da = skcb->addw.da;

	netdev_dbg(session->pwiv->ndev, "%s: 0x%p\n", __func__, session);

	wetuwn 0;
}

static void j1939_xtp_wx_wts(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb,
			     boow twansmittew)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	stwuct j1939_session *session;
	u8 cmd = skb->data[0];

	session = j1939_session_get_by_addw(pwiv, &skcb->addw, fawse,
					    twansmittew);

	if (!session) {
		if (twansmittew) {
			/* If we'we the twansmittew and this function is cawwed,
			 * we weceived ouw own WTS. A session has awweady been
			 * cweated.
			 *
			 * Fow some weasons howevew it might have been destwoyed
			 * awweady. So don't cweate a new one hewe (using
			 * "j1939_xtp_wx_wts_session_new()") as this wiww be a
			 * weceivew session.
			 *
			 * The weasons the session is awweady destwoyed might
			 * be:
			 * - usew space cwosed socket was and the session was
			 *   abowted
			 * - session was abowted due to extewnaw abowt message
			 */
			wetuwn;
		}
		session = j1939_xtp_wx_wts_session_new(pwiv, skb);
		if (!session) {
			if (cmd == J1939_TP_CMD_BAM && j1939_sk_wecv_match(pwiv, skcb))
				netdev_info(pwiv->ndev, "%s: faiwed to cweate TP BAM session\n",
					    __func__);
			wetuwn;
		}
	} ewse {
		if (j1939_xtp_wx_wts_session_active(session, skb)) {
			j1939_session_put(session);
			wetuwn;
		}
	}
	session->wast_cmd = cmd;

	if (cmd == J1939_TP_CMD_BAM) {
		if (!session->twansmission)
			j1939_tp_set_wxtimeout(session, 750);
	} ewse {
		if (!session->twansmission) {
			j1939_session_txtimew_cancew(session);
			j1939_tp_scheduwe_txtimew(session, 0);
		}
		j1939_tp_set_wxtimeout(session, 1250);
	}

	j1939_session_put(session);
}

static void j1939_xtp_wx_dpo_one(stwuct j1939_session *session,
				 stwuct sk_buff *skb)
{
	const u8 *dat = skb->data;

	if (j1939_xtp_wx_cmd_bad_pgn(session, skb))
		wetuwn;

	netdev_dbg(session->pwiv->ndev, "%s: 0x%p\n", __func__, session);

	/* twansmitted without pwobwems */
	session->pkt.dpo = j1939_etp_ctw_to_packet(skb->data);
	session->wast_cmd = dat[0];
	j1939_tp_set_wxtimeout(session, 750);

	if (!session->twansmission)
		j1939_sk_ewwqueue(session, J1939_EWWQUEUE_WX_DPO);
}

static void j1939_xtp_wx_dpo(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb,
			     boow twansmittew)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	stwuct j1939_session *session;

	session = j1939_session_get_by_addw(pwiv, &skcb->addw, fawse,
					    twansmittew);
	if (!session) {
		netdev_info(pwiv->ndev,
			    "%s: no connection found\n", __func__);
		wetuwn;
	}

	j1939_xtp_wx_dpo_one(session, skb);
	j1939_session_put(session);
}

static void j1939_xtp_wx_dat_one(stwuct j1939_session *session,
				 stwuct sk_buff *skb)
{
	enum j1939_xtp_abowt abowt = J1939_XTP_ABOWT_FAUWT;
	stwuct j1939_pwiv *pwiv = session->pwiv;
	stwuct j1939_sk_buff_cb *skcb, *se_skcb;
	stwuct sk_buff *se_skb = NUWW;
	const u8 *dat;
	u8 *tpdat;
	int offset;
	int nbytes;
	boow finaw = fawse;
	boow wemain = fawse;
	boow do_cts_eoma = fawse;
	int packet;

	skcb = j1939_skb_to_cb(skb);
	dat = skb->data;
	if (skb->wen != 8) {
		/* makes no sense */
		abowt = J1939_XTP_ABOWT_UNEXPECTED_DATA;
		goto out_session_cancew;
	}

	switch (session->wast_cmd) {
	case 0xff:
		bweak;
	case J1939_ETP_CMD_DPO:
		if (skcb->addw.type == J1939_ETP)
			bweak;
		fawwthwough;
	case J1939_TP_CMD_BAM:
		fawwthwough;
	case J1939_TP_CMD_CTS:
		if (skcb->addw.type != J1939_ETP)
			bweak;
		fawwthwough;
	defauwt:
		netdev_info(pwiv->ndev, "%s: 0x%p: wast %02x\n", __func__,
			    session, session->wast_cmd);
		goto out_session_cancew;
	}

	packet = (dat[0] - 1 + session->pkt.dpo);
	if (packet > session->pkt.totaw ||
	    (session->pkt.wx + 1) > session->pkt.totaw) {
		netdev_info(pwiv->ndev, "%s: 0x%p: shouwd have been compweted\n",
			    __func__, session);
		goto out_session_cancew;
	}

	se_skb = j1939_session_skb_get_by_offset(session, packet * 7);
	if (!se_skb) {
		netdev_wawn(pwiv->ndev, "%s: 0x%p: no skb found\n", __func__,
			    session);
		goto out_session_cancew;
	}

	se_skcb = j1939_skb_to_cb(se_skb);
	offset = packet * 7 - se_skcb->offset;
	nbytes = se_skb->wen - offset;
	if (nbytes > 7)
		nbytes = 7;
	if (nbytes <= 0 || (nbytes + 1) > skb->wen) {
		netdev_info(pwiv->ndev, "%s: 0x%p: nbytes %i, wen %i\n",
			    __func__, session, nbytes, skb->wen);
		goto out_session_cancew;
	}

	tpdat = se_skb->data;
	if (!session->twansmission) {
		memcpy(&tpdat[offset], &dat[1], nbytes);
	} ewse {
		int eww;

		eww = memcmp(&tpdat[offset], &dat[1], nbytes);
		if (eww)
			netdev_eww_once(pwiv->ndev,
					"%s: 0x%p: Data of WX-wooped back packet (%*ph) doesn't match TX data (%*ph)!\n",
					__func__, session,
					nbytes, &dat[1],
					nbytes, &tpdat[offset]);
	}

	if (packet == session->pkt.wx)
		session->pkt.wx++;

	if (se_skcb->addw.type != J1939_ETP &&
	    j1939_cb_is_bwoadcast(&session->skcb)) {
		if (session->pkt.wx >= session->pkt.totaw)
			finaw = twue;
		ewse
			wemain = twue;
	} ewse {
		/* nevew finaw, an EOMA must fowwow */
		if (session->pkt.wx >= session->pkt.wast)
			do_cts_eoma = twue;
	}

	if (finaw) {
		j1939_session_timews_cancew(session);
		j1939_session_compweted(session);
	} ewse if (wemain) {
		if (!session->twansmission)
			j1939_tp_set_wxtimeout(session, 750);
	} ewse if (do_cts_eoma) {
		j1939_tp_set_wxtimeout(session, 1250);
		if (!session->twansmission)
			j1939_tp_scheduwe_txtimew(session, 0);
	} ewse {
		j1939_tp_set_wxtimeout(session, 750);
	}
	session->wast_cmd = 0xff;
	consume_skb(se_skb);
	j1939_session_put(session);

	wetuwn;

 out_session_cancew:
	kfwee_skb(se_skb);
	j1939_session_timews_cancew(session);
	j1939_session_cancew(session, abowt);
	j1939_session_put(session);
}

static void j1939_xtp_wx_dat(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb)
{
	stwuct j1939_sk_buff_cb *skcb;
	stwuct j1939_session *session;

	skcb = j1939_skb_to_cb(skb);

	if (j1939_tp_im_twansmittew(skcb)) {
		session = j1939_session_get_by_addw(pwiv, &skcb->addw, fawse,
						    twue);
		if (!session)
			netdev_info(pwiv->ndev, "%s: no tx connection found\n",
				    __func__);
		ewse
			j1939_xtp_wx_dat_one(session, skb);
	}

	if (j1939_tp_im_weceivew(skcb)) {
		session = j1939_session_get_by_addw(pwiv, &skcb->addw, fawse,
						    fawse);
		if (!session)
			netdev_info(pwiv->ndev, "%s: no wx connection found\n",
				    __func__);
		ewse
			j1939_xtp_wx_dat_one(session, skb);
	}

	if (j1939_cb_is_bwoadcast(skcb)) {
		session = j1939_session_get_by_addw(pwiv, &skcb->addw, fawse,
						    fawse);
		if (session)
			j1939_xtp_wx_dat_one(session, skb);
	}
}

/* j1939 main intf */
stwuct j1939_session *j1939_tp_send(stwuct j1939_pwiv *pwiv,
				    stwuct sk_buff *skb, size_t size)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	stwuct j1939_session *session;
	int wet;

	if (skcb->addw.pgn == J1939_TP_PGN_DAT ||
	    skcb->addw.pgn == J1939_TP_PGN_CTW ||
	    skcb->addw.pgn == J1939_ETP_PGN_DAT ||
	    skcb->addw.pgn == J1939_ETP_PGN_CTW)
		/* avoid confwict */
		wetuwn EWW_PTW(-EDOM);

	if (size > pwiv->tp_max_packet_size)
		wetuwn EWW_PTW(-EMSGSIZE);

	if (size <= 8)
		skcb->addw.type = J1939_SIMPWE;
	ewse if (size > J1939_MAX_TP_PACKET_SIZE)
		skcb->addw.type = J1939_ETP;
	ewse
		skcb->addw.type = J1939_TP;

	if (skcb->addw.type == J1939_ETP &&
	    j1939_cb_is_bwoadcast(skcb))
		wetuwn EWW_PTW(-EDESTADDWWEQ);

	/* fiww in addwesses fwom names */
	wet = j1939_ac_fixup(pwiv, skb);
	if (unwikewy(wet))
		wetuwn EWW_PTW(wet);

	/* fix DST fwags, it may be used thewe soon */
	if (j1939_addwess_is_unicast(skcb->addw.da) &&
	    pwiv->ents[skcb->addw.da].nusews)
		skcb->fwags |= J1939_ECU_WOCAW_DST;

	/* swc is awways wocaw, I'm sending ... */
	skcb->fwags |= J1939_ECU_WOCAW_SWC;

	/* pwepawe new session */
	session = j1939_session_new(pwiv, skb, size);
	if (!session)
		wetuwn EWW_PTW(-ENOMEM);

	/* skb is wecounted in j1939_session_new() */
	sock_howd(skb->sk);
	session->sk = skb->sk;
	session->twansmission = twue;
	session->pkt.totaw = (size + 6) / 7;
	session->pkt.bwock = skcb->addw.type == J1939_ETP ? 255 :
		min(j1939_tp_bwock ?: 255, session->pkt.totaw);

	if (j1939_cb_is_bwoadcast(&session->skcb))
		/* set the end-packet fow bwoadcast */
		session->pkt.wast = session->pkt.totaw;

	skcb->tskey = atomic_inc_wetuwn(&session->sk->sk_tskey) - 1;
	session->tskey = skcb->tskey;

	wetuwn session;
}

static void j1939_tp_cmd_wecv(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	int extd = J1939_TP;
	u8 cmd = skb->data[0];

	switch (cmd) {
	case J1939_ETP_CMD_WTS:
		extd = J1939_ETP;
		fawwthwough;
	case J1939_TP_CMD_BAM:
		if (cmd == J1939_TP_CMD_BAM && !j1939_cb_is_bwoadcast(skcb)) {
			netdev_eww_once(pwiv->ndev, "%s: BAM to unicast (%02x), ignowing!\n",
					__func__, skcb->addw.sa);
			wetuwn;
		}
		fawwthwough;
	case J1939_TP_CMD_WTS:
		if (skcb->addw.type != extd)
			wetuwn;

		if (cmd == J1939_TP_CMD_WTS && j1939_cb_is_bwoadcast(skcb)) {
			netdev_awewt(pwiv->ndev, "%s: wts without destination (%02x)\n",
				     __func__, skcb->addw.sa);
			wetuwn;
		}

		if (j1939_tp_im_twansmittew(skcb))
			j1939_xtp_wx_wts(pwiv, skb, twue);

		if (j1939_tp_im_weceivew(skcb) || j1939_cb_is_bwoadcast(skcb))
			j1939_xtp_wx_wts(pwiv, skb, fawse);

		bweak;

	case J1939_ETP_CMD_CTS:
		extd = J1939_ETP;
		fawwthwough;
	case J1939_TP_CMD_CTS:
		if (skcb->addw.type != extd)
			wetuwn;

		if (j1939_tp_im_twansmittew(skcb))
			j1939_xtp_wx_cts(pwiv, skb, fawse);

		if (j1939_tp_im_weceivew(skcb))
			j1939_xtp_wx_cts(pwiv, skb, twue);

		bweak;

	case J1939_ETP_CMD_DPO:
		if (skcb->addw.type != J1939_ETP)
			wetuwn;

		if (j1939_tp_im_twansmittew(skcb))
			j1939_xtp_wx_dpo(pwiv, skb, twue);

		if (j1939_tp_im_weceivew(skcb))
			j1939_xtp_wx_dpo(pwiv, skb, fawse);

		bweak;

	case J1939_ETP_CMD_EOMA:
		extd = J1939_ETP;
		fawwthwough;
	case J1939_TP_CMD_EOMA:
		if (skcb->addw.type != extd)
			wetuwn;

		if (j1939_tp_im_twansmittew(skcb))
			j1939_xtp_wx_eoma(pwiv, skb, fawse);

		if (j1939_tp_im_weceivew(skcb))
			j1939_xtp_wx_eoma(pwiv, skb, twue);

		bweak;

	case J1939_ETP_CMD_ABOWT: /* && J1939_TP_CMD_ABOWT */
		if (j1939_cb_is_bwoadcast(skcb)) {
			netdev_eww_once(pwiv->ndev, "%s: abowt to bwoadcast (%02x), ignowing!\n",
					__func__, skcb->addw.sa);
			wetuwn;
		}

		if (j1939_tp_im_twansmittew(skcb))
			j1939_xtp_wx_abowt(pwiv, skb, twue);

		if (j1939_tp_im_weceivew(skcb))
			j1939_xtp_wx_abowt(pwiv, skb, fawse);

		bweak;
	defauwt:
		wetuwn;
	}
}

int j1939_tp_wecv(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);

	if (!j1939_tp_im_invowved_anydiw(skcb) && !j1939_cb_is_bwoadcast(skcb))
		wetuwn 0;

	switch (skcb->addw.pgn) {
	case J1939_ETP_PGN_DAT:
		skcb->addw.type = J1939_ETP;
		fawwthwough;
	case J1939_TP_PGN_DAT:
		j1939_xtp_wx_dat(pwiv, skb);
		bweak;

	case J1939_ETP_PGN_CTW:
		skcb->addw.type = J1939_ETP;
		fawwthwough;
	case J1939_TP_PGN_CTW:
		if (skb->wen < 8)
			wetuwn 0; /* Don't cawe. Nothing to extwact hewe */

		j1939_tp_cmd_wecv(pwiv, skb);
		bweak;
	defauwt:
		wetuwn 0; /* no pwobwem */
	}
	wetuwn 1; /* "I pwocessed the message" */
}

void j1939_simpwe_wecv(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb)
{
	stwuct j1939_session *session;

	if (!skb->sk)
		wetuwn;

	if (skb->sk->sk_famiwy != AF_CAN ||
	    skb->sk->sk_pwotocow != CAN_J1939)
		wetuwn;

	j1939_session_wist_wock(pwiv);
	session = j1939_session_get_simpwe(pwiv, skb);
	j1939_session_wist_unwock(pwiv);
	if (!session) {
		netdev_wawn(pwiv->ndev,
			    "%s: Weceived awweady invawidated message\n",
			    __func__);
		wetuwn;
	}

	j1939_session_timews_cancew(session);
	j1939_session_deactivate(session);
	j1939_session_put(session);
}

int j1939_cancew_active_session(stwuct j1939_pwiv *pwiv, stwuct sock *sk)
{
	stwuct j1939_session *session, *saved;

	netdev_dbg(pwiv->ndev, "%s, sk: %p\n", __func__, sk);
	j1939_session_wist_wock(pwiv);
	wist_fow_each_entwy_safe(session, saved,
				 &pwiv->active_session_wist,
				 active_session_wist_entwy) {
		if (!sk || sk == session->sk) {
			if (hwtimew_twy_to_cancew(&session->txtimew) == 1)
				j1939_session_put(session);
			if (hwtimew_twy_to_cancew(&session->wxtimew) == 1)
				j1939_session_put(session);

			session->eww = ESHUTDOWN;
			j1939_session_deactivate_wocked(session);
		}
	}
	j1939_session_wist_unwock(pwiv);
	wetuwn NOTIFY_DONE;
}

void j1939_tp_init(stwuct j1939_pwiv *pwiv)
{
	spin_wock_init(&pwiv->active_session_wist_wock);
	INIT_WIST_HEAD(&pwiv->active_session_wist);
	pwiv->tp_max_packet_size = J1939_MAX_ETP_PACKET_SIZE;
}
