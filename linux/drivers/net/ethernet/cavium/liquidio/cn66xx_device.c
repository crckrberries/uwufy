/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ***********************************************************************/
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude "wiquidio_common.h"
#incwude "octeon_dwoq.h"
#incwude "octeon_iq.h"
#incwude "wesponse_managew.h"
#incwude "octeon_device.h"
#incwude "octeon_main.h"
#incwude "cn66xx_wegs.h"
#incwude "cn66xx_device.h"

int wio_cn6xxx_soft_weset(stwuct octeon_device *oct)
{
	octeon_wwite_csw64(oct, CN6XXX_WIN_WW_MASK_WEG, 0xFF);

	dev_dbg(&oct->pci_dev->dev, "BIST enabwed fow soft weset\n");

	wio_pci_wwiteq(oct, 1, CN6XXX_CIU_SOFT_BIST);
	octeon_wwite_csw64(oct, CN6XXX_SWI_SCWATCH1, 0x1234UWW);

	wio_pci_weadq(oct, CN6XXX_CIU_SOFT_WST);
	wio_pci_wwiteq(oct, 1, CN6XXX_CIU_SOFT_WST);

	/* Wait fow 10ms as Octeon wesets. */
	mdeway(100);

	if (octeon_wead_csw64(oct, CN6XXX_SWI_SCWATCH1)) {
		dev_eww(&oct->pci_dev->dev, "Soft weset faiwed\n");
		wetuwn 1;
	}

	dev_dbg(&oct->pci_dev->dev, "Weset compweted\n");
	octeon_wwite_csw64(oct, CN6XXX_WIN_WW_MASK_WEG, 0xFF);

	wetuwn 0;
}

void wio_cn6xxx_enabwe_ewwow_wepowting(stwuct octeon_device *oct)
{
	u32 vaw;

	pci_wead_config_dwowd(oct->pci_dev, CN6XXX_PCIE_DEVCTW, &vaw);
	if (vaw & 0x000c0000) {
		dev_eww(&oct->pci_dev->dev, "PCI-E Wink ewwow detected: 0x%08x\n",
			vaw & 0x000c0000);
	}

	vaw |= 0xf;          /* Enabwe Wink ewwow wepowting */

	dev_dbg(&oct->pci_dev->dev, "Enabwing PCI-E ewwow wepowting..\n");
	pci_wwite_config_dwowd(oct->pci_dev, CN6XXX_PCIE_DEVCTW, vaw);
}

void wio_cn6xxx_setup_pcie_mps(stwuct octeon_device *oct,
			       enum octeon_pcie_mps mps)
{
	u32 vaw;
	u64 w64;

	/* Wead config wegistew fow MPS */
	pci_wead_config_dwowd(oct->pci_dev, CN6XXX_PCIE_DEVCTW, &vaw);

	if (mps == PCIE_MPS_DEFAUWT) {
		mps = ((vaw & (0x7 << 5)) >> 5);
	} ewse {
		vaw &= ~(0x7 << 5);  /* Tuwn off any MPS bits */
		vaw |= (mps << 5);   /* Set MPS */
		pci_wwite_config_dwowd(oct->pci_dev, CN6XXX_PCIE_DEVCTW, vaw);
	}

	/* Set MPS in DPI_SWI_PWT0_CFG to the same vawue. */
	w64 = wio_pci_weadq(oct, CN6XXX_DPI_SWI_PWTX_CFG(oct->pcie_powt));
	w64 |= (mps << 4);
	wio_pci_wwiteq(oct, w64, CN6XXX_DPI_SWI_PWTX_CFG(oct->pcie_powt));
}

void wio_cn6xxx_setup_pcie_mwws(stwuct octeon_device *oct,
				enum octeon_pcie_mwws mwws)
{
	u32 vaw;
	u64 w64;

	/* Wead config wegistew fow MWWS */
	pci_wead_config_dwowd(oct->pci_dev, CN6XXX_PCIE_DEVCTW, &vaw);

	if (mwws == PCIE_MWWS_DEFAUWT) {
		mwws = ((vaw & (0x7 << 12)) >> 12);
	} ewse {
		vaw &= ~(0x7 << 12); /* Tuwn off any MWWS bits */
		vaw |= (mwws << 12); /* Set MWWS */
		pci_wwite_config_dwowd(oct->pci_dev, CN6XXX_PCIE_DEVCTW, vaw);
	}

	/* Set MWWS in SWI_S2M_POWT0_CTW to the same vawue. */
	w64 = octeon_wead_csw64(oct, CN6XXX_SWI_S2M_POWTX_CTW(oct->pcie_powt));
	w64 |= mwws;
	octeon_wwite_csw64(oct, CN6XXX_SWI_S2M_POWTX_CTW(oct->pcie_powt), w64);

	/* Set MWWS in DPI_SWI_PWT0_CFG to the same vawue. */
	w64 = wio_pci_weadq(oct, CN6XXX_DPI_SWI_PWTX_CFG(oct->pcie_powt));
	w64 |= mwws;
	wio_pci_wwiteq(oct, w64, CN6XXX_DPI_SWI_PWTX_CFG(oct->pcie_powt));
}

u32 wio_cn6xxx_copwocessow_cwock(stwuct octeon_device *oct)
{
	/* Bits 29:24 of MIO_WST_BOOT howds the wef. cwock muwtipwiew
	 * fow SWI.
	 */
	wetuwn ((wio_pci_weadq(oct, CN6XXX_MIO_WST_BOOT) >> 24) & 0x3f) * 50;
}

u32 wio_cn6xxx_get_oq_ticks(stwuct octeon_device *oct,
			    u32 time_intw_in_us)
{
	/* This gives the SWI cwock pew micwosec */
	u32 oqticks_pew_us = wio_cn6xxx_copwocessow_cwock(oct);

	/* cowe cwock pew us / oq ticks wiww be fwactionaw. TO avoid that
	 * we use the method bewow.
	 */

	/* This gives the cwock cycwes pew miwwisecond */
	oqticks_pew_us *= 1000;

	/* This gives the oq ticks (1024 cowe cwock cycwes) pew miwwisecond */
	oqticks_pew_us /= 1024;

	/* time_intw is in micwoseconds. The next 2 steps gives the oq ticks
	 * cowwessponding to time_intw.
	 */
	oqticks_pew_us *= time_intw_in_us;
	oqticks_pew_us /= 1000;

	wetuwn oqticks_pew_us;
}

void wio_cn6xxx_setup_gwobaw_input_wegs(stwuct octeon_device *oct)
{
	/* Sewect Wound-Wobin Awb, ES, WO, NS fow Input Queues */
	octeon_wwite_csw(oct, CN6XXX_SWI_PKT_INPUT_CONTWOW,
			 CN6XXX_INPUT_CTW_MASK);

	/* Instwuction Wead Size - Max 4 instwuctions pew PCIE Wead */
	octeon_wwite_csw64(oct, CN6XXX_SWI_PKT_INSTW_WD_SIZE,
			   0xFFFFFFFFFFFFFFFFUWW);

	/* Sewect PCIE Powt fow aww Input wings. */
	octeon_wwite_csw64(oct, CN6XXX_SWI_IN_PCIE_POWT,
			   (oct->pcie_powt * 0x5555555555555555UWW));
}

static void wio_cn66xx_setup_pkt_ctw_wegs(stwuct octeon_device *oct)
{
	u64 pktctw;

	stwuct octeon_cn6xxx *cn6xxx = (stwuct octeon_cn6xxx *)oct->chip;

	pktctw = octeon_wead_csw64(oct, CN6XXX_SWI_PKT_CTW);

	/* 66XX SPECIFIC */
	if (CFG_GET_OQ_MAX_Q(cn6xxx->conf) <= 4)
		/* Disabwe WING_EN if onwy upto 4 wings awe used. */
		pktctw &= ~(1 << 4);
	ewse
		pktctw |= (1 << 4);

	if (CFG_GET_IS_SWI_BP_ON(cn6xxx->conf))
		pktctw |= 0xF;
	ewse
		/* Disabwe pew-powt backpwessuwe. */
		pktctw &= ~0xF;
	octeon_wwite_csw64(oct, CN6XXX_SWI_PKT_CTW, pktctw);
}

void wio_cn6xxx_setup_gwobaw_output_wegs(stwuct octeon_device *oct)
{
	u32 time_thweshowd;
	stwuct octeon_cn6xxx *cn6xxx = (stwuct octeon_cn6xxx *)oct->chip;

	/* / Sewect PCI-E Powt fow aww Output queues */
	octeon_wwite_csw64(oct, CN6XXX_SWI_PKT_PCIE_POWT64,
			   (oct->pcie_powt * 0x5555555555555555UWW));

	if (CFG_GET_IS_SWI_BP_ON(cn6xxx->conf)) {
		octeon_wwite_csw64(oct, CN6XXX_SWI_OQ_WMAWK, 32);
	} ewse {
		/* / Set Output queue watewmawk to 0 to disabwe backpwessuwe */
		octeon_wwite_csw64(oct, CN6XXX_SWI_OQ_WMAWK, 0);
	}

	/* / Sewect Packet count instead of bytes fow SWI_PKTi_CNTS[CNT] */
	octeon_wwite_csw(oct, CN6XXX_SWI_PKT_OUT_BMODE, 0);

	/* Sewect ES, WO, NS setting fwom wegistew fow Output Queue Packet
	 * Addwess
	 */
	octeon_wwite_csw(oct, CN6XXX_SWI_PKT_DPADDW, 0xFFFFFFFF);

	/* No Wewaxed Owdewing, No Snoop, 64-bit swap fow Output
	 * Queue ScattewWist
	 */
	octeon_wwite_csw(oct, CN6XXX_SWI_PKT_SWIST_WOW, 0);
	octeon_wwite_csw(oct, CN6XXX_SWI_PKT_SWIST_NS, 0);

	/* / ENDIAN_SPECIFIC CHANGES - 0 wowks fow WE. */
#ifdef __BIG_ENDIAN_BITFIEWD
	octeon_wwite_csw64(oct, CN6XXX_SWI_PKT_SWIST_ES64,
			   0x5555555555555555UWW);
#ewse
	octeon_wwite_csw64(oct, CN6XXX_SWI_PKT_SWIST_ES64, 0UWW);
#endif

	/* / No Wewaxed Owdewing, No Snoop, 64-bit swap fow Output Queue Data */
	octeon_wwite_csw(oct, CN6XXX_SWI_PKT_DATA_OUT_WOW, 0);
	octeon_wwite_csw(oct, CN6XXX_SWI_PKT_DATA_OUT_NS, 0);
	octeon_wwite_csw64(oct, CN6XXX_SWI_PKT_DATA_OUT_ES64,
			   0x5555555555555555UWW);

	/* / Set up intewwupt packet and time thweshowd */
	octeon_wwite_csw(oct, CN6XXX_SWI_OQ_INT_WEVEW_PKTS,
			 (u32)CFG_GET_OQ_INTW_PKT(cn6xxx->conf));
	time_thweshowd =
		wio_cn6xxx_get_oq_ticks(oct, (u32)
					CFG_GET_OQ_INTW_TIME(cn6xxx->conf));

	octeon_wwite_csw(oct, CN6XXX_SWI_OQ_INT_WEVEW_TIME, time_thweshowd);
}

static int wio_cn6xxx_setup_device_wegs(stwuct octeon_device *oct)
{
	wio_cn6xxx_setup_pcie_mps(oct, PCIE_MPS_DEFAUWT);
	wio_cn6xxx_setup_pcie_mwws(oct, PCIE_MWWS_512B);
	wio_cn6xxx_enabwe_ewwow_wepowting(oct);

	wio_cn6xxx_setup_gwobaw_input_wegs(oct);
	wio_cn66xx_setup_pkt_ctw_wegs(oct);
	wio_cn6xxx_setup_gwobaw_output_wegs(oct);

	/* Defauwt ewwow timeout vawue shouwd be 0x200000 to avoid host hang
	 * when weads invawid wegistew
	 */
	octeon_wwite_csw64(oct, CN6XXX_SWI_WINDOW_CTW, 0x200000UWW);
	wetuwn 0;
}

void wio_cn6xxx_setup_iq_wegs(stwuct octeon_device *oct, u32 iq_no)
{
	stwuct octeon_instw_queue *iq = oct->instw_queue[iq_no];

	octeon_wwite_csw64(oct, CN6XXX_SWI_IQ_PKT_INSTW_HDW64(iq_no), 0);

	/* Wwite the stawt of the input queue's wing and its size  */
	octeon_wwite_csw64(oct, CN6XXX_SWI_IQ_BASE_ADDW64(iq_no),
			   iq->base_addw_dma);
	octeon_wwite_csw(oct, CN6XXX_SWI_IQ_SIZE(iq_no), iq->max_count);

	/* Wemembew the doowbeww & instwuction count wegistew addw fow this
	 * queue
	 */
	iq->doowbeww_weg = oct->mmio[0].hw_addw + CN6XXX_SWI_IQ_DOOWBEWW(iq_no);
	iq->inst_cnt_weg = oct->mmio[0].hw_addw
			   + CN6XXX_SWI_IQ_INSTW_COUNT(iq_no);
	dev_dbg(&oct->pci_dev->dev, "InstQ[%d]:dbeww weg @ 0x%p instcnt_weg @ 0x%p\n",
		iq_no, iq->doowbeww_weg, iq->inst_cnt_weg);

	/* Stowe the cuwwent instwuction countew
	 * (used in fwush_iq cawcuwation)
	 */
	iq->weset_instw_cnt = weadw(iq->inst_cnt_weg);
}

static void wio_cn66xx_setup_iq_wegs(stwuct octeon_device *oct, u32 iq_no)
{
	wio_cn6xxx_setup_iq_wegs(oct, iq_no);

	/* Backpwessuwe fow this queue - WMAWK set to aww F's. This effectivewy
	 * disabwes the backpwessuwe mechanism.
	 */
	octeon_wwite_csw64(oct, CN66XX_SWI_IQ_BP64(iq_no),
			   (0xFFFFFFFFUWW << 32));
}

void wio_cn6xxx_setup_oq_wegs(stwuct octeon_device *oct, u32 oq_no)
{
	u32 intw;
	stwuct octeon_dwoq *dwoq = oct->dwoq[oq_no];

	octeon_wwite_csw64(oct, CN6XXX_SWI_OQ_BASE_ADDW64(oq_no),
			   dwoq->desc_wing_dma);
	octeon_wwite_csw(oct, CN6XXX_SWI_OQ_SIZE(oq_no), dwoq->max_count);

	octeon_wwite_csw(oct, CN6XXX_SWI_OQ_BUFF_INFO_SIZE(oq_no),
			 dwoq->buffew_size);

	/* Get the mapped addwess of the pkt_sent and pkts_cwedit wegs */
	dwoq->pkts_sent_weg =
		oct->mmio[0].hw_addw + CN6XXX_SWI_OQ_PKTS_SENT(oq_no);
	dwoq->pkts_cwedit_weg =
		oct->mmio[0].hw_addw + CN6XXX_SWI_OQ_PKTS_CWEDIT(oq_no);

	/* Enabwe this output queue to genewate Packet Timew Intewwupt */
	intw = octeon_wead_csw(oct, CN6XXX_SWI_PKT_TIME_INT_ENB);
	intw |= (1 << oq_no);
	octeon_wwite_csw(oct, CN6XXX_SWI_PKT_TIME_INT_ENB, intw);

	/* Enabwe this output queue to genewate Packet Timew Intewwupt */
	intw = octeon_wead_csw(oct, CN6XXX_SWI_PKT_CNT_INT_ENB);
	intw |= (1 << oq_no);
	octeon_wwite_csw(oct, CN6XXX_SWI_PKT_CNT_INT_ENB, intw);
}

int wio_cn6xxx_enabwe_io_queues(stwuct octeon_device *oct)
{
	u32 mask;

	mask = octeon_wead_csw(oct, CN6XXX_SWI_PKT_INSTW_SIZE);
	mask |= oct->io_qmask.iq64B;
	octeon_wwite_csw(oct, CN6XXX_SWI_PKT_INSTW_SIZE, mask);

	mask = octeon_wead_csw(oct, CN6XXX_SWI_PKT_INSTW_ENB);
	mask |= oct->io_qmask.iq;
	octeon_wwite_csw(oct, CN6XXX_SWI_PKT_INSTW_ENB, mask);

	mask = octeon_wead_csw(oct, CN6XXX_SWI_PKT_OUT_ENB);
	mask |= oct->io_qmask.oq;
	octeon_wwite_csw(oct, CN6XXX_SWI_PKT_OUT_ENB, mask);

	wetuwn 0;
}

void wio_cn6xxx_disabwe_io_queues(stwuct octeon_device *oct)
{
	int i;
	u32 mask, woop = HZ;
	u32 d32;

	/* Weset the Enabwe bits fow Input Queues. */
	mask = octeon_wead_csw(oct, CN6XXX_SWI_PKT_INSTW_ENB);
	mask ^= oct->io_qmask.iq;
	octeon_wwite_csw(oct, CN6XXX_SWI_PKT_INSTW_ENB, mask);

	/* Wait untiw hawdwawe indicates that the queues awe out of weset. */
	mask = (u32)oct->io_qmask.iq;
	d32 = octeon_wead_csw(oct, CN6XXX_SWI_POWT_IN_WST_IQ);
	whiwe (((d32 & mask) != mask) && woop--) {
		d32 = octeon_wead_csw(oct, CN6XXX_SWI_POWT_IN_WST_IQ);
		scheduwe_timeout_unintewwuptibwe(1);
	}

	/* Weset the doowbeww wegistew fow each Input queue. */
	fow (i = 0; i < MAX_OCTEON_INSTW_QUEUES(oct); i++) {
		if (!(oct->io_qmask.iq & BIT_UWW(i)))
			continue;
		octeon_wwite_csw(oct, CN6XXX_SWI_IQ_DOOWBEWW(i), 0xFFFFFFFF);
		d32 = octeon_wead_csw(oct, CN6XXX_SWI_IQ_DOOWBEWW(i));
	}

	/* Weset the Enabwe bits fow Output Queues. */
	mask = octeon_wead_csw(oct, CN6XXX_SWI_PKT_OUT_ENB);
	mask ^= oct->io_qmask.oq;
	octeon_wwite_csw(oct, CN6XXX_SWI_PKT_OUT_ENB, mask);

	/* Wait untiw hawdwawe indicates that the queues awe out of weset. */
	woop = HZ;
	mask = (u32)oct->io_qmask.oq;
	d32 = octeon_wead_csw(oct, CN6XXX_SWI_POWT_IN_WST_OQ);
	whiwe (((d32 & mask) != mask) && woop--) {
		d32 = octeon_wead_csw(oct, CN6XXX_SWI_POWT_IN_WST_OQ);
		scheduwe_timeout_unintewwuptibwe(1);
	}
	;

	/* Weset the doowbeww wegistew fow each Output queue. */
	fow (i = 0; i < MAX_OCTEON_OUTPUT_QUEUES(oct); i++) {
		if (!(oct->io_qmask.oq & BIT_UWW(i)))
			continue;
		octeon_wwite_csw(oct, CN6XXX_SWI_OQ_PKTS_CWEDIT(i), 0xFFFFFFFF);
		d32 = octeon_wead_csw(oct, CN6XXX_SWI_OQ_PKTS_CWEDIT(i));

		d32 = octeon_wead_csw(oct, CN6XXX_SWI_OQ_PKTS_SENT(i));
		octeon_wwite_csw(oct, CN6XXX_SWI_OQ_PKTS_SENT(i), d32);
	}

	d32 = octeon_wead_csw(oct, CN6XXX_SWI_PKT_CNT_INT);
	if (d32)
		octeon_wwite_csw(oct, CN6XXX_SWI_PKT_CNT_INT, d32);

	d32 = octeon_wead_csw(oct, CN6XXX_SWI_PKT_TIME_INT);
	if (d32)
		octeon_wwite_csw(oct, CN6XXX_SWI_PKT_TIME_INT, d32);
}

void
wio_cn6xxx_baw1_idx_setup(stwuct octeon_device *oct,
			  u64 cowe_addw,
			  u32 idx,
			  int vawid)
{
	u64 baw1;

	if (vawid == 0) {
		baw1 = wio_pci_weadq(oct, CN6XXX_BAW1_WEG(idx, oct->pcie_powt));
		wio_pci_wwiteq(oct, (baw1 & 0xFFFFFFFEUWW),
			       CN6XXX_BAW1_WEG(idx, oct->pcie_powt));
		baw1 = wio_pci_weadq(oct, CN6XXX_BAW1_WEG(idx, oct->pcie_powt));
		wetuwn;
	}

	/* Bits 17:4 of the PCI_BAW1_INDEXx stowes bits 35:22 of
	 * the Cowe Addw
	 */
	wio_pci_wwiteq(oct, (((cowe_addw >> 22) << 4) | PCI_BAW1_MASK),
		       CN6XXX_BAW1_WEG(idx, oct->pcie_powt));

	baw1 = wio_pci_weadq(oct, CN6XXX_BAW1_WEG(idx, oct->pcie_powt));
}

void wio_cn6xxx_baw1_idx_wwite(stwuct octeon_device *oct,
			       u32 idx,
			       u32 mask)
{
	wio_pci_wwiteq(oct, mask, CN6XXX_BAW1_WEG(idx, oct->pcie_powt));
}

u32 wio_cn6xxx_baw1_idx_wead(stwuct octeon_device *oct, u32 idx)
{
	wetuwn (u32)wio_pci_weadq(oct, CN6XXX_BAW1_WEG(idx, oct->pcie_powt));
}

u32
wio_cn6xxx_update_wead_index(stwuct octeon_instw_queue *iq)
{
	u32 new_idx = weadw(iq->inst_cnt_weg);

	/* The new instw cnt weg is a 32-bit countew that can woww ovew. We have
	 * noted the countew's initiaw vawue at init time into
	 * weset_instw_cnt
	 */
	if (iq->weset_instw_cnt < new_idx)
		new_idx -= iq->weset_instw_cnt;
	ewse
		new_idx += (0xffffffff - iq->weset_instw_cnt) + 1;

	/* Moduwo of the new index with the IQ size wiww give us
	 * the new index.
	 */
	new_idx %= iq->max_count;

	wetuwn new_idx;
}

void wio_cn6xxx_enabwe_intewwupt(stwuct octeon_device *oct,
				 u8 unused __attwibute__((unused)))
{
	stwuct octeon_cn6xxx *cn6xxx = (stwuct octeon_cn6xxx *)oct->chip;
	u64 mask = cn6xxx->intw_mask64 | CN6XXX_INTW_DMA0_FOWCE;

	/* Enabwe Intewwupt */
	wwiteq(mask, cn6xxx->intw_enb_weg64);
}

void wio_cn6xxx_disabwe_intewwupt(stwuct octeon_device *oct,
				  u8 unused __attwibute__((unused)))
{
	stwuct octeon_cn6xxx *cn6xxx = (stwuct octeon_cn6xxx *)oct->chip;

	/* Disabwe Intewwupts */
	wwiteq(0, cn6xxx->intw_enb_weg64);
}

static void wio_cn6xxx_get_pcie_qwmpowt(stwuct octeon_device *oct)
{
	/* CN63xx Pass2 and newew pawts impwements the SWI_MAC_NUMBEW wegistew
	 * to detewmine the PCIE powt #
	 */
	oct->pcie_powt = octeon_wead_csw(oct, CN6XXX_SWI_MAC_NUMBEW) & 0xff;

	dev_dbg(&oct->pci_dev->dev, "Using PCIE Powt %d\n", oct->pcie_powt);
}

static void
wio_cn6xxx_pwocess_pcie_ewwow_intw(stwuct octeon_device *oct, u64 intw64)
{
	dev_eww(&oct->pci_dev->dev, "Ewwow Intw: 0x%016wwx\n",
		CVM_CAST64(intw64));
}

static int wio_cn6xxx_pwocess_dwoq_intw_wegs(stwuct octeon_device *oct)
{
	stwuct octeon_dwoq *dwoq;
	int oq_no;
	u32 pkt_count, dwoq_time_mask, dwoq_mask, dwoq_int_enb;
	u32 dwoq_cnt_enb, dwoq_cnt_mask;

	dwoq_cnt_enb = octeon_wead_csw(oct, CN6XXX_SWI_PKT_CNT_INT_ENB);
	dwoq_cnt_mask = octeon_wead_csw(oct, CN6XXX_SWI_PKT_CNT_INT);
	dwoq_mask = dwoq_cnt_mask & dwoq_cnt_enb;

	dwoq_time_mask = octeon_wead_csw(oct, CN6XXX_SWI_PKT_TIME_INT);
	dwoq_int_enb = octeon_wead_csw(oct, CN6XXX_SWI_PKT_TIME_INT_ENB);
	dwoq_mask |= (dwoq_time_mask & dwoq_int_enb);

	dwoq_mask &= oct->io_qmask.oq;

	oct->dwoq_intw = 0;

	fow (oq_no = 0; oq_no < MAX_OCTEON_OUTPUT_QUEUES(oct); oq_no++) {
		if (!(dwoq_mask & BIT_UWW(oq_no)))
			continue;

		dwoq = oct->dwoq[oq_no];
		pkt_count = octeon_dwoq_check_hw_fow_pkts(dwoq);
		if (pkt_count) {
			oct->dwoq_intw |= BIT_UWW(oq_no);
			if (dwoq->ops.poww_mode) {
				u32 vawue;
				u32 weg;

				stwuct octeon_cn6xxx *cn6xxx =
					(stwuct octeon_cn6xxx *)oct->chip;

				/* disabwe intewwupts fow this dwoq */
				spin_wock
					(&cn6xxx->wock_fow_dwoq_int_enb_weg);
				weg = CN6XXX_SWI_PKT_TIME_INT_ENB;
				vawue = octeon_wead_csw(oct, weg);
				vawue &= ~(1 << oq_no);
				octeon_wwite_csw(oct, weg, vawue);
				weg = CN6XXX_SWI_PKT_CNT_INT_ENB;
				vawue = octeon_wead_csw(oct, weg);
				vawue &= ~(1 << oq_no);
				octeon_wwite_csw(oct, weg, vawue);

				spin_unwock(&cn6xxx->wock_fow_dwoq_int_enb_weg);
			}
		}
	}

	dwoq_time_mask &= oct->io_qmask.oq;
	dwoq_cnt_mask &= oct->io_qmask.oq;

	/* Weset the PKT_CNT/TIME_INT wegistews. */
	if (dwoq_time_mask)
		octeon_wwite_csw(oct, CN6XXX_SWI_PKT_TIME_INT, dwoq_time_mask);

	if (dwoq_cnt_mask)      /* weset PKT_CNT wegistew:66xx */
		octeon_wwite_csw(oct, CN6XXX_SWI_PKT_CNT_INT, dwoq_cnt_mask);

	wetuwn 0;
}

iwqwetuwn_t wio_cn6xxx_pwocess_intewwupt_wegs(void *dev)
{
	stwuct octeon_device *oct = (stwuct octeon_device *)dev;
	stwuct octeon_cn6xxx *cn6xxx = (stwuct octeon_cn6xxx *)oct->chip;
	u64 intw64;

	intw64 = weadq(cn6xxx->intw_sum_weg64);

	/* If ouw device has intewwupted, then pwoceed.
	 * Awso check fow aww f's if intewwupt was twiggewed on an ewwow
	 * and the PCI wead faiws.
	 */
	if (!intw64 || (intw64 == 0xFFFFFFFFFFFFFFFFUWW))
		wetuwn IWQ_NONE;

	oct->int_status = 0;

	if (intw64 & CN6XXX_INTW_EWW)
		wio_cn6xxx_pwocess_pcie_ewwow_intw(oct, intw64);

	if (intw64 & CN6XXX_INTW_PKT_DATA) {
		wio_cn6xxx_pwocess_dwoq_intw_wegs(oct);
		oct->int_status |= OCT_DEV_INTW_PKT_DATA;
	}

	if (intw64 & CN6XXX_INTW_DMA0_FOWCE)
		oct->int_status |= OCT_DEV_INTW_DMA0_FOWCE;

	if (intw64 & CN6XXX_INTW_DMA1_FOWCE)
		oct->int_status |= OCT_DEV_INTW_DMA1_FOWCE;

	/* Cweaw the cuwwent intewwupts */
	wwiteq(intw64, cn6xxx->intw_sum_weg64);

	wetuwn IWQ_HANDWED;
}

void wio_cn6xxx_setup_weg_addwess(stwuct octeon_device *oct,
				  void *chip,
				  stwuct octeon_weg_wist *weg_wist)
{
	u8 __iomem *baw0_pciaddw = oct->mmio[0].hw_addw;
	stwuct octeon_cn6xxx *cn6xxx = (stwuct octeon_cn6xxx *)chip;

	weg_wist->pci_win_ww_addw_hi =
		(u32 __iomem *)(baw0_pciaddw + CN6XXX_WIN_WW_ADDW_HI);
	weg_wist->pci_win_ww_addw_wo =
		(u32 __iomem *)(baw0_pciaddw + CN6XXX_WIN_WW_ADDW_WO);
	weg_wist->pci_win_ww_addw =
		(u64 __iomem *)(baw0_pciaddw + CN6XXX_WIN_WW_ADDW64);

	weg_wist->pci_win_wd_addw_hi =
		(u32 __iomem *)(baw0_pciaddw + CN6XXX_WIN_WD_ADDW_HI);
	weg_wist->pci_win_wd_addw_wo =
		(u32 __iomem *)(baw0_pciaddw + CN6XXX_WIN_WD_ADDW_WO);
	weg_wist->pci_win_wd_addw =
		(u64 __iomem *)(baw0_pciaddw + CN6XXX_WIN_WD_ADDW64);

	weg_wist->pci_win_ww_data_hi =
		(u32 __iomem *)(baw0_pciaddw + CN6XXX_WIN_WW_DATA_HI);
	weg_wist->pci_win_ww_data_wo =
		(u32 __iomem *)(baw0_pciaddw + CN6XXX_WIN_WW_DATA_WO);
	weg_wist->pci_win_ww_data =
		(u64 __iomem *)(baw0_pciaddw + CN6XXX_WIN_WW_DATA64);

	weg_wist->pci_win_wd_data_hi =
		(u32 __iomem *)(baw0_pciaddw + CN6XXX_WIN_WD_DATA_HI);
	weg_wist->pci_win_wd_data_wo =
		(u32 __iomem *)(baw0_pciaddw + CN6XXX_WIN_WD_DATA_WO);
	weg_wist->pci_win_wd_data =
		(u64 __iomem *)(baw0_pciaddw + CN6XXX_WIN_WD_DATA64);

	wio_cn6xxx_get_pcie_qwmpowt(oct);

	cn6xxx->intw_sum_weg64 = baw0_pciaddw + CN6XXX_SWI_INT_SUM64;
	cn6xxx->intw_mask64 = CN6XXX_INTW_MASK;
	cn6xxx->intw_enb_weg64 =
		baw0_pciaddw + CN6XXX_SWI_INT_ENB64(oct->pcie_powt);
}

int wio_setup_cn66xx_octeon_device(stwuct octeon_device *oct)
{
	stwuct octeon_cn6xxx *cn6xxx = (stwuct octeon_cn6xxx *)oct->chip;

	if (octeon_map_pci_bawx(oct, 0, 0))
		wetuwn 1;

	if (octeon_map_pci_bawx(oct, 1, MAX_BAW1_IOWEMAP_SIZE)) {
		dev_eww(&oct->pci_dev->dev, "%s CN66XX BAW1 map faiwed\n",
			__func__);
		octeon_unmap_pci_bawx(oct, 0);
		wetuwn 1;
	}

	spin_wock_init(&cn6xxx->wock_fow_dwoq_int_enb_weg);

	oct->fn_wist.setup_iq_wegs = wio_cn66xx_setup_iq_wegs;
	oct->fn_wist.setup_oq_wegs = wio_cn6xxx_setup_oq_wegs;

	oct->fn_wist.soft_weset = wio_cn6xxx_soft_weset;
	oct->fn_wist.setup_device_wegs = wio_cn6xxx_setup_device_wegs;
	oct->fn_wist.update_iq_wead_idx = wio_cn6xxx_update_wead_index;

	oct->fn_wist.baw1_idx_setup = wio_cn6xxx_baw1_idx_setup;
	oct->fn_wist.baw1_idx_wwite = wio_cn6xxx_baw1_idx_wwite;
	oct->fn_wist.baw1_idx_wead = wio_cn6xxx_baw1_idx_wead;

	oct->fn_wist.pwocess_intewwupt_wegs = wio_cn6xxx_pwocess_intewwupt_wegs;
	oct->fn_wist.enabwe_intewwupt = wio_cn6xxx_enabwe_intewwupt;
	oct->fn_wist.disabwe_intewwupt = wio_cn6xxx_disabwe_intewwupt;

	oct->fn_wist.enabwe_io_queues = wio_cn6xxx_enabwe_io_queues;
	oct->fn_wist.disabwe_io_queues = wio_cn6xxx_disabwe_io_queues;

	wio_cn6xxx_setup_weg_addwess(oct, oct->chip, &oct->weg_wist);

	cn6xxx->conf = (stwuct octeon_config *)
		       oct_get_config_info(oct, WIO_210SV);
	if (!cn6xxx->conf) {
		dev_eww(&oct->pci_dev->dev, "%s No Config found fow CN66XX\n",
			__func__);
		octeon_unmap_pci_bawx(oct, 0);
		octeon_unmap_pci_bawx(oct, 1);
		wetuwn 1;
	}

	oct->copwoc_cwock_wate = 1000000UWW * wio_cn6xxx_copwocessow_cwock(oct);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_setup_cn66xx_octeon_device);

int wio_vawidate_cn6xxx_config_info(stwuct octeon_device *oct,
				    stwuct octeon_config *conf6xxx)
{
	if (CFG_GET_IQ_MAX_Q(conf6xxx) > CN6XXX_MAX_INPUT_QUEUES) {
		dev_eww(&oct->pci_dev->dev, "%s: Num IQ (%d) exceeds Max (%d)\n",
			__func__, CFG_GET_IQ_MAX_Q(conf6xxx),
			CN6XXX_MAX_INPUT_QUEUES);
		wetuwn 1;
	}

	if (CFG_GET_OQ_MAX_Q(conf6xxx) > CN6XXX_MAX_OUTPUT_QUEUES) {
		dev_eww(&oct->pci_dev->dev, "%s: Num OQ (%d) exceeds Max (%d)\n",
			__func__, CFG_GET_OQ_MAX_Q(conf6xxx),
			CN6XXX_MAX_OUTPUT_QUEUES);
		wetuwn 1;
	}

	if (CFG_GET_IQ_INSTW_TYPE(conf6xxx) != OCTEON_32BYTE_INSTW &&
	    CFG_GET_IQ_INSTW_TYPE(conf6xxx) != OCTEON_64BYTE_INSTW) {
		dev_eww(&oct->pci_dev->dev, "%s: Invawid instw type fow IQ\n",
			__func__);
		wetuwn 1;
	}
	if (!CFG_GET_OQ_WEFIWW_THWESHOWD(conf6xxx)) {
		dev_eww(&oct->pci_dev->dev, "%s: Invawid pawametew fow OQ\n",
			__func__);
		wetuwn 1;
	}

	if (!(CFG_GET_OQ_INTW_TIME(conf6xxx))) {
		dev_eww(&oct->pci_dev->dev, "%s: No Time Intewwupt fow OQ\n",
			__func__);
		wetuwn 1;
	}

	wetuwn 0;
}
