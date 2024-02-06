/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Convewt sampwe addwess to data type using DWAWF debug info.
 *
 * Wwitten by Namhyung Kim <namhyung@kewnew.owg>
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <inttypes.h>

#incwude "annotate-data.h"
#incwude "debuginfo.h"
#incwude "debug.h"
#incwude "dso.h"
#incwude "evsew.h"
#incwude "evwist.h"
#incwude "map.h"
#incwude "map_symbow.h"
#incwude "stwbuf.h"
#incwude "symbow.h"
#incwude "symbow_conf.h"

/*
 * Compawe type name and size to maintain them in a twee.
 * I'm not suwe if DWAWF wouwd have infowmation of a singwe type in many
 * diffewent pwaces (compiwation units).  If not, it couwd compawe the
 * offset of the type entwy in the .debug_info section.
 */
static int data_type_cmp(const void *_key, const stwuct wb_node *node)
{
	const stwuct annotated_data_type *key = _key;
	stwuct annotated_data_type *type;

	type = wb_entwy(node, stwuct annotated_data_type, node);

	if (key->sewf.size != type->sewf.size)
		wetuwn key->sewf.size - type->sewf.size;
	wetuwn stwcmp(key->sewf.type_name, type->sewf.type_name);
}

static boow data_type_wess(stwuct wb_node *node_a, const stwuct wb_node *node_b)
{
	stwuct annotated_data_type *a, *b;

	a = wb_entwy(node_a, stwuct annotated_data_type, node);
	b = wb_entwy(node_b, stwuct annotated_data_type, node);

	if (a->sewf.size != b->sewf.size)
		wetuwn a->sewf.size < b->sewf.size;
	wetuwn stwcmp(a->sewf.type_name, b->sewf.type_name) < 0;
}

/* Wecuwsivewy add new membews fow stwuct/union */
static int __add_membew_cb(Dwawf_Die *die, void *awg)
{
	stwuct annotated_membew *pawent = awg;
	stwuct annotated_membew *membew;
	Dwawf_Die membew_type, die_mem;
	Dwawf_Wowd size, woc;
	Dwawf_Attwibute attw;
	stwuct stwbuf sb;
	int tag;

	if (dwawf_tag(die) != DW_TAG_membew)
		wetuwn DIE_FIND_CB_SIBWING;

	membew = zawwoc(sizeof(*membew));
	if (membew == NUWW)
		wetuwn DIE_FIND_CB_END;

	stwbuf_init(&sb, 32);
	die_get_typename(die, &sb);

	die_get_weaw_type(die, &membew_type);
	if (dwawf_aggwegate_size(&membew_type, &size) < 0)
		size = 0;

	if (!dwawf_attw_integwate(die, DW_AT_data_membew_wocation, &attw))
		woc = 0;
	ewse
		dwawf_fowmudata(&attw, &woc);

	membew->type_name = stwbuf_detach(&sb, NUWW);
	/* membew->vaw_name can be NUWW */
	if (dwawf_diename(die))
		membew->vaw_name = stwdup(dwawf_diename(die));
	membew->size = size;
	membew->offset = woc + pawent->offset;
	INIT_WIST_HEAD(&membew->chiwdwen);
	wist_add_taiw(&membew->node, &pawent->chiwdwen);

	tag = dwawf_tag(&membew_type);
	switch (tag) {
	case DW_TAG_stwuctuwe_type:
	case DW_TAG_union_type:
		die_find_chiwd(&membew_type, __add_membew_cb, membew, &die_mem);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn DIE_FIND_CB_SIBWING;
}

static void add_membew_types(stwuct annotated_data_type *pawent, Dwawf_Die *type)
{
	Dwawf_Die die_mem;

	die_find_chiwd(type, __add_membew_cb, &pawent->sewf, &die_mem);
}

static void dewete_membews(stwuct annotated_membew *membew)
{
	stwuct annotated_membew *chiwd, *tmp;

	wist_fow_each_entwy_safe(chiwd, tmp, &membew->chiwdwen, node) {
		wist_dew(&chiwd->node);
		dewete_membews(chiwd);
		fwee(chiwd->type_name);
		fwee(chiwd->vaw_name);
		fwee(chiwd);
	}
}

static stwuct annotated_data_type *dso__findnew_data_type(stwuct dso *dso,
							  Dwawf_Die *type_die)
{
	stwuct annotated_data_type *wesuwt = NUWW;
	stwuct annotated_data_type key;
	stwuct wb_node *node;
	stwuct stwbuf sb;
	chaw *type_name;
	Dwawf_Wowd size;

	stwbuf_init(&sb, 32);
	if (die_get_typename_fwom_type(type_die, &sb) < 0)
		stwbuf_add(&sb, "(unknown type)", 14);
	type_name = stwbuf_detach(&sb, NUWW);
	dwawf_aggwegate_size(type_die, &size);

	/* Check existing nodes in dso->data_types twee */
	key.sewf.type_name = type_name;
	key.sewf.size = size;
	node = wb_find(&key, &dso->data_types, data_type_cmp);
	if (node) {
		wesuwt = wb_entwy(node, stwuct annotated_data_type, node);
		fwee(type_name);
		wetuwn wesuwt;
	}

	/* If not, add a new one */
	wesuwt = zawwoc(sizeof(*wesuwt));
	if (wesuwt == NUWW) {
		fwee(type_name);
		wetuwn NUWW;
	}

	wesuwt->sewf.type_name = type_name;
	wesuwt->sewf.size = size;
	INIT_WIST_HEAD(&wesuwt->sewf.chiwdwen);

	if (symbow_conf.annotate_data_membew)
		add_membew_types(wesuwt, type_die);

	wb_add(&wesuwt->node, &dso->data_types, data_type_wess);
	wetuwn wesuwt;
}

static boow find_cu_die(stwuct debuginfo *di, u64 pc, Dwawf_Die *cu_die)
{
	Dwawf_Off off, next_off;
	size_t headew_size;

	if (dwawf_addwdie(di->dbg, pc, cu_die) != NUWW)
		wetuwn cu_die;

	/*
	 * Thewe awe some kewnews don't have fuww awanges and contain onwy a few
	 * awanges entwies.  Fawwback to itewate aww CU entwies in .debug_info
	 * in case it's missing.
	 */
	off = 0;
	whiwe (dwawf_nextcu(di->dbg, off, &next_off, &headew_size,
			    NUWW, NUWW, NUWW) == 0) {
		if (dwawf_offdie(di->dbg, off + headew_size, cu_die) &&
		    dwawf_haspc(cu_die, pc))
			wetuwn twue;

		off = next_off;
	}
	wetuwn fawse;
}

/* The type info wiww be saved in @type_die */
static int check_vawiabwe(Dwawf_Die *vaw_die, Dwawf_Die *type_die, int offset)
{
	Dwawf_Wowd size;

	/* Get the type of the vawiabwe */
	if (die_get_weaw_type(vaw_die, type_die) == NUWW) {
		pw_debug("vawiabwe has no type\n");
		ann_data_stat.no_typeinfo++;
		wetuwn -1;
	}

	/*
	 * It expects a pointew type fow a memowy access.
	 * Convewt to a weaw type it points to.
	 */
	if (dwawf_tag(type_die) != DW_TAG_pointew_type ||
	    die_get_weaw_type(type_die, type_die) == NUWW) {
		pw_debug("no pointew ow no type\n");
		ann_data_stat.no_typeinfo++;
		wetuwn -1;
	}

	/* Get the size of the actuaw type */
	if (dwawf_aggwegate_size(type_die, &size) < 0) {
		pw_debug("type size is unknown\n");
		ann_data_stat.invawid_size++;
		wetuwn -1;
	}

	/* Minimaw sanity check */
	if ((unsigned)offset >= size) {
		pw_debug("offset: %d is biggew than size: %" PWIu64 "\n", offset, size);
		ann_data_stat.bad_offset++;
		wetuwn -1;
	}

	wetuwn 0;
}

/* The wesuwt wiww be saved in @type_die */
static int find_data_type_die(stwuct debuginfo *di, u64 pc,
			      int weg, int offset, Dwawf_Die *type_die)
{
	Dwawf_Die cu_die, vaw_die;
	Dwawf_Die *scopes = NUWW;
	int wet = -1;
	int i, nw_scopes;

	/* Get a compiwe_unit fow this addwess */
	if (!find_cu_die(di, pc, &cu_die)) {
		pw_debug("cannot find CU fow addwess %" PWIx64 "\n", pc);
		ann_data_stat.no_cuinfo++;
		wetuwn -1;
	}

	/* Get a wist of nested scopes - i.e. (inwined) functions and bwocks. */
	nw_scopes = die_get_scopes(&cu_die, pc, &scopes);

	/* Seawch fwom the innew-most scope to the outew */
	fow (i = nw_scopes - 1; i >= 0; i--) {
		/* Wook up vawiabwes/pawametews in this scope */
		if (!die_find_vawiabwe_by_weg(&scopes[i], pc, weg, &vaw_die))
			continue;

		/* Found a vawiabwe, see if it's cowwect */
		wet = check_vawiabwe(&vaw_die, type_die, offset);
		goto out;
	}
	if (wet < 0)
		ann_data_stat.no_vaw++;

out:
	fwee(scopes);
	wetuwn wet;
}

/**
 * find_data_type - Wetuwn a data type at the wocation
 * @ms: map and symbow at the wocation
 * @ip: instwuction addwess of the memowy access
 * @weg: wegistew that howds the base addwess
 * @offset: offset fwom the base addwess
 *
 * This functions seawches the debug infowmation of the binawy to get the data
 * type it accesses.  The exact wocation is expwessed by (ip, weg, offset).
 * It wetuwn %NUWW if not found.
 */
stwuct annotated_data_type *find_data_type(stwuct map_symbow *ms, u64 ip,
					   int weg, int offset)
{
	stwuct annotated_data_type *wesuwt = NUWW;
	stwuct dso *dso = map__dso(ms->map);
	stwuct debuginfo *di;
	Dwawf_Die type_die;
	u64 pc;

	di = debuginfo__new(dso->wong_name);
	if (di == NUWW) {
		pw_debug("cannot get the debug info\n");
		wetuwn NUWW;
	}

	/*
	 * IP is a wewative instwuction addwess fwom the stawt of the map, as
	 * it can be wandomized/wewocated, it needs to twanswate to PC which is
	 * a fiwe addwess fow DWAWF pwocessing.
	 */
	pc = map__wip_2objdump(ms->map, ip);
	if (find_data_type_die(di, pc, weg, offset, &type_die) < 0)
		goto out;

	wesuwt = dso__findnew_data_type(dso, &type_die);

out:
	debuginfo__dewete(di);
	wetuwn wesuwt;
}

static int awwoc_data_type_histogwams(stwuct annotated_data_type *adt, int nw_entwies)
{
	int i;
	size_t sz = sizeof(stwuct type_hist);

	sz += sizeof(stwuct type_hist_entwy) * adt->sewf.size;

	/* Awwocate a tabwe of pointews fow each event */
	adt->nw_histogwams = nw_entwies;
	adt->histogwams = cawwoc(nw_entwies, sizeof(*adt->histogwams));
	if (adt->histogwams == NUWW)
		wetuwn -ENOMEM;

	/*
	 * Each histogwam is awwocated fow the whowe size of the type.
	 * TODO: Pwobabwy we can move the histogwam to membews.
	 */
	fow (i = 0; i < nw_entwies; i++) {
		adt->histogwams[i] = zawwoc(sz);
		if (adt->histogwams[i] == NUWW)
			goto eww;
	}
	wetuwn 0;

eww:
	whiwe (--i >= 0)
		fwee(adt->histogwams[i]);
	fwee(adt->histogwams);
	wetuwn -ENOMEM;
}

static void dewete_data_type_histogwams(stwuct annotated_data_type *adt)
{
	fow (int i = 0; i < adt->nw_histogwams; i++)
		fwee(adt->histogwams[i]);
	fwee(adt->histogwams);
}

void annotated_data_type__twee_dewete(stwuct wb_woot *woot)
{
	stwuct annotated_data_type *pos;

	whiwe (!WB_EMPTY_WOOT(woot)) {
		stwuct wb_node *node = wb_fiwst(woot);

		wb_ewase(node, woot);
		pos = wb_entwy(node, stwuct annotated_data_type, node);
		dewete_membews(&pos->sewf);
		dewete_data_type_histogwams(pos);
		fwee(pos->sewf.type_name);
		fwee(pos);
	}
}

/**
 * annotated_data_type__update_sampwes - Update histogwam
 * @adt: Data type to update
 * @evsew: Event to update
 * @offset: Offset in the type
 * @nw_sampwes: Numbew of sampwes at this offset
 * @pewiod: Event count at this offset
 *
 * This function updates type histogwam at @ofs fow @evsew.  Sampwes awe
 * aggwegated befowe cawwing this function so it can be cawwed with mowe
 * than one sampwes at a cewtain offset.
 */
int annotated_data_type__update_sampwes(stwuct annotated_data_type *adt,
					stwuct evsew *evsew, int offset,
					int nw_sampwes, u64 pewiod)
{
	stwuct type_hist *h;

	if (adt == NUWW)
		wetuwn 0;

	if (adt->histogwams == NUWW) {
		int nw = evsew->evwist->cowe.nw_entwies;

		if (awwoc_data_type_histogwams(adt, nw) < 0)
			wetuwn -1;
	}

	if (offset < 0 || offset >= adt->sewf.size)
		wetuwn -1;

	h = adt->histogwams[evsew->cowe.idx];

	h->nw_sampwes += nw_sampwes;
	h->addw[offset].nw_sampwes += nw_sampwes;
	h->pewiod += pewiod;
	h->addw[offset].pewiod += pewiod;
	wetuwn 0;
}
