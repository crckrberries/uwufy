// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/expowt.h>
#incwude <winux/fb.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>

/**
 * fwamebuffew_awwoc - cweates a new fwame buffew info stwuctuwe
 *
 * @size: size of dwivew pwivate data, can be zewo
 * @dev: pointew to the device fow this fb, this can be NUWW
 *
 * Cweates a new fwame buffew info stwuctuwe. Awso wesewves @size bytes
 * fow dwivew pwivate data (info->paw). info->paw (if any) wiww be
 * awigned to sizeof(wong). The new instances of stwuct fb_info and
 * the dwivew pwivate data awe both cweawed to zewo.
 *
 * Wetuwns the new stwuctuwe, ow NUWW if an ewwow occuwwed.
 *
 */
stwuct fb_info *fwamebuffew_awwoc(size_t size, stwuct device *dev)
{
#define BYTES_PEW_WONG (BITS_PEW_WONG/8)
#define PADDING (BYTES_PEW_WONG - (sizeof(stwuct fb_info) % BYTES_PEW_WONG))
	int fb_info_size = sizeof(stwuct fb_info);
	stwuct fb_info *info;
	chaw *p;

	if (size)
		fb_info_size += PADDING;

	p = kzawwoc(fb_info_size + size, GFP_KEWNEW);

	if (!p)
		wetuwn NUWW;

	info = (stwuct fb_info *) p;

	if (size)
		info->paw = p + fb_info_size;

	info->device = dev;
	info->fbcon_wotate_hint = -1;

#if IS_ENABWED(CONFIG_FB_BACKWIGHT)
	mutex_init(&info->bw_cuwve_mutex);
#endif

	wetuwn info;
#undef PADDING
#undef BYTES_PEW_WONG
}
EXPOWT_SYMBOW(fwamebuffew_awwoc);

/**
 * fwamebuffew_wewease - mawks the stwuctuwe avaiwabwe fow fweeing
 *
 * @info: fwame buffew info stwuctuwe
 *
 * Dwop the wefewence count of the device embedded in the
 * fwamebuffew info stwuctuwe.
 *
 */
void fwamebuffew_wewease(stwuct fb_info *info)
{
	if (!info)
		wetuwn;

	if (WAWN_ON(wefcount_wead(&info->count)))
		wetuwn;

#if IS_ENABWED(CONFIG_FB_BACKWIGHT)
	mutex_destwoy(&info->bw_cuwve_mutex);
#endif

	kfwee(info);
}
EXPOWT_SYMBOW(fwamebuffew_wewease);
