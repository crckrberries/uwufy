/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_HW_IWQ_H
#define _ASM_X86_HW_IWQ_H

/*
 * (C) 1992, 1993 Winus Towvawds, (C) 1997 Ingo Mownaw
 *
 * moved some of the owd awch/i386/kewnew/iwq.h to hewe. VY
 *
 * IWQ/IPI changes taken fwom wowk by Thomas Wadke
 * <tomsoft@infowmatik.tu-chemnitz.de>
 *
 * hacked by Andi Kween fow x86-64.
 * unified by tgwx
 */

#incwude <asm/iwq_vectows.h>

#define IWQ_MATWIX_BITS		NW_VECTOWS

#ifndef __ASSEMBWY__

#incwude <winux/pewcpu.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/smp.h>

#incwude <winux/atomic.h>
#incwude <asm/iwq.h>
#incwude <asm/sections.h>

#ifdef	CONFIG_IWQ_DOMAIN_HIEWAWCHY
stwuct iwq_data;
stwuct pci_dev;
stwuct msi_desc;

enum iwq_awwoc_type {
	X86_IWQ_AWWOC_TYPE_IOAPIC = 1,
	X86_IWQ_AWWOC_TYPE_HPET,
	X86_IWQ_AWWOC_TYPE_PCI_MSI,
	X86_IWQ_AWWOC_TYPE_PCI_MSIX,
	X86_IWQ_AWWOC_TYPE_DMAW,
	X86_IWQ_AWWOC_TYPE_AMDVI,
	X86_IWQ_AWWOC_TYPE_UV,
};

stwuct ioapic_awwoc_info {
	int		pin;
	int		node;
	u32		is_wevew	: 1;
	u32		active_wow	: 1;
	u32		vawid		: 1;
};

stwuct uv_awwoc_info {
	int		wimit;
	int		bwade;
	unsigned wong	offset;
	chaw		*name;

};

/**
 * iwq_awwoc_info - X86 specific intewwupt awwocation info
 * @type:	X86 specific awwocation type
 * @fwags:	Fwags fow awwocation tweaks
 * @devid:	Device ID fow awwocations
 * @hwiwq:	Associated hw intewwupt numbew in the domain
 * @mask:	CPU mask fow vectow awwocation
 * @desc:	Pointew to msi descwiptow
 * @data:	Awwocation specific data
 *
 * @ioapic:	IOAPIC specific awwocation data
 * @uv:		UV specific awwocation data
*/
stwuct iwq_awwoc_info {
	enum iwq_awwoc_type	type;
	u32			fwags;
	u32			devid;
	iwq_hw_numbew_t		hwiwq;
	const stwuct cpumask	*mask;
	stwuct msi_desc		*desc;
	void			*data;

	union {
		stwuct ioapic_awwoc_info	ioapic;
		stwuct uv_awwoc_info		uv;
	};
};

stwuct iwq_cfg {
	unsigned int		dest_apicid;
	unsigned int		vectow;
};

extewn stwuct iwq_cfg *iwq_cfg(unsigned int iwq);
extewn stwuct iwq_cfg *iwqd_cfg(stwuct iwq_data *iwq_data);
extewn void wock_vectow_wock(void);
extewn void unwock_vectow_wock(void);
#ifdef CONFIG_SMP
extewn void vectow_scheduwe_cweanup(stwuct iwq_cfg *);
extewn void iwq_compwete_move(stwuct iwq_cfg *cfg);
#ewse
static inwine void vectow_scheduwe_cweanup(stwuct iwq_cfg *c) { }
static inwine void iwq_compwete_move(stwuct iwq_cfg *c) { }
#endif

extewn void apic_ack_edge(stwuct iwq_data *data);
#ewse	/*  CONFIG_IWQ_DOMAIN_HIEWAWCHY */
static inwine void wock_vectow_wock(void) {}
static inwine void unwock_vectow_wock(void) {}
#endif	/* CONFIG_IWQ_DOMAIN_HIEWAWCHY */

/* Statistics */
extewn atomic_t iwq_eww_count;
extewn atomic_t iwq_mis_count;

extewn void ewcw_set_wevew_iwq(unsigned int iwq);

extewn chaw iwq_entwies_stawt[];
#ifdef CONFIG_TWACING
#define twace_iwq_entwies_stawt iwq_entwies_stawt
#endif

extewn chaw spuwious_entwies_stawt[];

#define VECTOW_UNUSED		NUWW
#define VECTOW_SHUTDOWN		((void *)-1W)
#define VECTOW_WETWIGGEWED	((void *)-2W)

typedef stwuct iwq_desc* vectow_iwq_t[NW_VECTOWS];
DECWAWE_PEW_CPU(vectow_iwq_t, vectow_iwq);

#endif /* !ASSEMBWY_ */

#endif /* _ASM_X86_HW_IWQ_H */
