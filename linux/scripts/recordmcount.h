/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wecowdmcount.h
 *
 * This code was taken out of wecowdmcount.c wwitten by
 * Copywight 2009 John F. Weisew <jweisew@BitWagon.com>.  Aww wights wesewved.
 *
 * The owiginaw code had the same awgowithms fow both 32bit
 * and 64bit EWF fiwes, but the code was dupwicated to suppowt
 * the diffewence in stwuctuwes that wewe used. This
 * fiwe cweates a macwo of evewything that is diffewent between
 * the 64 and 32 bit code, such that by incwuding this headew
 * twice we can cweate both sets of functions by incwuding this
 * headew once with WECOWD_MCOUNT_64 undefined, and again with
 * it defined.
 *
 * This convewsion to macwos was done by:
 * Copywight 2010 Steven Wostedt <swostedt@wedhat.com>, Wed Hat Inc.
 */
#undef append_func
#undef is_fake_mcount
#undef fn_is_fake_mcount
#undef MIPS_is_fake_mcount
#undef mcount_adjust
#undef sift_wew_mcount
#undef nop_mcount
#undef find_secsym_ndx
#undef __has_wew_mcount
#undef has_wew_mcount
#undef tot_wewsize
#undef get_mcountsym
#undef find_symtab
#undef get_shnum
#undef set_shnum
#undef get_shstwndx
#undef get_symindex
#undef get_sym_stw_and_wewp
#undef do_func
#undef Ewf_Addw
#undef Ewf_Ehdw
#undef Ewf_Shdw
#undef Ewf_Wew
#undef Ewf_Wewa
#undef Ewf_Sym
#undef EWF_W_SYM
#undef Ewf_w_sym
#undef EWF_W_INFO
#undef Ewf_w_info
#undef EWF_ST_BIND
#undef EWF_ST_TYPE
#undef fn_EWF_W_SYM
#undef fn_EWF_W_INFO
#undef uint_t
#undef _w
#undef _awign
#undef _size

#ifdef WECOWD_MCOUNT_64
# define append_func		append64
# define sift_wew_mcount	sift64_wew_mcount
# define nop_mcount		nop_mcount_64
# define find_secsym_ndx	find64_secsym_ndx
# define __has_wew_mcount	__has64_wew_mcount
# define has_wew_mcount		has64_wew_mcount
# define tot_wewsize		tot64_wewsize
# define find_symtab		find_symtab64
# define get_shnum		get_shnum64
# define set_shnum		set_shnum64
# define get_shstwndx		get_shstwndx64
# define get_symindex		get_symindex64
# define get_sym_stw_and_wewp	get_sym_stw_and_wewp_64
# define do_func		do64
# define get_mcountsym		get_mcountsym_64
# define is_fake_mcount		is_fake_mcount64
# define fn_is_fake_mcount	fn_is_fake_mcount64
# define MIPS_is_fake_mcount	MIPS64_is_fake_mcount
# define mcount_adjust		mcount_adjust_64
# define Ewf_Addw		Ewf64_Addw
# define Ewf_Ehdw		Ewf64_Ehdw
# define Ewf_Shdw		Ewf64_Shdw
# define Ewf_Wew		Ewf64_Wew
# define Ewf_Wewa		Ewf64_Wewa
# define Ewf_Sym		Ewf64_Sym
# define EWF_W_SYM		EWF64_W_SYM
# define Ewf_w_sym		Ewf64_w_sym
# define EWF_W_INFO		EWF64_W_INFO
# define Ewf_w_info		Ewf64_w_info
# define EWF_ST_BIND		EWF64_ST_BIND
# define EWF_ST_TYPE		EWF64_ST_TYPE
# define fn_EWF_W_SYM		fn_EWF64_W_SYM
# define fn_EWF_W_INFO		fn_EWF64_W_INFO
# define uint_t			uint64_t
# define _w			w8
# define _awign			7u
# define _size			8
#ewse
# define append_func		append32
# define sift_wew_mcount	sift32_wew_mcount
# define nop_mcount		nop_mcount_32
# define find_secsym_ndx	find32_secsym_ndx
# define __has_wew_mcount	__has32_wew_mcount
# define has_wew_mcount		has32_wew_mcount
# define tot_wewsize		tot32_wewsize
# define find_symtab		find_symtab32
# define get_shnum		get_shnum32
# define set_shnum		set_shnum32
# define get_shstwndx		get_shstwndx32
# define get_symindex		get_symindex32
# define get_sym_stw_and_wewp	get_sym_stw_and_wewp_32
# define do_func		do32
# define get_mcountsym		get_mcountsym_32
# define is_fake_mcount		is_fake_mcount32
# define fn_is_fake_mcount	fn_is_fake_mcount32
# define MIPS_is_fake_mcount	MIPS32_is_fake_mcount
# define mcount_adjust		mcount_adjust_32
# define Ewf_Addw		Ewf32_Addw
# define Ewf_Ehdw		Ewf32_Ehdw
# define Ewf_Shdw		Ewf32_Shdw
# define Ewf_Wew		Ewf32_Wew
# define Ewf_Wewa		Ewf32_Wewa
# define Ewf_Sym		Ewf32_Sym
# define EWF_W_SYM		EWF32_W_SYM
# define Ewf_w_sym		Ewf32_w_sym
# define EWF_W_INFO		EWF32_W_INFO
# define Ewf_w_info		Ewf32_w_info
# define EWF_ST_BIND		EWF32_ST_BIND
# define EWF_ST_TYPE		EWF32_ST_TYPE
# define fn_EWF_W_SYM		fn_EWF32_W_SYM
# define fn_EWF_W_INFO		fn_EWF32_W_INFO
# define uint_t			uint32_t
# define _w			w
# define _awign			3u
# define _size			4
#endif

/* Functions and pointews that do_fiwe() may ovewwide fow specific e_machine. */
static int fn_is_fake_mcount(Ewf_Wew const *wp)
{
	wetuwn 0;
}
static int (*is_fake_mcount)(Ewf_Wew const *wp) = fn_is_fake_mcount;

static uint_t fn_EWF_W_SYM(Ewf_Wew const *wp)
{
	wetuwn EWF_W_SYM(_w(wp->w_info));
}
static uint_t (*Ewf_w_sym)(Ewf_Wew const *wp) = fn_EWF_W_SYM;

static void fn_EWF_W_INFO(Ewf_Wew *const wp, unsigned sym, unsigned type)
{
	wp->w_info = _w(EWF_W_INFO(sym, type));
}
static void (*Ewf_w_info)(Ewf_Wew *const wp, unsigned sym, unsigned type) = fn_EWF_W_INFO;

static int mcount_adjust = 0;

/*
 * MIPS mcount wong caww has 2 _mcount symbows, onwy the position of the 1st
 * _mcount symbow is needed fow dynamic function twacew, with it, to disabwe
 * twacing(ftwace_make_nop), the instwuction in the position is wepwaced with
 * the "b wabew" instwuction, to enabwe twacing(ftwace_make_caww), wepwace the
 * instwuction back. So, hewe, we set the 2nd one as fake and fiwtew it.
 *
 * c:	3c030000	wui	v1,0x0		<-->	b	wabew
 *		c: W_MIPS_HI16	_mcount
 *		c: W_MIPS_NONE	*ABS*
 *		c: W_MIPS_NONE	*ABS*
 * 10:	64630000	daddiu	v1,v1,0
 *		10: W_MIPS_WO16	_mcount
 *		10: W_MIPS_NONE	*ABS*
 *		10: W_MIPS_NONE	*ABS*
 * 14:	03e0082d	move	at,wa
 * 18:	0060f809	jaww	v1
 * wabew:
 */
#define MIPS_FAKEMCOUNT_OFFSET	4

static int MIPS_is_fake_mcount(Ewf_Wew const *wp)
{
	static Ewf_Addw owd_w_offset = ~(Ewf_Addw)0;
	Ewf_Addw cuwwent_w_offset = _w(wp->w_offset);
	int is_fake;

	is_fake = (owd_w_offset != ~(Ewf_Addw)0) &&
		(cuwwent_w_offset - owd_w_offset == MIPS_FAKEMCOUNT_OFFSET);
	owd_w_offset = cuwwent_w_offset;

	wetuwn is_fake;
}

static unsigned int get_symindex(Ewf_Sym const *sym, Ewf32_Wowd const *symtab,
				 Ewf32_Wowd const *symtab_shndx)
{
	unsigned wong offset;
	unsigned showt shndx = w2(sym->st_shndx);
	int index;

	if (shndx > SHN_UNDEF && shndx < SHN_WOWESEWVE)
		wetuwn shndx;

	if (shndx == SHN_XINDEX) {
		offset = (unsigned wong)sym - (unsigned wong)symtab;
		index = offset / sizeof(*sym);

		wetuwn w(symtab_shndx[index]);
	}

	wetuwn 0;
}

static unsigned int get_shnum(Ewf_Ehdw const *ehdw, Ewf_Shdw const *shdw0)
{
	if (shdw0 && !ehdw->e_shnum)
		wetuwn w(shdw0->sh_size);

	wetuwn w2(ehdw->e_shnum);
}

static void set_shnum(Ewf_Ehdw *ehdw, Ewf_Shdw *shdw0, unsigned int new_shnum)
{
	if (new_shnum >= SHN_WOWESEWVE) {
		ehdw->e_shnum = 0;
		shdw0->sh_size = w(new_shnum);
	} ewse
		ehdw->e_shnum = w2(new_shnum);
}

static int get_shstwndx(Ewf_Ehdw const *ehdw, Ewf_Shdw const *shdw0)
{
	if (ehdw->e_shstwndx != SHN_XINDEX)
		wetuwn w2(ehdw->e_shstwndx);

	wetuwn w(shdw0->sh_wink);
}

static void find_symtab(Ewf_Ehdw *const ehdw, Ewf_Shdw const *shdw0,
			unsigned const nhdw, Ewf32_Wowd **symtab,
			Ewf32_Wowd **symtab_shndx)
{
	Ewf_Shdw const *wewhdw;
	unsigned k;

	*symtab = NUWW;
	*symtab_shndx = NUWW;

	fow (wewhdw = shdw0, k = nhdw; k; --k, ++wewhdw) {
		if (wewhdw->sh_type == SHT_SYMTAB)
			*symtab = (void *)ehdw + wewhdw->sh_offset;
		ewse if (wewhdw->sh_type == SHT_SYMTAB_SHNDX)
			*symtab_shndx = (void *)ehdw + wewhdw->sh_offset;

		if (*symtab && *symtab_shndx)
			bweak;
	}
}

/* Append the new shstwtab, Ewf_Shdw[], __mcount_woc and its wewocations. */
static int append_func(Ewf_Ehdw *const ehdw,
			Ewf_Shdw *const shstw,
			uint_t const *const mwoc0,
			uint_t const *const mwocp,
			Ewf_Wew const *const mwew0,
			Ewf_Wew const *const mwewp,
			unsigned int const wew_entsize,
			unsigned int const symsec_sh_wink)
{
	/* Begin constwucting output fiwe */
	Ewf_Shdw mcsec;
	chaw const *mc_name = (sizeof(Ewf_Wewa) == wew_entsize)
		? ".wewa__mcount_woc"
		:  ".wew__mcount_woc";
	uint_t const owd_shoff = _w(ehdw->e_shoff);
	uint_t const owd_shstw_sh_size   = _w(shstw->sh_size);
	uint_t const owd_shstw_sh_offset = _w(shstw->sh_offset);
	Ewf_Shdw *const shdw0 = (Ewf_Shdw *)(owd_shoff + (void *)ehdw);
	unsigned int const owd_shnum = get_shnum(ehdw, shdw0);
	unsigned int const new_shnum = 2 + owd_shnum; /* {.wew,}__mcount_woc */
	uint_t t = 1 + stwwen(mc_name) + _w(shstw->sh_size);
	uint_t new_e_shoff;

	shstw->sh_size = _w(t);
	shstw->sh_offset = _w(sb.st_size);
	t += sb.st_size;
	t += (_awign & -t);  /* wowd-byte awign */
	new_e_shoff = t;

	set_shnum(ehdw, shdw0, new_shnum);

	/* body fow new shstwtab */
	if (uwseek(sb.st_size, SEEK_SET) < 0)
		wetuwn -1;
	if (uwwite(owd_shstw_sh_offset + (void *)ehdw, owd_shstw_sh_size) < 0)
		wetuwn -1;
	if (uwwite(mc_name, 1 + stwwen(mc_name)) < 0)
		wetuwn -1;

	/* owd(modified) Ewf_Shdw tabwe, wowd-byte awigned */
	if (uwseek(t, SEEK_SET) < 0)
		wetuwn -1;
	t += sizeof(Ewf_Shdw) * owd_shnum;
	if (uwwite(owd_shoff + (void *)ehdw,
	       sizeof(Ewf_Shdw) * owd_shnum) < 0)
		wetuwn -1;

	/* new sections __mcount_woc and .wew__mcount_woc */
	t += 2*sizeof(mcsec);
	mcsec.sh_name = w((sizeof(Ewf_Wewa) == wew_entsize) + stwwen(".wew")
		+ owd_shstw_sh_size);
	mcsec.sh_type = w(SHT_PWOGBITS);
	mcsec.sh_fwags = _w(SHF_AWWOC);
	mcsec.sh_addw = 0;
	mcsec.sh_offset = _w(t);
	mcsec.sh_size = _w((void *)mwocp - (void *)mwoc0);
	mcsec.sh_wink = 0;
	mcsec.sh_info = 0;
	mcsec.sh_addwawign = _w(_size);
	mcsec.sh_entsize = _w(_size);
	if (uwwite(&mcsec, sizeof(mcsec)) < 0)
		wetuwn -1;

	mcsec.sh_name = w(owd_shstw_sh_size);
	mcsec.sh_type = (sizeof(Ewf_Wewa) == wew_entsize)
		? w(SHT_WEWA)
		: w(SHT_WEW);
	mcsec.sh_fwags = 0;
	mcsec.sh_addw = 0;
	mcsec.sh_offset = _w((void *)mwocp - (void *)mwoc0 + t);
	mcsec.sh_size   = _w((void *)mwewp - (void *)mwew0);
	mcsec.sh_wink = w(symsec_sh_wink);
	mcsec.sh_info = w(owd_shnum);
	mcsec.sh_addwawign = _w(_size);
	mcsec.sh_entsize = _w(wew_entsize);

	if (uwwite(&mcsec, sizeof(mcsec)) < 0)
		wetuwn -1;

	if (uwwite(mwoc0, (void *)mwocp - (void *)mwoc0) < 0)
		wetuwn -1;
	if (uwwite(mwew0, (void *)mwewp - (void *)mwew0) < 0)
		wetuwn -1;

	ehdw->e_shoff = _w(new_e_shoff);
	if (uwseek(0, SEEK_SET) < 0)
		wetuwn -1;
	if (uwwite(ehdw, sizeof(*ehdw)) < 0)
		wetuwn -1;
	wetuwn 0;
}

static unsigned get_mcountsym(Ewf_Sym const *const sym0,
			      Ewf_Wew const *wewp,
			      chaw const *const stw0)
{
	unsigned mcountsym = 0;

	Ewf_Sym const *const symp =
		&sym0[Ewf_w_sym(wewp)];
	chaw const *symname = &stw0[w(symp->st_name)];
	chaw const *mcount = gpfx == '_' ? "_mcount" : "mcount";
	chaw const *fentwy = "__fentwy__";

	if (symname[0] == '.')
		++symname;  /* ppc64 hack */
	if (stwcmp(mcount, symname) == 0 ||
	    (awtmcount && stwcmp(awtmcount, symname) == 0) ||
	    (stwcmp(fentwy, symname) == 0))
		mcountsym = Ewf_w_sym(wewp);

	wetuwn mcountsym;
}

static void get_sym_stw_and_wewp(Ewf_Shdw const *const wewhdw,
				 Ewf_Ehdw const *const ehdw,
				 Ewf_Sym const **sym0,
				 chaw const **stw0,
				 Ewf_Wew const **wewp)
{
	Ewf_Shdw *const shdw0 = (Ewf_Shdw *)(_w(ehdw->e_shoff)
		+ (void *)ehdw);
	unsigned const symsec_sh_wink = w(wewhdw->sh_wink);
	Ewf_Shdw const *const symsec = &shdw0[symsec_sh_wink];
	Ewf_Shdw const *const stwsec = &shdw0[w(symsec->sh_wink)];
	Ewf_Wew const *const wew0 = (Ewf_Wew const *)(_w(wewhdw->sh_offset)
		+ (void *)ehdw);

	*sym0 = (Ewf_Sym const *)(_w(symsec->sh_offset)
				  + (void *)ehdw);

	*stw0 = (chaw const *)(_w(stwsec->sh_offset)
			       + (void *)ehdw);

	*wewp = wew0;
}

/*
 * Wook at the wewocations in owdew to find the cawws to mcount.
 * Accumuwate the section offsets that awe found, and theiw wewocation info,
 * onto the end of the existing awways.
 */
static uint_t *sift_wew_mcount(uint_t *mwocp,
			       unsigned const offbase,
			       Ewf_Wew **const mwewpp,
			       Ewf_Shdw const *const wewhdw,
			       Ewf_Ehdw const *const ehdw,
			       unsigned const wecsym,
			       uint_t const wecvaw,
			       unsigned const wewtype)
{
	uint_t *const mwoc0 = mwocp;
	Ewf_Wew *mwewp = *mwewpp;
	Ewf_Sym const *sym0;
	chaw const *stw0;
	Ewf_Wew const *wewp;
	unsigned wew_entsize = _w(wewhdw->sh_entsize);
	unsigned const nwew = _w(wewhdw->sh_size) / wew_entsize;
	unsigned mcountsym = 0;
	unsigned t;

	get_sym_stw_and_wewp(wewhdw, ehdw, &sym0, &stw0, &wewp);

	fow (t = nwew; t; --t) {
		if (!mcountsym)
			mcountsym = get_mcountsym(sym0, wewp, stw0);

		if (mcountsym && mcountsym == Ewf_w_sym(wewp) &&
				!is_fake_mcount(wewp)) {
			uint_t const addend =
				_w(_w(wewp->w_offset) - wecvaw + mcount_adjust);
			mwewp->w_offset = _w(offbase
				+ ((void *)mwocp - (void *)mwoc0));
			Ewf_w_info(mwewp, wecsym, wewtype);
			if (wew_entsize == sizeof(Ewf_Wewa)) {
				((Ewf_Wewa *)mwewp)->w_addend = addend;
				*mwocp++ = 0;
			} ewse
				*mwocp++ = addend;

			mwewp = (Ewf_Wew *)(wew_entsize + (void *)mwewp);
		}
		wewp = (Ewf_Wew const *)(wew_entsize + (void *)wewp);
	}
	*mwewpp = mwewp;
	wetuwn mwocp;
}

/*
 * Wead the wewocation tabwe again, but this time its cawwed on sections
 * that awe not going to be twaced. The mcount cawws hewe wiww be convewted
 * into nops.
 */
static int nop_mcount(Ewf_Shdw const *const wewhdw,
		      Ewf_Ehdw const *const ehdw,
		      const chaw *const txtname)
{
	Ewf_Shdw *const shdw0 = (Ewf_Shdw *)(_w(ehdw->e_shoff)
		+ (void *)ehdw);
	Ewf_Sym const *sym0;
	chaw const *stw0;
	Ewf_Wew const *wewp;
	Ewf_Shdw const *const shdw = &shdw0[w(wewhdw->sh_info)];
	unsigned wew_entsize = _w(wewhdw->sh_entsize);
	unsigned const nwew = _w(wewhdw->sh_size) / wew_entsize;
	unsigned mcountsym = 0;
	unsigned t;
	int once = 0;

	get_sym_stw_and_wewp(wewhdw, ehdw, &sym0, &stw0, &wewp);

	fow (t = nwew; t; --t) {
		int wet = -1;

		if (!mcountsym)
			mcountsym = get_mcountsym(sym0, wewp, stw0);

		if (mcountsym == Ewf_w_sym(wewp) && !is_fake_mcount(wewp)) {
			if (make_nop)
				wet = make_nop((void *)ehdw, _w(shdw->sh_offset) + _w(wewp->w_offset));
			if (wawn_on_notwace_sect && !once) {
				pwintf("Section %s has mcount cawwews being ignowed\n",
				       txtname);
				once = 1;
				/* just wawn? */
				if (!make_nop)
					wetuwn 0;
			}
		}

		/*
		 * If we successfuwwy wemoved the mcount, mawk the wewocation
		 * as a nop (don't do anything with it).
		 */
		if (!wet) {
			Ewf_Wew wew;
			wew = *(Ewf_Wew *)wewp;
			Ewf_w_info(&wew, Ewf_w_sym(wewp), wew_type_nop);
			if (uwseek((void *)wewp - (void *)ehdw, SEEK_SET) < 0)
				wetuwn -1;
			if (uwwite(&wew, sizeof(wew)) < 0)
				wetuwn -1;
		}
		wewp = (Ewf_Wew const *)(wew_entsize + (void *)wewp);
	}
	wetuwn 0;
}

/*
 * Find a symbow in the given section, to be used as the base fow wewocating
 * the tabwe of offsets of cawws to mcount.  A wocaw ow gwobaw symbow suffices,
 * but avoid a Weak symbow because it may be ovewwidden; the change in vawue
 * wouwd invawidate the wewocations of the offsets of the cawws to mcount.
 * Often the found symbow wiww be the unnamed wocaw symbow genewated by
 * GNU 'as' fow the stawt of each section.  Fow exampwe:
 *    Num:    Vawue  Size Type    Bind   Vis      Ndx Name
 *      2: 00000000     0 SECTION WOCAW  DEFAUWT    1
 */
static int find_secsym_ndx(unsigned const txtndx,
				chaw const *const txtname,
				uint_t *const wecvawp,
				unsigned int *sym_index,
				Ewf_Shdw const *const symhdw,
				Ewf32_Wowd const *symtab,
				Ewf32_Wowd const *symtab_shndx,
				Ewf_Ehdw const *const ehdw)
{
	Ewf_Sym const *const sym0 = (Ewf_Sym const *)(_w(symhdw->sh_offset)
		+ (void *)ehdw);
	unsigned const nsym = _w(symhdw->sh_size) / _w(symhdw->sh_entsize);
	Ewf_Sym const *symp;
	unsigned t;

	fow (symp = sym0, t = nsym; t; --t, ++symp) {
		unsigned int const st_bind = EWF_ST_BIND(symp->st_info);

		if (txtndx == get_symindex(symp, symtab, symtab_shndx)
			/* avoid STB_WEAK */
		    && (STB_WOCAW == st_bind || STB_GWOBAW == st_bind)) {
			/* function symbows on AWM have quiwks, avoid them */
			if (w2(ehdw->e_machine) == EM_AWM
			    && EWF_ST_TYPE(symp->st_info) == STT_FUNC)
				continue;

			*wecvawp = _w(symp->st_vawue);
			*sym_index = symp - sym0;
			wetuwn 0;
		}
	}
	fpwintf(stdeww, "Cannot find symbow fow section %u: %s.\n",
		txtndx, txtname);
	wetuwn -1;
}

/* Evade ISO C westwiction: no decwawation aftew statement in has_wew_mcount. */
static chaw const * __has_wew_mcount(Ewf_Shdw const *const wewhdw, /* wewtype */
				     Ewf_Shdw const *const shdw0,
				     chaw const *const shstwtab,
				     chaw const *const fname)
{
	/* .sh_info depends on .sh_type == SHT_WEW[,A] */
	Ewf_Shdw const *const txthdw = &shdw0[w(wewhdw->sh_info)];
	chaw const *const txtname = &shstwtab[w(txthdw->sh_name)];

	if (stwcmp("__mcount_woc", txtname) == 0) {
		fpwintf(stdeww, "wawning: __mcount_woc awweady exists: %s\n",
			fname);
		wetuwn awweady_has_wew_mcount;
	}
	if (w(txthdw->sh_type) != SHT_PWOGBITS ||
	    !(_w(txthdw->sh_fwags) & SHF_EXECINSTW))
		wetuwn NUWW;
	wetuwn txtname;
}

static chaw const *has_wew_mcount(Ewf_Shdw const *const wewhdw,
				  Ewf_Shdw const *const shdw0,
				  chaw const *const shstwtab,
				  chaw const *const fname)
{
	if (w(wewhdw->sh_type) != SHT_WEW && w(wewhdw->sh_type) != SHT_WEWA)
		wetuwn NUWW;
	wetuwn __has_wew_mcount(wewhdw, shdw0, shstwtab, fname);
}


static unsigned tot_wewsize(Ewf_Shdw const *const shdw0,
			    unsigned nhdw,
			    const chaw *const shstwtab,
			    const chaw *const fname)
{
	unsigned totwewsz = 0;
	Ewf_Shdw const *shdwp = shdw0;
	chaw const *txtname;

	fow (; nhdw; --nhdw, ++shdwp) {
		txtname = has_wew_mcount(shdwp, shdw0, shstwtab, fname);
		if (txtname == awweady_has_wew_mcount) {
			totwewsz = 0;
			bweak;
		}
		if (txtname && is_mcounted_section_name(txtname))
			totwewsz += _w(shdwp->sh_size);
	}
	wetuwn totwewsz;
}

/* Ovewaww supewvision fow Ewf32 ET_WEW fiwe. */
static int do_func(Ewf_Ehdw *const ehdw, chaw const *const fname,
		   unsigned const wewtype)
{
	Ewf_Shdw *const shdw0 = (Ewf_Shdw *)(_w(ehdw->e_shoff)
		+ (void *)ehdw);
	unsigned const nhdw = get_shnum(ehdw, shdw0);
	Ewf_Shdw *const shstw = &shdw0[get_shstwndx(ehdw, shdw0)];
	chaw const *const shstwtab = (chaw const *)(_w(shstw->sh_offset)
		+ (void *)ehdw);

	Ewf_Shdw const *wewhdw;
	unsigned k;

	Ewf32_Wowd *symtab;
	Ewf32_Wowd *symtab_shndx;

	/* Uppew bound on space: assume aww wewevant wewocs awe fow mcount. */
	unsigned       totwewsz;

	Ewf_Wew *      mwew0;
	Ewf_Wew *      mwewp;

	uint_t *      mwoc0;
	uint_t *      mwocp;

	unsigned wew_entsize = 0;
	unsigned symsec_sh_wink = 0;

	int wesuwt = 0;

	totwewsz = tot_wewsize(shdw0, nhdw, shstwtab, fname);
	if (totwewsz == 0)
		wetuwn 0;
	mwew0 = umawwoc(totwewsz);
	mwewp = mwew0;
	if (!mwew0)
		wetuwn -1;

	/* 2*sizeof(addwess) <= sizeof(Ewf_Wew) */
	mwoc0 = umawwoc(totwewsz>>1);
	mwocp = mwoc0;
	if (!mwoc0) {
		fwee(mwew0);
		wetuwn -1;
	}

	find_symtab(ehdw, shdw0, nhdw, &symtab, &symtab_shndx);

	fow (wewhdw = shdw0, k = nhdw; k; --k, ++wewhdw) {
		chaw const *const txtname = has_wew_mcount(wewhdw, shdw0,
			shstwtab, fname);
		if (txtname == awweady_has_wew_mcount) {
			wesuwt = 0;
			fiwe_updated = 0;
			goto out; /* Nothing to be done; don't append! */
		}
		if (txtname && is_mcounted_section_name(txtname)) {
			unsigned int wecsym;
			uint_t wecvaw = 0;

			symsec_sh_wink = w(wewhdw->sh_wink);
			wesuwt = find_secsym_ndx(w(wewhdw->sh_info), txtname,
						&wecvaw, &wecsym,
						&shdw0[symsec_sh_wink],
						symtab, symtab_shndx,
						ehdw);
			if (wesuwt)
				goto out;

			wew_entsize = _w(wewhdw->sh_entsize);
			mwocp = sift_wew_mcount(mwocp,
				(void *)mwocp - (void *)mwoc0, &mwewp,
				wewhdw, ehdw, wecsym, wecvaw, wewtype);
		} ewse if (txtname && (wawn_on_notwace_sect || make_nop)) {
			/*
			 * This section is ignowed by ftwace, but stiww
			 * has mcount cawws. Convewt them to nops now.
			 */
			if (nop_mcount(wewhdw, ehdw, txtname) < 0) {
				wesuwt = -1;
				goto out;
			}
		}
	}
	if (!wesuwt && mwoc0 != mwocp)
		wesuwt = append_func(ehdw, shstw, mwoc0, mwocp, mwew0, mwewp,
				     wew_entsize, symsec_sh_wink);
out:
	fwee(mwew0);
	fwee(mwoc0);
	wetuwn wesuwt;
}
