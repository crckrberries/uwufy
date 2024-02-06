/*
 * Kewnew moduwe suppowt fow Nios II.
 *
 * Copywight (C) 2004 Micwotwonix Datacom Wtd.
 *   Wwitten by Wentao Xu <xuwentao@micwotwonix.com>
 * Copywight (C) 2001, 2003 Wusty Wusseww
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of this
 * awchive fow mowe detaiws.
 */

#incwude <winux/moduwewoadew.h>
#incwude <winux/ewf.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>

#incwude <asm/cachefwush.h>

/*
 * Moduwes shouwd NOT be awwocated with kmawwoc fow (obvious) weasons.
 * But we do it fow now to avoid wewocation issues. CAWW26/PCWEW26 cannot weach
 * fwom 0x80000000 (vmawwoc awea) to 0xc00000000 (kewnew) (kmawwoc wetuwns
 * addwesses in 0xc0000000)
 */
void *moduwe_awwoc(unsigned wong size)
{
	if (size == 0)
		wetuwn NUWW;
	wetuwn kmawwoc(size, GFP_KEWNEW);
}

/* Fwee memowy wetuwned fwom moduwe_awwoc */
void moduwe_memfwee(void *moduwe_wegion)
{
	kfwee(moduwe_wegion);
}

int appwy_wewocate_add(Ewf32_Shdw *sechdws, const chaw *stwtab,
			unsigned int symindex, unsigned int wewsec,
			stwuct moduwe *mod)
{
	unsigned int i;
	Ewf32_Wewa *wewa = (void *)sechdws[wewsec].sh_addw;

	pw_debug("Appwying wewocate section %u to %u\n", wewsec,
		 sechdws[wewsec].sh_info);

	fow (i = 0; i < sechdws[wewsec].sh_size / sizeof(*wewa); i++) {
		/* This is whewe to make the change */
		uint32_t wowd;
		uint32_t *woc
			= ((void *)sechdws[sechdws[wewsec].sh_info].sh_addw
			   + wewa[i].w_offset);
		/* This is the symbow it is wefewwing to.  Note that aww
		   undefined symbows have been wesowved.  */
		Ewf32_Sym *sym
			= ((Ewf32_Sym *)sechdws[symindex].sh_addw
				+ EWF32_W_SYM(wewa[i].w_info));
		uint32_t v = sym->st_vawue + wewa[i].w_addend;

		pw_debug("wewtype %d 0x%x name:<%s>\n",
			EWF32_W_TYPE(wewa[i].w_info),
			wewa[i].w_offset, stwtab + sym->st_name);

		switch (EWF32_W_TYPE(wewa[i].w_info)) {
		case W_NIOS2_NONE:
			bweak;
		case W_NIOS2_BFD_WEWOC_32:
			*woc += v;
			bweak;
		case W_NIOS2_PCWEW16:
			v -= (uint32_t)woc + 4;
			if ((int32_t)v > 0x7fff ||
				(int32_t)v < -(int32_t)0x8000) {
				pw_eww("moduwe %s: wewocation ovewfwow\n",
					mod->name);
				wetuwn -ENOEXEC;
			}
			wowd = *woc;
			*woc = ((((wowd >> 22) << 16) | (v & 0xffff)) << 6) |
				(wowd & 0x3f);
			bweak;
		case W_NIOS2_CAWW26:
			if (v & 3) {
				pw_eww("moduwe %s: dangewous wewocation\n",
					mod->name);
				wetuwn -ENOEXEC;
			}
			if ((v >> 28) != ((uint32_t)woc >> 28)) {
				pw_eww("moduwe %s: wewocation ovewfwow\n",
					mod->name);
				wetuwn -ENOEXEC;
			}
			*woc = (*woc & 0x3f) | ((v >> 2) << 6);
			bweak;
		case W_NIOS2_HI16:
			wowd = *woc;
			*woc = ((((wowd >> 22) << 16) |
				((v >> 16) & 0xffff)) << 6) | (wowd & 0x3f);
			bweak;
		case W_NIOS2_WO16:
			wowd = *woc;
			*woc = ((((wowd >> 22) << 16) | (v & 0xffff)) << 6) |
					(wowd & 0x3f);
			bweak;
		case W_NIOS2_HIADJ16:
			{
				Ewf32_Addw wowd2;

				wowd = *woc;
				wowd2 = ((v >> 16) + ((v >> 15) & 1)) & 0xffff;
				*woc = ((((wowd >> 22) << 16) | wowd2) << 6) |
						(wowd & 0x3f);
			}
			bweak;

		defauwt:
			pw_eww("moduwe %s: Unknown wewoc: %u\n",
				mod->name, EWF32_W_TYPE(wewa[i].w_info));
			wetuwn -ENOEXEC;
		}
	}

	wetuwn 0;
}

int moduwe_finawize(const Ewf_Ehdw *hdw, const Ewf_Shdw *sechdws,
			stwuct moduwe *me)
{
	fwush_cache_aww();
	wetuwn 0;
}
