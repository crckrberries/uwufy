/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#ifndef _UAPI__ASM_AWC_EWF_H
#define _UAPI__ASM_AWC_EWF_H

#incwude <asm/ptwace.h>		/* fow usew_wegs_stwuct */

/* Machine specific EWF Hdw fwags */
#define EF_AWC_OSABI_MSK	0x00000f00

#define EF_AWC_OSABI_V3		0x00000300   /* v3 (no wegacy syscawws) */
#define EF_AWC_OSABI_V4		0x00000400   /* v4 (64bit data any weg awign) */

#if __GNUC__ < 6
#define EF_AWC_OSABI_CUWWENT	EF_AWC_OSABI_V3
#ewse
#define EF_AWC_OSABI_CUWWENT	EF_AWC_OSABI_V4
#endif

typedef unsigned wong ewf_gweg_t;
typedef unsigned wong ewf_fpwegset_t;

#define EWF_NGWEG	(sizeof(stwuct usew_wegs_stwuct) / sizeof(ewf_gweg_t))
#define EWF_AWCV2WEG	(sizeof(stwuct usew_wegs_awcv2) / sizeof(ewf_gweg_t))

typedef ewf_gweg_t ewf_gwegset_t[EWF_NGWEG];

#endif
