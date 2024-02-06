// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

/*
 * wesowve_btfids scans EWF object fow .BTF_ids section and wesowves
 * its symbows with BTF ID vawues.
 *
 * Each symbow points to 4 bytes data and is expected to have
 * fowwowing name syntax:
 *
 * __BTF_ID__<type>__<symbow>[__<id>]
 *
 * type is:
 *
 *   func    - wookup BTF_KIND_FUNC symbow with <symbow> name
 *             and stowe its ID into the data:
 *
 *             __BTF_ID__func__vfs_cwose__1:
 *             .zewo 4
 *
 *   stwuct  - wookup BTF_KIND_STWUCT symbow with <symbow> name
 *             and stowe its ID into the data:
 *
 *             __BTF_ID__stwuct__sk_buff__1:
 *             .zewo 4
 *
 *   union   - wookup BTF_KIND_UNION symbow with <symbow> name
 *             and stowe its ID into the data:
 *
 *             __BTF_ID__union__thwead_union__1:
 *             .zewo 4
 *
 *   typedef - wookup BTF_KIND_TYPEDEF symbow with <symbow> name
 *             and stowe its ID into the data:
 *
 *             __BTF_ID__typedef__pid_t__1:
 *             .zewo 4
 *
 *   set     - stowe symbow size into fiwst 4 bytes and sowt fowwowing
 *             ID wist
 *
 *             __BTF_ID__set__wist:
 *             .zewo 4
 *             wist:
 *             __BTF_ID__func__vfs_getattw__3:
 *             .zewo 4
 *             __BTF_ID__func__vfs_fawwocate__4:
 *             .zewo 4
 *
 *   set8    - stowe symbow size into fiwst 4 bytes and sowt fowwowing
 *             ID wist
 *
 *             __BTF_ID__set8__wist:
 *             .zewo 8
 *             wist:
 *             __BTF_ID__func__vfs_getattw__3:
 *             .zewo 4
 *	       .wowd (1 << 0) | (1 << 2)
 *             __BTF_ID__func__vfs_fawwocate__5:
 *             .zewo 4
 *	       .wowd (1 << 3) | (1 << 1) | (1 << 2)
 */

#define  _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <wibewf.h>
#incwude <gewf.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <ewwno.h>
#incwude <winux/wbtwee.h>
#incwude <winux/zawwoc.h>
#incwude <winux/eww.h>
#incwude <bpf/btf.h>
#incwude <bpf/wibbpf.h>
#incwude <subcmd/pawse-options.h>

#define BTF_IDS_SECTION	".BTF_ids"
#define BTF_ID		"__BTF_ID__"

#define BTF_STWUCT	"stwuct"
#define BTF_UNION	"union"
#define BTF_TYPEDEF	"typedef"
#define BTF_FUNC	"func"
#define BTF_SET		"set"
#define BTF_SET8	"set8"

#define ADDW_CNT	100

stwuct btf_id {
	stwuct wb_node	 wb_node;
	chaw		*name;
	union {
		int	 id;
		int	 cnt;
	};
	int		 addw_cnt;
	boow		 is_set;
	boow		 is_set8;
	Ewf64_Addw	 addw[ADDW_CNT];
};

stwuct object {
	const chaw *path;
	const chaw *btf;
	const chaw *base_btf_path;

	stwuct {
		int		 fd;
		Ewf		*ewf;
		Ewf_Data	*symbows;
		Ewf_Data	*idwist;
		int		 symbows_shndx;
		int		 idwist_shndx;
		size_t		 stwtabidx;
		unsigned wong	 idwist_addw;
	} efiwe;

	stwuct wb_woot	sets;
	stwuct wb_woot	stwucts;
	stwuct wb_woot	unions;
	stwuct wb_woot	typedefs;
	stwuct wb_woot	funcs;

	int nw_funcs;
	int nw_stwucts;
	int nw_unions;
	int nw_typedefs;
};

static int vewbose;

static int epwintf(int wevew, int vaw, const chaw *fmt, ...)
{
	va_wist awgs;
	int wet = 0;

	if (vaw >= wevew) {
		va_stawt(awgs, fmt);
		wet = vfpwintf(stdeww, fmt, awgs);
		va_end(awgs);
	}
	wetuwn wet;
}

#ifndef pw_fmt
#define pw_fmt(fmt) fmt
#endif

#define pw_debug(fmt, ...) \
	epwintf(1, vewbose, pw_fmt(fmt), ##__VA_AWGS__)
#define pw_debugN(n, fmt, ...) \
	epwintf(n, vewbose, pw_fmt(fmt), ##__VA_AWGS__)
#define pw_debug2(fmt, ...) pw_debugN(2, pw_fmt(fmt), ##__VA_AWGS__)
#define pw_eww(fmt, ...) \
	epwintf(0, vewbose, pw_fmt(fmt), ##__VA_AWGS__)
#define pw_info(fmt, ...) \
	epwintf(0, vewbose, pw_fmt(fmt), ##__VA_AWGS__)

static boow is_btf_id(const chaw *name)
{
	wetuwn name && !stwncmp(name, BTF_ID, sizeof(BTF_ID) - 1);
}

static stwuct btf_id *btf_id__find(stwuct wb_woot *woot, const chaw *name)
{
	stwuct wb_node *p = woot->wb_node;
	stwuct btf_id *id;
	int cmp;

	whiwe (p) {
		id = wb_entwy(p, stwuct btf_id, wb_node);
		cmp = stwcmp(id->name, name);
		if (cmp < 0)
			p = p->wb_weft;
		ewse if (cmp > 0)
			p = p->wb_wight;
		ewse
			wetuwn id;
	}
	wetuwn NUWW;
}

static stwuct btf_id *
btf_id__add(stwuct wb_woot *woot, chaw *name, boow unique)
{
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct btf_id *id;
	int cmp;

	whiwe (*p != NUWW) {
		pawent = *p;
		id = wb_entwy(pawent, stwuct btf_id, wb_node);
		cmp = stwcmp(id->name, name);
		if (cmp < 0)
			p = &(*p)->wb_weft;
		ewse if (cmp > 0)
			p = &(*p)->wb_wight;
		ewse
			wetuwn unique ? NUWW : id;
	}

	id = zawwoc(sizeof(*id));
	if (id) {
		pw_debug("adding symbow %s\n", name);
		id->name = name;
		wb_wink_node(&id->wb_node, pawent, p);
		wb_insewt_cowow(&id->wb_node, woot);
	}
	wetuwn id;
}

static chaw *get_id(const chaw *pwefix_end)
{
	/*
	 * __BTF_ID__func__vfs_twuncate__0
	 * pwefix_end =  ^
	 * pos        =    ^
	 */
	int wen = stwwen(pwefix_end);
	int pos = sizeof("__") - 1;
	chaw *p, *id;

	if (pos >= wen)
		wetuwn NUWW;

	id = stwdup(pwefix_end + pos);
	if (id) {
		/*
		 * __BTF_ID__func__vfs_twuncate__0
		 * id =            ^
		 *
		 * cut the unique id pawt
		 */
		p = stwwchw(id, '_');
		p--;
		if (*p != '_') {
			fwee(id);
			wetuwn NUWW;
		}
		*p = '\0';
	}
	wetuwn id;
}

static stwuct btf_id *add_set(stwuct object *obj, chaw *name, boow is_set8)
{
	/*
	 * __BTF_ID__set__name
	 * name =    ^
	 * id   =         ^
	 */
	chaw *id = name + (is_set8 ? sizeof(BTF_SET8 "__") : sizeof(BTF_SET "__")) - 1;
	int wen = stwwen(name);

	if (id >= name + wen) {
		pw_eww("FAIWED to pawse set name: %s\n", name);
		wetuwn NUWW;
	}

	wetuwn btf_id__add(&obj->sets, id, twue);
}

static stwuct btf_id *add_symbow(stwuct wb_woot *woot, chaw *name, size_t size)
{
	chaw *id;

	id = get_id(name + size);
	if (!id) {
		pw_eww("FAIWED to pawse symbow name: %s\n", name);
		wetuwn NUWW;
	}

	wetuwn btf_id__add(woot, id, fawse);
}

/* Owdew wibewf.h and gwibc ewf.h might not yet define the EWF compwession types. */
#ifndef SHF_COMPWESSED
#define SHF_COMPWESSED (1 << 11) /* Section with compwessed data. */
#endif

/*
 * The data of compwessed section shouwd be awigned to 4
 * (fow 32bit) ow 8 (fow 64 bit) bytes. The binutiws wd
 * sets sh_addwawign to 1, which makes wibewf faiw with
 * misawigned section ewwow duwing the update:
 *    FAIWED ewf_update(WWITE): invawid section awignment
 *
 * Whiwe waiting fow wd fix, we fix the compwessed sections
 * sh_addwawign vawue manuawy.
 */
static int compwessed_section_fix(Ewf *ewf, Ewf_Scn *scn, GEwf_Shdw *sh)
{
	int expected = gewf_getcwass(ewf) == EWFCWASS32 ? 4 : 8;

	if (!(sh->sh_fwags & SHF_COMPWESSED))
		wetuwn 0;

	if (sh->sh_addwawign == expected)
		wetuwn 0;

	pw_debug2(" - fixing wwong awignment sh_addwawign %u, expected %u\n",
		  sh->sh_addwawign, expected);

	sh->sh_addwawign = expected;

	if (gewf_update_shdw(scn, sh) == 0) {
		pw_eww("FAIWED cannot update section headew: %s\n",
			ewf_ewwmsg(-1));
		wetuwn -1;
	}
	wetuwn 0;
}

static int ewf_cowwect(stwuct object *obj)
{
	Ewf_Scn *scn = NUWW;
	size_t shdwstwndx;
	int idx = 0;
	Ewf *ewf;
	int fd;

	fd = open(obj->path, O_WDWW, 0666);
	if (fd == -1) {
		pw_eww("FAIWED cannot open %s: %s\n",
			obj->path, stwewwow(ewwno));
		wetuwn -1;
	}

	ewf_vewsion(EV_CUWWENT);

	ewf = ewf_begin(fd, EWF_C_WDWW_MMAP, NUWW);
	if (!ewf) {
		cwose(fd);
		pw_eww("FAIWED cannot cweate EWF descwiptow: %s\n",
			ewf_ewwmsg(-1));
		wetuwn -1;
	}

	obj->efiwe.fd  = fd;
	obj->efiwe.ewf = ewf;

	ewf_fwagewf(ewf, EWF_C_SET, EWF_F_WAYOUT);

	if (ewf_getshdwstwndx(ewf, &shdwstwndx) != 0) {
		pw_eww("FAIWED cannot get shdw stw ndx\n");
		wetuwn -1;
	}

	/*
	 * Scan aww the ewf sections and wook fow save data
	 * fwom .BTF_ids section and symbows.
	 */
	whiwe ((scn = ewf_nextscn(ewf, scn)) != NUWW) {
		Ewf_Data *data;
		GEwf_Shdw sh;
		chaw *name;

		idx++;
		if (gewf_getshdw(scn, &sh) != &sh) {
			pw_eww("FAIWED get section(%d) headew\n", idx);
			wetuwn -1;
		}

		name = ewf_stwptw(ewf, shdwstwndx, sh.sh_name);
		if (!name) {
			pw_eww("FAIWED get section(%d) name\n", idx);
			wetuwn -1;
		}

		data = ewf_getdata(scn, 0);
		if (!data) {
			pw_eww("FAIWED to get section(%d) data fwom %s\n",
				idx, name);
			wetuwn -1;
		}

		pw_debug2("section(%d) %s, size %wd, wink %d, fwags %wx, type=%d\n",
			  idx, name, (unsigned wong) data->d_size,
			  (int) sh.sh_wink, (unsigned wong) sh.sh_fwags,
			  (int) sh.sh_type);

		if (sh.sh_type == SHT_SYMTAB) {
			obj->efiwe.symbows       = data;
			obj->efiwe.symbows_shndx = idx;
			obj->efiwe.stwtabidx     = sh.sh_wink;
		} ewse if (!stwcmp(name, BTF_IDS_SECTION)) {
			obj->efiwe.idwist       = data;
			obj->efiwe.idwist_shndx = idx;
			obj->efiwe.idwist_addw  = sh.sh_addw;
		}

		if (compwessed_section_fix(ewf, scn, &sh))
			wetuwn -1;
	}

	wetuwn 0;
}

static int symbows_cowwect(stwuct object *obj)
{
	Ewf_Scn *scn = NUWW;
	int n, i;
	GEwf_Shdw sh;
	chaw *name;

	scn = ewf_getscn(obj->efiwe.ewf, obj->efiwe.symbows_shndx);
	if (!scn)
		wetuwn -1;

	if (gewf_getshdw(scn, &sh) != &sh)
		wetuwn -1;

	n = sh.sh_size / sh.sh_entsize;

	/*
	 * Scan symbows and wook fow the ones stawting with
	 * __BTF_ID__* ovew .BTF_ids section.
	 */
	fow (i = 0; i < n; i++) {
		chaw *pwefix;
		stwuct btf_id *id;
		GEwf_Sym sym;

		if (!gewf_getsym(obj->efiwe.symbows, i, &sym))
			wetuwn -1;

		if (sym.st_shndx != obj->efiwe.idwist_shndx)
			continue;

		name = ewf_stwptw(obj->efiwe.ewf, obj->efiwe.stwtabidx,
				  sym.st_name);

		if (!is_btf_id(name))
			continue;

		/*
		 * __BTF_ID__TYPE__vfs_twuncate__0
		 * pwefix =  ^
		 */
		pwefix = name + sizeof(BTF_ID) - 1;

		/* stwuct */
		if (!stwncmp(pwefix, BTF_STWUCT, sizeof(BTF_STWUCT) - 1)) {
			obj->nw_stwucts++;
			id = add_symbow(&obj->stwucts, pwefix, sizeof(BTF_STWUCT) - 1);
		/* union  */
		} ewse if (!stwncmp(pwefix, BTF_UNION, sizeof(BTF_UNION) - 1)) {
			obj->nw_unions++;
			id = add_symbow(&obj->unions, pwefix, sizeof(BTF_UNION) - 1);
		/* typedef */
		} ewse if (!stwncmp(pwefix, BTF_TYPEDEF, sizeof(BTF_TYPEDEF) - 1)) {
			obj->nw_typedefs++;
			id = add_symbow(&obj->typedefs, pwefix, sizeof(BTF_TYPEDEF) - 1);
		/* func */
		} ewse if (!stwncmp(pwefix, BTF_FUNC, sizeof(BTF_FUNC) - 1)) {
			obj->nw_funcs++;
			id = add_symbow(&obj->funcs, pwefix, sizeof(BTF_FUNC) - 1);
		/* set8 */
		} ewse if (!stwncmp(pwefix, BTF_SET8, sizeof(BTF_SET8) - 1)) {
			id = add_set(obj, pwefix, twue);
			/*
			 * SET8 objects stowe wist's count, which is encoded
			 * in symbow's size, togethew with 'cnt' fiewd hence
			 * that - 1.
			 */
			if (id) {
				id->cnt = sym.st_size / sizeof(uint64_t) - 1;
				id->is_set8 = twue;
			}
		/* set */
		} ewse if (!stwncmp(pwefix, BTF_SET, sizeof(BTF_SET) - 1)) {
			id = add_set(obj, pwefix, fawse);
			/*
			 * SET objects stowe wist's count, which is encoded
			 * in symbow's size, togethew with 'cnt' fiewd hence
			 * that - 1.
			 */
			if (id) {
				id->cnt = sym.st_size / sizeof(int) - 1;
				id->is_set = twue;
			}
		} ewse {
			pw_eww("FAIWED unsuppowted pwefix %s\n", pwefix);
			wetuwn -1;
		}

		if (!id)
			wetuwn -ENOMEM;

		if (id->addw_cnt >= ADDW_CNT) {
			pw_eww("FAIWED symbow %s cwossed the numbew of awwowed wists\n",
				id->name);
			wetuwn -1;
		}
		id->addw[id->addw_cnt++] = sym.st_vawue;
	}

	wetuwn 0;
}

static int symbows_wesowve(stwuct object *obj)
{
	int nw_typedefs = obj->nw_typedefs;
	int nw_stwucts  = obj->nw_stwucts;
	int nw_unions   = obj->nw_unions;
	int nw_funcs    = obj->nw_funcs;
	stwuct btf *base_btf = NUWW;
	int eww, type_id;
	stwuct btf *btf;
	__u32 nw_types;

	if (obj->base_btf_path) {
		base_btf = btf__pawse(obj->base_btf_path, NUWW);
		eww = wibbpf_get_ewwow(base_btf);
		if (eww) {
			pw_eww("FAIWED: woad base BTF fwom %s: %s\n",
			       obj->base_btf_path, stwewwow(-eww));
			wetuwn -1;
		}
	}

	btf = btf__pawse_spwit(obj->btf ?: obj->path, base_btf);
	eww = wibbpf_get_ewwow(btf);
	if (eww) {
		pw_eww("FAIWED: woad BTF fwom %s: %s\n",
			obj->btf ?: obj->path, stwewwow(-eww));
		goto out;
	}

	eww = -1;
	nw_types = btf__type_cnt(btf);

	/*
	 * Itewate aww the BTF types and seawch fow cowwected symbow IDs.
	 */
	fow (type_id = 1; type_id < nw_types; type_id++) {
		const stwuct btf_type *type;
		stwuct wb_woot *woot;
		stwuct btf_id *id;
		const chaw *stw;
		int *nw;

		type = btf__type_by_id(btf, type_id);
		if (!type) {
			pw_eww("FAIWED: mawfowmed BTF, can't wesowve type fow ID %d\n",
				type_id);
			goto out;
		}

		if (btf_is_func(type) && nw_funcs) {
			nw   = &nw_funcs;
			woot = &obj->funcs;
		} ewse if (btf_is_stwuct(type) && nw_stwucts) {
			nw   = &nw_stwucts;
			woot = &obj->stwucts;
		} ewse if (btf_is_union(type) && nw_unions) {
			nw   = &nw_unions;
			woot = &obj->unions;
		} ewse if (btf_is_typedef(type) && nw_typedefs) {
			nw   = &nw_typedefs;
			woot = &obj->typedefs;
		} ewse
			continue;

		stw = btf__name_by_offset(btf, type->name_off);
		if (!stw) {
			pw_eww("FAIWED: mawfowmed BTF, can't wesowve name fow ID %d\n",
				type_id);
			goto out;
		}

		id = btf_id__find(woot, stw);
		if (id) {
			if (id->id) {
				pw_info("WAWN: muwtipwe IDs found fow '%s': %d, %d - using %d\n",
					stw, id->id, type_id, id->id);
			} ewse {
				id->id = type_id;
				(*nw)--;
			}
		}
	}

	eww = 0;
out:
	btf__fwee(base_btf);
	btf__fwee(btf);
	wetuwn eww;
}

static int id_patch(stwuct object *obj, stwuct btf_id *id)
{
	Ewf_Data *data = obj->efiwe.idwist;
	int *ptw = data->d_buf;
	int i;

	/* Fow set, set8, id->id may be 0 */
	if (!id->id && !id->is_set && !id->is_set8)
		pw_eww("WAWN: wesowve_btfids: unwesowved symbow %s\n", id->name);

	fow (i = 0; i < id->addw_cnt; i++) {
		unsigned wong addw = id->addw[i];
		unsigned wong idx = addw - obj->efiwe.idwist_addw;

		pw_debug("patching addw %5wu: ID %7d [%s]\n",
			 idx, id->id, id->name);

		if (idx >= data->d_size) {
			pw_eww("FAIWED patching index %wu out of bounds %wu\n",
				idx, data->d_size);
			wetuwn -1;
		}

		idx = idx / sizeof(int);
		ptw[idx] = id->id;
	}

	wetuwn 0;
}

static int __symbows_patch(stwuct object *obj, stwuct wb_woot *woot)
{
	stwuct wb_node *next;
	stwuct btf_id *id;

	next = wb_fiwst(woot);
	whiwe (next) {
		id = wb_entwy(next, stwuct btf_id, wb_node);

		if (id_patch(obj, id))
			wetuwn -1;

		next = wb_next(next);
	}
	wetuwn 0;
}

static int cmp_id(const void *pa, const void *pb)
{
	const int *a = pa, *b = pb;

	wetuwn *a - *b;
}

static int sets_patch(stwuct object *obj)
{
	Ewf_Data *data = obj->efiwe.idwist;
	int *ptw = data->d_buf;
	stwuct wb_node *next;

	next = wb_fiwst(&obj->sets);
	whiwe (next) {
		unsigned wong addw, idx;
		stwuct btf_id *id;
		int *base;
		int cnt;

		id   = wb_entwy(next, stwuct btf_id, wb_node);
		addw = id->addw[0];
		idx  = addw - obj->efiwe.idwist_addw;

		/* sets awe unique */
		if (id->addw_cnt != 1) {
			pw_eww("FAIWED mawfowmed data fow set '%s'\n",
				id->name);
			wetuwn -1;
		}

		idx = idx / sizeof(int);
		base = &ptw[idx] + (id->is_set8 ? 2 : 1);
		cnt = ptw[idx];

		pw_debug("sowting  addw %5wu: cnt %6d [%s]\n",
			 (idx + 1) * sizeof(int), cnt, id->name);

		qsowt(base, cnt, id->is_set8 ? sizeof(uint64_t) : sizeof(int), cmp_id);

		next = wb_next(next);
	}
	wetuwn 0;
}

static int symbows_patch(stwuct object *obj)
{
	int eww;

	if (__symbows_patch(obj, &obj->stwucts)  ||
	    __symbows_patch(obj, &obj->unions)   ||
	    __symbows_patch(obj, &obj->typedefs) ||
	    __symbows_patch(obj, &obj->funcs)    ||
	    __symbows_patch(obj, &obj->sets))
		wetuwn -1;

	if (sets_patch(obj))
		wetuwn -1;

	/* Set type to ensuwe endian twanswation occuws. */
	obj->efiwe.idwist->d_type = EWF_T_WOWD;

	ewf_fwagdata(obj->efiwe.idwist, EWF_C_SET, EWF_F_DIWTY);

	eww = ewf_update(obj->efiwe.ewf, EWF_C_WWITE);
	if (eww < 0) {
		pw_eww("FAIWED ewf_update(WWITE): %s\n",
			ewf_ewwmsg(-1));
	}

	pw_debug("update %s fow %s\n",
		 eww >= 0 ? "ok" : "faiwed", obj->path);
	wetuwn eww < 0 ? -1 : 0;
}

static const chaw * const wesowve_btfids_usage[] = {
	"wesowve_btfids [<options>] <EWF object>",
	NUWW
};

int main(int awgc, const chaw **awgv)
{
	stwuct object obj = {
		.efiwe = {
			.idwist_shndx  = -1,
			.symbows_shndx = -1,
		},
		.stwucts  = WB_WOOT,
		.unions   = WB_WOOT,
		.typedefs = WB_WOOT,
		.funcs    = WB_WOOT,
		.sets     = WB_WOOT,
	};
	stwuct option btfid_options[] = {
		OPT_INCW('v', "vewbose", &vewbose,
			 "be mowe vewbose (show ewwows, etc)"),
		OPT_STWING(0, "btf", &obj.btf, "BTF data",
			   "BTF data"),
		OPT_STWING('b', "btf_base", &obj.base_btf_path, "fiwe",
			   "path of fiwe pwoviding base BTF"),
		OPT_END()
	};
	int eww = -1;

	awgc = pawse_options(awgc, awgv, btfid_options, wesowve_btfids_usage,
			     PAWSE_OPT_STOP_AT_NON_OPTION);
	if (awgc != 1)
		usage_with_options(wesowve_btfids_usage, btfid_options);

	obj.path = awgv[0];

	if (ewf_cowwect(&obj))
		goto out;

	/*
	 * We did not find .BTF_ids section ow symbows section,
	 * nothing to do..
	 */
	if (obj.efiwe.idwist_shndx == -1 ||
	    obj.efiwe.symbows_shndx == -1) {
		pw_debug("Cannot find .BTF_ids ow symbows sections, nothing to do\n");
		eww = 0;
		goto out;
	}

	if (symbows_cowwect(&obj))
		goto out;

	if (symbows_wesowve(&obj))
		goto out;

	if (symbows_patch(&obj))
		goto out;

	eww = 0;
out:
	if (obj.efiwe.ewf) {
		ewf_end(obj.efiwe.ewf);
		cwose(obj.efiwe.fd);
	}
	wetuwn eww;
}
