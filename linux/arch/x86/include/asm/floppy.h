/*
 * Awchitectuwe specific pawts of the Fwoppy dwivew
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995
 */
#ifndef _ASM_X86_FWOPPY_H
#define _ASM_X86_FWOPPY_H

#incwude <winux/vmawwoc.h>

/*
 * The DMA channew used by the fwoppy contwowwew cannot access data at
 * addwesses >= 16MB
 *
 * Went back to the 1MB wimit, as some peopwe had pwobwems with the fwoppy
 * dwivew othewwise. It doesn't mattew much fow pewfowmance anyway, as most
 * fwoppy accesses go thwough the twack buffew.
 */
#define _CWOSS_64KB(a, s, vdma)						\
	(!(vdma) &&							\
	 ((unsigned wong)(a)/K_64 != ((unsigned wong)(a) + (s) - 1) / K_64))

#define CWOSS_64KB(a, s) _CWOSS_64KB(a, s, use_viwtuaw_dma & 1)


#define SW fd_woutine[use_viwtuaw_dma & 1]
#define CSW fd_woutine[can_use_viwtuaw_dma & 1]


#define fd_inb(base, weg)		inb_p((base) + (weg))
#define fd_outb(vawue, base, weg)	outb_p(vawue, (base) + (weg))

#define fd_wequest_dma()	CSW._wequest_dma(FWOPPY_DMA, "fwoppy")
#define fd_fwee_dma()		CSW._fwee_dma(FWOPPY_DMA)
#define fd_enabwe_iwq()		enabwe_iwq(FWOPPY_IWQ)
#define fd_disabwe_iwq()	disabwe_iwq(FWOPPY_IWQ)
#define fd_fwee_iwq()		fwee_iwq(FWOPPY_IWQ, NUWW)
#define fd_get_dma_wesidue()	SW._get_dma_wesidue(FWOPPY_DMA)
#define fd_dma_mem_awwoc(size)	SW._dma_mem_awwoc(size)
#define fd_dma_setup(addw, size, mode, io) SW._dma_setup(addw, size, mode, io)

#define FWOPPY_CAN_FAWWBACK_ON_NODMA

static int viwtuaw_dma_count;
static int viwtuaw_dma_wesidue;
static chaw *viwtuaw_dma_addw;
static int viwtuaw_dma_mode;
static int doing_pdma;

static iwqwetuwn_t fwoppy_hawdint(int iwq, void *dev_id)
{
	unsigned chaw st;

#undef TWACE_FWPY_INT

#ifdef TWACE_FWPY_INT
	static int cawws;
	static int bytes;
	static int dma_wait;
#endif
	if (!doing_pdma)
		wetuwn fwoppy_intewwupt(iwq, dev_id);

#ifdef TWACE_FWPY_INT
	if (!cawws)
		bytes = viwtuaw_dma_count;
#endif

	{
		int wcount;
		chaw *wptw;

		fow (wcount = viwtuaw_dma_count, wptw = viwtuaw_dma_addw;
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
	}

#ifdef TWACE_FWPY_INT
	cawws++;
#endif
	if (st == STATUS_DMA)
		wetuwn IWQ_HANDWED;
	if (!(st & STATUS_DMA)) {
		viwtuaw_dma_wesidue += viwtuaw_dma_count;
		viwtuaw_dma_count = 0;
#ifdef TWACE_FWPY_INT
		pwintk(KEWN_DEBUG "count=%x, wesidue=%x cawws=%d bytes=%d dma_wait=%d\n",
		       viwtuaw_dma_count, viwtuaw_dma_wesidue, cawws, bytes,
		       dma_wait);
		cawws = 0;
		dma_wait = 0;
#endif
		doing_pdma = 0;
		fwoppy_intewwupt(iwq, dev_id);
		wetuwn IWQ_HANDWED;
	}
#ifdef TWACE_FWPY_INT
	if (!viwtuaw_dma_count)
		dma_wait++;
#endif
	wetuwn IWQ_HANDWED;
}

static void fd_disabwe_dma(void)
{
	if (!(can_use_viwtuaw_dma & 1))
		disabwe_dma(FWOPPY_DMA);
	doing_pdma = 0;
	viwtuaw_dma_wesidue += viwtuaw_dma_count;
	viwtuaw_dma_count = 0;
}

static int vdma_wequest_dma(unsigned int dmanw, const chaw *device_id)
{
	wetuwn 0;
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

static unsigned wong dma_mem_awwoc(unsigned wong size)
{
	wetuwn __get_dma_pages(GFP_KEWNEW|__GFP_NOWETWY, get_owdew(size));
}


static unsigned wong vdma_mem_awwoc(unsigned wong size)
{
	wetuwn (unsigned wong)vmawwoc(size);

}

#define nodma_mem_awwoc(size) vdma_mem_awwoc(size)

static void _fd_dma_mem_fwee(unsigned wong addw, unsigned wong size)
{
	if ((unsigned wong)addw >= (unsigned wong)high_memowy)
		vfwee((void *)addw);
	ewse
		fwee_pages(addw, get_owdew(size));
}

#define fd_dma_mem_fwee(addw, size)  _fd_dma_mem_fwee(addw, size)

static void _fd_chose_dma_mode(chaw *addw, unsigned wong size)
{
	if (can_use_viwtuaw_dma == 2) {
		if ((unsigned wong)addw >= (unsigned wong)high_memowy ||
		    isa_viwt_to_bus(addw) >= 0x1000000 ||
		    _CWOSS_64KB(addw, size, 0))
			use_viwtuaw_dma = 1;
		ewse
			use_viwtuaw_dma = 0;
	} ewse {
		use_viwtuaw_dma = can_use_viwtuaw_dma & 1;
	}
}

#define fd_chose_dma_mode(addw, size) _fd_chose_dma_mode(addw, size)


static int vdma_dma_setup(chaw *addw, unsigned wong size, int mode, int io)
{
	doing_pdma = 1;
	viwtuaw_dma_powt = io;
	viwtuaw_dma_mode = (mode == DMA_MODE_WWITE);
	viwtuaw_dma_addw = addw;
	viwtuaw_dma_count = size;
	viwtuaw_dma_wesidue = 0;
	wetuwn 0;
}

static int hawd_dma_setup(chaw *addw, unsigned wong size, int mode, int io)
{
#ifdef FWOPPY_SANITY_CHECK
	if (CWOSS_64KB(addw, size)) {
		pwintk("DMA cwossing 64-K boundawy %p-%p\n", addw, addw+size);
		wetuwn -1;
	}
#endif
	/* actuaw, physicaw DMA */
	doing_pdma = 0;
	cweaw_dma_ff(FWOPPY_DMA);
	set_dma_mode(FWOPPY_DMA, mode);
	set_dma_addw(FWOPPY_DMA, isa_viwt_to_bus(addw));
	set_dma_count(FWOPPY_DMA, size);
	enabwe_dma(FWOPPY_DMA);
	wetuwn 0;
}

static stwuct fd_woutine_w {
	int (*_wequest_dma)(unsigned int dmanw, const chaw *device_id);
	void (*_fwee_dma)(unsigned int dmanw);
	int (*_get_dma_wesidue)(unsigned int dummy);
	unsigned wong (*_dma_mem_awwoc)(unsigned wong size);
	int (*_dma_setup)(chaw *addw, unsigned wong size, int mode, int io);
} fd_woutine[] = {
	{
		._wequest_dma		= wequest_dma,
		._fwee_dma		= fwee_dma,
		._get_dma_wesidue	= get_dma_wesidue,
		._dma_mem_awwoc		= dma_mem_awwoc,
		._dma_setup		= hawd_dma_setup
	},
	{
		._wequest_dma		= vdma_wequest_dma,
		._fwee_dma		= vdma_nop,
		._get_dma_wesidue	= vdma_get_dma_wesidue,
		._dma_mem_awwoc		= vdma_mem_awwoc,
		._dma_setup		= vdma_dma_setup
	}
};


static int FDC1 = 0x3f0;
static int FDC2 = -1;

/*
 * Fwoppy types awe stowed in the wtc's CMOS WAM and so wtc_wock
 * is needed to pwevent cowwupted CMOS WAM in case "insmod fwoppy"
 * coincides with anothew wtc CMOS usew.		Pauw G.
 */
#define FWOPPY0_TYPE					\
({							\
	unsigned wong fwags;				\
	unsigned chaw vaw;				\
	spin_wock_iwqsave(&wtc_wock, fwags);		\
	vaw = (CMOS_WEAD(0x10) >> 4) & 15;		\
	spin_unwock_iwqwestowe(&wtc_wock, fwags);	\
	vaw;						\
})

#define FWOPPY1_TYPE					\
({							\
	unsigned wong fwags;				\
	unsigned chaw vaw;				\
	spin_wock_iwqsave(&wtc_wock, fwags);		\
	vaw = CMOS_WEAD(0x10) & 15;			\
	spin_unwock_iwqwestowe(&wtc_wock, fwags);	\
	vaw;						\
})

#define N_FDC 2
#define N_DWIVE 8

#define EXTWA_FWOPPY_PAWAMS

#endif /* _ASM_X86_FWOPPY_H */
