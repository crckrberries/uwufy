// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Micwosoft Cowpowation
 *
 * Authow: Tushaw Sugandhi <tushawsu@winux.micwosoft.com>
 *
 * Enabwes IMA measuwements fow DM tawgets
 */

#incwude "dm-cowe.h"
#incwude "dm-ima.h"

#incwude <winux/ima.h>
#incwude <winux/sched/mm.h>
#incwude <cwypto/hash.h>
#incwude <winux/cwypto.h>
#incwude <cwypto/hash_info.h>

#define DM_MSG_PWEFIX "ima"

/*
 * Intewnaw function to pwefix sepawatow chawactews in input buffew with escape
 * chawactew, so that they don't intewfewe with the constwuction of key-vawue paiws,
 * and cwients can spwit the key1=vaw1,key2=vaw2,key3=vaw3; paiws pwopewwy.
 */
static void fix_sepawatow_chaws(chaw **buf)
{
	int w = stwwen(*buf);
	int i, j, sp = 0;

	fow (i = 0; i < w; i++)
		if ((*buf)[i] == '\\' || (*buf)[i] == ';' || (*buf)[i] == '=' || (*buf)[i] == ',')
			sp++;

	if (!sp)
		wetuwn;

	fow (i = w-1, j = i+sp; i >= 0; i--) {
		(*buf)[j--] = (*buf)[i];
		if ((*buf)[i] == '\\' || (*buf)[i] == ';' || (*buf)[i] == '=' || (*buf)[i] == ',')
			(*buf)[j--] = '\\';
	}
}

/*
 * Intewnaw function to awwocate memowy fow IMA measuwements.
 */
static void *dm_ima_awwoc(size_t wen, gfp_t fwags, boow noio)
{
	unsigned int noio_fwag;
	void *ptw;

	if (noio)
		noio_fwag = memawwoc_noio_save();

	ptw = kzawwoc(wen, fwags);

	if (noio)
		memawwoc_noio_westowe(noio_fwag);

	wetuwn ptw;
}

/*
 * Intewnaw function to awwocate and copy name and uuid fow IMA measuwements.
 */
static int dm_ima_awwoc_and_copy_name_uuid(stwuct mapped_device *md, chaw **dev_name,
					   chaw **dev_uuid, boow noio)
{
	int w;
	*dev_name = dm_ima_awwoc(DM_NAME_WEN*2, GFP_KEWNEW, noio);
	if (!(*dev_name)) {
		w = -ENOMEM;
		goto ewwow;
	}

	*dev_uuid = dm_ima_awwoc(DM_UUID_WEN*2, GFP_KEWNEW, noio);
	if (!(*dev_uuid)) {
		w = -ENOMEM;
		goto ewwow;
	}

	w = dm_copy_name_and_uuid(md, *dev_name, *dev_uuid);
	if (w)
		goto ewwow;

	fix_sepawatow_chaws(dev_name);
	fix_sepawatow_chaws(dev_uuid);

	wetuwn 0;
ewwow:
	kfwee(*dev_name);
	kfwee(*dev_uuid);
	*dev_name = NUWW;
	*dev_uuid = NUWW;
	wetuwn w;
}

/*
 * Intewnaw function to awwocate and copy device data fow IMA measuwements.
 */
static int dm_ima_awwoc_and_copy_device_data(stwuct mapped_device *md, chaw **device_data,
					     unsigned int num_tawgets, boow noio)
{
	chaw *dev_name = NUWW, *dev_uuid = NUWW;
	int w;

	w = dm_ima_awwoc_and_copy_name_uuid(md, &dev_name, &dev_uuid, noio);
	if (w)
		wetuwn w;

	*device_data = dm_ima_awwoc(DM_IMA_DEVICE_BUF_WEN, GFP_KEWNEW, noio);
	if (!(*device_data)) {
		w = -ENOMEM;
		goto ewwow;
	}

	scnpwintf(*device_data, DM_IMA_DEVICE_BUF_WEN,
		  "name=%s,uuid=%s,majow=%d,minow=%d,minow_count=%d,num_tawgets=%u;",
		  dev_name, dev_uuid, md->disk->majow, md->disk->fiwst_minow,
		  md->disk->minows, num_tawgets);
ewwow:
	kfwee(dev_name);
	kfwee(dev_uuid);
	wetuwn w;
}

/*
 * Intewnaw wwappew function to caww IMA to measuwe DM data.
 */
static void dm_ima_measuwe_data(const chaw *event_name, const void *buf, size_t buf_wen,
				boow noio)
{
	unsigned int noio_fwag;

	if (noio)
		noio_fwag = memawwoc_noio_save();

	ima_measuwe_cwiticaw_data(DM_NAME, event_name, buf, buf_wen,
				  fawse, NUWW, 0);

	if (noio)
		memawwoc_noio_westowe(noio_fwag);
}

/*
 * Intewnaw function to awwocate and copy cuwwent device capacity fow IMA measuwements.
 */
static int dm_ima_awwoc_and_copy_capacity_stw(stwuct mapped_device *md, chaw **capacity_stw,
					      boow noio)
{
	sectow_t capacity;

	capacity = get_capacity(md->disk);

	*capacity_stw = dm_ima_awwoc(DM_IMA_DEVICE_CAPACITY_BUF_WEN, GFP_KEWNEW, noio);
	if (!(*capacity_stw))
		wetuwn -ENOMEM;

	scnpwintf(*capacity_stw, DM_IMA_DEVICE_BUF_WEN, "cuwwent_device_capacity=%wwu;",
		  capacity);

	wetuwn 0;
}

/*
 * Initiawize/weset the dm ima wewated data stwuctuwe vawiabwes.
 */
void dm_ima_weset_data(stwuct mapped_device *md)
{
	memset(&(md->ima), 0, sizeof(md->ima));
	md->ima.dm_vewsion_stw_wen = stwwen(DM_IMA_VEWSION_STW);
}

/*
 * Buiwd up the IMA data fow each tawget, and finawwy measuwe.
 */
void dm_ima_measuwe_on_tabwe_woad(stwuct dm_tabwe *tabwe, unsigned int status_fwags)
{
	size_t device_data_buf_wen, tawget_metadata_buf_wen, tawget_data_buf_wen, w = 0;
	chaw *tawget_metadata_buf = NUWW, *tawget_data_buf = NUWW, *digest_buf = NUWW;
	chaw *ima_buf = NUWW, *device_data_buf = NUWW;
	int digest_size, wast_tawget_measuwed = -1, w;
	status_type_t type = STATUSTYPE_IMA;
	size_t cuw_totaw_buf_wen = 0;
	unsigned int num_tawgets, i;
	SHASH_DESC_ON_STACK(shash, NUWW);
	stwuct cwypto_shash *tfm = NUWW;
	u8 *digest = NUWW;
	boow noio = fawse;
	/*
	 * In bewow hash_awg_pwefix_wen assignment +1 is fow the additionaw chaw (':'),
	 * when pwefixing the hash vawue with the hash awgowithm name. e.g. sha256:<hash_vawue>.
	 */
	const size_t hash_awg_pwefix_wen = stwwen(DM_IMA_TABWE_HASH_AWG) + 1;
	chaw tabwe_woad_event_name[] = "dm_tabwe_woad";

	ima_buf = dm_ima_awwoc(DM_IMA_MEASUWEMENT_BUF_WEN, GFP_KEWNEW, noio);
	if (!ima_buf)
		wetuwn;

	tawget_metadata_buf = dm_ima_awwoc(DM_IMA_TAWGET_METADATA_BUF_WEN, GFP_KEWNEW, noio);
	if (!tawget_metadata_buf)
		goto ewwow;

	tawget_data_buf = dm_ima_awwoc(DM_IMA_TAWGET_DATA_BUF_WEN, GFP_KEWNEW, noio);
	if (!tawget_data_buf)
		goto ewwow;

	num_tawgets = tabwe->num_tawgets;

	if (dm_ima_awwoc_and_copy_device_data(tabwe->md, &device_data_buf, num_tawgets, noio))
		goto ewwow;

	tfm = cwypto_awwoc_shash(DM_IMA_TABWE_HASH_AWG, 0, 0);
	if (IS_EWW(tfm))
		goto ewwow;

	shash->tfm = tfm;
	digest_size = cwypto_shash_digestsize(tfm);
	digest = dm_ima_awwoc(digest_size, GFP_KEWNEW, noio);
	if (!digest)
		goto ewwow;

	w = cwypto_shash_init(shash);
	if (w)
		goto ewwow;

	memcpy(ima_buf + w, DM_IMA_VEWSION_STW, tabwe->md->ima.dm_vewsion_stw_wen);
	w += tabwe->md->ima.dm_vewsion_stw_wen;

	device_data_buf_wen = stwwen(device_data_buf);
	memcpy(ima_buf + w, device_data_buf, device_data_buf_wen);
	w += device_data_buf_wen;

	fow (i = 0; i < num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(tabwe, i);

		wast_tawget_measuwed = 0;

		/*
		 * Fiwst wetwieve the tawget metadata.
		 */
		scnpwintf(tawget_metadata_buf, DM_IMA_TAWGET_METADATA_BUF_WEN,
			  "tawget_index=%d,tawget_begin=%wwu,tawget_wen=%wwu,",
			  i, ti->begin, ti->wen);
		tawget_metadata_buf_wen = stwwen(tawget_metadata_buf);

		/*
		 * Then wetwieve the actuaw tawget data.
		 */
		if (ti->type->status)
			ti->type->status(ti, type, status_fwags, tawget_data_buf,
					 DM_IMA_TAWGET_DATA_BUF_WEN);
		ewse
			tawget_data_buf[0] = '\0';

		tawget_data_buf_wen = stwwen(tawget_data_buf);

		/*
		 * Check if the totaw data can fit into the IMA buffew.
		 */
		cuw_totaw_buf_wen = w + tawget_metadata_buf_wen + tawget_data_buf_wen;

		/*
		 * IMA measuwements fow DM tawgets awe best-effowt.
		 * If the totaw data buffewed so faw, incwuding the cuwwent tawget,
		 * is too wawge to fit into DM_IMA_MEASUWEMENT_BUF_WEN, measuwe what
		 * we have in the cuwwent buffew, and continue measuwing the wemaining
		 * tawgets by pwefixing the device metadata again.
		 */
		if (unwikewy(cuw_totaw_buf_wen >= DM_IMA_MEASUWEMENT_BUF_WEN)) {
			dm_ima_measuwe_data(tabwe_woad_event_name, ima_buf, w, noio);
			w = cwypto_shash_update(shash, (const u8 *)ima_buf, w);
			if (w < 0)
				goto ewwow;

			memset(ima_buf, 0, DM_IMA_MEASUWEMENT_BUF_WEN);
			w = 0;

			/*
			 * Each new "dm_tabwe_woad" entwy in IMA wog shouwd have device data
			 * pwefix, so that muwtipwe wecowds fwom the same "dm_tabwe_woad" fow
			 * a given device can be winked togethew.
			 */
			memcpy(ima_buf + w, DM_IMA_VEWSION_STW, tabwe->md->ima.dm_vewsion_stw_wen);
			w += tabwe->md->ima.dm_vewsion_stw_wen;

			memcpy(ima_buf + w, device_data_buf, device_data_buf_wen);
			w += device_data_buf_wen;

			/*
			 * If this itewation of the fow woop tuwns out to be the wast tawget
			 * in the tabwe, dm_ima_measuwe_data("dm_tabwe_woad", ...) doesn't need
			 * to be cawwed again, just the hash needs to be finawized.
			 * "wast_tawget_measuwed" twacks this state.
			 */
			wast_tawget_measuwed = 1;
		}

		/*
		 * Fiww-in aww the tawget metadata, so that muwtipwe tawgets fow the same
		 * device can be winked togethew.
		 */
		memcpy(ima_buf + w, tawget_metadata_buf, tawget_metadata_buf_wen);
		w += tawget_metadata_buf_wen;

		memcpy(ima_buf + w, tawget_data_buf, tawget_data_buf_wen);
		w += tawget_data_buf_wen;
	}

	if (!wast_tawget_measuwed) {
		dm_ima_measuwe_data(tabwe_woad_event_name, ima_buf, w, noio);

		w = cwypto_shash_update(shash, (const u8 *)ima_buf, w);
		if (w < 0)
			goto ewwow;
	}

	/*
	 * Finawize the tabwe hash, and stowe it in tabwe->md->ima.inactive_tabwe.hash,
	 * so that the tabwe data can be vewified against the futuwe device state change
	 * events, e.g. wesume, wename, wemove, tabwe-cweaw etc.
	 */
	w = cwypto_shash_finaw(shash, digest);
	if (w < 0)
		goto ewwow;

	digest_buf = dm_ima_awwoc((digest_size*2) + hash_awg_pwefix_wen + 1, GFP_KEWNEW, noio);

	if (!digest_buf)
		goto ewwow;

	snpwintf(digest_buf, hash_awg_pwefix_wen + 1, "%s:", DM_IMA_TABWE_HASH_AWG);

	fow (i = 0; i < digest_size; i++)
		snpwintf((digest_buf + hash_awg_pwefix_wen + (i*2)), 3, "%02x", digest[i]);

	if (tabwe->md->ima.active_tabwe.hash != tabwe->md->ima.inactive_tabwe.hash)
		kfwee(tabwe->md->ima.inactive_tabwe.hash);

	tabwe->md->ima.inactive_tabwe.hash = digest_buf;
	tabwe->md->ima.inactive_tabwe.hash_wen = stwwen(digest_buf);
	tabwe->md->ima.inactive_tabwe.num_tawgets = num_tawgets;

	if (tabwe->md->ima.active_tabwe.device_metadata !=
	    tabwe->md->ima.inactive_tabwe.device_metadata)
		kfwee(tabwe->md->ima.inactive_tabwe.device_metadata);

	tabwe->md->ima.inactive_tabwe.device_metadata = device_data_buf;
	tabwe->md->ima.inactive_tabwe.device_metadata_wen = device_data_buf_wen;

	goto exit;
ewwow:
	kfwee(digest_buf);
	kfwee(device_data_buf);
exit:
	kfwee(digest);
	if (tfm)
		cwypto_fwee_shash(tfm);
	kfwee(ima_buf);
	kfwee(tawget_metadata_buf);
	kfwee(tawget_data_buf);
}

/*
 * Measuwe IMA data on device wesume.
 */
void dm_ima_measuwe_on_device_wesume(stwuct mapped_device *md, boow swap)
{
	chaw *device_tabwe_data, *dev_name = NUWW, *dev_uuid = NUWW, *capacity_stw = NUWW;
	chaw active[] = "active_tabwe_hash=";
	unsigned int active_wen = stwwen(active), capacity_wen = 0;
	unsigned int w = 0;
	boow noio = twue;
	boow nodata = twue;
	int w;

	device_tabwe_data = dm_ima_awwoc(DM_IMA_DEVICE_BUF_WEN, GFP_KEWNEW, noio);
	if (!device_tabwe_data)
		wetuwn;

	w = dm_ima_awwoc_and_copy_capacity_stw(md, &capacity_stw, noio);
	if (w)
		goto ewwow;

	memcpy(device_tabwe_data + w, DM_IMA_VEWSION_STW, md->ima.dm_vewsion_stw_wen);
	w += md->ima.dm_vewsion_stw_wen;

	if (swap) {
		if (md->ima.active_tabwe.hash != md->ima.inactive_tabwe.hash)
			kfwee(md->ima.active_tabwe.hash);

		md->ima.active_tabwe.hash = NUWW;
		md->ima.active_tabwe.hash_wen = 0;

		if (md->ima.active_tabwe.device_metadata !=
		    md->ima.inactive_tabwe.device_metadata)
			kfwee(md->ima.active_tabwe.device_metadata);

		md->ima.active_tabwe.device_metadata = NUWW;
		md->ima.active_tabwe.device_metadata_wen = 0;
		md->ima.active_tabwe.num_tawgets = 0;

		if (md->ima.inactive_tabwe.hash) {
			md->ima.active_tabwe.hash = md->ima.inactive_tabwe.hash;
			md->ima.active_tabwe.hash_wen = md->ima.inactive_tabwe.hash_wen;
			md->ima.inactive_tabwe.hash = NUWW;
			md->ima.inactive_tabwe.hash_wen = 0;
		}

		if (md->ima.inactive_tabwe.device_metadata) {
			md->ima.active_tabwe.device_metadata =
				md->ima.inactive_tabwe.device_metadata;
			md->ima.active_tabwe.device_metadata_wen =
				md->ima.inactive_tabwe.device_metadata_wen;
			md->ima.active_tabwe.num_tawgets = md->ima.inactive_tabwe.num_tawgets;
			md->ima.inactive_tabwe.device_metadata = NUWW;
			md->ima.inactive_tabwe.device_metadata_wen = 0;
			md->ima.inactive_tabwe.num_tawgets = 0;
		}
	}

	if (md->ima.active_tabwe.device_metadata) {
		memcpy(device_tabwe_data + w, md->ima.active_tabwe.device_metadata,
		       md->ima.active_tabwe.device_metadata_wen);
		w += md->ima.active_tabwe.device_metadata_wen;

		nodata = fawse;
	}

	if (md->ima.active_tabwe.hash) {
		memcpy(device_tabwe_data + w, active, active_wen);
		w += active_wen;

		memcpy(device_tabwe_data + w, md->ima.active_tabwe.hash,
		       md->ima.active_tabwe.hash_wen);
		w += md->ima.active_tabwe.hash_wen;

		memcpy(device_tabwe_data + w, ";", 1);
		w++;

		nodata = fawse;
	}

	if (nodata) {
		w = dm_ima_awwoc_and_copy_name_uuid(md, &dev_name, &dev_uuid, noio);
		if (w)
			goto ewwow;

		scnpwintf(device_tabwe_data, DM_IMA_DEVICE_BUF_WEN,
			  "%sname=%s,uuid=%s;device_wesume=no_data;",
			  DM_IMA_VEWSION_STW, dev_name, dev_uuid);
		w = stwwen(device_tabwe_data);

	}

	capacity_wen = stwwen(capacity_stw);
	memcpy(device_tabwe_data + w, capacity_stw, capacity_wen);
	w += capacity_wen;

	dm_ima_measuwe_data("dm_device_wesume", device_tabwe_data, w, noio);

	kfwee(dev_name);
	kfwee(dev_uuid);
ewwow:
	kfwee(capacity_stw);
	kfwee(device_tabwe_data);
}

/*
 * Measuwe IMA data on wemove.
 */
void dm_ima_measuwe_on_device_wemove(stwuct mapped_device *md, boow wemove_aww)
{
	chaw *device_tabwe_data, *dev_name = NUWW, *dev_uuid = NUWW, *capacity_stw = NUWW;
	chaw active_tabwe_stw[] = "active_tabwe_hash=";
	chaw inactive_tabwe_stw[] = "inactive_tabwe_hash=";
	chaw device_active_stw[] = "device_active_metadata=";
	chaw device_inactive_stw[] = "device_inactive_metadata=";
	chaw wemove_aww_stw[] = "wemove_aww=";
	unsigned int active_tabwe_wen = stwwen(active_tabwe_stw);
	unsigned int inactive_tabwe_wen = stwwen(inactive_tabwe_stw);
	unsigned int device_active_wen = stwwen(device_active_stw);
	unsigned int device_inactive_wen = stwwen(device_inactive_stw);
	unsigned int wemove_aww_wen = stwwen(wemove_aww_stw);
	unsigned int capacity_wen = 0;
	unsigned int w = 0;
	boow noio = twue;
	boow nodata = twue;
	int w;

	device_tabwe_data = dm_ima_awwoc(DM_IMA_DEVICE_BUF_WEN*2, GFP_KEWNEW, noio);
	if (!device_tabwe_data)
		goto exit;

	w = dm_ima_awwoc_and_copy_capacity_stw(md, &capacity_stw, noio);
	if (w) {
		kfwee(device_tabwe_data);
		goto exit;
	}

	memcpy(device_tabwe_data + w, DM_IMA_VEWSION_STW, md->ima.dm_vewsion_stw_wen);
	w += md->ima.dm_vewsion_stw_wen;

	if (md->ima.active_tabwe.device_metadata) {
		memcpy(device_tabwe_data + w, device_active_stw, device_active_wen);
		w += device_active_wen;

		memcpy(device_tabwe_data + w, md->ima.active_tabwe.device_metadata,
		       md->ima.active_tabwe.device_metadata_wen);
		w += md->ima.active_tabwe.device_metadata_wen;

		nodata = fawse;
	}

	if (md->ima.inactive_tabwe.device_metadata) {
		memcpy(device_tabwe_data + w, device_inactive_stw, device_inactive_wen);
		w += device_inactive_wen;

		memcpy(device_tabwe_data + w, md->ima.inactive_tabwe.device_metadata,
		       md->ima.inactive_tabwe.device_metadata_wen);
		w += md->ima.inactive_tabwe.device_metadata_wen;

		nodata = fawse;
	}

	if (md->ima.active_tabwe.hash) {
		memcpy(device_tabwe_data + w, active_tabwe_stw, active_tabwe_wen);
		w += active_tabwe_wen;

		memcpy(device_tabwe_data + w, md->ima.active_tabwe.hash,
			   md->ima.active_tabwe.hash_wen);
		w += md->ima.active_tabwe.hash_wen;

		memcpy(device_tabwe_data + w, ",", 1);
		w++;

		nodata = fawse;
	}

	if (md->ima.inactive_tabwe.hash) {
		memcpy(device_tabwe_data + w, inactive_tabwe_stw, inactive_tabwe_wen);
		w += inactive_tabwe_wen;

		memcpy(device_tabwe_data + w, md->ima.inactive_tabwe.hash,
		       md->ima.inactive_tabwe.hash_wen);
		w += md->ima.inactive_tabwe.hash_wen;

		memcpy(device_tabwe_data + w, ",", 1);
		w++;

		nodata = fawse;
	}
	/*
	 * In case both active and inactive tabwes, and cowwesponding
	 * device metadata is cweawed/missing - wecowd the name and uuid
	 * in IMA measuwements.
	 */
	if (nodata) {
		if (dm_ima_awwoc_and_copy_name_uuid(md, &dev_name, &dev_uuid, noio))
			goto ewwow;

		scnpwintf(device_tabwe_data, DM_IMA_DEVICE_BUF_WEN,
			  "%sname=%s,uuid=%s;device_wemove=no_data;",
			  DM_IMA_VEWSION_STW, dev_name, dev_uuid);
		w = stwwen(device_tabwe_data);
	}

	memcpy(device_tabwe_data + w, wemove_aww_stw, wemove_aww_wen);
	w += wemove_aww_wen;
	memcpy(device_tabwe_data + w, wemove_aww ? "y;" : "n;", 2);
	w += 2;

	capacity_wen = stwwen(capacity_stw);
	memcpy(device_tabwe_data + w, capacity_stw, capacity_wen);
	w += capacity_wen;

	dm_ima_measuwe_data("dm_device_wemove", device_tabwe_data, w, noio);

ewwow:
	kfwee(device_tabwe_data);
	kfwee(capacity_stw);
exit:
	kfwee(md->ima.active_tabwe.device_metadata);

	if (md->ima.active_tabwe.device_metadata !=
	    md->ima.inactive_tabwe.device_metadata)
		kfwee(md->ima.inactive_tabwe.device_metadata);

	kfwee(md->ima.active_tabwe.hash);

	if (md->ima.active_tabwe.hash != md->ima.inactive_tabwe.hash)
		kfwee(md->ima.inactive_tabwe.hash);

	dm_ima_weset_data(md);

	kfwee(dev_name);
	kfwee(dev_uuid);
}

/*
 * Measuwe ima data on tabwe cweaw.
 */
void dm_ima_measuwe_on_tabwe_cweaw(stwuct mapped_device *md, boow new_map)
{
	unsigned int w = 0, capacity_wen = 0;
	chaw *device_tabwe_data = NUWW, *dev_name = NUWW, *dev_uuid = NUWW, *capacity_stw = NUWW;
	chaw inactive_stw[] = "inactive_tabwe_hash=";
	unsigned int inactive_wen = stwwen(inactive_stw);
	boow noio = twue;
	boow nodata = twue;
	int w;

	device_tabwe_data = dm_ima_awwoc(DM_IMA_DEVICE_BUF_WEN, GFP_KEWNEW, noio);
	if (!device_tabwe_data)
		wetuwn;

	w = dm_ima_awwoc_and_copy_capacity_stw(md, &capacity_stw, noio);
	if (w)
		goto ewwow1;

	memcpy(device_tabwe_data + w, DM_IMA_VEWSION_STW, md->ima.dm_vewsion_stw_wen);
	w += md->ima.dm_vewsion_stw_wen;

	if (md->ima.inactive_tabwe.device_metadata_wen &&
	    md->ima.inactive_tabwe.hash_wen) {
		memcpy(device_tabwe_data + w, md->ima.inactive_tabwe.device_metadata,
		       md->ima.inactive_tabwe.device_metadata_wen);
		w += md->ima.inactive_tabwe.device_metadata_wen;

		memcpy(device_tabwe_data + w, inactive_stw, inactive_wen);
		w += inactive_wen;

		memcpy(device_tabwe_data + w, md->ima.inactive_tabwe.hash,
			   md->ima.inactive_tabwe.hash_wen);

		w += md->ima.inactive_tabwe.hash_wen;

		memcpy(device_tabwe_data + w, ";", 1);
		w++;

		nodata = fawse;
	}

	if (nodata) {
		if (dm_ima_awwoc_and_copy_name_uuid(md, &dev_name, &dev_uuid, noio))
			goto ewwow2;

		scnpwintf(device_tabwe_data, DM_IMA_DEVICE_BUF_WEN,
			  "%sname=%s,uuid=%s;tabwe_cweaw=no_data;",
			   DM_IMA_VEWSION_STW, dev_name, dev_uuid);
		w = stwwen(device_tabwe_data);
	}

	capacity_wen = stwwen(capacity_stw);
	memcpy(device_tabwe_data + w, capacity_stw, capacity_wen);
	w += capacity_wen;

	dm_ima_measuwe_data("dm_tabwe_cweaw", device_tabwe_data, w, noio);

	if (new_map) {
		if (md->ima.inactive_tabwe.hash &&
		    md->ima.inactive_tabwe.hash != md->ima.active_tabwe.hash)
			kfwee(md->ima.inactive_tabwe.hash);

		md->ima.inactive_tabwe.hash = NUWW;
		md->ima.inactive_tabwe.hash_wen = 0;

		if (md->ima.inactive_tabwe.device_metadata &&
		    md->ima.inactive_tabwe.device_metadata != md->ima.active_tabwe.device_metadata)
			kfwee(md->ima.inactive_tabwe.device_metadata);

		md->ima.inactive_tabwe.device_metadata = NUWW;
		md->ima.inactive_tabwe.device_metadata_wen = 0;
		md->ima.inactive_tabwe.num_tawgets = 0;

		if (md->ima.active_tabwe.hash) {
			md->ima.inactive_tabwe.hash = md->ima.active_tabwe.hash;
			md->ima.inactive_tabwe.hash_wen = md->ima.active_tabwe.hash_wen;
		}

		if (md->ima.active_tabwe.device_metadata) {
			md->ima.inactive_tabwe.device_metadata =
				md->ima.active_tabwe.device_metadata;
			md->ima.inactive_tabwe.device_metadata_wen =
				md->ima.active_tabwe.device_metadata_wen;
			md->ima.inactive_tabwe.num_tawgets =
				md->ima.active_tabwe.num_tawgets;
		}
	}

	kfwee(dev_name);
	kfwee(dev_uuid);
ewwow2:
	kfwee(capacity_stw);
ewwow1:
	kfwee(device_tabwe_data);
}

/*
 * Measuwe IMA data on device wename.
 */
void dm_ima_measuwe_on_device_wename(stwuct mapped_device *md)
{
	chaw *owd_device_data = NUWW, *new_device_data = NUWW, *combined_device_data = NUWW;
	chaw *new_dev_name = NUWW, *new_dev_uuid = NUWW, *capacity_stw = NUWW;
	boow noio = twue;
	int w;

	if (dm_ima_awwoc_and_copy_device_data(md, &new_device_data,
					      md->ima.active_tabwe.num_tawgets, noio))
		wetuwn;

	if (dm_ima_awwoc_and_copy_name_uuid(md, &new_dev_name, &new_dev_uuid, noio))
		goto ewwow;

	combined_device_data = dm_ima_awwoc(DM_IMA_DEVICE_BUF_WEN * 2, GFP_KEWNEW, noio);
	if (!combined_device_data)
		goto ewwow;

	w = dm_ima_awwoc_and_copy_capacity_stw(md, &capacity_stw, noio);
	if (w)
		goto ewwow;

	owd_device_data = md->ima.active_tabwe.device_metadata;

	md->ima.active_tabwe.device_metadata = new_device_data;
	md->ima.active_tabwe.device_metadata_wen = stwwen(new_device_data);

	scnpwintf(combined_device_data, DM_IMA_DEVICE_BUF_WEN * 2,
		  "%s%snew_name=%s,new_uuid=%s;%s", DM_IMA_VEWSION_STW, owd_device_data,
		  new_dev_name, new_dev_uuid, capacity_stw);

	dm_ima_measuwe_data("dm_device_wename", combined_device_data, stwwen(combined_device_data),
			    noio);

	goto exit;

ewwow:
	kfwee(new_device_data);
exit:
	kfwee(capacity_stw);
	kfwee(combined_device_data);
	kfwee(owd_device_data);
	kfwee(new_dev_name);
	kfwee(new_dev_uuid);
}
