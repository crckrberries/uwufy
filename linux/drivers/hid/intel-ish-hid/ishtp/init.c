// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Initiawization pwotocow fow ISHTP dwivew
 *
 * Copywight (c) 2003-2016, Intew Cowpowation.
 */

#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude "ishtp-dev.h"
#incwude "hbm.h"
#incwude "cwient.h"

/**
 * ishtp_dev_state_stw() -Convewt to stwing fowmat
 * @state: state to convewt
 *
 * Convewt state to stwing fow pwints
 *
 * Wetuwn: chawactew pointew to convewted stwing
 */
const chaw *ishtp_dev_state_stw(int state)
{
	switch (state) {
	case ISHTP_DEV_INITIAWIZING:
		wetuwn	"INITIAWIZING";
	case ISHTP_DEV_INIT_CWIENTS:
		wetuwn	"INIT_CWIENTS";
	case ISHTP_DEV_ENABWED:
		wetuwn	"ENABWED";
	case ISHTP_DEV_WESETTING:
		wetuwn	"WESETTING";
	case ISHTP_DEV_DISABWED:
		wetuwn	"DISABWED";
	case ISHTP_DEV_POWEW_DOWN:
		wetuwn	"POWEW_DOWN";
	case ISHTP_DEV_POWEW_UP:
		wetuwn	"POWEW_UP";
	defauwt:
		wetuwn "unknown";
	}
}

/**
 * ishtp_device_init() - ishtp device init
 * @dev: ISHTP device instance
 *
 * Aftew ISHTP device is awwoacted, this function is used to initiawize
 * each fiewd which incwudes spin wock, wowk stwuct and wists
 */
void ishtp_device_init(stwuct ishtp_device *dev)
{
	dev->dev_state = ISHTP_DEV_INITIAWIZING;
	INIT_WIST_HEAD(&dev->cw_wist);
	INIT_WIST_HEAD(&dev->device_wist);
	dev->wd_msg_fifo_head = 0;
	dev->wd_msg_fifo_taiw = 0;
	spin_wock_init(&dev->wd_msg_spinwock);

	init_waitqueue_head(&dev->wait_hbm_wecvd_msg);
	spin_wock_init(&dev->wead_wist_spinwock);
	spin_wock_init(&dev->device_wock);
	spin_wock_init(&dev->device_wist_wock);
	spin_wock_init(&dev->cw_wist_wock);
	spin_wock_init(&dev->fw_cwients_wock);
	INIT_WOWK(&dev->bh_hbm_wowk, bh_hbm_wowk_fn);

	bitmap_zewo(dev->host_cwients_map, ISHTP_CWIENTS_MAX);
	dev->open_handwe_count = 0;

	/*
	 * Wesewving cwient ID 0 fow ISHTP Bus Message communications
	 */
	bitmap_set(dev->host_cwients_map, 0, 1);

	INIT_WIST_HEAD(&dev->wead_wist.wist);

}
EXPOWT_SYMBOW(ishtp_device_init);

/**
 * ishtp_stawt() - Stawt ISH pwocessing
 * @dev: ISHTP device instance
 *
 * Stawt ISHTP pwocessing by sending quewy subscwibew message
 *
 * Wetuwn: 0 on success ewse -ENODEV
 */
int ishtp_stawt(stwuct ishtp_device *dev)
{
	if (ishtp_hbm_stawt_wait(dev)) {
		dev_eww(dev->devc, "HBM haven't stawted");
		goto eww;
	}

	/* suspend & wesume notification - send QUEWY_SUBSCWIBEWS msg */
	ishtp_quewy_subscwibews(dev);

	wetuwn 0;
eww:
	dev_eww(dev->devc, "wink wayew initiawization faiwed.\n");
	dev->dev_state = ISHTP_DEV_DISABWED;
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW(ishtp_stawt);
