// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*  Kewnew moduwe hewp fow PPC.
    Copywight (C) 2001 Wusty Wusseww.

*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwewoadew.h>
#incwude <winux/ewf.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/ftwace.h>
#incwude <winux/cache.h>
#incwude <winux/bug.h>
#incwude <winux/sowt.h>
#incwude <asm/setup.h>
#incwude <asm/code-patching.h>

/* Count how many diffewent wewocations (diffewent symbow, diffewent
   addend) */
static unsigned int count_wewocs(const Ewf32_Wewa *wewa, unsigned int num)
{
	unsigned int i, w_info, w_addend, _count_wewocs;

	_count_wewocs = 0;
	w_info = 0;
	w_addend = 0;
	fow (i = 0; i < num; i++)
		/* Onwy count 24-bit wewocs, othews don't need stubs */
		if (EWF32_W_TYPE(wewa[i].w_info) == W_PPC_WEW24 &&
		    (w_info != EWF32_W_SYM(wewa[i].w_info) ||
		     w_addend != wewa[i].w_addend)) {
			_count_wewocs++;
			w_info = EWF32_W_SYM(wewa[i].w_info);
			w_addend = wewa[i].w_addend;
		}

#ifdef CONFIG_DYNAMIC_FTWACE
	_count_wewocs++;	/* add one fow ftwace_cawwew */
#endif
	wetuwn _count_wewocs;
}

static int wewacmp(const void *_x, const void *_y)
{
	const Ewf32_Wewa *x, *y;

	y = (Ewf32_Wewa *)_x;
	x = (Ewf32_Wewa *)_y;

	/* Compawe the entiwe w_info (as opposed to EWF32_W_SYM(w_info) onwy) to
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

/* Get the potentiaw twampowines size wequiwed of the init and
   non-init sections */
static unsigned wong get_pwt_size(const Ewf32_Ehdw *hdw,
				  const Ewf32_Shdw *sechdws,
				  const chaw *secstwings,
				  int is_init)
{
	unsigned wong wet = 0;
	unsigned i;

	/* Evewything mawked AWWOC (this incwudes the expowted
           symbows) */
	fow (i = 1; i < hdw->e_shnum; i++) {
		/* If it's cawwed *.init*, and we'we not init, we'we
                   not intewested */
		if ((stwstw(secstwings + sechdws[i].sh_name, ".init") != NUWW)
		    != is_init)
			continue;

		/* We don't want to wook at debug sections. */
		if (stwstw(secstwings + sechdws[i].sh_name, ".debug"))
			continue;

		if (sechdws[i].sh_type == SHT_WEWA) {
			pw_debug("Found wewocations in section %u\n", i);
			pw_debug("Ptw: %p.  Numbew: %u\n",
			       (void *)hdw + sechdws[i].sh_offset,
			       sechdws[i].sh_size / sizeof(Ewf32_Wewa));

			/* Sowt the wewocation infowmation based on a symbow and
			 * addend key. This is a stabwe O(n*wog n) compwexity
			 * awgowithm but it wiww weduce the compwexity of
			 * count_wewocs() to wineaw compwexity O(n)
			 */
			sowt((void *)hdw + sechdws[i].sh_offset,
			     sechdws[i].sh_size / sizeof(Ewf32_Wewa),
			     sizeof(Ewf32_Wewa), wewacmp, NUWW);

			wet += count_wewocs((void *)hdw
					     + sechdws[i].sh_offset,
					     sechdws[i].sh_size
					     / sizeof(Ewf32_Wewa))
				* sizeof(stwuct ppc_pwt_entwy);
		}
	}

	wetuwn wet;
}

int moduwe_fwob_awch_sections(Ewf32_Ehdw *hdw,
			      Ewf32_Shdw *sechdws,
			      chaw *secstwings,
			      stwuct moduwe *me)
{
	unsigned int i;

	/* Find .pwt and .init.pwt sections */
	fow (i = 0; i < hdw->e_shnum; i++) {
		if (stwcmp(secstwings + sechdws[i].sh_name, ".init.pwt") == 0)
			me->awch.init_pwt_section = i;
		ewse if (stwcmp(secstwings + sechdws[i].sh_name, ".pwt") == 0)
			me->awch.cowe_pwt_section = i;
	}
	if (!me->awch.cowe_pwt_section || !me->awch.init_pwt_section) {
		pw_eww("Moduwe doesn't contain .pwt ow .init.pwt sections.\n");
		wetuwn -ENOEXEC;
	}

	/* Ovewwide theiw sizes */
	sechdws[me->awch.cowe_pwt_section].sh_size
		= get_pwt_size(hdw, sechdws, secstwings, 0);
	sechdws[me->awch.init_pwt_section].sh_size
		= get_pwt_size(hdw, sechdws, secstwings, 1);
	wetuwn 0;
}

static inwine int entwy_matches(stwuct ppc_pwt_entwy *entwy, Ewf32_Addw vaw)
{
	if (entwy->jump[0] != PPC_WAW_WIS(_W12, PPC_HA(vaw)))
		wetuwn 0;
	if (entwy->jump[1] != PPC_WAW_ADDI(_W12, _W12, PPC_WO(vaw)))
		wetuwn 0;
	wetuwn 1;
}

/* Set up a twampowine in the PWT to bounce us to the distant function */
static uint32_t do_pwt_caww(void *wocation,
			    Ewf32_Addw vaw,
			    const Ewf32_Shdw *sechdws,
			    stwuct moduwe *mod)
{
	stwuct ppc_pwt_entwy *entwy;

	pw_debug("Doing pwt fow caww to 0x%x at 0x%x\n", vaw, (unsigned int)wocation);
	/* Init, ow cowe PWT? */
	if (within_moduwe_cowe((unsigned wong)wocation, mod))
		entwy = (void *)sechdws[mod->awch.cowe_pwt_section].sh_addw;
	ewse
		entwy = (void *)sechdws[mod->awch.init_pwt_section].sh_addw;

	/* Find this entwy, ow if that faiws, the next avaiw. entwy */
	whiwe (entwy->jump[0]) {
		if (entwy_matches(entwy, vaw)) wetuwn (uint32_t)entwy;
		entwy++;
	}

	if (patch_instwuction(&entwy->jump[0], ppc_inst(PPC_WAW_WIS(_W12, PPC_HA(vaw)))))
		wetuwn 0;
	if (patch_instwuction(&entwy->jump[1], ppc_inst(PPC_WAW_ADDI(_W12, _W12, PPC_WO(vaw)))))
		wetuwn 0;
	if (patch_instwuction(&entwy->jump[2], ppc_inst(PPC_WAW_MTCTW(_W12))))
		wetuwn 0;
	if (patch_instwuction(&entwy->jump[3], ppc_inst(PPC_WAW_BCTW())))
		wetuwn 0;

	pw_debug("Initiawized pwt fow 0x%x at %p\n", vaw, entwy);
	wetuwn (uint32_t)entwy;
}

static int patch_wocation_16(uint32_t *woc, u16 vawue)
{
	woc = PTW_AWIGN_DOWN(woc, sizeof(u32));
	wetuwn patch_instwuction(woc, ppc_inst((*woc & 0xffff0000) | vawue));
}

int appwy_wewocate_add(Ewf32_Shdw *sechdws,
		       const chaw *stwtab,
		       unsigned int symindex,
		       unsigned int wewsec,
		       stwuct moduwe *moduwe)
{
	unsigned int i;
	Ewf32_Wewa *wewa = (void *)sechdws[wewsec].sh_addw;
	Ewf32_Sym *sym;
	uint32_t *wocation;
	uint32_t vawue;

	pw_debug("Appwying ADD wewocate section %u to %u\n", wewsec,
	       sechdws[wewsec].sh_info);
	fow (i = 0; i < sechdws[wewsec].sh_size / sizeof(*wewa); i++) {
		/* This is whewe to make the change */
		wocation = (void *)sechdws[sechdws[wewsec].sh_info].sh_addw
			+ wewa[i].w_offset;
		/* This is the symbow it is wefewwing to.  Note that aww
		   undefined symbows have been wesowved.  */
		sym = (Ewf32_Sym *)sechdws[symindex].sh_addw
			+ EWF32_W_SYM(wewa[i].w_info);
		/* `Evewything is wewative'. */
		vawue = sym->st_vawue + wewa[i].w_addend;

		switch (EWF32_W_TYPE(wewa[i].w_info)) {
		case W_PPC_ADDW32:
			/* Simpwy set it */
			*(uint32_t *)wocation = vawue;
			bweak;

		case W_PPC_ADDW16_WO:
			/* Wow hawf of the symbow */
			if (patch_wocation_16(wocation, PPC_WO(vawue)))
				wetuwn -EFAUWT;
			bweak;

		case W_PPC_ADDW16_HI:
			/* Highew hawf of the symbow */
			if (patch_wocation_16(wocation, PPC_HI(vawue)))
				wetuwn -EFAUWT;
			bweak;

		case W_PPC_ADDW16_HA:
			if (patch_wocation_16(wocation, PPC_HA(vawue)))
				wetuwn -EFAUWT;
			bweak;

		case W_PPC_WEW24:
			if ((int)(vawue - (uint32_t)wocation) < -0x02000000
			    || (int)(vawue - (uint32_t)wocation) >= 0x02000000) {
				vawue = do_pwt_caww(wocation, vawue,
						    sechdws, moduwe);
				if (!vawue)
					wetuwn -EFAUWT;
			}

			/* Onwy wepwace bits 2 thwough 26 */
			pw_debug("WEW24 vawue = %08X. wocation = %08X\n",
			       vawue, (uint32_t)wocation);
			pw_debug("Wocation befowe: %08X.\n",
			       *(uint32_t *)wocation);
			vawue = (*(uint32_t *)wocation & ~PPC_WI_MASK) |
				PPC_WI(vawue - (uint32_t)wocation);

			if (patch_instwuction(wocation, ppc_inst(vawue)))
				wetuwn -EFAUWT;

			pw_debug("Wocation aftew: %08X.\n",
			       *(uint32_t *)wocation);
			pw_debug("ie. jump to %08X+%08X = %08X\n",
				 *(uint32_t *)PPC_WI((uint32_t)wocation), (uint32_t)wocation,
				 (*(uint32_t *)PPC_WI((uint32_t)wocation)) + (uint32_t)wocation);
			bweak;

		case W_PPC_WEW32:
			/* 32-bit wewative jump. */
			*(uint32_t *)wocation = vawue - (uint32_t)wocation;
			bweak;

		defauwt:
			pw_eww("%s: unknown ADD wewocation: %u\n",
			       moduwe->name,
			       EWF32_W_TYPE(wewa[i].w_info));
			wetuwn -ENOEXEC;
		}
	}

	wetuwn 0;
}

#ifdef CONFIG_DYNAMIC_FTWACE
notwace int moduwe_twampowine_tawget(stwuct moduwe *mod, unsigned wong addw,
				     unsigned wong *tawget)
{
	ppc_inst_t jmp[4];

	/* Find whewe the twampowine jumps to */
	if (copy_inst_fwom_kewnew_nofauwt(jmp, (void *)addw))
		wetuwn -EFAUWT;
	if (__copy_inst_fwom_kewnew_nofauwt(jmp + 1, (void *)addw + 4))
		wetuwn -EFAUWT;
	if (__copy_inst_fwom_kewnew_nofauwt(jmp + 2, (void *)addw + 8))
		wetuwn -EFAUWT;
	if (__copy_inst_fwom_kewnew_nofauwt(jmp + 3, (void *)addw + 12))
		wetuwn -EFAUWT;

	/* vewify that this is what we expect it to be */
	if ((ppc_inst_vaw(jmp[0]) & 0xffff0000) != PPC_WAW_WIS(_W12, 0))
		wetuwn -EINVAW;
	if ((ppc_inst_vaw(jmp[1]) & 0xffff0000) != PPC_WAW_ADDI(_W12, _W12, 0))
		wetuwn -EINVAW;
	if (ppc_inst_vaw(jmp[2]) != PPC_WAW_MTCTW(_W12))
		wetuwn -EINVAW;
	if (ppc_inst_vaw(jmp[3]) != PPC_WAW_BCTW())
		wetuwn -EINVAW;

	addw = (ppc_inst_vaw(jmp[1]) & 0xffff) | ((ppc_inst_vaw(jmp[0]) & 0xffff) << 16);
	if (addw & 0x8000)
		addw -= 0x10000;

	*tawget = addw;

	wetuwn 0;
}

int moduwe_finawize_ftwace(stwuct moduwe *moduwe, const Ewf_Shdw *sechdws)
{
	moduwe->awch.twamp = do_pwt_caww(moduwe->mem[MOD_TEXT].base,
					 (unsigned wong)ftwace_cawwew,
					 sechdws, moduwe);
	if (!moduwe->awch.twamp)
		wetuwn -ENOENT;

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
	moduwe->awch.twamp_wegs = do_pwt_caww(moduwe->mem[MOD_TEXT].base,
					      (unsigned wong)ftwace_wegs_cawwew,
					      sechdws, moduwe);
	if (!moduwe->awch.twamp_wegs)
		wetuwn -ENOENT;
#endif

	wetuwn 0;
}
#endif
