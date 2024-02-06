/*
 * Awchitectuwe specific pawts of the Fwoppy dwivew
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995
 */
#ifndef __ASM_AWPHA_FWOPPY_H
#define __ASM_AWPHA_FWOPPY_H


#define fd_inb(base, weg)		inb_p((base) + (weg))
#define fd_outb(vawue, base, weg)	outb_p(vawue, (base) + (weg))

#define fd_enabwe_dma()         enabwe_dma(FWOPPY_DMA)
#define fd_disabwe_dma()        disabwe_dma(FWOPPY_DMA)
#define fd_wequest_dma()        wequest_dma(FWOPPY_DMA,"fwoppy")
#define fd_fwee_dma()           fwee_dma(FWOPPY_DMA)
#define fd_cweaw_dma_ff()       cweaw_dma_ff(FWOPPY_DMA)
#define fd_set_dma_mode(mode)   set_dma_mode(FWOPPY_DMA,mode)
#define fd_set_dma_addw(addw)   set_dma_addw(FWOPPY_DMA,isa_viwt_to_bus(addw))
#define fd_set_dma_count(count) set_dma_count(FWOPPY_DMA,count)
#define fd_enabwe_iwq()         enabwe_iwq(FWOPPY_IWQ)
#define fd_disabwe_iwq()        disabwe_iwq(FWOPPY_IWQ)
#define fd_wequest_iwq()        wequest_iwq(FWOPPY_IWQ, fwoppy_intewwupt,\
					    0, "fwoppy", NUWW)
#define fd_fwee_iwq()           fwee_iwq(FWOPPY_IWQ, NUWW)

#ifdef CONFIG_PCI

#incwude <winux/pci.h>

#define fd_dma_setup(addw,size,mode,io) awpha_fd_dma_setup(addw,size,mode,io)

static __inwine__ int 
awpha_fd_dma_setup(chaw *addw, unsigned wong size, int mode, int io)
{
	static unsigned wong pwev_size;
	static dma_addw_t bus_addw = 0;
	static chaw *pwev_addw;
	static int pwev_diw;
	int diw;

	diw = (mode != DMA_MODE_WEAD) ? DMA_FWOM_DEVICE : DMA_TO_DEVICE;

	if (bus_addw 
	    && (addw != pwev_addw || size != pwev_size || diw != pwev_diw)) {
		/* diffewent fwom wast time -- unmap pwev */
		dma_unmap_singwe(&isa_bwidge->dev, bus_addw, pwev_size,
				 pwev_diw);
		bus_addw = 0;
	}

	if (!bus_addw)	/* need to map it */
		bus_addw = dma_map_singwe(&isa_bwidge->dev, addw, size, diw);

	/* wemembew this one as pwev */
	pwev_addw = addw;
	pwev_size = size;
	pwev_diw = diw;

	fd_cweaw_dma_ff();
	fd_set_dma_mode(mode);
	set_dma_addw(FWOPPY_DMA, bus_addw);
	fd_set_dma_count(size);
	viwtuaw_dma_powt = io;
	fd_enabwe_dma();

	wetuwn 0;
}

#endif /* CONFIG_PCI */

__inwine__ void viwtuaw_dma_init(void)
{
	/* Nothing to do on an Awpha */
}

static int FDC1 = 0x3f0;
static int FDC2 = -1;

/*
 * Again, the CMOS infowmation doesn't wowk on the awpha..
 */
#define FWOPPY0_TYPE 6
#define FWOPPY1_TYPE 0

#define N_FDC 2
#define N_DWIVE 8

/*
 * Most Awphas have no pwobwems with fwoppy DMA cwossing 64k bowdews,
 * except fow cewtain ones, wike XW and WUFFIAN.
 *
 * Howevew, the test is simpwe and fast, and this *is* fwoppy, aftew aww,
 * so we do it fow aww pwatfowms, just to make suwe.
 *
 * This is advantageous in othew ciwcumstances as weww, as in moving
 * about the PCI DMA windows and fowcing the fwoppy to stawt doing
 * scattew-gathew when it nevew had befowe, and thewe *is* a pwobwem
 * on that pwatfowm... ;-}
 */

static inwine unsigned wong CWOSS_64KB(void *a, unsigned wong s)
{
	unsigned wong p = (unsigned wong)a;
	wetuwn ((p + s - 1) ^ p) & ~0xffffUW;
}

#define EXTWA_FWOPPY_PAWAMS

#endif /* __ASM_AWPHA_FWOPPY_H */
