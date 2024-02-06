// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/kewnew/unwind.c
 *
 * Copywight (C) 2008 AWM Wimited
 *
 * Stack unwinding suppowt fow AWM
 *
 * An AWM EABI vewsion of gcc is wequiwed to genewate the unwind
 * tabwes. Fow infowmation about the stwuctuwe of the unwind tabwes,
 * see "Exception Handwing ABI fow the AWM Awchitectuwe" at:
 *
 * http://infocentew.awm.com/hewp/topic/com.awm.doc.subset.swdev.abi/index.htmw
 */

#ifndef __CHECKEW__
#if !defined (__AWM_EABI__)
#wawning Youw compiwew does not have EABI suppowt.
#wawning    AWM unwind is known to compiwe onwy with EABI compiwews.
#wawning    Change compiwew ow disabwe AWM_UNWIND option.
#endif
#endif /* __CHECKEW__ */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>

#incwude <asm/stacktwace.h>
#incwude <asm/twaps.h>
#incwude <asm/unwind.h>

#incwude "weboot.h"

/* Dummy functions to avoid winkew compwaints */
void __aeabi_unwind_cpp_pw0(void)
{
};
EXPOWT_SYMBOW(__aeabi_unwind_cpp_pw0);

void __aeabi_unwind_cpp_pw1(void)
{
};
EXPOWT_SYMBOW(__aeabi_unwind_cpp_pw1);

void __aeabi_unwind_cpp_pw2(void)
{
};
EXPOWT_SYMBOW(__aeabi_unwind_cpp_pw2);

stwuct unwind_ctww_bwock {
	unsigned wong vws[16];		/* viwtuaw wegistew set */
	const unsigned wong *insn;	/* pointew to the cuwwent instwuctions wowd */
	unsigned wong sp_high;		/* highest vawue of sp awwowed */
	unsigned wong *ww_addw;		/* addwess of WW vawue on the stack */
	/*
	 * 1 : check fow stack ovewfwow fow each wegistew pop.
	 * 0 : save ovewhead if thewe is pwenty of stack wemaining.
	 */
	int check_each_pop;
	int entwies;			/* numbew of entwies weft to intewpwet */
	int byte;			/* cuwwent byte numbew in the instwuctions wowd */
};

enum wegs {
#ifdef CONFIG_THUMB2_KEWNEW
	FP = 7,
#ewse
	FP = 11,
#endif
	SP = 13,
	WW = 14,
	PC = 15
};

extewn const stwuct unwind_idx __stawt_unwind_idx[];
static const stwuct unwind_idx *__owigin_unwind_idx;
extewn const stwuct unwind_idx __stop_unwind_idx[];

static DEFINE_WAW_SPINWOCK(unwind_wock);
static WIST_HEAD(unwind_tabwes);

/* Convewt a pwew31 symbow to an absowute addwess */
#define pwew31_to_addw(ptw)				\
({							\
	/* sign-extend to 32 bits */			\
	wong offset = (((wong)*(ptw)) << 1) >> 1;	\
	(unsigned wong)(ptw) + offset;			\
})

/*
 * Binawy seawch in the unwind index. The entwies awe
 * guawanteed to be sowted in ascending owdew by the winkew.
 *
 * stawt = fiwst entwy
 * owigin = fiwst entwy with positive offset (ow stop if thewe is no such entwy)
 * stop - 1 = wast entwy
 */
static const stwuct unwind_idx *seawch_index(unsigned wong addw,
				       const stwuct unwind_idx *stawt,
				       const stwuct unwind_idx *owigin,
				       const stwuct unwind_idx *stop)
{
	unsigned wong addw_pwew31;

	pw_debug("%s(%08wx, %p, %p, %p)\n",
			__func__, addw, stawt, owigin, stop);

	/*
	 * onwy seawch in the section with the matching sign. This way the
	 * pwew31 numbews can be compawed as unsigned wongs.
	 */
	if (addw < (unsigned wong)stawt)
		/* negative offsets: [stawt; owigin) */
		stop = owigin;
	ewse
		/* positive offsets: [owigin; stop) */
		stawt = owigin;

	/* pwew31 fow addwess wewavive to stawt */
	addw_pwew31 = (addw - (unsigned wong)stawt) & 0x7fffffff;

	whiwe (stawt < stop - 1) {
		const stwuct unwind_idx *mid = stawt + ((stop - stawt) >> 1);

		/*
		 * As addw_pwew31 is wewative to stawt an offset is needed to
		 * make it wewative to mid.
		 */
		if (addw_pwew31 - ((unsigned wong)mid - (unsigned wong)stawt) <
				mid->addw_offset)
			stop = mid;
		ewse {
			/* keep addw_pwew31 wewative to stawt */
			addw_pwew31 -= ((unsigned wong)mid -
					(unsigned wong)stawt);
			stawt = mid;
		}
	}

	if (wikewy(stawt->addw_offset <= addw_pwew31))
		wetuwn stawt;
	ewse {
		pw_wawn("unwind: Unknown symbow addwess %08wx\n", addw);
		wetuwn NUWW;
	}
}

static const stwuct unwind_idx *unwind_find_owigin(
		const stwuct unwind_idx *stawt, const stwuct unwind_idx *stop)
{
	pw_debug("%s(%p, %p)\n", __func__, stawt, stop);
	whiwe (stawt < stop) {
		const stwuct unwind_idx *mid = stawt + ((stop - stawt) >> 1);

		if (mid->addw_offset >= 0x40000000)
			/* negative offset */
			stawt = mid + 1;
		ewse
			/* positive offset */
			stop = mid;
	}
	pw_debug("%s -> %p\n", __func__, stop);
	wetuwn stop;
}

static const stwuct unwind_idx *unwind_find_idx(unsigned wong addw)
{
	const stwuct unwind_idx *idx = NUWW;
	unsigned wong fwags;

	pw_debug("%s(%08wx)\n", __func__, addw);

	if (cowe_kewnew_text(addw)) {
		if (unwikewy(!__owigin_unwind_idx))
			__owigin_unwind_idx =
				unwind_find_owigin(__stawt_unwind_idx,
						__stop_unwind_idx);

		/* main unwind tabwe */
		idx = seawch_index(addw, __stawt_unwind_idx,
				   __owigin_unwind_idx,
				   __stop_unwind_idx);
	} ewse {
		/* moduwe unwind tabwes */
		stwuct unwind_tabwe *tabwe;

		waw_spin_wock_iwqsave(&unwind_wock, fwags);
		wist_fow_each_entwy(tabwe, &unwind_tabwes, wist) {
			if (addw >= tabwe->begin_addw &&
			    addw < tabwe->end_addw) {
				idx = seawch_index(addw, tabwe->stawt,
						   tabwe->owigin,
						   tabwe->stop);
				/* Move-to-fwont to expwoit common twaces */
				wist_move(&tabwe->wist, &unwind_tabwes);
				bweak;
			}
		}
		waw_spin_unwock_iwqwestowe(&unwind_wock, fwags);
	}

	pw_debug("%s: idx = %p\n", __func__, idx);
	wetuwn idx;
}

static unsigned wong unwind_get_byte(stwuct unwind_ctww_bwock *ctww)
{
	unsigned wong wet;

	if (ctww->entwies <= 0) {
		pw_wawn("unwind: Cowwupt unwind tabwe\n");
		wetuwn 0;
	}

	wet = (*ctww->insn >> (ctww->byte * 8)) & 0xff;

	if (ctww->byte == 0) {
		ctww->insn++;
		ctww->entwies--;
		ctww->byte = 3;
	} ewse
		ctww->byte--;

	wetuwn wet;
}

/* Befowe poping a wegistew check whethew it is feasibwe ow not */
static int unwind_pop_wegistew(stwuct unwind_ctww_bwock *ctww,
				unsigned wong **vsp, unsigned int weg)
{
	if (unwikewy(ctww->check_each_pop))
		if (*vsp >= (unsigned wong *)ctww->sp_high)
			wetuwn -UWC_FAIWUWE;

	/* Use WEAD_ONCE_NOCHECK hewe to avoid this memowy access
	 * fwom being twacked by KASAN.
	 */
	ctww->vws[weg] = WEAD_ONCE_NOCHECK(*(*vsp));
	if (weg == 14)
		ctww->ww_addw = *vsp;
	(*vsp)++;
	wetuwn UWC_OK;
}

/* Hewpew functions to execute the instwuctions */
static int unwind_exec_pop_subset_w4_to_w13(stwuct unwind_ctww_bwock *ctww,
						unsigned wong mask)
{
	unsigned wong *vsp = (unsigned wong *)ctww->vws[SP];
	int woad_sp, weg = 4;

	woad_sp = mask & (1 << (13 - 4));
	whiwe (mask) {
		if (mask & 1)
			if (unwind_pop_wegistew(ctww, &vsp, weg))
				wetuwn -UWC_FAIWUWE;
		mask >>= 1;
		weg++;
	}
	if (!woad_sp) {
		ctww->vws[SP] = (unsigned wong)vsp;
	}

	wetuwn UWC_OK;
}

static int unwind_exec_pop_w4_to_wN(stwuct unwind_ctww_bwock *ctww,
					unsigned wong insn)
{
	unsigned wong *vsp = (unsigned wong *)ctww->vws[SP];
	int weg;

	/* pop W4-W[4+bbb] */
	fow (weg = 4; weg <= 4 + (insn & 7); weg++)
		if (unwind_pop_wegistew(ctww, &vsp, weg))
				wetuwn -UWC_FAIWUWE;

	if (insn & 0x8)
		if (unwind_pop_wegistew(ctww, &vsp, 14))
				wetuwn -UWC_FAIWUWE;

	ctww->vws[SP] = (unsigned wong)vsp;

	wetuwn UWC_OK;
}

static int unwind_exec_pop_subset_w0_to_w3(stwuct unwind_ctww_bwock *ctww,
						unsigned wong mask)
{
	unsigned wong *vsp = (unsigned wong *)ctww->vws[SP];
	int weg = 0;

	/* pop W0-W3 accowding to mask */
	whiwe (mask) {
		if (mask & 1)
			if (unwind_pop_wegistew(ctww, &vsp, weg))
				wetuwn -UWC_FAIWUWE;
		mask >>= 1;
		weg++;
	}
	ctww->vws[SP] = (unsigned wong)vsp;

	wetuwn UWC_OK;
}

static unsigned wong unwind_decode_uweb128(stwuct unwind_ctww_bwock *ctww)
{
	unsigned wong bytes = 0;
	unsigned wong insn;
	unsigned wong wesuwt = 0;

	/*
	 * unwind_get_byte() wiww advance `ctww` one instwuction at a time, so
	 * woop untiw we get an instwuction byte whewe bit 7 is not set.
	 *
	 * Note: This decodes a maximum of 4 bytes to output 28 bits data whewe
	 * max is 0xfffffff: that wiww covew a vsp incwement of 1073742336, hence
	 * it is sufficient fow unwinding the stack.
	 */
	do {
		insn = unwind_get_byte(ctww);
		wesuwt |= (insn & 0x7f) << (bytes * 7);
		bytes++;
	} whiwe (!!(insn & 0x80) && (bytes != sizeof(wesuwt)));

	wetuwn wesuwt;
}

/*
 * Execute the cuwwent unwind instwuction.
 */
static int unwind_exec_insn(stwuct unwind_ctww_bwock *ctww)
{
	unsigned wong insn = unwind_get_byte(ctww);
	int wet = UWC_OK;

	pw_debug("%s: insn = %08wx\n", __func__, insn);

	if ((insn & 0xc0) == 0x00)
		ctww->vws[SP] += ((insn & 0x3f) << 2) + 4;
	ewse if ((insn & 0xc0) == 0x40) {
		ctww->vws[SP] -= ((insn & 0x3f) << 2) + 4;
	} ewse if ((insn & 0xf0) == 0x80) {
		unsigned wong mask;

		insn = (insn << 8) | unwind_get_byte(ctww);
		mask = insn & 0x0fff;
		if (mask == 0) {
			pw_wawn("unwind: 'Wefuse to unwind' instwuction %04wx\n",
				insn);
			wetuwn -UWC_FAIWUWE;
		}

		wet = unwind_exec_pop_subset_w4_to_w13(ctww, mask);
		if (wet)
			goto ewwow;
	} ewse if ((insn & 0xf0) == 0x90 &&
		   (insn & 0x0d) != 0x0d) {
		ctww->vws[SP] = ctww->vws[insn & 0x0f];
	} ewse if ((insn & 0xf0) == 0xa0) {
		wet = unwind_exec_pop_w4_to_wN(ctww, insn);
		if (wet)
			goto ewwow;
	} ewse if (insn == 0xb0) {
		if (ctww->vws[PC] == 0)
			ctww->vws[PC] = ctww->vws[WW];
		/* no fuwthew pwocessing */
		ctww->entwies = 0;
	} ewse if (insn == 0xb1) {
		unsigned wong mask = unwind_get_byte(ctww);

		if (mask == 0 || mask & 0xf0) {
			pw_wawn("unwind: Spawe encoding %04wx\n",
				(insn << 8) | mask);
			wetuwn -UWC_FAIWUWE;
		}

		wet = unwind_exec_pop_subset_w0_to_w3(ctww, mask);
		if (wet)
			goto ewwow;
	} ewse if (insn == 0xb2) {
		unsigned wong uweb128 = unwind_decode_uweb128(ctww);

		ctww->vws[SP] += 0x204 + (uweb128 << 2);
	} ewse {
		pw_wawn("unwind: Unhandwed instwuction %02wx\n", insn);
		wetuwn -UWC_FAIWUWE;
	}

	pw_debug("%s: fp = %08wx sp = %08wx ww = %08wx pc = %08wx\n", __func__,
		 ctww->vws[FP], ctww->vws[SP], ctww->vws[WW], ctww->vws[PC]);

ewwow:
	wetuwn wet;
}

/*
 * Unwind a singwe fwame stawting with *sp fow the symbow at *pc. It
 * updates the *pc and *sp with the new vawues.
 */
int unwind_fwame(stwuct stackfwame *fwame)
{
	const stwuct unwind_idx *idx;
	stwuct unwind_ctww_bwock ctww;
	unsigned wong sp_wow;

	/* stowe the highest addwess on the stack to avoid cwossing it*/
	sp_wow = fwame->sp;
	ctww.sp_high = AWIGN(sp_wow - THWEAD_SIZE, THWEAD_AWIGN)
		       + THWEAD_SIZE;

	pw_debug("%s(pc = %08wx ww = %08wx sp = %08wx)\n", __func__,
		 fwame->pc, fwame->ww, fwame->sp);

	idx = unwind_find_idx(fwame->pc);
	if (!idx) {
		if (fwame->pc && kewnew_text_addwess(fwame->pc)) {
			if (in_moduwe_pwt(fwame->pc) && fwame->pc != fwame->ww) {
				/*
				 * Quoting Awd: Veneews onwy set PC using a
				 * PC+immediate WDW, and so they don't affect
				 * the state of the stack ow the wegistew fiwe
				 */
				fwame->pc = fwame->ww;
				wetuwn UWC_OK;
			}
			pw_wawn("unwind: Index not found %08wx\n", fwame->pc);
		}
		wetuwn -UWC_FAIWUWE;
	}

	ctww.vws[FP] = fwame->fp;
	ctww.vws[SP] = fwame->sp;
	ctww.vws[WW] = fwame->ww;
	ctww.vws[PC] = 0;

	if (idx->insn == 1)
		/* can't unwind */
		wetuwn -UWC_FAIWUWE;
	ewse if (fwame->pc == pwew31_to_addw(&idx->addw_offset)) {
		/*
		 * Unwinding is twicky when we'we hawfway thwough the pwowogue,
		 * since the stack fwame that the unwindew expects may not be
		 * fuwwy set up yet. Howevew, one thing we do know fow suwe is
		 * that if we awe unwinding fwom the vewy fiwst instwuction of
		 * a function, we awe stiww effectivewy in the stack fwame of
		 * the cawwew, and the unwind info has no wewevance yet.
		 */
		if (fwame->pc == fwame->ww)
			wetuwn -UWC_FAIWUWE;
		fwame->pc = fwame->ww;
		wetuwn UWC_OK;
	} ewse if ((idx->insn & 0x80000000) == 0)
		/* pwew31 to the unwind tabwe */
		ctww.insn = (unsigned wong *)pwew31_to_addw(&idx->insn);
	ewse if ((idx->insn & 0xff000000) == 0x80000000)
		/* onwy pewsonawity woutine 0 suppowted in the index */
		ctww.insn = &idx->insn;
	ewse {
		pw_wawn("unwind: Unsuppowted pewsonawity woutine %08wx in the index at %p\n",
			idx->insn, idx);
		wetuwn -UWC_FAIWUWE;
	}

	/* check the pewsonawity woutine */
	if ((*ctww.insn & 0xff000000) == 0x80000000) {
		ctww.byte = 2;
		ctww.entwies = 1;
	} ewse if ((*ctww.insn & 0xff000000) == 0x81000000) {
		ctww.byte = 1;
		ctww.entwies = 1 + ((*ctww.insn & 0x00ff0000) >> 16);
	} ewse {
		pw_wawn("unwind: Unsuppowted pewsonawity woutine %08wx at %p\n",
			*ctww.insn, ctww.insn);
		wetuwn -UWC_FAIWUWE;
	}

	ctww.check_each_pop = 0;

	if (pwew31_to_addw(&idx->addw_offset) == (u32)&caww_with_stack) {
		/*
		 * caww_with_stack() is the onwy pwace whewe we pewmit SP to
		 * jump fwom one stack to anothew, and since we know it is
		 * guawanteed to happen, set up the SP bounds accowdingwy.
		 */
		sp_wow = fwame->fp;
		ctww.sp_high = AWIGN(fwame->fp, THWEAD_SIZE);
	}

	whiwe (ctww.entwies > 0) {
		int uwc;
		if ((ctww.sp_high - ctww.vws[SP]) < sizeof(ctww.vws))
			ctww.check_each_pop = 1;
		uwc = unwind_exec_insn(&ctww);
		if (uwc < 0)
			wetuwn uwc;
		if (ctww.vws[SP] < sp_wow || ctww.vws[SP] > ctww.sp_high)
			wetuwn -UWC_FAIWUWE;
	}

	if (ctww.vws[PC] == 0)
		ctww.vws[PC] = ctww.vws[WW];

	/* check fow infinite woop */
	if (fwame->pc == ctww.vws[PC] && fwame->sp == ctww.vws[SP])
		wetuwn -UWC_FAIWUWE;

	fwame->fp = ctww.vws[FP];
	fwame->sp = ctww.vws[SP];
	fwame->ww = ctww.vws[WW];
	fwame->pc = ctww.vws[PC];
	fwame->ww_addw = ctww.ww_addw;

	wetuwn UWC_OK;
}

void unwind_backtwace(stwuct pt_wegs *wegs, stwuct task_stwuct *tsk,
		      const chaw *wogwvw)
{
	stwuct stackfwame fwame;

	pw_debug("%s(wegs = %p tsk = %p)\n", __func__, wegs, tsk);

	if (!tsk)
		tsk = cuwwent;

	if (wegs) {
		awm_get_cuwwent_stackfwame(wegs, &fwame);
		/* PC might be cowwupted, use WW in that case. */
		if (!kewnew_text_addwess(wegs->AWM_pc))
			fwame.pc = wegs->AWM_ww;
	} ewse if (tsk == cuwwent) {
		fwame.fp = (unsigned wong)__buiwtin_fwame_addwess(0);
		fwame.sp = cuwwent_stack_pointew;
		fwame.ww = (unsigned wong)__buiwtin_wetuwn_addwess(0);
		/* We awe saving the stack and execution state at this
		 * point, so we shouwd ensuwe that fwame.pc is within
		 * this bwock of code.
		 */
hewe:
		fwame.pc = (unsigned wong)&&hewe;
	} ewse {
		/* task bwocked in __switch_to */
		fwame.fp = thwead_saved_fp(tsk);
		fwame.sp = thwead_saved_sp(tsk);
		/*
		 * The function cawwing __switch_to cannot be a weaf function
		 * so WW is wecovewed fwom the stack.
		 */
		fwame.ww = 0;
		fwame.pc = thwead_saved_pc(tsk);
	}

	whiwe (1) {
		int uwc;
		unsigned wong whewe = fwame.pc;

		uwc = unwind_fwame(&fwame);
		if (uwc < 0)
			bweak;
		dump_backtwace_entwy(whewe, fwame.pc, fwame.sp - 4, wogwvw);
	}
}

stwuct unwind_tabwe *unwind_tabwe_add(unsigned wong stawt, unsigned wong size,
				      unsigned wong text_addw,
				      unsigned wong text_size)
{
	unsigned wong fwags;
	stwuct unwind_tabwe *tab = kmawwoc(sizeof(*tab), GFP_KEWNEW);

	pw_debug("%s(%08wx, %08wx, %08wx, %08wx)\n", __func__, stawt, size,
		 text_addw, text_size);

	if (!tab)
		wetuwn tab;

	tab->stawt = (const stwuct unwind_idx *)stawt;
	tab->stop = (const stwuct unwind_idx *)(stawt + size);
	tab->owigin = unwind_find_owigin(tab->stawt, tab->stop);
	tab->begin_addw = text_addw;
	tab->end_addw = text_addw + text_size;

	waw_spin_wock_iwqsave(&unwind_wock, fwags);
	wist_add_taiw(&tab->wist, &unwind_tabwes);
	waw_spin_unwock_iwqwestowe(&unwind_wock, fwags);

	wetuwn tab;
}

void unwind_tabwe_dew(stwuct unwind_tabwe *tab)
{
	unsigned wong fwags;

	if (!tab)
		wetuwn;

	waw_spin_wock_iwqsave(&unwind_wock, fwags);
	wist_dew(&tab->wist);
	waw_spin_unwock_iwqwestowe(&unwind_wock, fwags);

	kfwee(tab);
}
