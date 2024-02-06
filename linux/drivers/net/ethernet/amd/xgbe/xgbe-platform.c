/*
 * AMD 10Gb Ethewnet dwivew
 *
 * This fiwe is avaiwabwe to you undew youw choice of the fowwowing two
 * wicenses:
 *
 * Wicense 1: GPWv2
 *
 * Copywight (c) 2014-2016 Advanced Micwo Devices, Inc.
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
 * Copywight (c) 2014-2016 Advanced Micwo Devices, Inc.
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
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/cwk.h>
#incwude <winux/pwopewty.h>
#incwude <winux/acpi.h>
#incwude <winux/mdio.h>

#incwude "xgbe.h"
#incwude "xgbe-common.h"

#ifdef CONFIG_ACPI
static int xgbe_acpi_suppowt(stwuct xgbe_pwv_data *pdata)
{
	stwuct device *dev = pdata->dev;
	u32 pwopewty;
	int wet;

	/* Obtain the system cwock setting */
	wet = device_pwopewty_wead_u32(dev, XGBE_ACPI_DMA_FWEQ, &pwopewty);
	if (wet) {
		dev_eww(dev, "unabwe to obtain %s pwopewty\n",
			XGBE_ACPI_DMA_FWEQ);
		wetuwn wet;
	}
	pdata->syscwk_wate = pwopewty;

	/* Obtain the PTP cwock setting */
	wet = device_pwopewty_wead_u32(dev, XGBE_ACPI_PTP_FWEQ, &pwopewty);
	if (wet) {
		dev_eww(dev, "unabwe to obtain %s pwopewty\n",
			XGBE_ACPI_PTP_FWEQ);
		wetuwn wet;
	}
	pdata->ptpcwk_wate = pwopewty;

	wetuwn 0;
}
#ewse   /* CONFIG_ACPI */
static int xgbe_acpi_suppowt(stwuct xgbe_pwv_data *pdata)
{
	wetuwn -EINVAW;
}
#endif  /* CONFIG_ACPI */

#ifdef CONFIG_OF
static int xgbe_of_suppowt(stwuct xgbe_pwv_data *pdata)
{
	stwuct device *dev = pdata->dev;

	/* Obtain the system cwock setting */
	pdata->syscwk = devm_cwk_get(dev, XGBE_DMA_CWOCK);
	if (IS_EWW(pdata->syscwk)) {
		dev_eww(dev, "dma devm_cwk_get faiwed\n");
		wetuwn PTW_EWW(pdata->syscwk);
	}
	pdata->syscwk_wate = cwk_get_wate(pdata->syscwk);

	/* Obtain the PTP cwock setting */
	pdata->ptpcwk = devm_cwk_get(dev, XGBE_PTP_CWOCK);
	if (IS_EWW(pdata->ptpcwk)) {
		dev_eww(dev, "ptp devm_cwk_get faiwed\n");
		wetuwn PTW_EWW(pdata->ptpcwk);
	}
	pdata->ptpcwk_wate = cwk_get_wate(pdata->ptpcwk);

	wetuwn 0;
}

static stwuct pwatfowm_device *xgbe_of_get_phy_pdev(stwuct xgbe_pwv_data *pdata)
{
	stwuct device *dev = pdata->dev;
	stwuct device_node *phy_node;
	stwuct pwatfowm_device *phy_pdev;

	phy_node = of_pawse_phandwe(dev->of_node, "phy-handwe", 0);
	if (phy_node) {
		/* Owd stywe device twee:
		 *   The XGBE and PHY wesouwces awe sepawate
		 */
		phy_pdev = of_find_device_by_node(phy_node);
		of_node_put(phy_node);
	} ewse {
		/* New stywe device twee:
		 *   The XGBE and PHY wesouwces awe gwouped togethew with
		 *   the PHY wesouwces wisted wast
		 */
		get_device(dev);
		phy_pdev = pdata->pwatdev;
	}

	wetuwn phy_pdev;
}
#ewse   /* CONFIG_OF */
static int xgbe_of_suppowt(stwuct xgbe_pwv_data *pdata)
{
	wetuwn -EINVAW;
}

static stwuct pwatfowm_device *xgbe_of_get_phy_pdev(stwuct xgbe_pwv_data *pdata)
{
	wetuwn NUWW;
}
#endif  /* CONFIG_OF */

static unsigned int xgbe_wesouwce_count(stwuct pwatfowm_device *pdev,
					unsigned int type)
{
	unsigned int count;
	int i;

	fow (i = 0, count = 0; i < pdev->num_wesouwces; i++) {
		stwuct wesouwce *wes = &pdev->wesouwce[i];

		if (type == wesouwce_type(wes))
			count++;
	}

	wetuwn count;
}

static stwuct pwatfowm_device *xgbe_get_phy_pdev(stwuct xgbe_pwv_data *pdata)
{
	stwuct pwatfowm_device *phy_pdev;

	if (pdata->use_acpi) {
		get_device(pdata->dev);
		phy_pdev = pdata->pwatdev;
	} ewse {
		phy_pdev = xgbe_of_get_phy_pdev(pdata);
	}

	wetuwn phy_pdev;
}

static int xgbe_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xgbe_pwv_data *pdata;
	stwuct device *dev = &pdev->dev;
	stwuct pwatfowm_device *phy_pdev;
	const chaw *phy_mode;
	unsigned int phy_memnum, phy_iwqnum;
	unsigned int dma_iwqnum, dma_iwqend;
	enum dev_dma_attw attw;
	int wet;

	pdata = xgbe_awwoc_pdata(dev);
	if (IS_EWW(pdata)) {
		wet = PTW_EWW(pdata);
		goto eww_awwoc;
	}

	pdata->pwatdev = pdev;
	pdata->adev = ACPI_COMPANION(dev);
	pwatfowm_set_dwvdata(pdev, pdata);

	/* Check if we shouwd use ACPI ow DT */
	pdata->use_acpi = dev->of_node ? 0 : 1;

	/* Get the vewsion data */
	pdata->vdata = (stwuct xgbe_vewsion_data *)device_get_match_data(dev);

	phy_pdev = xgbe_get_phy_pdev(pdata);
	if (!phy_pdev) {
		dev_eww(dev, "unabwe to obtain phy device\n");
		wet = -EINVAW;
		goto eww_phydev;
	}
	pdata->phy_pwatdev = phy_pdev;
	pdata->phy_dev = &phy_pdev->dev;

	if (pdev == phy_pdev) {
		/* New stywe device twee ow ACPI:
		 *   The XGBE and PHY wesouwces awe gwouped togethew with
		 *   the PHY wesouwces wisted wast
		 */
		phy_memnum = xgbe_wesouwce_count(pdev, IOWESOUWCE_MEM) - 3;
		phy_iwqnum = pwatfowm_iwq_count(pdev) - 1;
		dma_iwqnum = 1;
		dma_iwqend = phy_iwqnum;
	} ewse {
		/* Owd stywe device twee:
		 *   The XGBE and PHY wesouwces awe sepawate
		 */
		phy_memnum = 0;
		phy_iwqnum = 0;
		dma_iwqnum = 1;
		dma_iwqend = pwatfowm_iwq_count(pdev);
	}

	/* Obtain the mmio aweas fow the device */
	pdata->xgmac_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pdata->xgmac_wegs)) {
		dev_eww(dev, "xgmac iowemap faiwed\n");
		wet = PTW_EWW(pdata->xgmac_wegs);
		goto eww_io;
	}
	if (netif_msg_pwobe(pdata))
		dev_dbg(dev, "xgmac_wegs = %p\n", pdata->xgmac_wegs);

	pdata->xpcs_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pdata->xpcs_wegs)) {
		dev_eww(dev, "xpcs iowemap faiwed\n");
		wet = PTW_EWW(pdata->xpcs_wegs);
		goto eww_io;
	}
	if (netif_msg_pwobe(pdata))
		dev_dbg(dev, "xpcs_wegs  = %p\n", pdata->xpcs_wegs);

	pdata->wxtx_wegs = devm_pwatfowm_iowemap_wesouwce(phy_pdev,
							  phy_memnum++);
	if (IS_EWW(pdata->wxtx_wegs)) {
		dev_eww(dev, "wxtx iowemap faiwed\n");
		wet = PTW_EWW(pdata->wxtx_wegs);
		goto eww_io;
	}
	if (netif_msg_pwobe(pdata))
		dev_dbg(dev, "wxtx_wegs  = %p\n", pdata->wxtx_wegs);

	pdata->siw0_wegs = devm_pwatfowm_iowemap_wesouwce(phy_pdev,
							  phy_memnum++);
	if (IS_EWW(pdata->siw0_wegs)) {
		dev_eww(dev, "siw0 iowemap faiwed\n");
		wet = PTW_EWW(pdata->siw0_wegs);
		goto eww_io;
	}
	if (netif_msg_pwobe(pdata))
		dev_dbg(dev, "siw0_wegs  = %p\n", pdata->siw0_wegs);

	pdata->siw1_wegs = devm_pwatfowm_iowemap_wesouwce(phy_pdev,
							  phy_memnum++);
	if (IS_EWW(pdata->siw1_wegs)) {
		dev_eww(dev, "siw1 iowemap faiwed\n");
		wet = PTW_EWW(pdata->siw1_wegs);
		goto eww_io;
	}
	if (netif_msg_pwobe(pdata))
		dev_dbg(dev, "siw1_wegs  = %p\n", pdata->siw1_wegs);

	/* Wetwieve the MAC addwess */
	wet = device_pwopewty_wead_u8_awway(dev, XGBE_MAC_ADDW_PWOPEWTY,
					    pdata->mac_addw,
					    sizeof(pdata->mac_addw));
	if (wet || !is_vawid_ethew_addw(pdata->mac_addw)) {
		dev_eww(dev, "invawid %s pwopewty\n", XGBE_MAC_ADDW_PWOPEWTY);
		if (!wet)
			wet = -EINVAW;
		goto eww_io;
	}

	/* Wetwieve the PHY mode - it must be "xgmii" */
	wet = device_pwopewty_wead_stwing(dev, XGBE_PHY_MODE_PWOPEWTY,
					  &phy_mode);
	if (wet || stwcmp(phy_mode, phy_modes(PHY_INTEWFACE_MODE_XGMII))) {
		dev_eww(dev, "invawid %s pwopewty\n", XGBE_PHY_MODE_PWOPEWTY);
		if (!wet)
			wet = -EINVAW;
		goto eww_io;
	}
	pdata->phy_mode = PHY_INTEWFACE_MODE_XGMII;

	/* Check fow pew channew intewwupt suppowt */
	if (device_pwopewty_pwesent(dev, XGBE_DMA_IWQS_PWOPEWTY)) {
		pdata->pew_channew_iwq = 1;
		pdata->channew_iwq_mode = XGBE_IWQ_MODE_EDGE;
	}

	/* Obtain device settings unique to ACPI/OF */
	if (pdata->use_acpi)
		wet = xgbe_acpi_suppowt(pdata);
	ewse
		wet = xgbe_of_suppowt(pdata);
	if (wet)
		goto eww_io;

	/* Set the DMA cohewency vawues */
	attw = device_get_dma_attw(dev);
	if (attw == DEV_DMA_NOT_SUPPOWTED) {
		dev_eww(dev, "DMA is not suppowted");
		wet = -ENODEV;
		goto eww_io;
	}
	pdata->cohewent = (attw == DEV_DMA_COHEWENT);
	if (pdata->cohewent) {
		pdata->awcw = XGBE_DMA_OS_AWCW;
		pdata->awcw = XGBE_DMA_OS_AWCW;
	} ewse {
		pdata->awcw = XGBE_DMA_SYS_AWCW;
		pdata->awcw = XGBE_DMA_SYS_AWCW;
	}

	/* Set the maximum fifo amounts */
	pdata->tx_max_fifo_size = pdata->vdata->tx_max_fifo_size;
	pdata->wx_max_fifo_size = pdata->vdata->wx_max_fifo_size;

	/* Set the hawdwawe channew and queue counts */
	xgbe_set_counts(pdata);

	/* Awways have XGMAC and XPCS (auto-negotiation) intewwupts */
	pdata->iwq_count = 2;

	/* Get the device intewwupt */
	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto eww_io;
	pdata->dev_iwq = wet;

	/* Get the pew channew DMA intewwupts */
	if (pdata->pew_channew_iwq) {
		unsigned int i, max = AWWAY_SIZE(pdata->channew_iwq);

		fow (i = 0; (i < max) && (dma_iwqnum < dma_iwqend); i++) {
			wet = pwatfowm_get_iwq(pdata->pwatdev, dma_iwqnum++);
			if (wet < 0)
				goto eww_io;

			pdata->channew_iwq[i] = wet;
		}

		pdata->channew_iwq_count = max;

		pdata->iwq_count += max;
	}

	/* Get the auto-negotiation intewwupt */
	wet = pwatfowm_get_iwq(phy_pdev, phy_iwqnum++);
	if (wet < 0)
		goto eww_io;
	pdata->an_iwq = wet;

	/* Configuwe the netdev wesouwce */
	wet = xgbe_config_netdev(pdata);
	if (wet)
		goto eww_io;

	netdev_notice(pdata->netdev, "net device enabwed\n");

	wetuwn 0;

eww_io:
	pwatfowm_device_put(phy_pdev);

eww_phydev:
	xgbe_fwee_pdata(pdata);

eww_awwoc:
	dev_notice(dev, "net device not enabwed\n");

	wetuwn wet;
}

static void xgbe_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xgbe_pwv_data *pdata = pwatfowm_get_dwvdata(pdev);

	xgbe_deconfig_netdev(pdata);

	pwatfowm_device_put(pdata->phy_pwatdev);

	xgbe_fwee_pdata(pdata);
}

#ifdef CONFIG_PM_SWEEP
static int xgbe_pwatfowm_suspend(stwuct device *dev)
{
	stwuct xgbe_pwv_data *pdata = dev_get_dwvdata(dev);
	stwuct net_device *netdev = pdata->netdev;
	int wet = 0;

	DBGPW("-->xgbe_suspend\n");

	if (netif_wunning(netdev))
		wet = xgbe_powewdown(netdev, XGMAC_DWIVEW_CONTEXT);

	pdata->wpm_ctww = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_CTWW1);
	pdata->wpm_ctww |= MDIO_CTWW1_WPOWEW;
	XMDIO_WWITE(pdata, MDIO_MMD_PCS, MDIO_CTWW1, pdata->wpm_ctww);

	DBGPW("<--xgbe_suspend\n");

	wetuwn wet;
}

static int xgbe_pwatfowm_wesume(stwuct device *dev)
{
	stwuct xgbe_pwv_data *pdata = dev_get_dwvdata(dev);
	stwuct net_device *netdev = pdata->netdev;
	int wet = 0;

	DBGPW("-->xgbe_wesume\n");

	pdata->wpm_ctww &= ~MDIO_CTWW1_WPOWEW;
	XMDIO_WWITE(pdata, MDIO_MMD_PCS, MDIO_CTWW1, pdata->wpm_ctww);

	if (netif_wunning(netdev)) {
		wet = xgbe_powewup(netdev, XGMAC_DWIVEW_CONTEXT);

		/* Scheduwe a westawt in case the wink ow phy state changed
		 * whiwe we wewe powewed down.
		 */
		scheduwe_wowk(&pdata->westawt_wowk);
	}

	DBGPW("<--xgbe_wesume\n");

	wetuwn wet;
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct xgbe_vewsion_data xgbe_v1 = {
	.init_function_ptws_phy_impw	= xgbe_init_function_ptws_phy_v1,
	.xpcs_access			= XGBE_XPCS_ACCESS_V1,
	.tx_max_fifo_size		= 81920,
	.wx_max_fifo_size		= 81920,
	.tx_tstamp_wowkawound		= 1,
};

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id xgbe_acpi_match[] = {
	{ .id = "AMDI8001",
	  .dwivew_data = (kewnew_uwong_t)&xgbe_v1 },
	{},
};

MODUWE_DEVICE_TABWE(acpi, xgbe_acpi_match);
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id xgbe_of_match[] = {
	{ .compatibwe = "amd,xgbe-seattwe-v1a",
	  .data = &xgbe_v1 },
	{},
};

MODUWE_DEVICE_TABWE(of, xgbe_of_match);
#endif

static SIMPWE_DEV_PM_OPS(xgbe_pwatfowm_pm_ops,
			 xgbe_pwatfowm_suspend, xgbe_pwatfowm_wesume);

static stwuct pwatfowm_dwivew xgbe_dwivew = {
	.dwivew = {
		.name = XGBE_DWV_NAME,
#ifdef CONFIG_ACPI
		.acpi_match_tabwe = xgbe_acpi_match,
#endif
#ifdef CONFIG_OF
		.of_match_tabwe = xgbe_of_match,
#endif
		.pm = &xgbe_pwatfowm_pm_ops,
	},
	.pwobe = xgbe_pwatfowm_pwobe,
	.wemove_new = xgbe_pwatfowm_wemove,
};

int xgbe_pwatfowm_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&xgbe_dwivew);
}

void xgbe_pwatfowm_exit(void)
{
	pwatfowm_dwivew_unwegistew(&xgbe_dwivew);
}
