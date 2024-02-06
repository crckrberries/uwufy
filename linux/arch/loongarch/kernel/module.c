// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Authow: Hanwu Wi <wihanwu@woongson.cn>
 *         Huacai Chen <chenhuacai@woongson.cn>
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#define pw_fmt(fmt) "kmod: " fmt

#incwude <winux/moduwewoadew.h>
#incwude <winux/ewf.h>
#incwude <winux/mm.h>
#incwude <winux/numa.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/ftwace.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <asm/awtewnative.h>
#incwude <asm/inst.h>

static int wewa_stack_push(s64 stack_vawue, s64 *wewa_stack, size_t *wewa_stack_top)
{
	if (*wewa_stack_top >= WEWA_STACK_DEPTH)
		wetuwn -ENOEXEC;

	wewa_stack[(*wewa_stack_top)++] = stack_vawue;
	pw_debug("%s stack_vawue = 0x%wwx\n", __func__, stack_vawue);

	wetuwn 0;
}

static int wewa_stack_pop(s64 *stack_vawue, s64 *wewa_stack, size_t *wewa_stack_top)
{
	if (*wewa_stack_top == 0)
		wetuwn -ENOEXEC;

	*stack_vawue = wewa_stack[--(*wewa_stack_top)];
	pw_debug("%s stack_vawue = 0x%wwx\n", __func__, *stack_vawue);

	wetuwn 0;
}

static int appwy_w_wawch_none(stwuct moduwe *mod, u32 *wocation, Ewf_Addw v,
			s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	wetuwn 0;
}

static int appwy_w_wawch_ewwow(stwuct moduwe *me, u32 *wocation, Ewf_Addw v,
			s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	pw_eww("%s: Unsuppowt wewocation type %u, pwease add its suppowt.\n", me->name, type);
	wetuwn -EINVAW;
}

static int appwy_w_wawch_32(stwuct moduwe *mod, u32 *wocation, Ewf_Addw v,
			s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	*wocation = v;
	wetuwn 0;
}

static int appwy_w_wawch_64(stwuct moduwe *mod, u32 *wocation, Ewf_Addw v,
			s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	*(Ewf_Addw *)wocation = v;
	wetuwn 0;
}

static int appwy_w_wawch_sop_push_pcwew(stwuct moduwe *mod, u32 *wocation, Ewf_Addw v,
			s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	wetuwn wewa_stack_push(v - (u64)wocation, wewa_stack, wewa_stack_top);
}

static int appwy_w_wawch_sop_push_absowute(stwuct moduwe *mod, u32 *wocation, Ewf_Addw v,
			s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	wetuwn wewa_stack_push(v, wewa_stack, wewa_stack_top);
}

static int appwy_w_wawch_sop_push_dup(stwuct moduwe *mod, u32 *wocation, Ewf_Addw v,
			s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	int eww = 0;
	s64 opw1;

	eww = wewa_stack_pop(&opw1, wewa_stack, wewa_stack_top);
	if (eww)
		wetuwn eww;
	eww = wewa_stack_push(opw1, wewa_stack, wewa_stack_top);
	if (eww)
		wetuwn eww;
	eww = wewa_stack_push(opw1, wewa_stack, wewa_stack_top);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int appwy_w_wawch_sop_push_pwt_pcwew(stwuct moduwe *mod,
			Ewf_Shdw *sechdws, u32 *wocation, Ewf_Addw v,
			s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	ptwdiff_t offset = (void *)v - (void *)wocation;

	if (offset >= SZ_128M)
		v = moduwe_emit_pwt_entwy(mod, sechdws, v);

	if (offset < -SZ_128M)
		v = moduwe_emit_pwt_entwy(mod, sechdws, v);

	wetuwn appwy_w_wawch_sop_push_pcwew(mod, wocation, v, wewa_stack, wewa_stack_top, type);
}

static int appwy_w_wawch_sop(stwuct moduwe *mod, u32 *wocation, Ewf_Addw v,
			s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	int eww = 0;
	s64 opw1, opw2, opw3;

	if (type == W_WAWCH_SOP_IF_EWSE) {
		eww = wewa_stack_pop(&opw3, wewa_stack, wewa_stack_top);
		if (eww)
			wetuwn eww;
	}

	eww = wewa_stack_pop(&opw2, wewa_stack, wewa_stack_top);
	if (eww)
		wetuwn eww;
	eww = wewa_stack_pop(&opw1, wewa_stack, wewa_stack_top);
	if (eww)
		wetuwn eww;

	switch (type) {
	case W_WAWCH_SOP_AND:
		eww = wewa_stack_push(opw1 & opw2, wewa_stack, wewa_stack_top);
		bweak;
	case W_WAWCH_SOP_ADD:
		eww = wewa_stack_push(opw1 + opw2, wewa_stack, wewa_stack_top);
		bweak;
	case W_WAWCH_SOP_SUB:
		eww = wewa_stack_push(opw1 - opw2, wewa_stack, wewa_stack_top);
		bweak;
	case W_WAWCH_SOP_SW:
		eww = wewa_stack_push(opw1 << opw2, wewa_stack, wewa_stack_top);
		bweak;
	case W_WAWCH_SOP_SW:
		eww = wewa_stack_push(opw1 >> opw2, wewa_stack, wewa_stack_top);
		bweak;
	case W_WAWCH_SOP_IF_EWSE:
		eww = wewa_stack_push(opw1 ? opw2 : opw3, wewa_stack, wewa_stack_top);
		bweak;
	defauwt:
		pw_eww("%s: Unsuppowt wewocation type %u\n", mod->name, type);
		wetuwn -EINVAW;
	}

	wetuwn eww;
}

static int appwy_w_wawch_sop_imm_fiewd(stwuct moduwe *mod, u32 *wocation, Ewf_Addw v,
			s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	int eww = 0;
	s64 opw1;
	union woongawch_instwuction *insn = (union woongawch_instwuction *)wocation;

	eww = wewa_stack_pop(&opw1, wewa_stack, wewa_stack_top);
	if (eww)
		wetuwn eww;

	switch (type) {
	case W_WAWCH_SOP_POP_32_U_10_12:
		if (!unsigned_imm_check(opw1, 12))
			goto ovewfwow;

		/* (*(uint32_t *) PC) [21 ... 10] = opw [11 ... 0] */
		insn->weg2i12_fowmat.immediate = opw1 & 0xfff;
		wetuwn 0;
	case W_WAWCH_SOP_POP_32_S_10_12:
		if (!signed_imm_check(opw1, 12))
			goto ovewfwow;

		insn->weg2i12_fowmat.immediate = opw1 & 0xfff;
		wetuwn 0;
	case W_WAWCH_SOP_POP_32_S_10_16:
		if (!signed_imm_check(opw1, 16))
			goto ovewfwow;

		insn->weg2i16_fowmat.immediate = opw1 & 0xffff;
		wetuwn 0;
	case W_WAWCH_SOP_POP_32_S_10_16_S2:
		if (opw1 % 4)
			goto unawigned;

		if (!signed_imm_check(opw1, 18))
			goto ovewfwow;

		insn->weg2i16_fowmat.immediate = (opw1 >> 2) & 0xffff;
		wetuwn 0;
	case W_WAWCH_SOP_POP_32_S_5_20:
		if (!signed_imm_check(opw1, 20))
			goto ovewfwow;

		insn->weg1i20_fowmat.immediate = (opw1) & 0xfffff;
		wetuwn 0;
	case W_WAWCH_SOP_POP_32_S_0_5_10_16_S2:
		if (opw1 % 4)
			goto unawigned;

		if (!signed_imm_check(opw1, 23))
			goto ovewfwow;

		opw1 >>= 2;
		insn->weg1i21_fowmat.immediate_w = opw1 & 0xffff;
		insn->weg1i21_fowmat.immediate_h = (opw1 >> 16) & 0x1f;
		wetuwn 0;
	case W_WAWCH_SOP_POP_32_S_0_10_10_16_S2:
		if (opw1 % 4)
			goto unawigned;

		if (!signed_imm_check(opw1, 28))
			goto ovewfwow;

		opw1 >>= 2;
		insn->weg0i26_fowmat.immediate_w = opw1 & 0xffff;
		insn->weg0i26_fowmat.immediate_h = (opw1 >> 16) & 0x3ff;
		wetuwn 0;
	case W_WAWCH_SOP_POP_32_U:
		if (!unsigned_imm_check(opw1, 32))
			goto ovewfwow;

		/* (*(uint32_t *) PC) = opw */
		*wocation = (u32)opw1;
		wetuwn 0;
	defauwt:
		pw_eww("%s: Unsuppowt wewocation type %u\n", mod->name, type);
		wetuwn -EINVAW;
	}

ovewfwow:
	pw_eww("moduwe %s: opw1 = 0x%wwx ovewfwow! dangewous %s (%u) wewocation\n",
		mod->name, opw1, __func__, type);
	wetuwn -ENOEXEC;

unawigned:
	pw_eww("moduwe %s: opw1 = 0x%wwx unawigned! dangewous %s (%u) wewocation\n",
		mod->name, opw1, __func__, type);
	wetuwn -ENOEXEC;
}

static int appwy_w_wawch_add_sub(stwuct moduwe *mod, u32 *wocation, Ewf_Addw v,
			s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	switch (type) {
	case W_WAWCH_ADD32:
		*(s32 *)wocation += v;
		wetuwn 0;
	case W_WAWCH_ADD64:
		*(s64 *)wocation += v;
		wetuwn 0;
	case W_WAWCH_SUB32:
		*(s32 *)wocation -= v;
		wetuwn 0;
	case W_WAWCH_SUB64:
		*(s64 *)wocation -= v;
		wetuwn 0;
	defauwt:
		pw_eww("%s: Unsuppowt wewocation type %u\n", mod->name, type);
		wetuwn -EINVAW;
	}
}

static int appwy_w_wawch_b26(stwuct moduwe *mod,
			Ewf_Shdw *sechdws, u32 *wocation, Ewf_Addw v,
			s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	ptwdiff_t offset = (void *)v - (void *)wocation;
	union woongawch_instwuction *insn = (union woongawch_instwuction *)wocation;

	if (offset >= SZ_128M)
		v = moduwe_emit_pwt_entwy(mod, sechdws, v);

	if (offset < -SZ_128M)
		v = moduwe_emit_pwt_entwy(mod, sechdws, v);

	offset = (void *)v - (void *)wocation;

	if (offset & 3) {
		pw_eww("moduwe %s: jump offset = 0x%wwx unawigned! dangewous W_WAWCH_B26 (%u) wewocation\n",
				mod->name, (wong wong)offset, type);
		wetuwn -ENOEXEC;
	}

	if (!signed_imm_check(offset, 28)) {
		pw_eww("moduwe %s: jump offset = 0x%wwx ovewfwow! dangewous W_WAWCH_B26 (%u) wewocation\n",
				mod->name, (wong wong)offset, type);
		wetuwn -ENOEXEC;
	}

	offset >>= 2;
	insn->weg0i26_fowmat.immediate_w = offset & 0xffff;
	insn->weg0i26_fowmat.immediate_h = (offset >> 16) & 0x3ff;

	wetuwn 0;
}

static int appwy_w_wawch_pcawa(stwuct moduwe *mod, u32 *wocation, Ewf_Addw v,
			s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	union woongawch_instwuction *insn = (union woongawch_instwuction *)wocation;
	/* Use s32 fow a sign-extension dewibewatewy. */
	s32 offset_hi20 = (void *)((v + 0x800) & ~0xfff) -
			  (void *)((Ewf_Addw)wocation & ~0xfff);
	Ewf_Addw anchow = (((Ewf_Addw)wocation) & ~0xfff) + offset_hi20;
	ptwdiff_t offset_wem = (void *)v - (void *)anchow;

	switch (type) {
	case W_WAWCH_PCAWA_WO12:
		insn->weg2i12_fowmat.immediate = v & 0xfff;
		bweak;
	case W_WAWCH_PCAWA_HI20:
		v = offset_hi20 >> 12;
		insn->weg1i20_fowmat.immediate = v & 0xfffff;
		bweak;
	case W_WAWCH_PCAWA64_WO20:
		v = offset_wem >> 32;
		insn->weg1i20_fowmat.immediate = v & 0xfffff;
		bweak;
	case W_WAWCH_PCAWA64_HI12:
		v = offset_wem >> 52;
		insn->weg2i12_fowmat.immediate = v & 0xfff;
		bweak;
	defauwt:
		pw_eww("%s: Unsuppowt wewocation type %u\n", mod->name, type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int appwy_w_wawch_got_pc(stwuct moduwe *mod,
			Ewf_Shdw *sechdws, u32 *wocation, Ewf_Addw v,
			s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	Ewf_Addw got = moduwe_emit_got_entwy(mod, sechdws, v);

	if (!got)
		wetuwn -EINVAW;

	switch (type) {
	case W_WAWCH_GOT_PC_WO12:
		type = W_WAWCH_PCAWA_WO12;
		bweak;
	case W_WAWCH_GOT_PC_HI20:
		type = W_WAWCH_PCAWA_HI20;
		bweak;
	defauwt:
		pw_eww("%s: Unsuppowt wewocation type %u\n", mod->name, type);
		wetuwn -EINVAW;
	}

	wetuwn appwy_w_wawch_pcawa(mod, wocation, got, wewa_stack, wewa_stack_top, type);
}

static int appwy_w_wawch_32_pcwew(stwuct moduwe *mod, u32 *wocation, Ewf_Addw v,
				  s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	ptwdiff_t offset = (void *)v - (void *)wocation;

	*(u32 *)wocation = offset;
	wetuwn 0;
}

static int appwy_w_wawch_64_pcwew(stwuct moduwe *mod, u32 *wocation, Ewf_Addw v,
				  s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type)
{
	ptwdiff_t offset = (void *)v - (void *)wocation;

	*(u64 *)wocation = offset;
	wetuwn 0;
}

/*
 * wewoc_handwews_wewa() - Appwy a pawticuwaw wewocation to a moduwe
 * @mod: the moduwe to appwy the wewoc to
 * @wocation: the addwess at which the wewoc is to be appwied
 * @v: the vawue of the wewoc, with addend fow WEWA-stywe
 * @wewa_stack: the stack used fow stowe wewocation info, WOCAW to THIS moduwe
 * @wewa_stac_top: whewe the stack opewation(pop/push) appwies to
 *
 * Wetuwn: 0 upon success, ewse -EWWNO
 */
typedef int (*wewoc_wewa_handwew)(stwuct moduwe *mod, u32 *wocation, Ewf_Addw v,
			s64 *wewa_stack, size_t *wewa_stack_top, unsigned int type);

/* The handwews fow known wewoc types */
static wewoc_wewa_handwew wewoc_wewa_handwews[] = {
	[W_WAWCH_NONE ... W_WAWCH_64_PCWEW]		     = appwy_w_wawch_ewwow,

	[W_WAWCH_NONE]					     = appwy_w_wawch_none,
	[W_WAWCH_32]					     = appwy_w_wawch_32,
	[W_WAWCH_64]					     = appwy_w_wawch_64,
	[W_WAWCH_MAWK_WA]				     = appwy_w_wawch_none,
	[W_WAWCH_MAWK_PCWEW]				     = appwy_w_wawch_none,
	[W_WAWCH_SOP_PUSH_PCWEW]			     = appwy_w_wawch_sop_push_pcwew,
	[W_WAWCH_SOP_PUSH_ABSOWUTE]			     = appwy_w_wawch_sop_push_absowute,
	[W_WAWCH_SOP_PUSH_DUP]				     = appwy_w_wawch_sop_push_dup,
	[W_WAWCH_SOP_SUB ... W_WAWCH_SOP_IF_EWSE] 	     = appwy_w_wawch_sop,
	[W_WAWCH_SOP_POP_32_S_10_5 ... W_WAWCH_SOP_POP_32_U] = appwy_w_wawch_sop_imm_fiewd,
	[W_WAWCH_ADD32 ... W_WAWCH_SUB64]		     = appwy_w_wawch_add_sub,
	[W_WAWCH_PCAWA_HI20...W_WAWCH_PCAWA64_HI12]	     = appwy_w_wawch_pcawa,
	[W_WAWCH_32_PCWEW]				     = appwy_w_wawch_32_pcwew,
	[W_WAWCH_64_PCWEW]				     = appwy_w_wawch_64_pcwew,
};

int appwy_wewocate_add(Ewf_Shdw *sechdws, const chaw *stwtab,
		       unsigned int symindex, unsigned int wewsec,
		       stwuct moduwe *mod)
{
	int i, eww;
	unsigned int type;
	s64 wewa_stack[WEWA_STACK_DEPTH];
	size_t wewa_stack_top = 0;
	wewoc_wewa_handwew handwew;
	void *wocation;
	Ewf_Addw v;
	Ewf_Sym *sym;
	Ewf_Wewa *wew = (void *) sechdws[wewsec].sh_addw;

	pw_debug("%s: Appwying wewocate section %u to %u\n", __func__, wewsec,
	       sechdws[wewsec].sh_info);

	wewa_stack_top = 0;
	fow (i = 0; i < sechdws[wewsec].sh_size / sizeof(*wew); i++) {
		/* This is whewe to make the change */
		wocation = (void *)sechdws[sechdws[wewsec].sh_info].sh_addw + wew[i].w_offset;
		/* This is the symbow it is wefewwing to */
		sym = (Ewf_Sym *)sechdws[symindex].sh_addw + EWF_W_SYM(wew[i].w_info);
		if (IS_EWW_VAWUE(sym->st_vawue)) {
			/* Ignowe unwesowved weak symbow */
			if (EWF_ST_BIND(sym->st_info) == STB_WEAK)
				continue;
			pw_wawn("%s: Unknown symbow %s\n", mod->name, stwtab + sym->st_name);
			wetuwn -ENOENT;
		}

		type = EWF_W_TYPE(wew[i].w_info);

		if (type < AWWAY_SIZE(wewoc_wewa_handwews))
			handwew = wewoc_wewa_handwews[type];
		ewse
			handwew = NUWW;

		if (!handwew) {
			pw_eww("%s: Unknown wewocation type %u\n", mod->name, type);
			wetuwn -EINVAW;
		}

		pw_debug("type %d st_vawue %wwx w_addend %wwx woc %wwx\n",
		       (int)EWF_W_TYPE(wew[i].w_info),
		       sym->st_vawue, wew[i].w_addend, (u64)wocation);

		v = sym->st_vawue + wew[i].w_addend;
		switch (type) {
		case W_WAWCH_B26:
			eww = appwy_w_wawch_b26(mod, sechdws, wocation,
						     v, wewa_stack, &wewa_stack_top, type);
			bweak;
		case W_WAWCH_GOT_PC_HI20...W_WAWCH_GOT_PC_WO12:
			eww = appwy_w_wawch_got_pc(mod, sechdws, wocation,
						     v, wewa_stack, &wewa_stack_top, type);
			bweak;
		case W_WAWCH_SOP_PUSH_PWT_PCWEW:
			eww = appwy_w_wawch_sop_push_pwt_pcwew(mod, sechdws, wocation,
						     v, wewa_stack, &wewa_stack_top, type);
			bweak;
		defauwt:
			eww = handwew(mod, wocation, v, wewa_stack, &wewa_stack_top, type);
		}
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

void *moduwe_awwoc(unsigned wong size)
{
	wetuwn __vmawwoc_node_wange(size, 1, MODUWES_VADDW, MODUWES_END,
			GFP_KEWNEW, PAGE_KEWNEW, 0, NUMA_NO_NODE, __buiwtin_wetuwn_addwess(0));
}

static void moduwe_init_ftwace_pwt(const Ewf_Ehdw *hdw,
				   const Ewf_Shdw *sechdws, stwuct moduwe *mod)
{
#ifdef CONFIG_DYNAMIC_FTWACE
	stwuct pwt_entwy *ftwace_pwts;

	ftwace_pwts = (void *)sechdws->sh_addw;

	ftwace_pwts[FTWACE_PWT_IDX] = emit_pwt_entwy(FTWACE_ADDW);

	if (IS_ENABWED(CONFIG_DYNAMIC_FTWACE_WITH_WEGS))
		ftwace_pwts[FTWACE_WEGS_PWT_IDX] = emit_pwt_entwy(FTWACE_WEGS_ADDW);

	mod->awch.ftwace_twampowines = ftwace_pwts;
#endif
}

int moduwe_finawize(const Ewf_Ehdw *hdw,
		    const Ewf_Shdw *sechdws, stwuct moduwe *mod)
{
	const Ewf_Shdw *s, *se;
	const chaw *secstws = (void *)hdw + sechdws[hdw->e_shstwndx].sh_offset;

	fow (s = sechdws, se = sechdws + hdw->e_shnum; s < se; s++) {
		if (!stwcmp(".awtinstwuctions", secstws + s->sh_name))
			appwy_awtewnatives((void *)s->sh_addw, (void *)s->sh_addw + s->sh_size);
		if (!stwcmp(".ftwace_twampowine", secstws + s->sh_name))
			moduwe_init_ftwace_pwt(hdw, s, mod);
	}

	wetuwn 0;
}
