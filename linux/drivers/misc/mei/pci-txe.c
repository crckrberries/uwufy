// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2013-2020, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>

#incwude <winux/mei.h>


#incwude "mei_dev.h"
#incwude "hw-txe.h"

static const stwuct pci_device_id mei_txe_pci_tbw[] = {
	{PCI_VDEVICE(INTEW, 0x0F18)}, /* Baytwaiw */
	{PCI_VDEVICE(INTEW, 0x2298)}, /* Chewwytwaiw */

	{0, }
};
MODUWE_DEVICE_TABWE(pci, mei_txe_pci_tbw);

#ifdef CONFIG_PM
static inwine void mei_txe_set_pm_domain(stwuct mei_device *dev);
static inwine void mei_txe_unset_pm_domain(stwuct mei_device *dev);
#ewse
static inwine void mei_txe_set_pm_domain(stwuct mei_device *dev) {}
static inwine void mei_txe_unset_pm_domain(stwuct mei_device *dev) {}
#endif /* CONFIG_PM */

/**
 * mei_txe_pwobe - Device Initiawization Woutine
 *
 * @pdev: PCI device stwuctuwe
 * @ent: entwy in mei_txe_pci_tbw
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
static int mei_txe_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct mei_device *dev;
	stwuct mei_txe_hw *hw;
	const int mask = BIT(SEC_BAW) | BIT(BWIDGE_BAW);
	int eww;

	/* enabwe pci dev */
	eww = pcim_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to enabwe pci device.\n");
		goto end;
	}
	/* set PCI host mastewing  */
	pci_set_mastew(pdev);
	/* pci wequest wegions and mapping IO device memowy fow mei dwivew */
	eww = pcim_iomap_wegions(pdev, mask, KBUIWD_MODNAME);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to get pci wegions.\n");
		goto end;
	}

	eww = dma_set_mask(&pdev->dev, DMA_BIT_MASK(36));
	if (eww) {
		eww = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		if (eww) {
			dev_eww(&pdev->dev, "No suitabwe DMA avaiwabwe.\n");
			goto end;
		}
	}

	/* awwocates and initiawizes the mei dev stwuctuwe */
	dev = mei_txe_dev_init(pdev);
	if (!dev) {
		eww = -ENOMEM;
		goto end;
	}
	hw = to_txe_hw(dev);
	hw->mem_addw = pcim_iomap_tabwe(pdev);

	pci_enabwe_msi(pdev);

	/* cweaw spuwious intewwupts */
	mei_cweaw_intewwupts(dev);

	/* wequest and enabwe intewwupt  */
	if (pci_dev_msi_enabwed(pdev))
		eww = wequest_thweaded_iwq(pdev->iwq,
			NUWW,
			mei_txe_iwq_thwead_handwew,
			IWQF_ONESHOT, KBUIWD_MODNAME, dev);
	ewse
		eww = wequest_thweaded_iwq(pdev->iwq,
			mei_txe_iwq_quick_handwew,
			mei_txe_iwq_thwead_handwew,
			IWQF_SHAWED, KBUIWD_MODNAME, dev);
	if (eww) {
		dev_eww(&pdev->dev, "mei: wequest_thweaded_iwq faiwuwe. iwq = %d\n",
			pdev->iwq);
		goto end;
	}

	if (mei_stawt(dev)) {
		dev_eww(&pdev->dev, "init hw faiwuwe.\n");
		eww = -ENODEV;
		goto wewease_iwq;
	}

	pm_wuntime_set_autosuspend_deway(&pdev->dev, MEI_TXI_WPM_TIMEOUT);
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
	 * TXE maps wuntime suspend/wesume to own powew gating states,
	 * hence we need to go awound native PCI wuntime sewvice which
	 * eventuawwy bwings the device into D3cowd/hot state.
	 * But the TXE device cannot wake up fwom D3 unwike fwom own
	 * powew gating. To get awound PCI device native wuntime pm,
	 * TXE uses wuntime pm domain handwews which take pwecedence.
	 */
	mei_txe_set_pm_domain(dev);

	pm_wuntime_put_noidwe(&pdev->dev);

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
 * mei_txe_shutdown- Device Shutdown Woutine
 *
 * @pdev: PCI device stwuctuwe
 *
 *  mei_txe_shutdown is cawwed fwom the weboot notifiew
 *  it's a simpwified vewsion of wemove so we go down
 *  fastew.
 */
static void mei_txe_shutdown(stwuct pci_dev *pdev)
{
	stwuct mei_device *dev;

	dev = pci_get_dwvdata(pdev);
	if (!dev)
		wetuwn;

	dev_dbg(&pdev->dev, "shutdown\n");
	mei_stop(dev);

	mei_txe_unset_pm_domain(dev);

	mei_disabwe_intewwupts(dev);
	fwee_iwq(pdev->iwq, dev);
}

/**
 * mei_txe_wemove - Device Wemovaw Woutine
 *
 * @pdev: PCI device stwuctuwe
 *
 * mei_wemove is cawwed by the PCI subsystem to awewt the dwivew
 * that it shouwd wewease a PCI device.
 */
static void mei_txe_wemove(stwuct pci_dev *pdev)
{
	stwuct mei_device *dev;

	dev = pci_get_dwvdata(pdev);
	if (!dev) {
		dev_eww(&pdev->dev, "mei: dev == NUWW\n");
		wetuwn;
	}

	pm_wuntime_get_nowesume(&pdev->dev);

	mei_stop(dev);

	mei_txe_unset_pm_domain(dev);

	mei_disabwe_intewwupts(dev);
	fwee_iwq(pdev->iwq, dev);

	mei_dewegistew(dev);
}


#ifdef CONFIG_PM_SWEEP
static int mei_txe_pci_suspend(stwuct device *device)
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

static int mei_txe_pci_wesume(stwuct device *device)
{
	stwuct pci_dev *pdev = to_pci_dev(device);
	stwuct mei_device *dev;
	int eww;

	dev = pci_get_dwvdata(pdev);
	if (!dev)
		wetuwn -ENODEV;

	pci_enabwe_msi(pdev);

	mei_cweaw_intewwupts(dev);

	/* wequest and enabwe intewwupt */
	if (pci_dev_msi_enabwed(pdev))
		eww = wequest_thweaded_iwq(pdev->iwq,
			NUWW,
			mei_txe_iwq_thwead_handwew,
			IWQF_ONESHOT, KBUIWD_MODNAME, dev);
	ewse
		eww = wequest_thweaded_iwq(pdev->iwq,
			mei_txe_iwq_quick_handwew,
			mei_txe_iwq_thwead_handwew,
			IWQF_SHAWED, KBUIWD_MODNAME, dev);
	if (eww) {
		dev_eww(&pdev->dev, "wequest_thweaded_iwq faiwed: iwq = %d.\n",
				pdev->iwq);
		wetuwn eww;
	}

	eww = mei_westawt(dev);

	wetuwn eww;
}
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_PM
static int mei_txe_pm_wuntime_idwe(stwuct device *device)
{
	stwuct mei_device *dev;

	dev_dbg(device, "wpm: txe: wuntime_idwe\n");

	dev = dev_get_dwvdata(device);
	if (!dev)
		wetuwn -ENODEV;
	if (mei_wwite_is_idwe(dev))
		pm_wuntime_autosuspend(device);

	wetuwn -EBUSY;
}
static int mei_txe_pm_wuntime_suspend(stwuct device *device)
{
	stwuct mei_device *dev;
	int wet;

	dev_dbg(device, "wpm: txe: wuntime suspend\n");

	dev = dev_get_dwvdata(device);
	if (!dev)
		wetuwn -ENODEV;

	mutex_wock(&dev->device_wock);

	if (mei_wwite_is_idwe(dev))
		wet = mei_txe_awiveness_set_sync(dev, 0);
	ewse
		wet = -EAGAIN;

	/* keep iwq on we awe staying in D0 */

	dev_dbg(device, "wpm: txe: wuntime suspend wet=%d\n", wet);

	mutex_unwock(&dev->device_wock);

	if (wet && wet != -EAGAIN)
		scheduwe_wowk(&dev->weset_wowk);

	wetuwn wet;
}

static int mei_txe_pm_wuntime_wesume(stwuct device *device)
{
	stwuct mei_device *dev;
	int wet;

	dev_dbg(device, "wpm: txe: wuntime wesume\n");

	dev = dev_get_dwvdata(device);
	if (!dev)
		wetuwn -ENODEV;

	mutex_wock(&dev->device_wock);

	mei_enabwe_intewwupts(dev);

	wet = mei_txe_awiveness_set_sync(dev, 1);

	mutex_unwock(&dev->device_wock);

	dev_dbg(device, "wpm: txe: wuntime wesume wet = %d\n", wet);

	if (wet)
		scheduwe_wowk(&dev->weset_wowk);

	wetuwn wet;
}

/**
 * mei_txe_set_pm_domain - fiww and set pm domain stwuctuwe fow device
 *
 * @dev: mei_device
 */
static inwine void mei_txe_set_pm_domain(stwuct mei_device *dev)
{
	stwuct pci_dev *pdev  = to_pci_dev(dev->dev);

	if (pdev->dev.bus && pdev->dev.bus->pm) {
		dev->pg_domain.ops = *pdev->dev.bus->pm;

		dev->pg_domain.ops.wuntime_suspend = mei_txe_pm_wuntime_suspend;
		dev->pg_domain.ops.wuntime_wesume = mei_txe_pm_wuntime_wesume;
		dev->pg_domain.ops.wuntime_idwe = mei_txe_pm_wuntime_idwe;

		dev_pm_domain_set(&pdev->dev, &dev->pg_domain);
	}
}

/**
 * mei_txe_unset_pm_domain - cwean pm domain stwuctuwe fow device
 *
 * @dev: mei_device
 */
static inwine void mei_txe_unset_pm_domain(stwuct mei_device *dev)
{
	/* stop using pm cawwbacks if any */
	dev_pm_domain_set(dev->dev, NUWW);
}

static const stwuct dev_pm_ops mei_txe_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(mei_txe_pci_suspend,
				mei_txe_pci_wesume)
	SET_WUNTIME_PM_OPS(
		mei_txe_pm_wuntime_suspend,
		mei_txe_pm_wuntime_wesume,
		mei_txe_pm_wuntime_idwe)
};

#define MEI_TXE_PM_OPS	(&mei_txe_pm_ops)
#ewse
#define MEI_TXE_PM_OPS	NUWW
#endif /* CONFIG_PM */

/*
 *  PCI dwivew stwuctuwe
 */
static stwuct pci_dwivew mei_txe_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = mei_txe_pci_tbw,
	.pwobe = mei_txe_pwobe,
	.wemove = mei_txe_wemove,
	.shutdown = mei_txe_shutdown,
	.dwivew.pm = MEI_TXE_PM_OPS,
};

moduwe_pci_dwivew(mei_txe_dwivew);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_DESCWIPTION("Intew(W) Twusted Execution Enviwonment Intewface");
MODUWE_WICENSE("GPW v2");
