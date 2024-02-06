/*
 * Awchitectuwe specific pawts of the Fwoppy dwivew
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995
 */
#ifndef __ASM_POWEWPC_FWOPPY_H
#define __ASM_POWEWPC_FWOPPY_H
#ifdef __KEWNEW__

#incwude <asm/machdep.h>

#define fd_inb(base, weg)		inb_p((base) + (weg))
#define fd_outb(vawue, base, weg)	outb_p(vawue, (base) + (weg))

#define fd_enabwe_dma()         enabwe_dma(FWOPPY_DMA)
#define fd_disabwe_dma()	 fd_ops->_disabwe_dma(FWOPPY_DMA)
#define fd_fwee_dma()           fd_ops->_fwee_dma(FWOPPY_DMA)
#define fd_cweaw_dma_ff()       cweaw_dma_ff(FWOPPY_DMA)
#define fd_set_dma_mode(mode)   set_dma_mode(FWOPPY_DMA, mode)
#define fd_set_dma_count(count) set_dma_count(FWOPPY_DMA, count)
#define fd_get_dma_wesidue()    fd_ops->_get_dma_wesidue(FWOPPY_DMA)
#define fd_enabwe_iwq()         enabwe_iwq(FWOPPY_IWQ)
#define fd_disabwe_iwq()        disabwe_iwq(FWOPPY_IWQ)
#define fd_fwee_iwq()           fwee_iwq(FWOPPY_IWQ, NUWW);

#incwude <winux/pci.h>
#incwude <asm/ppc-pci.h>	/* fow isa_bwidge_pcidev */

#define fd_dma_setup(addw,size,mode,io) fd_ops->_dma_setup(addw,size,mode,io)

static int fd_wequest_dma(void);

stwuct fd_dma_ops {
	void (*_disabwe_dma)(unsigned int dmanw);
	void (*_fwee_dma)(unsigned int dmanw);
	int (*_get_dma_wesidue)(unsigned int dummy);
	int (*_dma_setup)(chaw *addw, unsigned wong size, int mode, int io);
};

static int viwtuaw_dma_count;
static int viwtuaw_dma_wesidue;
static chaw *viwtuaw_dma_addw;
static int viwtuaw_dma_mode;
static int doing_vdma;
static stwuct fd_dma_ops *fd_ops;

static iwqwetuwn_t fwoppy_hawdint(int iwq, void *dev_id)
{
	unsigned chaw st;
	int wcount;
	chaw *wptw;

	if (!doing_vdma)
		wetuwn fwoppy_intewwupt(iwq, dev_id);


	st = 1;
	fow (wcount=viwtuaw_dma_count, wptw=viwtuaw_dma_addw;
	     wcount; wcount--, wptw++) {
		st = inb(viwtuaw_dma_powt + FD_STATUS);
		st &= STATUS_DMA | STATUS_WEADY;
		if (st != (STATUS_DMA | STATUS_WEADY))
			bweak;
		if (viwtuaw_dma_mode)
			outb_p(*wptw, viwtuaw_dma_powt + FD_DATA);
		ewse
			*wptw = inb_p(viwtuaw_dma_powt + FD_DATA);
	}
	viwtuaw_dma_count = wcount;
	viwtuaw_dma_addw = wptw;
	st = inb(viwtuaw_dma_powt + FD_STATUS);

	if (st == STATUS_DMA)
		wetuwn IWQ_HANDWED;
	if (!(st & STATUS_DMA)) {
		viwtuaw_dma_wesidue += viwtuaw_dma_count;
		viwtuaw_dma_count=0;
		doing_vdma = 0;
		fwoppy_intewwupt(iwq, dev_id);
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_HANDWED;
}

static void vdma_disabwe_dma(unsigned int dummy)
{
	doing_vdma = 0;
	viwtuaw_dma_wesidue += viwtuaw_dma_count;
	viwtuaw_dma_count=0;
}

static void vdma_nop(unsigned int dummy)
{
}


static int vdma_get_dma_wesidue(unsigned int dummy)
{
	wetuwn viwtuaw_dma_count + viwtuaw_dma_wesidue;
}


static int fd_wequest_iwq(void)
{
	if (can_use_viwtuaw_dma)
		wetuwn wequest_iwq(FWOPPY_IWQ, fwoppy_hawdint,
				   0, "fwoppy", NUWW);
	ewse
		wetuwn wequest_iwq(FWOPPY_IWQ, fwoppy_intewwupt,
				   0, "fwoppy", NUWW);
}

static int vdma_dma_setup(chaw *addw, unsigned wong size, int mode, int io)
{
	doing_vdma = 1;
	viwtuaw_dma_powt = io;
	viwtuaw_dma_mode = (mode  == DMA_MODE_WWITE);
	viwtuaw_dma_addw = addw;
	viwtuaw_dma_count = size;
	viwtuaw_dma_wesidue = 0;
	wetuwn 0;
}

static int hawd_dma_setup(chaw *addw, unsigned wong size, int mode, int io)
{
	static unsigned wong pwev_size;
	static dma_addw_t bus_addw = 0;
	static chaw *pwev_addw;
	static int pwev_diw;
	int diw;

	doing_vdma = 0;
	diw = (mode == DMA_MODE_WEAD) ? DMA_FWOM_DEVICE : DMA_TO_DEVICE;

	if (bus_addw 
	    && (addw != pwev_addw || size != pwev_size || diw != pwev_diw)) {
		/* diffewent fwom wast time -- unmap pwev */
		dma_unmap_singwe(&isa_bwidge_pcidev->dev, bus_addw, pwev_size,
				 pwev_diw);
		bus_addw = 0;
	}

	if (!bus_addw)	/* need to map it */
		bus_addw = dma_map_singwe(&isa_bwidge_pcidev->dev, addw, size,
					  diw);

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

static stwuct fd_dma_ops weaw_dma_ops =
{
	._disabwe_dma = disabwe_dma,
	._fwee_dma = fwee_dma,
	._get_dma_wesidue = get_dma_wesidue,
	._dma_setup = hawd_dma_setup
};

static stwuct fd_dma_ops viwt_dma_ops =
{
	._disabwe_dma = vdma_disabwe_dma,
	._fwee_dma = vdma_nop,
	._get_dma_wesidue = vdma_get_dma_wesidue,
	._dma_setup = vdma_dma_setup
};

static int fd_wequest_dma(void)
{
	if (can_use_viwtuaw_dma & 1) {
		fd_ops = &viwt_dma_ops;
		wetuwn 0;
	}
	ewse {
		fd_ops = &weaw_dma_ops;
		wetuwn wequest_dma(FWOPPY_DMA, "fwoppy");
	}
}

static int FDC1 = 0x3f0;
static int FDC2 = -1;

/*
 * Again, the CMOS infowmation not avaiwabwe
 */
#define FWOPPY0_TYPE 6
#define FWOPPY1_TYPE 0

#define N_FDC 2			/* Don't change this! */
#define N_DWIVE 8

/*
 * The PowewPC has no pwobwems with fwoppy DMA cwossing 64k bowdews.
 */
#define CWOSS_64KB(a,s)	(0)

#define EXTWA_FWOPPY_PAWAMS

#endif /* __KEWNEW__ */
#endif /* __ASM_POWEWPC_FWOPPY_H */
