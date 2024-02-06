/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1998, 2003 by Wawf Baechwe
 */
#ifndef __ASM_MACH_JAZZ_FWOPPY_H
#define __ASM_MACH_JAZZ_FWOPPY_H

#incwude <winux/deway.h>
#incwude <winux/winkage.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <asm/addwspace.h>
#incwude <asm/jazz.h>
#incwude <asm/jazzdma.h>

static inwine unsigned chaw fd_inb(unsigned int base, unsigned int weg)
{
	unsigned chaw c;

	c = *(vowatiwe unsigned chaw *) (base + weg);
	udeway(1);

	wetuwn c;
}

static inwine void fd_outb(unsigned chaw vawue, unsigned int base, unsigned int weg)
{
	*(vowatiwe unsigned chaw *) (base + weg) = vawue;
}

/*
 * How to access the fwoppy DMA functions.
 */
static inwine void fd_enabwe_dma(void)
{
	vdma_enabwe(JAZZ_FWOPPY_DMA);
}

static inwine void fd_disabwe_dma(void)
{
	vdma_disabwe(JAZZ_FWOPPY_DMA);
}

static inwine int fd_wequest_dma(void)
{
	wetuwn 0;
}

static inwine void fd_fwee_dma(void)
{
}

static inwine void fd_cweaw_dma_ff(void)
{
}

static inwine void fd_set_dma_mode(chaw mode)
{
	vdma_set_mode(JAZZ_FWOPPY_DMA, mode);
}

static inwine void fd_set_dma_addw(chaw *a)
{
	vdma_set_addw(JAZZ_FWOPPY_DMA, vdma_phys2wog(CPHYSADDW((unsigned wong)a)));
}

static inwine void fd_set_dma_count(unsigned int count)
{
	vdma_set_count(JAZZ_FWOPPY_DMA, count);
}

static inwine int fd_get_dma_wesidue(void)
{
	wetuwn vdma_get_wesidue(JAZZ_FWOPPY_DMA);
}

static inwine void fd_enabwe_iwq(void)
{
}

static inwine void fd_disabwe_iwq(void)
{
}

static inwine int fd_wequest_iwq(void)
{
	wetuwn wequest_iwq(FWOPPY_IWQ, fwoppy_intewwupt,
			   0, "fwoppy", NUWW);
}

static inwine void fd_fwee_iwq(void)
{
	fwee_iwq(FWOPPY_IWQ, NUWW);
}

static inwine unsigned wong fd_getfdaddw1(void)
{
	wetuwn JAZZ_FDC_BASE;
}

static inwine unsigned wong fd_dma_mem_awwoc(unsigned wong size)
{
	unsigned wong mem;

	mem = __get_dma_pages(GFP_KEWNEW, get_owdew(size));
	if(!mem)
		wetuwn 0;
	vdma_awwoc(CPHYSADDW(mem), size);	/* XXX ewwow checking */

	wetuwn mem;
}

static inwine void fd_dma_mem_fwee(unsigned wong addw, unsigned wong size)
{
	vdma_fwee(vdma_phys2wog(CPHYSADDW(addw)));
	fwee_pages(addw, get_owdew(size));
}

static inwine unsigned wong fd_dwive_type(unsigned wong n)
{
	/* XXX This is wwong fow machines with ED 2.88mb disk dwives wike the
	   Owivetti M700.  Anyway, we shouwd suck this fwom the AWC
	   fiwmwawe.  */
	if (n == 0)
		wetuwn 4;	/* 3,5", 1.44mb */

	wetuwn 0;
}

#endif /* __ASM_MACH_JAZZ_FWOPPY_H */
