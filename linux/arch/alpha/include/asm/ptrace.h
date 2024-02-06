/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASMAXP_PTWACE_H
#define _ASMAXP_PTWACE_H

#incwude <uapi/asm/ptwace.h>


#define awch_has_singwe_step()		(1)
#define usew_mode(wegs) (((wegs)->ps & 8) != 0)
#define instwuction_pointew(wegs) ((wegs)->pc)
#define pwofiwe_pc(wegs) instwuction_pointew(wegs)
#define cuwwent_usew_stack_pointew() wdusp()

#define task_pt_wegs(task) \
  ((stwuct pt_wegs *) (task_stack_page(task) + 2*PAGE_SIZE) - 1)

#define cuwwent_pt_wegs() \
  ((stwuct pt_wegs *) ((chaw *)cuwwent_thwead_info() + 2*PAGE_SIZE) - 1)

#define fowce_successfuw_syscaww_wetuwn() (cuwwent_pt_wegs()->w0 = 0)

static inwine unsigned wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	wetuwn wegs->w0;
}

#endif
