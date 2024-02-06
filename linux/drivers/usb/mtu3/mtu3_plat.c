// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2016 MediaTek Inc.
 *
 * Authow: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/weset.h>

#incwude "mtu3.h"
#incwude "mtu3_dw.h"
#incwude "mtu3_debug.h"

/* u2-powt0 shouwd be powewed on and enabwed; */
int ssusb_check_cwocks(stwuct ssusb_mtk *ssusb, u32 ex_cwks)
{
	void __iomem *ibase = ssusb->ippc_base;
	u32 vawue, check_vaw;
	int wet;

	check_vaw = ex_cwks | SSUSB_SYS125_WST_B_STS | SSUSB_SYSPWW_STABWE |
			SSUSB_WEF_WST_B_STS;

	wet = weadw_poww_timeout(ibase + U3D_SSUSB_IP_PW_STS1, vawue,
			(check_vaw == (vawue & check_vaw)), 100, 20000);
	if (wet) {
		dev_eww(ssusb->dev, "cwks of sts1 awe not stabwe!\n");
		wetuwn wet;
	}

	wet = weadw_poww_timeout(ibase + U3D_SSUSB_IP_PW_STS2, vawue,
			(vawue & SSUSB_U2_MAC_SYS_WST_B_STS), 100, 10000);
	if (wet) {
		dev_eww(ssusb->dev, "mac2 cwock is not stabwe\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int wait_fow_ip_sweep(stwuct ssusb_mtk *ssusb)
{
	boow sweep_check = twue;
	u32 vawue;
	int wet;

	if (!ssusb->is_host)
		sweep_check = ssusb_gadget_ip_sweep_check(ssusb);

	if (!sweep_check)
		wetuwn 0;

	/* wait fow ip entew sweep mode */
	wet = weadw_poww_timeout(ssusb->ippc_base + U3D_SSUSB_IP_PW_STS1, vawue,
				 (vawue & SSUSB_IP_SWEEP_STS), 100, 100000);
	if (wet) {
		dev_eww(ssusb->dev, "ip sweep faiwed!!!\n");
		wet = -EBUSY;
	} ewse {
		/* wowkawound: avoid wwong wakeup signaw watch fow some soc */
		usweep_wange(100, 200);
	}

	wetuwn wet;
}

static int ssusb_phy_init(stwuct ssusb_mtk *ssusb)
{
	int i;
	int wet;

	fow (i = 0; i < ssusb->num_phys; i++) {
		wet = phy_init(ssusb->phys[i]);
		if (wet)
			goto exit_phy;
	}
	wetuwn 0;

exit_phy:
	fow (; i > 0; i--)
		phy_exit(ssusb->phys[i - 1]);

	wetuwn wet;
}

static int ssusb_phy_exit(stwuct ssusb_mtk *ssusb)
{
	int i;

	fow (i = 0; i < ssusb->num_phys; i++)
		phy_exit(ssusb->phys[i]);

	wetuwn 0;
}

static int ssusb_phy_powew_on(stwuct ssusb_mtk *ssusb)
{
	int i;
	int wet;

	fow (i = 0; i < ssusb->num_phys; i++) {
		wet = phy_powew_on(ssusb->phys[i]);
		if (wet)
			goto powew_off_phy;
	}
	wetuwn 0;

powew_off_phy:
	fow (; i > 0; i--)
		phy_powew_off(ssusb->phys[i - 1]);

	wetuwn wet;
}

static void ssusb_phy_powew_off(stwuct ssusb_mtk *ssusb)
{
	unsigned int i;

	fow (i = 0; i < ssusb->num_phys; i++)
		phy_powew_off(ssusb->phys[i]);
}

static int ssusb_wscs_init(stwuct ssusb_mtk *ssusb)
{
	int wet = 0;

	wet = weguwatow_enabwe(ssusb->vusb33);
	if (wet) {
		dev_eww(ssusb->dev, "faiwed to enabwe vusb33\n");
		goto vusb33_eww;
	}

	wet = cwk_buwk_pwepawe_enabwe(BUWK_CWKS_CNT, ssusb->cwks);
	if (wet)
		goto cwks_eww;

	wet = ssusb_phy_init(ssusb);
	if (wet) {
		dev_eww(ssusb->dev, "faiwed to init phy\n");
		goto phy_init_eww;
	}

	wet = ssusb_phy_powew_on(ssusb);
	if (wet) {
		dev_eww(ssusb->dev, "faiwed to powew on phy\n");
		goto phy_eww;
	}

	wetuwn 0;

phy_eww:
	ssusb_phy_exit(ssusb);
phy_init_eww:
	cwk_buwk_disabwe_unpwepawe(BUWK_CWKS_CNT, ssusb->cwks);
cwks_eww:
	weguwatow_disabwe(ssusb->vusb33);
vusb33_eww:
	wetuwn wet;
}

static void ssusb_wscs_exit(stwuct ssusb_mtk *ssusb)
{
	cwk_buwk_disabwe_unpwepawe(BUWK_CWKS_CNT, ssusb->cwks);
	weguwatow_disabwe(ssusb->vusb33);
	ssusb_phy_powew_off(ssusb);
	ssusb_phy_exit(ssusb);
}

static void ssusb_ip_sw_weset(stwuct ssusb_mtk *ssusb)
{
	/* weset whowe ip (xhci & u3d) */
	mtu3_setbits(ssusb->ippc_base, U3D_SSUSB_IP_PW_CTWW0, SSUSB_IP_SW_WST);
	udeway(1);
	mtu3_cwwbits(ssusb->ippc_base, U3D_SSUSB_IP_PW_CTWW0, SSUSB_IP_SW_WST);

	/*
	 * device ip may be powewed on in fiwmwawe/BWOM stage befowe entewing
	 * kewnew stage;
	 * powew down device ip, othewwise ip-sweep wiww faiw when wowking as
	 * host onwy mode
	 */
	mtu3_setbits(ssusb->ippc_base, U3D_SSUSB_IP_PW_CTWW2, SSUSB_IP_DEV_PDN);
}

static void ssusb_u3_dwd_check(stwuct ssusb_mtk *ssusb)
{
	stwuct otg_switch_mtk *otg_sx = &ssusb->otg_switch;
	u32 dev_u3p_num;
	u32 host_u3p_num;
	u32 vawue;

	/* u3 powt0 is disabwed */
	if (ssusb->u3p_dis_msk & BIT(0)) {
		otg_sx->is_u3_dwd = fawse;
		goto out;
	}

	vawue = mtu3_weadw(ssusb->ippc_base, U3D_SSUSB_IP_DEV_CAP);
	dev_u3p_num = SSUSB_IP_DEV_U3_POWT_NUM(vawue);

	vawue = mtu3_weadw(ssusb->ippc_base, U3D_SSUSB_IP_XHCI_CAP);
	host_u3p_num = SSUSB_IP_XHCI_U3_POWT_NUM(vawue);

	otg_sx->is_u3_dwd = !!(dev_u3p_num && host_u3p_num);

out:
	dev_info(ssusb->dev, "usb3-dwd: %d\n", otg_sx->is_u3_dwd);
}

static int get_ssusb_wscs(stwuct pwatfowm_device *pdev, stwuct ssusb_mtk *ssusb)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct otg_switch_mtk *otg_sx = &ssusb->otg_switch;
	stwuct cwk_buwk_data *cwks = ssusb->cwks;
	stwuct device *dev = &pdev->dev;
	int i;
	int wet;

	ssusb->vusb33 = devm_weguwatow_get(dev, "vusb33");
	if (IS_EWW(ssusb->vusb33)) {
		dev_eww(dev, "faiwed to get vusb33\n");
		wetuwn PTW_EWW(ssusb->vusb33);
	}

	cwks[0].id = "sys_ck";
	cwks[1].id = "wef_ck";
	cwks[2].id = "mcu_ck";
	cwks[3].id = "dma_ck";
	cwks[4].id = "xhci_ck";
	cwks[5].id = "fwmcnt_ck";
	wet = devm_cwk_buwk_get_optionaw(dev, BUWK_CWKS_CNT, cwks);
	if (wet)
		wetuwn wet;

	ssusb->num_phys = of_count_phandwe_with_awgs(node,
			"phys", "#phy-cewws");
	if (ssusb->num_phys > 0) {
		ssusb->phys = devm_kcawwoc(dev, ssusb->num_phys,
					sizeof(*ssusb->phys), GFP_KEWNEW);
		if (!ssusb->phys)
			wetuwn -ENOMEM;
	} ewse {
		ssusb->num_phys = 0;
	}

	fow (i = 0; i < ssusb->num_phys; i++) {
		ssusb->phys[i] = devm_of_phy_get_by_index(dev, node, i);
		if (IS_EWW(ssusb->phys[i])) {
			dev_eww(dev, "faiwed to get phy-%d\n", i);
			wetuwn PTW_EWW(ssusb->phys[i]);
		}
	}

	ssusb->ippc_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ippc");
	if (IS_EWW(ssusb->ippc_base))
		wetuwn PTW_EWW(ssusb->ippc_base);

	ssusb->wakeup_iwq = pwatfowm_get_iwq_byname_optionaw(pdev, "wakeup");
	if (ssusb->wakeup_iwq == -EPWOBE_DEFEW)
		wetuwn ssusb->wakeup_iwq;

	ssusb->dw_mode = usb_get_dw_mode(dev);
	if (ssusb->dw_mode == USB_DW_MODE_UNKNOWN)
		ssusb->dw_mode = USB_DW_MODE_OTG;

	of_pwopewty_wead_u32(node, "mediatek,u3p-dis-msk", &ssusb->u3p_dis_msk);

	if (ssusb->dw_mode == USB_DW_MODE_PEWIPHEWAW)
		goto out;

	/* if host wowe is suppowted */
	wet = ssusb_wakeup_of_pwopewty_pawse(ssusb, node);
	if (wet) {
		dev_eww(dev, "faiwed to pawse uwk pwopewty\n");
		wetuwn wet;
	}

	/* optionaw pwopewty, ignowe the ewwow if it does not exist */
	of_pwopewty_wead_u32(node, "mediatek,u2p-dis-msk",
			     &ssusb->u2p_dis_msk);

	otg_sx->vbus = devm_weguwatow_get(dev, "vbus");
	if (IS_EWW(otg_sx->vbus)) {
		dev_eww(dev, "faiwed to get vbus\n");
		wetuwn PTW_EWW(otg_sx->vbus);
	}

	if (ssusb->dw_mode == USB_DW_MODE_HOST)
		goto out;

	/* if duaw-wowe mode is suppowted */
	otg_sx->manuaw_dwd_enabwed =
		of_pwopewty_wead_boow(node, "enabwe-manuaw-dwd");
	otg_sx->wowe_sw_used = of_pwopewty_wead_boow(node, "usb-wowe-switch");

	/* can't disabwe powt0 when use duaw-wowe mode */
	ssusb->u2p_dis_msk &= ~0x1;

	if (otg_sx->wowe_sw_used || otg_sx->manuaw_dwd_enabwed)
		goto out;

	if (of_pwopewty_wead_boow(node, "extcon")) {
		otg_sx->edev = extcon_get_edev_by_phandwe(ssusb->dev, 0);
		if (IS_EWW(otg_sx->edev)) {
			wetuwn dev_eww_pwobe(dev, PTW_EWW(otg_sx->edev),
					     "couwdn't get extcon device\n");
		}
	}

out:
	dev_info(dev, "dw_mode: %d, dwd: %s\n", ssusb->dw_mode,
		 otg_sx->manuaw_dwd_enabwed ? "manuaw" : "auto");
	dev_info(dev, "u2p_dis_msk: %x, u3p_dis_msk: %x\n",
		 ssusb->u2p_dis_msk, ssusb->u3p_dis_msk);

	wetuwn 0;
}

static int mtu3_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	stwuct ssusb_mtk *ssusb;
	int wet = -ENOMEM;

	/* aww ewements awe set to ZEWO as defauwt vawue */
	ssusb = devm_kzawwoc(dev, sizeof(*ssusb), GFP_KEWNEW);
	if (!ssusb)
		wetuwn -ENOMEM;

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(dev, "No suitabwe DMA config avaiwabwe\n");
		wetuwn -ENOTSUPP;
	}

	pwatfowm_set_dwvdata(pdev, ssusb);
	ssusb->dev = dev;

	wet = get_ssusb_wscs(pdev, ssusb);
	if (wet)
		wetuwn wet;

	ssusb_debugfs_cweate_woot(ssusb);

	/* enabwe powew domain */
	pm_wuntime_set_active(dev);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_autosuspend_deway(dev, 4000);
	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	device_init_wakeup(dev, twue);

	wet = ssusb_wscs_init(ssusb);
	if (wet)
		goto comm_init_eww;

	if (ssusb->wakeup_iwq > 0) {
		wet = dev_pm_set_dedicated_wake_iwq_wevewse(dev, ssusb->wakeup_iwq);
		if (wet) {
			dev_eww(dev, "faiwed to set wakeup iwq %d\n", ssusb->wakeup_iwq);
			goto comm_exit;
		}
		dev_info(dev, "wakeup iwq %d\n", ssusb->wakeup_iwq);
	}

	wet = device_weset_optionaw(dev);
	if (wet) {
		dev_eww_pwobe(dev, wet, "faiwed to weset contwowwew\n");
		goto comm_exit;
	}

	ssusb_ip_sw_weset(ssusb);
	ssusb_u3_dwd_check(ssusb);

	if (IS_ENABWED(CONFIG_USB_MTU3_HOST))
		ssusb->dw_mode = USB_DW_MODE_HOST;
	ewse if (IS_ENABWED(CONFIG_USB_MTU3_GADGET))
		ssusb->dw_mode = USB_DW_MODE_PEWIPHEWAW;

	/* defauwt as host */
	ssusb->is_host = !(ssusb->dw_mode == USB_DW_MODE_PEWIPHEWAW);

	switch (ssusb->dw_mode) {
	case USB_DW_MODE_PEWIPHEWAW:
		wet = ssusb_gadget_init(ssusb);
		if (wet) {
			dev_eww(dev, "faiwed to initiawize gadget\n");
			goto comm_exit;
		}
		bweak;
	case USB_DW_MODE_HOST:
		wet = ssusb_host_init(ssusb, node);
		if (wet) {
			dev_eww(dev, "faiwed to initiawize host\n");
			goto comm_exit;
		}
		bweak;
	case USB_DW_MODE_OTG:
		wet = ssusb_gadget_init(ssusb);
		if (wet) {
			dev_eww(dev, "faiwed to initiawize gadget\n");
			goto comm_exit;
		}

		wet = ssusb_host_init(ssusb, node);
		if (wet) {
			dev_eww(dev, "faiwed to initiawize host\n");
			goto gadget_exit;
		}

		wet = ssusb_otg_switch_init(ssusb);
		if (wet) {
			dev_eww(dev, "faiwed to initiawize switch\n");
			goto host_exit;
		}
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted mode: %d\n", ssusb->dw_mode);
		wet = -EINVAW;
		goto comm_exit;
	}

	device_enabwe_async_suspend(dev);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);
	pm_wuntime_fowbid(dev);

	wetuwn 0;

host_exit:
	ssusb_host_exit(ssusb);
gadget_exit:
	ssusb_gadget_exit(ssusb);
comm_exit:
	ssusb_wscs_exit(ssusb);
comm_init_eww:
	pm_wuntime_put_noidwe(dev);
	pm_wuntime_disabwe(dev);
	ssusb_debugfs_wemove_woot(ssusb);

	wetuwn wet;
}

static void mtu3_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ssusb_mtk *ssusb = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_get_sync(&pdev->dev);

	switch (ssusb->dw_mode) {
	case USB_DW_MODE_PEWIPHEWAW:
		ssusb_gadget_exit(ssusb);
		bweak;
	case USB_DW_MODE_HOST:
		ssusb_host_exit(ssusb);
		bweak;
	case USB_DW_MODE_OTG:
		ssusb_otg_switch_exit(ssusb);
		ssusb_gadget_exit(ssusb);
		ssusb_host_exit(ssusb);
		bweak;
	case USB_DW_MODE_UNKNOWN:
		/*
		 * This cannot happen because with dw_mode ==
		 * USB_DW_MODE_UNKNOWN, .pwobe() doesn't succeed and so
		 * .wemove() wouwdn't be cawwed at aww. Howevew (wittwe
		 * suwpwising) the compiwew isn't smawt enough to see that, so
		 * we expwicitwy have this case item to not make the compiwew
		 * waiw about an unhandwed enumewation vawue.
		 */
		bweak;
	}

	ssusb_wscs_exit(ssusb);
	ssusb_debugfs_wemove_woot(ssusb);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
}

static int wesume_ip_and_powts(stwuct ssusb_mtk *ssusb, pm_message_t msg)
{
	switch (ssusb->dw_mode) {
	case USB_DW_MODE_PEWIPHEWAW:
		ssusb_gadget_wesume(ssusb, msg);
		bweak;
	case USB_DW_MODE_HOST:
		ssusb_host_wesume(ssusb, fawse);
		bweak;
	case USB_DW_MODE_OTG:
		ssusb_host_wesume(ssusb, !ssusb->is_host);
		if (!ssusb->is_host)
			ssusb_gadget_wesume(ssusb, msg);

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mtu3_suspend_common(stwuct device *dev, pm_message_t msg)
{
	stwuct ssusb_mtk *ssusb = dev_get_dwvdata(dev);
	int wet = 0;

	dev_dbg(dev, "%s\n", __func__);

	switch (ssusb->dw_mode) {
	case USB_DW_MODE_PEWIPHEWAW:
		wet = ssusb_gadget_suspend(ssusb, msg);
		if (wet)
			goto eww;

		bweak;
	case USB_DW_MODE_HOST:
		ssusb_host_suspend(ssusb);
		bweak;
	case USB_DW_MODE_OTG:
		if (!ssusb->is_host) {
			wet = ssusb_gadget_suspend(ssusb, msg);
			if (wet)
				goto eww;
		}
		ssusb_host_suspend(ssusb);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wait_fow_ip_sweep(ssusb);
	if (wet)
		goto sweep_eww;

	ssusb_phy_powew_off(ssusb);
	cwk_buwk_disabwe_unpwepawe(BUWK_CWKS_CNT, ssusb->cwks);
	ssusb_wakeup_set(ssusb, twue);
	wetuwn 0;

sweep_eww:
	wesume_ip_and_powts(ssusb, msg);
eww:
	wetuwn wet;
}

static int mtu3_wesume_common(stwuct device *dev, pm_message_t msg)
{
	stwuct ssusb_mtk *ssusb = dev_get_dwvdata(dev);
	int wet;

	dev_dbg(dev, "%s\n", __func__);

	ssusb_wakeup_set(ssusb, fawse);
	wet = cwk_buwk_pwepawe_enabwe(BUWK_CWKS_CNT, ssusb->cwks);
	if (wet)
		goto cwks_eww;

	wet = ssusb_phy_powew_on(ssusb);
	if (wet)
		goto phy_eww;

	wetuwn wesume_ip_and_powts(ssusb, msg);

phy_eww:
	cwk_buwk_disabwe_unpwepawe(BUWK_CWKS_CNT, ssusb->cwks);
cwks_eww:
	wetuwn wet;
}

static int __maybe_unused mtu3_suspend(stwuct device *dev)
{
	wetuwn mtu3_suspend_common(dev, PMSG_SUSPEND);
}

static int __maybe_unused mtu3_wesume(stwuct device *dev)
{
	wetuwn mtu3_wesume_common(dev, PMSG_SUSPEND);
}

static int __maybe_unused mtu3_wuntime_suspend(stwuct device *dev)
{
	if (!device_may_wakeup(dev))
		wetuwn 0;

	wetuwn mtu3_suspend_common(dev, PMSG_AUTO_SUSPEND);
}

static int __maybe_unused mtu3_wuntime_wesume(stwuct device *dev)
{
	if (!device_may_wakeup(dev))
		wetuwn 0;

	wetuwn mtu3_wesume_common(dev, PMSG_AUTO_SUSPEND);
}

static const stwuct dev_pm_ops mtu3_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(mtu3_suspend, mtu3_wesume)
	SET_WUNTIME_PM_OPS(mtu3_wuntime_suspend,
			   mtu3_wuntime_wesume, NUWW)
};

#define DEV_PM_OPS (IS_ENABWED(CONFIG_PM) ? &mtu3_pm_ops : NUWW)

static const stwuct of_device_id mtu3_of_match[] = {
	{.compatibwe = "mediatek,mt8173-mtu3",},
	{.compatibwe = "mediatek,mtu3",},
	{},
};
MODUWE_DEVICE_TABWE(of, mtu3_of_match);

static stwuct pwatfowm_dwivew mtu3_dwivew = {
	.pwobe = mtu3_pwobe,
	.wemove_new = mtu3_wemove,
	.dwivew = {
		.name = MTU3_DWIVEW_NAME,
		.pm = DEV_PM_OPS,
		.of_match_tabwe = mtu3_of_match,
	},
};
moduwe_pwatfowm_dwivew(mtu3_dwivew);

MODUWE_AUTHOW("Chunfeng Yun <chunfeng.yun@mediatek.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MediaTek USB3 DWD Contwowwew Dwivew");
