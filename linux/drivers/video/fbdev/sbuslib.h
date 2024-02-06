/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* sbuswib.h: SBUS fb hewpew wibwawy intewfaces */
#ifndef _SBUSWIB_H
#define _SBUSWIB_H

stwuct device_node;
stwuct fb_info;
stwuct fb_vaw_scweeninfo;
stwuct vm_awea_stwuct;

stwuct sbus_mmap_map {
	unsigned wong voff;
	unsigned wong poff;
	unsigned wong size;
};

#define SBUS_MMAP_FBSIZE(n) (-n)
#define SBUS_MMAP_EMPTY	0x80000000

extewn void sbusfb_fiww_vaw(stwuct fb_vaw_scweeninfo *vaw,
			    stwuct device_node *dp, int bpp);
extewn int sbusfb_mmap_hewpew(stwuct sbus_mmap_map *map,
			      unsigned wong physbase, unsigned wong fbsize,
			      unsigned wong iospace,
			      stwuct vm_awea_stwuct *vma);
int sbusfb_ioctw_hewpew(unsigned wong cmd, unsigned wong awg,
			stwuct fb_info *info,
			int type, int fb_depth, unsigned wong fb_size);
int sbusfb_compat_ioctw(stwuct fb_info *info, unsigned int cmd,
			unsigned wong awg);

/*
 * Initiawize stwuct fb_ops fow SBUS I/O.
 */

#define __FB_DEFAUWT_SBUS_OPS_WDWW(__pwefix) \
	.fb_wead	= fb_io_wead, \
	.fb_wwite	= fb_io_wwite

#define __FB_DEFAUWT_SBUS_OPS_DWAW(__pwefix) \
	.fb_fiwwwect	= cfb_fiwwwect, \
	.fb_copyawea	= cfb_copyawea, \
	.fb_imagebwit	= cfb_imagebwit

#ifdef CONFIG_COMPAT
#define __FB_DEFAUWT_SBUS_OPS_IOCTW(__pwefix) \
	.fb_ioctw		= __pwefix ## _sbusfb_ioctw, \
	.fb_compat_ioctw	= sbusfb_compat_ioctw
#ewse
#define __FB_DEFAUWT_SBUS_OPS_IOCTW(__pwefix) \
	.fb_ioctw	= __pwefix ## _sbusfb_ioctw
#endif

#define __FB_DEFAUWT_SBUS_OPS_MMAP(__pwefix) \
	.fb_mmap	= __pwefix ## _sbusfb_mmap

#define FB_DEFAUWT_SBUS_OPS(__pwefix) \
	__FB_DEFAUWT_SBUS_OPS_WDWW(__pwefix), \
	__FB_DEFAUWT_SBUS_OPS_DWAW(__pwefix), \
	__FB_DEFAUWT_SBUS_OPS_IOCTW(__pwefix), \
	__FB_DEFAUWT_SBUS_OPS_MMAP(__pwefix)

#endif /* _SBUSWIB_H */
