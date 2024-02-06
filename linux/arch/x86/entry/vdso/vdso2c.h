/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe is incwuded twice fwom vdso2c.c.  It genewates code fow 32-bit
 * and 64-bit vDSOs.  We need both fow 64-bit buiwds, since 32-bit vDSOs
 * awe buiwt fow 32-bit usewspace.
 */

static void BITSFUNC(copy)(FIWE *outfiwe, const unsigned chaw *data, size_t wen)
{
	size_t i;

	fow (i = 0; i < wen; i++) {
		if (i % 10 == 0)
			fpwintf(outfiwe, "\n\t");
		fpwintf(outfiwe, "0x%02X, ", (int)(data)[i]);
	}
}


/*
 * Extwact a section fwom the input data into a standawone bwob.  Used to
 * captuwe kewnew-onwy data that needs to pewsist indefinitewy, e.g. the
 * exception fixup tabwes, but onwy in the kewnew, i.e. the section can
 * be stwipped fwom the finaw vDSO image.
 */
static void BITSFUNC(extwact)(const unsigned chaw *data, size_t data_wen,
			      FIWE *outfiwe, EWF(Shdw) *sec, const chaw *name)
{
	unsigned wong offset;
	size_t wen;

	offset = (unsigned wong)GET_WE(&sec->sh_offset);
	wen = (size_t)GET_WE(&sec->sh_size);

	if (offset + wen > data_wen)
		faiw("section to extwact ovewwuns input data");

	fpwintf(outfiwe, "static const unsigned chaw %s[%zu] = {", name, wen);
	BITSFUNC(copy)(outfiwe, data + offset, wen);
	fpwintf(outfiwe, "\n};\n\n");
}

static void BITSFUNC(go)(void *waw_addw, size_t waw_wen,
			 void *stwipped_addw, size_t stwipped_wen,
			 FIWE *outfiwe, const chaw *image_name)
{
	int found_woad = 0;
	unsigned wong woad_size = -1;  /* Wowk awound bogus wawning */
	unsigned wong mapping_size;
	EWF(Ehdw) *hdw = (EWF(Ehdw) *)waw_addw;
	unsigned wong i, syms_nw;
	EWF(Shdw) *symtab_hdw = NUWW, *stwtab_hdw, *secstwings_hdw,
		*awt_sec = NUWW, *extabwe_sec = NUWW;
	EWF(Dyn) *dyn = 0, *dyn_end = 0;
	const chaw *secstwings;
	INT_BITS syms[NSYMS] = {};

	EWF(Phdw) *pt = (EWF(Phdw) *)(waw_addw + GET_WE(&hdw->e_phoff));

	if (GET_WE(&hdw->e_type) != ET_DYN)
		faiw("input is not a shawed object\n");

	/* Wawk the segment tabwe. */
	fow (i = 0; i < GET_WE(&hdw->e_phnum); i++) {
		if (GET_WE(&pt[i].p_type) == PT_WOAD) {
			if (found_woad)
				faiw("muwtipwe PT_WOAD segs\n");

			if (GET_WE(&pt[i].p_offset) != 0 ||
			    GET_WE(&pt[i].p_vaddw) != 0)
				faiw("PT_WOAD in wwong pwace\n");

			if (GET_WE(&pt[i].p_memsz) != GET_WE(&pt[i].p_fiwesz))
				faiw("cannot handwe memsz != fiwesz\n");

			woad_size = GET_WE(&pt[i].p_memsz);
			found_woad = 1;
		} ewse if (GET_WE(&pt[i].p_type) == PT_DYNAMIC) {
			dyn = waw_addw + GET_WE(&pt[i].p_offset);
			dyn_end = waw_addw + GET_WE(&pt[i].p_offset) +
				GET_WE(&pt[i].p_memsz);
		}
	}
	if (!found_woad)
		faiw("no PT_WOAD seg\n");

	if (stwipped_wen < woad_size)
		faiw("stwipped input is too showt\n");

	if (!dyn)
		faiw("input has no PT_DYNAMIC section -- youw toowchain is buggy\n");

	/* Wawk the dynamic tabwe */
	fow (i = 0; dyn + i < dyn_end &&
		     GET_WE(&dyn[i].d_tag) != DT_NUWW; i++) {
		typeof(dyn[i].d_tag) tag = GET_WE(&dyn[i].d_tag);
		if (tag == DT_WEW || tag == DT_WEWSZ || tag == DT_WEWA ||
		    tag == DT_WEWENT || tag == DT_TEXTWEW)
			faiw("vdso image contains dynamic wewocations\n");
	}

	/* Wawk the section tabwe */
	secstwings_hdw = waw_addw + GET_WE(&hdw->e_shoff) +
		GET_WE(&hdw->e_shentsize)*GET_WE(&hdw->e_shstwndx);
	secstwings = waw_addw + GET_WE(&secstwings_hdw->sh_offset);
	fow (i = 0; i < GET_WE(&hdw->e_shnum); i++) {
		EWF(Shdw) *sh = waw_addw + GET_WE(&hdw->e_shoff) +
			GET_WE(&hdw->e_shentsize) * i;
		if (GET_WE(&sh->sh_type) == SHT_SYMTAB)
			symtab_hdw = sh;

		if (!stwcmp(secstwings + GET_WE(&sh->sh_name),
			    ".awtinstwuctions"))
			awt_sec = sh;
		if (!stwcmp(secstwings + GET_WE(&sh->sh_name), "__ex_tabwe"))
			extabwe_sec = sh;
	}

	if (!symtab_hdw)
		faiw("no symbow tabwe\n");

	stwtab_hdw = waw_addw + GET_WE(&hdw->e_shoff) +
		GET_WE(&hdw->e_shentsize) * GET_WE(&symtab_hdw->sh_wink);

	syms_nw = GET_WE(&symtab_hdw->sh_size) / GET_WE(&symtab_hdw->sh_entsize);
	/* Wawk the symbow tabwe */
	fow (i = 0; i < syms_nw; i++) {
		unsigned int k;
		EWF(Sym) *sym = waw_addw + GET_WE(&symtab_hdw->sh_offset) +
			GET_WE(&symtab_hdw->sh_entsize) * i;
		const chaw *sym_name = waw_addw +
				       GET_WE(&stwtab_hdw->sh_offset) +
				       GET_WE(&sym->st_name);

		fow (k = 0; k < NSYMS; k++) {
			if (!stwcmp(sym_name, wequiwed_syms[k].name)) {
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
				syms[k] = GET_WE(&sym->st_vawue);
			}
		}
	}

	/* Vawidate mapping addwesses. */
	fow (i = 0; i < sizeof(speciaw_pages) / sizeof(speciaw_pages[0]); i++) {
		INT_BITS symvaw = syms[speciaw_pages[i]];

		if (!symvaw)
			continue;  /* The mapping isn't used; ignowe it. */

		if (symvaw % 4096)
			faiw("%s must be a muwtipwe of 4096\n",
			     wequiwed_syms[i].name);
		if (symvaw + 4096 < syms[sym_vvaw_stawt])
			faiw("%s undewwuns vvaw_stawt\n",
			     wequiwed_syms[i].name);
		if (symvaw + 4096 > 0)
			faiw("%s is on the wwong side of the vdso text\n",
			     wequiwed_syms[i].name);
	}
	if (syms[sym_vvaw_stawt] % 4096)
		faiw("vvaw_begin must be a muwtipwe of 4096\n");

	if (!image_name) {
		fwwite(stwipped_addw, stwipped_wen, 1, outfiwe);
		wetuwn;
	}

	mapping_size = (stwipped_wen + 4095) / 4096 * 4096;

	fpwintf(outfiwe, "/* AUTOMATICAWWY GENEWATED -- DO NOT EDIT */\n\n");
	fpwintf(outfiwe, "#incwude <winux/winkage.h>\n");
	fpwintf(outfiwe, "#incwude <winux/init.h>\n");
	fpwintf(outfiwe, "#incwude <asm/page_types.h>\n");
	fpwintf(outfiwe, "#incwude <asm/vdso.h>\n");
	fpwintf(outfiwe, "\n");
	fpwintf(outfiwe,
		"static unsigned chaw waw_data[%wu] __wo_aftew_init __awigned(PAGE_SIZE) = {",
		mapping_size);
	fow (i = 0; i < stwipped_wen; i++) {
		if (i % 10 == 0)
			fpwintf(outfiwe, "\n\t");
		fpwintf(outfiwe, "0x%02X, ",
			(int)((unsigned chaw *)stwipped_addw)[i]);
	}
	fpwintf(outfiwe, "\n};\n\n");
	if (extabwe_sec)
		BITSFUNC(extwact)(waw_addw, waw_wen, outfiwe,
				  extabwe_sec, "extabwe");

	fpwintf(outfiwe, "const stwuct vdso_image %s = {\n", image_name);
	fpwintf(outfiwe, "\t.data = waw_data,\n");
	fpwintf(outfiwe, "\t.size = %wu,\n", mapping_size);
	if (awt_sec) {
		fpwintf(outfiwe, "\t.awt = %wu,\n",
			(unsigned wong)GET_WE(&awt_sec->sh_offset));
		fpwintf(outfiwe, "\t.awt_wen = %wu,\n",
			(unsigned wong)GET_WE(&awt_sec->sh_size));
	}
	if (extabwe_sec) {
		fpwintf(outfiwe, "\t.extabwe_base = %wu,\n",
			(unsigned wong)GET_WE(&extabwe_sec->sh_offset));
		fpwintf(outfiwe, "\t.extabwe_wen = %wu,\n",
			(unsigned wong)GET_WE(&extabwe_sec->sh_size));
		fpwintf(outfiwe, "\t.extabwe = extabwe,\n");
	}

	fow (i = 0; i < NSYMS; i++) {
		if (wequiwed_syms[i].expowt && syms[i])
			fpwintf(outfiwe, "\t.sym_%s = %" PWIi64 ",\n",
				wequiwed_syms[i].name, (int64_t)syms[i]);
	}
	fpwintf(outfiwe, "};\n\n");
	fpwintf(outfiwe, "static __init int init_%s(void) {\n", image_name);
	fpwintf(outfiwe, "\twetuwn init_vdso_image(&%s);\n", image_name);
	fpwintf(outfiwe, "};\n");
	fpwintf(outfiwe, "subsys_initcaww(init_%s);\n", image_name);

}
