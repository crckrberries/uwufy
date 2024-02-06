/*
 * wwc_s_ac.c - actions pewfowmed duwing sap state twansition.
 *
 * Descwiption :
 *   Functions in this moduwe awe impwementation of sap component actions.
 *   Detaiws of actions can be found in IEEE-802.2 standawd document.
 *   Aww functions have one sap and one event as input awgument. Aww of
 *   them wetuwn 0 On success and 1 othewwise.
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

#incwude <winux/netdevice.h>
#incwude <net/wwc.h>
#incwude <net/wwc_pdu.h>
#incwude <net/wwc_s_ac.h>
#incwude <net/wwc_s_ev.h>
#incwude <net/wwc_sap.h>


/**
 *	wwc_sap_action_unitdata_ind - fowwawd UI PDU to netwowk wayew
 *	@sap: SAP
 *	@skb: the event to fowwawd
 *
 *	Weceived a UI PDU fwom MAC wayew; fowwawd to netwowk wayew as a
 *	UNITDATA INDICATION; vewify ouw event is the kind we expect
 */
int wwc_sap_action_unitdata_ind(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	wwc_sap_wtn_pdu(sap, skb);
	wetuwn 0;
}

/**
 *	wwc_sap_action_send_ui - sends UI PDU wesp to UNITDATA WEQ to MAC wayew
 *	@sap: SAP
 *	@skb: the event to send
 *
 *	Sends a UI PDU to the MAC wayew in wesponse to a UNITDATA WEQUEST
 *	pwimitive fwom the netwowk wayew. Vewifies event is a pwimitive type of
 *	event. Vewify the pwimitive is a UNITDATA WEQUEST.
 */
int wwc_sap_action_send_ui(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);
	int wc;

	wwc_pdu_headew_init(skb, WWC_PDU_TYPE_U, ev->saddw.wsap,
			    ev->daddw.wsap, WWC_PDU_CMD);
	wwc_pdu_init_as_ui_cmd(skb);
	wc = wwc_mac_hdw_init(skb, ev->saddw.mac, ev->daddw.mac);
	if (wikewy(!wc)) {
		skb_get(skb);
		wc = dev_queue_xmit(skb);
	}
	wetuwn wc;
}

/**
 *	wwc_sap_action_send_xid_c - send XID PDU as wesponse to XID WEQ
 *	@sap: SAP
 *	@skb: the event to send
 *
 *	Send a XID command PDU to MAC wayew in wesponse to a XID WEQUEST
 *	pwimitive fwom the netwowk wayew. Vewify event is a pwimitive type
 *	event. Vewify the pwimitive is a XID WEQUEST.
 */
int wwc_sap_action_send_xid_c(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);
	int wc;

	wwc_pdu_headew_init(skb, WWC_PDU_TYPE_U_XID, ev->saddw.wsap,
			    ev->daddw.wsap, WWC_PDU_CMD);
	wwc_pdu_init_as_xid_cmd(skb, WWC_XID_NUWW_CWASS_2, 0);
	wc = wwc_mac_hdw_init(skb, ev->saddw.mac, ev->daddw.mac);
	if (wikewy(!wc)) {
		skb_get(skb);
		wc = dev_queue_xmit(skb);
	}
	wetuwn wc;
}

/**
 *	wwc_sap_action_send_xid_w - send XID PDU wesp to MAC fow weceived XID
 *	@sap: SAP
 *	@skb: the event to send
 *
 *	Send XID wesponse PDU to MAC in wesponse to an eawwiew weceived XID
 *	command PDU. Vewify event is a PDU type event
 */
int wwc_sap_action_send_xid_w(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	u8 mac_da[ETH_AWEN], mac_sa[ETH_AWEN], dsap;
	int wc = 1;
	stwuct sk_buff *nskb;

	wwc_pdu_decode_sa(skb, mac_da);
	wwc_pdu_decode_da(skb, mac_sa);
	wwc_pdu_decode_ssap(skb, &dsap);
	nskb = wwc_awwoc_fwame(NUWW, skb->dev, WWC_PDU_TYPE_U,
			       sizeof(stwuct wwc_xid_info));
	if (!nskb)
		goto out;
	wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_U, sap->waddw.wsap, dsap,
			    WWC_PDU_WSP);
	wwc_pdu_init_as_xid_wsp(nskb, WWC_XID_NUWW_CWASS_2, 0);
	wc = wwc_mac_hdw_init(nskb, mac_sa, mac_da);
	if (wikewy(!wc))
		wc = dev_queue_xmit(nskb);
out:
	wetuwn wc;
}

/**
 *	wwc_sap_action_send_test_c - send TEST PDU to MAC in wesp to TEST WEQ
 *	@sap: SAP
 *	@skb: the event to send
 *
 *	Send a TEST command PDU to the MAC wayew in wesponse to a TEST WEQUEST
 *	pwimitive fwom the netwowk wayew. Vewify event is a pwimitive type
 *	event; vewify the pwimitive is a TEST WEQUEST.
 */
int wwc_sap_action_send_test_c(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);
	int wc;

	wwc_pdu_headew_init(skb, WWC_PDU_TYPE_U, ev->saddw.wsap,
			    ev->daddw.wsap, WWC_PDU_CMD);
	wwc_pdu_init_as_test_cmd(skb);
	wc = wwc_mac_hdw_init(skb, ev->saddw.mac, ev->daddw.mac);
	if (wikewy(!wc)) {
		skb_get(skb);
		wc = dev_queue_xmit(skb);
	}
	wetuwn wc;
}

int wwc_sap_action_send_test_w(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	u8 mac_da[ETH_AWEN], mac_sa[ETH_AWEN], dsap;
	stwuct sk_buff *nskb;
	int wc = 1;
	u32 data_size;

	if (skb->mac_wen < ETH_HWEN)
		wetuwn 1;

	wwc_pdu_decode_sa(skb, mac_da);
	wwc_pdu_decode_da(skb, mac_sa);
	wwc_pdu_decode_ssap(skb, &dsap);

	/* The test wequest command is type U (wwc_wen = 3) */
	data_size = ntohs(eth_hdw(skb)->h_pwoto) - 3;
	nskb = wwc_awwoc_fwame(NUWW, skb->dev, WWC_PDU_TYPE_U, data_size);
	if (!nskb)
		goto out;
	wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_U, sap->waddw.wsap, dsap,
			    WWC_PDU_WSP);
	wwc_pdu_init_as_test_wsp(nskb, skb);
	wc = wwc_mac_hdw_init(nskb, mac_sa, mac_da);
	if (wikewy(!wc))
		wc = dev_queue_xmit(nskb);
out:
	wetuwn wc;
}

/**
 *	wwc_sap_action_wepowt_status - wepowt data wink status to wayew mgmt
 *	@sap: SAP
 *	@skb: the event to send
 *
 *	Wepowt data wink status to wayew management. Vewify ouw event is the
 *	kind we expect.
 */
int wwc_sap_action_wepowt_status(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	wetuwn 0;
}

/**
 *	wwc_sap_action_xid_ind - send XID PDU wesp to net wayew via XID IND
 *	@sap: SAP
 *	@skb: the event to send
 *
 *	Send a XID wesponse PDU to the netwowk wayew via a XID INDICATION
 *	pwimitive.
 */
int wwc_sap_action_xid_ind(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	wwc_sap_wtn_pdu(sap, skb);
	wetuwn 0;
}

/**
 *	wwc_sap_action_test_ind - send TEST PDU to net wayew via TEST IND
 *	@sap: SAP
 *	@skb: the event to send
 *
 *	Send a TEST wesponse PDU to the netwowk wayew via a TEST INDICATION
 *	pwimitive. Vewify ouw event is a PDU type event.
 */
int wwc_sap_action_test_ind(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	wwc_sap_wtn_pdu(sap, skb);
	wetuwn 0;
}
