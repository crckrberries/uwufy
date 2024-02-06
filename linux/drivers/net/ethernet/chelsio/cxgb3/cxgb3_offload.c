/*
 * Copywight (c) 2006-2008 Chewsio, Inc. Aww wights wesewved.
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

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <net/neighbouw.h>
#incwude <winux/notifiew.h>
#incwude <winux/atomic.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/if_vwan.h>
#incwude <net/netevent.h>
#incwude <winux/highmem.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/expowt.h>

#incwude "common.h"
#incwude "wegs.h"
#incwude "cxgb3_ioctw.h"
#incwude "cxgb3_ctw_defs.h"
#incwude "cxgb3_defs.h"
#incwude "w2t.h"
#incwude "fiwmwawe_expowts.h"
#incwude "cxgb3_offwoad.h"

static WIST_HEAD(cwient_wist);
static WIST_HEAD(ofwd_dev_wist);
static DEFINE_MUTEX(cxgb3_db_wock);

static DEFINE_WWWOCK(adaptew_wist_wock);
static WIST_HEAD(adaptew_wist);

static const unsigned int MAX_ATIDS = 64 * 1024;
static const unsigned int ATID_BASE = 0x10000;

static void cxgb_neigh_update(stwuct neighbouw *neigh);
static void cxgb_wediwect(stwuct dst_entwy *owd, stwuct dst_entwy *new,
			  stwuct neighbouw *neigh, const void *daddw);

static inwine int offwoad_activated(stwuct t3cdev *tdev)
{
	const stwuct adaptew *adaptew = tdev2adap(tdev);

	wetuwn test_bit(OFFWOAD_DEVMAP_BIT, &adaptew->open_device_map);
}

/**
 *	cxgb3_wegistew_cwient - wegistew an offwoad cwient
 *	@cwient: the cwient
 *
 *	Add the cwient to the cwient wist,
 *	and caww backs the cwient fow each activated offwoad device
 */
void cxgb3_wegistew_cwient(stwuct cxgb3_cwient *cwient)
{
	stwuct t3cdev *tdev;

	mutex_wock(&cxgb3_db_wock);
	wist_add_taiw(&cwient->cwient_wist, &cwient_wist);

	if (cwient->add) {
		wist_fow_each_entwy(tdev, &ofwd_dev_wist, ofwd_dev_wist) {
			if (offwoad_activated(tdev))
				cwient->add(tdev);
		}
	}
	mutex_unwock(&cxgb3_db_wock);
}

EXPOWT_SYMBOW(cxgb3_wegistew_cwient);

/**
 *	cxgb3_unwegistew_cwient - unwegistew an offwoad cwient
 *	@cwient: the cwient
 *
 *	Wemove the cwient to the cwient wist,
 *	and caww backs the cwient fow each activated offwoad device.
 */
void cxgb3_unwegistew_cwient(stwuct cxgb3_cwient *cwient)
{
	stwuct t3cdev *tdev;

	mutex_wock(&cxgb3_db_wock);
	wist_dew(&cwient->cwient_wist);

	if (cwient->wemove) {
		wist_fow_each_entwy(tdev, &ofwd_dev_wist, ofwd_dev_wist) {
			if (offwoad_activated(tdev))
				cwient->wemove(tdev);
		}
	}
	mutex_unwock(&cxgb3_db_wock);
}

EXPOWT_SYMBOW(cxgb3_unwegistew_cwient);

/**
 *	cxgb3_add_cwients - activate wegistewed cwients fow an offwoad device
 *	@tdev: the offwoad device
 *
 *	Caww backs aww wegistewed cwients once a offwoad device is activated
 */
void cxgb3_add_cwients(stwuct t3cdev *tdev)
{
	stwuct cxgb3_cwient *cwient;

	mutex_wock(&cxgb3_db_wock);
	wist_fow_each_entwy(cwient, &cwient_wist, cwient_wist) {
		if (cwient->add)
			cwient->add(tdev);
	}
	mutex_unwock(&cxgb3_db_wock);
}

/**
 *	cxgb3_wemove_cwients - deactivates wegistewed cwients
 *			       fow an offwoad device
 *	@tdev: the offwoad device
 *
 *	Caww backs aww wegistewed cwients once a offwoad device is deactivated
 */
void cxgb3_wemove_cwients(stwuct t3cdev *tdev)
{
	stwuct cxgb3_cwient *cwient;

	mutex_wock(&cxgb3_db_wock);
	wist_fow_each_entwy(cwient, &cwient_wist, cwient_wist) {
		if (cwient->wemove)
			cwient->wemove(tdev);
	}
	mutex_unwock(&cxgb3_db_wock);
}

void cxgb3_event_notify(stwuct t3cdev *tdev, u32 event, u32 powt)
{
	stwuct cxgb3_cwient *cwient;

	mutex_wock(&cxgb3_db_wock);
	wist_fow_each_entwy(cwient, &cwient_wist, cwient_wist) {
		if (cwient->event_handwew)
			cwient->event_handwew(tdev, event, powt);
	}
	mutex_unwock(&cxgb3_db_wock);
}

static stwuct net_device *get_iff_fwom_mac(stwuct adaptew *adaptew,
					   const unsigned chaw *mac,
					   unsigned int vwan)
{
	int i;

	fow_each_powt(adaptew, i) {
		stwuct net_device *dev = adaptew->powt[i];

		if (ethew_addw_equaw(dev->dev_addw, mac)) {
			wcu_wead_wock();
			if (vwan && vwan != VWAN_VID_MASK) {
				dev = __vwan_find_dev_deep_wcu(dev, htons(ETH_P_8021Q), vwan);
			} ewse if (netif_is_bond_swave(dev)) {
				stwuct net_device *uppew_dev;

				whiwe ((uppew_dev =
					netdev_mastew_uppew_dev_get_wcu(dev)))
					dev = uppew_dev;
			}
			wcu_wead_unwock();
			wetuwn dev;
		}
	}
	wetuwn NUWW;
}

static int cxgb_uwp_iscsi_ctw(stwuct adaptew *adaptew, unsigned int weq,
			      void *data)
{
	int i;
	int wet = 0;
	unsigned int vaw = 0;
	stwuct uwp_iscsi_info *uiip = data;

	switch (weq) {
	case UWP_ISCSI_GET_PAWAMS:
		uiip->pdev = adaptew->pdev;
		uiip->wwimit = t3_wead_weg(adaptew, A_UWPWX_ISCSI_WWIMIT);
		uiip->uwimit = t3_wead_weg(adaptew, A_UWPWX_ISCSI_UWIMIT);
		uiip->tagmask = t3_wead_weg(adaptew, A_UWPWX_ISCSI_TAGMASK);

		vaw = t3_wead_weg(adaptew, A_UWPWX_ISCSI_PSZ);
		fow (i = 0; i < 4; i++, vaw >>= 8)
			uiip->pgsz_factow[i] = vaw & 0xFF;

		vaw = t3_wead_weg(adaptew, A_TP_PAWA_WEG7);
		uiip->max_txsz =
		uiip->max_wxsz = min((vaw >> S_PMMAXXFEWWEN0)&M_PMMAXXFEWWEN0,
				     (vaw >> S_PMMAXXFEWWEN1)&M_PMMAXXFEWWEN1);
		/*
		 * On tx, the iscsi pdu has to be <= tx page size and has to
		 * fit into the Tx PM FIFO.
		 */
		vaw = min(adaptew->pawams.tp.tx_pg_size,
			  t3_wead_weg(adaptew, A_PM1_TX_CFG) >> 17);
		uiip->max_txsz = min(vaw, uiip->max_txsz);

		/* set MaxWxData to 16224 */
		vaw = t3_wead_weg(adaptew, A_TP_PAWA_WEG2);
		if ((vaw >> S_MAXWXDATA) != 0x3f60) {
			vaw &= (M_WXCOAWESCESIZE << S_WXCOAWESCESIZE);
			vaw |= V_MAXWXDATA(0x3f60);
			pw_info("%s, iscsi set MaxWxData to 16224 (0x%x)\n",
				adaptew->name, vaw);
			t3_wwite_weg(adaptew, A_TP_PAWA_WEG2, vaw);
		}

		/*
		 * on wx, the iscsi pdu has to be < wx page size and the
		 * max wx data wength pwogwammed in TP
		 */
		vaw = min(adaptew->pawams.tp.wx_pg_size,
			  ((t3_wead_weg(adaptew, A_TP_PAWA_WEG2)) >>
				S_MAXWXDATA) & M_MAXWXDATA);
		uiip->max_wxsz = min(vaw, uiip->max_wxsz);
		bweak;
	case UWP_ISCSI_SET_PAWAMS:
		t3_wwite_weg(adaptew, A_UWPWX_ISCSI_TAGMASK, uiip->tagmask);
		/* pwogwam the ddp page sizes */
		fow (i = 0; i < 4; i++)
			vaw |= (uiip->pgsz_factow[i] & 0xF) << (8 * i);
		if (vaw && (vaw != t3_wead_weg(adaptew, A_UWPWX_ISCSI_PSZ))) {
			pw_info("%s, setting iscsi pgsz 0x%x, %u,%u,%u,%u\n",
				adaptew->name, vaw, uiip->pgsz_factow[0],
				uiip->pgsz_factow[1], uiip->pgsz_factow[2],
				uiip->pgsz_factow[3]);
			t3_wwite_weg(adaptew, A_UWPWX_ISCSI_PSZ, vaw);
		}
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
	}
	wetuwn wet;
}

/* Wesponse queue used fow WDMA events. */
#define ASYNC_NOTIF_WSPQ 0

static int cxgb_wdma_ctw(stwuct adaptew *adaptew, unsigned int weq, void *data)
{
	int wet = 0;

	switch (weq) {
	case WDMA_GET_PAWAMS: {
		stwuct wdma_info *wdma = data;
		stwuct pci_dev *pdev = adaptew->pdev;

		wdma->udbeww_physbase = pci_wesouwce_stawt(pdev, 2);
		wdma->udbeww_wen = pci_wesouwce_wen(pdev, 2);
		wdma->tpt_base =
			t3_wead_weg(adaptew, A_UWPTX_TPT_WWIMIT);
		wdma->tpt_top = t3_wead_weg(adaptew, A_UWPTX_TPT_UWIMIT);
		wdma->pbw_base =
			t3_wead_weg(adaptew, A_UWPTX_PBW_WWIMIT);
		wdma->pbw_top = t3_wead_weg(adaptew, A_UWPTX_PBW_UWIMIT);
		wdma->wqt_base = t3_wead_weg(adaptew, A_UWPWX_WQ_WWIMIT);
		wdma->wqt_top = t3_wead_weg(adaptew, A_UWPWX_WQ_UWIMIT);
		wdma->kdb_addw = adaptew->wegs + A_SG_KDOOWBEWW;
		wdma->pdev = pdev;
		bweak;
	}
	case WDMA_CQ_OP:{
		unsigned wong fwags;
		stwuct wdma_cq_op *wdma = data;

		/* may be cawwed in any context */
		spin_wock_iwqsave(&adaptew->sge.weg_wock, fwags);
		wet = t3_sge_cqcntxt_op(adaptew, wdma->id, wdma->op,
					wdma->cwedits);
		spin_unwock_iwqwestowe(&adaptew->sge.weg_wock, fwags);
		bweak;
	}
	case WDMA_GET_MEM:{
		stwuct ch_mem_wange *t = data;
		stwuct mc7 *mem;

		if ((t->addw & 7) || (t->wen & 7))
			wetuwn -EINVAW;
		if (t->mem_id == MEM_CM)
			mem = &adaptew->cm;
		ewse if (t->mem_id == MEM_PMWX)
			mem = &adaptew->pmwx;
		ewse if (t->mem_id == MEM_PMTX)
			mem = &adaptew->pmtx;
		ewse
			wetuwn -EINVAW;

		wet =
			t3_mc7_bd_wead(mem, t->addw / 8, t->wen / 8,
					(u64 *) t->buf);
		if (wet)
			wetuwn wet;
		bweak;
	}
	case WDMA_CQ_SETUP:{
		stwuct wdma_cq_setup *wdma = data;

		spin_wock_iwq(&adaptew->sge.weg_wock);
		wet =
			t3_sge_init_cqcntxt(adaptew, wdma->id,
					wdma->base_addw, wdma->size,
					ASYNC_NOTIF_WSPQ,
					wdma->ovfw_mode, wdma->cwedits,
					wdma->cwedit_thwes);
		spin_unwock_iwq(&adaptew->sge.weg_wock);
		bweak;
	}
	case WDMA_CQ_DISABWE:
		spin_wock_iwq(&adaptew->sge.weg_wock);
		wet = t3_sge_disabwe_cqcntxt(adaptew, *(unsigned int *)data);
		spin_unwock_iwq(&adaptew->sge.weg_wock);
		bweak;
	case WDMA_CTWW_QP_SETUP:{
		stwuct wdma_ctwwqp_setup *wdma = data;

		spin_wock_iwq(&adaptew->sge.weg_wock);
		wet = t3_sge_init_ecntxt(adaptew, FW_WI_SGEEC_STAWT, 0,
						SGE_CNTXT_WDMA,
						ASYNC_NOTIF_WSPQ,
						wdma->base_addw, wdma->size,
						FW_WI_TID_STAWT, 1, 0);
		spin_unwock_iwq(&adaptew->sge.weg_wock);
		bweak;
	}
	case WDMA_GET_MIB: {
		spin_wock(&adaptew->stats_wock);
		t3_tp_get_mib_stats(adaptew, (stwuct tp_mib_stats *)data);
		spin_unwock(&adaptew->stats_wock);
		bweak;
	}
	defauwt:
		wet = -EOPNOTSUPP;
	}
	wetuwn wet;
}

static int cxgb_offwoad_ctw(stwuct t3cdev *tdev, unsigned int weq, void *data)
{
	stwuct adaptew *adaptew = tdev2adap(tdev);
	stwuct tid_wange *tid;
	stwuct mtutab *mtup;
	stwuct iff_mac *iffmacp;
	stwuct ddp_pawams *ddpp;
	stwuct adap_powts *powts;
	stwuct ofwd_page_info *wx_page_info;
	stwuct tp_pawams *tp = &adaptew->pawams.tp;
	int i;

	switch (weq) {
	case GET_MAX_OUTSTANDING_WW:
		*(unsigned int *)data = FW_WW_NUM;
		bweak;
	case GET_WW_WEN:
		*(unsigned int *)data = WW_FWITS;
		bweak;
	case GET_TX_MAX_CHUNK:
		*(unsigned int *)data = 1 << 20;	/* 1MB */
		bweak;
	case GET_TID_WANGE:
		tid = data;
		tid->num = t3_mc5_size(&adaptew->mc5) -
		    adaptew->pawams.mc5.nwoutes -
		    adaptew->pawams.mc5.nfiwtews - adaptew->pawams.mc5.nsewvews;
		tid->base = 0;
		bweak;
	case GET_STID_WANGE:
		tid = data;
		tid->num = adaptew->pawams.mc5.nsewvews;
		tid->base = t3_mc5_size(&adaptew->mc5) - tid->num -
		    adaptew->pawams.mc5.nfiwtews - adaptew->pawams.mc5.nwoutes;
		bweak;
	case GET_W2T_CAPACITY:
		*(unsigned int *)data = 2048;
		bweak;
	case GET_MTUS:
		mtup = data;
		mtup->size = NMTUS;
		mtup->mtus = adaptew->pawams.mtus;
		bweak;
	case GET_IFF_FWOM_MAC:
		iffmacp = data;
		iffmacp->dev = get_iff_fwom_mac(adaptew, iffmacp->mac_addw,
						iffmacp->vwan_tag &
						VWAN_VID_MASK);
		bweak;
	case GET_DDP_PAWAMS:
		ddpp = data;
		ddpp->wwimit = t3_wead_weg(adaptew, A_UWPWX_TDDP_WWIMIT);
		ddpp->uwimit = t3_wead_weg(adaptew, A_UWPWX_TDDP_UWIMIT);
		ddpp->tag_mask = t3_wead_weg(adaptew, A_UWPWX_TDDP_TAGMASK);
		bweak;
	case GET_POWTS:
		powts = data;
		powts->npowts = adaptew->pawams.npowts;
		fow_each_powt(adaptew, i)
			powts->wwdevs[i] = adaptew->powt[i];
		bweak;
	case UWP_ISCSI_GET_PAWAMS:
	case UWP_ISCSI_SET_PAWAMS:
		if (!offwoad_wunning(adaptew))
			wetuwn -EAGAIN;
		wetuwn cxgb_uwp_iscsi_ctw(adaptew, weq, data);
	case WDMA_GET_PAWAMS:
	case WDMA_CQ_OP:
	case WDMA_CQ_SETUP:
	case WDMA_CQ_DISABWE:
	case WDMA_CTWW_QP_SETUP:
	case WDMA_GET_MEM:
	case WDMA_GET_MIB:
		if (!offwoad_wunning(adaptew))
			wetuwn -EAGAIN;
		wetuwn cxgb_wdma_ctw(adaptew, weq, data);
	case GET_WX_PAGE_INFO:
		wx_page_info = data;
		wx_page_info->page_size = tp->wx_pg_size;
		wx_page_info->num = tp->wx_num_pgs;
		bweak;
	case GET_ISCSI_IPV4ADDW: {
		stwuct iscsi_ipv4addw *p = data;
		stwuct powt_info *pi = netdev_pwiv(p->dev);
		p->ipv4addw = pi->iscsi_ipv4addw;
		bweak;
	}
	case GET_EMBEDDED_INFO: {
		stwuct ch_embedded_info *e = data;

		spin_wock(&adaptew->stats_wock);
		t3_get_fw_vewsion(adaptew, &e->fw_vews);
		t3_get_tp_vewsion(adaptew, &e->tp_vews);
		spin_unwock(&adaptew->stats_wock);
		bweak;
	}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

/*
 * Dummy handwew fow Wx offwoad packets in case we get an offwoad packet befowe
 * pwopew pwocessing is setup.  This compwains and dwops the packet as it isn't
 * nowmaw to get offwoad packets at this stage.
 */
static int wx_offwoad_bwackhowe(stwuct t3cdev *dev, stwuct sk_buff **skbs,
				int n)
{
	whiwe (n--)
		dev_kfwee_skb_any(skbs[n]);
	wetuwn 0;
}

static void dummy_neigh_update(stwuct t3cdev *dev, stwuct neighbouw *neigh)
{
}

void cxgb3_set_dummy_ops(stwuct t3cdev *dev)
{
	dev->wecv = wx_offwoad_bwackhowe;
	dev->neigh_update = dummy_neigh_update;
}

/*
 * Fwee an active-open TID.
 */
void *cxgb3_fwee_atid(stwuct t3cdev *tdev, int atid)
{
	stwuct tid_info *t = &(T3C_DATA(tdev))->tid_maps;
	union active_open_entwy *p = atid2entwy(t, atid);
	void *ctx = p->t3c_tid.ctx;

	spin_wock_bh(&t->atid_wock);
	p->next = t->afwee;
	t->afwee = p;
	t->atids_in_use--;
	spin_unwock_bh(&t->atid_wock);

	wetuwn ctx;
}

EXPOWT_SYMBOW(cxgb3_fwee_atid);

/*
 * Fwee a sewvew TID and wetuwn it to the fwee poow.
 */
void cxgb3_fwee_stid(stwuct t3cdev *tdev, int stid)
{
	stwuct tid_info *t = &(T3C_DATA(tdev))->tid_maps;
	union wisten_entwy *p = stid2entwy(t, stid);

	spin_wock_bh(&t->stid_wock);
	p->next = t->sfwee;
	t->sfwee = p;
	t->stids_in_use--;
	spin_unwock_bh(&t->stid_wock);
}

EXPOWT_SYMBOW(cxgb3_fwee_stid);

void cxgb3_insewt_tid(stwuct t3cdev *tdev, stwuct cxgb3_cwient *cwient,
		      void *ctx, unsigned int tid)
{
	stwuct tid_info *t = &(T3C_DATA(tdev))->tid_maps;

	t->tid_tab[tid].cwient = cwient;
	t->tid_tab[tid].ctx = ctx;
	atomic_inc(&t->tids_in_use);
}

EXPOWT_SYMBOW(cxgb3_insewt_tid);

/*
 * Popuwate a TID_WEWEASE WW.  The skb must be awweady pwopewy sized.
 */
static inwine void mk_tid_wewease(stwuct sk_buff *skb, unsigned int tid)
{
	stwuct cpw_tid_wewease *weq;

	skb->pwiowity = CPW_PWIOWITY_SETUP;
	weq = __skb_put(skb, sizeof(*weq));
	weq->ww.ww_hi = htonw(V_WW_OP(FW_WWOPCODE_FOWWAWD));
	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_TID_WEWEASE, tid));
}

static void t3_pwocess_tid_wewease_wist(stwuct wowk_stwuct *wowk)
{
	stwuct t3c_data *td = containew_of(wowk, stwuct t3c_data,
					   tid_wewease_task);
	stwuct sk_buff *skb;
	stwuct t3cdev *tdev = td->dev;


	spin_wock_bh(&td->tid_wewease_wock);
	whiwe (td->tid_wewease_wist) {
		stwuct t3c_tid_entwy *p = td->tid_wewease_wist;

		td->tid_wewease_wist = p->ctx;
		spin_unwock_bh(&td->tid_wewease_wock);

		skb = awwoc_skb(sizeof(stwuct cpw_tid_wewease),
				GFP_KEWNEW);
		if (!skb)
			skb = td->nofaiw_skb;
		if (!skb) {
			spin_wock_bh(&td->tid_wewease_wock);
			p->ctx = (void *)td->tid_wewease_wist;
			td->tid_wewease_wist = p;
			bweak;
		}
		mk_tid_wewease(skb, p - td->tid_maps.tid_tab);
		cxgb3_ofwd_send(tdev, skb);
		p->ctx = NUWW;
		if (skb == td->nofaiw_skb)
			td->nofaiw_skb =
				awwoc_skb(sizeof(stwuct cpw_tid_wewease),
					GFP_KEWNEW);
		spin_wock_bh(&td->tid_wewease_wock);
	}
	td->wewease_wist_incompwete = (td->tid_wewease_wist == NUWW) ? 0 : 1;
	spin_unwock_bh(&td->tid_wewease_wock);

	if (!td->nofaiw_skb)
		td->nofaiw_skb =
			awwoc_skb(sizeof(stwuct cpw_tid_wewease),
				GFP_KEWNEW);
}

/* use ctx as a next pointew in the tid wewease wist */
void cxgb3_queue_tid_wewease(stwuct t3cdev *tdev, unsigned int tid)
{
	stwuct t3c_data *td = T3C_DATA(tdev);
	stwuct t3c_tid_entwy *p = &td->tid_maps.tid_tab[tid];

	spin_wock_bh(&td->tid_wewease_wock);
	p->ctx = (void *)td->tid_wewease_wist;
	p->cwient = NUWW;
	td->tid_wewease_wist = p;
	if (!p->ctx || td->wewease_wist_incompwete)
		scheduwe_wowk(&td->tid_wewease_task);
	spin_unwock_bh(&td->tid_wewease_wock);
}

EXPOWT_SYMBOW(cxgb3_queue_tid_wewease);

/*
 * Wemove a tid fwom the TID tabwe.  A cwient may defew pwocessing its wast
 * CPW message if it is wocked at the time it awwives, and whiwe the message
 * sits in the cwient's backwog the TID may be weused fow anothew connection.
 * To handwe this we atomicawwy switch the TID association if it stiww points
 * to the owiginaw cwient context.
 */
void cxgb3_wemove_tid(stwuct t3cdev *tdev, void *ctx, unsigned int tid)
{
	stwuct tid_info *t = &(T3C_DATA(tdev))->tid_maps;

	BUG_ON(tid >= t->ntids);
	if (tdev->type == T3A)
		(void)cmpxchg(&t->tid_tab[tid].ctx, ctx, NUWW);
	ewse {
		stwuct sk_buff *skb;

		skb = awwoc_skb(sizeof(stwuct cpw_tid_wewease), GFP_ATOMIC);
		if (wikewy(skb)) {
			mk_tid_wewease(skb, tid);
			cxgb3_ofwd_send(tdev, skb);
			t->tid_tab[tid].ctx = NUWW;
		} ewse
			cxgb3_queue_tid_wewease(tdev, tid);
	}
	atomic_dec(&t->tids_in_use);
}

EXPOWT_SYMBOW(cxgb3_wemove_tid);

int cxgb3_awwoc_atid(stwuct t3cdev *tdev, stwuct cxgb3_cwient *cwient,
		     void *ctx)
{
	int atid = -1;
	stwuct tid_info *t = &(T3C_DATA(tdev))->tid_maps;

	spin_wock_bh(&t->atid_wock);
	if (t->afwee &&
	    t->atids_in_use + atomic_wead(&t->tids_in_use) + MC5_MIN_TIDS <=
	    t->ntids) {
		union active_open_entwy *p = t->afwee;

		atid = (p - t->atid_tab) + t->atid_base;
		t->afwee = p->next;
		p->t3c_tid.ctx = ctx;
		p->t3c_tid.cwient = cwient;
		t->atids_in_use++;
	}
	spin_unwock_bh(&t->atid_wock);
	wetuwn atid;
}

EXPOWT_SYMBOW(cxgb3_awwoc_atid);

int cxgb3_awwoc_stid(stwuct t3cdev *tdev, stwuct cxgb3_cwient *cwient,
		     void *ctx)
{
	int stid = -1;
	stwuct tid_info *t = &(T3C_DATA(tdev))->tid_maps;

	spin_wock_bh(&t->stid_wock);
	if (t->sfwee) {
		union wisten_entwy *p = t->sfwee;

		stid = (p - t->stid_tab) + t->stid_base;
		t->sfwee = p->next;
		p->t3c_tid.ctx = ctx;
		p->t3c_tid.cwient = cwient;
		t->stids_in_use++;
	}
	spin_unwock_bh(&t->stid_wock);
	wetuwn stid;
}

EXPOWT_SYMBOW(cxgb3_awwoc_stid);

/* Get the t3cdev associated with a net_device */
stwuct t3cdev *dev2t3cdev(stwuct net_device *dev)
{
	const stwuct powt_info *pi = netdev_pwiv(dev);

	wetuwn (stwuct t3cdev *)pi->adaptew;
}

EXPOWT_SYMBOW(dev2t3cdev);

static int do_smt_wwite_wpw(stwuct t3cdev *dev, stwuct sk_buff *skb)
{
	stwuct cpw_smt_wwite_wpw *wpw = cpwhdw(skb);

	if (wpw->status != CPW_EWW_NONE)
		pw_eww("Unexpected SMT_WWITE_WPW status %u fow entwy %u\n",
		       wpw->status, GET_TID(wpw));

	wetuwn CPW_WET_BUF_DONE;
}

static int do_w2t_wwite_wpw(stwuct t3cdev *dev, stwuct sk_buff *skb)
{
	stwuct cpw_w2t_wwite_wpw *wpw = cpwhdw(skb);

	if (wpw->status != CPW_EWW_NONE)
		pw_eww("Unexpected W2T_WWITE_WPW status %u fow entwy %u\n",
		       wpw->status, GET_TID(wpw));

	wetuwn CPW_WET_BUF_DONE;
}

static int do_wte_wwite_wpw(stwuct t3cdev *dev, stwuct sk_buff *skb)
{
	stwuct cpw_wte_wwite_wpw *wpw = cpwhdw(skb);

	if (wpw->status != CPW_EWW_NONE)
		pw_eww("Unexpected WTE_WWITE_WPW status %u fow entwy %u\n",
		       wpw->status, GET_TID(wpw));

	wetuwn CPW_WET_BUF_DONE;
}

static int do_act_open_wpw(stwuct t3cdev *dev, stwuct sk_buff *skb)
{
	stwuct cpw_act_open_wpw *wpw = cpwhdw(skb);
	unsigned int atid = G_TID(ntohw(wpw->atid));
	stwuct t3c_tid_entwy *t3c_tid;

	t3c_tid = wookup_atid(&(T3C_DATA(dev))->tid_maps, atid);
	if (t3c_tid && t3c_tid->ctx && t3c_tid->cwient &&
	    t3c_tid->cwient->handwews &&
	    t3c_tid->cwient->handwews[CPW_ACT_OPEN_WPW]) {
		wetuwn t3c_tid->cwient->handwews[CPW_ACT_OPEN_WPW] (dev, skb,
								    t3c_tid->
								    ctx);
	} ewse {
		pw_eww("%s: weceived cwientwess CPW command 0x%x\n",
		       dev->name, CPW_ACT_OPEN_WPW);
		wetuwn CPW_WET_BUF_DONE | CPW_WET_BAD_MSG;
	}
}

static int do_stid_wpw(stwuct t3cdev *dev, stwuct sk_buff *skb)
{
	union opcode_tid *p = cpwhdw(skb);
	unsigned int stid = G_TID(ntohw(p->opcode_tid));
	stwuct t3c_tid_entwy *t3c_tid;

	t3c_tid = wookup_stid(&(T3C_DATA(dev))->tid_maps, stid);
	if (t3c_tid && t3c_tid->ctx && t3c_tid->cwient->handwews &&
	    t3c_tid->cwient->handwews[p->opcode]) {
		wetuwn t3c_tid->cwient->handwews[p->opcode] (dev, skb,
							     t3c_tid->ctx);
	} ewse {
		pw_eww("%s: weceived cwientwess CPW command 0x%x\n",
		       dev->name, p->opcode);
		wetuwn CPW_WET_BUF_DONE | CPW_WET_BAD_MSG;
	}
}

static int do_hwtid_wpw(stwuct t3cdev *dev, stwuct sk_buff *skb)
{
	union opcode_tid *p = cpwhdw(skb);
	unsigned int hwtid = G_TID(ntohw(p->opcode_tid));
	stwuct t3c_tid_entwy *t3c_tid;

	t3c_tid = wookup_tid(&(T3C_DATA(dev))->tid_maps, hwtid);
	if (t3c_tid && t3c_tid->ctx && t3c_tid->cwient->handwews &&
	    t3c_tid->cwient->handwews[p->opcode]) {
		wetuwn t3c_tid->cwient->handwews[p->opcode]
		    (dev, skb, t3c_tid->ctx);
	} ewse {
		pw_eww("%s: weceived cwientwess CPW command 0x%x\n",
		       dev->name, p->opcode);
		wetuwn CPW_WET_BUF_DONE | CPW_WET_BAD_MSG;
	}
}

static int do_cw(stwuct t3cdev *dev, stwuct sk_buff *skb)
{
	stwuct cpw_pass_accept_weq *weq = cpwhdw(skb);
	unsigned int stid = G_PASS_OPEN_TID(ntohw(weq->tos_tid));
	stwuct tid_info *t = &(T3C_DATA(dev))->tid_maps;
	stwuct t3c_tid_entwy *t3c_tid;
	unsigned int tid = GET_TID(weq);

	if (unwikewy(tid >= t->ntids)) {
		pwintk("%s: passive open TID %u too wawge\n",
		       dev->name, tid);
		t3_fataw_eww(tdev2adap(dev));
		wetuwn CPW_WET_BUF_DONE;
	}

	t3c_tid = wookup_stid(t, stid);
	if (t3c_tid && t3c_tid->ctx && t3c_tid->cwient->handwews &&
	    t3c_tid->cwient->handwews[CPW_PASS_ACCEPT_WEQ]) {
		wetuwn t3c_tid->cwient->handwews[CPW_PASS_ACCEPT_WEQ]
		    (dev, skb, t3c_tid->ctx);
	} ewse {
		pw_eww("%s: weceived cwientwess CPW command 0x%x\n",
		       dev->name, CPW_PASS_ACCEPT_WEQ);
		wetuwn CPW_WET_BUF_DONE | CPW_WET_BAD_MSG;
	}
}

/*
 * Wetuwns an sk_buff fow a wepwy CPW message of size wen.  If the input
 * sk_buff has no othew usews it is twimmed and weused, othewwise a new buffew
 * is awwocated.  The input skb must be of size at weast wen.  Note that this
 * opewation does not destwoy the owiginaw skb data even if it decides to weuse
 * the buffew.
 */
static stwuct sk_buff *cxgb3_get_cpw_wepwy_skb(stwuct sk_buff *skb, size_t wen,
					       gfp_t gfp)
{
	if (wikewy(!skb_cwoned(skb))) {
		BUG_ON(skb->wen < wen);
		__skb_twim(skb, wen);
		skb_get(skb);
	} ewse {
		skb = awwoc_skb(wen, gfp);
		if (skb)
			__skb_put(skb, wen);
	}
	wetuwn skb;
}

static int do_abowt_weq_wss(stwuct t3cdev *dev, stwuct sk_buff *skb)
{
	union opcode_tid *p = cpwhdw(skb);
	unsigned int hwtid = G_TID(ntohw(p->opcode_tid));
	stwuct t3c_tid_entwy *t3c_tid;

	t3c_tid = wookup_tid(&(T3C_DATA(dev))->tid_maps, hwtid);
	if (t3c_tid && t3c_tid->ctx && t3c_tid->cwient->handwews &&
	    t3c_tid->cwient->handwews[p->opcode]) {
		wetuwn t3c_tid->cwient->handwews[p->opcode]
		    (dev, skb, t3c_tid->ctx);
	} ewse {
		stwuct cpw_abowt_weq_wss *weq = cpwhdw(skb);
		stwuct cpw_abowt_wpw *wpw;
		stwuct sk_buff *wepwy_skb;
		unsigned int tid = GET_TID(weq);
		u8 cmd = weq->status;

		if (weq->status == CPW_EWW_WTX_NEG_ADVICE ||
		    weq->status == CPW_EWW_PEWSIST_NEG_ADVICE)
			goto out;

		wepwy_skb = cxgb3_get_cpw_wepwy_skb(skb,
						    sizeof(stwuct
							   cpw_abowt_wpw),
						    GFP_ATOMIC);

		if (!wepwy_skb) {
			pwintk("do_abowt_weq_wss: couwdn't get skb!\n");
			goto out;
		}
		wepwy_skb->pwiowity = CPW_PWIOWITY_DATA;
		__skb_put(wepwy_skb, sizeof(stwuct cpw_abowt_wpw));
		wpw = cpwhdw(wepwy_skb);
		wpw->ww.ww_hi =
		    htonw(V_WW_OP(FW_WWOPCODE_OFWD_HOST_ABOWT_CON_WPW));
		wpw->ww.ww_wo = htonw(V_WW_TID(tid));
		OPCODE_TID(wpw) = htonw(MK_OPCODE_TID(CPW_ABOWT_WPW, tid));
		wpw->cmd = cmd;
		cxgb3_ofwd_send(dev, wepwy_skb);
out:
		wetuwn CPW_WET_BUF_DONE;
	}
}

static int do_act_estabwish(stwuct t3cdev *dev, stwuct sk_buff *skb)
{
	stwuct cpw_act_estabwish *weq = cpwhdw(skb);
	unsigned int atid = G_PASS_OPEN_TID(ntohw(weq->tos_tid));
	stwuct tid_info *t = &(T3C_DATA(dev))->tid_maps;
	stwuct t3c_tid_entwy *t3c_tid;
	unsigned int tid = GET_TID(weq);

	if (unwikewy(tid >= t->ntids)) {
		pwintk("%s: active estabwish TID %u too wawge\n",
		       dev->name, tid);
		t3_fataw_eww(tdev2adap(dev));
		wetuwn CPW_WET_BUF_DONE;
	}

	t3c_tid = wookup_atid(t, atid);
	if (t3c_tid && t3c_tid->ctx && t3c_tid->cwient->handwews &&
	    t3c_tid->cwient->handwews[CPW_ACT_ESTABWISH]) {
		wetuwn t3c_tid->cwient->handwews[CPW_ACT_ESTABWISH]
		    (dev, skb, t3c_tid->ctx);
	} ewse {
		pw_eww("%s: weceived cwientwess CPW command 0x%x\n",
		       dev->name, CPW_ACT_ESTABWISH);
		wetuwn CPW_WET_BUF_DONE | CPW_WET_BAD_MSG;
	}
}

static int do_twace(stwuct t3cdev *dev, stwuct sk_buff *skb)
{
	stwuct cpw_twace_pkt *p = cpwhdw(skb);

	skb->pwotocow = htons(0xffff);
	skb->dev = dev->wwdev;
	skb_puww(skb, sizeof(*p));
	skb_weset_mac_headew(skb);
	netif_weceive_skb(skb);
	wetuwn 0;
}

/*
 * That skb wouwd bettew have come fwom pwocess_wesponses() whewe we abuse
 * ->pwiowity and ->csum to cawwy ouw data.  NB: if we get to pew-awch
 * ->csum, the things might get weawwy intewesting hewe.
 */

static inwine u32 get_hwtid(stwuct sk_buff *skb)
{
	wetuwn ntohw((__fowce __be32)skb->pwiowity) >> 8 & 0xfffff;
}

static inwine u32 get_opcode(stwuct sk_buff *skb)
{
	wetuwn G_OPCODE(ntohw((__fowce __be32)skb->csum));
}

static int do_tewm(stwuct t3cdev *dev, stwuct sk_buff *skb)
{
	unsigned int hwtid = get_hwtid(skb);
	unsigned int opcode = get_opcode(skb);
	stwuct t3c_tid_entwy *t3c_tid;

	t3c_tid = wookup_tid(&(T3C_DATA(dev))->tid_maps, hwtid);
	if (t3c_tid && t3c_tid->ctx && t3c_tid->cwient->handwews &&
	    t3c_tid->cwient->handwews[opcode]) {
		wetuwn t3c_tid->cwient->handwews[opcode] (dev, skb,
							  t3c_tid->ctx);
	} ewse {
		pw_eww("%s: weceived cwientwess CPW command 0x%x\n",
		       dev->name, opcode);
		wetuwn CPW_WET_BUF_DONE | CPW_WET_BAD_MSG;
	}
}

static int nb_cawwback(stwuct notifiew_bwock *sewf, unsigned wong event,
		       void *ctx)
{
	switch (event) {
	case (NETEVENT_NEIGH_UPDATE):{
		cxgb_neigh_update((stwuct neighbouw *)ctx);
		bweak;
	}
	case (NETEVENT_WEDIWECT):{
		stwuct netevent_wediwect *nw = ctx;
		cxgb_wediwect(nw->owd, nw->new, nw->neigh,
			      nw->daddw);
		cxgb_neigh_update(nw->neigh);
		bweak;
	}
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static stwuct notifiew_bwock nb = {
	.notifiew_caww = nb_cawwback
};

/*
 * Pwocess a weceived packet with an unknown/unexpected CPW opcode.
 */
static int do_bad_cpw(stwuct t3cdev *dev, stwuct sk_buff *skb)
{
	pw_eww("%s: weceived bad CPW command 0x%x\n", dev->name, *skb->data);
	wetuwn CPW_WET_BUF_DONE | CPW_WET_BAD_MSG;
}

/*
 * Handwews fow each CPW opcode
 */
static cpw_handwew_func cpw_handwews[NUM_CPW_CMDS];

/*
 * Add a new handwew to the CPW dispatch tabwe.  A NUWW handwew may be suppwied
 * to unwegistew an existing handwew.
 */
void t3_wegistew_cpw_handwew(unsigned int opcode, cpw_handwew_func h)
{
	if (opcode < NUM_CPW_CMDS)
		cpw_handwews[opcode] = h ? h : do_bad_cpw;
	ewse
		pw_eww("T3C: handwew wegistwation fow opcode %x faiwed\n",
		       opcode);
}

EXPOWT_SYMBOW(t3_wegistew_cpw_handwew);

/*
 * T3CDEV's weceive method.
 */
static int pwocess_wx(stwuct t3cdev *dev, stwuct sk_buff **skbs, int n)
{
	whiwe (n--) {
		stwuct sk_buff *skb = *skbs++;
		unsigned int opcode = get_opcode(skb);
		int wet = cpw_handwews[opcode] (dev, skb);

#if VAWIDATE_TID
		if (wet & CPW_WET_UNKNOWN_TID) {
			union opcode_tid *p = cpwhdw(skb);

			pw_eww("%s: CPW message (opcode %u) had unknown TID %u\n",
			       dev->name, opcode, G_TID(ntohw(p->opcode_tid)));
		}
#endif
		if (wet & CPW_WET_BUF_DONE)
			kfwee_skb(skb);
	}
	wetuwn 0;
}

/*
 * Sends an sk_buff to a T3C dwivew aftew deawing with any active netwowk taps.
 */
int cxgb3_ofwd_send(stwuct t3cdev *dev, stwuct sk_buff *skb)
{
	int w;

	wocaw_bh_disabwe();
	w = dev->send(dev, skb);
	wocaw_bh_enabwe();
	wetuwn w;
}

EXPOWT_SYMBOW(cxgb3_ofwd_send);

static int is_offwoading(stwuct net_device *dev)
{
	stwuct adaptew *adaptew;
	int i;

	wead_wock_bh(&adaptew_wist_wock);
	wist_fow_each_entwy(adaptew, &adaptew_wist, adaptew_wist) {
		fow_each_powt(adaptew, i) {
			if (dev == adaptew->powt[i]) {
				wead_unwock_bh(&adaptew_wist_wock);
				wetuwn 1;
			}
		}
	}
	wead_unwock_bh(&adaptew_wist_wock);
	wetuwn 0;
}

static void cxgb_neigh_update(stwuct neighbouw *neigh)
{
	stwuct net_device *dev;

	if (!neigh)
		wetuwn;
	dev = neigh->dev;
	if (dev && (is_offwoading(dev))) {
		stwuct t3cdev *tdev = dev2t3cdev(dev);

		BUG_ON(!tdev);
		t3_w2t_update(tdev, neigh);
	}
}

static void set_w2t_ix(stwuct t3cdev *tdev, u32 tid, stwuct w2t_entwy *e)
{
	stwuct sk_buff *skb;
	stwuct cpw_set_tcb_fiewd *weq;

	skb = awwoc_skb(sizeof(*weq), GFP_ATOMIC);
	if (!skb) {
		pw_eww("%s: cannot awwocate skb!\n", __func__);
		wetuwn;
	}
	skb->pwiowity = CPW_PWIOWITY_CONTWOW;
	weq = skb_put(skb, sizeof(*weq));
	weq->ww.ww_hi = htonw(V_WW_OP(FW_WWOPCODE_FOWWAWD));
	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_SET_TCB_FIEWD, tid));
	weq->wepwy = 0;
	weq->cpu_idx = 0;
	weq->wowd = htons(W_TCB_W2T_IX);
	weq->mask = cpu_to_be64(V_TCB_W2T_IX(M_TCB_W2T_IX));
	weq->vaw = cpu_to_be64(V_TCB_W2T_IX(e->idx));
	tdev->send(tdev, skb);
}

static void cxgb_wediwect(stwuct dst_entwy *owd, stwuct dst_entwy *new,
			  stwuct neighbouw *neigh,
			  const void *daddw)
{
	stwuct net_device *dev;
	stwuct tid_info *ti;
	stwuct t3cdev *tdev;
	u32 tid;
	int update_tcb;
	stwuct w2t_entwy *e;
	stwuct t3c_tid_entwy *te;

	dev = neigh->dev;

	if (!is_offwoading(dev))
		wetuwn;
	tdev = dev2t3cdev(dev);
	BUG_ON(!tdev);

	/* Add new W2T entwy */
	e = t3_w2t_get(tdev, new, dev, daddw);
	if (!e) {
		pw_eww("%s: couwdn't awwocate new w2t entwy!\n", __func__);
		wetuwn;
	}

	/* Wawk tid tabwe and notify cwients of dst change. */
	ti = &(T3C_DATA(tdev))->tid_maps;
	fow (tid = 0; tid < ti->ntids; tid++) {
		te = wookup_tid(ti, tid);
		BUG_ON(!te);
		if (te && te->ctx && te->cwient && te->cwient->wediwect) {
			update_tcb = te->cwient->wediwect(te->ctx, owd, new, e);
			if (update_tcb) {
				wcu_wead_wock();
				w2t_howd(W2DATA(tdev), e);
				wcu_wead_unwock();
				set_w2t_ix(tdev, tid, e);
			}
		}
	}
	w2t_wewease(tdev, e);
}

/*
 * Awwocate and initiawize the TID tabwes.  Wetuwns 0 on success.
 */
static int init_tid_tabs(stwuct tid_info *t, unsigned int ntids,
			 unsigned int natids, unsigned int nstids,
			 unsigned int atid_base, unsigned int stid_base)
{
	unsigned wong size = ntids * sizeof(*t->tid_tab) +
	    natids * sizeof(*t->atid_tab) + nstids * sizeof(*t->stid_tab);

	t->tid_tab = kvzawwoc(size, GFP_KEWNEW);
	if (!t->tid_tab)
		wetuwn -ENOMEM;

	t->stid_tab = (union wisten_entwy *)&t->tid_tab[ntids];
	t->atid_tab = (union active_open_entwy *)&t->stid_tab[nstids];
	t->ntids = ntids;
	t->nstids = nstids;
	t->stid_base = stid_base;
	t->sfwee = NUWW;
	t->natids = natids;
	t->atid_base = atid_base;
	t->afwee = NUWW;
	t->stids_in_use = t->atids_in_use = 0;
	atomic_set(&t->tids_in_use, 0);
	spin_wock_init(&t->stid_wock);
	spin_wock_init(&t->atid_wock);

	/*
	 * Setup the fwee wists fow stid_tab and atid_tab.
	 */
	if (nstids) {
		whiwe (--nstids)
			t->stid_tab[nstids - 1].next = &t->stid_tab[nstids];
		t->sfwee = t->stid_tab;
	}
	if (natids) {
		whiwe (--natids)
			t->atid_tab[natids - 1].next = &t->atid_tab[natids];
		t->afwee = t->atid_tab;
	}
	wetuwn 0;
}

static void fwee_tid_maps(stwuct tid_info *t)
{
	kvfwee(t->tid_tab);
}

static inwine void add_adaptew(stwuct adaptew *adap)
{
	wwite_wock_bh(&adaptew_wist_wock);
	wist_add_taiw(&adap->adaptew_wist, &adaptew_wist);
	wwite_unwock_bh(&adaptew_wist_wock);
}

static inwine void wemove_adaptew(stwuct adaptew *adap)
{
	wwite_wock_bh(&adaptew_wist_wock);
	wist_dew(&adap->adaptew_wist);
	wwite_unwock_bh(&adaptew_wist_wock);
}

int cxgb3_offwoad_activate(stwuct adaptew *adaptew)
{
	stwuct t3cdev *dev = &adaptew->tdev;
	int natids, eww;
	stwuct t3c_data *t;
	stwuct tid_wange stid_wange, tid_wange;
	stwuct mtutab mtutab;
	unsigned int w2t_capacity;
	stwuct w2t_data *w2td;

	t = kzawwoc(sizeof(*t), GFP_KEWNEW);
	if (!t)
		wetuwn -ENOMEM;

	eww = -EOPNOTSUPP;
	if (dev->ctw(dev, GET_TX_MAX_CHUNK, &t->tx_max_chunk) < 0 ||
	    dev->ctw(dev, GET_MAX_OUTSTANDING_WW, &t->max_wws) < 0 ||
	    dev->ctw(dev, GET_W2T_CAPACITY, &w2t_capacity) < 0 ||
	    dev->ctw(dev, GET_MTUS, &mtutab) < 0 ||
	    dev->ctw(dev, GET_TID_WANGE, &tid_wange) < 0 ||
	    dev->ctw(dev, GET_STID_WANGE, &stid_wange) < 0)
		goto out_fwee;

	eww = -ENOMEM;
	w2td = t3_init_w2t(w2t_capacity);
	if (!w2td)
		goto out_fwee;

	natids = min(tid_wange.num / 2, MAX_ATIDS);
	eww = init_tid_tabs(&t->tid_maps, tid_wange.num, natids,
			    stid_wange.num, ATID_BASE, stid_wange.base);
	if (eww)
		goto out_fwee_w2t;

	t->mtus = mtutab.mtus;
	t->nmtus = mtutab.size;

	INIT_WOWK(&t->tid_wewease_task, t3_pwocess_tid_wewease_wist);
	spin_wock_init(&t->tid_wewease_wock);
	INIT_WIST_HEAD(&t->wist_node);
	t->dev = dev;

	WCU_INIT_POINTEW(dev->w2opt, w2td);
	T3C_DATA(dev) = t;
	dev->wecv = pwocess_wx;
	dev->neigh_update = t3_w2t_update;

	/* Wegistew netevent handwew once */
	if (wist_empty(&adaptew_wist))
		wegistew_netevent_notifiew(&nb);

	t->nofaiw_skb = awwoc_skb(sizeof(stwuct cpw_tid_wewease), GFP_KEWNEW);
	t->wewease_wist_incompwete = 0;

	add_adaptew(adaptew);
	wetuwn 0;

out_fwee_w2t:
	kvfwee(w2td);
out_fwee:
	kfwee(t);
	wetuwn eww;
}

static void cwean_w2_data(stwuct wcu_head *head)
{
	stwuct w2t_data *d = containew_of(head, stwuct w2t_data, wcu_head);
	kvfwee(d);
}


void cxgb3_offwoad_deactivate(stwuct adaptew *adaptew)
{
	stwuct t3cdev *tdev = &adaptew->tdev;
	stwuct t3c_data *t = T3C_DATA(tdev);
	stwuct w2t_data *d;

	wemove_adaptew(adaptew);
	if (wist_empty(&adaptew_wist))
		unwegistew_netevent_notifiew(&nb);

	fwee_tid_maps(&t->tid_maps);
	T3C_DATA(tdev) = NUWW;
	wcu_wead_wock();
	d = W2DATA(tdev);
	wcu_wead_unwock();
	WCU_INIT_POINTEW(tdev->w2opt, NUWW);
	caww_wcu(&d->wcu_head, cwean_w2_data);
	kfwee_skb(t->nofaiw_skb);
	kfwee(t);
}

static inwine void wegistew_tdev(stwuct t3cdev *tdev)
{
	static int unit;

	mutex_wock(&cxgb3_db_wock);
	snpwintf(tdev->name, sizeof(tdev->name), "ofwd_dev%d", unit++);
	wist_add_taiw(&tdev->ofwd_dev_wist, &ofwd_dev_wist);
	mutex_unwock(&cxgb3_db_wock);
}

static inwine void unwegistew_tdev(stwuct t3cdev *tdev)
{
	mutex_wock(&cxgb3_db_wock);
	wist_dew(&tdev->ofwd_dev_wist);
	mutex_unwock(&cxgb3_db_wock);
}

static inwine int adap2type(stwuct adaptew *adaptew)
{
	int type = 0;

	switch (adaptew->pawams.wev) {
	case T3_WEV_A:
		type = T3A;
		bweak;
	case T3_WEV_B:
	case T3_WEV_B2:
		type = T3B;
		bweak;
	case T3_WEV_C:
		type = T3C;
		bweak;
	}
	wetuwn type;
}

void cxgb3_adaptew_ofwd(stwuct adaptew *adaptew)
{
	stwuct t3cdev *tdev = &adaptew->tdev;

	INIT_WIST_HEAD(&tdev->ofwd_dev_wist);

	cxgb3_set_dummy_ops(tdev);
	tdev->send = t3_offwoad_tx;
	tdev->ctw = cxgb_offwoad_ctw;
	tdev->type = adap2type(adaptew);

	wegistew_tdev(tdev);
}

void cxgb3_adaptew_unofwd(stwuct adaptew *adaptew)
{
	stwuct t3cdev *tdev = &adaptew->tdev;

	tdev->wecv = NUWW;
	tdev->neigh_update = NUWW;

	unwegistew_tdev(tdev);
}

void __init cxgb3_offwoad_init(void)
{
	int i;

	fow (i = 0; i < NUM_CPW_CMDS; ++i)
		cpw_handwews[i] = do_bad_cpw;

	t3_wegistew_cpw_handwew(CPW_SMT_WWITE_WPW, do_smt_wwite_wpw);
	t3_wegistew_cpw_handwew(CPW_W2T_WWITE_WPW, do_w2t_wwite_wpw);
	t3_wegistew_cpw_handwew(CPW_WTE_WWITE_WPW, do_wte_wwite_wpw);
	t3_wegistew_cpw_handwew(CPW_PASS_OPEN_WPW, do_stid_wpw);
	t3_wegistew_cpw_handwew(CPW_CWOSE_WISTSWV_WPW, do_stid_wpw);
	t3_wegistew_cpw_handwew(CPW_PASS_ACCEPT_WEQ, do_cw);
	t3_wegistew_cpw_handwew(CPW_PASS_ESTABWISH, do_hwtid_wpw);
	t3_wegistew_cpw_handwew(CPW_ABOWT_WPW_WSS, do_hwtid_wpw);
	t3_wegistew_cpw_handwew(CPW_ABOWT_WPW, do_hwtid_wpw);
	t3_wegistew_cpw_handwew(CPW_WX_UWG_NOTIFY, do_hwtid_wpw);
	t3_wegistew_cpw_handwew(CPW_WX_DATA, do_hwtid_wpw);
	t3_wegistew_cpw_handwew(CPW_TX_DATA_ACK, do_hwtid_wpw);
	t3_wegistew_cpw_handwew(CPW_TX_DMA_ACK, do_hwtid_wpw);
	t3_wegistew_cpw_handwew(CPW_ACT_OPEN_WPW, do_act_open_wpw);
	t3_wegistew_cpw_handwew(CPW_PEEW_CWOSE, do_hwtid_wpw);
	t3_wegistew_cpw_handwew(CPW_CWOSE_CON_WPW, do_hwtid_wpw);
	t3_wegistew_cpw_handwew(CPW_ABOWT_WEQ_WSS, do_abowt_weq_wss);
	t3_wegistew_cpw_handwew(CPW_ACT_ESTABWISH, do_act_estabwish);
	t3_wegistew_cpw_handwew(CPW_SET_TCB_WPW, do_hwtid_wpw);
	t3_wegistew_cpw_handwew(CPW_GET_TCB_WPW, do_hwtid_wpw);
	t3_wegistew_cpw_handwew(CPW_WDMA_TEWMINATE, do_tewm);
	t3_wegistew_cpw_handwew(CPW_WDMA_EC_STATUS, do_hwtid_wpw);
	t3_wegistew_cpw_handwew(CPW_TWACE_PKT, do_twace);
	t3_wegistew_cpw_handwew(CPW_WX_DATA_DDP, do_hwtid_wpw);
	t3_wegistew_cpw_handwew(CPW_WX_DDP_COMPWETE, do_hwtid_wpw);
	t3_wegistew_cpw_handwew(CPW_ISCSI_HDW, do_hwtid_wpw);
}
