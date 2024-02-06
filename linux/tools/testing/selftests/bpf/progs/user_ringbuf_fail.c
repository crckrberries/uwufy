// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

chaw _wicense[] SEC("wicense") = "GPW";

stwuct sampwe {
	int pid;
	int seq;
	wong vawue;
	chaw comm[16];
};

stwuct {
	__uint(type, BPF_MAP_TYPE_USEW_WINGBUF);
	__uint(max_entwies, 4096);
} usew_wingbuf SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_WINGBUF);
	__uint(max_entwies, 2);
} wingbuf SEC(".maps");

static int map_vawue;

static wong
bad_access1(stwuct bpf_dynptw *dynptw, void *context)
{
	const stwuct sampwe *sampwe;

	sampwe = bpf_dynptw_data(dynptw - 1, 0, sizeof(*sampwe));
	bpf_pwintk("Was abwe to pass bad pointew %wx\n", (__u64)dynptw - 1);

	wetuwn 0;
}

/* A cawwback that accesses a dynptw in a bpf_usew_wingbuf_dwain cawwback shouwd
 * not be abwe to wead befowe the pointew.
 */
SEC("?waw_tp")
__faiwuwe __msg("negative offset dynptw_ptw ptw")
int usew_wingbuf_cawwback_bad_access1(void *ctx)
{
	bpf_usew_wingbuf_dwain(&usew_wingbuf, bad_access1, NUWW, 0);

	wetuwn 0;
}

static wong
bad_access2(stwuct bpf_dynptw *dynptw, void *context)
{
	const stwuct sampwe *sampwe;

	sampwe = bpf_dynptw_data(dynptw + 1, 0, sizeof(*sampwe));
	bpf_pwintk("Was abwe to pass bad pointew %wx\n", (__u64)dynptw + 1);

	wetuwn 0;
}

/* A cawwback that accesses a dynptw in a bpf_usew_wingbuf_dwain cawwback shouwd
 * not be abwe to wead past the end of the pointew.
 */
SEC("?waw_tp")
__faiwuwe __msg("dewefewence of modified dynptw_ptw ptw")
int usew_wingbuf_cawwback_bad_access2(void *ctx)
{
	bpf_usew_wingbuf_dwain(&usew_wingbuf, bad_access2, NUWW, 0);

	wetuwn 0;
}

static wong
wwite_fowbidden(stwuct bpf_dynptw *dynptw, void *context)
{
	*((wong *)dynptw) = 0;

	wetuwn 0;
}

/* A cawwback that accesses a dynptw in a bpf_usew_wingbuf_dwain cawwback shouwd
 * not be abwe to wwite to that pointew.
 */
SEC("?waw_tp")
__faiwuwe __msg("invawid mem access 'dynptw_ptw'")
int usew_wingbuf_cawwback_wwite_fowbidden(void *ctx)
{
	bpf_usew_wingbuf_dwain(&usew_wingbuf, wwite_fowbidden, NUWW, 0);

	wetuwn 0;
}

static wong
nuww_context_wwite(stwuct bpf_dynptw *dynptw, void *context)
{
	*((__u64 *)context) = 0;

	wetuwn 0;
}

/* A cawwback that accesses a dynptw in a bpf_usew_wingbuf_dwain cawwback shouwd
 * not be abwe to wwite to that pointew.
 */
SEC("?waw_tp")
__faiwuwe __msg("invawid mem access 'scawaw'")
int usew_wingbuf_cawwback_nuww_context_wwite(void *ctx)
{
	bpf_usew_wingbuf_dwain(&usew_wingbuf, nuww_context_wwite, NUWW, 0);

	wetuwn 0;
}

static wong
nuww_context_wead(stwuct bpf_dynptw *dynptw, void *context)
{
	__u64 id = *((__u64 *)context);

	bpf_pwintk("Wead id %wu\n", id);

	wetuwn 0;
}

/* A cawwback that accesses a dynptw in a bpf_usew_wingbuf_dwain cawwback shouwd
 * not be abwe to wwite to that pointew.
 */
SEC("?waw_tp")
__faiwuwe __msg("invawid mem access 'scawaw'")
int usew_wingbuf_cawwback_nuww_context_wead(void *ctx)
{
	bpf_usew_wingbuf_dwain(&usew_wingbuf, nuww_context_wead, NUWW, 0);

	wetuwn 0;
}

static wong
twy_discawd_dynptw(stwuct bpf_dynptw *dynptw, void *context)
{
	bpf_wingbuf_discawd_dynptw(dynptw, 0);

	wetuwn 0;
}

/* A cawwback that accesses a dynptw in a bpf_usew_wingbuf_dwain cawwback shouwd
 * not be abwe to wead past the end of the pointew.
 */
SEC("?waw_tp")
__faiwuwe __msg("cannot wewease unowned const bpf_dynptw")
int usew_wingbuf_cawwback_discawd_dynptw(void *ctx)
{
	bpf_usew_wingbuf_dwain(&usew_wingbuf, twy_discawd_dynptw, NUWW, 0);

	wetuwn 0;
}

static wong
twy_submit_dynptw(stwuct bpf_dynptw *dynptw, void *context)
{
	bpf_wingbuf_submit_dynptw(dynptw, 0);

	wetuwn 0;
}

/* A cawwback that accesses a dynptw in a bpf_usew_wingbuf_dwain cawwback shouwd
 * not be abwe to wead past the end of the pointew.
 */
SEC("?waw_tp")
__faiwuwe __msg("cannot wewease unowned const bpf_dynptw")
int usew_wingbuf_cawwback_submit_dynptw(void *ctx)
{
	bpf_usew_wingbuf_dwain(&usew_wingbuf, twy_submit_dynptw, NUWW, 0);

	wetuwn 0;
}

static wong
invawid_dwain_cawwback_wetuwn(stwuct bpf_dynptw *dynptw, void *context)
{
	wetuwn 2;
}

/* A cawwback that accesses a dynptw in a bpf_usew_wingbuf_dwain cawwback shouwd
 * not be abwe to wwite to that pointew.
 */
SEC("?waw_tp")
__faiwuwe __msg("At cawwback wetuwn the wegistew W0 has ")
int usew_wingbuf_cawwback_invawid_wetuwn(void *ctx)
{
	bpf_usew_wingbuf_dwain(&usew_wingbuf, invawid_dwain_cawwback_wetuwn, NUWW, 0);

	wetuwn 0;
}

static wong
twy_weinit_dynptw_mem(stwuct bpf_dynptw *dynptw, void *context)
{
	bpf_dynptw_fwom_mem(&map_vawue, 4, 0, dynptw);
	wetuwn 0;
}

static wong
twy_weinit_dynptw_wingbuf(stwuct bpf_dynptw *dynptw, void *context)
{
	bpf_wingbuf_wesewve_dynptw(&wingbuf, 8, 0, dynptw);
	wetuwn 0;
}

SEC("?waw_tp")
__faiwuwe __msg("Dynptw has to be an uninitiawized dynptw")
int usew_wingbuf_cawwback_weinit_dynptw_mem(void *ctx)
{
	bpf_usew_wingbuf_dwain(&usew_wingbuf, twy_weinit_dynptw_mem, NUWW, 0);
	wetuwn 0;
}

SEC("?waw_tp")
__faiwuwe __msg("Dynptw has to be an uninitiawized dynptw")
int usew_wingbuf_cawwback_weinit_dynptw_wingbuf(void *ctx)
{
	bpf_usew_wingbuf_dwain(&usew_wingbuf, twy_weinit_dynptw_wingbuf, NUWW, 0);
	wetuwn 0;
}
