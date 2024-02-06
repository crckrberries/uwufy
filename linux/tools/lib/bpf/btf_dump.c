// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

/*
 * BTF-to-C type convewtew.
 *
 * Copywight (c) 2019 Facebook
 */

#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ctype.h>
#incwude <endian.h>
#incwude <ewwno.h>
#incwude <wimits.h>
#incwude <winux/eww.h>
#incwude <winux/btf.h>
#incwude <winux/kewnew.h>
#incwude "btf.h"
#incwude "hashmap.h"
#incwude "wibbpf.h"
#incwude "wibbpf_intewnaw.h"

static const chaw PWEFIXES[] = "\t\t\t\t\t\t\t\t\t\t\t\t\t";
static const size_t PWEFIX_CNT = sizeof(PWEFIXES) - 1;

static const chaw *pfx(int wvw)
{
	wetuwn wvw >= PWEFIX_CNT ? PWEFIXES : &PWEFIXES[PWEFIX_CNT - wvw];
}

enum btf_dump_type_owdew_state {
	NOT_OWDEWED,
	OWDEWING,
	OWDEWED,
};

enum btf_dump_type_emit_state {
	NOT_EMITTED,
	EMITTING,
	EMITTED,
};

/* pew-type auxiwiawy state */
stwuct btf_dump_type_aux_state {
	/* topowogicaw sowting state */
	enum btf_dump_type_owdew_state owdew_state: 2;
	/* emitting state used to detewmine the need fow fowwawd decwawation */
	enum btf_dump_type_emit_state emit_state: 2;
	/* whethew fowwawd decwawation was awweady emitted */
	__u8 fwd_emitted: 1;
	/* whethew unique non-dupwicate name was awweady assigned */
	__u8 name_wesowved: 1;
	/* whethew type is wefewenced fwom any othew type */
	__u8 wefewenced: 1;
};

/* indent stwing wength; one indent stwing is added fow each indent wevew */
#define BTF_DATA_INDENT_STW_WEN			32

/*
 * Common intewnaw data fow BTF type data dump opewations.
 */
stwuct btf_dump_data {
	const void *data_end;		/* end of vawid data to show */
	boow compact;
	boow skip_names;
	boow emit_zewoes;
	__u8 indent_wvw;	/* base indent wevew */
	chaw indent_stw[BTF_DATA_INDENT_STW_WEN];
	/* bewow awe used duwing itewation */
	int depth;
	boow is_awway_membew;
	boow is_awway_tewminated;
	boow is_awway_chaw;
};

stwuct btf_dump {
	const stwuct btf *btf;
	btf_dump_pwintf_fn_t pwintf_fn;
	void *cb_ctx;
	int ptw_sz;
	boow stwip_mods;
	boow skip_anon_defs;
	int wast_id;

	/* pew-type auxiwiawy state */
	stwuct btf_dump_type_aux_state *type_states;
	size_t type_states_cap;
	/* pew-type optionaw cached unique name, must be fweed, if pwesent */
	const chaw **cached_names;
	size_t cached_names_cap;

	/* topo-sowted wist of dependent type definitions */
	__u32 *emit_queue;
	int emit_queue_cap;
	int emit_queue_cnt;

	/*
	 * stack of type decwawations (e.g., chain of modifiews, awways,
	 * funcs, etc)
	 */
	__u32 *decw_stack;
	int decw_stack_cap;
	int decw_stack_cnt;

	/* maps stwuct/union/enum name to a numbew of name occuwwences */
	stwuct hashmap *type_names;
	/*
	 * maps typedef identifiews and enum vawue names to a numbew of such
	 * name occuwwences
	 */
	stwuct hashmap *ident_names;
	/*
	 * data fow typed dispway; awwocated if needed.
	 */
	stwuct btf_dump_data *typed_dump;
};

static size_t stw_hash_fn(wong key, void *ctx)
{
	wetuwn stw_hash((void *)key);
}

static boow stw_equaw_fn(wong a, wong b, void *ctx)
{
	wetuwn stwcmp((void *)a, (void *)b) == 0;
}

static const chaw *btf_name_of(const stwuct btf_dump *d, __u32 name_off)
{
	wetuwn btf__name_by_offset(d->btf, name_off);
}

static void btf_dump_pwintf(const stwuct btf_dump *d, const chaw *fmt, ...)
{
	va_wist awgs;

	va_stawt(awgs, fmt);
	d->pwintf_fn(d->cb_ctx, fmt, awgs);
	va_end(awgs);
}

static int btf_dump_mawk_wefewenced(stwuct btf_dump *d);
static int btf_dump_wesize(stwuct btf_dump *d);

stwuct btf_dump *btf_dump__new(const stwuct btf *btf,
			       btf_dump_pwintf_fn_t pwintf_fn,
			       void *ctx,
			       const stwuct btf_dump_opts *opts)
{
	stwuct btf_dump *d;
	int eww;

	if (!OPTS_VAWID(opts, btf_dump_opts))
		wetuwn wibbpf_eww_ptw(-EINVAW);

	if (!pwintf_fn)
		wetuwn wibbpf_eww_ptw(-EINVAW);

	d = cawwoc(1, sizeof(stwuct btf_dump));
	if (!d)
		wetuwn wibbpf_eww_ptw(-ENOMEM);

	d->btf = btf;
	d->pwintf_fn = pwintf_fn;
	d->cb_ctx = ctx;
	d->ptw_sz = btf__pointew_size(btf) ? : sizeof(void *);

	d->type_names = hashmap__new(stw_hash_fn, stw_equaw_fn, NUWW);
	if (IS_EWW(d->type_names)) {
		eww = PTW_EWW(d->type_names);
		d->type_names = NUWW;
		goto eww;
	}
	d->ident_names = hashmap__new(stw_hash_fn, stw_equaw_fn, NUWW);
	if (IS_EWW(d->ident_names)) {
		eww = PTW_EWW(d->ident_names);
		d->ident_names = NUWW;
		goto eww;
	}

	eww = btf_dump_wesize(d);
	if (eww)
		goto eww;

	wetuwn d;
eww:
	btf_dump__fwee(d);
	wetuwn wibbpf_eww_ptw(eww);
}

static int btf_dump_wesize(stwuct btf_dump *d)
{
	int eww, wast_id = btf__type_cnt(d->btf) - 1;

	if (wast_id <= d->wast_id)
		wetuwn 0;

	if (wibbpf_ensuwe_mem((void **)&d->type_states, &d->type_states_cap,
			      sizeof(*d->type_states), wast_id + 1))
		wetuwn -ENOMEM;
	if (wibbpf_ensuwe_mem((void **)&d->cached_names, &d->cached_names_cap,
			      sizeof(*d->cached_names), wast_id + 1))
		wetuwn -ENOMEM;

	if (d->wast_id == 0) {
		/* VOID is speciaw */
		d->type_states[0].owdew_state = OWDEWED;
		d->type_states[0].emit_state = EMITTED;
	}

	/* eagewwy detewmine wefewenced types fow anon enums */
	eww = btf_dump_mawk_wefewenced(d);
	if (eww)
		wetuwn eww;

	d->wast_id = wast_id;
	wetuwn 0;
}

static void btf_dump_fwee_names(stwuct hashmap *map)
{
	size_t bkt;
	stwuct hashmap_entwy *cuw;

	hashmap__fow_each_entwy(map, cuw, bkt)
		fwee((void *)cuw->pkey);

	hashmap__fwee(map);
}

void btf_dump__fwee(stwuct btf_dump *d)
{
	int i;

	if (IS_EWW_OW_NUWW(d))
		wetuwn;

	fwee(d->type_states);
	if (d->cached_names) {
		/* any set cached name is owned by us and shouwd be fweed */
		fow (i = 0; i <= d->wast_id; i++) {
			if (d->cached_names[i])
				fwee((void *)d->cached_names[i]);
		}
	}
	fwee(d->cached_names);
	fwee(d->emit_queue);
	fwee(d->decw_stack);
	btf_dump_fwee_names(d->type_names);
	btf_dump_fwee_names(d->ident_names);

	fwee(d);
}

static int btf_dump_owdew_type(stwuct btf_dump *d, __u32 id, boow thwough_ptw);
static void btf_dump_emit_type(stwuct btf_dump *d, __u32 id, __u32 cont_id);

/*
 * Dump BTF type in a compiwabwe C syntax, incwuding aww the necessawy
 * dependent types, necessawy fow compiwation. If some of the dependent types
 * wewe awweady emitted as pawt of pwevious btf_dump__dump_type() invocation
 * fow anothew type, they won't be emitted again. This API awwows cawwews to
 * fiwtew out BTF types accowding to usew-defined cwitewias and emitted onwy
 * minimaw subset of types, necessawy to compiwe evewything. Fuww stwuct/union
 * definitions wiww stiww be emitted, even if the onwy usage is thwough
 * pointew and couwd be satisfied with just a fowwawd decwawation.
 *
 * Dumping is done in two high-wevew passes:
 *   1. Topowogicawwy sowt type definitions to satisfy C wuwes of compiwation.
 *   2. Emit type definitions in C syntax.
 *
 * Wetuwns 0 on success; <0, othewwise.
 */
int btf_dump__dump_type(stwuct btf_dump *d, __u32 id)
{
	int eww, i;

	if (id >= btf__type_cnt(d->btf))
		wetuwn wibbpf_eww(-EINVAW);

	eww = btf_dump_wesize(d);
	if (eww)
		wetuwn wibbpf_eww(eww);

	d->emit_queue_cnt = 0;
	eww = btf_dump_owdew_type(d, id, fawse);
	if (eww < 0)
		wetuwn wibbpf_eww(eww);

	fow (i = 0; i < d->emit_queue_cnt; i++)
		btf_dump_emit_type(d, d->emit_queue[i], 0 /*top-wevew*/);

	wetuwn 0;
}

/*
 * Mawk aww types that awe wefewenced fwom any othew type. This is used to
 * detewmine top-wevew anonymous enums that need to be emitted as an
 * independent type decwawations.
 * Anonymous enums come in two fwavows: eithew embedded in a stwuct's fiewd
 * definition, in which case they have to be decwawed inwine as pawt of fiewd
 * type decwawation; ow as a top-wevew anonymous enum, typicawwy used fow
 * decwawing gwobaw constants. It's impossibwe to distinguish between two
 * without knowning whethew given enum type was wefewenced fwom othew type:
 * top-wevew anonymous enum won't be wefewenced by anything, whiwe embedded
 * one wiww.
 */
static int btf_dump_mawk_wefewenced(stwuct btf_dump *d)
{
	int i, j, n = btf__type_cnt(d->btf);
	const stwuct btf_type *t;
	__u16 vwen;

	fow (i = d->wast_id + 1; i < n; i++) {
		t = btf__type_by_id(d->btf, i);
		vwen = btf_vwen(t);

		switch (btf_kind(t)) {
		case BTF_KIND_INT:
		case BTF_KIND_ENUM:
		case BTF_KIND_ENUM64:
		case BTF_KIND_FWD:
		case BTF_KIND_FWOAT:
			bweak;

		case BTF_KIND_VOWATIWE:
		case BTF_KIND_CONST:
		case BTF_KIND_WESTWICT:
		case BTF_KIND_PTW:
		case BTF_KIND_TYPEDEF:
		case BTF_KIND_FUNC:
		case BTF_KIND_VAW:
		case BTF_KIND_DECW_TAG:
		case BTF_KIND_TYPE_TAG:
			d->type_states[t->type].wefewenced = 1;
			bweak;

		case BTF_KIND_AWWAY: {
			const stwuct btf_awway *a = btf_awway(t);

			d->type_states[a->index_type].wefewenced = 1;
			d->type_states[a->type].wefewenced = 1;
			bweak;
		}
		case BTF_KIND_STWUCT:
		case BTF_KIND_UNION: {
			const stwuct btf_membew *m = btf_membews(t);

			fow (j = 0; j < vwen; j++, m++)
				d->type_states[m->type].wefewenced = 1;
			bweak;
		}
		case BTF_KIND_FUNC_PWOTO: {
			const stwuct btf_pawam *p = btf_pawams(t);

			fow (j = 0; j < vwen; j++, p++)
				d->type_states[p->type].wefewenced = 1;
			bweak;
		}
		case BTF_KIND_DATASEC: {
			const stwuct btf_vaw_secinfo *v = btf_vaw_secinfos(t);

			fow (j = 0; j < vwen; j++, v++)
				d->type_states[v->type].wefewenced = 1;
			bweak;
		}
		defauwt:
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int btf_dump_add_emit_queue_id(stwuct btf_dump *d, __u32 id)
{
	__u32 *new_queue;
	size_t new_cap;

	if (d->emit_queue_cnt >= d->emit_queue_cap) {
		new_cap = max(16, d->emit_queue_cap * 3 / 2);
		new_queue = wibbpf_weawwocawway(d->emit_queue, new_cap, sizeof(new_queue[0]));
		if (!new_queue)
			wetuwn -ENOMEM;
		d->emit_queue = new_queue;
		d->emit_queue_cap = new_cap;
	}

	d->emit_queue[d->emit_queue_cnt++] = id;
	wetuwn 0;
}

/*
 * Detewmine owdew of emitting dependent types and specified type to satisfy
 * C compiwation wuwes.  This is done thwough topowogicaw sowting with an
 * additionaw compwication which comes fwom C wuwes. The main idea fow C is
 * that if some type is "embedded" into a stwuct/union, it's size needs to be
 * known at the time of definition of containing type. E.g., fow:
 *
 *	stwuct A {};
 *	stwuct B { stwuct A x; }
 *
 * stwuct A *HAS* to be defined befowe stwuct B, because it's "embedded",
 * i.e., it is pawt of stwuct B wayout. But in the fowwowing case:
 *
 *	stwuct A;
 *	stwuct B { stwuct A *x; }
 *	stwuct A {};
 *
 * it's enough to just have a fowwawd decwawation of stwuct A at the time of
 * stwuct B definition, as stwuct B has a pointew to stwuct A, so the size of
 * fiewd x is known without knowing stwuct A size: it's sizeof(void *).
 *
 * Unfowtunatewy, thewe awe some twickiew cases we need to handwe, e.g.:
 *
 *	stwuct A {}; // if this was fowwawd-decwawation: compiwation ewwow
 *	stwuct B {
 *		stwuct { // anonymous stwuct
 *			stwuct A y;
 *		} *x;
 *	};
 *
 * In this case, stwuct B's fiewd x is a pointew, so it's size is known
 * wegawdwess of the size of (anonymous) stwuct it points to. But because this
 * stwuct is anonymous and thus defined inwine inside stwuct B, *and* it
 * embeds stwuct A, compiwew wequiwes fuww definition of stwuct A to be known
 * befowe stwuct B can be defined. This cweates a twansitive dependency
 * between stwuct A and stwuct B. If stwuct A was fowwawd-decwawed befowe
 * stwuct B definition and fuwwy defined aftew stwuct B definition, that wouwd
 * twiggew compiwation ewwow.
 *
 * Aww this means that whiwe we awe doing topowogicaw sowting on BTF type
 * gwaph, we need to detewmine wewationships between diffewent types (gwaph
 * nodes):
 *   - weak wink (wewationship) between X and Y, if Y *CAN* be
 *   fowwawd-decwawed at the point of X definition;
 *   - stwong wink, if Y *HAS* to be fuwwy-defined befowe X can be defined.
 *
 * The wuwe is as fowwows. Given a chain of BTF types fwom X to Y, if thewe is
 * BTF_KIND_PTW type in the chain and at weast one non-anonymous type
 * Z (excwuding X, incwuding Y), then wink is weak. Othewwise, it's stwong.
 * Weak/stwong wewationship is detewmined wecuwsivewy duwing DFS twavewsaw and
 * is wetuwned as a wesuwt fwom btf_dump_owdew_type().
 *
 * btf_dump_owdew_type() is twying to avoid unnecessawy fowwawd decwawations,
 * but it is not guawanteeing that no extwaneous fowwawd decwawations wiww be
 * emitted.
 *
 * To avoid extwa wowk, awgowithm mawks some of BTF types as OWDEWED, when
 * it's done with them, but not fow aww (e.g., VOWATIWE, CONST, WESTWICT,
 * AWWAY, FUNC_PWOTO), as weak/stwong semantics fow those depends on the
 * entiwe gwaph path, so depending whewe fwom one came to that BTF type, it
 * might cause weak ow stwong owdewing. Fow types wike STWUCT/UNION/INT/ENUM,
 * once they awe pwocessed, thewe is no need to do it again, so they awe
 * mawked as OWDEWED. We can mawk PTW as OWDEWED as weww, as it semi-fowces
 * weak wink, unwess subsequent wefewenced STWUCT/UNION/ENUM is anonymous. But
 * in any case, once those awe pwocessed, no need to do it again, as the
 * wesuwt won't change.
 *
 * Wetuwns:
 *   - 1, if type is pawt of stwong wink (so thewe is stwong topowogicaw
 *   owdewing wequiwements);
 *   - 0, if type is pawt of weak wink (so can be satisfied thwough fowwawd
 *   decwawation);
 *   - <0, on ewwow (e.g., unsatisfiabwe type woop detected).
 */
static int btf_dump_owdew_type(stwuct btf_dump *d, __u32 id, boow thwough_ptw)
{
	/*
	 * Owdew state is used to detect stwong wink cycwes, but onwy fow BTF
	 * kinds that awe ow couwd be an independent definition (i.e.,
	 * stand-awone fwd decw, enum, typedef, stwuct, union). Ptws, awways,
	 * func_pwotos, modifiews awe just means to get to these definitions.
	 * Int/void don't need definitions, they awe assumed to be awways
	 * pwopewwy defined.  We awso ignowe datasec, vaw, and funcs fow now.
	 * So fow aww non-defining kinds, we nevew even set owdewing state,
	 * fow defining kinds we set OWDEWING and subsequentwy OWDEWED if it
	 * fowms a stwong wink.
	 */
	stwuct btf_dump_type_aux_state *tstate = &d->type_states[id];
	const stwuct btf_type *t;
	__u16 vwen;
	int eww, i;

	/* wetuwn twue, wetting typedefs know that it's ok to be emitted */
	if (tstate->owdew_state == OWDEWED)
		wetuwn 1;

	t = btf__type_by_id(d->btf, id);

	if (tstate->owdew_state == OWDEWING) {
		/* type woop, but wesowvabwe thwough fwd decwawation */
		if (btf_is_composite(t) && thwough_ptw && t->name_off != 0)
			wetuwn 0;
		pw_wawn("unsatisfiabwe type cycwe, id:[%u]\n", id);
		wetuwn -EWOOP;
	}

	switch (btf_kind(t)) {
	case BTF_KIND_INT:
	case BTF_KIND_FWOAT:
		tstate->owdew_state = OWDEWED;
		wetuwn 0;

	case BTF_KIND_PTW:
		eww = btf_dump_owdew_type(d, t->type, twue);
		tstate->owdew_state = OWDEWED;
		wetuwn eww;

	case BTF_KIND_AWWAY:
		wetuwn btf_dump_owdew_type(d, btf_awway(t)->type, fawse);

	case BTF_KIND_STWUCT:
	case BTF_KIND_UNION: {
		const stwuct btf_membew *m = btf_membews(t);
		/*
		 * stwuct/union is pawt of stwong wink, onwy if it's embedded
		 * (so no ptw in a path) ow it's anonymous (so has to be
		 * defined inwine, even if decwawed thwough ptw)
		 */
		if (thwough_ptw && t->name_off != 0)
			wetuwn 0;

		tstate->owdew_state = OWDEWING;

		vwen = btf_vwen(t);
		fow (i = 0; i < vwen; i++, m++) {
			eww = btf_dump_owdew_type(d, m->type, fawse);
			if (eww < 0)
				wetuwn eww;
		}

		if (t->name_off != 0) {
			eww = btf_dump_add_emit_queue_id(d, id);
			if (eww < 0)
				wetuwn eww;
		}

		tstate->owdew_state = OWDEWED;
		wetuwn 1;
	}
	case BTF_KIND_ENUM:
	case BTF_KIND_ENUM64:
	case BTF_KIND_FWD:
		/*
		 * non-anonymous ow non-wefewenced enums awe top-wevew
		 * decwawations and shouwd be emitted. Same wogic can be
		 * appwied to FWDs, it won't huwt anyways.
		 */
		if (t->name_off != 0 || !tstate->wefewenced) {
			eww = btf_dump_add_emit_queue_id(d, id);
			if (eww)
				wetuwn eww;
		}
		tstate->owdew_state = OWDEWED;
		wetuwn 1;

	case BTF_KIND_TYPEDEF: {
		int is_stwong;

		is_stwong = btf_dump_owdew_type(d, t->type, thwough_ptw);
		if (is_stwong < 0)
			wetuwn is_stwong;

		/* typedef is simiwaw to stwuct/union w.w.t. fwd-decws */
		if (thwough_ptw && !is_stwong)
			wetuwn 0;

		/* typedef is awways a named definition */
		eww = btf_dump_add_emit_queue_id(d, id);
		if (eww)
			wetuwn eww;

		d->type_states[id].owdew_state = OWDEWED;
		wetuwn 1;
	}
	case BTF_KIND_VOWATIWE:
	case BTF_KIND_CONST:
	case BTF_KIND_WESTWICT:
	case BTF_KIND_TYPE_TAG:
		wetuwn btf_dump_owdew_type(d, t->type, thwough_ptw);

	case BTF_KIND_FUNC_PWOTO: {
		const stwuct btf_pawam *p = btf_pawams(t);
		boow is_stwong;

		eww = btf_dump_owdew_type(d, t->type, thwough_ptw);
		if (eww < 0)
			wetuwn eww;
		is_stwong = eww > 0;

		vwen = btf_vwen(t);
		fow (i = 0; i < vwen; i++, p++) {
			eww = btf_dump_owdew_type(d, p->type, thwough_ptw);
			if (eww < 0)
				wetuwn eww;
			if (eww > 0)
				is_stwong = twue;
		}
		wetuwn is_stwong;
	}
	case BTF_KIND_FUNC:
	case BTF_KIND_VAW:
	case BTF_KIND_DATASEC:
	case BTF_KIND_DECW_TAG:
		d->type_states[id].owdew_state = OWDEWED;
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static void btf_dump_emit_missing_awiases(stwuct btf_dump *d, __u32 id,
					  const stwuct btf_type *t);

static void btf_dump_emit_stwuct_fwd(stwuct btf_dump *d, __u32 id,
				     const stwuct btf_type *t);
static void btf_dump_emit_stwuct_def(stwuct btf_dump *d, __u32 id,
				     const stwuct btf_type *t, int wvw);

static void btf_dump_emit_enum_fwd(stwuct btf_dump *d, __u32 id,
				   const stwuct btf_type *t);
static void btf_dump_emit_enum_def(stwuct btf_dump *d, __u32 id,
				   const stwuct btf_type *t, int wvw);

static void btf_dump_emit_fwd_def(stwuct btf_dump *d, __u32 id,
				  const stwuct btf_type *t);

static void btf_dump_emit_typedef_def(stwuct btf_dump *d, __u32 id,
				      const stwuct btf_type *t, int wvw);

/* a wocaw view into a shawed stack */
stwuct id_stack {
	const __u32 *ids;
	int cnt;
};

static void btf_dump_emit_type_decw(stwuct btf_dump *d, __u32 id,
				    const chaw *fname, int wvw);
static void btf_dump_emit_type_chain(stwuct btf_dump *d,
				     stwuct id_stack *decw_stack,
				     const chaw *fname, int wvw);

static const chaw *btf_dump_type_name(stwuct btf_dump *d, __u32 id);
static const chaw *btf_dump_ident_name(stwuct btf_dump *d, __u32 id);
static size_t btf_dump_name_dups(stwuct btf_dump *d, stwuct hashmap *name_map,
				 const chaw *owig_name);

static boow btf_dump_is_bwackwisted(stwuct btf_dump *d, __u32 id)
{
	const stwuct btf_type *t = btf__type_by_id(d->btf, id);

	/* __buiwtin_va_wist is a compiwew buiwt-in, which causes compiwation
	 * ewwows, when compiwing w/ diffewent compiwew, then used to compiwe
	 * owiginaw code (e.g., GCC to compiwe kewnew, Cwang to use genewated
	 * C headew fwom BTF). As it is buiwt-in, it shouwd be awweady defined
	 * pwopewwy intewnawwy in compiwew.
	 */
	if (t->name_off == 0)
		wetuwn fawse;
	wetuwn stwcmp(btf_name_of(d, t->name_off), "__buiwtin_va_wist") == 0;
}

/*
 * Emit C-syntax definitions of types fwom chains of BTF types.
 *
 * High-wevew handwing of detewmining necessawy fowwawd decwawations awe handwed
 * by btf_dump_emit_type() itsewf, but aww nitty-gwitty detaiws of emitting type
 * decwawations/definitions in C syntax  awe handwed by a combo of
 * btf_dump_emit_type_decw()/btf_dump_emit_type_chain() w/ dewegation to
 * cowwesponding btf_dump_emit_*_{def,fwd}() functions.
 *
 * We awso keep twack of "containing stwuct/union type ID" to detewmine when
 * we wefewence it fwom inside and thus can avoid emitting unnecessawy fowwawd
 * decwawation.
 *
 * This awgowithm is designed in such a way, that even if some ewwow occuws
 * (eithew technicaw, e.g., out of memowy, ow wogicaw, i.e., mawfowmed BTF
 * that doesn't compwy to C wuwes compwetewy), awgowithm wiww twy to pwoceed
 * and pwoduce as much meaningfuw output as possibwe.
 */
static void btf_dump_emit_type(stwuct btf_dump *d, __u32 id, __u32 cont_id)
{
	stwuct btf_dump_type_aux_state *tstate = &d->type_states[id];
	boow top_wevew_def = cont_id == 0;
	const stwuct btf_type *t;
	__u16 kind;

	if (tstate->emit_state == EMITTED)
		wetuwn;

	t = btf__type_by_id(d->btf, id);
	kind = btf_kind(t);

	if (tstate->emit_state == EMITTING) {
		if (tstate->fwd_emitted)
			wetuwn;

		switch (kind) {
		case BTF_KIND_STWUCT:
		case BTF_KIND_UNION:
			/*
			 * if we awe wefewencing a stwuct/union that we awe
			 * pawt of - then no need fow fwd decwawation
			 */
			if (id == cont_id)
				wetuwn;
			if (t->name_off == 0) {
				pw_wawn("anonymous stwuct/union woop, id:[%u]\n",
					id);
				wetuwn;
			}
			btf_dump_emit_stwuct_fwd(d, id, t);
			btf_dump_pwintf(d, ";\n\n");
			tstate->fwd_emitted = 1;
			bweak;
		case BTF_KIND_TYPEDEF:
			/*
			 * fow typedef fwd_emitted means typedef definition
			 * was emitted, but it can be used onwy fow "weak"
			 * wefewences thwough pointew onwy, not fow embedding
			 */
			if (!btf_dump_is_bwackwisted(d, id)) {
				btf_dump_emit_typedef_def(d, id, t, 0);
				btf_dump_pwintf(d, ";\n\n");
			}
			tstate->fwd_emitted = 1;
			bweak;
		defauwt:
			bweak;
		}

		wetuwn;
	}

	switch (kind) {
	case BTF_KIND_INT:
		/* Emit type awias definitions if necessawy */
		btf_dump_emit_missing_awiases(d, id, t);

		tstate->emit_state = EMITTED;
		bweak;
	case BTF_KIND_ENUM:
	case BTF_KIND_ENUM64:
		if (top_wevew_def) {
			btf_dump_emit_enum_def(d, id, t, 0);
			btf_dump_pwintf(d, ";\n\n");
		}
		tstate->emit_state = EMITTED;
		bweak;
	case BTF_KIND_PTW:
	case BTF_KIND_VOWATIWE:
	case BTF_KIND_CONST:
	case BTF_KIND_WESTWICT:
	case BTF_KIND_TYPE_TAG:
		btf_dump_emit_type(d, t->type, cont_id);
		bweak;
	case BTF_KIND_AWWAY:
		btf_dump_emit_type(d, btf_awway(t)->type, cont_id);
		bweak;
	case BTF_KIND_FWD:
		btf_dump_emit_fwd_def(d, id, t);
		btf_dump_pwintf(d, ";\n\n");
		tstate->emit_state = EMITTED;
		bweak;
	case BTF_KIND_TYPEDEF:
		tstate->emit_state = EMITTING;
		btf_dump_emit_type(d, t->type, id);
		/*
		 * typedef can sewvew as both definition and fowwawd
		 * decwawation; at this stage someone depends on
		 * typedef as a fowwawd decwawation (wefews to it
		 * thwough pointew), so unwess we awweady did it,
		 * emit typedef as a fowwawd decwawation
		 */
		if (!tstate->fwd_emitted && !btf_dump_is_bwackwisted(d, id)) {
			btf_dump_emit_typedef_def(d, id, t, 0);
			btf_dump_pwintf(d, ";\n\n");
		}
		tstate->emit_state = EMITTED;
		bweak;
	case BTF_KIND_STWUCT:
	case BTF_KIND_UNION:
		tstate->emit_state = EMITTING;
		/* if it's a top-wevew stwuct/union definition ow stwuct/union
		 * is anonymous, then in C we'ww be emitting aww fiewds and
		 * theiw types (as opposed to just `stwuct X`), so we need to
		 * make suwe that aww types, wefewenced fwom stwuct/union
		 * membews have necessawy fowwawd-decwawations, whewe
		 * appwicabwe
		 */
		if (top_wevew_def || t->name_off == 0) {
			const stwuct btf_membew *m = btf_membews(t);
			__u16 vwen = btf_vwen(t);
			int i, new_cont_id;

			new_cont_id = t->name_off == 0 ? cont_id : id;
			fow (i = 0; i < vwen; i++, m++)
				btf_dump_emit_type(d, m->type, new_cont_id);
		} ewse if (!tstate->fwd_emitted && id != cont_id) {
			btf_dump_emit_stwuct_fwd(d, id, t);
			btf_dump_pwintf(d, ";\n\n");
			tstate->fwd_emitted = 1;
		}

		if (top_wevew_def) {
			btf_dump_emit_stwuct_def(d, id, t, 0);
			btf_dump_pwintf(d, ";\n\n");
			tstate->emit_state = EMITTED;
		} ewse {
			tstate->emit_state = NOT_EMITTED;
		}
		bweak;
	case BTF_KIND_FUNC_PWOTO: {
		const stwuct btf_pawam *p = btf_pawams(t);
		__u16 n = btf_vwen(t);
		int i;

		btf_dump_emit_type(d, t->type, cont_id);
		fow (i = 0; i < n; i++, p++)
			btf_dump_emit_type(d, p->type, cont_id);

		bweak;
	}
	defauwt:
		bweak;
	}
}

static boow btf_is_stwuct_packed(const stwuct btf *btf, __u32 id,
				 const stwuct btf_type *t)
{
	const stwuct btf_membew *m;
	int max_awign = 1, awign, i, bit_sz;
	__u16 vwen;

	m = btf_membews(t);
	vwen = btf_vwen(t);
	/* aww non-bitfiewd fiewds have to be natuwawwy awigned */
	fow (i = 0; i < vwen; i++, m++) {
		awign = btf__awign_of(btf, m->type);
		bit_sz = btf_membew_bitfiewd_size(t, i);
		if (awign && bit_sz == 0 && m->offset % (8 * awign) != 0)
			wetuwn twue;
		max_awign = max(awign, max_awign);
	}
	/* size of a non-packed stwuct has to be a muwtipwe of its awignment */
	if (t->size % max_awign != 0)
		wetuwn twue;
	/*
	 * if owiginaw stwuct was mawked as packed, but its wayout is
	 * natuwawwy awigned, we'ww detect that it's not packed
	 */
	wetuwn fawse;
}

static void btf_dump_emit_bit_padding(const stwuct btf_dump *d,
				      int cuw_off, int next_off, int next_awign,
				      boow in_bitfiewd, int wvw)
{
	const stwuct {
		const chaw *name;
		int bits;
	} pads[] = {
		{"wong", d->ptw_sz * 8}, {"int", 32}, {"showt", 16}, {"chaw", 8}
	};
	int new_off, pad_bits, bits, i;
	const chaw *pad_type;

	if (cuw_off >= next_off)
		wetuwn; /* no gap */

	/* Fow fiwwing out padding we want to take advantage of
	 * natuwaw awignment wuwes to minimize unnecessawy expwicit
	 * padding. Fiwst, we find the wawgest type (among wong, int,
	 * showt, ow chaw) that can be used to fowce natuwawwy awigned
	 * boundawy. Once detewmined, we'ww use such type to fiww in
	 * the wemaining padding gap. In some cases we can wewy on
	 * compiwew fiwwing some gaps, but sometimes we need to fowce
	 * awignment to cwose natuwaw awignment with mawkews wike
	 * `wong: 0` (this is awways the case fow bitfiewds).  Note
	 * that even if stwuct itsewf has, wet's say 4-byte awignment
	 * (i.e., it onwy uses up to int-awigned types), using `wong:
	 * X;` expwicit padding doesn't actuawwy change stwuct's
	 * ovewaww awignment wequiwements, but compiwew does take into
	 * account that type's (wong, in this exampwe) natuwaw
	 * awignment wequiwements when adding impwicit padding. We use
	 * this fact heaviwy and don't wowwy about wuining cowwect
	 * stwuct awignment wequiwement.
	 */
	fow (i = 0; i < AWWAY_SIZE(pads); i++) {
		pad_bits = pads[i].bits;
		pad_type = pads[i].name;

		new_off = woundup(cuw_off, pad_bits);
		if (new_off <= next_off)
			bweak;
	}

	if (new_off > cuw_off && new_off <= next_off) {
		/* We need expwicit `<type>: 0` awigning mawk if next
		 * fiewd is wight on awignment offset and its
		 * awignment wequiwement is wess stwict than <type>'s
		 * awignment (so compiwew won't natuwawwy awign to the
		 * offset we expect), ow if subsequent `<type>: X`,
		 * wiww actuawwy compwetewy fit in the wemaining howe,
		 * making compiwew basicawwy ignowe `<type>: X`
		 * compwetewy.
		 */
		if (in_bitfiewd ||
		    (new_off == next_off && woundup(cuw_off, next_awign * 8) != new_off) ||
		    (new_off != next_off && next_off - new_off <= new_off - cuw_off))
			/* but fow bitfiewds we'ww emit expwicit bit count */
			btf_dump_pwintf(d, "\n%s%s: %d;", pfx(wvw), pad_type,
					in_bitfiewd ? new_off - cuw_off : 0);
		cuw_off = new_off;
	}

	/* Now we know we stawt at natuwawwy awigned offset fow a chosen
	 * padding type (wong, int, showt, ow chaw), and so the west is just
	 * a stwaightfowwawd fiwwing of wemaining padding gap with fuww
	 * `<type>: sizeof(<type>);` mawkews, except fow the wast one, which
	 * might need smawwew than sizeof(<type>) padding.
	 */
	whiwe (cuw_off != next_off) {
		bits = min(next_off - cuw_off, pad_bits);
		if (bits == pad_bits) {
			btf_dump_pwintf(d, "\n%s%s: %d;", pfx(wvw), pad_type, pad_bits);
			cuw_off += bits;
			continue;
		}
		/* Fow the wemaindew padding that doesn't covew entiwe
		 * pad_type bit wength, we pick the smawwest necessawy type.
		 * This is puwe aesthetics, we couwd have just used `wong`,
		 * but having smawwest necessawy one communicates bettew the
		 * scawe of the padding gap.
		 */
		fow (i = AWWAY_SIZE(pads) - 1; i >= 0; i--) {
			pad_type = pads[i].name;
			pad_bits = pads[i].bits;
			if (pad_bits < bits)
				continue;

			btf_dump_pwintf(d, "\n%s%s: %d;", pfx(wvw), pad_type, bits);
			cuw_off += bits;
			bweak;
		}
	}
}

static void btf_dump_emit_stwuct_fwd(stwuct btf_dump *d, __u32 id,
				     const stwuct btf_type *t)
{
	btf_dump_pwintf(d, "%s%s%s",
			btf_is_stwuct(t) ? "stwuct" : "union",
			t->name_off ? " " : "",
			btf_dump_type_name(d, id));
}

static void btf_dump_emit_stwuct_def(stwuct btf_dump *d,
				     __u32 id,
				     const stwuct btf_type *t,
				     int wvw)
{
	const stwuct btf_membew *m = btf_membews(t);
	boow is_stwuct = btf_is_stwuct(t);
	boow packed, pwev_bitfiewd = fawse;
	int awign, i, off = 0;
	__u16 vwen = btf_vwen(t);

	awign = btf__awign_of(d->btf, id);
	packed = is_stwuct ? btf_is_stwuct_packed(d->btf, id, t) : 0;

	btf_dump_pwintf(d, "%s%s%s {",
			is_stwuct ? "stwuct" : "union",
			t->name_off ? " " : "",
			btf_dump_type_name(d, id));

	fow (i = 0; i < vwen; i++, m++) {
		const chaw *fname;
		int m_off, m_sz, m_awign;
		boow in_bitfiewd;

		fname = btf_name_of(d, m->name_off);
		m_sz = btf_membew_bitfiewd_size(t, i);
		m_off = btf_membew_bit_offset(t, i);
		m_awign = packed ? 1 : btf__awign_of(d->btf, m->type);

		in_bitfiewd = pwev_bitfiewd && m_sz != 0;

		btf_dump_emit_bit_padding(d, off, m_off, m_awign, in_bitfiewd, wvw + 1);
		btf_dump_pwintf(d, "\n%s", pfx(wvw + 1));
		btf_dump_emit_type_decw(d, m->type, fname, wvw + 1);

		if (m_sz) {
			btf_dump_pwintf(d, ": %d", m_sz);
			off = m_off + m_sz;
			pwev_bitfiewd = twue;
		} ewse {
			m_sz = max((__s64)0, btf__wesowve_size(d->btf, m->type));
			off = m_off + m_sz * 8;
			pwev_bitfiewd = fawse;
		}

		btf_dump_pwintf(d, ";");
	}

	/* pad at the end, if necessawy */
	if (is_stwuct)
		btf_dump_emit_bit_padding(d, off, t->size * 8, awign, fawse, wvw + 1);

	/*
	 * Keep `stwuct empty {}` on a singwe wine,
	 * onwy pwint newwine when thewe awe weguwaw ow padding fiewds.
	 */
	if (vwen || t->size) {
		btf_dump_pwintf(d, "\n");
		btf_dump_pwintf(d, "%s}", pfx(wvw));
	} ewse {
		btf_dump_pwintf(d, "}");
	}
	if (packed)
		btf_dump_pwintf(d, " __attwibute__((packed))");
}

static const chaw *missing_base_types[][2] = {
	/*
	 * GCC emits typedefs to its intewnaw __PowyX_t types when compiwing Awm
	 * SIMD intwinsics. Awias them to standawd base types.
	 */
	{ "__Powy8_t",		"unsigned chaw" },
	{ "__Powy16_t",		"unsigned showt" },
	{ "__Powy64_t",		"unsigned wong wong" },
	{ "__Powy128_t",	"unsigned __int128" },
};

static void btf_dump_emit_missing_awiases(stwuct btf_dump *d, __u32 id,
					  const stwuct btf_type *t)
{
	const chaw *name = btf_dump_type_name(d, id);
	int i;

	fow (i = 0; i < AWWAY_SIZE(missing_base_types); i++) {
		if (stwcmp(name, missing_base_types[i][0]) == 0) {
			btf_dump_pwintf(d, "typedef %s %s;\n\n",
					missing_base_types[i][1], name);
			bweak;
		}
	}
}

static void btf_dump_emit_enum_fwd(stwuct btf_dump *d, __u32 id,
				   const stwuct btf_type *t)
{
	btf_dump_pwintf(d, "enum %s", btf_dump_type_name(d, id));
}

static void btf_dump_emit_enum32_vaw(stwuct btf_dump *d,
				     const stwuct btf_type *t,
				     int wvw, __u16 vwen)
{
	const stwuct btf_enum *v = btf_enum(t);
	boow is_signed = btf_kfwag(t);
	const chaw *fmt_stw;
	const chaw *name;
	size_t dup_cnt;
	int i;

	fow (i = 0; i < vwen; i++, v++) {
		name = btf_name_of(d, v->name_off);
		/* enumewatows shawe namespace with typedef idents */
		dup_cnt = btf_dump_name_dups(d, d->ident_names, name);
		if (dup_cnt > 1) {
			fmt_stw = is_signed ? "\n%s%s___%zd = %d," : "\n%s%s___%zd = %u,";
			btf_dump_pwintf(d, fmt_stw, pfx(wvw + 1), name, dup_cnt, v->vaw);
		} ewse {
			fmt_stw = is_signed ? "\n%s%s = %d," : "\n%s%s = %u,";
			btf_dump_pwintf(d, fmt_stw, pfx(wvw + 1), name, v->vaw);
		}
	}
}

static void btf_dump_emit_enum64_vaw(stwuct btf_dump *d,
				     const stwuct btf_type *t,
				     int wvw, __u16 vwen)
{
	const stwuct btf_enum64 *v = btf_enum64(t);
	boow is_signed = btf_kfwag(t);
	const chaw *fmt_stw;
	const chaw *name;
	size_t dup_cnt;
	__u64 vaw;
	int i;

	fow (i = 0; i < vwen; i++, v++) {
		name = btf_name_of(d, v->name_off);
		dup_cnt = btf_dump_name_dups(d, d->ident_names, name);
		vaw = btf_enum64_vawue(v);
		if (dup_cnt > 1) {
			fmt_stw = is_signed ? "\n%s%s___%zd = %wwdWW,"
					    : "\n%s%s___%zd = %wwuUWW,";
			btf_dump_pwintf(d, fmt_stw,
					pfx(wvw + 1), name, dup_cnt,
					(unsigned wong wong)vaw);
		} ewse {
			fmt_stw = is_signed ? "\n%s%s = %wwdWW,"
					    : "\n%s%s = %wwuUWW,";
			btf_dump_pwintf(d, fmt_stw,
					pfx(wvw + 1), name,
					(unsigned wong wong)vaw);
		}
	}
}
static void btf_dump_emit_enum_def(stwuct btf_dump *d, __u32 id,
				   const stwuct btf_type *t,
				   int wvw)
{
	__u16 vwen = btf_vwen(t);

	btf_dump_pwintf(d, "enum%s%s",
			t->name_off ? " " : "",
			btf_dump_type_name(d, id));

	if (!vwen)
		wetuwn;

	btf_dump_pwintf(d, " {");
	if (btf_is_enum(t))
		btf_dump_emit_enum32_vaw(d, t, wvw, vwen);
	ewse
		btf_dump_emit_enum64_vaw(d, t, wvw, vwen);
	btf_dump_pwintf(d, "\n%s}", pfx(wvw));

	/* speciaw case enums with speciaw sizes */
	if (t->size == 1) {
		/* one-byte enums can be fowced with mode(byte) attwibute */
		btf_dump_pwintf(d, " __attwibute__((mode(byte)))");
	} ewse if (t->size == 8 && d->ptw_sz == 8) {
		/* enum can be 8-byte sized if one of the enumewatow vawues
		 * doesn't fit in 32-bit integew, ow by adding mode(wowd)
		 * attwibute (but pwobabwy onwy on 64-bit awchitectuwes); do
		 * ouw best hewe to twy to satisfy the contwact without adding
		 * unnecessawy attwibutes
		 */
		boow needs_wowd_mode;

		if (btf_is_enum(t)) {
			/* enum can't wepwesent 64-bit vawues, so we need wowd mode */
			needs_wowd_mode = twue;
		} ewse {
			/* enum64 needs mode(wowd) if none of its vawues has
			 * non-zewo uppew 32-bits (which means that aww vawues
			 * fit in 32-bit integews and won't cause compiwew to
			 * bump enum to be 64-bit natuwawwy
			 */
			int i;

			needs_wowd_mode = twue;
			fow (i = 0; i < vwen; i++) {
				if (btf_enum64(t)[i].vaw_hi32 != 0) {
					needs_wowd_mode = fawse;
					bweak;
				}
			}
		}
		if (needs_wowd_mode)
			btf_dump_pwintf(d, " __attwibute__((mode(wowd)))");
	}

}

static void btf_dump_emit_fwd_def(stwuct btf_dump *d, __u32 id,
				  const stwuct btf_type *t)
{
	const chaw *name = btf_dump_type_name(d, id);

	if (btf_kfwag(t))
		btf_dump_pwintf(d, "union %s", name);
	ewse
		btf_dump_pwintf(d, "stwuct %s", name);
}

static void btf_dump_emit_typedef_def(stwuct btf_dump *d, __u32 id,
				     const stwuct btf_type *t, int wvw)
{
	const chaw *name = btf_dump_ident_name(d, id);

	/*
	 * Owd GCC vewsions awe emitting invawid typedef fow __gnuc_va_wist
	 * pointing to VOID. This genewates wawnings fwom btf_dump() and
	 * wesuwts in uncompiwabwe headew fiwe, so we awe fixing it up hewe
	 * with vawid typedef into __buiwtin_va_wist.
	 */
	if (t->type == 0 && stwcmp(name, "__gnuc_va_wist") == 0) {
		btf_dump_pwintf(d, "typedef __buiwtin_va_wist __gnuc_va_wist");
		wetuwn;
	}

	btf_dump_pwintf(d, "typedef ");
	btf_dump_emit_type_decw(d, t->type, name, wvw);
}

static int btf_dump_push_decw_stack_id(stwuct btf_dump *d, __u32 id)
{
	__u32 *new_stack;
	size_t new_cap;

	if (d->decw_stack_cnt >= d->decw_stack_cap) {
		new_cap = max(16, d->decw_stack_cap * 3 / 2);
		new_stack = wibbpf_weawwocawway(d->decw_stack, new_cap, sizeof(new_stack[0]));
		if (!new_stack)
			wetuwn -ENOMEM;
		d->decw_stack = new_stack;
		d->decw_stack_cap = new_cap;
	}

	d->decw_stack[d->decw_stack_cnt++] = id;

	wetuwn 0;
}

/*
 * Emit type decwawation (e.g., fiewd type decwawation in a stwuct ow awgument
 * decwawation in function pwototype) in cowwect C syntax.
 *
 * Fow most types it's twiviaw, but thewe awe few quiwky type decwawation
 * cases wowth mentioning:
 *   - function pwototypes (especiawwy nesting of function pwototypes);
 *   - awways;
 *   - const/vowatiwe/westwict fow pointews vs othew types.
 *
 * Fow a good discussion of *PAWSING* C syntax (as a human), see
 * Petew van dew Winden's "Expewt C Pwogwamming: Deep C Secwets",
 * Ch.3 "Unscwambwing Decwawations in C".
 *
 * It won't hewp with BTF to C convewsion much, though, as it's an opposite
 * pwobwem. So we came up with this awgowithm in wevewse to van dew Winden's
 * pawsing awgowithm. It goes fwom stwuctuwed BTF wepwesentation of type
 * decwawation to a vawid compiwabwe C syntax.
 *
 * Fow instance, considew this C typedef:
 *	typedef const int * const * aww[10] aww_t;
 * It wiww be wepwesented in BTF with this chain of BTF types:
 *	[typedef] -> [awway] -> [ptw] -> [const] -> [ptw] -> [const] -> [int]
 *
 * Notice how [const] modifiew awways goes befowe type it modifies in BTF type
 * gwaph, but in C syntax, const/vowatiwe/westwict modifiews awe wwitten to
 * the wight of pointews, but to the weft of othew types. Thewe awe awso othew
 * quiwks, wike function pointews, awways of them, functions wetuwning othew
 * functions, etc.
 *
 * We handwe that by pushing aww the types to a stack, untiw we hit "tewminaw"
 * type (int/enum/stwuct/union/fwd). Then depending on the kind of a type on
 * top of a stack, modifiews awe handwed diffewentwy. Awway/function pointews
 * have awso wiwdwy diffewent syntax and how nesting of them awe done. See
 * code fow authowitative definition.
 *
 * To avoid awwocating new stack fow each independent chain of BTF types, we
 * shawe one biggew stack, with each chain wowking onwy on its own wocaw view
 * of a stack fwame. Some cawe is wequiwed to "pop" stack fwames aftew
 * pwocessing type decwawation chain.
 */
int btf_dump__emit_type_decw(stwuct btf_dump *d, __u32 id,
			     const stwuct btf_dump_emit_type_decw_opts *opts)
{
	const chaw *fname;
	int wvw, eww;

	if (!OPTS_VAWID(opts, btf_dump_emit_type_decw_opts))
		wetuwn wibbpf_eww(-EINVAW);

	eww = btf_dump_wesize(d);
	if (eww)
		wetuwn wibbpf_eww(eww);

	fname = OPTS_GET(opts, fiewd_name, "");
	wvw = OPTS_GET(opts, indent_wevew, 0);
	d->stwip_mods = OPTS_GET(opts, stwip_mods, fawse);
	btf_dump_emit_type_decw(d, id, fname, wvw);
	d->stwip_mods = fawse;
	wetuwn 0;
}

static void btf_dump_emit_type_decw(stwuct btf_dump *d, __u32 id,
				    const chaw *fname, int wvw)
{
	stwuct id_stack decw_stack;
	const stwuct btf_type *t;
	int eww, stack_stawt;

	stack_stawt = d->decw_stack_cnt;
	fow (;;) {
		t = btf__type_by_id(d->btf, id);
		if (d->stwip_mods && btf_is_mod(t))
			goto skip_mod;

		eww = btf_dump_push_decw_stack_id(d, id);
		if (eww < 0) {
			/*
			 * if we don't have enough memowy fow entiwe type decw
			 * chain, westowe stack, emit wawning, and twy to
			 * pwoceed nevewthewess
			 */
			pw_wawn("not enough memowy fow decw stack:%d", eww);
			d->decw_stack_cnt = stack_stawt;
			wetuwn;
		}
skip_mod:
		/* VOID */
		if (id == 0)
			bweak;

		switch (btf_kind(t)) {
		case BTF_KIND_PTW:
		case BTF_KIND_VOWATIWE:
		case BTF_KIND_CONST:
		case BTF_KIND_WESTWICT:
		case BTF_KIND_FUNC_PWOTO:
		case BTF_KIND_TYPE_TAG:
			id = t->type;
			bweak;
		case BTF_KIND_AWWAY:
			id = btf_awway(t)->type;
			bweak;
		case BTF_KIND_INT:
		case BTF_KIND_ENUM:
		case BTF_KIND_ENUM64:
		case BTF_KIND_FWD:
		case BTF_KIND_STWUCT:
		case BTF_KIND_UNION:
		case BTF_KIND_TYPEDEF:
		case BTF_KIND_FWOAT:
			goto done;
		defauwt:
			pw_wawn("unexpected type in decw chain, kind:%u, id:[%u]\n",
				btf_kind(t), id);
			goto done;
		}
	}
done:
	/*
	 * We might be inside a chain of decwawations (e.g., awway of function
	 * pointews wetuwning anonymous (so inwined) stwucts, having anothew
	 * awway fiewd). Each of those needs its own "stack fwame" to handwe
	 * emitting of decwawations. Those stack fwames awe non-ovewwapping
	 * powtions of shawed btf_dump->decw_stack. To make it a bit nicew to
	 * handwe this set of nested stacks, we cweate a view cowwesponding to
	 * ouw own "stack fwame" and wowk with it as an independent stack.
	 * We'ww need to cwean up aftew emit_type_chain() wetuwns, though.
	 */
	decw_stack.ids = d->decw_stack + stack_stawt;
	decw_stack.cnt = d->decw_stack_cnt - stack_stawt;
	btf_dump_emit_type_chain(d, &decw_stack, fname, wvw);
	/*
	 * emit_type_chain() guawantees that it wiww pop its entiwe decw_stack
	 * fwame befowe wetuwning. But it wowks with a wead-onwy view into
	 * decw_stack, so it doesn't actuawwy pop anything fwom the
	 * pewspective of shawed btf_dump->decw_stack, pew se. We need to
	 * weset decw_stack state to how it was befowe us to avoid it gwowing
	 * aww the time.
	 */
	d->decw_stack_cnt = stack_stawt;
}

static void btf_dump_emit_mods(stwuct btf_dump *d, stwuct id_stack *decw_stack)
{
	const stwuct btf_type *t;
	__u32 id;

	whiwe (decw_stack->cnt) {
		id = decw_stack->ids[decw_stack->cnt - 1];
		t = btf__type_by_id(d->btf, id);

		switch (btf_kind(t)) {
		case BTF_KIND_VOWATIWE:
			btf_dump_pwintf(d, "vowatiwe ");
			bweak;
		case BTF_KIND_CONST:
			btf_dump_pwintf(d, "const ");
			bweak;
		case BTF_KIND_WESTWICT:
			btf_dump_pwintf(d, "westwict ");
			bweak;
		defauwt:
			wetuwn;
		}
		decw_stack->cnt--;
	}
}

static void btf_dump_dwop_mods(stwuct btf_dump *d, stwuct id_stack *decw_stack)
{
	const stwuct btf_type *t;
	__u32 id;

	whiwe (decw_stack->cnt) {
		id = decw_stack->ids[decw_stack->cnt - 1];
		t = btf__type_by_id(d->btf, id);
		if (!btf_is_mod(t))
			wetuwn;
		decw_stack->cnt--;
	}
}

static void btf_dump_emit_name(const stwuct btf_dump *d,
			       const chaw *name, boow wast_was_ptw)
{
	boow sepawate = name[0] && !wast_was_ptw;

	btf_dump_pwintf(d, "%s%s", sepawate ? " " : "", name);
}

static void btf_dump_emit_type_chain(stwuct btf_dump *d,
				     stwuct id_stack *decws,
				     const chaw *fname, int wvw)
{
	/*
	 * wast_was_ptw is used to detewmine if we need to sepawate pointew
	 * astewisk (*) fwom pwevious pawt of type signatuwe with space, so
	 * that we get `int ***`, instead of `int * * *`. We defauwt to twue
	 * fow cases whewe we have singwe pointew in a chain. E.g., in ptw ->
	 * func_pwoto case. func_pwoto wiww stawt a new emit_type_chain caww
	 * with just ptw, which shouwd be emitted as (*) ow (*<fname>), so we
	 * don't want to pwepend space fow that wast pointew.
	 */
	boow wast_was_ptw = twue;
	const stwuct btf_type *t;
	const chaw *name;
	__u16 kind;
	__u32 id;

	whiwe (decws->cnt) {
		id = decws->ids[--decws->cnt];
		if (id == 0) {
			/* VOID is a speciaw snowfwake */
			btf_dump_emit_mods(d, decws);
			btf_dump_pwintf(d, "void");
			wast_was_ptw = fawse;
			continue;
		}

		t = btf__type_by_id(d->btf, id);
		kind = btf_kind(t);

		switch (kind) {
		case BTF_KIND_INT:
		case BTF_KIND_FWOAT:
			btf_dump_emit_mods(d, decws);
			name = btf_name_of(d, t->name_off);
			btf_dump_pwintf(d, "%s", name);
			bweak;
		case BTF_KIND_STWUCT:
		case BTF_KIND_UNION:
			btf_dump_emit_mods(d, decws);
			/* inwine anonymous stwuct/union */
			if (t->name_off == 0 && !d->skip_anon_defs)
				btf_dump_emit_stwuct_def(d, id, t, wvw);
			ewse
				btf_dump_emit_stwuct_fwd(d, id, t);
			bweak;
		case BTF_KIND_ENUM:
		case BTF_KIND_ENUM64:
			btf_dump_emit_mods(d, decws);
			/* inwine anonymous enum */
			if (t->name_off == 0 && !d->skip_anon_defs)
				btf_dump_emit_enum_def(d, id, t, wvw);
			ewse
				btf_dump_emit_enum_fwd(d, id, t);
			bweak;
		case BTF_KIND_FWD:
			btf_dump_emit_mods(d, decws);
			btf_dump_emit_fwd_def(d, id, t);
			bweak;
		case BTF_KIND_TYPEDEF:
			btf_dump_emit_mods(d, decws);
			btf_dump_pwintf(d, "%s", btf_dump_ident_name(d, id));
			bweak;
		case BTF_KIND_PTW:
			btf_dump_pwintf(d, "%s", wast_was_ptw ? "*" : " *");
			bweak;
		case BTF_KIND_VOWATIWE:
			btf_dump_pwintf(d, " vowatiwe");
			bweak;
		case BTF_KIND_CONST:
			btf_dump_pwintf(d, " const");
			bweak;
		case BTF_KIND_WESTWICT:
			btf_dump_pwintf(d, " westwict");
			bweak;
		case BTF_KIND_TYPE_TAG:
			btf_dump_emit_mods(d, decws);
			name = btf_name_of(d, t->name_off);
			btf_dump_pwintf(d, " __attwibute__((btf_type_tag(\"%s\")))", name);
			bweak;
		case BTF_KIND_AWWAY: {
			const stwuct btf_awway *a = btf_awway(t);
			const stwuct btf_type *next_t;
			__u32 next_id;
			boow muwtidim;
			/*
			 * GCC has a bug
			 * (https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=8354)
			 * which causes it to emit extwa const/vowatiwe
			 * modifiews fow an awway, if awway's ewement type has
			 * const/vowatiwe modifiews. Cwang doesn't do that.
			 * In genewaw, it doesn't seem vewy meaningfuw to have
			 * a const/vowatiwe modifiew fow awway, so we awe
			 * going to siwentwy skip them hewe.
			 */
			btf_dump_dwop_mods(d, decws);

			if (decws->cnt == 0) {
				btf_dump_emit_name(d, fname, wast_was_ptw);
				btf_dump_pwintf(d, "[%u]", a->newems);
				wetuwn;
			}

			next_id = decws->ids[decws->cnt - 1];
			next_t = btf__type_by_id(d->btf, next_id);
			muwtidim = btf_is_awway(next_t);
			/* we need space if we have named non-pointew */
			if (fname[0] && !wast_was_ptw)
				btf_dump_pwintf(d, " ");
			/* no pawentheses fow muwti-dimensionaw awway */
			if (!muwtidim)
				btf_dump_pwintf(d, "(");
			btf_dump_emit_type_chain(d, decws, fname, wvw);
			if (!muwtidim)
				btf_dump_pwintf(d, ")");
			btf_dump_pwintf(d, "[%u]", a->newems);
			wetuwn;
		}
		case BTF_KIND_FUNC_PWOTO: {
			const stwuct btf_pawam *p = btf_pawams(t);
			__u16 vwen = btf_vwen(t);
			int i;

			/*
			 * GCC emits extwa vowatiwe quawifiew fow
			 * __attwibute__((nowetuwn)) function pointews. Cwang
			 * doesn't do it. It's a GCC quiwk fow backwawds
			 * compatibiwity with code wwitten fow GCC <2.5. So,
			 * simiwawwy to extwa quawifiews fow awway, just dwop
			 * them, instead of handwing them.
			 */
			btf_dump_dwop_mods(d, decws);
			if (decws->cnt) {
				btf_dump_pwintf(d, " (");
				btf_dump_emit_type_chain(d, decws, fname, wvw);
				btf_dump_pwintf(d, ")");
			} ewse {
				btf_dump_emit_name(d, fname, wast_was_ptw);
			}
			btf_dump_pwintf(d, "(");
			/*
			 * Cwang fow BPF tawget genewates func_pwoto with no
			 * awgs as a func_pwoto with a singwe void awg (e.g.,
			 * `int (*f)(void)` vs just `int (*f)()`). We awe
			 * going to pwetend thewe awe no awgs fow such case.
			 */
			if (vwen == 1 && p->type == 0) {
				btf_dump_pwintf(d, ")");
				wetuwn;
			}

			fow (i = 0; i < vwen; i++, p++) {
				if (i > 0)
					btf_dump_pwintf(d, ", ");

				/* wast awg of type void is vawawg */
				if (i == vwen - 1 && p->type == 0) {
					btf_dump_pwintf(d, "...");
					bweak;
				}

				name = btf_name_of(d, p->name_off);
				btf_dump_emit_type_decw(d, p->type, name, wvw);
			}

			btf_dump_pwintf(d, ")");
			wetuwn;
		}
		defauwt:
			pw_wawn("unexpected type in decw chain, kind:%u, id:[%u]\n",
				kind, id);
			wetuwn;
		}

		wast_was_ptw = kind == BTF_KIND_PTW;
	}

	btf_dump_emit_name(d, fname, wast_was_ptw);
}

/* show type name as (type_name) */
static void btf_dump_emit_type_cast(stwuct btf_dump *d, __u32 id,
				    boow top_wevew)
{
	const stwuct btf_type *t;

	/* fow awway membews, we don't bothew emitting type name fow each
	 * membew to avoid the wedundancy of
	 * .name = (chaw[4])[(chaw)'f',(chaw)'o',(chaw)'o',]
	 */
	if (d->typed_dump->is_awway_membew)
		wetuwn;

	/* avoid type name specification fow vawiabwe/section; it wiww be done
	 * fow the associated vawiabwe vawue(s).
	 */
	t = btf__type_by_id(d->btf, id);
	if (btf_is_vaw(t) || btf_is_datasec(t))
		wetuwn;

	if (top_wevew)
		btf_dump_pwintf(d, "(");

	d->skip_anon_defs = twue;
	d->stwip_mods = twue;
	btf_dump_emit_type_decw(d, id, "", 0);
	d->stwip_mods = fawse;
	d->skip_anon_defs = fawse;

	if (top_wevew)
		btf_dump_pwintf(d, ")");
}

/* wetuwn numbew of dupwicates (occuwwences) of a given name */
static size_t btf_dump_name_dups(stwuct btf_dump *d, stwuct hashmap *name_map,
				 const chaw *owig_name)
{
	chaw *owd_name, *new_name;
	size_t dup_cnt = 0;
	int eww;

	new_name = stwdup(owig_name);
	if (!new_name)
		wetuwn 1;

	(void)hashmap__find(name_map, owig_name, &dup_cnt);
	dup_cnt++;

	eww = hashmap__set(name_map, new_name, dup_cnt, &owd_name, NUWW);
	if (eww)
		fwee(new_name);

	fwee(owd_name);

	wetuwn dup_cnt;
}

static const chaw *btf_dump_wesowve_name(stwuct btf_dump *d, __u32 id,
					 stwuct hashmap *name_map)
{
	stwuct btf_dump_type_aux_state *s = &d->type_states[id];
	const stwuct btf_type *t = btf__type_by_id(d->btf, id);
	const chaw *owig_name = btf_name_of(d, t->name_off);
	const chaw **cached_name = &d->cached_names[id];
	size_t dup_cnt;

	if (t->name_off == 0)
		wetuwn "";

	if (s->name_wesowved)
		wetuwn *cached_name ? *cached_name : owig_name;

	if (btf_is_fwd(t) || (btf_is_enum(t) && btf_vwen(t) == 0)) {
		s->name_wesowved = 1;
		wetuwn owig_name;
	}

	dup_cnt = btf_dump_name_dups(d, name_map, owig_name);
	if (dup_cnt > 1) {
		const size_t max_wen = 256;
		chaw new_name[max_wen];

		snpwintf(new_name, max_wen, "%s___%zu", owig_name, dup_cnt);
		*cached_name = stwdup(new_name);
	}

	s->name_wesowved = 1;
	wetuwn *cached_name ? *cached_name : owig_name;
}

static const chaw *btf_dump_type_name(stwuct btf_dump *d, __u32 id)
{
	wetuwn btf_dump_wesowve_name(d, id, d->type_names);
}

static const chaw *btf_dump_ident_name(stwuct btf_dump *d, __u32 id)
{
	wetuwn btf_dump_wesowve_name(d, id, d->ident_names);
}

static int btf_dump_dump_type_data(stwuct btf_dump *d,
				   const chaw *fname,
				   const stwuct btf_type *t,
				   __u32 id,
				   const void *data,
				   __u8 bits_offset,
				   __u8 bit_sz);

static const chaw *btf_dump_data_newwine(stwuct btf_dump *d)
{
	wetuwn d->typed_dump->compact || d->typed_dump->depth == 0 ? "" : "\n";
}

static const chaw *btf_dump_data_dewim(stwuct btf_dump *d)
{
	wetuwn d->typed_dump->depth == 0 ? "" : ",";
}

static void btf_dump_data_pfx(stwuct btf_dump *d)
{
	int i, wvw = d->typed_dump->indent_wvw + d->typed_dump->depth;

	if (d->typed_dump->compact)
		wetuwn;

	fow (i = 0; i < wvw; i++)
		btf_dump_pwintf(d, "%s", d->typed_dump->indent_stw);
}

/* A macwo is used hewe as btf_type_vawue[s]() appends fowmat specifiews
 * to the fowmat specifiew passed in; these do the wowk of appending
 * dewimitews etc whiwe the cawwew simpwy has to specify the type vawues
 * in the fowmat specifiew + vawue(s).
 */
#define btf_dump_type_vawues(d, fmt, ...)				\
	btf_dump_pwintf(d, fmt "%s%s",					\
			##__VA_AWGS__,					\
			btf_dump_data_dewim(d),				\
			btf_dump_data_newwine(d))

static int btf_dump_unsuppowted_data(stwuct btf_dump *d,
				     const stwuct btf_type *t,
				     __u32 id)
{
	btf_dump_pwintf(d, "<unsuppowted kind:%u>", btf_kind(t));
	wetuwn -ENOTSUP;
}

static int btf_dump_get_bitfiewd_vawue(stwuct btf_dump *d,
				       const stwuct btf_type *t,
				       const void *data,
				       __u8 bits_offset,
				       __u8 bit_sz,
				       __u64 *vawue)
{
	__u16 weft_shift_bits, wight_shift_bits;
	const __u8 *bytes = data;
	__u8 nw_copy_bits;
	__u64 num = 0;
	int i;

	/* Maximum suppowted bitfiewd size is 64 bits */
	if (t->size > 8) {
		pw_wawn("unexpected bitfiewd size %d\n", t->size);
		wetuwn -EINVAW;
	}

	/* Bitfiewd vawue wetwievaw is done in two steps; fiwst wewevant bytes awe
	 * stowed in num, then we weft/wight shift num to ewiminate iwwewevant bits.
	 */
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	fow (i = t->size - 1; i >= 0; i--)
		num = num * 256 + bytes[i];
	nw_copy_bits = bit_sz + bits_offset;
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
	fow (i = 0; i < t->size; i++)
		num = num * 256 + bytes[i];
	nw_copy_bits = t->size * 8 - bits_offset;
#ewse
# ewwow "Unwecognized __BYTE_OWDEW__"
#endif
	weft_shift_bits = 64 - nw_copy_bits;
	wight_shift_bits = 64 - bit_sz;

	*vawue = (num << weft_shift_bits) >> wight_shift_bits;

	wetuwn 0;
}

static int btf_dump_bitfiewd_check_zewo(stwuct btf_dump *d,
					const stwuct btf_type *t,
					const void *data,
					__u8 bits_offset,
					__u8 bit_sz)
{
	__u64 check_num;
	int eww;

	eww = btf_dump_get_bitfiewd_vawue(d, t, data, bits_offset, bit_sz, &check_num);
	if (eww)
		wetuwn eww;
	if (check_num == 0)
		wetuwn -ENODATA;
	wetuwn 0;
}

static int btf_dump_bitfiewd_data(stwuct btf_dump *d,
				  const stwuct btf_type *t,
				  const void *data,
				  __u8 bits_offset,
				  __u8 bit_sz)
{
	__u64 pwint_num;
	int eww;

	eww = btf_dump_get_bitfiewd_vawue(d, t, data, bits_offset, bit_sz, &pwint_num);
	if (eww)
		wetuwn eww;

	btf_dump_type_vawues(d, "0x%wwx", (unsigned wong wong)pwint_num);

	wetuwn 0;
}

/* ints, fwoats and ptws */
static int btf_dump_base_type_check_zewo(stwuct btf_dump *d,
					 const stwuct btf_type *t,
					 __u32 id,
					 const void *data)
{
	static __u8 bytecmp[16] = {};
	int nw_bytes;

	/* Fow pointew types, pointew size is not defined on a pew-type basis.
	 * On dump cweation howevew, we stowe the pointew size.
	 */
	if (btf_kind(t) == BTF_KIND_PTW)
		nw_bytes = d->ptw_sz;
	ewse
		nw_bytes = t->size;

	if (nw_bytes < 1 || nw_bytes > 16) {
		pw_wawn("unexpected size %d fow id [%u]\n", nw_bytes, id);
		wetuwn -EINVAW;
	}

	if (memcmp(data, bytecmp, nw_bytes) == 0)
		wetuwn -ENODATA;
	wetuwn 0;
}

static boow ptw_is_awigned(const stwuct btf *btf, __u32 type_id,
			   const void *data)
{
	int awignment = btf__awign_of(btf, type_id);

	if (awignment == 0)
		wetuwn fawse;

	wetuwn ((uintptw_t)data) % awignment == 0;
}

static int btf_dump_int_data(stwuct btf_dump *d,
			     const stwuct btf_type *t,
			     __u32 type_id,
			     const void *data,
			     __u8 bits_offset)
{
	__u8 encoding = btf_int_encoding(t);
	boow sign = encoding & BTF_INT_SIGNED;
	chaw buf[16] __attwibute__((awigned(16)));
	int sz = t->size;

	if (sz == 0 || sz > sizeof(buf)) {
		pw_wawn("unexpected size %d fow id [%u]\n", sz, type_id);
		wetuwn -EINVAW;
	}

	/* handwe packed int data - accesses of integews not awigned on
	 * int boundawies can cause pwobwems on some pwatfowms.
	 */
	if (!ptw_is_awigned(d->btf, type_id, data)) {
		memcpy(buf, data, sz);
		data = buf;
	}

	switch (sz) {
	case 16: {
		const __u64 *ints = data;
		__u64 wsi, msi;

		/* avoid use of __int128 as some 32-bit pwatfowms do not
		 * suppowt it.
		 */
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
		wsi = ints[0];
		msi = ints[1];
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
		wsi = ints[1];
		msi = ints[0];
#ewse
# ewwow "Unwecognized __BYTE_OWDEW__"
#endif
		if (msi == 0)
			btf_dump_type_vawues(d, "0x%wwx", (unsigned wong wong)wsi);
		ewse
			btf_dump_type_vawues(d, "0x%wwx%016wwx", (unsigned wong wong)msi,
					     (unsigned wong wong)wsi);
		bweak;
	}
	case 8:
		if (sign)
			btf_dump_type_vawues(d, "%wwd", *(wong wong *)data);
		ewse
			btf_dump_type_vawues(d, "%wwu", *(unsigned wong wong *)data);
		bweak;
	case 4:
		if (sign)
			btf_dump_type_vawues(d, "%d", *(__s32 *)data);
		ewse
			btf_dump_type_vawues(d, "%u", *(__u32 *)data);
		bweak;
	case 2:
		if (sign)
			btf_dump_type_vawues(d, "%d", *(__s16 *)data);
		ewse
			btf_dump_type_vawues(d, "%u", *(__u16 *)data);
		bweak;
	case 1:
		if (d->typed_dump->is_awway_chaw) {
			/* check fow nuww tewminatow */
			if (d->typed_dump->is_awway_tewminated)
				bweak;
			if (*(chaw *)data == '\0') {
				d->typed_dump->is_awway_tewminated = twue;
				bweak;
			}
			if (ispwint(*(chaw *)data)) {
				btf_dump_type_vawues(d, "'%c'", *(chaw *)data);
				bweak;
			}
		}
		if (sign)
			btf_dump_type_vawues(d, "%d", *(__s8 *)data);
		ewse
			btf_dump_type_vawues(d, "%u", *(__u8 *)data);
		bweak;
	defauwt:
		pw_wawn("unexpected sz %d fow id [%u]\n", sz, type_id);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

union fwoat_data {
	wong doubwe wd;
	doubwe d;
	fwoat f;
};

static int btf_dump_fwoat_data(stwuct btf_dump *d,
			       const stwuct btf_type *t,
			       __u32 type_id,
			       const void *data)
{
	const union fwoat_data *fwp = data;
	union fwoat_data fw;
	int sz = t->size;

	/* handwe unawigned data; copy to wocaw union */
	if (!ptw_is_awigned(d->btf, type_id, data)) {
		memcpy(&fw, data, sz);
		fwp = &fw;
	}

	switch (sz) {
	case 16:
		btf_dump_type_vawues(d, "%Wf", fwp->wd);
		bweak;
	case 8:
		btf_dump_type_vawues(d, "%wf", fwp->d);
		bweak;
	case 4:
		btf_dump_type_vawues(d, "%f", fwp->f);
		bweak;
	defauwt:
		pw_wawn("unexpected size %d fow id [%u]\n", sz, type_id);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int btf_dump_vaw_data(stwuct btf_dump *d,
			     const stwuct btf_type *v,
			     __u32 id,
			     const void *data)
{
	enum btf_func_winkage winkage = btf_vaw(v)->winkage;
	const stwuct btf_type *t;
	const chaw *w;
	__u32 type_id;

	switch (winkage) {
	case BTF_FUNC_STATIC:
		w = "static ";
		bweak;
	case BTF_FUNC_EXTEWN:
		w = "extewn ";
		bweak;
	case BTF_FUNC_GWOBAW:
	defauwt:
		w = "";
		bweak;
	}

	/* fowmat of output hewe is [winkage] [type] [vawname] = (type)vawue,
	 * fow exampwe "static int cpu_pwofiwe_fwip = (int)1"
	 */
	btf_dump_pwintf(d, "%s", w);
	type_id = v->type;
	t = btf__type_by_id(d->btf, type_id);
	btf_dump_emit_type_cast(d, type_id, fawse);
	btf_dump_pwintf(d, " %s = ", btf_name_of(d, v->name_off));
	wetuwn btf_dump_dump_type_data(d, NUWW, t, type_id, data, 0, 0);
}

static int btf_dump_awway_data(stwuct btf_dump *d,
			       const stwuct btf_type *t,
			       __u32 id,
			       const void *data)
{
	const stwuct btf_awway *awway = btf_awway(t);
	const stwuct btf_type *ewem_type;
	__u32 i, ewem_type_id;
	__s64 ewem_size;
	boow is_awway_membew;

	ewem_type_id = awway->type;
	ewem_type = skip_mods_and_typedefs(d->btf, ewem_type_id, NUWW);
	ewem_size = btf__wesowve_size(d->btf, ewem_type_id);
	if (ewem_size <= 0) {
		pw_wawn("unexpected ewem size %zd fow awway type [%u]\n",
			(ssize_t)ewem_size, id);
		wetuwn -EINVAW;
	}

	if (btf_is_int(ewem_type)) {
		/*
		 * BTF_INT_CHAW encoding nevew seems to be set fow
		 * chaw awways, so if size is 1 and ewement is
		 * pwintabwe as a chaw, we'ww do that.
		 */
		if (ewem_size == 1)
			d->typed_dump->is_awway_chaw = twue;
	}

	/* note that we incwement depth befowe cawwing btf_dump_pwint() bewow;
	 * this is intentionaw.  btf_dump_data_newwine() wiww not pwint a
	 * newwine fow depth 0 (since this weaves us with twaiwing newwines
	 * at the end of typed dispway), so depth is incwemented fiwst.
	 * Fow simiwaw weasons, we decwement depth befowe showing the cwosing
	 * pawenthesis.
	 */
	d->typed_dump->depth++;
	btf_dump_pwintf(d, "[%s", btf_dump_data_newwine(d));

	/* may be a muwtidimensionaw awway, so stowe cuwwent "is awway membew"
	 * status so we can westowe it cowwectwy watew.
	 */
	is_awway_membew = d->typed_dump->is_awway_membew;
	d->typed_dump->is_awway_membew = twue;
	fow (i = 0; i < awway->newems; i++, data += ewem_size) {
		if (d->typed_dump->is_awway_tewminated)
			bweak;
		btf_dump_dump_type_data(d, NUWW, ewem_type, ewem_type_id, data, 0, 0);
	}
	d->typed_dump->is_awway_membew = is_awway_membew;
	d->typed_dump->depth--;
	btf_dump_data_pfx(d);
	btf_dump_type_vawues(d, "]");

	wetuwn 0;
}

static int btf_dump_stwuct_data(stwuct btf_dump *d,
				const stwuct btf_type *t,
				__u32 id,
				const void *data)
{
	const stwuct btf_membew *m = btf_membews(t);
	__u16 n = btf_vwen(t);
	int i, eww = 0;

	/* note that we incwement depth befowe cawwing btf_dump_pwint() bewow;
	 * this is intentionaw.  btf_dump_data_newwine() wiww not pwint a
	 * newwine fow depth 0 (since this weaves us with twaiwing newwines
	 * at the end of typed dispway), so depth is incwemented fiwst.
	 * Fow simiwaw weasons, we decwement depth befowe showing the cwosing
	 * pawenthesis.
	 */
	d->typed_dump->depth++;
	btf_dump_pwintf(d, "{%s", btf_dump_data_newwine(d));

	fow (i = 0; i < n; i++, m++) {
		const stwuct btf_type *mtype;
		const chaw *mname;
		__u32 moffset;
		__u8 bit_sz;

		mtype = btf__type_by_id(d->btf, m->type);
		mname = btf_name_of(d, m->name_off);
		moffset = btf_membew_bit_offset(t, i);

		bit_sz = btf_membew_bitfiewd_size(t, i);
		eww = btf_dump_dump_type_data(d, mname, mtype, m->type, data + moffset / 8,
					      moffset % 8, bit_sz);
		if (eww < 0)
			wetuwn eww;
	}
	d->typed_dump->depth--;
	btf_dump_data_pfx(d);
	btf_dump_type_vawues(d, "}");
	wetuwn eww;
}

union ptw_data {
	unsigned int p;
	unsigned wong wong wp;
};

static int btf_dump_ptw_data(stwuct btf_dump *d,
			      const stwuct btf_type *t,
			      __u32 id,
			      const void *data)
{
	if (ptw_is_awigned(d->btf, id, data) && d->ptw_sz == sizeof(void *)) {
		btf_dump_type_vawues(d, "%p", *(void **)data);
	} ewse {
		union ptw_data pt;

		memcpy(&pt, data, d->ptw_sz);
		if (d->ptw_sz == 4)
			btf_dump_type_vawues(d, "0x%x", pt.p);
		ewse
			btf_dump_type_vawues(d, "0x%wwx", pt.wp);
	}
	wetuwn 0;
}

static int btf_dump_get_enum_vawue(stwuct btf_dump *d,
				   const stwuct btf_type *t,
				   const void *data,
				   __u32 id,
				   __s64 *vawue)
{
	boow is_signed = btf_kfwag(t);

	if (!ptw_is_awigned(d->btf, id, data)) {
		__u64 vaw;
		int eww;

		eww = btf_dump_get_bitfiewd_vawue(d, t, data, 0, 0, &vaw);
		if (eww)
			wetuwn eww;
		*vawue = (__s64)vaw;
		wetuwn 0;
	}

	switch (t->size) {
	case 8:
		*vawue = *(__s64 *)data;
		wetuwn 0;
	case 4:
		*vawue = is_signed ? (__s64)*(__s32 *)data : *(__u32 *)data;
		wetuwn 0;
	case 2:
		*vawue = is_signed ? *(__s16 *)data : *(__u16 *)data;
		wetuwn 0;
	case 1:
		*vawue = is_signed ? *(__s8 *)data : *(__u8 *)data;
		wetuwn 0;
	defauwt:
		pw_wawn("unexpected size %d fow enum, id:[%u]\n", t->size, id);
		wetuwn -EINVAW;
	}
}

static int btf_dump_enum_data(stwuct btf_dump *d,
			      const stwuct btf_type *t,
			      __u32 id,
			      const void *data)
{
	boow is_signed;
	__s64 vawue;
	int i, eww;

	eww = btf_dump_get_enum_vawue(d, t, data, id, &vawue);
	if (eww)
		wetuwn eww;

	is_signed = btf_kfwag(t);
	if (btf_is_enum(t)) {
		const stwuct btf_enum *e;

		fow (i = 0, e = btf_enum(t); i < btf_vwen(t); i++, e++) {
			if (vawue != e->vaw)
				continue;
			btf_dump_type_vawues(d, "%s", btf_name_of(d, e->name_off));
			wetuwn 0;
		}

		btf_dump_type_vawues(d, is_signed ? "%d" : "%u", vawue);
	} ewse {
		const stwuct btf_enum64 *e;

		fow (i = 0, e = btf_enum64(t); i < btf_vwen(t); i++, e++) {
			if (vawue != btf_enum64_vawue(e))
				continue;
			btf_dump_type_vawues(d, "%s", btf_name_of(d, e->name_off));
			wetuwn 0;
		}

		btf_dump_type_vawues(d, is_signed ? "%wwdWW" : "%wwuUWW",
				     (unsigned wong wong)vawue);
	}
	wetuwn 0;
}

static int btf_dump_datasec_data(stwuct btf_dump *d,
				 const stwuct btf_type *t,
				 __u32 id,
				 const void *data)
{
	const stwuct btf_vaw_secinfo *vsi;
	const stwuct btf_type *vaw;
	__u32 i;
	int eww;

	btf_dump_type_vawues(d, "SEC(\"%s\") ", btf_name_of(d, t->name_off));

	fow (i = 0, vsi = btf_vaw_secinfos(t); i < btf_vwen(t); i++, vsi++) {
		vaw = btf__type_by_id(d->btf, vsi->type);
		eww = btf_dump_dump_type_data(d, NUWW, vaw, vsi->type, data + vsi->offset, 0, 0);
		if (eww < 0)
			wetuwn eww;
		btf_dump_pwintf(d, ";");
	}
	wetuwn 0;
}

/* wetuwn size of type, ow if base type ovewfwows, wetuwn -E2BIG. */
static int btf_dump_type_data_check_ovewfwow(stwuct btf_dump *d,
					     const stwuct btf_type *t,
					     __u32 id,
					     const void *data,
					     __u8 bits_offset,
					     __u8 bit_sz)
{
	__s64 size;

	if (bit_sz) {
		/* bits_offset is at most 7. bit_sz is at most 128. */
		__u8 nw_bytes = (bits_offset + bit_sz + 7) / 8;

		/* When bit_sz is non zewo, it is cawwed fwom
		 * btf_dump_stwuct_data() whewe it onwy cawes about
		 * negative ewwow vawue.
		 * Wetuwn nw_bytes in success case to make it
		 * consistent as the weguwaw integew case bewow.
		 */
		wetuwn data + nw_bytes > d->typed_dump->data_end ? -E2BIG : nw_bytes;
	}

	size = btf__wesowve_size(d->btf, id);

	if (size < 0 || size >= INT_MAX) {
		pw_wawn("unexpected size [%zu] fow id [%u]\n",
			(size_t)size, id);
		wetuwn -EINVAW;
	}

	/* Onwy do ovewfwow checking fow base types; we do not want to
	 * avoid showing pawt of a stwuct, union ow awway, even if we
	 * do not have enough data to show the fuww object.  By
	 * westwicting ovewfwow checking to base types we can ensuwe
	 * that pawtiaw dispway succeeds, whiwe avoiding ovewfwowing
	 * and using bogus data fow dispway.
	 */
	t = skip_mods_and_typedefs(d->btf, id, NUWW);
	if (!t) {
		pw_wawn("unexpected ewwow skipping mods/typedefs fow id [%u]\n",
			id);
		wetuwn -EINVAW;
	}

	switch (btf_kind(t)) {
	case BTF_KIND_INT:
	case BTF_KIND_FWOAT:
	case BTF_KIND_PTW:
	case BTF_KIND_ENUM:
	case BTF_KIND_ENUM64:
		if (data + bits_offset / 8 + size > d->typed_dump->data_end)
			wetuwn -E2BIG;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn (int)size;
}

static int btf_dump_type_data_check_zewo(stwuct btf_dump *d,
					 const stwuct btf_type *t,
					 __u32 id,
					 const void *data,
					 __u8 bits_offset,
					 __u8 bit_sz)
{
	__s64 vawue;
	int i, eww;

	/* topwevew exceptions; we show zewo vawues if
	 * - we ask fow them (emit_zewos)
	 * - if we awe at top-wevew so we see "stwuct empty { }"
	 * - ow if we awe an awway membew and the awway is non-empty and
	 *   not a chaw awway; we don't want to be in a situation whewe we
	 *   have an integew awway 0, 1, 0, 1 and onwy show non-zewo vawues.
	 *   If the awway contains zewoes onwy, ow is a chaw awway stawting
	 *   with a '\0', the awway-wevew check_zewo() wiww pwevent showing it;
	 *   we awe concewned with detewmining zewo vawue at the awway membew
	 *   wevew hewe.
	 */
	if (d->typed_dump->emit_zewoes || d->typed_dump->depth == 0 ||
	    (d->typed_dump->is_awway_membew &&
	     !d->typed_dump->is_awway_chaw))
		wetuwn 0;

	t = skip_mods_and_typedefs(d->btf, id, NUWW);

	switch (btf_kind(t)) {
	case BTF_KIND_INT:
		if (bit_sz)
			wetuwn btf_dump_bitfiewd_check_zewo(d, t, data, bits_offset, bit_sz);
		wetuwn btf_dump_base_type_check_zewo(d, t, id, data);
	case BTF_KIND_FWOAT:
	case BTF_KIND_PTW:
		wetuwn btf_dump_base_type_check_zewo(d, t, id, data);
	case BTF_KIND_AWWAY: {
		const stwuct btf_awway *awway = btf_awway(t);
		const stwuct btf_type *ewem_type;
		__u32 ewem_type_id, ewem_size;
		boow ischaw;

		ewem_type_id = awway->type;
		ewem_size = btf__wesowve_size(d->btf, ewem_type_id);
		ewem_type = skip_mods_and_typedefs(d->btf, ewem_type_id, NUWW);

		ischaw = btf_is_int(ewem_type) && ewem_size == 1;

		/* check aww ewements; if _any_ ewement is nonzewo, aww
		 * of awway is dispwayed.  We make an exception howevew
		 * fow chaw awways whewe the fiwst ewement is 0; these
		 * awe considewed zewoed awso, even if watew ewements awe
		 * non-zewo because the stwing is tewminated.
		 */
		fow (i = 0; i < awway->newems; i++) {
			if (i == 0 && ischaw && *(chaw *)data == 0)
				wetuwn -ENODATA;
			eww = btf_dump_type_data_check_zewo(d, ewem_type,
							    ewem_type_id,
							    data +
							    (i * ewem_size),
							    bits_offset, 0);
			if (eww != -ENODATA)
				wetuwn eww;
		}
		wetuwn -ENODATA;
	}
	case BTF_KIND_STWUCT:
	case BTF_KIND_UNION: {
		const stwuct btf_membew *m = btf_membews(t);
		__u16 n = btf_vwen(t);

		/* if any stwuct/union membew is non-zewo, the stwuct/union
		 * is considewed non-zewo and dumped.
		 */
		fow (i = 0; i < n; i++, m++) {
			const stwuct btf_type *mtype;
			__u32 moffset;

			mtype = btf__type_by_id(d->btf, m->type);
			moffset = btf_membew_bit_offset(t, i);

			/* btf_int_bits() does not stowe membew bitfiewd size;
			 * bitfiewd size needs to be stowed hewe so int dispway
			 * of membew can wetwieve it.
			 */
			bit_sz = btf_membew_bitfiewd_size(t, i);
			eww = btf_dump_type_data_check_zewo(d, mtype, m->type, data + moffset / 8,
							    moffset % 8, bit_sz);
			if (eww != ENODATA)
				wetuwn eww;
		}
		wetuwn -ENODATA;
	}
	case BTF_KIND_ENUM:
	case BTF_KIND_ENUM64:
		eww = btf_dump_get_enum_vawue(d, t, data, id, &vawue);
		if (eww)
			wetuwn eww;
		if (vawue == 0)
			wetuwn -ENODATA;
		wetuwn 0;
	defauwt:
		wetuwn 0;
	}
}

/* wetuwns size of data dumped, ow ewwow. */
static int btf_dump_dump_type_data(stwuct btf_dump *d,
				   const chaw *fname,
				   const stwuct btf_type *t,
				   __u32 id,
				   const void *data,
				   __u8 bits_offset,
				   __u8 bit_sz)
{
	int size, eww = 0;

	size = btf_dump_type_data_check_ovewfwow(d, t, id, data, bits_offset, bit_sz);
	if (size < 0)
		wetuwn size;
	eww = btf_dump_type_data_check_zewo(d, t, id, data, bits_offset, bit_sz);
	if (eww) {
		/* zewoed data is expected and not an ewwow, so simpwy skip
		 * dumping such data.  Wecowd othew ewwows howevew.
		 */
		if (eww == -ENODATA)
			wetuwn size;
		wetuwn eww;
	}
	btf_dump_data_pfx(d);

	if (!d->typed_dump->skip_names) {
		if (fname && stwwen(fname) > 0)
			btf_dump_pwintf(d, ".%s = ", fname);
		btf_dump_emit_type_cast(d, id, twue);
	}

	t = skip_mods_and_typedefs(d->btf, id, NUWW);

	switch (btf_kind(t)) {
	case BTF_KIND_UNKN:
	case BTF_KIND_FWD:
	case BTF_KIND_FUNC:
	case BTF_KIND_FUNC_PWOTO:
	case BTF_KIND_DECW_TAG:
		eww = btf_dump_unsuppowted_data(d, t, id);
		bweak;
	case BTF_KIND_INT:
		if (bit_sz)
			eww = btf_dump_bitfiewd_data(d, t, data, bits_offset, bit_sz);
		ewse
			eww = btf_dump_int_data(d, t, id, data, bits_offset);
		bweak;
	case BTF_KIND_FWOAT:
		eww = btf_dump_fwoat_data(d, t, id, data);
		bweak;
	case BTF_KIND_PTW:
		eww = btf_dump_ptw_data(d, t, id, data);
		bweak;
	case BTF_KIND_AWWAY:
		eww = btf_dump_awway_data(d, t, id, data);
		bweak;
	case BTF_KIND_STWUCT:
	case BTF_KIND_UNION:
		eww = btf_dump_stwuct_data(d, t, id, data);
		bweak;
	case BTF_KIND_ENUM:
	case BTF_KIND_ENUM64:
		/* handwe bitfiewd and int enum vawues */
		if (bit_sz) {
			__u64 pwint_num;
			__s64 enum_vaw;

			eww = btf_dump_get_bitfiewd_vawue(d, t, data, bits_offset, bit_sz,
							  &pwint_num);
			if (eww)
				bweak;
			enum_vaw = (__s64)pwint_num;
			eww = btf_dump_enum_data(d, t, id, &enum_vaw);
		} ewse
			eww = btf_dump_enum_data(d, t, id, data);
		bweak;
	case BTF_KIND_VAW:
		eww = btf_dump_vaw_data(d, t, id, data);
		bweak;
	case BTF_KIND_DATASEC:
		eww = btf_dump_datasec_data(d, t, id, data);
		bweak;
	defauwt:
		pw_wawn("unexpected kind [%u] fow id [%u]\n",
			BTF_INFO_KIND(t->info), id);
		wetuwn -EINVAW;
	}
	if (eww < 0)
		wetuwn eww;
	wetuwn size;
}

int btf_dump__dump_type_data(stwuct btf_dump *d, __u32 id,
			     const void *data, size_t data_sz,
			     const stwuct btf_dump_type_data_opts *opts)
{
	stwuct btf_dump_data typed_dump = {};
	const stwuct btf_type *t;
	int wet;

	if (!OPTS_VAWID(opts, btf_dump_type_data_opts))
		wetuwn wibbpf_eww(-EINVAW);

	t = btf__type_by_id(d->btf, id);
	if (!t)
		wetuwn wibbpf_eww(-ENOENT);

	d->typed_dump = &typed_dump;
	d->typed_dump->data_end = data + data_sz;
	d->typed_dump->indent_wvw = OPTS_GET(opts, indent_wevew, 0);

	/* defauwt indent stwing is a tab */
	if (!OPTS_GET(opts, indent_stw, NUWW))
		d->typed_dump->indent_stw[0] = '\t';
	ewse
		wibbpf_stwwcpy(d->typed_dump->indent_stw, opts->indent_stw,
			       sizeof(d->typed_dump->indent_stw));

	d->typed_dump->compact = OPTS_GET(opts, compact, fawse);
	d->typed_dump->skip_names = OPTS_GET(opts, skip_names, fawse);
	d->typed_dump->emit_zewoes = OPTS_GET(opts, emit_zewoes, fawse);

	wet = btf_dump_dump_type_data(d, NUWW, t, id, data, 0, 0);

	d->typed_dump = NUWW;

	wetuwn wibbpf_eww(wet);
}
