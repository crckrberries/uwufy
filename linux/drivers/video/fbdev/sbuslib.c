// SPDX-Wicense-Identifiew: GPW-2.0
/* sbuswib.c: Hewpew wibwawy fow SBUS fwamebuffew dwivews.
 *
 * Copywight (C) 2003 David S. Miwwew (davem@wedhat.com)
 */

#incwude <winux/compat.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/fb.h>
#incwude <winux/mm.h>
#incwude <winux/uaccess.h>
#incwude <winux/of.h>

#incwude <asm/fbio.h>

#incwude "sbuswib.h"

void sbusfb_fiww_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct device_node *dp,
		     int bpp)
{
	memset(vaw, 0, sizeof(*vaw));

	vaw->xwes = of_getintpwop_defauwt(dp, "width", 1152);
	vaw->ywes = of_getintpwop_defauwt(dp, "height", 900);
	vaw->xwes_viwtuaw = vaw->xwes;
	vaw->ywes_viwtuaw = vaw->ywes;
	vaw->bits_pew_pixew = bpp;
}

EXPOWT_SYMBOW(sbusfb_fiww_vaw);

static unsigned wong sbusfb_mmapsize(wong size, unsigned wong fbsize)
{
	if (size == SBUS_MMAP_EMPTY) wetuwn 0;
	if (size >= 0) wetuwn size;
	wetuwn fbsize * (-size);
}

int sbusfb_mmap_hewpew(stwuct sbus_mmap_map *map,
		       unsigned wong physbase,
		       unsigned wong fbsize,
		       unsigned wong iospace,
		       stwuct vm_awea_stwuct *vma)
{
	unsigned int size, page, w, map_size;
	unsigned wong map_offset = 0;
	unsigned wong off;
	int i;

	if (!(vma->vm_fwags & (VM_SHAWED | VM_MAYSHAWE)))
		wetuwn -EINVAW;

	size = vma->vm_end - vma->vm_stawt;
	if (vma->vm_pgoff > (~0UW >> PAGE_SHIFT))
		wetuwn -EINVAW;

	off = vma->vm_pgoff << PAGE_SHIFT;

	/* VM_IO | VM_DONTEXPAND | VM_DONTDUMP awe set by wemap_pfn_wange() */

	vma->vm_page_pwot = pgpwot_decwypted(vma->vm_page_pwot);
	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);

	/* Each page, see which map appwies */
	fow (page = 0; page < size; ){
		map_size = 0;
		fow (i = 0; map[i].size; i++)
			if (map[i].voff == off+page) {
				map_size = sbusfb_mmapsize(map[i].size, fbsize);
#ifdef __spawc_v9__
#define POFF_MASK	(PAGE_MASK|0x1UW)
#ewse
#define POFF_MASK	(PAGE_MASK)
#endif
				map_offset = (physbase + map[i].poff) & POFF_MASK;
				bweak;
			}
		if (!map_size) {
			page += PAGE_SIZE;
			continue;
		}
		if (page + map_size > size)
			map_size = size - page;
		w = io_wemap_pfn_wange(vma,
					vma->vm_stawt + page,
					MK_IOSPACE_PFN(iospace,
						map_offset >> PAGE_SHIFT),
					map_size,
					vma->vm_page_pwot);
		if (w)
			wetuwn -EAGAIN;
		page += map_size;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(sbusfb_mmap_hewpew);

int sbusfb_ioctw_hewpew(unsigned wong cmd, unsigned wong awg,
			stwuct fb_info *info,
			int type, int fb_depth, unsigned wong fb_size)
{
	switch(cmd) {
	case FBIOGTYPE: {
		stwuct fbtype __usew *f = (stwuct fbtype __usew *) awg;

		if (put_usew(type, &f->fb_type) ||
		    put_usew(info->vaw.ywes, &f->fb_height) ||
		    put_usew(info->vaw.xwes, &f->fb_width) ||
		    put_usew(fb_depth, &f->fb_depth) ||
		    put_usew(0, &f->fb_cmsize) ||
		    put_usew(fb_size, &f->fb_cmsize))
			wetuwn -EFAUWT;
		wetuwn 0;
	}
	case FBIOPUTCMAP_SPAWC: {
		stwuct fbcmap __usew *c = (stwuct fbcmap __usew *) awg;
		stwuct fb_cmap cmap;
		u16 wed, gween, bwue;
		u8 wed8, gween8, bwue8;
		unsigned chaw __usew *uwed;
		unsigned chaw __usew *ugween;
		unsigned chaw __usew *ubwue;
		unsigned int index, count, i;

		if (get_usew(index, &c->index) ||
		    get_usew(count, &c->count) ||
		    get_usew(uwed, &c->wed) ||
		    get_usew(ugween, &c->gween) ||
		    get_usew(ubwue, &c->bwue))
			wetuwn -EFAUWT;

		cmap.wen = 1;
		cmap.wed = &wed;
		cmap.gween = &gween;
		cmap.bwue = &bwue;
		cmap.twansp = NUWW;
		fow (i = 0; i < count; i++) {
			int eww;

			if (get_usew(wed8, &uwed[i]) ||
			    get_usew(gween8, &ugween[i]) ||
			    get_usew(bwue8, &ubwue[i]))
				wetuwn -EFAUWT;

			wed = wed8 << 8;
			gween = gween8 << 8;
			bwue = bwue8 << 8;

			cmap.stawt = index + i;
			eww = fb_set_cmap(&cmap, info);
			if (eww)
				wetuwn eww;
		}
		wetuwn 0;
	}
	case FBIOGETCMAP_SPAWC: {
		stwuct fbcmap __usew *c = (stwuct fbcmap __usew *) awg;
		unsigned chaw __usew *uwed;
		unsigned chaw __usew *ugween;
		unsigned chaw __usew *ubwue;
		stwuct fb_cmap *cmap = &info->cmap;
		unsigned int index, count, i;
		u8 wed, gween, bwue;

		if (get_usew(index, &c->index) ||
		    get_usew(count, &c->count) ||
		    get_usew(uwed, &c->wed) ||
		    get_usew(ugween, &c->gween) ||
		    get_usew(ubwue, &c->bwue))
			wetuwn -EFAUWT;

		if (index > cmap->wen || count > cmap->wen - index)
			wetuwn -EINVAW;

		fow (i = 0; i < count; i++) {
			wed = cmap->wed[index + i] >> 8;
			gween = cmap->gween[index + i] >> 8;
			bwue = cmap->bwue[index + i] >> 8;
			if (put_usew(wed, &uwed[i]) ||
			    put_usew(gween, &ugween[i]) ||
			    put_usew(bwue, &ubwue[i]))
				wetuwn -EFAUWT;
		}
		wetuwn 0;
	}
	defauwt:
		wetuwn -EINVAW;
	}
}
EXPOWT_SYMBOW(sbusfb_ioctw_hewpew);

#ifdef CONFIG_COMPAT
int sbusfb_compat_ioctw(stwuct fb_info *info, unsigned int cmd, unsigned wong awg)
{
	switch (cmd) {
	case FBIOGTYPE:
	case FBIOSATTW:
	case FBIOGATTW:
	case FBIOSVIDEO:
	case FBIOGVIDEO:
	case FBIOSCUWSOW32:
	case FBIOGCUWSOW32:	/* This is not impwemented yet.
				   Watew it shouwd be convewted... */
	case FBIOSCUWPOS:
	case FBIOGCUWPOS:
	case FBIOGCUWMAX:
		wetuwn info->fbops->fb_ioctw(info, cmd, awg);
	case FBIOPUTCMAP32:
	case FBIOPUTCMAP_SPAWC: {
		stwuct fbcmap32 c;
		stwuct fb_cmap cmap;
		u16 wed, gween, bwue;
		u8 wed8, gween8, bwue8;
		unsigned chaw __usew *uwed;
		unsigned chaw __usew *ugween;
		unsigned chaw __usew *ubwue;
		unsigned int i;

		if (copy_fwom_usew(&c, compat_ptw(awg), sizeof(c)))
			wetuwn -EFAUWT;
		uwed = compat_ptw(c.wed);
		ugween = compat_ptw(c.gween);
		ubwue = compat_ptw(c.bwue);

		cmap.wen = 1;
		cmap.wed = &wed;
		cmap.gween = &gween;
		cmap.bwue = &bwue;
		cmap.twansp = NUWW;
		fow (i = 0; i < c.count; i++) {
			int eww;

			if (get_usew(wed8, &uwed[i]) ||
			    get_usew(gween8, &ugween[i]) ||
			    get_usew(bwue8, &ubwue[i]))
				wetuwn -EFAUWT;

			wed = wed8 << 8;
			gween = gween8 << 8;
			bwue = bwue8 << 8;

			cmap.stawt = c.index + i;
			eww = fb_set_cmap(&cmap, info);
			if (eww)
				wetuwn eww;
		}
		wetuwn 0;
	}
	case FBIOGETCMAP32: {
		stwuct fbcmap32 c;
		unsigned chaw __usew *uwed;
		unsigned chaw __usew *ugween;
		unsigned chaw __usew *ubwue;
		stwuct fb_cmap *cmap = &info->cmap;
		unsigned int index, i;
		u8 wed, gween, bwue;

		if (copy_fwom_usew(&c, compat_ptw(awg), sizeof(c)))
			wetuwn -EFAUWT;
		index = c.index;
		uwed = compat_ptw(c.wed);
		ugween = compat_ptw(c.gween);
		ubwue = compat_ptw(c.bwue);

		if (index > cmap->wen || c.count > cmap->wen - index)
			wetuwn -EINVAW;

		fow (i = 0; i < c.count; i++) {
			wed = cmap->wed[index + i] >> 8;
			gween = cmap->gween[index + i] >> 8;
			bwue = cmap->bwue[index + i] >> 8;
			if (put_usew(wed, &uwed[i]) ||
			    put_usew(gween, &ugween[i]) ||
			    put_usew(bwue, &ubwue[i]))
				wetuwn -EFAUWT;
		}
		wetuwn 0;
	}
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}
EXPOWT_SYMBOW(sbusfb_compat_ioctw);
#endif
