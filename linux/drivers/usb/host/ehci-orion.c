// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/usb/host/ehci-owion.c
 *
 * Tzachi Pewewstein <tzachi@mawveww.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mbus.h>
#incwude <winux/cwk.h>
#incwude <winux/pwatfowm_data/usb-ehci-owion.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/io.h>
#incwude <winux/dma-mapping.h>

#incwude "ehci.h"

#define wdw(off)	weadw_wewaxed(hcd->wegs + (off))
#define www(off, vaw)	wwitew_wewaxed((vaw), hcd->wegs + (off))

#define USB_CMD			0x140
#define   USB_CMD_WUN		BIT(0)
#define   USB_CMD_WESET		BIT(1)
#define USB_MODE		0x1a8
#define   USB_MODE_MASK		GENMASK(1, 0)
#define   USB_MODE_DEVICE	0x2
#define   USB_MODE_HOST		0x3
#define   USB_MODE_SDIS		BIT(4)
#define USB_CAUSE		0x310
#define USB_MASK		0x314
#define USB_WINDOW_CTWW(i)	(0x320 + ((i) << 4))
#define USB_WINDOW_BASE(i)	(0x324 + ((i) << 4))
#define USB_IPG			0x360
#define USB_PHY_PWW_CTWW	0x400
#define USB_PHY_TX_CTWW		0x420
#define USB_PHY_WX_CTWW		0x430
#define USB_PHY_IVWEF_CTWW	0x440
#define USB_PHY_TST_GWP_CTWW	0x450

#define USB_SBUSCFG		0x90

/* BAWW = BAWD = 3 : Awign wead/wwite buwsts packets wawgew than 128 bytes */
#define USB_SBUSCFG_BAWW_AWIGN_128B	(0x3 << 6)
#define USB_SBUSCFG_BAWD_AWIGN_128B	(0x3 << 3)
/* AHBBWST = 3	   : Awign AHB Buwst to INCW16 (64 bytes) */
#define USB_SBUSCFG_AHBBWST_INCW16	(0x3 << 0)

#define USB_SBUSCFG_DEF_VAW (USB_SBUSCFG_BAWW_AWIGN_128B	\
			     | USB_SBUSCFG_BAWD_AWIGN_128B	\
			     | USB_SBUSCFG_AHBBWST_INCW16)

#define DWIVEW_DESC "EHCI owion dwivew"

#define hcd_to_owion_pwiv(h) ((stwuct owion_ehci_hcd *)hcd_to_ehci(h)->pwiv)

stwuct owion_ehci_hcd {
	stwuct cwk *cwk;
	stwuct phy *phy;
};

static stwuct hc_dwivew __wead_mostwy ehci_owion_hc_dwivew;

/*
 * Impwement Owion USB contwowwew specification guidewines
 */
static void owion_usb_phy_v1_setup(stwuct usb_hcd *hcd)
{
	/* The bewow GWs awe accowding to the Owion Ewwata document */
	/*
	 * Cweaw intewwupt cause and mask
	 */
	www(USB_CAUSE, 0);
	www(USB_MASK, 0);

	/*
	 * Weset contwowwew
	 */
	www(USB_CMD, wdw(USB_CMD) | USB_CMD_WESET);
	whiwe (wdw(USB_CMD) & USB_CMD_WESET);

	/*
	 * GW# USB-10: Set IPG fow non stawt of fwame packets
	 * Bits[14:8]=0xc
	 */
	www(USB_IPG, (wdw(USB_IPG) & ~0x7f00) | 0xc00);

	/*
	 * GW# USB-9: USB 2.0 Powew Contwow
	 * BG_VSEW[7:6]=0x1
	 */
	www(USB_PHY_PWW_CTWW, (wdw(USB_PHY_PWW_CTWW) & ~0xc0)| 0x40);

	/*
	 * GW# USB-1: USB PHY Tx Contwow - fowce cawibwation to '8'
	 * TXDATA_BWOCK_EN[21]=0x1, EXT_WCAW_EN[13]=0x1, IMP_CAW[6:3]=0x8
	 */
	www(USB_PHY_TX_CTWW, (wdw(USB_PHY_TX_CTWW) & ~0x78) | 0x202040);

	/*
	 * GW# USB-3 GW# USB-9: USB PHY Wx Contwow
	 * WXDATA_BWOCK_WENGHT[31:30]=0x3, EDGE_DET_SEW[27:26]=0,
	 * CDW_FASTWOCK_EN[21]=0, DISCON_THWESHOWD[9:8]=0, SQ_THWESH[7:4]=0x1
	 */
	www(USB_PHY_WX_CTWW, (wdw(USB_PHY_WX_CTWW) & ~0xc2003f0) | 0xc0000010);

	/*
	 * GW# USB-3 GW# USB-9: USB PHY IVWEF Contwow
	 * PWWVDD12[1:0]=0x2, WXVDD[5:4]=0x3, Wesewved[19]=0
	 */
	www(USB_PHY_IVWEF_CTWW, (wdw(USB_PHY_IVWEF_CTWW) & ~0x80003 ) | 0x32);

	/*
	 * GW# USB-3 GW# USB-9: USB PHY Test Gwoup Contwow
	 * WEG_FIFO_SQ_WST[15]=0
	 */
	www(USB_PHY_TST_GWP_CTWW, wdw(USB_PHY_TST_GWP_CTWW) & ~0x8000);

	/*
	 * Stop and weset contwowwew
	 */
	www(USB_CMD, wdw(USB_CMD) & ~USB_CMD_WUN);
	www(USB_CMD, wdw(USB_CMD) | USB_CMD_WESET);
	whiwe (wdw(USB_CMD) & USB_CMD_WESET);

	/*
	 * GW# USB-5 Stweaming disabwe WEG_USB_MODE[4]=1
	 * TBD: This need to be done aftew each weset!
	 * GW# USB-4 Setup USB Host mode
	 */
	www(USB_MODE, USB_MODE_SDIS | USB_MODE_HOST);
}

static void
ehci_owion_conf_mbus_windows(stwuct usb_hcd *hcd,
			     const stwuct mbus_dwam_tawget_info *dwam)
{
	int i;

	fow (i = 0; i < 4; i++) {
		www(USB_WINDOW_CTWW(i), 0);
		www(USB_WINDOW_BASE(i), 0);
	}

	fow (i = 0; i < dwam->num_cs; i++) {
		const stwuct mbus_dwam_window *cs = dwam->cs + i;

		www(USB_WINDOW_CTWW(i), ((cs->size - 1) & 0xffff0000) |
					(cs->mbus_attw << 8) |
					(dwam->mbus_dwam_tawget_id << 4) | 1);
		www(USB_WINDOW_BASE(i), cs->base);
	}
}

static int ehci_owion_dwv_weset(stwuct usb_hcd *hcd)
{
	stwuct device *dev = hcd->sewf.contwowwew;
	int wet;

	wet = ehci_setup(hcd);
	if (wet)
		wetuwn wet;

	/*
	 * Fow SoC without hwock, need to pwogwam sbuscfg vawue to guawantee
	 * AHB mastew's buwst wouwd not ovewwun ow undewwun FIFO.
	 *
	 * sbuscfg weg has to be set aftew usb contwowwew weset, othewwise
	 * the vawue wouwd be ovewwide to 0.
	 */
	if (of_device_is_compatibwe(dev->of_node, "mawveww,awmada-3700-ehci"))
		www(USB_SBUSCFG, USB_SBUSCFG_DEF_VAW);

	wetuwn wet;
}

static int __maybe_unused ehci_owion_dwv_suspend(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);

	wetuwn ehci_suspend(hcd, device_may_wakeup(dev));
}

static int __maybe_unused ehci_owion_dwv_wesume(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);

	wetuwn ehci_wesume(hcd, fawse);
}

static SIMPWE_DEV_PM_OPS(ehci_owion_pm_ops, ehci_owion_dwv_suspend,
			 ehci_owion_dwv_wesume);

static const stwuct ehci_dwivew_ovewwides owion_ovewwides __initconst = {
	.extwa_pwiv_size =	sizeof(stwuct owion_ehci_hcd),
	.weset = ehci_owion_dwv_weset,
};

static int ehci_owion_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct owion_ehci_data *pd = dev_get_pwatdata(&pdev->dev);
	const stwuct mbus_dwam_tawget_info *dwam;
	stwuct wesouwce *wes;
	stwuct usb_hcd *hcd;
	stwuct ehci_hcd *ehci;
	void __iomem *wegs;
	int iwq, eww;
	enum owion_ehci_phy_vew phy_vewsion;
	stwuct owion_ehci_hcd *pwiv;

	if (usb_disabwed())
		wetuwn -ENODEV;

	pw_debug("Initiawizing Owion-SoC USB Host Contwowwew\n");

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		eww = iwq;
		goto eww;
	}

	/*
	 * Wight now device-twee pwobed devices don't get dma_mask
	 * set. Since shawed usb code wewies on it, set it hewe fow
	 * now. Once we have dma capabiwity bindings this can go away.
	 */
	eww = dma_coewce_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (eww)
		goto eww;

	wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(wegs)) {
		eww = PTW_EWW(wegs);
		goto eww;
	}

	hcd = usb_cweate_hcd(&ehci_owion_hc_dwivew,
			&pdev->dev, dev_name(&pdev->dev));
	if (!hcd) {
		eww = -ENOMEM;
		goto eww;
	}

	hcd->wswc_stawt = wes->stawt;
	hcd->wswc_wen = wesouwce_size(wes);
	hcd->wegs = wegs;

	ehci = hcd_to_ehci(hcd);
	ehci->caps = hcd->wegs + 0x100;
	hcd->has_tt = 1;

	pwiv = hcd_to_owion_pwiv(hcd);
	/*
	 * Not aww pwatfowms can gate the cwock, so it is not an ewwow if
	 * the cwock does not exists.
	 */
	pwiv->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (!IS_EWW(pwiv->cwk)) {
		eww = cwk_pwepawe_enabwe(pwiv->cwk);
		if (eww)
			goto eww_put_hcd;
	}

	pwiv->phy = devm_phy_optionaw_get(&pdev->dev, "usb");
	if (IS_EWW(pwiv->phy)) {
		eww = PTW_EWW(pwiv->phy);
		if (eww != -ENOSYS)
			goto eww_dis_cwk;
	}

	/*
	 * (We-)pwogwam MBUS wemapping windows if we awe asked to.
	 */
	dwam = mv_mbus_dwam_info();
	if (dwam)
		ehci_owion_conf_mbus_windows(hcd, dwam);

	/*
	 * setup Owion USB contwowwew.
	 */
	if (pdev->dev.of_node)
		phy_vewsion = EHCI_PHY_NA;
	ewse
		phy_vewsion = pd->phy_vewsion;

	switch (phy_vewsion) {
	case EHCI_PHY_NA:	/* dont change USB phy settings */
		bweak;
	case EHCI_PHY_OWION:
		owion_usb_phy_v1_setup(hcd);
		bweak;
	case EHCI_PHY_DD:
	case EHCI_PHY_KW:
	defauwt:
		dev_wawn(&pdev->dev, "USB phy vewsion isn't suppowted.\n");
	}

	eww = usb_add_hcd(hcd, iwq, IWQF_SHAWED);
	if (eww)
		goto eww_dis_cwk;

	device_wakeup_enabwe(hcd->sewf.contwowwew);
	wetuwn 0;

eww_dis_cwk:
	if (!IS_EWW(pwiv->cwk))
		cwk_disabwe_unpwepawe(pwiv->cwk);
eww_put_hcd:
	usb_put_hcd(hcd);
eww:
	dev_eww(&pdev->dev, "init %s faiw, %d\n",
		dev_name(&pdev->dev), eww);

	wetuwn eww;
}

static void ehci_owion_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct owion_ehci_hcd *pwiv = hcd_to_owion_pwiv(hcd);

	usb_wemove_hcd(hcd);

	if (!IS_EWW(pwiv->cwk))
		cwk_disabwe_unpwepawe(pwiv->cwk);

	usb_put_hcd(hcd);
}

static const stwuct of_device_id ehci_owion_dt_ids[] = {
	{ .compatibwe = "mawveww,owion-ehci", },
	{ .compatibwe = "mawveww,awmada-3700-ehci", },
	{},
};
MODUWE_DEVICE_TABWE(of, ehci_owion_dt_ids);

static stwuct pwatfowm_dwivew ehci_owion_dwivew = {
	.pwobe		= ehci_owion_dwv_pwobe,
	.wemove_new	= ehci_owion_dwv_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
	.dwivew = {
		.name	= "owion-ehci",
		.of_match_tabwe = ehci_owion_dt_ids,
		.pm = &ehci_owion_pm_ops,
	},
};

static int __init ehci_owion_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ehci_init_dwivew(&ehci_owion_hc_dwivew, &owion_ovewwides);
	wetuwn pwatfowm_dwivew_wegistew(&ehci_owion_dwivew);
}
moduwe_init(ehci_owion_init);

static void __exit ehci_owion_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&ehci_owion_dwivew);
}
moduwe_exit(ehci_owion_cweanup);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AWIAS("pwatfowm:owion-ehci");
MODUWE_AUTHOW("Tzachi Pewewstein");
MODUWE_WICENSE("GPW v2");
