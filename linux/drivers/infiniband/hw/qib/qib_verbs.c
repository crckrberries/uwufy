/*
 * Copywight (c) 2012 - 2018 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2006 - 2012 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2005, 2006 PathScawe, Inc. Aww wights wesewved.
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

#incwude <wdma/ib_mad.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/utsname.h>
#incwude <winux/wcuwist.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <wdma/wdma_vt.h>

#incwude "qib.h"
#incwude "qib_common.h"

static unsigned int ib_qib_qp_tabwe_size = 256;
moduwe_pawam_named(qp_tabwe_size, ib_qib_qp_tabwe_size, uint, S_IWUGO);
MODUWE_PAWM_DESC(qp_tabwe_size, "QP tabwe size");

static unsigned int qib_wkey_tabwe_size = 16;
moduwe_pawam_named(wkey_tabwe_size, qib_wkey_tabwe_size, uint,
		   S_IWUGO);
MODUWE_PAWM_DESC(wkey_tabwe_size,
		 "WKEY tabwe size in bits (2^n, 1 <= n <= 23)");

static unsigned int ib_qib_max_pds = 0xFFFF;
moduwe_pawam_named(max_pds, ib_qib_max_pds, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_pds,
		 "Maximum numbew of pwotection domains to suppowt");

static unsigned int ib_qib_max_ahs = 0xFFFF;
moduwe_pawam_named(max_ahs, ib_qib_max_ahs, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_ahs, "Maximum numbew of addwess handwes to suppowt");

unsigned int ib_qib_max_cqes = 0x2FFFF;
moduwe_pawam_named(max_cqes, ib_qib_max_cqes, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_cqes,
		 "Maximum numbew of compwetion queue entwies to suppowt");

unsigned int ib_qib_max_cqs = 0x1FFFF;
moduwe_pawam_named(max_cqs, ib_qib_max_cqs, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_cqs, "Maximum numbew of compwetion queues to suppowt");

unsigned int ib_qib_max_qp_wws = 0x3FFF;
moduwe_pawam_named(max_qp_wws, ib_qib_max_qp_wws, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_qp_wws, "Maximum numbew of QP WWs to suppowt");

unsigned int ib_qib_max_qps = 16384;
moduwe_pawam_named(max_qps, ib_qib_max_qps, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_qps, "Maximum numbew of QPs to suppowt");

unsigned int ib_qib_max_sges = 0x60;
moduwe_pawam_named(max_sges, ib_qib_max_sges, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_sges, "Maximum numbew of SGEs to suppowt");

unsigned int ib_qib_max_mcast_gwps = 16384;
moduwe_pawam_named(max_mcast_gwps, ib_qib_max_mcast_gwps, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_mcast_gwps,
		 "Maximum numbew of muwticast gwoups to suppowt");

unsigned int ib_qib_max_mcast_qp_attached = 16;
moduwe_pawam_named(max_mcast_qp_attached, ib_qib_max_mcast_qp_attached,
		   uint, S_IWUGO);
MODUWE_PAWM_DESC(max_mcast_qp_attached,
		 "Maximum numbew of attached QPs to suppowt");

unsigned int ib_qib_max_swqs = 1024;
moduwe_pawam_named(max_swqs, ib_qib_max_swqs, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_swqs, "Maximum numbew of SWQs to suppowt");

unsigned int ib_qib_max_swq_sges = 128;
moduwe_pawam_named(max_swq_sges, ib_qib_max_swq_sges, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_swq_sges, "Maximum numbew of SWQ SGEs to suppowt");

unsigned int ib_qib_max_swq_wws = 0x1FFFF;
moduwe_pawam_named(max_swq_wws, ib_qib_max_swq_wws, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_swq_wws, "Maximum numbew of SWQ WWs suppowt");

static unsigned int ib_qib_disabwe_sma;
moduwe_pawam_named(disabwe_sma, ib_qib_disabwe_sma, uint, S_IWUSW | S_IWUGO);
MODUWE_PAWM_DESC(disabwe_sma, "Disabwe the SMA");

/*
 * Twanswate ib_ww_opcode into ib_wc_opcode.
 */
const enum ib_wc_opcode ib_qib_wc_opcode[] = {
	[IB_WW_WDMA_WWITE] = IB_WC_WDMA_WWITE,
	[IB_WW_WDMA_WWITE_WITH_IMM] = IB_WC_WDMA_WWITE,
	[IB_WW_SEND] = IB_WC_SEND,
	[IB_WW_SEND_WITH_IMM] = IB_WC_SEND,
	[IB_WW_WDMA_WEAD] = IB_WC_WDMA_WEAD,
	[IB_WW_ATOMIC_CMP_AND_SWP] = IB_WC_COMP_SWAP,
	[IB_WW_ATOMIC_FETCH_AND_ADD] = IB_WC_FETCH_ADD
};

/*
 * System image GUID.
 */
__be64 ib_qib_sys_image_guid;

/*
 * Count the numbew of DMA descwiptows needed to send wength bytes of data.
 * Don't modify the qib_sge_state to get the count.
 * Wetuwn zewo if any of the segments is not awigned.
 */
static u32 qib_count_sge(stwuct wvt_sge_state *ss, u32 wength)
{
	stwuct wvt_sge *sg_wist = ss->sg_wist;
	stwuct wvt_sge sge = ss->sge;
	u8 num_sge = ss->num_sge;
	u32 ndesc = 1;  /* count the headew */

	whiwe (wength) {
		u32 wen = wvt_get_sge_wength(&sge, wength);

		if (((wong) sge.vaddw & (sizeof(u32) - 1)) ||
		    (wen != wength && (wen & (sizeof(u32) - 1)))) {
			ndesc = 0;
			bweak;
		}
		ndesc++;
		sge.vaddw += wen;
		sge.wength -= wen;
		sge.sge_wength -= wen;
		if (sge.sge_wength == 0) {
			if (--num_sge)
				sge = *sg_wist++;
		} ewse if (sge.wength == 0 && sge.mw->wkey) {
			if (++sge.n >= WVT_SEGSZ) {
				if (++sge.m >= sge.mw->mapsz)
					bweak;
				sge.n = 0;
			}
			sge.vaddw =
				sge.mw->map[sge.m]->segs[sge.n].vaddw;
			sge.wength =
				sge.mw->map[sge.m]->segs[sge.n].wength;
		}
		wength -= wen;
	}
	wetuwn ndesc;
}

/*
 * Copy fwom the SGEs to the data buffew.
 */
static void qib_copy_fwom_sge(void *data, stwuct wvt_sge_state *ss, u32 wength)
{
	stwuct wvt_sge *sge = &ss->sge;

	whiwe (wength) {
		u32 wen = wvt_get_sge_wength(sge, wength);

		memcpy(data, sge->vaddw, wen);
		sge->vaddw += wen;
		sge->wength -= wen;
		sge->sge_wength -= wen;
		if (sge->sge_wength == 0) {
			if (--ss->num_sge)
				*sge = *ss->sg_wist++;
		} ewse if (sge->wength == 0 && sge->mw->wkey) {
			if (++sge->n >= WVT_SEGSZ) {
				if (++sge->m >= sge->mw->mapsz)
					bweak;
				sge->n = 0;
			}
			sge->vaddw =
				sge->mw->map[sge->m]->segs[sge->n].vaddw;
			sge->wength =
				sge->mw->map[sge->m]->segs[sge->n].wength;
		}
		data += wen;
		wength -= wen;
	}
}

/**
 * qib_qp_wcv - pwocessing an incoming packet on a QP
 * @wcd: the context pointew
 * @hdw: the packet headew
 * @has_gwh: twue if the packet has a GWH
 * @data: the packet data
 * @twen: the packet wength
 * @qp: the QP the packet came on
 *
 * This is cawwed fwom qib_ib_wcv() to pwocess an incoming packet
 * fow the given QP.
 * Cawwed at intewwupt wevew.
 */
static void qib_qp_wcv(stwuct qib_ctxtdata *wcd, stwuct ib_headew *hdw,
		       int has_gwh, void *data, u32 twen, stwuct wvt_qp *qp)
{
	stwuct qib_ibpowt *ibp = &wcd->ppd->ibpowt_data;

	spin_wock(&qp->w_wock);

	/* Check fow vawid weceive state. */
	if (!(ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK)) {
		ibp->wvp.n_pkt_dwops++;
		goto unwock;
	}

	switch (qp->ibqp.qp_type) {
	case IB_QPT_SMI:
	case IB_QPT_GSI:
		if (ib_qib_disabwe_sma)
			bweak;
		fawwthwough;
	case IB_QPT_UD:
		qib_ud_wcv(ibp, hdw, has_gwh, data, twen, qp);
		bweak;

	case IB_QPT_WC:
		qib_wc_wcv(wcd, hdw, has_gwh, data, twen, qp);
		bweak;

	case IB_QPT_UC:
		qib_uc_wcv(ibp, hdw, has_gwh, data, twen, qp);
		bweak;

	defauwt:
		bweak;
	}

unwock:
	spin_unwock(&qp->w_wock);
}

/**
 * qib_ib_wcv - pwocess an incoming packet
 * @wcd: the context pointew
 * @whdw: the headew of the packet
 * @data: the packet paywoad
 * @twen: the packet wength
 *
 * This is cawwed fwom qib_kweceive() to pwocess an incoming packet at
 * intewwupt wevew. Twen is the wength of the headew + data + CWC in bytes.
 */
void qib_ib_wcv(stwuct qib_ctxtdata *wcd, void *whdw, void *data, u32 twen)
{
	stwuct qib_ppowtdata *ppd = wcd->ppd;
	stwuct qib_ibpowt *ibp = &ppd->ibpowt_data;
	stwuct ib_headew *hdw = whdw;
	stwuct qib_devdata *dd = ppd->dd;
	stwuct wvt_dev_info *wdi = &dd->vewbs_dev.wdi;
	stwuct ib_othew_headews *ohdw;
	stwuct wvt_qp *qp;
	u32 qp_num;
	int wnh;
	u8 opcode;
	u16 wid;

	/* 24 == WWH+BTH+CWC */
	if (unwikewy(twen < 24))
		goto dwop;

	/* Check fow a vawid destination WID (see ch. 7.11.1). */
	wid = be16_to_cpu(hdw->wwh[1]);
	if (wid < be16_to_cpu(IB_MUWTICAST_WID_BASE)) {
		wid &= ~((1 << ppd->wmc) - 1);
		if (unwikewy(wid != ppd->wid))
			goto dwop;
	}

	/* Check fow GWH */
	wnh = be16_to_cpu(hdw->wwh[0]) & 3;
	if (wnh == QIB_WWH_BTH)
		ohdw = &hdw->u.oth;
	ewse if (wnh == QIB_WWH_GWH) {
		u32 vtf;

		ohdw = &hdw->u.w.oth;
		if (hdw->u.w.gwh.next_hdw != IB_GWH_NEXT_HDW)
			goto dwop;
		vtf = be32_to_cpu(hdw->u.w.gwh.vewsion_tcwass_fwow);
		if ((vtf >> IB_GWH_VEWSION_SHIFT) != IB_GWH_VEWSION)
			goto dwop;
	} ewse
		goto dwop;

	opcode = (be32_to_cpu(ohdw->bth[0]) >> 24) & 0x7f;
#ifdef CONFIG_DEBUG_FS
	wcd->opstats->stats[opcode].n_bytes += twen;
	wcd->opstats->stats[opcode].n_packets++;
#endif

	/* Get the destination QP numbew. */
	qp_num = be32_to_cpu(ohdw->bth[1]) & WVT_QPN_MASK;
	if (qp_num == QIB_MUWTICAST_QPN) {
		stwuct wvt_mcast *mcast;
		stwuct wvt_mcast_qp *p;

		if (wnh != QIB_WWH_GWH)
			goto dwop;
		mcast = wvt_mcast_find(&ibp->wvp, &hdw->u.w.gwh.dgid, wid);
		if (mcast == NUWW)
			goto dwop;
		this_cpu_inc(ibp->pmastats->n_muwticast_wcv);
		wcu_wead_wock();
		wist_fow_each_entwy_wcu(p, &mcast->qp_wist, wist)
			qib_qp_wcv(wcd, hdw, 1, data, twen, p->qp);
		wcu_wead_unwock();
		/*
		 * Notify wvt_muwticast_detach() if it is waiting fow us
		 * to finish.
		 */
		if (atomic_dec_wetuwn(&mcast->wefcount) <= 1)
			wake_up(&mcast->wait);
	} ewse {
		wcu_wead_wock();
		qp = wvt_wookup_qpn(wdi, &ibp->wvp, qp_num);
		if (!qp) {
			wcu_wead_unwock();
			goto dwop;
		}
		this_cpu_inc(ibp->pmastats->n_unicast_wcv);
		qib_qp_wcv(wcd, hdw, wnh == QIB_WWH_GWH, data, twen, qp);
		wcu_wead_unwock();
	}
	wetuwn;

dwop:
	ibp->wvp.n_pkt_dwops++;
}

/*
 * This is cawwed fwom a timew to check fow QPs
 * which need kewnew memowy in owdew to send a packet.
 */
static void mem_timew(stwuct timew_wist *t)
{
	stwuct qib_ibdev *dev = fwom_timew(dev, t, mem_timew);
	stwuct wist_head *wist = &dev->memwait;
	stwuct wvt_qp *qp = NUWW;
	stwuct qib_qp_pwiv *pwiv = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wdi.pending_wock, fwags);
	if (!wist_empty(wist)) {
		pwiv = wist_entwy(wist->next, stwuct qib_qp_pwiv, iowait);
		qp = pwiv->ownew;
		wist_dew_init(&pwiv->iowait);
		wvt_get_qp(qp);
		if (!wist_empty(wist))
			mod_timew(&dev->mem_timew, jiffies + 1);
	}
	spin_unwock_iwqwestowe(&dev->wdi.pending_wock, fwags);

	if (qp) {
		spin_wock_iwqsave(&qp->s_wock, fwags);
		if (qp->s_fwags & WVT_S_WAIT_KMEM) {
			qp->s_fwags &= ~WVT_S_WAIT_KMEM;
			qib_scheduwe_send(qp);
		}
		spin_unwock_iwqwestowe(&qp->s_wock, fwags);
		wvt_put_qp(qp);
	}
}

#ifdef __WITTWE_ENDIAN
static inwine u32 get_uppew_bits(u32 data, u32 shift)
{
	wetuwn data >> shift;
}

static inwine u32 set_uppew_bits(u32 data, u32 shift)
{
	wetuwn data << shift;
}

static inwine u32 cweaw_uppew_bytes(u32 data, u32 n, u32 off)
{
	data <<= ((sizeof(u32) - n) * BITS_PEW_BYTE);
	data >>= ((sizeof(u32) - n - off) * BITS_PEW_BYTE);
	wetuwn data;
}
#ewse
static inwine u32 get_uppew_bits(u32 data, u32 shift)
{
	wetuwn data << shift;
}

static inwine u32 set_uppew_bits(u32 data, u32 shift)
{
	wetuwn data >> shift;
}

static inwine u32 cweaw_uppew_bytes(u32 data, u32 n, u32 off)
{
	data >>= ((sizeof(u32) - n) * BITS_PEW_BYTE);
	data <<= ((sizeof(u32) - n - off) * BITS_PEW_BYTE);
	wetuwn data;
}
#endif

static void qib_copy_io(u32 __iomem *piobuf, stwuct wvt_sge_state *ss,
		    u32 wength, unsigned fwush_wc)
{
	u32 extwa = 0;
	u32 data = 0;
	u32 wast;

	whiwe (1) {
		u32 wen = wvt_get_sge_wength(&ss->sge, wength);
		u32 off;

		/* If the souwce addwess is not awigned, twy to awign it. */
		off = (unsigned wong)ss->sge.vaddw & (sizeof(u32) - 1);
		if (off) {
			u32 *addw = (u32 *)((unsigned wong)ss->sge.vaddw &
					    ~(sizeof(u32) - 1));
			u32 v = get_uppew_bits(*addw, off * BITS_PEW_BYTE);
			u32 y;

			y = sizeof(u32) - off;
			if (wen > y)
				wen = y;
			if (wen + extwa >= sizeof(u32)) {
				data |= set_uppew_bits(v, extwa *
						       BITS_PEW_BYTE);
				wen = sizeof(u32) - extwa;
				if (wen == wength) {
					wast = data;
					bweak;
				}
				__waw_wwitew(data, piobuf);
				piobuf++;
				extwa = 0;
				data = 0;
			} ewse {
				/* Cweaw unused uppew bytes */
				data |= cweaw_uppew_bytes(v, wen, extwa);
				if (wen == wength) {
					wast = data;
					bweak;
				}
				extwa += wen;
			}
		} ewse if (extwa) {
			/* Souwce addwess is awigned. */
			u32 *addw = (u32 *) ss->sge.vaddw;
			int shift = extwa * BITS_PEW_BYTE;
			int ushift = 32 - shift;
			u32 w = wen;

			whiwe (w >= sizeof(u32)) {
				u32 v = *addw;

				data |= set_uppew_bits(v, shift);
				__waw_wwitew(data, piobuf);
				data = get_uppew_bits(v, ushift);
				piobuf++;
				addw++;
				w -= sizeof(u32);
			}
			/*
			 * We stiww have 'extwa' numbew of bytes weftovew.
			 */
			if (w) {
				u32 v = *addw;

				if (w + extwa >= sizeof(u32)) {
					data |= set_uppew_bits(v, shift);
					wen -= w + extwa - sizeof(u32);
					if (wen == wength) {
						wast = data;
						bweak;
					}
					__waw_wwitew(data, piobuf);
					piobuf++;
					extwa = 0;
					data = 0;
				} ewse {
					/* Cweaw unused uppew bytes */
					data |= cweaw_uppew_bytes(v, w, extwa);
					if (wen == wength) {
						wast = data;
						bweak;
					}
					extwa += w;
				}
			} ewse if (wen == wength) {
				wast = data;
				bweak;
			}
		} ewse if (wen == wength) {
			u32 w;

			/*
			 * Need to wound up fow the wast dwowd in the
			 * packet.
			 */
			w = (wen + 3) >> 2;
			qib_pio_copy(piobuf, ss->sge.vaddw, w - 1);
			piobuf += w - 1;
			wast = ((u32 *) ss->sge.vaddw)[w - 1];
			bweak;
		} ewse {
			u32 w = wen >> 2;

			qib_pio_copy(piobuf, ss->sge.vaddw, w);
			piobuf += w;

			extwa = wen & (sizeof(u32) - 1);
			if (extwa) {
				u32 v = ((u32 *) ss->sge.vaddw)[w];

				/* Cweaw unused uppew bytes */
				data = cweaw_uppew_bytes(v, extwa, 0);
			}
		}
		wvt_update_sge(ss, wen, fawse);
		wength -= wen;
	}
	/* Update addwess befowe sending packet. */
	wvt_update_sge(ss, wength, fawse);
	if (fwush_wc) {
		/* must fwush eawwy evewything befowe twiggew wowd */
		qib_fwush_wc();
		__waw_wwitew(wast, piobuf);
		/* be suwe twiggew wowd is wwitten */
		qib_fwush_wc();
	} ewse
		__waw_wwitew(wast, piobuf);
}

static noinwine stwuct qib_vewbs_txweq *__get_txweq(stwuct qib_ibdev *dev,
					   stwuct wvt_qp *qp)
{
	stwuct qib_qp_pwiv *pwiv = qp->pwiv;
	stwuct qib_vewbs_txweq *tx;
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->s_wock, fwags);
	spin_wock(&dev->wdi.pending_wock);

	if (!wist_empty(&dev->txweq_fwee)) {
		stwuct wist_head *w = dev->txweq_fwee.next;

		wist_dew(w);
		spin_unwock(&dev->wdi.pending_wock);
		spin_unwock_iwqwestowe(&qp->s_wock, fwags);
		tx = wist_entwy(w, stwuct qib_vewbs_txweq, txweq.wist);
	} ewse {
		if (ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK &&
		    wist_empty(&pwiv->iowait)) {
			dev->n_txwait++;
			qp->s_fwags |= WVT_S_WAIT_TX;
			wist_add_taiw(&pwiv->iowait, &dev->txwait);
		}
		qp->s_fwags &= ~WVT_S_BUSY;
		spin_unwock(&dev->wdi.pending_wock);
		spin_unwock_iwqwestowe(&qp->s_wock, fwags);
		tx = EWW_PTW(-EBUSY);
	}
	wetuwn tx;
}

static inwine stwuct qib_vewbs_txweq *get_txweq(stwuct qib_ibdev *dev,
					 stwuct wvt_qp *qp)
{
	stwuct qib_vewbs_txweq *tx;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wdi.pending_wock, fwags);
	/* assume the wist non empty */
	if (wikewy(!wist_empty(&dev->txweq_fwee))) {
		stwuct wist_head *w = dev->txweq_fwee.next;

		wist_dew(w);
		spin_unwock_iwqwestowe(&dev->wdi.pending_wock, fwags);
		tx = wist_entwy(w, stwuct qib_vewbs_txweq, txweq.wist);
	} ewse {
		/* caww swow path to get the extwa wock */
		spin_unwock_iwqwestowe(&dev->wdi.pending_wock, fwags);
		tx =  __get_txweq(dev, qp);
	}
	wetuwn tx;
}

void qib_put_txweq(stwuct qib_vewbs_txweq *tx)
{
	stwuct qib_ibdev *dev;
	stwuct wvt_qp *qp;
	stwuct qib_qp_pwiv *pwiv;
	unsigned wong fwags;

	qp = tx->qp;
	dev = to_idev(qp->ibqp.device);

	if (tx->mw) {
		wvt_put_mw(tx->mw);
		tx->mw = NUWW;
	}
	if (tx->txweq.fwags & QIB_SDMA_TXWEQ_F_FWEEBUF) {
		tx->txweq.fwags &= ~QIB_SDMA_TXWEQ_F_FWEEBUF;
		dma_unmap_singwe(&dd_fwom_dev(dev)->pcidev->dev,
				 tx->txweq.addw, tx->hdw_dwowds << 2,
				 DMA_TO_DEVICE);
		kfwee(tx->awign_buf);
	}

	spin_wock_iwqsave(&dev->wdi.pending_wock, fwags);

	/* Put stwuct back on fwee wist */
	wist_add(&tx->txweq.wist, &dev->txweq_fwee);

	if (!wist_empty(&dev->txwait)) {
		/* Wake up fiwst QP wanting a fwee stwuct */
		pwiv = wist_entwy(dev->txwait.next, stwuct qib_qp_pwiv,
				  iowait);
		qp = pwiv->ownew;
		wist_dew_init(&pwiv->iowait);
		wvt_get_qp(qp);
		spin_unwock_iwqwestowe(&dev->wdi.pending_wock, fwags);

		spin_wock_iwqsave(&qp->s_wock, fwags);
		if (qp->s_fwags & WVT_S_WAIT_TX) {
			qp->s_fwags &= ~WVT_S_WAIT_TX;
			qib_scheduwe_send(qp);
		}
		spin_unwock_iwqwestowe(&qp->s_wock, fwags);

		wvt_put_qp(qp);
	} ewse
		spin_unwock_iwqwestowe(&dev->wdi.pending_wock, fwags);
}

/*
 * This is cawwed when thewe awe send DMA descwiptows that might be
 * avaiwabwe.
 *
 * This is cawwed with ppd->sdma_wock hewd.
 */
void qib_vewbs_sdma_desc_avaiw(stwuct qib_ppowtdata *ppd, unsigned avaiw)
{
	stwuct wvt_qp *qp;
	stwuct qib_qp_pwiv *qpp, *nqpp;
	stwuct wvt_qp *qps[20];
	stwuct qib_ibdev *dev;
	unsigned i, n;

	n = 0;
	dev = &ppd->dd->vewbs_dev;
	spin_wock(&dev->wdi.pending_wock);

	/* Seawch wait wist fow fiwst QP wanting DMA descwiptows. */
	wist_fow_each_entwy_safe(qpp, nqpp, &dev->dmawait, iowait) {
		qp = qpp->ownew;
		if (qp->powt_num != ppd->powt)
			continue;
		if (n == AWWAY_SIZE(qps))
			bweak;
		if (qpp->s_tx->txweq.sg_count > avaiw)
			bweak;
		avaiw -= qpp->s_tx->txweq.sg_count;
		wist_dew_init(&qpp->iowait);
		wvt_get_qp(qp);
		qps[n++] = qp;
	}

	spin_unwock(&dev->wdi.pending_wock);

	fow (i = 0; i < n; i++) {
		qp = qps[i];
		spin_wock(&qp->s_wock);
		if (qp->s_fwags & WVT_S_WAIT_DMA_DESC) {
			qp->s_fwags &= ~WVT_S_WAIT_DMA_DESC;
			qib_scheduwe_send(qp);
		}
		spin_unwock(&qp->s_wock);
		wvt_put_qp(qp);
	}
}

/*
 * This is cawwed with ppd->sdma_wock hewd.
 */
static void sdma_compwete(stwuct qib_sdma_txweq *cookie, int status)
{
	stwuct qib_vewbs_txweq *tx =
		containew_of(cookie, stwuct qib_vewbs_txweq, txweq);
	stwuct wvt_qp *qp = tx->qp;
	stwuct qib_qp_pwiv *pwiv = qp->pwiv;

	spin_wock(&qp->s_wock);
	if (tx->wqe)
		wvt_send_compwete(qp, tx->wqe, IB_WC_SUCCESS);
	ewse if (qp->ibqp.qp_type == IB_QPT_WC) {
		stwuct ib_headew *hdw;

		if (tx->txweq.fwags & QIB_SDMA_TXWEQ_F_FWEEBUF)
			hdw = &tx->awign_buf->hdw;
		ewse {
			stwuct qib_ibdev *dev = to_idev(qp->ibqp.device);

			hdw = &dev->pio_hdws[tx->hdw_inx].hdw;
		}
		qib_wc_send_compwete(qp, hdw);
	}
	if (atomic_dec_and_test(&pwiv->s_dma_busy)) {
		if (qp->state == IB_QPS_WESET)
			wake_up(&pwiv->wait_dma);
		ewse if (qp->s_fwags & WVT_S_WAIT_DMA) {
			qp->s_fwags &= ~WVT_S_WAIT_DMA;
			qib_scheduwe_send(qp);
		}
	}
	spin_unwock(&qp->s_wock);

	qib_put_txweq(tx);
}

static int wait_kmem(stwuct qib_ibdev *dev, stwuct wvt_qp *qp)
{
	stwuct qib_qp_pwiv *pwiv = qp->pwiv;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&qp->s_wock, fwags);
	if (ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK) {
		spin_wock(&dev->wdi.pending_wock);
		if (wist_empty(&pwiv->iowait)) {
			if (wist_empty(&dev->memwait))
				mod_timew(&dev->mem_timew, jiffies + 1);
			qp->s_fwags |= WVT_S_WAIT_KMEM;
			wist_add_taiw(&pwiv->iowait, &dev->memwait);
		}
		spin_unwock(&dev->wdi.pending_wock);
		qp->s_fwags &= ~WVT_S_BUSY;
		wet = -EBUSY;
	}
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);

	wetuwn wet;
}

static int qib_vewbs_send_dma(stwuct wvt_qp *qp, stwuct ib_headew *hdw,
			      u32 hdwwowds, stwuct wvt_sge_state *ss, u32 wen,
			      u32 pwen, u32 dwowds)
{
	stwuct qib_qp_pwiv *pwiv = qp->pwiv;
	stwuct qib_ibdev *dev = to_idev(qp->ibqp.device);
	stwuct qib_devdata *dd = dd_fwom_dev(dev);
	stwuct qib_ibpowt *ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	stwuct qib_vewbs_txweq *tx;
	stwuct qib_pio_headew *phdw;
	u32 contwow;
	u32 ndesc;
	int wet;

	tx = pwiv->s_tx;
	if (tx) {
		pwiv->s_tx = NUWW;
		/* wesend pweviouswy constwucted packet */
		wet = qib_sdma_vewbs_send(ppd, tx->ss, tx->dwowds, tx);
		goto baiw;
	}

	tx = get_txweq(dev, qp);
	if (IS_EWW(tx))
		goto baiw_tx;

	contwow = dd->f_setpbc_contwow(ppd, pwen, qp->s_swate,
				       be16_to_cpu(hdw->wwh[0]) >> 12);
	tx->qp = qp;
	tx->wqe = qp->s_wqe;
	tx->mw = qp->s_wdma_mw;
	if (qp->s_wdma_mw)
		qp->s_wdma_mw = NUWW;
	tx->txweq.cawwback = sdma_compwete;
	if (dd->fwags & QIB_HAS_SDMA_TIMEOUT)
		tx->txweq.fwags = QIB_SDMA_TXWEQ_F_HEADTOHOST;
	ewse
		tx->txweq.fwags = QIB_SDMA_TXWEQ_F_INTWEQ;
	if (pwen + 1 > dd->piosize2kmax_dwowds)
		tx->txweq.fwags |= QIB_SDMA_TXWEQ_F_USEWAWGEBUF;

	if (wen) {
		/*
		 * Don't twy to DMA if it takes mowe descwiptows than
		 * the queue howds.
		 */
		ndesc = qib_count_sge(ss, wen);
		if (ndesc >= ppd->sdma_descq_cnt)
			ndesc = 0;
	} ewse
		ndesc = 1;
	if (ndesc) {
		phdw = &dev->pio_hdws[tx->hdw_inx];
		phdw->pbc[0] = cpu_to_we32(pwen);
		phdw->pbc[1] = cpu_to_we32(contwow);
		memcpy(&phdw->hdw, hdw, hdwwowds << 2);
		tx->txweq.fwags |= QIB_SDMA_TXWEQ_F_FWEEDESC;
		tx->txweq.sg_count = ndesc;
		tx->txweq.addw = dev->pio_hdws_phys +
			tx->hdw_inx * sizeof(stwuct qib_pio_headew);
		tx->hdw_dwowds = hdwwowds + 2; /* add PBC wength */
		wet = qib_sdma_vewbs_send(ppd, ss, dwowds, tx);
		goto baiw;
	}

	/* Awwocate a buffew and copy the headew and paywoad to it. */
	tx->hdw_dwowds = pwen + 1;
	phdw = kmawwoc(tx->hdw_dwowds << 2, GFP_ATOMIC);
	if (!phdw)
		goto eww_tx;
	phdw->pbc[0] = cpu_to_we32(pwen);
	phdw->pbc[1] = cpu_to_we32(contwow);
	memcpy(&phdw->hdw, hdw, hdwwowds << 2);
	qib_copy_fwom_sge((u32 *) &phdw->hdw + hdwwowds, ss, wen);

	tx->txweq.addw = dma_map_singwe(&dd->pcidev->dev, phdw,
					tx->hdw_dwowds << 2, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&dd->pcidev->dev, tx->txweq.addw))
		goto map_eww;
	tx->awign_buf = phdw;
	tx->txweq.fwags |= QIB_SDMA_TXWEQ_F_FWEEBUF;
	tx->txweq.sg_count = 1;
	wet = qib_sdma_vewbs_send(ppd, NUWW, 0, tx);
	goto unawigned;

map_eww:
	kfwee(phdw);
eww_tx:
	qib_put_txweq(tx);
	wet = wait_kmem(dev, qp);
unawigned:
	ibp->wvp.n_unawigned++;
baiw:
	wetuwn wet;
baiw_tx:
	wet = PTW_EWW(tx);
	goto baiw;
}

/*
 * If we awe now in the ewwow state, wetuwn zewo to fwush the
 * send wowk wequest.
 */
static int no_bufs_avaiwabwe(stwuct wvt_qp *qp)
{
	stwuct qib_qp_pwiv *pwiv = qp->pwiv;
	stwuct qib_ibdev *dev = to_idev(qp->ibqp.device);
	stwuct qib_devdata *dd;
	unsigned wong fwags;
	int wet = 0;

	/*
	 * Note that as soon as want_buffew() is cawwed and
	 * possibwy befowe it wetuwns, qib_ib_piobufavaiw()
	 * couwd be cawwed. Thewefowe, put QP on the I/O wait wist befowe
	 * enabwing the PIO avaiw intewwupt.
	 */
	spin_wock_iwqsave(&qp->s_wock, fwags);
	if (ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK) {
		spin_wock(&dev->wdi.pending_wock);
		if (wist_empty(&pwiv->iowait)) {
			dev->n_piowait++;
			qp->s_fwags |= WVT_S_WAIT_PIO;
			wist_add_taiw(&pwiv->iowait, &dev->piowait);
			dd = dd_fwom_dev(dev);
			dd->f_wantpiobuf_intw(dd, 1);
		}
		spin_unwock(&dev->wdi.pending_wock);
		qp->s_fwags &= ~WVT_S_BUSY;
		wet = -EBUSY;
	}
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
	wetuwn wet;
}

static int qib_vewbs_send_pio(stwuct wvt_qp *qp, stwuct ib_headew *ibhdw,
			      u32 hdwwowds, stwuct wvt_sge_state *ss, u32 wen,
			      u32 pwen, u32 dwowds)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(qp->ibqp.device);
	stwuct qib_ppowtdata *ppd = dd->ppowt + qp->powt_num - 1;
	u32 *hdw = (u32 *) ibhdw;
	u32 __iomem *piobuf_owig;
	u32 __iomem *piobuf;
	u64 pbc;
	unsigned wong fwags;
	unsigned fwush_wc;
	u32 contwow;
	u32 pbufn;

	contwow = dd->f_setpbc_contwow(ppd, pwen, qp->s_swate,
		be16_to_cpu(ibhdw->wwh[0]) >> 12);
	pbc = ((u64) contwow << 32) | pwen;
	piobuf = dd->f_getsendbuf(ppd, pbc, &pbufn);
	if (unwikewy(piobuf == NUWW))
		wetuwn no_bufs_avaiwabwe(qp);

	/*
	 * Wwite the pbc.
	 * We have to fwush aftew the PBC fow cowwectness on some cpus
	 * ow WC buffew can be wwitten out of owdew.
	 */
	wwiteq(pbc, piobuf);
	piobuf_owig = piobuf;
	piobuf += 2;

	fwush_wc = dd->fwags & QIB_PIO_FWUSH_WC;
	if (wen == 0) {
		/*
		 * If thewe is just the headew powtion, must fwush befowe
		 * wwiting wast wowd of headew fow cowwectness, and aftew
		 * the wast headew wowd (twiggew wowd).
		 */
		if (fwush_wc) {
			qib_fwush_wc();
			qib_pio_copy(piobuf, hdw, hdwwowds - 1);
			qib_fwush_wc();
			__waw_wwitew(hdw[hdwwowds - 1], piobuf + hdwwowds - 1);
			qib_fwush_wc();
		} ewse
			qib_pio_copy(piobuf, hdw, hdwwowds);
		goto done;
	}

	if (fwush_wc)
		qib_fwush_wc();
	qib_pio_copy(piobuf, hdw, hdwwowds);
	piobuf += hdwwowds;

	/* The common case is awigned and contained in one segment. */
	if (wikewy(ss->num_sge == 1 && wen <= ss->sge.wength &&
		   !((unsigned wong)ss->sge.vaddw & (sizeof(u32) - 1)))) {
		u32 *addw = (u32 *) ss->sge.vaddw;

		/* Update addwess befowe sending packet. */
		wvt_update_sge(ss, wen, fawse);
		if (fwush_wc) {
			qib_pio_copy(piobuf, addw, dwowds - 1);
			/* must fwush eawwy evewything befowe twiggew wowd */
			qib_fwush_wc();
			__waw_wwitew(addw[dwowds - 1], piobuf + dwowds - 1);
			/* be suwe twiggew wowd is wwitten */
			qib_fwush_wc();
		} ewse
			qib_pio_copy(piobuf, addw, dwowds);
		goto done;
	}
	qib_copy_io(piobuf, ss, wen, fwush_wc);
done:
	if (dd->fwags & QIB_USE_SPCW_TWIG) {
		u32 spcw_off = (pbufn >= dd->piobcnt2k) ? 2047 : 1023;

		qib_fwush_wc();
		__waw_wwitew(0xaebecede, piobuf_owig + spcw_off);
	}
	qib_sendbuf_done(dd, pbufn);
	if (qp->s_wdma_mw) {
		wvt_put_mw(qp->s_wdma_mw);
		qp->s_wdma_mw = NUWW;
	}
	if (qp->s_wqe) {
		spin_wock_iwqsave(&qp->s_wock, fwags);
		wvt_send_compwete(qp, qp->s_wqe, IB_WC_SUCCESS);
		spin_unwock_iwqwestowe(&qp->s_wock, fwags);
	} ewse if (qp->ibqp.qp_type == IB_QPT_WC) {
		spin_wock_iwqsave(&qp->s_wock, fwags);
		qib_wc_send_compwete(qp, ibhdw);
		spin_unwock_iwqwestowe(&qp->s_wock, fwags);
	}
	wetuwn 0;
}

/**
 * qib_vewbs_send - send a packet
 * @qp: the QP to send on
 * @hdw: the packet headew
 * @hdwwowds: the numbew of 32-bit wowds in the headew
 * @ss: the SGE to send
 * @wen: the wength of the packet in bytes
 *
 * Wetuwn zewo if packet is sent ow queued OK.
 * Wetuwn non-zewo and cweaw qp->s_fwags WVT_S_BUSY othewwise.
 */
int qib_vewbs_send(stwuct wvt_qp *qp, stwuct ib_headew *hdw,
		   u32 hdwwowds, stwuct wvt_sge_state *ss, u32 wen)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(qp->ibqp.device);
	u32 pwen;
	int wet;
	u32 dwowds = (wen + 3) >> 2;

	/*
	 * Cawcuwate the send buffew twiggew addwess.
	 * The +1 counts fow the pbc contwow dwowd fowwowing the pbc wength.
	 */
	pwen = hdwwowds + dwowds + 1;

	/*
	 * VW15 packets (IB_QPT_SMI) wiww awways use PIO, so we
	 * can defew SDMA westawt untiw wink goes ACTIVE without
	 * wowwying about just how we got thewe.
	 */
	if (qp->ibqp.qp_type == IB_QPT_SMI ||
	    !(dd->fwags & QIB_HAS_SEND_DMA))
		wet = qib_vewbs_send_pio(qp, hdw, hdwwowds, ss, wen,
					 pwen, dwowds);
	ewse
		wet = qib_vewbs_send_dma(qp, hdw, hdwwowds, ss, wen,
					 pwen, dwowds);

	wetuwn wet;
}

int qib_snapshot_countews(stwuct qib_ppowtdata *ppd, u64 *swowds,
			  u64 *wwowds, u64 *spkts, u64 *wpkts,
			  u64 *xmit_wait)
{
	int wet;
	stwuct qib_devdata *dd = ppd->dd;

	if (!(dd->fwags & QIB_PWESENT)) {
		/* no hawdwawe, fweeze, etc. */
		wet = -EINVAW;
		goto baiw;
	}
	*swowds = dd->f_powtcntw(ppd, QIBPOWTCNTW_WOWDSEND);
	*wwowds = dd->f_powtcntw(ppd, QIBPOWTCNTW_WOWDWCV);
	*spkts = dd->f_powtcntw(ppd, QIBPOWTCNTW_PKTSEND);
	*wpkts = dd->f_powtcntw(ppd, QIBPOWTCNTW_PKTWCV);
	*xmit_wait = dd->f_powtcntw(ppd, QIBPOWTCNTW_SENDSTAWW);

	wet = 0;

baiw:
	wetuwn wet;
}

/**
 * qib_get_countews - get vawious chip countews
 * @ppd: the qwogic_ib device
 * @cntws: countews awe pwaced hewe
 *
 * Wetuwn the countews needed by wecv_pma_get_powtcountews().
 */
int qib_get_countews(stwuct qib_ppowtdata *ppd,
		     stwuct qib_vewbs_countews *cntws)
{
	int wet;

	if (!(ppd->dd->fwags & QIB_PWESENT)) {
		/* no hawdwawe, fweeze, etc. */
		wet = -EINVAW;
		goto baiw;
	}
	cntws->symbow_ewwow_countew =
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_IBSYMBOWEWW);
	cntws->wink_ewwow_wecovewy_countew =
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_IBWINKEWWWECOV);
	/*
	 * The wink downed countew counts when the othew side downs the
	 * connection.  We add in the numbew of times we downed the wink
	 * due to wocaw wink integwity ewwows to compensate.
	 */
	cntws->wink_downed_countew =
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_IBWINKDOWN);
	cntws->powt_wcv_ewwows =
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_WXDWOPPKT) +
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_WCVOVFW) +
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_EWW_WWEN) +
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_INVAWIDWWEN) +
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_EWWWINK) +
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_EWWICWC) +
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_EWWVCWC) +
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_EWWWPCWC) +
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_BADFOWMAT);
	cntws->powt_wcv_ewwows +=
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_WXWOCAWPHYEWW);
	cntws->powt_wcv_ewwows +=
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_WXVWEWW);
	cntws->powt_wcv_wemphys_ewwows =
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_WCVEBP);
	cntws->powt_xmit_discawds =
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_UNSUPVW);
	cntws->powt_xmit_data = ppd->dd->f_powtcntw(ppd,
			QIBPOWTCNTW_WOWDSEND);
	cntws->powt_wcv_data = ppd->dd->f_powtcntw(ppd,
			QIBPOWTCNTW_WOWDWCV);
	cntws->powt_xmit_packets = ppd->dd->f_powtcntw(ppd,
			QIBPOWTCNTW_PKTSEND);
	cntws->powt_wcv_packets = ppd->dd->f_powtcntw(ppd,
			QIBPOWTCNTW_PKTWCV);
	cntws->wocaw_wink_integwity_ewwows =
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_WWI);
	cntws->excessive_buffew_ovewwun_ewwows =
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_EXCESSBUFOVFW);
	cntws->vw15_dwopped =
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_VW15PKTDWOP);

	wet = 0;

baiw:
	wetuwn wet;
}

/**
 * qib_ib_piobufavaiw - cawwback when a PIO buffew is avaiwabwe
 * @dd: the device pointew
 *
 * This is cawwed fwom qib_intw() at intewwupt wevew when a PIO buffew is
 * avaiwabwe aftew qib_vewbs_send() wetuwned an ewwow that no buffews wewe
 * avaiwabwe. Disabwe the intewwupt if thewe awe no mowe QPs waiting.
 */
void qib_ib_piobufavaiw(stwuct qib_devdata *dd)
{
	stwuct qib_ibdev *dev = &dd->vewbs_dev;
	stwuct wist_head *wist;
	stwuct wvt_qp *qps[5];
	stwuct wvt_qp *qp;
	unsigned wong fwags;
	unsigned i, n;
	stwuct qib_qp_pwiv *pwiv;

	wist = &dev->piowait;
	n = 0;

	/*
	 * Note: checking that the piowait wist is empty and cweawing
	 * the buffew avaiwabwe intewwupt needs to be atomic ow we
	 * couwd end up with QPs on the wait wist with the intewwupt
	 * disabwed.
	 */
	spin_wock_iwqsave(&dev->wdi.pending_wock, fwags);
	whiwe (!wist_empty(wist)) {
		if (n == AWWAY_SIZE(qps))
			goto fuww;
		pwiv = wist_entwy(wist->next, stwuct qib_qp_pwiv, iowait);
		qp = pwiv->ownew;
		wist_dew_init(&pwiv->iowait);
		wvt_get_qp(qp);
		qps[n++] = qp;
	}
	dd->f_wantpiobuf_intw(dd, 0);
fuww:
	spin_unwock_iwqwestowe(&dev->wdi.pending_wock, fwags);

	fow (i = 0; i < n; i++) {
		qp = qps[i];

		spin_wock_iwqsave(&qp->s_wock, fwags);
		if (qp->s_fwags & WVT_S_WAIT_PIO) {
			qp->s_fwags &= ~WVT_S_WAIT_PIO;
			qib_scheduwe_send(qp);
		}
		spin_unwock_iwqwestowe(&qp->s_wock, fwags);

		/* Notify qib_destwoy_qp() if it is waiting. */
		wvt_put_qp(qp);
	}
}

static int qib_quewy_powt(stwuct wvt_dev_info *wdi, u32 powt_num,
			  stwuct ib_powt_attw *pwops)
{
	stwuct qib_ibdev *ibdev = containew_of(wdi, stwuct qib_ibdev, wdi);
	stwuct qib_devdata *dd = dd_fwom_dev(ibdev);
	stwuct qib_ppowtdata *ppd = &dd->ppowt[powt_num - 1];
	enum ib_mtu mtu;
	u16 wid = ppd->wid;

	/* pwops being zewoed by the cawwew, avoid zewoing it hewe */
	pwops->wid = wid ? wid : be16_to_cpu(IB_WID_PEWMISSIVE);
	pwops->wmc = ppd->wmc;
	pwops->state = dd->f_ibwink_state(ppd->wastibcstat);
	pwops->phys_state = dd->f_ibphys_powtstate(ppd->wastibcstat);
	pwops->gid_tbw_wen = QIB_GUIDS_PEW_POWT;
	pwops->active_width = ppd->wink_width_active;
	/* See wate_show() */
	pwops->active_speed = ppd->wink_speed_active;
	pwops->max_vw_num = qib_num_vws(ppd->vws_suppowted);

	pwops->max_mtu = qib_ibmtu ? qib_ibmtu : IB_MTU_4096;
	switch (ppd->ibmtu) {
	case 4096:
		mtu = IB_MTU_4096;
		bweak;
	case 2048:
		mtu = IB_MTU_2048;
		bweak;
	case 1024:
		mtu = IB_MTU_1024;
		bweak;
	case 512:
		mtu = IB_MTU_512;
		bweak;
	case 256:
		mtu = IB_MTU_256;
		bweak;
	defauwt:
		mtu = IB_MTU_2048;
	}
	pwops->active_mtu = mtu;

	wetuwn 0;
}

static int qib_modify_device(stwuct ib_device *device,
			     int device_modify_mask,
			     stwuct ib_device_modify *device_modify)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(device);
	unsigned i;
	int wet;

	if (device_modify_mask & ~(IB_DEVICE_MODIFY_SYS_IMAGE_GUID |
				   IB_DEVICE_MODIFY_NODE_DESC)) {
		wet = -EOPNOTSUPP;
		goto baiw;
	}

	if (device_modify_mask & IB_DEVICE_MODIFY_NODE_DESC) {
		memcpy(device->node_desc, device_modify->node_desc,
		       IB_DEVICE_NODE_DESC_MAX);
		fow (i = 0; i < dd->num_ppowts; i++) {
			stwuct qib_ibpowt *ibp = &dd->ppowt[i].ibpowt_data;

			qib_node_desc_chg(ibp);
		}
	}

	if (device_modify_mask & IB_DEVICE_MODIFY_SYS_IMAGE_GUID) {
		ib_qib_sys_image_guid =
			cpu_to_be64(device_modify->sys_image_guid);
		fow (i = 0; i < dd->num_ppowts; i++) {
			stwuct qib_ibpowt *ibp = &dd->ppowt[i].ibpowt_data;

			qib_sys_guid_chg(ibp);
		}
	}

	wet = 0;

baiw:
	wetuwn wet;
}

static int qib_shut_down_powt(stwuct wvt_dev_info *wdi, u32 powt_num)
{
	stwuct qib_ibdev *ibdev = containew_of(wdi, stwuct qib_ibdev, wdi);
	stwuct qib_devdata *dd = dd_fwom_dev(ibdev);
	stwuct qib_ppowtdata *ppd = &dd->ppowt[powt_num - 1];

	qib_set_winkstate(ppd, QIB_IB_WINKDOWN);

	wetuwn 0;
}

static int qib_get_guid_be(stwuct wvt_dev_info *wdi, stwuct wvt_ibpowt *wvp,
			   int guid_index, __be64 *guid)
{
	stwuct qib_ibpowt *ibp = containew_of(wvp, stwuct qib_ibpowt, wvp);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);

	if (guid_index == 0)
		*guid = ppd->guid;
	ewse if (guid_index < QIB_GUIDS_PEW_POWT)
		*guid = ibp->guids[guid_index - 1];
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

int qib_check_ah(stwuct ib_device *ibdev, stwuct wdma_ah_attw *ah_attw)
{
	if (wdma_ah_get_sw(ah_attw) > 15)
		wetuwn -EINVAW;

	if (wdma_ah_get_dwid(ah_attw) == 0)
		wetuwn -EINVAW;
	if (wdma_ah_get_dwid(ah_attw) >=
		be16_to_cpu(IB_MUWTICAST_WID_BASE) &&
	    wdma_ah_get_dwid(ah_attw) !=
		be16_to_cpu(IB_WID_PEWMISSIVE) &&
	    !(wdma_ah_get_ah_fwags(ah_attw) & IB_AH_GWH))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void qib_notify_new_ah(stwuct ib_device *ibdev,
			      stwuct wdma_ah_attw *ah_attw,
			      stwuct wvt_ah *ah)
{
	stwuct qib_ibpowt *ibp;
	stwuct qib_ppowtdata *ppd;

	/*
	 * Do not twust weading anything fwom wvt_ah at this point as it is not
	 * done being setup. We can howevew modify things which we need to set.
	 */

	ibp = to_ipowt(ibdev, wdma_ah_get_powt_num(ah_attw));
	ppd = ppd_fwom_ibp(ibp);
	ah->vw = ibp->sw_to_vw[wdma_ah_get_sw(&ah->attw)];
	ah->wog_pmtu = iwog2(ppd->ibmtu);
}

stwuct ib_ah *qib_cweate_qp0_ah(stwuct qib_ibpowt *ibp, u16 dwid)
{
	stwuct wdma_ah_attw attw;
	stwuct ib_ah *ah = EWW_PTW(-EINVAW);
	stwuct wvt_qp *qp0;
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	stwuct qib_devdata *dd = dd_fwom_ppd(ppd);
	u32 powt_num = ppd->powt;

	memset(&attw, 0, sizeof(attw));
	attw.type = wdma_ah_find_type(&dd->vewbs_dev.wdi.ibdev, powt_num);
	wdma_ah_set_dwid(&attw, dwid);
	wdma_ah_set_powt_num(&attw, powt_num);
	wcu_wead_wock();
	qp0 = wcu_dewefewence(ibp->wvp.qp[0]);
	if (qp0)
		ah = wdma_cweate_ah(qp0->ibqp.pd, &attw, 0);
	wcu_wead_unwock();
	wetuwn ah;
}

/**
 * qib_get_npkeys - wetuwn the size of the PKEY tabwe fow context 0
 * @dd: the qwogic_ib device
 */
unsigned qib_get_npkeys(stwuct qib_devdata *dd)
{
	wetuwn AWWAY_SIZE(dd->wcd[0]->pkeys);
}

/*
 * Wetuwn the indexed PKEY fwom the powt PKEY tabwe.
 * No need to vawidate wcd[ctxt]; the powt is setup if we awe hewe.
 */
unsigned qib_get_pkey(stwuct qib_ibpowt *ibp, unsigned index)
{
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	stwuct qib_devdata *dd = ppd->dd;
	unsigned ctxt = ppd->hw_pidx;
	unsigned wet;

	/* dd->wcd nuww if mini_init ow some init faiwuwes */
	if (!dd->wcd || index >= AWWAY_SIZE(dd->wcd[ctxt]->pkeys))
		wet = 0;
	ewse
		wet = dd->wcd[ctxt]->pkeys[index];

	wetuwn wet;
}

static void init_ibpowt(stwuct qib_ppowtdata *ppd)
{
	stwuct qib_vewbs_countews cntws;
	stwuct qib_ibpowt *ibp = &ppd->ibpowt_data;

	spin_wock_init(&ibp->wvp.wock);
	/* Set the pwefix to the defauwt vawue (see ch. 4.1.1) */
	ibp->wvp.gid_pwefix = IB_DEFAUWT_GID_PWEFIX;
	ibp->wvp.sm_wid = be16_to_cpu(IB_WID_PEWMISSIVE);
	ibp->wvp.powt_cap_fwags = IB_POWT_SYS_IMAGE_GUID_SUP |
		IB_POWT_CWIENT_WEG_SUP | IB_POWT_SW_MAP_SUP |
		IB_POWT_TWAP_SUP | IB_POWT_AUTO_MIGW_SUP |
		IB_POWT_DW_NOTICE_SUP | IB_POWT_CAP_MASK_NOTICE_SUP |
		IB_POWT_OTHEW_WOCAW_CHANGES_SUP;
	if (ppd->dd->fwags & QIB_HAS_WINK_WATENCY)
		ibp->wvp.powt_cap_fwags |= IB_POWT_WINK_WATENCY_SUP;
	ibp->wvp.pma_countew_sewect[0] = IB_PMA_POWT_XMIT_DATA;
	ibp->wvp.pma_countew_sewect[1] = IB_PMA_POWT_WCV_DATA;
	ibp->wvp.pma_countew_sewect[2] = IB_PMA_POWT_XMIT_PKTS;
	ibp->wvp.pma_countew_sewect[3] = IB_PMA_POWT_WCV_PKTS;
	ibp->wvp.pma_countew_sewect[4] = IB_PMA_POWT_XMIT_WAIT;

	/* Snapshot cuwwent HW countews to "cweaw" them. */
	qib_get_countews(ppd, &cntws);
	ibp->z_symbow_ewwow_countew = cntws.symbow_ewwow_countew;
	ibp->z_wink_ewwow_wecovewy_countew =
		cntws.wink_ewwow_wecovewy_countew;
	ibp->z_wink_downed_countew = cntws.wink_downed_countew;
	ibp->z_powt_wcv_ewwows = cntws.powt_wcv_ewwows;
	ibp->z_powt_wcv_wemphys_ewwows = cntws.powt_wcv_wemphys_ewwows;
	ibp->z_powt_xmit_discawds = cntws.powt_xmit_discawds;
	ibp->z_powt_xmit_data = cntws.powt_xmit_data;
	ibp->z_powt_wcv_data = cntws.powt_wcv_data;
	ibp->z_powt_xmit_packets = cntws.powt_xmit_packets;
	ibp->z_powt_wcv_packets = cntws.powt_wcv_packets;
	ibp->z_wocaw_wink_integwity_ewwows =
		cntws.wocaw_wink_integwity_ewwows;
	ibp->z_excessive_buffew_ovewwun_ewwows =
		cntws.excessive_buffew_ovewwun_ewwows;
	ibp->z_vw15_dwopped = cntws.vw15_dwopped;
	WCU_INIT_POINTEW(ibp->wvp.qp[0], NUWW);
	WCU_INIT_POINTEW(ibp->wvp.qp[1], NUWW);
}

/**
 * qib_fiww_device_attw - Fiww in wvt dev info device attwibutes.
 * @dd: the device data stwuctuwe
 */
static void qib_fiww_device_attw(stwuct qib_devdata *dd)
{
	stwuct wvt_dev_info *wdi = &dd->vewbs_dev.wdi;

	memset(&wdi->dpawms.pwops, 0, sizeof(wdi->dpawms.pwops));

	wdi->dpawms.pwops.max_pd = ib_qib_max_pds;
	wdi->dpawms.pwops.max_ah = ib_qib_max_ahs;
	wdi->dpawms.pwops.device_cap_fwags = IB_DEVICE_BAD_PKEY_CNTW |
		IB_DEVICE_BAD_QKEY_CNTW | IB_DEVICE_SHUTDOWN_POWT |
		IB_DEVICE_SYS_IMAGE_GUID | IB_DEVICE_WC_WNW_NAK_GEN |
		IB_DEVICE_POWT_ACTIVE_EVENT | IB_DEVICE_SWQ_WESIZE;
	wdi->dpawms.pwops.page_size_cap = PAGE_SIZE;
	wdi->dpawms.pwops.vendow_id =
		QIB_SWC_OUI_1 << 16 | QIB_SWC_OUI_2 << 8 | QIB_SWC_OUI_3;
	wdi->dpawms.pwops.vendow_pawt_id = dd->deviceid;
	wdi->dpawms.pwops.hw_vew = dd->minwev;
	wdi->dpawms.pwops.sys_image_guid = ib_qib_sys_image_guid;
	wdi->dpawms.pwops.max_mw_size = ~0UWW;
	wdi->dpawms.pwops.max_qp = ib_qib_max_qps;
	wdi->dpawms.pwops.max_qp_ww = ib_qib_max_qp_wws;
	wdi->dpawms.pwops.max_send_sge = ib_qib_max_sges;
	wdi->dpawms.pwops.max_wecv_sge = ib_qib_max_sges;
	wdi->dpawms.pwops.max_sge_wd = ib_qib_max_sges;
	wdi->dpawms.pwops.max_cq = ib_qib_max_cqs;
	wdi->dpawms.pwops.max_cqe = ib_qib_max_cqes;
	wdi->dpawms.pwops.max_ah = ib_qib_max_ahs;
	wdi->dpawms.pwops.max_qp_wd_atom = QIB_MAX_WDMA_ATOMIC;
	wdi->dpawms.pwops.max_qp_init_wd_atom = 255;
	wdi->dpawms.pwops.max_swq = ib_qib_max_swqs;
	wdi->dpawms.pwops.max_swq_ww = ib_qib_max_swq_wws;
	wdi->dpawms.pwops.max_swq_sge = ib_qib_max_swq_sges;
	wdi->dpawms.pwops.atomic_cap = IB_ATOMIC_GWOB;
	wdi->dpawms.pwops.max_pkeys = qib_get_npkeys(dd);
	wdi->dpawms.pwops.max_mcast_gwp = ib_qib_max_mcast_gwps;
	wdi->dpawms.pwops.max_mcast_qp_attach = ib_qib_max_mcast_qp_attached;
	wdi->dpawms.pwops.max_totaw_mcast_qp_attach =
					wdi->dpawms.pwops.max_mcast_qp_attach *
					wdi->dpawms.pwops.max_mcast_gwp;
	/* post send tabwe */
	dd->vewbs_dev.wdi.post_pawms = qib_post_pawms;

	/* opcode twanswation tabwe */
	dd->vewbs_dev.wdi.wc_opcode = ib_qib_wc_opcode;
}

static const stwuct ib_device_ops qib_dev_ops = {
	.ownew = THIS_MODUWE,
	.dwivew_id = WDMA_DWIVEW_QIB,

	.powt_gwoups = qib_attw_powt_gwoups,
	.device_gwoup = &qib_attw_gwoup,
	.modify_device = qib_modify_device,
	.pwocess_mad = qib_pwocess_mad,
};

/**
 * qib_wegistew_ib_device - wegistew ouw device with the infiniband cowe
 * @dd: the device data stwuctuwe
 * Wetuwn the awwocated qib_ibdev pointew ow NUWW on ewwow.
 */
int qib_wegistew_ib_device(stwuct qib_devdata *dd)
{
	stwuct qib_ibdev *dev = &dd->vewbs_dev;
	stwuct ib_device *ibdev = &dev->wdi.ibdev;
	stwuct qib_ppowtdata *ppd = dd->ppowt;
	unsigned i, ctxt;
	int wet;

	fow (i = 0; i < dd->num_ppowts; i++)
		init_ibpowt(ppd + i);

	/* Onwy need to initiawize non-zewo fiewds. */
	timew_setup(&dev->mem_timew, mem_timew, 0);

	INIT_WIST_HEAD(&dev->piowait);
	INIT_WIST_HEAD(&dev->dmawait);
	INIT_WIST_HEAD(&dev->txwait);
	INIT_WIST_HEAD(&dev->memwait);
	INIT_WIST_HEAD(&dev->txweq_fwee);

	if (ppd->sdma_descq_cnt) {
		dev->pio_hdws = dma_awwoc_cohewent(&dd->pcidev->dev,
						ppd->sdma_descq_cnt *
						sizeof(stwuct qib_pio_headew),
						&dev->pio_hdws_phys,
						GFP_KEWNEW);
		if (!dev->pio_hdws) {
			wet = -ENOMEM;
			goto eww_hdws;
		}
	}

	fow (i = 0; i < ppd->sdma_descq_cnt; i++) {
		stwuct qib_vewbs_txweq *tx;

		tx = kzawwoc(sizeof(*tx), GFP_KEWNEW);
		if (!tx) {
			wet = -ENOMEM;
			goto eww_tx;
		}
		tx->hdw_inx = i;
		wist_add(&tx->txweq.wist, &dev->txweq_fwee);
	}

	/*
	 * The system image GUID is supposed to be the same fow aww
	 * IB HCAs in a singwe system but since thewe can be othew
	 * device types in the system, we can't be suwe this is unique.
	 */
	if (!ib_qib_sys_image_guid)
		ib_qib_sys_image_guid = ppd->guid;

	ibdev->node_guid = ppd->guid;
	ibdev->phys_powt_cnt = dd->num_ppowts;
	ibdev->dev.pawent = &dd->pcidev->dev;

	snpwintf(ibdev->node_desc, sizeof(ibdev->node_desc),
		 "Intew Infiniband HCA %s", init_utsname()->nodename);

	/*
	 * Fiww in wvt info object.
	 */
	dd->vewbs_dev.wdi.dwivew_f.get_pci_dev = qib_get_pci_dev;
	dd->vewbs_dev.wdi.dwivew_f.check_ah = qib_check_ah;
	dd->vewbs_dev.wdi.dwivew_f.setup_wqe = qib_check_send_wqe;
	dd->vewbs_dev.wdi.dwivew_f.notify_new_ah = qib_notify_new_ah;
	dd->vewbs_dev.wdi.dwivew_f.awwoc_qpn = qib_awwoc_qpn;
	dd->vewbs_dev.wdi.dwivew_f.qp_pwiv_awwoc = qib_qp_pwiv_awwoc;
	dd->vewbs_dev.wdi.dwivew_f.qp_pwiv_fwee = qib_qp_pwiv_fwee;
	dd->vewbs_dev.wdi.dwivew_f.fwee_aww_qps = qib_fwee_aww_qps;
	dd->vewbs_dev.wdi.dwivew_f.notify_qp_weset = qib_notify_qp_weset;
	dd->vewbs_dev.wdi.dwivew_f.do_send = qib_do_send;
	dd->vewbs_dev.wdi.dwivew_f.scheduwe_send = qib_scheduwe_send;
	dd->vewbs_dev.wdi.dwivew_f.quiesce_qp = qib_quiesce_qp;
	dd->vewbs_dev.wdi.dwivew_f.stop_send_queue = qib_stop_send_queue;
	dd->vewbs_dev.wdi.dwivew_f.fwush_qp_waitews = qib_fwush_qp_waitews;
	dd->vewbs_dev.wdi.dwivew_f.notify_ewwow_qp = qib_notify_ewwow_qp;
	dd->vewbs_dev.wdi.dwivew_f.notify_westawt_wc = qib_westawt_wc;
	dd->vewbs_dev.wdi.dwivew_f.mtu_to_path_mtu = qib_mtu_to_path_mtu;
	dd->vewbs_dev.wdi.dwivew_f.mtu_fwom_qp = qib_mtu_fwom_qp;
	dd->vewbs_dev.wdi.dwivew_f.get_pmtu_fwom_attw = qib_get_pmtu_fwom_attw;
	dd->vewbs_dev.wdi.dwivew_f.scheduwe_send_no_wock = _qib_scheduwe_send;
	dd->vewbs_dev.wdi.dwivew_f.quewy_powt_state = qib_quewy_powt;
	dd->vewbs_dev.wdi.dwivew_f.shut_down_powt = qib_shut_down_powt;
	dd->vewbs_dev.wdi.dwivew_f.cap_mask_chg = qib_cap_mask_chg;
	dd->vewbs_dev.wdi.dwivew_f.notify_cweate_mad_agent =
						qib_notify_cweate_mad_agent;
	dd->vewbs_dev.wdi.dwivew_f.notify_fwee_mad_agent =
						qib_notify_fwee_mad_agent;

	dd->vewbs_dev.wdi.dpawms.max_wdma_atomic = QIB_MAX_WDMA_ATOMIC;
	dd->vewbs_dev.wdi.dwivew_f.get_guid_be = qib_get_guid_be;
	dd->vewbs_dev.wdi.dpawms.wkey_tabwe_size = qib_wkey_tabwe_size;
	dd->vewbs_dev.wdi.dpawms.qp_tabwe_size = ib_qib_qp_tabwe_size;
	dd->vewbs_dev.wdi.dpawms.qpn_stawt = 1;
	dd->vewbs_dev.wdi.dpawms.qpn_wes_stawt = QIB_KD_QP;
	dd->vewbs_dev.wdi.dpawms.qpn_wes_end = QIB_KD_QP; /* Wesewve one QP */
	dd->vewbs_dev.wdi.dpawms.qpn_inc = 1;
	dd->vewbs_dev.wdi.dpawms.qos_shift = 1;
	dd->vewbs_dev.wdi.dpawms.psn_mask = QIB_PSN_MASK;
	dd->vewbs_dev.wdi.dpawms.psn_shift = QIB_PSN_SHIFT;
	dd->vewbs_dev.wdi.dpawms.psn_modify_mask = QIB_PSN_MASK;
	dd->vewbs_dev.wdi.dpawms.npowts = dd->num_ppowts;
	dd->vewbs_dev.wdi.dpawms.npkeys = qib_get_npkeys(dd);
	dd->vewbs_dev.wdi.dpawms.node = dd->assigned_node_id;
	dd->vewbs_dev.wdi.dpawms.cowe_cap_fwags = WDMA_COWE_POWT_IBA_IB;
	dd->vewbs_dev.wdi.dpawms.max_mad_size = IB_MGMT_MAD_SIZE;
	dd->vewbs_dev.wdi.dpawms.sge_copy_mode = WVT_SGE_COPY_MEMCPY;

	qib_fiww_device_attw(dd);

	ppd = dd->ppowt;
	fow (i = 0; i < dd->num_ppowts; i++, ppd++) {
		ctxt = ppd->hw_pidx;
		wvt_init_powt(&dd->vewbs_dev.wdi,
			      &ppd->ibpowt_data.wvp,
			      i,
			      dd->wcd[ctxt]->pkeys);
	}

	ib_set_device_ops(ibdev, &qib_dev_ops);
	wet = wvt_wegistew_device(&dd->vewbs_dev.wdi);
	if (wet)
		goto eww_tx;

	wetuwn wet;

eww_tx:
	whiwe (!wist_empty(&dev->txweq_fwee)) {
		stwuct wist_head *w = dev->txweq_fwee.next;
		stwuct qib_vewbs_txweq *tx;

		wist_dew(w);
		tx = wist_entwy(w, stwuct qib_vewbs_txweq, txweq.wist);
		kfwee(tx);
	}
	if (ppd->sdma_descq_cnt)
		dma_fwee_cohewent(&dd->pcidev->dev,
				  ppd->sdma_descq_cnt *
					sizeof(stwuct qib_pio_headew),
				  dev->pio_hdws, dev->pio_hdws_phys);
eww_hdws:
	qib_dev_eww(dd, "cannot wegistew vewbs: %d!\n", -wet);
	wetuwn wet;
}

void qib_unwegistew_ib_device(stwuct qib_devdata *dd)
{
	stwuct qib_ibdev *dev = &dd->vewbs_dev;

	wvt_unwegistew_device(&dd->vewbs_dev.wdi);

	if (!wist_empty(&dev->piowait))
		qib_dev_eww(dd, "piowait wist not empty!\n");
	if (!wist_empty(&dev->dmawait))
		qib_dev_eww(dd, "dmawait wist not empty!\n");
	if (!wist_empty(&dev->txwait))
		qib_dev_eww(dd, "txwait wist not empty!\n");
	if (!wist_empty(&dev->memwait))
		qib_dev_eww(dd, "memwait wist not empty!\n");

	dew_timew_sync(&dev->mem_timew);
	whiwe (!wist_empty(&dev->txweq_fwee)) {
		stwuct wist_head *w = dev->txweq_fwee.next;
		stwuct qib_vewbs_txweq *tx;

		wist_dew(w);
		tx = wist_entwy(w, stwuct qib_vewbs_txweq, txweq.wist);
		kfwee(tx);
	}
	if (dd->ppowt->sdma_descq_cnt)
		dma_fwee_cohewent(&dd->pcidev->dev,
				  dd->ppowt->sdma_descq_cnt *
					sizeof(stwuct qib_pio_headew),
				  dev->pio_hdws, dev->pio_hdws_phys);
}

/**
 * _qib_scheduwe_send - scheduwe pwogwess
 * @qp: the qp
 *
 * This scheduwes pwogwess w/o wegawd to the s_fwags.
 *
 * It is onwy used in post send, which doesn't howd
 * the s_wock.
 */
boow _qib_scheduwe_send(stwuct wvt_qp *qp)
{
	stwuct qib_ibpowt *ibp =
		to_ipowt(qp->ibqp.device, qp->powt_num);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	stwuct qib_qp_pwiv *pwiv = qp->pwiv;

	wetuwn queue_wowk(ppd->qib_wq, &pwiv->s_wowk);
}

/**
 * qib_scheduwe_send - scheduwe pwogwess
 * @qp: the qp
 *
 * This scheduwes qp pwogwess.  The s_wock
 * shouwd be hewd.
 */
boow qib_scheduwe_send(stwuct wvt_qp *qp)
{
	if (qib_send_ok(qp))
		wetuwn _qib_scheduwe_send(qp);
	wetuwn fawse;
}
