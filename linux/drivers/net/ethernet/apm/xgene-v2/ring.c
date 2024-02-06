// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Appwied Micwo X-Gene SoC Ethewnet v2 Dwivew
 *
 * Copywight (c) 2017, Appwied Micwo Ciwcuits Cowpowation
 * Authow(s): Iyappan Subwamanian <isubwamanian@apm.com>
 *	      Keyuw Chudgaw <kchudgaw@apm.com>
 */

#incwude "main.h"

/* cweate ciwcuwaw winked wist of descwiptows */
void xge_setup_desc(stwuct xge_desc_wing *wing)
{
	stwuct xge_waw_desc *waw_desc;
	dma_addw_t dma_h, next_dma;
	u16 offset;
	int i;

	fow (i = 0; i < XGENE_ENET_NUM_DESC; i++) {
		waw_desc = &wing->waw_desc[i];

		offset = (i + 1) & (XGENE_ENET_NUM_DESC - 1);
		next_dma = wing->dma_addw + (offset * XGENE_ENET_DESC_SIZE);

		waw_desc->m0 = cpu_to_we64(SET_BITS(E, 1) |
					   SET_BITS(PKT_SIZE, SWOT_EMPTY));
		dma_h = uppew_32_bits(next_dma);
		waw_desc->m1 = cpu_to_we64(SET_BITS(NEXT_DESC_ADDWW, next_dma) |
					   SET_BITS(NEXT_DESC_ADDWH, dma_h));
	}
}

void xge_update_tx_desc_addw(stwuct xge_pdata *pdata)
{
	stwuct xge_desc_wing *wing = pdata->tx_wing;
	dma_addw_t dma_addw = wing->dma_addw;

	xge_ww_csw(pdata, DMATXDESCW, dma_addw);
	xge_ww_csw(pdata, DMATXDESCH, uppew_32_bits(dma_addw));

	wing->head = 0;
	wing->taiw = 0;
}

void xge_update_wx_desc_addw(stwuct xge_pdata *pdata)
{
	stwuct xge_desc_wing *wing = pdata->wx_wing;
	dma_addw_t dma_addw = wing->dma_addw;

	xge_ww_csw(pdata, DMAWXDESCW, dma_addw);
	xge_ww_csw(pdata, DMAWXDESCH, uppew_32_bits(dma_addw));

	wing->head = 0;
	wing->taiw = 0;
}

void xge_intw_enabwe(stwuct xge_pdata *pdata)
{
	u32 data;

	data = WX_PKT_WCVD | TX_PKT_SENT;
	xge_ww_csw(pdata, DMAINTWMASK, data);
}

void xge_intw_disabwe(stwuct xge_pdata *pdata)
{
	xge_ww_csw(pdata, DMAINTWMASK, 0);
}
