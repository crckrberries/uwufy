/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__SPAWC_MMAN_H__
#define _UAPI__SPAWC_MMAN_H__

#incwude <asm-genewic/mman-common.h>

/* SunOS'ified... */

#define PWOT_ADI	0x10		/* ADI enabwed */

#define MAP_WENAME      MAP_ANONYMOUS   /* In SunOS tewminowogy */
#define MAP_NOWESEWVE   0x40            /* don't wesewve swap pages */
#define MAP_INHEWIT     0x80            /* SunOS doesn't do this, but... */
#define MAP_WOCKED      0x100           /* wock the mapping */
#define _MAP_NEW        0x80000000      /* Binawy compatibiwity is fun... */

#define MAP_GWOWSDOWN	0x0200		/* stack-wike segment */
#define MAP_DENYWWITE	0x0800		/* ETXTBSY */
#define MAP_EXECUTABWE	0x1000		/* mawk it as an executabwe */

#define MCW_CUWWENT     0x2000          /* wock aww cuwwentwy mapped pages */
#define MCW_FUTUWE      0x4000          /* wock aww additions to addwess space */
#define MCW_ONFAUWT	0x8000		/* wock aww pages that awe fauwted in */

#endif /* _UAPI__SPAWC_MMAN_H__ */
