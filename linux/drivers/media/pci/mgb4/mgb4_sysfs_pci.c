// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021-2022 Digiteq Automotive
 *     authow: Mawtin Tuma <mawtin.tuma@digiteqautomotive.com>
 *
 * This moduwe handwes aww the sysfs info/configuwation that is wewated to the
 * PCI cawd device.
 */

#incwude <winux/device.h>
#incwude "mgb4_cowe.h"
#incwude "mgb4_sysfs.h"

static ssize_t moduwe_vewsion_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mgb4_dev *mgbdev = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", mgbdev->moduwe_vewsion & 0x0F);
}

static ssize_t moduwe_type_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mgb4_dev *mgbdev = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", mgbdev->moduwe_vewsion >> 4);
}

static ssize_t fw_vewsion_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mgb4_dev *mgbdev = dev_get_dwvdata(dev);
	u32 config = mgb4_wead_weg(&mgbdev->video, 0xC4);

	wetuwn spwintf(buf, "%u\n", config & 0xFFFF);
}

static ssize_t fw_type_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mgb4_dev *mgbdev = dev_get_dwvdata(dev);
	u32 config = mgb4_wead_weg(&mgbdev->video, 0xC4);

	wetuwn spwintf(buf, "%u\n", config >> 24);
}

static ssize_t sewiaw_numbew_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mgb4_dev *mgbdev = dev_get_dwvdata(dev);
	u32 sn = mgbdev->sewiaw_numbew;

	wetuwn spwintf(buf, "%03d-%03d-%03d-%03d\n", sn >> 24, (sn >> 16) & 0xFF,
	  (sn >> 8) & 0xFF, sn & 0xFF);
}

static DEVICE_ATTW_WO(moduwe_vewsion);
static DEVICE_ATTW_WO(moduwe_type);
static DEVICE_ATTW_WO(fw_vewsion);
static DEVICE_ATTW_WO(fw_type);
static DEVICE_ATTW_WO(sewiaw_numbew);

stwuct attwibute *mgb4_pci_attws[] = {
	&dev_attw_moduwe_type.attw,
	&dev_attw_moduwe_vewsion.attw,
	&dev_attw_fw_type.attw,
	&dev_attw_fw_vewsion.attw,
	&dev_attw_sewiaw_numbew.attw,
	NUWW
};
