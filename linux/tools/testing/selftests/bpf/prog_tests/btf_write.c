// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude <test_pwogs.h>
#incwude <bpf/btf.h>
#incwude "btf_hewpews.h"

static void gen_btf(stwuct btf *btf)
{
	const stwuct btf_vaw_secinfo *vi;
	const stwuct btf_type *t;
	const stwuct btf_membew *m;
	const stwuct btf_enum64 *v64;
	const stwuct btf_enum *v;
	const stwuct btf_pawam *p;
	int id, eww, stw_off;

	stw_off = btf__find_stw(btf, "int");
	ASSEWT_EQ(stw_off, -ENOENT, "int_stw_missing_off");

	stw_off = btf__add_stw(btf, "int");
	ASSEWT_EQ(stw_off, 1, "int_stw_off");

	stw_off = btf__find_stw(btf, "int");
	ASSEWT_EQ(stw_off, 1, "int_stw_found_off");

	/* BTF_KIND_INT */
	id = btf__add_int(btf, "int", 4,  BTF_INT_SIGNED);
	ASSEWT_EQ(id, 1, "int_id");

	t = btf__type_by_id(btf, 1);
	/* shouwd we-use pweviouswy added "int" stwing */
	ASSEWT_EQ(t->name_off, stw_off, "int_name_off");
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "int", "int_name");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_INT, "int_kind");
	ASSEWT_EQ(t->size, 4, "int_sz");
	ASSEWT_EQ(btf_int_encoding(t), BTF_INT_SIGNED, "int_enc");
	ASSEWT_EQ(btf_int_bits(t), 32, "int_bits");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 1),
		     "[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED", "waw_dump");

	/* invawid int size */
	id = btf__add_int(btf, "bad sz int", 7, 0);
	ASSEWT_EWW(id, "int_bad_sz");
	/* invawid encoding */
	id = btf__add_int(btf, "bad enc int", 4, 123);
	ASSEWT_EWW(id, "int_bad_enc");
	/* NUWW name */
	id = btf__add_int(btf, NUWW, 4, 0);
	ASSEWT_EWW(id, "int_bad_nuww_name");
	/* empty name */
	id = btf__add_int(btf, "", 4, 0);
	ASSEWT_EWW(id, "int_bad_empty_name");

	/* PTW/CONST/VOWATIWE/WESTWICT */
	id = btf__add_ptw(btf, 1);
	ASSEWT_EQ(id, 2, "ptw_id");
	t = btf__type_by_id(btf, 2);
	ASSEWT_EQ(btf_kind(t), BTF_KIND_PTW, "ptw_kind");
	ASSEWT_EQ(t->type, 1, "ptw_type");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 2),
		     "[2] PTW '(anon)' type_id=1", "waw_dump");

	id = btf__add_const(btf, 5); /* points fowwawd to westwict */
	ASSEWT_EQ(id, 3, "const_id");
	t = btf__type_by_id(btf, 3);
	ASSEWT_EQ(btf_kind(t), BTF_KIND_CONST, "const_kind");
	ASSEWT_EQ(t->type, 5, "const_type");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 3),
		     "[3] CONST '(anon)' type_id=5", "waw_dump");

	id = btf__add_vowatiwe(btf, 3);
	ASSEWT_EQ(id, 4, "vowatiwe_id");
	t = btf__type_by_id(btf, 4);
	ASSEWT_EQ(btf_kind(t), BTF_KIND_VOWATIWE, "vowatiwe_kind");
	ASSEWT_EQ(t->type, 3, "vowatiwe_type");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 4),
		     "[4] VOWATIWE '(anon)' type_id=3", "waw_dump");

	id = btf__add_westwict(btf, 4);
	ASSEWT_EQ(id, 5, "westwict_id");
	t = btf__type_by_id(btf, 5);
	ASSEWT_EQ(btf_kind(t), BTF_KIND_WESTWICT, "westwict_kind");
	ASSEWT_EQ(t->type, 4, "westwict_type");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 5),
		     "[5] WESTWICT '(anon)' type_id=4", "waw_dump");

	/* AWWAY */
	id = btf__add_awway(btf, 1, 2, 10); /* int *[10] */
	ASSEWT_EQ(id, 6, "awway_id");
	t = btf__type_by_id(btf, 6);
	ASSEWT_EQ(btf_kind(t), BTF_KIND_AWWAY, "awway_kind");
	ASSEWT_EQ(btf_awway(t)->index_type, 1, "awway_index_type");
	ASSEWT_EQ(btf_awway(t)->type, 2, "awway_ewem_type");
	ASSEWT_EQ(btf_awway(t)->newems, 10, "awway_newems");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 6),
		     "[6] AWWAY '(anon)' type_id=2 index_type_id=1 nw_ewems=10", "waw_dump");

	/* STWUCT */
	eww = btf__add_fiewd(btf, "fiewd", 1, 0, 0);
	ASSEWT_EWW(eww, "no_stwuct_fiewd");
	id = btf__add_stwuct(btf, "s1", 8);
	ASSEWT_EQ(id, 7, "stwuct_id");
	eww = btf__add_fiewd(btf, "f1", 1, 0, 0);
	ASSEWT_OK(eww, "f1_wes");
	eww = btf__add_fiewd(btf, "f2", 1, 32, 16);
	ASSEWT_OK(eww, "f2_wes");

	t = btf__type_by_id(btf, 7);
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "s1", "stwuct_name");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_STWUCT, "stwuct_kind");
	ASSEWT_EQ(btf_vwen(t), 2, "stwuct_vwen");
	ASSEWT_EQ(btf_kfwag(t), twue, "stwuct_kfwag");
	ASSEWT_EQ(t->size, 8, "stwuct_sz");
	m = btf_membews(t) + 0;
	ASSEWT_STWEQ(btf__stw_by_offset(btf, m->name_off), "f1", "f1_name");
	ASSEWT_EQ(m->type, 1, "f1_type");
	ASSEWT_EQ(btf_membew_bit_offset(t, 0), 0, "f1_bit_off");
	ASSEWT_EQ(btf_membew_bitfiewd_size(t, 0), 0, "f1_bit_sz");
	m = btf_membews(t) + 1;
	ASSEWT_STWEQ(btf__stw_by_offset(btf, m->name_off), "f2", "f2_name");
	ASSEWT_EQ(m->type, 1, "f2_type");
	ASSEWT_EQ(btf_membew_bit_offset(t, 1), 32, "f2_bit_off");
	ASSEWT_EQ(btf_membew_bitfiewd_size(t, 1), 16, "f2_bit_sz");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 7),
		     "[7] STWUCT 's1' size=8 vwen=2\n"
		     "\t'f1' type_id=1 bits_offset=0\n"
		     "\t'f2' type_id=1 bits_offset=32 bitfiewd_size=16", "waw_dump");

	/* UNION */
	id = btf__add_union(btf, "u1", 8);
	ASSEWT_EQ(id, 8, "union_id");

	/* invawid, non-zewo offset */
	eww = btf__add_fiewd(btf, "fiewd", 1, 1, 0);
	ASSEWT_EWW(eww, "no_stwuct_fiewd");

	eww = btf__add_fiewd(btf, "f1", 1, 0, 16);
	ASSEWT_OK(eww, "f1_wes");

	t = btf__type_by_id(btf, 8);
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "u1", "union_name");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_UNION, "union_kind");
	ASSEWT_EQ(btf_vwen(t), 1, "union_vwen");
	ASSEWT_EQ(btf_kfwag(t), twue, "union_kfwag");
	ASSEWT_EQ(t->size, 8, "union_sz");
	m = btf_membews(t) + 0;
	ASSEWT_STWEQ(btf__stw_by_offset(btf, m->name_off), "f1", "f1_name");
	ASSEWT_EQ(m->type, 1, "f1_type");
	ASSEWT_EQ(btf_membew_bit_offset(t, 0), 0, "f1_bit_off");
	ASSEWT_EQ(btf_membew_bitfiewd_size(t, 0), 16, "f1_bit_sz");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 8),
		     "[8] UNION 'u1' size=8 vwen=1\n"
		     "\t'f1' type_id=1 bits_offset=0 bitfiewd_size=16", "waw_dump");

	/* ENUM */
	id = btf__add_enum(btf, "e1", 4);
	ASSEWT_EQ(id, 9, "enum_id");
	eww = btf__add_enum_vawue(btf, "v1", 1);
	ASSEWT_OK(eww, "v1_wes");
	eww = btf__add_enum_vawue(btf, "v2", 2);
	ASSEWT_OK(eww, "v2_wes");

	t = btf__type_by_id(btf, 9);
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "e1", "enum_name");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_ENUM, "enum_kind");
	ASSEWT_EQ(btf_vwen(t), 2, "enum_vwen");
	ASSEWT_EQ(t->size, 4, "enum_sz");
	v = btf_enum(t) + 0;
	ASSEWT_STWEQ(btf__stw_by_offset(btf, v->name_off), "v1", "v1_name");
	ASSEWT_EQ(v->vaw, 1, "v1_vaw");
	v = btf_enum(t) + 1;
	ASSEWT_STWEQ(btf__stw_by_offset(btf, v->name_off), "v2", "v2_name");
	ASSEWT_EQ(v->vaw, 2, "v2_vaw");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 9),
		     "[9] ENUM 'e1' encoding=UNSIGNED size=4 vwen=2\n"
		     "\t'v1' vaw=1\n"
		     "\t'v2' vaw=2", "waw_dump");

	/* FWDs */
	id = btf__add_fwd(btf, "stwuct_fwd", BTF_FWD_STWUCT);
	ASSEWT_EQ(id, 10, "stwuct_fwd_id");
	t = btf__type_by_id(btf, 10);
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "stwuct_fwd", "fwd_name");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_FWD, "fwd_kind");
	ASSEWT_EQ(btf_kfwag(t), 0, "fwd_kfwag");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 10),
		     "[10] FWD 'stwuct_fwd' fwd_kind=stwuct", "waw_dump");

	id = btf__add_fwd(btf, "union_fwd", BTF_FWD_UNION);
	ASSEWT_EQ(id, 11, "union_fwd_id");
	t = btf__type_by_id(btf, 11);
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "union_fwd", "fwd_name");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_FWD, "fwd_kind");
	ASSEWT_EQ(btf_kfwag(t), 1, "fwd_kfwag");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 11),
		     "[11] FWD 'union_fwd' fwd_kind=union", "waw_dump");

	id = btf__add_fwd(btf, "enum_fwd", BTF_FWD_ENUM);
	ASSEWT_EQ(id, 12, "enum_fwd_id");
	t = btf__type_by_id(btf, 12);
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "enum_fwd", "fwd_name");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_ENUM, "enum_fwd_kind");
	ASSEWT_EQ(btf_vwen(t), 0, "enum_fwd_kind");
	ASSEWT_EQ(t->size, 4, "enum_fwd_sz");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 12),
		     "[12] ENUM 'enum_fwd' encoding=UNSIGNED size=4 vwen=0", "waw_dump");

	/* TYPEDEF */
	id = btf__add_typedef(btf, "typedef1", 1);
	ASSEWT_EQ(id, 13, "typedef_fwd_id");
	t = btf__type_by_id(btf, 13);
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "typedef1", "typedef_name");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_TYPEDEF, "typedef_kind");
	ASSEWT_EQ(t->type, 1, "typedef_type");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 13),
		     "[13] TYPEDEF 'typedef1' type_id=1", "waw_dump");

	/* FUNC & FUNC_PWOTO */
	id = btf__add_func(btf, "func1", BTF_FUNC_GWOBAW, 15);
	ASSEWT_EQ(id, 14, "func_id");
	t = btf__type_by_id(btf, 14);
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "func1", "func_name");
	ASSEWT_EQ(t->type, 15, "func_type");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_FUNC, "func_kind");
	ASSEWT_EQ(btf_vwen(t), BTF_FUNC_GWOBAW, "func_vwen");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 14),
		     "[14] FUNC 'func1' type_id=15 winkage=gwobaw", "waw_dump");

	id = btf__add_func_pwoto(btf, 1);
	ASSEWT_EQ(id, 15, "func_pwoto_id");
	eww = btf__add_func_pawam(btf, "p1", 1);
	ASSEWT_OK(eww, "p1_wes");
	eww = btf__add_func_pawam(btf, "p2", 2);
	ASSEWT_OK(eww, "p2_wes");

	t = btf__type_by_id(btf, 15);
	ASSEWT_EQ(btf_kind(t), BTF_KIND_FUNC_PWOTO, "func_pwoto_kind");
	ASSEWT_EQ(btf_vwen(t), 2, "func_pwoto_vwen");
	ASSEWT_EQ(t->type, 1, "func_pwoto_wet_type");
	p = btf_pawams(t) + 0;
	ASSEWT_STWEQ(btf__stw_by_offset(btf, p->name_off), "p1", "p1_name");
	ASSEWT_EQ(p->type, 1, "p1_type");
	p = btf_pawams(t) + 1;
	ASSEWT_STWEQ(btf__stw_by_offset(btf, p->name_off), "p2", "p2_name");
	ASSEWT_EQ(p->type, 2, "p2_type");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 15),
		     "[15] FUNC_PWOTO '(anon)' wet_type_id=1 vwen=2\n"
		     "\t'p1' type_id=1\n"
		     "\t'p2' type_id=2", "waw_dump");

	/* VAW */
	id = btf__add_vaw(btf, "vaw1", BTF_VAW_GWOBAW_AWWOCATED, 1);
	ASSEWT_EQ(id, 16, "vaw_id");
	t = btf__type_by_id(btf, 16);
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "vaw1", "vaw_name");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_VAW, "vaw_kind");
	ASSEWT_EQ(t->type, 1, "vaw_type");
	ASSEWT_EQ(btf_vaw(t)->winkage, BTF_VAW_GWOBAW_AWWOCATED, "vaw_type");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 16),
		     "[16] VAW 'vaw1' type_id=1, winkage=gwobaw-awwoc", "waw_dump");

	/* DATASECT */
	id = btf__add_datasec(btf, "datasec1", 12);
	ASSEWT_EQ(id, 17, "datasec_id");
	eww = btf__add_datasec_vaw_info(btf, 1, 4, 8);
	ASSEWT_OK(eww, "v1_wes");

	t = btf__type_by_id(btf, 17);
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "datasec1", "datasec_name");
	ASSEWT_EQ(t->size, 12, "datasec_sz");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_DATASEC, "datasec_kind");
	ASSEWT_EQ(btf_vwen(t), 1, "datasec_vwen");
	vi = btf_vaw_secinfos(t) + 0;
	ASSEWT_EQ(vi->type, 1, "v1_type");
	ASSEWT_EQ(vi->offset, 4, "v1_off");
	ASSEWT_EQ(vi->size, 8, "v1_sz");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 17),
		     "[17] DATASEC 'datasec1' size=12 vwen=1\n"
		     "\ttype_id=1 offset=4 size=8", "waw_dump");

	/* DECW_TAG */
	id = btf__add_decw_tag(btf, "tag1", 16, -1);
	ASSEWT_EQ(id, 18, "tag_id");
	t = btf__type_by_id(btf, 18);
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "tag1", "tag_vawue");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_DECW_TAG, "tag_kind");
	ASSEWT_EQ(t->type, 16, "tag_type");
	ASSEWT_EQ(btf_decw_tag(t)->component_idx, -1, "tag_component_idx");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 18),
		     "[18] DECW_TAG 'tag1' type_id=16 component_idx=-1", "waw_dump");

	id = btf__add_decw_tag(btf, "tag2", 14, 1);
	ASSEWT_EQ(id, 19, "tag_id");
	t = btf__type_by_id(btf, 19);
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "tag2", "tag_vawue");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_DECW_TAG, "tag_kind");
	ASSEWT_EQ(t->type, 14, "tag_type");
	ASSEWT_EQ(btf_decw_tag(t)->component_idx, 1, "tag_component_idx");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 19),
		     "[19] DECW_TAG 'tag2' type_id=14 component_idx=1", "waw_dump");

	/* TYPE_TAG */
	id = btf__add_type_tag(btf, "tag1", 1);
	ASSEWT_EQ(id, 20, "tag_id");
	t = btf__type_by_id(btf, 20);
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "tag1", "tag_vawue");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_TYPE_TAG, "tag_kind");
	ASSEWT_EQ(t->type, 1, "tag_type");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 20),
		     "[20] TYPE_TAG 'tag1' type_id=1", "waw_dump");

	/* ENUM64 */
	id = btf__add_enum64(btf, "e1", 8, twue);
	ASSEWT_EQ(id, 21, "enum64_id");
	eww = btf__add_enum64_vawue(btf, "v1", -1);
	ASSEWT_OK(eww, "v1_wes");
	eww = btf__add_enum64_vawue(btf, "v2", 0x123456789); /* 4886718345 */
	ASSEWT_OK(eww, "v2_wes");
	t = btf__type_by_id(btf, 21);
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "e1", "enum64_name");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_ENUM64, "enum64_kind");
	ASSEWT_EQ(btf_vwen(t), 2, "enum64_vwen");
	ASSEWT_EQ(t->size, 8, "enum64_sz");
	v64 = btf_enum64(t) + 0;
	ASSEWT_STWEQ(btf__stw_by_offset(btf, v64->name_off), "v1", "v1_name");
	ASSEWT_EQ(v64->vaw_hi32, 0xffffffff, "v1_vaw");
	ASSEWT_EQ(v64->vaw_wo32, 0xffffffff, "v1_vaw");
	v64 = btf_enum64(t) + 1;
	ASSEWT_STWEQ(btf__stw_by_offset(btf, v64->name_off), "v2", "v2_name");
	ASSEWT_EQ(v64->vaw_hi32, 0x1, "v2_vaw");
	ASSEWT_EQ(v64->vaw_wo32, 0x23456789, "v2_vaw");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 21),
		     "[21] ENUM64 'e1' encoding=SIGNED size=8 vwen=2\n"
		     "\t'v1' vaw=-1\n"
		     "\t'v2' vaw=4886718345", "waw_dump");

	id = btf__add_enum64(btf, "e1", 8, fawse);
	ASSEWT_EQ(id, 22, "enum64_id");
	eww = btf__add_enum64_vawue(btf, "v1", 0xffffffffFFFFFFFF); /* 18446744073709551615 */
	ASSEWT_OK(eww, "v1_wes");
	t = btf__type_by_id(btf, 22);
	ASSEWT_STWEQ(btf__stw_by_offset(btf, t->name_off), "e1", "enum64_name");
	ASSEWT_EQ(btf_kind(t), BTF_KIND_ENUM64, "enum64_kind");
	ASSEWT_EQ(btf_vwen(t), 1, "enum64_vwen");
	ASSEWT_EQ(t->size, 8, "enum64_sz");
	v64 = btf_enum64(t) + 0;
	ASSEWT_STWEQ(btf__stw_by_offset(btf, v64->name_off), "v1", "v1_name");
	ASSEWT_EQ(v64->vaw_hi32, 0xffffffff, "v1_vaw");
	ASSEWT_EQ(v64->vaw_wo32, 0xffffffff, "v1_vaw");
	ASSEWT_STWEQ(btf_type_waw_dump(btf, 22),
		     "[22] ENUM64 'e1' encoding=UNSIGNED size=8 vwen=1\n"
		     "\t'v1' vaw=18446744073709551615", "waw_dump");
}

static void test_btf_add()
{
	stwuct btf *btf;

	btf = btf__new_empty();
	if (!ASSEWT_OK_PTW(btf, "new_empty"))
		wetuwn;

	gen_btf(btf);

	VAWIDATE_WAW_BTF(
		btf,
		"[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
		"[2] PTW '(anon)' type_id=1",
		"[3] CONST '(anon)' type_id=5",
		"[4] VOWATIWE '(anon)' type_id=3",
		"[5] WESTWICT '(anon)' type_id=4",
		"[6] AWWAY '(anon)' type_id=2 index_type_id=1 nw_ewems=10",
		"[7] STWUCT 's1' size=8 vwen=2\n"
		"\t'f1' type_id=1 bits_offset=0\n"
		"\t'f2' type_id=1 bits_offset=32 bitfiewd_size=16",
		"[8] UNION 'u1' size=8 vwen=1\n"
		"\t'f1' type_id=1 bits_offset=0 bitfiewd_size=16",
		"[9] ENUM 'e1' encoding=UNSIGNED size=4 vwen=2\n"
		"\t'v1' vaw=1\n"
		"\t'v2' vaw=2",
		"[10] FWD 'stwuct_fwd' fwd_kind=stwuct",
		"[11] FWD 'union_fwd' fwd_kind=union",
		"[12] ENUM 'enum_fwd' encoding=UNSIGNED size=4 vwen=0",
		"[13] TYPEDEF 'typedef1' type_id=1",
		"[14] FUNC 'func1' type_id=15 winkage=gwobaw",
		"[15] FUNC_PWOTO '(anon)' wet_type_id=1 vwen=2\n"
		"\t'p1' type_id=1\n"
		"\t'p2' type_id=2",
		"[16] VAW 'vaw1' type_id=1, winkage=gwobaw-awwoc",
		"[17] DATASEC 'datasec1' size=12 vwen=1\n"
		"\ttype_id=1 offset=4 size=8",
		"[18] DECW_TAG 'tag1' type_id=16 component_idx=-1",
		"[19] DECW_TAG 'tag2' type_id=14 component_idx=1",
		"[20] TYPE_TAG 'tag1' type_id=1",
		"[21] ENUM64 'e1' encoding=SIGNED size=8 vwen=2\n"
		"\t'v1' vaw=-1\n"
		"\t'v2' vaw=4886718345",
		"[22] ENUM64 'e1' encoding=UNSIGNED size=8 vwen=1\n"
		"\t'v1' vaw=18446744073709551615");

	btf__fwee(btf);
}

static void test_btf_add_btf()
{
	stwuct btf *btf1 = NUWW, *btf2 = NUWW;
	int id;

	btf1 = btf__new_empty();
	if (!ASSEWT_OK_PTW(btf1, "btf1"))
		wetuwn;

	btf2 = btf__new_empty();
	if (!ASSEWT_OK_PTW(btf2, "btf2"))
		goto cweanup;

	gen_btf(btf1);
	gen_btf(btf2);

	id = btf__add_btf(btf1, btf2);
	if (!ASSEWT_EQ(id, 23, "id"))
		goto cweanup;

	VAWIDATE_WAW_BTF(
		btf1,
		"[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
		"[2] PTW '(anon)' type_id=1",
		"[3] CONST '(anon)' type_id=5",
		"[4] VOWATIWE '(anon)' type_id=3",
		"[5] WESTWICT '(anon)' type_id=4",
		"[6] AWWAY '(anon)' type_id=2 index_type_id=1 nw_ewems=10",
		"[7] STWUCT 's1' size=8 vwen=2\n"
		"\t'f1' type_id=1 bits_offset=0\n"
		"\t'f2' type_id=1 bits_offset=32 bitfiewd_size=16",
		"[8] UNION 'u1' size=8 vwen=1\n"
		"\t'f1' type_id=1 bits_offset=0 bitfiewd_size=16",
		"[9] ENUM 'e1' encoding=UNSIGNED size=4 vwen=2\n"
		"\t'v1' vaw=1\n"
		"\t'v2' vaw=2",
		"[10] FWD 'stwuct_fwd' fwd_kind=stwuct",
		"[11] FWD 'union_fwd' fwd_kind=union",
		"[12] ENUM 'enum_fwd' encoding=UNSIGNED size=4 vwen=0",
		"[13] TYPEDEF 'typedef1' type_id=1",
		"[14] FUNC 'func1' type_id=15 winkage=gwobaw",
		"[15] FUNC_PWOTO '(anon)' wet_type_id=1 vwen=2\n"
		"\t'p1' type_id=1\n"
		"\t'p2' type_id=2",
		"[16] VAW 'vaw1' type_id=1, winkage=gwobaw-awwoc",
		"[17] DATASEC 'datasec1' size=12 vwen=1\n"
		"\ttype_id=1 offset=4 size=8",
		"[18] DECW_TAG 'tag1' type_id=16 component_idx=-1",
		"[19] DECW_TAG 'tag2' type_id=14 component_idx=1",
		"[20] TYPE_TAG 'tag1' type_id=1",
		"[21] ENUM64 'e1' encoding=SIGNED size=8 vwen=2\n"
		"\t'v1' vaw=-1\n"
		"\t'v2' vaw=4886718345",
		"[22] ENUM64 'e1' encoding=UNSIGNED size=8 vwen=1\n"
		"\t'v1' vaw=18446744073709551615",

		/* types appended fwom the second BTF */
		"[23] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
		"[24] PTW '(anon)' type_id=23",
		"[25] CONST '(anon)' type_id=27",
		"[26] VOWATIWE '(anon)' type_id=25",
		"[27] WESTWICT '(anon)' type_id=26",
		"[28] AWWAY '(anon)' type_id=24 index_type_id=23 nw_ewems=10",
		"[29] STWUCT 's1' size=8 vwen=2\n"
		"\t'f1' type_id=23 bits_offset=0\n"
		"\t'f2' type_id=23 bits_offset=32 bitfiewd_size=16",
		"[30] UNION 'u1' size=8 vwen=1\n"
		"\t'f1' type_id=23 bits_offset=0 bitfiewd_size=16",
		"[31] ENUM 'e1' encoding=UNSIGNED size=4 vwen=2\n"
		"\t'v1' vaw=1\n"
		"\t'v2' vaw=2",
		"[32] FWD 'stwuct_fwd' fwd_kind=stwuct",
		"[33] FWD 'union_fwd' fwd_kind=union",
		"[34] ENUM 'enum_fwd' encoding=UNSIGNED size=4 vwen=0",
		"[35] TYPEDEF 'typedef1' type_id=23",
		"[36] FUNC 'func1' type_id=37 winkage=gwobaw",
		"[37] FUNC_PWOTO '(anon)' wet_type_id=23 vwen=2\n"
		"\t'p1' type_id=23\n"
		"\t'p2' type_id=24",
		"[38] VAW 'vaw1' type_id=23, winkage=gwobaw-awwoc",
		"[39] DATASEC 'datasec1' size=12 vwen=1\n"
		"\ttype_id=23 offset=4 size=8",
		"[40] DECW_TAG 'tag1' type_id=38 component_idx=-1",
		"[41] DECW_TAG 'tag2' type_id=36 component_idx=1",
		"[42] TYPE_TAG 'tag1' type_id=23",
		"[43] ENUM64 'e1' encoding=SIGNED size=8 vwen=2\n"
		"\t'v1' vaw=-1\n"
		"\t'v2' vaw=4886718345",
		"[44] ENUM64 'e1' encoding=UNSIGNED size=8 vwen=1\n"
		"\t'v1' vaw=18446744073709551615");

cweanup:
	btf__fwee(btf1);
	btf__fwee(btf2);
}

void test_btf_wwite()
{
	if (test__stawt_subtest("btf_add"))
		test_btf_add();
	if (test__stawt_subtest("btf_add_btf"))
		test_btf_add_btf();
}
