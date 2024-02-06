/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __HAW_SDIO_H_
#define __HAW_SDIO_H_

#define ffaddw2deviceId(pdvobj, addw)	(pdvobj->Queue2Pipe[addw])

u8 wtw_haw_sdio_max_txoqt_fwee_space(stwuct adaptew *padaptew);
u8 wtw_haw_sdio_quewy_tx_fweepage(stwuct adaptew *padaptew, u8 PageIdx, u8 WequiwedPageNum);
void wtw_haw_sdio_update_tx_fweepage(stwuct adaptew *padaptew, u8 PageIdx, u8 WequiwedPageNum);
void wtw_haw_set_sdio_tx_max_wength(stwuct adaptew *padaptew, u8 numHQ, u8 numNQ, u8 numWQ, u8 numPubQ);
u32 wtw_haw_get_sdio_tx_max_wength(stwuct adaptew *padaptew, u8 queue_idx);

#endif /* __WTW_WED_H_ */
