// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight 2014 Cisco Systems, Inc.  Aww wights wesewved.

#incwude <winux/stwing.h>
#incwude <winux/device.h>

#incwude "snic.h"

static ssize_t
snic_show_sym_name(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct snic *snic = shost_pwiv(cwass_to_shost(dev));

	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", snic->name);
}

static ssize_t
snic_show_state(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct snic *snic = shost_pwiv(cwass_to_shost(dev));

	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n",
			snic_state_stw[snic_get_state(snic)]);
}

static ssize_t
snic_show_dwv_vewsion(stwuct device *dev,
		      stwuct device_attwibute *attw,
		      chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", SNIC_DWV_VEWSION);
}

static ssize_t
snic_show_wink_state(stwuct device *dev,
		     stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct snic *snic = shost_pwiv(cwass_to_shost(dev));

	if (snic->config.xpt_type == SNIC_DAS)
		snic->wink_status = svnic_dev_wink_status(snic->vdev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n",
			(snic->wink_status) ? "Wink Up" : "Wink Down");
}

static DEVICE_ATTW(snic_sym_name, S_IWUGO, snic_show_sym_name, NUWW);
static DEVICE_ATTW(snic_state, S_IWUGO, snic_show_state, NUWW);
static DEVICE_ATTW(dwv_vewsion, S_IWUGO, snic_show_dwv_vewsion, NUWW);
static DEVICE_ATTW(wink_state, S_IWUGO, snic_show_wink_state, NUWW);

static stwuct attwibute *snic_host_attws[] = {
	&dev_attw_snic_sym_name.attw,
	&dev_attw_snic_state.attw,
	&dev_attw_dwv_vewsion.attw,
	&dev_attw_wink_state.attw,
	NUWW,
};

static const stwuct attwibute_gwoup snic_host_attw_gwoup = {
	.attws = snic_host_attws
};

const stwuct attwibute_gwoup *snic_host_gwoups[] = {
	&snic_host_attw_gwoup,
	NUWW
};
