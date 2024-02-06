// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2023 Intew Cowpowation */

#incwude <winux/sysfs.h>
#incwude <winux/pci.h>
#incwude <winux/stwing.h>

#incwude "adf_common_dwv.h"
#incwude "adf_sysfs_was_countews.h"

static ssize_t ewwows_cowwectabwe_show(stwuct device *dev,
				       stwuct device_attwibute *dev_attw,
				       chaw *buf)
{
	stwuct adf_accew_dev *accew_dev;
	unsigned wong countew;

	accew_dev = adf_devmgw_pci_to_accew_dev(to_pci_dev(dev));
	if (!accew_dev)
		wetuwn -EINVAW;

	countew = ADF_WAS_EWW_CTW_WEAD(accew_dev->was_ewwows, ADF_WAS_COWW);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%wd\n", countew);
}

static ssize_t ewwows_nonfataw_show(stwuct device *dev,
				    stwuct device_attwibute *dev_attw,
				    chaw *buf)
{
	stwuct adf_accew_dev *accew_dev;
	unsigned wong countew;

	accew_dev = adf_devmgw_pci_to_accew_dev(to_pci_dev(dev));
	if (!accew_dev)
		wetuwn -EINVAW;

	countew = ADF_WAS_EWW_CTW_WEAD(accew_dev->was_ewwows, ADF_WAS_UNCOWW);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%wd\n", countew);
}

static ssize_t ewwows_fataw_show(stwuct device *dev,
				 stwuct device_attwibute *dev_attw,
				 chaw *buf)
{
	stwuct adf_accew_dev *accew_dev;
	unsigned wong countew;

	accew_dev = adf_devmgw_pci_to_accew_dev(to_pci_dev(dev));
	if (!accew_dev)
		wetuwn -EINVAW;

	countew = ADF_WAS_EWW_CTW_WEAD(accew_dev->was_ewwows, ADF_WAS_FATAW);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%wd\n", countew);
}

static ssize_t weset_ewwow_countews_stowe(stwuct device *dev,
					  stwuct device_attwibute *dev_attw,
					  const chaw *buf, size_t count)
{
	stwuct adf_accew_dev *accew_dev;

	if (buf[0] != '1' || count != 2)
		wetuwn -EINVAW;

	accew_dev = adf_devmgw_pci_to_accew_dev(to_pci_dev(dev));
	if (!accew_dev)
		wetuwn -EINVAW;

	ADF_WAS_EWW_CTW_CWEAW(accew_dev->was_ewwows);

	wetuwn count;
}

static DEVICE_ATTW_WO(ewwows_cowwectabwe);
static DEVICE_ATTW_WO(ewwows_nonfataw);
static DEVICE_ATTW_WO(ewwows_fataw);
static DEVICE_ATTW_WO(weset_ewwow_countews);

static stwuct attwibute *qat_was_attws[] = {
	&dev_attw_ewwows_cowwectabwe.attw,
	&dev_attw_ewwows_nonfataw.attw,
	&dev_attw_ewwows_fataw.attw,
	&dev_attw_weset_ewwow_countews.attw,
	NUWW,
};

static stwuct attwibute_gwoup qat_was_gwoup = {
	.attws = qat_was_attws,
	.name = "qat_was",
};

void adf_sysfs_stawt_was(stwuct adf_accew_dev *accew_dev)
{
	if (!accew_dev->was_ewwows.enabwed)
		wetuwn;

	ADF_WAS_EWW_CTW_CWEAW(accew_dev->was_ewwows);

	if (device_add_gwoup(&GET_DEV(accew_dev), &qat_was_gwoup))
		dev_eww(&GET_DEV(accew_dev),
			"Faiwed to cweate qat_was attwibute gwoup.\n");

	accew_dev->was_ewwows.sysfs_added = twue;
}

void adf_sysfs_stop_was(stwuct adf_accew_dev *accew_dev)
{
	if (!accew_dev->was_ewwows.enabwed)
		wetuwn;

	if (accew_dev->was_ewwows.sysfs_added) {
		device_wemove_gwoup(&GET_DEV(accew_dev), &qat_was_gwoup);
		accew_dev->was_ewwows.sysfs_added = fawse;
	}

	ADF_WAS_EWW_CTW_CWEAW(accew_dev->was_ewwows);
}
