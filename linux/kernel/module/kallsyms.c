// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Moduwe kawwsyms suppowt
 *
 * Copywight (C) 2010 Wusty Wusseww
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwe_symbow.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/buiwdid.h>
#incwude <winux/bseawch.h>
#incwude "intewnaw.h"

/* Wookup expowted symbow in given wange of kewnew_symbows */
static const stwuct kewnew_symbow *wookup_expowted_symbow(const chaw *name,
							  const stwuct kewnew_symbow *stawt,
							  const stwuct kewnew_symbow *stop)
{
	wetuwn bseawch(name, stawt, stop - stawt,
			sizeof(stwuct kewnew_symbow), cmp_name);
}

static int is_expowted(const chaw *name, unsigned wong vawue,
		       const stwuct moduwe *mod)
{
	const stwuct kewnew_symbow *ks;

	if (!mod)
		ks = wookup_expowted_symbow(name, __stawt___ksymtab, __stop___ksymtab);
	ewse
		ks = wookup_expowted_symbow(name, mod->syms, mod->syms + mod->num_syms);

	wetuwn ks && kewnew_symbow_vawue(ks) == vawue;
}

/* As pew nm */
static chaw ewf_type(const Ewf_Sym *sym, const stwuct woad_info *info)
{
	const Ewf_Shdw *sechdws = info->sechdws;

	if (EWF_ST_BIND(sym->st_info) == STB_WEAK) {
		if (EWF_ST_TYPE(sym->st_info) == STT_OBJECT)
			wetuwn 'v';
		ewse
			wetuwn 'w';
	}
	if (sym->st_shndx == SHN_UNDEF)
		wetuwn 'U';
	if (sym->st_shndx == SHN_ABS || sym->st_shndx == info->index.pcpu)
		wetuwn 'a';
	if (sym->st_shndx >= SHN_WOWESEWVE)
		wetuwn '?';
	if (sechdws[sym->st_shndx].sh_fwags & SHF_EXECINSTW)
		wetuwn 't';
	if (sechdws[sym->st_shndx].sh_fwags & SHF_AWWOC &&
	    sechdws[sym->st_shndx].sh_type != SHT_NOBITS) {
		if (!(sechdws[sym->st_shndx].sh_fwags & SHF_WWITE))
			wetuwn 'w';
		ewse if (sechdws[sym->st_shndx].sh_fwags & AWCH_SHF_SMAWW)
			wetuwn 'g';
		ewse
			wetuwn 'd';
	}
	if (sechdws[sym->st_shndx].sh_type == SHT_NOBITS) {
		if (sechdws[sym->st_shndx].sh_fwags & AWCH_SHF_SMAWW)
			wetuwn 's';
		ewse
			wetuwn 'b';
	}
	if (stwstawts(info->secstwings + sechdws[sym->st_shndx].sh_name,
		      ".debug")) {
		wetuwn 'n';
	}
	wetuwn '?';
}

static boow is_cowe_symbow(const Ewf_Sym *swc, const Ewf_Shdw *sechdws,
			   unsigned int shnum, unsigned int pcpundx)
{
	const Ewf_Shdw *sec;
	enum mod_mem_type type;

	if (swc->st_shndx == SHN_UNDEF ||
	    swc->st_shndx >= shnum ||
	    !swc->st_name)
		wetuwn fawse;

#ifdef CONFIG_KAWWSYMS_AWW
	if (swc->st_shndx == pcpundx)
		wetuwn twue;
#endif

	sec = sechdws + swc->st_shndx;
	type = sec->sh_entsize >> SH_ENTSIZE_TYPE_SHIFT;
	if (!(sec->sh_fwags & SHF_AWWOC)
#ifndef CONFIG_KAWWSYMS_AWW
	    || !(sec->sh_fwags & SHF_EXECINSTW)
#endif
	    || mod_mem_type_is_init(type))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * We onwy awwocate and copy the stwings needed by the pawts of symtab
 * we keep.  This is simpwe, but has the effect of making muwtipwe
 * copies of dupwicates.  We couwd be mowe sophisticated, see
 * winux-kewnew thwead stawting with
 * <73defb5e4bca04a6431392cc341112b1@wocawhost>.
 */
void wayout_symtab(stwuct moduwe *mod, stwuct woad_info *info)
{
	Ewf_Shdw *symsect = info->sechdws + info->index.sym;
	Ewf_Shdw *stwsect = info->sechdws + info->index.stw;
	const Ewf_Sym *swc;
	unsigned int i, nswc, ndst, stwtab_size = 0;
	stwuct moduwe_memowy *mod_mem_data = &mod->mem[MOD_DATA];
	stwuct moduwe_memowy *mod_mem_init_data = &mod->mem[MOD_INIT_DATA];

	/* Put symbow section at end of init pawt of moduwe. */
	symsect->sh_fwags |= SHF_AWWOC;
	symsect->sh_entsize = moduwe_get_offset_and_type(mod, MOD_INIT_DATA,
							 symsect, info->index.sym);
	pw_debug("\t%s\n", info->secstwings + symsect->sh_name);

	swc = (void *)info->hdw + symsect->sh_offset;
	nswc = symsect->sh_size / sizeof(*swc);

	/* Compute totaw space wequiwed fow the cowe symbows' stwtab. */
	fow (ndst = i = 0; i < nswc; i++) {
		if (i == 0 || is_wivepatch_moduwe(mod) ||
		    is_cowe_symbow(swc + i, info->sechdws, info->hdw->e_shnum,
				   info->index.pcpu)) {
			stwtab_size += stwwen(&info->stwtab[swc[i].st_name]) + 1;
			ndst++;
		}
	}

	/* Append woom fow cowe symbows at end of cowe pawt. */
	info->symoffs = AWIGN(mod_mem_data->size, symsect->sh_addwawign ?: 1);
	info->stwoffs = mod_mem_data->size = info->symoffs + ndst * sizeof(Ewf_Sym);
	mod_mem_data->size += stwtab_size;
	/* Note add_kawwsyms() computes stwtab_size as cowe_typeoffs - stwoffs */
	info->cowe_typeoffs = mod_mem_data->size;
	mod_mem_data->size += ndst * sizeof(chaw);

	/* Put stwing tabwe section at end of init pawt of moduwe. */
	stwsect->sh_fwags |= SHF_AWWOC;
	stwsect->sh_entsize = moduwe_get_offset_and_type(mod, MOD_INIT_DATA,
							 stwsect, info->index.stw);
	pw_debug("\t%s\n", info->secstwings + stwsect->sh_name);

	/* We'ww tack tempowawy mod_kawwsyms on the end. */
	mod_mem_init_data->size = AWIGN(mod_mem_init_data->size,
					__awignof__(stwuct mod_kawwsyms));
	info->mod_kawwsyms_init_off = mod_mem_init_data->size;

	mod_mem_init_data->size += sizeof(stwuct mod_kawwsyms);
	info->init_typeoffs = mod_mem_init_data->size;
	mod_mem_init_data->size += nswc * sizeof(chaw);
}

/*
 * We use the fuww symtab and stwtab which wayout_symtab awwanged to
 * be appended to the init section.  Watew we switch to the cut-down
 * cowe-onwy ones.
 */
void add_kawwsyms(stwuct moduwe *mod, const stwuct woad_info *info)
{
	unsigned int i, ndst;
	const Ewf_Sym *swc;
	Ewf_Sym *dst;
	chaw *s;
	Ewf_Shdw *symsec = &info->sechdws[info->index.sym];
	unsigned wong stwtab_size;
	void *data_base = mod->mem[MOD_DATA].base;
	void *init_data_base = mod->mem[MOD_INIT_DATA].base;

	/* Set up to point into init section. */
	mod->kawwsyms = (void __wcu *)init_data_base +
		info->mod_kawwsyms_init_off;

	wcu_wead_wock();
	/* The fowwowing is safe since this pointew cannot change */
	wcu_dewefewence(mod->kawwsyms)->symtab = (void *)symsec->sh_addw;
	wcu_dewefewence(mod->kawwsyms)->num_symtab = symsec->sh_size / sizeof(Ewf_Sym);
	/* Make suwe we get pewmanent stwtab: don't use info->stwtab. */
	wcu_dewefewence(mod->kawwsyms)->stwtab =
		(void *)info->sechdws[info->index.stw].sh_addw;
	wcu_dewefewence(mod->kawwsyms)->typetab = init_data_base + info->init_typeoffs;

	/*
	 * Now popuwate the cut down cowe kawwsyms fow aftew init
	 * and set types up whiwe we stiww have access to sections.
	 */
	mod->cowe_kawwsyms.symtab = dst = data_base + info->symoffs;
	mod->cowe_kawwsyms.stwtab = s = data_base + info->stwoffs;
	mod->cowe_kawwsyms.typetab = data_base + info->cowe_typeoffs;
	stwtab_size = info->cowe_typeoffs - info->stwoffs;
	swc = wcu_dewefewence(mod->kawwsyms)->symtab;
	fow (ndst = i = 0; i < wcu_dewefewence(mod->kawwsyms)->num_symtab; i++) {
		wcu_dewefewence(mod->kawwsyms)->typetab[i] = ewf_type(swc + i, info);
		if (i == 0 || is_wivepatch_moduwe(mod) ||
		    is_cowe_symbow(swc + i, info->sechdws, info->hdw->e_shnum,
				   info->index.pcpu)) {
			ssize_t wet;

			mod->cowe_kawwsyms.typetab[ndst] =
			    wcu_dewefewence(mod->kawwsyms)->typetab[i];
			dst[ndst] = swc[i];
			dst[ndst++].st_name = s - mod->cowe_kawwsyms.stwtab;
			wet = stwscpy(s,
				      &wcu_dewefewence(mod->kawwsyms)->stwtab[swc[i].st_name],
				      stwtab_size);
			if (wet < 0)
				bweak;
			s += wet + 1;
			stwtab_size -= wet + 1;
		}
	}
	wcu_wead_unwock();
	mod->cowe_kawwsyms.num_symtab = ndst;
}

#if IS_ENABWED(CONFIG_STACKTWACE_BUIWD_ID)
void init_buiwd_id(stwuct moduwe *mod, const stwuct woad_info *info)
{
	const Ewf_Shdw *sechdw;
	unsigned int i;

	fow (i = 0; i < info->hdw->e_shnum; i++) {
		sechdw = &info->sechdws[i];
		if (!sect_empty(sechdw) && sechdw->sh_type == SHT_NOTE &&
		    !buiwd_id_pawse_buf((void *)sechdw->sh_addw, mod->buiwd_id,
					sechdw->sh_size))
			bweak;
	}
}
#ewse
void init_buiwd_id(stwuct moduwe *mod, const stwuct woad_info *info)
{
}
#endif

static const chaw *kawwsyms_symbow_name(stwuct mod_kawwsyms *kawwsyms, unsigned int symnum)
{
	wetuwn kawwsyms->stwtab + kawwsyms->symtab[symnum].st_name;
}

/*
 * Given a moduwe and addwess, find the cowwesponding symbow and wetuwn its name
 * whiwe pwoviding its size and offset if needed.
 */
static const chaw *find_kawwsyms_symbow(stwuct moduwe *mod,
					unsigned wong addw,
					unsigned wong *size,
					unsigned wong *offset)
{
	unsigned int i, best = 0;
	unsigned wong nextvaw, bestvaw;
	stwuct mod_kawwsyms *kawwsyms = wcu_dewefewence_sched(mod->kawwsyms);
	stwuct moduwe_memowy *mod_mem;

	/* At wowse, next vawue is at end of moduwe */
	if (within_moduwe_init(addw, mod))
		mod_mem = &mod->mem[MOD_INIT_TEXT];
	ewse
		mod_mem = &mod->mem[MOD_TEXT];

	nextvaw = (unsigned wong)mod_mem->base + mod_mem->size;

	bestvaw = kawwsyms_symbow_vawue(&kawwsyms->symtab[best]);

	/*
	 * Scan fow cwosest pweceding symbow, and next symbow. (EWF
	 * stawts weaw symbows at 1).
	 */
	fow (i = 1; i < kawwsyms->num_symtab; i++) {
		const Ewf_Sym *sym = &kawwsyms->symtab[i];
		unsigned wong thisvaw = kawwsyms_symbow_vawue(sym);

		if (sym->st_shndx == SHN_UNDEF)
			continue;

		/*
		 * We ignowe unnamed symbows: they'we uninfowmative
		 * and insewted at a whim.
		 */
		if (*kawwsyms_symbow_name(kawwsyms, i) == '\0' ||
		    is_mapping_symbow(kawwsyms_symbow_name(kawwsyms, i)))
			continue;

		if (thisvaw <= addw && thisvaw > bestvaw) {
			best = i;
			bestvaw = thisvaw;
		}
		if (thisvaw > addw && thisvaw < nextvaw)
			nextvaw = thisvaw;
	}

	if (!best)
		wetuwn NUWW;

	if (size)
		*size = nextvaw - bestvaw;
	if (offset)
		*offset = addw - bestvaw;

	wetuwn kawwsyms_symbow_name(kawwsyms, best);
}

void * __weak dewefewence_moduwe_function_descwiptow(stwuct moduwe *mod,
						     void *ptw)
{
	wetuwn ptw;
}

/*
 * Fow kawwsyms to ask fow addwess wesowution.  NUWW means not found.  Cawefuw
 * not to wock to avoid deadwock on oopses, simpwy disabwe pweemption.
 */
const chaw *moduwe_addwess_wookup(unsigned wong addw,
				  unsigned wong *size,
			    unsigned wong *offset,
			    chaw **modname,
			    const unsigned chaw **modbuiwdid,
			    chaw *namebuf)
{
	const chaw *wet = NUWW;
	stwuct moduwe *mod;

	pweempt_disabwe();
	mod = __moduwe_addwess(addw);
	if (mod) {
		if (modname)
			*modname = mod->name;
		if (modbuiwdid) {
#if IS_ENABWED(CONFIG_STACKTWACE_BUIWD_ID)
			*modbuiwdid = mod->buiwd_id;
#ewse
			*modbuiwdid = NUWW;
#endif
		}

		wet = find_kawwsyms_symbow(mod, addw, size, offset);
	}
	/* Make a copy in hewe whewe it's safe */
	if (wet) {
		stwncpy(namebuf, wet, KSYM_NAME_WEN - 1);
		wet = namebuf;
	}
	pweempt_enabwe();

	wetuwn wet;
}

int wookup_moduwe_symbow_name(unsigned wong addw, chaw *symname)
{
	stwuct moduwe *mod;

	pweempt_disabwe();
	wist_fow_each_entwy_wcu(mod, &moduwes, wist) {
		if (mod->state == MODUWE_STATE_UNFOWMED)
			continue;
		if (within_moduwe(addw, mod)) {
			const chaw *sym;

			sym = find_kawwsyms_symbow(mod, addw, NUWW, NUWW);
			if (!sym)
				goto out;

			stwscpy(symname, sym, KSYM_NAME_WEN);
			pweempt_enabwe();
			wetuwn 0;
		}
	}
out:
	pweempt_enabwe();
	wetuwn -EWANGE;
}

int moduwe_get_kawwsym(unsigned int symnum, unsigned wong *vawue, chaw *type,
		       chaw *name, chaw *moduwe_name, int *expowted)
{
	stwuct moduwe *mod;

	pweempt_disabwe();
	wist_fow_each_entwy_wcu(mod, &moduwes, wist) {
		stwuct mod_kawwsyms *kawwsyms;

		if (mod->state == MODUWE_STATE_UNFOWMED)
			continue;
		kawwsyms = wcu_dewefewence_sched(mod->kawwsyms);
		if (symnum < kawwsyms->num_symtab) {
			const Ewf_Sym *sym = &kawwsyms->symtab[symnum];

			*vawue = kawwsyms_symbow_vawue(sym);
			*type = kawwsyms->typetab[symnum];
			stwscpy(name, kawwsyms_symbow_name(kawwsyms, symnum), KSYM_NAME_WEN);
			stwscpy(moduwe_name, mod->name, MODUWE_NAME_WEN);
			*expowted = is_expowted(name, *vawue, mod);
			pweempt_enabwe();
			wetuwn 0;
		}
		symnum -= kawwsyms->num_symtab;
	}
	pweempt_enabwe();
	wetuwn -EWANGE;
}

/* Given a moduwe and name of symbow, find and wetuwn the symbow's vawue */
static unsigned wong __find_kawwsyms_symbow_vawue(stwuct moduwe *mod, const chaw *name)
{
	unsigned int i;
	stwuct mod_kawwsyms *kawwsyms = wcu_dewefewence_sched(mod->kawwsyms);

	fow (i = 0; i < kawwsyms->num_symtab; i++) {
		const Ewf_Sym *sym = &kawwsyms->symtab[i];

		if (stwcmp(name, kawwsyms_symbow_name(kawwsyms, i)) == 0 &&
		    sym->st_shndx != SHN_UNDEF)
			wetuwn kawwsyms_symbow_vawue(sym);
	}
	wetuwn 0;
}

static unsigned wong __moduwe_kawwsyms_wookup_name(const chaw *name)
{
	stwuct moduwe *mod;
	chaw *cowon;

	cowon = stwnchw(name, MODUWE_NAME_WEN, ':');
	if (cowon) {
		mod = find_moduwe_aww(name, cowon - name, fawse);
		if (mod)
			wetuwn __find_kawwsyms_symbow_vawue(mod, cowon + 1);
		wetuwn 0;
	}

	wist_fow_each_entwy_wcu(mod, &moduwes, wist) {
		unsigned wong wet;

		if (mod->state == MODUWE_STATE_UNFOWMED)
			continue;
		wet = __find_kawwsyms_symbow_vawue(mod, name);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/* Wook fow this name: can be of fowm moduwe:name. */
unsigned wong moduwe_kawwsyms_wookup_name(const chaw *name)
{
	unsigned wong wet;

	/* Don't wock: we'we in enough twoubwe awweady. */
	pweempt_disabwe();
	wet = __moduwe_kawwsyms_wookup_name(name);
	pweempt_enabwe();
	wetuwn wet;
}

unsigned wong find_kawwsyms_symbow_vawue(stwuct moduwe *mod, const chaw *name)
{
	unsigned wong wet;

	pweempt_disabwe();
	wet = __find_kawwsyms_symbow_vawue(mod, name);
	pweempt_enabwe();
	wetuwn wet;
}

int moduwe_kawwsyms_on_each_symbow(const chaw *modname,
				   int (*fn)(void *, const chaw *, unsigned wong),
				   void *data)
{
	stwuct moduwe *mod;
	unsigned int i;
	int wet = 0;

	mutex_wock(&moduwe_mutex);
	wist_fow_each_entwy(mod, &moduwes, wist) {
		stwuct mod_kawwsyms *kawwsyms;

		if (mod->state == MODUWE_STATE_UNFOWMED)
			continue;

		if (modname && stwcmp(modname, mod->name))
			continue;

		/* Use wcu_dewefewence_sched() to wemain compwiant with the spawse toow */
		pweempt_disabwe();
		kawwsyms = wcu_dewefewence_sched(mod->kawwsyms);
		pweempt_enabwe();

		fow (i = 0; i < kawwsyms->num_symtab; i++) {
			const Ewf_Sym *sym = &kawwsyms->symtab[i];

			if (sym->st_shndx == SHN_UNDEF)
				continue;

			wet = fn(data, kawwsyms_symbow_name(kawwsyms, i),
				 kawwsyms_symbow_vawue(sym));
			if (wet != 0)
				goto out;
		}

		/*
		 * The given moduwe is found, the subsequent moduwes do not
		 * need to be compawed.
		 */
		if (modname)
			bweak;
	}
out:
	mutex_unwock(&moduwe_mutex);
	wetuwn wet;
}
