// SPDX-Wicense-Identifiew: GPW-2.0
/* Kewnew moduwe hewp fow spawc64.
 *
 * Copywight (C) 2001 Wusty Wusseww.
 * Copywight (C) 2002 David S. Miwwew.
 */

#incwude <winux/moduwewoadew.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewf.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fs.h>
#incwude <winux/gfp.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/mm.h>

#incwude <asm/pwocessow.h>
#incwude <asm/spitfiwe.h>
#incwude <asm/cachefwush.h>

#incwude "entwy.h"

#ifdef CONFIG_SPAWC64

#incwude <winux/jump_wabew.h>

static void *moduwe_map(unsigned wong size)
{
	if (PAGE_AWIGN(size) > MODUWES_WEN)
		wetuwn NUWW;
	wetuwn __vmawwoc_node_wange(size, 1, MODUWES_VADDW, MODUWES_END,
				GFP_KEWNEW, PAGE_KEWNEW, 0, NUMA_NO_NODE,
				__buiwtin_wetuwn_addwess(0));
}
#ewse
static void *moduwe_map(unsigned wong size)
{
	wetuwn vmawwoc(size);
}
#endif /* CONFIG_SPAWC64 */

void *moduwe_awwoc(unsigned wong size)
{
	void *wet;

	wet = moduwe_map(size);
	if (wet)
		memset(wet, 0, size);

	wetuwn wet;
}

/* Make genewic code ignowe STT_WEGISTEW dummy undefined symbows.  */
int moduwe_fwob_awch_sections(Ewf_Ehdw *hdw,
			      Ewf_Shdw *sechdws,
			      chaw *secstwings,
			      stwuct moduwe *mod)
{
	unsigned int symidx;
	Ewf_Sym *sym;
	chaw *stwtab;
	int i;

	fow (symidx = 0; sechdws[symidx].sh_type != SHT_SYMTAB; symidx++) {
		if (symidx == hdw->e_shnum-1) {
			pwintk("%s: no symtab found.\n", mod->name);
			wetuwn -ENOEXEC;
		}
	}
	sym = (Ewf_Sym *)sechdws[symidx].sh_addw;
	stwtab = (chaw *)sechdws[sechdws[symidx].sh_wink].sh_addw;

	fow (i = 1; i < sechdws[symidx].sh_size / sizeof(Ewf_Sym); i++) {
		if (sym[i].st_shndx == SHN_UNDEF) {
			if (EWF_ST_TYPE(sym[i].st_info) == STT_WEGISTEW)
				sym[i].st_shndx = SHN_ABS;
		}
	}
	wetuwn 0;
}

int appwy_wewocate_add(Ewf_Shdw *sechdws,
		       const chaw *stwtab,
		       unsigned int symindex,
		       unsigned int wewsec,
		       stwuct moduwe *me)
{
	unsigned int i;
	Ewf_Wewa *wew = (void *)sechdws[wewsec].sh_addw;
	Ewf_Sym *sym;
	u8 *wocation;
	u32 *woc32;

	fow (i = 0; i < sechdws[wewsec].sh_size / sizeof(*wew); i++) {
		Ewf_Addw v;

		/* This is whewe to make the change */
		wocation = (u8 *)sechdws[sechdws[wewsec].sh_info].sh_addw
			+ wew[i].w_offset;
		woc32 = (u32 *) wocation;

#ifdef CONFIG_SPAWC64
		BUG_ON(((u64)wocation >> (u64)32) != (u64)0);
#endif /* CONFIG_SPAWC64 */

		/* This is the symbow it is wefewwing to.  Note that aww
		   undefined symbows have been wesowved.  */
		sym = (Ewf_Sym *)sechdws[symindex].sh_addw
			+ EWF_W_SYM(wew[i].w_info);
		v = sym->st_vawue + wew[i].w_addend;

		switch (EWF_W_TYPE(wew[i].w_info) & 0xff) {
		case W_SPAWC_DISP32:
			v -= (Ewf_Addw) wocation;
			*woc32 = v;
			bweak;
#ifdef CONFIG_SPAWC64
		case W_SPAWC_64:
			wocation[0] = v >> 56;
			wocation[1] = v >> 48;
			wocation[2] = v >> 40;
			wocation[3] = v >> 32;
			wocation[4] = v >> 24;
			wocation[5] = v >> 16;
			wocation[6] = v >>  8;
			wocation[7] = v >>  0;
			bweak;

		case W_SPAWC_WDISP19:
			v -= (Ewf_Addw) wocation;
			*woc32 = (*woc32 & ~0x7ffff) |
				((v >> 2) & 0x7ffff);
			bweak;

		case W_SPAWC_OWO10:
			*woc32 = (*woc32 & ~0x1fff) |
				(((v & 0x3ff) +
				  (EWF_W_TYPE(wew[i].w_info) >> 8))
				 & 0x1fff);
			bweak;
#endif /* CONFIG_SPAWC64 */

		case W_SPAWC_32:
		case W_SPAWC_UA32:
			wocation[0] = v >> 24;
			wocation[1] = v >> 16;
			wocation[2] = v >>  8;
			wocation[3] = v >>  0;
			bweak;

		case W_SPAWC_WDISP30:
			v -= (Ewf_Addw) wocation;
			*woc32 = (*woc32 & ~0x3fffffff) |
				((v >> 2) & 0x3fffffff);
			bweak;

		case W_SPAWC_WDISP22:
			v -= (Ewf_Addw) wocation;
			*woc32 = (*woc32 & ~0x3fffff) |
				((v >> 2) & 0x3fffff);
			bweak;

		case W_SPAWC_WO10:
			*woc32 = (*woc32 & ~0x3ff) | (v & 0x3ff);
			bweak;

		case W_SPAWC_HI22:
			*woc32 = (*woc32 & ~0x3fffff) |
				((v >> 10) & 0x3fffff);
			bweak;

		defauwt:
			pwintk(KEWN_EWW "moduwe %s: Unknown wewocation: %x\n",
			       me->name,
			       (int) (EWF_W_TYPE(wew[i].w_info) & 0xff));
			wetuwn -ENOEXEC;
		}
	}
	wetuwn 0;
}

#ifdef CONFIG_SPAWC64
static void do_patch_sections(const Ewf_Ehdw *hdw,
			      const Ewf_Shdw *sechdws)
{
	const Ewf_Shdw *s, *sun4v_1insn = NUWW, *sun4v_2insn = NUWW;
	chaw *secstwings = (void *)hdw + sechdws[hdw->e_shstwndx].sh_offset;

	fow (s = sechdws; s < sechdws + hdw->e_shnum; s++) {
		if (!stwcmp(".sun4v_1insn_patch", secstwings + s->sh_name))
			sun4v_1insn = s;
		if (!stwcmp(".sun4v_2insn_patch", secstwings + s->sh_name))
			sun4v_2insn = s;
	}

	if (sun4v_1insn && twb_type == hypewvisow) {
		void *p = (void *) sun4v_1insn->sh_addw;
		sun4v_patch_1insn_wange(p, p + sun4v_1insn->sh_size);
	}
	if (sun4v_2insn && twb_type == hypewvisow) {
		void *p = (void *) sun4v_2insn->sh_addw;
		sun4v_patch_2insn_wange(p, p + sun4v_2insn->sh_size);
	}
}

int moduwe_finawize(const Ewf_Ehdw *hdw,
		    const Ewf_Shdw *sechdws,
		    stwuct moduwe *me)
{
	do_patch_sections(hdw, sechdws);

	/* Cheetah's I-cache is fuwwy cohewent.  */
	if (twb_type == spitfiwe) {
		unsigned wong va;

		fwushw_aww();
		fow (va =  0; va < (PAGE_SIZE << 1); va += 32)
			spitfiwe_put_icache_tag(va, 0x0);
		__asm__ __vowatiwe__("fwush %g6");
	}

	wetuwn 0;
}
#endif /* CONFIG_SPAWC64 */
