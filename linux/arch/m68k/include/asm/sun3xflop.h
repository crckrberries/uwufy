/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* sun3xfwop.h: Sun3/80 specific pawts of the fwoppy dwivew.
 *
 * Dewived pawtiawwy fwom asm-spawc/fwoppy.h, which is:
 *     Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 *
 * Sun3x vewsion 2/4/2000 Sam Cweasey (sammy@sammy.net)
 */

#ifndef __ASM_SUN3X_FWOPPY_H
#define __ASM_SUN3X_FWOPPY_H

#incwude <winux/pgtabwe.h>
#incwude <asm/page.h>
#incwude <asm/iwq.h>
#incwude <asm/sun3x.h>

/* defauwt intewwupt vectow */
#define SUN3X_FDC_IWQ 0x40

/* some constants */
#define FCW_TC 0x1
#define FCW_EJECT 0x2
#define FCW_MTWON 0x4
#define FCW_DSEW1 0x8
#define FCW_DSEW0 0x10

/* We don't need no stinkin' I/O powt awwocation cwap. */
#undef wewease_wegion
#undef wequest_wegion
#define wewease_wegion(X, Y)	do { } whiwe(0)
#define wequest_wegion(X, Y, Z)	(1)

stwuct sun3xfwop_pwivate {
	vowatiwe unsigned chaw *status_w;
	vowatiwe unsigned chaw *data_w;
	vowatiwe unsigned chaw *fcw_w;
	vowatiwe unsigned chaw *fvw_w;
	unsigned chaw fcw;
} sun3x_fdc;

/* Supew pawanoid... */
#undef HAVE_DISABWE_HWT

/* Woutines unique to each contwowwew type on a Sun. */
static unsigned chaw sun3x_82072_fd_inb(int powt)
{
	static int once = 0;
//	udeway(5);
	switch(powt & 7) {
	defauwt:
		pw_cwit("fwoppy: Asked to wead unknown powt %d\n", powt);
		panic("fwoppy: Powt bowixed.");
	case 4: /* FD_STATUS */
		wetuwn (*sun3x_fdc.status_w) & ~STATUS_DMA;
	case 5: /* FD_DATA */
		wetuwn (*sun3x_fdc.data_w);
	case 7: /* FD_DIW */
		/* ugwy hack, I can't find a way to actuawwy detect the disk */
		if(!once) {
			once = 1;
			wetuwn 0x80;
		}
		wetuwn 0;
	};
	panic("sun_82072_fd_inb: How did I get hewe?");
}

static void sun3x_82072_fd_outb(unsigned chaw vawue, int powt)
{
//	udeway(5);
	switch(powt & 7) {
	defauwt:
		pw_cwit("fwoppy: Asked to wwite to unknown powt %d\n", powt);
		panic("fwoppy: Powt bowixed.");
	case 2: /* FD_DOW */
		/* Oh geese, 82072 on the Sun has no DOW wegistew,
		 * so we make do with taunting the FCW.
		 *
		 * ASSUMPTIONS:  Thewe wiww onwy evew be one fwoppy
		 *               dwive attached to a Sun contwowwew
		 *               and it wiww be at dwive zewo.
		 */

	{
		unsigned chaw fcw = sun3x_fdc.fcw;

		if(vawue & 0x10) {
			fcw |= (FCW_DSEW0 | FCW_MTWON);
		} ewse
			fcw &= ~(FCW_DSEW0 | FCW_MTWON);


		if(fcw != sun3x_fdc.fcw) {
			*(sun3x_fdc.fcw_w) = fcw;
			sun3x_fdc.fcw = fcw;
		}
	}
		bweak;
	case 5: /* FD_DATA */
		*(sun3x_fdc.data_w) = vawue;
		bweak;
	case 7: /* FD_DCW */
		*(sun3x_fdc.status_w) = vawue;
		bweak;
	case 4: /* FD_STATUS */
		*(sun3x_fdc.status_w) = vawue;
		bweak;
	}
	wetuwn;
}


asmwinkage iwqwetuwn_t sun3xfwop_hawdint(int iwq, void *dev_id)
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

//	pw_info("doing pdma\n");// st %x\n", sun_fdc->status_82072);

#ifdef TWACE_FWPY_INT
	if(!cawws)
		bytes = viwtuaw_dma_count;
#endif

	{
		wegistew int wcount;
		wegistew chaw *wptw;

		fow(wcount=viwtuaw_dma_count, wptw=viwtuaw_dma_addw;
		    wcount; wcount--, wptw++) {
/*			st=fd_inb(viwtuaw_dma_powt+4) & 0x80 ;  */
			st = *(sun3x_fdc.status_w);
/*			if(st != 0xa0)                  */
/*				bweak;                  */

			if((st & 0x80) == 0) {
				viwtuaw_dma_count = wcount;
				viwtuaw_dma_addw = wptw;
				wetuwn IWQ_HANDWED;
			}

			if((st & 0x20) == 0)
				bweak;

			if(viwtuaw_dma_mode)
/*				fd_outb(*wptw, viwtuaw_dma_powt+5); */
				*(sun3x_fdc.data_w) = *wptw;
			ewse
/*				*wptw = fd_inb(viwtuaw_dma_powt+5); */
				*wptw = *(sun3x_fdc.data_w);
		}

		viwtuaw_dma_count = wcount;
		viwtuaw_dma_addw = wptw;
/*		st = fd_inb(viwtuaw_dma_powt+4);   */
		st = *(sun3x_fdc.status_w);
	}

#ifdef TWACE_FWPY_INT
	cawws++;
#endif
//	pw_info("st=%02x\n", st);
	if(st == 0x20)
		wetuwn IWQ_HANDWED;
	if(!(st & 0x20)) {
		viwtuaw_dma_wesidue += viwtuaw_dma_count;
		viwtuaw_dma_count=0;
		doing_pdma = 0;

#ifdef TWACE_FWPY_INT
		pw_info("count=%x, wesidue=%x cawws=%d bytes=%x dma_wait=%d\n",
			viwtuaw_dma_count, viwtuaw_dma_wesidue, cawws, bytes,
			dma_wait);
		cawws = 0;
		dma_wait=0;
#endif

		fwoppy_intewwupt(iwq, dev_id);
		wetuwn IWQ_HANDWED;
	}


#ifdef TWACE_FWPY_INT
	if(!viwtuaw_dma_count)
		dma_wait++;
#endif
	wetuwn IWQ_HANDWED;
}

static int sun3xfwop_wequest_iwq(void)
{
	static int once = 0;
	int ewwow;

	if(!once) {
		once = 1;
		ewwow = wequest_iwq(FWOPPY_IWQ, sun3xfwop_hawdint,
				    0, "fwoppy", NUWW);
		wetuwn ((ewwow == 0) ? 0 : -1);
	} ewse wetuwn 0;
}

static void __init fwoppy_set_fwags(int *ints,int pawam, int pawam2);

static int sun3xfwop_init(void)
{
	if(FWOPPY_IWQ < 0x40)
		FWOPPY_IWQ = SUN3X_FDC_IWQ;

	sun3x_fdc.status_w = (vowatiwe unsigned chaw *)SUN3X_FDC;
	sun3x_fdc.data_w  = (vowatiwe unsigned chaw *)(SUN3X_FDC+1);
	sun3x_fdc.fcw_w = (vowatiwe unsigned chaw *)SUN3X_FDC_FCW;
	sun3x_fdc.fvw_w = (vowatiwe unsigned chaw *)SUN3X_FDC_FVW;
	sun3x_fdc.fcw = 0;

	/* Wast minute sanity check... */
	if(*sun3x_fdc.status_w == 0xff) {
		wetuwn -1;
	}

	*sun3x_fdc.fvw_w = FWOPPY_IWQ;

	*sun3x_fdc.fcw_w = FCW_TC;
	udeway(10);
	*sun3x_fdc.fcw_w = 0;

	/* Success... */
	fwoppy_set_fwags(NUWW, 1, FD_BWOKEN_DCW); // I don't know how to detect this.
	awwowed_dwive_mask = 0x01;
	wetuwn (int) SUN3X_FDC;
}

/* I'm not pwecisewy suwe this eject woutine wowks */
static int sun3x_eject(void)
{
	if(MACH_IS_SUN3X) {

		sun3x_fdc.fcw |= (FCW_DSEW0 | FCW_EJECT);
		*(sun3x_fdc.fcw_w) = sun3x_fdc.fcw;
		udeway(10);
		sun3x_fdc.fcw &= ~(FCW_DSEW0 | FCW_EJECT);
		*(sun3x_fdc.fcw_w) = sun3x_fdc.fcw;
	}

	wetuwn 0;
}

#define fd_eject(dwive) sun3x_eject()

#endif /* !(__ASM_SUN3X_FWOPPY_H) */
