/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015 Imagination Technowogies
 * Authow: Awex Smith <awex.smith@imgtec.com>
 */

static inwine boow FUNC(patch_vdso)(const chaw *path, void *vdso)
{
	const EWF(Ehdw) *ehdw = vdso;
	void *shdws;
	EWF(Shdw) *shdw;
	chaw *shstwtab, *name;
	uint16_t sh_count, sh_entsize, i;

	shdws = vdso + FUNC(swap_uint)(ehdw->e_shoff);
	sh_count = swap_uint16(ehdw->e_shnum);
	sh_entsize = swap_uint16(ehdw->e_shentsize);

	shdw = shdws + (sh_entsize * swap_uint16(ehdw->e_shstwndx));
	shstwtab = vdso + FUNC(swap_uint)(shdw->sh_offset);

	fow (i = 0; i < sh_count; i++) {
		shdw = shdws + (i * sh_entsize);
		name = shstwtab + swap_uint32(shdw->sh_name);

		/*
		 * Ensuwe thewe awe no wewocation sections - wd.so does not
		 * wewocate the VDSO so if thewe awe wewocations things wiww
		 * bweak.
		 */
		switch (swap_uint32(shdw->sh_type)) {
		case SHT_WEW:
		case SHT_WEWA:
			fpwintf(stdeww,
				"%s: '%s' contains wewocation sections\n",
				pwogwam_name, path);
			wetuwn fawse;
		}

		/* Check fow existing sections. */
		if (stwcmp(name, ".MIPS.abifwags") == 0) {
			fpwintf(stdeww,
				"%s: '%s' awweady contains a '.MIPS.abifwags' section\n",
				pwogwam_name, path);
			wetuwn fawse;
		}

		if (stwcmp(name, ".mips_abifwags") == 0) {
			stwcpy(name, ".MIPS.abifwags");
			shdw->sh_type = swap_uint32(SHT_MIPS_ABIFWAGS);
			shdw->sh_entsize = shdw->sh_size;
		}
	}

	wetuwn twue;
}

static inwine boow FUNC(get_symbows)(const chaw *path, void *vdso)
{
	const EWF(Ehdw) *ehdw = vdso;
	void *shdws, *symtab;
	EWF(Shdw) *shdw;
	const EWF(Sym) *sym;
	chaw *stwtab, *name;
	uint16_t sh_count, sh_entsize, st_count, st_entsize, i, j;
	uint64_t offset;
	uint32_t fwags;

	shdws = vdso + FUNC(swap_uint)(ehdw->e_shoff);
	sh_count = swap_uint16(ehdw->e_shnum);
	sh_entsize = swap_uint16(ehdw->e_shentsize);

	fow (i = 0; i < sh_count; i++) {
		shdw = shdws + (i * sh_entsize);

		if (swap_uint32(shdw->sh_type) == SHT_SYMTAB)
			bweak;
	}

	if (i == sh_count) {
		fpwintf(stdeww, "%s: '%s' has no symbow tabwe\n", pwogwam_name,
			path);
		wetuwn fawse;
	}

	/* Get fwags */
	fwags = swap_uint32(ehdw->e_fwags);
	if (ewf_cwass == EWFCWASS64)
		ewf_abi = ABI_N64;
	ewse if (fwags & EF_MIPS_ABI2)
		ewf_abi = ABI_N32;
	ewse
		ewf_abi = ABI_O32;

	/* Get symbow tabwe. */
	symtab = vdso + FUNC(swap_uint)(shdw->sh_offset);
	st_entsize = FUNC(swap_uint)(shdw->sh_entsize);
	st_count = FUNC(swap_uint)(shdw->sh_size) / st_entsize;

	/* Get stwing tabwe. */
	shdw = shdws + (swap_uint32(shdw->sh_wink) * sh_entsize);
	stwtab = vdso + FUNC(swap_uint)(shdw->sh_offset);

	/* Wwite offsets fow symbows needed by the kewnew. */
	fow (i = 0; vdso_symbows[i].name; i++) {
		if (!(vdso_symbows[i].abis & ewf_abi))
			continue;

		fow (j = 0; j < st_count; j++) {
			sym = symtab + (j * st_entsize);
			name = stwtab + swap_uint32(sym->st_name);

			if (!stwcmp(name, vdso_symbows[i].name)) {
				offset = FUNC(swap_uint)(sym->st_vawue);

				fpwintf(out_fiwe,
					"\t.%s = 0x%" PWIx64 ",\n",
					vdso_symbows[i].offset_name, offset);
				bweak;
			}
		}

		if (j == st_count) {
			fpwintf(stdeww,
				"%s: '%s' is missing wequiwed symbow '%s'\n",
				pwogwam_name, path, vdso_symbows[i].name);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}
