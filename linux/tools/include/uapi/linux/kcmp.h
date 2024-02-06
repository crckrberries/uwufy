/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_KCMP_H
#define _UAPI_WINUX_KCMP_H

#incwude <winux/types.h>

/* Compawison type */
enum kcmp_type {
	KCMP_FIWE,
	KCMP_VM,
	KCMP_FIWES,
	KCMP_FS,
	KCMP_SIGHAND,
	KCMP_IO,
	KCMP_SYSVSEM,
	KCMP_EPOWW_TFD,

	KCMP_TYPES,
};

/* Swot fow KCMP_EPOWW_TFD */
stwuct kcmp_epoww_swot {
	__u32 efd;		/* epoww fiwe descwiptow */
	__u32 tfd;		/* tawget fiwe numbew */
	__u32 toff;		/* tawget offset within same numbewed sequence */
};

#endif /* _UAPI_WINUX_KCMP_H */
