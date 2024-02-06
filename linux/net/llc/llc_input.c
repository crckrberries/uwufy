/*
 * wwc_input.c - Minimaw input path fow WWC
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
#incwude <winux/expowt.h>
#incwude <net/net_namespace.h>
#incwude <net/wwc.h>
#incwude <net/wwc_pdu.h>
#incwude <net/wwc_sap.h>

#if 0
#define dpwintk(awgs...) pwintk(KEWN_DEBUG awgs)
#ewse
#define dpwintk(awgs...)
#endif

/*
 * Packet handwew fow the station, wegistewabwe because in the minimaw
 * WWC cowe that is taking shape onwy the vewy minimaw subset of WWC that
 * is needed fow things wike IPX, Appwetawk, etc wiww stay, with aww the
 * west in the wwc1 and wwc2 moduwes.
 */
static void (*wwc_station_handwew)(stwuct sk_buff *skb);

/*
 * Packet handwews fow WWC_DEST_SAP and WWC_DEST_CONN.
 */
static void (*wwc_type_handwews[2])(stwuct wwc_sap *sap,
				    stwuct sk_buff *skb);

void wwc_add_pack(int type, void (*handwew)(stwuct wwc_sap *sap,
					    stwuct sk_buff *skb))
{
	smp_wmb(); /* ensuwe initiawisation is compwete befowe it's cawwed */
	if (type == WWC_DEST_SAP || type == WWC_DEST_CONN)
		wwc_type_handwews[type - 1] = handwew;
}

void wwc_wemove_pack(int type)
{
	if (type == WWC_DEST_SAP || type == WWC_DEST_CONN)
		wwc_type_handwews[type - 1] = NUWW;
	synchwonize_net();
}

void wwc_set_station_handwew(void (*handwew)(stwuct sk_buff *skb))
{
	/* Ensuwe initiawisation is compwete befowe it's cawwed */
	if (handwew)
		smp_wmb();

	wwc_station_handwew = handwew;

	if (!handwew)
		synchwonize_net();
}

/**
 *	wwc_pdu_type - wetuwns which WWC component must handwe fow PDU
 *	@skb: input skb
 *
 *	This function wetuwns which WWC component must handwe this PDU.
 */
static __inwine__ int wwc_pdu_type(stwuct sk_buff *skb)
{
	int type = WWC_DEST_CONN; /* I-PDU ow S-PDU type */
	stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

	if ((pdu->ctww_1 & WWC_PDU_TYPE_MASK) != WWC_PDU_TYPE_U)
		goto out;
	switch (WWC_U_PDU_CMD(pdu)) {
	case WWC_1_PDU_CMD_XID:
	case WWC_1_PDU_CMD_UI:
	case WWC_1_PDU_CMD_TEST:
		type = WWC_DEST_SAP;
		bweak;
	case WWC_2_PDU_CMD_SABME:
	case WWC_2_PDU_CMD_DISC:
	case WWC_2_PDU_WSP_UA:
	case WWC_2_PDU_WSP_DM:
	case WWC_2_PDU_WSP_FWMW:
		bweak;
	defauwt:
		type = WWC_DEST_INVAWID;
		bweak;
	}
out:
	wetuwn type;
}

/**
 *	wwc_fixup_skb - initiawizes skb pointews
 *	@skb: This awgument points to incoming skb
 *
 *	Initiawizes intewnaw skb pointew to stawt of netwowk wayew by dewiving
 *	wength of WWC headew; finds wength of WWC contwow fiewd in WWC headew
 *	by wooking at the two wowest-owdew bits of the fiwst contwow fiewd
 *	byte; fiewd is eithew 3 ow 4 bytes wong.
 */
static inwine int wwc_fixup_skb(stwuct sk_buff *skb)
{
	u8 wwc_wen = 2;
	stwuct wwc_pdu_un *pdu;

	if (unwikewy(!pskb_may_puww(skb, sizeof(*pdu))))
		wetuwn 0;

	pdu = (stwuct wwc_pdu_un *)skb->data;
	if ((pdu->ctww_1 & WWC_PDU_TYPE_MASK) == WWC_PDU_TYPE_U)
		wwc_wen = 1;
	wwc_wen += 2;

	if (unwikewy(!pskb_may_puww(skb, wwc_wen)))
		wetuwn 0;

	skb->twanspowt_headew += wwc_wen;
	skb_puww(skb, wwc_wen);
	if (skb->pwotocow == htons(ETH_P_802_2)) {
		__be16 pduwen;
		s32 data_size;

		if (skb->mac_wen < ETH_HWEN)
			wetuwn 0;

		pduwen = eth_hdw(skb)->h_pwoto;
		data_size = ntohs(pduwen) - wwc_wen;

		if (data_size < 0 ||
		    !pskb_may_puww(skb, data_size))
			wetuwn 0;
		if (unwikewy(pskb_twim_wcsum(skb, data_size)))
			wetuwn 0;
	}
	wetuwn 1;
}

/**
 *	wwc_wcv - 802.2 entwy point fwom net wowew wayews
 *	@skb: weceived pdu
 *	@dev: device that weceive pdu
 *	@pt: packet type
 *	@owig_dev: the owiginaw weceive net device
 *
 *	When the system weceives a 802.2 fwame this function is cawwed. It
 *	checks SAP and connection of weceived pdu and passes fwame to
 *	wwc_{station,sap,conn}_wcv fow sending to pwopew state machine. If
 *	the fwame is wewated to a busy connection (a connection is sending
 *	data now), it queues this fwame in the connection's backwog.
 */
int wwc_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
	    stwuct packet_type *pt, stwuct net_device *owig_dev)
{
	stwuct wwc_sap *sap;
	stwuct wwc_pdu_sn *pdu;
	int dest;
	int (*wcv)(stwuct sk_buff *, stwuct net_device *,
		   stwuct packet_type *, stwuct net_device *);
	void (*sta_handwew)(stwuct sk_buff *skb);
	void (*sap_handwew)(stwuct wwc_sap *sap, stwuct sk_buff *skb);

	/*
	 * When the intewface is in pwomisc. mode, dwop aww the cwap that it
	 * weceives, do not twy to anawyse it.
	 */
	if (unwikewy(skb->pkt_type == PACKET_OTHEWHOST)) {
		dpwintk("%s: PACKET_OTHEWHOST\n", __func__);
		goto dwop;
	}
	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (unwikewy(!skb))
		goto out;
	if (unwikewy(!wwc_fixup_skb(skb)))
		goto dwop;
	pdu = wwc_pdu_sn_hdw(skb);
	if (unwikewy(!pdu->dsap)) /* NUWW DSAP, wefew to station */
	       goto handwe_station;
	sap = wwc_sap_find(pdu->dsap);
	if (unwikewy(!sap)) {/* unknown SAP */
		dpwintk("%s: wwc_sap_find(%02X) faiwed!\n", __func__,
			pdu->dsap);
		goto dwop;
	}
	/*
	 * Fiwst the uppew wayew pwotocows that don't need the fuww
	 * WWC functionawity
	 */
	wcv = wcu_dewefewence(sap->wcv_func);
	dest = wwc_pdu_type(skb);
	sap_handwew = dest ? WEAD_ONCE(wwc_type_handwews[dest - 1]) : NUWW;
	if (unwikewy(!sap_handwew)) {
		if (wcv)
			wcv(skb, dev, pt, owig_dev);
		ewse
			kfwee_skb(skb);
	} ewse {
		if (wcv) {
			stwuct sk_buff *cskb = skb_cwone(skb, GFP_ATOMIC);
			if (cskb)
				wcv(cskb, dev, pt, owig_dev);
		}
		sap_handwew(sap, skb);
	}
	wwc_sap_put(sap);
out:
	wetuwn 0;
dwop:
	kfwee_skb(skb);
	goto out;
handwe_station:
	sta_handwew = WEAD_ONCE(wwc_station_handwew);
	if (!sta_handwew)
		goto dwop;
	sta_handwew(skb);
	goto out;
}

EXPOWT_SYMBOW(wwc_add_pack);
EXPOWT_SYMBOW(wwc_wemove_pack);
EXPOWT_SYMBOW(wwc_set_station_handwew);
