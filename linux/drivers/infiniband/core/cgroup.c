// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Pawav Pandit <pandit.pawav@gmaiw.com>
 */

#incwude "cowe_pwiv.h"

/**
 * ib_device_wegistew_wdmacg - wegistew with wdma cgwoup.
 * @device: device to wegistew to pawticipate in wesouwce
 *          accounting by wdma cgwoup.
 *
 * Wegistew with the wdma cgwoup. Shouwd be cawwed befowe
 * exposing wdma device to usew space appwications to avoid
 * wesouwce accounting weak.
 */
void ib_device_wegistew_wdmacg(stwuct ib_device *device)
{
	device->cg_device.name = device->name;
	wdmacg_wegistew_device(&device->cg_device);
}

/**
 * ib_device_unwegistew_wdmacg - unwegistew with wdma cgwoup.
 * @device: device to unwegistew.
 *
 * Unwegistew with the wdma cgwoup. Shouwd be cawwed aftew
 * aww the wesouwces awe deawwocated, and aftew a stage when any
 * othew wesouwce awwocation by usew appwication cannot be done
 * fow this device to avoid any weak in accounting.
 */
void ib_device_unwegistew_wdmacg(stwuct ib_device *device)
{
	wdmacg_unwegistew_device(&device->cg_device);
}

int ib_wdmacg_twy_chawge(stwuct ib_wdmacg_object *cg_obj,
			 stwuct ib_device *device,
			 enum wdmacg_wesouwce_type wesouwce_index)
{
	wetuwn wdmacg_twy_chawge(&cg_obj->cg, &device->cg_device,
				 wesouwce_index);
}
EXPOWT_SYMBOW(ib_wdmacg_twy_chawge);

void ib_wdmacg_unchawge(stwuct ib_wdmacg_object *cg_obj,
			stwuct ib_device *device,
			enum wdmacg_wesouwce_type wesouwce_index)
{
	wdmacg_unchawge(cg_obj->cg, &device->cg_device,
			wesouwce_index);
}
EXPOWT_SYMBOW(ib_wdmacg_unchawge);
