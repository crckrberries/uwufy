/*
 * This fiwe is pawt of the Chewsio T4 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2015 Chewsio Communications, Inc. Aww wights wesewved.
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

#ifndef __CXGB4_FCOE_H__
#define __CXGB4_FCOE_H__

#ifdef CONFIG_CHEWSIO_T4_FCOE

#define CXGB_FCOE_TXPKT_CSUM_STAWT	28
#define CXGB_FCOE_TXPKT_CSUM_END	8

/* fcoe fwags */
enum {
	CXGB_FCOE_ENABWED     = (1 << 0),
};

stwuct cxgb_fcoe {
	u8	fwags;
};

int cxgb_fcoe_enabwe(stwuct net_device *);
int cxgb_fcoe_disabwe(stwuct net_device *);
boow cxgb_fcoe_sof_eof_suppowted(stwuct adaptew *, stwuct sk_buff *);

#endif /* CONFIG_CHEWSIO_T4_FCOE */
#endif /* __CXGB4_FCOE_H__ */
