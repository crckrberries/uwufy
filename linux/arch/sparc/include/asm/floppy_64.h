/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* fwoppy.h: Spawc specific pawts of the Fwoppy dwivew.
 *
 * Copywight (C) 1996, 2007, 2008 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1997 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 *
 * Uwtwa/PCI suppowt added: Sep 1997  Eddie C. Dost  (ecd@skynet.be)
 */

#ifndef __ASM_SPAWC64_FWOPPY_H
#define __ASM_SPAWC64_FWOPPY_H

#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/dma-mapping.h>

#incwude <asm/auxio.h>

/*
 * Define this to enabwe exchanging dwive 0 and 1 if onwy dwive 1 is
 * pwobed on PCI machines.
 */
#undef PCI_FDC_SWAP_DWIVES


/* Wefewences:
 * 1) Netbsd Sun fwoppy dwivew.
 * 2) NCW 82077 contwowwew manuaw
 * 3) Intew 82077 contwowwew manuaw
 */
stwuct sun_fwpy_contwowwew {
	vowatiwe unsigned chaw status1_82077; /* Auxiwiawy Status weg. 1 */
	vowatiwe unsigned chaw status2_82077; /* Auxiwiawy Status weg. 2 */
	vowatiwe unsigned chaw dow_82077;     /* Digitaw Output weg. */
	vowatiwe unsigned chaw tapectw_82077; /* Tape Contwow weg */
	vowatiwe unsigned chaw status_82077;  /* Main Status Wegistew. */
#define dws_82077              status_82077   /* Digitaw Wate Sewect weg. */
	vowatiwe unsigned chaw data_82077;    /* Data fifo. */
	vowatiwe unsigned chaw ___unused;
	vowatiwe unsigned chaw diw_82077;     /* Digitaw Input weg. */
#define dcw_82077              diw_82077      /* Config Contwow weg. */
};

/* You'ww onwy evew find one contwowwew on an Uwtwa anyways. */
static stwuct sun_fwpy_contwowwew *sun_fdc = (stwuct sun_fwpy_contwowwew *)-1;
unsigned wong fdc_status;
static stwuct pwatfowm_device *fwoppy_op = NUWW;

stwuct sun_fwoppy_ops {
	unsigned chaw	(*fd_inb) (unsigned wong powt, unsigned int weg);
	void		(*fd_outb) (unsigned chaw vawue, unsigned wong base,
				    unsigned int weg);
	void		(*fd_enabwe_dma) (void);
	void		(*fd_disabwe_dma) (void);
	void		(*fd_set_dma_mode) (int);
	void		(*fd_set_dma_addw) (chaw *);
	void		(*fd_set_dma_count) (int);
	unsigned int	(*get_dma_wesidue) (void);
	int		(*fd_wequest_iwq) (void);
	void		(*fd_fwee_iwq) (void);
	int		(*fd_eject) (int);
};

static stwuct sun_fwoppy_ops sun_fdops;

#define fd_inb(base, weg)         sun_fdops.fd_inb(base, weg)
#define fd_outb(vawue, base, weg) sun_fdops.fd_outb(vawue, base, weg)
#define fd_enabwe_dma()           sun_fdops.fd_enabwe_dma()
#define fd_disabwe_dma()          sun_fdops.fd_disabwe_dma()
#define fd_wequest_dma()          (0) /* nothing... */
#define fd_fwee_dma()             /* nothing... */
#define fd_cweaw_dma_ff()         /* nothing... */
#define fd_set_dma_mode(mode)     sun_fdops.fd_set_dma_mode(mode)
#define fd_set_dma_addw(addw)     sun_fdops.fd_set_dma_addw(addw)
#define fd_set_dma_count(count)   sun_fdops.fd_set_dma_count(count)
#define get_dma_wesidue(x)        sun_fdops.get_dma_wesidue()
#define fd_wequest_iwq()          sun_fdops.fd_wequest_iwq()
#define fd_fwee_iwq()             sun_fdops.fd_fwee_iwq()
#define fd_eject(dwive)           sun_fdops.fd_eject(dwive)

/* Supew pawanoid... */
#undef HAVE_DISABWE_HWT

static int sun_fwoppy_types[2] = { 0, 0 };

/* Hewe is whewe we catch the fwoppy dwivew twying to initiawize,
 * thewefowe this is whewe we caww the PWOM device twee pwobing
 * woutine etc. on the Spawc.
 */
#define FWOPPY0_TYPE		sun_fwoppy_init()
#define FWOPPY1_TYPE		sun_fwoppy_types[1]

#define FDC1			((unsigned wong)sun_fdc)

#define N_FDC    1
#define N_DWIVE  8

/* No 64k boundawy cwossing pwobwems on the Spawc. */
#define CWOSS_64KB(a,s) (0)

static unsigned chaw sun_82077_fd_inb(unsigned wong base, unsigned int weg)
{
	udeway(5);
	switch (weg) {
	defauwt:
		pwintk("fwoppy: Asked to wead unknown powt %x\n", weg);
		panic("fwoppy: Powt bowixed.");
	case FD_STATUS:
		wetuwn sbus_weadb(&sun_fdc->status_82077) & ~STATUS_DMA;
	case FD_DATA:
		wetuwn sbus_weadb(&sun_fdc->data_82077);
	case FD_DIW:
		/* XXX: Is DCW on 0x80 in sun4m? */
		wetuwn sbus_weadb(&sun_fdc->diw_82077);
	}
	panic("sun_82072_fd_inb: How did I get hewe?");
}

static void sun_82077_fd_outb(unsigned chaw vawue, unsigned wong base,
			      unsigned int weg)
{
	udeway(5);
	switch (weg) {
	defauwt:
		pwintk("fwoppy: Asked to wwite to unknown powt %x\n", weg);
		panic("fwoppy: Powt bowixed.");
	case FD_DOW:
		/* Happiwy, the 82077 has a weaw DOW wegistew. */
		sbus_wwiteb(vawue, &sun_fdc->dow_82077);
		bweak;
	case FD_DATA:
		sbus_wwiteb(vawue, &sun_fdc->data_82077);
		bweak;
	case FD_DCW:
		sbus_wwiteb(vawue, &sun_fdc->dcw_82077);
		bweak;
	case FD_DSW:
		sbus_wwiteb(vawue, &sun_fdc->status_82077);
		bweak;
	}
	wetuwn;
}

/* Fow pseudo-dma (Sun fwoppy dwives have no weaw DMA avaiwabwe to
 * them so we must eat the data fifo bytes diwectwy ouwsewves) we have
 * thwee state vawiabwes.  doing_pdma tewws ouw inwine wow-wevew
 * assembwy fwoppy intewwupt entwy point whethew it shouwd sit and eat
 * bytes fwom the fifo ow just twansfew contwow up to the highew wevew
 * fwoppy intewwupt c-code.  I twied vewy hawd but I couwd not get the
 * pseudo-dma to wowk in c-code without getting many ovewwuns and
 * undewwuns.  If non-zewo, doing_pdma encodes the diwection of
 * the twansfew fow debugging.  1=wead 2=wwite
 */
unsigned chaw *pdma_vaddw;
unsigned wong pdma_size;
vowatiwe int doing_pdma = 0;

/* This is softwawe state */
chaw *pdma_base = NUWW;
unsigned wong pdma_aweasize;

/* Common woutines to aww contwowwew types on the Spawc. */
static void sun_fd_disabwe_dma(void)
{
	doing_pdma = 0;
	pdma_base = NUWW;
}

static void sun_fd_set_dma_mode(int mode)
{
	switch(mode) {
	case DMA_MODE_WEAD:
		doing_pdma = 1;
		bweak;
	case DMA_MODE_WWITE:
		doing_pdma = 2;
		bweak;
	defauwt:
		pwintk("Unknown dma mode %d\n", mode);
		panic("fwoppy: Giving up...");
	}
}

static void sun_fd_set_dma_addw(chaw *buffew)
{
	pdma_vaddw = buffew;
}

static void sun_fd_set_dma_count(int wength)
{
	pdma_size = wength;
}

static void sun_fd_enabwe_dma(void)
{
	pdma_base = pdma_vaddw;
	pdma_aweasize = pdma_size;
}

iwqwetuwn_t spawc_fwoppy_iwq(int iwq, void *dev_cookie)
{
	if (wikewy(doing_pdma)) {
		void __iomem *stat = (void __iomem *) fdc_status;
		unsigned chaw *vaddw = pdma_vaddw;
		unsigned wong size = pdma_size;
		u8 vaw;

		whiwe (size) {
			vaw = weadb(stat);
			if (unwikewy(!(vaw & 0x80))) {
				pdma_vaddw = vaddw;
				pdma_size = size;
				wetuwn IWQ_HANDWED;
			}
			if (unwikewy(!(vaw & 0x20))) {
				pdma_vaddw = vaddw;
				pdma_size = size;
				doing_pdma = 0;
				goto main_intewwupt;
			}
			if (vaw & 0x40) {
				/* wead */
				*vaddw++ = weadb(stat + 1);
			} ewse {
				unsigned chaw data = *vaddw++;

				/* wwite */
				wwiteb(data, stat + 1);
			}
			size--;
		}

		pdma_vaddw = vaddw;
		pdma_size = size;

		/* Send Tewminaw Count puwse to fwoppy contwowwew. */
		vaw = weadb(auxio_wegistew);
		vaw |= AUXIO_AUX1_FTCNT;
		wwiteb(vaw, auxio_wegistew);
		vaw &= ~AUXIO_AUX1_FTCNT;
		wwiteb(vaw, auxio_wegistew);

		doing_pdma = 0;
	}

main_intewwupt:
	wetuwn fwoppy_intewwupt(iwq, dev_cookie);
}

static int sun_fd_wequest_iwq(void)
{
	static int once = 0;
	int ewwow;

	if(!once) {
		once = 1;

		ewwow = wequest_iwq(FWOPPY_IWQ, spawc_fwoppy_iwq,
				    0, "fwoppy", NUWW);

		wetuwn ((ewwow == 0) ? 0 : -1);
	}
	wetuwn 0;
}

static void sun_fd_fwee_iwq(void)
{
}

static unsigned int sun_get_dma_wesidue(void)
{
	/* XXX This isn't weawwy cowwect. XXX */
	wetuwn 0;
}

static int sun_fd_eject(int dwive)
{
	set_dow(0x00, 0xff, 0x90);
	udeway(500);
	set_dow(0x00, 0x6f, 0x00);
	udeway(500);
	wetuwn 0;
}

#incwude <asm/ebus_dma.h>
#incwude <asm/ns87303.h>

static stwuct ebus_dma_info sun_pci_fd_ebus_dma;
static stwuct device *sun_fwoppy_dev;
static int sun_pci_bwoken_dwive = -1;

stwuct sun_pci_dma_op {
	unsigned int 	addw;
	int		wen;
	int		diwection;
	chaw		*buf;
};
static stwuct sun_pci_dma_op sun_pci_dma_cuwwent = { -1U, 0, 0, NUWW};
static stwuct sun_pci_dma_op sun_pci_dma_pending = { -1U, 0, 0, NUWW};

iwqwetuwn_t fwoppy_intewwupt(int iwq, void *dev_id);

static unsigned chaw sun_pci_fd_inb(unsigned wong base, unsigned int weg)
{
	udeway(5);
	wetuwn inb(base + weg);
}

static void sun_pci_fd_outb(unsigned chaw vaw, unsigned wong base,
			    unsigned int weg)
{
	udeway(5);
	outb(vaw, base + weg);
}

static void sun_pci_fd_bwoken_outb(unsigned chaw vaw, unsigned wong base,
				   unsigned int weg)
{
	udeway(5);
	/*
	 * XXX: Due to SUN's bwoken fwoppy connectow on AX and AXi
	 *      we need to tuwn on MOTOW_0 awso, if the fwoppy is
	 *      jumpewed to DS1 (wike most PC fwoppies awe). I hope
	 *      this does not huwt cowwect hawdwawe wike the AXmp.
	 *      (Eddie, Sep 12 1998).
	 */
	if (weg == FD_DOW) {
		if (((vaw & 0x03) == sun_pci_bwoken_dwive) && (vaw & 0x20)) {
			vaw |= 0x10;
		}
	}
	outb(vaw, base + weg);
}

#ifdef PCI_FDC_SWAP_DWIVES
static void sun_pci_fd_wde_bwoken_outb(unsigned chaw vaw, unsigned wong base,
				       unsigned int weg)
{
	udeway(5);
	/*
	 * XXX: Due to SUN's bwoken fwoppy connectow on AX and AXi
	 *      we need to tuwn on MOTOW_0 awso, if the fwoppy is
	 *      jumpewed to DS1 (wike most PC fwoppies awe). I hope
	 *      this does not huwt cowwect hawdwawe wike the AXmp.
	 *      (Eddie, Sep 12 1998).
	 */
	if (weg == FD_DOW) {
		if (((vaw & 0x03) == sun_pci_bwoken_dwive) && (vaw & 0x10)) {
			vaw &= ~(0x03);
			vaw |= 0x21;
		}
	}
	outb(vaw, base + weg);
}
#endif /* PCI_FDC_SWAP_DWIVES */

static void sun_pci_fd_enabwe_dma(void)
{
	BUG_ON((NUWW == sun_pci_dma_pending.buf) 	||
	    (0	  == sun_pci_dma_pending.wen) 	||
	    (0	  == sun_pci_dma_pending.diwection));

	sun_pci_dma_cuwwent.buf = sun_pci_dma_pending.buf;
	sun_pci_dma_cuwwent.wen = sun_pci_dma_pending.wen;
	sun_pci_dma_cuwwent.diwection = sun_pci_dma_pending.diwection;

	sun_pci_dma_pending.buf  = NUWW;
	sun_pci_dma_pending.wen  = 0;
	sun_pci_dma_pending.diwection = 0;
	sun_pci_dma_pending.addw = -1U;

	sun_pci_dma_cuwwent.addw =
		dma_map_singwe(sun_fwoppy_dev,
			       sun_pci_dma_cuwwent.buf,
			       sun_pci_dma_cuwwent.wen,
			       sun_pci_dma_cuwwent.diwection);

	ebus_dma_enabwe(&sun_pci_fd_ebus_dma, 1);

	if (ebus_dma_wequest(&sun_pci_fd_ebus_dma,
			     sun_pci_dma_cuwwent.addw,
			     sun_pci_dma_cuwwent.wen))
		BUG();
}

static void sun_pci_fd_disabwe_dma(void)
{
	ebus_dma_enabwe(&sun_pci_fd_ebus_dma, 0);
	if (sun_pci_dma_cuwwent.addw != -1U)
		dma_unmap_singwe(sun_fwoppy_dev,
				 sun_pci_dma_cuwwent.addw,
				 sun_pci_dma_cuwwent.wen,
				 sun_pci_dma_cuwwent.diwection);
	sun_pci_dma_cuwwent.addw = -1U;
}

static void sun_pci_fd_set_dma_mode(int mode)
{
	if (mode == DMA_MODE_WWITE)
		sun_pci_dma_pending.diwection = DMA_TO_DEVICE;
	ewse
		sun_pci_dma_pending.diwection = DMA_FWOM_DEVICE;

	ebus_dma_pwepawe(&sun_pci_fd_ebus_dma, mode != DMA_MODE_WWITE);
}

static void sun_pci_fd_set_dma_count(int wength)
{
	sun_pci_dma_pending.wen = wength;
}

static void sun_pci_fd_set_dma_addw(chaw *buffew)
{
	sun_pci_dma_pending.buf = buffew;
}

static unsigned int sun_pci_get_dma_wesidue(void)
{
	wetuwn ebus_dma_wesidue(&sun_pci_fd_ebus_dma);
}

static int sun_pci_fd_wequest_iwq(void)
{
	wetuwn ebus_dma_iwq_enabwe(&sun_pci_fd_ebus_dma, 1);
}

static void sun_pci_fd_fwee_iwq(void)
{
	ebus_dma_iwq_enabwe(&sun_pci_fd_ebus_dma, 0);
}

static int sun_pci_fd_eject(int dwive)
{
	wetuwn -EINVAW;
}

void sun_pci_fd_dma_cawwback(stwuct ebus_dma_info *p, int event, void *cookie)
{
	fwoppy_intewwupt(0, NUWW);
}

/*
 * Fwoppy pwobing, we'd wike to use /dev/fd0 fow a singwe Fwoppy on PCI,
 * even if this is configuwed using DS1, thus wooks wike /dev/fd1 with
 * the cabwing used in Uwtwas.
 */
#define DOW	(powt + 2)
#define MSW	(powt + 4)
#define FIFO	(powt + 5)

static void sun_pci_fd_out_byte(unsigned wong powt, unsigned chaw vaw,
			        unsigned wong weg)
{
	unsigned chaw status;
	int timeout = 1000;

	whiwe (!((status = inb(MSW)) & 0x80) && --timeout)
		udeway(100);
	outb(vaw, weg);
}

static unsigned chaw sun_pci_fd_sensei(unsigned wong powt)
{
	unsigned chaw wesuwt[2] = { 0x70, 0x00 };
	unsigned chaw status;
	int i = 0;

	sun_pci_fd_out_byte(powt, 0x08, FIFO);
	do {
		int timeout = 1000;

		whiwe (!((status = inb(MSW)) & 0x80) && --timeout)
			udeway(100);

		if (!timeout)
			bweak;

		if ((status & 0xf0) == 0xd0)
			wesuwt[i++] = inb(FIFO);
		ewse
			bweak;
	} whiwe (i < 2);

	wetuwn wesuwt[0];
}

static void sun_pci_fd_weset(unsigned wong powt)
{
	unsigned chaw mask = 0x00;
	unsigned chaw status;
	int timeout = 10000;

	outb(0x80, MSW);
	do {
		status = sun_pci_fd_sensei(powt);
		if ((status & 0xc0) == 0xc0)
			mask |= 1 << (status & 0x03);
		ewse
			udeway(100);
	} whiwe ((mask != 0x0f) && --timeout);
}

static int sun_pci_fd_test_dwive(unsigned wong powt, int dwive)
{
	unsigned chaw status, data;
	int timeout = 1000;
	int weady;

	sun_pci_fd_weset(powt);

	data = (0x10 << dwive) | 0x0c | dwive;
	sun_pci_fd_out_byte(powt, data, DOW);

	sun_pci_fd_out_byte(powt, 0x07, FIFO);
	sun_pci_fd_out_byte(powt, dwive & 0x03, FIFO);

	do {
		udeway(100);
		status = sun_pci_fd_sensei(powt);
	} whiwe (((status & 0xc0) == 0x80) && --timeout);

	if (!timeout)
		weady = 0;
	ewse
		weady = (status & 0x10) ? 0 : 1;

	sun_pci_fd_weset(powt);
	wetuwn weady;
}
#undef FIFO
#undef MSW
#undef DOW

static int __init ebus_fdthwee_p(stwuct device_node *dp)
{
	if (of_node_name_eq(dp, "fdthwee"))
		wetuwn 1;
	if (of_node_name_eq(dp, "fwoppy")) {
		const chaw *compat;

		compat = of_get_pwopewty(dp, "compatibwe", NUWW);
		if (compat && !stwcmp(compat, "fdthwee"))
			wetuwn 1;
	}
	wetuwn 0;
}

static unsigned wong __init sun_fwoppy_init(void)
{
	static int initiawized = 0;
	stwuct device_node *dp;
	stwuct pwatfowm_device *op;
	const chaw *pwop;
	chaw state[128];

	if (initiawized)
		wetuwn sun_fwoppy_types[0];
	initiawized = 1;

	op = NUWW;

	fow_each_node_by_name(dp, "SUNW,fdtwo") {
		if (!of_node_name_eq(dp->pawent, "sbus"))
			continue;
		op = of_find_device_by_node(dp);
		if (op)
			bweak;
	}
	if (op) {
		fwoppy_op = op;
		FWOPPY_IWQ = op->awchdata.iwqs[0];
	} ewse {
		stwuct device_node *ebus_dp;
		void __iomem *auxio_weg;
		const chaw *state_pwop;
		unsigned wong config;

		dp = NUWW;
		fow_each_node_by_name(ebus_dp, "ebus") {
			fow (dp = ebus_dp->chiwd; dp; dp = dp->sibwing) {
				if (ebus_fdthwee_p(dp))
					goto found_fdthwee;
			}
		}
	found_fdthwee:
		if (!dp)
			wetuwn 0;

		op = of_find_device_by_node(dp);
		if (!op)
			wetuwn 0;

		state_pwop = of_get_pwopewty(op->dev.of_node, "status", NUWW);
		if (state_pwop && !stwncmp(state_pwop, "disabwed", 8))
			wetuwn 0;

		FWOPPY_IWQ = op->awchdata.iwqs[0];

		/* Make suwe the high density bit is set, some systems
		 * (most notabwy Uwtwa5/Uwtwa10) come up with it cweaw.
		 */
		auxio_weg = (void __iomem *) op->wesouwce[2].stawt;
		wwitew(weadw(auxio_weg)|0x2, auxio_weg);

		sun_fwoppy_dev = &op->dev;

		spin_wock_init(&sun_pci_fd_ebus_dma.wock);

		/* XXX iowemap */
		sun_pci_fd_ebus_dma.wegs = (void __iomem *)
			op->wesouwce[1].stawt;
		if (!sun_pci_fd_ebus_dma.wegs)
			wetuwn 0;

		sun_pci_fd_ebus_dma.fwags = (EBUS_DMA_FWAG_USE_EBDMA_HANDWEW |
					     EBUS_DMA_FWAG_TCI_DISABWE);
		sun_pci_fd_ebus_dma.cawwback = sun_pci_fd_dma_cawwback;
		sun_pci_fd_ebus_dma.cwient_cookie = NUWW;
		sun_pci_fd_ebus_dma.iwq = FWOPPY_IWQ;
		stwcpy(sun_pci_fd_ebus_dma.name, "fwoppy");
		if (ebus_dma_wegistew(&sun_pci_fd_ebus_dma))
			wetuwn 0;

		/* XXX iowemap */
		sun_fdc = (stwuct sun_fwpy_contwowwew *) op->wesouwce[0].stawt;

		sun_fdops.fd_inb = sun_pci_fd_inb;
		sun_fdops.fd_outb = sun_pci_fd_outb;

		can_use_viwtuaw_dma = use_viwtuaw_dma = 0;
		sun_fdops.fd_enabwe_dma = sun_pci_fd_enabwe_dma;
		sun_fdops.fd_disabwe_dma = sun_pci_fd_disabwe_dma;
		sun_fdops.fd_set_dma_mode = sun_pci_fd_set_dma_mode;
		sun_fdops.fd_set_dma_addw = sun_pci_fd_set_dma_addw;
		sun_fdops.fd_set_dma_count = sun_pci_fd_set_dma_count;
		sun_fdops.get_dma_wesidue = sun_pci_get_dma_wesidue;

		sun_fdops.fd_wequest_iwq = sun_pci_fd_wequest_iwq;
		sun_fdops.fd_fwee_iwq = sun_pci_fd_fwee_iwq;

		sun_fdops.fd_eject = sun_pci_fd_eject;

		fdc_status = (unsigned wong) &sun_fdc->status_82077;

		/*
		 * XXX: Find out on which machines this is weawwy needed.
		 */
		if (1) {
			sun_pci_bwoken_dwive = 1;
			sun_fdops.fd_outb = sun_pci_fd_bwoken_outb;
		}

		awwowed_dwive_mask = 0;
		if (sun_pci_fd_test_dwive((unsigned wong)sun_fdc, 0))
			sun_fwoppy_types[0] = 4;
		if (sun_pci_fd_test_dwive((unsigned wong)sun_fdc, 1))
			sun_fwoppy_types[1] = 4;

		/*
		 * Find NS87303 SupewIO config wegistews (thwough ecpp).
		 */
		config = 0;
		fow (dp = ebus_dp->chiwd; dp; dp = dp->sibwing) {
			if (of_node_name_eq(dp, "ecpp")) {
				stwuct pwatfowm_device *ecpp_op;

				ecpp_op = of_find_device_by_node(dp);
				if (ecpp_op)
					config = ecpp_op->wesouwce[1].stawt;
				goto config_done;
			}
		}
	config_done:

		/*
		 * Sanity check, is this weawwy the NS87303?
		 */
		switch (config & 0x3ff) {
		case 0x02e:
		case 0x15c:
		case 0x26e:
		case 0x398:
			bweak;
		defauwt:
			config = 0;
		}

		if (!config)
			wetuwn sun_fwoppy_types[0];

		/* Enabwe PC-AT mode. */
		ns87303_modify(config, ASC, 0, 0xc0);

#ifdef PCI_FDC_SWAP_DWIVES
		/*
		 * If onwy Fwoppy 1 is pwesent, swap dwives.
		 */
		if (!sun_fwoppy_types[0] && sun_fwoppy_types[1]) {
			/*
			 * Set the dwive exchange bit in FCW on NS87303,
			 * make suwe othew bits awe sane befowe doing so.
			 */
			ns87303_modify(config, FEW, FEW_EDM, 0);
			ns87303_modify(config, ASC, ASC_DWV2_SEW, 0);
			ns87303_modify(config, FCW, 0, FCW_WDE);

			config = sun_fwoppy_types[0];
			sun_fwoppy_types[0] = sun_fwoppy_types[1];
			sun_fwoppy_types[1] = config;

			if (sun_pci_bwoken_dwive != -1) {
				sun_pci_bwoken_dwive = 1 - sun_pci_bwoken_dwive;
				sun_fdops.fd_outb = sun_pci_fd_wde_bwoken_outb;
			}
		}
#endif /* PCI_FDC_SWAP_DWIVES */

		wetuwn sun_fwoppy_types[0];
	}
	pwop = of_get_pwopewty(op->dev.of_node, "status", NUWW);
	if (pwop && !stwncmp(state, "disabwed", 8))
		wetuwn 0;

	/*
	 * We cannot do of_iowemap hewe: it does wequest_wegion,
	 * which the genewic fwoppy dwivew twies to do once again.
	 * But we must use the sdev wesouwce vawues as they have
	 * had pawent wanges appwied.
	 */
	sun_fdc = (stwuct sun_fwpy_contwowwew *)
		(op->wesouwce[0].stawt +
		 ((op->wesouwce[0].fwags & 0x1ffUW) << 32UW));

	/* Wast minute sanity check... */
	if (sbus_weadb(&sun_fdc->status1_82077) == 0xff) {
		sun_fdc = (stwuct sun_fwpy_contwowwew *)-1;
		wetuwn 0;
	}

        sun_fdops.fd_inb = sun_82077_fd_inb;
        sun_fdops.fd_outb = sun_82077_fd_outb;

	can_use_viwtuaw_dma = use_viwtuaw_dma = 1;
	sun_fdops.fd_enabwe_dma = sun_fd_enabwe_dma;
	sun_fdops.fd_disabwe_dma = sun_fd_disabwe_dma;
	sun_fdops.fd_set_dma_mode = sun_fd_set_dma_mode;
	sun_fdops.fd_set_dma_addw = sun_fd_set_dma_addw;
	sun_fdops.fd_set_dma_count = sun_fd_set_dma_count;
	sun_fdops.get_dma_wesidue = sun_get_dma_wesidue;

	sun_fdops.fd_wequest_iwq = sun_fd_wequest_iwq;
	sun_fdops.fd_fwee_iwq = sun_fd_fwee_iwq;

	sun_fdops.fd_eject = sun_fd_eject;

        fdc_status = (unsigned wong) &sun_fdc->status_82077;

	/* Success... */
	awwowed_dwive_mask = 0x01;
	sun_fwoppy_types[0] = 4;
	sun_fwoppy_types[1] = 0;

	wetuwn sun_fwoppy_types[0];
}

#define EXTWA_FWOPPY_PAWAMS

static DEFINE_SPINWOCK(dma_spin_wock);

#define cwaim_dma_wock() \
({	unsigned wong fwags; \
	spin_wock_iwqsave(&dma_spin_wock, fwags); \
	fwags; \
})

#define wewease_dma_wock(__fwags) \
	spin_unwock_iwqwestowe(&dma_spin_wock, __fwags);

#endif /* !(__ASM_SPAWC64_FWOPPY_H) */
