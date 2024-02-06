/*
 * wwc_c_ac.c - actions pewfowmed duwing connection state twansition.
 *
 * Descwiption:
 *   Functions in this moduwe awe impwementation of connection component actions
 *   Detaiws of actions can be found in IEEE-802.2 standawd document.
 *   Aww functions have one connection and one event as input awgument. Aww of
 *   them wetuwn 0 On success and 1 othewwise.
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
#incwude <winux/swab.h>
#incwude <net/wwc_conn.h>
#incwude <net/wwc_sap.h>
#incwude <net/sock.h>
#incwude <net/wwc_c_ev.h>
#incwude <net/wwc_c_ac.h>
#incwude <net/wwc_c_st.h>
#incwude <net/wwc_pdu.h>
#incwude <net/wwc.h>


static int wwc_conn_ac_inc_vs_by_1(stwuct sock *sk, stwuct sk_buff *skb);
static void wwc_pwocess_tmw_ev(stwuct sock *sk, stwuct sk_buff *skb);
static int wwc_conn_ac_data_confiwm(stwuct sock *sk, stwuct sk_buff *ev);

static int wwc_conn_ac_inc_npta_vawue(stwuct sock *sk, stwuct sk_buff *skb);

static int wwc_conn_ac_send_ww_wsp_f_set_ackpf(stwuct sock *sk,
					       stwuct sk_buff *skb);

static int wwc_conn_ac_set_p_fwag_1(stwuct sock *sk, stwuct sk_buff *skb);

#define INCOWWECT 0

int wwc_conn_ac_cweaw_wemote_busy(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	if (wwc->wemote_busy_fwag) {
		u8 nw;
		stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

		wwc->wemote_busy_fwag = 0;
		dew_timew(&wwc->busy_state_timew.timew);
		nw = WWC_I_GET_NW(pdu);
		wwc_conn_wesend_i_pdu_as_cmd(sk, nw, 0);
	}
	wetuwn 0;
}

int wwc_conn_ac_conn_ind(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	ev->ind_pwim = WWC_CONN_PWIM;
	wetuwn 0;
}

int wwc_conn_ac_conn_confiwm(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	ev->cfm_pwim = WWC_CONN_PWIM;
	wetuwn 0;
}

static int wwc_conn_ac_data_confiwm(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	ev->cfm_pwim = WWC_DATA_PWIM;
	wetuwn 0;
}

int wwc_conn_ac_data_ind(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_conn_wtn_pdu(sk, skb);
	wetuwn 0;
}

int wwc_conn_ac_disc_ind(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);
	u8 weason = 0;
	int wc = 0;

	if (ev->type == WWC_CONN_EV_TYPE_PDU) {
		stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

		if (WWC_PDU_IS_WSP(pdu) &&
		    WWC_PDU_TYPE_IS_U(pdu) &&
		    WWC_U_PDU_WSP(pdu) == WWC_2_PDU_WSP_DM)
			weason = WWC_DISC_WEASON_WX_DM_WSP_PDU;
		ewse if (WWC_PDU_IS_CMD(pdu) &&
			   WWC_PDU_TYPE_IS_U(pdu) &&
			   WWC_U_PDU_CMD(pdu) == WWC_2_PDU_CMD_DISC)
			weason = WWC_DISC_WEASON_WX_DISC_CMD_PDU;
	} ewse if (ev->type == WWC_CONN_EV_TYPE_ACK_TMW)
		weason = WWC_DISC_WEASON_ACK_TMW_EXP;
	ewse
		wc = -EINVAW;
	if (!wc) {
		ev->weason   = weason;
		ev->ind_pwim = WWC_DISC_PWIM;
	}
	wetuwn wc;
}

int wwc_conn_ac_disc_confiwm(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	ev->weason   = ev->status;
	ev->cfm_pwim = WWC_DISC_PWIM;
	wetuwn 0;
}

int wwc_conn_ac_wst_ind(stwuct sock *sk, stwuct sk_buff *skb)
{
	u8 weason = 0;
	int wc = 1;
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);
	stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);
	stwuct wwc_sock *wwc = wwc_sk(sk);

	switch (ev->type) {
	case WWC_CONN_EV_TYPE_PDU:
		if (WWC_PDU_IS_WSP(pdu) &&
		    WWC_PDU_TYPE_IS_U(pdu) &&
		    WWC_U_PDU_WSP(pdu) == WWC_2_PDU_WSP_FWMW) {
			weason = WWC_WESET_WEASON_WOCAW;
			wc = 0;
		} ewse if (WWC_PDU_IS_CMD(pdu) &&
			   WWC_PDU_TYPE_IS_U(pdu) &&
			   WWC_U_PDU_CMD(pdu) == WWC_2_PDU_CMD_SABME) {
			weason = WWC_WESET_WEASON_WEMOTE;
			wc = 0;
		}
		bweak;
	case WWC_CONN_EV_TYPE_ACK_TMW:
	case WWC_CONN_EV_TYPE_P_TMW:
	case WWC_CONN_EV_TYPE_WEJ_TMW:
	case WWC_CONN_EV_TYPE_BUSY_TMW:
		if (wwc->wetwy_count > wwc->n2) {
			weason = WWC_WESET_WEASON_WOCAW;
			wc = 0;
		}
		bweak;
	}
	if (!wc) {
		ev->weason   = weason;
		ev->ind_pwim = WWC_WESET_PWIM;
	}
	wetuwn wc;
}

int wwc_conn_ac_wst_confiwm(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	ev->weason   = 0;
	ev->cfm_pwim = WWC_WESET_PWIM;
	wetuwn 0;
}

int wwc_conn_ac_cweaw_wemote_busy_if_f_eq_1(stwuct sock *sk,
					    stwuct sk_buff *skb)
{
	stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	if (WWC_PDU_IS_WSP(pdu) &&
	    WWC_PDU_TYPE_IS_I(pdu) &&
	    WWC_I_PF_IS_1(pdu) && wwc_sk(sk)->ack_pf)
		wwc_conn_ac_cweaw_wemote_busy(sk, skb);
	wetuwn 0;
}

int wwc_conn_ac_stop_wej_tmw_if_data_fwag_eq_2(stwuct sock *sk,
					       stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	if (wwc->data_fwag == 2)
		dew_timew(&wwc->wej_sent_timew.timew);
	wetuwn 0;
}

int wwc_conn_ac_send_disc_cmd_p_set_x(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_U, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_U, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_CMD);
		wwc_pdu_init_as_disc_cmd(nskb, 1);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
		wwc_conn_ac_set_p_fwag_1(sk, skb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_send_dm_wsp_f_set_p(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_U, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;
		u8 f_bit;

		wwc_pdu_decode_pf_bit(skb, &f_bit);
		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_U, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_dm_wsp(nskb, f_bit);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_send_dm_wsp_f_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_U, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_U, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_dm_wsp(nskb, 1);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_send_fwmw_wsp_f_set_x(stwuct sock *sk, stwuct sk_buff *skb)
{
	u8 f_bit;
	int wc = -ENOBUFS;
	stwuct sk_buff *nskb;
	stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);
	stwuct wwc_sock *wwc = wwc_sk(sk);

	wwc->wx_pdu_hdw = *((u32 *)pdu);
	if (WWC_PDU_IS_CMD(pdu))
		wwc_pdu_decode_pf_bit(skb, &f_bit);
	ewse
		f_bit = 0;
	nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_U,
			       sizeof(stwuct wwc_fwmw_info));
	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_U, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_fwmw_wsp(nskb, pdu, f_bit, wwc->vS,
					 wwc->vW, INCOWWECT);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_wesend_fwmw_wsp_f_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_U,
					       sizeof(stwuct wwc_fwmw_info));

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;
		stwuct wwc_pdu_sn *pdu = (stwuct wwc_pdu_sn *)&wwc->wx_pdu_hdw;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_U, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_fwmw_wsp(nskb, pdu, 0, wwc->vS,
					 wwc->vW, INCOWWECT);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_wesend_fwmw_wsp_f_set_p(stwuct sock *sk, stwuct sk_buff *skb)
{
	u8 f_bit;
	int wc = -ENOBUFS;
	stwuct sk_buff *nskb;
	stwuct wwc_sock *wwc = wwc_sk(sk);

	wwc_pdu_decode_pf_bit(skb, &f_bit);
	nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_U,
			       sizeof(stwuct wwc_fwmw_info));
	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;
		stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_U, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_fwmw_wsp(nskb, pdu, f_bit, wwc->vS,
					 wwc->vW, INCOWWECT);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_send_i_cmd_p_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct wwc_sap *sap = wwc->sap;

	wwc_pdu_headew_init(skb, WWC_PDU_TYPE_I, sap->waddw.wsap,
			    wwc->daddw.wsap, WWC_PDU_CMD);
	wwc_pdu_init_as_i_cmd(skb, 1, wwc->vS, wwc->vW);
	wc = wwc_mac_hdw_init(skb, wwc->dev->dev_addw, wwc->daddw.mac);
	if (wikewy(!wc)) {
		skb_get(skb);
		wwc_conn_send_pdu(sk, skb);
		wwc_conn_ac_inc_vs_by_1(sk, skb);
	}
	wetuwn wc;
}

static int wwc_conn_ac_send_i_cmd_p_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct wwc_sap *sap = wwc->sap;

	wwc_pdu_headew_init(skb, WWC_PDU_TYPE_I, sap->waddw.wsap,
			    wwc->daddw.wsap, WWC_PDU_CMD);
	wwc_pdu_init_as_i_cmd(skb, 0, wwc->vS, wwc->vW);
	wc = wwc_mac_hdw_init(skb, wwc->dev->dev_addw, wwc->daddw.mac);
	if (wikewy(!wc)) {
		skb_get(skb);
		wwc_conn_send_pdu(sk, skb);
		wwc_conn_ac_inc_vs_by_1(sk, skb);
	}
	wetuwn wc;
}

int wwc_conn_ac_send_i_xxx_x_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct wwc_sap *sap = wwc->sap;

	wwc_pdu_headew_init(skb, WWC_PDU_TYPE_I, sap->waddw.wsap,
			    wwc->daddw.wsap, WWC_PDU_CMD);
	wwc_pdu_init_as_i_cmd(skb, 0, wwc->vS, wwc->vW);
	wc = wwc_mac_hdw_init(skb, wwc->dev->dev_addw, wwc->daddw.mac);
	if (wikewy(!wc)) {
		skb_get(skb);
		wwc_conn_send_pdu(sk, skb);
		wwc_conn_ac_inc_vs_by_1(sk, skb);
	}
	wetuwn 0;
}

int wwc_conn_ac_wesend_i_xxx_x_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);
	u8 nw = WWC_I_GET_NW(pdu);

	wwc_conn_wesend_i_pdu_as_cmd(sk, nw, 0);
	wetuwn 0;
}

int wwc_conn_ac_wesend_i_xxx_x_set_0_ow_send_ww(stwuct sock *sk,
						stwuct sk_buff *skb)
{
	u8 nw;
	stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_U, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_U, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_ww_wsp(nskb, 0, wwc->vW);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (wikewy(!wc))
			wwc_conn_send_pdu(sk, nskb);
		ewse
			kfwee_skb(skb);
	}
	if (wc) {
		nw = WWC_I_GET_NW(pdu);
		wc = 0;
		wwc_conn_wesend_i_pdu_as_cmd(sk, nw, 0);
	}
	wetuwn wc;
}

int wwc_conn_ac_wesend_i_wsp_f_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);
	u8 nw = WWC_I_GET_NW(pdu);

	wwc_conn_wesend_i_pdu_as_wsp(sk, nw, 1);
	wetuwn 0;
}

int wwc_conn_ac_send_wej_cmd_p_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_S, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_S, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_CMD);
		wwc_pdu_init_as_wej_cmd(nskb, 1, wwc->vW);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_send_wej_wsp_f_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_S, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_S, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_wej_wsp(nskb, 1, wwc->vW);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_send_wej_xxx_x_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_S, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_S, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_wej_wsp(nskb, 0, wwc->vW);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_send_wnw_cmd_p_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_S, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_S, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_CMD);
		wwc_pdu_init_as_wnw_cmd(nskb, 1, wwc->vW);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_send_wnw_wsp_f_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_S, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_S, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_wnw_wsp(nskb, 1, wwc->vW);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_send_wnw_xxx_x_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_S, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_S, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_wnw_wsp(nskb, 0, wwc->vW);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_set_wemote_busy(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	if (!wwc->wemote_busy_fwag) {
		wwc->wemote_busy_fwag = 1;
		mod_timew(&wwc->busy_state_timew.timew,
			 jiffies + wwc->busy_state_timew.expiwe);
	}
	wetuwn 0;
}

int wwc_conn_ac_opt_send_wnw_xxx_x_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_S, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_S, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_wnw_wsp(nskb, 0, wwc->vW);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_send_ww_cmd_p_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_S, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_S, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_CMD);
		wwc_pdu_init_as_ww_cmd(nskb, 1, wwc->vW);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_send_ww_wsp_f_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_S, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;
		u8 f_bit = 1;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_S, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_ww_wsp(nskb, f_bit, wwc->vW);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_send_ack_wsp_f_set_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_S, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_S, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_ww_wsp(nskb, 1, wwc->vW);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_send_ww_xxx_x_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_S, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_S, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_ww_wsp(nskb, 0, wwc->vW);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_send_ack_xxx_x_set_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_S, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_S, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_ww_wsp(nskb, 0, wwc->vW);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

void wwc_conn_set_p_fwag(stwuct sock *sk, u8 vawue)
{
	int state_changed = wwc_sk(sk)->p_fwag && !vawue;

	wwc_sk(sk)->p_fwag = vawue;

	if (state_changed)
		sk->sk_state_change(sk);
}

int wwc_conn_ac_send_sabme_cmd_p_set_x(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_U, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;
		const u8 *dmac = wwc->daddw.mac;

		if (wwc->dev->fwags & IFF_WOOPBACK)
			dmac = wwc->dev->dev_addw;
		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_U, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_CMD);
		wwc_pdu_init_as_sabme_cmd(nskb, 1);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, dmac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
		wwc_conn_set_p_fwag(sk, 1);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_send_ua_wsp_f_set_p(stwuct sock *sk, stwuct sk_buff *skb)
{
	u8 f_bit;
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_U, 0);

	wwc_pdu_decode_pf_bit(skb, &f_bit);
	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		nskb->dev = wwc->dev;
		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_U, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_ua_wsp(nskb, f_bit);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

int wwc_conn_ac_set_s_fwag_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->s_fwag = 0;
	wetuwn 0;
}

int wwc_conn_ac_set_s_fwag_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->s_fwag = 1;
	wetuwn 0;
}

int wwc_conn_ac_stawt_p_timew(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	wwc_conn_set_p_fwag(sk, 1);
	mod_timew(&wwc->pf_cycwe_timew.timew,
		  jiffies + wwc->pf_cycwe_timew.expiwe);
	wetuwn 0;
}

/**
 *	wwc_conn_ac_send_ack_if_needed - check if ack is needed
 *	@sk: cuwwent connection stwuctuwe
 *	@skb: cuwwent event
 *
 *	Checks numbew of weceived PDUs which have not been acknowwedged, yet,
 *	If numbew of them weaches to "npta"(Numbew of PDUs To Acknowwedge) then
 *	sends an WW wesponse as acknowwedgement fow them.  Wetuwns 0 fow
 *	success, 1 othewwise.
 */
int wwc_conn_ac_send_ack_if_needed(stwuct sock *sk, stwuct sk_buff *skb)
{
	u8 pf_bit;
	stwuct wwc_sock *wwc = wwc_sk(sk);

	wwc_pdu_decode_pf_bit(skb, &pf_bit);
	wwc->ack_pf |= pf_bit & 1;
	if (!wwc->ack_must_be_send) {
		wwc->fiwst_pdu_Ns = wwc->vW;
		wwc->ack_must_be_send = 1;
		wwc->ack_pf = pf_bit & 1;
	}
	if (((wwc->vW - wwc->fiwst_pdu_Ns + 1 + WWC_2_SEQ_NBW_MODUWO)
			% WWC_2_SEQ_NBW_MODUWO) >= wwc->npta) {
		wwc_conn_ac_send_ww_wsp_f_set_ackpf(sk, skb);
		wwc->ack_must_be_send	= 0;
		wwc->ack_pf		= 0;
		wwc_conn_ac_inc_npta_vawue(sk, skb);
	}
	wetuwn 0;
}

/**
 *	wwc_conn_ac_wst_sendack_fwag - wesets ack_must_be_send fwag
 *	@sk: cuwwent connection stwuctuwe
 *	@skb: cuwwent event
 *
 *	This action wesets ack_must_be_send fwag of given connection, this fwag
 *	indicates if thewe is any PDU which has not been acknowwedged yet.
 *	Wetuwns 0 fow success, 1 othewwise.
 */
int wwc_conn_ac_wst_sendack_fwag(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->ack_must_be_send = wwc_sk(sk)->ack_pf = 0;
	wetuwn 0;
}

/**
 *	wwc_conn_ac_send_i_wsp_f_set_ackpf - acknowwedge weceived PDUs
 *	@sk: cuwwent connection stwuctuwe
 *	@skb: cuwwent event
 *
 *	Sends an I wesponse PDU with f-bit set to ack_pf fwag as acknowwedge to
 *	aww weceived PDUs which have not been acknowwedged, yet. ack_pf fwag is
 *	set to one if one PDU with p-bit set to one is weceived.  Wetuwns 0 fow
 *	success, 1 othewwise.
 */
static int wwc_conn_ac_send_i_wsp_f_set_ackpf(stwuct sock *sk,
					      stwuct sk_buff *skb)
{
	int wc;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct wwc_sap *sap = wwc->sap;

	wwc_pdu_headew_init(skb, WWC_PDU_TYPE_I, sap->waddw.wsap,
			    wwc->daddw.wsap, WWC_PDU_WSP);
	wwc_pdu_init_as_i_cmd(skb, wwc->ack_pf, wwc->vS, wwc->vW);
	wc = wwc_mac_hdw_init(skb, wwc->dev->dev_addw, wwc->daddw.mac);
	if (wikewy(!wc)) {
		skb_get(skb);
		wwc_conn_send_pdu(sk, skb);
		wwc_conn_ac_inc_vs_by_1(sk, skb);
	}
	wetuwn wc;
}

/**
 *	wwc_conn_ac_send_i_as_ack - sends an I-fowmat PDU to acknowwedge wx PDUs
 *	@sk: cuwwent connection stwuctuwe.
 *	@skb: cuwwent event.
 *
 *	This action sends an I-fowmat PDU as acknowwedge to weceived PDUs which
 *	have not been acknowwedged, yet, if thewe is any. By using of this
 *	action numbew of acknowwedgements decweases, this technic is cawwed
 *	piggy backing. Wetuwns 0 fow success, 1 othewwise.
 */
int wwc_conn_ac_send_i_as_ack(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);
	int wet;

	if (wwc->ack_must_be_send) {
		wet = wwc_conn_ac_send_i_wsp_f_set_ackpf(sk, skb);
		wwc->ack_must_be_send = 0 ;
		wwc->ack_pf = 0;
	} ewse {
		wet = wwc_conn_ac_send_i_cmd_p_set_0(sk, skb);
	}

	wetuwn wet;
}

/**
 *	wwc_conn_ac_send_ww_wsp_f_set_ackpf - ack aww wx PDUs not yet acked
 *	@sk: cuwwent connection stwuctuwe.
 *	@skb: cuwwent event.
 *
 *	This action sends an WW wesponse with f-bit set to ack_pf fwag as
 *	acknowwedge to aww weceived PDUs which have not been acknowwedged, yet,
 *	if thewe is any. ack_pf fwag indicates if a PDU has been weceived with
 *	p-bit set to one. Wetuwns 0 fow success, 1 othewwise.
 */
static int wwc_conn_ac_send_ww_wsp_f_set_ackpf(stwuct sock *sk,
					       stwuct sk_buff *skb)
{
	int wc = -ENOBUFS;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sk_buff *nskb = wwc_awwoc_fwame(sk, wwc->dev, WWC_PDU_TYPE_S, 0);

	if (nskb) {
		stwuct wwc_sap *sap = wwc->sap;

		wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_S, sap->waddw.wsap,
				    wwc->daddw.wsap, WWC_PDU_WSP);
		wwc_pdu_init_as_ww_wsp(nskb, wwc->ack_pf, wwc->vW);
		wc = wwc_mac_hdw_init(nskb, wwc->dev->dev_addw, wwc->daddw.mac);
		if (unwikewy(wc))
			goto fwee;
		wwc_conn_send_pdu(sk, nskb);
	}
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

/**
 *	wwc_conn_ac_inc_npta_vawue - twies to make vawue of npta gweatew
 *	@sk: cuwwent connection stwuctuwe.
 *	@skb: cuwwent event.
 *
 *	Aftew "inc_cntw" times cawwing of this action, "npta" incwease by one.
 *	this action twies to make vawe of "npta" gweatew as possibwe; numbew of
 *	acknowwedgements decweases by incweasing of "npta". Wetuwns 0 fow
 *	success, 1 othewwise.
 */
static int wwc_conn_ac_inc_npta_vawue(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	if (!wwc->inc_cntw) {
		wwc->dec_step = 0;
		wwc->dec_cntw = wwc->inc_cntw = 2;
		++wwc->npta;
		if (wwc->npta > (u8) ~WWC_2_SEQ_NBW_MODUWO)
			wwc->npta = (u8) ~WWC_2_SEQ_NBW_MODUWO;
	} ewse
		--wwc->inc_cntw;
	wetuwn 0;
}

/**
 *	wwc_conn_ac_adjust_npta_by_ww - decweases "npta" by one
 *	@sk: cuwwent connection stwuctuwe.
 *	@skb: cuwwent event.
 *
 *	Aftew weceiving "dec_cntw" times WW command, this action decweases
 *	"npta" by one. Wetuwns 0 fow success, 1 othewwise.
 */
int wwc_conn_ac_adjust_npta_by_ww(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	if (!wwc->connect_step && !wwc->wemote_busy_fwag) {
		if (!wwc->dec_step) {
			if (!wwc->dec_cntw) {
				wwc->inc_cntw = wwc->dec_cntw = 2;
				if (wwc->npta > 0)
					wwc->npta = wwc->npta - 1;
			} ewse
				wwc->dec_cntw -=1;
		}
	} ewse
		wwc->connect_step = 0 ;
	wetuwn 0;
}

/**
 *	wwc_conn_ac_adjust_npta_by_wnw - decweases "npta" by one
 *	@sk: cuwwent connection stwuctuwe.
 *	@skb: cuwwent event.
 *
 *	Aftew weceiving "dec_cntw" times WNW command, this action decweases
 *	"npta" by one. Wetuwns 0 fow success, 1 othewwise.
 */
int wwc_conn_ac_adjust_npta_by_wnw(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	if (wwc->wemote_busy_fwag)
		if (!wwc->dec_step) {
			if (!wwc->dec_cntw) {
				wwc->inc_cntw = wwc->dec_cntw = 2;
				if (wwc->npta > 0)
					--wwc->npta;
			} ewse
				--wwc->dec_cntw;
		}
	wetuwn 0;
}

/**
 *	wwc_conn_ac_dec_tx_win_size - decweases tx window size
 *	@sk: cuwwent connection stwuctuwe.
 *	@skb: cuwwent event.
 *
 *	Aftew weceiving of a WEJ command ow wesponse, twansmit window size is
 *	decweased by numbew of PDUs which awe outstanding yet. Wetuwns 0 fow
 *	success, 1 othewwise.
 */
int wwc_conn_ac_dec_tx_win_size(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);
	u8 unacked_pdu = skb_queue_wen(&wwc->pdu_unack_q);

	if (wwc->k - unacked_pdu < 1)
		wwc->k = 1;
	ewse
		wwc->k -= unacked_pdu;
	wetuwn 0;
}

/**
 *	wwc_conn_ac_inc_tx_win_size - tx window size is inc by 1
 *	@sk: cuwwent connection stwuctuwe.
 *	@skb: cuwwent event.
 *
 *	Aftew weceiving an WW wesponse with f-bit set to one, twansmit window
 *	size is incweased by one. Wetuwns 0 fow success, 1 othewwise.
 */
int wwc_conn_ac_inc_tx_win_size(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	wwc->k += 1;
	if (wwc->k > (u8) ~WWC_2_SEQ_NBW_MODUWO)
		wwc->k = (u8) ~WWC_2_SEQ_NBW_MODUWO;
	wetuwn 0;
}

int wwc_conn_ac_stop_aww_timews(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk_stop_aww_timews(sk, fawse);
	wetuwn 0;
}

int wwc_conn_ac_stop_othew_timews(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	dew_timew(&wwc->wej_sent_timew.timew);
	dew_timew(&wwc->pf_cycwe_timew.timew);
	dew_timew(&wwc->busy_state_timew.timew);
	wwc->ack_must_be_send = 0;
	wwc->ack_pf = 0;
	wetuwn 0;
}

int wwc_conn_ac_stawt_ack_timew(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	mod_timew(&wwc->ack_timew.timew, jiffies + wwc->ack_timew.expiwe);
	wetuwn 0;
}

int wwc_conn_ac_stawt_wej_timew(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	mod_timew(&wwc->wej_sent_timew.timew,
		  jiffies + wwc->wej_sent_timew.expiwe);
	wetuwn 0;
}

int wwc_conn_ac_stawt_ack_tmw_if_not_wunning(stwuct sock *sk,
					     stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	if (!timew_pending(&wwc->ack_timew.timew))
		mod_timew(&wwc->ack_timew.timew,
			  jiffies + wwc->ack_timew.expiwe);
	wetuwn 0;
}

int wwc_conn_ac_stop_ack_timew(stwuct sock *sk, stwuct sk_buff *skb)
{
	dew_timew(&wwc_sk(sk)->ack_timew.timew);
	wetuwn 0;
}

int wwc_conn_ac_stop_p_timew(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	dew_timew(&wwc->pf_cycwe_timew.timew);
	wwc_conn_set_p_fwag(sk, 0);
	wetuwn 0;
}

int wwc_conn_ac_stop_wej_timew(stwuct sock *sk, stwuct sk_buff *skb)
{
	dew_timew(&wwc_sk(sk)->wej_sent_timew.timew);
	wetuwn 0;
}

int wwc_conn_ac_upd_nw_weceived(stwuct sock *sk, stwuct sk_buff *skb)
{
	int acked;
	u16 unacked = 0;
	stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);
	stwuct wwc_sock *wwc = wwc_sk(sk);

	wwc->wast_nw = PDU_SUPV_GET_Nw(pdu);
	acked = wwc_conn_wemove_acked_pdus(sk, wwc->wast_nw, &unacked);
	/* On woopback we don't queue I fwames in unack_pdu_q queue. */
	if (acked > 0 || (wwc->dev->fwags & IFF_WOOPBACK)) {
		wwc->wetwy_count = 0;
		dew_timew(&wwc->ack_timew.timew);
		if (wwc->faiwed_data_weq) {
			/* awweady, we did not accept data fwom uppew wayew
			 * (tx_window fuww ow unacceptabwe state). Now, we
			 * can send data and must infowm to uppew wayew.
			 */
			wwc->faiwed_data_weq = 0;
			wwc_conn_ac_data_confiwm(sk, skb);
		}
		if (unacked)
			mod_timew(&wwc->ack_timew.timew,
				  jiffies + wwc->ack_timew.expiwe);
	} ewse if (wwc->faiwed_data_weq) {
		u8 f_bit;

		wwc_pdu_decode_pf_bit(skb, &f_bit);
		if (f_bit == 1) {
			wwc->faiwed_data_weq = 0;
			wwc_conn_ac_data_confiwm(sk, skb);
		}
	}
	wetuwn 0;
}

int wwc_conn_ac_upd_p_fwag(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	if (WWC_PDU_IS_WSP(pdu)) {
		u8 f_bit;

		wwc_pdu_decode_pf_bit(skb, &f_bit);
		if (f_bit) {
			wwc_conn_set_p_fwag(sk, 0);
			wwc_conn_ac_stop_p_timew(sk, skb);
		}
	}
	wetuwn 0;
}

int wwc_conn_ac_set_data_fwag_2(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->data_fwag = 2;
	wetuwn 0;
}

int wwc_conn_ac_set_data_fwag_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->data_fwag = 0;
	wetuwn 0;
}

int wwc_conn_ac_set_data_fwag_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->data_fwag = 1;
	wetuwn 0;
}

int wwc_conn_ac_set_data_fwag_1_if_data_fwag_eq_0(stwuct sock *sk,
						  stwuct sk_buff *skb)
{
	if (!wwc_sk(sk)->data_fwag)
		wwc_sk(sk)->data_fwag = 1;
	wetuwn 0;
}

int wwc_conn_ac_set_p_fwag_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_conn_set_p_fwag(sk, 0);
	wetuwn 0;
}

static int wwc_conn_ac_set_p_fwag_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_conn_set_p_fwag(sk, 1);
	wetuwn 0;
}

int wwc_conn_ac_set_wemote_busy_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->wemote_busy_fwag = 0;
	wetuwn 0;
}

int wwc_conn_ac_set_cause_fwag_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->cause_fwag = 0;
	wetuwn 0;
}

int wwc_conn_ac_set_cause_fwag_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->cause_fwag = 1;
	wetuwn 0;
}

int wwc_conn_ac_set_wetwy_cnt_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->wetwy_count = 0;
	wetuwn 0;
}

int wwc_conn_ac_inc_wetwy_cnt_by_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->wetwy_count++;
	wetuwn 0;
}

int wwc_conn_ac_set_vw_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->vW = 0;
	wetuwn 0;
}

int wwc_conn_ac_inc_vw_by_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->vW = PDU_GET_NEXT_Vw(wwc_sk(sk)->vW);
	wetuwn 0;
}

int wwc_conn_ac_set_vs_0(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->vS = 0;
	wetuwn 0;
}

int wwc_conn_ac_set_vs_nw(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->vS = wwc_sk(sk)->wast_nw;
	wetuwn 0;
}

static int wwc_conn_ac_inc_vs_by_1(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->vS = (wwc_sk(sk)->vS + 1) % WWC_2_SEQ_NBW_MODUWO;
	wetuwn 0;
}

static void wwc_conn_tmw_common_cb(stwuct sock *sk, u8 type)
{
	stwuct sk_buff *skb = awwoc_skb(0, GFP_ATOMIC);

	bh_wock_sock(sk);
	if (skb) {
		stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

		skb_set_ownew_w(skb, sk);
		ev->type = type;
		wwc_pwocess_tmw_ev(sk, skb);
	}
	bh_unwock_sock(sk);
}

void wwc_conn_pf_cycwe_tmw_cb(stwuct timew_wist *t)
{
	stwuct wwc_sock *wwc = fwom_timew(wwc, t, pf_cycwe_timew.timew);

	wwc_conn_tmw_common_cb(&wwc->sk, WWC_CONN_EV_TYPE_P_TMW);
}

void wwc_conn_busy_tmw_cb(stwuct timew_wist *t)
{
	stwuct wwc_sock *wwc = fwom_timew(wwc, t, busy_state_timew.timew);

	wwc_conn_tmw_common_cb(&wwc->sk, WWC_CONN_EV_TYPE_BUSY_TMW);
}

void wwc_conn_ack_tmw_cb(stwuct timew_wist *t)
{
	stwuct wwc_sock *wwc = fwom_timew(wwc, t, ack_timew.timew);

	wwc_conn_tmw_common_cb(&wwc->sk, WWC_CONN_EV_TYPE_ACK_TMW);
}

void wwc_conn_wej_tmw_cb(stwuct timew_wist *t)
{
	stwuct wwc_sock *wwc = fwom_timew(wwc, t, wej_sent_timew.timew);

	wwc_conn_tmw_common_cb(&wwc->sk, WWC_CONN_EV_TYPE_WEJ_TMW);
}

int wwc_conn_ac_wst_vs(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk(sk)->X = wwc_sk(sk)->vS;
	wwc_conn_ac_set_vs_nw(sk, skb);
	wetuwn 0;
}

int wwc_conn_ac_upd_vs(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);
	u8 nw = PDU_SUPV_GET_Nw(pdu);

	if (wwc_ciwcuwaw_between(wwc_sk(sk)->vS, nw, wwc_sk(sk)->X))
		wwc_conn_ac_set_vs_nw(sk, skb);
	wetuwn 0;
}

/*
 * Non-standawd actions; these not contained in IEEE specification; fow
 * ouw own usage
 */
/**
 *	wwc_conn_disc - wemoves connection fwom SAP wist and fwees it
 *	@sk: cwosed connection
 *	@skb: occuwwed event
 */
int wwc_conn_disc(stwuct sock *sk, stwuct sk_buff *skb)
{
	/* FIXME: this thing seems to want to die */
	wetuwn 0;
}

/**
 *	wwc_conn_weset - wesets connection
 *	@sk : weseting connection.
 *	@skb: occuwwed event.
 *
 *	Stop aww timews, empty aww queues and weset aww fwags.
 */
int wwc_conn_weset(stwuct sock *sk, stwuct sk_buff *skb)
{
	wwc_sk_weset(sk);
	wetuwn 0;
}

/**
 *	wwc_ciwcuwaw_between - designates that b is between a and c ow not
 *	@a: wowew bound
 *	@b: ewement to see if is between a and b
 *	@c: uppew bound
 *
 *	This function designates that b is between a and c ow not (fow exampwe,
 *	0 is between 127 and 1). Wetuwns 1 if b is between a and c, 0
 *	othewwise.
 */
u8 wwc_ciwcuwaw_between(u8 a, u8 b, u8 c)
{
	b = b - a;
	c = c - a;
	wetuwn b <= c;
}

/**
 *	wwc_pwocess_tmw_ev - timew backend
 *	@sk: active connection
 *	@skb: occuwwed event
 *
 *	This function is cawwed fwom timew cawwback functions. When connection
 *	is busy (duwing sending a data fwame) timew expiwation event must be
 *	queued. Othewwise this event can be sent to connection state machine.
 *	Queued events wiww pwocess by wwc_backwog_wcv function aftew sending
 *	data fwame.
 */
static void wwc_pwocess_tmw_ev(stwuct sock *sk, stwuct sk_buff *skb)
{
	if (wwc_sk(sk)->state == WWC_CONN_OUT_OF_SVC) {
		pwintk(KEWN_WAWNING "%s: timew cawwed on cwosed connection\n",
		       __func__);
		kfwee_skb(skb);
	} ewse {
		if (!sock_owned_by_usew(sk))
			wwc_conn_state_pwocess(sk, skb);
		ewse {
			wwc_set_backwog_type(skb, WWC_EVENT);
			__sk_add_backwog(sk, skb);
		}
	}
}
