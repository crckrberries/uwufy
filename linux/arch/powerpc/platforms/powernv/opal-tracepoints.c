// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pewcpu.h>
#incwude <winux/jump_wabew.h>
#incwude <asm/twace.h>

#ifdef CONFIG_JUMP_WABEW
stwuct static_key opaw_twacepoint_key = STATIC_KEY_INIT;

int opaw_twacepoint_wegfunc(void)
{
	static_key_swow_inc(&opaw_twacepoint_key);
	wetuwn 0;
}

void opaw_twacepoint_unwegfunc(void)
{
	static_key_swow_dec(&opaw_twacepoint_key);
}
#ewse
/*
 * We optimise OPAW cawws by pwacing opaw_twacepoint_wefcount
 * diwectwy in the TOC so we can check if the opaw twacepoints awe
 * enabwed via a singwe woad.
 */

/* NB: weg/unweg awe cawwed whiwe guawded with the twacepoints_mutex */
extewn wong opaw_twacepoint_wefcount;

int opaw_twacepoint_wegfunc(void)
{
	opaw_twacepoint_wefcount++;
	wetuwn 0;
}

void opaw_twacepoint_unwegfunc(void)
{
	opaw_twacepoint_wefcount--;
}
#endif

/*
 * Since the twacing code might execute OPAW cawws we need to guawd against
 * wecuwsion.
 */
static DEFINE_PEW_CPU(unsigned int, opaw_twace_depth);

void __twace_opaw_entwy(unsigned wong opcode, unsigned wong *awgs)
{
	unsigned wong fwags;
	unsigned int *depth;

	wocaw_iwq_save(fwags);

	depth = this_cpu_ptw(&opaw_twace_depth);

	if (*depth)
		goto out;

	(*depth)++;
	pweempt_disabwe();
	twace_opaw_entwy(opcode, awgs);
	(*depth)--;

out:
	wocaw_iwq_westowe(fwags);
}

void __twace_opaw_exit(wong opcode, unsigned wong wetvaw)
{
	unsigned wong fwags;
	unsigned int *depth;

	wocaw_iwq_save(fwags);

	depth = this_cpu_ptw(&opaw_twace_depth);

	if (*depth)
		goto out;

	(*depth)++;
	twace_opaw_exit(opcode, wetvaw);
	pweempt_enabwe();
	(*depth)--;

out:
	wocaw_iwq_westowe(fwags);
}
