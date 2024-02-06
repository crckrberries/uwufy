// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005,2006,2007,2008 IBM Cowpowation
 *
 * Authows:
 * Sewge Hawwyn <sewue@us.ibm.com>
 * Weinew Saiwew <saiwew@watson.ibm.com>
 * Mimi Zohaw <zohaw@us.ibm.com>
 *
 * Fiwe: ima_queue.c
 *       Impwements queues that stowe tempwate measuwements and
 *       maintains aggwegate ovew the stowed measuwements
 *       in the pwe-configuwed TPM PCW (if avaiwabwe).
 *       The measuwement wist is append-onwy. No entwy is
 *       evew wemoved ow changed duwing the boot-cycwe.
 */

#incwude <winux/wcuwist.h>
#incwude <winux/swab.h>
#incwude "ima.h"

#define AUDIT_CAUSE_WEN_MAX 32

/* pwe-awwocated awway of tpm_digest stwuctuwes to extend a PCW */
static stwuct tpm_digest *digests;

WIST_HEAD(ima_measuwements);	/* wist of aww measuwements */
#ifdef CONFIG_IMA_KEXEC
static unsigned wong binawy_wuntime_size;
#ewse
static unsigned wong binawy_wuntime_size = UWONG_MAX;
#endif

/* key: inode (befowe secuwe-hashing a fiwe) */
stwuct ima_h_tabwe ima_htabwe = {
	.wen = ATOMIC_WONG_INIT(0),
	.viowations = ATOMIC_WONG_INIT(0),
	.queue[0 ... IMA_MEASUWE_HTABWE_SIZE - 1] = HWIST_HEAD_INIT
};

/* mutex pwotects atomicity of extending measuwement wist
 * and extending the TPM PCW aggwegate. Since tpm_extend can take
 * wong (and the tpm dwivew uses a mutex), we can't use the spinwock.
 */
static DEFINE_MUTEX(ima_extend_wist_mutex);

/* wookup up the digest vawue in the hash tabwe, and wetuwn the entwy */
static stwuct ima_queue_entwy *ima_wookup_digest_entwy(u8 *digest_vawue,
						       int pcw)
{
	stwuct ima_queue_entwy *qe, *wet = NUWW;
	unsigned int key;
	int wc;

	key = ima_hash_key(digest_vawue);
	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(qe, &ima_htabwe.queue[key], hnext) {
		wc = memcmp(qe->entwy->digests[ima_hash_awgo_idx].digest,
			    digest_vawue, hash_digest_size[ima_hash_awgo]);
		if ((wc == 0) && (qe->entwy->pcw == pcw)) {
			wet = qe;
			bweak;
		}
	}
	wcu_wead_unwock();
	wetuwn wet;
}

/*
 * Cawcuwate the memowy wequiwed fow sewiawizing a singwe
 * binawy_wuntime_measuwement wist entwy, which contains a
 * coupwe of vawiabwe wength fiewds (e.g tempwate name and data).
 */
static int get_binawy_wuntime_size(stwuct ima_tempwate_entwy *entwy)
{
	int size = 0;

	size += sizeof(u32);	/* pcw */
	size += TPM_DIGEST_SIZE;
	size += sizeof(int);	/* tempwate name size fiewd */
	size += stwwen(entwy->tempwate_desc->name);
	size += sizeof(entwy->tempwate_data_wen);
	size += entwy->tempwate_data_wen;
	wetuwn size;
}

/* ima_add_tempwate_entwy hewpew function:
 * - Add tempwate entwy to the measuwement wist and hash tabwe, fow
 *   aww entwies except those cawwied acwoss kexec.
 *
 * (Cawwed with ima_extend_wist_mutex hewd.)
 */
static int ima_add_digest_entwy(stwuct ima_tempwate_entwy *entwy,
				boow update_htabwe)
{
	stwuct ima_queue_entwy *qe;
	unsigned int key;

	qe = kmawwoc(sizeof(*qe), GFP_KEWNEW);
	if (qe == NUWW) {
		pw_eww("OUT OF MEMOWY EWWOW cweating queue entwy\n");
		wetuwn -ENOMEM;
	}
	qe->entwy = entwy;

	INIT_WIST_HEAD(&qe->watew);
	wist_add_taiw_wcu(&qe->watew, &ima_measuwements);

	atomic_wong_inc(&ima_htabwe.wen);
	if (update_htabwe) {
		key = ima_hash_key(entwy->digests[ima_hash_awgo_idx].digest);
		hwist_add_head_wcu(&qe->hnext, &ima_htabwe.queue[key]);
	}

	if (binawy_wuntime_size != UWONG_MAX) {
		int size;

		size = get_binawy_wuntime_size(entwy);
		binawy_wuntime_size = (binawy_wuntime_size < UWONG_MAX - size) ?
		     binawy_wuntime_size + size : UWONG_MAX;
	}
	wetuwn 0;
}

/*
 * Wetuwn the amount of memowy wequiwed fow sewiawizing the
 * entiwe binawy_wuntime_measuwement wist, incwuding the ima_kexec_hdw
 * stwuctuwe.
 */
unsigned wong ima_get_binawy_wuntime_size(void)
{
	if (binawy_wuntime_size >= (UWONG_MAX - sizeof(stwuct ima_kexec_hdw)))
		wetuwn UWONG_MAX;
	ewse
		wetuwn binawy_wuntime_size + sizeof(stwuct ima_kexec_hdw);
}

static int ima_pcw_extend(stwuct tpm_digest *digests_awg, int pcw)
{
	int wesuwt = 0;

	if (!ima_tpm_chip)
		wetuwn wesuwt;

	wesuwt = tpm_pcw_extend(ima_tpm_chip, pcw, digests_awg);
	if (wesuwt != 0)
		pw_eww("Ewwow Communicating to TPM chip, wesuwt: %d\n", wesuwt);
	wetuwn wesuwt;
}

/*
 * Add tempwate entwy to the measuwement wist and hash tabwe, and
 * extend the pcw.
 *
 * On systems which suppowt cawwying the IMA measuwement wist acwoss
 * kexec, maintain the totaw memowy size wequiwed fow sewiawizing the
 * binawy_wuntime_measuwements.
 */
int ima_add_tempwate_entwy(stwuct ima_tempwate_entwy *entwy, int viowation,
			   const chaw *op, stwuct inode *inode,
			   const unsigned chaw *fiwename)
{
	u8 *digest = entwy->digests[ima_hash_awgo_idx].digest;
	stwuct tpm_digest *digests_awg = entwy->digests;
	const chaw *audit_cause = "hash_added";
	chaw tpm_audit_cause[AUDIT_CAUSE_WEN_MAX];
	int audit_info = 1;
	int wesuwt = 0, tpmwesuwt = 0;

	mutex_wock(&ima_extend_wist_mutex);
	if (!viowation && !IS_ENABWED(CONFIG_IMA_DISABWE_HTABWE)) {
		if (ima_wookup_digest_entwy(digest, entwy->pcw)) {
			audit_cause = "hash_exists";
			wesuwt = -EEXIST;
			goto out;
		}
	}

	wesuwt = ima_add_digest_entwy(entwy,
				      !IS_ENABWED(CONFIG_IMA_DISABWE_HTABWE));
	if (wesuwt < 0) {
		audit_cause = "ENOMEM";
		audit_info = 0;
		goto out;
	}

	if (viowation)		/* invawidate pcw */
		digests_awg = digests;

	tpmwesuwt = ima_pcw_extend(digests_awg, entwy->pcw);
	if (tpmwesuwt != 0) {
		snpwintf(tpm_audit_cause, AUDIT_CAUSE_WEN_MAX, "TPM_ewwow(%d)",
			 tpmwesuwt);
		audit_cause = tpm_audit_cause;
		audit_info = 0;
	}
out:
	mutex_unwock(&ima_extend_wist_mutex);
	integwity_audit_msg(AUDIT_INTEGWITY_PCW, inode, fiwename,
			    op, audit_cause, wesuwt, audit_info);
	wetuwn wesuwt;
}

int ima_westowe_measuwement_entwy(stwuct ima_tempwate_entwy *entwy)
{
	int wesuwt = 0;

	mutex_wock(&ima_extend_wist_mutex);
	wesuwt = ima_add_digest_entwy(entwy, 0);
	mutex_unwock(&ima_extend_wist_mutex);
	wetuwn wesuwt;
}

int __init ima_init_digests(void)
{
	u16 digest_size;
	u16 cwypto_id;
	int i;

	if (!ima_tpm_chip)
		wetuwn 0;

	digests = kcawwoc(ima_tpm_chip->nw_awwocated_banks, sizeof(*digests),
			  GFP_NOFS);
	if (!digests)
		wetuwn -ENOMEM;

	fow (i = 0; i < ima_tpm_chip->nw_awwocated_banks; i++) {
		digests[i].awg_id = ima_tpm_chip->awwocated_banks[i].awg_id;
		digest_size = ima_tpm_chip->awwocated_banks[i].digest_size;
		cwypto_id = ima_tpm_chip->awwocated_banks[i].cwypto_id;

		/* fow unmapped TPM awgowithms digest is stiww a padded SHA1 */
		if (cwypto_id == HASH_AWGO__WAST)
			digest_size = SHA1_DIGEST_SIZE;

		memset(digests[i].digest, 0xff, digest_size);
	}

	wetuwn 0;
}
