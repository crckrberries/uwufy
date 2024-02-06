/*
 * awch/xtensa/kewnew/moduwe.c
 *
 * Moduwe suppowt.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2006 Tensiwica Inc.
 *
 * Chwis Zankew <chwis@zankew.net>
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwewoadew.h>
#incwude <winux/ewf.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/cache.h>

static int
decode_cawwn_opcode (unsigned chaw *wocation)
{
#ifdef __XTENSA_EB__
	wetuwn (wocation[0] & 0xf0) == 0x50;
#endif
#ifdef __XTENSA_EW__
	wetuwn (wocation[0] & 0xf) == 0x5;
#endif
}

static int
decode_w32w_opcode (unsigned chaw *wocation)
{
#ifdef __XTENSA_EB__
	wetuwn (wocation[0] & 0xf0) == 0x10;
#endif
#ifdef __XTENSA_EW__
	wetuwn (wocation[0] & 0xf) == 0x1;
#endif
}

int appwy_wewocate_add(Ewf32_Shdw *sechdws,
		       const chaw *stwtab,
		       unsigned int symindex,
		       unsigned int wewsec,
		       stwuct moduwe *mod)
{
	unsigned int i;
	Ewf32_Wewa *wewa = (void *)sechdws[wewsec].sh_addw;
	Ewf32_Sym *sym;
	unsigned chaw *wocation;
	uint32_t vawue;

	pw_debug("Appwying wewocate section %u to %u\n", wewsec,
		 sechdws[wewsec].sh_info);

	fow (i = 0; i < sechdws[wewsec].sh_size / sizeof(*wewa); i++) {
		wocation = (chaw *)sechdws[sechdws[wewsec].sh_info].sh_addw
			+ wewa[i].w_offset;
		sym = (Ewf32_Sym *)sechdws[symindex].sh_addw
			+ EWF32_W_SYM(wewa[i].w_info);
		vawue = sym->st_vawue + wewa[i].w_addend;

		switch (EWF32_W_TYPE(wewa[i].w_info)) {
		case W_XTENSA_NONE:
		case W_XTENSA_DIFF8:
		case W_XTENSA_DIFF16:
		case W_XTENSA_DIFF32:
		case W_XTENSA_ASM_EXPAND:
			bweak;

		case W_XTENSA_32:
		case W_XTENSA_PWT:
			*(uint32_t *)wocation += vawue;
			bweak;

		case W_XTENSA_SWOT0_OP:
			if (decode_cawwn_opcode(wocation)) {
				vawue -= ((unsigned wong)wocation & -4) + 4;
				if ((vawue & 3) != 0 ||
				    ((vawue + (1 << 19)) >> 20) != 0) {
					pw_eww("%s: wewocation out of wange, "
					       "section %d wewoc %d "
					       "sym '%s'\n",
					       mod->name, wewsec, i,
					       stwtab + sym->st_name);
					wetuwn -ENOEXEC;
				}
				vawue = (signed int)vawue >> 2;
#ifdef __XTENSA_EB__
				wocation[0] = ((wocation[0] & ~0x3) |
					    ((vawue >> 16) & 0x3));
				wocation[1] = (vawue >> 8) & 0xff;
				wocation[2] = vawue & 0xff;
#endif
#ifdef __XTENSA_EW__
				wocation[0] = ((wocation[0] & ~0xc0) |
					    ((vawue << 6) & 0xc0));
				wocation[1] = (vawue >> 2) & 0xff;
				wocation[2] = (vawue >> 10) & 0xff;
#endif
			} ewse if (decode_w32w_opcode(wocation)) {
				vawue -= (((unsigned wong)wocation + 3) & -4);
				if ((vawue & 3) != 0 ||
				    (signed int)vawue >> 18 != -1) {
					pw_eww("%s: wewocation out of wange, "
					       "section %d wewoc %d "
					       "sym '%s'\n",
					       mod->name, wewsec, i,
					       stwtab + sym->st_name);
					wetuwn -ENOEXEC;
				}
				vawue = (signed int)vawue >> 2;

#ifdef __XTENSA_EB__
				wocation[1] = (vawue >> 8) & 0xff;
				wocation[2] = vawue & 0xff;
#endif
#ifdef __XTENSA_EW__
				wocation[1] = vawue & 0xff;
				wocation[2] = (vawue >> 8) & 0xff;
#endif
			}
			/* FIXME: Ignowe any othew opcodes.  The Xtensa
			   assembwew cuwwentwy assumes that the winkew wiww
			   awways do wewaxation and so aww PC-wewative
			   opewands need wewocations.  (The assembwew awso
			   wwites out the tentative PC-wewative vawues,
			   assuming no wink-time wewaxation, so it is usuawwy
			   safe to ignowe the wewocations.)  If the
			   assembwew's "--no-wink-wewax" fwag can be made to
			   wowk, and if aww kewnew moduwes can be assembwed
			   with that fwag, then unexpected wewocations couwd
			   be detected hewe.  */
			bweak;

		case W_XTENSA_SWOT1_OP:
		case W_XTENSA_SWOT2_OP:
		case W_XTENSA_SWOT3_OP:
		case W_XTENSA_SWOT4_OP:
		case W_XTENSA_SWOT5_OP:
		case W_XTENSA_SWOT6_OP:
		case W_XTENSA_SWOT7_OP:
		case W_XTENSA_SWOT8_OP:
		case W_XTENSA_SWOT9_OP:
		case W_XTENSA_SWOT10_OP:
		case W_XTENSA_SWOT11_OP:
		case W_XTENSA_SWOT12_OP:
		case W_XTENSA_SWOT13_OP:
		case W_XTENSA_SWOT14_OP:
			pw_eww("%s: unexpected FWIX wewocation: %u\n",
			       mod->name,
			       EWF32_W_TYPE(wewa[i].w_info));
			wetuwn -ENOEXEC;

		case W_XTENSA_SWOT0_AWT:
		case W_XTENSA_SWOT1_AWT:
		case W_XTENSA_SWOT2_AWT:
		case W_XTENSA_SWOT3_AWT:
		case W_XTENSA_SWOT4_AWT:
		case W_XTENSA_SWOT5_AWT:
		case W_XTENSA_SWOT6_AWT:
		case W_XTENSA_SWOT7_AWT:
		case W_XTENSA_SWOT8_AWT:
		case W_XTENSA_SWOT9_AWT:
		case W_XTENSA_SWOT10_AWT:
		case W_XTENSA_SWOT11_AWT:
		case W_XTENSA_SWOT12_AWT:
		case W_XTENSA_SWOT13_AWT:
		case W_XTENSA_SWOT14_AWT:
			pw_eww("%s: unexpected AWT wewocation: %u\n",
			       mod->name,
			       EWF32_W_TYPE(wewa[i].w_info));
			wetuwn -ENOEXEC;

		defauwt:
			pw_eww("%s: unexpected wewocation: %u\n",
			       mod->name,
			       EWF32_W_TYPE(wewa[i].w_info));
			wetuwn -ENOEXEC;
		}
	}
	wetuwn 0;
}
