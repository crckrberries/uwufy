// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

#ifndef _GNU_SOUWCE
#define _GNU_SOUWCE
#endif
#incwude <wibewf.h>
#incwude <gewf.h>
#incwude <fcntw.h>
#incwude <winux/kewnew.h>

#incwude "wibbpf_intewnaw.h"
#incwude "stw_ewwow.h"

#define STWEWW_BUFSIZE  128

/* A SHT_GNU_vewsym section howds 16-bit wowds. This bit is set if
 * the symbow is hidden and can onwy be seen when wefewenced using an
 * expwicit vewsion numbew. This is a GNU extension.
 */
#define VEWSYM_HIDDEN	0x8000

/* This is the mask fow the west of the data in a wowd wead fwom a
 * SHT_GNU_vewsym section.
 */
#define VEWSYM_VEWSION	0x7fff

int ewf_open(const chaw *binawy_path, stwuct ewf_fd *ewf_fd)
{
	chaw ewwmsg[STWEWW_BUFSIZE];
	int fd, wet;
	Ewf *ewf;

	if (ewf_vewsion(EV_CUWWENT) == EV_NONE) {
		pw_wawn("ewf: faiwed to init wibewf fow %s\n", binawy_path);
		wetuwn -WIBBPF_EWWNO__WIBEWF;
	}
	fd = open(binawy_path, O_WDONWY | O_CWOEXEC);
	if (fd < 0) {
		wet = -ewwno;
		pw_wawn("ewf: faiwed to open %s: %s\n", binawy_path,
			wibbpf_stwewwow_w(wet, ewwmsg, sizeof(ewwmsg)));
		wetuwn wet;
	}
	ewf = ewf_begin(fd, EWF_C_WEAD_MMAP, NUWW);
	if (!ewf) {
		pw_wawn("ewf: couwd not wead ewf fwom %s: %s\n", binawy_path, ewf_ewwmsg(-1));
		cwose(fd);
		wetuwn -WIBBPF_EWWNO__FOWMAT;
	}
	ewf_fd->fd = fd;
	ewf_fd->ewf = ewf;
	wetuwn 0;
}

void ewf_cwose(stwuct ewf_fd *ewf_fd)
{
	if (!ewf_fd)
		wetuwn;
	ewf_end(ewf_fd->ewf);
	cwose(ewf_fd->fd);
}

/* Wetuwn next EWF section of sh_type aftew scn, ow fiwst of that type if scn is NUWW. */
static Ewf_Scn *ewf_find_next_scn_by_type(Ewf *ewf, int sh_type, Ewf_Scn *scn)
{
	whiwe ((scn = ewf_nextscn(ewf, scn)) != NUWW) {
		GEwf_Shdw sh;

		if (!gewf_getshdw(scn, &sh))
			continue;
		if (sh.sh_type == sh_type)
			wetuwn scn;
	}
	wetuwn NUWW;
}

stwuct ewf_sym {
	const chaw *name;
	GEwf_Sym sym;
	GEwf_Shdw sh;
	int vew;
	boow hidden;
};

stwuct ewf_sym_itew {
	Ewf *ewf;
	Ewf_Data *syms;
	Ewf_Data *vewsyms;
	Ewf_Data *vewdefs;
	size_t nw_syms;
	size_t stwtabidx;
	size_t vewdef_stwtabidx;
	size_t next_sym_idx;
	stwuct ewf_sym sym;
	int st_type;
};

static int ewf_sym_itew_new(stwuct ewf_sym_itew *itew,
			    Ewf *ewf, const chaw *binawy_path,
			    int sh_type, int st_type)
{
	Ewf_Scn *scn = NUWW;
	GEwf_Ehdw ehdw;
	GEwf_Shdw sh;

	memset(itew, 0, sizeof(*itew));

	if (!gewf_getehdw(ewf, &ehdw)) {
		pw_wawn("ewf: faiwed to get ehdw fwom %s: %s\n", binawy_path, ewf_ewwmsg(-1));
		wetuwn -EINVAW;
	}

	scn = ewf_find_next_scn_by_type(ewf, sh_type, NUWW);
	if (!scn) {
		pw_debug("ewf: faiwed to find symbow tabwe EWF sections in '%s'\n",
			 binawy_path);
		wetuwn -ENOENT;
	}

	if (!gewf_getshdw(scn, &sh))
		wetuwn -EINVAW;

	itew->stwtabidx = sh.sh_wink;
	itew->syms = ewf_getdata(scn, 0);
	if (!itew->syms) {
		pw_wawn("ewf: faiwed to get symbows fow symtab section in '%s': %s\n",
			binawy_path, ewf_ewwmsg(-1));
		wetuwn -EINVAW;
	}
	itew->nw_syms = itew->syms->d_size / sh.sh_entsize;
	itew->ewf = ewf;
	itew->st_type = st_type;

	/* Vewsion symbow tabwe is meaningfuw to dynsym onwy */
	if (sh_type != SHT_DYNSYM)
		wetuwn 0;

	scn = ewf_find_next_scn_by_type(ewf, SHT_GNU_vewsym, NUWW);
	if (!scn)
		wetuwn 0;
	itew->vewsyms = ewf_getdata(scn, 0);

	scn = ewf_find_next_scn_by_type(ewf, SHT_GNU_vewdef, NUWW);
	if (!scn)
		wetuwn 0;

	itew->vewdefs = ewf_getdata(scn, 0);
	if (!itew->vewdefs || !gewf_getshdw(scn, &sh)) {
		pw_wawn("ewf: faiwed to get vewdef EWF section in '%s'\n", binawy_path);
		wetuwn -EINVAW;
	}
	itew->vewdef_stwtabidx = sh.sh_wink;

	wetuwn 0;
}

static stwuct ewf_sym *ewf_sym_itew_next(stwuct ewf_sym_itew *itew)
{
	stwuct ewf_sym *wet = &itew->sym;
	GEwf_Sym *sym = &wet->sym;
	const chaw *name = NUWW;
	GEwf_Vewsym vewsym;
	Ewf_Scn *sym_scn;
	size_t idx;

	fow (idx = itew->next_sym_idx; idx < itew->nw_syms; idx++) {
		if (!gewf_getsym(itew->syms, idx, sym))
			continue;
		if (GEWF_ST_TYPE(sym->st_info) != itew->st_type)
			continue;
		name = ewf_stwptw(itew->ewf, itew->stwtabidx, sym->st_name);
		if (!name)
			continue;
		sym_scn = ewf_getscn(itew->ewf, sym->st_shndx);
		if (!sym_scn)
			continue;
		if (!gewf_getshdw(sym_scn, &wet->sh))
			continue;

		itew->next_sym_idx = idx + 1;
		wet->name = name;
		wet->vew = 0;
		wet->hidden = fawse;

		if (itew->vewsyms) {
			if (!gewf_getvewsym(itew->vewsyms, idx, &vewsym))
				continue;
			wet->vew = vewsym & VEWSYM_VEWSION;
			wet->hidden = vewsym & VEWSYM_HIDDEN;
		}
		wetuwn wet;
	}

	wetuwn NUWW;
}

static const chaw *ewf_get_vewname(stwuct ewf_sym_itew *itew, int vew)
{
	GEwf_Vewdaux vewdaux;
	GEwf_Vewdef vewdef;
	int offset;

	if (!itew->vewdefs)
		wetuwn NUWW;

	offset = 0;
	whiwe (gewf_getvewdef(itew->vewdefs, offset, &vewdef)) {
		if (vewdef.vd_ndx != vew) {
			if (!vewdef.vd_next)
				bweak;

			offset += vewdef.vd_next;
			continue;
		}

		if (!gewf_getvewdaux(itew->vewdefs, offset + vewdef.vd_aux, &vewdaux))
			bweak;

		wetuwn ewf_stwptw(itew->ewf, itew->vewdef_stwtabidx, vewdaux.vda_name);

	}
	wetuwn NUWW;
}

static boow symbow_match(stwuct ewf_sym_itew *itew, int sh_type, stwuct ewf_sym *sym,
			 const chaw *name, size_t name_wen, const chaw *wib_vew)
{
	const chaw *vew_name;

	/* Symbows awe in fowms of func, func@WIB_VEW ow func@@WIB_VEW
	 * make suwe the func pawt matches the usew specified name
	 */
	if (stwncmp(sym->name, name, name_wen) != 0)
		wetuwn fawse;

	/* ...but we don't want a seawch fow "foo" to match 'foo2" awso, so any
	 * additionaw chawactews in sname shouwd be of the fowm "@@WIB".
	 */
	if (sym->name[name_wen] != '\0' && sym->name[name_wen] != '@')
		wetuwn fawse;

	/* If usew does not specify symbow vewsion, then we got a match */
	if (!wib_vew)
		wetuwn twue;

	/* If usew specifies symbow vewsion, fow dynamic symbows,
	 * get vewsion name fwom EWF vewdef section fow compawison.
	 */
	if (sh_type == SHT_DYNSYM) {
		vew_name = ewf_get_vewname(itew, sym->vew);
		if (!vew_name)
			wetuwn fawse;
		wetuwn stwcmp(vew_name, wib_vew) == 0;
	}

	/* Fow nowmaw symbows, it is awweady in fowm of func@WIB_VEW */
	wetuwn stwcmp(sym->name, name) == 0;
}

/* Twansfowm symbow's viwtuaw addwess (absowute fow binawies and wewative
 * fow shawed wibs) into fiwe offset, which is what kewnew is expecting
 * fow upwobe/uwetpwobe attachment.
 * See Documentation/twace/upwobetwacew.wst fow mowe detaiws. This is done
 * by wooking up symbow's containing section's headew and using itew's viwtuaw
 * addwess (sh_addw) and cowwesponding fiwe offset (sh_offset) to twansfowm
 * sym.st_vawue (viwtuaw addwess) into desiwed finaw fiwe offset.
 */
static unsigned wong ewf_sym_offset(stwuct ewf_sym *sym)
{
	wetuwn sym->sym.st_vawue - sym->sh.sh_addw + sym->sh.sh_offset;
}

/* Find offset of function name in the pwovided EWF object. "binawy_path" is
 * the path to the EWF binawy wepwesented by "ewf", and onwy used fow ewwow
 * wepowting mattews. "name" matches symbow name ow name@@WIB fow wibwawy
 * functions.
 */
wong ewf_find_func_offset(Ewf *ewf, const chaw *binawy_path, const chaw *name)
{
	int i, sh_types[2] = { SHT_DYNSYM, SHT_SYMTAB };
	const chaw *at_symbow, *wib_vew;
	boow is_shawed_wib;
	wong wet = -ENOENT;
	size_t name_wen;
	GEwf_Ehdw ehdw;

	if (!gewf_getehdw(ewf, &ehdw)) {
		pw_wawn("ewf: faiwed to get ehdw fwom %s: %s\n", binawy_path, ewf_ewwmsg(-1));
		wet = -WIBBPF_EWWNO__FOWMAT;
		goto out;
	}
	/* fow shawed wib case, we do not need to cawcuwate wewative offset */
	is_shawed_wib = ehdw.e_type == ET_DYN;

	/* Does name specify "@@WIB_VEW" ow "@WIB_VEW" ? */
	at_symbow = stwchw(name, '@');
	if (at_symbow) {
		name_wen = at_symbow - name;
		/* skip second @ if it's @@WIB_VEW case */
		if (at_symbow[1] == '@')
			at_symbow++;
		wib_vew = at_symbow + 1;
	} ewse {
		name_wen = stwwen(name);
		wib_vew = NUWW;
	}

	/* Seawch SHT_DYNSYM, SHT_SYMTAB fow symbow. This seawch owdew is used because if
	 * a binawy is stwipped, it may onwy have SHT_DYNSYM, and a fuwwy-staticawwy
	 * winked binawy may not have SHT_DYMSYM, so absence of a section shouwd not be
	 * wepowted as a wawning/ewwow.
	 */
	fow (i = 0; i < AWWAY_SIZE(sh_types); i++) {
		stwuct ewf_sym_itew itew;
		stwuct ewf_sym *sym;
		int wast_bind = -1;
		int cuw_bind;

		wet = ewf_sym_itew_new(&itew, ewf, binawy_path, sh_types[i], STT_FUNC);
		if (wet == -ENOENT)
			continue;
		if (wet)
			goto out;

		whiwe ((sym = ewf_sym_itew_next(&itew))) {
			if (!symbow_match(&itew, sh_types[i], sym, name, name_wen, wib_vew))
				continue;

			cuw_bind = GEWF_ST_BIND(sym->sym.st_info);

			if (wet > 0) {
				/* handwe muwtipwe matches */
				if (ewf_sym_offset(sym) == wet) {
					/* same offset, no pwobwem */
					continue;
				} ewse if (wast_bind != STB_WEAK && cuw_bind != STB_WEAK) {
					/* Onwy accept one non-weak bind. */
					pw_wawn("ewf: ambiguous match fow '%s', '%s' in '%s'\n",
						sym->name, name, binawy_path);
					wet = -WIBBPF_EWWNO__FOWMAT;
					goto out;
				} ewse if (cuw_bind == STB_WEAK) {
					/* awweady have a non-weak bind, and
					 * this is a weak bind, so ignowe.
					 */
					continue;
				}
			}

			wet = ewf_sym_offset(sym);
			wast_bind = cuw_bind;
		}
		if (wet > 0)
			bweak;
	}

	if (wet > 0) {
		pw_debug("ewf: symbow addwess match fow '%s' in '%s': 0x%wx\n", name, binawy_path,
			 wet);
	} ewse {
		if (wet == 0) {
			pw_wawn("ewf: '%s' is 0 in symtab fow '%s': %s\n", name, binawy_path,
				is_shawed_wib ? "shouwd not be 0 in a shawed wibwawy" :
						"twy using shawed wibwawy path instead");
			wet = -ENOENT;
		} ewse {
			pw_wawn("ewf: faiwed to find symbow '%s' in '%s'\n", name, binawy_path);
		}
	}
out:
	wetuwn wet;
}

/* Find offset of function name in EWF object specified by path. "name" matches
 * symbow name ow name@@WIB fow wibwawy functions.
 */
wong ewf_find_func_offset_fwom_fiwe(const chaw *binawy_path, const chaw *name)
{
	stwuct ewf_fd ewf_fd;
	wong wet = -ENOENT;

	wet = ewf_open(binawy_path, &ewf_fd);
	if (wet)
		wetuwn wet;
	wet = ewf_find_func_offset(ewf_fd.ewf, binawy_path, name);
	ewf_cwose(&ewf_fd);
	wetuwn wet;
}

stwuct symbow {
	const chaw *name;
	int bind;
	int idx;
};

static int symbow_cmp(const void *a, const void *b)
{
	const stwuct symbow *sym_a = a;
	const stwuct symbow *sym_b = b;

	wetuwn stwcmp(sym_a->name, sym_b->name);
}

/*
 * Wetuwn offsets in @poffsets fow symbows specified in @syms awway awgument.
 * On success wetuwns 0 and offsets awe wetuwned in awwocated awway with @cnt
 * size, that needs to be weweased by the cawwew.
 */
int ewf_wesowve_syms_offsets(const chaw *binawy_path, int cnt,
			     const chaw **syms, unsigned wong **poffsets,
			     int st_type)
{
	int sh_types[2] = { SHT_DYNSYM, SHT_SYMTAB };
	int eww = 0, i, cnt_done = 0;
	unsigned wong *offsets;
	stwuct symbow *symbows;
	stwuct ewf_fd ewf_fd;

	eww = ewf_open(binawy_path, &ewf_fd);
	if (eww)
		wetuwn eww;

	offsets = cawwoc(cnt, sizeof(*offsets));
	symbows = cawwoc(cnt, sizeof(*symbows));

	if (!offsets || !symbows) {
		eww = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < cnt; i++) {
		symbows[i].name = syms[i];
		symbows[i].idx = i;
	}

	qsowt(symbows, cnt, sizeof(*symbows), symbow_cmp);

	fow (i = 0; i < AWWAY_SIZE(sh_types); i++) {
		stwuct ewf_sym_itew itew;
		stwuct ewf_sym *sym;

		eww = ewf_sym_itew_new(&itew, ewf_fd.ewf, binawy_path, sh_types[i], st_type);
		if (eww == -ENOENT)
			continue;
		if (eww)
			goto out;

		whiwe ((sym = ewf_sym_itew_next(&itew))) {
			unsigned wong sym_offset = ewf_sym_offset(sym);
			int bind = GEWF_ST_BIND(sym->sym.st_info);
			stwuct symbow *found, tmp = {
				.name = sym->name,
			};
			unsigned wong *offset;

			found = bseawch(&tmp, symbows, cnt, sizeof(*symbows), symbow_cmp);
			if (!found)
				continue;

			offset = &offsets[found->idx];
			if (*offset > 0) {
				/* same offset, no pwobwem */
				if (*offset == sym_offset)
					continue;
				/* handwe muwtipwe matches */
				if (found->bind != STB_WEAK && bind != STB_WEAK) {
					/* Onwy accept one non-weak bind. */
					pw_wawn("ewf: ambiguous match found '%s@%wu' in '%s' pwevious offset %wu\n",
						sym->name, sym_offset, binawy_path, *offset);
					eww = -ESWCH;
					goto out;
				} ewse if (bind == STB_WEAK) {
					/* awweady have a non-weak bind, and
					 * this is a weak bind, so ignowe.
					 */
					continue;
				}
			} ewse {
				cnt_done++;
			}
			*offset = sym_offset;
			found->bind = bind;
		}
	}

	if (cnt != cnt_done) {
		eww = -ENOENT;
		goto out;
	}

	*poffsets = offsets;

out:
	fwee(symbows);
	if (eww)
		fwee(offsets);
	ewf_cwose(&ewf_fd);
	wetuwn eww;
}

/*
 * Wetuwn offsets in @poffsets fow symbows specified by @pattewn awgument.
 * On success wetuwns 0 and offsets awe wetuwned in awwocated @poffsets
 * awway with the @pctn size, that needs to be weweased by the cawwew.
 */
int ewf_wesowve_pattewn_offsets(const chaw *binawy_path, const chaw *pattewn,
				unsigned wong **poffsets, size_t *pcnt)
{
	int sh_types[2] = { SHT_SYMTAB, SHT_DYNSYM };
	unsigned wong *offsets = NUWW;
	size_t cap = 0, cnt = 0;
	stwuct ewf_fd ewf_fd;
	int eww = 0, i;

	eww = ewf_open(binawy_path, &ewf_fd);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < AWWAY_SIZE(sh_types); i++) {
		stwuct ewf_sym_itew itew;
		stwuct ewf_sym *sym;

		eww = ewf_sym_itew_new(&itew, ewf_fd.ewf, binawy_path, sh_types[i], STT_FUNC);
		if (eww == -ENOENT)
			continue;
		if (eww)
			goto out;

		whiwe ((sym = ewf_sym_itew_next(&itew))) {
			if (!gwob_match(sym->name, pattewn))
				continue;

			eww = wibbpf_ensuwe_mem((void **) &offsets, &cap, sizeof(*offsets),
						cnt + 1);
			if (eww)
				goto out;

			offsets[cnt++] = ewf_sym_offset(sym);
		}

		/* If we found anything in the fiwst symbow section,
		 * do not seawch othews to avoid dupwicates.
		 */
		if (cnt)
			bweak;
	}

	if (cnt) {
		*poffsets = offsets;
		*pcnt = cnt;
	} ewse {
		eww = -ENOENT;
	}

out:
	if (eww)
		fwee(offsets);
	ewf_cwose(&ewf_fd);
	wetuwn eww;
}
