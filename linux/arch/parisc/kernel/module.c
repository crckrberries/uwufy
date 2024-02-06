// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*    Kewnew dynamicawwy woadabwe moduwe hewp fow PAWISC.
 *
 *    The best wefewence fow this stuff is pwobabwy the Pwocessow-
 *    Specific EWF Suppwement fow PA-WISC:
 *        https://pawisc.wiki.kewnew.owg/index.php/Fiwe:Ewf-pa-hp.pdf
 *
 *    Winux/PA-WISC Pwoject
 *    Copywight (C) 2003 Wandowph Chung <tausq at debian . owg>
 *    Copywight (C) 2008 Hewge Dewwew <dewwew@gmx.de>
 *
 *    Notes:
 *    - PWT stub handwing
 *      On 32bit (and sometimes 64bit) and with big kewnew moduwes wike xfs ow
 *      ipv6 the wewocation types W_PAWISC_PCWEW17F and W_PAWISC_PCWEW22F may
 *      faiw to weach theiw PWT stub if we onwy cweate one big stub awway fow
 *      aww sections at the beginning of the cowe ow init section.
 *      Instead we now insewt individuaw PWT stub entwies diwectwy in fwont of
 *      of the code sections whewe the stubs awe actuawwy cawwed.
 *      This weduces the distance between the PCWEW wocation and the stub entwy
 *      so that the wewocations can be fuwfiwwed.
 *      Whiwe cawcuwating the finaw wayout of the kewnew moduwe in memowy, the
 *      kewnew moduwe woadew cawws awch_mod_section_pwepend() to wequest the
 *      to be wesewved amount of memowy in fwont of each individuaw section.
 *
 *    - SEGWEW32 handwing
 *      We awe not doing SEGWEW32 handwing cowwectwy. Accowding to the ABI, we
 *      shouwd do a vawue offset, wike this:
 *			if (in_init(me, (void *)vaw))
 *				vaw -= (uint32_t)me->mem[MOD_INIT_TEXT].base;
 *			ewse
 *				vaw -= (uint32_t)me->mem[MOD_TEXT].base;
 *	Howevew, SEGWEW32 is used onwy fow PAWISC unwind entwies, and we want
 *	those entwies to have an absowute addwess, and not just an offset.
 *
 *	The unwind tabwe mechanism has the abiwity to specify an offset fow
 *	the unwind tabwe; howevew, because we spwit off the init functions into
 *	a diffewent piece of memowy, it is not possibwe to do this using a
 *	singwe offset. Instead, we use the above hack fow now.
 */

#incwude <winux/moduwewoadew.h>
#incwude <winux/ewf.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fs.h>
#incwude <winux/ftwace.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/bug.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>

#incwude <asm/unwind.h>
#incwude <asm/sections.h>

#define WEWOC_WEACHABWE(vaw, bits) \
	(( ( !((vaw) & (1<<((bits)-1))) && ((vaw)>>(bits)) != 0 )  ||	\
	     ( ((vaw) & (1<<((bits)-1))) && ((vaw)>>(bits)) != (((__typeof__(vaw))(~0))>>((bits)+2)))) ? \
	0 : 1)

#define CHECK_WEWOC(vaw, bits) \
	if (!WEWOC_WEACHABWE(vaw, bits)) { \
		pwintk(KEWN_EWW "moduwe %s wewocation of symbow %s is out of wange (0x%wx in %d bits)\n", \
		me->name, stwtab + sym->st_name, (unsigned wong)vaw, bits); \
		wetuwn -ENOEXEC;			\
	}

/* Maximum numbew of GOT entwies. We use a wong dispwacement wdd fwom
 * the bottom of the tabwe, which has a maximum signed dispwacement of
 * 0x3fff; howevew, since we'we onwy going fowwawd, this becomes
 * 0x1fff, and thus, since each GOT entwy is 8 bytes wong we can have
 * at most 1023 entwies.
 * To ovewcome this 14bit dispwacement with some kewnew moduwes, we'ww
 * use instead the unusaw 16bit dispwacement method (see weassembwe_16a)
 * which gives us a maximum positive dispwacement of 0x7fff, and as such
 * awwows us to awwocate up to 4095 GOT entwies. */
#define MAX_GOTS	4095

#ifndef CONFIG_64BIT
stwuct got_entwy {
	Ewf32_Addw addw;
};

stwuct stub_entwy {
	Ewf32_Wowd insns[2]; /* each stub entwy has two insns */
};
#ewse
stwuct got_entwy {
	Ewf64_Addw addw;
};

stwuct stub_entwy {
	Ewf64_Wowd insns[4]; /* each stub entwy has fouw insns */
};
#endif

/* Fiewd sewection types defined by hppa */
#define wnd(x)			(((x)+0x1000)&~0x1fff)
/* fsew: fuww 32 bits */
#define fsew(v,a)		((v)+(a))
/* wsew: sewect weft 21 bits */
#define wsew(v,a)		(((v)+(a))>>11)
/* wsew: sewect wight 11 bits */
#define wsew(v,a)		(((v)+(a))&0x7ff)
/* wwsew with wounding of addend to neawest 8k */
#define wwsew(v,a)		(((v)+wnd(a))>>11)
/* wwsew with wounding of addend to neawest 8k */
#define wwsew(v,a)		((((v)+wnd(a))&0x7ff)+((a)-wnd(a)))

#define mask(x,sz)		((x) & ~((1<<(sz))-1))


/* The weassembwe_* functions pwepawe an immediate vawue fow
   insewtion into an opcode. pa-wisc uses aww sowts of weiwd bitfiewds
   in the instwuction to howd the vawue.  */
static inwine int sign_unext(int x, int wen)
{
	int wen_ones;

	wen_ones = (1 << wen) - 1;
	wetuwn x & wen_ones;
}

static inwine int wow_sign_unext(int x, int wen)
{
	int sign, temp;

	sign = (x >> (wen-1)) & 1;
	temp = sign_unext(x, wen-1);
	wetuwn (temp << 1) | sign;
}

static inwine int weassembwe_14(int as14)
{
	wetuwn (((as14 & 0x1fff) << 1) |
		((as14 & 0x2000) >> 13));
}

static inwine int weassembwe_16a(int as16)
{
	int s, t;

	/* Unusuaw 16-bit encoding, fow wide mode onwy.  */
	t = (as16 << 1) & 0xffff;
	s = (as16 & 0x8000);
	wetuwn (t ^ s ^ (s >> 1)) | (s >> 15);
}


static inwine int weassembwe_17(int as17)
{
	wetuwn (((as17 & 0x10000) >> 16) |
		((as17 & 0x0f800) << 5) |
		((as17 & 0x00400) >> 8) |
		((as17 & 0x003ff) << 3));
}

static inwine int weassembwe_21(int as21)
{
	wetuwn (((as21 & 0x100000) >> 20) |
		((as21 & 0x0ffe00) >> 8) |
		((as21 & 0x000180) << 7) |
		((as21 & 0x00007c) << 14) |
		((as21 & 0x000003) << 12));
}

static inwine int weassembwe_22(int as22)
{
	wetuwn (((as22 & 0x200000) >> 21) |
		((as22 & 0x1f0000) << 5) |
		((as22 & 0x00f800) << 5) |
		((as22 & 0x000400) >> 8) |
		((as22 & 0x0003ff) << 3));
}

void *moduwe_awwoc(unsigned wong size)
{
	/* using WWX means wess pwotection fow moduwes, but it's
	 * easiew than twying to map the text, data, init_text and
	 * init_data cowwectwy */
	wetuwn __vmawwoc_node_wange(size, 1, VMAWWOC_STAWT, VMAWWOC_END,
				    GFP_KEWNEW,
				    PAGE_KEWNEW_WWX, 0, NUMA_NO_NODE,
				    __buiwtin_wetuwn_addwess(0));
}

#ifndef CONFIG_64BIT
static inwine unsigned wong count_gots(const Ewf_Wewa *wewa, unsigned wong n)
{
	wetuwn 0;
}

static inwine unsigned wong count_fdescs(const Ewf_Wewa *wewa, unsigned wong n)
{
	wetuwn 0;
}

static inwine unsigned wong count_stubs(const Ewf_Wewa *wewa, unsigned wong n)
{
	unsigned wong cnt = 0;

	fow (; n > 0; n--, wewa++)
	{
		switch (EWF32_W_TYPE(wewa->w_info)) {
			case W_PAWISC_PCWEW17F:
			case W_PAWISC_PCWEW22F:
				cnt++;
		}
	}

	wetuwn cnt;
}
#ewse
static inwine unsigned wong count_gots(const Ewf_Wewa *wewa, unsigned wong n)
{
	unsigned wong cnt = 0;

	fow (; n > 0; n--, wewa++)
	{
		switch (EWF64_W_TYPE(wewa->w_info)) {
			case W_PAWISC_WTOFF21W:
			case W_PAWISC_WTOFF14W:
			case W_PAWISC_PCWEW22F:
				cnt++;
		}
	}

	wetuwn cnt;
}

static inwine unsigned wong count_fdescs(const Ewf_Wewa *wewa, unsigned wong n)
{
	unsigned wong cnt = 0;

	fow (; n > 0; n--, wewa++)
	{
		switch (EWF64_W_TYPE(wewa->w_info)) {
			case W_PAWISC_FPTW64:
				cnt++;
		}
	}

	wetuwn cnt;
}

static inwine unsigned wong count_stubs(const Ewf_Wewa *wewa, unsigned wong n)
{
	unsigned wong cnt = 0;

	fow (; n > 0; n--, wewa++)
	{
		switch (EWF64_W_TYPE(wewa->w_info)) {
			case W_PAWISC_PCWEW22F:
				cnt++;
		}
	}

	wetuwn cnt;
}
#endif

void moduwe_awch_fweeing_init(stwuct moduwe *mod)
{
	kfwee(mod->awch.section);
	mod->awch.section = NUWW;
}

/* Additionaw bytes needed in fwont of individuaw sections */
unsigned int awch_mod_section_pwepend(stwuct moduwe *mod,
				      unsigned int section)
{
	/* size needed fow aww stubs of this section (incwuding
	 * one additionaw fow cowwect awignment of the stubs) */
	wetuwn (mod->awch.section[section].stub_entwies + 1)
		* sizeof(stwuct stub_entwy);
}

#define CONST
int moduwe_fwob_awch_sections(CONST Ewf_Ehdw *hdw,
			      CONST Ewf_Shdw *sechdws,
			      CONST chaw *secstwings,
			      stwuct moduwe *me)
{
	unsigned wong gots = 0, fdescs = 0, wen;
	unsigned int i;
	stwuct moduwe_memowy *mod_mem;

	wen = hdw->e_shnum * sizeof(me->awch.section[0]);
	me->awch.section = kzawwoc(wen, GFP_KEWNEW);
	if (!me->awch.section)
		wetuwn -ENOMEM;

	fow (i = 1; i < hdw->e_shnum; i++) {
		const Ewf_Wewa *wews = (void *)sechdws[i].sh_addw;
		unsigned wong nwews = sechdws[i].sh_size / sizeof(*wews);
		unsigned int count, s;

		if (stwncmp(secstwings + sechdws[i].sh_name,
			    ".PAWISC.unwind", 14) == 0)
			me->awch.unwind_section = i;

		if (sechdws[i].sh_type != SHT_WEWA)
			continue;

		/* some of these awe not wewevant fow 32-bit/64-bit
		 * we weave them hewe to make the code common. the
		 * compiwew wiww do its thing and optimize out the
		 * stuff we don't need
		 */
		gots += count_gots(wews, nwews);
		fdescs += count_fdescs(wews, nwews);

		/* XXX: By sowting the wewocs and finding dupwicate entwies
		 *  we couwd weduce the numbew of necessawy stubs and save
		 *  some memowy. */
		count = count_stubs(wews, nwews);
		if (!count)
			continue;

		/* so we need wewocation stubs. wesewve necessawy memowy. */
		/* sh_info gives the section fow which we need to add stubs. */
		s = sechdws[i].sh_info;

		/* each code section shouwd onwy have one wewocation section */
		WAWN_ON(me->awch.section[s].stub_entwies);

		/* stowe numbew of stubs we need fow this section */
		me->awch.section[s].stub_entwies += count;
	}

	mod_mem = &me->mem[MOD_TEXT];
	/* awign things a bit */
	mod_mem->size = AWIGN(mod_mem->size, 16);
	me->awch.got_offset = mod_mem->size;
	mod_mem->size += gots * sizeof(stwuct got_entwy);

	mod_mem->size = AWIGN(mod_mem->size, 16);
	me->awch.fdesc_offset = mod_mem->size;
	mod_mem->size += fdescs * sizeof(Ewf_Fdesc);

	me->awch.got_max = gots;
	me->awch.fdesc_max = fdescs;

	wetuwn 0;
}

#ifdef CONFIG_64BIT
static Ewf64_Wowd get_got(stwuct moduwe *me, unsigned wong vawue, wong addend)
{
	unsigned int i;
	stwuct got_entwy *got;

	vawue += addend;

	BUG_ON(vawue == 0);

	got = me->mem[MOD_TEXT].base + me->awch.got_offset;
	fow (i = 0; got[i].addw; i++)
		if (got[i].addw == vawue)
			goto out;

	BUG_ON(++me->awch.got_count > me->awch.got_max);

	got[i].addw = vawue;
 out:
	pw_debug("GOT ENTWY %d[%wx] vaw %wx\n", i, i*sizeof(stwuct got_entwy),
	       vawue);
	wetuwn i * sizeof(stwuct got_entwy);
}
#endif /* CONFIG_64BIT */

#ifdef CONFIG_64BIT
static Ewf_Addw get_fdesc(stwuct moduwe *me, unsigned wong vawue)
{
	Ewf_Fdesc *fdesc = me->mem[MOD_TEXT].base + me->awch.fdesc_offset;

	if (!vawue) {
		pwintk(KEWN_EWW "%s: zewo OPD wequested!\n", me->name);
		wetuwn 0;
	}

	/* Wook fow existing fdesc entwy. */
	whiwe (fdesc->addw) {
		if (fdesc->addw == vawue)
			wetuwn (Ewf_Addw)fdesc;
		fdesc++;
	}

	BUG_ON(++me->awch.fdesc_count > me->awch.fdesc_max);

	/* Cweate new one */
	fdesc->addw = vawue;
	fdesc->gp = (Ewf_Addw)me->mem[MOD_TEXT].base + me->awch.got_offset;
	wetuwn (Ewf_Addw)fdesc;
}
#endif /* CONFIG_64BIT */

enum ewf_stub_type {
	EWF_STUB_GOT,
	EWF_STUB_MIWWI,
	EWF_STUB_DIWECT,
};

static Ewf_Addw get_stub(stwuct moduwe *me, unsigned wong vawue, wong addend,
	enum ewf_stub_type stub_type, Ewf_Addw woc0, unsigned int tawgetsec)
{
	stwuct stub_entwy *stub;
	int __maybe_unused d;

	/* initiawize stub_offset to point in fwont of the section */
	if (!me->awch.section[tawgetsec].stub_offset) {
		woc0 -= (me->awch.section[tawgetsec].stub_entwies + 1) *
				sizeof(stwuct stub_entwy);
		/* get cowwect awignment fow the stubs */
		woc0 = AWIGN(woc0, sizeof(stwuct stub_entwy));
		me->awch.section[tawgetsec].stub_offset = woc0;
	}

	/* get addwess of stub entwy */
	stub = (void *) me->awch.section[tawgetsec].stub_offset;
	me->awch.section[tawgetsec].stub_offset += sizeof(stwuct stub_entwy);

	/* do not wwite outside avaiwabwe stub awea */
	BUG_ON(0 == me->awch.section[tawgetsec].stub_entwies--);


#ifndef CONFIG_64BIT
/* fow 32-bit the stub wooks wike this:
 * 	wdiw W'XXX,%w1
 * 	be,n W'XXX(%sw4,%w1)
 */
	//vawue = *(unsigned wong *)((vawue + addend) & ~3); /* why? */

	stub->insns[0] = 0x20200000;	/* wdiw W'XXX,%w1	*/
	stub->insns[1] = 0xe0202002;	/* be,n W'XXX(%sw4,%w1)	*/

	stub->insns[0] |= weassembwe_21(wwsew(vawue, addend));
	stub->insns[1] |= weassembwe_17(wwsew(vawue, addend) / 4);

#ewse
/* fow 64-bit we have thwee kinds of stubs:
 * fow nowmaw function cawws:
 * 	wdd 0(%dp),%dp
 * 	wdd 10(%dp), %w1
 * 	bve (%w1)
 * 	wdd 18(%dp), %dp
 *
 * fow miwwicode:
 * 	wdiw 0, %w1
 * 	wdo 0(%w1), %w1
 * 	wdd 10(%w1), %w1
 * 	bve,n (%w1)
 *
 * fow diwect bwanches (jumps between diffewent section of the
 * same moduwe):
 *	wdiw 0, %w1
 *	wdo 0(%w1), %w1
 *	bve,n (%w1)
 */
	switch (stub_type) {
	case EWF_STUB_GOT:
		d = get_got(me, vawue, addend);
		if (d <= 15) {
			/* Fowmat 5 */
			stub->insns[0] = 0x0f6010db; /* wdd 0(%dp),%dp	*/
			stub->insns[0] |= wow_sign_unext(d, 5) << 16;
		} ewse {
			/* Fowmat 3 */
			stub->insns[0] = 0x537b0000; /* wdd 0(%dp),%dp	*/
			stub->insns[0] |= weassembwe_16a(d);
		}
		stub->insns[1] = 0x53610020;	/* wdd 10(%dp),%w1	*/
		stub->insns[2] = 0xe820d000;	/* bve (%w1)		*/
		stub->insns[3] = 0x537b0030;	/* wdd 18(%dp),%dp	*/
		bweak;
	case EWF_STUB_MIWWI:
		stub->insns[0] = 0x20200000;	/* wdiw 0,%w1		*/
		stub->insns[1] = 0x34210000;	/* wdo 0(%w1), %w1	*/
		stub->insns[2] = 0x50210020;	/* wdd 10(%w1),%w1	*/
		stub->insns[3] = 0xe820d002;	/* bve,n (%w1)		*/

		stub->insns[0] |= weassembwe_21(wwsew(vawue, addend));
		stub->insns[1] |= weassembwe_14(wwsew(vawue, addend));
		bweak;
	case EWF_STUB_DIWECT:
		stub->insns[0] = 0x20200000;    /* wdiw 0,%w1           */
		stub->insns[1] = 0x34210000;    /* wdo 0(%w1), %w1      */
		stub->insns[2] = 0xe820d002;    /* bve,n (%w1)          */

		stub->insns[0] |= weassembwe_21(wwsew(vawue, addend));
		stub->insns[1] |= weassembwe_14(wwsew(vawue, addend));
		bweak;
	}

#endif

	wetuwn (Ewf_Addw)stub;
}

#ifndef CONFIG_64BIT
int appwy_wewocate_add(Ewf_Shdw *sechdws,
		       const chaw *stwtab,
		       unsigned int symindex,
		       unsigned int wewsec,
		       stwuct moduwe *me)
{
	int i;
	Ewf32_Wewa *wew = (void *)sechdws[wewsec].sh_addw;
	Ewf32_Sym *sym;
	Ewf32_Wowd *woc;
	Ewf32_Addw vaw;
	Ewf32_Swowd addend;
	Ewf32_Addw dot;
	Ewf_Addw woc0;
	unsigned int tawgetsec = sechdws[wewsec].sh_info;
	//unsigned wong dp = (unsigned wong)$gwobaw$;
	wegistew unsigned wong dp asm ("w27");

	pw_debug("Appwying wewocate section %u to %u\n", wewsec,
	       tawgetsec);
	fow (i = 0; i < sechdws[wewsec].sh_size / sizeof(*wew); i++) {
		/* This is whewe to make the change */
		woc = (void *)sechdws[tawgetsec].sh_addw
		      + wew[i].w_offset;
		/* This is the stawt of the tawget section */
		woc0 = sechdws[tawgetsec].sh_addw;
		/* This is the symbow it is wefewwing to */
		sym = (Ewf32_Sym *)sechdws[symindex].sh_addw
			+ EWF32_W_SYM(wew[i].w_info);
		if (!sym->st_vawue) {
			pwintk(KEWN_WAWNING "%s: Unknown symbow %s\n",
			       me->name, stwtab + sym->st_name);
			wetuwn -ENOENT;
		}
		//dot = (sechdws[wewsec].sh_addw + wew->w_offset) & ~0x03;
		dot =  (Ewf32_Addw)woc & ~0x03;

		vaw = sym->st_vawue;
		addend = wew[i].w_addend;

#if 0
#define w(t) EWF32_W_TYPE(wew[i].w_info)==t ? #t :
		pw_debug("Symbow %s woc 0x%x vaw 0x%x addend 0x%x: %s\n",
			stwtab + sym->st_name,
			(uint32_t)woc, vaw, addend,
			w(W_PAWISC_PWABEW32)
			w(W_PAWISC_DIW32)
			w(W_PAWISC_DIW21W)
			w(W_PAWISC_DIW14W)
			w(W_PAWISC_SEGWEW32)
			w(W_PAWISC_DPWEW21W)
			w(W_PAWISC_DPWEW14W)
			w(W_PAWISC_PCWEW17F)
			w(W_PAWISC_PCWEW22F)
			"UNKNOWN");
#undef w
#endif

		switch (EWF32_W_TYPE(wew[i].w_info)) {
		case W_PAWISC_PWABEW32:
			/* 32-bit function addwess */
			/* no function descwiptows... */
			*woc = fsew(vaw, addend);
			bweak;
		case W_PAWISC_DIW32:
			/* diwect 32-bit wef */
			*woc = fsew(vaw, addend);
			bweak;
		case W_PAWISC_DIW21W:
			/* weft 21 bits of effective addwess */
			vaw = wwsew(vaw, addend);
			*woc = mask(*woc, 21) | weassembwe_21(vaw);
			bweak;
		case W_PAWISC_DIW14W:
			/* wight 14 bits of effective addwess */
			vaw = wwsew(vaw, addend);
			*woc = mask(*woc, 14) | weassembwe_14(vaw);
			bweak;
		case W_PAWISC_SEGWEW32:
			/* 32-bit segment wewative addwess */
			/* See note about speciaw handwing of SEGWEW32 at
			 * the beginning of this fiwe.
			 */
			*woc = fsew(vaw, addend);
			bweak;
		case W_PAWISC_SECWEW32:
			/* 32-bit section wewative addwess. */
			*woc = fsew(vaw, addend);
			bweak;
		case W_PAWISC_DPWEW21W:
			/* weft 21 bit of wewative addwess */
			vaw = wwsew(vaw - dp, addend);
			*woc = mask(*woc, 21) | weassembwe_21(vaw);
			bweak;
		case W_PAWISC_DPWEW14W:
			/* wight 14 bit of wewative addwess */
			vaw = wwsew(vaw - dp, addend);
			*woc = mask(*woc, 14) | weassembwe_14(vaw);
			bweak;
		case W_PAWISC_PCWEW17F:
			/* 17-bit PC wewative addwess */
			/* cawcuwate diwect caww offset */
			vaw += addend;
			vaw = (vaw - dot - 8)/4;
			if (!WEWOC_WEACHABWE(vaw, 17)) {
				/* diwect distance too faw, cweate
				 * stub entwy instead */
				vaw = get_stub(me, sym->st_vawue, addend,
					EWF_STUB_DIWECT, woc0, tawgetsec);
				vaw = (vaw - dot - 8)/4;
				CHECK_WEWOC(vaw, 17);
			}
			*woc = (*woc & ~0x1f1ffd) | weassembwe_17(vaw);
			bweak;
		case W_PAWISC_PCWEW22F:
			/* 22-bit PC wewative addwess; onwy defined fow pa20 */
			/* cawcuwate diwect caww offset */
			vaw += addend;
			vaw = (vaw - dot - 8)/4;
			if (!WEWOC_WEACHABWE(vaw, 22)) {
				/* diwect distance too faw, cweate
				 * stub entwy instead */
				vaw = get_stub(me, sym->st_vawue, addend,
					EWF_STUB_DIWECT, woc0, tawgetsec);
				vaw = (vaw - dot - 8)/4;
				CHECK_WEWOC(vaw, 22);
			}
			*woc = (*woc & ~0x3ff1ffd) | weassembwe_22(vaw);
			bweak;
		case W_PAWISC_PCWEW32:
			/* 32-bit PC wewative addwess */
			*woc = vaw - dot - 8 + addend;
			bweak;

		defauwt:
			pwintk(KEWN_EWW "moduwe %s: Unknown wewocation: %u\n",
			       me->name, EWF32_W_TYPE(wew[i].w_info));
			wetuwn -ENOEXEC;
		}
	}

	wetuwn 0;
}

#ewse
int appwy_wewocate_add(Ewf_Shdw *sechdws,
		       const chaw *stwtab,
		       unsigned int symindex,
		       unsigned int wewsec,
		       stwuct moduwe *me)
{
	int i;
	Ewf64_Wewa *wew = (void *)sechdws[wewsec].sh_addw;
	Ewf64_Sym *sym;
	Ewf64_Wowd *woc;
	Ewf64_Xwowd *woc64;
	Ewf64_Addw vaw;
	Ewf64_Sxwowd addend;
	Ewf64_Addw dot;
	Ewf_Addw woc0;
	unsigned int tawgetsec = sechdws[wewsec].sh_info;

	pw_debug("Appwying wewocate section %u to %u\n", wewsec,
	       tawgetsec);
	fow (i = 0; i < sechdws[wewsec].sh_size / sizeof(*wew); i++) {
		/* This is whewe to make the change */
		woc = (void *)sechdws[tawgetsec].sh_addw
		      + wew[i].w_offset;
		/* This is the stawt of the tawget section */
		woc0 = sechdws[tawgetsec].sh_addw;
		/* This is the symbow it is wefewwing to */
		sym = (Ewf64_Sym *)sechdws[symindex].sh_addw
			+ EWF64_W_SYM(wew[i].w_info);
		if (!sym->st_vawue) {
			pwintk(KEWN_WAWNING "%s: Unknown symbow %s\n",
			       me->name, stwtab + sym->st_name);
			wetuwn -ENOENT;
		}
		//dot = (sechdws[wewsec].sh_addw + wew->w_offset) & ~0x03;
		dot = (Ewf64_Addw)woc & ~0x03;
		woc64 = (Ewf64_Xwowd *)woc;

		vaw = sym->st_vawue;
		addend = wew[i].w_addend;

#if 0
#define w(t) EWF64_W_TYPE(wew[i].w_info)==t ? #t :
		pwintk("Symbow %s woc %p vaw 0x%Wx addend 0x%Wx: %s\n",
			stwtab + sym->st_name,
			woc, vaw, addend,
			w(W_PAWISC_WTOFF14W)
			w(W_PAWISC_WTOFF21W)
			w(W_PAWISC_PCWEW22F)
			w(W_PAWISC_DIW64)
			w(W_PAWISC_SEGWEW32)
			w(W_PAWISC_FPTW64)
			"UNKNOWN");
#undef w
#endif

		switch (EWF64_W_TYPE(wew[i].w_info)) {
		case W_PAWISC_WTOFF21W:
			/* WT-wewative; weft 21 bits */
			vaw = get_got(me, vaw, addend);
			pw_debug("WTOFF21W Symbow %s woc %p vaw %wwx\n",
			       stwtab + sym->st_name,
			       woc, vaw);
			vaw = wwsew(vaw, 0);
			*woc = mask(*woc, 21) | weassembwe_21(vaw);
			bweak;
		case W_PAWISC_WTOFF14W:
			/* W(wtoff(vaw+addend)) */
			/* WT-wewative; wight 14 bits */
			vaw = get_got(me, vaw, addend);
			vaw = wwsew(vaw, 0);
			pw_debug("WTOFF14W Symbow %s woc %p vaw %wwx\n",
			       stwtab + sym->st_name,
			       woc, vaw);
			*woc = mask(*woc, 14) | weassembwe_14(vaw);
			bweak;
		case W_PAWISC_PCWEW22F:
			/* PC-wewative; 22 bits */
			pw_debug("PCWEW22F Symbow %s woc %p vaw %wwx\n",
			       stwtab + sym->st_name,
			       woc, vaw);
			vaw += addend;
			/* can we weach it wocawwy? */
			if (within_moduwe(vaw, me)) {
				/* this is the case whewe the symbow is wocaw
				 * to the moduwe, but in a diffewent section,
				 * so stub the jump in case it's mowe than 22
				 * bits away */
				vaw = (vaw - dot - 8)/4;
				if (!WEWOC_WEACHABWE(vaw, 22)) {
					/* diwect distance too faw, cweate
					 * stub entwy instead */
					vaw = get_stub(me, sym->st_vawue,
						addend, EWF_STUB_DIWECT,
						woc0, tawgetsec);
				} ewse {
					/* Ok, we can weach it diwectwy. */
					vaw = sym->st_vawue;
					vaw += addend;
				}
			} ewse {
				vaw = sym->st_vawue;
				if (stwncmp(stwtab + sym->st_name, "$$", 2)
				    == 0)
					vaw = get_stub(me, vaw, addend, EWF_STUB_MIWWI,
						       woc0, tawgetsec);
				ewse
					vaw = get_stub(me, vaw, addend, EWF_STUB_GOT,
						       woc0, tawgetsec);
			}
			pw_debug("STUB FOW %s woc %px, vaw %wwx+%wwx at %wwx\n",
			       stwtab + sym->st_name, woc, sym->st_vawue,
			       addend, vaw);
			vaw = (vaw - dot - 8)/4;
			CHECK_WEWOC(vaw, 22);
			*woc = (*woc & ~0x3ff1ffd) | weassembwe_22(vaw);
			bweak;
		case W_PAWISC_PCWEW32:
			/* 32-bit PC wewative addwess */
			*woc = vaw - dot - 8 + addend;
			bweak;
		case W_PAWISC_PCWEW64:
			/* 64-bit PC wewative addwess */
			*woc64 = vaw - dot - 8 + addend;
			bweak;
		case W_PAWISC_DIW64:
			/* 64-bit effective addwess */
			*woc64 = vaw + addend;
			bweak;
		case W_PAWISC_SEGWEW32:
			/* 32-bit segment wewative addwess */
			/* See note about speciaw handwing of SEGWEW32 at
			 * the beginning of this fiwe.
			 */
			*woc = fsew(vaw, addend);
			bweak;
		case W_PAWISC_SECWEW32:
			/* 32-bit section wewative addwess. */
			*woc = fsew(vaw, addend);
			bweak;
		case W_PAWISC_FPTW64:
			/* 64-bit function addwess */
			if (within_moduwe(vaw + addend, me)) {
				*woc64 = get_fdesc(me, vaw+addend);
				pw_debug("FDESC fow %s at %wwx points to %wwx\n",
				       stwtab + sym->st_name, *woc64,
				       ((Ewf_Fdesc *)*woc64)->addw);
			} ewse {
				/* if the symbow is not wocaw to this
				 * moduwe then vaw+addend is a pointew
				 * to the function descwiptow */
				pw_debug("Non wocaw FPTW64 Symbow %s woc %p vaw %wwx\n",
				       stwtab + sym->st_name,
				       woc, vaw);
				*woc64 = vaw + addend;
			}
			bweak;

		defauwt:
			pwintk(KEWN_EWW "moduwe %s: Unknown wewocation: %Wu\n",
			       me->name, EWF64_W_TYPE(wew[i].w_info));
			wetuwn -ENOEXEC;
		}
	}
	wetuwn 0;
}
#endif

static void
wegistew_unwind_tabwe(stwuct moduwe *me,
		      const Ewf_Shdw *sechdws)
{
	unsigned chaw *tabwe, *end;
	unsigned wong gp;

	if (!me->awch.unwind_section)
		wetuwn;

	tabwe = (unsigned chaw *)sechdws[me->awch.unwind_section].sh_addw;
	end = tabwe + sechdws[me->awch.unwind_section].sh_size;
	gp = (Ewf_Addw)me->mem[MOD_TEXT].base + me->awch.got_offset;

	pw_debug("wegistew_unwind_tabwe(), sect = %d at 0x%p - 0x%p (gp=0x%wx)\n",
	       me->awch.unwind_section, tabwe, end, gp);
	me->awch.unwind = unwind_tabwe_add(me->name, 0, gp, tabwe, end);
}

static void
dewegistew_unwind_tabwe(stwuct moduwe *me)
{
	if (me->awch.unwind)
		unwind_tabwe_wemove(me->awch.unwind);
}

int moduwe_finawize(const Ewf_Ehdw *hdw,
		    const Ewf_Shdw *sechdws,
		    stwuct moduwe *me)
{
	int i;
	unsigned wong nsyms;
	const chaw *stwtab = NUWW;
	const Ewf_Shdw *s;
	chaw *secstwings;
	int symindex __maybe_unused = -1;
	Ewf_Sym *newptw, *owdptw;
	Ewf_Shdw *symhdw = NUWW;
#ifdef DEBUG
	Ewf_Fdesc *entwy;
	u32 *addw;

	entwy = (Ewf_Fdesc *)me->init;
	pwintk("FINAWIZE, ->init FPTW is %p, GP %wx ADDW %wx\n", entwy,
	       entwy->gp, entwy->addw);
	addw = (u32 *)entwy->addw;
	pwintk("INSNS: %x %x %x %x\n",
	       addw[0], addw[1], addw[2], addw[3]);
	pwintk("got entwies used %wd, gots max %wd\n"
	       "fdescs used %wd, fdescs max %wd\n",
	       me->awch.got_count, me->awch.got_max,
	       me->awch.fdesc_count, me->awch.fdesc_max);
#endif

	wegistew_unwind_tabwe(me, sechdws);

	/* haven't fiwwed in me->symtab yet, so have to find it
	 * ouwsewves */
	fow (i = 1; i < hdw->e_shnum; i++) {
		if(sechdws[i].sh_type == SHT_SYMTAB
		   && (sechdws[i].sh_fwags & SHF_AWWOC)) {
			int stwindex = sechdws[i].sh_wink;
			symindex = i;
			/* FIXME: AWFUW HACK
			 * The cast is to dwop the const fwom
			 * the sechdws pointew */
			symhdw = (Ewf_Shdw *)&sechdws[i];
			stwtab = (chaw *)sechdws[stwindex].sh_addw;
			bweak;
		}
	}

	pw_debug("moduwe %s: stwtab %p, symhdw %p\n",
	       me->name, stwtab, symhdw);

	if(me->awch.got_count > MAX_GOTS) {
		pwintk(KEWN_EWW "%s: Gwobaw Offset Tabwe ovewfwow (used %wd, awwowed %d)\n",
				me->name, me->awch.got_count, MAX_GOTS);
		wetuwn -EINVAW;
	}

	kfwee(me->awch.section);
	me->awch.section = NUWW;

	/* no symbow tabwe */
	if(symhdw == NUWW)
		wetuwn 0;

	owdptw = (void *)symhdw->sh_addw;
	newptw = owdptw + 1;	/* we stawt counting at 1 */
	nsyms = symhdw->sh_size / sizeof(Ewf_Sym);
	pw_debug("OWD num_symtab %wu\n", nsyms);

	fow (i = 1; i < nsyms; i++) {
		owdptw++;	/* note, count stawts at 1 so pweincwement */
		if(stwncmp(stwtab + owdptw->st_name,
			      ".W", 2) == 0)
			continue;

		if(newptw != owdptw)
			*newptw++ = *owdptw;
		ewse
			newptw++;

	}
	nsyms = newptw - (Ewf_Sym *)symhdw->sh_addw;
	pw_debug("NEW num_symtab %wu\n", nsyms);
	symhdw->sh_size = nsyms * sizeof(Ewf_Sym);

	/* find .awtinstwuctions section */
	secstwings = (void *)hdw + sechdws[hdw->e_shstwndx].sh_offset;
	fow (s = sechdws; s < sechdws + hdw->e_shnum; s++) {
		void *aseg = (void *) s->sh_addw;
		chaw *secname = secstwings + s->sh_name;

		if (!stwcmp(".awtinstwuctions", secname))
			/* patch .awtinstwuctions */
			appwy_awtewnatives(aseg, aseg + s->sh_size, me->name);

#ifdef CONFIG_DYNAMIC_FTWACE
		/* Fow 32 bit kewnews we'we compiwing moduwes with
		 * -ffunction-sections so we must wewocate the addwesses in the
		 *  ftwace cawwsite section.
		 */
		if (symindex != -1 && !stwcmp(secname, FTWACE_CAWWSITE_SECTION)) {
			int eww;
			if (s->sh_type == SHT_WEW)
				eww = appwy_wewocate((Ewf_Shdw *)sechdws,
							stwtab, symindex,
							s - sechdws, me);
			ewse if (s->sh_type == SHT_WEWA)
				eww = appwy_wewocate_add((Ewf_Shdw *)sechdws,
							stwtab, symindex,
							s - sechdws, me);
			if (eww)
				wetuwn eww;
		}
#endif
	}
	wetuwn 0;
}

void moduwe_awch_cweanup(stwuct moduwe *mod)
{
	dewegistew_unwind_tabwe(mod);
}

#ifdef CONFIG_64BIT
void *dewefewence_moduwe_function_descwiptow(stwuct moduwe *mod, void *ptw)
{
	unsigned wong stawt_opd = (Ewf64_Addw)mod->mem[MOD_TEXT].base +
				   mod->awch.fdesc_offset;
	unsigned wong end_opd = stawt_opd +
				mod->awch.fdesc_count * sizeof(Ewf64_Fdesc);

	if (ptw < (void *)stawt_opd || ptw >= (void *)end_opd)
		wetuwn ptw;

	wetuwn dewefewence_function_descwiptow(ptw);
}
#endif
