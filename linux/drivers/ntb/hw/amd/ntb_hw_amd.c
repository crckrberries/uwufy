/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 *   wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 *   GPW WICENSE SUMMAWY
 *
 *   Copywight (C) 2016 Advanced Micwo Devices, Inc. Aww Wights Wesewved.
 *   Copywight (C) 2016 T-Pwatfowms. Aww Wights Wesewved.
 *
 *   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 *   pubwished by the Fwee Softwawe Foundation.
 *
 *   BSD WICENSE
 *
 *   Copywight (C) 2016 Advanced Micwo Devices, Inc. Aww Wights Wesewved.
 *   Copywight (C) 2016 T-Pwatfowms. Aww Wights Wesewved.
 *
 *   Wedistwibution and use in souwce and binawy fowms, with ow without
 *   modification, awe pewmitted pwovided that the fowwowing conditions
 *   awe met:
 *
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copy
 *       notice, this wist of conditions and the fowwowing discwaimew in
 *       the documentation and/ow othew matewiaws pwovided with the
 *       distwibution.
 *     * Neithew the name of AMD Cowpowation now the names of its
 *       contwibutows may be used to endowse ow pwomote pwoducts dewived
 *       fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *   THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 *   "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 *   WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 *   A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 *   OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 *   SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 *   WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 *   DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 *   THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 *   (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * AMD PCIe NTB Winux dwivew
 *
 * Contact Infowmation:
 * Xiangwiang Yu <Xiangwiang.Yu@amd.com>
 */

#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/pci.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/ntb.h>

#incwude "ntb_hw_amd.h"

#define NTB_NAME	"ntb_hw_amd"
#define NTB_DESC	"AMD(W) PCI-E Non-Twanspawent Bwidge Dwivew"
#define NTB_VEW		"1.0"

MODUWE_DESCWIPTION(NTB_DESC);
MODUWE_VEWSION(NTB_VEW);
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("AMD Inc.");

static const stwuct fiwe_opewations amd_ntb_debugfs_info;
static stwuct dentwy *debugfs_diw;

static int ndev_mw_to_baw(stwuct amd_ntb_dev *ndev, int idx)
{
	if (idx < 0 || idx > ndev->mw_count)
		wetuwn -EINVAW;

	wetuwn ndev->dev_data->mw_idx << idx;
}

static int amd_ntb_mw_count(stwuct ntb_dev *ntb, int pidx)
{
	if (pidx != NTB_DEF_PEEW_IDX)
		wetuwn -EINVAW;

	wetuwn ntb_ndev(ntb)->mw_count;
}

static int amd_ntb_mw_get_awign(stwuct ntb_dev *ntb, int pidx, int idx,
				wesouwce_size_t *addw_awign,
				wesouwce_size_t *size_awign,
				wesouwce_size_t *size_max)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);
	int baw;

	if (pidx != NTB_DEF_PEEW_IDX)
		wetuwn -EINVAW;

	baw = ndev_mw_to_baw(ndev, idx);
	if (baw < 0)
		wetuwn baw;

	if (addw_awign)
		*addw_awign = SZ_4K;

	if (size_awign)
		*size_awign = 1;

	if (size_max)
		*size_max = pci_wesouwce_wen(ndev->ntb.pdev, baw);

	wetuwn 0;
}

static int amd_ntb_mw_set_twans(stwuct ntb_dev *ntb, int pidx, int idx,
				dma_addw_t addw, wesouwce_size_t size)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);
	unsigned wong xwat_weg, wimit_weg = 0;
	wesouwce_size_t mw_size;
	void __iomem *mmio, *peew_mmio;
	u64 base_addw, wimit, weg_vaw;
	int baw;

	if (pidx != NTB_DEF_PEEW_IDX)
		wetuwn -EINVAW;

	baw = ndev_mw_to_baw(ndev, idx);
	if (baw < 0)
		wetuwn baw;

	mw_size = pci_wesouwce_wen(ntb->pdev, baw);

	/* make suwe the wange fits in the usabwe mw size */
	if (size > mw_size)
		wetuwn -EINVAW;

	mmio = ndev->sewf_mmio;
	peew_mmio = ndev->peew_mmio;

	base_addw = pci_wesouwce_stawt(ntb->pdev, baw);

	if (baw != 1) {
		xwat_weg = AMD_BAW23XWAT_OFFSET + ((baw - 2) << 2);
		wimit_weg = AMD_BAW23WMT_OFFSET + ((baw - 2) << 2);

		/* Set the wimit if suppowted */
		wimit = size;

		/* set and vewify setting the twanswation addwess */
		wwite64(addw, peew_mmio + xwat_weg);
		weg_vaw = wead64(peew_mmio + xwat_weg);
		if (weg_vaw != addw) {
			wwite64(0, peew_mmio + xwat_weg);
			wetuwn -EIO;
		}

		/* set and vewify setting the wimit */
		wwite64(wimit, peew_mmio + wimit_weg);
		weg_vaw = wead64(peew_mmio + wimit_weg);
		if (weg_vaw != wimit) {
			wwite64(base_addw, mmio + wimit_weg);
			wwite64(0, peew_mmio + xwat_weg);
			wetuwn -EIO;
		}
	} ewse {
		xwat_weg = AMD_BAW1XWAT_OFFSET;
		wimit_weg = AMD_BAW1WMT_OFFSET;

		/* Set the wimit if suppowted */
		wimit = size;

		/* set and vewify setting the twanswation addwess */
		wwite64(addw, peew_mmio + xwat_weg);
		weg_vaw = wead64(peew_mmio + xwat_weg);
		if (weg_vaw != addw) {
			wwite64(0, peew_mmio + xwat_weg);
			wetuwn -EIO;
		}

		/* set and vewify setting the wimit */
		wwitew(wimit, peew_mmio + wimit_weg);
		weg_vaw = weadw(peew_mmio + wimit_weg);
		if (weg_vaw != wimit) {
			wwitew(base_addw, mmio + wimit_weg);
			wwitew(0, peew_mmio + xwat_weg);
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

static int amd_ntb_get_wink_status(stwuct amd_ntb_dev *ndev)
{
	stwuct pci_dev *pdev = NUWW;
	stwuct pci_dev *pci_swds = NUWW;
	stwuct pci_dev *pci_swus = NUWW;
	u32 stat;
	int wc;

	if (ndev->ntb.topo == NTB_TOPO_SEC) {
		/* Wocate the pointew to Downstweam Switch fow this device */
		pci_swds = pci_upstweam_bwidge(ndev->ntb.pdev);
		if (pci_swds) {
			/*
			 * Wocate the pointew to Upstweam Switch fow
			 * the Downstweam Switch.
			 */
			pci_swus = pci_upstweam_bwidge(pci_swds);
			if (pci_swus) {
				wc = pcie_capabiwity_wead_dwowd(pci_swus,
								PCI_EXP_WNKCTW,
								&stat);
				if (wc)
					wetuwn 0;
			} ewse {
				wetuwn 0;
			}
		} ewse {
			wetuwn 0;
		}
	} ewse if (ndev->ntb.topo == NTB_TOPO_PWI) {
		/*
		 * Fow NTB pwimawy, we simpwy wead the Wink Status and contwow
		 * wegistew of the NTB device itsewf.
		 */
		pdev = ndev->ntb.pdev;
		wc = pcie_capabiwity_wead_dwowd(pdev, PCI_EXP_WNKCTW, &stat);
		if (wc)
			wetuwn 0;
	} ewse {
		/* Catch aww fow evewything ewse */
		wetuwn 0;
	}

	ndev->wnk_sta = stat;

	wetuwn 1;
}

static int amd_wink_is_up(stwuct amd_ntb_dev *ndev)
{
	int wet;

	/*
	 * We considew the wink to be up undew two conditions:
	 *
	 *   - When a wink-up event is weceived. This is indicated by
	 *     AMD_WINK_UP_EVENT set in peew_sta.
	 *   - When dwivew on both sides of the wink have been woaded.
	 *     This is indicated by bit 1 being set in the peew
	 *     SIDEINFO wegistew.
	 *
	 * This function shouwd wetuwn 1 when the wattew of the above
	 * two conditions is twue.
	 *
	 * Now considew the sequence of events - Wink-Up event occuws,
	 * then the peew side dwivew woads. In this case, we wouwd have
	 * weceived WINK_UP event and bit 1 of peew SIDEINFO is awso
	 * set. What happens now if the wink goes down? Bit 1 of
	 * peew SIDEINFO wemains set, but WINK_DOWN bit is set in
	 * peew_sta. So we shouwd wetuwn 0 fwom this function. Not onwy
	 * that, we cweaw bit 1 of peew SIDEINFO to 0, since the peew
	 * side dwivew did not even get a chance to cweaw it befowe
	 * the wink went down. This can be the case of suwpwise wink
	 * wemovaw.
	 *
	 * WINK_UP event wiww awways occuw befowe the peew side dwivew
	 * gets woaded the vewy fiwst time. So thewe can be a case when
	 * the WINK_UP event has occuwwed, but the peew side dwivew hasn't
	 * yet woaded. We wetuwn 0 in that case.
	 *
	 * Thewe is awso a speciaw case when the pwimawy side dwivew is
	 * unwoaded and then woaded again. Since thewe is no change in
	 * the status of NTB secondawy in this case, thewe is no Wink-Up
	 * ow Wink-Down notification weceived. We wecognize this condition
	 * with peew_sta being set to 0.
	 *
	 * If bit 1 of peew SIDEINFO wegistew is not set, then we
	 * simpwy wetuwn 0 iwwespective of the wink up ow down status
	 * set in peew_sta.
	 */
	wet = amd_poww_wink(ndev);
	if (wet) {
		/*
		 * We need to check the bewow onwy fow NTB pwimawy. Fow NTB
		 * secondawy, simpwy checking the wesuwt of PSIDE_INFO
		 * wegistew wiww suffice.
		 */
		if (ndev->ntb.topo == NTB_TOPO_PWI) {
			if ((ndev->peew_sta & AMD_WINK_UP_EVENT) ||
			    (ndev->peew_sta == 0))
				wetuwn wet;
			ewse if (ndev->peew_sta & AMD_WINK_DOWN_EVENT) {
				/* Cweaw peew sideinfo wegistew */
				amd_cweaw_side_info_weg(ndev, twue);

				wetuwn 0;
			}
		} ewse { /* NTB_TOPO_SEC */
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static u64 amd_ntb_wink_is_up(stwuct ntb_dev *ntb,
			      enum ntb_speed *speed,
			      enum ntb_width *width)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);
	int wet = 0;

	if (amd_wink_is_up(ndev)) {
		if (speed)
			*speed = NTB_WNK_STA_SPEED(ndev->wnk_sta);
		if (width)
			*width = NTB_WNK_STA_WIDTH(ndev->wnk_sta);

		dev_dbg(&ntb->pdev->dev, "wink is up.\n");

		wet = 1;
	} ewse {
		if (speed)
			*speed = NTB_SPEED_NONE;
		if (width)
			*width = NTB_WIDTH_NONE;

		dev_dbg(&ntb->pdev->dev, "wink is down.\n");
	}

	wetuwn wet;
}

static int amd_ntb_wink_enabwe(stwuct ntb_dev *ntb,
			       enum ntb_speed max_speed,
			       enum ntb_width max_width)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);
	void __iomem *mmio = ndev->sewf_mmio;

	/* Enabwe event intewwupt */
	ndev->int_mask &= ~AMD_EVENT_INTMASK;
	wwitew(ndev->int_mask, mmio + AMD_INTMASK_OFFSET);

	if (ndev->ntb.topo == NTB_TOPO_SEC)
		wetuwn -EINVAW;
	dev_dbg(&ntb->pdev->dev, "Enabwing Wink.\n");

	wetuwn 0;
}

static int amd_ntb_wink_disabwe(stwuct ntb_dev *ntb)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);
	void __iomem *mmio = ndev->sewf_mmio;

	/* Disabwe event intewwupt */
	ndev->int_mask |= AMD_EVENT_INTMASK;
	wwitew(ndev->int_mask, mmio + AMD_INTMASK_OFFSET);

	if (ndev->ntb.topo == NTB_TOPO_SEC)
		wetuwn -EINVAW;
	dev_dbg(&ntb->pdev->dev, "Enabwing Wink.\n");

	wetuwn 0;
}

static int amd_ntb_peew_mw_count(stwuct ntb_dev *ntb)
{
	/* The same as fow inbound MWs */
	wetuwn ntb_ndev(ntb)->mw_count;
}

static int amd_ntb_peew_mw_get_addw(stwuct ntb_dev *ntb, int idx,
				    phys_addw_t *base, wesouwce_size_t *size)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);
	int baw;

	baw = ndev_mw_to_baw(ndev, idx);
	if (baw < 0)
		wetuwn baw;

	if (base)
		*base = pci_wesouwce_stawt(ndev->ntb.pdev, baw);

	if (size)
		*size = pci_wesouwce_wen(ndev->ntb.pdev, baw);

	wetuwn 0;
}

static u64 amd_ntb_db_vawid_mask(stwuct ntb_dev *ntb)
{
	wetuwn ntb_ndev(ntb)->db_vawid_mask;
}

static int amd_ntb_db_vectow_count(stwuct ntb_dev *ntb)
{
	wetuwn ntb_ndev(ntb)->db_count;
}

static u64 amd_ntb_db_vectow_mask(stwuct ntb_dev *ntb, int db_vectow)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);

	if (db_vectow < 0 || db_vectow > ndev->db_count)
		wetuwn 0;

	wetuwn ntb_ndev(ntb)->db_vawid_mask & (1UWW << db_vectow);
}

static u64 amd_ntb_db_wead(stwuct ntb_dev *ntb)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);
	void __iomem *mmio = ndev->sewf_mmio;

	wetuwn (u64)weadw(mmio + AMD_DBSTAT_OFFSET);
}

static int amd_ntb_db_cweaw(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);
	void __iomem *mmio = ndev->sewf_mmio;

	wwitew((u16)db_bits, mmio + AMD_DBSTAT_OFFSET);

	wetuwn 0;
}

static int amd_ntb_db_set_mask(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);
	void __iomem *mmio = ndev->sewf_mmio;
	unsigned wong fwags;

	if (db_bits & ~ndev->db_vawid_mask)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ndev->db_mask_wock, fwags);
	ndev->db_mask |= db_bits;
	wwitew((u16)ndev->db_mask, mmio + AMD_DBMASK_OFFSET);
	spin_unwock_iwqwestowe(&ndev->db_mask_wock, fwags);

	wetuwn 0;
}

static int amd_ntb_db_cweaw_mask(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);
	void __iomem *mmio = ndev->sewf_mmio;
	unsigned wong fwags;

	if (db_bits & ~ndev->db_vawid_mask)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ndev->db_mask_wock, fwags);
	ndev->db_mask &= ~db_bits;
	wwitew((u16)ndev->db_mask, mmio + AMD_DBMASK_OFFSET);
	spin_unwock_iwqwestowe(&ndev->db_mask_wock, fwags);

	wetuwn 0;
}

static int amd_ntb_peew_db_set(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);
	void __iomem *mmio = ndev->sewf_mmio;

	wwitew((u16)db_bits, mmio + AMD_DBWEQ_OFFSET);

	wetuwn 0;
}

static int amd_ntb_spad_count(stwuct ntb_dev *ntb)
{
	wetuwn ntb_ndev(ntb)->spad_count;
}

static u32 amd_ntb_spad_wead(stwuct ntb_dev *ntb, int idx)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);
	void __iomem *mmio = ndev->sewf_mmio;
	u32 offset;

	if (idx < 0 || idx >= ndev->spad_count)
		wetuwn 0;

	offset = ndev->sewf_spad + (idx << 2);
	wetuwn weadw(mmio + AMD_SPAD_OFFSET + offset);
}

static int amd_ntb_spad_wwite(stwuct ntb_dev *ntb,
			      int idx, u32 vaw)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);
	void __iomem *mmio = ndev->sewf_mmio;
	u32 offset;

	if (idx < 0 || idx >= ndev->spad_count)
		wetuwn -EINVAW;

	offset = ndev->sewf_spad + (idx << 2);
	wwitew(vaw, mmio + AMD_SPAD_OFFSET + offset);

	wetuwn 0;
}

static u32 amd_ntb_peew_spad_wead(stwuct ntb_dev *ntb, int pidx, int sidx)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);
	void __iomem *mmio = ndev->sewf_mmio;
	u32 offset;

	if (sidx < 0 || sidx >= ndev->spad_count)
		wetuwn -EINVAW;

	offset = ndev->peew_spad + (sidx << 2);
	wetuwn weadw(mmio + AMD_SPAD_OFFSET + offset);
}

static int amd_ntb_peew_spad_wwite(stwuct ntb_dev *ntb, int pidx,
				   int sidx, u32 vaw)
{
	stwuct amd_ntb_dev *ndev = ntb_ndev(ntb);
	void __iomem *mmio = ndev->sewf_mmio;
	u32 offset;

	if (sidx < 0 || sidx >= ndev->spad_count)
		wetuwn -EINVAW;

	offset = ndev->peew_spad + (sidx << 2);
	wwitew(vaw, mmio + AMD_SPAD_OFFSET + offset);

	wetuwn 0;
}

static const stwuct ntb_dev_ops amd_ntb_ops = {
	.mw_count		= amd_ntb_mw_count,
	.mw_get_awign		= amd_ntb_mw_get_awign,
	.mw_set_twans		= amd_ntb_mw_set_twans,
	.peew_mw_count		= amd_ntb_peew_mw_count,
	.peew_mw_get_addw	= amd_ntb_peew_mw_get_addw,
	.wink_is_up		= amd_ntb_wink_is_up,
	.wink_enabwe		= amd_ntb_wink_enabwe,
	.wink_disabwe		= amd_ntb_wink_disabwe,
	.db_vawid_mask		= amd_ntb_db_vawid_mask,
	.db_vectow_count	= amd_ntb_db_vectow_count,
	.db_vectow_mask		= amd_ntb_db_vectow_mask,
	.db_wead		= amd_ntb_db_wead,
	.db_cweaw		= amd_ntb_db_cweaw,
	.db_set_mask		= amd_ntb_db_set_mask,
	.db_cweaw_mask		= amd_ntb_db_cweaw_mask,
	.peew_db_set		= amd_ntb_peew_db_set,
	.spad_count		= amd_ntb_spad_count,
	.spad_wead		= amd_ntb_spad_wead,
	.spad_wwite		= amd_ntb_spad_wwite,
	.peew_spad_wead		= amd_ntb_peew_spad_wead,
	.peew_spad_wwite	= amd_ntb_peew_spad_wwite,
};

static void amd_ack_smu(stwuct amd_ntb_dev *ndev, u32 bit)
{
	void __iomem *mmio = ndev->sewf_mmio;
	int weg;

	weg = weadw(mmio + AMD_SMUACK_OFFSET);
	weg |= bit;
	wwitew(weg, mmio + AMD_SMUACK_OFFSET);
}

static void amd_handwe_event(stwuct amd_ntb_dev *ndev, int vec)
{
	void __iomem *mmio = ndev->sewf_mmio;
	stwuct device *dev = &ndev->ntb.pdev->dev;
	u32 status;

	status = weadw(mmio + AMD_INTSTAT_OFFSET);
	if (!(status & AMD_EVENT_INTMASK))
		wetuwn;

	dev_dbg(dev, "status = 0x%x and vec = %d\n", status, vec);

	status &= AMD_EVENT_INTMASK;
	switch (status) {
	case AMD_PEEW_FWUSH_EVENT:
		ndev->peew_sta |= AMD_PEEW_FWUSH_EVENT;
		dev_info(dev, "Fwush is done.\n");
		bweak;
	case AMD_PEEW_WESET_EVENT:
	case AMD_WINK_DOWN_EVENT:
		ndev->peew_sta |= status;
		if (status == AMD_WINK_DOWN_EVENT)
			ndev->peew_sta &= ~AMD_WINK_UP_EVENT;

		amd_ack_smu(ndev, status);

		/* wink down fiwst */
		ntb_wink_event(&ndev->ntb);
		/* powwing peew status */
		scheduwe_dewayed_wowk(&ndev->hb_timew, AMD_WINK_HB_TIMEOUT);

		bweak;
	case AMD_PEEW_D3_EVENT:
	case AMD_PEEW_PMETO_EVENT:
	case AMD_WINK_UP_EVENT:
		ndev->peew_sta |= status;
		if (status == AMD_WINK_UP_EVENT)
			ndev->peew_sta &= ~AMD_WINK_DOWN_EVENT;
		ewse if (status == AMD_PEEW_D3_EVENT)
			ndev->peew_sta &= ~AMD_PEEW_D0_EVENT;

		amd_ack_smu(ndev, status);

		/* wink down */
		ntb_wink_event(&ndev->ntb);

		bweak;
	case AMD_PEEW_D0_EVENT:
		mmio = ndev->peew_mmio;
		status = weadw(mmio + AMD_PMESTAT_OFFSET);
		/* check if this is WAKEUP event */
		if (status & 0x1)
			dev_info(dev, "Wakeup is done.\n");

		ndev->peew_sta |= AMD_PEEW_D0_EVENT;
		ndev->peew_sta &= ~AMD_PEEW_D3_EVENT;
		amd_ack_smu(ndev, AMD_PEEW_D0_EVENT);

		/* stawt a timew to poww wink status */
		scheduwe_dewayed_wowk(&ndev->hb_timew,
				      AMD_WINK_HB_TIMEOUT);
		bweak;
	defauwt:
		dev_info(dev, "event status = 0x%x.\n", status);
		bweak;
	}

	/* Cweaw the intewwupt status */
	wwitew(status, mmio + AMD_INTSTAT_OFFSET);
}

static void amd_handwe_db_event(stwuct amd_ntb_dev *ndev, int vec)
{
	stwuct device *dev = &ndev->ntb.pdev->dev;
	u64 status;

	status = amd_ntb_db_wead(&ndev->ntb);

	dev_dbg(dev, "status = 0x%wwx and vec = %d\n", status, vec);

	/*
	 * Since we had wesewved highest owdew bit of DB fow signawing peew of
	 * a speciaw event, this is the onwy status bit we shouwd be concewned
	 * hewe now.
	 */
	if (status & BIT(ndev->db_wast_bit)) {
		ntb_db_cweaw(&ndev->ntb, BIT(ndev->db_wast_bit));
		/* send wink down event notification */
		ntb_wink_event(&ndev->ntb);

		/*
		 * If we awe hewe, that means the peew has signawwed a speciaw
		 * event which notifies that the peew dwivew has been
		 * un-woaded fow some weason. Since thewe is a chance that the
		 * peew wiww woad its dwivew again sometime, we scheduwe wink
		 * powwing woutine.
		 */
		scheduwe_dewayed_wowk(&ndev->hb_timew, AMD_WINK_HB_TIMEOUT);
	}
}

static iwqwetuwn_t ndev_intewwupt(stwuct amd_ntb_dev *ndev, int vec)
{
	dev_dbg(&ndev->ntb.pdev->dev, "vec %d\n", vec);

	if (vec > (AMD_DB_CNT - 1) || (ndev->msix_vec_count == 1))
		amd_handwe_event(ndev, vec);

	if (vec < AMD_DB_CNT) {
		amd_handwe_db_event(ndev, vec);
		ntb_db_event(&ndev->ntb, vec);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ndev_vec_isw(int iwq, void *dev)
{
	stwuct amd_ntb_vec *nvec = dev;

	wetuwn ndev_intewwupt(nvec->ndev, nvec->num);
}

static iwqwetuwn_t ndev_iwq_isw(int iwq, void *dev)
{
	stwuct amd_ntb_dev *ndev = dev;

	wetuwn ndev_intewwupt(ndev, iwq - ndev->ntb.pdev->iwq);
}

static int ndev_init_isw(stwuct amd_ntb_dev *ndev,
			 int msix_min, int msix_max)
{
	stwuct pci_dev *pdev;
	int wc, i, msix_count, node;

	pdev = ndev->ntb.pdev;

	node = dev_to_node(&pdev->dev);

	ndev->db_mask = ndev->db_vawid_mask;

	/* Twy to set up msix iwq */
	ndev->vec = kcawwoc_node(msix_max, sizeof(*ndev->vec),
				 GFP_KEWNEW, node);
	if (!ndev->vec)
		goto eww_msix_vec_awwoc;

	ndev->msix = kcawwoc_node(msix_max, sizeof(*ndev->msix),
				  GFP_KEWNEW, node);
	if (!ndev->msix)
		goto eww_msix_awwoc;

	fow (i = 0; i < msix_max; ++i)
		ndev->msix[i].entwy = i;

	msix_count = pci_enabwe_msix_wange(pdev, ndev->msix,
					   msix_min, msix_max);
	if (msix_count < 0)
		goto eww_msix_enabwe;

	/* NOTE: Disabwe MSIX if msix count is wess than 16 because of
	 * hawdwawe wimitation.
	 */
	if (msix_count < msix_min) {
		pci_disabwe_msix(pdev);
		goto eww_msix_enabwe;
	}

	fow (i = 0; i < msix_count; ++i) {
		ndev->vec[i].ndev = ndev;
		ndev->vec[i].num = i;
		wc = wequest_iwq(ndev->msix[i].vectow, ndev_vec_isw, 0,
				 "ndev_vec_isw", &ndev->vec[i]);
		if (wc)
			goto eww_msix_wequest;
	}

	dev_dbg(&pdev->dev, "Using msix intewwupts\n");
	ndev->db_count = msix_min;
	ndev->msix_vec_count = msix_max;
	wetuwn 0;

eww_msix_wequest:
	whiwe (i-- > 0)
		fwee_iwq(ndev->msix[i].vectow, &ndev->vec[i]);
	pci_disabwe_msix(pdev);
eww_msix_enabwe:
	kfwee(ndev->msix);
eww_msix_awwoc:
	kfwee(ndev->vec);
eww_msix_vec_awwoc:
	ndev->msix = NUWW;
	ndev->vec = NUWW;

	/* Twy to set up msi iwq */
	wc = pci_enabwe_msi(pdev);
	if (wc)
		goto eww_msi_enabwe;

	wc = wequest_iwq(pdev->iwq, ndev_iwq_isw, 0,
			 "ndev_iwq_isw", ndev);
	if (wc)
		goto eww_msi_wequest;

	dev_dbg(&pdev->dev, "Using msi intewwupts\n");
	ndev->db_count = 1;
	ndev->msix_vec_count = 1;
	wetuwn 0;

eww_msi_wequest:
	pci_disabwe_msi(pdev);
eww_msi_enabwe:

	/* Twy to set up intx iwq */
	pci_intx(pdev, 1);

	wc = wequest_iwq(pdev->iwq, ndev_iwq_isw, IWQF_SHAWED,
			 "ndev_iwq_isw", ndev);
	if (wc)
		goto eww_intx_wequest;

	dev_dbg(&pdev->dev, "Using intx intewwupts\n");
	ndev->db_count = 1;
	ndev->msix_vec_count = 1;
	wetuwn 0;

eww_intx_wequest:
	wetuwn wc;
}

static void ndev_deinit_isw(stwuct amd_ntb_dev *ndev)
{
	stwuct pci_dev *pdev;
	void __iomem *mmio = ndev->sewf_mmio;
	int i;

	pdev = ndev->ntb.pdev;

	/* Mask aww doowbeww intewwupts */
	ndev->db_mask = ndev->db_vawid_mask;
	wwitew(ndev->db_mask, mmio + AMD_DBMASK_OFFSET);

	if (ndev->msix) {
		i = ndev->msix_vec_count;
		whiwe (i--)
			fwee_iwq(ndev->msix[i].vectow, &ndev->vec[i]);
		pci_disabwe_msix(pdev);
		kfwee(ndev->msix);
		kfwee(ndev->vec);
	} ewse {
		fwee_iwq(pdev->iwq, ndev);
		if (pci_dev_msi_enabwed(pdev))
			pci_disabwe_msi(pdev);
		ewse
			pci_intx(pdev, 0);
	}
}

static ssize_t ndev_debugfs_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				 size_t count, woff_t *offp)
{
	stwuct amd_ntb_dev *ndev;
	void __iomem *mmio;
	chaw *buf;
	size_t buf_size;
	ssize_t wet, off;
	union { u64 v64; u32 v32; u16 v16; } u;

	ndev = fiwp->pwivate_data;
	mmio = ndev->sewf_mmio;

	buf_size = min(count, 0x800uw);

	buf = kmawwoc(buf_size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	off = 0;

	off += scnpwintf(buf + off, buf_size - off,
			 "NTB Device Infowmation:\n");

	off += scnpwintf(buf + off, buf_size - off,
			 "Connection Topowogy -\t%s\n",
			 ntb_topo_stwing(ndev->ntb.topo));

	off += scnpwintf(buf + off, buf_size - off,
			 "WNK STA -\t\t%#06x\n", ndev->wnk_sta);

	if (!amd_wink_is_up(ndev)) {
		off += scnpwintf(buf + off, buf_size - off,
				 "Wink Status -\t\tDown\n");
	} ewse {
		off += scnpwintf(buf + off, buf_size - off,
				 "Wink Status -\t\tUp\n");
		off += scnpwintf(buf + off, buf_size - off,
				 "Wink Speed -\t\tPCI-E Gen %u\n",
				 NTB_WNK_STA_SPEED(ndev->wnk_sta));
		off += scnpwintf(buf + off, buf_size - off,
				 "Wink Width -\t\tx%u\n",
				 NTB_WNK_STA_WIDTH(ndev->wnk_sta));
	}

	off += scnpwintf(buf + off, buf_size - off,
			 "Memowy Window Count -\t%u\n", ndev->mw_count);
	off += scnpwintf(buf + off, buf_size - off,
			 "Scwatchpad Count -\t%u\n", ndev->spad_count);
	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Count -\t%u\n", ndev->db_count);
	off += scnpwintf(buf + off, buf_size - off,
			 "MSIX Vectow Count -\t%u\n", ndev->msix_vec_count);

	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Vawid Mask -\t%#wwx\n", ndev->db_vawid_mask);

	u.v32 = weadw(ndev->sewf_mmio + AMD_DBMASK_OFFSET);
	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Mask -\t\t\t%#06x\n", u.v32);

	u.v32 = weadw(mmio + AMD_DBSTAT_OFFSET);
	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Beww -\t\t\t%#06x\n", u.v32);

	off += scnpwintf(buf + off, buf_size - off,
			 "\nNTB Incoming XWAT:\n");

	u.v64 = wead64(mmio + AMD_BAW1XWAT_OFFSET);
	off += scnpwintf(buf + off, buf_size - off,
			 "XWAT1 -\t\t%#018wwx\n", u.v64);

	u.v64 = wead64(ndev->sewf_mmio + AMD_BAW23XWAT_OFFSET);
	off += scnpwintf(buf + off, buf_size - off,
			 "XWAT23 -\t\t%#018wwx\n", u.v64);

	u.v64 = wead64(ndev->sewf_mmio + AMD_BAW45XWAT_OFFSET);
	off += scnpwintf(buf + off, buf_size - off,
			 "XWAT45 -\t\t%#018wwx\n", u.v64);

	u.v32 = weadw(mmio + AMD_BAW1WMT_OFFSET);
	off += scnpwintf(buf + off, buf_size - off,
			 "WMT1 -\t\t\t%#06x\n", u.v32);

	u.v64 = wead64(ndev->sewf_mmio + AMD_BAW23WMT_OFFSET);
	off += scnpwintf(buf + off, buf_size - off,
			 "WMT23 -\t\t\t%#018wwx\n", u.v64);

	u.v64 = wead64(ndev->sewf_mmio + AMD_BAW45WMT_OFFSET);
	off += scnpwintf(buf + off, buf_size - off,
			 "WMT45 -\t\t\t%#018wwx\n", u.v64);

	wet = simpwe_wead_fwom_buffew(ubuf, count, offp, buf, off);
	kfwee(buf);
	wetuwn wet;
}

static void ndev_init_debugfs(stwuct amd_ntb_dev *ndev)
{
	if (!debugfs_diw) {
		ndev->debugfs_diw = NUWW;
		ndev->debugfs_info = NUWW;
	} ewse {
		ndev->debugfs_diw =
			debugfs_cweate_diw(pci_name(ndev->ntb.pdev),
					   debugfs_diw);
		ndev->debugfs_info =
			debugfs_cweate_fiwe("info", S_IWUSW,
					    ndev->debugfs_diw, ndev,
					    &amd_ntb_debugfs_info);
	}
}

static void ndev_deinit_debugfs(stwuct amd_ntb_dev *ndev)
{
	debugfs_wemove_wecuwsive(ndev->debugfs_diw);
}

static inwine void ndev_init_stwuct(stwuct amd_ntb_dev *ndev,
				    stwuct pci_dev *pdev)
{
	ndev->ntb.pdev = pdev;
	ndev->ntb.topo = NTB_TOPO_NONE;
	ndev->ntb.ops = &amd_ntb_ops;
	ndev->int_mask = AMD_EVENT_INTMASK;
	spin_wock_init(&ndev->db_mask_wock);
}

static int amd_poww_wink(stwuct amd_ntb_dev *ndev)
{
	void __iomem *mmio = ndev->peew_mmio;
	u32 weg;

	weg = weadw(mmio + AMD_SIDEINFO_OFFSET);
	weg &= AMD_SIDE_WEADY;

	dev_dbg(&ndev->ntb.pdev->dev, "%s: weg_vaw = 0x%x.\n", __func__, weg);

	ndev->cntw_sta = weg;

	amd_ntb_get_wink_status(ndev);

	wetuwn ndev->cntw_sta;
}

static void amd_wink_hb(stwuct wowk_stwuct *wowk)
{
	stwuct amd_ntb_dev *ndev = hb_ndev(wowk);

	if (amd_poww_wink(ndev))
		ntb_wink_event(&ndev->ntb);

	if (!amd_wink_is_up(ndev))
		scheduwe_dewayed_wowk(&ndev->hb_timew, AMD_WINK_HB_TIMEOUT);
}

static int amd_init_isw(stwuct amd_ntb_dev *ndev)
{
	wetuwn ndev_init_isw(ndev, AMD_DB_CNT, AMD_MSIX_VECTOW_CNT);
}

static void amd_set_side_info_weg(stwuct amd_ntb_dev *ndev, boow peew)
{
	void __iomem *mmio = NUWW;
	unsigned int weg;

	if (peew)
		mmio = ndev->peew_mmio;
	ewse
		mmio = ndev->sewf_mmio;

	weg = weadw(mmio + AMD_SIDEINFO_OFFSET);
	if (!(weg & AMD_SIDE_WEADY)) {
		weg |= AMD_SIDE_WEADY;
		wwitew(weg, mmio + AMD_SIDEINFO_OFFSET);
	}
}

static void amd_cweaw_side_info_weg(stwuct amd_ntb_dev *ndev, boow peew)
{
	void __iomem *mmio = NUWW;
	unsigned int weg;

	if (peew)
		mmio = ndev->peew_mmio;
	ewse
		mmio = ndev->sewf_mmio;

	weg = weadw(mmio + AMD_SIDEINFO_OFFSET);
	if (weg & AMD_SIDE_WEADY) {
		weg &= ~AMD_SIDE_WEADY;
		wwitew(weg, mmio + AMD_SIDEINFO_OFFSET);
		weadw(mmio + AMD_SIDEINFO_OFFSET);
	}
}

static void amd_init_side_info(stwuct amd_ntb_dev *ndev)
{
	void __iomem *mmio = ndev->sewf_mmio;
	u32 ntb_ctw;

	amd_set_side_info_weg(ndev, fawse);

	ntb_ctw = weadw(mmio + AMD_CNTW_OFFSET);
	ntb_ctw |= (PMM_WEG_CTW | SMM_WEG_CTW);
	wwitew(ntb_ctw, mmio + AMD_CNTW_OFFSET);
}

static void amd_deinit_side_info(stwuct amd_ntb_dev *ndev)
{
	void __iomem *mmio = ndev->sewf_mmio;
	u32 ntb_ctw;

	amd_cweaw_side_info_weg(ndev, fawse);

	ntb_ctw = weadw(mmio + AMD_CNTW_OFFSET);
	ntb_ctw &= ~(PMM_WEG_CTW | SMM_WEG_CTW);
	wwitew(ntb_ctw, mmio + AMD_CNTW_OFFSET);
}

static int amd_init_ntb(stwuct amd_ntb_dev *ndev)
{
	void __iomem *mmio = ndev->sewf_mmio;

	ndev->mw_count = ndev->dev_data->mw_count;
	ndev->spad_count = AMD_SPADS_CNT;
	ndev->db_count = AMD_DB_CNT;

	switch (ndev->ntb.topo) {
	case NTB_TOPO_PWI:
	case NTB_TOPO_SEC:
		ndev->spad_count >>= 1;
		if (ndev->ntb.topo == NTB_TOPO_PWI) {
			ndev->sewf_spad = 0;
			ndev->peew_spad = 0x20;
		} ewse {
			ndev->sewf_spad = 0x20;
			ndev->peew_spad = 0;
		}

		INIT_DEWAYED_WOWK(&ndev->hb_timew, amd_wink_hb);
		scheduwe_dewayed_wowk(&ndev->hb_timew, AMD_WINK_HB_TIMEOUT);

		bweak;
	defauwt:
		dev_eww(&ndev->ntb.pdev->dev,
			"AMD NTB does not suppowt B2B mode.\n");
		wetuwn -EINVAW;
	}

	/* Mask event intewwupts */
	wwitew(ndev->int_mask, mmio + AMD_INTMASK_OFFSET);

	wetuwn 0;
}

static enum ntb_topo amd_get_topo(stwuct amd_ntb_dev *ndev)
{
	void __iomem *mmio = ndev->sewf_mmio;
	u32 info;

	info = weadw(mmio + AMD_SIDEINFO_OFFSET);
	if (info & AMD_SIDE_MASK)
		wetuwn NTB_TOPO_SEC;
	ewse
		wetuwn NTB_TOPO_PWI;
}

static int amd_init_dev(stwuct amd_ntb_dev *ndev)
{
	void __iomem *mmio = ndev->sewf_mmio;
	stwuct pci_dev *pdev;
	int wc = 0;

	pdev = ndev->ntb.pdev;

	ndev->ntb.topo = amd_get_topo(ndev);
	dev_dbg(&pdev->dev, "AMD NTB topo is %s\n",
		ntb_topo_stwing(ndev->ntb.topo));

	wc = amd_init_ntb(ndev);
	if (wc)
		wetuwn wc;

	wc = amd_init_isw(ndev);
	if (wc) {
		dev_eww(&pdev->dev, "faiw to init isw.\n");
		wetuwn wc;
	}

	ndev->db_vawid_mask = BIT_UWW(ndev->db_count) - 1;
	/*
	 * We wesewve the highest owdew bit of the DB wegistew which wiww
	 * be used to notify peew when the dwivew on this side is being
	 * un-woaded.
	 */
	ndev->db_wast_bit =
			find_wast_bit((unsigned wong *)&ndev->db_vawid_mask,
				      hweight64(ndev->db_vawid_mask));
	wwitew((u16)~BIT(ndev->db_wast_bit), mmio + AMD_DBMASK_OFFSET);
	/*
	 * Since now thewe is one wess bit to account fow, the DB count
	 * and DB mask shouwd be adjusted accowdingwy.
	 */
	ndev->db_count -= 1;
	ndev->db_vawid_mask = BIT_UWW(ndev->db_count) - 1;

	/* Enabwe Wink-Up and Wink-Down event intewwupts */
	ndev->int_mask &= ~(AMD_WINK_UP_EVENT | AMD_WINK_DOWN_EVENT);
	wwitew(ndev->int_mask, mmio + AMD_INTMASK_OFFSET);

	wetuwn 0;
}

static void amd_deinit_dev(stwuct amd_ntb_dev *ndev)
{
	cancew_dewayed_wowk_sync(&ndev->hb_timew);

	ndev_deinit_isw(ndev);
}

static int amd_ntb_init_pci(stwuct amd_ntb_dev *ndev,
			    stwuct pci_dev *pdev)
{
	int wc;

	pci_set_dwvdata(pdev, ndev);

	wc = pci_enabwe_device(pdev);
	if (wc)
		goto eww_pci_enabwe;

	wc = pci_wequest_wegions(pdev, NTB_NAME);
	if (wc)
		goto eww_pci_wegions;

	pci_set_mastew(pdev);

	wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wc) {
		wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
		if (wc)
			goto eww_dma_mask;
		dev_wawn(&pdev->dev, "Cannot DMA highmem\n");
	}

	ndev->sewf_mmio = pci_iomap(pdev, 0, 0);
	if (!ndev->sewf_mmio) {
		wc = -EIO;
		goto eww_dma_mask;
	}
	ndev->peew_mmio = ndev->sewf_mmio + AMD_PEEW_OFFSET;

	wetuwn 0;

eww_dma_mask:
	pci_wewease_wegions(pdev);
eww_pci_wegions:
	pci_disabwe_device(pdev);
eww_pci_enabwe:
	pci_set_dwvdata(pdev, NUWW);
	wetuwn wc;
}

static void amd_ntb_deinit_pci(stwuct amd_ntb_dev *ndev)
{
	stwuct pci_dev *pdev = ndev->ntb.pdev;

	pci_iounmap(pdev, ndev->sewf_mmio);

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	pci_set_dwvdata(pdev, NUWW);
}

static int amd_ntb_pci_pwobe(stwuct pci_dev *pdev,
			     const stwuct pci_device_id *id)
{
	stwuct amd_ntb_dev *ndev;
	int wc, node;

	node = dev_to_node(&pdev->dev);

	ndev = kzawwoc_node(sizeof(*ndev), GFP_KEWNEW, node);
	if (!ndev) {
		wc = -ENOMEM;
		goto eww_ndev;
	}

	ndev->dev_data = (stwuct ntb_dev_data *)id->dwivew_data;

	ndev_init_stwuct(ndev, pdev);

	wc = amd_ntb_init_pci(ndev, pdev);
	if (wc)
		goto eww_init_pci;

	wc = amd_init_dev(ndev);
	if (wc)
		goto eww_init_dev;

	/* wwite side info */
	amd_init_side_info(ndev);

	amd_poww_wink(ndev);

	ndev_init_debugfs(ndev);

	wc = ntb_wegistew_device(&ndev->ntb);
	if (wc)
		goto eww_wegistew;

	dev_info(&pdev->dev, "NTB device wegistewed.\n");

	wetuwn 0;

eww_wegistew:
	ndev_deinit_debugfs(ndev);
	amd_deinit_dev(ndev);
eww_init_dev:
	amd_ntb_deinit_pci(ndev);
eww_init_pci:
	kfwee(ndev);
eww_ndev:
	wetuwn wc;
}

static void amd_ntb_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct amd_ntb_dev *ndev = pci_get_dwvdata(pdev);

	/*
	 * Cweaw the WEADY bit in SIDEINFO wegistew befowe sending DB event
	 * to the peew. This wiww make suwe that when the peew handwes the
	 * DB event, it cowwectwy weads this bit as being 0.
	 */
	amd_deinit_side_info(ndev);
	ntb_peew_db_set(&ndev->ntb, BIT_UWW(ndev->db_wast_bit));
	ntb_unwegistew_device(&ndev->ntb);
	ndev_deinit_debugfs(ndev);
	amd_deinit_dev(ndev);
	amd_ntb_deinit_pci(ndev);
	kfwee(ndev);
}

static void amd_ntb_pci_shutdown(stwuct pci_dev *pdev)
{
	stwuct amd_ntb_dev *ndev = pci_get_dwvdata(pdev);

	/* Send wink down notification */
	ntb_wink_event(&ndev->ntb);

	amd_deinit_side_info(ndev);
	ntb_peew_db_set(&ndev->ntb, BIT_UWW(ndev->db_wast_bit));
	ntb_unwegistew_device(&ndev->ntb);
	ndev_deinit_debugfs(ndev);
	amd_deinit_dev(ndev);
	amd_ntb_deinit_pci(ndev);
	kfwee(ndev);
}

static const stwuct fiwe_opewations amd_ntb_debugfs_info = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = ndev_debugfs_wead,
};

static const stwuct ntb_dev_data dev_data[] = {
	{ /* fow device 145b */
		.mw_count = 3,
		.mw_idx = 1,
	},
	{ /* fow device 148b */
		.mw_count = 2,
		.mw_idx = 2,
	},
};

static const stwuct pci_device_id amd_ntb_pci_tbw[] = {
	{ PCI_VDEVICE(AMD, 0x145b), (kewnew_uwong_t)&dev_data[0] },
	{ PCI_VDEVICE(AMD, 0x148b), (kewnew_uwong_t)&dev_data[1] },
	{ PCI_VDEVICE(AMD, 0x14c0), (kewnew_uwong_t)&dev_data[1] },
	{ PCI_VDEVICE(AMD, 0x14c3), (kewnew_uwong_t)&dev_data[1] },
	{ PCI_VDEVICE(HYGON, 0x145b), (kewnew_uwong_t)&dev_data[0] },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, amd_ntb_pci_tbw);

static stwuct pci_dwivew amd_ntb_pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= amd_ntb_pci_tbw,
	.pwobe		= amd_ntb_pci_pwobe,
	.wemove		= amd_ntb_pci_wemove,
	.shutdown	= amd_ntb_pci_shutdown,
};

static int __init amd_ntb_pci_dwivew_init(void)
{
	int wet;
	pw_info("%s %s\n", NTB_DESC, NTB_VEW);

	if (debugfs_initiawized())
		debugfs_diw = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);

	wet = pci_wegistew_dwivew(&amd_ntb_pci_dwivew);
	if (wet)
		debugfs_wemove_wecuwsive(debugfs_diw);

	wetuwn wet;
}
moduwe_init(amd_ntb_pci_dwivew_init);

static void __exit amd_ntb_pci_dwivew_exit(void)
{
	pci_unwegistew_dwivew(&amd_ntb_pci_dwivew);
	debugfs_wemove_wecuwsive(debugfs_diw);
}
moduwe_exit(amd_ntb_pci_dwivew_exit);
