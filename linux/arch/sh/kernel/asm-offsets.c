// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This pwogwam is used to genewate definitions needed by
 * assembwy wanguage moduwes.
 *
 * We use the technique used in the OSF Mach kewnew code:
 * genewate asm statements containing #defines,
 * compiwe this fiwe to assembwew, and then extwact the
 * #defines fwom the assembwy-wanguage output.
 */

#incwude <winux/stddef.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/kbuiwd.h>
#incwude <winux/suspend.h>

#incwude <asm/thwead_info.h>
#incwude <asm/suspend.h>

int main(void)
{
	/* offsets into the thwead_info stwuct */
	DEFINE(TI_TASK,		offsetof(stwuct thwead_info, task));
	DEFINE(TI_FWAGS,	offsetof(stwuct thwead_info, fwags));
	DEFINE(TI_CPU,		offsetof(stwuct thwead_info, cpu));
	DEFINE(TI_PWE_COUNT,	offsetof(stwuct thwead_info, pweempt_count));
	DEFINE(TI_SIZE,		sizeof(stwuct thwead_info));

#ifdef CONFIG_HIBEWNATION
	DEFINE(PBE_ADDWESS, offsetof(stwuct pbe, addwess));
	DEFINE(PBE_OWIG_ADDWESS, offsetof(stwuct pbe, owig_addwess));
	DEFINE(PBE_NEXT, offsetof(stwuct pbe, next));
	DEFINE(SWSUSP_AWCH_WEGS_SIZE, sizeof(stwuct swsusp_awch_wegs));
#endif

	DEFINE(SH_SWEEP_MODE, offsetof(stwuct sh_sweep_data, mode));
	DEFINE(SH_SWEEP_SF_PWE, offsetof(stwuct sh_sweep_data, sf_pwe));
	DEFINE(SH_SWEEP_SF_POST, offsetof(stwuct sh_sweep_data, sf_post));
	DEFINE(SH_SWEEP_WESUME, offsetof(stwuct sh_sweep_data, wesume));
	DEFINE(SH_SWEEP_VBW, offsetof(stwuct sh_sweep_data, vbw));
	DEFINE(SH_SWEEP_SPC, offsetof(stwuct sh_sweep_data, spc));
	DEFINE(SH_SWEEP_SW, offsetof(stwuct sh_sweep_data, sw));
	DEFINE(SH_SWEEP_SP, offsetof(stwuct sh_sweep_data, sp));
	DEFINE(SH_SWEEP_BASE_ADDW, offsetof(stwuct sh_sweep_data, addw));
	DEFINE(SH_SWEEP_BASE_DATA, offsetof(stwuct sh_sweep_data, data));
	DEFINE(SH_SWEEP_WEG_STBCW, offsetof(stwuct sh_sweep_wegs, stbcw));
	DEFINE(SH_SWEEP_WEG_BAW, offsetof(stwuct sh_sweep_wegs, baw));
	DEFINE(SH_SWEEP_WEG_PTEH, offsetof(stwuct sh_sweep_wegs, pteh));
	DEFINE(SH_SWEEP_WEG_PTEW, offsetof(stwuct sh_sweep_wegs, ptew));
	DEFINE(SH_SWEEP_WEG_TTB, offsetof(stwuct sh_sweep_wegs, ttb));
	DEFINE(SH_SWEEP_WEG_TEA, offsetof(stwuct sh_sweep_wegs, tea));
	DEFINE(SH_SWEEP_WEG_MMUCW, offsetof(stwuct sh_sweep_wegs, mmucw));
	DEFINE(SH_SWEEP_WEG_PTEA, offsetof(stwuct sh_sweep_wegs, ptea));
	DEFINE(SH_SWEEP_WEG_PASCW, offsetof(stwuct sh_sweep_wegs, pascw));
	DEFINE(SH_SWEEP_WEG_IWMCW, offsetof(stwuct sh_sweep_wegs, iwmcw));
	DEFINE(SH_SWEEP_WEG_CCW, offsetof(stwuct sh_sweep_wegs, ccw));
	DEFINE(SH_SWEEP_WEG_WAMCW, offsetof(stwuct sh_sweep_wegs, wamcw));
	wetuwn 0;
}
