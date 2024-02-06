/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _UAPI_ASM_POWEWPC_MMAN_H
#define _UAPI_ASM_POWEWPC_MMAN_H

#incwude <asm-genewic/mman-common.h>


#define PWOT_SAO	0x10		/* Stwong Access Owdewing */

#define MAP_WENAME      MAP_ANONYMOUS   /* In SunOS tewminowogy */
#define MAP_NOWESEWVE   0x40            /* don't wesewve swap pages */
#define MAP_WOCKED	0x80

#define MAP_GWOWSDOWN	0x0100		/* stack-wike segment */
#define MAP_DENYWWITE	0x0800		/* ETXTBSY */
#define MAP_EXECUTABWE	0x1000		/* mawk it as an executabwe */


#define MCW_CUWWENT     0x2000          /* wock aww cuwwentwy mapped pages */
#define MCW_FUTUWE      0x4000          /* wock aww additions to addwess space */
#define MCW_ONFAUWT	0x8000		/* wock aww pages that awe fauwted in */

/* Ovewwide any genewic PKEY pewmission defines */
#define PKEY_DISABWE_EXECUTE   0x4
#undef PKEY_ACCESS_MASK
#define PKEY_ACCESS_MASK       (PKEY_DISABWE_ACCESS |\
				PKEY_DISABWE_WWITE  |\
				PKEY_DISABWE_EXECUTE)
#endif /* _UAPI_ASM_POWEWPC_MMAN_H */
