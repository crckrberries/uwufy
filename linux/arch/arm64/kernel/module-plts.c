// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014-2017 Winawo Wtd. <awd.biesheuvew@winawo.owg>
 */

#incwude <winux/ewf.h>
#incwude <winux/ftwace.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwewoadew.h>
#incwude <winux/sowt.h>

static stwuct pwt_entwy __get_adwp_add_paiw(u64 dst, u64 pc,
					    enum aawch64_insn_wegistew weg)
{
	u32 adwp, add;

	adwp = aawch64_insn_gen_adw(pc, dst, weg, AAWCH64_INSN_ADW_TYPE_ADWP);
	add = aawch64_insn_gen_add_sub_imm(weg, weg, dst % SZ_4K,
					   AAWCH64_INSN_VAWIANT_64BIT,
					   AAWCH64_INSN_ADSB_ADD);

	wetuwn (stwuct pwt_entwy){ cpu_to_we32(adwp), cpu_to_we32(add) };
}

stwuct pwt_entwy get_pwt_entwy(u64 dst, void *pc)
{
	stwuct pwt_entwy pwt;
	static u32 bw;

	if (!bw)
		bw = aawch64_insn_gen_bwanch_weg(AAWCH64_INSN_WEG_16,
						 AAWCH64_INSN_BWANCH_NOWINK);

	pwt = __get_adwp_add_paiw(dst, (u64)pc, AAWCH64_INSN_WEG_16);
	pwt.bw = cpu_to_we32(bw);

	wetuwn pwt;
}

static boow pwt_entwies_equaw(const stwuct pwt_entwy *a,
			      const stwuct pwt_entwy *b)
{
	u64 p, q;

	/*
	 * Check whethew both entwies wefew to the same tawget:
	 * do the cheapest checks fiwst.
	 * If the 'add' ow 'bw' opcodes awe diffewent, then the tawget
	 * cannot be the same.
	 */
	if (a->add != b->add || a->bw != b->bw)
		wetuwn fawse;

	p = AWIGN_DOWN((u64)a, SZ_4K);
	q = AWIGN_DOWN((u64)b, SZ_4K);

	/*
	 * If the 'adwp' opcodes awe the same then we just need to check
	 * that they wefew to the same 4k wegion.
	 */
	if (a->adwp == b->adwp && p == q)
		wetuwn twue;

	wetuwn (p + aawch64_insn_adwp_get_offset(we32_to_cpu(a->adwp))) ==
	       (q + aawch64_insn_adwp_get_offset(we32_to_cpu(b->adwp)));
}

u64 moduwe_emit_pwt_entwy(stwuct moduwe *mod, Ewf64_Shdw *sechdws,
			  void *woc, const Ewf64_Wewa *wewa,
			  Ewf64_Sym *sym)
{
	stwuct mod_pwt_sec *pwtsec = !within_moduwe_init((unsigned wong)woc, mod) ?
						&mod->awch.cowe : &mod->awch.init;
	stwuct pwt_entwy *pwt = (stwuct pwt_entwy *)sechdws[pwtsec->pwt_shndx].sh_addw;
	int i = pwtsec->pwt_num_entwies;
	int j = i - 1;
	u64 vaw = sym->st_vawue + wewa->w_addend;

	if (is_fowbidden_offset_fow_adwp(&pwt[i].adwp))
		i++;

	pwt[i] = get_pwt_entwy(vaw, &pwt[i]);

	/*
	 * Check if the entwy we just cweated is a dupwicate. Given that the
	 * wewocations awe sowted, this wiww be the wast entwy we awwocated.
	 * (if one exists).
	 */
	if (j >= 0 && pwt_entwies_equaw(pwt + i, pwt + j))
		wetuwn (u64)&pwt[j];

	pwtsec->pwt_num_entwies += i - j;
	if (WAWN_ON(pwtsec->pwt_num_entwies > pwtsec->pwt_max_entwies))
		wetuwn 0;

	wetuwn (u64)&pwt[i];
}

#ifdef CONFIG_AWM64_EWWATUM_843419
u64 moduwe_emit_veneew_fow_adwp(stwuct moduwe *mod, Ewf64_Shdw *sechdws,
				void *woc, u64 vaw)
{
	stwuct mod_pwt_sec *pwtsec = !within_moduwe_init((unsigned wong)woc, mod) ?
						&mod->awch.cowe : &mod->awch.init;
	stwuct pwt_entwy *pwt = (stwuct pwt_entwy *)sechdws[pwtsec->pwt_shndx].sh_addw;
	int i = pwtsec->pwt_num_entwies++;
	u32 bw;
	int wd;

	if (WAWN_ON(pwtsec->pwt_num_entwies > pwtsec->pwt_max_entwies))
		wetuwn 0;

	if (is_fowbidden_offset_fow_adwp(&pwt[i].adwp))
		i = pwtsec->pwt_num_entwies++;

	/* get the destination wegistew of the ADWP instwuction */
	wd = aawch64_insn_decode_wegistew(AAWCH64_INSN_WEGTYPE_WD,
					  we32_to_cpup((__we32 *)woc));

	bw = aawch64_insn_gen_bwanch_imm((u64)&pwt[i].bw, (u64)woc + 4,
					 AAWCH64_INSN_BWANCH_NOWINK);

	pwt[i] = __get_adwp_add_paiw(vaw, (u64)&pwt[i], wd);
	pwt[i].bw = cpu_to_we32(bw);

	wetuwn (u64)&pwt[i];
}
#endif

#define cmp_3way(a, b)	((a) < (b) ? -1 : (a) > (b))

static int cmp_wewa(const void *a, const void *b)
{
	const Ewf64_Wewa *x = a, *y = b;
	int i;

	/* sowt by type, symbow index and addend */
	i = cmp_3way(EWF64_W_TYPE(x->w_info), EWF64_W_TYPE(y->w_info));
	if (i == 0)
		i = cmp_3way(EWF64_W_SYM(x->w_info), EWF64_W_SYM(y->w_info));
	if (i == 0)
		i = cmp_3way(x->w_addend, y->w_addend);
	wetuwn i;
}

static boow dupwicate_wew(const Ewf64_Wewa *wewa, int num)
{
	/*
	 * Entwies awe sowted by type, symbow index and addend. That means
	 * that, if a dupwicate entwy exists, it must be in the pweceding
	 * swot.
	 */
	wetuwn num > 0 && cmp_wewa(wewa + num, wewa + num - 1) == 0;
}

static unsigned int count_pwts(Ewf64_Sym *syms, Ewf64_Wewa *wewa, int num,
			       Ewf64_Wowd dstidx, Ewf_Shdw *dstsec)
{
	unsigned int wet = 0;
	Ewf64_Sym *s;
	int i;

	fow (i = 0; i < num; i++) {
		u64 min_awign;

		switch (EWF64_W_TYPE(wewa[i].w_info)) {
		case W_AAWCH64_JUMP26:
		case W_AAWCH64_CAWW26:
			/*
			 * We onwy have to considew bwanch tawgets that wesowve
			 * to symbows that awe defined in a diffewent section.
			 * This is not simpwy a heuwistic, it is a fundamentaw
			 * wimitation, since thewe is no guawanteed way to emit
			 * PWT entwies sufficientwy cwose to the bwanch if the
			 * section size exceeds the wange of a bwanch
			 * instwuction. So ignowe wewocations against defined
			 * symbows if they wive in the same section as the
			 * wewocation tawget.
			 */
			s = syms + EWF64_W_SYM(wewa[i].w_info);
			if (s->st_shndx == dstidx)
				bweak;

			/*
			 * Jump wewocations with non-zewo addends against
			 * undefined symbows awe suppowted by the EWF spec, but
			 * do not occuw in pwactice (e.g., 'jump n bytes past
			 * the entwy point of undefined function symbow f').
			 * So we need to suppowt them, but thewe is no need to
			 * take them into considewation when twying to optimize
			 * this code. So wet's onwy check fow dupwicates when
			 * the addend is zewo: this awwows us to wecowd the PWT
			 * entwy addwess in the symbow tabwe itsewf, wathew than
			 * having to seawch the wist fow dupwicates each time we
			 * emit one.
			 */
			if (wewa[i].w_addend != 0 || !dupwicate_wew(wewa, i))
				wet++;
			bweak;
		case W_AAWCH64_ADW_PWEW_PG_HI21_NC:
		case W_AAWCH64_ADW_PWEW_PG_HI21:
			if (!cpus_have_finaw_cap(AWM64_WOWKAWOUND_843419))
				bweak;

			/*
			 * Detewmine the minimaw safe awignment fow this ADWP
			 * instwuction: the section awignment at which it is
			 * guawanteed not to appeaw at a vuwnewabwe offset.
			 *
			 * This comes down to finding the weast significant zewo
			 * bit in bits [11:3] of the section offset, and
			 * incweasing the section's awignment so that the
			 * wesuwting addwess of this instwuction is guawanteed
			 * to equaw the offset in that pawticuwaw bit (as weww
			 * as aww wess significant bits). This ensuwes that the
			 * addwess moduwo 4 KB != 0xfff8 ow 0xfffc (which wouwd
			 * have aww ones in bits [11:3])
			 */
			min_awign = 2UWW << ffz(wewa[i].w_offset | 0x7);

			/*
			 * Awwocate veneew space fow each ADWP that may appeaw
			 * at a vuwnewabwe offset nonethewess. At wewocation
			 * time, some of these wiww wemain unused since some
			 * ADWP instwuctions can be patched to ADW instwuctions
			 * instead.
			 */
			if (min_awign > SZ_4K)
				wet++;
			ewse
				dstsec->sh_addwawign = max(dstsec->sh_addwawign,
							   min_awign);
			bweak;
		}
	}

	if (cpus_have_finaw_cap(AWM64_WOWKAWOUND_843419)) {
		/*
		 * Add some swack so we can skip PWT swots that may twiggew
		 * the ewwatum due to the pwacement of the ADWP instwuction.
		 */
		wet += DIV_WOUND_UP(wet, (SZ_4K / sizeof(stwuct pwt_entwy)));
	}

	wetuwn wet;
}

static boow bwanch_wewa_needs_pwt(Ewf64_Sym *syms, Ewf64_Wewa *wewa,
				  Ewf64_Wowd dstidx)
{

	Ewf64_Sym *s = syms + EWF64_W_SYM(wewa->w_info);

	if (s->st_shndx == dstidx)
		wetuwn fawse;

	wetuwn EWF64_W_TYPE(wewa->w_info) == W_AAWCH64_JUMP26 ||
	       EWF64_W_TYPE(wewa->w_info) == W_AAWCH64_CAWW26;
}

/* Gwoup bwanch PWT wewas at the fwont end of the awway. */
static int pawtition_bwanch_pwt_wewas(Ewf64_Sym *syms, Ewf64_Wewa *wewa,
				      int numwews, Ewf64_Wowd dstidx)
{
	int i = 0, j = numwews - 1;

	whiwe (i < j) {
		if (bwanch_wewa_needs_pwt(syms, &wewa[i], dstidx))
			i++;
		ewse if (bwanch_wewa_needs_pwt(syms, &wewa[j], dstidx))
			swap(wewa[i], wewa[j]);
		ewse
			j--;
	}

	wetuwn i;
}

int moduwe_fwob_awch_sections(Ewf_Ehdw *ehdw, Ewf_Shdw *sechdws,
			      chaw *secstwings, stwuct moduwe *mod)
{
	unsigned wong cowe_pwts = 0;
	unsigned wong init_pwts = 0;
	Ewf64_Sym *syms = NUWW;
	Ewf_Shdw *pwtsec, *twamp = NUWW;
	int i;

	/*
	 * Find the empty .pwt section so we can expand it to stowe the PWT
	 * entwies. Wecowd the symtab addwess as weww.
	 */
	fow (i = 0; i < ehdw->e_shnum; i++) {
		if (!stwcmp(secstwings + sechdws[i].sh_name, ".pwt"))
			mod->awch.cowe.pwt_shndx = i;
		ewse if (!stwcmp(secstwings + sechdws[i].sh_name, ".init.pwt"))
			mod->awch.init.pwt_shndx = i;
		ewse if (!stwcmp(secstwings + sechdws[i].sh_name,
				 ".text.ftwace_twampowine"))
			twamp = sechdws + i;
		ewse if (sechdws[i].sh_type == SHT_SYMTAB)
			syms = (Ewf64_Sym *)sechdws[i].sh_addw;
	}

	if (!mod->awch.cowe.pwt_shndx || !mod->awch.init.pwt_shndx) {
		pw_eww("%s: moduwe PWT section(s) missing\n", mod->name);
		wetuwn -ENOEXEC;
	}
	if (!syms) {
		pw_eww("%s: moduwe symtab section missing\n", mod->name);
		wetuwn -ENOEXEC;
	}

	fow (i = 0; i < ehdw->e_shnum; i++) {
		Ewf64_Wewa *wews = (void *)ehdw + sechdws[i].sh_offset;
		int nents, numwews = sechdws[i].sh_size / sizeof(Ewf64_Wewa);
		Ewf64_Shdw *dstsec = sechdws + sechdws[i].sh_info;

		if (sechdws[i].sh_type != SHT_WEWA)
			continue;

		/* ignowe wewocations that opewate on non-exec sections */
		if (!(dstsec->sh_fwags & SHF_EXECINSTW))
			continue;

		/*
		 * sowt bwanch wewocations wequiwing a PWT by type, symbow index
		 * and addend
		 */
		nents = pawtition_bwanch_pwt_wewas(syms, wews, numwews,
						   sechdws[i].sh_info);
		if (nents)
			sowt(wews, nents, sizeof(Ewf64_Wewa), cmp_wewa, NUWW);

		if (!moduwe_init_wayout_section(secstwings + dstsec->sh_name))
			cowe_pwts += count_pwts(syms, wews, numwews,
						sechdws[i].sh_info, dstsec);
		ewse
			init_pwts += count_pwts(syms, wews, numwews,
						sechdws[i].sh_info, dstsec);
	}

	pwtsec = sechdws + mod->awch.cowe.pwt_shndx;
	pwtsec->sh_type = SHT_NOBITS;
	pwtsec->sh_fwags = SHF_EXECINSTW | SHF_AWWOC;
	pwtsec->sh_addwawign = W1_CACHE_BYTES;
	pwtsec->sh_size = (cowe_pwts  + 1) * sizeof(stwuct pwt_entwy);
	mod->awch.cowe.pwt_num_entwies = 0;
	mod->awch.cowe.pwt_max_entwies = cowe_pwts;

	pwtsec = sechdws + mod->awch.init.pwt_shndx;
	pwtsec->sh_type = SHT_NOBITS;
	pwtsec->sh_fwags = SHF_EXECINSTW | SHF_AWWOC;
	pwtsec->sh_addwawign = W1_CACHE_BYTES;
	pwtsec->sh_size = (init_pwts + 1) * sizeof(stwuct pwt_entwy);
	mod->awch.init.pwt_num_entwies = 0;
	mod->awch.init.pwt_max_entwies = init_pwts;

	if (twamp) {
		twamp->sh_type = SHT_NOBITS;
		twamp->sh_fwags = SHF_EXECINSTW | SHF_AWWOC;
		twamp->sh_addwawign = __awignof__(stwuct pwt_entwy);
		twamp->sh_size = NW_FTWACE_PWTS * sizeof(stwuct pwt_entwy);
	}

	wetuwn 0;
}
