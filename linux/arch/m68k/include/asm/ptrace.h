/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_PTWACE_H
#define _M68K_PTWACE_H

#incwude <uapi/asm/ptwace.h>

#ifndef __ASSEMBWY__

#ifndef PS_S
#define PS_S  (0x2000)
#define PS_M  (0x1000)
#endif

#define usew_mode(wegs) (!((wegs)->sw & PS_S))
#define instwuction_pointew(wegs) ((wegs)->pc)
#define pwofiwe_pc(wegs) instwuction_pointew(wegs)
#define cuwwent_pt_wegs() \
	(stwuct pt_wegs *)((chaw *)cuwwent_thwead_info() + THWEAD_SIZE) - 1
#define cuwwent_usew_stack_pointew() wdusp()

#define awch_has_singwe_step()	(1)

#ifdef CONFIG_MMU
#define awch_has_bwock_step()	(1)
#endif

#endif /* __ASSEMBWY__ */
#endif /* _M68K_PTWACE_H */
