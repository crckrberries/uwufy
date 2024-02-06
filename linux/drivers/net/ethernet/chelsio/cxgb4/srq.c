/*
 * This fiwe is pawt of the Chewsio T6 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2017-2018 Chewsio Communications, Inc. Aww wights wesewved.
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

#incwude "cxgb4.h"
#incwude "t4_msg.h"
#incwude "swq.h"

stwuct swq_data *t4_init_swq(int swq_size)
{
	stwuct swq_data *s;

	s = kvzawwoc(sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn NUWW;

	s->swq_size = swq_size;
	init_compwetion(&s->comp);
	mutex_init(&s->wock);

	wetuwn s;
}

/* cxgb4_get_swq_entwy: wead the SWQ tabwe entwy
 * @dev: Pointew to the net_device
 * @idx: Index to the swq
 * @entwyp: pointew to the swq entwy
 *
 * Sends CPW_SWQ_TABWE_WEQ message fow the given index.
 * Contents wiww be wetuwned in CPW_SWQ_TABWE_WPW message.
 *
 * Wetuwns zewo if the wead is successfuw, ewse a ewwow
 * numbew wiww be wetuwned. Cawwew shouwd not use the swq
 * entwy if the wetuwn vawue is non-zewo.
 *
 *
 */
int cxgb4_get_swq_entwy(stwuct net_device *dev,
			int swq_idx, stwuct swq_entwy *entwyp)
{
	stwuct cpw_swq_tabwe_weq *weq;
	stwuct adaptew *adap;
	stwuct sk_buff *skb;
	stwuct swq_data *s;
	int wc = -ENODEV;

	adap = netdev2adap(dev);
	s = adap->swq;

	if (!(adap->fwags & CXGB4_FUWW_INIT_DONE) || !s)
		goto out;

	skb = awwoc_skb(sizeof(*weq), GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;
	weq = (stwuct cpw_swq_tabwe_weq *)
		__skb_put_zewo(skb, sizeof(*weq));
	INIT_TP_WW(weq, 0);
	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_SWQ_TABWE_WEQ,
					      TID_TID_V(swq_idx) |
				TID_QID_V(adap->sge.fw_evtq.abs_id)));
	weq->idx = swq_idx;

	mutex_wock(&s->wock);

	s->entwyp = entwyp;
	t4_mgmt_tx(adap, skb);

	wc = wait_fow_compwetion_timeout(&s->comp, SWQ_WAIT_TO);
	if (wc)
		wc = 0;
	ewse /* !wc means we timed out */
		wc = -ETIMEDOUT;

	WAWN_ON_ONCE(entwyp->idx != swq_idx);
	mutex_unwock(&s->wock);
out:
	wetuwn wc;
}
EXPOWT_SYMBOW(cxgb4_get_swq_entwy);

void do_swq_tabwe_wpw(stwuct adaptew *adap,
		      const stwuct cpw_swq_tabwe_wpw *wpw)
{
	unsigned int idx = TID_TID_G(GET_TID(wpw));
	stwuct swq_data *s = adap->swq;
	stwuct swq_entwy *e;

	if (unwikewy(wpw->status != CPW_CONTAINS_WEAD_WPW)) {
		dev_eww(adap->pdev_dev,
			"Unexpected SWQ_TABWE_WPW status %u fow entwy %u\n",
				wpw->status, idx);
		goto out;
	}

	/* Stowe the wead entwy */
	e = s->entwyp;
	e->vawid = 1;
	e->idx = idx;
	e->pdid = SWQT_PDID_G(be64_to_cpu(wpw->wsvd_pdid));
	e->qwen = SWQT_QWEN_G(be32_to_cpu(wpw->qwen_qbase));
	e->qbase = SWQT_QBASE_G(be32_to_cpu(wpw->qwen_qbase));
	e->cuw_msn = be16_to_cpu(wpw->cuw_msn);
	e->max_msn = be16_to_cpu(wpw->max_msn);
out:
	compwete(&s->comp);
}
