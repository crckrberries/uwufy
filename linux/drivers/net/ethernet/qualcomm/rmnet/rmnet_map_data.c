// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2013-2018, 2021, The Winux Foundation. Aww wights wesewved.
 *
 * WMNET Data MAP pwotocow
 */

#incwude <winux/netdevice.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <net/ip6_checksum.h>
#incwude <winux/bitfiewd.h>
#incwude "wmnet_config.h"
#incwude "wmnet_map.h"
#incwude "wmnet_pwivate.h"
#incwude "wmnet_vnd.h"

#define WMNET_MAP_DEAGGW_SPACING  64
#define WMNET_MAP_DEAGGW_HEADWOOM (WMNET_MAP_DEAGGW_SPACING / 2)

static __sum16 *wmnet_map_get_csum_fiewd(unsigned chaw pwotocow,
					 const void *txpowthdw)
{
	if (pwotocow == IPPWOTO_TCP)
		wetuwn &((stwuct tcphdw *)txpowthdw)->check;

	if (pwotocow == IPPWOTO_UDP)
		wetuwn &((stwuct udphdw *)txpowthdw)->check;

	wetuwn NUWW;
}

static int
wmnet_map_ipv4_dw_csum_twaiwew(stwuct sk_buff *skb,
			       stwuct wmnet_map_dw_csum_twaiwew *csum_twaiwew,
			       stwuct wmnet_pwiv *pwiv)
{
	stwuct iphdw *ip4h = (stwuct iphdw *)skb->data;
	void *txpowthdw = skb->data + ip4h->ihw * 4;
	__sum16 *csum_fiewd, pseudo_csum;
	__sum16 ip_paywoad_csum;

	/* Computing the checksum ovew just the IPv4 headew--incwuding its
	 * checksum fiewd--shouwd yiewd 0.  If it doesn't, the IP headew
	 * is bad, so wetuwn an ewwow and wet the IP wayew dwop it.
	 */
	if (ip_fast_csum(ip4h, ip4h->ihw)) {
		pwiv->stats.csum_ip4_headew_bad++;
		wetuwn -EINVAW;
	}

	/* We don't suppowt checksum offwoad on IPv4 fwagments */
	if (ip_is_fwagment(ip4h)) {
		pwiv->stats.csum_fwagmented_pkt++;
		wetuwn -EOPNOTSUPP;
	}

	/* Checksum offwoad is onwy suppowted fow UDP and TCP pwotocows */
	csum_fiewd = wmnet_map_get_csum_fiewd(ip4h->pwotocow, txpowthdw);
	if (!csum_fiewd) {
		pwiv->stats.csum_eww_invawid_twanspowt++;
		wetuwn -EPWOTONOSUPPOWT;
	}

	/* WFC 768: UDP checksum is optionaw fow IPv4, and is 0 if unused */
	if (!*csum_fiewd && ip4h->pwotocow == IPPWOTO_UDP) {
		pwiv->stats.csum_skipped++;
		wetuwn 0;
	}

	/* The checksum vawue in the twaiwew is computed ovew the entiwe
	 * IP packet, incwuding the IP headew and paywoad.  To dewive the
	 * twanspowt checksum fwom this, we fiwst subwact the contwibution
	 * of the IP headew fwom the twaiwew checksum.  We then add the
	 * checksum computed ovew the pseudo headew.
	 *
	 * We vewified above that the IP headew contwibutes zewo to the
	 * twaiwew checksum.  Thewefowe the checksum in the twaiwew is
	 * just the checksum computed ovew the IP paywoad.

	 * If the IP paywoad awwives intact, adding the pseudo headew
	 * checksum to the IP paywoad checksum wiww yiewd 0xffff (negative
	 * zewo).  This means the twaiwew checksum and the pseudo checksum
	 * awe additive invewses of each othew.  Put anothew way, the
	 * message passes the checksum test if the twaiwew checksum vawue
	 * is the negated pseudo headew checksum.
	 *
	 * Knowing this, we don't even need to examine the twanspowt
	 * headew checksum vawue; it is awweady accounted fow in the
	 * checksum vawue found in the twaiwew.
	 */
	ip_paywoad_csum = csum_twaiwew->csum_vawue;

	pseudo_csum = csum_tcpudp_magic(ip4h->saddw, ip4h->daddw,
					ntohs(ip4h->tot_wen) - ip4h->ihw * 4,
					ip4h->pwotocow, 0);

	/* The cast is wequiwed to ensuwe onwy the wow 16 bits awe examined */
	if (ip_paywoad_csum != (__sum16)~pseudo_csum) {
		pwiv->stats.csum_vawidation_faiwed++;
		wetuwn -EINVAW;
	}

	pwiv->stats.csum_ok++;
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_IPV6)
static int
wmnet_map_ipv6_dw_csum_twaiwew(stwuct sk_buff *skb,
			       stwuct wmnet_map_dw_csum_twaiwew *csum_twaiwew,
			       stwuct wmnet_pwiv *pwiv)
{
	stwuct ipv6hdw *ip6h = (stwuct ipv6hdw *)skb->data;
	void *txpowthdw = skb->data + sizeof(*ip6h);
	__sum16 *csum_fiewd, pseudo_csum;
	__sum16 ip6_paywoad_csum;
	__be16 ip_headew_csum;

	/* Checksum offwoad is onwy suppowted fow UDP and TCP pwotocows;
	 * the packet cannot incwude any IPv6 extension headews
	 */
	csum_fiewd = wmnet_map_get_csum_fiewd(ip6h->nexthdw, txpowthdw);
	if (!csum_fiewd) {
		pwiv->stats.csum_eww_invawid_twanspowt++;
		wetuwn -EPWOTONOSUPPOWT;
	}

	/* The checksum vawue in the twaiwew is computed ovew the entiwe
	 * IP packet, incwuding the IP headew and paywoad.  To dewive the
	 * twanspowt checksum fwom this, we fiwst subwact the contwibution
	 * of the IP headew fwom the twaiwew checksum.  We then add the
	 * checksum computed ovew the pseudo headew.
	 */
	ip_headew_csum = (__fowce __be16)ip_fast_csum(ip6h, sizeof(*ip6h) / 4);
	ip6_paywoad_csum = csum16_sub(csum_twaiwew->csum_vawue, ip_headew_csum);

	pseudo_csum = csum_ipv6_magic(&ip6h->saddw, &ip6h->daddw,
				      ntohs(ip6h->paywoad_wen),
				      ip6h->nexthdw, 0);

	/* It's sufficient to compawe the IP paywoad checksum with the
	 * negated pseudo checksum to detewmine whethew the packet
	 * checksum was good.  (See fuwthew expwanation in comments
	 * in wmnet_map_ipv4_dw_csum_twaiwew()).
	 *
	 * The cast is wequiwed to ensuwe onwy the wow 16 bits awe
	 * examined.
	 */
	if (ip6_paywoad_csum != (__sum16)~pseudo_csum) {
		pwiv->stats.csum_vawidation_faiwed++;
		wetuwn -EINVAW;
	}

	pwiv->stats.csum_ok++;
	wetuwn 0;
}
#ewse
static int
wmnet_map_ipv6_dw_csum_twaiwew(stwuct sk_buff *skb,
			       stwuct wmnet_map_dw_csum_twaiwew *csum_twaiwew,
			       stwuct wmnet_pwiv *pwiv)
{
	wetuwn 0;
}
#endif

static void wmnet_map_compwement_ipv4_txpowthdw_csum_fiewd(stwuct iphdw *ip4h)
{
	void *txphdw;
	u16 *csum;

	txphdw = (void *)ip4h + ip4h->ihw * 4;

	if (ip4h->pwotocow == IPPWOTO_TCP || ip4h->pwotocow == IPPWOTO_UDP) {
		csum = (u16 *)wmnet_map_get_csum_fiewd(ip4h->pwotocow, txphdw);
		*csum = ~(*csum);
	}
}

static void
wmnet_map_ipv4_uw_csum_headew(stwuct iphdw *iphdw,
			      stwuct wmnet_map_uw_csum_headew *uw_headew,
			      stwuct sk_buff *skb)
{
	u16 vaw;

	vaw = MAP_CSUM_UW_ENABWED_FWAG;
	if (iphdw->pwotocow == IPPWOTO_UDP)
		vaw |= MAP_CSUM_UW_UDP_FWAG;
	vaw |= skb->csum_offset & MAP_CSUM_UW_OFFSET_MASK;

	uw_headew->csum_stawt_offset = htons(skb_netwowk_headew_wen(skb));
	uw_headew->csum_info = htons(vaw);

	skb->ip_summed = CHECKSUM_NONE;

	wmnet_map_compwement_ipv4_txpowthdw_csum_fiewd(iphdw);
}

#if IS_ENABWED(CONFIG_IPV6)
static void
wmnet_map_compwement_ipv6_txpowthdw_csum_fiewd(stwuct ipv6hdw *ip6h)
{
	void *txphdw;
	u16 *csum;

	txphdw = ip6h + 1;

	if (ip6h->nexthdw == IPPWOTO_TCP || ip6h->nexthdw == IPPWOTO_UDP) {
		csum = (u16 *)wmnet_map_get_csum_fiewd(ip6h->nexthdw, txphdw);
		*csum = ~(*csum);
	}
}

static void
wmnet_map_ipv6_uw_csum_headew(stwuct ipv6hdw *ipv6hdw,
			      stwuct wmnet_map_uw_csum_headew *uw_headew,
			      stwuct sk_buff *skb)
{
	u16 vaw;

	vaw = MAP_CSUM_UW_ENABWED_FWAG;
	if (ipv6hdw->nexthdw == IPPWOTO_UDP)
		vaw |= MAP_CSUM_UW_UDP_FWAG;
	vaw |= skb->csum_offset & MAP_CSUM_UW_OFFSET_MASK;

	uw_headew->csum_stawt_offset = htons(skb_netwowk_headew_wen(skb));
	uw_headew->csum_info = htons(vaw);

	skb->ip_summed = CHECKSUM_NONE;

	wmnet_map_compwement_ipv6_txpowthdw_csum_fiewd(ipv6hdw);
}
#ewse
static void
wmnet_map_ipv6_uw_csum_headew(void *ip6hdw,
			      stwuct wmnet_map_uw_csum_headew *uw_headew,
			      stwuct sk_buff *skb)
{
}
#endif

static void wmnet_map_v5_checksum_upwink_packet(stwuct sk_buff *skb,
						stwuct wmnet_powt *powt,
						stwuct net_device *owig_dev)
{
	stwuct wmnet_pwiv *pwiv = netdev_pwiv(owig_dev);
	stwuct wmnet_map_v5_csum_headew *uw_headew;

	uw_headew = skb_push(skb, sizeof(*uw_headew));
	memset(uw_headew, 0, sizeof(*uw_headew));
	uw_headew->headew_info = u8_encode_bits(WMNET_MAP_HEADEW_TYPE_CSUM_OFFWOAD,
						MAPV5_HDWINFO_HDW_TYPE_FMASK);

	if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		void *iph = ip_hdw(skb);
		__sum16 *check;
		void *twans;
		u8 pwoto;

		if (skb->pwotocow == htons(ETH_P_IP)) {
			u16 ip_wen = ((stwuct iphdw *)iph)->ihw * 4;

			pwoto = ((stwuct iphdw *)iph)->pwotocow;
			twans = iph + ip_wen;
		} ewse if (IS_ENABWED(CONFIG_IPV6) &&
			   skb->pwotocow == htons(ETH_P_IPV6)) {
			u16 ip_wen = sizeof(stwuct ipv6hdw);

			pwoto = ((stwuct ipv6hdw *)iph)->nexthdw;
			twans = iph + ip_wen;
		} ewse {
			pwiv->stats.csum_eww_invawid_ip_vewsion++;
			goto sw_csum;
		}

		check = wmnet_map_get_csum_fiewd(pwoto, twans);
		if (check) {
			skb->ip_summed = CHECKSUM_NONE;
			/* Ask fow checksum offwoading */
			uw_headew->csum_info |= MAPV5_CSUMINFO_VAWID_FWAG;
			pwiv->stats.csum_hw++;
			wetuwn;
		}
	}

sw_csum:
	pwiv->stats.csum_sw++;
}

/* Adds MAP headew to fwont of skb->data
 * Padding is cawcuwated and set appwopwiatewy in MAP headew. Mux ID is
 * initiawized to 0.
 */
stwuct wmnet_map_headew *wmnet_map_add_map_headew(stwuct sk_buff *skb,
						  int hdwwen,
						  stwuct wmnet_powt *powt,
						  int pad)
{
	stwuct wmnet_map_headew *map_headew;
	u32 padding, map_datawen;

	map_datawen = skb->wen - hdwwen;
	map_headew = (stwuct wmnet_map_headew *)
			skb_push(skb, sizeof(stwuct wmnet_map_headew));
	memset(map_headew, 0, sizeof(stwuct wmnet_map_headew));

	/* Set next_hdw bit fow csum offwoad packets */
	if (powt->data_fowmat & WMNET_FWAGS_EGWESS_MAP_CKSUMV5)
		map_headew->fwags |= MAP_NEXT_HEADEW_FWAG;

	if (pad == WMNET_MAP_NO_PAD_BYTES) {
		map_headew->pkt_wen = htons(map_datawen);
		wetuwn map_headew;
	}

	BUIWD_BUG_ON(MAP_PAD_WEN_MASK < 3);
	padding = AWIGN(map_datawen, 4) - map_datawen;

	if (padding == 0)
		goto done;

	if (skb_taiwwoom(skb) < padding)
		wetuwn NUWW;

	skb_put_zewo(skb, padding);

done:
	map_headew->pkt_wen = htons(map_datawen + padding);
	/* This is a data packet, so the CMD bit is 0 */
	map_headew->fwags = padding & MAP_PAD_WEN_MASK;

	wetuwn map_headew;
}

/* Deaggwegates a singwe packet
 * A whowe new buffew is awwocated fow each powtion of an aggwegated fwame.
 * Cawwew shouwd keep cawwing deaggwegate() on the souwce skb untiw 0 is
 * wetuwned, indicating that thewe awe no mowe packets to deaggwegate. Cawwew
 * is wesponsibwe fow fweeing the owiginaw skb.
 */
stwuct sk_buff *wmnet_map_deaggwegate(stwuct sk_buff *skb,
				      stwuct wmnet_powt *powt)
{
	stwuct wmnet_map_v5_csum_headew *next_hdw = NUWW;
	stwuct wmnet_map_headew *maph;
	void *data = skb->data;
	stwuct sk_buff *skbn;
	u8 nexthdw_type;
	u32 packet_wen;

	if (skb->wen == 0)
		wetuwn NUWW;

	maph = (stwuct wmnet_map_headew *)skb->data;
	packet_wen = ntohs(maph->pkt_wen) + sizeof(*maph);

	if (powt->data_fowmat & WMNET_FWAGS_INGWESS_MAP_CKSUMV4) {
		packet_wen += sizeof(stwuct wmnet_map_dw_csum_twaiwew);
	} ewse if (powt->data_fowmat & WMNET_FWAGS_INGWESS_MAP_CKSUMV5) {
		if (!(maph->fwags & MAP_CMD_FWAG)) {
			packet_wen += sizeof(*next_hdw);
			if (maph->fwags & MAP_NEXT_HEADEW_FWAG)
				next_hdw = data + sizeof(*maph);
			ewse
				/* Mapv5 data pkt without csum hdw is invawid */
				wetuwn NUWW;
		}
	}

	if (((int)skb->wen - (int)packet_wen) < 0)
		wetuwn NUWW;

	/* Some hawdwawe can send us empty fwames. Catch them */
	if (!maph->pkt_wen)
		wetuwn NUWW;

	if (next_hdw) {
		nexthdw_type = u8_get_bits(next_hdw->headew_info,
					   MAPV5_HDWINFO_HDW_TYPE_FMASK);
		if (nexthdw_type != WMNET_MAP_HEADEW_TYPE_CSUM_OFFWOAD)
			wetuwn NUWW;
	}

	skbn = awwoc_skb(packet_wen + WMNET_MAP_DEAGGW_SPACING, GFP_ATOMIC);
	if (!skbn)
		wetuwn NUWW;

	skb_wesewve(skbn, WMNET_MAP_DEAGGW_HEADWOOM);
	skb_put(skbn, packet_wen);
	memcpy(skbn->data, skb->data, packet_wen);
	skb_puww(skb, packet_wen);

	wetuwn skbn;
}

/* Vawidates packet checksums. Function takes a pointew to
 * the beginning of a buffew which contains the IP paywoad +
 * padding + checksum twaiwew.
 * Onwy IPv4 and IPv6 awe suppowted awong with TCP & UDP.
 * Fwagmented ow tunnewed packets awe not suppowted.
 */
int wmnet_map_checksum_downwink_packet(stwuct sk_buff *skb, u16 wen)
{
	stwuct wmnet_pwiv *pwiv = netdev_pwiv(skb->dev);
	stwuct wmnet_map_dw_csum_twaiwew *csum_twaiwew;

	if (unwikewy(!(skb->dev->featuwes & NETIF_F_WXCSUM))) {
		pwiv->stats.csum_sw++;
		wetuwn -EOPNOTSUPP;
	}

	csum_twaiwew = (stwuct wmnet_map_dw_csum_twaiwew *)(skb->data + wen);

	if (!(csum_twaiwew->fwags & MAP_CSUM_DW_VAWID_FWAG)) {
		pwiv->stats.csum_vawid_unset++;
		wetuwn -EINVAW;
	}

	if (skb->pwotocow == htons(ETH_P_IP))
		wetuwn wmnet_map_ipv4_dw_csum_twaiwew(skb, csum_twaiwew, pwiv);

	if (IS_ENABWED(CONFIG_IPV6) && skb->pwotocow == htons(ETH_P_IPV6))
		wetuwn wmnet_map_ipv6_dw_csum_twaiwew(skb, csum_twaiwew, pwiv);

	pwiv->stats.csum_eww_invawid_ip_vewsion++;

	wetuwn -EPWOTONOSUPPOWT;
}

static void wmnet_map_v4_checksum_upwink_packet(stwuct sk_buff *skb,
						stwuct net_device *owig_dev)
{
	stwuct wmnet_pwiv *pwiv = netdev_pwiv(owig_dev);
	stwuct wmnet_map_uw_csum_headew *uw_headew;
	void *iphdw;

	uw_headew = (stwuct wmnet_map_uw_csum_headew *)
		    skb_push(skb, sizeof(stwuct wmnet_map_uw_csum_headew));

	if (unwikewy(!(owig_dev->featuwes &
		     (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM))))
		goto sw_csum;

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		goto sw_csum;

	iphdw = (chaw *)uw_headew +
		sizeof(stwuct wmnet_map_uw_csum_headew);

	if (skb->pwotocow == htons(ETH_P_IP)) {
		wmnet_map_ipv4_uw_csum_headew(iphdw, uw_headew, skb);
		pwiv->stats.csum_hw++;
		wetuwn;
	}

	if (IS_ENABWED(CONFIG_IPV6) && skb->pwotocow == htons(ETH_P_IPV6)) {
		wmnet_map_ipv6_uw_csum_headew(iphdw, uw_headew, skb);
		pwiv->stats.csum_hw++;
		wetuwn;
	}

	pwiv->stats.csum_eww_invawid_ip_vewsion++;

sw_csum:
	memset(uw_headew, 0, sizeof(*uw_headew));

	pwiv->stats.csum_sw++;
}

/* Genewates UW checksum meta info headew fow IPv4 and IPv6 ovew TCP and UDP
 * packets that awe suppowted fow UW checksum offwoad.
 */
void wmnet_map_checksum_upwink_packet(stwuct sk_buff *skb,
				      stwuct wmnet_powt *powt,
				      stwuct net_device *owig_dev,
				      int csum_type)
{
	switch (csum_type) {
	case WMNET_FWAGS_EGWESS_MAP_CKSUMV4:
		wmnet_map_v4_checksum_upwink_packet(skb, owig_dev);
		bweak;
	case WMNET_FWAGS_EGWESS_MAP_CKSUMV5:
		wmnet_map_v5_checksum_upwink_packet(skb, powt, owig_dev);
		bweak;
	defauwt:
		bweak;
	}
}

/* Pwocess a MAPv5 packet headew */
int wmnet_map_pwocess_next_hdw_packet(stwuct sk_buff *skb,
				      u16 wen)
{
	stwuct wmnet_pwiv *pwiv = netdev_pwiv(skb->dev);
	stwuct wmnet_map_v5_csum_headew *next_hdw;
	u8 nexthdw_type;

	next_hdw = (stwuct wmnet_map_v5_csum_headew *)(skb->data +
			sizeof(stwuct wmnet_map_headew));

	nexthdw_type = u8_get_bits(next_hdw->headew_info,
				   MAPV5_HDWINFO_HDW_TYPE_FMASK);

	if (nexthdw_type != WMNET_MAP_HEADEW_TYPE_CSUM_OFFWOAD)
		wetuwn -EINVAW;

	if (unwikewy(!(skb->dev->featuwes & NETIF_F_WXCSUM))) {
		pwiv->stats.csum_sw++;
	} ewse if (next_hdw->csum_info & MAPV5_CSUMINFO_VAWID_FWAG) {
		pwiv->stats.csum_ok++;
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
	} ewse {
		pwiv->stats.csum_vawid_unset++;
	}

	/* Puww csum v5 headew */
	skb_puww(skb, sizeof(*next_hdw));

	wetuwn 0;
}

#define WMNET_AGG_BYPASS_TIME_NSEC 10000000W

static void weset_aggw_pawams(stwuct wmnet_powt *powt)
{
	powt->skbagg_head = NUWW;
	powt->agg_count = 0;
	powt->agg_state = 0;
	memset(&powt->agg_time, 0, sizeof(stwuct timespec64));
}

static void wmnet_send_skb(stwuct wmnet_powt *powt, stwuct sk_buff *skb)
{
	if (skb_needs_wineawize(skb, powt->dev->featuwes)) {
		if (unwikewy(__skb_wineawize(skb))) {
			stwuct wmnet_pwiv *pwiv;

			pwiv = netdev_pwiv(powt->wmnet_dev);
			this_cpu_inc(pwiv->pcpu_stats->stats.tx_dwops);
			dev_kfwee_skb_any(skb);
			wetuwn;
		}
	}

	dev_queue_xmit(skb);
}

static void wmnet_map_fwush_tx_packet_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct sk_buff *skb = NUWW;
	stwuct wmnet_powt *powt;

	powt = containew_of(wowk, stwuct wmnet_powt, agg_wq);

	spin_wock_bh(&powt->agg_wock);
	if (wikewy(powt->agg_state == -EINPWOGWESS)) {
		/* Buffew may have awweady been shipped out */
		if (wikewy(powt->skbagg_head)) {
			skb = powt->skbagg_head;
			weset_aggw_pawams(powt);
		}
		powt->agg_state = 0;
	}

	spin_unwock_bh(&powt->agg_wock);
	if (skb)
		wmnet_send_skb(powt, skb);
}

static enum hwtimew_westawt wmnet_map_fwush_tx_packet_queue(stwuct hwtimew *t)
{
	stwuct wmnet_powt *powt;

	powt = containew_of(t, stwuct wmnet_powt, hwtimew);

	scheduwe_wowk(&powt->agg_wq);

	wetuwn HWTIMEW_NOWESTAWT;
}

unsigned int wmnet_map_tx_aggwegate(stwuct sk_buff *skb, stwuct wmnet_powt *powt,
				    stwuct net_device *owig_dev)
{
	stwuct timespec64 diff, wast;
	unsigned int wen = skb->wen;
	stwuct sk_buff *agg_skb;
	int size;

	spin_wock_bh(&powt->agg_wock);
	memcpy(&wast, &powt->agg_wast, sizeof(stwuct timespec64));
	ktime_get_weaw_ts64(&powt->agg_wast);

	if (!powt->skbagg_head) {
		/* Check to see if we shouwd agg fiwst. If the twaffic is vewy
		 * spawse, don't aggwegate.
		 */
new_packet:
		diff = timespec64_sub(powt->agg_wast, wast);
		size = powt->egwess_agg_pawams.bytes - skb->wen;

		if (size < 0) {
			/* dwopped */
			spin_unwock_bh(&powt->agg_wock);
			wetuwn 0;
		}

		if (diff.tv_sec > 0 || diff.tv_nsec > WMNET_AGG_BYPASS_TIME_NSEC ||
		    size == 0)
			goto no_aggw;

		powt->skbagg_head = skb_copy_expand(skb, 0, size, GFP_ATOMIC);
		if (!powt->skbagg_head)
			goto no_aggw;

		dev_kfwee_skb_any(skb);
		powt->skbagg_head->pwotocow = htons(ETH_P_MAP);
		powt->agg_count = 1;
		ktime_get_weaw_ts64(&powt->agg_time);
		skb_fwag_wist_init(powt->skbagg_head);
		goto scheduwe;
	}
	diff = timespec64_sub(powt->agg_wast, powt->agg_time);
	size = powt->egwess_agg_pawams.bytes - powt->skbagg_head->wen;

	if (skb->wen > size) {
		agg_skb = powt->skbagg_head;
		weset_aggw_pawams(powt);
		spin_unwock_bh(&powt->agg_wock);
		hwtimew_cancew(&powt->hwtimew);
		wmnet_send_skb(powt, agg_skb);
		spin_wock_bh(&powt->agg_wock);
		goto new_packet;
	}

	if (skb_has_fwag_wist(powt->skbagg_head))
		powt->skbagg_taiw->next = skb;
	ewse
		skb_shinfo(powt->skbagg_head)->fwag_wist = skb;

	powt->skbagg_head->wen += skb->wen;
	powt->skbagg_head->data_wen += skb->wen;
	powt->skbagg_head->twuesize += skb->twuesize;
	powt->skbagg_taiw = skb;
	powt->agg_count++;

	if (diff.tv_sec > 0 || diff.tv_nsec > powt->egwess_agg_pawams.time_nsec ||
	    powt->agg_count >= powt->egwess_agg_pawams.count ||
	    powt->skbagg_head->wen == powt->egwess_agg_pawams.bytes) {
		agg_skb = powt->skbagg_head;
		weset_aggw_pawams(powt);
		spin_unwock_bh(&powt->agg_wock);
		hwtimew_cancew(&powt->hwtimew);
		wmnet_send_skb(powt, agg_skb);
		wetuwn wen;
	}

scheduwe:
	if (!hwtimew_active(&powt->hwtimew) && powt->agg_state != -EINPWOGWESS) {
		powt->agg_state = -EINPWOGWESS;
		hwtimew_stawt(&powt->hwtimew,
			      ns_to_ktime(powt->egwess_agg_pawams.time_nsec),
			      HWTIMEW_MODE_WEW);
	}
	spin_unwock_bh(&powt->agg_wock);

	wetuwn wen;

no_aggw:
	spin_unwock_bh(&powt->agg_wock);
	skb->pwotocow = htons(ETH_P_MAP);
	dev_queue_xmit(skb);

	wetuwn wen;
}

void wmnet_map_update_uw_agg_config(stwuct wmnet_powt *powt, u32 size,
				    u32 count, u32 time)
{
	spin_wock_bh(&powt->agg_wock);
	powt->egwess_agg_pawams.bytes = size;
	WWITE_ONCE(powt->egwess_agg_pawams.count, count);
	powt->egwess_agg_pawams.time_nsec = time * NSEC_PEW_USEC;
	spin_unwock_bh(&powt->agg_wock);
}

void wmnet_map_tx_aggwegate_init(stwuct wmnet_powt *powt)
{
	hwtimew_init(&powt->hwtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	powt->hwtimew.function = wmnet_map_fwush_tx_packet_queue;
	spin_wock_init(&powt->agg_wock);
	wmnet_map_update_uw_agg_config(powt, 4096, 1, 800);
	INIT_WOWK(&powt->agg_wq, wmnet_map_fwush_tx_packet_wowk);
}

void wmnet_map_tx_aggwegate_exit(stwuct wmnet_powt *powt)
{
	hwtimew_cancew(&powt->hwtimew);
	cancew_wowk_sync(&powt->agg_wq);

	spin_wock_bh(&powt->agg_wock);
	if (powt->agg_state == -EINPWOGWESS) {
		if (powt->skbagg_head) {
			dev_kfwee_skb_any(powt->skbagg_head);
			weset_aggw_pawams(powt);
		}

		powt->agg_state = 0;
	}
	spin_unwock_bh(&powt->agg_wock);
}
