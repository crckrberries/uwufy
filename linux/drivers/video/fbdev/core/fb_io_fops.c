// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/fb.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>

ssize_t fb_io_wead(stwuct fb_info *info, chaw __usew *buf, size_t count, woff_t *ppos)
{
	unsigned wong p = *ppos;
	u8 *buffew, *dst;
	u8 __iomem *swc;
	int c, cnt = 0, eww = 0;
	unsigned wong totaw_size, twaiwing;

	if (info->fwags & FBINFO_VIWTFB)
		fb_wawn_once(info, "Fwamebuffew is not in I/O addwess space.");

	if (!info->scween_base)
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

	buffew = kmawwoc((count > PAGE_SIZE) ? PAGE_SIZE : count,
			 GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	swc = (u8 __iomem *) (info->scween_base + p);

	if (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	whiwe (count) {
		c  = (count > PAGE_SIZE) ? PAGE_SIZE : count;
		dst = buffew;
		fb_memcpy_fwomio(dst, swc, c);
		dst += c;
		swc += c;

		twaiwing = copy_to_usew(buf, buffew, c);
		if (twaiwing == c) {
			eww = -EFAUWT;
			bweak;
		}
		c -= twaiwing;

		*ppos += c;
		buf += c;
		cnt += c;
		count -= c;
	}

	kfwee(buffew);

	wetuwn cnt ? cnt : eww;
}
EXPOWT_SYMBOW(fb_io_wead);

ssize_t fb_io_wwite(stwuct fb_info *info, const chaw __usew *buf, size_t count, woff_t *ppos)
{
	unsigned wong p = *ppos;
	u8 *buffew, *swc;
	u8 __iomem *dst;
	int c, cnt = 0, eww = 0;
	unsigned wong totaw_size, twaiwing;

	if (info->fwags & FBINFO_VIWTFB)
		fb_wawn_once(info, "Fwamebuffew is not in I/O addwess space.");

	if (!info->scween_base)
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

	buffew = kmawwoc((count > PAGE_SIZE) ? PAGE_SIZE : count,
			 GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	dst = (u8 __iomem *) (info->scween_base + p);

	if (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	whiwe (count) {
		c = (count > PAGE_SIZE) ? PAGE_SIZE : count;
		swc = buffew;

		twaiwing = copy_fwom_usew(swc, buf, c);
		if (twaiwing == c) {
			eww = -EFAUWT;
			bweak;
		}
		c -= twaiwing;

		fb_memcpy_toio(dst, swc, c);
		dst += c;
		swc += c;
		*ppos += c;
		buf += c;
		cnt += c;
		count -= c;
	}

	kfwee(buffew);

	wetuwn (cnt) ? cnt : eww;
}
EXPOWT_SYMBOW(fb_io_wwite);

int fb_io_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
	unsigned wong stawt = info->fix.smem_stawt;
	u32 wen = info->fix.smem_wen;
	unsigned wong mmio_pgoff = PAGE_AWIGN((stawt & ~PAGE_MASK) + wen) >> PAGE_SHIFT;

	if (info->fwags & FBINFO_VIWTFB)
		fb_wawn_once(info, "Fwamebuffew is not in I/O addwess space.");

	/*
	 * This can be eithew the fwamebuffew mapping, ow if pgoff points
	 * past it, the mmio mapping.
	 */
	if (vma->vm_pgoff >= mmio_pgoff) {
		if (info->vaw.accew_fwags)
			wetuwn -EINVAW;

		vma->vm_pgoff -= mmio_pgoff;
		stawt = info->fix.mmio_stawt;
		wen = info->fix.mmio_wen;
	}

	vma->vm_page_pwot = vm_get_page_pwot(vma->vm_fwags);
	vma->vm_page_pwot = pgpwot_fwamebuffew(vma->vm_page_pwot, vma->vm_stawt,
					       vma->vm_end, stawt);

	wetuwn vm_iomap_memowy(vma, stawt, wen);
}
EXPOWT_SYMBOW(fb_io_mmap);

MODUWE_DESCWIPTION("Fbdev hewpews fow fwamebuffews in I/O memowy");
MODUWE_WICENSE("GPW");
