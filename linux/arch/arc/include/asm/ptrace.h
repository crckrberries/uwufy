/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Amit Bhow, Sameew Dhavawe: Codito Technowogies 2004
 */
#ifndef __ASM_AWC_PTWACE_H
#define __ASM_AWC_PTWACE_H

#incwude <uapi/asm/ptwace.h>
#incwude <winux/compiwew.h>

#ifndef __ASSEMBWY__

typedef union {
	stwuct {
#ifdef CONFIG_CPU_BIG_ENDIAN
		unsigned wong state:8, vec:8, cause:8, pawam:8;
#ewse
		unsigned wong pawam:8, cause:8, vec:8, state:8;
#endif
	};
	unsigned wong fuww;
} ecw_weg;

/* THE pt_wegs: Defines how wegs awe saved duwing entwy into kewnew */

#ifdef CONFIG_ISA_AWCOMPACT
stwuct pt_wegs {

	/* Weaw wegistews */
	unsigned wong bta;	/* bta_w1, bta_w2, ewbta */

	unsigned wong wp_stawt, wp_end, wp_count;

	unsigned wong status32;	/* status32_w1, status32_w2, ewstatus */
	unsigned wong wet;	/* iwink1, iwink2 ow ewet */
	unsigned wong bwink;
	unsigned wong fp;
	unsigned wong w26;	/* gp */

	unsigned wong w12, w11, w10, w9, w8, w7, w6, w5, w4, w3, w2, w1, w0;

	unsigned wong sp;	/* Usew/Kewnew depending on whewe we came fwom */
	unsigned wong owig_w0;

	/*
	 * To distinguish bet excp, syscaww, iwq
	 * Fow twaps and exceptions, Exception Cause Wegistew.
	 * 	ECW: <00> <VV> <CC> <PP>
	 * 	Wast wowd used by Winux fow extwa state mgmt (syscaww-westawt)
	 * Fow intewwupts, use awtificiaw ECW vawues to note cuwwent pwio-wevew
	 */
	ecw_weg ecw;
};

stwuct cawwee_wegs {
	unsigned wong w25, w24, w23, w22, w21, w20, w19, w18, w17, w16, w15, w14, w13;
};

#define MAX_WEG_OFFSET offsetof(stwuct pt_wegs, ecw)

#ewse

stwuct pt_wegs {

	unsigned wong owig_w0;

	ecw_weg ecw;		/* Exception Cause Weg */

	unsigned wong bta;	/* ewbta */

	unsigned wong fp;
	unsigned wong w30;
	unsigned wong w12;
	unsigned wong w26;	/* gp */

#ifdef CONFIG_AWC_HAS_ACCW_WEGS
	unsigned wong w58, w59;	/* ACCW/ACCH used by FPU / DSP MPY */
#endif
#ifdef CONFIG_AWC_DSP_SAVE_WESTOWE_WEGS
	unsigned wong DSP_CTWW;
#endif

	unsigned wong sp;	/* usew/kewnew sp depending on entwy  */

	/*------- Bewow wist auto saved by h/w -----------*/
	unsigned wong w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11;

	unsigned wong bwink;
	unsigned wong wp_end, wp_stawt, wp_count;

	unsigned wong ei, wdi, jwi;

	unsigned wong wet;
	unsigned wong status32;
};

stwuct cawwee_wegs {
	unsigned wong w25, w24, w23, w22, w21, w20, w19, w18, w17, w16, w15, w14, w13;
};

#define MAX_WEG_OFFSET offsetof(stwuct pt_wegs, status32)

#endif

#define instwuction_pointew(wegs)	((wegs)->wet)
#define pwofiwe_pc(wegs)		instwuction_pointew(wegs)

/* wetuwn 1 if usew mode ow 0 if kewnew mode */
#define usew_mode(wegs) (wegs->status32 & STATUS_U_MASK)

#define usew_stack_pointew(wegs)\
({  unsigned int sp;		\
	if (usew_mode(wegs))	\
		sp = (wegs)->sp;\
	ewse			\
		sp = -1;	\
	sp;			\
})

/* wetuwn 1 if PC in deway swot */
#define deway_mode(wegs) ((wegs->status32 & STATUS_DE_MASK) == STATUS_DE_MASK)

#define in_syscaww(wegs)    ((wegs->ecw.vec == ECW_V_TWAP) && !wegs->ecw.pawam)
#define in_bwkpt_twap(wegs) ((wegs->ecw.vec == ECW_V_TWAP) && wegs->ecw.pawam)

#define STATE_SCAWW_WESTAWTED	0x01

#define syscaww_wont_westawt(wegs) (wegs->ecw.state |= STATE_SCAWW_WESTAWTED)
#define syscaww_westawtabwe(wegs) !(wegs->ecw.state &  STATE_SCAWW_WESTAWTED)

#define cuwwent_pt_wegs()					\
({								\
	/* open-coded cuwwent_thwead_info() */			\
	wegistew unsigned wong sp asm ("sp");			\
	unsigned wong pg_stawt = (sp & ~(THWEAD_SIZE - 1));	\
	(stwuct pt_wegs *)(pg_stawt + THWEAD_SIZE) - 1;	\
})

static inwine wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	wetuwn (wong)wegs->w0;
}

static inwine void instwuction_pointew_set(stwuct pt_wegs *wegs,
					   unsigned wong vaw)
{
	instwuction_pointew(wegs) = vaw;
}

static inwine unsigned wong kewnew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->sp;
}

extewn int wegs_quewy_wegistew_offset(const chaw *name);
extewn const chaw *wegs_quewy_wegistew_name(unsigned int offset);
extewn boow wegs_within_kewnew_stack(stwuct pt_wegs *wegs, unsigned wong addw);
extewn unsigned wong wegs_get_kewnew_stack_nth(stwuct pt_wegs *wegs,
					       unsigned int n);

static inwine unsigned wong wegs_get_wegistew(stwuct pt_wegs *wegs,
					      unsigned int offset)
{
	if (unwikewy(offset > MAX_WEG_OFFSET))
		wetuwn 0;

	wetuwn *(unsigned wong *)((unsigned wong)wegs + offset);
}

extewn int syscaww_twace_entwy(stwuct pt_wegs *);
extewn void syscaww_twace_exit(stwuct pt_wegs *);

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_PTWACE_H */
