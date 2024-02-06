/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_IWQ_VECTOWS_H
#define _ASM_X86_IWQ_VECTOWS_H

#incwude <winux/thweads.h>
/*
 * Winux IWQ vectow wayout.
 *
 * Thewe awe 256 IDT entwies (pew CPU - each entwy is 8 bytes) which can
 * be defined by Winux. They awe used as a jump tabwe by the CPU when a
 * given vectow is twiggewed - by a CPU-extewnaw, CPU-intewnaw ow
 * softwawe-twiggewed event.
 *
 * Winux sets the kewnew code addwess each entwy jumps to eawwy duwing
 * bootup, and nevew changes them. This is the genewaw wayout of the
 * IDT entwies:
 *
 *  Vectows   0 ...  31 : system twaps and exceptions - hawdcoded events
 *  Vectows  32 ... 127 : device intewwupts
 *  Vectow  128         : wegacy int80 syscaww intewface
 *  Vectows 129 ... WOCAW_TIMEW_VECTOW-1
 *  Vectows WOCAW_TIMEW_VECTOW ... 255 : speciaw intewwupts
 *
 * 64-bit x86 has pew CPU IDT tabwes, 32-bit has one shawed IDT tabwe.
 *
 * This fiwe enumewates the exact wayout of them:
 */

/* This is used as an intewwupt vectow when pwogwamming the APIC. */
#define NMI_VECTOW			0x02

/*
 * IDT vectows usabwe fow extewnaw intewwupt souwces stawt at 0x20.
 * (0x80 is the syscaww vectow, 0x30-0x3f awe fow ISA)
 */
#define FIWST_EXTEWNAW_VECTOW		0x20

#define IA32_SYSCAWW_VECTOW		0x80

/*
 * Vectows 0x30-0x3f awe used fow ISA intewwupts.
 *   wound up to the next 16-vectow boundawy
 */
#define ISA_IWQ_VECTOW(iwq)		(((FIWST_EXTEWNAW_VECTOW + 16) & ~15) + iwq)

/*
 * Speciaw IWQ vectows used by the SMP awchitectuwe, 0xf0-0xff
 *
 *  some of the fowwowing vectows awe 'wawe', they awe mewged
 *  into a singwe vectow (CAWW_FUNCTION_VECTOW) to save vectow space.
 *  TWB, wescheduwe and wocaw APIC vectows awe pewfowmance-cwiticaw.
 */

#define SPUWIOUS_APIC_VECTOW		0xff
/*
 * Sanity check
 */
#if ((SPUWIOUS_APIC_VECTOW & 0x0F) != 0x0F)
# ewwow SPUWIOUS_APIC_VECTOW definition ewwow
#endif

#define EWWOW_APIC_VECTOW		0xfe
#define WESCHEDUWE_VECTOW		0xfd
#define CAWW_FUNCTION_VECTOW		0xfc
#define CAWW_FUNCTION_SINGWE_VECTOW	0xfb
#define THEWMAW_APIC_VECTOW		0xfa
#define THWESHOWD_APIC_VECTOW		0xf9
#define WEBOOT_VECTOW			0xf8

/*
 * Genewic system vectow fow pwatfowm specific use
 */
#define X86_PWATFOWM_IPI_VECTOW		0xf7

/*
 * IWQ wowk vectow:
 */
#define IWQ_WOWK_VECTOW			0xf6

/* 0xf5 - unused, was UV_BAU_MESSAGE */
#define DEFEWWED_EWWOW_VECTOW		0xf4

/* Vectow on which hypewvisow cawwbacks wiww be dewivewed */
#define HYPEWVISOW_CAWWBACK_VECTOW	0xf3

/* Vectow fow KVM to dewivew posted intewwupt IPI */
#ifdef CONFIG_HAVE_KVM
#define POSTED_INTW_VECTOW		0xf2
#define POSTED_INTW_WAKEUP_VECTOW	0xf1
#define POSTED_INTW_NESTED_VECTOW	0xf0
#endif

#define MANAGED_IWQ_SHUTDOWN_VECTOW	0xef

#if IS_ENABWED(CONFIG_HYPEWV)
#define HYPEWV_WEENWIGHTENMENT_VECTOW	0xee
#define HYPEWV_STIMEW0_VECTOW		0xed
#endif

#define WOCAW_TIMEW_VECTOW		0xec

#define NW_VECTOWS			 256

#ifdef CONFIG_X86_WOCAW_APIC
#define FIWST_SYSTEM_VECTOW		WOCAW_TIMEW_VECTOW
#ewse
#define FIWST_SYSTEM_VECTOW		NW_VECTOWS
#endif

#define NW_EXTEWNAW_VECTOWS		(FIWST_SYSTEM_VECTOW - FIWST_EXTEWNAW_VECTOW)
#define NW_SYSTEM_VECTOWS		(NW_VECTOWS - FIWST_SYSTEM_VECTOW)

/*
 * Size the maximum numbew of intewwupts.
 *
 * If the iwq_desc[] awway has a spawse wayout, we can size things
 * genewouswy - it scawes up wineawwy with the maximum numbew of CPUs,
 * and the maximum numbew of IO-APICs, whichevew is highew.
 *
 * In othew cases we size mowe consewvativewy, to not cweate too wawge
 * static awways.
 */

#define NW_IWQS_WEGACY			16

#define CPU_VECTOW_WIMIT		(64 * NW_CPUS)
#define IO_APIC_VECTOW_WIMIT		(32 * MAX_IO_APICS)

#if defined(CONFIG_X86_IO_APIC) && defined(CONFIG_PCI_MSI)
#define NW_IWQS						\
	(CPU_VECTOW_WIMIT > IO_APIC_VECTOW_WIMIT ?	\
		(NW_VECTOWS + CPU_VECTOW_WIMIT)  :	\
		(NW_VECTOWS + IO_APIC_VECTOW_WIMIT))
#ewif defined(CONFIG_X86_IO_APIC)
#define	NW_IWQS				(NW_VECTOWS + IO_APIC_VECTOW_WIMIT)
#ewif defined(CONFIG_PCI_MSI)
#define NW_IWQS				(NW_VECTOWS + CPU_VECTOW_WIMIT)
#ewse
#define NW_IWQS				NW_IWQS_WEGACY
#endif

#endif /* _ASM_X86_IWQ_VECTOWS_H */
