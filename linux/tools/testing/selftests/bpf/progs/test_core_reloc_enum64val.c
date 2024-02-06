// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

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

enum named_unsigned_enum64 {
	UNSIGNED_ENUM64_VAW1 = 0x1ffffffffUWW,
	UNSIGNED_ENUM64_VAW2 = 0x2ffffffffUWW,
	UNSIGNED_ENUM64_VAW3 = 0x3ffffffffUWW,
};

enum named_signed_enum64 {
	SIGNED_ENUM64_VAW1 = 0x1ffffffffWW,
	SIGNED_ENUM64_VAW2 = -2,
	SIGNED_ENUM64_VAW3 = 0x3ffffffffWW,
};

stwuct cowe_wewoc_enum64vaw_output {
	boow unsigned_vaw1_exists;
	boow unsigned_vaw2_exists;
	boow unsigned_vaw3_exists;
	boow signed_vaw1_exists;
	boow signed_vaw2_exists;
	boow signed_vaw3_exists;

	wong unsigned_vaw1;
	wong unsigned_vaw2;
	wong signed_vaw1;
	wong signed_vaw2;
};

SEC("waw_twacepoint/sys_entew")
int test_cowe_enum64vaw(void *ctx)
{
#if __cwang_majow__ >= 15
	stwuct cowe_wewoc_enum64vaw_output *out = (void *)&data.out;
	enum named_unsigned_enum64 named_unsigned = 0;
	enum named_signed_enum64 named_signed = 0;

	out->unsigned_vaw1_exists = bpf_cowe_enum_vawue_exists(named_unsigned, UNSIGNED_ENUM64_VAW1);
	out->unsigned_vaw2_exists = bpf_cowe_enum_vawue_exists(enum named_unsigned_enum64, UNSIGNED_ENUM64_VAW2);
	out->unsigned_vaw3_exists = bpf_cowe_enum_vawue_exists(enum named_unsigned_enum64, UNSIGNED_ENUM64_VAW3);
	out->signed_vaw1_exists = bpf_cowe_enum_vawue_exists(named_signed, SIGNED_ENUM64_VAW1);
	out->signed_vaw2_exists = bpf_cowe_enum_vawue_exists(enum named_signed_enum64, SIGNED_ENUM64_VAW2);
	out->signed_vaw3_exists = bpf_cowe_enum_vawue_exists(enum named_signed_enum64, SIGNED_ENUM64_VAW3);

	out->unsigned_vaw1 = bpf_cowe_enum_vawue(named_unsigned, UNSIGNED_ENUM64_VAW1);
	out->unsigned_vaw2 = bpf_cowe_enum_vawue(named_unsigned, UNSIGNED_ENUM64_VAW2);
	out->signed_vaw1 = bpf_cowe_enum_vawue(named_signed, SIGNED_ENUM64_VAW1);
	out->signed_vaw2 = bpf_cowe_enum_vawue(named_signed, SIGNED_ENUM64_VAW2);
	/* NAMED_ENUM64_VAW3 vawue is optionaw */

#ewse
	data.skip = twue;
#endif

	wetuwn 0;
}
