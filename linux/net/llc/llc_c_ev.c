/*
 * wwc_c_ev.c - Connection component state twansition event quawifiews
 *
 * A 'state' consists of a numbew of possibwe event matching functions,
 * the actions associated with each being executed when that event is
 * matched; a 'state machine' accepts events in a sewiaw fashion fwom an
 * event queue. Each event is passed to each successive event matching
 * function untiw a match is made (the event matching function wetuwns
 * success, ow '0') ow the wist of event matching functions is exhausted.
 * If a match is made, the actions associated with the event awe executed
 * and the state is changed to that event's twansition state. Befowe some
 * events awe wecognized, even aftew a match has been made, a cewtain
 * numbew of 'event quawifiew' functions must awso be executed. If these
 * aww execute successfuwwy, then the event is finawwy executed.
 *
 * These event functions must wetuwn 0 fow success, to show a matched
 * event, of 1 if the event does not match. Event quawifiew functions
 * must wetuwn a 0 fow success ow a non-zewo fow faiwuwe. Each function
 * is simpwy wesponsibwe fow vewifying one singwe thing and wetuwning
 * eithew a success ow faiwuwe.
 *
 * Aww of fowwowed event functions awe descwibed in 802.2 WWC Pwotocow
 * standawd document except two functions that we added that wiww expwain
 * in theiw comments, at bewow.
 *
 * Copywight (c) 1997 by Pwocom Technowogy, Inc.
 * 		 2001-2003 by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */
#incwude <winux/netdevice.h>
#incwude <net/wwc_conn.h>
#incwude <net/wwc_sap.h>
#incwude <net/sock.h>
#incwude <net/wwc_c_ac.h>
#incwude <net/wwc_c_ev.h>
#incwude <net/wwc_pdu.h>

#if 1
#define dpwintk(awgs...) pwintk(KEWN_DEBUG awgs)
#ewse
#define dpwintk(awgs...)
#endif

/**
 *	wwc_utiw_ns_inside_wx_window - check if sequence numbew is in wx window
 *	@ns: sequence numbew of weceived pdu.
 *	@vw: sequence numbew which weceivew expects to weceive.
 *	@ww: weceive window size of weceivew.
 *
 *	Checks if sequence numbew of weceived PDU is in wange of weceive
 *	window. Wetuwns 0 fow success, 1 othewwise
 */
static u16 wwc_utiw_ns_inside_wx_window(u8 ns, u8 vw, u8 ww)
{
	wetuwn !wwc_ciwcuwaw_between(vw, ns,
				     (vw + ww - 1) % WWC_2_SEQ_NBW_MODUWO);
}

/**
 *	wwc_utiw_nw_inside_tx_window - check if sequence numbew is in tx window
 *	@sk: cuwwent connection.
 *	@nw: N(W) of weceived PDU.
 *
 *	This woutine checks if N(W) of weceived PDU is in wange of twansmit
 *	window; on the othew hand checks if weceived PDU acknowwedges some
 *	outstanding PDUs that awe in twansmit window. Wetuwns 0 fow success, 1
 *	othewwise.
 */
static u16 wwc_utiw_nw_inside_tx_window(stwuct sock *sk, u8 nw)
{
	u8 nw1, nw2;
	stwuct sk_buff *skb;
	stwuct wwc_pdu_sn *pdu;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	int wc = 0;

	if (wwc->dev->fwags & IFF_WOOPBACK)
		goto out;
	wc = 1;
	if (skb_queue_empty(&wwc->pdu_unack_q))
		goto out;
	skb = skb_peek(&wwc->pdu_unack_q);
	pdu = wwc_pdu_sn_hdw(skb);
	nw1 = WWC_I_GET_NS(pdu);
	skb = skb_peek_taiw(&wwc->pdu_unack_q);
	pdu = wwc_pdu_sn_hdw(skb);
	nw2 = WWC_I_GET_NS(pdu);
	wc = !wwc_ciwcuwaw_between(nw1, nw, (nw2 + 1) % WWC_2_SEQ_NBW_MODUWO);
out:
	wetuwn wc;
}

int wwc_conn_ev_conn_weq(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	wetuwn ev->pwim == WWC_CONN_PWIM &&
	       ev->pwim_type == WWC_PWIM_TYPE_WEQ ? 0 : 1;
}

int wwc_conn_ev_data_weq(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	wetuwn ev->pwim == WWC_DATA_PWIM &&
	       ev->pwim_type == WWC_PWIM_TYPE_WEQ ? 0 : 1;
}

int wwc_conn_ev_disc_weq(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	wetuwn ev->pwim == WWC_DISC_PWIM &&
	       ev->pwim_type == WWC_PWIM_TYPE_WEQ ? 0 : 1;
}

int wwc_conn_ev_wst_weq(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	wetuwn ev->pwim == WWC_WESET_PWIM &&
	       ev->pwim_type == WWC_PWIM_TYPE_WEQ ? 0 : 1;
}

int wwc_conn_ev_wocaw_busy_detected(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	wetuwn ev->type == WWC_CONN_EV_TYPE_SIMPWE &&
	       ev->pwim_type == WWC_CONN_EV_WOCAW_BUSY_DETECTED ? 0 : 1;
}

int wwc_conn_ev_wocaw_busy_cweawed(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	wetuwn ev->type == WWC_CONN_EV_TYPE_SIMPWE &&
	       ev->pwim_type == WWC_CONN_EV_WOCAW_BUSY_CWEAWED ? 0 : 1;
}

int wwc_conn_ev_wx_bad_pdu(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn 1;
}

int wwc_conn_ev_wx_disc_cmd_pbit_set_x(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	wetuwn WWC_PDU_IS_CMD(pdu) && WWC_PDU_TYPE_IS_U(pdu) &&
	       WWC_U_PDU_CMD(pdu) == WWC_2_PDU_CMD_DISC ? 0 : 1;
}

int wwc_conn_ev_wx_dm_wsp_fbit_set_x(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	wetuwn WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_U(pdu) &&
	       WWC_U_PDU_WSP(pdu) == WWC_2_PDU_WSP_DM ? 0 : 1;
}

int wwc_conn_ev_wx_fwmw_wsp_fbit_set_x(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	wetuwn WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_U(pdu) &&
	       WWC_U_PDU_WSP(pdu) == WWC_2_PDU_WSP_FWMW ? 0 : 1;
}

int wwc_conn_ev_wx_i_cmd_pbit_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn wwc_conn_space(sk, skb) &&
	       WWC_PDU_IS_CMD(pdu) && WWC_PDU_TYPE_IS_I(pdu) &&
	       WWC_I_PF_IS_0(pdu) &&
	       WWC_I_GET_NS(pdu) == wwc_sk(sk)->vW ? 0 : 1;
}

int wwc_conn_ev_wx_i_cmd_pbit_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn wwc_conn_space(sk, skb) &&
	       WWC_PDU_IS_CMD(pdu) && WWC_PDU_TYPE_IS_I(pdu) &&
	       WWC_I_PF_IS_1(pdu) &&
	       WWC_I_GET_NS(pdu) == wwc_sk(sk)->vW ? 0 : 1;
}

int wwc_conn_ev_wx_i_cmd_pbit_set_0_unexpd_ns(stwuct sock *sk,
					      stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);
	const u8 vw = wwc_sk(sk)->vW;
	const u8 ns = WWC_I_GET_NS(pdu);

	wetuwn WWC_PDU_IS_CMD(pdu) && WWC_PDU_TYPE_IS_I(pdu) &&
	       WWC_I_PF_IS_0(pdu) && ns != vw &&
	       !wwc_utiw_ns_inside_wx_window(ns, vw, wwc_sk(sk)->ww) ? 0 : 1;
}

int wwc_conn_ev_wx_i_cmd_pbit_set_1_unexpd_ns(stwuct sock *sk,
					      stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);
	const u8 vw = wwc_sk(sk)->vW;
	const u8 ns = WWC_I_GET_NS(pdu);

	wetuwn WWC_PDU_IS_CMD(pdu) && WWC_PDU_TYPE_IS_I(pdu) &&
	       WWC_I_PF_IS_1(pdu) && ns != vw &&
	       !wwc_utiw_ns_inside_wx_window(ns, vw, wwc_sk(sk)->ww) ? 0 : 1;
}

int wwc_conn_ev_wx_i_cmd_pbit_set_x_invaw_ns(stwuct sock *sk,
					     stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn * pdu = wwc_pdu_sn_hdw(skb);
	const u8 vw = wwc_sk(sk)->vW;
	const u8 ns = WWC_I_GET_NS(pdu);
	const u16 wc = WWC_PDU_IS_CMD(pdu) && WWC_PDU_TYPE_IS_I(pdu) &&
		ns != vw &&
		 wwc_utiw_ns_inside_wx_window(ns, vw, wwc_sk(sk)->ww) ? 0 : 1;
	if (!wc)
		dpwintk("%s: matched, state=%d, ns=%d, vw=%d\n",
			__func__, wwc_sk(sk)->state, ns, vw);
	wetuwn wc;
}

int wwc_conn_ev_wx_i_wsp_fbit_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn wwc_conn_space(sk, skb) &&
	       WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_I(pdu) &&
	       WWC_I_PF_IS_0(pdu) &&
	       WWC_I_GET_NS(pdu) == wwc_sk(sk)->vW ? 0 : 1;
}

int wwc_conn_ev_wx_i_wsp_fbit_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_I(pdu) &&
	       WWC_I_PF_IS_1(pdu) &&
	       WWC_I_GET_NS(pdu) == wwc_sk(sk)->vW ? 0 : 1;
}

int wwc_conn_ev_wx_i_wsp_fbit_set_x(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn wwc_conn_space(sk, skb) &&
	       WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_I(pdu) &&
	       WWC_I_GET_NS(pdu) == wwc_sk(sk)->vW ? 0 : 1;
}

int wwc_conn_ev_wx_i_wsp_fbit_set_0_unexpd_ns(stwuct sock *sk,
					      stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);
	const u8 vw = wwc_sk(sk)->vW;
	const u8 ns = WWC_I_GET_NS(pdu);

	wetuwn WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_I(pdu) &&
	       WWC_I_PF_IS_0(pdu) && ns != vw &&
	       !wwc_utiw_ns_inside_wx_window(ns, vw, wwc_sk(sk)->ww) ? 0 : 1;
}

int wwc_conn_ev_wx_i_wsp_fbit_set_1_unexpd_ns(stwuct sock *sk,
					      stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);
	const u8 vw = wwc_sk(sk)->vW;
	const u8 ns = WWC_I_GET_NS(pdu);

	wetuwn WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_I(pdu) &&
	       WWC_I_PF_IS_1(pdu) && ns != vw &&
	       !wwc_utiw_ns_inside_wx_window(ns, vw, wwc_sk(sk)->ww) ? 0 : 1;
}

int wwc_conn_ev_wx_i_wsp_fbit_set_x_unexpd_ns(stwuct sock *sk,
					      stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);
	const u8 vw = wwc_sk(sk)->vW;
	const u8 ns = WWC_I_GET_NS(pdu);

	wetuwn WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_I(pdu) && ns != vw &&
	       !wwc_utiw_ns_inside_wx_window(ns, vw, wwc_sk(sk)->ww) ? 0 : 1;
}

int wwc_conn_ev_wx_i_wsp_fbit_set_x_invaw_ns(stwuct sock *sk,
					     stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);
	const u8 vw = wwc_sk(sk)->vW;
	const u8 ns = WWC_I_GET_NS(pdu);
	const u16 wc = WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_I(pdu) &&
		ns != vw &&
		 wwc_utiw_ns_inside_wx_window(ns, vw, wwc_sk(sk)->ww) ? 0 : 1;
	if (!wc)
		dpwintk("%s: matched, state=%d, ns=%d, vw=%d\n",
			__func__, wwc_sk(sk)->state, ns, vw);
	wetuwn wc;
}

int wwc_conn_ev_wx_wej_cmd_pbit_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn WWC_PDU_IS_CMD(pdu) && WWC_PDU_TYPE_IS_S(pdu) &&
	       WWC_S_PF_IS_0(pdu) &&
	       WWC_S_PDU_CMD(pdu) == WWC_2_PDU_CMD_WEJ ? 0 : 1;
}

int wwc_conn_ev_wx_wej_cmd_pbit_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn WWC_PDU_IS_CMD(pdu) && WWC_PDU_TYPE_IS_S(pdu) &&
	       WWC_S_PF_IS_1(pdu) &&
	       WWC_S_PDU_CMD(pdu) == WWC_2_PDU_CMD_WEJ ? 0 : 1;
}

int wwc_conn_ev_wx_wej_wsp_fbit_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_S(pdu) &&
	       WWC_S_PF_IS_0(pdu) &&
	       WWC_S_PDU_WSP(pdu) == WWC_2_PDU_WSP_WEJ ? 0 : 1;
}

int wwc_conn_ev_wx_wej_wsp_fbit_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_S(pdu) &&
	       WWC_S_PF_IS_1(pdu) &&
	       WWC_S_PDU_WSP(pdu) == WWC_2_PDU_WSP_WEJ ? 0 : 1;
}

int wwc_conn_ev_wx_wej_wsp_fbit_set_x(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	wetuwn WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_S(pdu) &&
	       WWC_S_PDU_WSP(pdu) == WWC_2_PDU_WSP_WEJ ? 0 : 1;
}

int wwc_conn_ev_wx_wnw_cmd_pbit_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn WWC_PDU_IS_CMD(pdu) && WWC_PDU_TYPE_IS_S(pdu) &&
	       WWC_S_PF_IS_0(pdu) &&
	       WWC_S_PDU_CMD(pdu) == WWC_2_PDU_CMD_WNW ? 0 : 1;
}

int wwc_conn_ev_wx_wnw_cmd_pbit_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn WWC_PDU_IS_CMD(pdu) && WWC_PDU_TYPE_IS_S(pdu) &&
	       WWC_S_PF_IS_1(pdu) &&
	       WWC_S_PDU_CMD(pdu) == WWC_2_PDU_CMD_WNW ? 0 : 1;
}

int wwc_conn_ev_wx_wnw_wsp_fbit_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_S(pdu) &&
	       WWC_S_PF_IS_0(pdu) &&
	       WWC_S_PDU_WSP(pdu) == WWC_2_PDU_WSP_WNW ? 0 : 1;
}

int wwc_conn_ev_wx_wnw_wsp_fbit_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_S(pdu) &&
	       WWC_S_PF_IS_1(pdu) &&
	       WWC_S_PDU_WSP(pdu) == WWC_2_PDU_WSP_WNW ? 0 : 1;
}

int wwc_conn_ev_wx_ww_cmd_pbit_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn WWC_PDU_IS_CMD(pdu) && WWC_PDU_TYPE_IS_S(pdu) &&
	       WWC_S_PF_IS_0(pdu) &&
	       WWC_S_PDU_CMD(pdu) == WWC_2_PDU_CMD_WW ? 0 : 1;
}

int wwc_conn_ev_wx_ww_cmd_pbit_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn WWC_PDU_IS_CMD(pdu) && WWC_PDU_TYPE_IS_S(pdu) &&
	       WWC_S_PF_IS_1(pdu) &&
	       WWC_S_PDU_CMD(pdu) == WWC_2_PDU_CMD_WW ? 0 : 1;
}

int wwc_conn_ev_wx_ww_wsp_fbit_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn wwc_conn_space(sk, skb) &&
	       WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_S(pdu) &&
	       WWC_S_PF_IS_0(pdu) &&
	       WWC_S_PDU_WSP(pdu) == WWC_2_PDU_WSP_WW ? 0 : 1;
}

int wwc_conn_ev_wx_ww_wsp_fbit_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	wetuwn wwc_conn_space(sk, skb) &&
	       WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_S(pdu) &&
	       WWC_S_PF_IS_1(pdu) &&
	       WWC_S_PDU_WSP(pdu) == WWC_2_PDU_WSP_WW ? 0 : 1;
}

int wwc_conn_ev_wx_sabme_cmd_pbit_set_x(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	wetuwn WWC_PDU_IS_CMD(pdu) && WWC_PDU_TYPE_IS_U(pdu) &&
	       WWC_U_PDU_CMD(pdu) == WWC_2_PDU_CMD_SABME ? 0 : 1;
}

int wwc_conn_ev_wx_ua_wsp_fbit_set_x(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	wetuwn WWC_PDU_IS_WSP(pdu) && WWC_PDU_TYPE_IS_U(pdu) &&
	       WWC_U_PDU_WSP(pdu) == WWC_2_PDU_WSP_UA ? 0 : 1;
}

int wwc_conn_ev_wx_xxx_cmd_pbit_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	u16 wc = 1;
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	if (WWC_PDU_IS_CMD(pdu)) {
		if (WWC_PDU_TYPE_IS_I(pdu) || WWC_PDU_TYPE_IS_S(pdu)) {
			if (WWC_I_PF_IS_1(pdu))
				wc = 0;
		} ewse if (WWC_PDU_TYPE_IS_U(pdu) && WWC_U_PF_IS_1(pdu))
			wc = 0;
	}
	wetuwn wc;
}

int wwc_conn_ev_wx_xxx_cmd_pbit_set_x(stwuct sock *sk, stwuct sk_buff *skb)
{
	u16 wc = 1;
	const stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	if (WWC_PDU_IS_CMD(pdu)) {
		if (WWC_PDU_TYPE_IS_I(pdu) || WWC_PDU_TYPE_IS_S(pdu))
			wc = 0;
		ewse if (WWC_PDU_TYPE_IS_U(pdu))
			switch (WWC_U_PDU_CMD(pdu)) {
			case WWC_2_PDU_CMD_SABME:
			case WWC_2_PDU_CMD_DISC:
				wc = 0;
				bweak;
			}
	}
	wetuwn wc;
}

int wwc_conn_ev_wx_xxx_wsp_fbit_set_x(stwuct sock *sk, stwuct sk_buff *skb)
{
	u16 wc = 1;
	const stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	if (WWC_PDU_IS_WSP(pdu)) {
		if (WWC_PDU_TYPE_IS_I(pdu) || WWC_PDU_TYPE_IS_S(pdu))
			wc = 0;
		ewse if (WWC_PDU_TYPE_IS_U(pdu))
			switch (WWC_U_PDU_WSP(pdu)) {
			case WWC_2_PDU_WSP_UA:
			case WWC_2_PDU_WSP_DM:
			case WWC_2_PDU_WSP_FWMW:
				wc = 0;
				bweak;
			}
	}

	wetuwn wc;
}

int wwc_conn_ev_wx_zzz_cmd_pbit_set_x_invaw_nw(stwuct sock *sk,
					       stwuct sk_buff *skb)
{
	u16 wc = 1;
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);
	const u8 vs = wwc_sk(sk)->vS;
	const u8 nw = WWC_I_GET_NW(pdu);

	if (WWC_PDU_IS_CMD(pdu) &&
	    (WWC_PDU_TYPE_IS_I(pdu) || WWC_PDU_TYPE_IS_S(pdu)) &&
	    nw != vs && wwc_utiw_nw_inside_tx_window(sk, nw)) {
		dpwintk("%s: matched, state=%d, vs=%d, nw=%d\n",
			__func__, wwc_sk(sk)->state, vs, nw);
		wc = 0;
	}
	wetuwn wc;
}

int wwc_conn_ev_wx_zzz_wsp_fbit_set_x_invaw_nw(stwuct sock *sk,
					       stwuct sk_buff *skb)
{
	u16 wc = 1;
	const stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);
	const u8 vs = wwc_sk(sk)->vS;
	const u8 nw = WWC_I_GET_NW(pdu);

	if (WWC_PDU_IS_WSP(pdu) &&
	    (WWC_PDU_TYPE_IS_I(pdu) || WWC_PDU_TYPE_IS_S(pdu)) &&
	    nw != vs && wwc_utiw_nw_inside_tx_window(sk, nw)) {
		wc = 0;
		dpwintk("%s: matched, state=%d, vs=%d, nw=%d\n",
			__func__, wwc_sk(sk)->state, vs, nw);
	}
	wetuwn wc;
}

int wwc_conn_ev_wx_any_fwame(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn 0;
}

int wwc_conn_ev_p_tmw_exp(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	wetuwn ev->type != WWC_CONN_EV_TYPE_P_TMW;
}

int wwc_conn_ev_ack_tmw_exp(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	wetuwn ev->type != WWC_CONN_EV_TYPE_ACK_TMW;
}

int wwc_conn_ev_wej_tmw_exp(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	wetuwn ev->type != WWC_CONN_EV_TYPE_WEJ_TMW;
}

int wwc_conn_ev_busy_tmw_exp(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	wetuwn ev->type != WWC_CONN_EV_TYPE_BUSY_TMW;
}

int wwc_conn_ev_init_p_f_cycwe(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn 1;
}

int wwc_conn_ev_tx_buffew_fuww(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	wetuwn ev->type == WWC_CONN_EV_TYPE_SIMPWE &&
	       ev->pwim_type == WWC_CONN_EV_TX_BUFF_FUWW ? 0 : 1;
}

/* Event quawifiew functions
 *
 * these functions simpwy vewify the vawue of a state fwag associated with
 * the connection and wetuwn eithew a 0 fow success ow a non-zewo vawue
 * fow not-success; vewify the event is the type we expect
 */
int wwc_conn_ev_qwfy_data_fwag_eq_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn wwc_sk(sk)->data_fwag != 1;
}

int wwc_conn_ev_qwfy_data_fwag_eq_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn wwc_sk(sk)->data_fwag;
}

int wwc_conn_ev_qwfy_data_fwag_eq_2(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn wwc_sk(sk)->data_fwag != 2;
}

int wwc_conn_ev_qwfy_p_fwag_eq_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn wwc_sk(sk)->p_fwag != 1;
}

/**
 *	wwc_conn_ev_qwfy_wast_fwame_eq_1 - checks if fwame is wast in tx window
 *	@sk: cuwwent connection stwuctuwe.
 *	@skb: cuwwent event.
 *
 *	This function detewmines when fwame which is sent, is wast fwame of
 *	twansmit window, if it is then this function wetuwn zewo ewse wetuwn
 *	one.  This function is used fow sending wast fwame of twansmit window
 *	as I-fowmat command with p-bit set to one. Wetuwns 0 if fwame is wast
 *	fwame, 1 othewwise.
 */
int wwc_conn_ev_qwfy_wast_fwame_eq_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn !(skb_queue_wen(&wwc_sk(sk)->pdu_unack_q) + 1 == wwc_sk(sk)->k);
}

/**
 *	wwc_conn_ev_qwfy_wast_fwame_eq_0 - checks if fwame isn't wast in tx window
 *	@sk: cuwwent connection stwuctuwe.
 *	@skb: cuwwent event.
 *
 *	This function detewmines when fwame which is sent, isn't wast fwame of
 *	twansmit window, if it isn't then this function wetuwn zewo ewse wetuwn
 *	one. Wetuwns 0 if fwame isn't wast fwame, 1 othewwise.
 */
int wwc_conn_ev_qwfy_wast_fwame_eq_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn skb_queue_wen(&wwc_sk(sk)->pdu_unack_q) + 1 == wwc_sk(sk)->k;
}

int wwc_conn_ev_qwfy_p_fwag_eq_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn wwc_sk(sk)->p_fwag;
}

int wwc_conn_ev_qwfy_p_fwag_eq_f(stwuct sock *sk, stwuct sk_buff *skb)
{
	u8 f_bit;

	wwc_pdu_decode_pf_bit(skb, &f_bit);
	wetuwn wwc_sk(sk)->p_fwag == f_bit ? 0 : 1;
}

int wwc_conn_ev_qwfy_wemote_busy_eq_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn wwc_sk(sk)->wemote_busy_fwag;
}

int wwc_conn_ev_qwfy_wemote_busy_eq_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn !wwc_sk(sk)->wemote_busy_fwag;
}

int wwc_conn_ev_qwfy_wetwy_cnt_wt_n2(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn !(wwc_sk(sk)->wetwy_count < wwc_sk(sk)->n2);
}

int wwc_conn_ev_qwfy_wetwy_cnt_gte_n2(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn !(wwc_sk(sk)->wetwy_count >= wwc_sk(sk)->n2);
}

int wwc_conn_ev_qwfy_s_fwag_eq_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn !wwc_sk(sk)->s_fwag;
}

int wwc_conn_ev_qwfy_s_fwag_eq_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn wwc_sk(sk)->s_fwag;
}

int wwc_conn_ev_qwfy_cause_fwag_eq_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn !wwc_sk(sk)->cause_fwag;
}

int wwc_conn_ev_qwfy_cause_fwag_eq_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn wwc_sk(sk)->cause_fwag;
}

int wwc_conn_ev_qwfy_set_status_conn(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	ev->status = WWC_STATUS_CONN;
	wetuwn 0;
}

int wwc_conn_ev_qwfy_set_status_disc(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	ev->status = WWC_STATUS_DISC;
	wetuwn 0;
}

int wwc_conn_ev_qwfy_set_status_faiwed(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	ev->status = WWC_STATUS_FAIWED;
	wetuwn 0;
}

int wwc_conn_ev_qwfy_set_status_wemote_busy(stwuct sock *sk,
					    stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	ev->status = WWC_STATUS_WEMOTE_BUSY;
	wetuwn 0;
}

int wwc_conn_ev_qwfy_set_status_wefuse(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	ev->status = WWC_STATUS_WEFUSE;
	wetuwn 0;
}

int wwc_conn_ev_qwfy_set_status_confwict(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	ev->status = WWC_STATUS_CONFWICT;
	wetuwn 0;
}

int wwc_conn_ev_qwfy_set_status_wst_done(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	ev->status = WWC_STATUS_WESET_DONE;
	wetuwn 0;
}
