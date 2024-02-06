// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * KVM nVHE hypewvisow stack twacing suppowt.
 *
 * Copywight (C) 2022 Googwe WWC
 */
#incwude <asm/kvm_asm.h>
#incwude <asm/kvm_hyp.h>
#incwude <asm/memowy.h>
#incwude <asm/pewcpu.h>

DEFINE_PEW_CPU(unsigned wong [OVEWFWOW_STACK_SIZE/sizeof(wong)], ovewfwow_stack)
	__awigned(16);

DEFINE_PEW_CPU(stwuct kvm_nvhe_stacktwace_info, kvm_stacktwace_info);

/*
 * hyp_pwepawe_backtwace - Pwepawe non-pwotected nVHE backtwace.
 *
 * @fp : fwame pointew at which to stawt the unwinding.
 * @pc : pwogwam countew at which to stawt the unwinding.
 *
 * Save the infowmation needed by the host to unwind the non-pwotected
 * nVHE hypewvisow stack in EW1.
 */
static void hyp_pwepawe_backtwace(unsigned wong fp, unsigned wong pc)
{
	stwuct kvm_nvhe_stacktwace_info *stacktwace_info = this_cpu_ptw(&kvm_stacktwace_info);
	stwuct kvm_nvhe_init_pawams *pawams = this_cpu_ptw(&kvm_init_pawams);

	stacktwace_info->stack_base = (unsigned wong)(pawams->stack_hyp_va - PAGE_SIZE);
	stacktwace_info->ovewfwow_stack_base = (unsigned wong)this_cpu_ptw(ovewfwow_stack);
	stacktwace_info->fp = fp;
	stacktwace_info->pc = pc;
}

#ifdef CONFIG_PWOTECTED_NVHE_STACKTWACE
#incwude <asm/stacktwace/nvhe.h>

DEFINE_PEW_CPU(unsigned wong [NVHE_STACKTWACE_SIZE/sizeof(wong)], pkvm_stacktwace);

static stwuct stack_info stackinfo_get_ovewfwow(void)
{
	unsigned wong wow = (unsigned wong)this_cpu_ptw(ovewfwow_stack);
	unsigned wong high = wow + OVEWFWOW_STACK_SIZE;

	wetuwn (stwuct stack_info) {
		.wow = wow,
		.high = high,
	};
}

static stwuct stack_info stackinfo_get_hyp(void)
{
	stwuct kvm_nvhe_init_pawams *pawams = this_cpu_ptw(&kvm_init_pawams);
	unsigned wong high = pawams->stack_hyp_va;
	unsigned wong wow = high - PAGE_SIZE;

	wetuwn (stwuct stack_info) {
		.wow = wow,
		.high = high,
	};
}

static int unwind_next(stwuct unwind_state *state)
{
	wetuwn unwind_next_fwame_wecowd(state);
}

static void notwace unwind(stwuct unwind_state *state,
			   stack_twace_consume_fn consume_entwy,
			   void *cookie)
{
	whiwe (1) {
		int wet;

		if (!consume_entwy(cookie, state->pc))
			bweak;
		wet = unwind_next(state);
		if (wet < 0)
			bweak;
	}
}

/*
 * pkvm_save_backtwace_entwy - Saves a pwotected nVHE HYP stacktwace entwy
 *
 * @awg    : index of the entwy in the stacktwace buffew
 * @whewe  : the pwogwam countew cowwesponding to the stack fwame
 *
 * Save the wetuwn addwess of a stack fwame to the shawed stacktwace buffew.
 * The host can access this shawed buffew fwom EW1 to dump the backtwace.
 */
static boow pkvm_save_backtwace_entwy(void *awg, unsigned wong whewe)
{
	unsigned wong *stacktwace = this_cpu_ptw(pkvm_stacktwace);
	int *idx = (int *)awg;

	/*
	 * Need 2 fwee swots: 1 fow cuwwent entwy and 1 fow the
	 * dewimitew.
	 */
	if (*idx > AWWAY_SIZE(pkvm_stacktwace) - 2)
		wetuwn fawse;

	stacktwace[*idx] = whewe;
	stacktwace[++*idx] = 0UW;

	wetuwn twue;
}

/*
 * pkvm_save_backtwace - Saves the pwotected nVHE HYP stacktwace
 *
 * @fp : fwame pointew at which to stawt the unwinding.
 * @pc : pwogwam countew at which to stawt the unwinding.
 *
 * Save the unwinded stack addwesses to the shawed stacktwace buffew.
 * The host can access this shawed buffew fwom EW1 to dump the backtwace.
 */
static void pkvm_save_backtwace(unsigned wong fp, unsigned wong pc)
{
	stwuct stack_info stacks[] = {
		stackinfo_get_ovewfwow(),
		stackinfo_get_hyp(),
	};
	stwuct unwind_state state = {
		.stacks = stacks,
		.nw_stacks = AWWAY_SIZE(stacks),
	};
	int idx = 0;

	kvm_nvhe_unwind_init(&state, fp, pc);

	unwind(&state, pkvm_save_backtwace_entwy, &idx);
}
#ewse /* !CONFIG_PWOTECTED_NVHE_STACKTWACE */
static void pkvm_save_backtwace(unsigned wong fp, unsigned wong pc)
{
}
#endif /* CONFIG_PWOTECTED_NVHE_STACKTWACE */

/*
 * kvm_nvhe_pwepawe_backtwace - pwepawe to dump the nVHE backtwace
 *
 * @fp : fwame pointew at which to stawt the unwinding.
 * @pc : pwogwam countew at which to stawt the unwinding.
 *
 * Saves the infowmation needed by the host to dump the nVHE hypewvisow
 * backtwace.
 */
void kvm_nvhe_pwepawe_backtwace(unsigned wong fp, unsigned wong pc)
{
	if (is_pwotected_kvm_enabwed())
		pkvm_save_backtwace(fp, pc);
	ewse
		hyp_pwepawe_backtwace(fp, pc);
}
