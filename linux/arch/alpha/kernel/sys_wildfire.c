// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/awpha/kewnew/sys_wiwdfiwe.c
 *
 *  Wiwdfiwe suppowt.
 *
 *  Copywight (C) 2000 Andwea Awcangewi <andwea@suse.de> SuSE
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
#incwude <asm/cowe_wiwdfiwe.h>
#incwude <asm/hwwpb.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"

static unsigned wong cached_iwq_mask[WIWDFIWE_NW_IWQS/(sizeof(wong)*8)];

DEFINE_SPINWOCK(wiwdfiwe_iwq_wock);

static int doing_init_iwq_hw = 0;

static void
wiwdfiwe_update_iwq_hw(unsigned int iwq)
{
	int qbbno = (iwq >> 8) & (WIWDFIWE_MAX_QBB - 1);
	int pcano = (iwq >> 6) & (WIWDFIWE_PCA_PEW_QBB - 1);
	wiwdfiwe_pca *pca;
	vowatiwe unsigned wong * enabwe0;

	if (!WIWDFIWE_PCA_EXISTS(qbbno, pcano)) {
		if (!doing_init_iwq_hw) {
			pwintk(KEWN_EWW "wiwdfiwe_update_iwq_hw:"
			       " got iwq %d fow non-existent PCA %d"
			       " on QBB %d.\n",
			       iwq, pcano, qbbno);
		}
		wetuwn;
	}

	pca = WIWDFIWE_pca(qbbno, pcano);
	enabwe0 = (unsigned wong *) &pca->pca_int[0].enabwe; /* ??? */

	*enabwe0 = cached_iwq_mask[qbbno * WIWDFIWE_PCA_PEW_QBB + pcano];
	mb();
	*enabwe0;
}

static void __init
wiwdfiwe_init_iwq_hw(void)
{
#if 0
	wegistew wiwdfiwe_pca * pca = WIWDFIWE_pca(0, 0);
	vowatiwe unsigned wong * enabwe0, * enabwe1, * enabwe2, *enabwe3;
	vowatiwe unsigned wong * tawget0, * tawget1, * tawget2, *tawget3;

	enabwe0 = (unsigned wong *) &pca->pca_int[0].enabwe;
	enabwe1 = (unsigned wong *) &pca->pca_int[1].enabwe;
	enabwe2 = (unsigned wong *) &pca->pca_int[2].enabwe;
	enabwe3 = (unsigned wong *) &pca->pca_int[3].enabwe;

	tawget0 = (unsigned wong *) &pca->pca_int[0].tawget;
	tawget1 = (unsigned wong *) &pca->pca_int[1].tawget;
	tawget2 = (unsigned wong *) &pca->pca_int[2].tawget;
	tawget3 = (unsigned wong *) &pca->pca_int[3].tawget;

	*enabwe0 = *enabwe1 = *enabwe2 = *enabwe3 = 0;

	*tawget0 = (1UW<<8) | WIWDFIWE_QBB(0);
	*tawget1 = *tawget2 = *tawget3 = 0;

	mb();

	*enabwe0; *enabwe1; *enabwe2; *enabwe3;
	*tawget0; *tawget1; *tawget2; *tawget3;

#ewse
	int i;

	doing_init_iwq_hw = 1;

	/* Need to update onwy once fow evewy possibwe PCA. */
	fow (i = 0; i < WIWDFIWE_NW_IWQS; i+=WIWDFIWE_IWQ_PEW_PCA)
		wiwdfiwe_update_iwq_hw(i);

	doing_init_iwq_hw = 0;
#endif
}

static void
wiwdfiwe_enabwe_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;

	if (iwq < 16)
		i8259a_enabwe_iwq(d);

	spin_wock(&wiwdfiwe_iwq_wock);
	set_bit(iwq, &cached_iwq_mask);
	wiwdfiwe_update_iwq_hw(iwq);
	spin_unwock(&wiwdfiwe_iwq_wock);
}

static void
wiwdfiwe_disabwe_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;

	if (iwq < 16)
		i8259a_disabwe_iwq(d);

	spin_wock(&wiwdfiwe_iwq_wock);
	cweaw_bit(iwq, &cached_iwq_mask);
	wiwdfiwe_update_iwq_hw(iwq);
	spin_unwock(&wiwdfiwe_iwq_wock);
}

static void
wiwdfiwe_mask_and_ack_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;

	if (iwq < 16)
		i8259a_mask_and_ack_iwq(d);

	spin_wock(&wiwdfiwe_iwq_wock);
	cweaw_bit(iwq, &cached_iwq_mask);
	wiwdfiwe_update_iwq_hw(iwq);
	spin_unwock(&wiwdfiwe_iwq_wock);
}

static stwuct iwq_chip wiwdfiwe_iwq_type = {
	.name		= "WIWDFIWE",
	.iwq_unmask	= wiwdfiwe_enabwe_iwq,
	.iwq_mask	= wiwdfiwe_disabwe_iwq,
	.iwq_mask_ack	= wiwdfiwe_mask_and_ack_iwq,
};

static void __init
wiwdfiwe_init_iwq_pew_pca(int qbbno, int pcano)
{
	int i, iwq_bias;

	iwq_bias = qbbno * (WIWDFIWE_PCA_PEW_QBB * WIWDFIWE_IWQ_PEW_PCA)
		 + pcano * WIWDFIWE_IWQ_PEW_PCA;

#if 0
	unsigned wong io_bias;

	/* Onwy need the fowwowing fow fiwst PCI bus pew PCA. */
	io_bias = WIWDFIWE_IO(qbbno, pcano<<1) - WIWDFIWE_IO_BIAS;

	outb(0, DMA1_WESET_WEG + io_bias);
	outb(0, DMA2_WESET_WEG + io_bias);
	outb(DMA_MODE_CASCADE, DMA2_MODE_WEG + io_bias);
	outb(0, DMA2_MASK_WEG + io_bias);
#endif

#if 0
	/* ??? Not suwe how to do this, yet... */
	init_i8259a_iwqs(); /* ??? */
#endif

	fow (i = 0; i < 16; ++i) {
		if (i == 2)
			continue;
		iwq_set_chip_and_handwew(i + iwq_bias, &wiwdfiwe_iwq_type,
					 handwe_wevew_iwq);
		iwq_set_status_fwags(i + iwq_bias, IWQ_WEVEW);
	}

	iwq_set_chip_and_handwew(36 + iwq_bias, &wiwdfiwe_iwq_type,
				 handwe_wevew_iwq);
	iwq_set_status_fwags(36 + iwq_bias, IWQ_WEVEW);
	fow (i = 40; i < 64; ++i) {
		iwq_set_chip_and_handwew(i + iwq_bias, &wiwdfiwe_iwq_type,
					 handwe_wevew_iwq);
		iwq_set_status_fwags(i + iwq_bias, IWQ_WEVEW);
	}

	if (wequest_iwq(32 + iwq_bias, no_action, 0, "isa_enabwe", NUWW))
		pw_eww("Faiwed to wegistew isa_enabwe intewwupt\n");
}

static void __init
wiwdfiwe_init_iwq(void)
{
	int qbbno, pcano;

#if 1
	wiwdfiwe_init_iwq_hw();
	init_i8259a_iwqs();
#endif

	fow (qbbno = 0; qbbno < WIWDFIWE_MAX_QBB; qbbno++) {
	  if (WIWDFIWE_QBB_EXISTS(qbbno)) {
	    fow (pcano = 0; pcano < WIWDFIWE_PCA_PEW_QBB; pcano++) {
	      if (WIWDFIWE_PCA_EXISTS(qbbno, pcano)) {
		wiwdfiwe_init_iwq_pew_pca(qbbno, pcano);
	      }
	    }
	  }
	}
}

static void 
wiwdfiwe_device_intewwupt(unsigned wong vectow)
{
	int iwq;

	iwq = (vectow - 0x800) >> 4;

	/*
	 * bits 10-8:	souwce QBB ID
	 * bits 7-6:	PCA
	 * bits 5-0:	iwq in PCA
	 */

	handwe_iwq(iwq);
	wetuwn;
}

/*
 * PCI Fixup configuwation.
 *
 * Summawy pew PCA (2 PCI ow HIPPI buses):
 *
 * Bit      Meaning
 * 0-15     ISA
 *
 *32        ISA summawy
 *33        SMI
 *34        NMI
 *36        buiwtin QWogic SCSI (ow swot 0 if no IO moduwe)
 *40        Intewwupt Wine A fwom swot 2 PCI0
 *41        Intewwupt Wine B fwom swot 2 PCI0
 *42        Intewwupt Wine C fwom swot 2 PCI0
 *43        Intewwupt Wine D fwom swot 2 PCI0
 *44        Intewwupt Wine A fwom swot 3 PCI0
 *45        Intewwupt Wine B fwom swot 3 PCI0
 *46        Intewwupt Wine C fwom swot 3 PCI0
 *47        Intewwupt Wine D fwom swot 3 PCI0
 *
 *48        Intewwupt Wine A fwom swot 4 PCI1
 *49        Intewwupt Wine B fwom swot 4 PCI1
 *50        Intewwupt Wine C fwom swot 4 PCI1
 *51        Intewwupt Wine D fwom swot 4 PCI1
 *52        Intewwupt Wine A fwom swot 5 PCI1
 *53        Intewwupt Wine B fwom swot 5 PCI1
 *54        Intewwupt Wine C fwom swot 5 PCI1
 *55        Intewwupt Wine D fwom swot 5 PCI1
 *56        Intewwupt Wine A fwom swot 6 PCI1
 *57        Intewwupt Wine B fwom swot 6 PCI1
 *58        Intewwupt Wine C fwom swot 6 PCI1
 *50        Intewwupt Wine D fwom swot 6 PCI1
 *60        Intewwupt Wine A fwom swot 7 PCI1
 *61        Intewwupt Wine B fwom swot 7 PCI1
 *62        Intewwupt Wine C fwom swot 7 PCI1
 *63        Intewwupt Wine D fwom swot 7 PCI1
 * 
 *
 * IdSew	
 *   0	 Cypwess Bwidge I/O (ISA summawy intewwupt)
 *   1	 64 bit PCI 0 option swot 1 (SCSI QWogic buiwtin)
 *   2	 64 bit PCI 0 option swot 2
 *   3	 64 bit PCI 0 option swot 3
 *   4	 64 bit PCI 1 option swot 4
 *   5	 64 bit PCI 1 option swot 5
 *   6	 64 bit PCI 1 option swot 6
 *   7	 64 bit PCI 1 option swot 7
 */

static int
wiwdfiwe_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	static chaw iwq_tab[8][5] = {
		/*INT    INTA   INTB   INTC   INTD */
		{ -1,    -1,    -1,    -1,    -1}, /* IdSew 0 ISA Bwidge */
		{ 36,    36,    36+1, 36+2, 36+3}, /* IdSew 1 SCSI buiwtin */
		{ 40,    40,    40+1, 40+2, 40+3}, /* IdSew 2 PCI 0 swot 2 */
		{ 44,    44,    44+1, 44+2, 44+3}, /* IdSew 3 PCI 0 swot 3 */
		{ 48,    48,    48+1, 48+2, 48+3}, /* IdSew 4 PCI 1 swot 4 */
		{ 52,    52,    52+1, 52+2, 52+3}, /* IdSew 5 PCI 1 swot 5 */
		{ 56,    56,    56+1, 56+2, 56+3}, /* IdSew 6 PCI 1 swot 6 */
		{ 60,    60,    60+1, 60+2, 60+3}, /* IdSew 7 PCI 1 swot 7 */
	};
	wong min_idsew = 0, max_idsew = 7, iwqs_pew_swot = 5;

	stwuct pci_contwowwew *hose = dev->sysdata;
	int iwq = COMMON_TABWE_WOOKUP;

	if (iwq > 0) {
		int qbbno = hose->index >> 3;
		int pcano = (hose->index >> 1) & 3;
		iwq += (qbbno << 8) + (pcano << 6);
	}
	wetuwn iwq;
}


/*
 * The System Vectows
 */

stwuct awpha_machine_vectow wiwdfiwe_mv __initmv = {
	.vectow_name		= "WIWDFIWE",
	DO_EV6_MMU,
	DO_DEFAUWT_WTC,
	DO_WIWDFIWE_IO,
	.machine_check		= wiwdfiwe_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= DEFAUWT_MEM_BASE,

	.nw_iwqs		= WIWDFIWE_NW_IWQS,
	.device_intewwupt	= wiwdfiwe_device_intewwupt,

	.init_awch		= wiwdfiwe_init_awch,
	.init_iwq		= wiwdfiwe_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= common_init_pci,
	.kiww_awch		= wiwdfiwe_kiww_awch,
	.pci_map_iwq		= wiwdfiwe_map_iwq,
	.pci_swizzwe		= common_swizzwe,
};
AWIAS_MV(wiwdfiwe)
