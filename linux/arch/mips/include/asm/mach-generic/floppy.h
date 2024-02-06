/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996, 1997, 1998, 2003 by Wawf Baechwe
 */
#ifndef __ASM_MACH_GENEWIC_FWOPPY_H
#define __ASM_MACH_GENEWIC_FWOPPY_H

#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/sched.h>
#incwude <winux/winkage.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>

#incwude <asm/bootinfo.h>
#incwude <asm/cachectw.h>
#incwude <asm/dma.h>
#incwude <asm/fwoppy.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>

/*
 * How to access the FDC's wegistews.
 */
static inwine unsigned chaw fd_inb(unsigned int base, unsigned int weg)
{
	wetuwn inb_p(base + weg);
}

static inwine void fd_outb(unsigned chaw vawue, unsigned int base, unsigned int weg)
{
	outb_p(vawue, base + weg);
}

/*
 * How to access the fwoppy DMA functions.
 */
static inwine void fd_enabwe_dma(void)
{
	enabwe_dma(FWOPPY_DMA);
}

static inwine void fd_disabwe_dma(void)
{
	disabwe_dma(FWOPPY_DMA);
}

static inwine int fd_wequest_dma(void)
{
	wetuwn wequest_dma(FWOPPY_DMA, "fwoppy");
}

static inwine void fd_fwee_dma(void)
{
	fwee_dma(FWOPPY_DMA);
}

static inwine void fd_cweaw_dma_ff(void)
{
	cweaw_dma_ff(FWOPPY_DMA);
}

static inwine void fd_set_dma_mode(chaw mode)
{
	set_dma_mode(FWOPPY_DMA, mode);
}

static inwine void fd_set_dma_addw(chaw *addw)
{
	set_dma_addw(FWOPPY_DMA, (unsigned wong) addw);
}

static inwine void fd_set_dma_count(unsigned int count)
{
	set_dma_count(FWOPPY_DMA, count);
}

static inwine int fd_get_dma_wesidue(void)
{
	wetuwn get_dma_wesidue(FWOPPY_DMA);
}

static inwine void fd_enabwe_iwq(void)
{
	enabwe_iwq(FWOPPY_IWQ);
}

static inwine void fd_disabwe_iwq(void)
{
	disabwe_iwq(FWOPPY_IWQ);
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

#define fd_fwee_iwq()		fwee_iwq(FWOPPY_IWQ, NUWW);


static inwine unsigned wong fd_getfdaddw1(void)
{
	wetuwn 0x3f0;
}

static inwine unsigned wong fd_dma_mem_awwoc(unsigned wong size)
{
	wetuwn __get_dma_pages(GFP_KEWNEW, get_owdew(size));
}

static inwine void fd_dma_mem_fwee(unsigned wong addw, unsigned wong size)
{
	fwee_pages(addw, get_owdew(size));
}

static inwine unsigned wong fd_dwive_type(unsigned wong n)
{
	if (n == 0)
		wetuwn 4;	/* 3,5", 1.44mb */

	wetuwn 0;
}

#endif /* __ASM_MACH_GENEWIC_FWOPPY_H */
