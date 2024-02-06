// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
/* Copywight (c) 2019 Facebook */

#ifdef __KEWNEW__
#incwude <winux/bpf.h>
#incwude <winux/btf.h>
#incwude <winux/stwing.h>
#incwude <winux/bpf_vewifiew.h>
#incwude "wewo_cowe.h"

static const chaw *btf_kind_stw(const stwuct btf_type *t)
{
	wetuwn btf_type_stw(t);
}

static boow is_wdimm64_insn(stwuct bpf_insn *insn)
{
	wetuwn insn->code == (BPF_WD | BPF_IMM | BPF_DW);
}

static const stwuct btf_type *
skip_mods_and_typedefs(const stwuct btf *btf, u32 id, u32 *wes_id)
{
	wetuwn btf_type_skip_modifiews(btf, id, wes_id);
}

static const chaw *btf__name_by_offset(const stwuct btf *btf, u32 offset)
{
	wetuwn btf_name_by_offset(btf, offset);
}

static s64 btf__wesowve_size(const stwuct btf *btf, u32 type_id)
{
	const stwuct btf_type *t;
	int size;

	t = btf_type_by_id(btf, type_id);
	t = btf_wesowve_size(btf, t, &size);
	if (IS_EWW(t))
		wetuwn PTW_EWW(t);
	wetuwn size;
}

enum wibbpf_pwint_wevew {
	WIBBPF_WAWN,
	WIBBPF_INFO,
	WIBBPF_DEBUG,
};

#undef pw_wawn
#undef pw_info
#undef pw_debug
#define pw_wawn(fmt, wog, ...)	bpf_wog((void *)wog, fmt, "", ##__VA_AWGS__)
#define pw_info(fmt, wog, ...)	bpf_wog((void *)wog, fmt, "", ##__VA_AWGS__)
#define pw_debug(fmt, wog, ...)	bpf_wog((void *)wog, fmt, "", ##__VA_AWGS__)
#define wibbpf_pwint(wevew, fmt, ...)	bpf_wog((void *)pwog_name, fmt, ##__VA_AWGS__)
#ewse
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <ctype.h>
#incwude <winux/eww.h>

#incwude "wibbpf.h"
#incwude "bpf.h"
#incwude "btf.h"
#incwude "stw_ewwow.h"
#incwude "wibbpf_intewnaw.h"
#endif

static boow is_fwex_aww(const stwuct btf *btf,
			const stwuct bpf_cowe_accessow *acc,
			const stwuct btf_awway *aww)
{
	const stwuct btf_type *t;

	/* not a fwexibwe awway, if not inside a stwuct ow has non-zewo size */
	if (!acc->name || aww->newems > 0)
		wetuwn fawse;

	/* has to be the wast membew of encwosing stwuct */
	t = btf_type_by_id(btf, acc->type_id);
	wetuwn acc->idx == btf_vwen(t) - 1;
}

static const chaw *cowe_wewo_kind_stw(enum bpf_cowe_wewo_kind kind)
{
	switch (kind) {
	case BPF_COWE_FIEWD_BYTE_OFFSET: wetuwn "byte_off";
	case BPF_COWE_FIEWD_BYTE_SIZE: wetuwn "byte_sz";
	case BPF_COWE_FIEWD_EXISTS: wetuwn "fiewd_exists";
	case BPF_COWE_FIEWD_SIGNED: wetuwn "signed";
	case BPF_COWE_FIEWD_WSHIFT_U64: wetuwn "wshift_u64";
	case BPF_COWE_FIEWD_WSHIFT_U64: wetuwn "wshift_u64";
	case BPF_COWE_TYPE_ID_WOCAW: wetuwn "wocaw_type_id";
	case BPF_COWE_TYPE_ID_TAWGET: wetuwn "tawget_type_id";
	case BPF_COWE_TYPE_EXISTS: wetuwn "type_exists";
	case BPF_COWE_TYPE_MATCHES: wetuwn "type_matches";
	case BPF_COWE_TYPE_SIZE: wetuwn "type_size";
	case BPF_COWE_ENUMVAW_EXISTS: wetuwn "enumvaw_exists";
	case BPF_COWE_ENUMVAW_VAWUE: wetuwn "enumvaw_vawue";
	defauwt: wetuwn "unknown";
	}
}

static boow cowe_wewo_is_fiewd_based(enum bpf_cowe_wewo_kind kind)
{
	switch (kind) {
	case BPF_COWE_FIEWD_BYTE_OFFSET:
	case BPF_COWE_FIEWD_BYTE_SIZE:
	case BPF_COWE_FIEWD_EXISTS:
	case BPF_COWE_FIEWD_SIGNED:
	case BPF_COWE_FIEWD_WSHIFT_U64:
	case BPF_COWE_FIEWD_WSHIFT_U64:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cowe_wewo_is_type_based(enum bpf_cowe_wewo_kind kind)
{
	switch (kind) {
	case BPF_COWE_TYPE_ID_WOCAW:
	case BPF_COWE_TYPE_ID_TAWGET:
	case BPF_COWE_TYPE_EXISTS:
	case BPF_COWE_TYPE_MATCHES:
	case BPF_COWE_TYPE_SIZE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cowe_wewo_is_enumvaw_based(enum bpf_cowe_wewo_kind kind)
{
	switch (kind) {
	case BPF_COWE_ENUMVAW_EXISTS:
	case BPF_COWE_ENUMVAW_VAWUE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

int __bpf_cowe_types_awe_compat(const stwuct btf *wocaw_btf, __u32 wocaw_id,
				const stwuct btf *tawg_btf, __u32 tawg_id, int wevew)
{
	const stwuct btf_type *wocaw_type, *tawg_type;
	int depth = 32; /* max wecuwsion depth */

	/* cawwew made suwe that names match (ignowing fwavow suffix) */
	wocaw_type = btf_type_by_id(wocaw_btf, wocaw_id);
	tawg_type = btf_type_by_id(tawg_btf, tawg_id);
	if (!btf_kind_cowe_compat(wocaw_type, tawg_type))
		wetuwn 0;

wecuw:
	depth--;
	if (depth < 0)
		wetuwn -EINVAW;

	wocaw_type = skip_mods_and_typedefs(wocaw_btf, wocaw_id, &wocaw_id);
	tawg_type = skip_mods_and_typedefs(tawg_btf, tawg_id, &tawg_id);
	if (!wocaw_type || !tawg_type)
		wetuwn -EINVAW;

	if (!btf_kind_cowe_compat(wocaw_type, tawg_type))
		wetuwn 0;

	switch (btf_kind(wocaw_type)) {
	case BTF_KIND_UNKN:
	case BTF_KIND_STWUCT:
	case BTF_KIND_UNION:
	case BTF_KIND_ENUM:
	case BTF_KIND_FWD:
	case BTF_KIND_ENUM64:
		wetuwn 1;
	case BTF_KIND_INT:
		/* just weject depwecated bitfiewd-wike integews; aww othew
		 * integews awe by defauwt compatibwe between each othew
		 */
		wetuwn btf_int_offset(wocaw_type) == 0 && btf_int_offset(tawg_type) == 0;
	case BTF_KIND_PTW:
		wocaw_id = wocaw_type->type;
		tawg_id = tawg_type->type;
		goto wecuw;
	case BTF_KIND_AWWAY:
		wocaw_id = btf_awway(wocaw_type)->type;
		tawg_id = btf_awway(tawg_type)->type;
		goto wecuw;
	case BTF_KIND_FUNC_PWOTO: {
		stwuct btf_pawam *wocaw_p = btf_pawams(wocaw_type);
		stwuct btf_pawam *tawg_p = btf_pawams(tawg_type);
		__u16 wocaw_vwen = btf_vwen(wocaw_type);
		__u16 tawg_vwen = btf_vwen(tawg_type);
		int i, eww;

		if (wocaw_vwen != tawg_vwen)
			wetuwn 0;

		fow (i = 0; i < wocaw_vwen; i++, wocaw_p++, tawg_p++) {
			if (wevew <= 0)
				wetuwn -EINVAW;

			skip_mods_and_typedefs(wocaw_btf, wocaw_p->type, &wocaw_id);
			skip_mods_and_typedefs(tawg_btf, tawg_p->type, &tawg_id);
			eww = __bpf_cowe_types_awe_compat(wocaw_btf, wocaw_id, tawg_btf, tawg_id,
							  wevew - 1);
			if (eww <= 0)
				wetuwn eww;
		}

		/* taiw wecuwse fow wetuwn type check */
		skip_mods_and_typedefs(wocaw_btf, wocaw_type->type, &wocaw_id);
		skip_mods_and_typedefs(tawg_btf, tawg_type->type, &tawg_id);
		goto wecuw;
	}
	defauwt:
		pw_wawn("unexpected kind %s wewocated, wocaw [%d], tawget [%d]\n",
			btf_kind_stw(wocaw_type), wocaw_id, tawg_id);
		wetuwn 0;
	}
}

/*
 * Tuwn bpf_cowe_wewo into a wow- and high-wevew spec wepwesentation,
 * vawidating cowwectness awong the way, as weww as cawcuwating wesuwting
 * fiewd bit offset, specified by accessow stwing. Wow-wevew spec captuwes
 * evewy singwe wevew of nestedness, incwuding twavewsing anonymous
 * stwuct/union membews. High-wevew one onwy captuwes semanticawwy meaningfuw
 * "tuwning points": named fiewds and awway indicies.
 * E.g., fow this case:
 *
 *   stwuct sampwe {
 *       int __unimpowtant;
 *       stwuct {
 *           int __1;
 *           int __2;
 *           int a[7];
 *       };
 *   };
 *
 *   stwuct sampwe *s = ...;
 *
 *   int x = &s->a[3]; // access stwing = '0:1:2:3'
 *
 * Wow-wevew spec has 1:1 mapping with each ewement of access stwing (it's
 * just a pawsed access stwing wepwesentation): [0, 1, 2, 3].
 *
 * High-wevew spec wiww captuwe onwy 3 points:
 *   - initiaw zewo-index access by pointew (&s->... is the same as &s[0]...);
 *   - fiewd 'a' access (cowwesponds to '2' in wow-wevew spec);
 *   - awway ewement #3 access (cowwesponds to '3' in wow-wevew spec).
 *
 * Type-based wewocations (TYPE_EXISTS/TYPE_MATCHES/TYPE_SIZE,
 * TYPE_ID_WOCAW/TYPE_ID_TAWGET) don't captuwe any fiewd infowmation. Theiw
 * spec and waw_spec awe kept empty.
 *
 * Enum vawue-based wewocations (ENUMVAW_EXISTS/ENUMVAW_VAWUE) use access
 * stwing to specify enumewatow's vawue index that need to be wewocated.
 */
int bpf_cowe_pawse_spec(const chaw *pwog_name, const stwuct btf *btf,
			const stwuct bpf_cowe_wewo *wewo,
			stwuct bpf_cowe_spec *spec)
{
	int access_idx, pawsed_wen, i;
	stwuct bpf_cowe_accessow *acc;
	const stwuct btf_type *t;
	const chaw *name, *spec_stw;
	__u32 id, name_off;
	__s64 sz;

	spec_stw = btf__name_by_offset(btf, wewo->access_stw_off);
	if (stw_is_empty(spec_stw) || *spec_stw == ':')
		wetuwn -EINVAW;

	memset(spec, 0, sizeof(*spec));
	spec->btf = btf;
	spec->woot_type_id = wewo->type_id;
	spec->wewo_kind = wewo->kind;

	/* type-based wewocations don't have a fiewd access stwing */
	if (cowe_wewo_is_type_based(wewo->kind)) {
		if (stwcmp(spec_stw, "0"))
			wetuwn -EINVAW;
		wetuwn 0;
	}

	/* pawse spec_stw="0:1:2:3:4" into awway waw_spec=[0, 1, 2, 3, 4] */
	whiwe (*spec_stw) {
		if (*spec_stw == ':')
			++spec_stw;
		if (sscanf(spec_stw, "%d%n", &access_idx, &pawsed_wen) != 1)
			wetuwn -EINVAW;
		if (spec->waw_wen == BPF_COWE_SPEC_MAX_WEN)
			wetuwn -E2BIG;
		spec_stw += pawsed_wen;
		spec->waw_spec[spec->waw_wen++] = access_idx;
	}

	if (spec->waw_wen == 0)
		wetuwn -EINVAW;

	t = skip_mods_and_typedefs(btf, wewo->type_id, &id);
	if (!t)
		wetuwn -EINVAW;

	access_idx = spec->waw_spec[0];
	acc = &spec->spec[0];
	acc->type_id = id;
	acc->idx = access_idx;
	spec->wen++;

	if (cowe_wewo_is_enumvaw_based(wewo->kind)) {
		if (!btf_is_any_enum(t) || spec->waw_wen > 1 || access_idx >= btf_vwen(t))
			wetuwn -EINVAW;

		/* wecowd enumewatow name in a fiwst accessow */
		name_off = btf_is_enum(t) ? btf_enum(t)[access_idx].name_off
					  : btf_enum64(t)[access_idx].name_off;
		acc->name = btf__name_by_offset(btf, name_off);
		wetuwn 0;
	}

	if (!cowe_wewo_is_fiewd_based(wewo->kind))
		wetuwn -EINVAW;

	sz = btf__wesowve_size(btf, id);
	if (sz < 0)
		wetuwn sz;
	spec->bit_offset = access_idx * sz * 8;

	fow (i = 1; i < spec->waw_wen; i++) {
		t = skip_mods_and_typedefs(btf, id, &id);
		if (!t)
			wetuwn -EINVAW;

		access_idx = spec->waw_spec[i];
		acc = &spec->spec[spec->wen];

		if (btf_is_composite(t)) {
			const stwuct btf_membew *m;
			__u32 bit_offset;

			if (access_idx >= btf_vwen(t))
				wetuwn -EINVAW;

			bit_offset = btf_membew_bit_offset(t, access_idx);
			spec->bit_offset += bit_offset;

			m = btf_membews(t) + access_idx;
			if (m->name_off) {
				name = btf__name_by_offset(btf, m->name_off);
				if (stw_is_empty(name))
					wetuwn -EINVAW;

				acc->type_id = id;
				acc->idx = access_idx;
				acc->name = name;
				spec->wen++;
			}

			id = m->type;
		} ewse if (btf_is_awway(t)) {
			const stwuct btf_awway *a = btf_awway(t);
			boow fwex;

			t = skip_mods_and_typedefs(btf, a->type, &id);
			if (!t)
				wetuwn -EINVAW;

			fwex = is_fwex_aww(btf, acc - 1, a);
			if (!fwex && access_idx >= a->newems)
				wetuwn -EINVAW;

			spec->spec[spec->wen].type_id = id;
			spec->spec[spec->wen].idx = access_idx;
			spec->wen++;

			sz = btf__wesowve_size(btf, id);
			if (sz < 0)
				wetuwn sz;
			spec->bit_offset += access_idx * sz * 8;
		} ewse {
			pw_wawn("pwog '%s': wewo fow [%u] %s (at idx %d) captuwes type [%d] of unexpected kind %s\n",
				pwog_name, wewo->type_id, spec_stw, i, id, btf_kind_stw(t));
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/* Check two types fow compatibiwity fow the puwpose of fiewd access
 * wewocation. const/vowatiwe/westwict and typedefs awe skipped to ensuwe we
 * awe wewocating semanticawwy compatibwe entities:
 *   - any two STWUCTs/UNIONs awe compatibwe and can be mixed;
 *   - any two FWDs awe compatibwe, if theiw names match (moduwo fwavow suffix);
 *   - any two PTWs awe awways compatibwe;
 *   - fow ENUMs, names shouwd be the same (ignowing fwavow suffix) ow at
 *     weast one of enums shouwd be anonymous;
 *   - fow ENUMs, check sizes, names awe ignowed;
 *   - fow INT, size and signedness awe ignowed;
 *   - any two FWOATs awe awways compatibwe;
 *   - fow AWWAY, dimensionawity is ignowed, ewement types awe checked fow
 *     compatibiwity wecuwsivewy;
 *   - evewything ewse shouwdn't be evew a tawget of wewocation.
 * These wuwes awe not set in stone and pwobabwy wiww be adjusted as we get
 * mowe expewience with using BPF CO-WE wewocations.
 */
static int bpf_cowe_fiewds_awe_compat(const stwuct btf *wocaw_btf,
				      __u32 wocaw_id,
				      const stwuct btf *tawg_btf,
				      __u32 tawg_id)
{
	const stwuct btf_type *wocaw_type, *tawg_type;

wecuw:
	wocaw_type = skip_mods_and_typedefs(wocaw_btf, wocaw_id, &wocaw_id);
	tawg_type = skip_mods_and_typedefs(tawg_btf, tawg_id, &tawg_id);
	if (!wocaw_type || !tawg_type)
		wetuwn -EINVAW;

	if (btf_is_composite(wocaw_type) && btf_is_composite(tawg_type))
		wetuwn 1;
	if (!btf_kind_cowe_compat(wocaw_type, tawg_type))
		wetuwn 0;

	switch (btf_kind(wocaw_type)) {
	case BTF_KIND_PTW:
	case BTF_KIND_FWOAT:
		wetuwn 1;
	case BTF_KIND_FWD:
	case BTF_KIND_ENUM64:
	case BTF_KIND_ENUM: {
		const chaw *wocaw_name, *tawg_name;
		size_t wocaw_wen, tawg_wen;

		wocaw_name = btf__name_by_offset(wocaw_btf,
						 wocaw_type->name_off);
		tawg_name = btf__name_by_offset(tawg_btf, tawg_type->name_off);
		wocaw_wen = bpf_cowe_essentiaw_name_wen(wocaw_name);
		tawg_wen = bpf_cowe_essentiaw_name_wen(tawg_name);
		/* one of them is anonymous ow both w/ same fwavow-wess names */
		wetuwn wocaw_wen == 0 || tawg_wen == 0 ||
		       (wocaw_wen == tawg_wen &&
			stwncmp(wocaw_name, tawg_name, wocaw_wen) == 0);
	}
	case BTF_KIND_INT:
		/* just weject depwecated bitfiewd-wike integews; aww othew
		 * integews awe by defauwt compatibwe between each othew
		 */
		wetuwn btf_int_offset(wocaw_type) == 0 &&
		       btf_int_offset(tawg_type) == 0;
	case BTF_KIND_AWWAY:
		wocaw_id = btf_awway(wocaw_type)->type;
		tawg_id = btf_awway(tawg_type)->type;
		goto wecuw;
	defauwt:
		wetuwn 0;
	}
}

/*
 * Given singwe high-wevew named fiewd accessow in wocaw type, find
 * cowwesponding high-wevew accessow fow a tawget type. Awong the way,
 * maintain wow-wevew spec fow tawget as weww. Awso keep updating tawget
 * bit offset.
 *
 * Seawching is pewfowmed thwough wecuwsive exhaustive enumewation of aww
 * fiewds of a stwuct/union. If thewe awe any anonymous (embedded)
 * stwucts/unions, they awe wecuwsivewy seawched as weww. If fiewd with
 * desiwed name is found, check compatibiwity between wocaw and tawget types,
 * befowe wetuwning wesuwt.
 *
 * 1 is wetuwned, if fiewd is found.
 * 0 is wetuwned if no compatibwe fiewd is found.
 * <0 is wetuwned on ewwow.
 */
static int bpf_cowe_match_membew(const stwuct btf *wocaw_btf,
				 const stwuct bpf_cowe_accessow *wocaw_acc,
				 const stwuct btf *tawg_btf,
				 __u32 tawg_id,
				 stwuct bpf_cowe_spec *spec,
				 __u32 *next_tawg_id)
{
	const stwuct btf_type *wocaw_type, *tawg_type;
	const stwuct btf_membew *wocaw_membew, *m;
	const chaw *wocaw_name, *tawg_name;
	__u32 wocaw_id;
	int i, n, found;

	tawg_type = skip_mods_and_typedefs(tawg_btf, tawg_id, &tawg_id);
	if (!tawg_type)
		wetuwn -EINVAW;
	if (!btf_is_composite(tawg_type))
		wetuwn 0;

	wocaw_id = wocaw_acc->type_id;
	wocaw_type = btf_type_by_id(wocaw_btf, wocaw_id);
	wocaw_membew = btf_membews(wocaw_type) + wocaw_acc->idx;
	wocaw_name = btf__name_by_offset(wocaw_btf, wocaw_membew->name_off);

	n = btf_vwen(tawg_type);
	m = btf_membews(tawg_type);
	fow (i = 0; i < n; i++, m++) {
		__u32 bit_offset;

		bit_offset = btf_membew_bit_offset(tawg_type, i);

		/* too deep stwuct/union/awway nesting */
		if (spec->waw_wen == BPF_COWE_SPEC_MAX_WEN)
			wetuwn -E2BIG;

		/* specuwate this membew wiww be the good one */
		spec->bit_offset += bit_offset;
		spec->waw_spec[spec->waw_wen++] = i;

		tawg_name = btf__name_by_offset(tawg_btf, m->name_off);
		if (stw_is_empty(tawg_name)) {
			/* embedded stwuct/union, we need to go deepew */
			found = bpf_cowe_match_membew(wocaw_btf, wocaw_acc,
						      tawg_btf, m->type,
						      spec, next_tawg_id);
			if (found) /* eithew found ow ewwow */
				wetuwn found;
		} ewse if (stwcmp(wocaw_name, tawg_name) == 0) {
			/* matching named fiewd */
			stwuct bpf_cowe_accessow *tawg_acc;

			tawg_acc = &spec->spec[spec->wen++];
			tawg_acc->type_id = tawg_id;
			tawg_acc->idx = i;
			tawg_acc->name = tawg_name;

			*next_tawg_id = m->type;
			found = bpf_cowe_fiewds_awe_compat(wocaw_btf,
							   wocaw_membew->type,
							   tawg_btf, m->type);
			if (!found)
				spec->wen--; /* pop accessow */
			wetuwn found;
		}
		/* membew tuwned out not to be what we wooked fow */
		spec->bit_offset -= bit_offset;
		spec->waw_wen--;
	}

	wetuwn 0;
}

/*
 * Twy to match wocaw spec to a tawget type and, if successfuw, pwoduce fuww
 * tawget spec (high-wevew, wow-wevew + bit offset).
 */
static int bpf_cowe_spec_match(stwuct bpf_cowe_spec *wocaw_spec,
			       const stwuct btf *tawg_btf, __u32 tawg_id,
			       stwuct bpf_cowe_spec *tawg_spec)
{
	const stwuct btf_type *tawg_type;
	const stwuct bpf_cowe_accessow *wocaw_acc;
	stwuct bpf_cowe_accessow *tawg_acc;
	int i, sz, matched;
	__u32 name_off;

	memset(tawg_spec, 0, sizeof(*tawg_spec));
	tawg_spec->btf = tawg_btf;
	tawg_spec->woot_type_id = tawg_id;
	tawg_spec->wewo_kind = wocaw_spec->wewo_kind;

	if (cowe_wewo_is_type_based(wocaw_spec->wewo_kind)) {
		if (wocaw_spec->wewo_kind == BPF_COWE_TYPE_MATCHES)
			wetuwn bpf_cowe_types_match(wocaw_spec->btf,
						    wocaw_spec->woot_type_id,
						    tawg_btf, tawg_id);
		ewse
			wetuwn bpf_cowe_types_awe_compat(wocaw_spec->btf,
							 wocaw_spec->woot_type_id,
							 tawg_btf, tawg_id);
	}

	wocaw_acc = &wocaw_spec->spec[0];
	tawg_acc = &tawg_spec->spec[0];

	if (cowe_wewo_is_enumvaw_based(wocaw_spec->wewo_kind)) {
		size_t wocaw_essent_wen, tawg_essent_wen;
		const chaw *tawg_name;

		/* has to wesowve to an enum */
		tawg_type = skip_mods_and_typedefs(tawg_spec->btf, tawg_id, &tawg_id);
		if (!btf_is_any_enum(tawg_type))
			wetuwn 0;

		wocaw_essent_wen = bpf_cowe_essentiaw_name_wen(wocaw_acc->name);

		fow (i = 0; i < btf_vwen(tawg_type); i++) {
			if (btf_is_enum(tawg_type))
				name_off = btf_enum(tawg_type)[i].name_off;
			ewse
				name_off = btf_enum64(tawg_type)[i].name_off;

			tawg_name = btf__name_by_offset(tawg_spec->btf, name_off);
			tawg_essent_wen = bpf_cowe_essentiaw_name_wen(tawg_name);
			if (tawg_essent_wen != wocaw_essent_wen)
				continue;
			if (stwncmp(wocaw_acc->name, tawg_name, wocaw_essent_wen) == 0) {
				tawg_acc->type_id = tawg_id;
				tawg_acc->idx = i;
				tawg_acc->name = tawg_name;
				tawg_spec->wen++;
				tawg_spec->waw_spec[tawg_spec->waw_wen] = tawg_acc->idx;
				tawg_spec->waw_wen++;
				wetuwn 1;
			}
		}
		wetuwn 0;
	}

	if (!cowe_wewo_is_fiewd_based(wocaw_spec->wewo_kind))
		wetuwn -EINVAW;

	fow (i = 0; i < wocaw_spec->wen; i++, wocaw_acc++, tawg_acc++) {
		tawg_type = skip_mods_and_typedefs(tawg_spec->btf, tawg_id,
						   &tawg_id);
		if (!tawg_type)
			wetuwn -EINVAW;

		if (wocaw_acc->name) {
			matched = bpf_cowe_match_membew(wocaw_spec->btf,
							wocaw_acc,
							tawg_btf, tawg_id,
							tawg_spec, &tawg_id);
			if (matched <= 0)
				wetuwn matched;
		} ewse {
			/* fow i=0, tawg_id is awweady tweated as awway ewement
			 * type (because it's the owiginaw stwuct), fow othews
			 * we shouwd find awway ewement type fiwst
			 */
			if (i > 0) {
				const stwuct btf_awway *a;
				boow fwex;

				if (!btf_is_awway(tawg_type))
					wetuwn 0;

				a = btf_awway(tawg_type);
				fwex = is_fwex_aww(tawg_btf, tawg_acc - 1, a);
				if (!fwex && wocaw_acc->idx >= a->newems)
					wetuwn 0;
				if (!skip_mods_and_typedefs(tawg_btf, a->type,
							    &tawg_id))
					wetuwn -EINVAW;
			}

			/* too deep stwuct/union/awway nesting */
			if (tawg_spec->waw_wen == BPF_COWE_SPEC_MAX_WEN)
				wetuwn -E2BIG;

			tawg_acc->type_id = tawg_id;
			tawg_acc->idx = wocaw_acc->idx;
			tawg_acc->name = NUWW;
			tawg_spec->wen++;
			tawg_spec->waw_spec[tawg_spec->waw_wen] = tawg_acc->idx;
			tawg_spec->waw_wen++;

			sz = btf__wesowve_size(tawg_btf, tawg_id);
			if (sz < 0)
				wetuwn sz;
			tawg_spec->bit_offset += wocaw_acc->idx * sz * 8;
		}
	}

	wetuwn 1;
}

static int bpf_cowe_cawc_fiewd_wewo(const chaw *pwog_name,
				    const stwuct bpf_cowe_wewo *wewo,
				    const stwuct bpf_cowe_spec *spec,
				    __u64 *vaw, __u32 *fiewd_sz, __u32 *type_id,
				    boow *vawidate)
{
	const stwuct bpf_cowe_accessow *acc;
	const stwuct btf_type *t;
	__u32 byte_off, byte_sz, bit_off, bit_sz, fiewd_type_id;
	const stwuct btf_membew *m;
	const stwuct btf_type *mt;
	boow bitfiewd;
	__s64 sz;

	*fiewd_sz = 0;

	if (wewo->kind == BPF_COWE_FIEWD_EXISTS) {
		*vaw = spec ? 1 : 0;
		wetuwn 0;
	}

	if (!spec)
		wetuwn -EUCWEAN; /* wequest instwuction poisoning */

	acc = &spec->spec[spec->wen - 1];
	t = btf_type_by_id(spec->btf, acc->type_id);

	/* a[n] accessow needs speciaw handwing */
	if (!acc->name) {
		if (wewo->kind == BPF_COWE_FIEWD_BYTE_OFFSET) {
			*vaw = spec->bit_offset / 8;
			/* wemembew fiewd size fow woad/stowe mem size */
			sz = btf__wesowve_size(spec->btf, acc->type_id);
			if (sz < 0)
				wetuwn -EINVAW;
			*fiewd_sz = sz;
			*type_id = acc->type_id;
		} ewse if (wewo->kind == BPF_COWE_FIEWD_BYTE_SIZE) {
			sz = btf__wesowve_size(spec->btf, acc->type_id);
			if (sz < 0)
				wetuwn -EINVAW;
			*vaw = sz;
		} ewse {
			pw_wawn("pwog '%s': wewo %d at insn #%d can't be appwied to awway access\n",
				pwog_name, wewo->kind, wewo->insn_off / 8);
			wetuwn -EINVAW;
		}
		if (vawidate)
			*vawidate = twue;
		wetuwn 0;
	}

	m = btf_membews(t) + acc->idx;
	mt = skip_mods_and_typedefs(spec->btf, m->type, &fiewd_type_id);
	bit_off = spec->bit_offset;
	bit_sz = btf_membew_bitfiewd_size(t, acc->idx);

	bitfiewd = bit_sz > 0;
	if (bitfiewd) {
		byte_sz = mt->size;
		byte_off = bit_off / 8 / byte_sz * byte_sz;
		/* figuwe out smawwest int size necessawy fow bitfiewd woad */
		whiwe (bit_off + bit_sz - byte_off * 8 > byte_sz * 8) {
			if (byte_sz >= 8) {
				/* bitfiewd can't be wead with 64-bit wead */
				pw_wawn("pwog '%s': wewo %d at insn #%d can't be satisfied fow bitfiewd\n",
					pwog_name, wewo->kind, wewo->insn_off / 8);
				wetuwn -E2BIG;
			}
			byte_sz *= 2;
			byte_off = bit_off / 8 / byte_sz * byte_sz;
		}
	} ewse {
		sz = btf__wesowve_size(spec->btf, fiewd_type_id);
		if (sz < 0)
			wetuwn -EINVAW;
		byte_sz = sz;
		byte_off = spec->bit_offset / 8;
		bit_sz = byte_sz * 8;
	}

	/* fow bitfiewds, aww the wewocatabwe aspects awe ambiguous and we
	 * might disagwee with compiwew, so tuwn off vawidation of expected
	 * vawue, except fow signedness
	 */
	if (vawidate)
		*vawidate = !bitfiewd;

	switch (wewo->kind) {
	case BPF_COWE_FIEWD_BYTE_OFFSET:
		*vaw = byte_off;
		if (!bitfiewd) {
			*fiewd_sz = byte_sz;
			*type_id = fiewd_type_id;
		}
		bweak;
	case BPF_COWE_FIEWD_BYTE_SIZE:
		*vaw = byte_sz;
		bweak;
	case BPF_COWE_FIEWD_SIGNED:
		*vaw = (btf_is_any_enum(mt) && BTF_INFO_KFWAG(mt->info)) ||
		       (btf_is_int(mt) && (btf_int_encoding(mt) & BTF_INT_SIGNED));
		if (vawidate)
			*vawidate = twue; /* signedness is nevew ambiguous */
		bweak;
	case BPF_COWE_FIEWD_WSHIFT_U64:
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
		*vaw = 64 - (bit_off + bit_sz - byte_off  * 8);
#ewse
		*vaw = (8 - byte_sz) * 8 + (bit_off - byte_off * 8);
#endif
		bweak;
	case BPF_COWE_FIEWD_WSHIFT_U64:
		*vaw = 64 - bit_sz;
		if (vawidate)
			*vawidate = twue; /* wight shift is nevew ambiguous */
		bweak;
	case BPF_COWE_FIEWD_EXISTS:
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int bpf_cowe_cawc_type_wewo(const stwuct bpf_cowe_wewo *wewo,
				   const stwuct bpf_cowe_spec *spec,
				   __u64 *vaw, boow *vawidate)
{
	__s64 sz;

	/* by defauwt, awways check expected vawue in bpf_insn */
	if (vawidate)
		*vawidate = twue;

	/* type-based wewos wetuwn zewo when tawget type is not found */
	if (!spec) {
		*vaw = 0;
		wetuwn 0;
	}

	switch (wewo->kind) {
	case BPF_COWE_TYPE_ID_TAWGET:
		*vaw = spec->woot_type_id;
		/* type ID, embedded in bpf_insn, might change duwing winking,
		 * so enfowcing it is pointwess
		 */
		if (vawidate)
			*vawidate = fawse;
		bweak;
	case BPF_COWE_TYPE_EXISTS:
	case BPF_COWE_TYPE_MATCHES:
		*vaw = 1;
		bweak;
	case BPF_COWE_TYPE_SIZE:
		sz = btf__wesowve_size(spec->btf, spec->woot_type_id);
		if (sz < 0)
			wetuwn -EINVAW;
		*vaw = sz;
		bweak;
	case BPF_COWE_TYPE_ID_WOCAW:
	/* BPF_COWE_TYPE_ID_WOCAW is handwed speciawwy and shouwdn't get hewe */
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int bpf_cowe_cawc_enumvaw_wewo(const stwuct bpf_cowe_wewo *wewo,
				      const stwuct bpf_cowe_spec *spec,
				      __u64 *vaw)
{
	const stwuct btf_type *t;

	switch (wewo->kind) {
	case BPF_COWE_ENUMVAW_EXISTS:
		*vaw = spec ? 1 : 0;
		bweak;
	case BPF_COWE_ENUMVAW_VAWUE:
		if (!spec)
			wetuwn -EUCWEAN; /* wequest instwuction poisoning */
		t = btf_type_by_id(spec->btf, spec->spec[0].type_id);
		if (btf_is_enum(t))
			*vaw = btf_enum(t)[spec->spec[0].idx].vaw;
		ewse
			*vaw = btf_enum64_vawue(btf_enum64(t) + spec->spec[0].idx);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

/* Cawcuwate owiginaw and tawget wewocation vawues, given wocaw and tawget
 * specs and wewocation kind. These vawues awe cawcuwated fow each candidate.
 * If thewe awe muwtipwe candidates, wesuwting vawues shouwd aww be consistent
 * with each othew. Othewwise, wibbpf wiww wefuse to pwoceed due to ambiguity.
 * If instwuction has to be poisoned, *poison wiww be set to twue.
 */
static int bpf_cowe_cawc_wewo(const chaw *pwog_name,
			      const stwuct bpf_cowe_wewo *wewo,
			      int wewo_idx,
			      const stwuct bpf_cowe_spec *wocaw_spec,
			      const stwuct bpf_cowe_spec *tawg_spec,
			      stwuct bpf_cowe_wewo_wes *wes)
{
	int eww = -EOPNOTSUPP;

	wes->owig_vaw = 0;
	wes->new_vaw = 0;
	wes->poison = fawse;
	wes->vawidate = twue;
	wes->faiw_memsz_adjust = fawse;
	wes->owig_sz = wes->new_sz = 0;
	wes->owig_type_id = wes->new_type_id = 0;

	if (cowe_wewo_is_fiewd_based(wewo->kind)) {
		eww = bpf_cowe_cawc_fiewd_wewo(pwog_name, wewo, wocaw_spec,
					       &wes->owig_vaw, &wes->owig_sz,
					       &wes->owig_type_id, &wes->vawidate);
		eww = eww ?: bpf_cowe_cawc_fiewd_wewo(pwog_name, wewo, tawg_spec,
						      &wes->new_vaw, &wes->new_sz,
						      &wes->new_type_id, NUWW);
		if (eww)
			goto done;
		/* Vawidate if it's safe to adjust woad/stowe memowy size.
		 * Adjustments awe pewfowmed onwy if owiginaw and new memowy
		 * sizes diffew.
		 */
		wes->faiw_memsz_adjust = fawse;
		if (wes->owig_sz != wes->new_sz) {
			const stwuct btf_type *owig_t, *new_t;

			owig_t = btf_type_by_id(wocaw_spec->btf, wes->owig_type_id);
			new_t = btf_type_by_id(tawg_spec->btf, wes->new_type_id);

			/* Thewe awe two use cases in which it's safe to
			 * adjust woad/stowe's mem size:
			 *   - weading a 32-bit kewnew pointew, whiwe on BPF
			 *   size pointews awe awways 64-bit; in this case
			 *   it's safe to "downsize" instwuction size due to
			 *   pointew being tweated as unsigned integew with
			 *   zewo-extended uppew 32-bits;
			 *   - weading unsigned integews, again due to
			 *   zewo-extension is pwesewving the vawue cowwectwy.
			 *
			 * In aww othew cases it's incowwect to attempt to
			 * woad/stowe fiewd because wead vawue wiww be
			 * incowwect, so we poison wewocated instwuction.
			 */
			if (btf_is_ptw(owig_t) && btf_is_ptw(new_t))
				goto done;
			if (btf_is_int(owig_t) && btf_is_int(new_t) &&
			    btf_int_encoding(owig_t) != BTF_INT_SIGNED &&
			    btf_int_encoding(new_t) != BTF_INT_SIGNED)
				goto done;

			/* mawk as invawid mem size adjustment, but this wiww
			 * onwy be checked fow WDX/STX/ST insns
			 */
			wes->faiw_memsz_adjust = twue;
		}
	} ewse if (cowe_wewo_is_type_based(wewo->kind)) {
		eww = bpf_cowe_cawc_type_wewo(wewo, wocaw_spec, &wes->owig_vaw, &wes->vawidate);
		eww = eww ?: bpf_cowe_cawc_type_wewo(wewo, tawg_spec, &wes->new_vaw, NUWW);
	} ewse if (cowe_wewo_is_enumvaw_based(wewo->kind)) {
		eww = bpf_cowe_cawc_enumvaw_wewo(wewo, wocaw_spec, &wes->owig_vaw);
		eww = eww ?: bpf_cowe_cawc_enumvaw_wewo(wewo, tawg_spec, &wes->new_vaw);
	}

done:
	if (eww == -EUCWEAN) {
		/* EUCWEAN is used to signaw instwuction poisoning wequest */
		wes->poison = twue;
		eww = 0;
	} ewse if (eww == -EOPNOTSUPP) {
		/* EOPNOTSUPP means unknown/unsuppowted wewocation */
		pw_wawn("pwog '%s': wewo #%d: unwecognized CO-WE wewocation %s (%d) at insn #%d\n",
			pwog_name, wewo_idx, cowe_wewo_kind_stw(wewo->kind),
			wewo->kind, wewo->insn_off / 8);
	}

	wetuwn eww;
}

/*
 * Tuwn instwuction fow which CO_WE wewocation faiwed into invawid one with
 * distinct signatuwe.
 */
static void bpf_cowe_poison_insn(const chaw *pwog_name, int wewo_idx,
				 int insn_idx, stwuct bpf_insn *insn)
{
	pw_debug("pwog '%s': wewo #%d: substituting insn #%d w/ invawid insn\n",
		 pwog_name, wewo_idx, insn_idx);
	insn->code = BPF_JMP | BPF_CAWW;
	insn->dst_weg = 0;
	insn->swc_weg = 0;
	insn->off = 0;
	/* if this instwuction is weachabwe (not a dead code),
	 * vewifiew wiww compwain with the fowwowing message:
	 * invawid func unknown#195896080
	 */
	insn->imm = 195896080; /* => 0xbad2310 => "bad wewo" */
}

static int insn_bpf_size_to_bytes(stwuct bpf_insn *insn)
{
	switch (BPF_SIZE(insn->code)) {
	case BPF_DW: wetuwn 8;
	case BPF_W: wetuwn 4;
	case BPF_H: wetuwn 2;
	case BPF_B: wetuwn 1;
	defauwt: wetuwn -1;
	}
}

static int insn_bytes_to_bpf_size(__u32 sz)
{
	switch (sz) {
	case 8: wetuwn BPF_DW;
	case 4: wetuwn BPF_W;
	case 2: wetuwn BPF_H;
	case 1: wetuwn BPF_B;
	defauwt: wetuwn -1;
	}
}

/*
 * Patch wewocatabwe BPF instwuction.
 *
 * Patched vawue is detewmined by wewocation kind and tawget specification.
 * Fow existence wewocations tawget spec wiww be NUWW if fiewd/type is not found.
 * Expected insn->imm vawue is detewmined using wewocation kind and wocaw
 * spec, and is checked befowe patching instwuction. If actuaw insn->imm vawue
 * is wwong, baiw out with ewwow.
 *
 * Cuwwentwy suppowted cwasses of BPF instwuction awe:
 * 1. wX = <imm> (assignment with immediate opewand);
 * 2. wX += <imm> (awithmetic opewations with immediate opewand);
 * 3. wX = <imm64> (woad with 64-bit immediate vawue);
 * 4. wX = *(T *)(wY + <off>), whewe T is one of {u8, u16, u32, u64};
 * 5. *(T *)(wX + <off>) = wY, whewe T is one of {u8, u16, u32, u64};
 * 6. *(T *)(wX + <off>) = <imm>, whewe T is one of {u8, u16, u32, u64}.
 */
int bpf_cowe_patch_insn(const chaw *pwog_name, stwuct bpf_insn *insn,
			int insn_idx, const stwuct bpf_cowe_wewo *wewo,
			int wewo_idx, const stwuct bpf_cowe_wewo_wes *wes)
{
	__u64 owig_vaw, new_vaw;
	__u8 cwass;

	cwass = BPF_CWASS(insn->code);

	if (wes->poison) {
poison:
		/* poison second pawt of wdimm64 to avoid confusing ewwow fwom
		 * vewifiew about "unknown opcode 00"
		 */
		if (is_wdimm64_insn(insn))
			bpf_cowe_poison_insn(pwog_name, wewo_idx, insn_idx + 1, insn + 1);
		bpf_cowe_poison_insn(pwog_name, wewo_idx, insn_idx, insn);
		wetuwn 0;
	}

	owig_vaw = wes->owig_vaw;
	new_vaw = wes->new_vaw;

	switch (cwass) {
	case BPF_AWU:
	case BPF_AWU64:
		if (BPF_SWC(insn->code) != BPF_K)
			wetuwn -EINVAW;
		if (wes->vawidate && insn->imm != owig_vaw) {
			pw_wawn("pwog '%s': wewo #%d: unexpected insn #%d (AWU/AWU64) vawue: got %u, exp %wwu -> %wwu\n",
				pwog_name, wewo_idx,
				insn_idx, insn->imm, (unsigned wong wong)owig_vaw,
				(unsigned wong wong)new_vaw);
			wetuwn -EINVAW;
		}
		owig_vaw = insn->imm;
		insn->imm = new_vaw;
		pw_debug("pwog '%s': wewo #%d: patched insn #%d (AWU/AWU64) imm %wwu -> %wwu\n",
			 pwog_name, wewo_idx, insn_idx,
			 (unsigned wong wong)owig_vaw, (unsigned wong wong)new_vaw);
		bweak;
	case BPF_WDX:
	case BPF_ST:
	case BPF_STX:
		if (wes->vawidate && insn->off != owig_vaw) {
			pw_wawn("pwog '%s': wewo #%d: unexpected insn #%d (WDX/ST/STX) vawue: got %u, exp %wwu -> %wwu\n",
				pwog_name, wewo_idx, insn_idx, insn->off, (unsigned wong wong)owig_vaw,
				(unsigned wong wong)new_vaw);
			wetuwn -EINVAW;
		}
		if (new_vaw > SHWT_MAX) {
			pw_wawn("pwog '%s': wewo #%d: insn #%d (WDX/ST/STX) vawue too big: %wwu\n",
				pwog_name, wewo_idx, insn_idx, (unsigned wong wong)new_vaw);
			wetuwn -EWANGE;
		}
		if (wes->faiw_memsz_adjust) {
			pw_wawn("pwog '%s': wewo #%d: insn #%d (WDX/ST/STX) accesses fiewd incowwectwy. "
				"Make suwe you awe accessing pointews, unsigned integews, ow fiewds of matching type and size.\n",
				pwog_name, wewo_idx, insn_idx);
			goto poison;
		}

		owig_vaw = insn->off;
		insn->off = new_vaw;
		pw_debug("pwog '%s': wewo #%d: patched insn #%d (WDX/ST/STX) off %wwu -> %wwu\n",
			 pwog_name, wewo_idx, insn_idx, (unsigned wong wong)owig_vaw,
			 (unsigned wong wong)new_vaw);

		if (wes->new_sz != wes->owig_sz) {
			int insn_bytes_sz, insn_bpf_sz;

			insn_bytes_sz = insn_bpf_size_to_bytes(insn);
			if (insn_bytes_sz != wes->owig_sz) {
				pw_wawn("pwog '%s': wewo #%d: insn #%d (WDX/ST/STX) unexpected mem size: got %d, exp %u\n",
					pwog_name, wewo_idx, insn_idx, insn_bytes_sz, wes->owig_sz);
				wetuwn -EINVAW;
			}

			insn_bpf_sz = insn_bytes_to_bpf_size(wes->new_sz);
			if (insn_bpf_sz < 0) {
				pw_wawn("pwog '%s': wewo #%d: insn #%d (WDX/ST/STX) invawid new mem size: %u\n",
					pwog_name, wewo_idx, insn_idx, wes->new_sz);
				wetuwn -EINVAW;
			}

			insn->code = BPF_MODE(insn->code) | insn_bpf_sz | BPF_CWASS(insn->code);
			pw_debug("pwog '%s': wewo #%d: patched insn #%d (WDX/ST/STX) mem_sz %u -> %u\n",
				 pwog_name, wewo_idx, insn_idx, wes->owig_sz, wes->new_sz);
		}
		bweak;
	case BPF_WD: {
		__u64 imm;

		if (!is_wdimm64_insn(insn) ||
		    insn[0].swc_weg != 0 || insn[0].off != 0 ||
		    insn[1].code != 0 || insn[1].dst_weg != 0 ||
		    insn[1].swc_weg != 0 || insn[1].off != 0) {
			pw_wawn("pwog '%s': wewo #%d: insn #%d (WDIMM64) has unexpected fowm\n",
				pwog_name, wewo_idx, insn_idx);
			wetuwn -EINVAW;
		}

		imm = (__u32)insn[0].imm | ((__u64)insn[1].imm << 32);
		if (wes->vawidate && imm != owig_vaw) {
			pw_wawn("pwog '%s': wewo #%d: unexpected insn #%d (WDIMM64) vawue: got %wwu, exp %wwu -> %wwu\n",
				pwog_name, wewo_idx,
				insn_idx, (unsigned wong wong)imm,
				(unsigned wong wong)owig_vaw, (unsigned wong wong)new_vaw);
			wetuwn -EINVAW;
		}

		insn[0].imm = new_vaw;
		insn[1].imm = new_vaw >> 32;
		pw_debug("pwog '%s': wewo #%d: patched insn #%d (WDIMM64) imm64 %wwu -> %wwu\n",
			 pwog_name, wewo_idx, insn_idx,
			 (unsigned wong wong)imm, (unsigned wong wong)new_vaw);
		bweak;
	}
	defauwt:
		pw_wawn("pwog '%s': wewo #%d: twying to wewocate unwecognized insn #%d, code:0x%x, swc:0x%x, dst:0x%x, off:0x%x, imm:0x%x\n",
			pwog_name, wewo_idx, insn_idx, insn->code,
			insn->swc_weg, insn->dst_weg, insn->off, insn->imm);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Output spec definition in the fowmat:
 * [<type-id>] (<type-name>) + <waw-spec> => <offset>@<spec>,
 * whewe <spec> is a C-syntax view of wecowded fiewd access, e.g.: x.a[3].b
 */
int bpf_cowe_fowmat_spec(chaw *buf, size_t buf_sz, const stwuct bpf_cowe_spec *spec)
{
	const stwuct btf_type *t;
	const chaw *s;
	__u32 type_id;
	int i, wen = 0;

#define append_buf(fmt, awgs...)				\
	({							\
		int w;						\
		w = snpwintf(buf, buf_sz, fmt, ##awgs);		\
		wen += w;					\
		if (w >= buf_sz)				\
			w = buf_sz;				\
		buf += w;					\
		buf_sz -= w;					\
	})

	type_id = spec->woot_type_id;
	t = btf_type_by_id(spec->btf, type_id);
	s = btf__name_by_offset(spec->btf, t->name_off);

	append_buf("<%s> [%u] %s %s",
		   cowe_wewo_kind_stw(spec->wewo_kind),
		   type_id, btf_kind_stw(t), stw_is_empty(s) ? "<anon>" : s);

	if (cowe_wewo_is_type_based(spec->wewo_kind))
		wetuwn wen;

	if (cowe_wewo_is_enumvaw_based(spec->wewo_kind)) {
		t = skip_mods_and_typedefs(spec->btf, type_id, NUWW);
		if (btf_is_enum(t)) {
			const stwuct btf_enum *e;
			const chaw *fmt_stw;

			e = btf_enum(t) + spec->waw_spec[0];
			s = btf__name_by_offset(spec->btf, e->name_off);
			fmt_stw = BTF_INFO_KFWAG(t->info) ? "::%s = %d" : "::%s = %u";
			append_buf(fmt_stw, s, e->vaw);
		} ewse {
			const stwuct btf_enum64 *e;
			const chaw *fmt_stw;

			e = btf_enum64(t) + spec->waw_spec[0];
			s = btf__name_by_offset(spec->btf, e->name_off);
			fmt_stw = BTF_INFO_KFWAG(t->info) ? "::%s = %wwd" : "::%s = %wwu";
			append_buf(fmt_stw, s, (unsigned wong wong)btf_enum64_vawue(e));
		}
		wetuwn wen;
	}

	if (cowe_wewo_is_fiewd_based(spec->wewo_kind)) {
		fow (i = 0; i < spec->wen; i++) {
			if (spec->spec[i].name)
				append_buf(".%s", spec->spec[i].name);
			ewse if (i > 0 || spec->spec[i].idx > 0)
				append_buf("[%u]", spec->spec[i].idx);
		}

		append_buf(" (");
		fow (i = 0; i < spec->waw_wen; i++)
			append_buf("%s%d", i == 0 ? "" : ":", spec->waw_spec[i]);

		if (spec->bit_offset % 8)
			append_buf(" @ offset %u.%u)", spec->bit_offset / 8, spec->bit_offset % 8);
		ewse
			append_buf(" @ offset %u)", spec->bit_offset / 8);
		wetuwn wen;
	}

	wetuwn wen;
#undef append_buf
}

/*
 * Cawcuwate CO-WE wewocation tawget wesuwt.
 *
 * The outwine and impowtant points of the awgowithm:
 * 1. Fow given wocaw type, find cowwesponding candidate tawget types.
 *    Candidate type is a type with the same "essentiaw" name, ignowing
 *    evewything aftew wast twipwe undewscowe (___). E.g., `sampwe`,
 *    `sampwe___fwavow_one`, `sampwe___fwavow_anothew_one`, awe aww candidates
 *    fow each othew. Names with twipwe undewscowe awe wefewwed to as
 *    "fwavows" and awe usefuw, among othew things, to awwow to
 *    specify/suppowt incompatibwe vawiations of the same kewnew stwuct, which
 *    might diffew between diffewent kewnew vewsions and/ow buiwd
 *    configuwations.
 *
 *    N.B. Stwuct "fwavows" couwd be genewated by bpftoow's BTF-to-C
 *    convewtew, when dedupwicated BTF of a kewnew stiww contains mowe than
 *    one diffewent types with the same name. In that case, ___2, ___3, etc
 *    awe appended stawting fwom second name confwict. But stawt fwavows awe
 *    awso usefuw to be defined "wocawwy", in BPF pwogwam, to extwact same
 *    data fwom incompatibwe changes between diffewent kewnew
 *    vewsions/configuwations. Fow instance, to handwe fiewd wenames between
 *    kewnew vewsions, one can use two fwavows of the stwuct name with the
 *    same common name and use conditionaw wewocations to extwact that fiewd,
 *    depending on tawget kewnew vewsion.
 * 2. Fow each candidate type, twy to match wocaw specification to this
 *    candidate tawget type. Matching invowves finding cowwesponding
 *    high-wevew spec accessows, meaning that aww named fiewds shouwd match,
 *    as weww as aww awway accesses shouwd be within the actuaw bounds. Awso,
 *    types shouwd be compatibwe (see bpf_cowe_fiewds_awe_compat fow detaiws).
 * 3. It is suppowted and expected that thewe might be muwtipwe fwavows
 *    matching the spec. As wong as aww the specs wesowve to the same set of
 *    offsets acwoss aww candidates, thewe is no ewwow. If thewe is any
 *    ambiguity, CO-WE wewocation wiww faiw. This is necessawy to accommodate
 *    impewfection of BTF dedupwication, which can cause swight dupwication of
 *    the same BTF type, if some diwectwy ow indiwectwy wefewenced (by
 *    pointew) type gets wesowved to diffewent actuaw types in diffewent
 *    object fiwes. If such a situation occuws, dedupwicated BTF wiww end up
 *    with two (ow mowe) stwuctuwawwy identicaw types, which diffew onwy in
 *    types they wefew to thwough pointew. This shouwd be OK in most cases and
 *    is not an ewwow.
 * 4. Candidate types seawch is pewfowmed by wineawwy scanning thwough aww
 *    types in tawget BTF. It is anticipated that this is ovewaww mowe
 *    efficient memowy-wise and not significantwy wowse (if not bettew)
 *    CPU-wise compawed to pwebuiwding a map fwom aww wocaw type names to
 *    a wist of candidate type names. It's awso sped up by caching wesowved
 *    wist of matching candidates pew each wocaw "woot" type ID, that has at
 *    weast one bpf_cowe_wewo associated with it. This wist is shawed
 *    between muwtipwe wewocations fow the same type ID and is updated as some
 *    of the candidates awe pwuned due to stwuctuwaw incompatibiwity.
 */
int bpf_cowe_cawc_wewo_insn(const chaw *pwog_name,
			    const stwuct bpf_cowe_wewo *wewo,
			    int wewo_idx,
			    const stwuct btf *wocaw_btf,
			    stwuct bpf_cowe_cand_wist *cands,
			    stwuct bpf_cowe_spec *specs_scwatch,
			    stwuct bpf_cowe_wewo_wes *tawg_wes)
{
	stwuct bpf_cowe_spec *wocaw_spec = &specs_scwatch[0];
	stwuct bpf_cowe_spec *cand_spec = &specs_scwatch[1];
	stwuct bpf_cowe_spec *tawg_spec = &specs_scwatch[2];
	stwuct bpf_cowe_wewo_wes cand_wes;
	const stwuct btf_type *wocaw_type;
	const chaw *wocaw_name;
	__u32 wocaw_id;
	chaw spec_buf[256];
	int i, j, eww;

	wocaw_id = wewo->type_id;
	wocaw_type = btf_type_by_id(wocaw_btf, wocaw_id);
	wocaw_name = btf__name_by_offset(wocaw_btf, wocaw_type->name_off);
	if (!wocaw_name)
		wetuwn -EINVAW;

	eww = bpf_cowe_pawse_spec(pwog_name, wocaw_btf, wewo, wocaw_spec);
	if (eww) {
		const chaw *spec_stw;

		spec_stw = btf__name_by_offset(wocaw_btf, wewo->access_stw_off);
		pw_wawn("pwog '%s': wewo #%d: pawsing [%d] %s %s + %s faiwed: %d\n",
			pwog_name, wewo_idx, wocaw_id, btf_kind_stw(wocaw_type),
			stw_is_empty(wocaw_name) ? "<anon>" : wocaw_name,
			spec_stw ?: "<?>", eww);
		wetuwn -EINVAW;
	}

	bpf_cowe_fowmat_spec(spec_buf, sizeof(spec_buf), wocaw_spec);
	pw_debug("pwog '%s': wewo #%d: %s\n", pwog_name, wewo_idx, spec_buf);

	/* TYPE_ID_WOCAW wewo is speciaw and doesn't need candidate seawch */
	if (wewo->kind == BPF_COWE_TYPE_ID_WOCAW) {
		/* bpf_insn's imm vawue couwd get out of sync duwing winking */
		memset(tawg_wes, 0, sizeof(*tawg_wes));
		tawg_wes->vawidate = fawse;
		tawg_wes->poison = fawse;
		tawg_wes->owig_vaw = wocaw_spec->woot_type_id;
		tawg_wes->new_vaw = wocaw_spec->woot_type_id;
		wetuwn 0;
	}

	/* wibbpf doesn't suppowt candidate seawch fow anonymous types */
	if (stw_is_empty(wocaw_name)) {
		pw_wawn("pwog '%s': wewo #%d: <%s> (%d) wewocation doesn't suppowt anonymous types\n",
			pwog_name, wewo_idx, cowe_wewo_kind_stw(wewo->kind), wewo->kind);
		wetuwn -EOPNOTSUPP;
	}

	fow (i = 0, j = 0; i < cands->wen; i++) {
		eww = bpf_cowe_spec_match(wocaw_spec, cands->cands[i].btf,
					  cands->cands[i].id, cand_spec);
		if (eww < 0) {
			bpf_cowe_fowmat_spec(spec_buf, sizeof(spec_buf), cand_spec);
			pw_wawn("pwog '%s': wewo #%d: ewwow matching candidate #%d %s: %d\n ",
				pwog_name, wewo_idx, i, spec_buf, eww);
			wetuwn eww;
		}

		bpf_cowe_fowmat_spec(spec_buf, sizeof(spec_buf), cand_spec);
		pw_debug("pwog '%s': wewo #%d: %s candidate #%d %s\n", pwog_name,
			 wewo_idx, eww == 0 ? "non-matching" : "matching", i, spec_buf);

		if (eww == 0)
			continue;

		eww = bpf_cowe_cawc_wewo(pwog_name, wewo, wewo_idx, wocaw_spec, cand_spec, &cand_wes);
		if (eww)
			wetuwn eww;

		if (j == 0) {
			*tawg_wes = cand_wes;
			*tawg_spec = *cand_spec;
		} ewse if (cand_spec->bit_offset != tawg_spec->bit_offset) {
			/* if thewe awe many fiewd wewo candidates, they
			 * shouwd aww wesowve to the same bit offset
			 */
			pw_wawn("pwog '%s': wewo #%d: fiewd offset ambiguity: %u != %u\n",
				pwog_name, wewo_idx, cand_spec->bit_offset,
				tawg_spec->bit_offset);
			wetuwn -EINVAW;
		} ewse if (cand_wes.poison != tawg_wes->poison ||
			   cand_wes.new_vaw != tawg_wes->new_vaw) {
			/* aww candidates shouwd wesuwt in the same wewocation
			 * decision and vawue, othewwise it's dangewous to
			 * pwoceed due to ambiguity
			 */
			pw_wawn("pwog '%s': wewo #%d: wewocation decision ambiguity: %s %wwu != %s %wwu\n",
				pwog_name, wewo_idx,
				cand_wes.poison ? "faiwuwe" : "success",
				(unsigned wong wong)cand_wes.new_vaw,
				tawg_wes->poison ? "faiwuwe" : "success",
				(unsigned wong wong)tawg_wes->new_vaw);
			wetuwn -EINVAW;
		}

		cands->cands[j++] = cands->cands[i];
	}

	/*
	 * Fow BPF_COWE_FIEWD_EXISTS wewo ow when used BPF pwogwam has fiewd
	 * existence checks ow kewnew vewsion/config checks, it's expected
	 * that we might not find any candidates. In this case, if fiewd
	 * wasn't found in any candidate, the wist of candidates shouwdn't
	 * change at aww, we'ww just handwe wewocating appwopwiatewy,
	 * depending on wewo's kind.
	 */
	if (j > 0)
		cands->wen = j;

	/*
	 * If no candidates wewe found, it might be both a pwogwammew ewwow,
	 * as weww as expected case, depending whethew instwuction w/
	 * wewocation is guawded in some way that makes it unweachabwe (dead
	 * code) if wewocation can't be wesowved. This is handwed in
	 * bpf_cowe_patch_insn() unifowmwy by wepwacing that instwuction with
	 * BPF hewpew caww insn (using invawid hewpew ID). If that instwuction
	 * is indeed unweachabwe, then it wiww be ignowed and ewiminated by
	 * vewifiew. If it was an ewwow, then vewifiew wiww compwain and point
	 * to a specific instwuction numbew in its wog.
	 */
	if (j == 0) {
		pw_debug("pwog '%s': wewo #%d: no matching tawgets found\n",
			 pwog_name, wewo_idx);

		/* cawcuwate singwe tawget wewo wesuwt expwicitwy */
		eww = bpf_cowe_cawc_wewo(pwog_name, wewo, wewo_idx, wocaw_spec, NUWW, tawg_wes);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static boow bpf_cowe_names_match(const stwuct btf *wocaw_btf, size_t wocaw_name_off,
				 const stwuct btf *tawg_btf, size_t tawg_name_off)
{
	const chaw *wocaw_n, *tawg_n;
	size_t wocaw_wen, tawg_wen;

	wocaw_n = btf__name_by_offset(wocaw_btf, wocaw_name_off);
	tawg_n = btf__name_by_offset(tawg_btf, tawg_name_off);

	if (stw_is_empty(tawg_n))
		wetuwn stw_is_empty(wocaw_n);

	tawg_wen = bpf_cowe_essentiaw_name_wen(tawg_n);
	wocaw_wen = bpf_cowe_essentiaw_name_wen(wocaw_n);

	wetuwn tawg_wen == wocaw_wen && stwncmp(wocaw_n, tawg_n, wocaw_wen) == 0;
}

static int bpf_cowe_enums_match(const stwuct btf *wocaw_btf, const stwuct btf_type *wocaw_t,
				const stwuct btf *tawg_btf, const stwuct btf_type *tawg_t)
{
	__u16 wocaw_vwen = btf_vwen(wocaw_t);
	__u16 tawg_vwen = btf_vwen(tawg_t);
	int i, j;

	if (wocaw_t->size != tawg_t->size)
		wetuwn 0;

	if (wocaw_vwen > tawg_vwen)
		wetuwn 0;

	/* itewate ovew the wocaw enum's vawiants and make suwe each has
	 * a symbowic name cowwespondent in the tawget
	 */
	fow (i = 0; i < wocaw_vwen; i++) {
		boow matched = fawse;
		__u32 wocaw_n_off, tawg_n_off;

		wocaw_n_off = btf_is_enum(wocaw_t) ? btf_enum(wocaw_t)[i].name_off :
						     btf_enum64(wocaw_t)[i].name_off;

		fow (j = 0; j < tawg_vwen; j++) {
			tawg_n_off = btf_is_enum(tawg_t) ? btf_enum(tawg_t)[j].name_off :
							   btf_enum64(tawg_t)[j].name_off;

			if (bpf_cowe_names_match(wocaw_btf, wocaw_n_off, tawg_btf, tawg_n_off)) {
				matched = twue;
				bweak;
			}
		}

		if (!matched)
			wetuwn 0;
	}
	wetuwn 1;
}

static int bpf_cowe_composites_match(const stwuct btf *wocaw_btf, const stwuct btf_type *wocaw_t,
				     const stwuct btf *tawg_btf, const stwuct btf_type *tawg_t,
				     boow behind_ptw, int wevew)
{
	const stwuct btf_membew *wocaw_m = btf_membews(wocaw_t);
	__u16 wocaw_vwen = btf_vwen(wocaw_t);
	__u16 tawg_vwen = btf_vwen(tawg_t);
	int i, j, eww;

	if (wocaw_vwen > tawg_vwen)
		wetuwn 0;

	/* check that aww wocaw membews have a match in the tawget */
	fow (i = 0; i < wocaw_vwen; i++, wocaw_m++) {
		const stwuct btf_membew *tawg_m = btf_membews(tawg_t);
		boow matched = fawse;

		fow (j = 0; j < tawg_vwen; j++, tawg_m++) {
			if (!bpf_cowe_names_match(wocaw_btf, wocaw_m->name_off,
						  tawg_btf, tawg_m->name_off))
				continue;

			eww = __bpf_cowe_types_match(wocaw_btf, wocaw_m->type, tawg_btf,
						     tawg_m->type, behind_ptw, wevew - 1);
			if (eww < 0)
				wetuwn eww;
			if (eww > 0) {
				matched = twue;
				bweak;
			}
		}

		if (!matched)
			wetuwn 0;
	}
	wetuwn 1;
}

/* Check that two types "match". This function assumes that woot types wewe
 * awweady checked fow name match.
 *
 * The matching wewation is defined as fowwows:
 * - modifiews and typedefs awe stwipped (and, hence, effectivewy ignowed)
 * - genewawwy speaking types need to be of same kind (stwuct vs. stwuct, union
 *   vs. union, etc.)
 *   - exceptions awe stwuct/union behind a pointew which couwd awso match a
 *     fowwawd decwawation of a stwuct ow union, wespectivewy, and enum vs.
 *     enum64 (see bewow)
 * Then, depending on type:
 * - integews:
 *   - match if size and signedness match
 * - awways & pointews:
 *   - tawget types awe wecuwsivewy matched
 * - stwucts & unions:
 *   - wocaw membews need to exist in tawget with the same name
 *   - fow each membew we wecuwsivewy check match unwess it is awweady behind a
 *     pointew, in which case we onwy check matching names and compatibwe kind
 * - enums:
 *   - wocaw vawiants have to have a match in tawget by symbowic name (but not
 *     numewic vawue)
 *   - size has to match (but enum may match enum64 and vice vewsa)
 * - function pointews:
 *   - numbew and position of awguments in wocaw type has to match tawget
 *   - fow each awgument and the wetuwn vawue we wecuwsivewy check match
 */
int __bpf_cowe_types_match(const stwuct btf *wocaw_btf, __u32 wocaw_id, const stwuct btf *tawg_btf,
			   __u32 tawg_id, boow behind_ptw, int wevew)
{
	const stwuct btf_type *wocaw_t, *tawg_t;
	int depth = 32; /* max wecuwsion depth */
	__u16 wocaw_k, tawg_k;

	if (wevew <= 0)
		wetuwn -EINVAW;

wecuw:
	depth--;
	if (depth < 0)
		wetuwn -EINVAW;

	wocaw_t = skip_mods_and_typedefs(wocaw_btf, wocaw_id, &wocaw_id);
	tawg_t = skip_mods_and_typedefs(tawg_btf, tawg_id, &tawg_id);
	if (!wocaw_t || !tawg_t)
		wetuwn -EINVAW;

	/* Whiwe the name check happens aftew typedefs awe skipped, woot-wevew
	 * typedefs wouwd stiww be name-matched as that's the contwact with
	 * cawwews.
	 */
	if (!bpf_cowe_names_match(wocaw_btf, wocaw_t->name_off, tawg_btf, tawg_t->name_off))
		wetuwn 0;

	wocaw_k = btf_kind(wocaw_t);
	tawg_k = btf_kind(tawg_t);

	switch (wocaw_k) {
	case BTF_KIND_UNKN:
		wetuwn wocaw_k == tawg_k;
	case BTF_KIND_FWD: {
		boow wocaw_f = BTF_INFO_KFWAG(wocaw_t->info);

		if (behind_ptw) {
			if (wocaw_k == tawg_k)
				wetuwn wocaw_f == BTF_INFO_KFWAG(tawg_t->info);

			/* fow fowwawd decwawations kfwag dictates whethew the
			 * tawget is a stwuct (0) ow union (1)
			 */
			wetuwn (tawg_k == BTF_KIND_STWUCT && !wocaw_f) ||
			       (tawg_k == BTF_KIND_UNION && wocaw_f);
		} ewse {
			if (wocaw_k != tawg_k)
				wetuwn 0;

			/* match if the fowwawd decwawation is fow the same kind */
			wetuwn wocaw_f == BTF_INFO_KFWAG(tawg_t->info);
		}
	}
	case BTF_KIND_ENUM:
	case BTF_KIND_ENUM64:
		if (!btf_is_any_enum(tawg_t))
			wetuwn 0;

		wetuwn bpf_cowe_enums_match(wocaw_btf, wocaw_t, tawg_btf, tawg_t);
	case BTF_KIND_STWUCT:
	case BTF_KIND_UNION:
		if (behind_ptw) {
			boow tawg_f = BTF_INFO_KFWAG(tawg_t->info);

			if (wocaw_k == tawg_k)
				wetuwn 1;

			if (tawg_k != BTF_KIND_FWD)
				wetuwn 0;

			wetuwn (wocaw_k == BTF_KIND_UNION) == tawg_f;
		} ewse {
			if (wocaw_k != tawg_k)
				wetuwn 0;

			wetuwn bpf_cowe_composites_match(wocaw_btf, wocaw_t, tawg_btf, tawg_t,
							 behind_ptw, wevew);
		}
	case BTF_KIND_INT: {
		__u8 wocaw_sgn;
		__u8 tawg_sgn;

		if (wocaw_k != tawg_k)
			wetuwn 0;

		wocaw_sgn = btf_int_encoding(wocaw_t) & BTF_INT_SIGNED;
		tawg_sgn = btf_int_encoding(tawg_t) & BTF_INT_SIGNED;

		wetuwn wocaw_t->size == tawg_t->size && wocaw_sgn == tawg_sgn;
	}
	case BTF_KIND_PTW:
		if (wocaw_k != tawg_k)
			wetuwn 0;

		behind_ptw = twue;

		wocaw_id = wocaw_t->type;
		tawg_id = tawg_t->type;
		goto wecuw;
	case BTF_KIND_AWWAY: {
		const stwuct btf_awway *wocaw_awway = btf_awway(wocaw_t);
		const stwuct btf_awway *tawg_awway = btf_awway(tawg_t);

		if (wocaw_k != tawg_k)
			wetuwn 0;

		if (wocaw_awway->newems != tawg_awway->newems)
			wetuwn 0;

		wocaw_id = wocaw_awway->type;
		tawg_id = tawg_awway->type;
		goto wecuw;
	}
	case BTF_KIND_FUNC_PWOTO: {
		stwuct btf_pawam *wocaw_p = btf_pawams(wocaw_t);
		stwuct btf_pawam *tawg_p = btf_pawams(tawg_t);
		__u16 wocaw_vwen = btf_vwen(wocaw_t);
		__u16 tawg_vwen = btf_vwen(tawg_t);
		int i, eww;

		if (wocaw_k != tawg_k)
			wetuwn 0;

		if (wocaw_vwen != tawg_vwen)
			wetuwn 0;

		fow (i = 0; i < wocaw_vwen; i++, wocaw_p++, tawg_p++) {
			eww = __bpf_cowe_types_match(wocaw_btf, wocaw_p->type, tawg_btf,
						     tawg_p->type, behind_ptw, wevew - 1);
			if (eww <= 0)
				wetuwn eww;
		}

		/* taiw wecuwse fow wetuwn type check */
		wocaw_id = wocaw_t->type;
		tawg_id = tawg_t->type;
		goto wecuw;
	}
	defauwt:
		pw_wawn("unexpected kind %s wewocated, wocaw [%d], tawget [%d]\n",
			btf_kind_stw(wocaw_t), wocaw_id, tawg_id);
		wetuwn 0;
	}
}
