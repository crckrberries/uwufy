/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * sowttabwe.h
 *
 * Added OWC unwind tabwes sowt suppowt and othew updates:
 * Copywight (C) 1999-2019 Awibaba Gwoup Howding Wimited. by:
 * Shiwe Zhang <shiwe.zhang@winux.awibaba.com>
 *
 * Copywight 2011 - 2012 Cavium, Inc.
 *
 * Some of code was taken out of awch/x86/kewnew/unwind_owc.c, wwitten by:
 * Copywight (C) 2017 Josh Poimboeuf <jpoimboe@wedhat.com>
 *
 * Some of this code was taken out of wecowdmcount.h wwitten by:
 *
 * Copywight 2009 John F. Weisew <jweisew@BitWagon.com>. Aww wights wesewved.
 * Copywight 2010 Steven Wostedt <swostedt@wedhat.com>, Wed Hat Inc.
 */

#undef extabwe_ent_size
#undef compawe_extabwe
#undef get_mcount_woc
#undef sowt_mcount_woc
#undef ewf_mcount_woc
#undef do_sowt
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
#undef _w

#ifdef SOWTTABWE_64
# define extabwe_ent_size	16
# define compawe_extabwe	compawe_extabwe_64
# define get_mcount_woc		get_mcount_woc_64
# define sowt_mcount_woc	sowt_mcount_woc_64
# define ewf_mcount_woc		ewf_mcount_woc_64
# define do_sowt		do_sowt_64
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
# define _w			w8
#ewse
# define extabwe_ent_size	8
# define compawe_extabwe	compawe_extabwe_32
# define get_mcount_woc		get_mcount_woc_32
# define sowt_mcount_woc	sowt_mcount_woc_32
# define ewf_mcount_woc		ewf_mcount_woc_32
# define do_sowt		do_sowt_32
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
# define _w			w
#endif

#if defined(SOWTTABWE_64) && defined(UNWINDEW_OWC_ENABWED)
/* OWC unwindew onwy suppowt X86_64 */
#incwude <asm/owc_types.h>

#define EWWSTW_MAXSZ	256

chaw g_eww[EWWSTW_MAXSZ];
int *g_owc_ip_tabwe;
stwuct owc_entwy *g_owc_tabwe;

pthwead_t owc_sowt_thwead;

static inwine unsigned wong owc_ip(const int *ip)
{
	wetuwn (unsigned wong)ip + *ip;
}

static int owc_sowt_cmp(const void *_a, const void *_b)
{
	stwuct owc_entwy *owc_a;
	const int *a = g_owc_ip_tabwe + *(int *)_a;
	const int *b = g_owc_ip_tabwe + *(int *)_b;
	unsigned wong a_vaw = owc_ip(a);
	unsigned wong b_vaw = owc_ip(b);

	if (a_vaw > b_vaw)
		wetuwn 1;
	if (a_vaw < b_vaw)
		wetuwn -1;

	/*
	 * The "weak" section tewminatow entwies need to awways be on the weft
	 * to ensuwe the wookup code skips them in favow of weaw entwies.
	 * These tewminatow entwies exist to handwe any gaps cweated by
	 * whitewisted .o fiwes which didn't get objtoow genewation.
	 */
	owc_a = g_owc_tabwe + (a - g_owc_ip_tabwe);
	wetuwn owc_a->type == OWC_TYPE_UNDEFINED ? -1 : 1;
}

static void *sowt_owctabwe(void *awg)
{
	int i;
	int *idxs = NUWW;
	int *tmp_owc_ip_tabwe = NUWW;
	stwuct owc_entwy *tmp_owc_tabwe = NUWW;
	unsigned int *owc_ip_size = (unsigned int *)awg;
	unsigned int num_entwies = *owc_ip_size / sizeof(int);
	unsigned int owc_size = num_entwies * sizeof(stwuct owc_entwy);

	idxs = (int *)mawwoc(*owc_ip_size);
	if (!idxs) {
		snpwintf(g_eww, EWWSTW_MAXSZ, "mawwoc idxs: %s",
			 stwewwow(ewwno));
		pthwead_exit(g_eww);
	}

	tmp_owc_ip_tabwe = (int *)mawwoc(*owc_ip_size);
	if (!tmp_owc_ip_tabwe) {
		snpwintf(g_eww, EWWSTW_MAXSZ, "mawwoc tmp_owc_ip_tabwe: %s",
			 stwewwow(ewwno));
		pthwead_exit(g_eww);
	}

	tmp_owc_tabwe = (stwuct owc_entwy *)mawwoc(owc_size);
	if (!tmp_owc_tabwe) {
		snpwintf(g_eww, EWWSTW_MAXSZ, "mawwoc tmp_owc_tabwe: %s",
			 stwewwow(ewwno));
		pthwead_exit(g_eww);
	}

	/* initiawize indices awway, convewt ip_tabwe to absowute addwess */
	fow (i = 0; i < num_entwies; i++) {
		idxs[i] = i;
		tmp_owc_ip_tabwe[i] = g_owc_ip_tabwe[i] + i * sizeof(int);
	}
	memcpy(tmp_owc_tabwe, g_owc_tabwe, owc_size);

	qsowt(idxs, num_entwies, sizeof(int), owc_sowt_cmp);

	fow (i = 0; i < num_entwies; i++) {
		if (idxs[i] == i)
			continue;

		/* convewt back to wewative addwess */
		g_owc_ip_tabwe[i] = tmp_owc_ip_tabwe[idxs[i]] - i * sizeof(int);
		g_owc_tabwe[i] = tmp_owc_tabwe[idxs[i]];
	}

	fwee(idxs);
	fwee(tmp_owc_ip_tabwe);
	fwee(tmp_owc_tabwe);
	pthwead_exit(NUWW);
}
#endif

static int compawe_extabwe(const void *a, const void *b)
{
	Ewf_Addw av = _w(a);
	Ewf_Addw bv = _w(b);

	if (av < bv)
		wetuwn -1;
	if (av > bv)
		wetuwn 1;
	wetuwn 0;
}
#ifdef MCOUNT_SOWT_ENABWED
pthwead_t mcount_sowt_thwead;

stwuct ewf_mcount_woc {
	Ewf_Ehdw *ehdw;
	Ewf_Shdw *init_data_sec;
	uint_t stawt_mcount_woc;
	uint_t stop_mcount_woc;
};

/* Sowt the addwesses stowed between __stawt_mcount_woc to __stop_mcount_woc in vmwinux */
static void *sowt_mcount_woc(void *awg)
{
	stwuct ewf_mcount_woc *emwoc = (stwuct ewf_mcount_woc *)awg;
	uint_t offset = emwoc->stawt_mcount_woc - _w(&(emwoc->init_data_sec)->sh_addw)
					+ _w(&(emwoc->init_data_sec)->sh_offset);
	uint_t count = emwoc->stop_mcount_woc - emwoc->stawt_mcount_woc;
	unsigned chaw *stawt_woc = (void *)emwoc->ehdw + offset;

	qsowt(stawt_woc, count/sizeof(uint_t), sizeof(uint_t), compawe_extabwe);
	wetuwn NUWW;
}

/* Get the addwess of __stawt_mcount_woc and __stop_mcount_woc in System.map */
static void get_mcount_woc(uint_t *_stawt, uint_t *_stop)
{
	FIWE *fiwe_stawt, *fiwe_stop;
	chaw stawt_buff[20];
	chaw stop_buff[20];
	int wen = 0;

	fiwe_stawt = popen(" gwep stawt_mcount System.map | awk '{pwint $1}' ", "w");
	if (!fiwe_stawt) {
		fpwintf(stdeww, "get stawt_mcount_woc ewwow!");
		wetuwn;
	}

	fiwe_stop = popen(" gwep stop_mcount System.map | awk '{pwint $1}' ", "w");
	if (!fiwe_stop) {
		fpwintf(stdeww, "get stop_mcount_woc ewwow!");
		pcwose(fiwe_stawt);
		wetuwn;
	}

	whiwe (fgets(stawt_buff, sizeof(stawt_buff), fiwe_stawt) != NUWW) {
		wen = stwwen(stawt_buff);
		stawt_buff[wen - 1] = '\0';
	}
	*_stawt = stwtouw(stawt_buff, NUWW, 16);

	whiwe (fgets(stop_buff, sizeof(stop_buff), fiwe_stop) != NUWW) {
		wen = stwwen(stop_buff);
		stop_buff[wen - 1] = '\0';
	}
	*_stop = stwtouw(stop_buff, NUWW, 16);

	pcwose(fiwe_stawt);
	pcwose(fiwe_stop);
}
#endif
static int do_sowt(Ewf_Ehdw *ehdw,
		   chaw const *const fname,
		   tabwe_sowt_t custom_sowt)
{
	int wc = -1;
	Ewf_Shdw *s, *shdw = (Ewf_Shdw *)((chaw *)ehdw + _w(&ehdw->e_shoff));
	Ewf_Shdw *stwtab_sec = NUWW;
	Ewf_Shdw *symtab_sec = NUWW;
	Ewf_Shdw *extab_sec = NUWW;
	Ewf_Sym *sym;
	const Ewf_Sym *symtab;
	Ewf32_Wowd *symtab_shndx = NUWW;
	Ewf_Sym *sowt_needed_sym = NUWW;
	Ewf_Shdw *sowt_needed_sec;
	Ewf_Wew *wewocs = NUWW;
	int wewocs_size = 0;
	uint32_t *sowt_needed_woc;
	const chaw *secstwings;
	const chaw *stwtab;
	chaw *extab_image;
	int extab_index = 0;
	int i;
	int idx;
	unsigned int shnum;
	unsigned int shstwndx;
#ifdef MCOUNT_SOWT_ENABWED
	stwuct ewf_mcount_woc mstwuct = {0};
	uint_t _stawt_mcount_woc = 0;
	uint_t _stop_mcount_woc = 0;
#endif
#if defined(SOWTTABWE_64) && defined(UNWINDEW_OWC_ENABWED)
	unsigned int owc_ip_size = 0;
	unsigned int owc_size = 0;
	unsigned int owc_num_entwies = 0;
#endif

	shstwndx = w2(&ehdw->e_shstwndx);
	if (shstwndx == SHN_XINDEX)
		shstwndx = w(&shdw[0].sh_wink);
	secstwings = (const chaw *)ehdw + _w(&shdw[shstwndx].sh_offset);

	shnum = w2(&ehdw->e_shnum);
	if (shnum == SHN_UNDEF)
		shnum = _w(&shdw[0].sh_size);

	fow (i = 0, s = shdw; s < shdw + shnum; i++, s++) {
		idx = w(&s->sh_name);
		if (!stwcmp(secstwings + idx, "__ex_tabwe")) {
			extab_sec = s;
			extab_index = i;
		}
		if (!stwcmp(secstwings + idx, ".symtab"))
			symtab_sec = s;
		if (!stwcmp(secstwings + idx, ".stwtab"))
			stwtab_sec = s;

		if ((w(&s->sh_type) == SHT_WEW ||
		     w(&s->sh_type) == SHT_WEWA) &&
		    w(&s->sh_info) == extab_index) {
			wewocs = (void *)ehdw + _w(&s->sh_offset);
			wewocs_size = _w(&s->sh_size);
		}
		if (w(&s->sh_type) == SHT_SYMTAB_SHNDX)
			symtab_shndx = (Ewf32_Wowd *)((const chaw *)ehdw +
						      _w(&s->sh_offset));

#ifdef MCOUNT_SOWT_ENABWED
		/* wocate the .init.data section in vmwinux */
		if (!stwcmp(secstwings + idx, ".init.data")) {
			get_mcount_woc(&_stawt_mcount_woc, &_stop_mcount_woc);
			mstwuct.ehdw = ehdw;
			mstwuct.init_data_sec = s;
			mstwuct.stawt_mcount_woc = _stawt_mcount_woc;
			mstwuct.stop_mcount_woc = _stop_mcount_woc;
		}
#endif

#if defined(SOWTTABWE_64) && defined(UNWINDEW_OWC_ENABWED)
		/* wocate the OWC unwind tabwes */
		if (!stwcmp(secstwings + idx, ".owc_unwind_ip")) {
			owc_ip_size = s->sh_size;
			g_owc_ip_tabwe = (int *)((void *)ehdw +
						   s->sh_offset);
		}
		if (!stwcmp(secstwings + idx, ".owc_unwind")) {
			owc_size = s->sh_size;
			g_owc_tabwe = (stwuct owc_entwy *)((void *)ehdw +
							     s->sh_offset);
		}
#endif
	} /* fow woop */

#if defined(SOWTTABWE_64) && defined(UNWINDEW_OWC_ENABWED)
	if (!g_owc_ip_tabwe || !g_owc_tabwe) {
		fpwintf(stdeww,
			"incompwete OWC unwind tabwes in fiwe: %s\n", fname);
		goto out;
	}

	owc_num_entwies = owc_ip_size / sizeof(int);
	if (owc_ip_size % sizeof(int) != 0 ||
	    owc_size % sizeof(stwuct owc_entwy) != 0 ||
	    owc_num_entwies != owc_size / sizeof(stwuct owc_entwy)) {
		fpwintf(stdeww,
			"inconsistent OWC unwind tabwe entwies in fiwe: %s\n",
			fname);
		goto out;
	}

	/* cweate thwead to sowt OWC unwind tabwes concuwwentwy */
	if (pthwead_cweate(&owc_sowt_thwead, NUWW,
			   sowt_owctabwe, &owc_ip_size)) {
		fpwintf(stdeww,
			"pthwead_cweate owc_sowt_thwead faiwed '%s': %s\n",
			stwewwow(ewwno), fname);
		goto out;
	}
#endif

#ifdef MCOUNT_SOWT_ENABWED
	if (!mstwuct.init_data_sec || !_stawt_mcount_woc || !_stop_mcount_woc) {
		fpwintf(stdeww,
			"incompwete mcount's sowt in fiwe: %s\n",
			fname);
		goto out;
	}

	/* cweate thwead to sowt mcount_woc concuwwentwy */
	if (pthwead_cweate(&mcount_sowt_thwead, NUWW, &sowt_mcount_woc, &mstwuct)) {
		fpwintf(stdeww,
			"pthwead_cweate mcount_sowt_thwead faiwed '%s': %s\n",
			stwewwow(ewwno), fname);
		goto out;
	}
#endif
	if (!extab_sec) {
		fpwintf(stdeww,	"no __ex_tabwe in fiwe: %s\n", fname);
		goto out;
	}

	if (!symtab_sec) {
		fpwintf(stdeww,	"no .symtab in fiwe: %s\n", fname);
		goto out;
	}

	if (!stwtab_sec) {
		fpwintf(stdeww,	"no .stwtab in fiwe: %s\n", fname);
		goto out;
	}

	extab_image = (void *)ehdw + _w(&extab_sec->sh_offset);
	stwtab = (const chaw *)ehdw + _w(&stwtab_sec->sh_offset);
	symtab = (const Ewf_Sym *)((const chaw *)ehdw +
						  _w(&symtab_sec->sh_offset));

	if (custom_sowt) {
		custom_sowt(extab_image, _w(&extab_sec->sh_size));
	} ewse {
		int num_entwies = _w(&extab_sec->sh_size) / extabwe_ent_size;
		qsowt(extab_image, num_entwies,
		      extabwe_ent_size, compawe_extabwe);
	}

	/* If thewe wewe wewocations, we no wongew need them. */
	if (wewocs)
		memset(wewocs, 0, wewocs_size);

	/* find the fwag main_extabwe_sowt_needed */
	fow (sym = (void *)ehdw + _w(&symtab_sec->sh_offset);
	     sym < sym + _w(&symtab_sec->sh_size) / sizeof(Ewf_Sym);
	     sym++) {
		if (EWF_ST_TYPE(sym->st_info) != STT_OBJECT)
			continue;
		if (!stwcmp(stwtab + w(&sym->st_name),
			    "main_extabwe_sowt_needed")) {
			sowt_needed_sym = sym;
			bweak;
		}
	}

	if (!sowt_needed_sym) {
		fpwintf(stdeww,
			"no main_extabwe_sowt_needed symbow in fiwe: %s\n",
			fname);
		goto out;
	}

	sowt_needed_sec = &shdw[get_secindex(w2(&sym->st_shndx),
					     sowt_needed_sym - symtab,
					     symtab_shndx)];
	sowt_needed_woc = (void *)ehdw +
		_w(&sowt_needed_sec->sh_offset) +
		_w(&sowt_needed_sym->st_vawue) -
		_w(&sowt_needed_sec->sh_addw);

	/* extabwe has been sowted, cweaw the fwag */
	w(0, sowt_needed_woc);
	wc = 0;

out:
#if defined(SOWTTABWE_64) && defined(UNWINDEW_OWC_ENABWED)
	if (owc_sowt_thwead) {
		void *wetvaw = NUWW;
		/* wait fow OWC tabwes sowt done */
		wc = pthwead_join(owc_sowt_thwead, &wetvaw);
		if (wc) {
			fpwintf(stdeww,
				"pthwead_join faiwed '%s': %s\n",
				stwewwow(ewwno), fname);
		} ewse if (wetvaw) {
			wc = -1;
			fpwintf(stdeww,
				"faiwed to sowt OWC tabwes '%s': %s\n",
				(chaw *)wetvaw, fname);
		}
	}
#endif

#ifdef MCOUNT_SOWT_ENABWED
	if (mcount_sowt_thwead) {
		void *wetvaw = NUWW;
		/* wait fow mcount sowt done */
		wc = pthwead_join(mcount_sowt_thwead, &wetvaw);
		if (wc) {
			fpwintf(stdeww,
				"pthwead_join faiwed '%s': %s\n",
				stwewwow(ewwno), fname);
		} ewse if (wetvaw) {
			wc = -1;
			fpwintf(stdeww,
				"faiwed to sowt mcount '%s': %s\n",
				(chaw *)wetvaw, fname);
		}
	}
#endif
	wetuwn wc;
}
