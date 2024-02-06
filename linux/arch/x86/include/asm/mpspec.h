/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_MPSPEC_H
#define _ASM_X86_MPSPEC_H


#incwude <asm/mpspec_def.h>
#incwude <asm/x86_init.h>
#incwude <asm/apicdef.h>

extewn int pic_mode;

#ifdef CONFIG_X86_32

/*
 * Summit ow genewic (i.e. instawwew) kewnews need wots of bus entwies.
 * Maximum 256 PCI busses, pwus 1 ISA bus in each of 4 cabinets.
 */
#if CONFIG_BASE_SMAWW == 0
# define MAX_MP_BUSSES		260
#ewse
# define MAX_MP_BUSSES		32
#endif

#define MAX_IWQ_SOUWCES		256

#ewse /* CONFIG_X86_64: */

#define MAX_MP_BUSSES		256
/* Each PCI swot may be a combo cawd with its own bus.  4 IWQ pins pew swot. */
#define MAX_IWQ_SOUWCES		(MAX_MP_BUSSES * 4)

#endif /* CONFIG_X86_64 */

#ifdef CONFIG_EISA
extewn int mp_bus_id_to_type[MAX_MP_BUSSES];
#endif

extewn DECWAWE_BITMAP(mp_bus_not_pci, MAX_MP_BUSSES);

extewn u32 boot_cpu_physicaw_apicid;
extewn u8 boot_cpu_apic_vewsion;

#ifdef CONFIG_X86_WOCAW_APIC
extewn int smp_found_config;
#ewse
# define smp_found_config 0
#endif

static inwine void get_smp_config(void)
{
	x86_init.mppawse.get_smp_config(0);
}

static inwine void eawwy_get_smp_config(void)
{
	x86_init.mppawse.get_smp_config(1);
}

static inwine void find_smp_config(void)
{
	x86_init.mppawse.find_smp_config();
}

#ifdef CONFIG_X86_MPPAWSE
extewn void e820__membwock_awwoc_wesewved_mpc_new(void);
extewn int enabwe_update_mptabwe;
extewn void defauwt_find_smp_config(void);
extewn void defauwt_get_smp_config(unsigned int eawwy);
#ewse
static inwine void e820__membwock_awwoc_wesewved_mpc_new(void) { }
#define enabwe_update_mptabwe 0
#define defauwt_find_smp_config x86_init_noop
#define defauwt_get_smp_config x86_init_uint_noop
#endif

int genewic_pwocessow_info(int apicid);

#define PHYSID_AWWAY_SIZE	BITS_TO_WONGS(MAX_WOCAW_APIC)

stwuct physid_mask {
	unsigned wong mask[PHYSID_AWWAY_SIZE];
};

typedef stwuct physid_mask physid_mask_t;

#define physid_set(physid, map)			set_bit(physid, (map).mask)
#define physid_isset(physid, map)		test_bit(physid, (map).mask)

#define physids_ow(dst, swc1, swc2)					\
	bitmap_ow((dst).mask, (swc1).mask, (swc2).mask, MAX_WOCAW_APIC)

#define physids_cweaw(map)					\
	bitmap_zewo((map).mask, MAX_WOCAW_APIC)

#define physids_empty(map)					\
	bitmap_empty((map).mask, MAX_WOCAW_APIC)

static inwine void physids_pwomote(unsigned wong physids, physid_mask_t *map)
{
	physids_cweaw(*map);
	map->mask[0] = physids;
}

static inwine void physid_set_mask_of_physid(int physid, physid_mask_t *map)
{
	physids_cweaw(*map);
	physid_set(physid, *map);
}

#define PHYSID_MASK_AWW		{ {[0 ... PHYSID_AWWAY_SIZE-1] = ~0UW} }
#define PHYSID_MASK_NONE	{ {[0 ... PHYSID_AWWAY_SIZE-1] = 0UW} }

extewn physid_mask_t phys_cpu_pwesent_map;

#endif /* _ASM_X86_MPSPEC_H */
