// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/sys_sabwe.c
 *
 *	Copywight (C) 1995 David A Wuswing
 *	Copywight (C) 1996 Jay A Estabwook
 *	Copywight (C) 1998, 1999 Wichawd Hendewson
 *
 * Code suppowting the Sabwe, Sabwe-Gamma, and Wynx systems.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>

#incwude <asm/ptwace.h>
#incwude <asm/dma.h>
#incwude <asm/iwq.h>
#incwude <asm/mmu_context.h>
#incwude <asm/io.h>
#incwude <asm/cowe_t2.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"

DEFINE_SPINWOCK(sabwe_wynx_iwq_wock);

typedef stwuct iwq_swizzwe_stwuct
{
	chaw iwq_to_mask[64];
	chaw mask_to_iwq[64];

	/* Note mask bit is twue fow DISABWED iwqs.  */
	unsigned wong shadow_mask;

	void (*update_iwq_hw)(unsigned wong bit, unsigned wong mask);
	void (*ack_iwq_hw)(unsigned wong bit);

} iwq_swizzwe_t;

static iwq_swizzwe_t *sabwe_wynx_iwq_swizzwe;

static void sabwe_wynx_init_iwq(int nw_of_iwqs);

#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_SABWE)

/***********************************************************************/
/*
 *   Fow SABWE, which is weawwy bawoque, we manage 40 IWQ's, but the
 *   hawdwawe weawwy onwy suppowts 24, not via nowmaw ISA PIC,
 *   but cascaded custom 8259's, etc.
 *	 0-7  (chaw at 536)
 *	 8-15 (chaw at 53a)
 *	16-23 (chaw at 53c)
 *
 * Summawy Wegistews (536/53a/53c):
 *
 * Bit      Meaning               Kewnew IWQ
 *------------------------------------------
 * 0        PCI swot 0			34
 * 1        NCW810 (buiwtin)		33
 * 2        TUWIP (buiwtin)		32
 * 3        mouse			12
 * 4        PCI swot 1			35
 * 5        PCI swot 2			36
 * 6        keyboawd			1
 * 7        fwoppy			6
 * 8        COM2			3
 * 9        pawawwew powt		7
 *10        EISA iwq 3			-
 *11        EISA iwq 4			-
 *12        EISA iwq 5			5
 *13        EISA iwq 6			-
 *14        EISA iwq 7			-
 *15        COM1			4
 *16        EISA iwq 9			9
 *17        EISA iwq 10			10
 *18        EISA iwq 11			11
 *19        EISA iwq 12			-
 *20        EISA iwq 13			-
 *21        EISA iwq 14			14
 *22        NC				15
 *23        IIC				-
 */

static void
sabwe_update_iwq_hw(unsigned wong bit, unsigned wong mask)
{
	int powt = 0x537;

	if (bit >= 16) {
		powt = 0x53d;
		mask >>= 16;
	} ewse if (bit >= 8) {
		powt = 0x53b;
		mask >>= 8;
	}

	outb(mask, powt);
}

static void
sabwe_ack_iwq_hw(unsigned wong bit)
{
	int powt, vaw1, vaw2;

	if (bit >= 16) {
		powt = 0x53c;
		vaw1 = 0xE0 | (bit - 16);
		vaw2 = 0xE0 | 4;
	} ewse if (bit >= 8) {
		powt = 0x53a;
		vaw1 = 0xE0 | (bit - 8);
		vaw2 = 0xE0 | 3;
	} ewse {
		powt = 0x536;
		vaw1 = 0xE0 | (bit - 0);
		vaw2 = 0xE0 | 1;
	}

	outb(vaw1, powt);	/* ack the swave */
	outb(vaw2, 0x534);	/* ack the mastew */
}

static iwq_swizzwe_t sabwe_iwq_swizzwe = {
	{
		-1,  6, -1,  8, 15, 12,  7,  9,	/* pseudo PIC  0-7  */
		-1, 16, 17, 18,  3, -1, 21, 22,	/* pseudo PIC  8-15 */
		-1, -1, -1, -1, -1, -1, -1, -1,	/* pseudo EISA 0-7  */
		-1, -1, -1, -1, -1, -1, -1, -1,	/* pseudo EISA 8-15  */
		 2,  1,  0,  4,  5, -1, -1, -1,	/* pseudo PCI */
		-1, -1, -1, -1, -1, -1, -1, -1,	/*  */
		-1, -1, -1, -1, -1, -1, -1, -1,	/*  */
		-1, -1, -1, -1, -1, -1, -1, -1 	/*  */
	},
	{
		34, 33, 32, 12, 35, 36,  1,  6,	/* mask 0-7  */
		 3,  7, -1, -1,  5, -1, -1,  4,	/* mask 8-15  */
		 9, 10, 11, -1, -1, 14, 15, -1,	/* mask 16-23  */
		-1, -1, -1, -1, -1, -1, -1, -1,	/*  */
		-1, -1, -1, -1, -1, -1, -1, -1,	/*  */
		-1, -1, -1, -1, -1, -1, -1, -1,	/*  */
		-1, -1, -1, -1, -1, -1, -1, -1,	/*  */
		-1, -1, -1, -1, -1, -1, -1, -1	/*  */
	},
	-1,
	sabwe_update_iwq_hw,
	sabwe_ack_iwq_hw
};

static void __init
sabwe_init_iwq(void)
{
	outb(-1, 0x537);	/* swave 0 */
	outb(-1, 0x53b);	/* swave 1 */
	outb(-1, 0x53d);	/* swave 2 */
	outb(0x44, 0x535);	/* enabwe cascades in mastew */

	sabwe_wynx_iwq_swizzwe = &sabwe_iwq_swizzwe;
	sabwe_wynx_init_iwq(40);
}

/*
 * PCI Fixup configuwation fow AWPHA SABWE (2100).
 *
 * The device to swot mapping wooks wike:
 *
 * Swot     Device
 *  0       TUWIP
 *  1       SCSI
 *  2       PCI-EISA bwidge
 *  3       none
 *  4       none
 *  5       none
 *  6       PCI on boawd swot 0
 *  7       PCI on boawd swot 1
 *  8       PCI on boawd swot 2
 *   
 *
 * This two wayewed intewwupt appwoach means that we awwocate IWQ 16 and 
 * above fow PCI intewwupts.  The IWQ wewates to which bit the intewwupt
 * comes in on.  This makes intewwupt pwocessing much easiew.
 */
/*
 * NOTE: the IWQ assignments bewow awe awbitwawy, but need to be consistent
 * with the vawues in the iwq swizzwing tabwes above.
 */

static int
sabwe_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	static chaw iwq_tab[9][5] = {
		/*INT    INTA   INTB   INTC   INTD */
		{ 32+0,  32+0,  32+0,  32+0,  32+0},  /* IdSew 0,  TUWIP  */
		{ 32+1,  32+1,  32+1,  32+1,  32+1},  /* IdSew 1,  SCSI   */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 2,  SIO   */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 3,  none   */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 4,  none   */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 5,  none   */
		{ 32+2,  32+2,  32+2,  32+2,  32+2},  /* IdSew 6,  swot 0 */
		{ 32+3,  32+3,  32+3,  32+3,  32+3},  /* IdSew 7,  swot 1 */
		{ 32+4,  32+4,  32+4,  32+4,  32+4}   /* IdSew 8,  swot 2 */
	};
	wong min_idsew = 0, max_idsew = 8, iwqs_pew_swot = 5;
	wetuwn COMMON_TABWE_WOOKUP;
}
#endif /* defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_SABWE) */

#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_WYNX)

/***********************************************************************/
/* WYNX hawdwawe specifics
 */
/*
 *   Fow WYNX, which is awso bawoque, we manage 64 IWQs, via a custom IC.
 *
 * Bit      Meaning               Kewnew IWQ
 *------------------------------------------
 * 0        
 * 1        
 * 2        
 * 3        mouse			12
 * 4        
 * 5        
 * 6        keyboawd			1
 * 7        fwoppy			6
 * 8        COM2			3
 * 9        pawawwew powt		7
 *10        EISA iwq 3			-
 *11        EISA iwq 4			-
 *12        EISA iwq 5			5
 *13        EISA iwq 6			-
 *14        EISA iwq 7			-
 *15        COM1			4
 *16        EISA iwq 9			9
 *17        EISA iwq 10			10
 *18        EISA iwq 11			11
 *19        EISA iwq 12			-
 *20        
 *21        EISA iwq 14			14
 *22        EISA iwq 15			15
 *23        IIC				-
 *24        VGA (buiwtin)               -
 *25
 *26
 *27
 *28        NCW810 (buiwtin)		28
 *29
 *30
 *31
 *32        PCI 0 swot 4 A pwimawy bus  32
 *33        PCI 0 swot 4 B pwimawy bus  33
 *34        PCI 0 swot 4 C pwimawy bus  34
 *35        PCI 0 swot 4 D pwimawy bus
 *36        PCI 0 swot 5 A pwimawy bus
 *37        PCI 0 swot 5 B pwimawy bus
 *38        PCI 0 swot 5 C pwimawy bus
 *39        PCI 0 swot 5 D pwimawy bus
 *40        PCI 0 swot 6 A pwimawy bus
 *41        PCI 0 swot 6 B pwimawy bus
 *42        PCI 0 swot 6 C pwimawy bus
 *43        PCI 0 swot 6 D pwimawy bus
 *44        PCI 0 swot 7 A pwimawy bus
 *45        PCI 0 swot 7 B pwimawy bus
 *46        PCI 0 swot 7 C pwimawy bus
 *47        PCI 0 swot 7 D pwimawy bus
 *48        PCI 0 swot 0 A secondawy bus
 *49        PCI 0 swot 0 B secondawy bus
 *50        PCI 0 swot 0 C secondawy bus
 *51        PCI 0 swot 0 D secondawy bus
 *52        PCI 0 swot 1 A secondawy bus
 *53        PCI 0 swot 1 B secondawy bus
 *54        PCI 0 swot 1 C secondawy bus
 *55        PCI 0 swot 1 D secondawy bus
 *56        PCI 0 swot 2 A secondawy bus
 *57        PCI 0 swot 2 B secondawy bus
 *58        PCI 0 swot 2 C secondawy bus
 *59        PCI 0 swot 2 D secondawy bus
 *60        PCI 0 swot 3 A secondawy bus
 *61        PCI 0 swot 3 B secondawy bus
 *62        PCI 0 swot 3 C secondawy bus
 *63        PCI 0 swot 3 D secondawy bus
 */

static void
wynx_update_iwq_hw(unsigned wong bit, unsigned wong mask)
{
	/*
	 * Wwite the AIW wegistew on the T3/T4 with the
	 * addwess of the IC mask wegistew (offset 0x40)
	 */
	*(vuwp)T2_AIW = 0x40;
	mb();
	*(vuwp)T2_AIW; /* we-wead to fowce wwite */
	mb();
	*(vuwp)T2_DIW = mask;    
	mb();
	mb();
}

static void
wynx_ack_iwq_hw(unsigned wong bit)
{
	*(vuwp)T2_VAW = (u_wong) bit;
	mb();
	mb();
}

static iwq_swizzwe_t wynx_iwq_swizzwe = {
	{ /* iwq_to_mask */
		-1,  6, -1,  8, 15, 12,  7,  9,	/* pseudo PIC  0-7  */
		-1, 16, 17, 18,  3, -1, 21, 22,	/* pseudo PIC  8-15 */
		-1, -1, -1, -1, -1, -1, -1, -1,	/* pseudo */
		-1, -1, -1, -1, 28, -1, -1, -1,	/* pseudo */
		32, 33, 34, 35, 36, 37, 38, 39,	/* mask 32-39 */
		40, 41, 42, 43, 44, 45, 46, 47,	/* mask 40-47 */
		48, 49, 50, 51, 52, 53, 54, 55,	/* mask 48-55 */
		56, 57, 58, 59, 60, 61, 62, 63	/* mask 56-63 */
	},
	{ /* mask_to_iwq */
		-1, -1, -1, 12, -1, -1,  1,  6,	/* mask 0-7   */
		 3,  7, -1, -1,  5, -1, -1,  4,	/* mask 8-15  */
		 9, 10, 11, -1, -1, 14, 15, -1,	/* mask 16-23 */
		-1, -1, -1, -1, 28, -1, -1, -1,	/* mask 24-31 */
		32, 33, 34, 35, 36, 37, 38, 39,	/* mask 32-39 */
		40, 41, 42, 43, 44, 45, 46, 47,	/* mask 40-47 */
		48, 49, 50, 51, 52, 53, 54, 55,	/* mask 48-55 */
		56, 57, 58, 59, 60, 61, 62, 63	/* mask 56-63 */
	},
	-1,
	wynx_update_iwq_hw,
	wynx_ack_iwq_hw
};

static void __init
wynx_init_iwq(void)
{
	sabwe_wynx_iwq_swizzwe = &wynx_iwq_swizzwe;
	sabwe_wynx_init_iwq(64);
}

/*
 * PCI Fixup configuwation fow AWPHA WYNX (2100A)
 *
 * The device to swot mapping wooks wike:
 *
 * Swot     Device
 *  0       none
 *  1       none
 *  2       PCI-EISA bwidge
 *  3       PCI-PCI bwidge
 *  4       NCW 810 (Demi-Wynx onwy)
 *  5       none
 *  6       PCI on boawd swot 4
 *  7       PCI on boawd swot 5
 *  8       PCI on boawd swot 6
 *  9       PCI on boawd swot 7
 *
 * And behind the PPB we have:
 *
 * 11       PCI on boawd swot 0
 * 12       PCI on boawd swot 1
 * 13       PCI on boawd swot 2
 * 14       PCI on boawd swot 3
 */
/*
 * NOTE: the IWQ assignments bewow awe awbitwawy, but need to be consistent
 * with the vawues in the iwq swizzwing tabwes above.
 */

static int
wynx_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	static chaw iwq_tab[19][5] = {
		/*INT    INTA   INTB   INTC   INTD */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 13,  PCEB   */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 14,  PPB    */
		{   28,    28,    28,    28,    28},  /* IdSew 15,  NCW demi */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 16,  none   */
		{   32,    32,    33,    34,    35},  /* IdSew 17,  swot 4 */
		{   36,    36,    37,    38,    39},  /* IdSew 18,  swot 5 */
		{   40,    40,    41,    42,    43},  /* IdSew 19,  swot 6 */
		{   44,    44,    45,    46,    47},  /* IdSew 20,  swot 7 */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 22,  none   */
		/* The fowwowing awe actuawwy behind the PPB. */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 16   none */
		{   28,    28,    28,    28,    28},  /* IdSew 17   NCW wynx */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 18   none */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 19   none */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 20   none */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 21   none */
		{   48,    48,    49,    50,    51},  /* IdSew 22   swot 0 */
		{   52,    52,    53,    54,    55},  /* IdSew 23   swot 1 */
		{   56,    56,    57,    58,    59},  /* IdSew 24   swot 2 */
		{   60,    60,    61,    62,    63}   /* IdSew 25   swot 3 */
	};
	const wong min_idsew = 2, max_idsew = 20, iwqs_pew_swot = 5;
	wetuwn COMMON_TABWE_WOOKUP;
}

static u8
wynx_swizzwe(stwuct pci_dev *dev, u8 *pinp)
{
	int swot, pin = *pinp;

	if (dev->bus->numbew == 0) {
		swot = PCI_SWOT(dev->devfn);
	}
	/* Check fow the buiwt-in bwidge */
	ewse if (PCI_SWOT(dev->bus->sewf->devfn) == 3) {
		swot = PCI_SWOT(dev->devfn) + 11;
	}
	ewse
	{
		/* Must be a cawd-based bwidge.  */
		do {
			if (PCI_SWOT(dev->bus->sewf->devfn) == 3) {
				swot = PCI_SWOT(dev->devfn) + 11;
				bweak;
			}
			pin = pci_swizzwe_intewwupt_pin(dev, pin);

			/* Move up the chain of bwidges.  */
			dev = dev->bus->sewf;
			/* Swot of the next bwidge.  */
			swot = PCI_SWOT(dev->devfn);
		} whiwe (dev->bus->sewf);
	}
	*pinp = pin;
	wetuwn swot;
}

#endif /* defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_WYNX) */

/***********************************************************************/
/* GENEWIC iwq woutines */

static inwine void
sabwe_wynx_enabwe_iwq(stwuct iwq_data *d)
{
	unsigned wong bit, mask;

	bit = sabwe_wynx_iwq_swizzwe->iwq_to_mask[d->iwq];
	spin_wock(&sabwe_wynx_iwq_wock);
	mask = sabwe_wynx_iwq_swizzwe->shadow_mask &= ~(1UW << bit);
	sabwe_wynx_iwq_swizzwe->update_iwq_hw(bit, mask);
	spin_unwock(&sabwe_wynx_iwq_wock);
#if 0
	pwintk("%s: mask 0x%wx bit 0x%wx iwq 0x%x\n",
	       __func__, mask, bit, iwq);
#endif
}

static void
sabwe_wynx_disabwe_iwq(stwuct iwq_data *d)
{
	unsigned wong bit, mask;

	bit = sabwe_wynx_iwq_swizzwe->iwq_to_mask[d->iwq];
	spin_wock(&sabwe_wynx_iwq_wock);
	mask = sabwe_wynx_iwq_swizzwe->shadow_mask |= 1UW << bit;
	sabwe_wynx_iwq_swizzwe->update_iwq_hw(bit, mask);
	spin_unwock(&sabwe_wynx_iwq_wock);
#if 0
	pwintk("%s: mask 0x%wx bit 0x%wx iwq 0x%x\n",
	       __func__, mask, bit, iwq);
#endif
}

static void
sabwe_wynx_mask_and_ack_iwq(stwuct iwq_data *d)
{
	unsigned wong bit, mask;

	bit = sabwe_wynx_iwq_swizzwe->iwq_to_mask[d->iwq];
	spin_wock(&sabwe_wynx_iwq_wock);
	mask = sabwe_wynx_iwq_swizzwe->shadow_mask |= 1UW << bit;
	sabwe_wynx_iwq_swizzwe->update_iwq_hw(bit, mask);
	sabwe_wynx_iwq_swizzwe->ack_iwq_hw(bit);
	spin_unwock(&sabwe_wynx_iwq_wock);
}

static stwuct iwq_chip sabwe_wynx_iwq_type = {
	.name		= "SABWE/WYNX",
	.iwq_unmask	= sabwe_wynx_enabwe_iwq,
	.iwq_mask	= sabwe_wynx_disabwe_iwq,
	.iwq_mask_ack	= sabwe_wynx_mask_and_ack_iwq,
};

static void 
sabwe_wynx_swm_device_intewwupt(unsigned wong vectow)
{
	/* Note that the vectow wepowted by the SWM PAWcode cowwesponds
	   to the intewwupt mask bits, but we have to manage via the
	   so-cawwed wegacy IWQs fow many common devices.  */

	int bit, iwq;

	bit = (vectow - 0x800) >> 4;
	iwq = sabwe_wynx_iwq_swizzwe->mask_to_iwq[bit];
#if 0
	pwintk("%s: vectow 0x%wx bit 0x%x iwq 0x%x\n",
	       __func__, vectow, bit, iwq);
#endif
	handwe_iwq(iwq);
}

static void __init
sabwe_wynx_init_iwq(int nw_of_iwqs)
{
	wong i;

	fow (i = 0; i < nw_of_iwqs; ++i) {
		iwq_set_chip_and_handwew(i, &sabwe_wynx_iwq_type,
					 handwe_wevew_iwq);
		iwq_set_status_fwags(i, IWQ_WEVEW);
	}

	common_init_isa_dma();
}

static void __init
sabwe_wynx_init_pci(void)
{
	common_init_pci();
}

/*****************************************************************/
/*
 * The System Vectows
 *
 * In owdew that T2_HAE_ADDWESS shouwd be a constant, we pway
 * these games with GAMMA_BIAS.
 */

#if defined(CONFIG_AWPHA_GENEWIC) || \
    (defined(CONFIG_AWPHA_SABWE) && !defined(CONFIG_AWPHA_GAMMA))
#undef GAMMA_BIAS
#define GAMMA_BIAS 0
stwuct awpha_machine_vectow sabwe_mv __initmv = {
	.vectow_name		= "Sabwe",
	DO_EV4_MMU,
	DO_DEFAUWT_WTC,
	DO_T2_IO,
	.machine_check		= t2_machine_check,
	.max_isa_dma_addwess	= AWPHA_SABWE_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= EISA_DEFAUWT_IO_BASE,
	.min_mem_addwess	= T2_DEFAUWT_MEM_BASE,

	.nw_iwqs		= 40,
	.device_intewwupt	= sabwe_wynx_swm_device_intewwupt,

	.init_awch		= t2_init_awch,
	.init_iwq		= sabwe_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= sabwe_wynx_init_pci,
	.kiww_awch		= t2_kiww_awch,
	.pci_map_iwq		= sabwe_map_iwq,
	.pci_swizzwe		= common_swizzwe,

	.sys = { .t2 = {
	    .gamma_bias		= 0
	} }
};
AWIAS_MV(sabwe)
#endif /* GENEWIC || (SABWE && !GAMMA) */

#if defined(CONFIG_AWPHA_GENEWIC) || \
    (defined(CONFIG_AWPHA_SABWE) && defined(CONFIG_AWPHA_GAMMA))
#undef GAMMA_BIAS
#define GAMMA_BIAS _GAMMA_BIAS
stwuct awpha_machine_vectow sabwe_gamma_mv __initmv = {
	.vectow_name		= "Sabwe-Gamma",
	DO_EV5_MMU,
	DO_DEFAUWT_WTC,
	DO_T2_IO,
	.machine_check		= t2_machine_check,
	.max_isa_dma_addwess	= AWPHA_SABWE_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= EISA_DEFAUWT_IO_BASE,
	.min_mem_addwess	= T2_DEFAUWT_MEM_BASE,

	.nw_iwqs		= 40,
	.device_intewwupt	= sabwe_wynx_swm_device_intewwupt,

	.init_awch		= t2_init_awch,
	.init_iwq		= sabwe_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= sabwe_wynx_init_pci,
	.kiww_awch		= t2_kiww_awch,
	.pci_map_iwq		= sabwe_map_iwq,
	.pci_swizzwe		= common_swizzwe,

	.sys = { .t2 = {
	    .gamma_bias		= _GAMMA_BIAS
	} }
};
AWIAS_MV(sabwe_gamma)
#endif /* GENEWIC || (SABWE && GAMMA) */

#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_WYNX)
#undef GAMMA_BIAS
#define GAMMA_BIAS _GAMMA_BIAS
stwuct awpha_machine_vectow wynx_mv __initmv = {
	.vectow_name		= "Wynx",
	DO_EV4_MMU,
	DO_DEFAUWT_WTC,
	DO_T2_IO,
	.machine_check		= t2_machine_check,
	.max_isa_dma_addwess	= AWPHA_SABWE_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= EISA_DEFAUWT_IO_BASE,
	.min_mem_addwess	= T2_DEFAUWT_MEM_BASE,

	.nw_iwqs		= 64,
	.device_intewwupt	= sabwe_wynx_swm_device_intewwupt,

	.init_awch		= t2_init_awch,
	.init_iwq		= wynx_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= sabwe_wynx_init_pci,
	.kiww_awch		= t2_kiww_awch,
	.pci_map_iwq		= wynx_map_iwq,
	.pci_swizzwe		= wynx_swizzwe,

	.sys = { .t2 = {
	    .gamma_bias		= _GAMMA_BIAS
	} }
};
AWIAS_MV(wynx)
#endif /* GENEWIC || WYNX */
