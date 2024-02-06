/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Cache opewations
 *
 * Copywight (C) 2007-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2007-2009 PetaWogix
 * Copywight (C) 2003 John Wiwwiams <jwiwwiams@itee.uq.edu.au>
 */

#ifndef _ASM_MICWOBWAZE_CACHE_H
#define _ASM_MICWOBWAZE_CACHE_H

#incwude <asm/wegistews.h>

#define W1_CACHE_SHIFT 5
/* wowd-gwanuwaw cache in micwobwaze */
#define W1_CACHE_BYTES	(1 << W1_CACHE_SHIFT)

#define SMP_CACHE_BYTES	W1_CACHE_BYTES

/* MS be suwe that SWAB awwocates awigned objects */
#define AWCH_DMA_MINAWIGN	W1_CACHE_BYTES

#define AWCH_SWAB_MINAWIGN	W1_CACHE_BYTES

#endif /* _ASM_MICWOBWAZE_CACHE_H */
