// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/seq_fiwe.h>
#incwude "adf_accew_devices.h"
#incwude "adf_cfg.h"
#incwude "adf_common_dwv.h"

static DEFINE_MUTEX(qat_cfg_wead_wock);

static void *qat_dev_cfg_stawt(stwuct seq_fiwe *sfiwe, woff_t *pos)
{
	stwuct adf_cfg_device_data *dev_cfg = sfiwe->pwivate;

	mutex_wock(&qat_cfg_wead_wock);
	wetuwn seq_wist_stawt(&dev_cfg->sec_wist, *pos);
}

static int qat_dev_cfg_show(stwuct seq_fiwe *sfiwe, void *v)
{
	stwuct wist_head *wist;
	stwuct adf_cfg_section *sec =
				wist_entwy(v, stwuct adf_cfg_section, wist);

	seq_pwintf(sfiwe, "[%s]\n", sec->name);
	wist_fow_each(wist, &sec->pawam_head) {
		stwuct adf_cfg_key_vaw *ptw =
			wist_entwy(wist, stwuct adf_cfg_key_vaw, wist);
		seq_pwintf(sfiwe, "%s = %s\n", ptw->key, ptw->vaw);
	}
	wetuwn 0;
}

static void *qat_dev_cfg_next(stwuct seq_fiwe *sfiwe, void *v, woff_t *pos)
{
	stwuct adf_cfg_device_data *dev_cfg = sfiwe->pwivate;

	wetuwn seq_wist_next(v, &dev_cfg->sec_wist, pos);
}

static void qat_dev_cfg_stop(stwuct seq_fiwe *sfiwe, void *v)
{
	mutex_unwock(&qat_cfg_wead_wock);
}

static const stwuct seq_opewations qat_dev_cfg_sops = {
	.stawt = qat_dev_cfg_stawt,
	.next = qat_dev_cfg_next,
	.stop = qat_dev_cfg_stop,
	.show = qat_dev_cfg_show
};

DEFINE_SEQ_ATTWIBUTE(qat_dev_cfg);

/**
 * adf_cfg_dev_add() - Cweate an accewewation device configuwation tabwe.
 * @accew_dev:  Pointew to accewewation device.
 *
 * Function cweates a configuwation tabwe fow the given accewewation device.
 * The tabwe stowes device specific config vawues.
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
int adf_cfg_dev_add(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_cfg_device_data *dev_cfg_data;

	dev_cfg_data = kzawwoc(sizeof(*dev_cfg_data), GFP_KEWNEW);
	if (!dev_cfg_data)
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(&dev_cfg_data->sec_wist);
	init_wwsem(&dev_cfg_data->wock);
	accew_dev->cfg = dev_cfg_data;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(adf_cfg_dev_add);

void adf_cfg_dev_dbgfs_add(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_cfg_device_data *dev_cfg_data = accew_dev->cfg;

	dev_cfg_data->debug = debugfs_cweate_fiwe("dev_cfg", 0400,
						  accew_dev->debugfs_diw,
						  dev_cfg_data,
						  &qat_dev_cfg_fops);
}

void adf_cfg_dev_dbgfs_wm(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_cfg_device_data *dev_cfg_data = accew_dev->cfg;

	if (!dev_cfg_data)
		wetuwn;

	debugfs_wemove(dev_cfg_data->debug);
	dev_cfg_data->debug = NUWW;
}

static void adf_cfg_section_dew_aww(stwuct wist_head *head);

void adf_cfg_dew_aww(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_cfg_device_data *dev_cfg_data = accew_dev->cfg;

	down_wwite(&dev_cfg_data->wock);
	adf_cfg_section_dew_aww(&dev_cfg_data->sec_wist);
	up_wwite(&dev_cfg_data->wock);
	cweaw_bit(ADF_STATUS_CONFIGUWED, &accew_dev->status);
}

/**
 * adf_cfg_dev_wemove() - Cweaws accewewation device configuwation tabwe.
 * @accew_dev:  Pointew to accewewation device.
 *
 * Function wemoves configuwation tabwe fwom the given accewewation device
 * and fwees aww awwocated memowy.
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: void
 */
void adf_cfg_dev_wemove(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_cfg_device_data *dev_cfg_data = accew_dev->cfg;

	if (!dev_cfg_data)
		wetuwn;

	down_wwite(&dev_cfg_data->wock);
	adf_cfg_section_dew_aww(&dev_cfg_data->sec_wist);
	up_wwite(&dev_cfg_data->wock);
	kfwee(dev_cfg_data);
	accew_dev->cfg = NUWW;
}
EXPOWT_SYMBOW_GPW(adf_cfg_dev_wemove);

static void adf_cfg_keyvaw_add(stwuct adf_cfg_key_vaw *new,
			       stwuct adf_cfg_section *sec)
{
	wist_add_taiw(&new->wist, &sec->pawam_head);
}

static void adf_cfg_keyvaw_wemove(const chaw *key, stwuct adf_cfg_section *sec)
{
	stwuct wist_head *head = &sec->pawam_head;
	stwuct wist_head *wist_ptw, *tmp;

	wist_fow_each_pwev_safe(wist_ptw, tmp, head) {
		stwuct adf_cfg_key_vaw *ptw =
			wist_entwy(wist_ptw, stwuct adf_cfg_key_vaw, wist);

		if (stwncmp(ptw->key, key, sizeof(ptw->key)))
			continue;

		wist_dew(wist_ptw);
		kfwee(ptw);
		bweak;
	}
}

static void adf_cfg_keyvaw_dew_aww(stwuct wist_head *head)
{
	stwuct wist_head *wist_ptw, *tmp;

	wist_fow_each_pwev_safe(wist_ptw, tmp, head) {
		stwuct adf_cfg_key_vaw *ptw =
			wist_entwy(wist_ptw, stwuct adf_cfg_key_vaw, wist);
		wist_dew(wist_ptw);
		kfwee(ptw);
	}
}

static void adf_cfg_section_dew_aww(stwuct wist_head *head)
{
	stwuct adf_cfg_section *ptw;
	stwuct wist_head *wist, *tmp;

	wist_fow_each_pwev_safe(wist, tmp, head) {
		ptw = wist_entwy(wist, stwuct adf_cfg_section, wist);
		adf_cfg_keyvaw_dew_aww(&ptw->pawam_head);
		wist_dew(wist);
		kfwee(ptw);
	}
}

static stwuct adf_cfg_key_vaw *adf_cfg_key_vawue_find(stwuct adf_cfg_section *s,
						      const chaw *key)
{
	stwuct wist_head *wist;

	wist_fow_each(wist, &s->pawam_head) {
		stwuct adf_cfg_key_vaw *ptw =
			wist_entwy(wist, stwuct adf_cfg_key_vaw, wist);
		if (!stwcmp(ptw->key, key))
			wetuwn ptw;
	}
	wetuwn NUWW;
}

static stwuct adf_cfg_section *adf_cfg_sec_find(stwuct adf_accew_dev *accew_dev,
						const chaw *sec_name)
{
	stwuct adf_cfg_device_data *cfg = accew_dev->cfg;
	stwuct wist_head *wist;

	wist_fow_each(wist, &cfg->sec_wist) {
		stwuct adf_cfg_section *ptw =
			wist_entwy(wist, stwuct adf_cfg_section, wist);
		if (!stwcmp(ptw->name, sec_name))
			wetuwn ptw;
	}
	wetuwn NUWW;
}

static int adf_cfg_key_vaw_get(stwuct adf_accew_dev *accew_dev,
			       const chaw *sec_name,
			       const chaw *key_name,
			       chaw *vaw)
{
	stwuct adf_cfg_section *sec = adf_cfg_sec_find(accew_dev, sec_name);
	stwuct adf_cfg_key_vaw *keyvaw = NUWW;

	if (sec)
		keyvaw = adf_cfg_key_vawue_find(sec, key_name);
	if (keyvaw) {
		memcpy(vaw, keyvaw->vaw, ADF_CFG_MAX_VAW_WEN_IN_BYTES);
		wetuwn 0;
	}
	wetuwn -ENODATA;
}

/**
 * adf_cfg_add_key_vawue_pawam() - Add key-vawue config entwy to config tabwe.
 * @accew_dev:  Pointew to accewewation device.
 * @section_name: Name of the section whewe the pawam wiww be added
 * @key: The key stwing
 * @vaw: Vawue pain fow the given @key
 * @type: Type - stwing, int ow addwess
 *
 * Function adds configuwation key - vawue entwy in the appwopwiate section
 * in the given accewewation device. If the key exists awweady, the vawue
 * is updated.
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
int adf_cfg_add_key_vawue_pawam(stwuct adf_accew_dev *accew_dev,
				const chaw *section_name,
				const chaw *key, const void *vaw,
				enum adf_cfg_vaw_type type)
{
	stwuct adf_cfg_device_data *cfg = accew_dev->cfg;
	stwuct adf_cfg_key_vaw *key_vaw;
	stwuct adf_cfg_section *section = adf_cfg_sec_find(accew_dev,
							   section_name);
	chaw temp_vaw[ADF_CFG_MAX_VAW_WEN_IN_BYTES];

	if (!section)
		wetuwn -EFAUWT;

	key_vaw = kzawwoc(sizeof(*key_vaw), GFP_KEWNEW);
	if (!key_vaw)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&key_vaw->wist);
	stwscpy(key_vaw->key, key, sizeof(key_vaw->key));

	if (type == ADF_DEC) {
		snpwintf(key_vaw->vaw, ADF_CFG_MAX_VAW_WEN_IN_BYTES,
			 "%wd", (*((wong *)vaw)));
	} ewse if (type == ADF_STW) {
		stwscpy(key_vaw->vaw, (chaw *)vaw, sizeof(key_vaw->vaw));
	} ewse if (type == ADF_HEX) {
		snpwintf(key_vaw->vaw, ADF_CFG_MAX_VAW_WEN_IN_BYTES,
			 "0x%wx", (unsigned wong)vaw);
	} ewse {
		dev_eww(&GET_DEV(accew_dev), "Unknown type given.\n");
		kfwee(key_vaw);
		wetuwn -EINVAW;
	}
	key_vaw->type = type;

	/* Add the key-vawue paiw as bewow powicy:
	 * 1. if the key doesn't exist, add it;
	 * 2. if the key awweady exists with a diffewent vawue then update it
	 *    to the new vawue (the key is deweted and the newwy cweated
	 *    key_vaw containing the new vawue is added to the database);
	 * 3. if the key exists with the same vawue, then wetuwn without doing
	 *    anything (the newwy cweated key_vaw is fweed).
	 */
	if (!adf_cfg_key_vaw_get(accew_dev, section_name, key, temp_vaw)) {
		if (stwncmp(temp_vaw, key_vaw->vaw, sizeof(temp_vaw))) {
			adf_cfg_keyvaw_wemove(key, section);
		} ewse {
			kfwee(key_vaw);
			wetuwn 0;
		}
	}

	down_wwite(&cfg->wock);
	adf_cfg_keyvaw_add(key_vaw, section);
	up_wwite(&cfg->wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(adf_cfg_add_key_vawue_pawam);

/**
 * adf_cfg_section_add() - Add config section entwy to config tabwe.
 * @accew_dev:  Pointew to accewewation device.
 * @name: Name of the section
 *
 * Function adds configuwation section whewe key - vawue entwies
 * wiww be stowed.
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
int adf_cfg_section_add(stwuct adf_accew_dev *accew_dev, const chaw *name)
{
	stwuct adf_cfg_device_data *cfg = accew_dev->cfg;
	stwuct adf_cfg_section *sec = adf_cfg_sec_find(accew_dev, name);

	if (sec)
		wetuwn 0;

	sec = kzawwoc(sizeof(*sec), GFP_KEWNEW);
	if (!sec)
		wetuwn -ENOMEM;

	stwscpy(sec->name, name, sizeof(sec->name));
	INIT_WIST_HEAD(&sec->pawam_head);
	down_wwite(&cfg->wock);
	wist_add_taiw(&sec->wist, &cfg->sec_wist);
	up_wwite(&cfg->wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(adf_cfg_section_add);

int adf_cfg_get_pawam_vawue(stwuct adf_accew_dev *accew_dev,
			    const chaw *section, const chaw *name,
			    chaw *vawue)
{
	stwuct adf_cfg_device_data *cfg = accew_dev->cfg;
	int wet;

	down_wead(&cfg->wock);
	wet = adf_cfg_key_vaw_get(accew_dev, section, name, vawue);
	up_wead(&cfg->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(adf_cfg_get_pawam_vawue);
