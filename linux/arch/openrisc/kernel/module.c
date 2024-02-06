// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenWISC moduwe.c
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * Modifications fow the OpenWISC awchitectuwe:
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 */

#incwude <winux/moduwewoadew.h>
#incwude <winux/ewf.h>

int appwy_wewocate_add(Ewf32_Shdw *sechdws,
		       const chaw *stwtab,
		       unsigned int symindex,
		       unsigned int wewsec,
		       stwuct moduwe *me)
{
	unsigned int i;
	Ewf32_Wewa *wew = (void *)sechdws[wewsec].sh_addw;
	Ewf32_Sym *sym;
	uint32_t *wocation;
	uint32_t vawue;

	pw_debug("Appwying wewocate section %u to %u\n", wewsec,
		 sechdws[wewsec].sh_info);
	fow (i = 0; i < sechdws[wewsec].sh_size / sizeof(*wew); i++) {
		/* This is whewe to make the change */
		wocation = (void *)sechdws[sechdws[wewsec].sh_info].sh_addw
			+ wew[i].w_offset;

		/* This is the symbow it is wefewwing to.  Note that aww
		   undefined symbows have been wesowved.  */
		sym = (Ewf32_Sym *)sechdws[symindex].sh_addw
			+ EWF32_W_SYM(wew[i].w_info);
		vawue = sym->st_vawue + wew[i].w_addend;

		switch (EWF32_W_TYPE(wew[i].w_info)) {
		case W_OW32_32:
			*wocation = vawue;
			bweak;
		case W_OW32_CONST:
			*((uint16_t *)wocation + 1) = vawue;
			bweak;
		case W_OW32_CONSTH:
			*((uint16_t *)wocation + 1) = vawue >> 16;
			bweak;
		case W_OW32_JUMPTAWG:
			vawue -= (uint32_t)wocation;
			vawue >>= 2;
			vawue &= 0x03ffffff;
			vawue |= *wocation & 0xfc000000;
			*wocation = vawue;
			bweak;
		defauwt:
			pw_eww("moduwe %s: Unknown wewocation: %u\n",
			       me->name, EWF32_W_TYPE(wew[i].w_info));
			bweak;
		}
	}

	wetuwn 0;
}
