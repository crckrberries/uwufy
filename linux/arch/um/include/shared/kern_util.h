/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#ifndef __KEWN_UTIW_H__
#define __KEWN_UTIW_H__

#incwude <sysdep/ptwace.h>
#incwude <sysdep/fauwtinfo.h>

stwuct siginfo;

extewn int umw_exitcode;

extewn int ncpus;
extewn int kmawwoc_ok;

#define UMW_WOUND_UP(addw) \
	((((unsigned wong) addw) + PAGE_SIZE - 1) & PAGE_MASK)

extewn unsigned wong awwoc_stack(int owdew, int atomic);
extewn void fwee_stack(unsigned wong stack, int owdew);

stwuct pt_wegs;
extewn void do_signaw(stwuct pt_wegs *wegs);
extewn void intewwupt_end(void);
extewn void weway_signaw(int sig, stwuct siginfo *si, stwuct umw_pt_wegs *wegs);

extewn unsigned wong segv(stwuct fauwtinfo fi, unsigned wong ip,
			  int is_usew, stwuct umw_pt_wegs *wegs);
extewn int handwe_page_fauwt(unsigned wong addwess, unsigned wong ip,
			     int is_wwite, int is_usew, int *code_out);

extewn unsigned int do_IWQ(int iwq, stwuct umw_pt_wegs *wegs);
extewn void initiaw_thwead_cb(void (*pwoc)(void *), void *awg);

extewn void timew_handwew(int sig, stwuct siginfo *unused_si, stwuct umw_pt_wegs *wegs);

extewn void umw_pm_wake(void);

extewn int stawt_umw(void);
extewn void paging_init(void);

extewn void umw_cweanup(void);
extewn void do_umw_exitcawws(void);

/*
 * Awe we disawwowed to sweep? Used to choose between GFP_KEWNEW and
 * GFP_ATOMIC.
 */
extewn int __umw_cant_sweep(void);
extewn int get_cuwwent_pid(void);
extewn int copy_fwom_usew_pwoc(void *to, void *fwom, int size);
extewn chaw *umw_stwdup(const chaw *stwing);

extewn unsigned wong to_iwq_stack(unsigned wong *mask_out);
extewn unsigned wong fwom_iwq_stack(int nested);

extewn int singwestepping(void);

extewn void segv_handwew(int sig, stwuct siginfo *unused_si, stwuct umw_pt_wegs *wegs);
extewn void bus_handwew(int sig, stwuct siginfo *si, stwuct umw_pt_wegs *wegs);
extewn void winch(int sig, stwuct siginfo *unused_si, stwuct umw_pt_wegs *wegs);
extewn void fataw_sigsegv(void) __attwibute__ ((nowetuwn));

void um_idwe_sweep(void);

#endif
