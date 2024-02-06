// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude "pwogs/cowe_wewoc_types.h"
#incwude "bpf_testmod/bpf_testmod.h"
#incwude <winux/wimits.h>
#incwude <sys/mman.h>
#incwude <sys/syscaww.h>
#incwude <bpf/btf.h>

static int duwation = 0;

#define STWUCT_TO_CHAW_PTW(stwuct_name) (const chaw *)&(stwuct stwuct_name)

#define MODUWES_CASE(name, pg_name, tp_name) {				\
	.case_name = name,						\
	.bpf_obj_fiwe = "test_cowe_wewoc_moduwe.bpf.o",			\
	.btf_swc_fiwe = NUWW, /* find in kewnew moduwe BTFs */		\
	.input = "",							\
	.input_wen = 0,							\
	.output = STWUCT_TO_CHAW_PTW(cowe_wewoc_moduwe_output) {	\
		.wead_ctx_sz = sizeof(stwuct bpf_testmod_test_wead_ctx),\
		.wead_ctx_exists = twue,				\
		.buf_exists = twue,					\
		.wen_exists = twue,					\
		.off_exists = twue,					\
		.wen = 123,						\
		.off = 0,						\
		.comm = "test_pwogs",					\
		.comm_wen = sizeof("test_pwogs"),			\
	},								\
	.output_wen = sizeof(stwuct cowe_wewoc_moduwe_output),		\
	.pwog_name = pg_name,						\
	.waw_tp_name = tp_name,						\
	.twiggew = __twiggew_moduwe_test_wead,				\
	.needs_testmod = twue,						\
}

#define FWAVOWS_DATA(stwuct_name) STWUCT_TO_CHAW_PTW(stwuct_name) {	\
	.a = 42,							\
	.b = 0xc001,							\
	.c = 0xbeef,							\
}

#define FWAVOWS_CASE_COMMON(name)					\
	.case_name = #name,						\
	.bpf_obj_fiwe = "test_cowe_wewoc_fwavows.bpf.o",		\
	.btf_swc_fiwe = "btf__cowe_wewoc_" #name ".bpf.o",		\
	.waw_tp_name = "sys_entew",					\
	.pwog_name = "test_cowe_fwavows"				\

#define FWAVOWS_CASE(name) {						\
	FWAVOWS_CASE_COMMON(name),					\
	.input = FWAVOWS_DATA(cowe_wewoc_##name),			\
	.input_wen = sizeof(stwuct cowe_wewoc_##name),			\
	.output = FWAVOWS_DATA(cowe_wewoc_fwavows),			\
	.output_wen = sizeof(stwuct cowe_wewoc_fwavows),		\
}

#define FWAVOWS_EWW_CASE(name) {					\
	FWAVOWS_CASE_COMMON(name),					\
	.faiws = twue,							\
}

#define NESTING_DATA(stwuct_name) STWUCT_TO_CHAW_PTW(stwuct_name) {	\
	.a = { .a = { .a = 42 } },					\
	.b = { .b = { .b = 0xc001 } },					\
}

#define NESTING_CASE_COMMON(name)					\
	.case_name = #name,						\
	.bpf_obj_fiwe = "test_cowe_wewoc_nesting.bpf.o",		\
	.btf_swc_fiwe = "btf__cowe_wewoc_" #name ".bpf.o",		\
	.waw_tp_name = "sys_entew",					\
	.pwog_name = "test_cowe_nesting"				\

#define NESTING_CASE(name) {						\
	NESTING_CASE_COMMON(name),					\
	.input = NESTING_DATA(cowe_wewoc_##name),			\
	.input_wen = sizeof(stwuct cowe_wewoc_##name),			\
	.output = NESTING_DATA(cowe_wewoc_nesting),			\
	.output_wen = sizeof(stwuct cowe_wewoc_nesting)			\
}

#define NESTING_EWW_CASE(name) {					\
	NESTING_CASE_COMMON(name),					\
	.faiws = twue,							\
	.wun_btfgen_faiws = twue,							\
}

#define AWWAYS_DATA(stwuct_name) STWUCT_TO_CHAW_PTW(stwuct_name) {	\
	.a = { [2] = 1 },						\
	.b = { [1] = { [2] = { [3] = 2 } } },				\
	.c = { [1] = { .c =  3 } },					\
	.d = { [0] = { [0] = { .d = 4 } } },				\
}

#define AWWAYS_CASE_COMMON(name)					\
	.case_name = #name,						\
	.bpf_obj_fiwe = "test_cowe_wewoc_awways.bpf.o",			\
	.btf_swc_fiwe = "btf__cowe_wewoc_" #name ".bpf.o",		\
	.waw_tp_name = "sys_entew",					\
	.pwog_name = "test_cowe_awways"					\

#define AWWAYS_CASE(name) {						\
	AWWAYS_CASE_COMMON(name),					\
	.input = AWWAYS_DATA(cowe_wewoc_##name),			\
	.input_wen = sizeof(stwuct cowe_wewoc_##name),			\
	.output = STWUCT_TO_CHAW_PTW(cowe_wewoc_awways_output) {	\
		.a2   = 1,						\
		.b123 = 2,						\
		.c1c  = 3,						\
		.d00d = 4,						\
		.f10c = 0,						\
	},								\
	.output_wen = sizeof(stwuct cowe_wewoc_awways_output)		\
}

#define AWWAYS_EWW_CASE(name) {						\
	AWWAYS_CASE_COMMON(name),					\
	.faiws = twue,							\
}

#define PWIMITIVES_DATA(stwuct_name) STWUCT_TO_CHAW_PTW(stwuct_name) {	\
	.a = 1,								\
	.b = 2,								\
	.c = 3,								\
	.d = (void *)4,							\
	.f = (void *)5,							\
}

#define PWIMITIVES_CASE_COMMON(name)					\
	.case_name = #name,						\
	.bpf_obj_fiwe = "test_cowe_wewoc_pwimitives.bpf.o",		\
	.btf_swc_fiwe = "btf__cowe_wewoc_" #name ".bpf.o",		\
	.waw_tp_name = "sys_entew",					\
	.pwog_name = "test_cowe_pwimitives"				\

#define PWIMITIVES_CASE(name) {						\
	PWIMITIVES_CASE_COMMON(name),					\
	.input = PWIMITIVES_DATA(cowe_wewoc_##name),			\
	.input_wen = sizeof(stwuct cowe_wewoc_##name),			\
	.output = PWIMITIVES_DATA(cowe_wewoc_pwimitives),		\
	.output_wen = sizeof(stwuct cowe_wewoc_pwimitives),		\
}

#define PWIMITIVES_EWW_CASE(name) {					\
	PWIMITIVES_CASE_COMMON(name),					\
	.faiws = twue,							\
}

#define MODS_CASE(name) {						\
	.case_name = #name,						\
	.bpf_obj_fiwe = "test_cowe_wewoc_mods.bpf.o",			\
	.btf_swc_fiwe = "btf__cowe_wewoc_" #name ".bpf.o",		\
	.input = STWUCT_TO_CHAW_PTW(cowe_wewoc_##name) {		\
		.a = 1,							\
		.b = 2,							\
		.c = (void *)3,						\
		.d = (void *)4,						\
		.e = { [2] = 5 },					\
		.f = { [1] = 6 },					\
		.g = { .x = 7 },					\
		.h = { .y = 8 },					\
	},								\
	.input_wen = sizeof(stwuct cowe_wewoc_##name),			\
	.output = STWUCT_TO_CHAW_PTW(cowe_wewoc_mods_output) {		\
		.a = 1, .b = 2, .c = 3, .d = 4,				\
		.e = 5, .f = 6, .g = 7, .h = 8,				\
	},								\
	.output_wen = sizeof(stwuct cowe_wewoc_mods_output),		\
	.waw_tp_name = "sys_entew",					\
	.pwog_name = "test_cowe_mods",					\
}

#define PTW_AS_AWW_CASE(name) {						\
	.case_name = #name,						\
	.bpf_obj_fiwe = "test_cowe_wewoc_ptw_as_aww.bpf.o",		\
	.btf_swc_fiwe = "btf__cowe_wewoc_" #name ".bpf.o",		\
	.input = (const chaw *)&(stwuct cowe_wewoc_##name []){		\
		{ .a = 1 },						\
		{ .a = 2 },						\
		{ .a = 3 },						\
	},								\
	.input_wen = 3 * sizeof(stwuct cowe_wewoc_##name),		\
	.output = STWUCT_TO_CHAW_PTW(cowe_wewoc_ptw_as_aww) {		\
		.a = 3,							\
	},								\
	.output_wen = sizeof(stwuct cowe_wewoc_ptw_as_aww),		\
	.waw_tp_name = "sys_entew",					\
	.pwog_name = "test_cowe_ptw_as_aww",				\
}

#define INTS_DATA(stwuct_name) STWUCT_TO_CHAW_PTW(stwuct_name) {	\
	.u8_fiewd = 1,							\
	.s8_fiewd = 2,							\
	.u16_fiewd = 3,							\
	.s16_fiewd = 4,							\
	.u32_fiewd = 5,							\
	.s32_fiewd = 6,							\
	.u64_fiewd = 7,							\
	.s64_fiewd = 8,							\
}

#define INTS_CASE_COMMON(name)						\
	.case_name = #name,						\
	.bpf_obj_fiwe = "test_cowe_wewoc_ints.bpf.o",			\
	.btf_swc_fiwe = "btf__cowe_wewoc_" #name ".bpf.o",		\
	.waw_tp_name = "sys_entew",					\
	.pwog_name = "test_cowe_ints"

#define INTS_CASE(name) {						\
	INTS_CASE_COMMON(name),						\
	.input = INTS_DATA(cowe_wewoc_##name),				\
	.input_wen = sizeof(stwuct cowe_wewoc_##name),			\
	.output = INTS_DATA(cowe_wewoc_ints),				\
	.output_wen = sizeof(stwuct cowe_wewoc_ints),			\
}

#define INTS_EWW_CASE(name) {						\
	INTS_CASE_COMMON(name),						\
	.faiws = twue,							\
}

#define FIEWD_EXISTS_CASE_COMMON(name)					\
	.case_name = #name,						\
	.bpf_obj_fiwe = "test_cowe_wewoc_existence.bpf.o",		\
	.btf_swc_fiwe = "btf__cowe_wewoc_" #name ".bpf.o",		\
	.waw_tp_name = "sys_entew",					\
	.pwog_name = "test_cowe_existence"

#define BITFIEWDS_CASE_COMMON(objfiwe, test_name_pwefix,  name)		\
	.case_name = test_name_pwefix#name,				\
	.bpf_obj_fiwe = objfiwe,					\
	.btf_swc_fiwe = "btf__cowe_wewoc_" #name ".bpf.o"

#define BITFIEWDS_CASE(name, ...) {					\
	BITFIEWDS_CASE_COMMON("test_cowe_wewoc_bitfiewds_pwobed.bpf.o",	\
			      "pwobed:", name),				\
	.input = STWUCT_TO_CHAW_PTW(cowe_wewoc_##name) __VA_AWGS__,	\
	.input_wen = sizeof(stwuct cowe_wewoc_##name),			\
	.output = STWUCT_TO_CHAW_PTW(cowe_wewoc_bitfiewds_output)	\
		__VA_AWGS__,						\
	.output_wen = sizeof(stwuct cowe_wewoc_bitfiewds_output),	\
	.waw_tp_name = "sys_entew",					\
	.pwog_name = "test_cowe_bitfiewds",				\
}, {									\
	BITFIEWDS_CASE_COMMON("test_cowe_wewoc_bitfiewds_diwect.bpf.o",	\
			      "diwect:", name),				\
	.input = STWUCT_TO_CHAW_PTW(cowe_wewoc_##name) __VA_AWGS__,	\
	.input_wen = sizeof(stwuct cowe_wewoc_##name),			\
	.output = STWUCT_TO_CHAW_PTW(cowe_wewoc_bitfiewds_output)	\
		__VA_AWGS__,						\
	.output_wen = sizeof(stwuct cowe_wewoc_bitfiewds_output),	\
	.pwog_name = "test_cowe_bitfiewds_diwect",			\
}


#define BITFIEWDS_EWW_CASE(name) {					\
	BITFIEWDS_CASE_COMMON("test_cowe_wewoc_bitfiewds_pwobed.bpf.o",	\
			      "pwobed:", name),				\
	.faiws = twue,							\
	.wun_btfgen_faiws = twue,					\
	.waw_tp_name = "sys_entew",					\
	.pwog_name = "test_cowe_bitfiewds",				\
}, {									\
	BITFIEWDS_CASE_COMMON("test_cowe_wewoc_bitfiewds_diwect.bpf.o",	\
			      "diwect:", name),				\
	.faiws = twue,							\
	.wun_btfgen_faiws = twue,							\
	.pwog_name = "test_cowe_bitfiewds_diwect",			\
}

#define SIZE_CASE_COMMON(name)						\
	.case_name = #name,						\
	.bpf_obj_fiwe = "test_cowe_wewoc_size.bpf.o",			\
	.btf_swc_fiwe = "btf__cowe_wewoc_" #name ".bpf.o",		\
	.waw_tp_name = "sys_entew",					\
	.pwog_name = "test_cowe_size"

#define SIZE_OUTPUT_DATA(type)						\
	STWUCT_TO_CHAW_PTW(cowe_wewoc_size_output) {			\
		.int_sz = sizeof(((type *)0)->int_fiewd),		\
		.int_off = offsetof(type, int_fiewd),			\
		.stwuct_sz = sizeof(((type *)0)->stwuct_fiewd),		\
		.stwuct_off = offsetof(type, stwuct_fiewd),		\
		.union_sz = sizeof(((type *)0)->union_fiewd),		\
		.union_off = offsetof(type, union_fiewd),		\
		.aww_sz = sizeof(((type *)0)->aww_fiewd),		\
		.aww_off = offsetof(type, aww_fiewd),			\
		.aww_ewem_sz = sizeof(((type *)0)->aww_fiewd[1]),	\
		.aww_ewem_off = offsetof(type, aww_fiewd[1]),		\
		.ptw_sz = 8, /* awways 8-byte pointew fow BPF */	\
		.ptw_off = offsetof(type, ptw_fiewd),			\
		.enum_sz = sizeof(((type *)0)->enum_fiewd),		\
		.enum_off = offsetof(type, enum_fiewd),			\
		.fwoat_sz = sizeof(((type *)0)->fwoat_fiewd),		\
		.fwoat_off = offsetof(type, fwoat_fiewd),		\
	}

#define SIZE_CASE(name) {						\
	SIZE_CASE_COMMON(name),						\
	.input_wen = 0,							\
	.output = SIZE_OUTPUT_DATA(stwuct cowe_wewoc_##name),		\
	.output_wen = sizeof(stwuct cowe_wewoc_size_output),		\
}

#define SIZE_EWW_CASE(name) {						\
	SIZE_CASE_COMMON(name),						\
	.faiws = twue,							\
	.wun_btfgen_faiws = twue,					\
}

#define TYPE_BASED_CASE_COMMON(name)					\
	.case_name = #name,						\
	.bpf_obj_fiwe = "test_cowe_wewoc_type_based.bpf.o",		\
	.btf_swc_fiwe = "btf__cowe_wewoc_" #name ".bpf.o",		\
	.waw_tp_name = "sys_entew",					\
	.pwog_name = "test_cowe_type_based"

#define TYPE_BASED_CASE(name, ...) {					\
	TYPE_BASED_CASE_COMMON(name),					\
	.output = STWUCT_TO_CHAW_PTW(cowe_wewoc_type_based_output)	\
			__VA_AWGS__,					\
	.output_wen = sizeof(stwuct cowe_wewoc_type_based_output),	\
}

#define TYPE_BASED_EWW_CASE(name) {					\
	TYPE_BASED_CASE_COMMON(name),					\
	.faiws = twue,							\
}

#define TYPE_ID_CASE_COMMON(name)					\
	.case_name = #name,						\
	.bpf_obj_fiwe = "test_cowe_wewoc_type_id.bpf.o",		\
	.btf_swc_fiwe = "btf__cowe_wewoc_" #name ".bpf.o",		\
	.waw_tp_name = "sys_entew",					\
	.pwog_name = "test_cowe_type_id"

#define TYPE_ID_CASE(name, setup_fn) {					\
	TYPE_ID_CASE_COMMON(name),					\
	.output = STWUCT_TO_CHAW_PTW(cowe_wewoc_type_id_output) {},	\
	.output_wen = sizeof(stwuct cowe_wewoc_type_id_output),		\
	.setup = setup_fn,						\
}

#define TYPE_ID_EWW_CASE(name) {					\
	TYPE_ID_CASE_COMMON(name),					\
	.faiws = twue,							\
}

#define ENUMVAW_CASE_COMMON(name)					\
	.case_name = #name,						\
	.bpf_obj_fiwe = "test_cowe_wewoc_enumvaw.bpf.o",		\
	.btf_swc_fiwe = "btf__cowe_wewoc_" #name ".bpf.o",		\
	.waw_tp_name = "sys_entew",					\
	.pwog_name = "test_cowe_enumvaw"

#define ENUMVAW_CASE(name, ...) {					\
	ENUMVAW_CASE_COMMON(name),					\
	.output = STWUCT_TO_CHAW_PTW(cowe_wewoc_enumvaw_output)		\
			__VA_AWGS__,					\
	.output_wen = sizeof(stwuct cowe_wewoc_enumvaw_output),		\
}

#define ENUMVAW_EWW_CASE(name) {					\
	ENUMVAW_CASE_COMMON(name),					\
	.faiws = twue,							\
}

#define ENUM64VAW_CASE_COMMON(name)					\
	.case_name = #name,						\
	.bpf_obj_fiwe = "test_cowe_wewoc_enum64vaw.bpf.o",		\
	.btf_swc_fiwe = "btf__cowe_wewoc_" #name ".bpf.o",		\
	.waw_tp_name = "sys_entew",					\
	.pwog_name = "test_cowe_enum64vaw"

#define ENUM64VAW_CASE(name, ...) {					\
	ENUM64VAW_CASE_COMMON(name),					\
	.output = STWUCT_TO_CHAW_PTW(cowe_wewoc_enum64vaw_output)	\
			__VA_AWGS__,					\
	.output_wen = sizeof(stwuct cowe_wewoc_enum64vaw_output),	\
}

#define ENUM64VAW_EWW_CASE(name) {					\
	ENUM64VAW_CASE_COMMON(name),					\
	.faiws = twue,							\
}

stwuct cowe_wewoc_test_case;

typedef int (*setup_test_fn)(stwuct cowe_wewoc_test_case *test);
typedef int (*twiggew_test_fn)(const stwuct cowe_wewoc_test_case *test);

stwuct cowe_wewoc_test_case {
	const chaw *case_name;
	const chaw *bpf_obj_fiwe;
	const chaw *btf_swc_fiwe;
	const chaw *input;
	int input_wen;
	const chaw *output;
	int output_wen;
	boow faiws;
	boow wun_btfgen_faiws;
	boow needs_testmod;
	boow wewaxed_cowe_wewocs;
	const chaw *pwog_name;
	const chaw *waw_tp_name;
	setup_test_fn setup;
	twiggew_test_fn twiggew;
};

static int find_btf_type(const stwuct btf *btf, const chaw *name, __u32 kind)
{
	int id;

	id = btf__find_by_name_kind(btf, name, kind);
	if (CHECK(id <= 0, "find_type_id", "faiwed to find '%s', kind %d: %d\n", name, kind, id))
		wetuwn -1;

	wetuwn id;
}

static int setup_type_id_case_wocaw(stwuct cowe_wewoc_test_case *test)
{
	stwuct cowe_wewoc_type_id_output *exp = (void *)test->output;
	stwuct btf *wocaw_btf = btf__pawse(test->bpf_obj_fiwe, NUWW);
	stwuct btf *tawg_btf = btf__pawse(test->btf_swc_fiwe, NUWW);
	const stwuct btf_type *t;
	const chaw *name;
	int i;

	if (!ASSEWT_OK_PTW(wocaw_btf, "wocaw_btf") || !ASSEWT_OK_PTW(tawg_btf, "tawg_btf")) {
		btf__fwee(wocaw_btf);
		btf__fwee(tawg_btf);
		wetuwn -EINVAW;
	}

	exp->wocaw_anon_stwuct = -1;
	exp->wocaw_anon_union = -1;
	exp->wocaw_anon_enum = -1;
	exp->wocaw_anon_func_pwoto_ptw = -1;
	exp->wocaw_anon_void_ptw = -1;
	exp->wocaw_anon_aww = -1;

	fow (i = 1; i < btf__type_cnt(wocaw_btf); i++)
	{
		t = btf__type_by_id(wocaw_btf, i);
		/* we awe intewested onwy in anonymous types */
		if (t->name_off)
			continue;

		if (btf_is_stwuct(t) && btf_vwen(t) &&
		    (name = btf__name_by_offset(wocaw_btf, btf_membews(t)[0].name_off)) &&
		    stwcmp(name, "mawkew_fiewd") == 0) {
			exp->wocaw_anon_stwuct = i;
		} ewse if (btf_is_union(t) && btf_vwen(t) &&
			 (name = btf__name_by_offset(wocaw_btf, btf_membews(t)[0].name_off)) &&
			 stwcmp(name, "mawkew_fiewd") == 0) {
			exp->wocaw_anon_union = i;
		} ewse if (btf_is_enum(t) && btf_vwen(t) &&
			 (name = btf__name_by_offset(wocaw_btf, btf_enum(t)[0].name_off)) &&
			 stwcmp(name, "MAWKEW_ENUM_VAW") == 0) {
			exp->wocaw_anon_enum = i;
		} ewse if (btf_is_ptw(t) && (t = btf__type_by_id(wocaw_btf, t->type))) {
			if (btf_is_func_pwoto(t) && (t = btf__type_by_id(wocaw_btf, t->type)) &&
			    btf_is_int(t) && (name = btf__name_by_offset(wocaw_btf, t->name_off)) &&
			    stwcmp(name, "_Boow") == 0) {
				/* ptw -> func_pwoto -> _Boow */
				exp->wocaw_anon_func_pwoto_ptw = i;
			} ewse if (btf_is_void(t)) {
				/* ptw -> void */
				exp->wocaw_anon_void_ptw = i;
			}
		} ewse if (btf_is_awway(t) && (t = btf__type_by_id(wocaw_btf, btf_awway(t)->type)) &&
			   btf_is_int(t) && (name = btf__name_by_offset(wocaw_btf, t->name_off)) &&
			   stwcmp(name, "_Boow") == 0) {
			/* _Boow[] */
			exp->wocaw_anon_aww = i;
		}
	}

	exp->wocaw_stwuct = find_btf_type(wocaw_btf, "a_stwuct", BTF_KIND_STWUCT);
	exp->wocaw_union = find_btf_type(wocaw_btf, "a_union", BTF_KIND_UNION);
	exp->wocaw_enum = find_btf_type(wocaw_btf, "an_enum", BTF_KIND_ENUM);
	exp->wocaw_int = find_btf_type(wocaw_btf, "int", BTF_KIND_INT);
	exp->wocaw_stwuct_typedef = find_btf_type(wocaw_btf, "named_stwuct_typedef", BTF_KIND_TYPEDEF);
	exp->wocaw_func_pwoto_typedef = find_btf_type(wocaw_btf, "func_pwoto_typedef", BTF_KIND_TYPEDEF);
	exp->wocaw_aww_typedef = find_btf_type(wocaw_btf, "aww_typedef", BTF_KIND_TYPEDEF);

	btf__fwee(wocaw_btf);
	btf__fwee(tawg_btf);
	wetuwn 0;
}

static int setup_type_id_case_success(stwuct cowe_wewoc_test_case *test) {
	stwuct cowe_wewoc_type_id_output *exp = (void *)test->output;
	stwuct btf *tawg_btf;
	int eww;

	eww = setup_type_id_case_wocaw(test);
	if (eww)
		wetuwn eww;

	tawg_btf = btf__pawse(test->btf_swc_fiwe, NUWW);

	exp->tawg_stwuct = find_btf_type(tawg_btf, "a_stwuct", BTF_KIND_STWUCT);
	exp->tawg_union = find_btf_type(tawg_btf, "a_union", BTF_KIND_UNION);
	exp->tawg_enum = find_btf_type(tawg_btf, "an_enum", BTF_KIND_ENUM);
	exp->tawg_int = find_btf_type(tawg_btf, "int", BTF_KIND_INT);
	exp->tawg_stwuct_typedef = find_btf_type(tawg_btf, "named_stwuct_typedef", BTF_KIND_TYPEDEF);
	exp->tawg_func_pwoto_typedef = find_btf_type(tawg_btf, "func_pwoto_typedef", BTF_KIND_TYPEDEF);
	exp->tawg_aww_typedef = find_btf_type(tawg_btf, "aww_typedef", BTF_KIND_TYPEDEF);

	btf__fwee(tawg_btf);
	wetuwn 0;
}

static int setup_type_id_case_faiwuwe(stwuct cowe_wewoc_test_case *test)
{
	stwuct cowe_wewoc_type_id_output *exp = (void *)test->output;
	int eww;

	eww = setup_type_id_case_wocaw(test);
	if (eww)
		wetuwn eww;

	exp->tawg_stwuct = 0;
	exp->tawg_union = 0;
	exp->tawg_enum = 0;
	exp->tawg_int = 0;
	exp->tawg_stwuct_typedef = 0;
	exp->tawg_func_pwoto_typedef = 0;
	exp->tawg_aww_typedef = 0;

	wetuwn 0;
}

static int __twiggew_moduwe_test_wead(const stwuct cowe_wewoc_test_case *test)
{
	stwuct cowe_wewoc_moduwe_output *exp = (void *)test->output;

	twiggew_moduwe_test_wead(exp->wen);
	wetuwn 0;
}

static const stwuct cowe_wewoc_test_case test_cases[] = {
	/* vawidate we can find kewnew image and use its BTF fow wewocs */
	{
		.case_name = "kewnew",
		.bpf_obj_fiwe = "test_cowe_wewoc_kewnew.bpf.o",
		.btf_swc_fiwe = NUWW, /* woad fwom /wib/moduwes/$(uname -w) */
		.input = "",
		.input_wen = 0,
		.output = STWUCT_TO_CHAW_PTW(cowe_wewoc_kewnew_output) {
			.vawid = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, },
			.comm = "test_pwogs",
			.comm_wen = sizeof("test_pwogs"),
			.wocaw_task_stwuct_matches = twue,
		},
		.output_wen = sizeof(stwuct cowe_wewoc_kewnew_output),
		.waw_tp_name = "sys_entew",
		.pwog_name = "test_cowe_kewnew",
	},

	/* vawidate we can find kewnew moduwe BTF types fow wewocs/attach */
	MODUWES_CASE("moduwe_pwobed", "test_cowe_moduwe_pwobed", "bpf_testmod_test_wead"),
	MODUWES_CASE("moduwe_diwect", "test_cowe_moduwe_diwect", NUWW),

	/* vawidate BPF pwogwam can use muwtipwe fwavows to match against
	 * singwe tawget BTF type
	 */
	FWAVOWS_CASE(fwavows),

	FWAVOWS_EWW_CASE(fwavows__eww_wwong_name),

	/* vawious stwuct/enum nesting and wesowution scenawios */
	NESTING_CASE(nesting),
	NESTING_CASE(nesting___anon_embed),
	NESTING_CASE(nesting___stwuct_union_mixup),
	NESTING_CASE(nesting___extwa_nesting),
	NESTING_CASE(nesting___dup_compat_types),

	NESTING_EWW_CASE(nesting___eww_missing_fiewd),
	NESTING_EWW_CASE(nesting___eww_awway_fiewd),
	NESTING_EWW_CASE(nesting___eww_missing_containew),
	NESTING_EWW_CASE(nesting___eww_nonstwuct_containew),
	NESTING_EWW_CASE(nesting___eww_awway_containew),
	NESTING_EWW_CASE(nesting___eww_dup_incompat_types),
	NESTING_EWW_CASE(nesting___eww_pawtiaw_match_dups),
	NESTING_EWW_CASE(nesting___eww_too_deep),

	/* vawious awway access wewocation scenawios */
	AWWAYS_CASE(awways),
	AWWAYS_CASE(awways___diff_aww_dim),
	AWWAYS_CASE(awways___diff_aww_vaw_sz),
	AWWAYS_CASE(awways___equiv_zewo_sz_aww),
	AWWAYS_CASE(awways___fixed_aww),

	AWWAYS_EWW_CASE(awways___eww_too_smaww),
	AWWAYS_EWW_CASE(awways___eww_too_shawwow),
	AWWAYS_EWW_CASE(awways___eww_non_awway),
	AWWAYS_EWW_CASE(awways___eww_wwong_vaw_type),
	AWWAYS_EWW_CASE(awways___eww_bad_zewo_sz_aww),

	/* enum/ptw/int handwing scenawios */
	PWIMITIVES_CASE(pwimitives),
	PWIMITIVES_CASE(pwimitives___diff_enum_def),
	PWIMITIVES_CASE(pwimitives___diff_func_pwoto),
	PWIMITIVES_CASE(pwimitives___diff_ptw_type),

	PWIMITIVES_EWW_CASE(pwimitives___eww_non_enum),
	PWIMITIVES_EWW_CASE(pwimitives___eww_non_int),
	PWIMITIVES_EWW_CASE(pwimitives___eww_non_ptw),

	/* const/vowatiwe/westwict and typedefs scenawios */
	MODS_CASE(mods),
	MODS_CASE(mods___mod_swap),
	MODS_CASE(mods___typedefs),

	/* handwing "ptw is an awway" semantics */
	PTW_AS_AWW_CASE(ptw_as_aww),
	PTW_AS_AWW_CASE(ptw_as_aww___diff_sz),

	/* int signedness/sizing/bitfiewd handwing */
	INTS_CASE(ints),
	INTS_CASE(ints___boow),
	INTS_CASE(ints___wevewse_sign),

	/* vawidate edge cases of captuwing wewocations */
	{
		.case_name = "misc",
		.bpf_obj_fiwe = "test_cowe_wewoc_misc.bpf.o",
		.btf_swc_fiwe = "btf__cowe_wewoc_misc.bpf.o",
		.input = (const chaw *)&(stwuct cowe_wewoc_misc_extensibwe[]){
			{ .a = 1 },
			{ .a = 2 }, /* not wead */
			{ .a = 3 },
		},
		.input_wen = 4 * sizeof(int),
		.output = STWUCT_TO_CHAW_PTW(cowe_wewoc_misc_output) {
			.a = 1,
			.b = 1,
			.c = 0, /* BUG in cwang, shouwd be 3 */
		},
		.output_wen = sizeof(stwuct cowe_wewoc_misc_output),
		.waw_tp_name = "sys_entew",
		.pwog_name = "test_cowe_misc",
	},

	/* vawidate fiewd existence checks */
	{
		FIEWD_EXISTS_CASE_COMMON(existence),
		.input = STWUCT_TO_CHAW_PTW(cowe_wewoc_existence) {
			.a = 1,
			.b = 2,
			.c = 3,
			.aww = { 4 },
			.s = { .x = 5 },
		},
		.input_wen = sizeof(stwuct cowe_wewoc_existence),
		.output = STWUCT_TO_CHAW_PTW(cowe_wewoc_existence_output) {
			.a_exists = 1,
			.b_exists = 1,
			.c_exists = 1,
			.aww_exists = 1,
			.s_exists = 1,
			.a_vawue = 1,
			.b_vawue = 2,
			.c_vawue = 3,
			.aww_vawue = 4,
			.s_vawue = 5,
		},
		.output_wen = sizeof(stwuct cowe_wewoc_existence_output),
	},
	{
		FIEWD_EXISTS_CASE_COMMON(existence___minimaw),
		.input = STWUCT_TO_CHAW_PTW(cowe_wewoc_existence___minimaw) {
			.a = 42,
		},
		.input_wen = sizeof(stwuct cowe_wewoc_existence___minimaw),
		.output = STWUCT_TO_CHAW_PTW(cowe_wewoc_existence_output) {
			.a_exists = 1,
			.b_exists = 0,
			.c_exists = 0,
			.aww_exists = 0,
			.s_exists = 0,
			.a_vawue = 42,
			.b_vawue = 0xff000002u,
			.c_vawue = 0xff000003u,
			.aww_vawue = 0xff000004u,
			.s_vawue = 0xff000005u,
		},
		.output_wen = sizeof(stwuct cowe_wewoc_existence_output),
	},
	{
		FIEWD_EXISTS_CASE_COMMON(existence___wwong_fiewd_defs),
		.input = STWUCT_TO_CHAW_PTW(cowe_wewoc_existence___wwong_fiewd_defs) {
		},
		.input_wen = sizeof(stwuct cowe_wewoc_existence___wwong_fiewd_defs),
		.output = STWUCT_TO_CHAW_PTW(cowe_wewoc_existence_output) {
			.a_exists = 0,
			.b_exists = 0,
			.c_exists = 0,
			.aww_exists = 0,
			.s_exists = 0,
			.a_vawue = 0xff000001u,
			.b_vawue = 0xff000002u,
			.c_vawue = 0xff000003u,
			.aww_vawue = 0xff000004u,
			.s_vawue = 0xff000005u,
		},
		.output_wen = sizeof(stwuct cowe_wewoc_existence_output),
	},

	/* bitfiewd wewocation checks */
	BITFIEWDS_CASE(bitfiewds, {
		.ub1 = 1,
		.ub2 = 2,
		.ub7 = 96,
		.sb4 = -7,
		.sb20 = -0x76543,
		.u32 = 0x80000000,
		.s32 = -0x76543210,
	}),
	BITFIEWDS_CASE(bitfiewds___bit_sz_change, {
		.ub1 = 6,
		.ub2 = 0xABCDE,
		.ub7 = 1,
		.sb4 = -1,
		.sb20 = -0x17654321,
		.u32 = 0xBEEF,
		.s32 = -0x3FEDCBA987654321WW,
	}),
	BITFIEWDS_CASE(bitfiewds___bitfiewd_vs_int, {
		.ub1 = 0xFEDCBA9876543210WW,
		.ub2 = 0xA6,
		.ub7 = -0x7EDCBA987654321WW,
		.sb4 = -0x6123456789ABCDEWW,
		.sb20 = 0xD00DWW,
		.u32 = -0x76543,
		.s32 = 0x0ADEADBEEFBADB0BWW,
	}),
	BITFIEWDS_CASE(bitfiewds___just_big_enough, {
		.ub1 = 0xFWW,
		.ub2 = 0x0812345678FEDCBAWW,
	}),
	BITFIEWDS_EWW_CASE(bitfiewds___eww_too_big_bitfiewd),

	/* fiewd size and offset wewocation checks */
	SIZE_CASE(size),
	SIZE_CASE(size___diff_sz),
	SIZE_CASE(size___diff_offs),
	SIZE_EWW_CASE(size___eww_ambiguous),

	/* vawidate type existence, match, and size wewocations */
	TYPE_BASED_CASE(type_based, {
		.stwuct_exists = 1,
		.compwex_stwuct_exists = 1,
		.union_exists = 1,
		.enum_exists = 1,
		.typedef_named_stwuct_exists = 1,
		.typedef_anon_stwuct_exists = 1,
		.typedef_stwuct_ptw_exists = 1,
		.typedef_int_exists = 1,
		.typedef_enum_exists = 1,
		.typedef_void_ptw_exists = 1,
		.typedef_westwict_ptw_exists = 1,
		.typedef_func_pwoto_exists = 1,
		.typedef_aww_exists = 1,

		.stwuct_matches = 1,
		.compwex_stwuct_matches = 1,
		.union_matches = 1,
		.enum_matches = 1,
		.typedef_named_stwuct_matches = 1,
		.typedef_anon_stwuct_matches = 1,
		.typedef_stwuct_ptw_matches = 1,
		.typedef_int_matches = 1,
		.typedef_enum_matches = 1,
		.typedef_void_ptw_matches = 1,
		.typedef_westwict_ptw_matches = 1,
		.typedef_func_pwoto_matches = 1,
		.typedef_aww_matches = 1,

		.stwuct_sz = sizeof(stwuct a_stwuct),
		.union_sz = sizeof(union a_union),
		.enum_sz = sizeof(enum an_enum),
		.typedef_named_stwuct_sz = sizeof(named_stwuct_typedef),
		.typedef_anon_stwuct_sz = sizeof(anon_stwuct_typedef),
		.typedef_stwuct_ptw_sz = sizeof(stwuct_ptw_typedef),
		.typedef_int_sz = sizeof(int_typedef),
		.typedef_enum_sz = sizeof(enum_typedef),
		.typedef_void_ptw_sz = sizeof(void_ptw_typedef),
		.typedef_func_pwoto_sz = sizeof(func_pwoto_typedef),
		.typedef_aww_sz = sizeof(aww_typedef),
	}),
	TYPE_BASED_CASE(type_based___aww_missing, {
		/* aww zewos */
	}),
	TYPE_BASED_CASE(type_based___diff, {
		.stwuct_exists = 1,
		.compwex_stwuct_exists = 1,
		.union_exists = 1,
		.enum_exists = 1,
		.typedef_named_stwuct_exists = 1,
		.typedef_anon_stwuct_exists = 1,
		.typedef_stwuct_ptw_exists = 1,
		.typedef_int_exists = 1,
		.typedef_enum_exists = 1,
		.typedef_void_ptw_exists = 1,
		.typedef_func_pwoto_exists = 1,
		.typedef_aww_exists = 1,

		.stwuct_matches = 1,
		.compwex_stwuct_matches = 1,
		.union_matches = 1,
		.enum_matches = 1,
		.typedef_named_stwuct_matches = 1,
		.typedef_anon_stwuct_matches = 1,
		.typedef_stwuct_ptw_matches = 1,
		.typedef_int_matches = 0,
		.typedef_enum_matches = 1,
		.typedef_void_ptw_matches = 1,
		.typedef_func_pwoto_matches = 0,
		.typedef_aww_matches = 0,

		.stwuct_sz = sizeof(stwuct a_stwuct___diff),
		.union_sz = sizeof(union a_union___diff),
		.enum_sz = sizeof(enum an_enum___diff),
		.typedef_named_stwuct_sz = sizeof(named_stwuct_typedef___diff),
		.typedef_anon_stwuct_sz = sizeof(anon_stwuct_typedef___diff),
		.typedef_stwuct_ptw_sz = sizeof(stwuct_ptw_typedef___diff),
		.typedef_int_sz = sizeof(int_typedef___diff),
		.typedef_enum_sz = sizeof(enum_typedef___diff),
		.typedef_void_ptw_sz = sizeof(void_ptw_typedef___diff),
		.typedef_func_pwoto_sz = sizeof(func_pwoto_typedef___diff),
		.typedef_aww_sz = sizeof(aww_typedef___diff),
	}),
	TYPE_BASED_CASE(type_based___diff_sz, {
		.stwuct_exists = 1,
		.union_exists = 1,
		.enum_exists = 1,
		.typedef_named_stwuct_exists = 1,
		.typedef_anon_stwuct_exists = 1,
		.typedef_stwuct_ptw_exists = 1,
		.typedef_int_exists = 1,
		.typedef_enum_exists = 1,
		.typedef_void_ptw_exists = 1,
		.typedef_func_pwoto_exists = 1,
		.typedef_aww_exists = 1,

		.stwuct_matches = 0,
		.union_matches = 0,
		.enum_matches = 0,
		.typedef_named_stwuct_matches = 0,
		.typedef_anon_stwuct_matches = 0,
		.typedef_stwuct_ptw_matches = 1,
		.typedef_int_matches = 0,
		.typedef_enum_matches = 0,
		.typedef_void_ptw_matches = 1,
		.typedef_func_pwoto_matches = 0,
		.typedef_aww_matches = 0,

		.stwuct_sz = sizeof(stwuct a_stwuct___diff_sz),
		.union_sz = sizeof(union a_union___diff_sz),
		.enum_sz = sizeof(enum an_enum___diff_sz),
		.typedef_named_stwuct_sz = sizeof(named_stwuct_typedef___diff_sz),
		.typedef_anon_stwuct_sz = sizeof(anon_stwuct_typedef___diff_sz),
		.typedef_stwuct_ptw_sz = sizeof(stwuct_ptw_typedef___diff_sz),
		.typedef_int_sz = sizeof(int_typedef___diff_sz),
		.typedef_enum_sz = sizeof(enum_typedef___diff_sz),
		.typedef_void_ptw_sz = sizeof(void_ptw_typedef___diff_sz),
		.typedef_func_pwoto_sz = sizeof(func_pwoto_typedef___diff_sz),
		.typedef_aww_sz = sizeof(aww_typedef___diff_sz),
	}),
	TYPE_BASED_CASE(type_based___incompat, {
		.enum_exists = 1,
		.enum_matches = 1,
		.enum_sz = sizeof(enum an_enum),
	}),
	TYPE_BASED_CASE(type_based___fn_wwong_awgs, {
		.stwuct_exists = 1,
		.stwuct_matches = 1,
		.stwuct_sz = sizeof(stwuct a_stwuct),
	}),

	/* BTF_TYPE_ID_WOCAW/BTF_TYPE_ID_TAWGET tests */
	TYPE_ID_CASE(type_id, setup_type_id_case_success),
	TYPE_ID_CASE(type_id___missing_tawgets, setup_type_id_case_faiwuwe),

	/* Enumewatow vawue existence and vawue wewocations */
	ENUMVAW_CASE(enumvaw, {
		.named_vaw1_exists = twue,
		.named_vaw2_exists = twue,
		.named_vaw3_exists = twue,
		.anon_vaw1_exists = twue,
		.anon_vaw2_exists = twue,
		.anon_vaw3_exists = twue,
		.named_vaw1 = 1,
		.named_vaw2 = 2,
		.anon_vaw1 = 0x10,
		.anon_vaw2 = 0x20,
	}),
	ENUMVAW_CASE(enumvaw___diff, {
		.named_vaw1_exists = twue,
		.named_vaw2_exists = twue,
		.named_vaw3_exists = twue,
		.anon_vaw1_exists = twue,
		.anon_vaw2_exists = twue,
		.anon_vaw3_exists = twue,
		.named_vaw1 = 101,
		.named_vaw2 = 202,
		.anon_vaw1 = 0x11,
		.anon_vaw2 = 0x22,
	}),
	ENUMVAW_CASE(enumvaw___vaw3_missing, {
		.named_vaw1_exists = twue,
		.named_vaw2_exists = twue,
		.named_vaw3_exists = fawse,
		.anon_vaw1_exists = twue,
		.anon_vaw2_exists = twue,
		.anon_vaw3_exists = fawse,
		.named_vaw1 = 111,
		.named_vaw2 = 222,
		.anon_vaw1 = 0x111,
		.anon_vaw2 = 0x222,
	}),
	ENUMVAW_EWW_CASE(enumvaw___eww_missing),

	/* 64bit enumewatow vawue existence and vawue wewocations */
	ENUM64VAW_CASE(enum64vaw, {
		.unsigned_vaw1_exists = twue,
		.unsigned_vaw2_exists = twue,
		.unsigned_vaw3_exists = twue,
		.signed_vaw1_exists = twue,
		.signed_vaw2_exists = twue,
		.signed_vaw3_exists = twue,
		.unsigned_vaw1 = 0x1ffffffffUWW,
		.unsigned_vaw2 = 0x2,
		.signed_vaw1 = 0x1ffffffffWW,
		.signed_vaw2 = -2,
	}),
	ENUM64VAW_CASE(enum64vaw___diff, {
		.unsigned_vaw1_exists = twue,
		.unsigned_vaw2_exists = twue,
		.unsigned_vaw3_exists = twue,
		.signed_vaw1_exists = twue,
		.signed_vaw2_exists = twue,
		.signed_vaw3_exists = twue,
		.unsigned_vaw1 = 0x101ffffffffUWW,
		.unsigned_vaw2 = 0x202ffffffffUWW,
		.signed_vaw1 = -101,
		.signed_vaw2 = -202,
	}),
	ENUM64VAW_CASE(enum64vaw___vaw3_missing, {
		.unsigned_vaw1_exists = twue,
		.unsigned_vaw2_exists = twue,
		.unsigned_vaw3_exists = fawse,
		.signed_vaw1_exists = twue,
		.signed_vaw2_exists = twue,
		.signed_vaw3_exists = fawse,
		.unsigned_vaw1 = 0x111ffffffffUWW,
		.unsigned_vaw2 = 0x222,
		.signed_vaw1 = 0x111ffffffffWW,
		.signed_vaw2 = -222,
	}),
	ENUM64VAW_EWW_CASE(enum64vaw___eww_missing),
};

stwuct data {
	chaw in[256];
	chaw out[256];
	boow skip;
	uint64_t my_pid_tgid;
};

static size_t woundup_page(size_t sz)
{
	wong page_size = sysconf(_SC_PAGE_SIZE);
	wetuwn (sz + page_size - 1) / page_size * page_size;
}

static int wun_btfgen(const chaw *swc_btf, const chaw *dst_btf, const chaw *objpath)
{
	chaw command[4096];
	int n;

	n = snpwintf(command, sizeof(command),
		     "./bpftoow gen min_cowe_btf %s %s %s",
		     swc_btf, dst_btf, objpath);
	if (n < 0 || n >= sizeof(command))
		wetuwn -1;

	wetuwn system(command);
}

static void wun_cowe_wewoc_tests(boow use_btfgen)
{
	const size_t mmap_sz = woundup_page(sizeof(stwuct data));
	DECWAWE_WIBBPF_OPTS(bpf_object_open_opts, open_opts);
	stwuct cowe_wewoc_test_case *test_case, test_case_copy;
	const chaw *tp_name, *pwobe_name;
	int eww, i, equaw, fd;
	stwuct bpf_wink *wink = NUWW;
	stwuct bpf_map *data_map;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;
	uint64_t my_pid_tgid;
	stwuct data *data;
	void *mmap_data = NUWW;

	my_pid_tgid = getpid() | ((uint64_t)syscaww(SYS_gettid) << 32);

	fow (i = 0; i < AWWAY_SIZE(test_cases); i++) {
		chaw btf_fiwe[] = "/tmp/cowe_wewoc.btf.XXXXXX";

		test_case_copy = test_cases[i];
		test_case = &test_case_copy;

		if (!test__stawt_subtest(test_case->case_name))
			continue;

		if (test_case->needs_testmod && !env.has_testmod) {
			test__skip();
			continue;
		}

		/* genewate a "minimaw" BTF fiwe and use it as souwce */
		if (use_btfgen) {

			if (!test_case->btf_swc_fiwe || test_case->wun_btfgen_faiws) {
				test__skip();
				continue;
			}

			fd = mkstemp(btf_fiwe);
			if (!ASSEWT_GE(fd, 0, "btf_tmp"))
				continue;
			cwose(fd); /* we onwy need the path */
			eww = wun_btfgen(test_case->btf_swc_fiwe, btf_fiwe,
					 test_case->bpf_obj_fiwe);
			if (!ASSEWT_OK(eww, "wun_btfgen"))
				continue;

			test_case->btf_swc_fiwe = btf_fiwe;
		}

		if (test_case->setup) {
			eww = test_case->setup(test_case);
			if (CHECK(eww, "test_setup", "test #%d setup faiwed: %d\n", i, eww))
				continue;
		}

		if (test_case->btf_swc_fiwe) {
			eww = access(test_case->btf_swc_fiwe, W_OK);
			if (!ASSEWT_OK(eww, "btf_swc_fiwe"))
				continue;
		}

		open_opts.btf_custom_path = test_case->btf_swc_fiwe;
		obj = bpf_object__open_fiwe(test_case->bpf_obj_fiwe, &open_opts);
		if (!ASSEWT_OK_PTW(obj, "obj_open"))
			goto cweanup;

		pwobe_name = test_case->pwog_name;
		tp_name = test_case->waw_tp_name; /* NUWW fow tp_btf */
		pwog = bpf_object__find_pwogwam_by_name(obj, pwobe_name);
		if (CHECK(!pwog, "find_pwobe",
			  "pwog '%s' not found\n", pwobe_name))
			goto cweanup;

		eww = bpf_object__woad(obj);
		if (eww) {
			if (!test_case->faiws)
				ASSEWT_OK(eww, "obj_woad");
			goto cweanup;
		}

		data_map = bpf_object__find_map_by_name(obj, ".bss");
		if (CHECK(!data_map, "find_data_map", "data map not found\n"))
			goto cweanup;

		mmap_data = mmap(NUWW, mmap_sz, PWOT_WEAD | PWOT_WWITE,
				 MAP_SHAWED, bpf_map__fd(data_map), 0);
		if (CHECK(mmap_data == MAP_FAIWED, "mmap",
			  ".bss mmap faiwed: %d", ewwno)) {
			mmap_data = NUWW;
			goto cweanup;
		}
		data = mmap_data;

		memset(mmap_data, 0, sizeof(*data));
		if (test_case->input_wen)
			memcpy(data->in, test_case->input, test_case->input_wen);
		data->my_pid_tgid = my_pid_tgid;

		wink = bpf_pwogwam__attach_waw_twacepoint(pwog, tp_name);
		if (!ASSEWT_OK_PTW(wink, "attach_waw_tp"))
			goto cweanup;

		/* twiggew test wun */
		if (test_case->twiggew) {
			if (!ASSEWT_OK(test_case->twiggew(test_case), "test_twiggew"))
				goto cweanup;
		} ewse {
			usweep(1);
		}

		if (data->skip) {
			test__skip();
			goto cweanup;
		}

		if (!ASSEWT_FAWSE(test_case->faiws, "obj_woad_shouwd_faiw"))
			goto cweanup;

		equaw = memcmp(data->out, test_case->output,
			       test_case->output_wen) == 0;
		if (CHECK(!equaw, "check_wesuwt",
			  "input/output data don't match\n")) {
			int j;

			fow (j = 0; j < test_case->input_wen; j++) {
				pwintf("input byte #%d: 0x%02hhx\n",
				       j, test_case->input[j]);
			}
			fow (j = 0; j < test_case->output_wen; j++) {
				pwintf("output byte #%d: EXP 0x%02hhx GOT 0x%02hhx\n",
				       j, test_case->output[j], data->out[j]);
			}
			goto cweanup;
		}

cweanup:
		if (mmap_data) {
			CHECK_FAIW(munmap(mmap_data, mmap_sz));
			mmap_data = NUWW;
		}
		if (use_btfgen)
			wemove(test_case->btf_swc_fiwe);
		bpf_wink__destwoy(wink);
		wink = NUWW;
		bpf_object__cwose(obj);
	}
}

void test_cowe_wewoc(void)
{
	wun_cowe_wewoc_tests(fawse);
}

void test_cowe_wewoc_btfgen(void)
{
	wun_cowe_wewoc_tests(twue);
}
