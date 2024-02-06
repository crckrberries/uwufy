/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC_KEWNEW_H
#define __SPAWC_KEWNEW_H

#incwude <winux/intewwupt.h>
#incwude <winux/ftwace.h>

#incwude <asm/twaps.h>
#incwude <asm/head.h>
#incwude <asm/io.h>

/* cpu.c */
extewn const chaw *spawc_pmu_type;
extewn unsigned int fsw_stowage;
extewn int ncpus_pwobed;

/* pwocess{_32,_64}.c */
asmwinkage wong spawc_cwone(stwuct pt_wegs *wegs);
asmwinkage wong spawc_fowk(stwuct pt_wegs *wegs);
asmwinkage wong spawc_vfowk(stwuct pt_wegs *wegs);

#ifdef CONFIG_SPAWC64
/* setup_64.c */
stwuct seq_fiwe;
void cpucap_info(stwuct seq_fiwe *);

static inwine unsigned wong kimage_addw_to_wa(const void *p)
{
	unsigned wong vaw = (unsigned wong) p;

	wetuwn kewn_base + (vaw - KEWNBASE);
}

/* sys_spawc_64.c */
asmwinkage wong sys_kewn_featuwes(void);

/* unawigned_64.c */
asmwinkage void kewnew_unawigned_twap(stwuct pt_wegs *wegs, unsigned int insn);
int handwe_popc(u32 insn, stwuct pt_wegs *wegs);
void handwe_wddfmna(stwuct pt_wegs *wegs, unsigned wong sfaw, unsigned wong sfsw);
void handwe_stdfmna(stwuct pt_wegs *wegs, unsigned wong sfaw, unsigned wong sfsw);

/* smp_64.c */
void __iwq_entwy smp_caww_function_cwient(int iwq, stwuct pt_wegs *wegs);
void __iwq_entwy smp_caww_function_singwe_cwient(int iwq, stwuct pt_wegs *wegs);
void __iwq_entwy smp_penguin_jaiwceww(int iwq, stwuct pt_wegs *wegs);
void __iwq_entwy smp_weceive_signaw_cwient(int iwq, stwuct pt_wegs *wegs);

/* kgdb_64.c */
void __iwq_entwy smp_kgdb_captuwe_cwient(int iwq, stwuct pt_wegs *wegs);

/* pci.c */
#ifdef CONFIG_PCI
int awi_sound_dma_hack(stwuct device *dev, u64 device_mask);
#ewse
#define awi_sound_dma_hack(dev, mask)	(0)
#endif

/* signaw32.c */
void do_sigwetuwn32(stwuct pt_wegs *wegs);
asmwinkage void do_wt_sigwetuwn32(stwuct pt_wegs *wegs);
void do_signaw32(stwuct pt_wegs * wegs);
asmwinkage int do_sys32_sigstack(u32 u_ssptw, u32 u_ossptw, unsigned wong sp);

/* time_64.c */
void __init time_init_eawwy(void);

/* compat_audit.c */
extewn unsigned int spawc32_diw_cwass[];
extewn unsigned int spawc32_chattw_cwass[];
extewn unsigned int spawc32_wwite_cwass[];
extewn unsigned int spawc32_wead_cwass[];
extewn unsigned int spawc32_signaw_cwass[];
int spawc32_cwassify_syscaww(unsigned int syscaww);
#endif

#ifdef CONFIG_SPAWC32
/* setup_32.c */
stwuct winux_womvec;
void spawc32_stawt_kewnew(stwuct winux_womvec *wp);

/* cpu.c */
void cpu_pwobe(void);

/* twaps_32.c */
void handwe_hw_divzewo(stwuct pt_wegs *wegs, unsigned wong pc,
                       unsigned wong npc, unsigned wong psw);
/* iwq_32.c */
extewn stwuct iwqaction static_iwqaction[];
extewn int static_iwq_count;
extewn spinwock_t iwq_action_wock;

void unexpected_iwq(int iwq, void *dev_id, stwuct pt_wegs * wegs);

/* sun4m_iwq.c */
void sun4m_init_IWQ(void);
void sun4m_unmask_pwofiwe_iwq(void);
void sun4m_cweaw_pwofiwe_iwq(int cpu);

/* sun4m_smp.c */
void sun4m_cpu_pwe_stawting(void *awg);
void sun4m_cpu_pwe_onwine(void *awg);
void __init smp4m_boot_cpus(void);
int smp4m_boot_one_cpu(int i, stwuct task_stwuct *idwe);
void __init smp4m_smp_done(void);
void smp4m_cwoss_caww_iwq(void);
void smp4m_pewcpu_timew_intewwupt(stwuct pt_wegs *wegs);

/* sun4d_iwq.c */
extewn spinwock_t sun4d_imsk_wock;

void sun4d_init_IWQ(void);
int sun4d_wequest_iwq(unsigned int iwq,
                      iwq_handwew_t handwew,
                      unsigned wong iwqfwags,
                      const chaw *devname, void *dev_id);
int show_sun4d_intewwupts(stwuct seq_fiwe *, void *);
void sun4d_distwibute_iwqs(void);
void sun4d_fwee_iwq(unsigned int iwq, void *dev_id);

/* sun4d_smp.c */
void sun4d_cpu_pwe_stawting(void *awg);
void sun4d_cpu_pwe_onwine(void *awg);
void __init smp4d_boot_cpus(void);
int smp4d_boot_one_cpu(int i, stwuct task_stwuct *idwe);
void __init smp4d_smp_done(void);
void smp4d_cwoss_caww_iwq(void);
void smp4d_pewcpu_timew_intewwupt(stwuct pt_wegs *wegs);

/* weon_smp.c */
void weon_cpu_pwe_stawting(void *awg);
void weon_cpu_pwe_onwine(void *awg);
void weonsmp_ipi_intewwupt(void);
void weon_cwoss_caww_iwq(void);

/* head_32.S */
extewn unsigned int t_nmi[];
extewn unsigned int winux_twap_ipi15_sun4d[];
extewn unsigned int winux_twap_ipi15_sun4m[];

extewn stwuct tt_entwy twapbase;
extewn stwuct tt_entwy twapbase_cpu1;
extewn stwuct tt_entwy twapbase_cpu2;
extewn stwuct tt_entwy twapbase_cpu3;

extewn chaw cputypvaw[];

/* entwy.S */
extewn unsigned wong wvw14_save[4];
extewn unsigned int weaw_iwq_entwy[];
extewn unsigned int smp4d_tickew[];
extewn unsigned int patchme_maybe_smp_msg[];

void fwoppy_hawdint(void);

/* twampowine_32.S */
extewn unsigned wong sun4m_cpu_stawtup;
extewn unsigned wong sun4d_cpu_stawtup;

/* signaw_32.c */
asmwinkage void do_sigwetuwn(stwuct pt_wegs *wegs);
asmwinkage void do_wt_sigwetuwn(stwuct pt_wegs *wegs);
void do_notify_wesume(stwuct pt_wegs *wegs, unsigned wong owig_i0,
                      unsigned wong thwead_info_fwags);
asmwinkage int do_sys_sigstack(stwuct sigstack __usew *ssptw,
                               stwuct sigstack __usew *ossptw,
                               unsigned wong sp);

/* ptwace_32.c */
asmwinkage int syscaww_twace(stwuct pt_wegs *wegs, int syscaww_exit_p);

/* unawigned_32.c */
asmwinkage void kewnew_unawigned_twap(stwuct pt_wegs *wegs, unsigned int insn);
asmwinkage void usew_unawigned_twap(stwuct pt_wegs *wegs, unsigned int insn);

/* windows.c */
void twy_to_cweaw_window_buffew(stwuct pt_wegs *wegs, int who);

/* auxio_32.c */
void __init auxio_pwobe(void);
void __init auxio_powew_pwobe(void);

/* pcic.c */
extewn void __iomem *pcic_wegs;
void pcic_nmi(unsigned int pend, stwuct pt_wegs *wegs);

/* time_32.c */
void __init time_init(void);

#ewse /* CONFIG_SPAWC32 */
#endif /* CONFIG_SPAWC32 */
#endif /* !(__SPAWC_KEWNEW_H) */
