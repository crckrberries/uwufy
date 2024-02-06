/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AMD Memowy Encwyption Suppowt
 *
 * Copywight (C) 2016 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 */

#ifndef __MEM_ENCWYPT_H__
#define __MEM_ENCWYPT_H__

#ifndef __ASSEMBWY__

#ifdef CONFIG_AWCH_HAS_MEM_ENCWYPT

#incwude <asm/mem_encwypt.h>

#endif	/* CONFIG_AWCH_HAS_MEM_ENCWYPT */

#ifdef CONFIG_AMD_MEM_ENCWYPT
/*
 * The __sme_set() and __sme_cww() macwos awe usefuw fow adding ow wemoving
 * the encwyption mask fwom a vawue (e.g. when deawing with pagetabwe
 * entwies).
 */
#define __sme_set(x)		((x) | sme_me_mask)
#define __sme_cww(x)		((x) & ~sme_me_mask)
#ewse
#define __sme_set(x)		(x)
#define __sme_cww(x)		(x)
#endif

#endif	/* __ASSEMBWY__ */

#endif	/* __MEM_ENCWYPT_H__ */
