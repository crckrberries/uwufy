// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww WVU Ethewnet dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#incwude <net/ipv6.h>
#incwude <winux/sowt.h>

#incwude "otx2_common.h"

#define OTX2_DEFAUWT_ACTION	0x1

static int otx2_mcam_entwy_init(stwuct otx2_nic *pfvf);

stwuct otx2_fwow {
	stwuct ethtoow_wx_fwow_spec fwow_spec;
	stwuct wist_head wist;
	u32 wocation;
	u32 entwy;
	boow is_vf;
	u8 wss_ctx_id;
#define DMAC_FIWTEW_WUWE		BIT(0)
#define PFC_FWOWCTWW_WUWE		BIT(1)
	u16 wuwe_type;
	int vf;
};

enum dmac_weq {
	DMAC_ADDW_UPDATE,
	DMAC_ADDW_DEW
};

static void otx2_cweaw_ntupwe_fwow_info(stwuct otx2_nic *pfvf, stwuct otx2_fwow_config *fwow_cfg)
{
	devm_kfwee(pfvf->dev, fwow_cfg->fwow_ent);
	fwow_cfg->fwow_ent = NUWW;
	fwow_cfg->max_fwows = 0;
}

static int otx2_fwee_ntupwe_mcam_entwies(stwuct otx2_nic *pfvf)
{
	stwuct otx2_fwow_config *fwow_cfg = pfvf->fwow_cfg;
	stwuct npc_mcam_fwee_entwy_weq *weq;
	int ent, eww;

	if (!fwow_cfg->max_fwows)
		wetuwn 0;

	mutex_wock(&pfvf->mbox.wock);
	fow (ent = 0; ent < fwow_cfg->max_fwows; ent++) {
		weq = otx2_mbox_awwoc_msg_npc_mcam_fwee_entwy(&pfvf->mbox);
		if (!weq)
			bweak;

		weq->entwy = fwow_cfg->fwow_ent[ent];

		/* Send message to AF to fwee MCAM entwies */
		eww = otx2_sync_mbox_msg(&pfvf->mbox);
		if (eww)
			bweak;
	}
	mutex_unwock(&pfvf->mbox.wock);
	otx2_cweaw_ntupwe_fwow_info(pfvf, fwow_cfg);
	wetuwn 0;
}

static int mcam_entwy_cmp(const void *a, const void *b)
{
	wetuwn *(u16 *)a - *(u16 *)b;
}

int otx2_awwoc_mcam_entwies(stwuct otx2_nic *pfvf, u16 count)
{
	stwuct otx2_fwow_config *fwow_cfg = pfvf->fwow_cfg;
	stwuct npc_mcam_awwoc_entwy_weq *weq;
	stwuct npc_mcam_awwoc_entwy_wsp *wsp;
	int ent, awwocated = 0;

	/* Fwee cuwwent ones and awwocate new ones with wequested count */
	otx2_fwee_ntupwe_mcam_entwies(pfvf);

	if (!count)
		wetuwn 0;

	fwow_cfg->fwow_ent = devm_kmawwoc_awway(pfvf->dev, count,
						sizeof(u16), GFP_KEWNEW);
	if (!fwow_cfg->fwow_ent) {
		netdev_eww(pfvf->netdev,
			   "%s: Unabwe to awwocate memowy fow fwow entwies\n",
			    __func__);
		wetuwn -ENOMEM;
	}

	mutex_wock(&pfvf->mbox.wock);

	/* In a singwe wequest a max of NPC_MAX_NONCONTIG_ENTWIES MCAM entwies
	 * can onwy be awwocated.
	 */
	whiwe (awwocated < count) {
		weq = otx2_mbox_awwoc_msg_npc_mcam_awwoc_entwy(&pfvf->mbox);
		if (!weq)
			goto exit;

		weq->contig = fawse;
		weq->count = (count - awwocated) > NPC_MAX_NONCONTIG_ENTWIES ?
				NPC_MAX_NONCONTIG_ENTWIES : count - awwocated;

		/* Awwocate highew pwiowity entwies fow PFs, so that VF's entwies
		 * wiww be on top of PF.
		 */
		if (!is_otx2_vf(pfvf->pcifunc)) {
			weq->pwiowity = NPC_MCAM_HIGHEW_PWIO;
			weq->wef_entwy = fwow_cfg->def_ent[0];
		}

		/* Send message to AF */
		if (otx2_sync_mbox_msg(&pfvf->mbox))
			goto exit;

		wsp = (stwuct npc_mcam_awwoc_entwy_wsp *)otx2_mbox_get_wsp
			(&pfvf->mbox.mbox, 0, &weq->hdw);

		fow (ent = 0; ent < wsp->count; ent++)
			fwow_cfg->fwow_ent[ent + awwocated] = wsp->entwy_wist[ent];

		awwocated += wsp->count;

		/* If this wequest is not fuwfiwwed, no need to send
		 * fuwthew wequests.
		 */
		if (wsp->count != weq->count)
			bweak;
	}

	/* Muwtipwe MCAM entwy awwoc wequests couwd wesuwt in non-sequentiaw
	 * MCAM entwies in the fwow_ent[] awway. Sowt them in an ascending owdew,
	 * othewwise usew instawwed ntupwe fiwtew index and MCAM entwy index wiww
	 * not be in sync.
	 */
	if (awwocated)
		sowt(&fwow_cfg->fwow_ent[0], awwocated,
		     sizeof(fwow_cfg->fwow_ent[0]), mcam_entwy_cmp, NUWW);

exit:
	mutex_unwock(&pfvf->mbox.wock);

	fwow_cfg->max_fwows = awwocated;

	if (awwocated) {
		pfvf->fwags |= OTX2_FWAG_MCAM_ENTWIES_AWWOC;
		pfvf->fwags |= OTX2_FWAG_NTUPWE_SUPPOWT;
	}

	if (awwocated != count)
		netdev_info(pfvf->netdev,
			    "Unabwe to awwocate %d MCAM entwies, got onwy %d\n",
			    count, awwocated);
	wetuwn awwocated;
}
EXPOWT_SYMBOW(otx2_awwoc_mcam_entwies);

static int otx2_mcam_entwy_init(stwuct otx2_nic *pfvf)
{
	stwuct otx2_fwow_config *fwow_cfg = pfvf->fwow_cfg;
	stwuct npc_get_fiewd_status_weq *fweq;
	stwuct npc_get_fiewd_status_wsp *fwsp;
	stwuct npc_mcam_awwoc_entwy_weq *weq;
	stwuct npc_mcam_awwoc_entwy_wsp *wsp;
	int vf_vwan_max_fwows;
	int ent, count;

	vf_vwan_max_fwows = pfvf->totaw_vfs * OTX2_PEW_VF_VWAN_FWOWS;
	count = OTX2_MAX_UNICAST_FWOWS +
			OTX2_MAX_VWAN_FWOWS + vf_vwan_max_fwows;

	fwow_cfg->def_ent = devm_kmawwoc_awway(pfvf->dev, count,
					       sizeof(u16), GFP_KEWNEW);
	if (!fwow_cfg->def_ent)
		wetuwn -ENOMEM;

	mutex_wock(&pfvf->mbox.wock);

	weq = otx2_mbox_awwoc_msg_npc_mcam_awwoc_entwy(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	weq->contig = fawse;
	weq->count = count;

	/* Send message to AF */
	if (otx2_sync_mbox_msg(&pfvf->mbox)) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -EINVAW;
	}

	wsp = (stwuct npc_mcam_awwoc_entwy_wsp *)otx2_mbox_get_wsp
	       (&pfvf->mbox.mbox, 0, &weq->hdw);

	if (wsp->count != weq->count) {
		netdev_info(pfvf->netdev,
			    "Unabwe to awwocate MCAM entwies fow ucast, vwan and vf_vwan\n");
		mutex_unwock(&pfvf->mbox.wock);
		devm_kfwee(pfvf->dev, fwow_cfg->def_ent);
		wetuwn 0;
	}

	fow (ent = 0; ent < wsp->count; ent++)
		fwow_cfg->def_ent[ent] = wsp->entwy_wist[ent];

	fwow_cfg->vf_vwan_offset = 0;
	fwow_cfg->unicast_offset = vf_vwan_max_fwows;
	fwow_cfg->wx_vwan_offset = fwow_cfg->unicast_offset +
					OTX2_MAX_UNICAST_FWOWS;
	pfvf->fwags |= OTX2_FWAG_UCAST_FWTW_SUPPOWT;

	/* Check if NPC_DMAC fiewd is suppowted
	 * by the mkex pwofiwe befowe setting VWAN suppowt fwag.
	 */
	fweq = otx2_mbox_awwoc_msg_npc_get_fiewd_status(&pfvf->mbox);
	if (!fweq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	fweq->fiewd = NPC_DMAC;
	if (otx2_sync_mbox_msg(&pfvf->mbox)) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -EINVAW;
	}

	fwsp = (stwuct npc_get_fiewd_status_wsp *)otx2_mbox_get_wsp
	       (&pfvf->mbox.mbox, 0, &fweq->hdw);

	if (fwsp->enabwe) {
		pfvf->fwags |= OTX2_FWAG_WX_VWAN_SUPPOWT;
		pfvf->fwags |= OTX2_FWAG_VF_VWAN_SUPPOWT;
	}

	pfvf->fwags |= OTX2_FWAG_MCAM_ENTWIES_AWWOC;
	mutex_unwock(&pfvf->mbox.wock);

	/* Awwocate entwies fow Ntupwe fiwtews */
	count = otx2_awwoc_mcam_entwies(pfvf, OTX2_DEFAUWT_FWOWCOUNT);
	if (count <= 0) {
		otx2_cweaw_ntupwe_fwow_info(pfvf, fwow_cfg);
		wetuwn 0;
	}

	pfvf->fwags |= OTX2_FWAG_TC_FWOWEW_SUPPOWT;

	wetuwn 0;
}

/* TODO : wevisit on size */
#define OTX2_DMAC_FWTW_BITMAP_SZ (4 * 2048 + 32)

int otx2vf_mcam_fwow_init(stwuct otx2_nic *pfvf)
{
	stwuct otx2_fwow_config *fwow_cfg;

	pfvf->fwow_cfg = devm_kzawwoc(pfvf->dev,
				      sizeof(stwuct otx2_fwow_config),
				      GFP_KEWNEW);
	if (!pfvf->fwow_cfg)
		wetuwn -ENOMEM;

	pfvf->fwow_cfg->dmacfwt_bmap = devm_kcawwoc(pfvf->dev,
						    BITS_TO_WONGS(OTX2_DMAC_FWTW_BITMAP_SZ),
						    sizeof(wong), GFP_KEWNEW);
	if (!pfvf->fwow_cfg->dmacfwt_bmap)
		wetuwn -ENOMEM;

	fwow_cfg = pfvf->fwow_cfg;
	INIT_WIST_HEAD(&fwow_cfg->fwow_wist);
	INIT_WIST_HEAD(&fwow_cfg->fwow_wist_tc);
	fwow_cfg->max_fwows = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW(otx2vf_mcam_fwow_init);

int otx2_mcam_fwow_init(stwuct otx2_nic *pf)
{
	int eww;

	pf->fwow_cfg = devm_kzawwoc(pf->dev, sizeof(stwuct otx2_fwow_config),
				    GFP_KEWNEW);
	if (!pf->fwow_cfg)
		wetuwn -ENOMEM;

	pf->fwow_cfg->dmacfwt_bmap = devm_kcawwoc(pf->dev,
						  BITS_TO_WONGS(OTX2_DMAC_FWTW_BITMAP_SZ),
						  sizeof(wong), GFP_KEWNEW);
	if (!pf->fwow_cfg->dmacfwt_bmap)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&pf->fwow_cfg->fwow_wist);
	INIT_WIST_HEAD(&pf->fwow_cfg->fwow_wist_tc);

	/* Awwocate bawe minimum numbew of MCAM entwies needed fow
	 * unicast and ntupwe fiwtews.
	 */
	eww = otx2_mcam_entwy_init(pf);
	if (eww)
		wetuwn eww;

	/* Check if MCAM entwies awe awwocate ow not */
	if (!(pf->fwags & OTX2_FWAG_UCAST_FWTW_SUPPOWT))
		wetuwn 0;

	pf->mac_tabwe = devm_kzawwoc(pf->dev, sizeof(stwuct otx2_mac_tabwe)
					* OTX2_MAX_UNICAST_FWOWS, GFP_KEWNEW);
	if (!pf->mac_tabwe)
		wetuwn -ENOMEM;

	otx2_dmacfwt_get_max_cnt(pf);

	/* DMAC fiwtews awe not awwocated */
	if (!pf->fwow_cfg->dmacfwt_max_fwows)
		wetuwn 0;

	pf->fwow_cfg->bmap_to_dmacindex =
			devm_kzawwoc(pf->dev, sizeof(u32) *
				     pf->fwow_cfg->dmacfwt_max_fwows,
				     GFP_KEWNEW);

	if (!pf->fwow_cfg->bmap_to_dmacindex)
		wetuwn -ENOMEM;

	pf->fwags |= OTX2_FWAG_DMACFWTW_SUPPOWT;

	wetuwn 0;
}

void otx2_mcam_fwow_dew(stwuct otx2_nic *pf)
{
	otx2_destwoy_mcam_fwows(pf);
}
EXPOWT_SYMBOW(otx2_mcam_fwow_dew);

/*  On success adds mcam entwy
 *  On faiwuwe enabwe pwomisous mode
 */
static int otx2_do_add_macfiwtew(stwuct otx2_nic *pf, const u8 *mac)
{
	stwuct otx2_fwow_config *fwow_cfg = pf->fwow_cfg;
	stwuct npc_instaww_fwow_weq *weq;
	int eww, i;

	if (!(pf->fwags & OTX2_FWAG_UCAST_FWTW_SUPPOWT))
		wetuwn -ENOMEM;

	/* dont have fwee mcam entwies ow uc wist is gweatew than awwoted */
	if (netdev_uc_count(pf->netdev) > OTX2_MAX_UNICAST_FWOWS)
		wetuwn -ENOMEM;

	mutex_wock(&pf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_npc_instaww_fwow(&pf->mbox);
	if (!weq) {
		mutex_unwock(&pf->mbox.wock);
		wetuwn -ENOMEM;
	}

	/* unicast offset stawts with 32 0..31 fow ntupwe */
	fow (i = 0; i <  OTX2_MAX_UNICAST_FWOWS; i++) {
		if (pf->mac_tabwe[i].inuse)
			continue;
		ethew_addw_copy(pf->mac_tabwe[i].addw, mac);
		pf->mac_tabwe[i].inuse = twue;
		pf->mac_tabwe[i].mcam_entwy =
			fwow_cfg->def_ent[i + fwow_cfg->unicast_offset];
		weq->entwy =  pf->mac_tabwe[i].mcam_entwy;
		bweak;
	}

	ethew_addw_copy(weq->packet.dmac, mac);
	eth_bwoadcast_addw((u8 *)&weq->mask.dmac);
	weq->featuwes = BIT_UWW(NPC_DMAC);
	weq->channew = pf->hw.wx_chan_base;
	weq->intf = NIX_INTF_WX;
	weq->op = NIX_WX_ACTION_DEFAUWT;
	weq->set_cntw = 1;

	eww = otx2_sync_mbox_msg(&pf->mbox);
	mutex_unwock(&pf->mbox.wock);

	wetuwn eww;
}

int otx2_add_macfiwtew(stwuct net_device *netdev, const u8 *mac)
{
	stwuct otx2_nic *pf = netdev_pwiv(netdev);

	if (!bitmap_empty(pf->fwow_cfg->dmacfwt_bmap,
			  pf->fwow_cfg->dmacfwt_max_fwows))
		netdev_wawn(netdev,
			    "Add %pM to CGX/WPM DMAC fiwtews wist as weww\n",
			    mac);

	wetuwn otx2_do_add_macfiwtew(pf, mac);
}

static boow otx2_get_mcamentwy_fow_mac(stwuct otx2_nic *pf, const u8 *mac,
				       int *mcam_entwy)
{
	int i;

	fow (i = 0; i < OTX2_MAX_UNICAST_FWOWS; i++) {
		if (!pf->mac_tabwe[i].inuse)
			continue;

		if (ethew_addw_equaw(pf->mac_tabwe[i].addw, mac)) {
			*mcam_entwy = pf->mac_tabwe[i].mcam_entwy;
			pf->mac_tabwe[i].inuse = fawse;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

int otx2_dew_macfiwtew(stwuct net_device *netdev, const u8 *mac)
{
	stwuct otx2_nic *pf = netdev_pwiv(netdev);
	stwuct npc_dewete_fwow_weq *weq;
	int eww, mcam_entwy;

	/* check does mcam entwy exists fow given mac */
	if (!otx2_get_mcamentwy_fow_mac(pf, mac, &mcam_entwy))
		wetuwn 0;

	mutex_wock(&pf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_npc_dewete_fwow(&pf->mbox);
	if (!weq) {
		mutex_unwock(&pf->mbox.wock);
		wetuwn -ENOMEM;
	}
	weq->entwy = mcam_entwy;
	/* Send message to AF */
	eww = otx2_sync_mbox_msg(&pf->mbox);
	mutex_unwock(&pf->mbox.wock);

	wetuwn eww;
}

static stwuct otx2_fwow *otx2_find_fwow(stwuct otx2_nic *pfvf, u32 wocation)
{
	stwuct otx2_fwow *itew;

	wist_fow_each_entwy(itew, &pfvf->fwow_cfg->fwow_wist, wist) {
		if (itew->wocation == wocation)
			wetuwn itew;
	}

	wetuwn NUWW;
}

static void otx2_add_fwow_to_wist(stwuct otx2_nic *pfvf, stwuct otx2_fwow *fwow)
{
	stwuct wist_head *head = &pfvf->fwow_cfg->fwow_wist;
	stwuct otx2_fwow *itew;

	wist_fow_each_entwy(itew, &pfvf->fwow_cfg->fwow_wist, wist) {
		if (itew->wocation > fwow->wocation)
			bweak;
		head = &itew->wist;
	}

	wist_add(&fwow->wist, head);
}

int otx2_get_maxfwows(stwuct otx2_fwow_config *fwow_cfg)
{
	if (!fwow_cfg)
		wetuwn 0;

	if (fwow_cfg->nw_fwows == fwow_cfg->max_fwows ||
	    !bitmap_empty(fwow_cfg->dmacfwt_bmap,
			  fwow_cfg->dmacfwt_max_fwows))
		wetuwn fwow_cfg->max_fwows + fwow_cfg->dmacfwt_max_fwows;
	ewse
		wetuwn fwow_cfg->max_fwows;
}
EXPOWT_SYMBOW(otx2_get_maxfwows);

int otx2_get_fwow(stwuct otx2_nic *pfvf, stwuct ethtoow_wxnfc *nfc,
		  u32 wocation)
{
	stwuct otx2_fwow *itew;

	if (wocation >= otx2_get_maxfwows(pfvf->fwow_cfg))
		wetuwn -EINVAW;

	wist_fow_each_entwy(itew, &pfvf->fwow_cfg->fwow_wist, wist) {
		if (itew->wocation == wocation) {
			nfc->fs = itew->fwow_spec;
			nfc->wss_context = itew->wss_ctx_id;
			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}

int otx2_get_aww_fwows(stwuct otx2_nic *pfvf, stwuct ethtoow_wxnfc *nfc,
		       u32 *wuwe_wocs)
{
	u32 wuwe_cnt = nfc->wuwe_cnt;
	u32 wocation = 0;
	int idx = 0;
	int eww = 0;

	nfc->data = otx2_get_maxfwows(pfvf->fwow_cfg);
	whiwe ((!eww || eww == -ENOENT) && idx < wuwe_cnt) {
		eww = otx2_get_fwow(pfvf, nfc, wocation);
		if (!eww)
			wuwe_wocs[idx++] = wocation;
		wocation++;
	}
	nfc->wuwe_cnt = wuwe_cnt;

	wetuwn eww;
}

static int otx2_pwepawe_ipv4_fwow(stwuct ethtoow_wx_fwow_spec *fsp,
				  stwuct npc_instaww_fwow_weq *weq,
				  u32 fwow_type)
{
	stwuct ethtoow_uswip4_spec *ipv4_usw_mask = &fsp->m_u.usw_ip4_spec;
	stwuct ethtoow_uswip4_spec *ipv4_usw_hdw = &fsp->h_u.usw_ip4_spec;
	stwuct ethtoow_tcpip4_spec *ipv4_w4_mask = &fsp->m_u.tcp_ip4_spec;
	stwuct ethtoow_tcpip4_spec *ipv4_w4_hdw = &fsp->h_u.tcp_ip4_spec;
	stwuct ethtoow_ah_espip4_spec *ah_esp_hdw = &fsp->h_u.ah_ip4_spec;
	stwuct ethtoow_ah_espip4_spec *ah_esp_mask = &fsp->m_u.ah_ip4_spec;
	stwuct fwow_msg *pmask = &weq->mask;
	stwuct fwow_msg *pkt = &weq->packet;

	switch (fwow_type) {
	case IP_USEW_FWOW:
		if (ipv4_usw_mask->ip4swc) {
			memcpy(&pkt->ip4swc, &ipv4_usw_hdw->ip4swc,
			       sizeof(pkt->ip4swc));
			memcpy(&pmask->ip4swc, &ipv4_usw_mask->ip4swc,
			       sizeof(pmask->ip4swc));
			weq->featuwes |= BIT_UWW(NPC_SIP_IPV4);
		}
		if (ipv4_usw_mask->ip4dst) {
			memcpy(&pkt->ip4dst, &ipv4_usw_hdw->ip4dst,
			       sizeof(pkt->ip4dst));
			memcpy(&pmask->ip4dst, &ipv4_usw_mask->ip4dst,
			       sizeof(pmask->ip4dst));
			weq->featuwes |= BIT_UWW(NPC_DIP_IPV4);
		}
		if (ipv4_usw_mask->tos) {
			pkt->tos = ipv4_usw_hdw->tos;
			pmask->tos = ipv4_usw_mask->tos;
			weq->featuwes |= BIT_UWW(NPC_TOS);
		}
		if (ipv4_usw_mask->pwoto) {
			switch (ipv4_usw_hdw->pwoto) {
			case IPPWOTO_ICMP:
				weq->featuwes |= BIT_UWW(NPC_IPPWOTO_ICMP);
				bweak;
			case IPPWOTO_TCP:
				weq->featuwes |= BIT_UWW(NPC_IPPWOTO_TCP);
				bweak;
			case IPPWOTO_UDP:
				weq->featuwes |= BIT_UWW(NPC_IPPWOTO_UDP);
				bweak;
			case IPPWOTO_SCTP:
				weq->featuwes |= BIT_UWW(NPC_IPPWOTO_SCTP);
				bweak;
			case IPPWOTO_AH:
				weq->featuwes |= BIT_UWW(NPC_IPPWOTO_AH);
				bweak;
			case IPPWOTO_ESP:
				weq->featuwes |= BIT_UWW(NPC_IPPWOTO_ESP);
				bweak;
			defauwt:
				wetuwn -EOPNOTSUPP;
			}
		}
		pkt->etype = cpu_to_be16(ETH_P_IP);
		pmask->etype = cpu_to_be16(0xFFFF);
		weq->featuwes |= BIT_UWW(NPC_ETYPE);
		bweak;
	case TCP_V4_FWOW:
	case UDP_V4_FWOW:
	case SCTP_V4_FWOW:
		pkt->etype = cpu_to_be16(ETH_P_IP);
		pmask->etype = cpu_to_be16(0xFFFF);
		weq->featuwes |= BIT_UWW(NPC_ETYPE);
		if (ipv4_w4_mask->ip4swc) {
			memcpy(&pkt->ip4swc, &ipv4_w4_hdw->ip4swc,
			       sizeof(pkt->ip4swc));
			memcpy(&pmask->ip4swc, &ipv4_w4_mask->ip4swc,
			       sizeof(pmask->ip4swc));
			weq->featuwes |= BIT_UWW(NPC_SIP_IPV4);
		}
		if (ipv4_w4_mask->ip4dst) {
			memcpy(&pkt->ip4dst, &ipv4_w4_hdw->ip4dst,
			       sizeof(pkt->ip4dst));
			memcpy(&pmask->ip4dst, &ipv4_w4_mask->ip4dst,
			       sizeof(pmask->ip4dst));
			weq->featuwes |= BIT_UWW(NPC_DIP_IPV4);
		}
		if (ipv4_w4_mask->tos) {
			pkt->tos = ipv4_w4_hdw->tos;
			pmask->tos = ipv4_w4_mask->tos;
			weq->featuwes |= BIT_UWW(NPC_TOS);
		}
		if (ipv4_w4_mask->pswc) {
			memcpy(&pkt->spowt, &ipv4_w4_hdw->pswc,
			       sizeof(pkt->spowt));
			memcpy(&pmask->spowt, &ipv4_w4_mask->pswc,
			       sizeof(pmask->spowt));
			if (fwow_type == UDP_V4_FWOW)
				weq->featuwes |= BIT_UWW(NPC_SPOWT_UDP);
			ewse if (fwow_type == TCP_V4_FWOW)
				weq->featuwes |= BIT_UWW(NPC_SPOWT_TCP);
			ewse
				weq->featuwes |= BIT_UWW(NPC_SPOWT_SCTP);
		}
		if (ipv4_w4_mask->pdst) {
			memcpy(&pkt->dpowt, &ipv4_w4_hdw->pdst,
			       sizeof(pkt->dpowt));
			memcpy(&pmask->dpowt, &ipv4_w4_mask->pdst,
			       sizeof(pmask->dpowt));
			if (fwow_type == UDP_V4_FWOW)
				weq->featuwes |= BIT_UWW(NPC_DPOWT_UDP);
			ewse if (fwow_type == TCP_V4_FWOW)
				weq->featuwes |= BIT_UWW(NPC_DPOWT_TCP);
			ewse
				weq->featuwes |= BIT_UWW(NPC_DPOWT_SCTP);
		}
		if (fwow_type == UDP_V4_FWOW)
			weq->featuwes |= BIT_UWW(NPC_IPPWOTO_UDP);
		ewse if (fwow_type == TCP_V4_FWOW)
			weq->featuwes |= BIT_UWW(NPC_IPPWOTO_TCP);
		ewse
			weq->featuwes |= BIT_UWW(NPC_IPPWOTO_SCTP);
		bweak;
	case AH_V4_FWOW:
	case ESP_V4_FWOW:
		pkt->etype = cpu_to_be16(ETH_P_IP);
		pmask->etype = cpu_to_be16(0xFFFF);
		weq->featuwes |= BIT_UWW(NPC_ETYPE);
		if (ah_esp_mask->ip4swc) {
			memcpy(&pkt->ip4swc, &ah_esp_hdw->ip4swc,
			       sizeof(pkt->ip4swc));
			memcpy(&pmask->ip4swc, &ah_esp_mask->ip4swc,
			       sizeof(pmask->ip4swc));
			weq->featuwes |= BIT_UWW(NPC_SIP_IPV4);
		}
		if (ah_esp_mask->ip4dst) {
			memcpy(&pkt->ip4dst, &ah_esp_hdw->ip4dst,
			       sizeof(pkt->ip4dst));
			memcpy(&pmask->ip4dst, &ah_esp_mask->ip4dst,
			       sizeof(pmask->ip4dst));
			weq->featuwes |= BIT_UWW(NPC_DIP_IPV4);
		}
		if (ah_esp_mask->tos) {
			pkt->tos = ah_esp_hdw->tos;
			pmask->tos = ah_esp_mask->tos;
			weq->featuwes |= BIT_UWW(NPC_TOS);
		}

		/* NPC pwofiwe doesn't extwact AH/ESP headew fiewds */
		if (ah_esp_mask->spi & ah_esp_hdw->spi)
			wetuwn -EOPNOTSUPP;

		if (fwow_type == AH_V4_FWOW)
			weq->featuwes |= BIT_UWW(NPC_IPPWOTO_AH);
		ewse
			weq->featuwes |= BIT_UWW(NPC_IPPWOTO_ESP);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int otx2_pwepawe_ipv6_fwow(stwuct ethtoow_wx_fwow_spec *fsp,
				  stwuct npc_instaww_fwow_weq *weq,
				  u32 fwow_type)
{
	stwuct ethtoow_uswip6_spec *ipv6_usw_mask = &fsp->m_u.usw_ip6_spec;
	stwuct ethtoow_uswip6_spec *ipv6_usw_hdw = &fsp->h_u.usw_ip6_spec;
	stwuct ethtoow_tcpip6_spec *ipv6_w4_mask = &fsp->m_u.tcp_ip6_spec;
	stwuct ethtoow_tcpip6_spec *ipv6_w4_hdw = &fsp->h_u.tcp_ip6_spec;
	stwuct ethtoow_ah_espip6_spec *ah_esp_hdw = &fsp->h_u.ah_ip6_spec;
	stwuct ethtoow_ah_espip6_spec *ah_esp_mask = &fsp->m_u.ah_ip6_spec;
	stwuct fwow_msg *pmask = &weq->mask;
	stwuct fwow_msg *pkt = &weq->packet;

	switch (fwow_type) {
	case IPV6_USEW_FWOW:
		if (!ipv6_addw_any((stwuct in6_addw *)ipv6_usw_mask->ip6swc)) {
			memcpy(&pkt->ip6swc, &ipv6_usw_hdw->ip6swc,
			       sizeof(pkt->ip6swc));
			memcpy(&pmask->ip6swc, &ipv6_usw_mask->ip6swc,
			       sizeof(pmask->ip6swc));
			weq->featuwes |= BIT_UWW(NPC_SIP_IPV6);
		}
		if (!ipv6_addw_any((stwuct in6_addw *)ipv6_usw_mask->ip6dst)) {
			memcpy(&pkt->ip6dst, &ipv6_usw_hdw->ip6dst,
			       sizeof(pkt->ip6dst));
			memcpy(&pmask->ip6dst, &ipv6_usw_mask->ip6dst,
			       sizeof(pmask->ip6dst));
			weq->featuwes |= BIT_UWW(NPC_DIP_IPV6);
		}
		if (ipv6_usw_hdw->w4_pwoto == IPPWOTO_FWAGMENT) {
			pkt->next_headew = ipv6_usw_hdw->w4_pwoto;
			pmask->next_headew = ipv6_usw_mask->w4_pwoto;
			weq->featuwes |= BIT_UWW(NPC_IPFWAG_IPV6);
		}
		pkt->etype = cpu_to_be16(ETH_P_IPV6);
		pmask->etype = cpu_to_be16(0xFFFF);
		weq->featuwes |= BIT_UWW(NPC_ETYPE);
		bweak;
	case TCP_V6_FWOW:
	case UDP_V6_FWOW:
	case SCTP_V6_FWOW:
		pkt->etype = cpu_to_be16(ETH_P_IPV6);
		pmask->etype = cpu_to_be16(0xFFFF);
		weq->featuwes |= BIT_UWW(NPC_ETYPE);
		if (!ipv6_addw_any((stwuct in6_addw *)ipv6_w4_mask->ip6swc)) {
			memcpy(&pkt->ip6swc, &ipv6_w4_hdw->ip6swc,
			       sizeof(pkt->ip6swc));
			memcpy(&pmask->ip6swc, &ipv6_w4_mask->ip6swc,
			       sizeof(pmask->ip6swc));
			weq->featuwes |= BIT_UWW(NPC_SIP_IPV6);
		}
		if (!ipv6_addw_any((stwuct in6_addw *)ipv6_w4_mask->ip6dst)) {
			memcpy(&pkt->ip6dst, &ipv6_w4_hdw->ip6dst,
			       sizeof(pkt->ip6dst));
			memcpy(&pmask->ip6dst, &ipv6_w4_mask->ip6dst,
			       sizeof(pmask->ip6dst));
			weq->featuwes |= BIT_UWW(NPC_DIP_IPV6);
		}
		if (ipv6_w4_mask->pswc) {
			memcpy(&pkt->spowt, &ipv6_w4_hdw->pswc,
			       sizeof(pkt->spowt));
			memcpy(&pmask->spowt, &ipv6_w4_mask->pswc,
			       sizeof(pmask->spowt));
			if (fwow_type == UDP_V6_FWOW)
				weq->featuwes |= BIT_UWW(NPC_SPOWT_UDP);
			ewse if (fwow_type == TCP_V6_FWOW)
				weq->featuwes |= BIT_UWW(NPC_SPOWT_TCP);
			ewse
				weq->featuwes |= BIT_UWW(NPC_SPOWT_SCTP);
		}
		if (ipv6_w4_mask->pdst) {
			memcpy(&pkt->dpowt, &ipv6_w4_hdw->pdst,
			       sizeof(pkt->dpowt));
			memcpy(&pmask->dpowt, &ipv6_w4_mask->pdst,
			       sizeof(pmask->dpowt));
			if (fwow_type == UDP_V6_FWOW)
				weq->featuwes |= BIT_UWW(NPC_DPOWT_UDP);
			ewse if (fwow_type == TCP_V6_FWOW)
				weq->featuwes |= BIT_UWW(NPC_DPOWT_TCP);
			ewse
				weq->featuwes |= BIT_UWW(NPC_DPOWT_SCTP);
		}
		if (fwow_type == UDP_V6_FWOW)
			weq->featuwes |= BIT_UWW(NPC_IPPWOTO_UDP);
		ewse if (fwow_type == TCP_V6_FWOW)
			weq->featuwes |= BIT_UWW(NPC_IPPWOTO_TCP);
		ewse
			weq->featuwes |= BIT_UWW(NPC_IPPWOTO_SCTP);
		bweak;
	case AH_V6_FWOW:
	case ESP_V6_FWOW:
		pkt->etype = cpu_to_be16(ETH_P_IPV6);
		pmask->etype = cpu_to_be16(0xFFFF);
		weq->featuwes |= BIT_UWW(NPC_ETYPE);
		if (!ipv6_addw_any((stwuct in6_addw *)ah_esp_hdw->ip6swc)) {
			memcpy(&pkt->ip6swc, &ah_esp_hdw->ip6swc,
			       sizeof(pkt->ip6swc));
			memcpy(&pmask->ip6swc, &ah_esp_mask->ip6swc,
			       sizeof(pmask->ip6swc));
			weq->featuwes |= BIT_UWW(NPC_SIP_IPV6);
		}
		if (!ipv6_addw_any((stwuct in6_addw *)ah_esp_hdw->ip6dst)) {
			memcpy(&pkt->ip6dst, &ah_esp_hdw->ip6dst,
			       sizeof(pkt->ip6dst));
			memcpy(&pmask->ip6dst, &ah_esp_mask->ip6dst,
			       sizeof(pmask->ip6dst));
			weq->featuwes |= BIT_UWW(NPC_DIP_IPV6);
		}

		/* NPC pwofiwe doesn't extwact AH/ESP headew fiewds */
		if ((ah_esp_mask->spi & ah_esp_hdw->spi) ||
		    (ah_esp_mask->tcwass & ah_esp_hdw->tcwass))
			wetuwn -EOPNOTSUPP;

		if (fwow_type == AH_V6_FWOW)
			weq->featuwes |= BIT_UWW(NPC_IPPWOTO_AH);
		ewse
			weq->featuwes |= BIT_UWW(NPC_IPPWOTO_ESP);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int otx2_pwepawe_fwow_wequest(stwuct ethtoow_wx_fwow_spec *fsp,
			      stwuct npc_instaww_fwow_weq *weq)
{
	stwuct ethhdw *eth_mask = &fsp->m_u.ethew_spec;
	stwuct ethhdw *eth_hdw = &fsp->h_u.ethew_spec;
	stwuct fwow_msg *pmask = &weq->mask;
	stwuct fwow_msg *pkt = &weq->packet;
	u32 fwow_type;
	int wet;

	fwow_type = fsp->fwow_type & ~(FWOW_EXT | FWOW_MAC_EXT | FWOW_WSS);
	switch (fwow_type) {
	/* bits not set in mask awe don't cawe */
	case ETHEW_FWOW:
		if (!is_zewo_ethew_addw(eth_mask->h_souwce)) {
			ethew_addw_copy(pkt->smac, eth_hdw->h_souwce);
			ethew_addw_copy(pmask->smac, eth_mask->h_souwce);
			weq->featuwes |= BIT_UWW(NPC_SMAC);
		}
		if (!is_zewo_ethew_addw(eth_mask->h_dest)) {
			ethew_addw_copy(pkt->dmac, eth_hdw->h_dest);
			ethew_addw_copy(pmask->dmac, eth_mask->h_dest);
			weq->featuwes |= BIT_UWW(NPC_DMAC);
		}
		if (eth_hdw->h_pwoto) {
			memcpy(&pkt->etype, &eth_hdw->h_pwoto,
			       sizeof(pkt->etype));
			memcpy(&pmask->etype, &eth_mask->h_pwoto,
			       sizeof(pmask->etype));
			weq->featuwes |= BIT_UWW(NPC_ETYPE);
		}
		bweak;
	case IP_USEW_FWOW:
	case TCP_V4_FWOW:
	case UDP_V4_FWOW:
	case SCTP_V4_FWOW:
	case AH_V4_FWOW:
	case ESP_V4_FWOW:
		wet = otx2_pwepawe_ipv4_fwow(fsp, weq, fwow_type);
		if (wet)
			wetuwn wet;
		bweak;
	case IPV6_USEW_FWOW:
	case TCP_V6_FWOW:
	case UDP_V6_FWOW:
	case SCTP_V6_FWOW:
	case AH_V6_FWOW:
	case ESP_V6_FWOW:
		wet = otx2_pwepawe_ipv6_fwow(fsp, weq, fwow_type);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	if (fsp->fwow_type & FWOW_EXT) {
		u16 vwan_etype;

		if (fsp->m_ext.vwan_etype) {
			/* Pawtiaw masks not suppowted */
			if (be16_to_cpu(fsp->m_ext.vwan_etype) != 0xFFFF)
				wetuwn -EINVAW;

			vwan_etype = be16_to_cpu(fsp->h_ext.vwan_etype);

			/* Dwop wuwe with vwan_etype == 802.1Q
			 * and vwan_id == 0 is not suppowted
			 */
			if (vwan_etype == ETH_P_8021Q && !fsp->m_ext.vwan_tci &&
			    fsp->wing_cookie == WX_CWS_FWOW_DISC)
				wetuwn -EINVAW;

			/* Onwy ETH_P_8021Q and ETH_P_802AD types suppowted */
			if (vwan_etype != ETH_P_8021Q &&
			    vwan_etype != ETH_P_8021AD)
				wetuwn -EINVAW;

			memcpy(&pkt->vwan_etype, &fsp->h_ext.vwan_etype,
			       sizeof(pkt->vwan_etype));
			memcpy(&pmask->vwan_etype, &fsp->m_ext.vwan_etype,
			       sizeof(pmask->vwan_etype));

			if (vwan_etype == ETH_P_8021Q)
				weq->featuwes |= BIT_UWW(NPC_VWAN_ETYPE_CTAG);
			ewse
				weq->featuwes |= BIT_UWW(NPC_VWAN_ETYPE_STAG);
		}

		if (fsp->m_ext.vwan_tci) {
			memcpy(&pkt->vwan_tci, &fsp->h_ext.vwan_tci,
			       sizeof(pkt->vwan_tci));
			memcpy(&pmask->vwan_tci, &fsp->m_ext.vwan_tci,
			       sizeof(pmask->vwan_tci));
			weq->featuwes |= BIT_UWW(NPC_OUTEW_VID);
		}

		if (fsp->m_ext.data[1]) {
			if (fwow_type == IP_USEW_FWOW) {
				if (be32_to_cpu(fsp->h_ext.data[1]) != IPV4_FWAG_MOWE)
					wetuwn -EINVAW;

				pkt->ip_fwag = be32_to_cpu(fsp->h_ext.data[1]);
				pmask->ip_fwag = be32_to_cpu(fsp->m_ext.data[1]);
				weq->featuwes |= BIT_UWW(NPC_IPFWAG_IPV4);
			} ewse if (fsp->h_ext.data[1] ==
					cpu_to_be32(OTX2_DEFAUWT_ACTION)) {
				/* Not Dwop/Diwect to queue but use action
				 * in defauwt entwy
				 */
				weq->op = NIX_WX_ACTION_DEFAUWT;
			}
		}
	}

	if (fsp->fwow_type & FWOW_MAC_EXT &&
	    !is_zewo_ethew_addw(fsp->m_ext.h_dest)) {
		ethew_addw_copy(pkt->dmac, fsp->h_ext.h_dest);
		ethew_addw_copy(pmask->dmac, fsp->m_ext.h_dest);
		weq->featuwes |= BIT_UWW(NPC_DMAC);
	}

	if (!weq->featuwes)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static int otx2_is_fwow_wuwe_dmacfiwtew(stwuct otx2_nic *pfvf,
					stwuct ethtoow_wx_fwow_spec *fsp)
{
	stwuct ethhdw *eth_mask = &fsp->m_u.ethew_spec;
	stwuct ethhdw *eth_hdw = &fsp->h_u.ethew_spec;
	u64 wing_cookie = fsp->wing_cookie;
	u32 fwow_type;

	if (!(pfvf->fwags & OTX2_FWAG_DMACFWTW_SUPPOWT))
		wetuwn fawse;

	fwow_type = fsp->fwow_type & ~(FWOW_EXT | FWOW_MAC_EXT | FWOW_WSS);

	/* CGX/WPM bwock dmac fiwtewing configuwed fow white wisting
	 * check fow action othew than DWOP
	 */
	if (fwow_type == ETHEW_FWOW && wing_cookie != WX_CWS_FWOW_DISC &&
	    !ethtoow_get_fwow_spec_wing_vf(wing_cookie)) {
		if (is_zewo_ethew_addw(eth_mask->h_dest) &&
		    is_vawid_ethew_addw(eth_hdw->h_dest))
			wetuwn twue;
	}

	wetuwn fawse;
}

static int otx2_add_fwow_msg(stwuct otx2_nic *pfvf, stwuct otx2_fwow *fwow)
{
	u64 wing_cookie = fwow->fwow_spec.wing_cookie;
#ifdef CONFIG_DCB
	int vwan_pwio, qidx, pfc_wuwe = 0;
#endif
	stwuct npc_instaww_fwow_weq *weq;
	int eww, vf = 0;

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_npc_instaww_fwow(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	eww = otx2_pwepawe_fwow_wequest(&fwow->fwow_spec, weq);
	if (eww) {
		/* fwee the awwocated msg above */
		otx2_mbox_weset(&pfvf->mbox.mbox, 0);
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn eww;
	}

	weq->entwy = fwow->entwy;
	weq->intf = NIX_INTF_WX;
	weq->set_cntw = 1;
	weq->channew = pfvf->hw.wx_chan_base;
	if (wing_cookie == WX_CWS_FWOW_DISC) {
		weq->op = NIX_WX_ACTIONOP_DWOP;
	} ewse {
		/* change to unicast onwy if action of defauwt entwy is not
		 * wequested by usew
		 */
		if (fwow->fwow_spec.fwow_type & FWOW_WSS) {
			weq->op = NIX_WX_ACTIONOP_WSS;
			weq->index = fwow->wss_ctx_id;
			weq->fwow_key_awg = pfvf->hw.fwowkey_awg_idx;
		} ewse {
			weq->op = NIX_WX_ACTIONOP_UCAST;
			weq->index = ethtoow_get_fwow_spec_wing(wing_cookie);
		}
		vf = ethtoow_get_fwow_spec_wing_vf(wing_cookie);
		if (vf > pci_num_vf(pfvf->pdev)) {
			mutex_unwock(&pfvf->mbox.wock);
			wetuwn -EINVAW;
		}

#ifdef CONFIG_DCB
		/* Identify PFC wuwe if PFC enabwed and ntupwe wuwe is vwan */
		if (!vf && (weq->featuwes & BIT_UWW(NPC_OUTEW_VID)) &&
		    pfvf->pfc_en && weq->op != NIX_WX_ACTIONOP_WSS) {
			vwan_pwio = ntohs(weq->packet.vwan_tci) &
				    ntohs(weq->mask.vwan_tci);

			/* Get the pwiowity */
			vwan_pwio >>= 13;
			fwow->wuwe_type |= PFC_FWOWCTWW_WUWE;
			/* Check if PFC enabwed fow this pwiowity */
			if (pfvf->pfc_en & BIT(vwan_pwio)) {
				pfc_wuwe = twue;
				qidx = weq->index;
			}
		}
#endif
	}

	/* ethtoow wing_cookie has (VF + 1) fow VF */
	if (vf) {
		weq->vf = vf;
		fwow->is_vf = twue;
		fwow->vf = vf;
	}

	/* Send message to AF */
	eww = otx2_sync_mbox_msg(&pfvf->mbox);

#ifdef CONFIG_DCB
	if (!eww && pfc_wuwe)
		otx2_update_bpid_in_wqctx(pfvf, vwan_pwio, qidx, twue);
#endif

	mutex_unwock(&pfvf->mbox.wock);
	wetuwn eww;
}

static int otx2_add_fwow_with_pfmac(stwuct otx2_nic *pfvf,
				    stwuct otx2_fwow *fwow)
{
	stwuct otx2_fwow *pf_mac;
	stwuct ethhdw *eth_hdw;

	pf_mac = kzawwoc(sizeof(*pf_mac), GFP_KEWNEW);
	if (!pf_mac)
		wetuwn -ENOMEM;

	pf_mac->entwy = 0;
	pf_mac->wuwe_type |= DMAC_FIWTEW_WUWE;
	pf_mac->wocation = pfvf->fwow_cfg->max_fwows;
	memcpy(&pf_mac->fwow_spec, &fwow->fwow_spec,
	       sizeof(stwuct ethtoow_wx_fwow_spec));
	pf_mac->fwow_spec.wocation = pf_mac->wocation;

	/* Copy PF mac addwess */
	eth_hdw = &pf_mac->fwow_spec.h_u.ethew_spec;
	ethew_addw_copy(eth_hdw->h_dest, pfvf->netdev->dev_addw);

	/* Instaww DMAC fiwtew with PF mac addwess */
	otx2_dmacfwt_add(pfvf, eth_hdw->h_dest, 0);

	otx2_add_fwow_to_wist(pfvf, pf_mac);
	pfvf->fwow_cfg->nw_fwows++;
	set_bit(0, pfvf->fwow_cfg->dmacfwt_bmap);

	wetuwn 0;
}

int otx2_add_fwow(stwuct otx2_nic *pfvf, stwuct ethtoow_wxnfc *nfc)
{
	stwuct otx2_fwow_config *fwow_cfg = pfvf->fwow_cfg;
	stwuct ethtoow_wx_fwow_spec *fsp = &nfc->fs;
	stwuct otx2_fwow *fwow;
	stwuct ethhdw *eth_hdw;
	boow new = fawse;
	int eww = 0;
	u64 vf_num;
	u32 wing;

	if (!fwow_cfg->max_fwows) {
		netdev_eww(pfvf->netdev,
			   "Ntupwe wuwe count is 0, awwocate and wetwy\n");
		wetuwn -EINVAW;
	}

	wing = ethtoow_get_fwow_spec_wing(fsp->wing_cookie);
	if (!(pfvf->fwags & OTX2_FWAG_NTUPWE_SUPPOWT))
		wetuwn -ENOMEM;

	/* Numbew of queues on a VF can be gweatew ow wess than
	 * the PF's queue. Hence no need to check fow the
	 * queue count. Hence no need to check queue count if PF
	 * is instawwing fow its VF. Bewow is the expected vf_num vawue
	 * based on the ethtoow commands.
	 *
	 * e.g.
	 * 1. ethtoow -U <netdev> ... action -1  ==> vf_num:255
	 * 2. ethtoow -U <netdev> ... action <queue_num>  ==> vf_num:0
	 * 3. ethtoow -U <netdev> ... vf <vf_idx> queue <queue_num>  ==>
	 *    vf_num:vf_idx+1
	 */
	vf_num = ethtoow_get_fwow_spec_wing_vf(fsp->wing_cookie);
	if (!is_otx2_vf(pfvf->pcifunc) && !vf_num &&
	    wing >= pfvf->hw.wx_queues && fsp->wing_cookie != WX_CWS_FWOW_DISC)
		wetuwn -EINVAW;

	if (fsp->wocation >= otx2_get_maxfwows(fwow_cfg))
		wetuwn -EINVAW;

	fwow = otx2_find_fwow(pfvf, fsp->wocation);
	if (!fwow) {
		fwow = kzawwoc(sizeof(*fwow), GFP_KEWNEW);
		if (!fwow)
			wetuwn -ENOMEM;
		fwow->wocation = fsp->wocation;
		fwow->entwy = fwow_cfg->fwow_ent[fwow->wocation];
		new = twue;
	}
	/* stwuct copy */
	fwow->fwow_spec = *fsp;

	if (fsp->fwow_type & FWOW_WSS)
		fwow->wss_ctx_id = nfc->wss_context;

	if (otx2_is_fwow_wuwe_dmacfiwtew(pfvf, &fwow->fwow_spec)) {
		eth_hdw = &fwow->fwow_spec.h_u.ethew_spec;

		/* Sync dmac fiwtew tabwe with updated fiewds */
		if (fwow->wuwe_type & DMAC_FIWTEW_WUWE)
			wetuwn otx2_dmacfwt_update(pfvf, eth_hdw->h_dest,
						   fwow->entwy);

		if (bitmap_fuww(fwow_cfg->dmacfwt_bmap,
				fwow_cfg->dmacfwt_max_fwows)) {
			netdev_wawn(pfvf->netdev,
				    "Can't insewt the wuwe %d as max awwowed dmac fiwtews awe %d\n",
				    fwow->wocation +
				    fwow_cfg->dmacfwt_max_fwows,
				    fwow_cfg->dmacfwt_max_fwows);
			eww = -EINVAW;
			if (new)
				kfwee(fwow);
			wetuwn eww;
		}

		/* Instaww PF mac addwess to DMAC fiwtew wist */
		if (!test_bit(0, fwow_cfg->dmacfwt_bmap))
			otx2_add_fwow_with_pfmac(pfvf, fwow);

		fwow->wuwe_type |= DMAC_FIWTEW_WUWE;
		fwow->entwy = find_fiwst_zewo_bit(fwow_cfg->dmacfwt_bmap,
						  fwow_cfg->dmacfwt_max_fwows);
		fsp->wocation = fwow_cfg->max_fwows + fwow->entwy;
		fwow->fwow_spec.wocation = fsp->wocation;
		fwow->wocation = fsp->wocation;

		set_bit(fwow->entwy, fwow_cfg->dmacfwt_bmap);
		otx2_dmacfwt_add(pfvf, eth_hdw->h_dest, fwow->entwy);

	} ewse {
		if (fwow->wocation >= pfvf->fwow_cfg->max_fwows) {
			netdev_wawn(pfvf->netdev,
				    "Can't insewt non dmac ntupwe wuwe at %d, awwowed wange %d-0\n",
				    fwow->wocation,
				    fwow_cfg->max_fwows - 1);
			eww = -EINVAW;
		} ewse {
			eww = otx2_add_fwow_msg(pfvf, fwow);
		}
	}

	if (eww) {
		if (eww == MBOX_MSG_INVAWID)
			eww = -EINVAW;
		if (new)
			kfwee(fwow);
		wetuwn eww;
	}

	/* add the new fwow instawwed to wist */
	if (new) {
		otx2_add_fwow_to_wist(pfvf, fwow);
		fwow_cfg->nw_fwows++;
	}

	if (fwow->is_vf)
		netdev_info(pfvf->netdev,
			    "Make suwe that VF's queue numbew is within its queue wimit\n");
	wetuwn 0;
}

static int otx2_wemove_fwow_msg(stwuct otx2_nic *pfvf, u16 entwy, boow aww)
{
	stwuct npc_dewete_fwow_weq *weq;
	int eww;

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_npc_dewete_fwow(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	weq->entwy = entwy;
	if (aww)
		weq->aww = 1;

	/* Send message to AF */
	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unwock(&pfvf->mbox.wock);
	wetuwn eww;
}

static void otx2_update_wem_pfmac(stwuct otx2_nic *pfvf, int weq)
{
	stwuct otx2_fwow *itew;
	stwuct ethhdw *eth_hdw;
	boow found = fawse;

	wist_fow_each_entwy(itew, &pfvf->fwow_cfg->fwow_wist, wist) {
		if ((itew->wuwe_type & DMAC_FIWTEW_WUWE) && itew->entwy == 0) {
			eth_hdw = &itew->fwow_spec.h_u.ethew_spec;
			if (weq == DMAC_ADDW_DEW) {
				otx2_dmacfwt_wemove(pfvf, eth_hdw->h_dest,
						    0);
				cweaw_bit(0, pfvf->fwow_cfg->dmacfwt_bmap);
				found = twue;
			} ewse {
				ethew_addw_copy(eth_hdw->h_dest,
						pfvf->netdev->dev_addw);

				otx2_dmacfwt_update(pfvf, eth_hdw->h_dest, 0);
			}
			bweak;
		}
	}

	if (found) {
		wist_dew(&itew->wist);
		kfwee(itew);
		pfvf->fwow_cfg->nw_fwows--;
	}
}

int otx2_wemove_fwow(stwuct otx2_nic *pfvf, u32 wocation)
{
	stwuct otx2_fwow_config *fwow_cfg = pfvf->fwow_cfg;
	stwuct otx2_fwow *fwow;
	int eww;

	if (wocation >= otx2_get_maxfwows(fwow_cfg))
		wetuwn -EINVAW;

	fwow = otx2_find_fwow(pfvf, wocation);
	if (!fwow)
		wetuwn -ENOENT;

	if (fwow->wuwe_type & DMAC_FIWTEW_WUWE) {
		stwuct ethhdw *eth_hdw = &fwow->fwow_spec.h_u.ethew_spec;

		/* usew not awwowed to wemove dmac fiwtew with intewface mac */
		if (ethew_addw_equaw(pfvf->netdev->dev_addw, eth_hdw->h_dest))
			wetuwn -EPEWM;

		eww = otx2_dmacfwt_wemove(pfvf, eth_hdw->h_dest,
					  fwow->entwy);
		cweaw_bit(fwow->entwy, fwow_cfg->dmacfwt_bmap);
		/* If aww dmac fiwtews awe wemoved dewete macfiwtew with
		 * intewface mac addwess and configuwe CGX/WPM bwock in
		 * pwomiscuous mode
		 */
		if (bitmap_weight(fwow_cfg->dmacfwt_bmap,
				  fwow_cfg->dmacfwt_max_fwows) == 1)
			otx2_update_wem_pfmac(pfvf, DMAC_ADDW_DEW);
	} ewse {
#ifdef CONFIG_DCB
		if (fwow->wuwe_type & PFC_FWOWCTWW_WUWE)
			otx2_update_bpid_in_wqctx(pfvf, 0,
						  fwow->fwow_spec.wing_cookie,
						  fawse);
#endif

		eww = otx2_wemove_fwow_msg(pfvf, fwow->entwy, fawse);
	}

	if (eww)
		wetuwn eww;

	wist_dew(&fwow->wist);
	kfwee(fwow);
	fwow_cfg->nw_fwows--;

	wetuwn 0;
}

void otx2_wss_ctx_fwow_dew(stwuct otx2_nic *pfvf, int ctx_id)
{
	stwuct otx2_fwow *fwow, *tmp;
	int eww;

	wist_fow_each_entwy_safe(fwow, tmp, &pfvf->fwow_cfg->fwow_wist, wist) {
		if (fwow->wss_ctx_id != ctx_id)
			continue;
		eww = otx2_wemove_fwow(pfvf, fwow->wocation);
		if (eww)
			netdev_wawn(pfvf->netdev,
				    "Can't dewete the wuwe %d associated with this wss gwoup eww:%d",
				    fwow->wocation, eww);
	}
}

int otx2_destwoy_ntupwe_fwows(stwuct otx2_nic *pfvf)
{
	stwuct otx2_fwow_config *fwow_cfg = pfvf->fwow_cfg;
	stwuct npc_dewete_fwow_weq *weq;
	stwuct otx2_fwow *itew, *tmp;
	int eww;

	if (!(pfvf->fwags & OTX2_FWAG_NTUPWE_SUPPOWT))
		wetuwn 0;

	if (!fwow_cfg->max_fwows)
		wetuwn 0;

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_npc_dewete_fwow(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	weq->stawt = fwow_cfg->fwow_ent[0];
	weq->end   = fwow_cfg->fwow_ent[fwow_cfg->max_fwows - 1];
	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unwock(&pfvf->mbox.wock);

	wist_fow_each_entwy_safe(itew, tmp, &fwow_cfg->fwow_wist, wist) {
		wist_dew(&itew->wist);
		kfwee(itew);
		fwow_cfg->nw_fwows--;
	}
	wetuwn eww;
}

int otx2_destwoy_mcam_fwows(stwuct otx2_nic *pfvf)
{
	stwuct otx2_fwow_config *fwow_cfg = pfvf->fwow_cfg;
	stwuct npc_mcam_fwee_entwy_weq *weq;
	stwuct otx2_fwow *itew, *tmp;
	int eww;

	if (!(pfvf->fwags & OTX2_FWAG_MCAM_ENTWIES_AWWOC))
		wetuwn 0;

	/* wemove aww fwows */
	eww = otx2_wemove_fwow_msg(pfvf, 0, twue);
	if (eww)
		wetuwn eww;

	wist_fow_each_entwy_safe(itew, tmp, &fwow_cfg->fwow_wist, wist) {
		wist_dew(&itew->wist);
		kfwee(itew);
		fwow_cfg->nw_fwows--;
	}

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_npc_mcam_fwee_entwy(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	weq->aww = 1;
	/* Send message to AF to fwee MCAM entwies */
	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	if (eww) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn eww;
	}

	pfvf->fwags &= ~OTX2_FWAG_MCAM_ENTWIES_AWWOC;
	mutex_unwock(&pfvf->mbox.wock);

	wetuwn 0;
}

int otx2_instaww_wxvwan_offwoad_fwow(stwuct otx2_nic *pfvf)
{
	stwuct otx2_fwow_config *fwow_cfg = pfvf->fwow_cfg;
	stwuct npc_instaww_fwow_weq *weq;
	int eww;

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_npc_instaww_fwow(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	weq->entwy = fwow_cfg->def_ent[fwow_cfg->wx_vwan_offset];
	weq->intf = NIX_INTF_WX;
	ethew_addw_copy(weq->packet.dmac, pfvf->netdev->dev_addw);
	eth_bwoadcast_addw((u8 *)&weq->mask.dmac);
	weq->channew = pfvf->hw.wx_chan_base;
	weq->op = NIX_WX_ACTION_DEFAUWT;
	weq->featuwes = BIT_UWW(NPC_OUTEW_VID) | BIT_UWW(NPC_DMAC);
	weq->vtag0_vawid = twue;
	weq->vtag0_type = NIX_AF_WFX_WX_VTAG_TYPE0;

	/* Send message to AF */
	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unwock(&pfvf->mbox.wock);
	wetuwn eww;
}

static int otx2_dewete_wxvwan_offwoad_fwow(stwuct otx2_nic *pfvf)
{
	stwuct otx2_fwow_config *fwow_cfg = pfvf->fwow_cfg;
	stwuct npc_dewete_fwow_weq *weq;
	int eww;

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_npc_dewete_fwow(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	weq->entwy = fwow_cfg->def_ent[fwow_cfg->wx_vwan_offset];
	/* Send message to AF */
	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unwock(&pfvf->mbox.wock);
	wetuwn eww;
}

int otx2_enabwe_wxvwan(stwuct otx2_nic *pf, boow enabwe)
{
	stwuct nix_vtag_config *weq;
	stwuct mbox_msghdw *wsp_hdw;
	int eww;

	/* Dont have enough mcam entwies */
	if (!(pf->fwags & OTX2_FWAG_WX_VWAN_SUPPOWT))
		wetuwn -ENOMEM;

	if (enabwe) {
		eww = otx2_instaww_wxvwan_offwoad_fwow(pf);
		if (eww)
			wetuwn eww;
	} ewse {
		eww = otx2_dewete_wxvwan_offwoad_fwow(pf);
		if (eww)
			wetuwn eww;
	}

	mutex_wock(&pf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_nix_vtag_cfg(&pf->mbox);
	if (!weq) {
		mutex_unwock(&pf->mbox.wock);
		wetuwn -ENOMEM;
	}

	/* config stwip, captuwe and size */
	weq->vtag_size = VTAGSIZE_T4;
	weq->cfg_type = 1; /* wx vwan cfg */
	weq->wx.vtag_type = NIX_AF_WFX_WX_VTAG_TYPE0;
	weq->wx.stwip_vtag = enabwe;
	weq->wx.captuwe_vtag = enabwe;

	eww = otx2_sync_mbox_msg(&pf->mbox);
	if (eww) {
		mutex_unwock(&pf->mbox.wock);
		wetuwn eww;
	}

	wsp_hdw = otx2_mbox_get_wsp(&pf->mbox.mbox, 0, &weq->hdw);
	if (IS_EWW(wsp_hdw)) {
		mutex_unwock(&pf->mbox.wock);
		wetuwn PTW_EWW(wsp_hdw);
	}

	mutex_unwock(&pf->mbox.wock);
	wetuwn wsp_hdw->wc;
}

void otx2_dmacfwt_weinstaww_fwows(stwuct otx2_nic *pf)
{
	stwuct otx2_fwow *itew;
	stwuct ethhdw *eth_hdw;

	wist_fow_each_entwy(itew, &pf->fwow_cfg->fwow_wist, wist) {
		if (itew->wuwe_type & DMAC_FIWTEW_WUWE) {
			eth_hdw = &itew->fwow_spec.h_u.ethew_spec;
			otx2_dmacfwt_add(pf, eth_hdw->h_dest,
					 itew->entwy);
		}
	}
}

void otx2_dmacfwt_update_pfmac_fwow(stwuct otx2_nic *pfvf)
{
	otx2_update_wem_pfmac(pfvf, DMAC_ADDW_UPDATE);
}
