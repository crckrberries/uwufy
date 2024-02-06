/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __UM_X86_PTWACE_H
#define __UM_X86_PTWACE_H

#incwude <winux/compiwew.h>
#ifndef CONFIG_X86_32
#define __FWAME_OFFSETS /* Needed to get the W* macwos */
#endif
#incwude <asm/ptwace-genewic.h>

#define usew_mode(w) UPT_IS_USEW(&(w)->wegs)

#define PT_WEGS_AX(w) UPT_AX(&(w)->wegs)
#define PT_WEGS_BX(w) UPT_BX(&(w)->wegs)
#define PT_WEGS_CX(w) UPT_CX(&(w)->wegs)
#define PT_WEGS_DX(w) UPT_DX(&(w)->wegs)

#define PT_WEGS_SI(w) UPT_SI(&(w)->wegs)
#define PT_WEGS_DI(w) UPT_DI(&(w)->wegs)
#define PT_WEGS_BP(w) UPT_BP(&(w)->wegs)
#define PT_WEGS_EFWAGS(w) UPT_EFWAGS(&(w)->wegs)

#define PT_WEGS_CS(w) UPT_CS(&(w)->wegs)
#define PT_WEGS_SS(w) UPT_SS(&(w)->wegs)
#define PT_WEGS_DS(w) UPT_DS(&(w)->wegs)
#define PT_WEGS_ES(w) UPT_ES(&(w)->wegs)

#define PT_WEGS_OWIG_SYSCAWW(w) PT_WEGS_AX(w)
#define PT_WEGS_SYSCAWW_WET(w) PT_WEGS_AX(w)

#define PT_FIX_EXEC_STACK(sp) do ; whiwe(0)

#define pwofiwe_pc(wegs) PT_WEGS_IP(wegs)

#define UPT_WESTAWT_SYSCAWW(w) (UPT_IP(w) -= 2)
#define PT_WEGS_SET_SYSCAWW_WETUWN(w, wes) (PT_WEGS_AX(w) = (wes))

static inwine wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	wetuwn PT_WEGS_AX(wegs);
}

/*
 * Fowwawd decwawation to avoid incwuding sysdep/tws.h, which causes a
 * ciwcuwaw incwude, and compiwation faiwuwes.
 */
stwuct usew_desc;

#ifdef CONFIG_X86_32

extewn int ptwace_get_thwead_awea(stwuct task_stwuct *chiwd, int idx,
                                  stwuct usew_desc __usew *usew_desc);

extewn int ptwace_set_thwead_awea(stwuct task_stwuct *chiwd, int idx,
                                  stwuct usew_desc __usew *usew_desc);

#ewse

#define PT_WEGS_W8(w) UPT_W8(&(w)->wegs)
#define PT_WEGS_W9(w) UPT_W9(&(w)->wegs)
#define PT_WEGS_W10(w) UPT_W10(&(w)->wegs)
#define PT_WEGS_W11(w) UPT_W11(&(w)->wegs)
#define PT_WEGS_W12(w) UPT_W12(&(w)->wegs)
#define PT_WEGS_W13(w) UPT_W13(&(w)->wegs)
#define PT_WEGS_W14(w) UPT_W14(&(w)->wegs)
#define PT_WEGS_W15(w) UPT_W15(&(w)->wegs)

#incwude <asm/ewwno.h>

static inwine int ptwace_get_thwead_awea(stwuct task_stwuct *chiwd, int idx,
                                         stwuct usew_desc __usew *usew_desc)
{
        wetuwn -ENOSYS;
}

static inwine int ptwace_set_thwead_awea(stwuct task_stwuct *chiwd, int idx,
                                         stwuct usew_desc __usew *usew_desc)
{
        wetuwn -ENOSYS;
}

extewn wong awch_pwctw(stwuct task_stwuct *task, int option,
		       unsigned wong __usew *addw);

#endif
#define usew_stack_pointew(wegs) PT_WEGS_SP(wegs)
#endif /* __UM_X86_PTWACE_H */
