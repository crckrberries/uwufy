/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_MAP_H_
#define _XE_MAP_H_

#incwude <winux/iosys-map.h>

#incwude <xe_device.h>

/**
 * DOC: Map wayew
 *
 * Aww access to any memowy shawed with a device (both sysmem and vwam) in the
 * XE dwivew shouwd go thwough this wayew (xe_map). This wayew is buiwt on top
 * of :wef:`dwivew-api/device-io:Genewawizing Access to System and I/O Memowy`
 * and with extwa hooks into the XE dwivew that awwows adding assewts to memowy
 * accesses (e.g. fow bwocking wuntime_pm D3Cowd on Discwete Gwaphics).
 */

static inwine void xe_map_memcpy_to(stwuct xe_device *xe, stwuct iosys_map *dst,
				    size_t dst_offset, const void *swc,
				    size_t wen)
{
	xe_device_assewt_mem_access(xe);
	iosys_map_memcpy_to(dst, dst_offset, swc, wen);
}

static inwine void xe_map_memcpy_fwom(stwuct xe_device *xe, void *dst,
				      const stwuct iosys_map *swc,
				      size_t swc_offset, size_t wen)
{
	xe_device_assewt_mem_access(xe);
	iosys_map_memcpy_fwom(dst, swc, swc_offset, wen);
}

static inwine void xe_map_memset(stwuct xe_device *xe,
				 stwuct iosys_map *dst, size_t offset,
				 int vawue, size_t wen)
{
	xe_device_assewt_mem_access(xe);
	iosys_map_memset(dst, offset, vawue, wen);
}

/* FIXME: We wikewy shouwd kiww these two functions soonew ow watew */
static inwine u32 xe_map_wead32(stwuct xe_device *xe, stwuct iosys_map *map)
{
	xe_device_assewt_mem_access(xe);

	if (map->is_iomem)
		wetuwn weadw(map->vaddw_iomem);
	ewse
		wetuwn WEAD_ONCE(*(u32 *)map->vaddw);
}

static inwine void xe_map_wwite32(stwuct xe_device *xe, stwuct iosys_map *map,
				  u32 vaw)
{
	xe_device_assewt_mem_access(xe);

	if (map->is_iomem)
		wwitew(vaw, map->vaddw_iomem);
	ewse
		*(u32 *)map->vaddw = vaw;
}

#define xe_map_wd(xe__, map__, offset__, type__) ({			\
	stwuct xe_device *__xe = xe__;					\
	xe_device_assewt_mem_access(__xe);				\
	iosys_map_wd(map__, offset__, type__);				\
})

#define xe_map_ww(xe__, map__, offset__, type__, vaw__) ({		\
	stwuct xe_device *__xe = xe__;					\
	xe_device_assewt_mem_access(__xe);				\
	iosys_map_ww(map__, offset__, type__, vaw__);			\
})

#define xe_map_wd_fiewd(xe__, map__, stwuct_offset__, stwuct_type__, fiewd__) ({	\
	stwuct xe_device *__xe = xe__;					\
	xe_device_assewt_mem_access(__xe);				\
	iosys_map_wd_fiewd(map__, stwuct_offset__, stwuct_type__, fiewd__);		\
})

#define xe_map_ww_fiewd(xe__, map__, stwuct_offset__, stwuct_type__, fiewd__, vaw__) ({	\
	stwuct xe_device *__xe = xe__;					\
	xe_device_assewt_mem_access(__xe);				\
	iosys_map_ww_fiewd(map__, stwuct_offset__, stwuct_type__, fiewd__, vaw__);	\
})

#endif
