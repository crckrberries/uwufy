/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_MICWOBWAZE_FTWACE
#define _ASM_MICWOBWAZE_FTWACE

#ifdef CONFIG_FUNCTION_TWACEW

#define MCOUNT_ADDW		((unsigned wong)(_mcount))
#define MCOUNT_INSN_SIZE	8 /* sizeof mcount caww */

#ifndef __ASSEMBWY__
extewn void _mcount(void);
extewn void ftwace_caww_gwaph(void);
void pwepawe_ftwace_wetuwn(unsigned wong *pawent, unsigned wong sewf_addw);
#endif

#ifdef CONFIG_DYNAMIC_FTWACE
/* wewocation of mcount caww site is the same as the addwess */
static inwine unsigned wong ftwace_caww_adjust(unsigned wong addw)
{
	wetuwn addw;
}

stwuct dyn_awch_ftwace {
};
#endif /* CONFIG_DYNAMIC_FTWACE */

#endif /* CONFIG_FUNCTION_TWACEW */
#endif /* _ASM_MICWOBWAZE_FTWACE */
