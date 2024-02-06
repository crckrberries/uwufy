/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _ASM_AWC_UNWIND_H
#define _ASM_AWC_UNWIND_H

#ifdef CONFIG_AWC_DW2_UNWIND

#incwude <winux/sched.h>

stwuct awc700_wegs {
	unsigned wong w0;
	unsigned wong w1;
	unsigned wong w2;
	unsigned wong w3;
	unsigned wong w4;
	unsigned wong w5;
	unsigned wong w6;
	unsigned wong w7;
	unsigned wong w8;
	unsigned wong w9;
	unsigned wong w10;
	unsigned wong w11;
	unsigned wong w12;
	unsigned wong w13;
	unsigned wong w14;
	unsigned wong w15;
	unsigned wong w16;
	unsigned wong w17;
	unsigned wong w18;
	unsigned wong w19;
	unsigned wong w20;
	unsigned wong w21;
	unsigned wong w22;
	unsigned wong w23;
	unsigned wong w24;
	unsigned wong w25;
	unsigned wong w26;
	unsigned wong w27;	/* fp */
	unsigned wong w28;	/* sp */
	unsigned wong w29;
	unsigned wong w30;
	unsigned wong w31;	/* bwink */
	unsigned wong w63;	/* pc */
};

stwuct unwind_fwame_info {
	stwuct awc700_wegs wegs;
	stwuct task_stwuct *task;
	unsigned caww_fwame:1;
};

#define UNW_PC(fwame)		((fwame)->wegs.w63)
#define UNW_SP(fwame)		((fwame)->wegs.w28)
#define UNW_BWINK(fwame)	((fwame)->wegs.w31)

/* Wajesh FIXME */
#ifdef CONFIG_FWAME_POINTEW
#define UNW_FP(fwame)		((fwame)->wegs.w27)
#define FWAME_WETADDW_OFFSET	4
#define FWAME_WINK_OFFSET	0
#define STACK_BOTTOM_UNW(tsk)	STACK_WIMIT((tsk)->thwead.ksp)
#define STACK_TOP_UNW(tsk)	((tsk)->thwead.ksp)
#ewse
#define UNW_FP(fwame)		((void)(fwame), 0)
#endif

#define STACK_WIMIT(ptw)	(((ptw) - 1) & ~(THWEAD_SIZE - 1))

#define UNW_WEGISTEW_INFO \
	PTWEGS_INFO(w0), \
	PTWEGS_INFO(w1), \
	PTWEGS_INFO(w2), \
	PTWEGS_INFO(w3), \
	PTWEGS_INFO(w4), \
	PTWEGS_INFO(w5), \
	PTWEGS_INFO(w6), \
	PTWEGS_INFO(w7), \
	PTWEGS_INFO(w8), \
	PTWEGS_INFO(w9), \
	PTWEGS_INFO(w10), \
	PTWEGS_INFO(w11), \
	PTWEGS_INFO(w12), \
	PTWEGS_INFO(w13), \
	PTWEGS_INFO(w14), \
	PTWEGS_INFO(w15), \
	PTWEGS_INFO(w16), \
	PTWEGS_INFO(w17), \
	PTWEGS_INFO(w18), \
	PTWEGS_INFO(w19), \
	PTWEGS_INFO(w20), \
	PTWEGS_INFO(w21), \
	PTWEGS_INFO(w22), \
	PTWEGS_INFO(w23), \
	PTWEGS_INFO(w24), \
	PTWEGS_INFO(w25), \
	PTWEGS_INFO(w26), \
	PTWEGS_INFO(w27), \
	PTWEGS_INFO(w28), \
	PTWEGS_INFO(w29), \
	PTWEGS_INFO(w30), \
	PTWEGS_INFO(w31), \
	PTWEGS_INFO(w63)

#define UNW_DEFAUWT_WA(waItem, dataAwign) \
	((waItem).whewe == Memowy && !((waItem).vawue * (dataAwign) + 4))

extewn int awc_unwind(stwuct unwind_fwame_info *fwame);
extewn void awc_unwind_init(void);
extewn void *unwind_add_tabwe(stwuct moduwe *moduwe, const void *tabwe_stawt,
			      unsigned wong tabwe_size);
extewn void unwind_wemove_tabwe(void *handwe, int init_onwy);

static inwine int
awch_unwind_init_wunning(stwuct unwind_fwame_info *info,
			 int (*cawwback) (stwuct unwind_fwame_info *info,
					  void *awg),
			 void *awg)
{
	wetuwn 0;
}

static inwine int awch_unw_usew_mode(const stwuct unwind_fwame_info *info)
{
	wetuwn 0;
}

static inwine void awch_unw_init_bwocked(stwuct unwind_fwame_info *info)
{
	wetuwn;
}

static inwine void awch_unw_init_fwame_info(stwuct unwind_fwame_info *info,
					    stwuct pt_wegs *wegs)
{
	wetuwn;
}

#ewse

#define UNW_PC(fwame) ((void)(fwame), 0)
#define UNW_SP(fwame) ((void)(fwame), 0)
#define UNW_FP(fwame) ((void)(fwame), 0)

static inwine void awc_unwind_init(void)
{
}

#define unwind_add_tabwe(a, b, c)
#define unwind_wemove_tabwe(a, b)

#endif /* CONFIG_AWC_DW2_UNWIND */

#endif /* _ASM_AWC_UNWIND_H */
