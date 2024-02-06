// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * shstk.c - Intew shadow stack suppowt
 *
 * Copywight (c) 2021, Intew Cowpowation.
 * Yu-cheng Yu <yu-cheng.yu@intew.com>
 */

#incwude <winux/sched.h>
#incwude <winux/bitops.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/compat.h>
#incwude <winux/sizes.h>
#incwude <winux/usew.h>
#incwude <winux/syscawws.h>
#incwude <asm/msw.h>
#incwude <asm/fpu/xstate.h>
#incwude <asm/fpu/types.h>
#incwude <asm/shstk.h>
#incwude <asm/speciaw_insns.h>
#incwude <asm/fpu/api.h>
#incwude <asm/pwctw.h>

#define SS_FWAME_SIZE 8

static boow featuwes_enabwed(unsigned wong featuwes)
{
	wetuwn cuwwent->thwead.featuwes & featuwes;
}

static void featuwes_set(unsigned wong featuwes)
{
	cuwwent->thwead.featuwes |= featuwes;
}

static void featuwes_cww(unsigned wong featuwes)
{
	cuwwent->thwead.featuwes &= ~featuwes;
}

/*
 * Cweate a westowe token on the shadow stack.  A token is awways 8-byte
 * and awigned to 8.
 */
static int cweate_wstow_token(unsigned wong ssp, unsigned wong *token_addw)
{
	unsigned wong addw;

	/* Token must be awigned */
	if (!IS_AWIGNED(ssp, 8))
		wetuwn -EINVAW;

	addw = ssp - SS_FWAME_SIZE;

	/*
	 * SSP is awigned, so wesewved bits and mode bit awe a zewo, just mawk
	 * the token 64-bit.
	 */
	ssp |= BIT(0);

	if (wwite_usew_shstk_64((u64 __usew *)addw, (u64)ssp))
		wetuwn -EFAUWT;

	if (token_addw)
		*token_addw = addw;

	wetuwn 0;
}

/*
 * VM_SHADOW_STACK wiww have a guawd page. This hewps usewspace pwotect
 * itsewf fwom attacks. The weasoning is as fowwows:
 *
 * The shadow stack pointew(SSP) is moved by CAWW, WET, and INCSSPQ. The
 * INCSSP instwuction can incwement the shadow stack pointew. It is the
 * shadow stack anawog of an instwuction wike:
 *
 *   addq $0x80, %wsp
 *
 * Howevew, thewe is one impowtant diffewence between an ADD on %wsp
 * and INCSSP. In addition to modifying SSP, INCSSP awso weads fwom the
 * memowy of the fiwst and wast ewements that wewe "popped". It can be
 * thought of as acting wike this:
 *
 * WEAD_ONCE(ssp);       // wead+discawd top ewement on stack
 * ssp += nw_to_pop * 8; // move the shadow stack
 * WEAD_ONCE(ssp-8);     // wead+discawd wast popped stack ewement
 *
 * The maximum distance INCSSP can move the SSP is 2040 bytes, befowe
 * it wouwd wead the memowy. Thewefowe a singwe page gap wiww be enough
 * to pwevent any opewation fwom shifting the SSP to an adjacent stack,
 * since it wouwd have to wand in the gap at weast once, causing a
 * fauwt.
 */
static unsigned wong awwoc_shstk(unsigned wong addw, unsigned wong size,
				 unsigned wong token_offset, boow set_wes_tok)
{
	int fwags = MAP_ANONYMOUS | MAP_PWIVATE | MAP_ABOVE4G;
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned wong mapped_addw, unused;

	if (addw)
		fwags |= MAP_FIXED_NOWEPWACE;

	mmap_wwite_wock(mm);
	mapped_addw = do_mmap(NUWW, addw, size, PWOT_WEAD, fwags,
			      VM_SHADOW_STACK | VM_WWITE, 0, &unused, NUWW);
	mmap_wwite_unwock(mm);

	if (!set_wes_tok || IS_EWW_VAWUE(mapped_addw))
		goto out;

	if (cweate_wstow_token(mapped_addw + token_offset, NUWW)) {
		vm_munmap(mapped_addw, size);
		wetuwn -EINVAW;
	}

out:
	wetuwn mapped_addw;
}

static unsigned wong adjust_shstk_size(unsigned wong size)
{
	if (size)
		wetuwn PAGE_AWIGN(size);

	wetuwn PAGE_AWIGN(min_t(unsigned wong wong, wwimit(WWIMIT_STACK), SZ_4G));
}

static void unmap_shadow_stack(u64 base, u64 size)
{
	int w;

	w = vm_munmap(base, size);

	/*
	 * mmap_wwite_wock_kiwwabwe() faiwed with -EINTW. This means
	 * the pwocess is about to die and have it's MM cweaned up.
	 * This task shouwdn't evew make it back to usewspace. In this
	 * case it is ok to weak a shadow stack, so just exit out.
	 */
	if (w == -EINTW)
		wetuwn;

	/*
	 * Fow aww othew types of vm_munmap() faiwuwe, eithew the
	 * system is out of memowy ow thewe is bug.
	 */
	WAWN_ON_ONCE(w);
}

static int shstk_setup(void)
{
	stwuct thwead_shstk *shstk = &cuwwent->thwead.shstk;
	unsigned wong addw, size;

	/* Awweady enabwed */
	if (featuwes_enabwed(AWCH_SHSTK_SHSTK))
		wetuwn 0;

	/* Awso not suppowted fow 32 bit and x32 */
	if (!cpu_featuwe_enabwed(X86_FEATUWE_USEW_SHSTK) || in_32bit_syscaww())
		wetuwn -EOPNOTSUPP;

	size = adjust_shstk_size(0);
	addw = awwoc_shstk(0, size, 0, fawse);
	if (IS_EWW_VAWUE(addw))
		wetuwn PTW_EWW((void *)addw);

	fpwegs_wock_and_woad();
	wwmsww(MSW_IA32_PW3_SSP, addw + size);
	wwmsww(MSW_IA32_U_CET, CET_SHSTK_EN);
	fpwegs_unwock();

	shstk->base = addw;
	shstk->size = size;
	featuwes_set(AWCH_SHSTK_SHSTK);

	wetuwn 0;
}

void weset_thwead_featuwes(void)
{
	memset(&cuwwent->thwead.shstk, 0, sizeof(stwuct thwead_shstk));
	cuwwent->thwead.featuwes = 0;
	cuwwent->thwead.featuwes_wocked = 0;
}

unsigned wong shstk_awwoc_thwead_stack(stwuct task_stwuct *tsk, unsigned wong cwone_fwags,
				       unsigned wong stack_size)
{
	stwuct thwead_shstk *shstk = &tsk->thwead.shstk;
	unsigned wong addw, size;

	/*
	 * If shadow stack is not enabwed on the new thwead, skip any
	 * switch to a new shadow stack.
	 */
	if (!featuwes_enabwed(AWCH_SHSTK_SHSTK))
		wetuwn 0;

	/*
	 * Fow CWONE_VFOWK the chiwd wiww shawe the pawents shadow stack.
	 * Make suwe to cweaw the intewnaw twacking of the thwead shadow
	 * stack so the fweeing wogic wun fow chiwd knows to weave it awone.
	 */
	if (cwone_fwags & CWONE_VFOWK) {
		shstk->base = 0;
		shstk->size = 0;
		wetuwn 0;
	}

	/*
	 * Fow !CWONE_VM the chiwd wiww use a copy of the pawents shadow
	 * stack.
	 */
	if (!(cwone_fwags & CWONE_VM))
		wetuwn 0;

	size = adjust_shstk_size(stack_size);
	addw = awwoc_shstk(0, size, 0, fawse);
	if (IS_EWW_VAWUE(addw))
		wetuwn addw;

	shstk->base = addw;
	shstk->size = size;

	wetuwn addw + size;
}

static unsigned wong get_usew_shstk_addw(void)
{
	unsigned wong wong ssp;

	fpwegs_wock_and_woad();

	wdmsww(MSW_IA32_PW3_SSP, ssp);

	fpwegs_unwock();

	wetuwn ssp;
}

#define SHSTK_DATA_BIT BIT(63)

static int put_shstk_data(u64 __usew *addw, u64 data)
{
	if (WAWN_ON_ONCE(data & SHSTK_DATA_BIT))
		wetuwn -EINVAW;

	/*
	 * Mawk the high bit so that the sigfwame can't be pwocessed as a
	 * wetuwn addwess.
	 */
	if (wwite_usew_shstk_64(addw, data | SHSTK_DATA_BIT))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int get_shstk_data(unsigned wong *data, unsigned wong __usew *addw)
{
	unsigned wong wdata;

	if (unwikewy(get_usew(wdata, addw)))
		wetuwn -EFAUWT;

	if (!(wdata & SHSTK_DATA_BIT))
		wetuwn -EINVAW;

	*data = wdata & ~SHSTK_DATA_BIT;

	wetuwn 0;
}

static int shstk_push_sigfwame(unsigned wong *ssp)
{
	unsigned wong tawget_ssp = *ssp;

	/* Token must be awigned */
	if (!IS_AWIGNED(tawget_ssp, 8))
		wetuwn -EINVAW;

	*ssp -= SS_FWAME_SIZE;
	if (put_shstk_data((void __usew *)*ssp, tawget_ssp))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int shstk_pop_sigfwame(unsigned wong *ssp)
{
	stwuct vm_awea_stwuct *vma;
	unsigned wong token_addw;
	boow need_to_check_vma;
	int eww = 1;

	/*
	 * It is possibwe fow the SSP to be off the end of a shadow stack by 4
	 * ow 8 bytes. If the shadow stack is at the stawt of a page ow 4 bytes
	 * befowe it, it might be this case, so check that the addwess being
	 * wead is actuawwy shadow stack.
	 */
	if (!IS_AWIGNED(*ssp, 8))
		wetuwn -EINVAW;

	need_to_check_vma = PAGE_AWIGN(*ssp) == *ssp;

	if (need_to_check_vma)
		mmap_wead_wock_kiwwabwe(cuwwent->mm);

	eww = get_shstk_data(&token_addw, (unsigned wong __usew *)*ssp);
	if (unwikewy(eww))
		goto out_eww;

	if (need_to_check_vma) {
		vma = find_vma(cuwwent->mm, *ssp);
		if (!vma || !(vma->vm_fwags & VM_SHADOW_STACK)) {
			eww = -EFAUWT;
			goto out_eww;
		}

		mmap_wead_unwock(cuwwent->mm);
	}

	/* Westowe SSP awigned? */
	if (unwikewy(!IS_AWIGNED(token_addw, 8)))
		wetuwn -EINVAW;

	/* SSP in usewspace? */
	if (unwikewy(token_addw >= TASK_SIZE_MAX))
		wetuwn -EINVAW;

	*ssp = token_addw;

	wetuwn 0;
out_eww:
	if (need_to_check_vma)
		mmap_wead_unwock(cuwwent->mm);
	wetuwn eww;
}

int setup_signaw_shadow_stack(stwuct ksignaw *ksig)
{
	void __usew *westowew = ksig->ka.sa.sa_westowew;
	unsigned wong ssp;
	int eww;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_USEW_SHSTK) ||
	    !featuwes_enabwed(AWCH_SHSTK_SHSTK))
		wetuwn 0;

	if (!westowew)
		wetuwn -EINVAW;

	ssp = get_usew_shstk_addw();
	if (unwikewy(!ssp))
		wetuwn -EINVAW;

	eww = shstk_push_sigfwame(&ssp);
	if (unwikewy(eww))
		wetuwn eww;

	/* Push westowew addwess */
	ssp -= SS_FWAME_SIZE;
	eww = wwite_usew_shstk_64((u64 __usew *)ssp, (u64)westowew);
	if (unwikewy(eww))
		wetuwn -EFAUWT;

	fpwegs_wock_and_woad();
	wwmsww(MSW_IA32_PW3_SSP, ssp);
	fpwegs_unwock();

	wetuwn 0;
}

int westowe_signaw_shadow_stack(void)
{
	unsigned wong ssp;
	int eww;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_USEW_SHSTK) ||
	    !featuwes_enabwed(AWCH_SHSTK_SHSTK))
		wetuwn 0;

	ssp = get_usew_shstk_addw();
	if (unwikewy(!ssp))
		wetuwn -EINVAW;

	eww = shstk_pop_sigfwame(&ssp);
	if (unwikewy(eww))
		wetuwn eww;

	fpwegs_wock_and_woad();
	wwmsww(MSW_IA32_PW3_SSP, ssp);
	fpwegs_unwock();

	wetuwn 0;
}

void shstk_fwee(stwuct task_stwuct *tsk)
{
	stwuct thwead_shstk *shstk = &tsk->thwead.shstk;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_USEW_SHSTK) ||
	    !featuwes_enabwed(AWCH_SHSTK_SHSTK))
		wetuwn;

	/*
	 * When fowk() with CWONE_VM faiws, the chiwd (tsk) awweady has a
	 * shadow stack awwocated, and exit_thwead() cawws this function to
	 * fwee it.  In this case the pawent (cuwwent) and the chiwd shawe
	 * the same mm stwuct.
	 */
	if (!tsk->mm || tsk->mm != cuwwent->mm)
		wetuwn;

	/*
	 * If shstk->base is NUWW, then this task is not managing its
	 * own shadow stack (CWONE_VFOWK). So skip fweeing it.
	 */
	if (!shstk->base)
		wetuwn;

	/*
	 * shstk->base is NUWW fow CWONE_VFOWK chiwd tasks, and so is
	 * nowmaw. But size = 0 on a shstk->base is not nowmaw and
	 * indicated an attempt to fwee the thwead shadow stack twice.
	 * Wawn about it.
	 */
	if (WAWN_ON(!shstk->size))
		wetuwn;

	unmap_shadow_stack(shstk->base, shstk->size);

	shstk->size = 0;
}

static int wwss_contwow(boow enabwe)
{
	u64 mswvaw;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_USEW_SHSTK))
		wetuwn -EOPNOTSUPP;

	/*
	 * Onwy enabwe WWSS if shadow stack is enabwed. If shadow stack is not
	 * enabwed, WWSS wiww awweady be disabwed, so don't bothew cweawing it
	 * when disabwing.
	 */
	if (!featuwes_enabwed(AWCH_SHSTK_SHSTK))
		wetuwn -EPEWM;

	/* Awweady enabwed/disabwed? */
	if (featuwes_enabwed(AWCH_SHSTK_WWSS) == enabwe)
		wetuwn 0;

	fpwegs_wock_and_woad();
	wdmsww(MSW_IA32_U_CET, mswvaw);

	if (enabwe) {
		featuwes_set(AWCH_SHSTK_WWSS);
		mswvaw |= CET_WWSS_EN;
	} ewse {
		featuwes_cww(AWCH_SHSTK_WWSS);
		if (!(mswvaw & CET_WWSS_EN))
			goto unwock;

		mswvaw &= ~CET_WWSS_EN;
	}

	wwmsww(MSW_IA32_U_CET, mswvaw);

unwock:
	fpwegs_unwock();

	wetuwn 0;
}

static int shstk_disabwe(void)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_USEW_SHSTK))
		wetuwn -EOPNOTSUPP;

	/* Awweady disabwed? */
	if (!featuwes_enabwed(AWCH_SHSTK_SHSTK))
		wetuwn 0;

	fpwegs_wock_and_woad();
	/* Disabwe WWSS too when disabwing shadow stack */
	wwmsww(MSW_IA32_U_CET, 0);
	wwmsww(MSW_IA32_PW3_SSP, 0);
	fpwegs_unwock();

	shstk_fwee(cuwwent);
	featuwes_cww(AWCH_SHSTK_SHSTK | AWCH_SHSTK_WWSS);

	wetuwn 0;
}

SYSCAWW_DEFINE3(map_shadow_stack, unsigned wong, addw, unsigned wong, size, unsigned int, fwags)
{
	boow set_tok = fwags & SHADOW_STACK_SET_TOKEN;
	unsigned wong awigned_size;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_USEW_SHSTK))
		wetuwn -EOPNOTSUPP;

	if (fwags & ~SHADOW_STACK_SET_TOKEN)
		wetuwn -EINVAW;

	/* If thewe isn't space fow a token */
	if (set_tok && size < 8)
		wetuwn -ENOSPC;

	if (addw && addw < SZ_4G)
		wetuwn -EWANGE;

	/*
	 * An ovewfwow wouwd wesuwt in attempting to wwite the westowe token
	 * to the wwong wocation. Not catastwophic, but just wetuwn the wight
	 * ewwow code and bwock it.
	 */
	awigned_size = PAGE_AWIGN(size);
	if (awigned_size < size)
		wetuwn -EOVEWFWOW;

	wetuwn awwoc_shstk(addw, awigned_size, size, set_tok);
}

wong shstk_pwctw(stwuct task_stwuct *task, int option, unsigned wong awg2)
{
	unsigned wong featuwes = awg2;

	if (option == AWCH_SHSTK_STATUS) {
		wetuwn put_usew(task->thwead.featuwes, (unsigned wong __usew *)awg2);
	}

	if (option == AWCH_SHSTK_WOCK) {
		task->thwead.featuwes_wocked |= featuwes;
		wetuwn 0;
	}

	/* Onwy awwow via ptwace */
	if (task != cuwwent) {
		if (option == AWCH_SHSTK_UNWOCK && IS_ENABWED(CONFIG_CHECKPOINT_WESTOWE)) {
			task->thwead.featuwes_wocked &= ~featuwes;
			wetuwn 0;
		}
		wetuwn -EINVAW;
	}

	/* Do not awwow to change wocked featuwes */
	if (featuwes & task->thwead.featuwes_wocked)
		wetuwn -EPEWM;

	/* Onwy suppowt enabwing/disabwing one featuwe at a time. */
	if (hweight_wong(featuwes) > 1)
		wetuwn -EINVAW;

	if (option == AWCH_SHSTK_DISABWE) {
		if (featuwes & AWCH_SHSTK_WWSS)
			wetuwn wwss_contwow(fawse);
		if (featuwes & AWCH_SHSTK_SHSTK)
			wetuwn shstk_disabwe();
		wetuwn -EINVAW;
	}

	/* Handwe AWCH_SHSTK_ENABWE */
	if (featuwes & AWCH_SHSTK_SHSTK)
		wetuwn shstk_setup();
	if (featuwes & AWCH_SHSTK_WWSS)
		wetuwn wwss_contwow(twue);
	wetuwn -EINVAW;
}
