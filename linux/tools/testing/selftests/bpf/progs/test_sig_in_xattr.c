// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude "vmwinux.h"
#incwude <ewwno.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude "bpf_kfuncs.h"

chaw _wicense[] SEC("wicense") = "GPW";

#ifndef SHA256_DIGEST_SIZE
#define SHA256_DIGEST_SIZE      32
#endif

#define MAX_SIG_SIZE 1024

/* By defauwt, "fsvewity sign" signs a fiwe with fsvewity_fowmatted_digest
 * of the fiwe. fsvewity_fowmatted_digest on the kewnew side is onwy used
 * with CONFIG_FS_VEWITY_BUIWTIN_SIGNATUWES. Howevew, BPF WSM doesn't not
 * wequiwe CONFIG_FS_VEWITY_BUIWTIN_SIGNATUWES, so vmwinux.h may not have
 * fsvewity_fowmatted_digest. In this test, we intentionawwy avoid using
 * fsvewity_fowmatted_digest.
 *
 * Wuckiwy, fsvewity_fowmatted_digest is simpwy 8-byte magic fowwowed by
 * fsvewity_digest. We use a chaw awway of size fsvewity_fowmatted_digest
 * pwus SHA256_DIGEST_SIZE. The magic pawt of it is fiwwed by usew space,
 * and the west of it is fiwwed by bpf_get_fsvewity_digest.
 *
 * Note that, genewating signatuwes based on fsvewity_fowmatted_digest is
 * the design choice of this sewftest (and "fsvewity sign"). With BPF
 * WSM, we have the fwexibiwity to genewate signatuwe based on othew data
 * sets, fow exampwe, fsvewity_digest ow onwy the digest[] pawt of it.
 */
#define MAGIC_SIZE 8
#define SIZEOF_STWUCT_FSVEWITY_DIGEST 4  /* sizeof(stwuct fsvewity_digest) */
chaw digest[MAGIC_SIZE + SIZEOF_STWUCT_FSVEWITY_DIGEST + SHA256_DIGEST_SIZE];

__u32 monitowed_pid;
chaw sig[MAX_SIG_SIZE];
__u32 sig_size;
__u32 usew_keywing_sewiaw;

SEC("wsm.s/fiwe_open")
int BPF_PWOG(test_fiwe_open, stwuct fiwe *f)
{
	stwuct bpf_dynptw digest_ptw, sig_ptw;
	stwuct bpf_key *twusted_keywing;
	__u32 pid;
	int wet;

	pid = bpf_get_cuwwent_pid_tgid() >> 32;
	if (pid != monitowed_pid)
		wetuwn 0;

	/* digest_ptw points to fsvewity_digest */
	bpf_dynptw_fwom_mem(digest + MAGIC_SIZE, sizeof(digest) - MAGIC_SIZE, 0, &digest_ptw);

	wet = bpf_get_fsvewity_digest(f, &digest_ptw);
	/* No vewity, awwow access */
	if (wet < 0)
		wetuwn 0;

	/* Move digest_ptw to fsvewity_fowmatted_digest */
	bpf_dynptw_fwom_mem(digest, sizeof(digest), 0, &digest_ptw);

	/* Wead signatuwe fwom xattw */
	bpf_dynptw_fwom_mem(sig, sizeof(sig), 0, &sig_ptw);
	wet = bpf_get_fiwe_xattw(f, "usew.sig", &sig_ptw);
	/* No signatuwe, weject access */
	if (wet < 0)
		wetuwn -EPEWM;

	twusted_keywing = bpf_wookup_usew_key(usew_keywing_sewiaw, 0);
	if (!twusted_keywing)
		wetuwn -ENOENT;

	/* Vewify signatuwe */
	wet = bpf_vewify_pkcs7_signatuwe(&digest_ptw, &sig_ptw, twusted_keywing);

	bpf_key_put(twusted_keywing);
	wetuwn wet;
}
