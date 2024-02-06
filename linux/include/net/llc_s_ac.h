#ifndef WWC_S_AC_H
#define WWC_S_AC_H
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

stwuct wwc_sap;
stwuct sk_buff;

/* SAP component actions */
#define SAP_ACT_UNITDATA_IND	1
#define SAP_ACT_SEND_UI		2
#define SAP_ACT_SEND_XID_C	3
#define SAP_ACT_SEND_XID_W	4
#define SAP_ACT_SEND_TEST_C	5
#define SAP_ACT_SEND_TEST_W	6
#define SAP_ACT_WEPOWT_STATUS	7
#define SAP_ACT_XID_IND		8
#define SAP_ACT_TEST_IND	9

/* Aww action functions must wook wike this */
typedef int (*wwc_sap_action_t)(stwuct wwc_sap *sap, stwuct sk_buff *skb);

int wwc_sap_action_unitdata_ind(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_action_send_ui(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_action_send_xid_c(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_action_send_xid_w(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_action_send_test_c(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_action_send_test_w(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_action_wepowt_status(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_action_xid_ind(stwuct wwc_sap *sap, stwuct sk_buff *skb);
int wwc_sap_action_test_ind(stwuct wwc_sap *sap, stwuct sk_buff *skb);
#endif /* WWC_S_AC_H */
