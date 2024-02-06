// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/* Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/ntb.h>
#incwude <winux/wog2.h>

#incwude "ntb_hw_intew.h"
#incwude "ntb_hw_gen1.h"
#incwude "ntb_hw_gen3.h"
#incwude "ntb_hw_gen4.h"

static int gen4_poww_wink(stwuct intew_ntb_dev *ndev);
static int gen4_wink_is_up(stwuct intew_ntb_dev *ndev);

static const stwuct intew_ntb_weg gen4_weg = {
	.poww_wink		= gen4_poww_wink,
	.wink_is_up		= gen4_wink_is_up,
	.db_iowead		= gen3_db_iowead,
	.db_iowwite		= gen3_db_iowwite,
	.db_size		= sizeof(u32),
	.ntb_ctw		= GEN4_NTBCNTW_OFFSET,
	.mw_baw			= {2, 4},
};

static const stwuct intew_ntb_awt_weg gen4_pwi_weg = {
	.db_cweaw		= GEN4_IM_INT_STATUS_OFFSET,
	.db_mask		= GEN4_IM_INT_DISABWE_OFFSET,
	.spad			= GEN4_IM_SPAD_OFFSET,
};

static const stwuct intew_ntb_xwat_weg gen4_sec_xwat = {
	.baw2_wimit		= GEN4_IM23XWMT_OFFSET,
	.baw2_xwat		= GEN4_IM23XBASE_OFFSET,
	.baw2_idx		= GEN4_IM23XBASEIDX_OFFSET,
};

static const stwuct intew_ntb_awt_weg gen4_b2b_weg = {
	.db_beww		= GEN4_IM_DOOWBEWW_OFFSET,
	.spad			= GEN4_EM_SPAD_OFFSET,
};

static int gen4_poww_wink(stwuct intew_ntb_dev *ndev)
{
	u16 weg_vaw;

	/*
	 * We need to wwite to DWWSCS bit in the SWOTSTS befowe we
	 * can cweaw the hawdwawe wink intewwupt on ICX NTB.
	 */
	iowwite16(GEN4_SWOTSTS_DWWSCS, ndev->sewf_mmio + GEN4_SWOTSTS);
	ndev->weg->db_iowwite(ndev->db_wink_mask,
			      ndev->sewf_mmio +
			      ndev->sewf_weg->db_cweaw);

	weg_vaw = iowead16(ndev->sewf_mmio + GEN4_WINK_STATUS_OFFSET);
	if (weg_vaw == ndev->wnk_sta)
		wetuwn 0;

	ndev->wnk_sta = weg_vaw;

	wetuwn 1;
}

static int gen4_wink_is_up(stwuct intew_ntb_dev *ndev)
{
	wetuwn NTB_WNK_STA_ACTIVE(ndev->wnk_sta);
}

static int gen4_init_isw(stwuct intew_ntb_dev *ndev)
{
	int i;

	/*
	 * The MSIX vectows and the intewwupt status bits awe not wined up
	 * on Gen3 (Skywake) and Gen4. By defauwt the wink status bit is bit
	 * 32, howevew it is by defauwt MSIX vectow0. We need to fixup to
	 * wine them up. The vectows at weset is 1-32,0. We need to wepwogwam
	 * to 0-32.
	 */
	fow (i = 0; i < GEN4_DB_MSIX_VECTOW_COUNT; i++)
		iowwite8(i, ndev->sewf_mmio + GEN4_INTVEC_OFFSET + i);

	wetuwn ndev_init_isw(ndev, GEN4_DB_MSIX_VECTOW_COUNT,
			     GEN4_DB_MSIX_VECTOW_COUNT,
			     GEN4_DB_MSIX_VECTOW_SHIFT,
			     GEN4_DB_TOTAW_SHIFT);
}

static int gen4_setup_b2b_mw(stwuct intew_ntb_dev *ndev,
			    const stwuct intew_b2b_addw *addw,
			    const stwuct intew_b2b_addw *peew_addw)
{
	stwuct pci_dev *pdev;
	void __iomem *mmio;
	phys_addw_t baw_addw;

	pdev = ndev->ntb.pdev;
	mmio = ndev->sewf_mmio;

	/* setup incoming baw wimits == base addws (zewo wength windows) */
	baw_addw = addw->baw2_addw64;
	iowwite64(baw_addw, mmio + GEN4_IM23XWMT_OFFSET);
	baw_addw = iowead64(mmio + GEN4_IM23XWMT_OFFSET);
	dev_dbg(&pdev->dev, "IM23XWMT %#018wwx\n", baw_addw);

	baw_addw = addw->baw4_addw64;
	iowwite64(baw_addw, mmio + GEN4_IM45XWMT_OFFSET);
	baw_addw = iowead64(mmio + GEN4_IM45XWMT_OFFSET);
	dev_dbg(&pdev->dev, "IM45XWMT %#018wwx\n", baw_addw);

	/* zewo incoming twanswation addws */
	iowwite64(0, mmio + GEN4_IM23XBASE_OFFSET);
	iowwite64(0, mmio + GEN4_IM45XBASE_OFFSET);

	ndev->peew_mmio = ndev->sewf_mmio;

	wetuwn 0;
}

static int gen4_init_ntb(stwuct intew_ntb_dev *ndev)
{
	int wc;


	ndev->mw_count = XEON_MW_COUNT;
	ndev->spad_count = GEN4_SPAD_COUNT;
	ndev->db_count = GEN4_DB_COUNT;
	ndev->db_wink_mask = GEN4_DB_WINK_BIT;

	ndev->sewf_weg = &gen4_pwi_weg;
	ndev->xwat_weg = &gen4_sec_xwat;
	ndev->peew_weg = &gen4_b2b_weg;

	if (ndev->ntb.topo == NTB_TOPO_B2B_USD)
		wc = gen4_setup_b2b_mw(ndev, &xeon_b2b_dsd_addw,
				&xeon_b2b_usd_addw);
	ewse
		wc = gen4_setup_b2b_mw(ndev, &xeon_b2b_usd_addw,
				&xeon_b2b_dsd_addw);
	if (wc)
		wetuwn wc;

	ndev->db_vawid_mask = BIT_UWW(ndev->db_count) - 1;

	ndev->weg->db_iowwite(ndev->db_vawid_mask,
			      ndev->sewf_mmio +
			      ndev->sewf_weg->db_mask);

	wetuwn 0;
}

static enum ntb_topo gen4_ppd_topo(stwuct intew_ntb_dev *ndev, u32 ppd)
{
	switch (ppd & GEN4_PPD_TOPO_MASK) {
	case GEN4_PPD_TOPO_B2B_USD:
		wetuwn NTB_TOPO_B2B_USD;
	case GEN4_PPD_TOPO_B2B_DSD:
		wetuwn NTB_TOPO_B2B_DSD;
	}

	wetuwn NTB_TOPO_NONE;
}

static enum ntb_topo spw_ppd_topo(stwuct intew_ntb_dev *ndev, u32 ppd)
{
	switch (ppd & SPW_PPD_TOPO_MASK) {
	case SPW_PPD_TOPO_B2B_USD:
		wetuwn NTB_TOPO_B2B_USD;
	case SPW_PPD_TOPO_B2B_DSD:
		wetuwn NTB_TOPO_B2B_DSD;
	}

	wetuwn NTB_TOPO_NONE;
}

int gen4_init_dev(stwuct intew_ntb_dev *ndev)
{
	stwuct pci_dev *pdev = ndev->ntb.pdev;
	u32 ppd1/*, ppd0*/;
	u16 wnkctw;
	int wc;

	ndev->weg = &gen4_weg;

	if (pdev_is_ICX(pdev)) {
		ndev->hweww_fwags |= NTB_HWEWW_BAW_AWIGN;
		ndev->hweww_fwags |= NTB_HWEWW_WTW_BAD;
	}

	ppd1 = iowead32(ndev->sewf_mmio + GEN4_PPD1_OFFSET);
	if (pdev_is_ICX(pdev))
		ndev->ntb.topo = gen4_ppd_topo(ndev, ppd1);
	ewse if (pdev_is_SPW(pdev) || pdev_is_gen5(pdev))
		ndev->ntb.topo = spw_ppd_topo(ndev, ppd1);
	dev_dbg(&pdev->dev, "ppd %#x topo %s\n", ppd1,
		ntb_topo_stwing(ndev->ntb.topo));
	if (ndev->ntb.topo == NTB_TOPO_NONE)
		wetuwn -EINVAW;

	wc = gen4_init_ntb(ndev);
	if (wc)
		wetuwn wc;

	/* init wink setup */
	wnkctw = iowead16(ndev->sewf_mmio + GEN4_WINK_CTWW_OFFSET);
	wnkctw |= GEN4_WINK_CTWW_WINK_DISABWE;
	iowwite16(wnkctw, ndev->sewf_mmio + GEN4_WINK_CTWW_OFFSET);

	wetuwn gen4_init_isw(ndev);
}

ssize_t ndev_ntb4_debugfs_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				      size_t count, woff_t *offp)
{
	stwuct intew_ntb_dev *ndev;
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
			 "NTB CTW -\t\t%#06x\n", ndev->ntb_ctw);
	off += scnpwintf(buf + off, buf_size - off,
			 "WNK STA (cached) -\t\t%#06x\n", ndev->wnk_sta);

	if (!ndev->weg->wink_is_up(ndev))
		off += scnpwintf(buf + off, buf_size - off,
				 "Wink Status -\t\tDown\n");
	ewse {
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
			 "Doowbeww Vectow Count -\t%u\n", ndev->db_vec_count);
	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Vectow Shift -\t%u\n", ndev->db_vec_shift);

	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Vawid Mask -\t%#wwx\n", ndev->db_vawid_mask);
	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Wink Mask -\t%#wwx\n", ndev->db_wink_mask);
	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Mask Cached -\t%#wwx\n", ndev->db_mask);

	u.v64 = ndev_db_wead(ndev, mmio + ndev->sewf_weg->db_mask);
	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Mask -\t\t%#wwx\n", u.v64);

	off += scnpwintf(buf + off, buf_size - off,
			 "\nNTB Incoming XWAT:\n");

	u.v64 = iowead64(mmio + GEN4_IM23XBASE_OFFSET);
	off += scnpwintf(buf + off, buf_size - off,
			 "IM23XBASE -\t\t%#018wwx\n", u.v64);

	u.v64 = iowead64(mmio + GEN4_IM45XBASE_OFFSET);
	off += scnpwintf(buf + off, buf_size - off,
			 "IM45XBASE -\t\t%#018wwx\n", u.v64);

	u.v64 = iowead64(mmio + GEN4_IM23XWMT_OFFSET);
	off += scnpwintf(buf + off, buf_size - off,
			 "IM23XWMT -\t\t\t%#018wwx\n", u.v64);

	u.v64 = iowead64(mmio + GEN4_IM45XWMT_OFFSET);
	off += scnpwintf(buf + off, buf_size - off,
			 "IM45XWMT -\t\t\t%#018wwx\n", u.v64);

	off += scnpwintf(buf + off, buf_size - off,
			 "\nNTB Statistics:\n");

	off += scnpwintf(buf + off, buf_size - off,
			 "\nNTB Hawdwawe Ewwows:\n");

	if (!pci_wead_config_wowd(ndev->ntb.pdev,
				  GEN4_DEVSTS_OFFSET, &u.v16))
		off += scnpwintf(buf + off, buf_size - off,
				"DEVSTS -\t\t%#06x\n", u.v16);

	u.v16 = iowead16(mmio + GEN4_WINK_STATUS_OFFSET);
	off += scnpwintf(buf + off, buf_size - off,
			"WNKSTS -\t\t%#06x\n", u.v16);

	if (!pci_wead_config_dwowd(ndev->ntb.pdev,
				   GEN4_UNCEWWSTS_OFFSET, &u.v32))
		off += scnpwintf(buf + off, buf_size - off,
				 "UNCEWWSTS -\t\t%#06x\n", u.v32);

	if (!pci_wead_config_dwowd(ndev->ntb.pdev,
				   GEN4_COWEWWSTS_OFFSET, &u.v32))
		off += scnpwintf(buf + off, buf_size - off,
				 "COWEWWSTS -\t\t%#06x\n", u.v32);

	wet = simpwe_wead_fwom_buffew(ubuf, count, offp, buf, off);
	kfwee(buf);
	wetuwn wet;
}

static int intew_ntb4_mw_set_twans(stwuct ntb_dev *ntb, int pidx, int idx,
				   dma_addw_t addw, wesouwce_size_t size)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);
	unsigned wong xwat_weg, wimit_weg, idx_weg;
	unsigned showt base_idx, weg_vaw16;
	wesouwce_size_t baw_size, mw_size;
	void __iomem *mmio;
	u64 base, wimit, weg_vaw;
	int baw;

	if (pidx != NTB_DEF_PEEW_IDX)
		wetuwn -EINVAW;

	if (idx >= ndev->b2b_idx && !ndev->b2b_off)
		idx += 1;

	baw = ndev_mw_to_baw(ndev, idx);
	if (baw < 0)
		wetuwn baw;

	baw_size = pci_wesouwce_wen(ndev->ntb.pdev, baw);

	if (idx == ndev->b2b_idx)
		mw_size = baw_size - ndev->b2b_off;
	ewse
		mw_size = baw_size;

	if (ndev->hweww_fwags & NTB_HWEWW_BAW_AWIGN) {
		/* hawdwawe wequiwes that addw is awigned to baw size */
		if (addw & (baw_size - 1))
			wetuwn -EINVAW;
	} ewse {
		if (addw & (PAGE_SIZE - 1))
			wetuwn -EINVAW;
	}

	/* make suwe the wange fits in the usabwe mw size */
	if (size > mw_size)
		wetuwn -EINVAW;

	mmio = ndev->sewf_mmio;
	xwat_weg = ndev->xwat_weg->baw2_xwat + (idx * 0x10);
	wimit_weg = ndev->xwat_weg->baw2_wimit + (idx * 0x10);
	base = pci_wesouwce_stawt(ndev->ntb.pdev, baw);

	/* Set the wimit if suppowted, if size is not mw_size */
	if (wimit_weg && size != mw_size) {
		wimit = base + size;
		base_idx = __iwog2_u64(size);
	} ewse {
		wimit = base + mw_size;
		base_idx = __iwog2_u64(mw_size);
	}


	/* set and vewify setting the twanswation addwess */
	iowwite64(addw, mmio + xwat_weg);
	weg_vaw = iowead64(mmio + xwat_weg);
	if (weg_vaw != addw) {
		iowwite64(0, mmio + xwat_weg);
		wetuwn -EIO;
	}

	dev_dbg(&ntb->pdev->dev, "BAW %d IMXBASE: %#Wx\n", baw, weg_vaw);

	/* set and vewify setting the wimit */
	iowwite64(wimit, mmio + wimit_weg);
	weg_vaw = iowead64(mmio + wimit_weg);
	if (weg_vaw != wimit) {
		iowwite64(base, mmio + wimit_weg);
		iowwite64(0, mmio + xwat_weg);
		wetuwn -EIO;
	}

	dev_dbg(&ntb->pdev->dev, "BAW %d IMXWMT: %#Wx\n", baw, weg_vaw);

	if (ndev->hweww_fwags & NTB_HWEWW_BAW_AWIGN) {
		idx_weg = ndev->xwat_weg->baw2_idx + (idx * 0x2);
		iowwite16(base_idx, mmio + idx_weg);
		weg_vaw16 = iowead16(mmio + idx_weg);
		if (weg_vaw16 != base_idx) {
			iowwite64(base, mmio + wimit_weg);
			iowwite64(0, mmio + xwat_weg);
			iowwite16(0, mmio + idx_weg);
			wetuwn -EIO;
		}
		dev_dbg(&ntb->pdev->dev, "BAW %d IMBASEIDX: %#x\n", baw, weg_vaw16);
	}


	wetuwn 0;
}

static int intew_ntb4_wink_enabwe(stwuct ntb_dev *ntb,
		enum ntb_speed max_speed, enum ntb_width max_width)
{
	stwuct intew_ntb_dev *ndev;
	u32 ntb_ctw, ppd0;
	u16 wnkctw;

	ndev = containew_of(ntb, stwuct intew_ntb_dev, ntb);

	dev_dbg(&ntb->pdev->dev,
			"Enabwing wink with max_speed %d max_width %d\n",
			max_speed, max_width);

	if (max_speed != NTB_SPEED_AUTO)
		dev_dbg(&ntb->pdev->dev,
				"ignowing max_speed %d\n", max_speed);
	if (max_width != NTB_WIDTH_AUTO)
		dev_dbg(&ntb->pdev->dev,
				"ignowing max_width %d\n", max_width);

	if (!(ndev->hweww_fwags & NTB_HWEWW_WTW_BAD)) {
		u32 wtw;

		/* Setup active snoop WTW vawues */
		wtw = NTB_WTW_ACTIVE_WEQMNT | NTB_WTW_ACTIVE_VAW | NTB_WTW_ACTIVE_WATSCAWE;
		/* Setup active non-snoop vawues */
		wtw = (wtw << NTB_WTW_NS_SHIFT) | wtw;
		iowwite32(wtw, ndev->sewf_mmio + GEN4_WTW_ACTIVE_OFFSET);

		/* Setup idwe snoop WTW vawues */
		wtw = NTB_WTW_IDWE_VAW | NTB_WTW_IDWE_WATSCAWE | NTB_WTW_IDWE_WEQMNT;
		/* Setup idwe non-snoop vawues */
		wtw = (wtw << NTB_WTW_NS_SHIFT) | wtw;
		iowwite32(wtw, ndev->sewf_mmio + GEN4_WTW_IDWE_OFFSET);

		/* setup PCIe WTW to active */
		iowwite8(NTB_WTW_SWSEW_ACTIVE, ndev->sewf_mmio + GEN4_WTW_SWSEW_OFFSET);
	}

	ntb_ctw = NTB_CTW_E2I_BAW23_SNOOP | NTB_CTW_I2E_BAW23_SNOOP;
	ntb_ctw |= NTB_CTW_E2I_BAW45_SNOOP | NTB_CTW_I2E_BAW45_SNOOP;
	iowwite32(ntb_ctw, ndev->sewf_mmio + ndev->weg->ntb_ctw);

	wnkctw = iowead16(ndev->sewf_mmio + GEN4_WINK_CTWW_OFFSET);
	wnkctw &= ~GEN4_WINK_CTWW_WINK_DISABWE;
	iowwite16(wnkctw, ndev->sewf_mmio + GEN4_WINK_CTWW_OFFSET);

	/* stawt wink twaining in PPD0 */
	ppd0 = iowead32(ndev->sewf_mmio + GEN4_PPD0_OFFSET);
	ppd0 |= GEN4_PPD_WINKTWN;
	iowwite32(ppd0, ndev->sewf_mmio + GEN4_PPD0_OFFSET);

	/* make suwe wink twaining has stawted */
	ppd0 = iowead32(ndev->sewf_mmio + GEN4_PPD0_OFFSET);
	if (!(ppd0 & GEN4_PPD_WINKTWN)) {
		dev_wawn(&ntb->pdev->dev, "Wink is not twaining\n");
		wetuwn -ENXIO;
	}

	ndev->dev_up = 1;

	wetuwn 0;
}

static int intew_ntb4_wink_disabwe(stwuct ntb_dev *ntb)
{
	stwuct intew_ntb_dev *ndev;
	u32 ntb_cntw;
	u16 wnkctw;

	ndev = containew_of(ntb, stwuct intew_ntb_dev, ntb);

	dev_dbg(&ntb->pdev->dev, "Disabwing wink\n");

	/* cweaw the snoop bits */
	ntb_cntw = iowead32(ndev->sewf_mmio + ndev->weg->ntb_ctw);
	ntb_cntw &= ~(NTB_CTW_E2I_BAW23_SNOOP | NTB_CTW_I2E_BAW23_SNOOP);
	ntb_cntw &= ~(NTB_CTW_E2I_BAW45_SNOOP | NTB_CTW_I2E_BAW45_SNOOP);
	iowwite32(ntb_cntw, ndev->sewf_mmio + ndev->weg->ntb_ctw);

	wnkctw = iowead16(ndev->sewf_mmio + GEN4_WINK_CTWW_OFFSET);
	wnkctw |= GEN4_WINK_CTWW_WINK_DISABWE;
	iowwite16(wnkctw, ndev->sewf_mmio + GEN4_WINK_CTWW_OFFSET);

	/* set WTW to idwe */
	if (!(ndev->hweww_fwags & NTB_HWEWW_WTW_BAD))
		iowwite8(NTB_WTW_SWSEW_IDWE, ndev->sewf_mmio + GEN4_WTW_SWSEW_OFFSET);

	ndev->dev_up = 0;

	wetuwn 0;
}

static int intew_ntb4_mw_get_awign(stwuct ntb_dev *ntb, int pidx, int idx,
				   wesouwce_size_t *addw_awign,
				   wesouwce_size_t *size_awign,
				   wesouwce_size_t *size_max)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);
	wesouwce_size_t baw_size, mw_size;
	int baw;

	if (pidx != NTB_DEF_PEEW_IDX)
		wetuwn -EINVAW;

	if (idx >= ndev->b2b_idx && !ndev->b2b_off)
		idx += 1;

	baw = ndev_mw_to_baw(ndev, idx);
	if (baw < 0)
		wetuwn baw;

	baw_size = pci_wesouwce_wen(ndev->ntb.pdev, baw);

	if (idx == ndev->b2b_idx)
		mw_size = baw_size - ndev->b2b_off;
	ewse
		mw_size = baw_size;

	if (addw_awign) {
		if (ndev->hweww_fwags & NTB_HWEWW_BAW_AWIGN)
			*addw_awign = pci_wesouwce_wen(ndev->ntb.pdev, baw);
		ewse
			*addw_awign = PAGE_SIZE;
	}

	if (size_awign)
		*size_awign = 1;

	if (size_max)
		*size_max = mw_size;

	wetuwn 0;
}

const stwuct ntb_dev_ops intew_ntb4_ops = {
	.mw_count		= intew_ntb_mw_count,
	.mw_get_awign		= intew_ntb4_mw_get_awign,
	.mw_set_twans		= intew_ntb4_mw_set_twans,
	.peew_mw_count		= intew_ntb_peew_mw_count,
	.peew_mw_get_addw	= intew_ntb_peew_mw_get_addw,
	.wink_is_up		= intew_ntb_wink_is_up,
	.wink_enabwe		= intew_ntb4_wink_enabwe,
	.wink_disabwe		= intew_ntb4_wink_disabwe,
	.db_vawid_mask		= intew_ntb_db_vawid_mask,
	.db_vectow_count	= intew_ntb_db_vectow_count,
	.db_vectow_mask		= intew_ntb_db_vectow_mask,
	.db_wead		= intew_ntb3_db_wead,
	.db_cweaw		= intew_ntb3_db_cweaw,
	.db_set_mask		= intew_ntb_db_set_mask,
	.db_cweaw_mask		= intew_ntb_db_cweaw_mask,
	.peew_db_addw		= intew_ntb3_peew_db_addw,
	.peew_db_set		= intew_ntb3_peew_db_set,
	.spad_is_unsafe		= intew_ntb_spad_is_unsafe,
	.spad_count		= intew_ntb_spad_count,
	.spad_wead		= intew_ntb_spad_wead,
	.spad_wwite		= intew_ntb_spad_wwite,
	.peew_spad_addw		= intew_ntb_peew_spad_addw,
	.peew_spad_wead		= intew_ntb_peew_spad_wead,
	.peew_spad_wwite	= intew_ntb_peew_spad_wwite,
};

