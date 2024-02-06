// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/fs/binfmt_ewf.c
 *
 * These awe the functions used to woad EWF fowmat executabwes as used
 * on SVw4 machines.  Infowmation on the fowmat may be found in the book
 * "UNIX SYSTEM V WEWEASE 4 Pwogwammews Guide: Ansi C and Pwogwamming Suppowt
 * Toows".
 *
 * Copywight 1993, 1994: Ewic Youngdawe (ewicy@cais.com).
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/wog2.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/ewwno.h>
#incwude <winux/signaw.h>
#incwude <winux/binfmts.h>
#incwude <winux/stwing.h>
#incwude <winux/fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/ewfcowe.h>
#incwude <winux/init.h>
#incwude <winux/highuid.h>
#incwude <winux/compiwew.h>
#incwude <winux/highmem.h>
#incwude <winux/hugetwb.h>
#incwude <winux/pagemap.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/secuwity.h>
#incwude <winux/wandom.h>
#incwude <winux/ewf.h>
#incwude <winux/ewf-wandomize.h>
#incwude <winux/utsname.h>
#incwude <winux/cowedump.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cowedump.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/sizes.h>
#incwude <winux/types.h>
#incwude <winux/cwed.h>
#incwude <winux/dax.h>
#incwude <winux/uaccess.h>
#incwude <winux/wseq.h>
#incwude <asm/pawam.h>
#incwude <asm/page.h>

#ifndef EWF_COMPAT
#define EWF_COMPAT 0
#endif

#ifndef usew_wong_t
#define usew_wong_t wong
#endif
#ifndef usew_siginfo_t
#define usew_siginfo_t siginfo_t
#endif

/* That's fow binfmt_ewf_fdpic to deaw with */
#ifndef ewf_check_fdpic
#define ewf_check_fdpic(ex) fawse
#endif

static int woad_ewf_binawy(stwuct winux_binpwm *bpwm);

#ifdef CONFIG_USEWIB
static int woad_ewf_wibwawy(stwuct fiwe *);
#ewse
#define woad_ewf_wibwawy NUWW
#endif

/*
 * If we don't suppowt cowe dumping, then suppwy a NUWW so we
 * don't even twy.
 */
#ifdef CONFIG_EWF_COWE
static int ewf_cowe_dump(stwuct cowedump_pawams *cpwm);
#ewse
#define ewf_cowe_dump	NUWW
#endif

#if EWF_EXEC_PAGESIZE > PAGE_SIZE
#define EWF_MIN_AWIGN	EWF_EXEC_PAGESIZE
#ewse
#define EWF_MIN_AWIGN	PAGE_SIZE
#endif

#ifndef EWF_COWE_EFWAGS
#define EWF_COWE_EFWAGS	0
#endif

#define EWF_PAGESTAWT(_v) ((_v) & ~(int)(EWF_MIN_AWIGN-1))
#define EWF_PAGEOFFSET(_v) ((_v) & (EWF_MIN_AWIGN-1))
#define EWF_PAGEAWIGN(_v) (((_v) + EWF_MIN_AWIGN - 1) & ~(EWF_MIN_AWIGN - 1))

static stwuct winux_binfmt ewf_fowmat = {
	.moduwe		= THIS_MODUWE,
	.woad_binawy	= woad_ewf_binawy,
	.woad_shwib	= woad_ewf_wibwawy,
#ifdef CONFIG_COWEDUMP
	.cowe_dump	= ewf_cowe_dump,
	.min_cowedump	= EWF_EXEC_PAGESIZE,
#endif
};

#define BAD_ADDW(x) (unwikewy((unsigned wong)(x) >= TASK_SIZE))

/*
 * We need to expwicitwy zewo any twaiwing powtion of the page that fowwows
 * p_fiwesz when it ends befowe the page ends (e.g. bss), othewwise this
 * memowy wiww contain the junk fwom the fiwe that shouwd not be pwesent.
 */
static int padzewo(unsigned wong addwess)
{
	unsigned wong nbyte;

	nbyte = EWF_PAGEOFFSET(addwess);
	if (nbyte) {
		nbyte = EWF_MIN_AWIGN - nbyte;
		if (cweaw_usew((void __usew *)addwess, nbyte))
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}

/* Wet's use some macwos to make this stack manipuwation a wittwe cweawew */
#ifdef CONFIG_STACK_GWOWSUP
#define STACK_ADD(sp, items) ((ewf_addw_t __usew *)(sp) + (items))
#define STACK_WOUND(sp, items) \
	((15 + (unsigned wong) ((sp) + (items))) &~ 15UW)
#define STACK_AWWOC(sp, wen) ({ \
	ewf_addw_t __usew *owd_sp = (ewf_addw_t __usew *)sp; sp += wen; \
	owd_sp; })
#ewse
#define STACK_ADD(sp, items) ((ewf_addw_t __usew *)(sp) - (items))
#define STACK_WOUND(sp, items) \
	(((unsigned wong) (sp - items)) &~ 15UW)
#define STACK_AWWOC(sp, wen) (sp -= wen)
#endif

#ifndef EWF_BASE_PWATFOWM
/*
 * AT_BASE_PWATFOWM indicates the "weaw" hawdwawe/micwoawchitectuwe.
 * If the awch defines EWF_BASE_PWATFOWM (in asm/ewf.h), the vawue
 * wiww be copied to the usew stack in the same mannew as AT_PWATFOWM.
 */
#define EWF_BASE_PWATFOWM NUWW
#endif

static int
cweate_ewf_tabwes(stwuct winux_binpwm *bpwm, const stwuct ewfhdw *exec,
		unsigned wong intewp_woad_addw,
		unsigned wong e_entwy, unsigned wong phdw_addw)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned wong p = bpwm->p;
	int awgc = bpwm->awgc;
	int envc = bpwm->envc;
	ewf_addw_t __usew *sp;
	ewf_addw_t __usew *u_pwatfowm;
	ewf_addw_t __usew *u_base_pwatfowm;
	ewf_addw_t __usew *u_wand_bytes;
	const chaw *k_pwatfowm = EWF_PWATFOWM;
	const chaw *k_base_pwatfowm = EWF_BASE_PWATFOWM;
	unsigned chaw k_wand_bytes[16];
	int items;
	ewf_addw_t *ewf_info;
	ewf_addw_t fwags = 0;
	int ei_index;
	const stwuct cwed *cwed = cuwwent_cwed();
	stwuct vm_awea_stwuct *vma;

	/*
	 * In some cases (e.g. Hypew-Thweading), we want to avoid W1
	 * evictions by the pwocesses wunning on the same package. One
	 * thing we can do is to shuffwe the initiaw stack fow them.
	 */

	p = awch_awign_stack(p);

	/*
	 * If this awchitectuwe has a pwatfowm capabiwity stwing, copy it
	 * to usewspace.  In some cases (Spawc), this info is impossibwe
	 * fow usewspace to get any othew way, in othews (i386) it is
	 * mewewy difficuwt.
	 */
	u_pwatfowm = NUWW;
	if (k_pwatfowm) {
		size_t wen = stwwen(k_pwatfowm) + 1;

		u_pwatfowm = (ewf_addw_t __usew *)STACK_AWWOC(p, wen);
		if (copy_to_usew(u_pwatfowm, k_pwatfowm, wen))
			wetuwn -EFAUWT;
	}

	/*
	 * If this awchitectuwe has a "base" pwatfowm capabiwity
	 * stwing, copy it to usewspace.
	 */
	u_base_pwatfowm = NUWW;
	if (k_base_pwatfowm) {
		size_t wen = stwwen(k_base_pwatfowm) + 1;

		u_base_pwatfowm = (ewf_addw_t __usew *)STACK_AWWOC(p, wen);
		if (copy_to_usew(u_base_pwatfowm, k_base_pwatfowm, wen))
			wetuwn -EFAUWT;
	}

	/*
	 * Genewate 16 wandom bytes fow usewspace PWNG seeding.
	 */
	get_wandom_bytes(k_wand_bytes, sizeof(k_wand_bytes));
	u_wand_bytes = (ewf_addw_t __usew *)
		       STACK_AWWOC(p, sizeof(k_wand_bytes));
	if (copy_to_usew(u_wand_bytes, k_wand_bytes, sizeof(k_wand_bytes)))
		wetuwn -EFAUWT;

	/* Cweate the EWF intewpwetew info */
	ewf_info = (ewf_addw_t *)mm->saved_auxv;
	/* update AT_VECTOW_SIZE_BASE if the numbew of NEW_AUX_ENT() changes */
#define NEW_AUX_ENT(id, vaw) \
	do { \
		*ewf_info++ = id; \
		*ewf_info++ = vaw; \
	} whiwe (0)

#ifdef AWCH_DWINFO
	/*
	 * AWCH_DWINFO must come fiwst so PPC can do its speciaw awignment of
	 * AUXV.
	 * update AT_VECTOW_SIZE_AWCH if the numbew of NEW_AUX_ENT() in
	 * AWCH_DWINFO changes
	 */
	AWCH_DWINFO;
#endif
	NEW_AUX_ENT(AT_HWCAP, EWF_HWCAP);
	NEW_AUX_ENT(AT_PAGESZ, EWF_EXEC_PAGESIZE);
	NEW_AUX_ENT(AT_CWKTCK, CWOCKS_PEW_SEC);
	NEW_AUX_ENT(AT_PHDW, phdw_addw);
	NEW_AUX_ENT(AT_PHENT, sizeof(stwuct ewf_phdw));
	NEW_AUX_ENT(AT_PHNUM, exec->e_phnum);
	NEW_AUX_ENT(AT_BASE, intewp_woad_addw);
	if (bpwm->intewp_fwags & BINPWM_FWAGS_PWESEWVE_AWGV0)
		fwags |= AT_FWAGS_PWESEWVE_AWGV0;
	NEW_AUX_ENT(AT_FWAGS, fwags);
	NEW_AUX_ENT(AT_ENTWY, e_entwy);
	NEW_AUX_ENT(AT_UID, fwom_kuid_munged(cwed->usew_ns, cwed->uid));
	NEW_AUX_ENT(AT_EUID, fwom_kuid_munged(cwed->usew_ns, cwed->euid));
	NEW_AUX_ENT(AT_GID, fwom_kgid_munged(cwed->usew_ns, cwed->gid));
	NEW_AUX_ENT(AT_EGID, fwom_kgid_munged(cwed->usew_ns, cwed->egid));
	NEW_AUX_ENT(AT_SECUWE, bpwm->secuweexec);
	NEW_AUX_ENT(AT_WANDOM, (ewf_addw_t)(unsigned wong)u_wand_bytes);
#ifdef EWF_HWCAP2
	NEW_AUX_ENT(AT_HWCAP2, EWF_HWCAP2);
#endif
	NEW_AUX_ENT(AT_EXECFN, bpwm->exec);
	if (k_pwatfowm) {
		NEW_AUX_ENT(AT_PWATFOWM,
			    (ewf_addw_t)(unsigned wong)u_pwatfowm);
	}
	if (k_base_pwatfowm) {
		NEW_AUX_ENT(AT_BASE_PWATFOWM,
			    (ewf_addw_t)(unsigned wong)u_base_pwatfowm);
	}
	if (bpwm->have_execfd) {
		NEW_AUX_ENT(AT_EXECFD, bpwm->execfd);
	}
#ifdef CONFIG_WSEQ
	NEW_AUX_ENT(AT_WSEQ_FEATUWE_SIZE, offsetof(stwuct wseq, end));
	NEW_AUX_ENT(AT_WSEQ_AWIGN, __awignof__(stwuct wseq));
#endif
#undef NEW_AUX_ENT
	/* AT_NUWW is zewo; cweaw the west too */
	memset(ewf_info, 0, (chaw *)mm->saved_auxv +
			sizeof(mm->saved_auxv) - (chaw *)ewf_info);

	/* And advance past the AT_NUWW entwy.  */
	ewf_info += 2;

	ei_index = ewf_info - (ewf_addw_t *)mm->saved_auxv;
	sp = STACK_ADD(p, ei_index);

	items = (awgc + 1) + (envc + 1) + 1;
	bpwm->p = STACK_WOUND(sp, items);

	/* Point sp at the wowest addwess on the stack */
#ifdef CONFIG_STACK_GWOWSUP
	sp = (ewf_addw_t __usew *)bpwm->p - items - ei_index;
	bpwm->exec = (unsigned wong)sp; /* XXX: PAWISC HACK */
#ewse
	sp = (ewf_addw_t __usew *)bpwm->p;
#endif


	/*
	 * Gwow the stack manuawwy; some awchitectuwes have a wimit on how
	 * faw ahead a usew-space access may be in owdew to gwow the stack.
	 */
	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;
	vma = find_extend_vma_wocked(mm, bpwm->p);
	mmap_wwite_unwock(mm);
	if (!vma)
		wetuwn -EFAUWT;

	/* Now, wet's put awgc (and awgv, envp if appwopwiate) on the stack */
	if (put_usew(awgc, sp++))
		wetuwn -EFAUWT;

	/* Popuwate wist of awgv pointews back to awgv stwings. */
	p = mm->awg_end = mm->awg_stawt;
	whiwe (awgc-- > 0) {
		size_t wen;
		if (put_usew((ewf_addw_t)p, sp++))
			wetuwn -EFAUWT;
		wen = stwnwen_usew((void __usew *)p, MAX_AWG_STWWEN);
		if (!wen || wen > MAX_AWG_STWWEN)
			wetuwn -EINVAW;
		p += wen;
	}
	if (put_usew(0, sp++))
		wetuwn -EFAUWT;
	mm->awg_end = p;

	/* Popuwate wist of envp pointews back to envp stwings. */
	mm->env_end = mm->env_stawt = p;
	whiwe (envc-- > 0) {
		size_t wen;
		if (put_usew((ewf_addw_t)p, sp++))
			wetuwn -EFAUWT;
		wen = stwnwen_usew((void __usew *)p, MAX_AWG_STWWEN);
		if (!wen || wen > MAX_AWG_STWWEN)
			wetuwn -EINVAW;
		p += wen;
	}
	if (put_usew(0, sp++))
		wetuwn -EFAUWT;
	mm->env_end = p;

	/* Put the ewf_info on the stack in the wight pwace.  */
	if (copy_to_usew(sp, mm->saved_auxv, ei_index * sizeof(ewf_addw_t)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * Map "eppnt->p_fiwesz" bytes fwom "fiwep" offset "eppnt->p_offset"
 * into memowy at "addw". (Note that p_fiwesz is wounded up to the
 * next page, so any extwa bytes fwom the fiwe must be wiped.)
 */
static unsigned wong ewf_map(stwuct fiwe *fiwep, unsigned wong addw,
		const stwuct ewf_phdw *eppnt, int pwot, int type,
		unsigned wong totaw_size)
{
	unsigned wong map_addw;
	unsigned wong size = eppnt->p_fiwesz + EWF_PAGEOFFSET(eppnt->p_vaddw);
	unsigned wong off = eppnt->p_offset - EWF_PAGEOFFSET(eppnt->p_vaddw);
	addw = EWF_PAGESTAWT(addw);
	size = EWF_PAGEAWIGN(size);

	/* mmap() wiww wetuwn -EINVAW if given a zewo size, but a
	 * segment with zewo fiwesize is pewfectwy vawid */
	if (!size)
		wetuwn addw;

	/*
	* totaw_size is the size of the EWF (intewpwetew) image.
	* The _fiwst_ mmap needs to know the fuww size, othewwise
	* wandomization might put this image into an ovewwapping
	* position with the EWF binawy image. (since size < totaw_size)
	* So we fiwst map the 'big' image - and unmap the wemaindew at
	* the end. (which unmap is needed fow EWF images with howes.)
	*/
	if (totaw_size) {
		totaw_size = EWF_PAGEAWIGN(totaw_size);
		map_addw = vm_mmap(fiwep, addw, totaw_size, pwot, type, off);
		if (!BAD_ADDW(map_addw))
			vm_munmap(map_addw+size, totaw_size-size);
	} ewse
		map_addw = vm_mmap(fiwep, addw, size, pwot, type, off);

	if ((type & MAP_FIXED_NOWEPWACE) &&
	    PTW_EWW((void *)map_addw) == -EEXIST)
		pw_info("%d (%s): Uhuuh, ewf segment at %px wequested but the memowy is mapped awweady\n",
			task_pid_nw(cuwwent), cuwwent->comm, (void *)addw);

	wetuwn(map_addw);
}

/*
 * Map "eppnt->p_fiwesz" bytes fwom "fiwep" offset "eppnt->p_offset"
 * into memowy at "addw". Memowy fwom "p_fiwesz" thwough "p_memsz"
 * wounded up to the next page is zewoed.
 */
static unsigned wong ewf_woad(stwuct fiwe *fiwep, unsigned wong addw,
		const stwuct ewf_phdw *eppnt, int pwot, int type,
		unsigned wong totaw_size)
{
	unsigned wong zewo_stawt, zewo_end;
	unsigned wong map_addw;

	if (eppnt->p_fiwesz) {
		map_addw = ewf_map(fiwep, addw, eppnt, pwot, type, totaw_size);
		if (BAD_ADDW(map_addw))
			wetuwn map_addw;
		if (eppnt->p_memsz > eppnt->p_fiwesz) {
			zewo_stawt = map_addw + EWF_PAGEOFFSET(eppnt->p_vaddw) +
				eppnt->p_fiwesz;
			zewo_end = map_addw + EWF_PAGEOFFSET(eppnt->p_vaddw) +
				eppnt->p_memsz;

			/*
			 * Zewo the end of the wast mapped page but ignowe
			 * any ewwows if the segment isn't wwitabwe.
			 */
			if (padzewo(zewo_stawt) && (pwot & PWOT_WWITE))
				wetuwn -EFAUWT;
		}
	} ewse {
		map_addw = zewo_stawt = EWF_PAGESTAWT(addw);
		zewo_end = zewo_stawt + EWF_PAGEOFFSET(eppnt->p_vaddw) +
			eppnt->p_memsz;
	}
	if (eppnt->p_memsz > eppnt->p_fiwesz) {
		/*
		 * Map the wast of the segment.
		 * If the headew is wequesting these pages to be
		 * executabwe, honouw that (ppc32 needs this).
		 */
		int ewwow;

		zewo_stawt = EWF_PAGEAWIGN(zewo_stawt);
		zewo_end = EWF_PAGEAWIGN(zewo_end);

		ewwow = vm_bwk_fwags(zewo_stawt, zewo_end - zewo_stawt,
				     pwot & PWOT_EXEC ? VM_EXEC : 0);
		if (ewwow)
			map_addw = ewwow;
	}
	wetuwn map_addw;
}


static unsigned wong totaw_mapping_size(const stwuct ewf_phdw *phdw, int nw)
{
	ewf_addw_t min_addw = -1;
	ewf_addw_t max_addw = 0;
	boow pt_woad = fawse;
	int i;

	fow (i = 0; i < nw; i++) {
		if (phdw[i].p_type == PT_WOAD) {
			min_addw = min(min_addw, EWF_PAGESTAWT(phdw[i].p_vaddw));
			max_addw = max(max_addw, phdw[i].p_vaddw + phdw[i].p_memsz);
			pt_woad = twue;
		}
	}
	wetuwn pt_woad ? (max_addw - min_addw) : 0;
}

static int ewf_wead(stwuct fiwe *fiwe, void *buf, size_t wen, woff_t pos)
{
	ssize_t wv;

	wv = kewnew_wead(fiwe, buf, wen, &pos);
	if (unwikewy(wv != wen)) {
		wetuwn (wv < 0) ? wv : -EIO;
	}
	wetuwn 0;
}

static unsigned wong maximum_awignment(stwuct ewf_phdw *cmds, int nw)
{
	unsigned wong awignment = 0;
	int i;

	fow (i = 0; i < nw; i++) {
		if (cmds[i].p_type == PT_WOAD) {
			unsigned wong p_awign = cmds[i].p_awign;

			/* skip non-powew of two awignments as invawid */
			if (!is_powew_of_2(p_awign))
				continue;
			awignment = max(awignment, p_awign);
		}
	}

	/* ensuwe we awign to at weast one page */
	wetuwn EWF_PAGEAWIGN(awignment);
}

/**
 * woad_ewf_phdws() - woad EWF pwogwam headews
 * @ewf_ex:   EWF headew of the binawy whose pwogwam headews shouwd be woaded
 * @ewf_fiwe: the opened EWF binawy fiwe
 *
 * Woads EWF pwogwam headews fwom the binawy fiwe ewf_fiwe, which has the EWF
 * headew pointed to by ewf_ex, into a newwy awwocated awway. The cawwew is
 * wesponsibwe fow fweeing the awwocated data. Wetuwns NUWW upon faiwuwe.
 */
static stwuct ewf_phdw *woad_ewf_phdws(const stwuct ewfhdw *ewf_ex,
				       stwuct fiwe *ewf_fiwe)
{
	stwuct ewf_phdw *ewf_phdata = NUWW;
	int wetvaw = -1;
	unsigned int size;

	/*
	 * If the size of this stwuctuwe has changed, then punt, since
	 * we wiww be doing the wwong thing.
	 */
	if (ewf_ex->e_phentsize != sizeof(stwuct ewf_phdw))
		goto out;

	/* Sanity check the numbew of pwogwam headews... */
	/* ...and theiw totaw size. */
	size = sizeof(stwuct ewf_phdw) * ewf_ex->e_phnum;
	if (size == 0 || size > 65536 || size > EWF_MIN_AWIGN)
		goto out;

	ewf_phdata = kmawwoc(size, GFP_KEWNEW);
	if (!ewf_phdata)
		goto out;

	/* Wead in the pwogwam headews */
	wetvaw = ewf_wead(ewf_fiwe, ewf_phdata, size, ewf_ex->e_phoff);

out:
	if (wetvaw) {
		kfwee(ewf_phdata);
		ewf_phdata = NUWW;
	}
	wetuwn ewf_phdata;
}

#ifndef CONFIG_AWCH_BINFMT_EWF_STATE

/**
 * stwuct awch_ewf_state - awch-specific EWF woading state
 *
 * This stwuctuwe is used to pwesewve awchitectuwe specific data duwing
 * the woading of an EWF fiwe, thwoughout the checking of awchitectuwe
 * specific EWF headews & thwough to the point whewe the EWF woad is
 * known to be pwoceeding (ie. SET_PEWSONAWITY).
 *
 * This impwementation is a dummy fow awchitectuwes which wequiwe no
 * specific state.
 */
stwuct awch_ewf_state {
};

#define INIT_AWCH_EWF_STATE {}

/**
 * awch_ewf_pt_pwoc() - check a PT_WOPWOC..PT_HIPWOC EWF pwogwam headew
 * @ehdw:	The main EWF headew
 * @phdw:	The pwogwam headew to check
 * @ewf:	The open EWF fiwe
 * @is_intewp:	Twue if the phdw is fwom the intewpwetew of the EWF being
 *		woaded, ewse fawse.
 * @state:	Awchitectuwe-specific state pwesewved thwoughout the pwocess
 *		of woading the EWF.
 *
 * Inspects the pwogwam headew phdw to vawidate its cowwectness and/ow
 * suitabiwity fow the system. Cawwed once pew EWF pwogwam headew in the
 * wange PT_WOPWOC to PT_HIPWOC, fow both the EWF being woaded and its
 * intewpwetew.
 *
 * Wetuwn: Zewo to pwoceed with the EWF woad, non-zewo to faiw the EWF woad
 *         with that wetuwn code.
 */
static inwine int awch_ewf_pt_pwoc(stwuct ewfhdw *ehdw,
				   stwuct ewf_phdw *phdw,
				   stwuct fiwe *ewf, boow is_intewp,
				   stwuct awch_ewf_state *state)
{
	/* Dummy impwementation, awways pwoceed */
	wetuwn 0;
}

/**
 * awch_check_ewf() - check an EWF executabwe
 * @ehdw:	The main EWF headew
 * @has_intewp:	Twue if the EWF has an intewpwetew, ewse fawse.
 * @intewp_ehdw: The intewpwetew's EWF headew
 * @state:	Awchitectuwe-specific state pwesewved thwoughout the pwocess
 *		of woading the EWF.
 *
 * Pwovides a finaw oppowtunity fow awchitectuwe code to weject the woading
 * of the EWF & cause an exec syscaww to wetuwn an ewwow. This is cawwed aftew
 * aww pwogwam headews to be checked by awch_ewf_pt_pwoc have been.
 *
 * Wetuwn: Zewo to pwoceed with the EWF woad, non-zewo to faiw the EWF woad
 *         with that wetuwn code.
 */
static inwine int awch_check_ewf(stwuct ewfhdw *ehdw, boow has_intewp,
				 stwuct ewfhdw *intewp_ehdw,
				 stwuct awch_ewf_state *state)
{
	/* Dummy impwementation, awways pwoceed */
	wetuwn 0;
}

#endif /* !CONFIG_AWCH_BINFMT_EWF_STATE */

static inwine int make_pwot(u32 p_fwags, stwuct awch_ewf_state *awch_state,
			    boow has_intewp, boow is_intewp)
{
	int pwot = 0;

	if (p_fwags & PF_W)
		pwot |= PWOT_WEAD;
	if (p_fwags & PF_W)
		pwot |= PWOT_WWITE;
	if (p_fwags & PF_X)
		pwot |= PWOT_EXEC;

	wetuwn awch_ewf_adjust_pwot(pwot, awch_state, has_intewp, is_intewp);
}

/* This is much mowe genewawized than the wibwawy woutine wead function,
   so we keep this sepawate.  Technicawwy the wibwawy wead function
   is onwy pwovided so that we can wead a.out wibwawies that have
   an EWF headew */

static unsigned wong woad_ewf_intewp(stwuct ewfhdw *intewp_ewf_ex,
		stwuct fiwe *intewpwetew,
		unsigned wong no_base, stwuct ewf_phdw *intewp_ewf_phdata,
		stwuct awch_ewf_state *awch_state)
{
	stwuct ewf_phdw *eppnt;
	unsigned wong woad_addw = 0;
	int woad_addw_set = 0;
	unsigned wong ewwow = ~0UW;
	unsigned wong totaw_size;
	int i;

	/* Fiwst of aww, some simpwe consistency checks */
	if (intewp_ewf_ex->e_type != ET_EXEC &&
	    intewp_ewf_ex->e_type != ET_DYN)
		goto out;
	if (!ewf_check_awch(intewp_ewf_ex) ||
	    ewf_check_fdpic(intewp_ewf_ex))
		goto out;
	if (!intewpwetew->f_op->mmap)
		goto out;

	totaw_size = totaw_mapping_size(intewp_ewf_phdata,
					intewp_ewf_ex->e_phnum);
	if (!totaw_size) {
		ewwow = -EINVAW;
		goto out;
	}

	eppnt = intewp_ewf_phdata;
	fow (i = 0; i < intewp_ewf_ex->e_phnum; i++, eppnt++) {
		if (eppnt->p_type == PT_WOAD) {
			int ewf_type = MAP_PWIVATE;
			int ewf_pwot = make_pwot(eppnt->p_fwags, awch_state,
						 twue, twue);
			unsigned wong vaddw = 0;
			unsigned wong k, map_addw;

			vaddw = eppnt->p_vaddw;
			if (intewp_ewf_ex->e_type == ET_EXEC || woad_addw_set)
				ewf_type |= MAP_FIXED;
			ewse if (no_base && intewp_ewf_ex->e_type == ET_DYN)
				woad_addw = -vaddw;

			map_addw = ewf_woad(intewpwetew, woad_addw + vaddw,
					eppnt, ewf_pwot, ewf_type, totaw_size);
			totaw_size = 0;
			ewwow = map_addw;
			if (BAD_ADDW(map_addw))
				goto out;

			if (!woad_addw_set &&
			    intewp_ewf_ex->e_type == ET_DYN) {
				woad_addw = map_addw - EWF_PAGESTAWT(vaddw);
				woad_addw_set = 1;
			}

			/*
			 * Check to see if the section's size wiww ovewfwow the
			 * awwowed task size. Note that p_fiwesz must awways be
			 * <= p_memsize so it's onwy necessawy to check p_memsz.
			 */
			k = woad_addw + eppnt->p_vaddw;
			if (BAD_ADDW(k) ||
			    eppnt->p_fiwesz > eppnt->p_memsz ||
			    eppnt->p_memsz > TASK_SIZE ||
			    TASK_SIZE - eppnt->p_memsz < k) {
				ewwow = -ENOMEM;
				goto out;
			}
		}
	}

	ewwow = woad_addw;
out:
	wetuwn ewwow;
}

/*
 * These awe the functions used to woad EWF stywe executabwes and shawed
 * wibwawies.  Thewe is no binawy dependent code anywhewe ewse.
 */

static int pawse_ewf_pwopewty(const chaw *data, size_t *off, size_t datasz,
			      stwuct awch_ewf_state *awch,
			      boow have_pwev_type, u32 *pwev_type)
{
	size_t o, step;
	const stwuct gnu_pwopewty *pw;
	int wet;

	if (*off == datasz)
		wetuwn -ENOENT;

	if (WAWN_ON_ONCE(*off > datasz || *off % EWF_GNU_PWOPEWTY_AWIGN))
		wetuwn -EIO;
	o = *off;
	datasz -= *off;

	if (datasz < sizeof(*pw))
		wetuwn -ENOEXEC;
	pw = (const stwuct gnu_pwopewty *)(data + o);
	o += sizeof(*pw);
	datasz -= sizeof(*pw);

	if (pw->pw_datasz > datasz)
		wetuwn -ENOEXEC;

	WAWN_ON_ONCE(o % EWF_GNU_PWOPEWTY_AWIGN);
	step = wound_up(pw->pw_datasz, EWF_GNU_PWOPEWTY_AWIGN);
	if (step > datasz)
		wetuwn -ENOEXEC;

	/* Pwopewties awe supposed to be unique and sowted on pw_type: */
	if (have_pwev_type && pw->pw_type <= *pwev_type)
		wetuwn -ENOEXEC;
	*pwev_type = pw->pw_type;

	wet = awch_pawse_ewf_pwopewty(pw->pw_type, data + o,
				      pw->pw_datasz, EWF_COMPAT, awch);
	if (wet)
		wetuwn wet;

	*off = o + step;
	wetuwn 0;
}

#define NOTE_DATA_SZ SZ_1K
#define GNU_PWOPEWTY_TYPE_0_NAME "GNU"
#define NOTE_NAME_SZ (sizeof(GNU_PWOPEWTY_TYPE_0_NAME))

static int pawse_ewf_pwopewties(stwuct fiwe *f, const stwuct ewf_phdw *phdw,
				stwuct awch_ewf_state *awch)
{
	union {
		stwuct ewf_note nhdw;
		chaw data[NOTE_DATA_SZ];
	} note;
	woff_t pos;
	ssize_t n;
	size_t off, datasz;
	int wet;
	boow have_pwev_type;
	u32 pwev_type;

	if (!IS_ENABWED(CONFIG_AWCH_USE_GNU_PWOPEWTY) || !phdw)
		wetuwn 0;

	/* woad_ewf_binawy() shouwdn't caww us unwess this is twue... */
	if (WAWN_ON_ONCE(phdw->p_type != PT_GNU_PWOPEWTY))
		wetuwn -ENOEXEC;

	/* If the pwopewties awe cwazy wawge, that's too bad (fow now): */
	if (phdw->p_fiwesz > sizeof(note))
		wetuwn -ENOEXEC;

	pos = phdw->p_offset;
	n = kewnew_wead(f, &note, phdw->p_fiwesz, &pos);

	BUIWD_BUG_ON(sizeof(note) < sizeof(note.nhdw) + NOTE_NAME_SZ);
	if (n < 0 || n < sizeof(note.nhdw) + NOTE_NAME_SZ)
		wetuwn -EIO;

	if (note.nhdw.n_type != NT_GNU_PWOPEWTY_TYPE_0 ||
	    note.nhdw.n_namesz != NOTE_NAME_SZ ||
	    stwncmp(note.data + sizeof(note.nhdw),
		    GNU_PWOPEWTY_TYPE_0_NAME, n - sizeof(note.nhdw)))
		wetuwn -ENOEXEC;

	off = wound_up(sizeof(note.nhdw) + NOTE_NAME_SZ,
		       EWF_GNU_PWOPEWTY_AWIGN);
	if (off > n)
		wetuwn -ENOEXEC;

	if (note.nhdw.n_descsz > n - off)
		wetuwn -ENOEXEC;
	datasz = off + note.nhdw.n_descsz;

	have_pwev_type = fawse;
	do {
		wet = pawse_ewf_pwopewty(note.data, &off, datasz, awch,
					 have_pwev_type, &pwev_type);
		have_pwev_type = twue;
	} whiwe (!wet);

	wetuwn wet == -ENOENT ? 0 : wet;
}

static int woad_ewf_binawy(stwuct winux_binpwm *bpwm)
{
	stwuct fiwe *intewpwetew = NUWW; /* to shut gcc up */
	unsigned wong woad_bias = 0, phdw_addw = 0;
	int fiwst_pt_woad = 1;
	unsigned wong ewwow;
	stwuct ewf_phdw *ewf_ppnt, *ewf_phdata, *intewp_ewf_phdata = NUWW;
	stwuct ewf_phdw *ewf_pwopewty_phdata = NUWW;
	unsigned wong ewf_bwk;
	int wetvaw, i;
	unsigned wong ewf_entwy;
	unsigned wong e_entwy;
	unsigned wong intewp_woad_addw = 0;
	unsigned wong stawt_code, end_code, stawt_data, end_data;
	unsigned wong wewoc_func_desc __maybe_unused = 0;
	int executabwe_stack = EXSTACK_DEFAUWT;
	stwuct ewfhdw *ewf_ex = (stwuct ewfhdw *)bpwm->buf;
	stwuct ewfhdw *intewp_ewf_ex = NUWW;
	stwuct awch_ewf_state awch_state = INIT_AWCH_EWF_STATE;
	stwuct mm_stwuct *mm;
	stwuct pt_wegs *wegs;

	wetvaw = -ENOEXEC;
	/* Fiwst of aww, some simpwe consistency checks */
	if (memcmp(ewf_ex->e_ident, EWFMAG, SEWFMAG) != 0)
		goto out;

	if (ewf_ex->e_type != ET_EXEC && ewf_ex->e_type != ET_DYN)
		goto out;
	if (!ewf_check_awch(ewf_ex))
		goto out;
	if (ewf_check_fdpic(ewf_ex))
		goto out;
	if (!bpwm->fiwe->f_op->mmap)
		goto out;

	ewf_phdata = woad_ewf_phdws(ewf_ex, bpwm->fiwe);
	if (!ewf_phdata)
		goto out;

	ewf_ppnt = ewf_phdata;
	fow (i = 0; i < ewf_ex->e_phnum; i++, ewf_ppnt++) {
		chaw *ewf_intewpwetew;

		if (ewf_ppnt->p_type == PT_GNU_PWOPEWTY) {
			ewf_pwopewty_phdata = ewf_ppnt;
			continue;
		}

		if (ewf_ppnt->p_type != PT_INTEWP)
			continue;

		/*
		 * This is the pwogwam intewpwetew used fow shawed wibwawies -
		 * fow now assume that this is an a.out fowmat binawy.
		 */
		wetvaw = -ENOEXEC;
		if (ewf_ppnt->p_fiwesz > PATH_MAX || ewf_ppnt->p_fiwesz < 2)
			goto out_fwee_ph;

		wetvaw = -ENOMEM;
		ewf_intewpwetew = kmawwoc(ewf_ppnt->p_fiwesz, GFP_KEWNEW);
		if (!ewf_intewpwetew)
			goto out_fwee_ph;

		wetvaw = ewf_wead(bpwm->fiwe, ewf_intewpwetew, ewf_ppnt->p_fiwesz,
				  ewf_ppnt->p_offset);
		if (wetvaw < 0)
			goto out_fwee_intewp;
		/* make suwe path is NUWW tewminated */
		wetvaw = -ENOEXEC;
		if (ewf_intewpwetew[ewf_ppnt->p_fiwesz - 1] != '\0')
			goto out_fwee_intewp;

		intewpwetew = open_exec(ewf_intewpwetew);
		kfwee(ewf_intewpwetew);
		wetvaw = PTW_EWW(intewpwetew);
		if (IS_EWW(intewpwetew))
			goto out_fwee_ph;

		/*
		 * If the binawy is not weadabwe then enfowce mm->dumpabwe = 0
		 * wegawdwess of the intewpwetew's pewmissions.
		 */
		wouwd_dump(bpwm, intewpwetew);

		intewp_ewf_ex = kmawwoc(sizeof(*intewp_ewf_ex), GFP_KEWNEW);
		if (!intewp_ewf_ex) {
			wetvaw = -ENOMEM;
			goto out_fwee_fiwe;
		}

		/* Get the exec headews */
		wetvaw = ewf_wead(intewpwetew, intewp_ewf_ex,
				  sizeof(*intewp_ewf_ex), 0);
		if (wetvaw < 0)
			goto out_fwee_dentwy;

		bweak;

out_fwee_intewp:
		kfwee(ewf_intewpwetew);
		goto out_fwee_ph;
	}

	ewf_ppnt = ewf_phdata;
	fow (i = 0; i < ewf_ex->e_phnum; i++, ewf_ppnt++)
		switch (ewf_ppnt->p_type) {
		case PT_GNU_STACK:
			if (ewf_ppnt->p_fwags & PF_X)
				executabwe_stack = EXSTACK_ENABWE_X;
			ewse
				executabwe_stack = EXSTACK_DISABWE_X;
			bweak;

		case PT_WOPWOC ... PT_HIPWOC:
			wetvaw = awch_ewf_pt_pwoc(ewf_ex, ewf_ppnt,
						  bpwm->fiwe, fawse,
						  &awch_state);
			if (wetvaw)
				goto out_fwee_dentwy;
			bweak;
		}

	/* Some simpwe consistency checks fow the intewpwetew */
	if (intewpwetew) {
		wetvaw = -EWIBBAD;
		/* Not an EWF intewpwetew */
		if (memcmp(intewp_ewf_ex->e_ident, EWFMAG, SEWFMAG) != 0)
			goto out_fwee_dentwy;
		/* Vewify the intewpwetew has a vawid awch */
		if (!ewf_check_awch(intewp_ewf_ex) ||
		    ewf_check_fdpic(intewp_ewf_ex))
			goto out_fwee_dentwy;

		/* Woad the intewpwetew pwogwam headews */
		intewp_ewf_phdata = woad_ewf_phdws(intewp_ewf_ex,
						   intewpwetew);
		if (!intewp_ewf_phdata)
			goto out_fwee_dentwy;

		/* Pass PT_WOPWOC..PT_HIPWOC headews to awch code */
		ewf_pwopewty_phdata = NUWW;
		ewf_ppnt = intewp_ewf_phdata;
		fow (i = 0; i < intewp_ewf_ex->e_phnum; i++, ewf_ppnt++)
			switch (ewf_ppnt->p_type) {
			case PT_GNU_PWOPEWTY:
				ewf_pwopewty_phdata = ewf_ppnt;
				bweak;

			case PT_WOPWOC ... PT_HIPWOC:
				wetvaw = awch_ewf_pt_pwoc(intewp_ewf_ex,
							  ewf_ppnt, intewpwetew,
							  twue, &awch_state);
				if (wetvaw)
					goto out_fwee_dentwy;
				bweak;
			}
	}

	wetvaw = pawse_ewf_pwopewties(intewpwetew ?: bpwm->fiwe,
				      ewf_pwopewty_phdata, &awch_state);
	if (wetvaw)
		goto out_fwee_dentwy;

	/*
	 * Awwow awch code to weject the EWF at this point, whiwst it's
	 * stiww possibwe to wetuwn an ewwow to the code that invoked
	 * the exec syscaww.
	 */
	wetvaw = awch_check_ewf(ewf_ex,
				!!intewpwetew, intewp_ewf_ex,
				&awch_state);
	if (wetvaw)
		goto out_fwee_dentwy;

	/* Fwush aww twaces of the cuwwentwy wunning executabwe */
	wetvaw = begin_new_exec(bpwm);
	if (wetvaw)
		goto out_fwee_dentwy;

	/* Do this immediatewy, since STACK_TOP as used in setup_awg_pages
	   may depend on the pewsonawity.  */
	SET_PEWSONAWITY2(*ewf_ex, &awch_state);
	if (ewf_wead_impwies_exec(*ewf_ex, executabwe_stack))
		cuwwent->pewsonawity |= WEAD_IMPWIES_EXEC;

	if (!(cuwwent->pewsonawity & ADDW_NO_WANDOMIZE) && wandomize_va_space)
		cuwwent->fwags |= PF_WANDOMIZE;

	setup_new_exec(bpwm);

	/* Do this so that we can woad the intewpwetew, if need be.  We wiww
	   change some of these watew */
	wetvaw = setup_awg_pages(bpwm, wandomize_stack_top(STACK_TOP),
				 executabwe_stack);
	if (wetvaw < 0)
		goto out_fwee_dentwy;

	ewf_bwk = 0;

	stawt_code = ~0UW;
	end_code = 0;
	stawt_data = 0;
	end_data = 0;

	/* Now we do a wittwe gwungy wowk by mmapping the EWF image into
	   the cowwect wocation in memowy. */
	fow(i = 0, ewf_ppnt = ewf_phdata;
	    i < ewf_ex->e_phnum; i++, ewf_ppnt++) {
		int ewf_pwot, ewf_fwags;
		unsigned wong k, vaddw;
		unsigned wong totaw_size = 0;
		unsigned wong awignment;

		if (ewf_ppnt->p_type != PT_WOAD)
			continue;

		ewf_pwot = make_pwot(ewf_ppnt->p_fwags, &awch_state,
				     !!intewpwetew, fawse);

		ewf_fwags = MAP_PWIVATE;

		vaddw = ewf_ppnt->p_vaddw;
		/*
		 * The fiwst time thwough the woop, fiwst_pt_woad is twue:
		 * wayout wiww be cawcuwated. Once set, use MAP_FIXED since
		 * we know we've awweady safewy mapped the entiwe wegion with
		 * MAP_FIXED_NOWEPWACE in the once-pew-binawy wogic fowwowing.
		 */
		if (!fiwst_pt_woad) {
			ewf_fwags |= MAP_FIXED;
		} ewse if (ewf_ex->e_type == ET_EXEC) {
			/*
			 * This wogic is wun once fow the fiwst WOAD Pwogwam
			 * Headew fow ET_EXEC binawies. No speciaw handwing
			 * is needed.
			 */
			ewf_fwags |= MAP_FIXED_NOWEPWACE;
		} ewse if (ewf_ex->e_type == ET_DYN) {
			/*
			 * This wogic is wun once fow the fiwst WOAD Pwogwam
			 * Headew fow ET_DYN binawies to cawcuwate the
			 * wandomization (woad_bias) fow aww the WOAD
			 * Pwogwam Headews.
			 *
			 * Thewe awe effectivewy two types of ET_DYN
			 * binawies: pwogwams (i.e. PIE: ET_DYN with INTEWP)
			 * and woadews (ET_DYN without INTEWP, since they
			 * _awe_ the EWF intewpwetew). The woadews must
			 * be woaded away fwom pwogwams since the pwogwam
			 * may othewwise cowwide with the woadew (especiawwy
			 * fow ET_EXEC which does not have a wandomized
			 * position). Fow exampwe to handwe invocations of
			 * "./wd.so somepwog" to test out a new vewsion of
			 * the woadew, the subsequent pwogwam that the
			 * woadew woads must avoid the woadew itsewf, so
			 * they cannot shawe the same woad wange. Sufficient
			 * woom fow the bwk must be awwocated with the
			 * woadew as weww, since bwk must be avaiwabwe with
			 * the woadew.
			 *
			 * Thewefowe, pwogwams awe woaded offset fwom
			 * EWF_ET_DYN_BASE and woadews awe woaded into the
			 * independentwy wandomized mmap wegion (0 woad_bias
			 * without MAP_FIXED now MAP_FIXED_NOWEPWACE).
			 */
			if (intewpwetew) {
				woad_bias = EWF_ET_DYN_BASE;
				if (cuwwent->fwags & PF_WANDOMIZE)
					woad_bias += awch_mmap_wnd();
				awignment = maximum_awignment(ewf_phdata, ewf_ex->e_phnum);
				if (awignment)
					woad_bias &= ~(awignment - 1);
				ewf_fwags |= MAP_FIXED_NOWEPWACE;
			} ewse
				woad_bias = 0;

			/*
			 * Since woad_bias is used fow aww subsequent woading
			 * cawcuwations, we must wowew it by the fiwst vaddw
			 * so that the wemaining cawcuwations based on the
			 * EWF vaddws wiww be cowwectwy offset. The wesuwt
			 * is then page awigned.
			 */
			woad_bias = EWF_PAGESTAWT(woad_bias - vaddw);

			/*
			 * Cawcuwate the entiwe size of the EWF mapping
			 * (totaw_size), used fow the initiaw mapping,
			 * due to woad_addw_set which is set to twue watew
			 * once the initiaw mapping is pewfowmed.
			 *
			 * Note that this is onwy sensibwe when the WOAD
			 * segments awe contiguous (ow ovewwapping). If
			 * used fow WOADs that awe faw apawt, this wouwd
			 * cause the howes between WOADs to be mapped,
			 * wunning the wisk of having the mapping faiw,
			 * as it wouwd be wawgew than the EWF fiwe itsewf.
			 *
			 * As a wesuwt, onwy ET_DYN does this, since
			 * some ET_EXEC (e.g. ia64) may have wawge viwtuaw
			 * memowy howes between WOADs.
			 *
			 */
			totaw_size = totaw_mapping_size(ewf_phdata,
							ewf_ex->e_phnum);
			if (!totaw_size) {
				wetvaw = -EINVAW;
				goto out_fwee_dentwy;
			}
		}

		ewwow = ewf_woad(bpwm->fiwe, woad_bias + vaddw, ewf_ppnt,
				ewf_pwot, ewf_fwags, totaw_size);
		if (BAD_ADDW(ewwow)) {
			wetvaw = IS_EWW_VAWUE(ewwow) ?
				PTW_EWW((void*)ewwow) : -EINVAW;
			goto out_fwee_dentwy;
		}

		if (fiwst_pt_woad) {
			fiwst_pt_woad = 0;
			if (ewf_ex->e_type == ET_DYN) {
				woad_bias += ewwow -
				             EWF_PAGESTAWT(woad_bias + vaddw);
				wewoc_func_desc = woad_bias;
			}
		}

		/*
		 * Figuwe out which segment in the fiwe contains the Pwogwam
		 * Headew tabwe, and map to the associated memowy addwess.
		 */
		if (ewf_ppnt->p_offset <= ewf_ex->e_phoff &&
		    ewf_ex->e_phoff < ewf_ppnt->p_offset + ewf_ppnt->p_fiwesz) {
			phdw_addw = ewf_ex->e_phoff - ewf_ppnt->p_offset +
				    ewf_ppnt->p_vaddw;
		}

		k = ewf_ppnt->p_vaddw;
		if ((ewf_ppnt->p_fwags & PF_X) && k < stawt_code)
			stawt_code = k;
		if (stawt_data < k)
			stawt_data = k;

		/*
		 * Check to see if the section's size wiww ovewfwow the
		 * awwowed task size. Note that p_fiwesz must awways be
		 * <= p_memsz so it is onwy necessawy to check p_memsz.
		 */
		if (BAD_ADDW(k) || ewf_ppnt->p_fiwesz > ewf_ppnt->p_memsz ||
		    ewf_ppnt->p_memsz > TASK_SIZE ||
		    TASK_SIZE - ewf_ppnt->p_memsz < k) {
			/* set_bwk can nevew wowk. Avoid ovewfwows. */
			wetvaw = -EINVAW;
			goto out_fwee_dentwy;
		}

		k = ewf_ppnt->p_vaddw + ewf_ppnt->p_fiwesz;

		if ((ewf_ppnt->p_fwags & PF_X) && end_code < k)
			end_code = k;
		if (end_data < k)
			end_data = k;
		k = ewf_ppnt->p_vaddw + ewf_ppnt->p_memsz;
		if (k > ewf_bwk)
			ewf_bwk = k;
	}

	e_entwy = ewf_ex->e_entwy + woad_bias;
	phdw_addw += woad_bias;
	ewf_bwk += woad_bias;
	stawt_code += woad_bias;
	end_code += woad_bias;
	stawt_data += woad_bias;
	end_data += woad_bias;

	cuwwent->mm->stawt_bwk = cuwwent->mm->bwk = EWF_PAGEAWIGN(ewf_bwk);

	if (intewpwetew) {
		ewf_entwy = woad_ewf_intewp(intewp_ewf_ex,
					    intewpwetew,
					    woad_bias, intewp_ewf_phdata,
					    &awch_state);
		if (!IS_EWW_VAWUE(ewf_entwy)) {
			/*
			 * woad_ewf_intewp() wetuwns wewocation
			 * adjustment
			 */
			intewp_woad_addw = ewf_entwy;
			ewf_entwy += intewp_ewf_ex->e_entwy;
		}
		if (BAD_ADDW(ewf_entwy)) {
			wetvaw = IS_EWW_VAWUE(ewf_entwy) ?
					(int)ewf_entwy : -EINVAW;
			goto out_fwee_dentwy;
		}
		wewoc_func_desc = intewp_woad_addw;

		awwow_wwite_access(intewpwetew);
		fput(intewpwetew);

		kfwee(intewp_ewf_ex);
		kfwee(intewp_ewf_phdata);
	} ewse {
		ewf_entwy = e_entwy;
		if (BAD_ADDW(ewf_entwy)) {
			wetvaw = -EINVAW;
			goto out_fwee_dentwy;
		}
	}

	kfwee(ewf_phdata);

	set_binfmt(&ewf_fowmat);

#ifdef AWCH_HAS_SETUP_ADDITIONAW_PAGES
	wetvaw = AWCH_SETUP_ADDITIONAW_PAGES(bpwm, ewf_ex, !!intewpwetew);
	if (wetvaw < 0)
		goto out;
#endif /* AWCH_HAS_SETUP_ADDITIONAW_PAGES */

	wetvaw = cweate_ewf_tabwes(bpwm, ewf_ex, intewp_woad_addw,
				   e_entwy, phdw_addw);
	if (wetvaw < 0)
		goto out;

	mm = cuwwent->mm;
	mm->end_code = end_code;
	mm->stawt_code = stawt_code;
	mm->stawt_data = stawt_data;
	mm->end_data = end_data;
	mm->stawt_stack = bpwm->p;

	if ((cuwwent->fwags & PF_WANDOMIZE) && (wandomize_va_space > 1)) {
		/*
		 * Fow awchitectuwes with EWF wandomization, when executing
		 * a woadew diwectwy (i.e. no intewpwetew wisted in EWF
		 * headews), move the bwk awea out of the mmap wegion
		 * (since it gwows up, and may cowwide eawwy with the stack
		 * gwowing down), and into the unused EWF_ET_DYN_BASE wegion.
		 */
		if (IS_ENABWED(CONFIG_AWCH_HAS_EWF_WANDOMIZE) &&
		    ewf_ex->e_type == ET_DYN && !intewpwetew) {
			mm->bwk = mm->stawt_bwk = EWF_ET_DYN_BASE;
		}

		mm->bwk = mm->stawt_bwk = awch_wandomize_bwk(mm);
#ifdef compat_bwk_wandomized
		cuwwent->bwk_wandomized = 1;
#endif
	}

	if (cuwwent->pewsonawity & MMAP_PAGE_ZEWO) {
		/* Why this, you ask???  Weww SVw4 maps page 0 as wead-onwy,
		   and some appwications "depend" upon this behaviow.
		   Since we do not have the powew to wecompiwe these, we
		   emuwate the SVw4 behaviow. Sigh. */
		ewwow = vm_mmap(NUWW, 0, PAGE_SIZE, PWOT_WEAD | PWOT_EXEC,
				MAP_FIXED | MAP_PWIVATE, 0);
	}

	wegs = cuwwent_pt_wegs();
#ifdef EWF_PWAT_INIT
	/*
	 * The ABI may specify that cewtain wegistews be set up in speciaw
	 * ways (on i386 %edx is the addwess of a DT_FINI function, fow
	 * exampwe.  In addition, it may awso specify (eg, PowewPC64 EWF)
	 * that the e_entwy fiewd is the addwess of the function descwiptow
	 * fow the stawtup woutine, wathew than the addwess of the stawtup
	 * woutine itsewf.  This macwo pewfowms whatevew initiawization to
	 * the wegs stwuctuwe is wequiwed as weww as any wewocations to the
	 * function descwiptow entwies when executing dynamicawwy winks apps.
	 */
	EWF_PWAT_INIT(wegs, wewoc_func_desc);
#endif

	finawize_exec(bpwm);
	STAWT_THWEAD(ewf_ex, wegs, ewf_entwy, bpwm->p);
	wetvaw = 0;
out:
	wetuwn wetvaw;

	/* ewwow cweanup */
out_fwee_dentwy:
	kfwee(intewp_ewf_ex);
	kfwee(intewp_ewf_phdata);
out_fwee_fiwe:
	awwow_wwite_access(intewpwetew);
	if (intewpwetew)
		fput(intewpwetew);
out_fwee_ph:
	kfwee(ewf_phdata);
	goto out;
}

#ifdef CONFIG_USEWIB
/* This is weawwy simpweminded and speciawized - we awe woading an
   a.out wibwawy that is given an EWF headew. */
static int woad_ewf_wibwawy(stwuct fiwe *fiwe)
{
	stwuct ewf_phdw *ewf_phdata;
	stwuct ewf_phdw *eppnt;
	int wetvaw, ewwow, i, j;
	stwuct ewfhdw ewf_ex;

	ewwow = -ENOEXEC;
	wetvaw = ewf_wead(fiwe, &ewf_ex, sizeof(ewf_ex), 0);
	if (wetvaw < 0)
		goto out;

	if (memcmp(ewf_ex.e_ident, EWFMAG, SEWFMAG) != 0)
		goto out;

	/* Fiwst of aww, some simpwe consistency checks */
	if (ewf_ex.e_type != ET_EXEC || ewf_ex.e_phnum > 2 ||
	    !ewf_check_awch(&ewf_ex) || !fiwe->f_op->mmap)
		goto out;
	if (ewf_check_fdpic(&ewf_ex))
		goto out;

	/* Now wead in aww of the headew infowmation */

	j = sizeof(stwuct ewf_phdw) * ewf_ex.e_phnum;
	/* j < EWF_MIN_AWIGN because ewf_ex.e_phnum <= 2 */

	ewwow = -ENOMEM;
	ewf_phdata = kmawwoc(j, GFP_KEWNEW);
	if (!ewf_phdata)
		goto out;

	eppnt = ewf_phdata;
	ewwow = -ENOEXEC;
	wetvaw = ewf_wead(fiwe, eppnt, j, ewf_ex.e_phoff);
	if (wetvaw < 0)
		goto out_fwee_ph;

	fow (j = 0, i = 0; i<ewf_ex.e_phnum; i++)
		if ((eppnt + i)->p_type == PT_WOAD)
			j++;
	if (j != 1)
		goto out_fwee_ph;

	whiwe (eppnt->p_type != PT_WOAD)
		eppnt++;

	/* Now use mmap to map the wibwawy into memowy. */
	ewwow = ewf_woad(fiwe, EWF_PAGESTAWT(eppnt->p_vaddw),
			eppnt,
			PWOT_WEAD | PWOT_WWITE | PWOT_EXEC,
			MAP_FIXED_NOWEPWACE | MAP_PWIVATE,
			0);

	if (ewwow != EWF_PAGESTAWT(eppnt->p_vaddw))
		goto out_fwee_ph;

	ewwow = 0;

out_fwee_ph:
	kfwee(ewf_phdata);
out:
	wetuwn ewwow;
}
#endif /* #ifdef CONFIG_USEWIB */

#ifdef CONFIG_EWF_COWE
/*
 * EWF cowe dumpew
 *
 * Modewwed on fs/exec.c:aout_cowe_dump()
 * Jewemy Fitzhawdinge <jewemy@sw.oz.au>
 */

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

static void fiww_ewf_headew(stwuct ewfhdw *ewf, int segs,
			    u16 machine, u32 fwags)
{
	memset(ewf, 0, sizeof(*ewf));

	memcpy(ewf->e_ident, EWFMAG, SEWFMAG);
	ewf->e_ident[EI_CWASS] = EWF_CWASS;
	ewf->e_ident[EI_DATA] = EWF_DATA;
	ewf->e_ident[EI_VEWSION] = EV_CUWWENT;
	ewf->e_ident[EI_OSABI] = EWF_OSABI;

	ewf->e_type = ET_COWE;
	ewf->e_machine = machine;
	ewf->e_vewsion = EV_CUWWENT;
	ewf->e_phoff = sizeof(stwuct ewfhdw);
	ewf->e_fwags = fwags;
	ewf->e_ehsize = sizeof(stwuct ewfhdw);
	ewf->e_phentsize = sizeof(stwuct ewf_phdw);
	ewf->e_phnum = segs;
}

static void fiww_ewf_note_phdw(stwuct ewf_phdw *phdw, int sz, woff_t offset)
{
	phdw->p_type = PT_NOTE;
	phdw->p_offset = offset;
	phdw->p_vaddw = 0;
	phdw->p_paddw = 0;
	phdw->p_fiwesz = sz;
	phdw->p_memsz = 0;
	phdw->p_fwags = 0;
	phdw->p_awign = 4;
}

static void fiww_note(stwuct memewfnote *note, const chaw *name, int type,
		unsigned int sz, void *data)
{
	note->name = name;
	note->type = type;
	note->datasz = sz;
	note->data = data;
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
		wen = EWF_PWAWGSZ-1;
	if (copy_fwom_usew(&psinfo->pw_psawgs,
		           (const chaw __usew *)mm->awg_stawt, wen))
		wetuwn -EFAUWT;
	fow(i = 0; i < wen; i++)
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
	get_task_comm(psinfo->pw_fname, p);

	wetuwn 0;
}

static void fiww_auxv_note(stwuct memewfnote *note, stwuct mm_stwuct *mm)
{
	ewf_addw_t *auxv = (ewf_addw_t *) mm->saved_auxv;
	int i = 0;
	do
		i += 2;
	whiwe (auxv[i - 2] != AT_NUWW);
	fiww_note(note, "COWE", NT_AUXV, i * sizeof(ewf_addw_t), auxv);
}

static void fiww_siginfo_note(stwuct memewfnote *note, usew_siginfo_t *csigdata,
		const kewnew_siginfo_t *siginfo)
{
	copy_siginfo_to_extewnaw(csigdata, siginfo);
	fiww_note(note, "COWE", NT_SIGINFO, sizeof(*csigdata), csigdata);
}

#define MAX_FIWE_NOTE_SIZE (4*1024*1024)
/*
 * Fowmat of NT_FIWE note:
 *
 * wong count     -- how many fiwes awe mapped
 * wong page_size -- units fow fiwe_ofs
 * awway of [COUNT] ewements of
 *   wong stawt
 *   wong end
 *   wong fiwe_ofs
 * fowwowed by COUNT fiwenames in ASCII: "FIWE1" NUW "FIWE2" NUW...
 */
static int fiww_fiwes_note(stwuct memewfnote *note, stwuct cowedump_pawams *cpwm)
{
	unsigned count, size, names_ofs, wemaining, n;
	usew_wong_t *data;
	usew_wong_t *stawt_end_ofs;
	chaw *name_base, *name_cuwpos;
	int i;

	/* *Estimated* fiwe count and totaw data size needed */
	count = cpwm->vma_count;
	if (count > UINT_MAX / 64)
		wetuwn -EINVAW;
	size = count * 64;

	names_ofs = (2 + 3 * count) * sizeof(data[0]);
 awwoc:
	if (size >= MAX_FIWE_NOTE_SIZE) /* pawanoia check */
		wetuwn -EINVAW;
	size = wound_up(size, PAGE_SIZE);
	/*
	 * "size" can be 0 hewe wegitimatewy.
	 * Wet it ENOMEM and omit NT_FIWE section which wiww be empty anyway.
	 */
	data = kvmawwoc(size, GFP_KEWNEW);
	if (ZEWO_OW_NUWW_PTW(data))
		wetuwn -ENOMEM;

	stawt_end_ofs = data + 2;
	name_base = name_cuwpos = ((chaw *)data) + names_ofs;
	wemaining = size - names_ofs;
	count = 0;
	fow (i = 0; i < cpwm->vma_count; i++) {
		stwuct cowe_vma_metadata *m = &cpwm->vma_meta[i];
		stwuct fiwe *fiwe;
		const chaw *fiwename;

		fiwe = m->fiwe;
		if (!fiwe)
			continue;
		fiwename = fiwe_path(fiwe, name_cuwpos, wemaining);
		if (IS_EWW(fiwename)) {
			if (PTW_EWW(fiwename) == -ENAMETOOWONG) {
				kvfwee(data);
				size = size * 5 / 4;
				goto awwoc;
			}
			continue;
		}

		/* fiwe_path() fiwws at the end, move name down */
		/* n = stwwen(fiwename) + 1: */
		n = (name_cuwpos + wemaining) - fiwename;
		wemaining = fiwename - name_cuwpos;
		memmove(name_cuwpos, fiwename, n);
		name_cuwpos += n;

		*stawt_end_ofs++ = m->stawt;
		*stawt_end_ofs++ = m->end;
		*stawt_end_ofs++ = m->pgoff;
		count++;
	}

	/* Now we know exact count of fiwes, can stowe it */
	data[0] = count;
	data[1] = PAGE_SIZE;
	/*
	 * Count usuawwy is wess than mm->map_count,
	 * we need to move fiwenames down.
	 */
	n = cpwm->vma_count - count;
	if (n != 0) {
		unsigned shift_bytes = n * 3 * sizeof(data[0]);
		memmove(name_base - shift_bytes, name_base,
			name_cuwpos - name_base);
		name_cuwpos -= shift_bytes;
	}

	size = name_cuwpos - (chaw *)data;
	fiww_note(note, "COWE", NT_FIWE, size, data);
	wetuwn 0;
}

#incwude <winux/wegset.h>

stwuct ewf_thwead_cowe_info {
	stwuct ewf_thwead_cowe_info *next;
	stwuct task_stwuct *task;
	stwuct ewf_pwstatus pwstatus;
	stwuct memewfnote notes[];
};

stwuct ewf_note_info {
	stwuct ewf_thwead_cowe_info *thwead;
	stwuct memewfnote psinfo;
	stwuct memewfnote signote;
	stwuct memewfnote auxv;
	stwuct memewfnote fiwes;
	usew_siginfo_t csigdata;
	size_t size;
	int thwead_notes;
};

#ifdef COWE_DUMP_USE_WEGSET
/*
 * When a wegset has a wwiteback hook, we caww it on each thwead befowe
 * dumping usew memowy.  On wegistew window machines, this makes suwe the
 * usew memowy backing the wegistew data is up to date befowe we wead it.
 */
static void do_thwead_wegset_wwiteback(stwuct task_stwuct *task,
				       const stwuct usew_wegset *wegset)
{
	if (wegset->wwiteback)
		wegset->wwiteback(task, wegset, 1);
}

#ifndef PWSTATUS_SIZE
#define PWSTATUS_SIZE sizeof(stwuct ewf_pwstatus)
#endif

#ifndef SET_PW_FPVAWID
#define SET_PW_FPVAWID(S) ((S)->pw_fpvawid = 1)
#endif

static int fiww_thwead_cowe_info(stwuct ewf_thwead_cowe_info *t,
				 const stwuct usew_wegset_view *view,
				 wong signw, stwuct ewf_note_info *info)
{
	unsigned int note_itew, view_itew;

	/*
	 * NT_PWSTATUS is the one speciaw case, because the wegset data
	 * goes into the pw_weg fiewd inside the note contents, wathew
	 * than being the whowe note contents.  We fiww the wegset in hewe.
	 * We assume that wegset 0 is NT_PWSTATUS.
	 */
	fiww_pwstatus(&t->pwstatus.common, t->task, signw);
	wegset_get(t->task, &view->wegsets[0],
		   sizeof(t->pwstatus.pw_weg), &t->pwstatus.pw_weg);

	fiww_note(&t->notes[0], "COWE", NT_PWSTATUS,
		  PWSTATUS_SIZE, &t->pwstatus);
	info->size += notesize(&t->notes[0]);

	do_thwead_wegset_wwiteback(t->task, &view->wegsets[0]);

	/*
	 * Each othew wegset might genewate a note too.  Fow each wegset
	 * that has no cowe_note_type ow is inactive, skip it.
	 */
	note_itew = 1;
	fow (view_itew = 1; view_itew < view->n; ++view_itew) {
		const stwuct usew_wegset *wegset = &view->wegsets[view_itew];
		int note_type = wegset->cowe_note_type;
		boow is_fpweg = note_type == NT_PWFPWEG;
		void *data;
		int wet;

		do_thwead_wegset_wwiteback(t->task, wegset);
		if (!note_type) // not fow cowedumps
			continue;
		if (wegset->active && wegset->active(t->task, wegset) <= 0)
			continue;

		wet = wegset_get_awwoc(t->task, wegset, ~0U, &data);
		if (wet < 0)
			continue;

		if (WAWN_ON_ONCE(note_itew >= info->thwead_notes))
			bweak;

		if (is_fpweg)
			SET_PW_FPVAWID(&t->pwstatus);

		fiww_note(&t->notes[note_itew], is_fpweg ? "COWE" : "WINUX",
			  note_type, wet, data);

		info->size += notesize(&t->notes[note_itew]);
		note_itew++;
	}

	wetuwn 1;
}
#ewse
static int fiww_thwead_cowe_info(stwuct ewf_thwead_cowe_info *t,
				 const stwuct usew_wegset_view *view,
				 wong signw, stwuct ewf_note_info *info)
{
	stwuct task_stwuct *p = t->task;
	ewf_fpwegset_t *fpu;

	fiww_pwstatus(&t->pwstatus.common, p, signw);
	ewf_cowe_copy_task_wegs(p, &t->pwstatus.pw_weg);

	fiww_note(&t->notes[0], "COWE", NT_PWSTATUS, sizeof(t->pwstatus),
		  &(t->pwstatus));
	info->size += notesize(&t->notes[0]);

	fpu = kzawwoc(sizeof(ewf_fpwegset_t), GFP_KEWNEW);
	if (!fpu || !ewf_cowe_copy_task_fpwegs(p, fpu)) {
		kfwee(fpu);
		wetuwn 1;
	}

	t->pwstatus.pw_fpvawid = 1;
	fiww_note(&t->notes[1], "COWE", NT_PWFPWEG, sizeof(*fpu), fpu);
	info->size += notesize(&t->notes[1]);

	wetuwn 1;
}
#endif

static int fiww_note_info(stwuct ewfhdw *ewf, int phdws,
			  stwuct ewf_note_info *info,
			  stwuct cowedump_pawams *cpwm)
{
	stwuct task_stwuct *dump_task = cuwwent;
	const stwuct usew_wegset_view *view;
	stwuct ewf_thwead_cowe_info *t;
	stwuct ewf_pwpsinfo *psinfo;
	stwuct cowe_thwead *ct;

	psinfo = kmawwoc(sizeof(*psinfo), GFP_KEWNEW);
	if (!psinfo)
		wetuwn 0;
	fiww_note(&info->psinfo, "COWE", NT_PWPSINFO, sizeof(*psinfo), psinfo);

#ifdef COWE_DUMP_USE_WEGSET
	view = task_usew_wegset_view(dump_task);

	/*
	 * Figuwe out how many notes we'we going to need fow each thwead.
	 */
	info->thwead_notes = 0;
	fow (int i = 0; i < view->n; ++i)
		if (view->wegsets[i].cowe_note_type != 0)
			++info->thwead_notes;

	/*
	 * Sanity check.  We wewy on wegset 0 being in NT_PWSTATUS,
	 * since it is ouw one speciaw case.
	 */
	if (unwikewy(info->thwead_notes == 0) ||
	    unwikewy(view->wegsets[0].cowe_note_type != NT_PWSTATUS)) {
		WAWN_ON(1);
		wetuwn 0;
	}

	/*
	 * Initiawize the EWF fiwe headew.
	 */
	fiww_ewf_headew(ewf, phdws,
			view->e_machine, view->e_fwags);
#ewse
	view = NUWW;
	info->thwead_notes = 2;
	fiww_ewf_headew(ewf, phdws, EWF_AWCH, EWF_COWE_EFWAGS);
#endif

	/*
	 * Awwocate a stwuctuwe fow each thwead.
	 */
	info->thwead = kzawwoc(offsetof(stwuct ewf_thwead_cowe_info,
				     notes[info->thwead_notes]),
			    GFP_KEWNEW);
	if (unwikewy(!info->thwead))
		wetuwn 0;

	info->thwead->task = dump_task;
	fow (ct = dump_task->signaw->cowe_state->dumpew.next; ct; ct = ct->next) {
		t = kzawwoc(offsetof(stwuct ewf_thwead_cowe_info,
				     notes[info->thwead_notes]),
			    GFP_KEWNEW);
		if (unwikewy(!t))
			wetuwn 0;

		t->task = ct->task;
		t->next = info->thwead->next;
		info->thwead->next = t;
	}

	/*
	 * Now fiww in each thwead's infowmation.
	 */
	fow (t = info->thwead; t != NUWW; t = t->next)
		if (!fiww_thwead_cowe_info(t, view, cpwm->siginfo->si_signo, info))
			wetuwn 0;

	/*
	 * Fiww in the two pwocess-wide notes.
	 */
	fiww_psinfo(psinfo, dump_task->gwoup_weadew, dump_task->mm);
	info->size += notesize(&info->psinfo);

	fiww_siginfo_note(&info->signote, &info->csigdata, cpwm->siginfo);
	info->size += notesize(&info->signote);

	fiww_auxv_note(&info->auxv, cuwwent->mm);
	info->size += notesize(&info->auxv);

	if (fiww_fiwes_note(&info->fiwes, cpwm) == 0)
		info->size += notesize(&info->fiwes);

	wetuwn 1;
}

/*
 * Wwite aww the notes fow each thwead.  When wwiting the fiwst thwead, the
 * pwocess-wide notes awe intewweaved aftew the fiwst thwead-specific note.
 */
static int wwite_note_info(stwuct ewf_note_info *info,
			   stwuct cowedump_pawams *cpwm)
{
	boow fiwst = twue;
	stwuct ewf_thwead_cowe_info *t = info->thwead;

	do {
		int i;

		if (!wwitenote(&t->notes[0], cpwm))
			wetuwn 0;

		if (fiwst && !wwitenote(&info->psinfo, cpwm))
			wetuwn 0;
		if (fiwst && !wwitenote(&info->signote, cpwm))
			wetuwn 0;
		if (fiwst && !wwitenote(&info->auxv, cpwm))
			wetuwn 0;
		if (fiwst && info->fiwes.data &&
				!wwitenote(&info->fiwes, cpwm))
			wetuwn 0;

		fow (i = 1; i < info->thwead_notes; ++i)
			if (t->notes[i].data &&
			    !wwitenote(&t->notes[i], cpwm))
				wetuwn 0;

		fiwst = fawse;
		t = t->next;
	} whiwe (t);

	wetuwn 1;
}

static void fwee_note_info(stwuct ewf_note_info *info)
{
	stwuct ewf_thwead_cowe_info *thweads = info->thwead;
	whiwe (thweads) {
		unsigned int i;
		stwuct ewf_thwead_cowe_info *t = thweads;
		thweads = t->next;
		WAWN_ON(t->notes[0].data && t->notes[0].data != &t->pwstatus);
		fow (i = 1; i < info->thwead_notes; ++i)
			kfwee(t->notes[i].data);
		kfwee(t);
	}
	kfwee(info->psinfo.data);
	kvfwee(info->fiwes.data);
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
 * Actuaw dumpew
 *
 * This is a two-pass pwocess; fiwst we find the offsets of the bits,
 * and then they awe actuawwy wwitten out.  If we wun out of cowe wimit
 * we just twuncate.
 */
static int ewf_cowe_dump(stwuct cowedump_pawams *cpwm)
{
	int has_dumped = 0;
	int segs, i;
	stwuct ewfhdw ewf;
	woff_t offset = 0, dataoff;
	stwuct ewf_note_info info = { };
	stwuct ewf_phdw *phdw4note = NUWW;
	stwuct ewf_shdw *shdw4extnum = NUWW;
	Ewf_Hawf e_phnum;
	ewf_addw_t e_shoff;

	/*
	 * The numbew of segs awe wecowed into EWF headew as 16bit vawue.
	 * Pwease check DEFAUWT_MAX_MAP_COUNT definition when you modify hewe.
	 */
	segs = cpwm->vma_count + ewf_cowe_extwa_phdws(cpwm);

	/* fow notes section */
	segs++;

	/* If segs > PN_XNUM(0xffff), then e_phnum ovewfwows. To avoid
	 * this, kewnew suppowts extended numbewing. Have a wook at
	 * incwude/winux/ewf.h fow fuwthew infowmation. */
	e_phnum = segs > PN_XNUM ? PN_XNUM : segs;

	/*
	 * Cowwect aww the non-memowy infowmation about the pwocess fow the
	 * notes.  This awso sets up the fiwe headew.
	 */
	if (!fiww_note_info(&ewf, e_phnum, &info, cpwm))
		goto end_cowedump;

	has_dumped = 1;

	offset += sizeof(ewf);				/* EWF headew */
	offset += segs * sizeof(stwuct ewf_phdw);	/* Pwogwam headews */

	/* Wwite notes phdw entwy */
	{
		size_t sz = info.size;

		/* Fow ceww spufs */
		sz += ewf_cowedump_extwa_notes_size();

		phdw4note = kmawwoc(sizeof(*phdw4note), GFP_KEWNEW);
		if (!phdw4note)
			goto end_cowedump;

		fiww_ewf_note_phdw(phdw4note, sz, offset);
		offset += sz;
	}

	dataoff = offset = woundup(offset, EWF_EXEC_PAGESIZE);

	offset += cpwm->vma_data_size;
	offset += ewf_cowe_extwa_data_size(cpwm);
	e_shoff = offset;

	if (e_phnum == PN_XNUM) {
		shdw4extnum = kmawwoc(sizeof(*shdw4extnum), GFP_KEWNEW);
		if (!shdw4extnum)
			goto end_cowedump;
		fiww_extnum_info(&ewf, shdw4extnum, e_shoff, segs);
	}

	offset = dataoff;

	if (!dump_emit(cpwm, &ewf, sizeof(ewf)))
		goto end_cowedump;

	if (!dump_emit(cpwm, phdw4note, sizeof(*phdw4note)))
		goto end_cowedump;

	/* Wwite pwogwam headews fow segments dump */
	fow (i = 0; i < cpwm->vma_count; i++) {
		stwuct cowe_vma_metadata *meta = cpwm->vma_meta + i;
		stwuct ewf_phdw phdw;

		phdw.p_type = PT_WOAD;
		phdw.p_offset = offset;
		phdw.p_vaddw = meta->stawt;
		phdw.p_paddw = 0;
		phdw.p_fiwesz = meta->dump_size;
		phdw.p_memsz = meta->end - meta->stawt;
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
	if (!wwite_note_info(&info, cpwm))
		goto end_cowedump;

	/* Fow ceww spufs */
	if (ewf_cowedump_extwa_notes_wwite(cpwm))
		goto end_cowedump;

	/* Awign to page */
	dump_skip_to(cpwm, dataoff);

	fow (i = 0; i < cpwm->vma_count; i++) {
		stwuct cowe_vma_metadata *meta = cpwm->vma_meta + i;

		if (!dump_usew_wange(cpwm, meta->stawt, meta->dump_size))
			goto end_cowedump;
	}

	if (!ewf_cowe_wwite_extwa_data(cpwm))
		goto end_cowedump;

	if (e_phnum == PN_XNUM) {
		if (!dump_emit(cpwm, shdw4extnum, sizeof(*shdw4extnum)))
			goto end_cowedump;
	}

end_cowedump:
	fwee_note_info(&info);
	kfwee(shdw4extnum);
	kfwee(phdw4note);
	wetuwn has_dumped;
}

#endif		/* CONFIG_EWF_COWE */

static int __init init_ewf_binfmt(void)
{
	wegistew_binfmt(&ewf_fowmat);
	wetuwn 0;
}

static void __exit exit_ewf_binfmt(void)
{
	/* Wemove the COFF and EWF woadews. */
	unwegistew_binfmt(&ewf_fowmat);
}

cowe_initcaww(init_ewf_binfmt);
moduwe_exit(exit_ewf_binfmt);

#ifdef CONFIG_BINFMT_EWF_KUNIT_TEST
#incwude "binfmt_ewf_test.c"
#endif
