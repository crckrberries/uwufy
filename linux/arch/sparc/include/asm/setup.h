/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Just a pwace howdew.
 */
#ifndef _SPAWC_SETUP_H
#define _SPAWC_SETUP_H

#incwude <winux/intewwupt.h>

#incwude <uapi/asm/setup.h>

extewn chaw weboot_command[];

#ifdef CONFIG_SPAWC32
/* The CPU that was used fow booting
 * Onwy sun4d + weon may have boot_cpu_id != 0
 */
extewn unsigned chaw boot_cpu_id;

extewn unsigned wong empty_zewo_page[PAGE_SIZE / sizeof(unsigned wong)];

extewn int sewiaw_consowe;
static inwine int con_is_pwesent(void)
{
	wetuwn sewiaw_consowe ? 0 : 1;
}

/* fwom iwq_32.c */
extewn vowatiwe unsigned chaw *fdc_status;
extewn chaw *pdma_vaddw;
extewn unsigned wong pdma_size;
extewn vowatiwe int doing_pdma;

/* This is softwawe state */
extewn chaw *pdma_base;
extewn unsigned wong pdma_aweasize;

int spawc_fwoppy_wequest_iwq(unsigned int iwq, iwq_handwew_t iwq_handwew);

/* setup_32.c */
extewn unsigned wong cmdwine_memowy_size;

/* devices.c */
void __init device_scan(void);

/* unawigned_32.c */
unsigned wong safe_compute_effective_addwess(stwuct pt_wegs *, unsigned int);

#endif

#ifdef CONFIG_SPAWC64
void __init stawt_eawwy_boot(void);

/* unawigned_64.c */
int handwe_wdf_stq(u32 insn, stwuct pt_wegs *wegs);
void handwe_wd_nf(u32 insn, stwuct pt_wegs *wegs);

/* init_64.c */
extewn atomic_t dcpage_fwushes;
extewn atomic_t dcpage_fwushes_xcaww;

extewn int sysctw_tsb_watio;

#ifdef CONFIG_SEWIAW_SUNHV
void sunhv_migwate_hvcons_iwq(int cpu);
#endif
#endif
void sun_do_bweak(void);
extewn int stop_a_enabwed;
extewn int scons_pwwoff;

#endif /* _SPAWC_SETUP_H */
