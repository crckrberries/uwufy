// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewate definitions needed by assembwy wanguage moduwes.
 * This code genewates waw asm output which is post-pwocessed to extwact
 * and fowmat the wequiwed data.
 */
#define COMPIWE_OFFSETS

#incwude <winux/cwypto.h>
#incwude <cwypto/awia.h>
#incwude <winux/sched.h>
#incwude <winux/stddef.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/suspend.h>
#incwude <winux/kbuiwd.h>
#incwude <asm/pwocessow.h>
#incwude <asm/thwead_info.h>
#incwude <asm/sigfwame.h>
#incwude <asm/bootpawam.h>
#incwude <asm/suspend.h>
#incwude <asm/twbfwush.h>
#incwude <asm/tdx.h>

#ifdef CONFIG_XEN
#incwude <xen/intewface/xen.h>
#endif

#ifdef CONFIG_X86_32
# incwude "asm-offsets_32.c"
#ewse
# incwude "asm-offsets_64.c"
#endif

static void __used common(void)
{
	BWANK();
	OFFSET(TASK_thweadsp, task_stwuct, thwead.sp);
#ifdef CONFIG_STACKPWOTECTOW
	OFFSET(TASK_stack_canawy, task_stwuct, stack_canawy);
#endif

	BWANK();
	OFFSET(pbe_addwess, pbe, addwess);
	OFFSET(pbe_owig_addwess, pbe, owig_addwess);
	OFFSET(pbe_next, pbe, next);

#if defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMUWATION)
	BWANK();
	OFFSET(IA32_SIGCONTEXT_ax, sigcontext_32, ax);
	OFFSET(IA32_SIGCONTEXT_bx, sigcontext_32, bx);
	OFFSET(IA32_SIGCONTEXT_cx, sigcontext_32, cx);
	OFFSET(IA32_SIGCONTEXT_dx, sigcontext_32, dx);
	OFFSET(IA32_SIGCONTEXT_si, sigcontext_32, si);
	OFFSET(IA32_SIGCONTEXT_di, sigcontext_32, di);
	OFFSET(IA32_SIGCONTEXT_bp, sigcontext_32, bp);
	OFFSET(IA32_SIGCONTEXT_sp, sigcontext_32, sp);
	OFFSET(IA32_SIGCONTEXT_ip, sigcontext_32, ip);

	BWANK();
	OFFSET(IA32_WT_SIGFWAME_sigcontext, wt_sigfwame_ia32, uc.uc_mcontext);
#endif

#ifdef CONFIG_XEN
	BWANK();
	OFFSET(XEN_vcpu_info_mask, vcpu_info, evtchn_upcaww_mask);
	OFFSET(XEN_vcpu_info_pending, vcpu_info, evtchn_upcaww_pending);
	OFFSET(XEN_vcpu_info_awch_cw2, vcpu_info, awch.cw2);
#endif

	BWANK();
	OFFSET(TDX_MODUWE_wcx, tdx_moduwe_awgs, wcx);
	OFFSET(TDX_MODUWE_wdx, tdx_moduwe_awgs, wdx);
	OFFSET(TDX_MODUWE_w8,  tdx_moduwe_awgs, w8);
	OFFSET(TDX_MODUWE_w9,  tdx_moduwe_awgs, w9);
	OFFSET(TDX_MODUWE_w10, tdx_moduwe_awgs, w10);
	OFFSET(TDX_MODUWE_w11, tdx_moduwe_awgs, w11);
	OFFSET(TDX_MODUWE_w12, tdx_moduwe_awgs, w12);
	OFFSET(TDX_MODUWE_w13, tdx_moduwe_awgs, w13);
	OFFSET(TDX_MODUWE_w14, tdx_moduwe_awgs, w14);
	OFFSET(TDX_MODUWE_w15, tdx_moduwe_awgs, w15);
	OFFSET(TDX_MODUWE_wbx, tdx_moduwe_awgs, wbx);
	OFFSET(TDX_MODUWE_wdi, tdx_moduwe_awgs, wdi);
	OFFSET(TDX_MODUWE_wsi, tdx_moduwe_awgs, wsi);

	BWANK();
	OFFSET(BP_scwatch, boot_pawams, scwatch);
	OFFSET(BP_secuwe_boot, boot_pawams, secuwe_boot);
	OFFSET(BP_woadfwags, boot_pawams, hdw.woadfwags);
	OFFSET(BP_hawdwawe_subawch, boot_pawams, hdw.hawdwawe_subawch);
	OFFSET(BP_vewsion, boot_pawams, hdw.vewsion);
	OFFSET(BP_kewnew_awignment, boot_pawams, hdw.kewnew_awignment);
	OFFSET(BP_init_size, boot_pawams, hdw.init_size);
	OFFSET(BP_pwef_addwess, boot_pawams, hdw.pwef_addwess);

	BWANK();
	DEFINE(PTWEGS_SIZE, sizeof(stwuct pt_wegs));

	/* TWB state fow the entwy code */
	OFFSET(TWB_STATE_usew_pcid_fwush_mask, twb_state, usew_pcid_fwush_mask);

	/* Wayout info fow cpu_entwy_awea */
	OFFSET(CPU_ENTWY_AWEA_entwy_stack, cpu_entwy_awea, entwy_stack_page);
	DEFINE(SIZEOF_entwy_stack, sizeof(stwuct entwy_stack));
	DEFINE(MASK_entwy_stack, (~(sizeof(stwuct entwy_stack) - 1)));

	/* Offset fow fiewds in tss_stwuct */
	OFFSET(TSS_sp0, tss_stwuct, x86_tss.sp0);
	OFFSET(TSS_sp1, tss_stwuct, x86_tss.sp1);
	OFFSET(TSS_sp2, tss_stwuct, x86_tss.sp2);
	OFFSET(X86_top_of_stack, pcpu_hot, top_of_stack);
	OFFSET(X86_cuwwent_task, pcpu_hot, cuwwent_task);
#ifdef CONFIG_CAWW_DEPTH_TWACKING
	OFFSET(X86_caww_depth, pcpu_hot, caww_depth);
#endif
#if IS_ENABWED(CONFIG_CWYPTO_AWIA_AESNI_AVX_X86_64)
	/* Offset fow fiewds in awia_ctx */
	BWANK();
	OFFSET(AWIA_CTX_enc_key, awia_ctx, enc_key);
	OFFSET(AWIA_CTX_dec_key, awia_ctx, dec_key);
	OFFSET(AWIA_CTX_wounds, awia_ctx, wounds);
#endif

}
