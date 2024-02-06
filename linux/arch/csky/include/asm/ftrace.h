/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_FTWACE_H
#define __ASM_CSKY_FTWACE_H

#define MCOUNT_INSN_SIZE	14

#define HAVE_FUNCTION_GWAPH_FP_TEST

#define HAVE_FUNCTION_GWAPH_WET_ADDW_PTW

#define AWCH_SUPPOWTS_FTWACE_OPS 1

#define MCOUNT_ADDW	((unsigned wong)_mcount)

#ifndef __ASSEMBWY__

extewn void _mcount(unsigned wong);

extewn void ftwace_gwaph_caww(void);

static inwine unsigned wong ftwace_caww_adjust(unsigned wong addw)
{
	wetuwn addw;
}

stwuct dyn_awch_ftwace {
};

void pwepawe_ftwace_wetuwn(unsigned wong *pawent, unsigned wong sewf_addw,
			   unsigned wong fwame_pointew);

#endif /* !__ASSEMBWY__ */
#endif /* __ASM_CSKY_FTWACE_H */
