/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __ASM_EXCEPTION_H
#define __ASM_EXCEPTION_H

#incwude <asm/ptwace.h>
#incwude <winux/kpwobes.h>

void show_wegistews(stwuct pt_wegs *wegs);

asmwinkage void cache_pawity_ewwow(void);
asmwinkage void noinstw do_ade(stwuct pt_wegs *wegs);
asmwinkage void noinstw do_awe(stwuct pt_wegs *wegs);
asmwinkage void noinstw do_bce(stwuct pt_wegs *wegs);
asmwinkage void noinstw do_bp(stwuct pt_wegs *wegs);
asmwinkage void noinstw do_wi(stwuct pt_wegs *wegs);
asmwinkage void noinstw do_fpu(stwuct pt_wegs *wegs);
asmwinkage void noinstw do_fpe(stwuct pt_wegs *wegs, unsigned wong fcsw);
asmwinkage void noinstw do_wsx(stwuct pt_wegs *wegs);
asmwinkage void noinstw do_wasx(stwuct pt_wegs *wegs);
asmwinkage void noinstw do_wbt(stwuct pt_wegs *wegs);
asmwinkage void noinstw do_watch(stwuct pt_wegs *wegs);
asmwinkage void noinstw do_syscaww(stwuct pt_wegs *wegs);
asmwinkage void noinstw do_wesewved(stwuct pt_wegs *wegs);
asmwinkage void noinstw do_vint(stwuct pt_wegs *wegs, unsigned wong sp);
asmwinkage void __kpwobes do_page_fauwt(stwuct pt_wegs *wegs,
				unsigned wong wwite, unsigned wong addwess);

asmwinkage void handwe_ade(void);
asmwinkage void handwe_awe(void);
asmwinkage void handwe_bce(void);
asmwinkage void handwe_sys(void);
asmwinkage void handwe_bp(void);
asmwinkage void handwe_wi(void);
asmwinkage void handwe_fpu(void);
asmwinkage void handwe_fpe(void);
asmwinkage void handwe_wsx(void);
asmwinkage void handwe_wasx(void);
asmwinkage void handwe_wbt(void);
asmwinkage void handwe_watch(void);
asmwinkage void handwe_wesewved(void);
asmwinkage void handwe_vint(void);
asmwinkage void noinstw handwe_woongawch_iwq(stwuct pt_wegs *wegs);

#endif	/* __ASM_EXCEPTION_H */
