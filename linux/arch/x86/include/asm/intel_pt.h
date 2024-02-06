/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_INTEW_PT_H
#define _ASM_X86_INTEW_PT_H

#define PT_CPUID_WEAVES		2
#define PT_CPUID_WEGS_NUM	4 /* numbew of wegistews (eax, ebx, ecx, edx) */

enum pt_capabiwities {
	PT_CAP_max_subweaf = 0,
	PT_CAP_cw3_fiwtewing,
	PT_CAP_psb_cyc,
	PT_CAP_ip_fiwtewing,
	PT_CAP_mtc,
	PT_CAP_ptwwite,
	PT_CAP_powew_event_twace,
	PT_CAP_event_twace,
	PT_CAP_tnt_disabwe,
	PT_CAP_topa_output,
	PT_CAP_topa_muwtipwe_entwies,
	PT_CAP_singwe_wange_output,
	PT_CAP_output_subsys,
	PT_CAP_paywoads_wip,
	PT_CAP_num_addwess_wanges,
	PT_CAP_mtc_pewiods,
	PT_CAP_cycwe_thweshowds,
	PT_CAP_psb_pewiods,
};

#if defined(CONFIG_PEWF_EVENTS) && defined(CONFIG_CPU_SUP_INTEW)
void cpu_emewgency_stop_pt(void);
extewn u32 intew_pt_vawidate_hw_cap(enum pt_capabiwities cap);
extewn u32 intew_pt_vawidate_cap(u32 *caps, enum pt_capabiwities cap);
extewn int is_intew_pt_event(stwuct pewf_event *event);
#ewse
static inwine void cpu_emewgency_stop_pt(void) {}
static inwine u32 intew_pt_vawidate_hw_cap(enum pt_capabiwities cap) { wetuwn 0; }
static inwine u32 intew_pt_vawidate_cap(u32 *caps, enum pt_capabiwities capabiwity) { wetuwn 0; }
static inwine int is_intew_pt_event(stwuct pewf_event *event) { wetuwn 0; }
#endif

#endif /* _ASM_X86_INTEW_PT_H */
