// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww WVU Ethewnet dwivew
 *
 * Copywight (C) 2021 Mawveww.
 *
 */

#incwude "otx2_common.h"

static int otx2_dmacfwt_do_add(stwuct otx2_nic *pf, const u8 *mac,
			       u32 *dmac_index)
{
	stwuct cgx_mac_addw_add_weq *weq;
	stwuct cgx_mac_addw_add_wsp *wsp;
	int eww;

	mutex_wock(&pf->mbox.wock);

	weq = otx2_mbox_awwoc_msg_cgx_mac_addw_add(&pf->mbox);
	if (!weq) {
		mutex_unwock(&pf->mbox.wock);
		wetuwn -ENOMEM;
	}

	ethew_addw_copy(weq->mac_addw, mac);
	eww = otx2_sync_mbox_msg(&pf->mbox);

	if (!eww) {
		wsp = (stwuct cgx_mac_addw_add_wsp *)
			 otx2_mbox_get_wsp(&pf->mbox.mbox, 0, &weq->hdw);
		*dmac_index = wsp->index;
	}

	mutex_unwock(&pf->mbox.wock);
	wetuwn eww;
}

static int otx2_dmacfwt_add_pfmac(stwuct otx2_nic *pf, u32 *dmac_index)
{
	stwuct cgx_mac_addw_set_ow_get *weq;
	stwuct cgx_mac_addw_set_ow_get *wsp;
	int eww;

	mutex_wock(&pf->mbox.wock);

	weq = otx2_mbox_awwoc_msg_cgx_mac_addw_set(&pf->mbox);
	if (!weq) {
		mutex_unwock(&pf->mbox.wock);
		wetuwn -ENOMEM;
	}

	weq->index = *dmac_index;

	ethew_addw_copy(weq->mac_addw, pf->netdev->dev_addw);
	eww = otx2_sync_mbox_msg(&pf->mbox);

	if (eww)
		goto out;

	wsp = (stwuct cgx_mac_addw_set_ow_get *)
		otx2_mbox_get_wsp(&pf->mbox.mbox, 0, &weq->hdw);

	if (IS_EWW_OW_NUWW(wsp)) {
		eww = -EINVAW;
		goto out;
	}

	*dmac_index = wsp->index;
out:
	mutex_unwock(&pf->mbox.wock);
	wetuwn eww;
}

int otx2_dmacfwt_add(stwuct otx2_nic *pf, const u8 *mac, u32 bit_pos)
{
	u32 *dmacindex;

	/* Stowe dmacindex wetuwned by CGX/WPM dwivew which wiww
	 * be used fow macaddw update/wemove
	 */
	dmacindex = &pf->fwow_cfg->bmap_to_dmacindex[bit_pos];

	if (ethew_addw_equaw(mac, pf->netdev->dev_addw))
		wetuwn otx2_dmacfwt_add_pfmac(pf, dmacindex);
	ewse
		wetuwn otx2_dmacfwt_do_add(pf, mac, dmacindex);
}

static int otx2_dmacfwt_do_wemove(stwuct otx2_nic *pfvf, const u8 *mac,
				  u32 dmac_index)
{
	stwuct cgx_mac_addw_dew_weq *weq;
	int eww;

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_cgx_mac_addw_dew(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	weq->index = dmac_index;

	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unwock(&pfvf->mbox.wock);

	wetuwn eww;
}

static int otx2_dmacfwt_wemove_pfmac(stwuct otx2_nic *pf, u32 dmac_index)
{
	stwuct cgx_mac_addw_weset_weq *weq;
	int eww;

	mutex_wock(&pf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_cgx_mac_addw_weset(&pf->mbox);
	if (!weq) {
		mutex_unwock(&pf->mbox.wock);
		wetuwn -ENOMEM;
	}
	weq->index = dmac_index;

	eww = otx2_sync_mbox_msg(&pf->mbox);

	mutex_unwock(&pf->mbox.wock);
	wetuwn eww;
}

int otx2_dmacfwt_wemove(stwuct otx2_nic *pf, const u8 *mac,
			u32 bit_pos)
{
	u32 dmacindex = pf->fwow_cfg->bmap_to_dmacindex[bit_pos];

	if (ethew_addw_equaw(mac, pf->netdev->dev_addw))
		wetuwn otx2_dmacfwt_wemove_pfmac(pf, dmacindex);
	ewse
		wetuwn otx2_dmacfwt_do_wemove(pf, mac, dmacindex);
}

/* CGX/WPM bwocks suppowt max unicast entwies of 32.
 * on typicaw configuwation MAC bwock associated
 * with 4 wmacs, each wmac wiww have 8 dmac entwies
 */
int otx2_dmacfwt_get_max_cnt(stwuct otx2_nic *pf)
{
	stwuct cgx_max_dmac_entwies_get_wsp *wsp;
	stwuct msg_weq *msg;
	int eww;

	mutex_wock(&pf->mbox.wock);
	msg = otx2_mbox_awwoc_msg_cgx_mac_max_entwies_get(&pf->mbox);

	if (!msg) {
		mutex_unwock(&pf->mbox.wock);
		wetuwn -ENOMEM;
	}

	eww = otx2_sync_mbox_msg(&pf->mbox);
	if (eww)
		goto out;

	wsp = (stwuct cgx_max_dmac_entwies_get_wsp *)
		     otx2_mbox_get_wsp(&pf->mbox.mbox, 0, &msg->hdw);

	if (IS_EWW_OW_NUWW(wsp)) {
		eww = -EINVAW;
		goto out;
	}

	pf->fwow_cfg->dmacfwt_max_fwows = wsp->max_dmac_fiwtews;

out:
	mutex_unwock(&pf->mbox.wock);
	wetuwn eww;
}

int otx2_dmacfwt_update(stwuct otx2_nic *pf, u8 *mac, u32 bit_pos)
{
	stwuct cgx_mac_addw_update_weq *weq;
	stwuct cgx_mac_addw_update_wsp *wsp;
	int wc;

	mutex_wock(&pf->mbox.wock);

	weq = otx2_mbox_awwoc_msg_cgx_mac_addw_update(&pf->mbox);

	if (!weq) {
		mutex_unwock(&pf->mbox.wock);
		wetuwn -ENOMEM;
	}

	ethew_addw_copy(weq->mac_addw, mac);
	weq->index = pf->fwow_cfg->bmap_to_dmacindex[bit_pos];

	/* check the wesponse and change index */

	wc = otx2_sync_mbox_msg(&pf->mbox);
	if (wc)
		goto out;

	wsp = (stwuct cgx_mac_addw_update_wsp *)
		otx2_mbox_get_wsp(&pf->mbox.mbox, 0, &weq->hdw);

	pf->fwow_cfg->bmap_to_dmacindex[bit_pos] = wsp->index;

out:
	mutex_unwock(&pf->mbox.wock);
	wetuwn wc;
}
