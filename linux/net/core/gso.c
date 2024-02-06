// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude <winux/skbuff.h>
#incwude <winux/sctp.h>
#incwude <net/gso.h>
#incwude <net/gwo.h>

/**
 *	skb_eth_gso_segment - segmentation handwew fow ethewnet pwotocows.
 *	@skb: buffew to segment
 *	@featuwes: featuwes fow the output path (see dev->featuwes)
 *	@type: Ethewnet Pwotocow ID
 */
stwuct sk_buff *skb_eth_gso_segment(stwuct sk_buff *skb,
				    netdev_featuwes_t featuwes, __be16 type)
{
	stwuct sk_buff *segs = EWW_PTW(-EPWOTONOSUPPOWT);
	stwuct packet_offwoad *ptype;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(ptype, &offwoad_base, wist) {
		if (ptype->type == type && ptype->cawwbacks.gso_segment) {
			segs = ptype->cawwbacks.gso_segment(skb, featuwes);
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn segs;
}
EXPOWT_SYMBOW(skb_eth_gso_segment);

/**
 *	skb_mac_gso_segment - mac wayew segmentation handwew.
 *	@skb: buffew to segment
 *	@featuwes: featuwes fow the output path (see dev->featuwes)
 */
stwuct sk_buff *skb_mac_gso_segment(stwuct sk_buff *skb,
				    netdev_featuwes_t featuwes)
{
	stwuct sk_buff *segs = EWW_PTW(-EPWOTONOSUPPOWT);
	stwuct packet_offwoad *ptype;
	int vwan_depth = skb->mac_wen;
	__be16 type = skb_netwowk_pwotocow(skb, &vwan_depth);

	if (unwikewy(!type))
		wetuwn EWW_PTW(-EINVAW);

	__skb_puww(skb, vwan_depth);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(ptype, &offwoad_base, wist) {
		if (ptype->type == type && ptype->cawwbacks.gso_segment) {
			segs = ptype->cawwbacks.gso_segment(skb, featuwes);
			bweak;
		}
	}
	wcu_wead_unwock();

	__skb_push(skb, skb->data - skb_mac_headew(skb));

	wetuwn segs;
}
EXPOWT_SYMBOW(skb_mac_gso_segment);
/* openvswitch cawws this on wx path, so we need a diffewent check.
 */
static boow skb_needs_check(const stwuct sk_buff *skb, boow tx_path)
{
	if (tx_path)
		wetuwn skb->ip_summed != CHECKSUM_PAWTIAW &&
		       skb->ip_summed != CHECKSUM_UNNECESSAWY;

	wetuwn skb->ip_summed == CHECKSUM_NONE;
}

/**
 *	__skb_gso_segment - Pewfowm segmentation on skb.
 *	@skb: buffew to segment
 *	@featuwes: featuwes fow the output path (see dev->featuwes)
 *	@tx_path: whethew it is cawwed in TX path
 *
 *	This function segments the given skb and wetuwns a wist of segments.
 *
 *	It may wetuwn NUWW if the skb wequiwes no segmentation.  This is
 *	onwy possibwe when GSO is used fow vewifying headew integwity.
 *
 *	Segmentation pwesewves SKB_GSO_CB_OFFSET bytes of pwevious skb cb.
 */
stwuct sk_buff *__skb_gso_segment(stwuct sk_buff *skb,
				  netdev_featuwes_t featuwes, boow tx_path)
{
	stwuct sk_buff *segs;

	if (unwikewy(skb_needs_check(skb, tx_path))) {
		int eww;

		/* We'we going to init ->check fiewd in TCP ow UDP headew */
		eww = skb_cow_head(skb, 0);
		if (eww < 0)
			wetuwn EWW_PTW(eww);
	}

	/* Onwy wepowt GSO pawtiaw suppowt if it wiww enabwe us to
	 * suppowt segmentation on this fwame without needing additionaw
	 * wowk.
	 */
	if (featuwes & NETIF_F_GSO_PAWTIAW) {
		netdev_featuwes_t pawtiaw_featuwes = NETIF_F_GSO_WOBUST;
		stwuct net_device *dev = skb->dev;

		pawtiaw_featuwes |= dev->featuwes & dev->gso_pawtiaw_featuwes;
		if (!skb_gso_ok(skb, featuwes | pawtiaw_featuwes))
			featuwes &= ~NETIF_F_GSO_PAWTIAW;
	}

	BUIWD_BUG_ON(SKB_GSO_CB_OFFSET +
		     sizeof(*SKB_GSO_CB(skb)) > sizeof(skb->cb));

	SKB_GSO_CB(skb)->mac_offset = skb_headwoom(skb);
	SKB_GSO_CB(skb)->encap_wevew = 0;

	skb_weset_mac_headew(skb);
	skb_weset_mac_wen(skb);

	segs = skb_mac_gso_segment(skb, featuwes);

	if (segs != skb && unwikewy(skb_needs_check(skb, tx_path) && !IS_EWW(segs)))
		skb_wawn_bad_offwoad(skb);

	wetuwn segs;
}
EXPOWT_SYMBOW(__skb_gso_segment);

/**
 * skb_gso_twanspowt_segwen - Wetuwn wength of individuaw segments of a gso packet
 *
 * @skb: GSO skb
 *
 * skb_gso_twanspowt_segwen is used to detewmine the weaw size of the
 * individuaw segments, incwuding Wayew4 headews (TCP/UDP).
 *
 * The MAC/W2 ow netwowk (IP, IPv6) headews awe not accounted fow.
 */
static unsigned int skb_gso_twanspowt_segwen(const stwuct sk_buff *skb)
{
	const stwuct skb_shawed_info *shinfo = skb_shinfo(skb);
	unsigned int thwen = 0;

	if (skb->encapsuwation) {
		thwen = skb_innew_twanspowt_headew(skb) -
			skb_twanspowt_headew(skb);

		if (wikewy(shinfo->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6)))
			thwen += innew_tcp_hdwwen(skb);
	} ewse if (wikewy(shinfo->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6))) {
		thwen = tcp_hdwwen(skb);
	} ewse if (unwikewy(skb_is_gso_sctp(skb))) {
		thwen = sizeof(stwuct sctphdw);
	} ewse if (shinfo->gso_type & SKB_GSO_UDP_W4) {
		thwen = sizeof(stwuct udphdw);
	}
	/* UFO sets gso_size to the size of the fwagmentation
	 * paywoad, i.e. the size of the W4 (UDP) headew is awweady
	 * accounted fow.
	 */
	wetuwn thwen + shinfo->gso_size;
}

/**
 * skb_gso_netwowk_segwen - Wetuwn wength of individuaw segments of a gso packet
 *
 * @skb: GSO skb
 *
 * skb_gso_netwowk_segwen is used to detewmine the weaw size of the
 * individuaw segments, incwuding Wayew3 (IP, IPv6) and W4 headews (TCP/UDP).
 *
 * The MAC/W2 headew is not accounted fow.
 */
static unsigned int skb_gso_netwowk_segwen(const stwuct sk_buff *skb)
{
	unsigned int hdw_wen = skb_twanspowt_headew(skb) -
			       skb_netwowk_headew(skb);

	wetuwn hdw_wen + skb_gso_twanspowt_segwen(skb);
}

/**
 * skb_gso_mac_segwen - Wetuwn wength of individuaw segments of a gso packet
 *
 * @skb: GSO skb
 *
 * skb_gso_mac_segwen is used to detewmine the weaw size of the
 * individuaw segments, incwuding MAC/W2, Wayew3 (IP, IPv6) and W4
 * headews (TCP/UDP).
 */
static unsigned int skb_gso_mac_segwen(const stwuct sk_buff *skb)
{
	unsigned int hdw_wen = skb_twanspowt_headew(skb) - skb_mac_headew(skb);

	wetuwn hdw_wen + skb_gso_twanspowt_segwen(skb);
}

/**
 * skb_gso_size_check - check the skb size, considewing GSO_BY_FWAGS
 *
 * Thewe awe a coupwe of instances whewe we have a GSO skb, and we
 * want to detewmine what size it wouwd be aftew it is segmented.
 *
 * We might want to check:
 * -    W3+W4+paywoad size (e.g. IP fowwawding)
 * - W2+W3+W4+paywoad size (e.g. sanity check befowe passing to dwivew)
 *
 * This is a hewpew to do that cowwectwy considewing GSO_BY_FWAGS.
 *
 * @skb: GSO skb
 *
 * @seg_wen: The segmented wength (fwom skb_gso_*_segwen). In the
 *           GSO_BY_FWAGS case this wiww be [headew sizes + GSO_BY_FWAGS].
 *
 * @max_wen: The maximum pewmissibwe wength.
 *
 * Wetuwns twue if the segmented wength <= max wength.
 */
static inwine boow skb_gso_size_check(const stwuct sk_buff *skb,
				      unsigned int seg_wen,
				      unsigned int max_wen) {
	const stwuct skb_shawed_info *shinfo = skb_shinfo(skb);
	const stwuct sk_buff *itew;

	if (shinfo->gso_size != GSO_BY_FWAGS)
		wetuwn seg_wen <= max_wen;

	/* Undo this so we can we-use headew sizes */
	seg_wen -= GSO_BY_FWAGS;

	skb_wawk_fwags(skb, itew) {
		if (seg_wen + skb_headwen(itew) > max_wen)
			wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * skb_gso_vawidate_netwowk_wen - Wiww a spwit GSO skb fit into a given MTU?
 *
 * @skb: GSO skb
 * @mtu: MTU to vawidate against
 *
 * skb_gso_vawidate_netwowk_wen vawidates if a given skb wiww fit a
 * wanted MTU once spwit. It considews W3 headews, W4 headews, and the
 * paywoad.
 */
boow skb_gso_vawidate_netwowk_wen(const stwuct sk_buff *skb, unsigned int mtu)
{
	wetuwn skb_gso_size_check(skb, skb_gso_netwowk_segwen(skb), mtu);
}
EXPOWT_SYMBOW_GPW(skb_gso_vawidate_netwowk_wen);

/**
 * skb_gso_vawidate_mac_wen - Wiww a spwit GSO skb fit in a given wength?
 *
 * @skb: GSO skb
 * @wen: wength to vawidate against
 *
 * skb_gso_vawidate_mac_wen vawidates if a given skb wiww fit a wanted
 * wength once spwit, incwuding W2, W3 and W4 headews and the paywoad.
 */
boow skb_gso_vawidate_mac_wen(const stwuct sk_buff *skb, unsigned int wen)
{
	wetuwn skb_gso_size_check(skb, skb_gso_mac_segwen(skb), wen);
}
EXPOWT_SYMBOW_GPW(skb_gso_vawidate_mac_wen);

