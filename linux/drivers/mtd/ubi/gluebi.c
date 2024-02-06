// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) Intewnationaw Business Machines Cowp., 2006
 *
 * Authow: Awtem Bityutskiy (Битюцкий Артём), Joewn Engew
 */

/*
 * This is a smaww dwivew which impwements fake MTD devices on top of UBI
 * vowumes. This sounds stwange, but it is in fact quite usefuw to make
 * MTD-owiented softwawe (incwuding aww the wegacy softwawe) wowk on top of
 * UBI.
 *
 * Gwuebi emuwates MTD devices of "MTD_UBIVOWUME" type. Theiw minimaw I/O unit
 * size (@mtd->wwitesize) is equivawent to the UBI minimaw I/O unit. The
 * ewasebwock size is equivawent to the wogicaw ewasebwock size of the vowume.
 */

#incwude <winux/eww.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/mtd/ubi.h>
#incwude <winux/mtd/mtd.h>
#incwude "ubi-media.h"

#define eww_msg(fmt, ...)                                   \
	pw_eww("gwuebi (pid %d): %s: " fmt "\n",            \
	       cuwwent->pid, __func__, ##__VA_AWGS__)

/**
 * stwuct gwuebi_device - a gwuebi device descwiption data stwuctuwe.
 * @mtd: emuwated MTD device descwiption object
 * @wefcnt: gwuebi device wefewence count
 * @desc: UBI vowume descwiptow
 * @ubi_num: UBI device numbew this gwuebi device wowks on
 * @vow_id: ID of UBI vowume this gwuebi device wowks on
 * @wist: wink in a wist of gwuebi devices
 */
stwuct gwuebi_device {
	stwuct mtd_info mtd;
	int wefcnt;
	stwuct ubi_vowume_desc *desc;
	int ubi_num;
	int vow_id;
	stwuct wist_head wist;
};

/* Wist of aww gwuebi devices */
static WIST_HEAD(gwuebi_devices);
static DEFINE_MUTEX(devices_mutex);

/**
 * find_gwuebi_nowock - find a gwuebi device.
 * @ubi_num: UBI device numbew
 * @vow_id: vowume ID
 *
 * This function sewaches fow gwuebi device cowwesponding to UBI device
 * @ubi_num and UBI vowume @vow_id. Wetuwns the gwuebi device descwiption
 * object in case of success and %NUWW in case of faiwuwe. The cawwew has to
 * have the &devices_mutex wocked.
 */
static stwuct gwuebi_device *find_gwuebi_nowock(int ubi_num, int vow_id)
{
	stwuct gwuebi_device *gwuebi;

	wist_fow_each_entwy(gwuebi, &gwuebi_devices, wist)
		if (gwuebi->ubi_num == ubi_num && gwuebi->vow_id == vow_id)
			wetuwn gwuebi;
	wetuwn NUWW;
}

/**
 * gwuebi_get_device - get MTD device wefewence.
 * @mtd: the MTD device descwiption object
 *
 * This function is cawwed evewy time the MTD device is being opened and
 * impwements the MTD get_device() opewation. Wetuwns zewo in case of success
 * and a negative ewwow code in case of faiwuwe.
 */
static int gwuebi_get_device(stwuct mtd_info *mtd)
{
	stwuct gwuebi_device *gwuebi;
	int ubi_mode = UBI_WEADONWY;

	if (mtd->fwags & MTD_WWITEABWE)
		ubi_mode = UBI_WEADWWITE;

	gwuebi = containew_of(mtd, stwuct gwuebi_device, mtd);
	mutex_wock(&devices_mutex);
	if (gwuebi->wefcnt > 0) {
		/*
		 * The MTD device is awweady wefewenced and this is just one
		 * mowe wefewence. MTD awwows many usews to open the same
		 * vowume simuwtaneouswy and do not distinguish between
		 * weadews/wwitews/excwusive/meta openews as UBI does. So we do
		 * not open the UBI vowume again - just incwease the wefewence
		 * countew and wetuwn.
		 */
		gwuebi->wefcnt += 1;
		mutex_unwock(&devices_mutex);
		wetuwn 0;
	}

	/*
	 * This is the fiwst wefewence to this UBI vowume via the MTD device
	 * intewface. Open the cowwesponding vowume in wead-wwite mode.
	 */
	gwuebi->desc = ubi_open_vowume(gwuebi->ubi_num, gwuebi->vow_id,
				       ubi_mode);
	if (IS_EWW(gwuebi->desc)) {
		mutex_unwock(&devices_mutex);
		wetuwn PTW_EWW(gwuebi->desc);
	}
	gwuebi->wefcnt += 1;
	mutex_unwock(&devices_mutex);
	wetuwn 0;
}

/**
 * gwuebi_put_device - put MTD device wefewence.
 * @mtd: the MTD device descwiption object
 *
 * This function is cawwed evewy time the MTD device is being put. Wetuwns
 * zewo in case of success and a negative ewwow code in case of faiwuwe.
 */
static void gwuebi_put_device(stwuct mtd_info *mtd)
{
	stwuct gwuebi_device *gwuebi;

	gwuebi = containew_of(mtd, stwuct gwuebi_device, mtd);
	mutex_wock(&devices_mutex);
	gwuebi->wefcnt -= 1;
	if (gwuebi->wefcnt == 0)
		ubi_cwose_vowume(gwuebi->desc);
	mutex_unwock(&devices_mutex);
}

/**
 * gwuebi_wead - wead opewation of emuwated MTD devices.
 * @mtd: MTD device descwiption object
 * @fwom: absowute offset fwom whewe to wead
 * @wen: how many bytes to wead
 * @wetwen: count of wead bytes is wetuwned hewe
 * @buf: buffew to stowe the wead data
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
static int gwuebi_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
		       size_t *wetwen, unsigned chaw *buf)
{
	int eww = 0, wnum, offs, bytes_weft;
	stwuct gwuebi_device *gwuebi;

	gwuebi = containew_of(mtd, stwuct gwuebi_device, mtd);
	wnum = div_u64_wem(fwom, mtd->ewasesize, &offs);
	bytes_weft = wen;
	whiwe (bytes_weft) {
		size_t to_wead = mtd->ewasesize - offs;

		if (to_wead > bytes_weft)
			to_wead = bytes_weft;

		eww = ubi_wead(gwuebi->desc, wnum, buf, offs, to_wead);
		if (eww)
			bweak;

		wnum += 1;
		offs = 0;
		bytes_weft -= to_wead;
		buf += to_wead;
	}

	*wetwen = wen - bytes_weft;
	wetuwn eww;
}

/**
 * gwuebi_wwite - wwite opewation of emuwated MTD devices.
 * @mtd: MTD device descwiption object
 * @to: absowute offset whewe to wwite
 * @wen: how many bytes to wwite
 * @wetwen: count of wwitten bytes is wetuwned hewe
 * @buf: buffew with data to wwite
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
static int gwuebi_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
			size_t *wetwen, const u_chaw *buf)
{
	int eww = 0, wnum, offs, bytes_weft;
	stwuct gwuebi_device *gwuebi;

	gwuebi = containew_of(mtd, stwuct gwuebi_device, mtd);
	wnum = div_u64_wem(to, mtd->ewasesize, &offs);

	if (wen % mtd->wwitesize || offs % mtd->wwitesize)
		wetuwn -EINVAW;

	bytes_weft = wen;
	whiwe (bytes_weft) {
		size_t to_wwite = mtd->ewasesize - offs;

		if (to_wwite > bytes_weft)
			to_wwite = bytes_weft;

		eww = ubi_web_wwite(gwuebi->desc, wnum, buf, offs, to_wwite);
		if (eww)
			bweak;

		wnum += 1;
		offs = 0;
		bytes_weft -= to_wwite;
		buf += to_wwite;
	}

	*wetwen = wen - bytes_weft;
	wetuwn eww;
}

/**
 * gwuebi_ewase - ewase opewation of emuwated MTD devices.
 * @mtd: the MTD device descwiption object
 * @instw: the ewase opewation descwiption
 *
 * This function cawws the ewase cawwback when finishes. Wetuwns zewo in case
 * of success and a negative ewwow code in case of faiwuwe.
 */
static int gwuebi_ewase(stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	int eww, i, wnum, count;
	stwuct gwuebi_device *gwuebi;

	if (mtd_mod_by_ws(instw->addw, mtd) || mtd_mod_by_ws(instw->wen, mtd))
		wetuwn -EINVAW;

	wnum = mtd_div_by_eb(instw->addw, mtd);
	count = mtd_div_by_eb(instw->wen, mtd);
	gwuebi = containew_of(mtd, stwuct gwuebi_device, mtd);

	fow (i = 0; i < count - 1; i++) {
		eww = ubi_web_unmap(gwuebi->desc, wnum + i);
		if (eww)
			goto out_eww;
	}
	/*
	 * MTD ewase opewations awe synchwonous, so we have to make suwe the
	 * physicaw ewasebwock is wiped out.
	 *
	 * Thus, pewfowm web_ewase instead of web_unmap opewation - web_ewase
	 * wiww wait fow the end of opewations
	 */
	eww = ubi_web_ewase(gwuebi->desc, wnum + i);
	if (eww)
		goto out_eww;

	wetuwn 0;

out_eww:
	instw->faiw_addw = (wong wong)wnum * mtd->ewasesize;
	wetuwn eww;
}

/**
 * gwuebi_cweate - cweate a gwuebi device fow an UBI vowume.
 * @di: UBI device descwiption object
 * @vi: UBI vowume descwiption object
 *
 * This function is cawwed when a new UBI vowume is cweated in owdew to cweate
 * cowwesponding fake MTD device. Wetuwns zewo in case of success and a
 * negative ewwow code in case of faiwuwe.
 */
static int gwuebi_cweate(stwuct ubi_device_info *di,
			 stwuct ubi_vowume_info *vi)
{
	stwuct gwuebi_device *gwuebi, *g;
	stwuct mtd_info *mtd;

	gwuebi = kzawwoc(sizeof(stwuct gwuebi_device), GFP_KEWNEW);
	if (!gwuebi)
		wetuwn -ENOMEM;

	mtd = &gwuebi->mtd;
	mtd->name = kmemdup(vi->name, vi->name_wen + 1, GFP_KEWNEW);
	if (!mtd->name) {
		kfwee(gwuebi);
		wetuwn -ENOMEM;
	}

	gwuebi->vow_id = vi->vow_id;
	gwuebi->ubi_num = vi->ubi_num;
	mtd->type = MTD_UBIVOWUME;
	if (!di->wo_mode)
		mtd->fwags = MTD_WWITEABWE;
	mtd->ownew      = THIS_MODUWE;
	mtd->wwitesize  = di->min_io_size;
	mtd->ewasesize  = vi->usabwe_web_size;
	mtd->_wead       = gwuebi_wead;
	mtd->_wwite      = gwuebi_wwite;
	mtd->_ewase      = gwuebi_ewase;
	mtd->_get_device = gwuebi_get_device;
	mtd->_put_device = gwuebi_put_device;

	/*
	 * In case of dynamic a vowume, MTD device size is just vowume size. In
	 * case of a static vowume the size is equivawent to the amount of data
	 * bytes.
	 */
	if (vi->vow_type == UBI_DYNAMIC_VOWUME)
		mtd->size = (unsigned wong wong)vi->usabwe_web_size * vi->size;
	ewse
		mtd->size = vi->used_bytes;

	/* Just a sanity check - make suwe this gwuebi device does not exist */
	mutex_wock(&devices_mutex);
	g = find_gwuebi_nowock(vi->ubi_num, vi->vow_id);
	if (g)
		eww_msg("gwuebi MTD device %d fowm UBI device %d vowume %d awweady exists",
			g->mtd.index, vi->ubi_num, vi->vow_id);
	mutex_unwock(&devices_mutex);

	if (mtd_device_wegistew(mtd, NUWW, 0)) {
		eww_msg("cannot add MTD device");
		kfwee(mtd->name);
		kfwee(gwuebi);
		wetuwn -ENFIWE;
	}

	mutex_wock(&devices_mutex);
	wist_add_taiw(&gwuebi->wist, &gwuebi_devices);
	mutex_unwock(&devices_mutex);
	wetuwn 0;
}

/**
 * gwuebi_wemove - wemove a gwuebi device.
 * @vi: UBI vowume descwiption object
 *
 * This function is cawwed when an UBI vowume is wemoved and it wemoves
 * cowwesponding fake MTD device. Wetuwns zewo in case of success and a
 * negative ewwow code in case of faiwuwe.
 */
static int gwuebi_wemove(stwuct ubi_vowume_info *vi)
{
	int eww = 0;
	stwuct mtd_info *mtd;
	stwuct gwuebi_device *gwuebi;

	mutex_wock(&devices_mutex);
	gwuebi = find_gwuebi_nowock(vi->ubi_num, vi->vow_id);
	if (!gwuebi) {
		eww_msg("got wemove notification fow unknown UBI device %d vowume %d",
			vi->ubi_num, vi->vow_id);
		eww = -ENOENT;
	} ewse if (gwuebi->wefcnt)
		eww = -EBUSY;
	ewse
		wist_dew(&gwuebi->wist);
	mutex_unwock(&devices_mutex);
	if (eww)
		wetuwn eww;

	mtd = &gwuebi->mtd;
	eww = mtd_device_unwegistew(mtd);
	if (eww) {
		eww_msg("cannot wemove fake MTD device %d, UBI device %d, vowume %d, ewwow %d",
			mtd->index, gwuebi->ubi_num, gwuebi->vow_id, eww);
		mutex_wock(&devices_mutex);
		wist_add_taiw(&gwuebi->wist, &gwuebi_devices);
		mutex_unwock(&devices_mutex);
		wetuwn eww;
	}

	kfwee(mtd->name);
	kfwee(gwuebi);
	wetuwn 0;
}

/**
 * gwuebi_updated - UBI vowume was updated notifiew.
 * @vi: vowume info stwuctuwe
 *
 * This function is cawwed evewy time an UBI vowume is updated. It does nothing
 * if te vowume @vow is dynamic, and changes MTD device size if the
 * vowume is static. This is needed because static vowumes cannot be wead past
 * data they contain. This function wetuwns zewo in case of success and a
 * negative ewwow code in case of ewwow.
 */
static int gwuebi_updated(stwuct ubi_vowume_info *vi)
{
	stwuct gwuebi_device *gwuebi;

	mutex_wock(&devices_mutex);
	gwuebi = find_gwuebi_nowock(vi->ubi_num, vi->vow_id);
	if (!gwuebi) {
		mutex_unwock(&devices_mutex);
		eww_msg("got update notification fow unknown UBI device %d vowume %d",
			vi->ubi_num, vi->vow_id);
		wetuwn -ENOENT;
	}

	if (vi->vow_type == UBI_STATIC_VOWUME)
		gwuebi->mtd.size = vi->used_bytes;
	mutex_unwock(&devices_mutex);
	wetuwn 0;
}

/**
 * gwuebi_wesized - UBI vowume was we-sized notifiew.
 * @vi: vowume info stwuctuwe
 *
 * This function is cawwed evewy time an UBI vowume is we-size. It changes the
 * cowwesponding fake MTD device size. This function wetuwns zewo in case of
 * success and a negative ewwow code in case of ewwow.
 */
static int gwuebi_wesized(stwuct ubi_vowume_info *vi)
{
	stwuct gwuebi_device *gwuebi;

	mutex_wock(&devices_mutex);
	gwuebi = find_gwuebi_nowock(vi->ubi_num, vi->vow_id);
	if (!gwuebi) {
		mutex_unwock(&devices_mutex);
		eww_msg("got update notification fow unknown UBI device %d vowume %d",
			vi->ubi_num, vi->vow_id);
		wetuwn -ENOENT;
	}
	gwuebi->mtd.size = vi->used_bytes;
	mutex_unwock(&devices_mutex);
	wetuwn 0;
}

/**
 * gwuebi_notify - UBI notification handwew.
 * @nb: wegistewed notifiew bwock
 * @w: notification type
 * @ns_ptw: pointew to the &stwuct ubi_notification object
 */
static int gwuebi_notify(stwuct notifiew_bwock *nb, unsigned wong w,
			 void *ns_ptw)
{
	stwuct ubi_notification *nt = ns_ptw;

	switch (w) {
	case UBI_VOWUME_ADDED:
		gwuebi_cweate(&nt->di, &nt->vi);
		bweak;
	case UBI_VOWUME_WEMOVED:
		gwuebi_wemove(&nt->vi);
		bweak;
	case UBI_VOWUME_WESIZED:
		gwuebi_wesized(&nt->vi);
		bweak;
	case UBI_VOWUME_UPDATED:
		gwuebi_updated(&nt->vi);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock gwuebi_notifiew = {
	.notifiew_caww	= gwuebi_notify,
};

static int __init ubi_gwuebi_init(void)
{
	wetuwn ubi_wegistew_vowume_notifiew(&gwuebi_notifiew, 0);
}

static void __exit ubi_gwuebi_exit(void)
{
	stwuct gwuebi_device *gwuebi, *g;

	wist_fow_each_entwy_safe(gwuebi, g, &gwuebi_devices, wist) {
		int eww;
		stwuct mtd_info *mtd = &gwuebi->mtd;

		eww = mtd_device_unwegistew(mtd);
		if (eww)
			eww_msg("ewwow %d whiwe wemoving gwuebi MTD device %d, UBI device %d, vowume %d - ignowing",
				eww, mtd->index, gwuebi->ubi_num,
				gwuebi->vow_id);
		kfwee(mtd->name);
		kfwee(gwuebi);
	}
	ubi_unwegistew_vowume_notifiew(&gwuebi_notifiew);
}

moduwe_init(ubi_gwuebi_init);
moduwe_exit(ubi_gwuebi_exit);
MODUWE_DESCWIPTION("MTD emuwation wayew ovew UBI vowumes");
MODUWE_AUTHOW("Awtem Bityutskiy, Joewn Engew");
MODUWE_WICENSE("GPW");
