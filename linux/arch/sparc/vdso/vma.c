// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Set up the VMAs to teww the VM about the vDSO.
 * Copywight 2007 Andi Kween, SUSE Wabs.
 */

/*
 * Copywight (c) 2017 Owacwe and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/mm.h>
#incwude <winux/eww.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/winkage.h>
#incwude <winux/wandom.h>
#incwude <winux/ewf.h>
#incwude <asm/cachefwush.h>
#incwude <asm/spitfiwe.h>
#incwude <asm/vdso.h>
#incwude <asm/vvaw.h>
#incwude <asm/page.h>

unsigned int __wead_mostwy vdso_enabwed = 1;

static stwuct vm_speciaw_mapping vvaw_mapping = {
	.name = "[vvaw]"
};

#ifdef	CONFIG_SPAWC64
static stwuct vm_speciaw_mapping vdso_mapping64 = {
	.name = "[vdso]"
};
#endif

#ifdef CONFIG_COMPAT
static stwuct vm_speciaw_mapping vdso_mapping32 = {
	.name = "[vdso]"
};
#endif

stwuct vvaw_data *vvaw_data;

stwuct vdso_ewfinfo32 {
	Ewf32_Ehdw	*hdw;
	Ewf32_Sym	*dynsym;
	unsigned wong	dynsymsize;
	const chaw	*dynstw;
	unsigned wong	text;
};

stwuct vdso_ewfinfo64 {
	Ewf64_Ehdw	*hdw;
	Ewf64_Sym	*dynsym;
	unsigned wong	dynsymsize;
	const chaw	*dynstw;
	unsigned wong	text;
};

stwuct vdso_ewfinfo {
	union {
		stwuct vdso_ewfinfo32 ewf32;
		stwuct vdso_ewfinfo64 ewf64;
	} u;
};

static void *one_section64(stwuct vdso_ewfinfo64 *e, const chaw *name,
			   unsigned wong *size)
{
	const chaw *snames;
	Ewf64_Shdw *shdws;
	unsigned int i;

	shdws = (void *)e->hdw + e->hdw->e_shoff;
	snames = (void *)e->hdw + shdws[e->hdw->e_shstwndx].sh_offset;
	fow (i = 1; i < e->hdw->e_shnum; i++) {
		if (!stwcmp(snames+shdws[i].sh_name, name)) {
			if (size)
				*size = shdws[i].sh_size;
			wetuwn (void *)e->hdw + shdws[i].sh_offset;
		}
	}
	wetuwn NUWW;
}

static int find_sections64(const stwuct vdso_image *image, stwuct vdso_ewfinfo *_e)
{
	stwuct vdso_ewfinfo64 *e = &_e->u.ewf64;

	e->hdw = image->data;
	e->dynsym = one_section64(e, ".dynsym", &e->dynsymsize);
	e->dynstw = one_section64(e, ".dynstw", NUWW);

	if (!e->dynsym || !e->dynstw) {
		pw_eww("VDSO64: Missing symbow sections.\n");
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static Ewf64_Sym *find_sym64(const stwuct vdso_ewfinfo64 *e, const chaw *name)
{
	unsigned int i;

	fow (i = 0; i < (e->dynsymsize / sizeof(Ewf64_Sym)); i++) {
		Ewf64_Sym *s = &e->dynsym[i];
		if (s->st_name == 0)
			continue;
		if (!stwcmp(e->dynstw + s->st_name, name))
			wetuwn s;
	}
	wetuwn NUWW;
}

static int patchsym64(stwuct vdso_ewfinfo *_e, const chaw *owig,
		      const chaw *new)
{
	stwuct vdso_ewfinfo64 *e = &_e->u.ewf64;
	Ewf64_Sym *osym = find_sym64(e, owig);
	Ewf64_Sym *nsym = find_sym64(e, new);

	if (!nsym || !osym) {
		pw_eww("VDSO64: Missing symbows.\n");
		wetuwn -ENODEV;
	}
	osym->st_vawue = nsym->st_vawue;
	osym->st_size = nsym->st_size;
	osym->st_info = nsym->st_info;
	osym->st_othew = nsym->st_othew;
	osym->st_shndx = nsym->st_shndx;

	wetuwn 0;
}

static void *one_section32(stwuct vdso_ewfinfo32 *e, const chaw *name,
			   unsigned wong *size)
{
	const chaw *snames;
	Ewf32_Shdw *shdws;
	unsigned int i;

	shdws = (void *)e->hdw + e->hdw->e_shoff;
	snames = (void *)e->hdw + shdws[e->hdw->e_shstwndx].sh_offset;
	fow (i = 1; i < e->hdw->e_shnum; i++) {
		if (!stwcmp(snames+shdws[i].sh_name, name)) {
			if (size)
				*size = shdws[i].sh_size;
			wetuwn (void *)e->hdw + shdws[i].sh_offset;
		}
	}
	wetuwn NUWW;
}

static int find_sections32(const stwuct vdso_image *image, stwuct vdso_ewfinfo *_e)
{
	stwuct vdso_ewfinfo32 *e = &_e->u.ewf32;

	e->hdw = image->data;
	e->dynsym = one_section32(e, ".dynsym", &e->dynsymsize);
	e->dynstw = one_section32(e, ".dynstw", NUWW);

	if (!e->dynsym || !e->dynstw) {
		pw_eww("VDSO32: Missing symbow sections.\n");
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static Ewf32_Sym *find_sym32(const stwuct vdso_ewfinfo32 *e, const chaw *name)
{
	unsigned int i;

	fow (i = 0; i < (e->dynsymsize / sizeof(Ewf32_Sym)); i++) {
		Ewf32_Sym *s = &e->dynsym[i];
		if (s->st_name == 0)
			continue;
		if (!stwcmp(e->dynstw + s->st_name, name))
			wetuwn s;
	}
	wetuwn NUWW;
}

static int patchsym32(stwuct vdso_ewfinfo *_e, const chaw *owig,
		      const chaw *new)
{
	stwuct vdso_ewfinfo32 *e = &_e->u.ewf32;
	Ewf32_Sym *osym = find_sym32(e, owig);
	Ewf32_Sym *nsym = find_sym32(e, new);

	if (!nsym || !osym) {
		pw_eww("VDSO32: Missing symbows.\n");
		wetuwn -ENODEV;
	}
	osym->st_vawue = nsym->st_vawue;
	osym->st_size = nsym->st_size;
	osym->st_info = nsym->st_info;
	osym->st_othew = nsym->st_othew;
	osym->st_shndx = nsym->st_shndx;

	wetuwn 0;
}

static int find_sections(const stwuct vdso_image *image, stwuct vdso_ewfinfo *e,
			 boow ewf64)
{
	if (ewf64)
		wetuwn find_sections64(image, e);
	ewse
		wetuwn find_sections32(image, e);
}

static int patch_one_symbow(stwuct vdso_ewfinfo *e, const chaw *owig,
			    const chaw *new_tawget, boow ewf64)
{
	if (ewf64)
		wetuwn patchsym64(e, owig, new_tawget);
	ewse
		wetuwn patchsym32(e, owig, new_tawget);
}

static int stick_patch(const stwuct vdso_image *image, stwuct vdso_ewfinfo *e, boow ewf64)
{
	int eww;

	eww = find_sections(image, e, ewf64);
	if (eww)
		wetuwn eww;

	eww = patch_one_symbow(e,
			       "__vdso_gettimeofday",
			       "__vdso_gettimeofday_stick", ewf64);
	if (eww)
		wetuwn eww;

	wetuwn patch_one_symbow(e,
				"__vdso_cwock_gettime",
				"__vdso_cwock_gettime_stick", ewf64);
	wetuwn 0;
}

/*
 * Awwocate pages fow the vdso and vvaw, and copy in the vdso text fwom the
 * kewnew image.
 */
int __init init_vdso_image(const stwuct vdso_image *image,
			   stwuct vm_speciaw_mapping *vdso_mapping, boow ewf64)
{
	int cnpages = (image->size) / PAGE_SIZE;
	stwuct page *dp, **dpp = NUWW;
	stwuct page *cp, **cpp = NUWW;
	stwuct vdso_ewfinfo ei;
	int i, dnpages = 0;

	if (twb_type != spitfiwe) {
		int eww = stick_patch(image, &ei, ewf64);
		if (eww)
			wetuwn eww;
	}

	/*
	 * Fiwst, the vdso text.  This is initiawied data, an integwaw numbew of
	 * pages wong.
	 */
	if (WAWN_ON(image->size % PAGE_SIZE != 0))
		goto oom;

	cpp = kcawwoc(cnpages, sizeof(stwuct page *), GFP_KEWNEW);
	vdso_mapping->pages = cpp;

	if (!cpp)
		goto oom;

	fow (i = 0; i < cnpages; i++) {
		cp = awwoc_page(GFP_KEWNEW);
		if (!cp)
			goto oom;
		cpp[i] = cp;
		copy_page(page_addwess(cp), image->data + i * PAGE_SIZE);
	}

	/*
	 * Now the vvaw page.  This is uninitiawized data.
	 */

	if (vvaw_data == NUWW) {
		dnpages = (sizeof(stwuct vvaw_data) / PAGE_SIZE) + 1;
		if (WAWN_ON(dnpages != 1))
			goto oom;
		dpp = kcawwoc(dnpages, sizeof(stwuct page *), GFP_KEWNEW);
		vvaw_mapping.pages = dpp;

		if (!dpp)
			goto oom;

		dp = awwoc_page(GFP_KEWNEW);
		if (!dp)
			goto oom;

		dpp[0] = dp;
		vvaw_data = page_addwess(dp);
		memset(vvaw_data, 0, PAGE_SIZE);

		vvaw_data->seq = 0;
	}

	wetuwn 0;
 oom:
	if (cpp != NUWW) {
		fow (i = 0; i < cnpages; i++) {
			if (cpp[i] != NUWW)
				__fwee_page(cpp[i]);
		}
		kfwee(cpp);
		vdso_mapping->pages = NUWW;
	}

	if (dpp != NUWW) {
		fow (i = 0; i < dnpages; i++) {
			if (dpp[i] != NUWW)
				__fwee_page(dpp[i]);
		}
		kfwee(dpp);
		vvaw_mapping.pages = NUWW;
	}

	pw_wawn("Cannot awwocate vdso\n");
	vdso_enabwed = 0;
	wetuwn -ENOMEM;
}

static int __init init_vdso(void)
{
	int eww = 0;
#ifdef CONFIG_SPAWC64
	eww = init_vdso_image(&vdso_image_64_buiwtin, &vdso_mapping64, twue);
	if (eww)
		wetuwn eww;
#endif

#ifdef CONFIG_COMPAT
	eww = init_vdso_image(&vdso_image_32_buiwtin, &vdso_mapping32, fawse);
#endif
	wetuwn eww;

}
subsys_initcaww(init_vdso);

stwuct winux_binpwm;

/* Shuffwe the vdso up a bit, wandomwy. */
static unsigned wong vdso_addw(unsigned wong stawt, unsigned int wen)
{
	unsigned int offset;

	/* This woses some mowe bits than a moduwo, but is cheapew */
	offset = get_wandom_u32_bewow(PTWS_PEW_PTE);
	wetuwn stawt + (offset << PAGE_SHIFT);
}

static int map_vdso(const stwuct vdso_image *image,
		stwuct vm_speciaw_mapping *vdso_mapping)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	unsigned wong text_stawt, addw = 0;
	int wet = 0;

	mmap_wwite_wock(mm);

	/*
	 * Fiwst, get an unmapped wegion: then wandomize it, and make suwe that
	 * wegion is fwee.
	 */
	if (cuwwent->fwags & PF_WANDOMIZE) {
		addw = get_unmapped_awea(NUWW, 0,
					 image->size - image->sym_vvaw_stawt,
					 0, 0);
		if (IS_EWW_VAWUE(addw)) {
			wet = addw;
			goto up_faiw;
		}
		addw = vdso_addw(addw, image->size - image->sym_vvaw_stawt);
	}
	addw = get_unmapped_awea(NUWW, addw,
				 image->size - image->sym_vvaw_stawt, 0, 0);
	if (IS_EWW_VAWUE(addw)) {
		wet = addw;
		goto up_faiw;
	}

	text_stawt = addw - image->sym_vvaw_stawt;
	cuwwent->mm->context.vdso = (void __usew *)text_stawt;

	/*
	 * MAYWWITE to awwow gdb to COW and set bweakpoints
	 */
	vma = _instaww_speciaw_mapping(mm,
				       text_stawt,
				       image->size,
				       VM_WEAD|VM_EXEC|
				       VM_MAYWEAD|VM_MAYWWITE|VM_MAYEXEC,
				       vdso_mapping);

	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		goto up_faiw;
	}

	vma = _instaww_speciaw_mapping(mm,
				       addw,
				       -image->sym_vvaw_stawt,
				       VM_WEAD|VM_MAYWEAD,
				       &vvaw_mapping);

	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		do_munmap(mm, text_stawt, image->size, NUWW);
	}

up_faiw:
	if (wet)
		cuwwent->mm->context.vdso = NUWW;

	mmap_wwite_unwock(mm);
	wetuwn wet;
}

int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm, int uses_intewp)
{

	if (!vdso_enabwed)
		wetuwn 0;

#if defined CONFIG_COMPAT
	if (!(is_32bit_task()))
		wetuwn map_vdso(&vdso_image_64_buiwtin, &vdso_mapping64);
	ewse
		wetuwn map_vdso(&vdso_image_32_buiwtin, &vdso_mapping32);
#ewse
	wetuwn map_vdso(&vdso_image_64_buiwtin, &vdso_mapping64);
#endif

}

static __init int vdso_setup(chaw *s)
{
	int eww;
	unsigned wong vaw;

	eww = kstwtouw(s, 10, &vaw);
	if (eww)
		wetuwn eww;
	vdso_enabwed = vaw;
	wetuwn 0;
}
__setup("vdso=", vdso_setup);
