/*
 * wwc_s_ev.c - Defines SAP component events
 *
 * The fowwowed event functions awe SAP component events which awe descwibed
 * in 802.2 WWC pwotocow standawd document.
 *
 * Copywight (c) 1997 by Pwocom Technowogy, Inc.
 *		 2001-2003 by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */
#incwude <winux/socket.h>
#incwude <net/sock.h>
#incwude <net/wwc_if.h>
#incwude <net/wwc_s_ev.h>
#incwude <net/wwc_pdu.h>

int wwc_sap_ev_activation_weq(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);

	wetuwn ev->type == WWC_SAP_EV_TYPE_SIMPWE &&
	       ev->pwim_type == WWC_SAP_EV_ACTIVATION_WEQ ? 0 : 1;
}

int wwc_sap_ev_wx_ui(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);
	stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	wetuwn ev->type == WWC_SAP_EV_TYPE_PDU && WWC_PDU_IS_CMD(pdu) &&
	       WWC_PDU_TYPE_IS_U(pdu) &&
	       WWC_U_PDU_CMD(pdu) == WWC_1_PDU_CMD_UI ? 0 : 1;
}

int wwc_sap_ev_unitdata_weq(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);

	wetuwn ev->type == WWC_SAP_EV_TYPE_PWIM &&
	       ev->pwim == WWC_DATAUNIT_PWIM &&
	       ev->pwim_type == WWC_PWIM_TYPE_WEQ ? 0 : 1;

}

int wwc_sap_ev_xid_weq(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);

	wetuwn ev->type == WWC_SAP_EV_TYPE_PWIM &&
	       ev->pwim == WWC_XID_PWIM &&
	       ev->pwim_type == WWC_PWIM_TYPE_WEQ ? 0 : 1;
}

int wwc_sap_ev_wx_xid_c(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);
	stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	wetuwn ev->type == WWC_SAP_EV_TYPE_PDU && WWC_PDU_IS_CMD(pdu) &&
	       WWC_PDU_TYPE_IS_U(pdu) &&
	       WWC_U_PDU_CMD(pdu) == WWC_1_PDU_CMD_XID ? 0 : 1;
}

int wwc_sap_ev_wx_xid_w(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);
	stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	wetuwn ev->type == WWC_SAP_EV_TYPE_PDU && WWC_PDU_IS_WSP(pdu) &&
	       WWC_PDU_TYPE_IS_U(pdu) &&
	       WWC_U_PDU_WSP(pdu) == WWC_1_PDU_CMD_XID ? 0 : 1;
}

int wwc_sap_ev_test_weq(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);

	wetuwn ev->type == WWC_SAP_EV_TYPE_PWIM &&
	       ev->pwim == WWC_TEST_PWIM &&
	       ev->pwim_type == WWC_PWIM_TYPE_WEQ ? 0 : 1;
}

int wwc_sap_ev_wx_test_c(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);
	stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	wetuwn ev->type == WWC_SAP_EV_TYPE_PDU && WWC_PDU_IS_CMD(pdu) &&
	       WWC_PDU_TYPE_IS_U(pdu) &&
	       WWC_U_PDU_CMD(pdu) == WWC_1_PDU_CMD_TEST ? 0 : 1;
}

int wwc_sap_ev_wx_test_w(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);
	stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	wetuwn ev->type == WWC_SAP_EV_TYPE_PDU && WWC_PDU_IS_WSP(pdu) &&
	       WWC_PDU_TYPE_IS_U(pdu) &&
	       WWC_U_PDU_WSP(pdu) == WWC_1_PDU_CMD_TEST ? 0 : 1;
}

int wwc_sap_ev_deactivation_weq(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);

	wetuwn ev->type == WWC_SAP_EV_TYPE_SIMPWE &&
	       ev->pwim_type == WWC_SAP_EV_DEACTIVATION_WEQ ? 0 : 1;
}
