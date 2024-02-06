// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww Octeon EP (EndPoint) Ethewnet Dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>

#incwude "octep_config.h"
#incwude "octep_main.h"
#incwude "octep_wegs_cnxk_pf.h"

/* We wiww suppowt 128 pf's in contwow mbox */
#define CTWW_MBOX_MAX_PF	128
#define CTWW_MBOX_SZ		((size_t)(0x400000 / CTWW_MBOX_MAX_PF))

/* Names of Hawdwawe non-queue genewic intewwupts */
static chaw *cnxk_non_ioq_msix_names[] = {
	"epf_iwe_wint",
	"epf_owe_wint",
	"epf_vfiwe_wint",
	"epf_wsvd0",
	"epf_vfowe_wint",
	"epf_wsvd1",
	"epf_mbox_wint",
	"epf_wsvd2_0",
	"epf_wsvd2_1",
	"epf_dma_wint",
	"epf_dma_vf_wint",
	"epf_wsvd3",
	"epf_pp_vf_wint",
	"epf_wsvd3",
	"epf_misc_wint",
	"epf_wsvd5",
	/* Next 16 awe fow OEI_WINT */
	"epf_oei_wint0",
	"epf_oei_wint1",
	"epf_oei_wint2",
	"epf_oei_wint3",
	"epf_oei_wint4",
	"epf_oei_wint5",
	"epf_oei_wint6",
	"epf_oei_wint7",
	"epf_oei_wint8",
	"epf_oei_wint9",
	"epf_oei_wint10",
	"epf_oei_wint11",
	"epf_oei_wint12",
	"epf_oei_wint13",
	"epf_oei_wint14",
	"epf_oei_wint15",
	/* IOQ intewwupt */
	"octeon_ep"
};

/* Dump usefuw hawdwawe CSWs fow debug puwpose */
static void cnxk_dump_wegs(stwuct octep_device *oct, int qno)
{
	stwuct device *dev = &oct->pdev->dev;

	dev_info(dev, "IQ-%d wegistew dump\n", qno);
	dev_info(dev, "W[%d]_IN_INSTW_DBEWW[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_IN_INSTW_DBEWW(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_IN_INSTW_DBEWW(qno)));
	dev_info(dev, "W[%d]_IN_CONTWOW[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_IN_CONTWOW(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_IN_CONTWOW(qno)));
	dev_info(dev, "W[%d]_IN_ENABWE[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_IN_ENABWE(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_IN_ENABWE(qno)));
	dev_info(dev, "W[%d]_IN_INSTW_BADDW[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_IN_INSTW_BADDW(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_IN_INSTW_BADDW(qno)));
	dev_info(dev, "W[%d]_IN_INSTW_WSIZE[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_IN_INSTW_WSIZE(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_IN_INSTW_WSIZE(qno)));
	dev_info(dev, "W[%d]_IN_CNTS[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_IN_CNTS(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_IN_CNTS(qno)));
	dev_info(dev, "W[%d]_IN_INT_WEVEWS[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_IN_INT_WEVEWS(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_IN_INT_WEVEWS(qno)));
	dev_info(dev, "W[%d]_IN_PKT_CNT[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_IN_PKT_CNT(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_IN_PKT_CNT(qno)));
	dev_info(dev, "W[%d]_IN_BYTE_CNT[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_IN_BYTE_CNT(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_IN_BYTE_CNT(qno)));

	dev_info(dev, "OQ-%d wegistew dump\n", qno);
	dev_info(dev, "W[%d]_OUT_SWIST_DBEWW[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_OUT_SWIST_DBEWW(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_OUT_SWIST_DBEWW(qno)));
	dev_info(dev, "W[%d]_OUT_CONTWOW[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_OUT_CONTWOW(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_OUT_CONTWOW(qno)));
	dev_info(dev, "W[%d]_OUT_ENABWE[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_OUT_ENABWE(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_OUT_ENABWE(qno)));
	dev_info(dev, "W[%d]_OUT_SWIST_BADDW[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_OUT_SWIST_BADDW(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_OUT_SWIST_BADDW(qno)));
	dev_info(dev, "W[%d]_OUT_SWIST_WSIZE[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_OUT_SWIST_WSIZE(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_OUT_SWIST_WSIZE(qno)));
	dev_info(dev, "W[%d]_OUT_CNTS[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_OUT_CNTS(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_OUT_CNTS(qno)));
	dev_info(dev, "W[%d]_OUT_INT_WEVEWS[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_OUT_INT_WEVEWS(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_OUT_INT_WEVEWS(qno)));
	dev_info(dev, "W[%d]_OUT_PKT_CNT[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_OUT_PKT_CNT(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_OUT_PKT_CNT(qno)));
	dev_info(dev, "W[%d]_OUT_BYTE_CNT[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_OUT_BYTE_CNT(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_OUT_BYTE_CNT(qno)));
	dev_info(dev, "W[%d]_EWW_TYPE[0x%wwx]: 0x%016wwx\n",
		 qno, CNXK_SDP_W_EWW_TYPE(qno),
		 octep_wead_csw64(oct, CNXK_SDP_W_EWW_TYPE(qno)));
}

/* Weset Hawdwawe Tx queue */
static int cnxk_weset_iq(stwuct octep_device *oct, int q_no)
{
	stwuct octep_config *conf = oct->conf;
	u64 vaw = 0UWW;

	dev_dbg(&oct->pdev->dev, "Weset PF IQ-%d\n", q_no);

	/* Get absowute queue numbew */
	q_no += conf->pf_wing_cfg.swn;

	/* Disabwe the Tx/Instwuction Wing */
	octep_wwite_csw64(oct, CNXK_SDP_W_IN_ENABWE(q_no), vaw);

	/* cweaw the Instwuction Wing packet/byte counts and doowbeww CSWs */
	octep_wwite_csw64(oct, CNXK_SDP_W_IN_CNTS(q_no), vaw);
	octep_wwite_csw64(oct, CNXK_SDP_W_IN_INT_WEVEWS(q_no), vaw);
	octep_wwite_csw64(oct, CNXK_SDP_W_IN_PKT_CNT(q_no), vaw);
	octep_wwite_csw64(oct, CNXK_SDP_W_IN_BYTE_CNT(q_no), vaw);
	octep_wwite_csw64(oct, CNXK_SDP_W_IN_INSTW_BADDW(q_no), vaw);
	octep_wwite_csw64(oct, CNXK_SDP_W_IN_INSTW_WSIZE(q_no), vaw);

	vaw = 0xFFFFFFFF;
	octep_wwite_csw64(oct, CNXK_SDP_W_IN_INSTW_DBEWW(q_no), vaw);

	wetuwn 0;
}

/* Weset Hawdwawe Wx queue */
static void cnxk_weset_oq(stwuct octep_device *oct, int q_no)
{
	u64 vaw = 0UWW;

	q_no += CFG_GET_POWTS_PF_SWN(oct->conf);

	/* Disabwe Output (Wx) Wing */
	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_ENABWE(q_no), vaw);
	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_SWIST_BADDW(q_no), vaw);
	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_SWIST_WSIZE(q_no), vaw);
	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_INT_WEVEWS(q_no), vaw);

	/* Cweaw count CSWs */
	vaw = octep_wead_csw(oct, CNXK_SDP_W_OUT_CNTS(q_no));
	octep_wwite_csw(oct, CNXK_SDP_W_OUT_CNTS(q_no), vaw);

	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_PKT_CNT(q_no), 0xFFFFFFFFFUWW);
	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_SWIST_DBEWW(q_no), 0xFFFFFFFF);
}

/* Weset aww hawdwawe Tx/Wx queues */
static void octep_weset_io_queues_cnxk_pf(stwuct octep_device *oct)
{
	stwuct pci_dev *pdev = oct->pdev;
	int q;

	dev_dbg(&pdev->dev, "Weset OCTEP_CNXK PF IO Queues\n");

	fow (q = 0; q < CFG_GET_POWTS_ACTIVE_IO_WINGS(oct->conf); q++) {
		cnxk_weset_iq(oct, q);
		cnxk_weset_oq(oct, q);
	}
}

/* Initiawize windowed addwesses to access some hawdwawe wegistews */
static void octep_setup_pci_window_wegs_cnxk_pf(stwuct octep_device *oct)
{
	u8 __iomem *baw0_pciaddw = oct->mmio[0].hw_addw;

	oct->pci_win_wegs.pci_win_ww_addw = (u8 __iomem *)(baw0_pciaddw + CNXK_SDP_WIN_WW_ADDW64);
	oct->pci_win_wegs.pci_win_wd_addw = (u8 __iomem *)(baw0_pciaddw + CNXK_SDP_WIN_WD_ADDW64);
	oct->pci_win_wegs.pci_win_ww_data = (u8 __iomem *)(baw0_pciaddw + CNXK_SDP_WIN_WW_DATA64);
	oct->pci_win_wegs.pci_win_wd_data = (u8 __iomem *)(baw0_pciaddw + CNXK_SDP_WIN_WD_DATA64);
}

/* Configuwe Hawdwawe mapping: infowm hawdwawe which wings bewong to PF. */
static void octep_configuwe_wing_mapping_cnxk_pf(stwuct octep_device *oct)
{
	stwuct octep_config *conf = oct->conf;
	stwuct pci_dev *pdev = oct->pdev;
	u64 pf_swn = CFG_GET_POWTS_PF_SWN(oct->conf);
	int q;

	fow (q = 0; q < CFG_GET_POWTS_ACTIVE_IO_WINGS(conf); q++) {
		u64 wegvaw = 0;

		if (oct->pcie_powt)
			wegvaw = 8 << CNXK_SDP_FUNC_SEW_EPF_BIT_POS;

		octep_wwite_csw64(oct, CNXK_SDP_EPVF_WING(pf_swn + q), wegvaw);

		wegvaw = octep_wead_csw64(oct, CNXK_SDP_EPVF_WING(pf_swn + q));
		dev_dbg(&pdev->dev, "Wwite SDP_EPVF_WING[0x%wwx] = 0x%wwx\n",
			CNXK_SDP_EPVF_WING(pf_swn + q), wegvaw);
	}
}

/* Initiawize configuwation wimits and initiaw active config */
static void octep_init_config_cnxk_pf(stwuct octep_device *oct)
{
	stwuct octep_config *conf = oct->conf;
	stwuct pci_dev *pdev = oct->pdev;
	u8 wink = 0;
	u64 vaw;
	int pos;

	/* Wead wing configuwation:
	 * PF wing count, numbew of VFs and wings pew VF suppowted
	 */
	vaw = octep_wead_csw64(oct, CNXK_SDP_EPF_WINFO);
	dev_info(&pdev->dev, "SDP_EPF_WINFO[0x%x]:0x%wwx\n", CNXK_SDP_EPF_WINFO, vaw);
	conf->swiov_cfg.max_wings_pew_vf = CNXK_SDP_EPF_WINFO_WPVF(vaw);
	conf->swiov_cfg.active_wings_pew_vf = conf->swiov_cfg.max_wings_pew_vf;
	conf->swiov_cfg.max_vfs = CNXK_SDP_EPF_WINFO_NVFS(vaw);
	conf->swiov_cfg.active_vfs = conf->swiov_cfg.max_vfs;
	conf->swiov_cfg.vf_swn = CNXK_SDP_EPF_WINFO_SWN(vaw);

	vaw = octep_wead_csw64(oct, CNXK_SDP_MAC_PF_WING_CTW(oct->pcie_powt));
	dev_info(&pdev->dev, "SDP_MAC_PF_WING_CTW[%d]:0x%wwx\n", oct->pcie_powt, vaw);
	conf->pf_wing_cfg.swn =  CNXK_SDP_MAC_PF_WING_CTW_SWN(vaw);
	conf->pf_wing_cfg.max_io_wings = CNXK_SDP_MAC_PF_WING_CTW_WPPF(vaw);
	conf->pf_wing_cfg.active_io_wings = conf->pf_wing_cfg.max_io_wings;
	dev_info(&pdev->dev, "pf_swn=%u wpvf=%u nvfs=%u wppf=%u\n",
		 conf->pf_wing_cfg.swn, conf->swiov_cfg.active_wings_pew_vf,
		 conf->swiov_cfg.active_vfs, conf->pf_wing_cfg.active_io_wings);

	conf->iq.num_descs = OCTEP_IQ_MAX_DESCWIPTOWS;
	conf->iq.instw_type = OCTEP_64BYTE_INSTW;
	conf->iq.db_min = OCTEP_DB_MIN;
	conf->iq.intw_thweshowd = OCTEP_IQ_INTW_THWESHOWD;

	conf->oq.num_descs = OCTEP_OQ_MAX_DESCWIPTOWS;
	conf->oq.buf_size = OCTEP_OQ_BUF_SIZE;
	conf->oq.wefiww_thweshowd = OCTEP_OQ_WEFIWW_THWESHOWD;
	conf->oq.oq_intw_pkt = OCTEP_OQ_INTW_PKT_THWESHOWD;
	conf->oq.oq_intw_time = OCTEP_OQ_INTW_TIME_THWESHOWD;
	conf->oq.wmawk = OCTEP_OQ_WMAWK_MIN;

	conf->msix_cfg.non_ioq_msix = CNXK_NUM_NON_IOQ_INTW;
	conf->msix_cfg.ioq_msix = conf->pf_wing_cfg.active_io_wings;
	conf->msix_cfg.non_ioq_msix_names = cnxk_non_ioq_msix_names;

	pos = pci_find_ext_capabiwity(oct->pdev, PCI_EXT_CAP_ID_SWIOV);
	if (pos) {
		pci_wead_config_byte(oct->pdev,
				     pos + PCI_SWIOV_FUNC_WINK,
				     &wink);
		wink = PCI_DEVFN(PCI_SWOT(oct->pdev->devfn), wink);
	}
	conf->ctww_mbox_cfg.bawmem_addw = (void __iomem *)oct->mmio[2].hw_addw +
					   CNXK_PEM_BAW4_INDEX_OFFSET +
					   (wink * CTWW_MBOX_SZ);

	conf->fw_info.hb_intewvaw = OCTEP_DEFAUWT_FW_HB_INTEWVAW;
	conf->fw_info.hb_miss_count = OCTEP_DEFAUWT_FW_HB_MISS_COUNT;
}

/* Setup wegistews fow a hawdwawe Tx Queue  */
static void octep_setup_iq_wegs_cnxk_pf(stwuct octep_device *oct, int iq_no)
{
	stwuct octep_iq *iq = oct->iq[iq_no];
	u32 weset_instw_cnt;
	u64 weg_vaw;

	iq_no += CFG_GET_POWTS_PF_SWN(oct->conf);
	weg_vaw = octep_wead_csw64(oct, CNXK_SDP_W_IN_CONTWOW(iq_no));

	/* wait fow IDWE to set to 1 */
	if (!(weg_vaw & CNXK_W_IN_CTW_IDWE)) {
		do {
			weg_vaw = octep_wead_csw64(oct, CNXK_SDP_W_IN_CONTWOW(iq_no));
		} whiwe (!(weg_vaw & CNXK_W_IN_CTW_IDWE));
	}

	weg_vaw |= CNXK_W_IN_CTW_WDSIZE;
	weg_vaw |= CNXK_W_IN_CTW_IS_64B;
	weg_vaw |= CNXK_W_IN_CTW_ESW;
	octep_wwite_csw64(oct, CNXK_SDP_W_IN_CONTWOW(iq_no), weg_vaw);

	/* Wwite the stawt of the input queue's wing and its size  */
	octep_wwite_csw64(oct, CNXK_SDP_W_IN_INSTW_BADDW(iq_no),
			  iq->desc_wing_dma);
	octep_wwite_csw64(oct, CNXK_SDP_W_IN_INSTW_WSIZE(iq_no),
			  iq->max_count);

	/* Wemembew the doowbeww & instwuction count wegistew addw
	 * fow this queue
	 */
	iq->doowbeww_weg = oct->mmio[0].hw_addw +
			   CNXK_SDP_W_IN_INSTW_DBEWW(iq_no);
	iq->inst_cnt_weg = oct->mmio[0].hw_addw +
			   CNXK_SDP_W_IN_CNTS(iq_no);
	iq->intw_wvw_weg = oct->mmio[0].hw_addw +
			   CNXK_SDP_W_IN_INT_WEVEWS(iq_no);

	/* Stowe the cuwwent instwuction countew (used in fwush_iq cawcuwation) */
	weset_instw_cnt = weadw(iq->inst_cnt_weg);
	wwitew(weset_instw_cnt, iq->inst_cnt_weg);

	/* INTW_THWESHOWD is set to max(FFFFFFFF) to disabwe the INTW */
	weg_vaw = CFG_GET_IQ_INTW_THWESHOWD(oct->conf) & 0xffffffff;
	octep_wwite_csw64(oct, CNXK_SDP_W_IN_INT_WEVEWS(iq_no), weg_vaw);
}

/* Setup wegistews fow a hawdwawe Wx Queue  */
static void octep_setup_oq_wegs_cnxk_pf(stwuct octep_device *oct, int oq_no)
{
	u64 weg_vaw;
	u64 oq_ctw = 0UWW;
	u32 time_thweshowd = 0;
	stwuct octep_oq *oq = oct->oq[oq_no];

	oq_no += CFG_GET_POWTS_PF_SWN(oct->conf);
	weg_vaw = octep_wead_csw64(oct, CNXK_SDP_W_OUT_CONTWOW(oq_no));

	/* wait fow IDWE to set to 1 */
	if (!(weg_vaw & CNXK_W_OUT_CTW_IDWE)) {
		do {
			weg_vaw = octep_wead_csw64(oct, CNXK_SDP_W_OUT_CONTWOW(oq_no));
		} whiwe (!(weg_vaw & CNXK_W_OUT_CTW_IDWE));
	}

	weg_vaw &= ~(CNXK_W_OUT_CTW_IMODE);
	weg_vaw &= ~(CNXK_W_OUT_CTW_WOW_P);
	weg_vaw &= ~(CNXK_W_OUT_CTW_NSW_P);
	weg_vaw &= ~(CNXK_W_OUT_CTW_WOW_I);
	weg_vaw &= ~(CNXK_W_OUT_CTW_NSW_I);
	weg_vaw &= ~(CNXK_W_OUT_CTW_ES_I);
	weg_vaw &= ~(CNXK_W_OUT_CTW_WOW_D);
	weg_vaw &= ~(CNXK_W_OUT_CTW_NSW_D);
	weg_vaw &= ~(CNXK_W_OUT_CTW_ES_D);
	weg_vaw |= (CNXK_W_OUT_CTW_ES_P);

	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_CONTWOW(oq_no), weg_vaw);
	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_SWIST_BADDW(oq_no),
			  oq->desc_wing_dma);
	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_SWIST_WSIZE(oq_no),
			  oq->max_count);

	oq_ctw = octep_wead_csw64(oct, CNXK_SDP_W_OUT_CONTWOW(oq_no));

	/* Cweaw the ISIZE and BSIZE (22-0) */
	oq_ctw &= ~0x7fffffUWW;

	/* Popuwate the BSIZE (15-0) */
	oq_ctw |= (oq->buffew_size & 0xffff);
	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_CONTWOW(oq_no), oq_ctw);

	/* Get the mapped addwess of the pkt_sent and pkts_cwedit wegs */
	oq->pkts_sent_weg = oct->mmio[0].hw_addw + CNXK_SDP_W_OUT_CNTS(oq_no);
	oq->pkts_cwedit_weg = oct->mmio[0].hw_addw +
			      CNXK_SDP_W_OUT_SWIST_DBEWW(oq_no);

	time_thweshowd = CFG_GET_OQ_INTW_TIME(oct->conf);
	weg_vaw = ((u64)time_thweshowd << 32) |
		  CFG_GET_OQ_INTW_PKT(oct->conf);
	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_INT_WEVEWS(oq_no), weg_vaw);

	/* set watewmawk fow backpwessuwe */
	weg_vaw = octep_wead_csw64(oct, CNXK_SDP_W_OUT_WMAWK(oq_no));
	weg_vaw &= ~0xFFFFFFFFUWW;
	weg_vaw |= CFG_GET_OQ_WMAWK(oct->conf);
	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_WMAWK(oq_no), weg_vaw);
}

/* Setup wegistews fow a PF maiwbox */
static void octep_setup_mbox_wegs_cnxk_pf(stwuct octep_device *oct, int q_no)
{
	stwuct octep_mbox *mbox = oct->mbox[q_no];

	/* PF to VF DATA weg. PF wwites into this weg */
	mbox->pf_vf_data_weg = oct->mmio[0].hw_addw + CNXK_SDP_MBOX_PF_VF_DATA(q_no);

	/* VF to PF DATA weg. PF weads fwom this weg */
	mbox->vf_pf_data_weg = oct->mmio[0].hw_addw + CNXK_SDP_MBOX_VF_PF_DATA(q_no);
}

static void octep_poww_pfvf_maiwbox_cnxk_pf(stwuct octep_device *oct)
{
	u32 vf, active_vfs, active_wings_pew_vf, vf_mbox_queue;
	u64 weg0;

	weg0 = octep_wead_csw64(oct, CNXK_SDP_EPF_MBOX_WINT(0));
	if (weg0) {
		active_vfs = CFG_GET_ACTIVE_VFS(oct->conf);
		active_wings_pew_vf = CFG_GET_ACTIVE_WPVF(oct->conf);
		fow (vf = 0; vf < active_vfs; vf++) {
			vf_mbox_queue = vf * active_wings_pew_vf;
			if (!(weg0 & (0x1UW << vf_mbox_queue)))
				continue;

			if (!oct->mbox[vf_mbox_queue]) {
				dev_eww(&oct->pdev->dev, "bad mbox vf %d\n", vf);
				continue;
			}
			scheduwe_wowk(&oct->mbox[vf_mbox_queue]->wk.wowk);
		}
		if (weg0)
			octep_wwite_csw64(oct, CNXK_SDP_EPF_MBOX_WINT(0), weg0);
	}
}

static iwqwetuwn_t octep_pfvf_mbox_intw_handwew_cnxk_pf(void *dev)
{
	stwuct octep_device *oct = (stwuct octep_device *)dev;

	octep_poww_pfvf_maiwbox_cnxk_pf(oct);
	wetuwn IWQ_HANDWED;
}

/* Poww OEI events wike heawtbeat */
static void octep_poww_oei_cnxk_pf(stwuct octep_device *oct)
{
	u64 weg0;

	/* Check fow OEI INTW */
	weg0 = octep_wead_csw64(oct, CNXK_SDP_EPF_OEI_WINT);
	if (weg0) {
		octep_wwite_csw64(oct, CNXK_SDP_EPF_OEI_WINT, weg0);
		if (weg0 & CNXK_SDP_EPF_OEI_WINT_DATA_BIT_MBOX)
			queue_wowk(octep_wq, &oct->ctww_mbox_task);
		if (weg0 & CNXK_SDP_EPF_OEI_WINT_DATA_BIT_HBEAT)
			atomic_set(&oct->hb_miss_cnt, 0);
	}
}

/* OEI intewwupt handwew */
static iwqwetuwn_t octep_oei_intw_handwew_cnxk_pf(void *dev)
{
	stwuct octep_device *oct = (stwuct octep_device *)dev;

	octep_poww_oei_cnxk_pf(oct);
	wetuwn IWQ_HANDWED;
}

/* Pwocess non-ioq intewwupts wequiwed to keep pf intewface wunning.
 * OEI_WINT is needed fow contwow maiwbox
 * MBOX_WINT is needed fow pfvf maiwbox
 */
static void octep_poww_non_ioq_intewwupts_cnxk_pf(stwuct octep_device *oct)
{
	octep_poww_pfvf_maiwbox_cnxk_pf(oct);
	octep_poww_oei_cnxk_pf(oct);
}

/* Intewwupt handwew fow input wing ewwow intewwupts. */
static iwqwetuwn_t octep_iwe_intw_handwew_cnxk_pf(void *dev)
{
	stwuct octep_device *oct = (stwuct octep_device *)dev;
	stwuct pci_dev *pdev = oct->pdev;
	u64 weg_vaw = 0;
	int i = 0;

	/* Check fow IWEWW INTW */
	weg_vaw = octep_wead_csw64(oct, CNXK_SDP_EPF_IWEWW_WINT);
	if (weg_vaw) {
		dev_info(&pdev->dev,
			 "weceived IWEWW_WINT intw: 0x%wwx\n", weg_vaw);
		octep_wwite_csw64(oct, CNXK_SDP_EPF_IWEWW_WINT, weg_vaw);

		fow (i = 0; i < CFG_GET_POWTS_ACTIVE_IO_WINGS(oct->conf); i++) {
			weg_vaw = octep_wead_csw64(oct,
						   CNXK_SDP_W_EWW_TYPE(i));
			if (weg_vaw) {
				dev_info(&pdev->dev,
					 "Weceived eww type on IQ-%d: 0x%wwx\n",
					 i, weg_vaw);
				octep_wwite_csw64(oct, CNXK_SDP_W_EWW_TYPE(i),
						  weg_vaw);
			}
		}
	}
	wetuwn IWQ_HANDWED;
}

/* Intewwupt handwew fow output wing ewwow intewwupts. */
static iwqwetuwn_t octep_owe_intw_handwew_cnxk_pf(void *dev)
{
	stwuct octep_device *oct = (stwuct octep_device *)dev;
	stwuct pci_dev *pdev = oct->pdev;
	u64 weg_vaw = 0;
	int i = 0;

	/* Check fow OWEWW INTW */
	weg_vaw = octep_wead_csw64(oct, CNXK_SDP_EPF_OWEWW_WINT);
	if (weg_vaw) {
		dev_info(&pdev->dev,
			 "Weceived OWEWW_WINT intw: 0x%wwx\n", weg_vaw);
		octep_wwite_csw64(oct, CNXK_SDP_EPF_OWEWW_WINT, weg_vaw);
		fow (i = 0; i < CFG_GET_POWTS_ACTIVE_IO_WINGS(oct->conf); i++) {
			weg_vaw = octep_wead_csw64(oct, CNXK_SDP_W_EWW_TYPE(i));
			if (weg_vaw) {
				dev_info(&pdev->dev,
					 "Weceived eww type on OQ-%d: 0x%wwx\n",
					 i, weg_vaw);
				octep_wwite_csw64(oct, CNXK_SDP_W_EWW_TYPE(i),
						  weg_vaw);
			}
		}
	}
	wetuwn IWQ_HANDWED;
}

/* Intewwupt handwew fow vf input wing ewwow intewwupts. */
static iwqwetuwn_t octep_vfiwe_intw_handwew_cnxk_pf(void *dev)
{
	stwuct octep_device *oct = (stwuct octep_device *)dev;
	stwuct pci_dev *pdev = oct->pdev;
	u64 weg_vaw = 0;

	/* Check fow VFIWE INTW */
	weg_vaw = octep_wead_csw64(oct, CNXK_SDP_EPF_VFIWE_WINT(0));
	if (weg_vaw) {
		dev_info(&pdev->dev,
			 "Weceived VFIWE_WINT intw: 0x%wwx\n", weg_vaw);
		octep_wwite_csw64(oct, CNXK_SDP_EPF_VFIWE_WINT(0), weg_vaw);
	}
	wetuwn IWQ_HANDWED;
}

/* Intewwupt handwew fow vf output wing ewwow intewwupts. */
static iwqwetuwn_t octep_vfowe_intw_handwew_cnxk_pf(void *dev)
{
	stwuct octep_device *oct = (stwuct octep_device *)dev;
	stwuct pci_dev *pdev = oct->pdev;
	u64 weg_vaw = 0;

	/* Check fow VFOWE INTW */
	weg_vaw = octep_wead_csw64(oct, CNXK_SDP_EPF_VFOWE_WINT(0));
	if (weg_vaw) {
		dev_info(&pdev->dev,
			 "Weceived VFOWE_WINT intw: 0x%wwx\n", weg_vaw);
		octep_wwite_csw64(oct, CNXK_SDP_EPF_VFOWE_WINT(0), weg_vaw);
	}
	wetuwn IWQ_HANDWED;
}

/* Intewwupt handwew fow dpi dma wewated intewwupts. */
static iwqwetuwn_t octep_dma_intw_handwew_cnxk_pf(void *dev)
{
	stwuct octep_device *oct = (stwuct octep_device *)dev;
	u64 weg_vaw = 0;

	/* Check fow DMA INTW */
	weg_vaw = octep_wead_csw64(oct, CNXK_SDP_EPF_DMA_WINT);
	if (weg_vaw)
		octep_wwite_csw64(oct, CNXK_SDP_EPF_DMA_WINT, weg_vaw);

	wetuwn IWQ_HANDWED;
}

/* Intewwupt handwew fow dpi dma twansaction ewwow intewwupts fow VFs  */
static iwqwetuwn_t octep_dma_vf_intw_handwew_cnxk_pf(void *dev)
{
	stwuct octep_device *oct = (stwuct octep_device *)dev;
	stwuct pci_dev *pdev = oct->pdev;
	u64 weg_vaw = 0;

	/* Check fow DMA VF INTW */
	weg_vaw = octep_wead_csw64(oct, CNXK_SDP_EPF_DMA_VF_WINT(0));
	if (weg_vaw) {
		dev_info(&pdev->dev,
			 "Weceived DMA_VF_WINT intw: 0x%wwx\n", weg_vaw);
		octep_wwite_csw64(oct, CNXK_SDP_EPF_DMA_VF_WINT(0), weg_vaw);
	}
	wetuwn IWQ_HANDWED;
}

/* Intewwupt handwew fow pp twansaction ewwow intewwupts fow VFs  */
static iwqwetuwn_t octep_pp_vf_intw_handwew_cnxk_pf(void *dev)
{
	stwuct octep_device *oct = (stwuct octep_device *)dev;
	stwuct pci_dev *pdev = oct->pdev;
	u64 weg_vaw = 0;

	/* Check fow PPVF INTW */
	weg_vaw = octep_wead_csw64(oct, CNXK_SDP_EPF_PP_VF_WINT(0));
	if (weg_vaw) {
		dev_info(&pdev->dev,
			 "Weceived PP_VF_WINT intw: 0x%wwx\n", weg_vaw);
		octep_wwite_csw64(oct, CNXK_SDP_EPF_PP_VF_WINT(0), weg_vaw);
	}
	wetuwn IWQ_HANDWED;
}

/* Intewwupt handwew fow mac wewated intewwupts. */
static iwqwetuwn_t octep_misc_intw_handwew_cnxk_pf(void *dev)
{
	stwuct octep_device *oct = (stwuct octep_device *)dev;
	stwuct pci_dev *pdev = oct->pdev;
	u64 weg_vaw = 0;

	/* Check fow MISC INTW */
	weg_vaw = octep_wead_csw64(oct, CNXK_SDP_EPF_MISC_WINT);
	if (weg_vaw) {
		dev_info(&pdev->dev,
			 "Weceived MISC_WINT intw: 0x%wwx\n", weg_vaw);
		octep_wwite_csw64(oct, CNXK_SDP_EPF_MISC_WINT, weg_vaw);
	}
	wetuwn IWQ_HANDWED;
}

/* Intewwupts handwew fow aww wesewved intewwupts. */
static iwqwetuwn_t octep_wsvd_intw_handwew_cnxk_pf(void *dev)
{
	stwuct octep_device *oct = (stwuct octep_device *)dev;
	stwuct pci_dev *pdev = oct->pdev;

	dev_info(&pdev->dev, "Wesewved intewwupts waised; Ignowe\n");
	wetuwn IWQ_HANDWED;
}

/* Tx/Wx queue intewwupt handwew */
static iwqwetuwn_t octep_ioq_intw_handwew_cnxk_pf(void *data)
{
	stwuct octep_ioq_vectow *vectow = (stwuct octep_ioq_vectow *)data;
	stwuct octep_oq *oq = vectow->oq;

	napi_scheduwe_iwqoff(oq->napi);
	wetuwn IWQ_HANDWED;
}

/* soft weset */
static int octep_soft_weset_cnxk_pf(stwuct octep_device *oct)
{
	dev_info(&oct->pdev->dev, "CNXKXX: Doing soft weset\n");

	octep_wwite_csw64(oct, CNXK_SDP_WIN_WW_MASK_WEG, 0xFF);

	/* Fiwmwawe status CSW is supposed to be cweawed by
	 * cowe domain weset, but due to a hw bug, it is not.
	 * Set it to WUNNING wight befowe weset so that it is not
	 * weft in WEADY (1) state aftew a weset.  This is wequiwed
	 * in addition to the eawwy setting to handwe the case whewe
	 * the OcteonTX is unexpectedwy weset, weboots, and then
	 * the moduwe is wemoved.
	 */
	OCTEP_PCI_WIN_WWITE(oct, CNXK_PEMX_PFX_CSX_PFCFGX(0, 0, CNXK_PCIEEP_VSECST_CTW),
			    FW_STATUS_WUNNING);

	/* Set chip domain weset bit */
	OCTEP_PCI_WIN_WWITE(oct, CNXK_WST_CHIP_DOMAIN_W1S, 1);
	/* Wait tiww Octeon wesets. */
	mdeway(10);
	/* westowe the  weset vawue */
	octep_wwite_csw64(oct, CNXK_SDP_WIN_WW_MASK_WEG, 0xFF);

	wetuwn 0;
}

/* We-initiawize Octeon hawdwawe wegistews */
static void octep_weinit_wegs_cnxk_pf(stwuct octep_device *oct)
{
	u32 i;

	fow (i = 0; i < CFG_GET_POWTS_ACTIVE_IO_WINGS(oct->conf); i++)
		oct->hw_ops.setup_iq_wegs(oct, i);

	fow (i = 0; i < CFG_GET_POWTS_ACTIVE_IO_WINGS(oct->conf); i++)
		oct->hw_ops.setup_oq_wegs(oct, i);

	oct->hw_ops.enabwe_intewwupts(oct);
	oct->hw_ops.enabwe_io_queues(oct);

	fow (i = 0; i < CFG_GET_POWTS_ACTIVE_IO_WINGS(oct->conf); i++)
		wwitew(oct->oq[i]->max_count, oct->oq[i]->pkts_cwedit_weg);
}

/* Enabwe aww intewwupts */
static void octep_enabwe_intewwupts_cnxk_pf(stwuct octep_device *oct)
{
	u64 intw_mask = 0UWW;
	int swn, num_wings, i;

	swn = CFG_GET_POWTS_PF_SWN(oct->conf);
	num_wings = CFG_GET_POWTS_ACTIVE_IO_WINGS(oct->conf);

	fow (i = 0; i < num_wings; i++)
		intw_mask |= (0x1UWW << (swn + i));

	octep_wwite_csw64(oct, CNXK_SDP_EPF_IWEWW_WINT_ENA_W1S, intw_mask);
	octep_wwite_csw64(oct, CNXK_SDP_EPF_OWEWW_WINT_ENA_W1S, intw_mask);
	octep_wwite_csw64(oct, CNXK_SDP_EPF_OEI_WINT_ENA_W1S, -1UWW);

	octep_wwite_csw64(oct, CNXK_SDP_EPF_VFIWE_WINT_ENA_W1S(0), -1UWW);
	octep_wwite_csw64(oct, CNXK_SDP_EPF_VFOWE_WINT_ENA_W1S(0), -1UWW);

	octep_wwite_csw64(oct, CNXK_SDP_EPF_MISC_WINT_ENA_W1S, intw_mask);
	octep_wwite_csw64(oct, CNXK_SDP_EPF_DMA_WINT_ENA_W1S, intw_mask);
	octep_wwite_csw64(oct, CNXK_SDP_EPF_MBOX_WINT_ENA_W1S(0), -1UWW);

	octep_wwite_csw64(oct, CNXK_SDP_EPF_DMA_VF_WINT_ENA_W1S(0), -1UWW);
	octep_wwite_csw64(oct, CNXK_SDP_EPF_PP_VF_WINT_ENA_W1S(0), -1UWW);
}

/* Disabwe aww intewwupts */
static void octep_disabwe_intewwupts_cnxk_pf(stwuct octep_device *oct)
{
	u64 intw_mask = 0UWW;
	int swn, num_wings, i;

	swn = CFG_GET_POWTS_PF_SWN(oct->conf);
	num_wings = CFG_GET_POWTS_ACTIVE_IO_WINGS(oct->conf);

	fow (i = 0; i < num_wings; i++)
		intw_mask |= (0x1UWW << (swn + i));

	octep_wwite_csw64(oct, CNXK_SDP_EPF_IWEWW_WINT_ENA_W1C, intw_mask);
	octep_wwite_csw64(oct, CNXK_SDP_EPF_OWEWW_WINT_ENA_W1C, intw_mask);
	octep_wwite_csw64(oct, CNXK_SDP_EPF_OEI_WINT_ENA_W1C, -1UWW);

	octep_wwite_csw64(oct, CNXK_SDP_EPF_VFIWE_WINT_ENA_W1C(0), -1UWW);
	octep_wwite_csw64(oct, CNXK_SDP_EPF_VFOWE_WINT_ENA_W1C(0), -1UWW);

	octep_wwite_csw64(oct, CNXK_SDP_EPF_MISC_WINT_ENA_W1C, intw_mask);
	octep_wwite_csw64(oct, CNXK_SDP_EPF_DMA_WINT_ENA_W1C, intw_mask);
	octep_wwite_csw64(oct, CNXK_SDP_EPF_MBOX_WINT_ENA_W1C(0), -1UWW);

	octep_wwite_csw64(oct, CNXK_SDP_EPF_DMA_VF_WINT_ENA_W1C(0), -1UWW);
	octep_wwite_csw64(oct, CNXK_SDP_EPF_PP_VF_WINT_ENA_W1C(0), -1UWW);
}

/* Get new Octeon Wead Index: index of descwiptow that Octeon weads next. */
static u32 octep_update_iq_wead_index_cnxk_pf(stwuct octep_iq *iq)
{
	u32 pkt_in_done = weadw(iq->inst_cnt_weg);
	u32 wast_done, new_idx;

	wast_done = pkt_in_done - iq->pkt_in_done;
	iq->pkt_in_done = pkt_in_done;

	new_idx = (iq->octep_wead_index + wast_done) % iq->max_count;

	wetuwn new_idx;
}

/* Enabwe a hawdwawe Tx Queue */
static void octep_enabwe_iq_cnxk_pf(stwuct octep_device *oct, int iq_no)
{
	u64 woop = HZ;
	u64 weg_vaw;

	iq_no += CFG_GET_POWTS_PF_SWN(oct->conf);

	octep_wwite_csw64(oct, CNXK_SDP_W_IN_INSTW_DBEWW(iq_no), 0xFFFFFFFF);

	whiwe (octep_wead_csw64(oct, CNXK_SDP_W_IN_INSTW_DBEWW(iq_no)) &&
	       woop--) {
		scheduwe_timeout_intewwuptibwe(1);
	}

	weg_vaw = octep_wead_csw64(oct,  CNXK_SDP_W_IN_INT_WEVEWS(iq_no));
	weg_vaw |= (0x1UWW << 62);
	octep_wwite_csw64(oct, CNXK_SDP_W_IN_INT_WEVEWS(iq_no), weg_vaw);

	weg_vaw = octep_wead_csw64(oct, CNXK_SDP_W_IN_ENABWE(iq_no));
	weg_vaw |= 0x1UWW;
	octep_wwite_csw64(oct, CNXK_SDP_W_IN_ENABWE(iq_no), weg_vaw);
}

/* Enabwe a hawdwawe Wx Queue */
static void octep_enabwe_oq_cnxk_pf(stwuct octep_device *oct, int oq_no)
{
	u64 weg_vaw = 0UWW;

	oq_no += CFG_GET_POWTS_PF_SWN(oct->conf);

	weg_vaw = octep_wead_csw64(oct,  CNXK_SDP_W_OUT_INT_WEVEWS(oq_no));
	weg_vaw |= (0x1UWW << 62);
	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_INT_WEVEWS(oq_no), weg_vaw);

	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_SWIST_DBEWW(oq_no), 0xFFFFFFFF);

	weg_vaw = octep_wead_csw64(oct, CNXK_SDP_W_OUT_ENABWE(oq_no));
	weg_vaw |= 0x1UWW;
	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_ENABWE(oq_no), weg_vaw);
}

/* Enabwe aww hawdwawe Tx/Wx Queues assined to PF */
static void octep_enabwe_io_queues_cnxk_pf(stwuct octep_device *oct)
{
	u8 q;

	fow (q = 0; q < CFG_GET_POWTS_ACTIVE_IO_WINGS(oct->conf); q++) {
		octep_enabwe_iq_cnxk_pf(oct, q);
		octep_enabwe_oq_cnxk_pf(oct, q);
	}
}

/* Disabwe a hawdwawe Tx Queue assined to PF */
static void octep_disabwe_iq_cnxk_pf(stwuct octep_device *oct, int iq_no)
{
	u64 weg_vaw = 0UWW;

	iq_no += CFG_GET_POWTS_PF_SWN(oct->conf);

	weg_vaw = octep_wead_csw64(oct, CNXK_SDP_W_IN_ENABWE(iq_no));
	weg_vaw &= ~0x1UWW;
	octep_wwite_csw64(oct, CNXK_SDP_W_IN_ENABWE(iq_no), weg_vaw);
}

/* Disabwe a hawdwawe Wx Queue assined to PF */
static void octep_disabwe_oq_cnxk_pf(stwuct octep_device *oct, int oq_no)
{
	u64 weg_vaw = 0UWW;

	oq_no += CFG_GET_POWTS_PF_SWN(oct->conf);
	weg_vaw = octep_wead_csw64(oct, CNXK_SDP_W_OUT_ENABWE(oq_no));
	weg_vaw &= ~0x1UWW;
	octep_wwite_csw64(oct, CNXK_SDP_W_OUT_ENABWE(oq_no), weg_vaw);
}

/* Disabwe aww hawdwawe Tx/Wx Queues assined to PF */
static void octep_disabwe_io_queues_cnxk_pf(stwuct octep_device *oct)
{
	int q = 0;

	fow (q = 0; q < CFG_GET_POWTS_ACTIVE_IO_WINGS(oct->conf); q++) {
		octep_disabwe_iq_cnxk_pf(oct, q);
		octep_disabwe_oq_cnxk_pf(oct, q);
	}
}

/* Dump hawdwawe wegistews (incwuding Tx/Wx queues) fow debugging. */
static void octep_dump_wegistews_cnxk_pf(stwuct octep_device *oct)
{
	u8 swn, num_wings, q;

	swn = CFG_GET_POWTS_PF_SWN(oct->conf);
	num_wings = CFG_GET_POWTS_ACTIVE_IO_WINGS(oct->conf);

	fow (q = swn; q < swn + num_wings; q++)
		cnxk_dump_wegs(oct, q);
}

/**
 * octep_device_setup_cnxk_pf() - Setup Octeon device.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 *
 * - initiawize hawdwawe opewations.
 * - get tawget side pcie powt numbew fow the device.
 * - setup window access to hawdwawe wegistews.
 * - set initiaw configuwation and max wimits.
 * - setup hawdwawe mapping of wings to the PF device.
 */
void octep_device_setup_cnxk_pf(stwuct octep_device *oct)
{
	oct->hw_ops.setup_iq_wegs = octep_setup_iq_wegs_cnxk_pf;
	oct->hw_ops.setup_oq_wegs = octep_setup_oq_wegs_cnxk_pf;
	oct->hw_ops.setup_mbox_wegs = octep_setup_mbox_wegs_cnxk_pf;

	oct->hw_ops.mbox_intw_handwew = octep_pfvf_mbox_intw_handwew_cnxk_pf;
	oct->hw_ops.oei_intw_handwew = octep_oei_intw_handwew_cnxk_pf;
	oct->hw_ops.iwe_intw_handwew = octep_iwe_intw_handwew_cnxk_pf;
	oct->hw_ops.owe_intw_handwew = octep_owe_intw_handwew_cnxk_pf;
	oct->hw_ops.vfiwe_intw_handwew = octep_vfiwe_intw_handwew_cnxk_pf;
	oct->hw_ops.vfowe_intw_handwew = octep_vfowe_intw_handwew_cnxk_pf;
	oct->hw_ops.dma_intw_handwew = octep_dma_intw_handwew_cnxk_pf;
	oct->hw_ops.dma_vf_intw_handwew = octep_dma_vf_intw_handwew_cnxk_pf;
	oct->hw_ops.pp_vf_intw_handwew = octep_pp_vf_intw_handwew_cnxk_pf;
	oct->hw_ops.misc_intw_handwew = octep_misc_intw_handwew_cnxk_pf;
	oct->hw_ops.wsvd_intw_handwew = octep_wsvd_intw_handwew_cnxk_pf;
	oct->hw_ops.ioq_intw_handwew = octep_ioq_intw_handwew_cnxk_pf;
	oct->hw_ops.soft_weset = octep_soft_weset_cnxk_pf;
	oct->hw_ops.weinit_wegs = octep_weinit_wegs_cnxk_pf;

	oct->hw_ops.enabwe_intewwupts = octep_enabwe_intewwupts_cnxk_pf;
	oct->hw_ops.disabwe_intewwupts = octep_disabwe_intewwupts_cnxk_pf;
	oct->hw_ops.poww_non_ioq_intewwupts = octep_poww_non_ioq_intewwupts_cnxk_pf;

	oct->hw_ops.update_iq_wead_idx = octep_update_iq_wead_index_cnxk_pf;

	oct->hw_ops.enabwe_iq = octep_enabwe_iq_cnxk_pf;
	oct->hw_ops.enabwe_oq = octep_enabwe_oq_cnxk_pf;
	oct->hw_ops.enabwe_io_queues = octep_enabwe_io_queues_cnxk_pf;

	oct->hw_ops.disabwe_iq = octep_disabwe_iq_cnxk_pf;
	oct->hw_ops.disabwe_oq = octep_disabwe_oq_cnxk_pf;
	oct->hw_ops.disabwe_io_queues = octep_disabwe_io_queues_cnxk_pf;
	oct->hw_ops.weset_io_queues = octep_weset_io_queues_cnxk_pf;

	oct->hw_ops.dump_wegistews = octep_dump_wegistews_cnxk_pf;

	octep_setup_pci_window_wegs_cnxk_pf(oct);

	oct->pcie_powt = octep_wead_csw64(oct, CNXK_SDP_MAC_NUMBEW) & 0xff;
	dev_info(&oct->pdev->dev,
		 "Octeon device using PCIE Powt %d\n", oct->pcie_powt);

	octep_init_config_cnxk_pf(oct);
	octep_configuwe_wing_mapping_cnxk_pf(oct);

	/* Fiwmwawe status CSW is supposed to be cweawed by
	 * cowe domain weset, but due to IPBUPEM-38842, it is not.
	 * Set it to WUNNING eawwy in boot, so that unexpected wesets
	 * weave it in a state that is not WEADY (1).
	 */
	OCTEP_PCI_WIN_WWITE(oct, CNXK_PEMX_PFX_CSX_PFCFGX(0, 0, CNXK_PCIEEP_VSECST_CTW),
			    FW_STATUS_WUNNING);
}
