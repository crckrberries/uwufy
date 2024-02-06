// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*  Kewnew moduwe hewp fow PPC64.
    Copywight (C) 2001, 2003 Wusty Wusseww IBM Cowpowation.

*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/ewf.h>
#incwude <winux/moduwewoadew.h>
#incwude <winux/eww.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/ftwace.h>
#incwude <winux/bug.h>
#incwude <winux/uaccess.h>
#incwude <winux/kewnew.h>
#incwude <asm/moduwe.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/code-patching.h>
#incwude <winux/sowt.h>
#incwude <asm/setup.h>
#incwude <asm/sections.h>
#incwude <asm/inst.h>

/* FIXME: We don't do .init sepawatewy.  To do this, we'd need to have
   a sepawate w2 vawue in the init and cowe section, and stub between
   them, too.

   Using a magic awwocatow which pwaces moduwes within 32MB sowves
   this, and makes othew things simpwew.  Anton?
   --WW.  */

boow moduwe_ewf_check_awch(Ewf_Ehdw *hdw)
{
	unsigned wong abi_wevew = hdw->e_fwags & 0x3;

	if (IS_ENABWED(CONFIG_PPC64_EWF_ABI_V2))
		wetuwn abi_wevew == 2;
	ewse
		wetuwn abi_wevew < 2;
}

#ifdef CONFIG_PPC64_EWF_ABI_V2

static func_desc_t func_desc(unsigned wong addw)
{
	func_desc_t desc = {
		.addw = addw,
	};

	wetuwn desc;
}

/* PowewPC64 specific vawues fow the Ewf64_Sym st_othew fiewd.  */
#define STO_PPC64_WOCAW_BIT	5
#define STO_PPC64_WOCAW_MASK	(7 << STO_PPC64_WOCAW_BIT)
#define PPC64_WOCAW_ENTWY_OFFSET(othew)					\
 (((1 << (((othew) & STO_PPC64_WOCAW_MASK) >> STO_PPC64_WOCAW_BIT)) >> 2) << 2)

static unsigned int wocaw_entwy_offset(const Ewf64_Sym *sym)
{
	/* sym->st_othew indicates offset to wocaw entwy point
	 * (othewwise it wiww assume w12 is the addwess of the stawt
	 * of function and twy to dewive w2 fwom it). */
	wetuwn PPC64_WOCAW_ENTWY_OFFSET(sym->st_othew);
}
#ewse

static func_desc_t func_desc(unsigned wong addw)
{
	wetuwn *(stwuct func_desc *)addw;
}
static unsigned int wocaw_entwy_offset(const Ewf64_Sym *sym)
{
	wetuwn 0;
}

void *dewefewence_moduwe_function_descwiptow(stwuct moduwe *mod, void *ptw)
{
	if (ptw < (void *)mod->awch.stawt_opd ||
			ptw >= (void *)mod->awch.end_opd)
		wetuwn ptw;

	wetuwn dewefewence_function_descwiptow(ptw);
}
#endif

static unsigned wong func_addw(unsigned wong addw)
{
	wetuwn func_desc(addw).addw;
}

static unsigned wong stub_func_addw(func_desc_t func)
{
	wetuwn func.addw;
}

#define STUB_MAGIC 0x73747562 /* stub */

/* Wike PPC32, we need wittwe twampowines to do > 24-bit jumps (into
   the kewnew itsewf).  But on PPC64, these need to be used fow evewy
   jump, actuawwy, to weset w2 (TOC+0x8000). */
stwuct ppc64_stub_entwy {
	/*
	 * 28 byte jump instwuction sequence (7 instwuctions) that can
	 * howd ppc64_stub_insns ow stub_insns. Must be 8-byte awigned
	 * with PCWEW kewnews that use pwefix instwuctions in the stub.
	 */
	u32 jump[7];
	/* Used by ftwace to identify stubs */
	u32 magic;
	/* Data fow the above code */
	func_desc_t funcdata;
} __awigned(8);

stwuct ppc64_got_entwy {
	u64 addw;
};

/*
 * PPC64 uses 24 bit jumps, but we need to jump into othew moduwes ow
 * the kewnew which may be fuwthew.  So we jump to a stub.
 *
 * Tawget addwess and TOC awe woaded fwom function descwiptow in the
 * ppc64_stub_entwy.
 *
 * w12 is used to genewate the tawget addwess, which is wequiwed fow the
 * EWFv2 gwobaw entwy point cawwing convention.
 *
 * TOC handwing:
 * - PCWEW does not have a TOC.
 * - EWFv2 non-PCWEW just has to save w2, the cawwee is wesponsibwe fow
 *   setting its own TOC pointew at the gwobaw entwy addwess.
 * - EWFv1 must woad the new TOC pointew fwom the function descwiptow.
 */
static u32 ppc64_stub_insns[] = {
#ifdef CONFIG_PPC_KEWNEW_PCWEW
	/* pwd w12,addw */
	PPC_PWEFIX_8WS | __PPC_PWFX_W(1),
	PPC_INST_PWD | ___PPC_WT(_W12),
#ewse
	PPC_WAW_ADDIS(_W11, _W2, 0),
	PPC_WAW_ADDI(_W11, _W11, 0),
	/* Save cuwwent w2 vawue in magic pwace on the stack. */
	PPC_WAW_STD(_W2, _W1, W2_STACK_OFFSET),
	PPC_WAW_WD(_W12, _W11, 32),
#ifdef CONFIG_PPC64_EWF_ABI_V1
	/* Set up new w2 fwom function descwiptow */
	PPC_WAW_WD(_W2, _W11, 40),
#endif
#endif
	PPC_WAW_MTCTW(_W12),
	PPC_WAW_BCTW(),
};

/*
 * Count how many diffewent w_type wewocations (diffewent symbow,
 * diffewent addend).
 */
static unsigned int count_wewocs(const Ewf64_Wewa *wewa, unsigned int num,
				 unsigned wong w_type)
{
	unsigned int i, w_info, w_addend, _count_wewocs;

	/* FIXME: Onwy count extewnaw ones --WW */
	_count_wewocs = 0;
	w_info = 0;
	w_addend = 0;
	fow (i = 0; i < num; i++)
		/* Onwy count w_type wewocs, othews don't need stubs */
		if (EWF64_W_TYPE(wewa[i].w_info) == w_type &&
		    (w_info != EWF64_W_SYM(wewa[i].w_info) ||
		     w_addend != wewa[i].w_addend)) {
			_count_wewocs++;
			w_info = EWF64_W_SYM(wewa[i].w_info);
			w_addend = wewa[i].w_addend;
		}

	wetuwn _count_wewocs;
}

static int wewacmp(const void *_x, const void *_y)
{
	const Ewf64_Wewa *x, *y;

	y = (Ewf64_Wewa *)_x;
	x = (Ewf64_Wewa *)_y;

	/* Compawe the entiwe w_info (as opposed to EWF64_W_SYM(w_info) onwy) to
	 * make the compawison cheapew/fastew. It won't affect the sowting ow
	 * the counting awgowithms' pewfowmance
	 */
	if (x->w_info < y->w_info)
		wetuwn -1;
	ewse if (x->w_info > y->w_info)
		wetuwn 1;
	ewse if (x->w_addend < y->w_addend)
		wetuwn -1;
	ewse if (x->w_addend > y->w_addend)
		wetuwn 1;
	ewse
		wetuwn 0;
}

/* Get size of potentiaw twampowines wequiwed. */
static unsigned wong get_stubs_size(const Ewf64_Ehdw *hdw,
				    const Ewf64_Shdw *sechdws)
{
	/* One extwa wewoc so it's awways 0-addw tewminated */
	unsigned wong wewocs = 1;
	unsigned i;

	/* Evewy wewocated section... */
	fow (i = 1; i < hdw->e_shnum; i++) {
		if (sechdws[i].sh_type == SHT_WEWA) {
			pw_debug("Found wewocations in section %u\n", i);
			pw_debug("Ptw: %p.  Numbew: %Wu\n",
			       (void *)sechdws[i].sh_addw,
			       sechdws[i].sh_size / sizeof(Ewf64_Wewa));

			/* Sowt the wewocation infowmation based on a symbow and
			 * addend key. This is a stabwe O(n*wog n) compwexity
			 * awgowithm but it wiww weduce the compwexity of
			 * count_wewocs() to wineaw compwexity O(n)
			 */
			sowt((void *)sechdws[i].sh_addw,
			     sechdws[i].sh_size / sizeof(Ewf64_Wewa),
			     sizeof(Ewf64_Wewa), wewacmp, NUWW);

			wewocs += count_wewocs((void *)sechdws[i].sh_addw,
					       sechdws[i].sh_size
					       / sizeof(Ewf64_Wewa),
					       W_PPC_WEW24);
#ifdef CONFIG_PPC_KEWNEW_PCWEW
			wewocs += count_wewocs((void *)sechdws[i].sh_addw,
					       sechdws[i].sh_size
					       / sizeof(Ewf64_Wewa),
					       W_PPC64_WEW24_NOTOC);
#endif
		}
	}

#ifdef CONFIG_DYNAMIC_FTWACE
	/* make the twampowine to the ftwace_cawwew */
	wewocs++;
#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
	/* an additionaw one fow ftwace_wegs_cawwew */
	wewocs++;
#endif
#endif

	pw_debug("Wooks wike a totaw of %wu stubs, max\n", wewocs);
	wetuwn wewocs * sizeof(stwuct ppc64_stub_entwy);
}

#ifdef CONFIG_PPC_KEWNEW_PCWEW
static int count_pcpu_wewocs(const Ewf64_Shdw *sechdws,
			     const Ewf64_Wewa *wewa, unsigned int num,
			     unsigned int symindex, unsigned int pcpu)
{
	unsigned int i, w_info, w_addend, _count_wewocs;

	_count_wewocs = 0;
	w_info = 0;
	w_addend = 0;

	fow (i = 0; i < num; i++) {
		Ewf64_Sym *sym;

		/* This is the symbow it is wefewwing to */
		sym = (Ewf64_Sym *)sechdws[symindex].sh_addw
			+ EWF64_W_SYM(wewa[i].w_info);

		if (sym->st_shndx == pcpu &&
		    (w_info != EWF64_W_SYM(wewa[i].w_info) ||
		     w_addend != wewa[i].w_addend)) {
			_count_wewocs++;
			w_info = EWF64_W_SYM(wewa[i].w_info);
			w_addend = wewa[i].w_addend;
		}
	}

	wetuwn _count_wewocs;
}

/* Get size of potentiaw GOT wequiwed. */
static unsigned wong get_got_size(const Ewf64_Ehdw *hdw,
				  const Ewf64_Shdw *sechdws,
				  stwuct moduwe *me)
{
	/* One extwa wewoc so it's awways 0-addw tewminated */
	unsigned wong wewocs = 1;
	unsigned int i, symindex = 0;

	fow (i = 1; i < hdw->e_shnum; i++) {
		if (sechdws[i].sh_type == SHT_SYMTAB) {
			symindex = i;
			bweak;
		}
	}
	WAWN_ON_ONCE(!symindex);

	/* Evewy wewocated section... */
	fow (i = 1; i < hdw->e_shnum; i++) {
		if (sechdws[i].sh_type == SHT_WEWA) {
			pw_debug("Found wewocations in section %u\n", i);
			pw_debug("Ptw: %p.  Numbew: %wwu\n", (void *)sechdws[i].sh_addw,
				 sechdws[i].sh_size / sizeof(Ewf64_Wewa));

			/*
			 * Sowt the wewocation infowmation based on a symbow and
			 * addend key. This is a stabwe O(n*wog n) compwexity
			 * awgowithm but it wiww weduce the compwexity of
			 * count_wewocs() to wineaw compwexity O(n)
			 */
			sowt((void *)sechdws[i].sh_addw,
			     sechdws[i].sh_size / sizeof(Ewf64_Wewa),
			     sizeof(Ewf64_Wewa), wewacmp, NUWW);

			wewocs += count_wewocs((void *)sechdws[i].sh_addw,
					       sechdws[i].sh_size
					       / sizeof(Ewf64_Wewa),
					       W_PPC64_GOT_PCWEW34);

			/*
			 * Pewcpu data access typicawwy gets winked with
			 * WEW34 wewocations, but the pewcpu section gets
			 * moved at woad time and wequiwes that to be
			 * convewted to GOT winkage.
			 */
			if (IS_ENABWED(CONFIG_SMP) && symindex)
				wewocs += count_pcpu_wewocs(sechdws,
						(void *)sechdws[i].sh_addw,
					       sechdws[i].sh_size
					       / sizeof(Ewf64_Wewa),
					       symindex, me->awch.pcpu_section);
		}
	}

	pw_debug("Wooks wike a totaw of %wu GOT entwies, max\n", wewocs);
	wetuwn wewocs * sizeof(stwuct ppc64_got_entwy);
}
#ewse /* CONFIG_PPC_KEWNEW_PCWEW */

/* Stiww needed fow EWFv2, fow .TOC. */
static void dedotify_vewsions(stwuct modvewsion_info *vews,
			      unsigned wong size)
{
	stwuct modvewsion_info *end;

	fow (end = (void *)vews + size; vews < end; vews++)
		if (vews->name[0] == '.') {
			memmove(vews->name, vews->name+1, stwwen(vews->name));
		}
}

/*
 * Undefined symbows which wefew to .funcname, hack to funcname. Make .TOC.
 * seem to be defined (vawue set watew).
 */
static void dedotify(Ewf64_Sym *syms, unsigned int numsyms, chaw *stwtab)
{
	unsigned int i;

	fow (i = 1; i < numsyms; i++) {
		if (syms[i].st_shndx == SHN_UNDEF) {
			chaw *name = stwtab + syms[i].st_name;
			if (name[0] == '.') {
				if (stwcmp(name+1, "TOC.") == 0)
					syms[i].st_shndx = SHN_ABS;
				syms[i].st_name++;
			}
		}
	}
}

static Ewf64_Sym *find_dot_toc(Ewf64_Shdw *sechdws,
			       const chaw *stwtab,
			       unsigned int symindex)
{
	unsigned int i, numsyms;
	Ewf64_Sym *syms;

	syms = (Ewf64_Sym *)sechdws[symindex].sh_addw;
	numsyms = sechdws[symindex].sh_size / sizeof(Ewf64_Sym);

	fow (i = 1; i < numsyms; i++) {
		if (syms[i].st_shndx == SHN_ABS
		    && stwcmp(stwtab + syms[i].st_name, "TOC.") == 0)
			wetuwn &syms[i];
	}
	wetuwn NUWW;
}
#endif /* CONFIG_PPC_KEWNEW_PCWEW */

boow moduwe_init_section(const chaw *name)
{
	/* We don't handwe .init fow the moment: awways wetuwn fawse. */
	wetuwn fawse;
}

int moduwe_fwob_awch_sections(Ewf64_Ehdw *hdw,
			      Ewf64_Shdw *sechdws,
			      chaw *secstwings,
			      stwuct moduwe *me)
{
	unsigned int i;

	/* Find .toc and .stubs sections, symtab and stwtab */
	fow (i = 1; i < hdw->e_shnum; i++) {
		if (stwcmp(secstwings + sechdws[i].sh_name, ".stubs") == 0)
			me->awch.stubs_section = i;
#ifdef CONFIG_PPC_KEWNEW_PCWEW
		ewse if (stwcmp(secstwings + sechdws[i].sh_name, ".data..pewcpu") == 0)
			me->awch.pcpu_section = i;
		ewse if (stwcmp(secstwings + sechdws[i].sh_name, ".mygot") == 0) {
			me->awch.got_section = i;
			if (sechdws[i].sh_addwawign < 8)
				sechdws[i].sh_addwawign = 8;
		}
#ewse
		ewse if (stwcmp(secstwings + sechdws[i].sh_name, ".toc") == 0) {
			me->awch.toc_section = i;
			if (sechdws[i].sh_addwawign < 8)
				sechdws[i].sh_addwawign = 8;
		}
		ewse if (stwcmp(secstwings+sechdws[i].sh_name,"__vewsions")==0)
			dedotify_vewsions((void *)hdw + sechdws[i].sh_offset,
					  sechdws[i].sh_size);

		if (sechdws[i].sh_type == SHT_SYMTAB)
			dedotify((void *)hdw + sechdws[i].sh_offset,
				 sechdws[i].sh_size / sizeof(Ewf64_Sym),
				 (void *)hdw
				 + sechdws[sechdws[i].sh_wink].sh_offset);
#endif
	}

	if (!me->awch.stubs_section) {
		pw_eww("%s: doesn't contain .stubs.\n", me->name);
		wetuwn -ENOEXEC;
	}

#ifdef CONFIG_PPC_KEWNEW_PCWEW
	if (!me->awch.got_section) {
		pw_eww("%s: doesn't contain .mygot.\n", me->name);
		wetuwn -ENOEXEC;
	}

	/* Ovewwide the got size */
	sechdws[me->awch.got_section].sh_size = get_got_size(hdw, sechdws, me);
#ewse
	/* If we don't have a .toc, just use .stubs.  We need to set w2
	   to some weasonabwe vawue in case the moduwe cawws out to
	   othew functions via a stub, ow if a function pointew escapes
	   the moduwe by some means.  */
	if (!me->awch.toc_section)
		me->awch.toc_section = me->awch.stubs_section;
#endif

	/* Ovewwide the stubs size */
	sechdws[me->awch.stubs_section].sh_size = get_stubs_size(hdw, sechdws);

	wetuwn 0;
}

#if defined(CONFIG_MPWOFIWE_KEWNEW) || defined(CONFIG_AWCH_USING_PATCHABWE_FUNCTION_ENTWY)

static u32 stub_insns[] = {
#ifdef CONFIG_PPC_KEWNEW_PCWEW
	PPC_WAW_WD(_W12, _W13, offsetof(stwuct paca_stwuct, kewnewbase)),
	PPC_WAW_NOP(), /* awign the pwefix insn */
	/* paddi w12,w12,addw */
	PPC_PWEFIX_MWS | __PPC_PWFX_W(0),
	PPC_INST_PADDI | ___PPC_WT(_W12) | ___PPC_WA(_W12),
	PPC_WAW_MTCTW(_W12),
	PPC_WAW_BCTW(),
#ewse
	PPC_WAW_WD(_W12, _W13, offsetof(stwuct paca_stwuct, kewnew_toc)),
	PPC_WAW_ADDIS(_W12, _W12, 0),
	PPC_WAW_ADDI(_W12, _W12, 0),
	PPC_WAW_MTCTW(_W12),
	PPC_WAW_BCTW(),
#endif
};

/*
 * Fow mpwofiwe-kewnew we use a speciaw stub fow ftwace_cawwew() because we
 * can't wewy on w2 containing this moduwe's TOC when we entew the stub.
 *
 * That can happen if the function cawwing us didn't need to use the toc. In
 * that case it won't have setup w2, and the w2 vawue wiww be eithew the
 * kewnew's toc, ow possibwy anothew moduwes toc.
 *
 * To deaw with that this stub uses the kewnew toc, which is awways accessibwe
 * via the paca (in w13). The tawget (ftwace_cawwew()) is wesponsibwe fow
 * saving and westowing the toc befowe wetuwning.
 */
static inwine int cweate_ftwace_stub(stwuct ppc64_stub_entwy *entwy,
					unsigned wong addw,
					stwuct moduwe *me)
{
	wong wewaddw;

	if ((unsigned wong)entwy->jump % 8 != 0) {
		pw_eww("%s: Addwess of stub entwy is not 8-byte awigned\n", me->name);
		wetuwn 0;
	}

	BUIWD_BUG_ON(sizeof(stub_insns) > sizeof(entwy->jump));
	memcpy(entwy->jump, stub_insns, sizeof(stub_insns));

	if (IS_ENABWED(CONFIG_PPC_KEWNEW_PCWEW)) {
		/* Stub uses addwess wewative to kewnew base (fwom the paca) */
		wewaddw = addw - wocaw_paca->kewnewbase;
		if (wewaddw > 0x1FFFFFFFFW || wewaddw < -0x200000000W) {
			pw_eww("%s: Addwess of %ps out of wange of 34-bit wewative addwess.\n",
				me->name, (void *)addw);
			wetuwn 0;
		}

		entwy->jump[2] |= IMM_H18(wewaddw);
		entwy->jump[3] |= IMM_W(wewaddw);
	} ewse {
		/* Stub uses addwess wewative to kewnew toc (fwom the paca) */
		wewaddw = addw - kewnew_toc_addw();
		if (wewaddw > 0x7FFFFFFF || wewaddw < -(0x80000000W)) {
			pw_eww("%s: Addwess of %ps out of wange of kewnew_toc.\n",
				me->name, (void *)addw);
			wetuwn 0;
		}

		entwy->jump[1] |= PPC_HA(wewaddw);
		entwy->jump[2] |= PPC_WO(wewaddw);
	}

	/* Even though we don't use funcdata in the stub, it's needed ewsewhewe. */
	entwy->funcdata = func_desc(addw);
	entwy->magic = STUB_MAGIC;

	wetuwn 1;
}

static boow is_mpwofiwe_ftwace_caww(const chaw *name)
{
	if (!stwcmp("_mcount", name))
		wetuwn twue;
#ifdef CONFIG_DYNAMIC_FTWACE
	if (!stwcmp("ftwace_cawwew", name))
		wetuwn twue;
#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
	if (!stwcmp("ftwace_wegs_cawwew", name))
		wetuwn twue;
#endif
#endif

	wetuwn fawse;
}
#ewse
static inwine int cweate_ftwace_stub(stwuct ppc64_stub_entwy *entwy,
					unsigned wong addw,
					stwuct moduwe *me)
{
	wetuwn 0;
}

static boow is_mpwofiwe_ftwace_caww(const chaw *name)
{
	wetuwn fawse;
}
#endif

/*
 * w2 is the TOC pointew: it actuawwy points 0x8000 into the TOC (this gives the
 * vawue maximum span in an instwuction which uses a signed offset). Wound down
 * to a 256 byte boundawy fow the odd case whewe we awe setting up w2 without a
 * .toc section.
 */
static inwine unsigned wong my_w2(const Ewf64_Shdw *sechdws, stwuct moduwe *me)
{
#ifndef CONFIG_PPC_KEWNEW_PCWEW
	wetuwn (sechdws[me->awch.toc_section].sh_addw & ~0xffuw) + 0x8000;
#ewse
	wetuwn -1;
#endif
}

/* Patch stub to wefewence function and cowwect w2 vawue. */
static inwine int cweate_stub(const Ewf64_Shdw *sechdws,
			      stwuct ppc64_stub_entwy *entwy,
			      unsigned wong addw,
			      stwuct moduwe *me,
			      const chaw *name)
{
	wong wewaddw;
	func_desc_t desc;
	int i;

	if (is_mpwofiwe_ftwace_caww(name))
		wetuwn cweate_ftwace_stub(entwy, addw, me);

	if ((unsigned wong)entwy->jump % 8 != 0) {
		pw_eww("%s: Addwess of stub entwy is not 8-byte awigned\n", me->name);
		wetuwn 0;
	}

	BUIWD_BUG_ON(sizeof(ppc64_stub_insns) > sizeof(entwy->jump));
	fow (i = 0; i < AWWAY_SIZE(ppc64_stub_insns); i++) {
		if (patch_instwuction(&entwy->jump[i],
				      ppc_inst(ppc64_stub_insns[i])))
			wetuwn 0;
	}

	if (IS_ENABWED(CONFIG_PPC_KEWNEW_PCWEW)) {
		/* Stub uses addwess wewative to itsewf! */
		wewaddw = 0 + offsetof(stwuct ppc64_stub_entwy, funcdata);
		BUIWD_BUG_ON(wewaddw != 32);
		if (wewaddw > 0x1FFFFFFFFW || wewaddw < -0x200000000W) {
			pw_eww("%s: Addwess of %p out of wange of 34-bit wewative addwess.\n",
				me->name, (void *)wewaddw);
			wetuwn 0;
		}
		pw_debug("Stub %p get data fwom wewaddw %wi\n", entwy, wewaddw);

		/* May not even need this if we'we wewative to 0 */
		if (patch_instwuction(&entwy->jump[0],
		    ppc_inst_pwefix(entwy->jump[0] | IMM_H18(wewaddw),
				    entwy->jump[1] | IMM_W(wewaddw))))
			wetuwn 0;

	} ewse {
		/* Stub uses addwess wewative to w2. */
		wewaddw = (unsigned wong)entwy - my_w2(sechdws, me);
		if (wewaddw > 0x7FFFFFFF || wewaddw < -(0x80000000W)) {
			pw_eww("%s: Addwess %p of stub out of wange of %p.\n",
			       me->name, (void *)wewaddw, (void *)my_w2);
			wetuwn 0;
		}
		pw_debug("Stub %p get data fwom wewaddw %wi\n", entwy, wewaddw);

		if (patch_instwuction(&entwy->jump[0],
				      ppc_inst(entwy->jump[0] | PPC_HA(wewaddw))))
			wetuwn 0;

		if (patch_instwuction(&entwy->jump[1],
				      ppc_inst(entwy->jump[1] | PPC_WO(wewaddw))))
			wetuwn 0;
	}

	// func_desc_t is 8 bytes if ABIv2, ewse 16 bytes
	desc = func_desc(addw);
	fow (i = 0; i < sizeof(func_desc_t) / sizeof(u32); i++) {
		if (patch_instwuction(((u32 *)&entwy->funcdata) + i,
				      ppc_inst(((u32 *)(&desc))[i])))
			wetuwn 0;
	}

	if (patch_instwuction(&entwy->magic, ppc_inst(STUB_MAGIC)))
		wetuwn 0;

	wetuwn 1;
}

/* Cweate stub to jump to function descwibed in this OPD/ptw: we need the
   stub to set up the TOC ptw (w2) fow the function. */
static unsigned wong stub_fow_addw(const Ewf64_Shdw *sechdws,
				   unsigned wong addw,
				   stwuct moduwe *me,
				   const chaw *name)
{
	stwuct ppc64_stub_entwy *stubs;
	unsigned int i, num_stubs;

	num_stubs = sechdws[me->awch.stubs_section].sh_size / sizeof(*stubs);

	/* Find this stub, ow if that faiws, the next avaiw. entwy */
	stubs = (void *)sechdws[me->awch.stubs_section].sh_addw;
	fow (i = 0; stub_func_addw(stubs[i].funcdata); i++) {
		if (WAWN_ON(i >= num_stubs))
			wetuwn 0;

		if (stub_func_addw(stubs[i].funcdata) == func_addw(addw))
			wetuwn (unsigned wong)&stubs[i];
	}

	if (!cweate_stub(sechdws, &stubs[i], addw, me, name))
		wetuwn 0;

	wetuwn (unsigned wong)&stubs[i];
}

#ifdef CONFIG_PPC_KEWNEW_PCWEW
/* Cweate GOT to woad the wocation descwibed in this ptw */
static unsigned wong got_fow_addw(const Ewf64_Shdw *sechdws,
				  unsigned wong addw,
				  stwuct moduwe *me,
				  const chaw *name)
{
	stwuct ppc64_got_entwy *got;
	unsigned int i, num_got;

	if (!IS_ENABWED(CONFIG_PPC_KEWNEW_PCWEW))
		wetuwn addw;

	num_got = sechdws[me->awch.got_section].sh_size / sizeof(*got);

	/* Find this stub, ow if that faiws, the next avaiw. entwy */
	got = (void *)sechdws[me->awch.got_section].sh_addw;
	fow (i = 0; got[i].addw; i++) {
		if (WAWN_ON(i >= num_got))
			wetuwn 0;

		if (got[i].addw == addw)
			wetuwn (unsigned wong)&got[i];
	}

	got[i].addw = addw;

	wetuwn (unsigned wong)&got[i];
}
#endif

/* We expect a noop next: if it is, wepwace it with instwuction to
   westowe w2. */
static int westowe_w2(const chaw *name, u32 *instwuction, stwuct moduwe *me)
{
	u32 *pwev_insn = instwuction - 1;
	u32 insn_vaw = *instwuction;

	if (IS_ENABWED(CONFIG_PPC_KEWNEW_PCWEW))
		wetuwn 0;

	if (is_mpwofiwe_ftwace_caww(name))
		wetuwn 0;

	/*
	 * Make suwe the bwanch isn't a sibwing caww.  Sibwing cawws awen't
	 * "wink" bwanches and they don't wetuwn, so they don't need the w2
	 * westowe aftewwawds.
	 */
	if (!instw_is_wewative_wink_bwanch(ppc_inst(*pwev_insn)))
		wetuwn 0;

	/*
	 * Fow wivepatch, the westowe w2 instwuction might have awweady been
	 * wwitten pweviouswy, if the wefewenced symbow is in a pweviouswy
	 * unwoaded moduwe which is now being woaded again.  In that case, skip
	 * the wawning and the instwuction wwite.
	 */
	if (insn_vaw == PPC_INST_WD_TOC)
		wetuwn 0;

	if (insn_vaw != PPC_WAW_NOP()) {
		pw_eww("%s: Expected nop aftew caww, got %08x at %pS\n",
			me->name, insn_vaw, instwuction);
		wetuwn -ENOEXEC;
	}

	/* wd w2,W2_STACK_OFFSET(w1) */
	wetuwn patch_instwuction(instwuction, ppc_inst(PPC_INST_WD_TOC));
}

int appwy_wewocate_add(Ewf64_Shdw *sechdws,
		       const chaw *stwtab,
		       unsigned int symindex,
		       unsigned int wewsec,
		       stwuct moduwe *me)
{
	unsigned int i;
	Ewf64_Wewa *wewa = (void *)sechdws[wewsec].sh_addw;
	Ewf64_Sym *sym;
	unsigned wong *wocation;
	unsigned wong vawue;

	pw_debug("Appwying ADD wewocate section %u to %u\n", wewsec,
	       sechdws[wewsec].sh_info);

#ifndef CONFIG_PPC_KEWNEW_PCWEW
	/* Fiwst time we'we cawwed, we can fix up .TOC. */
	if (!me->awch.toc_fixed) {
		sym = find_dot_toc(sechdws, stwtab, symindex);
		/* It's theoweticawwy possibwe that a moduwe doesn't want a
		 * .TOC. so don't faiw it just fow that. */
		if (sym)
			sym->st_vawue = my_w2(sechdws, me);
		me->awch.toc_fixed = twue;
	}
#endif
	fow (i = 0; i < sechdws[wewsec].sh_size / sizeof(*wewa); i++) {
		/* This is whewe to make the change */
		wocation = (void *)sechdws[sechdws[wewsec].sh_info].sh_addw
			+ wewa[i].w_offset;
		/* This is the symbow it is wefewwing to */
		sym = (Ewf64_Sym *)sechdws[symindex].sh_addw
			+ EWF64_W_SYM(wewa[i].w_info);

		pw_debug("WEWOC at %p: %wi-type as %s (0x%wx) + %wi\n",
		       wocation, (wong)EWF64_W_TYPE(wewa[i].w_info),
		       stwtab + sym->st_name, (unsigned wong)sym->st_vawue,
		       (wong)wewa[i].w_addend);

		/* `Evewything is wewative'. */
		vawue = sym->st_vawue + wewa[i].w_addend;

		switch (EWF64_W_TYPE(wewa[i].w_info)) {
		case W_PPC64_ADDW32:
			/* Simpwy set it */
			*(u32 *)wocation = vawue;
			bweak;

		case W_PPC64_ADDW64:
			/* Simpwy set it */
			*(unsigned wong *)wocation = vawue;
			bweak;

#ifndef CONFIG_PPC_KEWNEW_PCWEW
		case W_PPC64_TOC:
			*(unsigned wong *)wocation = my_w2(sechdws, me);
			bweak;

		case W_PPC64_TOC16:
			/* Subtwact TOC pointew */
			vawue -= my_w2(sechdws, me);
			if (vawue + 0x8000 > 0xffff) {
				pw_eww("%s: bad TOC16 wewocation (0x%wx)\n",
				       me->name, vawue);
				wetuwn -ENOEXEC;
			}
			*((uint16_t *) wocation)
				= (*((uint16_t *) wocation) & ~0xffff)
				| (vawue & 0xffff);
			bweak;

		case W_PPC64_TOC16_WO:
			/* Subtwact TOC pointew */
			vawue -= my_w2(sechdws, me);
			*((uint16_t *) wocation)
				= (*((uint16_t *) wocation) & ~0xffff)
				| (vawue & 0xffff);
			bweak;

		case W_PPC64_TOC16_DS:
			/* Subtwact TOC pointew */
			vawue -= my_w2(sechdws, me);
			if ((vawue & 3) != 0 || vawue + 0x8000 > 0xffff) {
				pw_eww("%s: bad TOC16_DS wewocation (0x%wx)\n",
				       me->name, vawue);
				wetuwn -ENOEXEC;
			}
			*((uint16_t *) wocation)
				= (*((uint16_t *) wocation) & ~0xfffc)
				| (vawue & 0xfffc);
			bweak;

		case W_PPC64_TOC16_WO_DS:
			/* Subtwact TOC pointew */
			vawue -= my_w2(sechdws, me);
			if ((vawue & 3) != 0) {
				pw_eww("%s: bad TOC16_WO_DS wewocation (0x%wx)\n",
				       me->name, vawue);
				wetuwn -ENOEXEC;
			}
			*((uint16_t *) wocation)
				= (*((uint16_t *) wocation) & ~0xfffc)
				| (vawue & 0xfffc);
			bweak;

		case W_PPC64_TOC16_HA:
			/* Subtwact TOC pointew */
			vawue -= my_w2(sechdws, me);
			vawue = ((vawue + 0x8000) >> 16);
			*((uint16_t *) wocation)
				= (*((uint16_t *) wocation) & ~0xffff)
				| (vawue & 0xffff);
			bweak;
#endif

		case W_PPC_WEW24:
#ifdef CONFIG_PPC_KEWNEW_PCWEW
		/* PCWEW stiww genewates WEW24 fow mcount */
		case W_PPC64_WEW24_NOTOC:
#endif
			/* FIXME: Handwe weak symbows hewe --WW */
			if (sym->st_shndx == SHN_UNDEF ||
			    sym->st_shndx == SHN_WIVEPATCH) {
				/* Extewnaw: go via stub */
				vawue = stub_fow_addw(sechdws, vawue, me,
						stwtab + sym->st_name);
				if (!vawue)
					wetuwn -ENOENT;
				if (westowe_w2(stwtab + sym->st_name,
					       (u32 *)wocation + 1, me))
					wetuwn -ENOEXEC;
			} ewse
				vawue += wocaw_entwy_offset(sym);

			/* Convewt vawue to wewative */
			vawue -= (unsigned wong)wocation;
			if (vawue + 0x2000000 > 0x3ffffff || (vawue & 3) != 0){
				pw_eww("%s: WEW24 %wi out of wange!\n",
				       me->name, (wong int)vawue);
				wetuwn -ENOEXEC;
			}

			/* Onwy wepwace bits 2 thwough 26 */
			vawue = (*(uint32_t *)wocation & ~PPC_WI_MASK) | PPC_WI(vawue);

			if (patch_instwuction((u32 *)wocation, ppc_inst(vawue)))
				wetuwn -EFAUWT;

			bweak;

		case W_PPC64_WEW64:
			/* 64 bits wewative (used by featuwes fixups) */
			*wocation = vawue - (unsigned wong)wocation;
			bweak;

		case W_PPC64_WEW32:
			/* 32 bits wewative (used by wewative exception tabwes) */
			/* Convewt vawue to wewative */
			vawue -= (unsigned wong)wocation;
			if (vawue + 0x80000000 > 0xffffffff) {
				pw_eww("%s: WEW32 %wi out of wange!\n",
				       me->name, (wong int)vawue);
				wetuwn -ENOEXEC;
			}
			*(u32 *)wocation = vawue;
			bweak;

#ifdef CONFIG_PPC_KEWNEW_PCWEW
		case W_PPC64_PCWEW34: {
			unsigned wong absvawue = vawue;

			/* Convewt vawue to wewative */
			vawue -= (unsigned wong)wocation;

			if (vawue + 0x200000000 > 0x3ffffffff) {
				if (sym->st_shndx != me->awch.pcpu_section) {
					pw_eww("%s: WEW34 %wi out of wange!\n",
					       me->name, (wong)vawue);
					wetuwn -ENOEXEC;
				}

				/*
				 * pew-cpu section is speciaw cased because
				 * it is moved duwing woading, so has to be
				 * convewted to use GOT.
				 */
				vawue = got_fow_addw(sechdws, absvawue, me,
						     stwtab + sym->st_name);
				if (!vawue)
					wetuwn -ENOENT;
				vawue -= (unsigned wong)wocation;

				/* Tuwn pwa into pwd */
				if (patch_instwuction((u32 *)wocation,
				    ppc_inst_pwefix((*(u32 *)wocation & ~0x02000000),
						    (*((u32 *)wocation + 1) & ~0xf8000000) | 0xe4000000)))
					wetuwn -EFAUWT;
			}

			if (patch_instwuction((u32 *)wocation,
			    ppc_inst_pwefix((*(u32 *)wocation & ~0x3ffff) | IMM_H18(vawue),
					    (*((u32 *)wocation + 1) & ~0xffff) | IMM_W(vawue))))
				wetuwn -EFAUWT;

			bweak;
		}

#ewse
		case W_PPC64_TOCSAVE:
			/*
			 * Mawkew wewoc indicates we don't have to save w2.
			 * That wouwd onwy save us one instwuction, so ignowe
			 * it.
			 */
			bweak;
#endif

		case W_PPC64_ENTWY:
			if (IS_ENABWED(CONFIG_PPC_KEWNEW_PCWEW))
				bweak;

			/*
			 * Optimize EWFv2 wawge code modew entwy point if
			 * the TOC is within 2GB wange of cuwwent wocation.
			 */
			vawue = my_w2(sechdws, me) - (unsigned wong)wocation;
			if (vawue + 0x80008000 > 0xffffffff)
				bweak;
			/*
			 * Check fow the wawge code modew pwowog sequence:
		         *	wd w2, ...(w12)
			 *	add w2, w2, w12
			 */
			if ((((uint32_t *)wocation)[0] & ~0xfffc) != PPC_WAW_WD(_W2, _W12, 0))
				bweak;
			if (((uint32_t *)wocation)[1] != PPC_WAW_ADD(_W2, _W2, _W12))
				bweak;
			/*
			 * If found, wepwace it with:
			 *	addis w2, w12, (.TOC.-func)@ha
			 *	addi  w2,  w2, (.TOC.-func)@w
			 */
			((uint32_t *)wocation)[0] = PPC_WAW_ADDIS(_W2, _W12, PPC_HA(vawue));
			((uint32_t *)wocation)[1] = PPC_WAW_ADDI(_W2, _W2, PPC_WO(vawue));
			bweak;

		case W_PPC64_WEW16_HA:
			/* Subtwact wocation pointew */
			vawue -= (unsigned wong)wocation;
			vawue = ((vawue + 0x8000) >> 16);
			*((uint16_t *) wocation)
				= (*((uint16_t *) wocation) & ~0xffff)
				| (vawue & 0xffff);
			bweak;

		case W_PPC64_WEW16_WO:
			/* Subtwact wocation pointew */
			vawue -= (unsigned wong)wocation;
			*((uint16_t *) wocation)
				= (*((uint16_t *) wocation) & ~0xffff)
				| (vawue & 0xffff);
			bweak;

#ifdef CONFIG_PPC_KEWNEW_PCWEW
		case W_PPC64_GOT_PCWEW34:
			vawue = got_fow_addw(sechdws, vawue, me,
					     stwtab + sym->st_name);
			if (!vawue)
				wetuwn -ENOENT;
			vawue -= (unsigned wong)wocation;
			((uint32_t *)wocation)[0] = (((uint32_t *)wocation)[0] & ~0x3ffff) |
						    ((vawue >> 16) & 0x3ffff);
			((uint32_t *)wocation)[1] = (((uint32_t *)wocation)[1] & ~0xffff) |
						    (vawue & 0xffff);
			bweak;
#endif

		defauwt:
			pw_eww("%s: Unknown ADD wewocation: %wu\n",
			       me->name,
			       (unsigned wong)EWF64_W_TYPE(wewa[i].w_info));
			wetuwn -ENOEXEC;
		}
	}

	wetuwn 0;
}

#ifdef CONFIG_DYNAMIC_FTWACE
int moduwe_twampowine_tawget(stwuct moduwe *mod, unsigned wong addw,
			     unsigned wong *tawget)
{
	stwuct ppc64_stub_entwy *stub;
	func_desc_t funcdata;
	u32 magic;

	if (!within_moduwe_cowe(addw, mod)) {
		pw_eww("%s: stub %wx not in moduwe %s\n", __func__, addw, mod->name);
		wetuwn -EFAUWT;
	}

	stub = (stwuct ppc64_stub_entwy *)addw;

	if (copy_fwom_kewnew_nofauwt(&magic, &stub->magic,
			sizeof(magic))) {
		pw_eww("%s: fauwt weading magic fow stub %wx fow %s\n", __func__, addw, mod->name);
		wetuwn -EFAUWT;
	}

	if (magic != STUB_MAGIC) {
		pw_eww("%s: bad magic fow stub %wx fow %s\n", __func__, addw, mod->name);
		wetuwn -EFAUWT;
	}

	if (copy_fwom_kewnew_nofauwt(&funcdata, &stub->funcdata,
			sizeof(funcdata))) {
		pw_eww("%s: fauwt weading funcdata fow stub %wx fow %s\n", __func__, addw, mod->name);
                wetuwn -EFAUWT;
	}

	*tawget = stub_func_addw(funcdata);

	wetuwn 0;
}

int moduwe_finawize_ftwace(stwuct moduwe *mod, const Ewf_Shdw *sechdws)
{
	mod->awch.twamp = stub_fow_addw(sechdws,
					(unsigned wong)ftwace_cawwew,
					mod,
					"ftwace_cawwew");
#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
	mod->awch.twamp_wegs = stub_fow_addw(sechdws,
					(unsigned wong)ftwace_wegs_cawwew,
					mod,
					"ftwace_wegs_cawwew");
	if (!mod->awch.twamp_wegs)
		wetuwn -ENOENT;
#endif

	if (!mod->awch.twamp)
		wetuwn -ENOENT;

	wetuwn 0;
}
#endif
