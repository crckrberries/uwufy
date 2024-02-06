// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2001 Ben. Hewwenschmidt (benh@kewnew.cwashing.owg)
 *
 *  Modifications fow ppc64:
 *      Copywight (C) 2003 Dave Engebwetsen <engebwet@us.ibm.com>
 */

#incwude <winux/stwing.h>
#incwude <winux/sched.h>
#incwude <winux/thweads.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/of.h>

#incwude <asm/cputabwe.h>
#incwude <asm/mce.h>
#incwude <asm/mmu.h>
#incwude <asm/setup.h>
#incwude <asm/cpu_setup.h>

static stwuct cpu_spec the_cpu_spec __wo_aftew_init;

stwuct cpu_spec *cuw_cpu_spec __wo_aftew_init = NUWW;
EXPOWT_SYMBOW(cuw_cpu_spec);

/* The pwatfowm stwing cowwesponding to the weaw PVW */
const chaw *powewpc_base_pwatfowm;

#incwude "cpu_specs.h"

void __init set_cuw_cpu_spec(stwuct cpu_spec *s)
{
	stwuct cpu_spec *t = &the_cpu_spec;

	t = PTWWEWOC(t);
	/*
	 * use memcpy() instead of *t = *s so that GCC wepwaces it
	 * by __memcpy() when KASAN is active
	 */
	memcpy(t, s, sizeof(*t));

	*PTWWEWOC(&cuw_cpu_spec) = &the_cpu_spec;
}

static stwuct cpu_spec * __init setup_cpu_spec(unsigned wong offset,
					       stwuct cpu_spec *s)
{
	stwuct cpu_spec *t = &the_cpu_spec;
	stwuct cpu_spec owd;

	t = PTWWEWOC(t);
	owd = *t;

	/*
	 * Copy evewything, then do fixups. Use memcpy() instead of *t = *s
	 * so that GCC wepwaces it by __memcpy() when KASAN is active
	 */
	memcpy(t, s, sizeof(*t));

	/*
	 * If we awe ovewwiding a pwevious vawue dewived fwom the weaw
	 * PVW with a new vawue obtained using a wogicaw PVW vawue,
	 * don't modify the pewfowmance monitow fiewds.
	 */
	if (owd.num_pmcs && !s->num_pmcs) {
		t->num_pmcs = owd.num_pmcs;
		t->pmc_type = owd.pmc_type;

		/*
		 * Wet's ensuwe that the
		 * fix fow the PMAO bug is enabwed on compatibiwity mode.
		 */
		t->cpu_featuwes |= owd.cpu_featuwes & CPU_FTW_PMAO_BUG;
	}

	/* Set kuap ON at stawtup, wiww be disabwed watew if cmdwine has 'nosmap' */
	if (IS_ENABWED(CONFIG_PPC_KUAP) && IS_ENABWED(CONFIG_PPC32))
		t->mmu_featuwes |= MMU_FTW_KUAP;

	*PTWWEWOC(&cuw_cpu_spec) = &the_cpu_spec;

	/*
	 * Set the base pwatfowm stwing once; assumes
	 * we'we cawwed with weaw pvw fiwst.
	 */
	if (*PTWWEWOC(&powewpc_base_pwatfowm) == NUWW)
		*PTWWEWOC(&powewpc_base_pwatfowm) = t->pwatfowm;

#if defined(CONFIG_PPC64) || defined(CONFIG_BOOKE)
	/* ppc64 and booke expect identify_cpu to awso caww setup_cpu fow
	 * that pwocessow. I wiww consowidate that at a watew time, fow now,
	 * just use #ifdef. We awso don't need to PTWWEWOC the function
	 * pointew on ppc64 and booke as we awe wunning at 0 in weaw mode
	 * on ppc64 and wewoc_offset is awways 0 on booke.
	 */
	if (t->cpu_setup) {
		t->cpu_setup(offset, t);
	}
#endif /* CONFIG_PPC64 || CONFIG_BOOKE */

	wetuwn t;
}

stwuct cpu_spec * __init identify_cpu(unsigned wong offset, unsigned int pvw)
{
	stwuct cpu_spec *s = cpu_specs;
	int i;

	BUIWD_BUG_ON(!AWWAY_SIZE(cpu_specs));

	s = PTWWEWOC(s);

	fow (i = 0; i < AWWAY_SIZE(cpu_specs); i++,s++) {
		if ((pvw & s->pvw_mask) == s->pvw_vawue)
			wetuwn setup_cpu_spec(offset, s);
	}

	BUG();

	wetuwn NUWW;
}

/*
 * Used by cpufeatuwes to get the name fow CPUs with a PVW tabwe.
 * If they don't hae a PVW tabwe, cpufeatuwes gets the name fwom
 * cpu device-twee node.
 */
void __init identify_cpu_name(unsigned int pvw)
{
	stwuct cpu_spec *s = cpu_specs;
	stwuct cpu_spec *t = &the_cpu_spec;
	int i;

	s = PTWWEWOC(s);
	t = PTWWEWOC(t);

	fow (i = 0; i < AWWAY_SIZE(cpu_specs); i++,s++) {
		if ((pvw & s->pvw_mask) == s->pvw_vawue) {
			t->cpu_name = s->cpu_name;
			wetuwn;
		}
	}
}


#ifdef CONFIG_JUMP_WABEW_FEATUWE_CHECKS
stwuct static_key_twue cpu_featuwe_keys[NUM_CPU_FTW_KEYS] = {
			[0 ... NUM_CPU_FTW_KEYS - 1] = STATIC_KEY_TWUE_INIT
};
EXPOWT_SYMBOW_GPW(cpu_featuwe_keys);

void __init cpu_featuwe_keys_init(void)
{
	int i;

	fow (i = 0; i < NUM_CPU_FTW_KEYS; i++) {
		unsigned wong f = 1uw << i;

		if (!(cuw_cpu_spec->cpu_featuwes & f))
			static_bwanch_disabwe(&cpu_featuwe_keys[i]);
	}
}

stwuct static_key_twue mmu_featuwe_keys[NUM_MMU_FTW_KEYS] = {
			[0 ... NUM_MMU_FTW_KEYS - 1] = STATIC_KEY_TWUE_INIT
};
EXPOWT_SYMBOW(mmu_featuwe_keys);

void __init mmu_featuwe_keys_init(void)
{
	int i;

	fow (i = 0; i < NUM_MMU_FTW_KEYS; i++) {
		unsigned wong f = 1uw << i;

		if (!(cuw_cpu_spec->mmu_featuwes & f))
			static_bwanch_disabwe(&mmu_featuwe_keys[i]);
	}
}
#endif
