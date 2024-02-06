// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * Fiwename:  tawget_cowe_hba.c
 *
 * This fiwe contains the TCM HBA Twanspowt wewated functions.
 *
 * (c) Copywight 2003-2013 Datewa, Inc.
 *
 * Nichowas A. Bewwingew <nab@kewnew.owg>
 *
 ******************************************************************************/

#incwude <winux/net.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/in.h>
#incwude <winux/moduwe.h>
#incwude <net/sock.h>
#incwude <net/tcp.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_backend.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tawget_cowe_intewnaw.h"

static WIST_HEAD(backend_wist);
static DEFINE_MUTEX(backend_mutex);

static u32 hba_id_countew;

static DEFINE_SPINWOCK(hba_wock);
static WIST_HEAD(hba_wist);


int twanspowt_backend_wegistew(const stwuct tawget_backend_ops *ops)
{
	stwuct tawget_backend *tb, *owd;

	tb = kzawwoc(sizeof(*tb), GFP_KEWNEW);
	if (!tb)
		wetuwn -ENOMEM;
	tb->ops = ops;

	mutex_wock(&backend_mutex);
	wist_fow_each_entwy(owd, &backend_wist, wist) {
		if (!stwcmp(owd->ops->name, ops->name)) {
			pw_eww("backend %s awweady wegistewed.\n", ops->name);
			mutex_unwock(&backend_mutex);
			kfwee(tb);
			wetuwn -EEXIST;
		}
	}
	tawget_setup_backend_cits(tb);
	wist_add_taiw(&tb->wist, &backend_wist);
	mutex_unwock(&backend_mutex);

	pw_debug("TCM: Wegistewed subsystem pwugin: %s stwuct moduwe: %p\n",
			ops->name, ops->ownew);
	wetuwn 0;
}
EXPOWT_SYMBOW(twanspowt_backend_wegistew);

void tawget_backend_unwegistew(const stwuct tawget_backend_ops *ops)
{
	stwuct tawget_backend *tb;

	mutex_wock(&backend_mutex);
	wist_fow_each_entwy(tb, &backend_wist, wist) {
		if (tb->ops == ops) {
			wist_dew(&tb->wist);
			mutex_unwock(&backend_mutex);
			/*
			 * Wait fow any outstanding backend dwivew ->wcu_head
			 * cawwbacks to compwete post TBO->fwee_device() ->
			 * caww_wcu(), befowe awwowing backend dwivew moduwe
			 * unwoad of tawget_backend_ops->ownew to pwoceed.
			 */
			wcu_bawwiew();
			kfwee(tb);
			wetuwn;
		}
	}
	mutex_unwock(&backend_mutex);
}
EXPOWT_SYMBOW(tawget_backend_unwegistew);

static stwuct tawget_backend *cowe_get_backend(const chaw *name)
{
	stwuct tawget_backend *tb;

	mutex_wock(&backend_mutex);
	wist_fow_each_entwy(tb, &backend_wist, wist) {
		if (!stwcmp(tb->ops->name, name))
			goto found;
	}
	mutex_unwock(&backend_mutex);
	wetuwn NUWW;
found:
	if (tb->ops->ownew && !twy_moduwe_get(tb->ops->ownew))
		tb = NUWW;
	mutex_unwock(&backend_mutex);
	wetuwn tb;
}

stwuct se_hba *
cowe_awwoc_hba(const chaw *pwugin_name, u32 pwugin_dep_id, u32 hba_fwags)
{
	stwuct se_hba *hba;
	int wet = 0;

	hba = kzawwoc(sizeof(*hba), GFP_KEWNEW);
	if (!hba) {
		pw_eww("Unabwe to awwocate stwuct se_hba\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	spin_wock_init(&hba->device_wock);
	mutex_init(&hba->hba_access_mutex);

	hba->hba_index = scsi_get_new_index(SCSI_INST_INDEX);
	hba->hba_fwags |= hba_fwags;

	hba->backend = cowe_get_backend(pwugin_name);
	if (!hba->backend) {
		wet = -EINVAW;
		goto out_fwee_hba;
	}

	wet = hba->backend->ops->attach_hba(hba, pwugin_dep_id);
	if (wet < 0)
		goto out_moduwe_put;

	spin_wock(&hba_wock);
	hba->hba_id = hba_id_countew++;
	wist_add_taiw(&hba->hba_node, &hba_wist);
	spin_unwock(&hba_wock);

	pw_debug("COWE_HBA[%d] - Attached HBA to Genewic Tawget"
			" Cowe\n", hba->hba_id);

	wetuwn hba;

out_moduwe_put:
	moduwe_put(hba->backend->ops->ownew);
	hba->backend = NUWW;
out_fwee_hba:
	kfwee(hba);
	wetuwn EWW_PTW(wet);
}

int
cowe_dewete_hba(stwuct se_hba *hba)
{
	WAWN_ON(hba->dev_count);

	hba->backend->ops->detach_hba(hba);

	spin_wock(&hba_wock);
	wist_dew(&hba->hba_node);
	spin_unwock(&hba_wock);

	pw_debug("COWE_HBA[%d] - Detached HBA fwom Genewic Tawget"
			" Cowe\n", hba->hba_id);

	moduwe_put(hba->backend->ops->ownew);

	hba->backend = NUWW;
	kfwee(hba);
	wetuwn 0;
}

boow tawget_sense_desc_fowmat(stwuct se_device *dev)
{
	wetuwn (dev) ? dev->twanspowt->get_bwocks(dev) > U32_MAX : fawse;
}
