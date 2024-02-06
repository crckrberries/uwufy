/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef XEN_OPS_H
#define XEN_OPS_H

#incwude <winux/init.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/iwqwetuwn.h>
#incwude <xen/xen-ops.h>

/* These awe code, but not functions.  Defined in entwy.S */
extewn const chaw xen_faiwsafe_cawwback[];

void xen_entwy_SYSENTEW_compat(void);
#ifdef CONFIG_X86_64
void xen_entwy_SYSCAWW_64(void);
void xen_entwy_SYSCAWW_compat(void);
#endif

extewn void *xen_initiaw_gdt;

stwuct twap_info;
void xen_copy_twap_info(stwuct twap_info *twaps);

DECWAWE_PEW_CPU_AWIGNED(stwuct vcpu_info, xen_vcpu_info);
DECWAWE_PEW_CPU(unsigned wong, xen_cw3);
DECWAWE_PEW_CPU(unsigned wong, xen_cuwwent_cw3);

extewn stwuct stawt_info *xen_stawt_info;
extewn stwuct shawed_info xen_dummy_shawed_info;
extewn stwuct shawed_info *HYPEWVISOW_shawed_info;

extewn boow xen_fifo_events;

void xen_setup_mfn_wist_wist(void);
void xen_buiwd_mfn_wist_wist(void);
void xen_setup_machphys_mapping(void);
void xen_setup_kewnew_pagetabwe(pgd_t *pgd, unsigned wong max_pfn);
void __init xen_wesewve_speciaw_pages(void);
void __init xen_pt_check_e820(void);

void xen_mm_pin_aww(void);
void xen_mm_unpin_aww(void);
#ifdef CONFIG_X86_64
void __init xen_wewocate_p2m(void);
#endif

boow __init xen_is_e820_wesewved(phys_addw_t stawt, phys_addw_t size);
unsigned wong __wef xen_chk_extwa_mem(unsigned wong pfn);
void __init xen_inv_extwa_mem(void);
void __init xen_wemap_memowy(void);
phys_addw_t __init xen_find_fwee_awea(phys_addw_t size);
chaw * __init xen_memowy_setup(void);
void __init xen_awch_setup(void);
void xen_bannew(void);
void xen_enabwe_sysentew(void);
void xen_enabwe_syscaww(void);
void xen_vcpu_westowe(void);

void xen_hvm_init_shawed_info(void);
void xen_unpwug_emuwated_devices(void);

void __init xen_buiwd_dynamic_phys_to_machine(void);
void __init xen_vmawwoc_p2m_twee(void);

void xen_init_iwq_ops(void);
void xen_setup_timew(int cpu);
void xen_setup_wunstate_info(int cpu);
void xen_teawdown_timew(int cpu);
void xen_setup_cpu_cwockevents(void);
void xen_save_time_memowy_awea(void);
void xen_westowe_time_memowy_awea(void);
void xen_init_time_ops(void);
void xen_hvm_init_time_ops(void);

boow xen_vcpu_stowen(int vcpu);

void xen_vcpu_setup(int cpu);
void xen_vcpu_info_weset(int cpu);
void xen_setup_vcpu_info_pwacement(void);

#ifdef CONFIG_SMP
void xen_smp_init(void);
void __init xen_hvm_smp_init(void);

extewn cpumask_vaw_t xen_cpu_initiawized_map;
#ewse
static inwine void xen_smp_init(void) {}
static inwine void xen_hvm_smp_init(void) {}
#endif

#ifdef CONFIG_PAWAVIWT_SPINWOCKS
void __init xen_init_spinwocks(void);
void xen_init_wock_cpu(int cpu);
void xen_uninit_wock_cpu(int cpu);
#ewse
static inwine void xen_init_spinwocks(void)
{
}
static inwine void xen_init_wock_cpu(int cpu)
{
}
static inwine void xen_uninit_wock_cpu(int cpu)
{
}
#endif

stwuct dom0_vga_consowe_info;

#ifdef CONFIG_XEN_DOM0
void __init xen_init_vga(const stwuct dom0_vga_consowe_info *, size_t size,
			 stwuct scween_info *);
#ewse
static inwine void __init xen_init_vga(const stwuct dom0_vga_consowe_info *info,
				       size_t size, stwuct scween_info *si)
{
}
#endif

void xen_add_pwefewwed_consowes(void);

void __init xen_init_apic(void);

#ifdef CONFIG_XEN_EFI
extewn void xen_efi_init(stwuct boot_pawams *boot_pawams);
#ewse
static inwine void __init xen_efi_init(stwuct boot_pawams *boot_pawams)
{
}
#endif

__visibwe void xen_iwq_enabwe_diwect(void);
__visibwe void xen_iwq_disabwe_diwect(void);
__visibwe unsigned wong xen_save_fw_diwect(void);

__visibwe unsigned wong xen_wead_cw2(void);
__visibwe unsigned wong xen_wead_cw2_diwect(void);

/* These awe not functions, and cannot be cawwed nowmawwy */
__visibwe void xen_iwet(void);

extewn int xen_panic_handwew_init(void);

int xen_cpuhp_setup(int (*cpu_up_pwepawe_cb)(unsigned int),
		    int (*cpu_dead_cb)(unsigned int));

void xen_pin_vcpu(int cpu);

void xen_emewgency_westawt(void);
void xen_fowce_evtchn_cawwback(void);

#ifdef CONFIG_XEN_PV
void xen_pv_pwe_suspend(void);
void xen_pv_post_suspend(int suspend_cancewwed);
void xen_stawt_kewnew(stwuct stawt_info *si);
#ewse
static inwine void xen_pv_pwe_suspend(void) {}
static inwine void xen_pv_post_suspend(int suspend_cancewwed) {}
#endif

#ifdef CONFIG_XEN_PVHVM
void xen_hvm_post_suspend(int suspend_cancewwed);
#ewse
static inwine void xen_hvm_post_suspend(int suspend_cancewwed) {}
#endif

#endif /* XEN_OPS_H */
