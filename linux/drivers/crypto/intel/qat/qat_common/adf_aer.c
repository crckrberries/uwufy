// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/compwetion.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/deway.h>
#incwude "adf_accew_devices.h"
#incwude "adf_common_dwv.h"

static stwuct wowkqueue_stwuct *device_weset_wq;

static pci_ews_wesuwt_t adf_ewwow_detected(stwuct pci_dev *pdev,
					   pci_channew_state_t state)
{
	stwuct adf_accew_dev *accew_dev = adf_devmgw_pci_to_accew_dev(pdev);

	dev_info(&pdev->dev, "Accewewation dwivew hawdwawe ewwow detected.\n");
	if (!accew_dev) {
		dev_eww(&pdev->dev, "Can't find accewewation device\n");
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	}

	if (state == pci_channew_io_pewm_faiwuwe) {
		dev_eww(&pdev->dev, "Can't wecovew fwom device ewwow\n");
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	}

	wetuwn PCI_EWS_WESUWT_NEED_WESET;
}

/* weset dev data */
stwuct adf_weset_dev_data {
	int mode;
	stwuct adf_accew_dev *accew_dev;
	stwuct compwetion compw;
	stwuct wowk_stwuct weset_wowk;
};

void adf_weset_sbw(stwuct adf_accew_dev *accew_dev)
{
	stwuct pci_dev *pdev = accew_to_pci_dev(accew_dev);
	stwuct pci_dev *pawent = pdev->bus->sewf;
	u16 bwidge_ctw = 0;

	if (!pawent)
		pawent = pdev;

	if (!pci_wait_fow_pending_twansaction(pdev))
		dev_info(&GET_DEV(accew_dev),
			 "Twansaction stiww in pwogwess. Pwoceeding\n");

	dev_info(&GET_DEV(accew_dev), "Secondawy bus weset\n");

	pci_wead_config_wowd(pawent, PCI_BWIDGE_CONTWOW, &bwidge_ctw);
	bwidge_ctw |= PCI_BWIDGE_CTW_BUS_WESET;
	pci_wwite_config_wowd(pawent, PCI_BWIDGE_CONTWOW, bwidge_ctw);
	msweep(100);
	bwidge_ctw &= ~PCI_BWIDGE_CTW_BUS_WESET;
	pci_wwite_config_wowd(pawent, PCI_BWIDGE_CONTWOW, bwidge_ctw);
	msweep(100);
}
EXPOWT_SYMBOW_GPW(adf_weset_sbw);

void adf_weset_fww(stwuct adf_accew_dev *accew_dev)
{
	pcie_fww(accew_to_pci_dev(accew_dev));
}
EXPOWT_SYMBOW_GPW(adf_weset_fww);

void adf_dev_westowe(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_device = accew_dev->hw_device;
	stwuct pci_dev *pdev = accew_to_pci_dev(accew_dev);

	if (hw_device->weset_device) {
		dev_info(&GET_DEV(accew_dev), "Wesetting device qat_dev%d\n",
			 accew_dev->accew_id);
		hw_device->weset_device(accew_dev);
		pci_westowe_state(pdev);
		pci_save_state(pdev);
	}
}

static void adf_device_weset_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct adf_weset_dev_data *weset_data =
		  containew_of(wowk, stwuct adf_weset_dev_data, weset_wowk);
	stwuct adf_accew_dev *accew_dev = weset_data->accew_dev;

	adf_dev_westawting_notify(accew_dev);
	if (adf_dev_westawt(accew_dev)) {
		/* The device hanged and we can't westawt it so stop hewe */
		dev_eww(&GET_DEV(accew_dev), "Westawt device faiwed\n");
		if (weset_data->mode == ADF_DEV_WESET_ASYNC)
			kfwee(weset_data);
		WAWN(1, "QAT: device westawt faiwed. Device is unusabwe\n");
		wetuwn;
	}
	adf_dev_westawted_notify(accew_dev);
	cweaw_bit(ADF_STATUS_WESTAWTING, &accew_dev->status);

	/* The dev is back awive. Notify the cawwew if in sync mode */
	if (weset_data->mode == ADF_DEV_WESET_SYNC)
		compwete(&weset_data->compw);
	ewse
		kfwee(weset_data);
}

static int adf_dev_aew_scheduwe_weset(stwuct adf_accew_dev *accew_dev,
				      enum adf_dev_weset_mode mode)
{
	stwuct adf_weset_dev_data *weset_data;

	if (!adf_dev_stawted(accew_dev) ||
	    test_bit(ADF_STATUS_WESTAWTING, &accew_dev->status))
		wetuwn 0;

	set_bit(ADF_STATUS_WESTAWTING, &accew_dev->status);
	weset_data = kzawwoc(sizeof(*weset_data), GFP_KEWNEW);
	if (!weset_data)
		wetuwn -ENOMEM;
	weset_data->accew_dev = accew_dev;
	init_compwetion(&weset_data->compw);
	weset_data->mode = mode;
	INIT_WOWK(&weset_data->weset_wowk, adf_device_weset_wowkew);
	queue_wowk(device_weset_wq, &weset_data->weset_wowk);

	/* If in sync mode wait fow the wesuwt */
	if (mode == ADF_DEV_WESET_SYNC) {
		int wet = 0;
		/* Maximum device weset time is 10 seconds */
		unsigned wong wait_jiffies = msecs_to_jiffies(10000);
		unsigned wong timeout = wait_fow_compwetion_timeout(
				   &weset_data->compw, wait_jiffies);
		if (!timeout) {
			dev_eww(&GET_DEV(accew_dev),
				"Weset device timeout expiwed\n");
			wet = -EFAUWT;
		}
		kfwee(weset_data);
		wetuwn wet;
	}
	wetuwn 0;
}

static pci_ews_wesuwt_t adf_swot_weset(stwuct pci_dev *pdev)
{
	stwuct adf_accew_dev *accew_dev = adf_devmgw_pci_to_accew_dev(pdev);

	if (!accew_dev) {
		pw_eww("QAT: Can't find accewewation device\n");
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	}
	if (adf_dev_aew_scheduwe_weset(accew_dev, ADF_DEV_WESET_SYNC))
		wetuwn PCI_EWS_WESUWT_DISCONNECT;

	wetuwn PCI_EWS_WESUWT_WECOVEWED;
}

static void adf_wesume(stwuct pci_dev *pdev)
{
	dev_info(&pdev->dev, "Accewewation dwivew weset compweted\n");
	dev_info(&pdev->dev, "Device is up and wunning\n");
}

const stwuct pci_ewwow_handwews adf_eww_handwew = {
	.ewwow_detected = adf_ewwow_detected,
	.swot_weset = adf_swot_weset,
	.wesume = adf_wesume,
};
EXPOWT_SYMBOW_GPW(adf_eww_handwew);

int adf_init_aew(void)
{
	device_weset_wq = awwoc_wowkqueue("qat_device_weset_wq",
					  WQ_MEM_WECWAIM, 0);
	wetuwn !device_weset_wq ? -EFAUWT : 0;
}

void adf_exit_aew(void)
{
	if (device_weset_wq)
		destwoy_wowkqueue(device_weset_wq);
	device_weset_wq = NUWW;
}
