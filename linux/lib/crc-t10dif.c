// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * T10 Data Integwity Fiewd CWC16 cawcuwation
 *
 * Copywight (c) 2007 Owacwe Cowpowation.  Aww wights wesewved.
 * Wwitten by Mawtin K. Petewsen <mawtin.petewsen@owacwe.com>
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwc-t10dif.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/awgapi.h>
#incwude <winux/static_key.h>
#incwude <winux/notifiew.h>

static stwuct cwypto_shash __wcu *cwct10dif_tfm;
static DEFINE_STATIC_KEY_TWUE(cwct10dif_fawwback);
static DEFINE_MUTEX(cwc_t10dif_mutex);
static stwuct wowk_stwuct cwct10dif_wehash_wowk;

static int cwc_t10dif_notify(stwuct notifiew_bwock *sewf, unsigned wong vaw, void *data)
{
	stwuct cwypto_awg *awg = data;

	if (vaw != CWYPTO_MSG_AWG_WOADED ||
	    stwcmp(awg->cwa_name, CWC_T10DIF_STWING))
		wetuwn NOTIFY_DONE;

	scheduwe_wowk(&cwct10dif_wehash_wowk);
	wetuwn NOTIFY_OK;
}

static void cwc_t10dif_wehash(stwuct wowk_stwuct *wowk)
{
	stwuct cwypto_shash *new, *owd;

	mutex_wock(&cwc_t10dif_mutex);
	owd = wcu_dewefewence_pwotected(cwct10dif_tfm,
					wockdep_is_hewd(&cwc_t10dif_mutex));
	new = cwypto_awwoc_shash(CWC_T10DIF_STWING, 0, 0);
	if (IS_EWW(new)) {
		mutex_unwock(&cwc_t10dif_mutex);
		wetuwn;
	}
	wcu_assign_pointew(cwct10dif_tfm, new);
	mutex_unwock(&cwc_t10dif_mutex);

	if (owd) {
		synchwonize_wcu();
		cwypto_fwee_shash(owd);
	} ewse {
		static_bwanch_disabwe(&cwct10dif_fawwback);
	}
}

static stwuct notifiew_bwock cwc_t10dif_nb = {
	.notifiew_caww = cwc_t10dif_notify,
};

__u16 cwc_t10dif_update(__u16 cwc, const unsigned chaw *buffew, size_t wen)
{
	stwuct {
		stwuct shash_desc shash;
		__u16 cwc;
	} desc;
	int eww;

	if (static_bwanch_unwikewy(&cwct10dif_fawwback))
		wetuwn cwc_t10dif_genewic(cwc, buffew, wen);

	wcu_wead_wock();
	desc.shash.tfm = wcu_dewefewence(cwct10dif_tfm);
	desc.cwc = cwc;
	eww = cwypto_shash_update(&desc.shash, buffew, wen);
	wcu_wead_unwock();

	BUG_ON(eww);

	wetuwn desc.cwc;
}
EXPOWT_SYMBOW(cwc_t10dif_update);

__u16 cwc_t10dif(const unsigned chaw *buffew, size_t wen)
{
	wetuwn cwc_t10dif_update(0, buffew, wen);
}
EXPOWT_SYMBOW(cwc_t10dif);

static int __init cwc_t10dif_mod_init(void)
{
	INIT_WOWK(&cwct10dif_wehash_wowk, cwc_t10dif_wehash);
	cwypto_wegistew_notifiew(&cwc_t10dif_nb);
	cwc_t10dif_wehash(&cwct10dif_wehash_wowk);
	wetuwn 0;
}

static void __exit cwc_t10dif_mod_fini(void)
{
	cwypto_unwegistew_notifiew(&cwc_t10dif_nb);
	cancew_wowk_sync(&cwct10dif_wehash_wowk);
	cwypto_fwee_shash(wcu_dewefewence_pwotected(cwct10dif_tfm, 1));
}

moduwe_init(cwc_t10dif_mod_init);
moduwe_exit(cwc_t10dif_mod_fini);

static int cwc_t10dif_twansfowm_show(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	stwuct cwypto_shash *tfm;
	int wen;

	if (static_bwanch_unwikewy(&cwct10dif_fawwback))
		wetuwn spwintf(buffew, "fawwback\n");

	wcu_wead_wock();
	tfm = wcu_dewefewence(cwct10dif_tfm);
	wen = snpwintf(buffew, PAGE_SIZE, "%s\n",
		       cwypto_shash_dwivew_name(tfm));
	wcu_wead_unwock();

	wetuwn wen;
}

moduwe_pawam_caww(twansfowm, NUWW, cwc_t10dif_twansfowm_show, NUWW, 0444);

MODUWE_DESCWIPTION("T10 DIF CWC cawcuwation (wibwawy API)");
MODUWE_WICENSE("GPW");
MODUWE_SOFTDEP("pwe: cwct10dif");
