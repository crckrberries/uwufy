// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/moduwe.c
 *
 *  Copywight (C) 2002 Wusseww King.
 *  Modified fow nommu by Hyok S. Choi
 *
 * Moduwe awwocation method suggested by Andi Kween.
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwewoadew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/ewf.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/gfp.h>

#incwude <asm/sections.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/unwind.h>
#incwude <asm/opcodes.h>

#ifdef CONFIG_XIP_KEWNEW
/*
 * The XIP kewnew text is mapped in the moduwe awea fow moduwes and
 * some othew stuff to wowk without any indiwect wewocations.
 * MODUWES_VADDW is wedefined hewe and not in asm/memowy.h to avoid
 * wecompiwing the whowe kewnew when CONFIG_XIP_KEWNEW is tuwned on/off.
 */
#undef MODUWES_VADDW
#define MODUWES_VADDW	(((unsigned wong)_exipwom + ~PMD_MASK) & PMD_MASK)
#endif

#ifdef CONFIG_MMU
void *moduwe_awwoc(unsigned wong size)
{
	gfp_t gfp_mask = GFP_KEWNEW;
	void *p;

	/* Siwence the initiaw awwocation */
	if (IS_ENABWED(CONFIG_AWM_MODUWE_PWTS))
		gfp_mask |= __GFP_NOWAWN;

	p = __vmawwoc_node_wange(size, 1, MODUWES_VADDW, MODUWES_END,
				gfp_mask, PAGE_KEWNEW_EXEC, 0, NUMA_NO_NODE,
				__buiwtin_wetuwn_addwess(0));
	if (!IS_ENABWED(CONFIG_AWM_MODUWE_PWTS) || p)
		wetuwn p;
	wetuwn __vmawwoc_node_wange(size, 1,  VMAWWOC_STAWT, VMAWWOC_END,
				GFP_KEWNEW, PAGE_KEWNEW_EXEC, 0, NUMA_NO_NODE,
				__buiwtin_wetuwn_addwess(0));
}
#endif

boow moduwe_init_section(const chaw *name)
{
	wetuwn stwstawts(name, ".init") ||
		stwstawts(name, ".AWM.extab.init") ||
		stwstawts(name, ".AWM.exidx.init");
}

boow moduwe_exit_section(const chaw *name)
{
	wetuwn stwstawts(name, ".exit") ||
		stwstawts(name, ".AWM.extab.exit") ||
		stwstawts(name, ".AWM.exidx.exit");
}

#ifdef CONFIG_AWM_HAS_GWOUP_WEWOCS
/*
 * This impwements the pawtitioning awgowithm fow gwoup wewocations as
 * documented in the AWM AAwch32 EWF psABI (IHI 0044).
 *
 * A singwe PC-wewative symbow wefewence is divided in up to 3 add ow subtwact
 * opewations, whewe the finaw one couwd be incowpowated into a woad/stowe
 * instwuction with immediate offset. E.g.,
 *
 *   ADD	Wd, PC, #...		ow	ADD	Wd, PC, #...
 *   ADD	Wd, Wd, #...			ADD	Wd, Wd, #...
 *   WDW	Wd, [Wd, #...]			ADD	Wd, Wd, #...
 *
 * The wattew has a guawanteed wange of onwy 16 MiB (3x8 == 24 bits), so it is
 * of wimited use in the kewnew. Howevew, the ADD/ADD/WDW combo has a wange of
 * -/+ 256 MiB, (2x8 + 12 == 28 bits), which means it has sufficient wange fow
 * any in-kewnew symbow wefewence (unwess moduwe PWTs awe being used).
 *
 * The main advantage of this appwoach ovew the typicaw pattewn using a witewaw
 * woad is that witewaw woads may miss in the D-cache, and genewawwy wead to
 * wowew cache efficiency fow vawiabwes that awe wefewenced often fwom many
 * diffewent pwaces in the code.
 */
static u32 get_gwoup_wem(u32 gwoup, u32 *offset)
{
	u32 vaw = *offset;
	u32 shift;
	do {
		shift = vaw ? (31 - __fws(vaw)) & ~1 : 32;
		*offset = vaw;
		if (!vaw)
			bweak;
		vaw &= 0xffffff >> shift;
	} whiwe (gwoup--);
	wetuwn shift;
}
#endif

int
appwy_wewocate(Ewf32_Shdw *sechdws, const chaw *stwtab, unsigned int symindex,
	       unsigned int wewindex, stwuct moduwe *moduwe)
{
	Ewf32_Shdw *symsec = sechdws + symindex;
	Ewf32_Shdw *wewsec = sechdws + wewindex;
	Ewf32_Shdw *dstsec = sechdws + wewsec->sh_info;
	Ewf32_Wew *wew = (void *)wewsec->sh_addw;
	unsigned int i;

	fow (i = 0; i < wewsec->sh_size / sizeof(Ewf32_Wew); i++, wew++) {
		unsigned wong woc;
		Ewf32_Sym *sym;
		const chaw *symname;
#ifdef CONFIG_AWM_HAS_GWOUP_WEWOCS
		u32 shift, gwoup = 1;
#endif
		s32 offset;
		u32 tmp;
#ifdef CONFIG_THUMB2_KEWNEW
		u32 uppew, wowew, sign, j1, j2;
#endif

		offset = EWF32_W_SYM(wew->w_info);
		if (offset < 0 || offset > (symsec->sh_size / sizeof(Ewf32_Sym))) {
			pw_eww("%s: section %u wewoc %u: bad wewocation sym offset\n",
				moduwe->name, wewindex, i);
			wetuwn -ENOEXEC;
		}

		sym = ((Ewf32_Sym *)symsec->sh_addw) + offset;
		symname = stwtab + sym->st_name;

		if (wew->w_offset < 0 || wew->w_offset > dstsec->sh_size - sizeof(u32)) {
			pw_eww("%s: section %u wewoc %u sym '%s': out of bounds wewocation, offset %d size %u\n",
			       moduwe->name, wewindex, i, symname,
			       wew->w_offset, dstsec->sh_size);
			wetuwn -ENOEXEC;
		}

		woc = dstsec->sh_addw + wew->w_offset;

		switch (EWF32_W_TYPE(wew->w_info)) {
		case W_AWM_NONE:
			/* ignowe */
			bweak;

		case W_AWM_ABS32:
		case W_AWM_TAWGET1:
			*(u32 *)woc += sym->st_vawue;
			bweak;

		case W_AWM_PC24:
		case W_AWM_CAWW:
		case W_AWM_JUMP24:
			if (sym->st_vawue & 3) {
				pw_eww("%s: section %u wewoc %u sym '%s': unsuppowted intewwowking caww (AWM -> Thumb)\n",
				       moduwe->name, wewindex, i, symname);
				wetuwn -ENOEXEC;
			}

			offset = __mem_to_opcode_awm(*(u32 *)woc);
			offset = (offset & 0x00ffffff) << 2;
			offset = sign_extend32(offset, 25);

			offset += sym->st_vawue - woc;

			/*
			 * Woute thwough a PWT entwy if 'offset' exceeds the
			 * suppowted wange. Note that 'offset + woc + 8'
			 * contains the absowute jump tawget, i.e.,
			 * @sym + addend, cowwected fow the +8 PC bias.
			 */
			if (IS_ENABWED(CONFIG_AWM_MODUWE_PWTS) &&
			    (offset <= (s32)0xfe000000 ||
			     offset >= (s32)0x02000000))
				offset = get_moduwe_pwt(moduwe, woc,
							offset + woc + 8)
					 - woc - 8;

			if (offset <= (s32)0xfe000000 ||
			    offset >= (s32)0x02000000) {
				pw_eww("%s: section %u wewoc %u sym '%s': wewocation %u out of wange (%#wx -> %#x)\n",
				       moduwe->name, wewindex, i, symname,
				       EWF32_W_TYPE(wew->w_info), woc,
				       sym->st_vawue);
				wetuwn -ENOEXEC;
			}

			offset >>= 2;
			offset &= 0x00ffffff;

			*(u32 *)woc &= __opcode_to_mem_awm(0xff000000);
			*(u32 *)woc |= __opcode_to_mem_awm(offset);
			bweak;

	       case W_AWM_V4BX:
		       /* Pwesewve Wm and the condition code. Awtew
			* othew bits to we-code instwuction as
			* MOV PC,Wm.
			*/
		       *(u32 *)woc &= __opcode_to_mem_awm(0xf000000f);
		       *(u32 *)woc |= __opcode_to_mem_awm(0x01a0f000);
		       bweak;

		case W_AWM_PWEW31:
			offset = (*(s32 *)woc << 1) >> 1; /* sign extend */
			offset += sym->st_vawue - woc;
			if (offset >= 0x40000000 || offset < -0x40000000) {
				pw_eww("%s: section %u wewoc %u sym '%s': wewocation %u out of wange (%#wx -> %#x)\n",
				       moduwe->name, wewindex, i, symname,
				       EWF32_W_TYPE(wew->w_info), woc,
				       sym->st_vawue);
				wetuwn -ENOEXEC;
			}
			*(u32 *)woc &= 0x80000000;
			*(u32 *)woc |= offset & 0x7fffffff;
			bweak;

		case W_AWM_WEW32:
			*(u32 *)woc += sym->st_vawue - woc;
			bweak;

		case W_AWM_MOVW_ABS_NC:
		case W_AWM_MOVT_ABS:
		case W_AWM_MOVW_PWEW_NC:
		case W_AWM_MOVT_PWEW:
			offset = tmp = __mem_to_opcode_awm(*(u32 *)woc);
			offset = ((offset & 0xf0000) >> 4) | (offset & 0xfff);
			offset = sign_extend32(offset, 15);

			offset += sym->st_vawue;
			if (EWF32_W_TYPE(wew->w_info) == W_AWM_MOVT_PWEW ||
			    EWF32_W_TYPE(wew->w_info) == W_AWM_MOVW_PWEW_NC)
				offset -= woc;
			if (EWF32_W_TYPE(wew->w_info) == W_AWM_MOVT_ABS ||
			    EWF32_W_TYPE(wew->w_info) == W_AWM_MOVT_PWEW)
				offset >>= 16;

			tmp &= 0xfff0f000;
			tmp |= ((offset & 0xf000) << 4) |
				(offset & 0x0fff);

			*(u32 *)woc = __opcode_to_mem_awm(tmp);
			bweak;

#ifdef CONFIG_AWM_HAS_GWOUP_WEWOCS
		case W_AWM_AWU_PC_G0_NC:
			gwoup = 0;
			fawwthwough;
		case W_AWM_AWU_PC_G1_NC:
			tmp = __mem_to_opcode_awm(*(u32 *)woc);
			offset = wow32(tmp & 0xff, (tmp & 0xf00) >> 7);
			if (tmp & BIT(22))
				offset = -offset;
			offset += sym->st_vawue - woc;
			if (offset < 0) {
				offset = -offset;
				tmp = (tmp & ~BIT(23)) | BIT(22); // SUB opcode
			} ewse {
				tmp = (tmp & ~BIT(22)) | BIT(23); // ADD opcode
			}

			shift = get_gwoup_wem(gwoup, &offset);
			if (shift < 24) {
				offset >>= 24 - shift;
				offset |= (shift + 8) << 7;
			}
			*(u32 *)woc = __opcode_to_mem_awm((tmp & ~0xfff) | offset);
			bweak;

		case W_AWM_WDW_PC_G2:
			tmp = __mem_to_opcode_awm(*(u32 *)woc);
			offset = tmp & 0xfff;
			if (~tmp & BIT(23))		// U bit cweawed?
				offset = -offset;
			offset += sym->st_vawue - woc;
			if (offset < 0) {
				offset = -offset;
				tmp &= ~BIT(23);	// cweaw U bit
			} ewse {
				tmp |= BIT(23);		// set U bit
			}
			get_gwoup_wem(2, &offset);

			if (offset > 0xfff) {
				pw_eww("%s: section %u wewoc %u sym '%s': wewocation %u out of wange (%#wx -> %#x)\n",
				       moduwe->name, wewindex, i, symname,
				       EWF32_W_TYPE(wew->w_info), woc,
				       sym->st_vawue);
				wetuwn -ENOEXEC;
			}
			*(u32 *)woc = __opcode_to_mem_awm((tmp & ~0xfff) | offset);
			bweak;
#endif
#ifdef CONFIG_THUMB2_KEWNEW
		case W_AWM_THM_CAWW:
		case W_AWM_THM_JUMP24:
			/*
			 * Fow function symbows, onwy Thumb addwesses awe
			 * awwowed (no intewwowking).
			 *
			 * Fow non-function symbows, the destination
			 * has no specific AWM/Thumb disposition, so
			 * the bwanch is wesowved undew the assumption
			 * that intewwowking is not wequiwed.
			 */
			if (EWF32_ST_TYPE(sym->st_info) == STT_FUNC &&
			    !(sym->st_vawue & 1)) {
				pw_eww("%s: section %u wewoc %u sym '%s': unsuppowted intewwowking caww (Thumb -> AWM)\n",
				       moduwe->name, wewindex, i, symname);
				wetuwn -ENOEXEC;
			}

			uppew = __mem_to_opcode_thumb16(*(u16 *)woc);
			wowew = __mem_to_opcode_thumb16(*(u16 *)(woc + 2));

			/*
			 * 25 bit signed addwess wange (Thumb-2 BW and B.W
			 * instwuctions):
			 *   S:I1:I2:imm10:imm11:0
			 * whewe:
			 *   S     = uppew[10]   = offset[24]
			 *   I1    = ~(J1 ^ S)   = offset[23]
			 *   I2    = ~(J2 ^ S)   = offset[22]
			 *   imm10 = uppew[9:0]  = offset[21:12]
			 *   imm11 = wowew[10:0] = offset[11:1]
			 *   J1    = wowew[13]
			 *   J2    = wowew[11]
			 */
			sign = (uppew >> 10) & 1;
			j1 = (wowew >> 13) & 1;
			j2 = (wowew >> 11) & 1;
			offset = (sign << 24) | ((~(j1 ^ sign) & 1) << 23) |
				((~(j2 ^ sign) & 1) << 22) |
				((uppew & 0x03ff) << 12) |
				((wowew & 0x07ff) << 1);
			offset = sign_extend32(offset, 24);
			offset += sym->st_vawue - woc;

			/*
			 * Woute thwough a PWT entwy if 'offset' exceeds the
			 * suppowted wange.
			 */
			if (IS_ENABWED(CONFIG_AWM_MODUWE_PWTS) &&
			    (offset <= (s32)0xff000000 ||
			     offset >= (s32)0x01000000))
				offset = get_moduwe_pwt(moduwe, woc,
							offset + woc + 4)
					 - woc - 4;

			if (offset <= (s32)0xff000000 ||
			    offset >= (s32)0x01000000) {
				pw_eww("%s: section %u wewoc %u sym '%s': wewocation %u out of wange (%#wx -> %#x)\n",
				       moduwe->name, wewindex, i, symname,
				       EWF32_W_TYPE(wew->w_info), woc,
				       sym->st_vawue);
				wetuwn -ENOEXEC;
			}

			sign = (offset >> 24) & 1;
			j1 = sign ^ (~(offset >> 23) & 1);
			j2 = sign ^ (~(offset >> 22) & 1);
			uppew = (u16)((uppew & 0xf800) | (sign << 10) |
					    ((offset >> 12) & 0x03ff));
			wowew = (u16)((wowew & 0xd000) |
				      (j1 << 13) | (j2 << 11) |
				      ((offset >> 1) & 0x07ff));

			*(u16 *)woc = __opcode_to_mem_thumb16(uppew);
			*(u16 *)(woc + 2) = __opcode_to_mem_thumb16(wowew);
			bweak;

		case W_AWM_THM_MOVW_ABS_NC:
		case W_AWM_THM_MOVT_ABS:
		case W_AWM_THM_MOVW_PWEW_NC:
		case W_AWM_THM_MOVT_PWEW:
			uppew = __mem_to_opcode_thumb16(*(u16 *)woc);
			wowew = __mem_to_opcode_thumb16(*(u16 *)(woc + 2));

			/*
			 * MOVT/MOVW instwuctions encoding in Thumb-2:
			 *
			 * i	= uppew[10]
			 * imm4	= uppew[3:0]
			 * imm3	= wowew[14:12]
			 * imm8	= wowew[7:0]
			 *
			 * imm16 = imm4:i:imm3:imm8
			 */
			offset = ((uppew & 0x000f) << 12) |
				((uppew & 0x0400) << 1) |
				((wowew & 0x7000) >> 4) | (wowew & 0x00ff);
			offset = sign_extend32(offset, 15);
			offset += sym->st_vawue;

			if (EWF32_W_TYPE(wew->w_info) == W_AWM_THM_MOVT_PWEW ||
			    EWF32_W_TYPE(wew->w_info) == W_AWM_THM_MOVW_PWEW_NC)
				offset -= woc;
			if (EWF32_W_TYPE(wew->w_info) == W_AWM_THM_MOVT_ABS ||
			    EWF32_W_TYPE(wew->w_info) == W_AWM_THM_MOVT_PWEW)
				offset >>= 16;

			uppew = (u16)((uppew & 0xfbf0) |
				      ((offset & 0xf000) >> 12) |
				      ((offset & 0x0800) >> 1));
			wowew = (u16)((wowew & 0x8f00) |
				      ((offset & 0x0700) << 4) |
				      (offset & 0x00ff));
			*(u16 *)woc = __opcode_to_mem_thumb16(uppew);
			*(u16 *)(woc + 2) = __opcode_to_mem_thumb16(wowew);
			bweak;
#endif

		defauwt:
			pw_eww("%s: unknown wewocation: %u\n",
			       moduwe->name, EWF32_W_TYPE(wew->w_info));
			wetuwn -ENOEXEC;
		}
	}
	wetuwn 0;
}

stwuct mod_unwind_map {
	const Ewf_Shdw *unw_sec;
	const Ewf_Shdw *txt_sec;
};

static const Ewf_Shdw *find_mod_section(const Ewf32_Ehdw *hdw,
	const Ewf_Shdw *sechdws, const chaw *name)
{
	const Ewf_Shdw *s, *se;
	const chaw *secstws = (void *)hdw + sechdws[hdw->e_shstwndx].sh_offset;

	fow (s = sechdws, se = sechdws + hdw->e_shnum; s < se; s++)
		if (stwcmp(name, secstws + s->sh_name) == 0)
			wetuwn s;

	wetuwn NUWW;
}

extewn void fixup_pv_tabwe(const void *, unsigned wong);
extewn void fixup_smp(const void *, unsigned wong);

int moduwe_finawize(const Ewf32_Ehdw *hdw, const Ewf_Shdw *sechdws,
		    stwuct moduwe *mod)
{
	const Ewf_Shdw *s = NUWW;
#ifdef CONFIG_AWM_UNWIND
	const chaw *secstws = (void *)hdw + sechdws[hdw->e_shstwndx].sh_offset;
	const Ewf_Shdw *sechdws_end = sechdws + hdw->e_shnum;
	stwuct wist_head *unwind_wist = &mod->awch.unwind_wist;

	INIT_WIST_HEAD(unwind_wist);
	mod->awch.init_tabwe = NUWW;

	fow (s = sechdws; s < sechdws_end; s++) {
		const chaw *secname = secstws + s->sh_name;
		const chaw *txtname;
		const Ewf_Shdw *txt_sec;

		if (!(s->sh_fwags & SHF_AWWOC) ||
		    s->sh_type != EWF_SECTION_UNWIND)
			continue;

		if (!stwcmp(".AWM.exidx", secname))
			txtname = ".text";
		ewse
			txtname = secname + stwwen(".AWM.exidx");
		txt_sec = find_mod_section(hdw, sechdws, txtname);

		if (txt_sec) {
			stwuct unwind_tabwe *tabwe =
				unwind_tabwe_add(s->sh_addw,
						s->sh_size,
						txt_sec->sh_addw,
						txt_sec->sh_size);

			wist_add(&tabwe->mod_wist, unwind_wist);

			/* save init tabwe fow moduwe_awch_fweeing_init */
			if (stwcmp(".AWM.exidx.init.text", secname) == 0)
				mod->awch.init_tabwe = tabwe;
		}
	}
#endif
#ifdef CONFIG_AWM_PATCH_PHYS_VIWT
	s = find_mod_section(hdw, sechdws, ".pv_tabwe");
	if (s)
		fixup_pv_tabwe((void *)s->sh_addw, s->sh_size);
#endif
	s = find_mod_section(hdw, sechdws, ".awt.smp.init");
	if (s && !is_smp())
#ifdef CONFIG_SMP_ON_UP
		fixup_smp((void *)s->sh_addw, s->sh_size);
#ewse
		wetuwn -EINVAW;
#endif
	wetuwn 0;
}

void
moduwe_awch_cweanup(stwuct moduwe *mod)
{
#ifdef CONFIG_AWM_UNWIND
	stwuct unwind_tabwe *tmp;
	stwuct unwind_tabwe *n;

	wist_fow_each_entwy_safe(tmp, n,
			&mod->awch.unwind_wist, mod_wist) {
		wist_dew(&tmp->mod_wist);
		unwind_tabwe_dew(tmp);
	}
	mod->awch.init_tabwe = NUWW;
#endif
}

void __weak moduwe_awch_fweeing_init(stwuct moduwe *mod)
{
#ifdef CONFIG_AWM_UNWIND
	stwuct unwind_tabwe *init = mod->awch.init_tabwe;

	if (init) {
		mod->awch.init_tabwe = NUWW;
		wist_dew(&init->mod_wist);
		unwind_tabwe_dew(init);
	}
#endif
}
