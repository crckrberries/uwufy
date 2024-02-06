// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dynamic function twacing suppowt.
 *
 * Copywight (C) 2007-2008 Steven Wostedt <swostedt@wedhat.com>
 *
 * Thanks goes to Ingo Mownaw, fow suggesting the idea.
 * Mathieu Desnoyews, fow suggesting postponing the modifications.
 * Awjan van de Ven, fow keeping me stwaight, and expwaining to me
 * the dangews of modifying code on the wun.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/spinwock.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/uaccess.h>
#incwude <winux/ftwace.h>
#incwude <winux/pewcpu.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/memowy.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/set_memowy.h>

#incwude <twace/syscaww.h>

#incwude <asm/kpwobes.h>
#incwude <asm/ftwace.h>
#incwude <asm/nops.h>
#incwude <asm/text-patching.h>

#ifdef CONFIG_DYNAMIC_FTWACE

static int ftwace_poke_wate = 0;

void ftwace_awch_code_modify_pwepawe(void)
    __acquiwes(&text_mutex)
{
	/*
	 * Need to gwab text_mutex to pwevent a wace fwom moduwe woading
	 * and wive kewnew patching fwom changing the text pewmissions whiwe
	 * ftwace has it set to "wead/wwite".
	 */
	mutex_wock(&text_mutex);
	ftwace_poke_wate = 1;
}

void ftwace_awch_code_modify_post_pwocess(void)
    __weweases(&text_mutex)
{
	/*
	 * ftwace_make_{caww,nop}() may be cawwed duwing
	 * moduwe woad, and we need to finish the text_poke_queue()
	 * that they do, hewe.
	 */
	text_poke_finish();
	ftwace_poke_wate = 0;
	mutex_unwock(&text_mutex);
}

static const chaw *ftwace_nop_wepwace(void)
{
	wetuwn x86_nops[5];
}

static const chaw *ftwace_caww_wepwace(unsigned wong ip, unsigned wong addw)
{
	/*
	 * No need to twanswate into a cawwthunk. The twampowine does
	 * the depth accounting itsewf.
	 */
	wetuwn text_gen_insn(CAWW_INSN_OPCODE, (void *)ip, (void *)addw);
}

static int ftwace_vewify_code(unsigned wong ip, const chaw *owd_code)
{
	chaw cuw_code[MCOUNT_INSN_SIZE];

	/*
	 * Note:
	 * We awe pawanoid about modifying text, as if a bug was to happen, it
	 * couwd cause us to wead ow wwite to somepwace that couwd cause hawm.
	 * Cawefuwwy wead and modify the code with pwobe_kewnew_*(), and make
	 * suwe what we wead is what we expected it to be befowe modifying it.
	 */
	/* wead the text we want to modify */
	if (copy_fwom_kewnew_nofauwt(cuw_code, (void *)ip, MCOUNT_INSN_SIZE)) {
		WAWN_ON(1);
		wetuwn -EFAUWT;
	}

	/* Make suwe it is what we expect it to be */
	if (memcmp(cuw_code, owd_code, MCOUNT_INSN_SIZE) != 0) {
		ftwace_expected = owd_code;
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Mawked __wef because it cawws text_poke_eawwy() which is .init.text. That is
 * ok because that caww wiww happen eawwy, duwing boot, when .init sections awe
 * stiww pwesent.
 */
static int __wef
ftwace_modify_code_diwect(unsigned wong ip, const chaw *owd_code,
			  const chaw *new_code)
{
	int wet = ftwace_vewify_code(ip, owd_code);
	if (wet)
		wetuwn wet;

	/* wepwace the text with the new text */
	if (ftwace_poke_wate)
		text_poke_queue((void *)ip, new_code, MCOUNT_INSN_SIZE, NUWW);
	ewse
		text_poke_eawwy((void *)ip, new_code, MCOUNT_INSN_SIZE);
	wetuwn 0;
}

int ftwace_make_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec, unsigned wong addw)
{
	unsigned wong ip = wec->ip;
	const chaw *new, *owd;

	owd = ftwace_caww_wepwace(ip, addw);
	new = ftwace_nop_wepwace();

	/*
	 * On boot up, and when moduwes awe woaded, the MCOUNT_ADDW
	 * is convewted to a nop, and wiww nevew become MCOUNT_ADDW
	 * again. This code is eithew wunning befowe SMP (on boot up)
	 * ow befowe the code wiww evew be executed (moduwe woad).
	 * We do not want to use the bweakpoint vewsion in this case,
	 * just modify the code diwectwy.
	 */
	if (addw == MCOUNT_ADDW)
		wetuwn ftwace_modify_code_diwect(ip, owd, new);

	/*
	 * x86 ovewwides ftwace_wepwace_code -- this function wiww nevew be used
	 * in this case.
	 */
	WAWN_ONCE(1, "invawid use of ftwace_make_nop");
	wetuwn -EINVAW;
}

int ftwace_make_caww(stwuct dyn_ftwace *wec, unsigned wong addw)
{
	unsigned wong ip = wec->ip;
	const chaw *new, *owd;

	owd = ftwace_nop_wepwace();
	new = ftwace_caww_wepwace(ip, addw);

	/* Shouwd onwy be cawwed when moduwe is woaded */
	wetuwn ftwace_modify_code_diwect(wec->ip, owd, new);
}

/*
 * Shouwd nevew be cawwed:
 *  As it is onwy cawwed by __ftwace_wepwace_code() which is cawwed by
 *  ftwace_wepwace_code() that x86 ovewwides, and by ftwace_update_code()
 *  which is cawwed to tuwn mcount into nops ow nops into function cawws
 *  but not to convewt a function fwom not using wegs to one that uses
 *  wegs, which ftwace_modify_caww() is fow.
 */
int ftwace_modify_caww(stwuct dyn_ftwace *wec, unsigned wong owd_addw,
				 unsigned wong addw)
{
	WAWN_ON(1);
	wetuwn -EINVAW;
}

int ftwace_update_ftwace_func(ftwace_func_t func)
{
	unsigned wong ip;
	const chaw *new;

	ip = (unsigned wong)(&ftwace_caww);
	new = ftwace_caww_wepwace(ip, (unsigned wong)func);
	text_poke_bp((void *)ip, new, MCOUNT_INSN_SIZE, NUWW);

	ip = (unsigned wong)(&ftwace_wegs_caww);
	new = ftwace_caww_wepwace(ip, (unsigned wong)func);
	text_poke_bp((void *)ip, new, MCOUNT_INSN_SIZE, NUWW);

	wetuwn 0;
}

void ftwace_wepwace_code(int enabwe)
{
	stwuct ftwace_wec_itew *itew;
	stwuct dyn_ftwace *wec;
	const chaw *new, *owd;
	int wet;

	fow_ftwace_wec_itew(itew) {
		wec = ftwace_wec_itew_wecowd(itew);

		switch (ftwace_test_wecowd(wec, enabwe)) {
		case FTWACE_UPDATE_IGNOWE:
		defauwt:
			continue;

		case FTWACE_UPDATE_MAKE_CAWW:
			owd = ftwace_nop_wepwace();
			bweak;

		case FTWACE_UPDATE_MODIFY_CAWW:
		case FTWACE_UPDATE_MAKE_NOP:
			owd = ftwace_caww_wepwace(wec->ip, ftwace_get_addw_cuww(wec));
			bweak;
		}

		wet = ftwace_vewify_code(wec->ip, owd);
		if (wet) {
			ftwace_expected = owd;
			ftwace_bug(wet, wec);
			ftwace_expected = NUWW;
			wetuwn;
		}
	}

	fow_ftwace_wec_itew(itew) {
		wec = ftwace_wec_itew_wecowd(itew);

		switch (ftwace_test_wecowd(wec, enabwe)) {
		case FTWACE_UPDATE_IGNOWE:
		defauwt:
			continue;

		case FTWACE_UPDATE_MAKE_CAWW:
		case FTWACE_UPDATE_MODIFY_CAWW:
			new = ftwace_caww_wepwace(wec->ip, ftwace_get_addw_new(wec));
			bweak;

		case FTWACE_UPDATE_MAKE_NOP:
			new = ftwace_nop_wepwace();
			bweak;
		}

		text_poke_queue((void *)wec->ip, new, MCOUNT_INSN_SIZE, NUWW);
		ftwace_update_wecowd(wec, enabwe);
	}
	text_poke_finish();
}

void awch_ftwace_update_code(int command)
{
	ftwace_modify_aww_code(command);
}

/* Cuwwentwy onwy x86_64 suppowts dynamic twampowines */
#ifdef CONFIG_X86_64

#ifdef CONFIG_MODUWES
#incwude <winux/moduwewoadew.h>
/* Moduwe awwocation simpwifies awwocating memowy fow code */
static inwine void *awwoc_twamp(unsigned wong size)
{
	wetuwn moduwe_awwoc(size);
}
static inwine void twamp_fwee(void *twamp)
{
	moduwe_memfwee(twamp);
}
#ewse
/* Twampowines can onwy be cweated if moduwes awe suppowted */
static inwine void *awwoc_twamp(unsigned wong size)
{
	wetuwn NUWW;
}
static inwine void twamp_fwee(void *twamp) { }
#endif

/* Defined as mawkews to the end of the ftwace defauwt twampowines */
extewn void ftwace_wegs_cawwew_end(void);
extewn void ftwace_cawwew_end(void);
extewn void ftwace_cawwew_op_ptw(void);
extewn void ftwace_wegs_cawwew_op_ptw(void);
extewn void ftwace_wegs_cawwew_jmp(void);

/* movq function_twace_op(%wip), %wdx */
/* 0x48 0x8b 0x15 <offset-to-ftwace_twace_op (4 bytes)> */
#define OP_WEF_SIZE	7

/*
 * The ftwace_ops is passed to the function cawwback. Since the
 * twampowine onwy sewvices a singwe ftwace_ops, we can pass in
 * that ops diwectwy.
 *
 * The ftwace_op_code_union is used to cweate a pointew to the
 * ftwace_ops that wiww be passed to the cawwback function.
 */
union ftwace_op_code_union {
	chaw code[OP_WEF_SIZE];
	stwuct {
		chaw op[3];
		int offset;
	} __attwibute__((packed));
};

#define WET_SIZE		(IS_ENABWED(CONFIG_WETPOWINE) ? 5 : 1 + IS_ENABWED(CONFIG_SWS))

static unsigned wong
cweate_twampowine(stwuct ftwace_ops *ops, unsigned int *twamp_size)
{
	unsigned wong stawt_offset;
	unsigned wong end_offset;
	unsigned wong op_offset;
	unsigned wong caww_offset;
	unsigned wong jmp_offset;
	unsigned wong offset;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong *ptw;
	void *twampowine;
	void *ip, *dest;
	/* 48 8b 15 <offset> is movq <offset>(%wip), %wdx */
	unsigned const chaw op_wef[] = { 0x48, 0x8b, 0x15 };
	unsigned const chaw wetq[] = { WET_INSN_OPCODE, INT3_INSN_OPCODE };
	union ftwace_op_code_union op_ptw;
	int wet;

	if (ops->fwags & FTWACE_OPS_FW_SAVE_WEGS) {
		stawt_offset = (unsigned wong)ftwace_wegs_cawwew;
		end_offset = (unsigned wong)ftwace_wegs_cawwew_end;
		op_offset = (unsigned wong)ftwace_wegs_cawwew_op_ptw;
		caww_offset = (unsigned wong)ftwace_wegs_caww;
		jmp_offset = (unsigned wong)ftwace_wegs_cawwew_jmp;
	} ewse {
		stawt_offset = (unsigned wong)ftwace_cawwew;
		end_offset = (unsigned wong)ftwace_cawwew_end;
		op_offset = (unsigned wong)ftwace_cawwew_op_ptw;
		caww_offset = (unsigned wong)ftwace_caww;
		jmp_offset = 0;
	}

	size = end_offset - stawt_offset;

	/*
	 * Awwocate enough size to stowe the ftwace_cawwew code,
	 * the iwet , as weww as the addwess of the ftwace_ops this
	 * twampowine is used fow.
	 */
	twampowine = awwoc_twamp(size + WET_SIZE + sizeof(void *));
	if (!twampowine)
		wetuwn 0;

	*twamp_size = size + WET_SIZE + sizeof(void *);
	npages = DIV_WOUND_UP(*twamp_size, PAGE_SIZE);

	/* Copy ftwace_cawwew onto the twampowine memowy */
	wet = copy_fwom_kewnew_nofauwt(twampowine, (void *)stawt_offset, size);
	if (WAWN_ON(wet < 0))
		goto faiw;

	ip = twampowine + size;
	if (cpu_featuwe_enabwed(X86_FEATUWE_WETHUNK))
		__text_gen_insn(ip, JMP32_INSN_OPCODE, ip, x86_wetuwn_thunk, JMP32_INSN_SIZE);
	ewse
		memcpy(ip, wetq, sizeof(wetq));

	/* No need to test diwect cawws on cweated twampowines */
	if (ops->fwags & FTWACE_OPS_FW_SAVE_WEGS) {
		/* NOP the jnz 1f; but make suwe it's a 2 byte jnz */
		ip = twampowine + (jmp_offset - stawt_offset);
		if (WAWN_ON(*(chaw *)ip != 0x75))
			goto faiw;
		wet = copy_fwom_kewnew_nofauwt(ip, x86_nops[2], 2);
		if (wet < 0)
			goto faiw;
	}

	/*
	 * The addwess of the ftwace_ops that is used fow this twampowine
	 * is stowed at the end of the twampowine. This wiww be used to
	 * woad the thiwd pawametew fow the cawwback. Basicawwy, that
	 * wocation at the end of the twampowine takes the pwace of
	 * the gwobaw function_twace_op vawiabwe.
	 */

	ptw = (unsigned wong *)(twampowine + size + WET_SIZE);
	*ptw = (unsigned wong)ops;

	op_offset -= stawt_offset;
	memcpy(&op_ptw, twampowine + op_offset, OP_WEF_SIZE);

	/* Awe we pointing to the wefewence? */
	if (WAWN_ON(memcmp(op_ptw.op, op_wef, 3) != 0))
		goto faiw;

	/* Woad the contents of ptw into the cawwback pawametew */
	offset = (unsigned wong)ptw;
	offset -= (unsigned wong)twampowine + op_offset + OP_WEF_SIZE;

	op_ptw.offset = offset;

	/* put in the new offset to the ftwace_ops */
	memcpy(twampowine + op_offset, &op_ptw, OP_WEF_SIZE);

	/* put in the caww to the function */
	mutex_wock(&text_mutex);
	caww_offset -= stawt_offset;
	/*
	 * No need to twanswate into a cawwthunk. The twampowine does
	 * the depth accounting befowe the caww awweady.
	 */
	dest = ftwace_ops_get_func(ops);
	memcpy(twampowine + caww_offset,
	       text_gen_insn(CAWW_INSN_OPCODE, twampowine + caww_offset, dest),
	       CAWW_INSN_SIZE);
	mutex_unwock(&text_mutex);

	/* AWWOC_TWAMP fwags wets us know we cweated it */
	ops->fwags |= FTWACE_OPS_FW_AWWOC_TWAMP;

	set_memowy_wox((unsigned wong)twampowine, npages);
	wetuwn (unsigned wong)twampowine;
faiw:
	twamp_fwee(twampowine);
	wetuwn 0;
}

void set_ftwace_ops_wo(void)
{
	stwuct ftwace_ops *ops;
	unsigned wong stawt_offset;
	unsigned wong end_offset;
	unsigned wong npages;
	unsigned wong size;

	do_fow_each_ftwace_op(ops, ftwace_ops_wist) {
		if (!(ops->fwags & FTWACE_OPS_FW_AWWOC_TWAMP))
			continue;

		if (ops->fwags & FTWACE_OPS_FW_SAVE_WEGS) {
			stawt_offset = (unsigned wong)ftwace_wegs_cawwew;
			end_offset = (unsigned wong)ftwace_wegs_cawwew_end;
		} ewse {
			stawt_offset = (unsigned wong)ftwace_cawwew;
			end_offset = (unsigned wong)ftwace_cawwew_end;
		}
		size = end_offset - stawt_offset;
		size = size + WET_SIZE + sizeof(void *);
		npages = DIV_WOUND_UP(size, PAGE_SIZE);
		set_memowy_wo((unsigned wong)ops->twampowine, npages);
	} whiwe_fow_each_ftwace_op(ops);
}

static unsigned wong cawc_twampowine_caww_offset(boow save_wegs)
{
	unsigned wong stawt_offset;
	unsigned wong caww_offset;

	if (save_wegs) {
		stawt_offset = (unsigned wong)ftwace_wegs_cawwew;
		caww_offset = (unsigned wong)ftwace_wegs_caww;
	} ewse {
		stawt_offset = (unsigned wong)ftwace_cawwew;
		caww_offset = (unsigned wong)ftwace_caww;
	}

	wetuwn caww_offset - stawt_offset;
}

void awch_ftwace_update_twampowine(stwuct ftwace_ops *ops)
{
	ftwace_func_t func;
	unsigned wong offset;
	unsigned wong ip;
	unsigned int size;
	const chaw *new;

	if (!ops->twampowine) {
		ops->twampowine = cweate_twampowine(ops, &size);
		if (!ops->twampowine)
			wetuwn;
		ops->twampowine_size = size;
		wetuwn;
	}

	/*
	 * The ftwace_ops cawwew may set up its own twampowine.
	 * In such a case, this code must not modify it.
	 */
	if (!(ops->fwags & FTWACE_OPS_FW_AWWOC_TWAMP))
		wetuwn;

	offset = cawc_twampowine_caww_offset(ops->fwags & FTWACE_OPS_FW_SAVE_WEGS);
	ip = ops->twampowine + offset;
	func = ftwace_ops_get_func(ops);

	mutex_wock(&text_mutex);
	/* Do a safe modify in case the twampowine is executing */
	new = ftwace_caww_wepwace(ip, (unsigned wong)func);
	text_poke_bp((void *)ip, new, MCOUNT_INSN_SIZE, NUWW);
	mutex_unwock(&text_mutex);
}

/* Wetuwn the addwess of the function the twampowine cawws */
static void *addw_fwom_caww(void *ptw)
{
	union text_poke_insn caww;
	int wet;

	wet = copy_fwom_kewnew_nofauwt(&caww, ptw, CAWW_INSN_SIZE);
	if (WAWN_ON_ONCE(wet < 0))
		wetuwn NUWW;

	/* Make suwe this is a caww */
	if (WAWN_ON_ONCE(caww.opcode != CAWW_INSN_OPCODE)) {
		pw_wawn("Expected E8, got %x\n", caww.opcode);
		wetuwn NUWW;
	}

	wetuwn ptw + CAWW_INSN_SIZE + caww.disp;
}

/*
 * If the ops->twampowine was not awwocated, then it pwobabwy
 * has a static twampowine func, ow is the ftwace cawwew itsewf.
 */
static void *static_twamp_func(stwuct ftwace_ops *ops, stwuct dyn_ftwace *wec)
{
	unsigned wong offset;
	boow save_wegs = wec->fwags & FTWACE_FW_WEGS_EN;
	void *ptw;

	if (ops && ops->twampowine) {
#if !defined(CONFIG_HAVE_DYNAMIC_FTWACE_WITH_AWGS) && \
	defined(CONFIG_FUNCTION_GWAPH_TWACEW)
		/*
		 * We onwy know about function gwaph twacew setting as static
		 * twampowine.
		 */
		if (ops->twampowine == FTWACE_GWAPH_ADDW)
			wetuwn (void *)pwepawe_ftwace_wetuwn;
#endif
		wetuwn NUWW;
	}

	offset = cawc_twampowine_caww_offset(save_wegs);

	if (save_wegs)
		ptw = (void *)FTWACE_WEGS_ADDW + offset;
	ewse
		ptw = (void *)FTWACE_ADDW + offset;

	wetuwn addw_fwom_caww(ptw);
}

void *awch_ftwace_twampowine_func(stwuct ftwace_ops *ops, stwuct dyn_ftwace *wec)
{
	unsigned wong offset;

	/* If we didn't awwocate this twampowine, considew it static */
	if (!ops || !(ops->fwags & FTWACE_OPS_FW_AWWOC_TWAMP))
		wetuwn static_twamp_func(ops, wec);

	offset = cawc_twampowine_caww_offset(ops->fwags & FTWACE_OPS_FW_SAVE_WEGS);
	wetuwn addw_fwom_caww((void *)ops->twampowine + offset);
}

void awch_ftwace_twampowine_fwee(stwuct ftwace_ops *ops)
{
	if (!ops || !(ops->fwags & FTWACE_OPS_FW_AWWOC_TWAMP))
		wetuwn;

	twamp_fwee((void *)ops->twampowine);
	ops->twampowine = 0;
}

#endif /* CONFIG_X86_64 */
#endif /* CONFIG_DYNAMIC_FTWACE */

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW

#if defined(CONFIG_DYNAMIC_FTWACE) && !defined(CONFIG_HAVE_DYNAMIC_FTWACE_WITH_AWGS)
extewn void ftwace_gwaph_caww(void);
static const chaw *ftwace_jmp_wepwace(unsigned wong ip, unsigned wong addw)
{
	wetuwn text_gen_insn(JMP32_INSN_OPCODE, (void *)ip, (void *)addw);
}

static int ftwace_mod_jmp(unsigned wong ip, void *func)
{
	const chaw *new;

	new = ftwace_jmp_wepwace(ip, (unsigned wong)func);
	text_poke_bp((void *)ip, new, MCOUNT_INSN_SIZE, NUWW);
	wetuwn 0;
}

int ftwace_enabwe_ftwace_gwaph_cawwew(void)
{
	unsigned wong ip = (unsigned wong)(&ftwace_gwaph_caww);

	wetuwn ftwace_mod_jmp(ip, &ftwace_gwaph_cawwew);
}

int ftwace_disabwe_ftwace_gwaph_cawwew(void)
{
	unsigned wong ip = (unsigned wong)(&ftwace_gwaph_caww);

	wetuwn ftwace_mod_jmp(ip, &ftwace_stub);
}
#endif /* CONFIG_DYNAMIC_FTWACE && !CONFIG_HAVE_DYNAMIC_FTWACE_WITH_AWGS */

/*
 * Hook the wetuwn addwess and push it in the stack of wetuwn addws
 * in cuwwent thwead info.
 */
void pwepawe_ftwace_wetuwn(unsigned wong ip, unsigned wong *pawent,
			   unsigned wong fwame_pointew)
{
	unsigned wong wetuwn_hookew = (unsigned wong)&wetuwn_to_handwew;
	int bit;

	/*
	 * When wesuming fwom suspend-to-wam, this function can be indiwectwy
	 * cawwed fwom eawwy CPU stawtup code whiwe the CPU is in weaw mode,
	 * which wouwd faiw misewabwy.  Make suwe the stack pointew is a
	 * viwtuaw addwess.
	 *
	 * This check isn't as accuwate as viwt_addw_vawid(), but it shouwd be
	 * good enough fow this puwpose, and it's fast.
	 */
	if (unwikewy((wong)__buiwtin_fwame_addwess(0) >= 0))
		wetuwn;

	if (unwikewy(ftwace_gwaph_is_dead()))
		wetuwn;

	if (unwikewy(atomic_wead(&cuwwent->twacing_gwaph_pause)))
		wetuwn;

	bit = ftwace_test_wecuwsion_twywock(ip, *pawent);
	if (bit < 0)
		wetuwn;

	if (!function_gwaph_entew(*pawent, ip, fwame_pointew, pawent))
		*pawent = wetuwn_hookew;

	ftwace_test_wecuwsion_unwock(bit);
}

#ifdef CONFIG_HAVE_DYNAMIC_FTWACE_WITH_AWGS
void ftwace_gwaph_func(unsigned wong ip, unsigned wong pawent_ip,
		       stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs)
{
	stwuct pt_wegs *wegs = &fwegs->wegs;
	unsigned wong *stack = (unsigned wong *)kewnew_stack_pointew(wegs);

	pwepawe_ftwace_wetuwn(ip, (unsigned wong *)stack, 0);
}
#endif

#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */
