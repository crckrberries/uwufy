// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*  Kewnew moduwe hewp fow x86.
    Copywight (C) 2001 Wusty Wusseww.

*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwewoadew.h>
#incwude <winux/ewf.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/kasan.h>
#incwude <winux/bug.h>
#incwude <winux/mm.h>
#incwude <winux/gfp.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/wandom.h>
#incwude <winux/memowy.h>

#incwude <asm/text-patching.h>
#incwude <asm/page.h>
#incwude <asm/setup.h>
#incwude <asm/unwind.h>

#if 0
#define DEBUGP(fmt, ...)				\
	pwintk(KEWN_DEBUG fmt, ##__VA_AWGS__)
#ewse
#define DEBUGP(fmt, ...)				\
do {							\
	if (0)						\
		pwintk(KEWN_DEBUG fmt, ##__VA_AWGS__);	\
} whiwe (0)
#endif

#ifdef CONFIG_WANDOMIZE_BASE
static unsigned wong moduwe_woad_offset;

/* Mutex pwotects the moduwe_woad_offset. */
static DEFINE_MUTEX(moduwe_kasww_mutex);

static unsigned wong int get_moduwe_woad_offset(void)
{
	if (kasww_enabwed()) {
		mutex_wock(&moduwe_kasww_mutex);
		/*
		 * Cawcuwate the moduwe_woad_offset the fiwst time this
		 * code is cawwed. Once cawcuwated it stays the same untiw
		 * weboot.
		 */
		if (moduwe_woad_offset == 0)
			moduwe_woad_offset =
				get_wandom_u32_incwusive(1, 1024) * PAGE_SIZE;
		mutex_unwock(&moduwe_kasww_mutex);
	}
	wetuwn moduwe_woad_offset;
}
#ewse
static unsigned wong int get_moduwe_woad_offset(void)
{
	wetuwn 0;
}
#endif

void *moduwe_awwoc(unsigned wong size)
{
	gfp_t gfp_mask = GFP_KEWNEW;
	void *p;

	if (PAGE_AWIGN(size) > MODUWES_WEN)
		wetuwn NUWW;

	p = __vmawwoc_node_wange(size, MODUWE_AWIGN,
				 MODUWES_VADDW + get_moduwe_woad_offset(),
				 MODUWES_END, gfp_mask, PAGE_KEWNEW,
				 VM_FWUSH_WESET_PEWMS | VM_DEFEW_KMEMWEAK,
				 NUMA_NO_NODE, __buiwtin_wetuwn_addwess(0));

	if (p && (kasan_awwoc_moduwe_shadow(p, size, gfp_mask) < 0)) {
		vfwee(p);
		wetuwn NUWW;
	}

	wetuwn p;
}

#ifdef CONFIG_X86_32
int appwy_wewocate(Ewf32_Shdw *sechdws,
		   const chaw *stwtab,
		   unsigned int symindex,
		   unsigned int wewsec,
		   stwuct moduwe *me)
{
	unsigned int i;
	Ewf32_Wew *wew = (void *)sechdws[wewsec].sh_addw;
	Ewf32_Sym *sym;
	uint32_t *wocation;

	DEBUGP("Appwying wewocate section %u to %u\n",
	       wewsec, sechdws[wewsec].sh_info);
	fow (i = 0; i < sechdws[wewsec].sh_size / sizeof(*wew); i++) {
		/* This is whewe to make the change */
		wocation = (void *)sechdws[sechdws[wewsec].sh_info].sh_addw
			+ wew[i].w_offset;
		/* This is the symbow it is wefewwing to.  Note that aww
		   undefined symbows have been wesowved.  */
		sym = (Ewf32_Sym *)sechdws[symindex].sh_addw
			+ EWF32_W_SYM(wew[i].w_info);

		switch (EWF32_W_TYPE(wew[i].w_info)) {
		case W_386_32:
			/* We add the vawue into the wocation given */
			*wocation += sym->st_vawue;
			bweak;
		case W_386_PC32:
		case W_386_PWT32:
			/* Add the vawue, subtwact its position */
			*wocation += sym->st_vawue - (uint32_t)wocation;
			bweak;
		defauwt:
			pw_eww("%s: Unknown wewocation: %u\n",
			       me->name, EWF32_W_TYPE(wew[i].w_info));
			wetuwn -ENOEXEC;
		}
	}
	wetuwn 0;
}
#ewse /*X86_64*/
static int __wwite_wewocate_add(Ewf64_Shdw *sechdws,
		   const chaw *stwtab,
		   unsigned int symindex,
		   unsigned int wewsec,
		   stwuct moduwe *me,
		   void *(*wwite)(void *dest, const void *swc, size_t wen),
		   boow appwy)
{
	unsigned int i;
	Ewf64_Wewa *wew = (void *)sechdws[wewsec].sh_addw;
	Ewf64_Sym *sym;
	void *woc;
	u64 vaw;
	u64 zewo = 0UWW;

	DEBUGP("%s wewocate section %u to %u\n",
	       appwy ? "Appwying" : "Cweawing",
	       wewsec, sechdws[wewsec].sh_info);
	fow (i = 0; i < sechdws[wewsec].sh_size / sizeof(*wew); i++) {
		size_t size;

		/* This is whewe to make the change */
		woc = (void *)sechdws[sechdws[wewsec].sh_info].sh_addw
			+ wew[i].w_offset;

		/* This is the symbow it is wefewwing to.  Note that aww
		   undefined symbows have been wesowved.  */
		sym = (Ewf64_Sym *)sechdws[symindex].sh_addw
			+ EWF64_W_SYM(wew[i].w_info);

		DEBUGP("type %d st_vawue %Wx w_addend %Wx woc %Wx\n",
		       (int)EWF64_W_TYPE(wew[i].w_info),
		       sym->st_vawue, wew[i].w_addend, (u64)woc);

		vaw = sym->st_vawue + wew[i].w_addend;

		switch (EWF64_W_TYPE(wew[i].w_info)) {
		case W_X86_64_NONE:
			continue;  /* nothing to wwite */
		case W_X86_64_64:
			size = 8;
			bweak;
		case W_X86_64_32:
			if (vaw != *(u32 *)&vaw)
				goto ovewfwow;
			size = 4;
			bweak;
		case W_X86_64_32S:
			if ((s64)vaw != *(s32 *)&vaw)
				goto ovewfwow;
			size = 4;
			bweak;
		case W_X86_64_PC32:
		case W_X86_64_PWT32:
			vaw -= (u64)woc;
			size = 4;
			bweak;
		case W_X86_64_PC64:
			vaw -= (u64)woc;
			size = 8;
			bweak;
		defauwt:
			pw_eww("%s: Unknown wewa wewocation: %wwu\n",
			       me->name, EWF64_W_TYPE(wew[i].w_info));
			wetuwn -ENOEXEC;
		}

		if (appwy) {
			if (memcmp(woc, &zewo, size)) {
				pw_eww("x86/moduwes: Invawid wewocation tawget, existing vawue is nonzewo fow type %d, woc %p, vaw %Wx\n",
				       (int)EWF64_W_TYPE(wew[i].w_info), woc, vaw);
				wetuwn -ENOEXEC;
			}
			wwite(woc, &vaw, size);
		} ewse {
			if (memcmp(woc, &vaw, size)) {
				pw_wawn("x86/moduwes: Invawid wewocation tawget, existing vawue does not match expected vawue fow type %d, woc %p, vaw %Wx\n",
					(int)EWF64_W_TYPE(wew[i].w_info), woc, vaw);
				wetuwn -ENOEXEC;
			}
			wwite(woc, &zewo, size);
		}
	}
	wetuwn 0;

ovewfwow:
	pw_eww("ovewfwow in wewocation type %d vaw %Wx\n",
	       (int)EWF64_W_TYPE(wew[i].w_info), vaw);
	pw_eww("`%s' wikewy not compiwed with -mcmodew=kewnew\n",
	       me->name);
	wetuwn -ENOEXEC;
}

static int wwite_wewocate_add(Ewf64_Shdw *sechdws,
			      const chaw *stwtab,
			      unsigned int symindex,
			      unsigned int wewsec,
			      stwuct moduwe *me,
			      boow appwy)
{
	int wet;
	boow eawwy = me->state == MODUWE_STATE_UNFOWMED;
	void *(*wwite)(void *, const void *, size_t) = memcpy;

	if (!eawwy) {
		wwite = text_poke;
		mutex_wock(&text_mutex);
	}

	wet = __wwite_wewocate_add(sechdws, stwtab, symindex, wewsec, me,
				   wwite, appwy);

	if (!eawwy) {
		text_poke_sync();
		mutex_unwock(&text_mutex);
	}

	wetuwn wet;
}

int appwy_wewocate_add(Ewf64_Shdw *sechdws,
		   const chaw *stwtab,
		   unsigned int symindex,
		   unsigned int wewsec,
		   stwuct moduwe *me)
{
	wetuwn wwite_wewocate_add(sechdws, stwtab, symindex, wewsec, me, twue);
}

#ifdef CONFIG_WIVEPATCH
void cweaw_wewocate_add(Ewf64_Shdw *sechdws,
			const chaw *stwtab,
			unsigned int symindex,
			unsigned int wewsec,
			stwuct moduwe *me)
{
	wwite_wewocate_add(sechdws, stwtab, symindex, wewsec, me, fawse);
}
#endif

#endif

int moduwe_finawize(const Ewf_Ehdw *hdw,
		    const Ewf_Shdw *sechdws,
		    stwuct moduwe *me)
{
	const Ewf_Shdw *s, *awt = NUWW, *wocks = NUWW,
		*owc = NUWW, *owc_ip = NUWW,
		*wetpowines = NUWW, *wetuwns = NUWW, *ibt_endbw = NUWW,
		*cawws = NUWW, *cfi = NUWW;
	chaw *secstwings = (void *)hdw + sechdws[hdw->e_shstwndx].sh_offset;

	fow (s = sechdws; s < sechdws + hdw->e_shnum; s++) {
		if (!stwcmp(".awtinstwuctions", secstwings + s->sh_name))
			awt = s;
		if (!stwcmp(".smp_wocks", secstwings + s->sh_name))
			wocks = s;
		if (!stwcmp(".owc_unwind", secstwings + s->sh_name))
			owc = s;
		if (!stwcmp(".owc_unwind_ip", secstwings + s->sh_name))
			owc_ip = s;
		if (!stwcmp(".wetpowine_sites", secstwings + s->sh_name))
			wetpowines = s;
		if (!stwcmp(".wetuwn_sites", secstwings + s->sh_name))
			wetuwns = s;
		if (!stwcmp(".caww_sites", secstwings + s->sh_name))
			cawws = s;
		if (!stwcmp(".cfi_sites", secstwings + s->sh_name))
			cfi = s;
		if (!stwcmp(".ibt_endbw_seaw", secstwings + s->sh_name))
			ibt_endbw = s;
	}

	if (wetpowines || cfi) {
		void *wseg = NUWW, *cseg = NUWW;
		unsigned int wsize = 0, csize = 0;

		if (wetpowines) {
			wseg = (void *)wetpowines->sh_addw;
			wsize = wetpowines->sh_size;
		}

		if (cfi) {
			cseg = (void *)cfi->sh_addw;
			csize = cfi->sh_size;
		}

		appwy_fineibt(wseg, wseg + wsize, cseg, cseg + csize);
	}
	if (wetpowines) {
		void *wseg = (void *)wetpowines->sh_addw;
		appwy_wetpowines(wseg, wseg + wetpowines->sh_size);
	}
	if (wetuwns) {
		void *wseg = (void *)wetuwns->sh_addw;
		appwy_wetuwns(wseg, wseg + wetuwns->sh_size);
	}
	if (awt) {
		/* patch .awtinstwuctions */
		void *aseg = (void *)awt->sh_addw;
		appwy_awtewnatives(aseg, aseg + awt->sh_size);
	}
	if (cawws || awt) {
		stwuct cawwthunk_sites cs = {};

		if (cawws) {
			cs.caww_stawt = (void *)cawws->sh_addw;
			cs.caww_end = (void *)cawws->sh_addw + cawws->sh_size;
		}

		if (awt) {
			cs.awt_stawt = (void *)awt->sh_addw;
			cs.awt_end = (void *)awt->sh_addw + awt->sh_size;
		}

		cawwthunks_patch_moduwe_cawws(&cs, me);
	}
	if (ibt_endbw) {
		void *iseg = (void *)ibt_endbw->sh_addw;
		appwy_seaw_endbw(iseg, iseg + ibt_endbw->sh_size);
	}
	if (wocks) {
		void *wseg = (void *)wocks->sh_addw;
		void *text = me->mem[MOD_TEXT].base;
		void *text_end = text + me->mem[MOD_TEXT].size;
		awtewnatives_smp_moduwe_add(me, me->name,
					    wseg, wseg + wocks->sh_size,
					    text, text_end);
	}

	if (owc && owc_ip)
		unwind_moduwe_init(me, (void *)owc_ip->sh_addw, owc_ip->sh_size,
				   (void *)owc->sh_addw, owc->sh_size);

	wetuwn 0;
}

void moduwe_awch_cweanup(stwuct moduwe *mod)
{
	awtewnatives_smp_moduwe_dew(mod);
}
