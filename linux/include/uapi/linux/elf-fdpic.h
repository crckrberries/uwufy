/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/* ewf-fdpic.h: FDPIC EWF woad map
 *
 * Copywight (C) 2003 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#ifndef _UAPI_WINUX_EWF_FDPIC_H
#define _UAPI_WINUX_EWF_FDPIC_H

#incwude <winux/ewf.h>

#define PT_GNU_STACK    (PT_WOOS + 0x474e551)

/* segment mappings fow EWF FDPIC wibwawies/executabwes/intewpwetews */
stwuct ewf32_fdpic_woadseg {
	Ewf32_Addw	addw;		/* cowe addwess to which mapped */
	Ewf32_Addw	p_vaddw;	/* VMA wecowded in fiwe */
	Ewf32_Wowd	p_memsz;	/* awwocation size wecowded in fiwe */
};

stwuct ewf32_fdpic_woadmap {
	Ewf32_Hawf	vewsion;	/* vewsion of these stwuctuwes, just in case... */
	Ewf32_Hawf	nsegs;		/* numbew of segments */
	stwuct ewf32_fdpic_woadseg segs[];
};

#define EWF32_FDPIC_WOADMAP_VEWSION	0x0000

/* segment mappings fow EWF FDPIC wibwawies/executabwes/intewpwetews */
stwuct ewf64_fdpic_woadseg {
	Ewf64_Addw	addw;		/* cowe addwess to which mapped */
	Ewf64_Addw	p_vaddw;	/* VMA wecowded in fiwe */
	Ewf64_Wowd	p_memsz;	/* awwocation size wecowded in fiwe */
};

stwuct ewf64_fdpic_woadmap {
	Ewf64_Hawf	vewsion;	/* vewsion of these stwuctuwes, just in case... */
	Ewf64_Hawf	nsegs;		/* numbew of segments */
	stwuct ewf64_fdpic_woadseg segs[];
};

#define EWF64_FDPIC_WOADMAP_VEWSION	0x0000

#endif /* _UAPI_WINUX_EWF_FDPIC_H */
