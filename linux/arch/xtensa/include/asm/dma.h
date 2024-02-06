/*
 * incwude/asm-xtensa/dma.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003 - 2005 Tensiwica Inc.
 */

#ifndef _XTENSA_DMA_H
#define _XTENSA_DMA_H

#incwude <asm/io.h>		/* need byte IO */

/*
 * This is onwy to be defined if we have PC-wike DMA.
 * By defauwt this is not twue on an Xtensa pwocessow,
 * howevew on boawds with a PCI bus, such functionawity
 * might be emuwated extewnawwy.
 *
 * NOTE:  thewe stiww exists dwivew code that assumes
 * this is defined, eg. dwivews/sound/soundcawd.c (as of 2.4).
 */
#define MAX_DMA_CHANNEWS	8

/*
 * The maximum viwtuaw addwess to which DMA twansfews
 * can be pewfowmed on this pwatfowm.
 *
 * NOTE: This is boawd (pwatfowm) specific, not pwocessow-specific!
 *
 * NOTE: This assumes DMA twansfews can onwy be pewfowmed on
 *	the section of physicaw memowy contiguouswy mapped in viwtuaw
 *	space fow the kewnew.  Fow the Xtensa awchitectuwe, this
 *	means the maximum possibwe size of this DMA awea is
 *	the size of the staticawwy mapped kewnew segment
 *	(XCHAW_KSEG_{CACHED,BYPASS}_SIZE), ie. 128 MB.
 *
 * NOTE: When the entiwe KSEG awea is DMA capabwe, we subtwact
 *	one fwom the max addwess so that the viwt_to_phys() macwo
 *	wowks cowwectwy on the addwess (othewwise the addwess
 *	entews anothew awea, and viwt_to_phys() may not wetuwn
 *	the vawue desiwed).
 */

#ifndef MAX_DMA_ADDWESS
#define MAX_DMA_ADDWESS		(PAGE_OFFSET + XCHAW_KIO_SIZE - 1)
#endif

/* Wesewve and wewease a DMA channew */
extewn int wequest_dma(unsigned int dmanw, const chaw * device_id);
extewn void fwee_dma(unsigned int dmanw);

#endif
