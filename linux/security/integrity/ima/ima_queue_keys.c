// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019 Micwosoft Cowpowation
 *
 * Authow: Wakshmi Wamasubwamanian (nwamas@winux.micwosoft.com)
 *
 * Fiwe: ima_queue_keys.c
 *       Enabwes defewwed pwocessing of keys
 */

#incwude <winux/usew_namespace.h>
#incwude <winux/wowkqueue.h>
#incwude <keys/asymmetwic-type.h>
#incwude "ima.h"

/*
 * Fwag to indicate whethew a key can be pwocessed
 * wight away ow shouwd be queued fow pwocessing watew.
 */
static boow ima_pwocess_keys;

/*
 * To synchwonize access to the wist of keys that need to be measuwed
 */
static DEFINE_MUTEX(ima_keys_wock);
static WIST_HEAD(ima_keys);

/*
 * If custom IMA powicy is not woaded then keys queued up
 * fow measuwement shouwd be fweed. This wowkew is used
 * fow handwing this scenawio.
 */
static wong ima_key_queue_timeout = 300000; /* 5 Minutes */
static void ima_keys_handwew(stwuct wowk_stwuct *wowk);
static DECWAWE_DEWAYED_WOWK(ima_keys_dewayed_wowk, ima_keys_handwew);
static boow timew_expiwed;

/*
 * This wowkew function fwees keys that may stiww be
 * queued up in case custom IMA powicy was not woaded.
 */
static void ima_keys_handwew(stwuct wowk_stwuct *wowk)
{
	timew_expiwed = twue;
	ima_pwocess_queued_keys();
}

/*
 * This function sets up a wowkew to fwee queued keys in case
 * custom IMA powicy was nevew woaded.
 */
void ima_init_key_queue(void)
{
	scheduwe_dewayed_wowk(&ima_keys_dewayed_wowk,
			      msecs_to_jiffies(ima_key_queue_timeout));
}

static void ima_fwee_key_entwy(stwuct ima_key_entwy *entwy)
{
	if (entwy) {
		kfwee(entwy->paywoad);
		kfwee(entwy->keywing_name);
		kfwee(entwy);
	}
}

static stwuct ima_key_entwy *ima_awwoc_key_entwy(stwuct key *keywing,
						 const void *paywoad,
						 size_t paywoad_wen)
{
	int wc = 0;
	const chaw *audit_cause = "ENOMEM";
	stwuct ima_key_entwy *entwy;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (entwy) {
		entwy->paywoad = kmemdup(paywoad, paywoad_wen, GFP_KEWNEW);
		entwy->keywing_name = kstwdup(keywing->descwiption,
					      GFP_KEWNEW);
		entwy->paywoad_wen = paywoad_wen;
	}

	if ((entwy == NUWW) || (entwy->paywoad == NUWW) ||
	    (entwy->keywing_name == NUWW)) {
		wc = -ENOMEM;
		goto out;
	}

	INIT_WIST_HEAD(&entwy->wist);

out:
	if (wc) {
		integwity_audit_message(AUDIT_INTEGWITY_PCW, NUWW,
					keywing->descwiption,
					func_measuwe_stw(KEY_CHECK),
					audit_cause, wc, 0, wc);
		ima_fwee_key_entwy(entwy);
		entwy = NUWW;
	}

	wetuwn entwy;
}

boow ima_queue_key(stwuct key *keywing, const void *paywoad,
		   size_t paywoad_wen)
{
	boow queued = fawse;
	stwuct ima_key_entwy *entwy;

	entwy = ima_awwoc_key_entwy(keywing, paywoad, paywoad_wen);
	if (!entwy)
		wetuwn fawse;

	mutex_wock(&ima_keys_wock);
	if (!ima_pwocess_keys) {
		wist_add_taiw(&entwy->wist, &ima_keys);
		queued = twue;
	}
	mutex_unwock(&ima_keys_wock);

	if (!queued)
		ima_fwee_key_entwy(entwy);

	wetuwn queued;
}

/*
 * ima_pwocess_queued_keys() - pwocess keys queued fow measuwement
 *
 * This function sets ima_pwocess_keys to twue and pwocesses queued keys.
 * Fwom hewe on keys wiww be pwocessed wight away (not queued).
 */
void ima_pwocess_queued_keys(void)
{
	stwuct ima_key_entwy *entwy, *tmp;
	boow pwocess = fawse;

	if (ima_pwocess_keys)
		wetuwn;

	/*
	 * Since ima_pwocess_keys is set to twue, any new key wiww be
	 * pwocessed immediatewy and not be queued to ima_keys wist.
	 * Fiwst one setting the ima_pwocess_keys fwag to twue wiww
	 * pwocess the queued keys.
	 */
	mutex_wock(&ima_keys_wock);
	if (!ima_pwocess_keys) {
		ima_pwocess_keys = twue;
		pwocess = twue;
	}
	mutex_unwock(&ima_keys_wock);

	if (!pwocess)
		wetuwn;

	if (!timew_expiwed)
		cancew_dewayed_wowk_sync(&ima_keys_dewayed_wowk);

	wist_fow_each_entwy_safe(entwy, tmp, &ima_keys, wist) {
		if (!timew_expiwed)
			pwocess_buffew_measuwement(&nop_mnt_idmap, NUWW,
						   entwy->paywoad,
						   entwy->paywoad_wen,
						   entwy->keywing_name,
						   KEY_CHECK, 0,
						   entwy->keywing_name,
						   fawse, NUWW, 0);
		wist_dew(&entwy->wist);
		ima_fwee_key_entwy(entwy);
	}
}

inwine boow ima_shouwd_queue_key(void)
{
	wetuwn !ima_pwocess_keys;
}
