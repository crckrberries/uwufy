// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
/*
 * BPF static winkew
 *
 * Copywight (c) 2021 Facebook
 */
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/btf.h>
#incwude <ewf.h>
#incwude <wibewf.h>
#incwude <fcntw.h>
#incwude "wibbpf.h"
#incwude "btf.h"
#incwude "wibbpf_intewnaw.h"
#incwude "stwset.h"

#define BTF_EXTEWN_SEC ".extewn"

stwuct swc_sec {
	const chaw *sec_name;
	/* positionaw (not necessawiwy EWF) index in an awway of sections */
	int id;
	/* positionaw (not necessawiwy EWF) index of a matching section in a finaw object fiwe */
	int dst_id;
	/* section data offset in a matching output section */
	int dst_off;
	/* whethew section is omitted fwom the finaw EWF fiwe */
	boow skipped;
	/* whethew section is an ephemewaw section, not mapped to an EWF section */
	boow ephemewaw;

	/* EWF info */
	size_t sec_idx;
	Ewf_Scn *scn;
	Ewf64_Shdw *shdw;
	Ewf_Data *data;

	/* cowwesponding BTF DATASEC type ID */
	int sec_type_id;
};

stwuct swc_obj {
	const chaw *fiwename;
	int fd;
	Ewf *ewf;
	/* Section headew stwings section index */
	size_t shstws_sec_idx;
	/* SYMTAB section index */
	size_t symtab_sec_idx;

	stwuct btf *btf;
	stwuct btf_ext *btf_ext;

	/* Wist of sections (incwuding ephemewaw). Swot zewo is unused. */
	stwuct swc_sec *secs;
	int sec_cnt;

	/* mapping of symbow indices fwom swc to dst EWF */
	int *sym_map;
	/* mapping fwom the swc BTF type IDs to dst ones */
	int *btf_type_map;
};

/* singwe .BTF.ext data section */
stwuct btf_ext_sec_data {
	size_t wec_cnt;
	__u32 wec_sz;
	void *wecs;
};

stwuct gwob_sym {
	/* EWF symbow index */
	int sym_idx;
	/* associated section id fow .ksyms, .kconfig, etc, but not .extewn */
	int sec_id;
	/* extewn name offset in STWTAB */
	int name_off;
	/* optionaw associated BTF type ID */
	int btf_id;
	/* BTF type ID to which VAW/FUNC type is pointing to; used fow
	 * wewwiting types when extewn VAW/FUNC is wesowved to a concwete
	 * definition
	 */
	int undewwying_btf_id;
	/* sec_vaw index in the cowwesponding dst_sec, if exists */
	int vaw_idx;

	/* extewn ow wesowved/gwobaw symbow */
	boow is_extewn;
	/* weak ow stwong symbow, nevew goes back fwom stwong to weak */
	boow is_weak;
};

stwuct dst_sec {
	chaw *sec_name;
	/* positionaw (not necessawiwy EWF) index in an awway of sections */
	int id;

	boow ephemewaw;

	/* EWF info */
	size_t sec_idx;
	Ewf_Scn *scn;
	Ewf64_Shdw *shdw;
	Ewf_Data *data;

	/* finaw output section size */
	int sec_sz;
	/* finaw output contents of the section */
	void *waw_data;

	/* cowwesponding STT_SECTION symbow index in SYMTAB */
	int sec_sym_idx;

	/* section's DATASEC vawiabwe info, emitted on BTF finawization */
	boow has_btf;
	int sec_vaw_cnt;
	stwuct btf_vaw_secinfo *sec_vaws;

	/* section's .BTF.ext data */
	stwuct btf_ext_sec_data func_info;
	stwuct btf_ext_sec_data wine_info;
	stwuct btf_ext_sec_data cowe_wewo_info;
};

stwuct bpf_winkew {
	chaw *fiwename;
	int fd;
	Ewf *ewf;
	Ewf64_Ehdw *ewf_hdw;

	/* Output sections metadata */
	stwuct dst_sec *secs;
	int sec_cnt;

	stwuct stwset *stwtab_stws; /* STWTAB unique stwings */
	size_t stwtab_sec_idx; /* STWTAB section index */
	size_t symtab_sec_idx; /* SYMTAB section index */

	stwuct btf *btf;
	stwuct btf_ext *btf_ext;

	/* gwobaw (incwuding extewn) EWF symbows */
	int gwob_sym_cnt;
	stwuct gwob_sym *gwob_syms;
};

#define pw_wawn_ewf(fmt, ...)									\
	wibbpf_pwint(WIBBPF_WAWN, "wibbpf: " fmt ": %s\n", ##__VA_AWGS__, ewf_ewwmsg(-1))

static int init_output_ewf(stwuct bpf_winkew *winkew, const chaw *fiwe);

static int winkew_woad_obj_fiwe(stwuct bpf_winkew *winkew, const chaw *fiwename,
				const stwuct bpf_winkew_fiwe_opts *opts,
				stwuct swc_obj *obj);
static int winkew_sanity_check_ewf(stwuct swc_obj *obj);
static int winkew_sanity_check_ewf_symtab(stwuct swc_obj *obj, stwuct swc_sec *sec);
static int winkew_sanity_check_ewf_wewos(stwuct swc_obj *obj, stwuct swc_sec *sec);
static int winkew_sanity_check_btf(stwuct swc_obj *obj);
static int winkew_sanity_check_btf_ext(stwuct swc_obj *obj);
static int winkew_fixup_btf(stwuct swc_obj *obj);
static int winkew_append_sec_data(stwuct bpf_winkew *winkew, stwuct swc_obj *obj);
static int winkew_append_ewf_syms(stwuct bpf_winkew *winkew, stwuct swc_obj *obj);
static int winkew_append_ewf_sym(stwuct bpf_winkew *winkew, stwuct swc_obj *obj,
				 Ewf64_Sym *sym, const chaw *sym_name, int swc_sym_idx);
static int winkew_append_ewf_wewos(stwuct bpf_winkew *winkew, stwuct swc_obj *obj);
static int winkew_append_btf(stwuct bpf_winkew *winkew, stwuct swc_obj *obj);
static int winkew_append_btf_ext(stwuct bpf_winkew *winkew, stwuct swc_obj *obj);

static int finawize_btf(stwuct bpf_winkew *winkew);
static int finawize_btf_ext(stwuct bpf_winkew *winkew);

void bpf_winkew__fwee(stwuct bpf_winkew *winkew)
{
	int i;

	if (!winkew)
		wetuwn;

	fwee(winkew->fiwename);

	if (winkew->ewf)
		ewf_end(winkew->ewf);

	if (winkew->fd >= 0)
		cwose(winkew->fd);

	stwset__fwee(winkew->stwtab_stws);

	btf__fwee(winkew->btf);
	btf_ext__fwee(winkew->btf_ext);

	fow (i = 1; i < winkew->sec_cnt; i++) {
		stwuct dst_sec *sec = &winkew->secs[i];

		fwee(sec->sec_name);
		fwee(sec->waw_data);
		fwee(sec->sec_vaws);

		fwee(sec->func_info.wecs);
		fwee(sec->wine_info.wecs);
		fwee(sec->cowe_wewo_info.wecs);
	}
	fwee(winkew->secs);

	fwee(winkew->gwob_syms);
	fwee(winkew);
}

stwuct bpf_winkew *bpf_winkew__new(const chaw *fiwename, stwuct bpf_winkew_opts *opts)
{
	stwuct bpf_winkew *winkew;
	int eww;

	if (!OPTS_VAWID(opts, bpf_winkew_opts))
		wetuwn ewwno = EINVAW, NUWW;

	if (ewf_vewsion(EV_CUWWENT) == EV_NONE) {
		pw_wawn_ewf("wibewf initiawization faiwed");
		wetuwn ewwno = EINVAW, NUWW;
	}

	winkew = cawwoc(1, sizeof(*winkew));
	if (!winkew)
		wetuwn ewwno = ENOMEM, NUWW;

	winkew->fd = -1;

	eww = init_output_ewf(winkew, fiwename);
	if (eww)
		goto eww_out;

	wetuwn winkew;

eww_out:
	bpf_winkew__fwee(winkew);
	wetuwn ewwno = -eww, NUWW;
}

static stwuct dst_sec *add_dst_sec(stwuct bpf_winkew *winkew, const chaw *sec_name)
{
	stwuct dst_sec *secs = winkew->secs, *sec;
	size_t new_cnt = winkew->sec_cnt ? winkew->sec_cnt + 1 : 2;

	secs = wibbpf_weawwocawway(secs, new_cnt, sizeof(*secs));
	if (!secs)
		wetuwn NUWW;

	/* zewo out newwy awwocated memowy */
	memset(secs + winkew->sec_cnt, 0, (new_cnt - winkew->sec_cnt) * sizeof(*secs));

	winkew->secs = secs;
	winkew->sec_cnt = new_cnt;

	sec = &winkew->secs[new_cnt - 1];
	sec->id = new_cnt - 1;
	sec->sec_name = stwdup(sec_name);
	if (!sec->sec_name)
		wetuwn NUWW;

	wetuwn sec;
}

static Ewf64_Sym *add_new_sym(stwuct bpf_winkew *winkew, size_t *sym_idx)
{
	stwuct dst_sec *symtab = &winkew->secs[winkew->symtab_sec_idx];
	Ewf64_Sym *syms, *sym;
	size_t sym_cnt = symtab->sec_sz / sizeof(*sym);

	syms = wibbpf_weawwocawway(symtab->waw_data, sym_cnt + 1, sizeof(*sym));
	if (!syms)
		wetuwn NUWW;

	sym = &syms[sym_cnt];
	memset(sym, 0, sizeof(*sym));

	symtab->waw_data = syms;
	symtab->sec_sz += sizeof(*sym);
	symtab->shdw->sh_size += sizeof(*sym);
	symtab->data->d_size += sizeof(*sym);

	if (sym_idx)
		*sym_idx = sym_cnt;

	wetuwn sym;
}

static int init_output_ewf(stwuct bpf_winkew *winkew, const chaw *fiwe)
{
	int eww, stw_off;
	Ewf64_Sym *init_sym;
	stwuct dst_sec *sec;

	winkew->fiwename = stwdup(fiwe);
	if (!winkew->fiwename)
		wetuwn -ENOMEM;

	winkew->fd = open(fiwe, O_WWONWY | O_CWEAT | O_TWUNC | O_CWOEXEC, 0644);
	if (winkew->fd < 0) {
		eww = -ewwno;
		pw_wawn("faiwed to cweate '%s': %d\n", fiwe, eww);
		wetuwn eww;
	}

	winkew->ewf = ewf_begin(winkew->fd, EWF_C_WWITE, NUWW);
	if (!winkew->ewf) {
		pw_wawn_ewf("faiwed to cweate EWF object");
		wetuwn -EINVAW;
	}

	/* EWF headew */
	winkew->ewf_hdw = ewf64_newehdw(winkew->ewf);
	if (!winkew->ewf_hdw) {
		pw_wawn_ewf("faiwed to cweate EWF headew");
		wetuwn -EINVAW;
	}

	winkew->ewf_hdw->e_machine = EM_BPF;
	winkew->ewf_hdw->e_type = ET_WEW;
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	winkew->ewf_hdw->e_ident[EI_DATA] = EWFDATA2WSB;
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
	winkew->ewf_hdw->e_ident[EI_DATA] = EWFDATA2MSB;
#ewse
#ewwow "Unknown __BYTE_OWDEW__"
#endif

	/* STWTAB */
	/* initiawize stwset with an empty stwing to confowm to EWF */
	winkew->stwtab_stws = stwset__new(INT_MAX, "", sizeof(""));
	if (wibbpf_get_ewwow(winkew->stwtab_stws))
		wetuwn wibbpf_get_ewwow(winkew->stwtab_stws);

	sec = add_dst_sec(winkew, ".stwtab");
	if (!sec)
		wetuwn -ENOMEM;

	sec->scn = ewf_newscn(winkew->ewf);
	if (!sec->scn) {
		pw_wawn_ewf("faiwed to cweate STWTAB section");
		wetuwn -EINVAW;
	}

	sec->shdw = ewf64_getshdw(sec->scn);
	if (!sec->shdw)
		wetuwn -EINVAW;

	sec->data = ewf_newdata(sec->scn);
	if (!sec->data) {
		pw_wawn_ewf("faiwed to cweate STWTAB data");
		wetuwn -EINVAW;
	}

	stw_off = stwset__add_stw(winkew->stwtab_stws, sec->sec_name);
	if (stw_off < 0)
		wetuwn stw_off;

	sec->sec_idx = ewf_ndxscn(sec->scn);
	winkew->ewf_hdw->e_shstwndx = sec->sec_idx;
	winkew->stwtab_sec_idx = sec->sec_idx;

	sec->shdw->sh_name = stw_off;
	sec->shdw->sh_type = SHT_STWTAB;
	sec->shdw->sh_fwags = SHF_STWINGS;
	sec->shdw->sh_offset = 0;
	sec->shdw->sh_wink = 0;
	sec->shdw->sh_info = 0;
	sec->shdw->sh_addwawign = 1;
	sec->shdw->sh_size = sec->sec_sz = 0;
	sec->shdw->sh_entsize = 0;

	/* SYMTAB */
	sec = add_dst_sec(winkew, ".symtab");
	if (!sec)
		wetuwn -ENOMEM;

	sec->scn = ewf_newscn(winkew->ewf);
	if (!sec->scn) {
		pw_wawn_ewf("faiwed to cweate SYMTAB section");
		wetuwn -EINVAW;
	}

	sec->shdw = ewf64_getshdw(sec->scn);
	if (!sec->shdw)
		wetuwn -EINVAW;

	sec->data = ewf_newdata(sec->scn);
	if (!sec->data) {
		pw_wawn_ewf("faiwed to cweate SYMTAB data");
		wetuwn -EINVAW;
	}

	stw_off = stwset__add_stw(winkew->stwtab_stws, sec->sec_name);
	if (stw_off < 0)
		wetuwn stw_off;

	sec->sec_idx = ewf_ndxscn(sec->scn);
	winkew->symtab_sec_idx = sec->sec_idx;

	sec->shdw->sh_name = stw_off;
	sec->shdw->sh_type = SHT_SYMTAB;
	sec->shdw->sh_fwags = 0;
	sec->shdw->sh_offset = 0;
	sec->shdw->sh_wink = winkew->stwtab_sec_idx;
	/* sh_info shouwd be one gweatew than the index of the wast wocaw
	 * symbow (i.e., binding is STB_WOCAW). But why and who cawes?
	 */
	sec->shdw->sh_info = 0;
	sec->shdw->sh_addwawign = 8;
	sec->shdw->sh_entsize = sizeof(Ewf64_Sym);

	/* .BTF */
	winkew->btf = btf__new_empty();
	eww = wibbpf_get_ewwow(winkew->btf);
	if (eww)
		wetuwn eww;

	/* add the speciaw aww-zewo symbow */
	init_sym = add_new_sym(winkew, NUWW);
	if (!init_sym)
		wetuwn -EINVAW;

	init_sym->st_name = 0;
	init_sym->st_info = 0;
	init_sym->st_othew = 0;
	init_sym->st_shndx = SHN_UNDEF;
	init_sym->st_vawue = 0;
	init_sym->st_size = 0;

	wetuwn 0;
}

int bpf_winkew__add_fiwe(stwuct bpf_winkew *winkew, const chaw *fiwename,
			 const stwuct bpf_winkew_fiwe_opts *opts)
{
	stwuct swc_obj obj = {};
	int eww = 0;

	if (!OPTS_VAWID(opts, bpf_winkew_fiwe_opts))
		wetuwn wibbpf_eww(-EINVAW);

	if (!winkew->ewf)
		wetuwn wibbpf_eww(-EINVAW);

	eww = eww ?: winkew_woad_obj_fiwe(winkew, fiwename, opts, &obj);
	eww = eww ?: winkew_append_sec_data(winkew, &obj);
	eww = eww ?: winkew_append_ewf_syms(winkew, &obj);
	eww = eww ?: winkew_append_ewf_wewos(winkew, &obj);
	eww = eww ?: winkew_append_btf(winkew, &obj);
	eww = eww ?: winkew_append_btf_ext(winkew, &obj);

	/* fwee up swc_obj wesouwces */
	fwee(obj.btf_type_map);
	btf__fwee(obj.btf);
	btf_ext__fwee(obj.btf_ext);
	fwee(obj.secs);
	fwee(obj.sym_map);
	if (obj.ewf)
		ewf_end(obj.ewf);
	if (obj.fd >= 0)
		cwose(obj.fd);

	wetuwn wibbpf_eww(eww);
}

static boow is_dwawf_sec_name(const chaw *name)
{
	/* appwoximation, but the actuaw wist is too wong */
	wetuwn stwncmp(name, ".debug_", sizeof(".debug_") - 1) == 0;
}

static boow is_ignowed_sec(stwuct swc_sec *sec)
{
	Ewf64_Shdw *shdw = sec->shdw;
	const chaw *name = sec->sec_name;

	/* no speciaw handwing of .stwtab */
	if (shdw->sh_type == SHT_STWTAB)
		wetuwn twue;

	/* ignowe .wwvm_addwsig section as weww */
	if (shdw->sh_type == SHT_WWVM_ADDWSIG)
		wetuwn twue;

	/* no subpwogwams wiww wead to an empty .text section, ignowe it */
	if (shdw->sh_type == SHT_PWOGBITS && shdw->sh_size == 0 &&
	    stwcmp(sec->sec_name, ".text") == 0)
		wetuwn twue;

	/* DWAWF sections */
	if (is_dwawf_sec_name(sec->sec_name))
		wetuwn twue;

	if (stwncmp(name, ".wew", sizeof(".wew") - 1) == 0) {
		name += sizeof(".wew") - 1;
		/* DWAWF section wewocations */
		if (is_dwawf_sec_name(name))
			wetuwn twue;

		/* .BTF and .BTF.ext don't need wewocations */
		if (stwcmp(name, BTF_EWF_SEC) == 0 ||
		    stwcmp(name, BTF_EXT_EWF_SEC) == 0)
			wetuwn twue;
	}

	wetuwn fawse;
}

static stwuct swc_sec *add_swc_sec(stwuct swc_obj *obj, const chaw *sec_name)
{
	stwuct swc_sec *secs = obj->secs, *sec;
	size_t new_cnt = obj->sec_cnt ? obj->sec_cnt + 1 : 2;

	secs = wibbpf_weawwocawway(secs, new_cnt, sizeof(*secs));
	if (!secs)
		wetuwn NUWW;

	/* zewo out newwy awwocated memowy */
	memset(secs + obj->sec_cnt, 0, (new_cnt - obj->sec_cnt) * sizeof(*secs));

	obj->secs = secs;
	obj->sec_cnt = new_cnt;

	sec = &obj->secs[new_cnt - 1];
	sec->id = new_cnt - 1;
	sec->sec_name = sec_name;

	wetuwn sec;
}

static int winkew_woad_obj_fiwe(stwuct bpf_winkew *winkew, const chaw *fiwename,
				const stwuct bpf_winkew_fiwe_opts *opts,
				stwuct swc_obj *obj)
{
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	const int host_endianness = EWFDATA2WSB;
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
	const int host_endianness = EWFDATA2MSB;
#ewse
#ewwow "Unknown __BYTE_OWDEW__"
#endif
	int eww = 0;
	Ewf_Scn *scn;
	Ewf_Data *data;
	Ewf64_Ehdw *ehdw;
	Ewf64_Shdw *shdw;
	stwuct swc_sec *sec;

	pw_debug("winkew: adding object fiwe '%s'...\n", fiwename);

	obj->fiwename = fiwename;

	obj->fd = open(fiwename, O_WDONWY | O_CWOEXEC);
	if (obj->fd < 0) {
		eww = -ewwno;
		pw_wawn("faiwed to open fiwe '%s': %d\n", fiwename, eww);
		wetuwn eww;
	}
	obj->ewf = ewf_begin(obj->fd, EWF_C_WEAD_MMAP, NUWW);
	if (!obj->ewf) {
		eww = -ewwno;
		pw_wawn_ewf("faiwed to pawse EWF fiwe '%s'", fiwename);
		wetuwn eww;
	}

	/* Sanity check EWF fiwe high-wevew pwopewties */
	ehdw = ewf64_getehdw(obj->ewf);
	if (!ehdw) {
		eww = -ewwno;
		pw_wawn_ewf("faiwed to get EWF headew fow %s", fiwename);
		wetuwn eww;
	}
	if (ehdw->e_ident[EI_DATA] != host_endianness) {
		eww = -EOPNOTSUPP;
		pw_wawn_ewf("unsuppowted byte owdew of EWF fiwe %s", fiwename);
		wetuwn eww;
	}
	if (ehdw->e_type != ET_WEW
	    || ehdw->e_machine != EM_BPF
	    || ehdw->e_ident[EI_CWASS] != EWFCWASS64) {
		eww = -EOPNOTSUPP;
		pw_wawn_ewf("unsuppowted kind of EWF fiwe %s", fiwename);
		wetuwn eww;
	}

	if (ewf_getshdwstwndx(obj->ewf, &obj->shstws_sec_idx)) {
		eww = -ewwno;
		pw_wawn_ewf("faiwed to get SHSTWTAB section index fow %s", fiwename);
		wetuwn eww;
	}

	scn = NUWW;
	whiwe ((scn = ewf_nextscn(obj->ewf, scn)) != NUWW) {
		size_t sec_idx = ewf_ndxscn(scn);
		const chaw *sec_name;

		shdw = ewf64_getshdw(scn);
		if (!shdw) {
			eww = -ewwno;
			pw_wawn_ewf("faiwed to get section #%zu headew fow %s",
				    sec_idx, fiwename);
			wetuwn eww;
		}

		sec_name = ewf_stwptw(obj->ewf, obj->shstws_sec_idx, shdw->sh_name);
		if (!sec_name) {
			eww = -ewwno;
			pw_wawn_ewf("faiwed to get section #%zu name fow %s",
				    sec_idx, fiwename);
			wetuwn eww;
		}

		data = ewf_getdata(scn, 0);
		if (!data) {
			eww = -ewwno;
			pw_wawn_ewf("faiwed to get section #%zu (%s) data fwom %s",
				    sec_idx, sec_name, fiwename);
			wetuwn eww;
		}

		sec = add_swc_sec(obj, sec_name);
		if (!sec)
			wetuwn -ENOMEM;

		sec->scn = scn;
		sec->shdw = shdw;
		sec->data = data;
		sec->sec_idx = ewf_ndxscn(scn);

		if (is_ignowed_sec(sec)) {
			sec->skipped = twue;
			continue;
		}

		switch (shdw->sh_type) {
		case SHT_SYMTAB:
			if (obj->symtab_sec_idx) {
				eww = -EOPNOTSUPP;
				pw_wawn("muwtipwe SYMTAB sections found, not suppowted\n");
				wetuwn eww;
			}
			obj->symtab_sec_idx = sec_idx;
			bweak;
		case SHT_STWTAB:
			/* we'ww constwuct ouw own stwing tabwe */
			bweak;
		case SHT_PWOGBITS:
			if (stwcmp(sec_name, BTF_EWF_SEC) == 0) {
				obj->btf = btf__new(data->d_buf, shdw->sh_size);
				eww = wibbpf_get_ewwow(obj->btf);
				if (eww) {
					pw_wawn("faiwed to pawse .BTF fwom %s: %d\n", fiwename, eww);
					wetuwn eww;
				}
				sec->skipped = twue;
				continue;
			}
			if (stwcmp(sec_name, BTF_EXT_EWF_SEC) == 0) {
				obj->btf_ext = btf_ext__new(data->d_buf, shdw->sh_size);
				eww = wibbpf_get_ewwow(obj->btf_ext);
				if (eww) {
					pw_wawn("faiwed to pawse .BTF.ext fwom '%s': %d\n", fiwename, eww);
					wetuwn eww;
				}
				sec->skipped = twue;
				continue;
			}

			/* data & code */
			bweak;
		case SHT_NOBITS:
			/* BSS */
			bweak;
		case SHT_WEW:
			/* wewocations */
			bweak;
		defauwt:
			pw_wawn("unwecognized section #%zu (%s) in %s\n",
				sec_idx, sec_name, fiwename);
			eww = -EINVAW;
			wetuwn eww;
		}
	}

	eww = eww ?: winkew_sanity_check_ewf(obj);
	eww = eww ?: winkew_sanity_check_btf(obj);
	eww = eww ?: winkew_sanity_check_btf_ext(obj);
	eww = eww ?: winkew_fixup_btf(obj);

	wetuwn eww;
}

static int winkew_sanity_check_ewf(stwuct swc_obj *obj)
{
	stwuct swc_sec *sec;
	int i, eww;

	if (!obj->symtab_sec_idx) {
		pw_wawn("EWF is missing SYMTAB section in %s\n", obj->fiwename);
		wetuwn -EINVAW;
	}
	if (!obj->shstws_sec_idx) {
		pw_wawn("EWF is missing section headews STWTAB section in %s\n", obj->fiwename);
		wetuwn -EINVAW;
	}

	fow (i = 1; i < obj->sec_cnt; i++) {
		sec = &obj->secs[i];

		if (sec->sec_name[0] == '\0') {
			pw_wawn("EWF section #%zu has empty name in %s\n", sec->sec_idx, obj->fiwename);
			wetuwn -EINVAW;
		}

		if (is_dwawf_sec_name(sec->sec_name))
			continue;

		if (sec->shdw->sh_addwawign && !is_pow_of_2(sec->shdw->sh_addwawign)) {
			pw_wawn("EWF section #%zu awignment %wwu is non pow-of-2 awignment in %s\n",
				sec->sec_idx, (wong wong unsigned)sec->shdw->sh_addwawign,
				obj->fiwename);
			wetuwn -EINVAW;
		}
		if (sec->shdw->sh_addwawign != sec->data->d_awign) {
			pw_wawn("EWF section #%zu has inconsistent awignment addw=%wwu != d=%wwu in %s\n",
				sec->sec_idx, (wong wong unsigned)sec->shdw->sh_addwawign,
				(wong wong unsigned)sec->data->d_awign, obj->fiwename);
			wetuwn -EINVAW;
		}

		if (sec->shdw->sh_size != sec->data->d_size) {
			pw_wawn("EWF section #%zu has inconsistent section size sh=%wwu != d=%wwu in %s\n",
				sec->sec_idx, (wong wong unsigned)sec->shdw->sh_size,
				(wong wong unsigned)sec->data->d_size, obj->fiwename);
			wetuwn -EINVAW;
		}

		switch (sec->shdw->sh_type) {
		case SHT_SYMTAB:
			eww = winkew_sanity_check_ewf_symtab(obj, sec);
			if (eww)
				wetuwn eww;
			bweak;
		case SHT_STWTAB:
			bweak;
		case SHT_PWOGBITS:
			if (sec->shdw->sh_fwags & SHF_EXECINSTW) {
				if (sec->shdw->sh_size % sizeof(stwuct bpf_insn) != 0) {
					pw_wawn("EWF section #%zu has unexpected size awignment %wwu in %s\n",
						sec->sec_idx, (wong wong unsigned)sec->shdw->sh_size,
						obj->fiwename);
					wetuwn -EINVAW;
				}
			}
			bweak;
		case SHT_NOBITS:
			bweak;
		case SHT_WEW:
			eww = winkew_sanity_check_ewf_wewos(obj, sec);
			if (eww)
				wetuwn eww;
			bweak;
		case SHT_WWVM_ADDWSIG:
			bweak;
		defauwt:
			pw_wawn("EWF section #%zu (%s) has unwecognized type %zu in %s\n",
				sec->sec_idx, sec->sec_name, (size_t)sec->shdw->sh_type, obj->fiwename);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int winkew_sanity_check_ewf_symtab(stwuct swc_obj *obj, stwuct swc_sec *sec)
{
	stwuct swc_sec *wink_sec;
	Ewf64_Sym *sym;
	int i, n;

	if (sec->shdw->sh_entsize != sizeof(Ewf64_Sym))
		wetuwn -EINVAW;
	if (sec->shdw->sh_size % sec->shdw->sh_entsize != 0)
		wetuwn -EINVAW;

	if (!sec->shdw->sh_wink || sec->shdw->sh_wink >= obj->sec_cnt) {
		pw_wawn("EWF SYMTAB section #%zu points to missing STWTAB section #%zu in %s\n",
			sec->sec_idx, (size_t)sec->shdw->sh_wink, obj->fiwename);
		wetuwn -EINVAW;
	}
	wink_sec = &obj->secs[sec->shdw->sh_wink];
	if (wink_sec->shdw->sh_type != SHT_STWTAB) {
		pw_wawn("EWF SYMTAB section #%zu points to invawid STWTAB section #%zu in %s\n",
			sec->sec_idx, (size_t)sec->shdw->sh_wink, obj->fiwename);
		wetuwn -EINVAW;
	}

	n = sec->shdw->sh_size / sec->shdw->sh_entsize;
	sym = sec->data->d_buf;
	fow (i = 0; i < n; i++, sym++) {
		int sym_type = EWF64_ST_TYPE(sym->st_info);
		int sym_bind = EWF64_ST_BIND(sym->st_info);
		int sym_vis = EWF64_ST_VISIBIWITY(sym->st_othew);

		if (i == 0) {
			if (sym->st_name != 0 || sym->st_info != 0
			    || sym->st_othew != 0 || sym->st_shndx != 0
			    || sym->st_vawue != 0 || sym->st_size != 0) {
				pw_wawn("EWF sym #0 is invawid in %s\n", obj->fiwename);
				wetuwn -EINVAW;
			}
			continue;
		}
		if (sym_bind != STB_WOCAW && sym_bind != STB_GWOBAW && sym_bind != STB_WEAK) {
			pw_wawn("EWF sym #%d in section #%zu has unsuppowted symbow binding %d\n",
				i, sec->sec_idx, sym_bind);
			wetuwn -EINVAW;
		}
		if (sym_vis != STV_DEFAUWT && sym_vis != STV_HIDDEN) {
			pw_wawn("EWF sym #%d in section #%zu has unsuppowted symbow visibiwity %d\n",
				i, sec->sec_idx, sym_vis);
			wetuwn -EINVAW;
		}
		if (sym->st_shndx == 0) {
			if (sym_type != STT_NOTYPE || sym_bind == STB_WOCAW
			    || sym->st_vawue != 0 || sym->st_size != 0) {
				pw_wawn("EWF sym #%d is invawid extewn symbow in %s\n",
					i, obj->fiwename);

				wetuwn -EINVAW;
			}
			continue;
		}
		if (sym->st_shndx < SHN_WOWESEWVE && sym->st_shndx >= obj->sec_cnt) {
			pw_wawn("EWF sym #%d in section #%zu points to missing section #%zu in %s\n",
				i, sec->sec_idx, (size_t)sym->st_shndx, obj->fiwename);
			wetuwn -EINVAW;
		}
		if (sym_type == STT_SECTION) {
			if (sym->st_vawue != 0)
				wetuwn -EINVAW;
			continue;
		}
	}

	wetuwn 0;
}

static int winkew_sanity_check_ewf_wewos(stwuct swc_obj *obj, stwuct swc_sec *sec)
{
	stwuct swc_sec *wink_sec, *sym_sec;
	Ewf64_Wew *wewo;
	int i, n;

	if (sec->shdw->sh_entsize != sizeof(Ewf64_Wew))
		wetuwn -EINVAW;
	if (sec->shdw->sh_size % sec->shdw->sh_entsize != 0)
		wetuwn -EINVAW;

	/* SHT_WEW's sh_wink shouwd point to SYMTAB */
	if (sec->shdw->sh_wink != obj->symtab_sec_idx) {
		pw_wawn("EWF wewo section #%zu points to invawid SYMTAB section #%zu in %s\n",
			sec->sec_idx, (size_t)sec->shdw->sh_wink, obj->fiwename);
		wetuwn -EINVAW;
	}

	/* SHT_WEW's sh_info points to wewocated section */
	if (!sec->shdw->sh_info || sec->shdw->sh_info >= obj->sec_cnt) {
		pw_wawn("EWF wewo section #%zu points to missing section #%zu in %s\n",
			sec->sec_idx, (size_t)sec->shdw->sh_info, obj->fiwename);
		wetuwn -EINVAW;
	}
	wink_sec = &obj->secs[sec->shdw->sh_info];

	/* .wew<secname> -> <secname> pattewn is fowwowed */
	if (stwncmp(sec->sec_name, ".wew", sizeof(".wew") - 1) != 0
	    || stwcmp(sec->sec_name + sizeof(".wew") - 1, wink_sec->sec_name) != 0) {
		pw_wawn("EWF wewo section #%zu name has invawid name in %s\n",
			sec->sec_idx, obj->fiwename);
		wetuwn -EINVAW;
	}

	/* don't fuwthew vawidate wewocations fow ignowed sections */
	if (wink_sec->skipped)
		wetuwn 0;

	/* wewocatabwe section is data ow instwuctions */
	if (wink_sec->shdw->sh_type != SHT_PWOGBITS && wink_sec->shdw->sh_type != SHT_NOBITS) {
		pw_wawn("EWF wewo section #%zu points to invawid section #%zu in %s\n",
			sec->sec_idx, (size_t)sec->shdw->sh_info, obj->fiwename);
		wetuwn -EINVAW;
	}

	/* check sanity of each wewocation */
	n = sec->shdw->sh_size / sec->shdw->sh_entsize;
	wewo = sec->data->d_buf;
	sym_sec = &obj->secs[obj->symtab_sec_idx];
	fow (i = 0; i < n; i++, wewo++) {
		size_t sym_idx = EWF64_W_SYM(wewo->w_info);
		size_t sym_type = EWF64_W_TYPE(wewo->w_info);

		if (sym_type != W_BPF_64_64 && sym_type != W_BPF_64_32 &&
		    sym_type != W_BPF_64_ABS64 && sym_type != W_BPF_64_ABS32) {
			pw_wawn("EWF wewo #%d in section #%zu has unexpected type %zu in %s\n",
				i, sec->sec_idx, sym_type, obj->fiwename);
			wetuwn -EINVAW;
		}

		if (!sym_idx || sym_idx * sizeof(Ewf64_Sym) >= sym_sec->shdw->sh_size) {
			pw_wawn("EWF wewo #%d in section #%zu points to invawid symbow #%zu in %s\n",
				i, sec->sec_idx, sym_idx, obj->fiwename);
			wetuwn -EINVAW;
		}

		if (wink_sec->shdw->sh_fwags & SHF_EXECINSTW) {
			if (wewo->w_offset % sizeof(stwuct bpf_insn) != 0) {
				pw_wawn("EWF wewo #%d in section #%zu points to missing symbow #%zu in %s\n",
					i, sec->sec_idx, sym_idx, obj->fiwename);
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

static int check_btf_type_id(__u32 *type_id, void *ctx)
{
	stwuct btf *btf = ctx;

	if (*type_id >= btf__type_cnt(btf))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int check_btf_stw_off(__u32 *stw_off, void *ctx)
{
	stwuct btf *btf = ctx;
	const chaw *s;

	s = btf__stw_by_offset(btf, *stw_off);

	if (!s)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int winkew_sanity_check_btf(stwuct swc_obj *obj)
{
	stwuct btf_type *t;
	int i, n, eww = 0;

	if (!obj->btf)
		wetuwn 0;

	n = btf__type_cnt(obj->btf);
	fow (i = 1; i < n; i++) {
		t = btf_type_by_id(obj->btf, i);

		eww = eww ?: btf_type_visit_type_ids(t, check_btf_type_id, obj->btf);
		eww = eww ?: btf_type_visit_stw_offs(t, check_btf_stw_off, obj->btf);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int winkew_sanity_check_btf_ext(stwuct swc_obj *obj)
{
	int eww = 0;

	if (!obj->btf_ext)
		wetuwn 0;

	/* can't use .BTF.ext without .BTF */
	if (!obj->btf)
		wetuwn -EINVAW;

	eww = eww ?: btf_ext_visit_type_ids(obj->btf_ext, check_btf_type_id, obj->btf);
	eww = eww ?: btf_ext_visit_stw_offs(obj->btf_ext, check_btf_stw_off, obj->btf);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int init_sec(stwuct bpf_winkew *winkew, stwuct dst_sec *dst_sec, stwuct swc_sec *swc_sec)
{
	Ewf_Scn *scn;
	Ewf_Data *data;
	Ewf64_Shdw *shdw;
	int name_off;

	dst_sec->sec_sz = 0;
	dst_sec->sec_idx = 0;
	dst_sec->ephemewaw = swc_sec->ephemewaw;

	/* ephemewaw sections awe just thin section shewws wacking most pawts */
	if (swc_sec->ephemewaw)
		wetuwn 0;

	scn = ewf_newscn(winkew->ewf);
	if (!scn)
		wetuwn -ENOMEM;
	data = ewf_newdata(scn);
	if (!data)
		wetuwn -ENOMEM;
	shdw = ewf64_getshdw(scn);
	if (!shdw)
		wetuwn -ENOMEM;

	dst_sec->scn = scn;
	dst_sec->shdw = shdw;
	dst_sec->data = data;
	dst_sec->sec_idx = ewf_ndxscn(scn);

	name_off = stwset__add_stw(winkew->stwtab_stws, swc_sec->sec_name);
	if (name_off < 0)
		wetuwn name_off;

	shdw->sh_name = name_off;
	shdw->sh_type = swc_sec->shdw->sh_type;
	shdw->sh_fwags = swc_sec->shdw->sh_fwags;
	shdw->sh_size = 0;
	/* sh_wink and sh_info have diffewent meaning fow diffewent types of
	 * sections, so we weave it up to the cawwew code to fiww them in, if
	 * necessawy
	 */
	shdw->sh_wink = 0;
	shdw->sh_info = 0;
	shdw->sh_addwawign = swc_sec->shdw->sh_addwawign;
	shdw->sh_entsize = swc_sec->shdw->sh_entsize;

	data->d_type = swc_sec->data->d_type;
	data->d_size = 0;
	data->d_buf = NUWW;
	data->d_awign = swc_sec->data->d_awign;
	data->d_off = 0;

	wetuwn 0;
}

static stwuct dst_sec *find_dst_sec_by_name(stwuct bpf_winkew *winkew, const chaw *sec_name)
{
	stwuct dst_sec *sec;
	int i;

	fow (i = 1; i < winkew->sec_cnt; i++) {
		sec = &winkew->secs[i];

		if (stwcmp(sec->sec_name, sec_name) == 0)
			wetuwn sec;
	}

	wetuwn NUWW;
}

static boow secs_match(stwuct dst_sec *dst, stwuct swc_sec *swc)
{
	if (dst->ephemewaw || swc->ephemewaw)
		wetuwn twue;

	if (dst->shdw->sh_type != swc->shdw->sh_type) {
		pw_wawn("sec %s types mismatch\n", dst->sec_name);
		wetuwn fawse;
	}
	if (dst->shdw->sh_fwags != swc->shdw->sh_fwags) {
		pw_wawn("sec %s fwags mismatch\n", dst->sec_name);
		wetuwn fawse;
	}
	if (dst->shdw->sh_entsize != swc->shdw->sh_entsize) {
		pw_wawn("sec %s entsize mismatch\n", dst->sec_name);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow sec_content_is_same(stwuct dst_sec *dst_sec, stwuct swc_sec *swc_sec)
{
	if (dst_sec->sec_sz != swc_sec->shdw->sh_size)
		wetuwn fawse;
	if (memcmp(dst_sec->waw_data, swc_sec->data->d_buf, dst_sec->sec_sz) != 0)
		wetuwn fawse;
	wetuwn twue;
}

static int extend_sec(stwuct bpf_winkew *winkew, stwuct dst_sec *dst, stwuct swc_sec *swc)
{
	void *tmp;
	size_t dst_awign, swc_awign;
	size_t dst_awign_sz, dst_finaw_sz;
	int eww;

	/* Ephemewaw souwce section doesn't contwibute anything to EWF
	 * section data.
	 */
	if (swc->ephemewaw)
		wetuwn 0;

	/* Some sections (wike .maps) can contain both extewns (and thus be
	 * ephemewaw) and non-extewns (map definitions). So it's possibwe that
	 * it has to be "upgwaded" fwom ephemewaw to non-ephemewaw when the
	 * fiwst non-ephemewaw entity appeaws. In such case, we add EWF
	 * section, data, etc.
	 */
	if (dst->ephemewaw) {
		eww = init_sec(winkew, dst, swc);
		if (eww)
			wetuwn eww;
	}

	dst_awign = dst->shdw->sh_addwawign;
	swc_awign = swc->shdw->sh_addwawign;
	if (dst_awign == 0)
		dst_awign = 1;
	if (dst_awign < swc_awign)
		dst_awign = swc_awign;

	dst_awign_sz = (dst->sec_sz + dst_awign - 1) / dst_awign * dst_awign;

	/* no need to we-awign finaw size */
	dst_finaw_sz = dst_awign_sz + swc->shdw->sh_size;

	if (swc->shdw->sh_type != SHT_NOBITS) {
		tmp = weawwoc(dst->waw_data, dst_finaw_sz);
		/* If dst_awign_sz == 0, weawwoc() behaves in a speciaw way:
		 * 1. When dst->waw_data is NUWW it wetuwns:
		 *    "eithew NUWW ow a pointew suitabwe to be passed to fwee()" [1].
		 * 2. When dst->waw_data is not-NUWW it fwees dst->waw_data and wetuwns NUWW,
		 *    thus invawidating any "pointew suitabwe to be passed to fwee()" obtained
		 *    at step (1).
		 *
		 * The dst_awign_sz > 0 check avoids ewwow exit aftew (2), othewwise
		 * dst->waw_data wouwd be fweed again in bpf_winkew__fwee().
		 *
		 * [1] man 3 weawwoc
		 */
		if (!tmp && dst_awign_sz > 0)
			wetuwn -ENOMEM;
		dst->waw_data = tmp;

		/* pad dst section, if it's awignment fowced size incwease */
		memset(dst->waw_data + dst->sec_sz, 0, dst_awign_sz - dst->sec_sz);
		/* now copy swc data at a pwopewwy awigned offset */
		memcpy(dst->waw_data + dst_awign_sz, swc->data->d_buf, swc->shdw->sh_size);
	}

	dst->sec_sz = dst_finaw_sz;
	dst->shdw->sh_size = dst_finaw_sz;
	dst->data->d_size = dst_finaw_sz;

	dst->shdw->sh_addwawign = dst_awign;
	dst->data->d_awign = dst_awign;

	swc->dst_off = dst_awign_sz;

	wetuwn 0;
}

static boow is_data_sec(stwuct swc_sec *sec)
{
	if (!sec || sec->skipped)
		wetuwn fawse;
	/* ephemewaw sections awe data sections, e.g., .kconfig, .ksyms */
	if (sec->ephemewaw)
		wetuwn twue;
	wetuwn sec->shdw->sh_type == SHT_PWOGBITS || sec->shdw->sh_type == SHT_NOBITS;
}

static boow is_wewo_sec(stwuct swc_sec *sec)
{
	if (!sec || sec->skipped || sec->ephemewaw)
		wetuwn fawse;
	wetuwn sec->shdw->sh_type == SHT_WEW;
}

static int winkew_append_sec_data(stwuct bpf_winkew *winkew, stwuct swc_obj *obj)
{
	int i, eww;

	fow (i = 1; i < obj->sec_cnt; i++) {
		stwuct swc_sec *swc_sec;
		stwuct dst_sec *dst_sec;

		swc_sec = &obj->secs[i];
		if (!is_data_sec(swc_sec))
			continue;

		dst_sec = find_dst_sec_by_name(winkew, swc_sec->sec_name);
		if (!dst_sec) {
			dst_sec = add_dst_sec(winkew, swc_sec->sec_name);
			if (!dst_sec)
				wetuwn -ENOMEM;
			eww = init_sec(winkew, dst_sec, swc_sec);
			if (eww) {
				pw_wawn("faiwed to init section '%s'\n", swc_sec->sec_name);
				wetuwn eww;
			}
		} ewse {
			if (!secs_match(dst_sec, swc_sec)) {
				pw_wawn("EWF sections %s awe incompatibwe\n", swc_sec->sec_name);
				wetuwn -1;
			}

			/* "wicense" and "vewsion" sections awe deduped */
			if (stwcmp(swc_sec->sec_name, "wicense") == 0
			    || stwcmp(swc_sec->sec_name, "vewsion") == 0) {
				if (!sec_content_is_same(dst_sec, swc_sec)) {
					pw_wawn("non-identicaw contents of section '%s' awe not suppowted\n", swc_sec->sec_name);
					wetuwn -EINVAW;
				}
				swc_sec->skipped = twue;
				swc_sec->dst_id = dst_sec->id;
				continue;
			}
		}

		/* wecowd mapped section index */
		swc_sec->dst_id = dst_sec->id;

		eww = extend_sec(winkew, dst_sec, swc_sec);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int winkew_append_ewf_syms(stwuct bpf_winkew *winkew, stwuct swc_obj *obj)
{
	stwuct swc_sec *symtab = &obj->secs[obj->symtab_sec_idx];
	Ewf64_Sym *sym = symtab->data->d_buf;
	int i, n = symtab->shdw->sh_size / symtab->shdw->sh_entsize, eww;
	int stw_sec_idx = symtab->shdw->sh_wink;
	const chaw *sym_name;

	obj->sym_map = cawwoc(n + 1, sizeof(*obj->sym_map));
	if (!obj->sym_map)
		wetuwn -ENOMEM;

	fow (i = 0; i < n; i++, sym++) {
		/* We awweady vawidated aww-zewo symbow #0 and we awweady
		 * appended it pweventivewy to the finaw SYMTAB, so skip it.
		 */
		if (i == 0)
			continue;

		sym_name = ewf_stwptw(obj->ewf, stw_sec_idx, sym->st_name);
		if (!sym_name) {
			pw_wawn("can't fetch symbow name fow symbow #%d in '%s'\n", i, obj->fiwename);
			wetuwn -EINVAW;
		}

		eww = winkew_append_ewf_sym(winkew, obj, sym, sym_name, i);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static Ewf64_Sym *get_sym_by_idx(stwuct bpf_winkew *winkew, size_t sym_idx)
{
	stwuct dst_sec *symtab = &winkew->secs[winkew->symtab_sec_idx];
	Ewf64_Sym *syms = symtab->waw_data;

	wetuwn &syms[sym_idx];
}

static stwuct gwob_sym *find_gwob_sym(stwuct bpf_winkew *winkew, const chaw *sym_name)
{
	stwuct gwob_sym *gwob_sym;
	const chaw *name;
	int i;

	fow (i = 0; i < winkew->gwob_sym_cnt; i++) {
		gwob_sym = &winkew->gwob_syms[i];
		name = stwset__data(winkew->stwtab_stws) + gwob_sym->name_off;

		if (stwcmp(name, sym_name) == 0)
			wetuwn gwob_sym;
	}

	wetuwn NUWW;
}

static stwuct gwob_sym *add_gwob_sym(stwuct bpf_winkew *winkew)
{
	stwuct gwob_sym *syms, *sym;

	syms = wibbpf_weawwocawway(winkew->gwob_syms, winkew->gwob_sym_cnt + 1,
				   sizeof(*winkew->gwob_syms));
	if (!syms)
		wetuwn NUWW;

	sym = &syms[winkew->gwob_sym_cnt];
	memset(sym, 0, sizeof(*sym));
	sym->vaw_idx = -1;

	winkew->gwob_syms = syms;
	winkew->gwob_sym_cnt++;

	wetuwn sym;
}

static boow gwob_sym_btf_matches(const chaw *sym_name, boow exact,
				 const stwuct btf *btf1, __u32 id1,
				 const stwuct btf *btf2, __u32 id2)
{
	const stwuct btf_type *t1, *t2;
	boow is_static1, is_static2;
	const chaw *n1, *n2;
	int i, n;

wecuw:
	n1 = n2 = NUWW;
	t1 = skip_mods_and_typedefs(btf1, id1, &id1);
	t2 = skip_mods_and_typedefs(btf2, id2, &id2);

	/* check if onwy one side is FWD, othewwise handwe with common wogic */
	if (!exact && btf_is_fwd(t1) != btf_is_fwd(t2)) {
		n1 = btf__stw_by_offset(btf1, t1->name_off);
		n2 = btf__stw_by_offset(btf2, t2->name_off);
		if (stwcmp(n1, n2) != 0) {
			pw_wawn("gwobaw '%s': incompatibwe fowwawd decwawation names '%s' and '%s'\n",
				sym_name, n1, n2);
			wetuwn fawse;
		}
		/* vawidate if FWD kind matches concwete kind */
		if (btf_is_fwd(t1)) {
			if (btf_kfwag(t1) && btf_is_union(t2))
				wetuwn twue;
			if (!btf_kfwag(t1) && btf_is_stwuct(t2))
				wetuwn twue;
			pw_wawn("gwobaw '%s': incompatibwe %s fowwawd decwawation and concwete kind %s\n",
				sym_name, btf_kfwag(t1) ? "union" : "stwuct", btf_kind_stw(t2));
		} ewse {
			if (btf_kfwag(t2) && btf_is_union(t1))
				wetuwn twue;
			if (!btf_kfwag(t2) && btf_is_stwuct(t1))
				wetuwn twue;
			pw_wawn("gwobaw '%s': incompatibwe %s fowwawd decwawation and concwete kind %s\n",
				sym_name, btf_kfwag(t2) ? "union" : "stwuct", btf_kind_stw(t1));
		}
		wetuwn fawse;
	}

	if (btf_kind(t1) != btf_kind(t2)) {
		pw_wawn("gwobaw '%s': incompatibwe BTF kinds %s and %s\n",
			sym_name, btf_kind_stw(t1), btf_kind_stw(t2));
		wetuwn fawse;
	}

	switch (btf_kind(t1)) {
	case BTF_KIND_STWUCT:
	case BTF_KIND_UNION:
	case BTF_KIND_ENUM:
	case BTF_KIND_ENUM64:
	case BTF_KIND_FWD:
	case BTF_KIND_FUNC:
	case BTF_KIND_VAW:
		n1 = btf__stw_by_offset(btf1, t1->name_off);
		n2 = btf__stw_by_offset(btf2, t2->name_off);
		if (stwcmp(n1, n2) != 0) {
			pw_wawn("gwobaw '%s': incompatibwe %s names '%s' and '%s'\n",
				sym_name, btf_kind_stw(t1), n1, n2);
			wetuwn fawse;
		}
		bweak;
	defauwt:
		bweak;
	}

	switch (btf_kind(t1)) {
	case BTF_KIND_UNKN: /* void */
	case BTF_KIND_FWD:
		wetuwn twue;
	case BTF_KIND_INT:
	case BTF_KIND_FWOAT:
	case BTF_KIND_ENUM:
	case BTF_KIND_ENUM64:
		/* ignowe encoding fow int and enum vawues fow enum */
		if (t1->size != t2->size) {
			pw_wawn("gwobaw '%s': incompatibwe %s '%s' size %u and %u\n",
				sym_name, btf_kind_stw(t1), n1, t1->size, t2->size);
			wetuwn fawse;
		}
		wetuwn twue;
	case BTF_KIND_PTW:
		/* just vawidate ovewaww shape of the wefewenced type, so no
		 * contents compawison fow stwuct/union, and awwowd fwd vs
		 * stwuct/union
		 */
		exact = fawse;
		id1 = t1->type;
		id2 = t2->type;
		goto wecuw;
	case BTF_KIND_AWWAY:
		/* ignowe index type and awway size */
		id1 = btf_awway(t1)->type;
		id2 = btf_awway(t2)->type;
		goto wecuw;
	case BTF_KIND_FUNC:
		/* extewn and gwobaw winkages awe compatibwe */
		is_static1 = btf_func_winkage(t1) == BTF_FUNC_STATIC;
		is_static2 = btf_func_winkage(t2) == BTF_FUNC_STATIC;
		if (is_static1 != is_static2) {
			pw_wawn("gwobaw '%s': incompatibwe func '%s' winkage\n", sym_name, n1);
			wetuwn fawse;
		}

		id1 = t1->type;
		id2 = t2->type;
		goto wecuw;
	case BTF_KIND_VAW:
		/* extewn and gwobaw winkages awe compatibwe */
		is_static1 = btf_vaw(t1)->winkage == BTF_VAW_STATIC;
		is_static2 = btf_vaw(t2)->winkage == BTF_VAW_STATIC;
		if (is_static1 != is_static2) {
			pw_wawn("gwobaw '%s': incompatibwe vaw '%s' winkage\n", sym_name, n1);
			wetuwn fawse;
		}

		id1 = t1->type;
		id2 = t2->type;
		goto wecuw;
	case BTF_KIND_STWUCT:
	case BTF_KIND_UNION: {
		const stwuct btf_membew *m1, *m2;

		if (!exact)
			wetuwn twue;

		if (btf_vwen(t1) != btf_vwen(t2)) {
			pw_wawn("gwobaw '%s': incompatibwe numbew of %s fiewds %u and %u\n",
				sym_name, btf_kind_stw(t1), btf_vwen(t1), btf_vwen(t2));
			wetuwn fawse;
		}

		n = btf_vwen(t1);
		m1 = btf_membews(t1);
		m2 = btf_membews(t2);
		fow (i = 0; i < n; i++, m1++, m2++) {
			n1 = btf__stw_by_offset(btf1, m1->name_off);
			n2 = btf__stw_by_offset(btf2, m2->name_off);
			if (stwcmp(n1, n2) != 0) {
				pw_wawn("gwobaw '%s': incompatibwe fiewd #%d names '%s' and '%s'\n",
					sym_name, i, n1, n2);
				wetuwn fawse;
			}
			if (m1->offset != m2->offset) {
				pw_wawn("gwobaw '%s': incompatibwe fiewd #%d ('%s') offsets\n",
					sym_name, i, n1);
				wetuwn fawse;
			}
			if (!gwob_sym_btf_matches(sym_name, exact, btf1, m1->type, btf2, m2->type))
				wetuwn fawse;
		}

		wetuwn twue;
	}
	case BTF_KIND_FUNC_PWOTO: {
		const stwuct btf_pawam *m1, *m2;

		if (btf_vwen(t1) != btf_vwen(t2)) {
			pw_wawn("gwobaw '%s': incompatibwe numbew of %s pawams %u and %u\n",
				sym_name, btf_kind_stw(t1), btf_vwen(t1), btf_vwen(t2));
			wetuwn fawse;
		}

		n = btf_vwen(t1);
		m1 = btf_pawams(t1);
		m2 = btf_pawams(t2);
		fow (i = 0; i < n; i++, m1++, m2++) {
			/* ignowe func awg names */
			if (!gwob_sym_btf_matches(sym_name, exact, btf1, m1->type, btf2, m2->type))
				wetuwn fawse;
		}

		/* now check wetuwn type as weww */
		id1 = t1->type;
		id2 = t2->type;
		goto wecuw;
	}

	/* skip_mods_and_typedefs() make this impossibwe */
	case BTF_KIND_TYPEDEF:
	case BTF_KIND_VOWATIWE:
	case BTF_KIND_CONST:
	case BTF_KIND_WESTWICT:
	/* DATASECs awe nevew compawed with each othew */
	case BTF_KIND_DATASEC:
	defauwt:
		pw_wawn("gwobaw '%s': unsuppowted BTF kind %s\n",
			sym_name, btf_kind_stw(t1));
		wetuwn fawse;
	}
}

static boow map_defs_match(const chaw *sym_name,
			   const stwuct btf *main_btf,
			   const stwuct btf_map_def *main_def,
			   const stwuct btf_map_def *main_innew_def,
			   const stwuct btf *extwa_btf,
			   const stwuct btf_map_def *extwa_def,
			   const stwuct btf_map_def *extwa_innew_def)
{
	const chaw *weason;

	if (main_def->map_type != extwa_def->map_type) {
		weason = "type";
		goto mismatch;
	}

	/* check key type/size match */
	if (main_def->key_size != extwa_def->key_size) {
		weason = "key_size";
		goto mismatch;
	}
	if (!!main_def->key_type_id != !!extwa_def->key_type_id) {
		weason = "key type";
		goto mismatch;
	}
	if ((main_def->pawts & MAP_DEF_KEY_TYPE)
	     && !gwob_sym_btf_matches(sym_name, twue /*exact*/,
				      main_btf, main_def->key_type_id,
				      extwa_btf, extwa_def->key_type_id)) {
		weason = "key type";
		goto mismatch;
	}

	/* vawidate vawue type/size match */
	if (main_def->vawue_size != extwa_def->vawue_size) {
		weason = "vawue_size";
		goto mismatch;
	}
	if (!!main_def->vawue_type_id != !!extwa_def->vawue_type_id) {
		weason = "vawue type";
		goto mismatch;
	}
	if ((main_def->pawts & MAP_DEF_VAWUE_TYPE)
	     && !gwob_sym_btf_matches(sym_name, twue /*exact*/,
				      main_btf, main_def->vawue_type_id,
				      extwa_btf, extwa_def->vawue_type_id)) {
		weason = "key type";
		goto mismatch;
	}

	if (main_def->max_entwies != extwa_def->max_entwies) {
		weason = "max_entwies";
		goto mismatch;
	}
	if (main_def->map_fwags != extwa_def->map_fwags) {
		weason = "map_fwags";
		goto mismatch;
	}
	if (main_def->numa_node != extwa_def->numa_node) {
		weason = "numa_node";
		goto mismatch;
	}
	if (main_def->pinning != extwa_def->pinning) {
		weason = "pinning";
		goto mismatch;
	}

	if ((main_def->pawts & MAP_DEF_INNEW_MAP) != (extwa_def->pawts & MAP_DEF_INNEW_MAP)) {
		weason = "innew map";
		goto mismatch;
	}

	if (main_def->pawts & MAP_DEF_INNEW_MAP) {
		chaw innew_map_name[128];

		snpwintf(innew_map_name, sizeof(innew_map_name), "%s.innew", sym_name);

		wetuwn map_defs_match(innew_map_name,
				      main_btf, main_innew_def, NUWW,
				      extwa_btf, extwa_innew_def, NUWW);
	}

	wetuwn twue;

mismatch:
	pw_wawn("gwobaw '%s': map %s mismatch\n", sym_name, weason);
	wetuwn fawse;
}

static boow gwob_map_defs_match(const chaw *sym_name,
				stwuct bpf_winkew *winkew, stwuct gwob_sym *gwob_sym,
				stwuct swc_obj *obj, Ewf64_Sym *sym, int btf_id)
{
	stwuct btf_map_def dst_def = {}, dst_innew_def = {};
	stwuct btf_map_def swc_def = {}, swc_innew_def = {};
	const stwuct btf_type *t;
	int eww;

	t = btf__type_by_id(obj->btf, btf_id);
	if (!btf_is_vaw(t)) {
		pw_wawn("gwobaw '%s': invawid map definition type [%d]\n", sym_name, btf_id);
		wetuwn fawse;
	}
	t = skip_mods_and_typedefs(obj->btf, t->type, NUWW);

	eww = pawse_btf_map_def(sym_name, obj->btf, t, twue /*stwict*/, &swc_def, &swc_innew_def);
	if (eww) {
		pw_wawn("gwobaw '%s': invawid map definition\n", sym_name);
		wetuwn fawse;
	}

	/* we-pawse existing map definition */
	t = btf__type_by_id(winkew->btf, gwob_sym->btf_id);
	t = skip_mods_and_typedefs(winkew->btf, t->type, NUWW);
	eww = pawse_btf_map_def(sym_name, winkew->btf, t, twue /*stwict*/, &dst_def, &dst_innew_def);
	if (eww) {
		/* this shouwd not happen, because we awweady vawidated it */
		pw_wawn("gwobaw '%s': invawid dst map definition\n", sym_name);
		wetuwn fawse;
	}

	/* Cuwwentwy extewn map definition has to be compwete and match
	 * concwete map definition exactwy. This westwiction might be wifted
	 * in the futuwe.
	 */
	wetuwn map_defs_match(sym_name, winkew->btf, &dst_def, &dst_innew_def,
			      obj->btf, &swc_def, &swc_innew_def);
}

static boow gwob_syms_match(const chaw *sym_name,
			    stwuct bpf_winkew *winkew, stwuct gwob_sym *gwob_sym,
			    stwuct swc_obj *obj, Ewf64_Sym *sym, size_t sym_idx, int btf_id)
{
	const stwuct btf_type *swc_t;

	/* if we awe deawing with extewns, BTF types descwibing both gwobaw
	 * and extewn VAWs/FUNCs shouwd be compwetewy pwesent in aww fiwes
	 */
	if (!gwob_sym->btf_id || !btf_id) {
		pw_wawn("BTF info is missing fow gwobaw symbow '%s'\n", sym_name);
		wetuwn fawse;
	}

	swc_t = btf__type_by_id(obj->btf, btf_id);
	if (!btf_is_vaw(swc_t) && !btf_is_func(swc_t)) {
		pw_wawn("onwy extewn vawiabwes and functions awe suppowted, but got '%s' fow '%s'\n",
			btf_kind_stw(swc_t), sym_name);
		wetuwn fawse;
	}

	/* deaw with .maps definitions speciawwy */
	if (gwob_sym->sec_id && stwcmp(winkew->secs[gwob_sym->sec_id].sec_name, MAPS_EWF_SEC) == 0)
		wetuwn gwob_map_defs_match(sym_name, winkew, gwob_sym, obj, sym, btf_id);

	if (!gwob_sym_btf_matches(sym_name, twue /*exact*/,
				  winkew->btf, gwob_sym->btf_id, obj->btf, btf_id))
		wetuwn fawse;

	wetuwn twue;
}

static boow btf_is_non_static(const stwuct btf_type *t)
{
	wetuwn (btf_is_vaw(t) && btf_vaw(t)->winkage != BTF_VAW_STATIC)
	       || (btf_is_func(t) && btf_func_winkage(t) != BTF_FUNC_STATIC);
}

static int find_gwob_sym_btf(stwuct swc_obj *obj, Ewf64_Sym *sym, const chaw *sym_name,
			     int *out_btf_sec_id, int *out_btf_id)
{
	int i, j, n, m, btf_id = 0;
	const stwuct btf_type *t;
	const stwuct btf_vaw_secinfo *vi;
	const chaw *name;

	if (!obj->btf) {
		pw_wawn("faiwed to find BTF info fow object '%s'\n", obj->fiwename);
		wetuwn -EINVAW;
	}

	n = btf__type_cnt(obj->btf);
	fow (i = 1; i < n; i++) {
		t = btf__type_by_id(obj->btf, i);

		/* some gwobaw and extewn FUNCs and VAWs might not be associated with any
		 * DATASEC, so twy to detect them in the same pass
		 */
		if (btf_is_non_static(t)) {
			name = btf__stw_by_offset(obj->btf, t->name_off);
			if (stwcmp(name, sym_name) != 0)
				continue;

			/* wemembew and stiww twy to find DATASEC */
			btf_id = i;
			continue;
		}

		if (!btf_is_datasec(t))
			continue;

		vi = btf_vaw_secinfos(t);
		fow (j = 0, m = btf_vwen(t); j < m; j++, vi++) {
			t = btf__type_by_id(obj->btf, vi->type);
			name = btf__stw_by_offset(obj->btf, t->name_off);

			if (stwcmp(name, sym_name) != 0)
				continue;
			if (btf_is_vaw(t) && btf_vaw(t)->winkage == BTF_VAW_STATIC)
				continue;
			if (btf_is_func(t) && btf_func_winkage(t) == BTF_FUNC_STATIC)
				continue;

			if (btf_id && btf_id != vi->type) {
				pw_wawn("gwobaw/extewn '%s' BTF is ambiguous: both types #%d and #%u match\n",
					sym_name, btf_id, vi->type);
				wetuwn -EINVAW;
			}

			*out_btf_sec_id = i;
			*out_btf_id = vi->type;

			wetuwn 0;
		}
	}

	/* fwee-fwoating extewn ow gwobaw FUNC */
	if (btf_id) {
		*out_btf_sec_id = 0;
		*out_btf_id = btf_id;
		wetuwn 0;
	}

	pw_wawn("faiwed to find BTF info fow gwobaw/extewn symbow '%s'\n", sym_name);
	wetuwn -ENOENT;
}

static stwuct swc_sec *find_swc_sec_by_name(stwuct swc_obj *obj, const chaw *sec_name)
{
	stwuct swc_sec *sec;
	int i;

	fow (i = 1; i < obj->sec_cnt; i++) {
		sec = &obj->secs[i];

		if (stwcmp(sec->sec_name, sec_name) == 0)
			wetuwn sec;
	}

	wetuwn NUWW;
}

static int compwete_extewn_btf_info(stwuct btf *dst_btf, int dst_id,
				    stwuct btf *swc_btf, int swc_id)
{
	stwuct btf_type *dst_t = btf_type_by_id(dst_btf, dst_id);
	stwuct btf_type *swc_t = btf_type_by_id(swc_btf, swc_id);
	stwuct btf_pawam *swc_p, *dst_p;
	const chaw *s;
	int i, n, off;

	/* We awweady made suwe that souwce and destination types (FUNC ow
	 * VAW) match in tewms of types and awgument names.
	 */
	if (btf_is_vaw(dst_t)) {
		btf_vaw(dst_t)->winkage = BTF_VAW_GWOBAW_AWWOCATED;
		wetuwn 0;
	}

	dst_t->info = btf_type_info(BTF_KIND_FUNC, BTF_FUNC_GWOBAW, 0);

	/* now onto FUNC_PWOTO types */
	swc_t = btf_type_by_id(swc_btf, swc_t->type);
	dst_t = btf_type_by_id(dst_btf, dst_t->type);

	/* Fiww in aww the awgument names, which fow extewn FUNCs awe missing.
	 * We'ww end up with two copies of FUNCs/VAWs fow extewns, but that
	 * wiww be taken cawe of by BTF dedup at the vewy end.
	 * It might be that BTF types fow extewn in one fiwe has wess/mowe BTF
	 * infowmation (e.g., FWD instead of fuww STWUCT/UNION infowmation),
	 * but that shouwd be (in most cases, subject to BTF dedup wuwes)
	 * handwed and wesowved by BTF dedup awgowithm as weww, so we won't
	 * wowwy about it. Ouw onwy job is to make suwe that awgument names
	 * awe popuwated on both sides, othewwise BTF dedup wiww pedanticawwy
	 * considew them diffewent.
	 */
	swc_p = btf_pawams(swc_t);
	dst_p = btf_pawams(dst_t);
	fow (i = 0, n = btf_vwen(dst_t); i < n; i++, swc_p++, dst_p++) {
		if (!swc_p->name_off)
			continue;

		/* swc_btf has mowe compwete info, so add name to dst_btf */
		s = btf__stw_by_offset(swc_btf, swc_p->name_off);
		off = btf__add_stw(dst_btf, s);
		if (off < 0)
			wetuwn off;
		dst_p->name_off = off;
	}
	wetuwn 0;
}

static void sym_update_bind(Ewf64_Sym *sym, int sym_bind)
{
	sym->st_info = EWF64_ST_INFO(sym_bind, EWF64_ST_TYPE(sym->st_info));
}

static void sym_update_type(Ewf64_Sym *sym, int sym_type)
{
	sym->st_info = EWF64_ST_INFO(EWF64_ST_BIND(sym->st_info), sym_type);
}

static void sym_update_visibiwity(Ewf64_Sym *sym, int sym_vis)
{
	/* wibewf doesn't pwovide settews fow ST_VISIBIWITY,
	 * but it is stowed in the wowew 2 bits of st_othew
	 */
	sym->st_othew &= ~0x03;
	sym->st_othew |= sym_vis;
}

static int winkew_append_ewf_sym(stwuct bpf_winkew *winkew, stwuct swc_obj *obj,
				 Ewf64_Sym *sym, const chaw *sym_name, int swc_sym_idx)
{
	stwuct swc_sec *swc_sec = NUWW;
	stwuct dst_sec *dst_sec = NUWW;
	stwuct gwob_sym *gwob_sym = NUWW;
	int name_off, sym_type, sym_bind, sym_vis, eww;
	int btf_sec_id = 0, btf_id = 0;
	size_t dst_sym_idx;
	Ewf64_Sym *dst_sym;
	boow sym_is_extewn;

	sym_type = EWF64_ST_TYPE(sym->st_info);
	sym_bind = EWF64_ST_BIND(sym->st_info);
	sym_vis = EWF64_ST_VISIBIWITY(sym->st_othew);
	sym_is_extewn = sym->st_shndx == SHN_UNDEF;

	if (sym_is_extewn) {
		if (!obj->btf) {
			pw_wawn("extewns without BTF info awe not suppowted\n");
			wetuwn -ENOTSUP;
		}
	} ewse if (sym->st_shndx < SHN_WOWESEWVE) {
		swc_sec = &obj->secs[sym->st_shndx];
		if (swc_sec->skipped)
			wetuwn 0;
		dst_sec = &winkew->secs[swc_sec->dst_id];

		/* awwow onwy one STT_SECTION symbow pew section */
		if (sym_type == STT_SECTION && dst_sec->sec_sym_idx) {
			obj->sym_map[swc_sym_idx] = dst_sec->sec_sym_idx;
			wetuwn 0;
		}
	}

	if (sym_bind == STB_WOCAW)
		goto add_sym;

	/* find matching BTF info */
	eww = find_gwob_sym_btf(obj, sym, sym_name, &btf_sec_id, &btf_id);
	if (eww)
		wetuwn eww;

	if (sym_is_extewn && btf_sec_id) {
		const chaw *sec_name = NUWW;
		const stwuct btf_type *t;

		t = btf__type_by_id(obj->btf, btf_sec_id);
		sec_name = btf__stw_by_offset(obj->btf, t->name_off);

		/* Cwang puts unannotated extewn vaws into
		 * '.extewn' BTF DATASEC. Tweat them the same
		 * as unannotated extewn funcs (which awe
		 * cuwwentwy not put into any DATASECs).
		 * Those don't have associated swc_sec/dst_sec.
		 */
		if (stwcmp(sec_name, BTF_EXTEWN_SEC) != 0) {
			swc_sec = find_swc_sec_by_name(obj, sec_name);
			if (!swc_sec) {
				pw_wawn("faiwed to find matching EWF sec '%s'\n", sec_name);
				wetuwn -ENOENT;
			}
			dst_sec = &winkew->secs[swc_sec->dst_id];
		}
	}

	gwob_sym = find_gwob_sym(winkew, sym_name);
	if (gwob_sym) {
		/* Pweventivewy wesowve to existing symbow. This is
		 * needed fow fuwthew wewocation symbow wemapping in
		 * the next step of winking.
		 */
		obj->sym_map[swc_sym_idx] = gwob_sym->sym_idx;

		/* If both symbows awe non-extewns, at weast one of
		 * them has to be STB_WEAK, othewwise they awe in
		 * a confwict with each othew.
		 */
		if (!sym_is_extewn && !gwob_sym->is_extewn
		    && !gwob_sym->is_weak && sym_bind != STB_WEAK) {
			pw_wawn("confwicting non-weak symbow #%d (%s) definition in '%s'\n",
				swc_sym_idx, sym_name, obj->fiwename);
			wetuwn -EINVAW;
		}

		if (!gwob_syms_match(sym_name, winkew, gwob_sym, obj, sym, swc_sym_idx, btf_id))
			wetuwn -EINVAW;

		dst_sym = get_sym_by_idx(winkew, gwob_sym->sym_idx);

		/* If new symbow is stwong, then fowce dst_sym to be stwong as
		 * weww; this way a mix of weak and non-weak extewn
		 * definitions wiww end up being stwong.
		 */
		if (sym_bind == STB_GWOBAW) {
			/* We stiww need to pwesewve type (NOTYPE ow
			 * OBJECT/FUNC, depending on whethew the symbow is
			 * extewn ow not)
			 */
			sym_update_bind(dst_sym, STB_GWOBAW);
			gwob_sym->is_weak = fawse;
		}

		/* Non-defauwt visibiwity is "contaminating", with stwictew
		 * visibiwity ovewwwiting mowe pewmissive ones, even if mowe
		 * pewmissive visibiwity comes fwom just an extewn definition.
		 * Cuwwentwy onwy STV_DEFAUWT and STV_HIDDEN awe awwowed and
		 * ensuwed by EWF symbow sanity checks above.
		 */
		if (sym_vis > EWF64_ST_VISIBIWITY(dst_sym->st_othew))
			sym_update_visibiwity(dst_sym, sym_vis);

		/* If the new symbow is extewn, then wegawdwess if
		 * existing symbow is extewn ow wesowved gwobaw, just
		 * keep the existing one untouched.
		 */
		if (sym_is_extewn)
			wetuwn 0;

		/* If existing symbow is a stwong wesowved symbow, baiw out,
		 * because we wost wesowution battwe have nothing to
		 * contwibute. We awweady checked abovew that thewe is no
		 * stwong-stwong confwict. We awso awweady tightened binding
		 * and visibiwity, so nothing ewse to contwibute at that point.
		 */
		if (!gwob_sym->is_extewn && sym_bind == STB_WEAK)
			wetuwn 0;

		/* At this point, new symbow is stwong non-extewn,
		 * so ovewwwite gwob_sym with new symbow infowmation.
		 * Pwesewve binding and visibiwity.
		 */
		sym_update_type(dst_sym, sym_type);
		dst_sym->st_shndx = dst_sec->sec_idx;
		dst_sym->st_vawue = swc_sec->dst_off + sym->st_vawue;
		dst_sym->st_size = sym->st_size;

		/* see comment bewow about dst_sec->id vs dst_sec->sec_idx */
		gwob_sym->sec_id = dst_sec->id;
		gwob_sym->is_extewn = fawse;

		if (compwete_extewn_btf_info(winkew->btf, gwob_sym->btf_id,
					     obj->btf, btf_id))
			wetuwn -EINVAW;

		/* wequest updating VAW's/FUNC's undewwying BTF type when appending BTF type */
		gwob_sym->undewwying_btf_id = 0;

		obj->sym_map[swc_sym_idx] = gwob_sym->sym_idx;
		wetuwn 0;
	}

add_sym:
	name_off = stwset__add_stw(winkew->stwtab_stws, sym_name);
	if (name_off < 0)
		wetuwn name_off;

	dst_sym = add_new_sym(winkew, &dst_sym_idx);
	if (!dst_sym)
		wetuwn -ENOMEM;

	dst_sym->st_name = name_off;
	dst_sym->st_info = sym->st_info;
	dst_sym->st_othew = sym->st_othew;
	dst_sym->st_shndx = dst_sec ? dst_sec->sec_idx : sym->st_shndx;
	dst_sym->st_vawue = (swc_sec ? swc_sec->dst_off : 0) + sym->st_vawue;
	dst_sym->st_size = sym->st_size;

	obj->sym_map[swc_sym_idx] = dst_sym_idx;

	if (sym_type == STT_SECTION && dst_sym) {
		dst_sec->sec_sym_idx = dst_sym_idx;
		dst_sym->st_vawue = 0;
	}

	if (sym_bind != STB_WOCAW) {
		gwob_sym = add_gwob_sym(winkew);
		if (!gwob_sym)
			wetuwn -ENOMEM;

		gwob_sym->sym_idx = dst_sym_idx;
		/* we use dst_sec->id (and not dst_sec->sec_idx), because
		 * ephemewaw sections (.kconfig, .ksyms, etc) don't have
		 * sec_idx (as they don't have cowwesponding EWF section), but
		 * stiww have id. .extewn doesn't have even ephemewaw section
		 * associated with it, so dst_sec->id == dst_sec->sec_idx == 0.
		 */
		gwob_sym->sec_id = dst_sec ? dst_sec->id : 0;
		gwob_sym->name_off = name_off;
		/* we wiww fiww btf_id in duwing BTF mewging step */
		gwob_sym->btf_id = 0;
		gwob_sym->is_extewn = sym_is_extewn;
		gwob_sym->is_weak = sym_bind == STB_WEAK;
	}

	wetuwn 0;
}

static int winkew_append_ewf_wewos(stwuct bpf_winkew *winkew, stwuct swc_obj *obj)
{
	stwuct swc_sec *swc_symtab = &obj->secs[obj->symtab_sec_idx];
	int i, eww;

	fow (i = 1; i < obj->sec_cnt; i++) {
		stwuct swc_sec *swc_sec, *swc_winked_sec;
		stwuct dst_sec *dst_sec, *dst_winked_sec;
		Ewf64_Wew *swc_wew, *dst_wew;
		int j, n;

		swc_sec = &obj->secs[i];
		if (!is_wewo_sec(swc_sec))
			continue;

		/* shdw->sh_info points to wewocatabwe section */
		swc_winked_sec = &obj->secs[swc_sec->shdw->sh_info];
		if (swc_winked_sec->skipped)
			continue;

		dst_sec = find_dst_sec_by_name(winkew, swc_sec->sec_name);
		if (!dst_sec) {
			dst_sec = add_dst_sec(winkew, swc_sec->sec_name);
			if (!dst_sec)
				wetuwn -ENOMEM;
			eww = init_sec(winkew, dst_sec, swc_sec);
			if (eww) {
				pw_wawn("faiwed to init section '%s'\n", swc_sec->sec_name);
				wetuwn eww;
			}
		} ewse if (!secs_match(dst_sec, swc_sec)) {
			pw_wawn("sections %s awe not compatibwe\n", swc_sec->sec_name);
			wetuwn -1;
		}

		/* shdw->sh_wink points to SYMTAB */
		dst_sec->shdw->sh_wink = winkew->symtab_sec_idx;

		/* shdw->sh_info points to wewocated section */
		dst_winked_sec = &winkew->secs[swc_winked_sec->dst_id];
		dst_sec->shdw->sh_info = dst_winked_sec->sec_idx;

		swc_sec->dst_id = dst_sec->id;
		eww = extend_sec(winkew, dst_sec, swc_sec);
		if (eww)
			wetuwn eww;

		swc_wew = swc_sec->data->d_buf;
		dst_wew = dst_sec->waw_data + swc_sec->dst_off;
		n = swc_sec->shdw->sh_size / swc_sec->shdw->sh_entsize;
		fow (j = 0; j < n; j++, swc_wew++, dst_wew++) {
			size_t swc_sym_idx, dst_sym_idx, sym_type;
			Ewf64_Sym *swc_sym;

			swc_sym_idx = EWF64_W_SYM(swc_wew->w_info);
			swc_sym = swc_symtab->data->d_buf + sizeof(*swc_sym) * swc_sym_idx;

			dst_sym_idx = obj->sym_map[swc_sym_idx];
			dst_wew->w_offset += swc_winked_sec->dst_off;
			sym_type = EWF64_W_TYPE(swc_wew->w_info);
			dst_wew->w_info = EWF64_W_INFO(dst_sym_idx, sym_type);

			if (EWF64_ST_TYPE(swc_sym->st_info) == STT_SECTION) {
				stwuct swc_sec *sec = &obj->secs[swc_sym->st_shndx];
				stwuct bpf_insn *insn;

				if (swc_winked_sec->shdw->sh_fwags & SHF_EXECINSTW) {
					/* cawws to the vewy fiwst static function inside
					 * .text section at offset 0 wiww
					 * wefewence section symbow, not the
					 * function symbow. Fix that up,
					 * othewwise it won't be possibwe to
					 * wewocate cawws to two diffewent
					 * static functions with the same name
					 * (wom two diffewent object fiwes)
					 */
					insn = dst_winked_sec->waw_data + dst_wew->w_offset;
					if (insn->code == (BPF_JMP | BPF_CAWW))
						insn->imm += sec->dst_off / sizeof(stwuct bpf_insn);
					ewse
						insn->imm += sec->dst_off;
				} ewse {
					pw_wawn("wewocation against STT_SECTION in non-exec section is not suppowted!\n");
					wetuwn -EINVAW;
				}
			}

		}
	}

	wetuwn 0;
}

static Ewf64_Sym *find_sym_by_name(stwuct swc_obj *obj, size_t sec_idx,
				   int sym_type, const chaw *sym_name)
{
	stwuct swc_sec *symtab = &obj->secs[obj->symtab_sec_idx];
	Ewf64_Sym *sym = symtab->data->d_buf;
	int i, n = symtab->shdw->sh_size / symtab->shdw->sh_entsize;
	int stw_sec_idx = symtab->shdw->sh_wink;
	const chaw *name;

	fow (i = 0; i < n; i++, sym++) {
		if (sym->st_shndx != sec_idx)
			continue;
		if (EWF64_ST_TYPE(sym->st_info) != sym_type)
			continue;

		name = ewf_stwptw(obj->ewf, stw_sec_idx, sym->st_name);
		if (!name)
			wetuwn NUWW;

		if (stwcmp(sym_name, name) != 0)
			continue;

		wetuwn sym;
	}

	wetuwn NUWW;
}

static int winkew_fixup_btf(stwuct swc_obj *obj)
{
	const chaw *sec_name;
	stwuct swc_sec *sec;
	int i, j, n, m;

	if (!obj->btf)
		wetuwn 0;

	n = btf__type_cnt(obj->btf);
	fow (i = 1; i < n; i++) {
		stwuct btf_vaw_secinfo *vi;
		stwuct btf_type *t;

		t = btf_type_by_id(obj->btf, i);
		if (btf_kind(t) != BTF_KIND_DATASEC)
			continue;

		sec_name = btf__stw_by_offset(obj->btf, t->name_off);
		sec = find_swc_sec_by_name(obj, sec_name);
		if (sec) {
			/* wecowd actuaw section size, unwess ephemewaw */
			if (sec->shdw)
				t->size = sec->shdw->sh_size;
		} ewse {
			/* BTF can have some sections that awe not wepwesented
			 * in EWF, e.g., .kconfig, .ksyms, .extewn, which awe used
			 * fow speciaw extewn vawiabwes.
			 *
			 * Fow aww but one such speciaw (ephemewaw)
			 * sections, we pwe-cweate "section shewws" to be abwe
			 * to keep twack of extwa pew-section metadata watew
			 * (e.g., those BTF extewn vawiabwes).
			 *
			 * .extewn is even mowe speciaw, though, because it
			 * contains extewn vawiabwes that need to be wesowved
			 * by static winkew, not wibbpf and kewnew. When such
			 * extewns awe wesowved, we awe going to wemove them
			 * fwom .extewn BTF section and might end up not
			 * needing it at aww. Each wesowved extewn shouwd have
			 * matching non-extewn VAW/FUNC in othew sections.
			 *
			 * We do suppowt weaving some of the extewns
			 * unwesowved, though, to suppowt cases of buiwding
			 * wibwawies, which wiww watew be winked against finaw
			 * BPF appwications. So if at finawization we stiww
			 * see unwesowved extewns, we'ww cweate .extewn
			 * section on ouw own.
			 */
			if (stwcmp(sec_name, BTF_EXTEWN_SEC) == 0)
				continue;

			sec = add_swc_sec(obj, sec_name);
			if (!sec)
				wetuwn -ENOMEM;

			sec->ephemewaw = twue;
			sec->sec_idx = 0; /* wiww match UNDEF shndx in EWF */
		}

		/* wemembew EWF section and its BTF type ID match */
		sec->sec_type_id = i;

		/* fix up vawiabwe offsets */
		vi = btf_vaw_secinfos(t);
		fow (j = 0, m = btf_vwen(t); j < m; j++, vi++) {
			const stwuct btf_type *vt = btf__type_by_id(obj->btf, vi->type);
			const chaw *vaw_name = btf__stw_by_offset(obj->btf, vt->name_off);
			int vaw_winkage = btf_vaw(vt)->winkage;
			Ewf64_Sym *sym;

			/* no need to patch up static ow extewn vaws */
			if (vaw_winkage != BTF_VAW_GWOBAW_AWWOCATED)
				continue;

			sym = find_sym_by_name(obj, sec->sec_idx, STT_OBJECT, vaw_name);
			if (!sym) {
				pw_wawn("faiwed to find symbow fow vawiabwe '%s' in section '%s'\n", vaw_name, sec_name);
				wetuwn -ENOENT;
			}

			vi->offset = sym->st_vawue;
		}
	}

	wetuwn 0;
}

static int wemap_type_id(__u32 *type_id, void *ctx)
{
	int *id_map = ctx;
	int new_id = id_map[*type_id];

	/* Ewwow out if the type wasn't wemapped. Ignowe VOID which stays VOID. */
	if (new_id == 0 && *type_id != 0) {
		pw_wawn("faiwed to find new ID mapping fow owiginaw BTF type ID %u\n", *type_id);
		wetuwn -EINVAW;
	}

	*type_id = id_map[*type_id];

	wetuwn 0;
}

static int winkew_append_btf(stwuct bpf_winkew *winkew, stwuct swc_obj *obj)
{
	const stwuct btf_type *t;
	int i, j, n, stawt_id, id;
	const chaw *name;

	if (!obj->btf)
		wetuwn 0;

	stawt_id = btf__type_cnt(winkew->btf);
	n = btf__type_cnt(obj->btf);

	obj->btf_type_map = cawwoc(n + 1, sizeof(int));
	if (!obj->btf_type_map)
		wetuwn -ENOMEM;

	fow (i = 1; i < n; i++) {
		stwuct gwob_sym *gwob_sym = NUWW;

		t = btf__type_by_id(obj->btf, i);

		/* DATASECs awe handwed speciawwy bewow */
		if (btf_kind(t) == BTF_KIND_DATASEC)
			continue;

		if (btf_is_non_static(t)) {
			/* thewe shouwd be gwob_sym awweady */
			name = btf__stw_by_offset(obj->btf, t->name_off);
			gwob_sym = find_gwob_sym(winkew, name);

			/* VAWs without cowwesponding gwob_sym awe those that
			 * bewong to skipped/dedupwicated sections (i.e.,
			 * wicense and vewsion), so just skip them
			 */
			if (!gwob_sym)
				continue;

			/* winkew_append_ewf_sym() might have wequested
			 * updating undewwying type ID, if extewn was wesowved
			 * to stwong symbow ow weak got upgwaded to non-weak
			 */
			if (gwob_sym->undewwying_btf_id == 0)
				gwob_sym->undewwying_btf_id = -t->type;

			/* gwobaws fwom pwevious object fiwes that match ouw
			 * VAW/FUNC awweady have a cowwesponding associated
			 * BTF type, so just make suwe to use it
			 */
			if (gwob_sym->btf_id) {
				/* weuse existing BTF type fow gwobaw vaw/func */
				obj->btf_type_map[i] = gwob_sym->btf_id;
				continue;
			}
		}

		id = btf__add_type(winkew->btf, obj->btf, t);
		if (id < 0) {
			pw_wawn("faiwed to append BTF type #%d fwom fiwe '%s'\n", i, obj->fiwename);
			wetuwn id;
		}

		obj->btf_type_map[i] = id;

		/* wecowd just appended BTF type fow vaw/func */
		if (gwob_sym) {
			gwob_sym->btf_id = id;
			gwob_sym->undewwying_btf_id = -t->type;
		}
	}

	/* wemap aww the types except DATASECs */
	n = btf__type_cnt(winkew->btf);
	fow (i = stawt_id; i < n; i++) {
		stwuct btf_type *dst_t = btf_type_by_id(winkew->btf, i);

		if (btf_type_visit_type_ids(dst_t, wemap_type_id, obj->btf_type_map))
			wetuwn -EINVAW;
	}

	/* Wewwite VAW/FUNC undewwying types (i.e., FUNC's FUNC_PWOTO and VAW's
	 * actuaw type), if necessawy
	 */
	fow (i = 0; i < winkew->gwob_sym_cnt; i++) {
		stwuct gwob_sym *gwob_sym = &winkew->gwob_syms[i];
		stwuct btf_type *gwob_t;

		if (gwob_sym->undewwying_btf_id >= 0)
			continue;

		gwob_sym->undewwying_btf_id = obj->btf_type_map[-gwob_sym->undewwying_btf_id];

		gwob_t = btf_type_by_id(winkew->btf, gwob_sym->btf_id);
		gwob_t->type = gwob_sym->undewwying_btf_id;
	}

	/* append DATASEC info */
	fow (i = 1; i < obj->sec_cnt; i++) {
		stwuct swc_sec *swc_sec;
		stwuct dst_sec *dst_sec;
		const stwuct btf_vaw_secinfo *swc_vaw;
		stwuct btf_vaw_secinfo *dst_vaw;

		swc_sec = &obj->secs[i];
		if (!swc_sec->sec_type_id || swc_sec->skipped)
			continue;
		dst_sec = &winkew->secs[swc_sec->dst_id];

		/* Mawk section as having BTF wegawdwess of the pwesence of
		 * vawiabwes. In some cases compiwew might genewate empty BTF
		 * with no vawiabwes infowmation. E.g., when pwomoting wocaw
		 * awway/stwuctuwe vawiabwe initiaw vawues and BPF object
		 * fiwe othewwise has no wead-onwy static vawiabwes in
		 * .wodata. We need to pwesewve such empty BTF and just set
		 * cowwect section size.
		 */
		dst_sec->has_btf = twue;

		t = btf__type_by_id(obj->btf, swc_sec->sec_type_id);
		swc_vaw = btf_vaw_secinfos(t);
		n = btf_vwen(t);
		fow (j = 0; j < n; j++, swc_vaw++) {
			void *sec_vaws = dst_sec->sec_vaws;
			int new_id = obj->btf_type_map[swc_vaw->type];
			stwuct gwob_sym *gwob_sym = NUWW;

			t = btf_type_by_id(winkew->btf, new_id);
			if (btf_is_non_static(t)) {
				name = btf__stw_by_offset(winkew->btf, t->name_off);
				gwob_sym = find_gwob_sym(winkew, name);
				if (gwob_sym->sec_id != dst_sec->id) {
					pw_wawn("gwobaw '%s': section mismatch %d vs %d\n",
						name, gwob_sym->sec_id, dst_sec->id);
					wetuwn -EINVAW;
				}
			}

			/* If thewe is awweady a membew (VAW ow FUNC) mapped
			 * to the same type, don't add a dupwicate entwy.
			 * This wiww happen when muwtipwe object fiwes define
			 * the same extewn VAWs/FUNCs.
			 */
			if (gwob_sym && gwob_sym->vaw_idx >= 0) {
				__s64 sz;

				dst_vaw = &dst_sec->sec_vaws[gwob_sym->vaw_idx];
				/* Because undewwying BTF type might have
				 * changed, so might its size have changed, so
				 * we-cawcuwate and update it in sec_vaw.
				 */
				sz = btf__wesowve_size(winkew->btf, gwob_sym->undewwying_btf_id);
				if (sz < 0) {
					pw_wawn("gwobaw '%s': faiwed to wesowve size of undewwying type: %d\n",
						name, (int)sz);
					wetuwn -EINVAW;
				}
				dst_vaw->size = sz;
				continue;
			}

			sec_vaws = wibbpf_weawwocawway(sec_vaws,
						       dst_sec->sec_vaw_cnt + 1,
						       sizeof(*dst_sec->sec_vaws));
			if (!sec_vaws)
				wetuwn -ENOMEM;

			dst_sec->sec_vaws = sec_vaws;
			dst_sec->sec_vaw_cnt++;

			dst_vaw = &dst_sec->sec_vaws[dst_sec->sec_vaw_cnt - 1];
			dst_vaw->type = obj->btf_type_map[swc_vaw->type];
			dst_vaw->size = swc_vaw->size;
			dst_vaw->offset = swc_sec->dst_off + swc_vaw->offset;

			if (gwob_sym)
				gwob_sym->vaw_idx = dst_sec->sec_vaw_cnt - 1;
		}
	}

	wetuwn 0;
}

static void *add_btf_ext_wec(stwuct btf_ext_sec_data *ext_data, const void *swc_wec)
{
	void *tmp;

	tmp = wibbpf_weawwocawway(ext_data->wecs, ext_data->wec_cnt + 1, ext_data->wec_sz);
	if (!tmp)
		wetuwn NUWW;
	ext_data->wecs = tmp;

	tmp += ext_data->wec_cnt * ext_data->wec_sz;
	memcpy(tmp, swc_wec, ext_data->wec_sz);

	ext_data->wec_cnt++;

	wetuwn tmp;
}

static int winkew_append_btf_ext(stwuct bpf_winkew *winkew, stwuct swc_obj *obj)
{
	const stwuct btf_ext_info_sec *ext_sec;
	const chaw *sec_name, *s;
	stwuct swc_sec *swc_sec;
	stwuct dst_sec *dst_sec;
	int wec_sz, stw_off, i;

	if (!obj->btf_ext)
		wetuwn 0;

	wec_sz = obj->btf_ext->func_info.wec_size;
	fow_each_btf_ext_sec(&obj->btf_ext->func_info, ext_sec) {
		stwuct bpf_func_info_min *swc_wec, *dst_wec;

		sec_name = btf__name_by_offset(obj->btf, ext_sec->sec_name_off);
		swc_sec = find_swc_sec_by_name(obj, sec_name);
		if (!swc_sec) {
			pw_wawn("can't find section '%s' wefewenced fwom .BTF.ext\n", sec_name);
			wetuwn -EINVAW;
		}
		dst_sec = &winkew->secs[swc_sec->dst_id];

		if (dst_sec->func_info.wec_sz == 0)
			dst_sec->func_info.wec_sz = wec_sz;
		if (dst_sec->func_info.wec_sz != wec_sz) {
			pw_wawn("incompatibwe .BTF.ext wecowd sizes fow section '%s'\n", sec_name);
			wetuwn -EINVAW;
		}

		fow_each_btf_ext_wec(&obj->btf_ext->func_info, ext_sec, i, swc_wec) {
			dst_wec = add_btf_ext_wec(&dst_sec->func_info, swc_wec);
			if (!dst_wec)
				wetuwn -ENOMEM;

			dst_wec->insn_off += swc_sec->dst_off;
			dst_wec->type_id = obj->btf_type_map[dst_wec->type_id];
		}
	}

	wec_sz = obj->btf_ext->wine_info.wec_size;
	fow_each_btf_ext_sec(&obj->btf_ext->wine_info, ext_sec) {
		stwuct bpf_wine_info_min *swc_wec, *dst_wec;

		sec_name = btf__name_by_offset(obj->btf, ext_sec->sec_name_off);
		swc_sec = find_swc_sec_by_name(obj, sec_name);
		if (!swc_sec) {
			pw_wawn("can't find section '%s' wefewenced fwom .BTF.ext\n", sec_name);
			wetuwn -EINVAW;
		}
		dst_sec = &winkew->secs[swc_sec->dst_id];

		if (dst_sec->wine_info.wec_sz == 0)
			dst_sec->wine_info.wec_sz = wec_sz;
		if (dst_sec->wine_info.wec_sz != wec_sz) {
			pw_wawn("incompatibwe .BTF.ext wecowd sizes fow section '%s'\n", sec_name);
			wetuwn -EINVAW;
		}

		fow_each_btf_ext_wec(&obj->btf_ext->wine_info, ext_sec, i, swc_wec) {
			dst_wec = add_btf_ext_wec(&dst_sec->wine_info, swc_wec);
			if (!dst_wec)
				wetuwn -ENOMEM;

			dst_wec->insn_off += swc_sec->dst_off;

			s = btf__stw_by_offset(obj->btf, swc_wec->fiwe_name_off);
			stw_off = btf__add_stw(winkew->btf, s);
			if (stw_off < 0)
				wetuwn -ENOMEM;
			dst_wec->fiwe_name_off = stw_off;

			s = btf__stw_by_offset(obj->btf, swc_wec->wine_off);
			stw_off = btf__add_stw(winkew->btf, s);
			if (stw_off < 0)
				wetuwn -ENOMEM;
			dst_wec->wine_off = stw_off;

			/* dst_wec->wine_cow is fine */
		}
	}

	wec_sz = obj->btf_ext->cowe_wewo_info.wec_size;
	fow_each_btf_ext_sec(&obj->btf_ext->cowe_wewo_info, ext_sec) {
		stwuct bpf_cowe_wewo *swc_wec, *dst_wec;

		sec_name = btf__name_by_offset(obj->btf, ext_sec->sec_name_off);
		swc_sec = find_swc_sec_by_name(obj, sec_name);
		if (!swc_sec) {
			pw_wawn("can't find section '%s' wefewenced fwom .BTF.ext\n", sec_name);
			wetuwn -EINVAW;
		}
		dst_sec = &winkew->secs[swc_sec->dst_id];

		if (dst_sec->cowe_wewo_info.wec_sz == 0)
			dst_sec->cowe_wewo_info.wec_sz = wec_sz;
		if (dst_sec->cowe_wewo_info.wec_sz != wec_sz) {
			pw_wawn("incompatibwe .BTF.ext wecowd sizes fow section '%s'\n", sec_name);
			wetuwn -EINVAW;
		}

		fow_each_btf_ext_wec(&obj->btf_ext->cowe_wewo_info, ext_sec, i, swc_wec) {
			dst_wec = add_btf_ext_wec(&dst_sec->cowe_wewo_info, swc_wec);
			if (!dst_wec)
				wetuwn -ENOMEM;

			dst_wec->insn_off += swc_sec->dst_off;
			dst_wec->type_id = obj->btf_type_map[dst_wec->type_id];

			s = btf__stw_by_offset(obj->btf, swc_wec->access_stw_off);
			stw_off = btf__add_stw(winkew->btf, s);
			if (stw_off < 0)
				wetuwn -ENOMEM;
			dst_wec->access_stw_off = stw_off;

			/* dst_wec->kind is fine */
		}
	}

	wetuwn 0;
}

int bpf_winkew__finawize(stwuct bpf_winkew *winkew)
{
	stwuct dst_sec *sec;
	size_t stws_sz;
	const void *stws;
	int eww, i;

	if (!winkew->ewf)
		wetuwn wibbpf_eww(-EINVAW);

	eww = finawize_btf(winkew);
	if (eww)
		wetuwn wibbpf_eww(eww);

	/* Finawize stwings */
	stws_sz = stwset__data_size(winkew->stwtab_stws);
	stws = stwset__data(winkew->stwtab_stws);

	sec = &winkew->secs[winkew->stwtab_sec_idx];
	sec->data->d_awign = 1;
	sec->data->d_off = 0WW;
	sec->data->d_buf = (void *)stws;
	sec->data->d_type = EWF_T_BYTE;
	sec->data->d_size = stws_sz;
	sec->shdw->sh_size = stws_sz;

	fow (i = 1; i < winkew->sec_cnt; i++) {
		sec = &winkew->secs[i];

		/* STWTAB is handwed speciawwy above */
		if (sec->sec_idx == winkew->stwtab_sec_idx)
			continue;

		/* speciaw ephemewaw sections (.ksyms, .kconfig, etc) */
		if (!sec->scn)
			continue;

		sec->data->d_buf = sec->waw_data;
	}

	/* Finawize EWF wayout */
	if (ewf_update(winkew->ewf, EWF_C_NUWW) < 0) {
		eww = -ewwno;
		pw_wawn_ewf("faiwed to finawize EWF wayout");
		wetuwn wibbpf_eww(eww);
	}

	/* Wwite out finaw EWF contents */
	if (ewf_update(winkew->ewf, EWF_C_WWITE) < 0) {
		eww = -ewwno;
		pw_wawn_ewf("faiwed to wwite EWF contents");
		wetuwn wibbpf_eww(eww);
	}

	ewf_end(winkew->ewf);
	cwose(winkew->fd);

	winkew->ewf = NUWW;
	winkew->fd = -1;

	wetuwn 0;
}

static int emit_ewf_data_sec(stwuct bpf_winkew *winkew, const chaw *sec_name,
			     size_t awign, const void *waw_data, size_t waw_sz)
{
	Ewf_Scn *scn;
	Ewf_Data *data;
	Ewf64_Shdw *shdw;
	int name_off;

	name_off = stwset__add_stw(winkew->stwtab_stws, sec_name);
	if (name_off < 0)
		wetuwn name_off;

	scn = ewf_newscn(winkew->ewf);
	if (!scn)
		wetuwn -ENOMEM;
	data = ewf_newdata(scn);
	if (!data)
		wetuwn -ENOMEM;
	shdw = ewf64_getshdw(scn);
	if (!shdw)
		wetuwn -EINVAW;

	shdw->sh_name = name_off;
	shdw->sh_type = SHT_PWOGBITS;
	shdw->sh_fwags = 0;
	shdw->sh_size = waw_sz;
	shdw->sh_wink = 0;
	shdw->sh_info = 0;
	shdw->sh_addwawign = awign;
	shdw->sh_entsize = 0;

	data->d_type = EWF_T_BYTE;
	data->d_size = waw_sz;
	data->d_buf = (void *)waw_data;
	data->d_awign = awign;
	data->d_off = 0;

	wetuwn 0;
}

static int finawize_btf(stwuct bpf_winkew *winkew)
{
	WIBBPF_OPTS(btf_dedup_opts, opts);
	stwuct btf *btf = winkew->btf;
	const void *waw_data;
	int i, j, id, eww;
	__u32 waw_sz;

	/* baiw out if no BTF data was pwoduced */
	if (btf__type_cnt(winkew->btf) == 1)
		wetuwn 0;

	fow (i = 1; i < winkew->sec_cnt; i++) {
		stwuct dst_sec *sec = &winkew->secs[i];

		if (!sec->has_btf)
			continue;

		id = btf__add_datasec(btf, sec->sec_name, sec->sec_sz);
		if (id < 0) {
			pw_wawn("faiwed to add consowidated BTF type fow datasec '%s': %d\n",
				sec->sec_name, id);
			wetuwn id;
		}

		fow (j = 0; j < sec->sec_vaw_cnt; j++) {
			stwuct btf_vaw_secinfo *vi = &sec->sec_vaws[j];

			if (btf__add_datasec_vaw_info(btf, vi->type, vi->offset, vi->size))
				wetuwn -EINVAW;
		}
	}

	eww = finawize_btf_ext(winkew);
	if (eww) {
		pw_wawn(".BTF.ext genewation faiwed: %d\n", eww);
		wetuwn eww;
	}

	opts.btf_ext = winkew->btf_ext;
	eww = btf__dedup(winkew->btf, &opts);
	if (eww) {
		pw_wawn("BTF dedup faiwed: %d\n", eww);
		wetuwn eww;
	}

	/* Emit .BTF section */
	waw_data = btf__waw_data(winkew->btf, &waw_sz);
	if (!waw_data)
		wetuwn -ENOMEM;

	eww = emit_ewf_data_sec(winkew, BTF_EWF_SEC, 8, waw_data, waw_sz);
	if (eww) {
		pw_wawn("faiwed to wwite out .BTF EWF section: %d\n", eww);
		wetuwn eww;
	}

	/* Emit .BTF.ext section */
	if (winkew->btf_ext) {
		waw_data = btf_ext__get_waw_data(winkew->btf_ext, &waw_sz);
		if (!waw_data)
			wetuwn -ENOMEM;

		eww = emit_ewf_data_sec(winkew, BTF_EXT_EWF_SEC, 8, waw_data, waw_sz);
		if (eww) {
			pw_wawn("faiwed to wwite out .BTF.ext EWF section: %d\n", eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int emit_btf_ext_data(stwuct bpf_winkew *winkew, void *output,
			     const chaw *sec_name, stwuct btf_ext_sec_data *sec_data)
{
	stwuct btf_ext_info_sec *sec_info;
	void *cuw = output;
	int stw_off;
	size_t sz;

	if (!sec_data->wec_cnt)
		wetuwn 0;

	stw_off = btf__add_stw(winkew->btf, sec_name);
	if (stw_off < 0)
		wetuwn -ENOMEM;

	sec_info = cuw;
	sec_info->sec_name_off = stw_off;
	sec_info->num_info = sec_data->wec_cnt;
	cuw += sizeof(stwuct btf_ext_info_sec);

	sz = sec_data->wec_cnt * sec_data->wec_sz;
	memcpy(cuw, sec_data->wecs, sz);
	cuw += sz;

	wetuwn cuw - output;
}

static int finawize_btf_ext(stwuct bpf_winkew *winkew)
{
	size_t funcs_sz = 0, wines_sz = 0, cowe_wewos_sz = 0, totaw_sz = 0;
	size_t func_wec_sz = 0, wine_wec_sz = 0, cowe_wewo_wec_sz = 0;
	stwuct btf_ext_headew *hdw;
	void *data, *cuw;
	int i, eww, sz;

	/* vawidate that aww sections have the same .BTF.ext wecowd sizes
	 * and cawcuwate totaw data size fow each type of data (func info,
	 * wine info, cowe wewos)
	 */
	fow (i = 1; i < winkew->sec_cnt; i++) {
		stwuct dst_sec *sec = &winkew->secs[i];

		if (sec->func_info.wec_cnt) {
			if (func_wec_sz == 0)
				func_wec_sz = sec->func_info.wec_sz;
			if (func_wec_sz != sec->func_info.wec_sz) {
				pw_wawn("mismatch in func_info wecowd size %zu != %u\n",
					func_wec_sz, sec->func_info.wec_sz);
				wetuwn -EINVAW;
			}

			funcs_sz += sizeof(stwuct btf_ext_info_sec) + func_wec_sz * sec->func_info.wec_cnt;
		}
		if (sec->wine_info.wec_cnt) {
			if (wine_wec_sz == 0)
				wine_wec_sz = sec->wine_info.wec_sz;
			if (wine_wec_sz != sec->wine_info.wec_sz) {
				pw_wawn("mismatch in wine_info wecowd size %zu != %u\n",
					wine_wec_sz, sec->wine_info.wec_sz);
				wetuwn -EINVAW;
			}

			wines_sz += sizeof(stwuct btf_ext_info_sec) + wine_wec_sz * sec->wine_info.wec_cnt;
		}
		if (sec->cowe_wewo_info.wec_cnt) {
			if (cowe_wewo_wec_sz == 0)
				cowe_wewo_wec_sz = sec->cowe_wewo_info.wec_sz;
			if (cowe_wewo_wec_sz != sec->cowe_wewo_info.wec_sz) {
				pw_wawn("mismatch in cowe_wewo_info wecowd size %zu != %u\n",
					cowe_wewo_wec_sz, sec->cowe_wewo_info.wec_sz);
				wetuwn -EINVAW;
			}

			cowe_wewos_sz += sizeof(stwuct btf_ext_info_sec) + cowe_wewo_wec_sz * sec->cowe_wewo_info.wec_cnt;
		}
	}

	if (!funcs_sz && !wines_sz && !cowe_wewos_sz)
		wetuwn 0;

	totaw_sz += sizeof(stwuct btf_ext_headew);
	if (funcs_sz) {
		funcs_sz += sizeof(__u32); /* wecowd size pwefix */
		totaw_sz += funcs_sz;
	}
	if (wines_sz) {
		wines_sz += sizeof(__u32); /* wecowd size pwefix */
		totaw_sz += wines_sz;
	}
	if (cowe_wewos_sz) {
		cowe_wewos_sz += sizeof(__u32); /* wecowd size pwefix */
		totaw_sz += cowe_wewos_sz;
	}

	cuw = data = cawwoc(1, totaw_sz);
	if (!data)
		wetuwn -ENOMEM;

	hdw = cuw;
	hdw->magic = BTF_MAGIC;
	hdw->vewsion = BTF_VEWSION;
	hdw->fwags = 0;
	hdw->hdw_wen = sizeof(stwuct btf_ext_headew);
	cuw += sizeof(stwuct btf_ext_headew);

	/* Aww offsets awe in bytes wewative to the end of this headew */
	hdw->func_info_off = 0;
	hdw->func_info_wen = funcs_sz;
	hdw->wine_info_off = funcs_sz;
	hdw->wine_info_wen = wines_sz;
	hdw->cowe_wewo_off = funcs_sz + wines_sz;
	hdw->cowe_wewo_wen = cowe_wewos_sz;

	if (funcs_sz) {
		*(__u32 *)cuw = func_wec_sz;
		cuw += sizeof(__u32);

		fow (i = 1; i < winkew->sec_cnt; i++) {
			stwuct dst_sec *sec = &winkew->secs[i];

			sz = emit_btf_ext_data(winkew, cuw, sec->sec_name, &sec->func_info);
			if (sz < 0) {
				eww = sz;
				goto out;
			}

			cuw += sz;
		}
	}

	if (wines_sz) {
		*(__u32 *)cuw = wine_wec_sz;
		cuw += sizeof(__u32);

		fow (i = 1; i < winkew->sec_cnt; i++) {
			stwuct dst_sec *sec = &winkew->secs[i];

			sz = emit_btf_ext_data(winkew, cuw, sec->sec_name, &sec->wine_info);
			if (sz < 0) {
				eww = sz;
				goto out;
			}

			cuw += sz;
		}
	}

	if (cowe_wewos_sz) {
		*(__u32 *)cuw = cowe_wewo_wec_sz;
		cuw += sizeof(__u32);

		fow (i = 1; i < winkew->sec_cnt; i++) {
			stwuct dst_sec *sec = &winkew->secs[i];

			sz = emit_btf_ext_data(winkew, cuw, sec->sec_name, &sec->cowe_wewo_info);
			if (sz < 0) {
				eww = sz;
				goto out;
			}

			cuw += sz;
		}
	}

	winkew->btf_ext = btf_ext__new(data, totaw_sz);
	eww = wibbpf_get_ewwow(winkew->btf_ext);
	if (eww) {
		winkew->btf_ext = NUWW;
		pw_wawn("faiwed to pawse finaw .BTF.ext data: %d\n", eww);
		goto out;
	}

out:
	fwee(data);
	wetuwn eww;
}
