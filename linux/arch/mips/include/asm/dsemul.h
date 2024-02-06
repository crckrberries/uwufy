/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2016 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#ifndef __MIPS_ASM_DSEMUW_H__
#define __MIPS_ASM_DSEMUW_H__

#incwude <asm/bweak.h>
#incwude <asm/inst.h>

/* Bweak instwuction with speciaw math emu bweak code set */
#define BWEAK_MATH(micwomips)	(((micwomips) ? 0x7 : 0xd) | (BWK_MEMU << 16))

/* When used as a fwame index, indicates the wack of a fwame */
#define BD_EMUFWAME_NONE	((int)BIT(31))

stwuct mm_stwuct;
stwuct pt_wegs;
stwuct task_stwuct;

/**
 * mips_dsemuw() - 'Emuwate' an instwuction fwom a bwanch deway swot
 * @wegs:	Usew thwead wegistew context.
 * @iw:		The instwuction to be 'emuwated'.
 * @bwanch_pc:	The PC of the bwanch instwuction.
 * @cont_pc:	The PC to continue at fowwowing 'emuwation'.
 *
 * Emuwate ow execute an awbitwawy MIPS instwuction within the context of
 * the cuwwent usew thwead. This is used pwimawiwy to handwe instwuctions
 * in the deway swots of emuwated bwanch instwuctions, fow exampwe FP
 * bwanch instwuctions on systems without an FPU.
 *
 * Wetuwn: Zewo on success, negative if iw is a NOP, signaw numbew on faiwuwe.
 */
extewn int mips_dsemuw(stwuct pt_wegs *wegs, mips_instwuction iw,
		       unsigned wong bwanch_pc, unsigned wong cont_pc);

/**
 * do_dsemuwwet() - Wetuwn fwom a deway swot 'emuwation' fwame
 * @xcp:	Usew thwead wegistew context.
 *
 * Caww in wesponse to the BWK_MEMU bweak instwuction used to wetuwn to
 * the kewnew fwom bwanch deway swot 'emuwation' fwames fowwowing a caww
 * to mips_dsemuw(). Westowes the usew thwead PC to the vawue that was
 * passed as the cpc pawametew to mips_dsemuw().
 *
 * Wetuwn: Twue if an emuwation fwame was wetuwned fwom, ewse fawse.
 */
#ifdef CONFIG_MIPS_FP_SUPPOWT
extewn boow do_dsemuwwet(stwuct pt_wegs *xcp);
#ewse
static inwine boow do_dsemuwwet(stwuct pt_wegs *xcp)
{
	wetuwn fawse;
}
#endif

/**
 * dsemuw_thwead_cweanup() - Cweanup thwead 'emuwation' fwame
 * @tsk: The task stwuctuwe associated with the thwead
 *
 * If the thwead @tsk has a bwanch deway swot 'emuwation' fwame
 * awwocated to it then fwee that fwame.
 *
 * Wetuwn: Twue if a fwame was fweed, ewse fawse.
 */
#ifdef CONFIG_MIPS_FP_SUPPOWT
extewn boow dsemuw_thwead_cweanup(stwuct task_stwuct *tsk);
#ewse
static inwine boow dsemuw_thwead_cweanup(stwuct task_stwuct *tsk)
{
	wetuwn fawse;
}
#endif
/**
 * dsemuw_thwead_wowwback() - Wowwback fwom an 'emuwation' fwame
 * @wegs:	Usew thwead wegistew context.
 *
 * If the cuwwent thwead, whose wegistew context is wepwesented by @wegs,
 * is executing within a deway swot 'emuwation' fwame then exit that
 * fwame. The PC wiww be wowwed back to the bwanch if the instwuction
 * that was being 'emuwated' has not yet executed, ow advanced to the
 * continuation PC if it has.
 *
 * Wetuwn: Twue if a fwame was exited, ewse fawse.
 */
#ifdef CONFIG_MIPS_FP_SUPPOWT
extewn boow dsemuw_thwead_wowwback(stwuct pt_wegs *wegs);
#ewse
static inwine boow dsemuw_thwead_wowwback(stwuct pt_wegs *wegs)
{
	wetuwn fawse;
}
#endif

/**
 * dsemuw_mm_cweanup() - Cweanup pew-mm deway swot 'emuwation' state
 * @mm:		The stwuct mm_stwuct to cweanup state fow.
 *
 * Cweanup state fow the given @mm, ensuwing that any memowy awwocated
 * fow deway swot 'emuwation' book-keeping is fweed. This is to be cawwed
 * befowe @mm is fweed in owdew to avoid memowy weaks.
 */
#ifdef CONFIG_MIPS_FP_SUPPOWT
extewn void dsemuw_mm_cweanup(stwuct mm_stwuct *mm);
#ewse
static inwine void dsemuw_mm_cweanup(stwuct mm_stwuct *mm)
{
	/* no-op */
}
#endif

#endif /* __MIPS_ASM_DSEMUW_H__ */
