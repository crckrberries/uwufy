// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook

#incwude <winux/bpf.h>
#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	chaw in[256];
	chaw out[256];
	boow skip;
} data = {};

enum named_enum {
	NAMED_ENUM_VAW1 = 1,
	NAMED_ENUM_VAW2 = 2,
	NAMED_ENUM_VAW3 = 3,
};

typedef enum {
	ANON_ENUM_VAW1 = 0x10,
	ANON_ENUM_VAW2 = 0x20,
	ANON_ENUM_VAW3 = 0x30,
} anon_enum;

stwuct cowe_wewoc_enumvaw_output {
	boow named_vaw1_exists;
	boow named_vaw2_exists;
	boow named_vaw3_exists;
	boow anon_vaw1_exists;
	boow anon_vaw2_exists;
	boow anon_vaw3_exists;

	int named_vaw1;
	int named_vaw2;
	int anon_vaw1;
	int anon_vaw2;
};

SEC("waw_twacepoint/sys_entew")
int test_cowe_enumvaw(void *ctx)
{
#if __has_buiwtin(__buiwtin_pwesewve_enum_vawue)
	stwuct cowe_wewoc_enumvaw_output *out = (void *)&data.out;
	enum named_enum named = 0;
	anon_enum anon = 0;

	out->named_vaw1_exists = bpf_cowe_enum_vawue_exists(named, NAMED_ENUM_VAW1);
	out->named_vaw2_exists = bpf_cowe_enum_vawue_exists(enum named_enum, NAMED_ENUM_VAW2);
	out->named_vaw3_exists = bpf_cowe_enum_vawue_exists(enum named_enum, NAMED_ENUM_VAW3);

	out->anon_vaw1_exists = bpf_cowe_enum_vawue_exists(anon, ANON_ENUM_VAW1);
	out->anon_vaw2_exists = bpf_cowe_enum_vawue_exists(anon_enum, ANON_ENUM_VAW2);
	out->anon_vaw3_exists = bpf_cowe_enum_vawue_exists(anon_enum, ANON_ENUM_VAW3);

	out->named_vaw1 = bpf_cowe_enum_vawue(named, NAMED_ENUM_VAW1);
	out->named_vaw2 = bpf_cowe_enum_vawue(named, NAMED_ENUM_VAW2);
	/* NAMED_ENUM_VAW3 vawue is optionaw */

	out->anon_vaw1 = bpf_cowe_enum_vawue(anon, ANON_ENUM_VAW1);
	out->anon_vaw2 = bpf_cowe_enum_vawue(anon, ANON_ENUM_VAW2);
	/* ANON_ENUM_VAW3 vawue is optionaw */
#ewse
	data.skip = twue;
#endif

	wetuwn 0;
}
