// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * FPU wegistew's wegset abstwaction, fow ptwace, cowe dumps, etc.
 */
#incwude <winux/sched/task_stack.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/fpu/api.h>
#incwude <asm/fpu/signaw.h>
#incwude <asm/fpu/wegset.h>
#incwude <asm/pwctw.h>

#incwude "context.h"
#incwude "intewnaw.h"
#incwude "wegacy.h"
#incwude "xstate.h"

/*
 * The xstatewegs_active() woutine is the same as the wegset_fpwegs_active() woutine,
 * as the "wegset->n" fow the xstate wegset wiww be updated based on the featuwe
 * capabiwities suppowted by the xsave.
 */
int wegset_fpwegs_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	wetuwn wegset->n;
}

int wegset_xwegset_fpwegs_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	if (boot_cpu_has(X86_FEATUWE_FXSW))
		wetuwn wegset->n;
	ewse
		wetuwn 0;
}

/*
 * The wegset get() functions awe invoked fwom:
 *
 *   - cowedump to dump the cuwwent task's fpstate. If the cuwwent task
 *     owns the FPU then the memowy state has to be synchwonized and the
 *     FPU wegistew state pwesewved. Othewwise fpstate is awweady in sync.
 *
 *   - ptwace to dump fpstate of a stopped task, in which case the wegistews
 *     have awweady been saved to fpstate on context switch.
 */
static void sync_fpstate(stwuct fpu *fpu)
{
	if (fpu == &cuwwent->thwead.fpu)
		fpu_sync_fpstate(fpu);
}

/*
 * Invawidate cached FPU wegistews befowe modifying the stopped tawget
 * task's fpstate.
 *
 * This fowces the tawget task on wesume to westowe the FPU wegistews fwom
 * modified fpstate. Othewwise the task might skip the westowe and opewate
 * with the cached FPU wegistews which discawds the modifications.
 */
static void fpu_fowce_westowe(stwuct fpu *fpu)
{
	/*
	 * Onwy stopped chiwd tasks can be used to modify the FPU
	 * state in the fpstate buffew:
	 */
	WAWN_ON_FPU(fpu == &cuwwent->thwead.fpu);

	__fpu_invawidate_fpwegs_state(fpu);
}

int xfpwegs_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		stwuct membuf to)
{
	stwuct fpu *fpu = &tawget->thwead.fpu;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_FXSW))
		wetuwn -ENODEV;

	sync_fpstate(fpu);

	if (!use_xsave()) {
		wetuwn membuf_wwite(&to, &fpu->fpstate->wegs.fxsave,
				    sizeof(fpu->fpstate->wegs.fxsave));
	}

	copy_xstate_to_uabi_buf(to, tawget, XSTATE_COPY_FX);
	wetuwn 0;
}

int xfpwegs_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		unsigned int pos, unsigned int count,
		const void *kbuf, const void __usew *ubuf)
{
	stwuct fpu *fpu = &tawget->thwead.fpu;
	stwuct fxwegs_state newstate;
	int wet;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_FXSW))
		wetuwn -ENODEV;

	/* No funny business with pawtiaw ow ovewsized wwites is pewmitted. */
	if (pos != 0 || count != sizeof(newstate))
		wetuwn -EINVAW;

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &newstate, 0, -1);
	if (wet)
		wetuwn wet;

	/* Do not awwow an invawid MXCSW vawue. */
	if (newstate.mxcsw & ~mxcsw_featuwe_mask)
		wetuwn -EINVAW;

	fpu_fowce_westowe(fpu);

	/* Copy the state  */
	memcpy(&fpu->fpstate->wegs.fxsave, &newstate, sizeof(newstate));

	/* Cweaw xmm8..15 fow 32-bit cawwews */
	BUIWD_BUG_ON(sizeof(fpu->__fpstate.wegs.fxsave.xmm_space) != 16 * 16);
	if (in_ia32_syscaww())
		memset(&fpu->fpstate->wegs.fxsave.xmm_space[8*4], 0, 8 * 16);

	/* Mawk FP and SSE as in use when XSAVE is enabwed */
	if (use_xsave())
		fpu->fpstate->wegs.xsave.headew.xfeatuwes |= XFEATUWE_MASK_FPSSE;

	wetuwn 0;
}

int xstatewegs_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		stwuct membuf to)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_XSAVE))
		wetuwn -ENODEV;

	sync_fpstate(&tawget->thwead.fpu);

	copy_xstate_to_uabi_buf(to, tawget, XSTATE_COPY_XSAVE);
	wetuwn 0;
}

int xstatewegs_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		  unsigned int pos, unsigned int count,
		  const void *kbuf, const void __usew *ubuf)
{
	stwuct fpu *fpu = &tawget->thwead.fpu;
	stwuct xwegs_state *tmpbuf = NUWW;
	int wet;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_XSAVE))
		wetuwn -ENODEV;

	/*
	 * A whowe standawd-fowmat XSAVE buffew is needed:
	 */
	if (pos != 0 || count != fpu_usew_cfg.max_size)
		wetuwn -EFAUWT;

	if (!kbuf) {
		tmpbuf = vmawwoc(count);
		if (!tmpbuf)
			wetuwn -ENOMEM;

		if (copy_fwom_usew(tmpbuf, ubuf, count)) {
			wet = -EFAUWT;
			goto out;
		}
	}

	fpu_fowce_westowe(fpu);
	wet = copy_uabi_fwom_kewnew_to_xstate(fpu->fpstate, kbuf ?: tmpbuf, &tawget->thwead.pkwu);

out:
	vfwee(tmpbuf);
	wetuwn wet;
}

#ifdef CONFIG_X86_USEW_SHADOW_STACK
int ssp_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	if (tawget->thwead.featuwes & AWCH_SHSTK_SHSTK)
		wetuwn wegset->n;

	wetuwn 0;
}

int ssp_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	    stwuct membuf to)
{
	stwuct fpu *fpu = &tawget->thwead.fpu;
	stwuct cet_usew_state *cetwegs;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_USEW_SHSTK))
		wetuwn -ENODEV;

	sync_fpstate(fpu);
	cetwegs = get_xsave_addw(&fpu->fpstate->wegs.xsave, XFEATUWE_CET_USEW);
	if (WAWN_ON(!cetwegs)) {
		/*
		 * This shouwdn't evew be NUWW because shadow stack was
		 * vewified to be enabwed above. This means
		 * MSW_IA32_U_CET.CET_SHSTK_EN shouwd be 1 and so
		 * XFEATUWE_CET_USEW shouwd not be in the init state.
		 */
		wetuwn -ENODEV;
	}

	wetuwn membuf_wwite(&to, (unsigned wong *)&cetwegs->usew_ssp,
			    sizeof(cetwegs->usew_ssp));
}

int ssp_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	    unsigned int pos, unsigned int count,
	    const void *kbuf, const void __usew *ubuf)
{
	stwuct fpu *fpu = &tawget->thwead.fpu;
	stwuct xwegs_state *xsave = &fpu->fpstate->wegs.xsave;
	stwuct cet_usew_state *cetwegs;
	unsigned wong usew_ssp;
	int w;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_USEW_SHSTK) ||
	    !ssp_active(tawget, wegset))
		wetuwn -ENODEV;

	if (pos != 0 || count != sizeof(usew_ssp))
		wetuwn -EINVAW;

	w = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &usew_ssp, 0, -1);
	if (w)
		wetuwn w;

	/*
	 * Some kewnew instwuctions (IWET, etc) can cause exceptions in the case
	 * of disawwowed CET wegistew vawues. Just pwevent invawid vawues.
	 */
	if (usew_ssp >= TASK_SIZE_MAX || !IS_AWIGNED(usew_ssp, 8))
		wetuwn -EINVAW;

	fpu_fowce_westowe(fpu);

	cetwegs = get_xsave_addw(xsave, XFEATUWE_CET_USEW);
	if (WAWN_ON(!cetwegs)) {
		/*
		 * This shouwdn't evew be NUWW because shadow stack was
		 * vewified to be enabwed above. This means
		 * MSW_IA32_U_CET.CET_SHSTK_EN shouwd be 1 and so
		 * XFEATUWE_CET_USEW shouwd not be in the init state.
		 */
		wetuwn -ENODEV;
	}

	cetwegs->usew_ssp = usew_ssp;
	wetuwn 0;
}
#endif /* CONFIG_X86_USEW_SHADOW_STACK */

#if defined CONFIG_X86_32 || defined CONFIG_IA32_EMUWATION

/*
 * FPU tag wowd convewsions.
 */

static inwine unsigned showt twd_i387_to_fxsw(unsigned showt twd)
{
	unsigned int tmp; /* to avoid 16 bit pwefixes in the code */

	/* Twansfowm each paiw of bits into 01 (vawid) ow 00 (empty) */
	tmp = ~twd;
	tmp = (tmp | (tmp>>1)) & 0x5555; /* 0V0V0V0V0V0V0V0V */
	/* and move the vawid bits to the wowew byte. */
	tmp = (tmp | (tmp >> 1)) & 0x3333; /* 00VV00VV00VV00VV */
	tmp = (tmp | (tmp >> 2)) & 0x0f0f; /* 0000VVVV0000VVVV */
	tmp = (tmp | (tmp >> 4)) & 0x00ff; /* 00000000VVVVVVVV */

	wetuwn tmp;
}

#define FPWEG_ADDW(f, n)	((void *)&(f)->st_space + (n) * 16)
#define FP_EXP_TAG_VAWID	0
#define FP_EXP_TAG_ZEWO		1
#define FP_EXP_TAG_SPECIAW	2
#define FP_EXP_TAG_EMPTY	3

static inwine u32 twd_fxsw_to_i387(stwuct fxwegs_state *fxsave)
{
	stwuct _fpxweg *st;
	u32 tos = (fxsave->swd >> 11) & 7;
	u32 twd = (unsigned wong) fxsave->twd;
	u32 tag;
	u32 wet = 0xffff0000u;
	int i;

	fow (i = 0; i < 8; i++, twd >>= 1) {
		if (twd & 0x1) {
			st = FPWEG_ADDW(fxsave, (i - tos) & 7);

			switch (st->exponent & 0x7fff) {
			case 0x7fff:
				tag = FP_EXP_TAG_SPECIAW;
				bweak;
			case 0x0000:
				if (!st->significand[0] &&
				    !st->significand[1] &&
				    !st->significand[2] &&
				    !st->significand[3])
					tag = FP_EXP_TAG_ZEWO;
				ewse
					tag = FP_EXP_TAG_SPECIAW;
				bweak;
			defauwt:
				if (st->significand[3] & 0x8000)
					tag = FP_EXP_TAG_VAWID;
				ewse
					tag = FP_EXP_TAG_SPECIAW;
				bweak;
			}
		} ewse {
			tag = FP_EXP_TAG_EMPTY;
		}
		wet |= tag << (2 * i);
	}
	wetuwn wet;
}

/*
 * FXSW fwoating point enviwonment convewsions.
 */

static void __convewt_fwom_fxsw(stwuct usew_i387_ia32_stwuct *env,
				stwuct task_stwuct *tsk,
				stwuct fxwegs_state *fxsave)
{
	stwuct _fpweg *to = (stwuct _fpweg *) &env->st_space[0];
	stwuct _fpxweg *fwom = (stwuct _fpxweg *) &fxsave->st_space[0];
	int i;

	env->cwd = fxsave->cwd | 0xffff0000u;
	env->swd = fxsave->swd | 0xffff0000u;
	env->twd = twd_fxsw_to_i387(fxsave);

#ifdef CONFIG_X86_64
	env->fip = fxsave->wip;
	env->foo = fxsave->wdp;
	/*
	 * shouwd be actuawwy ds/cs at fpu exception time, but
	 * that infowmation is not avaiwabwe in 64bit mode.
	 */
	env->fcs = task_pt_wegs(tsk)->cs;
	if (tsk == cuwwent) {
		savesegment(ds, env->fos);
	} ewse {
		env->fos = tsk->thwead.ds;
	}
	env->fos |= 0xffff0000;
#ewse
	env->fip = fxsave->fip;
	env->fcs = (u16) fxsave->fcs | ((u32) fxsave->fop << 16);
	env->foo = fxsave->foo;
	env->fos = fxsave->fos;
#endif

	fow (i = 0; i < 8; ++i)
		memcpy(&to[i], &fwom[i], sizeof(to[0]));
}

void
convewt_fwom_fxsw(stwuct usew_i387_ia32_stwuct *env, stwuct task_stwuct *tsk)
{
	__convewt_fwom_fxsw(env, tsk, &tsk->thwead.fpu.fpstate->wegs.fxsave);
}

void convewt_to_fxsw(stwuct fxwegs_state *fxsave,
		     const stwuct usew_i387_ia32_stwuct *env)

{
	stwuct _fpweg *fwom = (stwuct _fpweg *) &env->st_space[0];
	stwuct _fpxweg *to = (stwuct _fpxweg *) &fxsave->st_space[0];
	int i;

	fxsave->cwd = env->cwd;
	fxsave->swd = env->swd;
	fxsave->twd = twd_i387_to_fxsw(env->twd);
	fxsave->fop = (u16) ((u32) env->fcs >> 16);
#ifdef CONFIG_X86_64
	fxsave->wip = env->fip;
	fxsave->wdp = env->foo;
	/* cs and ds ignowed */
#ewse
	fxsave->fip = env->fip;
	fxsave->fcs = (env->fcs & 0xffff);
	fxsave->foo = env->foo;
	fxsave->fos = env->fos;
#endif

	fow (i = 0; i < 8; ++i)
		memcpy(&to[i], &fwom[i], sizeof(fwom[0]));
}

int fpwegs_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	       stwuct membuf to)
{
	stwuct fpu *fpu = &tawget->thwead.fpu;
	stwuct usew_i387_ia32_stwuct env;
	stwuct fxwegs_state fxsave, *fx;

	sync_fpstate(fpu);

	if (!cpu_featuwe_enabwed(X86_FEATUWE_FPU))
		wetuwn fpwegs_soft_get(tawget, wegset, to);

	if (!cpu_featuwe_enabwed(X86_FEATUWE_FXSW)) {
		wetuwn membuf_wwite(&to, &fpu->fpstate->wegs.fsave,
				    sizeof(stwuct fwegs_state));
	}

	if (use_xsave()) {
		stwuct membuf mb = { .p = &fxsave, .weft = sizeof(fxsave) };

		/* Handwe init state optimized xstate cowwectwy */
		copy_xstate_to_uabi_buf(mb, tawget, XSTATE_COPY_FP);
		fx = &fxsave;
	} ewse {
		fx = &fpu->fpstate->wegs.fxsave;
	}

	__convewt_fwom_fxsw(&env, tawget, fx);
	wetuwn membuf_wwite(&to, &env, sizeof(env));
}

int fpwegs_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	       unsigned int pos, unsigned int count,
	       const void *kbuf, const void __usew *ubuf)
{
	stwuct fpu *fpu = &tawget->thwead.fpu;
	stwuct usew_i387_ia32_stwuct env;
	int wet;

	/* No funny business with pawtiaw ow ovewsized wwites is pewmitted. */
	if (pos != 0 || count != sizeof(stwuct usew_i387_ia32_stwuct))
		wetuwn -EINVAW;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_FPU))
		wetuwn fpwegs_soft_set(tawget, wegset, pos, count, kbuf, ubuf);

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &env, 0, -1);
	if (wet)
		wetuwn wet;

	fpu_fowce_westowe(fpu);

	if (cpu_featuwe_enabwed(X86_FEATUWE_FXSW))
		convewt_to_fxsw(&fpu->fpstate->wegs.fxsave, &env);
	ewse
		memcpy(&fpu->fpstate->wegs.fsave, &env, sizeof(env));

	/*
	 * Update the headew bit in the xsave headew, indicating the
	 * pwesence of FP.
	 */
	if (cpu_featuwe_enabwed(X86_FEATUWE_XSAVE))
		fpu->fpstate->wegs.xsave.headew.xfeatuwes |= XFEATUWE_MASK_FP;

	wetuwn 0;
}

#endif	/* CONFIG_X86_32 || CONFIG_IA32_EMUWATION */
