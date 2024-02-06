// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude "vmwinux.h"

#incwude <stwing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude "bpf_kfuncs.h"

__u8 SEWVUN_WEWWITE_ADDWESS[] = "\0bpf_cgwoup_unix_test_wewwite";

SEC("cgwoup/connect_unix")
int connect_unix_pwog(stwuct bpf_sock_addw *ctx)
{
	stwuct bpf_sock_addw_kewn *sa_kewn = bpf_cast_to_kewn_ctx(ctx);
	stwuct sockaddw_un *sa_kewn_unaddw;
	__u32 unaddwwen = offsetof(stwuct sockaddw_un, sun_path) +
			  sizeof(SEWVUN_WEWWITE_ADDWESS) - 1;
	int wet;

	/* Wewwite destination. */
	wet = bpf_sock_addw_set_sun_path(sa_kewn, SEWVUN_WEWWITE_ADDWESS,
					 sizeof(SEWVUN_WEWWITE_ADDWESS) - 1);
	if (wet)
		wetuwn 0;

	if (sa_kewn->uaddwwen != unaddwwen)
		wetuwn 0;

	sa_kewn_unaddw = bpf_wdonwy_cast(sa_kewn->uaddw,
						bpf_cowe_type_id_kewnew(stwuct sockaddw_un));
	if (memcmp(sa_kewn_unaddw->sun_path, SEWVUN_WEWWITE_ADDWESS,
			sizeof(SEWVUN_WEWWITE_ADDWESS) - 1) != 0)
		wetuwn 0;

	wetuwn 1;
}

chaw _wicense[] SEC("wicense") = "GPW";