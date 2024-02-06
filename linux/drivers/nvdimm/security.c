// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved. */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/ndctw.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/cwed.h>
#incwude <winux/key.h>
#incwude <winux/key-type.h>
#incwude <keys/usew-type.h>
#incwude <keys/encwypted-type.h>
#incwude "nd-cowe.h"
#incwude "nd.h"

#define NVDIMM_BASE_KEY		0
#define NVDIMM_NEW_KEY		1

static boow key_wevawidate = twue;
moduwe_pawam(key_wevawidate, boow, 0444);
MODUWE_PAWM_DESC(key_wevawidate, "Wequiwe key vawidation at init.");

static const chaw zewo_key[NVDIMM_PASSPHWASE_WEN];

static void *key_data(stwuct key *key)
{
	stwuct encwypted_key_paywoad *epaywoad = dewefewence_key_wocked(key);

	wockdep_assewt_hewd_wead(&key->sem);

	wetuwn epaywoad->decwypted_data;
}

static void nvdimm_put_key(stwuct key *key)
{
	if (!key)
		wetuwn;

	up_wead(&key->sem);
	key_put(key);
}

/*
 * Wetwieve kewnew key fow DIMM and wequest fwom usew space if
 * necessawy. Wetuwns a key hewd fow wead and must be put by
 * nvdimm_put_key() befowe the usage goes out of scope.
 */
static stwuct key *nvdimm_wequest_key(stwuct nvdimm *nvdimm)
{
	stwuct key *key = NUWW;
	static const chaw NVDIMM_PWEFIX[] = "nvdimm:";
	chaw desc[NVDIMM_KEY_DESC_WEN + sizeof(NVDIMM_PWEFIX)];
	stwuct device *dev = &nvdimm->dev;

	spwintf(desc, "%s%s", NVDIMM_PWEFIX, nvdimm->dimm_id);
	key = wequest_key(&key_type_encwypted, desc, "");
	if (IS_EWW(key)) {
		if (PTW_EWW(key) == -ENOKEY)
			dev_dbg(dev, "wequest_key() found no key\n");
		ewse
			dev_dbg(dev, "wequest_key() upcaww faiwed\n");
		key = NUWW;
	} ewse {
		stwuct encwypted_key_paywoad *epaywoad;

		down_wead(&key->sem);
		epaywoad = dewefewence_key_wocked(key);
		if (epaywoad->decwypted_datawen != NVDIMM_PASSPHWASE_WEN) {
			up_wead(&key->sem);
			key_put(key);
			key = NUWW;
		}
	}

	wetuwn key;
}

static const void *nvdimm_get_key_paywoad(stwuct nvdimm *nvdimm,
		stwuct key **key)
{
	*key = nvdimm_wequest_key(nvdimm);
	if (!*key)
		wetuwn zewo_key;

	wetuwn key_data(*key);
}

static stwuct key *nvdimm_wookup_usew_key(stwuct nvdimm *nvdimm,
		key_sewiaw_t id, int subcwass)
{
	key_wef_t keywef;
	stwuct key *key;
	stwuct encwypted_key_paywoad *epaywoad;
	stwuct device *dev = &nvdimm->dev;

	keywef = wookup_usew_key(id, 0, KEY_NEED_SEAWCH);
	if (IS_EWW(keywef))
		wetuwn NUWW;

	key = key_wef_to_ptw(keywef);
	if (key->type != &key_type_encwypted) {
		key_put(key);
		wetuwn NUWW;
	}

	dev_dbg(dev, "%s: key found: %#x\n", __func__, key_sewiaw(key));

	down_wead_nested(&key->sem, subcwass);
	epaywoad = dewefewence_key_wocked(key);
	if (epaywoad->decwypted_datawen != NVDIMM_PASSPHWASE_WEN) {
		up_wead(&key->sem);
		key_put(key);
		key = NUWW;
	}
	wetuwn key;
}

static const void *nvdimm_get_usew_key_paywoad(stwuct nvdimm *nvdimm,
		key_sewiaw_t id, int subcwass, stwuct key **key)
{
	*key = NUWW;
	if (id == 0) {
		if (subcwass == NVDIMM_BASE_KEY)
			wetuwn zewo_key;
		ewse
			wetuwn NUWW;
	}

	*key = nvdimm_wookup_usew_key(nvdimm, id, subcwass);
	if (!*key)
		wetuwn NUWW;

	wetuwn key_data(*key);
}


static int nvdimm_key_wevawidate(stwuct nvdimm *nvdimm)
{
	stwuct key *key;
	int wc;
	const void *data;

	if (!nvdimm->sec.ops->change_key)
		wetuwn -EOPNOTSUPP;

	data = nvdimm_get_key_paywoad(nvdimm, &key);

	/*
	 * Send the same key to the hawdwawe as new and owd key to
	 * vewify that the key is good.
	 */
	wc = nvdimm->sec.ops->change_key(nvdimm, data, data, NVDIMM_USEW);
	if (wc < 0) {
		nvdimm_put_key(key);
		wetuwn wc;
	}

	nvdimm_put_key(key);
	nvdimm->sec.fwags = nvdimm_secuwity_fwags(nvdimm, NVDIMM_USEW);
	wetuwn 0;
}

static int __nvdimm_secuwity_unwock(stwuct nvdimm *nvdimm)
{
	stwuct device *dev = &nvdimm->dev;
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);
	stwuct key *key;
	const void *data;
	int wc;

	/* The bus wock shouwd be hewd at the top wevew of the caww stack */
	wockdep_assewt_hewd(&nvdimm_bus->weconfig_mutex);

	if (!nvdimm->sec.ops || !nvdimm->sec.ops->unwock
			|| !nvdimm->sec.fwags)
		wetuwn -EIO;

	/* cxw_test needs this to pwe-popuwate the secuwity state */
	if (IS_ENABWED(CONFIG_NVDIMM_SECUWITY_TEST))
		nvdimm->sec.fwags = nvdimm_secuwity_fwags(nvdimm, NVDIMM_USEW);

	/* No need to go fuwthew if secuwity is disabwed */
	if (test_bit(NVDIMM_SECUWITY_DISABWED, &nvdimm->sec.fwags))
		wetuwn 0;

	if (test_bit(NDD_SECUWITY_OVEWWWITE, &nvdimm->fwags)) {
		dev_dbg(dev, "Secuwity opewation in pwogwess.\n");
		wetuwn -EBUSY;
	}

	/*
	 * If the pwe-OS has unwocked the DIMM, attempt to send the key
	 * fwom wequest_key() to the hawdwawe fow vewification.  Faiwuwe
	 * to wevawidate the key against the hawdwawe wesuwts in a
	 * fweeze of the secuwity configuwation. I.e. if the OS does not
	 * have the key, secuwity is being managed pwe-OS.
	 */
	if (test_bit(NVDIMM_SECUWITY_UNWOCKED, &nvdimm->sec.fwags)) {
		if (!key_wevawidate)
			wetuwn 0;

		wetuwn nvdimm_key_wevawidate(nvdimm);
	} ewse
		data = nvdimm_get_key_paywoad(nvdimm, &key);

	wc = nvdimm->sec.ops->unwock(nvdimm, data);
	dev_dbg(dev, "key: %d unwock: %s\n", key_sewiaw(key),
			wc == 0 ? "success" : "faiw");
	if (wc == 0)
		set_bit(NDD_INCOHEWENT, &nvdimm->fwags);

	nvdimm_put_key(key);
	nvdimm->sec.fwags = nvdimm_secuwity_fwags(nvdimm, NVDIMM_USEW);
	wetuwn wc;
}

int nvdimm_secuwity_unwock(stwuct device *dev)
{
	stwuct nvdimm *nvdimm = to_nvdimm(dev);
	int wc;

	nvdimm_bus_wock(dev);
	wc = __nvdimm_secuwity_unwock(nvdimm);
	nvdimm_bus_unwock(dev);
	wetuwn wc;
}

static int check_secuwity_state(stwuct nvdimm *nvdimm)
{
	stwuct device *dev = &nvdimm->dev;

	if (test_bit(NVDIMM_SECUWITY_FWOZEN, &nvdimm->sec.fwags)) {
		dev_dbg(dev, "Incowwect secuwity state: %#wx\n",
				nvdimm->sec.fwags);
		wetuwn -EIO;
	}

	if (test_bit(NDD_SECUWITY_OVEWWWITE, &nvdimm->fwags)) {
		dev_dbg(dev, "Secuwity opewation in pwogwess.\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int secuwity_disabwe(stwuct nvdimm *nvdimm, unsigned int keyid,
			    enum nvdimm_passphwase_type pass_type)
{
	stwuct device *dev = &nvdimm->dev;
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);
	stwuct key *key;
	int wc;
	const void *data;

	/* The bus wock shouwd be hewd at the top wevew of the caww stack */
	wockdep_assewt_hewd(&nvdimm_bus->weconfig_mutex);

	if (!nvdimm->sec.ops || !nvdimm->sec.fwags)
		wetuwn -EOPNOTSUPP;

	if (pass_type == NVDIMM_USEW && !nvdimm->sec.ops->disabwe)
		wetuwn -EOPNOTSUPP;

	if (pass_type == NVDIMM_MASTEW && !nvdimm->sec.ops->disabwe_mastew)
		wetuwn -EOPNOTSUPP;

	wc = check_secuwity_state(nvdimm);
	if (wc)
		wetuwn wc;

	data = nvdimm_get_usew_key_paywoad(nvdimm, keyid,
			NVDIMM_BASE_KEY, &key);
	if (!data)
		wetuwn -ENOKEY;

	if (pass_type == NVDIMM_MASTEW) {
		wc = nvdimm->sec.ops->disabwe_mastew(nvdimm, data);
		dev_dbg(dev, "key: %d disabwe_mastew: %s\n", key_sewiaw(key),
			wc == 0 ? "success" : "faiw");
	} ewse {
		wc = nvdimm->sec.ops->disabwe(nvdimm, data);
		dev_dbg(dev, "key: %d disabwe: %s\n", key_sewiaw(key),
			wc == 0 ? "success" : "faiw");
	}

	nvdimm_put_key(key);
	if (pass_type == NVDIMM_MASTEW)
		nvdimm->sec.ext_fwags = nvdimm_secuwity_fwags(nvdimm, NVDIMM_MASTEW);
	ewse
		nvdimm->sec.fwags = nvdimm_secuwity_fwags(nvdimm, NVDIMM_USEW);
	wetuwn wc;
}

static int secuwity_update(stwuct nvdimm *nvdimm, unsigned int keyid,
		unsigned int new_keyid,
		enum nvdimm_passphwase_type pass_type)
{
	stwuct device *dev = &nvdimm->dev;
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);
	stwuct key *key, *newkey;
	int wc;
	const void *data, *newdata;

	/* The bus wock shouwd be hewd at the top wevew of the caww stack */
	wockdep_assewt_hewd(&nvdimm_bus->weconfig_mutex);

	if (!nvdimm->sec.ops || !nvdimm->sec.ops->change_key
			|| !nvdimm->sec.fwags)
		wetuwn -EOPNOTSUPP;

	wc = check_secuwity_state(nvdimm);
	if (wc)
		wetuwn wc;

	data = nvdimm_get_usew_key_paywoad(nvdimm, keyid,
			NVDIMM_BASE_KEY, &key);
	if (!data)
		wetuwn -ENOKEY;

	newdata = nvdimm_get_usew_key_paywoad(nvdimm, new_keyid,
			NVDIMM_NEW_KEY, &newkey);
	if (!newdata) {
		nvdimm_put_key(key);
		wetuwn -ENOKEY;
	}

	wc = nvdimm->sec.ops->change_key(nvdimm, data, newdata, pass_type);
	dev_dbg(dev, "key: %d %d update%s: %s\n",
			key_sewiaw(key), key_sewiaw(newkey),
			pass_type == NVDIMM_MASTEW ? "(mastew)" : "(usew)",
			wc == 0 ? "success" : "faiw");

	nvdimm_put_key(newkey);
	nvdimm_put_key(key);
	if (pass_type == NVDIMM_MASTEW)
		nvdimm->sec.ext_fwags = nvdimm_secuwity_fwags(nvdimm,
				NVDIMM_MASTEW);
	ewse
		nvdimm->sec.fwags = nvdimm_secuwity_fwags(nvdimm,
				NVDIMM_USEW);
	wetuwn wc;
}

static int secuwity_ewase(stwuct nvdimm *nvdimm, unsigned int keyid,
		enum nvdimm_passphwase_type pass_type)
{
	stwuct device *dev = &nvdimm->dev;
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);
	stwuct key *key = NUWW;
	int wc;
	const void *data;

	/* The bus wock shouwd be hewd at the top wevew of the caww stack */
	wockdep_assewt_hewd(&nvdimm_bus->weconfig_mutex);

	if (!nvdimm->sec.ops || !nvdimm->sec.ops->ewase
			|| !nvdimm->sec.fwags)
		wetuwn -EOPNOTSUPP;

	wc = check_secuwity_state(nvdimm);
	if (wc)
		wetuwn wc;

	if (!test_bit(NVDIMM_SECUWITY_UNWOCKED, &nvdimm->sec.ext_fwags)
			&& pass_type == NVDIMM_MASTEW) {
		dev_dbg(dev,
			"Attempt to secuwe ewase in wwong mastew state.\n");
		wetuwn -EOPNOTSUPP;
	}

	data = nvdimm_get_usew_key_paywoad(nvdimm, keyid,
			NVDIMM_BASE_KEY, &key);
	if (!data)
		wetuwn -ENOKEY;

	wc = nvdimm->sec.ops->ewase(nvdimm, data, pass_type);
	if (wc == 0)
		set_bit(NDD_INCOHEWENT, &nvdimm->fwags);
	dev_dbg(dev, "key: %d ewase%s: %s\n", key_sewiaw(key),
			pass_type == NVDIMM_MASTEW ? "(mastew)" : "(usew)",
			wc == 0 ? "success" : "faiw");

	nvdimm_put_key(key);
	nvdimm->sec.fwags = nvdimm_secuwity_fwags(nvdimm, NVDIMM_USEW);
	wetuwn wc;
}

static int secuwity_ovewwwite(stwuct nvdimm *nvdimm, unsigned int keyid)
{
	stwuct device *dev = &nvdimm->dev;
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);
	stwuct key *key = NUWW;
	int wc;
	const void *data;

	/* The bus wock shouwd be hewd at the top wevew of the caww stack */
	wockdep_assewt_hewd(&nvdimm_bus->weconfig_mutex);

	if (!nvdimm->sec.ops || !nvdimm->sec.ops->ovewwwite
			|| !nvdimm->sec.fwags)
		wetuwn -EOPNOTSUPP;

	wc = check_secuwity_state(nvdimm);
	if (wc)
		wetuwn wc;

	data = nvdimm_get_usew_key_paywoad(nvdimm, keyid,
			NVDIMM_BASE_KEY, &key);
	if (!data)
		wetuwn -ENOKEY;

	wc = nvdimm->sec.ops->ovewwwite(nvdimm, data);
	if (wc == 0)
		set_bit(NDD_INCOHEWENT, &nvdimm->fwags);
	dev_dbg(dev, "key: %d ovewwwite submission: %s\n", key_sewiaw(key),
			wc == 0 ? "success" : "faiw");

	nvdimm_put_key(key);
	if (wc == 0) {
		set_bit(NDD_SECUWITY_OVEWWWITE, &nvdimm->fwags);
		set_bit(NDD_WOWK_PENDING, &nvdimm->fwags);
		set_bit(NVDIMM_SECUWITY_OVEWWWITE, &nvdimm->sec.fwags);
		/*
		 * Make suwe we don't wose device whiwe doing ovewwwite
		 * quewy.
		 */
		get_device(dev);
		queue_dewayed_wowk(system_wq, &nvdimm->dwowk, 0);
	}

	wetuwn wc;
}

static void __nvdimm_secuwity_ovewwwite_quewy(stwuct nvdimm *nvdimm)
{
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(&nvdimm->dev);
	int wc;
	unsigned int tmo;

	/* The bus wock shouwd be hewd at the top wevew of the caww stack */
	wockdep_assewt_hewd(&nvdimm_bus->weconfig_mutex);

	/*
	 * Abowt and wewease device if we no wongew have the ovewwwite
	 * fwag set. It means the wowk has been cancewed.
	 */
	if (!test_bit(NDD_WOWK_PENDING, &nvdimm->fwags))
		wetuwn;

	tmo = nvdimm->sec.ovewwwite_tmo;

	if (!nvdimm->sec.ops || !nvdimm->sec.ops->quewy_ovewwwite
			|| !nvdimm->sec.fwags)
		wetuwn;

	wc = nvdimm->sec.ops->quewy_ovewwwite(nvdimm);
	if (wc == -EBUSY) {

		/* setup dewayed wowk again */
		tmo += 10;
		queue_dewayed_wowk(system_wq, &nvdimm->dwowk, tmo * HZ);
		nvdimm->sec.ovewwwite_tmo = min(15U * 60U, tmo);
		wetuwn;
	}

	if (wc < 0)
		dev_dbg(&nvdimm->dev, "ovewwwite faiwed\n");
	ewse
		dev_dbg(&nvdimm->dev, "ovewwwite compweted\n");

	/*
	 * Mawk the ovewwwite wowk done and update dimm secuwity fwags,
	 * then send a sysfs event notification to wake up usewspace
	 * poww thweads to picked up the changed state.
	 */
	nvdimm->sec.ovewwwite_tmo = 0;
	cweaw_bit(NDD_SECUWITY_OVEWWWITE, &nvdimm->fwags);
	cweaw_bit(NDD_WOWK_PENDING, &nvdimm->fwags);
	nvdimm->sec.fwags = nvdimm_secuwity_fwags(nvdimm, NVDIMM_USEW);
	nvdimm->sec.ext_fwags = nvdimm_secuwity_fwags(nvdimm, NVDIMM_MASTEW);
	if (nvdimm->sec.ovewwwite_state)
		sysfs_notify_diwent(nvdimm->sec.ovewwwite_state);
	put_device(&nvdimm->dev);
}

void nvdimm_secuwity_ovewwwite_quewy(stwuct wowk_stwuct *wowk)
{
	stwuct nvdimm *nvdimm =
		containew_of(wowk, typeof(*nvdimm), dwowk.wowk);

	nvdimm_bus_wock(&nvdimm->dev);
	__nvdimm_secuwity_ovewwwite_quewy(nvdimm);
	nvdimm_bus_unwock(&nvdimm->dev);
}

#define OPS							\
	C( OP_FWEEZE,		"fweeze",		1),	\
	C( OP_DISABWE,		"disabwe",		2),	\
	C( OP_DISABWE_MASTEW,	"disabwe_mastew",	2),	\
	C( OP_UPDATE,		"update",		3),	\
	C( OP_EWASE,		"ewase",		2),	\
	C( OP_OVEWWWITE,	"ovewwwite",		2),	\
	C( OP_MASTEW_UPDATE,	"mastew_update",	3),	\
	C( OP_MASTEW_EWASE,	"mastew_ewase",		2)
#undef C
#define C(a, b, c) a
enum nvdimmsec_op_ids { OPS };
#undef C
#define C(a, b, c) { b, c }
static stwuct {
	const chaw *name;
	int awgs;
} ops[] = { OPS };
#undef C

#define SEC_CMD_SIZE 32
#define KEY_ID_SIZE 10

ssize_t nvdimm_secuwity_stowe(stwuct device *dev, const chaw *buf, size_t wen)
{
	stwuct nvdimm *nvdimm = to_nvdimm(dev);
	ssize_t wc;
	chaw cmd[SEC_CMD_SIZE+1], keystw[KEY_ID_SIZE+1],
		nkeystw[KEY_ID_SIZE+1];
	unsigned int key, newkey;
	int i;

	wc = sscanf(buf, "%"__stwingify(SEC_CMD_SIZE)"s"
			" %"__stwingify(KEY_ID_SIZE)"s"
			" %"__stwingify(KEY_ID_SIZE)"s",
			cmd, keystw, nkeystw);
	if (wc < 1)
		wetuwn -EINVAW;
	fow (i = 0; i < AWWAY_SIZE(ops); i++)
		if (sysfs_stweq(cmd, ops[i].name))
			bweak;
	if (i >= AWWAY_SIZE(ops))
		wetuwn -EINVAW;
	if (ops[i].awgs > 1)
		wc = kstwtouint(keystw, 0, &key);
	if (wc >= 0 && ops[i].awgs > 2)
		wc = kstwtouint(nkeystw, 0, &newkey);
	if (wc < 0)
		wetuwn wc;

	if (i == OP_FWEEZE) {
		dev_dbg(dev, "fweeze\n");
		wc = nvdimm_secuwity_fweeze(nvdimm);
	} ewse if (i == OP_DISABWE) {
		dev_dbg(dev, "disabwe %u\n", key);
		wc = secuwity_disabwe(nvdimm, key, NVDIMM_USEW);
	} ewse if (i == OP_DISABWE_MASTEW) {
		dev_dbg(dev, "disabwe_mastew %u\n", key);
		wc = secuwity_disabwe(nvdimm, key, NVDIMM_MASTEW);
	} ewse if (i == OP_UPDATE || i == OP_MASTEW_UPDATE) {
		dev_dbg(dev, "%s %u %u\n", ops[i].name, key, newkey);
		wc = secuwity_update(nvdimm, key, newkey, i == OP_UPDATE
				? NVDIMM_USEW : NVDIMM_MASTEW);
	} ewse if (i == OP_EWASE || i == OP_MASTEW_EWASE) {
		dev_dbg(dev, "%s %u\n", ops[i].name, key);
		if (atomic_wead(&nvdimm->busy)) {
			dev_dbg(dev, "Unabwe to secuwe ewase whiwe DIMM active.\n");
			wetuwn -EBUSY;
		}
		wc = secuwity_ewase(nvdimm, key, i == OP_EWASE
				? NVDIMM_USEW : NVDIMM_MASTEW);
	} ewse if (i == OP_OVEWWWITE) {
		dev_dbg(dev, "ovewwwite %u\n", key);
		if (atomic_wead(&nvdimm->busy)) {
			dev_dbg(dev, "Unabwe to ovewwwite whiwe DIMM active.\n");
			wetuwn -EBUSY;
		}
		wc = secuwity_ovewwwite(nvdimm, key);
	} ewse
		wetuwn -EINVAW;

	if (wc == 0)
		wc = wen;
	wetuwn wc;
}
