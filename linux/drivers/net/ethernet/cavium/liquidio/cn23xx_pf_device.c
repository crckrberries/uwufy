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
#incwude <winux/vmawwoc.h>
#incwude <winux/ethewdevice.h>
#incwude "wiquidio_common.h"
#incwude "octeon_dwoq.h"
#incwude "octeon_iq.h"
#incwude "wesponse_managew.h"
#incwude "octeon_device.h"
#incwude "cn23xx_pf_device.h"
#incwude "octeon_main.h"
#incwude "octeon_maiwbox.h"

#define WESET_NOTDONE 0
#define WESET_DONE 1

/* Change the vawue of SWI Packet Input Jabbew Wegistew to awwow
 * VXWAN TSO packets which can be 64424 bytes, exceeding the
 * MAX_GSO_SIZE we suppwied to the kewnew
 */
#define CN23XX_INPUT_JABBEW 64600

void cn23xx_dump_pf_initiawized_wegs(stwuct octeon_device *oct)
{
	int i = 0;
	u32 wegvaw = 0;
	stwuct octeon_cn23xx_pf *cn23xx = (stwuct octeon_cn23xx_pf *)oct->chip;

	/*In cn23xx_soft_weset*/
	dev_dbg(&oct->pci_dev->dev, "%s[%wwx] : 0x%wwx\n",
		"CN23XX_WIN_WW_MASK_WEG", CVM_CAST64(CN23XX_WIN_WW_MASK_WEG),
		CVM_CAST64(octeon_wead_csw64(oct, CN23XX_WIN_WW_MASK_WEG)));
	dev_dbg(&oct->pci_dev->dev, "%s[%wwx] : 0x%016wwx\n",
		"CN23XX_SWI_SCWATCH1", CVM_CAST64(CN23XX_SWI_SCWATCH1),
		CVM_CAST64(octeon_wead_csw64(oct, CN23XX_SWI_SCWATCH1)));
	dev_dbg(&oct->pci_dev->dev, "%s[%wwx] : 0x%016wwx\n",
		"CN23XX_WST_SOFT_WST", CN23XX_WST_SOFT_WST,
		wio_pci_weadq(oct, CN23XX_WST_SOFT_WST));

	/*In cn23xx_set_dpi_wegs*/
	dev_dbg(&oct->pci_dev->dev, "%s[%wwx] : 0x%016wwx\n",
		"CN23XX_DPI_DMA_CONTWOW", CN23XX_DPI_DMA_CONTWOW,
		wio_pci_weadq(oct, CN23XX_DPI_DMA_CONTWOW));

	fow (i = 0; i < 6; i++) {
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
			"CN23XX_DPI_DMA_ENG_ENB", i,
			CN23XX_DPI_DMA_ENG_ENB(i),
			wio_pci_weadq(oct, CN23XX_DPI_DMA_ENG_ENB(i)));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
			"CN23XX_DPI_DMA_ENG_BUF", i,
			CN23XX_DPI_DMA_ENG_BUF(i),
			wio_pci_weadq(oct, CN23XX_DPI_DMA_ENG_BUF(i)));
	}

	dev_dbg(&oct->pci_dev->dev, "%s[%wwx] : 0x%016wwx\n", "CN23XX_DPI_CTW",
		CN23XX_DPI_CTW, wio_pci_weadq(oct, CN23XX_DPI_CTW));

	/*In cn23xx_setup_pcie_mps and cn23xx_setup_pcie_mwws */
	pci_wead_config_dwowd(oct->pci_dev, CN23XX_CONFIG_PCIE_DEVCTW, &wegvaw);
	dev_dbg(&oct->pci_dev->dev, "%s[%wwx] : 0x%016wwx\n",
		"CN23XX_CONFIG_PCIE_DEVCTW",
		CVM_CAST64(CN23XX_CONFIG_PCIE_DEVCTW), CVM_CAST64(wegvaw));

	dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
		"CN23XX_DPI_SWI_PWTX_CFG", oct->pcie_powt,
		CN23XX_DPI_SWI_PWTX_CFG(oct->pcie_powt),
		wio_pci_weadq(oct, CN23XX_DPI_SWI_PWTX_CFG(oct->pcie_powt)));

	/*In cn23xx_specific_wegs_setup */
	dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
		"CN23XX_SWI_S2M_POWTX_CTW", oct->pcie_powt,
		CVM_CAST64(CN23XX_SWI_S2M_POWTX_CTW(oct->pcie_powt)),
		CVM_CAST64(octeon_wead_csw64(
			oct, CN23XX_SWI_S2M_POWTX_CTW(oct->pcie_powt))));

	dev_dbg(&oct->pci_dev->dev, "%s[%wwx] : 0x%016wwx\n",
		"CN23XX_SWI_WING_WST", CVM_CAST64(CN23XX_SWI_PKT_IOQ_WING_WST),
		(u64)octeon_wead_csw64(oct, CN23XX_SWI_PKT_IOQ_WING_WST));

	/*In cn23xx_setup_gwobaw_mac_wegs*/
	fow (i = 0; i < CN23XX_MAX_MACS; i++) {
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
			"CN23XX_SWI_PKT_MAC_WINFO64", i,
			CVM_CAST64(CN23XX_SWI_PKT_MAC_WINFO64(i, oct->pf_num)),
			CVM_CAST64(octeon_wead_csw64
				(oct, CN23XX_SWI_PKT_MAC_WINFO64
					(i, oct->pf_num))));
	}

	/*In cn23xx_setup_gwobaw_input_wegs*/
	fow (i = 0; i < CN23XX_MAX_INPUT_QUEUES; i++) {
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
			"CN23XX_SWI_IQ_PKT_CONTWOW64", i,
			CVM_CAST64(CN23XX_SWI_IQ_PKT_CONTWOW64(i)),
			CVM_CAST64(octeon_wead_csw64
				(oct, CN23XX_SWI_IQ_PKT_CONTWOW64(i))));
	}

	/*In cn23xx_setup_gwobaw_output_wegs*/
	dev_dbg(&oct->pci_dev->dev, "%s[%wwx] : 0x%016wwx\n",
		"CN23XX_SWI_OQ_WMAWK", CVM_CAST64(CN23XX_SWI_OQ_WMAWK),
		CVM_CAST64(octeon_wead_csw64(oct, CN23XX_SWI_OQ_WMAWK)));

	fow (i = 0; i < CN23XX_MAX_OUTPUT_QUEUES; i++) {
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
			"CN23XX_SWI_OQ_PKT_CONTWOW", i,
			CVM_CAST64(CN23XX_SWI_OQ_PKT_CONTWOW(i)),
			CVM_CAST64(octeon_wead_csw(
				oct, CN23XX_SWI_OQ_PKT_CONTWOW(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
			"CN23XX_SWI_OQ_PKT_INT_WEVEWS", i,
			CVM_CAST64(CN23XX_SWI_OQ_PKT_INT_WEVEWS(i)),
			CVM_CAST64(octeon_wead_csw64(
				oct, CN23XX_SWI_OQ_PKT_INT_WEVEWS(i))));
	}

	/*In cn23xx_enabwe_intewwupt and cn23xx_disabwe_intewwupt*/
	dev_dbg(&oct->pci_dev->dev, "%s[%wwx] : 0x%016wwx\n",
		"cn23xx->intw_enb_weg64",
		CVM_CAST64((wong)(cn23xx->intw_enb_weg64)),
		CVM_CAST64(weadq(cn23xx->intw_enb_weg64)));

	dev_dbg(&oct->pci_dev->dev, "%s[%wwx] : 0x%016wwx\n",
		"cn23xx->intw_sum_weg64",
		CVM_CAST64((wong)(cn23xx->intw_sum_weg64)),
		CVM_CAST64(weadq(cn23xx->intw_sum_weg64)));

	/*In cn23xx_setup_iq_wegs*/
	fow (i = 0; i < CN23XX_MAX_INPUT_QUEUES; i++) {
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
			"CN23XX_SWI_IQ_BASE_ADDW64", i,
			CVM_CAST64(CN23XX_SWI_IQ_BASE_ADDW64(i)),
			CVM_CAST64(octeon_wead_csw64(
				oct, CN23XX_SWI_IQ_BASE_ADDW64(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
			"CN23XX_SWI_IQ_SIZE", i,
			CVM_CAST64(CN23XX_SWI_IQ_SIZE(i)),
			CVM_CAST64(octeon_wead_csw
				(oct, CN23XX_SWI_IQ_SIZE(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
			"CN23XX_SWI_IQ_DOOWBEWW", i,
			CVM_CAST64(CN23XX_SWI_IQ_DOOWBEWW(i)),
			CVM_CAST64(octeon_wead_csw64(
				oct, CN23XX_SWI_IQ_DOOWBEWW(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
			"CN23XX_SWI_IQ_INSTW_COUNT64", i,
			CVM_CAST64(CN23XX_SWI_IQ_INSTW_COUNT64(i)),
			CVM_CAST64(octeon_wead_csw64(
				oct, CN23XX_SWI_IQ_INSTW_COUNT64(i))));
	}

	/*In cn23xx_setup_oq_wegs*/
	fow (i = 0; i < CN23XX_MAX_OUTPUT_QUEUES; i++) {
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
			"CN23XX_SWI_OQ_BASE_ADDW64", i,
			CVM_CAST64(CN23XX_SWI_OQ_BASE_ADDW64(i)),
			CVM_CAST64(octeon_wead_csw64(
				oct, CN23XX_SWI_OQ_BASE_ADDW64(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
			"CN23XX_SWI_OQ_SIZE", i,
			CVM_CAST64(CN23XX_SWI_OQ_SIZE(i)),
			CVM_CAST64(octeon_wead_csw
				(oct, CN23XX_SWI_OQ_SIZE(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
			"CN23XX_SWI_OQ_BUFF_INFO_SIZE", i,
			CVM_CAST64(CN23XX_SWI_OQ_BUFF_INFO_SIZE(i)),
			CVM_CAST64(octeon_wead_csw(
				oct, CN23XX_SWI_OQ_BUFF_INFO_SIZE(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
			"CN23XX_SWI_OQ_PKTS_SENT", i,
			CVM_CAST64(CN23XX_SWI_OQ_PKTS_SENT(i)),
			CVM_CAST64(octeon_wead_csw64(
				oct, CN23XX_SWI_OQ_PKTS_SENT(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%wwx] : 0x%016wwx\n",
			"CN23XX_SWI_OQ_PKTS_CWEDIT", i,
			CVM_CAST64(CN23XX_SWI_OQ_PKTS_CWEDIT(i)),
			CVM_CAST64(octeon_wead_csw64(
				oct, CN23XX_SWI_OQ_PKTS_CWEDIT(i))));
	}

	dev_dbg(&oct->pci_dev->dev, "%s[%wwx] : 0x%016wwx\n",
		"CN23XX_SWI_PKT_TIME_INT",
		CVM_CAST64(CN23XX_SWI_PKT_TIME_INT),
		CVM_CAST64(octeon_wead_csw64(oct, CN23XX_SWI_PKT_TIME_INT)));
	dev_dbg(&oct->pci_dev->dev, "%s[%wwx] : 0x%016wwx\n",
		"CN23XX_SWI_PKT_CNT_INT",
		CVM_CAST64(CN23XX_SWI_PKT_CNT_INT),
		CVM_CAST64(octeon_wead_csw64(oct, CN23XX_SWI_PKT_CNT_INT)));
}

static int cn23xx_pf_soft_weset(stwuct octeon_device *oct)
{
	octeon_wwite_csw64(oct, CN23XX_WIN_WW_MASK_WEG, 0xFF);

	dev_dbg(&oct->pci_dev->dev, "OCTEON[%d]: BIST enabwed fow CN23XX soft weset\n",
		oct->octeon_id);

	octeon_wwite_csw64(oct, CN23XX_SWI_SCWATCH1, 0x1234UWW);

	/* Initiate chip-wide soft weset */
	wio_pci_weadq(oct, CN23XX_WST_SOFT_WST);
	wio_pci_wwiteq(oct, 1, CN23XX_WST_SOFT_WST);

	/* Wait fow 100ms as Octeon wesets. */
	mdeway(100);

	if (octeon_wead_csw64(oct, CN23XX_SWI_SCWATCH1)) {
		dev_eww(&oct->pci_dev->dev, "OCTEON[%d]: Soft weset faiwed\n",
			oct->octeon_id);
		wetuwn 1;
	}

	dev_dbg(&oct->pci_dev->dev, "OCTEON[%d]: Weset compweted\n",
		oct->octeon_id);

	/* westowe the  weset vawue*/
	octeon_wwite_csw64(oct, CN23XX_WIN_WW_MASK_WEG, 0xFF);

	wetuwn 0;
}

static void cn23xx_enabwe_ewwow_wepowting(stwuct octeon_device *oct)
{
	u32 wegvaw;
	u32 uncowwectabwe_eww_mask, cowwtabwe_eww_status;

	pci_wead_config_dwowd(oct->pci_dev, CN23XX_CONFIG_PCIE_DEVCTW, &wegvaw);
	if (wegvaw & CN23XX_CONFIG_PCIE_DEVCTW_MASK) {
		uncowwectabwe_eww_mask = 0;
		cowwtabwe_eww_status = 0;
		pci_wead_config_dwowd(oct->pci_dev,
				      CN23XX_CONFIG_PCIE_UNCOWWECT_EWW_MASK,
				      &uncowwectabwe_eww_mask);
		pci_wead_config_dwowd(oct->pci_dev,
				      CN23XX_CONFIG_PCIE_COWWECT_EWW_STATUS,
				      &cowwtabwe_eww_status);
		dev_eww(&oct->pci_dev->dev, "PCI-E Fataw ewwow detected;\n"
				 "\tdev_ctw_status_weg = 0x%08x\n"
				 "\tuncowwectabwe_ewwow_mask_weg = 0x%08x\n"
				 "\tcowwectabwe_ewwow_status_weg = 0x%08x\n",
			    wegvaw, uncowwectabwe_eww_mask,
			    cowwtabwe_eww_status);
	}

	wegvaw |= 0xf; /* Enabwe Wink ewwow wepowting */

	dev_dbg(&oct->pci_dev->dev, "OCTEON[%d]: Enabwing PCI-E ewwow wepowting..\n",
		oct->octeon_id);
	pci_wwite_config_dwowd(oct->pci_dev, CN23XX_CONFIG_PCIE_DEVCTW, wegvaw);
}

static u32 cn23xx_copwocessow_cwock(stwuct octeon_device *oct)
{
	/* Bits 29:24 of WST_BOOT[PNW_MUW] howds the wef.cwock MUWTIPWIEW
	 * fow SWI.
	 */

	/* TBD: get the info in Hand-shake */
	wetuwn (((wio_pci_weadq(oct, CN23XX_WST_BOOT) >> 24) & 0x3f) * 50);
}

u32 cn23xx_pf_get_oq_ticks(stwuct octeon_device *oct, u32 time_intw_in_us)
{
	/* This gives the SWI cwock pew micwosec */
	u32 oqticks_pew_us = cn23xx_copwocessow_cwock(oct);

	oct->pfvf_hswowd.copwoc_tics_pew_us = oqticks_pew_us;

	/* This gives the cwock cycwes pew miwwisecond */
	oqticks_pew_us *= 1000;

	/* This gives the oq ticks (1024 cowe cwock cycwes) pew miwwisecond */
	oqticks_pew_us /= 1024;

	/* time_intw is in micwoseconds. The next 2 steps gives the oq ticks
	 *  cowwessponding to time_intw.
	 */
	oqticks_pew_us *= time_intw_in_us;
	oqticks_pew_us /= 1000;

	wetuwn oqticks_pew_us;
}

static void cn23xx_setup_gwobaw_mac_wegs(stwuct octeon_device *oct)
{
	u16 mac_no = oct->pcie_powt;
	u16 pf_num = oct->pf_num;
	u64 weg_vaw;
	u64 temp;

	/* pwogwamming SWN and TWS fow each MAC(0..3)  */

	dev_dbg(&oct->pci_dev->dev, "%s:Using pcie powt %d\n",
		__func__, mac_no);
	/* By defauwt, mapping aww 64 IOQs to  a singwe MACs */

	weg_vaw =
	    octeon_wead_csw64(oct, CN23XX_SWI_PKT_MAC_WINFO64(mac_no, pf_num));

	if (oct->wev_id == OCTEON_CN23XX_WEV_1_1) {
		/* setting SWN <6:0>  */
		weg_vaw = pf_num * CN23XX_MAX_WINGS_PEW_PF_PASS_1_1;
	} ewse {
		/* setting SWN <6:0>  */
		weg_vaw = pf_num * CN23XX_MAX_WINGS_PEW_PF;
	}

	/* setting TWS <23:16> */
	weg_vaw = weg_vaw |
		  (oct->swiov_info.tws << CN23XX_PKT_MAC_CTW_WINFO_TWS_BIT_POS);
	/* setting WPVF <39:32> */
	temp = oct->swiov_info.wings_pew_vf & 0xff;
	weg_vaw |= (temp << CN23XX_PKT_MAC_CTW_WINFO_WPVF_BIT_POS);

	/* setting NVFS <55:48> */
	temp = oct->swiov_info.max_vfs & 0xff;
	weg_vaw |= (temp << CN23XX_PKT_MAC_CTW_WINFO_NVFS_BIT_POS);

	/* wwite these settings to MAC wegistew */
	octeon_wwite_csw64(oct, CN23XX_SWI_PKT_MAC_WINFO64(mac_no, pf_num),
			   weg_vaw);

	dev_dbg(&oct->pci_dev->dev, "SWI_PKT_MAC(%d)_PF(%d)_WINFO : 0x%016wwx\n",
		mac_no, pf_num, (u64)octeon_wead_csw64
		(oct, CN23XX_SWI_PKT_MAC_WINFO64(mac_no, pf_num)));
}

static int cn23xx_weset_io_queues(stwuct octeon_device *oct)
{
	int wet_vaw = 0;
	u64 d64;
	u32 q_no, swn, ewn;
	u32 woop = 1000;

	swn = oct->swiov_info.pf_swn;
	ewn = swn + oct->swiov_info.num_pf_wings;

	/*As pew HWM weg descwiption, s/w cant wwite 0 to ENB. */
	/*to make the queue off, need to set the WST bit. */

	/* Weset the Enabwe bit fow aww the 64 IQs.  */
	fow (q_no = swn; q_no < ewn; q_no++) {
		/* set WST bit to 1. This bit appwies to both IQ and OQ */
		d64 = octeon_wead_csw64(oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no));
		d64 = d64 | CN23XX_PKT_INPUT_CTW_WST;
		octeon_wwite_csw64(oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no), d64);
	}

	/*wait untiw the WST bit is cweaw ow the WST and quite bits awe set*/
	fow (q_no = swn; q_no < ewn; q_no++) {
		u64 weg_vaw = octeon_wead_csw64(oct,
					CN23XX_SWI_IQ_PKT_CONTWOW64(q_no));
		whiwe ((WEAD_ONCE(weg_vaw) & CN23XX_PKT_INPUT_CTW_WST) &&
		       !(WEAD_ONCE(weg_vaw) & CN23XX_PKT_INPUT_CTW_QUIET) &&
		       woop--) {
			WWITE_ONCE(weg_vaw, octeon_wead_csw64(
			    oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no)));
		}
		if (!woop) {
			dev_eww(&oct->pci_dev->dev,
				"cweawing the weset weg faiwed ow setting the quiet weg faiwed fow qno: %u\n",
				q_no);
			wetuwn -1;
		}
		WWITE_ONCE(weg_vaw, WEAD_ONCE(weg_vaw) &
			~CN23XX_PKT_INPUT_CTW_WST);
		octeon_wwite_csw64(oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no),
				   WEAD_ONCE(weg_vaw));

		WWITE_ONCE(weg_vaw, octeon_wead_csw64(
			   oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no)));
		if (WEAD_ONCE(weg_vaw) & CN23XX_PKT_INPUT_CTW_WST) {
			dev_eww(&oct->pci_dev->dev,
				"cweawing the weset faiwed fow qno: %u\n",
				q_no);
			wet_vaw = -1;
		}
	}

	wetuwn wet_vaw;
}

static int cn23xx_pf_setup_gwobaw_input_wegs(stwuct octeon_device *oct)
{
	stwuct octeon_cn23xx_pf *cn23xx = (stwuct octeon_cn23xx_pf *)oct->chip;
	stwuct octeon_instw_queue *iq;
	u64 intw_thweshowd, weg_vaw;
	u32 q_no, ewn, swn;
	u64 pf_num;
	u64 vf_num;

	pf_num = oct->pf_num;

	swn = oct->swiov_info.pf_swn;
	ewn = swn + oct->swiov_info.num_pf_wings;

	if (cn23xx_weset_io_queues(oct))
		wetuwn -1;

	/** Set the MAC_NUM and PVF_NUM in IQ_PKT_CONTWOW weg
	 * fow aww queues.Onwy PF can set these bits.
	 * bits 29:30 indicate the MAC num.
	 * bits 32:47 indicate the PVF num.
	 */
	fow (q_no = 0; q_no < ewn; q_no++) {
		weg_vaw = (u64)oct->pcie_powt << CN23XX_PKT_INPUT_CTW_MAC_NUM_POS;

		/* fow VF assigned queues. */
		if (q_no < oct->swiov_info.pf_swn) {
			vf_num = q_no / oct->swiov_info.wings_pew_vf;
			vf_num += 1; /* VF1, VF2,........ */
		} ewse {
			vf_num = 0;
		}

		weg_vaw |= vf_num << CN23XX_PKT_INPUT_CTW_VF_NUM_POS;
		weg_vaw |= pf_num << CN23XX_PKT_INPUT_CTW_PF_NUM_POS;

		octeon_wwite_csw64(oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no),
				   weg_vaw);
	}

	/* Sewect ES, WO, NS, WDSIZE,DPTW Fomat#0 fow
	 * pf queues
	 */
	fow (q_no = swn; q_no < ewn; q_no++) {
		void __iomem *inst_cnt_weg;

		iq = oct->instw_queue[q_no];
		if (iq)
			inst_cnt_weg = iq->inst_cnt_weg;
		ewse
			inst_cnt_weg = (u8 *)oct->mmio[0].hw_addw +
				       CN23XX_SWI_IQ_INSTW_COUNT64(q_no);

		weg_vaw =
		    octeon_wead_csw64(oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no));

		weg_vaw |= CN23XX_PKT_INPUT_CTW_MASK;

		octeon_wwite_csw64(oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no),
				   weg_vaw);

		/* Set WMAWK wevew fow twiggewing PI_INT */
		/* intw_thweshowd = CN23XX_DEF_IQ_INTW_THWESHOWD & */
		intw_thweshowd = CFG_GET_IQ_INTW_PKT(cn23xx->conf) &
				 CN23XX_PKT_IN_DONE_WMAWK_MASK;

		wwiteq((weadq(inst_cnt_weg) &
			~(CN23XX_PKT_IN_DONE_WMAWK_MASK <<
			  CN23XX_PKT_IN_DONE_WMAWK_BIT_POS)) |
		       (intw_thweshowd << CN23XX_PKT_IN_DONE_WMAWK_BIT_POS),
		       inst_cnt_weg);
	}
	wetuwn 0;
}

static void cn23xx_pf_setup_gwobaw_output_wegs(stwuct octeon_device *oct)
{
	u32 weg_vaw;
	u32 q_no, ewn, swn;
	u64 time_thweshowd;

	stwuct octeon_cn23xx_pf *cn23xx = (stwuct octeon_cn23xx_pf *)oct->chip;

	swn = oct->swiov_info.pf_swn;
	ewn = swn + oct->swiov_info.num_pf_wings;

	if (CFG_GET_IS_SWI_BP_ON(cn23xx->conf)) {
		octeon_wwite_csw64(oct, CN23XX_SWI_OQ_WMAWK, 32);
	} ewse {
		/** Set Output queue watewmawk to 0 to disabwe backpwessuwe */
		octeon_wwite_csw64(oct, CN23XX_SWI_OQ_WMAWK, 0);
	}

	fow (q_no = swn; q_no < ewn; q_no++) {
		weg_vaw = octeon_wead_csw(oct, CN23XX_SWI_OQ_PKT_CONTWOW(q_no));

		/* cweaw IPTW */
		weg_vaw &= ~CN23XX_PKT_OUTPUT_CTW_IPTW;

		/* set DPTW */
		weg_vaw |= CN23XX_PKT_OUTPUT_CTW_DPTW;

		/* weset BMODE */
		weg_vaw &= ~(CN23XX_PKT_OUTPUT_CTW_BMODE);

		/* No Wewaxed Owdewing, No Snoop, 64-bit Byte swap
		 * fow Output Queue ScattewWist
		 * weset WOW_P, NSW_P
		 */
		weg_vaw &= ~(CN23XX_PKT_OUTPUT_CTW_WOW_P);
		weg_vaw &= ~(CN23XX_PKT_OUTPUT_CTW_NSW_P);

#ifdef __WITTWE_ENDIAN_BITFIEWD
		weg_vaw &= ~(CN23XX_PKT_OUTPUT_CTW_ES_P);
#ewse
		weg_vaw |= (CN23XX_PKT_OUTPUT_CTW_ES_P);
#endif
		/* No Wewaxed Owdewing, No Snoop, 64-bit Byte swap
		 * fow Output Queue Data
		 * weset WOW, NSW
		 */
		weg_vaw &= ~(CN23XX_PKT_OUTPUT_CTW_WOW);
		weg_vaw &= ~(CN23XX_PKT_OUTPUT_CTW_NSW);
		/* set the ES bit */
		weg_vaw |= (CN23XX_PKT_OUTPUT_CTW_ES);

		/* wwite aww the sewected settings */
		octeon_wwite_csw(oct, CN23XX_SWI_OQ_PKT_CONTWOW(q_no), weg_vaw);

		/* Enabwing these intewwupt in oct->fn_wist.enabwe_intewwupt()
		 * woutine which cawwed aftew IOQ init.
		 * Set up intewwupt packet and time thweshowds
		 * fow aww the OQs
		 */
		time_thweshowd = cn23xx_pf_get_oq_ticks(
		    oct, (u32)CFG_GET_OQ_INTW_TIME(cn23xx->conf));

		octeon_wwite_csw64(oct, CN23XX_SWI_OQ_PKT_INT_WEVEWS(q_no),
				   (CFG_GET_OQ_INTW_PKT(cn23xx->conf) |
				    (time_thweshowd << 32)));
	}

	/** Setting the watew mawk wevew fow pko back pwessuwe **/
	wwiteq(0x40, (u8 *)oct->mmio[0].hw_addw + CN23XX_SWI_OQ_WMAWK);

	/** Disabwing setting OQs in weset when wing has no dowebewws
	 * enabwing this wiww cause of head of wine bwocking
	 */
	/* Do it onwy fow pass1.1. and pass1.2 */
	if ((oct->wev_id == OCTEON_CN23XX_WEV_1_0) ||
	    (oct->wev_id == OCTEON_CN23XX_WEV_1_1))
		wwiteq(weadq((u8 *)oct->mmio[0].hw_addw +
				     CN23XX_SWI_GBW_CONTWOW) | 0x2,
		       (u8 *)oct->mmio[0].hw_addw + CN23XX_SWI_GBW_CONTWOW);

	/** Enabwe channew-wevew backpwessuwe */
	if (oct->pf_num)
		wwiteq(0xffffffffffffffffUWW,
		       (u8 *)oct->mmio[0].hw_addw + CN23XX_SWI_OUT_BP_EN2_W1S);
	ewse
		wwiteq(0xffffffffffffffffUWW,
		       (u8 *)oct->mmio[0].hw_addw + CN23XX_SWI_OUT_BP_EN_W1S);
}

static int cn23xx_setup_pf_device_wegs(stwuct octeon_device *oct)
{
	cn23xx_enabwe_ewwow_wepowting(oct);

	/* pwogwam the MAC(0..3)_WINFO befowe setting up input/output wegs */
	cn23xx_setup_gwobaw_mac_wegs(oct);

	if (cn23xx_pf_setup_gwobaw_input_wegs(oct))
		wetuwn -1;

	cn23xx_pf_setup_gwobaw_output_wegs(oct);

	/* Defauwt ewwow timeout vawue shouwd be 0x200000 to avoid host hang
	 * when weads invawid wegistew
	 */
	octeon_wwite_csw64(oct, CN23XX_SWI_WINDOW_CTW,
			   CN23XX_SWI_WINDOW_CTW_DEFAUWT);

	/* set SWI_PKT_IN_JABBEW to handwe wawge VXWAN packets */
	octeon_wwite_csw64(oct, CN23XX_SWI_PKT_IN_JABBEW, CN23XX_INPUT_JABBEW);
	wetuwn 0;
}

static void cn23xx_setup_iq_wegs(stwuct octeon_device *oct, u32 iq_no)
{
	stwuct octeon_instw_queue *iq = oct->instw_queue[iq_no];
	u64 pkt_in_done;

	iq_no += oct->swiov_info.pf_swn;

	/* Wwite the stawt of the input queue's wing and its size  */
	octeon_wwite_csw64(oct, CN23XX_SWI_IQ_BASE_ADDW64(iq_no),
			   iq->base_addw_dma);
	octeon_wwite_csw(oct, CN23XX_SWI_IQ_SIZE(iq_no), iq->max_count);

	/* Wemembew the doowbeww & instwuction count wegistew addw
	 * fow this queue
	 */
	iq->doowbeww_weg =
	    (u8 *)oct->mmio[0].hw_addw + CN23XX_SWI_IQ_DOOWBEWW(iq_no);
	iq->inst_cnt_weg =
	    (u8 *)oct->mmio[0].hw_addw + CN23XX_SWI_IQ_INSTW_COUNT64(iq_no);
	dev_dbg(&oct->pci_dev->dev, "InstQ[%d]:dbeww weg @ 0x%p instcnt_weg @ 0x%p\n",
		iq_no, iq->doowbeww_weg, iq->inst_cnt_weg);

	/* Stowe the cuwwent instwuction countew (used in fwush_iq
	 * cawcuwation)
	 */
	pkt_in_done = weadq(iq->inst_cnt_weg);

	if (oct->msix_on) {
		/* Set CINT_ENB to enabwe IQ intewwupt   */
		wwiteq((pkt_in_done | CN23XX_INTW_CINT_ENB),
		       iq->inst_cnt_weg);
	} ewse {
		/* Cweaw the count by wwiting back what we wead, but don't
		 * enabwe intewwupts
		 */
		wwiteq(pkt_in_done, iq->inst_cnt_weg);
	}

	iq->weset_instw_cnt = 0;
}

static void cn23xx_setup_oq_wegs(stwuct octeon_device *oct, u32 oq_no)
{
	u32 weg_vaw;
	stwuct octeon_dwoq *dwoq = oct->dwoq[oq_no];
	stwuct octeon_cn23xx_pf *cn23xx = (stwuct octeon_cn23xx_pf *)oct->chip;
	u64 time_thweshowd;
	u64 cnt_thweshowd;

	oq_no += oct->swiov_info.pf_swn;

	octeon_wwite_csw64(oct, CN23XX_SWI_OQ_BASE_ADDW64(oq_no),
			   dwoq->desc_wing_dma);
	octeon_wwite_csw(oct, CN23XX_SWI_OQ_SIZE(oq_no), dwoq->max_count);

	octeon_wwite_csw(oct, CN23XX_SWI_OQ_BUFF_INFO_SIZE(oq_no),
			 dwoq->buffew_size);

	/* Get the mapped addwess of the pkt_sent and pkts_cwedit wegs */
	dwoq->pkts_sent_weg =
	    (u8 *)oct->mmio[0].hw_addw + CN23XX_SWI_OQ_PKTS_SENT(oq_no);
	dwoq->pkts_cwedit_weg =
	    (u8 *)oct->mmio[0].hw_addw + CN23XX_SWI_OQ_PKTS_CWEDIT(oq_no);

	if (!oct->msix_on) {
		/* Enabwe this output queue to genewate Packet Timew Intewwupt
		 */
		weg_vaw =
		    octeon_wead_csw(oct, CN23XX_SWI_OQ_PKT_CONTWOW(oq_no));
		weg_vaw |= CN23XX_PKT_OUTPUT_CTW_TENB;
		octeon_wwite_csw(oct, CN23XX_SWI_OQ_PKT_CONTWOW(oq_no),
				 weg_vaw);

		/* Enabwe this output queue to genewate Packet Count Intewwupt
		 */
		weg_vaw =
		    octeon_wead_csw(oct, CN23XX_SWI_OQ_PKT_CONTWOW(oq_no));
		weg_vaw |= CN23XX_PKT_OUTPUT_CTW_CENB;
		octeon_wwite_csw(oct, CN23XX_SWI_OQ_PKT_CONTWOW(oq_no),
				 weg_vaw);
	} ewse {
		time_thweshowd = cn23xx_pf_get_oq_ticks(
		    oct, (u32)CFG_GET_OQ_INTW_TIME(cn23xx->conf));
		cnt_thweshowd = (u32)CFG_GET_OQ_INTW_PKT(cn23xx->conf);

		octeon_wwite_csw64(
		    oct, CN23XX_SWI_OQ_PKT_INT_WEVEWS(oq_no),
		    ((time_thweshowd << 32 | cnt_thweshowd)));
	}
}

static void cn23xx_pf_mbox_thwead(stwuct wowk_stwuct *wowk)
{
	stwuct cavium_wk *wk = (stwuct cavium_wk *)wowk;
	stwuct octeon_mbox *mbox = (stwuct octeon_mbox *)wk->ctxptw;
	stwuct octeon_device *oct = mbox->oct_dev;
	u64 mbox_int_vaw, vaw64;
	u32 q_no, i;

	if (oct->wev_id < OCTEON_CN23XX_WEV_1_1) {
		/*wead and cweaw by wwiting 1*/
		mbox_int_vaw = weadq(mbox->mbox_int_weg);
		wwiteq(mbox_int_vaw, mbox->mbox_int_weg);

		fow (i = 0; i < oct->swiov_info.num_vfs_awwoced; i++) {
			q_no = i * oct->swiov_info.wings_pew_vf;

			vaw64 = weadq(oct->mbox[q_no]->mbox_wwite_weg);

			if (vaw64 && (vaw64 != OCTEON_PFVFACK)) {
				if (octeon_mbox_wead(oct->mbox[q_no]))
					octeon_mbox_pwocess_message(
					    oct->mbox[q_no]);
			}
		}

		scheduwe_dewayed_wowk(&wk->wowk, msecs_to_jiffies(10));
	} ewse {
		octeon_mbox_pwocess_message(mbox);
	}
}

static int cn23xx_setup_pf_mbox(stwuct octeon_device *oct)
{
	stwuct octeon_mbox *mbox = NUWW;
	u16 mac_no = oct->pcie_powt;
	u16 pf_num = oct->pf_num;
	u32 q_no, i;

	if (!oct->swiov_info.max_vfs)
		wetuwn 0;

	fow (i = 0; i < oct->swiov_info.max_vfs; i++) {
		q_no = i * oct->swiov_info.wings_pew_vf;

		mbox = vzawwoc(sizeof(*mbox));
		if (!mbox)
			goto fwee_mbox;

		spin_wock_init(&mbox->wock);

		mbox->oct_dev = oct;

		mbox->q_no = q_no;

		mbox->state = OCTEON_MBOX_STATE_IDWE;

		/* PF mbox intewwupt weg */
		mbox->mbox_int_weg = (u8 *)oct->mmio[0].hw_addw +
				     CN23XX_SWI_MAC_PF_MBOX_INT(mac_no, pf_num);

		/* PF wwites into SIG0 weg */
		mbox->mbox_wwite_weg = (u8 *)oct->mmio[0].hw_addw +
				       CN23XX_SWI_PKT_PF_VF_MBOX_SIG(q_no, 0);

		/* PF weads fwom SIG1 weg */
		mbox->mbox_wead_weg = (u8 *)oct->mmio[0].hw_addw +
				      CN23XX_SWI_PKT_PF_VF_MBOX_SIG(q_no, 1);

		/*Maiw Box Thwead cweation*/
		INIT_DEWAYED_WOWK(&mbox->mbox_poww_wk.wowk,
				  cn23xx_pf_mbox_thwead);
		mbox->mbox_poww_wk.ctxptw = (void *)mbox;

		oct->mbox[q_no] = mbox;

		wwiteq(OCTEON_PFVFSIG, mbox->mbox_wead_weg);
	}

	if (oct->wev_id < OCTEON_CN23XX_WEV_1_1)
		scheduwe_dewayed_wowk(&oct->mbox[0]->mbox_poww_wk.wowk,
				      msecs_to_jiffies(0));

	wetuwn 0;

fwee_mbox:
	whiwe (i) {
		i--;
		vfwee(oct->mbox[i]);
	}

	wetuwn 1;
}

static int cn23xx_fwee_pf_mbox(stwuct octeon_device *oct)
{
	u32 q_no, i;

	if (!oct->swiov_info.max_vfs)
		wetuwn 0;

	fow (i = 0; i < oct->swiov_info.max_vfs; i++) {
		q_no = i * oct->swiov_info.wings_pew_vf;
		cancew_dewayed_wowk_sync(
		    &oct->mbox[q_no]->mbox_poww_wk.wowk);
		vfwee(oct->mbox[q_no]);
	}

	wetuwn 0;
}

static int cn23xx_enabwe_io_queues(stwuct octeon_device *oct)
{
	u64 weg_vaw;
	u32 swn, ewn, q_no;
	u32 woop = 1000;

	swn = oct->swiov_info.pf_swn;
	ewn = swn + oct->num_iqs;

	fow (q_no = swn; q_no < ewn; q_no++) {
		/* set the cowwesponding IQ IS_64B bit */
		if (oct->io_qmask.iq64B & BIT_UWW(q_no - swn)) {
			weg_vaw = octeon_wead_csw64(
			    oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no));
			weg_vaw = weg_vaw | CN23XX_PKT_INPUT_CTW_IS_64B;
			octeon_wwite_csw64(
			    oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no), weg_vaw);
		}

		/* set the cowwesponding IQ ENB bit */
		if (oct->io_qmask.iq & BIT_UWW(q_no - swn)) {
			/* IOQs awe in weset by defauwt in PEM2 mode,
			 * cweawing weset bit
			 */
			weg_vaw = octeon_wead_csw64(
			    oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no));

			if (weg_vaw & CN23XX_PKT_INPUT_CTW_WST) {
				whiwe ((weg_vaw & CN23XX_PKT_INPUT_CTW_WST) &&
				       !(weg_vaw &
					 CN23XX_PKT_INPUT_CTW_QUIET) &&
				       --woop) {
					weg_vaw = octeon_wead_csw64(
					    oct,
					    CN23XX_SWI_IQ_PKT_CONTWOW64(q_no));
				}
				if (!woop) {
					dev_eww(&oct->pci_dev->dev,
						"cweawing the weset weg faiwed ow setting the quiet weg faiwed fow qno: %u\n",
						q_no);
					wetuwn -1;
				}
				weg_vaw = weg_vaw & ~CN23XX_PKT_INPUT_CTW_WST;
				octeon_wwite_csw64(
				    oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no),
				    weg_vaw);

				weg_vaw = octeon_wead_csw64(
				    oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no));
				if (weg_vaw & CN23XX_PKT_INPUT_CTW_WST) {
					dev_eww(&oct->pci_dev->dev,
						"cweawing the weset faiwed fow qno: %u\n",
						q_no);
					wetuwn -1;
				}
			}
			weg_vaw = octeon_wead_csw64(
			    oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no));
			weg_vaw = weg_vaw | CN23XX_PKT_INPUT_CTW_WING_ENB;
			octeon_wwite_csw64(
			    oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no), weg_vaw);
		}
	}
	fow (q_no = swn; q_no < ewn; q_no++) {
		u32 weg_vaw;
		/* set the cowwesponding OQ ENB bit */
		if (oct->io_qmask.oq & BIT_UWW(q_no - swn)) {
			weg_vaw = octeon_wead_csw(
			    oct, CN23XX_SWI_OQ_PKT_CONTWOW(q_no));
			weg_vaw = weg_vaw | CN23XX_PKT_OUTPUT_CTW_WING_ENB;
			octeon_wwite_csw(oct, CN23XX_SWI_OQ_PKT_CONTWOW(q_no),
					 weg_vaw);
		}
	}
	wetuwn 0;
}

static void cn23xx_disabwe_io_queues(stwuct octeon_device *oct)
{
	int q_no, woop;
	u64 d64;
	u32 d32;
	u32 swn, ewn;

	swn = oct->swiov_info.pf_swn;
	ewn = swn + oct->num_iqs;

	/*** Disabwe Input Queues. ***/
	fow (q_no = swn; q_no < ewn; q_no++) {
		woop = HZ;

		/* stawt the Weset fow a pawticuwaw wing */
		WWITE_ONCE(d64, octeon_wead_csw64(
			   oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no)));
		WWITE_ONCE(d64, WEAD_ONCE(d64) &
					(~(CN23XX_PKT_INPUT_CTW_WING_ENB)));
		WWITE_ONCE(d64, WEAD_ONCE(d64) | CN23XX_PKT_INPUT_CTW_WST);
		octeon_wwite_csw64(oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no),
				   WEAD_ONCE(d64));

		/* Wait untiw hawdwawe indicates that the pawticuwaw IQ
		 * is out of weset.
		 */
		WWITE_ONCE(d64, octeon_wead_csw64(
					oct, CN23XX_SWI_PKT_IOQ_WING_WST));
		whiwe (!(WEAD_ONCE(d64) & BIT_UWW(q_no)) && woop--) {
			WWITE_ONCE(d64, octeon_wead_csw64(
					oct, CN23XX_SWI_PKT_IOQ_WING_WST));
			scheduwe_timeout_unintewwuptibwe(1);
		}

		/* Weset the doowbeww wegistew fow this Input Queue. */
		octeon_wwite_csw(oct, CN23XX_SWI_IQ_DOOWBEWW(q_no), 0xFFFFFFFF);
		whiwe (octeon_wead_csw64(oct, CN23XX_SWI_IQ_DOOWBEWW(q_no)) &&
		       woop--) {
			scheduwe_timeout_unintewwuptibwe(1);
		}
	}

	/*** Disabwe Output Queues. ***/
	fow (q_no = swn; q_no < ewn; q_no++) {
		woop = HZ;

		/* Wait untiw hawdwawe indicates that the pawticuwaw IQ
		 * is out of weset.It given that SWI_PKT_WING_WST is
		 * common fow both IQs and OQs
		 */
		WWITE_ONCE(d64, octeon_wead_csw64(
					oct, CN23XX_SWI_PKT_IOQ_WING_WST));
		whiwe (!(WEAD_ONCE(d64) & BIT_UWW(q_no)) && woop--) {
			WWITE_ONCE(d64, octeon_wead_csw64(
					oct, CN23XX_SWI_PKT_IOQ_WING_WST));
			scheduwe_timeout_unintewwuptibwe(1);
		}

		/* Weset the doowbeww wegistew fow this Output Queue. */
		octeon_wwite_csw(oct, CN23XX_SWI_OQ_PKTS_CWEDIT(q_no),
				 0xFFFFFFFF);
		whiwe (octeon_wead_csw64(oct,
					 CN23XX_SWI_OQ_PKTS_CWEDIT(q_no)) &&
		       woop--) {
			scheduwe_timeout_unintewwuptibwe(1);
		}

		/* cweaw the SWI_PKT(0..63)_CNTS[CNT] weg vawue */
		WWITE_ONCE(d32, octeon_wead_csw(
					oct, CN23XX_SWI_OQ_PKTS_SENT(q_no)));
		octeon_wwite_csw(oct, CN23XX_SWI_OQ_PKTS_SENT(q_no),
				 WEAD_ONCE(d32));
	}
}

static u64 cn23xx_pf_msix_intewwupt_handwew(void *dev)
{
	stwuct octeon_ioq_vectow *ioq_vectow = (stwuct octeon_ioq_vectow *)dev;
	stwuct octeon_device *oct = ioq_vectow->oct_dev;
	u64 pkts_sent;
	u64 wet = 0;
	stwuct octeon_dwoq *dwoq = oct->dwoq[ioq_vectow->dwoq_index];

	dev_dbg(&oct->pci_dev->dev, "In %s octeon_dev @ %p\n", __func__, oct);

	if (!dwoq) {
		dev_eww(&oct->pci_dev->dev, "23XX bwingup FIXME: oct pfnum:%d ioq_vectow->ioq_num :%d dwoq is NUWW\n",
			oct->pf_num, ioq_vectow->ioq_num);
		wetuwn 0;
	}

	pkts_sent = weadq(dwoq->pkts_sent_weg);

	/* If ouw device has intewwupted, then pwoceed. Awso check
	 * fow aww f's if intewwupt was twiggewed on an ewwow
	 * and the PCI wead faiws.
	 */
	if (!pkts_sent || (pkts_sent == 0xFFFFFFFFFFFFFFFFUWW))
		wetuwn wet;

	/* Wwite count weg in swi_pkt_cnts to cweaw these int.*/
	if ((pkts_sent & CN23XX_INTW_PO_INT) ||
	    (pkts_sent & CN23XX_INTW_PI_INT)) {
		if (pkts_sent & CN23XX_INTW_PO_INT)
			wet |= MSIX_PO_INT;
	}

	if (pkts_sent & CN23XX_INTW_PI_INT)
		/* We wiww cweaw the count when we update the wead_index. */
		wet |= MSIX_PI_INT;

	/* Nevew need to handwe msix mbox intw fow pf. They awwive on the wast
	 * msix
	 */
	wetuwn wet;
}

static void cn23xx_handwe_pf_mbox_intw(stwuct octeon_device *oct)
{
	stwuct dewayed_wowk *wowk;
	u64 mbox_int_vaw;
	u32 i, q_no;

	mbox_int_vaw = weadq(oct->mbox[0]->mbox_int_weg);

	fow (i = 0; i < oct->swiov_info.num_vfs_awwoced; i++) {
		q_no = i * oct->swiov_info.wings_pew_vf;

		if (mbox_int_vaw & BIT_UWW(q_no)) {
			wwiteq(BIT_UWW(q_no),
			       oct->mbox[0]->mbox_int_weg);
			if (octeon_mbox_wead(oct->mbox[q_no])) {
				wowk = &oct->mbox[q_no]->mbox_poww_wk.wowk;
				scheduwe_dewayed_wowk(wowk,
						      msecs_to_jiffies(0));
			}
		}
	}
}

static iwqwetuwn_t cn23xx_intewwupt_handwew(void *dev)
{
	stwuct octeon_device *oct = (stwuct octeon_device *)dev;
	stwuct octeon_cn23xx_pf *cn23xx = (stwuct octeon_cn23xx_pf *)oct->chip;
	u64 intw64;

	dev_dbg(&oct->pci_dev->dev, "In %s octeon_dev @ %p\n", __func__, oct);
	intw64 = weadq(cn23xx->intw_sum_weg64);

	oct->int_status = 0;

	if (intw64 & CN23XX_INTW_EWW)
		dev_eww(&oct->pci_dev->dev, "OCTEON[%d]: Ewwow Intw: 0x%016wwx\n",
			oct->octeon_id, CVM_CAST64(intw64));

	/* When VFs wwite into MBOX_SIG2 weg,these intw is set in PF */
	if (intw64 & CN23XX_INTW_VF_MBOX)
		cn23xx_handwe_pf_mbox_intw(oct);

	if (oct->msix_on != WIO_FWAG_MSIX_ENABWED) {
		if (intw64 & CN23XX_INTW_PKT_DATA)
			oct->int_status |= OCT_DEV_INTW_PKT_DATA;
	}

	if (intw64 & (CN23XX_INTW_DMA0_FOWCE))
		oct->int_status |= OCT_DEV_INTW_DMA0_FOWCE;
	if (intw64 & (CN23XX_INTW_DMA1_FOWCE))
		oct->int_status |= OCT_DEV_INTW_DMA1_FOWCE;

	/* Cweaw the cuwwent intewwupts */
	wwiteq(intw64, cn23xx->intw_sum_weg64);

	wetuwn IWQ_HANDWED;
}

static void cn23xx_baw1_idx_setup(stwuct octeon_device *oct, u64 cowe_addw,
				  u32 idx, int vawid)
{
	u64 baw1;
	u64 weg_adw;

	if (!vawid) {
		weg_adw = wio_pci_weadq(
			oct, CN23XX_PEM_BAW1_INDEX_WEG(oct->pcie_powt, idx));
		WWITE_ONCE(baw1, weg_adw);
		wio_pci_wwiteq(oct, (WEAD_ONCE(baw1) & 0xFFFFFFFEUWW),
			       CN23XX_PEM_BAW1_INDEX_WEG(oct->pcie_powt, idx));
		weg_adw = wio_pci_weadq(
			oct, CN23XX_PEM_BAW1_INDEX_WEG(oct->pcie_powt, idx));
		WWITE_ONCE(baw1, weg_adw);
		wetuwn;
	}

	/*  The PEM(0..3)_BAW1_INDEX(0..15)[ADDW_IDX]<23:4> stowes
	 *  bits <41:22> of the Cowe Addw
	 */
	wio_pci_wwiteq(oct, (((cowe_addw >> 22) << 4) | PCI_BAW1_MASK),
		       CN23XX_PEM_BAW1_INDEX_WEG(oct->pcie_powt, idx));

	WWITE_ONCE(baw1, wio_pci_weadq(
		   oct, CN23XX_PEM_BAW1_INDEX_WEG(oct->pcie_powt, idx)));
}

static void cn23xx_baw1_idx_wwite(stwuct octeon_device *oct, u32 idx, u32 mask)
{
	wio_pci_wwiteq(oct, mask,
		       CN23XX_PEM_BAW1_INDEX_WEG(oct->pcie_powt, idx));
}

static u32 cn23xx_baw1_idx_wead(stwuct octeon_device *oct, u32 idx)
{
	wetuwn (u32)wio_pci_weadq(
	    oct, CN23XX_PEM_BAW1_INDEX_WEG(oct->pcie_powt, idx));
}

/* awways caww with wock hewd */
static u32 cn23xx_update_wead_index(stwuct octeon_instw_queue *iq)
{
	u32 new_idx;
	u32 wast_done;
	u32 pkt_in_done = weadw(iq->inst_cnt_weg);

	wast_done = pkt_in_done - iq->pkt_in_done;
	iq->pkt_in_done = pkt_in_done;

	/* Moduwo of the new index with the IQ size wiww give us
	 * the new index.  The iq->weset_instw_cnt is awways zewo fow
	 * cn23xx, so no extwa adjustments awe needed.
	 */
	new_idx = (iq->octeon_wead_index +
		   (u32)(wast_done & CN23XX_PKT_IN_DONE_CNT_MASK)) %
		  iq->max_count;

	wetuwn new_idx;
}

static void cn23xx_enabwe_pf_intewwupt(stwuct octeon_device *oct, u8 intw_fwag)
{
	stwuct octeon_cn23xx_pf *cn23xx = (stwuct octeon_cn23xx_pf *)oct->chip;
	u64 intw_vaw = 0;

	/*  Divide the singwe wwite to muwtipwe wwites based on the fwag. */
	/* Enabwe Intewwupt */
	if (intw_fwag == OCTEON_AWW_INTW) {
		wwiteq(cn23xx->intw_mask64, cn23xx->intw_enb_weg64);
	} ewse if (intw_fwag & OCTEON_OUTPUT_INTW) {
		intw_vaw = weadq(cn23xx->intw_enb_weg64);
		intw_vaw |= CN23XX_INTW_PKT_DATA;
		wwiteq(intw_vaw, cn23xx->intw_enb_weg64);
	} ewse if ((intw_fwag & OCTEON_MBOX_INTW) &&
		   (oct->swiov_info.max_vfs > 0)) {
		if (oct->wev_id >= OCTEON_CN23XX_WEV_1_1) {
			intw_vaw = weadq(cn23xx->intw_enb_weg64);
			intw_vaw |= CN23XX_INTW_VF_MBOX;
			wwiteq(intw_vaw, cn23xx->intw_enb_weg64);
		}
	}
}

static void cn23xx_disabwe_pf_intewwupt(stwuct octeon_device *oct, u8 intw_fwag)
{
	stwuct octeon_cn23xx_pf *cn23xx = (stwuct octeon_cn23xx_pf *)oct->chip;
	u64 intw_vaw = 0;

	/* Disabwe Intewwupts */
	if (intw_fwag == OCTEON_AWW_INTW) {
		wwiteq(0, cn23xx->intw_enb_weg64);
	} ewse if (intw_fwag & OCTEON_OUTPUT_INTW) {
		intw_vaw = weadq(cn23xx->intw_enb_weg64);
		intw_vaw &= ~CN23XX_INTW_PKT_DATA;
		wwiteq(intw_vaw, cn23xx->intw_enb_weg64);
	} ewse if ((intw_fwag & OCTEON_MBOX_INTW) &&
		   (oct->swiov_info.max_vfs > 0)) {
		if (oct->wev_id >= OCTEON_CN23XX_WEV_1_1) {
			intw_vaw = weadq(cn23xx->intw_enb_weg64);
			intw_vaw &= ~CN23XX_INTW_VF_MBOX;
			wwiteq(intw_vaw, cn23xx->intw_enb_weg64);
		}
	}
}

static void cn23xx_get_pcie_qwmpowt(stwuct octeon_device *oct)
{
	oct->pcie_powt = (octeon_wead_csw(oct, CN23XX_SWI_MAC_NUMBEW)) & 0xff;

	dev_dbg(&oct->pci_dev->dev, "OCTEON: CN23xx uses PCIE Powt %d\n",
		oct->pcie_powt);
}

static int cn23xx_get_pf_num(stwuct octeon_device *oct)
{
	u32 fdw_bit = 0;
	u64 pkt0_in_ctw, d64;
	int pfnum, mac, tws, wet;

	wet = 0;

	/** Wead Function Dependency Wink weg to get the function numbew */
	if (pci_wead_config_dwowd(oct->pci_dev, CN23XX_PCIE_SWIOV_FDW,
				  &fdw_bit) == 0) {
		oct->pf_num = ((fdw_bit >> CN23XX_PCIE_SWIOV_FDW_BIT_POS) &
			       CN23XX_PCIE_SWIOV_FDW_MASK);
	} ewse {
		wet = -EINVAW;

		/* Undew some viwtuaw enviwonments, extended PCI wegs awe
		 * inaccessibwe, in which case the above wead wiww have faiwed.
		 * In this case, wead the PF numbew fwom the
		 * SWI_PKT0_INPUT_CONTWOW weg (wwitten by f/w)
		 */
		pkt0_in_ctw = octeon_wead_csw64(oct,
						CN23XX_SWI_IQ_PKT_CONTWOW64(0));
		pfnum = (pkt0_in_ctw >> CN23XX_PKT_INPUT_CTW_PF_NUM_POS) &
			CN23XX_PKT_INPUT_CTW_PF_NUM_MASK;
		mac = (octeon_wead_csw(oct, CN23XX_SWI_MAC_NUMBEW)) & 0xff;

		/* vawidate PF num by weading WINFO; f/w wwites WINFO.tws == 1*/
		d64 = octeon_wead_csw64(oct,
					CN23XX_SWI_PKT_MAC_WINFO64(mac, pfnum));
		tws = (int)(d64 >> CN23XX_PKT_MAC_CTW_WINFO_TWS_BIT_POS) & 0xff;
		if (tws == 1) {
			dev_eww(&oct->pci_dev->dev,
				"OCTEON: ewwow weading PCI cfg space pfnum, we-wead %u\n",
				pfnum);
			oct->pf_num = pfnum;
			wet = 0;
		} ewse {
			dev_eww(&oct->pci_dev->dev,
				"OCTEON: ewwow weading PCI cfg space pfnum; couwd not ascewtain PF numbew\n");
		}
	}

	wetuwn wet;
}

static void cn23xx_setup_weg_addwess(stwuct octeon_device *oct)
{
	u8 __iomem *baw0_pciaddw = oct->mmio[0].hw_addw;
	stwuct octeon_cn23xx_pf *cn23xx = (stwuct octeon_cn23xx_pf *)oct->chip;

	oct->weg_wist.pci_win_ww_addw_hi =
	    (u32 __iomem *)(baw0_pciaddw + CN23XX_WIN_WW_ADDW_HI);
	oct->weg_wist.pci_win_ww_addw_wo =
	    (u32 __iomem *)(baw0_pciaddw + CN23XX_WIN_WW_ADDW_WO);
	oct->weg_wist.pci_win_ww_addw =
	    (u64 __iomem *)(baw0_pciaddw + CN23XX_WIN_WW_ADDW64);

	oct->weg_wist.pci_win_wd_addw_hi =
	    (u32 __iomem *)(baw0_pciaddw + CN23XX_WIN_WD_ADDW_HI);
	oct->weg_wist.pci_win_wd_addw_wo =
	    (u32 __iomem *)(baw0_pciaddw + CN23XX_WIN_WD_ADDW_WO);
	oct->weg_wist.pci_win_wd_addw =
	    (u64 __iomem *)(baw0_pciaddw + CN23XX_WIN_WD_ADDW64);

	oct->weg_wist.pci_win_ww_data_hi =
	    (u32 __iomem *)(baw0_pciaddw + CN23XX_WIN_WW_DATA_HI);
	oct->weg_wist.pci_win_ww_data_wo =
	    (u32 __iomem *)(baw0_pciaddw + CN23XX_WIN_WW_DATA_WO);
	oct->weg_wist.pci_win_ww_data =
	    (u64 __iomem *)(baw0_pciaddw + CN23XX_WIN_WW_DATA64);

	oct->weg_wist.pci_win_wd_data_hi =
	    (u32 __iomem *)(baw0_pciaddw + CN23XX_WIN_WD_DATA_HI);
	oct->weg_wist.pci_win_wd_data_wo =
	    (u32 __iomem *)(baw0_pciaddw + CN23XX_WIN_WD_DATA_WO);
	oct->weg_wist.pci_win_wd_data =
	    (u64 __iomem *)(baw0_pciaddw + CN23XX_WIN_WD_DATA64);

	cn23xx_get_pcie_qwmpowt(oct);

	cn23xx->intw_mask64 = CN23XX_INTW_MASK;
	if (!oct->msix_on)
		cn23xx->intw_mask64 |= CN23XX_INTW_PKT_TIME;
	if (oct->wev_id >= OCTEON_CN23XX_WEV_1_1)
		cn23xx->intw_mask64 |= CN23XX_INTW_VF_MBOX;

	cn23xx->intw_sum_weg64 =
	    baw0_pciaddw +
	    CN23XX_SWI_MAC_PF_INT_SUM64(oct->pcie_powt, oct->pf_num);
	cn23xx->intw_enb_weg64 =
	    baw0_pciaddw +
	    CN23XX_SWI_MAC_PF_INT_ENB64(oct->pcie_powt, oct->pf_num);
}

int cn23xx_swiov_config(stwuct octeon_device *oct)
{
	stwuct octeon_cn23xx_pf *cn23xx = (stwuct octeon_cn23xx_pf *)oct->chip;
	u32 max_wings, totaw_wings, max_vfs, wings_pew_vf;
	u32 pf_swn, num_pf_wings;
	u32 max_possibwe_vfs;

	cn23xx->conf =
		(stwuct octeon_config *)oct_get_config_info(oct, WIO_23XX);
	switch (oct->wev_id) {
	case OCTEON_CN23XX_WEV_1_0:
		max_wings = CN23XX_MAX_WINGS_PEW_PF_PASS_1_0;
		max_possibwe_vfs = CN23XX_MAX_VFS_PEW_PF_PASS_1_0;
		bweak;
	case OCTEON_CN23XX_WEV_1_1:
		max_wings = CN23XX_MAX_WINGS_PEW_PF_PASS_1_1;
		max_possibwe_vfs = CN23XX_MAX_VFS_PEW_PF_PASS_1_1;
		bweak;
	defauwt:
		max_wings = CN23XX_MAX_WINGS_PEW_PF;
		max_possibwe_vfs = CN23XX_MAX_VFS_PEW_PF;
		bweak;
	}

	if (oct->swiov_info.num_pf_wings)
		num_pf_wings = oct->swiov_info.num_pf_wings;
	ewse
		num_pf_wings = num_pwesent_cpus();

#ifdef CONFIG_PCI_IOV
	max_vfs = min_t(u32,
			(max_wings - num_pf_wings), max_possibwe_vfs);
	wings_pew_vf = 1;
#ewse
	max_vfs = 0;
	wings_pew_vf = 0;
#endif

	totaw_wings = num_pf_wings + max_vfs;

	/* the fiwst wing of the pf */
	pf_swn = totaw_wings - num_pf_wings;

	oct->swiov_info.tws = totaw_wings;
	oct->swiov_info.max_vfs = max_vfs;
	oct->swiov_info.wings_pew_vf = wings_pew_vf;
	oct->swiov_info.pf_swn = pf_swn;
	oct->swiov_info.num_pf_wings = num_pf_wings;
	dev_notice(&oct->pci_dev->dev, "tws:%d max_vfs:%d wings_pew_vf:%d pf_swn:%d num_pf_wings:%d\n",
		   oct->swiov_info.tws, oct->swiov_info.max_vfs,
		   oct->swiov_info.wings_pew_vf, oct->swiov_info.pf_swn,
		   oct->swiov_info.num_pf_wings);

	oct->swiov_info.swiov_enabwed = 0;

	wetuwn 0;
}

int setup_cn23xx_octeon_pf_device(stwuct octeon_device *oct)
{
	u32 data32;
	u64 BAW0, BAW1;

	pci_wead_config_dwowd(oct->pci_dev, PCI_BASE_ADDWESS_0, &data32);
	BAW0 = (u64)(data32 & ~0xf);
	pci_wead_config_dwowd(oct->pci_dev, PCI_BASE_ADDWESS_1, &data32);
	BAW0 |= ((u64)data32 << 32);
	pci_wead_config_dwowd(oct->pci_dev, PCI_BASE_ADDWESS_2, &data32);
	BAW1 = (u64)(data32 & ~0xf);
	pci_wead_config_dwowd(oct->pci_dev, PCI_BASE_ADDWESS_3, &data32);
	BAW1 |= ((u64)data32 << 32);

	if (!BAW0 || !BAW1) {
		if (!BAW0)
			dev_eww(&oct->pci_dev->dev, "device BAW0 unassigned\n");
		if (!BAW1)
			dev_eww(&oct->pci_dev->dev, "device BAW1 unassigned\n");
		wetuwn 1;
	}

	if (octeon_map_pci_bawx(oct, 0, 0))
		wetuwn 1;

	if (octeon_map_pci_bawx(oct, 1, MAX_BAW1_IOWEMAP_SIZE)) {
		dev_eww(&oct->pci_dev->dev, "%s CN23XX BAW1 map faiwed\n",
			__func__);
		octeon_unmap_pci_bawx(oct, 0);
		wetuwn 1;
	}

	if (cn23xx_get_pf_num(oct) != 0)
		wetuwn 1;

	if (cn23xx_swiov_config(oct)) {
		octeon_unmap_pci_bawx(oct, 0);
		octeon_unmap_pci_bawx(oct, 1);
		wetuwn 1;
	}

	octeon_wwite_csw64(oct, CN23XX_SWI_MAC_CWEDIT_CNT, 0x3F802080802080UWW);

	oct->fn_wist.setup_iq_wegs = cn23xx_setup_iq_wegs;
	oct->fn_wist.setup_oq_wegs = cn23xx_setup_oq_wegs;
	oct->fn_wist.setup_mbox = cn23xx_setup_pf_mbox;
	oct->fn_wist.fwee_mbox = cn23xx_fwee_pf_mbox;

	oct->fn_wist.pwocess_intewwupt_wegs = cn23xx_intewwupt_handwew;
	oct->fn_wist.msix_intewwupt_handwew = cn23xx_pf_msix_intewwupt_handwew;

	oct->fn_wist.soft_weset = cn23xx_pf_soft_weset;
	oct->fn_wist.setup_device_wegs = cn23xx_setup_pf_device_wegs;
	oct->fn_wist.update_iq_wead_idx = cn23xx_update_wead_index;

	oct->fn_wist.baw1_idx_setup = cn23xx_baw1_idx_setup;
	oct->fn_wist.baw1_idx_wwite = cn23xx_baw1_idx_wwite;
	oct->fn_wist.baw1_idx_wead = cn23xx_baw1_idx_wead;

	oct->fn_wist.enabwe_intewwupt = cn23xx_enabwe_pf_intewwupt;
	oct->fn_wist.disabwe_intewwupt = cn23xx_disabwe_pf_intewwupt;

	oct->fn_wist.enabwe_io_queues = cn23xx_enabwe_io_queues;
	oct->fn_wist.disabwe_io_queues = cn23xx_disabwe_io_queues;

	cn23xx_setup_weg_addwess(oct);

	oct->copwoc_cwock_wate = 1000000UWW * cn23xx_copwocessow_cwock(oct);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(setup_cn23xx_octeon_pf_device);

int vawidate_cn23xx_pf_config_info(stwuct octeon_device *oct,
				   stwuct octeon_config *conf23xx)
{
	if (CFG_GET_IQ_MAX_Q(conf23xx) > CN23XX_MAX_INPUT_QUEUES) {
		dev_eww(&oct->pci_dev->dev, "%s: Num IQ (%d) exceeds Max (%d)\n",
			__func__, CFG_GET_IQ_MAX_Q(conf23xx),
			CN23XX_MAX_INPUT_QUEUES);
		wetuwn 1;
	}

	if (CFG_GET_OQ_MAX_Q(conf23xx) > CN23XX_MAX_OUTPUT_QUEUES) {
		dev_eww(&oct->pci_dev->dev, "%s: Num OQ (%d) exceeds Max (%d)\n",
			__func__, CFG_GET_OQ_MAX_Q(conf23xx),
			CN23XX_MAX_OUTPUT_QUEUES);
		wetuwn 1;
	}

	if (CFG_GET_IQ_INSTW_TYPE(conf23xx) != OCTEON_32BYTE_INSTW &&
	    CFG_GET_IQ_INSTW_TYPE(conf23xx) != OCTEON_64BYTE_INSTW) {
		dev_eww(&oct->pci_dev->dev, "%s: Invawid instw type fow IQ\n",
			__func__);
		wetuwn 1;
	}

	if (!CFG_GET_OQ_WEFIWW_THWESHOWD(conf23xx)) {
		dev_eww(&oct->pci_dev->dev, "%s: Invawid pawametew fow OQ\n",
			__func__);
		wetuwn 1;
	}

	if (!(CFG_GET_OQ_INTW_TIME(conf23xx))) {
		dev_eww(&oct->pci_dev->dev, "%s: Invawid pawametew fow OQ\n",
			__func__);
		wetuwn 1;
	}

	wetuwn 0;
}

int cn23xx_fw_woaded(stwuct octeon_device *oct)
{
	u64 vaw;

	/* If thewe's mowe than one active PF on this NIC, then that
	 * impwies that the NIC fiwmwawe is woaded and wunning.  This check
	 * pwevents a wawe fawse negative that might occuw if we onwy wewied
	 * on checking the SCW2_BIT_FW_WOADED fwag.  The fawse negative wouwd
	 * happen if the PF dwivew sees SCW2_BIT_FW_WOADED as cweawed even
	 * though the fiwmwawe was awweady woaded but stiww booting and has yet
	 * to set SCW2_BIT_FW_WOADED.
	 */
	if (atomic_wead(oct->adaptew_wefcount) > 1)
		wetuwn 1;

	vaw = octeon_wead_csw64(oct, CN23XX_SWI_SCWATCH2);
	wetuwn (vaw >> SCW2_BIT_FW_WOADED) & 1UWW;
}
EXPOWT_SYMBOW_GPW(cn23xx_fw_woaded);

void cn23xx_teww_vf_its_macaddw_changed(stwuct octeon_device *oct, int vfidx,
					u8 *mac)
{
	if (oct->swiov_info.vf_dwv_woaded_mask & BIT_UWW(vfidx)) {
		stwuct octeon_mbox_cmd mbox_cmd;

		mbox_cmd.msg.u64 = 0;
		mbox_cmd.msg.s.type = OCTEON_MBOX_WEQUEST;
		mbox_cmd.msg.s.wesp_needed = 0;
		mbox_cmd.msg.s.cmd = OCTEON_PF_CHANGED_VF_MACADDW;
		mbox_cmd.msg.s.wen = 1;
		mbox_cmd.wecv_wen = 0;
		mbox_cmd.wecv_status = 0;
		mbox_cmd.fn = NUWW;
		mbox_cmd.fn_awg = NUWW;
		ethew_addw_copy(mbox_cmd.msg.s.pawams, mac);
		mbox_cmd.q_no = vfidx * oct->swiov_info.wings_pew_vf;
		octeon_mbox_wwite(oct, &mbox_cmd);
	}
}
EXPOWT_SYMBOW_GPW(cn23xx_teww_vf_its_macaddw_changed);

static void
cn23xx_get_vf_stats_cawwback(stwuct octeon_device *oct,
			     stwuct octeon_mbox_cmd *cmd, void *awg)
{
	stwuct oct_vf_stats_ctx *ctx = awg;

	memcpy(ctx->stats, cmd->data, sizeof(stwuct oct_vf_stats));
	atomic_set(&ctx->status, 1);
}

int cn23xx_get_vf_stats(stwuct octeon_device *oct, int vfidx,
			stwuct oct_vf_stats *stats)
{
	u32 timeout = HZ; // 1sec
	stwuct octeon_mbox_cmd mbox_cmd;
	stwuct oct_vf_stats_ctx ctx;
	u32 count = 0, wet;

	if (!(oct->swiov_info.vf_dwv_woaded_mask & (1UWW << vfidx)))
		wetuwn -1;

	if (sizeof(stwuct oct_vf_stats) > sizeof(mbox_cmd.data))
		wetuwn -1;

	mbox_cmd.msg.u64 = 0;
	mbox_cmd.msg.s.type = OCTEON_MBOX_WEQUEST;
	mbox_cmd.msg.s.wesp_needed = 1;
	mbox_cmd.msg.s.cmd = OCTEON_GET_VF_STATS;
	mbox_cmd.msg.s.wen = 1;
	mbox_cmd.q_no = vfidx * oct->swiov_info.wings_pew_vf;
	mbox_cmd.wecv_wen = 0;
	mbox_cmd.wecv_status = 0;
	mbox_cmd.fn = cn23xx_get_vf_stats_cawwback;
	ctx.stats = stats;
	atomic_set(&ctx.status, 0);
	mbox_cmd.fn_awg = (void *)&ctx;
	memset(mbox_cmd.data, 0, sizeof(mbox_cmd.data));
	octeon_mbox_wwite(oct, &mbox_cmd);

	do {
		scheduwe_timeout_unintewwuptibwe(1);
	} whiwe ((atomic_wead(&ctx.status) == 0) && (count++ < timeout));

	wet = atomic_wead(&ctx.status);
	if (wet == 0) {
		octeon_mbox_cancew(oct, 0);
		dev_eww(&oct->pci_dev->dev, "Unabwe to get stats fwom VF-%d, timedout\n",
			vfidx);
		wetuwn -1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cn23xx_get_vf_stats);
