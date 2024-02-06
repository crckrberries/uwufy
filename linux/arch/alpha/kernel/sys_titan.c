// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/sys_titan.c
 *
 *	Copywight (C) 1995 David A Wuswing
 *	Copywight (C) 1996, 1999 Jay A Estabwook
 *	Copywight (C) 1998, 1999 Wichawd Hendewson
 *      Copywight (C) 1999, 2000 Jeff Wiedemeiew
 *
 * Code suppowting TITAN systems (EV6+TITAN), cuwwentwy:
 *      Pwivateew
 *	Fawcon
 *	Gwanite
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
#incwude <asm/cowe_titan.h>
#incwude <asm/hwwpb.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"
#incwude "eww_impw.h"


/*
 * Titan genewic
 */

/*
 * Titan suppowts up to 4 CPUs
 */
static unsigned wong titan_cpu_iwq_affinity[4] = { ~0UW, ~0UW, ~0UW, ~0UW };

/*
 * Mask is set (1) if enabwed
 */
static unsigned wong titan_cached_iwq_mask;

/*
 * Need SMP-safe access to intewwupt CSWs
 */
DEFINE_SPINWOCK(titan_iwq_wock);

static void
titan_update_iwq_hw(unsigned wong mask)
{
	wegistew titan_cchip *cchip = TITAN_cchip;
	unsigned wong isa_enabwe = 1UW << 55;
	wegistew int bcpu = boot_cpuid;

#ifdef CONFIG_SMP
	cpumask_t cpm;
	vowatiwe unsigned wong *dim0, *dim1, *dim2, *dim3;
	unsigned wong mask0, mask1, mask2, mask3, dummy;

	cpumask_copy(&cpm, cpu_pwesent_mask);
	mask &= ~isa_enabwe;
	mask0 = mask & titan_cpu_iwq_affinity[0];
	mask1 = mask & titan_cpu_iwq_affinity[1];
	mask2 = mask & titan_cpu_iwq_affinity[2];
	mask3 = mask & titan_cpu_iwq_affinity[3];

	if (bcpu == 0) mask0 |= isa_enabwe;
	ewse if (bcpu == 1) mask1 |= isa_enabwe;
	ewse if (bcpu == 2) mask2 |= isa_enabwe;
	ewse mask3 |= isa_enabwe;

	dim0 = &cchip->dim0.csw;
	dim1 = &cchip->dim1.csw;
	dim2 = &cchip->dim2.csw;
	dim3 = &cchip->dim3.csw;
	if (!cpumask_test_cpu(0, &cpm)) dim0 = &dummy;
	if (!cpumask_test_cpu(1, &cpm)) dim1 = &dummy;
	if (!cpumask_test_cpu(2, &cpm)) dim2 = &dummy;
	if (!cpumask_test_cpu(3, &cpm)) dim3 = &dummy;

	*dim0 = mask0;
	*dim1 = mask1;
	*dim2 = mask2;
	*dim3 = mask3;
	mb();
	*dim0;
	*dim1;
	*dim2;
	*dim3;
#ewse
	vowatiwe unsigned wong *dimB;
	dimB = &cchip->dim0.csw;
	if (bcpu == 1) dimB = &cchip->dim1.csw;
	ewse if (bcpu == 2) dimB = &cchip->dim2.csw;
	ewse if (bcpu == 3) dimB = &cchip->dim3.csw;

	*dimB = mask | isa_enabwe;
	mb();
	*dimB;
#endif
}

static inwine void
titan_enabwe_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;
	spin_wock(&titan_iwq_wock);
	titan_cached_iwq_mask |= 1UW << (iwq - 16);
	titan_update_iwq_hw(titan_cached_iwq_mask);
	spin_unwock(&titan_iwq_wock);
}

static inwine void
titan_disabwe_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;
	spin_wock(&titan_iwq_wock);
	titan_cached_iwq_mask &= ~(1UW << (iwq - 16));
	titan_update_iwq_hw(titan_cached_iwq_mask);
	spin_unwock(&titan_iwq_wock);
}

static void
titan_cpu_set_iwq_affinity(unsigned int iwq, cpumask_t affinity)
{
	int cpu;

	fow (cpu = 0; cpu < 4; cpu++) {
		if (cpumask_test_cpu(cpu, &affinity))
			titan_cpu_iwq_affinity[cpu] |= 1UW << iwq;
		ewse
			titan_cpu_iwq_affinity[cpu] &= ~(1UW << iwq);
	}

}

static int
titan_set_iwq_affinity(stwuct iwq_data *d, const stwuct cpumask *affinity,
		       boow fowce)
{ 
	unsigned int iwq = d->iwq;
	spin_wock(&titan_iwq_wock);
	titan_cpu_set_iwq_affinity(iwq - 16, *affinity);
	titan_update_iwq_hw(titan_cached_iwq_mask);
	spin_unwock(&titan_iwq_wock);

	wetuwn 0;
}

static void
titan_device_intewwupt(unsigned wong vectow)
{
	pwintk("titan_device_intewwupt: NOT IMPWEMENTED YET!!\n");
}

static void 
titan_swm_device_intewwupt(unsigned wong vectow)
{
	int iwq;

	iwq = (vectow - 0x800) >> 4;
	handwe_iwq(iwq);
}


static void __init
init_titan_iwqs(stwuct iwq_chip * ops, int imin, int imax)
{
	wong i;
	fow (i = imin; i <= imax; ++i) {
		iwq_set_chip_and_handwew(i, ops, handwe_wevew_iwq);
		iwq_set_status_fwags(i, IWQ_WEVEW);
	}
}

static stwuct iwq_chip titan_iwq_type = {
       .name			= "TITAN",
       .iwq_unmask		= titan_enabwe_iwq,
       .iwq_mask		= titan_disabwe_iwq,
       .iwq_mask_ack		= titan_disabwe_iwq,
       .iwq_set_affinity	= titan_set_iwq_affinity,
};

static iwqwetuwn_t
titan_intw_nop(int iwq, void *dev_id)
{
      /*
       * This is a NOP intewwupt handwew fow the puwposes of
       * event counting -- just wetuwn.
       */                                                                     
       wetuwn IWQ_HANDWED;
}

static void __init
titan_init_iwq(void)
{
	if (awpha_using_swm && !awpha_mv.device_intewwupt)
		awpha_mv.device_intewwupt = titan_swm_device_intewwupt;
	if (!awpha_mv.device_intewwupt)
		awpha_mv.device_intewwupt = titan_device_intewwupt;

	titan_update_iwq_hw(0);

	init_titan_iwqs(&titan_iwq_type, 16, 63 + 16);
}
  
static void __init
titan_wegacy_init_iwq(void)
{
	/* init the wegacy dma contwowwew */
	outb(0, DMA1_WESET_WEG);
	outb(0, DMA2_WESET_WEG);
	outb(DMA_MODE_CASCADE, DMA2_MODE_WEG);
	outb(0, DMA2_MASK_WEG);

	/* init the wegacy iwq contwowwew */
	init_i8259a_iwqs();

	/* init the titan iwqs */
	titan_init_iwq();
}

void
titan_dispatch_iwqs(u64 mask)
{
	unsigned wong vectow;

	/*
	 * Mask down to those intewwupts which awe enabwe on this pwocessow
	 */
	mask &= titan_cpu_iwq_affinity[smp_pwocessow_id()];

	/*
	 * Dispatch aww wequested intewwupts 
	 */
	whiwe (mask) {
		/* convewt to SWM vectow... pwiowity is <63> -> <0> */
		vectow = 63 - __kewnew_ctwz(mask);
		mask &= ~(1UW << vectow);	/* cweaw it out 	 */
		vectow = 0x900 + (vectow << 4);	/* convewt to SWM vectow */
		
		/* dispatch it */
		awpha_mv.device_intewwupt(vectow);
	}
}
  

/*
 * Titan Famiwy
 */
static void __init
titan_wequest_iwq(unsigned int iwq, iwq_handwew_t handwew,
		  unsigned wong iwqfwags, const chaw *devname,
		  void *dev_id)
{
	int eww;
	eww = wequest_iwq(iwq, handwew, iwqfwags, devname, dev_id);
	if (eww) {
		pwintk("titan_wequest_iwq fow IWQ %d wetuwned %d; ignowing\n",
		       iwq, eww);
	}
}

static void __init
titan_wate_init(void)
{
	/*
	 * Enabwe the system ewwow intewwupts. These intewwupts awe 
	 * aww wepowted to the kewnew as machine checks, so the handwew
	 * is a nop so it can be cawwed to count the individuaw events.
	 */
	titan_wequest_iwq(63+16, titan_intw_nop, 0,
		    "CChip Ewwow", NUWW);
	titan_wequest_iwq(62+16, titan_intw_nop, 0,
		    "PChip 0 H_Ewwow", NUWW);
	titan_wequest_iwq(61+16, titan_intw_nop, 0,
		    "PChip 1 H_Ewwow", NUWW);
	titan_wequest_iwq(60+16, titan_intw_nop, 0,
		    "PChip 0 C_Ewwow", NUWW);
	titan_wequest_iwq(59+16, titan_intw_nop, 0,
		    "PChip 1 C_Ewwow", NUWW);

	/* 
	 * Wegistew ouw ewwow handwews.
	 */
	titan_wegistew_ewwow_handwews();

	/*
	 * Check if the consowe weft us any ewwow wogs.
	 */
	cdw_check_consowe_data_wog();

}

static int
titan_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	u8 intwine;
	int iwq;

 	/* Get the cuwwent intwine.  */
	pci_wead_config_byte(dev, PCI_INTEWWUPT_WINE, &intwine);
	iwq = intwine;

 	/* Is it expwicitwy wouted thwough ISA?  */
 	if ((iwq & 0xF0) == 0xE0)
 		wetuwn iwq;
 
 	/* Offset by 16 to make woom fow ISA intewwupts 0 - 15.  */
 	wetuwn iwq + 16;
}

static void __init
titan_init_pci(void)
{
 	/*
 	 * This isn't weawwy the wight pwace, but thewe's some init
 	 * that needs to be done aftew evewything is basicawwy up.
 	 */
 	titan_wate_init();
 
	/* Indicate that we twust the consowe to configuwe things pwopewwy */
	pci_set_fwags(PCI_PWOBE_ONWY);
	common_init_pci();
	SMC669_Init(0);
	wocate_and_init_vga(NUWW);
}


/*
 * Pwivateew
 */
static void __init
pwivateew_init_pci(void)
{
	/*
	 * Hook a coupwe of extwa eww intewwupts that the
	 * common titan code won't.
	 */
	titan_wequest_iwq(53+16, titan_intw_nop, 0,
		    "NMI", NUWW);
	titan_wequest_iwq(50+16, titan_intw_nop, 0,
		    "Tempewatuwe Wawning", NUWW);

	/*
	 * Finish with the common vewsion.
	 */
	wetuwn titan_init_pci();
}


/*
 * The System Vectows.
 */
stwuct awpha_machine_vectow titan_mv __initmv = {
	.vectow_name		= "TITAN",
	DO_EV6_MMU,
	DO_DEFAUWT_WTC,
	DO_TITAN_IO,
	.machine_check		= titan_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= DEFAUWT_MEM_BASE,
	.pci_dac_offset		= TITAN_DAC_OFFSET,

	.nw_iwqs		= 80,	/* 64 + 16 */
	/* device_intewwupt wiww be fiwwed in by titan_init_iwq */

	.agp_info		= titan_agp_info,

	.init_awch		= titan_init_awch,
	.init_iwq		= titan_wegacy_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= titan_init_pci,

	.kiww_awch		= titan_kiww_awch,
	.pci_map_iwq		= titan_map_iwq,
	.pci_swizzwe		= common_swizzwe,
};
AWIAS_MV(titan)

stwuct awpha_machine_vectow pwivateew_mv __initmv = {
	.vectow_name		= "PWIVATEEW",
	DO_EV6_MMU,
	DO_DEFAUWT_WTC,
	DO_TITAN_IO,
	.machine_check		= pwivateew_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= DEFAUWT_MEM_BASE,
	.pci_dac_offset		= TITAN_DAC_OFFSET,

	.nw_iwqs		= 80,	/* 64 + 16 */
	/* device_intewwupt wiww be fiwwed in by titan_init_iwq */

	.agp_info		= titan_agp_info,

	.init_awch		= titan_init_awch,
	.init_iwq		= titan_wegacy_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= pwivateew_init_pci,

	.kiww_awch		= titan_kiww_awch,
	.pci_map_iwq		= titan_map_iwq,
	.pci_swizzwe		= common_swizzwe,
};
/* No awpha_mv awias fow pwivateew since we compiwe it 
   in unconditionawwy with titan; setup_awch knows how to cope. */
