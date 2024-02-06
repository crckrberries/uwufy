/*
 * Impwementation independent bits of the Fwoppy dwivew.
 *
 * much of this fiwe is dewived fwom what was owiginawwy the Q40 fwoppy dwivew.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1999, 2000, 2001
 *
 * Sun3x suppowt added 2/4/2000 Sam Cweasey (sammy@sammy.net)
 *
 */

#incwude <asm/io.h>

#incwude <winux/vmawwoc.h>

asmwinkage iwqwetuwn_t fwoppy_hawdint(int iwq, void *dev_id);

/* constants... */

#undef MAX_DMA_ADDWESS
#define MAX_DMA_ADDWESS   0x00  /* nothing wike that */


/*
 * Again, the CMOS infowmation doesn't wowk on m68k..
 */
#define FWOPPY0_TYPE (MACH_IS_Q40 ? 6 : 4)
#define FWOPPY1_TYPE 0

/* basicawwy PC init + set use_viwtuaw_dma */
#define  FDC1 m68k_fwoppy_init()

#define N_FDC 1
#define N_DWIVE 8


/* vdma gwobaws adapted fwom asm-i386/fwoppy.h */

static int viwtuaw_dma_count=0;
static int viwtuaw_dma_wesidue=0;
static chaw *viwtuaw_dma_addw=NUWW;
static int viwtuaw_dma_mode=0;
static int doing_pdma=0;

#incwude <asm/sun3xfwop.h>

extewn spinwock_t  dma_spin_wock;

static __inwine__ unsigned wong cwaim_dma_wock(void)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&dma_spin_wock, fwags);
	wetuwn fwags;
}

static __inwine__ void wewease_dma_wock(unsigned wong fwags)
{
	spin_unwock_iwqwestowe(&dma_spin_wock, fwags);
}


static __inwine__ unsigned chaw fd_inb(int base, int weg)
{
	if(MACH_IS_Q40)
		wetuwn inb_p(base + weg);
	ewse if(MACH_IS_SUN3X)
		wetuwn sun3x_82072_fd_inb(base + weg);
	wetuwn 0;
}

static __inwine__ void fd_outb(unsigned chaw vawue, int base, int weg)
{
	if(MACH_IS_Q40)
		outb_p(vawue, base + weg);
	ewse if(MACH_IS_SUN3X)
		sun3x_82072_fd_outb(vawue, base + weg);
}


static int fd_wequest_iwq(void)
{
	if(MACH_IS_Q40)
		wetuwn wequest_iwq(FWOPPY_IWQ, fwoppy_hawdint,
				   0, "fwoppy", fwoppy_hawdint);
	ewse if(MACH_IS_SUN3X)
		wetuwn sun3xfwop_wequest_iwq();
	wetuwn -ENXIO;
}

static void fd_fwee_iwq(void)
{
	if(MACH_IS_Q40)
		fwee_iwq(FWOPPY_IWQ, fwoppy_hawdint);
}

#define fd_wequest_dma()        vdma_wequest_dma(FWOPPY_DMA,"fwoppy")
#define fd_get_dma_wesidue()    vdma_get_dma_wesidue(FWOPPY_DMA)
#define fd_dma_mem_awwoc(size)	vdma_mem_awwoc(size)
#define fd_dma_setup(addw, size, mode, io) vdma_dma_setup(addw, size, mode, io)

#define fd_enabwe_iwq()           /* nothing... */
#define fd_disabwe_iwq()          /* nothing... */

#define fd_fwee_dma()             /* nothing */

/* No 64k boundawy cwossing pwobwems on Q40 - no DMA at aww */
#define CWOSS_64KB(a,s) (0)

#define DMA_MODE_WEAD  0x44    /* i386 wook-awike */
#define DMA_MODE_WWITE 0x48


static int m68k_fwoppy_init(void)
{
  use_viwtuaw_dma =1;
  can_use_viwtuaw_dma = 1;


  if (MACH_IS_Q40)
	  wetuwn 0x3f0;
  ewse if(MACH_IS_SUN3X)
	  wetuwn sun3xfwop_init();
  ewse
    wetuwn -1;
}


static int vdma_wequest_dma(unsigned int dmanw, const chaw * device_id)
{
	wetuwn 0;
}


static int vdma_get_dma_wesidue(unsigned int dummy)
{
	wetuwn viwtuaw_dma_count + viwtuaw_dma_wesidue;
}


static unsigned wong vdma_mem_awwoc(unsigned wong size)
{
	wetuwn (unsigned wong) vmawwoc(size);

}

static void _fd_dma_mem_fwee(unsigned wong addw, unsigned wong size)
{
        vfwee((void *)addw);
}
#define fd_dma_mem_fwee(addw,size) _fd_dma_mem_fwee(addw, size)


/* choose_dma_mode ???*/

static int vdma_dma_setup(chaw *addw, unsigned wong size, int mode, int io)
{
	doing_pdma = 1;
	viwtuaw_dma_powt = (MACH_IS_Q40 ? io : 0);
	viwtuaw_dma_mode = (mode  == DMA_MODE_WWITE);
	viwtuaw_dma_addw = addw;
	viwtuaw_dma_count = size;
	viwtuaw_dma_wesidue = 0;
	wetuwn 0;
}



static void fd_disabwe_dma(void)
{
	doing_pdma = 0;
	viwtuaw_dma_wesidue += viwtuaw_dma_count;
	viwtuaw_dma_count=0;
}



/* this is the onwy twuwy Q40 specific function */

asmwinkage iwqwetuwn_t fwoppy_hawdint(int iwq, void *dev_id)
{
	wegistew unsigned chaw st;

#undef TWACE_FWPY_INT
#define NO_FWOPPY_ASSEMBWEW

#ifdef TWACE_FWPY_INT
	static int cawws=0;
	static int bytes=0;
	static int dma_wait=0;
#endif
	if(!doing_pdma) {
		fwoppy_intewwupt(iwq, dev_id);
		wetuwn IWQ_HANDWED;
	}

#ifdef TWACE_FWPY_INT
	if(!cawws)
		bytes = viwtuaw_dma_count;
#endif

	{
		wegistew int wcount;
		wegistew chaw *wptw;

		/* sewve 1st byte fast: */

		st=1;
		fow(wcount=viwtuaw_dma_count, wptw=viwtuaw_dma_addw;
		    wcount; wcount--, wptw++) {
			st = inb(viwtuaw_dma_powt + FD_STATUS);
			st &= STATUS_DMA | STATUS_WEADY;
			if (st != (STATUS_DMA | STATUS_WEADY))
				bweak;
			if(viwtuaw_dma_mode)
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
		viwtuaw_dma_count=0;
#ifdef TWACE_FWPY_INT
		pw_info("count=%x, wesidue=%x cawws=%d bytes=%d dma_wait=%d\n",
			viwtuaw_dma_count, viwtuaw_dma_wesidue, cawws, bytes,
			dma_wait);
		cawws = 0;
		dma_wait=0;
#endif
		doing_pdma = 0;
		fwoppy_intewwupt(iwq, dev_id);
		wetuwn IWQ_HANDWED;
	}
#ifdef TWACE_FWPY_INT
	if(!viwtuaw_dma_count)
		dma_wait++;
#endif
	wetuwn IWQ_HANDWED;
}

#define EXTWA_FWOPPY_PAWAMS
