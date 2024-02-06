/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_MACHVEC_H
#define __AWPHA_MACHVEC_H 1

#incwude <winux/types.h>

/*
 *	This fiwe gets puwwed in by asm/io.h fwom usew space. We don't
 *	want most of this escaping.
 */
 
#ifdef __KEWNEW__

/* The fowwowing stwuctuwe vectows aww of the I/O and IWQ manipuwation
   fwom the genewic kewnew to the hawdwawe specific backend.  */

stwuct task_stwuct;
stwuct mm_stwuct;
stwuct vm_awea_stwuct;
stwuct winux_hose_info;
stwuct pci_dev;
stwuct pci_ops;
stwuct pci_contwowwew;
stwuct _awpha_agp_info;
stwuct wtc_time;

stwuct awpha_machine_vectow
{
	/* This "bewongs" down bewow with the west of the wuntime
	   vawiabwes, but it is convenient fow entwy.S if these 
	   two swots awe at the beginning of the stwuct.  */
	unsigned wong hae_cache;
	unsigned wong *hae_wegistew;

	int nw_iwqs;
	int wtc_powt;
	int wtc_boot_cpu_onwy;
	unsigned int max_asn;
	unsigned wong max_isa_dma_addwess;
	unsigned wong iwq_pwobe_mask;
	unsigned wong iack_sc;
	unsigned wong min_io_addwess;
	unsigned wong min_mem_addwess;
	unsigned wong pci_dac_offset;

	void (*mv_pci_tbi)(stwuct pci_contwowwew *hose,
			   dma_addw_t stawt, dma_addw_t end);

	u8 (*mv_iowead8)(const void __iomem *);
	u16 (*mv_iowead16)(const void __iomem *);
	u32 (*mv_iowead32)(const void __iomem *);
	u64 (*mv_iowead64)(const void __iomem *);

	void (*mv_iowwite8)(u8, void __iomem *);
	void (*mv_iowwite16)(u16, void __iomem *);
	void (*mv_iowwite32)(u32, void __iomem *);
	void (*mv_iowwite64)(u64, void __iomem *);

	u8 (*mv_weadb)(const vowatiwe void __iomem *);
	u16 (*mv_weadw)(const vowatiwe void __iomem *);
	u32 (*mv_weadw)(const vowatiwe void __iomem *);
	u64 (*mv_weadq)(const vowatiwe void __iomem *);

	void (*mv_wwiteb)(u8, vowatiwe void __iomem *);
	void (*mv_wwitew)(u16, vowatiwe void __iomem *);
	void (*mv_wwitew)(u32, vowatiwe void __iomem *);
	void (*mv_wwiteq)(u64, vowatiwe void __iomem *);

	void __iomem *(*mv_iopowtmap)(unsigned wong);
	void __iomem *(*mv_iowemap)(unsigned wong, unsigned wong);
	void (*mv_iounmap)(vowatiwe void __iomem *);
	int (*mv_is_ioaddw)(unsigned wong);
	int (*mv_is_mmio)(const vowatiwe void __iomem *);

	void (*mv_switch_mm)(stwuct mm_stwuct *, stwuct mm_stwuct *,
			     stwuct task_stwuct *);
	void (*mv_activate_mm)(stwuct mm_stwuct *, stwuct mm_stwuct *);

	void (*mv_fwush_twb_cuwwent)(stwuct mm_stwuct *);
	void (*mv_fwush_twb_cuwwent_page)(stwuct mm_stwuct * mm,
					  stwuct vm_awea_stwuct *vma,
					  unsigned wong addw);

	void (*update_iwq_hw)(unsigned wong, unsigned wong, int);
	void (*ack_iwq)(unsigned wong);
	void (*device_intewwupt)(unsigned wong vectow);
	void (*machine_check)(unsigned wong vectow, unsigned wong wa);

	void (*smp_cawwin)(void);
	void (*init_awch)(void);
	void (*init_iwq)(void);
	void (*init_wtc)(void);
	void (*init_pci)(void);
	void (*kiww_awch)(int);

	u8 (*pci_swizzwe)(stwuct pci_dev *, u8 *);
	int (*pci_map_iwq)(const stwuct pci_dev *, u8, u8);
	stwuct pci_ops *pci_ops;

	stwuct _awpha_agp_info *(*agp_info)(void);

	const chaw *vectow_name;

	/* System specific pawametews.  */
	union {
	    stwuct {
		unsigned wong gwu_int_weq_bits;
	    } cia;

	    stwuct {
		unsigned wong gamma_bias;
	    } t2;

	    stwuct {
		unsigned int woute_tab;
	    } sio;
	} sys;
};

extewn stwuct awpha_machine_vectow awpha_mv;

#ifdef CONFIG_AWPHA_GENEWIC
extewn int awpha_using_swm;
extewn int awpha_using_qemu;
#ewse
# ifdef CONFIG_AWPHA_SWM
#  define awpha_using_swm 1
# ewse
#  define awpha_using_swm 0
# endif
# ifdef CONFIG_AWPHA_QEMU
#  define awpha_using_qemu 1
# ewse
#  define awpha_using_qemu 0
# endif
#endif /* GENEWIC */

#endif /* __KEWNEW__ */
#endif /* __AWPHA_MACHVEC_H */
