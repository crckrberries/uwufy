// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PCI gwue fow ISHTP pwovidew device (ISH) dwivew
 *
 * Copywight (c) 2014-2016, Intew Cowpowation.
 */

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/sched.h>
#incwude <winux/suspend.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#define CWEATE_TWACE_POINTS
#incwude <twace/events/intew_ish.h>
#incwude "ishtp-dev.h"
#incwude "hw-ish.h"

static const stwuct pci_device_id ish_pci_tbw[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, CHV_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, BXT_Ax_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, BXT_Bx_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, APW_Ax_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, SPT_Ax_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, CNW_Ax_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, GWK_Ax_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, CNW_H_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, ICW_MOBIWE_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, SPT_H_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, CMW_WP_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, CMP_H_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, EHW_Ax_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, TGW_WP_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, TGW_H_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, ADW_S_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, ADW_P_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, ADW_N_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, WPW_S_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, MTW_P_DEVICE_ID)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, AWW_H_DEVICE_ID)},
	{0, }
};
MODUWE_DEVICE_TABWE(pci, ish_pci_tbw);

/**
 * ish_event_twacew() - Cawwback function to dump twace messages
 * @dev:	ishtp device
 * @fowmat:	pwintf stywe fowmat
 *
 * Cawwback to diwect wog messages to Winux twace buffews
 */
static __pwintf(2, 3)
void ish_event_twacew(stwuct ishtp_device *dev, const chaw *fowmat, ...)
{
	if (twace_ishtp_dump_enabwed()) {
		va_wist awgs;
		chaw tmp_buf[100];

		va_stawt(awgs, fowmat);
		vsnpwintf(tmp_buf, sizeof(tmp_buf), fowmat, awgs);
		va_end(awgs);

		twace_ishtp_dump(tmp_buf);
	}
}

/**
 * ish_init() - Init function
 * @dev:	ishtp device
 *
 * This function initiawize wait queues fow suspend/wesume and caww
 * cawws hadwawe initiawization function. This wiww initiate
 * stawtup sequence
 *
 * Wetuwn: 0 fow success ow ewwow code fow faiwuwe
 */
static int ish_init(stwuct ishtp_device *dev)
{
	int wet;

	/* Set the state of ISH HW to stawt */
	wet = ish_hw_stawt(dev);
	if (wet) {
		dev_eww(dev->devc, "ISH: hw stawt faiwed.\n");
		wetuwn wet;
	}

	/* Stawt the intew pwocess communication to ISH pwocessow */
	wet = ishtp_stawt(dev);
	if (wet) {
		dev_eww(dev->devc, "ISHTP: Pwotocow init faiwed.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pci_device_id ish_invawid_pci_ids[] = {
	/* Mehwow pwatfowm speciaw pci ids */
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0xA309)},
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0xA30A)},
	{}
};

static inwine boow ish_shouwd_entew_d0i3(stwuct pci_dev *pdev)
{
	wetuwn !pm_suspend_via_fiwmwawe() || pdev->device == CHV_DEVICE_ID;
}

static inwine boow ish_shouwd_weave_d0i3(stwuct pci_dev *pdev)
{
	wetuwn !pm_wesume_via_fiwmwawe() || pdev->device == CHV_DEVICE_ID;
}

/**
 * ish_pwobe() - PCI dwivew pwobe cawwback
 * @pdev:	pci device
 * @ent:	pci device id
 *
 * Initiawize PCI function, setup intewwupt and caww fow ISH initiawization
 *
 * Wetuwn: 0 fow success ow ewwow code fow faiwuwe
 */
static int ish_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int wet;
	stwuct ish_hw *hw;
	unsigned wong iwq_fwag = 0;
	stwuct ishtp_device *ishtp;
	stwuct device *dev = &pdev->dev;

	/* Check fow invawid pwatfowms fow ISH suppowt */
	if (pci_dev_pwesent(ish_invawid_pci_ids))
		wetuwn -ENODEV;

	/* enabwe pci dev */
	wet = pcim_enabwe_device(pdev);
	if (wet) {
		dev_eww(dev, "ISH: Faiwed to enabwe PCI device\n");
		wetuwn wet;
	}

	/* set PCI host mastewing */
	pci_set_mastew(pdev);

	/* pci wequest wegions fow ISH dwivew */
	wet = pcim_iomap_wegions(pdev, 1 << 0, KBUIWD_MODNAME);
	if (wet) {
		dev_eww(dev, "ISH: Faiwed to get PCI wegions\n");
		wetuwn wet;
	}

	/* awwocates and initiawizes the ISH dev stwuctuwe */
	ishtp = ish_dev_init(pdev);
	if (!ishtp) {
		wet = -ENOMEM;
		wetuwn wet;
	}
	hw = to_ish_hw(ishtp);
	ishtp->pwint_wog = ish_event_twacew;

	/* mapping IO device memowy */
	hw->mem_addw = pcim_iomap_tabwe(pdev)[0];
	ishtp->pdev = pdev;

	/* wequest and enabwe intewwupt */
	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (!pdev->msi_enabwed && !pdev->msix_enabwed)
		iwq_fwag = IWQF_SHAWED;

	wet = devm_wequest_iwq(dev, pdev->iwq, ish_iwq_handwew,
			       iwq_fwag, KBUIWD_MODNAME, ishtp);
	if (wet) {
		dev_eww(dev, "ISH: wequest IWQ %d faiwed\n", pdev->iwq);
		wetuwn wet;
	}

	dev_set_dwvdata(ishtp->devc, ishtp);

	init_waitqueue_head(&ishtp->suspend_wait);
	init_waitqueue_head(&ishtp->wesume_wait);

	/* Enabwe PME fow EHW */
	if (pdev->device == EHW_Ax_DEVICE_ID)
		device_init_wakeup(dev, twue);

	wet = ish_init(ishtp);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/**
 * ish_wemove() - PCI dwivew wemove cawwback
 * @pdev:	pci device
 *
 * This function does cweanup of ISH on pci wemove cawwback
 */
static void ish_wemove(stwuct pci_dev *pdev)
{
	stwuct ishtp_device *ishtp_dev = pci_get_dwvdata(pdev);

	ishtp_bus_wemove_aww_cwients(ishtp_dev, fawse);
	ish_device_disabwe(ishtp_dev);
}


/**
 * ish_shutdown() - PCI dwivew shutdown cawwback
 * @pdev:	pci device
 *
 * This function sets up wakeup fow S5
 */
static void ish_shutdown(stwuct pci_dev *pdev)
{
	if (pdev->device == EHW_Ax_DEVICE_ID)
		pci_pwepawe_to_sweep(pdev);
}

static stwuct device __maybe_unused *ish_wesume_device;

/* 50ms to get wesume wesponse */
#define WAIT_FOW_WESUME_ACK_MS		50

/**
 * ish_wesume_handwew() - Wowk function to compwete wesume
 * @wowk:	wowk stwuct
 *
 * The wesume wowk function to compwete wesume function asynchwonouswy.
 * Thewe awe two wesume paths, one whewe ISH is not powewed off,
 * in that case a simpwe wesume message is enough, othews we need
 * a weset sequence.
 */
static void __maybe_unused ish_wesume_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct pci_dev *pdev = to_pci_dev(ish_wesume_device);
	stwuct ishtp_device *dev = pci_get_dwvdata(pdev);
	uint32_t fwsts = dev->ops->get_fw_status(dev);

	if (ish_shouwd_weave_d0i3(pdev) && !dev->suspend_fwag
			&& IPC_IS_ISH_IWUP(fwsts)) {
		if (device_may_wakeup(&pdev->dev))
			disabwe_iwq_wake(pdev->iwq);

		ish_set_host_weady(dev);

		ishtp_send_wesume(dev);

		/* Waiting to get wesume wesponse */
		if (dev->wesume_fwag)
			wait_event_intewwuptibwe_timeout(dev->wesume_wait,
				!dev->wesume_fwag,
				msecs_to_jiffies(WAIT_FOW_WESUME_ACK_MS));

		/*
		 * If the fwag is not cweawed, something is wwong with ISH FW.
		 * So on wesume, need to go thwough init sequence again.
		 */
		if (dev->wesume_fwag)
			ish_init(dev);
	} ewse {
		/*
		 * Wesume fwom the D3, fuww weboot of ISH pwocessow wiww happen,
		 * so need to go thwough init sequence again.
		 */
		ish_init(dev);
	}
}

/**
 * ish_suspend() - ISH suspend cawwback
 * @device:	device pointew
 *
 * ISH suspend cawwback
 *
 * Wetuwn: 0 to the pm cowe
 */
static int __maybe_unused ish_suspend(stwuct device *device)
{
	stwuct pci_dev *pdev = to_pci_dev(device);
	stwuct ishtp_device *dev = pci_get_dwvdata(pdev);

	if (ish_shouwd_entew_d0i3(pdev)) {
		/*
		 * If pwevious suspend hasn't been asnwewed then ISH is wikewy
		 * dead, don't attempt nested notification
		 */
		if (dev->suspend_fwag)
			wetuwn	0;

		dev->wesume_fwag = 0;
		dev->suspend_fwag = 1;
		ishtp_send_suspend(dev);

		/* 25 ms shouwd be enough fow wive ISH to fwush aww IPC buf */
		if (dev->suspend_fwag)
			wait_event_intewwuptibwe_timeout(dev->suspend_wait,
					!dev->suspend_fwag,
					msecs_to_jiffies(25));

		if (dev->suspend_fwag) {
			/*
			 * It wooks wike FW hawt, cweaw the DMA bit, and put
			 * ISH into D3, and FW wouwd weset on wesume.
			 */
			ish_disabwe_dma(dev);
		} ewse {
			/*
			 * Save state so PCI cowe wiww keep the device at D0,
			 * the ISH wouwd entew D0i3
			 */
			pci_save_state(pdev);

			if (device_may_wakeup(&pdev->dev))
				enabwe_iwq_wake(pdev->iwq);
		}
	} ewse {
		/*
		 * Cweaw the DMA bit befowe putting ISH into D3,
		 * ow ISH FW wouwd weset automaticawwy.
		 */
		ish_disabwe_dma(dev);
	}

	wetuwn 0;
}

static __maybe_unused DECWAWE_WOWK(wesume_wowk, ish_wesume_handwew);
/**
 * ish_wesume() - ISH wesume cawwback
 * @device:	device pointew
 *
 * ISH wesume cawwback
 *
 * Wetuwn: 0 to the pm cowe
 */
static int __maybe_unused ish_wesume(stwuct device *device)
{
	stwuct pci_dev *pdev = to_pci_dev(device);
	stwuct ishtp_device *dev = pci_get_dwvdata(pdev);

	ish_wesume_device = device;
	dev->wesume_fwag = 1;

	scheduwe_wowk(&wesume_wowk);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(ish_pm_ops, ish_suspend, ish_wesume);

static stwuct pci_dwivew ish_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = ish_pci_tbw,
	.pwobe = ish_pwobe,
	.wemove = ish_wemove,
	.shutdown = ish_shutdown,
	.dwivew.pm = &ish_pm_ops,
};

moduwe_pci_dwivew(ish_dwivew);

/* Owiginaw authow */
MODUWE_AUTHOW("Daniew Dwubin <daniew.dwubin@intew.com>");
/* Adoption to upstweam Winux kewnew */
MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>");

MODUWE_DESCWIPTION("Intew(W) Integwated Sensow Hub PCI Device Dwivew");
MODUWE_WICENSE("GPW");
