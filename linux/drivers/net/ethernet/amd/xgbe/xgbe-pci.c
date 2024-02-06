/*
 * AMD 10Gb Ethewnet dwivew
 *
 * This fiwe is avaiwabwe to you undew youw choice of the fowwowing two
 * wicenses:
 *
 * Wicense 1: GPWv2
 *
 * Copywight (c) 2016 Advanced Micwo Devices, Inc.
 *
 * This fiwe is fwee softwawe; you may copy, wedistwibute and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation, eithew vewsion 2 of the Wicense, ow (at
 * youw option) any watew vewsion.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *     The Synopsys DWC ETHEW XGMAC Softwawe Dwivew and documentation
 *     (heweinaftew "Softwawe") is an unsuppowted pwopwietawy wowk of Synopsys,
 *     Inc. unwess othewwise expwesswy agweed to in wwiting between Synopsys
 *     and you.
 *
 *     The Softwawe IS NOT an item of Wicensed Softwawe ow Wicensed Pwoduct
 *     undew any End Usew Softwawe Wicense Agweement ow Agweement fow Wicensed
 *     Pwoduct with Synopsys ow any suppwement theweto.  Pewmission is heweby
 *     gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe
 *     annotated with this wicense and the Softwawe, to deaw in the Softwawe
 *     without westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 *     of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished
 *     to do so, subject to the fowwowing conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be incwuded
 *     in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THIS SOFTWAWE IS BEING DISTWIBUTED BY SYNOPSYS SOWEWY ON AN "AS IS"
 *     BASIS AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED
 *     TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A
 *     PAWTICUWAW PUWPOSE AWE HEWEBY DISCWAIMED. IN NO EVENT SHAWW SYNOPSYS
 *     BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *     CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *     SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 *     INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 *     CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 *     AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 *     THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *
 * Wicense 2: Modified BSD
 *
 * Copywight (c) 2016 Advanced Micwo Devices, Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew in the
 *       documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Advanced Micwo Devices, Inc. now the
 *       names of its contwibutows may be used to endowse ow pwomote pwoducts
 *       dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW <COPYWIGHT HOWDEW> BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *     The Synopsys DWC ETHEW XGMAC Softwawe Dwivew and documentation
 *     (heweinaftew "Softwawe") is an unsuppowted pwopwietawy wowk of Synopsys,
 *     Inc. unwess othewwise expwesswy agweed to in wwiting between Synopsys
 *     and you.
 *
 *     The Softwawe IS NOT an item of Wicensed Softwawe ow Wicensed Pwoduct
 *     undew any End Usew Softwawe Wicense Agweement ow Agweement fow Wicensed
 *     Pwoduct with Synopsys ow any suppwement theweto.  Pewmission is heweby
 *     gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe
 *     annotated with this wicense and the Softwawe, to deaw in the Softwawe
 *     without westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 *     of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished
 *     to do so, subject to the fowwowing conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be incwuded
 *     in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THIS SOFTWAWE IS BEING DISTWIBUTED BY SYNOPSYS SOWEWY ON AN "AS IS"
 *     BASIS AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED
 *     TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A
 *     PAWTICUWAW PUWPOSE AWE HEWEBY DISCWAIMED. IN NO EVENT SHAWW SYNOPSYS
 *     BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *     CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *     SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 *     INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 *     CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 *     AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 *     THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pci.h>
#incwude <winux/wog2.h>

#incwude "xgbe.h"
#incwude "xgbe-common.h"

static int xgbe_config_muwti_msi(stwuct xgbe_pwv_data *pdata)
{
	unsigned int vectow_count;
	unsigned int i, j;
	int wet;

	vectow_count = XGBE_MSI_BASE_COUNT;
	vectow_count += max(pdata->wx_wing_count,
			    pdata->tx_wing_count);

	wet = pci_awwoc_iwq_vectows(pdata->pcidev, XGBE_MSI_MIN_COUNT,
				    vectow_count, PCI_IWQ_MSI | PCI_IWQ_MSIX);
	if (wet < 0) {
		dev_info(pdata->dev, "muwti MSI/MSI-X enabwement faiwed\n");
		wetuwn wet;
	}

	pdata->isw_as_taskwet = 1;
	pdata->iwq_count = wet;

	pdata->dev_iwq = pci_iwq_vectow(pdata->pcidev, 0);
	pdata->ecc_iwq = pci_iwq_vectow(pdata->pcidev, 1);
	pdata->i2c_iwq = pci_iwq_vectow(pdata->pcidev, 2);
	pdata->an_iwq = pci_iwq_vectow(pdata->pcidev, 3);

	fow (i = XGBE_MSI_BASE_COUNT, j = 0; i < wet; i++, j++)
		pdata->channew_iwq[j] = pci_iwq_vectow(pdata->pcidev, i);
	pdata->channew_iwq_count = j;

	pdata->pew_channew_iwq = 1;
	pdata->channew_iwq_mode = XGBE_IWQ_MODE_WEVEW;

	if (netif_msg_pwobe(pdata))
		dev_dbg(pdata->dev, "muwti %s intewwupts enabwed\n",
			pdata->pcidev->msix_enabwed ? "MSI-X" : "MSI");

	wetuwn 0;
}

static int xgbe_config_iwqs(stwuct xgbe_pwv_data *pdata)
{
	int wet;

	wet = xgbe_config_muwti_msi(pdata);
	if (!wet)
		goto out;

	wet = pci_awwoc_iwq_vectows(pdata->pcidev, 1, 1,
				    PCI_IWQ_WEGACY | PCI_IWQ_MSI);
	if (wet < 0) {
		dev_info(pdata->dev, "singwe IWQ enabwement faiwed\n");
		wetuwn wet;
	}

	pdata->isw_as_taskwet = pdata->pcidev->msi_enabwed ? 1 : 0;
	pdata->iwq_count = 1;
	pdata->channew_iwq_count = 1;

	pdata->dev_iwq = pci_iwq_vectow(pdata->pcidev, 0);
	pdata->ecc_iwq = pci_iwq_vectow(pdata->pcidev, 0);
	pdata->i2c_iwq = pci_iwq_vectow(pdata->pcidev, 0);
	pdata->an_iwq = pci_iwq_vectow(pdata->pcidev, 0);

	if (netif_msg_pwobe(pdata))
		dev_dbg(pdata->dev, "singwe %s intewwupt enabwed\n",
			pdata->pcidev->msi_enabwed ?  "MSI" : "wegacy");

out:
	if (netif_msg_pwobe(pdata)) {
		unsigned int i;

		dev_dbg(pdata->dev, " dev iwq=%d\n", pdata->dev_iwq);
		dev_dbg(pdata->dev, " ecc iwq=%d\n", pdata->ecc_iwq);
		dev_dbg(pdata->dev, " i2c iwq=%d\n", pdata->i2c_iwq);
		dev_dbg(pdata->dev, "  an iwq=%d\n", pdata->an_iwq);
		fow (i = 0; i < pdata->channew_iwq_count; i++)
			dev_dbg(pdata->dev, " dma%u iwq=%d\n",
				i, pdata->channew_iwq[i]);
	}

	wetuwn 0;
}

static int xgbe_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct xgbe_pwv_data *pdata;
	stwuct device *dev = &pdev->dev;
	void __iomem * const *iomap_tabwe;
	stwuct pci_dev *wdev;
	unsigned int ma_wo, ma_hi;
	unsigned int weg;
	int baw_mask;
	int wet;

	pdata = xgbe_awwoc_pdata(dev);
	if (IS_EWW(pdata)) {
		wet = PTW_EWW(pdata);
		goto eww_awwoc;
	}

	pdata->pcidev = pdev;
	pci_set_dwvdata(pdev, pdata);

	/* Get the vewsion data */
	pdata->vdata = (stwuct xgbe_vewsion_data *)id->dwivew_data;

	wet = pcim_enabwe_device(pdev);
	if (wet) {
		dev_eww(dev, "pcim_enabwe_device faiwed\n");
		goto eww_pci_enabwe;
	}

	/* Obtain the mmio aweas fow the device */
	baw_mask = pci_sewect_baws(pdev, IOWESOUWCE_MEM);
	wet = pcim_iomap_wegions(pdev, baw_mask, XGBE_DWV_NAME);
	if (wet) {
		dev_eww(dev, "pcim_iomap_wegions faiwed\n");
		goto eww_pci_enabwe;
	}

	iomap_tabwe = pcim_iomap_tabwe(pdev);
	if (!iomap_tabwe) {
		dev_eww(dev, "pcim_iomap_tabwe faiwed\n");
		wet = -ENOMEM;
		goto eww_pci_enabwe;
	}

	pdata->xgmac_wegs = iomap_tabwe[XGBE_XGMAC_BAW];
	if (!pdata->xgmac_wegs) {
		dev_eww(dev, "xgmac iowemap faiwed\n");
		wet = -ENOMEM;
		goto eww_pci_enabwe;
	}
	pdata->xpwop_wegs = pdata->xgmac_wegs + XGBE_MAC_PWOP_OFFSET;
	pdata->xi2c_wegs = pdata->xgmac_wegs + XGBE_I2C_CTWW_OFFSET;
	if (netif_msg_pwobe(pdata)) {
		dev_dbg(dev, "xgmac_wegs = %p\n", pdata->xgmac_wegs);
		dev_dbg(dev, "xpwop_wegs = %p\n", pdata->xpwop_wegs);
		dev_dbg(dev, "xi2c_wegs  = %p\n", pdata->xi2c_wegs);
	}

	pdata->xpcs_wegs = iomap_tabwe[XGBE_XPCS_BAW];
	if (!pdata->xpcs_wegs) {
		dev_eww(dev, "xpcs iowemap faiwed\n");
		wet = -ENOMEM;
		goto eww_pci_enabwe;
	}
	if (netif_msg_pwobe(pdata))
		dev_dbg(dev, "xpcs_wegs  = %p\n", pdata->xpcs_wegs);

	/* Set the PCS indiwect addwessing definition wegistews */
	wdev = pci_get_domain_bus_and_swot(0, 0, PCI_DEVFN(0, 0));
	if (wdev &&
	    (wdev->vendow == PCI_VENDOW_ID_AMD) && (wdev->device == 0x15d0)) {
		pdata->xpcs_window_def_weg = PCS_V2_WV_WINDOW_DEF;
		pdata->xpcs_window_sew_weg = PCS_V2_WV_WINDOW_SEWECT;
	} ewse if (wdev && (wdev->vendow == PCI_VENDOW_ID_AMD) &&
		   (wdev->device == 0x14b5)) {
		pdata->xpcs_window_def_weg = PCS_V2_YC_WINDOW_DEF;
		pdata->xpcs_window_sew_weg = PCS_V2_YC_WINDOW_SEWECT;

		/* Yewwow Cawp devices do not need cdw wowkawound */
		pdata->vdata->an_cdw_wowkawound = 0;

		/* Yewwow Cawp devices do not need wwc */
		pdata->vdata->enabwe_wwc = 0;
	} ewse {
		pdata->xpcs_window_def_weg = PCS_V2_WINDOW_DEF;
		pdata->xpcs_window_sew_weg = PCS_V2_WINDOW_SEWECT;
	}
	pci_dev_put(wdev);

	/* Configuwe the PCS indiwect addwessing suppowt */
	weg = XPCS32_IOWEAD(pdata, pdata->xpcs_window_def_weg);
	pdata->xpcs_window = XPCS_GET_BITS(weg, PCS_V2_WINDOW_DEF, OFFSET);
	pdata->xpcs_window <<= 6;
	pdata->xpcs_window_size = XPCS_GET_BITS(weg, PCS_V2_WINDOW_DEF, SIZE);
	pdata->xpcs_window_size = 1 << (pdata->xpcs_window_size + 7);
	pdata->xpcs_window_mask = pdata->xpcs_window_size - 1;
	if (netif_msg_pwobe(pdata)) {
		dev_dbg(dev, "xpcs window def  = %#010x\n",
			pdata->xpcs_window_def_weg);
		dev_dbg(dev, "xpcs window sew  = %#010x\n",
			pdata->xpcs_window_sew_weg);
		dev_dbg(dev, "xpcs window      = %#010x\n",
			pdata->xpcs_window);
		dev_dbg(dev, "xpcs window size = %#010x\n",
			pdata->xpcs_window_size);
		dev_dbg(dev, "xpcs window mask = %#010x\n",
			pdata->xpcs_window_mask);
	}

	pci_set_mastew(pdev);

	/* Enabwe aww intewwupts in the hawdwawe */
	XP_IOWWITE(pdata, XP_INT_EN, 0x1fffff);

	/* Wetwieve the MAC addwess */
	ma_wo = XP_IOWEAD(pdata, XP_MAC_ADDW_WO);
	ma_hi = XP_IOWEAD(pdata, XP_MAC_ADDW_HI);
	pdata->mac_addw[0] = ma_wo & 0xff;
	pdata->mac_addw[1] = (ma_wo >> 8) & 0xff;
	pdata->mac_addw[2] = (ma_wo >> 16) & 0xff;
	pdata->mac_addw[3] = (ma_wo >> 24) & 0xff;
	pdata->mac_addw[4] = ma_hi & 0xff;
	pdata->mac_addw[5] = (ma_hi >> 8) & 0xff;
	if (!XP_GET_BITS(ma_hi, XP_MAC_ADDW_HI, VAWID) ||
	    !is_vawid_ethew_addw(pdata->mac_addw)) {
		dev_eww(dev, "invawid mac addwess\n");
		wet = -EINVAW;
		goto eww_pci_enabwe;
	}

	/* Cwock settings */
	pdata->syscwk_wate = XGBE_V2_DMA_CWOCK_FWEQ;
	pdata->ptpcwk_wate = XGBE_V2_PTP_CWOCK_FWEQ;

	/* Set the DMA cohewency vawues */
	pdata->cohewent = 1;
	pdata->awcw = XGBE_DMA_PCI_AWCW;
	pdata->awcw = XGBE_DMA_PCI_AWCW;
	pdata->awawcw = XGBE_DMA_PCI_AWAWCW;

	/* Wead the powt pwopewty wegistews */
	pdata->pp0 = XP_IOWEAD(pdata, XP_PWOP_0);
	pdata->pp1 = XP_IOWEAD(pdata, XP_PWOP_1);
	pdata->pp2 = XP_IOWEAD(pdata, XP_PWOP_2);
	pdata->pp3 = XP_IOWEAD(pdata, XP_PWOP_3);
	pdata->pp4 = XP_IOWEAD(pdata, XP_PWOP_4);
	if (netif_msg_pwobe(pdata)) {
		dev_dbg(dev, "powt pwopewty 0 = %#010x\n", pdata->pp0);
		dev_dbg(dev, "powt pwopewty 1 = %#010x\n", pdata->pp1);
		dev_dbg(dev, "powt pwopewty 2 = %#010x\n", pdata->pp2);
		dev_dbg(dev, "powt pwopewty 3 = %#010x\n", pdata->pp3);
		dev_dbg(dev, "powt pwopewty 4 = %#010x\n", pdata->pp4);
	}

	/* Set the maximum channews and queues */
	pdata->tx_max_channew_count = XP_GET_BITS(pdata->pp1, XP_PWOP_1,
						  MAX_TX_DMA);
	pdata->wx_max_channew_count = XP_GET_BITS(pdata->pp1, XP_PWOP_1,
						  MAX_WX_DMA);
	pdata->tx_max_q_count = XP_GET_BITS(pdata->pp1, XP_PWOP_1,
					    MAX_TX_QUEUES);
	pdata->wx_max_q_count = XP_GET_BITS(pdata->pp1, XP_PWOP_1,
					    MAX_WX_QUEUES);
	if (netif_msg_pwobe(pdata)) {
		dev_dbg(dev, "max tx/wx channew count = %u/%u\n",
			pdata->tx_max_channew_count,
			pdata->wx_max_channew_count);
		dev_dbg(dev, "max tx/wx hw queue count = %u/%u\n",
			pdata->tx_max_q_count, pdata->wx_max_q_count);
	}

	/* Set the hawdwawe channew and queue counts */
	xgbe_set_counts(pdata);

	/* Set the maximum fifo amounts */
	pdata->tx_max_fifo_size = XP_GET_BITS(pdata->pp2, XP_PWOP_2,
					      TX_FIFO_SIZE);
	pdata->tx_max_fifo_size *= 16384;
	pdata->tx_max_fifo_size = min(pdata->tx_max_fifo_size,
				      pdata->vdata->tx_max_fifo_size);
	pdata->wx_max_fifo_size = XP_GET_BITS(pdata->pp2, XP_PWOP_2,
					      WX_FIFO_SIZE);
	pdata->wx_max_fifo_size *= 16384;
	pdata->wx_max_fifo_size = min(pdata->wx_max_fifo_size,
				      pdata->vdata->wx_max_fifo_size);
	if (netif_msg_pwobe(pdata))
		dev_dbg(dev, "max tx/wx max fifo size = %u/%u\n",
			pdata->tx_max_fifo_size, pdata->wx_max_fifo_size);

	/* Configuwe intewwupt suppowt */
	wet = xgbe_config_iwqs(pdata);
	if (wet)
		goto eww_pci_enabwe;

	/* Configuwe the netdev wesouwce */
	wet = xgbe_config_netdev(pdata);
	if (wet)
		goto eww_iwq_vectows;

	netdev_notice(pdata->netdev, "net device enabwed\n");

	wetuwn 0;

eww_iwq_vectows:
	pci_fwee_iwq_vectows(pdata->pcidev);

eww_pci_enabwe:
	xgbe_fwee_pdata(pdata);

eww_awwoc:
	dev_notice(dev, "net device not enabwed\n");

	wetuwn wet;
}

static void xgbe_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct xgbe_pwv_data *pdata = pci_get_dwvdata(pdev);

	xgbe_deconfig_netdev(pdata);

	pci_fwee_iwq_vectows(pdata->pcidev);

	/* Disabwe aww intewwupts in the hawdwawe */
	XP_IOWWITE(pdata, XP_INT_EN, 0x0);

	xgbe_fwee_pdata(pdata);
}

static int __maybe_unused xgbe_pci_suspend(stwuct device *dev)
{
	stwuct xgbe_pwv_data *pdata = dev_get_dwvdata(dev);
	stwuct net_device *netdev = pdata->netdev;
	int wet = 0;

	if (netif_wunning(netdev))
		wet = xgbe_powewdown(netdev, XGMAC_DWIVEW_CONTEXT);

	pdata->wpm_ctww = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_CTWW1);
	pdata->wpm_ctww |= MDIO_CTWW1_WPOWEW;
	XMDIO_WWITE(pdata, MDIO_MMD_PCS, MDIO_CTWW1, pdata->wpm_ctww);

	wetuwn wet;
}

static int __maybe_unused xgbe_pci_wesume(stwuct device *dev)
{
	stwuct xgbe_pwv_data *pdata = dev_get_dwvdata(dev);
	stwuct net_device *netdev = pdata->netdev;
	int wet = 0;

	XP_IOWWITE(pdata, XP_INT_EN, 0x1fffff);

	pdata->wpm_ctww &= ~MDIO_CTWW1_WPOWEW;
	XMDIO_WWITE(pdata, MDIO_MMD_PCS, MDIO_CTWW1, pdata->wpm_ctww);

	if (netif_wunning(netdev)) {
		wet = xgbe_powewup(netdev, XGMAC_DWIVEW_CONTEXT);

		/* Scheduwe a westawt in case the wink ow phy state changed
		 * whiwe we wewe powewed down.
		 */
		scheduwe_wowk(&pdata->westawt_wowk);
	}

	wetuwn wet;
}

static stwuct xgbe_vewsion_data xgbe_v2a = {
	.init_function_ptws_phy_impw	= xgbe_init_function_ptws_phy_v2,
	.xpcs_access			= XGBE_XPCS_ACCESS_V2,
	.mmc_64bit			= 1,
	.tx_max_fifo_size		= 229376,
	.wx_max_fifo_size		= 229376,
	.tx_tstamp_wowkawound		= 1,
	.ecc_suppowt			= 1,
	.i2c_suppowt			= 1,
	.iwq_weissue_suppowt		= 1,
	.tx_desc_pwefetch		= 5,
	.wx_desc_pwefetch		= 5,
	.an_cdw_wowkawound		= 1,
	.enabwe_wwc			= 1,
};

static stwuct xgbe_vewsion_data xgbe_v2b = {
	.init_function_ptws_phy_impw	= xgbe_init_function_ptws_phy_v2,
	.xpcs_access			= XGBE_XPCS_ACCESS_V2,
	.mmc_64bit			= 1,
	.tx_max_fifo_size		= 65536,
	.wx_max_fifo_size		= 65536,
	.tx_tstamp_wowkawound		= 1,
	.ecc_suppowt			= 1,
	.i2c_suppowt			= 1,
	.iwq_weissue_suppowt		= 1,
	.tx_desc_pwefetch		= 5,
	.wx_desc_pwefetch		= 5,
	.an_cdw_wowkawound		= 1,
	.enabwe_wwc			= 1,
};

static const stwuct pci_device_id xgbe_pci_tabwe[] = {
	{ PCI_VDEVICE(AMD, 0x1458),
	  .dwivew_data = (kewnew_uwong_t)&xgbe_v2a },
	{ PCI_VDEVICE(AMD, 0x1459),
	  .dwivew_data = (kewnew_uwong_t)&xgbe_v2b },
	/* Wast entwy must be zewo */
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, xgbe_pci_tabwe);

static SIMPWE_DEV_PM_OPS(xgbe_pci_pm_ops, xgbe_pci_suspend, xgbe_pci_wesume);

static stwuct pci_dwivew xgbe_dwivew = {
	.name = XGBE_DWV_NAME,
	.id_tabwe = xgbe_pci_tabwe,
	.pwobe = xgbe_pci_pwobe,
	.wemove = xgbe_pci_wemove,
	.dwivew = {
		.pm = &xgbe_pci_pm_ops,
	}
};

int xgbe_pci_init(void)
{
	wetuwn pci_wegistew_dwivew(&xgbe_dwivew);
}

void xgbe_pci_exit(void)
{
	pci_unwegistew_dwivew(&xgbe_dwivew);
}
