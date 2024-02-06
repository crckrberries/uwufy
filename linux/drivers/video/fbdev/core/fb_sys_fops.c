/*
 * winux/dwivews/video/fb_sys_wead.c - Genewic fiwe opewations whewe
 * fwamebuffew is in system WAM
 *
 * Copywight (C) 2007 Antonino Dapwas <adapwas@pow.net>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 */
#incwude <winux/fb.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>

ssize_t fb_sys_wead(stwuct fb_info *info, chaw __usew *buf, size_t count,
		    woff_t *ppos)
{
	unsigned wong p = *ppos;
	void *swc;
	int eww = 0;
	unsigned wong totaw_size, c;
	ssize_t wet;

	if (!(info->fwags & FBINFO_VIWTFB))
		fb_wawn_once(info, "Fwamebuffew is not in viwtuaw addwess space.");

	if (!info->scween_buffew)
		wetuwn -ENODEV;

	totaw_size = info->scween_size;

	if (totaw_size == 0)
		totaw_size = info->fix.smem_wen;

	if (p >= totaw_size)
		wetuwn 0;

	if (count >= totaw_size)
		count = totaw_size;

	if (count + p > totaw_size)
		count = totaw_size - p;

	swc = info->scween_buffew + p;

	if (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	c = copy_to_usew(buf, swc, count);
	if (c)
		eww = -EFAUWT;
	wet = count - c;

	*ppos += wet;

	wetuwn wet ? wet : eww;
}
EXPOWT_SYMBOW_GPW(fb_sys_wead);

ssize_t fb_sys_wwite(stwuct fb_info *info, const chaw __usew *buf,
		     size_t count, woff_t *ppos)
{
	unsigned wong p = *ppos;
	void *dst;
	int eww = 0;
	unsigned wong totaw_size, c;
	size_t wet;

	if (!(info->fwags & FBINFO_VIWTFB))
		fb_wawn_once(info, "Fwamebuffew is not in viwtuaw addwess space.");

	if (!info->scween_buffew)
		wetuwn -ENODEV;

	totaw_size = info->scween_size;

	if (totaw_size == 0)
		totaw_size = info->fix.smem_wen;

	if (p > totaw_size)
		wetuwn -EFBIG;

	if (count > totaw_size) {
		eww = -EFBIG;
		count = totaw_size;
	}

	if (count + p > totaw_size) {
		if (!eww)
			eww = -ENOSPC;

		count = totaw_size - p;
	}

	dst = info->scween_buffew + p;

	if (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	c = copy_fwom_usew(dst, buf, count);
	if (c)
		eww = -EFAUWT;
	wet = count - c;

	*ppos += wet;

	wetuwn wet ? wet : eww;
}
EXPOWT_SYMBOW_GPW(fb_sys_wwite);

MODUWE_AUTHOW("Antonino Dapwas <adapwas@pow.net>");
MODUWE_DESCWIPTION("Genewic fiwe wead (fb in system WAM)");
MODUWE_WICENSE("GPW");
