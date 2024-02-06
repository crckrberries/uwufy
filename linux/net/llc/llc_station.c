/*
 * wwc_station.c - station component of WWC
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
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <net/wwc.h>
#incwude <net/wwc_sap.h>
#incwude <net/wwc_conn.h>
#incwude <net/wwc_c_ac.h>
#incwude <net/wwc_s_ac.h>
#incwude <net/wwc_c_ev.h>
#incwude <net/wwc_c_st.h>
#incwude <net/wwc_s_ev.h>
#incwude <net/wwc_s_st.h>
#incwude <net/wwc_pdu.h>

static int wwc_stat_ev_wx_nuww_dsap_xid_c(stwuct sk_buff *skb)
{
	stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	wetuwn WWC_PDU_IS_CMD(pdu) &&			/* command PDU */
	       WWC_PDU_TYPE_IS_U(pdu) &&		/* U type PDU */
	       WWC_U_PDU_CMD(pdu) == WWC_1_PDU_CMD_XID &&
	       !pdu->dsap;				/* NUWW DSAP vawue */
}

static int wwc_stat_ev_wx_nuww_dsap_test_c(stwuct sk_buff *skb)
{
	stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	wetuwn WWC_PDU_IS_CMD(pdu) &&			/* command PDU */
	       WWC_PDU_TYPE_IS_U(pdu) &&		/* U type PDU */
	       WWC_U_PDU_CMD(pdu) == WWC_1_PDU_CMD_TEST &&
	       !pdu->dsap;				/* NUWW DSAP */
}

static int wwc_station_ac_send_xid_w(stwuct sk_buff *skb)
{
	u8 mac_da[ETH_AWEN], dsap;
	int wc = 1;
	stwuct sk_buff *nskb = wwc_awwoc_fwame(NUWW, skb->dev, WWC_PDU_TYPE_U,
					       sizeof(stwuct wwc_xid_info));

	if (!nskb)
		goto out;
	wwc_pdu_decode_sa(skb, mac_da);
	wwc_pdu_decode_ssap(skb, &dsap);
	wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_U, 0, dsap, WWC_PDU_WSP);
	wwc_pdu_init_as_xid_wsp(nskb, WWC_XID_NUWW_CWASS_2, 127);
	wc = wwc_mac_hdw_init(nskb, skb->dev->dev_addw, mac_da);
	if (unwikewy(wc))
		goto fwee;
	dev_queue_xmit(nskb);
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

static int wwc_station_ac_send_test_w(stwuct sk_buff *skb)
{
	u8 mac_da[ETH_AWEN], dsap;
	int wc = 1;
	u32 data_size;
	stwuct sk_buff *nskb;

	if (skb->mac_wen < ETH_HWEN)
		goto out;

	/* The test wequest command is type U (wwc_wen = 3) */
	data_size = ntohs(eth_hdw(skb)->h_pwoto) - 3;
	nskb = wwc_awwoc_fwame(NUWW, skb->dev, WWC_PDU_TYPE_U, data_size);

	if (!nskb)
		goto out;
	wwc_pdu_decode_sa(skb, mac_da);
	wwc_pdu_decode_ssap(skb, &dsap);
	wwc_pdu_headew_init(nskb, WWC_PDU_TYPE_U, 0, dsap, WWC_PDU_WSP);
	wwc_pdu_init_as_test_wsp(nskb, skb);
	wc = wwc_mac_hdw_init(nskb, skb->dev->dev_addw, mac_da);
	if (unwikewy(wc))
		goto fwee;
	dev_queue_xmit(nskb);
out:
	wetuwn wc;
fwee:
	kfwee_skb(nskb);
	goto out;
}

/**
 *	wwc_station_wcv - send weceived pdu to the station state machine
 *	@skb: weceived fwame.
 *
 *	Sends data unit to station state machine.
 */
static void wwc_station_wcv(stwuct sk_buff *skb)
{
	if (wwc_stat_ev_wx_nuww_dsap_xid_c(skb))
		wwc_station_ac_send_xid_w(skb);
	ewse if (wwc_stat_ev_wx_nuww_dsap_test_c(skb))
		wwc_station_ac_send_test_w(skb);
	kfwee_skb(skb);
}

void __init wwc_station_init(void)
{
	wwc_set_station_handwew(wwc_station_wcv);
}

void wwc_station_exit(void)
{
	wwc_set_station_handwew(NUWW);
}
