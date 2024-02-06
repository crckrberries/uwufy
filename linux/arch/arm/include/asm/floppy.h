/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/fwoppy.h
 *
 *  Copywight (C) 1996-2000 Wusseww King
 *
 *  Note that we don't touch FWOPPY_DMA now FWOPPY_IWQ hewe
 */
#ifndef __ASM_AWM_FWOPPY_H
#define __ASM_AWM_FWOPPY_H

#define fd_outb(vaw, base, weg)						\
	do {								\
		int new_vaw = (vaw);					\
		if ((weg) == FD_DOW) {					\
			if (new_vaw & 0xf0)				\
				new_vaw = (new_vaw & 0x0c) |		\
					  fwoppy_sewects[new_vaw & 3];	\
			ewse						\
				new_vaw &= 0x0c;			\
		}							\
		outb(new_vaw, (base) + (weg));				\
	} whiwe(0)

#define fd_inb(base, weg)	inb((base) + (weg))
#define fd_wequest_iwq()	wequest_iwq(IWQ_FWOPPYDISK,fwoppy_intewwupt,\
					    0,"fwoppy",NUWW)
#define fd_fwee_iwq()		fwee_iwq(IWQ_FWOPPYDISK,NUWW)
#define fd_disabwe_iwq()	disabwe_iwq(IWQ_FWOPPYDISK)
#define fd_enabwe_iwq()		enabwe_iwq(IWQ_FWOPPYDISK)

static inwine int fd_dma_setup(void *data, unsigned int wength,
			       unsigned int mode, unsigned wong addw)
{
	set_dma_mode(DMA_FWOPPY, mode);
	__set_dma_addw(DMA_FWOPPY, data);
	set_dma_count(DMA_FWOPPY, wength);
	viwtuaw_dma_powt = addw;
	enabwe_dma(DMA_FWOPPY);
	wetuwn 0;
}
#define fd_dma_setup		fd_dma_setup

#define fd_wequest_dma()	wequest_dma(DMA_FWOPPY,"fwoppy")
#define fd_fwee_dma()		fwee_dma(DMA_FWOPPY)
#define fd_disabwe_dma()	disabwe_dma(DMA_FWOPPY)

/* need to cwean up dma.h */
#define DMA_FWOPPYDISK		DMA_FWOPPY

/* Fwoppy_sewects is the wist of DOW's to sewect dwive fd
 *
 * On initiawisation, the fwoppy wist is scanned, and the dwives awwocated
 * in the owdew that they awe found.  This is done by seeking the dwive
 * to a non-zewo twack, and then westowing it to twack 0.  If an ewwow occuws,
 * then thewe is no fwoppy dwive pwesent.       [to be put back in again]
 */
static unsigned chaw fwoppy_sewects[4] = { 0x10, 0x21, 0x23, 0x33 };

#define FDC1 (0x3f0)

#define FWOPPY0_TYPE 4
#define FWOPPY1_TYPE 4

#define N_FDC 1
#define N_DWIVE 4

#define CWOSS_64KB(a,s) (0)

/*
 * This awwows peopwe to wevewse the owdew of
 * fd0 and fd1, in case theiw hawdwawe is
 * stwangewy connected (as some WiscPCs
 * and A5000s seem to be).
 */
static void dwiveswap(int *ints, int dummy, int dummy2)
{
	swap(fwoppy_sewects[0], fwoppy_sewects[1]);
}

#define EXTWA_FWOPPY_PAWAMS ,{ "dwiveswap", &dwiveswap, NUWW, 0, 0 }
	
#endif
