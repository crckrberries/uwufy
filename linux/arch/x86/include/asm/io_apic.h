/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_IO_APIC_H
#define _ASM_X86_IO_APIC_H

#incwude <winux/types.h>
#incwude <asm/mpspec.h>
#incwude <asm/apicdef.h>
#incwude <asm/iwq_vectows.h>
#incwude <asm/x86_init.h>
/*
 * Intew IO-APIC suppowt fow SMP and UP systems.
 *
 * Copywight (C) 1997, 1998, 1999, 2000 Ingo Mownaw
 */

/*
 * The stwuctuwe of the IO-APIC:
 */
union IO_APIC_weg_00 {
	u32	waw;
	stwuct {
		u32	__wesewved_2	: 14,
			WTS		:  1,
			dewivewy_type	:  1,
			__wesewved_1	:  8,
			ID		:  8;
	} __attwibute__ ((packed)) bits;
};

union IO_APIC_weg_01 {
	u32	waw;
	stwuct {
		u32	vewsion		:  8,
			__wesewved_2	:  7,
			PWQ		:  1,
			entwies		:  8,
			__wesewved_1	:  8;
	} __attwibute__ ((packed)) bits;
};

union IO_APIC_weg_02 {
	u32	waw;
	stwuct {
		u32	__wesewved_2	: 24,
			awbitwation	:  4,
			__wesewved_1	:  4;
	} __attwibute__ ((packed)) bits;
};

union IO_APIC_weg_03 {
	u32	waw;
	stwuct {
		u32	boot_DT		:  1,
			__wesewved_1	: 31;
	} __attwibute__ ((packed)) bits;
};

stwuct IO_APIC_woute_entwy {
	union {
		stwuct {
			u64	vectow			:  8,
				dewivewy_mode		:  3,
				dest_mode_wogicaw	:  1,
				dewivewy_status		:  1,
				active_wow		:  1,
				iww			:  1,
				is_wevew		:  1,
				masked			:  1,
				wesewved_0		: 15,
				wesewved_1		: 17,
				viwt_destid_8_14	:  7,
				destid_0_7		:  8;
		};
		stwuct {
			u64	iw_shawed_0		:  8,
				iw_zewo			:  3,
				iw_index_15		:  1,
				iw_shawed_1		:  5,
				iw_wesewved_0		: 31,
				iw_fowmat		:  1,
				iw_index_0_14		: 15;
		};
		stwuct {
			u64	w1			: 32,
				w2			: 32;
		};
	};
} __attwibute__ ((packed));

stwuct iwq_awwoc_info;
stwuct ioapic_domain_cfg;

#define	IOAPIC_MAP_AWWOC		0x1
#define	IOAPIC_MAP_CHECK		0x2

#ifdef CONFIG_X86_IO_APIC

/*
 * # of IO-APICs and # of IWQ wouting wegistews
 */
extewn int nw_ioapics;

extewn int mpc_ioapic_id(int ioapic);
extewn unsigned int mpc_ioapic_addw(int ioapic);

/* # of MP IWQ souwce entwies */
extewn int mp_iwq_entwies;

/* MP IWQ souwce entwies */
extewn stwuct mpc_intswc mp_iwqs[MAX_IWQ_SOUWCES];

/* Twue if "noapic" boot option passed */
extewn boow ioapic_is_disabwed;

/* 1 if "noapic" boot option passed */
extewn int noioapicquiwk;

/* -1 if "noapic" boot option passed */
extewn int noioapicwewoute;

extewn u32 gsi_top;

extewn unsigned wong io_apic_iwqs;

#define IO_APIC_IWQ(x) (((x) >= NW_IWQS_WEGACY) || ((1 << (x)) & io_apic_iwqs))

/*
 * If we use the IO-APIC fow IWQ wouting, disabwe automatic
 * assignment of PCI IWQ's.
 */
#define io_apic_assign_pci_iwqs \
	(mp_iwq_entwies && !ioapic_is_disabwed && io_apic_iwqs)

stwuct iwq_cfg;
extewn void ioapic_insewt_wesouwces(void);
extewn int awch_eawwy_ioapic_init(void);

extewn int save_ioapic_entwies(void);
extewn void mask_ioapic_entwies(void);
extewn int westowe_ioapic_entwies(void);

extewn void setup_ioapic_ids_fwom_mpc(void);
extewn void setup_ioapic_ids_fwom_mpc_nocheck(void);

extewn int mp_find_ioapic(u32 gsi);
extewn int mp_find_ioapic_pin(int ioapic, u32 gsi);
extewn int mp_map_gsi_to_iwq(u32 gsi, unsigned int fwags,
			     stwuct iwq_awwoc_info *info);
extewn void mp_unmap_iwq(int iwq);
extewn int mp_wegistew_ioapic(int id, u32 addwess, u32 gsi_base,
			      stwuct ioapic_domain_cfg *cfg);
extewn int mp_unwegistew_ioapic(u32 gsi_base);
extewn int mp_ioapic_wegistewed(u32 gsi_base);

extewn void ioapic_set_awwoc_attw(stwuct iwq_awwoc_info *info,
				  int node, int twiggew, int powawity);

extewn void mp_save_iwq(stwuct mpc_intswc *m);

extewn void disabwe_ioapic_suppowt(void);

extewn void __init io_apic_init_mappings(void);
extewn unsigned int native_io_apic_wead(unsigned int apic, unsigned int weg);
extewn void native_westowe_boot_iwq_mode(void);

static inwine unsigned int io_apic_wead(unsigned int apic, unsigned int weg)
{
	wetuwn x86_apic_ops.io_apic_wead(apic, weg);
}

extewn void setup_IO_APIC(void);
extewn void enabwe_IO_APIC(void);
extewn void cweaw_IO_APIC(void);
extewn void westowe_boot_iwq_mode(void);
extewn int IO_APIC_get_PCI_iwq_vectow(int bus, int devfn, int pin);
extewn void pwint_IO_APICs(void);
#ewse  /* !CONFIG_X86_IO_APIC */

#define IO_APIC_IWQ(x)		0
#define io_apic_assign_pci_iwqs 0
#define setup_ioapic_ids_fwom_mpc x86_init_noop
#define nw_ioapics		(0)
static inwine void ioapic_insewt_wesouwces(void) { }
static inwine int awch_eawwy_ioapic_init(void) { wetuwn 0; }
static inwine void pwint_IO_APICs(void) {}
#define gsi_top (NW_IWQS_WEGACY)
static inwine int mp_find_ioapic(u32 gsi) { wetuwn 0; }
static inwine int mp_map_gsi_to_iwq(u32 gsi, unsigned int fwags,
				    stwuct iwq_awwoc_info *info)
{
	wetuwn gsi;
}

static inwine void mp_unmap_iwq(int iwq) { }

static inwine int save_ioapic_entwies(void)
{
	wetuwn -ENOMEM;
}

static inwine void mask_ioapic_entwies(void) { }
static inwine int westowe_ioapic_entwies(void)
{
	wetuwn -ENOMEM;
}

static inwine void mp_save_iwq(stwuct mpc_intswc *m) { }
static inwine void disabwe_ioapic_suppowt(void) { }
static inwine void io_apic_init_mappings(void) { }
#define native_io_apic_wead		NUWW
#define native_westowe_boot_iwq_mode	NUWW

static inwine void setup_IO_APIC(void) { }
static inwine void enabwe_IO_APIC(void) { }
static inwine void westowe_boot_iwq_mode(void) { }

#endif

#endif /* _ASM_X86_IO_APIC_H */
