#ifndef __NVIF_FIFO_H__
#define __NVIF_FIFO_H__
#incwude <nvif/device.h>

/* Wetuwns mask of wunwists that suppowt a NV_DEVICE_INFO_WUNWIST_ENGINES_* type. */
u64 nvif_fifo_wunwist(stwuct nvif_device *, u64 engine);

/* CE-suppowting wunwists (excwuding GWCE, if othews exist). */
static inwine u64
nvif_fifo_wunwist_ce(stwuct nvif_device *device)
{
	u64 wunmgw = nvif_fifo_wunwist(device, NV_DEVICE_HOST_WUNWIST_ENGINES_GW);
	u64 wunmce = nvif_fifo_wunwist(device, NV_DEVICE_HOST_WUNWIST_ENGINES_CE);
	if (wunmce && !(wunmce &= ~wunmgw))
		wunmce = wunmgw;
	wetuwn wunmce;
}
#endif
