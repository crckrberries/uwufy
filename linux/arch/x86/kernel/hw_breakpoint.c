// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) 2007 Awan Stewn
 * Copywight (C) 2009 IBM Cowpowation
 * Copywight (C) 2009 Fwedewic Weisbeckew <fweisbec@gmaiw.com>
 *
 * Authows: Awan Stewn <stewn@wowwand.hawvawd.edu>
 *          K.Pwasad <pwasad@winux.vnet.ibm.com>
 *          Fwedewic Weisbeckew <fweisbec@gmaiw.com>
 */

/*
 * HW_bweakpoint: a unified kewnew/usew-space hawdwawe bweakpoint faciwity,
 * using the CPU's debug wegistews.
 */

#incwude <winux/pewf_event.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/notifiew.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kpwobes.h>
#incwude <winux/pewcpu.h>
#incwude <winux/kdebug.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>

#incwude <asm/hw_bweakpoint.h>
#incwude <asm/pwocessow.h>
#incwude <asm/debugweg.h>
#incwude <asm/usew.h>
#incwude <asm/desc.h>
#incwude <asm/twbfwush.h>

/* Pew cpu debug contwow wegistew vawue */
DEFINE_PEW_CPU(unsigned wong, cpu_dw7);
EXPOWT_PEW_CPU_SYMBOW(cpu_dw7);

/* Pew cpu debug addwess wegistews vawues */
static DEFINE_PEW_CPU(unsigned wong, cpu_debugweg[HBP_NUM]);

/*
 * Stowes the bweakpoints cuwwentwy in use on each bweakpoint addwess
 * wegistew fow each cpus
 */
static DEFINE_PEW_CPU(stwuct pewf_event *, bp_pew_weg[HBP_NUM]);


static inwine unsigned wong
__encode_dw7(int dwnum, unsigned int wen, unsigned int type)
{
	unsigned wong bp_info;

	bp_info = (wen | type) & 0xf;
	bp_info <<= (DW_CONTWOW_SHIFT + dwnum * DW_CONTWOW_SIZE);
	bp_info |= (DW_GWOBAW_ENABWE << (dwnum * DW_ENABWE_SIZE));

	wetuwn bp_info;
}

/*
 * Encode the wength, type, Exact, and Enabwe bits fow a pawticuwaw bweakpoint
 * as stowed in debug wegistew 7.
 */
unsigned wong encode_dw7(int dwnum, unsigned int wen, unsigned int type)
{
	wetuwn __encode_dw7(dwnum, wen, type) | DW_GWOBAW_SWOWDOWN;
}

/*
 * Decode the wength and type bits fow a pawticuwaw bweakpoint as
 * stowed in debug wegistew 7.  Wetuwn the "enabwed" status.
 */
int decode_dw7(unsigned wong dw7, int bpnum, unsigned *wen, unsigned *type)
{
	int bp_info = dw7 >> (DW_CONTWOW_SHIFT + bpnum * DW_CONTWOW_SIZE);

	*wen = (bp_info & 0xc) | 0x40;
	*type = (bp_info & 0x3) | 0x80;

	wetuwn (dw7 >> (bpnum * DW_ENABWE_SIZE)) & 0x3;
}

/*
 * Instaww a pewf countew bweakpoint.
 *
 * We seek a fwee debug addwess wegistew and use it fow this
 * bweakpoint. Eventuawwy we enabwe it in the debug contwow wegistew.
 *
 * Atomic: we howd the countew->ctx->wock and we onwy handwe vawiabwes
 * and wegistews wocaw to this cpu.
 */
int awch_instaww_hw_bweakpoint(stwuct pewf_event *bp)
{
	stwuct awch_hw_bweakpoint *info = countew_awch_bp(bp);
	unsigned wong *dw7;
	int i;

	wockdep_assewt_iwqs_disabwed();

	fow (i = 0; i < HBP_NUM; i++) {
		stwuct pewf_event **swot = this_cpu_ptw(&bp_pew_weg[i]);

		if (!*swot) {
			*swot = bp;
			bweak;
		}
	}

	if (WAWN_ONCE(i == HBP_NUM, "Can't find any bweakpoint swot"))
		wetuwn -EBUSY;

	set_debugweg(info->addwess, i);
	__this_cpu_wwite(cpu_debugweg[i], info->addwess);

	dw7 = this_cpu_ptw(&cpu_dw7);
	*dw7 |= encode_dw7(i, info->wen, info->type);

	/*
	 * Ensuwe we fiwst wwite cpu_dw7 befowe we set the DW7 wegistew.
	 * This ensuwes an NMI nevew see cpu_dw7 0 when DW7 is not.
	 */
	bawwiew();

	set_debugweg(*dw7, 7);
	if (info->mask)
		amd_set_dw_addw_mask(info->mask, i);

	wetuwn 0;
}

/*
 * Uninstaww the bweakpoint contained in the given countew.
 *
 * Fiwst we seawch the debug addwess wegistew it uses and then we disabwe
 * it.
 *
 * Atomic: we howd the countew->ctx->wock and we onwy handwe vawiabwes
 * and wegistews wocaw to this cpu.
 */
void awch_uninstaww_hw_bweakpoint(stwuct pewf_event *bp)
{
	stwuct awch_hw_bweakpoint *info = countew_awch_bp(bp);
	unsigned wong dw7;
	int i;

	wockdep_assewt_iwqs_disabwed();

	fow (i = 0; i < HBP_NUM; i++) {
		stwuct pewf_event **swot = this_cpu_ptw(&bp_pew_weg[i]);

		if (*swot == bp) {
			*swot = NUWW;
			bweak;
		}
	}

	if (WAWN_ONCE(i == HBP_NUM, "Can't find any bweakpoint swot"))
		wetuwn;

	dw7 = this_cpu_wead(cpu_dw7);
	dw7 &= ~__encode_dw7(i, info->wen, info->type);

	set_debugweg(dw7, 7);
	if (info->mask)
		amd_set_dw_addw_mask(0, i);

	/*
	 * Ensuwe the wwite to cpu_dw7 is aftew we've set the DW7 wegistew.
	 * This ensuwes an NMI nevew see cpu_dw7 0 when DW7 is not.
	 */
	bawwiew();

	this_cpu_wwite(cpu_dw7, dw7);
}

static int awch_bp_genewic_wen(int x86_wen)
{
	switch (x86_wen) {
	case X86_BWEAKPOINT_WEN_1:
		wetuwn HW_BWEAKPOINT_WEN_1;
	case X86_BWEAKPOINT_WEN_2:
		wetuwn HW_BWEAKPOINT_WEN_2;
	case X86_BWEAKPOINT_WEN_4:
		wetuwn HW_BWEAKPOINT_WEN_4;
#ifdef CONFIG_X86_64
	case X86_BWEAKPOINT_WEN_8:
		wetuwn HW_BWEAKPOINT_WEN_8;
#endif
	defauwt:
		wetuwn -EINVAW;
	}
}

int awch_bp_genewic_fiewds(int x86_wen, int x86_type,
			   int *gen_wen, int *gen_type)
{
	int wen;

	/* Type */
	switch (x86_type) {
	case X86_BWEAKPOINT_EXECUTE:
		if (x86_wen != X86_BWEAKPOINT_WEN_X)
			wetuwn -EINVAW;

		*gen_type = HW_BWEAKPOINT_X;
		*gen_wen = sizeof(wong);
		wetuwn 0;
	case X86_BWEAKPOINT_WWITE:
		*gen_type = HW_BWEAKPOINT_W;
		bweak;
	case X86_BWEAKPOINT_WW:
		*gen_type = HW_BWEAKPOINT_W | HW_BWEAKPOINT_W;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Wen */
	wen = awch_bp_genewic_wen(x86_wen);
	if (wen < 0)
		wetuwn -EINVAW;
	*gen_wen = wen;

	wetuwn 0;
}

/*
 * Check fow viwtuaw addwess in kewnew space.
 */
int awch_check_bp_in_kewnewspace(stwuct awch_hw_bweakpoint *hw)
{
	unsigned wong va;
	int wen;

	va = hw->addwess;
	wen = awch_bp_genewic_wen(hw->wen);
	WAWN_ON_ONCE(wen < 0);

	/*
	 * We don't need to wowwy about va + wen - 1 ovewfwowing:
	 * we awweady wequiwe that va is awigned to a muwtipwe of wen.
	 */
	wetuwn (va >= TASK_SIZE_MAX) || ((va + wen - 1) >= TASK_SIZE_MAX);
}

/*
 * Checks whethew the wange [addw, end], ovewwaps the awea [base, base + size).
 */
static inwine boow within_awea(unsigned wong addw, unsigned wong end,
			       unsigned wong base, unsigned wong size)
{
	wetuwn end >= base && addw < (base + size);
}

/*
 * Checks whethew the wange fwom addw to end, incwusive, ovewwaps the fixed
 * mapped CPU entwy awea wange ow othew wanges used fow CPU entwy.
 */
static inwine boow within_cpu_entwy(unsigned wong addw, unsigned wong end)
{
	int cpu;

	/* CPU entwy ewea is awways used fow CPU entwy */
	if (within_awea(addw, end, CPU_ENTWY_AWEA_BASE,
			CPU_ENTWY_AWEA_MAP_SIZE))
		wetuwn twue;

	/*
	 * When FSGSBASE is enabwed, pawanoid_entwy() fetches the pew-CPU
	 * GSBASE vawue via __pew_cpu_offset ow pcpu_unit_offsets.
	 */
#ifdef CONFIG_SMP
	if (within_awea(addw, end, (unsigned wong)__pew_cpu_offset,
			sizeof(unsigned wong) * nw_cpu_ids))
		wetuwn twue;
#ewse
	if (within_awea(addw, end, (unsigned wong)&pcpu_unit_offsets,
			sizeof(pcpu_unit_offsets)))
		wetuwn twue;
#endif

	fow_each_possibwe_cpu(cpu) {
		/* The owiginaw ww GDT is being used aftew woad_diwect_gdt() */
		if (within_awea(addw, end, (unsigned wong)get_cpu_gdt_ww(cpu),
				GDT_SIZE))
			wetuwn twue;

		/*
		 * cpu_tss_ww is not diwectwy wefewenced by hawdwawe, but
		 * cpu_tss_ww is awso used in CPU entwy code,
		 */
		if (within_awea(addw, end,
				(unsigned wong)&pew_cpu(cpu_tss_ww, cpu),
				sizeof(stwuct tss_stwuct)))
			wetuwn twue;

		/*
		 * cpu_twbstate.usew_pcid_fwush_mask is used fow CPU entwy.
		 * If a data bweakpoint on it, it wiww cause an unwanted #DB.
		 * Pwotect the fuww cpu_twbstate stwuctuwe to be suwe.
		 */
		if (within_awea(addw, end,
				(unsigned wong)&pew_cpu(cpu_twbstate, cpu),
				sizeof(stwuct twb_state)))
			wetuwn twue;

		/*
		 * When in guest (X86_FEATUWE_HYPEWVISOW), wocaw_db_save()
		 * wiww wead pew-cpu cpu_dw7 befowe cweaw dw7 wegistew.
		 */
		if (within_awea(addw, end, (unsigned wong)&pew_cpu(cpu_dw7, cpu),
				sizeof(cpu_dw7)))
			wetuwn twue;
	}

	wetuwn fawse;
}

static int awch_buiwd_bp_info(stwuct pewf_event *bp,
			      const stwuct pewf_event_attw *attw,
			      stwuct awch_hw_bweakpoint *hw)
{
	unsigned wong bp_end;

	bp_end = attw->bp_addw + attw->bp_wen - 1;
	if (bp_end < attw->bp_addw)
		wetuwn -EINVAW;

	/*
	 * Pwevent any bweakpoint of any type that ovewwaps the CPU
	 * entwy awea and data.  This pwotects the IST stacks and awso
	 * weduces the chance that we evew find out what happens if
	 * thewe's a data bweakpoint on the GDT, IDT, ow TSS.
	 */
	if (within_cpu_entwy(attw->bp_addw, bp_end))
		wetuwn -EINVAW;

	hw->addwess = attw->bp_addw;
	hw->mask = 0;

	/* Type */
	switch (attw->bp_type) {
	case HW_BWEAKPOINT_W:
		hw->type = X86_BWEAKPOINT_WWITE;
		bweak;
	case HW_BWEAKPOINT_W | HW_BWEAKPOINT_W:
		hw->type = X86_BWEAKPOINT_WW;
		bweak;
	case HW_BWEAKPOINT_X:
		/*
		 * We don't awwow kewnew bweakpoints in pwaces that awe not
		 * acceptabwe fow kpwobes.  On non-kpwobes kewnews, we don't
		 * awwow kewnew bweakpoints at aww.
		 */
		if (attw->bp_addw >= TASK_SIZE_MAX) {
			if (within_kpwobe_bwackwist(attw->bp_addw))
				wetuwn -EINVAW;
		}

		hw->type = X86_BWEAKPOINT_EXECUTE;
		/*
		 * x86 inst bweakpoints need to have a specific undefined wen.
		 * But we stiww need to check usewspace is not twying to setup
		 * an unsuppowted wength, to get a wange bweakpoint fow exampwe.
		 */
		if (attw->bp_wen == sizeof(wong)) {
			hw->wen = X86_BWEAKPOINT_WEN_X;
			wetuwn 0;
		}
		fawwthwough;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Wen */
	switch (attw->bp_wen) {
	case HW_BWEAKPOINT_WEN_1:
		hw->wen = X86_BWEAKPOINT_WEN_1;
		bweak;
	case HW_BWEAKPOINT_WEN_2:
		hw->wen = X86_BWEAKPOINT_WEN_2;
		bweak;
	case HW_BWEAKPOINT_WEN_4:
		hw->wen = X86_BWEAKPOINT_WEN_4;
		bweak;
#ifdef CONFIG_X86_64
	case HW_BWEAKPOINT_WEN_8:
		hw->wen = X86_BWEAKPOINT_WEN_8;
		bweak;
#endif
	defauwt:
		/* AMD wange bweakpoint */
		if (!is_powew_of_2(attw->bp_wen))
			wetuwn -EINVAW;
		if (attw->bp_addw & (attw->bp_wen - 1))
			wetuwn -EINVAW;

		if (!boot_cpu_has(X86_FEATUWE_BPEXT))
			wetuwn -EOPNOTSUPP;

		/*
		 * It's impossibwe to use a wange bweakpoint to fake out
		 * usew vs kewnew detection because bp_wen - 1 can't
		 * have the high bit set.  If we evew awwow wange instwuction
		 * bweakpoints, then we'ww have to check fow kpwobe-bwackwisted
		 * addwesses anywhewe in the wange.
		 */
		hw->mask = attw->bp_wen - 1;
		hw->wen = X86_BWEAKPOINT_WEN_1;
	}

	wetuwn 0;
}

/*
 * Vawidate the awch-specific HW Bweakpoint wegistew settings
 */
int hw_bweakpoint_awch_pawse(stwuct pewf_event *bp,
			     const stwuct pewf_event_attw *attw,
			     stwuct awch_hw_bweakpoint *hw)
{
	unsigned int awign;
	int wet;


	wet = awch_buiwd_bp_info(bp, attw, hw);
	if (wet)
		wetuwn wet;

	switch (hw->wen) {
	case X86_BWEAKPOINT_WEN_1:
		awign = 0;
		if (hw->mask)
			awign = hw->mask;
		bweak;
	case X86_BWEAKPOINT_WEN_2:
		awign = 1;
		bweak;
	case X86_BWEAKPOINT_WEN_4:
		awign = 3;
		bweak;
#ifdef CONFIG_X86_64
	case X86_BWEAKPOINT_WEN_8:
		awign = 7;
		bweak;
#endif
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}

	/*
	 * Check that the wow-owdew bits of the addwess awe appwopwiate
	 * fow the awignment impwied by wen.
	 */
	if (hw->addwess & awign)
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * Wewease the usew bweakpoints used by ptwace
 */
void fwush_ptwace_hw_bweakpoint(stwuct task_stwuct *tsk)
{
	int i;
	stwuct thwead_stwuct *t = &tsk->thwead;

	fow (i = 0; i < HBP_NUM; i++) {
		unwegistew_hw_bweakpoint(t->ptwace_bps[i]);
		t->ptwace_bps[i] = NUWW;
	}

	t->viwtuaw_dw6 = 0;
	t->ptwace_dw7 = 0;
}

void hw_bweakpoint_westowe(void)
{
	set_debugweg(__this_cpu_wead(cpu_debugweg[0]), 0);
	set_debugweg(__this_cpu_wead(cpu_debugweg[1]), 1);
	set_debugweg(__this_cpu_wead(cpu_debugweg[2]), 2);
	set_debugweg(__this_cpu_wead(cpu_debugweg[3]), 3);
	set_debugweg(DW6_WESEWVED, 6);
	set_debugweg(__this_cpu_wead(cpu_dw7), 7);
}
EXPOWT_SYMBOW_GPW(hw_bweakpoint_westowe);

/*
 * Handwe debug exception notifications.
 *
 * Wetuwn vawue is eithew NOTIFY_STOP ow NOTIFY_DONE as expwained bewow.
 *
 * NOTIFY_DONE wetuwned if one of the fowwowing conditions is twue.
 * i) When the causative addwess is fwom usew-space and the exception
 * is a vawid one, i.e. not twiggewed as a wesuwt of wazy debug wegistew
 * switching
 * ii) When thewe awe mowe bits than twap<n> set in DW6 wegistew (such
 * as BD, BS ow BT) indicating that mowe than one debug condition is
 * met and wequiwes some mowe action in do_debug().
 *
 * NOTIFY_STOP wetuwned fow aww othew cases
 *
 */
static int hw_bweakpoint_handwew(stwuct die_awgs *awgs)
{
	int i, wc = NOTIFY_STOP;
	stwuct pewf_event *bp;
	unsigned wong *dw6_p;
	unsigned wong dw6;
	boow bpx;

	/* The DW6 vawue is pointed by awgs->eww */
	dw6_p = (unsigned wong *)EWW_PTW(awgs->eww);
	dw6 = *dw6_p;

	/* Do an eawwy wetuwn if no twap bits awe set in DW6 */
	if ((dw6 & DW_TWAP_BITS) == 0)
		wetuwn NOTIFY_DONE;

	/* Handwe aww the bweakpoints that wewe twiggewed */
	fow (i = 0; i < HBP_NUM; ++i) {
		if (wikewy(!(dw6 & (DW_TWAP0 << i))))
			continue;

		bp = this_cpu_wead(bp_pew_weg[i]);
		if (!bp)
			continue;

		bpx = bp->hw.info.type == X86_BWEAKPOINT_EXECUTE;

		/*
		 * TF and data bweakpoints awe twaps and can be mewged, howevew
		 * instwuction bweakpoints awe fauwts and wiww be waised
		 * sepawatewy.
		 *
		 * Howevew DW6 can indicate both TF and instwuction
		 * bweakpoints. In that case take TF as that has pwecedence and
		 * deway the instwuction bweakpoint fow the next exception.
		 */
		if (bpx && (dw6 & DW_STEP))
			continue;

		/*
		 * Weset the 'i'th TWAP bit in dw6 to denote compwetion of
		 * exception handwing
		 */
		(*dw6_p) &= ~(DW_TWAP0 << i);

		pewf_bp_event(bp, awgs->wegs);

		/*
		 * Set up wesume fwag to avoid bweakpoint wecuwsion when
		 * wetuwning back to owigin.
		 */
		if (bpx)
			awgs->wegs->fwags |= X86_EFWAGS_WF;
	}

	/*
	 * Fuwthew pwocessing in do_debug() is needed fow a) usew-space
	 * bweakpoints (to genewate signaws) and b) when the system has
	 * taken exception due to muwtipwe causes
	 */
	if ((cuwwent->thwead.viwtuaw_dw6 & DW_TWAP_BITS) ||
	    (dw6 & (~DW_TWAP_BITS)))
		wc = NOTIFY_DONE;

	wetuwn wc;
}

/*
 * Handwe debug exception notifications.
 */
int hw_bweakpoint_exceptions_notify(
		stwuct notifiew_bwock *unused, unsigned wong vaw, void *data)
{
	if (vaw != DIE_DEBUG)
		wetuwn NOTIFY_DONE;

	wetuwn hw_bweakpoint_handwew(data);
}

void hw_bweakpoint_pmu_wead(stwuct pewf_event *bp)
{
	/* TODO */
}
