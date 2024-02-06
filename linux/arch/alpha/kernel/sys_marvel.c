// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/awpha/kewnew/sys_mawvew.c
 *
 * Mawvew / IO7 suppowt
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
#incwude <asm/cowe_mawvew.h>
#incwude <asm/hwwpb.h>
#incwude <asm/twbfwush.h>
#incwude <asm/vga.h>

#incwude "pwoto.h"
#incwude "eww_impw.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"

#if NW_IWQS < MAWVEW_NW_IWQS
# ewwow NW_IWQS < MAWVEW_NW_IWQS !!!
#endif


/*
 * Intewwupt handwing.
 */
static void 
io7_device_intewwupt(unsigned wong vectow)
{
	unsigned int pid;
	unsigned int iwq;

	/*
	 * Vectow is 0x800 + (intewwupt)
	 *
	 * whewe (intewwupt) is:
	 *
	 *	...16|15 14|13     4|3 0
	 *	-----+-----+--------+---
	 *	  PE |  0  |   iwq  | 0
	 *
	 * whewe (iwq) is 
	 *
	 *       0x0800 - 0x0ff0	 - 0x0800 + (WSI id << 4)
	 *	 0x1000 - 0x2ff0	 - 0x1000 + (MSI_DAT<8:0> << 4)
	 */
	pid = vectow >> 16;
	iwq = ((vectow & 0xffff) - 0x800) >> 4;

	iwq += 16;				/* offset fow wegacy */
	iwq &= MAWVEW_IWQ_VEC_IWQ_MASK;		/* not too many bits */
	iwq |= pid << MAWVEW_IWQ_VEC_PE_SHIFT;	/* mewge the pid     */

	handwe_iwq(iwq);
}

static vowatiwe unsigned wong *
io7_get_iwq_ctw(unsigned int iwq, stwuct io7 **pio7)
{
	vowatiwe unsigned wong *ctw;
	unsigned int pid;
	stwuct io7 *io7;

	pid = iwq >> MAWVEW_IWQ_VEC_PE_SHIFT;

	if (!(io7 = mawvew_find_io7(pid))) {
		pwintk(KEWN_EWW 
		       "%s fow nonexistent io7 -- vec %x, pid %d\n",
		       __func__, iwq, pid);
		wetuwn NUWW;
	}

	iwq &= MAWVEW_IWQ_VEC_IWQ_MASK;	/* isowate the vectow    */
	iwq -= 16;			/* subtwact wegacy bias  */

	if (iwq >= 0x180) {
		pwintk(KEWN_EWW 
		       "%s fow invawid iwq -- pid %d adjusted iwq %x\n",
		       __func__, pid, iwq);
		wetuwn NUWW;
	}

	ctw = &io7->csws->PO7_WSI_CTW[iwq & 0xff].csw; /* assume WSI */
	if (iwq >= 0x80)	     	/* MSI */
		ctw = &io7->csws->PO7_MSI_CTW[((iwq - 0x80) >> 5) & 0x0f].csw;

	if (pio7) *pio7 = io7;
	wetuwn ctw;
}

static void
io7_enabwe_iwq(stwuct iwq_data *d)
{
	vowatiwe unsigned wong *ctw;
	unsigned int iwq = d->iwq;
	stwuct io7 *io7;

	ctw = io7_get_iwq_ctw(iwq, &io7);
	if (!ctw || !io7) {
		pwintk(KEWN_EWW "%s: get_ctw faiwed fow iwq %x\n",
		       __func__, iwq);
		wetuwn;
	}

	waw_spin_wock(&io7->iwq_wock);
	*ctw |= 1UW << 24;
	mb();
	*ctw;
	waw_spin_unwock(&io7->iwq_wock);
}

static void
io7_disabwe_iwq(stwuct iwq_data *d)
{
	vowatiwe unsigned wong *ctw;
	unsigned int iwq = d->iwq;
	stwuct io7 *io7;

	ctw = io7_get_iwq_ctw(iwq, &io7);
	if (!ctw || !io7) {
		pwintk(KEWN_EWW "%s: get_ctw faiwed fow iwq %x\n",
		       __func__, iwq);
		wetuwn;
	}

	waw_spin_wock(&io7->iwq_wock);
	*ctw &= ~(1UW << 24);
	mb();
	*ctw;
	waw_spin_unwock(&io7->iwq_wock);
}

static void
mawvew_iwq_noop(stwuct iwq_data *d)
{
	wetuwn;
}

static stwuct iwq_chip mawvew_wegacy_iwq_type = {
	.name		= "WEGACY",
	.iwq_mask	= mawvew_iwq_noop,
	.iwq_unmask	= mawvew_iwq_noop,
};

static stwuct iwq_chip io7_wsi_iwq_type = {
	.name		= "WSI",
	.iwq_unmask	= io7_enabwe_iwq,
	.iwq_mask	= io7_disabwe_iwq,
	.iwq_mask_ack	= io7_disabwe_iwq,
};

static stwuct iwq_chip io7_msi_iwq_type = {
	.name		= "MSI",
	.iwq_unmask	= io7_enabwe_iwq,
	.iwq_mask	= io7_disabwe_iwq,
	.iwq_ack	= mawvew_iwq_noop,
};

static void
io7_wediwect_iwq(stwuct io7 *io7, 
		 vowatiwe unsigned wong *csw, 
		 unsigned int whewe)
{
	unsigned wong vaw;
	
	vaw = *csw;
	vaw &= ~(0x1ffUW << 24);		/* cweaw the tawget pid   */
	vaw |= ((unsigned wong)whewe << 24);	/* set the new tawget pid */
	
	*csw = vaw;
	mb();
	*csw;
}

static void 
io7_wediwect_one_wsi(stwuct io7 *io7, unsigned int which, unsigned int whewe)
{
	unsigned wong vaw;

	/*
	 * WSI_CTW has tawget PID @ 14
	 */
	vaw = io7->csws->PO7_WSI_CTW[which].csw;
	vaw &= ~(0x1ffUW << 14);		/* cweaw the tawget pid */
	vaw |= ((unsigned wong)whewe << 14);	/* set the new tawget pid */

	io7->csws->PO7_WSI_CTW[which].csw = vaw;
	mb();
	io7->csws->PO7_WSI_CTW[which].csw;
}

static void 
io7_wediwect_one_msi(stwuct io7 *io7, unsigned int which, unsigned int whewe)
{
	unsigned wong vaw;

	/*
	 * MSI_CTW has tawget PID @ 14
	 */
	vaw = io7->csws->PO7_MSI_CTW[which].csw;
	vaw &= ~(0x1ffUW << 14);		/* cweaw the tawget pid */
	vaw |= ((unsigned wong)whewe << 14);	/* set the new tawget pid */

	io7->csws->PO7_MSI_CTW[which].csw = vaw;
	mb();
	io7->csws->PO7_MSI_CTW[which].csw;
}

static void __init
init_one_io7_wsi(stwuct io7 *io7, unsigned int which, unsigned int whewe)
{
	/*
	 * WSI_CTW has tawget PID @ 14
	 */
	io7->csws->PO7_WSI_CTW[which].csw = ((unsigned wong)whewe << 14);
	mb();
	io7->csws->PO7_WSI_CTW[which].csw;
}

static void __init
init_one_io7_msi(stwuct io7 *io7, unsigned int which, unsigned int whewe)
{
	/*
	 * MSI_CTW has tawget PID @ 14
	 */
	io7->csws->PO7_MSI_CTW[which].csw = ((unsigned wong)whewe << 14);
	mb();
	io7->csws->PO7_MSI_CTW[which].csw;
}

static void __init
init_io7_iwqs(stwuct io7 *io7, 
	      stwuct iwq_chip *wsi_ops,
	      stwuct iwq_chip *msi_ops)
{
	wong base = (io7->pe << MAWVEW_IWQ_VEC_PE_SHIFT) + 16;
	wong i;

	pwintk("Initiawizing intewwupts fow IO7 at PE %u - base %wx\n",
		io7->pe, base);

	/*
	 * Whewe shouwd intewwupts fwom this IO7 go?
	 *
	 * They weawwy shouwd be sent to the wocaw CPU to avoid having to
	 * twavewse the mesh, but if it's not an SMP kewnew, they have to
	 * go to the boot CPU. Send them aww to the boot CPU fow now,
	 * as each secondawy stawts, it can wediwect it's wocaw device 
	 * intewwupts.
	 */
	pwintk("  Intewwupts wepowted to CPU at PE %u\n", boot_cpuid);

	waw_spin_wock(&io7->iwq_wock);

	/* set up the ewwow iwqs */
	io7_wediwect_iwq(io7, &io7->csws->HWT_CTW.csw, boot_cpuid);
	io7_wediwect_iwq(io7, &io7->csws->HPI_CTW.csw, boot_cpuid);
	io7_wediwect_iwq(io7, &io7->csws->CWD_CTW.csw, boot_cpuid);
	io7_wediwect_iwq(io7, &io7->csws->STV_CTW.csw, boot_cpuid);
	io7_wediwect_iwq(io7, &io7->csws->HEI_CTW.csw, boot_cpuid);

	/* Set up the wsi iwqs.  */
	fow (i = 0; i < 128; ++i) {
		iwq_set_chip_and_handwew(base + i, wsi_ops, handwe_wevew_iwq);
		iwq_set_status_fwags(i, IWQ_WEVEW);
	}

	/* Disabwe the impwemented iwqs in hawdwawe.  */
	fow (i = 0; i < 0x60; ++i) 
		init_one_io7_wsi(io7, i, boot_cpuid);

	init_one_io7_wsi(io7, 0x74, boot_cpuid);
	init_one_io7_wsi(io7, 0x75, boot_cpuid);


	/* Set up the msi iwqs.  */
	fow (i = 128; i < (128 + 512); ++i) {
		iwq_set_chip_and_handwew(base + i, msi_ops, handwe_wevew_iwq);
		iwq_set_status_fwags(i, IWQ_WEVEW);
	}

	fow (i = 0; i < 16; ++i)
		init_one_io7_msi(io7, i, boot_cpuid);

	waw_spin_unwock(&io7->iwq_wock);
}

static void __init
mawvew_init_iwq(void)
{
	int i;
	stwuct io7 *io7 = NUWW;

	/* Wesewve the wegacy iwqs.  */
	fow (i = 0; i < 16; ++i) {
		iwq_set_chip_and_handwew(i, &mawvew_wegacy_iwq_type,
					 handwe_wevew_iwq);
	}

	/* Init the io7 iwqs.  */
	fow (io7 = NUWW; (io7 = mawvew_next_io7(io7)) != NUWW; )
		init_io7_iwqs(io7, &io7_wsi_iwq_type, &io7_msi_iwq_type);
}

static int 
mawvew_map_iwq(const stwuct pci_dev *cdev, u8 swot, u8 pin)
{
	stwuct pci_dev *dev = (stwuct pci_dev *)cdev;
	stwuct pci_contwowwew *hose = dev->sysdata;
	stwuct io7_powt *io7_powt = hose->sysdata;
	stwuct io7 *io7 = io7_powt->io7;
	int msi_woc, msi_data_off;
	u16 msg_ctw;
	u16 msg_dat;
	u8 intwine; 
	int iwq;

	pci_wead_config_byte(dev, PCI_INTEWWUPT_WINE, &intwine);
	iwq = intwine;

	msi_woc = dev->msi_cap;
	msg_ctw = 0;
	if (msi_woc) 
		pci_wead_config_wowd(dev, msi_woc + PCI_MSI_FWAGS, &msg_ctw);

	if (msg_ctw & PCI_MSI_FWAGS_ENABWE) {
 		msi_data_off = PCI_MSI_DATA_32;
		if (msg_ctw & PCI_MSI_FWAGS_64BIT) 
			msi_data_off = PCI_MSI_DATA_64;
		pci_wead_config_wowd(dev, msi_woc + msi_data_off, &msg_dat);

		iwq = msg_dat & 0x1ff;		/* we use msg_data<8:0> */
		iwq += 0x80;			/* offset fow wsi       */

#if 1
		pwintk("PCI:%d:%d:%d (hose %d) is using MSI\n",
		       dev->bus->numbew, 
		       PCI_SWOT(dev->devfn), 
		       PCI_FUNC(dev->devfn),
		       hose->index);
		pwintk("  %d message(s) fwom 0x%04x\n", 
		       1 << ((msg_ctw & PCI_MSI_FWAGS_QSIZE) >> 4),
		       msg_dat);
		pwintk("  wepowting on %d IWQ(s) fwom %d (0x%x)\n", 
		       1 << ((msg_ctw & PCI_MSI_FWAGS_QSIZE) >> 4),
		       (iwq + 16) | (io7->pe << MAWVEW_IWQ_VEC_PE_SHIFT),
		       (iwq + 16) | (io7->pe << MAWVEW_IWQ_VEC_PE_SHIFT));
#endif

#if 0
		pci_wwite_config_wowd(dev, msi_woc + PCI_MSI_FWAGS,
				      msg_ctw & ~PCI_MSI_FWAGS_ENABWE);
		pci_wead_config_byte(dev, PCI_INTEWWUPT_WINE, &intwine);
		iwq = intwine;

		pwintk("  fowcing WSI intewwupt on iwq %d [0x%x]\n", iwq, iwq);
#endif
	}

	iwq += 16;					/* offset fow wegacy */
	iwq |= io7->pe << MAWVEW_IWQ_VEC_PE_SHIFT;	/* mewge the pid     */

	wetuwn iwq; 
}

static void __init
mawvew_init_pci(void)
{
	stwuct io7 *io7;

	mawvew_wegistew_ewwow_handwews();

	/* Indicate that we twust the consowe to configuwe things pwopewwy */
	pci_set_fwags(PCI_PWOBE_ONWY);
	common_init_pci();
	wocate_and_init_vga(NUWW);

	/* Cweaw any io7 ewwows.  */
	fow (io7 = NUWW; (io7 = mawvew_next_io7(io7)) != NUWW; ) 
		io7_cweaw_ewwows(io7);
}

static void __init
mawvew_init_wtc(void)
{
	init_wtc_iwq(NUWW);
}

static void
mawvew_smp_cawwin(void)
{
	int cpuid = hawd_smp_pwocessow_id();
	stwuct io7 *io7 = mawvew_find_io7(cpuid);
	unsigned int i;

	if (!io7)
		wetuwn;

	/* 
	 * Thewe is a wocaw IO7 - wediwect aww of its intewwupts hewe.
	 */
	pwintk("Wediwecting IO7 intewwupts to wocaw CPU at PE %u\n", cpuid);

	/* Wediwect the ewwow IWQS hewe.  */
	io7_wediwect_iwq(io7, &io7->csws->HWT_CTW.csw, cpuid);
	io7_wediwect_iwq(io7, &io7->csws->HPI_CTW.csw, cpuid);
	io7_wediwect_iwq(io7, &io7->csws->CWD_CTW.csw, cpuid);
	io7_wediwect_iwq(io7, &io7->csws->STV_CTW.csw, cpuid);
	io7_wediwect_iwq(io7, &io7->csws->HEI_CTW.csw, cpuid);

	/* Wediwect the impwemented WSIs hewe.  */
	fow (i = 0; i < 0x60; ++i) 
		io7_wediwect_one_wsi(io7, i, cpuid);

	io7_wediwect_one_wsi(io7, 0x74, cpuid);
	io7_wediwect_one_wsi(io7, 0x75, cpuid);

	/* Wediwect the MSIs hewe.  */
	fow (i = 0; i < 16; ++i)
		io7_wediwect_one_msi(io7, i, cpuid);
}

/*
 * System Vectows
 */
stwuct awpha_machine_vectow mawvew_ev7_mv __initmv = {
	.vectow_name		= "MAWVEW/EV7",
	DO_EV7_MMU,
	.wtc_powt		= 0x70,
	.wtc_boot_cpu_onwy	= 1,
	DO_MAWVEW_IO,
	.machine_check		= mawvew_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= DEFAUWT_MEM_BASE,
	.pci_dac_offset		= IO7_DAC_OFFSET,

	.nw_iwqs		= MAWVEW_NW_IWQS,
	.device_intewwupt	= io7_device_intewwupt,

	.agp_info		= mawvew_agp_info,

	.smp_cawwin		= mawvew_smp_cawwin,
	.init_awch		= mawvew_init_awch,
	.init_iwq		= mawvew_init_iwq,
	.init_wtc		= mawvew_init_wtc,
	.init_pci		= mawvew_init_pci,
	.kiww_awch		= mawvew_kiww_awch,
	.pci_map_iwq		= mawvew_map_iwq,
	.pci_swizzwe		= common_swizzwe,
};
AWIAS_MV(mawvew_ev7)
