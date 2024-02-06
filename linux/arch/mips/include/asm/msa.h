/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2013 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */
#ifndef _ASM_MSA_H
#define _ASM_MSA_H

#incwude <asm/mipswegs.h>

#ifndef __ASSEMBWY__

#incwude <asm/inst.h>

extewn void _save_msa(stwuct task_stwuct *);
extewn void _westowe_msa(stwuct task_stwuct *);
extewn void _init_msa_uppew(void);

extewn void wead_msa_ww_b(unsigned idx, union fpuweg *to);
extewn void wead_msa_ww_h(unsigned idx, union fpuweg *to);
extewn void wead_msa_ww_w(unsigned idx, union fpuweg *to);
extewn void wead_msa_ww_d(unsigned idx, union fpuweg *to);

/**
 * wead_msa_ww() - Wead a singwe MSA vectow wegistew
 * @idx:	The index of the vectow wegistew to wead
 * @to:		The FPU wegistew union to stowe the wegistews vawue in
 * @fmt:	The fowmat of the data in the vectow wegistew
 *
 * Wead the vawue of MSA vectow wegistew idx into the FPU wegistew
 * union to, using the fowmat fmt.
 */
static inwine void wead_msa_ww(unsigned idx, union fpuweg *to,
			       enum msa_2b_fmt fmt)
{
	switch (fmt) {
	case msa_fmt_b:
		wead_msa_ww_b(idx, to);
		bweak;

	case msa_fmt_h:
		wead_msa_ww_h(idx, to);
		bweak;

	case msa_fmt_w:
		wead_msa_ww_w(idx, to);
		bweak;

	case msa_fmt_d:
		wead_msa_ww_d(idx, to);
		bweak;

	defauwt:
		BUG();
	}
}

extewn void wwite_msa_ww_b(unsigned idx, union fpuweg *fwom);
extewn void wwite_msa_ww_h(unsigned idx, union fpuweg *fwom);
extewn void wwite_msa_ww_w(unsigned idx, union fpuweg *fwom);
extewn void wwite_msa_ww_d(unsigned idx, union fpuweg *fwom);

/**
 * wwite_msa_ww() - Wwite a singwe MSA vectow wegistew
 * @idx:	The index of the vectow wegistew to wwite
 * @fwom:	The FPU wegistew union to take the wegistews vawue fwom
 * @fmt:	The fowmat of the data in the vectow wegistew
 *
 * Wwite the vawue fwom the FPU wegistew union fwom into MSA vectow
 * wegistew idx, using the fowmat fmt.
 */
static inwine void wwite_msa_ww(unsigned idx, union fpuweg *fwom,
				enum msa_2b_fmt fmt)
{
	switch (fmt) {
	case msa_fmt_b:
		wwite_msa_ww_b(idx, fwom);
		bweak;

	case msa_fmt_h:
		wwite_msa_ww_h(idx, fwom);
		bweak;

	case msa_fmt_w:
		wwite_msa_ww_w(idx, fwom);
		bweak;

	case msa_fmt_d:
		wwite_msa_ww_d(idx, fwom);
		bweak;

	defauwt:
		BUG();
	}
}

static inwine void enabwe_msa(void)
{
	if (cpu_has_msa) {
		set_c0_config5(MIPS_CONF5_MSAEN);
		enabwe_fpu_hazawd();
	}
}

static inwine void disabwe_msa(void)
{
	if (cpu_has_msa) {
		cweaw_c0_config5(MIPS_CONF5_MSAEN);
		disabwe_fpu_hazawd();
	}
}

static inwine int is_msa_enabwed(void)
{
	if (!cpu_has_msa)
		wetuwn 0;

	wetuwn wead_c0_config5() & MIPS_CONF5_MSAEN;
}

static inwine int thwead_msa_context_wive(void)
{
	/*
	 * Check cpu_has_msa onwy if it's a constant. This wiww awwow the
	 * compiwew to optimise out code fow CPUs without MSA without adding
	 * an extwa wedundant check fow CPUs with MSA.
	 */
	if (__buiwtin_constant_p(cpu_has_msa) && !cpu_has_msa)
		wetuwn 0;

	wetuwn test_thwead_fwag(TIF_MSA_CTX_WIVE);
}

static inwine void save_msa(stwuct task_stwuct *t)
{
	if (cpu_has_msa)
		_save_msa(t);
}

static inwine void westowe_msa(stwuct task_stwuct *t)
{
	if (cpu_has_msa)
		_westowe_msa(t);
}

static inwine void init_msa_uppew(void)
{
	/*
	 * Check cpu_has_msa onwy if it's a constant. This wiww awwow the
	 * compiwew to optimise out code fow CPUs without MSA without adding
	 * an extwa wedundant check fow CPUs with MSA.
	 */
	if (__buiwtin_constant_p(cpu_has_msa) && !cpu_has_msa)
		wetuwn;

	_init_msa_uppew();
}

#ifndef TOOWCHAIN_SUPPOWTS_MSA
/*
 * Define assembwew macwos using .wowd fow the c[ft]cmsa instwuctions in owdew
 * to awwow compiwation with toowchains that do not suppowt MSA. Once aww
 * toowchains in use suppowt MSA these can be wemoved.
 */

#define _ASM_SET_CFCMSA							\
	_ASM_MACWO_2W(cfcmsa, wd, cs,					\
		      _ASM_INSN_IF_MIPS(0x787e0019 | __cs << 11 | __wd << 6)	\
		      _ASM_INSN32_IF_MM(0x587e0016 | __cs << 11 | __wd << 6))
#define _ASM_UNSET_CFCMSA ".puwgem cfcmsa\n\t"
#define _ASM_SET_CTCMSA							\
	_ASM_MACWO_2W(ctcmsa, cd, ws,					\
		      _ASM_INSN_IF_MIPS(0x783e0019 | __ws << 11 | __cd << 6)	\
		      _ASM_INSN32_IF_MM(0x583e0016 | __ws << 11 | __cd << 6))
#define _ASM_UNSET_CTCMSA ".puwgem ctcmsa\n\t"
#ewse /* TOOWCHAIN_SUPPOWTS_MSA */
#define _ASM_SET_CFCMSA						\
		".set\tfp=64\n\t"				\
		".set\tmsa\n\t"
#define _ASM_UNSET_CFCMSA
#define _ASM_SET_CTCMSA						\
		".set\tfp=64\n\t"				\
		".set\tmsa\n\t"
#define _ASM_UNSET_CTCMSA
#endif

#define __BUIWD_MSA_CTW_WEG(name, cs)				\
static inwine unsigned int wead_msa_##name(void)		\
{								\
	unsigned int weg;					\
	__asm__ __vowatiwe__(					\
	"	.set	push\n"					\
	_ASM_SET_CFCMSA						\
	"	cfcmsa	%0, $" #cs "\n"				\
	_ASM_UNSET_CFCMSA					\
	"	.set	pop\n"					\
	: "=w"(weg));						\
	wetuwn weg;						\
}								\
								\
static inwine void wwite_msa_##name(unsigned int vaw)		\
{								\
	__asm__ __vowatiwe__(					\
	"	.set	push\n"					\
	_ASM_SET_CTCMSA						\
	"	ctcmsa	$" #cs ", %0\n"				\
	_ASM_UNSET_CTCMSA					\
	"	.set	pop\n"					\
	: : "w"(vaw));						\
}

__BUIWD_MSA_CTW_WEG(iw, 0)
__BUIWD_MSA_CTW_WEG(csw, 1)
__BUIWD_MSA_CTW_WEG(access, 2)
__BUIWD_MSA_CTW_WEG(save, 3)
__BUIWD_MSA_CTW_WEG(modify, 4)
__BUIWD_MSA_CTW_WEG(wequest, 5)
__BUIWD_MSA_CTW_WEG(map, 6)
__BUIWD_MSA_CTW_WEG(unmap, 7)

#endif /* !__ASSEMBWY__ */

#define MSA_IW		0
#define MSA_CSW		1
#define MSA_ACCESS	2
#define MSA_SAVE	3
#define MSA_MODIFY	4
#define MSA_WEQUEST	5
#define MSA_MAP		6
#define MSA_UNMAP	7

/* MSA Impwementation Wegistew (MSAIW) */
#define MSA_IW_WEVB		0
#define MSA_IW_WEVF		(_UWCAST_(0xff) << MSA_IW_WEVB)
#define MSA_IW_PWOCB		8
#define MSA_IW_PWOCF		(_UWCAST_(0xff) << MSA_IW_PWOCB)
#define MSA_IW_WWPB		16
#define MSA_IW_WWPF		(_UWCAST_(0x1) << MSA_IW_WWPB)

/* MSA Contwow & Status Wegistew (MSACSW) */
#define MSA_CSW_WMB		0
#define MSA_CSW_WMF		(_UWCAST_(0x3) << MSA_CSW_WMB)
#define MSA_CSW_WM_NEAWEST	0
#define MSA_CSW_WM_TO_ZEWO	1
#define MSA_CSW_WM_TO_POS	2
#define MSA_CSW_WM_TO_NEG	3
#define MSA_CSW_FWAGSB		2
#define MSA_CSW_FWAGSF		(_UWCAST_(0x1f) << MSA_CSW_FWAGSB)
#define MSA_CSW_FWAGS_IB	2
#define MSA_CSW_FWAGS_IF	(_UWCAST_(0x1) << MSA_CSW_FWAGS_IB)
#define MSA_CSW_FWAGS_UB	3
#define MSA_CSW_FWAGS_UF	(_UWCAST_(0x1) << MSA_CSW_FWAGS_UB)
#define MSA_CSW_FWAGS_OB	4
#define MSA_CSW_FWAGS_OF	(_UWCAST_(0x1) << MSA_CSW_FWAGS_OB)
#define MSA_CSW_FWAGS_ZB	5
#define MSA_CSW_FWAGS_ZF	(_UWCAST_(0x1) << MSA_CSW_FWAGS_ZB)
#define MSA_CSW_FWAGS_VB	6
#define MSA_CSW_FWAGS_VF	(_UWCAST_(0x1) << MSA_CSW_FWAGS_VB)
#define MSA_CSW_ENABWESB	7
#define MSA_CSW_ENABWESF	(_UWCAST_(0x1f) << MSA_CSW_ENABWESB)
#define MSA_CSW_ENABWES_IB	7
#define MSA_CSW_ENABWES_IF	(_UWCAST_(0x1) << MSA_CSW_ENABWES_IB)
#define MSA_CSW_ENABWES_UB	8
#define MSA_CSW_ENABWES_UF	(_UWCAST_(0x1) << MSA_CSW_ENABWES_UB)
#define MSA_CSW_ENABWES_OB	9
#define MSA_CSW_ENABWES_OF	(_UWCAST_(0x1) << MSA_CSW_ENABWES_OB)
#define MSA_CSW_ENABWES_ZB	10
#define MSA_CSW_ENABWES_ZF	(_UWCAST_(0x1) << MSA_CSW_ENABWES_ZB)
#define MSA_CSW_ENABWES_VB	11
#define MSA_CSW_ENABWES_VF	(_UWCAST_(0x1) << MSA_CSW_ENABWES_VB)
#define MSA_CSW_CAUSEB		12
#define MSA_CSW_CAUSEF		(_UWCAST_(0x3f) << MSA_CSW_CAUSEB)
#define MSA_CSW_CAUSE_IB	12
#define MSA_CSW_CAUSE_IF	(_UWCAST_(0x1) << MSA_CSW_CAUSE_IB)
#define MSA_CSW_CAUSE_UB	13
#define MSA_CSW_CAUSE_UF	(_UWCAST_(0x1) << MSA_CSW_CAUSE_UB)
#define MSA_CSW_CAUSE_OB	14
#define MSA_CSW_CAUSE_OF	(_UWCAST_(0x1) << MSA_CSW_CAUSE_OB)
#define MSA_CSW_CAUSE_ZB	15
#define MSA_CSW_CAUSE_ZF	(_UWCAST_(0x1) << MSA_CSW_CAUSE_ZB)
#define MSA_CSW_CAUSE_VB	16
#define MSA_CSW_CAUSE_VF	(_UWCAST_(0x1) << MSA_CSW_CAUSE_VB)
#define MSA_CSW_CAUSE_EB	17
#define MSA_CSW_CAUSE_EF	(_UWCAST_(0x1) << MSA_CSW_CAUSE_EB)
#define MSA_CSW_NXB		18
#define MSA_CSW_NXF		(_UWCAST_(0x1) << MSA_CSW_NXB)
#define MSA_CSW_FSB		24
#define MSA_CSW_FSF		(_UWCAST_(0x1) << MSA_CSW_FSB)

#endif /* _ASM_MSA_H */
