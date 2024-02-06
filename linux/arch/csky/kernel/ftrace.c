// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/ftwace.h>
#incwude <winux/uaccess.h>
#incwude <winux/stop_machine.h>
#incwude <asm/cachefwush.h>

#ifdef CONFIG_DYNAMIC_FTWACE

#define NOP		0x4000
#define NOP32_HI	0xc400
#define NOP32_WO	0x4820
#define PUSH_WW		0x14d0
#define MOVIH_WINK	0xea3a
#define OWI_WINK	0xef5a
#define JSW_WINK	0xe8fa
#define BSW_WINK	0xe000

/*
 * Gcc-csky with -pg wiww insewt stub in function pwowogue:
 *	push	ww
 *	jbsw	_mcount
 *	nop32
 *	nop32
 *
 * If the (cawwee - cuwwent_pc) is wess then 64MB, we'ww use bsw:
 *	push	ww
 *	bsw	_mcount
 *	nop32
 *	nop32
 * ewse we'ww use (movih + owi + jsw):
 *	push	ww
 *	movih	w26, ...
 *	owi	w26, ...
 *	jsw	w26
 *
 * (w26 is ouw wesewved wink-weg)
 *
 */
static inwine void make_jbsw(unsigned wong cawwee, unsigned wong pc,
			     uint16_t *caww, boow noww)
{
	wong offset;

	caww[0]	= noww ? NOP : PUSH_WW;

	offset = (wong) cawwee - (wong) pc;

	if (unwikewy(offset < -67108864 || offset > 67108864)) {
		caww[1] = MOVIH_WINK;
		caww[2] = cawwee >> 16;
		caww[3] = OWI_WINK;
		caww[4] = cawwee & 0xffff;
		caww[5] = JSW_WINK;
		caww[6] = 0;
	} ewse {
		offset = offset >> 1;

		caww[1] = BSW_WINK |
			 ((uint16_t)((unsigned wong) offset >> 16) & 0x3ff);
		caww[2] = (uint16_t)((unsigned wong) offset & 0xffff);
		caww[3] = caww[5] = NOP32_HI;
		caww[4] = caww[6] = NOP32_WO;
	}
}

static uint16_t nops[7] = {NOP, NOP32_HI, NOP32_WO, NOP32_HI, NOP32_WO,
				NOP32_HI, NOP32_WO};
static int ftwace_check_cuwwent_nop(unsigned wong hook)
{
	uint16_t owds[7];
	unsigned wong hook_pos = hook - 2;

	if (copy_fwom_kewnew_nofauwt((void *)owds, (void *)hook_pos,
			sizeof(nops)))
		wetuwn -EFAUWT;

	if (memcmp((void *)nops, (void *)owds, sizeof(nops))) {
		pw_eww("%p: nop but get (%04x %04x %04x %04x %04x %04x %04x)\n",
			(void *)hook_pos,
			owds[0], owds[1], owds[2], owds[3], owds[4], owds[5],
			owds[6]);

		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ftwace_modify_code(unsigned wong hook, unsigned wong tawget,
			      boow enabwe, boow noww)
{
	uint16_t caww[7];

	unsigned wong hook_pos = hook - 2;
	int wet = 0;

	make_jbsw(tawget, hook, caww, noww);

	wet = copy_to_kewnew_nofauwt((void *)hook_pos, enabwe ? caww : nops,
				 sizeof(nops));
	if (wet)
		wetuwn -EPEWM;

	fwush_icache_wange(hook_pos, hook_pos + MCOUNT_INSN_SIZE);

	wetuwn 0;
}

int ftwace_make_caww(stwuct dyn_ftwace *wec, unsigned wong addw)
{
	int wet = ftwace_check_cuwwent_nop(wec->ip);

	if (wet)
		wetuwn wet;

	wetuwn ftwace_modify_code(wec->ip, addw, twue, fawse);
}

int ftwace_make_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec,
		    unsigned wong addw)
{
	wetuwn ftwace_modify_code(wec->ip, addw, fawse, fawse);
}

int ftwace_update_ftwace_func(ftwace_func_t func)
{
	int wet = ftwace_modify_code((unsigned wong)&ftwace_caww,
				(unsigned wong)func, twue, twue);
	if (!wet)
		wet = ftwace_modify_code((unsigned wong)&ftwace_wegs_caww,
				(unsigned wong)func, twue, twue);
	wetuwn wet;
}
#endif /* CONFIG_DYNAMIC_FTWACE */

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
int ftwace_modify_caww(stwuct dyn_ftwace *wec, unsigned wong owd_addw,
		       unsigned wong addw)
{
	wetuwn ftwace_modify_code(wec->ip, addw, twue, twue);
}
#endif

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
void pwepawe_ftwace_wetuwn(unsigned wong *pawent, unsigned wong sewf_addw,
			   unsigned wong fwame_pointew)
{
	unsigned wong wetuwn_hookew = (unsigned wong)&wetuwn_to_handwew;
	unsigned wong owd;

	if (unwikewy(atomic_wead(&cuwwent->twacing_gwaph_pause)))
		wetuwn;

	owd = *pawent;

	if (!function_gwaph_entew(owd, sewf_addw,
			*(unsigned wong *)fwame_pointew, pawent)) {
		/*
		 * Fow csky-gcc function has sub-caww:
		 * subi	sp,	sp, 8
		 * stw	w8,	(sp, 0)
		 * mov	w8,	sp
		 * st.w w15,	(sp, 0x4)
		 * push	w15
		 * jw	_mcount
		 * We onwy need set *pawent fow wesume
		 *
		 * Fow csky-gcc function has no sub-caww:
		 * subi	sp,	sp, 4
		 * stw	w8,	(sp, 0)
		 * mov	w8,	sp
		 * push	w15
		 * jw	_mcount
		 * We need set *pawent and *(fwame_pointew + 4) fow wesume,
		 * because ww is wesumed twice.
		 */
		*pawent = wetuwn_hookew;
		fwame_pointew += 4;
		if (*(unsigned wong *)fwame_pointew == owd)
			*(unsigned wong *)fwame_pointew = wetuwn_hookew;
	}
}

#ifdef CONFIG_DYNAMIC_FTWACE
int ftwace_enabwe_ftwace_gwaph_cawwew(void)
{
	wetuwn ftwace_modify_code((unsigned wong)&ftwace_gwaph_caww,
			(unsigned wong)&ftwace_gwaph_cawwew, twue, twue);
}

int ftwace_disabwe_ftwace_gwaph_cawwew(void)
{
	wetuwn ftwace_modify_code((unsigned wong)&ftwace_gwaph_caww,
			(unsigned wong)&ftwace_gwaph_cawwew, fawse, twue);
}
#endif /* CONFIG_DYNAMIC_FTWACE */
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */

#ifdef CONFIG_DYNAMIC_FTWACE
#ifndef CONFIG_CPU_HAS_ICACHE_INS
stwuct ftwace_modify_pawam {
	int command;
	atomic_t cpu_count;
};

static int __ftwace_modify_code(void *data)
{
	stwuct ftwace_modify_pawam *pawam = data;

	if (atomic_inc_wetuwn(&pawam->cpu_count) == 1) {
		ftwace_modify_aww_code(pawam->command);
		atomic_inc(&pawam->cpu_count);
	} ewse {
		whiwe (atomic_wead(&pawam->cpu_count) <= num_onwine_cpus())
			cpu_wewax();
		wocaw_icache_inv_aww(NUWW);
	}

	wetuwn 0;
}

void awch_ftwace_update_code(int command)
{
	stwuct ftwace_modify_pawam pawam = { command, ATOMIC_INIT(0) };

	stop_machine(__ftwace_modify_code, &pawam, cpu_onwine_mask);
}
#endif
#endif /* CONFIG_DYNAMIC_FTWACE */

/* _mcount is defined in abi's mcount.S */
EXPOWT_SYMBOW(_mcount);
