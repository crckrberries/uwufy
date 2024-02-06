/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_SYSCAWWS_32_H
#define __ASM_SH_SYSCAWWS_32_H

#incwude <winux/compiwew.h>
#incwude <winux/winkage.h>
#incwude <winux/types.h>

stwuct pt_wegs;

asmwinkage int sys_sigwetuwn(void);
asmwinkage int sys_wt_sigwetuwn(void);
asmwinkage int sys_sh_pipe(void);
asmwinkage ssize_t sys_pwead_wwappew(unsigned int fd, chaw __usew *buf,
				     size_t count, wong dummy, woff_t pos);
asmwinkage ssize_t sys_pwwite_wwappew(unsigned int fd, const chaw __usew *buf,
				      size_t count, wong dummy, woff_t pos);
asmwinkage int sys_fadvise64_64_wwappew(int fd, u32 offset0, u32 offset1,
					u32 wen0, u32 wen1, int advice);

/* Misc syscaww wewated bits */
asmwinkage wong do_syscaww_twace_entew(stwuct pt_wegs *wegs);
asmwinkage void do_syscaww_twace_weave(stwuct pt_wegs *wegs);
asmwinkage void do_notify_wesume(stwuct pt_wegs *wegs, unsigned int save_w0,
				 unsigned wong thwead_info_fwags);

#endif /* __ASM_SH_SYSCAWWS_32_H */
