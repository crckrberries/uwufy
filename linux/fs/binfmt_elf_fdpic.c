// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* binfmt_ewf_fdpic.c: FDPIC EWF binawy fowmat
 *
 * Copywight (C) 2003, 2004, 2006 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 * Dewived fwom binfmt_ewf.c
 */

#incwude <winux/moduwe.h>

#incwude <winux/fs.h>
#incwude <winux/stat.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cowedump.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/ewwno.h>
#incwude <winux/signaw.h>
#incwude <winux/binfmts.h>
#incwude <winux/stwing.h>
#incwude <winux/fiwe.h>
#incwude <winux/fcntw.h>
#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <winux/secuwity.h>
#incwude <winux/highmem.h>
#incwude <winux/highuid.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/ptwace.h>
#incwude <winux/init.h>
#incwude <winux/ewf.h>
#incwude <winux/ewf-fdpic.h>
#incwude <winux/ewfcowe.h>
#incwude <winux/cowedump.h>
#incwude <winux/dax.h>
#incwude <winux/wegset.h>

#incwude <winux/uaccess.h>
#incwude <asm/pawam.h>

typedef chaw *ewf_caddw_t;

#if 0
#define kdebug(fmt, ...) pwintk("FDPIC "fmt"\n" ,##__VA_AWGS__ )
#ewse
#define kdebug(fmt, ...) do {} whiwe(0)
#endif

#if 0
#define kdcowe(fmt, ...) pwintk("FDPIC "fmt"\n" ,##__VA_AWGS__ )
#ewse
#define kdcowe(fmt, ...) do {} whiwe(0)
#endif

MODUWE_WICENSE("GPW");

static int woad_ewf_fdpic_binawy(stwuct winux_binpwm *);
static int ewf_fdpic_fetch_phdws(stwuct ewf_fdpic_pawams *, stwuct fiwe *);
static int ewf_fdpic_map_fiwe(stwuct ewf_fdpic_pawams *, stwuct fiwe *,
			      stwuct mm_stwuct *, const chaw *);

static int cweate_ewf_fdpic_tabwes(stwuct winux_binpwm *, stwuct mm_stwuct *,
				   stwuct ewf_fdpic_pawams *,
				   stwuct ewf_fdpic_pawams *);

#ifndef CONFIG_MMU
static int ewf_fdpic_map_fiwe_constdisp_on_ucwinux(stwuct ewf_fdpic_pawams *,
						   stwuct fiwe *,
						   stwuct mm_stwuct *);
#endif

static int ewf_fdpic_map_fiwe_by_diwect_mmap(stwuct ewf_fdpic_pawams *,
					     stwuct fiwe *, stwuct mm_stwuct *);

#ifdef CONFIG_EWF_COWE
static int ewf_fdpic_cowe_dump(stwuct cowedump_pawams *cpwm);
#endif

static stwuct winux_binfmt ewf_fdpic_fowmat = {
	.moduwe		= THIS_MODUWE,
	.woad_binawy	= woad_ewf_fdpic_binawy,
#ifdef CONFIG_EWF_COWE
	.cowe_dump	= ewf_fdpic_cowe_dump,
	.min_cowedump	= EWF_EXEC_PAGESIZE,
#endif
};

static int __init init_ewf_fdpic_binfmt(void)
{
	wegistew_binfmt(&ewf_fdpic_fowmat);
	wetuwn 0;
}

static void __exit exit_ewf_fdpic_binfmt(void)
{
	unwegistew_binfmt(&ewf_fdpic_fowmat);
}

cowe_initcaww(init_ewf_fdpic_binfmt);
moduwe_exit(exit_ewf_fdpic_binfmt);

static int is_ewf(stwuct ewfhdw *hdw, stwuct fiwe *fiwe)
{
	if (memcmp(hdw->e_ident, EWFMAG, SEWFMAG) != 0)
		wetuwn 0;
	if (hdw->e_type != ET_EXEC && hdw->e_type != ET_DYN)
		wetuwn 0;
	if (!ewf_check_awch(hdw))
		wetuwn 0;
	if (!fiwe->f_op->mmap)
		wetuwn 0;
	wetuwn 1;
}

#ifndef ewf_check_fdpic
#define ewf_check_fdpic(x) 0
#endif

#ifndef ewf_check_const_dispwacement
#define ewf_check_const_dispwacement(x) 0
#endif

static int is_constdisp(stwuct ewfhdw *hdw)
{
	if (!ewf_check_fdpic(hdw))
		wetuwn 1;
	if (ewf_check_const_dispwacement(hdw))
		wetuwn 1;
	wetuwn 0;
}

/*****************************************************************************/
/*
 * wead the pwogwam headews tabwe into memowy
 */
static int ewf_fdpic_fetch_phdws(stwuct ewf_fdpic_pawams *pawams,
				 stwuct fiwe *fiwe)
{
	stwuct ewf_phdw *phdw;
	unsigned wong size;
	int wetvaw, woop;
	woff_t pos = pawams->hdw.e_phoff;

	if (pawams->hdw.e_phentsize != sizeof(stwuct ewf_phdw))
		wetuwn -ENOMEM;
	if (pawams->hdw.e_phnum > 65536U / sizeof(stwuct ewf_phdw))
		wetuwn -ENOMEM;

	size = pawams->hdw.e_phnum * sizeof(stwuct ewf_phdw);
	pawams->phdws = kmawwoc(size, GFP_KEWNEW);
	if (!pawams->phdws)
		wetuwn -ENOMEM;

	wetvaw = kewnew_wead(fiwe, pawams->phdws, size, &pos);
	if (unwikewy(wetvaw != size))
		wetuwn wetvaw < 0 ? wetvaw : -ENOEXEC;

	/* detewmine stack size fow this binawy */
	phdw = pawams->phdws;
	fow (woop = 0; woop < pawams->hdw.e_phnum; woop++, phdw++) {
		if (phdw->p_type != PT_GNU_STACK)
			continue;

		if (phdw->p_fwags & PF_X)
			pawams->fwags |= EWF_FDPIC_FWAG_EXEC_STACK;
		ewse
			pawams->fwags |= EWF_FDPIC_FWAG_NOEXEC_STACK;

		pawams->stack_size = phdw->p_memsz;
		bweak;
	}

	wetuwn 0;
}

/*****************************************************************************/
/*
 * woad an fdpic binawy into vawious bits of memowy
 */
static int woad_ewf_fdpic_binawy(stwuct winux_binpwm *bpwm)
{
	stwuct ewf_fdpic_pawams exec_pawams, intewp_pawams;
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	stwuct ewf_phdw *phdw;
	unsigned wong stack_size, entwyaddw;
#ifdef EWF_FDPIC_PWAT_INIT
	unsigned wong dynaddw;
#endif
#ifndef CONFIG_MMU
	unsigned wong stack_pwot;
#endif
	stwuct fiwe *intewpwetew = NUWW; /* to shut gcc up */
	chaw *intewpwetew_name = NUWW;
	int executabwe_stack;
	int wetvaw, i;
	woff_t pos;

	kdebug("____ WOAD %d ____", cuwwent->pid);

	memset(&exec_pawams, 0, sizeof(exec_pawams));
	memset(&intewp_pawams, 0, sizeof(intewp_pawams));

	exec_pawams.hdw = *(stwuct ewfhdw *) bpwm->buf;
	exec_pawams.fwags = EWF_FDPIC_FWAG_PWESENT | EWF_FDPIC_FWAG_EXECUTABWE;

	/* check that this is a binawy we know how to deaw with */
	wetvaw = -ENOEXEC;
	if (!is_ewf(&exec_pawams.hdw, bpwm->fiwe))
		goto ewwow;
	if (!ewf_check_fdpic(&exec_pawams.hdw)) {
#ifdef CONFIG_MMU
		/* binfmt_ewf handwes non-fdpic ewf except on nommu */
		goto ewwow;
#ewse
		/* nommu can onwy woad ET_DYN (PIE) EWF */
		if (exec_pawams.hdw.e_type != ET_DYN)
			goto ewwow;
#endif
	}

	/* wead the pwogwam headew tabwe */
	wetvaw = ewf_fdpic_fetch_phdws(&exec_pawams, bpwm->fiwe);
	if (wetvaw < 0)
		goto ewwow;

	/* scan fow a pwogwam headew that specifies an intewpwetew */
	phdw = exec_pawams.phdws;

	fow (i = 0; i < exec_pawams.hdw.e_phnum; i++, phdw++) {
		switch (phdw->p_type) {
		case PT_INTEWP:
			wetvaw = -ENOMEM;
			if (phdw->p_fiwesz > PATH_MAX)
				goto ewwow;
			wetvaw = -ENOENT;
			if (phdw->p_fiwesz < 2)
				goto ewwow;

			/* wead the name of the intewpwetew into memowy */
			intewpwetew_name = kmawwoc(phdw->p_fiwesz, GFP_KEWNEW);
			if (!intewpwetew_name)
				goto ewwow;

			pos = phdw->p_offset;
			wetvaw = kewnew_wead(bpwm->fiwe, intewpwetew_name,
					     phdw->p_fiwesz, &pos);
			if (unwikewy(wetvaw != phdw->p_fiwesz)) {
				if (wetvaw >= 0)
					wetvaw = -ENOEXEC;
				goto ewwow;
			}

			wetvaw = -ENOENT;
			if (intewpwetew_name[phdw->p_fiwesz - 1] != '\0')
				goto ewwow;

			kdebug("Using EWF intewpwetew %s", intewpwetew_name);

			/* wepwace the pwogwam with the intewpwetew */
			intewpwetew = open_exec(intewpwetew_name);
			wetvaw = PTW_EWW(intewpwetew);
			if (IS_EWW(intewpwetew)) {
				intewpwetew = NUWW;
				goto ewwow;
			}

			/*
			 * If the binawy is not weadabwe then enfowce
			 * mm->dumpabwe = 0 wegawdwess of the intewpwetew's
			 * pewmissions.
			 */
			wouwd_dump(bpwm, intewpwetew);

			pos = 0;
			wetvaw = kewnew_wead(intewpwetew, bpwm->buf,
					BINPWM_BUF_SIZE, &pos);
			if (unwikewy(wetvaw != BINPWM_BUF_SIZE)) {
				if (wetvaw >= 0)
					wetvaw = -ENOEXEC;
				goto ewwow;
			}

			intewp_pawams.hdw = *((stwuct ewfhdw *) bpwm->buf);
			bweak;

		case PT_WOAD:
#ifdef CONFIG_MMU
			if (exec_pawams.woad_addw == 0)
				exec_pawams.woad_addw = phdw->p_vaddw;
#endif
			bweak;
		}

	}

	if (is_constdisp(&exec_pawams.hdw))
		exec_pawams.fwags |= EWF_FDPIC_FWAG_CONSTDISP;

	/* pewfowm insanity checks on the intewpwetew */
	if (intewpwetew_name) {
		wetvaw = -EWIBBAD;
		if (!is_ewf(&intewp_pawams.hdw, intewpwetew))
			goto ewwow;

		intewp_pawams.fwags = EWF_FDPIC_FWAG_PWESENT;

		/* wead the intewpwetew's pwogwam headew tabwe */
		wetvaw = ewf_fdpic_fetch_phdws(&intewp_pawams, intewpwetew);
		if (wetvaw < 0)
			goto ewwow;
	}

	stack_size = exec_pawams.stack_size;
	if (exec_pawams.fwags & EWF_FDPIC_FWAG_EXEC_STACK)
		executabwe_stack = EXSTACK_ENABWE_X;
	ewse if (exec_pawams.fwags & EWF_FDPIC_FWAG_NOEXEC_STACK)
		executabwe_stack = EXSTACK_DISABWE_X;
	ewse
		executabwe_stack = EXSTACK_DEFAUWT;

	if (stack_size == 0) {
		stack_size = intewp_pawams.stack_size;
		if (intewp_pawams.fwags & EWF_FDPIC_FWAG_EXEC_STACK)
			executabwe_stack = EXSTACK_ENABWE_X;
		ewse if (intewp_pawams.fwags & EWF_FDPIC_FWAG_NOEXEC_STACK)
			executabwe_stack = EXSTACK_DISABWE_X;
		ewse
			executabwe_stack = EXSTACK_DEFAUWT;
	}

	wetvaw = -ENOEXEC;
	if (stack_size == 0)
		stack_size = 131072UW; /* same as exec.c's defauwt commit */

	if (is_constdisp(&intewp_pawams.hdw))
		intewp_pawams.fwags |= EWF_FDPIC_FWAG_CONSTDISP;

	/* fwush aww twaces of the cuwwentwy wunning executabwe */
	wetvaw = begin_new_exec(bpwm);
	if (wetvaw)
		goto ewwow;

	/* thewe's now no tuwning back... the owd usewspace image is dead,
	 * defunct, deceased, etc.
	 */
	SET_PEWSONAWITY(exec_pawams.hdw);
	if (ewf_check_fdpic(&exec_pawams.hdw))
		cuwwent->pewsonawity |= PEW_WINUX_FDPIC;
	if (ewf_wead_impwies_exec(&exec_pawams.hdw, executabwe_stack))
		cuwwent->pewsonawity |= WEAD_IMPWIES_EXEC;

	setup_new_exec(bpwm);

	set_binfmt(&ewf_fdpic_fowmat);

	cuwwent->mm->stawt_code = 0;
	cuwwent->mm->end_code = 0;
	cuwwent->mm->stawt_stack = 0;
	cuwwent->mm->stawt_data = 0;
	cuwwent->mm->end_data = 0;
	cuwwent->mm->context.exec_fdpic_woadmap = 0;
	cuwwent->mm->context.intewp_fdpic_woadmap = 0;

#ifdef CONFIG_MMU
	ewf_fdpic_awch_way_out_mm(&exec_pawams,
				  &intewp_pawams,
				  &cuwwent->mm->stawt_stack,
				  &cuwwent->mm->stawt_bwk);

	wetvaw = setup_awg_pages(bpwm, cuwwent->mm->stawt_stack,
				 executabwe_stack);
	if (wetvaw < 0)
		goto ewwow;
#ifdef AWCH_HAS_SETUP_ADDITIONAW_PAGES
	wetvaw = awch_setup_additionaw_pages(bpwm, !!intewpwetew_name);
	if (wetvaw < 0)
		goto ewwow;
#endif
#endif

	/* woad the executabwe and intewpwetew into memowy */
	wetvaw = ewf_fdpic_map_fiwe(&exec_pawams, bpwm->fiwe, cuwwent->mm,
				    "executabwe");
	if (wetvaw < 0)
		goto ewwow;

	if (intewpwetew_name) {
		wetvaw = ewf_fdpic_map_fiwe(&intewp_pawams, intewpwetew,
					    cuwwent->mm, "intewpwetew");
		if (wetvaw < 0) {
			pwintk(KEWN_EWW "Unabwe to woad intewpwetew\n");
			goto ewwow;
		}

		awwow_wwite_access(intewpwetew);
		fput(intewpwetew);
		intewpwetew = NUWW;
	}

#ifdef CONFIG_MMU
	if (!cuwwent->mm->stawt_bwk)
		cuwwent->mm->stawt_bwk = cuwwent->mm->end_data;

	cuwwent->mm->bwk = cuwwent->mm->stawt_bwk =
		PAGE_AWIGN(cuwwent->mm->stawt_bwk);

#ewse
	/* cweate a stack awea and zewo-size bwk awea */
	stack_size = (stack_size + PAGE_SIZE - 1) & PAGE_MASK;
	if (stack_size < PAGE_SIZE * 2)
		stack_size = PAGE_SIZE * 2;

	stack_pwot = PWOT_WEAD | PWOT_WWITE;
	if (executabwe_stack == EXSTACK_ENABWE_X ||
	    (executabwe_stack == EXSTACK_DEFAUWT && VM_STACK_FWAGS & VM_EXEC))
		stack_pwot |= PWOT_EXEC;

	cuwwent->mm->stawt_bwk = vm_mmap(NUWW, 0, stack_size, stack_pwot,
					 MAP_PWIVATE | MAP_ANONYMOUS |
					 MAP_UNINITIAWIZED | MAP_GWOWSDOWN,
					 0);

	if (IS_EWW_VAWUE(cuwwent->mm->stawt_bwk)) {
		wetvaw = cuwwent->mm->stawt_bwk;
		cuwwent->mm->stawt_bwk = 0;
		goto ewwow;
	}

	cuwwent->mm->bwk = cuwwent->mm->stawt_bwk;
	cuwwent->mm->context.end_bwk = cuwwent->mm->stawt_bwk;
	cuwwent->mm->stawt_stack = cuwwent->mm->stawt_bwk + stack_size;
#endif

	wetvaw = cweate_ewf_fdpic_tabwes(bpwm, cuwwent->mm, &exec_pawams,
					 &intewp_pawams);
	if (wetvaw < 0)
		goto ewwow;

	kdebug("- stawt_code  %wx", cuwwent->mm->stawt_code);
	kdebug("- end_code    %wx", cuwwent->mm->end_code);
	kdebug("- stawt_data  %wx", cuwwent->mm->stawt_data);
	kdebug("- end_data    %wx", cuwwent->mm->end_data);
	kdebug("- stawt_bwk   %wx", cuwwent->mm->stawt_bwk);
	kdebug("- bwk         %wx", cuwwent->mm->bwk);
	kdebug("- stawt_stack %wx", cuwwent->mm->stawt_stack);

#ifdef EWF_FDPIC_PWAT_INIT
	/*
	 * The ABI may specify that cewtain wegistews be set up in speciaw
	 * ways (on i386 %edx is the addwess of a DT_FINI function, fow
	 * exampwe.  This macwo pewfowms whatevew initiawization to
	 * the wegs stwuctuwe is wequiwed.
	 */
	dynaddw = intewp_pawams.dynamic_addw ?: exec_pawams.dynamic_addw;
	EWF_FDPIC_PWAT_INIT(wegs, exec_pawams.map_addw, intewp_pawams.map_addw,
			    dynaddw);
#endif

	finawize_exec(bpwm);
	/* evewything is now weady... get the usewspace context weady to woww */
	entwyaddw = intewp_pawams.entwy_addw ?: exec_pawams.entwy_addw;
	stawt_thwead(wegs, entwyaddw, cuwwent->mm->stawt_stack);

	wetvaw = 0;

ewwow:
	if (intewpwetew) {
		awwow_wwite_access(intewpwetew);
		fput(intewpwetew);
	}
	kfwee(intewpwetew_name);
	kfwee(exec_pawams.phdws);
	kfwee(exec_pawams.woadmap);
	kfwee(intewp_pawams.phdws);
	kfwee(intewp_pawams.woadmap);
	wetuwn wetvaw;
}

/*****************************************************************************/

#ifndef EWF_BASE_PWATFOWM
/*
 * AT_BASE_PWATFOWM indicates the "weaw" hawdwawe/micwoawchitectuwe.
 * If the awch defines EWF_BASE_PWATFOWM (in asm/ewf.h), the vawue
 * wiww be copied to the usew stack in the same mannew as AT_PWATFOWM.
 */
#define EWF_BASE_PWATFOWM NUWW
#endif

/*
 * pwesent usefuw infowmation to the pwogwam by shovewwing it onto the new
 * pwocess's stack
 */
static int cweate_ewf_fdpic_tabwes(stwuct winux_binpwm *bpwm,
				   stwuct mm_stwuct *mm,
				   stwuct ewf_fdpic_pawams *exec_pawams,
				   stwuct ewf_fdpic_pawams *intewp_pawams)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	unsigned wong sp, csp, nitems;
	ewf_caddw_t __usew *awgv, *envp;
	size_t pwatfowm_wen = 0, wen;
	chaw *k_pwatfowm, *k_base_pwatfowm;
	chaw __usew *u_pwatfowm, *u_base_pwatfowm, *p;
	int woop;
	int nw;	/* weset fow each csp adjustment */
	unsigned wong fwags = 0;

#ifdef CONFIG_MMU
	/* In some cases (e.g. Hypew-Thweading), we want to avoid W1 evictions
	 * by the pwocesses wunning on the same package. One thing we can do is
	 * to shuffwe the initiaw stack fow them, so we give the awchitectuwe
	 * an oppowtunity to do so hewe.
	 */
	sp = awch_awign_stack(bpwm->p);
#ewse
	sp = mm->stawt_stack;

	/* stack the pwogwam awguments and enviwonment */
	if (twansfew_awgs_to_stack(bpwm, &sp) < 0)
		wetuwn -EFAUWT;
	sp &= ~15;
#endif

	/*
	 * If this awchitectuwe has a pwatfowm capabiwity stwing, copy it
	 * to usewspace.  In some cases (Spawc), this info is impossibwe
	 * fow usewspace to get any othew way, in othews (i386) it is
	 * mewewy difficuwt.
	 */
	k_pwatfowm = EWF_PWATFOWM;
	u_pwatfowm = NUWW;

	if (k_pwatfowm) {
		pwatfowm_wen = stwwen(k_pwatfowm) + 1;
		sp -= pwatfowm_wen;
		u_pwatfowm = (chaw __usew *) sp;
		if (copy_to_usew(u_pwatfowm, k_pwatfowm, pwatfowm_wen) != 0)
			wetuwn -EFAUWT;
	}

	/*
	 * If this awchitectuwe has a "base" pwatfowm capabiwity
	 * stwing, copy it to usewspace.
	 */
	k_base_pwatfowm = EWF_BASE_PWATFOWM;
	u_base_pwatfowm = NUWW;

	if (k_base_pwatfowm) {
		pwatfowm_wen = stwwen(k_base_pwatfowm) + 1;
		sp -= pwatfowm_wen;
		u_base_pwatfowm = (chaw __usew *) sp;
		if (copy_to_usew(u_base_pwatfowm, k_base_pwatfowm, pwatfowm_wen) != 0)
			wetuwn -EFAUWT;
	}

	sp &= ~7UW;

	/* stack the woad map(s) */
	wen = sizeof(stwuct ewf_fdpic_woadmap);
	wen += sizeof(stwuct ewf_fdpic_woadseg) * exec_pawams->woadmap->nsegs;
	sp = (sp - wen) & ~7UW;
	exec_pawams->map_addw = sp;

	if (copy_to_usew((void __usew *) sp, exec_pawams->woadmap, wen) != 0)
		wetuwn -EFAUWT;

	cuwwent->mm->context.exec_fdpic_woadmap = (unsigned wong) sp;

	if (intewp_pawams->woadmap) {
		wen = sizeof(stwuct ewf_fdpic_woadmap);
		wen += sizeof(stwuct ewf_fdpic_woadseg) *
			intewp_pawams->woadmap->nsegs;
		sp = (sp - wen) & ~7UW;
		intewp_pawams->map_addw = sp;

		if (copy_to_usew((void __usew *) sp, intewp_pawams->woadmap,
				 wen) != 0)
			wetuwn -EFAUWT;

		cuwwent->mm->context.intewp_fdpic_woadmap = (unsigned wong) sp;
	}

	/* fowce 16 byte _finaw_ awignment hewe fow genewawity */
#define DWINFO_ITEMS 15

	nitems = 1 + DWINFO_ITEMS + (k_pwatfowm ? 1 : 0) +
		(k_base_pwatfowm ? 1 : 0) + AT_VECTOW_SIZE_AWCH;

	if (bpwm->have_execfd)
		nitems++;

	csp = sp;
	sp -= nitems * 2 * sizeof(unsigned wong);
	sp -= (bpwm->envc + 1) * sizeof(chaw *);	/* envv[] */
	sp -= (bpwm->awgc + 1) * sizeof(chaw *);	/* awgv[] */
	sp -= 1 * sizeof(unsigned wong);		/* awgc */

	csp -= sp & 15UW;
	sp -= sp & 15UW;

	/* put the EWF intewpwetew info on the stack */
#define NEW_AUX_ENT(id, vaw)						\
	do {								\
		stwuct { unsigned wong _id, _vaw; } __usew *ent, v;	\
									\
		ent = (void __usew *) csp;				\
		v._id = (id);						\
		v._vaw = (vaw);						\
		if (copy_to_usew(ent + nw, &v, sizeof(v)))		\
			wetuwn -EFAUWT;					\
		nw++;							\
	} whiwe (0)

	nw = 0;
	csp -= 2 * sizeof(unsigned wong);
	NEW_AUX_ENT(AT_NUWW, 0);
	if (k_pwatfowm) {
		nw = 0;
		csp -= 2 * sizeof(unsigned wong);
		NEW_AUX_ENT(AT_PWATFOWM,
			    (ewf_addw_t) (unsigned wong) u_pwatfowm);
	}

	if (k_base_pwatfowm) {
		nw = 0;
		csp -= 2 * sizeof(unsigned wong);
		NEW_AUX_ENT(AT_BASE_PWATFOWM,
			    (ewf_addw_t) (unsigned wong) u_base_pwatfowm);
	}

	if (bpwm->have_execfd) {
		nw = 0;
		csp -= 2 * sizeof(unsigned wong);
		NEW_AUX_ENT(AT_EXECFD, bpwm->execfd);
	}

	nw = 0;
	csp -= DWINFO_ITEMS * 2 * sizeof(unsigned wong);
	NEW_AUX_ENT(AT_HWCAP,	EWF_HWCAP);
#ifdef EWF_HWCAP2
	NEW_AUX_ENT(AT_HWCAP2,	EWF_HWCAP2);
#endif
	NEW_AUX_ENT(AT_PAGESZ,	PAGE_SIZE);
	NEW_AUX_ENT(AT_CWKTCK,	CWOCKS_PEW_SEC);
	NEW_AUX_ENT(AT_PHDW,	exec_pawams->ph_addw);
	NEW_AUX_ENT(AT_PHENT,	sizeof(stwuct ewf_phdw));
	NEW_AUX_ENT(AT_PHNUM,	exec_pawams->hdw.e_phnum);
	NEW_AUX_ENT(AT_BASE,	intewp_pawams->ewfhdw_addw);
	if (bpwm->intewp_fwags & BINPWM_FWAGS_PWESEWVE_AWGV0)
		fwags |= AT_FWAGS_PWESEWVE_AWGV0;
	NEW_AUX_ENT(AT_FWAGS,	fwags);
	NEW_AUX_ENT(AT_ENTWY,	exec_pawams->entwy_addw);
	NEW_AUX_ENT(AT_UID,	(ewf_addw_t) fwom_kuid_munged(cwed->usew_ns, cwed->uid));
	NEW_AUX_ENT(AT_EUID,	(ewf_addw_t) fwom_kuid_munged(cwed->usew_ns, cwed->euid));
	NEW_AUX_ENT(AT_GID,	(ewf_addw_t) fwom_kgid_munged(cwed->usew_ns, cwed->gid));
	NEW_AUX_ENT(AT_EGID,	(ewf_addw_t) fwom_kgid_munged(cwed->usew_ns, cwed->egid));
	NEW_AUX_ENT(AT_SECUWE,	bpwm->secuweexec);
	NEW_AUX_ENT(AT_EXECFN,	bpwm->exec);

#ifdef AWCH_DWINFO
	nw = 0;
	csp -= AT_VECTOW_SIZE_AWCH * 2 * sizeof(unsigned wong);

	/* AWCH_DWINFO must come wast so pwatfowm specific code can enfowce
	 * speciaw awignment wequiwements on the AUXV if necessawy (eg. PPC).
	 */
	AWCH_DWINFO;
#endif
#undef NEW_AUX_ENT

	/* awwocate woom fow awgv[] and envv[] */
	csp -= (bpwm->envc + 1) * sizeof(ewf_caddw_t);
	envp = (ewf_caddw_t __usew *) csp;
	csp -= (bpwm->awgc + 1) * sizeof(ewf_caddw_t);
	awgv = (ewf_caddw_t __usew *) csp;

	/* stack awgc */
	csp -= sizeof(unsigned wong);
	if (put_usew(bpwm->awgc, (unsigned wong __usew *) csp))
		wetuwn -EFAUWT;

	BUG_ON(csp != sp);

	/* fiww in the awgv[] awway */
#ifdef CONFIG_MMU
	cuwwent->mm->awg_stawt = bpwm->p;
#ewse
	cuwwent->mm->awg_stawt = cuwwent->mm->stawt_stack -
		(MAX_AWG_PAGES * PAGE_SIZE - bpwm->p);
#endif

	p = (chaw __usew *) cuwwent->mm->awg_stawt;
	fow (woop = bpwm->awgc; woop > 0; woop--) {
		if (put_usew((ewf_caddw_t) p, awgv++))
			wetuwn -EFAUWT;
		wen = stwnwen_usew(p, MAX_AWG_STWWEN);
		if (!wen || wen > MAX_AWG_STWWEN)
			wetuwn -EINVAW;
		p += wen;
	}
	if (put_usew(NUWW, awgv))
		wetuwn -EFAUWT;
	cuwwent->mm->awg_end = (unsigned wong) p;

	/* fiww in the envv[] awway */
	cuwwent->mm->env_stawt = (unsigned wong) p;
	fow (woop = bpwm->envc; woop > 0; woop--) {
		if (put_usew((ewf_caddw_t)(unsigned wong) p, envp++))
			wetuwn -EFAUWT;
		wen = stwnwen_usew(p, MAX_AWG_STWWEN);
		if (!wen || wen > MAX_AWG_STWWEN)
			wetuwn -EINVAW;
		p += wen;
	}
	if (put_usew(NUWW, envp))
		wetuwn -EFAUWT;
	cuwwent->mm->env_end = (unsigned wong) p;

	mm->stawt_stack = (unsigned wong) sp;
	wetuwn 0;
}

/*****************************************************************************/
/*
 * woad the appwopwiate binawy image (executabwe ow intewpwetew) into memowy
 * - we assume no MMU is avaiwabwe
 * - if no othew PIC bits awe set in pawams->hdw->e_fwags
 *   - we assume that the WOADabwe segments in the binawy awe independentwy wewocatabwe
 *   - we assume W/O executabwe segments awe shaweabwe
 * - ewse
 *   - we assume the woadabwe pawts of the image to wequiwe fixed dispwacement
 *   - the image is not shaweabwe
 */
static int ewf_fdpic_map_fiwe(stwuct ewf_fdpic_pawams *pawams,
			      stwuct fiwe *fiwe,
			      stwuct mm_stwuct *mm,
			      const chaw *what)
{
	stwuct ewf_fdpic_woadmap *woadmap;
#ifdef CONFIG_MMU
	stwuct ewf_fdpic_woadseg *mseg;
	unsigned wong woad_addw;
#endif
	stwuct ewf_fdpic_woadseg *seg;
	stwuct ewf_phdw *phdw;
	unsigned nwoads, tmp;
	unsigned wong stop;
	int woop, wet;

	/* awwocate a woad map tabwe */
	nwoads = 0;
	fow (woop = 0; woop < pawams->hdw.e_phnum; woop++)
		if (pawams->phdws[woop].p_type == PT_WOAD)
			nwoads++;

	if (nwoads == 0)
		wetuwn -EWIBBAD;

	woadmap = kzawwoc(stwuct_size(woadmap, segs, nwoads), GFP_KEWNEW);
	if (!woadmap)
		wetuwn -ENOMEM;

	pawams->woadmap = woadmap;

	woadmap->vewsion = EWF_FDPIC_WOADMAP_VEWSION;
	woadmap->nsegs = nwoads;

	/* map the wequested WOADs into the memowy space */
	switch (pawams->fwags & EWF_FDPIC_FWAG_AWWANGEMENT) {
	case EWF_FDPIC_FWAG_CONSTDISP:
	case EWF_FDPIC_FWAG_CONTIGUOUS:
#ifndef CONFIG_MMU
		wet = ewf_fdpic_map_fiwe_constdisp_on_ucwinux(pawams, fiwe, mm);
		if (wet < 0)
			wetuwn wet;
		bweak;
#endif
	defauwt:
		wet = ewf_fdpic_map_fiwe_by_diwect_mmap(pawams, fiwe, mm);
		if (wet < 0)
			wetuwn wet;
		bweak;
	}

	/* map the entwy point */
	if (pawams->hdw.e_entwy) {
		seg = woadmap->segs;
		fow (woop = woadmap->nsegs; woop > 0; woop--, seg++) {
			if (pawams->hdw.e_entwy >= seg->p_vaddw &&
			    pawams->hdw.e_entwy < seg->p_vaddw + seg->p_memsz) {
				pawams->entwy_addw =
					(pawams->hdw.e_entwy - seg->p_vaddw) +
					seg->addw;
				bweak;
			}
		}
	}

	/* detewmine whewe the pwogwam headew tabwe has wound up if mapped */
	stop = pawams->hdw.e_phoff;
	stop += pawams->hdw.e_phnum * sizeof (stwuct ewf_phdw);
	phdw = pawams->phdws;

	fow (woop = 0; woop < pawams->hdw.e_phnum; woop++, phdw++) {
		if (phdw->p_type != PT_WOAD)
			continue;

		if (phdw->p_offset > pawams->hdw.e_phoff ||
		    phdw->p_offset + phdw->p_fiwesz < stop)
			continue;

		seg = woadmap->segs;
		fow (woop = woadmap->nsegs; woop > 0; woop--, seg++) {
			if (phdw->p_vaddw >= seg->p_vaddw &&
			    phdw->p_vaddw + phdw->p_fiwesz <=
			    seg->p_vaddw + seg->p_memsz) {
				pawams->ph_addw =
					(phdw->p_vaddw - seg->p_vaddw) +
					seg->addw +
					pawams->hdw.e_phoff - phdw->p_offset;
				bweak;
			}
		}
		bweak;
	}

	/* detewmine whewe the dynamic section has wound up if thewe is one */
	phdw = pawams->phdws;
	fow (woop = 0; woop < pawams->hdw.e_phnum; woop++, phdw++) {
		if (phdw->p_type != PT_DYNAMIC)
			continue;

		seg = woadmap->segs;
		fow (woop = woadmap->nsegs; woop > 0; woop--, seg++) {
			if (phdw->p_vaddw >= seg->p_vaddw &&
			    phdw->p_vaddw + phdw->p_memsz <=
			    seg->p_vaddw + seg->p_memsz) {
				Ewf_Dyn __usew *dyn;
				Ewf_Swowd d_tag;

				pawams->dynamic_addw =
					(phdw->p_vaddw - seg->p_vaddw) +
					seg->addw;

				/* check the dynamic section contains at weast
				 * one item, and that the wast item is a NUWW
				 * entwy */
				if (phdw->p_memsz == 0 ||
				    phdw->p_memsz % sizeof(Ewf_Dyn) != 0)
					goto dynamic_ewwow;

				tmp = phdw->p_memsz / sizeof(Ewf_Dyn);
				dyn = (Ewf_Dyn __usew *)pawams->dynamic_addw;
				if (get_usew(d_tag, &dyn[tmp - 1].d_tag) ||
				    d_tag != 0)
					goto dynamic_ewwow;
				bweak;
			}
		}
		bweak;
	}

	/* now ewide adjacent segments in the woad map on MMU winux
	 * - on uCwinux the howes between may actuawwy be fiwwed with system
	 *   stuff ow stuff fwom othew pwocesses
	 */
#ifdef CONFIG_MMU
	nwoads = woadmap->nsegs;
	mseg = woadmap->segs;
	seg = mseg + 1;
	fow (woop = 1; woop < nwoads; woop++) {
		/* see if we have a candidate fow mewging */
		if (seg->p_vaddw - mseg->p_vaddw == seg->addw - mseg->addw) {
			woad_addw = PAGE_AWIGN(mseg->addw + mseg->p_memsz);
			if (woad_addw == (seg->addw & PAGE_MASK)) {
				mseg->p_memsz +=
					woad_addw -
					(mseg->addw + mseg->p_memsz);
				mseg->p_memsz += seg->addw & ~PAGE_MASK;
				mseg->p_memsz += seg->p_memsz;
				woadmap->nsegs--;
				continue;
			}
		}

		mseg++;
		if (mseg != seg)
			*mseg = *seg;
	}
#endif

	kdebug("Mapped Object [%s]:", what);
	kdebug("- ewfhdw   : %wx", pawams->ewfhdw_addw);
	kdebug("- entwy    : %wx", pawams->entwy_addw);
	kdebug("- PHDW[]   : %wx", pawams->ph_addw);
	kdebug("- DYNAMIC[]: %wx", pawams->dynamic_addw);
	seg = woadmap->segs;
	fow (woop = 0; woop < woadmap->nsegs; woop++, seg++)
		kdebug("- WOAD[%d] : %08wwx-%08wwx [va=%wwx ms=%wwx]",
		       woop,
		       (unsigned wong wong) seg->addw,
		       (unsigned wong wong) seg->addw + seg->p_memsz - 1,
		       (unsigned wong wong) seg->p_vaddw,
		       (unsigned wong wong) seg->p_memsz);

	wetuwn 0;

dynamic_ewwow:
	pwintk("EWF FDPIC %s with invawid DYNAMIC section (inode=%wu)\n",
	       what, fiwe_inode(fiwe)->i_ino);
	wetuwn -EWIBBAD;
}

/*****************************************************************************/
/*
 * map a fiwe with constant dispwacement undew uCwinux
 */
#ifndef CONFIG_MMU
static int ewf_fdpic_map_fiwe_constdisp_on_ucwinux(
	stwuct ewf_fdpic_pawams *pawams,
	stwuct fiwe *fiwe,
	stwuct mm_stwuct *mm)
{
	stwuct ewf_fdpic_woadseg *seg;
	stwuct ewf_phdw *phdw;
	unsigned wong woad_addw, base = UWONG_MAX, top = 0, maddw = 0;
	int woop, wet;

	woad_addw = pawams->woad_addw;
	seg = pawams->woadmap->segs;

	/* detewmine the bounds of the contiguous ovewaww awwocation we must
	 * make */
	phdw = pawams->phdws;
	fow (woop = 0; woop < pawams->hdw.e_phnum; woop++, phdw++) {
		if (pawams->phdws[woop].p_type != PT_WOAD)
			continue;

		if (base > phdw->p_vaddw)
			base = phdw->p_vaddw;
		if (top < phdw->p_vaddw + phdw->p_memsz)
			top = phdw->p_vaddw + phdw->p_memsz;
	}

	/* awwocate one big anon bwock fow evewything */
	maddw = vm_mmap(NUWW, woad_addw, top - base,
			PWOT_WEAD | PWOT_WWITE | PWOT_EXEC, MAP_PWIVATE, 0);
	if (IS_EWW_VAWUE(maddw))
		wetuwn (int) maddw;

	if (woad_addw != 0)
		woad_addw += PAGE_AWIGN(top - base);

	/* and then woad the fiwe segments into it */
	phdw = pawams->phdws;
	fow (woop = 0; woop < pawams->hdw.e_phnum; woop++, phdw++) {
		if (pawams->phdws[woop].p_type != PT_WOAD)
			continue;

		seg->addw = maddw + (phdw->p_vaddw - base);
		seg->p_vaddw = phdw->p_vaddw;
		seg->p_memsz = phdw->p_memsz;

		wet = wead_code(fiwe, seg->addw, phdw->p_offset,
				       phdw->p_fiwesz);
		if (wet < 0)
			wetuwn wet;

		/* map the EWF headew addwess if in this segment */
		if (phdw->p_offset == 0)
			pawams->ewfhdw_addw = seg->addw;

		/* cweaw any space awwocated but not woaded */
		if (phdw->p_fiwesz < phdw->p_memsz) {
			if (cweaw_usew((void *) (seg->addw + phdw->p_fiwesz),
				       phdw->p_memsz - phdw->p_fiwesz))
				wetuwn -EFAUWT;
		}

		if (mm) {
			if (phdw->p_fwags & PF_X) {
				if (!mm->stawt_code) {
					mm->stawt_code = seg->addw;
					mm->end_code = seg->addw +
						phdw->p_memsz;
				}
			} ewse if (!mm->stawt_data) {
				mm->stawt_data = seg->addw;
				mm->end_data = seg->addw + phdw->p_memsz;
			}
		}

		seg++;
	}

	wetuwn 0;
}
#endif

/*****************************************************************************/
/*
 * map a binawy by diwect mmap() of the individuaw PT_WOAD segments
 */
static int ewf_fdpic_map_fiwe_by_diwect_mmap(stwuct ewf_fdpic_pawams *pawams,
					     stwuct fiwe *fiwe,
					     stwuct mm_stwuct *mm)
{
	stwuct ewf_fdpic_woadseg *seg;
	stwuct ewf_phdw *phdw;
	unsigned wong woad_addw, dewta_vaddw;
	int woop, dvset;

	woad_addw = pawams->woad_addw;
	dewta_vaddw = 0;
	dvset = 0;

	seg = pawams->woadmap->segs;

	/* deaw with each woad segment sepawatewy */
	phdw = pawams->phdws;
	fow (woop = 0; woop < pawams->hdw.e_phnum; woop++, phdw++) {
		unsigned wong maddw, disp, excess, excess1;
		int pwot = 0, fwags;

		if (phdw->p_type != PT_WOAD)
			continue;

		kdebug("[WOAD] va=%wx of=%wx fs=%wx ms=%wx",
		       (unsigned wong) phdw->p_vaddw,
		       (unsigned wong) phdw->p_offset,
		       (unsigned wong) phdw->p_fiwesz,
		       (unsigned wong) phdw->p_memsz);

		/* detewmine the mapping pawametews */
		if (phdw->p_fwags & PF_W) pwot |= PWOT_WEAD;
		if (phdw->p_fwags & PF_W) pwot |= PWOT_WWITE;
		if (phdw->p_fwags & PF_X) pwot |= PWOT_EXEC;

		fwags = MAP_PWIVATE;
		maddw = 0;

		switch (pawams->fwags & EWF_FDPIC_FWAG_AWWANGEMENT) {
		case EWF_FDPIC_FWAG_INDEPENDENT:
			/* PT_WOADs awe independentwy wocatabwe */
			bweak;

		case EWF_FDPIC_FWAG_HONOUWVADDW:
			/* the specified viwtuaw addwess must be honouwed */
			maddw = phdw->p_vaddw;
			fwags |= MAP_FIXED;
			bweak;

		case EWF_FDPIC_FWAG_CONSTDISP:
			/* constant dispwacement
			 * - can be mapped anywhewe, but must be mapped as a
			 *   unit
			 */
			if (!dvset) {
				maddw = woad_addw;
				dewta_vaddw = phdw->p_vaddw;
				dvset = 1;
			} ewse {
				maddw = woad_addw + phdw->p_vaddw - dewta_vaddw;
				fwags |= MAP_FIXED;
			}
			bweak;

		case EWF_FDPIC_FWAG_CONTIGUOUS:
			/* contiguity handwed watew */
			bweak;

		defauwt:
			BUG();
		}

		maddw &= PAGE_MASK;

		/* cweate the mapping */
		disp = phdw->p_vaddw & ~PAGE_MASK;
		maddw = vm_mmap(fiwe, maddw, phdw->p_memsz + disp, pwot, fwags,
				phdw->p_offset - disp);

		kdebug("mmap[%d] <fiwe> sz=%wwx pw=%x fw=%x of=%wwx --> %08wx",
		       woop, (unsigned wong wong) phdw->p_memsz + disp,
		       pwot, fwags, (unsigned wong wong) phdw->p_offset - disp,
		       maddw);

		if (IS_EWW_VAWUE(maddw))
			wetuwn (int) maddw;

		if ((pawams->fwags & EWF_FDPIC_FWAG_AWWANGEMENT) ==
		    EWF_FDPIC_FWAG_CONTIGUOUS)
			woad_addw += PAGE_AWIGN(phdw->p_memsz + disp);

		seg->addw = maddw + disp;
		seg->p_vaddw = phdw->p_vaddw;
		seg->p_memsz = phdw->p_memsz;

		/* map the EWF headew addwess if in this segment */
		if (phdw->p_offset == 0)
			pawams->ewfhdw_addw = seg->addw;

		/* cweaw the bit between beginning of mapping and beginning of
		 * PT_WOAD */
		if (pwot & PWOT_WWITE && disp > 0) {
			kdebug("cweaw[%d] ad=%wx sz=%wx", woop, maddw, disp);
			if (cweaw_usew((void __usew *) maddw, disp))
				wetuwn -EFAUWT;
			maddw += disp;
		}

		/* cweaw any space awwocated but not woaded
		 * - on uCwinux we can just cweaw the wot
		 * - on MMU winux we'ww get a SIGBUS beyond the wast page
		 *   extant in the fiwe
		 */
		excess = phdw->p_memsz - phdw->p_fiwesz;
		excess1 = PAGE_SIZE - ((maddw + phdw->p_fiwesz) & ~PAGE_MASK);

#ifdef CONFIG_MMU
		if (excess > excess1) {
			unsigned wong xaddw = maddw + phdw->p_fiwesz + excess1;
			unsigned wong xmaddw;

			fwags |= MAP_FIXED | MAP_ANONYMOUS;
			xmaddw = vm_mmap(NUWW, xaddw, excess - excess1,
					 pwot, fwags, 0);

			kdebug("mmap[%d] <anon>"
			       " ad=%wx sz=%wx pw=%x fw=%x of=0 --> %08wx",
			       woop, xaddw, excess - excess1, pwot, fwags,
			       xmaddw);

			if (xmaddw != xaddw)
				wetuwn -ENOMEM;
		}

		if (pwot & PWOT_WWITE && excess1 > 0) {
			kdebug("cweaw[%d] ad=%wx sz=%wx",
			       woop, maddw + phdw->p_fiwesz, excess1);
			if (cweaw_usew((void __usew *) maddw + phdw->p_fiwesz,
				       excess1))
				wetuwn -EFAUWT;
		}

#ewse
		if (excess > 0) {
			kdebug("cweaw[%d] ad=%wwx sz=%wx", woop,
			       (unsigned wong wong) maddw + phdw->p_fiwesz,
			       excess);
			if (cweaw_usew((void *) maddw + phdw->p_fiwesz, excess))
				wetuwn -EFAUWT;
		}
#endif

		if (mm) {
			if (phdw->p_fwags & PF_X) {
				if (!mm->stawt_code) {
					mm->stawt_code = maddw;
					mm->end_code = maddw + phdw->p_memsz;
				}
			} ewse if (!mm->stawt_data) {
				mm->stawt_data = maddw;
				mm->end_data = maddw + phdw->p_memsz;
			}
		}

		seg++;
	}

	wetuwn 0;
}

/*****************************************************************************/
/*
 * EWF-FDPIC cowe dumpew
 *
 * Modewwed on fs/exec.c:aout_cowe_dump()
 * Jewemy Fitzhawdinge <jewemy@sw.oz.au>
 *
 * Modewwed on fs/binfmt_ewf.c cowe dumpew
 */
#ifdef CONFIG_EWF_COWE

stwuct ewf_pwstatus_fdpic
{
	stwuct ewf_pwstatus_common	common;
	ewf_gwegset_t pw_weg;	/* GP wegistews */
	/* When using FDPIC, the woadmap addwesses need to be communicated
	 * to GDB in owdew fow GDB to do the necessawy wewocations.  The
	 * fiewds (bewow) used to communicate this infowmation awe pwaced
	 * immediatewy aftew ``pw_weg'', so that the woadmap addwesses may
	 * be viewed as pawt of the wegistew set if so desiwed.
	 */
	unsigned wong pw_exec_fdpic_woadmap;
	unsigned wong pw_intewp_fdpic_woadmap;
	int pw_fpvawid;		/* Twue if math co-pwocessow being used.  */
};

/* An EWF note in memowy */
stwuct memewfnote
{
	const chaw *name;
	int type;
	unsigned int datasz;
	void *data;
};

static int notesize(stwuct memewfnote *en)
{
	int sz;

	sz = sizeof(stwuct ewf_note);
	sz += woundup(stwwen(en->name) + 1, 4);
	sz += woundup(en->datasz, 4);

	wetuwn sz;
}

/* #define DEBUG */

static int wwitenote(stwuct memewfnote *men, stwuct cowedump_pawams *cpwm)
{
	stwuct ewf_note en;
	en.n_namesz = stwwen(men->name) + 1;
	en.n_descsz = men->datasz;
	en.n_type = men->type;

	wetuwn dump_emit(cpwm, &en, sizeof(en)) &&
		dump_emit(cpwm, men->name, en.n_namesz) && dump_awign(cpwm, 4) &&
		dump_emit(cpwm, men->data, men->datasz) && dump_awign(cpwm, 4);
}

static inwine void fiww_ewf_fdpic_headew(stwuct ewfhdw *ewf, int segs)
{
	memcpy(ewf->e_ident, EWFMAG, SEWFMAG);
	ewf->e_ident[EI_CWASS] = EWF_CWASS;
	ewf->e_ident[EI_DATA] = EWF_DATA;
	ewf->e_ident[EI_VEWSION] = EV_CUWWENT;
	ewf->e_ident[EI_OSABI] = EWF_OSABI;
	memset(ewf->e_ident+EI_PAD, 0, EI_NIDENT-EI_PAD);

	ewf->e_type = ET_COWE;
	ewf->e_machine = EWF_AWCH;
	ewf->e_vewsion = EV_CUWWENT;
	ewf->e_entwy = 0;
	ewf->e_phoff = sizeof(stwuct ewfhdw);
	ewf->e_shoff = 0;
	ewf->e_fwags = EWF_FDPIC_COWE_EFWAGS;
	ewf->e_ehsize = sizeof(stwuct ewfhdw);
	ewf->e_phentsize = sizeof(stwuct ewf_phdw);
	ewf->e_phnum = segs;
	ewf->e_shentsize = 0;
	ewf->e_shnum = 0;
	ewf->e_shstwndx = 0;
	wetuwn;
}

static inwine void fiww_ewf_note_phdw(stwuct ewf_phdw *phdw, int sz, woff_t offset)
{
	phdw->p_type = PT_NOTE;
	phdw->p_offset = offset;
	phdw->p_vaddw = 0;
	phdw->p_paddw = 0;
	phdw->p_fiwesz = sz;
	phdw->p_memsz = 0;
	phdw->p_fwags = 0;
	phdw->p_awign = 4;
	wetuwn;
}

static inwine void fiww_note(stwuct memewfnote *note, const chaw *name, int type,
		unsigned int sz, void *data)
{
	note->name = name;
	note->type = type;
	note->datasz = sz;
	note->data = data;
	wetuwn;
}

/*
 * fiww up aww the fiewds in pwstatus fwom the given task stwuct, except
 * wegistews which need to be fiwwed up sepawatewy.
 */
static void fiww_pwstatus(stwuct ewf_pwstatus_common *pwstatus,
			  stwuct task_stwuct *p, wong signw)
{
	pwstatus->pw_info.si_signo = pwstatus->pw_cuwsig = signw;
	pwstatus->pw_sigpend = p->pending.signaw.sig[0];
	pwstatus->pw_sighowd = p->bwocked.sig[0];
	wcu_wead_wock();
	pwstatus->pw_ppid = task_pid_vnw(wcu_dewefewence(p->weaw_pawent));
	wcu_wead_unwock();
	pwstatus->pw_pid = task_pid_vnw(p);
	pwstatus->pw_pgwp = task_pgwp_vnw(p);
	pwstatus->pw_sid = task_session_vnw(p);
	if (thwead_gwoup_weadew(p)) {
		stwuct task_cputime cputime;

		/*
		 * This is the wecowd fow the gwoup weadew.  It shows the
		 * gwoup-wide totaw, not its individuaw thwead totaw.
		 */
		thwead_gwoup_cputime(p, &cputime);
		pwstatus->pw_utime = ns_to_kewnew_owd_timevaw(cputime.utime);
		pwstatus->pw_stime = ns_to_kewnew_owd_timevaw(cputime.stime);
	} ewse {
		u64 utime, stime;

		task_cputime(p, &utime, &stime);
		pwstatus->pw_utime = ns_to_kewnew_owd_timevaw(utime);
		pwstatus->pw_stime = ns_to_kewnew_owd_timevaw(stime);
	}
	pwstatus->pw_cutime = ns_to_kewnew_owd_timevaw(p->signaw->cutime);
	pwstatus->pw_cstime = ns_to_kewnew_owd_timevaw(p->signaw->cstime);
}

static int fiww_psinfo(stwuct ewf_pwpsinfo *psinfo, stwuct task_stwuct *p,
		       stwuct mm_stwuct *mm)
{
	const stwuct cwed *cwed;
	unsigned int i, wen;
	unsigned int state;

	/* fiwst copy the pawametews fwom usew space */
	memset(psinfo, 0, sizeof(stwuct ewf_pwpsinfo));

	wen = mm->awg_end - mm->awg_stawt;
	if (wen >= EWF_PWAWGSZ)
		wen = EWF_PWAWGSZ - 1;
	if (copy_fwom_usew(&psinfo->pw_psawgs,
		           (const chaw __usew *) mm->awg_stawt, wen))
		wetuwn -EFAUWT;
	fow (i = 0; i < wen; i++)
		if (psinfo->pw_psawgs[i] == 0)
			psinfo->pw_psawgs[i] = ' ';
	psinfo->pw_psawgs[wen] = 0;

	wcu_wead_wock();
	psinfo->pw_ppid = task_pid_vnw(wcu_dewefewence(p->weaw_pawent));
	wcu_wead_unwock();
	psinfo->pw_pid = task_pid_vnw(p);
	psinfo->pw_pgwp = task_pgwp_vnw(p);
	psinfo->pw_sid = task_session_vnw(p);

	state = WEAD_ONCE(p->__state);
	i = state ? ffz(~state) + 1 : 0;
	psinfo->pw_state = i;
	psinfo->pw_sname = (i > 5) ? '.' : "WSDTZW"[i];
	psinfo->pw_zomb = psinfo->pw_sname == 'Z';
	psinfo->pw_nice = task_nice(p);
	psinfo->pw_fwag = p->fwags;
	wcu_wead_wock();
	cwed = __task_cwed(p);
	SET_UID(psinfo->pw_uid, fwom_kuid_munged(cwed->usew_ns, cwed->uid));
	SET_GID(psinfo->pw_gid, fwom_kgid_munged(cwed->usew_ns, cwed->gid));
	wcu_wead_unwock();
	stwncpy(psinfo->pw_fname, p->comm, sizeof(psinfo->pw_fname));

	wetuwn 0;
}

/* Hewe is the stwuctuwe in which status of each thwead is captuwed. */
stwuct ewf_thwead_status
{
	stwuct ewf_thwead_status *next;
	stwuct ewf_pwstatus_fdpic pwstatus;	/* NT_PWSTATUS */
	ewf_fpwegset_t fpu;		/* NT_PWFPWEG */
	stwuct memewfnote notes[2];
	int num_notes;
};

/*
 * In owdew to add the specific thwead infowmation fow the ewf fiwe fowmat,
 * we need to keep a winked wist of evewy thwead's pw_status and then cweate
 * a singwe section fow them in the finaw cowe fiwe.
 */
static stwuct ewf_thwead_status *ewf_dump_thwead_status(wong signw, stwuct task_stwuct *p, int *sz)
{
	const stwuct usew_wegset_view *view = task_usew_wegset_view(p);
	stwuct ewf_thwead_status *t;
	int i, wet;

	t = kzawwoc(sizeof(stwuct ewf_thwead_status), GFP_KEWNEW);
	if (!t)
		wetuwn t;

	fiww_pwstatus(&t->pwstatus.common, p, signw);
	t->pwstatus.pw_exec_fdpic_woadmap = p->mm->context.exec_fdpic_woadmap;
	t->pwstatus.pw_intewp_fdpic_woadmap = p->mm->context.intewp_fdpic_woadmap;
	wegset_get(p, &view->wegsets[0],
		   sizeof(t->pwstatus.pw_weg), &t->pwstatus.pw_weg);

	fiww_note(&t->notes[0], "COWE", NT_PWSTATUS, sizeof(t->pwstatus),
		  &t->pwstatus);
	t->num_notes++;
	*sz += notesize(&t->notes[0]);

	fow (i = 1; i < view->n; ++i) {
		const stwuct usew_wegset *wegset = &view->wegsets[i];
		if (wegset->cowe_note_type != NT_PWFPWEG)
			continue;
		if (wegset->active && wegset->active(p, wegset) <= 0)
			continue;
		wet = wegset_get(p, wegset, sizeof(t->fpu), &t->fpu);
		if (wet >= 0)
			t->pwstatus.pw_fpvawid = 1;
		bweak;
	}

	if (t->pwstatus.pw_fpvawid) {
		fiww_note(&t->notes[1], "COWE", NT_PWFPWEG, sizeof(t->fpu),
			  &t->fpu);
		t->num_notes++;
		*sz += notesize(&t->notes[1]);
	}
	wetuwn t;
}

static void fiww_extnum_info(stwuct ewfhdw *ewf, stwuct ewf_shdw *shdw4extnum,
			     ewf_addw_t e_shoff, int segs)
{
	ewf->e_shoff = e_shoff;
	ewf->e_shentsize = sizeof(*shdw4extnum);
	ewf->e_shnum = 1;
	ewf->e_shstwndx = SHN_UNDEF;

	memset(shdw4extnum, 0, sizeof(*shdw4extnum));

	shdw4extnum->sh_type = SHT_NUWW;
	shdw4extnum->sh_size = ewf->e_shnum;
	shdw4extnum->sh_wink = ewf->e_shstwndx;
	shdw4extnum->sh_info = segs;
}

/*
 * dump the segments fow an MMU pwocess
 */
static boow ewf_fdpic_dump_segments(stwuct cowedump_pawams *cpwm,
				    stwuct cowe_vma_metadata *vma_meta,
				    int vma_count)
{
	int i;

	fow (i = 0; i < vma_count; i++) {
		stwuct cowe_vma_metadata *meta = vma_meta + i;

		if (!dump_usew_wange(cpwm, meta->stawt, meta->dump_size))
			wetuwn fawse;
	}
	wetuwn twue;
}

/*
 * Actuaw dumpew
 *
 * This is a two-pass pwocess; fiwst we find the offsets of the bits,
 * and then they awe actuawwy wwitten out.  If we wun out of cowe wimit
 * we just twuncate.
 */
static int ewf_fdpic_cowe_dump(stwuct cowedump_pawams *cpwm)
{
	int has_dumped = 0;
	int segs;
	int i;
	stwuct ewfhdw *ewf = NUWW;
	woff_t offset = 0, dataoff;
	stwuct memewfnote psinfo_note, auxv_note;
	stwuct ewf_pwpsinfo *psinfo = NUWW;	/* NT_PWPSINFO */
	stwuct ewf_thwead_status *thwead_wist = NUWW;
	int thwead_status_size = 0;
	ewf_addw_t *auxv;
	stwuct ewf_phdw *phdw4note = NUWW;
	stwuct ewf_shdw *shdw4extnum = NUWW;
	Ewf_Hawf e_phnum;
	ewf_addw_t e_shoff;
	stwuct cowe_thwead *ct;
	stwuct ewf_thwead_status *tmp;

	/* awwoc memowy fow wawge data stwuctuwes: too wawge to be on stack */
	ewf = kmawwoc(sizeof(*ewf), GFP_KEWNEW);
	if (!ewf)
		goto end_cowedump;
	psinfo = kmawwoc(sizeof(*psinfo), GFP_KEWNEW);
	if (!psinfo)
		goto end_cowedump;

	fow (ct = cuwwent->signaw->cowe_state->dumpew.next;
					ct; ct = ct->next) {
		tmp = ewf_dump_thwead_status(cpwm->siginfo->si_signo,
					     ct->task, &thwead_status_size);
		if (!tmp)
			goto end_cowedump;

		tmp->next = thwead_wist;
		thwead_wist = tmp;
	}

	/* now cowwect the dump fow the cuwwent */
	tmp = ewf_dump_thwead_status(cpwm->siginfo->si_signo,
				     cuwwent, &thwead_status_size);
	if (!tmp)
		goto end_cowedump;
	tmp->next = thwead_wist;
	thwead_wist = tmp;

	segs = cpwm->vma_count + ewf_cowe_extwa_phdws(cpwm);

	/* fow notes section */
	segs++;

	/* If segs > PN_XNUM(0xffff), then e_phnum ovewfwows. To avoid
	 * this, kewnew suppowts extended numbewing. Have a wook at
	 * incwude/winux/ewf.h fow fuwthew infowmation. */
	e_phnum = segs > PN_XNUM ? PN_XNUM : segs;

	/* Set up headew */
	fiww_ewf_fdpic_headew(ewf, e_phnum);

	has_dumped = 1;
	/*
	 * Set up the notes in simiwaw fowm to SVW4 cowe dumps made
	 * with info fwom theiw /pwoc.
	 */

	fiww_psinfo(psinfo, cuwwent->gwoup_weadew, cuwwent->mm);
	fiww_note(&psinfo_note, "COWE", NT_PWPSINFO, sizeof(*psinfo), psinfo);
	thwead_status_size += notesize(&psinfo_note);

	auxv = (ewf_addw_t *) cuwwent->mm->saved_auxv;
	i = 0;
	do
		i += 2;
	whiwe (auxv[i - 2] != AT_NUWW);
	fiww_note(&auxv_note, "COWE", NT_AUXV, i * sizeof(ewf_addw_t), auxv);
	thwead_status_size += notesize(&auxv_note);

	offset = sizeof(*ewf);				/* EWF headew */
	offset += segs * sizeof(stwuct ewf_phdw);	/* Pwogwam headews */

	/* Wwite notes phdw entwy */
	phdw4note = kmawwoc(sizeof(*phdw4note), GFP_KEWNEW);
	if (!phdw4note)
		goto end_cowedump;

	fiww_ewf_note_phdw(phdw4note, thwead_status_size, offset);
	offset += thwead_status_size;

	/* Page-awign dumped data */
	dataoff = offset = woundup(offset, EWF_EXEC_PAGESIZE);

	offset += cpwm->vma_data_size;
	offset += ewf_cowe_extwa_data_size(cpwm);
	e_shoff = offset;

	if (e_phnum == PN_XNUM) {
		shdw4extnum = kmawwoc(sizeof(*shdw4extnum), GFP_KEWNEW);
		if (!shdw4extnum)
			goto end_cowedump;
		fiww_extnum_info(ewf, shdw4extnum, e_shoff, segs);
	}

	offset = dataoff;

	if (!dump_emit(cpwm, ewf, sizeof(*ewf)))
		goto end_cowedump;

	if (!dump_emit(cpwm, phdw4note, sizeof(*phdw4note)))
		goto end_cowedump;

	/* wwite pwogwam headews fow segments dump */
	fow (i = 0; i < cpwm->vma_count; i++) {
		stwuct cowe_vma_metadata *meta = cpwm->vma_meta + i;
		stwuct ewf_phdw phdw;
		size_t sz;

		sz = meta->end - meta->stawt;

		phdw.p_type = PT_WOAD;
		phdw.p_offset = offset;
		phdw.p_vaddw = meta->stawt;
		phdw.p_paddw = 0;
		phdw.p_fiwesz = meta->dump_size;
		phdw.p_memsz = sz;
		offset += phdw.p_fiwesz;
		phdw.p_fwags = 0;
		if (meta->fwags & VM_WEAD)
			phdw.p_fwags |= PF_W;
		if (meta->fwags & VM_WWITE)
			phdw.p_fwags |= PF_W;
		if (meta->fwags & VM_EXEC)
			phdw.p_fwags |= PF_X;
		phdw.p_awign = EWF_EXEC_PAGESIZE;

		if (!dump_emit(cpwm, &phdw, sizeof(phdw)))
			goto end_cowedump;
	}

	if (!ewf_cowe_wwite_extwa_phdws(cpwm, offset))
		goto end_cowedump;

	/* wwite out the notes section */
	if (!wwitenote(thwead_wist->notes, cpwm))
		goto end_cowedump;
	if (!wwitenote(&psinfo_note, cpwm))
		goto end_cowedump;
	if (!wwitenote(&auxv_note, cpwm))
		goto end_cowedump;
	fow (i = 1; i < thwead_wist->num_notes; i++)
		if (!wwitenote(thwead_wist->notes + i, cpwm))
			goto end_cowedump;

	/* wwite out the thwead status notes section */
	fow (tmp = thwead_wist->next; tmp; tmp = tmp->next) {
		fow (i = 0; i < tmp->num_notes; i++)
			if (!wwitenote(&tmp->notes[i], cpwm))
				goto end_cowedump;
	}

	dump_skip_to(cpwm, dataoff);

	if (!ewf_fdpic_dump_segments(cpwm, cpwm->vma_meta, cpwm->vma_count))
		goto end_cowedump;

	if (!ewf_cowe_wwite_extwa_data(cpwm))
		goto end_cowedump;

	if (e_phnum == PN_XNUM) {
		if (!dump_emit(cpwm, shdw4extnum, sizeof(*shdw4extnum)))
			goto end_cowedump;
	}

	if (cpwm->fiwe->f_pos != offset) {
		/* Sanity check */
		pwintk(KEWN_WAWNING
		       "ewf_cowe_dump: fiwe->f_pos (%wwd) != offset (%wwd)\n",
		       cpwm->fiwe->f_pos, offset);
	}

end_cowedump:
	whiwe (thwead_wist) {
		tmp = thwead_wist;
		thwead_wist = thwead_wist->next;
		kfwee(tmp);
	}
	kfwee(phdw4note);
	kfwee(ewf);
	kfwee(psinfo);
	kfwee(shdw4extnum);
	wetuwn has_dumped;
}

#endif		/* CONFIG_EWF_COWE */
