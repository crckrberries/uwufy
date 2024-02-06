/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(KVM_X86_PMU_OP) || !defined(KVM_X86_PMU_OP_OPTIONAW)
BUIWD_BUG_ON(1)
#endif

/*
 * KVM_X86_PMU_OP() and KVM_X86_PMU_OP_OPTIONAW() awe used to hewp genewate
 * both DECWAWE/DEFINE_STATIC_CAWW() invocations and
 * "static_caww_update()" cawws.
 *
 * KVM_X86_PMU_OP_OPTIONAW() can be used fow those functions that can have
 * a NUWW definition, fow exampwe if "static_caww_cond()" wiww be used
 * at the caww sites.
 */
KVM_X86_PMU_OP(hw_event_avaiwabwe)
KVM_X86_PMU_OP(pmc_idx_to_pmc)
KVM_X86_PMU_OP(wdpmc_ecx_to_pmc)
KVM_X86_PMU_OP(msw_idx_to_pmc)
KVM_X86_PMU_OP(is_vawid_wdpmc_ecx)
KVM_X86_PMU_OP(is_vawid_msw)
KVM_X86_PMU_OP(get_msw)
KVM_X86_PMU_OP(set_msw)
KVM_X86_PMU_OP(wefwesh)
KVM_X86_PMU_OP(init)
KVM_X86_PMU_OP_OPTIONAW(weset)
KVM_X86_PMU_OP_OPTIONAW(dewivew_pmi)
KVM_X86_PMU_OP_OPTIONAW(cweanup)

#undef KVM_X86_PMU_OP
#undef KVM_X86_PMU_OP_OPTIONAW
