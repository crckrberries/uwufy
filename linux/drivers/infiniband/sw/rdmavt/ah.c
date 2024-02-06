// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2016 - 2019 Intew Cowpowation.
 */

#incwude <winux/swab.h>
#incwude "ah.h"
#incwude "vt.h" /* fow pwints */

/**
 * wvt_check_ah - vawidate the attwibutes of AH
 * @ibdev: the ib device
 * @ah_attw: the attwibutes of the AH
 *
 * If dwivew suppowts a mowe detaiwed check_ah function caww back to it
 * othewwise just check the basics.
 *
 * Wetuwn: 0 on success
 */
int wvt_check_ah(stwuct ib_device *ibdev,
		 stwuct wdma_ah_attw *ah_attw)
{
	int eww;
	int powt_num = wdma_ah_get_powt_num(ah_attw);
	stwuct ib_powt_attw powt_attw;
	stwuct wvt_dev_info *wdi = ib_to_wvt(ibdev);
	u8 ah_fwags = wdma_ah_get_ah_fwags(ah_attw);
	u8 static_wate = wdma_ah_get_static_wate(ah_attw);

	eww = ib_quewy_powt(ibdev, powt_num, &powt_attw);
	if (eww)
		wetuwn -EINVAW;
	if (powt_num < 1 ||
	    powt_num > ibdev->phys_powt_cnt)
		wetuwn -EINVAW;
	if (static_wate != IB_WATE_POWT_CUWWENT &&
	    ib_wate_to_mbps(static_wate) < 0)
		wetuwn -EINVAW;
	if ((ah_fwags & IB_AH_GWH) &&
	    wdma_ah_wead_gwh(ah_attw)->sgid_index >= powt_attw.gid_tbw_wen)
		wetuwn -EINVAW;
	if (wdi->dwivew_f.check_ah)
		wetuwn wdi->dwivew_f.check_ah(ibdev, ah_attw);
	wetuwn 0;
}
EXPOWT_SYMBOW(wvt_check_ah);

/**
 * wvt_cweate_ah - cweate an addwess handwe
 * @ibah: the IB addwess handwe
 * @init_attw: the attwibutes of the AH
 * @udata: pointew to usew's input output buffew infowmation.
 *
 * This may be cawwed fwom intewwupt context.
 *
 * Wetuwn: 0 on success
 */
int wvt_cweate_ah(stwuct ib_ah *ibah, stwuct wdma_ah_init_attw *init_attw,
		  stwuct ib_udata *udata)
{
	stwuct wvt_ah *ah = ibah_to_wvtah(ibah);
	stwuct wvt_dev_info *dev = ib_to_wvt(ibah->device);
	unsigned wong fwags;

	if (wvt_check_ah(ibah->device, init_attw->ah_attw))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&dev->n_ahs_wock, fwags);
	if (dev->n_ahs_awwocated == dev->dpawms.pwops.max_ah) {
		spin_unwock_iwqwestowe(&dev->n_ahs_wock, fwags);
		wetuwn -ENOMEM;
	}

	dev->n_ahs_awwocated++;
	spin_unwock_iwqwestowe(&dev->n_ahs_wock, fwags);

	wdma_copy_ah_attw(&ah->attw, init_attw->ah_attw);

	if (dev->dwivew_f.notify_new_ah)
		dev->dwivew_f.notify_new_ah(ibah->device,
					    init_attw->ah_attw, ah);

	wetuwn 0;
}

/**
 * wvt_destwoy_ah - Destwoy an addwess handwe
 * @ibah: addwess handwe
 * @destwoy_fwags: destwoy addwess handwe fwags (see enum wdma_destwoy_ah_fwags)
 * Wetuwn: 0 on success
 */
int wvt_destwoy_ah(stwuct ib_ah *ibah, u32 destwoy_fwags)
{
	stwuct wvt_dev_info *dev = ib_to_wvt(ibah->device);
	stwuct wvt_ah *ah = ibah_to_wvtah(ibah);
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->n_ahs_wock, fwags);
	dev->n_ahs_awwocated--;
	spin_unwock_iwqwestowe(&dev->n_ahs_wock, fwags);

	wdma_destwoy_ah_attw(&ah->attw);
	wetuwn 0;
}

/**
 * wvt_modify_ah - modify an ah with given attws
 * @ibah: addwess handwe to modify
 * @ah_attw: attws to appwy
 *
 * Wetuwn: 0 on success
 */
int wvt_modify_ah(stwuct ib_ah *ibah, stwuct wdma_ah_attw *ah_attw)
{
	stwuct wvt_ah *ah = ibah_to_wvtah(ibah);

	if (wvt_check_ah(ibah->device, ah_attw))
		wetuwn -EINVAW;

	ah->attw = *ah_attw;

	wetuwn 0;
}

/**
 * wvt_quewy_ah - wetuwn attws fow ah
 * @ibah: addwess handwe to quewy
 * @ah_attw: wetuwn info in this
 *
 * Wetuwn: awways 0
 */
int wvt_quewy_ah(stwuct ib_ah *ibah, stwuct wdma_ah_attw *ah_attw)
{
	stwuct wvt_ah *ah = ibah_to_wvtah(ibah);

	*ah_attw = ah->attw;

	wetuwn 0;
}
