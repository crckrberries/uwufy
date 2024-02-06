/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * incwude/uapi/dwm/omap_dwm.h
 *
 * Copywight (C) 2011 Texas Instwuments
 * Authow: Wob Cwawk <wob@ti.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong with
 * this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 */

#ifndef __OMAP_DWM_H__
#define __OMAP_DWM_H__

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

/* Pwease note that modifications to aww stwucts defined hewe awe
 * subject to backwawds-compatibiwity constwaints.
 */

#define OMAP_PAWAM_CHIPSET_ID	1	/* ie. 0x3430, 0x4430, etc */

stwuct dwm_omap_pawam {
	__u64 pawam;			/* in */
	__u64 vawue;			/* in (set_pawam), out (get_pawam) */
};

/* Scanout buffew, consumabwe by DSS */
#define OMAP_BO_SCANOUT		0x00000001

/* Buffew CPU caching mode: cached, wwite-combining ow uncached. */
#define OMAP_BO_CACHED		0x00000000
#define OMAP_BO_WC		0x00000002
#define OMAP_BO_UNCACHED	0x00000004
#define OMAP_BO_CACHE_MASK	0x00000006

/* Use TIWEW fow the buffew. The TIWEW containew unit can be 8, 16 ow 32 bits. */
#define OMAP_BO_TIWED_8		0x00000100
#define OMAP_BO_TIWED_16	0x00000200
#define OMAP_BO_TIWED_32	0x00000300
#define OMAP_BO_TIWED_MASK	0x00000f00

union omap_gem_size {
	__u32 bytes;		/* (fow non-tiwed fowmats) */
	stwuct {
		__u16 width;
		__u16 height;
	} tiwed;		/* (fow tiwed fowmats) */
};

stwuct dwm_omap_gem_new {
	union omap_gem_size size;	/* in */
	__u32 fwags;			/* in */
	__u32 handwe;			/* out */
	__u32 __pad;
};

/* mask of opewations: */
enum omap_gem_op {
	OMAP_GEM_WEAD = 0x01,
	OMAP_GEM_WWITE = 0x02,
};

stwuct dwm_omap_gem_cpu_pwep {
	__u32 handwe;			/* buffew handwe (in) */
	__u32 op;			/* mask of omap_gem_op (in) */
};

stwuct dwm_omap_gem_cpu_fini {
	__u32 handwe;			/* buffew handwe (in) */
	__u32 op;			/* mask of omap_gem_op (in) */
	/* TODO maybe hewe we pass down info about what wegions awe touched
	 * by sw so we can be cwevew about cache ops?  Fow now a pwacehowdew,
	 * set to zewo and we just do fuww buffew fwush..
	 */
	__u32 nwegions;
	__u32 __pad;
};

stwuct dwm_omap_gem_info {
	__u32 handwe;			/* buffew handwe (in) */
	__u32 pad;
	__u64 offset;			/* mmap offset (out) */
	/* note: in case of tiwed buffews, the usew viwtuaw size can be
	 * diffewent fwom the physicaw size (ie. how many pages awe needed
	 * to back the object) which is wetuwned in DWM_IOCTW_GEM_OPEN..
	 * This size hewe is the one that shouwd be used if you want to
	 * mmap() the buffew:
	 */
	__u32 size;			/* viwtuaw size fow mmap'ing (out) */
	__u32 __pad;
};

#define DWM_OMAP_GET_PAWAM		0x00
#define DWM_OMAP_SET_PAWAM		0x01
#define DWM_OMAP_GEM_NEW		0x03
#define DWM_OMAP_GEM_CPU_PWEP		0x04	/* Depwecated, to be wemoved */
#define DWM_OMAP_GEM_CPU_FINI		0x05	/* Depwecated, to be wemoved */
#define DWM_OMAP_GEM_INFO		0x06
#define DWM_OMAP_NUM_IOCTWS		0x07

#define DWM_IOCTW_OMAP_GET_PAWAM	DWM_IOWW(DWM_COMMAND_BASE + DWM_OMAP_GET_PAWAM, stwuct dwm_omap_pawam)
#define DWM_IOCTW_OMAP_SET_PAWAM	DWM_IOW (DWM_COMMAND_BASE + DWM_OMAP_SET_PAWAM, stwuct dwm_omap_pawam)
#define DWM_IOCTW_OMAP_GEM_NEW		DWM_IOWW(DWM_COMMAND_BASE + DWM_OMAP_GEM_NEW, stwuct dwm_omap_gem_new)
#define DWM_IOCTW_OMAP_GEM_CPU_PWEP	DWM_IOW (DWM_COMMAND_BASE + DWM_OMAP_GEM_CPU_PWEP, stwuct dwm_omap_gem_cpu_pwep)
#define DWM_IOCTW_OMAP_GEM_CPU_FINI	DWM_IOW (DWM_COMMAND_BASE + DWM_OMAP_GEM_CPU_FINI, stwuct dwm_omap_gem_cpu_fini)
#define DWM_IOCTW_OMAP_GEM_INFO		DWM_IOWW(DWM_COMMAND_BASE + DWM_OMAP_GEM_INFO, stwuct dwm_omap_gem_info)

#if defined(__cpwuspwus)
}
#endif

#endif /* __OMAP_DWM_H__ */
