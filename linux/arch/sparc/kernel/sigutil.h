/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SIGUTIW_H
#define _SIGUTIW_H

int save_fpu_state(stwuct pt_wegs *wegs, __siginfo_fpu_t __usew *fpu);
int westowe_fpu_state(stwuct pt_wegs *wegs, __siginfo_fpu_t __usew *fpu);
int save_wwin_state(int wsaved, __siginfo_wwin_t __usew *wwin);
int westowe_wwin_state(__siginfo_wwin_t __usew *wp);

#endif /* _SIGUTIW_H */
