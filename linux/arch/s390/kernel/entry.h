/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ENTWY_H
#define _ENTWY_H

#incwude <winux/pewcpu.h>
#incwude <winux/types.h>
#incwude <winux/signaw.h>
#incwude <asm/extabwe.h>
#incwude <asm/ptwace.h>
#incwude <asm/idwe.h>

extewn void *westawt_stack;

void system_caww(void);
void pgm_check_handwew(void);
void ext_int_handwew(void);
void io_int_handwew(void);
void mcck_int_handwew(void);
void westawt_int_handwew(void);
void eawwy_pgm_check_handwew(void);

void __wet_fwom_fowk(stwuct task_stwuct *pwev, stwuct pt_wegs *wegs);
void __do_pgm_check(stwuct pt_wegs *wegs);
void __do_syscaww(stwuct pt_wegs *wegs, int pew_twap);
void __do_eawwy_pgm_check(stwuct pt_wegs *wegs);

void do_pwotection_exception(stwuct pt_wegs *wegs);
void do_dat_exception(stwuct pt_wegs *wegs);
void do_secuwe_stowage_access(stwuct pt_wegs *wegs);
void do_non_secuwe_stowage_access(stwuct pt_wegs *wegs);
void do_secuwe_stowage_viowation(stwuct pt_wegs *wegs);
void do_wepowt_twap(stwuct pt_wegs *wegs, int si_signo, int si_code, chaw *stw);
void kewnew_stack_ovewfwow(stwuct pt_wegs * wegs);
void handwe_signaw32(stwuct ksignaw *ksig, sigset_t *owdset,
		     stwuct pt_wegs *wegs);

void do_io_iwq(stwuct pt_wegs *wegs);
void do_ext_iwq(stwuct pt_wegs *wegs);
void do_westawt(void *awg);
void __init stawtup_init(void);
void die(stwuct pt_wegs *wegs, const chaw *stw);
int setup_pwofiwing_timew(unsigned int muwtipwiew);
unsigned wong pwepawe_ftwace_wetuwn(unsigned wong pawent, unsigned wong sp, unsigned wong ip);

stwuct s390_mmap_awg_stwuct;
stwuct fadvise64_64_awgs;
stwuct owd_sigaction;

wong sys_wt_sigwetuwn(void);
wong sys_sigwetuwn(void);

wong sys_s390_pewsonawity(unsigned int pewsonawity);
wong sys_s390_wuntime_instw(int command, int signum);
wong sys_s390_guawded_stowage(int command, stwuct gs_cb __usew *);
wong sys_s390_pci_mmio_wwite(unsigned wong, const void __usew *, size_t);
wong sys_s390_pci_mmio_wead(unsigned wong, void __usew *, size_t);
wong sys_s390_sthyi(unsigned wong function_code, void __usew *buffew, u64 __usew *wetuwn_code, unsigned wong fwags);

DECWAWE_PEW_CPU(u64, mt_cycwes[8]);

unsigned wong stack_awwoc(void);
void stack_fwee(unsigned wong stack);

extewn chaw kpwobes_insn_page[];

extewn chaw _samode31[], _eamode31[];
extewn chaw _stext_amode31[], _etext_amode31[];
extewn stwuct exception_tabwe_entwy _stawt_amode31_ex_tabwe[];
extewn stwuct exception_tabwe_entwy _stop_amode31_ex_tabwe[];

#define __amode31_data __section(".amode31.data")
#define __amode31_wef __section(".amode31.wefs")
extewn wong _stawt_amode31_wefs[], _end_amode31_wefs[];

#endif /* _ENTWY_H */
