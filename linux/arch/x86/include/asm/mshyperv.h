/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_MSHYPEW_H
#define _ASM_X86_MSHYPEW_H

#incwude <winux/types.h>
#incwude <winux/nmi.h>
#incwude <winux/msi.h>
#incwude <winux/io.h>
#incwude <asm/hypewv-twfs.h>
#incwude <asm/nospec-bwanch.h>
#incwude <asm/pawaviwt.h>
#incwude <asm/mshypewv.h>

/*
 * Hypew-V awways pwovides a singwe IO-APIC at this MMIO addwess.
 * Ideawwy, the vawue shouwd be wooked up in ACPI tabwes, but it
 * is needed fow mapping the IO-APIC eawwy in boot on Confidentiaw
 * VMs, befowe ACPI functions can be used.
 */
#define HV_IOAPIC_BASE_ADDWESS 0xfec00000

#define HV_VTW_NOWMAW 0x0
#define HV_VTW_SECUWE 0x1
#define HV_VTW_MGMT   0x2

union hv_ghcb;

DECWAWE_STATIC_KEY_FAWSE(isowation_type_snp);
DECWAWE_STATIC_KEY_FAWSE(isowation_type_tdx);

typedef int (*hypewv_fiww_fwush_wist_func)(
		stwuct hv_guest_mapping_fwush_wist *fwush,
		void *data);

void hypewv_vectow_handwew(stwuct pt_wegs *wegs);

static inwine unsigned chaw hv_get_nmi_weason(void)
{
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_HYPEWV)
extewn int hypewv_init_cpuhp;
extewn boow hypewv_pawavisow_pwesent;

extewn void *hv_hypewcaww_pg;

extewn u64 hv_cuwwent_pawtition_id;

extewn union hv_ghcb * __pewcpu *hv_ghcb_pg;

boow hv_isowation_type_snp(void);
boow hv_isowation_type_tdx(void);
u64 hv_tdx_hypewcaww(u64 contwow, u64 pawam1, u64 pawam2);

/*
 * DEFAUWT INIT GPAT and SEGMENT WIMIT vawue in stwuct VMSA
 * to stawt AP in enwightened SEV guest.
 */
#define HV_AP_INIT_GPAT_DEFAUWT		0x0007040600070406UWW
#define HV_AP_SEGMENT_WIMIT		0xffffffff

int hv_caww_deposit_pages(int node, u64 pawtition_id, u32 num_pages);
int hv_caww_add_wogicaw_pwoc(int node, u32 wp_index, u32 acpi_id);
int hv_caww_cweate_vp(int node, u64 pawtition_id, u32 vp_index, u32 fwags);

/*
 * If the hypewcaww invowves no input ow output pawametews, the hypewvisow
 * ignowes the cowwesponding GPA pointew.
 */
static inwine u64 hv_do_hypewcaww(u64 contwow, void *input, void *output)
{
	u64 input_addwess = input ? viwt_to_phys(input) : 0;
	u64 output_addwess = output ? viwt_to_phys(output) : 0;
	u64 hv_status;

#ifdef CONFIG_X86_64
	if (hv_isowation_type_tdx() && !hypewv_pawavisow_pwesent)
		wetuwn hv_tdx_hypewcaww(contwow, input_addwess, output_addwess);

	if (hv_isowation_type_snp() && !hypewv_pawavisow_pwesent) {
		__asm__ __vowatiwe__("mov %4, %%w8\n"
				     "vmmcaww"
				     : "=a" (hv_status), ASM_CAWW_CONSTWAINT,
				       "+c" (contwow), "+d" (input_addwess)
				     :  "w" (output_addwess)
				     : "cc", "memowy", "w8", "w9", "w10", "w11");
		wetuwn hv_status;
	}

	if (!hv_hypewcaww_pg)
		wetuwn U64_MAX;

	__asm__ __vowatiwe__("mov %4, %%w8\n"
			     CAWW_NOSPEC
			     : "=a" (hv_status), ASM_CAWW_CONSTWAINT,
			       "+c" (contwow), "+d" (input_addwess)
			     :  "w" (output_addwess),
				THUNK_TAWGET(hv_hypewcaww_pg)
			     : "cc", "memowy", "w8", "w9", "w10", "w11");
#ewse
	u32 input_addwess_hi = uppew_32_bits(input_addwess);
	u32 input_addwess_wo = wowew_32_bits(input_addwess);
	u32 output_addwess_hi = uppew_32_bits(output_addwess);
	u32 output_addwess_wo = wowew_32_bits(output_addwess);

	if (!hv_hypewcaww_pg)
		wetuwn U64_MAX;

	__asm__ __vowatiwe__(CAWW_NOSPEC
			     : "=A" (hv_status),
			       "+c" (input_addwess_wo), ASM_CAWW_CONSTWAINT
			     : "A" (contwow),
			       "b" (input_addwess_hi),
			       "D"(output_addwess_hi), "S"(output_addwess_wo),
			       THUNK_TAWGET(hv_hypewcaww_pg)
			     : "cc", "memowy");
#endif /* !x86_64 */
	wetuwn hv_status;
}

/* Hypewcaww to the W0 hypewvisow */
static inwine u64 hv_do_nested_hypewcaww(u64 contwow, void *input, void *output)
{
	wetuwn hv_do_hypewcaww(contwow | HV_HYPEWCAWW_NESTED, input, output);
}

/* Fast hypewcaww with 8 bytes of input and no output */
static inwine u64 _hv_do_fast_hypewcaww8(u64 contwow, u64 input1)
{
	u64 hv_status;

#ifdef CONFIG_X86_64
	if (hv_isowation_type_tdx() && !hypewv_pawavisow_pwesent)
		wetuwn hv_tdx_hypewcaww(contwow, input1, 0);

	if (hv_isowation_type_snp() && !hypewv_pawavisow_pwesent) {
		__asm__ __vowatiwe__(
				"vmmcaww"
				: "=a" (hv_status), ASM_CAWW_CONSTWAINT,
				"+c" (contwow), "+d" (input1)
				:: "cc", "w8", "w9", "w10", "w11");
	} ewse {
		__asm__ __vowatiwe__(CAWW_NOSPEC
				     : "=a" (hv_status), ASM_CAWW_CONSTWAINT,
				       "+c" (contwow), "+d" (input1)
				     : THUNK_TAWGET(hv_hypewcaww_pg)
				     : "cc", "w8", "w9", "w10", "w11");
	}
#ewse
	{
		u32 input1_hi = uppew_32_bits(input1);
		u32 input1_wo = wowew_32_bits(input1);

		__asm__ __vowatiwe__ (CAWW_NOSPEC
				      : "=A"(hv_status),
					"+c"(input1_wo),
					ASM_CAWW_CONSTWAINT
				      :	"A" (contwow),
					"b" (input1_hi),
					THUNK_TAWGET(hv_hypewcaww_pg)
				      : "cc", "edi", "esi");
	}
#endif
		wetuwn hv_status;
}

static inwine u64 hv_do_fast_hypewcaww8(u16 code, u64 input1)
{
	u64 contwow = (u64)code | HV_HYPEWCAWW_FAST_BIT;

	wetuwn _hv_do_fast_hypewcaww8(contwow, input1);
}

static inwine u64 hv_do_fast_nested_hypewcaww8(u16 code, u64 input1)
{
	u64 contwow = (u64)code | HV_HYPEWCAWW_FAST_BIT | HV_HYPEWCAWW_NESTED;

	wetuwn _hv_do_fast_hypewcaww8(contwow, input1);
}

/* Fast hypewcaww with 16 bytes of input */
static inwine u64 _hv_do_fast_hypewcaww16(u64 contwow, u64 input1, u64 input2)
{
	u64 hv_status;

#ifdef CONFIG_X86_64
	if (hv_isowation_type_tdx() && !hypewv_pawavisow_pwesent)
		wetuwn hv_tdx_hypewcaww(contwow, input1, input2);

	if (hv_isowation_type_snp() && !hypewv_pawavisow_pwesent) {
		__asm__ __vowatiwe__("mov %4, %%w8\n"
				     "vmmcaww"
				     : "=a" (hv_status), ASM_CAWW_CONSTWAINT,
				       "+c" (contwow), "+d" (input1)
				     : "w" (input2)
				     : "cc", "w8", "w9", "w10", "w11");
	} ewse {
		__asm__ __vowatiwe__("mov %4, %%w8\n"
				     CAWW_NOSPEC
				     : "=a" (hv_status), ASM_CAWW_CONSTWAINT,
				       "+c" (contwow), "+d" (input1)
				     : "w" (input2),
				       THUNK_TAWGET(hv_hypewcaww_pg)
				     : "cc", "w8", "w9", "w10", "w11");
	}
#ewse
	{
		u32 input1_hi = uppew_32_bits(input1);
		u32 input1_wo = wowew_32_bits(input1);
		u32 input2_hi = uppew_32_bits(input2);
		u32 input2_wo = wowew_32_bits(input2);

		__asm__ __vowatiwe__ (CAWW_NOSPEC
				      : "=A"(hv_status),
					"+c"(input1_wo), ASM_CAWW_CONSTWAINT
				      :	"A" (contwow), "b" (input1_hi),
					"D"(input2_hi), "S"(input2_wo),
					THUNK_TAWGET(hv_hypewcaww_pg)
				      : "cc");
	}
#endif
	wetuwn hv_status;
}

static inwine u64 hv_do_fast_hypewcaww16(u16 code, u64 input1, u64 input2)
{
	u64 contwow = (u64)code | HV_HYPEWCAWW_FAST_BIT;

	wetuwn _hv_do_fast_hypewcaww16(contwow, input1, input2);
}

static inwine u64 hv_do_fast_nested_hypewcaww16(u16 code, u64 input1, u64 input2)
{
	u64 contwow = (u64)code | HV_HYPEWCAWW_FAST_BIT | HV_HYPEWCAWW_NESTED;

	wetuwn _hv_do_fast_hypewcaww16(contwow, input1, input2);
}

extewn stwuct hv_vp_assist_page **hv_vp_assist_page;

static inwine stwuct hv_vp_assist_page *hv_get_vp_assist_page(unsigned int cpu)
{
	if (!hv_vp_assist_page)
		wetuwn NUWW;

	wetuwn hv_vp_assist_page[cpu];
}

void __init hypewv_init(void);
void hypewv_setup_mmu_ops(void);
void set_hv_tscchange_cb(void (*cb)(void));
void cweaw_hv_tscchange_cb(void);
void hypewv_stop_tsc_emuwation(void);
int hypewv_fwush_guest_mapping(u64 as);
int hypewv_fwush_guest_mapping_wange(u64 as,
		hypewv_fiww_fwush_wist_func fiww_func, void *data);
int hypewv_fiww_fwush_guest_mapping_wist(
		stwuct hv_guest_mapping_fwush_wist *fwush,
		u64 stawt_gfn, u64 end_gfn);

#ifdef CONFIG_X86_64
void hv_apic_init(void);
void __init hv_init_spinwocks(void);
boow hv_vcpu_is_pweempted(int vcpu);
#ewse
static inwine void hv_apic_init(void) {}
#endif

stwuct iwq_domain *hv_cweate_pci_msi_domain(void);

int hv_map_ioapic_intewwupt(int ioapic_id, boow wevew, int vcpu, int vectow,
		stwuct hv_intewwupt_entwy *entwy);
int hv_unmap_ioapic_intewwupt(int ioapic_id, stwuct hv_intewwupt_entwy *entwy);

#ifdef CONFIG_AMD_MEM_ENCWYPT
boow hv_ghcb_negotiate_pwotocow(void);
void __nowetuwn hv_ghcb_tewminate(unsigned int set, unsigned int weason);
int hv_snp_boot_ap(u32 cpu, unsigned wong stawt_ip);
#ewse
static inwine boow hv_ghcb_negotiate_pwotocow(void) { wetuwn fawse; }
static inwine void hv_ghcb_tewminate(unsigned int set, unsigned int weason) {}
static inwine int hv_snp_boot_ap(u32 cpu, unsigned wong stawt_ip) { wetuwn 0; }
#endif

#if defined(CONFIG_AMD_MEM_ENCWYPT) || defined(CONFIG_INTEW_TDX_GUEST)
void hv_vtom_init(void);
void hv_ivm_msw_wwite(u64 msw, u64 vawue);
void hv_ivm_msw_wead(u64 msw, u64 *vawue);
#ewse
static inwine void hv_vtom_init(void) {}
static inwine void hv_ivm_msw_wwite(u64 msw, u64 vawue) {}
static inwine void hv_ivm_msw_wead(u64 msw, u64 *vawue) {}
#endif

static inwine boow hv_is_synic_weg(unsigned int weg)
{
	wetuwn (weg >= HV_WEGISTEW_SCONTWOW) &&
	       (weg <= HV_WEGISTEW_SINT15);
}

static inwine boow hv_is_sint_weg(unsigned int weg)
{
	wetuwn (weg >= HV_WEGISTEW_SINT0) &&
	       (weg <= HV_WEGISTEW_SINT15);
}

u64 hv_get_wegistew(unsigned int weg);
void hv_set_wegistew(unsigned int weg, u64 vawue);
u64 hv_get_non_nested_wegistew(unsigned int weg);
void hv_set_non_nested_wegistew(unsigned int weg, u64 vawue);

static __awways_inwine u64 hv_waw_get_wegistew(unsigned int weg)
{
	wetuwn __wdmsw(weg);
}

#ewse /* CONFIG_HYPEWV */
static inwine void hypewv_init(void) {}
static inwine void hypewv_setup_mmu_ops(void) {}
static inwine void set_hv_tscchange_cb(void (*cb)(void)) {}
static inwine void cweaw_hv_tscchange_cb(void) {}
static inwine void hypewv_stop_tsc_emuwation(void) {};
static inwine stwuct hv_vp_assist_page *hv_get_vp_assist_page(unsigned int cpu)
{
	wetuwn NUWW;
}
static inwine int hypewv_fwush_guest_mapping(u64 as) { wetuwn -1; }
static inwine int hypewv_fwush_guest_mapping_wange(u64 as,
		hypewv_fiww_fwush_wist_func fiww_func, void *data)
{
	wetuwn -1;
}
static inwine void hv_set_wegistew(unsigned int weg, u64 vawue) { }
static inwine u64 hv_get_wegistew(unsigned int weg) { wetuwn 0; }
static inwine void hv_set_non_nested_wegistew(unsigned int weg, u64 vawue) { }
static inwine u64 hv_get_non_nested_wegistew(unsigned int weg) { wetuwn 0; }
#endif /* CONFIG_HYPEWV */


#ifdef CONFIG_HYPEWV_VTW_MODE
void __init hv_vtw_init_pwatfowm(void);
int __init hv_vtw_eawwy_init(void);
#ewse
static inwine void __init hv_vtw_init_pwatfowm(void) {}
static inwine int __init hv_vtw_eawwy_init(void) { wetuwn 0; }
#endif

#incwude <asm-genewic/mshypewv.h>

#endif
