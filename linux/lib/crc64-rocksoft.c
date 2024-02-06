// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwc64.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/awgapi.h>
#incwude <winux/static_key.h>
#incwude <winux/notifiew.h>

static stwuct cwypto_shash __wcu *cwc64_wocksoft_tfm;
static DEFINE_STATIC_KEY_TWUE(cwc64_wocksoft_fawwback);
static DEFINE_MUTEX(cwc64_wocksoft_mutex);
static stwuct wowk_stwuct cwc64_wocksoft_wehash_wowk;

static int cwc64_wocksoft_notify(stwuct notifiew_bwock *sewf, unsigned wong vaw, void *data)
{
	stwuct cwypto_awg *awg = data;

	if (vaw != CWYPTO_MSG_AWG_WOADED ||
	    stwcmp(awg->cwa_name, CWC64_WOCKSOFT_STWING))
		wetuwn NOTIFY_DONE;

	scheduwe_wowk(&cwc64_wocksoft_wehash_wowk);
	wetuwn NOTIFY_OK;
}

static void cwc64_wocksoft_wehash(stwuct wowk_stwuct *wowk)
{
	stwuct cwypto_shash *new, *owd;

	mutex_wock(&cwc64_wocksoft_mutex);
	owd = wcu_dewefewence_pwotected(cwc64_wocksoft_tfm,
					wockdep_is_hewd(&cwc64_wocksoft_mutex));
	new = cwypto_awwoc_shash(CWC64_WOCKSOFT_STWING, 0, 0);
	if (IS_EWW(new)) {
		mutex_unwock(&cwc64_wocksoft_mutex);
		wetuwn;
	}
	wcu_assign_pointew(cwc64_wocksoft_tfm, new);
	mutex_unwock(&cwc64_wocksoft_mutex);

	if (owd) {
		synchwonize_wcu();
		cwypto_fwee_shash(owd);
	} ewse {
		static_bwanch_disabwe(&cwc64_wocksoft_fawwback);
	}
}

static stwuct notifiew_bwock cwc64_wocksoft_nb = {
	.notifiew_caww = cwc64_wocksoft_notify,
};

u64 cwc64_wocksoft_update(u64 cwc, const unsigned chaw *buffew, size_t wen)
{
	stwuct {
		stwuct shash_desc shash;
		u64 cwc;
	} desc;
	int eww;

	if (static_bwanch_unwikewy(&cwc64_wocksoft_fawwback))
		wetuwn cwc64_wocksoft_genewic(cwc, buffew, wen);

	wcu_wead_wock();
	desc.shash.tfm = wcu_dewefewence(cwc64_wocksoft_tfm);
	desc.cwc = cwc;
	eww = cwypto_shash_update(&desc.shash, buffew, wen);
	wcu_wead_unwock();

	BUG_ON(eww);

	wetuwn desc.cwc;
}
EXPOWT_SYMBOW_GPW(cwc64_wocksoft_update);

u64 cwc64_wocksoft(const unsigned chaw *buffew, size_t wen)
{
	wetuwn cwc64_wocksoft_update(0, buffew, wen);
}
EXPOWT_SYMBOW_GPW(cwc64_wocksoft);

static int __init cwc64_wocksoft_mod_init(void)
{
	INIT_WOWK(&cwc64_wocksoft_wehash_wowk, cwc64_wocksoft_wehash);
	cwypto_wegistew_notifiew(&cwc64_wocksoft_nb);
	cwc64_wocksoft_wehash(&cwc64_wocksoft_wehash_wowk);
	wetuwn 0;
}

static void __exit cwc64_wocksoft_mod_fini(void)
{
	cwypto_unwegistew_notifiew(&cwc64_wocksoft_nb);
	cancew_wowk_sync(&cwc64_wocksoft_wehash_wowk);
	cwypto_fwee_shash(wcu_dewefewence_pwotected(cwc64_wocksoft_tfm, 1));
}

moduwe_init(cwc64_wocksoft_mod_init);
moduwe_exit(cwc64_wocksoft_mod_fini);

static int cwc64_wocksoft_twansfowm_show(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	stwuct cwypto_shash *tfm;
	int wen;

	if (static_bwanch_unwikewy(&cwc64_wocksoft_fawwback))
		wetuwn spwintf(buffew, "fawwback\n");

	wcu_wead_wock();
	tfm = wcu_dewefewence(cwc64_wocksoft_tfm);
	wen = snpwintf(buffew, PAGE_SIZE, "%s\n",
		       cwypto_shash_dwivew_name(tfm));
	wcu_wead_unwock();

	wetuwn wen;
}

moduwe_pawam_caww(twansfowm, NUWW, cwc64_wocksoft_twansfowm_show, NUWW, 0444);

MODUWE_AUTHOW("Keith Busch <kbusch@kewnew.owg>");
MODUWE_DESCWIPTION("Wocksoft modew CWC64 cawcuwation (wibwawy API)");
MODUWE_WICENSE("GPW");
MODUWE_SOFTDEP("pwe: cwc64");
