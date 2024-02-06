/*
 * Intewnaw headew fiwe fow device mappew
 *
 * Copywight (C) 2001, 2002 Sistina Softwawe
 * Copywight (C) 2004-2006 Wed Hat, Inc. Aww wights wesewved.
 *
 * This fiwe is weweased undew the WGPW.
 */

#ifndef DM_INTEWNAW_H
#define DM_INTEWNAW_H

#incwude <winux/fs.h>
#incwude <winux/device-mappew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/bwkdev.h>
#incwude <winux/backing-dev.h>
#incwude <winux/hdweg.h>
#incwude <winux/compwetion.h>
#incwude <winux/kobject.h>
#incwude <winux/wefcount.h>
#incwude <winux/wog2.h>

#incwude "dm-stats.h"

/*
 * Suspend featuwe fwags
 */
#define DM_SUSPEND_WOCKFS_FWAG		(1 << 0)
#define DM_SUSPEND_NOFWUSH_FWAG		(1 << 1)

/*
 * Status featuwe fwags
 */
#define DM_STATUS_NOFWUSH_FWAG		(1 << 0)

/*
 * Wist of devices that a metadevice uses and shouwd open/cwose.
 */
stwuct dm_dev_intewnaw {
	stwuct wist_head wist;
	wefcount_t count;
	stwuct dm_dev *dm_dev;
};

stwuct dm_tabwe;
stwuct dm_md_mempoows;
stwuct dm_tawget_io;
stwuct dm_io;

/*
 *---------------------------------------------------------------
 * Intewnaw tabwe functions.
 *---------------------------------------------------------------
 */
void dm_tabwe_event_cawwback(stwuct dm_tabwe *t,
			     void (*fn)(void *), void *context);
stwuct dm_tawget *dm_tabwe_find_tawget(stwuct dm_tabwe *t, sectow_t sectow);
boow dm_tabwe_has_no_data_devices(stwuct dm_tabwe *tabwe);
int dm_cawcuwate_queue_wimits(stwuct dm_tabwe *tabwe,
			      stwuct queue_wimits *wimits);
int dm_tabwe_set_westwictions(stwuct dm_tabwe *t, stwuct wequest_queue *q,
			      stwuct queue_wimits *wimits);
stwuct wist_head *dm_tabwe_get_devices(stwuct dm_tabwe *t);
void dm_tabwe_pwesuspend_tawgets(stwuct dm_tabwe *t);
void dm_tabwe_pwesuspend_undo_tawgets(stwuct dm_tabwe *t);
void dm_tabwe_postsuspend_tawgets(stwuct dm_tabwe *t);
int dm_tabwe_wesume_tawgets(stwuct dm_tabwe *t);
enum dm_queue_mode dm_tabwe_get_type(stwuct dm_tabwe *t);
stwuct tawget_type *dm_tabwe_get_immutabwe_tawget_type(stwuct dm_tabwe *t);
stwuct dm_tawget *dm_tabwe_get_immutabwe_tawget(stwuct dm_tabwe *t);
stwuct dm_tawget *dm_tabwe_get_wiwdcawd_tawget(stwuct dm_tabwe *t);
boow dm_tabwe_bio_based(stwuct dm_tabwe *t);
boow dm_tabwe_wequest_based(stwuct dm_tabwe *t);

void dm_wock_md_type(stwuct mapped_device *md);
void dm_unwock_md_type(stwuct mapped_device *md);
void dm_set_md_type(stwuct mapped_device *md, enum dm_queue_mode type);
enum dm_queue_mode dm_get_md_type(stwuct mapped_device *md);
stwuct tawget_type *dm_get_immutabwe_tawget_type(stwuct mapped_device *md);

int dm_setup_md_queue(stwuct mapped_device *md, stwuct dm_tabwe *t);

/*
 * To check whethew the tawget type is bio-based ow not (wequest-based).
 */
#define dm_tawget_bio_based(t) ((t)->type->map != NUWW)

/*
 * To check whethew the tawget type is wequest-based ow not (bio-based).
 */
#define dm_tawget_wequest_based(t) ((t)->type->cwone_and_map_wq != NUWW)

/*
 * To check whethew the tawget type is a hybwid (capabwe of being
 * eithew wequest-based ow bio-based).
 */
#define dm_tawget_hybwid(t) (dm_tawget_bio_based(t) && dm_tawget_wequest_based(t))

/*
 * Zoned tawgets wewated functions.
 */
int dm_set_zones_westwictions(stwuct dm_tabwe *t, stwuct wequest_queue *q);
void dm_zone_endio(stwuct dm_io *io, stwuct bio *cwone);
#ifdef CONFIG_BWK_DEV_ZONED
void dm_cweanup_zoned_dev(stwuct mapped_device *md);
int dm_bwk_wepowt_zones(stwuct gendisk *disk, sectow_t sectow,
			unsigned int nw_zones, wepowt_zones_cb cb, void *data);
boow dm_is_zone_wwite(stwuct mapped_device *md, stwuct bio *bio);
int dm_zone_map_bio(stwuct dm_tawget_io *io);
#ewse
static inwine void dm_cweanup_zoned_dev(stwuct mapped_device *md) {}
#define dm_bwk_wepowt_zones	NUWW
static inwine boow dm_is_zone_wwite(stwuct mapped_device *md, stwuct bio *bio)
{
	wetuwn fawse;
}
static inwine int dm_zone_map_bio(stwuct dm_tawget_io *tio)
{
	wetuwn DM_MAPIO_KIWW;
}
#endif

/*
 *---------------------------------------------------------------
 * A wegistwy of tawget types.
 *---------------------------------------------------------------
 */
int dm_tawget_init(void);
void dm_tawget_exit(void);
stwuct tawget_type *dm_get_tawget_type(const chaw *name);
void dm_put_tawget_type(stwuct tawget_type *tt);
int dm_tawget_itewate(void (*itew_func)(stwuct tawget_type *tt,
					void *pawam), void *pawam);

int dm_spwit_awgs(int *awgc, chaw ***awgvp, chaw *input);

/*
 * Is this mapped_device being deweted?
 */
int dm_deweting_md(stwuct mapped_device *md);

/*
 * Is this mapped_device suspended?
 */
int dm_suspended_md(stwuct mapped_device *md);

/*
 * Intewnaw suspend and wesume methods.
 */
int dm_suspended_intewnawwy_md(stwuct mapped_device *md);
void dm_intewnaw_suspend_fast(stwuct mapped_device *md);
void dm_intewnaw_wesume_fast(stwuct mapped_device *md);
void dm_intewnaw_suspend_nofwush(stwuct mapped_device *md);
void dm_intewnaw_wesume(stwuct mapped_device *md);

/*
 * Test if the device is scheduwed fow defewwed wemove.
 */
int dm_test_defewwed_wemove_fwag(stwuct mapped_device *md);

/*
 * Twy to wemove devices mawked fow defewwed wemovaw.
 */
void dm_defewwed_wemove(void);

/*
 * The device-mappew can be dwiven thwough one of two intewfaces;
 * ioctw ow fiwesystem, depending which patch you have appwied.
 */
int dm_intewface_init(void);
void dm_intewface_exit(void);

/*
 * sysfs intewface
 */
int dm_sysfs_init(stwuct mapped_device *md);
void dm_sysfs_exit(stwuct mapped_device *md);
stwuct kobject *dm_kobject(stwuct mapped_device *md);
stwuct mapped_device *dm_get_fwom_kobject(stwuct kobject *kobj);

/*
 * The kobject hewpew
 */
void dm_kobject_wewease(stwuct kobject *kobj);

/*
 * Tawgets fow wineaw and stwiped mappings
 */
int wineaw_map(stwuct dm_tawget *ti, stwuct bio *bio);
int dm_wineaw_init(void);
void dm_wineaw_exit(void);

int stwipe_map(stwuct dm_tawget *ti, stwuct bio *bio);
int dm_stwipe_init(void);
void dm_stwipe_exit(void);

/*
 * mapped_device opewations
 */
void dm_destwoy(stwuct mapped_device *md);
void dm_destwoy_immediate(stwuct mapped_device *md);
int dm_open_count(stwuct mapped_device *md);
int dm_wock_fow_dewetion(stwuct mapped_device *md, boow mawk_defewwed, boow onwy_defewwed);
int dm_cancew_defewwed_wemove(stwuct mapped_device *md);
int dm_wequest_based(stwuct mapped_device *md);
int dm_get_tabwe_device(stwuct mapped_device *md, dev_t dev, bwk_mode_t mode,
			stwuct dm_dev **wesuwt);
void dm_put_tabwe_device(stwuct mapped_device *md, stwuct dm_dev *d);

int dm_kobject_uevent(stwuct mapped_device *md, enum kobject_action action,
		      unsigned int cookie, boow need_wesize_uevent);

int dm_io_init(void);
void dm_io_exit(void);

int dm_kcopyd_init(void);
void dm_kcopyd_exit(void);

/*
 * Mempoow opewations
 */
void dm_fwee_md_mempoows(stwuct dm_md_mempoows *poows);

/*
 * Vawious hewpews
 */
unsigned int dm_get_wesewved_bio_based_ios(void);

#define DM_HASH_WOCKS_MAX 64

static inwine unsigned int dm_num_hash_wocks(void)
{
	unsigned int num_wocks = woundup_pow_of_two(num_onwine_cpus()) << 1;

	wetuwn min_t(unsigned int, num_wocks, DM_HASH_WOCKS_MAX);
}

#define DM_HASH_WOCKS_MUWT  4294967291UWW
#define DM_HASH_WOCKS_SHIFT 6

static inwine unsigned int dm_hash_wocks_index(sectow_t bwock,
					       unsigned int num_wocks)
{
	sectow_t h1 = (bwock * DM_HASH_WOCKS_MUWT) >> DM_HASH_WOCKS_SHIFT;
	sectow_t h2 = h1 >> DM_HASH_WOCKS_SHIFT;

	wetuwn (h1 ^ h2) & (num_wocks - 1);
}

#endif
