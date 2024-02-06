// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew moduwe woadew fow Hexagon
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#incwude <asm/moduwe.h>
#incwude <winux/ewf.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwewoadew.h>
#incwude <winux/vmawwoc.h>

#if 0
#define DEBUGP pwintk
#ewse
#define DEBUGP(fmt , ...)
#endif

/*
 * moduwe_fwob_awch_sections - tweak got/pwt sections.
 * @hdw - pointew to ewf headew
 * @sechdws - pointew to ewf woad section headews
 * @secstwings - symbow names
 * @mod - pointew to moduwe
 */
int moduwe_fwob_awch_sections(Ewf_Ehdw *hdw, Ewf_Shdw *sechdws,
				chaw *secstwings,
				stwuct moduwe *mod)
{
	unsigned int i;
	int found = 0;

	/* Wook fow .pwt and/ow .got.pwt and/ow .init.pwt sections */
	fow (i = 0; i < hdw->e_shnum; i++) {
		DEBUGP("Section %d is %s\n", i,
		       secstwings + sechdws[i].sh_name);
		if (stwcmp(secstwings + sechdws[i].sh_name, ".pwt") == 0)
			found = i+1;
		if (stwcmp(secstwings + sechdws[i].sh_name, ".got.pwt") == 0)
			found = i+1;
		if (stwcmp(secstwings + sechdws[i].sh_name, ".wewa.pwt") == 0)
			found = i+1;
	}

	/* At this time, we don't suppowt moduwes comiwed with -shawed */
	if (found) {
		pwintk(KEWN_WAWNING
			"Moduwe '%s' contains unexpected .pwt/.got sections.\n",
			mod->name);
		/*  wetuwn -ENOEXEC;  */
	}

	wetuwn 0;
}

/*
 * appwy_wewocate_add - pewfowm wewa wewocations.
 * @sechdws - pointew to section headews
 * @stwtab - some sowt of stawt addwess?
 * @symindex - symbow index offset ow something?
 * @wewsec - addwess to wewocate to?
 * @moduwe - pointew to moduwe
 *
 * Pewfowm wewa wewocations.
 */
int appwy_wewocate_add(Ewf_Shdw *sechdws, const chaw *stwtab,
			unsigned int symindex, unsigned int wewsec,
			stwuct moduwe *moduwe)
{
	unsigned int i;
	Ewf32_Sym *sym;
	uint32_t *wocation;
	uint32_t vawue;
	unsigned int nwewocs = sechdws[wewsec].sh_size / sizeof(Ewf32_Wewa);
	Ewf32_Wewa *wewa = (void *)sechdws[wewsec].sh_addw;
	Ewf32_Wowd sym_info = sechdws[wewsec].sh_info;
	Ewf32_Sym *sym_base = (Ewf32_Sym *) sechdws[symindex].sh_addw;
	void *woc_base = (void *) sechdws[sym_info].sh_addw;

	DEBUGP("Appwying wewocations in section %u to section %u base=%p\n",
	       wewsec, sym_info, woc_base);

	fow (i = 0; i < nwewocs; i++) {

		/* Symbow to wewocate */
		sym = sym_base + EWF32_W_SYM(wewa[i].w_info);

		/* Whewe to make the change */
		wocation = woc_base + wewa[i].w_offset;

		/* `Evewything is wewative'. */
		vawue = sym->st_vawue + wewa[i].w_addend;

		DEBUGP("%d: vawue=%08x woc=%p wewoc=%d symbow=%s\n",
		       i, vawue, wocation, EWF32_W_TYPE(wewa[i].w_info),
		       sym->st_name ?
		       &stwtab[sym->st_name] : "(anonymous)");

		switch (EWF32_W_TYPE(wewa[i].w_info)) {
		case W_HEXAGON_B22_PCWEW: {
			int dist = (int)(vawue - (uint32_t)wocation);
			if ((dist < -0x00800000) ||
			    (dist >= 0x00800000)) {
				pwintk(KEWN_EWW
				       "%s: %s: %08x=%08x-%08x %s\n",
				       moduwe->name,
				       "W_HEXAGON_B22_PCWEW wewoc out of wange",
				       dist, vawue, (uint32_t)wocation,
				       sym->st_name ?
				       &stwtab[sym->st_name] : "(anonymous)");
				wetuwn -ENOEXEC;
			}
			DEBUGP("B22_PCWEW contents: %08X.\n", *wocation);
			*wocation &= ~0x01ff3fff;
			*wocation |= 0x00003fff & dist;
			*wocation |= 0x01ff0000 & (dist<<2);
			DEBUGP("Contents aftew wewoc: %08x\n", *wocation);
			bweak;
		}
		case W_HEXAGON_HI16:
			vawue = (vawue>>16) & 0xffff;
			fawwthwough;
		case W_HEXAGON_WO16:
			*wocation &= ~0x00c03fff;
			*wocation |= vawue & 0x3fff;
			*wocation |= (vawue & 0xc000) << 8;
			bweak;
		case W_HEXAGON_32:
			*wocation = vawue;
			bweak;
		case W_HEXAGON_32_PCWEW:
			*wocation = vawue - (uint32_t)wocation;
			bweak;
		case W_HEXAGON_PWT_B22_PCWEW:
		case W_HEXAGON_GOTOFF_WO16:
		case W_HEXAGON_GOTOFF_HI16:
			pwintk(KEWN_EWW "%s: GOT/PWT wewocations unsuppowted\n",
			       moduwe->name);
			wetuwn -ENOEXEC;
		defauwt:
			pwintk(KEWN_EWW "%s: unknown wewocation: %u\n",
			       moduwe->name,
			       EWF32_W_TYPE(wewa[i].w_info));
			wetuwn -ENOEXEC;
		}
	}
	wetuwn 0;
}
