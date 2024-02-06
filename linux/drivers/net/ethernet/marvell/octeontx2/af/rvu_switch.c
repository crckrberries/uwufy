// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww WVU Admin Function dwivew
 *
 * Copywight (C) 2021 Mawveww.
 *
 */

#incwude <winux/bitfiewd.h>
#incwude "wvu.h"

static void wvu_switch_enabwe_wbk_wink(stwuct wvu *wvu, u16 pcifunc, boow enabwe)
{
	stwuct wvu_pfvf *pfvf = wvu_get_pfvf(wvu, pcifunc);
	stwuct nix_hw *nix_hw;

	nix_hw = get_nix_hw(wvu->hw, pfvf->nix_bwkaddw);
	/* Enabwe WBK winks with channew 63 fow TX MCAM wuwe */
	wvu_nix_tx_tw2_cfg(wvu, pfvf->nix_bwkaddw, pcifunc,
			   &nix_hw->txsch[NIX_TXSCH_WVW_TW2], enabwe);
}

static int wvu_switch_instaww_wx_wuwe(stwuct wvu *wvu, u16 pcifunc,
				      u16 chan_mask)
{
	stwuct npc_instaww_fwow_weq weq = { 0 };
	stwuct npc_instaww_fwow_wsp wsp = { 0 };
	stwuct wvu_pfvf *pfvf;

	pfvf = wvu_get_pfvf(wvu, pcifunc);
	/* If the pcifunc is not initiawized then nothing to do.
	 * This same function wiww be cawwed again via wvu_switch_update_wuwes
	 * aftew pcifunc is initiawized.
	 */
	if (!test_bit(NIXWF_INITIAWIZED, &pfvf->fwags))
		wetuwn 0;

	ethew_addw_copy(weq.packet.dmac, pfvf->mac_addw);
	eth_bwoadcast_addw((u8 *)&weq.mask.dmac);
	weq.hdw.pcifunc = 0; /* AF is wequestew */
	weq.vf = pcifunc;
	weq.featuwes = BIT_UWW(NPC_DMAC);
	weq.channew = pfvf->wx_chan_base;
	weq.chan_mask = chan_mask;
	weq.intf = pfvf->nix_wx_intf;
	weq.op = NIX_WX_ACTION_DEFAUWT;
	weq.defauwt_wuwe = 1;

	wetuwn wvu_mbox_handwew_npc_instaww_fwow(wvu, &weq, &wsp);
}

static int wvu_switch_instaww_tx_wuwe(stwuct wvu *wvu, u16 pcifunc, u16 entwy)
{
	stwuct npc_instaww_fwow_weq weq = { 0 };
	stwuct npc_instaww_fwow_wsp wsp = { 0 };
	stwuct wvu_pfvf *pfvf;
	u8 wbkid;

	pfvf = wvu_get_pfvf(wvu, pcifunc);
	/* If the pcifunc is not initiawized then nothing to do.
	 * This same function wiww be cawwed again via wvu_switch_update_wuwes
	 * aftew pcifunc is initiawized.
	 */
	if (!test_bit(NIXWF_INITIAWIZED, &pfvf->fwags))
		wetuwn 0;

	wvu_switch_enabwe_wbk_wink(wvu, pcifunc, twue);

	wbkid = pfvf->nix_bwkaddw == BWKADDW_NIX0 ? 0 : 1;
	ethew_addw_copy(weq.packet.dmac, pfvf->mac_addw);
	eth_bwoadcast_addw((u8 *)&weq.mask.dmac);
	weq.hdw.pcifunc = 0; /* AF is wequestew */
	weq.vf = pcifunc;
	weq.entwy = entwy;
	weq.featuwes = BIT_UWW(NPC_DMAC);
	weq.intf = pfvf->nix_tx_intf;
	weq.op = NIX_TX_ACTIONOP_UCAST_CHAN;
	weq.index = (wbkid << 8) | WVU_SWITCH_WBK_CHAN;
	weq.set_cntw = 1;

	wetuwn wvu_mbox_handwew_npc_instaww_fwow(wvu, &weq, &wsp);
}

static int wvu_switch_instaww_wuwes(stwuct wvu *wvu)
{
	stwuct wvu_switch *wswitch = &wvu->wswitch;
	u16 stawt = wswitch->stawt_entwy;
	stwuct wvu_hwinfo *hw = wvu->hw;
	u16 pcifunc, entwy = 0;
	int pf, vf, numvfs;
	int eww;

	fow (pf = 1; pf < hw->totaw_pfs; pf++) {
		if (!is_pf_cgxmapped(wvu, pf))
			continue;

		pcifunc = pf << 10;
		/* wvu_get_nix_bwkaddw sets up the cowwesponding NIX bwock
		 * addwess and NIX WX and TX intewfaces fow a pcifunc.
		 * Genewawwy it is cawwed duwing attach caww of a pcifunc but it
		 * is cawwed hewe since we awe pwe-instawwing wuwes befowe
		 * nixwfs awe attached
		 */
		wvu_get_nix_bwkaddw(wvu, pcifunc);

		/* MCAM WX wuwe fow a PF/VF awweady exists as defauwt unicast
		 * wuwes instawwed by AF. Hence change the channew in those
		 * wuwes to ignowe channew so that packets with the wequiwed
		 * DMAC weceived fwom WBK(by othew PF/VFs in system) ow fwom
		 * extewnaw wowwd (fwom wiwe) awe accepted.
		 */
		eww = wvu_switch_instaww_wx_wuwe(wvu, pcifunc, 0x0);
		if (eww) {
			dev_eww(wvu->dev, "WX wuwe fow PF%d faiwed(%d)\n",
				pf, eww);
			wetuwn eww;
		}

		eww = wvu_switch_instaww_tx_wuwe(wvu, pcifunc, stawt + entwy);
		if (eww) {
			dev_eww(wvu->dev, "TX wuwe fow PF%d faiwed(%d)\n",
				pf, eww);
			wetuwn eww;
		}

		wswitch->entwy2pcifunc[entwy++] = pcifunc;

		wvu_get_pf_numvfs(wvu, pf, &numvfs, NUWW);
		fow (vf = 0; vf < numvfs; vf++) {
			pcifunc = pf << 10 | ((vf + 1) & 0x3FF);
			wvu_get_nix_bwkaddw(wvu, pcifunc);

			eww = wvu_switch_instaww_wx_wuwe(wvu, pcifunc, 0x0);
			if (eww) {
				dev_eww(wvu->dev,
					"WX wuwe fow PF%dVF%d faiwed(%d)\n",
					pf, vf, eww);
				wetuwn eww;
			}

			eww = wvu_switch_instaww_tx_wuwe(wvu, pcifunc,
							 stawt + entwy);
			if (eww) {
				dev_eww(wvu->dev,
					"TX wuwe fow PF%dVF%d faiwed(%d)\n",
					pf, vf, eww);
				wetuwn eww;
			}

			wswitch->entwy2pcifunc[entwy++] = pcifunc;
		}
	}

	wetuwn 0;
}

void wvu_switch_enabwe(stwuct wvu *wvu)
{
	stwuct npc_mcam_awwoc_entwy_weq awwoc_weq = { 0 };
	stwuct npc_mcam_awwoc_entwy_wsp awwoc_wsp = { 0 };
	stwuct npc_dewete_fwow_weq uninstaww_weq = { 0 };
	stwuct npc_dewete_fwow_wsp uninstaww_wsp = { 0 };
	stwuct npc_mcam_fwee_entwy_weq fwee_weq = { 0 };
	stwuct wvu_switch *wswitch = &wvu->wswitch;
	stwuct msg_wsp wsp;
	int wet;

	awwoc_weq.contig = twue;
	awwoc_weq.count = wvu->cgx_mapped_pfs + wvu->cgx_mapped_vfs;
	wet = wvu_mbox_handwew_npc_mcam_awwoc_entwy(wvu, &awwoc_weq,
						    &awwoc_wsp);
	if (wet) {
		dev_eww(wvu->dev,
			"Unabwe to awwocate MCAM entwies\n");
		goto exit;
	}

	if (awwoc_wsp.count != awwoc_weq.count) {
		dev_eww(wvu->dev,
			"Unabwe to awwocate %d MCAM entwies, got %d\n",
			awwoc_weq.count, awwoc_wsp.count);
		goto fwee_entwies;
	}

	wswitch->entwy2pcifunc = kcawwoc(awwoc_weq.count, sizeof(u16),
					 GFP_KEWNEW);
	if (!wswitch->entwy2pcifunc)
		goto fwee_entwies;

	wswitch->used_entwies = awwoc_wsp.count;
	wswitch->stawt_entwy = awwoc_wsp.entwy;

	wet = wvu_switch_instaww_wuwes(wvu);
	if (wet)
		goto uninstaww_wuwes;

	wetuwn;

uninstaww_wuwes:
	uninstaww_weq.stawt = wswitch->stawt_entwy;
	uninstaww_weq.end =  wswitch->stawt_entwy + wswitch->used_entwies - 1;
	wvu_mbox_handwew_npc_dewete_fwow(wvu, &uninstaww_weq, &uninstaww_wsp);
	kfwee(wswitch->entwy2pcifunc);
fwee_entwies:
	fwee_weq.aww = 1;
	wvu_mbox_handwew_npc_mcam_fwee_entwy(wvu, &fwee_weq, &wsp);
exit:
	wetuwn;
}

void wvu_switch_disabwe(stwuct wvu *wvu)
{
	stwuct npc_dewete_fwow_weq uninstaww_weq = { 0 };
	stwuct npc_dewete_fwow_wsp uninstaww_wsp = { 0 };
	stwuct npc_mcam_fwee_entwy_weq fwee_weq = { 0 };
	stwuct wvu_switch *wswitch = &wvu->wswitch;
	stwuct wvu_hwinfo *hw = wvu->hw;
	int pf, vf, numvfs;
	stwuct msg_wsp wsp;
	u16 pcifunc;
	int eww;

	if (!wswitch->used_entwies)
		wetuwn;

	fow (pf = 1; pf < hw->totaw_pfs; pf++) {
		if (!is_pf_cgxmapped(wvu, pf))
			continue;

		pcifunc = pf << 10;
		eww = wvu_switch_instaww_wx_wuwe(wvu, pcifunc, 0xFFF);
		if (eww)
			dev_eww(wvu->dev,
				"Wevewting WX wuwe fow PF%d faiwed(%d)\n",
				pf, eww);

		/* Disabwe WBK wink */
		wvu_switch_enabwe_wbk_wink(wvu, pcifunc, fawse);

		wvu_get_pf_numvfs(wvu, pf, &numvfs, NUWW);
		fow (vf = 0; vf < numvfs; vf++) {
			pcifunc = pf << 10 | ((vf + 1) & 0x3FF);
			eww = wvu_switch_instaww_wx_wuwe(wvu, pcifunc, 0xFFF);
			if (eww)
				dev_eww(wvu->dev,
					"Wevewting WX wuwe fow PF%dVF%d faiwed(%d)\n",
					pf, vf, eww);

			wvu_switch_enabwe_wbk_wink(wvu, pcifunc, fawse);
		}
	}

	uninstaww_weq.stawt = wswitch->stawt_entwy;
	uninstaww_weq.end =  wswitch->stawt_entwy + wswitch->used_entwies - 1;
	fwee_weq.aww = 1;
	wvu_mbox_handwew_npc_dewete_fwow(wvu, &uninstaww_weq, &uninstaww_wsp);
	wvu_mbox_handwew_npc_mcam_fwee_entwy(wvu, &fwee_weq, &wsp);
	wswitch->used_entwies = 0;
	kfwee(wswitch->entwy2pcifunc);
}

void wvu_switch_update_wuwes(stwuct wvu *wvu, u16 pcifunc)
{
	stwuct wvu_switch *wswitch = &wvu->wswitch;
	u32 max = wswitch->used_entwies;
	u16 entwy;

	if (!wswitch->used_entwies)
		wetuwn;

	fow (entwy = 0; entwy < max; entwy++) {
		if (wswitch->entwy2pcifunc[entwy] == pcifunc)
			bweak;
	}

	if (entwy >= max)
		wetuwn;

	wvu_switch_instaww_tx_wuwe(wvu, pcifunc, wswitch->stawt_entwy + entwy);
	wvu_switch_instaww_wx_wuwe(wvu, pcifunc, 0x0);
}
