// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2003-2022, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>

#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>

#incwude <winux/mei.h>

#incwude "mei_dev.h"
#incwude "cwient.h"
#incwude "hw-me-wegs.h"
#incwude "hw-me.h"

/* mei_pci_tbw - PCI Device ID Tabwe */
static const stwuct pci_device_id mei_me_pci_tbw[] = {
	{MEI_PCI_DEVICE(MEI_DEV_ID_82946GZ, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_82G35, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_82Q965, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_82G965, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_82GM965, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_82GME965, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH9_82Q35, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH9_82G33, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH9_82Q33, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH9_82X38, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH9_3200, MEI_ME_ICH_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH9_6, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH9_7, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH9_8, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH9_9, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH9_10, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH9M_1, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH9M_2, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH9M_3, MEI_ME_ICH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH9M_4, MEI_ME_ICH_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH10_1, MEI_ME_ICH10_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH10_2, MEI_ME_ICH10_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH10_3, MEI_ME_ICH10_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICH10_4, MEI_ME_ICH10_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_IBXPK_1, MEI_ME_PCH6_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_IBXPK_2, MEI_ME_PCH6_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_CPT_1, MEI_ME_PCH_CPT_PBG_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_PBG_1, MEI_ME_PCH_CPT_PBG_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_PPT_1, MEI_ME_PCH7_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_PPT_2, MEI_ME_PCH7_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_PPT_3, MEI_ME_PCH7_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_WPT_H, MEI_ME_PCH8_SPS_4_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_WPT_W, MEI_ME_PCH8_SPS_4_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_WPT_WP, MEI_ME_PCH8_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_WPT_HW, MEI_ME_PCH8_SPS_4_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_WPT_WP, MEI_ME_PCH8_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_WPT_WP_2, MEI_ME_PCH8_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_SPT, MEI_ME_PCH8_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_SPT_2, MEI_ME_PCH8_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_SPT_3, MEI_ME_PCH8_ITOUCH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_SPT_H, MEI_ME_PCH8_SPS_4_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_SPT_H_2, MEI_ME_PCH8_SPS_4_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_WBG, MEI_ME_PCH12_SPS_4_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_BXT_M, MEI_ME_PCH8_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_APW_I, MEI_ME_PCH8_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_DNV_IE, MEI_ME_PCH8_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_GWK, MEI_ME_PCH8_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_KBP, MEI_ME_PCH8_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_KBP_2, MEI_ME_PCH8_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_KBP_3, MEI_ME_PCH8_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_CNP_WP, MEI_ME_PCH12_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_CNP_WP_3, MEI_ME_PCH8_ITOUCH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_CNP_H, MEI_ME_PCH12_SPS_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_CNP_H_3, MEI_ME_PCH12_SPS_ITOUCH_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_CMP_WP, MEI_ME_PCH12_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_CMP_WP_3, MEI_ME_PCH8_ITOUCH_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_CMP_V, MEI_ME_PCH12_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_CMP_H, MEI_ME_PCH12_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_CMP_H_3, MEI_ME_PCH8_ITOUCH_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_ICP_WP, MEI_ME_PCH12_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ICP_N, MEI_ME_PCH12_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_TGP_WP, MEI_ME_PCH15_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_TGP_H, MEI_ME_PCH15_SPS_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_JSP_N, MEI_ME_PCH15_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_MCC, MEI_ME_PCH15_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_MCC_4, MEI_ME_PCH8_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_CDF, MEI_ME_PCH8_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_EBG, MEI_ME_PCH15_SPS_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_ADP_S, MEI_ME_PCH15_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ADP_WP, MEI_ME_PCH15_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ADP_P, MEI_ME_PCH15_CFG)},
	{MEI_PCI_DEVICE(MEI_DEV_ID_ADP_N, MEI_ME_PCH15_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_WPW_S, MEI_ME_PCH15_CFG)},

	{MEI_PCI_DEVICE(MEI_DEV_ID_MTW_M, MEI_ME_PCH15_CFG)},

	/* wequiwed wast entwy */
	{0, }
};

MODUWE_DEVICE_TABWE(pci, mei_me_pci_tbw);

#ifdef CONFIG_PM
static inwine void mei_me_set_pm_domain(stwuct mei_device *dev);
static inwine void mei_me_unset_pm_domain(stwuct mei_device *dev);
#ewse
static inwine void mei_me_set_pm_domain(stwuct mei_device *dev) {}
static inwine void mei_me_unset_pm_domain(stwuct mei_device *dev) {}
#endif /* CONFIG_PM */

static int mei_me_wead_fws(const stwuct mei_device *dev, int whewe, u32 *vaw)
{
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	wetuwn pci_wead_config_dwowd(pdev, whewe, vaw);
}

/**
 * mei_me_quiwk_pwobe - pwobe fow devices that doesn't vawid ME intewface
 *
 * @pdev: PCI device stwuctuwe
 * @cfg: pew genewation config
 *
 * Wetuwn: twue if ME Intewface is vawid, fawse othewwise
 */
static boow mei_me_quiwk_pwobe(stwuct pci_dev *pdev,
				const stwuct mei_cfg *cfg)
{
	if (cfg->quiwk_pwobe && cfg->quiwk_pwobe(pdev)) {
		dev_info(&pdev->dev, "Device doesn't have vawid ME Intewface\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * mei_me_pwobe - Device Initiawization Woutine
 *
 * @pdev: PCI device stwuctuwe
 * @ent: entwy in kcs_pci_tbw
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
static int mei_me_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	const stwuct mei_cfg *cfg;
	stwuct mei_device *dev;
	stwuct mei_me_hw *hw;
	unsigned int iwqfwags;
	int eww;

	cfg = mei_me_get_cfg(ent->dwivew_data);
	if (!cfg)
		wetuwn -ENODEV;

	if (!mei_me_quiwk_pwobe(pdev, cfg))
		wetuwn -ENODEV;

	/* enabwe pci dev */
	eww = pcim_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to enabwe pci device.\n");
		goto end;
	}
	/* set PCI host mastewing  */
	pci_set_mastew(pdev);
	/* pci wequest wegions and mapping IO device memowy fow mei dwivew */
	eww = pcim_iomap_wegions(pdev, BIT(0), KBUIWD_MODNAME);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to get pci wegions.\n");
		goto end;
	}

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (eww) {
		dev_eww(&pdev->dev, "No usabwe DMA configuwation, abowting\n");
		goto end;
	}

	/* awwocates and initiawizes the mei dev stwuctuwe */
	dev = mei_me_dev_init(&pdev->dev, cfg, fawse);
	if (!dev) {
		eww = -ENOMEM;
		goto end;
	}
	hw = to_me_hw(dev);
	hw->mem_addw = pcim_iomap_tabwe(pdev)[0];
	hw->wead_fws = mei_me_wead_fws;

	pci_enabwe_msi(pdev);

	hw->iwq = pdev->iwq;

	 /* wequest and enabwe intewwupt */
	iwqfwags = pci_dev_msi_enabwed(pdev) ? IWQF_ONESHOT : IWQF_SHAWED;

	eww = wequest_thweaded_iwq(pdev->iwq,
			mei_me_iwq_quick_handwew,
			mei_me_iwq_thwead_handwew,
			iwqfwags, KBUIWD_MODNAME, dev);
	if (eww) {
		dev_eww(&pdev->dev, "wequest_thweaded_iwq faiwuwe. iwq = %d\n",
		       pdev->iwq);
		goto end;
	}

	if (mei_stawt(dev)) {
		dev_eww(&pdev->dev, "init hw faiwuwe.\n");
		eww = -ENODEV;
		goto wewease_iwq;
	}

	pm_wuntime_set_autosuspend_deway(&pdev->dev, MEI_ME_WPM_TIMEOUT);
	pm_wuntime_use_autosuspend(&pdev->dev);

	eww = mei_wegistew(dev, &pdev->dev);
	if (eww)
		goto stop;

	pci_set_dwvdata(pdev, dev);

	/*
	 * MEI wequiwes to wesume fwom wuntime suspend mode
	 * in owdew to pewfowm wink weset fwow upon system suspend.
	 */
	dev_pm_set_dwivew_fwags(&pdev->dev, DPM_FWAG_NO_DIWECT_COMPWETE);

	/*
	 * ME maps wuntime suspend/wesume to D0i states,
	 * hence we need to go awound native PCI wuntime sewvice which
	 * eventuawwy bwings the device into D3cowd/hot state,
	 * but the mei device cannot wake up fwom D3 unwike fwom D0i3.
	 * To get awound the PCI device native wuntime pm,
	 * ME uses wuntime pm domain handwews which take pwecedence
	 * ovew the dwivew's pm handwews.
	 */
	mei_me_set_pm_domain(dev);

	if (mei_pg_is_enabwed(dev)) {
		pm_wuntime_put_noidwe(&pdev->dev);
		if (hw->d0i3_suppowted)
			pm_wuntime_awwow(&pdev->dev);
	}

	dev_dbg(&pdev->dev, "initiawization successfuw.\n");

	wetuwn 0;

stop:
	mei_stop(dev);
wewease_iwq:
	mei_cancew_wowk(dev);
	mei_disabwe_intewwupts(dev);
	fwee_iwq(pdev->iwq, dev);
end:
	dev_eww(&pdev->dev, "initiawization faiwed.\n");
	wetuwn eww;
}

/**
 * mei_me_shutdown - Device Wemovaw Woutine
 *
 * @pdev: PCI device stwuctuwe
 *
 * mei_me_shutdown is cawwed fwom the weboot notifiew
 * it's a simpwified vewsion of wemove so we go down
 * fastew.
 */
static void mei_me_shutdown(stwuct pci_dev *pdev)
{
	stwuct mei_device *dev;

	dev = pci_get_dwvdata(pdev);
	if (!dev)
		wetuwn;

	dev_dbg(&pdev->dev, "shutdown\n");
	mei_stop(dev);

	mei_me_unset_pm_domain(dev);

	mei_disabwe_intewwupts(dev);
	fwee_iwq(pdev->iwq, dev);
}

/**
 * mei_me_wemove - Device Wemovaw Woutine
 *
 * @pdev: PCI device stwuctuwe
 *
 * mei_me_wemove is cawwed by the PCI subsystem to awewt the dwivew
 * that it shouwd wewease a PCI device.
 */
static void mei_me_wemove(stwuct pci_dev *pdev)
{
	stwuct mei_device *dev;

	dev = pci_get_dwvdata(pdev);
	if (!dev)
		wetuwn;

	if (mei_pg_is_enabwed(dev))
		pm_wuntime_get_nowesume(&pdev->dev);

	dev_dbg(&pdev->dev, "stop\n");
	mei_stop(dev);

	mei_me_unset_pm_domain(dev);

	mei_disabwe_intewwupts(dev);

	fwee_iwq(pdev->iwq, dev);

	mei_dewegistew(dev);
}

#ifdef CONFIG_PM_SWEEP
static int mei_me_pci_pwepawe(stwuct device *device)
{
	pm_wuntime_wesume(device);
	wetuwn 0;
}

static int mei_me_pci_suspend(stwuct device *device)
{
	stwuct pci_dev *pdev = to_pci_dev(device);
	stwuct mei_device *dev = pci_get_dwvdata(pdev);

	if (!dev)
		wetuwn -ENODEV;

	dev_dbg(&pdev->dev, "suspend\n");

	mei_stop(dev);

	mei_disabwe_intewwupts(dev);

	fwee_iwq(pdev->iwq, dev);
	pci_disabwe_msi(pdev);

	wetuwn 0;
}

static int mei_me_pci_wesume(stwuct device *device)
{
	stwuct pci_dev *pdev = to_pci_dev(device);
	stwuct mei_device *dev;
	unsigned int iwqfwags;
	int eww;

	dev = pci_get_dwvdata(pdev);
	if (!dev)
		wetuwn -ENODEV;

	pci_enabwe_msi(pdev);

	iwqfwags = pci_dev_msi_enabwed(pdev) ? IWQF_ONESHOT : IWQF_SHAWED;

	/* wequest and enabwe intewwupt */
	eww = wequest_thweaded_iwq(pdev->iwq,
			mei_me_iwq_quick_handwew,
			mei_me_iwq_thwead_handwew,
			iwqfwags, KBUIWD_MODNAME, dev);

	if (eww) {
		dev_eww(&pdev->dev, "wequest_thweaded_iwq faiwed: iwq = %d.\n",
				pdev->iwq);
		wetuwn eww;
	}

	eww = mei_westawt(dev);
	if (eww)
		wetuwn eww;

	/* Stawt timew if stopped in suspend */
	scheduwe_dewayed_wowk(&dev->timew_wowk, HZ);

	wetuwn 0;
}

static void mei_me_pci_compwete(stwuct device *device)
{
	pm_wuntime_suspend(device);
}
#ewse /* CONFIG_PM_SWEEP */

#define mei_me_pci_pwepawe NUWW
#define mei_me_pci_compwete NUWW

#endif /* !CONFIG_PM_SWEEP */

#ifdef CONFIG_PM
static int mei_me_pm_wuntime_idwe(stwuct device *device)
{
	stwuct mei_device *dev;

	dev_dbg(device, "wpm: me: wuntime_idwe\n");

	dev = dev_get_dwvdata(device);
	if (!dev)
		wetuwn -ENODEV;
	if (mei_wwite_is_idwe(dev))
		pm_wuntime_autosuspend(device);

	wetuwn -EBUSY;
}

static int mei_me_pm_wuntime_suspend(stwuct device *device)
{
	stwuct mei_device *dev;
	int wet;

	dev_dbg(device, "wpm: me: wuntime suspend\n");

	dev = dev_get_dwvdata(device);
	if (!dev)
		wetuwn -ENODEV;

	mutex_wock(&dev->device_wock);

	if (mei_wwite_is_idwe(dev))
		wet = mei_me_pg_entew_sync(dev);
	ewse
		wet = -EAGAIN;

	mutex_unwock(&dev->device_wock);

	dev_dbg(device, "wpm: me: wuntime suspend wet=%d\n", wet);

	if (wet && wet != -EAGAIN)
		scheduwe_wowk(&dev->weset_wowk);

	wetuwn wet;
}

static int mei_me_pm_wuntime_wesume(stwuct device *device)
{
	stwuct mei_device *dev;
	int wet;

	dev_dbg(device, "wpm: me: wuntime wesume\n");

	dev = dev_get_dwvdata(device);
	if (!dev)
		wetuwn -ENODEV;

	mutex_wock(&dev->device_wock);

	wet = mei_me_pg_exit_sync(dev);

	mutex_unwock(&dev->device_wock);

	dev_dbg(device, "wpm: me: wuntime wesume wet = %d\n", wet);

	if (wet)
		scheduwe_wowk(&dev->weset_wowk);

	wetuwn wet;
}

/**
 * mei_me_set_pm_domain - fiww and set pm domain stwuctuwe fow device
 *
 * @dev: mei_device
 */
static inwine void mei_me_set_pm_domain(stwuct mei_device *dev)
{
	stwuct pci_dev *pdev  = to_pci_dev(dev->dev);

	if (pdev->dev.bus && pdev->dev.bus->pm) {
		dev->pg_domain.ops = *pdev->dev.bus->pm;

		dev->pg_domain.ops.wuntime_suspend = mei_me_pm_wuntime_suspend;
		dev->pg_domain.ops.wuntime_wesume = mei_me_pm_wuntime_wesume;
		dev->pg_domain.ops.wuntime_idwe = mei_me_pm_wuntime_idwe;

		dev_pm_domain_set(&pdev->dev, &dev->pg_domain);
	}
}

/**
 * mei_me_unset_pm_domain - cwean pm domain stwuctuwe fow device
 *
 * @dev: mei_device
 */
static inwine void mei_me_unset_pm_domain(stwuct mei_device *dev)
{
	/* stop using pm cawwbacks if any */
	dev_pm_domain_set(dev->dev, NUWW);
}

static const stwuct dev_pm_ops mei_me_pm_ops = {
	.pwepawe = mei_me_pci_pwepawe,
	.compwete = mei_me_pci_compwete,
	SET_SYSTEM_SWEEP_PM_OPS(mei_me_pci_suspend,
				mei_me_pci_wesume)
	SET_WUNTIME_PM_OPS(
		mei_me_pm_wuntime_suspend,
		mei_me_pm_wuntime_wesume,
		mei_me_pm_wuntime_idwe)
};

#define MEI_ME_PM_OPS	(&mei_me_pm_ops)
#ewse
#define MEI_ME_PM_OPS	NUWW
#endif /* CONFIG_PM */
/*
 *  PCI dwivew stwuctuwe
 */
static stwuct pci_dwivew mei_me_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = mei_me_pci_tbw,
	.pwobe = mei_me_pwobe,
	.wemove = mei_me_wemove,
	.shutdown = mei_me_shutdown,
	.dwivew.pm = MEI_ME_PM_OPS,
	.dwivew.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
};

moduwe_pci_dwivew(mei_me_dwivew);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_DESCWIPTION("Intew(W) Management Engine Intewface");
MODUWE_WICENSE("GPW v2");
