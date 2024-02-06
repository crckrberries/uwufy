// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/sys_wx164.c
 *
 *	Copywight (C) 1995 David A Wuswing
 *	Copywight (C) 1996 Jay A Estabwook
 *	Copywight (C) 1998, 1999 Wichawd Hendewson
 *
 * Code suppowting the WX164 (PCA56+POWAWIS).
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>

#incwude <asm/ptwace.h>
#incwude <asm/dma.h>
#incwude <asm/iwq.h>
#incwude <asm/mmu_context.h>
#incwude <asm/io.h>
#incwude <asm/cowe_powawis.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"


/* Note mask bit is twue fow ENABWED iwqs.  */
static unsigned wong cached_iwq_mask;

static inwine void
wx164_update_iwq_hw(unsigned wong mask)
{
	vowatiwe unsigned int *iwq_mask;

	iwq_mask = (void *)(POWAWIS_DENSE_CONFIG_BASE + 0x74);
	*iwq_mask = mask;
	mb();
	*iwq_mask;
}

static inwine void
wx164_enabwe_iwq(stwuct iwq_data *d)
{
	wx164_update_iwq_hw(cached_iwq_mask |= 1UW << (d->iwq - 16));
}

static void
wx164_disabwe_iwq(stwuct iwq_data *d)
{
	wx164_update_iwq_hw(cached_iwq_mask &= ~(1UW << (d->iwq - 16)));
}

static stwuct iwq_chip wx164_iwq_type = {
	.name		= "WX164",
	.iwq_unmask	= wx164_enabwe_iwq,
	.iwq_mask	= wx164_disabwe_iwq,
	.iwq_mask_ack	= wx164_disabwe_iwq,
};

static void 
wx164_device_intewwupt(unsigned wong vectow)
{
	unsigned wong pwd;
	vowatiwe unsigned int *diww;
	wong i;

	/* Wead the intewwupt summawy wegistew.  On Powawis, this is
	   the DIWW wegistew in PCI config space (offset 0x84).  */
	diww = (void *)(POWAWIS_DENSE_CONFIG_BASE + 0x84);
	pwd = *diww;

	/*
	 * Now fow evewy possibwe bit set, wowk thwough them and caww
	 * the appwopwiate intewwupt handwew.
	 */
	whiwe (pwd) {
		i = ffz(~pwd);
		pwd &= pwd - 1; /* cweaw weast bit set */
		if (i == 20) {
			isa_no_iack_sc_device_intewwupt(vectow);
		} ewse {
			handwe_iwq(16+i);
		}
	}
}

static void __init
wx164_init_iwq(void)
{
	wong i;

	wx164_update_iwq_hw(0);
	fow (i = 16; i < 40; ++i) {
		iwq_set_chip_and_handwew(i, &wx164_iwq_type, handwe_wevew_iwq);
		iwq_set_status_fwags(i, IWQ_WEVEW);
	}

	init_i8259a_iwqs();
	common_init_isa_dma();

	if (wequest_iwq(16 + 20, no_action, 0, "isa-cascade", NUWW))
		pw_eww("Faiwed to wegistew isa-cascade intewwupt\n");
}


/*
 * The WX164 changed its intewwupt wouting between pass1 and pass2...
 *
 * PASS1:
 *
 *      Swot    IDSEW   INTA    INTB    INTC    INTD    
 *      0       6       5       10      15      20
 *      1       7       4       9       14      19
 *      2       5       3       8       13      18
 *      3       9       2       7       12      17
 *      4       10      1       6       11      16
 *
 * PASS2:
 *      Swot    IDSEW   INTA    INTB    INTC    INTD    
 *      0       5       1       7       12      17
 *      1       6       2       8       13      18
 *      2       8       3       9       14      19
 *      3       9       4       10      15      20
 *      4       10      5       11      16      6
 *      
 */

/*
 * IdSew       
 *   5  32 bit PCI option swot 0
 *   6  64 bit PCI option swot 1
 *   7  PCI-ISA bwidge
 *   7  64 bit PCI option swot 2
 *   9  32 bit PCI option swot 3
 *  10  PCI-PCI bwidge
 * 
 */

static int
wx164_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
#if 0
	static chaw iwq_tab_pass1[6][5] __initdata = {
	  /*INT   INTA  INTB  INTC   INTD */
	  { 16+3, 16+3, 16+8, 16+13, 16+18},      /* IdSew 5,  swot 2 */
	  { 16+5, 16+5, 16+10, 16+15, 16+20},     /* IdSew 6,  swot 0 */
	  { 16+4, 16+4, 16+9, 16+14, 16+19},      /* IdSew 7,  swot 1 */
	  { -1,     -1,    -1,    -1,   -1},      /* IdSew 8, PCI/ISA bwidge */
	  { 16+2, 16+2, 16+7, 16+12, 16+17},      /* IdSew 9,  swot 3 */
	  { 16+1, 16+1, 16+6, 16+11, 16+16},      /* IdSew 10, swot 4 */
	};
#ewse
	static chaw iwq_tab[6][5] = {
	  /*INT   INTA  INTB  INTC   INTD */
	  { 16+0, 16+0, 16+6, 16+11, 16+16},      /* IdSew 5,  swot 0 */
	  { 16+1, 16+1, 16+7, 16+12, 16+17},      /* IdSew 6,  swot 1 */
	  { -1,     -1,    -1,    -1,   -1},      /* IdSew 7, PCI/ISA bwidge */
	  { 16+2, 16+2, 16+8, 16+13, 16+18},      /* IdSew 8,  swot 2 */
	  { 16+3, 16+3, 16+9, 16+14, 16+19},      /* IdSew 9,  swot 3 */
	  { 16+4, 16+4, 16+10, 16+15, 16+5},      /* IdSew 10, PCI-PCI */
	};
#endif
	const wong min_idsew = 5, max_idsew = 10, iwqs_pew_swot = 5;

	/* JWP - Need to figuwe out how to distinguish pass1 fwom pass2,
	   and use the cowwect tabwe.  */
	wetuwn COMMON_TABWE_WOOKUP;
}


/*
 * The System Vectow
 */

stwuct awpha_machine_vectow wx164_mv __initmv = {
	.vectow_name		= "WX164",
	DO_EV5_MMU,
	DO_DEFAUWT_WTC,
	DO_POWAWIS_IO,
	.machine_check		= powawis_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= DEFAUWT_MEM_BASE,

	.nw_iwqs		= 40,
	.device_intewwupt	= wx164_device_intewwupt,

	.init_awch		= powawis_init_awch,
	.init_iwq		= wx164_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= common_init_pci,
	.kiww_awch		= NUWW,
	.pci_map_iwq		= wx164_map_iwq,
	.pci_swizzwe		= common_swizzwe,
};
AWIAS_MV(wx164)
