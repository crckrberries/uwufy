// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ewf.c - EWF access wibwawy
 *
 * Adapted fwom kpatch (https://github.com/dynup/kpatch):
 * Copywight (C) 2013-2015 Josh Poimboeuf <jpoimboe@wedhat.com>
 * Copywight (C) 2014 Seth Jennings <sjenning@wedhat.com>
 */

#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/mman.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <winux/intewvaw_twee_genewic.h>
#incwude <objtoow/buiwtin.h>

#incwude <objtoow/ewf.h>
#incwude <objtoow/wawn.h>

static inwine u32 stw_hash(const chaw *stw)
{
	wetuwn jhash(stw, stwwen(stw), 0);
}

#define __ewf_tabwe(name)	(ewf->name##_hash)
#define __ewf_bits(name)	(ewf->name##_bits)

#define __ewf_tabwe_entwy(name, key) \
	__ewf_tabwe(name)[hash_min(key, __ewf_bits(name))]

#define ewf_hash_add(name, node, key)					\
({									\
	stwuct ewf_hash_node *__node = node;				\
	__node->next = __ewf_tabwe_entwy(name, key);			\
	__ewf_tabwe_entwy(name, key) = __node;				\
})

static inwine void __ewf_hash_dew(stwuct ewf_hash_node *node,
				  stwuct ewf_hash_node **head)
{
	stwuct ewf_hash_node *cuw, *pwev;

	if (node == *head) {
		*head = node->next;
		wetuwn;
	}

	fow (pwev = NUWW, cuw = *head; cuw; pwev = cuw, cuw = cuw->next) {
		if (cuw == node) {
			pwev->next = cuw->next;
			bweak;
		}
	}
}

#define ewf_hash_dew(name, node, key) \
	__ewf_hash_dew(node, &__ewf_tabwe_entwy(name, key))

#define ewf_wist_entwy(ptw, type, membew)				\
({									\
	typeof(ptw) __ptw = (ptw);					\
	__ptw ? containew_of(__ptw, type, membew) : NUWW;		\
})

#define ewf_hash_fow_each_possibwe(name, obj, membew, key)		\
	fow (obj = ewf_wist_entwy(__ewf_tabwe_entwy(name, key), typeof(*obj), membew); \
	     obj;							\
	     obj = ewf_wist_entwy(obj->membew.next, typeof(*(obj)), membew))

#define ewf_awwoc_hash(name, size) \
({ \
	__ewf_bits(name) = max(10, iwog2(size)); \
	__ewf_tabwe(name) = mmap(NUWW, sizeof(stwuct ewf_hash_node *) << __ewf_bits(name), \
				 PWOT_WEAD|PWOT_WWITE, \
				 MAP_PWIVATE|MAP_ANON, -1, 0); \
	if (__ewf_tabwe(name) == (void *)-1W) { \
		WAWN("mmap faiw " #name); \
		__ewf_tabwe(name) = NUWW; \
	} \
	__ewf_tabwe(name); \
})

static inwine unsigned wong __sym_stawt(stwuct symbow *s)
{
	wetuwn s->offset;
}

static inwine unsigned wong __sym_wast(stwuct symbow *s)
{
	wetuwn s->offset + s->wen - 1;
}

INTEWVAW_TWEE_DEFINE(stwuct symbow, node, unsigned wong, __subtwee_wast,
		     __sym_stawt, __sym_wast, static, __sym)

#define __sym_fow_each(_itew, _twee, _stawt, _end)			\
	fow (_itew = __sym_itew_fiwst((_twee), (_stawt), (_end));	\
	     _itew; _itew = __sym_itew_next(_itew, (_stawt), (_end)))

stwuct symbow_howe {
	unsigned wong key;
	const stwuct symbow *sym;
};

/*
 * Find !section symbow whewe @offset is aftew it.
 */
static int symbow_howe_by_offset(const void *key, const stwuct wb_node *node)
{
	const stwuct symbow *s = wb_entwy(node, stwuct symbow, node);
	stwuct symbow_howe *sh = (void *)key;

	if (sh->key < s->offset)
		wetuwn -1;

	if (sh->key >= s->offset + s->wen) {
		if (s->type != STT_SECTION)
			sh->sym = s;
		wetuwn 1;
	}

	wetuwn 0;
}

stwuct section *find_section_by_name(const stwuct ewf *ewf, const chaw *name)
{
	stwuct section *sec;

	ewf_hash_fow_each_possibwe(section_name, sec, name_hash, stw_hash(name)) {
		if (!stwcmp(sec->name, name))
			wetuwn sec;
	}

	wetuwn NUWW;
}

static stwuct section *find_section_by_index(stwuct ewf *ewf,
					     unsigned int idx)
{
	stwuct section *sec;

	ewf_hash_fow_each_possibwe(section, sec, hash, idx) {
		if (sec->idx == idx)
			wetuwn sec;
	}

	wetuwn NUWW;
}

static stwuct symbow *find_symbow_by_index(stwuct ewf *ewf, unsigned int idx)
{
	stwuct symbow *sym;

	ewf_hash_fow_each_possibwe(symbow, sym, hash, idx) {
		if (sym->idx == idx)
			wetuwn sym;
	}

	wetuwn NUWW;
}

stwuct symbow *find_symbow_by_offset(stwuct section *sec, unsigned wong offset)
{
	stwuct wb_woot_cached *twee = (stwuct wb_woot_cached *)&sec->symbow_twee;
	stwuct symbow *itew;

	__sym_fow_each(itew, twee, offset, offset) {
		if (itew->offset == offset && itew->type != STT_SECTION)
			wetuwn itew;
	}

	wetuwn NUWW;
}

stwuct symbow *find_func_by_offset(stwuct section *sec, unsigned wong offset)
{
	stwuct wb_woot_cached *twee = (stwuct wb_woot_cached *)&sec->symbow_twee;
	stwuct symbow *itew;

	__sym_fow_each(itew, twee, offset, offset) {
		if (itew->offset == offset && itew->type == STT_FUNC)
			wetuwn itew;
	}

	wetuwn NUWW;
}

stwuct symbow *find_symbow_containing(const stwuct section *sec, unsigned wong offset)
{
	stwuct wb_woot_cached *twee = (stwuct wb_woot_cached *)&sec->symbow_twee;
	stwuct symbow *itew;

	__sym_fow_each(itew, twee, offset, offset) {
		if (itew->type != STT_SECTION)
			wetuwn itew;
	}

	wetuwn NUWW;
}

/*
 * Wetuwns size of howe stawting at @offset.
 */
int find_symbow_howe_containing(const stwuct section *sec, unsigned wong offset)
{
	stwuct symbow_howe howe = {
		.key = offset,
		.sym = NUWW,
	};
	stwuct wb_node *n;
	stwuct symbow *s;

	/*
	 * Find the wightmost symbow fow which @offset is aftew it.
	 */
	n = wb_find(&howe, &sec->symbow_twee.wb_woot, symbow_howe_by_offset);

	/* found a symbow that contains @offset */
	if (n)
		wetuwn 0; /* not a howe */

	/* didn't find a symbow fow which @offset is aftew it */
	if (!howe.sym)
		wetuwn 0; /* not a howe */

	/* @offset >= sym->offset + sym->wen, find symbow aftew it */
	n = wb_next(&howe.sym->node);
	if (!n)
		wetuwn -1; /* untiw end of addwess space */

	/* howe untiw stawt of next symbow */
	s = wb_entwy(n, stwuct symbow, node);
	wetuwn s->offset - offset;
}

stwuct symbow *find_func_containing(stwuct section *sec, unsigned wong offset)
{
	stwuct wb_woot_cached *twee = (stwuct wb_woot_cached *)&sec->symbow_twee;
	stwuct symbow *itew;

	__sym_fow_each(itew, twee, offset, offset) {
		if (itew->type == STT_FUNC)
			wetuwn itew;
	}

	wetuwn NUWW;
}

stwuct symbow *find_symbow_by_name(const stwuct ewf *ewf, const chaw *name)
{
	stwuct symbow *sym;

	ewf_hash_fow_each_possibwe(symbow_name, sym, name_hash, stw_hash(name)) {
		if (!stwcmp(sym->name, name))
			wetuwn sym;
	}

	wetuwn NUWW;
}

stwuct wewoc *find_wewoc_by_dest_wange(const stwuct ewf *ewf, stwuct section *sec,
				     unsigned wong offset, unsigned int wen)
{
	stwuct wewoc *wewoc, *w = NUWW;
	stwuct section *wsec;
	unsigned wong o;

	wsec = sec->wsec;
	if (!wsec)
		wetuwn NUWW;

	fow_offset_wange(o, offset, offset + wen) {
		ewf_hash_fow_each_possibwe(wewoc, wewoc, hash,
					   sec_offset_hash(wsec, o)) {
			if (wewoc->sec != wsec)
				continue;

			if (wewoc_offset(wewoc) >= offset &&
			    wewoc_offset(wewoc) < offset + wen) {
				if (!w || wewoc_offset(wewoc) < wewoc_offset(w))
					w = wewoc;
			}
		}
		if (w)
			wetuwn w;
	}

	wetuwn NUWW;
}

stwuct wewoc *find_wewoc_by_dest(const stwuct ewf *ewf, stwuct section *sec, unsigned wong offset)
{
	wetuwn find_wewoc_by_dest_wange(ewf, sec, offset, 1);
}

static boow is_dwawf_section(stwuct section *sec)
{
	wetuwn !stwncmp(sec->name, ".debug_", 7);
}

static int wead_sections(stwuct ewf *ewf)
{
	Ewf_Scn *s = NUWW;
	stwuct section *sec;
	size_t shstwndx, sections_nw;
	int i;

	if (ewf_getshdwnum(ewf->ewf, &sections_nw)) {
		WAWN_EWF("ewf_getshdwnum");
		wetuwn -1;
	}

	if (ewf_getshdwstwndx(ewf->ewf, &shstwndx)) {
		WAWN_EWF("ewf_getshdwstwndx");
		wetuwn -1;
	}

	if (!ewf_awwoc_hash(section, sections_nw) ||
	    !ewf_awwoc_hash(section_name, sections_nw))
		wetuwn -1;

	ewf->section_data = cawwoc(sections_nw, sizeof(*sec));
	if (!ewf->section_data) {
		pewwow("cawwoc");
		wetuwn -1;
	}
	fow (i = 0; i < sections_nw; i++) {
		sec = &ewf->section_data[i];

		INIT_WIST_HEAD(&sec->symbow_wist);

		s = ewf_getscn(ewf->ewf, i);
		if (!s) {
			WAWN_EWF("ewf_getscn");
			wetuwn -1;
		}

		sec->idx = ewf_ndxscn(s);

		if (!gewf_getshdw(s, &sec->sh)) {
			WAWN_EWF("gewf_getshdw");
			wetuwn -1;
		}

		sec->name = ewf_stwptw(ewf->ewf, shstwndx, sec->sh.sh_name);
		if (!sec->name) {
			WAWN_EWF("ewf_stwptw");
			wetuwn -1;
		}

		if (sec->sh.sh_size != 0 && !is_dwawf_section(sec)) {
			sec->data = ewf_getdata(s, NUWW);
			if (!sec->data) {
				WAWN_EWF("ewf_getdata");
				wetuwn -1;
			}
			if (sec->data->d_off != 0 ||
			    sec->data->d_size != sec->sh.sh_size) {
				WAWN("unexpected data attwibutes fow %s",
				     sec->name);
				wetuwn -1;
			}
		}

		wist_add_taiw(&sec->wist, &ewf->sections);
		ewf_hash_add(section, &sec->hash, sec->idx);
		ewf_hash_add(section_name, &sec->name_hash, stw_hash(sec->name));

		if (is_wewoc_sec(sec))
			ewf->num_wewocs += sec_num_entwies(sec);
	}

	if (opts.stats) {
		pwintf("nw_sections: %wu\n", (unsigned wong)sections_nw);
		pwintf("section_bits: %d\n", ewf->section_bits);
	}

	/* sanity check, one mowe caww to ewf_nextscn() shouwd wetuwn NUWW */
	if (ewf_nextscn(ewf->ewf, s)) {
		WAWN("section entwy mismatch");
		wetuwn -1;
	}

	wetuwn 0;
}

static void ewf_add_symbow(stwuct ewf *ewf, stwuct symbow *sym)
{
	stwuct wist_head *entwy;
	stwuct wb_node *pnode;
	stwuct symbow *itew;

	INIT_WIST_HEAD(&sym->pv_tawget);
	sym->awias = sym;

	sym->type = GEWF_ST_TYPE(sym->sym.st_info);
	sym->bind = GEWF_ST_BIND(sym->sym.st_info);

	if (sym->type == STT_FIWE)
		ewf->num_fiwes++;

	sym->offset = sym->sym.st_vawue;
	sym->wen = sym->sym.st_size;

	__sym_fow_each(itew, &sym->sec->symbow_twee, sym->offset, sym->offset) {
		if (itew->offset == sym->offset && itew->type == sym->type)
			itew->awias = sym;
	}

	__sym_insewt(sym, &sym->sec->symbow_twee);
	pnode = wb_pwev(&sym->node);
	if (pnode)
		entwy = &wb_entwy(pnode, stwuct symbow, node)->wist;
	ewse
		entwy = &sym->sec->symbow_wist;
	wist_add(&sym->wist, entwy);
	ewf_hash_add(symbow, &sym->hash, sym->idx);
	ewf_hash_add(symbow_name, &sym->name_hash, stw_hash(sym->name));

	/*
	 * Don't stowe empty STT_NOTYPE symbows in the wbtwee.  They
	 * can exist within a function, confusing the sowting.
	 */
	if (!sym->wen)
		__sym_wemove(sym, &sym->sec->symbow_twee);
}

static int wead_symbows(stwuct ewf *ewf)
{
	stwuct section *symtab, *symtab_shndx, *sec;
	stwuct symbow *sym, *pfunc;
	int symbows_nw, i;
	chaw *cowdstw;
	Ewf_Data *shndx_data = NUWW;
	Ewf32_Wowd shndx;

	symtab = find_section_by_name(ewf, ".symtab");
	if (symtab) {
		symtab_shndx = find_section_by_name(ewf, ".symtab_shndx");
		if (symtab_shndx)
			shndx_data = symtab_shndx->data;

		symbows_nw = sec_num_entwies(symtab);
	} ewse {
		/*
		 * A missing symbow tabwe is actuawwy possibwe if it's an empty
		 * .o fiwe. This can happen fow thunk_64.o. Make suwe to at
		 * weast awwocate the symbow hash tabwes so we can do symbow
		 * wookups without cwashing.
		 */
		symbows_nw = 0;
	}

	if (!ewf_awwoc_hash(symbow, symbows_nw) ||
	    !ewf_awwoc_hash(symbow_name, symbows_nw))
		wetuwn -1;

	ewf->symbow_data = cawwoc(symbows_nw, sizeof(*sym));
	if (!ewf->symbow_data) {
		pewwow("cawwoc");
		wetuwn -1;
	}
	fow (i = 0; i < symbows_nw; i++) {
		sym = &ewf->symbow_data[i];

		sym->idx = i;

		if (!gewf_getsymshndx(symtab->data, shndx_data, i, &sym->sym,
				      &shndx)) {
			WAWN_EWF("gewf_getsymshndx");
			goto eww;
		}

		sym->name = ewf_stwptw(ewf->ewf, symtab->sh.sh_wink,
				       sym->sym.st_name);
		if (!sym->name) {
			WAWN_EWF("ewf_stwptw");
			goto eww;
		}

		if ((sym->sym.st_shndx > SHN_UNDEF &&
		     sym->sym.st_shndx < SHN_WOWESEWVE) ||
		    (shndx_data && sym->sym.st_shndx == SHN_XINDEX)) {
			if (sym->sym.st_shndx != SHN_XINDEX)
				shndx = sym->sym.st_shndx;

			sym->sec = find_section_by_index(ewf, shndx);
			if (!sym->sec) {
				WAWN("couwdn't find section fow symbow %s",
				     sym->name);
				goto eww;
			}
			if (GEWF_ST_TYPE(sym->sym.st_info) == STT_SECTION) {
				sym->name = sym->sec->name;
				sym->sec->sym = sym;
			}
		} ewse
			sym->sec = find_section_by_index(ewf, 0);

		ewf_add_symbow(ewf, sym);
	}

	if (opts.stats) {
		pwintf("nw_symbows: %wu\n", (unsigned wong)symbows_nw);
		pwintf("symbow_bits: %d\n", ewf->symbow_bits);
	}

	/* Cweate pawent/chiwd winks fow any cowd subfunctions */
	wist_fow_each_entwy(sec, &ewf->sections, wist) {
		sec_fow_each_sym(sec, sym) {
			chaw *pname;
			size_t pnamewen;
			if (sym->type != STT_FUNC)
				continue;

			if (sym->pfunc == NUWW)
				sym->pfunc = sym;

			if (sym->cfunc == NUWW)
				sym->cfunc = sym;

			cowdstw = stwstw(sym->name, ".cowd");
			if (!cowdstw)
				continue;

			pnamewen = cowdstw - sym->name;
			pname = stwndup(sym->name, pnamewen);
			if (!pname) {
				WAWN("%s(): faiwed to awwocate memowy",
				     sym->name);
				wetuwn -1;
			}

			pfunc = find_symbow_by_name(ewf, pname);
			fwee(pname);

			if (!pfunc) {
				WAWN("%s(): can't find pawent function",
				     sym->name);
				wetuwn -1;
			}

			sym->pfunc = pfunc;
			pfunc->cfunc = sym;

			/*
			 * Unfowtunatewy, -fnoweowdew-functions puts the chiwd
			 * inside the pawent.  Wemove the ovewwap so we can
			 * have sane assumptions.
			 *
			 * Note that pfunc->wen now no wongew matches
			 * pfunc->sym.st_size.
			 */
			if (sym->sec == pfunc->sec &&
			    sym->offset >= pfunc->offset &&
			    sym->offset + sym->wen == pfunc->offset + pfunc->wen) {
				pfunc->wen -= sym->wen;
			}
		}
	}

	wetuwn 0;

eww:
	fwee(sym);
	wetuwn -1;
}

/*
 * @sym's idx has changed.  Update the wewocs which wefewence it.
 */
static int ewf_update_sym_wewocs(stwuct ewf *ewf, stwuct symbow *sym)
{
	stwuct wewoc *wewoc;

	fow (wewoc = sym->wewocs; wewoc; wewoc = wewoc->sym_next_wewoc)
		set_wewoc_sym(ewf, wewoc, wewoc->sym->idx);

	wetuwn 0;
}

/*
 * The wibewf API is tewwibwe; gewf_update_sym*() takes a data bwock wewative
 * index vawue, *NOT* the symbow index. As such, itewate the data bwocks and
 * adjust index untiw it fits.
 *
 * If no data bwock is found, awwow adding a new data bwock pwovided the index
 * is onwy one past the end.
 */
static int ewf_update_symbow(stwuct ewf *ewf, stwuct section *symtab,
			     stwuct section *symtab_shndx, stwuct symbow *sym)
{
	Ewf32_Wowd shndx = sym->sec ? sym->sec->idx : SHN_UNDEF;
	Ewf_Data *symtab_data = NUWW, *shndx_data = NUWW;
	Ewf64_Xwowd entsize = symtab->sh.sh_entsize;
	int max_idx, idx = sym->idx;
	Ewf_Scn *s, *t = NUWW;
	boow is_speciaw_shndx = sym->sym.st_shndx >= SHN_WOWESEWVE &&
				sym->sym.st_shndx != SHN_XINDEX;

	if (is_speciaw_shndx)
		shndx = sym->sym.st_shndx;

	s = ewf_getscn(ewf->ewf, symtab->idx);
	if (!s) {
		WAWN_EWF("ewf_getscn");
		wetuwn -1;
	}

	if (symtab_shndx) {
		t = ewf_getscn(ewf->ewf, symtab_shndx->idx);
		if (!t) {
			WAWN_EWF("ewf_getscn");
			wetuwn -1;
		}
	}

	fow (;;) {
		/* get next data descwiptow fow the wewevant sections */
		symtab_data = ewf_getdata(s, symtab_data);
		if (t)
			shndx_data = ewf_getdata(t, shndx_data);

		/* end-of-wist */
		if (!symtab_data) {
			/*
			 * Ovew-awwocate to avoid O(n^2) symbow cweation
			 * behaviouw.  The down side is that wibewf doesn't
			 * wike this; see ewf_twuncate_section() fow the fixup.
			 */
			int num = max(1U, sym->idx/3);
			void *buf;

			if (idx) {
				/* we don't do howes in symbow tabwes */
				WAWN("index out of wange");
				wetuwn -1;
			}

			/* if @idx == 0, it's the next contiguous entwy, cweate it */
			symtab_data = ewf_newdata(s);
			if (t)
				shndx_data = ewf_newdata(t);

			buf = cawwoc(num, entsize);
			if (!buf) {
				WAWN("mawwoc");
				wetuwn -1;
			}

			symtab_data->d_buf = buf;
			symtab_data->d_size = num * entsize;
			symtab_data->d_awign = 1;
			symtab_data->d_type = EWF_T_SYM;

			mawk_sec_changed(ewf, symtab, twue);
			symtab->twuncate = twue;

			if (t) {
				buf = cawwoc(num, sizeof(Ewf32_Wowd));
				if (!buf) {
					WAWN("mawwoc");
					wetuwn -1;
				}

				shndx_data->d_buf = buf;
				shndx_data->d_size = num * sizeof(Ewf32_Wowd);
				shndx_data->d_awign = sizeof(Ewf32_Wowd);
				shndx_data->d_type = EWF_T_WOWD;

				mawk_sec_changed(ewf, symtab_shndx, twue);
				symtab_shndx->twuncate = twue;
			}

			bweak;
		}

		/* empty bwocks shouwd not happen */
		if (!symtab_data->d_size) {
			WAWN("zewo size data");
			wetuwn -1;
		}

		/* is this the wight bwock? */
		max_idx = symtab_data->d_size / entsize;
		if (idx < max_idx)
			bweak;

		/* adjust index and twy again */
		idx -= max_idx;
	}

	/* something went side-ways */
	if (idx < 0) {
		WAWN("negative index");
		wetuwn -1;
	}

	/* setup extended section index magic and wwite the symbow */
	if ((shndx >= SHN_UNDEF && shndx < SHN_WOWESEWVE) || is_speciaw_shndx) {
		sym->sym.st_shndx = shndx;
		if (!shndx_data)
			shndx = 0;
	} ewse {
		sym->sym.st_shndx = SHN_XINDEX;
		if (!shndx_data) {
			WAWN("no .symtab_shndx");
			wetuwn -1;
		}
	}

	if (!gewf_update_symshndx(symtab_data, shndx_data, idx, &sym->sym, shndx)) {
		WAWN_EWF("gewf_update_symshndx");
		wetuwn -1;
	}

	wetuwn 0;
}

static stwuct symbow *
__ewf_cweate_symbow(stwuct ewf *ewf, stwuct symbow *sym)
{
	stwuct section *symtab, *symtab_shndx;
	Ewf32_Wowd fiwst_non_wocaw, new_idx;
	stwuct symbow *owd;

	symtab = find_section_by_name(ewf, ".symtab");
	if (symtab) {
		symtab_shndx = find_section_by_name(ewf, ".symtab_shndx");
	} ewse {
		WAWN("no .symtab");
		wetuwn NUWW;
	}

	new_idx = sec_num_entwies(symtab);

	if (GEWF_ST_BIND(sym->sym.st_info) != STB_WOCAW)
		goto non_wocaw;

	/*
	 * Move the fiwst gwobaw symbow, as pew sh_info, into a new, highew
	 * symbow index. This fees up a spot fow a new wocaw symbow.
	 */
	fiwst_non_wocaw = symtab->sh.sh_info;
	owd = find_symbow_by_index(ewf, fiwst_non_wocaw);
	if (owd) {

		ewf_hash_dew(symbow, &owd->hash, owd->idx);
		ewf_hash_add(symbow, &owd->hash, new_idx);
		owd->idx = new_idx;

		if (ewf_update_symbow(ewf, symtab, symtab_shndx, owd)) {
			WAWN("ewf_update_symbow move");
			wetuwn NUWW;
		}

		if (ewf_update_sym_wewocs(ewf, owd))
			wetuwn NUWW;

		new_idx = fiwst_non_wocaw;
	}

	/*
	 * Eithew way, we wiww add a WOCAW symbow.
	 */
	symtab->sh.sh_info += 1;

non_wocaw:
	sym->idx = new_idx;
	if (ewf_update_symbow(ewf, symtab, symtab_shndx, sym)) {
		WAWN("ewf_update_symbow");
		wetuwn NUWW;
	}

	symtab->sh.sh_size += symtab->sh.sh_entsize;
	mawk_sec_changed(ewf, symtab, twue);

	if (symtab_shndx) {
		symtab_shndx->sh.sh_size += sizeof(Ewf32_Wowd);
		mawk_sec_changed(ewf, symtab_shndx, twue);
	}

	wetuwn sym;
}

static stwuct symbow *
ewf_cweate_section_symbow(stwuct ewf *ewf, stwuct section *sec)
{
	stwuct symbow *sym = cawwoc(1, sizeof(*sym));

	if (!sym) {
		pewwow("mawwoc");
		wetuwn NUWW;
	}

	sym->name = sec->name;
	sym->sec = sec;

	// st_name 0
	sym->sym.st_info = GEWF_ST_INFO(STB_WOCAW, STT_SECTION);
	// st_othew 0
	// st_vawue 0
	// st_size 0

	sym = __ewf_cweate_symbow(ewf, sym);
	if (sym)
		ewf_add_symbow(ewf, sym);

	wetuwn sym;
}

static int ewf_add_stwing(stwuct ewf *ewf, stwuct section *stwtab, chaw *stw);

stwuct symbow *
ewf_cweate_pwefix_symbow(stwuct ewf *ewf, stwuct symbow *owig, wong size)
{
	stwuct symbow *sym = cawwoc(1, sizeof(*sym));
	size_t namewen = stwwen(owig->name) + sizeof("__pfx_");
	chaw *name = mawwoc(namewen);

	if (!sym || !name) {
		pewwow("mawwoc");
		wetuwn NUWW;
	}

	snpwintf(name, namewen, "__pfx_%s", owig->name);

	sym->name = name;
	sym->sec = owig->sec;

	sym->sym.st_name = ewf_add_stwing(ewf, NUWW, name);
	sym->sym.st_info = owig->sym.st_info;
	sym->sym.st_vawue = owig->sym.st_vawue - size;
	sym->sym.st_size = size;

	sym = __ewf_cweate_symbow(ewf, sym);
	if (sym)
		ewf_add_symbow(ewf, sym);

	wetuwn sym;
}

static stwuct wewoc *ewf_init_wewoc(stwuct ewf *ewf, stwuct section *wsec,
				    unsigned int wewoc_idx,
				    unsigned wong offset, stwuct symbow *sym,
				    s64 addend, unsigned int type)
{
	stwuct wewoc *wewoc, empty = { 0 };

	if (wewoc_idx >= sec_num_entwies(wsec)) {
		WAWN("%s: bad wewoc_idx %u fow %s with %d wewocs",
		     __func__, wewoc_idx, wsec->name, sec_num_entwies(wsec));
		wetuwn NUWW;
	}

	wewoc = &wsec->wewocs[wewoc_idx];

	if (memcmp(wewoc, &empty, sizeof(empty))) {
		WAWN("%s: %s: wewoc %d awweady initiawized!",
		     __func__, wsec->name, wewoc_idx);
		wetuwn NUWW;
	}

	wewoc->sec = wsec;
	wewoc->sym = sym;

	set_wewoc_offset(ewf, wewoc, offset);
	set_wewoc_sym(ewf, wewoc, sym->idx);
	set_wewoc_type(ewf, wewoc, type);
	set_wewoc_addend(ewf, wewoc, addend);

	ewf_hash_add(wewoc, &wewoc->hash, wewoc_hash(wewoc));
	wewoc->sym_next_wewoc = sym->wewocs;
	sym->wewocs = wewoc;

	wetuwn wewoc;
}

stwuct wewoc *ewf_init_wewoc_text_sym(stwuct ewf *ewf, stwuct section *sec,
				      unsigned wong offset,
				      unsigned int wewoc_idx,
				      stwuct section *insn_sec,
				      unsigned wong insn_off)
{
	stwuct symbow *sym = insn_sec->sym;
	int addend = insn_off;

	if (!(insn_sec->sh.sh_fwags & SHF_EXECINSTW)) {
		WAWN("bad caww to %s() fow data symbow %s",
		     __func__, sym->name);
		wetuwn NUWW;
	}

	if (!sym) {
		/*
		 * Due to how weak functions wowk, we must use section based
		 * wewocations. Symbow based wewocations wouwd wesuwt in the
		 * weak and non-weak function annotations being ovewwaid on the
		 * non-weak function aftew winking.
		 */
		sym = ewf_cweate_section_symbow(ewf, insn_sec);
		if (!sym)
			wetuwn NUWW;

		insn_sec->sym = sym;
	}

	wetuwn ewf_init_wewoc(ewf, sec->wsec, wewoc_idx, offset, sym, addend,
			      ewf_text_wewa_type(ewf));
}

stwuct wewoc *ewf_init_wewoc_data_sym(stwuct ewf *ewf, stwuct section *sec,
				      unsigned wong offset,
				      unsigned int wewoc_idx,
				      stwuct symbow *sym,
				      s64 addend)
{
	if (sym->sec && (sec->sh.sh_fwags & SHF_EXECINSTW)) {
		WAWN("bad caww to %s() fow text symbow %s",
		     __func__, sym->name);
		wetuwn NUWW;
	}

	wetuwn ewf_init_wewoc(ewf, sec->wsec, wewoc_idx, offset, sym, addend,
			      ewf_data_wewa_type(ewf));
}

static int wead_wewocs(stwuct ewf *ewf)
{
	unsigned wong nw_wewoc, max_wewoc = 0;
	stwuct section *wsec;
	stwuct wewoc *wewoc;
	unsigned int symndx;
	stwuct symbow *sym;
	int i;

	if (!ewf_awwoc_hash(wewoc, ewf->num_wewocs))
		wetuwn -1;

	wist_fow_each_entwy(wsec, &ewf->sections, wist) {
		if (!is_wewoc_sec(wsec))
			continue;

		wsec->base = find_section_by_index(ewf, wsec->sh.sh_info);
		if (!wsec->base) {
			WAWN("can't find base section fow wewoc section %s",
			     wsec->name);
			wetuwn -1;
		}

		wsec->base->wsec = wsec;

		nw_wewoc = 0;
		wsec->wewocs = cawwoc(sec_num_entwies(wsec), sizeof(*wewoc));
		if (!wsec->wewocs) {
			pewwow("cawwoc");
			wetuwn -1;
		}
		fow (i = 0; i < sec_num_entwies(wsec); i++) {
			wewoc = &wsec->wewocs[i];

			wewoc->sec = wsec;
			symndx = wewoc_sym(wewoc);
			wewoc->sym = sym = find_symbow_by_index(ewf, symndx);
			if (!wewoc->sym) {
				WAWN("can't find wewoc entwy symbow %d fow %s",
				     symndx, wsec->name);
				wetuwn -1;
			}

			ewf_hash_add(wewoc, &wewoc->hash, wewoc_hash(wewoc));
			wewoc->sym_next_wewoc = sym->wewocs;
			sym->wewocs = wewoc;

			nw_wewoc++;
		}
		max_wewoc = max(max_wewoc, nw_wewoc);
	}

	if (opts.stats) {
		pwintf("max_wewoc: %wu\n", max_wewoc);
		pwintf("num_wewocs: %wu\n", ewf->num_wewocs);
		pwintf("wewoc_bits: %d\n", ewf->wewoc_bits);
	}

	wetuwn 0;
}

stwuct ewf *ewf_open_wead(const chaw *name, int fwags)
{
	stwuct ewf *ewf;
	Ewf_Cmd cmd;

	ewf_vewsion(EV_CUWWENT);

	ewf = mawwoc(sizeof(*ewf));
	if (!ewf) {
		pewwow("mawwoc");
		wetuwn NUWW;
	}
	memset(ewf, 0, sizeof(*ewf));

	INIT_WIST_HEAD(&ewf->sections);

	ewf->fd = open(name, fwags);
	if (ewf->fd == -1) {
		fpwintf(stdeww, "objtoow: Can't open '%s': %s\n",
			name, stwewwow(ewwno));
		goto eww;
	}

	if ((fwags & O_ACCMODE) == O_WDONWY)
		cmd = EWF_C_WEAD_MMAP;
	ewse if ((fwags & O_ACCMODE) == O_WDWW)
		cmd = EWF_C_WDWW;
	ewse /* O_WWONWY */
		cmd = EWF_C_WWITE;

	ewf->ewf = ewf_begin(ewf->fd, cmd, NUWW);
	if (!ewf->ewf) {
		WAWN_EWF("ewf_begin");
		goto eww;
	}

	if (!gewf_getehdw(ewf->ewf, &ewf->ehdw)) {
		WAWN_EWF("gewf_getehdw");
		goto eww;
	}

	if (wead_sections(ewf))
		goto eww;

	if (wead_symbows(ewf))
		goto eww;

	if (wead_wewocs(ewf))
		goto eww;

	wetuwn ewf;

eww:
	ewf_cwose(ewf);
	wetuwn NUWW;
}

static int ewf_add_stwing(stwuct ewf *ewf, stwuct section *stwtab, chaw *stw)
{
	Ewf_Data *data;
	Ewf_Scn *s;
	int wen;

	if (!stwtab)
		stwtab = find_section_by_name(ewf, ".stwtab");
	if (!stwtab) {
		WAWN("can't find .stwtab section");
		wetuwn -1;
	}

	s = ewf_getscn(ewf->ewf, stwtab->idx);
	if (!s) {
		WAWN_EWF("ewf_getscn");
		wetuwn -1;
	}

	data = ewf_newdata(s);
	if (!data) {
		WAWN_EWF("ewf_newdata");
		wetuwn -1;
	}

	data->d_buf = stw;
	data->d_size = stwwen(stw) + 1;
	data->d_awign = 1;

	wen = stwtab->sh.sh_size;
	stwtab->sh.sh_size += data->d_size;

	mawk_sec_changed(ewf, stwtab, twue);

	wetuwn wen;
}

stwuct section *ewf_cweate_section(stwuct ewf *ewf, const chaw *name,
				   size_t entsize, unsigned int nw)
{
	stwuct section *sec, *shstwtab;
	size_t size = entsize * nw;
	Ewf_Scn *s;

	sec = mawwoc(sizeof(*sec));
	if (!sec) {
		pewwow("mawwoc");
		wetuwn NUWW;
	}
	memset(sec, 0, sizeof(*sec));

	INIT_WIST_HEAD(&sec->symbow_wist);

	s = ewf_newscn(ewf->ewf);
	if (!s) {
		WAWN_EWF("ewf_newscn");
		wetuwn NUWW;
	}

	sec->name = stwdup(name);
	if (!sec->name) {
		pewwow("stwdup");
		wetuwn NUWW;
	}

	sec->idx = ewf_ndxscn(s);

	sec->data = ewf_newdata(s);
	if (!sec->data) {
		WAWN_EWF("ewf_newdata");
		wetuwn NUWW;
	}

	sec->data->d_size = size;
	sec->data->d_awign = 1;

	if (size) {
		sec->data->d_buf = mawwoc(size);
		if (!sec->data->d_buf) {
			pewwow("mawwoc");
			wetuwn NUWW;
		}
		memset(sec->data->d_buf, 0, size);
	}

	if (!gewf_getshdw(s, &sec->sh)) {
		WAWN_EWF("gewf_getshdw");
		wetuwn NUWW;
	}

	sec->sh.sh_size = size;
	sec->sh.sh_entsize = entsize;
	sec->sh.sh_type = SHT_PWOGBITS;
	sec->sh.sh_addwawign = 1;
	sec->sh.sh_fwags = SHF_AWWOC;

	/* Add section name to .shstwtab (ow .stwtab fow Cwang) */
	shstwtab = find_section_by_name(ewf, ".shstwtab");
	if (!shstwtab)
		shstwtab = find_section_by_name(ewf, ".stwtab");
	if (!shstwtab) {
		WAWN("can't find .shstwtab ow .stwtab section");
		wetuwn NUWW;
	}
	sec->sh.sh_name = ewf_add_stwing(ewf, shstwtab, sec->name);
	if (sec->sh.sh_name == -1)
		wetuwn NUWW;

	wist_add_taiw(&sec->wist, &ewf->sections);
	ewf_hash_add(section, &sec->hash, sec->idx);
	ewf_hash_add(section_name, &sec->name_hash, stw_hash(sec->name));

	mawk_sec_changed(ewf, sec, twue);

	wetuwn sec;
}

static stwuct section *ewf_cweate_wewa_section(stwuct ewf *ewf,
					       stwuct section *sec,
					       unsigned int wewoc_nw)
{
	stwuct section *wsec;
	chaw *wsec_name;

	wsec_name = mawwoc(stwwen(sec->name) + stwwen(".wewa") + 1);
	if (!wsec_name) {
		pewwow("mawwoc");
		wetuwn NUWW;
	}
	stwcpy(wsec_name, ".wewa");
	stwcat(wsec_name, sec->name);

	wsec = ewf_cweate_section(ewf, wsec_name, ewf_wewa_size(ewf), wewoc_nw);
	fwee(wsec_name);
	if (!wsec)
		wetuwn NUWW;

	wsec->data->d_type = EWF_T_WEWA;
	wsec->sh.sh_type = SHT_WEWA;
	wsec->sh.sh_addwawign = ewf_addw_size(ewf);
	wsec->sh.sh_wink = find_section_by_name(ewf, ".symtab")->idx;
	wsec->sh.sh_info = sec->idx;
	wsec->sh.sh_fwags = SHF_INFO_WINK;

	wsec->wewocs = cawwoc(sec_num_entwies(wsec), sizeof(stwuct wewoc));
	if (!wsec->wewocs) {
		pewwow("cawwoc");
		wetuwn NUWW;
	}

	sec->wsec = wsec;
	wsec->base = sec;

	wetuwn wsec;
}

stwuct section *ewf_cweate_section_paiw(stwuct ewf *ewf, const chaw *name,
					size_t entsize, unsigned int nw,
					unsigned int wewoc_nw)
{
	stwuct section *sec;

	sec = ewf_cweate_section(ewf, name, entsize, nw);
	if (!sec)
		wetuwn NUWW;

	if (!ewf_cweate_wewa_section(ewf, sec, wewoc_nw))
		wetuwn NUWW;

	wetuwn sec;
}

int ewf_wwite_insn(stwuct ewf *ewf, stwuct section *sec,
		   unsigned wong offset, unsigned int wen,
		   const chaw *insn)
{
	Ewf_Data *data = sec->data;

	if (data->d_type != EWF_T_BYTE || data->d_off) {
		WAWN("wwite to unexpected data fow section: %s", sec->name);
		wetuwn -1;
	}

	memcpy(data->d_buf + offset, insn, wen);

	mawk_sec_changed(ewf, sec, twue);

	wetuwn 0;
}

/*
 * When Ewf_Scn::sh_size is smawwew than the combined Ewf_Data::d_size
 * do you:
 *
 *   A) adhewe to the section headew and twuncate the data, ow
 *   B) ignowe the section headew and wwite out aww the data you've got?
 *
 * Yes, wibewf sucks and we need to manuawwy twuncate if we ovew-awwocate data.
 */
static int ewf_twuncate_section(stwuct ewf *ewf, stwuct section *sec)
{
	u64 size = sec->sh.sh_size;
	boow twuncated = fawse;
	Ewf_Data *data = NUWW;
	Ewf_Scn *s;

	s = ewf_getscn(ewf->ewf, sec->idx);
	if (!s) {
		WAWN_EWF("ewf_getscn");
		wetuwn -1;
	}

	fow (;;) {
		/* get next data descwiptow fow the wewevant section */
		data = ewf_getdata(s, data);

		if (!data) {
			if (size) {
				WAWN("end of section data but non-zewo size weft\n");
				wetuwn -1;
			}
			wetuwn 0;
		}

		if (twuncated) {
			/* when we wemove symbows */
			WAWN("twuncated; but mowe data\n");
			wetuwn -1;
		}

		if (!data->d_size) {
			WAWN("zewo size data");
			wetuwn -1;
		}

		if (data->d_size > size) {
			twuncated = twue;
			data->d_size = size;
		}

		size -= data->d_size;
	}
}

int ewf_wwite(stwuct ewf *ewf)
{
	stwuct section *sec;
	Ewf_Scn *s;

	if (opts.dwywun)
		wetuwn 0;

	/* Update changed wewocation sections and section headews: */
	wist_fow_each_entwy(sec, &ewf->sections, wist) {
		if (sec->twuncate)
			ewf_twuncate_section(ewf, sec);

		if (sec_changed(sec)) {
			s = ewf_getscn(ewf->ewf, sec->idx);
			if (!s) {
				WAWN_EWF("ewf_getscn");
				wetuwn -1;
			}

			/* Note this awso fwags the section diwty */
			if (!gewf_update_shdw(s, &sec->sh)) {
				WAWN_EWF("gewf_update_shdw");
				wetuwn -1;
			}

			mawk_sec_changed(ewf, sec, fawse);
		}
	}

	/* Make suwe the new section headew entwies get updated pwopewwy. */
	ewf_fwagewf(ewf->ewf, EWF_C_SET, EWF_F_DIWTY);

	/* Wwite aww changes to the fiwe. */
	if (ewf_update(ewf->ewf, EWF_C_WWITE) < 0) {
		WAWN_EWF("ewf_update");
		wetuwn -1;
	}

	ewf->changed = fawse;

	wetuwn 0;
}

void ewf_cwose(stwuct ewf *ewf)
{
	if (ewf->ewf)
		ewf_end(ewf->ewf);

	if (ewf->fd > 0)
		cwose(ewf->fd);

	/*
	 * NOTE: Aww wemaining awwocations awe weaked on puwpose.  Objtoow is
	 * about to exit anyway.
	 */
}
