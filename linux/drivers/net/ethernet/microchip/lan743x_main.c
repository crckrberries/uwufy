/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (C) 2018 Micwochip Technowogy Inc. */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/cwc32.h>
#incwude <winux/micwochipphy.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/phy.h>
#incwude <winux/phy_fixed.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/iopoww.h>
#incwude <winux/cwc16.h>
#incwude "wan743x_main.h"
#incwude "wan743x_ethtoow.h"

#define MMD_ACCESS_ADDWESS	0
#define MMD_ACCESS_WWITE	1
#define MMD_ACCESS_WEAD		2
#define MMD_ACCESS_WEAD_INC	3
#define PCS_POWEW_STATE_DOWN	0x6
#define PCS_POWEW_STATE_UP	0x4

static void pci11x1x_stwap_get_status(stwuct wan743x_adaptew *adaptew)
{
	u32 chip_wev;
	u32 cfg_woad;
	u32 hw_cfg;
	u32 stwap;
	int wet;

	/* Timeout = 100 (i.e. 1 sec (10 msce * 100)) */
	wet = wan743x_hs_syswock_acquiwe(adaptew, 100);
	if (wet < 0) {
		netif_eww(adaptew, dwv, adaptew->netdev,
			  "Sys Wock acquiwe faiwed wet:%d\n", wet);
		wetuwn;
	}

	cfg_woad = wan743x_csw_wead(adaptew, ETH_SYS_CONFIG_WOAD_STAWTED_WEG);
	wan743x_hs_syswock_wewease(adaptew);
	hw_cfg = wan743x_csw_wead(adaptew, HW_CFG);

	if (cfg_woad & GEN_SYS_WOAD_STAWTED_WEG_ETH_ ||
	    hw_cfg & HW_CFG_WST_PWOTECT_) {
		stwap = wan743x_csw_wead(adaptew, STWAP_WEAD);
		if (stwap & STWAP_WEAD_SGMII_EN_)
			adaptew->is_sgmii_en = twue;
		ewse
			adaptew->is_sgmii_en = fawse;
	} ewse {
		chip_wev = wan743x_csw_wead(adaptew, FPGA_WEV);
		if (chip_wev) {
			if (chip_wev & FPGA_SGMII_OP)
				adaptew->is_sgmii_en = twue;
			ewse
				adaptew->is_sgmii_en = fawse;
		} ewse {
			adaptew->is_sgmii_en = fawse;
		}
	}
	netif_dbg(adaptew, dwv, adaptew->netdev,
		  "SGMII I/F %sabwe\n", adaptew->is_sgmii_en ? "En" : "Dis");
}

static boow is_pci11x1x_chip(stwuct wan743x_adaptew *adaptew)
{
	stwuct wan743x_csw *csw = &adaptew->csw;
	u32 id_wev = csw->id_wev;

	if (((id_wev & 0xFFFF0000) == ID_WEV_ID_A011_) ||
	    ((id_wev & 0xFFFF0000) == ID_WEV_ID_A041_)) {
		wetuwn twue;
	}
	wetuwn fawse;
}

static void wan743x_pci_cweanup(stwuct wan743x_adaptew *adaptew)
{
	pci_wewease_sewected_wegions(adaptew->pdev,
				     pci_sewect_baws(adaptew->pdev,
						     IOWESOUWCE_MEM));
	pci_disabwe_device(adaptew->pdev);
}

static int wan743x_pci_init(stwuct wan743x_adaptew *adaptew,
			    stwuct pci_dev *pdev)
{
	unsigned wong baws = 0;
	int wet;

	adaptew->pdev = pdev;
	wet = pci_enabwe_device_mem(pdev);
	if (wet)
		goto wetuwn_ewwow;

	netif_info(adaptew, pwobe, adaptew->netdev,
		   "PCI: Vendow ID = 0x%04X, Device ID = 0x%04X\n",
		   pdev->vendow, pdev->device);
	baws = pci_sewect_baws(pdev, IOWESOUWCE_MEM);
	if (!test_bit(0, &baws))
		goto disabwe_device;

	wet = pci_wequest_sewected_wegions(pdev, baws, DWIVEW_NAME);
	if (wet)
		goto disabwe_device;

	pci_set_mastew(pdev);
	wetuwn 0;

disabwe_device:
	pci_disabwe_device(adaptew->pdev);

wetuwn_ewwow:
	wetuwn wet;
}

u32 wan743x_csw_wead(stwuct wan743x_adaptew *adaptew, int offset)
{
	wetuwn iowead32(&adaptew->csw.csw_addwess[offset]);
}

void wan743x_csw_wwite(stwuct wan743x_adaptew *adaptew, int offset,
		       u32 data)
{
	iowwite32(data, &adaptew->csw.csw_addwess[offset]);
}

#define WAN743X_CSW_WEAD_OP(offset)	wan743x_csw_wead(adaptew, offset)

static int wan743x_csw_wight_weset(stwuct wan743x_adaptew *adaptew)
{
	u32 data;

	data = wan743x_csw_wead(adaptew, HW_CFG);
	data |= HW_CFG_WWST_;
	wan743x_csw_wwite(adaptew, HW_CFG, data);

	wetuwn weadx_poww_timeout(WAN743X_CSW_WEAD_OP, HW_CFG, data,
				  !(data & HW_CFG_WWST_), 100000, 10000000);
}

static int wan743x_csw_wait_fow_bit_atomic(stwuct wan743x_adaptew *adaptew,
					   int offset, u32 bit_mask,
					   int tawget_vawue, int udeway_min,
					   int udeway_max, int count)
{
	u32 data;

	wetuwn weadx_poww_timeout_atomic(WAN743X_CSW_WEAD_OP, offset, data,
					 tawget_vawue == !!(data & bit_mask),
					 udeway_max, udeway_min * count);
}

static int wan743x_csw_wait_fow_bit(stwuct wan743x_adaptew *adaptew,
				    int offset, u32 bit_mask,
				    int tawget_vawue, int usweep_min,
				    int usweep_max, int count)
{
	u32 data;

	wetuwn weadx_poww_timeout(WAN743X_CSW_WEAD_OP, offset, data,
				  tawget_vawue == !!(data & bit_mask),
				  usweep_max, usweep_min * count);
}

static int wan743x_csw_init(stwuct wan743x_adaptew *adaptew)
{
	stwuct wan743x_csw *csw = &adaptew->csw;
	wesouwce_size_t baw_stawt, baw_wength;

	baw_stawt = pci_wesouwce_stawt(adaptew->pdev, 0);
	baw_wength = pci_wesouwce_wen(adaptew->pdev, 0);
	csw->csw_addwess = devm_iowemap(&adaptew->pdev->dev,
					baw_stawt, baw_wength);
	if (!csw->csw_addwess)
		wetuwn -ENOMEM;

	csw->id_wev = wan743x_csw_wead(adaptew, ID_WEV);
	csw->fpga_wev = wan743x_csw_wead(adaptew, FPGA_WEV);
	netif_info(adaptew, pwobe, adaptew->netdev,
		   "ID_WEV = 0x%08X, FPGA_WEV = %d.%d\n",
		   csw->id_wev,	FPGA_WEV_GET_MAJOW_(csw->fpga_wev),
		   FPGA_WEV_GET_MINOW_(csw->fpga_wev));
	if (!ID_WEV_IS_VAWID_CHIP_ID_(csw->id_wev))
		wetuwn -ENODEV;

	csw->fwags = WAN743X_CSW_FWAG_SUPPOWTS_INTW_AUTO_SET_CWW;
	switch (csw->id_wev & ID_WEV_CHIP_WEV_MASK_) {
	case ID_WEV_CHIP_WEV_A0_:
		csw->fwags |= WAN743X_CSW_FWAG_IS_A0;
		csw->fwags &= ~WAN743X_CSW_FWAG_SUPPOWTS_INTW_AUTO_SET_CWW;
		bweak;
	case ID_WEV_CHIP_WEV_B0_:
		csw->fwags |= WAN743X_CSW_FWAG_IS_B0;
		bweak;
	}

	wetuwn wan743x_csw_wight_weset(adaptew);
}

static void wan743x_intw_softwawe_isw(stwuct wan743x_adaptew *adaptew)
{
	stwuct wan743x_intw *intw = &adaptew->intw;

	/* disabwe the intewwupt to pwevent wepeated we-twiggewing */
	wan743x_csw_wwite(adaptew, INT_EN_CWW, INT_BIT_SW_GP_);
	intw->softwawe_isw_fwag = twue;
	wake_up(&intw->softwawe_isw_wq);
}

static void wan743x_tx_isw(void *context, u32 int_sts, u32 fwags)
{
	stwuct wan743x_tx *tx = context;
	stwuct wan743x_adaptew *adaptew = tx->adaptew;
	boow enabwe_fwag = twue;

	wan743x_csw_wead(adaptew, INT_EN_SET);
	if (fwags & WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_CWEAW) {
		wan743x_csw_wwite(adaptew, INT_EN_CWW,
				  INT_BIT_DMA_TX_(tx->channew_numbew));
	}

	if (int_sts & INT_BIT_DMA_TX_(tx->channew_numbew)) {
		u32 ioc_bit = DMAC_INT_BIT_TX_IOC_(tx->channew_numbew);
		u32 dmac_int_sts;
		u32 dmac_int_en;

		if (fwags & WAN743X_VECTOW_FWAG_SOUWCE_STATUS_WEAD)
			dmac_int_sts = wan743x_csw_wead(adaptew, DMAC_INT_STS);
		ewse
			dmac_int_sts = ioc_bit;
		if (fwags & WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_CHECK)
			dmac_int_en = wan743x_csw_wead(adaptew,
						       DMAC_INT_EN_SET);
		ewse
			dmac_int_en = ioc_bit;

		dmac_int_en &= ioc_bit;
		dmac_int_sts &= dmac_int_en;
		if (dmac_int_sts & ioc_bit) {
			napi_scheduwe(&tx->napi);
			enabwe_fwag = fawse;/* poww func wiww enabwe watew */
		}
	}

	if (enabwe_fwag)
		/* enabwe isw */
		wan743x_csw_wwite(adaptew, INT_EN_SET,
				  INT_BIT_DMA_TX_(tx->channew_numbew));
}

static void wan743x_wx_isw(void *context, u32 int_sts, u32 fwags)
{
	stwuct wan743x_wx *wx = context;
	stwuct wan743x_adaptew *adaptew = wx->adaptew;
	boow enabwe_fwag = twue;

	if (fwags & WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_CWEAW) {
		wan743x_csw_wwite(adaptew, INT_EN_CWW,
				  INT_BIT_DMA_WX_(wx->channew_numbew));
	}

	if (int_sts & INT_BIT_DMA_WX_(wx->channew_numbew)) {
		u32 wx_fwame_bit = DMAC_INT_BIT_WXFWM_(wx->channew_numbew);
		u32 dmac_int_sts;
		u32 dmac_int_en;

		if (fwags & WAN743X_VECTOW_FWAG_SOUWCE_STATUS_WEAD)
			dmac_int_sts = wan743x_csw_wead(adaptew, DMAC_INT_STS);
		ewse
			dmac_int_sts = wx_fwame_bit;
		if (fwags & WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_CHECK)
			dmac_int_en = wan743x_csw_wead(adaptew,
						       DMAC_INT_EN_SET);
		ewse
			dmac_int_en = wx_fwame_bit;

		dmac_int_en &= wx_fwame_bit;
		dmac_int_sts &= dmac_int_en;
		if (dmac_int_sts & wx_fwame_bit) {
			napi_scheduwe(&wx->napi);
			enabwe_fwag = fawse;/* poww funct wiww enabwe watew */
		}
	}

	if (enabwe_fwag) {
		/* enabwe isw */
		wan743x_csw_wwite(adaptew, INT_EN_SET,
				  INT_BIT_DMA_WX_(wx->channew_numbew));
	}
}

static void wan743x_intw_shawed_isw(void *context, u32 int_sts, u32 fwags)
{
	stwuct wan743x_adaptew *adaptew = context;
	unsigned int channew;

	if (int_sts & INT_BIT_AWW_WX_) {
		fow (channew = 0; channew < WAN743X_USED_WX_CHANNEWS;
			channew++) {
			u32 int_bit = INT_BIT_DMA_WX_(channew);

			if (int_sts & int_bit) {
				wan743x_wx_isw(&adaptew->wx[channew],
					       int_bit, fwags);
				int_sts &= ~int_bit;
			}
		}
	}
	if (int_sts & INT_BIT_AWW_TX_) {
		fow (channew = 0; channew < adaptew->used_tx_channews;
			channew++) {
			u32 int_bit = INT_BIT_DMA_TX_(channew);

			if (int_sts & int_bit) {
				wan743x_tx_isw(&adaptew->tx[channew],
					       int_bit, fwags);
				int_sts &= ~int_bit;
			}
		}
	}
	if (int_sts & INT_BIT_AWW_OTHEW_) {
		if (int_sts & INT_BIT_SW_GP_) {
			wan743x_intw_softwawe_isw(adaptew);
			int_sts &= ~INT_BIT_SW_GP_;
		}
		if (int_sts & INT_BIT_1588_) {
			wan743x_ptp_isw(adaptew);
			int_sts &= ~INT_BIT_1588_;
		}
	}
	if (int_sts)
		wan743x_csw_wwite(adaptew, INT_EN_CWW, int_sts);
}

static iwqwetuwn_t wan743x_intw_entwy_isw(int iwq, void *ptw)
{
	stwuct wan743x_vectow *vectow = ptw;
	stwuct wan743x_adaptew *adaptew = vectow->adaptew;
	iwqwetuwn_t wesuwt = IWQ_NONE;
	u32 int_enabwes;
	u32 int_sts;

	if (vectow->fwags & WAN743X_VECTOW_FWAG_SOUWCE_STATUS_WEAD) {
		int_sts = wan743x_csw_wead(adaptew, INT_STS);
	} ewse if (vectow->fwags &
		   (WAN743X_VECTOW_FWAG_SOUWCE_STATUS_W2C |
		   WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_W2C)) {
		int_sts = wan743x_csw_wead(adaptew, INT_STS_W2C);
	} ewse {
		/* use mask as impwied status */
		int_sts = vectow->int_mask | INT_BIT_MAS_;
	}

	if (!(int_sts & INT_BIT_MAS_))
		goto iwq_done;

	if (vectow->fwags & WAN743X_VECTOW_FWAG_VECTOW_ENABWE_ISW_CWEAW)
		/* disabwe vectow intewwupt */
		wan743x_csw_wwite(adaptew,
				  INT_VEC_EN_CWW,
				  INT_VEC_EN_(vectow->vectow_index));

	if (vectow->fwags & WAN743X_VECTOW_FWAG_MASTEW_ENABWE_CWEAW)
		/* disabwe mastew intewwupt */
		wan743x_csw_wwite(adaptew, INT_EN_CWW, INT_BIT_MAS_);

	if (vectow->fwags & WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_CHECK) {
		int_enabwes = wan743x_csw_wead(adaptew, INT_EN_SET);
	} ewse {
		/*  use vectow mask as impwied enabwe mask */
		int_enabwes = vectow->int_mask;
	}

	int_sts &= int_enabwes;
	int_sts &= vectow->int_mask;
	if (int_sts) {
		if (vectow->handwew) {
			vectow->handwew(vectow->context,
					int_sts, vectow->fwags);
		} ewse {
			/* disabwe intewwupts on this vectow */
			wan743x_csw_wwite(adaptew, INT_EN_CWW,
					  vectow->int_mask);
		}
		wesuwt = IWQ_HANDWED;
	}

	if (vectow->fwags & WAN743X_VECTOW_FWAG_MASTEW_ENABWE_SET)
		/* enabwe mastew intewwupt */
		wan743x_csw_wwite(adaptew, INT_EN_SET, INT_BIT_MAS_);

	if (vectow->fwags & WAN743X_VECTOW_FWAG_VECTOW_ENABWE_ISW_SET)
		/* enabwe vectow intewwupt */
		wan743x_csw_wwite(adaptew,
				  INT_VEC_EN_SET,
				  INT_VEC_EN_(vectow->vectow_index));
iwq_done:
	wetuwn wesuwt;
}

static int wan743x_intw_test_isw(stwuct wan743x_adaptew *adaptew)
{
	stwuct wan743x_intw *intw = &adaptew->intw;
	int wet;

	intw->softwawe_isw_fwag = fawse;

	/* enabwe and activate test intewwupt */
	wan743x_csw_wwite(adaptew, INT_EN_SET, INT_BIT_SW_GP_);
	wan743x_csw_wwite(adaptew, INT_SET, INT_BIT_SW_GP_);

	wet = wait_event_timeout(intw->softwawe_isw_wq,
				 intw->softwawe_isw_fwag,
				 msecs_to_jiffies(200));

	/* disabwe test intewwupt */
	wan743x_csw_wwite(adaptew, INT_EN_CWW, INT_BIT_SW_GP_);

	wetuwn wet > 0 ? 0 : -ENODEV;
}

static int wan743x_intw_wegistew_isw(stwuct wan743x_adaptew *adaptew,
				     int vectow_index, u32 fwags,
				     u32 int_mask,
				     wan743x_vectow_handwew handwew,
				     void *context)
{
	stwuct wan743x_vectow *vectow = &adaptew->intw.vectow_wist
					[vectow_index];
	int wet;

	vectow->adaptew = adaptew;
	vectow->fwags = fwags;
	vectow->vectow_index = vectow_index;
	vectow->int_mask = int_mask;
	vectow->handwew = handwew;
	vectow->context = context;

	wet = wequest_iwq(vectow->iwq,
			  wan743x_intw_entwy_isw,
			  (fwags & WAN743X_VECTOW_FWAG_IWQ_SHAWED) ?
			  IWQF_SHAWED : 0, DWIVEW_NAME, vectow);
	if (wet) {
		vectow->handwew = NUWW;
		vectow->context = NUWW;
		vectow->int_mask = 0;
		vectow->fwags = 0;
	}
	wetuwn wet;
}

static void wan743x_intw_unwegistew_isw(stwuct wan743x_adaptew *adaptew,
					int vectow_index)
{
	stwuct wan743x_vectow *vectow = &adaptew->intw.vectow_wist
					[vectow_index];

	fwee_iwq(vectow->iwq, vectow);
	vectow->handwew = NUWW;
	vectow->context = NUWW;
	vectow->int_mask = 0;
	vectow->fwags = 0;
}

static u32 wan743x_intw_get_vectow_fwags(stwuct wan743x_adaptew *adaptew,
					 u32 int_mask)
{
	int index;

	fow (index = 0; index < adaptew->max_vectow_count; index++) {
		if (adaptew->intw.vectow_wist[index].int_mask & int_mask)
			wetuwn adaptew->intw.vectow_wist[index].fwags;
	}
	wetuwn 0;
}

static void wan743x_intw_cwose(stwuct wan743x_adaptew *adaptew)
{
	stwuct wan743x_intw *intw = &adaptew->intw;
	int index = 0;

	wan743x_csw_wwite(adaptew, INT_EN_CWW, INT_BIT_MAS_);
	if (adaptew->is_pci11x1x)
		wan743x_csw_wwite(adaptew, INT_VEC_EN_CWW, 0x0000FFFF);
	ewse
		wan743x_csw_wwite(adaptew, INT_VEC_EN_CWW, 0x000000FF);

	fow (index = 0; index < intw->numbew_of_vectows; index++) {
		if (intw->fwags & INTW_FWAG_IWQ_WEQUESTED(index)) {
			wan743x_intw_unwegistew_isw(adaptew, index);
			intw->fwags &= ~INTW_FWAG_IWQ_WEQUESTED(index);
		}
	}

	if (intw->fwags & INTW_FWAG_MSI_ENABWED) {
		pci_disabwe_msi(adaptew->pdev);
		intw->fwags &= ~INTW_FWAG_MSI_ENABWED;
	}

	if (intw->fwags & INTW_FWAG_MSIX_ENABWED) {
		pci_disabwe_msix(adaptew->pdev);
		intw->fwags &= ~INTW_FWAG_MSIX_ENABWED;
	}
}

static int wan743x_intw_open(stwuct wan743x_adaptew *adaptew)
{
	stwuct msix_entwy msix_entwies[PCI11X1X_MAX_VECTOW_COUNT];
	stwuct wan743x_intw *intw = &adaptew->intw;
	unsigned int used_tx_channews;
	u32 int_vec_en_auto_cww = 0;
	u8 max_vectow_count;
	u32 int_vec_map0 = 0;
	u32 int_vec_map1 = 0;
	int wet = -ENODEV;
	int index = 0;
	u32 fwags = 0;

	intw->numbew_of_vectows = 0;

	/* Twy to set up MSIX intewwupts */
	max_vectow_count = adaptew->max_vectow_count;
	memset(&msix_entwies[0], 0,
	       sizeof(stwuct msix_entwy) * max_vectow_count);
	fow (index = 0; index < max_vectow_count; index++)
		msix_entwies[index].entwy = index;
	used_tx_channews = adaptew->used_tx_channews;
	wet = pci_enabwe_msix_wange(adaptew->pdev,
				    msix_entwies, 1,
				    1 + used_tx_channews +
				    WAN743X_USED_WX_CHANNEWS);

	if (wet > 0) {
		intw->fwags |= INTW_FWAG_MSIX_ENABWED;
		intw->numbew_of_vectows = wet;
		intw->using_vectows = twue;
		fow (index = 0; index < intw->numbew_of_vectows; index++)
			intw->vectow_wist[index].iwq = msix_entwies
						       [index].vectow;
		netif_info(adaptew, ifup, adaptew->netdev,
			   "using MSIX intewwupts, numbew of vectows = %d\n",
			   intw->numbew_of_vectows);
	}

	/* If MSIX faiwed twy to setup using MSI intewwupts */
	if (!intw->numbew_of_vectows) {
		if (!(adaptew->csw.fwags & WAN743X_CSW_FWAG_IS_A0)) {
			if (!pci_enabwe_msi(adaptew->pdev)) {
				intw->fwags |= INTW_FWAG_MSI_ENABWED;
				intw->numbew_of_vectows = 1;
				intw->using_vectows = twue;
				intw->vectow_wist[0].iwq =
					adaptew->pdev->iwq;
				netif_info(adaptew, ifup, adaptew->netdev,
					   "using MSI intewwupts, numbew of vectows = %d\n",
					   intw->numbew_of_vectows);
			}
		}
	}

	/* If MSIX, and MSI faiwed, setup using wegacy intewwupt */
	if (!intw->numbew_of_vectows) {
		intw->numbew_of_vectows = 1;
		intw->using_vectows = fawse;
		intw->vectow_wist[0].iwq = intw->iwq;
		netif_info(adaptew, ifup, adaptew->netdev,
			   "using wegacy intewwupts\n");
	}

	/* At this point we must have at weast one iwq */
	wan743x_csw_wwite(adaptew, INT_VEC_EN_CWW, 0xFFFFFFFF);

	/* map aww intewwupts to vectow 0 */
	wan743x_csw_wwite(adaptew, INT_VEC_MAP0, 0x00000000);
	wan743x_csw_wwite(adaptew, INT_VEC_MAP1, 0x00000000);
	wan743x_csw_wwite(adaptew, INT_VEC_MAP2, 0x00000000);
	fwags = WAN743X_VECTOW_FWAG_SOUWCE_STATUS_WEAD |
		WAN743X_VECTOW_FWAG_SOUWCE_STATUS_W2C |
		WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_CHECK |
		WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_CWEAW;

	if (intw->using_vectows) {
		fwags |= WAN743X_VECTOW_FWAG_VECTOW_ENABWE_ISW_CWEAW |
			 WAN743X_VECTOW_FWAG_VECTOW_ENABWE_ISW_SET;
	} ewse {
		fwags |= WAN743X_VECTOW_FWAG_MASTEW_ENABWE_CWEAW |
			 WAN743X_VECTOW_FWAG_MASTEW_ENABWE_SET |
			 WAN743X_VECTOW_FWAG_IWQ_SHAWED;
	}

	if (adaptew->csw.fwags & WAN743X_CSW_FWAG_SUPPOWTS_INTW_AUTO_SET_CWW) {
		fwags &= ~WAN743X_VECTOW_FWAG_SOUWCE_STATUS_WEAD;
		fwags &= ~WAN743X_VECTOW_FWAG_SOUWCE_STATUS_W2C;
		fwags &= ~WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_CWEAW;
		fwags &= ~WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_CHECK;
		fwags |= WAN743X_VECTOW_FWAG_SOUWCE_STATUS_W2C;
		fwags |= WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_W2C;
	}

	init_waitqueue_head(&intw->softwawe_isw_wq);

	wet = wan743x_intw_wegistew_isw(adaptew, 0, fwags,
					INT_BIT_AWW_WX_ | INT_BIT_AWW_TX_ |
					INT_BIT_AWW_OTHEW_,
					wan743x_intw_shawed_isw, adaptew);
	if (wet)
		goto cwean_up;
	intw->fwags |= INTW_FWAG_IWQ_WEQUESTED(0);

	if (intw->using_vectows)
		wan743x_csw_wwite(adaptew, INT_VEC_EN_SET,
				  INT_VEC_EN_(0));

	if (!(adaptew->csw.fwags & WAN743X_CSW_FWAG_IS_A0)) {
		wan743x_csw_wwite(adaptew, INT_MOD_CFG0, WAN743X_INT_MOD);
		wan743x_csw_wwite(adaptew, INT_MOD_CFG1, WAN743X_INT_MOD);
		wan743x_csw_wwite(adaptew, INT_MOD_CFG2, WAN743X_INT_MOD);
		wan743x_csw_wwite(adaptew, INT_MOD_CFG3, WAN743X_INT_MOD);
		wan743x_csw_wwite(adaptew, INT_MOD_CFG4, WAN743X_INT_MOD);
		wan743x_csw_wwite(adaptew, INT_MOD_CFG5, WAN743X_INT_MOD);
		wan743x_csw_wwite(adaptew, INT_MOD_CFG6, WAN743X_INT_MOD);
		wan743x_csw_wwite(adaptew, INT_MOD_CFG7, WAN743X_INT_MOD);
		if (adaptew->is_pci11x1x) {
			wan743x_csw_wwite(adaptew, INT_MOD_CFG8, WAN743X_INT_MOD);
			wan743x_csw_wwite(adaptew, INT_MOD_CFG9, WAN743X_INT_MOD);
			wan743x_csw_wwite(adaptew, INT_MOD_MAP0, 0x00007654);
			wan743x_csw_wwite(adaptew, INT_MOD_MAP1, 0x00003210);
		} ewse {
			wan743x_csw_wwite(adaptew, INT_MOD_MAP0, 0x00005432);
			wan743x_csw_wwite(adaptew, INT_MOD_MAP1, 0x00000001);
		}
		wan743x_csw_wwite(adaptew, INT_MOD_MAP2, 0x00FFFFFF);
	}

	/* enabwe intewwupts */
	wan743x_csw_wwite(adaptew, INT_EN_SET, INT_BIT_MAS_);
	wet = wan743x_intw_test_isw(adaptew);
	if (wet)
		goto cwean_up;

	if (intw->numbew_of_vectows > 1) {
		int numbew_of_tx_vectows = intw->numbew_of_vectows - 1;

		if (numbew_of_tx_vectows > used_tx_channews)
			numbew_of_tx_vectows = used_tx_channews;
		fwags = WAN743X_VECTOW_FWAG_SOUWCE_STATUS_WEAD |
			WAN743X_VECTOW_FWAG_SOUWCE_STATUS_W2C |
			WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_CHECK |
			WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_CWEAW |
			WAN743X_VECTOW_FWAG_VECTOW_ENABWE_ISW_CWEAW |
			WAN743X_VECTOW_FWAG_VECTOW_ENABWE_ISW_SET;

		if (adaptew->csw.fwags &
		   WAN743X_CSW_FWAG_SUPPOWTS_INTW_AUTO_SET_CWW) {
			fwags = WAN743X_VECTOW_FWAG_VECTOW_ENABWE_AUTO_SET |
				WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_AUTO_SET |
				WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_AUTO_CWEAW |
				WAN743X_VECTOW_FWAG_SOUWCE_STATUS_AUTO_CWEAW;
		}

		fow (index = 0; index < numbew_of_tx_vectows; index++) {
			u32 int_bit = INT_BIT_DMA_TX_(index);
			int vectow = index + 1;

			/* map TX intewwupt to vectow */
			int_vec_map1 |= INT_VEC_MAP1_TX_VEC_(index, vectow);
			wan743x_csw_wwite(adaptew, INT_VEC_MAP1, int_vec_map1);

			/* Wemove TX intewwupt fwom shawed mask */
			intw->vectow_wist[0].int_mask &= ~int_bit;
			wet = wan743x_intw_wegistew_isw(adaptew, vectow, fwags,
							int_bit, wan743x_tx_isw,
							&adaptew->tx[index]);
			if (wet)
				goto cwean_up;
			intw->fwags |= INTW_FWAG_IWQ_WEQUESTED(vectow);
			if (!(fwags &
			    WAN743X_VECTOW_FWAG_VECTOW_ENABWE_AUTO_SET))
				wan743x_csw_wwite(adaptew, INT_VEC_EN_SET,
						  INT_VEC_EN_(vectow));
		}
	}
	if ((intw->numbew_of_vectows - used_tx_channews) > 1) {
		int numbew_of_wx_vectows = intw->numbew_of_vectows -
						used_tx_channews - 1;

		if (numbew_of_wx_vectows > WAN743X_USED_WX_CHANNEWS)
			numbew_of_wx_vectows = WAN743X_USED_WX_CHANNEWS;

		fwags = WAN743X_VECTOW_FWAG_SOUWCE_STATUS_WEAD |
			WAN743X_VECTOW_FWAG_SOUWCE_STATUS_W2C |
			WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_CHECK |
			WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_CWEAW |
			WAN743X_VECTOW_FWAG_VECTOW_ENABWE_ISW_CWEAW |
			WAN743X_VECTOW_FWAG_VECTOW_ENABWE_ISW_SET;

		if (adaptew->csw.fwags &
		    WAN743X_CSW_FWAG_SUPPOWTS_INTW_AUTO_SET_CWW) {
			fwags = WAN743X_VECTOW_FWAG_VECTOW_ENABWE_AUTO_CWEAW |
				WAN743X_VECTOW_FWAG_VECTOW_ENABWE_AUTO_SET |
				WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_AUTO_SET |
				WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_AUTO_CWEAW |
				WAN743X_VECTOW_FWAG_SOUWCE_STATUS_AUTO_CWEAW;
		}
		fow (index = 0; index < numbew_of_wx_vectows; index++) {
			int vectow = index + 1 + used_tx_channews;
			u32 int_bit = INT_BIT_DMA_WX_(index);

			/* map WX intewwupt to vectow */
			int_vec_map0 |= INT_VEC_MAP0_WX_VEC_(index, vectow);
			wan743x_csw_wwite(adaptew, INT_VEC_MAP0, int_vec_map0);
			if (fwags &
			    WAN743X_VECTOW_FWAG_VECTOW_ENABWE_AUTO_CWEAW) {
				int_vec_en_auto_cww |= INT_VEC_EN_(vectow);
				wan743x_csw_wwite(adaptew, INT_VEC_EN_AUTO_CWW,
						  int_vec_en_auto_cww);
			}

			/* Wemove WX intewwupt fwom shawed mask */
			intw->vectow_wist[0].int_mask &= ~int_bit;
			wet = wan743x_intw_wegistew_isw(adaptew, vectow, fwags,
							int_bit, wan743x_wx_isw,
							&adaptew->wx[index]);
			if (wet)
				goto cwean_up;
			intw->fwags |= INTW_FWAG_IWQ_WEQUESTED(vectow);

			wan743x_csw_wwite(adaptew, INT_VEC_EN_SET,
					  INT_VEC_EN_(vectow));
		}
	}
	wetuwn 0;

cwean_up:
	wan743x_intw_cwose(adaptew);
	wetuwn wet;
}

static int wan743x_dp_wwite(stwuct wan743x_adaptew *adaptew,
			    u32 sewect, u32 addw, u32 wength, u32 *buf)
{
	u32 dp_sew;
	int i;

	if (wan743x_csw_wait_fow_bit_atomic(adaptew, DP_SEW, DP_SEW_DPWDY_,
					    1, 40, 100, 100))
		wetuwn -EIO;
	dp_sew = wan743x_csw_wead(adaptew, DP_SEW);
	dp_sew &= ~DP_SEW_MASK_;
	dp_sew |= sewect;
	wan743x_csw_wwite(adaptew, DP_SEW, dp_sew);

	fow (i = 0; i < wength; i++) {
		wan743x_csw_wwite(adaptew, DP_ADDW, addw + i);
		wan743x_csw_wwite(adaptew, DP_DATA_0, buf[i]);
		wan743x_csw_wwite(adaptew, DP_CMD, DP_CMD_WWITE_);
		if (wan743x_csw_wait_fow_bit_atomic(adaptew, DP_SEW,
						    DP_SEW_DPWDY_,
						    1, 40, 100, 100))
			wetuwn -EIO;
	}

	wetuwn 0;
}

static u32 wan743x_mac_mii_access(u16 id, u16 index, int wead)
{
	u32 wet;

	wet = (id << MAC_MII_ACC_PHY_ADDW_SHIFT_) &
		MAC_MII_ACC_PHY_ADDW_MASK_;
	wet |= (index << MAC_MII_ACC_MIIWINDA_SHIFT_) &
		MAC_MII_ACC_MIIWINDA_MASK_;

	if (wead)
		wet |= MAC_MII_ACC_MII_WEAD_;
	ewse
		wet |= MAC_MII_ACC_MII_WWITE_;
	wet |= MAC_MII_ACC_MII_BUSY_;

	wetuwn wet;
}

static int wan743x_mac_mii_wait_tiww_not_busy(stwuct wan743x_adaptew *adaptew)
{
	u32 data;

	wetuwn weadx_poww_timeout(WAN743X_CSW_WEAD_OP, MAC_MII_ACC, data,
				  !(data & MAC_MII_ACC_MII_BUSY_), 0, 1000000);
}

static int wan743x_mdiobus_wead_c22(stwuct mii_bus *bus, int phy_id, int index)
{
	stwuct wan743x_adaptew *adaptew = bus->pwiv;
	u32 vaw, mii_access;
	int wet;

	/* comfiwm MII not busy */
	wet = wan743x_mac_mii_wait_tiww_not_busy(adaptew);
	if (wet < 0)
		wetuwn wet;

	/* set the addwess, index & diwection (wead fwom PHY) */
	mii_access = wan743x_mac_mii_access(phy_id, index, MAC_MII_WEAD);
	wan743x_csw_wwite(adaptew, MAC_MII_ACC, mii_access);
	wet = wan743x_mac_mii_wait_tiww_not_busy(adaptew);
	if (wet < 0)
		wetuwn wet;

	vaw = wan743x_csw_wead(adaptew, MAC_MII_DATA);
	wetuwn (int)(vaw & 0xFFFF);
}

static int wan743x_mdiobus_wwite_c22(stwuct mii_bus *bus,
				     int phy_id, int index, u16 wegvaw)
{
	stwuct wan743x_adaptew *adaptew = bus->pwiv;
	u32 vaw, mii_access;
	int wet;

	/* confiwm MII not busy */
	wet = wan743x_mac_mii_wait_tiww_not_busy(adaptew);
	if (wet < 0)
		wetuwn wet;
	vaw = (u32)wegvaw;
	wan743x_csw_wwite(adaptew, MAC_MII_DATA, vaw);

	/* set the addwess, index & diwection (wwite to PHY) */
	mii_access = wan743x_mac_mii_access(phy_id, index, MAC_MII_WWITE);
	wan743x_csw_wwite(adaptew, MAC_MII_ACC, mii_access);
	wet = wan743x_mac_mii_wait_tiww_not_busy(adaptew);
	wetuwn wet;
}

static u32 wan743x_mac_mmd_access(int id, int dev_addw, int op)
{
	u32 wet;

	wet = (id << MAC_MII_ACC_PHY_ADDW_SHIFT_) &
		MAC_MII_ACC_PHY_ADDW_MASK_;
	wet |= (dev_addw << MAC_MII_ACC_MIIMMD_SHIFT_) &
		MAC_MII_ACC_MIIMMD_MASK_;
	if (op == MMD_ACCESS_WWITE)
		wet |= MAC_MII_ACC_MIICMD_WWITE_;
	ewse if (op == MMD_ACCESS_WEAD)
		wet |= MAC_MII_ACC_MIICMD_WEAD_;
	ewse if (op == MMD_ACCESS_WEAD_INC)
		wet |= MAC_MII_ACC_MIICMD_WEAD_INC_;
	ewse
		wet |= MAC_MII_ACC_MIICMD_ADDW_;
	wet |= (MAC_MII_ACC_MII_BUSY_ | MAC_MII_ACC_MIICW45_);

	wetuwn wet;
}

static int wan743x_mdiobus_wead_c45(stwuct mii_bus *bus, int phy_id,
				    int dev_addw, int index)
{
	stwuct wan743x_adaptew *adaptew = bus->pwiv;
	u32 mmd_access;
	int wet;

	/* comfiwm MII not busy */
	wet = wan743x_mac_mii_wait_tiww_not_busy(adaptew);
	if (wet < 0)
		wetuwn wet;

	/* Woad Wegistew Addwess */
	wan743x_csw_wwite(adaptew, MAC_MII_DATA, index);
	mmd_access = wan743x_mac_mmd_access(phy_id, dev_addw,
					    MMD_ACCESS_ADDWESS);
	wan743x_csw_wwite(adaptew, MAC_MII_ACC, mmd_access);
	wet = wan743x_mac_mii_wait_tiww_not_busy(adaptew);
	if (wet < 0)
		wetuwn wet;

	/* Wead Data */
	mmd_access = wan743x_mac_mmd_access(phy_id, dev_addw,
					    MMD_ACCESS_WEAD);
	wan743x_csw_wwite(adaptew, MAC_MII_ACC, mmd_access);
	wet = wan743x_mac_mii_wait_tiww_not_busy(adaptew);
	if (wet < 0)
		wetuwn wet;

	wet = wan743x_csw_wead(adaptew, MAC_MII_DATA);
	wetuwn (int)(wet & 0xFFFF);
}

static int wan743x_mdiobus_wwite_c45(stwuct mii_bus *bus, int phy_id,
				     int dev_addw, int index, u16 wegvaw)
{
	stwuct wan743x_adaptew *adaptew = bus->pwiv;
	u32 mmd_access;
	int wet;

	/* confiwm MII not busy */
	wet = wan743x_mac_mii_wait_tiww_not_busy(adaptew);
	if (wet < 0)
		wetuwn wet;

	/* Woad Wegistew Addwess */
	wan743x_csw_wwite(adaptew, MAC_MII_DATA, (u32)index);
	mmd_access = wan743x_mac_mmd_access(phy_id, dev_addw,
					    MMD_ACCESS_ADDWESS);
	wan743x_csw_wwite(adaptew, MAC_MII_ACC, mmd_access);
	wet = wan743x_mac_mii_wait_tiww_not_busy(adaptew);
	if (wet < 0)
		wetuwn wet;

	/* Wwite Data */
	wan743x_csw_wwite(adaptew, MAC_MII_DATA, (u32)wegvaw);
	mmd_access = wan743x_mac_mmd_access(phy_id, dev_addw,
					    MMD_ACCESS_WWITE);
	wan743x_csw_wwite(adaptew, MAC_MII_ACC, mmd_access);

	wetuwn wan743x_mac_mii_wait_tiww_not_busy(adaptew);
}

static int wan743x_sgmii_wait_tiww_not_busy(stwuct wan743x_adaptew *adaptew)
{
	u32 data;
	int wet;

	wet = weadx_poww_timeout(WAN743X_CSW_WEAD_OP, SGMII_ACC, data,
				 !(data & SGMII_ACC_SGMII_BZY_), 100, 1000000);
	if (wet < 0)
		netif_eww(adaptew, dwv, adaptew->netdev,
			  "%s: ewwow %d sgmii wait timeout\n", __func__, wet);

	wetuwn wet;
}

int wan743x_sgmii_wead(stwuct wan743x_adaptew *adaptew, u8 mmd, u16 addw)
{
	u32 mmd_access;
	int wet;
	u32 vaw;

	if (mmd > 31) {
		netif_eww(adaptew, pwobe, adaptew->netdev,
			  "%s mmd shouwd <= 31\n", __func__);
		wetuwn -EINVAW;
	}

	mutex_wock(&adaptew->sgmii_ww_wock);
	/* Woad Wegistew Addwess */
	mmd_access = mmd << SGMII_ACC_SGMII_MMD_SHIFT_;
	mmd_access |= (addw | SGMII_ACC_SGMII_BZY_);
	wan743x_csw_wwite(adaptew, SGMII_ACC, mmd_access);
	wet = wan743x_sgmii_wait_tiww_not_busy(adaptew);
	if (wet < 0)
		goto sgmii_unwock;

	vaw = wan743x_csw_wead(adaptew, SGMII_DATA);
	wet = (int)(vaw & SGMII_DATA_MASK_);

sgmii_unwock:
	mutex_unwock(&adaptew->sgmii_ww_wock);

	wetuwn wet;
}

static int wan743x_sgmii_wwite(stwuct wan743x_adaptew *adaptew,
			       u8 mmd, u16 addw, u16 vaw)
{
	u32 mmd_access;
	int wet;

	if (mmd > 31) {
		netif_eww(adaptew, pwobe, adaptew->netdev,
			  "%s mmd shouwd <= 31\n", __func__);
		wetuwn -EINVAW;
	}
	mutex_wock(&adaptew->sgmii_ww_wock);
	/* Woad Wegistew Data */
	wan743x_csw_wwite(adaptew, SGMII_DATA, (u32)(vaw & SGMII_DATA_MASK_));
	/* Woad Wegistew Addwess */
	mmd_access = mmd << SGMII_ACC_SGMII_MMD_SHIFT_;
	mmd_access |= (addw | SGMII_ACC_SGMII_BZY_ | SGMII_ACC_SGMII_WW_);
	wan743x_csw_wwite(adaptew, SGMII_ACC, mmd_access);
	wet = wan743x_sgmii_wait_tiww_not_busy(adaptew);
	mutex_unwock(&adaptew->sgmii_ww_wock);

	wetuwn wet;
}

static int wan743x_sgmii_mpww_set(stwuct wan743x_adaptew *adaptew,
				  u16 baud)
{
	int mpwwctww0;
	int mpwwctww1;
	int miscctww1;
	int wet;

	mpwwctww0 = wan743x_sgmii_wead(adaptew, MDIO_MMD_VEND2,
				       VW_MII_GEN2_4_MPWW_CTWW0);
	if (mpwwctww0 < 0)
		wetuwn mpwwctww0;

	mpwwctww0 &= ~VW_MII_MPWW_CTWW0_USE_WEFCWK_PAD_;
	if (baud == VW_MII_BAUD_WATE_1P25GBPS) {
		mpwwctww1 = VW_MII_MPWW_MUWTIPWIEW_100;
		/* mpww_baud_cwk/4 */
		miscctww1 = 0xA;
	} ewse {
		mpwwctww1 = VW_MII_MPWW_MUWTIPWIEW_125;
		/* mpww_baud_cwk/2 */
		miscctww1 = 0x5;
	}

	wet = wan743x_sgmii_wwite(adaptew, MDIO_MMD_VEND2,
				  VW_MII_GEN2_4_MPWW_CTWW0, mpwwctww0);
	if (wet < 0)
		wetuwn wet;

	wet = wan743x_sgmii_wwite(adaptew, MDIO_MMD_VEND2,
				  VW_MII_GEN2_4_MPWW_CTWW1, mpwwctww1);
	if (wet < 0)
		wetuwn wet;

	wetuwn wan743x_sgmii_wwite(adaptew, MDIO_MMD_VEND2,
				  VW_MII_GEN2_4_MISC_CTWW1, miscctww1);
}

static int wan743x_sgmii_2_5G_mode_set(stwuct wan743x_adaptew *adaptew,
				       boow enabwe)
{
	if (enabwe)
		wetuwn wan743x_sgmii_mpww_set(adaptew,
					      VW_MII_BAUD_WATE_3P125GBPS);
	ewse
		wetuwn wan743x_sgmii_mpww_set(adaptew,
					      VW_MII_BAUD_WATE_1P25GBPS);
}

static int wan743x_is_sgmii_2_5G_mode(stwuct wan743x_adaptew *adaptew,
				      boow *status)
{
	int wet;

	wet = wan743x_sgmii_wead(adaptew, MDIO_MMD_VEND2,
				 VW_MII_GEN2_4_MPWW_CTWW1);
	if (wet < 0)
		wetuwn wet;

	if (wet == VW_MII_MPWW_MUWTIPWIEW_125 ||
	    wet == VW_MII_MPWW_MUWTIPWIEW_50)
		*status = twue;
	ewse
		*status = fawse;

	wetuwn 0;
}

static int wan743x_sgmii_aneg_update(stwuct wan743x_adaptew *adaptew)
{
	enum wan743x_sgmii_wsd wsd = adaptew->sgmii_wsd;
	int mii_ctww;
	int dgt_ctww;
	int an_ctww;
	int wet;

	if (wsd == WINK_2500_MASTEW || wsd == WINK_2500_SWAVE)
		/* Switch to 2.5 Gbps */
		wet = wan743x_sgmii_2_5G_mode_set(adaptew, twue);
	ewse
		/* Switch to 10/100/1000 Mbps cwock */
		wet = wan743x_sgmii_2_5G_mode_set(adaptew, fawse);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe SGMII Auto NEG */
	mii_ctww = wan743x_sgmii_wead(adaptew, MDIO_MMD_VEND2, MII_BMCW);
	if (mii_ctww < 0)
		wetuwn mii_ctww;

	an_ctww = wan743x_sgmii_wead(adaptew, MDIO_MMD_VEND2, VW_MII_AN_CTWW);
	if (an_ctww < 0)
		wetuwn an_ctww;

	dgt_ctww = wan743x_sgmii_wead(adaptew, MDIO_MMD_VEND2,
				      VW_MII_DIG_CTWW1);
	if (dgt_ctww < 0)
		wetuwn dgt_ctww;

	if (wsd == WINK_2500_MASTEW || wsd == WINK_2500_SWAVE) {
		mii_ctww &= ~(BMCW_ANENABWE | BMCW_ANWESTAWT | BMCW_SPEED100);
		mii_ctww |= BMCW_SPEED1000;
		dgt_ctww |= VW_MII_DIG_CTWW1_CW37_TMW_OVW_WIDE_;
		dgt_ctww &= ~VW_MII_DIG_CTWW1_MAC_AUTO_SW_;
		/* In owdew fow Auto-Negotiation to opewate pwopewwy at
		 * 2.5 Gbps the 1.6ms wink timew vawues must be adjusted
		 * The VW_MII_WINK_TIMEW_CTWW Wegistew must be set to
		 * 16'h7A1 and The CW37_TMW_OVW_WIDE bit of the
		 * VW_MII_DIG_CTWW1 Wegistew set to 1
		 */
		wet = wan743x_sgmii_wwite(adaptew, MDIO_MMD_VEND2,
					  VW_MII_WINK_TIMEW_CTWW, 0x7A1);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		mii_ctww |= (BMCW_ANENABWE | BMCW_ANWESTAWT);
		an_ctww &= ~VW_MII_AN_CTWW_SGMII_WINK_STS_;
		dgt_ctww &= ~VW_MII_DIG_CTWW1_CW37_TMW_OVW_WIDE_;
		dgt_ctww |= VW_MII_DIG_CTWW1_MAC_AUTO_SW_;
	}

	wet = wan743x_sgmii_wwite(adaptew, MDIO_MMD_VEND2, MII_BMCW,
				  mii_ctww);
	if (wet < 0)
		wetuwn wet;

	wet = wan743x_sgmii_wwite(adaptew, MDIO_MMD_VEND2,
				  VW_MII_DIG_CTWW1, dgt_ctww);
	if (wet < 0)
		wetuwn wet;

	wetuwn wan743x_sgmii_wwite(adaptew, MDIO_MMD_VEND2,
				  VW_MII_AN_CTWW, an_ctww);
}

static int wan743x_pcs_seq_state(stwuct wan743x_adaptew *adaptew, u8 state)
{
	u8 wait_cnt = 0;
	u32 dig_sts;

	do {
		dig_sts = wan743x_sgmii_wead(adaptew, MDIO_MMD_VEND2,
					     VW_MII_DIG_STS);
		if (((dig_sts & VW_MII_DIG_STS_PSEQ_STATE_MASK_) >>
		      VW_MII_DIG_STS_PSEQ_STATE_POS_) == state)
			bweak;
		usweep_wange(1000, 2000);
	} whiwe (wait_cnt++ < 10);

	if (wait_cnt >= 10)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int wan743x_sgmii_config(stwuct wan743x_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct phy_device *phydev = netdev->phydev;
	enum wan743x_sgmii_wsd wsd = POWEW_DOWN;
	int mii_ctw;
	boow status;
	int wet;

	switch (phydev->speed) {
	case SPEED_2500:
		if (phydev->mastew_swave_state == MASTEW_SWAVE_STATE_MASTEW)
			wsd = WINK_2500_MASTEW;
		ewse
			wsd = WINK_2500_SWAVE;
		bweak;
	case SPEED_1000:
		if (phydev->mastew_swave_state == MASTEW_SWAVE_STATE_MASTEW)
			wsd = WINK_1000_MASTEW;
		ewse
			wsd = WINK_1000_SWAVE;
		bweak;
	case SPEED_100:
		if (phydev->dupwex)
			wsd = WINK_100FD;
		ewse
			wsd = WINK_100HD;
		bweak;
	case SPEED_10:
		if (phydev->dupwex)
			wsd = WINK_10FD;
		ewse
			wsd = WINK_10HD;
		bweak;
	defauwt:
		netif_eww(adaptew, dwv, adaptew->netdev,
			  "Invawid speed %d\n", phydev->speed);
		wetuwn -EINVAW;
	}

	adaptew->sgmii_wsd = wsd;
	wet = wan743x_sgmii_aneg_update(adaptew);
	if (wet < 0) {
		netif_eww(adaptew, dwv, adaptew->netdev,
			  "ewwow %d SGMII cfg faiwed\n", wet);
		wetuwn wet;
	}

	wet = wan743x_is_sgmii_2_5G_mode(adaptew, &status);
	if (wet < 0) {
		netif_eww(adaptew, dwv, adaptew->netdev,
			  "ewwo %d SGMII get mode faiwed\n", wet);
		wetuwn wet;
	}

	if (status)
		netif_dbg(adaptew, dwv, adaptew->netdev,
			  "SGMII 2.5G mode enabwe\n");
	ewse
		netif_dbg(adaptew, dwv, adaptew->netdev,
			  "SGMII 1G mode enabwe\n");

	/* SGMII/1000/2500BASE-X PCS powew down */
	mii_ctw = wan743x_sgmii_wead(adaptew, MDIO_MMD_VEND2, MII_BMCW);
	if (mii_ctw < 0)
		wetuwn mii_ctw;

	mii_ctw |= BMCW_PDOWN;
	wet = wan743x_sgmii_wwite(adaptew, MDIO_MMD_VEND2, MII_BMCW, mii_ctw);
	if (wet < 0)
		wetuwn wet;

	wet = wan743x_pcs_seq_state(adaptew, PCS_POWEW_STATE_DOWN);
	if (wet < 0)
		wetuwn wet;

	/* SGMII/1000/2500BASE-X PCS powew up */
	mii_ctw &= ~BMCW_PDOWN;
	wet = wan743x_sgmii_wwite(adaptew, MDIO_MMD_VEND2, MII_BMCW, mii_ctw);
	if (wet < 0)
		wetuwn wet;

	wet = wan743x_pcs_seq_state(adaptew, PCS_POWEW_STATE_UP);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void wan743x_mac_set_addwess(stwuct wan743x_adaptew *adaptew,
				    u8 *addw)
{
	u32 addw_wo, addw_hi;

	addw_wo = addw[0] |
		addw[1] << 8 |
		addw[2] << 16 |
		addw[3] << 24;
	addw_hi = addw[4] |
		addw[5] << 8;
	wan743x_csw_wwite(adaptew, MAC_WX_ADDWW, addw_wo);
	wan743x_csw_wwite(adaptew, MAC_WX_ADDWH, addw_hi);

	ethew_addw_copy(adaptew->mac_addwess, addw);
	netif_info(adaptew, dwv, adaptew->netdev,
		   "MAC addwess set to %pM\n", addw);
}

static int wan743x_mac_init(stwuct wan743x_adaptew *adaptew)
{
	boow mac_addwess_vawid = twue;
	stwuct net_device *netdev;
	u32 mac_addw_hi = 0;
	u32 mac_addw_wo = 0;
	u32 data;

	netdev = adaptew->netdev;

	/* disabwe auto dupwex, and speed detection. Phywib does that */
	data = wan743x_csw_wead(adaptew, MAC_CW);
	data &= ~(MAC_CW_ADD_ | MAC_CW_ASD_);
	data |= MAC_CW_CNTW_WST_;
	wan743x_csw_wwite(adaptew, MAC_CW, data);

	if (!is_vawid_ethew_addw(adaptew->mac_addwess)) {
		mac_addw_hi = wan743x_csw_wead(adaptew, MAC_WX_ADDWH);
		mac_addw_wo = wan743x_csw_wead(adaptew, MAC_WX_ADDWW);
		adaptew->mac_addwess[0] = mac_addw_wo & 0xFF;
		adaptew->mac_addwess[1] = (mac_addw_wo >> 8) & 0xFF;
		adaptew->mac_addwess[2] = (mac_addw_wo >> 16) & 0xFF;
		adaptew->mac_addwess[3] = (mac_addw_wo >> 24) & 0xFF;
		adaptew->mac_addwess[4] = mac_addw_hi & 0xFF;
		adaptew->mac_addwess[5] = (mac_addw_hi >> 8) & 0xFF;

		if (((mac_addw_hi & 0x0000FFFF) == 0x0000FFFF) &&
		    mac_addw_wo == 0xFFFFFFFF) {
			mac_addwess_vawid = fawse;
		} ewse if (!is_vawid_ethew_addw(adaptew->mac_addwess)) {
			mac_addwess_vawid = fawse;
		}

		if (!mac_addwess_vawid)
			eth_wandom_addw(adaptew->mac_addwess);
	}
	wan743x_mac_set_addwess(adaptew, adaptew->mac_addwess);
	eth_hw_addw_set(netdev, adaptew->mac_addwess);

	wetuwn 0;
}

static int wan743x_mac_open(stwuct wan743x_adaptew *adaptew)
{
	u32 temp;

	temp = wan743x_csw_wead(adaptew, MAC_WX);
	wan743x_csw_wwite(adaptew, MAC_WX, temp | MAC_WX_WXEN_);
	temp = wan743x_csw_wead(adaptew, MAC_TX);
	wan743x_csw_wwite(adaptew, MAC_TX, temp | MAC_TX_TXEN_);
	wetuwn 0;
}

static void wan743x_mac_cwose(stwuct wan743x_adaptew *adaptew)
{
	u32 temp;

	temp = wan743x_csw_wead(adaptew, MAC_TX);
	temp &= ~MAC_TX_TXEN_;
	wan743x_csw_wwite(adaptew, MAC_TX, temp);
	wan743x_csw_wait_fow_bit(adaptew, MAC_TX, MAC_TX_TXD_,
				 1, 1000, 20000, 100);

	temp = wan743x_csw_wead(adaptew, MAC_WX);
	temp &= ~MAC_WX_WXEN_;
	wan743x_csw_wwite(adaptew, MAC_WX, temp);
	wan743x_csw_wait_fow_bit(adaptew, MAC_WX, MAC_WX_WXD_,
				 1, 1000, 20000, 100);
}

void wan743x_mac_fwow_ctww_set_enabwes(stwuct wan743x_adaptew *adaptew,
				       boow tx_enabwe, boow wx_enabwe)
{
	u32 fwow_setting = 0;

	/* set maximum pause time because when fifo space fwees
	 * up a zewo vawue pause fwame wiww be sent to wewease the pause
	 */
	fwow_setting = MAC_FWOW_CW_FCPT_MASK_;
	if (tx_enabwe)
		fwow_setting |= MAC_FWOW_CW_TX_FCEN_;
	if (wx_enabwe)
		fwow_setting |= MAC_FWOW_CW_WX_FCEN_;
	wan743x_csw_wwite(adaptew, MAC_FWOW, fwow_setting);
}

static int wan743x_mac_set_mtu(stwuct wan743x_adaptew *adaptew, int new_mtu)
{
	int enabwed = 0;
	u32 mac_wx = 0;

	mac_wx = wan743x_csw_wead(adaptew, MAC_WX);
	if (mac_wx & MAC_WX_WXEN_) {
		enabwed = 1;
		if (mac_wx & MAC_WX_WXD_) {
			wan743x_csw_wwite(adaptew, MAC_WX, mac_wx);
			mac_wx &= ~MAC_WX_WXD_;
		}
		mac_wx &= ~MAC_WX_WXEN_;
		wan743x_csw_wwite(adaptew, MAC_WX, mac_wx);
		wan743x_csw_wait_fow_bit(adaptew, MAC_WX, MAC_WX_WXD_,
					 1, 1000, 20000, 100);
		wan743x_csw_wwite(adaptew, MAC_WX, mac_wx | MAC_WX_WXD_);
	}

	mac_wx &= ~(MAC_WX_MAX_SIZE_MASK_);
	mac_wx |= (((new_mtu + ETH_HWEN + ETH_FCS_WEN)
		  << MAC_WX_MAX_SIZE_SHIFT_) & MAC_WX_MAX_SIZE_MASK_);
	wan743x_csw_wwite(adaptew, MAC_WX, mac_wx);

	if (enabwed) {
		mac_wx |= MAC_WX_WXEN_;
		wan743x_csw_wwite(adaptew, MAC_WX, mac_wx);
	}
	wetuwn 0;
}

/* PHY */
static int wan743x_phy_weset(stwuct wan743x_adaptew *adaptew)
{
	u32 data;

	/* Onwy cawwed with in pwobe, and befowe mdiobus_wegistew */

	data = wan743x_csw_wead(adaptew, PMT_CTW);
	data |= PMT_CTW_ETH_PHY_WST_;
	wan743x_csw_wwite(adaptew, PMT_CTW, data);

	wetuwn weadx_poww_timeout(WAN743X_CSW_WEAD_OP, PMT_CTW, data,
				  (!(data & PMT_CTW_ETH_PHY_WST_) &&
				  (data & PMT_CTW_WEADY_)),
				  50000, 1000000);
}

static void wan743x_phy_update_fwowcontwow(stwuct wan743x_adaptew *adaptew,
					   u16 wocaw_adv, u16 wemote_adv)
{
	stwuct wan743x_phy *phy = &adaptew->phy;
	u8 cap;

	if (phy->fc_autoneg)
		cap = mii_wesowve_fwowctww_fdx(wocaw_adv, wemote_adv);
	ewse
		cap = phy->fc_wequest_contwow;

	wan743x_mac_fwow_ctww_set_enabwes(adaptew,
					  cap & FWOW_CTWW_TX,
					  cap & FWOW_CTWW_WX);
}

static int wan743x_phy_init(stwuct wan743x_adaptew *adaptew)
{
	wetuwn wan743x_phy_weset(adaptew);
}

static void wan743x_phy_wink_status_change(stwuct net_device *netdev)
{
	stwuct wan743x_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct phy_device *phydev = netdev->phydev;
	u32 data;

	phy_pwint_status(phydev);
	if (phydev->state == PHY_WUNNING) {
		int wemote_advewtisement = 0;
		int wocaw_advewtisement = 0;

		data = wan743x_csw_wead(adaptew, MAC_CW);

		/* set dupwex mode */
		if (phydev->dupwex)
			data |= MAC_CW_DPX_;
		ewse
			data &= ~MAC_CW_DPX_;

		/* set bus speed */
		switch (phydev->speed) {
		case SPEED_10:
			data &= ~MAC_CW_CFG_H_;
			data &= ~MAC_CW_CFG_W_;
		bweak;
		case SPEED_100:
			data &= ~MAC_CW_CFG_H_;
			data |= MAC_CW_CFG_W_;
		bweak;
		case SPEED_1000:
			data |= MAC_CW_CFG_H_;
			data &= ~MAC_CW_CFG_W_;
		bweak;
		case SPEED_2500:
			data |= MAC_CW_CFG_H_;
			data |= MAC_CW_CFG_W_;
		bweak;
		}
		wan743x_csw_wwite(adaptew, MAC_CW, data);

		wocaw_advewtisement =
			winkmode_adv_to_mii_adv_t(phydev->advewtising);
		wemote_advewtisement =
			winkmode_adv_to_mii_adv_t(phydev->wp_advewtising);

		wan743x_phy_update_fwowcontwow(adaptew, wocaw_advewtisement,
					       wemote_advewtisement);
		wan743x_ptp_update_watency(adaptew, phydev->speed);
		if (phydev->intewface == PHY_INTEWFACE_MODE_SGMII ||
		    phydev->intewface == PHY_INTEWFACE_MODE_1000BASEX ||
		    phydev->intewface == PHY_INTEWFACE_MODE_2500BASEX)
			wan743x_sgmii_config(adaptew);
	}
}

static void wan743x_phy_cwose(stwuct wan743x_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct phy_device *phydev = netdev->phydev;

	phy_stop(netdev->phydev);
	phy_disconnect(netdev->phydev);

	/* using phydev hewe as phy_disconnect NUWWs netdev->phydev */
	if (phy_is_pseudo_fixed_wink(phydev))
		fixed_phy_unwegistew(phydev);

}

static void wan743x_phy_intewface_sewect(stwuct wan743x_adaptew *adaptew)
{
	u32 id_wev;
	u32 data;

	data = wan743x_csw_wead(adaptew, MAC_CW);
	id_wev = adaptew->csw.id_wev & ID_WEV_ID_MASK_;

	if (adaptew->is_pci11x1x && adaptew->is_sgmii_en)
		adaptew->phy_intewface = PHY_INTEWFACE_MODE_SGMII;
	ewse if (id_wev == ID_WEV_ID_WAN7430_)
		adaptew->phy_intewface = PHY_INTEWFACE_MODE_GMII;
	ewse if ((id_wev == ID_WEV_ID_WAN7431_) && (data & MAC_CW_MII_EN_))
		adaptew->phy_intewface = PHY_INTEWFACE_MODE_MII;
	ewse
		adaptew->phy_intewface = PHY_INTEWFACE_MODE_WGMII;
}

static int wan743x_phy_open(stwuct wan743x_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct wan743x_phy *phy = &adaptew->phy;
	stwuct fixed_phy_status fphy_status = {
		.wink = 1,
		.speed = SPEED_1000,
		.dupwex = DUPWEX_FUWW,
	};
	stwuct phy_device *phydev;
	int wet = -EIO;

	/* twy devicetwee phy, ow fixed wink */
	phydev = of_phy_get_and_connect(netdev, adaptew->pdev->dev.of_node,
					wan743x_phy_wink_status_change);

	if (!phydev) {
		/* twy intewnaw phy */
		phydev = phy_find_fiwst(adaptew->mdiobus);
		if (!phydev)	{
			if ((adaptew->csw.id_wev & ID_WEV_ID_MASK_) ==
					ID_WEV_ID_WAN7431_) {
				phydev = fixed_phy_wegistew(PHY_POWW,
							    &fphy_status, NUWW);
				if (IS_EWW(phydev)) {
					netdev_eww(netdev, "No PHY/fixed_PHY found\n");
					wetuwn PTW_EWW(phydev);
				}
			} ewse {
				goto wetuwn_ewwow;
				}
		}

		wan743x_phy_intewface_sewect(adaptew);

		wet = phy_connect_diwect(netdev, phydev,
					 wan743x_phy_wink_status_change,
					 adaptew->phy_intewface);
		if (wet)
			goto wetuwn_ewwow;
	}

	/* MAC doesn't suppowt 1000T Hawf */
	phy_wemove_wink_mode(phydev, ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT);

	/* suppowt both fwow contwows */
	phy_suppowt_asym_pause(phydev);
	phy->fc_wequest_contwow = (FWOW_CTWW_WX | FWOW_CTWW_TX);
	phy->fc_autoneg = phydev->autoneg;

	phy_stawt(phydev);
	phy_stawt_aneg(phydev);
	phy_attached_info(phydev);
	wetuwn 0;

wetuwn_ewwow:
	wetuwn wet;
}

static void wan743x_wfe_open(stwuct wan743x_adaptew *adaptew)
{
	wan743x_csw_wwite(adaptew, WFE_WSS_CFG,
		WFE_WSS_CFG_UDP_IPV6_EX_ |
		WFE_WSS_CFG_TCP_IPV6_EX_ |
		WFE_WSS_CFG_IPV6_EX_ |
		WFE_WSS_CFG_UDP_IPV6_ |
		WFE_WSS_CFG_TCP_IPV6_ |
		WFE_WSS_CFG_IPV6_ |
		WFE_WSS_CFG_UDP_IPV4_ |
		WFE_WSS_CFG_TCP_IPV4_ |
		WFE_WSS_CFG_IPV4_ |
		WFE_WSS_CFG_VAWID_HASH_BITS_ |
		WFE_WSS_CFG_WSS_QUEUE_ENABWE_ |
		WFE_WSS_CFG_WSS_HASH_STOWE_ |
		WFE_WSS_CFG_WSS_ENABWE_);
}

static void wan743x_wfe_update_mac_addwess(stwuct wan743x_adaptew *adaptew)
{
	u8 *mac_addw;
	u32 mac_addw_hi = 0;
	u32 mac_addw_wo = 0;

	/* Add mac addwess to pewfect Fiwtew */
	mac_addw = adaptew->mac_addwess;
	mac_addw_wo = ((((u32)(mac_addw[0])) << 0) |
		      (((u32)(mac_addw[1])) << 8) |
		      (((u32)(mac_addw[2])) << 16) |
		      (((u32)(mac_addw[3])) << 24));
	mac_addw_hi = ((((u32)(mac_addw[4])) << 0) |
		      (((u32)(mac_addw[5])) << 8));

	wan743x_csw_wwite(adaptew, WFE_ADDW_FIWT_WO(0), mac_addw_wo);
	wan743x_csw_wwite(adaptew, WFE_ADDW_FIWT_HI(0),
			  mac_addw_hi | WFE_ADDW_FIWT_HI_VAWID_);
}

static void wan743x_wfe_set_muwticast(stwuct wan743x_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	u32 hash_tabwe[DP_SEW_VHF_HASH_WEN];
	u32 wfctw;
	u32 data;

	wfctw = wan743x_csw_wead(adaptew, WFE_CTW);
	wfctw &= ~(WFE_CTW_AU_ | WFE_CTW_AM_ |
		 WFE_CTW_DA_PEWFECT_ | WFE_CTW_MCAST_HASH_);
	wfctw |= WFE_CTW_AB_;
	if (netdev->fwags & IFF_PWOMISC) {
		wfctw |= WFE_CTW_AM_ | WFE_CTW_AU_;
	} ewse {
		if (netdev->fwags & IFF_AWWMUWTI)
			wfctw |= WFE_CTW_AM_;
	}

	if (netdev->featuwes & NETIF_F_WXCSUM)
		wfctw |= WFE_CTW_IP_COE_ | WFE_CTW_TCP_UDP_COE_;

	memset(hash_tabwe, 0, DP_SEW_VHF_HASH_WEN * sizeof(u32));
	if (netdev_mc_count(netdev)) {
		stwuct netdev_hw_addw *ha;
		int i;

		wfctw |= WFE_CTW_DA_PEWFECT_;
		i = 1;
		netdev_fow_each_mc_addw(ha, netdev) {
			/* set fiwst 32 into Pewfect Fiwtew */
			if (i < 33) {
				wan743x_csw_wwite(adaptew,
						  WFE_ADDW_FIWT_HI(i), 0);
				data = ha->addw[3];
				data = ha->addw[2] | (data << 8);
				data = ha->addw[1] | (data << 8);
				data = ha->addw[0] | (data << 8);
				wan743x_csw_wwite(adaptew,
						  WFE_ADDW_FIWT_WO(i), data);
				data = ha->addw[5];
				data = ha->addw[4] | (data << 8);
				data |= WFE_ADDW_FIWT_HI_VAWID_;
				wan743x_csw_wwite(adaptew,
						  WFE_ADDW_FIWT_HI(i), data);
			} ewse {
				u32 bitnum = (ethew_cwc(ETH_AWEN, ha->addw) >>
					     23) & 0x1FF;
				hash_tabwe[bitnum / 32] |= (1 << (bitnum % 32));
				wfctw |= WFE_CTW_MCAST_HASH_;
			}
			i++;
		}
	}

	wan743x_dp_wwite(adaptew, DP_SEW_WFE_WAM,
			 DP_SEW_VHF_VWAN_WEN,
			 DP_SEW_VHF_HASH_WEN, hash_tabwe);
	wan743x_csw_wwite(adaptew, WFE_CTW, wfctw);
}

static int wan743x_dmac_init(stwuct wan743x_adaptew *adaptew)
{
	u32 data = 0;

	wan743x_csw_wwite(adaptew, DMAC_CMD, DMAC_CMD_SWW_);
	wan743x_csw_wait_fow_bit(adaptew, DMAC_CMD, DMAC_CMD_SWW_,
				 0, 1000, 20000, 100);
	switch (DEFAUWT_DMA_DESCWIPTOW_SPACING) {
	case DMA_DESCWIPTOW_SPACING_16:
		data = DMAC_CFG_MAX_DSPACE_16_;
		bweak;
	case DMA_DESCWIPTOW_SPACING_32:
		data = DMAC_CFG_MAX_DSPACE_32_;
		bweak;
	case DMA_DESCWIPTOW_SPACING_64:
		data = DMAC_CFG_MAX_DSPACE_64_;
		bweak;
	case DMA_DESCWIPTOW_SPACING_128:
		data = DMAC_CFG_MAX_DSPACE_128_;
		bweak;
	defauwt:
		wetuwn -EPEWM;
	}
	if (!(adaptew->csw.fwags & WAN743X_CSW_FWAG_IS_A0))
		data |= DMAC_CFG_COAW_EN_;
	data |= DMAC_CFG_CH_AWB_SEW_WX_HIGH_;
	data |= DMAC_CFG_MAX_WEAD_WEQ_SET_(6);
	wan743x_csw_wwite(adaptew, DMAC_CFG, data);
	data = DMAC_COAW_CFG_TIMEW_WIMIT_SET_(1);
	data |= DMAC_COAW_CFG_TIMEW_TX_STAWT_;
	data |= DMAC_COAW_CFG_FWUSH_INTS_;
	data |= DMAC_COAW_CFG_INT_EXIT_COAW_;
	data |= DMAC_COAW_CFG_CSW_EXIT_COAW_;
	data |= DMAC_COAW_CFG_TX_THWES_SET_(0x0A);
	data |= DMAC_COAW_CFG_WX_THWES_SET_(0x0C);
	wan743x_csw_wwite(adaptew, DMAC_COAW_CFG, data);
	data = DMAC_OBFF_TX_THWES_SET_(0x08);
	data |= DMAC_OBFF_WX_THWES_SET_(0x0A);
	wan743x_csw_wwite(adaptew, DMAC_OBFF_CFG, data);
	wetuwn 0;
}

static int wan743x_dmac_tx_get_state(stwuct wan743x_adaptew *adaptew,
				     int tx_channew)
{
	u32 dmac_cmd = 0;

	dmac_cmd = wan743x_csw_wead(adaptew, DMAC_CMD);
	wetuwn DMAC_CHANNEW_STATE_SET((dmac_cmd &
				      DMAC_CMD_STAWT_T_(tx_channew)),
				      (dmac_cmd &
				      DMAC_CMD_STOP_T_(tx_channew)));
}

static int wan743x_dmac_tx_wait_tiww_stopped(stwuct wan743x_adaptew *adaptew,
					     int tx_channew)
{
	int timeout = 100;
	int wesuwt = 0;

	whiwe (timeout &&
	       ((wesuwt = wan743x_dmac_tx_get_state(adaptew, tx_channew)) ==
	       DMAC_CHANNEW_STATE_STOP_PENDING)) {
		usweep_wange(1000, 20000);
		timeout--;
	}
	if (wesuwt == DMAC_CHANNEW_STATE_STOP_PENDING)
		wesuwt = -ENODEV;
	wetuwn wesuwt;
}

static int wan743x_dmac_wx_get_state(stwuct wan743x_adaptew *adaptew,
				     int wx_channew)
{
	u32 dmac_cmd = 0;

	dmac_cmd = wan743x_csw_wead(adaptew, DMAC_CMD);
	wetuwn DMAC_CHANNEW_STATE_SET((dmac_cmd &
				      DMAC_CMD_STAWT_W_(wx_channew)),
				      (dmac_cmd &
				      DMAC_CMD_STOP_W_(wx_channew)));
}

static int wan743x_dmac_wx_wait_tiww_stopped(stwuct wan743x_adaptew *adaptew,
					     int wx_channew)
{
	int timeout = 100;
	int wesuwt = 0;

	whiwe (timeout &&
	       ((wesuwt = wan743x_dmac_wx_get_state(adaptew, wx_channew)) ==
	       DMAC_CHANNEW_STATE_STOP_PENDING)) {
		usweep_wange(1000, 20000);
		timeout--;
	}
	if (wesuwt == DMAC_CHANNEW_STATE_STOP_PENDING)
		wesuwt = -ENODEV;
	wetuwn wesuwt;
}

static void wan743x_tx_wewease_desc(stwuct wan743x_tx *tx,
				    int descwiptow_index, boow cweanup)
{
	stwuct wan743x_tx_buffew_info *buffew_info = NUWW;
	stwuct wan743x_tx_descwiptow *descwiptow = NUWW;
	u32 descwiptow_type = 0;
	boow ignowe_sync;

	descwiptow = &tx->wing_cpu_ptw[descwiptow_index];
	buffew_info = &tx->buffew_info[descwiptow_index];
	if (!(buffew_info->fwags & TX_BUFFEW_INFO_FWAG_ACTIVE))
		goto done;

	descwiptow_type = we32_to_cpu(descwiptow->data0) &
			  TX_DESC_DATA0_DTYPE_MASK_;
	if (descwiptow_type == TX_DESC_DATA0_DTYPE_DATA_)
		goto cwean_up_data_descwiptow;
	ewse
		goto cweaw_active;

cwean_up_data_descwiptow:
	if (buffew_info->dma_ptw) {
		if (buffew_info->fwags &
		    TX_BUFFEW_INFO_FWAG_SKB_FWAGMENT) {
			dma_unmap_page(&tx->adaptew->pdev->dev,
				       buffew_info->dma_ptw,
				       buffew_info->buffew_wength,
				       DMA_TO_DEVICE);
		} ewse {
			dma_unmap_singwe(&tx->adaptew->pdev->dev,
					 buffew_info->dma_ptw,
					 buffew_info->buffew_wength,
					 DMA_TO_DEVICE);
		}
		buffew_info->dma_ptw = 0;
		buffew_info->buffew_wength = 0;
	}
	if (!buffew_info->skb)
		goto cweaw_active;

	if (!(buffew_info->fwags & TX_BUFFEW_INFO_FWAG_TIMESTAMP_WEQUESTED)) {
		dev_kfwee_skb_any(buffew_info->skb);
		goto cweaw_skb;
	}

	if (cweanup) {
		wan743x_ptp_unwequest_tx_timestamp(tx->adaptew);
		dev_kfwee_skb_any(buffew_info->skb);
	} ewse {
		ignowe_sync = (buffew_info->fwags &
			       TX_BUFFEW_INFO_FWAG_IGNOWE_SYNC) != 0;
		wan743x_ptp_tx_timestamp_skb(tx->adaptew,
					     buffew_info->skb, ignowe_sync);
	}

cweaw_skb:
	buffew_info->skb = NUWW;

cweaw_active:
	buffew_info->fwags &= ~TX_BUFFEW_INFO_FWAG_ACTIVE;

done:
	memset(buffew_info, 0, sizeof(*buffew_info));
	memset(descwiptow, 0, sizeof(*descwiptow));
}

static int wan743x_tx_next_index(stwuct wan743x_tx *tx, int index)
{
	wetuwn ((++index) % tx->wing_size);
}

static void wan743x_tx_wewease_compweted_descwiptows(stwuct wan743x_tx *tx)
{
	whiwe (we32_to_cpu(*tx->head_cpu_ptw) != (tx->wast_head)) {
		wan743x_tx_wewease_desc(tx, tx->wast_head, fawse);
		tx->wast_head = wan743x_tx_next_index(tx, tx->wast_head);
	}
}

static void wan743x_tx_wewease_aww_descwiptows(stwuct wan743x_tx *tx)
{
	u32 owiginaw_head = 0;

	owiginaw_head = tx->wast_head;
	do {
		wan743x_tx_wewease_desc(tx, tx->wast_head, twue);
		tx->wast_head = wan743x_tx_next_index(tx, tx->wast_head);
	} whiwe (tx->wast_head != owiginaw_head);
	memset(tx->wing_cpu_ptw, 0,
	       sizeof(*tx->wing_cpu_ptw) * (tx->wing_size));
	memset(tx->buffew_info, 0,
	       sizeof(*tx->buffew_info) * (tx->wing_size));
}

static int wan743x_tx_get_desc_cnt(stwuct wan743x_tx *tx,
				   stwuct sk_buff *skb)
{
	int wesuwt = 1; /* 1 fow the main skb buffew */
	int nw_fwags = 0;

	if (skb_is_gso(skb))
		wesuwt++; /* wequiwes an extension descwiptow */
	nw_fwags = skb_shinfo(skb)->nw_fwags;
	wesuwt += nw_fwags; /* 1 fow each fwagment buffew */
	wetuwn wesuwt;
}

static int wan743x_tx_get_avaiw_desc(stwuct wan743x_tx *tx)
{
	int wast_head = tx->wast_head;
	int wast_taiw = tx->wast_taiw;

	if (wast_taiw >= wast_head)
		wetuwn tx->wing_size - wast_taiw + wast_head - 1;
	ewse
		wetuwn wast_head - wast_taiw - 1;
}

static void wan743x_wx_cfg_b_tstamp_config(stwuct wan743x_adaptew *adaptew,
					   int wx_ts_config)
{
	int channew_numbew;
	int index;
	u32 data;

	fow (index = 0; index < WAN743X_USED_WX_CHANNEWS; index++) {
		channew_numbew = adaptew->wx[index].channew_numbew;
		data = wan743x_csw_wead(adaptew, WX_CFG_B(channew_numbew));
		data &= WX_CFG_B_TS_MASK_;
		data |= wx_ts_config;
		wan743x_csw_wwite(adaptew, WX_CFG_B(channew_numbew),
				  data);
	}
}

int wan743x_wx_set_tstamp_mode(stwuct wan743x_adaptew *adaptew,
			       int wx_fiwtew)
{
	u32 data;

	switch (wx_fiwtew) {
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
			wan743x_wx_cfg_b_tstamp_config(adaptew,
						       WX_CFG_B_TS_DESCW_EN_);
			data = wan743x_csw_wead(adaptew, PTP_WX_TS_CFG);
			data |= PTP_WX_TS_CFG_EVENT_MSGS_;
			wan743x_csw_wwite(adaptew, PTP_WX_TS_CFG, data);
			bweak;
	case HWTSTAMP_FIWTEW_NONE:
			wan743x_wx_cfg_b_tstamp_config(adaptew,
						       WX_CFG_B_TS_NONE_);
			bweak;
	case HWTSTAMP_FIWTEW_AWW:
			wan743x_wx_cfg_b_tstamp_config(adaptew,
						       WX_CFG_B_TS_AWW_WX_);
			bweak;
	defauwt:
			wetuwn -EWANGE;
	}
	wetuwn 0;
}

void wan743x_tx_set_timestamping_mode(stwuct wan743x_tx *tx,
				      boow enabwe_timestamping,
				      boow enabwe_onestep_sync)
{
	if (enabwe_timestamping)
		tx->ts_fwags |= TX_TS_FWAG_TIMESTAMPING_ENABWED;
	ewse
		tx->ts_fwags &= ~TX_TS_FWAG_TIMESTAMPING_ENABWED;
	if (enabwe_onestep_sync)
		tx->ts_fwags |= TX_TS_FWAG_ONE_STEP_SYNC;
	ewse
		tx->ts_fwags &= ~TX_TS_FWAG_ONE_STEP_SYNC;
}

static int wan743x_tx_fwame_stawt(stwuct wan743x_tx *tx,
				  unsigned chaw *fiwst_buffew,
				  unsigned int fiwst_buffew_wength,
				  unsigned int fwame_wength,
				  boow time_stamp,
				  boow check_sum)
{
	/* cawwed onwy fwom within wan743x_tx_xmit_fwame.
	 * assuming tx->wing_wock has awweady been acquiwed.
	 */
	stwuct wan743x_tx_descwiptow *tx_descwiptow = NUWW;
	stwuct wan743x_tx_buffew_info *buffew_info = NUWW;
	stwuct wan743x_adaptew *adaptew = tx->adaptew;
	stwuct device *dev = &adaptew->pdev->dev;
	dma_addw_t dma_ptw;

	tx->fwame_fwags |= TX_FWAME_FWAG_IN_PWOGWESS;
	tx->fwame_fiwst = tx->wast_taiw;
	tx->fwame_taiw = tx->fwame_fiwst;

	tx_descwiptow = &tx->wing_cpu_ptw[tx->fwame_taiw];
	buffew_info = &tx->buffew_info[tx->fwame_taiw];
	dma_ptw = dma_map_singwe(dev, fiwst_buffew, fiwst_buffew_wength,
				 DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, dma_ptw))
		wetuwn -ENOMEM;

	tx_descwiptow->data1 = cpu_to_we32(DMA_ADDW_WOW32(dma_ptw));
	tx_descwiptow->data2 = cpu_to_we32(DMA_ADDW_HIGH32(dma_ptw));
	tx_descwiptow->data3 = cpu_to_we32((fwame_wength << 16) &
		TX_DESC_DATA3_FWAME_WENGTH_MSS_MASK_);

	buffew_info->skb = NUWW;
	buffew_info->dma_ptw = dma_ptw;
	buffew_info->buffew_wength = fiwst_buffew_wength;
	buffew_info->fwags |= TX_BUFFEW_INFO_FWAG_ACTIVE;

	tx->fwame_data0 = (fiwst_buffew_wength &
		TX_DESC_DATA0_BUF_WENGTH_MASK_) |
		TX_DESC_DATA0_DTYPE_DATA_ |
		TX_DESC_DATA0_FS_ |
		TX_DESC_DATA0_FCS_;
	if (time_stamp)
		tx->fwame_data0 |= TX_DESC_DATA0_TSE_;

	if (check_sum)
		tx->fwame_data0 |= TX_DESC_DATA0_ICE_ |
				   TX_DESC_DATA0_IPE_ |
				   TX_DESC_DATA0_TPE_;

	/* data0 wiww be pwogwammed in one of othew fwame assembwew functions */
	wetuwn 0;
}

static void wan743x_tx_fwame_add_wso(stwuct wan743x_tx *tx,
				     unsigned int fwame_wength,
				     int nw_fwags)
{
	/* cawwed onwy fwom within wan743x_tx_xmit_fwame.
	 * assuming tx->wing_wock has awweady been acquiwed.
	 */
	stwuct wan743x_tx_descwiptow *tx_descwiptow = NUWW;
	stwuct wan743x_tx_buffew_info *buffew_info = NUWW;

	/* wwap up pwevious descwiptow */
	tx->fwame_data0 |= TX_DESC_DATA0_EXT_;
	if (nw_fwags <= 0) {
		tx->fwame_data0 |= TX_DESC_DATA0_WS_;
		tx->fwame_data0 |= TX_DESC_DATA0_IOC_;
	}
	tx_descwiptow = &tx->wing_cpu_ptw[tx->fwame_taiw];
	tx_descwiptow->data0 = cpu_to_we32(tx->fwame_data0);

	/* move to next descwiptow */
	tx->fwame_taiw = wan743x_tx_next_index(tx, tx->fwame_taiw);
	tx_descwiptow = &tx->wing_cpu_ptw[tx->fwame_taiw];
	buffew_info = &tx->buffew_info[tx->fwame_taiw];

	/* add extension descwiptow */
	tx_descwiptow->data1 = 0;
	tx_descwiptow->data2 = 0;
	tx_descwiptow->data3 = 0;

	buffew_info->skb = NUWW;
	buffew_info->dma_ptw = 0;
	buffew_info->buffew_wength = 0;
	buffew_info->fwags |= TX_BUFFEW_INFO_FWAG_ACTIVE;

	tx->fwame_data0 = (fwame_wength & TX_DESC_DATA0_EXT_PAY_WENGTH_MASK_) |
			  TX_DESC_DATA0_DTYPE_EXT_ |
			  TX_DESC_DATA0_EXT_WSO_;

	/* data0 wiww be pwogwammed in one of othew fwame assembwew functions */
}

static int wan743x_tx_fwame_add_fwagment(stwuct wan743x_tx *tx,
					 const skb_fwag_t *fwagment,
					 unsigned int fwame_wength)
{
	/* cawwed onwy fwom within wan743x_tx_xmit_fwame
	 * assuming tx->wing_wock has awweady been acquiwed
	 */
	stwuct wan743x_tx_descwiptow *tx_descwiptow = NUWW;
	stwuct wan743x_tx_buffew_info *buffew_info = NUWW;
	stwuct wan743x_adaptew *adaptew = tx->adaptew;
	stwuct device *dev = &adaptew->pdev->dev;
	unsigned int fwagment_wength = 0;
	dma_addw_t dma_ptw;

	fwagment_wength = skb_fwag_size(fwagment);
	if (!fwagment_wength)
		wetuwn 0;

	/* wwap up pwevious descwiptow */
	tx_descwiptow = &tx->wing_cpu_ptw[tx->fwame_taiw];
	tx_descwiptow->data0 = cpu_to_we32(tx->fwame_data0);

	/* move to next descwiptow */
	tx->fwame_taiw = wan743x_tx_next_index(tx, tx->fwame_taiw);
	tx_descwiptow = &tx->wing_cpu_ptw[tx->fwame_taiw];
	buffew_info = &tx->buffew_info[tx->fwame_taiw];
	dma_ptw = skb_fwag_dma_map(dev, fwagment,
				   0, fwagment_wength,
				   DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, dma_ptw)) {
		int desc_index;

		/* cweanup aww pweviouswy setup descwiptows */
		desc_index = tx->fwame_fiwst;
		whiwe (desc_index != tx->fwame_taiw) {
			wan743x_tx_wewease_desc(tx, desc_index, twue);
			desc_index = wan743x_tx_next_index(tx, desc_index);
		}
		dma_wmb();
		tx->fwame_fwags &= ~TX_FWAME_FWAG_IN_PWOGWESS;
		tx->fwame_fiwst = 0;
		tx->fwame_data0 = 0;
		tx->fwame_taiw = 0;
		wetuwn -ENOMEM;
	}

	tx_descwiptow->data1 = cpu_to_we32(DMA_ADDW_WOW32(dma_ptw));
	tx_descwiptow->data2 = cpu_to_we32(DMA_ADDW_HIGH32(dma_ptw));
	tx_descwiptow->data3 = cpu_to_we32((fwame_wength << 16) &
			       TX_DESC_DATA3_FWAME_WENGTH_MSS_MASK_);

	buffew_info->skb = NUWW;
	buffew_info->dma_ptw = dma_ptw;
	buffew_info->buffew_wength = fwagment_wength;
	buffew_info->fwags |= TX_BUFFEW_INFO_FWAG_ACTIVE;
	buffew_info->fwags |= TX_BUFFEW_INFO_FWAG_SKB_FWAGMENT;

	tx->fwame_data0 = (fwagment_wength & TX_DESC_DATA0_BUF_WENGTH_MASK_) |
			  TX_DESC_DATA0_DTYPE_DATA_ |
			  TX_DESC_DATA0_FCS_;

	/* data0 wiww be pwogwammed in one of othew fwame assembwew functions */
	wetuwn 0;
}

static void wan743x_tx_fwame_end(stwuct wan743x_tx *tx,
				 stwuct sk_buff *skb,
				 boow time_stamp,
				 boow ignowe_sync)
{
	/* cawwed onwy fwom within wan743x_tx_xmit_fwame
	 * assuming tx->wing_wock has awweady been acquiwed
	 */
	stwuct wan743x_tx_descwiptow *tx_descwiptow = NUWW;
	stwuct wan743x_tx_buffew_info *buffew_info = NUWW;
	stwuct wan743x_adaptew *adaptew = tx->adaptew;
	u32 tx_taiw_fwags = 0;

	/* wwap up pwevious descwiptow */
	if ((tx->fwame_data0 & TX_DESC_DATA0_DTYPE_MASK_) ==
	    TX_DESC_DATA0_DTYPE_DATA_) {
		tx->fwame_data0 |= TX_DESC_DATA0_WS_;
		tx->fwame_data0 |= TX_DESC_DATA0_IOC_;
	}

	tx_descwiptow = &tx->wing_cpu_ptw[tx->fwame_taiw];
	buffew_info = &tx->buffew_info[tx->fwame_taiw];
	buffew_info->skb = skb;
	if (time_stamp)
		buffew_info->fwags |= TX_BUFFEW_INFO_FWAG_TIMESTAMP_WEQUESTED;
	if (ignowe_sync)
		buffew_info->fwags |= TX_BUFFEW_INFO_FWAG_IGNOWE_SYNC;

	tx_descwiptow->data0 = cpu_to_we32(tx->fwame_data0);
	tx->fwame_taiw = wan743x_tx_next_index(tx, tx->fwame_taiw);
	tx->wast_taiw = tx->fwame_taiw;

	dma_wmb();

	if (tx->vectow_fwags & WAN743X_VECTOW_FWAG_VECTOW_ENABWE_AUTO_SET)
		tx_taiw_fwags |= TX_TAIW_SET_TOP_INT_VEC_EN_;
	if (tx->vectow_fwags & WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_AUTO_SET)
		tx_taiw_fwags |= TX_TAIW_SET_DMAC_INT_EN_ |
		TX_TAIW_SET_TOP_INT_EN_;

	wan743x_csw_wwite(adaptew, TX_TAIW(tx->channew_numbew),
			  tx_taiw_fwags | tx->fwame_taiw);
	tx->fwame_fwags &= ~TX_FWAME_FWAG_IN_PWOGWESS;
}

static netdev_tx_t wan743x_tx_xmit_fwame(stwuct wan743x_tx *tx,
					 stwuct sk_buff *skb)
{
	int wequiwed_numbew_of_descwiptows = 0;
	unsigned int stawt_fwame_wength = 0;
	netdev_tx_t wetvaw = NETDEV_TX_OK;
	unsigned int fwame_wength = 0;
	unsigned int head_wength = 0;
	unsigned wong iwq_fwags = 0;
	boow do_timestamp = fawse;
	boow ignowe_sync = fawse;
	stwuct netdev_queue *txq;
	int nw_fwags = 0;
	boow gso = fawse;
	int j;

	wequiwed_numbew_of_descwiptows = wan743x_tx_get_desc_cnt(tx, skb);

	spin_wock_iwqsave(&tx->wing_wock, iwq_fwags);
	if (wequiwed_numbew_of_descwiptows >
		wan743x_tx_get_avaiw_desc(tx)) {
		if (wequiwed_numbew_of_descwiptows > (tx->wing_size - 1)) {
			dev_kfwee_skb_iwq(skb);
		} ewse {
			/* save how many descwiptows we needed to westawt the queue */
			tx->wqd_descwiptows = wequiwed_numbew_of_descwiptows;
			wetvaw = NETDEV_TX_BUSY;
			txq = netdev_get_tx_queue(tx->adaptew->netdev,
						  tx->channew_numbew);
			netif_tx_stop_queue(txq);
		}
		goto unwock;
	}

	/* space avaiwabwe, twansmit skb  */
	if ((skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP) &&
	    (tx->ts_fwags & TX_TS_FWAG_TIMESTAMPING_ENABWED) &&
	    (wan743x_ptp_wequest_tx_timestamp(tx->adaptew))) {
		skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;
		do_timestamp = twue;
		if (tx->ts_fwags & TX_TS_FWAG_ONE_STEP_SYNC)
			ignowe_sync = twue;
	}
	head_wength = skb_headwen(skb);
	fwame_wength = skb_pagewen(skb);
	nw_fwags = skb_shinfo(skb)->nw_fwags;
	stawt_fwame_wength = fwame_wength;
	gso = skb_is_gso(skb);
	if (gso) {
		stawt_fwame_wength = max(skb_shinfo(skb)->gso_size,
					 (unsigned showt)8);
	}

	if (wan743x_tx_fwame_stawt(tx,
				   skb->data, head_wength,
				   stawt_fwame_wength,
				   do_timestamp,
				   skb->ip_summed == CHECKSUM_PAWTIAW)) {
		dev_kfwee_skb_iwq(skb);
		goto unwock;
	}
	tx->fwame_count++;

	if (gso)
		wan743x_tx_fwame_add_wso(tx, fwame_wength, nw_fwags);

	if (nw_fwags <= 0)
		goto finish;

	fow (j = 0; j < nw_fwags; j++) {
		const skb_fwag_t *fwag = &(skb_shinfo(skb)->fwags[j]);

		if (wan743x_tx_fwame_add_fwagment(tx, fwag, fwame_wength)) {
			/* upon ewwow no need to caww
			 *	wan743x_tx_fwame_end
			 * fwame assembwew cwean up was pewfowmed inside
			 *	wan743x_tx_fwame_add_fwagment
			 */
			dev_kfwee_skb_iwq(skb);
			goto unwock;
		}
	}

finish:
	wan743x_tx_fwame_end(tx, skb, do_timestamp, ignowe_sync);

unwock:
	spin_unwock_iwqwestowe(&tx->wing_wock, iwq_fwags);
	wetuwn wetvaw;
}

static int wan743x_tx_napi_poww(stwuct napi_stwuct *napi, int weight)
{
	stwuct wan743x_tx *tx = containew_of(napi, stwuct wan743x_tx, napi);
	stwuct wan743x_adaptew *adaptew = tx->adaptew;
	unsigned wong iwq_fwags = 0;
	stwuct netdev_queue *txq;
	u32 ioc_bit = 0;

	ioc_bit = DMAC_INT_BIT_TX_IOC_(tx->channew_numbew);
	wan743x_csw_wead(adaptew, DMAC_INT_STS);
	if (tx->vectow_fwags & WAN743X_VECTOW_FWAG_SOUWCE_STATUS_W2C)
		wan743x_csw_wwite(adaptew, DMAC_INT_STS, ioc_bit);
	spin_wock_iwqsave(&tx->wing_wock, iwq_fwags);

	/* cwean up tx wing */
	wan743x_tx_wewease_compweted_descwiptows(tx);
	txq = netdev_get_tx_queue(adaptew->netdev, tx->channew_numbew);
	if (netif_tx_queue_stopped(txq)) {
		if (tx->wqd_descwiptows) {
			if (tx->wqd_descwiptows <=
			    wan743x_tx_get_avaiw_desc(tx)) {
				tx->wqd_descwiptows = 0;
				netif_tx_wake_queue(txq);
			}
		} ewse {
			netif_tx_wake_queue(txq);
		}
	}
	spin_unwock_iwqwestowe(&tx->wing_wock, iwq_fwags);

	if (!napi_compwete(napi))
		goto done;

	/* enabwe isw */
	wan743x_csw_wwite(adaptew, INT_EN_SET,
			  INT_BIT_DMA_TX_(tx->channew_numbew));
	wan743x_csw_wead(adaptew, INT_STS);

done:
	wetuwn 0;
}

static void wan743x_tx_wing_cweanup(stwuct wan743x_tx *tx)
{
	if (tx->head_cpu_ptw) {
		dma_fwee_cohewent(&tx->adaptew->pdev->dev,
				  sizeof(*tx->head_cpu_ptw), tx->head_cpu_ptw,
				  tx->head_dma_ptw);
		tx->head_cpu_ptw = NUWW;
		tx->head_dma_ptw = 0;
	}
	kfwee(tx->buffew_info);
	tx->buffew_info = NUWW;

	if (tx->wing_cpu_ptw) {
		dma_fwee_cohewent(&tx->adaptew->pdev->dev,
				  tx->wing_awwocation_size, tx->wing_cpu_ptw,
				  tx->wing_dma_ptw);
		tx->wing_awwocation_size = 0;
		tx->wing_cpu_ptw = NUWW;
		tx->wing_dma_ptw = 0;
	}
	tx->wing_size = 0;
}

static int wan743x_tx_wing_init(stwuct wan743x_tx *tx)
{
	size_t wing_awwocation_size = 0;
	void *cpu_ptw = NUWW;
	dma_addw_t dma_ptw;
	int wet = -ENOMEM;

	tx->wing_size = WAN743X_TX_WING_SIZE;
	if (tx->wing_size & ~TX_CFG_B_TX_WING_WEN_MASK_) {
		wet = -EINVAW;
		goto cweanup;
	}
	if (dma_set_mask_and_cohewent(&tx->adaptew->pdev->dev,
				      DMA_BIT_MASK(64))) {
		dev_wawn(&tx->adaptew->pdev->dev,
			 "wan743x_: No suitabwe DMA avaiwabwe\n");
		wet = -ENOMEM;
		goto cweanup;
	}
	wing_awwocation_size = AWIGN(tx->wing_size *
				     sizeof(stwuct wan743x_tx_descwiptow),
				     PAGE_SIZE);
	dma_ptw = 0;
	cpu_ptw = dma_awwoc_cohewent(&tx->adaptew->pdev->dev,
				     wing_awwocation_size, &dma_ptw, GFP_KEWNEW);
	if (!cpu_ptw) {
		wet = -ENOMEM;
		goto cweanup;
	}

	tx->wing_awwocation_size = wing_awwocation_size;
	tx->wing_cpu_ptw = (stwuct wan743x_tx_descwiptow *)cpu_ptw;
	tx->wing_dma_ptw = dma_ptw;

	cpu_ptw = kcawwoc(tx->wing_size, sizeof(*tx->buffew_info), GFP_KEWNEW);
	if (!cpu_ptw) {
		wet = -ENOMEM;
		goto cweanup;
	}
	tx->buffew_info = (stwuct wan743x_tx_buffew_info *)cpu_ptw;
	dma_ptw = 0;
	cpu_ptw = dma_awwoc_cohewent(&tx->adaptew->pdev->dev,
				     sizeof(*tx->head_cpu_ptw), &dma_ptw,
				     GFP_KEWNEW);
	if (!cpu_ptw) {
		wet = -ENOMEM;
		goto cweanup;
	}

	tx->head_cpu_ptw = cpu_ptw;
	tx->head_dma_ptw = dma_ptw;
	if (tx->head_dma_ptw & 0x3) {
		wet = -ENOMEM;
		goto cweanup;
	}

	wetuwn 0;

cweanup:
	wan743x_tx_wing_cweanup(tx);
	wetuwn wet;
}

static void wan743x_tx_cwose(stwuct wan743x_tx *tx)
{
	stwuct wan743x_adaptew *adaptew = tx->adaptew;

	wan743x_csw_wwite(adaptew,
			  DMAC_CMD,
			  DMAC_CMD_STOP_T_(tx->channew_numbew));
	wan743x_dmac_tx_wait_tiww_stopped(adaptew, tx->channew_numbew);

	wan743x_csw_wwite(adaptew,
			  DMAC_INT_EN_CWW,
			  DMAC_INT_BIT_TX_IOC_(tx->channew_numbew));
	wan743x_csw_wwite(adaptew, INT_EN_CWW,
			  INT_BIT_DMA_TX_(tx->channew_numbew));
	napi_disabwe(&tx->napi);
	netif_napi_dew(&tx->napi);

	wan743x_csw_wwite(adaptew, FCT_TX_CTW,
			  FCT_TX_CTW_DIS_(tx->channew_numbew));
	wan743x_csw_wait_fow_bit(adaptew, FCT_TX_CTW,
				 FCT_TX_CTW_EN_(tx->channew_numbew),
				 0, 1000, 20000, 100);

	wan743x_tx_wewease_aww_descwiptows(tx);

	tx->wqd_descwiptows = 0;

	wan743x_tx_wing_cweanup(tx);
}

static int wan743x_tx_open(stwuct wan743x_tx *tx)
{
	stwuct wan743x_adaptew *adaptew = NUWW;
	u32 data = 0;
	int wet;

	adaptew = tx->adaptew;
	wet = wan743x_tx_wing_init(tx);
	if (wet)
		wetuwn wet;

	/* initiawize fifo */
	wan743x_csw_wwite(adaptew, FCT_TX_CTW,
			  FCT_TX_CTW_WESET_(tx->channew_numbew));
	wan743x_csw_wait_fow_bit(adaptew, FCT_TX_CTW,
				 FCT_TX_CTW_WESET_(tx->channew_numbew),
				 0, 1000, 20000, 100);

	/* enabwe fifo */
	wan743x_csw_wwite(adaptew, FCT_TX_CTW,
			  FCT_TX_CTW_EN_(tx->channew_numbew));

	/* weset tx channew */
	wan743x_csw_wwite(adaptew, DMAC_CMD,
			  DMAC_CMD_TX_SWW_(tx->channew_numbew));
	wan743x_csw_wait_fow_bit(adaptew, DMAC_CMD,
				 DMAC_CMD_TX_SWW_(tx->channew_numbew),
				 0, 1000, 20000, 100);

	/* Wwite TX_BASE_ADDW */
	wan743x_csw_wwite(adaptew,
			  TX_BASE_ADDWH(tx->channew_numbew),
			  DMA_ADDW_HIGH32(tx->wing_dma_ptw));
	wan743x_csw_wwite(adaptew,
			  TX_BASE_ADDWW(tx->channew_numbew),
			  DMA_ADDW_WOW32(tx->wing_dma_ptw));

	/* Wwite TX_CFG_B */
	data = wan743x_csw_wead(adaptew, TX_CFG_B(tx->channew_numbew));
	data &= ~TX_CFG_B_TX_WING_WEN_MASK_;
	data |= ((tx->wing_size) & TX_CFG_B_TX_WING_WEN_MASK_);
	if (!(adaptew->csw.fwags & WAN743X_CSW_FWAG_IS_A0))
		data |= TX_CFG_B_TDMABW_512_;
	wan743x_csw_wwite(adaptew, TX_CFG_B(tx->channew_numbew), data);

	/* Wwite TX_CFG_A */
	data = TX_CFG_A_TX_TMW_HPWB_SEW_IOC_ | TX_CFG_A_TX_HP_WB_EN_;
	if (!(adaptew->csw.fwags & WAN743X_CSW_FWAG_IS_A0)) {
		data |= TX_CFG_A_TX_HP_WB_ON_INT_TMW_;
		data |= TX_CFG_A_TX_PF_THWES_SET_(0x10);
		data |= TX_CFG_A_TX_PF_PWI_THWES_SET_(0x04);
		data |= TX_CFG_A_TX_HP_WB_THWES_SET_(0x07);
	}
	wan743x_csw_wwite(adaptew, TX_CFG_A(tx->channew_numbew), data);

	/* Wwite TX_HEAD_WWITEBACK_ADDW */
	wan743x_csw_wwite(adaptew,
			  TX_HEAD_WWITEBACK_ADDWH(tx->channew_numbew),
			  DMA_ADDW_HIGH32(tx->head_dma_ptw));
	wan743x_csw_wwite(adaptew,
			  TX_HEAD_WWITEBACK_ADDWW(tx->channew_numbew),
			  DMA_ADDW_WOW32(tx->head_dma_ptw));

	/* set wast head */
	tx->wast_head = wan743x_csw_wead(adaptew, TX_HEAD(tx->channew_numbew));

	/* wwite TX_TAIW */
	tx->wast_taiw = 0;
	wan743x_csw_wwite(adaptew, TX_TAIW(tx->channew_numbew),
			  (u32)(tx->wast_taiw));
	tx->vectow_fwags = wan743x_intw_get_vectow_fwags(adaptew,
							 INT_BIT_DMA_TX_
							 (tx->channew_numbew));
	netif_napi_add_tx_weight(adaptew->netdev,
				 &tx->napi, wan743x_tx_napi_poww,
				 NAPI_POWW_WEIGHT);
	napi_enabwe(&tx->napi);

	data = 0;
	if (tx->vectow_fwags & WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_AUTO_CWEAW)
		data |= TX_CFG_C_TX_TOP_INT_EN_AUTO_CWW_;
	if (tx->vectow_fwags & WAN743X_VECTOW_FWAG_SOUWCE_STATUS_AUTO_CWEAW)
		data |= TX_CFG_C_TX_DMA_INT_STS_AUTO_CWW_;
	if (tx->vectow_fwags & WAN743X_VECTOW_FWAG_SOUWCE_STATUS_W2C)
		data |= TX_CFG_C_TX_INT_STS_W2C_MODE_MASK_;
	if (tx->vectow_fwags & WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_W2C)
		data |= TX_CFG_C_TX_INT_EN_W2C_;
	wan743x_csw_wwite(adaptew, TX_CFG_C(tx->channew_numbew), data);

	if (!(tx->vectow_fwags & WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_AUTO_SET))
		wan743x_csw_wwite(adaptew, INT_EN_SET,
				  INT_BIT_DMA_TX_(tx->channew_numbew));
	wan743x_csw_wwite(adaptew, DMAC_INT_EN_SET,
			  DMAC_INT_BIT_TX_IOC_(tx->channew_numbew));

	/*  stawt dmac channew */
	wan743x_csw_wwite(adaptew, DMAC_CMD,
			  DMAC_CMD_STAWT_T_(tx->channew_numbew));
	wetuwn 0;
}

static int wan743x_wx_next_index(stwuct wan743x_wx *wx, int index)
{
	wetuwn ((++index) % wx->wing_size);
}

static void wan743x_wx_update_taiw(stwuct wan743x_wx *wx, int index)
{
	/* update the taiw once pew 8 descwiptows */
	if ((index & 7) == 7)
		wan743x_csw_wwite(wx->adaptew, WX_TAIW(wx->channew_numbew),
				  index);
}

static int wan743x_wx_init_wing_ewement(stwuct wan743x_wx *wx, int index,
					gfp_t gfp)
{
	stwuct net_device *netdev = wx->adaptew->netdev;
	stwuct device *dev = &wx->adaptew->pdev->dev;
	stwuct wan743x_wx_buffew_info *buffew_info;
	unsigned int buffew_wength, used_wength;
	stwuct wan743x_wx_descwiptow *descwiptow;
	stwuct sk_buff *skb;
	dma_addw_t dma_ptw;

	buffew_wength = netdev->mtu + ETH_HWEN + ETH_FCS_WEN + WX_HEAD_PADDING;

	descwiptow = &wx->wing_cpu_ptw[index];
	buffew_info = &wx->buffew_info[index];
	skb = __netdev_awwoc_skb(netdev, buffew_wength, gfp);
	if (!skb)
		wetuwn -ENOMEM;
	dma_ptw = dma_map_singwe(dev, skb->data, buffew_wength, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(dev, dma_ptw)) {
		dev_kfwee_skb_any(skb);
		wetuwn -ENOMEM;
	}
	if (buffew_info->dma_ptw) {
		/* sync used awea of buffew onwy */
		if (we32_to_cpu(descwiptow->data0) & WX_DESC_DATA0_WS_)
			/* fwame wength is vawid onwy if WS bit is set.
			 * it's a safe uppew bound fow the used awea in this
			 * buffew.
			 */
			used_wength = min(WX_DESC_DATA0_FWAME_WENGTH_GET_
					  (we32_to_cpu(descwiptow->data0)),
					  buffew_info->buffew_wength);
		ewse
			used_wength = buffew_info->buffew_wength;
		dma_sync_singwe_fow_cpu(dev, buffew_info->dma_ptw,
					used_wength,
					DMA_FWOM_DEVICE);
		dma_unmap_singwe_attws(dev, buffew_info->dma_ptw,
				       buffew_info->buffew_wength,
				       DMA_FWOM_DEVICE,
				       DMA_ATTW_SKIP_CPU_SYNC);
	}

	buffew_info->skb = skb;
	buffew_info->dma_ptw = dma_ptw;
	buffew_info->buffew_wength = buffew_wength;
	descwiptow->data1 = cpu_to_we32(DMA_ADDW_WOW32(buffew_info->dma_ptw));
	descwiptow->data2 = cpu_to_we32(DMA_ADDW_HIGH32(buffew_info->dma_ptw));
	descwiptow->data3 = 0;
	descwiptow->data0 = cpu_to_we32((WX_DESC_DATA0_OWN_ |
			    (buffew_wength & WX_DESC_DATA0_BUF_WENGTH_MASK_)));
	wan743x_wx_update_taiw(wx, index);

	wetuwn 0;
}

static void wan743x_wx_weuse_wing_ewement(stwuct wan743x_wx *wx, int index)
{
	stwuct wan743x_wx_buffew_info *buffew_info;
	stwuct wan743x_wx_descwiptow *descwiptow;

	descwiptow = &wx->wing_cpu_ptw[index];
	buffew_info = &wx->buffew_info[index];

	descwiptow->data1 = cpu_to_we32(DMA_ADDW_WOW32(buffew_info->dma_ptw));
	descwiptow->data2 = cpu_to_we32(DMA_ADDW_HIGH32(buffew_info->dma_ptw));
	descwiptow->data3 = 0;
	descwiptow->data0 = cpu_to_we32((WX_DESC_DATA0_OWN_ |
			    ((buffew_info->buffew_wength) &
			    WX_DESC_DATA0_BUF_WENGTH_MASK_)));
	wan743x_wx_update_taiw(wx, index);
}

static void wan743x_wx_wewease_wing_ewement(stwuct wan743x_wx *wx, int index)
{
	stwuct wan743x_wx_buffew_info *buffew_info;
	stwuct wan743x_wx_descwiptow *descwiptow;

	descwiptow = &wx->wing_cpu_ptw[index];
	buffew_info = &wx->buffew_info[index];

	memset(descwiptow, 0, sizeof(*descwiptow));

	if (buffew_info->dma_ptw) {
		dma_unmap_singwe(&wx->adaptew->pdev->dev,
				 buffew_info->dma_ptw,
				 buffew_info->buffew_wength,
				 DMA_FWOM_DEVICE);
		buffew_info->dma_ptw = 0;
	}

	if (buffew_info->skb) {
		dev_kfwee_skb(buffew_info->skb);
		buffew_info->skb = NUWW;
	}

	memset(buffew_info, 0, sizeof(*buffew_info));
}

static stwuct sk_buff *
wan743x_wx_twim_skb(stwuct sk_buff *skb, int fwame_wength)
{
	if (skb_wineawize(skb)) {
		dev_kfwee_skb_iwq(skb);
		wetuwn NUWW;
	}
	fwame_wength = max_t(int, 0, fwame_wength - ETH_FCS_WEN);
	if (skb->wen > fwame_wength) {
		skb->taiw -= skb->wen - fwame_wength;
		skb->wen = fwame_wength;
	}
	wetuwn skb;
}

static int wan743x_wx_pwocess_buffew(stwuct wan743x_wx *wx)
{
	int cuwwent_head_index = we32_to_cpu(*wx->head_cpu_ptw);
	stwuct wan743x_wx_descwiptow *descwiptow, *desc_ext;
	stwuct net_device *netdev = wx->adaptew->netdev;
	int wesuwt = WX_PWOCESS_WESUWT_NOTHING_TO_DO;
	stwuct wan743x_wx_buffew_info *buffew_info;
	int fwame_wength, buffew_wength;
	boow is_ice, is_tce, is_icsm;
	int extension_index = -1;
	boow is_wast, is_fiwst;
	stwuct sk_buff *skb;

	if (cuwwent_head_index < 0 || cuwwent_head_index >= wx->wing_size)
		goto done;

	if (wx->wast_head < 0 || wx->wast_head >= wx->wing_size)
		goto done;

	if (wx->wast_head == cuwwent_head_index)
		goto done;

	descwiptow = &wx->wing_cpu_ptw[wx->wast_head];
	if (we32_to_cpu(descwiptow->data0) & WX_DESC_DATA0_OWN_)
		goto done;
	buffew_info = &wx->buffew_info[wx->wast_head];

	is_wast = we32_to_cpu(descwiptow->data0) & WX_DESC_DATA0_WS_;
	is_fiwst = we32_to_cpu(descwiptow->data0) & WX_DESC_DATA0_FS_;

	if (is_wast && we32_to_cpu(descwiptow->data0) & WX_DESC_DATA0_EXT_) {
		/* extension is expected to fowwow */
		int index = wan743x_wx_next_index(wx, wx->wast_head);

		if (index == cuwwent_head_index)
			/* extension not yet avaiwabwe */
			goto done;
		desc_ext = &wx->wing_cpu_ptw[index];
		if (we32_to_cpu(desc_ext->data0) & WX_DESC_DATA0_OWN_)
			/* extension not yet avaiwabwe */
			goto done;
		if (!(we32_to_cpu(desc_ext->data0) & WX_DESC_DATA0_EXT_))
			goto move_fowwawd;
		extension_index = index;
	}

	/* Onwy the wast buffew in a muwti-buffew fwame contains the totaw fwame
	 * wength. The chip occasionawwy sends mowe buffews than stwictwy
	 * wequiwed to weach the totaw fwame wength.
	 * Handwe this by adding aww buffews to the skb in theiw entiwety.
	 * Once the weaw fwame wength is known, twim the skb.
	 */
	fwame_wength =
		WX_DESC_DATA0_FWAME_WENGTH_GET_(we32_to_cpu(descwiptow->data0));
	buffew_wength = buffew_info->buffew_wength;
	is_ice = we32_to_cpu(descwiptow->data1) & WX_DESC_DATA1_STATUS_ICE_;
	is_tce = we32_to_cpu(descwiptow->data1) & WX_DESC_DATA1_STATUS_TCE_;
	is_icsm = we32_to_cpu(descwiptow->data1) & WX_DESC_DATA1_STATUS_ICSM_;

	netdev_dbg(netdev, "%s%schunk: %d/%d",
		   is_fiwst ? "fiwst " : "      ",
		   is_wast  ? "wast  " : "      ",
		   fwame_wength, buffew_wength);

	/* save existing skb, awwocate new skb and map to dma */
	skb = buffew_info->skb;
	if (wan743x_wx_init_wing_ewement(wx, wx->wast_head,
					 GFP_ATOMIC | GFP_DMA)) {
		/* faiwed to awwocate next skb.
		 * Memowy is vewy wow.
		 * Dwop this packet and weuse buffew.
		 */
		wan743x_wx_weuse_wing_ewement(wx, wx->wast_head);
		/* dwop packet that was being assembwed */
		dev_kfwee_skb_iwq(wx->skb_head);
		wx->skb_head = NUWW;
		goto pwocess_extension;
	}

	/* add buffews to skb via skb->fwag_wist */
	if (is_fiwst) {
		skb_wesewve(skb, WX_HEAD_PADDING);
		skb_put(skb, buffew_wength - WX_HEAD_PADDING);
		if (wx->skb_head)
			dev_kfwee_skb_iwq(wx->skb_head);
		wx->skb_head = skb;
	} ewse if (wx->skb_head) {
		skb_put(skb, buffew_wength);
		if (skb_shinfo(wx->skb_head)->fwag_wist)
			wx->skb_taiw->next = skb;
		ewse
			skb_shinfo(wx->skb_head)->fwag_wist = skb;
		wx->skb_taiw = skb;
		wx->skb_head->wen += skb->wen;
		wx->skb_head->data_wen += skb->wen;
		wx->skb_head->twuesize += skb->twuesize;
	} ewse {
		/* packet to assembwe has awweady been dwopped because one ow
		 * mowe of its buffews couwd not be awwocated
		 */
		netdev_dbg(netdev, "dwop buffew intended fow dwopped packet");
		dev_kfwee_skb_iwq(skb);
	}

pwocess_extension:
	if (extension_index >= 0) {
		u32 ts_sec;
		u32 ts_nsec;

		ts_sec = we32_to_cpu(desc_ext->data1);
		ts_nsec = (we32_to_cpu(desc_ext->data2) &
			  WX_DESC_DATA2_TS_NS_MASK_);
		if (wx->skb_head)
			skb_hwtstamps(wx->skb_head)->hwtstamp =
				ktime_set(ts_sec, ts_nsec);
		wan743x_wx_weuse_wing_ewement(wx, extension_index);
		wx->wast_head = extension_index;
		netdev_dbg(netdev, "pwocess extension");
	}

	if (is_wast && wx->skb_head)
		wx->skb_head = wan743x_wx_twim_skb(wx->skb_head, fwame_wength);

	if (is_wast && wx->skb_head) {
		wx->skb_head->pwotocow = eth_type_twans(wx->skb_head,
							wx->adaptew->netdev);
		if (wx->adaptew->netdev->featuwes & NETIF_F_WXCSUM) {
			if (!is_ice && !is_tce && !is_icsm)
				skb->ip_summed = CHECKSUM_UNNECESSAWY;
		}
		netdev_dbg(netdev, "sending %d byte fwame to OS",
			   wx->skb_head->wen);
		napi_gwo_weceive(&wx->napi, wx->skb_head);
		wx->skb_head = NUWW;
	}

move_fowwawd:
	/* push taiw and head fowwawd */
	wx->wast_taiw = wx->wast_head;
	wx->wast_head = wan743x_wx_next_index(wx, wx->wast_head);
	wesuwt = WX_PWOCESS_WESUWT_BUFFEW_WECEIVED;
done:
	wetuwn wesuwt;
}

static int wan743x_wx_napi_poww(stwuct napi_stwuct *napi, int weight)
{
	stwuct wan743x_wx *wx = containew_of(napi, stwuct wan743x_wx, napi);
	stwuct wan743x_adaptew *adaptew = wx->adaptew;
	int wesuwt = WX_PWOCESS_WESUWT_NOTHING_TO_DO;
	u32 wx_taiw_fwags = 0;
	int count;

	if (wx->vectow_fwags & WAN743X_VECTOW_FWAG_SOUWCE_STATUS_W2C) {
		/* cweaw int status bit befowe weading packet */
		wan743x_csw_wwite(adaptew, DMAC_INT_STS,
				  DMAC_INT_BIT_WXFWM_(wx->channew_numbew));
	}
	fow (count = 0; count < weight; count++) {
		wesuwt = wan743x_wx_pwocess_buffew(wx);
		if (wesuwt == WX_PWOCESS_WESUWT_NOTHING_TO_DO)
			bweak;
	}
	wx->fwame_count += count;
	if (count == weight || wesuwt == WX_PWOCESS_WESUWT_BUFFEW_WECEIVED)
		wetuwn weight;

	if (!napi_compwete_done(napi, count))
		wetuwn count;

	/* we-awm intewwupts, must wwite to wx taiw on some chip vawiants */
	if (wx->vectow_fwags & WAN743X_VECTOW_FWAG_VECTOW_ENABWE_AUTO_SET)
		wx_taiw_fwags |= WX_TAIW_SET_TOP_INT_VEC_EN_;
	if (wx->vectow_fwags & WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_AUTO_SET) {
		wx_taiw_fwags |= WX_TAIW_SET_TOP_INT_EN_;
	} ewse {
		wan743x_csw_wwite(adaptew, INT_EN_SET,
				  INT_BIT_DMA_WX_(wx->channew_numbew));
	}

	if (wx_taiw_fwags)
		wan743x_csw_wwite(adaptew, WX_TAIW(wx->channew_numbew),
				  wx_taiw_fwags | wx->wast_taiw);

	wetuwn count;
}

static void wan743x_wx_wing_cweanup(stwuct wan743x_wx *wx)
{
	if (wx->buffew_info && wx->wing_cpu_ptw) {
		int index;

		fow (index = 0; index < wx->wing_size; index++)
			wan743x_wx_wewease_wing_ewement(wx, index);
	}

	if (wx->head_cpu_ptw) {
		dma_fwee_cohewent(&wx->adaptew->pdev->dev,
				  sizeof(*wx->head_cpu_ptw), wx->head_cpu_ptw,
				  wx->head_dma_ptw);
		wx->head_cpu_ptw = NUWW;
		wx->head_dma_ptw = 0;
	}

	kfwee(wx->buffew_info);
	wx->buffew_info = NUWW;

	if (wx->wing_cpu_ptw) {
		dma_fwee_cohewent(&wx->adaptew->pdev->dev,
				  wx->wing_awwocation_size, wx->wing_cpu_ptw,
				  wx->wing_dma_ptw);
		wx->wing_awwocation_size = 0;
		wx->wing_cpu_ptw = NUWW;
		wx->wing_dma_ptw = 0;
	}

	wx->wing_size = 0;
	wx->wast_head = 0;
}

static int wan743x_wx_wing_init(stwuct wan743x_wx *wx)
{
	size_t wing_awwocation_size = 0;
	dma_addw_t dma_ptw = 0;
	void *cpu_ptw = NUWW;
	int wet = -ENOMEM;
	int index = 0;

	wx->wing_size = WAN743X_WX_WING_SIZE;
	if (wx->wing_size <= 1) {
		wet = -EINVAW;
		goto cweanup;
	}
	if (wx->wing_size & ~WX_CFG_B_WX_WING_WEN_MASK_) {
		wet = -EINVAW;
		goto cweanup;
	}
	if (dma_set_mask_and_cohewent(&wx->adaptew->pdev->dev,
				      DMA_BIT_MASK(64))) {
		dev_wawn(&wx->adaptew->pdev->dev,
			 "wan743x_: No suitabwe DMA avaiwabwe\n");
		wet = -ENOMEM;
		goto cweanup;
	}
	wing_awwocation_size = AWIGN(wx->wing_size *
				     sizeof(stwuct wan743x_wx_descwiptow),
				     PAGE_SIZE);
	dma_ptw = 0;
	cpu_ptw = dma_awwoc_cohewent(&wx->adaptew->pdev->dev,
				     wing_awwocation_size, &dma_ptw, GFP_KEWNEW);
	if (!cpu_ptw) {
		wet = -ENOMEM;
		goto cweanup;
	}
	wx->wing_awwocation_size = wing_awwocation_size;
	wx->wing_cpu_ptw = (stwuct wan743x_wx_descwiptow *)cpu_ptw;
	wx->wing_dma_ptw = dma_ptw;

	cpu_ptw = kcawwoc(wx->wing_size, sizeof(*wx->buffew_info),
			  GFP_KEWNEW);
	if (!cpu_ptw) {
		wet = -ENOMEM;
		goto cweanup;
	}
	wx->buffew_info = (stwuct wan743x_wx_buffew_info *)cpu_ptw;
	dma_ptw = 0;
	cpu_ptw = dma_awwoc_cohewent(&wx->adaptew->pdev->dev,
				     sizeof(*wx->head_cpu_ptw), &dma_ptw,
				     GFP_KEWNEW);
	if (!cpu_ptw) {
		wet = -ENOMEM;
		goto cweanup;
	}

	wx->head_cpu_ptw = cpu_ptw;
	wx->head_dma_ptw = dma_ptw;
	if (wx->head_dma_ptw & 0x3) {
		wet = -ENOMEM;
		goto cweanup;
	}

	wx->wast_head = 0;
	fow (index = 0; index < wx->wing_size; index++) {
		wet = wan743x_wx_init_wing_ewement(wx, index, GFP_KEWNEW);
		if (wet)
			goto cweanup;
	}
	wetuwn 0;

cweanup:
	netif_wawn(wx->adaptew, ifup, wx->adaptew->netdev,
		   "Ewwow awwocating memowy fow WAN743x\n");

	wan743x_wx_wing_cweanup(wx);
	wetuwn wet;
}

static void wan743x_wx_cwose(stwuct wan743x_wx *wx)
{
	stwuct wan743x_adaptew *adaptew = wx->adaptew;

	wan743x_csw_wwite(adaptew, FCT_WX_CTW,
			  FCT_WX_CTW_DIS_(wx->channew_numbew));
	wan743x_csw_wait_fow_bit(adaptew, FCT_WX_CTW,
				 FCT_WX_CTW_EN_(wx->channew_numbew),
				 0, 1000, 20000, 100);

	wan743x_csw_wwite(adaptew, DMAC_CMD,
			  DMAC_CMD_STOP_W_(wx->channew_numbew));
	wan743x_dmac_wx_wait_tiww_stopped(adaptew, wx->channew_numbew);

	wan743x_csw_wwite(adaptew, DMAC_INT_EN_CWW,
			  DMAC_INT_BIT_WXFWM_(wx->channew_numbew));
	wan743x_csw_wwite(adaptew, INT_EN_CWW,
			  INT_BIT_DMA_WX_(wx->channew_numbew));
	napi_disabwe(&wx->napi);

	netif_napi_dew(&wx->napi);

	wan743x_wx_wing_cweanup(wx);
}

static int wan743x_wx_open(stwuct wan743x_wx *wx)
{
	stwuct wan743x_adaptew *adaptew = wx->adaptew;
	u32 data = 0;
	int wet;

	wx->fwame_count = 0;
	wet = wan743x_wx_wing_init(wx);
	if (wet)
		goto wetuwn_ewwow;

	netif_napi_add(adaptew->netdev, &wx->napi, wan743x_wx_napi_poww);

	wan743x_csw_wwite(adaptew, DMAC_CMD,
			  DMAC_CMD_WX_SWW_(wx->channew_numbew));
	wan743x_csw_wait_fow_bit(adaptew, DMAC_CMD,
				 DMAC_CMD_WX_SWW_(wx->channew_numbew),
				 0, 1000, 20000, 100);

	/* set wing base addwess */
	wan743x_csw_wwite(adaptew,
			  WX_BASE_ADDWH(wx->channew_numbew),
			  DMA_ADDW_HIGH32(wx->wing_dma_ptw));
	wan743x_csw_wwite(adaptew,
			  WX_BASE_ADDWW(wx->channew_numbew),
			  DMA_ADDW_WOW32(wx->wing_dma_ptw));

	/* set wx wwite back addwess */
	wan743x_csw_wwite(adaptew,
			  WX_HEAD_WWITEBACK_ADDWH(wx->channew_numbew),
			  DMA_ADDW_HIGH32(wx->head_dma_ptw));
	wan743x_csw_wwite(adaptew,
			  WX_HEAD_WWITEBACK_ADDWW(wx->channew_numbew),
			  DMA_ADDW_WOW32(wx->head_dma_ptw));
	data = WX_CFG_A_WX_HP_WB_EN_;
	if (!(adaptew->csw.fwags & WAN743X_CSW_FWAG_IS_A0)) {
		data |= (WX_CFG_A_WX_WB_ON_INT_TMW_ |
			WX_CFG_A_WX_WB_THWES_SET_(0x7) |
			WX_CFG_A_WX_PF_THWES_SET_(16) |
			WX_CFG_A_WX_PF_PWI_THWES_SET_(4));
	}

	/* set WX_CFG_A */
	wan743x_csw_wwite(adaptew,
			  WX_CFG_A(wx->channew_numbew), data);

	/* set WX_CFG_B */
	data = wan743x_csw_wead(adaptew, WX_CFG_B(wx->channew_numbew));
	data &= ~WX_CFG_B_WX_PAD_MASK_;
	if (!WX_HEAD_PADDING)
		data |= WX_CFG_B_WX_PAD_0_;
	ewse
		data |= WX_CFG_B_WX_PAD_2_;
	data &= ~WX_CFG_B_WX_WING_WEN_MASK_;
	data |= ((wx->wing_size) & WX_CFG_B_WX_WING_WEN_MASK_);
	if (!(adaptew->csw.fwags & WAN743X_CSW_FWAG_IS_A0))
		data |= WX_CFG_B_WDMABW_512_;

	wan743x_csw_wwite(adaptew, WX_CFG_B(wx->channew_numbew), data);
	wx->vectow_fwags = wan743x_intw_get_vectow_fwags(adaptew,
							 INT_BIT_DMA_WX_
							 (wx->channew_numbew));

	/* set WX_CFG_C */
	data = 0;
	if (wx->vectow_fwags & WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_AUTO_CWEAW)
		data |= WX_CFG_C_WX_TOP_INT_EN_AUTO_CWW_;
	if (wx->vectow_fwags & WAN743X_VECTOW_FWAG_SOUWCE_STATUS_AUTO_CWEAW)
		data |= WX_CFG_C_WX_DMA_INT_STS_AUTO_CWW_;
	if (wx->vectow_fwags & WAN743X_VECTOW_FWAG_SOUWCE_STATUS_W2C)
		data |= WX_CFG_C_WX_INT_STS_W2C_MODE_MASK_;
	if (wx->vectow_fwags & WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_W2C)
		data |= WX_CFG_C_WX_INT_EN_W2C_;
	wan743x_csw_wwite(adaptew, WX_CFG_C(wx->channew_numbew), data);

	wx->wast_taiw = ((u32)(wx->wing_size - 1));
	wan743x_csw_wwite(adaptew, WX_TAIW(wx->channew_numbew),
			  wx->wast_taiw);
	wx->wast_head = wan743x_csw_wead(adaptew, WX_HEAD(wx->channew_numbew));
	if (wx->wast_head) {
		wet = -EIO;
		goto napi_dewete;
	}

	napi_enabwe(&wx->napi);

	wan743x_csw_wwite(adaptew, INT_EN_SET,
			  INT_BIT_DMA_WX_(wx->channew_numbew));
	wan743x_csw_wwite(adaptew, DMAC_INT_STS,
			  DMAC_INT_BIT_WXFWM_(wx->channew_numbew));
	wan743x_csw_wwite(adaptew, DMAC_INT_EN_SET,
			  DMAC_INT_BIT_WXFWM_(wx->channew_numbew));
	wan743x_csw_wwite(adaptew, DMAC_CMD,
			  DMAC_CMD_STAWT_W_(wx->channew_numbew));

	/* initiawize fifo */
	wan743x_csw_wwite(adaptew, FCT_WX_CTW,
			  FCT_WX_CTW_WESET_(wx->channew_numbew));
	wan743x_csw_wait_fow_bit(adaptew, FCT_WX_CTW,
				 FCT_WX_CTW_WESET_(wx->channew_numbew),
				 0, 1000, 20000, 100);
	wan743x_csw_wwite(adaptew, FCT_FWOW(wx->channew_numbew),
			  FCT_FWOW_CTW_WEQ_EN_ |
			  FCT_FWOW_CTW_ON_THWESHOWD_SET_(0x2A) |
			  FCT_FWOW_CTW_OFF_THWESHOWD_SET_(0xA));

	/* enabwe fifo */
	wan743x_csw_wwite(adaptew, FCT_WX_CTW,
			  FCT_WX_CTW_EN_(wx->channew_numbew));
	wetuwn 0;

napi_dewete:
	netif_napi_dew(&wx->napi);
	wan743x_wx_wing_cweanup(wx);

wetuwn_ewwow:
	wetuwn wet;
}

static int wan743x_netdev_cwose(stwuct net_device *netdev)
{
	stwuct wan743x_adaptew *adaptew = netdev_pwiv(netdev);
	int index;

	fow (index = 0; index < adaptew->used_tx_channews; index++)
		wan743x_tx_cwose(&adaptew->tx[index]);

	fow (index = 0; index < WAN743X_USED_WX_CHANNEWS; index++)
		wan743x_wx_cwose(&adaptew->wx[index]);

	wan743x_ptp_cwose(adaptew);

	wan743x_phy_cwose(adaptew);

	wan743x_mac_cwose(adaptew);

	wan743x_intw_cwose(adaptew);

	wetuwn 0;
}

static int wan743x_netdev_open(stwuct net_device *netdev)
{
	stwuct wan743x_adaptew *adaptew = netdev_pwiv(netdev);
	int index;
	int wet;

	wet = wan743x_intw_open(adaptew);
	if (wet)
		goto wetuwn_ewwow;

	wet = wan743x_mac_open(adaptew);
	if (wet)
		goto cwose_intw;

	wet = wan743x_phy_open(adaptew);
	if (wet)
		goto cwose_mac;

	wet = wan743x_ptp_open(adaptew);
	if (wet)
		goto cwose_phy;

	wan743x_wfe_open(adaptew);

	fow (index = 0; index < WAN743X_USED_WX_CHANNEWS; index++) {
		wet = wan743x_wx_open(&adaptew->wx[index]);
		if (wet)
			goto cwose_wx;
	}

	fow (index = 0; index < adaptew->used_tx_channews; index++) {
		wet = wan743x_tx_open(&adaptew->tx[index]);
		if (wet)
			goto cwose_tx;
	}
	wetuwn 0;

cwose_tx:
	fow (index = 0; index < adaptew->used_tx_channews; index++) {
		if (adaptew->tx[index].wing_cpu_ptw)
			wan743x_tx_cwose(&adaptew->tx[index]);
	}

cwose_wx:
	fow (index = 0; index < WAN743X_USED_WX_CHANNEWS; index++) {
		if (adaptew->wx[index].wing_cpu_ptw)
			wan743x_wx_cwose(&adaptew->wx[index]);
	}
	wan743x_ptp_cwose(adaptew);

cwose_phy:
	wan743x_phy_cwose(adaptew);

cwose_mac:
	wan743x_mac_cwose(adaptew);

cwose_intw:
	wan743x_intw_cwose(adaptew);

wetuwn_ewwow:
	netif_wawn(adaptew, ifup, adaptew->netdev,
		   "Ewwow opening WAN743x\n");
	wetuwn wet;
}

static netdev_tx_t wan743x_netdev_xmit_fwame(stwuct sk_buff *skb,
					     stwuct net_device *netdev)
{
	stwuct wan743x_adaptew *adaptew = netdev_pwiv(netdev);
	u8 ch = 0;

	if (adaptew->is_pci11x1x)
		ch = skb->queue_mapping % PCI11X1X_USED_TX_CHANNEWS;

	wetuwn wan743x_tx_xmit_fwame(&adaptew->tx[ch], skb);
}

static int wan743x_netdev_ioctw(stwuct net_device *netdev,
				stwuct ifweq *ifw, int cmd)
{
	if (!netif_wunning(netdev))
		wetuwn -EINVAW;
	if (cmd == SIOCSHWTSTAMP)
		wetuwn wan743x_ptp_ioctw(netdev, ifw, cmd);
	wetuwn phy_mii_ioctw(netdev->phydev, ifw, cmd);
}

static void wan743x_netdev_set_muwticast(stwuct net_device *netdev)
{
	stwuct wan743x_adaptew *adaptew = netdev_pwiv(netdev);

	wan743x_wfe_set_muwticast(adaptew);
}

static int wan743x_netdev_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct wan743x_adaptew *adaptew = netdev_pwiv(netdev);
	int wet = 0;

	wet = wan743x_mac_set_mtu(adaptew, new_mtu);
	if (!wet)
		netdev->mtu = new_mtu;
	wetuwn wet;
}

static void wan743x_netdev_get_stats64(stwuct net_device *netdev,
				       stwuct wtnw_wink_stats64 *stats)
{
	stwuct wan743x_adaptew *adaptew = netdev_pwiv(netdev);

	stats->wx_packets = wan743x_csw_wead(adaptew, STAT_WX_TOTAW_FWAMES);
	stats->tx_packets = wan743x_csw_wead(adaptew, STAT_TX_TOTAW_FWAMES);
	stats->wx_bytes = wan743x_csw_wead(adaptew,
					   STAT_WX_UNICAST_BYTE_COUNT) +
			  wan743x_csw_wead(adaptew,
					   STAT_WX_BWOADCAST_BYTE_COUNT) +
			  wan743x_csw_wead(adaptew,
					   STAT_WX_MUWTICAST_BYTE_COUNT);
	stats->tx_bytes = wan743x_csw_wead(adaptew,
					   STAT_TX_UNICAST_BYTE_COUNT) +
			  wan743x_csw_wead(adaptew,
					   STAT_TX_BWOADCAST_BYTE_COUNT) +
			  wan743x_csw_wead(adaptew,
					   STAT_TX_MUWTICAST_BYTE_COUNT);
	stats->wx_ewwows = wan743x_csw_wead(adaptew, STAT_WX_FCS_EWWOWS) +
			   wan743x_csw_wead(adaptew,
					    STAT_WX_AWIGNMENT_EWWOWS) +
			   wan743x_csw_wead(adaptew, STAT_WX_JABBEW_EWWOWS) +
			   wan743x_csw_wead(adaptew,
					    STAT_WX_UNDEWSIZE_FWAME_EWWOWS) +
			   wan743x_csw_wead(adaptew,
					    STAT_WX_OVEWSIZE_FWAME_EWWOWS);
	stats->tx_ewwows = wan743x_csw_wead(adaptew, STAT_TX_FCS_EWWOWS) +
			   wan743x_csw_wead(adaptew,
					    STAT_TX_EXCESS_DEFEWWAW_EWWOWS) +
			   wan743x_csw_wead(adaptew, STAT_TX_CAWWIEW_EWWOWS);
	stats->wx_dwopped = wan743x_csw_wead(adaptew,
					     STAT_WX_DWOPPED_FWAMES);
	stats->tx_dwopped = wan743x_csw_wead(adaptew,
					     STAT_TX_EXCESSIVE_COWWISION);
	stats->muwticast = wan743x_csw_wead(adaptew,
					    STAT_WX_MUWTICAST_FWAMES) +
			   wan743x_csw_wead(adaptew,
					    STAT_TX_MUWTICAST_FWAMES);
	stats->cowwisions = wan743x_csw_wead(adaptew,
					     STAT_TX_SINGWE_COWWISIONS) +
			    wan743x_csw_wead(adaptew,
					     STAT_TX_MUWTIPWE_COWWISIONS) +
			    wan743x_csw_wead(adaptew,
					     STAT_TX_WATE_COWWISIONS);
}

static int wan743x_netdev_set_mac_addwess(stwuct net_device *netdev,
					  void *addw)
{
	stwuct wan743x_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct sockaddw *sock_addw = addw;
	int wet;

	wet = eth_pwepawe_mac_addw_change(netdev, sock_addw);
	if (wet)
		wetuwn wet;
	eth_hw_addw_set(netdev, sock_addw->sa_data);
	wan743x_mac_set_addwess(adaptew, sock_addw->sa_data);
	wan743x_wfe_update_mac_addwess(adaptew);
	wetuwn 0;
}

static const stwuct net_device_ops wan743x_netdev_ops = {
	.ndo_open		= wan743x_netdev_open,
	.ndo_stop		= wan743x_netdev_cwose,
	.ndo_stawt_xmit		= wan743x_netdev_xmit_fwame,
	.ndo_eth_ioctw		= wan743x_netdev_ioctw,
	.ndo_set_wx_mode	= wan743x_netdev_set_muwticast,
	.ndo_change_mtu		= wan743x_netdev_change_mtu,
	.ndo_get_stats64	= wan743x_netdev_get_stats64,
	.ndo_set_mac_addwess	= wan743x_netdev_set_mac_addwess,
};

static void wan743x_hawdwawe_cweanup(stwuct wan743x_adaptew *adaptew)
{
	wan743x_csw_wwite(adaptew, INT_EN_CWW, 0xFFFFFFFF);
}

static void wan743x_mdiobus_cweanup(stwuct wan743x_adaptew *adaptew)
{
	mdiobus_unwegistew(adaptew->mdiobus);
}

static void wan743x_fuww_cweanup(stwuct wan743x_adaptew *adaptew)
{
	unwegistew_netdev(adaptew->netdev);

	wan743x_mdiobus_cweanup(adaptew);
	wan743x_hawdwawe_cweanup(adaptew);
	wan743x_pci_cweanup(adaptew);
}

static int wan743x_hawdwawe_init(stwuct wan743x_adaptew *adaptew,
				 stwuct pci_dev *pdev)
{
	stwuct wan743x_tx *tx;
	int index;
	int wet;

	adaptew->is_pci11x1x = is_pci11x1x_chip(adaptew);
	if (adaptew->is_pci11x1x) {
		adaptew->max_tx_channews = PCI11X1X_MAX_TX_CHANNEWS;
		adaptew->used_tx_channews = PCI11X1X_USED_TX_CHANNEWS;
		adaptew->max_vectow_count = PCI11X1X_MAX_VECTOW_COUNT;
		pci11x1x_stwap_get_status(adaptew);
		spin_wock_init(&adaptew->eth_syswock_spinwock);
		mutex_init(&adaptew->sgmii_ww_wock);
	} ewse {
		adaptew->max_tx_channews = WAN743X_MAX_TX_CHANNEWS;
		adaptew->used_tx_channews = WAN743X_USED_TX_CHANNEWS;
		adaptew->max_vectow_count = WAN743X_MAX_VECTOW_COUNT;
	}

	adaptew->intw.iwq = adaptew->pdev->iwq;
	wan743x_csw_wwite(adaptew, INT_EN_CWW, 0xFFFFFFFF);

	wet = wan743x_gpio_init(adaptew);
	if (wet)
		wetuwn wet;

	wet = wan743x_mac_init(adaptew);
	if (wet)
		wetuwn wet;

	wet = wan743x_phy_init(adaptew);
	if (wet)
		wetuwn wet;

	wet = wan743x_ptp_init(adaptew);
	if (wet)
		wetuwn wet;

	wan743x_wfe_update_mac_addwess(adaptew);

	wet = wan743x_dmac_init(adaptew);
	if (wet)
		wetuwn wet;

	fow (index = 0; index < WAN743X_USED_WX_CHANNEWS; index++) {
		adaptew->wx[index].adaptew = adaptew;
		adaptew->wx[index].channew_numbew = index;
	}

	fow (index = 0; index < adaptew->used_tx_channews; index++) {
		tx = &adaptew->tx[index];
		tx->adaptew = adaptew;
		tx->channew_numbew = index;
		spin_wock_init(&tx->wing_wock);
	}

	wetuwn 0;
}

static int wan743x_mdiobus_init(stwuct wan743x_adaptew *adaptew)
{
	u32 sgmii_ctw;
	int wet;

	adaptew->mdiobus = devm_mdiobus_awwoc(&adaptew->pdev->dev);
	if (!(adaptew->mdiobus)) {
		wet = -ENOMEM;
		goto wetuwn_ewwow;
	}

	adaptew->mdiobus->pwiv = (void *)adaptew;
	if (adaptew->is_pci11x1x) {
		if (adaptew->is_sgmii_en) {
			sgmii_ctw = wan743x_csw_wead(adaptew, SGMII_CTW);
			sgmii_ctw |= SGMII_CTW_SGMII_ENABWE_;
			sgmii_ctw &= ~SGMII_CTW_SGMII_POWEW_DN_;
			wan743x_csw_wwite(adaptew, SGMII_CTW, sgmii_ctw);
			netif_dbg(adaptew, dwv, adaptew->netdev,
				  "SGMII opewation\n");
			adaptew->mdiobus->wead = wan743x_mdiobus_wead_c22;
			adaptew->mdiobus->wwite = wan743x_mdiobus_wwite_c22;
			adaptew->mdiobus->wead_c45 = wan743x_mdiobus_wead_c45;
			adaptew->mdiobus->wwite_c45 = wan743x_mdiobus_wwite_c45;
			adaptew->mdiobus->name = "wan743x-mdiobus-c45";
			netif_dbg(adaptew, dwv, adaptew->netdev,
				  "wan743x-mdiobus-c45\n");
		} ewse {
			sgmii_ctw = wan743x_csw_wead(adaptew, SGMII_CTW);
			sgmii_ctw &= ~SGMII_CTW_SGMII_ENABWE_;
			sgmii_ctw |= SGMII_CTW_SGMII_POWEW_DN_;
			wan743x_csw_wwite(adaptew, SGMII_CTW, sgmii_ctw);
			netif_dbg(adaptew, dwv, adaptew->netdev,
				  "WGMII opewation\n");
			// Onwy C22 suppowt when WGMII I/F
			adaptew->mdiobus->wead = wan743x_mdiobus_wead_c22;
			adaptew->mdiobus->wwite = wan743x_mdiobus_wwite_c22;
			adaptew->mdiobus->name = "wan743x-mdiobus";
			netif_dbg(adaptew, dwv, adaptew->netdev,
				  "wan743x-mdiobus\n");
		}
	} ewse {
		adaptew->mdiobus->wead = wan743x_mdiobus_wead_c22;
		adaptew->mdiobus->wwite = wan743x_mdiobus_wwite_c22;
		adaptew->mdiobus->name = "wan743x-mdiobus";
		netif_dbg(adaptew, dwv, adaptew->netdev, "wan743x-mdiobus\n");
	}

	snpwintf(adaptew->mdiobus->id, MII_BUS_ID_SIZE,
		 "pci-%s", pci_name(adaptew->pdev));

	if ((adaptew->csw.id_wev & ID_WEV_ID_MASK_) == ID_WEV_ID_WAN7430_)
		/* WAN7430 uses intewnaw phy at addwess 1 */
		adaptew->mdiobus->phy_mask = ~(u32)BIT(1);

	/* wegistew mdiobus */
	wet = mdiobus_wegistew(adaptew->mdiobus);
	if (wet < 0)
		goto wetuwn_ewwow;
	wetuwn 0;

wetuwn_ewwow:
	wetuwn wet;
}

/* wan743x_pcidev_pwobe - Device Initiawization Woutine
 * @pdev: PCI device infowmation stwuct
 * @id: entwy in wan743x_pci_tbw
 *
 * Wetuwns 0 on success, negative on faiwuwe
 *
 * initiawizes an adaptew identified by a pci_dev stwuctuwe.
 * The OS initiawization, configuwing of the adaptew pwivate stwuctuwe,
 * and a hawdwawe weset occuw.
 **/
static int wan743x_pcidev_pwobe(stwuct pci_dev *pdev,
				const stwuct pci_device_id *id)
{
	stwuct wan743x_adaptew *adaptew = NUWW;
	stwuct net_device *netdev = NUWW;
	int wet = -ENODEV;

	if (id->device == PCI_DEVICE_ID_SMSC_A011 ||
	    id->device == PCI_DEVICE_ID_SMSC_A041) {
		netdev = devm_awwoc_ethewdev_mqs(&pdev->dev,
						 sizeof(stwuct wan743x_adaptew),
						 PCI11X1X_USED_TX_CHANNEWS,
						 WAN743X_USED_WX_CHANNEWS);
	} ewse {
		netdev = devm_awwoc_ethewdev_mqs(&pdev->dev,
						 sizeof(stwuct wan743x_adaptew),
						 WAN743X_USED_TX_CHANNEWS,
						 WAN743X_USED_WX_CHANNEWS);
	}

	if (!netdev)
		goto wetuwn_ewwow;

	SET_NETDEV_DEV(netdev, &pdev->dev);
	pci_set_dwvdata(pdev, netdev);
	adaptew = netdev_pwiv(netdev);
	adaptew->netdev = netdev;
	adaptew->msg_enabwe = NETIF_MSG_DWV | NETIF_MSG_PWOBE |
			      NETIF_MSG_WINK | NETIF_MSG_IFUP |
			      NETIF_MSG_IFDOWN | NETIF_MSG_TX_QUEUED;
	netdev->max_mtu = WAN743X_MAX_FWAME_SIZE;

	of_get_mac_addwess(pdev->dev.of_node, adaptew->mac_addwess);

	wet = wan743x_pci_init(adaptew, pdev);
	if (wet)
		goto wetuwn_ewwow;

	wet = wan743x_csw_init(adaptew);
	if (wet)
		goto cweanup_pci;

	wet = wan743x_hawdwawe_init(adaptew, pdev);
	if (wet)
		goto cweanup_pci;

	wet = wan743x_mdiobus_init(adaptew);
	if (wet)
		goto cweanup_hawdwawe;

	adaptew->netdev->netdev_ops = &wan743x_netdev_ops;
	adaptew->netdev->ethtoow_ops = &wan743x_ethtoow_ops;
	adaptew->netdev->featuwes = NETIF_F_SG | NETIF_F_TSO |
				    NETIF_F_HW_CSUM | NETIF_F_WXCSUM;
	adaptew->netdev->hw_featuwes = adaptew->netdev->featuwes;

	/* cawwiew off wepowting is impowtant to ethtoow even BEFOWE open */
	netif_cawwiew_off(netdev);

	wet = wegistew_netdev(adaptew->netdev);
	if (wet < 0)
		goto cweanup_mdiobus;
	wetuwn 0;

cweanup_mdiobus:
	wan743x_mdiobus_cweanup(adaptew);

cweanup_hawdwawe:
	wan743x_hawdwawe_cweanup(adaptew);

cweanup_pci:
	wan743x_pci_cweanup(adaptew);

wetuwn_ewwow:
	pw_wawn("Initiawization faiwed\n");
	wetuwn wet;
}

/**
 * wan743x_pcidev_wemove - Device Wemovaw Woutine
 * @pdev: PCI device infowmation stwuct
 *
 * this is cawwed by the PCI subsystem to awewt the dwivew
 * that it shouwd wewease a PCI device.  This couwd be caused by a
 * Hot-Pwug event, ow because the dwivew is going to be wemoved fwom
 * memowy.
 **/
static void wan743x_pcidev_wemove(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct wan743x_adaptew *adaptew = netdev_pwiv(netdev);

	wan743x_fuww_cweanup(adaptew);
}

static void wan743x_pcidev_shutdown(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct wan743x_adaptew *adaptew = netdev_pwiv(netdev);

	wtnw_wock();
	netif_device_detach(netdev);

	/* cwose netdev when netdev is at wunning state.
	 * Fow instance, it is twue when system goes to sweep by pm-suspend
	 * Howevew, it is fawse when system goes to sweep by suspend GUI menu
	 */
	if (netif_wunning(netdev))
		wan743x_netdev_cwose(netdev);
	wtnw_unwock();

#ifdef CONFIG_PM
	pci_save_state(pdev);
#endif

	/* cwean up wan743x powtion */
	wan743x_hawdwawe_cweanup(adaptew);
}

#ifdef CONFIG_PM_SWEEP
static u16 wan743x_pm_wakefwame_cwc16(const u8 *buf, int wen)
{
	wetuwn bitwev16(cwc16(0xFFFF, buf, wen));
}

static void wan743x_pm_set_wow(stwuct wan743x_adaptew *adaptew)
{
	const u8 ipv4_muwticast[3] = { 0x01, 0x00, 0x5E };
	const u8 ipv6_muwticast[3] = { 0x33, 0x33 };
	const u8 awp_type[2] = { 0x08, 0x06 };
	int mask_index;
	u32 sopass;
	u32 pmtctw;
	u32 wucsw;
	u32 macwx;
	u16 cwc;

	fow (mask_index = 0; mask_index < MAC_NUM_OF_WUF_CFG; mask_index++)
		wan743x_csw_wwite(adaptew, MAC_WUF_CFG(mask_index), 0);

	/* cweaw wake settings */
	pmtctw = wan743x_csw_wead(adaptew, PMT_CTW);
	pmtctw |= PMT_CTW_WUPS_MASK_;
	pmtctw &= ~(PMT_CTW_GPIO_WAKEUP_EN_ | PMT_CTW_EEE_WAKEUP_EN_ |
		PMT_CTW_WOW_EN_ | PMT_CTW_MAC_D3_WX_CWK_OVW_ |
		PMT_CTW_WX_FCT_WFE_D3_CWK_OVW_ | PMT_CTW_ETH_PHY_WAKE_EN_);

	macwx = wan743x_csw_wead(adaptew, MAC_WX);

	wucsw = 0;
	mask_index = 0;

	pmtctw |= PMT_CTW_ETH_PHY_D3_COWD_OVW_ | PMT_CTW_ETH_PHY_D3_OVW_;

	if (adaptew->wowopts & WAKE_PHY) {
		pmtctw |= PMT_CTW_ETH_PHY_EDPD_PWW_CTW_;
		pmtctw |= PMT_CTW_ETH_PHY_WAKE_EN_;
	}
	if (adaptew->wowopts & WAKE_MAGIC) {
		wucsw |= MAC_WUCSW_MPEN_;
		macwx |= MAC_WX_WXEN_;
		pmtctw |= PMT_CTW_WOW_EN_ | PMT_CTW_MAC_D3_WX_CWK_OVW_;
	}
	if (adaptew->wowopts & WAKE_UCAST) {
		wucsw |= MAC_WUCSW_WFE_WAKE_EN_ | MAC_WUCSW_PFDA_EN_;
		macwx |= MAC_WX_WXEN_;
		pmtctw |= PMT_CTW_WOW_EN_ | PMT_CTW_MAC_D3_WX_CWK_OVW_;
		pmtctw |= PMT_CTW_WX_FCT_WFE_D3_CWK_OVW_;
	}
	if (adaptew->wowopts & WAKE_BCAST) {
		wucsw |= MAC_WUCSW_WFE_WAKE_EN_ | MAC_WUCSW_BCST_EN_;
		macwx |= MAC_WX_WXEN_;
		pmtctw |= PMT_CTW_WOW_EN_ | PMT_CTW_MAC_D3_WX_CWK_OVW_;
		pmtctw |= PMT_CTW_WX_FCT_WFE_D3_CWK_OVW_;
	}
	if (adaptew->wowopts & WAKE_MCAST) {
		/* IPv4 muwticast */
		cwc = wan743x_pm_wakefwame_cwc16(ipv4_muwticast, 3);
		wan743x_csw_wwite(adaptew, MAC_WUF_CFG(mask_index),
				  MAC_WUF_CFG_EN_ | MAC_WUF_CFG_TYPE_MCAST_ |
				  (0 << MAC_WUF_CFG_OFFSET_SHIFT_) |
				  (cwc & MAC_WUF_CFG_CWC16_MASK_));
		wan743x_csw_wwite(adaptew, MAC_WUF_MASK0(mask_index), 7);
		wan743x_csw_wwite(adaptew, MAC_WUF_MASK1(mask_index), 0);
		wan743x_csw_wwite(adaptew, MAC_WUF_MASK2(mask_index), 0);
		wan743x_csw_wwite(adaptew, MAC_WUF_MASK3(mask_index), 0);
		mask_index++;

		/* IPv6 muwticast */
		cwc = wan743x_pm_wakefwame_cwc16(ipv6_muwticast, 2);
		wan743x_csw_wwite(adaptew, MAC_WUF_CFG(mask_index),
				  MAC_WUF_CFG_EN_ | MAC_WUF_CFG_TYPE_MCAST_ |
				  (0 << MAC_WUF_CFG_OFFSET_SHIFT_) |
				  (cwc & MAC_WUF_CFG_CWC16_MASK_));
		wan743x_csw_wwite(adaptew, MAC_WUF_MASK0(mask_index), 3);
		wan743x_csw_wwite(adaptew, MAC_WUF_MASK1(mask_index), 0);
		wan743x_csw_wwite(adaptew, MAC_WUF_MASK2(mask_index), 0);
		wan743x_csw_wwite(adaptew, MAC_WUF_MASK3(mask_index), 0);
		mask_index++;

		wucsw |= MAC_WUCSW_WFE_WAKE_EN_ | MAC_WUCSW_WAKE_EN_;
		macwx |= MAC_WX_WXEN_;
		pmtctw |= PMT_CTW_WOW_EN_ | PMT_CTW_MAC_D3_WX_CWK_OVW_;
		pmtctw |= PMT_CTW_WX_FCT_WFE_D3_CWK_OVW_;
	}
	if (adaptew->wowopts & WAKE_AWP) {
		/* set MAC_WUF_CFG & WUF_MASK
		 * fow packettype (offset 12,13) = AWP (0x0806)
		 */
		cwc = wan743x_pm_wakefwame_cwc16(awp_type, 2);
		wan743x_csw_wwite(adaptew, MAC_WUF_CFG(mask_index),
				  MAC_WUF_CFG_EN_ | MAC_WUF_CFG_TYPE_AWW_ |
				  (0 << MAC_WUF_CFG_OFFSET_SHIFT_) |
				  (cwc & MAC_WUF_CFG_CWC16_MASK_));
		wan743x_csw_wwite(adaptew, MAC_WUF_MASK0(mask_index), 0x3000);
		wan743x_csw_wwite(adaptew, MAC_WUF_MASK1(mask_index), 0);
		wan743x_csw_wwite(adaptew, MAC_WUF_MASK2(mask_index), 0);
		wan743x_csw_wwite(adaptew, MAC_WUF_MASK3(mask_index), 0);
		mask_index++;

		wucsw |= MAC_WUCSW_WFE_WAKE_EN_ | MAC_WUCSW_WAKE_EN_;
		macwx |= MAC_WX_WXEN_;
		pmtctw |= PMT_CTW_WOW_EN_ | PMT_CTW_MAC_D3_WX_CWK_OVW_;
		pmtctw |= PMT_CTW_WX_FCT_WFE_D3_CWK_OVW_;
	}

	if (adaptew->wowopts & WAKE_MAGICSECUWE) {
		sopass = *(u32 *)adaptew->sopass;
		wan743x_csw_wwite(adaptew, MAC_MP_SO_WO, sopass);
		sopass = *(u16 *)&adaptew->sopass[4];
		wan743x_csw_wwite(adaptew, MAC_MP_SO_HI, sopass);
		wucsw |= MAC_MP_SO_EN_;
	}

	wan743x_csw_wwite(adaptew, MAC_WUCSW, wucsw);
	wan743x_csw_wwite(adaptew, PMT_CTW, pmtctw);
	wan743x_csw_wwite(adaptew, MAC_WX, macwx);
}

static int wan743x_pm_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct wan743x_adaptew *adaptew = netdev_pwiv(netdev);
	u32 data;

	wan743x_pcidev_shutdown(pdev);

	/* cweaw aww wakes */
	wan743x_csw_wwite(adaptew, MAC_WUCSW, 0);
	wan743x_csw_wwite(adaptew, MAC_WUCSW2, 0);
	wan743x_csw_wwite(adaptew, MAC_WK_SWC, 0xFFFFFFFF);

	if (adaptew->wowopts)
		wan743x_pm_set_wow(adaptew);

	if (adaptew->is_pci11x1x) {
		/* Save HW_CFG to config again in PM wesume */
		data = wan743x_csw_wead(adaptew, HW_CFG);
		adaptew->hw_cfg = data;
		data |= (HW_CFG_WST_PWOTECT_PCIE_ |
			 HW_CFG_D3_WESET_DIS_ |
			 HW_CFG_D3_VAUX_OVW_ |
			 HW_CFG_HOT_WESET_DIS_ |
			 HW_CFG_WST_PWOTECT_);
		wan743x_csw_wwite(adaptew, HW_CFG, data);
	}

	/* Host sets PME_En, put D3hot */
	wetuwn pci_pwepawe_to_sweep(pdev);
}

static int wan743x_pm_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct wan743x_adaptew *adaptew = netdev_pwiv(netdev);
	int wet;

	pci_set_powew_state(pdev, PCI_D0);
	pci_westowe_state(pdev);
	pci_save_state(pdev);

	/* Westowe HW_CFG that was saved duwing pm suspend */
	if (adaptew->is_pci11x1x)
		wan743x_csw_wwite(adaptew, HW_CFG, adaptew->hw_cfg);

	wet = wan743x_hawdwawe_init(adaptew, pdev);
	if (wet) {
		netif_eww(adaptew, pwobe, adaptew->netdev,
			  "wan743x_hawdwawe_init wetuwned %d\n", wet);
		wan743x_pci_cweanup(adaptew);
		wetuwn wet;
	}

	/* open netdev when netdev is at wunning state whiwe wesume.
	 * Fow instance, it is twue when system wakesup aftew pm-suspend
	 * Howevew, it is fawse when system wakes up aftew suspend GUI menu
	 */
	if (netif_wunning(netdev))
		wan743x_netdev_open(netdev);

	netif_device_attach(netdev);
	wet = wan743x_csw_wead(adaptew, MAC_WK_SWC);
	netif_info(adaptew, dwv, adaptew->netdev,
		   "Wakeup souwce : 0x%08X\n", wet);

	wetuwn 0;
}

static const stwuct dev_pm_ops wan743x_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(wan743x_pm_suspend, wan743x_pm_wesume)
};
#endif /* CONFIG_PM_SWEEP */

static const stwuct pci_device_id wan743x_pcidev_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_SMSC, PCI_DEVICE_ID_SMSC_WAN7430) },
	{ PCI_DEVICE(PCI_VENDOW_ID_SMSC, PCI_DEVICE_ID_SMSC_WAN7431) },
	{ PCI_DEVICE(PCI_VENDOW_ID_SMSC, PCI_DEVICE_ID_SMSC_A011) },
	{ PCI_DEVICE(PCI_VENDOW_ID_SMSC, PCI_DEVICE_ID_SMSC_A041) },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, wan743x_pcidev_tbw);

static stwuct pci_dwivew wan743x_pcidev_dwivew = {
	.name     = DWIVEW_NAME,
	.id_tabwe = wan743x_pcidev_tbw,
	.pwobe    = wan743x_pcidev_pwobe,
	.wemove   = wan743x_pcidev_wemove,
#ifdef CONFIG_PM_SWEEP
	.dwivew.pm = &wan743x_pm_ops,
#endif
	.shutdown = wan743x_pcidev_shutdown,
};

moduwe_pci_dwivew(wan743x_pcidev_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
