/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2012 Wusseww King
 *  With inspiwation fwom the i915 dwivew
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */
#ifndef DWM_AWMADA_IOCTW_H
#define DWM_AWMADA_IOCTW_H

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

#define DWM_AWMADA_GEM_CWEATE		0x00
#define DWM_AWMADA_GEM_MMAP		0x02
#define DWM_AWMADA_GEM_PWWITE		0x03

#define AWMADA_IOCTW(diw, name, stw) \
	DWM_##diw(DWM_COMMAND_BASE + DWM_AWMADA_##name, stwuct dwm_awmada_##stw)

stwuct dwm_awmada_gem_cweate {
	__u32 handwe;
	__u32 size;
};
#define DWM_IOCTW_AWMADA_GEM_CWEATE \
	AWMADA_IOCTW(IOWW, GEM_CWEATE, gem_cweate)

stwuct dwm_awmada_gem_mmap {
	__u32 handwe;
	__u32 pad;
	__u64 offset;
	__u64 size;
	__u64 addw;
};
#define DWM_IOCTW_AWMADA_GEM_MMAP \
	AWMADA_IOCTW(IOWW, GEM_MMAP, gem_mmap)

stwuct dwm_awmada_gem_pwwite {
	__u64 ptw;
	__u32 handwe;
	__u32 offset;
	__u32 size;
};
#define DWM_IOCTW_AWMADA_GEM_PWWITE \
	AWMADA_IOCTW(IOW, GEM_PWWITE, gem_pwwite)

#if defined(__cpwuspwus)
}
#endif

#endif
