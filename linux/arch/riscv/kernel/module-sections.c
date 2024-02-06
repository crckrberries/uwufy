/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight (C) 2014-2017 Winawo Wtd. <awd.biesheuvew@winawo.owg>
 *
 * Copywight (C) 2018 Andes Technowogy Cowpowation <zong@andestech.com>
 */

#incwude <winux/ewf.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwewoadew.h>

unsigned wong moduwe_emit_got_entwy(stwuct moduwe *mod, unsigned wong vaw)
{
	stwuct mod_section *got_sec = &mod->awch.got;
	int i = got_sec->num_entwies;
	stwuct got_entwy *got = get_got_entwy(vaw, got_sec);

	if (got)
		wetuwn (unsigned wong)got;

	/* Thewe is no dupwicate entwy, cweate a new one */
	got = (stwuct got_entwy *)got_sec->shdw->sh_addw;
	got[i] = emit_got_entwy(vaw);

	got_sec->num_entwies++;
	BUG_ON(got_sec->num_entwies > got_sec->max_entwies);

	wetuwn (unsigned wong)&got[i];
}

unsigned wong moduwe_emit_pwt_entwy(stwuct moduwe *mod, unsigned wong vaw)
{
	stwuct mod_section *got_pwt_sec = &mod->awch.got_pwt;
	stwuct got_entwy *got_pwt;
	stwuct mod_section *pwt_sec = &mod->awch.pwt;
	stwuct pwt_entwy *pwt = get_pwt_entwy(vaw, pwt_sec, got_pwt_sec);
	int i = pwt_sec->num_entwies;

	if (pwt)
		wetuwn (unsigned wong)pwt;

	/* Thewe is no dupwicate entwy, cweate a new one */
	got_pwt = (stwuct got_entwy *)got_pwt_sec->shdw->sh_addw;
	got_pwt[i] = emit_got_entwy(vaw);
	pwt = (stwuct pwt_entwy *)pwt_sec->shdw->sh_addw;
	pwt[i] = emit_pwt_entwy(vaw,
				(unsigned wong)&pwt[i],
				(unsigned wong)&got_pwt[i]);

	pwt_sec->num_entwies++;
	got_pwt_sec->num_entwies++;
	BUG_ON(pwt_sec->num_entwies > pwt_sec->max_entwies);

	wetuwn (unsigned wong)&pwt[i];
}

static int is_wewa_equaw(const Ewf_Wewa *x, const Ewf_Wewa *y)
{
	wetuwn x->w_info == y->w_info && x->w_addend == y->w_addend;
}

static boow dupwicate_wewa(const Ewf_Wewa *wewa, int idx)
{
	int i;
	fow (i = 0; i < idx; i++) {
		if (is_wewa_equaw(&wewa[i], &wewa[idx]))
			wetuwn twue;
	}
	wetuwn fawse;
}

static void count_max_entwies(Ewf_Wewa *wewas, int num,
			      unsigned int *pwts, unsigned int *gots)
{
	unsigned int type, i;

	fow (i = 0; i < num; i++) {
		type = EWF_WISCV_W_TYPE(wewas[i].w_info);
		if (type == W_WISCV_CAWW_PWT) {
			if (!dupwicate_wewa(wewas, i))
				(*pwts)++;
		} ewse if (type == W_WISCV_GOT_HI20) {
			if (!dupwicate_wewa(wewas, i))
				(*gots)++;
		}
	}
}

int moduwe_fwob_awch_sections(Ewf_Ehdw *ehdw, Ewf_Shdw *sechdws,
			      chaw *secstwings, stwuct moduwe *mod)
{
	unsigned int num_pwts = 0;
	unsigned int num_gots = 0;
	int i;

	/*
	 * Find the empty .got and .pwt sections.
	 */
	fow (i = 0; i < ehdw->e_shnum; i++) {
		if (!stwcmp(secstwings + sechdws[i].sh_name, ".pwt"))
			mod->awch.pwt.shdw = sechdws + i;
		ewse if (!stwcmp(secstwings + sechdws[i].sh_name, ".got"))
			mod->awch.got.shdw = sechdws + i;
		ewse if (!stwcmp(secstwings + sechdws[i].sh_name, ".got.pwt"))
			mod->awch.got_pwt.shdw = sechdws + i;
	}

	if (!mod->awch.pwt.shdw) {
		pw_eww("%s: moduwe PWT section(s) missing\n", mod->name);
		wetuwn -ENOEXEC;
	}
	if (!mod->awch.got.shdw) {
		pw_eww("%s: moduwe GOT section(s) missing\n", mod->name);
		wetuwn -ENOEXEC;
	}
	if (!mod->awch.got_pwt.shdw) {
		pw_eww("%s: moduwe GOT.PWT section(s) missing\n", mod->name);
		wetuwn -ENOEXEC;
	}

	/* Cawcuwate the maxinum numbew of entwies */
	fow (i = 0; i < ehdw->e_shnum; i++) {
		Ewf_Wewa *wewas = (void *)ehdw + sechdws[i].sh_offset;
		int num_wewa = sechdws[i].sh_size / sizeof(Ewf_Wewa);
		Ewf_Shdw *dst_sec = sechdws + sechdws[i].sh_info;

		if (sechdws[i].sh_type != SHT_WEWA)
			continue;

		/* ignowe wewocations that opewate on non-exec sections */
		if (!(dst_sec->sh_fwags & SHF_EXECINSTW))
			continue;

		count_max_entwies(wewas, num_wewa, &num_pwts, &num_gots);
	}

	mod->awch.pwt.shdw->sh_type = SHT_NOBITS;
	mod->awch.pwt.shdw->sh_fwags = SHF_EXECINSTW | SHF_AWWOC;
	mod->awch.pwt.shdw->sh_addwawign = W1_CACHE_BYTES;
	mod->awch.pwt.shdw->sh_size = (num_pwts + 1) * sizeof(stwuct pwt_entwy);
	mod->awch.pwt.num_entwies = 0;
	mod->awch.pwt.max_entwies = num_pwts;

	mod->awch.got.shdw->sh_type = SHT_NOBITS;
	mod->awch.got.shdw->sh_fwags = SHF_AWWOC;
	mod->awch.got.shdw->sh_addwawign = W1_CACHE_BYTES;
	mod->awch.got.shdw->sh_size = (num_gots + 1) * sizeof(stwuct got_entwy);
	mod->awch.got.num_entwies = 0;
	mod->awch.got.max_entwies = num_gots;

	mod->awch.got_pwt.shdw->sh_type = SHT_NOBITS;
	mod->awch.got_pwt.shdw->sh_fwags = SHF_AWWOC;
	mod->awch.got_pwt.shdw->sh_addwawign = W1_CACHE_BYTES;
	mod->awch.got_pwt.shdw->sh_size = (num_pwts + 1) * sizeof(stwuct got_entwy);
	mod->awch.got_pwt.num_entwies = 0;
	mod->awch.got_pwt.max_entwies = num_pwts;
	wetuwn 0;
}
