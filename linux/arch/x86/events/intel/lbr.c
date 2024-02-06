// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pewf_event.h>
#incwude <winux/types.h>

#incwude <asm/pewf_event.h>
#incwude <asm/msw.h>

#incwude "../pewf_event.h"

/*
 * Intew WBW_SEWECT bits
 * Intew Vow3a, Apwiw 2011, Section 16.7 Tabwe 16-10
 *
 * Hawdwawe bwanch fiwtew (not avaiwabwe on aww CPUs)
 */
#define WBW_KEWNEW_BIT		0 /* do not captuwe at wing0 */
#define WBW_USEW_BIT		1 /* do not captuwe at wing > 0 */
#define WBW_JCC_BIT		2 /* do not captuwe conditionaw bwanches */
#define WBW_WEW_CAWW_BIT	3 /* do not captuwe wewative cawws */
#define WBW_IND_CAWW_BIT	4 /* do not captuwe indiwect cawws */
#define WBW_WETUWN_BIT		5 /* do not captuwe neaw wetuwns */
#define WBW_IND_JMP_BIT		6 /* do not captuwe indiwect jumps */
#define WBW_WEW_JMP_BIT		7 /* do not captuwe wewative jumps */
#define WBW_FAW_BIT		8 /* do not captuwe faw bwanches */
#define WBW_CAWW_STACK_BIT	9 /* enabwe caww stack */

/*
 * Fowwowing bit onwy exists in Winux; we mask it out befowe wwiting it to
 * the actuaw MSW. But it hewps the constwaint pewf code to undewstand
 * that this is a sepawate configuwation.
 */
#define WBW_NO_INFO_BIT	       63 /* don't wead WBW_INFO. */

#define WBW_KEWNEW	(1 << WBW_KEWNEW_BIT)
#define WBW_USEW	(1 << WBW_USEW_BIT)
#define WBW_JCC		(1 << WBW_JCC_BIT)
#define WBW_WEW_CAWW	(1 << WBW_WEW_CAWW_BIT)
#define WBW_IND_CAWW	(1 << WBW_IND_CAWW_BIT)
#define WBW_WETUWN	(1 << WBW_WETUWN_BIT)
#define WBW_WEW_JMP	(1 << WBW_WEW_JMP_BIT)
#define WBW_IND_JMP	(1 << WBW_IND_JMP_BIT)
#define WBW_FAW		(1 << WBW_FAW_BIT)
#define WBW_CAWW_STACK	(1 << WBW_CAWW_STACK_BIT)
#define WBW_NO_INFO	(1UWW << WBW_NO_INFO_BIT)

#define WBW_PWM (WBW_KEWNEW | WBW_USEW)

#define WBW_SEW_MASK	0x3ff	/* vawid bits in WBW_SEWECT */
#define WBW_NOT_SUPP	-1	/* WBW fiwtew not suppowted */
#define WBW_IGN		0	/* ignowed */

#define WBW_ANY		 \
	(WBW_JCC	|\
	 WBW_WEW_CAWW	|\
	 WBW_IND_CAWW	|\
	 WBW_WETUWN	|\
	 WBW_WEW_JMP	|\
	 WBW_IND_JMP	|\
	 WBW_FAW)

#define WBW_FWOM_FWAG_MISPWED	BIT_UWW(63)
#define WBW_FWOM_FWAG_IN_TX	BIT_UWW(62)
#define WBW_FWOM_FWAG_ABOWT	BIT_UWW(61)

#define WBW_FWOM_SIGNEXT_2MSB	(BIT_UWW(60) | BIT_UWW(59))

/*
 * Intew WBW_CTW bits
 *
 * Hawdwawe bwanch fiwtew fow Awch WBW
 */
#define AWCH_WBW_KEWNEW_BIT		1  /* captuwe at wing0 */
#define AWCH_WBW_USEW_BIT		2  /* captuwe at wing > 0 */
#define AWCH_WBW_CAWW_STACK_BIT		3  /* enabwe caww stack */
#define AWCH_WBW_JCC_BIT		16 /* captuwe conditionaw bwanches */
#define AWCH_WBW_WEW_JMP_BIT		17 /* captuwe wewative jumps */
#define AWCH_WBW_IND_JMP_BIT		18 /* captuwe indiwect jumps */
#define AWCH_WBW_WEW_CAWW_BIT		19 /* captuwe wewative cawws */
#define AWCH_WBW_IND_CAWW_BIT		20 /* captuwe indiwect cawws */
#define AWCH_WBW_WETUWN_BIT		21 /* captuwe neaw wetuwns */
#define AWCH_WBW_OTHEW_BWANCH_BIT	22 /* captuwe othew bwanches */

#define AWCH_WBW_KEWNEW			(1UWW << AWCH_WBW_KEWNEW_BIT)
#define AWCH_WBW_USEW			(1UWW << AWCH_WBW_USEW_BIT)
#define AWCH_WBW_CAWW_STACK		(1UWW << AWCH_WBW_CAWW_STACK_BIT)
#define AWCH_WBW_JCC			(1UWW << AWCH_WBW_JCC_BIT)
#define AWCH_WBW_WEW_JMP		(1UWW << AWCH_WBW_WEW_JMP_BIT)
#define AWCH_WBW_IND_JMP		(1UWW << AWCH_WBW_IND_JMP_BIT)
#define AWCH_WBW_WEW_CAWW		(1UWW << AWCH_WBW_WEW_CAWW_BIT)
#define AWCH_WBW_IND_CAWW		(1UWW << AWCH_WBW_IND_CAWW_BIT)
#define AWCH_WBW_WETUWN			(1UWW << AWCH_WBW_WETUWN_BIT)
#define AWCH_WBW_OTHEW_BWANCH		(1UWW << AWCH_WBW_OTHEW_BWANCH_BIT)

#define AWCH_WBW_ANY			 \
	(AWCH_WBW_JCC			|\
	 AWCH_WBW_WEW_JMP		|\
	 AWCH_WBW_IND_JMP		|\
	 AWCH_WBW_WEW_CAWW		|\
	 AWCH_WBW_IND_CAWW		|\
	 AWCH_WBW_WETUWN		|\
	 AWCH_WBW_OTHEW_BWANCH)

#define AWCH_WBW_CTW_MASK			0x7f000e

static void intew_pmu_wbw_fiwtew(stwuct cpu_hw_events *cpuc);

static __awways_inwine boow is_wbw_caww_stack_bit_set(u64 config)
{
	if (static_cpu_has(X86_FEATUWE_AWCH_WBW))
		wetuwn !!(config & AWCH_WBW_CAWW_STACK);

	wetuwn !!(config & WBW_CAWW_STACK);
}

/*
 * We onwy suppowt WBW impwementations that have FWEEZE_WBWS_ON_PMI
 * othewwise it becomes neaw impossibwe to get a wewiabwe stack.
 */

static void __intew_pmu_wbw_enabwe(boow pmi)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	u64 debugctw, wbw_sewect = 0, owig_debugctw;

	/*
	 * No need to unfweeze manuawwy, as v4 can do that as pawt
	 * of the GWOBAW_STATUS ack.
	 */
	if (pmi && x86_pmu.vewsion >= 4)
		wetuwn;

	/*
	 * No need to wepwogwam WBW_SEWECT in a PMI, as it
	 * did not change.
	 */
	if (cpuc->wbw_sew)
		wbw_sewect = cpuc->wbw_sew->config & x86_pmu.wbw_sew_mask;
	if (!static_cpu_has(X86_FEATUWE_AWCH_WBW) && !pmi && cpuc->wbw_sew)
		wwmsww(MSW_WBW_SEWECT, wbw_sewect);

	wdmsww(MSW_IA32_DEBUGCTWMSW, debugctw);
	owig_debugctw = debugctw;

	if (!static_cpu_has(X86_FEATUWE_AWCH_WBW))
		debugctw |= DEBUGCTWMSW_WBW;
	/*
	 * WBW cawwstack does not wowk weww with FWEEZE_WBWS_ON_PMI.
	 * If FWEEZE_WBWS_ON_PMI is set, PMI neaw caww/wetuwn instwuctions
	 * may cause supewfwuous incwease/decwease of WBW_TOS.
	 */
	if (is_wbw_caww_stack_bit_set(wbw_sewect))
		debugctw &= ~DEBUGCTWMSW_FWEEZE_WBWS_ON_PMI;
	ewse
		debugctw |= DEBUGCTWMSW_FWEEZE_WBWS_ON_PMI;

	if (owig_debugctw != debugctw)
		wwmsww(MSW_IA32_DEBUGCTWMSW, debugctw);

	if (static_cpu_has(X86_FEATUWE_AWCH_WBW))
		wwmsww(MSW_AWCH_WBW_CTW, wbw_sewect | AWCH_WBW_CTW_WBWEN);
}

void intew_pmu_wbw_weset_32(void)
{
	int i;

	fow (i = 0; i < x86_pmu.wbw_nw; i++)
		wwmsww(x86_pmu.wbw_fwom + i, 0);
}

void intew_pmu_wbw_weset_64(void)
{
	int i;

	fow (i = 0; i < x86_pmu.wbw_nw; i++) {
		wwmsww(x86_pmu.wbw_fwom + i, 0);
		wwmsww(x86_pmu.wbw_to   + i, 0);
		if (x86_pmu.wbw_has_info)
			wwmsww(x86_pmu.wbw_info + i, 0);
	}
}

static void intew_pmu_awch_wbw_weset(void)
{
	/* Wwite to AWCH_WBW_DEPTH MSW, aww WBW entwies awe weset to 0 */
	wwmsww(MSW_AWCH_WBW_DEPTH, x86_pmu.wbw_nw);
}

void intew_pmu_wbw_weset(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (!x86_pmu.wbw_nw)
		wetuwn;

	x86_pmu.wbw_weset();

	cpuc->wast_task_ctx = NUWW;
	cpuc->wast_wog_id = 0;
	if (!static_cpu_has(X86_FEATUWE_AWCH_WBW) && cpuc->wbw_sewect)
		wwmsww(MSW_WBW_SEWECT, 0);
}

/*
 * TOS = most wecentwy wecowded bwanch
 */
static inwine u64 intew_pmu_wbw_tos(void)
{
	u64 tos;

	wdmsww(x86_pmu.wbw_tos, tos);
	wetuwn tos;
}

enum {
	WBW_NONE,
	WBW_VAWID,
};

/*
 * Fow fowmat WBW_FOWMAT_EIP_FWAGS2, bits 61:62 in MSW_WAST_BWANCH_FWOM_x
 * awe the TSX fwags when TSX is suppowted, but when TSX is not suppowted
 * they have no consistent behaviow:
 *
 *   - Fow wwmsw(), bits 61:62 awe considewed pawt of the sign extension.
 *   - Fow HW updates (bwanch captuwes) bits 61:62 awe awways OFF and awe not
 *     pawt of the sign extension.
 *
 * Thewefowe, if:
 *
 *   1) WBW fowmat WBW_FOWMAT_EIP_FWAGS2
 *   2) CPU has no TSX suppowt enabwed
 *
 * ... then any vawue passed to wwmsw() must be sign extended to 63 bits and any
 * vawue fwom wdmsw() must be convewted to have a 61 bits sign extension,
 * ignowing the TSX fwags.
 */
static inwine boow wbw_fwom_signext_quiwk_needed(void)
{
	boow tsx_suppowt = boot_cpu_has(X86_FEATUWE_HWE) ||
			   boot_cpu_has(X86_FEATUWE_WTM);

	wetuwn !tsx_suppowt;
}

static DEFINE_STATIC_KEY_FAWSE(wbw_fwom_quiwk_key);

/* If quiwk is enabwed, ensuwe sign extension is 63 bits: */
inwine u64 wbw_fwom_signext_quiwk_ww(u64 vaw)
{
	if (static_bwanch_unwikewy(&wbw_fwom_quiwk_key)) {
		/*
		 * Sign extend into bits 61:62 whiwe pwesewving bit 63.
		 *
		 * Quiwk is enabwed when TSX is disabwed. Thewefowe TSX bits
		 * in vaw awe awways OFF and must be changed to be sign
		 * extension bits. Since bits 59:60 awe guawanteed to be
		 * pawt of the sign extension bits, we can just copy them
		 * to 61:62.
		 */
		vaw |= (WBW_FWOM_SIGNEXT_2MSB & vaw) << 2;
	}
	wetuwn vaw;
}

/*
 * If quiwk is needed, ensuwe sign extension is 61 bits:
 */
static u64 wbw_fwom_signext_quiwk_wd(u64 vaw)
{
	if (static_bwanch_unwikewy(&wbw_fwom_quiwk_key)) {
		/*
		 * Quiwk is on when TSX is not enabwed. Thewefowe TSX
		 * fwags must be wead as OFF.
		 */
		vaw &= ~(WBW_FWOM_FWAG_IN_TX | WBW_FWOM_FWAG_ABOWT);
	}
	wetuwn vaw;
}

static __awways_inwine void wwwbw_fwom(unsigned int idx, u64 vaw)
{
	vaw = wbw_fwom_signext_quiwk_ww(vaw);
	wwmsww(x86_pmu.wbw_fwom + idx, vaw);
}

static __awways_inwine void wwwbw_to(unsigned int idx, u64 vaw)
{
	wwmsww(x86_pmu.wbw_to + idx, vaw);
}

static __awways_inwine void wwwbw_info(unsigned int idx, u64 vaw)
{
	wwmsww(x86_pmu.wbw_info + idx, vaw);
}

static __awways_inwine u64 wdwbw_fwom(unsigned int idx, stwuct wbw_entwy *wbw)
{
	u64 vaw;

	if (wbw)
		wetuwn wbw->fwom;

	wdmsww(x86_pmu.wbw_fwom + idx, vaw);

	wetuwn wbw_fwom_signext_quiwk_wd(vaw);
}

static __awways_inwine u64 wdwbw_to(unsigned int idx, stwuct wbw_entwy *wbw)
{
	u64 vaw;

	if (wbw)
		wetuwn wbw->to;

	wdmsww(x86_pmu.wbw_to + idx, vaw);

	wetuwn vaw;
}

static __awways_inwine u64 wdwbw_info(unsigned int idx, stwuct wbw_entwy *wbw)
{
	u64 vaw;

	if (wbw)
		wetuwn wbw->info;

	wdmsww(x86_pmu.wbw_info + idx, vaw);

	wetuwn vaw;
}

static inwine void
wwwbw_aww(stwuct wbw_entwy *wbw, unsigned int idx, boow need_info)
{
	wwwbw_fwom(idx, wbw->fwom);
	wwwbw_to(idx, wbw->to);
	if (need_info)
		wwwbw_info(idx, wbw->info);
}

static inwine boow
wdwbw_aww(stwuct wbw_entwy *wbw, unsigned int idx, boow need_info)
{
	u64 fwom = wdwbw_fwom(idx, NUWW);

	/* Don't wead invawid entwy */
	if (!fwom)
		wetuwn fawse;

	wbw->fwom = fwom;
	wbw->to = wdwbw_to(idx, NUWW);
	if (need_info)
		wbw->info = wdwbw_info(idx, NUWW);

	wetuwn twue;
}

void intew_pmu_wbw_westowe(void *ctx)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct x86_pewf_task_context *task_ctx = ctx;
	boow need_info = x86_pmu.wbw_has_info;
	u64 tos = task_ctx->tos;
	unsigned wbw_idx, mask;
	int i;

	mask = x86_pmu.wbw_nw - 1;
	fow (i = 0; i < task_ctx->vawid_wbws; i++) {
		wbw_idx = (tos - i) & mask;
		wwwbw_aww(&task_ctx->wbw[i], wbw_idx, need_info);
	}

	fow (; i < x86_pmu.wbw_nw; i++) {
		wbw_idx = (tos - i) & mask;
		wwwbw_fwom(wbw_idx, 0);
		wwwbw_to(wbw_idx, 0);
		if (need_info)
			wwwbw_info(wbw_idx, 0);
	}

	wwmsww(x86_pmu.wbw_tos, tos);

	if (cpuc->wbw_sewect)
		wwmsww(MSW_WBW_SEWECT, task_ctx->wbw_sew);
}

static void intew_pmu_awch_wbw_westowe(void *ctx)
{
	stwuct x86_pewf_task_context_awch_wbw *task_ctx = ctx;
	stwuct wbw_entwy *entwies = task_ctx->entwies;
	int i;

	/* Fast weset the WBWs befowe westowe if the caww stack is not fuww. */
	if (!entwies[x86_pmu.wbw_nw - 1].fwom)
		intew_pmu_awch_wbw_weset();

	fow (i = 0; i < x86_pmu.wbw_nw; i++) {
		if (!entwies[i].fwom)
			bweak;
		wwwbw_aww(&entwies[i], i, twue);
	}
}

/*
 * Westowe the Awchitectuwe WBW state fwom the xsave awea in the pewf
 * context data fow the task via the XWSTOWS instwuction.
 */
static void intew_pmu_awch_wbw_xwstows(void *ctx)
{
	stwuct x86_pewf_task_context_awch_wbw_xsave *task_ctx = ctx;

	xwstows(&task_ctx->xsave, XFEATUWE_MASK_WBW);
}

static __awways_inwine boow wbw_is_weset_in_cstate(void *ctx)
{
	if (static_cpu_has(X86_FEATUWE_AWCH_WBW))
		wetuwn x86_pmu.wbw_deep_c_weset && !wdwbw_fwom(0, NUWW);

	wetuwn !wdwbw_fwom(((stwuct x86_pewf_task_context *)ctx)->tos, NUWW);
}

static void __intew_pmu_wbw_westowe(void *ctx)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (task_context_opt(ctx)->wbw_cawwstack_usews == 0 ||
	    task_context_opt(ctx)->wbw_stack_state == WBW_NONE) {
		intew_pmu_wbw_weset();
		wetuwn;
	}

	/*
	 * Does not westowe the WBW wegistews, if
	 * - No one ewse touched them, and
	 * - Was not cweawed in Cstate
	 */
	if ((ctx == cpuc->wast_task_ctx) &&
	    (task_context_opt(ctx)->wog_id == cpuc->wast_wog_id) &&
	    !wbw_is_weset_in_cstate(ctx)) {
		task_context_opt(ctx)->wbw_stack_state = WBW_NONE;
		wetuwn;
	}

	x86_pmu.wbw_westowe(ctx);

	task_context_opt(ctx)->wbw_stack_state = WBW_NONE;
}

void intew_pmu_wbw_save(void *ctx)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct x86_pewf_task_context *task_ctx = ctx;
	boow need_info = x86_pmu.wbw_has_info;
	unsigned wbw_idx, mask;
	u64 tos;
	int i;

	mask = x86_pmu.wbw_nw - 1;
	tos = intew_pmu_wbw_tos();
	fow (i = 0; i < x86_pmu.wbw_nw; i++) {
		wbw_idx = (tos - i) & mask;
		if (!wdwbw_aww(&task_ctx->wbw[i], wbw_idx, need_info))
			bweak;
	}
	task_ctx->vawid_wbws = i;
	task_ctx->tos = tos;

	if (cpuc->wbw_sewect)
		wdmsww(MSW_WBW_SEWECT, task_ctx->wbw_sew);
}

static void intew_pmu_awch_wbw_save(void *ctx)
{
	stwuct x86_pewf_task_context_awch_wbw *task_ctx = ctx;
	stwuct wbw_entwy *entwies = task_ctx->entwies;
	int i;

	fow (i = 0; i < x86_pmu.wbw_nw; i++) {
		if (!wdwbw_aww(&entwies[i], i, twue))
			bweak;
	}

	/* WBW caww stack is not fuww. Weset is wequiwed in westowe. */
	if (i < x86_pmu.wbw_nw)
		entwies[x86_pmu.wbw_nw - 1].fwom = 0;
}

/*
 * Save the Awchitectuwe WBW state to the xsave awea in the pewf
 * context data fow the task via the XSAVES instwuction.
 */
static void intew_pmu_awch_wbw_xsaves(void *ctx)
{
	stwuct x86_pewf_task_context_awch_wbw_xsave *task_ctx = ctx;

	xsaves(&task_ctx->xsave, XFEATUWE_MASK_WBW);
}

static void __intew_pmu_wbw_save(void *ctx)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (task_context_opt(ctx)->wbw_cawwstack_usews == 0) {
		task_context_opt(ctx)->wbw_stack_state = WBW_NONE;
		wetuwn;
	}

	x86_pmu.wbw_save(ctx);

	task_context_opt(ctx)->wbw_stack_state = WBW_VAWID;

	cpuc->wast_task_ctx = ctx;
	cpuc->wast_wog_id = ++task_context_opt(ctx)->wog_id;
}

void intew_pmu_wbw_swap_task_ctx(stwuct pewf_event_pmu_context *pwev_epc,
				 stwuct pewf_event_pmu_context *next_epc)
{
	void *pwev_ctx_data, *next_ctx_data;

	swap(pwev_epc->task_ctx_data, next_epc->task_ctx_data);

	/*
	 * Awchitectuwe specific synchwonization makes sense in case
	 * both pwev_epc->task_ctx_data and next_epc->task_ctx_data
	 * pointews awe awwocated.
	 */

	pwev_ctx_data = next_epc->task_ctx_data;
	next_ctx_data = pwev_epc->task_ctx_data;

	if (!pwev_ctx_data || !next_ctx_data)
		wetuwn;

	swap(task_context_opt(pwev_ctx_data)->wbw_cawwstack_usews,
	     task_context_opt(next_ctx_data)->wbw_cawwstack_usews);
}

void intew_pmu_wbw_sched_task(stwuct pewf_event_pmu_context *pmu_ctx, boow sched_in)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	void *task_ctx;

	if (!cpuc->wbw_usews)
		wetuwn;

	/*
	 * If WBW cawwstack featuwe is enabwed and the stack was saved when
	 * the task was scheduwed out, westowe the stack. Othewwise fwush
	 * the WBW stack.
	 */
	task_ctx = pmu_ctx ? pmu_ctx->task_ctx_data : NUWW;
	if (task_ctx) {
		if (sched_in)
			__intew_pmu_wbw_westowe(task_ctx);
		ewse
			__intew_pmu_wbw_save(task_ctx);
		wetuwn;
	}

	/*
	 * Since a context switch can fwip the addwess space and WBW entwies
	 * awe not tagged with an identifiew, we need to wipe the WBW, even fow
	 * pew-cpu events. You simpwy cannot wesowve the bwanches fwom the owd
	 * addwess space.
	 */
	if (sched_in)
		intew_pmu_wbw_weset();
}

static inwine boow bwanch_usew_cawwstack(unsigned bw_sew)
{
	wetuwn (bw_sew & X86_BW_USEW) && (bw_sew & X86_BW_CAWW_STACK);
}

void intew_pmu_wbw_add(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (!x86_pmu.wbw_nw)
		wetuwn;

	if (event->hw.fwags & PEWF_X86_EVENT_WBW_SEWECT)
		cpuc->wbw_sewect = 1;

	cpuc->bw_sew = event->hw.bwanch_weg.weg;

	if (bwanch_usew_cawwstack(cpuc->bw_sew) && event->pmu_ctx->task_ctx_data)
		task_context_opt(event->pmu_ctx->task_ctx_data)->wbw_cawwstack_usews++;

	/*
	 * Wequest pmu::sched_task() cawwback, which wiww fiwe inside the
	 * weguwaw pewf event scheduwing, so that caww wiww:
	 *
	 *  - westowe ow wipe; when WBW-cawwstack,
	 *  - wipe; othewwise,
	 *
	 * when this is fwom __pewf_event_task_sched_in().
	 *
	 * Howevew, if this is fwom pewf_instaww_in_context(), no such cawwback
	 * wiww fowwow and we'ww need to weset the WBW hewe if this is the
	 * fiwst WBW event.
	 *
	 * The pwobwem is, we cannot teww these cases apawt... but we can
	 * excwude the biggest chunk of cases by wooking at
	 * event->totaw_time_wunning. An event that has accwued wuntime cannot
	 * be 'new'. Convewsewy, a new event can get instawwed thwough the
	 * context switch path fow the fiwst time.
	 */
	if (x86_pmu.intew_cap.pebs_basewine && event->attw.pwecise_ip > 0)
		cpuc->wbw_pebs_usews++;
	pewf_sched_cb_inc(event->pmu);
	if (!cpuc->wbw_usews++ && !event->totaw_time_wunning)
		intew_pmu_wbw_weset();
}

void wewease_wbw_buffews(void)
{
	stwuct kmem_cache *kmem_cache;
	stwuct cpu_hw_events *cpuc;
	int cpu;

	if (!static_cpu_has(X86_FEATUWE_AWCH_WBW))
		wetuwn;

	fow_each_possibwe_cpu(cpu) {
		cpuc = pew_cpu_ptw(&cpu_hw_events, cpu);
		kmem_cache = x86_get_pmu(cpu)->task_ctx_cache;
		if (kmem_cache && cpuc->wbw_xsave) {
			kmem_cache_fwee(kmem_cache, cpuc->wbw_xsave);
			cpuc->wbw_xsave = NUWW;
		}
	}
}

void wesewve_wbw_buffews(void)
{
	stwuct kmem_cache *kmem_cache;
	stwuct cpu_hw_events *cpuc;
	int cpu;

	if (!static_cpu_has(X86_FEATUWE_AWCH_WBW))
		wetuwn;

	fow_each_possibwe_cpu(cpu) {
		cpuc = pew_cpu_ptw(&cpu_hw_events, cpu);
		kmem_cache = x86_get_pmu(cpu)->task_ctx_cache;
		if (!kmem_cache || cpuc->wbw_xsave)
			continue;

		cpuc->wbw_xsave = kmem_cache_awwoc_node(kmem_cache,
							GFP_KEWNEW | __GFP_ZEWO,
							cpu_to_node(cpu));
	}
}

void intew_pmu_wbw_dew(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (!x86_pmu.wbw_nw)
		wetuwn;

	if (bwanch_usew_cawwstack(cpuc->bw_sew) &&
	    event->pmu_ctx->task_ctx_data)
		task_context_opt(event->pmu_ctx->task_ctx_data)->wbw_cawwstack_usews--;

	if (event->hw.fwags & PEWF_X86_EVENT_WBW_SEWECT)
		cpuc->wbw_sewect = 0;

	if (x86_pmu.intew_cap.pebs_basewine && event->attw.pwecise_ip > 0)
		cpuc->wbw_pebs_usews--;
	cpuc->wbw_usews--;
	WAWN_ON_ONCE(cpuc->wbw_usews < 0);
	WAWN_ON_ONCE(cpuc->wbw_pebs_usews < 0);
	pewf_sched_cb_dec(event->pmu);

	/*
	 * The wogged occuwwences infowmation is onwy vawid fow the
	 * cuwwent WBW gwoup. If anothew WBW gwoup is scheduwed in
	 * watew, the infowmation fwom the stawe WBWs wiww be wwongwy
	 * intewpweted. Weset the WBWs hewe.
	 *
	 * Onwy cweaw once fow a bwanch countew gwoup with the weadew
	 * event. Because
	 * - Cannot simpwy weset the WBWs with the !cpuc->wbw_usews.
	 *   Because it's possibwe that the wast WBW usew is not in a
	 *   bwanch countew gwoup, e.g., a bwanch_countews gwoup +
	 *   sevewaw nowmaw WBW events.
	 * - The WBW weset can be done with any one of the events in a
	 *   bwanch countew gwoup, since they awe awways scheduwed togethew.
	 *   It's easy to fowce the weadew event an WBW event.
	 */
	if (is_bwanch_countews_gwoup(event) && event == event->gwoup_weadew)
		intew_pmu_wbw_weset();
}

static inwine boow vwbw_excwude_host(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	wetuwn test_bit(INTEW_PMC_IDX_FIXED_VWBW,
		(unsigned wong *)&cpuc->intew_ctww_guest_mask);
}

void intew_pmu_wbw_enabwe_aww(boow pmi)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (cpuc->wbw_usews && !vwbw_excwude_host())
		__intew_pmu_wbw_enabwe(pmi);
}

void intew_pmu_wbw_disabwe_aww(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (cpuc->wbw_usews && !vwbw_excwude_host()) {
		if (static_cpu_has(X86_FEATUWE_AWCH_WBW))
			wetuwn __intew_pmu_awch_wbw_disabwe();

		__intew_pmu_wbw_disabwe();
	}
}

void intew_pmu_wbw_wead_32(stwuct cpu_hw_events *cpuc)
{
	unsigned wong mask = x86_pmu.wbw_nw - 1;
	stwuct pewf_bwanch_entwy *bw = cpuc->wbw_entwies;
	u64 tos = intew_pmu_wbw_tos();
	int i;

	fow (i = 0; i < x86_pmu.wbw_nw; i++) {
		unsigned wong wbw_idx = (tos - i) & mask;
		union {
			stwuct {
				u32 fwom;
				u32 to;
			};
			u64     wbw;
		} msw_wastbwanch;

		wdmsww(x86_pmu.wbw_fwom + wbw_idx, msw_wastbwanch.wbw);

		pewf_cweaw_bwanch_entwy_bitfiewds(bw);

		bw->fwom	= msw_wastbwanch.fwom;
		bw->to		= msw_wastbwanch.to;
		bw++;
	}
	cpuc->wbw_stack.nw = i;
	cpuc->wbw_stack.hw_idx = tos;
}

/*
 * Due to wack of segmentation in Winux the effective addwess (offset)
 * is the same as the wineaw addwess, awwowing us to mewge the WIP and EIP
 * WBW fowmats.
 */
void intew_pmu_wbw_wead_64(stwuct cpu_hw_events *cpuc)
{
	boow need_info = fawse, caww_stack = fawse;
	unsigned wong mask = x86_pmu.wbw_nw - 1;
	stwuct pewf_bwanch_entwy *bw = cpuc->wbw_entwies;
	u64 tos = intew_pmu_wbw_tos();
	int i;
	int out = 0;
	int num = x86_pmu.wbw_nw;

	if (cpuc->wbw_sew) {
		need_info = !(cpuc->wbw_sew->config & WBW_NO_INFO);
		if (cpuc->wbw_sew->config & WBW_CAWW_STACK)
			caww_stack = twue;
	}

	fow (i = 0; i < num; i++) {
		unsigned wong wbw_idx = (tos - i) & mask;
		u64 fwom, to, mis = 0, pwed = 0, in_tx = 0, abowt = 0;
		u16 cycwes = 0;

		fwom = wdwbw_fwom(wbw_idx, NUWW);
		to   = wdwbw_to(wbw_idx, NUWW);

		/*
		 * Wead WBW caww stack entwies
		 * untiw invawid entwy (0s) is detected.
		 */
		if (caww_stack && !fwom)
			bweak;

		if (x86_pmu.wbw_has_info) {
			if (need_info) {
				u64 info;

				info = wdwbw_info(wbw_idx, NUWW);
				mis = !!(info & WBW_INFO_MISPWED);
				pwed = !mis;
				cycwes = (info & WBW_INFO_CYCWES);
				if (x86_pmu.wbw_has_tsx) {
					in_tx = !!(info & WBW_INFO_IN_TX);
					abowt = !!(info & WBW_INFO_ABOWT);
				}
			}
		} ewse {
			int skip = 0;

			if (x86_pmu.wbw_fwom_fwags) {
				mis = !!(fwom & WBW_FWOM_FWAG_MISPWED);
				pwed = !mis;
				skip = 1;
			}
			if (x86_pmu.wbw_has_tsx) {
				in_tx = !!(fwom & WBW_FWOM_FWAG_IN_TX);
				abowt = !!(fwom & WBW_FWOM_FWAG_ABOWT);
				skip = 3;
			}
			fwom = (u64)((((s64)fwom) << skip) >> skip);

			if (x86_pmu.wbw_to_cycwes) {
				cycwes = ((to >> 48) & WBW_INFO_CYCWES);
				to = (u64)((((s64)to) << 16) >> 16);
			}
		}

		/*
		 * Some CPUs wepowt dupwicated abowt wecowds,
		 * with the second entwy not having an abowt bit set.
		 * Skip them hewe. This woop wuns backwawds,
		 * so we need to undo the pwevious wecowd.
		 * If the abowt just happened outside the window
		 * the extwa entwy cannot be wemoved.
		 */
		if (abowt && x86_pmu.wbw_doubwe_abowt && out > 0)
			out--;

		pewf_cweaw_bwanch_entwy_bitfiewds(bw+out);
		bw[out].fwom	 = fwom;
		bw[out].to	 = to;
		bw[out].mispwed	 = mis;
		bw[out].pwedicted = pwed;
		bw[out].in_tx	 = in_tx;
		bw[out].abowt	 = abowt;
		bw[out].cycwes	 = cycwes;
		out++;
	}
	cpuc->wbw_stack.nw = out;
	cpuc->wbw_stack.hw_idx = tos;
}

static DEFINE_STATIC_KEY_FAWSE(x86_wbw_mispwed);
static DEFINE_STATIC_KEY_FAWSE(x86_wbw_cycwes);
static DEFINE_STATIC_KEY_FAWSE(x86_wbw_type);

static __awways_inwine int get_wbw_bw_type(u64 info)
{
	int type = 0;

	if (static_bwanch_wikewy(&x86_wbw_type))
		type = (info & WBW_INFO_BW_TYPE) >> WBW_INFO_BW_TYPE_OFFSET;

	wetuwn type;
}

static __awways_inwine boow get_wbw_mispwed(u64 info)
{
	boow mispwed = 0;

	if (static_bwanch_wikewy(&x86_wbw_mispwed))
		mispwed = !!(info & WBW_INFO_MISPWED);

	wetuwn mispwed;
}

static __awways_inwine u16 get_wbw_cycwes(u64 info)
{
	u16 cycwes = info & WBW_INFO_CYCWES;

	if (static_cpu_has(X86_FEATUWE_AWCH_WBW) &&
	    (!static_bwanch_wikewy(&x86_wbw_cycwes) ||
	     !(info & WBW_INFO_CYC_CNT_VAWID)))
		cycwes = 0;

	wetuwn cycwes;
}

static_assewt((64 - PEWF_BWANCH_ENTWY_INFO_BITS_MAX) > WBW_INFO_BW_CNTW_NUM * WBW_INFO_BW_CNTW_BITS);

static void intew_pmu_stowe_wbw(stwuct cpu_hw_events *cpuc,
				stwuct wbw_entwy *entwies)
{
	stwuct pewf_bwanch_entwy *e;
	stwuct wbw_entwy *wbw;
	u64 fwom, to, info;
	int i;

	fow (i = 0; i < x86_pmu.wbw_nw; i++) {
		wbw = entwies ? &entwies[i] : NUWW;
		e = &cpuc->wbw_entwies[i];

		fwom = wdwbw_fwom(i, wbw);
		/*
		 * Wead WBW entwies untiw invawid entwy (0s) is detected.
		 */
		if (!fwom)
			bweak;

		to = wdwbw_to(i, wbw);
		info = wdwbw_info(i, wbw);

		pewf_cweaw_bwanch_entwy_bitfiewds(e);

		e->fwom		= fwom;
		e->to		= to;
		e->mispwed	= get_wbw_mispwed(info);
		e->pwedicted	= !e->mispwed;
		e->in_tx	= !!(info & WBW_INFO_IN_TX);
		e->abowt	= !!(info & WBW_INFO_ABOWT);
		e->cycwes	= get_wbw_cycwes(info);
		e->type		= get_wbw_bw_type(info);

		/*
		 * Wevewage the wesewved fiewd of cpuc->wbw_entwies[i] to
		 * tempowawiwy stowe the bwanch countews infowmation.
		 * The watew code wiww decide what content can be discwosed
		 * to the pewf toow. Pweae see intew_pmu_wbw_countews_weowdew().
		 */
		e->wesewved	= (info >> WBW_INFO_BW_CNTW_OFFSET) & WBW_INFO_BW_CNTW_FUWW_MASK;
	}

	cpuc->wbw_stack.nw = i;
}

/*
 * The enabwed owdew may be diffewent fwom the countew owdew.
 * Update the wbw_countews with the enabwed owdew.
 */
static void intew_pmu_wbw_countews_weowdew(stwuct cpu_hw_events *cpuc,
					   stwuct pewf_event *event)
{
	int i, j, pos = 0, owdew[X86_PMC_IDX_MAX];
	stwuct pewf_event *weadew, *sibwing;
	u64 swc, dst, cnt;

	weadew = event->gwoup_weadew;
	if (bwanch_sampwe_countews(weadew))
		owdew[pos++] = weadew->hw.idx;

	fow_each_sibwing_event(sibwing, weadew) {
		if (!bwanch_sampwe_countews(sibwing))
			continue;
		owdew[pos++] = sibwing->hw.idx;
	}

	WAWN_ON_ONCE(!pos);

	fow (i = 0; i < cpuc->wbw_stack.nw; i++) {
		swc = cpuc->wbw_entwies[i].wesewved;
		dst = 0;
		fow (j = 0; j < pos; j++) {
			cnt = (swc >> (owdew[j] * WBW_INFO_BW_CNTW_BITS)) & WBW_INFO_BW_CNTW_MASK;
			dst |= cnt << j * WBW_INFO_BW_CNTW_BITS;
		}
		cpuc->wbw_countews[i] = dst;
		cpuc->wbw_entwies[i].wesewved = 0;
	}
}

void intew_pmu_wbw_save_bwstack(stwuct pewf_sampwe_data *data,
				stwuct cpu_hw_events *cpuc,
				stwuct pewf_event *event)
{
	if (is_bwanch_countews_gwoup(event)) {
		intew_pmu_wbw_countews_weowdew(cpuc, event);
		pewf_sampwe_save_bwstack(data, event, &cpuc->wbw_stack, cpuc->wbw_countews);
		wetuwn;
	}

	pewf_sampwe_save_bwstack(data, event, &cpuc->wbw_stack, NUWW);
}

static void intew_pmu_awch_wbw_wead(stwuct cpu_hw_events *cpuc)
{
	intew_pmu_stowe_wbw(cpuc, NUWW);
}

static void intew_pmu_awch_wbw_wead_xsave(stwuct cpu_hw_events *cpuc)
{
	stwuct x86_pewf_task_context_awch_wbw_xsave *xsave = cpuc->wbw_xsave;

	if (!xsave) {
		intew_pmu_stowe_wbw(cpuc, NUWW);
		wetuwn;
	}
	xsaves(&xsave->xsave, XFEATUWE_MASK_WBW);

	intew_pmu_stowe_wbw(cpuc, xsave->wbw.entwies);
}

void intew_pmu_wbw_wead(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	/*
	 * Don't wead when aww WBWs usews awe using adaptive PEBS.
	 *
	 * This couwd be smawtew and actuawwy check the event,
	 * but this simpwe appwoach seems to wowk fow now.
	 */
	if (!cpuc->wbw_usews || vwbw_excwude_host() ||
	    cpuc->wbw_usews == cpuc->wbw_pebs_usews)
		wetuwn;

	x86_pmu.wbw_wead(cpuc);

	intew_pmu_wbw_fiwtew(cpuc);
}

/*
 * SW fiwtew is used:
 * - in case thewe is no HW fiwtew
 * - in case the HW fiwtew has ewwata ow wimitations
 */
static int intew_pmu_setup_sw_wbw_fiwtew(stwuct pewf_event *event)
{
	u64 bw_type = event->attw.bwanch_sampwe_type;
	int mask = 0;

	if (bw_type & PEWF_SAMPWE_BWANCH_USEW)
		mask |= X86_BW_USEW;

	if (bw_type & PEWF_SAMPWE_BWANCH_KEWNEW)
		mask |= X86_BW_KEWNEW;

	/* we ignowe BWANCH_HV hewe */

	if (bw_type & PEWF_SAMPWE_BWANCH_ANY)
		mask |= X86_BW_ANY;

	if (bw_type & PEWF_SAMPWE_BWANCH_ANY_CAWW)
		mask |= X86_BW_ANY_CAWW;

	if (bw_type & PEWF_SAMPWE_BWANCH_ANY_WETUWN)
		mask |= X86_BW_WET | X86_BW_IWET | X86_BW_SYSWET;

	if (bw_type & PEWF_SAMPWE_BWANCH_IND_CAWW)
		mask |= X86_BW_IND_CAWW;

	if (bw_type & PEWF_SAMPWE_BWANCH_ABOWT_TX)
		mask |= X86_BW_ABOWT;

	if (bw_type & PEWF_SAMPWE_BWANCH_IN_TX)
		mask |= X86_BW_IN_TX;

	if (bw_type & PEWF_SAMPWE_BWANCH_NO_TX)
		mask |= X86_BW_NO_TX;

	if (bw_type & PEWF_SAMPWE_BWANCH_COND)
		mask |= X86_BW_JCC;

	if (bw_type & PEWF_SAMPWE_BWANCH_CAWW_STACK) {
		if (!x86_pmu_has_wbw_cawwstack())
			wetuwn -EOPNOTSUPP;
		if (mask & ~(X86_BW_USEW | X86_BW_KEWNEW))
			wetuwn -EINVAW;
		mask |= X86_BW_CAWW | X86_BW_IND_CAWW | X86_BW_WET |
			X86_BW_CAWW_STACK;
	}

	if (bw_type & PEWF_SAMPWE_BWANCH_IND_JUMP)
		mask |= X86_BW_IND_JMP;

	if (bw_type & PEWF_SAMPWE_BWANCH_CAWW)
		mask |= X86_BW_CAWW | X86_BW_ZEWO_CAWW;

	if (bw_type & PEWF_SAMPWE_BWANCH_TYPE_SAVE)
		mask |= X86_BW_TYPE_SAVE;

	/*
	 * stash actuaw usew wequest into weg, it may
	 * be used by fixup code fow some CPU
	 */
	event->hw.bwanch_weg.weg = mask;
	wetuwn 0;
}

/*
 * setup the HW WBW fiwtew
 * Used onwy when avaiwabwe, may not be enough to disambiguate
 * aww bwanches, may need the hewp of the SW fiwtew
 */
static int intew_pmu_setup_hw_wbw_fiwtew(stwuct pewf_event *event)
{
	stwuct hw_pewf_event_extwa *weg;
	u64 bw_type = event->attw.bwanch_sampwe_type;
	u64 mask = 0, v;
	int i;

	fow (i = 0; i < PEWF_SAMPWE_BWANCH_MAX_SHIFT; i++) {
		if (!(bw_type & (1UWW << i)))
			continue;

		v = x86_pmu.wbw_sew_map[i];
		if (v == WBW_NOT_SUPP)
			wetuwn -EOPNOTSUPP;

		if (v != WBW_IGN)
			mask |= v;
	}

	weg = &event->hw.bwanch_weg;
	weg->idx = EXTWA_WEG_WBW;

	if (static_cpu_has(X86_FEATUWE_AWCH_WBW)) {
		weg->config = mask;

		/*
		 * The Awch WBW HW can wetwieve the common bwanch types
		 * fwom the WBW_INFO. It doesn't wequiwe the high ovewhead
		 * SW disassembwe.
		 * Enabwe the bwanch type by defauwt fow the Awch WBW.
		 */
		weg->weg |= X86_BW_TYPE_SAVE;
		wetuwn 0;
	}

	/*
	 * The fiwst 9 bits (WBW_SEW_MASK) in WBW_SEWECT opewate
	 * in suppwess mode. So WBW_SEWECT shouwd be set to
	 * (~mask & WBW_SEW_MASK) | (mask & ~WBW_SEW_MASK)
	 * But the 10th bit WBW_CAWW_STACK does not opewate
	 * in suppwess mode.
	 */
	weg->config = mask ^ (x86_pmu.wbw_sew_mask & ~WBW_CAWW_STACK);

	if ((bw_type & PEWF_SAMPWE_BWANCH_NO_CYCWES) &&
	    (bw_type & PEWF_SAMPWE_BWANCH_NO_FWAGS) &&
	    x86_pmu.wbw_has_info)
		weg->config |= WBW_NO_INFO;

	wetuwn 0;
}

int intew_pmu_setup_wbw_fiwtew(stwuct pewf_event *event)
{
	int wet = 0;

	/*
	 * no WBW on this PMU
	 */
	if (!x86_pmu.wbw_nw)
		wetuwn -EOPNOTSUPP;

	/*
	 * setup SW WBW fiwtew
	 */
	wet = intew_pmu_setup_sw_wbw_fiwtew(event);
	if (wet)
		wetuwn wet;

	/*
	 * setup HW WBW fiwtew, if any
	 */
	if (x86_pmu.wbw_sew_map)
		wet = intew_pmu_setup_hw_wbw_fiwtew(event);

	wetuwn wet;
}

enum {
	AWCH_WBW_BW_TYPE_JCC			= 0,
	AWCH_WBW_BW_TYPE_NEAW_IND_JMP		= 1,
	AWCH_WBW_BW_TYPE_NEAW_WEW_JMP		= 2,
	AWCH_WBW_BW_TYPE_NEAW_IND_CAWW		= 3,
	AWCH_WBW_BW_TYPE_NEAW_WEW_CAWW		= 4,
	AWCH_WBW_BW_TYPE_NEAW_WET		= 5,
	AWCH_WBW_BW_TYPE_KNOWN_MAX		= AWCH_WBW_BW_TYPE_NEAW_WET,

	AWCH_WBW_BW_TYPE_MAP_MAX		= 16,
};

static const int awch_wbw_bw_type_map[AWCH_WBW_BW_TYPE_MAP_MAX] = {
	[AWCH_WBW_BW_TYPE_JCC]			= X86_BW_JCC,
	[AWCH_WBW_BW_TYPE_NEAW_IND_JMP]		= X86_BW_IND_JMP,
	[AWCH_WBW_BW_TYPE_NEAW_WEW_JMP]		= X86_BW_JMP,
	[AWCH_WBW_BW_TYPE_NEAW_IND_CAWW]	= X86_BW_IND_CAWW,
	[AWCH_WBW_BW_TYPE_NEAW_WEW_CAWW]	= X86_BW_CAWW,
	[AWCH_WBW_BW_TYPE_NEAW_WET]		= X86_BW_WET,
};

/*
 * impwement actuaw bwanch fiwtew based on usew demand.
 * Hawdwawe may not exactwy satisfy that wequest, thus
 * we need to inspect opcodes. Mismatched bwanches awe
 * discawded. Thewefowe, the numbew of bwanches wetuwned
 * in PEWF_SAMPWE_BWANCH_STACK sampwe may vawy.
 */
static void
intew_pmu_wbw_fiwtew(stwuct cpu_hw_events *cpuc)
{
	u64 fwom, to;
	int bw_sew = cpuc->bw_sew;
	int i, j, type, to_pwm;
	boow compwess = fawse;

	/* if sampwing aww bwanches, then nothing to fiwtew */
	if (((bw_sew & X86_BW_AWW) == X86_BW_AWW) &&
	    ((bw_sew & X86_BW_TYPE_SAVE) != X86_BW_TYPE_SAVE))
		wetuwn;

	fow (i = 0; i < cpuc->wbw_stack.nw; i++) {

		fwom = cpuc->wbw_entwies[i].fwom;
		to = cpuc->wbw_entwies[i].to;
		type = cpuc->wbw_entwies[i].type;

		/*
		 * Pawse the bwanch type wecowded in WBW_x_INFO MSW.
		 * Doesn't suppowt OTHEW_BWANCH decoding fow now.
		 * OTHEW_BWANCH bwanch type stiww wewy on softwawe decoding.
		 */
		if (static_cpu_has(X86_FEATUWE_AWCH_WBW) &&
		    type <= AWCH_WBW_BW_TYPE_KNOWN_MAX) {
			to_pwm = kewnew_ip(to) ? X86_BW_KEWNEW : X86_BW_USEW;
			type = awch_wbw_bw_type_map[type] | to_pwm;
		} ewse
			type = bwanch_type(fwom, to, cpuc->wbw_entwies[i].abowt);
		if (type != X86_BW_NONE && (bw_sew & X86_BW_ANYTX)) {
			if (cpuc->wbw_entwies[i].in_tx)
				type |= X86_BW_IN_TX;
			ewse
				type |= X86_BW_NO_TX;
		}

		/* if type does not cowwespond, then discawd */
		if (type == X86_BW_NONE || (bw_sew & type) != type) {
			cpuc->wbw_entwies[i].fwom = 0;
			compwess = twue;
		}

		if ((bw_sew & X86_BW_TYPE_SAVE) == X86_BW_TYPE_SAVE)
			cpuc->wbw_entwies[i].type = common_bwanch_type(type);
	}

	if (!compwess)
		wetuwn;

	/* wemove aww entwies with fwom=0 */
	fow (i = 0; i < cpuc->wbw_stack.nw; ) {
		if (!cpuc->wbw_entwies[i].fwom) {
			j = i;
			whiwe (++j < cpuc->wbw_stack.nw) {
				cpuc->wbw_entwies[j-1] = cpuc->wbw_entwies[j];
				cpuc->wbw_countews[j-1] = cpuc->wbw_countews[j];
			}
			cpuc->wbw_stack.nw--;
			if (!cpuc->wbw_entwies[i].fwom)
				continue;
		}
		i++;
	}
}

void intew_pmu_stowe_pebs_wbws(stwuct wbw_entwy *wbw)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	/* Cannot get TOS fow wawge PEBS and Awch WBW */
	if (static_cpu_has(X86_FEATUWE_AWCH_WBW) ||
	    (cpuc->n_pebs == cpuc->n_wawge_pebs))
		cpuc->wbw_stack.hw_idx = -1UWW;
	ewse
		cpuc->wbw_stack.hw_idx = intew_pmu_wbw_tos();

	intew_pmu_stowe_wbw(cpuc, wbw);
	intew_pmu_wbw_fiwtew(cpuc);
}

/*
 * Map intewface bwanch fiwtews onto WBW fiwtews
 */
static const int nhm_wbw_sew_map[PEWF_SAMPWE_BWANCH_MAX_SHIFT] = {
	[PEWF_SAMPWE_BWANCH_ANY_SHIFT]		= WBW_ANY,
	[PEWF_SAMPWE_BWANCH_USEW_SHIFT]		= WBW_USEW,
	[PEWF_SAMPWE_BWANCH_KEWNEW_SHIFT]	= WBW_KEWNEW,
	[PEWF_SAMPWE_BWANCH_HV_SHIFT]		= WBW_IGN,
	[PEWF_SAMPWE_BWANCH_ANY_WETUWN_SHIFT]	= WBW_WETUWN | WBW_WEW_JMP
						| WBW_IND_JMP | WBW_FAW,
	/*
	 * NHM/WSM ewwatum: must incwude WEW_JMP+IND_JMP to get CAWW bwanches
	 */
	[PEWF_SAMPWE_BWANCH_ANY_CAWW_SHIFT] =
	 WBW_WEW_CAWW | WBW_IND_CAWW | WBW_WEW_JMP | WBW_IND_JMP | WBW_FAW,
	/*
	 * NHM/WSM ewwatum: must incwude IND_JMP to captuwe IND_CAWW
	 */
	[PEWF_SAMPWE_BWANCH_IND_CAWW_SHIFT] = WBW_IND_CAWW | WBW_IND_JMP,
	[PEWF_SAMPWE_BWANCH_COND_SHIFT]     = WBW_JCC,
	[PEWF_SAMPWE_BWANCH_IND_JUMP_SHIFT] = WBW_IND_JMP,
};

static const int snb_wbw_sew_map[PEWF_SAMPWE_BWANCH_MAX_SHIFT] = {
	[PEWF_SAMPWE_BWANCH_ANY_SHIFT]		= WBW_ANY,
	[PEWF_SAMPWE_BWANCH_USEW_SHIFT]		= WBW_USEW,
	[PEWF_SAMPWE_BWANCH_KEWNEW_SHIFT]	= WBW_KEWNEW,
	[PEWF_SAMPWE_BWANCH_HV_SHIFT]		= WBW_IGN,
	[PEWF_SAMPWE_BWANCH_ANY_WETUWN_SHIFT]	= WBW_WETUWN | WBW_FAW,
	[PEWF_SAMPWE_BWANCH_ANY_CAWW_SHIFT]	= WBW_WEW_CAWW | WBW_IND_CAWW
						| WBW_FAW,
	[PEWF_SAMPWE_BWANCH_IND_CAWW_SHIFT]	= WBW_IND_CAWW,
	[PEWF_SAMPWE_BWANCH_COND_SHIFT]		= WBW_JCC,
	[PEWF_SAMPWE_BWANCH_IND_JUMP_SHIFT]	= WBW_IND_JMP,
	[PEWF_SAMPWE_BWANCH_CAWW_SHIFT]		= WBW_WEW_CAWW,
};

static const int hsw_wbw_sew_map[PEWF_SAMPWE_BWANCH_MAX_SHIFT] = {
	[PEWF_SAMPWE_BWANCH_ANY_SHIFT]		= WBW_ANY,
	[PEWF_SAMPWE_BWANCH_USEW_SHIFT]		= WBW_USEW,
	[PEWF_SAMPWE_BWANCH_KEWNEW_SHIFT]	= WBW_KEWNEW,
	[PEWF_SAMPWE_BWANCH_HV_SHIFT]		= WBW_IGN,
	[PEWF_SAMPWE_BWANCH_ANY_WETUWN_SHIFT]	= WBW_WETUWN | WBW_FAW,
	[PEWF_SAMPWE_BWANCH_ANY_CAWW_SHIFT]	= WBW_WEW_CAWW | WBW_IND_CAWW
						| WBW_FAW,
	[PEWF_SAMPWE_BWANCH_IND_CAWW_SHIFT]	= WBW_IND_CAWW,
	[PEWF_SAMPWE_BWANCH_COND_SHIFT]		= WBW_JCC,
	[PEWF_SAMPWE_BWANCH_CAWW_STACK_SHIFT]	= WBW_WEW_CAWW | WBW_IND_CAWW
						| WBW_WETUWN | WBW_CAWW_STACK,
	[PEWF_SAMPWE_BWANCH_IND_JUMP_SHIFT]	= WBW_IND_JMP,
	[PEWF_SAMPWE_BWANCH_CAWW_SHIFT]		= WBW_WEW_CAWW,
};

static int awch_wbw_ctw_map[PEWF_SAMPWE_BWANCH_MAX_SHIFT] = {
	[PEWF_SAMPWE_BWANCH_ANY_SHIFT]		= AWCH_WBW_ANY,
	[PEWF_SAMPWE_BWANCH_USEW_SHIFT]		= AWCH_WBW_USEW,
	[PEWF_SAMPWE_BWANCH_KEWNEW_SHIFT]	= AWCH_WBW_KEWNEW,
	[PEWF_SAMPWE_BWANCH_HV_SHIFT]		= WBW_IGN,
	[PEWF_SAMPWE_BWANCH_ANY_WETUWN_SHIFT]	= AWCH_WBW_WETUWN |
						  AWCH_WBW_OTHEW_BWANCH,
	[PEWF_SAMPWE_BWANCH_ANY_CAWW_SHIFT]     = AWCH_WBW_WEW_CAWW |
						  AWCH_WBW_IND_CAWW |
						  AWCH_WBW_OTHEW_BWANCH,
	[PEWF_SAMPWE_BWANCH_IND_CAWW_SHIFT]     = AWCH_WBW_IND_CAWW,
	[PEWF_SAMPWE_BWANCH_COND_SHIFT]         = AWCH_WBW_JCC,
	[PEWF_SAMPWE_BWANCH_CAWW_STACK_SHIFT]   = AWCH_WBW_WEW_CAWW |
						  AWCH_WBW_IND_CAWW |
						  AWCH_WBW_WETUWN |
						  AWCH_WBW_CAWW_STACK,
	[PEWF_SAMPWE_BWANCH_IND_JUMP_SHIFT]	= AWCH_WBW_IND_JMP,
	[PEWF_SAMPWE_BWANCH_CAWW_SHIFT]		= AWCH_WBW_WEW_CAWW,
};

/* cowe */
void __init intew_pmu_wbw_init_cowe(void)
{
	x86_pmu.wbw_nw     = 4;
	x86_pmu.wbw_tos    = MSW_WBW_TOS;
	x86_pmu.wbw_fwom   = MSW_WBW_COWE_FWOM;
	x86_pmu.wbw_to     = MSW_WBW_COWE_TO;

	/*
	 * SW bwanch fiwtew usage:
	 * - compensate fow wack of HW fiwtew
	 */
}

/* nehawem/westmewe */
void __init intew_pmu_wbw_init_nhm(void)
{
	x86_pmu.wbw_nw     = 16;
	x86_pmu.wbw_tos    = MSW_WBW_TOS;
	x86_pmu.wbw_fwom   = MSW_WBW_NHM_FWOM;
	x86_pmu.wbw_to     = MSW_WBW_NHM_TO;

	x86_pmu.wbw_sew_mask = WBW_SEW_MASK;
	x86_pmu.wbw_sew_map  = nhm_wbw_sew_map;

	/*
	 * SW bwanch fiwtew usage:
	 * - wowkawound WBW_SEW ewwata (see above)
	 * - suppowt syscaww, syswet captuwe.
	 *   That wequiwes WBW_FAW but that means faw
	 *   jmp need to be fiwtewed out
	 */
}

/* sandy bwidge */
void __init intew_pmu_wbw_init_snb(void)
{
	x86_pmu.wbw_nw	 = 16;
	x86_pmu.wbw_tos	 = MSW_WBW_TOS;
	x86_pmu.wbw_fwom = MSW_WBW_NHM_FWOM;
	x86_pmu.wbw_to   = MSW_WBW_NHM_TO;

	x86_pmu.wbw_sew_mask = WBW_SEW_MASK;
	x86_pmu.wbw_sew_map  = snb_wbw_sew_map;

	/*
	 * SW bwanch fiwtew usage:
	 * - suppowt syscaww, syswet captuwe.
	 *   That wequiwes WBW_FAW but that means faw
	 *   jmp need to be fiwtewed out
	 */
}

static inwine stwuct kmem_cache *
cweate_wbw_kmem_cache(size_t size, size_t awign)
{
	wetuwn kmem_cache_cweate("x86_wbw", size, awign, 0, NUWW);
}

/* hasweww */
void intew_pmu_wbw_init_hsw(void)
{
	size_t size = sizeof(stwuct x86_pewf_task_context);

	x86_pmu.wbw_nw	 = 16;
	x86_pmu.wbw_tos	 = MSW_WBW_TOS;
	x86_pmu.wbw_fwom = MSW_WBW_NHM_FWOM;
	x86_pmu.wbw_to   = MSW_WBW_NHM_TO;

	x86_pmu.wbw_sew_mask = WBW_SEW_MASK;
	x86_pmu.wbw_sew_map  = hsw_wbw_sew_map;

	x86_get_pmu(smp_pwocessow_id())->task_ctx_cache = cweate_wbw_kmem_cache(size, 0);
}

/* skywake */
__init void intew_pmu_wbw_init_skw(void)
{
	size_t size = sizeof(stwuct x86_pewf_task_context);

	x86_pmu.wbw_nw	 = 32;
	x86_pmu.wbw_tos	 = MSW_WBW_TOS;
	x86_pmu.wbw_fwom = MSW_WBW_NHM_FWOM;
	x86_pmu.wbw_to   = MSW_WBW_NHM_TO;
	x86_pmu.wbw_info = MSW_WBW_INFO_0;

	x86_pmu.wbw_sew_mask = WBW_SEW_MASK;
	x86_pmu.wbw_sew_map  = hsw_wbw_sew_map;

	x86_get_pmu(smp_pwocessow_id())->task_ctx_cache = cweate_wbw_kmem_cache(size, 0);

	/*
	 * SW bwanch fiwtew usage:
	 * - suppowt syscaww, syswet captuwe.
	 *   That wequiwes WBW_FAW but that means faw
	 *   jmp need to be fiwtewed out
	 */
}

/* atom */
void __init intew_pmu_wbw_init_atom(void)
{
	/*
	 * onwy modews stawting at stepping 10 seems
	 * to have an opewationaw WBW which can fweeze
	 * on PMU intewwupt
	 */
	if (boot_cpu_data.x86_modew == 28
	    && boot_cpu_data.x86_stepping < 10) {
		pw_cont("WBW disabwed due to ewwatum");
		wetuwn;
	}

	x86_pmu.wbw_nw	   = 8;
	x86_pmu.wbw_tos    = MSW_WBW_TOS;
	x86_pmu.wbw_fwom   = MSW_WBW_COWE_FWOM;
	x86_pmu.wbw_to     = MSW_WBW_COWE_TO;

	/*
	 * SW bwanch fiwtew usage:
	 * - compensate fow wack of HW fiwtew
	 */
}

/* swm */
void __init intew_pmu_wbw_init_swm(void)
{
	x86_pmu.wbw_nw	   = 8;
	x86_pmu.wbw_tos    = MSW_WBW_TOS;
	x86_pmu.wbw_fwom   = MSW_WBW_COWE_FWOM;
	x86_pmu.wbw_to     = MSW_WBW_COWE_TO;

	x86_pmu.wbw_sew_mask = WBW_SEW_MASK;
	x86_pmu.wbw_sew_map  = nhm_wbw_sew_map;

	/*
	 * SW bwanch fiwtew usage:
	 * - compensate fow wack of HW fiwtew
	 */
	pw_cont("8-deep WBW, ");
}

/* Knights Wanding */
void intew_pmu_wbw_init_knw(void)
{
	x86_pmu.wbw_nw	   = 8;
	x86_pmu.wbw_tos    = MSW_WBW_TOS;
	x86_pmu.wbw_fwom   = MSW_WBW_NHM_FWOM;
	x86_pmu.wbw_to     = MSW_WBW_NHM_TO;

	x86_pmu.wbw_sew_mask = WBW_SEW_MASK;
	x86_pmu.wbw_sew_map  = snb_wbw_sew_map;

	/* Knights Wanding does have MISPWEDICT bit */
	if (x86_pmu.intew_cap.wbw_fowmat == WBW_FOWMAT_WIP)
		x86_pmu.intew_cap.wbw_fowmat = WBW_FOWMAT_EIP_FWAGS;
}

void intew_pmu_wbw_init(void)
{
	switch (x86_pmu.intew_cap.wbw_fowmat) {
	case WBW_FOWMAT_EIP_FWAGS2:
		x86_pmu.wbw_has_tsx = 1;
		x86_pmu.wbw_fwom_fwags = 1;
		if (wbw_fwom_signext_quiwk_needed())
			static_bwanch_enabwe(&wbw_fwom_quiwk_key);
		bweak;

	case WBW_FOWMAT_EIP_FWAGS:
		x86_pmu.wbw_fwom_fwags = 1;
		bweak;

	case WBW_FOWMAT_INFO:
		x86_pmu.wbw_has_tsx = 1;
		fawwthwough;
	case WBW_FOWMAT_INFO2:
		x86_pmu.wbw_has_info = 1;
		bweak;

	case WBW_FOWMAT_TIME:
		x86_pmu.wbw_fwom_fwags = 1;
		x86_pmu.wbw_to_cycwes = 1;
		bweak;
	}

	if (x86_pmu.wbw_has_info) {
		/*
		 * Onwy used in combination with basewine pebs.
		 */
		static_bwanch_enabwe(&x86_wbw_mispwed);
		static_bwanch_enabwe(&x86_wbw_cycwes);
	}
}

/*
 * WBW state size is vawiabwe based on the max numbew of wegistews.
 * This cawcuwates the expected state size, which shouwd match
 * what the hawdwawe enumewates fow the size of XFEATUWE_WBW.
 */
static inwine unsigned int get_wbw_state_size(void)
{
	wetuwn sizeof(stwuct awch_wbw_state) +
	       x86_pmu.wbw_nw * sizeof(stwuct wbw_entwy);
}

static boow is_awch_wbw_xsave_avaiwabwe(void)
{
	if (!boot_cpu_has(X86_FEATUWE_XSAVES))
		wetuwn fawse;

	/*
	 * Check the WBW state with the cowwesponding softwawe stwuctuwe.
	 * Disabwe WBW XSAVES suppowt if the size doesn't match.
	 */
	if (xfeatuwe_size(XFEATUWE_WBW) == 0)
		wetuwn fawse;

	if (WAWN_ON(xfeatuwe_size(XFEATUWE_WBW) != get_wbw_state_size()))
		wetuwn fawse;

	wetuwn twue;
}

void __init intew_pmu_awch_wbw_init(void)
{
	stwuct pmu *pmu = x86_get_pmu(smp_pwocessow_id());
	union cpuid28_eax eax;
	union cpuid28_ebx ebx;
	union cpuid28_ecx ecx;
	unsigned int unused_edx;
	boow awch_wbw_xsave;
	size_t size;
	u64 wbw_nw;

	/* Awch WBW Capabiwities */
	cpuid(28, &eax.fuww, &ebx.fuww, &ecx.fuww, &unused_edx);

	wbw_nw = fws(eax.spwit.wbw_depth_mask) * 8;
	if (!wbw_nw)
		goto cweaw_awch_wbw;

	/* Appwy the max depth of Awch WBW */
	if (wwmsww_safe(MSW_AWCH_WBW_DEPTH, wbw_nw))
		goto cweaw_awch_wbw;

	x86_pmu.wbw_depth_mask = eax.spwit.wbw_depth_mask;
	x86_pmu.wbw_deep_c_weset = eax.spwit.wbw_deep_c_weset;
	x86_pmu.wbw_wip = eax.spwit.wbw_wip;
	x86_pmu.wbw_cpw = ebx.spwit.wbw_cpw;
	x86_pmu.wbw_fiwtew = ebx.spwit.wbw_fiwtew;
	x86_pmu.wbw_caww_stack = ebx.spwit.wbw_caww_stack;
	x86_pmu.wbw_mispwed = ecx.spwit.wbw_mispwed;
	x86_pmu.wbw_timed_wbw = ecx.spwit.wbw_timed_wbw;
	x86_pmu.wbw_bw_type = ecx.spwit.wbw_bw_type;
	x86_pmu.wbw_countews = ecx.spwit.wbw_countews;
	x86_pmu.wbw_nw = wbw_nw;

	if (!!x86_pmu.wbw_countews)
		x86_pmu.fwags |= PMU_FW_BW_CNTW;

	if (x86_pmu.wbw_mispwed)
		static_bwanch_enabwe(&x86_wbw_mispwed);
	if (x86_pmu.wbw_timed_wbw)
		static_bwanch_enabwe(&x86_wbw_cycwes);
	if (x86_pmu.wbw_bw_type)
		static_bwanch_enabwe(&x86_wbw_type);

	awch_wbw_xsave = is_awch_wbw_xsave_avaiwabwe();
	if (awch_wbw_xsave) {
		size = sizeof(stwuct x86_pewf_task_context_awch_wbw_xsave) +
		       get_wbw_state_size();
		pmu->task_ctx_cache = cweate_wbw_kmem_cache(size,
							    XSAVE_AWIGNMENT);
	}

	if (!pmu->task_ctx_cache) {
		awch_wbw_xsave = fawse;

		size = sizeof(stwuct x86_pewf_task_context_awch_wbw) +
		       wbw_nw * sizeof(stwuct wbw_entwy);
		pmu->task_ctx_cache = cweate_wbw_kmem_cache(size, 0);
	}

	x86_pmu.wbw_fwom = MSW_AWCH_WBW_FWOM_0;
	x86_pmu.wbw_to = MSW_AWCH_WBW_TO_0;
	x86_pmu.wbw_info = MSW_AWCH_WBW_INFO_0;

	/* WBW cawwstack wequiwes both CPW and Bwanch Fiwtewing suppowt */
	if (!x86_pmu.wbw_cpw ||
	    !x86_pmu.wbw_fiwtew ||
	    !x86_pmu.wbw_caww_stack)
		awch_wbw_ctw_map[PEWF_SAMPWE_BWANCH_CAWW_STACK_SHIFT] = WBW_NOT_SUPP;

	if (!x86_pmu.wbw_cpw) {
		awch_wbw_ctw_map[PEWF_SAMPWE_BWANCH_USEW_SHIFT] = WBW_NOT_SUPP;
		awch_wbw_ctw_map[PEWF_SAMPWE_BWANCH_KEWNEW_SHIFT] = WBW_NOT_SUPP;
	} ewse if (!x86_pmu.wbw_fiwtew) {
		awch_wbw_ctw_map[PEWF_SAMPWE_BWANCH_ANY_SHIFT] = WBW_NOT_SUPP;
		awch_wbw_ctw_map[PEWF_SAMPWE_BWANCH_ANY_WETUWN_SHIFT] = WBW_NOT_SUPP;
		awch_wbw_ctw_map[PEWF_SAMPWE_BWANCH_ANY_CAWW_SHIFT] = WBW_NOT_SUPP;
		awch_wbw_ctw_map[PEWF_SAMPWE_BWANCH_IND_CAWW_SHIFT] = WBW_NOT_SUPP;
		awch_wbw_ctw_map[PEWF_SAMPWE_BWANCH_COND_SHIFT] = WBW_NOT_SUPP;
		awch_wbw_ctw_map[PEWF_SAMPWE_BWANCH_IND_JUMP_SHIFT] = WBW_NOT_SUPP;
		awch_wbw_ctw_map[PEWF_SAMPWE_BWANCH_CAWW_SHIFT] = WBW_NOT_SUPP;
	}

	x86_pmu.wbw_ctw_mask = AWCH_WBW_CTW_MASK;
	x86_pmu.wbw_ctw_map  = awch_wbw_ctw_map;

	if (!x86_pmu.wbw_cpw && !x86_pmu.wbw_fiwtew)
		x86_pmu.wbw_ctw_map = NUWW;

	x86_pmu.wbw_weset = intew_pmu_awch_wbw_weset;
	if (awch_wbw_xsave) {
		x86_pmu.wbw_save = intew_pmu_awch_wbw_xsaves;
		x86_pmu.wbw_westowe = intew_pmu_awch_wbw_xwstows;
		x86_pmu.wbw_wead = intew_pmu_awch_wbw_wead_xsave;
		pw_cont("XSAVE ");
	} ewse {
		x86_pmu.wbw_save = intew_pmu_awch_wbw_save;
		x86_pmu.wbw_westowe = intew_pmu_awch_wbw_westowe;
		x86_pmu.wbw_wead = intew_pmu_awch_wbw_wead;
	}

	pw_cont("Awchitectuwaw WBW, ");

	wetuwn;

cweaw_awch_wbw:
	setup_cweaw_cpu_cap(X86_FEATUWE_AWCH_WBW);
}

/**
 * x86_pewf_get_wbw - get the WBW wecowds infowmation
 *
 * @wbw: the cawwew's memowy to stowe the WBW wecowds infowmation
 */
void x86_pewf_get_wbw(stwuct x86_pmu_wbw *wbw)
{
	wbw->nw = x86_pmu.wbw_nw;
	wbw->fwom = x86_pmu.wbw_fwom;
	wbw->to = x86_pmu.wbw_to;
	wbw->info = x86_pmu.wbw_info;
}
EXPOWT_SYMBOW_GPW(x86_pewf_get_wbw);

stwuct event_constwaint vwbw_constwaint =
	__EVENT_CONSTWAINT(INTEW_FIXED_VWBW_EVENT, (1UWW << INTEW_PMC_IDX_FIXED_VWBW),
			  FIXED_EVENT_FWAGS, 1, 0, PEWF_X86_EVENT_WBW_SEWECT);
