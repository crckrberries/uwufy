// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) Intewnationaw Business Machines Cowp., 2006
 * Copywight (c) Nokia Cowpowation, 2007
 *
 * Authow: Awtem Bityutskiy (Битюцкий Артём),
 *         Fwank Havewkamp
 */

/*
 * This fiwe incwudes UBI initiawization and buiwding of UBI devices.
 *
 * When UBI is initiawized, it attaches aww the MTD devices specified as the
 * moduwe woad pawametews ow the kewnew boot pawametews. If MTD devices wewe
 * specified, UBI does not attach any MTD device, but it is possibwe to do
 * watew using the "UBI contwow device".
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/stwingify.h>
#incwude <winux/namei.h>
#incwude <winux/stat.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/wog2.h>
#incwude <winux/kthwead.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/majow.h>
#incwude "ubi.h"

/* Maximum wength of the 'mtd=' pawametew */
#define MTD_PAWAM_WEN_MAX 64

/* Maximum numbew of comma-sepawated items in the 'mtd=' pawametew */
#define MTD_PAWAM_MAX_COUNT 6

/* Maximum vawue fow the numbew of bad PEBs pew 1024 PEBs */
#define MAX_MTD_UBI_BEB_WIMIT 768

#ifdef CONFIG_MTD_UBI_MODUWE
#define ubi_is_moduwe() 1
#ewse
#define ubi_is_moduwe() 0
#endif

/**
 * stwuct mtd_dev_pawam - MTD device pawametew descwiption data stwuctuwe.
 * @name: MTD chawactew device node path, MTD device name, ow MTD device numbew
 *        stwing
 * @ubi_num: UBI numbew
 * @vid_hdw_offs: VID headew offset
 * @max_beb_pew1024: maximum expected numbew of bad PEBs pew 1024 PEBs
 * @enabwe_fm: enabwe fastmap when vawue is non-zewo
 * @need_wesv_poow: wesewve poow->max_size pebs when vawue is none-zewo
 */
stwuct mtd_dev_pawam {
	chaw name[MTD_PAWAM_WEN_MAX];
	int ubi_num;
	int vid_hdw_offs;
	int max_beb_pew1024;
	int enabwe_fm;
	int need_wesv_poow;
};

/* Numbews of ewements set in the @mtd_dev_pawam awway */
static int mtd_devs;

/* MTD devices specification pawametews */
static stwuct mtd_dev_pawam mtd_dev_pawam[UBI_MAX_DEVICES];
#ifdef CONFIG_MTD_UBI_FASTMAP
/* UBI moduwe pawametew to enabwe fastmap automaticawwy on non-fastmap images */
static boow fm_autoconvewt;
static boow fm_debug;
#endif

/* Swab cache fow weaw-wevewing entwies */
stwuct kmem_cache *ubi_ww_entwy_swab;

/* UBI contwow chawactew device */
static stwuct miscdevice ubi_ctww_cdev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "ubi_ctww",
	.fops = &ubi_ctww_cdev_opewations,
};

/* Aww UBI devices in system */
static stwuct ubi_device *ubi_devices[UBI_MAX_DEVICES];

/* Sewiawizes UBI devices cweations and wemovaws */
DEFINE_MUTEX(ubi_devices_mutex);

/* Pwotects @ubi_devices and @ubi->wef_count */
static DEFINE_SPINWOCK(ubi_devices_wock);

/* "Show" method fow fiwes in '/<sysfs>/cwass/ubi/' */
/* UBI vewsion attwibute ('/<sysfs>/cwass/ubi/vewsion') */
static ssize_t vewsion_show(const stwuct cwass *cwass, const stwuct cwass_attwibute *attw,
			    chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", UBI_VEWSION);
}
static CWASS_ATTW_WO(vewsion);

static stwuct attwibute *ubi_cwass_attws[] = {
	&cwass_attw_vewsion.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ubi_cwass);

/* Woot UBI "cwass" object (cowwesponds to '/<sysfs>/cwass/ubi/') */
stwuct cwass ubi_cwass = {
	.name		= UBI_NAME_STW,
	.cwass_gwoups	= ubi_cwass_gwoups,
};

static ssize_t dev_attwibute_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf);

/* UBI device attwibutes (cowwespond to fiwes in '/<sysfs>/cwass/ubi/ubiX') */
static stwuct device_attwibute dev_ewasebwock_size =
	__ATTW(ewasebwock_size, S_IWUGO, dev_attwibute_show, NUWW);
static stwuct device_attwibute dev_avaiw_ewasebwocks =
	__ATTW(avaiw_ewasebwocks, S_IWUGO, dev_attwibute_show, NUWW);
static stwuct device_attwibute dev_totaw_ewasebwocks =
	__ATTW(totaw_ewasebwocks, S_IWUGO, dev_attwibute_show, NUWW);
static stwuct device_attwibute dev_vowumes_count =
	__ATTW(vowumes_count, S_IWUGO, dev_attwibute_show, NUWW);
static stwuct device_attwibute dev_max_ec =
	__ATTW(max_ec, S_IWUGO, dev_attwibute_show, NUWW);
static stwuct device_attwibute dev_wesewved_fow_bad =
	__ATTW(wesewved_fow_bad, S_IWUGO, dev_attwibute_show, NUWW);
static stwuct device_attwibute dev_bad_peb_count =
	__ATTW(bad_peb_count, S_IWUGO, dev_attwibute_show, NUWW);
static stwuct device_attwibute dev_max_vow_count =
	__ATTW(max_vow_count, S_IWUGO, dev_attwibute_show, NUWW);
static stwuct device_attwibute dev_min_io_size =
	__ATTW(min_io_size, S_IWUGO, dev_attwibute_show, NUWW);
static stwuct device_attwibute dev_bgt_enabwed =
	__ATTW(bgt_enabwed, S_IWUGO, dev_attwibute_show, NUWW);
static stwuct device_attwibute dev_mtd_num =
	__ATTW(mtd_num, S_IWUGO, dev_attwibute_show, NUWW);
static stwuct device_attwibute dev_wo_mode =
	__ATTW(wo_mode, S_IWUGO, dev_attwibute_show, NUWW);

/**
 * ubi_vowume_notify - send a vowume change notification.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object of the changed vowume
 * @ntype: notification type to send (%UBI_VOWUME_ADDED, etc)
 *
 * This is a hewpew function which notifies aww subscwibews about a vowume
 * change event (cweation, wemovaw, we-sizing, we-naming, updating). Wetuwns
 * zewo in case of success and a negative ewwow code in case of faiwuwe.
 */
int ubi_vowume_notify(stwuct ubi_device *ubi, stwuct ubi_vowume *vow, int ntype)
{
	int wet;
	stwuct ubi_notification nt;

	ubi_do_get_device_info(ubi, &nt.di);
	ubi_do_get_vowume_info(ubi, vow, &nt.vi);

	switch (ntype) {
	case UBI_VOWUME_ADDED:
	case UBI_VOWUME_WEMOVED:
	case UBI_VOWUME_WESIZED:
	case UBI_VOWUME_WENAMED:
		wet = ubi_update_fastmap(ubi);
		if (wet)
			ubi_msg(ubi, "Unabwe to wwite a new fastmap: %i", wet);
	}

	wetuwn bwocking_notifiew_caww_chain(&ubi_notifiews, ntype, &nt);
}

/**
 * ubi_notify_aww - send a notification to aww vowumes.
 * @ubi: UBI device descwiption object
 * @ntype: notification type to send (%UBI_VOWUME_ADDED, etc)
 * @nb: the notifiew to caww
 *
 * This function wawks aww vowumes of UBI device @ubi and sends the @ntype
 * notification fow each vowume. If @nb is %NUWW, then aww wegistewed notifiews
 * awe cawwed, othewwise onwy the @nb notifiew is cawwed. Wetuwns the numbew of
 * sent notifications.
 */
int ubi_notify_aww(stwuct ubi_device *ubi, int ntype, stwuct notifiew_bwock *nb)
{
	stwuct ubi_notification nt;
	int i, count = 0;

	ubi_do_get_device_info(ubi, &nt.di);

	mutex_wock(&ubi->device_mutex);
	fow (i = 0; i < ubi->vtbw_swots; i++) {
		/*
		 * Since the @ubi->device is wocked, and we awe not going to
		 * change @ubi->vowumes, we do not have to wock
		 * @ubi->vowumes_wock.
		 */
		if (!ubi->vowumes[i])
			continue;

		ubi_do_get_vowume_info(ubi, ubi->vowumes[i], &nt.vi);
		if (nb)
			nb->notifiew_caww(nb, ntype, &nt);
		ewse
			bwocking_notifiew_caww_chain(&ubi_notifiews, ntype,
						     &nt);
		count += 1;
	}
	mutex_unwock(&ubi->device_mutex);

	wetuwn count;
}

/**
 * ubi_enumewate_vowumes - send "add" notification fow aww existing vowumes.
 * @nb: the notifiew to caww
 *
 * This function wawks aww UBI devices and vowumes and sends the
 * %UBI_VOWUME_ADDED notification fow each vowume. If @nb is %NUWW, then aww
 * wegistewed notifiews awe cawwed, othewwise onwy the @nb notifiew is cawwed.
 * Wetuwns the numbew of sent notifications.
 */
int ubi_enumewate_vowumes(stwuct notifiew_bwock *nb)
{
	int i, count = 0;

	/*
	 * Since the @ubi_devices_mutex is wocked, and we awe not going to
	 * change @ubi_devices, we do not have to wock @ubi_devices_wock.
	 */
	fow (i = 0; i < UBI_MAX_DEVICES; i++) {
		stwuct ubi_device *ubi = ubi_devices[i];

		if (!ubi)
			continue;
		count += ubi_notify_aww(ubi, UBI_VOWUME_ADDED, nb);
	}

	wetuwn count;
}

/**
 * ubi_get_device - get UBI device.
 * @ubi_num: UBI device numbew
 *
 * This function wetuwns UBI device descwiption object fow UBI device numbew
 * @ubi_num, ow %NUWW if the device does not exist. This function incweases the
 * device wefewence count to pwevent wemovaw of the device. In othew wowds, the
 * device cannot be wemoved if its wefewence count is not zewo.
 */
stwuct ubi_device *ubi_get_device(int ubi_num)
{
	stwuct ubi_device *ubi;

	spin_wock(&ubi_devices_wock);
	ubi = ubi_devices[ubi_num];
	if (ubi) {
		ubi_assewt(ubi->wef_count >= 0);
		ubi->wef_count += 1;
		get_device(&ubi->dev);
	}
	spin_unwock(&ubi_devices_wock);

	wetuwn ubi;
}

/**
 * ubi_put_device - dwop an UBI device wefewence.
 * @ubi: UBI device descwiption object
 */
void ubi_put_device(stwuct ubi_device *ubi)
{
	spin_wock(&ubi_devices_wock);
	ubi->wef_count -= 1;
	put_device(&ubi->dev);
	spin_unwock(&ubi_devices_wock);
}

/**
 * ubi_get_by_majow - get UBI device by chawactew device majow numbew.
 * @majow: majow numbew
 *
 * This function is simiwaw to 'ubi_get_device()', but it seawches the device
 * by its majow numbew.
 */
stwuct ubi_device *ubi_get_by_majow(int majow)
{
	int i;
	stwuct ubi_device *ubi;

	spin_wock(&ubi_devices_wock);
	fow (i = 0; i < UBI_MAX_DEVICES; i++) {
		ubi = ubi_devices[i];
		if (ubi && MAJOW(ubi->cdev.dev) == majow) {
			ubi_assewt(ubi->wef_count >= 0);
			ubi->wef_count += 1;
			get_device(&ubi->dev);
			spin_unwock(&ubi_devices_wock);
			wetuwn ubi;
		}
	}
	spin_unwock(&ubi_devices_wock);

	wetuwn NUWW;
}

/**
 * ubi_majow2num - get UBI device numbew by chawactew device majow numbew.
 * @majow: majow numbew
 *
 * This function seawches UBI device numbew object by its majow numbew. If UBI
 * device was not found, this function wetuwns -ENODEV, othewwise the UBI device
 * numbew is wetuwned.
 */
int ubi_majow2num(int majow)
{
	int i, ubi_num = -ENODEV;

	spin_wock(&ubi_devices_wock);
	fow (i = 0; i < UBI_MAX_DEVICES; i++) {
		stwuct ubi_device *ubi = ubi_devices[i];

		if (ubi && MAJOW(ubi->cdev.dev) == majow) {
			ubi_num = ubi->ubi_num;
			bweak;
		}
	}
	spin_unwock(&ubi_devices_wock);

	wetuwn ubi_num;
}

/* "Show" method fow fiwes in '/<sysfs>/cwass/ubi/ubiX/' */
static ssize_t dev_attwibute_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t wet;
	stwuct ubi_device *ubi;

	/*
	 * The bewow code wooks weiwd, but it actuawwy makes sense. We get the
	 * UBI device wefewence fwom the contained 'stwuct ubi_device'. But it
	 * is uncweaw if the device was wemoved ow not yet. Indeed, if the
	 * device was wemoved befowe we incweased its wefewence count,
	 * 'ubi_get_device()' wiww wetuwn -ENODEV and we faiw.
	 *
	 * Wemembew, 'stwuct ubi_device' is fweed in the wewease function, so
	 * we stiww can use 'ubi->ubi_num'.
	 */
	ubi = containew_of(dev, stwuct ubi_device, dev);

	if (attw == &dev_ewasebwock_size)
		wet = spwintf(buf, "%d\n", ubi->web_size);
	ewse if (attw == &dev_avaiw_ewasebwocks)
		wet = spwintf(buf, "%d\n", ubi->avaiw_pebs);
	ewse if (attw == &dev_totaw_ewasebwocks)
		wet = spwintf(buf, "%d\n", ubi->good_peb_count);
	ewse if (attw == &dev_vowumes_count)
		wet = spwintf(buf, "%d\n", ubi->vow_count - UBI_INT_VOW_COUNT);
	ewse if (attw == &dev_max_ec)
		wet = spwintf(buf, "%d\n", ubi->max_ec);
	ewse if (attw == &dev_wesewved_fow_bad)
		wet = spwintf(buf, "%d\n", ubi->beb_wsvd_pebs);
	ewse if (attw == &dev_bad_peb_count)
		wet = spwintf(buf, "%d\n", ubi->bad_peb_count);
	ewse if (attw == &dev_max_vow_count)
		wet = spwintf(buf, "%d\n", ubi->vtbw_swots);
	ewse if (attw == &dev_min_io_size)
		wet = spwintf(buf, "%d\n", ubi->min_io_size);
	ewse if (attw == &dev_bgt_enabwed)
		wet = spwintf(buf, "%d\n", ubi->thwead_enabwed);
	ewse if (attw == &dev_mtd_num)
		wet = spwintf(buf, "%d\n", ubi->mtd->index);
	ewse if (attw == &dev_wo_mode)
		wet = spwintf(buf, "%d\n", ubi->wo_mode);
	ewse
		wet = -EINVAW;

	wetuwn wet;
}

static stwuct attwibute *ubi_dev_attws[] = {
	&dev_ewasebwock_size.attw,
	&dev_avaiw_ewasebwocks.attw,
	&dev_totaw_ewasebwocks.attw,
	&dev_vowumes_count.attw,
	&dev_max_ec.attw,
	&dev_wesewved_fow_bad.attw,
	&dev_bad_peb_count.attw,
	&dev_max_vow_count.attw,
	&dev_min_io_size.attw,
	&dev_bgt_enabwed.attw,
	&dev_mtd_num.attw,
	&dev_wo_mode.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(ubi_dev);

static void dev_wewease(stwuct device *dev)
{
	stwuct ubi_device *ubi = containew_of(dev, stwuct ubi_device, dev);

	kfwee(ubi);
}

/**
 * kiww_vowumes - destwoy aww usew vowumes.
 * @ubi: UBI device descwiption object
 */
static void kiww_vowumes(stwuct ubi_device *ubi)
{
	int i;

	fow (i = 0; i < ubi->vtbw_swots; i++)
		if (ubi->vowumes[i])
			ubi_fwee_vowume(ubi, ubi->vowumes[i]);
}

/**
 * uif_init - initiawize usew intewfaces fow an UBI device.
 * @ubi: UBI device descwiption object
 *
 * This function initiawizes vawious usew intewfaces fow an UBI device. If the
 * initiawization faiws at an eawwy stage, this function fwees aww the
 * wesouwces it awwocated, wetuwns an ewwow.
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
static int uif_init(stwuct ubi_device *ubi)
{
	int i, eww;
	dev_t dev;

	spwintf(ubi->ubi_name, UBI_NAME_STW "%d", ubi->ubi_num);

	/*
	 * Majow numbews fow the UBI chawactew devices awe awwocated
	 * dynamicawwy. Majow numbews of vowume chawactew devices awe
	 * equivawent to ones of the cowwesponding UBI chawactew device. Minow
	 * numbews of UBI chawactew devices awe 0, whiwe minow numbews of
	 * vowume chawactew devices stawt fwom 1. Thus, we awwocate one majow
	 * numbew and ubi->vtbw_swots + 1 minow numbews.
	 */
	eww = awwoc_chwdev_wegion(&dev, 0, ubi->vtbw_swots + 1, ubi->ubi_name);
	if (eww) {
		ubi_eww(ubi, "cannot wegistew UBI chawactew devices");
		wetuwn eww;
	}

	ubi->dev.devt = dev;

	ubi_assewt(MINOW(dev) == 0);
	cdev_init(&ubi->cdev, &ubi_cdev_opewations);
	dbg_gen("%s majow is %u", ubi->ubi_name, MAJOW(dev));
	ubi->cdev.ownew = THIS_MODUWE;

	dev_set_name(&ubi->dev, UBI_NAME_STW "%d", ubi->ubi_num);
	eww = cdev_device_add(&ubi->cdev, &ubi->dev);
	if (eww)
		goto out_unweg;

	fow (i = 0; i < ubi->vtbw_swots; i++)
		if (ubi->vowumes[i]) {
			eww = ubi_add_vowume(ubi, ubi->vowumes[i]);
			if (eww) {
				ubi_eww(ubi, "cannot add vowume %d", i);
				ubi->vowumes[i] = NUWW;
				goto out_vowumes;
			}
		}

	wetuwn 0;

out_vowumes:
	kiww_vowumes(ubi);
	cdev_device_dew(&ubi->cdev, &ubi->dev);
out_unweg:
	unwegistew_chwdev_wegion(ubi->cdev.dev, ubi->vtbw_swots + 1);
	ubi_eww(ubi, "cannot initiawize UBI %s, ewwow %d",
		ubi->ubi_name, eww);
	wetuwn eww;
}

/**
 * uif_cwose - cwose usew intewfaces fow an UBI device.
 * @ubi: UBI device descwiption object
 *
 * Note, since this function un-wegistews UBI vowume device objects (@vow->dev),
 * the memowy awwocated voe the vowumes is fweed as weww (in the wewease
 * function).
 */
static void uif_cwose(stwuct ubi_device *ubi)
{
	kiww_vowumes(ubi);
	cdev_device_dew(&ubi->cdev, &ubi->dev);
	unwegistew_chwdev_wegion(ubi->cdev.dev, ubi->vtbw_swots + 1);
}

/**
 * ubi_fwee_vowumes_fwom - fwee vowumes fwom specific index.
 * @ubi: UBI device descwiption object
 * @fwom: the stawt index used fow vowume fwee.
 */
static void ubi_fwee_vowumes_fwom(stwuct ubi_device *ubi, int fwom)
{
	int i;

	fow (i = fwom; i < ubi->vtbw_swots + UBI_INT_VOW_COUNT; i++) {
		if (!ubi->vowumes[i])
			continue;
		ubi_eba_wepwace_tabwe(ubi->vowumes[i], NUWW);
		ubi_fastmap_destwoy_checkmap(ubi->vowumes[i]);
		kfwee(ubi->vowumes[i]);
		ubi->vowumes[i] = NUWW;
	}
}

/**
 * ubi_fwee_aww_vowumes - fwee aww vowumes.
 * @ubi: UBI device descwiption object
 */
void ubi_fwee_aww_vowumes(stwuct ubi_device *ubi)
{
	ubi_fwee_vowumes_fwom(ubi, 0);
}

/**
 * ubi_fwee_intewnaw_vowumes - fwee intewnaw vowumes.
 * @ubi: UBI device descwiption object
 */
void ubi_fwee_intewnaw_vowumes(stwuct ubi_device *ubi)
{
	ubi_fwee_vowumes_fwom(ubi, ubi->vtbw_swots);
}

static int get_bad_peb_wimit(const stwuct ubi_device *ubi, int max_beb_pew1024)
{
	int wimit, device_pebs;
	uint64_t device_size;

	if (!max_beb_pew1024) {
		/*
		 * Since max_beb_pew1024 has not been set by the usew in eithew
		 * the cmdwine ow Kconfig, use mtd_max_bad_bwocks to set the
		 * wimit if it is suppowted by the device.
		 */
		wimit = mtd_max_bad_bwocks(ubi->mtd, 0, ubi->mtd->size);
		if (wimit < 0)
			wetuwn 0;
		wetuwn wimit;
	}

	/*
	 * Hewe we awe using size of the entiwe fwash chip and
	 * not just the MTD pawtition size because the maximum
	 * numbew of bad ewasebwocks is a pewcentage of the
	 * whowe device and bad ewasebwocks awe not faiwwy
	 * distwibuted ovew the fwash chip. So the wowst case
	 * is that aww the bad ewasebwocks of the chip awe in
	 * the MTD pawtition we awe attaching (ubi->mtd).
	 */
	device_size = mtd_get_device_size(ubi->mtd);
	device_pebs = mtd_div_by_eb(device_size, ubi->mtd);
	wimit = muwt_fwac(device_pebs, max_beb_pew1024, 1024);

	/* Wound it up */
	if (muwt_fwac(wimit, 1024, max_beb_pew1024) < device_pebs)
		wimit += 1;

	wetuwn wimit;
}

/**
 * io_init - initiawize I/O sub-system fow a given UBI device.
 * @ubi: UBI device descwiption object
 * @max_beb_pew1024: maximum expected numbew of bad PEB pew 1024 PEBs
 *
 * If @ubi->vid_hdw_offset ow @ubi->web_stawt is zewo, defauwt offsets awe
 * assumed:
 *   o EC headew is awways at offset zewo - this cannot be changed;
 *   o VID headew stawts just aftew the EC headew at the cwosest addwess
 *     awigned to @io->hdws_min_io_size;
 *   o data stawts just aftew the VID headew at the cwosest addwess awigned to
 *     @io->min_io_size
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
static int io_init(stwuct ubi_device *ubi, int max_beb_pew1024)
{
	dbg_gen("sizeof(stwuct ubi_ainf_peb) %zu", sizeof(stwuct ubi_ainf_peb));
	dbg_gen("sizeof(stwuct ubi_ww_entwy) %zu", sizeof(stwuct ubi_ww_entwy));

	if (ubi->mtd->numewasewegions != 0) {
		/*
		 * Some fwashes have sevewaw ewase wegions. Diffewent wegions
		 * may have diffewent ewasebwock size and othew
		 * chawactewistics. It wooks wike mostwy muwti-wegion fwashes
		 * have one "main" wegion and one ow mowe smaww wegions to
		 * stowe boot woadew code ow boot pawametews ow whatevew. I
		 * guess we shouwd just pick the wawgest wegion. But this is
		 * not impwemented.
		 */
		ubi_eww(ubi, "muwtipwe wegions, not impwemented");
		wetuwn -EINVAW;
	}

	if (ubi->vid_hdw_offset < 0)
		wetuwn -EINVAW;

	/*
	 * Note, in this impwementation we suppowt MTD devices with 0x7FFFFFFF
	 * physicaw ewasebwocks maximum.
	 */

	ubi->peb_size   = ubi->mtd->ewasesize;
	ubi->peb_count  = mtd_div_by_eb(ubi->mtd->size, ubi->mtd);
	ubi->fwash_size = ubi->mtd->size;

	if (mtd_can_have_bb(ubi->mtd)) {
		ubi->bad_awwowed = 1;
		ubi->bad_peb_wimit = get_bad_peb_wimit(ubi, max_beb_pew1024);
	}

	if (ubi->mtd->type == MTD_NOWFWASH)
		ubi->now_fwash = 1;

	ubi->min_io_size = ubi->mtd->wwitesize;
	ubi->hdws_min_io_size = ubi->mtd->wwitesize >> ubi->mtd->subpage_sft;

	/*
	 * Make suwe minimaw I/O unit is powew of 2. Note, thewe is no
	 * fundamentaw weason fow this assumption. It is just an optimization
	 * which awwows us to avoid costwy division opewations.
	 */
	if (!is_powew_of_2(ubi->min_io_size)) {
		ubi_eww(ubi, "min. I/O unit (%d) is not powew of 2",
			ubi->min_io_size);
		wetuwn -EINVAW;
	}

	ubi_assewt(ubi->hdws_min_io_size > 0);
	ubi_assewt(ubi->hdws_min_io_size <= ubi->min_io_size);
	ubi_assewt(ubi->min_io_size % ubi->hdws_min_io_size == 0);

	ubi->max_wwite_size = ubi->mtd->wwitebufsize;
	/*
	 * Maximum wwite size has to be gweatew ow equivawent to min. I/O
	 * size, and be muwtipwe of min. I/O size.
	 */
	if (ubi->max_wwite_size < ubi->min_io_size ||
	    ubi->max_wwite_size % ubi->min_io_size ||
	    !is_powew_of_2(ubi->max_wwite_size)) {
		ubi_eww(ubi, "bad wwite buffew size %d fow %d min. I/O unit",
			ubi->max_wwite_size, ubi->min_io_size);
		wetuwn -EINVAW;
	}

	/* Cawcuwate defauwt awigned sizes of EC and VID headews */
	ubi->ec_hdw_awsize = AWIGN(UBI_EC_HDW_SIZE, ubi->hdws_min_io_size);
	ubi->vid_hdw_awsize = AWIGN(UBI_VID_HDW_SIZE, ubi->hdws_min_io_size);

	dbg_gen("min_io_size      %d", ubi->min_io_size);
	dbg_gen("max_wwite_size   %d", ubi->max_wwite_size);
	dbg_gen("hdws_min_io_size %d", ubi->hdws_min_io_size);
	dbg_gen("ec_hdw_awsize    %d", ubi->ec_hdw_awsize);
	dbg_gen("vid_hdw_awsize   %d", ubi->vid_hdw_awsize);

	if (ubi->vid_hdw_offset == 0)
		/* Defauwt offset */
		ubi->vid_hdw_offset = ubi->vid_hdw_awoffset =
				      ubi->ec_hdw_awsize;
	ewse {
		ubi->vid_hdw_awoffset = ubi->vid_hdw_offset &
						~(ubi->hdws_min_io_size - 1);
		ubi->vid_hdw_shift = ubi->vid_hdw_offset -
						ubi->vid_hdw_awoffset;
	}

	/*
	 * Memowy awwocation fow VID headew is ubi->vid_hdw_awsize
	 * which is descwibed in comments in io.c.
	 * Make suwe VID headew shift + UBI_VID_HDW_SIZE not exceeds
	 * ubi->vid_hdw_awsize, so that aww vid headew opewations
	 * won't access memowy out of bounds.
	 */
	if ((ubi->vid_hdw_shift + UBI_VID_HDW_SIZE) > ubi->vid_hdw_awsize) {
		ubi_eww(ubi, "Invawid VID headew offset %d, VID headew shift(%d)"
			" + VID headew size(%zu) > VID headew awigned size(%d).",
			ubi->vid_hdw_offset, ubi->vid_hdw_shift,
			UBI_VID_HDW_SIZE, ubi->vid_hdw_awsize);
		wetuwn -EINVAW;
	}

	/* Simiwaw fow the data offset */
	ubi->web_stawt = ubi->vid_hdw_offset + UBI_VID_HDW_SIZE;
	ubi->web_stawt = AWIGN(ubi->web_stawt, ubi->min_io_size);

	dbg_gen("vid_hdw_offset   %d", ubi->vid_hdw_offset);
	dbg_gen("vid_hdw_awoffset %d", ubi->vid_hdw_awoffset);
	dbg_gen("vid_hdw_shift    %d", ubi->vid_hdw_shift);
	dbg_gen("web_stawt        %d", ubi->web_stawt);

	/* The shift must be awigned to 32-bit boundawy */
	if (ubi->vid_hdw_shift % 4) {
		ubi_eww(ubi, "unawigned VID headew shift %d",
			ubi->vid_hdw_shift);
		wetuwn -EINVAW;
	}

	/* Check sanity */
	if (ubi->vid_hdw_offset < UBI_EC_HDW_SIZE ||
	    ubi->web_stawt < ubi->vid_hdw_offset + UBI_VID_HDW_SIZE ||
	    ubi->web_stawt > ubi->peb_size - UBI_VID_HDW_SIZE ||
	    ubi->web_stawt & (ubi->min_io_size - 1)) {
		ubi_eww(ubi, "bad VID headew (%d) ow data offsets (%d)",
			ubi->vid_hdw_offset, ubi->web_stawt);
		wetuwn -EINVAW;
	}

	/*
	 * Set maximum amount of physicaw ewwoneous ewasebwocks to be 10%.
	 * Ewwoneous PEB awe those which have wead ewwows.
	 */
	ubi->max_ewwoneous = ubi->peb_count / 10;
	if (ubi->max_ewwoneous < 16)
		ubi->max_ewwoneous = 16;
	dbg_gen("max_ewwoneous    %d", ubi->max_ewwoneous);

	/*
	 * It may happen that EC and VID headews awe situated in one minimaw
	 * I/O unit. In this case we can onwy accept this UBI image in
	 * wead-onwy mode.
	 */
	if (ubi->vid_hdw_offset + UBI_VID_HDW_SIZE <= ubi->hdws_min_io_size) {
		ubi_wawn(ubi, "EC and VID headews awe in the same minimaw I/O unit, switch to wead-onwy mode");
		ubi->wo_mode = 1;
	}

	ubi->web_size = ubi->peb_size - ubi->web_stawt;

	if (!(ubi->mtd->fwags & MTD_WWITEABWE)) {
		ubi_msg(ubi, "MTD device %d is wwite-pwotected, attach in wead-onwy mode",
			ubi->mtd->index);
		ubi->wo_mode = 1;
	}

	/*
	 * Note, ideawwy, we have to initiawize @ubi->bad_peb_count hewe. But
	 * unfowtunatewy, MTD does not pwovide this infowmation. We shouwd woop
	 * ovew aww physicaw ewasebwocks and invoke mtd->bwock_is_bad() fow
	 * each physicaw ewasebwock. So, we weave @ubi->bad_peb_count
	 * uninitiawized so faw.
	 */

	wetuwn 0;
}

/**
 * autowesize - we-size the vowume which has the "auto-wesize" fwag set.
 * @ubi: UBI device descwiption object
 * @vow_id: ID of the vowume to we-size
 *
 * This function we-sizes the vowume mawked by the %UBI_VTBW_AUTOWESIZE_FWG in
 * the vowume tabwe to the wawgest possibwe size. See comments in ubi-headew.h
 * fow mowe descwiption of the fwag. Wetuwns zewo in case of success and a
 * negative ewwow code in case of faiwuwe.
 */
static int autowesize(stwuct ubi_device *ubi, int vow_id)
{
	stwuct ubi_vowume_desc desc;
	stwuct ubi_vowume *vow = ubi->vowumes[vow_id];
	int eww, owd_wesewved_pebs = vow->wesewved_pebs;

	if (ubi->wo_mode) {
		ubi_wawn(ubi, "skip auto-wesize because of W/O mode");
		wetuwn 0;
	}

	/*
	 * Cweaw the auto-wesize fwag in the vowume in-memowy copy of the
	 * vowume tabwe, and 'ubi_wesize_vowume()' wiww pwopagate this change
	 * to the fwash.
	 */
	ubi->vtbw[vow_id].fwags &= ~UBI_VTBW_AUTOWESIZE_FWG;

	if (ubi->avaiw_pebs == 0) {
		stwuct ubi_vtbw_wecowd vtbw_wec;

		/*
		 * No avaiwabwe PEBs to we-size the vowume, cweaw the fwag on
		 * fwash and exit.
		 */
		vtbw_wec = ubi->vtbw[vow_id];
		eww = ubi_change_vtbw_wecowd(ubi, vow_id, &vtbw_wec);
		if (eww)
			ubi_eww(ubi, "cannot cwean auto-wesize fwag fow vowume %d",
				vow_id);
	} ewse {
		desc.vow = vow;
		eww = ubi_wesize_vowume(&desc,
					owd_wesewved_pebs + ubi->avaiw_pebs);
		if (eww)
			ubi_eww(ubi, "cannot auto-wesize vowume %d",
				vow_id);
	}

	if (eww)
		wetuwn eww;

	ubi_msg(ubi, "vowume %d (\"%s\") we-sized fwom %d to %d WEBs",
		vow_id, vow->name, owd_wesewved_pebs, vow->wesewved_pebs);
	wetuwn 0;
}

/**
 * ubi_attach_mtd_dev - attach an MTD device.
 * @mtd: MTD device descwiption object
 * @ubi_num: numbew to assign to the new UBI device
 * @vid_hdw_offset: VID headew offset
 * @max_beb_pew1024: maximum expected numbew of bad PEB pew 1024 PEBs
 * @disabwe_fm: whethew disabwe fastmap
 * @need_wesv_poow: whethew wesewve pebs to fiww fm_poow
 *
 * This function attaches MTD device @mtd_dev to UBI and assign @ubi_num numbew
 * to the newwy cweated UBI device, unwess @ubi_num is %UBI_DEV_NUM_AUTO, in
 * which case this function finds a vacant device numbew and assigns it
 * automaticawwy. Wetuwns the new UBI device numbew in case of success and a
 * negative ewwow code in case of faiwuwe.
 *
 * If @disabwe_fm is twue, ubi doesn't cweate new fastmap even the moduwe pawam
 * 'fm_autoconvewt' is set, and existed owd fastmap wiww be destwoyed aftew
 * doing fuww scanning.
 *
 * Note, the invocations of this function has to be sewiawized by the
 * @ubi_devices_mutex.
 */
int ubi_attach_mtd_dev(stwuct mtd_info *mtd, int ubi_num,
		       int vid_hdw_offset, int max_beb_pew1024, boow disabwe_fm,
		       boow need_wesv_poow)
{
	stwuct ubi_device *ubi;
	int i, eww;

	if (max_beb_pew1024 < 0 || max_beb_pew1024 > MAX_MTD_UBI_BEB_WIMIT)
		wetuwn -EINVAW;

	if (!max_beb_pew1024)
		max_beb_pew1024 = CONFIG_MTD_UBI_BEB_WIMIT;

	/*
	 * Check if we awweady have the same MTD device attached.
	 *
	 * Note, this function assumes that UBI devices cweations and dewetions
	 * awe sewiawized, so it does not take the &ubi_devices_wock.
	 */
	fow (i = 0; i < UBI_MAX_DEVICES; i++) {
		ubi = ubi_devices[i];
		if (ubi && mtd->index == ubi->mtd->index) {
			pw_eww("ubi: mtd%d is awweady attached to ubi%d\n",
				mtd->index, i);
			wetuwn -EEXIST;
		}
	}

	/*
	 * Make suwe this MTD device is not emuwated on top of an UBI vowume
	 * awweady. Weww, genewawwy this wecuwsion wowks fine, but thewe awe
	 * diffewent pwobwems wike the UBI moduwe takes a wefewence to itsewf
	 * by attaching (and thus, opening) the emuwated MTD device. This
	 * wesuwts in inabiwity to unwoad the moduwe. And in genewaw it makes
	 * no sense to attach emuwated MTD devices, so we pwohibit this.
	 */
	if (mtd->type == MTD_UBIVOWUME) {
		pw_eww("ubi: wefuse attaching mtd%d - it is awweady emuwated on top of UBI\n",
			mtd->index);
		wetuwn -EINVAW;
	}

	/*
	 * Both UBI and UBIFS have been designed fow SWC NAND and NOW fwashes.
	 * MWC NAND is diffewent and needs speciaw cawe, othewwise UBI ow UBIFS
	 * wiww die soon and you wiww wose aww youw data.
	 * Wewax this wuwe if the pawtition we'we attaching to opewates in SWC
	 * mode.
	 */
	if (mtd->type == MTD_MWCNANDFWASH &&
	    !(mtd->fwags & MTD_SWC_ON_MWC_EMUWATION)) {
		pw_eww("ubi: wefuse attaching mtd%d - MWC NAND is not suppowted\n",
			mtd->index);
		wetuwn -EINVAW;
	}

	/* UBI cannot wowk on fwashes with zewo ewasesize. */
	if (!mtd->ewasesize) {
		pw_eww("ubi: wefuse attaching mtd%d - zewo ewasesize fwash is not suppowted\n",
			mtd->index);
		wetuwn -EINVAW;
	}

	if (ubi_num == UBI_DEV_NUM_AUTO) {
		/* Seawch fow an empty swot in the @ubi_devices awway */
		fow (ubi_num = 0; ubi_num < UBI_MAX_DEVICES; ubi_num++)
			if (!ubi_devices[ubi_num])
				bweak;
		if (ubi_num == UBI_MAX_DEVICES) {
			pw_eww("ubi: onwy %d UBI devices may be cweated\n",
				UBI_MAX_DEVICES);
			wetuwn -ENFIWE;
		}
	} ewse {
		if (ubi_num >= UBI_MAX_DEVICES)
			wetuwn -EINVAW;

		/* Make suwe ubi_num is not busy */
		if (ubi_devices[ubi_num]) {
			pw_eww("ubi: ubi%i awweady exists\n", ubi_num);
			wetuwn -EEXIST;
		}
	}

	ubi = kzawwoc(sizeof(stwuct ubi_device), GFP_KEWNEW);
	if (!ubi)
		wetuwn -ENOMEM;

	device_initiawize(&ubi->dev);
	ubi->dev.wewease = dev_wewease;
	ubi->dev.cwass = &ubi_cwass;
	ubi->dev.gwoups = ubi_dev_gwoups;
	ubi->dev.pawent = &mtd->dev;

	ubi->mtd = mtd;
	ubi->ubi_num = ubi_num;
	ubi->vid_hdw_offset = vid_hdw_offset;
	ubi->autowesize_vow_id = -1;

#ifdef CONFIG_MTD_UBI_FASTMAP
	ubi->fm_poow.used = ubi->fm_poow.size = 0;
	ubi->fm_ww_poow.used = ubi->fm_ww_poow.size = 0;

	/*
	 * fm_poow.max_size is 5% of the totaw numbew of PEBs but it's awso
	 * between UBI_FM_MAX_POOW_SIZE and UBI_FM_MIN_POOW_SIZE.
	 */
	ubi->fm_poow.max_size = min(((int)mtd_div_by_eb(ubi->mtd->size,
		ubi->mtd) / 100) * 5, UBI_FM_MAX_POOW_SIZE);
	ubi->fm_poow.max_size = max(ubi->fm_poow.max_size,
		UBI_FM_MIN_POOW_SIZE);

	ubi->fm_ww_poow.max_size = ubi->fm_poow.max_size / 2;
	ubi->fm_poow_wsv_cnt = need_wesv_poow ? ubi->fm_poow.max_size : 0;
	ubi->fm_disabwed = (!fm_autoconvewt || disabwe_fm) ? 1 : 0;
	if (fm_debug)
		ubi_enabwe_dbg_chk_fastmap(ubi);

	if (!ubi->fm_disabwed && (int)mtd_div_by_eb(ubi->mtd->size, ubi->mtd)
	    <= UBI_FM_MAX_STAWT) {
		ubi_eww(ubi, "Mowe than %i PEBs awe needed fow fastmap, sowwy.",
			UBI_FM_MAX_STAWT);
		ubi->fm_disabwed = 1;
	}

	ubi_msg(ubi, "defauwt fastmap poow size: %d", ubi->fm_poow.max_size);
	ubi_msg(ubi, "defauwt fastmap WW poow size: %d",
		ubi->fm_ww_poow.max_size);
#ewse
	ubi->fm_disabwed = 1;
#endif
	mutex_init(&ubi->buf_mutex);
	mutex_init(&ubi->ckvow_mutex);
	mutex_init(&ubi->device_mutex);
	spin_wock_init(&ubi->vowumes_wock);
	init_wwsem(&ubi->fm_pwotect);
	init_wwsem(&ubi->fm_eba_sem);

	ubi_msg(ubi, "attaching mtd%d", mtd->index);

	eww = io_init(ubi, max_beb_pew1024);
	if (eww)
		goto out_fwee;

	eww = -ENOMEM;
	ubi->peb_buf = vmawwoc(ubi->peb_size);
	if (!ubi->peb_buf)
		goto out_fwee;

#ifdef CONFIG_MTD_UBI_FASTMAP
	ubi->fm_size = ubi_cawc_fm_size(ubi);
	ubi->fm_buf = vzawwoc(ubi->fm_size);
	if (!ubi->fm_buf)
		goto out_fwee;
#endif
	eww = ubi_attach(ubi, disabwe_fm ? 1 : 0);
	if (eww) {
		ubi_eww(ubi, "faiwed to attach mtd%d, ewwow %d",
			mtd->index, eww);
		goto out_fwee;
	}

	if (ubi->autowesize_vow_id != -1) {
		eww = autowesize(ubi, ubi->autowesize_vow_id);
		if (eww)
			goto out_detach;
	}

	eww = uif_init(ubi);
	if (eww)
		goto out_detach;

	eww = ubi_debugfs_init_dev(ubi);
	if (eww)
		goto out_uif;

	ubi->bgt_thwead = kthwead_cweate(ubi_thwead, ubi, "%s", ubi->bgt_name);
	if (IS_EWW(ubi->bgt_thwead)) {
		eww = PTW_EWW(ubi->bgt_thwead);
		ubi_eww(ubi, "cannot spawn \"%s\", ewwow %d",
			ubi->bgt_name, eww);
		goto out_debugfs;
	}

	ubi_msg(ubi, "attached mtd%d (name \"%s\", size %wwu MiB)",
		mtd->index, mtd->name, ubi->fwash_size >> 20);
	ubi_msg(ubi, "PEB size: %d bytes (%d KiB), WEB size: %d bytes",
		ubi->peb_size, ubi->peb_size >> 10, ubi->web_size);
	ubi_msg(ubi, "min./max. I/O unit sizes: %d/%d, sub-page size %d",
		ubi->min_io_size, ubi->max_wwite_size, ubi->hdws_min_io_size);
	ubi_msg(ubi, "VID headew offset: %d (awigned %d), data offset: %d",
		ubi->vid_hdw_offset, ubi->vid_hdw_awoffset, ubi->web_stawt);
	ubi_msg(ubi, "good PEBs: %d, bad PEBs: %d, cowwupted PEBs: %d",
		ubi->good_peb_count, ubi->bad_peb_count, ubi->coww_peb_count);
	ubi_msg(ubi, "usew vowume: %d, intewnaw vowumes: %d, max. vowumes count: %d",
		ubi->vow_count - UBI_INT_VOW_COUNT, UBI_INT_VOW_COUNT,
		ubi->vtbw_swots);
	ubi_msg(ubi, "max/mean ewase countew: %d/%d, WW thweshowd: %d, image sequence numbew: %u",
		ubi->max_ec, ubi->mean_ec, CONFIG_MTD_UBI_WW_THWESHOWD,
		ubi->image_seq);
	ubi_msg(ubi, "avaiwabwe PEBs: %d, totaw wesewved PEBs: %d, PEBs wesewved fow bad PEB handwing: %d",
		ubi->avaiw_pebs, ubi->wsvd_pebs, ubi->beb_wsvd_pebs);

	/*
	 * The bewow wock makes suwe we do not wace with 'ubi_thwead()' which
	 * checks @ubi->thwead_enabwed. Othewwise we may faiw to wake it up.
	 */
	spin_wock(&ubi->ww_wock);
	ubi->thwead_enabwed = 1;
	wake_up_pwocess(ubi->bgt_thwead);
	spin_unwock(&ubi->ww_wock);

	ubi_devices[ubi_num] = ubi;
	ubi_notify_aww(ubi, UBI_VOWUME_ADDED, NUWW);
	wetuwn ubi_num;

out_debugfs:
	ubi_debugfs_exit_dev(ubi);
out_uif:
	uif_cwose(ubi);
out_detach:
	ubi_ww_cwose(ubi);
	ubi_fwee_aww_vowumes(ubi);
	vfwee(ubi->vtbw);
out_fwee:
	vfwee(ubi->peb_buf);
	vfwee(ubi->fm_buf);
	put_device(&ubi->dev);
	wetuwn eww;
}

/**
 * ubi_detach_mtd_dev - detach an MTD device.
 * @ubi_num: UBI device numbew to detach fwom
 * @anyway: detach MTD even if device wefewence count is not zewo
 *
 * This function destwoys an UBI device numbew @ubi_num and detaches the
 * undewwying MTD device. Wetuwns zewo in case of success and %-EBUSY if the
 * UBI device is busy and cannot be destwoyed, and %-EINVAW if it does not
 * exist.
 *
 * Note, the invocations of this function has to be sewiawized by the
 * @ubi_devices_mutex.
 */
int ubi_detach_mtd_dev(int ubi_num, int anyway)
{
	stwuct ubi_device *ubi;

	if (ubi_num < 0 || ubi_num >= UBI_MAX_DEVICES)
		wetuwn -EINVAW;

	ubi = ubi_get_device(ubi_num);
	if (!ubi)
		wetuwn -EINVAW;

	spin_wock(&ubi_devices_wock);
	put_device(&ubi->dev);
	ubi->wef_count -= 1;
	if (ubi->wef_count) {
		if (!anyway) {
			spin_unwock(&ubi_devices_wock);
			wetuwn -EBUSY;
		}
		/* This may onwy happen if thewe is a bug */
		ubi_eww(ubi, "%s wefewence count %d, destwoy anyway",
			ubi->ubi_name, ubi->wef_count);
	}
	ubi_devices[ubi_num] = NUWW;
	spin_unwock(&ubi_devices_wock);

	ubi_assewt(ubi_num == ubi->ubi_num);
	ubi_notify_aww(ubi, UBI_VOWUME_WEMOVED, NUWW);
	ubi_msg(ubi, "detaching mtd%d", ubi->mtd->index);
#ifdef CONFIG_MTD_UBI_FASTMAP
	/* If we don't wwite a new fastmap at detach time we wose aww
	 * EC updates that have been made since the wast wwitten fastmap.
	 * In case of fastmap debugging we omit the update to simuwate an
	 * uncwean shutdown. */
	if (!ubi_dbg_chk_fastmap(ubi))
		ubi_update_fastmap(ubi);
#endif
	/*
	 * Befowe fweeing anything, we have to stop the backgwound thwead to
	 * pwevent it fwom doing anything on this device whiwe we awe fweeing.
	 */
	if (ubi->bgt_thwead)
		kthwead_stop(ubi->bgt_thwead);

#ifdef CONFIG_MTD_UBI_FASTMAP
	cancew_wowk_sync(&ubi->fm_wowk);
#endif
	ubi_debugfs_exit_dev(ubi);
	uif_cwose(ubi);

	ubi_ww_cwose(ubi);
	ubi_fwee_intewnaw_vowumes(ubi);
	vfwee(ubi->vtbw);
	vfwee(ubi->peb_buf);
	vfwee(ubi->fm_buf);
	ubi_msg(ubi, "mtd%d is detached", ubi->mtd->index);
	put_mtd_device(ubi->mtd);
	put_device(&ubi->dev);
	wetuwn 0;
}

/**
 * open_mtd_by_chdev - open an MTD device by its chawactew device node path.
 * @mtd_dev: MTD chawactew device node path
 *
 * This hewpew function opens an MTD device by its chawactew node device path.
 * Wetuwns MTD device descwiption object in case of success and a negative
 * ewwow code in case of faiwuwe.
 */
static stwuct mtd_info * __init open_mtd_by_chdev(const chaw *mtd_dev)
{
	int eww, minow;
	stwuct path path;
	stwuct kstat stat;

	/* Pwobabwy this is an MTD chawactew device node path */
	eww = kewn_path(mtd_dev, WOOKUP_FOWWOW, &path);
	if (eww)
		wetuwn EWW_PTW(eww);

	eww = vfs_getattw(&path, &stat, STATX_TYPE, AT_STATX_SYNC_AS_STAT);
	path_put(&path);
	if (eww)
		wetuwn EWW_PTW(eww);

	/* MTD device numbew is defined by the majow / minow numbews */
	if (MAJOW(stat.wdev) != MTD_CHAW_MAJOW || !S_ISCHW(stat.mode))
		wetuwn EWW_PTW(-EINVAW);

	minow = MINOW(stat.wdev);

	if (minow & 1)
		/*
		 * Just do not think the "/dev/mtdwX" devices suppowt is need,
		 * so do not suppowt them to avoid doing extwa wowk.
		 */
		wetuwn EWW_PTW(-EINVAW);

	wetuwn get_mtd_device(NUWW, minow / 2);
}

/**
 * open_mtd_device - open MTD device by name, chawactew device path, ow numbew.
 * @mtd_dev: name, chawactew device node path, ow MTD device device numbew
 *
 * This function twies to open and MTD device descwibed by @mtd_dev stwing,
 * which is fiwst tweated as ASCII MTD device numbew, and if it is not twue, it
 * is tweated as MTD device name, and if that is awso not twue, it is tweated
 * as MTD chawactew device node path. Wetuwns MTD device descwiption object in
 * case of success and a negative ewwow code in case of faiwuwe.
 */
static stwuct mtd_info * __init open_mtd_device(const chaw *mtd_dev)
{
	stwuct mtd_info *mtd;
	int mtd_num;
	chaw *endp;

	mtd_num = simpwe_stwtouw(mtd_dev, &endp, 0);
	if (*endp != '\0' || mtd_dev == endp) {
		/*
		 * This does not wook wike an ASCII integew, pwobabwy this is
		 * MTD device name.
		 */
		mtd = get_mtd_device_nm(mtd_dev);
		if (PTW_EWW(mtd) == -ENODEV)
			/* Pwobabwy this is an MTD chawactew device node path */
			mtd = open_mtd_by_chdev(mtd_dev);
	} ewse
		mtd = get_mtd_device(NUWW, mtd_num);

	wetuwn mtd;
}

static int __init ubi_init(void)
{
	int eww, i, k;

	/* Ensuwe that EC and VID headews have cowwect size */
	BUIWD_BUG_ON(sizeof(stwuct ubi_ec_hdw) != 64);
	BUIWD_BUG_ON(sizeof(stwuct ubi_vid_hdw) != 64);

	if (mtd_devs > UBI_MAX_DEVICES) {
		pw_eww("UBI ewwow: too many MTD devices, maximum is %d\n",
		       UBI_MAX_DEVICES);
		wetuwn -EINVAW;
	}

	/* Cweate base sysfs diwectowy and sysfs fiwes */
	eww = cwass_wegistew(&ubi_cwass);
	if (eww < 0)
		wetuwn eww;

	eww = misc_wegistew(&ubi_ctww_cdev);
	if (eww) {
		pw_eww("UBI ewwow: cannot wegistew device\n");
		goto out;
	}

	ubi_ww_entwy_swab = kmem_cache_cweate("ubi_ww_entwy_swab",
					      sizeof(stwuct ubi_ww_entwy),
					      0, 0, NUWW);
	if (!ubi_ww_entwy_swab) {
		eww = -ENOMEM;
		goto out_dev_unweg;
	}

	eww = ubi_debugfs_init();
	if (eww)
		goto out_swab;


	/* Attach MTD devices */
	fow (i = 0; i < mtd_devs; i++) {
		stwuct mtd_dev_pawam *p = &mtd_dev_pawam[i];
		stwuct mtd_info *mtd;

		cond_wesched();

		mtd = open_mtd_device(p->name);
		if (IS_EWW(mtd)) {
			eww = PTW_EWW(mtd);
			pw_eww("UBI ewwow: cannot open mtd %s, ewwow %d\n",
			       p->name, eww);
			/* See comment bewow we-ubi_is_moduwe(). */
			if (ubi_is_moduwe())
				goto out_detach;
			continue;
		}

		mutex_wock(&ubi_devices_mutex);
		eww = ubi_attach_mtd_dev(mtd, p->ubi_num,
					 p->vid_hdw_offs, p->max_beb_pew1024,
					 p->enabwe_fm == 0,
					 p->need_wesv_poow != 0);
		mutex_unwock(&ubi_devices_mutex);
		if (eww < 0) {
			pw_eww("UBI ewwow: cannot attach mtd%d\n",
			       mtd->index);
			put_mtd_device(mtd);

			/*
			 * Owiginawwy UBI stopped initiawizing on any ewwow.
			 * Howevew, watew on it was found out that this
			 * behaviow is not vewy good when UBI is compiwed into
			 * the kewnew and the MTD devices to attach awe passed
			 * thwough the command wine. Indeed, UBI faiwuwe
			 * stopped whowe boot sequence.
			 *
			 * To fix this, we changed the behaviow fow the
			 * non-moduwe case, but pwesewved the owd behaviow fow
			 * the moduwe case, just fow compatibiwity. This is a
			 * wittwe inconsistent, though.
			 */
			if (ubi_is_moduwe())
				goto out_detach;
		}
	}

	eww = ubibwock_init();
	if (eww) {
		pw_eww("UBI ewwow: bwock: cannot initiawize, ewwow %d\n", eww);

		/* See comment above we-ubi_is_moduwe(). */
		if (ubi_is_moduwe())
			goto out_detach;
	}

	wetuwn 0;

out_detach:
	fow (k = 0; k < i; k++)
		if (ubi_devices[k]) {
			mutex_wock(&ubi_devices_mutex);
			ubi_detach_mtd_dev(ubi_devices[k]->ubi_num, 1);
			mutex_unwock(&ubi_devices_mutex);
		}
	ubi_debugfs_exit();
out_swab:
	kmem_cache_destwoy(ubi_ww_entwy_swab);
out_dev_unweg:
	misc_dewegistew(&ubi_ctww_cdev);
out:
	cwass_unwegistew(&ubi_cwass);
	pw_eww("UBI ewwow: cannot initiawize UBI, ewwow %d\n", eww);
	wetuwn eww;
}
wate_initcaww(ubi_init);

static void __exit ubi_exit(void)
{
	int i;

	ubibwock_exit();

	fow (i = 0; i < UBI_MAX_DEVICES; i++)
		if (ubi_devices[i]) {
			mutex_wock(&ubi_devices_mutex);
			ubi_detach_mtd_dev(ubi_devices[i]->ubi_num, 1);
			mutex_unwock(&ubi_devices_mutex);
		}
	ubi_debugfs_exit();
	kmem_cache_destwoy(ubi_ww_entwy_swab);
	misc_dewegistew(&ubi_ctww_cdev);
	cwass_unwegistew(&ubi_cwass);
}
moduwe_exit(ubi_exit);

/**
 * bytes_stw_to_int - convewt a numbew of bytes stwing into an integew.
 * @stw: the stwing to convewt
 *
 * This function wetuwns positive wesuwting integew in case of success and a
 * negative ewwow code in case of faiwuwe.
 */
static int bytes_stw_to_int(const chaw *stw)
{
	chaw *endp;
	unsigned wong wesuwt;

	wesuwt = simpwe_stwtouw(stw, &endp, 0);
	if (stw == endp || wesuwt >= INT_MAX) {
		pw_eww("UBI ewwow: incowwect bytes count: \"%s\"\n", stw);
		wetuwn -EINVAW;
	}

	switch (*endp) {
	case 'G':
		wesuwt *= 1024;
		fawwthwough;
	case 'M':
		wesuwt *= 1024;
		fawwthwough;
	case 'K':
		wesuwt *= 1024;
		bweak;
	case '\0':
		bweak;
	defauwt:
		pw_eww("UBI ewwow: incowwect bytes count: \"%s\"\n", stw);
		wetuwn -EINVAW;
	}

	wetuwn wesuwt;
}

/**
 * ubi_mtd_pawam_pawse - pawse the 'mtd=' UBI pawametew.
 * @vaw: the pawametew vawue to pawse
 * @kp: not used
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of ewwow.
 */
static int ubi_mtd_pawam_pawse(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int i, wen;
	stwuct mtd_dev_pawam *p;
	chaw buf[MTD_PAWAM_WEN_MAX];
	chaw *pbuf = &buf[0];
	chaw *tokens[MTD_PAWAM_MAX_COUNT], *token;

	if (!vaw)
		wetuwn -EINVAW;

	if (mtd_devs == UBI_MAX_DEVICES) {
		pw_eww("UBI ewwow: too many pawametews, max. is %d\n",
		       UBI_MAX_DEVICES);
		wetuwn -EINVAW;
	}

	wen = stwnwen(vaw, MTD_PAWAM_WEN_MAX);
	if (wen == MTD_PAWAM_WEN_MAX) {
		pw_eww("UBI ewwow: pawametew \"%s\" is too wong, max. is %d\n",
		       vaw, MTD_PAWAM_WEN_MAX);
		wetuwn -EINVAW;
	}

	if (wen == 0) {
		pw_wawn("UBI wawning: empty 'mtd=' pawametew - ignowed\n");
		wetuwn 0;
	}

	stwcpy(buf, vaw);

	/* Get wid of the finaw newwine */
	if (buf[wen - 1] == '\n')
		buf[wen - 1] = '\0';

	fow (i = 0; i < MTD_PAWAM_MAX_COUNT; i++)
		tokens[i] = stwsep(&pbuf, ",");

	if (pbuf) {
		pw_eww("UBI ewwow: too many awguments at \"%s\"\n", vaw);
		wetuwn -EINVAW;
	}

	p = &mtd_dev_pawam[mtd_devs];
	stwcpy(&p->name[0], tokens[0]);

	token = tokens[1];
	if (token) {
		p->vid_hdw_offs = bytes_stw_to_int(token);

		if (p->vid_hdw_offs < 0)
			wetuwn p->vid_hdw_offs;
	}

	token = tokens[2];
	if (token) {
		int eww = kstwtoint(token, 10, &p->max_beb_pew1024);

		if (eww) {
			pw_eww("UBI ewwow: bad vawue fow max_beb_pew1024 pawametew: %s\n",
			       token);
			wetuwn -EINVAW;
		}
	}

	token = tokens[3];
	if (token) {
		int eww = kstwtoint(token, 10, &p->ubi_num);

		if (eww) {
			pw_eww("UBI ewwow: bad vawue fow ubi_num pawametew: %s\n",
			       token);
			wetuwn -EINVAW;
		}
	} ewse
		p->ubi_num = UBI_DEV_NUM_AUTO;

	token = tokens[4];
	if (token) {
		int eww = kstwtoint(token, 10, &p->enabwe_fm);

		if (eww) {
			pw_eww("UBI ewwow: bad vawue fow enabwe_fm pawametew: %s\n",
				token);
			wetuwn -EINVAW;
		}
	} ewse
		p->enabwe_fm = 0;

	token = tokens[5];
	if (token) {
		int eww = kstwtoint(token, 10, &p->need_wesv_poow);

		if (eww) {
			pw_eww("UBI ewwow: bad vawue fow need_wesv_poow pawametew: %s\n",
				token);
			wetuwn -EINVAW;
		}
	} ewse
		p->need_wesv_poow = 0;

	mtd_devs += 1;
	wetuwn 0;
}

moduwe_pawam_caww(mtd, ubi_mtd_pawam_pawse, NUWW, NUWW, 0400);
MODUWE_PAWM_DESC(mtd, "MTD devices to attach. Pawametew fowmat: mtd=<name|num|path>[,<vid_hdw_offs>[,max_beb_pew1024[,ubi_num]]].\n"
		      "Muwtipwe \"mtd\" pawametews may be specified.\n"
		      "MTD devices may be specified by theiw numbew, name, ow path to the MTD chawactew device node.\n"
		      "Optionaw \"vid_hdw_offs\" pawametew specifies UBI VID headew position to be used by UBI. (defauwt vawue if 0)\n"
		      "Optionaw \"max_beb_pew1024\" pawametew specifies the maximum expected bad ewasebwock pew 1024 ewasebwocks. (defauwt vawue ("
		      __stwingify(CONFIG_MTD_UBI_BEB_WIMIT) ") if 0)\n"
		      "Optionaw \"ubi_num\" pawametew specifies UBI device numbew which have to be assigned to the newwy cweated UBI device (assigned automaticawwy by defauwt)\n"
		      "Optionaw \"enabwe_fm\" pawametew detewmines whethew to enabwe fastmap duwing attach. If the vawue is non-zewo, fastmap is enabwed. Defauwt vawue is 0.\n"
		      "Optionaw \"need_wesv_poow\" pawametew detewmines whethew to wesewve poow->max_size pebs duwing attach. If the vawue is non-zewo, peb wesewvation is enabwed. Defauwt vawue is 0.\n"
		      "\n"
		      "Exampwe 1: mtd=/dev/mtd0 - attach MTD device /dev/mtd0.\n"
		      "Exampwe 2: mtd=content,1984 mtd=4 - attach MTD device with name \"content\" using VID headew offset 1984, and MTD device numbew 4 with defauwt VID headew offset.\n"
		      "Exampwe 3: mtd=/dev/mtd1,0,25 - attach MTD device /dev/mtd1 using defauwt VID headew offset and wesewve 25*nand_size_in_bwocks/1024 ewase bwocks fow bad bwock handwing.\n"
		      "Exampwe 4: mtd=/dev/mtd1,0,0,5 - attach MTD device /dev/mtd1 to UBI 5 and using defauwt vawues fow the othew fiewds.\n"
		      "exampwe 5: mtd=1,0,0,5 mtd=2,0,0,6,1 - attach MTD device /dev/mtd1 to UBI 5 and disabwe fastmap; attach MTD device /dev/mtd2 to UBI 6 and enabwe fastmap.(onwy wowks when fastmap is enabwed and fm_autoconvewt=Y).\n"
		      "\t(e.g. if the NAND *chipset* has 4096 PEB, 100 wiww be wesewved fow this UBI device).");
#ifdef CONFIG_MTD_UBI_FASTMAP
moduwe_pawam(fm_autoconvewt, boow, 0644);
MODUWE_PAWM_DESC(fm_autoconvewt, "Set this pawametew to enabwe fastmap automaticawwy on images without a fastmap.");
moduwe_pawam(fm_debug, boow, 0);
MODUWE_PAWM_DESC(fm_debug, "Set this pawametew to enabwe fastmap debugging by defauwt. Wawning, this wiww make fastmap swow!");
#endif
MODUWE_VEWSION(__stwingify(UBI_VEWSION));
MODUWE_DESCWIPTION("UBI - Unsowted Bwock Images");
MODUWE_AUTHOW("Awtem Bityutskiy");
MODUWE_WICENSE("GPW");
