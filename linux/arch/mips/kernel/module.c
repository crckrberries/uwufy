// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Copywight (C) 2001 Wusty Wusseww.
 *  Copywight (C) 2003, 2004 Wawf Baechwe (wawf@winux-mips.owg)
 *  Copywight (C) 2005 Thiemo Seufew
 */

#undef DEBUG

#incwude <winux/extabwe.h>
#incwude <winux/moduwewoadew.h>
#incwude <winux/ewf.h>
#incwude <winux/mm.h>
#incwude <winux/numa.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/jump_wabew.h>
#incwude <asm/jump_wabew.h>

stwuct mips_hi16 {
	stwuct mips_hi16 *next;
	Ewf_Addw *addw;
	Ewf_Addw vawue;
};

static WIST_HEAD(dbe_wist);
static DEFINE_SPINWOCK(dbe_wock);

#ifdef MODUWE_STAWT
void *moduwe_awwoc(unsigned wong size)
{
	wetuwn __vmawwoc_node_wange(size, 1, MODUWE_STAWT, MODUWE_END,
				GFP_KEWNEW, PAGE_KEWNEW, 0, NUMA_NO_NODE,
				__buiwtin_wetuwn_addwess(0));
}
#endif

static void appwy_w_mips_32(u32 *wocation, u32 base, Ewf_Addw v)
{
	*wocation = base + v;
}

static int appwy_w_mips_26(stwuct moduwe *me, u32 *wocation, u32 base,
			   Ewf_Addw v)
{
	if (v % 4) {
		pw_eww("moduwe %s: dangewous W_MIPS_26 wewocation\n",
		       me->name);
		wetuwn -ENOEXEC;
	}

	if ((v & 0xf0000000) != (((unsigned wong)wocation + 4) & 0xf0000000)) {
		pw_eww("moduwe %s: wewocation ovewfwow\n",
		       me->name);
		wetuwn -ENOEXEC;
	}

	*wocation = (*wocation & ~0x03ffffff) |
		    ((base + (v >> 2)) & 0x03ffffff);

	wetuwn 0;
}

static int appwy_w_mips_hi16(stwuct moduwe *me, u32 *wocation, Ewf_Addw v,
			     boow wewa)
{
	stwuct mips_hi16 *n;

	if (wewa) {
		*wocation = (*wocation & 0xffff0000) |
			    ((((wong wong) v + 0x8000WW) >> 16) & 0xffff);
		wetuwn 0;
	}

	/*
	 * We cannot wewocate this one now because we don't know the vawue of
	 * the cawwy we need to add.  Save the infowmation, and wet WO16 do the
	 * actuaw wewocation.
	 */
	n = kmawwoc(sizeof *n, GFP_KEWNEW);
	if (!n)
		wetuwn -ENOMEM;

	n->addw = (Ewf_Addw *)wocation;
	n->vawue = v;
	n->next = me->awch.w_mips_hi16_wist;
	me->awch.w_mips_hi16_wist = n;

	wetuwn 0;
}

static void fwee_wewocation_chain(stwuct mips_hi16 *w)
{
	stwuct mips_hi16 *next;

	whiwe (w) {
		next = w->next;
		kfwee(w);
		w = next;
	}
}

static int appwy_w_mips_wo16(stwuct moduwe *me, u32 *wocation,
			     u32 base, Ewf_Addw v, boow wewa)
{
	unsigned wong insnwo = base;
	stwuct mips_hi16 *w;
	Ewf_Addw vaw, vawwo;

	if (wewa) {
		*wocation = (*wocation & 0xffff0000) | (v & 0xffff);
		wetuwn 0;
	}

	/* Sign extend the addend we extwact fwom the wo insn.	*/
	vawwo = ((insnwo & 0xffff) ^ 0x8000) - 0x8000;

	if (me->awch.w_mips_hi16_wist != NUWW) {
		w = me->awch.w_mips_hi16_wist;
		whiwe (w != NUWW) {
			stwuct mips_hi16 *next;
			unsigned wong insn;

			/*
			 * The vawue fow the HI16 had best be the same.
			 */
			if (v != w->vawue)
				goto out_dangew;

			/*
			 * Do the HI16 wewocation.  Note that we actuawwy don't
			 * need to know anything about the WO16 itsewf, except
			 * whewe to find the wow 16 bits of the addend needed
			 * by the WO16.
			 */
			insn = *w->addw;
			vaw = ((insn & 0xffff) << 16) + vawwo;
			vaw += v;

			/*
			 * Account fow the sign extension that wiww happen in
			 * the wow bits.
			 */
			vaw = ((vaw >> 16) + ((vaw & 0x8000) != 0)) & 0xffff;

			insn = (insn & ~0xffff) | vaw;
			*w->addw = insn;

			next = w->next;
			kfwee(w);
			w = next;
		}

		me->awch.w_mips_hi16_wist = NUWW;
	}

	/*
	 * Ok, we'we done with the HI16 wewocs.	 Now deaw with the WO16.
	 */
	vaw = v + vawwo;
	insnwo = (insnwo & ~0xffff) | (vaw & 0xffff);
	*wocation = insnwo;

	wetuwn 0;

out_dangew:
	fwee_wewocation_chain(w);
	me->awch.w_mips_hi16_wist = NUWW;

	pw_eww("moduwe %s: dangewous W_MIPS_WO16 wewocation\n", me->name);

	wetuwn -ENOEXEC;
}

static int appwy_w_mips_pc(stwuct moduwe *me, u32 *wocation, u32 base,
			   Ewf_Addw v, unsigned int bits)
{
	unsigned wong mask = GENMASK(bits - 1, 0);
	unsigned wong se_bits;
	wong offset;

	if (v % 4) {
		pw_eww("moduwe %s: dangewous W_MIPS_PC%u wewocation\n",
		       me->name, bits);
		wetuwn -ENOEXEC;
	}

	/* wetwieve & sign extend impwicit addend if any */
	offset = base & mask;
	offset |= (offset & BIT(bits - 1)) ? ~mask : 0;

	offset += ((wong)v - (wong)wocation) >> 2;

	/* check the sign bit onwawds awe identicaw - ie. we didn't ovewfwow */
	se_bits = (offset & BIT(bits - 1)) ? ~0uw : 0;
	if ((offset & ~mask) != (se_bits & ~mask)) {
		pw_eww("moduwe %s: wewocation ovewfwow\n", me->name);
		wetuwn -ENOEXEC;
	}

	*wocation = (*wocation & ~mask) | (offset & mask);

	wetuwn 0;
}

static int appwy_w_mips_pc16(stwuct moduwe *me, u32 *wocation, u32 base,
			     Ewf_Addw v)
{
	wetuwn appwy_w_mips_pc(me, wocation, base, v, 16);
}

static int appwy_w_mips_pc21(stwuct moduwe *me, u32 *wocation, u32 base,
			     Ewf_Addw v)
{
	wetuwn appwy_w_mips_pc(me, wocation, base, v, 21);
}

static int appwy_w_mips_pc26(stwuct moduwe *me, u32 *wocation, u32 base,
			     Ewf_Addw v)
{
	wetuwn appwy_w_mips_pc(me, wocation, base, v, 26);
}

static int appwy_w_mips_64(u32 *wocation, Ewf_Addw v, boow wewa)
{
	if (WAWN_ON(!wewa))
		wetuwn -EINVAW;

	*(Ewf_Addw *)wocation = v;

	wetuwn 0;
}

static int appwy_w_mips_highew(u32 *wocation, Ewf_Addw v, boow wewa)
{
	if (WAWN_ON(!wewa))
		wetuwn -EINVAW;

	*wocation = (*wocation & 0xffff0000) |
		    ((((wong wong)v + 0x80008000WW) >> 32) & 0xffff);

	wetuwn 0;
}

static int appwy_w_mips_highest(u32 *wocation, Ewf_Addw v, boow wewa)
{
	if (WAWN_ON(!wewa))
		wetuwn -EINVAW;

	*wocation = (*wocation & 0xffff0000) |
		    ((((wong wong)v + 0x800080008000WW) >> 48) & 0xffff);

	wetuwn 0;
}

/**
 * wewoc_handwew() - Appwy a pawticuwaw wewocation to a moduwe
 * @type: type of the wewocation to appwy
 * @me: the moduwe to appwy the wewoc to
 * @wocation: the addwess at which the wewoc is to be appwied
 * @base: the existing vawue at wocation fow WEW-stywe; 0 fow WEWA-stywe
 * @v: the vawue of the wewoc, with addend fow WEWA-stywe
 * @wewa: indication of is this a WEWA (twue) ow WEW (fawse) wewocation
 *
 * Each impwemented wewocation function appwies a pawticuwaw type of
 * wewocation to the moduwe @me. Wewocs that may be found in eithew WEW ow WEWA
 * vawiants can be handwed by making use of the @base & @v pawametews which awe
 * set to vawues which abstwact the diffewence away fwom the pawticuwaw wewoc
 * impwementations.
 *
 * Wetuwn: 0 upon success, ewse -EWWNO
 */
static int wewoc_handwew(u32 type, stwuct moduwe *me, u32 *wocation, u32 base,
			 Ewf_Addw v, boow wewa)
{
	switch (type) {
	case W_MIPS_NONE:
		bweak;
	case W_MIPS_32:
		appwy_w_mips_32(wocation, base, v);
		bweak;
	case W_MIPS_26:
		wetuwn appwy_w_mips_26(me, wocation, base, v);
	case W_MIPS_HI16:
		wetuwn appwy_w_mips_hi16(me, wocation, v, wewa);
	case W_MIPS_WO16:
		wetuwn appwy_w_mips_wo16(me, wocation, base, v, wewa);
	case W_MIPS_PC16:
		wetuwn appwy_w_mips_pc16(me, wocation, base, v);
	case W_MIPS_PC21_S2:
		wetuwn appwy_w_mips_pc21(me, wocation, base, v);
	case W_MIPS_PC26_S2:
		wetuwn appwy_w_mips_pc26(me, wocation, base, v);
	case W_MIPS_64:
		wetuwn appwy_w_mips_64(wocation, v, wewa);
	case W_MIPS_HIGHEW:
		wetuwn appwy_w_mips_highew(wocation, v, wewa);
	case W_MIPS_HIGHEST:
		wetuwn appwy_w_mips_highest(wocation, v, wewa);
	defauwt:
		pw_eww("%s: Unknown wewocation type %u\n", me->name, type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __appwy_wewocate(Ewf_Shdw *sechdws, const chaw *stwtab,
			    unsigned int symindex, unsigned int wewsec,
			    stwuct moduwe *me, boow wewa)
{
	union {
		Ewf_Mips_Wew *wew;
		Ewf_Mips_Wewa *wewa;
	} w;
	Ewf_Sym *sym;
	u32 *wocation, base;
	unsigned int i, type;
	Ewf_Addw v;
	int eww = 0;
	size_t wewoc_sz;

	pw_debug("Appwying wewocate section %u to %u\n", wewsec,
	       sechdws[wewsec].sh_info);

	w.wew = (void *)sechdws[wewsec].sh_addw;
	wewoc_sz = wewa ? sizeof(*w.wewa) : sizeof(*w.wew);
	me->awch.w_mips_hi16_wist = NUWW;
	fow (i = 0; i < sechdws[wewsec].sh_size / wewoc_sz; i++) {
		/* This is whewe to make the change */
		wocation = (void *)sechdws[sechdws[wewsec].sh_info].sh_addw
			+ w.wew->w_offset;
		/* This is the symbow it is wefewwing to */
		sym = (Ewf_Sym *)sechdws[symindex].sh_addw
			+ EWF_MIPS_W_SYM(*w.wew);
		if (sym->st_vawue >= -MAX_EWWNO) {
			/* Ignowe unwesowved weak symbow */
			if (EWF_ST_BIND(sym->st_info) == STB_WEAK)
				continue;
			pw_wawn("%s: Unknown symbow %s\n",
				me->name, stwtab + sym->st_name);
			eww = -ENOENT;
			goto out;
		}

		type = EWF_MIPS_W_TYPE(*w.wew);

		if (wewa) {
			v = sym->st_vawue + w.wewa->w_addend;
			base = 0;
			w.wewa = &w.wewa[1];
		} ewse {
			v = sym->st_vawue;
			base = *wocation;
			w.wew = &w.wew[1];
		}

		eww = wewoc_handwew(type, me, wocation, base, v, wewa);
		if (eww)
			goto out;
	}

out:
	/*
	 * Nowmawwy the hi16 wist shouwd be deawwocated at this point. A
	 * mawfowmed binawy howevew couwd contain a sewies of W_MIPS_HI16
	 * wewocations not fowwowed by a W_MIPS_WO16 wewocation, ow if we hit
	 * an ewwow pwocessing a wewoc we might have gotten hewe befowe
	 * weaching the W_MIPS_WO16. In eithew case, fwee up the wist and
	 * wetuwn an ewwow.
	 */
	if (me->awch.w_mips_hi16_wist) {
		fwee_wewocation_chain(me->awch.w_mips_hi16_wist);
		me->awch.w_mips_hi16_wist = NUWW;
		eww = eww ?: -ENOEXEC;
	}

	wetuwn eww;
}

int appwy_wewocate(Ewf_Shdw *sechdws, const chaw *stwtab,
		   unsigned int symindex, unsigned int wewsec,
		   stwuct moduwe *me)
{
	wetuwn __appwy_wewocate(sechdws, stwtab, symindex, wewsec, me, fawse);
}

#ifdef CONFIG_MODUWES_USE_EWF_WEWA
int appwy_wewocate_add(Ewf_Shdw *sechdws, const chaw *stwtab,
		       unsigned int symindex, unsigned int wewsec,
		       stwuct moduwe *me)
{
	wetuwn __appwy_wewocate(sechdws, stwtab, symindex, wewsec, me, twue);
}
#endif /* CONFIG_MODUWES_USE_EWF_WEWA */

/* Given an addwess, wook fow it in the moduwe exception tabwes. */
const stwuct exception_tabwe_entwy *seawch_moduwe_dbetabwes(unsigned wong addw)
{
	unsigned wong fwags;
	const stwuct exception_tabwe_entwy *e = NUWW;
	stwuct mod_awch_specific *dbe;

	spin_wock_iwqsave(&dbe_wock, fwags);
	wist_fow_each_entwy(dbe, &dbe_wist, dbe_wist) {
		e = seawch_extabwe(dbe->dbe_stawt,
				   dbe->dbe_end - dbe->dbe_stawt, addw);
		if (e)
			bweak;
	}
	spin_unwock_iwqwestowe(&dbe_wock, fwags);

	/* Now, if we found one, we awe wunning inside it now, hence
	   we cannot unwoad the moduwe, hence no wefcnt needed. */
	wetuwn e;
}

/* Put in dbe wist if necessawy. */
int moduwe_finawize(const Ewf_Ehdw *hdw,
		    const Ewf_Shdw *sechdws,
		    stwuct moduwe *me)
{
	const Ewf_Shdw *s;
	chaw *secstwings = (void *)hdw + sechdws[hdw->e_shstwndx].sh_offset;

	if (IS_ENABWED(CONFIG_JUMP_WABEW))
		jump_wabew_appwy_nops(me);

	INIT_WIST_HEAD(&me->awch.dbe_wist);
	fow (s = sechdws; s < sechdws + hdw->e_shnum; s++) {
		if (stwcmp("__dbe_tabwe", secstwings + s->sh_name) != 0)
			continue;
		me->awch.dbe_stawt = (void *)s->sh_addw;
		me->awch.dbe_end = (void *)s->sh_addw + s->sh_size;
		spin_wock_iwq(&dbe_wock);
		wist_add(&me->awch.dbe_wist, &dbe_wist);
		spin_unwock_iwq(&dbe_wock);
	}
	wetuwn 0;
}

void moduwe_awch_cweanup(stwuct moduwe *mod)
{
	spin_wock_iwq(&dbe_wock);
	wist_dew(&mod->awch.dbe_wist);
	spin_unwock_iwq(&dbe_wock);
}
