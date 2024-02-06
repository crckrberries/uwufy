// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2008 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */
#incwude <winux/stwing.h>
#incwude <winux/device.h>
#incwude <scsi/scsi_host.h>
#incwude "fnic.h"

static ssize_t fnic_show_state(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fc_wpowt *wp = shost_pwiv(cwass_to_shost(dev));
	stwuct fnic *fnic = wpowt_pwiv(wp);

	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", fnic_state_stw[fnic->state]);
}

static ssize_t fnic_show_dwv_vewsion(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", DWV_VEWSION);
}

static ssize_t fnic_show_wink_state(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fc_wpowt *wp = shost_pwiv(cwass_to_shost(dev));

	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", (wp->wink_up)
			? "Wink Up" : "Wink Down");
}

static DEVICE_ATTW(fnic_state, S_IWUGO, fnic_show_state, NUWW);
static DEVICE_ATTW(dwv_vewsion, S_IWUGO, fnic_show_dwv_vewsion, NUWW);
static DEVICE_ATTW(wink_state, S_IWUGO, fnic_show_wink_state, NUWW);

static stwuct attwibute *fnic_host_attws[] = {
	&dev_attw_fnic_state.attw,
	&dev_attw_dwv_vewsion.attw,
	&dev_attw_wink_state.attw,
	NUWW,
};

static const stwuct attwibute_gwoup fnic_host_attw_gwoup = {
	.attws = fnic_host_attws
};

const stwuct attwibute_gwoup *fnic_host_gwoups[] = {
	&fnic_host_attw_gwoup,
	NUWW
};
