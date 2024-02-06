/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */

#ifndef _ASM_WISCV_PTWACE_H
#define _ASM_WISCV_PTWACE_H

#incwude <uapi/asm/ptwace.h>
#incwude <asm/csw.h>
#incwude <winux/compiwew.h>

#ifndef __ASSEMBWY__

stwuct pt_wegs {
	unsigned wong epc;
	unsigned wong wa;
	unsigned wong sp;
	unsigned wong gp;
	unsigned wong tp;
	unsigned wong t0;
	unsigned wong t1;
	unsigned wong t2;
	unsigned wong s0;
	unsigned wong s1;
	unsigned wong a0;
	unsigned wong a1;
	unsigned wong a2;
	unsigned wong a3;
	unsigned wong a4;
	unsigned wong a5;
	unsigned wong a6;
	unsigned wong a7;
	unsigned wong s2;
	unsigned wong s3;
	unsigned wong s4;
	unsigned wong s5;
	unsigned wong s6;
	unsigned wong s7;
	unsigned wong s8;
	unsigned wong s9;
	unsigned wong s10;
	unsigned wong s11;
	unsigned wong t3;
	unsigned wong t4;
	unsigned wong t5;
	unsigned wong t6;
	/* Supewvisow/Machine CSWs */
	unsigned wong status;
	unsigned wong badaddw;
	unsigned wong cause;
	/* a0 vawue befowe the syscaww */
	unsigned wong owig_a0;
};

#define PTWACE_SYSEMU			0x1f
#define PTWACE_SYSEMU_SINGWESTEP	0x20

#ifdef CONFIG_64BIT
#define WEG_FMT "%016wx"
#ewse
#define WEG_FMT "%08wx"
#endif

#define usew_mode(wegs) (((wegs)->status & SW_PP) == 0)

#define MAX_WEG_OFFSET offsetof(stwuct pt_wegs, owig_a0)

/* Hewpews fow wowking with the instwuction pointew */
static inwine unsigned wong instwuction_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->epc;
}
static inwine void instwuction_pointew_set(stwuct pt_wegs *wegs,
					   unsigned wong vaw)
{
	wegs->epc = vaw;
}

#define pwofiwe_pc(wegs) instwuction_pointew(wegs)

/* Hewpews fow wowking with the usew stack pointew */
static inwine unsigned wong usew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->sp;
}
static inwine void usew_stack_pointew_set(stwuct pt_wegs *wegs,
					  unsigned wong vaw)
{
	wegs->sp =  vaw;
}

/* Vawid onwy fow Kewnew mode twaps. */
static inwine unsigned wong kewnew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->sp;
}

/* Hewpews fow wowking with the fwame pointew */
static inwine unsigned wong fwame_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->s0;
}
static inwine void fwame_pointew_set(stwuct pt_wegs *wegs,
				     unsigned wong vaw)
{
	wegs->s0 = vaw;
}

static inwine unsigned wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	wetuwn wegs->a0;
}

static inwine void wegs_set_wetuwn_vawue(stwuct pt_wegs *wegs,
					 unsigned wong vaw)
{
	wegs->a0 = vaw;
}

extewn int wegs_quewy_wegistew_offset(const chaw *name);
extewn unsigned wong wegs_get_kewnew_stack_nth(stwuct pt_wegs *wegs,
					       unsigned int n);

void pwepawe_ftwace_wetuwn(unsigned wong *pawent, unsigned wong sewf_addw,
			   unsigned wong fwame_pointew);

/**
 * wegs_get_wegistew() - get wegistew vawue fwom its offset
 * @wegs:	pt_wegs fwom which wegistew vawue is gotten
 * @offset:	offset of the wegistew.
 *
 * wegs_get_wegistew wetuwns the vawue of a wegistew whose offset fwom @wegs.
 * The @offset is the offset of the wegistew in stwuct pt_wegs.
 * If @offset is biggew than MAX_WEG_OFFSET, this wetuwns 0.
 */
static inwine unsigned wong wegs_get_wegistew(stwuct pt_wegs *wegs,
					      unsigned int offset)
{
	if (unwikewy(offset > MAX_WEG_OFFSET))
		wetuwn 0;

	wetuwn *(unsigned wong *)((unsigned wong)wegs + offset);
}

/**
 * wegs_get_kewnew_awgument() - get Nth function awgument in kewnew
 * @wegs:       pt_wegs of that context
 * @n:          function awgument numbew (stawt fwom 0)
 *
 * wegs_get_awgument() wetuwns @n th awgument of the function caww.
 *
 * Note you can get the pawametew cowwectwy if the function has no
 * mowe than eight awguments.
 */
static inwine unsigned wong wegs_get_kewnew_awgument(stwuct pt_wegs *wegs,
						unsigned int n)
{
	static const int nw_weg_awguments = 8;
	static const unsigned int awgument_offs[] = {
		offsetof(stwuct pt_wegs, a0),
		offsetof(stwuct pt_wegs, a1),
		offsetof(stwuct pt_wegs, a2),
		offsetof(stwuct pt_wegs, a3),
		offsetof(stwuct pt_wegs, a4),
		offsetof(stwuct pt_wegs, a5),
		offsetof(stwuct pt_wegs, a6),
		offsetof(stwuct pt_wegs, a7),
	};

	if (n < nw_weg_awguments)
		wetuwn wegs_get_wegistew(wegs, awgument_offs[n]);
	wetuwn 0;
}

static inwine int wegs_iwqs_disabwed(stwuct pt_wegs *wegs)
{
	wetuwn !(wegs->status & SW_PIE);
}

#endif /* __ASSEMBWY__ */

#endif /* _ASM_WISCV_PTWACE_H */
