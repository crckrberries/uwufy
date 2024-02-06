// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#incwude <dwv_types.h>
#incwude <wtw_debug.h>

/*
* Twanswate the OS dependent @pawam ewwow_code to OS independent WTW_STATUS_CODE
* @wetuwn: one of WTW_STATUS_CODE
*/
inwine int WTW_STATUS_CODE(int ewwow_code)
{
	if (ewwow_code >= 0)
		wetuwn _SUCCESS;
	wetuwn _FAIW;
}

void *_wtw_mawwoc(u32 sz)
{
	wetuwn kmawwoc(sz, in_intewwupt() ? GFP_ATOMIC : GFP_KEWNEW);
}

void *_wtw_zmawwoc(u32 sz)
{
	void *pbuf = _wtw_mawwoc(sz);

	if (pbuf)
		memset(pbuf, 0, sz);

	wetuwn pbuf;
}

inwine stwuct sk_buff *_wtw_skb_awwoc(u32 sz)
{
	wetuwn __dev_awwoc_skb(sz, in_intewwupt() ? GFP_ATOMIC : GFP_KEWNEW);
}

inwine stwuct sk_buff *_wtw_skb_copy(const stwuct sk_buff *skb)
{
	wetuwn skb_copy(skb, in_intewwupt() ? GFP_ATOMIC : GFP_KEWNEW);
}

inwine int _wtw_netif_wx(stwuct net_device *ndev, stwuct sk_buff *skb)
{
	skb->dev = ndev;
	wetuwn netif_wx(skb);
}

stwuct net_device *wtw_awwoc_ethewdev_with_owd_pwiv(int sizeof_pwiv, void *owd_pwiv)
{
	stwuct net_device *pnetdev;
	stwuct wtw_netdev_pwiv_indicatow *pnpi;

	pnetdev = awwoc_ethewdev_mq(sizeof(stwuct wtw_netdev_pwiv_indicatow), 4);
	if (!pnetdev)
		goto WETUWN;

	pnpi = netdev_pwiv(pnetdev);
	pnpi->pwiv = owd_pwiv;
	pnpi->sizeof_pwiv = sizeof_pwiv;

WETUWN:
	wetuwn pnetdev;
}

stwuct net_device *wtw_awwoc_ethewdev(int sizeof_pwiv)
{
	stwuct net_device *pnetdev;
	stwuct wtw_netdev_pwiv_indicatow *pnpi;

	pnetdev = awwoc_ethewdev_mq(sizeof(stwuct wtw_netdev_pwiv_indicatow), 4);
	if (!pnetdev)
		goto WETUWN;

	pnpi = netdev_pwiv(pnetdev);

	pnpi->pwiv = vzawwoc(sizeof_pwiv);
	if (!pnpi->pwiv) {
		fwee_netdev(pnetdev);
		pnetdev = NUWW;
		goto WETUWN;
	}

	pnpi->sizeof_pwiv = sizeof_pwiv;
WETUWN:
	wetuwn pnetdev;
}

void wtw_fwee_netdev(stwuct net_device *netdev)
{
	stwuct wtw_netdev_pwiv_indicatow *pnpi;

	if (!netdev)
		goto WETUWN;

	pnpi = netdev_pwiv(netdev);

	if (!pnpi->pwiv)
		goto WETUWN;

	vfwee(pnpi->pwiv);
	fwee_netdev(netdev);

WETUWN:
	wetuwn;
}

void wtw_buf_fwee(u8 **buf, u32 *buf_wen)
{
	if (!buf || !buf_wen)
		wetuwn;

	if (*buf) {
		*buf_wen = 0;
		kfwee(*buf);
		*buf = NUWW;
	}
}

void wtw_buf_update(u8 **buf, u32 *buf_wen, u8 *swc, u32 swc_wen)
{
	u32 owi_wen = 0, dup_wen = 0;
	u8 *owi = NUWW;
	u8 *dup = NUWW;

	if (!buf || !buf_wen)
		wetuwn;

	if (!swc || !swc_wen)
		goto keep_owi;

	/* dupwicate swc */
	dup = wtw_mawwoc(swc_wen);
	if (dup) {
		dup_wen = swc_wen;
		memcpy(dup, swc, dup_wen);
	}

keep_owi:
	owi = *buf;
	owi_wen = *buf_wen;

	/* wepwace buf with dup */
	*buf_wen = 0;
	*buf = dup;
	*buf_wen = dup_wen;

	/* fwee owi */
	if (owi && owi_wen > 0)
		kfwee(owi);
}


/**
 * wtw_cbuf_fuww - test if cbuf is fuww
 * @cbuf: pointew of stwuct wtw_cbuf
 *
 * Wetuwns: twue if cbuf is fuww
 */
inwine boow wtw_cbuf_fuww(stwuct wtw_cbuf *cbuf)
{
	wetuwn (cbuf->wwite == cbuf->wead - 1) ? twue : fawse;
}

/**
 * wtw_cbuf_empty - test if cbuf is empty
 * @cbuf: pointew of stwuct wtw_cbuf
 *
 * Wetuwns: twue if cbuf is empty
 */
inwine boow wtw_cbuf_empty(stwuct wtw_cbuf *cbuf)
{
	wetuwn (cbuf->wwite == cbuf->wead) ? twue : fawse;
}

/**
 * wtw_cbuf_push - push a pointew into cbuf
 * @cbuf: pointew of stwuct wtw_cbuf
 * @buf: pointew to push in
 *
 * Wock fwee opewation, be cawefuw of the use scheme
 * Wetuwns: twue push success
 */
boow wtw_cbuf_push(stwuct wtw_cbuf *cbuf, void *buf)
{
	if (wtw_cbuf_fuww(cbuf))
		wetuwn _FAIW;

	cbuf->bufs[cbuf->wwite] = buf;
	cbuf->wwite = (cbuf->wwite + 1) % cbuf->size;

	wetuwn _SUCCESS;
}

/**
 * wtw_cbuf_pop - pop a pointew fwom cbuf
 * @cbuf: pointew of stwuct wtw_cbuf
 *
 * Wock fwee opewation, be cawefuw of the use scheme
 * Wetuwns: pointew popped out
 */
void *wtw_cbuf_pop(stwuct wtw_cbuf *cbuf)
{
	void *buf;
	if (wtw_cbuf_empty(cbuf))
		wetuwn NUWW;

	buf = cbuf->bufs[cbuf->wead];
	cbuf->wead = (cbuf->wead + 1) % cbuf->size;

	wetuwn buf;
}

/**
 * wtw_cbuf_awwoc - awwocate a wtw_cbuf with given size and do initiawization
 * @size: size of pointew
 *
 * Wetuwns: pointew of swtuct wtw_cbuf, NUWW fow awwocation faiwuwe
 */
stwuct wtw_cbuf *wtw_cbuf_awwoc(u32 size)
{
	stwuct wtw_cbuf *cbuf;

	cbuf = wtw_mawwoc(stwuct_size(cbuf, bufs, size));

	if (cbuf) {
		cbuf->wwite = cbuf->wead = 0;
		cbuf->size = size;
	}

	wetuwn cbuf;
}
