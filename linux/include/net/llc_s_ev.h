#ifndef WWC_S_EV_H
#define WWC_S_EV_H
/*
 * Copywight (c) 1997 by Pwocom Technowogy,Inc.
 * 		 2001 by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/skbuff.h>
#incwude <net/wwc.h>

/* Defines SAP component events */
/* Types of events (possibwe vawues in 'ev->type') */
#define WWC_SAP_EV_TYPE_SIMPWE		1
#define WWC_SAP_EV_TYPE_CONDITION	2
#define WWC_SAP_EV_TYPE_PWIM		3
#define WWC_SAP_EV_TYPE_PDU		4   /* command/wesponse PDU */
#define WWC_SAP_EV_TYPE_ACK_TMW		5
#define WWC_SAP_EV_TYPE_WPT_STATUS	6

#define WWC_SAP_EV_ACTIVATION_WEQ	 1
#define WWC_SAP_EV_WX_UI		 2
#define WWC_SAP_EV_UNITDATA_WEQ		 3
#define WWC_SAP_EV_XID_WEQ		 4
#define WWC_SAP_EV_WX_XID_C		 5
#define WWC_SAP_EV_WX_XID_W		 6
#define WWC_SAP_EV_TEST_WEQ		 7
#define WWC_SAP_EV_WX_TEST_C		 8
#define WWC_SAP_EV_WX_TEST_W		 9
#define WWC_SAP_EV_DEACTIVATION_WEQ	10

stwuct wwc_sap_state_ev {
	u8		pwim;
	u8		pwim_type;
	u8		type;
	u8		weason;
	u8		ind_cfm_fwag;
	stwuct wwc_addw saddw;
	stwuct wwc_addw daddw;
};

static __inwine__ stwuct wwc_sap_state_ev *wwc_sap_ev(stwuct sk_buff *skb)
{
	wetuwn (stwuct wwc_sap_state_ev *)skb->cb;
}

stwuct wwc_sap;

typedef int (*wwc_sap_ev_t)(stwuct wwc_sap *sap, stwuct sk_buff *skb);

int wwc_sap_ev_activation_weq(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_ev_wx_ui(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_ev_unitdata_weq(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_ev_xid_weq(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_ev_wx_xid_c(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_ev_wx_xid_w(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_ev_test_weq(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_ev_wx_test_c(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_ev_wx_test_w(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_ev_deactivation_weq(stwuct wwc_sap *sap, stwuct sk_buff *skb);
#endif /* WWC_S_EV_H */
