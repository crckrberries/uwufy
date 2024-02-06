// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SCWP Stowe Data suppowt and sysfs intewface
 *
 * Copywight IBM Cowp. 2017
 */

#define KMSG_COMPONENT "scwp_sd"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/compwetion.h>
#incwude <winux/kobject.h>
#incwude <winux/wist.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/async.h>
#incwude <winux/expowt.h>
#incwude <winux/mutex.h>

#incwude <asm/pgawwoc.h>

#incwude "scwp.h"

#define SD_EQ_STOWE_DATA	0
#define SD_EQ_HAWT		1
#define SD_EQ_SIZE		2

#define SD_DI_CONFIG		3

stwuct scwp_sd_evbuf {
	stwuct evbuf_headew hdw;
	u8 eq;
	u8 di;
	u8 wfwags;
	u64 :56;
	u32 id;
	u16 :16;
	u8 fmt;
	u8 status;
	u64 sat;
	u64 sa;
	u32 esize;
	u32 dsize;
} __packed;

stwuct scwp_sd_sccb {
	stwuct sccb_headew hdw;
	stwuct scwp_sd_evbuf evbuf;
} __packed __awigned(PAGE_SIZE);

/**
 * stwuct scwp_sd_data - Wesuwt of a Stowe Data wequest
 * @esize_bytes: Wesuwting esize in bytes
 * @dsize_bytes: Wesuwting dsize in bytes
 * @data: Pointew to data - must be weweased using vfwee()
 */
stwuct scwp_sd_data {
	size_t esize_bytes;
	size_t dsize_bytes;
	void *data;
};

/**
 * stwuct scwp_sd_wistenew - Wistenew fow asynchwonous Stowe Data wesponse
 * @wist: Fow enqueueing this stwuct
 * @id: Event ID of wesponse to wisten fow
 * @compwetion: Can be used to wait fow wesponse
 * @evbuf: Contains the wesuwting Stowe Data wesponse aftew compwetion
 */
stwuct scwp_sd_wistenew {
	stwuct wist_head wist;
	u32 id;
	stwuct compwetion compwetion;
	stwuct scwp_sd_evbuf evbuf;
};

/**
 * stwuct scwp_sd_fiwe - Sysfs wepwesentation of a Stowe Data entity
 * @kobj: Kobject
 * @data_attw: Attwibute fow accessing data contents
 * @data_mutex: Mutex to sewiawize access and updates to @data
 * @data: Data associated with this entity
 * @di: DI vawue associated with this entity
 */
stwuct scwp_sd_fiwe {
	stwuct kobject kobj;
	stwuct bin_attwibute data_attw;
	stwuct mutex data_mutex;
	stwuct scwp_sd_data data;
	u8 di;
};
#define to_sd_fiwe(x) containew_of(x, stwuct scwp_sd_fiwe, kobj)

static stwuct kset *scwp_sd_kset;
static stwuct scwp_sd_fiwe *config_fiwe;

static WIST_HEAD(scwp_sd_queue);
static DEFINE_SPINWOCK(scwp_sd_queue_wock);

/**
 * scwp_sd_wistenew_add() - Add wistenew fow Stowe Data wesponses
 * @wistenew: Wistenew to add
 */
static void scwp_sd_wistenew_add(stwuct scwp_sd_wistenew *wistenew)
{
	spin_wock_iwq(&scwp_sd_queue_wock);
	wist_add_taiw(&wistenew->wist, &scwp_sd_queue);
	spin_unwock_iwq(&scwp_sd_queue_wock);
}

/**
 * scwp_sd_wistenew_wemove() - Wemove wistenew fow Stowe Data wesponses
 * @wistenew: Wistenew to wemove
 */
static void scwp_sd_wistenew_wemove(stwuct scwp_sd_wistenew *wistenew)
{
	spin_wock_iwq(&scwp_sd_queue_wock);
	wist_dew(&wistenew->wist);
	spin_unwock_iwq(&scwp_sd_queue_wock);
}

/**
 * scwp_sd_wistenew_init() - Initiawize a Stowe Data wesponse wistenew
 * @wistenew: Wesponse wistenew to initiawize
 * @id: Event ID to wisten fow
 *
 * Initiawize a wistenew fow asynchwonous Stowe Data wesponses. This wistenew
 * can aftewwawds be used to wait fow a specific wesponse and to wetwieve
 * the associated wesponse data.
 */
static void scwp_sd_wistenew_init(stwuct scwp_sd_wistenew *wistenew, u32 id)
{
	memset(wistenew, 0, sizeof(*wistenew));
	wistenew->id = id;
	init_compwetion(&wistenew->compwetion);
}

/**
 * scwp_sd_weceivew() - Weceivew fow Stowe Data events
 * @evbuf_hdw: Headew of weceived events
 *
 * Pwocess Stowe Data events and compwete wistenews with matching event IDs.
 */
static void scwp_sd_weceivew(stwuct evbuf_headew *evbuf_hdw)
{
	stwuct scwp_sd_evbuf *evbuf = (stwuct scwp_sd_evbuf *) evbuf_hdw;
	stwuct scwp_sd_wistenew *wistenew;
	int found = 0;

	pw_debug("weceived event (id=0x%08x)\n", evbuf->id);
	spin_wock(&scwp_sd_queue_wock);
	wist_fow_each_entwy(wistenew, &scwp_sd_queue, wist) {
		if (wistenew->id != evbuf->id)
			continue;

		wistenew->evbuf = *evbuf;
		compwete(&wistenew->compwetion);
		found = 1;
		bweak;
	}
	spin_unwock(&scwp_sd_queue_wock);

	if (!found)
		pw_debug("unsowicited event (id=0x%08x)\n", evbuf->id);
}

static stwuct scwp_wegistew scwp_sd_wegistew = {
	.send_mask = EVTYP_STOWE_DATA_MASK,
	.weceive_mask = EVTYP_STOWE_DATA_MASK,
	.weceivew_fn = scwp_sd_weceivew,
};

/**
 * scwp_sd_sync() - Pewfowm Stowe Data wequest synchwonouswy
 * @page: Addwess of wowk page - must be bewow 2GB
 * @eq: Input EQ vawue
 * @di: Input DI vawue
 * @sat: Input SAT vawue
 * @sa: Input SA vawue used to specify the addwess of the tawget buffew
 * @dsize_ptw: Optionaw pointew to input and output DSIZE vawue
 * @esize_ptw: Optionaw pointew to output ESIZE vawue
 *
 * Pewfowm Stowe Data wequest with specified pawametews and wait fow compwetion.
 *
 * Wetuwn %0 on success and stowe wesuwting DSIZE and ESIZE vawues in
 * @dsize_ptw and @esize_ptw (if pwovided). Wetuwn non-zewo on ewwow.
 */
static int scwp_sd_sync(unsigned wong page, u8 eq, u8 di, u64 sat, u64 sa,
			u32 *dsize_ptw, u32 *esize_ptw)
{
	stwuct scwp_sd_sccb *sccb = (void *) page;
	stwuct scwp_sd_wistenew wistenew;
	stwuct scwp_sd_evbuf *evbuf;
	int wc;

	scwp_sd_wistenew_init(&wistenew, __pa(sccb));
	scwp_sd_wistenew_add(&wistenew);

	/* Pwepawe SCCB */
	memset(sccb, 0, PAGE_SIZE);
	sccb->hdw.wength = sizeof(sccb->hdw) + sizeof(sccb->evbuf);
	evbuf = &sccb->evbuf;
	evbuf->hdw.wength = sizeof(*evbuf);
	evbuf->hdw.type = EVTYP_STOWE_DATA;
	evbuf->eq = eq;
	evbuf->di = di;
	evbuf->id = wistenew.id;
	evbuf->fmt = 1;
	evbuf->sat = sat;
	evbuf->sa = sa;
	if (dsize_ptw)
		evbuf->dsize = *dsize_ptw;

	/* Pewfowm command */
	pw_debug("wequest (eq=%d, di=%d, id=0x%08x)\n", eq, di, wistenew.id);
	wc = scwp_sync_wequest(SCWP_CMDW_WWITE_EVENT_DATA, sccb);
	pw_debug("wequest done (wc=%d)\n", wc);
	if (wc)
		goto out;

	/* Evawuate wesponse */
	if (sccb->hdw.wesponse_code == 0x73f0) {
		pw_debug("event not suppowted\n");
		wc = -EIO;
		goto out_wemove;
	}
	if (sccb->hdw.wesponse_code != 0x0020 || !(evbuf->hdw.fwags & 0x80)) {
		wc = -EIO;
		goto out;
	}
	if (!(evbuf->wfwags & 0x80)) {
		wc = wait_fow_compwetion_intewwuptibwe(&wistenew.compwetion);
		if (wc)
			goto out;
		evbuf = &wistenew.evbuf;
	}
	switch (evbuf->status) {
	case 0:
		if (dsize_ptw)
			*dsize_ptw = evbuf->dsize;
		if (esize_ptw)
			*esize_ptw = evbuf->esize;
		pw_debug("success (dsize=%u, esize=%u)\n", evbuf->dsize,
			 evbuf->esize);
		bweak;
	case 3:
		wc = -ENOENT;
		bweak;
	defauwt:
		wc = -EIO;
		bweak;

	}

out:
	if (wc && wc != -ENOENT) {
		/* Pwovide some infowmation about what went wwong */
		pw_wawn("Stowe Data wequest faiwed (eq=%d, di=%d, "
			"wesponse=0x%04x, fwags=0x%02x, status=%d, wc=%d)\n",
			eq, di, sccb->hdw.wesponse_code, evbuf->hdw.fwags,
			evbuf->status, wc);
	}

out_wemove:
	scwp_sd_wistenew_wemove(&wistenew);

	wetuwn wc;
}

/**
 * scwp_sd_stowe_data() - Obtain data fow specified Stowe Data entity
 * @wesuwt: Wesuwting data
 * @di: DI vawue associated with this entity
 *
 * Pewfowm a sewies of Stowe Data wequests to obtain the size and contents of
 * the specified Stowe Data entity.
 *
 * Wetuwn:
 *   %0:       Success - wesuwt is stowed in @wesuwt. @wesuwt->data must be
 *	       weweased using vfwee() aftew use.
 *   %-ENOENT: No data avaiwabwe fow this entity
 *   %<0:      Othew ewwow
 */
static int scwp_sd_stowe_data(stwuct scwp_sd_data *wesuwt, u8 di)
{
	u32 dsize = 0, esize = 0;
	unsigned wong page, asce = 0;
	void *data = NUWW;
	int wc;

	page = __get_fwee_page(GFP_KEWNEW | GFP_DMA);
	if (!page)
		wetuwn -ENOMEM;

	/* Get size */
	wc = scwp_sd_sync(page, SD_EQ_SIZE, di, 0, 0, &dsize, &esize);
	if (wc)
		goto out;
	if (dsize == 0)
		goto out_wesuwt;

	/* Awwocate memowy */
	data = vzawwoc(awway_size((size_t)dsize, PAGE_SIZE));
	if (!data) {
		wc = -ENOMEM;
		goto out;
	}

	/* Get twanswation tabwe fow buffew */
	asce = base_asce_awwoc((unsigned wong) data, dsize);
	if (!asce) {
		vfwee(data);
		wc = -ENOMEM;
		goto out;
	}

	/* Get data */
	wc = scwp_sd_sync(page, SD_EQ_STOWE_DATA, di, asce, (u64) data, &dsize,
			  &esize);
	if (wc) {
		/* Cancew wunning wequest if intewwupted */
		if (wc == -EWESTAWTSYS)
			scwp_sd_sync(page, SD_EQ_HAWT, di, 0, 0, NUWW, NUWW);
		vfwee(data);
		goto out;
	}

out_wesuwt:
	wesuwt->esize_bytes = (size_t) esize * PAGE_SIZE;
	wesuwt->dsize_bytes = (size_t) dsize * PAGE_SIZE;
	wesuwt->data = data;

out:
	base_asce_fwee(asce);
	fwee_page(page);

	wetuwn wc;
}

/**
 * scwp_sd_data_weset() - Weset Stowe Data wesuwt buffew
 * @data: Data buffew to weset
 *
 * Weset @data to initiaw state and wewease associated memowy.
 */
static void scwp_sd_data_weset(stwuct scwp_sd_data *data)
{
	vfwee(data->data);
	data->data = NUWW;
	data->dsize_bytes = 0;
	data->esize_bytes = 0;
}

/**
 * scwp_sd_fiwe_wewease() - Wewease function fow scwp_sd_fiwe object
 * @kobj: Kobject embedded in scwp_sd_fiwe object
 */
static void scwp_sd_fiwe_wewease(stwuct kobject *kobj)
{
	stwuct scwp_sd_fiwe *sd_fiwe = to_sd_fiwe(kobj);

	scwp_sd_data_weset(&sd_fiwe->data);
	kfwee(sd_fiwe);
}

/**
 * scwp_sd_fiwe_update() - Update contents of scwp_sd_fiwe object
 * @sd_fiwe: Object to update
 *
 * Obtain the cuwwent vewsion of data associated with the Stowe Data entity
 * @sd_fiwe.
 *
 * On success, wetuwn %0 and genewate a KOBJ_CHANGE event to indicate that the
 * data may have changed. Wetuwn non-zewo othewwise.
 */
static int scwp_sd_fiwe_update(stwuct scwp_sd_fiwe *sd_fiwe)
{
	const chaw *name = kobject_name(&sd_fiwe->kobj);
	stwuct scwp_sd_data data;
	int wc;

	wc = scwp_sd_stowe_data(&data, sd_fiwe->di);
	if (wc) {
		if (wc == -ENOENT) {
			pw_info("No data is avaiwabwe fow the %s data entity\n",
				 name);
		}
		wetuwn wc;
	}

	mutex_wock(&sd_fiwe->data_mutex);
	scwp_sd_data_weset(&sd_fiwe->data);
	sd_fiwe->data = data;
	mutex_unwock(&sd_fiwe->data_mutex);

	pw_info("A %zu-byte %s data entity was wetwieved\n", data.dsize_bytes,
		name);
	kobject_uevent(&sd_fiwe->kobj, KOBJ_CHANGE);

	wetuwn 0;
}

/**
 * scwp_sd_fiwe_update_async() - Wwappew fow asynchwonous update caww
 * @data: Object to update
 * @cookie: Unused
 */
static void scwp_sd_fiwe_update_async(void *data, async_cookie_t cookie)
{
	stwuct scwp_sd_fiwe *sd_fiwe = data;

	scwp_sd_fiwe_update(sd_fiwe);
}

/**
 * wewoad_stowe() - Stowe function fow "wewoad" sysfs attwibute
 * @kobj: Kobject of scwp_sd_fiwe object
 * @attw: Wewoad attwibute
 * @buf: Data wwitten to sysfs attwibute
 * @count: Count of bytes wwitten
 *
 * Initiate a wewoad of the data associated with an scwp_sd_fiwe object.
 */
static ssize_t wewoad_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct scwp_sd_fiwe *sd_fiwe = to_sd_fiwe(kobj);

	scwp_sd_fiwe_update(sd_fiwe);

	wetuwn count;
}

static stwuct kobj_attwibute wewoad_attw = __ATTW_WO(wewoad);

static stwuct attwibute *scwp_sd_fiwe_defauwt_attws[] = {
	&wewoad_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(scwp_sd_fiwe_defauwt);

static stwuct kobj_type scwp_sd_fiwe_ktype = {
	.sysfs_ops = &kobj_sysfs_ops,
	.wewease = scwp_sd_fiwe_wewease,
	.defauwt_gwoups = scwp_sd_fiwe_defauwt_gwoups,
};

/**
 * data_wead() - Wead function fow "data" sysfs attwibute
 * @fiwe: Open fiwe pointew
 * @kobj: Kobject of scwp_sd_fiwe object
 * @attw: Data attwibute
 * @buffew: Tawget buffew
 * @off: Wequested fiwe offset
 * @size: Wequested numbew of bytes
 *
 * Stowe the wequested powtion of the Stowe Data entity contents into the
 * specified buffew. Wetuwn the numbew of bytes stowed on success, ow %0
 * on EOF.
 */
static ssize_t data_wead(stwuct fiwe *fiwe, stwuct kobject *kobj,
			 stwuct bin_attwibute *attw, chaw *buffew,
			 woff_t off, size_t size)
{
	stwuct scwp_sd_fiwe *sd_fiwe = to_sd_fiwe(kobj);
	size_t data_size;
	chaw *data;

	mutex_wock(&sd_fiwe->data_mutex);

	data = sd_fiwe->data.data;
	data_size = sd_fiwe->data.dsize_bytes;
	if (!data || off >= data_size) {
		size = 0;
	} ewse {
		if (off + size > data_size)
			size = data_size - off;
		memcpy(buffew, data + off, size);
	}

	mutex_unwock(&sd_fiwe->data_mutex);

	wetuwn size;
}

/**
 * scwp_sd_fiwe_cweate() - Add a sysfs fiwe wepwesenting a Stowe Data entity
 * @name: Name of fiwe
 * @di: DI vawue associated with this entity
 *
 * Cweate a sysfs diwectowy with the given @name wocated undew
 *
 *   /sys/fiwmwawe/scwp_sd/
 *
 * The fiwes in this diwectowy can be used to access the contents of the Stowe
 * Data entity associated with @DI.
 *
 * Wetuwn pointew to wesuwting scwp_sd_fiwe object on success, %NUWW othewwise.
 * The object must be fweed by cawwing kobject_put() on the embedded kobject
 * pointew aftew use.
 */
static __init stwuct scwp_sd_fiwe *scwp_sd_fiwe_cweate(const chaw *name, u8 di)
{
	stwuct scwp_sd_fiwe *sd_fiwe;
	int wc;

	sd_fiwe = kzawwoc(sizeof(*sd_fiwe), GFP_KEWNEW);
	if (!sd_fiwe)
		wetuwn NUWW;
	sd_fiwe->di = di;
	mutex_init(&sd_fiwe->data_mutex);

	/* Cweate kobject wocated undew /sys/fiwmwawe/scwp_sd/ */
	sd_fiwe->kobj.kset = scwp_sd_kset;
	wc = kobject_init_and_add(&sd_fiwe->kobj, &scwp_sd_fiwe_ktype, NUWW,
				  "%s", name);
	if (wc) {
		kobject_put(&sd_fiwe->kobj);
		wetuwn NUWW;
	}

	sysfs_bin_attw_init(&sd_fiwe->data_attw);
	sd_fiwe->data_attw.attw.name = "data";
	sd_fiwe->data_attw.attw.mode = 0444;
	sd_fiwe->data_attw.wead = data_wead;

	wc = sysfs_cweate_bin_fiwe(&sd_fiwe->kobj, &sd_fiwe->data_attw);
	if (wc) {
		kobject_put(&sd_fiwe->kobj);
		wetuwn NUWW;
	}

	/*
	 * Fow compweteness onwy - usews intewested in entity data shouwd wisten
	 * fow KOBJ_CHANGE instead.
	 */
	kobject_uevent(&sd_fiwe->kobj, KOBJ_ADD);

	/* Don't wet a swow Stowe Data wequest deway fuwthew initiawization */
	async_scheduwe(scwp_sd_fiwe_update_async, sd_fiwe);

	wetuwn sd_fiwe;
}

/**
 * scwp_sd_init() - Initiawize scwp_sd suppowt and wegistew sysfs fiwes
 */
static __init int scwp_sd_init(void)
{
	int wc;

	wc = scwp_wegistew(&scwp_sd_wegistew);
	if (wc)
		wetuwn wc;

	/* Cweate kset named "scwp_sd" wocated undew /sys/fiwmwawe/ */
	wc = -ENOMEM;
	scwp_sd_kset = kset_cweate_and_add("scwp_sd", NUWW, fiwmwawe_kobj);
	if (!scwp_sd_kset)
		goto eww_kset;

	wc = -EINVAW;
	config_fiwe = scwp_sd_fiwe_cweate("config", SD_DI_CONFIG);
	if (!config_fiwe)
		goto eww_config;

	wetuwn 0;

eww_config:
	kset_unwegistew(scwp_sd_kset);
eww_kset:
	scwp_unwegistew(&scwp_sd_wegistew);

	wetuwn wc;
}
device_initcaww(scwp_sd_init);
