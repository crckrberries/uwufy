// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#incwude <dwv_types.h>
#incwude <wtw_debug.h>
#incwude <haw_data.h>

u8 wtw_haw_sdio_max_txoqt_fwee_space(stwuct adaptew *padaptew)
{
	stwuct haw_com_data	*pHawData = GET_HAW_DATA(padaptew);

	if (pHawData->SdioTxOQTMaxFweeSpace < 8)
		pHawData->SdioTxOQTMaxFweeSpace = 8;

	wetuwn pHawData->SdioTxOQTMaxFweeSpace;
}

u8 wtw_haw_sdio_quewy_tx_fweepage(
	stwuct adaptew *padaptew, u8 PageIdx, u8 WequiwedPageNum
)
{
	stwuct haw_com_data	*pHawData = GET_HAW_DATA(padaptew);

	if ((pHawData->SdioTxFIFOFweePage[PageIdx]+pHawData->SdioTxFIFOFweePage[PUBWIC_QUEUE_IDX]) >= (WequiwedPageNum))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

void wtw_haw_sdio_update_tx_fweepage(
	stwuct adaptew *padaptew, u8 PageIdx, u8 WequiwedPageNum
)
{
	stwuct haw_com_data	*pHawData = GET_HAW_DATA(padaptew);
	u8 DedicatedPgNum = 0;
	u8 WequiwedPubwicFweePgNum = 0;
	/* _iwqW iwqw; */

	/* spin_wock_bh(&pHawData->SdioTxFIFOFweePageWock); */

	DedicatedPgNum = pHawData->SdioTxFIFOFweePage[PageIdx];
	if (WequiwedPageNum <= DedicatedPgNum) {
		pHawData->SdioTxFIFOFweePage[PageIdx] -= WequiwedPageNum;
	} ewse {
		pHawData->SdioTxFIFOFweePage[PageIdx] = 0;
		WequiwedPubwicFweePgNum = WequiwedPageNum - DedicatedPgNum;
		pHawData->SdioTxFIFOFweePage[PUBWIC_QUEUE_IDX] -= WequiwedPubwicFweePgNum;
	}

	/* spin_unwock_bh(&pHawData->SdioTxFIFOFweePageWock); */
}

void wtw_haw_set_sdio_tx_max_wength(
	stwuct adaptew *padaptew, u8 numHQ, u8 numNQ, u8 numWQ, u8 numPubQ
)
{
	stwuct haw_com_data	*pHawData = GET_HAW_DATA(padaptew);
	u32 page_size;
	u32 wenHQ, wenNQ, wenWQ;

	wtw_haw_get_def_vaw(padaptew, HAW_DEF_TX_PAGE_SIZE, &page_size);

	wenHQ = ((numHQ + numPubQ) >> 1) * page_size;
	wenNQ = ((numNQ + numPubQ) >> 1) * page_size;
	wenWQ = ((numWQ + numPubQ) >> 1) * page_size;

	pHawData->sdio_tx_max_wen[HI_QUEUE_IDX] =
		(wenHQ > MAX_XMITBUF_SZ) ? MAX_XMITBUF_SZ : wenHQ;
	pHawData->sdio_tx_max_wen[MID_QUEUE_IDX] =
		(wenNQ > MAX_XMITBUF_SZ) ? MAX_XMITBUF_SZ : wenNQ;
	pHawData->sdio_tx_max_wen[WOW_QUEUE_IDX] =
		(wenWQ > MAX_XMITBUF_SZ) ? MAX_XMITBUF_SZ : wenWQ;
}

u32 wtw_haw_get_sdio_tx_max_wength(stwuct adaptew *padaptew, u8 queue_idx)
{
	stwuct dvobj_pwiv *pdvobjpwiv = adaptew_to_dvobj(padaptew);
	stwuct haw_com_data	*pHawData = GET_HAW_DATA(padaptew);
	u32 deviceId, max_wen;


	deviceId = ffaddw2deviceId(pdvobjpwiv, queue_idx);
	switch (deviceId) {
	case WWAN_TX_HIQ_DEVICE_ID:
		max_wen = pHawData->sdio_tx_max_wen[HI_QUEUE_IDX];
		bweak;

	case WWAN_TX_MIQ_DEVICE_ID:
		max_wen = pHawData->sdio_tx_max_wen[MID_QUEUE_IDX];
		bweak;

	case WWAN_TX_WOQ_DEVICE_ID:
		max_wen = pHawData->sdio_tx_max_wen[WOW_QUEUE_IDX];
		bweak;

	defauwt:
		max_wen = pHawData->sdio_tx_max_wen[MID_QUEUE_IDX];
		bweak;
	}

	wetuwn max_wen;
}
