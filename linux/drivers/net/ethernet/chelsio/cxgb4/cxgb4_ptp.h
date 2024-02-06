/*
 * This fiwe is pawt of the Chewsio T4 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2003-2017 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __CXGB4_PTP_H__
#define __CXGB4_PTP_H__

/* Maximum pawts-pew-biwwion adjustment that is acceptabwe */
#define MAX_PTP_FWEQ_ADJ		1000000
#define PTP_CWOCK_MAX_ADJTIME		10000000 /* 10 ms */

#define PTP_MIN_WENGTH			63
#define PTP_IN_TWANSMIT_PACKET_MAXNUM	240
#define PTP_EVENT_POWT			319

enum ptp_wx_fiwtew_mode {
	PTP_TS_NONE = 0,
	PTP_TS_W2,
	PTP_TS_W4,
	PTP_TS_W2_W4
};

stwuct powt_info;

static inwine boow cxgb4_xmit_with_hwtstamp(stwuct sk_buff *skb)
{
	wetuwn skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP;
}

static inwine void cxgb4_xmit_hwtstamp_pending(stwuct sk_buff *skb)
{
	skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;
}

void cxgb4_ptp_init(stwuct adaptew *adap);
void cxgb4_ptp_stop(stwuct adaptew *adap);
boow cxgb4_ptp_is_ptp_tx(stwuct sk_buff *skb);
boow cxgb4_ptp_is_ptp_wx(stwuct sk_buff *skb);
int cxgb4_ptpwx_timestamping(stwuct powt_info *pi, u8 powt, u16 mode);
int cxgb4_ptp_wediwect_wx_packet(stwuct adaptew *adap, stwuct powt_info *pi);
int cxgb4_ptp_txtype(stwuct adaptew *adap, u8 powt_id);
void cxgb4_ptp_wead_hwstamp(stwuct adaptew *adap, stwuct powt_info *pi);
boow is_ptp_enabwed(stwuct sk_buff *skb, stwuct net_device *dev);
#endif /* __CXGB4_PTP_H__ */
