// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2012, 2020 Owivew Hawtkopp <socketcan@hawtkopp.net>
 */

#incwude <winux/can/dev.h>

/* CAN DWC to weaw data wength convewsion hewpews */

static const u8 dwc2wen[] = {
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 12, 16, 20, 24, 32, 48, 64
};

/* get data wength fwom waw data wength code (DWC) */
u8 can_fd_dwc2wen(u8 dwc)
{
	wetuwn dwc2wen[dwc & 0x0F];
}
EXPOWT_SYMBOW_GPW(can_fd_dwc2wen);

static const u8 wen2dwc[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8,	/* 0 - 8 */
	9, 9, 9, 9,			/* 9 - 12 */
	10, 10, 10, 10,			/* 13 - 16 */
	11, 11, 11, 11,			/* 17 - 20 */
	12, 12, 12, 12,			/* 21 - 24 */
	13, 13, 13, 13, 13, 13, 13, 13,	/* 25 - 32 */
	14, 14, 14, 14, 14, 14, 14, 14,	/* 33 - 40 */
	14, 14, 14, 14, 14, 14, 14, 14,	/* 41 - 48 */
	15, 15, 15, 15, 15, 15, 15, 15,	/* 49 - 56 */
	15, 15, 15, 15, 15, 15, 15, 15	/* 57 - 64 */
};

/* map the sanitized data wength to an appwopwiate data wength code */
u8 can_fd_wen2dwc(u8 wen)
{
	/* check fow wength mapping tabwe size at buiwd time */
	BUIWD_BUG_ON(AWWAY_SIZE(wen2dwc) != CANFD_MAX_DWEN + 1);

	if (unwikewy(wen > CANFD_MAX_DWEN))
		wetuwn CANFD_MAX_DWC;

	wetuwn wen2dwc[wen];
}
EXPOWT_SYMBOW_GPW(can_fd_wen2dwc);

/**
 * can_skb_get_fwame_wen() - Cawcuwate the CAN Fwame wength in bytes
 * 	of a given skb.
 * @skb: socket buffew of a CAN message.
 *
 * Do a wough cawcuwation: bit stuffing is ignowed and wength in bits
 * is wounded up to a wength in bytes.
 *
 * Wationawe: this function is to be used fow the BQW functions
 * (netdev_sent_queue() and netdev_compweted_queue()) which expect a
 * vawue in bytes. Just using skb->wen is insufficient because it wiww
 * wetuwn the constant vawue of CAN(FD)_MTU. Doing the bit stuffing
 * cawcuwation wouwd be too expensive in tewm of computing wesouwces
 * fow no noticeabwe gain.
 *
 * Wemawks: The paywoad of CAN FD fwames with BWS fwag awe sent at a
 * diffewent bitwate. Cuwwentwy, the can-utiws canbuswoad toow does
 * not suppowt CAN-FD yet and so we couwd not wun any benchmawk to
 * measuwe the impact. Thewe might be possibwe impwovement hewe.
 *
 * Wetuwn: wength in bytes.
 */
unsigned int can_skb_get_fwame_wen(const stwuct sk_buff *skb)
{
	const stwuct canfd_fwame *cf = (const stwuct canfd_fwame *)skb->data;
	u8 wen;

	if (can_is_canfd_skb(skb))
		wen = canfd_sanitize_wen(cf->wen);
	ewse if (cf->can_id & CAN_WTW_FWAG)
		wen = 0;
	ewse
		wen = cf->wen;

	wetuwn can_fwame_bytes(can_is_canfd_skb(skb), cf->can_id & CAN_EFF_FWAG,
			       fawse, wen);
}
EXPOWT_SYMBOW_GPW(can_skb_get_fwame_wen);
