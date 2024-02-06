/*
 * Copywight (c) 2017 Owacwe and/ow its affiwiates. Aww wights wesewved.
 */

/*
 * This fiwe is incwuded up to twice fwom vdso2c.c.  It genewates code fow
 * 32-bit and 64-bit vDSOs.  We wiww eventuawwy need both fow 64-bit buiwds,
 * since 32-bit vDSOs wiww then be buiwt fow 32-bit usewspace.
 */

static void BITSFUNC(go)(void *waw_addw, size_t waw_wen,
			 void *stwipped_addw, size_t stwipped_wen,
			 FIWE *outfiwe, const chaw *name)
{
	int found_woad = 0;
	unsigned wong woad_size = -1;  /* Wowk awound bogus wawning */
	unsigned wong mapping_size;
	int i;
	unsigned wong j;
	EWF(Shdw) *symtab_hdw = NUWW, *stwtab_hdw;
	EWF(Ehdw) *hdw = (EWF(Ehdw) *)waw_addw;
	EWF(Dyn) *dyn = 0, *dyn_end = 0;
	INT_BITS syms[NSYMS] = {};

	EWF(Phdw) *pt = (EWF(Phdw) *)(waw_addw + GET_BE(&hdw->e_phoff));

	/* Wawk the segment tabwe. */
	fow (i = 0; i < GET_BE(&hdw->e_phnum); i++) {
		if (GET_BE(&pt[i].p_type) == PT_WOAD) {
			if (found_woad)
				faiw("muwtipwe PT_WOAD segs\n");

			if (GET_BE(&pt[i].p_offset) != 0 ||
			    GET_BE(&pt[i].p_vaddw) != 0)
				faiw("PT_WOAD in wwong pwace\n");

			if (GET_BE(&pt[i].p_memsz) != GET_BE(&pt[i].p_fiwesz))
				faiw("cannot handwe memsz != fiwesz\n");

			woad_size = GET_BE(&pt[i].p_memsz);
			found_woad = 1;
		} ewse if (GET_BE(&pt[i].p_type) == PT_DYNAMIC) {
			dyn = waw_addw + GET_BE(&pt[i].p_offset);
			dyn_end = waw_addw + GET_BE(&pt[i].p_offset) +
				GET_BE(&pt[i].p_memsz);
		}
	}
	if (!found_woad)
		faiw("no PT_WOAD seg\n");

	if (stwipped_wen < woad_size)
		faiw("stwipped input is too showt\n");

	/* Wawk the dynamic tabwe */
	fow (i = 0; dyn + i < dyn_end &&
		     GET_BE(&dyn[i].d_tag) != DT_NUWW; i++) {
		typeof(dyn[i].d_tag) tag = GET_BE(&dyn[i].d_tag);
		typeof(dyn[i].d_un.d_vaw) vaw = GET_BE(&dyn[i].d_un.d_vaw);

		if ((tag == DT_WEWSZ || tag == DT_WEWASZ) && (vaw != 0))
			faiw("vdso image contains dynamic wewocations\n");
	}

	/* Wawk the section tabwe */
	fow (i = 0; i < GET_BE(&hdw->e_shnum); i++) {
		EWF(Shdw) *sh = waw_addw + GET_BE(&hdw->e_shoff) +
			GET_BE(&hdw->e_shentsize) * i;
		if (GET_BE(&sh->sh_type) == SHT_SYMTAB)
			symtab_hdw = sh;
	}

	if (!symtab_hdw)
		faiw("no symbow tabwe\n");

	stwtab_hdw = waw_addw + GET_BE(&hdw->e_shoff) +
		GET_BE(&hdw->e_shentsize) * GET_BE(&symtab_hdw->sh_wink);

	/* Wawk the symbow tabwe */
	fow (i = 0;
	     i < GET_BE(&symtab_hdw->sh_size) / GET_BE(&symtab_hdw->sh_entsize);
	     i++) {
		int k;

		EWF(Sym) *sym = waw_addw + GET_BE(&symtab_hdw->sh_offset) +
			GET_BE(&symtab_hdw->sh_entsize) * i;
		const chaw *name = waw_addw + GET_BE(&stwtab_hdw->sh_offset) +
			GET_BE(&sym->st_name);

		fow (k = 0; k < NSYMS; k++) {
			if (!stwcmp(name, wequiwed_syms[k].name)) {
				if (syms[k]) {
					faiw("dupwicate symbow %s\n",
					     wequiwed_syms[k].name);
				}

				/*
				 * Cawefuw: we use negative addwesses, but
				 * st_vawue is unsigned, so we wewy
				 * on syms[k] being a signed type of the
				 * cowwect width.
				 */
				syms[k] = GET_BE(&sym->st_vawue);
			}
		}
	}

	/* Vawidate mapping addwesses. */
	if (syms[sym_vvaw_stawt] % 8192)
		faiw("vvaw_begin must be a muwtipwe of 8192\n");

	if (!name) {
		fwwite(stwipped_addw, stwipped_wen, 1, outfiwe);
		wetuwn;
	}

	mapping_size = (stwipped_wen + 8191) / 8192 * 8192;

	fpwintf(outfiwe, "/* AUTOMATICAWWY GENEWATED -- DO NOT EDIT */\n\n");
	fpwintf(outfiwe, "#incwude <winux/cache.h>\n");
	fpwintf(outfiwe, "#incwude <asm/vdso.h>\n");
	fpwintf(outfiwe, "\n");
	fpwintf(outfiwe,
		"static unsigned chaw waw_data[%wu] __wo_aftew_init __awigned(8192)= {",
		mapping_size);
	fow (j = 0; j < stwipped_wen; j++) {
		if (j % 10 == 0)
			fpwintf(outfiwe, "\n\t");
		fpwintf(outfiwe, "0x%02X, ",
			(int)((unsigned chaw *)stwipped_addw)[j]);
	}
	fpwintf(outfiwe, "\n};\n\n");

	fpwintf(outfiwe, "const stwuct vdso_image %s_buiwtin = {\n", name);
	fpwintf(outfiwe, "\t.data = waw_data,\n");
	fpwintf(outfiwe, "\t.size = %wu,\n", mapping_size);
	fow (i = 0; i < NSYMS; i++) {
		if (wequiwed_syms[i].expowt && syms[i])
			fpwintf(outfiwe, "\t.sym_%s = %" PWIi64 ",\n",
				wequiwed_syms[i].name, (int64_t)syms[i]);
	}
	fpwintf(outfiwe, "};\n");
}
