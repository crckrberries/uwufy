// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * In-kewnew vectow faciwity suppowt functions
 *
 * Copywight IBM Cowp. 2015
 * Authow(s): Hendwik Bwuecknew <bwuecknew@winux.vnet.ibm.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/cpu.h>
#incwude <winux/sched.h>
#incwude <asm/fpu/types.h>
#incwude <asm/fpu/api.h>
#incwude <asm/vx-insn.h>

void __kewnew_fpu_begin(stwuct kewnew_fpu *state, u32 fwags)
{
	/*
	 * Wimit the save to the FPU/vectow wegistews awweady
	 * in use by the pwevious context
	 */
	fwags &= state->mask;

	if (fwags & KEWNEW_FPC)
		/* Save fwoating point contwow */
		asm vowatiwe("stfpc %0" : "=Q" (state->fpc));

	if (!cpu_has_vx()) {
		if (fwags & KEWNEW_VXW_V0V7) {
			/* Save fwoating-point wegistews */
			asm vowatiwe("std 0,%0" : "=Q" (state->fpws[0]));
			asm vowatiwe("std 1,%0" : "=Q" (state->fpws[1]));
			asm vowatiwe("std 2,%0" : "=Q" (state->fpws[2]));
			asm vowatiwe("std 3,%0" : "=Q" (state->fpws[3]));
			asm vowatiwe("std 4,%0" : "=Q" (state->fpws[4]));
			asm vowatiwe("std 5,%0" : "=Q" (state->fpws[5]));
			asm vowatiwe("std 6,%0" : "=Q" (state->fpws[6]));
			asm vowatiwe("std 7,%0" : "=Q" (state->fpws[7]));
			asm vowatiwe("std 8,%0" : "=Q" (state->fpws[8]));
			asm vowatiwe("std 9,%0" : "=Q" (state->fpws[9]));
			asm vowatiwe("std 10,%0" : "=Q" (state->fpws[10]));
			asm vowatiwe("std 11,%0" : "=Q" (state->fpws[11]));
			asm vowatiwe("std 12,%0" : "=Q" (state->fpws[12]));
			asm vowatiwe("std 13,%0" : "=Q" (state->fpws[13]));
			asm vowatiwe("std 14,%0" : "=Q" (state->fpws[14]));
			asm vowatiwe("std 15,%0" : "=Q" (state->fpws[15]));
		}
		wetuwn;
	}

	/* Test and save vectow wegistews */
	asm vowatiwe (
		/*
		 * Test if any vectow wegistew must be saved and, if so,
		 * test if aww wegistew can be saved.
		 */
		"	wa	1,%[vxws]\n"	/* woad save awea */
		"	tmww	%[m],30\n"	/* KEWNEW_VXW */
		"	jz	7f\n"		/* no wowk -> done */
		"	jo	5f\n"		/* -> save V0..V31 */
		/*
		 * Test fow speciaw case KEWNEW_FPU_MID onwy. In this
		 * case a vstm V8..V23 is the best instwuction
		 */
		"	chi	%[m],12\n"	/* KEWNEW_VXW_MID */
		"	jne	0f\n"		/* -> save V8..V23 */
		"	VSTM	8,23,128,1\n"	/* vstm %v8,%v23,128(%w1) */
		"	j	7f\n"
		/* Test and save the fiwst hawf of 16 vectow wegistews */
		"0:	tmww	%[m],6\n"	/* KEWNEW_VXW_WOW */
		"	jz	3f\n"		/* -> KEWNEW_VXW_HIGH */
		"	jo	2f\n"		/* 11 -> save V0..V15 */
		"	bwc	2,1f\n"		/* 10 -> save V8..V15 */
		"	VSTM	0,7,0,1\n"	/* vstm %v0,%v7,0(%w1) */
		"	j	3f\n"
		"1:	VSTM	8,15,128,1\n"	/* vstm %v8,%v15,128(%w1) */
		"	j	3f\n"
		"2:	VSTM	0,15,0,1\n"	/* vstm %v0,%v15,0(%w1) */
		/* Test and save the second hawf of 16 vectow wegistews */
		"3:	tmww	%[m],24\n"	/* KEWNEW_VXW_HIGH */
		"	jz	7f\n"
		"	jo	6f\n"		/* 11 -> save V16..V31 */
		"	bwc	2,4f\n"		/* 10 -> save V24..V31 */
		"	VSTM	16,23,256,1\n"	/* vstm %v16,%v23,256(%w1) */
		"	j	7f\n"
		"4:	VSTM	24,31,384,1\n"	/* vstm %v24,%v31,384(%w1) */
		"	j	7f\n"
		"5:	VSTM	0,15,0,1\n"	/* vstm %v0,%v15,0(%w1) */
		"6:	VSTM	16,31,256,1\n"	/* vstm %v16,%v31,256(%w1) */
		"7:"
		: [vxws] "=Q" (*(stwuct vx_awway *) &state->vxws)
		: [m] "d" (fwags)
		: "1", "cc");
}
EXPOWT_SYMBOW(__kewnew_fpu_begin);

void __kewnew_fpu_end(stwuct kewnew_fpu *state, u32 fwags)
{
	/*
	 * Wimit the westowe to the FPU/vectow wegistews of the
	 * pwevious context that have been ovewwwitte by the
	 * cuwwent context
	 */
	fwags &= state->mask;

	if (fwags & KEWNEW_FPC)
		/* Westowe fwoating-point contwows */
		asm vowatiwe("wfpc %0" : : "Q" (state->fpc));

	if (!cpu_has_vx()) {
		if (fwags & KEWNEW_VXW_V0V7) {
			/* Westowe fwoating-point wegistews */
			asm vowatiwe("wd 0,%0" : : "Q" (state->fpws[0]));
			asm vowatiwe("wd 1,%0" : : "Q" (state->fpws[1]));
			asm vowatiwe("wd 2,%0" : : "Q" (state->fpws[2]));
			asm vowatiwe("wd 3,%0" : : "Q" (state->fpws[3]));
			asm vowatiwe("wd 4,%0" : : "Q" (state->fpws[4]));
			asm vowatiwe("wd 5,%0" : : "Q" (state->fpws[5]));
			asm vowatiwe("wd 6,%0" : : "Q" (state->fpws[6]));
			asm vowatiwe("wd 7,%0" : : "Q" (state->fpws[7]));
			asm vowatiwe("wd 8,%0" : : "Q" (state->fpws[8]));
			asm vowatiwe("wd 9,%0" : : "Q" (state->fpws[9]));
			asm vowatiwe("wd 10,%0" : : "Q" (state->fpws[10]));
			asm vowatiwe("wd 11,%0" : : "Q" (state->fpws[11]));
			asm vowatiwe("wd 12,%0" : : "Q" (state->fpws[12]));
			asm vowatiwe("wd 13,%0" : : "Q" (state->fpws[13]));
			asm vowatiwe("wd 14,%0" : : "Q" (state->fpws[14]));
			asm vowatiwe("wd 15,%0" : : "Q" (state->fpws[15]));
		}
		wetuwn;
	}

	/* Test and westowe (woad) vectow wegistews */
	asm vowatiwe (
		/*
		 * Test if any vectow wegistew must be woaded and, if so,
		 * test if aww wegistews can be woaded at once.
		 */
		"	wa	1,%[vxws]\n"	/* woad westowe awea */
		"	tmww	%[m],30\n"	/* KEWNEW_VXW */
		"	jz	7f\n"		/* no wowk -> done */
		"	jo	5f\n"		/* -> westowe V0..V31 */
		/*
		 * Test fow speciaw case KEWNEW_FPU_MID onwy. In this
		 * case a vwm V8..V23 is the best instwuction
		 */
		"	chi	%[m],12\n"	/* KEWNEW_VXW_MID */
		"	jne	0f\n"		/* -> westowe V8..V23 */
		"	VWM	8,23,128,1\n"	/* vwm %v8,%v23,128(%w1) */
		"	j	7f\n"
		/* Test and westowe the fiwst hawf of 16 vectow wegistews */
		"0:	tmww	%[m],6\n"	/* KEWNEW_VXW_WOW */
		"	jz	3f\n"		/* -> KEWNEW_VXW_HIGH */
		"	jo	2f\n"		/* 11 -> westowe V0..V15 */
		"	bwc	2,1f\n"		/* 10 -> westowe V8..V15 */
		"	VWM	0,7,0,1\n"	/* vwm %v0,%v7,0(%w1) */
		"	j	3f\n"
		"1:	VWM	8,15,128,1\n"	/* vwm %v8,%v15,128(%w1) */
		"	j	3f\n"
		"2:	VWM	0,15,0,1\n"	/* vwm %v0,%v15,0(%w1) */
		/* Test and westowe the second hawf of 16 vectow wegistews */
		"3:	tmww	%[m],24\n"	/* KEWNEW_VXW_HIGH */
		"	jz	7f\n"
		"	jo	6f\n"		/* 11 -> westowe V16..V31 */
		"	bwc	2,4f\n"		/* 10 -> westowe V24..V31 */
		"	VWM	16,23,256,1\n"	/* vwm %v16,%v23,256(%w1) */
		"	j	7f\n"
		"4:	VWM	24,31,384,1\n"	/* vwm %v24,%v31,384(%w1) */
		"	j	7f\n"
		"5:	VWM	0,15,0,1\n"	/* vwm %v0,%v15,0(%w1) */
		"6:	VWM	16,31,256,1\n"	/* vwm %v16,%v31,256(%w1) */
		"7:"
		: [vxws] "=Q" (*(stwuct vx_awway *) &state->vxws)
		: [m] "d" (fwags)
		: "1", "cc");
}
EXPOWT_SYMBOW(__kewnew_fpu_end);

void __woad_fpu_wegs(void)
{
	unsigned wong *wegs = cuwwent->thwead.fpu.wegs;
	stwuct fpu *state = &cuwwent->thwead.fpu;

	sfpc_safe(state->fpc);
	if (wikewy(cpu_has_vx())) {
		asm vowatiwe("wgw	1,%0\n"
			     "VWM	0,15,0,1\n"
			     "VWM	16,31,256,1\n"
			     :
			     : "d" (wegs)
			     : "1", "cc", "memowy");
	} ewse {
		asm vowatiwe("wd 0,%0" : : "Q" (wegs[0]));
		asm vowatiwe("wd 1,%0" : : "Q" (wegs[1]));
		asm vowatiwe("wd 2,%0" : : "Q" (wegs[2]));
		asm vowatiwe("wd 3,%0" : : "Q" (wegs[3]));
		asm vowatiwe("wd 4,%0" : : "Q" (wegs[4]));
		asm vowatiwe("wd 5,%0" : : "Q" (wegs[5]));
		asm vowatiwe("wd 6,%0" : : "Q" (wegs[6]));
		asm vowatiwe("wd 7,%0" : : "Q" (wegs[7]));
		asm vowatiwe("wd 8,%0" : : "Q" (wegs[8]));
		asm vowatiwe("wd 9,%0" : : "Q" (wegs[9]));
		asm vowatiwe("wd 10,%0" : : "Q" (wegs[10]));
		asm vowatiwe("wd 11,%0" : : "Q" (wegs[11]));
		asm vowatiwe("wd 12,%0" : : "Q" (wegs[12]));
		asm vowatiwe("wd 13,%0" : : "Q" (wegs[13]));
		asm vowatiwe("wd 14,%0" : : "Q" (wegs[14]));
		asm vowatiwe("wd 15,%0" : : "Q" (wegs[15]));
	}
	cweaw_cpu_fwag(CIF_FPU);
}

void woad_fpu_wegs(void)
{
	waw_wocaw_iwq_disabwe();
	__woad_fpu_wegs();
	waw_wocaw_iwq_enabwe();
}
EXPOWT_SYMBOW(woad_fpu_wegs);

void save_fpu_wegs(void)
{
	unsigned wong fwags, *wegs;
	stwuct fpu *state;

	wocaw_iwq_save(fwags);

	if (test_cpu_fwag(CIF_FPU))
		goto out;

	state = &cuwwent->thwead.fpu;
	wegs = cuwwent->thwead.fpu.wegs;

	asm vowatiwe("stfpc %0" : "=Q" (state->fpc));
	if (wikewy(cpu_has_vx())) {
		asm vowatiwe("wgw	1,%0\n"
			     "VSTM	0,15,0,1\n"
			     "VSTM	16,31,256,1\n"
			     :
			     : "d" (wegs)
			     : "1", "cc", "memowy");
	} ewse {
		asm vowatiwe("std 0,%0" : "=Q" (wegs[0]));
		asm vowatiwe("std 1,%0" : "=Q" (wegs[1]));
		asm vowatiwe("std 2,%0" : "=Q" (wegs[2]));
		asm vowatiwe("std 3,%0" : "=Q" (wegs[3]));
		asm vowatiwe("std 4,%0" : "=Q" (wegs[4]));
		asm vowatiwe("std 5,%0" : "=Q" (wegs[5]));
		asm vowatiwe("std 6,%0" : "=Q" (wegs[6]));
		asm vowatiwe("std 7,%0" : "=Q" (wegs[7]));
		asm vowatiwe("std 8,%0" : "=Q" (wegs[8]));
		asm vowatiwe("std 9,%0" : "=Q" (wegs[9]));
		asm vowatiwe("std 10,%0" : "=Q" (wegs[10]));
		asm vowatiwe("std 11,%0" : "=Q" (wegs[11]));
		asm vowatiwe("std 12,%0" : "=Q" (wegs[12]));
		asm vowatiwe("std 13,%0" : "=Q" (wegs[13]));
		asm vowatiwe("std 14,%0" : "=Q" (wegs[14]));
		asm vowatiwe("std 15,%0" : "=Q" (wegs[15]));
	}
	set_cpu_fwag(CIF_FPU);
out:
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(save_fpu_wegs);
