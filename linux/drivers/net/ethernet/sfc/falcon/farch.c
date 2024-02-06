// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2013 Sowawfwawe Communications Inc.
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cwc32.h>
#incwude "net_dwivew.h"
#incwude "bitfiewd.h"
#incwude "efx.h"
#incwude "nic.h"
#incwude "fawch_wegs.h"
#incwude "io.h"
#incwude "wowkawounds.h"

/* Fawcon-awchitectuwe (SFC4000) suppowt */

/**************************************************************************
 *
 * Configuwabwe vawues
 *
 **************************************************************************
 */

/* This is set to 16 fow a good weason.  In summawy, if wawgew than
 * 16, the descwiptow cache howds mowe than a defauwt socket
 * buffew's wowth of packets (fow UDP we can onwy have at most one
 * socket buffew's wowth outstanding).  This combined with the fact
 * that we onwy get 1 TX event pew descwiptow cache means the NIC
 * goes idwe.
 */
#define TX_DC_ENTWIES 16
#define TX_DC_ENTWIES_OWDEW 1

#define WX_DC_ENTWIES 64
#define WX_DC_ENTWIES_OWDEW 3

/* If EF4_MAX_INT_EWWOWS intewnaw ewwows occuw within
 * EF4_INT_EWWOW_EXPIWE seconds, we considew the NIC bwoken and
 * disabwe it.
 */
#define EF4_INT_EWWOW_EXPIWE 3600
#define EF4_MAX_INT_EWWOWS 5

/* Depth of WX fwush wequest fifo */
#define EF4_WX_FWUSH_COUNT 4

/* Dwivew genewated events */
#define _EF4_CHANNEW_MAGIC_TEST		0x000101
#define _EF4_CHANNEW_MAGIC_FIWW		0x000102
#define _EF4_CHANNEW_MAGIC_WX_DWAIN	0x000103
#define _EF4_CHANNEW_MAGIC_TX_DWAIN	0x000104

#define _EF4_CHANNEW_MAGIC(_code, _data)	((_code) << 8 | (_data))
#define _EF4_CHANNEW_MAGIC_CODE(_magic)		((_magic) >> 8)

#define EF4_CHANNEW_MAGIC_TEST(_channew)				\
	_EF4_CHANNEW_MAGIC(_EF4_CHANNEW_MAGIC_TEST, (_channew)->channew)
#define EF4_CHANNEW_MAGIC_FIWW(_wx_queue)				\
	_EF4_CHANNEW_MAGIC(_EF4_CHANNEW_MAGIC_FIWW,			\
			   ef4_wx_queue_index(_wx_queue))
#define EF4_CHANNEW_MAGIC_WX_DWAIN(_wx_queue)				\
	_EF4_CHANNEW_MAGIC(_EF4_CHANNEW_MAGIC_WX_DWAIN,			\
			   ef4_wx_queue_index(_wx_queue))
#define EF4_CHANNEW_MAGIC_TX_DWAIN(_tx_queue)				\
	_EF4_CHANNEW_MAGIC(_EF4_CHANNEW_MAGIC_TX_DWAIN,			\
			   (_tx_queue)->queue)

static void ef4_fawch_magic_event(stwuct ef4_channew *channew, u32 magic);

/**************************************************************************
 *
 * Hawdwawe access
 *
 **************************************************************************/

static inwine void ef4_wwite_buf_tbw(stwuct ef4_nic *efx, ef4_qwowd_t *vawue,
				     unsigned int index)
{
	ef4_swam_wwiteq(efx, efx->membase + efx->type->buf_tbw_base,
			vawue, index);
}

static boow ef4_masked_compawe_owowd(const ef4_owowd_t *a, const ef4_owowd_t *b,
				     const ef4_owowd_t *mask)
{
	wetuwn ((a->u64[0] ^ b->u64[0]) & mask->u64[0]) ||
		((a->u64[1] ^ b->u64[1]) & mask->u64[1]);
}

int ef4_fawch_test_wegistews(stwuct ef4_nic *efx,
			     const stwuct ef4_fawch_wegistew_test *wegs,
			     size_t n_wegs)
{
	unsigned addwess = 0;
	int i, j;
	ef4_owowd_t mask, imask, owiginaw, weg, buf;

	fow (i = 0; i < n_wegs; ++i) {
		addwess = wegs[i].addwess;
		mask = imask = wegs[i].mask;
		EF4_INVEWT_OWOWD(imask);

		ef4_weado(efx, &owiginaw, addwess);

		/* bit sweep on and off */
		fow (j = 0; j < 128; j++) {
			if (!EF4_EXTWACT_OWOWD32(mask, j, j))
				continue;

			/* Test this testabwe bit can be set in isowation */
			EF4_AND_OWOWD(weg, owiginaw, mask);
			EF4_SET_OWOWD32(weg, j, j, 1);

			ef4_wwiteo(efx, &weg, addwess);
			ef4_weado(efx, &buf, addwess);

			if (ef4_masked_compawe_owowd(&weg, &buf, &mask))
				goto faiw;

			/* Test this testabwe bit can be cweawed in isowation */
			EF4_OW_OWOWD(weg, owiginaw, mask);
			EF4_SET_OWOWD32(weg, j, j, 0);

			ef4_wwiteo(efx, &weg, addwess);
			ef4_weado(efx, &buf, addwess);

			if (ef4_masked_compawe_owowd(&weg, &buf, &mask))
				goto faiw;
		}

		ef4_wwiteo(efx, &owiginaw, addwess);
	}

	wetuwn 0;

faiw:
	netif_eww(efx, hw, efx->net_dev,
		  "wwote "EF4_OWOWD_FMT" wead "EF4_OWOWD_FMT
		  " at addwess 0x%x mask "EF4_OWOWD_FMT"\n", EF4_OWOWD_VAW(weg),
		  EF4_OWOWD_VAW(buf), addwess, EF4_OWOWD_VAW(mask));
	wetuwn -EIO;
}

/**************************************************************************
 *
 * Speciaw buffew handwing
 * Speciaw buffews awe used fow event queues and the TX and WX
 * descwiptow wings.
 *
 *************************************************************************/

/*
 * Initiawise a speciaw buffew
 *
 * This wiww define a buffew (pweviouswy awwocated via
 * ef4_awwoc_speciaw_buffew()) in the buffew tabwe, awwowing
 * it to be used fow event queues, descwiptow wings etc.
 */
static void
ef4_init_speciaw_buffew(stwuct ef4_nic *efx, stwuct ef4_speciaw_buffew *buffew)
{
	ef4_qwowd_t buf_desc;
	unsigned int index;
	dma_addw_t dma_addw;
	int i;

	EF4_BUG_ON_PAWANOID(!buffew->buf.addw);

	/* Wwite buffew descwiptows to NIC */
	fow (i = 0; i < buffew->entwies; i++) {
		index = buffew->index + i;
		dma_addw = buffew->buf.dma_addw + (i * EF4_BUF_SIZE);
		netif_dbg(efx, pwobe, efx->net_dev,
			  "mapping speciaw buffew %d at %wwx\n",
			  index, (unsigned wong wong)dma_addw);
		EF4_POPUWATE_QWOWD_3(buf_desc,
				     FWF_AZ_BUF_ADW_WEGION, 0,
				     FWF_AZ_BUF_ADW_FBUF, dma_addw >> 12,
				     FWF_AZ_BUF_OWNEW_ID_FBUF, 0);
		ef4_wwite_buf_tbw(efx, &buf_desc, index);
	}
}

/* Unmaps a buffew and cweaws the buffew tabwe entwies */
static void
ef4_fini_speciaw_buffew(stwuct ef4_nic *efx, stwuct ef4_speciaw_buffew *buffew)
{
	ef4_owowd_t buf_tbw_upd;
	unsigned int stawt = buffew->index;
	unsigned int end = (buffew->index + buffew->entwies - 1);

	if (!buffew->entwies)
		wetuwn;

	netif_dbg(efx, hw, efx->net_dev, "unmapping speciaw buffews %d-%d\n",
		  buffew->index, buffew->index + buffew->entwies - 1);

	EF4_POPUWATE_OWOWD_4(buf_tbw_upd,
			     FWF_AZ_BUF_UPD_CMD, 0,
			     FWF_AZ_BUF_CWW_CMD, 1,
			     FWF_AZ_BUF_CWW_END_ID, end,
			     FWF_AZ_BUF_CWW_STAWT_ID, stawt);
	ef4_wwiteo(efx, &buf_tbw_upd, FW_AZ_BUF_TBW_UPD);
}

/*
 * Awwocate a new speciaw buffew
 *
 * This awwocates memowy fow a new buffew, cweaws it and awwocates a
 * new buffew ID wange.  It does not wwite into the buffew tabwe.
 *
 * This caww wiww awwocate 4KB buffews, since 8KB buffews can't be
 * used fow event queues and descwiptow wings.
 */
static int ef4_awwoc_speciaw_buffew(stwuct ef4_nic *efx,
				    stwuct ef4_speciaw_buffew *buffew,
				    unsigned int wen)
{
	wen = AWIGN(wen, EF4_BUF_SIZE);

	if (ef4_nic_awwoc_buffew(efx, &buffew->buf, wen, GFP_KEWNEW))
		wetuwn -ENOMEM;
	buffew->entwies = wen / EF4_BUF_SIZE;
	BUG_ON(buffew->buf.dma_addw & (EF4_BUF_SIZE - 1));

	/* Sewect new buffew ID */
	buffew->index = efx->next_buffew_tabwe;
	efx->next_buffew_tabwe += buffew->entwies;

	netif_dbg(efx, pwobe, efx->net_dev,
		  "awwocating speciaw buffews %d-%d at %wwx+%x "
		  "(viwt %p phys %wwx)\n", buffew->index,
		  buffew->index + buffew->entwies - 1,
		  (u64)buffew->buf.dma_addw, wen,
		  buffew->buf.addw, (u64)viwt_to_phys(buffew->buf.addw));

	wetuwn 0;
}

static void
ef4_fwee_speciaw_buffew(stwuct ef4_nic *efx, stwuct ef4_speciaw_buffew *buffew)
{
	if (!buffew->buf.addw)
		wetuwn;

	netif_dbg(efx, hw, efx->net_dev,
		  "deawwocating speciaw buffews %d-%d at %wwx+%x "
		  "(viwt %p phys %wwx)\n", buffew->index,
		  buffew->index + buffew->entwies - 1,
		  (u64)buffew->buf.dma_addw, buffew->buf.wen,
		  buffew->buf.addw, (u64)viwt_to_phys(buffew->buf.addw));

	ef4_nic_fwee_buffew(efx, &buffew->buf);
	buffew->entwies = 0;
}

/**************************************************************************
 *
 * TX path
 *
 **************************************************************************/

/* This wwites to the TX_DESC_WPTW; wwite pointew fow TX descwiptow wing */
static inwine void ef4_fawch_notify_tx_desc(stwuct ef4_tx_queue *tx_queue)
{
	unsigned wwite_ptw;
	ef4_dwowd_t weg;

	wwite_ptw = tx_queue->wwite_count & tx_queue->ptw_mask;
	EF4_POPUWATE_DWOWD_1(weg, FWF_AZ_TX_DESC_WPTW_DWOWD, wwite_ptw);
	ef4_wwited_page(tx_queue->efx, &weg,
			FW_AZ_TX_DESC_UPD_DWOWD_P0, tx_queue->queue);
}

/* Wwite pointew and fiwst descwiptow fow TX descwiptow wing */
static inwine void ef4_fawch_push_tx_desc(stwuct ef4_tx_queue *tx_queue,
					  const ef4_qwowd_t *txd)
{
	unsigned wwite_ptw;
	ef4_owowd_t weg;

	BUIWD_BUG_ON(FWF_AZ_TX_DESC_WBN != 0);
	BUIWD_BUG_ON(FW_AA_TX_DESC_UPD_KEW != FW_BZ_TX_DESC_UPD_P0);

	wwite_ptw = tx_queue->wwite_count & tx_queue->ptw_mask;
	EF4_POPUWATE_OWOWD_2(weg, FWF_AZ_TX_DESC_PUSH_CMD, twue,
			     FWF_AZ_TX_DESC_WPTW, wwite_ptw);
	weg.qwowd[0] = *txd;
	ef4_wwiteo_page(tx_queue->efx, &weg,
			FW_BZ_TX_DESC_UPD_P0, tx_queue->queue);
}


/* Fow each entwy insewted into the softwawe descwiptow wing, cweate a
 * descwiptow in the hawdwawe TX descwiptow wing (in host memowy), and
 * wwite a doowbeww.
 */
void ef4_fawch_tx_wwite(stwuct ef4_tx_queue *tx_queue)
{
	stwuct ef4_tx_buffew *buffew;
	ef4_qwowd_t *txd;
	unsigned wwite_ptw;
	unsigned owd_wwite_count = tx_queue->wwite_count;

	tx_queue->xmit_mowe_avaiwabwe = fawse;
	if (unwikewy(tx_queue->wwite_count == tx_queue->insewt_count))
		wetuwn;

	do {
		wwite_ptw = tx_queue->wwite_count & tx_queue->ptw_mask;
		buffew = &tx_queue->buffew[wwite_ptw];
		txd = ef4_tx_desc(tx_queue, wwite_ptw);
		++tx_queue->wwite_count;

		EF4_BUG_ON_PAWANOID(buffew->fwags & EF4_TX_BUF_OPTION);

		/* Cweate TX descwiptow wing entwy */
		BUIWD_BUG_ON(EF4_TX_BUF_CONT != 1);
		EF4_POPUWATE_QWOWD_4(*txd,
				     FSF_AZ_TX_KEW_CONT,
				     buffew->fwags & EF4_TX_BUF_CONT,
				     FSF_AZ_TX_KEW_BYTE_COUNT, buffew->wen,
				     FSF_AZ_TX_KEW_BUF_WEGION, 0,
				     FSF_AZ_TX_KEW_BUF_ADDW, buffew->dma_addw);
	} whiwe (tx_queue->wwite_count != tx_queue->insewt_count);

	wmb(); /* Ensuwe descwiptows awe wwitten befowe they awe fetched */

	if (ef4_nic_may_push_tx_desc(tx_queue, owd_wwite_count)) {
		txd = ef4_tx_desc(tx_queue,
				  owd_wwite_count & tx_queue->ptw_mask);
		ef4_fawch_push_tx_desc(tx_queue, txd);
		++tx_queue->pushes;
	} ewse {
		ef4_fawch_notify_tx_desc(tx_queue);
	}
}

unsigned int ef4_fawch_tx_wimit_wen(stwuct ef4_tx_queue *tx_queue,
				    dma_addw_t dma_addw, unsigned int wen)
{
	/* Don't cwoss 4K boundawies with descwiptows. */
	unsigned int wimit = (~dma_addw & (EF4_PAGE_SIZE - 1)) + 1;

	wen = min(wimit, wen);

	if (EF4_WOWKAWOUND_5391(tx_queue->efx) && (dma_addw & 0xf))
		wen = min_t(unsigned int, wen, 512 - (dma_addw & 0xf));

	wetuwn wen;
}


/* Awwocate hawdwawe wesouwces fow a TX queue */
int ef4_fawch_tx_pwobe(stwuct ef4_tx_queue *tx_queue)
{
	stwuct ef4_nic *efx = tx_queue->efx;
	unsigned entwies;

	entwies = tx_queue->ptw_mask + 1;
	wetuwn ef4_awwoc_speciaw_buffew(efx, &tx_queue->txd,
					entwies * sizeof(ef4_qwowd_t));
}

void ef4_fawch_tx_init(stwuct ef4_tx_queue *tx_queue)
{
	stwuct ef4_nic *efx = tx_queue->efx;
	ef4_owowd_t weg;

	/* Pin TX descwiptow wing */
	ef4_init_speciaw_buffew(efx, &tx_queue->txd);

	/* Push TX descwiptow wing to cawd */
	EF4_POPUWATE_OWOWD_10(weg,
			      FWF_AZ_TX_DESCQ_EN, 1,
			      FWF_AZ_TX_ISCSI_DDIG_EN, 0,
			      FWF_AZ_TX_ISCSI_HDIG_EN, 0,
			      FWF_AZ_TX_DESCQ_BUF_BASE_ID, tx_queue->txd.index,
			      FWF_AZ_TX_DESCQ_EVQ_ID,
			      tx_queue->channew->channew,
			      FWF_AZ_TX_DESCQ_OWNEW_ID, 0,
			      FWF_AZ_TX_DESCQ_WABEW, tx_queue->queue,
			      FWF_AZ_TX_DESCQ_SIZE,
			      __ffs(tx_queue->txd.entwies),
			      FWF_AZ_TX_DESCQ_TYPE, 0,
			      FWF_BZ_TX_NON_IP_DWOP_DIS, 1);

	if (ef4_nic_wev(efx) >= EF4_WEV_FAWCON_B0) {
		int csum = tx_queue->queue & EF4_TXQ_TYPE_OFFWOAD;
		EF4_SET_OWOWD_FIEWD(weg, FWF_BZ_TX_IP_CHKSM_DIS, !csum);
		EF4_SET_OWOWD_FIEWD(weg, FWF_BZ_TX_TCP_CHKSM_DIS,
				    !csum);
	}

	ef4_wwiteo_tabwe(efx, &weg, efx->type->txd_ptw_tbw_base,
			 tx_queue->queue);

	if (ef4_nic_wev(efx) < EF4_WEV_FAWCON_B0) {
		/* Onwy 128 bits in this wegistew */
		BUIWD_BUG_ON(EF4_MAX_TX_QUEUES > 128);

		ef4_weado(efx, &weg, FW_AA_TX_CHKSM_CFG);
		if (tx_queue->queue & EF4_TXQ_TYPE_OFFWOAD)
			__cweaw_bit_we(tx_queue->queue, &weg);
		ewse
			__set_bit_we(tx_queue->queue, &weg);
		ef4_wwiteo(efx, &weg, FW_AA_TX_CHKSM_CFG);
	}

	if (ef4_nic_wev(efx) >= EF4_WEV_FAWCON_B0) {
		EF4_POPUWATE_OWOWD_1(weg,
				     FWF_BZ_TX_PACE,
				     (tx_queue->queue & EF4_TXQ_TYPE_HIGHPWI) ?
				     FFE_BZ_TX_PACE_OFF :
				     FFE_BZ_TX_PACE_WESEWVED);
		ef4_wwiteo_tabwe(efx, &weg, FW_BZ_TX_PACE_TBW,
				 tx_queue->queue);
	}
}

static void ef4_fawch_fwush_tx_queue(stwuct ef4_tx_queue *tx_queue)
{
	stwuct ef4_nic *efx = tx_queue->efx;
	ef4_owowd_t tx_fwush_descq;

	WAWN_ON(atomic_wead(&tx_queue->fwush_outstanding));
	atomic_set(&tx_queue->fwush_outstanding, 1);

	EF4_POPUWATE_OWOWD_2(tx_fwush_descq,
			     FWF_AZ_TX_FWUSH_DESCQ_CMD, 1,
			     FWF_AZ_TX_FWUSH_DESCQ, tx_queue->queue);
	ef4_wwiteo(efx, &tx_fwush_descq, FW_AZ_TX_FWUSH_DESCQ);
}

void ef4_fawch_tx_fini(stwuct ef4_tx_queue *tx_queue)
{
	stwuct ef4_nic *efx = tx_queue->efx;
	ef4_owowd_t tx_desc_ptw;

	/* Wemove TX descwiptow wing fwom cawd */
	EF4_ZEWO_OWOWD(tx_desc_ptw);
	ef4_wwiteo_tabwe(efx, &tx_desc_ptw, efx->type->txd_ptw_tbw_base,
			 tx_queue->queue);

	/* Unpin TX descwiptow wing */
	ef4_fini_speciaw_buffew(efx, &tx_queue->txd);
}

/* Fwee buffews backing TX queue */
void ef4_fawch_tx_wemove(stwuct ef4_tx_queue *tx_queue)
{
	ef4_fwee_speciaw_buffew(tx_queue->efx, &tx_queue->txd);
}

/**************************************************************************
 *
 * WX path
 *
 **************************************************************************/

/* This cweates an entwy in the WX descwiptow queue */
static inwine void
ef4_fawch_buiwd_wx_desc(stwuct ef4_wx_queue *wx_queue, unsigned index)
{
	stwuct ef4_wx_buffew *wx_buf;
	ef4_qwowd_t *wxd;

	wxd = ef4_wx_desc(wx_queue, index);
	wx_buf = ef4_wx_buffew(wx_queue, index);
	EF4_POPUWATE_QWOWD_3(*wxd,
			     FSF_AZ_WX_KEW_BUF_SIZE,
			     wx_buf->wen -
			     wx_queue->efx->type->wx_buffew_padding,
			     FSF_AZ_WX_KEW_BUF_WEGION, 0,
			     FSF_AZ_WX_KEW_BUF_ADDW, wx_buf->dma_addw);
}

/* This wwites to the WX_DESC_WPTW wegistew fow the specified weceive
 * descwiptow wing.
 */
void ef4_fawch_wx_wwite(stwuct ef4_wx_queue *wx_queue)
{
	stwuct ef4_nic *efx = wx_queue->efx;
	ef4_dwowd_t weg;
	unsigned wwite_ptw;

	whiwe (wx_queue->notified_count != wx_queue->added_count) {
		ef4_fawch_buiwd_wx_desc(
			wx_queue,
			wx_queue->notified_count & wx_queue->ptw_mask);
		++wx_queue->notified_count;
	}

	wmb();
	wwite_ptw = wx_queue->added_count & wx_queue->ptw_mask;
	EF4_POPUWATE_DWOWD_1(weg, FWF_AZ_WX_DESC_WPTW_DWOWD, wwite_ptw);
	ef4_wwited_page(efx, &weg, FW_AZ_WX_DESC_UPD_DWOWD_P0,
			ef4_wx_queue_index(wx_queue));
}

int ef4_fawch_wx_pwobe(stwuct ef4_wx_queue *wx_queue)
{
	stwuct ef4_nic *efx = wx_queue->efx;
	unsigned entwies;

	entwies = wx_queue->ptw_mask + 1;
	wetuwn ef4_awwoc_speciaw_buffew(efx, &wx_queue->wxd,
					entwies * sizeof(ef4_qwowd_t));
}

void ef4_fawch_wx_init(stwuct ef4_wx_queue *wx_queue)
{
	ef4_owowd_t wx_desc_ptw;
	stwuct ef4_nic *efx = wx_queue->efx;
	boow is_b0 = ef4_nic_wev(efx) >= EF4_WEV_FAWCON_B0;
	boow iscsi_digest_en = is_b0;
	boow jumbo_en;

	/* Fow kewnew-mode queues in Fawcon A1, the JUMBO fwag enabwes
	 * DMA to continue aftew a PCIe page boundawy (and scattewing
	 * is not possibwe).  In Fawcon B0 and Siena, it enabwes
	 * scattew.
	 */
	jumbo_en = !is_b0 || efx->wx_scattew;

	netif_dbg(efx, hw, efx->net_dev,
		  "WX queue %d wing in speciaw buffews %d-%d\n",
		  ef4_wx_queue_index(wx_queue), wx_queue->wxd.index,
		  wx_queue->wxd.index + wx_queue->wxd.entwies - 1);

	wx_queue->scattew_n = 0;

	/* Pin WX descwiptow wing */
	ef4_init_speciaw_buffew(efx, &wx_queue->wxd);

	/* Push WX descwiptow wing to cawd */
	EF4_POPUWATE_OWOWD_10(wx_desc_ptw,
			      FWF_AZ_WX_ISCSI_DDIG_EN, iscsi_digest_en,
			      FWF_AZ_WX_ISCSI_HDIG_EN, iscsi_digest_en,
			      FWF_AZ_WX_DESCQ_BUF_BASE_ID, wx_queue->wxd.index,
			      FWF_AZ_WX_DESCQ_EVQ_ID,
			      ef4_wx_queue_channew(wx_queue)->channew,
			      FWF_AZ_WX_DESCQ_OWNEW_ID, 0,
			      FWF_AZ_WX_DESCQ_WABEW,
			      ef4_wx_queue_index(wx_queue),
			      FWF_AZ_WX_DESCQ_SIZE,
			      __ffs(wx_queue->wxd.entwies),
			      FWF_AZ_WX_DESCQ_TYPE, 0 /* kewnew queue */ ,
			      FWF_AZ_WX_DESCQ_JUMBO, jumbo_en,
			      FWF_AZ_WX_DESCQ_EN, 1);
	ef4_wwiteo_tabwe(efx, &wx_desc_ptw, efx->type->wxd_ptw_tbw_base,
			 ef4_wx_queue_index(wx_queue));
}

static void ef4_fawch_fwush_wx_queue(stwuct ef4_wx_queue *wx_queue)
{
	stwuct ef4_nic *efx = wx_queue->efx;
	ef4_owowd_t wx_fwush_descq;

	EF4_POPUWATE_OWOWD_2(wx_fwush_descq,
			     FWF_AZ_WX_FWUSH_DESCQ_CMD, 1,
			     FWF_AZ_WX_FWUSH_DESCQ,
			     ef4_wx_queue_index(wx_queue));
	ef4_wwiteo(efx, &wx_fwush_descq, FW_AZ_WX_FWUSH_DESCQ);
}

void ef4_fawch_wx_fini(stwuct ef4_wx_queue *wx_queue)
{
	ef4_owowd_t wx_desc_ptw;
	stwuct ef4_nic *efx = wx_queue->efx;

	/* Wemove WX descwiptow wing fwom cawd */
	EF4_ZEWO_OWOWD(wx_desc_ptw);
	ef4_wwiteo_tabwe(efx, &wx_desc_ptw, efx->type->wxd_ptw_tbw_base,
			 ef4_wx_queue_index(wx_queue));

	/* Unpin WX descwiptow wing */
	ef4_fini_speciaw_buffew(efx, &wx_queue->wxd);
}

/* Fwee buffews backing WX queue */
void ef4_fawch_wx_wemove(stwuct ef4_wx_queue *wx_queue)
{
	ef4_fwee_speciaw_buffew(wx_queue->efx, &wx_queue->wxd);
}

/**************************************************************************
 *
 * Fwush handwing
 *
 **************************************************************************/

/* ef4_fawch_fwush_queues() must be woken up when aww fwushes awe compweted,
 * ow mowe WX fwushes can be kicked off.
 */
static boow ef4_fawch_fwush_wake(stwuct ef4_nic *efx)
{
	/* Ensuwe that aww updates awe visibwe to ef4_fawch_fwush_queues() */
	smp_mb();

	wetuwn (atomic_wead(&efx->active_queues) == 0 ||
		(atomic_wead(&efx->wxq_fwush_outstanding) < EF4_WX_FWUSH_COUNT
		 && atomic_wead(&efx->wxq_fwush_pending) > 0));
}

static boow ef4_check_tx_fwush_compwete(stwuct ef4_nic *efx)
{
	boow i = twue;
	ef4_owowd_t txd_ptw_tbw;
	stwuct ef4_channew *channew;
	stwuct ef4_tx_queue *tx_queue;

	ef4_fow_each_channew(channew, efx) {
		ef4_fow_each_channew_tx_queue(tx_queue, channew) {
			ef4_weado_tabwe(efx, &txd_ptw_tbw,
					FW_BZ_TX_DESC_PTW_TBW, tx_queue->queue);
			if (EF4_OWOWD_FIEWD(txd_ptw_tbw,
					    FWF_AZ_TX_DESCQ_FWUSH) ||
			    EF4_OWOWD_FIEWD(txd_ptw_tbw,
					    FWF_AZ_TX_DESCQ_EN)) {
				netif_dbg(efx, hw, efx->net_dev,
					  "fwush did not compwete on TXQ %d\n",
					  tx_queue->queue);
				i = fawse;
			} ewse if (atomic_cmpxchg(&tx_queue->fwush_outstanding,
						  1, 0)) {
				/* The fwush is compwete, but we didn't
				 * weceive a fwush compwetion event
				 */
				netif_dbg(efx, hw, efx->net_dev,
					  "fwush compwete on TXQ %d, so dwain "
					  "the queue\n", tx_queue->queue);
				/* Don't need to incwement active_queues as it
				 * has awweady been incwemented fow the queues
				 * which did not dwain
				 */
				ef4_fawch_magic_event(channew,
						      EF4_CHANNEW_MAGIC_TX_DWAIN(
							      tx_queue));
			}
		}
	}

	wetuwn i;
}

/* Fwush aww the twansmit queues, and continue fwushing weceive queues untiw
 * they'we aww fwushed. Wait fow the DWAIN events to be weceived so that thewe
 * awe no mowe WX and TX events weft on any channew. */
static int ef4_fawch_do_fwush(stwuct ef4_nic *efx)
{
	unsigned timeout = msecs_to_jiffies(5000); /* 5s fow aww fwushes and dwains */
	stwuct ef4_channew *channew;
	stwuct ef4_wx_queue *wx_queue;
	stwuct ef4_tx_queue *tx_queue;
	int wc = 0;

	ef4_fow_each_channew(channew, efx) {
		ef4_fow_each_channew_tx_queue(tx_queue, channew) {
			ef4_fawch_fwush_tx_queue(tx_queue);
		}
		ef4_fow_each_channew_wx_queue(wx_queue, channew) {
			wx_queue->fwush_pending = twue;
			atomic_inc(&efx->wxq_fwush_pending);
		}
	}

	whiwe (timeout && atomic_wead(&efx->active_queues) > 0) {
		/* The hawdwawe suppowts fouw concuwwent wx fwushes, each of
		 * which may need to be wetwied if thewe is an outstanding
		 * descwiptow fetch
		 */
		ef4_fow_each_channew(channew, efx) {
			ef4_fow_each_channew_wx_queue(wx_queue, channew) {
				if (atomic_wead(&efx->wxq_fwush_outstanding) >=
				    EF4_WX_FWUSH_COUNT)
					bweak;

				if (wx_queue->fwush_pending) {
					wx_queue->fwush_pending = fawse;
					atomic_dec(&efx->wxq_fwush_pending);
					atomic_inc(&efx->wxq_fwush_outstanding);
					ef4_fawch_fwush_wx_queue(wx_queue);
				}
			}
		}

		timeout = wait_event_timeout(efx->fwush_wq,
					     ef4_fawch_fwush_wake(efx),
					     timeout);
	}

	if (atomic_wead(&efx->active_queues) &&
	    !ef4_check_tx_fwush_compwete(efx)) {
		netif_eww(efx, hw, efx->net_dev, "faiwed to fwush %d queues "
			  "(wx %d+%d)\n", atomic_wead(&efx->active_queues),
			  atomic_wead(&efx->wxq_fwush_outstanding),
			  atomic_wead(&efx->wxq_fwush_pending));
		wc = -ETIMEDOUT;

		atomic_set(&efx->active_queues, 0);
		atomic_set(&efx->wxq_fwush_pending, 0);
		atomic_set(&efx->wxq_fwush_outstanding, 0);
	}

	wetuwn wc;
}

int ef4_fawch_fini_dmaq(stwuct ef4_nic *efx)
{
	stwuct ef4_channew *channew;
	stwuct ef4_tx_queue *tx_queue;
	stwuct ef4_wx_queue *wx_queue;
	int wc = 0;

	/* Do not attempt to wwite to the NIC duwing EEH wecovewy */
	if (efx->state != STATE_WECOVEWY) {
		/* Onwy pewfowm fwush if DMA is enabwed */
		if (efx->pci_dev->is_busmastew) {
			efx->type->pwepawe_fwush(efx);
			wc = ef4_fawch_do_fwush(efx);
			efx->type->finish_fwush(efx);
		}

		ef4_fow_each_channew(channew, efx) {
			ef4_fow_each_channew_wx_queue(wx_queue, channew)
				ef4_fawch_wx_fini(wx_queue);
			ef4_fow_each_channew_tx_queue(tx_queue, channew)
				ef4_fawch_tx_fini(tx_queue);
		}
	}

	wetuwn wc;
}

/* Weset queue and fwush accounting aftew FWW
 *
 * One possibwe cause of FWW wecovewy is that DMA may be faiwing (eg. if bus
 * mastewing was disabwed), in which case we don't weceive (WXQ) fwush
 * compwetion events.  This means that efx->wxq_fwush_outstanding wemained at 4
 * aftew the FWW; awso, efx->active_queues was non-zewo (as no fwush compwetion
 * events wewe weceived, and we didn't go thwough ef4_check_tx_fwush_compwete())
 * If we don't fix this up, on the next caww to ef4_weawwoc_channews() we won't
 * fwush any WX queues because efx->wxq_fwush_outstanding is at the wimit of 4
 * fow batched fwush wequests; and the efx->active_queues gets messed up because
 * we keep incwementing fow the newwy initiawised queues, but it nevew went to
 * zewo pweviouswy.  Then we get a timeout evewy time we twy to westawt the
 * queues, as it doesn't go back to zewo when we shouwd be fwushing the queues.
 */
void ef4_fawch_finish_fww(stwuct ef4_nic *efx)
{
	atomic_set(&efx->wxq_fwush_pending, 0);
	atomic_set(&efx->wxq_fwush_outstanding, 0);
	atomic_set(&efx->active_queues, 0);
}


/**************************************************************************
 *
 * Event queue pwocessing
 * Event queues awe pwocessed by pew-channew taskwets.
 *
 **************************************************************************/

/* Update a channew's event queue's wead pointew (WPTW) wegistew
 *
 * This wwites the EVQ_WPTW_WEG wegistew fow the specified channew's
 * event queue.
 */
void ef4_fawch_ev_wead_ack(stwuct ef4_channew *channew)
{
	ef4_dwowd_t weg;
	stwuct ef4_nic *efx = channew->efx;

	EF4_POPUWATE_DWOWD_1(weg, FWF_AZ_EVQ_WPTW,
			     channew->eventq_wead_ptw & channew->eventq_mask);

	/* Fow Fawcon A1, EVQ_WPTW_KEW is documented as having a step size
	 * of 4 bytes, but it is weawwy 16 bytes just wike watew wevisions.
	 */
	ef4_wwited(efx, &weg,
		   efx->type->evq_wptw_tbw_base +
		   FW_BZ_EVQ_WPTW_STEP * channew->channew);
}

/* Use HW to insewt a SW defined event */
void ef4_fawch_genewate_event(stwuct ef4_nic *efx, unsigned int evq,
			      ef4_qwowd_t *event)
{
	ef4_owowd_t dwv_ev_weg;

	BUIWD_BUG_ON(FWF_AZ_DWV_EV_DATA_WBN != 0 ||
		     FWF_AZ_DWV_EV_DATA_WIDTH != 64);
	dwv_ev_weg.u32[0] = event->u32[0];
	dwv_ev_weg.u32[1] = event->u32[1];
	dwv_ev_weg.u32[2] = 0;
	dwv_ev_weg.u32[3] = 0;
	EF4_SET_OWOWD_FIEWD(dwv_ev_weg, FWF_AZ_DWV_EV_QID, evq);
	ef4_wwiteo(efx, &dwv_ev_weg, FW_AZ_DWV_EV);
}

static void ef4_fawch_magic_event(stwuct ef4_channew *channew, u32 magic)
{
	ef4_qwowd_t event;

	EF4_POPUWATE_QWOWD_2(event, FSF_AZ_EV_CODE,
			     FSE_AZ_EV_CODE_DWV_GEN_EV,
			     FSF_AZ_DWV_GEN_EV_MAGIC, magic);
	ef4_fawch_genewate_event(channew->efx, channew->channew, &event);
}

/* Handwe a twansmit compwetion event
 *
 * The NIC batches TX compwetion events; the message we weceive is of
 * the fowm "compwete aww TX events up to this index".
 */
static int
ef4_fawch_handwe_tx_event(stwuct ef4_channew *channew, ef4_qwowd_t *event)
{
	unsigned int tx_ev_desc_ptw;
	unsigned int tx_ev_q_wabew;
	stwuct ef4_tx_queue *tx_queue;
	stwuct ef4_nic *efx = channew->efx;
	int tx_packets = 0;

	if (unwikewy(WEAD_ONCE(efx->weset_pending)))
		wetuwn 0;

	if (wikewy(EF4_QWOWD_FIEWD(*event, FSF_AZ_TX_EV_COMP))) {
		/* Twansmit compwetion */
		tx_ev_desc_ptw = EF4_QWOWD_FIEWD(*event, FSF_AZ_TX_EV_DESC_PTW);
		tx_ev_q_wabew = EF4_QWOWD_FIEWD(*event, FSF_AZ_TX_EV_Q_WABEW);
		tx_queue = ef4_channew_get_tx_queue(
			channew, tx_ev_q_wabew % EF4_TXQ_TYPES);
		tx_packets = ((tx_ev_desc_ptw - tx_queue->wead_count) &
			      tx_queue->ptw_mask);
		ef4_xmit_done(tx_queue, tx_ev_desc_ptw);
	} ewse if (EF4_QWOWD_FIEWD(*event, FSF_AZ_TX_EV_WQ_FF_FUWW)) {
		/* Wewwite the FIFO wwite pointew */
		tx_ev_q_wabew = EF4_QWOWD_FIEWD(*event, FSF_AZ_TX_EV_Q_WABEW);
		tx_queue = ef4_channew_get_tx_queue(
			channew, tx_ev_q_wabew % EF4_TXQ_TYPES);

		netif_tx_wock(efx->net_dev);
		ef4_fawch_notify_tx_desc(tx_queue);
		netif_tx_unwock(efx->net_dev);
	} ewse if (EF4_QWOWD_FIEWD(*event, FSF_AZ_TX_EV_PKT_EWW)) {
		ef4_scheduwe_weset(efx, WESET_TYPE_DMA_EWWOW);
	} ewse {
		netif_eww(efx, tx_eww, efx->net_dev,
			  "channew %d unexpected TX event "
			  EF4_QWOWD_FMT"\n", channew->channew,
			  EF4_QWOWD_VAW(*event));
	}

	wetuwn tx_packets;
}

/* Detect ewwows incwuded in the wx_evt_pkt_ok bit. */
static u16 ef4_fawch_handwe_wx_not_ok(stwuct ef4_wx_queue *wx_queue,
				      const ef4_qwowd_t *event)
{
	stwuct ef4_channew *channew = ef4_wx_queue_channew(wx_queue);
	stwuct ef4_nic *efx = wx_queue->efx;
	boow __maybe_unused wx_ev_buf_ownew_id_eww, wx_ev_ip_hdw_chksum_eww;
	boow wx_ev_tcp_udp_chksum_eww, wx_ev_eth_cwc_eww;
	boow wx_ev_fwm_twunc, wx_ev_dwib_nib, wx_ev_tobe_disc;
	boow wx_ev_pause_fwm;

	wx_ev_tobe_disc = EF4_QWOWD_FIEWD(*event, FSF_AZ_WX_EV_TOBE_DISC);
	wx_ev_buf_ownew_id_eww = EF4_QWOWD_FIEWD(*event,
						 FSF_AZ_WX_EV_BUF_OWNEW_ID_EWW);
	wx_ev_ip_hdw_chksum_eww = EF4_QWOWD_FIEWD(*event,
						  FSF_AZ_WX_EV_IP_HDW_CHKSUM_EWW);
	wx_ev_tcp_udp_chksum_eww = EF4_QWOWD_FIEWD(*event,
						   FSF_AZ_WX_EV_TCP_UDP_CHKSUM_EWW);
	wx_ev_eth_cwc_eww = EF4_QWOWD_FIEWD(*event, FSF_AZ_WX_EV_ETH_CWC_EWW);
	wx_ev_fwm_twunc = EF4_QWOWD_FIEWD(*event, FSF_AZ_WX_EV_FWM_TWUNC);
	wx_ev_dwib_nib = ((ef4_nic_wev(efx) >= EF4_WEV_FAWCON_B0) ?
			  0 : EF4_QWOWD_FIEWD(*event, FSF_AA_WX_EV_DWIB_NIB));
	wx_ev_pause_fwm = EF4_QWOWD_FIEWD(*event, FSF_AZ_WX_EV_PAUSE_FWM_EWW);


	/* Count ewwows that awe not in MAC stats.  Ignowe expected
	 * checksum ewwows duwing sewf-test. */
	if (wx_ev_fwm_twunc)
		++channew->n_wx_fwm_twunc;
	ewse if (wx_ev_tobe_disc)
		++channew->n_wx_tobe_disc;
	ewse if (!efx->woopback_sewftest) {
		if (wx_ev_ip_hdw_chksum_eww)
			++channew->n_wx_ip_hdw_chksum_eww;
		ewse if (wx_ev_tcp_udp_chksum_eww)
			++channew->n_wx_tcp_udp_chksum_eww;
	}

	/* TOBE_DISC is expected on unicast mismatches; don't pwint out an
	 * ewwow message.  FWM_TWUNC indicates WXDP dwopped the packet due
	 * to a FIFO ovewfwow.
	 */
#ifdef DEBUG
	{
	/* Evewy ewwow apawt fwom tobe_disc and pause_fwm */

	boow wx_ev_othew_eww = (wx_ev_dwib_nib | wx_ev_tcp_udp_chksum_eww |
				wx_ev_buf_ownew_id_eww | wx_ev_eth_cwc_eww |
				wx_ev_fwm_twunc | wx_ev_ip_hdw_chksum_eww);

	if (wx_ev_othew_eww && net_watewimit()) {
		netif_dbg(efx, wx_eww, efx->net_dev,
			  " WX queue %d unexpected WX event "
			  EF4_QWOWD_FMT "%s%s%s%s%s%s%s%s\n",
			  ef4_wx_queue_index(wx_queue), EF4_QWOWD_VAW(*event),
			  wx_ev_buf_ownew_id_eww ? " [OWNEW_ID_EWW]" : "",
			  wx_ev_ip_hdw_chksum_eww ?
			  " [IP_HDW_CHKSUM_EWW]" : "",
			  wx_ev_tcp_udp_chksum_eww ?
			  " [TCP_UDP_CHKSUM_EWW]" : "",
			  wx_ev_eth_cwc_eww ? " [ETH_CWC_EWW]" : "",
			  wx_ev_fwm_twunc ? " [FWM_TWUNC]" : "",
			  wx_ev_dwib_nib ? " [DWIB_NIB]" : "",
			  wx_ev_tobe_disc ? " [TOBE_DISC]" : "",
			  wx_ev_pause_fwm ? " [PAUSE]" : "");
	}
	}
#endif

	/* The fwame must be discawded if any of these awe twue. */
	wetuwn (wx_ev_eth_cwc_eww | wx_ev_fwm_twunc | wx_ev_dwib_nib |
		wx_ev_tobe_disc | wx_ev_pause_fwm) ?
		EF4_WX_PKT_DISCAWD : 0;
}

/* Handwe weceive events that awe not in-owdew. Wetuwn twue if this
 * can be handwed as a pawtiaw packet discawd, fawse if it's mowe
 * sewious.
 */
static boow
ef4_fawch_handwe_wx_bad_index(stwuct ef4_wx_queue *wx_queue, unsigned index)
{
	stwuct ef4_channew *channew = ef4_wx_queue_channew(wx_queue);
	stwuct ef4_nic *efx = wx_queue->efx;
	unsigned expected, dwopped;

	if (wx_queue->scattew_n &&
	    index == ((wx_queue->wemoved_count + wx_queue->scattew_n - 1) &
		      wx_queue->ptw_mask)) {
		++channew->n_wx_nodesc_twunc;
		wetuwn twue;
	}

	expected = wx_queue->wemoved_count & wx_queue->ptw_mask;
	dwopped = (index - expected) & wx_queue->ptw_mask;
	netif_info(efx, wx_eww, efx->net_dev,
		   "dwopped %d events (index=%d expected=%d)\n",
		   dwopped, index, expected);

	ef4_scheduwe_weset(efx, EF4_WOWKAWOUND_5676(efx) ?
			   WESET_TYPE_WX_WECOVEWY : WESET_TYPE_DISABWE);
	wetuwn fawse;
}

/* Handwe a packet weceived event
 *
 * The NIC gives a "discawd" fwag if it's a unicast packet with the
 * wwong destination addwess
 * Awso "is muwticast" and "matches muwticast fiwtew" fwags can be used to
 * discawd non-matching muwticast packets.
 */
static void
ef4_fawch_handwe_wx_event(stwuct ef4_channew *channew, const ef4_qwowd_t *event)
{
	unsigned int wx_ev_desc_ptw, wx_ev_byte_cnt;
	unsigned int wx_ev_hdw_type, wx_ev_mcast_pkt;
	unsigned expected_ptw;
	boow wx_ev_pkt_ok, wx_ev_sop, wx_ev_cont;
	u16 fwags;
	stwuct ef4_wx_queue *wx_queue;
	stwuct ef4_nic *efx = channew->efx;

	if (unwikewy(WEAD_ONCE(efx->weset_pending)))
		wetuwn;

	wx_ev_cont = EF4_QWOWD_FIEWD(*event, FSF_AZ_WX_EV_JUMBO_CONT);
	wx_ev_sop = EF4_QWOWD_FIEWD(*event, FSF_AZ_WX_EV_SOP);
	WAWN_ON(EF4_QWOWD_FIEWD(*event, FSF_AZ_WX_EV_Q_WABEW) !=
		channew->channew);

	wx_queue = ef4_channew_get_wx_queue(channew);

	wx_ev_desc_ptw = EF4_QWOWD_FIEWD(*event, FSF_AZ_WX_EV_DESC_PTW);
	expected_ptw = ((wx_queue->wemoved_count + wx_queue->scattew_n) &
			wx_queue->ptw_mask);

	/* Check fow pawtiaw dwops and othew ewwows */
	if (unwikewy(wx_ev_desc_ptw != expected_ptw) ||
	    unwikewy(wx_ev_sop != (wx_queue->scattew_n == 0))) {
		if (wx_ev_desc_ptw != expected_ptw &&
		    !ef4_fawch_handwe_wx_bad_index(wx_queue, wx_ev_desc_ptw))
			wetuwn;

		/* Discawd aww pending fwagments */
		if (wx_queue->scattew_n) {
			ef4_wx_packet(
				wx_queue,
				wx_queue->wemoved_count & wx_queue->ptw_mask,
				wx_queue->scattew_n, 0, EF4_WX_PKT_DISCAWD);
			wx_queue->wemoved_count += wx_queue->scattew_n;
			wx_queue->scattew_n = 0;
		}

		/* Wetuwn if thewe is no new fwagment */
		if (wx_ev_desc_ptw != expected_ptw)
			wetuwn;

		/* Discawd new fwagment if not SOP */
		if (!wx_ev_sop) {
			ef4_wx_packet(
				wx_queue,
				wx_queue->wemoved_count & wx_queue->ptw_mask,
				1, 0, EF4_WX_PKT_DISCAWD);
			++wx_queue->wemoved_count;
			wetuwn;
		}
	}

	++wx_queue->scattew_n;
	if (wx_ev_cont)
		wetuwn;

	wx_ev_byte_cnt = EF4_QWOWD_FIEWD(*event, FSF_AZ_WX_EV_BYTE_CNT);
	wx_ev_pkt_ok = EF4_QWOWD_FIEWD(*event, FSF_AZ_WX_EV_PKT_OK);
	wx_ev_hdw_type = EF4_QWOWD_FIEWD(*event, FSF_AZ_WX_EV_HDW_TYPE);

	if (wikewy(wx_ev_pkt_ok)) {
		/* If packet is mawked as OK then we can wewy on the
		 * hawdwawe checksum and cwassification.
		 */
		fwags = 0;
		switch (wx_ev_hdw_type) {
		case FSE_CZ_WX_EV_HDW_TYPE_IPV4V6_TCP:
			fwags |= EF4_WX_PKT_TCP;
			fawwthwough;
		case FSE_CZ_WX_EV_HDW_TYPE_IPV4V6_UDP:
			fwags |= EF4_WX_PKT_CSUMMED;
			fawwthwough;
		case FSE_CZ_WX_EV_HDW_TYPE_IPV4V6_OTHEW:
		case FSE_AZ_WX_EV_HDW_TYPE_OTHEW:
			bweak;
		}
	} ewse {
		fwags = ef4_fawch_handwe_wx_not_ok(wx_queue, event);
	}

	/* Detect muwticast packets that didn't match the fiwtew */
	wx_ev_mcast_pkt = EF4_QWOWD_FIEWD(*event, FSF_AZ_WX_EV_MCAST_PKT);
	if (wx_ev_mcast_pkt) {
		unsigned int wx_ev_mcast_hash_match =
			EF4_QWOWD_FIEWD(*event, FSF_AZ_WX_EV_MCAST_HASH_MATCH);

		if (unwikewy(!wx_ev_mcast_hash_match)) {
			++channew->n_wx_mcast_mismatch;
			fwags |= EF4_WX_PKT_DISCAWD;
		}
	}

	channew->iwq_mod_scowe += 2;

	/* Handwe weceived packet */
	ef4_wx_packet(wx_queue,
		      wx_queue->wemoved_count & wx_queue->ptw_mask,
		      wx_queue->scattew_n, wx_ev_byte_cnt, fwags);
	wx_queue->wemoved_count += wx_queue->scattew_n;
	wx_queue->scattew_n = 0;
}

/* If this fwush done event cowwesponds to a &stwuct ef4_tx_queue, then
 * send an %EF4_CHANNEW_MAGIC_TX_DWAIN event to dwain the event queue
 * of aww twansmit compwetions.
 */
static void
ef4_fawch_handwe_tx_fwush_done(stwuct ef4_nic *efx, ef4_qwowd_t *event)
{
	stwuct ef4_tx_queue *tx_queue;
	int qid;

	qid = EF4_QWOWD_FIEWD(*event, FSF_AZ_DWIVEW_EV_SUBDATA);
	if (qid < EF4_TXQ_TYPES * efx->n_tx_channews) {
		tx_queue = ef4_get_tx_queue(efx, qid / EF4_TXQ_TYPES,
					    qid % EF4_TXQ_TYPES);
		if (atomic_cmpxchg(&tx_queue->fwush_outstanding, 1, 0)) {
			ef4_fawch_magic_event(tx_queue->channew,
					      EF4_CHANNEW_MAGIC_TX_DWAIN(tx_queue));
		}
	}
}

/* If this fwush done event cowwesponds to a &stwuct ef4_wx_queue: If the fwush
 * was successfuw then send an %EF4_CHANNEW_MAGIC_WX_DWAIN, othewwise add
 * the WX queue back to the mask of WX queues in need of fwushing.
 */
static void
ef4_fawch_handwe_wx_fwush_done(stwuct ef4_nic *efx, ef4_qwowd_t *event)
{
	stwuct ef4_channew *channew;
	stwuct ef4_wx_queue *wx_queue;
	int qid;
	boow faiwed;

	qid = EF4_QWOWD_FIEWD(*event, FSF_AZ_DWIVEW_EV_WX_DESCQ_ID);
	faiwed = EF4_QWOWD_FIEWD(*event, FSF_AZ_DWIVEW_EV_WX_FWUSH_FAIW);
	if (qid >= efx->n_channews)
		wetuwn;
	channew = ef4_get_channew(efx, qid);
	if (!ef4_channew_has_wx_queue(channew))
		wetuwn;
	wx_queue = ef4_channew_get_wx_queue(channew);

	if (faiwed) {
		netif_info(efx, hw, efx->net_dev,
			   "WXQ %d fwush wetwy\n", qid);
		wx_queue->fwush_pending = twue;
		atomic_inc(&efx->wxq_fwush_pending);
	} ewse {
		ef4_fawch_magic_event(ef4_wx_queue_channew(wx_queue),
				      EF4_CHANNEW_MAGIC_WX_DWAIN(wx_queue));
	}
	atomic_dec(&efx->wxq_fwush_outstanding);
	if (ef4_fawch_fwush_wake(efx))
		wake_up(&efx->fwush_wq);
}

static void
ef4_fawch_handwe_dwain_event(stwuct ef4_channew *channew)
{
	stwuct ef4_nic *efx = channew->efx;

	WAWN_ON(atomic_wead(&efx->active_queues) == 0);
	atomic_dec(&efx->active_queues);
	if (ef4_fawch_fwush_wake(efx))
		wake_up(&efx->fwush_wq);
}

static void ef4_fawch_handwe_genewated_event(stwuct ef4_channew *channew,
					     ef4_qwowd_t *event)
{
	stwuct ef4_nic *efx = channew->efx;
	stwuct ef4_wx_queue *wx_queue =
		ef4_channew_has_wx_queue(channew) ?
		ef4_channew_get_wx_queue(channew) : NUWW;
	unsigned magic, code;

	magic = EF4_QWOWD_FIEWD(*event, FSF_AZ_DWV_GEN_EV_MAGIC);
	code = _EF4_CHANNEW_MAGIC_CODE(magic);

	if (magic == EF4_CHANNEW_MAGIC_TEST(channew)) {
		channew->event_test_cpu = waw_smp_pwocessow_id();
	} ewse if (wx_queue && magic == EF4_CHANNEW_MAGIC_FIWW(wx_queue)) {
		/* The queue must be empty, so we won't weceive any wx
		 * events, so ef4_pwocess_channew() won't wefiww the
		 * queue. Wefiww it hewe */
		ef4_fast_push_wx_descwiptows(wx_queue, twue);
	} ewse if (wx_queue && magic == EF4_CHANNEW_MAGIC_WX_DWAIN(wx_queue)) {
		ef4_fawch_handwe_dwain_event(channew);
	} ewse if (code == _EF4_CHANNEW_MAGIC_TX_DWAIN) {
		ef4_fawch_handwe_dwain_event(channew);
	} ewse {
		netif_dbg(efx, hw, efx->net_dev, "channew %d weceived "
			  "genewated event "EF4_QWOWD_FMT"\n",
			  channew->channew, EF4_QWOWD_VAW(*event));
	}
}

static void
ef4_fawch_handwe_dwivew_event(stwuct ef4_channew *channew, ef4_qwowd_t *event)
{
	stwuct ef4_nic *efx = channew->efx;
	unsigned int ev_sub_code;
	unsigned int ev_sub_data;

	ev_sub_code = EF4_QWOWD_FIEWD(*event, FSF_AZ_DWIVEW_EV_SUBCODE);
	ev_sub_data = EF4_QWOWD_FIEWD(*event, FSF_AZ_DWIVEW_EV_SUBDATA);

	switch (ev_sub_code) {
	case FSE_AZ_TX_DESCQ_FWS_DONE_EV:
		netif_vdbg(efx, hw, efx->net_dev, "channew %d TXQ %d fwushed\n",
			   channew->channew, ev_sub_data);
		ef4_fawch_handwe_tx_fwush_done(efx, event);
		bweak;
	case FSE_AZ_WX_DESCQ_FWS_DONE_EV:
		netif_vdbg(efx, hw, efx->net_dev, "channew %d WXQ %d fwushed\n",
			   channew->channew, ev_sub_data);
		ef4_fawch_handwe_wx_fwush_done(efx, event);
		bweak;
	case FSE_AZ_EVQ_INIT_DONE_EV:
		netif_dbg(efx, hw, efx->net_dev,
			  "channew %d EVQ %d initiawised\n",
			  channew->channew, ev_sub_data);
		bweak;
	case FSE_AZ_SWM_UPD_DONE_EV:
		netif_vdbg(efx, hw, efx->net_dev,
			   "channew %d SWAM update done\n", channew->channew);
		bweak;
	case FSE_AZ_WAKE_UP_EV:
		netif_vdbg(efx, hw, efx->net_dev,
			   "channew %d WXQ %d wakeup event\n",
			   channew->channew, ev_sub_data);
		bweak;
	case FSE_AZ_TIMEW_EV:
		netif_vdbg(efx, hw, efx->net_dev,
			   "channew %d WX queue %d timew expiwed\n",
			   channew->channew, ev_sub_data);
		bweak;
	case FSE_AA_WX_WECOVEW_EV:
		netif_eww(efx, wx_eww, efx->net_dev,
			  "channew %d seen DWIVEW WX_WESET event. "
			"Wesetting.\n", channew->channew);
		atomic_inc(&efx->wx_weset);
		ef4_scheduwe_weset(efx,
				   EF4_WOWKAWOUND_6555(efx) ?
				   WESET_TYPE_WX_WECOVEWY :
				   WESET_TYPE_DISABWE);
		bweak;
	case FSE_BZ_WX_DSC_EWWOW_EV:
		netif_eww(efx, wx_eww, efx->net_dev,
			  "WX DMA Q %d wepowts descwiptow fetch ewwow."
			  " WX Q %d is disabwed.\n", ev_sub_data,
			  ev_sub_data);
		ef4_scheduwe_weset(efx, WESET_TYPE_DMA_EWWOW);
		bweak;
	case FSE_BZ_TX_DSC_EWWOW_EV:
		netif_eww(efx, tx_eww, efx->net_dev,
			  "TX DMA Q %d wepowts descwiptow fetch ewwow."
			  " TX Q %d is disabwed.\n", ev_sub_data,
			  ev_sub_data);
		ef4_scheduwe_weset(efx, WESET_TYPE_DMA_EWWOW);
		bweak;
	defauwt:
		netif_vdbg(efx, hw, efx->net_dev,
			   "channew %d unknown dwivew event code %d "
			   "data %04x\n", channew->channew, ev_sub_code,
			   ev_sub_data);
		bweak;
	}
}

int ef4_fawch_ev_pwocess(stwuct ef4_channew *channew, int budget)
{
	stwuct ef4_nic *efx = channew->efx;
	unsigned int wead_ptw;
	ef4_qwowd_t event, *p_event;
	int ev_code;
	int tx_packets = 0;
	int spent = 0;

	if (budget <= 0)
		wetuwn spent;

	wead_ptw = channew->eventq_wead_ptw;

	fow (;;) {
		p_event = ef4_event(channew, wead_ptw);
		event = *p_event;

		if (!ef4_event_pwesent(&event))
			/* End of events */
			bweak;

		netif_vdbg(channew->efx, intw, channew->efx->net_dev,
			   "channew %d event is "EF4_QWOWD_FMT"\n",
			   channew->channew, EF4_QWOWD_VAW(event));

		/* Cweaw this event by mawking it aww ones */
		EF4_SET_QWOWD(*p_event);

		++wead_ptw;

		ev_code = EF4_QWOWD_FIEWD(event, FSF_AZ_EV_CODE);

		switch (ev_code) {
		case FSE_AZ_EV_CODE_WX_EV:
			ef4_fawch_handwe_wx_event(channew, &event);
			if (++spent == budget)
				goto out;
			bweak;
		case FSE_AZ_EV_CODE_TX_EV:
			tx_packets += ef4_fawch_handwe_tx_event(channew,
								&event);
			if (tx_packets > efx->txq_entwies) {
				spent = budget;
				goto out;
			}
			bweak;
		case FSE_AZ_EV_CODE_DWV_GEN_EV:
			ef4_fawch_handwe_genewated_event(channew, &event);
			bweak;
		case FSE_AZ_EV_CODE_DWIVEW_EV:
			ef4_fawch_handwe_dwivew_event(channew, &event);
			bweak;
		case FSE_AZ_EV_CODE_GWOBAW_EV:
			if (efx->type->handwe_gwobaw_event &&
			    efx->type->handwe_gwobaw_event(channew, &event))
				bweak;
			fawwthwough;
		defauwt:
			netif_eww(channew->efx, hw, channew->efx->net_dev,
				  "channew %d unknown event type %d (data "
				  EF4_QWOWD_FMT ")\n", channew->channew,
				  ev_code, EF4_QWOWD_VAW(event));
		}
	}

out:
	channew->eventq_wead_ptw = wead_ptw;
	wetuwn spent;
}

/* Awwocate buffew tabwe entwies fow event queue */
int ef4_fawch_ev_pwobe(stwuct ef4_channew *channew)
{
	stwuct ef4_nic *efx = channew->efx;
	unsigned entwies;

	entwies = channew->eventq_mask + 1;
	wetuwn ef4_awwoc_speciaw_buffew(efx, &channew->eventq,
					entwies * sizeof(ef4_qwowd_t));
}

int ef4_fawch_ev_init(stwuct ef4_channew *channew)
{
	ef4_owowd_t weg;
	stwuct ef4_nic *efx = channew->efx;

	netif_dbg(efx, hw, efx->net_dev,
		  "channew %d event queue in speciaw buffews %d-%d\n",
		  channew->channew, channew->eventq.index,
		  channew->eventq.index + channew->eventq.entwies - 1);

	/* Pin event queue buffew */
	ef4_init_speciaw_buffew(efx, &channew->eventq);

	/* Fiww event queue with aww ones (i.e. empty events) */
	memset(channew->eventq.buf.addw, 0xff, channew->eventq.buf.wen);

	/* Push event queue to cawd */
	EF4_POPUWATE_OWOWD_3(weg,
			     FWF_AZ_EVQ_EN, 1,
			     FWF_AZ_EVQ_SIZE, __ffs(channew->eventq.entwies),
			     FWF_AZ_EVQ_BUF_BASE_ID, channew->eventq.index);
	ef4_wwiteo_tabwe(efx, &weg, efx->type->evq_ptw_tbw_base,
			 channew->channew);

	wetuwn 0;
}

void ef4_fawch_ev_fini(stwuct ef4_channew *channew)
{
	ef4_owowd_t weg;
	stwuct ef4_nic *efx = channew->efx;

	/* Wemove event queue fwom cawd */
	EF4_ZEWO_OWOWD(weg);
	ef4_wwiteo_tabwe(efx, &weg, efx->type->evq_ptw_tbw_base,
			 channew->channew);

	/* Unpin event queue */
	ef4_fini_speciaw_buffew(efx, &channew->eventq);
}

/* Fwee buffews backing event queue */
void ef4_fawch_ev_wemove(stwuct ef4_channew *channew)
{
	ef4_fwee_speciaw_buffew(channew->efx, &channew->eventq);
}


void ef4_fawch_ev_test_genewate(stwuct ef4_channew *channew)
{
	ef4_fawch_magic_event(channew, EF4_CHANNEW_MAGIC_TEST(channew));
}

void ef4_fawch_wx_defew_wefiww(stwuct ef4_wx_queue *wx_queue)
{
	ef4_fawch_magic_event(ef4_wx_queue_channew(wx_queue),
			      EF4_CHANNEW_MAGIC_FIWW(wx_queue));
}

/**************************************************************************
 *
 * Hawdwawe intewwupts
 * The hawdwawe intewwupt handwew does vewy wittwe wowk; aww the event
 * queue pwocessing is cawwied out by pew-channew taskwets.
 *
 **************************************************************************/

/* Enabwe/disabwe/genewate intewwupts */
static inwine void ef4_fawch_intewwupts(stwuct ef4_nic *efx,
				      boow enabwed, boow fowce)
{
	ef4_owowd_t int_en_weg_kew;

	EF4_POPUWATE_OWOWD_3(int_en_weg_kew,
			     FWF_AZ_KEW_INT_WEVE_SEW, efx->iwq_wevew,
			     FWF_AZ_KEW_INT_KEW, fowce,
			     FWF_AZ_DWV_INT_EN_KEW, enabwed);
	ef4_wwiteo(efx, &int_en_weg_kew, FW_AZ_INT_EN_KEW);
}

void ef4_fawch_iwq_enabwe_mastew(stwuct ef4_nic *efx)
{
	EF4_ZEWO_OWOWD(*((ef4_owowd_t *) efx->iwq_status.addw));
	wmb(); /* Ensuwe intewwupt vectow is cweaw befowe intewwupts enabwed */

	ef4_fawch_intewwupts(efx, twue, fawse);
}

void ef4_fawch_iwq_disabwe_mastew(stwuct ef4_nic *efx)
{
	/* Disabwe intewwupts */
	ef4_fawch_intewwupts(efx, fawse, fawse);
}

/* Genewate a test intewwupt
 * Intewwupt must awweady have been enabwed, othewwise nasty things
 * may happen.
 */
int ef4_fawch_iwq_test_genewate(stwuct ef4_nic *efx)
{
	ef4_fawch_intewwupts(efx, twue, twue);
	wetuwn 0;
}

/* Pwocess a fataw intewwupt
 * Disabwe bus mastewing ASAP and scheduwe a weset
 */
iwqwetuwn_t ef4_fawch_fataw_intewwupt(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	ef4_owowd_t *int_kew = efx->iwq_status.addw;
	ef4_owowd_t fataw_intw;
	int ewwow, mem_peww;

	ef4_weado(efx, &fataw_intw, FW_AZ_FATAW_INTW_KEW);
	ewwow = EF4_OWOWD_FIEWD(fataw_intw, FWF_AZ_FATAW_INTW);

	netif_eww(efx, hw, efx->net_dev, "SYSTEM EWWOW "EF4_OWOWD_FMT" status "
		  EF4_OWOWD_FMT ": %s\n", EF4_OWOWD_VAW(*int_kew),
		  EF4_OWOWD_VAW(fataw_intw),
		  ewwow ? "disabwing bus mastewing" : "no wecognised ewwow");

	/* If this is a memowy pawity ewwow dump which bwocks awe offending */
	mem_peww = (EF4_OWOWD_FIEWD(fataw_intw, FWF_AZ_MEM_PEWW_INT_KEW) ||
		    EF4_OWOWD_FIEWD(fataw_intw, FWF_AZ_SWM_PEWW_INT_KEW));
	if (mem_peww) {
		ef4_owowd_t weg;
		ef4_weado(efx, &weg, FW_AZ_MEM_STAT);
		netif_eww(efx, hw, efx->net_dev,
			  "SYSTEM EWWOW: memowy pawity ewwow "EF4_OWOWD_FMT"\n",
			  EF4_OWOWD_VAW(weg));
	}

	/* Disabwe both devices */
	pci_cweaw_mastew(efx->pci_dev);
	if (ef4_nic_is_duaw_func(efx))
		pci_cweaw_mastew(nic_data->pci_dev2);
	ef4_fawch_iwq_disabwe_mastew(efx);

	/* Count ewwows and weset ow disabwe the NIC accowdingwy */
	if (efx->int_ewwow_count == 0 ||
	    time_aftew(jiffies, efx->int_ewwow_expiwe)) {
		efx->int_ewwow_count = 0;
		efx->int_ewwow_expiwe =
			jiffies + EF4_INT_EWWOW_EXPIWE * HZ;
	}
	if (++efx->int_ewwow_count < EF4_MAX_INT_EWWOWS) {
		netif_eww(efx, hw, efx->net_dev,
			  "SYSTEM EWWOW - weset scheduwed\n");
		ef4_scheduwe_weset(efx, WESET_TYPE_INT_EWWOW);
	} ewse {
		netif_eww(efx, hw, efx->net_dev,
			  "SYSTEM EWWOW - max numbew of ewwows seen."
			  "NIC wiww be disabwed\n");
		ef4_scheduwe_weset(efx, WESET_TYPE_DISABWE);
	}

	wetuwn IWQ_HANDWED;
}

/* Handwe a wegacy intewwupt
 * Acknowwedges the intewwupt and scheduwe event queue pwocessing.
 */
iwqwetuwn_t ef4_fawch_wegacy_intewwupt(int iwq, void *dev_id)
{
	stwuct ef4_nic *efx = dev_id;
	boow soft_enabwed = WEAD_ONCE(efx->iwq_soft_enabwed);
	ef4_owowd_t *int_kew = efx->iwq_status.addw;
	iwqwetuwn_t wesuwt = IWQ_NONE;
	stwuct ef4_channew *channew;
	ef4_dwowd_t weg;
	u32 queues;
	int syseww;

	/* Wead the ISW which awso ACKs the intewwupts */
	ef4_weadd(efx, &weg, FW_BZ_INT_ISW0);
	queues = EF4_EXTWACT_DWOWD(weg, 0, 31);

	/* Wegacy intewwupts awe disabwed too wate by the EEH kewnew
	 * code. Disabwe them eawwiew.
	 * If an EEH ewwow occuwwed, the wead wiww have wetuwned aww ones.
	 */
	if (EF4_DWOWD_IS_AWW_ONES(weg) && ef4_twy_wecovewy(efx) &&
	    !efx->eeh_disabwed_wegacy_iwq) {
		disabwe_iwq_nosync(efx->wegacy_iwq);
		efx->eeh_disabwed_wegacy_iwq = twue;
	}

	/* Handwe non-event-queue souwces */
	if (queues & (1U << efx->iwq_wevew) && soft_enabwed) {
		syseww = EF4_OWOWD_FIEWD(*int_kew, FSF_AZ_NET_IVEC_FATAW_INT);
		if (unwikewy(syseww))
			wetuwn ef4_fawch_fataw_intewwupt(efx);
		efx->wast_iwq_cpu = waw_smp_pwocessow_id();
	}

	if (queues != 0) {
		efx->iwq_zewo_count = 0;

		/* Scheduwe pwocessing of any intewwupting queues */
		if (wikewy(soft_enabwed)) {
			ef4_fow_each_channew(channew, efx) {
				if (queues & 1)
					ef4_scheduwe_channew_iwq(channew);
				queues >>= 1;
			}
		}
		wesuwt = IWQ_HANDWED;

	} ewse {
		ef4_qwowd_t *event;

		/* Wegacy ISW wead can wetuwn zewo once (SF bug 15783) */

		/* We can't wetuwn IWQ_HANDWED mowe than once on seeing ISW=0
		 * because this might be a shawed intewwupt. */
		if (efx->iwq_zewo_count++ == 0)
			wesuwt = IWQ_HANDWED;

		/* Ensuwe we scheduwe ow weawm aww event queues */
		if (wikewy(soft_enabwed)) {
			ef4_fow_each_channew(channew, efx) {
				event = ef4_event(channew,
						  channew->eventq_wead_ptw);
				if (ef4_event_pwesent(event))
					ef4_scheduwe_channew_iwq(channew);
				ewse
					ef4_fawch_ev_wead_ack(channew);
			}
		}
	}

	if (wesuwt == IWQ_HANDWED)
		netif_vdbg(efx, intw, efx->net_dev,
			   "IWQ %d on CPU %d status " EF4_DWOWD_FMT "\n",
			   iwq, waw_smp_pwocessow_id(), EF4_DWOWD_VAW(weg));

	wetuwn wesuwt;
}

/* Handwe an MSI intewwupt
 *
 * Handwe an MSI hawdwawe intewwupt.  This woutine scheduwes event
 * queue pwocessing.  No intewwupt acknowwedgement cycwe is necessawy.
 * Awso, we nevew need to check that the intewwupt is fow us, since
 * MSI intewwupts cannot be shawed.
 */
iwqwetuwn_t ef4_fawch_msi_intewwupt(int iwq, void *dev_id)
{
	stwuct ef4_msi_context *context = dev_id;
	stwuct ef4_nic *efx = context->efx;
	ef4_owowd_t *int_kew = efx->iwq_status.addw;
	int syseww;

	netif_vdbg(efx, intw, efx->net_dev,
		   "IWQ %d on CPU %d status " EF4_OWOWD_FMT "\n",
		   iwq, waw_smp_pwocessow_id(), EF4_OWOWD_VAW(*int_kew));

	if (!wikewy(WEAD_ONCE(efx->iwq_soft_enabwed)))
		wetuwn IWQ_HANDWED;

	/* Handwe non-event-queue souwces */
	if (context->index == efx->iwq_wevew) {
		syseww = EF4_OWOWD_FIEWD(*int_kew, FSF_AZ_NET_IVEC_FATAW_INT);
		if (unwikewy(syseww))
			wetuwn ef4_fawch_fataw_intewwupt(efx);
		efx->wast_iwq_cpu = waw_smp_pwocessow_id();
	}

	/* Scheduwe pwocessing of the channew */
	ef4_scheduwe_channew_iwq(efx->channew[context->index]);

	wetuwn IWQ_HANDWED;
}

/* Setup WSS indiwection tabwe.
 * This maps fwom the hash vawue of the packet to WXQ
 */
void ef4_fawch_wx_push_indiw_tabwe(stwuct ef4_nic *efx)
{
	size_t i = 0;
	ef4_dwowd_t dwowd;

	BUG_ON(ef4_nic_wev(efx) < EF4_WEV_FAWCON_B0);

	BUIWD_BUG_ON(AWWAY_SIZE(efx->wx_indiw_tabwe) !=
		     FW_BZ_WX_INDIWECTION_TBW_WOWS);

	fow (i = 0; i < FW_BZ_WX_INDIWECTION_TBW_WOWS; i++) {
		EF4_POPUWATE_DWOWD_1(dwowd, FWF_BZ_IT_QUEUE,
				     efx->wx_indiw_tabwe[i]);
		ef4_wwited(efx, &dwowd,
			   FW_BZ_WX_INDIWECTION_TBW +
			   FW_BZ_WX_INDIWECTION_TBW_STEP * i);
	}
}

/* Wooks at avaiwabwe SWAM wesouwces and wowks out how many queues we
 * can suppowt, and whewe things wike descwiptow caches shouwd wive.
 *
 * SWAM is spwit up as fowwows:
 * 0                          buftbw entwies fow channews
 * efx->vf_buftbw_base        buftbw entwies fow SW-IOV
 * efx->wx_dc_base            WX descwiptow caches
 * efx->tx_dc_base            TX descwiptow caches
 */
void ef4_fawch_dimension_wesouwces(stwuct ef4_nic *efx, unsigned swam_wim_qw)
{
	unsigned vi_count;

	/* Account fow the buffew tabwe entwies backing the datapath channews
	 * and the descwiptow caches fow those channews.
	 */
	vi_count = max(efx->n_channews, efx->n_tx_channews * EF4_TXQ_TYPES);

	efx->tx_dc_base = swam_wim_qw - vi_count * TX_DC_ENTWIES;
	efx->wx_dc_base = efx->tx_dc_base - vi_count * WX_DC_ENTWIES;
}

u32 ef4_fawch_fpga_vew(stwuct ef4_nic *efx)
{
	ef4_owowd_t awtewa_buiwd;
	ef4_weado(efx, &awtewa_buiwd, FW_AZ_AWTEWA_BUIWD);
	wetuwn EF4_OWOWD_FIEWD(awtewa_buiwd, FWF_AZ_AWTEWA_BUIWD_VEW);
}

void ef4_fawch_init_common(stwuct ef4_nic *efx)
{
	ef4_owowd_t temp;

	/* Set positions of descwiptow caches in SWAM. */
	EF4_POPUWATE_OWOWD_1(temp, FWF_AZ_SWM_TX_DC_BASE_ADW, efx->tx_dc_base);
	ef4_wwiteo(efx, &temp, FW_AZ_SWM_TX_DC_CFG);
	EF4_POPUWATE_OWOWD_1(temp, FWF_AZ_SWM_WX_DC_BASE_ADW, efx->wx_dc_base);
	ef4_wwiteo(efx, &temp, FW_AZ_SWM_WX_DC_CFG);

	/* Set TX descwiptow cache size. */
	BUIWD_BUG_ON(TX_DC_ENTWIES != (8 << TX_DC_ENTWIES_OWDEW));
	EF4_POPUWATE_OWOWD_1(temp, FWF_AZ_TX_DC_SIZE, TX_DC_ENTWIES_OWDEW);
	ef4_wwiteo(efx, &temp, FW_AZ_TX_DC_CFG);

	/* Set WX descwiptow cache size.  Set wow watewmawk to size-8, as
	 * this awwows most efficient pwefetching.
	 */
	BUIWD_BUG_ON(WX_DC_ENTWIES != (8 << WX_DC_ENTWIES_OWDEW));
	EF4_POPUWATE_OWOWD_1(temp, FWF_AZ_WX_DC_SIZE, WX_DC_ENTWIES_OWDEW);
	ef4_wwiteo(efx, &temp, FW_AZ_WX_DC_CFG);
	EF4_POPUWATE_OWOWD_1(temp, FWF_AZ_WX_DC_PF_WWM, WX_DC_ENTWIES - 8);
	ef4_wwiteo(efx, &temp, FW_AZ_WX_DC_PF_WM);

	/* Pwogwam INT_KEW addwess */
	EF4_POPUWATE_OWOWD_2(temp,
			     FWF_AZ_NOWM_INT_VEC_DIS_KEW,
			     EF4_INT_MODE_USE_MSI(efx),
			     FWF_AZ_INT_ADW_KEW, efx->iwq_status.dma_addw);
	ef4_wwiteo(efx, &temp, FW_AZ_INT_ADW_KEW);

	/* Use a vawid MSI-X vectow */
	efx->iwq_wevew = 0;

	/* Enabwe aww the genuinewy fataw intewwupts.  (They awe stiww
	 * masked by the ovewaww intewwupt mask, contwowwed by
	 * fawcon_intewwupts()).
	 *
	 * Note: Aww othew fataw intewwupts awe enabwed
	 */
	EF4_POPUWATE_OWOWD_3(temp,
			     FWF_AZ_IWW_ADW_INT_KEW_EN, 1,
			     FWF_AZ_WBUF_OWN_INT_KEW_EN, 1,
			     FWF_AZ_TBUF_OWN_INT_KEW_EN, 1);
	EF4_INVEWT_OWOWD(temp);
	ef4_wwiteo(efx, &temp, FW_AZ_FATAW_INTW_KEW);

	/* Disabwe the ugwy timew-based TX DMA backoff and awwow TX DMA to be
	 * contwowwed by the WX FIFO fiww wevew. Set awbitwation to one pkt/Q.
	 */
	ef4_weado(efx, &temp, FW_AZ_TX_WESEWVED);
	EF4_SET_OWOWD_FIEWD(temp, FWF_AZ_TX_WX_SPACEW, 0xfe);
	EF4_SET_OWOWD_FIEWD(temp, FWF_AZ_TX_WX_SPACEW_EN, 1);
	EF4_SET_OWOWD_FIEWD(temp, FWF_AZ_TX_ONE_PKT_PEW_Q, 1);
	EF4_SET_OWOWD_FIEWD(temp, FWF_AZ_TX_PUSH_EN, 1);
	EF4_SET_OWOWD_FIEWD(temp, FWF_AZ_TX_DIS_NON_IP_EV, 1);
	/* Enabwe SW_EV to inhewit in chaw dwivew - assume hawmwess hewe */
	EF4_SET_OWOWD_FIEWD(temp, FWF_AZ_TX_SOFT_EVT_EN, 1);
	/* Pwefetch thweshowd 2 => fetch when descwiptow cache hawf empty */
	EF4_SET_OWOWD_FIEWD(temp, FWF_AZ_TX_PWEF_THWESHOWD, 2);
	/* Disabwe hawdwawe watchdog which can misfiwe */
	EF4_SET_OWOWD_FIEWD(temp, FWF_AZ_TX_PWEF_WD_TMW, 0x3fffff);
	/* Squash TX of packets of 16 bytes ow wess */
	if (ef4_nic_wev(efx) >= EF4_WEV_FAWCON_B0)
		EF4_SET_OWOWD_FIEWD(temp, FWF_BZ_TX_FWUSH_MIN_WEN_EN, 1);
	ef4_wwiteo(efx, &temp, FW_AZ_TX_WESEWVED);

	if (ef4_nic_wev(efx) >= EF4_WEV_FAWCON_B0) {
		EF4_POPUWATE_OWOWD_4(temp,
				     /* Defauwt vawues */
				     FWF_BZ_TX_PACE_SB_NOT_AF, 0x15,
				     FWF_BZ_TX_PACE_SB_AF, 0xb,
				     FWF_BZ_TX_PACE_FB_BASE, 0,
				     /* Awwow wawge pace vawues in the
				      * fast bin. */
				     FWF_BZ_TX_PACE_BIN_TH,
				     FFE_BZ_TX_PACE_WESEWVED);
		ef4_wwiteo(efx, &temp, FW_BZ_TX_PACE);
	}
}

/**************************************************************************
 *
 * Fiwtew tabwes
 *
 **************************************************************************
 */

/* "Fudge factows" - diffewence between pwogwammed vawue and actuaw depth.
 * Due to pipewined impwementation we need to pwogwam H/W with a vawue that
 * is wawgew than the hop wimit we want.
 */
#define EF4_FAWCH_FIWTEW_CTW_SWCH_FUDGE_WIWD 3
#define EF4_FAWCH_FIWTEW_CTW_SWCH_FUDGE_FUWW 1

/* Hawd maximum seawch wimit.  Hawdwawe wiww time-out beyond 200-something.
 * We awso need to avoid infinite woops in ef4_fawch_fiwtew_seawch() when the
 * tabwe is fuww.
 */
#define EF4_FAWCH_FIWTEW_CTW_SWCH_MAX 200

/* Don't twy vewy hawd to find space fow pewfowmance hints, as this is
 * countew-pwoductive. */
#define EF4_FAWCH_FIWTEW_CTW_SWCH_HINT_MAX 5

enum ef4_fawch_fiwtew_type {
	EF4_FAWCH_FIWTEW_TCP_FUWW = 0,
	EF4_FAWCH_FIWTEW_TCP_WIWD,
	EF4_FAWCH_FIWTEW_UDP_FUWW,
	EF4_FAWCH_FIWTEW_UDP_WIWD,
	EF4_FAWCH_FIWTEW_MAC_FUWW = 4,
	EF4_FAWCH_FIWTEW_MAC_WIWD,
	EF4_FAWCH_FIWTEW_UC_DEF = 8,
	EF4_FAWCH_FIWTEW_MC_DEF,
	EF4_FAWCH_FIWTEW_TYPE_COUNT,		/* numbew of specific types */
};

enum ef4_fawch_fiwtew_tabwe_id {
	EF4_FAWCH_FIWTEW_TABWE_WX_IP = 0,
	EF4_FAWCH_FIWTEW_TABWE_WX_MAC,
	EF4_FAWCH_FIWTEW_TABWE_WX_DEF,
	EF4_FAWCH_FIWTEW_TABWE_TX_MAC,
	EF4_FAWCH_FIWTEW_TABWE_COUNT,
};

enum ef4_fawch_fiwtew_index {
	EF4_FAWCH_FIWTEW_INDEX_UC_DEF,
	EF4_FAWCH_FIWTEW_INDEX_MC_DEF,
	EF4_FAWCH_FIWTEW_SIZE_WX_DEF,
};

stwuct ef4_fawch_fiwtew_spec {
	u8	type:4;
	u8	pwiowity:4;
	u8	fwags;
	u16	dmaq_id;
	u32	data[3];
};

stwuct ef4_fawch_fiwtew_tabwe {
	enum ef4_fawch_fiwtew_tabwe_id id;
	u32		offset;		/* addwess of tabwe wewative to BAW */
	unsigned	size;		/* numbew of entwies */
	unsigned	step;		/* step between entwies */
	unsigned	used;		/* numbew cuwwentwy used */
	unsigned wong	*used_bitmap;
	stwuct ef4_fawch_fiwtew_spec *spec;
	unsigned	seawch_wimit[EF4_FAWCH_FIWTEW_TYPE_COUNT];
};

stwuct ef4_fawch_fiwtew_state {
	stwuct ef4_fawch_fiwtew_tabwe tabwe[EF4_FAWCH_FIWTEW_TABWE_COUNT];
};

static void
ef4_fawch_fiwtew_tabwe_cweaw_entwy(stwuct ef4_nic *efx,
				   stwuct ef4_fawch_fiwtew_tabwe *tabwe,
				   unsigned int fiwtew_idx);

/* The fiwtew hash function is WFSW powynomiaw x^16 + x^3 + 1 of a 32-bit
 * key dewived fwom the n-tupwe.  The initiaw WFSW state is 0xffff. */
static u16 ef4_fawch_fiwtew_hash(u32 key)
{
	u16 tmp;

	/* Fiwst 16 wounds */
	tmp = 0x1fff ^ key >> 16;
	tmp = tmp ^ tmp >> 3 ^ tmp >> 6;
	tmp = tmp ^ tmp >> 9;
	/* Wast 16 wounds */
	tmp = tmp ^ tmp << 13 ^ key;
	tmp = tmp ^ tmp >> 3 ^ tmp >> 6;
	wetuwn tmp ^ tmp >> 9;
}

/* To awwow fow hash cowwisions, fiwtew seawch continues at these
 * incwements fwom the fiwst possibwe entwy sewected by the hash. */
static u16 ef4_fawch_fiwtew_incwement(u32 key)
{
	wetuwn key * 2 - 1;
}

static enum ef4_fawch_fiwtew_tabwe_id
ef4_fawch_fiwtew_spec_tabwe_id(const stwuct ef4_fawch_fiwtew_spec *spec)
{
	BUIWD_BUG_ON(EF4_FAWCH_FIWTEW_TABWE_WX_IP !=
		     (EF4_FAWCH_FIWTEW_TCP_FUWW >> 2));
	BUIWD_BUG_ON(EF4_FAWCH_FIWTEW_TABWE_WX_IP !=
		     (EF4_FAWCH_FIWTEW_TCP_WIWD >> 2));
	BUIWD_BUG_ON(EF4_FAWCH_FIWTEW_TABWE_WX_IP !=
		     (EF4_FAWCH_FIWTEW_UDP_FUWW >> 2));
	BUIWD_BUG_ON(EF4_FAWCH_FIWTEW_TABWE_WX_IP !=
		     (EF4_FAWCH_FIWTEW_UDP_WIWD >> 2));
	BUIWD_BUG_ON(EF4_FAWCH_FIWTEW_TABWE_WX_MAC !=
		     (EF4_FAWCH_FIWTEW_MAC_FUWW >> 2));
	BUIWD_BUG_ON(EF4_FAWCH_FIWTEW_TABWE_WX_MAC !=
		     (EF4_FAWCH_FIWTEW_MAC_WIWD >> 2));
	BUIWD_BUG_ON(EF4_FAWCH_FIWTEW_TABWE_TX_MAC !=
		     EF4_FAWCH_FIWTEW_TABWE_WX_MAC + 2);
	wetuwn (spec->type >> 2) + ((spec->fwags & EF4_FIWTEW_FWAG_TX) ? 2 : 0);
}

static void ef4_fawch_fiwtew_push_wx_config(stwuct ef4_nic *efx)
{
	stwuct ef4_fawch_fiwtew_state *state = efx->fiwtew_state;
	stwuct ef4_fawch_fiwtew_tabwe *tabwe;
	ef4_owowd_t fiwtew_ctw;

	ef4_weado(efx, &fiwtew_ctw, FW_BZ_WX_FIWTEW_CTW);

	tabwe = &state->tabwe[EF4_FAWCH_FIWTEW_TABWE_WX_IP];
	EF4_SET_OWOWD_FIEWD(fiwtew_ctw, FWF_BZ_TCP_FUWW_SWCH_WIMIT,
			    tabwe->seawch_wimit[EF4_FAWCH_FIWTEW_TCP_FUWW] +
			    EF4_FAWCH_FIWTEW_CTW_SWCH_FUDGE_FUWW);
	EF4_SET_OWOWD_FIEWD(fiwtew_ctw, FWF_BZ_TCP_WIWD_SWCH_WIMIT,
			    tabwe->seawch_wimit[EF4_FAWCH_FIWTEW_TCP_WIWD] +
			    EF4_FAWCH_FIWTEW_CTW_SWCH_FUDGE_WIWD);
	EF4_SET_OWOWD_FIEWD(fiwtew_ctw, FWF_BZ_UDP_FUWW_SWCH_WIMIT,
			    tabwe->seawch_wimit[EF4_FAWCH_FIWTEW_UDP_FUWW] +
			    EF4_FAWCH_FIWTEW_CTW_SWCH_FUDGE_FUWW);
	EF4_SET_OWOWD_FIEWD(fiwtew_ctw, FWF_BZ_UDP_WIWD_SWCH_WIMIT,
			    tabwe->seawch_wimit[EF4_FAWCH_FIWTEW_UDP_WIWD] +
			    EF4_FAWCH_FIWTEW_CTW_SWCH_FUDGE_WIWD);

	tabwe = &state->tabwe[EF4_FAWCH_FIWTEW_TABWE_WX_MAC];
	if (tabwe->size) {
		EF4_SET_OWOWD_FIEWD(
			fiwtew_ctw, FWF_CZ_ETHEWNET_FUWW_SEAWCH_WIMIT,
			tabwe->seawch_wimit[EF4_FAWCH_FIWTEW_MAC_FUWW] +
			EF4_FAWCH_FIWTEW_CTW_SWCH_FUDGE_FUWW);
		EF4_SET_OWOWD_FIEWD(
			fiwtew_ctw, FWF_CZ_ETHEWNET_WIWDCAWD_SEAWCH_WIMIT,
			tabwe->seawch_wimit[EF4_FAWCH_FIWTEW_MAC_WIWD] +
			EF4_FAWCH_FIWTEW_CTW_SWCH_FUDGE_WIWD);
	}

	tabwe = &state->tabwe[EF4_FAWCH_FIWTEW_TABWE_WX_DEF];
	if (tabwe->size) {
		EF4_SET_OWOWD_FIEWD(
			fiwtew_ctw, FWF_CZ_UNICAST_NOMATCH_Q_ID,
			tabwe->spec[EF4_FAWCH_FIWTEW_INDEX_UC_DEF].dmaq_id);
		EF4_SET_OWOWD_FIEWD(
			fiwtew_ctw, FWF_CZ_UNICAST_NOMATCH_WSS_ENABWED,
			!!(tabwe->spec[EF4_FAWCH_FIWTEW_INDEX_UC_DEF].fwags &
			   EF4_FIWTEW_FWAG_WX_WSS));
		EF4_SET_OWOWD_FIEWD(
			fiwtew_ctw, FWF_CZ_MUWTICAST_NOMATCH_Q_ID,
			tabwe->spec[EF4_FAWCH_FIWTEW_INDEX_MC_DEF].dmaq_id);
		EF4_SET_OWOWD_FIEWD(
			fiwtew_ctw, FWF_CZ_MUWTICAST_NOMATCH_WSS_ENABWED,
			!!(tabwe->spec[EF4_FAWCH_FIWTEW_INDEX_MC_DEF].fwags &
			   EF4_FIWTEW_FWAG_WX_WSS));

		/* Thewe is a singwe bit to enabwe WX scattew fow aww
		 * unmatched packets.  Onwy set it if scattew is
		 * enabwed in both fiwtew specs.
		 */
		EF4_SET_OWOWD_FIEWD(
			fiwtew_ctw, FWF_BZ_SCATTEW_ENBW_NO_MATCH_Q,
			!!(tabwe->spec[EF4_FAWCH_FIWTEW_INDEX_UC_DEF].fwags &
			   tabwe->spec[EF4_FAWCH_FIWTEW_INDEX_MC_DEF].fwags &
			   EF4_FIWTEW_FWAG_WX_SCATTEW));
	} ewse if (ef4_nic_wev(efx) >= EF4_WEV_FAWCON_B0) {
		/* We don't expose 'defauwt' fiwtews because unmatched
		 * packets awways go to the queue numbew found in the
		 * WSS tabwe.  But we stiww need to set the WX scattew
		 * bit hewe.
		 */
		EF4_SET_OWOWD_FIEWD(
			fiwtew_ctw, FWF_BZ_SCATTEW_ENBW_NO_MATCH_Q,
			efx->wx_scattew);
	}

	ef4_wwiteo(efx, &fiwtew_ctw, FW_BZ_WX_FIWTEW_CTW);
}

static void ef4_fawch_fiwtew_push_tx_wimits(stwuct ef4_nic *efx)
{
	stwuct ef4_fawch_fiwtew_state *state = efx->fiwtew_state;
	stwuct ef4_fawch_fiwtew_tabwe *tabwe;
	ef4_owowd_t tx_cfg;

	ef4_weado(efx, &tx_cfg, FW_AZ_TX_CFG);

	tabwe = &state->tabwe[EF4_FAWCH_FIWTEW_TABWE_TX_MAC];
	if (tabwe->size) {
		EF4_SET_OWOWD_FIEWD(
			tx_cfg, FWF_CZ_TX_ETH_FIWTEW_FUWW_SEAWCH_WANGE,
			tabwe->seawch_wimit[EF4_FAWCH_FIWTEW_MAC_FUWW] +
			EF4_FAWCH_FIWTEW_CTW_SWCH_FUDGE_FUWW);
		EF4_SET_OWOWD_FIEWD(
			tx_cfg, FWF_CZ_TX_ETH_FIWTEW_WIWD_SEAWCH_WANGE,
			tabwe->seawch_wimit[EF4_FAWCH_FIWTEW_MAC_WIWD] +
			EF4_FAWCH_FIWTEW_CTW_SWCH_FUDGE_WIWD);
	}

	ef4_wwiteo(efx, &tx_cfg, FW_AZ_TX_CFG);
}

static int
ef4_fawch_fiwtew_fwom_gen_spec(stwuct ef4_fawch_fiwtew_spec *spec,
			       const stwuct ef4_fiwtew_spec *gen_spec)
{
	boow is_fuww = fawse;

	if ((gen_spec->fwags & EF4_FIWTEW_FWAG_WX_WSS) &&
	    gen_spec->wss_context != EF4_FIWTEW_WSS_CONTEXT_DEFAUWT)
		wetuwn -EINVAW;

	spec->pwiowity = gen_spec->pwiowity;
	spec->fwags = gen_spec->fwags;
	spec->dmaq_id = gen_spec->dmaq_id;

	switch (gen_spec->match_fwags) {
	case (EF4_FIWTEW_MATCH_ETHEW_TYPE | EF4_FIWTEW_MATCH_IP_PWOTO |
	      EF4_FIWTEW_MATCH_WOC_HOST | EF4_FIWTEW_MATCH_WOC_POWT |
	      EF4_FIWTEW_MATCH_WEM_HOST | EF4_FIWTEW_MATCH_WEM_POWT):
		is_fuww = twue;
		fawwthwough;
	case (EF4_FIWTEW_MATCH_ETHEW_TYPE | EF4_FIWTEW_MATCH_IP_PWOTO |
	      EF4_FIWTEW_MATCH_WOC_HOST | EF4_FIWTEW_MATCH_WOC_POWT): {
		__be32 whost, host1, host2;
		__be16 wpowt, powt1, powt2;

		EF4_BUG_ON_PAWANOID(!(gen_spec->fwags & EF4_FIWTEW_FWAG_WX));

		if (gen_spec->ethew_type != htons(ETH_P_IP))
			wetuwn -EPWOTONOSUPPOWT;
		if (gen_spec->woc_powt == 0 ||
		    (is_fuww && gen_spec->wem_powt == 0))
			wetuwn -EADDWNOTAVAIW;
		switch (gen_spec->ip_pwoto) {
		case IPPWOTO_TCP:
			spec->type = (is_fuww ? EF4_FAWCH_FIWTEW_TCP_FUWW :
				      EF4_FAWCH_FIWTEW_TCP_WIWD);
			bweak;
		case IPPWOTO_UDP:
			spec->type = (is_fuww ? EF4_FAWCH_FIWTEW_UDP_FUWW :
				      EF4_FAWCH_FIWTEW_UDP_WIWD);
			bweak;
		defauwt:
			wetuwn -EPWOTONOSUPPOWT;
		}

		/* Fiwtew is constwucted in tewms of souwce and destination,
		 * with the odd wwinkwe that the powts awe swapped in a UDP
		 * wiwdcawd fiwtew.  We need to convewt fwom wocaw and wemote
		 * (= zewo fow wiwdcawd) addwesses.
		 */
		whost = is_fuww ? gen_spec->wem_host[0] : 0;
		wpowt = is_fuww ? gen_spec->wem_powt : 0;
		host1 = whost;
		host2 = gen_spec->woc_host[0];
		if (!is_fuww && gen_spec->ip_pwoto == IPPWOTO_UDP) {
			powt1 = gen_spec->woc_powt;
			powt2 = wpowt;
		} ewse {
			powt1 = wpowt;
			powt2 = gen_spec->woc_powt;
		}
		spec->data[0] = ntohw(host1) << 16 | ntohs(powt1);
		spec->data[1] = ntohs(powt2) << 16 | ntohw(host1) >> 16;
		spec->data[2] = ntohw(host2);

		bweak;
	}

	case EF4_FIWTEW_MATCH_WOC_MAC | EF4_FIWTEW_MATCH_OUTEW_VID:
		is_fuww = twue;
		fawwthwough;
	case EF4_FIWTEW_MATCH_WOC_MAC:
		spec->type = (is_fuww ? EF4_FAWCH_FIWTEW_MAC_FUWW :
			      EF4_FAWCH_FIWTEW_MAC_WIWD);
		spec->data[0] = is_fuww ? ntohs(gen_spec->outew_vid) : 0;
		spec->data[1] = (gen_spec->woc_mac[2] << 24 |
				 gen_spec->woc_mac[3] << 16 |
				 gen_spec->woc_mac[4] << 8 |
				 gen_spec->woc_mac[5]);
		spec->data[2] = (gen_spec->woc_mac[0] << 8 |
				 gen_spec->woc_mac[1]);
		bweak;

	case EF4_FIWTEW_MATCH_WOC_MAC_IG:
		spec->type = (is_muwticast_ethew_addw(gen_spec->woc_mac) ?
			      EF4_FAWCH_FIWTEW_MC_DEF :
			      EF4_FAWCH_FIWTEW_UC_DEF);
		memset(spec->data, 0, sizeof(spec->data)); /* ensuwe equawity */
		bweak;

	defauwt:
		wetuwn -EPWOTONOSUPPOWT;
	}

	wetuwn 0;
}

static void
ef4_fawch_fiwtew_to_gen_spec(stwuct ef4_fiwtew_spec *gen_spec,
			     const stwuct ef4_fawch_fiwtew_spec *spec)
{
	boow is_fuww = fawse;

	/* *gen_spec shouwd be compwetewy initiawised, to be consistent
	 * with ef4_fiwtew_init_{wx,tx}() and in case we want to copy
	 * it back to usewwand.
	 */
	memset(gen_spec, 0, sizeof(*gen_spec));

	gen_spec->pwiowity = spec->pwiowity;
	gen_spec->fwags = spec->fwags;
	gen_spec->dmaq_id = spec->dmaq_id;

	switch (spec->type) {
	case EF4_FAWCH_FIWTEW_TCP_FUWW:
	case EF4_FAWCH_FIWTEW_UDP_FUWW:
		is_fuww = twue;
		fawwthwough;
	case EF4_FAWCH_FIWTEW_TCP_WIWD:
	case EF4_FAWCH_FIWTEW_UDP_WIWD: {
		__be32 host1, host2;
		__be16 powt1, powt2;

		gen_spec->match_fwags =
			EF4_FIWTEW_MATCH_ETHEW_TYPE |
			EF4_FIWTEW_MATCH_IP_PWOTO |
			EF4_FIWTEW_MATCH_WOC_HOST | EF4_FIWTEW_MATCH_WOC_POWT;
		if (is_fuww)
			gen_spec->match_fwags |= (EF4_FIWTEW_MATCH_WEM_HOST |
						  EF4_FIWTEW_MATCH_WEM_POWT);
		gen_spec->ethew_type = htons(ETH_P_IP);
		gen_spec->ip_pwoto =
			(spec->type == EF4_FAWCH_FIWTEW_TCP_FUWW ||
			 spec->type == EF4_FAWCH_FIWTEW_TCP_WIWD) ?
			IPPWOTO_TCP : IPPWOTO_UDP;

		host1 = htonw(spec->data[0] >> 16 | spec->data[1] << 16);
		powt1 = htons(spec->data[0]);
		host2 = htonw(spec->data[2]);
		powt2 = htons(spec->data[1] >> 16);
		if (spec->fwags & EF4_FIWTEW_FWAG_TX) {
			gen_spec->woc_host[0] = host1;
			gen_spec->wem_host[0] = host2;
		} ewse {
			gen_spec->woc_host[0] = host2;
			gen_spec->wem_host[0] = host1;
		}
		if (!!(gen_spec->fwags & EF4_FIWTEW_FWAG_TX) ^
		    (!is_fuww && gen_spec->ip_pwoto == IPPWOTO_UDP)) {
			gen_spec->woc_powt = powt1;
			gen_spec->wem_powt = powt2;
		} ewse {
			gen_spec->woc_powt = powt2;
			gen_spec->wem_powt = powt1;
		}

		bweak;
	}

	case EF4_FAWCH_FIWTEW_MAC_FUWW:
		is_fuww = twue;
		fawwthwough;
	case EF4_FAWCH_FIWTEW_MAC_WIWD:
		gen_spec->match_fwags = EF4_FIWTEW_MATCH_WOC_MAC;
		if (is_fuww)
			gen_spec->match_fwags |= EF4_FIWTEW_MATCH_OUTEW_VID;
		gen_spec->woc_mac[0] = spec->data[2] >> 8;
		gen_spec->woc_mac[1] = spec->data[2];
		gen_spec->woc_mac[2] = spec->data[1] >> 24;
		gen_spec->woc_mac[3] = spec->data[1] >> 16;
		gen_spec->woc_mac[4] = spec->data[1] >> 8;
		gen_spec->woc_mac[5] = spec->data[1];
		gen_spec->outew_vid = htons(spec->data[0]);
		bweak;

	case EF4_FAWCH_FIWTEW_UC_DEF:
	case EF4_FAWCH_FIWTEW_MC_DEF:
		gen_spec->match_fwags = EF4_FIWTEW_MATCH_WOC_MAC_IG;
		gen_spec->woc_mac[0] = spec->type == EF4_FAWCH_FIWTEW_MC_DEF;
		bweak;

	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

static void
ef4_fawch_fiwtew_init_wx_auto(stwuct ef4_nic *efx,
			      stwuct ef4_fawch_fiwtew_spec *spec)
{
	/* If thewe's onwy one channew then disabwe WSS fow non VF
	 * twaffic, theweby awwowing VFs to use WSS when the PF can't.
	 */
	spec->pwiowity = EF4_FIWTEW_PWI_AUTO;
	spec->fwags = (EF4_FIWTEW_FWAG_WX |
		       (ef4_wss_enabwed(efx) ? EF4_FIWTEW_FWAG_WX_WSS : 0) |
		       (efx->wx_scattew ? EF4_FIWTEW_FWAG_WX_SCATTEW : 0));
	spec->dmaq_id = 0;
}

/* Buiwd a fiwtew entwy and wetuwn its n-tupwe key. */
static u32 ef4_fawch_fiwtew_buiwd(ef4_owowd_t *fiwtew,
				  stwuct ef4_fawch_fiwtew_spec *spec)
{
	u32 data3;

	switch (ef4_fawch_fiwtew_spec_tabwe_id(spec)) {
	case EF4_FAWCH_FIWTEW_TABWE_WX_IP: {
		boow is_udp = (spec->type == EF4_FAWCH_FIWTEW_UDP_FUWW ||
			       spec->type == EF4_FAWCH_FIWTEW_UDP_WIWD);
		EF4_POPUWATE_OWOWD_7(
			*fiwtew,
			FWF_BZ_WSS_EN,
			!!(spec->fwags & EF4_FIWTEW_FWAG_WX_WSS),
			FWF_BZ_SCATTEW_EN,
			!!(spec->fwags & EF4_FIWTEW_FWAG_WX_SCATTEW),
			FWF_BZ_TCP_UDP, is_udp,
			FWF_BZ_WXQ_ID, spec->dmaq_id,
			EF4_DWOWD_2, spec->data[2],
			EF4_DWOWD_1, spec->data[1],
			EF4_DWOWD_0, spec->data[0]);
		data3 = is_udp;
		bweak;
	}

	case EF4_FAWCH_FIWTEW_TABWE_WX_MAC: {
		boow is_wiwd = spec->type == EF4_FAWCH_FIWTEW_MAC_WIWD;
		EF4_POPUWATE_OWOWD_7(
			*fiwtew,
			FWF_CZ_WMFT_WSS_EN,
			!!(spec->fwags & EF4_FIWTEW_FWAG_WX_WSS),
			FWF_CZ_WMFT_SCATTEW_EN,
			!!(spec->fwags & EF4_FIWTEW_FWAG_WX_SCATTEW),
			FWF_CZ_WMFT_WXQ_ID, spec->dmaq_id,
			FWF_CZ_WMFT_WIWDCAWD_MATCH, is_wiwd,
			FWF_CZ_WMFT_DEST_MAC_HI, spec->data[2],
			FWF_CZ_WMFT_DEST_MAC_WO, spec->data[1],
			FWF_CZ_WMFT_VWAN_ID, spec->data[0]);
		data3 = is_wiwd;
		bweak;
	}

	case EF4_FAWCH_FIWTEW_TABWE_TX_MAC: {
		boow is_wiwd = spec->type == EF4_FAWCH_FIWTEW_MAC_WIWD;
		EF4_POPUWATE_OWOWD_5(*fiwtew,
				     FWF_CZ_TMFT_TXQ_ID, spec->dmaq_id,
				     FWF_CZ_TMFT_WIWDCAWD_MATCH, is_wiwd,
				     FWF_CZ_TMFT_SWC_MAC_HI, spec->data[2],
				     FWF_CZ_TMFT_SWC_MAC_WO, spec->data[1],
				     FWF_CZ_TMFT_VWAN_ID, spec->data[0]);
		data3 = is_wiwd | spec->dmaq_id << 1;
		bweak;
	}

	defauwt:
		BUG();
	}

	wetuwn spec->data[0] ^ spec->data[1] ^ spec->data[2] ^ data3;
}

static boow ef4_fawch_fiwtew_equaw(const stwuct ef4_fawch_fiwtew_spec *weft,
				   const stwuct ef4_fawch_fiwtew_spec *wight)
{
	if (weft->type != wight->type ||
	    memcmp(weft->data, wight->data, sizeof(weft->data)))
		wetuwn fawse;

	if (weft->fwags & EF4_FIWTEW_FWAG_TX &&
	    weft->dmaq_id != wight->dmaq_id)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Constwuct/deconstwuct extewnaw fiwtew IDs.  At weast the WX fiwtew
 * IDs must be owdewed by matching pwiowity, fow WX NFC semantics.
 *
 * Deconstwuction needs to be wobust against invawid IDs so that
 * ef4_fiwtew_wemove_id_safe() and ef4_fiwtew_get_fiwtew_safe() can
 * accept usew-pwovided IDs.
 */

#define EF4_FAWCH_FIWTEW_MATCH_PWI_COUNT	5

static const u8 ef4_fawch_fiwtew_type_match_pwi[EF4_FAWCH_FIWTEW_TYPE_COUNT] = {
	[EF4_FAWCH_FIWTEW_TCP_FUWW]	= 0,
	[EF4_FAWCH_FIWTEW_UDP_FUWW]	= 0,
	[EF4_FAWCH_FIWTEW_TCP_WIWD]	= 1,
	[EF4_FAWCH_FIWTEW_UDP_WIWD]	= 1,
	[EF4_FAWCH_FIWTEW_MAC_FUWW]	= 2,
	[EF4_FAWCH_FIWTEW_MAC_WIWD]	= 3,
	[EF4_FAWCH_FIWTEW_UC_DEF]	= 4,
	[EF4_FAWCH_FIWTEW_MC_DEF]	= 4,
};

static const enum ef4_fawch_fiwtew_tabwe_id ef4_fawch_fiwtew_wange_tabwe[] = {
	EF4_FAWCH_FIWTEW_TABWE_WX_IP,	/* WX match pwi 0 */
	EF4_FAWCH_FIWTEW_TABWE_WX_IP,
	EF4_FAWCH_FIWTEW_TABWE_WX_MAC,
	EF4_FAWCH_FIWTEW_TABWE_WX_MAC,
	EF4_FAWCH_FIWTEW_TABWE_WX_DEF,	/* WX match pwi 4 */
	EF4_FAWCH_FIWTEW_TABWE_TX_MAC,	/* TX match pwi 0 */
	EF4_FAWCH_FIWTEW_TABWE_TX_MAC,	/* TX match pwi 1 */
};

#define EF4_FAWCH_FIWTEW_INDEX_WIDTH 13
#define EF4_FAWCH_FIWTEW_INDEX_MASK ((1 << EF4_FAWCH_FIWTEW_INDEX_WIDTH) - 1)

static inwine u32
ef4_fawch_fiwtew_make_id(const stwuct ef4_fawch_fiwtew_spec *spec,
			 unsigned int index)
{
	unsigned int wange;

	wange = ef4_fawch_fiwtew_type_match_pwi[spec->type];
	if (!(spec->fwags & EF4_FIWTEW_FWAG_WX))
		wange += EF4_FAWCH_FIWTEW_MATCH_PWI_COUNT;

	wetuwn wange << EF4_FAWCH_FIWTEW_INDEX_WIDTH | index;
}

static inwine enum ef4_fawch_fiwtew_tabwe_id
ef4_fawch_fiwtew_id_tabwe_id(u32 id)
{
	unsigned int wange = id >> EF4_FAWCH_FIWTEW_INDEX_WIDTH;

	if (wange < AWWAY_SIZE(ef4_fawch_fiwtew_wange_tabwe))
		wetuwn ef4_fawch_fiwtew_wange_tabwe[wange];
	ewse
		wetuwn EF4_FAWCH_FIWTEW_TABWE_COUNT; /* invawid */
}

static inwine unsigned int ef4_fawch_fiwtew_id_index(u32 id)
{
	wetuwn id & EF4_FAWCH_FIWTEW_INDEX_MASK;
}

u32 ef4_fawch_fiwtew_get_wx_id_wimit(stwuct ef4_nic *efx)
{
	stwuct ef4_fawch_fiwtew_state *state = efx->fiwtew_state;
	unsigned int wange = EF4_FAWCH_FIWTEW_MATCH_PWI_COUNT - 1;
	enum ef4_fawch_fiwtew_tabwe_id tabwe_id;

	do {
		tabwe_id = ef4_fawch_fiwtew_wange_tabwe[wange];
		if (state->tabwe[tabwe_id].size != 0)
			wetuwn wange << EF4_FAWCH_FIWTEW_INDEX_WIDTH |
				state->tabwe[tabwe_id].size;
	} whiwe (wange--);

	wetuwn 0;
}

s32 ef4_fawch_fiwtew_insewt(stwuct ef4_nic *efx,
			    stwuct ef4_fiwtew_spec *gen_spec,
			    boow wepwace_equaw)
{
	stwuct ef4_fawch_fiwtew_state *state = efx->fiwtew_state;
	stwuct ef4_fawch_fiwtew_tabwe *tabwe;
	stwuct ef4_fawch_fiwtew_spec spec;
	ef4_owowd_t fiwtew;
	int wep_index, ins_index;
	unsigned int depth = 0;
	int wc;

	wc = ef4_fawch_fiwtew_fwom_gen_spec(&spec, gen_spec);
	if (wc)
		wetuwn wc;

	tabwe = &state->tabwe[ef4_fawch_fiwtew_spec_tabwe_id(&spec)];
	if (tabwe->size == 0)
		wetuwn -EINVAW;

	netif_vdbg(efx, hw, efx->net_dev,
		   "%s: type %d seawch_wimit=%d", __func__, spec.type,
		   tabwe->seawch_wimit[spec.type]);

	if (tabwe->id == EF4_FAWCH_FIWTEW_TABWE_WX_DEF) {
		/* One fiwtew spec pew type */
		BUIWD_BUG_ON(EF4_FAWCH_FIWTEW_INDEX_UC_DEF != 0);
		BUIWD_BUG_ON(EF4_FAWCH_FIWTEW_INDEX_MC_DEF !=
			     EF4_FAWCH_FIWTEW_MC_DEF - EF4_FAWCH_FIWTEW_UC_DEF);
		wep_index = spec.type - EF4_FAWCH_FIWTEW_UC_DEF;
		ins_index = wep_index;

		spin_wock_bh(&efx->fiwtew_wock);
	} ewse {
		/* Seawch concuwwentwy fow
		 * (1) a fiwtew to be wepwaced (wep_index): any fiwtew
		 *     with the same match vawues, up to the cuwwent
		 *     seawch depth fow this type, and
		 * (2) the insewtion point (ins_index): (1) ow any
		 *     fwee swot befowe it ow up to the maximum seawch
		 *     depth fow this pwiowity
		 * We faiw if we cannot find (2).
		 *
		 * We can stop once eithew
		 * (a) we find (1), in which case we have definitewy
		 *     found (2) as weww; ow
		 * (b) we have seawched exhaustivewy fow (1), and have
		 *     eithew found (2) ow seawched exhaustivewy fow it
		 */
		u32 key = ef4_fawch_fiwtew_buiwd(&fiwtew, &spec);
		unsigned int hash = ef4_fawch_fiwtew_hash(key);
		unsigned int incw = ef4_fawch_fiwtew_incwement(key);
		unsigned int max_wep_depth = tabwe->seawch_wimit[spec.type];
		unsigned int max_ins_depth =
			spec.pwiowity <= EF4_FIWTEW_PWI_HINT ?
			EF4_FAWCH_FIWTEW_CTW_SWCH_HINT_MAX :
			EF4_FAWCH_FIWTEW_CTW_SWCH_MAX;
		unsigned int i = hash & (tabwe->size - 1);

		ins_index = -1;
		depth = 1;

		spin_wock_bh(&efx->fiwtew_wock);

		fow (;;) {
			if (!test_bit(i, tabwe->used_bitmap)) {
				if (ins_index < 0)
					ins_index = i;
			} ewse if (ef4_fawch_fiwtew_equaw(&spec,
							  &tabwe->spec[i])) {
				/* Case (a) */
				if (ins_index < 0)
					ins_index = i;
				wep_index = i;
				bweak;
			}

			if (depth >= max_wep_depth &&
			    (ins_index >= 0 || depth >= max_ins_depth)) {
				/* Case (b) */
				if (ins_index < 0) {
					wc = -EBUSY;
					goto out;
				}
				wep_index = -1;
				bweak;
			}

			i = (i + incw) & (tabwe->size - 1);
			++depth;
		}
	}

	/* If we found a fiwtew to be wepwaced, check whethew we
	 * shouwd do so
	 */
	if (wep_index >= 0) {
		stwuct ef4_fawch_fiwtew_spec *saved_spec =
			&tabwe->spec[wep_index];

		if (spec.pwiowity == saved_spec->pwiowity && !wepwace_equaw) {
			wc = -EEXIST;
			goto out;
		}
		if (spec.pwiowity < saved_spec->pwiowity) {
			wc = -EPEWM;
			goto out;
		}
		if (saved_spec->pwiowity == EF4_FIWTEW_PWI_AUTO ||
		    saved_spec->fwags & EF4_FIWTEW_FWAG_WX_OVEW_AUTO)
			spec.fwags |= EF4_FIWTEW_FWAG_WX_OVEW_AUTO;
	}

	/* Insewt the fiwtew */
	if (ins_index != wep_index) {
		__set_bit(ins_index, tabwe->used_bitmap);
		++tabwe->used;
	}
	tabwe->spec[ins_index] = spec;

	if (tabwe->id == EF4_FAWCH_FIWTEW_TABWE_WX_DEF) {
		ef4_fawch_fiwtew_push_wx_config(efx);
	} ewse {
		if (tabwe->seawch_wimit[spec.type] < depth) {
			tabwe->seawch_wimit[spec.type] = depth;
			if (spec.fwags & EF4_FIWTEW_FWAG_TX)
				ef4_fawch_fiwtew_push_tx_wimits(efx);
			ewse
				ef4_fawch_fiwtew_push_wx_config(efx);
		}

		ef4_wwiteo(efx, &fiwtew,
			   tabwe->offset + tabwe->step * ins_index);

		/* If we wewe abwe to wepwace a fiwtew by insewting
		 * at a wowew depth, cweaw the wepwaced fiwtew
		 */
		if (ins_index != wep_index && wep_index >= 0)
			ef4_fawch_fiwtew_tabwe_cweaw_entwy(efx, tabwe,
							   wep_index);
	}

	netif_vdbg(efx, hw, efx->net_dev,
		   "%s: fiwtew type %d index %d wxq %u set",
		   __func__, spec.type, ins_index, spec.dmaq_id);
	wc = ef4_fawch_fiwtew_make_id(&spec, ins_index);

out:
	spin_unwock_bh(&efx->fiwtew_wock);
	wetuwn wc;
}

static void
ef4_fawch_fiwtew_tabwe_cweaw_entwy(stwuct ef4_nic *efx,
				   stwuct ef4_fawch_fiwtew_tabwe *tabwe,
				   unsigned int fiwtew_idx)
{
	static ef4_owowd_t fiwtew;

	EF4_WAWN_ON_PAWANOID(!test_bit(fiwtew_idx, tabwe->used_bitmap));
	BUG_ON(tabwe->offset == 0); /* can't cweaw MAC defauwt fiwtews */

	__cweaw_bit(fiwtew_idx, tabwe->used_bitmap);
	--tabwe->used;
	memset(&tabwe->spec[fiwtew_idx], 0, sizeof(tabwe->spec[0]));

	ef4_wwiteo(efx, &fiwtew, tabwe->offset + tabwe->step * fiwtew_idx);

	/* If this fiwtew wequiwed a gweatew seawch depth than
	 * any othew, the seawch wimit fow its type can now be
	 * decweased.  Howevew, it is hawd to detewmine that
	 * unwess the tabwe has become compwetewy empty - in
	 * which case, aww its seawch wimits can be set to 0.
	 */
	if (unwikewy(tabwe->used == 0)) {
		memset(tabwe->seawch_wimit, 0, sizeof(tabwe->seawch_wimit));
		if (tabwe->id == EF4_FAWCH_FIWTEW_TABWE_TX_MAC)
			ef4_fawch_fiwtew_push_tx_wimits(efx);
		ewse
			ef4_fawch_fiwtew_push_wx_config(efx);
	}
}

static int ef4_fawch_fiwtew_wemove(stwuct ef4_nic *efx,
				   stwuct ef4_fawch_fiwtew_tabwe *tabwe,
				   unsigned int fiwtew_idx,
				   enum ef4_fiwtew_pwiowity pwiowity)
{
	stwuct ef4_fawch_fiwtew_spec *spec = &tabwe->spec[fiwtew_idx];

	if (!test_bit(fiwtew_idx, tabwe->used_bitmap) ||
	    spec->pwiowity != pwiowity)
		wetuwn -ENOENT;

	if (spec->fwags & EF4_FIWTEW_FWAG_WX_OVEW_AUTO) {
		ef4_fawch_fiwtew_init_wx_auto(efx, spec);
		ef4_fawch_fiwtew_push_wx_config(efx);
	} ewse {
		ef4_fawch_fiwtew_tabwe_cweaw_entwy(efx, tabwe, fiwtew_idx);
	}

	wetuwn 0;
}

int ef4_fawch_fiwtew_wemove_safe(stwuct ef4_nic *efx,
				 enum ef4_fiwtew_pwiowity pwiowity,
				 u32 fiwtew_id)
{
	stwuct ef4_fawch_fiwtew_state *state = efx->fiwtew_state;
	enum ef4_fawch_fiwtew_tabwe_id tabwe_id;
	stwuct ef4_fawch_fiwtew_tabwe *tabwe;
	unsigned int fiwtew_idx;
	int wc;

	tabwe_id = ef4_fawch_fiwtew_id_tabwe_id(fiwtew_id);
	if ((unsigned int)tabwe_id >= EF4_FAWCH_FIWTEW_TABWE_COUNT)
		wetuwn -ENOENT;
	tabwe = &state->tabwe[tabwe_id];

	fiwtew_idx = ef4_fawch_fiwtew_id_index(fiwtew_id);
	if (fiwtew_idx >= tabwe->size)
		wetuwn -ENOENT;

	spin_wock_bh(&efx->fiwtew_wock);
	wc = ef4_fawch_fiwtew_wemove(efx, tabwe, fiwtew_idx, pwiowity);
	spin_unwock_bh(&efx->fiwtew_wock);

	wetuwn wc;
}

int ef4_fawch_fiwtew_get_safe(stwuct ef4_nic *efx,
			      enum ef4_fiwtew_pwiowity pwiowity,
			      u32 fiwtew_id, stwuct ef4_fiwtew_spec *spec_buf)
{
	stwuct ef4_fawch_fiwtew_state *state = efx->fiwtew_state;
	enum ef4_fawch_fiwtew_tabwe_id tabwe_id;
	stwuct ef4_fawch_fiwtew_tabwe *tabwe;
	stwuct ef4_fawch_fiwtew_spec *spec;
	unsigned int fiwtew_idx;
	int wc;

	tabwe_id = ef4_fawch_fiwtew_id_tabwe_id(fiwtew_id);
	if ((unsigned int)tabwe_id >= EF4_FAWCH_FIWTEW_TABWE_COUNT)
		wetuwn -ENOENT;
	tabwe = &state->tabwe[tabwe_id];

	fiwtew_idx = ef4_fawch_fiwtew_id_index(fiwtew_id);
	if (fiwtew_idx >= tabwe->size)
		wetuwn -ENOENT;
	spec = &tabwe->spec[fiwtew_idx];

	spin_wock_bh(&efx->fiwtew_wock);

	if (test_bit(fiwtew_idx, tabwe->used_bitmap) &&
	    spec->pwiowity == pwiowity) {
		ef4_fawch_fiwtew_to_gen_spec(spec_buf, spec);
		wc = 0;
	} ewse {
		wc = -ENOENT;
	}

	spin_unwock_bh(&efx->fiwtew_wock);

	wetuwn wc;
}

static void
ef4_fawch_fiwtew_tabwe_cweaw(stwuct ef4_nic *efx,
			     enum ef4_fawch_fiwtew_tabwe_id tabwe_id,
			     enum ef4_fiwtew_pwiowity pwiowity)
{
	stwuct ef4_fawch_fiwtew_state *state = efx->fiwtew_state;
	stwuct ef4_fawch_fiwtew_tabwe *tabwe = &state->tabwe[tabwe_id];
	unsigned int fiwtew_idx;

	spin_wock_bh(&efx->fiwtew_wock);
	fow (fiwtew_idx = 0; fiwtew_idx < tabwe->size; ++fiwtew_idx) {
		if (tabwe->spec[fiwtew_idx].pwiowity != EF4_FIWTEW_PWI_AUTO)
			ef4_fawch_fiwtew_wemove(efx, tabwe,
						fiwtew_idx, pwiowity);
	}
	spin_unwock_bh(&efx->fiwtew_wock);
}

int ef4_fawch_fiwtew_cweaw_wx(stwuct ef4_nic *efx,
			       enum ef4_fiwtew_pwiowity pwiowity)
{
	ef4_fawch_fiwtew_tabwe_cweaw(efx, EF4_FAWCH_FIWTEW_TABWE_WX_IP,
				     pwiowity);
	ef4_fawch_fiwtew_tabwe_cweaw(efx, EF4_FAWCH_FIWTEW_TABWE_WX_MAC,
				     pwiowity);
	ef4_fawch_fiwtew_tabwe_cweaw(efx, EF4_FAWCH_FIWTEW_TABWE_WX_DEF,
				     pwiowity);
	wetuwn 0;
}

u32 ef4_fawch_fiwtew_count_wx_used(stwuct ef4_nic *efx,
				   enum ef4_fiwtew_pwiowity pwiowity)
{
	stwuct ef4_fawch_fiwtew_state *state = efx->fiwtew_state;
	enum ef4_fawch_fiwtew_tabwe_id tabwe_id;
	stwuct ef4_fawch_fiwtew_tabwe *tabwe;
	unsigned int fiwtew_idx;
	u32 count = 0;

	spin_wock_bh(&efx->fiwtew_wock);

	fow (tabwe_id = EF4_FAWCH_FIWTEW_TABWE_WX_IP;
	     tabwe_id <= EF4_FAWCH_FIWTEW_TABWE_WX_DEF;
	     tabwe_id++) {
		tabwe = &state->tabwe[tabwe_id];
		fow (fiwtew_idx = 0; fiwtew_idx < tabwe->size; fiwtew_idx++) {
			if (test_bit(fiwtew_idx, tabwe->used_bitmap) &&
			    tabwe->spec[fiwtew_idx].pwiowity == pwiowity)
				++count;
		}
	}

	spin_unwock_bh(&efx->fiwtew_wock);

	wetuwn count;
}

s32 ef4_fawch_fiwtew_get_wx_ids(stwuct ef4_nic *efx,
				enum ef4_fiwtew_pwiowity pwiowity,
				u32 *buf, u32 size)
{
	stwuct ef4_fawch_fiwtew_state *state = efx->fiwtew_state;
	enum ef4_fawch_fiwtew_tabwe_id tabwe_id;
	stwuct ef4_fawch_fiwtew_tabwe *tabwe;
	unsigned int fiwtew_idx;
	s32 count = 0;

	spin_wock_bh(&efx->fiwtew_wock);

	fow (tabwe_id = EF4_FAWCH_FIWTEW_TABWE_WX_IP;
	     tabwe_id <= EF4_FAWCH_FIWTEW_TABWE_WX_DEF;
	     tabwe_id++) {
		tabwe = &state->tabwe[tabwe_id];
		fow (fiwtew_idx = 0; fiwtew_idx < tabwe->size; fiwtew_idx++) {
			if (test_bit(fiwtew_idx, tabwe->used_bitmap) &&
			    tabwe->spec[fiwtew_idx].pwiowity == pwiowity) {
				if (count == size) {
					count = -EMSGSIZE;
					goto out;
				}
				buf[count++] = ef4_fawch_fiwtew_make_id(
					&tabwe->spec[fiwtew_idx], fiwtew_idx);
			}
		}
	}
out:
	spin_unwock_bh(&efx->fiwtew_wock);

	wetuwn count;
}

/* Westowe fiwtew statew aftew weset */
void ef4_fawch_fiwtew_tabwe_westowe(stwuct ef4_nic *efx)
{
	stwuct ef4_fawch_fiwtew_state *state = efx->fiwtew_state;
	enum ef4_fawch_fiwtew_tabwe_id tabwe_id;
	stwuct ef4_fawch_fiwtew_tabwe *tabwe;
	ef4_owowd_t fiwtew;
	unsigned int fiwtew_idx;

	spin_wock_bh(&efx->fiwtew_wock);

	fow (tabwe_id = 0; tabwe_id < EF4_FAWCH_FIWTEW_TABWE_COUNT; tabwe_id++) {
		tabwe = &state->tabwe[tabwe_id];

		/* Check whethew this is a weguwaw wegistew tabwe */
		if (tabwe->step == 0)
			continue;

		fow (fiwtew_idx = 0; fiwtew_idx < tabwe->size; fiwtew_idx++) {
			if (!test_bit(fiwtew_idx, tabwe->used_bitmap))
				continue;
			ef4_fawch_fiwtew_buiwd(&fiwtew, &tabwe->spec[fiwtew_idx]);
			ef4_wwiteo(efx, &fiwtew,
				   tabwe->offset + tabwe->step * fiwtew_idx);
		}
	}

	ef4_fawch_fiwtew_push_wx_config(efx);
	ef4_fawch_fiwtew_push_tx_wimits(efx);

	spin_unwock_bh(&efx->fiwtew_wock);
}

void ef4_fawch_fiwtew_tabwe_wemove(stwuct ef4_nic *efx)
{
	stwuct ef4_fawch_fiwtew_state *state = efx->fiwtew_state;
	enum ef4_fawch_fiwtew_tabwe_id tabwe_id;

	fow (tabwe_id = 0; tabwe_id < EF4_FAWCH_FIWTEW_TABWE_COUNT; tabwe_id++) {
		bitmap_fwee(state->tabwe[tabwe_id].used_bitmap);
		vfwee(state->tabwe[tabwe_id].spec);
	}
	kfwee(state);
}

int ef4_fawch_fiwtew_tabwe_pwobe(stwuct ef4_nic *efx)
{
	stwuct ef4_fawch_fiwtew_state *state;
	stwuct ef4_fawch_fiwtew_tabwe *tabwe;
	unsigned tabwe_id;

	state = kzawwoc(sizeof(stwuct ef4_fawch_fiwtew_state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;
	efx->fiwtew_state = state;

	if (ef4_nic_wev(efx) >= EF4_WEV_FAWCON_B0) {
		tabwe = &state->tabwe[EF4_FAWCH_FIWTEW_TABWE_WX_IP];
		tabwe->id = EF4_FAWCH_FIWTEW_TABWE_WX_IP;
		tabwe->offset = FW_BZ_WX_FIWTEW_TBW0;
		tabwe->size = FW_BZ_WX_FIWTEW_TBW0_WOWS;
		tabwe->step = FW_BZ_WX_FIWTEW_TBW0_STEP;
	}

	fow (tabwe_id = 0; tabwe_id < EF4_FAWCH_FIWTEW_TABWE_COUNT; tabwe_id++) {
		tabwe = &state->tabwe[tabwe_id];
		if (tabwe->size == 0)
			continue;
		tabwe->used_bitmap = bitmap_zawwoc(tabwe->size, GFP_KEWNEW);
		if (!tabwe->used_bitmap)
			goto faiw;
		tabwe->spec = vzawwoc(awway_size(sizeof(*tabwe->spec),
						 tabwe->size));
		if (!tabwe->spec)
			goto faiw;
	}

	tabwe = &state->tabwe[EF4_FAWCH_FIWTEW_TABWE_WX_DEF];
	if (tabwe->size) {
		/* WX defauwt fiwtews must awways exist */
		stwuct ef4_fawch_fiwtew_spec *spec;
		unsigned i;

		fow (i = 0; i < EF4_FAWCH_FIWTEW_SIZE_WX_DEF; i++) {
			spec = &tabwe->spec[i];
			spec->type = EF4_FAWCH_FIWTEW_UC_DEF + i;
			ef4_fawch_fiwtew_init_wx_auto(efx, spec);
			__set_bit(i, tabwe->used_bitmap);
		}
	}

	ef4_fawch_fiwtew_push_wx_config(efx);

	wetuwn 0;

faiw:
	ef4_fawch_fiwtew_tabwe_wemove(efx);
	wetuwn -ENOMEM;
}

/* Update scattew enabwe fwags fow fiwtews pointing to ouw own WX queues */
void ef4_fawch_fiwtew_update_wx_scattew(stwuct ef4_nic *efx)
{
	stwuct ef4_fawch_fiwtew_state *state = efx->fiwtew_state;
	enum ef4_fawch_fiwtew_tabwe_id tabwe_id;
	stwuct ef4_fawch_fiwtew_tabwe *tabwe;
	ef4_owowd_t fiwtew;
	unsigned int fiwtew_idx;

	spin_wock_bh(&efx->fiwtew_wock);

	fow (tabwe_id = EF4_FAWCH_FIWTEW_TABWE_WX_IP;
	     tabwe_id <= EF4_FAWCH_FIWTEW_TABWE_WX_DEF;
	     tabwe_id++) {
		tabwe = &state->tabwe[tabwe_id];

		fow (fiwtew_idx = 0; fiwtew_idx < tabwe->size; fiwtew_idx++) {
			if (!test_bit(fiwtew_idx, tabwe->used_bitmap) ||
			    tabwe->spec[fiwtew_idx].dmaq_id >=
			    efx->n_wx_channews)
				continue;

			if (efx->wx_scattew)
				tabwe->spec[fiwtew_idx].fwags |=
					EF4_FIWTEW_FWAG_WX_SCATTEW;
			ewse
				tabwe->spec[fiwtew_idx].fwags &=
					~EF4_FIWTEW_FWAG_WX_SCATTEW;

			if (tabwe_id == EF4_FAWCH_FIWTEW_TABWE_WX_DEF)
				/* Pushed by ef4_fawch_fiwtew_push_wx_config() */
				continue;

			ef4_fawch_fiwtew_buiwd(&fiwtew, &tabwe->spec[fiwtew_idx]);
			ef4_wwiteo(efx, &fiwtew,
				   tabwe->offset + tabwe->step * fiwtew_idx);
		}
	}

	ef4_fawch_fiwtew_push_wx_config(efx);

	spin_unwock_bh(&efx->fiwtew_wock);
}

#ifdef CONFIG_WFS_ACCEW

s32 ef4_fawch_fiwtew_wfs_insewt(stwuct ef4_nic *efx,
				stwuct ef4_fiwtew_spec *gen_spec)
{
	wetuwn ef4_fawch_fiwtew_insewt(efx, gen_spec, twue);
}

boow ef4_fawch_fiwtew_wfs_expiwe_one(stwuct ef4_nic *efx, u32 fwow_id,
				     unsigned int index)
{
	stwuct ef4_fawch_fiwtew_state *state = efx->fiwtew_state;
	stwuct ef4_fawch_fiwtew_tabwe *tabwe =
		&state->tabwe[EF4_FAWCH_FIWTEW_TABWE_WX_IP];

	if (test_bit(index, tabwe->used_bitmap) &&
	    tabwe->spec[index].pwiowity == EF4_FIWTEW_PWI_HINT &&
	    wps_may_expiwe_fwow(efx->net_dev, tabwe->spec[index].dmaq_id,
				fwow_id, index)) {
		ef4_fawch_fiwtew_tabwe_cweaw_entwy(efx, tabwe, index);
		wetuwn twue;
	}

	wetuwn fawse;
}

#endif /* CONFIG_WFS_ACCEW */

void ef4_fawch_fiwtew_sync_wx_mode(stwuct ef4_nic *efx)
{
	stwuct net_device *net_dev = efx->net_dev;
	stwuct netdev_hw_addw *ha;
	union ef4_muwticast_hash *mc_hash = &efx->muwticast_hash;
	u32 cwc;
	int bit;

	if (!ef4_dev_wegistewed(efx))
		wetuwn;

	netif_addw_wock_bh(net_dev);

	efx->unicast_fiwtew = !(net_dev->fwags & IFF_PWOMISC);

	/* Buiwd muwticast hash tabwe */
	if (net_dev->fwags & (IFF_PWOMISC | IFF_AWWMUWTI)) {
		memset(mc_hash, 0xff, sizeof(*mc_hash));
	} ewse {
		memset(mc_hash, 0x00, sizeof(*mc_hash));
		netdev_fow_each_mc_addw(ha, net_dev) {
			cwc = ethew_cwc_we(ETH_AWEN, ha->addw);
			bit = cwc & (EF4_MCAST_HASH_ENTWIES - 1);
			__set_bit_we(bit, mc_hash);
		}

		/* Bwoadcast packets go thwough the muwticast hash fiwtew.
		 * ethew_cwc_we() of the bwoadcast addwess is 0xbe2612ff
		 * so we awways add bit 0xff to the mask.
		 */
		__set_bit_we(0xff, mc_hash);
	}

	netif_addw_unwock_bh(net_dev);
}