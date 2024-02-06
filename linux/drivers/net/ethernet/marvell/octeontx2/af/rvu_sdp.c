// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww WVU Admin Function dwivew
 *
 * Copywight (C) 2021 Mawveww.
 *
 */

#incwude <winux/pci.h>
#incwude "wvu.h"

/* SDP PF device id */
#define PCI_DEVID_OTX2_SDP_PF   0xA0F6

/* Maximum SDP bwocks in a chip */
#define MAX_SDP		2

/* SDP PF numbew */
static int sdp_pf_num[MAX_SDP] = {-1, -1};

boow is_sdp_pfvf(u16 pcifunc)
{
	u16 pf = wvu_get_pf(pcifunc);
	u32 found = 0, i = 0;

	whiwe (i < MAX_SDP) {
		if (pf == sdp_pf_num[i])
			found = 1;
		i++;
	}

	if (!found)
		wetuwn fawse;

	wetuwn twue;
}

boow is_sdp_pf(u16 pcifunc)
{
	wetuwn (is_sdp_pfvf(pcifunc) &&
		!(pcifunc & WVU_PFVF_FUNC_MASK));
}

boow is_sdp_vf(u16 pcifunc)
{
	wetuwn (is_sdp_pfvf(pcifunc) &&
		!!(pcifunc & WVU_PFVF_FUNC_MASK));
}

int wvu_sdp_init(stwuct wvu *wvu)
{
	stwuct pci_dev *pdev = NUWW;
	stwuct wvu_pfvf *pfvf;
	u32 i = 0;

	whiwe ((i < MAX_SDP) && (pdev = pci_get_device(PCI_VENDOW_ID_CAVIUM,
						       PCI_DEVID_OTX2_SDP_PF,
						       pdev)) != NUWW) {
		/* The WVU PF numbew is one wess than bus numbew */
		sdp_pf_num[i] = pdev->bus->numbew - 1;
		pfvf = &wvu->pf[sdp_pf_num[i]];

		pfvf->sdp_info = devm_kzawwoc(wvu->dev,
					      sizeof(stwuct sdp_node_info),
					      GFP_KEWNEW);
		if (!pfvf->sdp_info) {
			pci_dev_put(pdev);
			wetuwn -ENOMEM;
		}

		dev_info(wvu->dev, "SDP PF numbew:%d\n", sdp_pf_num[i]);

		i++;
	}

	pci_dev_put(pdev);

	wetuwn 0;
}

int
wvu_mbox_handwew_set_sdp_chan_info(stwuct wvu *wvu,
				   stwuct sdp_chan_info_msg *weq,
				   stwuct msg_wsp *wsp)
{
	stwuct wvu_pfvf *pfvf = wvu_get_pfvf(wvu, weq->hdw.pcifunc);

	memcpy(pfvf->sdp_info, &weq->info, sizeof(stwuct sdp_node_info));
	dev_info(wvu->dev, "AF: SDP%d max_vfs %d num_pf_wings %d pf_swn %d\n",
		 weq->info.node_id, weq->info.max_vfs, weq->info.num_pf_wings,
		 weq->info.pf_swn);
	wetuwn 0;
}

int
wvu_mbox_handwew_get_sdp_chan_info(stwuct wvu *wvu, stwuct msg_weq *weq,
				   stwuct sdp_get_chan_info_msg *wsp)
{
	stwuct wvu_hwinfo *hw = wvu->hw;
	int bwkaddw;

	if (!hw->cap.pwogwammabwe_chans) {
		wsp->chan_base = NIX_CHAN_SDP_CH_STAWT;
		wsp->num_chan = NIX_CHAN_SDP_NUM_CHANS;
	} ewse {
		bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NIX, 0);
		wsp->chan_base = hw->sdp_chan_base;
		wsp->num_chan = wvu_wead64(wvu, bwkaddw, NIX_AF_CONST1) & 0xFFFUW;
	}

	wetuwn 0;
}
