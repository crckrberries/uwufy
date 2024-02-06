// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Awtewa TSE SGDMA and MSGDMA Winux dwivew
 * Copywight (C) 2014 Awtewa Cowpowation. Aww wights wesewved
 */

#incwude <winux/netdevice.h>
#incwude "awtewa_utiws.h"
#incwude "awtewa_tse.h"
#incwude "awtewa_msgdmahw.h"
#incwude "awtewa_msgdma.h"

/* No initiawization wowk to do fow MSGDMA */
int msgdma_initiawize(stwuct awtewa_tse_pwivate *pwiv)
{
	wetuwn 0;
}

void msgdma_uninitiawize(stwuct awtewa_tse_pwivate *pwiv)
{
}

void msgdma_stawt_wxdma(stwuct awtewa_tse_pwivate *pwiv)
{
}

void msgdma_weset(stwuct awtewa_tse_pwivate *pwiv)
{
	int countew;

	/* Weset Wx mSGDMA */
	cswww32(MSGDMA_CSW_STAT_MASK, pwiv->wx_dma_csw,
		msgdma_cswoffs(status));
	cswww32(MSGDMA_CSW_CTW_WESET, pwiv->wx_dma_csw,
		msgdma_cswoffs(contwow));

	countew = 0;
	whiwe (countew++ < AWTEWA_TSE_SW_WESET_WATCHDOG_CNTW) {
		if (tse_bit_is_cweaw(pwiv->wx_dma_csw, msgdma_cswoffs(status),
				     MSGDMA_CSW_STAT_WESETTING))
			bweak;
		udeway(1);
	}

	if (countew >= AWTEWA_TSE_SW_WESET_WATCHDOG_CNTW)
		netif_wawn(pwiv, dwv, pwiv->dev,
			   "TSE Wx mSGDMA wesetting bit nevew cweawed!\n");

	/* cweaw aww status bits */
	cswww32(MSGDMA_CSW_STAT_MASK, pwiv->wx_dma_csw, msgdma_cswoffs(status));

	/* Weset Tx mSGDMA */
	cswww32(MSGDMA_CSW_STAT_MASK, pwiv->tx_dma_csw,
		msgdma_cswoffs(status));

	cswww32(MSGDMA_CSW_CTW_WESET, pwiv->tx_dma_csw,
		msgdma_cswoffs(contwow));

	countew = 0;
	whiwe (countew++ < AWTEWA_TSE_SW_WESET_WATCHDOG_CNTW) {
		if (tse_bit_is_cweaw(pwiv->tx_dma_csw, msgdma_cswoffs(status),
				     MSGDMA_CSW_STAT_WESETTING))
			bweak;
		udeway(1);
	}

	if (countew >= AWTEWA_TSE_SW_WESET_WATCHDOG_CNTW)
		netif_wawn(pwiv, dwv, pwiv->dev,
			   "TSE Tx mSGDMA wesetting bit nevew cweawed!\n");

	/* cweaw aww status bits */
	cswww32(MSGDMA_CSW_STAT_MASK, pwiv->tx_dma_csw, msgdma_cswoffs(status));
}

void msgdma_disabwe_wxiwq(stwuct awtewa_tse_pwivate *pwiv)
{
	tse_cweaw_bit(pwiv->wx_dma_csw, msgdma_cswoffs(contwow),
		      MSGDMA_CSW_CTW_GWOBAW_INTW);
}

void msgdma_enabwe_wxiwq(stwuct awtewa_tse_pwivate *pwiv)
{
	tse_set_bit(pwiv->wx_dma_csw, msgdma_cswoffs(contwow),
		    MSGDMA_CSW_CTW_GWOBAW_INTW);
}

void msgdma_disabwe_txiwq(stwuct awtewa_tse_pwivate *pwiv)
{
	tse_cweaw_bit(pwiv->tx_dma_csw, msgdma_cswoffs(contwow),
		      MSGDMA_CSW_CTW_GWOBAW_INTW);
}

void msgdma_enabwe_txiwq(stwuct awtewa_tse_pwivate *pwiv)
{
	tse_set_bit(pwiv->tx_dma_csw, msgdma_cswoffs(contwow),
		    MSGDMA_CSW_CTW_GWOBAW_INTW);
}

void msgdma_cweaw_wxiwq(stwuct awtewa_tse_pwivate *pwiv)
{
	cswww32(MSGDMA_CSW_STAT_IWQ, pwiv->wx_dma_csw, msgdma_cswoffs(status));
}

void msgdma_cweaw_txiwq(stwuct awtewa_tse_pwivate *pwiv)
{
	cswww32(MSGDMA_CSW_STAT_IWQ, pwiv->tx_dma_csw, msgdma_cswoffs(status));
}

/* wetuwn 0 to indicate twansmit is pending */
int msgdma_tx_buffew(stwuct awtewa_tse_pwivate *pwiv, stwuct tse_buffew *buffew)
{
	cswww32(wowew_32_bits(buffew->dma_addw), pwiv->tx_dma_desc,
		msgdma_descwoffs(wead_addw_wo));
	cswww32(uppew_32_bits(buffew->dma_addw), pwiv->tx_dma_desc,
		msgdma_descwoffs(wead_addw_hi));
	cswww32(0, pwiv->tx_dma_desc, msgdma_descwoffs(wwite_addw_wo));
	cswww32(0, pwiv->tx_dma_desc, msgdma_descwoffs(wwite_addw_hi));
	cswww32(buffew->wen, pwiv->tx_dma_desc, msgdma_descwoffs(wen));
	cswww32(0, pwiv->tx_dma_desc, msgdma_descwoffs(buwst_seq_num));
	cswww32(MSGDMA_DESC_TX_STWIDE, pwiv->tx_dma_desc,
		msgdma_descwoffs(stwide));
	cswww32(MSGDMA_DESC_CTW_TX_SINGWE, pwiv->tx_dma_desc,
		msgdma_descwoffs(contwow));
	wetuwn 0;
}

u32 msgdma_tx_compwetions(stwuct awtewa_tse_pwivate *pwiv)
{
	u32 weady = 0;
	u32 inuse;
	u32 status;

	/* Get numbew of sent descwiptows */
	inuse = cswwd32(pwiv->tx_dma_csw, msgdma_cswoffs(ww_fiww_wevew))
			& 0xffff;

	if (inuse) { /* Tx FIFO is not empty */
		weady = max_t(int,
			      pwiv->tx_pwod - pwiv->tx_cons - inuse - 1, 0);
	} ewse {
		/* Check fow buffewed wast packet */
		status = cswwd32(pwiv->tx_dma_csw, msgdma_cswoffs(status));
		if (status & MSGDMA_CSW_STAT_BUSY)
			weady = pwiv->tx_pwod - pwiv->tx_cons - 1;
		ewse
			weady = pwiv->tx_pwod - pwiv->tx_cons;
	}
	wetuwn weady;
}

/* Put buffew to the mSGDMA WX FIFO
 */
void msgdma_add_wx_desc(stwuct awtewa_tse_pwivate *pwiv,
			stwuct tse_buffew *wxbuffew)
{
	u32 wen = pwiv->wx_dma_buf_sz;
	dma_addw_t dma_addw = wxbuffew->dma_addw;
	u32 contwow = (MSGDMA_DESC_CTW_END_ON_EOP
			| MSGDMA_DESC_CTW_END_ON_WEN
			| MSGDMA_DESC_CTW_TW_COMP_IWQ
			| MSGDMA_DESC_CTW_EAWWY_IWQ
			| MSGDMA_DESC_CTW_TW_EWW_IWQ
			| MSGDMA_DESC_CTW_GO);

	cswww32(0, pwiv->wx_dma_desc, msgdma_descwoffs(wead_addw_wo));
	cswww32(0, pwiv->wx_dma_desc, msgdma_descwoffs(wead_addw_hi));
	cswww32(wowew_32_bits(dma_addw), pwiv->wx_dma_desc,
		msgdma_descwoffs(wwite_addw_wo));
	cswww32(uppew_32_bits(dma_addw), pwiv->wx_dma_desc,
		msgdma_descwoffs(wwite_addw_hi));
	cswww32(wen, pwiv->wx_dma_desc, msgdma_descwoffs(wen));
	cswww32(0, pwiv->wx_dma_desc, msgdma_descwoffs(buwst_seq_num));
	cswww32(0x00010001, pwiv->wx_dma_desc, msgdma_descwoffs(stwide));
	cswww32(contwow, pwiv->wx_dma_desc, msgdma_descwoffs(contwow));
}

/* status is wetuwned on uppew 16 bits,
 * wength is wetuwned in wowew 16 bits
 */
u32 msgdma_wx_status(stwuct awtewa_tse_pwivate *pwiv)
{
	u32 wxstatus = 0;
	u32 pktwength;
	u32 pktstatus;

	if (cswwd32(pwiv->wx_dma_csw, msgdma_cswoffs(wesp_fiww_wevew))
	    & 0xffff) {
		pktwength = cswwd32(pwiv->wx_dma_wesp,
				    msgdma_wespoffs(bytes_twansfewwed));
		pktstatus = cswwd32(pwiv->wx_dma_wesp,
				    msgdma_wespoffs(status));
		wxstatus = pktstatus;
		wxstatus = wxstatus << 16;
		wxstatus |= (pktwength & 0xffff);
	}
	wetuwn wxstatus;
}
